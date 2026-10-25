/* h/1/memref.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/1/memref.c:56  [anchor-callee]
void __cdecl MemRef_ReAlloc(unsigned int nMax)
{
  struct MemoryReference_s *v1; // ebx
  struct MemoryReference_s *v2; // edx
  int v3; // esi

  v1 = (struct MemoryReference_s *)Mem_AllocFn(8 * nMax, 4);
  memset(v1, 0, 4 * ((8 * nMax) >> 2));
  v2 = MemRef_patMemoryReference;
  if ( MemRef_nMemRefsUsed )
  {
    qmemcpy(v1, MemRef_patMemoryReference, 8 * MemRef_nMemRefsUsed);
  }
  else
  {
    v1->pxMemory = nullptr;
    v1->isUsed = false;
    MemRef_nMemRefsUsed = 1;
  }
  if ( v2 )
  {
    v3 = *(_DWORD *)((unsigned int)&v2[-1].isUsed & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v3);
    memset(*(void **)(v3 + 8), 0xCDu, *(_DWORD *)(v3 + 16));
    free((void *)v3);
  }
  MemRef_nMaxMemRefs = nMax;
  MemRef_patMemoryReference = v1;
}

// source: h/1/memref.c:96  [anchor-mhash]
enum bool __cdecl MemRef_IsRegistered(int *piMemRefID, void *pxMemory)
{
  int v2; // eax

  if ( !MemRef_patMemoryReference )
    return false;
  v2 = 1;
  if ( MemRef_nMemRefsUsed <= 1 )
    return false;
  while ( MemRef_patMemoryReference[v2].pxMemory != pxMemory )
  {
    if ( ++v2 >= MemRef_nMemRefsUsed )
      return false;
  }
  if ( piMemRefID )
    *piMemRefID = v2;
  return true;
}

// source: h/1/memref.c:128  [size]
void *__cdecl MemRef_GetMemory(int nMemRefID)
{
  return MemRef_patMemoryReference[nMemRefID].pxMemory;
}

// source: h/1/memref.c:146  [anchor-mhash]
int __cdecl MemRef_Register(void *pxMemory)
{
  int result; // eax
  struct MemoryReference_s *v2; // ecx

  result = MemRef_nMemRefsUsed;
  if ( MemRef_nMemRefsUsed == MemRef_nMaxMemRefs )
  {
    MemRef_ReAlloc(MemRef_nMaxMemRefs + MemRef_nReAllocMemRefs);
    result = MemRef_nMemRefsUsed;
  }
  v2 = MemRef_patMemoryReference;
  MemRef_patMemoryReference[result].pxMemory = pxMemory;
  v2[result].isUsed = true;
  MemRef_nMemRefsUsed = result + 1;
  return result;
}

// source: h/1/memref.c:174  [anchor-hash]
void __cdecl MemRef_Remove(void *pxMemory)
{
  int v1; // eax

  if ( MemRef_patMemoryReference )
  {
    v1 = 1;
    if ( MemRef_nMemRefsUsed > 1 )
    {
      while ( MemRef_patMemoryReference[v1].pxMemory != pxMemory )
      {
        if ( ++v1 >= MemRef_nMemRefsUsed )
          return;
      }
      MemRef_patMemoryReference[v1].isUsed = false;
    }
  }
}

// source: h/1/memref.c:201  [anchor-hash]
void __cdecl MemRef_Init()
{
  if ( MemRef_patMemoryReference )
  {
    while ( MemRef_nMemRefsUsed )
      ;
  }
  MemRef_nMemRefsUsed = 0;
}

// source: h/1/memref.c:224  [anchor-hash]
void __cdecl MemRef_Open()
{
  MemRef_nReAllocMemRefs = 256;
  MemRef_ReAlloc(0x400u);
}

// source: h/1/memref.c:242  [anchor-hash]
void __cdecl MemRef_Close()
{
  int v0; // esi

  if ( MemRef_patMemoryReference )
  {
    v0 = *(_DWORD *)((unsigned int)&MemRef_patMemoryReference[-1].isUsed & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
    MemRef_patMemoryReference = nullptr;
  }
}
