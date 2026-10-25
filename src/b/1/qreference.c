/* b/1/qreference.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/1/qreference.c:35  [anchor-callee]
struct QReference_s *__cdecl QReference_NewFn(
        void *pxObject,
        struct QReferenceList_s *ptQReferenceList,
        struct MemPool_s *ptMemPool)
{
  struct QReference_s *result; // eax

  if ( ptMemPool )
  {
    if ( ptMemPool->nAllocatedBlocks == ptMemPool->nBlocks )
      MemPool_ReAlloc(ptMemPool, ptMemPool->nReAllocBlocks);
    ++ptMemPool->nAllocatedBlocks;
    result = (struct QReference_s *)ptMemPool->tMemPoolFreeList.ptHead;
    ptMemPool->tMemPoolFreeList.ptHead = (struct MemPoolFreeItem_s *)result->ptNext;
  }
  else
  {
    result = (struct QReference_s *)Mem_AllocFn(12, 4);
  }
  result->ptPrev = nullptr;
  result->ptNext = nullptr;
  if ( ptQReferenceList )
    result = (struct QReference_s *)List_AddTail(result, (int)ptQReferenceList);
  result->pxObject = pxObject;
  return result;
}

// source: b/1/qreference.c:64  [anchor-callee]
void __cdecl QReference_Delete(struct QReference_s *ptQReference, struct MemPool_s *ptMemPool)
{
  int v3; // esi

  if ( ptQReference->ptNext )
    ptQReference = (struct QReference_s *)Node_Remove(ptQReference);
  if ( ptMemPool )
  {
    --ptMemPool->nAllocatedBlocks;
    ptQReference->ptNext = (struct QReference_s *)ptMemPool->tMemPoolFreeList.ptHead;
    ptMemPool->tMemPoolFreeList.ptHead = (struct MemPoolFreeItem_s *)ptQReference;
  }
  else
  {
    v3 = *(_DWORD *)((unsigned int)&ptQReference[-1].pxObject & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v3);
    memset(*(void **)(v3 + 8), 0xCDu, *(_DWORD *)(v3 + 16));
    free((void *)v3);
  }
}

// source: b/1/qreference.c:92  [size]
void __cdecl QReference_DeleteSafe(struct QReference_s **pptQReference, struct MemPool_s *ptMemPool)
{
  if ( *pptQReference )
  {
    QReference_Delete(*pptQReference, ptMemPool);
    *pptQReference = nullptr;
  }
}

// source: b/1/qreference.c:110  [size]
struct QReference_s *__cdecl QReference_Invalidate(struct QReference_s *ptQReference)
{
  ptQReference->pxObject = nullptr;
  return ptQReference;
}

// source: b/1/qreference.c:125  [anchor-mhash]
struct QReferenceList_s *__cdecl QReference_InvalidateListAndMove(
        struct QReferenceList_s *ptQReferenceList,
        struct QReferenceList_s *ptMoveToQReferenceList)
{
  struct QReferenceList_s *result; // eax
  struct QReferenceList_s *ptHead; // esi
  _DWORD *v4; // eax

  result = (struct QReferenceList_s *)ptQReferenceList->ptHead;
  ptHead = (struct QReferenceList_s *)result->ptHead;
  if ( result->ptHead )
  {
    do
    {
      v4 = Node_Remove(result);
      List_AddTail(v4, (int)ptMoveToQReferenceList)[2] = 0;
      result = ptHead;
      ptHead = (struct QReferenceList_s *)ptHead->ptHead;
    }
    while ( ptHead );
  }
  return result;
}

// source: b/1/qreference.c:149  [anchor-mhash]
struct QReference_s *__cdecl QReference_SetObject(
        struct QReference_s *ptQReference,
        void *pxObject,
        struct QReferenceList_s *ptQReferenceList)
{
  if ( ptQReference->ptNext )
    ptQReference = (struct QReference_s *)Node_Remove(ptQReference);
  ptQReference->pxObject = pxObject;
  if ( ptQReferenceList )
    return (struct QReference_s *)List_AddTail(ptQReference, (int)ptQReferenceList);
  return ptQReference;
}
