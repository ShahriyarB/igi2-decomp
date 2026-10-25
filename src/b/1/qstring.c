/* b/1/qstring.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/1/qstring.c:36  [anchor-mhash]
enum bool __cdecl QString_IsCharInQString(
        struct QString_s *ptQString,
        char tChar)
{
  unsigned int nLength; // ecx
  int v3; // eax

  nLength = ptQString->nLength;
  v3 = 0;
  if ( !nLength )
    return false;
  while ( ptQString->tPrivate.patQStringChar[v3] != tChar )
  {
    if ( ++v3 >= nLength )
      return false;
  }
  return true;
}

// source: b/1/qstring.c:63  [anchor-mhash]
struct QString_s *__cdecl QString_GetToken(
        struct QString_s *ptDestinationQString,
        struct QString_s *ptQString,
        unsigned int *pnOffset,
        struct QString_s *ptDelimiter)
{
  #pragma pack(push, 1)
  union
  {
    struct { char pattWhiteSpaceDelimiter[4]; };
    struct { char igi2_o1[4]; struct QString_s tWhiteSpaceDelimiter; };
    char igi2_extent[24];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char *patQStringChar; // edi
  unsigned int nAllocated; // ebp
  unsigned int v6; // eax
  int v7; // esi
  char *v8; // ecx
  char v9; // dl
  struct QString_s *p_tWhiteSpaceDelimiter; // ebx
  unsigned int v11; // eax
  unsigned int nLength; // edi
  int v13; // ecx
  unsigned int v14; // ebp
  unsigned int v15; // edi
  int v16; // ecx
  struct QString_s *ptDelimitera = *(struct QString_s * *)&ptDelimiter; // [esp+38h] [ebp+10h] ARGSLOT

  igi2_frame.tWhiteSpaceDelimiter.nLength = 0;
  igi2_frame.tWhiteSpaceDelimiter.tPrivate.nAllocated = 4;
  igi2_frame.tWhiteSpaceDelimiter.tPrivate.nReallocSize = 0;
  igi2_frame.tWhiteSpaceDelimiter.tPrivate.patQStringChar = igi2_frame.pattWhiteSpaceDelimiter;
  igi2_frame.tWhiteSpaceDelimiter.tPrivate.pxAllocatedMem = nullptr;
  QString_ReAlloc(&igi2_frame.tWhiteSpaceDelimiter, 4u);
  patQStringChar = igi2_frame.tWhiteSpaceDelimiter.tPrivate.patQStringChar;
  nAllocated = igi2_frame.tWhiteSpaceDelimiter.tPrivate.nAllocated;
  v6 = 0;
  v7 = " \t\r\n" - igi2_frame.tWhiteSpaceDelimiter.tPrivate.patQStringChar;
  do
  {
    if ( v6 >= nAllocated )
      break;
    v8 = &patQStringChar[v6];
    v9 = patQStringChar[v6++ + v7];
    *v8 = v9;
  }
  while ( v6 < 4 );
  p_tWhiteSpaceDelimiter = ptDelimiter;
  igi2_frame.tWhiteSpaceDelimiter.nLength = v6;
  if ( !ptDelimiter )
    p_tWhiteSpaceDelimiter = &igi2_frame.tWhiteSpaceDelimiter;
  v11 = *pnOffset;
  ptDelimitera = (struct QString_s *)ptQString->nLength;
  if ( *pnOffset < (unsigned int)ptDelimitera )
  {
    nLength = p_tWhiteSpaceDelimiter->nLength;
    do
    {
      v13 = 0;
      if ( !nLength )
        break;
      while ( p_tWhiteSpaceDelimiter->tPrivate.patQStringChar[v13] != ptQString->tPrivate.patQStringChar[v11] )
      {
        if ( ++v13 >= nLength )
          goto LABEL_13;
      }
      ++v11;
    }
    while ( v11 < (unsigned int)ptDelimitera );
  }
LABEL_13:
  v14 = v11;
  if ( v11 < (unsigned int)ptDelimitera )
  {
    v15 = p_tWhiteSpaceDelimiter->nLength;
    while ( 1 )
    {
      v16 = 0;
      if ( v15 )
        break;
LABEL_18:
      if ( ++v11 >= (unsigned int)ptDelimitera )
        goto LABEL_19;
    }
    while ( p_tWhiteSpaceDelimiter->tPrivate.patQStringChar[v16] != ptQString->tPrivate.patQStringChar[v11] )
    {
      if ( ++v16 >= v15 )
        goto LABEL_18;
    }
  }
LABEL_19:
  *pnOffset = v11;
  if ( v11 <= v14 )
    return nullptr;
  if ( ptDestinationQString->nLength )
    ptDestinationQString->nLength = 0;
  QString_InsertSubString(ptDestinationQString, 0, ptQString, v14, v11 - v14);
  return ptDestinationQString;
}

// source: b/1/qstring.c:112  [anchor-mhash]
struct QString_s *__cdecl QString_AllocEx(
        struct QString_s *ptQString,
        unsigned int nInitialSize,
        unsigned int nReAllocSize,
        char *patQStringChar)
{
  char *v4; // eax

  ptQString->nLength = 0;
  ptQString->tPrivate.nAllocated = nInitialSize;
  ptQString->tPrivate.nReallocSize = nReAllocSize;
  ptQString->tPrivate.patQStringChar = patQStringChar;
  ptQString->tPrivate.pxAllocatedMem = nullptr;
  if ( !patQStringChar && nInitialSize )
  {
    v4 = (char *)Mem_AllocFn(nInitialSize, 4);
    ptQString->tPrivate.patQStringChar = v4;
    ptQString->tPrivate.pxAllocatedMem = v4;
  }
  return ptQString;
}

// source: b/1/qstring.c:136  [anchor-hash]
struct QString_s *__cdecl QString_Alloc(struct QString_s *ptQString)
{
  ptQString->nLength = 0;
  ptQString->tPrivate.nAllocated = 0;
  ptQString->tPrivate.nReallocSize = 64;
  ptQString->tPrivate.patQStringChar = nullptr;
  ptQString->tPrivate.pxAllocatedMem = nullptr;
  return ptQString;
}

// source: b/1/qstring.c:151  [anchor-callee]
void __cdecl QString_DeAlloc(struct QString_s *ptQString)
{
  void *pxAllocatedMem; // eax
  int v2; // esi

  pxAllocatedMem = ptQString->tPrivate.pxAllocatedMem;
  if ( pxAllocatedMem )
  {
    v2 = *(_DWORD *)(((int)pxAllocatedMem - 4) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v2);
    memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
    free((void *)v2);
    ptQString->tPrivate.pxAllocatedMem = nullptr;
    ptQString->tPrivate.patQStringChar = nullptr;
    ptQString->tPrivate.nAllocated = 0;
    ptQString->nLength = 0;
  }
}

// source: b/1/qstring.c:173  [anchor-callee]
void __cdecl QString_ReAlloc(struct QString_s *ptQString, unsigned int nNewSize)
{
  unsigned int nAllocated; // ecx
  unsigned int v3; // edi
  char *v4; // eax
  char *patQStringChar; // esi
  char *v6; // ebp
  void *pxAllocatedMem; // eax
  unsigned int nAllocSize; // [esp+0h] [ebp-4h]

  nAllocated = ptQString->tPrivate.nAllocated;
  if ( nAllocated < nNewSize && ptQString->tPrivate.nReallocSize )
  {
    if ( nAllocated )
    {
      nAllocSize = ptQString->tPrivate.nAllocated;
      v3 = nAllocSize;
    }
    else
    {
      v3 = 256;
      nAllocSize = 256;
    }
    if ( nNewSize + 64 > v3 )
    {
      v3 += (nNewSize - v3 + 64) >> 6 << 6;
      nAllocSize = v3;
    }
    v4 = (char *)Mem_AllocFn(v3, 4);
    patQStringChar = ptQString->tPrivate.patQStringChar;
    v6 = v4;
    if ( patQStringChar )
    {
      qmemcpy(v4, patQStringChar, ptQString->nLength + 1);
      pxAllocatedMem = ptQString->tPrivate.pxAllocatedMem;
      if ( pxAllocatedMem )
      {
        Mem_DeAllocFn(pxAllocatedMem);
        ptQString->tPrivate.pxAllocatedMem = nullptr;
      }
      v3 = nAllocSize;
    }
    ptQString->tPrivate.nAllocated = v3;
    ptQString->tPrivate.patQStringChar = v6;
    ptQString->tPrivate.pxAllocatedMem = v6;
  }
}

// source: b/1/qstring.c:218  [anchor-hash]
struct QString_s *__cdecl QString_New()
{
  struct QString_s *result; // eax

  result = (struct QString_s *)Mem_AllocFn(20, 4);
  result->nLength = 0;
  result->tPrivate.nAllocated = 0;
  result->tPrivate.nReallocSize = 64;
  result->tPrivate.patQStringChar = nullptr;
  result->tPrivate.pxAllocatedMem = nullptr;
  return result;
}

// source: b/1/qstring.c:236  [anchor-caller]
void __cdecl QString_Delete(struct QString_s *ptQString)
{
  int v2; // esi

  QString_DeAlloc(ptQString);
  if ( ptQString )
  {
    v2 = *(_DWORD *)((unsigned int)&ptQString[-1].nLength & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v2);
    memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
    free((void *)v2);
  }
}

// source: b/1/qstring.c:252  [size]
unsigned int __cdecl QString_GetLength(struct QString_s *ptQString)
{
  return ptQString->nLength;
}

// source: b/1/qstring.c:267  [size]
unsigned int __cdecl QString_Trim(struct QString_s *ptQString, unsigned int nOffset)
{
  if ( ptQString->nLength > nOffset )
    ptQString->nLength = nOffset;
  return nOffset;
}

// source: b/1/qstring.c:293  [anchor-callee]
unsigned int __cdecl QString_InsertSubString(
        struct QString_s *ptDestinationQString,
        unsigned int nDestinationOffset,
        struct QString_s *ptQString,
        unsigned int nOffset,
        unsigned int nSourceLength)
{
  unsigned int nLength; // eax
  unsigned int v7; // esi
  unsigned int v9; // eax
  unsigned int nAllocated; // eax
  unsigned int i; // eax
  unsigned int v12; // ebp
  unsigned int j; // ebp
  char *v14; // eax
  unsigned int k; // eax
  char v16; // cl
  char *v17; // edx
  unsigned int result; // eax

  nLength = ptQString->nLength;
  v7 = nDestinationOffset;
  if ( nOffset + nSourceLength > nLength )
    nSourceLength = nLength - nOffset;
  v9 = ptDestinationQString->nLength;
  if ( v9 <= nDestinationOffset )
    v9 = nDestinationOffset;
  QString_ReAlloc(ptDestinationQString, nSourceLength + v9);
  nAllocated = ptDestinationQString->tPrivate.nAllocated;
  if ( v7 >= nAllocated )
    v7 = ptDestinationQString->tPrivate.nAllocated;
  if ( v7 + nSourceLength > nAllocated )
    nSourceLength = nAllocated - v7;
  for ( i = ptDestinationQString->nLength; i < v7; ++i )
    ptDestinationQString->tPrivate.patQStringChar[i] = 32;
  v12 = ptDestinationQString->nLength;
  if ( v12 <= v7 )
    v12 = v7;
  ptDestinationQString->nLength = v12;
  for ( j = v12 - v7; j; v14[v7 - 1 + nSourceLength] = v14[v7 - 1] )
    v14 = &ptDestinationQString->tPrivate.patQStringChar[j--];
  for ( k = 0; k < nSourceLength; v17[v7] = v16 )
  {
    v16 = ptQString->tPrivate.patQStringChar[k + nOffset];
    v17 = &ptDestinationQString->tPrivate.patQStringChar[k++];
  }
  result = nSourceLength + ptDestinationQString->nLength;
  ptDestinationQString->nLength = result;
  return result;
}

// source: b/1/qstring.c:344  [anchor-mhash]
struct QString_s *__cdecl QString_Copy(
        struct QString_s *ptDestinationQString,
        struct QString_s *ptQString)
{
  if ( ptDestinationQString->nLength )
    ptDestinationQString->nLength = 0;
  return (struct QString_s *)QString_InsertSubString(ptDestinationQString, 0, ptQString, 0, ptQString->nLength);
}

// source: b/1/qstring.c:358  [anchor-mhash]
void __cdecl QString_CopySubString(
        struct QString_s *ptDestinationQString,
        struct QString_s *ptQString,
        unsigned int nOffset,
        unsigned int nSourceLength)
{
  if ( ptDestinationQString->nLength )
    ptDestinationQString->nLength = 0;
  QString_InsertSubString(ptDestinationQString, 0, ptQString, nOffset, nSourceLength);
}

// source: b/1/qstring.c:372  [size]
struct QString_s *__cdecl QString_Append(
        struct QString_s *ptDestinationQString,
        struct QString_s *ptQString)
{
  return (struct QString_s *)QString_InsertSubString(
                               ptDestinationQString,
                               ptDestinationQString->nLength,
                               ptQString,
                               0,
                               ptQString->nLength);
}

// source: b/1/qstring.c:385  [size]
unsigned int __cdecl QString_AppendSubString(
        struct QString_s *ptDestinationQString,
        struct QString_s *ptQString,
        unsigned int nOffset,
        unsigned int nSourceLength)
{
  return QString_InsertSubString(ptDestinationQString, ptDestinationQString->nLength, ptQString, nOffset, nSourceLength);
}

// source: b/1/qstring.c:398  [anchor-callee]
void __cdecl QString_DeleteSubstring(
        struct QString_s *ptQString,
        unsigned int nOffset,
        unsigned int nLength)
{
  unsigned int v3; // ecx
  unsigned int v4; // eax

  v3 = ptQString->nLength;
  if ( nOffset < v3 )
  {
    v4 = 0;
    if ( v3 - nOffset != nLength )
    {
      do
      {
        ptQString->tPrivate.patQStringChar[v4 + nOffset] = ptQString->tPrivate.patQStringChar[v4 + nOffset + nLength];
        ++v4;
      }
      while ( v4 < ptQString->nLength - nOffset - nLength );
    }
    ptQString->nLength -= nLength;
  }
}

// source: b/1/qstring.c:423  [anchor-mhash]
void __cdecl QString_Split(
        struct QString_s *ptDestinationQString,
        struct QString_s *ptQString,
        unsigned int nOffset)
{
  if ( ptDestinationQString->nLength )
    ptDestinationQString->nLength = 0;
  QString_InsertSubString(ptDestinationQString, 0, ptQString, nOffset, ptQString->nLength - nOffset);
  if ( ptQString->nLength > nOffset )
    ptQString->nLength = nOffset;
}

// source: b/1/qstring.c:443  [anchor-callee]
struct QString_s *__cdecl QString_FromCString(
        struct QString_s *ptQString,
        char *zString,
        unsigned int nLength)
{
  unsigned int i; // eax

  QString_ReAlloc(ptQString, nLength);
  for ( i = 0; i < nLength; ++i )
  {
    if ( i >= ptQString->tPrivate.nAllocated )
      break;
    ptQString->tPrivate.patQStringChar[i] = zString[i];
  }
  ptQString->nLength = i;
  return ptQString;
}

// source: b/1/qstring.c:470  [anchor-callee]
int __cdecl QString_GetCString(
        struct QString_s *ptQString,
        char *zBuffer,
        unsigned int nBufferSize)
{
  int result; // eax

  result = 0;
  if ( nBufferSize && ptQString->nLength )
  {
    do
    {
      if ( result >= nBufferSize )
        break;
      zBuffer[result] = ptQString->tPrivate.patQStringChar[result];
      ++result;
    }
    while ( result < ptQString->nLength );
  }
  return result;
}
