/* Retail fallback: run chosen functions as the original machine code (see include/fallback.h).

   IGI2_FALLBACK selects them, a comma-separated list:
     all                    every function the table has
     Name, Terrain_*        a function, or a glob over names
     file:h/2/terrain.c     every function of source files containing that text
     -<any of the above>    leave these as C (applied after the others, in order)
     @path                  read more entries from a file, one per line
   IGI2_FALLBACK_LOG names a file that receives what was redirected and what could not be.

   Setup, before any game code runs:
   1. the retail code becomes executable, and its import table gets this process's imports;
   2. retail C runtime routines that keep state (heap, files, locale, rand) jump to ours, so the
      retail code and the C share one heap and one set of files;
   3. each chosen C function's entry (hot-patchable: /hotpatch and /FUNCTIONPADMIN:5) jumps to a
      stub that hands its descriptor to the generic adapter, which lays the C function's cdecl
      arguments out the way the retail one takes them (registers, stack offsets) and calls it.
      The result comes back in eax/edx/st0 as it left. Retail code calls retail code directly,
      so a fallback function takes its whole call tree with it, except calls through pointers. */
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#include "fallback.h"

#ifdef IGI2_FALLBACK

#define IMAGE_BASE 0x400000u

static FILE *s_ptLog;

static void Fallback_Log(const char *zFormat, ...)
{
    va_list args;
    if (!s_ptLog)
        return;
    va_start(args, zFormat);
    vfprintf(s_ptLog, zFormat, args);
    va_end(args);
    fflush(s_ptLog);
}

/* ---- the adapter ---------------------------------------------------------------------- */

unsigned int __cdecl Igi2_FallbackStackSize(const Igi2FallbackFunc *ptFunc)
{
    return (ptFunc->nStack + 3u) & ~3u;
}

/* registers: eax ecx edx ebx esi edi, then the retail address */
void __cdecl Igi2_FallbackMarshal(const Igi2FallbackFunc *ptFunc, const unsigned char *pOurs,
                                  unsigned int *anReg, unsigned char *pRetail)
{
    unsigned int i;
    memset(anReg, 0, 7 * sizeof(unsigned int));
    for (i = 0; i < ptFunc->nArgs; ++i) {
        const Igi2FallbackArg *a = &ptFunc->atArg[i];
        if (a->isReg)
            memcpy(&anReg[a->reg], pOurs + a->ours, a->size < 4 ? a->size : 4);
        else
            memcpy(pRetail + a->retail, pOurs + a->ours, (a->size + 3u) & ~3u);
    }
    anReg[6] = ptFunc->retail;
}

/* entered from a stub: [esp] = descriptor, [esp+4] = the C caller's return, [esp+8] = arguments */
__declspec(naked) static void Igi2_FallbackGeneric(void)
{
    __asm {
        push ebp
        mov ebp, esp
        push ebx
        push esi
        push edi
        sub esp, 32                 ; registers at [ebp-44]: eax ecx edx ebx esi edi target
        push dword ptr [ebp+4]
        call Igi2_FallbackStackSize
        add esp, 4
        sub esp, eax                ; the retail call's stack arguments
        mov ecx, esp
        lea edx, [ebp-44]
        lea eax, [ebp+12]
        push ecx
        push edx
        push eax
        push dword ptr [ebp+4]
        call Igi2_FallbackMarshal
        add esp, 16
        mov eax, [ebp-44]
        mov ecx, [ebp-40]
        mov edx, [ebp-36]
        mov ebx, [ebp-32]
        mov esi, [ebp-28]
        mov edi, [ebp-24]
        call dword ptr [ebp-20]
        lea esp, [ebp-12]           ; whether the retail function popped its arguments or not
        pop edi
        pop esi
        pop ebx
        pop ebp
        add esp, 4                  ; the descriptor
        ret
    }
}

/* ---- the reverse adapter: retail code calling a function that stays C ------------------- */

/* bytes of the C function's stack arguments */
unsigned int __cdecl Igi2_FallbackOursSize(const Igi2FallbackFunc *ptFunc)
{
    unsigned int i, n = 0;
    for (i = 0; i < ptFunc->nArgs; ++i) {
        const Igi2FallbackArg *a = &ptFunc->atArg[i];
        unsigned int end = a->ours + ((a->size + 3u) & ~3u);
        if (end > n)
            n = end;
    }
    return n;
}

/* registers as the retail caller left them: eax ecx edx ebx esi edi */
void __cdecl Igi2_FallbackUnmarshal(const Igi2FallbackFunc *ptFunc, const unsigned char *pRetail,
                                    const unsigned int *anReg, unsigned char *pOurs)
{
    unsigned int i;
    for (i = 0; i < ptFunc->nArgs; ++i) {
        const Igi2FallbackArg *a = &ptFunc->atArg[i];
        if (a->isReg)
            *(unsigned int *)(pOurs + a->ours) = anReg[a->reg];
        else
            memcpy(pOurs + a->ours, pRetail + a->retail, (a->size + 3u) & ~3u);
    }
}

/* where the C's result goes, and which caller registers come back: a retail caller may keep a
   value in ecx or edx across a call its callee does not spoil (link-time code generation knew
   each callee), so everything but the result is restored */
#define FALLBACK_OFS_POURS 8
#define FALLBACK_OFS_PURGE 24
#define FALLBACK_OFS_RETURN 26
_Static_assert(offsetof(Igi2FallbackFunc, pOurs) == FALLBACK_OFS_POURS, "descriptor layout");
_Static_assert(offsetof(Igi2FallbackFunc, nPurge) == FALLBACK_OFS_PURGE, "descriptor layout");
_Static_assert(offsetof(Igi2FallbackFunc, eReturn) == FALLBACK_OFS_RETURN, "descriptor layout");

/* entered from a stub: [esp] = descriptor, [esp+4] = the retail caller's return, [esp+8] = its
   stack arguments; the register arguments are in their registers */
__declspec(naked) static void Igi2_FallbackReverse(void)
{
    __asm {
        push ebp
        mov ebp, esp                ; [ebp+4] descriptor, [ebp+8] return, [ebp+12] arguments
        sub esp, 28                 ; [ebp-24..-4]: eax ecx edx ebx esi edi, [ebp-28] exit
        mov [ebp-24], eax
        mov [ebp-20], ecx
        mov [ebp-16], edx
        mov [ebp-12], ebx
        mov [ebp-8], esi
        mov [ebp-4], edi
        push dword ptr [ebp+4]
        call Igi2_FallbackOursSize
        add esp, 4
        sub esp, eax                ; the C call's stack arguments
        mov ecx, esp
        lea edx, [ebp-24]
        lea eax, [ebp+12]
        push ecx
        push edx
        push eax
        push dword ptr [ebp+4]
        call Igi2_FallbackUnmarshal
        add esp, 16
        mov eax, [ebp+4]
        call dword ptr [eax+FALLBACK_OFS_POURS]
        ; the result replaces the saved registers it is returned in
        mov ecx, [ebp+4]
        movzx ecx, byte ptr [ecx+FALLBACK_OFS_RETURN]
        cmp ecx, 1
        jb no_result
        mov [ebp-24], eax
        cmp ecx, 2
        jne no_result
        mov [ebp-16], edx
    no_result:
        ; a retail function that pops its own arguments: the return address moves up past them
        mov ecx, [ebp+4]
        movzx ecx, word ptr [ecx+FALLBACK_OFS_PURGE]
        mov eax, [ebp+8]
        mov [ebp+ecx+8], eax
        lea eax, [ebp+ecx+4]        ; the caller's ebp goes right below it
        mov edx, [ebp]
        mov [eax], edx
        mov [ebp-28], eax
        mov eax, [ebp-24]
        mov ecx, [ebp-20]
        mov edx, [ebp-16]
        mov esp, [ebp-28]
        pop ebp
        ret
    }
}

/* ---- selection ------------------------------------------------------------------------ */

static int Fallback_Glob(const char *zPattern, const char *zText)
{
    if (*zPattern == '*') {
        for (;; ++zText) {
            if (Fallback_Glob(zPattern + 1, zText))
                return 1;
            if (!*zText)
                return 0;
        }
    }
    if (!*zPattern)
        return !*zText;
    return *zPattern == *zText && Fallback_Glob(zPattern + 1, zText + 1);
}

static int Fallback_Matches(const char *zEntry, const Igi2FallbackFunc *ptFunc)
{
    if (!strcmp(zEntry, "all"))
        return 1;
    if (!strncmp(zEntry, "file:", 5))
        return ptFunc->zFile && strstr(ptFunc->zFile, zEntry + 5) != NULL;
    return Fallback_Glob(zEntry, ptFunc->zName);
}

static void Fallback_Apply(const char *zEntry, unsigned char *aisChosen)
{
    char zLine[512];
    unsigned int i;
    int isExclude = 0;
    while (*zEntry == ' ' || *zEntry == '\t')
        ++zEntry;
    if (!*zEntry)
        return;
    if (*zEntry == '@') {
        FILE *f = fopen(zEntry + 1, "r");
        if (!f) {
            Fallback_Log("cannot open %s\n", zEntry + 1);
            return;
        }
        while (fgets(zLine, sizeof zLine, f)) {
            zLine[strcspn(zLine, "\r\n#")] = 0;
            Fallback_Apply(zLine, aisChosen);
        }
        fclose(f);
        return;
    }
    if (*zEntry == '-') {
        isExclude = 1;
        ++zEntry;
    }
    for (i = 0; i < Igi2_nFallbackFunc; ++i)
        if (Fallback_Matches(zEntry, &Igi2_atFallbackFunc[i]))
            aisChosen[i] = (unsigned char)!isExclude;
}

/* ---- setup ---------------------------------------------------------------------------- */

static const IMAGE_NT_HEADERS32 *Fallback_Headers(void)
{
    const IMAGE_DOS_HEADER *dos = (const IMAGE_DOS_HEADER *)IMAGE_BASE;
    return (const IMAGE_NT_HEADERS32 *)(IMAGE_BASE + dos->e_lfanew);
}

static void Fallback_MakeRetailCodeRunnable(void)
{
    const IMAGE_NT_HEADERS32 *nt = Fallback_Headers();
    const IMAGE_SECTION_HEADER *s = IMAGE_FIRST_SECTION(nt);
    unsigned int i;
    DWORD old;
    for (i = 0; i < nt->FileHeader.NumberOfSections; ++i, ++s)
        if (s->Characteristics & IMAGE_SCN_MEM_EXECUTE)
            VirtualProtect((void *)(IMAGE_BASE + s->VirtualAddress), s->Misc.VirtualSize,
                           PAGE_EXECUTE_READWRITE, &old);
}

static void Fallback_ResolveRetailImports(void)
{
    const IMAGE_NT_HEADERS32 *nt = Fallback_Headers();
    const IMAGE_DATA_DIRECTORY *dir = &nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
    const IMAGE_IMPORT_DESCRIPTOR *d = (const IMAGE_IMPORT_DESCRIPTOR *)(IMAGE_BASE + dir->VirtualAddress);
    unsigned int nResolved = 0, nMissing = 0;
    if (!dir->VirtualAddress)
        return;
    for (; d->Name; ++d) {
        const char *zDll = (const char *)(IMAGE_BASE + d->Name);
        HMODULE h = LoadLibraryA(zDll);
        const DWORD *pName = (const DWORD *)(IMAGE_BASE + (d->OriginalFirstThunk ? d->OriginalFirstThunk : d->FirstThunk));
        DWORD *pSlot = (DWORD *)(IMAGE_BASE + d->FirstThunk);
        for (; *pName; ++pName, ++pSlot) {
            FARPROC p = NULL;
            if (h)
                p = (*pName & IMAGE_ORDINAL_FLAG32)
                    ? GetProcAddress(h, (LPCSTR)(UINT_PTR)(*pName & 0xFFFF))
                    : GetProcAddress(h, ((const IMAGE_IMPORT_BY_NAME *)(IMAGE_BASE + *pName))->Name);
            if (p) {
                *pSlot = (DWORD)(UINT_PTR)p;
                ++nResolved;
            } else {
                ++nMissing;
                Fallback_Log("import not found: %s!%s\n", zDll, (*pName & IMAGE_ORDINAL_FLAG32)
                             ? "(ordinal)" : ((const IMAGE_IMPORT_BY_NAME *)(IMAGE_BASE + *pName))->Name);
            }
        }
    }
    Fallback_Log("retail imports: %u resolved, %u missing\n", nResolved, nMissing);
}

static void Fallback_WriteJump(unsigned char *pAt, const void *pTo)
{
    pAt[0] = 0xE9;
    *(int *)(pAt + 1) = (int)((const unsigned char *)pTo - (pAt + 5));
}

static void Fallback_RedirectRetailRuntime(void)
{
    unsigned int i;
    for (i = 0; i < Igi2_nFallbackCrt; ++i)
        Fallback_WriteJump((unsigned char *)(UINT_PTR)Igi2_atFallbackCrt[i].retail, Igi2_atFallbackCrt[i].pOurs);
    Fallback_Log("retail runtime routines sent to ours: %u\n", Igi2_nFallbackCrt);
}

/* what the hooks overwrote, per table index, so a switch (Igi2_FallbackSwitch) can undo them */
static unsigned char (*s_aSavedOurs)[7];
static unsigned char (*s_aSavedRetail)[5];
static unsigned char *s_aisChosen;
static unsigned char *s_pReverseStubs;   /* 16 bytes per table index */

/* the C function's entry: "jmp short -7" onto a "jmp stub" in the padding before it */
static int Fallback_Hook(const Igi2FallbackFunc *ptFunc, unsigned char *pStub)
{
    unsigned char *pEntry = (unsigned char *)ptFunc->pOurs;
    DWORD old;
    int i;
    for (i = 1; i <= 5; ++i)
        if (pEntry[-i] != 0xCC && pEntry[-i] != 0x90)
            return 0;  /* no hot-patch padding: built without /FUNCTIONPADMIN */
    if (s_aSavedOurs)
        memcpy(s_aSavedOurs[ptFunc - Igi2_atFallbackFunc], pEntry - 5, 7);
    pStub[0] = 0x68;  /* push descriptor */
    *(const Igi2FallbackFunc **)(pStub + 1) = ptFunc;
    Fallback_WriteJump(pStub + 5, Igi2_FallbackGeneric);
    if (!VirtualProtect(pEntry - 5, 7, PAGE_EXECUTE_READWRITE, &old))
        return 0;
    Fallback_WriteJump(pEntry - 5, pStub);
    pEntry[0] = 0xEB;
    pEntry[1] = 0xF9;
    VirtualProtect(pEntry - 5, 7, old, &old);
    FlushInstructionCache(GetCurrentProcess(), pEntry - 5, 7);
    return 1;
}

/* functions retail cannot run against today's runtime (see Igi2_azFallbackPinned): never
   chosen, so their retail entries go to the C too (Fallback_ReverseUnchosen) */
static void Fallback_PinToC(unsigned char *aisChosen)
{
    unsigned int i, k;
    /* a replay (support/replay.c) drives each frame from App_Run: that one stays C */
    const char *zReplay = getenv("IGI2_REPLAY");
    if (zReplay && *zReplay)
        for (i = 0; i < Igi2_nFallbackFunc; ++i)
            if (!strcmp(Igi2_atFallbackFunc[i].zName, "App_Run"))
                aisChosen[i] = 0;
    for (k = 0; Igi2_azFallbackPinned[k]; ++k) {
        for (i = 0; i < Igi2_nFallbackFunc; ++i) {
            if (strcmp(Igi2_atFallbackFunc[i].zName, Igi2_azFallbackPinned[k]))
                continue;
            aisChosen[i] = 0;
            Fallback_Log("pinned to C: %s\n", Igi2_atFallbackFunc[i].zName);
        }
    }
}

/* the retail entry of a function that stays C: "jmp stub", the stub "push descriptor; jmp
   Igi2_FallbackReverse". Game functions are 16-byte aligned, so the 5 bytes fit before the next */
static int Fallback_Reverse(unsigned int i)
{
    const Igi2FallbackFunc *ptFunc = &Igi2_atFallbackFunc[i];
    unsigned char *pStub = s_pReverseStubs + i * 16;
    if (ptFunc->retail & 15)
        return 0;
    memcpy(s_aSavedRetail[i], (void *)(UINT_PTR)ptFunc->retail, 5);
    pStub[0] = 0x68;
    *(const Igi2FallbackFunc **)(pStub + 1) = ptFunc;
    Fallback_WriteJump(pStub + 5, Igi2_FallbackReverse);
    Fallback_WriteJump((unsigned char *)(UINT_PTR)ptFunc->retail, pStub);
    return 1;
}

static void Fallback_ReverseUnchosen(const unsigned char *aisChosen)
{
    unsigned int i, nReversed = 0, nUnchosen = 0;
    for (i = 0; i < Igi2_nFallbackFunc; ++i) {
        if (aisChosen[i])
            continue;
        ++nUnchosen;
        if (Fallback_Reverse(i))
            ++nReversed;
        else
            Fallback_Log("not reversible (unaligned): %s\n", Igi2_atFallbackFunc[i].zName);
    }
    FlushInstructionCache(GetCurrentProcess(), NULL, 0);
    Fallback_Log("retail entries sent to the C: %u of %u not chosen\n", nReversed, nUnchosen);
}

/* Mid-run: the functions IGI2_FALLBACK_LATER selects (same syntax) become C from now on. A
   replay starts every function as retail, so loading never runs mixed, and switches at a frame
   it names (support/replay.c): from there on the two runs differ only in those functions. */
void __cdecl Igi2_FallbackSwitch(void)
{
    const char *zLater = getenv("IGI2_FALLBACK_LATER");
    unsigned char *aisToC;
    char *zCopy, *zEntry, *zNext;
    unsigned int i, nSwitched = 0;
    if (!s_aisChosen || !zLater || !*zLater)
        return;
    aisToC = calloc(Igi2_nFallbackFunc, 1);
    zCopy = _strdup(zLater);
    for (zEntry = zCopy; zEntry; zEntry = zNext) {
        zNext = strpbrk(zEntry, ",;");
        if (zNext)
            *zNext++ = 0;
        Fallback_Apply(zEntry, aisToC);
    }
    free(zCopy);
    for (i = 0; i < Igi2_nFallbackFunc; ++i) {
        unsigned char *pEntry = (unsigned char *)Igi2_atFallbackFunc[i].pOurs;
        DWORD old;
        if (!aisToC[i] || !s_aisChosen[i])
            continue;
        if (VirtualProtect(pEntry - 5, 7, PAGE_EXECUTE_READWRITE, &old)) {
            memcpy(pEntry - 5, s_aSavedOurs[i], 7);   /* the C entry runs the C again */
            VirtualProtect(pEntry - 5, 7, old, &old);
        }
        if (Fallback_Reverse(i)) {                     /* and retail callers reach it too */
            s_aisChosen[i] = 0;
            ++nSwitched;
        }
    }
    free(aisToC);
    FlushInstructionCache(GetCurrentProcess(), NULL, 0);
    Fallback_Log("switched to C: %u\n", nSwitched);
}

static void __cdecl Igi2_InitFallback(void)
{
    const char *zSelection = getenv("IGI2_FALLBACK");
    const char *zLog = getenv("IGI2_FALLBACK_LOG");
    unsigned char *aisChosen, *pStubs;
    char *zCopy, *zEntry, *zNext;
    unsigned int i, nChosen = 0, nHooked = 0;
    if (!zSelection || !*zSelection)
        return;
    if (zLog && *zLog)
        s_ptLog = fopen(zLog, "w");
    Fallback_Log("IGI2_FALLBACK=%s\n", zSelection);

    Fallback_MakeRetailCodeRunnable();
    Fallback_ResolveRetailImports();
    Fallback_RedirectRetailRuntime();

    aisChosen = calloc(Igi2_nFallbackFunc, 1);
    s_aisChosen = aisChosen;
    s_aSavedOurs = calloc(Igi2_nFallbackFunc, sizeof *s_aSavedOurs);
    s_aSavedRetail = calloc(Igi2_nFallbackFunc, sizeof *s_aSavedRetail);
    s_pReverseStubs = VirtualAlloc(NULL, Igi2_nFallbackFunc * 16, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    zCopy = _strdup(zSelection);
    for (zEntry = zCopy; zEntry; zEntry = zNext) {
        zNext = strpbrk(zEntry, ",;");
        if (zNext)
            *zNext++ = 0;
        Fallback_Apply(zEntry, aisChosen);
    }
    free(zCopy);

    Fallback_PinToC(aisChosen);
    for (i = 0; i < Igi2_nFallbackFunc; ++i)
        nChosen += aisChosen[i];
    pStubs = VirtualAlloc(NULL, nChosen * 16 + 16, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    for (i = 0; i < Igi2_nFallbackFunc && pStubs; ++i) {
        if (!aisChosen[i])
            continue;
        if (Fallback_Hook(&Igi2_atFallbackFunc[i], pStubs + nHooked * 16)) {
            ++nHooked;
            Fallback_Log("retail: %s\n", Igi2_atFallbackFunc[i].zName);
        } else {
            Fallback_Log("not hookable: %s\n", Igi2_atFallbackFunc[i].zName);
        }
    }
    Fallback_Log("functions sent to retail: %u of %u chosen (table %u)\n", nHooked, nChosen, Igi2_nFallbackFunc);
    Fallback_ReverseUnchosen(aisChosen);   /* aisChosen stays: Igi2_FallbackSwitch updates it */
}

/* after the image is in place (data_init.c's initializer is in .CRT$XCU, this sorts after it) */
#pragma section(".CRT$XCV", read)
__declspec(allocate(".CRT$XCV")) static void (__cdecl *const kInitFallback)(void) = Igi2_InitFallback;

#endif
