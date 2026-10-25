/* c/0/qvmasm.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: c/0/qvmasm.c:72  [anchor-callee]
void __cdecl QVMAsm_ConvertString(char *zBuffer, char *zString)
{
  char v2; // dl
  int v3; // eax
  char *v4; // ecx
  char *v5; // edi
  char v6; // dl
  char v7; // cl

  v2 = zString[1];
  v3 = 0;
  v4 = zString + 1;
  if ( v2 != 34 )
  {
    v5 = (char *)v4;
    do
    {
      if ( *v5 == 92 )
      {
        v6 = *++v5;
        switch ( v6 )
        {
          case 'n':
            zBuffer[v3] = 10;
            break;
          case 'r':
            zBuffer[v3] = 13;
            break;
          case 't':
            zBuffer[v3] = 9;
            break;
          default:
            zBuffer[v3] = v6;
            break;
        }
      }
      else
      {
        zBuffer[v3] = *v5;
      }
      v7 = v5[1];
      ++v3;
      ++v5;
    }
    while ( v7 != 34 );
  }
  zBuffer[v3] = 0;
}

// source: c/0/qvmasm.c:126  [anchor-callee]
void QVMAsm_Error(struct QVMAsmParserContext_s *ptParserContext, char *zFormat, ...)
{
  char Buffer[1024]; // [esp+0h] [ebp-400h] BYREF
  va_list ArgList; // [esp+40Ch] [ebp+Ch] BYREF ARGSLOT

  va_start(ArgList, zFormat);
  vsprintf(Buffer, zFormat, ArgList);
  ++QVMAsm_nErrors;
  if ( !QVMAsm_pfErrorCallback )
  {
    LDebug_Error((char *)&stru_6A4CDC.tDebugConsoleLineList.ptMiddle, Buffer);
    abort();
  }
  QVMAsm_pfErrorCallback(Buffer, QVMAsm_pxErrorContext);
}

// source: c/0/qvmasm.c:181  [size]
void QVMAsm_Message(char *zFormat, ...)
{
  char Buffer[1024]; // [esp+0h] [ebp-400h] BYREF
  va_list ArgList; // [esp+408h] [ebp+8h] BYREF ARGSLOT

  va_start(ArgList, zFormat);
  if ( QVMAsm_pfMessageCallback )
  {
    vsprintf(Buffer, zFormat, ArgList);
    QVMAsm_pfMessageCallback(Buffer, QVMAsm_pxMessageContext);
  }
}

// source: c/0/qvmasm.c:208  [size]
void __cdecl QVMAsm_SetErrorCallback(
        void (__cdecl *pfCallback)(char *, void *),
        void *pxContext)
{
  QVMAsm_pfErrorCallback = pfCallback;
  QVMAsm_pxErrorContext = pxContext;
}

// source: c/0/qvmasm.c:222  [size]
void __cdecl QVMAsm_SetWarningCallback(
        void (__cdecl *pfCallback)(char *, void *),
        void *pxContext)
{
  QVMAsm_pfWarningCallback = pfCallback;
  QVMAsm_pxWarningContext = pxContext;
}

// source: c/0/qvmasm.c:236  [size]
void __cdecl QVMAsm_SetMessageCallback(
        void (__cdecl *pfCallback)(char *, void *),
        void *pxContext)
{
  QVMAsm_pfMessageCallback = pfCallback;
  QVMAsm_pxMessageContext = pxContext;
}

// source: c/0/qvmasm.c:253  [anchor-mhash]
struct QVMPCInfo_s *__cdecl QVMAsm_InstallPCInfo(struct QVMAsmParserContext_s *ptParserContext, int nPC)
{
  _DWORD *v2; // eax

  v2 = Mem_AllocFn(16, 4);
  v2[2] = nPC;
  v2[1] = 0;
  *v2 = 0;
  return (struct QVMPCInfo_s *)List_AddTail(v2, (int)&ptParserContext->tPCInfoList);
}

// source: c/0/qvmasm.c:277  [anchor-strings]
struct QVMPCInfo_s *__cdecl QVMAsm_GetPCInfo(
        struct QVMAsmParserContext_s *ptParserContext,
        int nPC)
{
  struct QVMPCInfo_s *result; // eax
  struct QVMPCInfo_s *ptNext; // ecx

  result = ptParserContext->tPCInfoList.ptHead;
  ptNext = result->ptNext;
  if ( !result->ptNext )
  {
LABEL_4:
    LDebug_Error("No PC info for address %08x.", nPC);
    abort();
  }
  while ( result->nPC != nPC )
  {
    result = ptNext;
    ptNext = ptNext->ptNext;
    if ( !ptNext )
      goto LABEL_4;
  }
  return result;
}

// source: c/0/qvmasm.c:308  [anchor-strings]
struct QVMLabelInfo_s *__cdecl QVMAsm_InstallLabel(
        struct QVMAsmParserContext_s *ptParserContext,
        char *zLabel)
{
  int v2; // edx
  char v3; // cl
  unsigned int v4; // kr00_4
  struct QHashTable_s *ptSymbolHash; // esi
  int v6; // eax
  struct QVMLabelInfo_s *result; // eax
  struct QVMLabelInfo_s *v8; // esi
  struct QHashTable_s *v9; // edi
  int v10; // eax
  char zTemp[128]; // [esp+8h] [ebp-80h] BYREF

  v2 = zTemp - zLabel;
  do
  {
    v3 = *zLabel;
    zLabel[v2] = *zLabel;
    ++zLabel;
  }
  while ( v3 );
  v4 = strlen(zTemp);
  if ( zTemp[v4 - 1] == 58 )
    zTemp[v4 - 1] = 0;
  ptSymbolHash = ptParserContext->ptSymbolHash;
  v6 = ptSymbolHash->tPrivate.pfHashFunction(ptSymbolHash->tPrivate.nHashTableSize, zTemp);
  result = (struct QVMLabelInfo_s *)((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))ptSymbolHash->tPrivate.pfFindElement)(ptSymbolHash, v6, (const void *)(zTemp));
  if ( result )
  {
    if ( result->isInstalled )
    {
      ptParserContext->nError = 1;
      QVMAsm_Error(ptParserContext, "Duplicate label: '%s'", zTemp);
      return nullptr;
    }
  }
  else
  {
    v8 = (struct QVMLabelInfo_s *)Mem_AllocFn(156, 4);
    v8->ptPrev = nullptr;
    v8->ptNext = nullptr;
    List_AddTail(v8, (int)&ptParserContext->tLabelList);
    v8->isInstalled = 0;
    strcpy(v8->zLabel, zTemp);
    v8->tLabelReferenceList.ptHead = (struct QVMLabelReference_s *)&v8->tLabelReferenceList.ptMiddle;
    v8->tLabelReferenceList.ptTail = (struct QVMLabelReference_s *)&v8->tLabelReferenceList;
    v8->tLabelReferenceList.ptMiddle = nullptr;
    v9 = ptParserContext->ptSymbolHash;
    v10 = v9->tPrivate.pfHashFunction(v9->tPrivate.nHashTableSize, v8->zLabel);
    v9->tPrivate.pfCreateElement(v9, v10, (const void *)(v8->zLabel), (const void *)(v8));
    return v8;
  }
  return result;
}

// source: c/0/qvmasm.c:366  [anchor-mhash]
struct QVMLabelInfo_s *__cdecl QVMAsm_GetLabel(
        struct QVMAsmParserContext_s *ptParserContext,
        char *zLabel)
{
  struct QHashTable_s *ptSymbolHash; // esi
  int v3; // eax

  ptSymbolHash = ptParserContext->ptSymbolHash;
  v3 = ptSymbolHash->tPrivate.pfHashFunction(ptSymbolHash->tPrivate.nHashTableSize, zLabel);
  return ((struct QVMLabelInfo_s * (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))ptSymbolHash->tPrivate.pfFindElement)(ptSymbolHash, v3, (const void *)(zLabel));
}

// source: c/0/qvmasm.c:385  [anchor-caller]
struct QVMLabelReference_s *__cdecl QVMAsm_InstallLabelReference(
        struct QVMAsmParserContext_s *ptParserContext,
        char *zLabel)
{
  struct QHashTable_s *ptSymbolHash; // esi
  int v3; // eax
  struct QVMLabelInfo_s *v4; // esi
  _DWORD *v5; // eax

  ptSymbolHash = ptParserContext->ptSymbolHash;
  v3 = ptSymbolHash->tPrivate.pfHashFunction(ptSymbolHash->tPrivate.nHashTableSize, zLabel);
  v4 = (struct QVMLabelInfo_s *)((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))ptSymbolHash->tPrivate.pfFindElement)(ptSymbolHash, v3, (const void *)(zLabel));
  if ( !v4 )
    v4 = QVMAsm_InstallLabel(ptParserContext, zLabel);
  v5 = Mem_AllocFn(16, 4);
  v5[1] = 0;
  *v5 = 0;
  return (struct QVMLabelReference_s *)List_AddTail(v5, (int)&v4->tLabelReferenceList);
}

// source: c/0/qvmasm.c:418  [anchor-callee]
int __cdecl QVMAsm_GetStringIndex(struct QVMAsmParserContext_s *ptParserContext, char *zString)
{
  #pragma pack(push, 1)
  union
  {
    struct { int iIndex; };
    struct { char igi2_o1[4]; char *zAlloc; };
    struct { char igi2_o2[12]; char zTempBuffer[2048]; };
    char igi2_extent[2060];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char *v3; // ebx
  unsigned int v4; // kr00_4
  struct QVMStringInfo_s *ptHead; // esi
  struct QVMStringInfo_s *ptNext; // ebp
  _DWORD *v7; // eax
  char *v8; // ecx
  int v9; // edx
  char v10; // al
  int v11; // esi

  igi2_frame.zAlloc = nullptr;
  igi2_frame.iIndex = 0;
  v3 = igi2_frame.zTempBuffer;
  v4 = strlen(zString);
  if ( v4 + 1 > 0x800 )
  {
    igi2_frame.zAlloc = (char *)Mem_AllocFn(v4 + 1, 4);
    v3 = igi2_frame.zAlloc;
  }
  QVMAsm_ConvertString(v3, zString);
  ptHead = ptParserContext->tStringList.ptHead;
  ptNext = ptHead->ptNext;
  if ( !ptHead->ptNext )
    goto LABEL_8;
  while ( strcmp(ptHead->zString, v3) )
  {
    ptHead = ptNext;
    ptNext = ptNext->ptNext;
    ++igi2_frame.iIndex;
    if ( !ptNext )
      goto LABEL_8;
  }
  if ( !ptHead )
  {
LABEL_8:
    v7 = Mem_AllocFn(2056, 4);
    v7[1] = 0;
    *v7 = 0;
    v8 = v3;
    v9 = (char *)(List_AddTail(v7, (int)&ptParserContext->tStringList) + 2) - v3;
    do
    {
      v10 = *v8;
      v8[v9] = *v8;
      ++v8;
    }
    while ( v10 );
  }
  if ( igi2_frame.zAlloc )
  {
    v11 = *(_DWORD *)((unsigned int)(igi2_frame.zAlloc - 4) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v11);
    memset(*(void **)(v11 + 8), 0xCDu, *(_DWORD *)(v11 + 16));
    free((void *)v11);
  }
  return igi2_frame.iIndex;
}

// source: c/0/qvmasm.c:488  [anchor-callee]
int __cdecl QVMAsm_GetIdentifierIndex(
        struct QVMAsmParserContext_s *ptParserContext,
        char *zIdentifier)
{
  struct QVMIdentifierInfo_s *ptHead; // ebp
  struct QVMIdentifierInfo_s *ptNext; // edi
  _DWORD *v4; // eax
  char *v5; // ecx
  int v6; // edx
  char v7; // al
  int iIndex; // [esp+Ch] [ebp-8h]
  struct QVMIdentifierList_s *a2; // [esp+10h] [ebp-4h]

  ptHead = ptParserContext->tIdentifierList.ptHead;
  ptNext = ptHead->ptNext;
  iIndex = 0;
  a2 = &ptParserContext->tIdentifierList;
  if ( !ptHead->ptNext )
    goto LABEL_6;
  while ( strcmp(ptHead->zIdentifier, zIdentifier) )
  {
    ptHead = ptNext;
    ptNext = ptNext->ptNext;
    ++iIndex;
    if ( !ptNext )
      goto LABEL_6;
  }
  if ( !ptHead )
  {
LABEL_6:
    v4 = Mem_AllocFn(136, 4);
    v4[1] = 0;
    *v4 = 0;
    v5 = zIdentifier;
    v6 = (char *)(List_AddTail(v4, (int)a2) + 2) - zIdentifier;
    do
    {
      v7 = *v5;
      v5[v6] = *v5;
      ++v5;
    }
    while ( v7 );
  }
  return iIndex;
}

// source: c/0/qvmasm.c:536  [anchor-mhash]
enum bool __cdecl QVMAsm_GetToken(
        struct QVMParserToken_s *ptQVMParserToken,
        struct QVMParser_s *ptQVMParser)
{

  if ( QVMParser_GetToken(ptQVMParserToken, ptQVMParser) == false )
    return false;
  while ( ptQVMParserToken->nTokenID == 1 )
  {
    if ( QVMParser_GetToken(ptQVMParserToken, ptQVMParser) == false )
      return false;
  }
  return true;
}

// source: c/0/qvmasm.c:565  [anchor-caller]
int __cdecl QVMAsm_Assemble(
        char *zDestinationFile,
        char *zSourceFile,
        char *zFileInfo)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct File_s *ptTempFile; };
    struct { char igi2_o1[4]; unsigned int nSize; };
    struct { char igi2_o2[8]; int nPC; };
    struct { char igi2_o3[12]; struct QVMParserPatternList_s tTokenList; };
    struct { char igi2_o4[24]; struct QVMGetNameContext_s tGetNameContext; };
    struct { char igi2_o5[32]; struct File_s *ptFile; };
    struct { char igi2_o6[36]; struct QVMAsmParserContext_s tParserContext; };
    struct { char igi2_o7[116]; struct QVMParser_s tQVMParser; };
    struct { char igi2_o8[136]; void *pxBuffer; };
    struct { char igi2_o9[140]; struct QVMRaw_s tQVMRaw; };
    struct { char igi2_o10[204]; struct InputStream_s tInp; };
    struct { char igi2_o11[236]; char zQVMTemp[260]; };
    struct { char igi2_o12[496]; struct QVMParserToken_s tToken; };
    struct { char igi2_o13[1032]; char azOpCodeName[49][8]; };
    char igi2_extent[1424];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct File_s *v5; // ebp
  void *v6; // esi
  struct QHashTable_s *v7; // esi
  void *v8; // edi
  int v9; // ebp
  void (__cdecl **v10)(void *, void *, int, int); // edi
  int v11; // esi
  struct QVMGetNameContext_s *p_tGetNameContext; // eax
  char v13; // cl
  struct File_s *v14; // esi
  struct QVMLabelInfo_s *v15; // eax
  int v16; // ecx
  char *zToken; // edx
  char v18; // al
  int i; // esi
  int v20; // edi
  char *v21; // ebp
  void (__cdecl *v22)(void *, void *, int, int); // eax
  char *ptHead; // ebp
  _DWORD *v24; // esi
  _DWORD *v25; // ebx
  unsigned int v26; // eax
  unsigned int v27; // ecx
  int v28; // edx
  int v29; // esi
  struct QHashTable_s *ptSymbolHash; // esi
  unsigned int v31; // eax
  int v32; // esi
  struct QVMPCInfo_s *v33; // eax
  struct QVMPCInfo_s *ptNext; // ebx
  int j; // ebp
  unsigned int nArgs; // ecx
  unsigned int v37; // edx
  int v38; // esi
  int v39; // esi
  struct QVMIdentifierInfo_s *v40; // eax
  struct QVMIdentifierInfo_s *v41; // ecx
  int v42; // esi
  int k; // edi
  struct QVMStringInfo_s *v44; // eax
  struct QVMStringInfo_s *v45; // ecx
  int v46; // edi
  int m; // esi
  int v48; // ebp
  int v49; // edi
  int v50; // esi
  struct File_s *v51; // esi
  struct QVMIdentifierInfo_s *v52; // eax
  struct QVMIdentifierInfo_s *v53; // edi
  struct QVMIdentifierInfo_s *v54; // ebx
  struct QVMIdentifierInfo_s *n; // edi
  struct QVMStringInfo_s *v56; // eax
  struct QVMStringInfo_s *v57; // edi
  struct QVMStringInfo_s *v58; // ebx
  struct QVMStringInfo_s *ii; // edi
  void *v60; // edi
  struct QVMIdentifierInfo_s *v61; // eax
  struct QVMIdentifierInfo_s *jj; // ebx
  _DWORD **v63; // eax
  int v64; // esi
  struct QVMStringInfo_s *v65; // eax
  struct QVMStringInfo_s *kk; // ebx
  _DWORD **v67; // eax
  int v68; // esi
  struct QVMPCInfo_s *v69; // eax
  struct QVMPCInfo_s *mm; // ebx
  _DWORD **v71; // eax
  int v72; // esi
  struct QVMLabelInfo_s *v73; // ebx
  struct QVMLabelInfo_s *nn; // ebp
  unsigned int *v75; // eax
  unsigned int *v76; // esi
  _DWORD **v77; // eax
  int v78; // esi
  struct QHashTable_s *v79; // esi
  unsigned int v80; // eax
  int v81; // esi
  struct QHashTable_s *v82; // ebx
  void *papxElement; // eax
  int v84; // esi
  int v85; // ecx
  int v86; // esi
  int v87; // esi
  struct Resource_s *v88; // ecx
  struct Resource_s *v89; // eax
  unsigned int nType; // eax
  int v91; // esi

  igi2_frame.tToken.zToken = igi2_frame.tToken.zTempToken;
  igi2_frame.tToken.ptPrev = nullptr;
  igi2_frame.tToken.ptNext = nullptr;
  igi2_frame.tToken.nMaxTokenSize = 512;
  igi2_frame.tToken.zAlloc = nullptr;
  if ( Wildcard_Match("{.*:(.*//)*}.*", nullptr, nullptr, (void *)zDestinationFile, 0)
    || Wildcard_Match("{(.*//)*}.*", nullptr, nullptr, (void *)zDestinationFile, 0) )
  {
    Wildcard_SubstituteString((int)zDestinationFile, igi2_frame.zQVMTemp, 260, "/0qvmbin.tmp");
  }
  else
  {
    strcpy(igi2_frame.zQVMTemp, "qvmbin.tmp");
  }
  QVMAsm_nErrors = 0;
  v5 = File_New(zDestinationFile, "w");
  igi2_frame.ptFile = v5;
  if ( v5 )
  {
    if ( Resource_IsLoadedInternal(zSourceFile, nullptr) || File_Exists(zSourceFile) )
    {
      v6 = Resource_Load(zSourceFile, &igi2_frame.nSize);
      igi2_frame.pxBuffer = v6;
      QVMAsm_Message("Initialising parser.\n");
      igi2_frame.tTokenList.ptTail = (struct QVMParserPattern_s *)&igi2_frame.tTokenList;
      igi2_frame.tTokenList.ptHead = (struct QVMParserPattern_s *)&igi2_frame.tTokenList.ptMiddle;
      igi2_frame.tTokenList.ptMiddle = nullptr;
      QVMParserPatternList_AddToken(&igi2_frame.tTokenList, "[ \\t\\n\\r]+", 1, true);
      QVMParserPatternList_AddToken(&igi2_frame.tTokenList, "\"([~\\\\\"]*(\\.)*)*\"", 2, true);
      QVMParserPatternList_AddToken(&igi2_frame.tTokenList, "[a-zA-Z][a-zA-Z0-9_]*:", 10, true);
      QVMParserPatternList_AddToken(&igi2_frame.tTokenList, "-?[0-9]+/.[0-9]+", 5, true);
      QVMParserPatternList_AddToken(&igi2_frame.tTokenList, word_692ACC, 6, true);
      QVMParserPatternList_AddToken(&igi2_frame.tTokenList, "/(", 7, true);
      QVMParserPatternList_AddToken(&igi2_frame.tTokenList, "/)", 8, true);
      QVMParserPatternList_AddToken(&igi2_frame.tTokenList, "0x[0-9a-fA-F]+", 3, true);
      QVMParserPatternList_AddToken(&igi2_frame.tTokenList, "[0-9a-zA-Z]+:", 11, true);
      QVMParserPatternList_AddToken(&igi2_frame.tTokenList, "@[0-9a-zA-Z]+", 12, true);
      QVMParserPatternList_AddToken(&igi2_frame.tTokenList, "[a-zA-Z][a-zA-Z0-9_.]*", 9, false);
      QVMParserPatternList_AddToken(&igi2_frame.tTokenList, "-?[0-9]+", 4, false);
      InputStream_Alloc(&igi2_frame.tInp, v6, igi2_frame.nSize, SingleLine_GetInput);
      igi2_frame.tQVMParser.ptInputStream = &igi2_frame.tInp;
      igi2_frame.tQVMParser.tQVMParserTokenList.ptHead = (struct QVMParserToken_s *)&igi2_frame.tQVMParser.tQVMParserTokenList.ptMiddle;
      igi2_frame.tQVMParser.tQVMParserTokenList.ptMiddle = nullptr;
      igi2_frame.nPC = 0;
      memset(&igi2_frame.tParserContext, 0, sizeof(igi2_frame.tParserContext));
      igi2_frame.tQVMParser.ptQVMParserPatternList = &igi2_frame.tTokenList;
      igi2_frame.tParserContext.ptQVMParser = &igi2_frame.tQVMParser;
      igi2_frame.tQVMParser.tQVMParserTokenList.ptTail = (struct QVMParserToken_s *)&igi2_frame.tQVMParser.tQVMParserTokenList;
      igi2_frame.tParserContext.tLabelList.ptTail = (struct QVMLabelInfo_s *)&igi2_frame.tParserContext.tLabelList;
      igi2_frame.tParserContext.ptToken = &igi2_frame.tToken;
      igi2_frame.tParserContext.tLabelList.ptHead = (struct QVMLabelInfo_s *)&igi2_frame.tParserContext.tLabelList.ptMiddle;
      igi2_frame.tParserContext.tIdentifierList.ptHead = (struct QVMIdentifierInfo_s *)&igi2_frame.tParserContext.tIdentifierList.ptMiddle;
      igi2_frame.tParserContext.tStringList.ptHead = (struct QVMStringInfo_s *)&igi2_frame.tParserContext.tStringList.ptMiddle;
      igi2_frame.tParserContext.tStringList.ptTail = (struct QVMStringInfo_s *)&igi2_frame.tParserContext.tStringList;
      igi2_frame.tParserContext.tPCInfoList.ptTail = (struct QVMPCInfo_s *)&igi2_frame.tParserContext.tPCInfoList;
      igi2_frame.tParserContext.ptFile = v5;
      igi2_frame.tParserContext.nPC = 0;
      igi2_frame.tParserContext.tLabelList.ptMiddle = nullptr;
      igi2_frame.tParserContext.tStringList.ptMiddle = nullptr;
      igi2_frame.tParserContext.tIdentifierList.ptTail = (struct QVMIdentifierInfo_s *)&igi2_frame.tParserContext.tIdentifierList;
      igi2_frame.tParserContext.tIdentifierList.ptMiddle = nullptr;
      igi2_frame.tParserContext.tPCInfoList.ptHead = (struct QVMPCInfo_s *)&igi2_frame.tParserContext.tPCInfoList.ptMiddle;
      igi2_frame.tParserContext.tPCInfoList.ptMiddle = nullptr;
      v7 = (struct QHashTable_s *)Mem_AllocFn(40, 4);
      v7->tPrivate.nHashTableSize = 77003;
      v7->tPrivate.pfHashFunction = QHashTable_StringHashFunction;
      v7->tPrivate.pfCompareKey = QHashTable_StringCompareKeyFunction;
      v7->tPrivate.pfDuplicateKey = nullptr;
      v7->tPrivate.pfCreateElement = QHashTable_CreateElementClosed;
      v7->tPrivate.pfFindElement = QHashTable_FindElementClosed;
      v7->tPrivate.pfDeleteElement = QHashTable_DeleteElementClosed;
      v7->tPrivate.pfMap = QHashTable_MapClosed;
      v7->tPrivate.nEntries = 0;
      v8 = Mem_AllocFn(616024, 4);
      v7->tPrivate.papxElement = v8;
      memset(v8, 0, 0x96658u);
      igi2_frame.tParserContext.ptSymbolHash = v7;
      v9 = 0;
      v10 = &QVM_atOpCode[0].apfOpCodeEvent[1];
      v11 = (char *)igi2_frame.azOpCodeName - (char *)&igi2_frame.tGetNameContext;
      do
      {
        if ( (int)v10 >= 139287148 && (int)v10 < 139288324 && *v10 )
          (*v10)(&igi2_frame.tGetNameContext, nullptr, v9, 1);
        p_tGetNameContext = &igi2_frame.tGetNameContext;
        do
        {
          v13 = p_tGetNameContext->zName[0];
          p_tGetNameContext->zName[v11] = p_tGetNameContext->zName[0];
          p_tGetNameContext = (struct QVMGetNameContext_s *)((char *)p_tGetNameContext + 1);
        }
        while ( v13 );
        v10 += 6;
        ++v9;
        v11 += 8;
      }
      while ( (int)v10 < 139288324 );
      v14 = File_New(igi2_frame.zQVMTemp, "w");
      igi2_frame.ptTempFile = v14;
      if ( v14 )
      {
        QVMAsm_Message("Assembling\n");
        igi2_frame.tParserContext.eEvent = 2;
        igi2_frame.tParserContext.ptFile = v14;
LABEL_21:
        while ( QVMParser_GetToken(&igi2_frame.tToken, &igi2_frame.tQVMParser) )
        {
          while ( igi2_frame.tToken.nTokenID == 1 )
          {
            if ( QVMParser_GetToken(&igi2_frame.tToken, &igi2_frame.tQVMParser) == false )
              goto LABEL_24;
          }
          if ( igi2_frame.tParserContext.nError )
            break;
          if ( igi2_frame.tToken.nTokenID == 10 )
          {
            v15 = QVMAsm_InstallLabel(&igi2_frame.tParserContext, igi2_frame.tToken.zToken);
            if ( v15 )
            {
              v16 = igi2_frame.nPC;
              v15->isInstalled = 1;
              v15->nPC = v16;
            }
          }
          else if ( igi2_frame.tToken.nTokenID == 9 )
          {
            zToken = igi2_frame.tToken.zToken;
            v18 = *igi2_frame.tToken.zToken;
            for ( i = 0; v18; ++i )
            {
              igi2_frame.tToken.zToken[i] = toupper(v18);
              zToken = igi2_frame.tToken.zToken;
              v18 = igi2_frame.tToken.zToken[i + 1];
            }
            v20 = 0;
            v21 = igi2_frame.azOpCodeName[0];
            while ( strcmp(zToken, v21) )
            {
              ++v20;
              v21 += 8;
              if ( v20 >= 49 )
              {
                igi2_frame.tParserContext.nError = 1;
                QVMAsm_Error(&igi2_frame.tParserContext, "Unknown opcode: %s\n", zToken);
                v14 = igi2_frame.ptTempFile;
                goto LABEL_21;
              }
            }
            igi2_frame.nSize = 0;
            if ( v20 >= 0 && igi2_frame.tParserContext.eEvent < 4u )
            {
              v22 = QVM_atOpCode[v20].apfOpCodeEvent[igi2_frame.tParserContext.eEvent];
              if ( v22 )
                v22(&igi2_frame.nSize, &igi2_frame.tParserContext, v20, igi2_frame.tParserContext.eEvent);
            }
            v14 = igi2_frame.ptTempFile;
            igi2_frame.nPC += igi2_frame.nSize;
            igi2_frame.tParserContext.nPC = igi2_frame.nPC;
          }
        }
LABEL_24:
        if ( v14 == &File_tDummyAsyncFile )
          File_tDummyAsyncFile.isAsync = false;
        else
          File_atDevice[v14->eDeviceID].pfDelete(v14->eDeviceID, v14);
        if ( !igi2_frame.tParserContext.nError )
        {
          igi2_frame.nSize = (unsigned int)File_Load(igi2_frame.zQVMTemp, (unsigned int *)&igi2_frame.ptTempFile);
          if ( igi2_frame.nSize )
          {
            if ( igi2_frame.ptTempFile != (struct File_s *)igi2_frame.nPC )
            {
              LDebug_Error("INTERNAL ERROR: QVMAsm bin file size does not match computed program size!!!");
              abort();
            }
            QVMAsm_Message("Patching code\n");
            ptHead = (char *)igi2_frame.tParserContext.tLabelList.ptHead;
            for ( igi2_frame.ptTempFile = (struct File_s *)igi2_frame.tParserContext.tLabelList.ptHead->ptNext;
                  igi2_frame.ptTempFile;
                  igi2_frame.ptTempFile = (struct File_s *)igi2_frame.ptTempFile->eDeviceID )
            {
              v24 = *((_DWORD **)ptHead + 2);
              v25 = (_DWORD *)*v24;
              if ( *v24 )
              {
                do
                {
                  if ( !*((_DWORD *)ptHead + 5) )
                    QVMAsm_Error(&igi2_frame.tParserContext, "Unknown label '%s' at PC:%08x\n", ptHead + 28, v24[2]);
                  v26 = *((_DWORD *)ptHead + 6) - v24[3];
                  v27 = igi2_frame.nSize;
                  *(_WORD *)(igi2_frame.nSize + v24[2]) = v26;
                  v28 = v24[2];
                  *(_DWORD *)igi2_frame.tGetNameContext.zName = v26;
                  v26 >>= 16;
                  *(_BYTE *)(v28 + v27 + 2) = v26;
                  *(_BYTE *)(v24[2] + v27 + 3) = BYTE1(v26);
                  Node_Remove((_DWORD **)v24);
                  v29 = *(_DWORD *)((unsigned int)(v24 - 1) & 0xFFFFFFFC);
                  --Mem_nCurrentAllocations;
                  Node_Remove((_DWORD **)v29);
                  memset(*(void **)(v29 + 8), 0xCDu, *(_DWORD *)(v29 + 16));
                  free((void *)v29);
                  v24 = v25;
                  v25 = (_DWORD *)*v25;
                }
                while ( v25 );
              }
              ptSymbolHash = igi2_frame.tParserContext.ptSymbolHash;
              v31 = igi2_frame.tParserContext.ptSymbolHash->tPrivate.pfHashFunction(
                      igi2_frame.tParserContext.ptSymbolHash->tPrivate.nHashTableSize,
                      ptHead + 28);
              ((void  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))ptSymbolHash->tPrivate.pfDeleteElement)(ptSymbolHash, v31, (const void *)(ptHead + 28));
              Node_Remove((_DWORD **)ptHead);
              v32 = *(_DWORD *)((unsigned int)(ptHead - 4) & 0xFFFFFFFC);
              --Mem_nCurrentAllocations;
              Node_Remove((_DWORD **)v32);
              memset(*(void **)(v32 + 8), 0xCDu, *(_DWORD *)(v32 + 16));
              free((void *)v32);
              ptHead = (char *)igi2_frame.ptTempFile;
            }
            v33 = igi2_frame.tParserContext.tPCInfoList.ptHead;
            ptNext = igi2_frame.tParserContext.tPCInfoList.ptHead->ptNext;
            for ( j = 0; ptNext; ptNext = ptNext->ptNext )
            {
              nArgs = v33->nArgs;
              v37 = igi2_frame.nSize;
              *(_WORD *)(igi2_frame.nSize + v33->nPC) = nArgs;
              v38 = v33->nPC;
              *(_DWORD *)igi2_frame.tGetNameContext.zName = nArgs;
              nArgs >>= 16;
              *(_BYTE *)(v37 + v38 + 2) = nArgs;
              *(_BYTE *)(v37 + v33->nPC + 3) = BYTE1(nArgs);
              v39 = *(_DWORD *)((unsigned int)(Node_Remove(v33) - 1) & 0xFFFFFFFC);
              --Mem_nCurrentAllocations;
              Node_Remove((_DWORD **)v39);
              memset(*(void **)(v39 + 8), 0xCDu, *(_DWORD *)(v39 + 16));
              free((void *)v39);
              v33 = ptNext;
            }
            v40 = igi2_frame.tParserContext.tIdentifierList.ptHead;
            igi2_frame.tQVMRaw.tRAWHeader.nLOOP = 1347374924;
            igi2_frame.tQVMRaw.tRAWHeader.nID = 8;
            igi2_frame.tQVMRaw.nDefaultStackElements = 0;
            igi2_frame.tQVMRaw.nDefaultStackSize = 0;
            igi2_frame.tQVMRaw.nVersion = 7;
            v41 = igi2_frame.tParserContext.tIdentifierList.ptHead->ptNext;
            v42 = 0;
            for ( k = 0; v41; ++k )
            {
              v42 += strlen(v40->zIdentifier) + 1;
              v40 = v41;
              v41 = v41->ptNext;
            }
            igi2_frame.tQVMRaw.nIdentifierTableSize = 4 * k;
            v44 = igi2_frame.tParserContext.tStringList.ptHead;
            igi2_frame.tQVMRaw.nIdentifierBufferOffset = 4 * k + 64;
            igi2_frame.tQVMRaw.nIdentifierBufferSize = v42;
            igi2_frame.tQVMRaw.nIdentifierTableOffset = 64;
            v45 = igi2_frame.tParserContext.tStringList.ptHead->ptNext;
            v46 = v42 + igi2_frame.tQVMRaw.nIdentifierBufferOffset;
            for ( m = 0; v45; ++j )
            {
              m += strlen(v44->zString) + 1;
              v44 = v45;
              v45 = v45->ptNext;
            }
            v48 = 4 * j;
            igi2_frame.tQVMRaw.nStringTableOffset = v46;
            v49 = v48 + v46;
            igi2_frame.tQVMRaw.nStringTableSize = v48;
            igi2_frame.tQVMRaw.nStringBufferSize = m;
            v50 = v49 + m;
            igi2_frame.tQVMRaw.nStringBufferOffset = v49;
            igi2_frame.tQVMRaw.nProgramOffset = v50;
            igi2_frame.tQVMRaw.nProgramSize = igi2_frame.nPC;
            if ( zFileInfo )
              igi2_frame.tQVMRaw.nFileInfoOffset = igi2_frame.nPC + v50;
            else
              igi2_frame.tQVMRaw.nFileInfoOffset = 0;
            v51 = igi2_frame.ptFile;
            File_atDevice[igi2_frame.ptFile->eDeviceID].pfWrite(igi2_frame.ptFile->eDeviceID, igi2_frame.ptFile, &igi2_frame.tQVMRaw, 64u);
            v52 = igi2_frame.tParserContext.tIdentifierList.ptHead;
            igi2_frame.ptTempFile = nullptr;
            v53 = igi2_frame.tParserContext.tIdentifierList.ptHead->ptNext;
            v54 = igi2_frame.tParserContext.tIdentifierList.ptHead;
            if ( igi2_frame.tParserContext.tIdentifierList.ptHead->ptNext )
            {
              do
              {
                File_atDevice[v51->eDeviceID].pfWrite(v51->eDeviceID, v51, &igi2_frame.ptTempFile, 4u);
                igi2_frame.ptTempFile = (struct File_s *)((char *)igi2_frame.ptTempFile + strlen(v54->zIdentifier) + 1);
                v54 = v53;
                v53 = v53->ptNext;
              }
              while ( v53 );
              v52 = igi2_frame.tParserContext.tIdentifierList.ptHead;
            }
            for ( n = v52->ptNext; n; n = n->ptNext )
            {
              File_atDevice[v51->eDeviceID].pfWrite(v51->eDeviceID, v51, v52->zIdentifier, strlen(v52->zIdentifier) + 1);
              v52 = n;
            }
            v56 = igi2_frame.tParserContext.tStringList.ptHead;
            igi2_frame.ptTempFile = nullptr;
            v57 = igi2_frame.tParserContext.tStringList.ptHead->ptNext;
            v58 = igi2_frame.tParserContext.tStringList.ptHead;
            if ( igi2_frame.tParserContext.tStringList.ptHead->ptNext )
            {
              do
              {
                File_atDevice[v51->eDeviceID].pfWrite(v51->eDeviceID, v51, &igi2_frame.ptTempFile, 4u);
                igi2_frame.ptTempFile = (struct File_s *)((char *)igi2_frame.ptTempFile + strlen(v58->zString) + 1);
                v58 = v57;
                v57 = v57->ptNext;
              }
              while ( v57 );
              v56 = igi2_frame.tParserContext.tStringList.ptHead;
            }
            for ( ii = v56->ptNext; ii; ii = ii->ptNext )
            {
              File_atDevice[v51->eDeviceID].pfWrite(v51->eDeviceID, v51, v56->zString, strlen(v56->zString) + 1);
              v56 = ii;
            }
            v60 = (void *)igi2_frame.nSize;
            File_atDevice[v51->eDeviceID].pfWrite(v51->eDeviceID, v51, (void *)igi2_frame.nSize, igi2_frame.nPC);
            if ( zFileInfo )
              File_atDevice[v51->eDeviceID].pfWrite(v51->eDeviceID, v51, zFileInfo, strlen(zFileInfo) + 1);
            File_Flush(v60);
          }
        }
      }
      else
      {
        QVMAsm_Error(&igi2_frame.tParserContext, "Failed to create temporary file '%s'.", igi2_frame.zQVMTemp);
      }
      QVMAsm_Message("Cleaning up\n");
      v61 = igi2_frame.tParserContext.tIdentifierList.ptHead;
      for ( jj = igi2_frame.tParserContext.tIdentifierList.ptHead->ptNext; jj; jj = jj->ptNext )
      {
        v63 = Node_Remove(v61);
        if ( v63 )
        {
          v64 = *(_DWORD *)((unsigned int)(v63 - 1) & 0xFFFFFFFC);
          --Mem_nCurrentAllocations;
          Node_Remove((_DWORD **)v64);
          memset(*(void **)(v64 + 8), 0xCDu, *(_DWORD *)(v64 + 16));
          free((void *)v64);
        }
        v61 = jj;
      }
      v65 = igi2_frame.tParserContext.tStringList.ptHead;
      for ( kk = igi2_frame.tParserContext.tStringList.ptHead->ptNext; kk; kk = kk->ptNext )
      {
        v67 = Node_Remove(v65);
        if ( v67 )
        {
          v68 = *(_DWORD *)((unsigned int)(v67 - 1) & 0xFFFFFFFC);
          --Mem_nCurrentAllocations;
          Node_Remove((_DWORD **)v68);
          memset(*(void **)(v68 + 8), 0xCDu, *(_DWORD *)(v68 + 16));
          free((void *)v68);
        }
        v65 = kk;
      }
      v69 = igi2_frame.tParserContext.tPCInfoList.ptHead;
      for ( mm = igi2_frame.tParserContext.tPCInfoList.ptHead->ptNext; mm; mm = mm->ptNext )
      {
        v71 = Node_Remove(v69);
        if ( v71 )
        {
          v72 = *(_DWORD *)((unsigned int)(v71 - 1) & 0xFFFFFFFC);
          --Mem_nCurrentAllocations;
          Node_Remove((_DWORD **)v72);
          memset(*(void **)(v72 + 8), 0xCDu, *(_DWORD *)(v72 + 16));
          free((void *)v72);
        }
        v69 = mm;
      }
      v73 = igi2_frame.tParserContext.tLabelList.ptHead;
      for ( nn = igi2_frame.tParserContext.tLabelList.ptHead->ptNext; nn; nn = nn->ptNext )
      {
        v75 = (unsigned int *)v73->tLabelReferenceList.ptHead;
        v76 = (unsigned int *)*v75;
        igi2_frame.nSize = *v75;
        if ( igi2_frame.nSize )
        {
          do
          {
            v77 = Node_Remove((_DWORD **)v75);
            if ( v77 )
            {
              v78 = *(_DWORD *)((unsigned int)(v77 - 1) & 0xFFFFFFFC);
              --Mem_nCurrentAllocations;
              Node_Remove((_DWORD **)v78);
              memset(*(void **)(v78 + 8), 0xCDu, *(_DWORD *)(v78 + 16));
              free((void *)v78);
              v76 = (unsigned int *)igi2_frame.nSize;
            }
            v75 = v76;
            v76 = (unsigned int *)*v76;
            igi2_frame.nSize = (unsigned int)v76;
          }
          while ( v76 );
        }
        v79 = igi2_frame.tParserContext.ptSymbolHash;
        v80 = igi2_frame.tParserContext.ptSymbolHash->tPrivate.pfHashFunction(
                igi2_frame.tParserContext.ptSymbolHash->tPrivate.nHashTableSize,
                v73->zLabel);
        ((void  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))v79->tPrivate.pfDeleteElement)(v79, v80, (const void *)(v73->zLabel));
        Node_Remove(v73);
        v81 = *(_DWORD *)((unsigned int)&v73[-1].zLabel[124] & 0xFFFFFFFC);
        --Mem_nCurrentAllocations;
        Node_Remove((_DWORD **)v81);
        memset(*(void **)(v81 + 8), 0xCDu, *(_DWORD *)(v81 + 16));
        free((void *)v81);
        v73 = nn;
      }
      v82 = igi2_frame.tParserContext.ptSymbolHash;
      if ( igi2_frame.tParserContext.ptSymbolHash->tPrivate.nEntries )
        igi2_frame.tParserContext.ptSymbolHash->tPrivate.pfMap(
          igi2_frame.tParserContext.ptSymbolHash,
          QHashTable_DeleteElementCallback,
          nullptr);
      papxElement = v82->tPrivate.papxElement;
      if ( papxElement )
      {
        v84 = *(_DWORD *)(((int)papxElement - 4) & 0xFFFFFFFC);
        --Mem_nCurrentAllocations;
        Node_Remove((_DWORD **)v84);
        memset(*(void **)(v84 + 8), 0xCDu, *(_DWORD *)(v84 + 16));
        free((void *)v84);
      }
      v85 = Mem_nCurrentAllocations;
      v82->tPrivate.papxElement = nullptr;
      v86 = *(_DWORD *)((unsigned int)&v82[-1].tPrivate.pfMap & 0xFFFFFFFC);
      Mem_nCurrentAllocations = v85 - 1;
      Node_Remove((_DWORD **)v86);
      memset(*(void **)(v86 + 8), 0xCDu, *(_DWORD *)(v86 + 16));
      free((void *)v86);
      File_Remove(igi2_frame.zQVMTemp);
      if ( igi2_frame.tInp.zBuffer )
      {
        v87 = *(_DWORD *)((int)(igi2_frame.tInp.zBuffer - 4) & 0xFFFFFFFC);
        --Mem_nCurrentAllocations;
        Node_Remove((_DWORD **)v87);
        memset(*(void **)(v87 + 8), 0xCDu, *(_DWORD *)(v87 + 16));
        free((void *)v87);
      }
      igi2_frame.tInp.zBuffer = nullptr;
      QVMParser_DeAlloc(&igi2_frame.tQVMParser);
      QVMParserPatternList_DeAlloc(&igi2_frame.tTokenList);
      v88 = Resource_tResourceList.ptHead;
      v89 = Resource_tResourceList.ptHead->ptNext;
      if ( Resource_tResourceList.ptHead->ptNext )
      {
        while ( v88->pxData != igi2_frame.pxBuffer )
        {
          v88 = v89;
          v89 = v89->ptNext;
          if ( !v89 )
            goto LABEL_9;
        }
        nType = v88->nType;
        if ( nType != 3 && nType != 1 )
          Resource_Remove(v88);
      }
    }
    else
    {
      QVMAsm_Error(&igi2_frame.tParserContext, "Failed to load assembler source file: '%s'", zSourceFile);
    }
LABEL_9:
    if ( igi2_frame.ptFile == &File_tDummyAsyncFile )
      File_tDummyAsyncFile.isAsync = false;
    else
      File_atDevice[igi2_frame.ptFile->eDeviceID].pfDelete(igi2_frame.ptFile->eDeviceID, igi2_frame.ptFile);
  }
  else
  {
    QVMAsm_Error(&igi2_frame.tParserContext, "Failed to open file '%s' for writing.", zDestinationFile);
  }
  if ( igi2_frame.tToken.zAlloc && igi2_frame.tToken.zToken )
  {
    v91 = *(_DWORD *)((int)(igi2_frame.tToken.zToken - 4) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v91);
    memset(*(void **)(v91 + 8), 0xCDu, *(_DWORD *)(v91 + 16));
    free((void *)v91);
  }
  return QVMAsm_nErrors;
}

// source: c/0/qvmasm.c:1041  [anchor-hash]
void __cdecl QVMAsm_Open()
{
  QVMAsm_pfErrorCallback = nullptr;
  QVMAsm_pfWarningCallback = nullptr;
  QVMAsm_pfMessageCallback = nullptr;
  QVMAsm_pxErrorContext = nullptr;
  QVMAsm_pxWarningContext = nullptr;
  QVMAsm_pxMessageContext = nullptr;
  QVMOpCode_LinkAsmHandlers();
}

// source: c/0/qvmasm.c:1060  [size]
void __cdecl QVMAsm_Close()
{
  ;
}
