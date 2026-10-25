/* h/1/serialize.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/1/serialize.c:50  [anchor-strings]
struct QTask_s *__cdecl Serialize_GetTaskFromArgList(struct ArgList_s *ptArgList, int *piArg)
{
  int *v2; // ebp
  int isQVM; // ecx
  int v5; // eax
  int *v6; // esi
  int v7; // eax
  unsigned __int16 QTaskType; // cx
  struct QReference_s *v9; // eax
  struct QTask_s *result; // eax
  char zTaskType[32]; // [esp+Ch] [ebp-20h] BYREF

  v2 = piArg;
  isQVM = ptArgList->isQVM;
  v5 = *piArg;
  if ( isQVM )
  {
    piArg = nullptr;
    QVM_EvalArg(&piArg, 4, ptArgList, v5, 1);
    v6 = piArg;
  }
  else
  {
    v6 = (int *)Expression_EvalInt(ptArgList->aptExpression[v5]);
  }
  v7 = *v2 + 1;
  if ( ptArgList->isQVM )
  {
    zTaskType[0] = 0;
    QVM_EvalArg(zTaskType, 32, ptArgList, v7, 3);
  }
  else
  {
    Expression_EvalString(ptArgList->aptExpression[v7], zTaskType, 32);
  }
  QTaskType = QTask_GetQTaskType(zTaskType);
  if ( (unsigned int)v6 < 0x1000 && (v9 = Level_atLevelQTaskID[(_DWORD)v6]) != nullptr )
    result = (struct QTask_s *)v9->pxObject;
  else
    result = nullptr;
  *v2 += 2;
  if ( !result || result->eQTaskType != QTaskType )
  {
    DebugConsole_printf(
      "Failed to de-serialize task (or child of task) id %d (%s), task does not exist or has changed.\n",
      v6,
      zTaskType);
    return nullptr;
  }
  return result;
}

// source: h/1/serialize.c:91  [anchor-caller]
struct QTask_s *__cdecl Serialize_GetChildTaskFromArgList(
        struct ArgList_s *ptArgList,
        struct QTask_s *ptParent,
        int nLevels,
        int *piArg)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct GetSerializeInfoContext_s tGetSerializeInfoContext; };
    struct { char igi2_o1[8]; char zTaskType[32]; };
    char igi2_extent[40];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v4; // eax
  unsigned __int16 QTaskType; // si
  int v6; // eax
  int v7; // edi
  struct QTask_s *FirstChildOfType; // eax
  void (__cdecl *pfHandler)(_DWORD, struct GetSerializeInfoContext_s *); // eax
  enum bool isRecreateIfNotFound; // ecx
  struct QTask_s *v11; // esi
  int v12; // eax
  int v13; // eax
  int v14; // edi
  void (__cdecl *v15)(struct QTask_s *, _DWORD); // eax
  void (__cdecl *v16)(struct QTask_s *); // eax
  void (__cdecl *v17)(struct QTask_s *); // eax

  if ( !nLevels )
  {
    ++*piArg;
    return ptParent;
  }
  v4 = (*piArg)++;
  if ( ptArgList->isQVM )
  {
    igi2_frame.zTaskType[0] = 0;
    QVM_EvalArg(igi2_frame.zTaskType, 32, ptArgList, v4, 3);
  }
  else
  {
    Expression_EvalString(ptArgList->aptExpression[v4], igi2_frame.zTaskType, 32);
  }
  QTaskType = QTask_GetQTaskType(igi2_frame.zTaskType);
  v6 = (*piArg)++;
  v7 = Script_EvalArgInt(ptArgList, v6);
  if ( QTaskType == 512 )
    goto LABEL_24;
  FirstChildOfType = QTask_GetFirstChildOfType(ptParent, QTaskType);
  if ( !FirstChildOfType )
  {
LABEL_9:
    if ( nLevels == 1 )
    {
      pfHandler = (void (__cdecl *)(_DWORD, struct GetSerializeInfoContext_s *))QTask_aatQTaskFinalEvent[Serialize_eGetSerializeInfoQTaskEvent][QTaskType].pfHandler;
      isRecreateIfNotFound = false;
      igi2_frame.tGetSerializeInfoContext.tReturn.isRecreateIfNotFound = false;
      igi2_frame.tGetSerializeInfoContext.tReturn.isUseParentToSerialize = false;
      if ( pfHandler )
      {
        pfHandler(0, &igi2_frame.tGetSerializeInfoContext);
        isRecreateIfNotFound = igi2_frame.tGetSerializeInfoContext.tReturn.isRecreateIfNotFound;
      }
      if ( isRecreateIfNotFound )
      {
        v11 = QTask_NewFn(ptParent, QTaskType, nullptr);
        v12 = (*piArg)++;
        v13 = Script_EvalArgInt(ptArgList, v12);
        v14 = v13;
        if ( v13 >= 0 && !Level_GetQTaskFromLevelQTaskID(v13) )
          Level_DefineQTaskID(v14, v11);
        v15 = (void (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][v11->eQTaskType].pfHandler;
        if ( v15 )
          v15(v11, 0);
        v16 = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Level_eUpdateInternalDataAfterLoadEvent][v11->eQTaskType].pfHandler;
        if ( v16 )
          v16(v11);
        v17 = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Level_eRegisterLevelScriptSymbolsEvent][v11->eQTaskType].pfHandler;
        if ( v17 )
          v17(v11);
        return v11;
      }
    }
LABEL_24:
    ++*piArg;
    return nullptr;
  }
  while ( v7 )
  {
    FirstChildOfType = QTask_GetNextSiblingOfType(FirstChildOfType, QTaskType);
    --v7;
    if ( !FirstChildOfType )
      goto LABEL_9;
  }
  return Serialize_GetChildTaskFromArgList(ptArgList, FirstChildOfType, nLevels - 1, piArg);
}

// source: h/1/serialize.c:184  [anchor-mhash]
struct Result_s *__cdecl Serialize_DeSerializeScriptFunction(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct ArgList_s *v9; };
    struct { char igi2_o1[4]; int piArg; };
    struct { char igi2_o2[8]; struct Result_s Rs; };
    char igi2_extent[32];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *TaskFromArgList; // edi
  int v4; // eax
  int v5; // eax
  struct QTask_s *ChildTaskFromArgList; // eax
  void (__cdecl *pfHandler)(struct QTask_s *, struct ArgList_s **); // ecx

  igi2_frame.v9 = ptArgList;
  igi2_frame.piArg = 0;
  TaskFromArgList = Serialize_GetTaskFromArgList(ptArgList, &igi2_frame.piArg);
  if ( TaskFromArgList )
  {
    v4 = igi2_frame.piArg++;
    v5 = Script_EvalArgInt(ptArgList, v4);
    ChildTaskFromArgList = Serialize_GetChildTaskFromArgList(ptArgList, TaskFromArgList, v5, &igi2_frame.piArg);
    if ( ChildTaskFromArgList )
    {
      pfHandler = (void (__cdecl *)(struct QTask_s *, struct ArgList_s **))QTask_aatQTaskFinalEvent[Serialize_eDeSerializeQTaskEvent][ChildTaskFromArgList->eQTaskType].pfHandler;
      if ( pfHandler )
        pfHandler(ChildTaskFromArgList, &igi2_frame.v9);
    }
  }
  igi2_frame.Rs.nResult = 0;
  igi2_frame.Rs.vResult = 0.0;
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: h/1/serialize.c:216  [anchor-mhash]
void __cdecl Serialize_SerializeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  void *v2; // ebx
  struct QTask_s *v3; // edi
  struct QTask_s *ptHead; // eax
  int v5; // edx
  struct QTask_s *v6; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // ecx
  int v8; // edx
  void (__cdecl *v9)(struct QTask_s *, struct QTask_s **); // eax
  enum bool isUseParentToSerialize; // edx
  void (__cdecl *v11)(_DWORD, struct GetSerializeInfoContext_s *); // eax
  int v12; // ecx
  struct QReference_s *v13; // eax
  struct QTask_s *i; // edx
  int v15; // eax
  struct QReference_s *v16; // ecx
  struct GetSerializeInfoContext_s tGetSerializeInfoContext; // [esp+Ch] [ebp-8h] BYREF

  v2 = pxContext;
  v3 = ptQTask;
  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v5 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v6 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v6 = nullptr;
      QTask_atProtectedQTaskStack[v5].ptQTask = v6;
      pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[Serialize_eSerializeQTaskEvent][ptHead->eQTaskType].pfHandler;
      v8 = v5 + 1;
      QTask_nProtectedQTaskStackOffset = v8;
      if ( pfHandler )
      {
        pfHandler(ptHead, v2);
        v8 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v8];
      v5 = v8 - 1;
      QTask_nProtectedQTaskStackOffset = v5;
    }
    while ( ptHead );
  }
  v9 = (void (__cdecl *)(struct QTask_s *, struct QTask_s **))QTask_aatQTaskFinalEvent[Serialize_eGetSerializeParameterListQTaskEvent][v3->eQTaskType].pfHandler;
  ptQTask = nullptr;
  if ( v9 )
  {
    v9(v3, &ptQTask);
    if ( ptQTask )
    {
      isUseParentToSerialize = false;
      tGetSerializeInfoContext.tReturn.isRecreateIfNotFound = false;
      v11 = (void (__cdecl *)(_DWORD, struct GetSerializeInfoContext_s *))QTask_aatQTaskFinalEvent[Serialize_eGetSerializeInfoQTaskEvent][v3->eQTaskType].pfHandler;
      tGetSerializeInfoContext.tReturn.isUseParentToSerialize = false;
      if ( v11 )
      {
        v11(0, &tGetSerializeInfoContext);
        isUseParentToSerialize = tGetSerializeInfoContext.tReturn.isUseParentToSerialize;
      }
      v12 = 0;
      while ( 1 )
      {
        v13 = Level_atLevelQTaskID[v12];
        if ( v13 )
        {
          if ( v13->pxObject == v3 )
            break;
        }
        if ( ++v12 >= 4096 )
          goto LABEL_18;
      }
      if ( v12 >= 0 && isUseParentToSerialize == false )
      {
        i = v3;
LABEL_30:
        if ( i )
          Serialize_SerializeChild(i, v3, v2);
        return;
      }
LABEL_18:
      if ( Serialize_aisSaveWithParent[v3->eQTaskType] || Serialize_isForceSerializeChildren || isUseParentToSerialize )
      {
        for ( i = v3->ptParent; i; i = i->ptParent )
        {
          v15 = 0;
          while ( 1 )
          {
            v16 = Level_atLevelQTaskID[v15];
            if ( v16 )
            {
              if ( v16->pxObject == i )
                break;
            }
            if ( ++v15 >= 4096 )
              goto LABEL_34;
          }
          if ( v15 >= 0 )
            goto LABEL_30;
LABEL_34:
          ;
        }
      }
    }
  }
}

// source: h/1/serialize.c:278  [anchor-callee]
void __cdecl Serialize_DeSerializeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  void (__cdecl *pfHandler)(struct QTask_s *, struct GetSerializeParameterListContext_s *); // eax
  struct GetSerializeParameterListContext_s tGetSerializeParameterListContext; // [esp+4h] [ebp-4h] BYREF

  pfHandler = (void (__cdecl *)(struct QTask_s *, struct GetSerializeParameterListContext_s *))QTask_aatQTaskFinalEvent[Serialize_eGetSerializeParameterListQTaskEvent][ptQTask->eQTaskType].pfHandler;
  tGetSerializeParameterListContext.tReturn.ptParameterList = nullptr;
  if ( pfHandler )
  {
    pfHandler(ptQTask, &tGetSerializeParameterListContext);
    if ( tGetSerializeParameterListContext.tReturn.ptParameterList )
      Serialize_ParseParameterList(
        ptQTask,
        (struct DeSerializeContext_s *)pxContext,
        tGetSerializeParameterListContext.tReturn.ptParameterList);
  }
}

// source: h/1/serialize.c:308  [anchor-caller]
struct QTask_s *__cdecl Serialize_Begin(
        struct QTask_s *ptQTask,
        struct SerializeContext_s *ptSerializeContext)
{
  struct QTask_s *result; // eax

  Serialize_BeginChild(ptQTask, ptQTask, ptSerializeContext);
  return result;
}

// source: h/1/serialize.c:323  [anchor-callee]
void __cdecl Serialize_BeginChild(
        struct QTask_s *ptParent,
        struct QTask_s *ptQTask,
        struct SerializeContext_s *ptSerializeContext)
{
  sprintf(
    ptSerializeContext->pzParameterBuffer,
    &g_zFileName.atPictureResources[20].zResourceFilename[60],
    "DefineTaskState");
  Serialize_PrintQTaskHierarchy(
    &ptSerializeContext->pzParameterBuffer[strlen(ptSerializeContext->pzParameterBuffer)],
    ptSerializeContext->nParameterBufferSize - strlen(ptSerializeContext->pzParameterBuffer),
    ptParent,
    ptQTask);
}

// source: h/1/serialize.c:345  [anchor-callee]
void __cdecl Serialize_WriteParameterList(
        void *pxParameterChunk,
        struct SerializeContext_s *ptSerializeContext,
        struct ParameterList_s *ptParameterList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v10; };
    struct { char igi2_o1[4]; struct ParameterPrintContext_s tParameterPrintContext; };
    char igi2_extent[24];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct SerializeContext_s *v3; // ecx
  char *v4; // esi
  int v5; // ebp
  unsigned int v6; // eax
  char *pzParameterBuffer; // edx
  unsigned int nParameterBufferSize; // eax
  struct ParameterListItem_s *ptParameterListItem; // ecx

  v3 = ptSerializeContext;
  v4 = &ptSerializeContext->pzParameterBuffer[strlen(ptSerializeContext->pzParameterBuffer)];
  v5 = 0;
  if ( ptParameterList->nParameters > 0 )
  {
    igi2_frame.v10 = 0;
    while ( 1 )
    {
      strcat(v4, ", ");
      v6 = (unsigned int)&v4[strlen(v4) + 1];
      pzParameterBuffer = v3->pzParameterBuffer;
      v4 = (char *)(v6 - 1);
      nParameterBufferSize = v3->nParameterBufferSize;
      ptParameterListItem = ptParameterList->ptParameterListItem;
      igi2_frame.tParameterPrintContext.nBufferSize = (unsigned int)&pzParameterBuffer[nParameterBufferSize - (_DWORD)v4];
      igi2_frame.tParameterPrintContext.ptParameterListItem = &ptParameterListItem[igi2_frame.v10];
      igi2_frame.tParameterPrintContext.isQuoteStrings = true;
      igi2_frame.tParameterPrintContext.tReturn.isBufferOverflow = false;
      igi2_frame.tParameterPrintContext.zBuffer = v4;
      ParameterList_atParameterType[ptParameterListItem[igi2_frame.v10].eParameterType].apfQParameterEvent[ParameterList_eQParameterPrintEvent](
        (char *)pxParameterChunk + ptParameterListItem[igi2_frame.v10].nOffset,
        &igi2_frame.tParameterPrintContext);
      ++v5;
      ++igi2_frame.v10;
      if ( v5 >= ptParameterList->nParameters )
        break;
      v3 = ptSerializeContext;
    }
  }
}

// source: h/1/serialize.c:384  [anchor-hash]
void __cdecl Serialize_End(struct QTask_s *ptQTask, struct SerializeContext_s *ptSerializeContext)
{
  *(_DWORD *)&ptSerializeContext->pzParameterBuffer[strlen(ptSerializeContext->pzParameterBuffer)] = 670505;
  File_atDevice[ptSerializeContext->ptFile->eDeviceID].pfWrite(
    ptSerializeContext->ptFile->eDeviceID,
    ptSerializeContext->ptFile,
    ptSerializeContext->pzParameterBuffer,
    strlen(ptSerializeContext->pzParameterBuffer));
  *ptSerializeContext->pzParameterBuffer = 0;
}

// source: h/1/serialize.c:407  [anchor-strings]
void __cdecl Serialize_ParseParameterList(
        void *pxParameterChunk,
        struct DeSerializeContext_s *ptDeSerializeContext,
        struct ParameterList_s *ptParameterList)
{
  int iArgOffset; // ecx
  int v4; // ebx
  int v5; // esi
  bool v6; // cc
  struct ParameterParseContext_s tParameterParseContext; // [esp+Ch] [ebp-14h] BYREF

  iArgOffset = ptDeSerializeContext->tReturn.iArgOffset;
  v4 = 0;
  tParameterParseContext.ptArgumentList = ptDeSerializeContext->ptArgList;
  v5 = 0;
  v6 = ptParameterList->nParameters <= 0;
  tParameterParseContext.iArg = iArgOffset;
  tParameterParseContext.nLinenumber = 0;
  tParameterParseContext.zScriptfile = "[N/A]";
  if ( v6 )
  {
    ptDeSerializeContext->tReturn.iArgOffset = iArgOffset;
  }
  else
  {
    do
    {
      tParameterParseContext.ptParameterListItem = &ptParameterList->ptParameterListItem[v4];
      ParameterList_atParameterType[tParameterParseContext.ptParameterListItem->eParameterType].apfQParameterEvent[ParameterList_eQParameterParseEvent](
        (char *)pxParameterChunk + tParameterParseContext.ptParameterListItem->nOffset,
        &tParameterParseContext);
      ++v5;
      ++v4;
    }
    while ( v5 < ptParameterList->nParameters );
    ptDeSerializeContext->tReturn.iArgOffset = tParameterParseContext.iArg;
  }
}

// source: h/1/serialize.c:440  [anchor-callee]
void __cdecl Serialize_SerializeToFile(struct File_s *ptScriptFile, struct QTask_s *ptQTask)
{
  char *v3; // esi
  int v4; // eax
  void (__cdecl *pfHandler)(struct QTask_s *, struct SerializeContext_s *); // eax
  int v6; // esi
  struct SerializeContext_s tSerializeContext; // [esp+Ch] [ebp-Ch] BYREF

  v3 = (char *)Mem_AllocFn(0x4000, 4);
  v4 = 511 * Serialize_eSerializeQTaskEvent;
  *v3 = 0;
  pfHandler = (void (__cdecl *)(struct QTask_s *, struct SerializeContext_s *))QTask_aatQTaskFinalEvent[0][ptQTask->eQTaskType + v4].pfHandler;
  tSerializeContext.pzParameterBuffer = v3;
  tSerializeContext.nParameterBufferSize = 0x4000;
  tSerializeContext.ptFile = ptScriptFile;
  if ( pfHandler )
    pfHandler(ptQTask, &tSerializeContext);
  if ( strlen(v3) )
    File_atDevice[ptScriptFile->eDeviceID].pfWrite(ptScriptFile->eDeviceID, ptScriptFile, v3, strlen(v3));
  v6 = *(_DWORD *)((unsigned int)(v3 - 4) & 0xFFFFFFFC);
  --Mem_nCurrentAllocations;
  Node_Remove((_DWORD **)v6);
  memset(*(void **)(v6 + 8), 0xCDu, *(_DWORD *)(v6 + 16));
  free((void *)v6);
}

// source: h/1/serialize.c:476  [anchor-strings]
void __cdecl Serialize_Serialize(char *pzFilename, struct QTask_s *ptQTask)
{
  struct File_s *v2; // ebx

  v2 = File_New(pzFilename, "w");
  if ( !v2 )
  {
    LDebug_Error("Serialize_Serialize() : Couldn't save file: '%s'", pzFilename);
    abort();
  }
  Serialize_SerializeToFile(v2, ptQTask);
  if ( v2 == &File_tDummyAsyncFile )
    File_tDummyAsyncFile.isAsync = false;
  else
    File_atDevice[v2->eDeviceID].pfDelete(v2->eDeviceID, v2);
}

// source: h/1/serialize.c:504  [anchor-callee]
void __cdecl Serialize_TriggerQTaskEventRecursivelyChildrenFirst(
        struct QTask_s *ptQTask,
        __int16 eQTaskEvent,
        void *pxContext)
{
  struct QTask_s *ptHead; // eax
  struct QTask_s *v4; // esi
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // eax

  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    do
    {
      if ( ptHead->ptNext )
        v4 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v4 = nullptr;
      Serialize_TriggerQTaskEventRecursivelyChildrenFirst(ptHead, eQTaskEvent, pxContext);
      ptHead = v4;
    }
    while ( v4 );
  }
  pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[eQTaskEvent][ptQTask->eQTaskType].pfHandler;
  if ( pfHandler )
    pfHandler(ptQTask, pxContext);
}

// source: h/1/serialize.c:529  [anchor-caller]
struct Script_s *__cdecl Serialize_DeSerializeScript(struct Script_s *ptScript, struct QTask_s *ptQTask)
{
  struct Script_s *result; // eax

  Script_Execute(ptScript);
  Serialize_TriggerQTaskEventRecursivelyChildrenFirst(ptQTask, Serialize_eDeSerializeDoneQTaskEvent, nullptr);
  return result;
}

// source: h/1/serialize.c:549  [anchor-strings]
void __cdecl Serialize_DeSerialize(char *pzFilename, struct QTask_s *ptQTask)
{
  struct Script_s *v2; // eax
  struct Script_s *v3; // esi

  v2 = Script_New(pzFilename);
  v3 = v2;
  if ( !v2 )
  {
    LDebug_Error("Serialize_DeSerialize() : File not found: '%s'", pzFilename);
    abort();
  }
  Script_Execute(v2);
  Serialize_TriggerQTaskEventRecursivelyChildrenFirst(ptQTask, Serialize_eDeSerializeDoneQTaskEvent, nullptr);
  Script_Delete(v3);
}

// source: h/1/serialize.c:576  [size]
__int16 __cdecl Serialize_GetSerializeQTaskEvent()
{
  return Serialize_eSerializeQTaskEvent;
}

// source: h/1/serialize.c:589  [size]
__int16 __cdecl Serialize_GetDeSerializeQTaskEvent()
{
  return Serialize_eDeSerializeQTaskEvent;
}

// source: h/1/serialize.c:602  [size]
__int16 __cdecl Serialize_GetDeSerializeDoneQTaskEvent()
{
  return Serialize_eDeSerializeDoneQTaskEvent;
}

// source: h/1/serialize.c:615  [size]
__int16 __cdecl Serialize_GetGetSerializeParameterList()
{
  return Serialize_eGetSerializeParameterListQTaskEvent;
}

// source: h/1/serialize.c:628  [size]
__int16 __cdecl Serialize_GetGetSerializeInfoQTaskEvent()
{
  return Serialize_eGetSerializeInfoQTaskEvent;
}

// source: h/1/serialize.c:641  [anchor-hash]
void __cdecl Serialize_LinkGenericHandlersForQTaskType(unsigned __int16 eQTaskType)
{
  QTask_LinkQTaskEventHandlerFn(eQTaskType, Serialize_eSerializeQTaskEvent, Serialize_SerializeHandler);
  QTask_LinkQTaskEventHandlerFn(eQTaskType, Serialize_eDeSerializeQTaskEvent, Serialize_DeSerializeHandler);
}

// source: h/1/serialize.c:658  [anchor-hash]
void __cdecl Serialize_SaveQTaskTypeWithParent(unsigned __int16 eQTaskType)
{
  Serialize_aisSaveWithParent[eQTaskType] = 1;
}

// source: h/1/serialize.c:676  [anchor-caller]
void *__cdecl Serialize_SerializeChild(
        struct QTask_s *ptParent,
        struct QTask_s *ptQTask,
        void *pxContext)
{
  struct ParameterList_s *v3; // ecx
  void *result; // eax
  struct GetSerializeParameterListContext_s tGetSerializeParameterListContext; // [esp+0h] [ebp-4h] BYREF

  tGetSerializeParameterListContext.tReturn.ptParameterList = v3;
  result = QTask_aatQTaskFinalEvent[Serialize_eGetSerializeParameterListQTaskEvent][ptQTask->eQTaskType].pfHandler;
  tGetSerializeParameterListContext.tReturn.ptParameterList = nullptr;
  if ( result )
  {
    ((void (__cdecl *)(struct QTask_s *, struct GetSerializeParameterListContext_s *))result)(
      ptQTask,
      &tGetSerializeParameterListContext);
    result = tGetSerializeParameterListContext.tReturn.ptParameterList;
    if ( tGetSerializeParameterListContext.tReturn.ptParameterList )
    {
      Serialize_BeginChild(ptParent, ptQTask, (struct SerializeContext_s *)pxContext);
      Serialize_WriteParameterList(
        ptQTask,
        (struct SerializeContext_s *)pxContext,
        tGetSerializeParameterListContext.tReturn.ptParameterList);
      Serialize_End(ptQTask, (struct SerializeContext_s *)pxContext);
    }
  }
  return result;
}

// source: h/1/serialize.c:705  [anchor-strings]
void __cdecl Serialize_PrintQTaskHierarchy(
        char *zBuffer,
        unsigned int nBufferSize,
        struct QTask_s *ptParent,
        struct QTask_s *ptQTask)
{
  int v4; // eax
  struct QReference_s *v5; // ecx
  int v6; // edi
  char *QTaskTypeName; // eax
  struct QTask_s *v8; // ebx
  int v9; // esi
  struct QTask_s *i; // ecx
  char *v11; // edi
  int v12; // ebx
  int v13; // ebp
  struct QTask_s *v14; // esi
  int v15; // eax
  unsigned __int16 eQTaskType; // dx
  struct QTask_s *FirstChildOfType; // eax
  int j; // edi
  unsigned int v19; // ecx
  unsigned int v20; // eax
  int v21; // ecx
  struct QReference_s *v22; // edx
  int v23; // [esp-Ch] [ebp-18h]
  char *v24; // [esp-Ch] [ebp-18h]

  v4 = 0;
  while ( 1 )
  {
    v5 = Level_atLevelQTaskID[v4];
    if ( v5 )
    {
      if ( v5->pxObject == ptParent )
        break;
    }
    if ( ++v4 >= 4096 )
    {
      v6 = -1;
      goto LABEL_6;
    }
  }
  v6 = v4;
LABEL_6:
  QTaskTypeName = QTask_GetQTaskTypeName(ptParent->eQTaskType);
  v8 = ptQTask;
  v9 = 0;
  for ( i = ptQTask; i != ptParent; ++v9 )
    i = i->ptParent;
  v23 = v6;
  v11 = zBuffer;
  sprintf(zBuffer, "%d, \"%s\", %d", v23, QTaskTypeName, v9);
  if ( v9 > 0 )
  {
    v12 = v9 - 1;
    v13 = v9;
    do
    {
      v14 = ptQTask;
      if ( v12 > 0 )
      {
        v15 = v12;
        do
        {
          --v15;
          v14 = v14->ptParent;
        }
        while ( v15 );
      }
      eQTaskType = v14->eQTaskType;
      FirstChildOfType = QTask_GetFirstChildOfType(v14->ptParent, eQTaskType);
      for ( j = 0; FirstChildOfType != v14; ++j )
        FirstChildOfType = QTask_GetNextSiblingOfType(FirstChildOfType, eQTaskType);
      v19 = strlen(zBuffer);
      v24 = QTask_GetQTaskTypeName(eQTaskType);
      sprintf(&zBuffer[v19], ", \"%s\", %d", v24, j);
      --v12;
      --v13;
    }
    while ( v13 );
    v8 = ptQTask;
    v11 = zBuffer;
  }
  v20 = strlen(v11);
  v21 = 0;
  while ( 1 )
  {
    v22 = Level_atLevelQTaskID[v21];
    if ( v22 )
    {
      if ( v22->pxObject == v8 )
        break;
    }
    if ( ++v21 >= 4096 )
    {
      v21 = -1;
      break;
    }
  }
  sprintf(&v11[v20], ", %d", v21);
}

// source: h/1/serialize.c:776  [anchor-mhash]
struct QTask_s *__cdecl Serialize_ParseQTaskHierarchy(struct ArgList_s *ptArgList, int *piArg)
{
  struct QTask_s *TaskFromArgList; // ebx
  int v3; // eax
  int v4; // eax

  TaskFromArgList = Serialize_GetTaskFromArgList(ptArgList, piArg);
  if ( !TaskFromArgList )
    return nullptr;
  v3 = (*piArg)++;
  v4 = Script_EvalArgInt(ptArgList, v3);
  return Serialize_GetChildTaskFromArgList(ptArgList, TaskFromArgList, v4, piArg);
}

// source: h/1/serialize.c:802  [size]
enum bool __cdecl Serialize_ForceSerializeChildren(enum bool isForced)
{
  Serialize_isForceSerializeChildren = isForced;
  return isForced;
}

// source: h/1/serialize.c:815  [anchor-hash]
void __cdecl Serialize_Open()
{
  unsigned __int16 BaseQTaskType; // si

  Serialize_eGetSerializeParameterListQTaskEvent = QTask_NewQTaskEventFn(0, "GetSerializeParameterList");
  Serialize_eSerializeQTaskEvent = QTask_NewQTaskEventFn(0, "Serialize");
  Serialize_eDeSerializeQTaskEvent = QTask_NewQTaskEventFn(0, "DeSerialize");
  Serialize_eDeSerializeDoneQTaskEvent = QTask_NewQTaskEventFn(0, "DeSerializeDone");
  Serialize_eGetSerializeInfoQTaskEvent = QTask_NewQTaskEventFn(0, "SerializeInfo");
  BaseQTaskType = QTask_GetBaseQTaskType();
  QTask_LinkQTaskEventHandlerFn(BaseQTaskType, Serialize_eSerializeQTaskEvent, Serialize_SerializeHandler);
  QTask_LinkQTaskEventHandlerFn(BaseQTaskType, Serialize_eDeSerializeQTaskEvent, Serialize_DeSerializeHandler);
  Symbol_Register(
    "DefineTaskState",
    Serialize_DeSerializeScriptFunction,
    nullptr,
    -1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}

// source: h/1/serialize.c:836  [anchor-hash]
void __cdecl Serialize_Close()
{
  Symbol_Remove("DefineTaskState");
  QTask_DeleteQTaskEvent(Serialize_eGetSerializeInfoQTaskEvent);
  QTask_DeleteQTaskEvent(Serialize_eGetSerializeParameterListQTaskEvent);
  QTask_DeleteQTaskEvent(Serialize_eSerializeQTaskEvent);
  QTask_DeleteQTaskEvent(Serialize_eDeSerializeQTaskEvent);
  QTask_DeleteQTaskEvent(Serialize_eDeSerializeDoneQTaskEvent);
}
