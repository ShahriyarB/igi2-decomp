"""TPI stream: the type records a PDB's symbols point at."""
import struct

from .leaf import cstr, numeric, skip_pad

LF_MODIFIER = 0x1001
LF_POINTER = 0x1002
LF_PROCEDURE = 0x1008
LF_MFUNCTION = 0x1009
LF_VTSHAPE = 0x000A
LF_ARGLIST = 0x1201
LF_FIELDLIST = 0x1203
LF_BITFIELD = 0x1205
LF_METHODLIST = 0x1206
LF_ARRAY = 0x1503
LF_CLASS = 0x1504
LF_STRUCTURE = 0x1505
LF_UNION = 0x1506
LF_ENUM = 0x1507

LF_BCLASS = 0x1400
LF_VBCLASS = 0x1401
LF_IVBCLASS = 0x1402
LF_INDEX = 0x1404
LF_VFUNCTAB = 0x1409
LF_ENUMERATE = 0x1502
LF_MEMBER = 0x150D
LF_STMEMBER = 0x150E
LF_METHOD = 0x150F
LF_NESTTYPE = 0x1510
LF_ONEMETHOD = 0x1511

# property bits on struct/union/enum records
PROP_FWDREF = 0x0080
PROP_HASUNIQUENAME = 0x0200


class Tpi:
    """Decoded type records keyed by type index (>= 0x1000)."""

    def __init__(self, data):
        _ver, header, self.ti_min, self.ti_max, _bytes = struct.unpack_from("<5I", data)
        self.types = {}
        pos, ti = header, self.ti_min
        while pos < len(data):
            length, kind = struct.unpack_from("<HH", data, pos)
            self.types[ti] = self._decode(data, pos + 4, pos + 2 + length, kind)
            pos += 2 + length
            ti += 1

    def __getitem__(self, ti):
        return self.types[ti]

    def get(self, ti):
        return self.types.get(ti)

    def _decode(self, b, p, end, kind):
        if kind == LF_MODIFIER:
            t, attr = struct.unpack_from("<IH", b, p)
            return {"kind": "modifier", "type": t, "const": bool(attr & 1), "volatile": bool(attr & 2)}
        if kind == LF_POINTER:
            t, attr = struct.unpack_from("<II", b, p)
            return {"kind": "pointer", "type": t, "mode": (attr >> 5) & 7, "ptrtype": attr & 0x1F,
                    "const": bool(attr & 0x400), "volatile": bool(attr & 0x200)}
        if kind == LF_PROCEDURE:
            rv, call, _attr, n, args = struct.unpack_from("<IBBHI", b, p)
            return {"kind": "procedure", "ret": rv, "call": call, "nparams": n, "args": args}
        if kind == LF_MFUNCTION:
            rv, cls, this, call, _attr, n, args, adj = struct.unpack_from("<IIIBBHIi", b, p)
            return {"kind": "mfunction", "ret": rv, "class": cls, "this": this, "call": call,
                    "nparams": n, "args": args}
        if kind == LF_ARGLIST:
            n = struct.unpack_from("<I", b, p)[0]
            return {"kind": "arglist", "args": list(struct.unpack_from(f"<{n}I", b, p + 4))}
        if kind == LF_BITFIELD:
            t, length, position = struct.unpack_from("<IBB", b, p)
            return {"kind": "bitfield", "type": t, "length": length, "position": position}
        if kind == LF_ARRAY:
            elem, idx = struct.unpack_from("<II", b, p)
            size, q = numeric(b, p + 8)
            name, _ = cstr(b, q) if q < end else ("", q)
            return {"kind": "array", "type": elem, "index": idx, "size": size, "name": name}
        if kind in (LF_CLASS, LF_STRUCTURE):
            count, prop, field, derived, vshape = struct.unpack_from("<HHIII", b, p)
            size, q = numeric(b, p + 16)
            name, q = cstr(b, q)
            unique = cstr(b, q)[0] if prop & PROP_HASUNIQUENAME and q < end else None
            return {"kind": "class" if kind == LF_CLASS else "struct", "count": count, "prop": prop,
                    "fields": field, "size": size, "name": name, "unique": unique,
                    "fwdref": bool(prop & PROP_FWDREF)}
        if kind == LF_UNION:
            count, prop, field = struct.unpack_from("<HHI", b, p)
            size, q = numeric(b, p + 8)
            name, q = cstr(b, q)
            unique = cstr(b, q)[0] if prop & PROP_HASUNIQUENAME and q < end else None
            return {"kind": "union", "count": count, "prop": prop, "fields": field, "size": size,
                    "name": name, "unique": unique, "fwdref": bool(prop & PROP_FWDREF)}
        if kind == LF_ENUM:
            count, prop, utype, field = struct.unpack_from("<HHII", b, p)
            name, q = cstr(b, p + 12)
            unique = cstr(b, q)[0] if prop & PROP_HASUNIQUENAME and q < end else None
            return {"kind": "enum", "count": count, "prop": prop, "utype": utype, "fields": field,
                    "name": name, "unique": unique, "fwdref": bool(prop & PROP_FWDREF)}
        if kind == LF_FIELDLIST:
            return {"kind": "fieldlist", "members": self._fieldlist(b, p, end)}
        if kind == LF_METHODLIST:
            return {"kind": "methodlist"}
        if kind == LF_VTSHAPE:
            return {"kind": "vtshape"}
        return {"kind": f"leaf_{kind:#06x}"}

    @staticmethod
    def _fieldlist(b, p, end):
        out = []
        while p < end:
            kind = struct.unpack_from("<H", b, p)[0]
            p += 2
            if kind == LF_MEMBER:
                attr, t = struct.unpack_from("<HI", b, p)
                off, p = numeric(b, p + 6)
                name, p = cstr(b, p)
                out.append({"kind": "member", "type": t, "offset": off, "name": name, "attr": attr})
            elif kind == LF_ENUMERATE:
                attr = struct.unpack_from("<H", b, p)[0]
                val, p = numeric(b, p + 2)
                name, p = cstr(b, p)
                out.append({"kind": "enumerate", "value": val, "name": name})
            elif kind == LF_STMEMBER:
                attr, t = struct.unpack_from("<HI", b, p)
                name, p = cstr(b, p + 6)
                out.append({"kind": "stmember", "type": t, "name": name})
            elif kind == LF_NESTTYPE:
                _pad, t = struct.unpack_from("<HI", b, p)
                name, p = cstr(b, p + 6)
                out.append({"kind": "nesttype", "type": t, "name": name})
            elif kind == LF_BCLASS:
                attr, t = struct.unpack_from("<HI", b, p)
                off, p = numeric(b, p + 6)
                out.append({"kind": "bclass", "type": t, "offset": off})
            elif kind in (LF_VBCLASS, LF_IVBCLASS):
                attr, bt, vbp = struct.unpack_from("<HII", b, p)
                _, p = numeric(b, p + 10)
                _, p = numeric(b, p)
                out.append({"kind": "vbclass", "type": bt})
            elif kind == LF_VFUNCTAB:
                _pad, t = struct.unpack_from("<HI", b, p)
                p += 6
                out.append({"kind": "vfunctab", "type": t})
            elif kind == LF_ONEMETHOD:
                attr, t = struct.unpack_from("<HI", b, p)
                p += 6
                if ((attr >> 2) & 7) in (4, 6):  # introducing virtual: vbaseoff follows
                    p += 4
                name, p = cstr(b, p)
                out.append({"kind": "method", "type": t, "name": name})
            elif kind == LF_METHOD:
                _count, _mlist = struct.unpack_from("<HI", b, p)
                name, p = cstr(b, p + 6)
                out.append({"kind": "methods", "name": name})
            elif kind == LF_INDEX:
                _pad, t = struct.unpack_from("<HI", b, p)
                p += 6
                out.append({"kind": "index", "type": t})
            else:
                raise ValueError(f"unknown field leaf {kind:#x}")
            p = skip_pad(b, p, end)
        return out
