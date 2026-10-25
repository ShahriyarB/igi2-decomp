"""Render PDB type indices as C declarations."""

_BASIC = {
    0x00: "void", 0x03: "void", 0x08: "HRESULT",
    0x10: "signed char", 0x11: "short", 0x12: "long", 0x13: "__int64",
    0x20: "unsigned char", 0x21: "unsigned short", 0x22: "unsigned long", 0x23: "unsigned __int64",
    0x30: "unsigned char", 0x31: "unsigned short", 0x32: "unsigned long", 0x33: "unsigned __int64",
    0x40: "float", 0x41: "double", 0x42: "long double",
    0x68: "signed char", 0x69: "unsigned char", 0x70: "char", 0x71: "wchar_t",
    0x72: "short", 0x73: "unsigned short", 0x74: "int", 0x75: "unsigned int",
    0x76: "__int64", 0x77: "unsigned __int64",
}
_BASIC_SIZE = {0x00: 0, 0x03: 0, 0x08: 4, 0x10: 1, 0x11: 2, 0x12: 4, 0x13: 8, 0x20: 1, 0x21: 2,
               0x22: 4, 0x23: 8, 0x30: 1, 0x31: 2, 0x32: 4, 0x33: 8, 0x40: 4, 0x41: 8, 0x42: 10,
               0x68: 1, 0x69: 1, 0x70: 1, 0x71: 2, 0x72: 2, 0x73: 2, 0x74: 4, 0x75: 4, 0x76: 8,
               0x77: 8}

CALL_CONV = {0x00: "__cdecl", 0x04: "__fastcall", 0x07: "__stdcall", 0x0B: "__thiscall"}


class TypeNamer:
    """Names aggregate types and renders declarators, resolving forward references."""

    def __init__(self, tpi, typedefs=None):
        self.tpi = tpi
        self.typedefs = typedefs or {}  # ti -> typedef name, from S_UDT
        self._defs = {}
        for ti, t in tpi.types.items():
            if t["kind"] in ("struct", "class", "union", "enum") and not t["fwdref"]:
                self._defs.setdefault(t.get("unique") or t["name"], ti)
        self._anon = {}

    def resolve(self, ti):
        """Forward reference -> its definition (same index when already a definition)."""
        t = self.tpi.get(ti)
        if t and t["kind"] in ("struct", "class", "union", "enum") and t["fwdref"]:
            return self._defs.get(t.get("unique") or t["name"], ti)
        return ti

    def tag(self, ti):
        """C tag name for an aggregate, inventing one for anonymous types."""
        ti = self.resolve(ti)
        t = self.tpi[ti]
        name = t["name"]
        if not name or name.startswith("<unnamed") or name.startswith("__unnamed") or "<" in name:
            name = self._anon.setdefault(ti, f"__anon_{ti:x}")
        return name.replace("::", "__")

    def keyword(self, ti):
        k = self.tpi[self.resolve(ti)]["kind"]
        return {"struct": "struct", "class": "struct", "union": "union", "enum": "enum"}[k]

    def size(self, ti):
        if ti < 0x1000:
            if (ti >> 8) & 0xF:
                return 4
            return _BASIC_SIZE.get(ti & 0xFF, 0)
        t = self.tpi[self.resolve(ti)]
        k = t["kind"]
        if k in ("struct", "class", "union"):
            return t["size"]
        if k == "enum":
            return self.size(t["utype"])
        if k == "pointer":
            return 4
        if k == "modifier":
            return self.size(t["type"])
        if k == "array":
            return t["size"]
        if k == "bitfield":
            return self.size(t["type"])
        return 0

    def base(self, ti):
        """Type name with no declarator (for aggregates and basics)."""
        if ti < 0x1000:
            mode, basic = (ti >> 8) & 0xF, ti & 0xFF
            name = _BASIC.get(basic, f"__basic_{basic:x}")
            return name + (" *" if mode else "")
        t = self.tpi[self.resolve(ti)]
        if t["kind"] in ("struct", "class", "union", "enum"):
            return f"{self.keyword(ti)} {self.tag(ti)}"
        raise ValueError(f"not a base type: {ti:#x} {t['kind']}")

    def decl(self, ti, name=""):
        """Full C declaration of `name` with type `ti` (inside-out declarator construction)."""
        inner = name
        while True:
            if ti < 0x1000:
                mode, basic = (ti >> 8) & 0xF, ti & 0xFF
                base = _BASIC.get(basic, f"__basic_{basic:x}")
                if mode:
                    inner = f"*{inner}"
                return f"{base} {inner}".rstrip() if inner else base
            t = self.tpi[self.resolve(ti)]
            k = t["kind"]
            if k in ("struct", "class", "union", "enum"):
                b = f"{self.keyword(ti)} {self.tag(ti)}"
                return f"{b} {inner}".rstrip() if inner else b
            if k == "modifier":
                q = ("const " if t["const"] else "") + ("volatile " if t["volatile"] else "")
                inner_t = t["type"]
                if inner_t < 0x1000 or self.tpi[self.resolve(inner_t)]["kind"] in (
                        "struct", "class", "union", "enum"):
                    return f"{q}{self.decl(inner_t, inner)}"
                inner = f"{q}{inner}"
                ti = inner_t
            elif k == "pointer":
                q = " const" if t["const"] else ""
                inner = f"*{q}{' ' if q and inner else ''}{inner}"
                ti = t["type"]
            elif k == "array":
                esize = self.size(t["type"]) or 1
                n = t["size"] // esize
                if inner.startswith("*"):
                    inner = f"({inner})"
                inner = f"{inner}[{n if n else ''}]"
                ti = t["type"]
            elif k in ("procedure", "mfunction"):
                if inner.startswith("*"):
                    inner = f"({CALL_CONV.get(t['call'], '')} {inner})"
                else:
                    inner = f"{CALL_CONV.get(t['call'], '')} {inner}"
                inner = f"{inner}({self.params(t)})"
                ti = t["ret"]
            elif k == "bitfield":
                return f"{self.decl(t['type'], inner)} : {t['length']}"
            else:
                return f"/* {k} */ void {inner}"

    def params(self, proc, names=None):
        args = self.tpi[proc["args"]]["args"]
        if not args:
            return "void"
        if args == [0]:
            return ""  # C has no "(...)": an empty list leaves the arguments unspecified
        out = []
        for i, a in enumerate(args):
            if a == 0:  # trailing varargs marker
                out.append("...")
                continue
            out.append(self.decl(a, names[i] if names and i < len(names) else ""))
        return ", ".join(out)

    def prototype(self, ti, name, param_names=None):
        t = self.tpi[ti]
        conv = CALL_CONV.get(t["call"], "")
        return self.decl(t["ret"], f"{conv} {name}({self.params(t, param_names)})")
