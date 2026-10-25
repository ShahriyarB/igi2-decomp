/* c/0/qvm.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: c/0/qvm.c:234  [anchor-hash]
struct QVM_s *__cdecl QVM_SaveSP(struct QVM_s *ptQVM)
{
  int nVSP; // edx

  nVSP = ptQVM->nVSP;
  QVM_nOldSP = ptQVM->nSP;
  QVM_nOldVSP = nVSP;
  return ptQVM;
}

// source: c/0/qvm.c:249  [anchor-hash]
struct QVM_s *__cdecl QVM_RestoreSP(struct QVM_s *ptQVM)
{
  int v1; // edx

  v1 = QVM_nOldVSP;
  ptQVM->nSP = QVM_nOldSP;
  ptQVM->nVSP = v1;
  return ptQVM;
}

// source: c/0/qvm.c:321  [anchor-callee]
int __cdecl QVM_Pop(
        struct QVM_s *ptQVM,
        void *pxData,
        int *pnDataSize,
        int *pnDataType)
{
  int v4; // edx
  int nVSP; // edx
  int v6; // ecx
  int v7; // edx
  int v8; // edx
  int *v9; // esi

  if ( pnDataType )
    *pnDataType = ptQVM->anOperandStackDataType[ptQVM->nSP];
  v4 = ptQVM->anOperandStackDataType[ptQVM->nSP];
  if ( v4 == 1 || v4 == 2 || v4 == 5 )
    goto LABEL_9;
  if ( v4 != 3 && v4 != 4 )
  {
    if ( v4 == 6 )
    {
LABEL_9:
      if ( pxData )
        *(_DWORD *)pxData = ptQVM->anOperandStack[ptQVM->nVSP];
      nVSP = ptQVM->nVSP;
      v6 = 4;
      ++ptQVM->nSP;
      v7 = nVSP + 1;
      goto LABEL_16;
    }
    if ( v4 != 7 )
    {
      LDebug_Error("Unknown data type.");
      abort();
    }
  }
  if ( pxData )
    *(_DWORD *)pxData = &ptQVM->anOperandStack[ptQVM->nVSP + 1];
  v8 = ptQVM->nVSP;
  v9 = &ptQVM->anOperandStack[v8];
  v6 = *v9 + 1;
  ++ptQVM->nSP;
  v7 = v8 + *v9 + 1;
LABEL_16:
  ptQVM->nVSP = v7;
  if ( pnDataSize )
    *pnDataSize = v6;
  return 1;
}

// source: c/0/qvm.c:424  [anchor-callee]
struct QVM_s *__cdecl QVM_PushInteger(struct QVM_s *ptQVM, int nValue)
{
  int nSP; // ecx
  int *anOperandStackDataType; // edx
  int nVSP; // ecx
  int *anOperandStack; // edx

  nSP = ptQVM->nSP;
  --ptQVM->nVSP;
  anOperandStackDataType = ptQVM->anOperandStackDataType;
  ptQVM->nSP = --nSP;
  anOperandStackDataType[nSP] = 1;
  nVSP = ptQVM->nVSP;
  anOperandStack = ptQVM->anOperandStack;
  anOperandStack[nVSP] = nValue;
  return (struct QVM_s *)nValue;
}

// source: c/0/qvm.c:446  [size]
struct QVM_s *__cdecl QVM_PushIdentifierContext(struct QVM_s *ptQVM, void *pxContext)
{
  int nSP; // ecx
  int *anOperandStackDataType; // edx
  int nVSP; // ecx
  int *anOperandStack; // edx

  nSP = ptQVM->nSP;
  --ptQVM->nVSP;
  anOperandStackDataType = ptQVM->anOperandStackDataType;
  ptQVM->nSP = --nSP;
  anOperandStackDataType[nSP] = 6;
  nVSP = ptQVM->nVSP;
  anOperandStack = ptQVM->anOperandStack;
  anOperandStack[nVSP] = (int)pxContext;
  return (struct QVM_s *)pxContext;
}

// source: c/0/qvm.c:469  [size]
struct QVM_s *__cdecl QVM_PushAddress(struct QVM_s *ptQVM, int nValue)
{
  int nSP; // ecx
  int *anOperandStackDataType; // edx
  int nVSP; // ecx
  int *anOperandStack; // edx

  nSP = ptQVM->nSP;
  --ptQVM->nVSP;
  anOperandStackDataType = ptQVM->anOperandStackDataType;
  ptQVM->nSP = --nSP;
  anOperandStackDataType[nSP] = 5;
  nVSP = ptQVM->nVSP;
  anOperandStack = ptQVM->anOperandStack;
  anOperandStack[nVSP] = nValue;
  return (struct QVM_s *)nValue;
}

// source: c/0/qvm.c:491  [anchor-mhash]
struct QVM_s *__cdecl QVM_PushFloat(struct QVM_s *ptQVM, float vValue)
{
  int nSP; // ecx
  int *anOperandStackDataType; // edx

  nSP = ptQVM->nSP;
  --ptQVM->nVSP;
  anOperandStackDataType = ptQVM->anOperandStackDataType;
  ptQVM->nSP = --nSP;
  anOperandStackDataType[nSP] = 2;
  *(float *)&ptQVM->anOperandStack[ptQVM->nVSP] = vValue;
  return ptQVM;
}

// source: c/0/qvm.c:513  [anchor-callee]
struct QVM_s *__cdecl QVM_PushString(struct QVM_s *ptQVM, char *zString, int nStringType)
{
  unsigned int v4; // ecx
  int *anOperandStackDataType; // edi
  int v6; // edx
  int *anOperandStack; // edi
  unsigned int v8; // ecx
  int v9; // edx
  int v10; // edx
  struct QVM_s *result; // eax

  v4 = strlen(zString);
  anOperandStackDataType = ptQVM->anOperandStackDataType;
  v6 = ptQVM->nSP - 1;
  ptQVM->nSP = v6;
  anOperandStackDataType[v6] = nStringType;
  anOperandStack = ptQVM->anOperandStack;
  v8 = ((v4 + 4) & 0xFFFFFFFC) >> 2;
  v9 = ptQVM->nVSP - v8;
  ptQVM->nVSP = v9;
  strcpy((char *)&anOperandStack[v9], zString);
  v10 = ptQVM->nVSP - 1;
  ptQVM->nVSP = v10;
  result = (struct QVM_s *)ptQVM->anOperandStack;
  *((_DWORD *)&result->anInstruction + v10) = v8;
  return result;
}

// source: c/0/qvm.c:542  [anchor-callee]
int __cdecl QVM_PopIdentifier(struct QVM_s *ptQVM, struct ScriptSymbol_s **pptScriptSymbol)
{
  struct QVM_s *v2; // ebp
  int v3; // eax
  char *v5; // esi
  int nPC; // edx
  int nStringSize; // [esp+4h] [ebp-4h] BYREF

  v2 = ptQVM;
  v3 = ptQVM->anOperandStackDataType[ptQVM->nSP];
  if ( v3 == 6 )
    return QVM_Pop(ptQVM, pptScriptSymbol, nullptr, nullptr);
  if ( v3 == 4 )
  {
    QVM_PopString(ptQVM, (char **)&ptQVM, &nStringSize, 4);
    v5 = (char *)ptQVM;
    if ( Symbol_Find((char *)ptQVM, pptScriptSymbol) )
      return 1;
    nPC = v2->nPC;
    v2->nError = 7;
    v2->nErrorPC = nPC;
    QVM_PushString(v2, v5, 4);
    strcpy(v2->zErrorParam, v5);
  }
  return 0;
}

// source: c/0/qvm.c:594  [anchor-callee]
int __cdecl QVM_PopString(
        struct QVM_s *ptQVM,
        char **pzString,
        int *pnStringSize,
        int nStringType)
{
  int v4; // ecx
  char *v6; // eax
  int nStringSize; // [esp+0h] [ebp-4h] BYREF

  nStringSize = v4;
  if ( ptQVM->anOperandStackDataType[ptQVM->nSP] == nStringType )
  {
    QVM_Pop(ptQVM, pzString, &nStringSize, nullptr);
    *pnStringSize = &(*pzString)[strlen(*pzString) + 1] - *pzString;
    return 1;
  }
  else if ( QVM_PopIdentifier(ptQVM, (struct ScriptSymbol_s **)&nStringType)
         && (!*(_DWORD *)nStringType || *(_DWORD *)nStringType == 2) )
  {
    if ( *(_DWORD *)(nStringType + 4) == 3 )
    {
      v6 = *(char **)(nStringType + 24);
      *pzString = v6;
      *pnStringSize = strlen(v6) + 1;
    }
    return 1;
  }
  else
  {
    *pzString = nullptr;
    *pnStringSize = 0;
    return 0;
  }
}

// source: c/0/qvm.c:672  [anchor-callee]
int __cdecl QVM_PopNumeric(struct QVM_s *ptQVM, int *pnValue, float *pvValue)
{
  #pragma pack(push, 1)
  union
  {
    struct { __int64 ptScriptSymbol; };
    struct { char igi2_o1[8]; struct Result_s tResult; };
    struct { char igi2_o2[32]; _BYTE v12[28]; };
    char igi2_extent[60];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v3; // ecx
  int v5; // ebx
  void *v6; // eax
  int v7; // ebx
  double nResult; // st7
  double vResult; // st6

  v3 = ptQVM->anOperandStackDataType[ptQVM->nSP];
  if ( v3 == 1 )
  {
    QVM_Pop(ptQVM, pnValue, nullptr, nullptr);
    *pvValue = (float)*pnValue;
    return 1;
  }
  else if ( v3 == 2 )
  {
    QVM_Pop(ptQVM, pvValue, nullptr, nullptr);
    *pnValue = (__int64)*pvValue;
    return 2;
  }
  else if ( QVM_PopIdentifier(ptQVM, (struct ScriptSymbol_s **)&igi2_frame.ptScriptSymbol)
         && ((v5 = igi2_frame.ptScriptSymbol, !*(_DWORD *)igi2_frame.ptScriptSymbol) || *(_DWORD *)igi2_frame.ptScriptSymbol == 2) )
  {
    v6 = (void *)(*(int (__cdecl **)(_BYTE *, _DWORD, _DWORD))(igi2_frame.ptScriptSymbol + 16))(
                         igi2_frame.v12,
                         *(_DWORD *)(igi2_frame.ptScriptSymbol + 24),
                         0);
    v7 = *(_DWORD *)(v5 + 4);
    qmemcpy(&igi2_frame.tResult, v6, sizeof(igi2_frame.tResult));
    if ( v7 == 1 )
    {
      nResult = (double)igi2_frame.tResult.nResult;
      *pnValue = igi2_frame.tResult.nResult;
      *pvValue = nResult;
      return 1;
    }
    else if ( v7 == 2 )
    {
      vResult = igi2_frame.tResult.vResult;
      igi2_frame.ptScriptSymbol = (__int64)igi2_frame.tResult.vResult;
      *pnValue = (__int64)igi2_frame.tResult.vResult;
      *pvValue = vResult;
      return 2;
    }
    else
    {
      return 0;
    }
  }
  else
  {
    return 0;
  }
}

// source: c/0/qvm.c:742  [anchor-mhash]
int __cdecl QVM_PopTwoNumeric(
        struct QVM_s *ptQVM,
        int *pnLeft,
        int *pnRight,
        float *pvLeft,
        float *pvRight)
{
  int result; // eax
  BOOL v6; // edi
  double v7; // st7
  int nSP; // eax
  int *anOperandStackDataType; // ecx
  int v10; // eax
  int v11; // ecx
  int *v12; // edx

  result = QVM_PopNumeric(ptQVM, pnLeft, pvLeft);
  if ( result )
  {
    v6 = result == 2;
    result = QVM_PopNumeric(ptQVM, pnRight, pvRight);
    if ( result )
    {
      if ( v6 )
        return 2;
    }
    else
    {
      if ( v6 )
      {
        v7 = *pvLeft;
        nSP = ptQVM->nSP;
        --ptQVM->nVSP;
        anOperandStackDataType = ptQVM->anOperandStackDataType;
        ptQVM->nSP = --nSP;
        anOperandStackDataType[nSP] = 2;
        *(float *)&ptQVM->anOperandStack[ptQVM->nVSP] = v7;
      }
      else
      {
        v10 = *pnLeft;
        v11 = ptQVM->nSP;
        --ptQVM->nVSP;
        v12 = ptQVM->anOperandStackDataType;
        ptQVM->nSP = --v11;
        v12[v11] = 1;
        ptQVM->anOperandStack[ptQVM->nVSP] = v10;
      }
      return 0;
    }
  }
  return result;
}

// source: c/0/qvm.c:790  [anchor-mhash]
char *__cdecl QVM_GetStringFromQVMStringTable(
        struct QVMStringTable_s *ptQVMStringTable,
        int nIndex)
{
  int nOffset; // [esp+0h] [ebp-4h]

  if ( nIndex >= ptQVMStringTable->nNextFree )
    return nullptr;
  nOffset = ptQVMStringTable->anStringOffset[nIndex];
  if ( nOffset >= ptQVMStringTable->nNextFreeOffset )
    return nullptr;
  else
    return &ptQVMStringTable->zBuffer[nOffset];
}

// source: c/0/qvm.c:820  [anchor-mhash]
void __cdecl QVM_OpBranch(struct QVM_s *ptQVM, void *pxUnused, int eOpCode, int eEvent)
{
  #pragma pack(push, 1)
  union
  {
    struct { int nValue; };
    struct { char igi2_o1[4]; float vValue; };
    char igi2_extent[8];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int nPC; // ecx
  unsigned __int8 *v6; // eax
  unsigned __int8 v7; // dl
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // edx
  struct QVM_s *ptQVMa = *(struct QVM_s * *)&ptQVM; // [esp+10h] [ebp+4h] ARGSLOT

  nPC = ptQVM->nPC;
  v6 = &ptQVM->anInstruction[nPC];
  LOWORD(ptQVMa) = *(_WORD *)(v6 + 1);
  BYTE2(ptQVMa) = v6[3];
  v7 = v6[4];
  v8 = *v6 - 3;
  HIBYTE(ptQVMa) = v7;
  if ( v8 )
  {
    v9 = v8 - 1;
    if ( v9 )
    {
      if ( v9 != 1 )
      {
        ptQVM->nErrorPC = nPC;
        ptQVM->nError = 3;
        ptQVM->nPC = nPC + 5;
        return;
      }
      v10 = QVM_PopNumeric(ptQVM, &igi2_frame.nValue, &igi2_frame.vValue);
      if ( v10 == 1 )
      {
        if ( !igi2_frame.nValue )
        {
          ptQVM->nPC += 5;
          return;
        }
        goto LABEL_18;
      }
      if ( v10 == 2 )
      {
        if ( igi2_frame.vValue == 0.0 )
        {
          ptQVM->nPC += 5;
          return;
        }
        goto LABEL_18;
      }
    }
    else
    {
      v11 = QVM_PopNumeric(ptQVM, &igi2_frame.nValue, &igi2_frame.vValue);
      if ( v11 == 1 )
      {
        if ( igi2_frame.nValue )
        {
          ptQVM->nPC += 5;
          return;
        }
        goto LABEL_18;
      }
      if ( v11 == 2 )
      {
        if ( igi2_frame.vValue != 0.0 )
        {
          ptQVM->nPC += 5;
          return;
        }
        goto LABEL_18;
      }
    }
    v12 = ptQVM->nPC;
    ptQVM->nError = 12;
    ptQVM->nErrorPC = v12;
    ptQVM->nPC = v12 + 5;
    return;
  }
LABEL_18:
  ptQVM->nPC += (int)&ptQVMa->nProgamSize + 1;
}

// source: c/0/qvm.c:902  [anchor-refs]
struct QVM_s *__cdecl QVM_OpPop(struct QVM_s *ptQVM)
{
  struct QVM_s *result; // eax
  int nSP; // ecx
  int v3; // edx
  int *anOperandStack; // edx

  result = ptQVM;
  nSP = ptQVM->nSP;
  v3 = ptQVM->anOperandStackDataType[nSP];
  if ( v3 == 1 || v3 == 2 || v3 == 5 )
    goto LABEL_7;
  if ( v3 != 3 && v3 != 4 )
  {
    if ( v3 == 6 )
    {
LABEL_7:
      ptQVM->nSP = nSP + 1;
      ++ptQVM->nVSP;
      ++ptQVM->nPC;
      return result;
    }
    if ( v3 != 7 )
    {
      LDebug_Error("Unknown data type.");
      abort();
    }
  }
  anOperandStack = ptQVM->anOperandStack;
  ptQVM->nSP = nSP + 1;
  ptQVM->nVSP += anOperandStack[ptQVM->nVSP] + 1;
  ++ptQVM->nPC;
  return result;
}

// source: c/0/qvm.c:917  [anchor-mhash]
void __cdecl QVM_OpCallFunction(struct QVM_s *ptQVM, void *pxUnused, int eOpCode, int eEvent)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v26; };
    struct { char igi2_o1[4]; int nSP; };
    struct { char igi2_o2[8]; int nVSP; };
    struct { char igi2_o3[12]; struct QVMArgList_s tArgList; };
    struct { char igi2_o4[32]; struct Result_s tResult; };
    struct { char igi2_o5[56]; char v31[24]; };
    char igi2_extent[80];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QVM_s *v4; // ebx
  int v5; // ecx
  struct QVM_s *v6; // ebp
  int nPC; // eax
  unsigned __int8 v8; // dl
  unsigned __int8 *v9; // eax
  unsigned __int8 v10; // cl
  unsigned __int8 v11; // dl
  unsigned __int8 v12; // cl
  int v13; // edx
  int v14; // ecx
  void *v15; // esi
  int nError; // eax
  int v17; // edx
  int nProgamSize; // ebp
  int v19; // eax
  int *anOperandStackDataType; // ecx
  double vResult; // st7
  int v22; // edx
  int v23; // eax
  int v24; // ecx
  int v25; // edx

  v4 = ptQVM;
  v5 = ptQVM->nVSP;
  QVM_nOldSP = ptQVM->nSP;
  QVM_nOldVSP = v5;
  if ( QVM_PopIdentifier(ptQVM, (struct ScriptSymbol_s **)&ptQVM) )
  {
    v6 = ptQVM;
    if ( ptQVM->anInstruction == (unsigned __int8 *)1 )
    {
      nPC = v4->nPC;
      v8 = v4->anInstruction[nPC + 1];
      igi2_frame.v26 = nPC;
      v9 = &v4->anInstruction[nPC];
      v10 = v9[2];
      LOBYTE(ptQVM) = v8;
      v11 = v9[3];
      BYTE1(ptQVM) = v10;
      v12 = v9[4];
      BYTE2(ptQVM) = v11;
      v13 = v4->nSP;
      HIBYTE(ptQVM) = v12;
      v14 = v4->nVSP;
      igi2_frame.nSP = v13;
      igi2_frame.tArgList.pnArgTable = v9 + 5;
      igi2_frame.tArgList.tArgList.nArguments = (int)ptQVM;
      igi2_frame.nVSP = v14;
      igi2_frame.tArgList.tArgList.aptExpression = nullptr;
      igi2_frame.tArgList.tArgList.isQVM = 1;
      igi2_frame.tArgList.ptQVM = v4;
      v15 = (void *)((int (__cdecl *)(char *, int, struct QVMArgList_s *))v6->nErrorPC)(igi2_frame.v31, v6->nVSP, &igi2_frame.tArgList);
      nError = v4->nError;
      qmemcpy(&igi2_frame.tResult, v15, sizeof(igi2_frame.tResult));
      if ( !nError )
      {
        v17 = igi2_frame.v26 + 4 * (_DWORD)ptQVM + 5;
        v4->isBreak = 0;
        v4->nPC = v17;
        v4->nSP = igi2_frame.nSP;
        v4->nVSP = igi2_frame.nVSP;
        nProgamSize = v6->nProgamSize;
        if ( nProgamSize == 3 )
        {
          QVM_PushString(v4, igi2_frame.tResult.zResult, 3);
        }
        else
        {
          v19 = igi2_frame.nSP - 1;
          v4->nVSP = igi2_frame.nVSP - 1;
          anOperandStackDataType = v4->anOperandStackDataType;
          v4->nSP = igi2_frame.nSP - 1;
          if ( nProgamSize == 2 )
          {
            vResult = igi2_frame.tResult.vResult;
            anOperandStackDataType[v19] = 2;
            *(float *)&v4->anOperandStack[v4->nVSP] = vResult;
          }
          else
          {
            anOperandStackDataType[v19] = 1;
            v4->anOperandStack[v4->nVSP] = igi2_frame.tResult.nResult;
          }
        }
      }
      return;
    }
    v22 = v4->nPC;
    v4->nError = 9;
    v4->nErrorPC = v22;
  }
  if ( !v4->nError )
  {
    v23 = v4->nPC;
    v24 = QVM_nOldSP;
    v25 = QVM_nOldVSP;
    v4->nError = 10;
    v4->nErrorPC = v23;
    v4->nSP = v24;
    v4->nVSP = v25;
  }
}

// source: c/0/qvm.c:1005  [anchor-mhash]
void __cdecl QVM_OpAssign(struct QVM_s *ptQVM, void *pxUnused, int eOpCode, int eEvent)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v16; };
    struct { char igi2_o1[16]; float vValue; };
    struct { char igi2_o2[20]; int nDataSize; };
    struct { char igi2_o3[24]; __int64 zValue; };
    char igi2_extent[32];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QVM_s *v4; // edi
  int nVSP; // ecx
  int v6; // ebx
  int v7; // esi
  int v8; // eax
  struct QVM_s *v9; // eax
  int v10; // edx
  char v11; // al
  int v12; // eax
  float v13; // ecx
  int v14; // edx
  int v15; // eax

  v4 = ptQVM;
  nVSP = ptQVM->nVSP;
  QVM_nOldSP = ptQVM->nSP;
  QVM_nOldVSP = nVSP;
  v6 = QVM_PopNumeric(ptQVM, (int *)&ptQVM, &igi2_frame.vValue);
  if ( v6 || (v6 = QVM_PopString(v4, (char **)&igi2_frame.zValue, &igi2_frame.nDataSize, 3) != 0 ? 3 : 0) != 0 )
  {
    if ( QVM_PopIdentifier(v4, (struct ScriptSymbol_s **)&igi2_frame.nDataSize) )
    {
      v7 = igi2_frame.nDataSize;
      if ( *(_DWORD *)igi2_frame.nDataSize )
      {
        v4->nError = 8;
        goto LABEL_27;
      }
      v8 = *(_DWORD *)(igi2_frame.nDataSize + 4);
      if ( v8 == 1 )
      {
        if ( v6 == 1 )
        {
          if ( *(_DWORD *)(igi2_frame.nDataSize + 12) == 1 )
          {
            v11 = (char)ptQVM;
            **(_BYTE **)(igi2_frame.nDataSize + 24) = (_BYTE)ptQVM;
            v10 = v11;
          }
          else
          {
            v9 = ptQVM;
            if ( *(_DWORD *)(igi2_frame.nDataSize + 12) != 2 )
            {
              **(_DWORD **)(igi2_frame.nDataSize + 24) = ptQVM;
              QVM_PushInteger(v4, (int)v9);
LABEL_13:
              ++v4->nPC;
              return;
            }
            **(_WORD **)(igi2_frame.nDataSize + 24) = (_WORD)ptQVM;
            v10 = (__int16)v9;
          }
          QVM_PushInteger(v4, v10);
          goto LABEL_13;
        }
        if ( v6 == 2 )
        {
          igi2_frame.zValue = (__int64)igi2_frame.vValue;
          v12 = igi2_frame.zValue;
          **(_DWORD **)(igi2_frame.nDataSize + 24) = igi2_frame.zValue;
          QVM_PushInteger(v4, v12);
          goto LABEL_13;
        }
      }
      else if ( v8 == 2 )
      {
        if ( v6 == 1 )
        {
          *(double *)*(_DWORD *)(igi2_frame.nDataSize + 24) = (double)(int)ptQVM;
          igi2_frame.v16 = (float)(int)ptQVM;
          QVM_PushFloat(v4, igi2_frame.v16);
          ++v4->nPC;
          return;
        }
        if ( v6 == 2 )
        {
          v13 = igi2_frame.vValue;
          *(double *)*(_DWORD *)(igi2_frame.nDataSize + 24) = igi2_frame.vValue;
          QVM_PushFloat(v4, v13);
          ++v4->nPC;
          return;
        }
      }
      else if ( v8 == 3 && v6 == 3 )
      {
        strncpy(*(char **)(igi2_frame.nDataSize + 24), (char *)igi2_frame.zValue, *(_DWORD *)(igi2_frame.nDataSize + 12) - 1);
        *(_BYTE *)(*(_DWORD *)(v7 + 12) + *(_DWORD *)(v7 + 24) - 1) = 0;
        QVM_PushString(v4, *(char **)(v7 + 24), 3);
        ++v4->nPC;
        return;
      }
    }
  }
  if ( v4->nError )
    return;
  v4->nError = 11;
LABEL_27:
  v14 = QVM_nOldSP;
  v15 = QVM_nOldVSP;
  v4->nErrorPC = v4->nPC;
  v4->nSP = v14;
  v4->nVSP = v15;
}

// source: c/0/qvm.c:1125  [anchor-mhash]
void __cdecl QVM_OpBinary(struct QVM_s *ptQVM, void *pxUnused, int eOpCode, int eEvent)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v20; };
    struct { float v21; };
    struct { float v22; };
    struct { float v23; };
    struct { char igi2_o4[16]; int pnRight; };
    struct { char igi2_o5[20]; char *pvLeft; };
    struct { char igi2_o6[24]; struct QVM_s ptQVMa; };
    char igi2_extent[4132];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int nVSP; // ecx
  int v5; // eax
  bool v6; // zf
  int nPC; // eax
  int v8; // ecx
  int v9; // edx
  int v10; // eax
  int v11; // eax
  int v12; // edx
  int v13; // eax
  char *p_nStackElements; // ebx
  char *v15; // eax
  char *v16; // edx
  char v17; // cl
  int v18; // esi
  int v19; // eax

  nVSP = ptQVM->nVSP;
  QVM_nOldSP = ptQVM->nSP;
  QVM_nOldVSP = nVSP;
  v5 = QVM_PopTwoNumeric(ptQVM, (int *)&igi2_frame.ptQVMa, &igi2_frame.ptQVMa.nProgamSize, (float *)&igi2_frame.pvLeft, (float *)&igi2_frame.pnRight);
  if ( v5 )
  {
    v6 = v5 == 1;
    nPC = ptQVM->nPC;
    if ( v6 )
    {
      switch ( ptQVM->anInstruction[nPC] )
      {
        case 0x19u:
          QVM_PushInteger(ptQVM, (int)&igi2_frame.ptQVMa.anInstruction[igi2_frame.ptQVMa.nProgamSize]);
          ++ptQVM->nPC;
          break;
        case 0x1Au:
          QVM_PushInteger(ptQVM, igi2_frame.ptQVMa.nProgamSize - (unsigned int)igi2_frame.ptQVMa.anInstruction);
          ++ptQVM->nPC;
          break;
        case 0x1Bu:
          QVM_PushInteger(ptQVM, igi2_frame.ptQVMa.nProgamSize * (int)igi2_frame.ptQVMa.anInstruction);
          ++ptQVM->nPC;
          break;
        case 0x1Cu:
          QVM_PushInteger(ptQVM, igi2_frame.ptQVMa.nProgamSize / (int)igi2_frame.ptQVMa.anInstruction);
          ++ptQVM->nPC;
          break;
        case 0x1Du:
          QVM_PushInteger(ptQVM, igi2_frame.ptQVMa.nProgamSize << SLOBYTE(igi2_frame.ptQVMa.anInstruction));
          ++ptQVM->nPC;
          break;
        case 0x1Eu:
          QVM_PushInteger(ptQVM, igi2_frame.ptQVMa.nProgamSize >> SLOBYTE(igi2_frame.ptQVMa.anInstruction));
          ++ptQVM->nPC;
          break;
        case 0x1Fu:
          QVM_PushInteger(ptQVM, igi2_frame.ptQVMa.nProgamSize & (int)igi2_frame.ptQVMa.anInstruction);
          ++ptQVM->nPC;
          break;
        case 0x20u:
          QVM_PushInteger(ptQVM, igi2_frame.ptQVMa.nProgamSize | (int)igi2_frame.ptQVMa.anInstruction);
          ++ptQVM->nPC;
          break;
        case 0x21u:
          QVM_PushInteger(ptQVM, igi2_frame.ptQVMa.nProgamSize ^ (int)igi2_frame.ptQVMa.anInstruction);
          ++ptQVM->nPC;
          break;
        case 0x22u:
          if ( igi2_frame.ptQVMa.nProgamSize && igi2_frame.ptQVMa.anInstruction )
            goto LABEL_15;
          goto LABEL_33;
        case 0x23u:
          if ( !igi2_frame.ptQVMa.nProgamSize && !igi2_frame.ptQVMa.anInstruction )
            goto LABEL_18;
          goto LABEL_15;
        case 0x24u:
          QVM_PushInteger(ptQVM, (unsigned __int8 *)igi2_frame.ptQVMa.nProgamSize == igi2_frame.ptQVMa.anInstruction);
          ++ptQVM->nPC;
          break;
        case 0x25u:
          QVM_PushInteger(ptQVM, (unsigned __int8 *)igi2_frame.ptQVMa.nProgamSize != igi2_frame.ptQVMa.anInstruction);
          ++ptQVM->nPC;
          break;
        case 0x26u:
          QVM_PushInteger(ptQVM, igi2_frame.ptQVMa.nProgamSize < (int)igi2_frame.ptQVMa.anInstruction);
          ++ptQVM->nPC;
          break;
        case 0x27u:
          QVM_PushInteger(ptQVM, igi2_frame.ptQVMa.nProgamSize <= (int)igi2_frame.ptQVMa.anInstruction);
          ++ptQVM->nPC;
          break;
        case 0x28u:
          QVM_PushInteger(ptQVM, igi2_frame.ptQVMa.nProgamSize > (int)igi2_frame.ptQVMa.anInstruction);
          ++ptQVM->nPC;
          break;
        case 0x29u:
          QVM_PushInteger(ptQVM, igi2_frame.ptQVMa.nProgamSize >= (int)igi2_frame.ptQVMa.anInstruction);
          ++ptQVM->nPC;
          break;
        default:
          goto LABEL_25;
      }
    }
    else
    {
      switch ( ptQVM->anInstruction[nPC] )
      {
        case 0x19u:
          igi2_frame.v22 = *(float *)&igi2_frame.pvLeft + *(float *)&igi2_frame.pnRight;
          QVM_PushFloat(ptQVM, igi2_frame.v22);
          ++ptQVM->nPC;
          return;
        case 0x1Au:
          igi2_frame.v23 = *(float *)&igi2_frame.pnRight - *(float *)&igi2_frame.pvLeft;
          QVM_PushFloat(ptQVM, igi2_frame.v23);
          ++ptQVM->nPC;
          return;
        case 0x1Bu:
          igi2_frame.v20 = *(float *)&igi2_frame.pvLeft * *(float *)&igi2_frame.pnRight;
          QVM_PushFloat(ptQVM, igi2_frame.v20);
          ++ptQVM->nPC;
          return;
        case 0x1Cu:
          igi2_frame.v21 = *(float *)&igi2_frame.pnRight / *(float *)&igi2_frame.pvLeft;
          QVM_PushFloat(ptQVM, igi2_frame.v21);
          ++ptQVM->nPC;
          return;
        case 0x1Du:
        case 0x1Eu:
        case 0x1Fu:
        case 0x20u:
        case 0x21u:
          goto LABEL_50;
        case 0x22u:
          if ( *(float *)&igi2_frame.pnRight == 0.0 || *(float *)&igi2_frame.pvLeft == 0.0 )
            goto LABEL_33;
          goto LABEL_15;
        case 0x23u:
          if ( *(float *)&igi2_frame.pnRight == 0.0 && *(float *)&igi2_frame.pvLeft == 0.0 )
          {
LABEL_18:
            QVM_PushInteger(ptQVM, 0);
            ++ptQVM->nPC;
          }
          else
          {
LABEL_15:
            QVM_PushInteger(ptQVM, 1);
            ++ptQVM->nPC;
          }
          return;
        case 0x24u:
          if ( *(float *)&igi2_frame.pnRight != *(float *)&igi2_frame.pvLeft )
            goto LABEL_33;
          v11 = 1;
          goto LABEL_34;
        case 0x25u:
          if ( *(float *)&igi2_frame.pnRight == *(float *)&igi2_frame.pvLeft )
            goto LABEL_33;
          v11 = 1;
          goto LABEL_34;
        case 0x26u:
          if ( *(float *)&igi2_frame.pnRight >= (double)*(float *)&igi2_frame.pvLeft )
            goto LABEL_33;
          v11 = 1;
          goto LABEL_34;
        case 0x27u:
          if ( *(float *)&igi2_frame.pnRight > (double)*(float *)&igi2_frame.pvLeft )
            goto LABEL_33;
          v11 = 1;
          goto LABEL_34;
        case 0x28u:
          if ( *(float *)&igi2_frame.pnRight <= (double)*(float *)&igi2_frame.pvLeft )
            goto LABEL_33;
          v11 = 1;
          goto LABEL_34;
        case 0x29u:
          if ( *(float *)&igi2_frame.pnRight < (double)*(float *)&igi2_frame.pvLeft )
LABEL_33:
            v11 = 0;
          else
            v11 = 1;
LABEL_34:
          QVM_PushInteger(ptQVM, v11);
          ++ptQVM->nPC;
          break;
        default:
LABEL_25:
          v8 = QVM_nOldSP;
          v9 = QVM_nOldVSP;
          ptQVM->nErrorPC = nPC;
          v10 = ptQVM->nPC + 1;
          ptQVM->nError = 3;
          ptQVM->nSP = v8;
          ptQVM->nVSP = v9;
          ptQVM->nPC = v10;
          break;
      }
    }
  }
  else
  {
    igi2_frame.ptQVMa.anInstruction = nullptr;
    if ( QVM_PopString(ptQVM, &igi2_frame.pvLeft, &igi2_frame.ptQVMa.nStackSize, 3)
      && QVM_PopString(ptQVM, (char **)&igi2_frame.pnRight, &igi2_frame.ptQVMa.nProgamSize, 3) )
    {
      nPC = ptQVM->nPC;
      switch ( ptQVM->anInstruction[nPC] )
      {
        case 0x19u:
          if ( (unsigned int)(igi2_frame.ptQVMa.nStackSize + igi2_frame.ptQVMa.nProgamSize) <= 0x1000 )
          {
            p_nStackElements = (char *)&igi2_frame.ptQVMa.nStackElements;
          }
          else
          {
            igi2_frame.ptQVMa.anInstruction = (unsigned __int8 *)Mem_AllocFn(igi2_frame.ptQVMa.nStackSize + igi2_frame.ptQVMa.nProgamSize, 4);
            p_nStackElements = (char *)igi2_frame.ptQVMa.anInstruction;
          }
          v15 = (char *)igi2_frame.pnRight;
          v16 = &p_nStackElements[-igi2_frame.pnRight];
          do
          {
            v17 = *v15;
            v15[(_DWORD)v16] = *v15;
            ++v15;
          }
          while ( v17 );
          strcat(p_nStackElements, igi2_frame.pvLeft);
          QVM_PushString(ptQVM, p_nStackElements, 3);
          if ( igi2_frame.ptQVMa.anInstruction )
          {
            v18 = *(_DWORD *)((int)(igi2_frame.ptQVMa.anInstruction - 4) & 0xFFFFFFFC);
            --Mem_nCurrentAllocations;
            Node_Remove((_DWORD **)v18);
            memset(*(void **)(v18 + 8), 0xCDu, *(_DWORD *)(v18 + 16));
            free((void *)v18);
          }
          goto LABEL_62;
        case 0x1Au:
        case 0x1Bu:
        case 0x1Cu:
        case 0x1Du:
        case 0x1Eu:
        case 0x1Fu:
        case 0x20u:
        case 0x21u:
        case 0x22u:
        case 0x23u:
LABEL_50:
          ptQVM->nErrorPC = nPC;
          goto LABEL_51;
        case 0x24u:
          QVM_PushInteger(ptQVM, strcmp((char *)igi2_frame.pnRight, igi2_frame.pvLeft) == 0);
          ++ptQVM->nPC;
          break;
        case 0x25u:
          QVM_PushInteger(ptQVM, strcmp((char *)igi2_frame.pnRight, igi2_frame.pvLeft) != 0);
          ++ptQVM->nPC;
          break;
        case 0x26u:
          QVM_PushInteger(ptQVM, strcmp((char *)igi2_frame.pnRight, igi2_frame.pvLeft) < 0);
          ++ptQVM->nPC;
          break;
        case 0x27u:
          QVM_PushInteger(ptQVM, strcmp((char *)igi2_frame.pnRight, igi2_frame.pvLeft) <= 0);
          ++ptQVM->nPC;
          break;
        case 0x28u:
          QVM_PushInteger(ptQVM, strcmp((char *)igi2_frame.pnRight, igi2_frame.pvLeft) > 0);
          ++ptQVM->nPC;
          break;
        case 0x29u:
          QVM_PushInteger(ptQVM, strcmp((char *)igi2_frame.pnRight, igi2_frame.pvLeft) >= 0);
          ++ptQVM->nPC;
          break;
        default:
          ptQVM->nErrorPC = nPC;
          v19 = ptQVM->nPC + 1;
          ptQVM->nError = 3;
          ptQVM->nPC = v19;
          break;
      }
    }
    else if ( ptQVM->nError )
    {
LABEL_62:
      ++ptQVM->nPC;
    }
    else
    {
      ptQVM->nErrorPC = ptQVM->nPC;
LABEL_51:
      v12 = QVM_nOldSP;
      ptQVM->nVSP = QVM_nOldVSP;
      v13 = ptQVM->nPC + 1;
      ptQVM->nError = 6;
      ptQVM->nSP = v12;
      ptQVM->nPC = v13;
    }
  }
}

// source: c/0/qvm.c:1401  [anchor-mhash]
void __cdecl QVM_OpUnary(struct QVM_s *ptQVM, void *pxUnused, int eOpCode, int eEvent)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v17; };
    struct { char igi2_o1[8]; int pnValue; };
    char igi2_extent[12];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QVM_s *v4; // esi
  int nVSP; // ecx
  int v6; // eax
  bool v7; // zf
  int nPC; // eax
  int v9; // ecx
  int v10; // edx
  int v11; // eax
  int v12; // ecx
  int v13; // eax
  int v14; // edx
  int v15; // eax
  int v16; // ecx

  v4 = ptQVM;
  nVSP = ptQVM->nVSP;
  QVM_nOldSP = ptQVM->nSP;
  QVM_nOldVSP = nVSP;
  v6 = QVM_PopNumeric(ptQVM, (int *)&ptQVM, (float *)&igi2_frame.pnValue);
  if ( v6 )
  {
    v7 = v6 == 1;
    nPC = v4->nPC;
    if ( v7 )
    {
      switch ( v4->anInstruction[nPC] )
      {
        case '+':
          QVM_PushInteger(v4, (int)ptQVM);
          ++v4->nPC;
          break;
        case ',':
          QVM_PushInteger(v4, -(int)ptQVM);
          ++v4->nPC;
          break;
        case '-':
          QVM_PushInteger(v4, ~(unsigned int)ptQVM);
          ++v4->nPC;
          break;
        case '.':
          QVM_PushInteger(v4, ptQVM == nullptr);
          ++v4->nPC;
          break;
        default:
          goto LABEL_12;
      }
    }
    else
    {
      switch ( v4->anInstruction[nPC] )
      {
        case '+':
          QVM_PushFloat(v4, *(float *)&igi2_frame.pnValue);
          ++v4->nPC;
          break;
        case ',':
          igi2_frame.v17 = -*(float *)&igi2_frame.pnValue;
          QVM_PushFloat(v4, igi2_frame.v17);
          ++v4->nPC;
          break;
        case '-':
        case '.':
          v9 = QVM_nOldSP;
          v10 = QVM_nOldVSP;
          v4->nErrorPC = nPC;
          v11 = v4->nPC + 1;
          v4->nError = 6;
          v4->nSP = v9;
          v4->nVSP = v10;
          v4->nPC = v11;
          break;
        default:
LABEL_12:
          v12 = QVM_nOldVSP;
          v4->nErrorPC = nPC;
          v4->nSP = QVM_nOldSP;
          v13 = v4->nPC + 1;
          v4->nError = 3;
          v4->nVSP = v12;
          v4->nPC = v13;
          break;
      }
    }
  }
  else if ( !v4->nError )
  {
    v14 = v4->nPC;
    v15 = QVM_nOldSP;
    v16 = QVM_nOldVSP;
    v4->nError = 6;
    v4->nErrorPC = v14;
    v4->nSP = v15;
    v4->nVSP = v16;
  }
}

// source: c/0/qvm.c:1487  [size]
void __cdecl QVM_OpPushOne(struct QVM_s *ptQVM, void *pxUnused, int eOpCode, int eEvent)
{
  int nSP; // edx

  nSP = ptQVM->nSP;
  --ptQVM->nVSP;
  ptQVM->nSP = --nSP;
  ptQVM->anOperandStackDataType[nSP] = 1;
  ptQVM->anOperandStack[ptQVM->nVSP] = 1;
  ++ptQVM->nPC;
}

// source: c/0/qvm.c:1504  [size]
void __cdecl QVM_OpPushZero(struct QVM_s *ptQVM, void *pxUnused, int eOpCode, int eEvent)
{
  int nSP; // edx

  nSP = ptQVM->nSP;
  --ptQVM->nVSP;
  ptQVM->nSP = --nSP;
  ptQVM->anOperandStackDataType[nSP] = 1;
  ptQVM->anOperandStack[ptQVM->nVSP] = 0;
  ++ptQVM->nPC;
}

// source: c/0/qvm.c:1521  [size]
void __cdecl QVM_OpPushMinusOne(struct QVM_s *ptQVM, void *pxUnused, int eOpCode, int eEvent)
{
  int nSP; // edx

  nSP = ptQVM->nSP;
  --ptQVM->nVSP;
  ptQVM->nSP = --nSP;
  ptQVM->anOperandStackDataType[nSP] = 1;
  ptQVM->anOperandStack[ptQVM->nVSP] = -1;
  ++ptQVM->nPC;
}

// source: c/0/qvm.c:1538  [anchor-mhash]
void __cdecl QVM_OpPushInteger8(struct QVM_s *ptQVM, void *pxUnused, int eOpCode, int eEvent)
{
  unsigned __int8 *v4; // ecx
  signed __int8 v5; // dl
  int v6; // ebx
  int v7; // esi
  int v8; // ecx
  int *anOperandStackDataType; // esi

  v4 = &ptQVM->anInstruction[ptQVM->nPC];
  v5 = v4[1];
  if ( *v4 != 9 )
  {
    LDebug_Error("Internal error.");
    abort();
  }
  v6 = ptQVM->nVSP - 1;
  v7 = ptQVM->nSP - 1;
  ptQVM->nSP = v7;
  v8 = v7;
  anOperandStackDataType = ptQVM->anOperandStackDataType;
  ptQVM->nVSP = v6;
  anOperandStackDataType[v8] = 1;
  ptQVM->anOperandStack[ptQVM->nVSP] = v5;
  ptQVM->nPC += 2;
}

// source: c/0/qvm.c:1571  [anchor-mhash]
struct QVM_s *__cdecl QVM_OpPushInteger16(struct QVM_s *ptQVM)
{
  struct QVM_s *result; // eax
  unsigned __int8 *v2; // ecx
  int v3; // esi
  int v4; // edx
  int v5; // ecx
  int *anOperandStackDataType; // edx
  __int16 ptQVMa = *(__int16 *)&ptQVM; // [esp+4h] [ebp+4h] ARGSLOT

  result = ptQVM;
  v2 = &ptQVM->anInstruction[ptQVM->nPC];
  ptQVMa = *(_WORD *)(v2 + 1);
  if ( *v2 != 10 )
  {
    LDebug_Error("Internal error.");
    abort();
  }
  v3 = result->nVSP - 1;
  v4 = result->nSP - 1;
  result->nSP = v4;
  v5 = v4;
  anOperandStackDataType = result->anOperandStackDataType;
  result->nVSP = v3;
  anOperandStackDataType[v5] = 1;
  result->anOperandStack[result->nVSP] = ptQVMa;
  result->nPC += 3;
  return result;
}

// source: c/0/qvm.c:1604  [anchor-mhash]
void __cdecl QVM_OpPushInteger(struct QVM_s *ptQVM, void *pxUnused, int eOpCode, int eEvent)
{
  unsigned __int8 *v5; // ecx
  unsigned __int8 v6; // dl
  unsigned __int8 v7; // cl
  int v8; // ecx
  int *v9; // edx
  int nSP; // ecx
  int *anOperandStackDataType; // edx
  struct QVM_s *ptQVMa = *(struct QVM_s * *)&ptQVM; // [esp+8h] [ebp+4h] ARGSLOT

  v5 = &ptQVM->anInstruction[ptQVM->nPC];
  LOWORD(ptQVMa) = *(_WORD *)(v5 + 1);
  BYTE2(ptQVMa) = v5[3];
  v6 = v5[4];
  v7 = *v5;
  HIBYTE(ptQVMa) = v6;
  if ( v7 == 8 )
  {
    nSP = ptQVM->nSP;
    --ptQVM->nVSP;
    anOperandStackDataType = ptQVM->anOperandStackDataType;
    ptQVM->nSP = --nSP;
    anOperandStackDataType[nSP] = 1;
  }
  else
  {
    if ( v7 != 12 )
    {
      LDebug_Error("Internal error.");
      abort();
    }
    v8 = ptQVM->nSP;
    --ptQVM->nVSP;
    v9 = ptQVM->anOperandStackDataType;
    ptQVM->nSP = --v8;
    v9[v8] = 5;
  }
  ptQVM->anOperandStack[ptQVM->nVSP] = (int)ptQVMa;
  ptQVM->nPC += 5;
}

// source: c/0/qvm.c:1641  [anchor-mhash]
void __cdecl QVM_OpData(struct QVM_s *ptQVM, void *pxUnused, int eOpCode, int eEvent)
{
  ptQVM->nPC += *(_DWORD *)&ptQVM->anInstruction[ptQVM->nPC + 1] + 5;
}

// source: c/0/qvm.c:1665  [anchor-mhash]
void __cdecl QVM_OpPushFloat(struct QVM_s *ptQVM, void *pxUnused, int eOpCode, int eEvent)
{
  int nSP; // edx
  struct QVM_s *ptQVMa = *(struct QVM_s * *)&ptQVM; // [esp+4h] [ebp+4h] ARGSLOT

  ptQVMa = *(struct QVM_s **)&ptQVM->anInstruction[ptQVM->nPC + 1];
  nSP = ptQVM->nSP;
  --ptQVM->nVSP;
  ptQVM->nSP = --nSP;
  ptQVM->anOperandStackDataType[nSP] = 2;
  ptQVM->anOperandStack[ptQVM->nVSP] = (int)ptQVMa;
  ptQVM->nPC += 5;
}

// source: c/0/qvm.c:1690  [anchor-refs]
void __cdecl QVM_OpPushString(struct QVM_s *ptQVM, void *pxUnused, int eOpCode, int eEvent)
{
  unsigned __int8 *v4; // eax
  int v5; // ecx

  v4 = &ptQVM->anInstruction[ptQVM->nPC];
  if ( *v4 == 13 )
  {
    v5 = 3;
  }
  else
  {
    if ( *v4 != 17 )
    {
      LDebug_Error("Unhandled opcode.");
      abort();
    }
    v5 = 4;
  }
  QVM_PushString(ptQVM, (char *)v4 + 1, v5);
  ptQVM->nPC = &ptQVM->anInstruction[ptQVM->nPC + 2 + strlen((char *)&ptQVM->anInstruction[ptQVM->nPC + 1])]
             - ptQVM->anInstruction;
}

// source: c/0/qvm.c:1721  [anchor-caller]
void __cdecl QVM_OpPushIndex(struct QVM_s *ptQVM, void *pxUnused, int eOpCode, int eEvent)
{
  int nPC; // edx
  unsigned __int8 *v6; // eax
  int v7; // eax
  int v8; // edi
  int v9; // eax
  char *v10; // ecx
  int v11; // edi
  int v12; // ebx
  struct ScriptSymbol_s *ptScriptSymbol; // ebp
  struct ScriptSymbolReference_s *v14; // eax
  _DWORD *v15; // eax
  struct ScriptSymbolReference_s *v16; // eax
  int v17; // ecx
  char *v18; // eax
  int v19; // esi
  char v20; // cl
  int v21; // eax
  char *v22; // edi
  struct QHashTable_s *v23; // ebp
  unsigned int v24; // eax
  struct ScriptSymbol_s *v25; // eax
  int v26; // edx
  int v27; // ecx
  int v28; // eax
  int *anOperandStackDataType; // ecx
  char *v30; // esi
  char *v31; // eax
  char v32; // cl
  int v33; // eax
  char *zSymbolName; // [esp+8h] [ebp-4h]
  int ptQVMa = *(int *)&ptQVM; // [esp+10h] [ebp+4h] ARGSLOT

  nPC = ptQVM->nPC;
  v6 = &ptQVM->anInstruction[nPC];
  switch ( *v6 )
  {
    case 0xEu:
      v7 = *(_DWORD *)(v6 + 1);
      v8 = 4;
      goto LABEL_3;
    case 0xFu:
      v7 = v6[1];
      v8 = 1;
      goto LABEL_3;
    case 0x10u:
      v7 = *(unsigned __int16 *)(v6 + 1);
      v8 = 2;
LABEL_3:
      if ( v7 < ptQVM->tStringTable.nNextFree
        && (v9 = ptQVM->tStringTable.anStringOffset[v7], v9 < ptQVM->tStringTable.nNextFreeOffset)
        && (v10 = &ptQVM->tStringTable.zBuffer[v9]) != nullptr )
      {
        QVM_PushString(ptQVM, v10, 3);
        ptQVM->nPC += v8 + 1;
      }
      else
      {
        ptQVM->nError = 15;
        ptQVM->nErrorPC = nPC;
      }
      return;
    case 0x12u:
      v11 = *(_DWORD *)(v6 + 1);
      ptQVMa = 4;
      goto LABEL_12;
    case 0x13u:
      v11 = v6[1];
      ptQVMa = 1;
      goto LABEL_12;
    case 0x14u:
      v11 = *(unsigned __int16 *)(v6 + 1);
      ptQVMa = 2;
LABEL_12:
      v12 = v11;
      ptScriptSymbol = (struct ScriptSymbol_s *)ptQVM->apxSymbolContext[v11];
      if ( ptScriptSymbol )
        goto LABEL_32;
      v14 = ptQVM->aptScriptSymbolReference[v12];
      if ( v14 && !v14->ptScriptSymbol )
      {
        v15 = Node_Remove(v14);
        List_AddHead(v15, (int)&Symbol_tFreeReferenceList);
        --Symbol_nReferencesUsed;
        ptQVM->aptScriptSymbolReference[v12] = nullptr;
      }
      v16 = ptQVM->aptScriptSymbolReference[v12];
      if ( v16 )
      {
        ptScriptSymbol = v16->ptScriptSymbol;
        if ( !ptScriptSymbol && v11 < ptQVM->tSymbolTable.nNextFree )
        {
          v17 = ptQVM->tSymbolTable.anStringOffset[v11];
          if ( v17 < ptQVM->tSymbolTable.nNextFreeOffset )
          {
            v18 = &ptQVM->tSymbolTable.zBuffer[v17];
            if ( v18 )
            {
              ptQVM->nErrorPC = ptQVM->nPC;
              ptQVM->nError = 7;
              v19 = (char *)ptQVM - v18;
              do
              {
                v20 = *v18;
                v18[v19 + 104] = *v18;
                ++v18;
              }
              while ( v20 );
              return;
            }
          }
        }
LABEL_32:
        v26 = ptQVM->nVSP - 1;
        v27 = ptQVM->nSP - 1;
        ptQVM->nSP = v27;
        v28 = v27;
        anOperandStackDataType = ptQVM->anOperandStackDataType;
        ptQVM->nVSP = v26;
        anOperandStackDataType[v28] = 6;
        ptQVM->anOperandStack[ptQVM->nVSP] = (int)ptScriptSymbol;
        ptQVM->nPC += ptQVMa + 1;
        return;
      }
      if ( v11 >= ptQVM->tSymbolTable.nNextFree
        || (v21 = ptQVM->tSymbolTable.anStringOffset[v12], v21 >= ptQVM->tSymbolTable.nNextFreeOffset)
        || (v22 = &ptQVM->tSymbolTable.zBuffer[v21]) == nullptr )
      {
        v33 = ptQVM->nPC;
        ptQVM->nError = 15;
        ptQVM->nErrorPC = v33;
        return;
      }
      zSymbolName = nullptr;
      v23 = Symbol_ptSymbolHashTable;
      v24 = Symbol_ptSymbolHashTable->tPrivate.pfHashFunction(Symbol_ptSymbolHashTable->tPrivate.nHashTableSize, v22);
      v25 = (struct ScriptSymbol_s *)((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Symbol_ptSymbolHashTable->tPrivate.pfFindElement)(v23, v24, (const void *)(v22));
      if ( v25 )
        zSymbolName = v25->zSymbolName;
      ptScriptSymbol = v25;
      if ( zSymbolName )
      {
        if ( v25->eLifespan )
          ptQVM->aptScriptSymbolReference[v12] = Symbol_NewReference(v22);
        else
          ptQVM->apxSymbolContext[v12] = v25;
        goto LABEL_32;
      }
      ptQVM->nErrorPC = ptQVM->nPC;
      ptQVM->nError = 7;
      v30 = (char *)((char *)ptQVM - v22);
      v31 = v22;
      do
      {
        v32 = *v31;
        v30[(_DWORD)v31 + 104] = *v31;
        ++v31;
      }
      while ( v32 );
      return;
    default:
      LDebug_Error("Unhandled opcode.");
      abort();
  }
}

// source: c/0/qvm.c:1885  [size]
void __cdecl QVM_OpNOP(struct QVM_s *ptQVM, void *pxUnused, int eOpCode, int eEvent)
{
  ++ptQVM->nPC;
}

// source: c/0/qvm.c:1901  [size]
void __cdecl QVM_OpBRK(struct QVM_s *ptQVM, void *pxUnused, int eOpCode, int eEvent)
{
  ptQVM->isBreak = 1;
}

// source: c/0/qvm.c:1917  [size]
void __cdecl QVM_OpIllegal(struct QVM_s *ptQVM, void *pxUnused, int eOpCode, int eEvent)
{
  ptQVM->nErrorPC = ptQVM->nPC;
  ptQVM->nError = 5;
}

// source: c/0/qvm.c:1934  [anchor-strings]
__declspec(noreturn) void QVM_NOTIMPLEMENTEDHandler()
{
  LDebug_Error("Instruction not implemented.");
  abort();
}

// source: c/0/qvm.c:1947  [anchor-strings]
void __cdecl QVM_GetNameHandler(void *pxOutputContext, void *pxInputContext, int eOpCode, int eEvent)
{
  char *v4; // eax
  int v5; // edx
  char v6; // cl

  switch ( eOpCode )
  {
    case 0:
      v4 = (char *)&dword_6891DC;
      break;
    case 1:
      v4 = "NOP";
      break;
    case 2:
      v4 = (char *)&dword_689150;
      break;
    case 3:
      v4 = (char *)&unk_68914C;
      break;
    case 4:
      v4 = (char *)&unk_689148;
      break;
    case 5:
      v4 = (char *)&unk_689144;
      break;
    case 6:
      v4 = (char *)&dword_689140;
      break;
    case 7:
      v4 = "CALL";
      break;
    case 8:
      v4 = "PUSH";
      break;
    case 9:
      v4 = "PUSHB";
      break;
    case 10:
      v4 = "PUSHW";
      break;
    case 11:
      v4 = "PUSHF";
      break;
    case 12:
      v4 = "PUSHA";
      break;
    case 13:
      v4 = "PUSHS";
      break;
    case 14:
      v4 = "PUSHSI";
      break;
    case 15:
      v4 = "PUSHSIB";
      break;
    case 16:
      v4 = "PUSHSIW";
      break;
    case 17:
      v4 = "PUSHI";
      break;
    case 18:
      v4 = "PUSHII";
      break;
    case 19:
      v4 = "PUSHIIB";
      break;
    case 20:
      v4 = "PUSHIIW";
      break;
    case 21:
      v4 = "PUSH0";
      break;
    case 22:
      v4 = "PUSH1";
      break;
    case 23:
      v4 = "PUSHM";
      break;
    case 24:
      v4 = (char *)&unk_689154;
      break;
    case 25:
      v4 = (char *)&unk_689134;
      break;
    case 26:
      v4 = (char *)&unk_689130;
      break;
    case 27:
      v4 = (char *)&unk_68912C;
      break;
    case 28:
      v4 = (char *)&unk_689128;
      break;
    case 29:
      v4 = (char *)&unk_689124;
      break;
    case 30:
      v4 = (char *)&dword_689120;
      break;
    case 31:
      v4 = (char *)&dword_68911C;
      break;
    case 32:
      v4 = "OR";
      break;
    case 33:
      v4 = "XOR";
      break;
    case 34:
      v4 = "LAND";
      break;
    case 35:
      v4 = "LOR";
      break;
    case 36:
      v4 = "EQ";
      break;
    case 37:
      v4 = "NE";
      break;
    case 38:
      v4 = "LT";
      break;
    case 39:
      v4 = "LE";
      break;
    case 40:
      v4 = "GT";
      break;
    case 41:
      v4 = "GE";
      break;
    case 42:
      v4 = "ASSIGN";
      break;
    case 43:
      v4 = "PLUS";
      break;
    case 44:
      v4 = "MINUS";
      break;
    case 45:
      v4 = (char *)&unk_6890D4;
      break;
    case 46:
      v4 = (char *)&unk_6890D0;
      break;
    case 47:
      v4 = (char *)&dword_6890CC;
      break;
    default:
      v4 = "ILLEGAL";
      break;
  }
  v5 = (_BYTE *)pxOutputContext - v4;
  do
  {
    v6 = *v4;
    v4[v5] = *v4;
    ++v4;
  }
  while ( v6 );
}

// source: c/0/qvm.c:2168  [anchor-hash]
void __cdecl QVM_Run(struct QVM_s *ptQVM)
{
  int v1; // [esp-8h] [ebp-8h]

  ptQVM->isBreak = 0;
  do
  {
    if ( ptQVM->nError || Script_isBreak && Script_isBreakEnabled )
      break;
    v1 = ptQVM->anInstruction[ptQVM->nPC];
    QVM_atOpCode[v1].apfOpCodeEvent[0](ptQVM, nullptr, v1, 0);
  }
  while ( !ptQVM->isBreak );
}

// source: c/0/qvm.c:2191  [anchor-strings]
void __cdecl QVM_DumpStack(struct QVM_s *ptQVM)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v4; };
    struct { char igi2_o1[4]; int v5; };
    struct { char igi2_o2[8]; char Buffer[4096]; };
    char igi2_extent[4104];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int nSP; // ebx
  int nVSP; // esi
  int v3; // ebx

  nSP = ptQVM->nSP;
  nVSP = ptQVM->nVSP;
  igi2_frame.v5 = nSP;
  igi2_frame.v4 = 0;
  if ( nSP < ptQVM->nStackElements )
  {
    do
    {
      switch ( ptQVM->anOperandStackDataType[nSP] )
      {
        case 1:
          sprintf(
            igi2_frame.Buffer,
            (char *const)&g_ptNetManager.tReceiveCounters.tCounters[9].nBytes,
            ptQVM->anOperandStack[nVSP++]);
          break;
        case 2:
          sprintf(igi2_frame.Buffer, "%f", *(float *)&ptQVM->anOperandStack[nVSP++]);
          break;
        case 3:
          sprintf(igi2_frame.Buffer, "\"%s\"", (char *)&ptQVM->anOperandStack[nVSP + 1]);
          nVSP += ptQVM->anOperandStack[nVSP] + 1;
          break;
        case 4:
          sprintf(
            igi2_frame.Buffer,
            (char *const)&stru_6A4CDC.tDebugConsoleLineList.ptMiddle,
            &ptQVM->anOperandStack[nVSP + 1]);
          nVSP += ptQVM->anOperandStack[nVSP] + 1;
          break;
        case 7:
          v3 = ptQVM->anOperandStack[nVSP];
          sprintf(igi2_frame.Buffer, "%d words of data.", v3);
          nVSP += v3 + 1;
          nSP = igi2_frame.v5;
          break;
        default:
          sprintf(igi2_frame.Buffer, "UNKNOWN DATA TYPE");
          igi2_frame.v4 = 1;
          break;
      }
      igi2_frame.v5 = ++nSP;
    }
    while ( !igi2_frame.v4 && nSP < ptQVM->nStackElements );
  }
}

// source: c/0/qvm.c:2280  [anchor-caller]
int __cdecl QVM_EvalArg(
        void *pxData,
        int nDataSize,
        struct ArgList_s *ptArgList,
        int nArg,
        int eDataType)
{
  #pragma pack(push, 1)
  union
  {
    struct { int nLength; };
    struct { char igi2_o1[4]; int isOK; };
    struct { char igi2_o2[8]; int nValue; };
    struct { char igi2_o3[12]; int nPC; };
    struct { char igi2_o4[16]; int nVSP; };
    char igi2_extent[20];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int *nArguments; // eax
  int v7; // edx
  int v8; // ebp
  int isQVM; // ecx
  struct QVM_s *v10; // esi
  struct QVM_s *v11; // eax
  int v12; // eax

  nArguments = (int *)ptArgList[1].nArguments;
  v7 = nArguments[6];
  v8 = nArguments[7];
  igi2_frame.nPC = nArguments[5];
  isQVM = ptArgList[1].isQVM;
  igi2_frame.nVSP = v7;
  LOWORD(igi2_frame.nLength) = *(_WORD *)(isQVM + 4 * nArg);
  LOBYTE(v7) = *(_BYTE *)(isQVM + 4 * nArg + 2);
  LOBYTE(isQVM) = *(_BYTE *)(isQVM + 4 * nArg + 3);
  BYTE2(igi2_frame.nLength) = v7;
  HIBYTE(igi2_frame.nLength) = isQVM;
  nArguments[5] = igi2_frame.nLength;
  v10 = (struct QVM_s *)ptArgList[1].nArguments;
  igi2_frame.isOK = 0;
  QVM_Run(v10);
  v11 = (struct QVM_s *)ptArgList[1].nArguments;
  if ( v11->nSP < v8 && !v11->nError )
  {
    switch ( eDataType )
    {
      case 1:
        if ( QVM_PopNumeric(v11, &igi2_frame.nValue, (float *)&igi2_frame.nLength) )
        {
          *(_DWORD *)pxData = igi2_frame.nValue;
          goto LABEL_13;
        }
        break;
      case 2:
        if ( QVM_PopNumeric(v11, &igi2_frame.nValue, (float *)&igi2_frame.nLength) )
        {
          *(_DWORD *)pxData = igi2_frame.nLength;
          goto LABEL_13;
        }
        break;
      case 3:
        if ( QVM_PopString(v11, (char **)&igi2_frame.nValue, &igi2_frame.nLength, 3) )
        {
          strncpy((char *)pxData, (char *)igi2_frame.nValue, nDataSize - 1);
          *((char *)pxData + nDataSize - 1) = 0;
LABEL_13:
          igi2_frame.isOK = 1;
        }
        break;
      default:
        LDebug_Error("Unknown data type.");
        abort();
    }
  }
  *(_DWORD *)(ptArgList[1].nArguments + 20) = igi2_frame.nPC;
  v12 = igi2_frame.nVSP;
  *(_DWORD *)(ptArgList[1].nArguments + 28) = v8;
  *(_DWORD *)(ptArgList[1].nArguments + 24) = v12;
  return igi2_frame.isOK;
}

// source: c/0/qvm.c:2371  [anchor-mhash]
int __cdecl QVM_EvalArgInt(struct ArgList_s *ptArgList, int nArg)
{
  int nValue; // [esp+4h] [ebp-4h] BYREF

  nValue = 0;
  QVM_EvalArg(&nValue, 4, ptArgList, nArg, 1);
  return nValue;
}

// source: c/0/qvm.c:2392  [anchor-mhash]
double __cdecl QVM_EvalArgFloat(struct ArgList_s *ptArgList, int nArg)
{
  float vValue; // [esp+4h] [ebp-4h] BYREF

  vValue = 0.0;
  QVM_EvalArg(&vValue, 4, ptArgList, nArg, 2);
  return vValue;
}

// source: c/0/qvm.c:2413  [anchor-mhash]
char *__cdecl QVM_EvalArgString(
        struct ArgList_s *ptArgList,
        int nArg,
        char *zBuffer,
        int nSize)
{
  *zBuffer = 0;
  QVM_EvalArg(zBuffer, nSize, ptArgList, nArg, 3);
  return zBuffer;
}

// source: c/0/qvm.c:2433  [size]
int __cdecl QVM_GetArgLinenumber(struct ArgList_s *ptArgList, int nArg)
{
  return 0;
}

// source: c/0/qvm.c:2450  [anchor-strings]
int __cdecl QVM_Execute(struct QVM_s *ptQVM)
{
  int nStackElements; // eax
  int nStackSize; // ecx
  int nError; // eax
  int result; // eax
  unsigned __int8 *v6; // eax
  char *v7; // [esp-4h] [ebp-10h]

  nStackElements = ptQVM->nStackElements;
  nStackSize = ptQVM->nStackSize;
  ptQVM->nPC = 0;
  ptQVM->nSP = nStackElements;
  ptQVM->nVSP = nStackSize;
  ptQVM->isBreak = 0;
  ptQVM->nError = 0;
  ptQVM->nErrorPC = 0;
  QVM_Run(ptQVM);
  nError = ptQVM->nError;
  if ( !nError )
    return 0;
  switch ( nError )
  {
    case 1:
      sprintf(ptQVM->zError, "Stack underflow");
      goto LABEL_18;
    case 2:
      v7 = "Stack overflow";
      goto LABEL_17;
    case 3:
      sprintf(ptQVM->zError, &stru_688EF4.zFilename[252]);
      goto LABEL_18;
    case 5:
      sprintf(ptQVM->zError, "Illegal instruction");
      goto LABEL_18;
    case 6:
      v7 = "Illegal operand(s) for instruction";
      goto LABEL_17;
    case 7:
      sprintf(ptQVM->zError, &stru_688EF4.zFilename[228], ptQVM->zErrorParam);
      QVM_DumpStack(ptQVM);
      return ptQVM->nError;
    case 8:
      sprintf(ptQVM->zError, &stru_688EF4.zFilename[200]);
      goto LABEL_18;
    case 9:
      sprintf(ptQVM->zError, &stru_688EF4.zFilename[172]);
      goto LABEL_18;
    case 10:
      v7 = &stru_688EF4.zFilename[148];
      goto LABEL_17;
    case 11:
      sprintf(ptQVM->zError, "Syntax error");
      goto LABEL_18;
    case 13:
      v6 = &ptQVM->anInstruction[ptQVM->nErrorPC];
      sprintf(ptQVM->zError, &stru_688EF4.zFilename[60], *(_DWORD *)(v6 + 1));
      QVM_DumpStack(ptQVM);
      return ptQVM->nError;
    case 14:
      sprintf(ptQVM->zError, &stru_688EF4.zFilename[104]);
      goto LABEL_18;
    case 15:
      sprintf(ptQVM->zError, &stru_688EF4.zFilename[128]);
      goto LABEL_18;
    default:
      v7 = &stru_688EF4.zFilename[44];
LABEL_17:
      sprintf(ptQVM->zError, v7);
LABEL_18:
      QVM_DumpStack(ptQVM);
      result = ptQVM->nError;
      break;
  }
  return result;
}

// source: c/0/qvm.c:2550  [anchor-mhash]
enum bool __cdecl QVM_IsQVM(void *pxBuffer, unsigned int nSize)
{
  return pxBuffer
      && nSize >= 0x40
      && *(_BYTE *)pxBuffer == 76
      && *((_BYTE *)pxBuffer + 1) == 79
      && *((_BYTE *)pxBuffer + 2) == 79
      && *((_BYTE *)pxBuffer + 3) == 80
      && *((_DWORD *)pxBuffer + 1) == 8
      && *((int *)pxBuffer + 2) >= 7;
}

// source: c/0/qvm.c:2575  [anchor-callee]
struct QVM_s *__cdecl QVM_CreateFromBuffer(
        void *pxBuffer,
        unsigned int nSize,
        int nStackSize,
        int nStackElements)
{
  int v4; // eax
  int v5; // ebp
  unsigned int v6; // ebp
  int v7; // edi
  struct QVM_s *v8; // edx
  int v9; // ecx
  void **v10; // ecx
  int v11; // eax

  v4 = nStackElements;
  v5 = nStackSize;
  if ( !nStackSize )
    v5 = *((_DWORD *)pxBuffer + 13);
  if ( !nStackElements )
  {
    v4 = *((_DWORD *)pxBuffer + 14);
    nStackElements = v4;
  }
  if ( !v5 )
    v5 = 2048;
  if ( !v4 )
  {
    v4 = 256;
    nStackElements = 256;
  }
  v6 = (unsigned int)(v5 + 3) >> 2;
  v7 = 4 * (v4 + v6 + 2 * *((_DWORD *)pxBuffer + 5) + 284);
  v8 = (struct QVM_s *)Mem_AllocFn(v7, 4);
  memset(v8, 0, v7);
  v8->anInstruction = (unsigned __int8 *)pxBuffer + *((_DWORD *)pxBuffer + 11);
  v8->nProgamSize = *((_DWORD *)pxBuffer + 12);
  v9 = (int)&v8[1] + 4 * v6;
  v8->anOperandStack = (int *)&v8[1];
  v8->anOperandStackDataType = (int *)v9;
  v10 = (void **)(v9 + 4 * nStackElements);
  v8->apxSymbolContext = v10;
  v8->ptQVMRaw = (struct QVMRaw_s *)pxBuffer;
  v8->zError[0] = 0;
  v8->zErrorParam[0] = 0;
  v8->aptScriptSymbolReference = (struct ScriptSymbolReference_s **)&v10[*((_DWORD *)pxBuffer + 5)];
  v8->nVSP = v6;
  v8->nSP = nStackElements;
  v8->nStackSize = v6;
  v8->nStackElements = nStackElements;
  if ( *((_DWORD *)pxBuffer + 5) )
  {
    v8->tSymbolTable.anStringOffset = (int *)((char *)pxBuffer + *((_DWORD *)pxBuffer + 3));
    v8->tSymbolTable.zBuffer = (char *)pxBuffer + *((_DWORD *)pxBuffer + 4);
    v8->tSymbolTable.nNextFree = *((_DWORD *)pxBuffer + 5);
    v8->tSymbolTable.nNextFreeOffset = *((_DWORD *)pxBuffer + 6);
  }
  if ( *((_DWORD *)pxBuffer + 9) )
  {
    v8->tStringTable.anStringOffset = (int *)((char *)pxBuffer + *((_DWORD *)pxBuffer + 7));
    v8->tStringTable.zBuffer = (char *)pxBuffer + *((_DWORD *)pxBuffer + 8);
    v8->tStringTable.nNextFree = *((_DWORD *)pxBuffer + 9);
    v8->tStringTable.nNextFreeOffset = *((_DWORD *)pxBuffer + 10);
  }
  v11 = *((_DWORD *)pxBuffer + 15);
  if ( v11 )
    v8->zFileInfo = (char *)pxBuffer + v11;
  else
    v8->zFileInfo = nullptr;
  return v8;
}

// source: c/0/qvm.c:2652  [anchor-strings]
struct QVM_s *__cdecl QVM_Load(char *zFilename, int nStackSize, int nStackElements)
{
  _BYTE *v4; // eax
  int v6; // eax
  char *RealFilename; // eax
  unsigned int nSize; // [esp+8h] [ebp-4h] BYREF

  v4 = Resource_Load(zFilename, &nSize);
  if ( !v4 )
    return nullptr;
  if ( nSize < 0x40
    || *v4 != 76
    || v4[1] != 79
    || v4[2] != 79
    || v4[3] != 80
    || *((_DWORD *)v4 + 1) != 8
    || *((int *)v4 + 2) < 7 )
  {
    if ( Resource_IsLoadedInternal(zFilename, (struct Resource_s **)&nSize) )
    {
      v6 = *(_DWORD *)(nSize + 36);
      if ( v6 != 3 && v6 != 1 )
        Resource_Remove((struct Resource_s *)nSize);
    }
    RealFilename = File_GetRealFilename(zFilename);
    LDebug_Error(&stru_688EF4.zFilename[8], RealFilename);
    abort();
  }
  return QVM_CreateFromBuffer(v4, nSize, nStackSize, nStackElements);
}

// source: c/0/qvm.c:2688  [anchor-hash]
void __cdecl QVM_Delete(struct QVM_s *ptQVM)
{
  int v2; // esi
  unsigned int v3; // ebx
  struct ScriptSymbolReference_s *v4; // eax
  _DWORD *v5; // eax
  struct Resource_s *ptHead; // ecx
  struct Resource_s *ptNext; // eax
  unsigned int nType; // eax
  int v9; // esi

  v2 = 0;
  if ( ptQVM->tSymbolTable.nNextFree > 0 )
  {
    v3 = Symbol_nReferencesUsed;
    do
    {
      v4 = ptQVM->aptScriptSymbolReference[v2];
      if ( v4 )
      {
        v5 = Node_Remove(v4);
        List_AddHead(v5, (int)&Symbol_tFreeReferenceList);
        --v3;
      }
      ++v2;
    }
    while ( v2 < ptQVM->tSymbolTable.nNextFree );
    Symbol_nReferencesUsed = v3;
  }
  ptHead = Resource_tResourceList.ptHead;
  ptNext = Resource_tResourceList.ptHead->ptNext;
  if ( Resource_tResourceList.ptHead->ptNext )
  {
    while ( ptHead->pxData != ptQVM->ptQVMRaw )
    {
      ptHead = ptNext;
      ptNext = ptNext->ptNext;
      if ( !ptNext )
        goto LABEL_14;
    }
    nType = ptHead->nType;
    if ( nType != 3 && nType != 1 )
      Resource_Remove(ptHead);
  }
LABEL_14:
  v9 = *(_DWORD *)((unsigned int)&ptQVM[-1].zFileInfo & 0xFFFFFFFC);
  --Mem_nCurrentAllocations;
  Node_Remove((_DWORD **)v9);
  memset(*(void **)(v9 + 8), 0xCDu, *(_DWORD *)(v9 + 16));
  free((void *)v9);
}

// source: c/0/qvm.c:2721  [anchor-mhash]
int __cdecl QVM_Save(
        struct QVM_s *ptQVM,
        char *zFilename,
        int nDefaultStackSize,
        int nDefaultStackElements,
        char *zFileInfo)
{
  int nNextFree; // ecx
  int v7; // ebx
  int v8; // eax
  int v9; // ecx
  int nNextFreeOffset; // esi
  int nProgamSize; // ecx
  struct File_s *v12; // eax
  struct File_s *v13; // esi
  struct QVMRaw_s tQVMRaw; // [esp+10h] [ebp-40h] BYREF
  int ptQVMa = *(int *)&ptQVM; // [esp+54h] [ebp+4h] ARGSLOT

  memset(&tQVMRaw, 0, sizeof(tQVMRaw));
  nNextFree = ptQVM->tStringTable.nNextFree;
  v7 = 0;
  ptQVMa = 0;
  tQVMRaw.tRAWHeader.nLOOP = 1347374924;
  tQVMRaw.tRAWHeader.nID = 8;
  v8 = 64;
  tQVMRaw.nVersion = 7;
  if ( nNextFree > 0 )
  {
    tQVMRaw.nStringTableOffset = 64;
    tQVMRaw.nStringBufferSize = ptQVM->tStringTable.nNextFreeOffset;
    v7 = 1;
    tQVMRaw.nStringTableSize = nNextFree;
    v8 = 4 * nNextFree + 64;
  }
  v9 = ptQVM->tSymbolTable.nNextFree;
  if ( v9 > 0 )
  {
    nNextFreeOffset = ptQVM->tSymbolTable.nNextFreeOffset;
    tQVMRaw.nIdentifierTableOffset = v8;
    ptQVMa = 1;
    tQVMRaw.nIdentifierTableSize = v9;
    tQVMRaw.nIdentifierBufferSize = nNextFreeOffset;
    v8 += 4 * v9;
  }
  if ( v7 )
  {
    tQVMRaw.nStringBufferOffset = v8;
    v8 += tQVMRaw.nStringBufferSize;
  }
  if ( ptQVMa )
  {
    tQVMRaw.nIdentifierBufferOffset = v8;
    v8 += tQVMRaw.nIdentifierBufferSize;
  }
  tQVMRaw.nDefaultStackSize = nDefaultStackSize;
  tQVMRaw.nDefaultStackElements = nDefaultStackElements;
  nProgamSize = ptQVM->nProgamSize;
  tQVMRaw.nProgramOffset = v8;
  tQVMRaw.nProgramSize = nProgamSize;
  if ( zFileInfo )
    tQVMRaw.nFileInfoOffset = v8 + nProgamSize;
  else
    tQVMRaw.nFileInfoOffset = 0;
  v12 = File_New(zFilename, "w");
  v13 = v12;
  if ( !v12 )
    return -1;
  File_atDevice[v12->eDeviceID].pfWrite(v12->eDeviceID, v12, &tQVMRaw, 64u);
  if ( v7 )
    File_atDevice[v13->eDeviceID].pfWrite(
      v13->eDeviceID,
      v13,
      ptQVM->tStringTable.anStringOffset,
      4 * tQVMRaw.nStringTableSize);
  if ( ptQVMa )
    File_atDevice[v13->eDeviceID].pfWrite(
      v13->eDeviceID,
      v13,
      ptQVM->tSymbolTable.anStringOffset,
      4 * tQVMRaw.nIdentifierTableSize);
  if ( v7 )
    File_atDevice[v13->eDeviceID].pfWrite(v13->eDeviceID, v13, ptQVM->tStringTable.zBuffer, tQVMRaw.nStringBufferSize);
  if ( ptQVMa )
    File_atDevice[v13->eDeviceID].pfWrite(
      v13->eDeviceID,
      v13,
      ptQVM->tSymbolTable.zBuffer,
      tQVMRaw.nIdentifierBufferSize);
  File_atDevice[v13->eDeviceID].pfWrite(v13->eDeviceID, v13, ptQVM->anInstruction, ptQVM->nProgamSize);
  if ( zFileInfo )
    File_atDevice[v13->eDeviceID].pfWrite(v13->eDeviceID, v13, zFileInfo, strlen(zFileInfo) + 1);
  if ( v13 == &File_tDummyAsyncFile )
    File_tDummyAsyncFile.isAsync = false;
  else
    File_atDevice[v13->eDeviceID].pfDelete(v13->eDeviceID, v13);
  return 0;
}

// source: c/0/qvm.c:2821  [size]
int __cdecl QVM_LinkOpCodeEventHandler(
        int eOpCode,
        int eEvent,
        void (__cdecl *pfOpCodeEventHandler)(void *, void *, int, int))
{
  int v3; // edx

  v3 = eEvent + 6 * eOpCode;
  QVM_atOpCode[0].apfOpCodeEvent[v3] = pfOpCodeEventHandler;
  return (int)pfOpCodeEventHandler;
}

// source: c/0/qvm.c:2836  [anchor-mhash]
int __cdecl QVM_TriggerOpCodeEvent(
        int eOpCode,
        int eEvent,
        void *pxOutputContext,
        void *pxInputContext)
{
  void (__cdecl *v4)(void *, void *, int, int); // ecx

  if ( (unsigned int)eOpCode <= 0x30 && (unsigned int)eEvent < 4 )
  {
    v4 = QVM_atOpCode[eOpCode].apfOpCodeEvent[eEvent];
    if ( v4 )
      return ((int (__cdecl *)(void *, void *, int, int))v4)(pxOutputContext, pxInputContext, eOpCode, eEvent);
  }
  return eOpCode;
}

// source: c/0/qvm.c:2858  [size]
void __cdecl QVM_SetErrorCallback(
        void (__cdecl *pfCallback)(char *, void *),
        void *pxContext)
{
  QVM_pfErrorCallback = pfCallback;
  QVM_pxErrorContext = pxContext;
}

// source: c/0/qvm.c:2872  [size]
void __cdecl QVM_SetWarningCallback(
        void (__cdecl *pfCallback)(char *, void *),
        void *pxContext)
{
  QVM_pfWarningCallback = pfCallback;
  QVM_pxWarningContext = pxContext;
}

// source: c/0/qvm.c:2886  [size]
void __cdecl QVM_SetMessageCallback(
        void (__cdecl *pfCallback)(char *, void *),
        void *pxContext)
{
  QVM_pfMessageCallback = pfCallback;
  QVM_pxMessageContext = pxContext;
}

// source: c/0/qvm.c:2900  [anchor-hash]
void __cdecl QVM_Open()
{
  void (__cdecl **apfOpCodeEvent)(void *, void *, int, int); // edx
  _DWORD *v1; // eax
  int v2; // ecx
  void (__cdecl **v3)(void *, void *, int, int); // eax

  apfOpCodeEvent = QVM_atOpCode[0].apfOpCodeEvent;
  do
  {
    v1 = apfOpCodeEvent;
    v2 = 49;
    do
    {
      *v1 = QVM_NOTIMPLEMENTEDHandler;
      v1 += 6;
      --v2;
    }
    while ( v2 );
    ++apfOpCodeEvent;
  }
  while ( (int)apfOpCodeEvent < 139287160 );
  v3 = &QVM_atOpCode[0].apfOpCodeEvent[1];
  do
  {
    *(v3 - 1) = (void (__cdecl *)(void *, void *, int, int))QVM_OpIllegal;
    *v3 = QVM_GetNameHandler;
    v3 += 6;
  }
  while ( (int)v3 < 139288324 );
  QVM_atOpCode[8].apfOpCodeEvent[0] = (void (__cdecl *)(void *, void *, int, int))QVM_OpPushInteger;
  QVM_atOpCode[12].apfOpCodeEvent[0] = (void (__cdecl *)(void *, void *, int, int))QVM_OpPushInteger;
  QVM_atOpCode[13].apfOpCodeEvent[0] = (void (__cdecl *)(void *, void *, int, int))QVM_OpPushString;
  QVM_atOpCode[17].apfOpCodeEvent[0] = (void (__cdecl *)(void *, void *, int, int))QVM_OpPushString;
  QVM_atOpCode[25].apfOpCodeEvent[0] = (void (__cdecl *)(void *, void *, int, int))QVM_OpBinary;
  QVM_atOpCode[26].apfOpCodeEvent[0] = (void (__cdecl *)(void *, void *, int, int))QVM_OpBinary;
  QVM_atOpCode[27].apfOpCodeEvent[0] = (void (__cdecl *)(void *, void *, int, int))QVM_OpBinary;
  QVM_atOpCode[28].apfOpCodeEvent[0] = (void (__cdecl *)(void *, void *, int, int))QVM_OpBinary;
  QVM_atOpCode[29].apfOpCodeEvent[0] = (void (__cdecl *)(void *, void *, int, int))QVM_OpBinary;
  QVM_atOpCode[30].apfOpCodeEvent[0] = (void (__cdecl *)(void *, void *, int, int))QVM_OpBinary;
  QVM_atOpCode[31].apfOpCodeEvent[0] = (void (__cdecl *)(void *, void *, int, int))QVM_OpBinary;
  QVM_atOpCode[32].apfOpCodeEvent[0] = (void (__cdecl *)(void *, void *, int, int))QVM_OpBinary;
  QVM_atOpCode[33].apfOpCodeEvent[0] = (void (__cdecl *)(void *, void *, int, int))QVM_OpBinary;
  QVM_atOpCode[34].apfOpCodeEvent[0] = (void (__cdecl *)(void *, void *, int, int))QVM_OpBinary;
  QVM_atOpCode[35].apfOpCodeEvent[0] = (void (__cdecl *)(void *, void *, int, int))QVM_OpBinary;
  QVM_atOpCode[36].apfOpCodeEvent[0] = (void (__cdecl *)(void *, void *, int, int))QVM_OpBinary;
  QVM_atOpCode[37].apfOpCodeEvent[0] = (void (__cdecl *)(void *, void *, int, int))QVM_OpBinary;
  QVM_atOpCode[38].apfOpCodeEvent[0] = (void (__cdecl *)(void *, void *, int, int))QVM_OpBinary;
  QVM_atOpCode[39].apfOpCodeEvent[0] = (void (__cdecl *)(void *, void *, int, int))QVM_OpBinary;
  QVM_atOpCode[40].apfOpCodeEvent[0] = (void (__cdecl *)(void *, void *, int, int))QVM_OpBinary;
  QVM_atOpCode[41].apfOpCodeEvent[0] = (void (__cdecl *)(void *, void *, int, int))QVM_OpBinary;
  QVM_atOpCode[43].apfOpCodeEvent[0] = (void (__cdecl *)(void *, void *, int, int))QVM_OpUnary;
  QVM_atOpCode[44].apfOpCodeEvent[0] = (void (__cdecl *)(void *, void *, int, int))QVM_OpUnary;
  QVM_atOpCode[45].apfOpCodeEvent[0] = (void (__cdecl *)(void *, void *, int, int))QVM_OpUnary;
  QVM_atOpCode[46].apfOpCodeEvent[0] = (void (__cdecl *)(void *, void *, int, int))QVM_OpUnary;
  QVM_atOpCode[3].apfOpCodeEvent[0] = (void (__cdecl *)(void *, void *, int, int))QVM_OpBranch;
  QVM_atOpCode[5].apfOpCodeEvent[0] = (void (__cdecl *)(void *, void *, int, int))QVM_OpBranch;
  QVM_atOpCode[4].apfOpCodeEvent[0] = (void (__cdecl *)(void *, void *, int, int))QVM_OpBranch;
  QVM_atOpCode[18].apfOpCodeEvent[0] = (void (__cdecl *)(void *, void *, int, int))QVM_OpPushIndex;
  QVM_atOpCode[19].apfOpCodeEvent[0] = (void (__cdecl *)(void *, void *, int, int))QVM_OpPushIndex;
  QVM_atOpCode[20].apfOpCodeEvent[0] = (void (__cdecl *)(void *, void *, int, int))QVM_OpPushIndex;
  QVM_atOpCode[14].apfOpCodeEvent[0] = (void (__cdecl *)(void *, void *, int, int))QVM_OpPushIndex;
  QVM_atOpCode[15].apfOpCodeEvent[0] = (void (__cdecl *)(void *, void *, int, int))QVM_OpPushIndex;
  QVM_atOpCode[16].apfOpCodeEvent[0] = (void (__cdecl *)(void *, void *, int, int))QVM_OpPushIndex;
  QVM_atOpCode[0].apfOpCodeEvent[0] = (void (__cdecl *)(void *, void *, int, int))QVM_OpBRK;
  QVM_atOpCode[1].apfOpCodeEvent[0] = (void (__cdecl *)(void *, void *, int, int))QVM_OpNOP;
  QVM_atOpCode[9].apfOpCodeEvent[0] = (void (__cdecl *)(void *, void *, int, int))QVM_OpPushInteger8;
  QVM_atOpCode[10].apfOpCodeEvent[0] = (void (__cdecl *)(void *, void *, int, int))QVM_OpPushInteger16;
  QVM_atOpCode[11].apfOpCodeEvent[0] = (void (__cdecl *)(void *, void *, int, int))QVM_OpPushFloat;
  QVM_atOpCode[21].apfOpCodeEvent[0] = (void (__cdecl *)(void *, void *, int, int))QVM_OpPushZero;
  QVM_atOpCode[22].apfOpCodeEvent[0] = (void (__cdecl *)(void *, void *, int, int))QVM_OpPushOne;
  QVM_atOpCode[23].apfOpCodeEvent[0] = (void (__cdecl *)(void *, void *, int, int))QVM_OpPushMinusOne;
  QVM_atOpCode[2].apfOpCodeEvent[0] = (void (__cdecl *)(void *, void *, int, int))QVM_OpIllegal;
  QVM_atOpCode[6].apfOpCodeEvent[0] = (void (__cdecl *)(void *, void *, int, int))QVM_OpIllegal;
  QVM_atOpCode[7].apfOpCodeEvent[0] = (void (__cdecl *)(void *, void *, int, int))QVM_OpCallFunction;
  QVM_atOpCode[42].apfOpCodeEvent[0] = (void (__cdecl *)(void *, void *, int, int))QVM_OpAssign;
  QVM_atOpCode[24].apfOpCodeEvent[0] = (void (__cdecl *)(void *, void *, int, int))QVM_OpPop;
  QVM_atOpCode[47].apfOpCodeEvent[0] = (void (__cdecl *)(void *, void *, int, int))QVM_OpData;
  QVM_pfErrorCallback = nullptr;
  QVM_pfMessageCallback = nullptr;
  QVM_pfWarningCallback = nullptr;
  QVM_pxErrorContext = nullptr;
  QVM_pxWarningContext = nullptr;
  QVM_pxMessageContext = nullptr;
}

// source: c/0/qvm.c:2983  [size]
void __cdecl QVM_Close()
{
  ;
}
