"""Shared CodeView decoding helpers: numeric leaves and strings."""
import struct

_NUMERIC = {
    0x8000: ("<b", 1), 0x8001: ("<h", 2), 0x8002: ("<H", 2), 0x8003: ("<i", 4),
    0x8004: ("<I", 4), 0x8005: ("<f", 4), 0x8006: ("<d", 8), 0x8009: ("<q", 8),
    0x800A: ("<Q", 8),
}


def numeric(buf, pos):
    """Decode a CodeView numeric leaf at `pos`; returns (value, new_pos)."""
    leaf = struct.unpack_from("<H", buf, pos)[0]
    if leaf < 0x8000:
        return leaf, pos + 2
    if leaf in _NUMERIC:
        fmt, size = _NUMERIC[leaf]
        return struct.unpack_from(fmt, buf, pos + 2)[0], pos + 2 + size
    if leaf == 0x8010:  # LF_VARSTRING
        n = struct.unpack_from("<H", buf, pos + 2)[0]
        return buf[pos + 4:pos + 4 + n].decode("latin1"), pos + 4 + n
    raise ValueError(f"unsupported numeric leaf {leaf:#x} at {pos:#x}")


def cstr(buf, pos):
    """Zero-terminated string at `pos`; returns (text, new_pos)."""
    end = buf.index(b"\0", pos)
    return buf[pos:end].decode("latin1"), end + 1


def skip_pad(buf, pos, end):
    """Field lists pad sub-records with LF_PAD bytes (0xF0..0xFF)."""
    while pos < end and buf[pos] >= 0xF0:
        pos += buf[pos] & 0x0F
    return pos
