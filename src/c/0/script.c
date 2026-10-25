/* c/0/script.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: c/0/script.c:109  [anchor-callee]
void Script_Error(char *zFormat, ...)
{
  char Buffer[1024]; // [esp+0h] [ebp-400h] BYREF
  va_list ArgList; // [esp+408h] [ebp+8h] BYREF ARGSLOT

  va_start(ArgList, zFormat);
  Script_isError = true;
  if ( Script_nWarningLevel )
  {
    vsprintf(Buffer, zFormat, ArgList);
    if ( Script_pfErrorCallback )
      Script_pfErrorCallback(Buffer, Script_pxErrorContext);
  }
}

// source: c/0/script.c:142  [size]
void Script_Warning(char *zFormat, ...)
{
  char Buffer[1024]; // [esp+0h] [ebp-400h] BYREF
  va_list ArgList; // [esp+408h] [ebp+8h] BYREF ARGSLOT

  va_start(ArgList, zFormat);
  if ( Script_pfWarningCallback )
  {
    vsprintf(Buffer, zFormat, ArgList);
    Script_pfWarningCallback(Buffer, Script_pxWarningContext);
  }
}

// source: c/0/script.c:167  [size]
void Script_Message(char *zFormat, ...)
{
  char Buffer[1024]; // [esp+0h] [ebp-400h] BYREF
  va_list ArgList; // [esp+408h] [ebp+8h] BYREF ARGSLOT

  va_start(ArgList, zFormat);
  if ( Script_pfMessageCallback )
  {
    vsprintf(Buffer, zFormat, ArgList);
    Script_pfMessageCallback(Buffer, Script_pxMessageContext);
  }
}

// source: c/0/script.c:194  [size]
struct Result_s *__cdecl Script__Break(
        struct Result_s *retstr,
        void *pxUnused,
        struct ArgList_s *aArgs)
{
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  Script_isBreak = true;
  return retstr;
}

// source: c/0/script.c:208  [size]
struct Result_s *__cdecl Script__SetWarningLevel(
        struct Result_s *retstr,
        void *pxUnused,
        struct ArgList_s *aArgs)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = aArgs;
  if ( aArgs->isQVM )
  {
    aArgs = nullptr;
    QVM_EvalArg(&aArgs, 4, v3, 0, 1);
    v4 = aArgs;
  }
  else
  {
    v4 = (struct ArgList_s *)Expression_EvalInt(*aArgs->aptExpression);
  }
  Script_nWarningLevel = (int)v4;
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: c/0/script.c:224  [size]
struct Result_s *__cdecl Script_Bool(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+4h] [ebp-18h] BYREF

  Rs.nResult = *(_DWORD *)pxContext;
  Rs.vResult = (double)Rs.nResult;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: c/0/script.c:239  [size]
struct Result_s *__cdecl Script_Int(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+4h] [ebp-18h] BYREF

  Rs.nResult = *(_DWORD *)pxContext;
  Rs.vResult = (double)Rs.nResult;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: c/0/script.c:254  [size]
struct Result_s *__cdecl Script_Int32(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+4h] [ebp-18h] BYREF

  Rs.nResult = *(_DWORD *)pxContext;
  Rs.vResult = (double)Rs.nResult;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: c/0/script.c:269  [size]
struct Result_s *__cdecl Script_Int16(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  Rs.nResult = *(__int16 *)pxContext;
  Rs.vResult = (double)Rs.nResult;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: c/0/script.c:284  [size]
struct Result_s *__cdecl Script_Int8(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  Rs.nResult = *(char *)pxContext;
  Rs.vResult = (double)Rs.nResult;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: c/0/script.c:299  [size]
struct Result_s *__cdecl Script_ConstInt(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+0h] [ebp-18h] BYREF

  Rs.nResult = (int)pxContext;
  Rs.vResult = (double)(int)pxContext;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: c/0/script.c:314  [anchor-mhash]
struct Result_s *__cdecl Script_Float(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { __int64 v5; };
    struct { char igi2_o1[8]; struct Result_s Rs; };
    char igi2_extent[32];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v3; // edx

  v3 = *(_DWORD *)pxContext;
  igi2_frame.v5 = (__int64)*(double *)pxContext;
  HIDWORD(igi2_frame.Rs.vResult) = *((_DWORD *)pxContext + 1);
  igi2_frame.Rs.nResult = igi2_frame.v5;
  LODWORD(igi2_frame.Rs.vResult) = v3;
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: c/0/script.c:329  [anchor-mhash]
struct Result_s *__cdecl Script_String(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  Rs.zResult = (char *)pxContext;
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: c/0/script.c:346  [size]
enum bool *__cdecl Script_RegisterDynamicBool(char *zName, enum bool *pnVar)
{
  enum bool *result; // eax

  Symbol_Register(
    zName,
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Bool,
    pnVar,
    4,
    QSCRIPT_SYMBOLCLASS_VARIABLE,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_FINITE);
  return result;
}

// source: c/0/script.c:359  [size]
int *__cdecl Script_RegisterDynamicInt(char *zVariableName, int *pnValue)
{
  int *result; // eax

  Symbol_Register(
    zVariableName,
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int,
    pnValue,
    4,
    QSCRIPT_SYMBOLCLASS_VARIABLE,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_FINITE);
  return result;
}

// source: c/0/script.c:372  [anchor-hash]
char *__cdecl Script_RegisterDynamicInt8(char *zVariableName, char *pnValue)
{
  char *result; // eax

  Symbol_Register(
    zVariableName,
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
    pnValue,
    1,
    QSCRIPT_SYMBOLCLASS_VARIABLE,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_FINITE);
  return result;
}

// source: c/0/script.c:385  [anchor-hash]
__int16 *__cdecl Script_RegisterDynamicInt16(char *zVariableName, __int16 *pnValue)
{
  __int16 *result; // eax

  Symbol_Register(
    zVariableName,
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int16,
    pnValue,
    2,
    QSCRIPT_SYMBOLCLASS_VARIABLE,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_FINITE);
  return result;
}

// source: c/0/script.c:398  [size]
int *__cdecl Script_RegisterDynamicInt32(char *zVariableName, int *pnValue)
{
  int *result; // eax

  Symbol_Register(
    zVariableName,
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int,
    pnValue,
    4,
    QSCRIPT_SYMBOLCLASS_VARIABLE,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_FINITE);
  return result;
}

// source: c/0/script.c:411  [anchor-hash]
double *__cdecl Script_RegisterDynamicFloat(char *zVariableName, double *pvValue)
{
  double *result; // eax

  Symbol_Register(
    zVariableName,
    Script_Float,
    pvValue,
    8,
    QSCRIPT_SYMBOLCLASS_VARIABLE,
    QSCRIPT_SYMBOLTYPE_FLOAT,
    QSCRIPT_SYMBOLLIFESPAN_FINITE);
  return result;
}

// source: c/0/script.c:424  [size]
int __cdecl Script_RegisterDynamicString(
        char *zVariableName,
        char *zVariable,
        int nSize)
{
  int result; // eax

  Symbol_Register(
    zVariableName,
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_String,
    zVariable,
    nSize,
    QSCRIPT_SYMBOLCLASS_VARIABLE,
    QSCRIPT_SYMBOLTYPE_STRING,
    QSCRIPT_SYMBOLLIFESPAN_FINITE);
  return result;
}

// source: c/0/script.c:437  [size]
// attributes: thunk
void __cdecl Script_RemoveDynamicSymbol(char *zVariableName)
{
  char *v1; // eax

  Symbol_Remove(v1);
}

// source: c/0/script.c:450  [size]
enum bool __cdecl Script_Exists(char *zFilename)
{
  unsigned int i; // eax
  char zCompiledFileName[260]; // [esp+4h] [ebp-104h] BYREF

  if ( AppContext_tAppContext.isTerrainLightmapsDisabled )
  {
    strcpy(zCompiledFileName, zFilename);
    for ( i = strlen(zCompiledFileName); i; --i )
    {
      if ( zCompiledFileName[i] == 46 )
        break;
    }
    strcpy(&zCompiledFileName[i], ".qvm");
    if ( Resource_IsLoadedInternal(zCompiledFileName, nullptr) || File_Exists(zCompiledFileName) )
      return true;
  }
  if ( Resource_IsLoadedInternal(zFilename, nullptr) )
    return true;
  else
    return File_Exists(zFilename);
}

// source: c/0/script.c:486  [anchor-strings]
struct Script_s *__cdecl Script_New(char *zFilename)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QVM_s *ptQVM; };
    struct { char igi2_o1[4]; struct FileTime_s nLen; };
    struct { char igi2_o2[12]; struct FileTime_s tQVMFileTime; };
    struct { char igi2_o3[20]; char zCompiledFileName[264]; };
    struct { char igi2_o4[284]; char zAssemblyFileName[264]; };
    char igi2_extent[548];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  _BYTE *v1; // ebp
  unsigned int i; // eax
  struct Script_s *result; // eax
  struct Script_s *v4; // ebx
  DWORD dwLowDateTime; // edi
  struct QVM_s *v6; // eax
  unsigned int j; // eax
  struct Script_s *v8; // ebx
  struct QVM_s *v9; // eax
  int v10; // esi

  v1 = nullptr;
  igi2_frame.ptQVM = nullptr;
  if ( AppContext_tAppContext.isTerrainLightmapsDisabled == false )
  {
LABEL_15:
    if ( Resource_IsLoadedInternal(zFilename, nullptr) == false && File_Exists(zFilename) == false )
      return nullptr;
    v1 = Resource_Load(zFilename, &igi2_frame.nLen.tFileTime.dwLowDateTime);
    if ( !v1 )
      return nullptr;
    goto LABEL_18;
  }
  strcpy(igi2_frame.zCompiledFileName, zFilename);
  for ( i = strlen(igi2_frame.zCompiledFileName); i; --i )
  {
    if ( igi2_frame.zCompiledFileName[i] == 46 )
      break;
  }
  strcpy(&igi2_frame.zCompiledFileName[i], ".qvm");
  if ( Resource_IsLoadedInternal(zFilename, nullptr) || File_Exists(zFilename) )
  {
    if ( Resource_IsLoadedInternal(igi2_frame.zCompiledFileName, nullptr) || File_Exists(igi2_frame.zCompiledFileName) )
    {
      Resource_GetFileTime(&igi2_frame.tQVMFileTime, igi2_frame.zCompiledFileName);
      Resource_GetFileTime(&igi2_frame.nLen, zFilename);
      if ( CompareFileTime(&igi2_frame.tQVMFileTime.tFileTime, &igi2_frame.nLen.tFileTime) >= 0 )
      {
        igi2_frame.ptQVM = QVM_Load(igi2_frame.zCompiledFileName, 0, 0);
        if ( igi2_frame.ptQVM )
          goto LABEL_18;
      }
    }
    goto LABEL_15;
  }
  if ( Resource_IsLoadedInternal(igi2_frame.zCompiledFileName, nullptr) == false && File_Exists(igi2_frame.zCompiledFileName) == false )
    return nullptr;
  result = (struct Script_s *)QVM_Load(igi2_frame.zCompiledFileName, 0, 0);
  igi2_frame.ptQVM = (struct QVM_s *)result;
  if ( !result )
    return result;
LABEL_18:
  v4 = (struct Script_s *)Mem_AllocFn(148, 4);
  memset(v4, 0, sizeof(struct Script_s));
  dwLowDateTime = igi2_frame.nLen.tFileTime.dwLowDateTime;
  Script_isBreakEnabled = false;
  if ( v1
    && igi2_frame.nLen.tFileTime.dwLowDateTime >= 0x40
    && *v1 == 76
    && v1[1] == 79
    && v1[2] == 79
    && v1[3] == 80
    && *((_DWORD *)v1 + 1) == 8
    && *((int *)v1 + 2) >= 7 )
  {
    v6 = QVM_CreateFromBuffer(v1, igi2_frame.nLen.tFileTime.dwLowDateTime, 0, 0);
  }
  else
  {
    v6 = igi2_frame.ptQVM;
  }
  if ( v6 )
  {
    v4->ptQVM = v6;
    v4->isCompiled = 1;
    strcpy(v4->zFilename, igi2_frame.zCompiledFileName);
    return v4;
  }
  if ( AppContext_tAppContext.isQVMUsed )
  {
    Resource_Flush(v1);
    if ( v4 )
    {
      v10 = *(_DWORD *)((unsigned int)&v4[-1].isCompiled & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v10);
      memset(*(void **)(v10 + 8), 0xCDu, *(_DWORD *)(v10 + 16));
      free((void *)v10);
    }
    return nullptr;
  }
  v4->zScript = v1;
  v4->nSize = dwLowDateTime;
  v4->nPos = 0;
  strcpy(v4->zFilename, zFilename);
  if ( AppContext_tAppContext.isTerrainLightmapsDisabled == false )
    return v4;
  strcpy(igi2_frame.zAssemblyFileName, zFilename);
  for ( j = strlen(igi2_frame.zAssemblyFileName); j; --j )
  {
    if ( igi2_frame.zAssemblyFileName[j] == 46 )
      break;
  }
  strcpy(&igi2_frame.zAssemblyFileName[j], ".qas");
  File_Remove(igi2_frame.zCompiledFileName);
  File_Remove(igi2_frame.zAssemblyFileName);
  if ( ScriptCompiler_CompileScript(igi2_frame.zAssemblyFileName, v4) )
  {
    Script_Delete(v4);
    Script_Error("An error occured when compiling file: %s", zFilename);
    return nullptr;
  }
  if ( QVMAsm_Assemble(igi2_frame.zCompiledFileName, igi2_frame.zAssemblyFileName, nullptr) )
  {
    Script_Error("An error occured when compiling file: %s", zFilename);
    return v4;
  }
  else
  {
    File_Remove(igi2_frame.zAssemblyFileName);
    Script_Delete(v4);
    v8 = (struct Script_s *)Mem_AllocFn(148, 4);
    memset(v8, 0, sizeof(struct Script_s));
    v9 = QVM_Load(igi2_frame.zCompiledFileName, 0, 0);
    if ( v9 )
    {
      v8->ptQVM = v9;
      v8->isCompiled = 1;
      strcpy(v8->zFilename, igi2_frame.zCompiledFileName);
      return v8;
    }
    else
    {
      Script_Error("Failed to load QVM file: %s", igi2_frame.zCompiledFileName);
      Mem_DeAllocFn(v8);
      return nullptr;
    }
  }
}

// source: c/0/script.c:650  [anchor-callee]
void __cdecl Script_Delete(struct Script_s *ptScript)
{
  struct QVM_s *ptQVM; // eax
  int v3; // eax
  int v4; // esi
  char zFilename[4]; // [esp+Ch] [ebp-4h] BYREF

  ptQVM = ptScript->ptQVM;
  if ( ptQVM )
  {
    QVM_Delete(ptQVM);
  }
  else if ( Resource_IsLoadedInternal(ptScript->zFilename, (struct Resource_s **)zFilename) )
  {
    v3 = *(_DWORD *)(*(_DWORD *)zFilename + 36);
    if ( v3 != 3 && v3 != 1 )
      Resource_Remove(*(struct Resource_s **)zFilename);
  }
  v4 = *(_DWORD *)((unsigned int)&ptScript[-1].isCompiled & 0xFFFFFFFC);
  --Mem_nCurrentAllocations;
  Node_Remove((_DWORD **)v4);
  memset(*(void **)(v4 + 8), 0xCDu, *(_DWORD *)(v4 + 16));
  free((void *)v4);
}

// source: c/0/script.c:672  [anchor-strings]
void __cdecl Script_CompileEx(char *zFilename, char *zCompiledFilename, char *zFileInfo)
{
  #pragma pack(push, 1)
  union
  {
    struct { unsigned int nLen; };
    struct { char igi2_o1[4]; char zAssemblyFilename[264]; };
    char igi2_extent[268];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char *v3; // eax
  char *v4; // ebx
  struct Script_s *v5; // esi
  unsigned int i; // eax

  if ( Resource_IsLoadedInternal(zFilename, nullptr) || File_Exists(zFilename) )
  {
    v3 = (char *)Resource_Load(zFilename, &igi2_frame.nLen);
    v4 = v3;
    if ( !v3
      || igi2_frame.nLen < 0x40
      || *v3 != 76
      || v3[1] != 79
      || v3[2] != 79
      || v3[3] != 80
      || *((_DWORD *)v3 + 1) != 8
      || *((int *)v3 + 2) < 7 )
    {
      v5 = (struct Script_s *)Mem_AllocFn(148, 4);
      memset(v5, 0, sizeof(struct Script_s));
      v5->nSize = igi2_frame.nLen;
      v5->zScript = v4;
      v5->nPos = 0;
      strcpy(v5->zFilename, zFilename);
      strcpy(igi2_frame.zAssemblyFilename, zFilename);
      for ( i = strlen(igi2_frame.zAssemblyFilename); i; --i )
      {
        if ( igi2_frame.zAssemblyFilename[i] == 46 )
          break;
      }
      strcpy(&igi2_frame.zAssemblyFilename[i], ".qas");
      File_Remove(zCompiledFilename);
      File_Remove(igi2_frame.zAssemblyFilename);
      if ( ScriptCompiler_CompileScript(igi2_frame.zAssemblyFilename, v5) )
      {
        Script_Delete(v5);
      }
      else if ( !QVMAsm_Assemble(zCompiledFilename, igi2_frame.zAssemblyFilename, zFileInfo) )
      {
        File_Remove(igi2_frame.zAssemblyFilename);
        Script_Delete(v5);
        return;
      }
      Script_Error("An error occured when compiling file: %s", zFilename);
    }
  }
}

// source: c/0/script.c:742  [anchor-strings]
void __cdecl Script_Compile(char *zFilename)
{
  unsigned int i; // eax
  char zCompiledFilename[264]; // [esp+4h] [ebp-108h] BYREF

  strcpy(zCompiledFilename, zFilename);
  for ( i = strlen(zCompiledFilename); i; --i )
  {
    if ( zCompiledFilename[i] == 46 )
      break;
  }
  strcpy(&zCompiledFilename[i], ".qvm");
  Script_CompileEx(zFilename, zCompiledFilename, "Hello, world!");
}

// source: c/0/script.c:765  [anchor-strings]
void __cdecl Script_Execute(struct Script_s *ptScript)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct ScriptControlBlock_s *ptBlock; };
    struct { char igi2_o1[4]; struct ParseContext_s tCtxt; };
    struct { char igi2_o2[52]; struct InputStream_s tInp; };
    struct { char igi2_o3[84]; char zTokenBuffer[2048]; };
    char igi2_extent[2136];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QVM_s *ptQVM; // eax
  int nSize; // edx
  char *zScript; // eax
  struct ScriptControlBlock_s *v5; // esi
  int v6; // esi

  ptQVM = ptScript->ptQVM;
  Script_isBreak = false;
  Script_isError = false;
  if ( ptQVM )
  {
    if ( QVM_Execute(ptQVM) )
    {
      Script_Error("Error in QVM program: %s\r\n%s", ptScript->zFilename, ptScript->ptQVM->zError);
      Script_isBreak = false;
      return;
    }
  }
  else
  {
    igi2_frame.tCtxt.tToken.zToken = igi2_frame.zTokenBuffer;
    nSize = ptScript->nSize;
    igi2_frame.tCtxt.tToken.ptHead = (struct QTokenItem_s *)&igi2_frame.tCtxt.tToken.ptMiddle;
    zScript = ptScript->zScript;
    igi2_frame.tCtxt.ptInputStream = &igi2_frame.tInp;
    igi2_frame.tCtxt.tToken.nMaxTokenSize = 2048;
    igi2_frame.tCtxt.tToken.ptTail = (struct QTokenItem_s *)&igi2_frame.tCtxt.tToken;
    igi2_frame.tCtxt.tToken.ptMiddle = nullptr;
    InputStream_Alloc(&igi2_frame.tInp, zScript, nSize, SingleLine_GetInput);
    while ( Script_isBreakEnabled == false || Script_isBreak == false )
    {
      igi2_frame.ptBlock = nullptr;
      if ( Token_GetToken(&igi2_frame.tCtxt, &igi2_frame.tCtxt.tToken) == false )
        break;
      if ( ScriptControl_ParseStatementBlock(&igi2_frame.tCtxt, &igi2_frame.ptBlock) )
      {
        v5 = igi2_frame.ptBlock;
        ScriptControlBlock_Execute(igi2_frame.ptBlock);
        ScriptControlBlock_Delete(v5);
        if ( Script_isError == false )
          continue;
      }
      if ( Script_nWarningLevel )
        Script_Error("An error occured in script file: %s", ptScript->zFilename);
      Script_isError = false;
      break;
    }
    if ( igi2_frame.tInp.zBuffer )
    {
      v6 = *(_DWORD *)((int)(igi2_frame.tInp.zBuffer - 4) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v6);
      memset(*(void **)(v6 + 8), 0xCDu, *(_DWORD *)(v6 + 16));
      free((void *)v6);
    }
  }
  Script_isBreak = false;
}

// source: c/0/script.c:839  [anchor-callee]
struct QExpression_s *__cdecl Script_ParseLine(char *zLine)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QExpression_s *ptExpression; };
    struct { char igi2_o1[4]; struct ParseContext_s tParseContext; };
    struct { char igi2_o2[52]; struct InputStream_s tInputStream; };
    struct { char igi2_o3[84]; char zTokenBuffer[2048]; };
    char igi2_extent[2136];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  igi2_frame.tParseContext.ptInputStream = &igi2_frame.tInputStream;
  igi2_frame.tParseContext.tToken.zToken = igi2_frame.zTokenBuffer;
  igi2_frame.tParseContext.tToken.ptHead = (struct QTokenItem_s *)&igi2_frame.tParseContext.tToken.ptMiddle;
  igi2_frame.tParseContext.tToken.nMaxTokenSize = 2048;
  igi2_frame.tParseContext.tToken.ptTail = (struct QTokenItem_s *)&igi2_frame.tParseContext.tToken;
  igi2_frame.tParseContext.tToken.ptMiddle = nullptr;
  InputStream_Alloc(&igi2_frame.tInputStream, (void *)zLine, strlen(zLine), SingleLine_GetInput);
  if ( Token_GetToken(&igi2_frame.tParseContext, &igi2_frame.tParseContext.tToken) && Expression_Parse(&igi2_frame.tParseContext, &igi2_frame.ptExpression, 0, 0) )
  {
    InputStream_DeAlloc(&igi2_frame.tInputStream);
    return igi2_frame.ptExpression;
  }
  else
  {
    InputStream_DeAlloc(&igi2_frame.tInputStream);
    Script_isError = false;
    return nullptr;
  }
}

// source: c/0/script.c:874  [anchor-callee]
char *__cdecl Script_ParseLineString(char *zBuffer, unsigned int nBufferSize, char *zLine)
{
  struct QExpression_s *v3; // esi

  v3 = Script_ParseLine(zLine);
  if ( v3 )
  {
    Expression_EvalString(v3, zBuffer, nBufferSize);
    Expression_Delete(v3);
  }
  Script_isError = false;
  return zBuffer;
}

// source: c/0/script.c:897  [anchor-callee]
int __cdecl Script_ParseLineInt32(char *zLine)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QExpression_s *ptExp; };
    struct { char igi2_o1[4]; struct ParseContext_s tCtxt; };
    struct { char igi2_o2[52]; struct InputStream_s tInp; };
    struct { char igi2_o3[84]; char zTokenBuffer[2048]; };
    char igi2_extent[2136];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QExpression_s *v1; // esi
  int v2; // edi

  igi2_frame.tCtxt.ptInputStream = &igi2_frame.tInp;
  igi2_frame.tCtxt.tToken.zToken = igi2_frame.zTokenBuffer;
  igi2_frame.tCtxt.tToken.ptHead = (struct QTokenItem_s *)&igi2_frame.tCtxt.tToken.ptMiddle;
  igi2_frame.tCtxt.tToken.nMaxTokenSize = 2048;
  igi2_frame.tCtxt.tToken.ptTail = (struct QTokenItem_s *)&igi2_frame.tCtxt.tToken;
  igi2_frame.tCtxt.tToken.ptMiddle = nullptr;
  InputStream_Alloc(&igi2_frame.tInp, (void *)zLine, strlen(zLine), SingleLine_GetInput);
  if ( Token_GetToken(&igi2_frame.tCtxt, &igi2_frame.tCtxt.tToken) && Expression_Parse(&igi2_frame.tCtxt, &igi2_frame.ptExp, 0, 0) )
  {
    v1 = igi2_frame.ptExp;
    v2 = Expression_EvalInt(igi2_frame.ptExp);
    Expression_Delete(v1);
    InputStream_DeAlloc(&igi2_frame.tInp);
    Script_isError = false;
    return v2;
  }
  else
  {
    InputStream_DeAlloc(&igi2_frame.tInp);
    Script_isError = false;
    return 0;
  }
}

// source: c/0/script.c:940  [anchor-callee]
double __cdecl Script_ParseLineFloat(char *zLine)
{
  #pragma pack(push, 1)
  union
  {
    struct { double ptExp; };
    struct { char igi2_o1[8]; struct ParseContext_s tCtxt; };
    struct { char igi2_o2[56]; struct InputStream_s tInp; };
    struct { char igi2_o3[88]; char zTokenBuffer[2048]; };
    char igi2_extent[2140];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QExpression_s *v1; // esi

  igi2_frame.tCtxt.ptInputStream = &igi2_frame.tInp;
  igi2_frame.tCtxt.tToken.zToken = igi2_frame.zTokenBuffer;
  igi2_frame.tCtxt.tToken.ptHead = (struct QTokenItem_s *)&igi2_frame.tCtxt.tToken.ptMiddle;
  igi2_frame.tCtxt.tToken.nMaxTokenSize = 2048;
  igi2_frame.tCtxt.tToken.ptTail = (struct QTokenItem_s *)&igi2_frame.tCtxt.tToken;
  igi2_frame.tCtxt.tToken.ptMiddle = nullptr;
  InputStream_Alloc(&igi2_frame.tInp, (void *)zLine, strlen(zLine), SingleLine_GetInput);
  if ( Token_GetToken(&igi2_frame.tCtxt, &igi2_frame.tCtxt.tToken) && Expression_Parse(&igi2_frame.tCtxt, (struct QExpression_s **)&igi2_frame.ptExp, 0, 0) )
  {
    v1 = (struct QExpression_s *)LODWORD(igi2_frame.ptExp);
    igi2_frame.ptExp = Expression_EvalFloat((struct QExpression_s *)LODWORD(igi2_frame.ptExp));
    Expression_Delete(v1);
    InputStream_DeAlloc(&igi2_frame.tInp);
    Script_isError = false;
    return igi2_frame.ptExp;
  }
  else
  {
    InputStream_DeAlloc(&igi2_frame.tInp);
    Script_isError = false;
    return 0.0;
  }
}

// source: c/0/script.c:983  [size]
enum bool *__cdecl Script_RegisterBool(char *zName, enum bool *pnVar)
{
  enum bool *result; // eax

  Symbol_Register(
    zName,
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Bool,
    pnVar,
    4,
    QSCRIPT_SYMBOLCLASS_VARIABLE,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  return result;
}

// source: c/0/script.c:998  [size]
int *__cdecl Script_RegisterInt(char *zName, int *pnVar)
{
  int *result; // eax

  Symbol_Register(
    zName,
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int,
    pnVar,
    4,
    QSCRIPT_SYMBOLCLASS_VARIABLE,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  return result;
}

// source: c/0/script.c:1013  [size]
int *__cdecl Script_RegisterInt32(char *zName, int *pnVar)
{
  int *result; // eax

  Symbol_Register(
    zName,
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int32,
    pnVar,
    4,
    QSCRIPT_SYMBOLCLASS_VARIABLE,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  return result;
}

// source: c/0/script.c:1028  [anchor-hash]
__int16 *__cdecl Script_RegisterInt16(char *zName, __int16 *pnVar)
{
  __int16 *result; // eax

  Symbol_Register(
    zName,
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int16,
    pnVar,
    2,
    QSCRIPT_SYMBOLCLASS_VARIABLE,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  return result;
}

// source: c/0/script.c:1043  [anchor-hash]
char *__cdecl Script_RegisterInt8(char *zName, char *pnVar)
{
  char *result; // eax

  Symbol_Register(
    zName,
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
    pnVar,
    1,
    QSCRIPT_SYMBOLCLASS_VARIABLE,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  return result;
}

// source: c/0/script.c:1058  [anchor-hash]
int __cdecl Script_RegisterConst(char *zName, int nValue)
{
  int result; // eax

  Symbol_Register(
    zName,
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)nValue,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  return result;
}

// source: c/0/script.c:1075  [anchor-hash]
double *__cdecl Script_RegisterFloat(char *zName, double *pvVar)
{
  double *result; // eax

  Symbol_Register(
    zName,
    Script_Float,
    pvVar,
    8,
    QSCRIPT_SYMBOLCLASS_VARIABLE,
    QSCRIPT_SYMBOLTYPE_FLOAT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  return result;
}

// source: c/0/script.c:1092  [size]
int __cdecl Script_RegisterString(char *zName, char *zString, int nSize)
{
  int result; // eax

  Symbol_Register(
    zName,
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_String,
    zString,
    nSize,
    QSCRIPT_SYMBOLCLASS_VARIABLE,
    QSCRIPT_SYMBOLTYPE_STRING,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  return result;
}

// source: c/0/script.c:1107  [size]
int __cdecl Script_RegisterFunction(
        char *zName,
        struct Result_s *(__cdecl *pfCB_)(struct Result_s *retstr, void *, struct ArgList_s *),
        void *pxContext,
        int nArgs)
{
  int result; // eax

  Symbol_Register(
    zName,
    pfCB_,
    pxContext,
    nArgs,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  return result;
}

// source: c/0/script.c:1122  [size]
int __cdecl Script_RegisterIntFunction(
        char *zName,
        struct Result_s *(__cdecl *pfCB_)(struct Result_s *retstr, void *, struct ArgList_s *),
        void *pxContext,
        int nArgs)
{
  int result; // eax

  Symbol_Register(
    zName,
    pfCB_,
    pxContext,
    nArgs,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  return result;
}

// source: c/0/script.c:1137  [size]
int __cdecl Script_RegisterRealFunction(
        char *zName,
        struct Result_s *(__cdecl *pfCB_)(struct Result_s *retstr, void *, struct ArgList_s *),
        void *pxContext,
        int nArgs)
{
  int result; // eax

  Symbol_Register(
    zName,
    pfCB_,
    pxContext,
    nArgs,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_FLOAT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  return result;
}

// source: c/0/script.c:1152  [size]
int __cdecl Script_RegisterStringFunction(
        char *zName,
        struct Result_s *(__cdecl *pfCB_)(struct Result_s *retstr, void *, struct ArgList_s *),
        void *pxContext,
        int nArgs)
{
  int result; // eax

  Symbol_Register(
    zName,
    pfCB_,
    pxContext,
    nArgs,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_STRING,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  return result;
}

// source: c/0/script.c:1167  [size]
// attributes: thunk
void __cdecl Script_RemoveSymbol(char *zName)
{
  char *v1; // eax

  Symbol_Remove(v1);
}

// source: c/0/script.c:1182  [anchor-mhash]
void __cdecl Script_SetSymbolContext(char *zName, void *pxContext)
{
  struct QHashTable_s *v2; // esi
  int v3; // eax
  int v4; // eax

  v2 = Symbol_ptSymbolHashTable;
  v3 = Symbol_ptSymbolHashTable->tPrivate.pfHashFunction(Symbol_ptSymbolHashTable->tPrivate.nHashTableSize, zName);
  v4 = ((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Symbol_ptSymbolHashTable->tPrivate.pfFindElement)(v2, v3, (const void *)(zName));
  if ( !v4 || !*(_DWORD *)(v4 + 20) )
  {
    LDebug_Error("Script_SetSymbolContext(): Symbol not found: %s", zName);
    abort();
  }
  *(_DWORD *)(v4 + 24) = pxContext;
}

// source: c/0/script.c:1205  [size]
int __cdecl Script_SetWarningLevel(int nLevel)
{
  Script_nWarningLevel = nLevel;
  return nLevel;
}

// source: c/0/script.c:1218  [anchor-strings]
int __cdecl Script_PushWarningLevel(int a1, int a2)
{
  int result; // eax

  if ( !Script_nSP )
  {
    LDebug_Error("Script: Stack underflow.");
    abort();
  }
  result = Script_nSP - 1;
  Script_nSP = result;
  Script_anWarningLevelStack[result] = Script_nWarningLevel;
  Script_nWarningLevel = a2;
  return result;
}

// source: c/0/script.c:1239  [anchor-hash]
int Script_PopWarningLevel()
{
  int result; // eax

  if ( Script_nSP >= 256 )
  {
    LDebug_Error("Script: Stack overflow.");
    abort();
  }
  result = Script_nSP + 1;
  Script_nWarningLevel = Script_anWarningLevelStack[Script_nSP++];
  return result;
}

// source: c/0/script.c:1259  [size]
int __cdecl Script_SetMaxFunctionArguments(int nArguments)
{
  Script_nMaxFunctionArguments = nArguments;
  return nArguments;
}

// source: c/0/script.c:1272  [size]
int __cdecl Script_SetInputBufferSize(int nSize)
{
  Script_nInputBufferSize = nSize;
  return nSize;
}

// source: c/0/script.c:1285  [size]
int __cdecl Script_EnableBreak(int isEnabled)
{
  Script_isBreakEnabled = isEnabled;
  return isEnabled;
}

// source: c/0/script.c:1298  [anchor-callee]
int __cdecl Script_EvalArgInt(struct ArgList_s *ptArgList, int nArg)
{
  int pxData; // [esp+8h] [ebp-4h] BYREF

  if ( !ptArgList->isQVM )
    return Expression_EvalInt(ptArgList->aptExpression[nArg]);
  pxData = 0;
  QVM_EvalArg(&pxData, 4, ptArgList, nArg, 1);
  return pxData;
}

// source: c/0/script.c:1318  [anchor-callee]
double __cdecl Script_EvalArgFloat(struct ArgList_s *ptArgList, int nArg)
{
  float pxData; // [esp+8h] [ebp-4h] BYREF

  if ( !ptArgList->isQVM )
    return Expression_EvalFloat(ptArgList->aptExpression[nArg]);
  pxData = 0.0;
  QVM_EvalArg(&pxData, 4, ptArgList, nArg, 2);
  return pxData;
}

// source: c/0/script.c:1338  [anchor-callee]
char *__cdecl Script_EvalArgString(
        struct ArgList_s *ptArgList,
        int nArg,
        char *zBuffer,
        int nBufferSize)
{
  if ( !ptArgList->isQVM )
    return Expression_EvalString(ptArgList->aptExpression[nArg], zBuffer, nBufferSize);
  *zBuffer = 0;
  QVM_EvalArg(zBuffer, nBufferSize, ptArgList, nArg, 3);
  return zBuffer;
}

// source: c/0/script.c:1358  [anchor-mhash]
int __cdecl Script_GetArgLinenumber(struct ArgList_s *ptArgList, int nArg)
{
  if ( ptArgList->isQVM )
    return 0;
  else
    return ptArgList->aptExpression[nArg]->nLinenumber;
}

// source: c/0/script.c:1378  [size]
int __cdecl Script_GetNumArguments(struct ArgList_s *ptArgList)
{
  return ptArgList->nArguments;
}

// source: c/0/script.c:1392  [size]
enum bool __cdecl Script_IsArgumentValid(struct ArgList_s *ptArgList, int nArg)
{
  return nArg < ptArgList->nArguments;
}

// source: c/0/script.c:1406  [size]
void *__cdecl Script_SetErrorCallback(
        void (__cdecl *pfCallback)(char *, void *),
        void *pxContext)
{
  Script_pfErrorCallback = pfCallback;
  Script_pxErrorContext = pxContext;
  ScriptCompiler_pfErrorCallback = pfCallback;
  ScriptCompiler_pxErrorContext = pxContext;
  QVMAsm_pfErrorCallback = pfCallback;
  QVMAsm_pxErrorContext = pxContext;
  return pxContext;
}

// source: c/0/script.c:1427  [size]
void *__cdecl Script_SetWarningCallback(
        void (__cdecl *pfCallback)(char *, void *),
        void *pxContext)
{
  Script_pfWarningCallback = pfCallback;
  Script_pxWarningContext = pxContext;
  ScriptCompiler_pfWarningCallback = pfCallback;
  ScriptCompiler_pxWarningContext = pxContext;
  QVMAsm_pfWarningCallback = pfCallback;
  QVMAsm_pxWarningContext = pxContext;
  return pxContext;
}

// source: c/0/script.c:1448  [size]
void *__cdecl Script_SetMessageCallback(
        void (__cdecl *pfCallback)(char *, void *),
        void *pxContext)
{
  Script_pfMessageCallback = pfCallback;
  Script_pxMessageContext = pxContext;
  ScriptCompiler_pfMessageCallback = pfCallback;
  ScriptCompiler_pxMessageContext = pxContext;
  QVMAsm_pfMessageCallback = pfCallback;
  QVMAsm_pxMessageContext = pxContext;
  return pxContext;
}

// source: c/0/script.c:1471  [anchor-caller]
char *__cdecl Script_Remove(char *zFilename)
{
  unsigned int i; // eax
  char *v3; // esi
  char *result; // eax
  char zCompiledFileName[260]; // [esp+4h] [ebp-104h] BYREF

  File_Remove(zFilename);
  strcpy(zCompiledFileName, zFilename);
  for ( i = strlen(zCompiledFileName); i; --i )
  {
    if ( zCompiledFileName[i] == 46 )
      break;
  }
  v3 = &zCompiledFileName[i];
  strcpy(&zCompiledFileName[i], ".qvm");
  File_Remove(zCompiledFileName);
  strcpy(v3, ".qas");
  File_Remove(zCompiledFileName);
  return result;
}

// source: c/0/script.c:1503  [anchor-hash]
char *__cdecl Script_GetFileInfo(struct Script_s *ptScript)
{
  struct QVM_s *ptQVM; // eax

  ptQVM = ptScript->ptQVM;
  if ( ptQVM )
    return ptQVM->zFileInfo;
  else
    return (char *)&g_zInitialValue;
}

// source: c/0/script.c:1529  [anchor-strings]
void __cdecl Script_DirListCallback(
        struct FileDirListCallbackContext_s *ptDirListCallbackContext,
        struct ScriptDirListContext_s *ptScriptDirListContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { char v9; };
    struct { char igi2_o1[1]; char zFilename[260]; };
    char igi2_extent[261];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  enum bool isQVMUsed; // eax
  char *v3; // eax
  int v4; // edx
  char v5; // cl
  unsigned int i; // eax
  char *v7; // edi

  if ( Wildcard_SearchSimple("*.qsc", (void *)ptDirListCallbackContext->zFilename, nullptr, nullptr, nullptr, 1) )
  {
    isQVMUsed = AppContext_tAppContext.isQVMUsed;
    goto LABEL_13;
  }
  if ( Wildcard_SearchSimple("*.qvm", (void *)ptDirListCallbackContext->zFilename, nullptr, nullptr, nullptr, 1) )
  {
    if ( AppContext_tAppContext.isQVMUsed )
    {
LABEL_14:
      ptScriptDirListContext->pfCallback(ptDirListCallbackContext, ptScriptDirListContext->pxContext);
      return;
    }
    v3 = ptDirListCallbackContext->zFilename;
    v4 = igi2_frame.zFilename - ptDirListCallbackContext->zFilename;
    do
    {
      v5 = *v3;
      v3[v4] = *v3;
      ++v3;
    }
    while ( v5 );
    for ( i = strlen(igi2_frame.zFilename); i; --i )
    {
      if ( igi2_frame.zFilename[i] == 46 )
        break;
    }
    igi2_frame.zFilename[i] = 0;
    v7 = &igi2_frame.v9;
    while ( *++v7 )
      ;
    strcpy(v7, ".qsc");
    isQVMUsed = File_Exists(igi2_frame.zFilename);
LABEL_13:
    if ( isQVMUsed )
      return;
    goto LABEL_14;
  }
  if ( ptDirListCallbackContext->isDirectory )
    ptScriptDirListContext->pfCallback(ptDirListCallbackContext, ptScriptDirListContext->pxContext);
}

// source: c/0/script.c:1578  [anchor-mhash]
void __cdecl Script_DirList(
        char *zPath,
        void (__cdecl *pfCallback)(struct FileDirListCallbackContext_s *, void *),
        void *pxContext)
{
  struct ScriptDirListContext_s tScriptDirListContext; // [esp+0h] [ebp-8h] BYREF

  tScriptDirListContext.pfCallback = pfCallback;
  tScriptDirListContext.pxContext = pxContext;
  File_DirList(
    zPath,
    (void (__cdecl *)(struct FileDirListCallbackContext_s *, void *))Script_DirListCallback,
    &tScriptDirListContext);
}

// source: c/0/script.c:1597  [anchor-hash]
void __cdecl Script_Open()
{
  Script_pfErrorCallback = nullptr;
  Script_pfMessageCallback = nullptr;
  Script_pfWarningCallback = nullptr;
  Script_pxErrorContext = nullptr;
  Script_pxWarningContext = nullptr;
  Script_pxMessageContext = nullptr;
  Symbol_Open();
  Script_nWarningLevel = 1;
  Symbol_Register(
    "TRUE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)1,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "ON",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)1,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "FALSE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    nullptr,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    dword_6A4E40,
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    nullptr,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "SCRIPT_WARNINGLEVEL_NO_WARNINGS",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    nullptr,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "SCRIPT_WARNINGLEVEL_NORMAL",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)1,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "SCRIPT_WARNINGLEVEL_HIGH",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)2,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "_Script_SetWarningLevel",
    Script__SetWarningLevel,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "BreakScript",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script__Break,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Script_nInputBufferSize = 2048;
  Script_nMaxFunctionArguments = 0x2000;
  Script_nSP = 256;
  QVM_Open();
  ScriptCompiler_pfErrorCallback = nullptr;
  ScriptCompiler_pfMessageCallback = nullptr;
  ScriptCompiler_pfWarningCallback = nullptr;
  ScriptCompiler_pxErrorContext = nullptr;
  ScriptCompiler_pxWarningContext = nullptr;
  ScriptCompiler_pxMessageContext = nullptr;
  QVMAsm_pfErrorCallback = nullptr;
  QVMAsm_pfWarningCallback = nullptr;
  QVMAsm_pfMessageCallback = nullptr;
  QVMAsm_pxErrorContext = nullptr;
  QVMAsm_pxWarningContext = nullptr;
  QVMAsm_pxMessageContext = nullptr;
  QVMOpCode_LinkAsmHandlers();
  QVMOpCode_LinkDisAsmHandlers();
}

// source: c/0/script.c:1642  [size]
// attributes: thunk
void __cdecl Script_Close()
{
  Symbol_Close();
}
