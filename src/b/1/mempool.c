/* b/1/mempool.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/1/mempool.c:98  [anchor-callee]
void *__cdecl MemPool_ReAlloc(struct MemPool_s *ptMemPool, unsigned int nBlocks)
{
  struct MemPoolSegment_s *v2; // edi
  int v3; // eax
  unsigned int v4; // ecx
  struct MemPoolFreeItem_s *v5; // eax

  v2 = (struct MemPoolSegment_s *)Mem_AllocFn(12, 4);
  v3 = nBlocks * ptMemPool->nBlockSize;
  v2->nByteSize = v3;
  v2->pxData = Mem_AllocFn(v3, ptMemPool->nAlignment);
  v2->ptNext = ptMemPool->tMemPoolSegmentList.ptHead;
  ptMemPool->nBlocks += nBlocks;
  v4 = 0;
  for ( ptMemPool->tMemPoolSegmentList.ptHead = v2; v4 < nBlocks; ptMemPool->tMemPoolFreeList.ptHead = v5 )
  {
    v5 = (struct MemPoolFreeItem_s *)((char *)v2->pxData + v4 * ptMemPool->nBlockSize);
    ++v4;
    v5->ptNext = ptMemPool->tMemPoolFreeList.ptHead;
  }
  return ptMemPool->tMemPoolFreeList.ptHead;
}

// source: b/1/mempool.c:143  [anchor-mhash]
unsigned int __cdecl MemPool_Init(
        struct MemPool_s *ptMemPool,
        unsigned int nBlockSize,
        unsigned int nBlocks,
        unsigned int nReAllocBlocks,
        unsigned int nAlignment)
{
  unsigned int v5; // edx
  unsigned int result; // eax

  if ( nAlignment < 4 )
    nAlignment = 4;
  if ( nBlockSize <= 4 )
    nBlockSize = 4;
  ptMemPool->nAlignment = nAlignment;
  v5 = ~(nAlignment - 1) & (nBlockSize + nAlignment - 1);
  result = nReAllocBlocks;
  ptMemPool->nBlocks = 0;
  ptMemPool->nAllocatedBlocks = 0;
  ptMemPool->nBlockSize = v5;
  ptMemPool->nReAllocBlocks = nReAllocBlocks;
  ptMemPool->tMemPoolFreeList.ptHead = nullptr;
  ptMemPool->tMemPoolSegmentList.ptHead = nullptr;
  if ( nBlocks )
    return (unsigned int)MemPool_ReAlloc(ptMemPool, nBlocks);
  return result;
}

// source: b/1/mempool.c:174  [anchor-callee]
void __cdecl MemPool_DeInit(struct MemPool_s *ptMemPool)
{
  struct MemPool_s *v1; // eax
  struct MemPoolSegment_s *ptHead; // esi
  void *pxData; // eax
  struct MemPoolSegment_s *ptNext; // ebp
  int v5; // ebx
  int v6; // eax
  int v7; // esi

  v1 = ptMemPool;
  ptHead = ptMemPool->tMemPoolSegmentList.ptHead;
  if ( ptHead )
  {
    do
    {
      pxData = ptHead->pxData;
      ptNext = ptHead->ptNext;
      if ( pxData )
      {
        --Mem_nCurrentAllocations;
        v5 = *(_DWORD *)(((int)pxData - 4) & 0xFFFFFFFC);
        Node_Remove((_DWORD **)v5);
        memset(*(void **)(v5 + 8), 0xCDu, *(_DWORD *)(v5 + 16));
        free((void *)v5);
      }
      v6 = Mem_nCurrentAllocations;
      ptHead->pxData = nullptr;
      v7 = *(_DWORD *)((unsigned int)&ptHead[-1].nByteSize & 0xFFFFFFFC);
      Mem_nCurrentAllocations = v6 - 1;
      Node_Remove((_DWORD **)v7);
      memset(*(void **)(v7 + 8), 0xCDu, *(_DWORD *)(v7 + 16));
      free((void *)v7);
      ptHead = ptNext;
    }
    while ( ptNext );
    v1 = ptMemPool;
  }
  v1->tMemPoolSegmentList.ptHead = nullptr;
}

// source: b/1/mempool.c:202  [anchor-hash]
struct MemPool_s *__cdecl MemPool_FreeAllAndDeInit(struct MemPool_s *ptMemPool)
{
  struct MemPool_s *result; // eax

  ptMemPool->nAllocatedBlocks = 0;
  MemPool_DeInit(ptMemPool);
  return result;
}

// source: b/1/mempool.c:220  [anchor-hash]
void *__cdecl MemPool_Alloc(struct MemPool_s *ptMemPool)
{
  void *result; // eax

  if ( ptMemPool->nAllocatedBlocks == ptMemPool->nBlocks )
    MemPool_ReAlloc(ptMemPool, ptMemPool->nReAllocBlocks);
  ++ptMemPool->nAllocatedBlocks;
  result = ptMemPool->tMemPoolFreeList.ptHead;
  ptMemPool->tMemPoolFreeList.ptHead = *(struct MemPoolFreeItem_s **)result;
  return result;
}

// source: b/1/mempool.c:246  [size]
struct MemPool_s *__cdecl MemPool_Free(struct MemPool_s *ptMemPool, void *pxBlock)
{
  --ptMemPool->nAllocatedBlocks;
  *(_DWORD *)pxBlock = ptMemPool->tMemPoolFreeList.ptHead;
  ptMemPool->tMemPoolFreeList.ptHead = (struct MemPoolFreeItem_s *)pxBlock;
  return ptMemPool;
}

// source: b/1/mempool.c:274  [size]
unsigned int __cdecl MemPool_GetFreeBlocks(struct MemPool_s *ptMemPool)
{
  return ptMemPool->nBlocks - ptMemPool->nAllocatedBlocks;
}

// source: b/1/mempool.c:289  [size]
void __cdecl MemPool_Open()
{
  ;
}

// source: b/1/mempool.c:301  [size]
void __cdecl MemPool_Close()
{
  ;
}

_DWORD *__cdecl List_AddTail(_DWORD *result, int a2)
{
  result[1] = *(_DWORD *)(a2 + 8);
  *result = a2 + 4;
  **(_DWORD **)(a2 + 8) = result;
  *(_DWORD *)(a2 + 8) = result;
  return result;
}

_DWORD *__cdecl List_AddHead(_DWORD *result, int a2)
{
  *result = *(_DWORD *)a2;
  result[1] = a2;
  *(_DWORD *)(*(_DWORD *)a2 + 4) = result;
  *(_DWORD *)a2 = result;
  return result;
}

_DWORD *__cdecl List_RemHead(int a1, _DWORD **a2)
{
  _DWORD *result; // eax
  _DWORD *v3; // ecx

  result = *a2;
  if ( *a2 == a2 + 1 )
    return nullptr;
  v3 = (_DWORD *)*result;
  *a2 = (_DWORD *)*result;
  v3[1] = a2;
  result[1] = 0;
  *result = 0;
  return result;
}

_DWORD **__cdecl Node_Remove(_DWORD **result)
{
  *result[1] = *result;
  (*result)[1] = result[1];
  result[1] = nullptr;
  *result = nullptr;
  return result;
}

_DWORD *__cdecl Node_InsertBefore(_DWORD *result, int a2)
{
  **(_DWORD **)(a2 + 4) = result;
  result[1] = *(_DWORD *)(a2 + 4);
  *(_DWORD *)(a2 + 4) = result;
  *result = a2;
  return result;
}

_DWORD *__cdecl Node_InsertAfter(_DWORD *result, int a2)
{
  *(_DWORD *)(*(_DWORD *)a2 + 4) = result;
  *result = *(_DWORD *)a2;
  *(_DWORD *)a2 = result;
  result[1] = a2;
  return result;
}

int __cdecl List_Length(_DWORD **this)
{
  _DWORD *v1; // ecx
  int result; // eax

  v1 = (_DWORD *)**this;
  for ( result = 0; v1; ++result )
    v1 = (_DWORD *)*v1;
  return result;
}
