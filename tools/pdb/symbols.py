"""Module symbol streams (procedures, locals, statics), C11 line tables and global symbols."""
import struct

from .leaf import cstr, numeric

S_END = 0x0006
S_OBJNAME = 0x1101
S_THUNK32 = 0x1102
S_BLOCK32 = 0x1103
S_WITH32 = 0x1104
S_LABEL32 = 0x1105
S_REGISTER = 0x1106
S_CONSTANT = 0x1107
S_UDT = 0x1108
S_BPREL32 = 0x110B
S_LDATA32 = 0x110C
S_GDATA32 = 0x110D
S_PUB32 = 0x110E
S_LPROC32 = 0x110F
S_GPROC32 = 0x1110
S_REGREL32 = 0x1111
S_LTHREAD32 = 0x1112
S_GTHREAD32 = 0x1113
S_COMPILE2 = 0x1116
S_PROCREF = 0x1125
S_LPROCREF = 0x1127

_SCOPE_OPEN = (S_GPROC32, S_LPROC32, S_BLOCK32, S_THUNK32, S_WITH32)

# CV_HREG_e for x86, the ones register locals use
X86_REGS = {1: "al", 2: "cl", 3: "dl", 4: "bl", 5: "ah", 6: "ch", 7: "dh", 8: "bh",
            9: "ax", 10: "cx", 11: "dx", 12: "bx", 13: "sp", 14: "bp", 15: "si", 16: "di",
            17: "eax", 18: "ecx", 19: "edx", 20: "ebx", 21: "esp", 22: "ebp", 23: "esi", 24: "edi",
            128: "st0", 129: "st1", 130: "st2", 131: "st3", 132: "st4", 133: "st5", 134: "st6",
            135: "st7"}


def _reg(r):
    if r in X86_REGS:
        return X86_REGS[r]
    lo, hi = r & 0xFF, r >> 8
    if lo in X86_REGS and hi in X86_REGS:  # register pair, e.g. edx:eax for 64-bit values
        return f"{X86_REGS[hi]}:{X86_REGS[lo]}"
    return f"reg{r}"


def module_symbols(msf, dbi, mod):
    """Procedures, file-scope data and compiler info declared in one module."""
    s = msf.stream(mod.stream)
    procs, data, compile_info = [], [], None
    stack = []  # open scopes; procs and blocks
    pos, end = 4, mod.sym_bytes
    while pos < end:
        length, kind = struct.unpack_from("<HH", s, pos)
        p, nxt = pos + 4, pos + 2 + length
        pos = nxt
        if kind in (S_GPROC32, S_LPROC32):
            _par, _end, _next, plen, dbg_start, dbg_end, ti, off, seg, flags = \
                struct.unpack_from("<7IIHB", s, p)
            name, _ = cstr(s, p + 35)
            proc = {"name": name, "static": kind == S_LPROC32, "type": ti, "seg": seg, "off": off,
                    "rva": dbi.rva(seg, off), "length": plen, "dbg_start": dbg_start,
                    "dbg_end": dbg_end, "flags": flags, "locals": [], "statics": [], "labels": [],
                    "blocks": 0}
            procs.append(proc)
            stack.append(proc)
        elif kind == S_BLOCK32:
            _par, _end, blen, off, seg = struct.unpack_from("<3IIH", s, p)
            owner = next((x for x in reversed(stack) if isinstance(x, dict)), None)
            if owner is not None:
                owner["blocks"] += 1
            stack.append("block")
        elif kind in (S_THUNK32, S_WITH32):
            stack.append("thunk")
        elif kind == S_END:
            if stack:
                stack.pop()
        elif kind in (S_BPREL32, S_REGISTER, S_REGREL32):
            proc = next((x for x in reversed(stack) if isinstance(x, dict)), None)
            depth = sum(1 for x in stack if x == "block")
            if kind == S_BPREL32:
                off, ti = struct.unpack_from("<iI", s, p)
                name, _ = cstr(s, p + 8)
                where = {"bp": off}
            elif kind == S_REGISTER:
                ti, reg = struct.unpack_from("<IH", s, p)
                name, _ = cstr(s, p + 6)
                where = {"reg": _reg(reg)}
            else:
                off, ti, reg = struct.unpack_from("<iIH", s, p)
                name, _ = cstr(s, p + 10)
                where = {"reg": _reg(reg), "off": off}
            if proc is not None:
                proc["locals"].append({"name": name, "type": ti, "depth": depth, **where})
        elif kind in (S_LDATA32, S_GDATA32, S_LTHREAD32, S_GTHREAD32):
            ti, off, seg = struct.unpack_from("<IIH", s, p)
            name, _ = cstr(s, p + 10)
            rec = {"name": name, "type": ti, "seg": seg, "off": off, "rva": dbi.rva(seg, off),
                   "static": kind in (S_LDATA32, S_LTHREAD32),
                   "tls": kind in (S_LTHREAD32, S_GTHREAD32)}
            proc = next((x for x in reversed(stack) if isinstance(x, dict)), None)
            (proc["statics"] if proc is not None else data).append(rec)
        elif kind == S_LABEL32:
            off, seg, _flags = struct.unpack_from("<IHB", s, p)
            name, _ = cstr(s, p + 7)
            proc = next((x for x in reversed(stack) if isinstance(x, dict)), None)
            if proc is not None:
                proc["labels"].append({"name": name, "rva": dbi.rva(seg, off)})
        elif kind == S_COMPILE2:
            flags, machine = struct.unpack_from("<IH", s, p)
            fe = struct.unpack_from("<4H", s, p + 6)
            be = struct.unpack_from("<4H", s, p + 14)
            ver, _ = cstr(s, p + 22)
            compile_info = {"lang": flags & 0xFF, "machine": machine, "frontend": list(fe),
                            "backend": list(be), "version": ver}
    lines = c11_lines(s[mod.sym_bytes:mod.sym_bytes + mod.c11_bytes], dbi) if mod.c11_bytes else []
    return procs, data, compile_info, lines


def c11_lines(b, dbi):
    """Old-style (C11) line table: [(file, [(rva, line), ...]), ...]."""
    cfile, cseg = struct.unpack_from("<HH", b)
    file_offs = struct.unpack_from(f"<{cfile}I", b, 4)
    out = []
    for fo in file_offs:
        nseg = struct.unpack_from("<H", b, fo)[0]
        seg_offs = struct.unpack_from(f"<{nseg}I", b, fo + 4)
        q = fo + 4 + 4 * nseg + 8 * nseg
        # VC 7.0 writes the name zero-terminated; older linkers wrote a length-prefixed one
        name = b[q + 1:q + 1 + b[q]].decode("latin1") if b[q] < 0x20 else cstr(b, q)[0]
        pairs = []
        for so in seg_offs:
            seg, n = struct.unpack_from("<HH", b, so)
            offs = struct.unpack_from(f"<{n}I", b, so + 4)
            nums = struct.unpack_from(f"<{n}H", b, so + 4 + 4 * n)
            pairs.extend((dbi.rva(seg, o), ln) for o, ln in zip(offs, nums))
        out.append((name, pairs))
    return out


def global_symbols(msf, dbi):
    """Public symbols (decorated names) and global data from the symbol record stream."""
    s = msf.stream(dbi.symrec_stream)
    publics, gdata, udts = [], [], {}
    pos = 0
    while pos + 4 <= len(s):
        length, kind = struct.unpack_from("<HH", s, pos)
        p = pos + 4
        pos += 2 + length
        if kind == S_PUB32:
            flags, off, seg = struct.unpack_from("<IIH", s, p)
            name, _ = cstr(s, p + 10)
            publics.append({"name": name, "rva": dbi.rva(seg, off), "seg": seg, "off": off,
                            "code": bool(flags & 2), "function": bool(flags & 2)})
        elif kind in (S_GDATA32, S_LDATA32, S_GTHREAD32):
            ti, off, seg = struct.unpack_from("<IIH", s, p)
            name, _ = cstr(s, p + 10)
            gdata.append({"name": name, "type": ti, "rva": dbi.rva(seg, off), "seg": seg,
                          "off": off, "static": kind == S_LDATA32})
        elif kind == S_UDT:
            ti = struct.unpack_from("<I", s, p)[0]
            udts[cstr(s, p + 4)[0]] = ti
    return publics, gdata, udts
