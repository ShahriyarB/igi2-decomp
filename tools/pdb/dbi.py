"""DBI stream: modules, their source files, section headers and the symbol record stream."""
import struct
import uuid

from .leaf import cstr

SECTION_HEADER_DBG_INDEX = 5  # optional debug header slot holding IMAGE_SECTION_HEADERs


class Module:
    __slots__ = ("index", "name", "obj", "stream", "sym_bytes", "c11_bytes", "c13_bytes",
                 "contrib", "files")

    def __init__(self, **kw):
        for k, v in kw.items():
            setattr(self, k, v)
        self.files = []

    @property
    def lib(self):
        """Library the module was linked from ('' for objects compiled into the exe directly)."""
        return self.obj if self.obj.lower().endswith(".lib") else ""


class Dbi:
    def __init__(self, msf):
        info = msf.stream(1)
        self.version, self.signature, self.age = struct.unpack_from("<3I", info)
        self.guid = str(uuid.UUID(bytes_le=info[12:28]))

        d = msf.stream(3)
        h = struct.unpack_from("<iIIHHHHHHiiiiiIiiHHI", d)
        self.age_dbi = h[2]
        self.global_stream, self.public_stream, self.symrec_stream = h[3], h[5], h[7]
        mod_size, sc_size, secmap_size, src_size, tsm_size = h[9], h[10], h[11], h[12], h[13]
        dbg_size, ec_size = h[15], h[16]

        self.modules = self._modules(d, 64, 64 + mod_size)
        src = 64 + mod_size + sc_size + secmap_size
        self._source_files(d[src:src + src_size])
        dbg = src + src_size + tsm_size + ec_size
        self.dbg_streams = struct.unpack_from(f"<{dbg_size // 2}H", d, dbg)

        self.sections = []  # (name, rva, virtual_size)
        hdrs = msf.stream(self.dbg_streams[SECTION_HEADER_DBG_INDEX])
        for i in range(len(hdrs) // 40):
            name, vsize, rva = struct.unpack_from("<8sII", hdrs, 40 * i)
            self.sections.append((name.rstrip(b"\0").decode("latin1"), rva, vsize))

    def rva(self, seg, off):
        """Section:offset as an RVA (segments are 1-based)."""
        if 1 <= seg <= len(self.sections):
            return self.sections[seg - 1][1] + off
        return None

    @staticmethod
    def _modules(d, pos, end):
        mods = []
        while pos < end:
            sec, _pad, off, size, chars, modi = struct.unpack_from("<HHiiIH", d, pos + 4)
            _flags, stream, sym_bytes, c11, c13 = struct.unpack_from("<HHIII", d, pos + 32)
            name, q = cstr(d, pos + 64)
            obj, q = cstr(d, q)
            mods.append(Module(index=len(mods), name=name, obj=obj, stream=stream,
                               sym_bytes=sym_bytes, c11_bytes=c11, c13_bytes=c13,
                               contrib=(sec, off, size, chars)))
            pos = (q + 3) & ~3
        return mods

    def _source_files(self, s):
        nmods = struct.unpack_from("<H", s)[0]
        counts = struct.unpack_from(f"<{nmods}H", s, 4 + 2 * nmods)
        total = sum(counts)
        offs = struct.unpack_from(f"<{total}I", s, 4 + 4 * nmods)
        names = 4 + 4 * nmods + 4 * total
        k = 0
        for mod, n in zip(self.modules, counts):
            mod.files = [cstr(s, names + o)[0] for o in offs[k:k + n]]
            k += n
