/* b/1/vector.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/1/vector.c:31  [anchor-callee]
void __cdecl QVector_Realloc(struct QVector_s *ptVector, unsigned int nElements)
{
  unsigned int nArraySize; // ebp
  unsigned int v3; // ecx
  void **v4; // ecx
  unsigned int v5; // eax
  void **papxElement; // eax
  int v7; // ebx
  void **papxNewElement; // [esp+4h] [ebp-4h]

  nArraySize = ptVector->tPrivate.nArraySize;
  if ( nArraySize < nElements + ptVector->tPrivate.nElements )
  {
    v3 = ptVector->tPrivate.nElements + nElements;
    do
      nArraySize += ptVector->tPrivate.nReallocSize;
    while ( nArraySize < v3 );
  }
  v4 = (void **)Mem_AllocFn(4 * nArraySize, 4);
  v5 = 0;
  for ( papxNewElement = v4; v5 < ptVector->tPrivate.nElements; ++v5 )
    v4[v5] = ptVector->tPrivate.papxElement[v5];
  papxElement = ptVector->tPrivate.papxElement;
  if ( papxElement && ptVector->tPrivate.isPrivateMem == false )
  {
    --Mem_nCurrentAllocations;
    v7 = *(_DWORD *)((unsigned int)(papxElement - 1) & 0xFFFFFFFC);
    Node_Remove((_DWORD **)v7);
    memset(*(void **)(v7 + 8), 0xCDu, *(_DWORD *)(v7 + 16));
    free((void *)v7);
    v4 = papxNewElement;
    ptVector->tPrivate.papxElement = nullptr;
  }
  ptVector->tPrivate.nArraySize = nArraySize;
  ptVector->tPrivate.papxElement = v4;
  ptVector->tPrivate.isPrivateMem = false;
}

// source: b/1/vector.c:74  [size]
struct QVector_s *__cdecl QVector_Init(
        struct QVector_s *ptVector,
        unsigned int nInitialSize,
        unsigned int nReallocSize,
        void **papxElement,
        enum bool isPrivateMem,
        enum bool isStrictOrder)
{
  ptVector->tPrivate.nArraySize = nInitialSize;
  ptVector->tPrivate.nReallocSize = nReallocSize;
  ptVector->tPrivate.isPrivateMem = isPrivateMem;
  ptVector->tPrivate.nElements = 0;
  ptVector->tPrivate.papxElement = papxElement;
  ptVector->tPrivate.isStrictOrder = isStrictOrder;
  return ptVector;
}

// source: b/1/vector.c:94  [anchor-callee]
struct QVector_s *__cdecl QVector_New(
        unsigned int nInitialSize,
        unsigned int nReallocSize,
        enum bool isStrictOrder)
{
  void **v3; // esi
  struct QVector_s *result; // eax

  v3 = nullptr;
  if ( nInitialSize )
    v3 = (void **)Mem_AllocFn(4 * nInitialSize, 4);
  result = (struct QVector_s *)Mem_AllocFn(24, 4);
  result->tPrivate.papxElement = v3;
  result->tPrivate.nArraySize = nInitialSize;
  result->tPrivate.nReallocSize = nReallocSize;
  result->tPrivate.nElements = 0;
  result->tPrivate.isPrivateMem = false;
  result->tPrivate.isStrictOrder = isStrictOrder;
  return result;
}

// source: b/1/vector.c:120  [anchor-hash]
void __cdecl QVector_Delete(struct QVector_s *ptVector)
{
  void **papxElement; // eax
  int v3; // esi
  int v4; // esi

  if ( ptVector )
  {
    papxElement = ptVector->tPrivate.papxElement;
    if ( papxElement )
    {
      if ( ptVector->tPrivate.isPrivateMem == false )
      {
        v3 = *(_DWORD *)((unsigned int)(papxElement - 1) & 0xFFFFFFFC);
        --Mem_nCurrentAllocations;
        Node_Remove((_DWORD **)v3);
        memset(*(void **)(v3 + 8), 0xCDu, *(_DWORD *)(v3 + 16));
        free((void *)v3);
        ptVector->tPrivate.papxElement = nullptr;
      }
    }
    v4 = *(_DWORD *)((unsigned int)&ptVector[-1].tPrivate.isStrictOrder & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v4);
    memset(*(void **)(v4 + 8), 0xCDu, *(_DWORD *)(v4 + 16));
    free((void *)v4);
  }
}

// source: b/1/vector.c:139  [size]
struct QVector_s *__cdecl QVector_SetElement(
        struct QVector_s *ptVector,
        unsigned int iElement,
        void *pxElement)
{
  void **papxElement; // ecx

  papxElement = ptVector->tPrivate.papxElement;
  papxElement[iElement] = (void *)pxElement;
  return (struct QVector_s *)iElement;
}

// source: b/1/vector.c:157  [anchor-callee]
unsigned int __cdecl QVector_AddElement(struct QVector_s *ptVector, void *pxElement)
{
  unsigned int nElements; // edi

  nElements = ptVector->tPrivate.nElements;
  if ( ptVector->tPrivate.nElements == ptVector->tPrivate.nArraySize )
    QVector_Realloc(ptVector, 1u);
  if ( nElements < ptVector->tPrivate.nElements - 1 )
    memmove(
      &ptVector->tPrivate.papxElement[nElements + 1],
      &ptVector->tPrivate.papxElement[nElements],
      4 * (ptVector->tPrivate.nElements - nElements));
  ++ptVector->tPrivate.nElements;
  ptVector->tPrivate.papxElement[nElements] = (void *)pxElement;
  return nElements;
}

// source: b/1/vector.c:172  [anchor-mhash]
unsigned int __cdecl QVector_InsertElement(
        struct QVector_s *ptVector,
        unsigned int iElement,
        void *pxElement)
{
  if ( ptVector->tPrivate.nElements == ptVector->tPrivate.nArraySize )
    QVector_Realloc(ptVector, 1u);
  if ( iElement < ptVector->tPrivate.nElements - 1 )
    memmove(
      &ptVector->tPrivate.papxElement[iElement + 1],
      &ptVector->tPrivate.papxElement[iElement],
      4 * (ptVector->tPrivate.nElements - iElement));
  ++ptVector->tPrivate.nElements;
  ptVector->tPrivate.papxElement[iElement] = (void *)pxElement;
  return iElement;
}

// source: b/1/vector.c:204  [anchor-mhash]
void __cdecl QVector_RemoveElement(struct QVector_s *ptVector, unsigned int iElement)
{
  unsigned int v2; // eax
  enum bool isStrictOrder; // esi
  void **papxElement; // ecx

  v2 = ptVector->tPrivate.nElements - 1;
  ptVector->tPrivate.nElements = v2;
  if ( iElement < v2 )
  {
    isStrictOrder = ptVector->tPrivate.isStrictOrder;
    papxElement = ptVector->tPrivate.papxElement;
    if ( isStrictOrder )
      memmove(&papxElement[iElement], &papxElement[iElement + 1], 4 * (v2 - iElement));
    else
      papxElement[iElement] = papxElement[v2];
  }
}

// source: b/1/vector.c:234  [anchor-mhash]
enum bool __cdecl QVector_FindElement(
        struct QVector_s *ptVector,
        unsigned int *piElement,
        void *pxElement)
{
  unsigned int nElements; // ecx
  unsigned int v4; // eax
  void **i; // edx

  nElements = ptVector->tPrivate.nElements;
  v4 = 0;
  if ( !ptVector->tPrivate.nElements )
    return false;
  for ( i = ptVector->tPrivate.papxElement; *i != pxElement; ++i )
  {
    if ( ++v4 >= nElements )
      return false;
  }
  if ( piElement )
    *piElement = v4;
  return true;
}

// source: b/1/vector.c:263  [anchor-callee]
void __cdecl QVector_RemoveElementByPointer(struct QVector_s *ptVector, void *pxElement)
{
  unsigned int nElements; // edi
  unsigned int v3; // eax
  void **papxElement; // esi
  void **i; // ecx
  unsigned int v6; // ecx

  nElements = ptVector->tPrivate.nElements;
  v3 = 0;
  if ( ptVector->tPrivate.nElements )
  {
    papxElement = ptVector->tPrivate.papxElement;
    for ( i = (void **)papxElement; *i != pxElement; ++i )
    {
      if ( ++v3 >= ptVector->tPrivate.nElements )
        return;
    }
    v6 = nElements - 1;
    ptVector->tPrivate.nElements = nElements - 1;
    if ( v3 < nElements - 1 )
    {
      if ( ptVector->tPrivate.isStrictOrder )
        memmove(&papxElement[v3], &papxElement[v3 + 1], 4 * (v6 - v3));
      else
        papxElement[v3] = papxElement[v6];
    }
  }
}

// source: b/1/vector.c:282  [anchor-mhash]
unsigned int __cdecl QVector_GetElementIndex(
        struct QVector_s *ptVector,
        void *pxElement)
{
  unsigned int v2; // ecx
  unsigned int nElements; // ecx
  unsigned int result; // eax
  void **i; // edx
  unsigned int iElement; // [esp+0h] [ebp-4h]

  iElement = v2;
  nElements = ptVector->tPrivate.nElements;
  result = 0;
  if ( !ptVector->tPrivate.nElements )
    return iElement;
  for ( i = ptVector->tPrivate.papxElement; *i != pxElement; ++i )
  {
    if ( ++result >= nElements )
      return iElement;
  }
  return result;
}

// source: b/1/vector.c:304  [size]
void __cdecl QVector_QSort(
        struct QVector_s *ptVector,
        int (__cdecl *pfQSortCallback)(void **, void **))
{
  if ( ptVector->tPrivate.nElements )
    qsort(ptVector->tPrivate.papxElement, ptVector->tPrivate.nElements, 4, pfQSortCallback);
}

// source: b/1/vector.c:324  [anchor-mhash]
struct QVector_s *__cdecl QVector_QSortPart(
        struct QVector_s *ptVector,
        unsigned int iStart,
        unsigned int nNum,
        int (__cdecl *pfQSortCallback)(void **, void **))
{
  if ( ptVector->tPrivate.nElements )
    qsort(&ptVector->tPrivate.papxElement[iStart], nNum, 4, pfQSortCallback);
    return 0;
  return ptVector;
}

// source: b/1/vector.c:343  [anchor-mhash]
void __cdecl QVector_Map(
        struct QVector_s *ptVector,
        void (__cdecl *pfVectorMap)(void *, void *),
        void *pxContext)
{
  unsigned int i; // esi

  for ( i = 0; i < ptVector->tPrivate.nElements; ++i )
    pfVectorMap(ptVector->tPrivate.papxElement[i], pxContext);
}

// source: b/1/vector.c:365  [size]
struct QVector_s *__cdecl QVector_Empty(struct QVector_s *ptVector)
{
  ptVector->tPrivate.nElements = 0;
  return ptVector;
}
