/* h/1/parameterlist.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/1/parameterlist.c:116  [anchor-hash]
int __cdecl ParameterList_GetParameterTypeByName(char *zName)
{
  int v1; // ebp
  struct ParameterType_s *v2; // edi

  v1 = 0;
  v2 = ParameterList_atParameterType;
  while ( v2->isUsed == false || strcmp(v2->zName, zName) )
  {
    ++v2;
    ++v1;
    if ( (int)v2 >= 128883744 )
      return -1;
  }
  return v1;
}

// source: h/1/parameterlist.c:142  [size]
void __cdecl ParameterList_Delete(struct ParameterList_s *ptParameterList)
{
  int v1; // esi

  if ( ptParameterList )
  {
    v1 = *(_DWORD *)((unsigned int)&ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
}

// source: h/1/parameterlist.c:178  [anchor-callee]
struct ParameterList_s *__cdecl ParameterList_Derive(
        struct ParameterList_s *ptBaseParameterList,
        int nMaxParameters)
{
  int v2; // esi
  struct ParameterList_s *result; // eax

  v2 = nMaxParameters + ptBaseParameterList->nParameters;
  result = (struct ParameterList_s *)Mem_AllocFn(20 * v2 + 12, 4);
  result->nParameters = 0;
  result->nMaxParameters = v2;
  result->ptParameterListItem = (struct ParameterListItem_s *)&result[1];
  qmemcpy(&result[1], ptBaseParameterList->ptParameterListItem, 20 * ptBaseParameterList->nParameters);
  result->nParameters = ptBaseParameterList->nParameters;
  return result;
}

// source: h/1/parameterlist.c:204  [anchor-strings]
int __cdecl ParameterList_NewParameterType(char *zName, int eParentParameterType)
{
  int result; // eax
  enum bool *p_isUsed; // ecx
  int v4; // ecx

  result = 0;
  p_isUsed = &ParameterList_atParameterType[0].isUsed;
  while ( *p_isUsed )
  {
    p_isUsed += 19;
    ++result;
    if ( (int)p_isUsed >= 128883816 )
    {
      LDebug_Error("Unable to allocate parameter type");
      abort();
    }
  }
  if ( eParentParameterType != -1 )
    qmemcpy((void *)(76 * result + 128878880), (void *)(76 * eParentParameterType + 128878880), 0x4Cu);
  v4 = result;
  ParameterList_atParameterType[v4].zName = zName;
  ParameterList_atParameterType[v4].isUsed = true;
  ParameterList_atParameterType[v4].eParentParameterType = eParentParameterType;
  return result;
}

// source: h/1/parameterlist.c:248  [size]
int __cdecl ParameterList_DeleteParameterType(int eParameterType)
{
  int result; // eax

  result = eParameterType;
  ParameterList_atParameterType[result].isUsed = false;
  return result * 76;
}

// source: h/1/parameterlist.c:264  [size]
int __cdecl ParameterList_GetParentParameterType(int eParameterType)
{
  return ParameterList_atParameterType[eParameterType].eParentParameterType;
}

// source: h/1/parameterlist.c:349  [size]
__int16 __cdecl ParameterList_GetGetParameterListQTaskEvent()
{
  return ParameterList_eGetParameterListQTaskEvent;
}

// source: h/1/parameterlist.c:364  [size]
__int16 __cdecl ParameterList_GetUpdateInternalDataQTaskEvent()
{
  return ParameterList_eUpdateInternalDataQTaskEvent;
}

// source: h/1/parameterlist.c:388  [anchor-callee]
void __cdecl ParameterList_AddParameterMinMax(
        struct ParameterList_s *ptParameterList,
        unsigned int nParameterOffset,
        int eParameterType,
        char *zName,
        unsigned __int8 bParameterProperties,
        double vMin,
        double vMax)
{
  double *v7; // eax
  void *v8; // esi

  v7 = (double *)Mem_AllocFn(24, 4);
  v8 = v7 + 1;
  v7[1] = vMin;
  *((_DWORD *)v7 + 4) = LODWORD(vMax);
  *((_DWORD *)v7 + 1) = 0;
  *(_DWORD *)v7 = 0;
  *((_DWORD *)v7 + 5) = HIDWORD(vMax);
  List_AddTail(v7, (int)&ParameterList_tParameterScalarContextList);
  ParameterList_AddParameter(ptParameterList, nParameterOffset, eParameterType, zName, bParameterProperties, v8);
}

// source: h/1/parameterlist.c:418  [anchor-caller]
void __cdecl ParameterList_AddParameterArrayMinMax(
        struct ParameterList_s *ptParameterList,
        unsigned int nParameterOffset,
        int eParameterType,
        char *zName,
        unsigned __int8 bParameterProperties,
        double vMin,
        double vMax,
        unsigned int nElementSize,
        unsigned int nArraySize)
{
  char *v9; // eax
  void *v10; // esi

  v9 = (char *)Mem_AllocFn(24, 4);
  v10 = v9 + 8;
  *((_DWORD *)v9 + 2) = HIDWORD(vMin);
  *(double *)(v9 + 12) = vMax;
  *((_DWORD *)v9 + 1) = 0;
  *(_DWORD *)v9 = 0;
  *((_DWORD *)v9 + 5) = nElementSize;
  List_AddTail(v9, (int)&ParameterList_tParameterScalarContextList);
  ParameterList_AddParameterArray(
    ptParameterList,
    nParameterOffset,
    eParameterType,
    zName,
    bParameterProperties,
    v10,
    LODWORD(vMin),
    nArraySize);
}

// source: h/1/parameterlist.c:445  [anchor-strings]
struct ParameterList_s *__cdecl ParameterList_AddParameter(
        struct ParameterList_s *ptParameterList,
        unsigned int nOffset,
        int eParameterType,
        char *zName,
        unsigned __int8 bParameterProperties,
        void *pxContext)
{
  if ( ptParameterList->nParameters >= ptParameterList->nMaxParameters )
  {
    LDebug_Error("Too many parameters");
    goto LABEL_3;
  }
  if ( eParameterType == -1 )
  {
    LDebug_Error("Undefined parameter type '%s'.", zName);
LABEL_3:
    abort();
  }
  ptParameterList->ptParameterListItem[ptParameterList->nParameters].nOffset = nOffset;
  ptParameterList->ptParameterListItem[ptParameterList->nParameters].eParameterType = eParameterType;
  ptParameterList->ptParameterListItem[ptParameterList->nParameters].zName = zName;
  ptParameterList->ptParameterListItem[ptParameterList->nParameters].pxContext = pxContext;
  ptParameterList->ptParameterListItem[ptParameterList->nParameters++].bParameterProperties = bParameterProperties;
  return ptParameterList;
}

// source: h/1/parameterlist.c:488  [anchor-mhash]
int __cdecl ParameterList_TriggerParameterEvent(
        void *pxData,
        int eParameterType,
        char eQParameterEvent,
        void *pxContext)
{
  return ((int (__cdecl *)(void *))ParameterList_atParameterType[eParameterType].apfQParameterEvent[eQParameterEvent])(pxData);
}

// source: h/1/parameterlist.c:510  [anchor-hash]
enum bool __cdecl ParameterList_ParameterEventHandlerExists(
        int eParameterType,
        char eQParameterEvent)
{
  return ParameterList_atParameterType[eParameterType].apfQParameterEvent[eQParameterEvent] != nullptr;
}

// source: h/1/parameterlist.c:549  [anchor-hash]
int ParameterList_NewParameterEvent()
{
  int result; // eax

  result = 0;
  while ( ParameterList_atParameterEvent[result].isUsed )
  {
    if ( ++result >= 16 )
    {
      LDebug_Error("Unable to allocate parameter event");
      abort();
    }
  }
  ParameterList_atParameterEvent[result].isUsed = true;
  return result;
}

// source: h/1/parameterlist.c:579  [anchor-hash]
void __cdecl ParameterList_DeleteParameterEvent(char eQParameterEvent)
{
  ParameterList_atParameterEvent[eQParameterEvent].isUsed = false;
}

// source: h/1/parameterlist.c:596  [size]
char __cdecl ParameterList_GetParseParameterEvent()
{
  return ParameterList_eQParameterParseEvent;
}

// source: h/1/parameterlist.c:611  [size]
char __cdecl ParameterList_GetNumberOfArgumentsParameterEvent()
{
  return ParameterList_eQParameterGetNumberOfArgumentsEvent;
}

// source: h/1/parameterlist.c:626  [size]
char __cdecl ParameterList_GetPrintParameterEvent()
{
  return ParameterList_eQParameterPrintEvent;
}

// source: h/1/parameterlist.c:641  [size]
char __cdecl ParameterList_GetGetSizeParameterEvent()
{
  return ParameterList_eQParameterGetSizeEvent;
}

// source: h/1/parameterlist.c:656  [size]
char __cdecl ParameterList_GetCopyParameterEvent()
{
  return ParameterList_eQParameterCopyEvent;
}

// source: h/1/parameterlist.c:671  [size]
char __cdecl ParameterList_GetPasteParameterEvent()
{
  return ParameterList_eQParameterPasteEvent;
}

// source: h/1/parameterlist.c:689  [anchor-callee]
void __cdecl ParameterList_LinkParameterEventHandler(
        int eParameterType,
        char eQParameterEvent,
        void (__cdecl *pfQParameterEvent)(void *, void *))
{
  int v3; // edi
  int *p_eParentParameterType; // esi

  ParameterList_atParameterType[eParameterType].apfQParameterEvent[eQParameterEvent] = pfQParameterEvent;
  v3 = 0;
  p_eParentParameterType = &ParameterList_atParameterType[0].eParentParameterType;
  do
  {
    if ( p_eParentParameterType[17] )
    {
      if ( *p_eParentParameterType == eParameterType )
        ParameterList_LinkParameterEventHandler(v3, eQParameterEvent, pfQParameterEvent);
    }
    p_eParentParameterType += 19;
    ++v3;
  }
  while ( (int)p_eParentParameterType < 128883748 );
}

// source: h/1/parameterlist.c:725  [anchor-mhash]
void __cdecl ParameterList_ValidateParameters(
        struct ParameterParseContext_s *ptParameterParseContext,
        int nArguments)
{
  int i; // eax

  for ( i = 0; i < nArguments; ++i )
  {
    if ( i + ptParameterParseContext->iArg >= ptParameterParseContext->ptArgumentList->nArguments )
    {
      LDebug_Error(
        "Too few parameters in line %d of file '%s'",
        ptParameterParseContext->nLinenumber,
        ptParameterParseContext->zScriptfile);
      abort();
    }
  }
}

// source: h/1/parameterlist.c:750  [size]
struct ParameterScalarContext_s *__cdecl ParameterList_Int32ZeroOrMoreContext()
{
  return (struct ParameterScalarContext_s *)&unk_6B09C8;
}

// source: h/1/parameterlist.c:766  [size]
struct ParameterScalarContext_s *__cdecl ParameterList_Real32ZeroToOneContext()
{
  return (struct ParameterScalarContext_s *)&unk_6B09D8;
}

// source: h/1/parameterlist.c:782  [size]
struct ParameterScalarContext_s *__cdecl ParameterList_Real32ZeroToTwoContext()
{
  return (struct ParameterScalarContext_s *)&unk_6B09E8;
}

// source: h/1/parameterlist.c:798  [size]
struct ParameterScalarContext_s *__cdecl ParameterList_Real32ZeroToOneHundredContext()
{
  return (struct ParameterScalarContext_s *)&unk_6B09F8;
}

// source: h/1/parameterlist.c:814  [anchor-mhash]
enum bool __cdecl ParameterList_IsParameterTypeDerived(
        int eParameterType,
        int eParentParameterType)
{
  while ( eParameterType != eParentParameterType )
  {
    eParameterType = ParameterList_atParameterType[eParameterType].eParentParameterType;
    if ( eParameterType == -1 )
      return false;
  }
  return true;
}

// source: h/1/parameterlist.c:839  [anchor-mhash]
enum bool __cdecl ParameterList_IsParameterTypeFamily(
        int eParameterType1,
        int eParameterType2)
{
  int eParentParameterType; // eax

  while ( 2 )
  {
    eParentParameterType = eParameterType2;
    do
    {
      if ( eParentParameterType == eParameterType1 )
        return true;
      eParentParameterType = ParameterList_atParameterType[eParentParameterType].eParentParameterType;
    }
    while ( eParentParameterType != -1 );
    eParameterType1 = ParameterList_atParameterType[eParameterType1].eParentParameterType;
    if ( eParameterType1 != -1 )
      continue;
    break;
  }
  return false;
}

// source: h/1/parameterlist.c:862  [anchor-hash]
struct ParameterType_s *__cdecl ParameterList_GetParameterType(int eParameterType)
{
  return (struct ParameterType_s *)(76 * eParameterType + 128878880);
}

// source: h/1/parameterlist.c:887  [anchor-hash]
struct ParameterList_s *__cdecl ParameterList_New(int nMaxParameters)
{
  struct ParameterList_s *result; // eax

  result = (struct ParameterList_s *)Mem_AllocFn(20 * nMaxParameters + 12, 4);
  result->nParameters = 0;
  result->nMaxParameters = nMaxParameters;
  result->ptParameterListItem = (struct ParameterListItem_s *)&result[1];
  return result;
}

// source: h/1/parameterlist.c:932  [anchor-mhash]
struct ParameterList_s *__cdecl ParameterList_DeriveFromQTaskType(
        unsigned __int16 eQTaskType,
        int nMaxParameters)
{
  struct GetParameterListContext_t tGetParameterListContext; // [esp+4h] [ebp-4h] BYREF

  tGetParameterListContext.ptParameterList = nullptr;
  ((void (__cdecl *)(_DWORD, struct GetParameterListContext_t *))QTask_aatQTaskFinalEvent[ParameterList_eGetParameterListQTaskEvent][eQTaskType].pfHandler)(
    0,
    &tGetParameterListContext);
  return ParameterList_Derive(tGetParameterListContext.ptParameterList, nMaxParameters);
}

// source: h/1/parameterlist.c:953  [anchor-callee]
void __cdecl ParameterList_AddParameterArray(
        struct ParameterList_s *ptParameterList,
        unsigned int nParameterOffset,
        int eParameterType,
        char *zName,
        unsigned __int8 bParameterProperties,
        void *pxContext,
        unsigned int nElementSize,
        unsigned int nArraySize)
{
  unsigned int i; // edi
  char *v9; // eax
  struct ParameterNameNode_s *v10; // ecx
  char zTemp[256]; // [esp+8h] [ebp-100h] BYREF

  for ( i = 0; i < nArraySize; ++i )
  {
    if ( i )
      sprintf(zTemp, "%s%d", zName, i);
    else
      sprintf(zTemp, (char *const)&stru_6A4CDC.tDebugConsoleLineList.ptMiddle, zName);
    v9 = (char *)Mem_AllocFn(strlen(zTemp) + 9, 4);
    v10 = ParameterList_ptNameNodeList;
    *((_DWORD *)v9 + 1) = v9 + 8;
    *(_DWORD *)v9 = v10;
    ParameterList_ptNameNodeList = (struct ParameterNameNode_s *)v9;
    strcpy(v9 + 8, zTemp);
    ParameterList_AddParameter(
      ptParameterList,
      nParameterOffset + nElementSize * i,
      eParameterType,
      *((char **)v9 + 1),
      bParameterProperties,
      pxContext);
  }
}

// source: h/1/parameterlist.c:991  [anchor-hash]
int ParameterList_Open()
{
  int v0; // eax
  int v1; // eax
  int v2; // eax
  int v3; // eax
  int v4; // eax
  int result; // eax

  memset(ParameterList_atParameterEvent, 0, sizeof(ParameterList_atParameterEvent));
  memset(ParameterList_atParameterType, 0, sizeof(ParameterList_atParameterType));
  ParameterList_eGetParameterListQTaskEvent = QTask_NewQTaskEventFn(0, "GetParameterList");
  ParameterList_eUpdateInternalDataQTaskEvent = QTask_NewQTaskEventFn(0, "UpdateInternalData");
  ParameterList_tParameterScalarContextList.ptHead = (struct ParameterScalarContextNode_s *)&ParameterList_tParameterScalarContextList.ptMiddle;
  ParameterList_tParameterScalarContextList.ptTail = (struct ParameterScalarContextNode_s *)&ParameterList_tParameterScalarContextList;
  ParameterList_tParameterScalarContextList.ptMiddle = nullptr;
  v0 = 0;
  while ( ParameterList_atParameterEvent[v0].isUsed )
  {
    if ( ++v0 >= 16 )
    {
LABEL_4:
      LDebug_Error("Unable to allocate parameter event");
      abort();
    }
  }
  ParameterList_atParameterEvent[v0].isUsed = true;
  ParameterList_eQParameterPrintEvent = v0;
  v1 = 0;
  while ( ParameterList_atParameterEvent[v1].isUsed )
  {
    if ( ++v1 >= 16 )
      goto LABEL_4;
  }
  ParameterList_atParameterEvent[v1].isUsed = true;
  ParameterList_eQParameterParseEvent = v1;
  v2 = 0;
  while ( ParameterList_atParameterEvent[v2].isUsed )
  {
    if ( ++v2 >= 16 )
      goto LABEL_4;
  }
  ParameterList_atParameterEvent[v2].isUsed = true;
  ParameterList_eQParameterCopyEvent = v2;
  v3 = 0;
  while ( ParameterList_atParameterEvent[v3].isUsed )
  {
    if ( ++v3 >= 16 )
      goto LABEL_4;
  }
  ParameterList_atParameterEvent[v3].isUsed = true;
  ParameterList_eQParameterPasteEvent = v3;
  v4 = 0;
  while ( ParameterList_atParameterEvent[v4].isUsed )
  {
    if ( ++v4 >= 16 )
      goto LABEL_4;
  }
  ParameterList_atParameterEvent[v4].isUsed = true;
  ParameterList_eQParameterGetSizeEvent = v4;
  result = 0;
  while ( ParameterList_atParameterEvent[result].isUsed )
  {
    if ( ++result >= 16 )
      goto LABEL_4;
  }
  ParameterList_atParameterEvent[result].isUsed = true;
  ParameterList_eQParameterGetNumberOfArgumentsEvent = result;
  return result;
}

// source: h/1/parameterlist.c:1026  [anchor-hash]
void __cdecl ParameterList_Close()
{
  struct ParameterScalarContextNode_s *ptHead; // eax
  struct ParameterScalarContextNode_s *i; // ebx
  _DWORD **v2; // eax
  int v3; // esi
  struct ParameterNameNode_s *v4; // eax
  struct ParameterNameNode_s *ptNext; // ebx
  int v6; // esi
  int v7; // ecx
  int v8; // edx
  int v9; // eax
  int v10; // ecx
  int v11; // edx

  ptHead = ParameterList_tParameterScalarContextList.ptHead;
  for ( i = ParameterList_tParameterScalarContextList.ptHead->ptNext; i; i = i->ptNext )
  {
    v2 = Node_Remove(ptHead);
    if ( v2 )
    {
      v3 = *(_DWORD *)((unsigned int)(v2 - 1) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v3);
      memset(*(void **)(v3 + 8), 0xCDu, *(_DWORD *)(v3 + 16));
      free((void *)v3);
    }
    ptHead = i;
  }
  v4 = ParameterList_ptNameNodeList;
  if ( ParameterList_ptNameNodeList )
  {
    do
    {
      ptNext = v4->ptNext;
      v6 = *(_DWORD *)((unsigned int)&v4[-1].pzName & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v6);
      memset(*(void **)(v6 + 8), 0xCDu, *(_DWORD *)(v6 + 16));
      free((void *)v6);
      v4 = ptNext;
    }
    while ( ptNext );
  }
  v7 = ParameterList_eQParameterParseEvent;
  v8 = ParameterList_eQParameterCopyEvent;
  ParameterList_atParameterEvent[ParameterList_eQParameterPrintEvent].isUsed = false;
  v9 = ParameterList_eQParameterPasteEvent;
  ParameterList_atParameterEvent[v7].isUsed = false;
  v10 = ParameterList_eQParameterGetSizeEvent;
  ParameterList_atParameterEvent[v8].isUsed = false;
  v11 = ParameterList_eQParameterGetNumberOfArgumentsEvent;
  ParameterList_atParameterEvent[v9].isUsed = false;
  ParameterList_eQParameterPrintEvent = -1;
  ParameterList_eQParameterParseEvent = -1;
  ParameterList_eQParameterCopyEvent = -1;
  ParameterList_eQParameterPasteEvent = -1;
  ParameterList_eQParameterGetSizeEvent = -1;
  ParameterList_eQParameterGetNumberOfArgumentsEvent = -1;
  LOWORD(v9) = ParameterList_eGetParameterListQTaskEvent;
  ParameterList_atParameterEvent[v10].isUsed = false;
  ParameterList_ptNameNodeList = nullptr;
  ParameterList_atParameterEvent[v11].isUsed = false;
  QTask_DeleteQTaskEvent(v9);
  QTask_DeleteQTaskEvent(ParameterList_eUpdateInternalDataQTaskEvent);
  ParameterList_eGetParameterListQTaskEvent = 512;
  ParameterList_eUpdateInternalDataQTaskEvent = 512;
}
