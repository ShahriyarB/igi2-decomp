"""MSF 7.00 container: the multi-stream file a PDB is stored in."""
import struct

MAGIC = b"Microsoft C/C++ MSF 7.00\r\n\x1aDS\0\0\0"


class Msf:
    def __init__(self, path):
        self.path = str(path)
        with open(path, "rb") as f:
            self._data = f.read()
        if not self._data.startswith(MAGIC):
            raise ValueError(f"{path}: not an MSF 7.00 file")
        bs, _fpm, _nblocks, dir_bytes, _unknown, dir_map = struct.unpack_from("<6I", self._data, 32)
        self.block_size = bs
        dir_blocks = struct.unpack_from(f"<{self._nb(dir_bytes)}I", self._data, dir_map * bs)
        directory = self._gather(dir_blocks, dir_bytes)
        count = struct.unpack_from("<I", directory)[0]
        self._sizes = struct.unpack_from(f"<{count}I", directory, 4)
        self._blocks = []
        off = 4 + 4 * count
        for size in self._sizes:
            if size == 0xFFFFFFFF:
                self._blocks.append(())
                continue
            n = self._nb(size)
            self._blocks.append(struct.unpack_from(f"<{n}I", directory, off))
            off += 4 * n
        self._cache = {}

    def _nb(self, size):
        return (size + self.block_size - 1) // self.block_size

    def _gather(self, blocks, size):
        bs = self.block_size
        return b"".join(self._data[b * bs:(b + 1) * bs] for b in blocks)[:size]

    @property
    def stream_count(self):
        return len(self._sizes)

    def stream(self, index):
        """Bytes of stream `index`; empty for missing (0xFFFF) or nil streams."""
        if index == 0xFFFF or index >= len(self._sizes) or self._sizes[index] == 0xFFFFFFFF:
            return b""
        if index not in self._cache:
            self._cache[index] = self._gather(self._blocks[index], self._sizes[index])
        return self._cache[index]
