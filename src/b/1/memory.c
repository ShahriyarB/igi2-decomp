/* b/1/memory.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/1/memory.c:226  [anchor-caller]
void __cdecl Mem_ParseBreakOnAlloc(char *zArg)
{
  int v1; // ecx

  Mem_nBreakOnAlloc = String_GetInteger(v1, (int)zArg);
  Mem_isBreakOnAlloc = true;
}

// source: b/1/memory.c:423  [size]
void __cdecl Mem_PrintLog()
{
  ;
}

// source: b/1/memory.c:474  [anchor-strings]
void *__cdecl Mem_AllocFn(int nSize, int nAlignment)
{
  size_t v4; // ebx
  _DWORD *v5; // eax
  _DWORD *v6; // esi
  struct MemHeader_s *ptHead; // ecx
  struct MemHeader_s *ptNext; // eax
  int i; // edx
  int nAllocated; // edi
  int v11; // ebp
  void *v12; // ebx
  bool v13; // zf
  int nSizea = *(int *)&nSize; // [esp+14h] [ebp+4h] ARGSLOT

  v4 = nAlignment + nSize + 28;
  ++Mem_nCurrentAllocations;
  nSizea = v4;
  v5 = malloc(v4);
  v6 = v5;
  if ( !v5 )
  {
    ptHead = Mem_sMemList.ptHead;
    ptNext = Mem_sMemList.ptHead->ptNext;
    for ( i = 0; ptNext; v6 = (_DWORD *)((char *)v6 + v11) )
    {
      nAllocated = ptHead->nAllocated;
      v11 = ptHead->nSize;
      ptHead = ptNext;
      ptNext = ptNext->ptNext;
      i += nAllocated;
    }
    LDebug_Error(
      "Mem_Alloc() failed to allocate %d bytes.\r\nTotal allocated by user: %d.\r\nTotal by Mem_Alloc():%d.",
      v4,
      v6,
      i);
    abort();
  }
  v12 = (void *)(~(nAlignment - 1) & ((unsigned int)v5 + nAlignment + 27));
  *(_DWORD *)(((int)v12 - 4) & 0xFFFFFFFC) = v5;
  v13 = Mem_isInitialised == 0;
  v5[1] = 0;
  *v5 = 0;
  if ( v13 )
    Mem_Open();
  List_AddTail(v6, (int)&Mem_sMemList);
  v6[3] = nSizea;
  v6[4] = nSize;
  v6[2] = v12;
  memset(v12, 0xABu, nSize);
  return v12;
}

// source: b/1/memory.c:614  [anchor-callee]
void __cdecl Mem_DeAllocFn(void *pxMem)
{
  int v1; // esi

  if ( pxMem )
  {
    v1 = *(_DWORD *)(((int)pxMem - 4) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
}

// source: b/1/memory.c:795  [size]
void __cdecl Mem_EnableAllocation()
{
  ;
}

// source: b/1/memory.c:810  [size]
void __cdecl Mem_DisableAllocation()
{
  ;
}

// source: b/1/memory.c:825  [size]
void __cdecl Mem_PushAllocationState(enum bool isAllocationEnabled)
{
  ;
}

// source: b/1/memory.c:844  [size]
void __cdecl Mem_PopAllocationState()
{
  ;
}

// source: b/1/memory.c:862  [size]
enum bool __cdecl Mem_AllocationEnabled()
{
  return true;
}

// source: b/1/memory.c:946  [anchor-hash]
void __cdecl Mem_Open()
{
  Mem_sMemList.ptHead = (struct MemHeader_s *)&Mem_sMemList.ptMiddle;
  Mem_sMemList.ptTail = (struct MemHeader_s *)&Mem_sMemList;
  Mem_sMemList.ptMiddle = nullptr;
  Mem_isInitialised = 1;
  Memory_nStackPtr = 16;
  AppMain_FindPrefix(AppContext_tAppContext.zCmdLine, "BreakOnAllocID:", Mem_ParseBreakOnAlloc);
}

// source: b/1/memory.c:966  [anchor-hash]
void __cdecl Mem_Close()
{
  struct MemHeader_s *ptHead; // eax
  struct MemHeader_s *i; // ebp
  void *pxMem; // eax
  int v3; // esi

  ptHead = Mem_sMemList.ptHead;
  for ( i = Mem_sMemList.ptHead->ptNext; i; i = i->ptNext )
  {
    pxMem = ptHead->pxMem;
    if ( pxMem )
    {
      v3 = *(_DWORD *)(((int)pxMem - 4) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v3);
      memset(*(void **)(v3 + 8), 0xCDu, *(_DWORD *)(v3 + 16));
      free((void *)v3);
    }
    ptHead = i;
  }
  Mem_isInitialised = 0;
}
