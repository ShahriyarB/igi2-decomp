/* c/0/qvmparser.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: c/0/qvmparser.c:28  [anchor-hash]
struct QVMParserPatternList_s *__cdecl QVMParserPatternList_Alloc(
        struct QVMParserPatternList_s *ptQVMParserPatternList)
{
  ptQVMParserPatternList->ptHead = (struct QVMParserPattern_s *)&ptQVMParserPatternList->ptMiddle;
  ptQVMParserPatternList->ptTail = (struct QVMParserPattern_s *)ptQVMParserPatternList;
  ptQVMParserPatternList->ptMiddle = nullptr;
  return ptQVMParserPatternList;
}

// source: c/0/qvmparser.c:43  [anchor-hash]
struct QVMParserPatternList_s *__cdecl QVMParserPatternList_DeAlloc(
        struct QVMParserPatternList_s *ptQVMParserPatternList)
{
  struct QVMParserPatternList_s *result; // eax
  struct QVMParserPatternList_s *ptHead; // ebx
  _DWORD **v3; // eax
  int v4; // esi

  result = (struct QVMParserPatternList_s *)ptQVMParserPatternList->ptHead;
  ptHead = (struct QVMParserPatternList_s *)result->ptHead;
  if ( result->ptHead )
  {
    do
    {
      v3 = Node_Remove(result);
      if ( v3 )
      {
        v4 = *(_DWORD *)((unsigned int)(v3 - 1) & 0xFFFFFFFC);
        --Mem_nCurrentAllocations;
        Node_Remove((_DWORD **)v4);
        memset(*(void **)(v4 + 8), 0xCDu, *(_DWORD *)(v4 + 16));
        free((void *)v4);
      }
      result = ptHead;
      ptHead = (struct QVMParserPatternList_s *)ptHead->ptHead;
    }
    while ( ptHead );
  }
  return result;
}

// source: c/0/qvmparser.c:71  [anchor-mhash]
void __cdecl QVMParserPatternList_AddToken(
        struct QVMParserPatternList_s *ptQVMParserPatternList,
        char *zToken,
        int nTokenID,
        enum bool isUnique)
{
  _DWORD *v5; // esi
  int v6; // esi

  v5 = Mem_AllocFn(18704, 4);
  v5[1] = 0;
  *v5 = 0;
  strcpy((char *)v5 + 8, zToken);
  v5[4675] = nTokenID;
  v5[4674] = isUnique;
  if ( Wildcard_CreateNFA(zToken, v5 + 66, (char *)v5 + 10504) )
  {
    List_AddTail(v5, (int)ptQVMParserPatternList);
  }
  else
  {
    v6 = *(_DWORD *)((unsigned int)(v5 - 1) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v6);
    memset(*(void **)(v6 + 8), 0xCDu, *(_DWORD *)(v6 + 16));
    free((void *)v6);
  }
}

// source: c/0/qvmparser.c:109  [anchor-mhash]
struct QVMParser_s *__cdecl QVMParser_Alloc(
        struct QVMParser_s *ptQVMParser,
        struct QVMParserPatternList_s *ptQVMParserPatternList,
        struct InputStream_s *ptInputStream)
{
  ptQVMParser->ptQVMParserPatternList = ptQVMParserPatternList;
  ptQVMParser->ptInputStream = ptInputStream;
  ptQVMParser->tQVMParserTokenList.ptHead = (struct QVMParserToken_s *)&ptQVMParser->tQVMParserTokenList.ptMiddle;
  ptQVMParser->tQVMParserTokenList.ptTail = (struct QVMParserToken_s *)&ptQVMParser->tQVMParserTokenList;
  ptQVMParser->tQVMParserTokenList.ptMiddle = nullptr;
  return ptQVMParser;
}

// source: c/0/qvmparser.c:128  [anchor-hash]
struct QVMParser_s *__cdecl QVMParser_DeAlloc(struct QVMParser_s *ptQVMParser)
{
  struct QVMParser_s *result; // eax
  struct QVMParser_s *ptQVMParserPatternList; // ebx
  _DWORD **v3; // eax
  int v4; // esi

  result = (struct QVMParser_s *)ptQVMParser->tQVMParserTokenList.ptHead;
  ptQVMParserPatternList = (struct QVMParser_s *)result->ptQVMParserPatternList;
  if ( result->ptQVMParserPatternList )
  {
    do
    {
      v3 = Node_Remove(result);
      if ( v3 )
      {
        v4 = *(_DWORD *)((unsigned int)(v3 - 1) & 0xFFFFFFFC);
        --Mem_nCurrentAllocations;
        Node_Remove((_DWORD **)v4);
        memset(*(void **)(v4 + 8), 0xCDu, *(_DWORD *)(v4 + 16));
        free((void *)v4);
      }
      result = ptQVMParserPatternList;
      ptQVMParserPatternList = (struct QVMParser_s *)ptQVMParserPatternList->ptQVMParserPatternList;
    }
    while ( ptQVMParserPatternList );
  }
  return result;
}

// source: c/0/qvmparser.c:150  [anchor-hash]
struct QVMParserToken_s *__cdecl QVMParser_AllocToken(
        struct QVMParserToken_s *ptQVMParserToken)
{
  ptQVMParserToken->ptPrev = nullptr;
  ptQVMParserToken->ptNext = nullptr;
  ptQVMParserToken->nMaxTokenSize = 512;
  ptQVMParserToken->zToken = ptQVMParserToken->zTempToken;
  ptQVMParserToken->zAlloc = nullptr;
  return ptQVMParserToken;
}

// source: c/0/qvmparser.c:168  [anchor-callee]
void __cdecl QVMParser_DeAllocToken(struct QVMParserToken_s *ptQVMParserToken)
{
  char *zToken; // eax
  int v2; // esi

  if ( ptQVMParserToken->zAlloc )
  {
    zToken = ptQVMParserToken->zToken;
    if ( zToken )
    {
      v2 = *(_DWORD *)((unsigned int)(zToken - 4) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v2);
      memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
      free((void *)v2);
    }
    ptQVMParserToken->zToken = nullptr;
    ptQVMParserToken->nMaxTokenSize = 0;
  }
}

// source: c/0/qvmparser.c:190  [anchor-callee]
void __cdecl QVMParser_CopyStringToToken(
        struct QVMParserToken_s *ptQVMParserToken,
        char *zString,
        unsigned int nMaxCharacters)
{
  char *zAlloc; // eax
  int v4; // ebx
  char *v5; // eax

  if ( nMaxCharacters >= ptQVMParserToken->nMaxTokenSize )
  {
    zAlloc = ptQVMParserToken->zAlloc;
    if ( zAlloc )
    {
      --Mem_nCurrentAllocations;
      v4 = *(_DWORD *)((unsigned int)(zAlloc - 4) & 0xFFFFFFFC);
      Node_Remove((_DWORD **)v4);
      memset(*(void **)(v4 + 8), 0xCDu, *(_DWORD *)(v4 + 16));
      free((void *)v4);
      ptQVMParserToken->zAlloc = nullptr;
    }
    v5 = (char *)Mem_AllocFn(nMaxCharacters + 1, 4);
    ptQVMParserToken->nMaxTokenSize = nMaxCharacters + 1;
    ptQVMParserToken->zAlloc = v5;
    ptQVMParserToken->zToken = v5;
  }
  strncpy(ptQVMParserToken->zToken, zString, nMaxCharacters);
  ptQVMParserToken->zToken[nMaxCharacters] = 0;
}

// source: c/0/qvmparser.c:223  [anchor-callee]
enum bool __cdecl QVMParser_GetToken(struct QVMParserToken_s *ptQVMParserToken, struct QVMParser_s *ptQVMParser)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QVMParserPattern_s *ptMax; };
    struct { char igi2_o1[4]; int nMatched; };
    char igi2_extent[8];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QVMParserToken_s *ptHead; // ebx
  _DWORD **v3; // eax
  struct InputStream_s *ptInputStream; // eax
  struct QVMParserPattern_s *v6; // edi
  struct QVMParserPattern_s *ptNext; // ebx
  signed int v8; // ebp

  ptHead = ptQVMParser->tQVMParserTokenList.ptHead;
  if ( ptHead->ptNext )
  {
    QVMParser_CopyStringToToken(ptQVMParserToken, ptHead->zToken, strlen(ptHead->zToken));
    ptQVMParserToken->nTokenID = ptHead->nTokenID;
    QVMParser_DeAllocToken(ptHead);
    v3 = Node_Remove(ptHead);
    Mem_DeAllocFn(v3);
    return true;
  }
  else
  {
    ptInputStream = ptQVMParser->ptInputStream;
    if ( *ptInputStream->zData )
    {
LABEL_6:
      v6 = ptQVMParser->ptQVMParserPatternList->ptHead;
      ptNext = v6->ptNext;
      v8 = 0;
      igi2_frame.ptMax = nullptr;
      if ( !v6->ptNext )
        return false;
      do
      {
        if ( Wildcard_MatchNFA(
               &igi2_frame.nMatched,
               nullptr,
               ptQVMParser->ptInputStream->zData,
               (int)v6->atNFA,
               (int)v6->atCharClass,
               0) )
        {
          if ( igi2_frame.nMatched >= v8 )
          {
            v8 = igi2_frame.nMatched;
            igi2_frame.ptMax = v6;
            if ( v6->isUnique )
              break;
          }
        }
        v6 = ptNext;
        ptNext = ptNext->ptNext;
      }
      while ( ptNext );
      if ( igi2_frame.ptMax )
      {
        QVMParser_CopyStringToToken(ptQVMParserToken, ptQVMParser->ptInputStream->zData, v8);
        ptQVMParser->ptInputStream->zData += v8;
        ptQVMParserToken->nTokenID = igi2_frame.ptMax->nTokenID;
        return true;
      }
      else
      {
        return false;
      }
    }
    else
    {
      while ( ptInputStream->pfGetInput(ptInputStream) )
      {
        ptInputStream = ptQVMParser->ptInputStream;
        if ( *ptInputStream->zData )
          goto LABEL_6;
      }
      return false;
    }
  }
}

// source: c/0/qvmparser.c:304  [anchor-caller]
void __cdecl QVMParser_PutToken(struct QVMParser_s *ptQVMParser, struct QVMParserToken_s *ptQVMParserToken)
{
  struct QVMParserToken_s *v2; // esi

  v2 = (struct QVMParserToken_s *)Mem_AllocFn(536, 4);
  v2->zToken = v2->zTempToken;
  v2->ptPrev = nullptr;
  v2->ptNext = nullptr;
  v2->nMaxTokenSize = 512;
  v2->zAlloc = nullptr;
  QVMParser_CopyStringToToken(v2, ptQVMParserToken->zToken, strlen(ptQVMParserToken->zToken));
  v2->nTokenID = ptQVMParserToken->nTokenID;
  List_AddHead(v2, (int)&ptQVMParser->tQVMParserTokenList);
}
