/* c/0/token.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: c/0/token.c:34  [anchor-hash]
enum bool __cdecl Token_IsNumber(struct QToken_s *ptTok)
{
  char *zToken; // ecx
  char v2; // al
  char v3; // al
  enum bool result; // eax

  zToken = ptTok->zToken;
  v2 = *zToken;
  result = true;
  if ( *zToken < 48 || v2 > 57 )
  {
    if ( v2 != 36 )
      return false;
    v3 = zToken[1];
    if ( (v3 < 48 || v3 > 57) && (v3 < 97 || v3 > 102) && (v3 < 65 || v3 > 70) )
      return false;
  }
  return result;
}

// source: c/0/token.c:54  [anchor-hash]
int __cdecl Token_IsNotReal(struct QToken_s *ptTok)
{
  char *zToken; // eax
  char v2; // cl
  char *v3; // ecx
  char v4; // al

  zToken = ptTok->zToken;
  if ( *zToken == 36 )
  {
    v2 = zToken[1];
    if ( v2 >= 48 && v2 <= 57 )
      return 1;
    if ( v2 >= 97 && v2 <= 102 || v2 >= 65 && v2 <= 70 )
      return 1;
  }
  if ( *zToken == 48 && zToken[1] == 120 )
    return 1;
  if ( zToken[1] == 88 )
    return 1;
  v3 = zToken;
  v4 = *zToken;
  if ( !v4 )
    return 1;
  while ( v4 != 46 && v4 != 101 && v4 != 69 )
  {
    v4 = *++v3;
    if ( !v4 )
      return 1;
  }
  return 0;
}

// source: c/0/token.c:83  [anchor-callee]
struct QToken_s *__cdecl Token_PutToken(
        struct QToken_s *ptDestinationToken,
        struct QToken_s *ptThis)
{
  char *v3; // eax

  v3 = (char *)Mem_AllocFn(strlen(ptThis->zToken) + 41, 4);
  *((_DWORD *)v3 + 1) = 0;
  *(_DWORD *)v3 = 0;
  *((_DWORD *)v3 + 4) = v3 + 40;
  *((_DWORD *)v3 + 2) = ptThis->eClass;
  *((_DWORD *)v3 + 3) = ptThis->eType;
  *((_DWORD *)v3 + 8) = ptThis->nTokenVal;
  *((double *)v3 + 3) = ptThis->vTokenVal;
  strcpy(v3 + 40, ptThis->zToken);
  return (struct QToken_s *)List_AddTail(v3, (int)ptDestinationToken);
}

// source: c/0/token.c:112  [anchor-caller]
enum bool __cdecl Token_GetToken(struct ParseContext_s *ptMyCtxt, struct QToken_s *ptTok)
{
  struct QTokenItem_s *ptHead; // eax
  _DWORD **v4; // eax
  struct InputStream_s *ptInputStream; // ebp
  int v7; // edi
  char v8; // al
  char v9; // al
  char *zToken; // eax
  char *zData; // eax
  unsigned int v12; // edi
  char v13; // al
  char v14; // al
  int v15; // ecx
  int v16; // ecx
  char *v17; // eax
  bool v18; // zf
  int v19; // [esp+4h] [ebp-4h]

  ptHead = ptTok->ptHead;
  if ( ptHead->ptNext )
  {
    ptTok->eClass = ptHead->eClass;
    ptTok->eType = ptHead->eType;
    ptTok->nTokenVal = ptHead->nTokenVal;
    LODWORD(ptTok->vTokenVal) = LODWORD(ptHead->vTokenVal);
    HIDWORD(ptTok->vTokenVal) = HIDWORD(ptHead->vTokenVal);
    strcpy(ptTok->zToken, ptHead->zToken);
    v4 = Node_Remove(ptHead);
    Mem_DeAllocFn(v4);
    return true;
  }
  ptInputStream = ptMyCtxt->ptInputStream;
  v19 = 1;
  v7 = 0;
  while ( 1 )
  {
    v8 = *ptInputStream->zData;
    if ( v8 != 32 && v8 != 9 && v8 != 10 && v8 != 13 )
      break;
    ++ptInputStream->zData;
  }
  if ( !*ptInputStream->zData )
  {
    while ( ptInputStream->pfGetInput(ptInputStream) )
    {
      while ( 1 )
      {
        v9 = *ptInputStream->zData;
        if ( v9 != 32 && v9 != 9 && v9 != 10 && v9 != 13 )
          break;
        ++ptInputStream->zData;
      }
      if ( *ptInputStream->zData )
        goto LABEL_17;
    }
    return false;
  }
LABEL_17:
  zToken = ptTok->zToken;
  ptTok->eClass = QSCRIPT_TOKENCLASS_NONE;
  ptTok->eType = QSCRIPT_TOKEN_NONE;
  *zToken = 0;
  zData = ptInputStream->zData;
  switch ( *ptInputStream->zData )
  {
    case '!':
      ptTok->eClass = QSCRIPT_TOKENCLASS_OPR;
      v12 = 2;
      if ( ptInputStream->zData[1] == 61 )
      {
        ptTok->eClass = QSCRIPT_TOKENCLASS_OPR;
        ptTok->eType = QSCRIPT_TOKEN_NE;
        v19 = 2;
      }
      else
      {
        ptTok->eClass = QSCRIPT_TOKENCLASS_UOPR;
        ptTok->eType = QSCRIPT_TOKEN_NOT;
      }
      goto LABEL_46;
    case '"':
      if ( !String_GetWordEx((int)zData, ptTok->zToken, ptInputStream, ptTok->nMaxTokenSize, 1) )
        goto LABEL_51;
      ptTok->eClass = QSCRIPT_TOKENCLASS_QSTRING;
      goto LABEL_55;
    case '&':
      ptTok->eClass = QSCRIPT_TOKENCLASS_OPR;
      ptTok->eType = QSCRIPT_TOKEN_AAND;
      v12 = 1;
      if ( ptInputStream->zData[1] == 38 )
      {
        v12 = 2;
        ptTok->eType = QSCRIPT_TOKEN_AND;
        v19 = 2;
      }
      goto LABEL_46;
    case '(':
      ptTok->eClass = QSCRIPT_TOKENCLASS_OPR;
      ptTok->eType = QSCRIPT_TOKEN_LPAR;
      v12 = 1;
      goto LABEL_46;
    case ')':
      ptTok->eClass = QSCRIPT_TOKENCLASS_EXPTERM;
      ptTok->eType = QSCRIPT_TOKEN_RPAR;
      v12 = 1;
      goto LABEL_46;
    case '*':
      ptTok->eClass = QSCRIPT_TOKENCLASS_OPR;
      ptTok->eType = QSCRIPT_TOKEN_MUL;
      v12 = 1;
      goto LABEL_46;
    case '+':
      ptTok->eClass = QSCRIPT_TOKENCLASS_OPR;
      ptTok->eType = QSCRIPT_TOKEN_ADD;
      v12 = 1;
      goto LABEL_46;
    case ',':
      ptTok->eClass = QSCRIPT_TOKENCLASS_OPR;
      ptTok->eType = QSCRIPT_TOKEN_COMMA;
      v12 = 1;
      goto LABEL_46;
    case '-':
      ptTok->eClass = QSCRIPT_TOKENCLASS_OPR;
      ptTok->eType = QSCRIPT_TOKEN_SUB;
      v12 = 1;
      goto LABEL_46;
    case '/':
      ptTok->eClass = QSCRIPT_TOKENCLASS_OPR;
      ptTok->eType = QSCRIPT_TOKEN_DIV;
      v12 = 1;
      goto LABEL_46;
    case ':':
      ptTok->eClass = QSCRIPT_TOKENCLASS_TOPR;
      ptTok->eType = QSCRIPT_TOKEN_CONDITIONAL2;
      v12 = 1;
      goto LABEL_46;
    case ';':
      ptTok->eClass = QSCRIPT_TOKENCLASS_EXPTERM;
      ptTok->eType = QSCRIPT_TOKEN_SEMICOLON;
      v12 = 1;
      goto LABEL_46;
    case '<':
      v13 = zData[1];
      if ( v13 == 60 )
      {
        ptTok->eType = QSCRIPT_TOKEN_SHL;
        v19 = 2;
        v7 = 1;
        ptTok->eClass = QSCRIPT_TOKENCLASS_OPR;
      }
      else
      {
        if ( v13 == 61 )
        {
          ptTok->eType = QSCRIPT_TOKEN_LE;
          v19 = 2;
          v7 = 1;
        }
        else
        {
          ptTok->eType = QSCRIPT_TOKEN_LT;
        }
        ptTok->eClass = QSCRIPT_TOKENCLASS_OPR;
      }
      goto LABEL_45;
    case '=':
      v18 = zData[1] == 61;
      ptTok->eClass = QSCRIPT_TOKENCLASS_OPR;
      if ( v18 )
      {
        ptTok->eType = QSCRIPT_TOKEN_EQ;
        goto LABEL_44;
      }
      ptTok->eType = QSCRIPT_TOKEN_ASSIGN;
      goto LABEL_45;
    case '>':
      v14 = zData[1];
      ptTok->eClass = QSCRIPT_TOKENCLASS_OPR;
      if ( v14 == 62 )
      {
        ptTok->eType = QSCRIPT_TOKEN_SHR;
LABEL_44:
        v19 = 2;
        v7 = 1;
        goto LABEL_45;
      }
      if ( v14 == 61 )
      {
        ptTok->eType = QSCRIPT_TOKEN_GE;
        goto LABEL_44;
      }
      v17 = ptTok->zToken;
      ptTok->eType = QSCRIPT_TOKEN_GT;
      *v17 = *ptInputStream->zData;
LABEL_45:
      v12 = v7 + 1;
      if ( v12 )
      {
LABEL_46:
        if ( v12 >= ptTok->nMaxTokenSize )
          goto LABEL_50;
        ptTok->zToken[v12] = 0;
        do
        {
          if ( v12 < ptTok->nMaxTokenSize )
            ptTok->zToken[v12 - 1] = ptInputStream->zData[v12 - 1];
LABEL_50:
          --v12;
        }
        while ( v12 );
      }
LABEL_51:
      v15 = v19;
      do
      {
        if ( *ptInputStream->zData )
          ++ptInputStream->zData;
        --v15;
      }
      while ( v15 );
LABEL_55:
      if ( ptTok->eClass == QSCRIPT_TOKENCLASS_ID && Token_IsNumber(ptTok) )
      {
        if ( Token_IsNotReal(ptTok) )
        {
          ptTok->nTokenVal = String_GetInteger(v16, (int)ptTok->zToken);
          ptTok->eClass = QSCRIPT_TOKENCLASS_INT;
          return ptTok->eClass != QSCRIPT_TOKENCLASS_NONE;
        }
        ptTok->vTokenVal = String_GetReal(ptTok->zToken);
        ptTok->eClass = QSCRIPT_TOKENCLASS_REAL;
      }
      return ptTok->eClass != QSCRIPT_TOKENCLASS_NONE;
    case '?':
      ptTok->eClass = QSCRIPT_TOKENCLASS_TOPR;
      ptTok->eType = QSCRIPT_TOKEN_CONDITIONAL;
      v12 = 1;
      goto LABEL_46;
    case '^':
      ptTok->eClass = QSCRIPT_TOKENCLASS_OPR;
      ptTok->eType = QSCRIPT_TOKEN_AXOR;
      v12 = 1;
      goto LABEL_46;
    case '{':
      ptTok->eType = QSCRIPT_TOKEN_LCURLY;
      ptTok->eClass = QSCRIPT_TOKENCLASS_EXPTERM;
      v12 = 1;
      goto LABEL_46;
    case '|':
      ptTok->eClass = QSCRIPT_TOKENCLASS_OPR;
      ptTok->eType = QSCRIPT_TOKEN_AOR;
      v12 = 1;
      if ( ptInputStream->zData[1] == 124 )
      {
        v12 = 2;
        ptTok->eType = QSCRIPT_TOKEN_OR;
        v19 = 2;
      }
      goto LABEL_46;
    case '}':
      ptTok->eType = QSCRIPT_TOKEN_RCURLY;
      ptTok->eClass = QSCRIPT_TOKENCLASS_EXPTERM;
      v12 = 1;
      goto LABEL_46;
    case '~':
      ptTok->eClass = QSCRIPT_TOKENCLASS_UOPR;
      ptTok->eType = QSCRIPT_TOKEN_ANOT;
      v12 = 1;
      goto LABEL_46;
    default:
      if ( !String_GetWordEx((int)zData, ptTok->zToken, ptInputStream, ptTok->nMaxTokenSize, 1) )
        goto LABEL_51;
      ptTok->eClass = QSCRIPT_TOKENCLASS_ID;
      goto LABEL_55;
  }
}

// source: c/0/token.c:413  [anchor-mhash]
struct ParseContext_s *__cdecl ParseContext_Init(
        struct ParseContext_s *ptParseContext,
        struct InputStream_s *ptInputStream,
        char *zTokenBuffer,
        unsigned int nTokenBufferSize)
{
  ptParseContext->ptInputStream = ptInputStream;
  ptParseContext->tToken.zToken = zTokenBuffer;
  ptParseContext->tToken.nMaxTokenSize = nTokenBufferSize;
  ptParseContext->tToken.ptHead = (struct QTokenItem_s *)&ptParseContext->tToken.ptMiddle;
  ptParseContext->tToken.ptTail = (struct QTokenItem_s *)&ptParseContext->tToken;
  ptParseContext->tToken.ptMiddle = nullptr;
  return ptParseContext;
}

// source: c/0/token.c:433  [size]
int __cdecl ParseContext_GetLineNumber(struct ParseContext_s *ptParseContext)
{
  return ptParseContext->ptInputStream->nLine;
}

// source: c/0/token.c:448  [size]
char *__cdecl ParseContext_GetLine(struct ParseContext_s *ptParseContext)
{
  return ptParseContext->ptInputStream->zBuffer;
}

int __cdecl sub_56F4E0(int a1, _BYTE *a2)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v16; };
    struct { char igi2_o1[4]; int v17; };
    struct { char igi2_o2[8]; _BYTE *v18; };
    struct { char igi2_o3[12]; int v19; };
    struct { char igi2_o4[16]; int v20; };
    struct { char igi2_o5[20]; _DWORD v21[256]; };
    char igi2_extent[1044];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  _BYTE *v2; // edx
  int v3; // eax
  int v4; // ecx
  int v5; // edi
  int v6; // ebp
  char v7; // dl
  int v8; // edi
  _BYTE *v9; // ebp
  int v10; // edx
  int v11; // eax
  int v12; // edx
  _BYTE *v13; // ebx
  int v14; // eax

  v2 = a2;
  v3 = 0;
  v4 = 0;
  igi2_frame.v16 = 0;
  v5 = 1;
  igi2_frame.v17 = 0;
  if ( *a2 )
  {
    v6 = igi2_frame.v19;
    do
    {
      v7 = v2[v4];
      switch ( v7 )
      {
        case '(':
          igi2_frame.v21[igi2_frame.v16++] = v3;
          goto LABEL_34;
        case ')':
          v6 = 0;
          if ( !igi2_frame.v16 )
            return 0;
          --igi2_frame.v16;
          goto LABEL_35;
        case '*':
        case '?':
          if ( v5 )
            return 0;
          *(_BYTE *)(v3 + a1) = v7;
          ++v3;
          ++v4;
          v5 = 1;
          v6 = 0;
          goto LABEL_37;
        case '+':
          if ( v5 )
            return 0;
          if ( v6 )
          {
            v8 = v3 - igi2_frame.v19;
            if ( v3 - igi2_frame.v19 > 0 )
            {
              v9 = (_BYTE *)(igi2_frame.v19 + a1);
              v10 = v3 - igi2_frame.v19;
              do
              {
                v9[v8] = *v9;
                ++v9;
                --v10;
              }
              while ( v10 );
            }
            v11 = v8 + v3;
            *(_BYTE *)(v11 + a1) = 42;
            v3 = v11 + 1;
            ++v4;
            v5 = 1;
            v6 = 0;
          }
          else if ( a2[v4 - 1] == 41 )
          {
            v12 = igi2_frame.v21[igi2_frame.v16];
            v5 = 1;
            if ( v3 - v12 > 0 )
            {
              v13 = (_BYTE *)(v3 + a1);
              igi2_frame.v18 = (_BYTE *)(a1 + v12);
              igi2_frame.v20 = v3 - v12;
              do
              {
                *v13++ = *igi2_frame.v18++;
                --igi2_frame.v20;
              }
              while ( igi2_frame.v20 );
            }
            v14 = v3 - v12 + v3;
            *(_BYTE *)(v14 + a1) = 42;
            v3 = v14 + 1;
            ++v4;
            v6 = 0;
          }
          else
          {
            *(_BYTE *)(v3 + a1) = v7;
            ++v3;
            ++v4;
            v5 = 1;
            v6 = 0;
          }
          goto LABEL_37;
        case '/':
        case '\\':
          *(_BYTE *)(v3 + a1) = v7;
          v7 = a2[v4 + 1];
          v6 = 0;
          v5 = 0;
          ++v3;
          ++v4;
          goto LABEL_36;
        case '[':
          igi2_frame.v19 = v3;
          if ( v7 == 93 )
            goto LABEL_11;
          break;
        case '{':
          if ( igi2_frame.v16 || igi2_frame.v17 )
            return 0;
          igi2_frame.v17 = 1;
          goto LABEL_34;
        case '}':
          if ( !igi2_frame.v17 )
            return 0;
          igi2_frame.v17 = 0;
LABEL_34:
          v6 = 0;
LABEL_35:
          v5 = 0;
LABEL_36:
          *(_BYTE *)(v3 + a1) = v7;
          ++v3;
          ++v4;
          goto LABEL_37;
        default:
          goto LABEL_34;
      }
      do
      {
        if ( !v7 )
          return 0;
        if ( v7 == 47 || v7 == 92 )
        {
          *(_BYTE *)(v3 + a1) = v7;
          ++v3;
          ++v4;
        }
        *(_BYTE *)(v3 + a1) = a2[v4];
        v7 = a2[v4 + 1];
        ++v3;
        ++v4;
      }
      while ( v7 != 93 );
LABEL_11:
      *(_BYTE *)(v3 + a1) = a2[v4];
      ++v3;
      ++v4;
      v6 = 1;
      v5 = 0;
LABEL_37:
      v2 = a2;
    }
    while ( a2[v4] );
  }
  *(_BYTE *)(v3 + a1) = 0;
  return 1;
}

int __cdecl sub_56F760(_BYTE *a1, _BYTE *a2)
{
  _BYTE *v2; // esi
  bool v3; // zf
  int result; // eax
  int v5; // eax

  v2 = a1;
  *a2 = 94;
  v3 = *a1 == 0;
  result = 1;
  if ( !v3 )
  {
    do
    {
      switch ( *v2 )
      {
        case '$':
        case '(':
        case ')':
        case '^':
          a2[result] = 47;
          v5 = result + 1;
          a2[v5] = *v2;
          result = v5 + 1;
          ++v2;
          continue;
        case '*':
          a2[result] = 46;
          a2[++result] = 42;
          break;
        case '.':
          a2[result++] = 47;
          goto LABEL_5;
        case '/':
        case '\\':
          a2[result++] = *v2++;
          goto LABEL_8;
        case '?':
LABEL_5:
          a2[result] = 46;
          break;
        default:
LABEL_8:
          a2[result] = *v2;
          break;
      }
      ++result;
    }
    while ( *++v2 );
  }
  a2[result] = 36;
  a2[result + 1] = 0;
  return result;
}

int __cdecl sub_56F830(int a1, int a2, int a3, int *a4, int a5, int a6)
{
  int v6; // eax
  int v7; // ecx
  int v8; // ebx
  int result; // eax
  int *v10; // ecx

  v6 = *a4;
  if ( *a4
    && (v7 = a3 + 20 * v6, *(_DWORD *)(v7 - 8) == a1)
    && (v8 = *(_DWORD *)(v7 - 12), v8 == a2 - 1)
    && *(_DWORD *)(v7 - 20) == a6 )
  {
    result = *(_DWORD *)(v7 - 4) + 1;
    *(_DWORD *)(v7 - 12) = v8 + 1;
    *(_DWORD *)(v7 - 4) = result;
  }
  else
  {
    v10 = (int *)(a3 + 20 * v6);
    v10[3] = a1;
    v10[1] = a5;
    v10[4] = 0;
    v10[2] = a2;
    *v10 = a6;
    result = v6 + 1;
    if ( dword_7AB6630 <= result )
      dword_7AB6630 = result;
    *a4 = result;
  }
  return result;
}

int __cdecl Wildcard_CreateNFA(_BYTE *a1, int *a2, char *a3)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v27; };
    struct { int v28; };
    struct { char igi2_o2[4]; int v29; };
    struct { char igi2_o3[8]; int *v30; };
    struct { char igi2_o4[12]; int v31; };
    struct { char igi2_o5[16]; int v32; };
    struct { char igi2_o6[20]; int v33; };
    struct { char igi2_o7[20]; char *v34; };
    struct { char igi2_o8[24]; int v35; };
    struct { char igi2_o9[28]; int v36; };
    struct { char igi2_o10[32]; int *v37; };
    struct { char igi2_o11[36]; char *v38; };
    struct { char igi2_o12[44]; int v39; };
    struct { char igi2_o13[48]; int v40; };
    struct { char igi2_o14[52]; int v41; };
    struct { char igi2_o15[56]; _BYTE v42[256]; };
    struct { char igi2_o16[312]; char a1a[512]; };
    struct { char igi2_o17[824]; char v44; };
    struct { char igi2_o18[1848]; _BYTE v45[1024]; };
    char igi2_extent[2872];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v3; // esi
  int v4; // ebx
  int v5; // kr00_4
  int v6; // ecx
  int *v7; // edx
  int *v8; // edi
  int v9; // ecx
  int v10; // eax
  int v11; // ecx
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // ecx
  int v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // ecx
  unsigned int v20; // esi
  _BYTE *v21; // edi
  int i; // edi
  int v23; // eax
  char *v24; // edi
  int *v25; // eax

  if ( sub_56F4E0((int)igi2_frame.a1a, a1) )
  {
    v3 = 0;
    memset(a3, 1u, 0x100u);
    v4 = 1;
    igi2_frame.v29 = 0;
    igi2_frame.v32 = 0;
    igi2_frame.v41 = 0;
    igi2_frame.v36 = -1;
    igi2_frame.v31 = 1;
    v5 = strlen(igi2_frame.a1a);
    v6 = 0;
    igi2_frame.v35 = 0;
    if ( v5 <= 0 )
    {
LABEL_64:
      v25 = &a2[5 * v6];
      v25[2] = 256;
      v25[4] = v6;
      v25[3] = v6;
      return 1;
    }
    v7 = a2;
    igi2_frame.v38 = a3 + 256;
    v8 = (int *)igi2_frame.v45;
    igi2_frame.v39 = 1;
    igi2_frame.v30 = (int *)&igi2_frame.v44;
    igi2_frame.v37 = (int *)igi2_frame.v45;
LABEL_4:
    switch ( igi2_frame.a1a[v3] )
    {
      case '$':
        v7[2] = 0x4000;
        goto LABEL_59;
      case '(':
        v9 = igi2_frame.v36;
        *igi2_frame.v30 = igi2_frame.v36;
        *v8 = igi2_frame.v35;
        v7[1] = igi2_frame.v41;
        igi2_frame.v36 = igi2_frame.v41++;
        ++igi2_frame.v29;
        ++v8;
        v7[2] = 0x8000;
        *v7 = v9;
        igi2_frame.v37 = v8;
        ++igi2_frame.v30;
        goto LABEL_59;
      case ')':
        if ( !igi2_frame.v29 )
          return 0;
        v10 = *(v8 - 1);
        --igi2_frame.v30;
        v7[1] = igi2_frame.v36;
        v11 = *igi2_frame.v30;
        --v8;
        igi2_frame.v40 = v10;
        *v7 = *igi2_frame.v30;
        igi2_frame.v36 = v11;
        v7[2] = 0x10000;
        v7[4] = -1;
        v7[3] = v4;
        a2[5 * v10 + 4] = v4;
        igi2_frame.v37 = v8;
        --igi2_frame.v29;
        goto LABEL_61;
      case '*':
        if ( !v6 )
          return 0;
        v14 = *(v7 - 3);
        v7 -= 5;
        v15 = v6 - 1;
        --v4;
        igi2_frame.v35 = v15;
        if ( v14 >= 256 && (v14 & 0x11000) == 0 )
          return 0;
        if ( (v14 & 0x10000) != 0 )
        {
          v7[3] = igi2_frame.v40;
          a2[5 * igi2_frame.v40 + 2] |= 0x20000u;
          v7[2] |= 0x200u;
        }
        else
        {
          v16 = v7[2] | 0x200;
          v7[3] = v15;
          v7[2] = v16;
        }
        v7[4] = v4;
        goto LABEL_61;
      case '.':
        v7[2] = 4096;
        goto LABEL_59;
      case '/':
        ++v3;
        goto LABEL_58;
      case '?':
        if ( !v6 )
          return 0;
        v12 = *(v7 - 3);
        v7 -= 5;
        --v4;
        igi2_frame.v35 = v6 - 1;
        if ( (v12 & 0x10000) != 0 )
          a2[5 * igi2_frame.v40 + 2] |= 0x20000u;
        v13 = v7[2] | 0x40000;
        v7[4] = v4;
        v7[2] = v13;
        goto LABEL_60;
      case '[':
        ++v3;
        memset(igi2_frame.v42, 0, sizeof(igi2_frame.v42));
        igi2_frame.v33 = 0;
        igi2_frame.v27 = v3;
        if ( igi2_frame.a1a[v3] == 126 )
        {
          ++v3;
          igi2_frame.v33 = 1;
          igi2_frame.v27 = v3;
        }
        LOBYTE(v17) = igi2_frame.a1a[v3];
        if ( (_BYTE)v17 == 93 )
          goto LABEL_39;
        break;
      case '^':
        v7[2] = 0x2000;
        goto LABEL_59;
      case '{':
        if ( igi2_frame.v32 || igi2_frame.v29 )
          return 0;
        v7[2] = 1024;
        v7[4] = v4;
        igi2_frame.v32 = 1;
        goto LABEL_60;
      case '}':
        if ( igi2_frame.v32 != 1 || igi2_frame.v29 )
          return 0;
        v7[2] = 2048;
        v7[4] = v4;
        igi2_frame.v32 = 0;
        goto LABEL_60;
      default:
LABEL_58:
        v7[2] = igi2_frame.a1a[v3];
        goto LABEL_59;
    }
    while ( v3 < v5 )
    {
      if ( (_BYTE)v17 == 92 )
      {
        v18 = igi2_frame.a1a[++v3];
        switch ( v18 )
        {
          case 0:
            return 0;
          case 78:
          case 110:
            igi2_frame.v42[10] = 1;
            goto LABEL_38;
          case 82:
          case 114:
            igi2_frame.v42[13] = 1;
            goto LABEL_38;
          case 84:
          case 116:
            igi2_frame.v42[9] = 1;
            goto LABEL_38;
          default:
            goto LABEL_33;
        }
      }
      if ( (_BYTE)v17 == 47 )
      {
        v18 = igi2_frame.a1a[++v3];
LABEL_33:
        igi2_frame.v42[v18] = 1;
      }
      else if ( igi2_frame.a1a[v3 + 1] == 45 )
      {
        v19 = igi2_frame.a1a[v3 + 2];
        v17 = (char)v17;
        igi2_frame.v28 = v3 + 2;
        if ( (char)v17 >= v19 )
          return 0;
        v20 = v19 - v17 + 1;
        memset(&igi2_frame.v42[v17], 1u, 4 * (v20 >> 2));
        v21 = &igi2_frame.v42[4 * (v20 >> 2) + v17];
        v3 = igi2_frame.v28;
        memset(v21, 1, ((_BYTE)v19 - (_BYTE)v17 + 1) & 3);
      }
      else
      {
        igi2_frame.v42[(char)v17] = 1;
      }
LABEL_38:
      LOBYTE(v17) = igi2_frame.a1a[++v3];
      igi2_frame.v27 = v3;
      if ( (_BYTE)v17 == 93 )
      {
LABEL_39:
        if ( igi2_frame.v33 )
        {
          for ( i = 0; i < 256; ++i )
            igi2_frame.v42[i] = igi2_frame.v42[i] == 0;
        }
        v23 = 0;
        if ( igi2_frame.v31 > 0 )
        {
          v24 = a3;
          igi2_frame.v34 = a3;
          do
          {
            if ( !memcmp(igi2_frame.v42, v24, 0x100u) )
              break;
            ++v23;
            v24 = igi2_frame.v34 + 256;
            igi2_frame.v34 += 256;
          }
          while ( v23 < igi2_frame.v31 );
          if ( v23 >= 32 )
            return 0;
          v4 = igi2_frame.v39;
          v3 = igi2_frame.v27;
        }
        if ( v23 == igi2_frame.v31 )
        {
          qmemcpy(igi2_frame.v38, igi2_frame.v42, 0x100u);
          ++igi2_frame.v31;
          v3 = igi2_frame.v27;
          igi2_frame.v38 += 256;
        }
        v8 = igi2_frame.v37;
        v7[2] = v23 | 0x1000;
LABEL_59:
        v7[4] = -1;
LABEL_60:
        v7[3] = v4;
LABEL_61:
        ++v3;
        v6 = igi2_frame.v35 + 1;
        ++v4;
        v7 += 5;
        ++igi2_frame.v35;
        igi2_frame.v39 = v4;
        if ( v3 >= v5 )
        {
          if ( igi2_frame.v32 || igi2_frame.v29 )
            return 0;
          goto LABEL_64;
        }
        goto LABEL_4;
      }
    }
  }
  return 0;
}

int __cdecl Wildcard_MatchNFA(int *a1, int *a2, char *a3, int a4, int a5, int a6)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v26; };
    struct { char igi2_o1[4]; int v27; };
    struct { char igi2_o2[8]; int v28; };
    struct { char igi2_o3[12]; int v29; };
    struct { char igi2_o4[16]; int v30; };
    struct { char igi2_o5[20]; int v31; };
    struct { char igi2_o6[24]; int *v32; };
    struct { char igi2_o7[28]; signed int v33; };
    struct { char igi2_o8[32]; int v34; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v6; // ebp
  int v7; // edx
  int v8; // edi
  int v9; // ecx
  int v10; // edx
  int v11; // edi
  int v12; // esi
  int v13; // ebp
  int v14; // ebx
  int v15; // eax
  int *v16; // ebx
  int v17; // eax
  bool v18; // zf
  int v19; // ecx
  int v21; // esi
  int v22; // ebx
  int v23; // ebx
  int *v24; // eax
  int v25; // eax

  v6 = 0;
  v7 = 0;
  v8 = 0;
  dword_834DCC0 = 0;
  dword_834DCC4 = 0;
  igi2_frame.v26 = 0;
  igi2_frame.v28 = 0;
  igi2_frame.v30 = 0;
  igi2_frame.v31 = 0;
  igi2_frame.v34 = 0;
  igi2_frame.v27 = 0;
  igi2_frame.v29 = 0;
  igi2_frame.v33 = strlen(a3);
  if ( a2 )
    *a2 = 0;
  if ( a1 )
    *a1 = -1;
  while ( 1 )
  {
    if ( v6 == -1 )
    {
      v9 = igi2_frame.v28;
      if ( igi2_frame.v28 <= 0 )
      {
        v11 = -1;
        v15 = 0;
      }
      else
      {
        v9 = igi2_frame.v28 - 1;
        v10 = dword_7ABDE98[5 * igi2_frame.v28 - 5];
        v11 = dword_7ABDE94[5 * igi2_frame.v28 - 5];
        v12 = dword_7ABDE90[5 * igi2_frame.v28 - 5];
        v13 = dword_7ABDE8C[5 * igi2_frame.v28 - 5];
        v14 = dword_7ABDE88[5 * igi2_frame.v28 - 5];
        if ( v10 )
        {
          dword_7ABDE98[5 * v9] = v10 - 1;
          dword_7ABDE90[5 * v9++] = v12 - 1;
        }
        v7 = v13;
        igi2_frame.v26 = v12;
        igi2_frame.v31 = v13;
        igi2_frame.v27 = v14;
        v15 = 1;
      }
      igi2_frame.v28 = v9;
      if ( !v15 )
        return 0;
      if ( v11 >= 0 )
        v6 = *(_DWORD *)(a4 + 20 * v11 + 16);
      else
        v6 = -1;
      v8 = 0;
      igi2_frame.v30 = v7;
      igi2_frame.v29 = 0;
    }
    v16 = (int *)(a4 + 20 * v6);
    v17 = v16[2];
    igi2_frame.v32 = v16;
    if ( v17 == 256 )
      break;
    switch ( v17 )
    {
      case 0x800:
        if ( v6 >= 0 )
          v6 = v16[3];
        else
          v6 = -1;
        if ( --igi2_frame.v30 < 0 )
          return 0;
        dword_7AB6634[2 * v7] = igi2_frame.v26 - (&dword_7AB6630)[2 * v7] + 1;
        goto LABEL_78;
      case 0x2000:
        if ( igi2_frame.v26 )
        {
          if ( v6 < 0 )
          {
            v6 = -1;
            goto LABEL_78;
          }
LABEL_28:
          v6 = v16[4];
          goto LABEL_78;
        }
LABEL_31:
        if ( v6 >= 0 )
          v6 = v16[3];
        else
          v6 = -1;
        goto LABEL_78;
      case 0x4000:
        if ( igi2_frame.v26 >= igi2_frame.v33 )
          goto LABEL_31;
LABEL_61:
        if ( v6 >= 0 )
          goto LABEL_28;
        v6 = -1;
        goto LABEL_78;
    }
    if ( (v17 & 0x8000) != 0 )
    {
      dword_7AB6688[v16[1]] = 0;
      v18 = (v16[2] & 0x20000) == 0;
      igi2_frame.v29 = 0;
      if ( !v18 )
        sub_56F830(v6, igi2_frame.v26, (int)dword_7ABDE88, &igi2_frame.v28, v7, igi2_frame.v27);
      if ( v6 >= 0 )
        v6 = v16[3];
      else
        v6 = -1;
      ++igi2_frame.v27;
      goto LABEL_78;
    }
    if ( (v17 & 0x10000) != 0 )
    {
      v19 = v16[1];
      if ( *v16 >= 0 )
        dword_7AB6688[*v16] += v8;
      if ( v8 || (igi2_frame.v29 = dword_7AB6688[v19]) != 0 )
      {
        if ( v6 >= 0 )
          v6 = v16[3];
        else
          v6 = -1;
        --igi2_frame.v27;
      }
      else
      {
        if ( v6 >= 0 )
          v6 = v16[4];
        else
          v6 = -1;
        --igi2_frame.v27;
      }
      goto LABEL_78;
    }
    if ( v17 == 1024 )
    {
      dword_7AB6638[2 * v7] = igi2_frame.v26;
      dword_7AB663C[2 * v7] = 0;
      if ( v6 >= 0 )
        v6 = v16[3];
      else
        v6 = -1;
      ++igi2_frame.v30;
      igi2_frame.v31 = v7 + 1;
      if ( v7 + 1 >= 10 )
        return 0;
      goto LABEL_78;
    }
    if ( igi2_frame.v26 >= igi2_frame.v33 )
      goto LABEL_61;
    v21 = a3[igi2_frame.v26];
    if ( (v17 & 0x1000) != 0 )
    {
      v22 = *(char *)(v21 + ((unsigned __int8)v17 << 8) + a5);
    }
    else if ( a6 )
    {
      v23 = toupper((unsigned __int8)v17);
      v22 = toupper(v21) == v23;
    }
    else
    {
      v22 = v21 == (unsigned __int8)v17;
    }
    v24 = igi2_frame.v32;
    if ( (igi2_frame.v32[2] & 0x200) != 0 && v22 )
    {
      sub_56F830(v6, igi2_frame.v26, (int)dword_7ABDE88, &igi2_frame.v28, igi2_frame.v31, igi2_frame.v27);
      v24 = igi2_frame.v32;
    }
    if ( (v24[2] & 0x40000) != 0 && v22 )
    {
      sub_56F830(v6, igi2_frame.v26, (int)dword_7ABDE88, &igi2_frame.v28, igi2_frame.v31, igi2_frame.v27);
      v24 = igi2_frame.v32;
    }
    if ( v6 >= 0 )
    {
      if ( !v22 )
      {
        v6 = v24[4];
        goto LABEL_78;
      }
      v6 = v24[3];
    }
    else
    {
      v6 = -1;
    }
    if ( v22 )
    {
      ++igi2_frame.v29;
      ++igi2_frame.v26;
    }
LABEL_78:
    if ( igi2_frame.v28 >= 512 )
      return 0;
    v7 = igi2_frame.v31;
    v8 = igi2_frame.v29;
  }
  v25 = igi2_frame.v26;
  if ( igi2_frame.v26 < 0 )
    v25 = igi2_frame.v34;
  if ( a2 )
    *a2 = v7;
  dword_834DCC0 = (int)dword_7AB6638;
  dword_834DCC4 = v7;
  if ( a1 )
    *a1 = v25;
  return 1;
}

int __cdecl Wildcard_SearchNFA(char *a1, _DWORD *a2, _DWORD *a3, int *a4, int a5, int a6, int a7)
{
  int v7; // ebx
  int v8; // esi
  int a1a; // [esp+Ch] [ebp-4h] BYREF

  v7 = strlen(a1);
  v8 = 0;
  if ( v7 <= 0 )
    return 0;
  while ( !Wildcard_MatchNFA(&a1a, a4, &a1[v8], a5, a6, a7) )
  {
    if ( ++v8 >= v7 )
      return 0;
  }
  if ( a2 )
    *a2 = v8;
  if ( a3 )
    *a3 = a1a;
  return 1;
}

int __cdecl Wildcard_Match(void *a1, void *a2, void *a3, void *a4, int a5)
{
  if ( Wildcard_CreateNFA(a1, &g_a2_0, g_a3_0) )
    return Wildcard_MatchNFA((int *)a2, (int *)a3, (char *)a4, (int)&g_a2_0, (int)g_a3_0, a5);
  else
    return 0;
}

int __cdecl Wildcard_MatchSimple(void *a1, void *a2, void *a3, void *a4, int a5)
{
  _BYTE a1a[512]; // [esp+0h] [ebp-200h] BYREF

  sub_56F760(a1, a1a);
  if ( Wildcard_CreateNFA(a1a, &g_a2_0, g_a3_0) )
    return Wildcard_MatchNFA((int *)a2, (int *)a3, (char *)a4, (int)&g_a2_0, (int)g_a3_0, a5);
  else
    return 0;
}

int __cdecl Wildcard_SearchSimple(void *a1, void *a2, void *a3, void *a4, void *a5, int a6)
{
  _BYTE a2a[512]; // [esp+0h] [ebp-200h] BYREF

  sub_56F760(a1, a2a);
  if ( Wildcard_CreateNFA(a2a, &g_a2_1, g_a3_1) )
    return Wildcard_SearchNFA((char *)a2, a3, a4, (int *)a5, (int)&g_a2_1, (int)g_a3_1, a6);
  else
    return 0;
}

int __cdecl Wildcard_GetMatchedTaggedExpression(
        int a1,
        int a2,
        int a3,
        _BYTE *a4)
{
  int v4; // eax
  int v5; // ecx
  int v6; // edi

  if ( dword_834DCC4 <= a3 )
  {
    if ( a2 )
      *a4 = 0;
    return 0;
  }
  if ( !a2 )
    return 0;
  v4 = 0;
  v5 = a2 - 1;
  if ( v5 > 0 )
  {
    v6 = dword_834DCC0;
    do
    {
      if ( v4 >= (int)(*(_DWORD *)(v6 + 8 * a3 + 4) - 1) )
        break;
      a4[v4] = *(_BYTE *)(v4 + *(_DWORD *)(v6 + 8 * a3) + a1);
      ++v4;
    }
    while ( v4 < v5 );
  }
  a4[v4] = 0;
  return 1;
}

signed int __cdecl Wildcard_SubstituteString(int a1, void *a2, int a3, void *a4)
{
  signed int result; // eax
  char v6; // cl

  for ( result = 0; result < a3 - 1; a4 = (char *)a4 + 1 )
  {
    v6 = *(_BYTE *)a4;
    if ( !*(_BYTE *)a4 )
      break;
    if ( v6 == 47 && (v6 = *((_BYTE *)a4 + 1), a4 = (char *)a4 + 1, v6 >= 48) && v6 <= 57 )
    {
      Wildcard_GetMatchedTaggedExpression(a1, a3 - result, v6 - 48, (_BYTE *)a2 + result);
      result = strlen((char *)a2);
    }
    else
    {
      *((_BYTE *)a2 + result++) = v6;
    }
  }
  *((_BYTE *)a2 + result) = 0;
  return result;
}
