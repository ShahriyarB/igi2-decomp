"""Decompile the retail IDB into src/<original path>.c, laid out like the original source tree.

Matched functions go to the file and line order the Final client PDB gives them. Retail functions
with no match go to the file of the matched function right before them (link order follows
object order). CRT and C++ library code is left out: it is linked from today's runtime.

Hand fixes in overrides/<function>.c replace the decompiled body of that function.

Decompiling is the slow part, so the work is sharded: pipeline.py runs N copies of this script,
each on its own copy of the IDB, and merges their build/export/*.json.

usage: python tools/export.py --idb <copy.i64> --shard K --of N   (system Python with idapro)
outputs: src/**.c, build/export/status_K.json, build/export/protos_K.json
"""
import bisect
import collections
import hashlib
import json
import re
import sys
import time
from pathlib import Path

import idapro

REPO = Path(__file__).resolve().parent.parent
LIBRARY_LIBS = {"libc.lib", "libcp.lib"}


def arg(flag, default=None):
    return sys.argv[sys.argv.index(flag) + 1] if flag in sys.argv else default


IDB = Path(arg("--idb", REPO / "work" / "retail" / "igi2_1.0.exe.i64"))
SHARD, SHARDS = int(arg("--shard", 0)), int(arg("--of", 1))

t0 = time.time()
if idapro.open_database(str(IDB), run_auto_analysis=False):
    raise SystemExit(f"could not open {IDB}")

import ida_funcs  # noqa: E402
import ida_hexrays  # noqa: E402
import ida_lines  # noqa: E402
import ida_name  # noqa: E402
import ida_typeinf  # noqa: E402
import idautils  # noqa: E402
import idc  # noqa: E402

ida_hexrays.init_hexrays_plugin()

cl = json.loads((REPO / "symbols" / "final.json").read_text())
m = json.loads((REPO / "symbols" / "match.json").read_text())
by_rva = {str(f["rva"]): f for f in cl["functions"] if f["rva"] is not None}

# ea -> (file, line, library?)
placed = {}
for rva, v in m.items():
    if v["ea"] is None:
        continue
    f = by_rva[rva]
    # C++ (the stackwalk crash reporter, the DirectX version check) is not C: left out like a library
    lib = v["lib"] in LIBRARY_LIBS or "::" in v["name"] or (f["file"] or "").endswith(".cpp")
    placed[v["ea"]] = (f["file"] or f"_objects/{v['obj'].rsplit('.', 1)[0]}.c", f["line_first"] or 0, lib)

SYSTEM_IDENTS = set(json.loads((REPO / "build" / "system_idents.json").read_text()))
starts = sorted(placed)
plan = collections.defaultdict(list)  # file -> [(line, order, ea)]
for ea in idautils.Functions():
    fn = ida_funcs.get_func(ea)
    if fn.flags & ida_funcs.FUNC_LIB:
        continue
    if fn.flags & ida_funcs.FUNC_THUNK and ida_name.get_name(ea).lstrip("_j") in SYSTEM_IDENTS:
        continue  # a jump to an imported function: the system headers declare it
    if ea in placed:
        file, line, lib = placed[ea]
        if not lib:
            plan[file].append((line, 0, ea))
        continue
    k = bisect.bisect_left(starts, ea) - 1
    if k < 0:
        continue
    if ea % 16:
        continue  # every game function of the Final build is 16-byte aligned: this is junk IDA made
    file, line, lib = placed[starts[k]]
    if not lib:  # else: inside the library tail
        plan[file].append((line, ea - starts[k], ea))  # right after its predecessor

# balance shards by function count: biggest files first, each to the lightest shard
loads = [0] * SHARDS
mine = []
for file, items in sorted(plan.items(), key=lambda kv: (-len(kv[1]), kv[0])):
    k = loads.index(min(loads))
    loads[k] += len(items)
    if k == SHARD:
        mine.append(file)

DUMMY_NAME = re.compile(r"^(byte|word|dword|qword|xmmword|tbyte|flt|dbl|unk|off|stru|asc|algn|loc|sub)_[0-9A-F]+$")
IDA_BACK = {"enum igi_bool": "enum bool", "igi_false": "false", "igi_true": "true"}


def to_c(text):
    for theirs, ours in IDA_BACK.items():
        text = re.sub(r"\b" + re.escape(theirs) + r"\b", ours, text)
    return text


class CastCalls(ida_hexrays.ctree_visitor_t):
    """Calls through a typed function pointer: the ones the decompiler had to cast (it found a
    different number of stack arguments than the pointer's type has), and the ones whose type
    matched (a COM method on a typed vtable, Direct3D_SetMode's GetAdapterCount) but whose pop
    auto-analysis may still have guessed as nothing. The callee type is the pointer's own."""
    def __init__(self):
        super().__init__(ida_hexrays.CV_FAST)
        self.calls = []

    def visit_expr(self, e):
        if e.op != ida_hexrays.cot_call or e.x.op == ida_hexrays.cot_obj:
            return 0
        if e.x.op == ida_hexrays.cot_cast:
            t = e.x.x.type
        elif e.x.op in (ida_hexrays.cot_memptr, ida_hexrays.cot_memref):
            t = e.x.type  # a typed member (a COM vtable's method): a declared type
        else:
            # "(*(T **)(*a3 + 44))(...)": a type the decompiler made up from the stack as IDA
            # has it, so it would only confirm a wrong guess (sub_5C5600's Lock got six
            # arguments, and its locked pointer came from a stack array)
            return 0
        if t.is_ptr() and t.get_pointed_object().is_func():
            self.calls.append((e.ea, t.get_pointed_object()))
        return 0


class NanConstants(ida_hexrays.ctree_visitor_t):
    """The decompiler prints any float constant whose bits are a NaN as "NAN"; the program stored
    exact bits (Terrain_TraceLinesHandler1's grid step is the int -1, 0xFFFFFFFF), and C's NAN
    is 0x7FC00000: the step became two billion and the walk never met its end cell. The bits
    come from the constant itself: IDA keeps it as eight little-endian words, the last one sign
    and exponent, the ones before it the mantissa from its top (explicit leading bit first)."""
    def __init__(self):
        super().__init__(ida_hexrays.CV_FAST)
        self.bits = []

    def visit_expr(self, e):
        if e.op == ida_hexrays.cot_fnum and "NAN" in ida_lines.tag_remove(e.print1(None)):
            import struct
            w = struct.unpack("<8H", bytes(e.fpc.fnum.bytes)[:16])
            sign = w[7] >> 15
            mantissa = (w[6] << 48) | (w[5] << 32) | (w[4] << 16) | w[3]
            if e.fpc.nbytes == 4:
                self.bits.append(("FLOAT", (sign << 31) | (0xFF << 23) | ((mantissa >> 40) & 0x7FFFFF), 8))
            elif e.fpc.nbytes == 8:
                self.bits.append(("DOUBLE", (sign << 63) | (0x7FF << 52) | ((mantissa >> 11) & ((1 << 52) - 1)), 16))
            else:
                self.bits.append(None)
        return 0


TAIL_EVENT_CALL = re.compile(
    r"\(\((?P<ret>[\w ]+?) \(__cdecl \*\)\(struct QTask_s \*\)\)(?P<fn>QTask_aatQTaskFinalEvent\[[^;]*?\]\.pfHandler)\)\((?P<arg>[^;]*?)\);")


def tail_call_arguments(ea, cf, text):
    """A handler that forwards an event by a tail jump overwrites its first argument with the
    new target and jumps: the callee also gets the rest of the caller's arguments
    (MagicObjContainer_GetShadowInfoHandler hands pxContext on to the model). The decompiler
    shows only the replaced one, so the model's handler read a stack slot as its context and
    wrote the shadow distance over a return address. Give the call the caller's other
    parameters, as the jump did."""
    pfn = ida_funcs.get_func(ea)
    tail = any(idc.print_insn_mnem(i) == "jmp" and idc.get_operand_type(i, 0) in (idc.o_mem, idc.o_displ, idc.o_phrase, idc.o_reg)
               and not (pfn.start_ea <= idc.get_operand_value(i, 0) < pfn.end_ea and idc.get_operand_type(i, 0) == idc.o_mem)
               for i in idautils.FuncItems(ea))
    if not tail:
        return text
    # the jump passes the caller's stack arguments on, in their order; register ones stay behind
    # (QTask_TriggerBaseHandler takes the type in ax and the event in dx)
    stack = sorted((lv.location.stkoff(), lv.name) for lv in cf.get_lvars()
                   if lv.is_arg_var and lv.location.is_stkoff())
    params = [name for _, name in stack]
    if not params:
        return text
    # nothing replaced: the base handler gets exactly the caller's arguments
    # ("((void (*)(void))QTask_aatQTaskFinalEvent[...].pfHandler)();" in QTask_TriggerBaseHandler)
    text = re.sub(r"\(\(void \(\*\)\(void\)\)(QTask_aatQTaskFinalEvent\[[^;]*?\]\.pfHandler)\)\(\);",
                  lambda m: f"((void (__cdecl *)()){m.group(1)})({', '.join(params)});", text)
    if len(params) < 2:
        return text
    rest = ", ".join(params[1:])
    text = TAIL_EVENT_CALL.sub(
        lambda m: f"(({m.group('ret')} (__cdecl *)(struct QTask_s *, ...)){m.group('fn')})({m.group('arg')}, {rest});", text)
    # the same through a local the handler was loaded into first (AnimBlender_RegisterHandler:
    # "pfHandler = (void (__cdecl *)(int))QTask_aatQTaskFinalEvent[...].pfHandler; pfHandler(v3);")
    for var, args in set(re.findall(r"\b(\w+) = \(\w[\w ]*? \(__cdecl \*\)\(([^()]*)\)\)QTask_aatQTaskFinalEvent\[", text)):
        if "," in args:
            continue  # it already takes more than the target
        text = re.sub(rf"\b{var} = \((\w[\w ]*?) \(__cdecl \*\)\({re.escape(args)}\)\)QTask_aatQTaskFinalEvent\[",
                      rf"{var} = (\1 (__cdecl *)({args}, ...))QTask_aatQTaskFinalEvent[", text)
        text = re.sub(rf"(\(__cdecl \*{var}\))\({re.escape(args)}\); //", rf"\1({args}, ...); //", text)
        text = re.sub(rf"\b{var}\(([^;(),]+)\);", rf"{var}(\1, {rest});", text)
    return text


def exact_nans(cf, text):
    """Each NAN in order of appearance gets its own bits (see NanConstants)."""
    if "NAN" not in text:
        return text
    v = NanConstants()
    v.apply_to(cf.body, None)
    bits = iter(v.bits)

    def one(m):
        b = next(bits, None)
        if b is None:
            return m.group(0)
        kind, value, digits = b
        return f"IGI2_{kind}_BITS({value:#0{digits + 2}x}u{'ll' if kind == 'DOUBLE' else ''})"
    text = re.sub(r"\bNAN\b", one, text)
    # through a reinterpreting cast the program stored or compared the integer itself
    return re.sub(r"\*\(float \*\)&([\w.\[\]>-]+) (=|==|!=) IGI2_FLOAT_BITS\((0x[0-9a-f]+u)\)",
                  r"*(unsigned int *)&\1 \2 \3", text)


class FloatConstants(ida_hexrays.ctree_visitor_t):
    """printed text -> exact value of every floating constant, None where two values print alike"""

    def __init__(self):
        super().__init__(ida_hexrays.CV_FAST)
        self.values = {}

    def visit_expr(self, e):
        if e.op == ida_hexrays.cot_fnum and not e.fpc.is_nan():
            printed = ida_lines.tag_remove(e.fpc._print())
            try:
                exact = float(str(e.fpc.fnum))
            except ValueError:
                return 0
            if self.values.get(printed, exact) != exact:
                self.values[printed] = None
            else:
                self.values[printed] = exact
        return 0


def exact_float_constants(cf, text):
    """The decompiler prints a constant with about 8 digits: "x - 84.741692" for the float
    84.74169158935547 the code subtracts, and the C double 84.741692 is another number. The
    player's fall speed drifted from the original's every tick in the air (HumanPlayer_InAirControl).
    Each constant whose text does not read back as its value is printed exactly (a float's value
    is a double, so the expression's types stay as they were)."""
    v = FloatConstants()
    v.apply_to(cf.body, None)
    for printed, exact in v.values.items():
        if exact is None or not re.fullmatch(r"-?\d+\.\d+(?:e[-+]?\d+)?", printed):
            continue
        if float(printed) == exact:
            continue
        text = re.sub(rf"(?<![\w.]){re.escape(printed)}(?![\w.])", repr(exact), text)
    return text


SIGNED_OPS = {getattr(ida_hexrays, n) for n in ("cot_sge", "cot_sle", "cot_sgt", "cot_slt", "cot_sdiv", "cot_smod",
                                                   "cot_sshr", "cot_asgsdiv", "cot_asgsmod", "cot_asgsshr")}
SIGNED_NAMES = {1: "__int8", 2: "__int16", 4: "int", 8: "__int64"}
SIGNED_OP_TEXT = ("<=", ">=", "<", ">", "/", "%", ">>", "/=", "%=", ">>=")


class SignedOperands(ida_hexrays.ctree_visitor_t):
    """Operands of signed comparisons, divisions and shifts whose type has no sign (_DWORD,
    _WORD, _BYTE), as printed: {text: size}."""

    def __init__(self):
        super().__init__(ida_hexrays.CV_FAST)
        self.found = {}

    ARITH = {getattr(ida_hexrays, n) for n in ("cot_add", "cot_sub", "cot_mul", "cot_neg", "cot_bnot", "cot_band",
                                                 "cot_bor", "cot_xor", "cot_shl", "cot_sshr", "cot_ushr", "cot_sdiv",
                                                 "cot_udiv", "cot_smod", "cot_umod")}

    @staticmethod
    def unsigned_in_c(e):
        """C computes e unsigned: a sign-less 4/8-byte value (our _DWORD/_QWORD are unsigned) in
        its arithmetic, where the decompiler's type for the whole may say int ("_DWORD - 1")"""
        t = e.type
        if t.is_integral() and t.get_sign() == ida_typeinf.no_sign and t.get_size() >= 4:
            return True
        if e.op in SignedOperands.ARITH:
            return any(SignedOperands.unsigned_in_c(x) for x in (e.x, e.y) if x is not None)
        return False

    def visit_expr(self, e):
        if e.op in SIGNED_OPS:
            for op in (e.x, e.y):
                if op is None or op.op == ida_hexrays.cot_num:
                    continue
                t = op.type
                size = t.get_size()
                if t.is_integral() and size in SIGNED_NAMES and (
                        t.get_sign() == ida_typeinf.no_sign or self.unsigned_in_c(op)):
                    self.found[ida_lines.tag_remove(op.print1(None))] = size
        return 0


def signed_operations(cf, text):
    """"*(_DWORD *)&x - 1 > 0" was a signed compare (jg): the decompiler's _DWORD has no sign,
    ours is unsigned, so C compared unsigned and 0 - 1 passed (Explosion0_CreateExplosion ran its
    fireball loop with no fireball and read a pointer it never set). The tree knows which
    comparisons, divisions and shifts were signed: their sign-less operands get a signed cast."""
    v = SignedOperands()
    v.apply_to(cf.body, None)
    for operand in sorted(v.found, key=len, reverse=True):
        if not operand or "\n" in operand:
            continue
        cast = f"({SIGNED_NAMES[v.found[operand]]})"
        q = re.escape(operand)
        ops = "|".join(re.escape(o) for o in sorted(SIGNED_OP_TEXT, key=len, reverse=True))
        # left of the operator ("x - 1 > 0"), then right of it ("a / x")
        text = re.sub(rf"(?<![\w.\])>])({q})(?= (?:{ops}) )", lambda m: f"{cast}({m.group(1)})", text)
        text = re.sub(rf"(?<= (?:<=|>=|>>|/=|%=)) ({q})(?![\w(\[.])|(?<= [<>/%]) ({q})(?![\w(\[.])",
                      lambda m: f" {cast}({m.group(1) or m.group(2)})", text)
    return text


def import_register_calls(pfn):
    """(call, import type) for each "call esi" whose register holds an import loaded earlier
    ("mov esi, ds:__imp_PeekMessageA"): auto-analysis has such a call pop nothing, so after a
    message loop the stack points came out 0x44 too deep (Direct3D_SetMode then reloaded its
    ptMode from a local)."""
    import ida_nalt
    loaded, out = {}, []
    for item in idautils.FuncItems(pfn.start_ea):
        mnem = idc.print_insn_mnem(item)
        if mnem == "call" and idc.get_operand_type(item, 0) == idc.o_reg:
            target = loaded.get(idc.print_operand(item, 0))
            tif = ida_typeinf.tinfo_t()
            if target is not None and ida_nalt.get_tinfo(tif, target):
                if tif.is_ptr():
                    tif = tif.get_pointed_object()
                if tif.is_func():
                    out.append((item, tif))
        elif mnem == "mov" and idc.get_operand_type(item, 0) == idc.o_reg:
            src = idc.get_operand_value(item, 1)
            if idc.get_operand_type(item, 1) == idc.o_mem and idc.get_segm_name(src) == ".idata":
                loaded[idc.print_operand(item, 0)] = src
            else:
                loaded.pop(idc.print_operand(item, 0), None)
        elif idc.get_operand_type(item, 0) == idc.o_reg:
            loaded.pop(idc.print_operand(item, 0), None)  # the register is written: no longer the import
    return out


def fix_call_purges(cf, ea):
    """Auto-analysis guessed how many bytes each indirect call pops before any types were known
    (a COM method, a QTask handler), and the decompiler hands the arguments out by that stack
    pointer: one wrong guess shifts every later call ("GetAdapterModeCount()" with none,
    "EnumAdapterModes" with six). With the pointer's type known, set the true pop at each."""
    import ida_auto
    import ida_frame

    def mismatched(cfunc):
        """(call, callee type, purge, what IDA has the call pop) for every cast call that disagrees"""
        visitor = CastCalls()
        visitor.apply_to(cfunc.body, None)
        pfn = ida_funcs.get_func(ea)
        out = []
        cast = {c for c, _ in visitor.calls}
        imports = [c for c in import_register_calls(pfn) if c[0] not in cast]
        for call_ea, ftype in visitor.calls + imports:
            if call_ea == idc.BADADDR or idc.print_insn_mnem(call_ea) != "call":
                continue
            if idc.get_operand_type(call_ea, 0) == idc.o_near:
                continue  # a direct call: IDA knows that callee (_CIpow's "stack" args are on the FPU)
            fi = ida_typeinf.func_type_data_t()
            if not ftype.get_func_details(fi):
                continue
            pops = fi.get_cc() in (ida_typeinf.CM_CC_STDCALL, ida_typeinf.CM_CC_THISCALL, ida_typeinf.CM_CC_FASTCALL)
            purge = sum((a.type.get_size() + 3) & ~3 for a in fi if a.argloc.is_stkoff()) if pops else 0
            nxt = idc.next_head(call_ea, pfn.end_ea)
            actual = ida_frame.get_spd(pfn, nxt) - ida_frame.get_spd(pfn, call_ea)
            if actual != purge:
                out.append((call_ea, ftype, purge, actual, nxt))
        # every call with a known type, right or corrected: the block rule is only for the rest
        # (Display_SetMode's GetSystemMetrics through edi had its argument pushed in the block
        # before, and "correcting" it moved the window rectangle by 4: the window went to x=32767)
        typed = {c[0] for c in out} | cast | {c[0] for c in imports}
        out += overpopping_calls(pfn, typed)
        return out

    def overpopping_calls(pfn, typed):
        """Untyped indirect calls IDA has pop more than was pushed in their basic block: no call
        can leave the stack above where its block began (sub_5C5600's Lock popped 24 for its
        20 bytes of arguments, and the locked pointer then came from a stack array). Measured
        from the block start, not the previous call, so arguments pushed before an earlier call
        (the hash-table macros) still count as this call's."""
        import ida_gdl
        out = []
        for block in ida_gdl.FlowChart(pfn):
            base = ida_frame.get_spd(pfn, block.start_ea)
            item = block.start_ea
            while item != idc.BADADDR and item < block.end_ea:
                nxt = idc.next_head(item, pfn.end_ea)
                if (idc.print_insn_mnem(item) == "call" and item not in typed
                        and idc.get_operand_type(item, 0) in (idc.o_reg, idc.o_displ, idc.o_phrase)
                        and nxt != idc.BADADDR):
                    after = ida_frame.get_spd(pfn, nxt)
                    if after > base:  # spd is minus the depth: larger is shallower
                        at = ida_frame.get_spd(pfn, item)
                        out.append((item, None, base - at, after - at, nxt))
                item = nxt
        return out

    calls = mismatched(cf)
    if not calls:
        return 0
    # correct each stack point by hand: giving IDA the callee types and reanalysing neither
    # sticks (Direct3D_SetMode's message loop stayed 0x44 deep) nor keeps the frame in place
    # (Direct3D_EnumDevices). A variable this moves into the argument area is that argument's
    # slot (argument_slot_variables)
    pfn = ida_funcs.get_func(ea)
    import ida_bytes

    def rebalance():
        # auto-analysis balanced its wrong depths where paths meet after code that does not fall
        # through (Direct3D_SetMode's epilogue after "jmp abort" had +0x34): redo those from the
        # corrected predecessors, or they now overshoot ("positive sp value")
        for item in list(idautils.FuncItems(ea)):
            after = idc.next_head(item, pfn.end_ea)
            if after != idc.BADADDR and not ida_bytes.is_flow(ida_bytes.get_flags(after)):
                ida_frame.recalc_spd(item)

    # calls whose decompiled type is wrong and whose IDA figure stands (overrides/purge_keep.json)
    calls = [c for c in calls if c[0] not in PURGE_KEEP]
    if not calls:
        return 0
    for call_ea, ftype, purge, actual, nxt in calls:
        ida_frame.add_user_stkpnt(nxt, ida_frame.get_sp_delta(pfn, nxt) + purge - actual)
    rebalance()
    return len(calls)


def entry_pushed_arguments(ea, cf, text):
    """"push esi; push edi; call Script_New": the function saves esi, then passes its own
    register argument zFile@edi straight on. The decompiler takes every register push at the
    entry for a save and leaves a stack variable at that slot that nothing assigns
    ("Script_New(v3)"). The slot of the k-th entry push is ebp-4k: where an unassigned stack
    variable sits on the slot of a pushed, never popped register that holds a parameter, that
    variable is the parameter."""
    import idautils
    items = sorted(idautils.FuncItems(ea))
    popped = {idc.print_operand(i, 0) for i in items if idc.print_insn_mnem(i) == "pop"}
    pushed, depth = {}, 0  # slot (bytes below the entry) -> register pushed there
    for item in items[:24]:  # up to the first call: pushes and stack adjustments move the slots
        mnem = idc.print_insn_mnem(item)
        if mnem in ("call", "jmp", "retn", "pop") or mnem.startswith("j"):
            break
        if mnem == "push":
            depth += 4
            if idc.get_operand_type(item, 0) == idc.o_reg and idc.print_operand(item, 0) not in popped:
                pushed[depth] = idc.print_operand(item, 0)
        elif mnem == "sub" and idc.print_operand(item, 0) == "esp" and idc.get_operand_type(item, 1) == idc.o_imm:
            depth += idc.get_operand_value(item, 1)
    if not pushed:
        return text
    fi = ida_typeinf.func_type_data_t()
    if not cf.type.get_func_details(fi):
        return text
    by_reg = {}
    for a in fi:
        if a.argloc.is_reg1():
            by_reg[ida_hexrays.get_mreg_name(ida_hexrays.reg2mreg(a.argloc.reg1()), 4)] = a.name
    for var, off in re.findall(r"^  [^/\n]*?\b(\w+); // \[esp[+-][0-9A-F]+h\] \[ebp-([0-9A-F]+)h\]$", text, re.M):
        param = by_reg.get(pushed.get(int(off, 16)))
        if param and not re.search(rf"\b{var}\s*=[^=]", text):
            text = re.sub(rf"^  [^\n]*\b{var}; // [^\n]*\n", "", text, flags=re.M)
            text = re.sub(rf"\b{var}\b", param, text)
    return text


def argument_slot_variables(cf, text):
    """A variable the decompiler placed in the argument area ("v28; // [esp+..] [ebp+4h]") is
    that stack slot: it starts as the incoming argument (Direct3D_SetMode reads ptMode as v28),
    and the compiler may later reuse the slot for something else (Mem_AllocFn keeps the total
    size in nSize's slot while nSize itself lives on in a register). So it is its own local,
    initialized from the argument's bits."""
    lvars = list(cf.get_lvars())
    # the decompiler's own arguments and where they sit; a variable at or above the lowest of
    # them is in the argument area (the sign of its frame offset says nothing: SoundSys keeps
    # the rest of a path buffer at "ebp+0".."ebp+6")
    arg_at = {lv.location.stkoff(): lv.name for lv in lvars if lv.is_arg_var and lv.location.is_stkoff()}
    if not arg_at:
        return text
    lowest = min(arg_at)
    for lv in lvars:
        if lv.is_arg_var or not lv.location.is_stkoff() or lv.location.stkoff() < lowest or not lv.name:
            continue
        m = re.search(rf"^  (?P<type>[^/\n]*?[\w\*\s]){lv.name}(?P<dims>(?:\[\d+\])*); // (?P<rest>[^\n]*)$", text, re.M)
        if not m:
            continue
        line, ctype, param = m.group(0), m.group("type").strip(), arg_at.get(lv.location.stkoff())
        if param and not m.group("dims") and "(" not in ctype:
            new = line.replace(f"{lv.name};", f"{lv.name} = *({ctype} *)&{param};", 1)
        else:
            new = line  # an array or an offset between arguments: keep, but not in the local frame
        text = text.replace(line, new + " ARGSLOT", 1)
    return text


def plain_prototype(ea):
    """The function's declaration as plain C: register arguments become ordinary ones."""
    decl = ida_typeinf.print_type(ea, ida_typeinf.PRTYPE_1LINE | ida_typeinf.PRTYPE_SEMI)
    if not decl:
        return None
    decl = re.sub(r"@<[^>]+>", "", decl)
    decl = decl.replace("__usercall", "__cdecl").replace("__userpurge", "__stdcall")
    return to_c(decl)


# call sites where the stack point IDA computed stands, against the decompiled callee type
PURGE_KEEP = {int(k, 16) for k in json.loads((REPO / "overrides" / "purge_keep.json").read_text())}

CACHE = REPO / "build" / "decomp_cache"
# off unless asked for (IGI2_DECOMP_CACHE=1): a fingerprint that misses one input serves text
# decompiled against an older IDB, and that cost more than the export time it saved
USE_CACHE = __import__("os").environ.get("IGI2_DECOMP_CACHE") == "1"


def local_types_digest():
    """Every local type as the IDB holds it: a struct that changes changes every function using it."""
    h = hashlib.sha1()
    til = ida_typeinf.get_idati()
    for ordinal in range(1, ida_typeinf.get_ordinal_limit(til)):
        tif = ida_typeinf.tinfo_t()
        if tif.get_numbered_type(til, ordinal):
            h.update(f"{ordinal}:{tif.get_type_name()}:".encode())
            h.update((tif._print(None, ida_typeinf.PRTYPE_DEF | ida_typeinf.PRTYPE_MULTI) or "").encode())
    return h.hexdigest()


# what every function's output also depends on: this script and the type library
GLOBAL_KEY = hashlib.sha1(Path(__file__).read_bytes() + local_types_digest().encode()).hexdigest()


def fingerprint(ea):
    """Everything the decompiler (and this script's fixes) read for one function: its bytes,
    item flags (operand forms), stack points, frame, type and comments, and the name, type and
    flags of everything it refers to. Equal fingerprints decompile to equal text.
    Also returns what it refers to, for undo_type_propagation."""
    import ida_bytes
    import ida_frame
    import ida_nalt
    pfn = ida_funcs.get_func(ea)
    h = hashlib.sha1(GLOBAL_KEY.encode())
    refs = {}

    def add(*parts):
        h.update(repr(parts).encode())

    add(ida_name.get_name(ea), pfn.flags, pfn.frsize, pfn.frregs, pfn.argsize,
        ida_typeinf.print_type(ea, ida_typeinf.PRTYPE_1LINE), idc.get_func_cmt(ea, 0), idc.get_func_cmt(ea, 1))
    for chunk in idautils.Chunks(ea):
        add("chunk", *chunk)
    frame = ida_typeinf.tinfo_t()
    if ida_frame.get_func_frame(frame, pfn):
        add("frame", frame._print(None, ida_typeinf.PRTYPE_MULTI))
    seen = set()
    for item in idautils.FuncItems(ea):
        size = ida_bytes.get_item_size(item)
        add(item, ida_bytes.get_bytes(item, size), ida_bytes.get_flags(item), ida_frame.get_sp_delta(pfn, item),
            idc.get_cmt(item, 0))
        for target in list(idautils.CodeRefsFrom(item, False)) + list(idautils.DataRefsFrom(item)):
            if target in seen:
                continue
            seen.add(target)
            tif = ida_typeinf.tinfo_t()
            callee = ida_funcs.get_func(target)
            typed = ida_nalt.get_tinfo(tif, target)
            refs[target] = tif if typed else None
            add("ref", target, ida_name.get_name(target), ida_bytes.get_flags(target),
                ida_typeinf.print_tinfo("", 0, 0, ida_typeinf.PRTYPE_1LINE, tif, "", "") if typed else None,
                callee.flags if callee and callee.start_ea == target else None)
            # a reference into an item prints as the item's name plus an offset: that name and
            # type are part of the text too (sanitize renumbers g_pxContext_N between runs)
            head = ida_bytes.get_item_head(target)
            if head != target:
                head_tif = ida_typeinf.tinfo_t()
                add("head", head, ida_name.get_name(head), ida_bytes.get_flags(head), ida_bytes.get_item_size(head),
                    ida_typeinf.print_tinfo("", 0, 0, ida_typeinf.PRTYPE_1LINE, head_tif, "", "")
                    if ida_nalt.get_tinfo(head_tif, head) else None)
    return h.hexdigest(), refs


def undo_type_propagation(refs):
    """Decompiling a function stores the types it deduces on the globals it touches
    ("dword_73D218 = pfPrint" makes dword_73D218 a function pointer), and every function
    decompiled after it in this shard would print differently: output would depend on order,
    sharding and the cache. Put each referenced item's type back as the applied IDB had it
    (export_data.py declares the globals from that IDB too)."""
    import ida_nalt
    for target, before in refs.items():
        now = ida_typeinf.tinfo_t()
        has = ida_nalt.get_tinfo(now, target)
        if before is None:
            if has:
                ida_nalt.del_tinfo(target)
        elif not has or not now.equals_to(before):
            ida_nalt.set_tinfo(target, before)


GENERATED_NAME = re.compile(r"\b(g_\w+|(?:byte|word|dword|qword|unk|off|stru|flt|dbl|asc)_[0-9A-F]{6,8})\b")


def cache_get(key):
    if not USE_CACHE:
        return None
    try:
        hit = json.loads((CACHE / key[:2] / f"{key}.json").read_text())
    except (OSError, ValueError):
        return None
    # a name that has since become a global's or a function's would now clash: decompile anew
    if any(ida_name.get_name_ea(idc.BADADDR, n) != idc.BADADDR for n in hit.get("lvars", [])):
        return None
    # a global the text names must still be called that: sanitize numbers g_pxContext_N anew
    # each run, and a reference the fingerprint saw at another address keeps the old name
    for n in set(GENERATED_NAME.findall(hit.get("text", ""))):
        if ida_name.get_name_ea(idc.BADADDR, n) == idc.BADADDR:
            return None
    return hit


def cache_put(key, value):
    if not USE_CACHE:
        return
    path = CACHE / key[:2] / f"{key}.json"
    path.parent.mkdir(parents=True, exist_ok=True)
    tmp = path.with_suffix(f".{SHARD}.tmp")
    tmp.write_text(json.dumps(value))
    tmp.replace(path)


status, protos, types, lvars = {}, {}, {}, set()
hits = 0
for file in sorted(mine):
    out = [f"/* {file} -- decompiled from the retail exe; do not edit (see overrides/). */",
           '#include "igi2.h"', ""]
    for _, _, ea in sorted(plan[file]):
        name = ida_name.get_name(ea)
        override = REPO / "overrides" / f"{name}.c"
        if override.exists():
            body = override.read_text()
            out.append(body.rstrip() + "\n")
            status[name] = {"ea": ea, "file": file, "state": "override"}
            sig = []  # the override's own signature declares it
            for line in body.splitlines():
                if line.startswith("{"):
                    break
                if not line.startswith("//") and line.strip():
                    sig.append(line.strip())
            if sig:
                protos[name] = " ".join(sig) + ";"
            elif (p := plain_prototype(ea)):
                protos[name] = p
            continue
        key, refs = fingerprint(ea)
        hit = cache_get(key)
        if hit:
            hits += 1
            status[name] = {"ea": ea, "file": file, "state": hit["state"], **({"error": hit["error"]} if "error" in hit else {})}
            if hit.get("type"):
                types[ea] = hit["type"]
            lvars.update(hit.get("lvars", []))
            if hit.get("proto"):
                protos[name] = hit["proto"]
            out.append(hit["text"].rstrip() + "\n")
            continue
        try:
            hf = ida_hexrays.hexrays_failure_t()
            cf = ida_hexrays.decompile_func(ida_funcs.get_func(ea), hf, ida_hexrays.DECOMP_NO_CACHE)
            if cf is None:
                raise ida_hexrays.DecompilationFailure(f"{hf.errea:#x}: {hf.desc()}")
            for _ in range(3):  # a corrected call can expose the next one
                if not fix_call_purges(cf, ea):
                    break
                cf = ida_hexrays.decompile(ea, flags=ida_hexrays.DECOMP_NO_CACHE) or cf
            # Globals are macros (export_data.py) and functions are file-scope names: a local or
            # parameter sharing a name with either would be expanded or would hide it.
            clash = [lv.name for lv in cf.get_lvars()
                     if lv.name and (ida_name.get_name_ea(idc.BADADDR, lv.name) != idc.BADADDR
                                     or DUMMY_NAME.match(lv.name) or not lv.name.isidentifier())]
            if clash:
                for n in clash:  # "28" (a name the decompiler made from a frame offset) is no identifier
                    ida_hexrays.rename_lvar(ea, n, n + "_" if n.isidentifier() else f"a{n}")
                cf = ida_hexrays.decompile(ea, flags=ida_hexrays.DECOMP_NO_CACHE)
            text = signed_operations(cf, exact_float_constants(cf, tail_call_arguments(ea, cf, exact_nans(cf, argument_slot_variables(cf, entry_pushed_arguments(ea, cf, to_c(str(cf))))))))
            status[name] = {"ea": ea, "file": file, "state": "decompiled"}
            types[ea] = ida_typeinf.print_tinfo("", 0, 0, ida_typeinf.PRTYPE_1LINE, cf.type, name, "")
            lvars.update(lv.name for lv in cf.get_lvars() if lv.name)
            # the declaration is the definition's own signature, so the two always agree
            sig = []
            for line in text.splitlines():
                if line.startswith("{"):
                    break
                if not line.startswith("//"):
                    sig.append(line.strip())
            if sig:
                protos[name] = " ".join(sig) + ";"
            cache_put(key, {"state": "decompiled", "text": text, "type": types[ea], "proto": protos.get(name),
                            "lvars": sorted({lv.name for lv in cf.get_lvars() if lv.name})})
        except ida_hexrays.DecompilationFailure as e:
            text = f"/* {name} @ {ea:#x}: decompilation failed: {e} */\n#error decompilation failed: {name}"
            status[name] = {"ea": ea, "file": file, "state": "failed", "error": str(e)}
            if (p := plain_prototype(ea)):
                protos[name] = p
            cache_put(key, {"state": "failed", "error": str(e), "text": text, "proto": protos.get(name)})
        finally:
            undo_type_propagation(refs)
        out.append(text.rstrip() + "\n")
    path = REPO / "src" / file
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text("\n".join(out))

outdir = REPO / "build" / "export"
outdir.mkdir(parents=True, exist_ok=True)
(outdir / f"status_{SHARD}.json").write_text(json.dumps(status))
(outdir / f"protos_{SHARD}.json").write_text(json.dumps(protos))
(outdir / f"types_{SHARD}.json").write_text(json.dumps(types))
(outdir / f"lvars_{SHARD}.json").write_text(json.dumps(sorted(lvars)))
states = collections.Counter(s["state"] for s in status.values())
print(f"shard {SHARD}/{SHARDS}: {len(mine)} files, {len(status)} functions {dict(states)}, "
      f"{hits} from the cache; {time.time() - t0:.0f}s", flush=True)
idapro.close_database(save=False)
