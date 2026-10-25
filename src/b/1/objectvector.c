/* b/1/objectvector.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/1/objectvector.c:39  [anchor-callee]
struct QObjectVector_s *__cdecl QObjectVector_RemoveElement(
        struct QObjectVector_s *ptQObjectVector,
        unsigned int iElement)
{
  unsigned int v2; // ebx
  unsigned int v3; // edi
  unsigned int v4; // esi
  unsigned int v5; // edx
  char *v6; // ebp
  unsigned int v7; // ecx
  unsigned int v8; // [esp+10h] [ebp-8h]

  v2 = iElement;
  if ( ptQObjectVector->isStrictOrder )
  {
    v3 = ptQObjectVector->nAllocated - iElement - 1;
    v4 = iElement + 1;
  }
  else
  {
    v4 = ptQObjectVector->nAllocated - 1;
    v3 = 1;
  }
  v5 = iElement;
  v6 = (char *)ptQObjectVector->papxElement[iElement];
  v7 = 0;
  if ( v3 )
  {
    v8 = v4;
    while ( 1 )
    {
      ptQObjectVector->papxElement[v5] = ptQObjectVector->papxElement[v8];
      *(_DWORD *)((char *)ptQObjectVector->papxElement[v5] + ptQObjectVector->nElementSize - 4) = v7 + v2;
      ++v7;
      ++v5;
      ++v8;
      if ( v7 >= v3 )
        break;
      v2 = iElement;
    }
  }
  ptQObjectVector->papxElement[ptQObjectVector->nAllocated - 1] = v6;
  *(_DWORD *)&v6[ptQObjectVector->nElementSize - 4] = --ptQObjectVector->nAllocated;
  return ptQObjectVector;
}

// source: b/1/objectvector.c:89  [anchor-callee]
void __cdecl QObjectVector_Realloc(struct QObjectVector_s *ptQObjectVector, unsigned int nReallocSize)
{
  unsigned int v3; // ebx
  void **v4; // eax
  void **papxElement; // esi
  void **v6; // edx
  void **v7; // eax
  int v8; // esi
  unsigned int nSize; // edi
  struct MemPoolFreeItem_s *ptHead; // eax
  unsigned int nNewSize; // [esp+10h] [ebp-4h]
  struct QObjectVector_s *ptQObjectVectora = *(struct QObjectVector_s * *)&ptQObjectVector; // [esp+18h] [ebp+4h] ARGSLOT

  v3 = nReallocSize + ptQObjectVector->nSize;
  nNewSize = v3;
  v4 = (void **)Mem_AllocFn(4 * v3, 4);
  papxElement = ptQObjectVector->papxElement;
  v6 = v4;
  ptQObjectVectora = (struct QObjectVector_s *)v4;
  if ( papxElement )
  {
    qmemcpy(v4, papxElement, 4 * ptQObjectVector->nSize);
    v7 = ptQObjectVector->papxElement;
    if ( v7 )
    {
      v8 = *(_DWORD *)((unsigned int)(v7 - 1) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v8);
      memset(*(void **)(v8 + 8), 0xCDu, *(_DWORD *)(v8 + 16));
      free((void *)v8);
      v6 = (void **)ptQObjectVectora;
    }
    ptQObjectVector->papxElement = nullptr;
  }
  nSize = ptQObjectVector->nSize;
  for ( ptQObjectVector->papxElement = v6; nSize < v3; ++nSize )
  {
    if ( ptQObjectVector->tMemPool.nAllocatedBlocks == ptQObjectVector->tMemPool.nBlocks )
    {
      MemPool_ReAlloc(&ptQObjectVector->tMemPool, ptQObjectVector->tMemPool.nReAllocBlocks);
      v3 = nNewSize;
      v6 = (void **)ptQObjectVectora;
    }
    ptHead = ptQObjectVector->tMemPool.tMemPoolFreeList.ptHead;
    ++ptQObjectVector->tMemPool.nAllocatedBlocks;
    ptQObjectVector->tMemPool.tMemPoolFreeList.ptHead = ptHead->ptNext;
    v6[nSize] = ptHead;
    *(struct MemPoolFreeItem_s **)((char *)&ptHead[-1].ptNext + ptQObjectVector->nElementSize) = (struct MemPoolFreeItem_s *)nSize;
  }
  ptQObjectVector->nSize = v3;
}

// source: b/1/objectvector.c:143  [anchor-mhash]
struct QObjectVector_s *__cdecl QObjectVector_New(
        unsigned int nElementSize,
        unsigned int nElementAlignment,
        unsigned int nInitialSize,
        unsigned int nReallocSize,
        enum bool isStrictOrder)
{
  unsigned int v6; // ecx
  unsigned int v7; // eax
  unsigned int v8; // edi
  struct QObjectVector_s *v9; // esi
  unsigned int v10; // eax

  v6 = nElementAlignment;
  if ( nElementAlignment > 4 )
  {
    v7 = nElementAlignment;
  }
  else
  {
    v6 = 4;
    v7 = 4;
  }
  v8 = ~(v7 - 1) & (v6 + nElementSize + 3);
  v9 = (struct QObjectVector_s *)Mem_AllocFn(52, 4);
  v9->isStrictOrder = isStrictOrder;
  v9->nSize = 0;
  v9->nAllocated = 0;
  v9->nReallocSize = nReallocSize;
  v9->papxElement = nullptr;
  v9->nElementSize = v8;
  v10 = nElementAlignment;
  if ( nElementAlignment < 4 )
    v10 = 4;
  if ( v8 <= 4 )
    v8 = 4;
  v9->tMemPool.nAlignment = v10;
  v9->tMemPool.nReAllocBlocks = nReallocSize;
  v9->tMemPool.nBlocks = 0;
  v9->tMemPool.nAllocatedBlocks = 0;
  v9->tMemPool.nBlockSize = ~(v10 - 1) & (v8 + v10 - 1);
  v9->tMemPool.tMemPoolFreeList.ptHead = nullptr;
  v9->tMemPool.tMemPoolSegmentList.ptHead = nullptr;
  if ( nInitialSize )
  {
    MemPool_ReAlloc(&v9->tMemPool, nInitialSize);
    QObjectVector_Realloc(v9, nInitialSize);
  }
  return v9;
}

// source: b/1/objectvector.c:172  [anchor-hash]
void __cdecl QObjectVector_Delete(struct QObjectVector_s *ptQObjectVector)
{
  void **papxElement; // eax
  int v3; // esi
  int v4; // esi

  ptQObjectVector->tMemPool.nAllocatedBlocks = 0;
  MemPool_DeInit(&ptQObjectVector->tMemPool);
  papxElement = ptQObjectVector->papxElement;
  if ( papxElement )
  {
    v3 = *(_DWORD *)((unsigned int)(papxElement - 1) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v3);
    memset(*(void **)(v3 + 8), 0xCDu, *(_DWORD *)(v3 + 16));
    free((void *)v3);
    ptQObjectVector->papxElement = nullptr;
  }
  v4 = *(_DWORD *)((unsigned int)&ptQObjectVector[-1].papxElement & 0xFFFFFFFC);
  --Mem_nCurrentAllocations;
  Node_Remove((_DWORD **)v4);
  memset(*(void **)(v4 + 8), 0xCDu, *(_DWORD *)(v4 + 16));
  free((void *)v4);
}

// source: b/1/objectvector.c:191  [anchor-hash]
void *__cdecl QObjectVector_NewElement(struct QObjectVector_s *ptQObjectVector)
{
  unsigned int nAllocated; // ecx
  void *result; // eax

  if ( ptQObjectVector->nAllocated == ptQObjectVector->nSize )
    QObjectVector_Realloc(ptQObjectVector, ptQObjectVector->nReallocSize);
  nAllocated = ptQObjectVector->nAllocated;
  result = ptQObjectVector->papxElement[nAllocated];
  ptQObjectVector->nAllocated = nAllocated + 1;
  return result;
}

// source: b/1/objectvector.c:209  [size]
unsigned int __cdecl QObjectVector_GetElementIndex(
        struct QObjectVector_s *ptQObjectVector,
        void *pxElement)
{
  return *(_DWORD *)((char *)pxElement + ptQObjectVector->nElementSize - 4);
}

// source: b/1/objectvector.c:230  [size]
struct QObjectVector_s *__cdecl QObjectVector_DeleteElement(
        struct QObjectVector_s *ptQObjectVector,
        void *pxElement)
{
  return QObjectVector_RemoveElement(
           ptQObjectVector,
           *(_DWORD *)((char *)pxElement + ptQObjectVector->nElementSize - 4));
}

// source: b/1/objectvector.c:246  [size]
unsigned int __cdecl QObjectVector_DeleteElementByIndex(
        struct QObjectVector_s *ptQObjectVector,
        unsigned int iElement)
{
  return (unsigned int)QObjectVector_RemoveElement(ptQObjectVector, iElement);
}

// source: b/1/objectvector.c:262  [size]
void *__cdecl QObjectVector_GetElement(
        struct QObjectVector_s *ptQObjectVector,
        unsigned int iElement)
{
  return ptQObjectVector->papxElement[iElement];
}

// source: b/1/objectvector.c:278  [size]
unsigned int __cdecl QObjectVector_GetSize(struct QObjectVector_s *ptQObjectVector)
{
  return ptQObjectVector->nAllocated;
}

// source: b/1/objectvector.c:295  [anchor-mhash]
void __cdecl QObjectVector_Map(
        struct QObjectVector_s *ptQObjectVector,
        void (__cdecl *pfElementCallback)(void *, void *),
        void *pxContext)
{
  unsigned int nAllocated; // edi
  unsigned int i; // esi

  nAllocated = ptQObjectVector->nAllocated;
  for ( i = 0; i < nAllocated; ++i )
    pfElementCallback(ptQObjectVector->papxElement[i], pxContext);
}

// source: b/1/objectvector.c:318  [size]
struct QObjectVector_s *__cdecl QObjectVector_Empty(struct QObjectVector_s *ptQObjectVector)
{
  ptQObjectVector->nAllocated = 0;
  return ptQObjectVector;
}

// source: b/1/objectvector.c:332  [size]
void __cdecl QObjectVector_QSort(
        struct QObjectVector_s *ptObjectVector,
        int (__cdecl *pfQSortCallback)(void **, void **))
{
  unsigned int nAllocated; // eax

  nAllocated = ptObjectVector->nAllocated;
  if ( nAllocated )
    qsort(ptObjectVector->papxElement, nAllocated, 4, pfQSortCallback);
}
