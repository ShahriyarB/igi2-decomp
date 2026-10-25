/* c/0/qvmopcode.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: c/0/qvmopcode.c:52  [anchor-mhash]
char *__cdecl QVMOpCode_GetString(struct QVMStringTable_s *ptQVMStringTable, int nIndex)
{
  int v2; // ecx

  if ( nIndex >= ptQVMStringTable->nNextFree )
    return nullptr;
  v2 = ptQVMStringTable->anStringOffset[nIndex];
  if ( v2 >= ptQVMStringTable->nNextFreeOffset )
    return nullptr;
  else
    return &ptQVMStringTable->zBuffer[v2];
}

// source: c/0/qvmopcode.c:79  [anchor-hash]
char *__cdecl QVMOpCode_WriteQuotedString(struct File_s *ptFile, char *zString)
{
  File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, &word_689EA8, 1u);
  if ( *zString )
  {
    do
    {
      switch ( *zString )
      {
        case 9:
        case 0xA:
        case 0xD:
          File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, &unk_688EF0, 2u);
          break;
        case 0x22:
          File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, &unk_688EEC, 2u);
          break;
        default:
          File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, zString, 1u);
          break;
      }
    }
    while ( *++zString );
  }
  return (char *)File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, &word_689EA8, 1u);
}

// source: c/0/qvmopcode.c:123  [anchor-mhash]
int __cdecl QVMOpCode_ParseHexString(char *zString)
{
  char v1; // cl
  int result; // eax
  int v3; // ecx

  v1 = *zString;
  for ( result = 0; v1; ++zString )
  {
    if ( v1 < 48 || v1 > 57 )
    {
      if ( v1 < 65 || v1 > 70 )
        v3 = v1 - 87;
      else
        v3 = v1 - 55;
    }
    else
    {
      v3 = v1 - 48;
    }
    result = v3 | (16 * result);
    v1 = zString[1];
  }
  return result;
}

// source: c/0/qvmopcode.c:164  [anchor-caller]
void __cdecl QVMAsm_PUSHAsmHandler(void *pxOutputContext, void *pxInputContext, int eOpCode, int eEvent)
{
  #pragma pack(push, 1)
  union
  {
    struct { unsigned __int8 nOpCode; };
    struct { char igi2_o1[1]; int nValue; };
    struct { char igi2_o2[5]; struct QVMParserToken_s tToken; };
    char igi2_extent[541];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QVMParser_s *v4; // edi
  int v5; // eax
  struct File_s *v6; // ecx
  struct File_s *v7; // ecx
  struct File_s *v8; // ecx
  struct File_s *v9; // ecx
  double v10; // st7
  struct File_s *v11; // esi
  struct File_s *v12; // ecx
  int StringIndex; // eax
  struct File_s *v14; // ecx
  bool v15; // cc
  _DWORD *v16; // eax
  struct File_s *v17; // ecx
  int IdentifierIndex; // eax
  struct File_s *v19; // ecx
  struct File_s *v20; // ecx

  v4 = *((struct QVMParser_s **)pxInputContext + 6);
  igi2_frame.tToken.ptPrev = nullptr;
  igi2_frame.tToken.ptNext = nullptr;
  igi2_frame.tToken.nMaxTokenSize = 512;
  igi2_frame.tToken.zToken = igi2_frame.tToken.zTempToken;
  igi2_frame.tToken.zAlloc = nullptr;
  if ( QVMParser_GetToken(&igi2_frame.tToken, v4) == false )
    goto LABEL_4;
  while ( igi2_frame.tToken.nTokenID == 1 )
  {
    if ( QVMParser_GetToken(&igi2_frame.tToken, v4) == false )
      goto LABEL_4;
  }
  if ( igi2_frame.tToken.nTokenID == 4 )
  {
    v5 = atoi(igi2_frame.tToken.zToken);
    igi2_frame.nValue = v5;
    if ( v5 < -128 || v5 > 127 )
    {
      if ( v5 < -32768 || v5 > 0x7FFF )
      {
        *(_DWORD *)pxOutputContext = 5;
        v9 = *((struct File_s **)pxInputContext + 4);
        igi2_frame.nOpCode = 8;
        File_atDevice[v9->eDeviceID].pfWrite(v9->eDeviceID, v9, &igi2_frame.nOpCode, 1u);
        File_atDevice[**((_DWORD **)pxInputContext + 4)].pfWrite(
          **((_DWORD **)pxInputContext + 4),
          *((struct File_s **)pxInputContext + 4),
          &igi2_frame.nValue,
          4u);
        QVMParser_DeAllocToken(&igi2_frame.tToken);
        return;
      }
      *(_DWORD *)pxOutputContext = 3;
      v8 = *((struct File_s **)pxInputContext + 4);
      igi2_frame.nOpCode = 10;
      File_Write(v8, &igi2_frame.nOpCode, 1u);
      File_Write(*((struct File_s **)pxInputContext + 4), &igi2_frame.nValue, 2u);
    }
    else
    {
      switch ( v5 )
      {
        case 0:
          igi2_frame.nOpCode = 21;
LABEL_10:
          *(_DWORD *)pxOutputContext = 1;
          File_Write(*((struct File_s **)pxInputContext + 4), &igi2_frame.nOpCode, 1u);
          QVMParser_DeAllocToken(&igi2_frame.tToken);
          return;
        case 1:
          *(_DWORD *)pxOutputContext = 1;
          v6 = *((struct File_s **)pxInputContext + 4);
          igi2_frame.nOpCode = 22;
          File_Write(v6, &igi2_frame.nOpCode, 1u);
          QVMParser_DeAllocToken(&igi2_frame.tToken);
          return;
        case -1:
          igi2_frame.nOpCode = 23;
          goto LABEL_10;
      }
      *(_DWORD *)pxOutputContext = 2;
      v7 = *((struct File_s **)pxInputContext + 4);
      igi2_frame.nOpCode = 9;
      File_Write(v7, &igi2_frame.nOpCode, 1u);
      File_Write(*((struct File_s **)pxInputContext + 4), &igi2_frame.nValue, 1u);
    }
    goto LABEL_42;
  }
  if ( igi2_frame.tToken.nTokenID != 5 )
  {
    if ( igi2_frame.tToken.nTokenID == 2 )
    {
      StringIndex = QVMAsm_GetStringIndex((struct QVMAsmParserContext_s *)pxInputContext, igi2_frame.tToken.zToken);
      igi2_frame.nValue = StringIndex;
      if ( StringIndex < 256 )
      {
        *(_DWORD *)pxOutputContext = 2;
        v14 = *((struct File_s **)pxInputContext + 4);
        igi2_frame.nOpCode = 15;
        File_Write(v14, &igi2_frame.nOpCode, 1u);
        File_Write(*((struct File_s **)pxInputContext + 4), &igi2_frame.nValue, 1u);
        goto LABEL_42;
      }
      v15 = StringIndex < 0x10000;
      v16 = pxOutputContext;
      if ( v15 )
      {
        *(_DWORD *)pxOutputContext = 3;
        v17 = *((struct File_s **)pxInputContext + 4);
        igi2_frame.nOpCode = 16;
        File_Write(v17, &igi2_frame.nOpCode, 1u);
        File_Write(*((struct File_s **)pxInputContext + 4), &igi2_frame.nValue, 2u);
        goto LABEL_42;
      }
      igi2_frame.nOpCode = 14;
LABEL_40:
      *v16 = 5;
      File_Write(*((struct File_s **)pxInputContext + 4), &igi2_frame.nOpCode, 1u);
      File_Write(*((struct File_s **)pxInputContext + 4), &igi2_frame.nValue, 4u);
      goto LABEL_42;
    }
    if ( igi2_frame.tToken.nTokenID == 9 )
    {
      IdentifierIndex = QVMAsm_GetIdentifierIndex((struct QVMAsmParserContext_s *)pxInputContext, igi2_frame.tToken.zToken);
      igi2_frame.nValue = IdentifierIndex;
      if ( IdentifierIndex < 256 )
      {
        *(_DWORD *)pxOutputContext = 2;
        v19 = *((struct File_s **)pxInputContext + 4);
        igi2_frame.nOpCode = 19;
        File_Write(v19, &igi2_frame.nOpCode, 1u);
        File_Write(*((struct File_s **)pxInputContext + 4), &igi2_frame.nValue, 1u);
        goto LABEL_42;
      }
      v15 = IdentifierIndex < 0x10000;
      v16 = pxOutputContext;
      if ( v15 )
      {
        *(_DWORD *)pxOutputContext = 3;
        v20 = *((struct File_s **)pxInputContext + 4);
        igi2_frame.nOpCode = 20;
        File_Write(v20, &igi2_frame.nOpCode, 1u);
        File_Write(*((struct File_s **)pxInputContext + 4), &igi2_frame.nValue, 2u);
        goto LABEL_42;
      }
      igi2_frame.nOpCode = 18;
      goto LABEL_40;
    }
LABEL_4:
    QVMParser_DeAllocToken(&igi2_frame.tToken);
    *((_DWORD *)pxInputContext + 1) = 1;
    return;
  }
  v10 = atof(igi2_frame.tToken.zToken);
  *(float *)&igi2_frame.nValue = v10;
  if ( v10 == 0.0 )
  {
    *(_DWORD *)pxOutputContext = 1;
    v11 = *((struct File_s **)pxInputContext + 4);
    igi2_frame.nOpCode = 21;
    File_atDevice[v11->eDeviceID].pfWrite(v11->eDeviceID, v11, &igi2_frame.nOpCode, 1u);
    QVMParser_DeAllocToken(&igi2_frame.tToken);
    return;
  }
  if ( *(float *)&igi2_frame.nValue == 1.0 )
  {
    igi2_frame.nOpCode = 22;
    goto LABEL_10;
  }
  if ( *(float *)&igi2_frame.nValue == -1.0 )
  {
    igi2_frame.nOpCode = 23;
    goto LABEL_10;
  }
  *(_DWORD *)pxOutputContext = 5;
  v12 = *((struct File_s **)pxInputContext + 4);
  igi2_frame.nOpCode = 11;
  File_Write(v12, &igi2_frame.nOpCode, 1u);
  File_Write(*((struct File_s **)pxInputContext + 4), &igi2_frame.nValue, 4u);
LABEL_42:
  QVMParser_DeAllocToken(&igi2_frame.tToken);
}

// source: c/0/qvmopcode.c:350  [anchor-mhash]
void __cdecl QVMAsm_BRAAsmHandler(void *pxOutputContext, void *pxInputContext, int eOpCode, int eEvent)
{
  #pragma pack(push, 1)
  union
  {
    struct { unsigned __int8 nOpCode; };
    struct { char igi2_o1[1]; int nPC; };
    struct { char igi2_o2[5]; struct QVMParserToken_s tToken; };
    char igi2_extent[541];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QVMParser_s *v4; // edi
  struct QVMLabelReference_s *v5; // eax

  v4 = *((struct QVMParser_s **)pxInputContext + 6);
  igi2_frame.tToken.ptPrev = nullptr;
  igi2_frame.tToken.ptNext = nullptr;
  igi2_frame.tToken.nMaxTokenSize = 512;
  igi2_frame.tToken.zToken = igi2_frame.tToken.zTempToken;
  igi2_frame.tToken.zAlloc = nullptr;
  if ( QVMParser_GetToken(&igi2_frame.tToken, v4) == false )
    goto LABEL_4;
  while ( igi2_frame.tToken.nTokenID == 1 )
  {
    if ( QVMParser_GetToken(&igi2_frame.tToken, v4) == false )
      goto LABEL_4;
  }
  if ( igi2_frame.tToken.nTokenID == 9 || igi2_frame.tToken.nTokenID == 12 )
  {
    igi2_frame.nOpCode = eOpCode;
    igi2_frame.nPC = 0;
    if ( igi2_frame.tToken.nTokenID == 9 )
    {
      v5 = QVMAsm_InstallLabelReference((struct QVMAsmParserContext_s *)pxInputContext, igi2_frame.tToken.zToken);
      if ( v5 )
      {
        v5->nPC = *(_DWORD *)pxInputContext + 1;
        v5->nRelativeTo = *(_DWORD *)pxInputContext + 5;
      }
      else
      {
        *((_DWORD *)pxInputContext + 1) = 1;
      }
    }
    else
    {
      igi2_frame.nPC = -5 - *(_DWORD *)pxInputContext + QVMOpCode_ParseHexString((char *)igi2_frame.tToken.zToken + 1);
    }
    *(_DWORD *)pxOutputContext = 5;
    File_atDevice[**((_DWORD **)pxInputContext + 4)].pfWrite(
      **((_DWORD **)pxInputContext + 4),
      *((struct File_s **)pxInputContext + 4),
      &igi2_frame.nOpCode,
      1u);
    File_atDevice[**((_DWORD **)pxInputContext + 4)].pfWrite(
      **((_DWORD **)pxInputContext + 4),
      *((struct File_s **)pxInputContext + 4),
      &igi2_frame.nPC,
      4u);
    QVMParser_DeAllocToken(&igi2_frame.tToken);
  }
  else
  {
LABEL_4:
    QVMParser_DeAllocToken(&igi2_frame.tToken);
    *((_DWORD *)pxInputContext + 1) = 1;
  }
}

// source: c/0/qvmopcode.c:416  [anchor-mhash]
void __cdecl QVMAsm_IMMAsmHandler(void *pxOutputContext, void *pxInputContext, int eOpCode, int eEvent)
{
  char v4; // cl
  _DWORD **v5; // edx

  v4 = eOpCode;
  v5 = (_DWORD **)pxInputContext;
  *(_DWORD *)pxOutputContext = 1;
  LOBYTE(pxOutputContext) = v4;
  File_atDevice[*v5[4]].pfWrite(*v5[4], (struct File_s *)v5[4], &pxOutputContext, 1u);
}

// source: c/0/qvmopcode.c:442  [anchor-mhash]
void __cdecl QVMAsm_CALLEXTAsmHandler(void *pxOutputContext, void *pxInputContext, int eOpCode, int eEvent)
{
  #pragma pack(push, 1)
  union
  {
    struct { unsigned __int8 nOpCode; };
    struct { char igi2_o1[1]; int nZero; };
    struct { char igi2_o2[5]; int nArgs; };
    struct { char igi2_o3[9]; struct QVMParserToken_s tToken; };
    char igi2_extent[545];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QVMParser_s *v4; // edi
  int v5; // edi
  struct File_s *v6; // ecx
  int v7; // ebp
  struct QVMParser_s *v8; // edi
  int nTokenID; // eax
  struct QVMLabelReference_s *v10; // eax
  struct QVMParser_s *v11; // edi
  int v12; // edi

  v4 = *((struct QVMParser_s **)pxInputContext + 6);
  igi2_frame.tToken.ptPrev = nullptr;
  igi2_frame.tToken.ptNext = nullptr;
  igi2_frame.tToken.nMaxTokenSize = 512;
  igi2_frame.tToken.zToken = igi2_frame.tToken.zTempToken;
  igi2_frame.tToken.zAlloc = nullptr;
  if ( QVMParser_GetToken(&igi2_frame.tToken, v4) )
  {
    while ( igi2_frame.tToken.nTokenID == 1 )
    {
      if ( QVMParser_GetToken(&igi2_frame.tToken, v4) == false )
        goto LABEL_4;
    }
    v5 = *(_DWORD *)pxInputContext;
    igi2_frame.nArgs = 0;
    igi2_frame.nZero = 0;
    if ( igi2_frame.tToken.nTokenID == 7 )
    {
      v6 = *((struct File_s **)pxInputContext + 4);
      igi2_frame.nOpCode = 7;
      File_atDevice[v6->eDeviceID].pfWrite(v6->eDeviceID, v6, &igi2_frame.nOpCode, 1u);
      File_atDevice[**((_DWORD **)pxInputContext + 4)].pfWrite(
        **((_DWORD **)pxInputContext + 4),
        *((struct File_s **)pxInputContext + 4),
        &igi2_frame.nZero,
        4u);
      v7 = v5 + 5;
      while ( 1 )
      {
        v8 = *((struct QVMParser_s **)pxInputContext + 6);
        if ( QVMParser_GetToken(&igi2_frame.tToken, v8) == false )
          break;
        while ( 1 )
        {
          nTokenID = igi2_frame.tToken.nTokenID;
          if ( igi2_frame.tToken.nTokenID != 1 )
            break;
          if ( QVMParser_GetToken(&igi2_frame.tToken, v8) == false )
            goto LABEL_4;
        }
        if ( igi2_frame.tToken.nTokenID == 9 )
        {
          v10 = QVMAsm_InstallLabelReference((struct QVMAsmParserContext_s *)pxInputContext, igi2_frame.tToken.zToken);
          if ( !v10 )
            break;
          v10->nPC = v7;
          v10->nRelativeTo = 0;
        }
        else
        {
          if ( igi2_frame.tToken.nTokenID != 12 )
            goto LABEL_21;
          igi2_frame.nZero = QVMOpCode_ParseHexString((char *)igi2_frame.tToken.zToken + 1);
        }
        File_atDevice[**((_DWORD **)pxInputContext + 4)].pfWrite(
          **((_DWORD **)pxInputContext + 4),
          *((struct File_s **)pxInputContext + 4),
          &igi2_frame.nZero,
          4u);
        v11 = *((struct QVMParser_s **)pxInputContext + 6);
        ++igi2_frame.nArgs;
        v7 += 4;
        if ( QVMParser_GetToken(&igi2_frame.tToken, v11) == false )
          break;
        while ( 1 )
        {
          nTokenID = igi2_frame.tToken.nTokenID;
          if ( igi2_frame.tToken.nTokenID != 1 )
            break;
          if ( QVMParser_GetToken(&igi2_frame.tToken, v11) == false )
            goto LABEL_4;
        }
        if ( igi2_frame.tToken.nTokenID != 6 )
        {
LABEL_21:
          if ( nTokenID != 8 )
            break;
          v12 = igi2_frame.nArgs;
          *(_DWORD *)pxOutputContext = 4 * igi2_frame.nArgs + 5;
          QVMAsm_InstallPCInfo((struct QVMAsmParserContext_s *)pxInputContext, *(_DWORD *)pxInputContext + 1)->nArgs = v12;
          QVMParser_DeAllocToken(&igi2_frame.tToken);
          return;
        }
      }
    }
  }
LABEL_4:
  QVMParser_DeAllocToken(&igi2_frame.tToken);
  *((_DWORD *)pxInputContext + 1) = 1;
}

// source: c/0/qvmopcode.c:551  [anchor-mhash]
void __cdecl QVMOpCode_IMMDisAsmHandler(void *pxOutputContext, void *pxInputContext, int eOpCode, int eEvent)
{
  File_atDevice[**(_DWORD **)pxOutputContext].pfWrite(
    **(_DWORD **)pxOutputContext,
    *(struct File_s **)pxOutputContext,
    "\r\n",
    2u);
  ++*((_DWORD *)pxOutputContext + 2);
}

// source: c/0/qvmopcode.c:576  [anchor-mhash]
void __cdecl QVMOpCode_PUSHDisAsmHandler(void *pxOutputContext, void *pxInputContext, int eOpCode, int eEvent)
{
  int v5; // eax
  char v6; // cl
  int v7; // eax
  char zParameter[32]; // [esp+8h] [ebp-20h] BYREF
  void *pxOutputContexta = *(void * *)&pxOutputContext; // [esp+2Ch] [ebp+4h] ARGSLOT

  v5 = *((_DWORD *)pxOutputContext + 2);
  v6 = *(_BYTE *)(v5 + *(_DWORD *)pxInputContext + 1);
  v7 = *(_DWORD *)pxInputContext + v5;
  LOBYTE(pxOutputContexta) = v6;
  BYTE1(pxOutputContexta) = *(_BYTE *)(v7 + 2);
  HIWORD(pxOutputContexta) = *(_WORD *)(v7 + 3);
  sprintf(zParameter, "%d\r\n", pxOutputContexta);
  File_atDevice[**(_DWORD **)pxOutputContext].pfWrite(
    **(_DWORD **)pxOutputContext,
    *(struct File_s **)pxOutputContext,
    zParameter,
    strlen(zParameter));
  *((_DWORD *)pxOutputContext + 2) += (int)(5);
}

// source: c/0/qvmopcode.c:606  [anchor-mhash]
void __cdecl QVMOpCode_PUSHFDisAsmHandler(void *pxOutputContext, void *pxInputContext, int eOpCode, int eEvent)
{
  int v5; // eax
  char v6; // cl
  int v7; // eax
  char zParameter[32]; // [esp+10h] [ebp-20h] BYREF
  void *pxOutputContexta = *(void * *)&pxOutputContext; // [esp+34h] [ebp+4h] ARGSLOT

  v5 = *((_DWORD *)pxOutputContext + 2);
  v6 = *(_BYTE *)(v5 + *(_DWORD *)pxInputContext + 1);
  v7 = *(_DWORD *)pxInputContext + v5;
  LOBYTE(pxOutputContexta) = v6;
  BYTE1(pxOutputContexta) = *(_BYTE *)(v7 + 2);
  HIWORD(pxOutputContexta) = *(_WORD *)(v7 + 3);
  sprintf(zParameter, "%f\r\n", *(float *)&pxOutputContexta);
  File_atDevice[**(_DWORD **)pxOutputContext].pfWrite(
    **(_DWORD **)pxOutputContext,
    *(struct File_s **)pxOutputContext,
    zParameter,
    strlen(zParameter));
  *((_DWORD *)pxOutputContext + 2) += (int)(5);
}

// source: c/0/qvmopcode.c:636  [anchor-strings]
void __cdecl QVMOpCode_BRANCHDisAsmHandler(void *pxOutputContext, void *pxInputContext, int eOpCode, int eEvent)
{
  char zParameter[32]; // [esp+8h] [ebp-20h] BYREF

  sprintf(
    zParameter,
    "@%08X\r\n",
    *((_DWORD *)pxOutputContext + 2) + *(_DWORD *)(*(_DWORD *)pxInputContext + *((_DWORD *)pxOutputContext + 2) + 1) + 5);
  File_atDevice[**(_DWORD **)pxOutputContext].pfWrite(
    **(_DWORD **)pxOutputContext,
    *(struct File_s **)pxOutputContext,
    zParameter,
    strlen(zParameter));
  *((_DWORD *)pxOutputContext + 2) += (int)(5);
}

// source: c/0/qvmopcode.c:666  [anchor-mhash]
void __cdecl QVMOpCode_PUSHINT8DisAsmHandler(void *pxOutputContext, void *pxInputContext, int eOpCode, int eEvent)
{
  char zParameter[32]; // [esp+8h] [ebp-20h] BYREF

  sprintf(zParameter, "%d\r\n", *(char *)(*(_DWORD *)pxInputContext + *((_DWORD *)pxOutputContext + 2) + 1));
  File_atDevice[**(_DWORD **)pxOutputContext].pfWrite(
    **(_DWORD **)pxOutputContext,
    *(struct File_s **)pxOutputContext,
    zParameter,
    strlen(zParameter));
  *((_DWORD *)pxOutputContext + 2) += (int)(2);
}

// source: c/0/qvmopcode.c:696  [anchor-mhash]
void __cdecl QVMOpCode_PUSHINT16DisAsmHandler(void *pxOutputContext, void *pxInputContext, int eOpCode, int eEvent)
{
  char zParameter[32]; // [esp+8h] [ebp-20h] BYREF

  sprintf(zParameter, "%d\r\n", *(__int16 *)(*((_DWORD *)pxOutputContext + 2) + *(_DWORD *)pxInputContext + 1));
  File_atDevice[**(_DWORD **)pxOutputContext].pfWrite(
    **(_DWORD **)pxOutputContext,
    *(struct File_s **)pxOutputContext,
    zParameter,
    strlen(zParameter));
  *((_DWORD *)pxOutputContext + 2) += (int)(3);
}

// source: c/0/qvmopcode.c:756  [anchor-strings]
void __cdecl QVMOpCode_PUSHSTRINGDisAsmHandler(void *pxOutputContext, void *pxInputContext, int eOpCode, int eEvent)
{
  int **v4; // edi
  int v5; // esi
  _DWORD *v6; // eax
  int v7; // ecx
  int v8; // edx
  int *v9; // edx
  int v10; // edx
  int v11; // ecx
  int v12; // ecx
  char *v13; // eax

  switch ( eOpCode )
  {
    case 14:
    case 18:
      v4 = (int **)pxOutputContext;
      v5 = *((_DWORD *)pxOutputContext + 2);
      v6 = pxInputContext;
      v7 = *(_DWORD *)(*(_DWORD *)pxInputContext + v5 + 1);
      *((_DWORD *)pxOutputContext + 2) = v5 + 5;
      goto LABEL_6;
    case 15:
    case 19:
      v4 = (int **)pxOutputContext;
      v6 = pxInputContext;
      v8 = *((_DWORD *)pxOutputContext + 2);
      v7 = *(unsigned __int8 *)(v8 + *(_DWORD *)pxInputContext + 1);
      v9 = (int *)(v8 + 2);
      goto LABEL_5;
    case 16:
    case 20:
      v4 = (int **)pxOutputContext;
      v6 = pxInputContext;
      v10 = *((_DWORD *)pxOutputContext + 2);
      v7 = *(unsigned __int16 *)(v10 + *(_DWORD *)pxInputContext + 1);
      v9 = (int *)(v10 + 3);
LABEL_5:
      v4[2] = v9;
LABEL_6:
      switch ( byte_5EA8D0[eOpCode - 14] )
      {
        case 0:
          if ( v7 < (int)(v6[14]) )
          {
            v12 = *(_DWORD *)(v6[16] + 4 * v7);
            if ( v12 < (int)(v6[15]) )
            {
              v13 = (char *)(v12 + v6[17]);
              if ( v13 )
                QVMOpCode_WriteQuotedString((struct File_s *)*v4, v13);
            }
          }
          break;
        case 1:
          if ( v7 < (int)(v6[20]) )
          {
            v11 = *(_DWORD *)(v6[22] + 4 * v7);
            if ( v11 < (int)(v6[21]) )
            {
              if ( v11 + v6[23] )
                File_atDevice[**v4].pfWrite(
                  **v4,
                  (struct File_s *)*v4,
                  (void *)(v11 + v6[23]),
                  strlen((char *)(v11 + v6[23])));
            }
          }
          break;
        case 2:
          break;
      }
      File_atDevice[**v4].pfWrite(**v4, (struct File_s *)*v4, "\r\n", 2u);
      return;
    default:
      LDebug_Error("Opcode not implemented for PUSHSTRING");
      abort();
  }
}

// source: c/0/qvmopcode.c:847  [anchor-strings]
void __cdecl QVMOpCode_CALLEXTDisAsmHandler(void *pxOutputContext, void *pxInputContext, int eOpCode, int eEvent)
{
  #pragma pack(push, 1)
  union
  {
    struct { int nArgs; };
    struct { char igi2_o1[4]; int nArgCount; };
    struct { char igi2_o2[12]; int nTab; };
    struct { char igi2_o3[16]; char zAddress[32]; };
    struct { char igi2_o4[48]; char zTab[512]; };
    char igi2_extent[560];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  unsigned int v4; // eax
  int v5; // ebx
  int v6; // eax
  char *v7; // edi

  memset(igi2_frame.zTab, 0x20u, sizeof(igi2_frame.zTab));
  qmemcpy(igi2_frame.zTab, "\r\n ", 3);
  v4 = *((_DWORD *)pxOutputContext + 1) + 2;
  igi2_frame.nTab = 512;
  if ( v4 <= 0x200 )
    igi2_frame.nTab = v4;
  igi2_frame.nArgs = *(_DWORD *)(*((_DWORD *)pxOutputContext + 2) + *(_DWORD *)pxInputContext + 1);
  File_atDevice[**(_DWORD **)pxOutputContext].pfWrite(
    **(_DWORD **)pxOutputContext,
    *(struct File_s **)pxOutputContext,
    word_692AD0,
    1u);
  v5 = 0;
  for ( igi2_frame.nArgCount = 0; v5 < igi2_frame.nArgs; ++igi2_frame.nArgCount )
  {
    v6 = *(_DWORD *)pxInputContext + *((_DWORD *)pxOutputContext + 2) + 4 * v5;
    sprintf(igi2_frame.zAddress, "@%08X", *(_DWORD *)(v6 + 5));
    if ( v5 >= igi2_frame.nArgs - 1 )
    {
      igi2_frame.nArgCount = 0;
    }
    else
    {
      v7 = (char *)&igi2_frame.nTab + 3;
      while ( *++v7 )
        ;
      strcpy(v7, ", ");
    }
    File_atDevice[**(_DWORD **)pxOutputContext].pfWrite(
      **(_DWORD **)pxOutputContext,
      *(struct File_s **)pxOutputContext,
      igi2_frame.zAddress,
      strlen(igi2_frame.zAddress));
    if ( igi2_frame.nArgCount >= 4 )
    {
      igi2_frame.nArgCount = -1;
      File_atDevice[**(_DWORD **)pxOutputContext].pfWrite(
        **(_DWORD **)pxOutputContext,
        *(struct File_s **)pxOutputContext,
        igi2_frame.zTab,
        igi2_frame.nTab);
    }
    ++v5;
  }
  File_atDevice[**(_DWORD **)pxOutputContext].pfWrite(
    **(_DWORD **)pxOutputContext,
    *(struct File_s **)pxOutputContext,
    &unk_684CD8,
    3u);
  *((_DWORD *)pxOutputContext + 2) += (int)(4 * igi2_frame.nArgs + 5);
}

// source: c/0/qvmopcode.c:907  [anchor-hash]
void __cdecl QVMOpCode_LinkAsmHandlers()
{
  void (__cdecl **v0)(void *, void *, int, int); // eax

  v0 = &QVM_atOpCode[0].apfOpCodeEvent[2];
  do
  {
    *v0 = QVMAsm_IMMAsmHandler;
    v0 += 6;
  }
  while ( (int)v0 < 139288328 );
  QVM_atOpCode[8].apfOpCodeEvent[2] = QVMAsm_PUSHAsmHandler;
  QVM_atOpCode[9].apfOpCodeEvent[2] = QVMAsm_PUSHAsmHandler;
  QVM_atOpCode[10].apfOpCodeEvent[2] = QVMAsm_PUSHAsmHandler;
  QVM_atOpCode[11].apfOpCodeEvent[2] = QVMAsm_PUSHAsmHandler;
  QVM_atOpCode[13].apfOpCodeEvent[2] = QVMAsm_PUSHAsmHandler;
  QVM_atOpCode[14].apfOpCodeEvent[2] = QVMAsm_PUSHAsmHandler;
  QVM_atOpCode[15].apfOpCodeEvent[2] = QVMAsm_PUSHAsmHandler;
  QVM_atOpCode[16].apfOpCodeEvent[2] = QVMAsm_PUSHAsmHandler;
  QVM_atOpCode[17].apfOpCodeEvent[2] = QVMAsm_PUSHAsmHandler;
  QVM_atOpCode[18].apfOpCodeEvent[2] = QVMAsm_PUSHAsmHandler;
  QVM_atOpCode[19].apfOpCodeEvent[2] = QVMAsm_PUSHAsmHandler;
  QVM_atOpCode[20].apfOpCodeEvent[2] = QVMAsm_PUSHAsmHandler;
  QVM_atOpCode[3].apfOpCodeEvent[2] = QVMAsm_BRAAsmHandler;
  QVM_atOpCode[4].apfOpCodeEvent[2] = QVMAsm_BRAAsmHandler;
  QVM_atOpCode[5].apfOpCodeEvent[2] = QVMAsm_BRAAsmHandler;
  QVM_atOpCode[7].apfOpCodeEvent[2] = QVMAsm_CALLEXTAsmHandler;
}

// source: c/0/qvmopcode.c:942  [anchor-hash]
void __cdecl QVMOpCode_LinkDisAsmHandlers()
{
  void (__cdecl **v0)(void *, void *, int, int); // eax

  v0 = &QVM_atOpCode[0].apfOpCodeEvent[3];
  do
  {
    *v0 = QVMOpCode_IMMDisAsmHandler;
    v0 += 6;
  }
  while ( (int)v0 < 139288332 );
  QVM_atOpCode[14].apfOpCodeEvent[3] = QVMOpCode_PUSHSTRINGDisAsmHandler;
  QVM_atOpCode[15].apfOpCodeEvent[3] = QVMOpCode_PUSHSTRINGDisAsmHandler;
  QVM_atOpCode[16].apfOpCodeEvent[3] = QVMOpCode_PUSHSTRINGDisAsmHandler;
  QVM_atOpCode[17].apfOpCodeEvent[3] = QVMOpCode_PUSHSTRINGDisAsmHandler;
  QVM_atOpCode[18].apfOpCodeEvent[3] = QVMOpCode_PUSHSTRINGDisAsmHandler;
  QVM_atOpCode[19].apfOpCodeEvent[3] = QVMOpCode_PUSHSTRINGDisAsmHandler;
  QVM_atOpCode[20].apfOpCodeEvent[3] = QVMOpCode_PUSHSTRINGDisAsmHandler;
  QVM_atOpCode[8].apfOpCodeEvent[3] = QVMOpCode_PUSHDisAsmHandler;
  QVM_atOpCode[9].apfOpCodeEvent[3] = QVMOpCode_PUSHINT8DisAsmHandler;
  QVM_atOpCode[10].apfOpCodeEvent[3] = QVMOpCode_PUSHINT16DisAsmHandler;
  QVM_atOpCode[11].apfOpCodeEvent[3] = QVMOpCode_PUSHFDisAsmHandler;
  QVM_atOpCode[3].apfOpCodeEvent[3] = QVMOpCode_BRANCHDisAsmHandler;
  QVM_atOpCode[4].apfOpCodeEvent[3] = QVMOpCode_BRANCHDisAsmHandler;
  QVM_atOpCode[5].apfOpCodeEvent[3] = QVMOpCode_BRANCHDisAsmHandler;
  QVM_atOpCode[7].apfOpCodeEvent[3] = QVMOpCode_CALLEXTDisAsmHandler;
  QVM_atOpCode[13].apfOpCodeEvent[3] = (void (__cdecl *)(void *, void *, int, int))QVM_NOTIMPLEMENTEDHandler;
}

// source: c/0/qvmopcode.c:977  [size]
void __cdecl QVMOpCode_Open()
{
  ;
}

// source: c/0/qvmopcode.c:989  [size]
void __cdecl QVMOpCode_Close()
{
  ;
}
