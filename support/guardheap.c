/* A debugging allocator for the game's own malloc/realloc/free (build with -DIGI2_GUARD_HEAP=ON).

   Every block ends exactly where an inaccessible page begins, so the first byte written past
   the end of an allocation faults at the instruction that writes it, instead of corrupting the
   heap for some later free to trip over. Blocks come from one large reservation and are never
   reused (freed pages become inaccessible too, which also catches use after free). Each block
   costs at least two pages, so the reservation runs out after some 100,000 allocations: later
   blocks come unguarded from the process heap. */
#include <windows.h>
#include <string.h>

#ifdef IGI2_GUARD_HEAP

#define GUARD_PAGE 4096u
#define GUARD_SPACE (1024u * 1024u * 1024u) /* address space to hand out: 1 GB */

static char *s_base, *s_next, *s_end;

typedef struct { size_t nSize; char *pBase; size_t nCommitted; } GuardHeader;

static void guard_init(void)
{
    size_t space = GUARD_SPACE; /* the largest free run a 32-bit process has, from 1 GB down */
    while (space >= 64u * 1024u * 1024u && !(s_base = VirtualAlloc(NULL, space, MEM_RESERVE, PAGE_NOACCESS)))
        space /= 2;
    s_next = s_base;
    s_end = s_base ? s_base + space : NULL;
}

void *igi2_guard_malloc(size_t n)
{
    size_t data = (n + 3) & ~(size_t)3; /* keep the 4-byte alignment the game expects */
    size_t pages = (data + sizeof(GuardHeader) + GUARD_PAGE - 1) / GUARD_PAGE;
    char *block, *p;
    if (!s_base)
        guard_init();
    if (!s_base || s_next + (pages + 1) * GUARD_PAGE > s_end)
        return HeapAlloc(GetProcessHeap(), 0, n ? n : 1);
    block = s_next;
    s_next += (pages + 1) * GUARD_PAGE; /* the page after the block stays reserved: no access */
    if (!VirtualAlloc(block, pages * GUARD_PAGE, MEM_COMMIT, PAGE_READWRITE))
        return NULL;
    p = block + pages * GUARD_PAGE - data;
    ((GuardHeader *)p)[-1].nSize = n;
    ((GuardHeader *)p)[-1].pBase = block;
    ((GuardHeader *)p)[-1].nCommitted = pages * GUARD_PAGE;
    return p;
}

static int guarded(const void *p)
{
    return (const char *)p >= s_base && (const char *)p < s_end;
}

void igi2_guard_free(void *p)
{
    GuardHeader *h;
    if (!p)
        return;
    if (!guarded(p)) {
        HeapFree(GetProcessHeap(), 0, p);
        return;
    }
    h = (GuardHeader *)p - 1;
    VirtualFree(h->pBase, h->nCommitted, MEM_DECOMMIT); /* a later use faults */
}

void *igi2_guard_realloc(void *p, size_t n)
{
    void *q = igi2_guard_malloc(n);
    if (p && q) {
        size_t old = guarded(p) ? ((GuardHeader *)p - 1)->nSize : HeapSize(GetProcessHeap(), 0, p);
        memcpy(q, p, old < n ? old : n);
        igi2_guard_free(p);
    }
    return q;
}

#endif
