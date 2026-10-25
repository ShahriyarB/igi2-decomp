/* h/2/animtask.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/animtask.c:66  [size]
void __cdecl AnimQTask_GetSerializeParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = AnimQTask_ptSerializeParameterList;
}

// source: h/2/animtask.c:84  [size]
// attributes: thunk
void __cdecl AnimQTask_DeSerializeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  Serialize_DeSerializeHandler(ptQTask, pxContext);
}

// source: h/2/animtask.c:100  [anchor-strings]
void __cdecl AnimQTask_ParameterPrintHandler(void *pxData, void *pxContext)
{
  char *v2; // esi
  char *v3; // esi
  int v4; // ebx
  float *v5; // edi

  v2 = *((char **)pxContext + 2);
  sprintf(v2, (char *const)&g_ptNetManager.tReceiveCounters.tCounters[9].nBytes, *((_DWORD *)pxData + 32851));
  v3 = &v2[strlen(v2)];
  v4 = 0;
  if ( *((int *)pxData + 32851) > 0 )
  {
    v5 = (float *)((char *)pxData + 240);
    do
    {
      sprintf(v3, ", %d, %.4f", *(char *)v5, v5[1]);
      v3 += strlen(v3);
      ++v4;
      v5 += 2;
    }
    while ( v4 < (int)(*((_DWORD *)pxData + 32851)) );
  }
}

// source: h/2/animtask.c:205  [anchor-callee]
void __cdecl AnimQTask_UpdateTarget(struct AnimQTask_s *ptAnimQTask)
{
  unsigned int nTargetID; // eax
  struct QReference_s *v2; // eax
  unsigned __int16 *pxObject; // eax
  int nTick; // edx
  void (__cdecl *pfHandler)(unsigned __int16 *, struct UpdateAnimDataContext_s *); // ecx
  struct UpdateAnimDataContext_s tUpdateAnimDataContext; // [esp+0h] [ebp-8h] BYREF

  nTargetID = ptAnimQTask->nTargetID;
  if ( nTargetID < 0x1000 )
  {
    v2 = Level_atLevelQTaskID[nTargetID];
    if ( v2 )
    {
      pxObject = (unsigned __int16 *)v2->pxObject;
      if ( pxObject )
      {
        nTick = ptAnimQTask->nTick;
        tUpdateAnimDataContext.pvChannel = ptAnimQTask->avChannel;
        tUpdateAnimDataContext.nTime = nTick;
        pfHandler = (void (__cdecl *)(unsigned __int16 *, struct UpdateAnimDataContext_s *))QTask_aatQTaskFinalEvent[AnimQTask_eUpdateAnimDataEvent][pxObject[18]].pfHandler;
        if ( pfHandler )
          pfHandler(pxObject, &tUpdateAnimDataContext);
      }
    }
  }
}

// source: h/2/animtask.c:230  [anchor-callee]
void __cdecl AnimQTask_RunCommand(struct AnimQTask_s *ptAnimQTask)
{
  double v1; // st7
  int v2; // eax
  int iChannel; // edx
  double vValue; // st7

  if ( (__int64)ptAnimQTask->avChannel[33] < ptAnimQTask->nCommand )
  {
    if ( ptAnimQTask->avChannel[32] != 0.0 )
    {
      v1 = ptAnimQTask->avChannel[32] - 1.0;
      ptAnimQTask->avChannel[32] = v1;
      if ( v1 == 0.0 )
        ptAnimQTask->avChannel[33] = ptAnimQTask->avChannel[33] + 1.0;
    }
    while ( ptAnimQTask->avChannel[32] == 0.0 )
    {
      v2 = (__int64)ptAnimQTask->avChannel[33];
      if ( v2 >= ptAnimQTask->nCommand )
        break;
      iChannel = ptAnimQTask->atCommand[v2].iChannel;
      vValue = ptAnimQTask->atCommand[v2].vValue;
      if ( iChannel == 32 )
        vValue = (double)(int)(__int64)vValue;
      ptAnimQTask->avChannel[iChannel] = vValue;
      if ( ptAnimQTask->avChannel[32] == 0.0 )
        ptAnimQTask->avChannel[33] = ptAnimQTask->avChannel[33] + 1.0;
    }
  }
  AnimQTask_UpdateTarget(ptAnimQTask);
}

// source: h/2/animtask.c:403  [anchor-caller]
void __cdecl AnimQTask_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptHead; // eax
  int v3; // edx
  struct QTask_s *v4; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, _DWORD); // ecx
  int v6; // edx

  if ( !pxContext || !*(_DWORD *)pxContext )
  {
    ptHead = ptQTask->tQTaskChildren.ptHead;
    if ( ptHead->ptNext )
    {
      if ( ptHead )
      {
        v3 = QTask_nProtectedQTaskStackOffset;
        do
        {
          if ( ptHead->ptNext )
            v4 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
          else
            v4 = nullptr;
          QTask_atProtectedQTaskStack[v3].ptQTask = v4;
          pfHandler = (void (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][ptHead->eQTaskType].pfHandler;
          v6 = v3 + 1;
          QTask_nProtectedQTaskStackOffset = v6;
          if ( pfHandler )
          {
            pfHandler(ptHead, 0);
            v6 = QTask_nProtectedQTaskStackOffset;
          }
          ptHead = (struct QTask_s *)dword_849C7DC[v6];
          v3 = v6 - 1;
          QTask_nProtectedQTaskStackOffset = v3;
        }
        while ( ptHead );
      }
    }
  }
  memset(&ptQTask[2].tQTaskRefList.ptMiddle, 0, 0x88u);
  ptQTask[3285].tQTaskChildren.ptHead = nullptr;
  AnimQTask_RunCommand((struct AnimQTask_s *)ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[3282].eQTaskType, ptQTask);
}

// source: h/2/animtask.c:606  [anchor-mhash]
void __cdecl AnimQTask_ParseHandler(void *pxData, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float *v17; };
    struct { char igi2_o1[4]; int v18; };
    struct { char igi2_o2[8]; float v19; };
    struct { char igi2_o3[12]; float v20; };
    struct { char igi2_o4[16]; int iCount; };
    struct { char igi2_o5[20]; __int64 v22; };
    char igi2_extent[28];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // esi
  struct ArgList_s *v3; // edi
  int v4; // eax
  int v5; // esi
  struct ArgList_s *v6; // edi
  char v7; // al
  struct ArgList_s *v8; // edi
  int v9; // esi
  bool v10; // zf
  int isQVM; // eax
  double v12; // st7
  double v13; // st7
  float *v14; // ecx
  int v15; // eax
  int v16; // edx

  v2 = *(_DWORD *)pxContext;
  v3 = *((struct ArgList_s **)pxContext + 1);
  if ( v3->isQVM )
  {
    igi2_frame.v17 = nullptr;
    QVM_EvalArg(&igi2_frame.v17, 4, v3, v2, 1);
    v4 = (int)igi2_frame.v17;
  }
  else
  {
    v4 = Expression_EvalInt(v3->aptExpression[v2]);
  }
  v5 = v2 + 1;
  *((_DWORD *)pxData + 32851) = v4;
  igi2_frame.iCount = 0;
  if ( v4 > 0 )
  {
    igi2_frame.v17 = (float *)((char *)pxData + 244);
    do
    {
      v6 = *((struct ArgList_s **)pxContext + 1);
      if ( v6->isQVM )
      {
        igi2_frame.v18 = 0;
        QVM_EvalArg(&igi2_frame.v18, 4, v6, v5, 1);
        v7 = igi2_frame.v18;
      }
      else
      {
        v7 = Expression_EvalInt(v6->aptExpression[v5]);
      }
      *((_BYTE *)igi2_frame.v17 - 4) = v7;
      v8 = *((struct ArgList_s **)pxContext + 1);
      v9 = v5 + 1;
      v10 = v7 == 32;
      isQVM = v8->isQVM;
      if ( v10 )
      {
        if ( isQVM )
        {
          igi2_frame.v19 = 0.0;
          QVM_EvalArg(&igi2_frame.v19, 4, v8, v9, 2);
          v12 = igi2_frame.v19;
        }
        else
        {
          v12 = Expression_EvalFloat(v8->aptExpression[v9]);
        }
        igi2_frame.v22 = (__int64)v12;
        LODWORD(igi2_frame.v22) = (__int64)v12;
        v13 = (double)(int)igi2_frame.v22;
      }
      else if ( isQVM )
      {
        igi2_frame.v20 = 0.0;
        QVM_EvalArg(&igi2_frame.v20, 4, v8, v9, 2);
        v13 = igi2_frame.v20;
      }
      else
      {
        v13 = Expression_EvalFloat(v8->aptExpression[v9]);
      }
      v14 = igi2_frame.v17;
      v15 = igi2_frame.iCount;
      *igi2_frame.v17 = v13;
      igi2_frame.v17 = v14 + 2;
      v16 = *((_DWORD *)pxData + 32851);
      v5 = v9 + 1;
      igi2_frame.iCount = v15 + 1;
    }
    while ( v15 + 1 < v16 );
  }
  *(_DWORD *)pxContext = v5;
}

// source: h/2/animtask.c:641  [anchor-mhash]
void __cdecl AnimQTask_GetNumberOfArgumentsHandler(void *pxData, void *pxContext)
{
  _DWORD *v2; // esi
  int v3; // eax
  struct ArgList_s *v4; // edi

  v2 = pxContext;
  v3 = *((_DWORD *)pxContext + 1);
  v4 = *((struct ArgList_s **)pxContext + 2);
  if ( v4->isQVM )
  {
    pxContext = nullptr;
    QVM_EvalArg(&pxContext, 4, v4, v3, 1);
    *v2 = 2 * (_DWORD)pxContext + 1;
  }
  else
  {
    *v2 = 2 * Expression_EvalInt(v4->aptExpression[v3]) + 1;
  }
}

// source: h/2/animtask.c:657  [size]
void __cdecl AnimQTask_PrintHandler(void *pxData, void *pxContext)
{
  ;
}

// source: h/2/animtask.c:707  [anchor-mhash]
void __cdecl AnimQTask_CopyHandler(void *pxData, void *pxContext)
{
  _DWORD *v2; // eax

  v2 = *(_DWORD **)pxContext;
  *v2++ = *((_DWORD *)pxData + 32851);
  qmemcpy(v2, (char *)pxData + 104, 0x88u);
  qmemcpy(v2 + 34, (char *)pxData + 240, 0x20000u);
}

// source: h/2/animtask.c:734  [anchor-mhash]
void __cdecl AnimQTask_PasteHandler(void *pxData, void *pxContext)
{
  _DWORD *v2; // eax

  v2 = *(_DWORD **)pxContext;
  *((_DWORD *)pxData + 32851) = **(_DWORD **)pxContext;
  qmemcpy((char *)pxData + 104, ++v2, 0x88u);
  qmemcpy((char *)pxData + 240, v2 + 34, 0x20000u);
}

// source: h/2/animtask.c:761  [size]
void __cdecl AnimQTask_GetSizeHandler(void *pxData, void *pxContext)
{
  *(_DWORD *)pxContext = 131212;
}

// source: h/2/animtask.c:784  [size]
void __cdecl AnimQTask_RigidDynCubeObjUpdateAnimDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: h/2/animtask.c:829  [size]
void __cdecl AnimQTask_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = AnimQTask_ptParameterList;
}

// source: h/2/animtask.c:846  [anchor-mhash]
void __cdecl AnimQTask_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[1].tQTaskRefList.ptMiddle = (struct QReference_s *)1065353216;
  ptQTask[2].ptNext = (struct QTask_s *)1065353216;
  ptQTask[2].tQTaskChildren.ptTail = (struct QTask_s *)1065353216;
  ptQTask[3285].tQTaskChildren.ptHead = (struct QTask_s *)-1;
  ptQTask[3285].ptNext = (struct QTask_s *)-1;
  ptQTask[1].ptNext = nullptr;
  ptQTask[1].ptPrev = nullptr;
  ptQTask[1].tQTaskChildren.ptHead = nullptr;
  ptQTask[1].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[1].tQTaskChildren.ptTail = nullptr;
  ptQTask[1].tQTaskRefList.ptHead = nullptr;
  ptQTask[1].tQTaskRefList.ptTail = nullptr;
  ptQTask[1].ptParent = nullptr;
  *(_DWORD *)&ptQTask[1].eQTaskType = 0;
  ptQTask[2].ptPrev = nullptr;
  ptQTask[2].tQTaskChildren.ptHead = nullptr;
  ptQTask[2].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[2].tQTaskRefList.ptHead = nullptr;
  ptQTask[3285].ptPrev = (struct QTask_s *)1;
  LOBYTE(ptQTask[3282].ptParent) = 1;
  LOBYTE(ptQTask[6].ptNext) = 32;
  ptQTask[6].ptPrev = nullptr;
  BYTE1(ptQTask[3282].ptParent) = 0;
  *(_DWORD *)&ptQTask[3284].eQTaskType = 0;
  *(_DWORD *)&ptQTask[3282].eQTaskType = 0;
  ptQTask[3283].ptNext = nullptr;
  ptQTask[3283].ptPrev = nullptr;
  ptQTask[3284].ptParent = nullptr;
  memset(&ptQTask[2].tQTaskRefList.ptMiddle, 0, 0x88u);
  QTaskList_Register(AnimQTask_ptQTaskList, (struct QTaskList_s *)ptQTask);
  LOBYTE(ptQTask[3285].tQTaskChildren.ptMiddle) = 0;
  BYTE1(ptQTask[3285].tQTaskChildren.ptMiddle) = 0;
}

// source: h/2/animtask.c:915  [anchor-mhash]
void __cdecl AnimQTask_DeleteHandler(struct QTask_s *ptQTask)
{
  int v1; // ecx
  struct QReference_s *v2; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v4; // eax
  struct QTask_s *v5; // eax

  v1 = 0;
  while ( 1 )
  {
    v2 = Level_atLevelQTaskID[v1];
    if ( v2 )
    {
      if ( v2->pxObject == ptQTask )
        break;
    }
    if ( ++v1 >= 4096 )
      goto LABEL_9;
  }
  if ( v1 >= 0 )
  {
    pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Level_eRemoveLevelScriptSymbolsEvent][ptQTask->eQTaskType].pfHandler;
    if ( pfHandler )
      pfHandler(ptQTask);
  }
LABEL_9:
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[3282].eQTaskType);
  QTaskList_Remove(AnimQTask_ptQTaskList, ptQTask);
  v4 = *(_DWORD *)&ptQTask[3284].eQTaskType;
  if ( v4 )
  {
    v5 = *(struct QTask_s **)(v4 + 8);
    if ( v5 )
      QTask_Delete(v5);
    QReference_Delete(*(struct QReference_s **)&ptQTask[3284].eQTaskType, &QTask_tQTaskRefPool);
  }
}

// source: h/2/animtask.c:968  [anchor-mhash]
void __cdecl AnimQTask_RunHandler(struct QTask_s *ptQTask)
{
  if ( *(_DWORD *)&ptQTask[3282].eQTaskType && ptQTask[3283].ptNext->ptNext && ptQTask[3283].ptPrev )
    LOBYTE(ptQTask[3282].ptParent) = (__int64)Level_RunLevelExpression(
                                                (struct LevelExpression_s *)&ptQTask[3282].eQTaskType,
                                                ptQTask);
  if ( LOBYTE(ptQTask[3282].ptParent) )
    AnimQTask_SetIdealTime(ptQTask, (int)&ptQTask[3285].tQTaskChildren.ptHead->ptNext + 1);
}

// source: h/2/animtask.c:993  [size]
void __cdecl AnimQTask_RegisterScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( !BYTE1(ptQTask[3282].ptParent) )
  {
    BYTE1(ptQTask[3282].ptParent) = 1;
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.isRun", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      &ptQTask[3282].ptParent,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.nTick", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int,
      &ptQTask[3285].tQTaskChildren,
      4,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
  }
}

// source: h/2/animtask.c:1026  [size]
void __cdecl AnimQTask_RemoveScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( BYTE1(ptQTask[3282].ptParent) )
  {
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    BYTE1(ptQTask[3282].ptParent) = 0;
    sprintf(igi2_frame.zTemp, "%s.isRun", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.nTick", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
  }
}

// source: h/2/animtask.c:1061  [anchor-mhash]
void __cdecl AnimQTask_GetKeyframeSizeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptNext; // eax
  struct QReference_s *v3; // eax
  unsigned __int16 *pxObject; // eax
  void (__cdecl *pfHandler)(unsigned __int16 *, void *); // ecx

  ptNext = ptQTask[3285].ptNext;
  if ( (unsigned int)ptNext < 0x1000 && (v3 = Level_atLevelQTaskID[(_DWORD)ptNext]) != nullptr )
    pxObject = (unsigned __int16 *)v3->pxObject;
  else
    pxObject = nullptr;
  if ( pxObject )
  {
    pfHandler = (void (__cdecl *)(unsigned __int16 *, void *))QTask_aatQTaskFinalEvent[AnimQTask_eGetKeyframeSizeEvent][pxObject[18]].pfHandler;
    if ( pfHandler )
    {
      pfHandler(pxObject, pxContext);
      *(_DWORD *)pxContext += (int)(232);
    }
    else
    {
      *(_DWORD *)pxContext = 232;
    }
  }
  else
  {
    *(_DWORD *)pxContext = 232;
  }
}

// source: h/2/animtask.c:1095  [anchor-mhash]
void __cdecl AnimQTask_SaveKeyframeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptNext; // eax
  struct QReference_s *v3; // eax
  unsigned __int16 *pxObject; // eax
  int v5; // edx
  void (__cdecl *pfHandler)(unsigned __int16 *, struct SaveKeyframeContext_s *); // ecx
  struct SaveKeyframeContext_s tSaveKeyframeContext; // [esp+Ch] [ebp-14h] BYREF

  ptNext = ptQTask[3285].ptNext;
  if ( (unsigned int)ptNext < 0x1000 && (v3 = Level_atLevelQTaskID[(_DWORD)ptNext]) != nullptr )
    pxObject = (unsigned __int16 *)v3->pxObject;
  else
    pxObject = nullptr;
  v5 = *(_DWORD *)pxContext;
  qmemcpy(&tSaveKeyframeContext, pxContext, sizeof(tSaveKeyframeContext));
  tSaveKeyframeContext.pxBuffer = (void *)(v5 + 232);
  qmemcpy((void *)v5, &ptQTask[2].tQTaskRefList.ptMiddle, 0xE8u);
  if ( pxObject )
  {
    pfHandler = (void (__cdecl *)(unsigned __int16 *, struct SaveKeyframeContext_s *))QTask_aatQTaskFinalEvent[AnimQTask_eSaveKeyframeEvent][pxObject[18]].pfHandler;
    if ( pfHandler )
      pfHandler(pxObject, &tSaveKeyframeContext);
  }
}

// source: h/2/animtask.c:1131  [anchor-mhash]
void __cdecl AnimQTask_RestoreKeyframeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptNext; // eax
  struct QReference_s *v3; // eax
  unsigned __int16 *pxObject; // edx
  void *pxBuffer; // esi
  void (__cdecl *pfHandler)(unsigned __int16 *, struct RestoreKeyframeContext_s *); // eax
  struct RestoreKeyframeContext_s tRestoreKeyframeContext; // [esp+Ch] [ebp-8h] BYREF

  ptNext = ptQTask[3285].ptNext;
  if ( (unsigned int)ptNext < 0x1000 && (v3 = Level_atLevelQTaskID[(_DWORD)ptNext]) != nullptr )
    pxObject = (unsigned __int16 *)v3->pxObject;
  else
    pxObject = nullptr;
  tRestoreKeyframeContext.pxBuffer = *(void **)pxContext;
  pxBuffer = tRestoreKeyframeContext.pxBuffer;
  tRestoreKeyframeContext.nTick = *((_DWORD *)pxContext + 1);
  tRestoreKeyframeContext.pxBuffer = (char *)tRestoreKeyframeContext.pxBuffer + 232;
  qmemcpy(&ptQTask[2].tQTaskRefList.ptMiddle, pxBuffer, 0xE8u);
  ptQTask[3285].tQTaskChildren.ptHead = *((struct QTask_s **)pxContext + 1);
  if ( pxObject )
  {
    pfHandler = (void (__cdecl *)(unsigned __int16 *, struct RestoreKeyframeContext_s *))QTask_aatQTaskFinalEvent[AnimQTask_eRestoreKeyframeEvent][pxObject[18]].pfHandler;
    if ( pfHandler )
      pfHandler(pxObject, &tRestoreKeyframeContext);
  }
}

// source: h/2/animtask.c:1171  [anchor-hash]
void __cdecl AnimQTask_OpenTypes()
{
  int v0; // esi

  AnimQTask_eQTaskType = QTask_NewQTaskType("AnimTask", 131416, EditorRigidObj_eQTaskType, 0, 0);
  AnimQTask_eUpdateAnimDataEvent = QTask_NewQTaskEventFn(0, "UpdateAnimData");
  AnimQTask_eRedrawAnimDataEvent = QTask_NewQTaskEventFn(0, "RedrawAnimData");
  AnimQTask_eGetChannelDescriptionEvent = QTask_NewQTaskEventFn(0, "GetChannelDescription");
  AnimQTask_eGetKeyframeSizeEvent = QTask_NewQTaskEventFn(0, "GetKeyframeSize");
  AnimQTask_eSaveKeyframeEvent = QTask_NewQTaskEventFn(0, "SaveKeyframe");
  AnimQTask_eRestoreKeyframeEvent = QTask_NewQTaskEventFn(0, "RestoreKeyframe");
  AnimQTask_eReadChannelsEvent = QTask_NewQTaskEventFn(0, "ReadChannels");
  v0 = ParameterList_NewParameterType("AnimData", -1);
  AnimQTask_eParameterType = v0;
  ParameterList_LinkParameterEventHandler(v0, ParameterList_eQParameterParseEvent, AnimQTask_ParseHandler);
  ParameterList_LinkParameterEventHandler(
    v0,
    ParameterList_eQParameterPrintEvent,
    (void (__cdecl *)(void *, void *))AnimQTask_PrintHandler);
  ParameterList_LinkParameterEventHandler(v0, ParameterList_eQParameterCopyEvent, AnimQTask_CopyHandler);
  ParameterList_LinkParameterEventHandler(v0, ParameterList_eQParameterPasteEvent, AnimQTask_PasteHandler);
  ParameterList_LinkParameterEventHandler(
    v0,
    ParameterList_eQParameterGetSizeEvent,
    (void (__cdecl *)(void *, void *))AnimQTask_GetSizeHandler);
  ParameterList_LinkParameterEventHandler(
    v0,
    ParameterList_eQParameterGetNumberOfArgumentsEvent,
    AnimQTask_GetNumberOfArgumentsHandler);
}

// source: h/2/animtask.c:1203  [anchor-hash]
void __cdecl AnimQTask_SetIdealTime(struct QTask_s *ptQTask, int nTick)
{
  struct QTask_s *ptHead; // eax
  struct QTask_s *v3; // eax
  int v4; // edi

  if ( nTick && (ptHead = ptQTask[3285].tQTaskChildren.ptHead, nTick >= (int)ptHead) )
  {
    if ( nTick > (int)ptHead )
    {
      do
      {
        AnimQTask_RunCommand((struct AnimQTask_s *)ptQTask);
        v3 = (struct QTask_s *)((char *)&ptQTask[3285].tQTaskChildren.ptHead->ptNext + 1);
        ptQTask[3285].tQTaskChildren.ptHead = v3;
      }
      while ( nTick > (int)v3 );
    }
  }
  else
  {
    memset(&ptQTask[2].tQTaskRefList.ptMiddle, 0, 0x88u);
    ptQTask[3285].tQTaskChildren.ptHead = nullptr;
    if ( nTick >= 0 )
    {
      v4 = nTick + 1;
      do
      {
        AnimQTask_RunCommand((struct AnimQTask_s *)ptQTask);
        --v4;
      }
      while ( v4 );
    }
  }
}

// source: h/2/animtask.c:1243  [size]
__int16 __cdecl AnimQTask_GetUpdateAnimDataQTaskEvent()
{
  return AnimQTask_eUpdateAnimDataEvent;
}

// source: h/2/animtask.c:1258  [size]
__int16 __cdecl AnimQTask_GetRedrawAnimDataQTaskEvent()
{
  return AnimQTask_eRedrawAnimDataEvent;
}

// source: h/2/animtask.c:1273  [size]
__int16 __cdecl AnimQTask_GetGetChannelDescriptionQTaskEvent()
{
  return AnimQTask_eGetChannelDescriptionEvent;
}

// source: h/2/animtask.c:1288  [size]
int __cdecl AnimQTask_GetParameterType()
{
  return AnimQTask_eParameterType;
}

// source: h/2/animtask.c:1302  [size]
unsigned __int16 __cdecl AnimQTask_GetQTaskType()
{
  return AnimQTask_eQTaskType;
}

// source: h/2/animtask.c:1315  [size]
__int16 __cdecl AnimQTask_GetGetKeyframeSizeQTaskEvent()
{
  return AnimQTask_eGetKeyframeSizeEvent;
}

// source: h/2/animtask.c:1328  [size]
__int16 __cdecl AnimQTask_GetSaveKeyframeQTaskEvent()
{
  return AnimQTask_eSaveKeyframeEvent;
}

// source: h/2/animtask.c:1343  [size]
__int16 __cdecl AnimQTask_GetRestoreKeyframeQTaskEvent()
{
  return AnimQTask_eRestoreKeyframeEvent;
}

// source: h/2/animtask.c:1356  [size]
__int16 __cdecl AnimQTask_GetReadChannelsQTaskEvent()
{
  return AnimQTask_eReadChannelsEvent;
}

// source: h/2/animtask.c:1369  [anchor-mhash]
int __cdecl AnimQTask_GetCommandTick(struct QTask_s *ptQTask, int nCommand)
{
  int result; // eax
  int v3; // esi
  int v4; // edi
  float *p_ptPrev; // ecx
  float *v6; // ecx
  int v7; // edx

  result = 0;
  v3 = 0;
  if ( nCommand >= 4 )
  {
    v4 = 3;
    p_ptPrev = (float *)&ptQTask[6].ptPrev;
    do
    {
      if ( *((_BYTE *)p_ptPrev - 4) == 32 )
        result += (__int64)*p_ptPrev;
      if ( *((_BYTE *)p_ptPrev + 4) == 32 )
        result += (__int64)p_ptPrev[2];
      if ( *((_BYTE *)p_ptPrev + 12) == 32 )
        result += (__int64)p_ptPrev[4];
      if ( *((_BYTE *)p_ptPrev + 20) == 32 )
        result += (__int64)p_ptPrev[6];
      v4 += 4;
      v3 += 4;
      p_ptPrev += 8;
    }
    while ( v4 < nCommand );
  }
  if ( v3 < nCommand )
  {
    v6 = (float *)(&ptQTask[6].ptPrev + 2 * v3);
    v7 = nCommand - v3;
    do
    {
      if ( *((_BYTE *)v6 - 4) == 32 )
        result += (__int64)*v6;
      v6 += 2;
      --v7;
    }
    while ( v7 );
  }
  return result;
}

// source: h/2/animtask.c:1416  [anchor-mhash]
int __cdecl AnimQTask_GetCommand(struct QTask_s *ptQTask, int nTime)
{
  int v3; // ecx
  int v4; // edx
  int result; // eax
  struct QTask_s *ptPrev; // ebp
  float *p_ptPrev; // esi

  v3 = 0;
  v4 = 0;
  result = 0;
  if ( nTime >= 0 )
  {
    ptPrev = ptQTask[3285].ptPrev;
    p_ptPrev = (float *)&ptQTask[6].ptPrev;
    do
    {
      if ( v4 >= (int)ptPrev )
        break;
      if ( v3 <= nTime )
        result = v4;
      if ( *((_BYTE *)p_ptPrev - 4) == 32 )
        v3 += (__int64)*p_ptPrev;
      ++v4;
      p_ptPrev += 2;
    }
    while ( v3 <= nTime );
  }
  return result;
}

// source: h/2/animtask.c:1448  [anchor-mhash]
int __cdecl AnimQTask_AnimQTaskListSetIdealTime(struct QTask_s *ptExcludeQTask, int nTick)
{
  int result; // eax
  int v4; // ebp
  int v5; // edi
  struct QTask_s *v6; // esi

  result = (int)AnimQTask_ptQTaskList;
  v4 = 0;
  if ( AnimQTask_ptQTaskList->nTask > 0 )
  {
    v5 = 8;
    do
    {
      v6 = *(struct QTask_s **)(v5 + result);
      if ( v6 != ptExcludeQTask )
      {
        AnimQTask_SetIdealTime(v6, nTick);
        result = (int)AnimQTask_ptQTaskList;
      }
      ++v4;
      v5 += 4;
    }
    while ( v4 < (int)(*(_DWORD *)result) );
  }
  return result;
}

// source: h/2/animtask.c:1479  [size]
struct QTaskList_s *__cdecl AnimQTask_GetQTaskList()
{
  return AnimQTask_ptQTaskList;
}

// source: h/2/animtask.c:1494  [anchor-hash]
enum bool __cdecl AnimQTask_IsTargetValid(struct QTask_s *ptQTask)
{
  struct QTask_s *ptNext; // eax
  struct QReference_s *v2; // eax
  unsigned __int16 *pxObject; // eax
  enum bool result; // eax

  ptNext = ptQTask[3285].ptNext;
  result = false;
  if ( (unsigned int)ptNext < 0x1000 )
  {
    v2 = Level_atLevelQTaskID[(_DWORD)ptNext];
    if ( v2 )
    {
      pxObject = (unsigned __int16 *)v2->pxObject;
      if ( pxObject )
      {
        if ( QTask_aatQTaskFinalEvent[AnimQTask_eGetKeyframeSizeEvent][pxObject[18]].pfHandler )
          return true;
      }
    }
  }
  return result;
}

// source: h/2/animtask.c:1523  [anchor-hash]
struct QTask_s *__cdecl AnimQTask_GetTarget(struct QTask_s *ptQTask)
{
  struct QTask_s *ptNext; // eax
  struct QReference_s *v2; // eax

  ptNext = ptQTask[3285].ptNext;
  if ( (unsigned int)ptNext < 0x1000 && (v2 = Level_atLevelQTaskID[(_DWORD)ptNext]) != nullptr )
    return (struct QTask_s *)v2->pxObject;
  else
    return nullptr;
}

// source: h/2/animtask.c:2035  [anchor-hash]
void __cdecl AnimQTask_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // edx
  unsigned __int16 v3; // si
  struct ParameterList_s *v4; // eax
  int v5; // edx

  v0 = AnimQTask_eQTaskType;
  QTask_LinkQTaskEventHandlerFn(AnimQTask_eQTaskType, 0, AnimQTask_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, AnimQTask_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, AnimQTask_RunHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))AnimQTask_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, AnimQTask_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(v0, AnimQTask_eGetKeyframeSizeEvent, AnimQTask_GetKeyframeSizeHandler);
  QTask_LinkQTaskEventHandlerFn(v0, AnimQTask_eSaveKeyframeEvent, AnimQTask_SaveKeyframeHandler);
  QTask_LinkQTaskEventHandlerFn(v0, AnimQTask_eRestoreKeyframeEvent, AnimQTask_RestoreKeyframeHandler);
  ParameterList_LinkParameterEventHandler(
    AnimQTask_eParameterType,
    ParameterList_eQParameterPrintEvent,
    AnimQTask_ParameterPrintHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eRegisterLevelScriptSymbolsEvent,
    AnimQTask_RegisterScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Level_eRemoveLevelScriptSymbolsEvent, AnimQTask_RemoveScriptSymbolsHandler);
  v1 = (struct ParameterList_s *)Mem_AllocFn(172, 4);
  v2 = Level_eParameterTypeObjectPos;
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  v1->nParameters = 0;
  v1->nMaxParameters = 8;
  AnimQTask_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0x28u, v2, "Position", 7u, nullptr);
  ParameterList_AddParameter(AnimQTask_ptParameterList, 0x40u, Level_eParameterTypeReal32x9, "Orientation", 7u, nullptr);
  ParameterList_AddParameter(AnimQTask_ptParameterList, 0x20148u, Level_eParameterTypeInt32, "TargetID", 7u, nullptr);
  ParameterList_AddParameter(
    AnimQTask_ptParameterList,
    0x200F4u,
    Level_eParameterTypeVarString,
    off_6A50D8,
    7u,
    nullptr);
  ParameterList_AddParameter(AnimQTask_ptParameterList, 0x200F0u, Level_eParameterTypebool8, "Initial run", 7u, nullptr);
  ParameterList_AddParameter(
    AnimQTask_ptParameterList,
    0x20154u,
    Level_eParameterTypePushButton,
    "Copy current target position",
    6u,
    nullptr);
  ParameterList_AddParameter(
    AnimQTask_ptParameterList,
    0x20155u,
    Level_eParameterTypePushButton,
    "Copy current target orientation",
    6u,
    nullptr);
  ParameterList_AddParameter(AnimQTask_ptParameterList, 0, AnimQTask_eParameterType, "AnimData", 7u, nullptr);
  QTask_LinkQTaskEventHandlerFn(
    RigidDynCubeObj_eQTaskType,
    AnimQTask_eRedrawAnimDataEvent,
    (void (__cdecl *)(struct QTask_s *, void *))AnimQTask_RigidDynCubeObjUpdateAnimDataHandler);
  AnimQTask_ptQTaskList = QTaskList_New(64);
  AnimQTask_nKeyframeInterval = 60;
  AnimQTask_nMaxKeyframes = 1024;
  v3 = AnimQTask_eQTaskType;
  QTask_LinkQTaskEventHandlerFn(
    AnimQTask_eQTaskType,
    Serialize_eGetSerializeParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))AnimQTask_GetSerializeParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v3, Serialize_eDeSerializeQTaskEvent, AnimQTask_DeSerializeHandler);
  v4 = (struct ParameterList_s *)Mem_AllocFn(52, 4);
  v5 = Level_eParameterTypeInt32;
  v4->ptParameterListItem = (struct ParameterListItem_s *)&v4[1];
  v4->nParameters = 0;
  v4->nMaxParameters = 2;
  AnimQTask_ptSerializeParameterList = v4;
  ParameterList_AddParameter(v4, 0x20150u, v5, "nTick", 7u, nullptr);
  ParameterList_AddParameter(
    AnimQTask_ptSerializeParameterList,
    0x68u,
    SerializeArray_eParameterType,
    "avChannel",
    7u,
    (void *)0x88);
}

// source: h/2/animtask.c:2101  [anchor-mhash]
void __cdecl AnimQTask_Close()
{
  int v0; // esi
  int v1; // esi

  QTaskList_Delete(AnimQTask_ptQTaskList);
  QTask_DeleteQTaskType(AnimQTask_eQTaskType);
  ParameterList_atParameterType[AnimQTask_eParameterType].isUsed = false;
  AnimQTask_eQTaskType = 512;
  AnimQTask_eParameterType = -1;
  if ( AnimQTask_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&AnimQTask_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  if ( AnimQTask_ptSerializeParameterList )
  {
    v1 = *(_DWORD *)((unsigned int)&AnimQTask_ptSerializeParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
  QTask_DeleteQTaskEvent(AnimQTask_eUpdateAnimDataEvent);
  QTask_DeleteQTaskEvent(AnimQTask_eRedrawAnimDataEvent);
  QTask_DeleteQTaskEvent(AnimQTask_eGetChannelDescriptionEvent);
  QTask_DeleteQTaskEvent(AnimQTask_eGetKeyframeSizeEvent);
  QTask_DeleteQTaskEvent(AnimQTask_eSaveKeyframeEvent);
  QTask_DeleteQTaskEvent(AnimQTask_eRestoreKeyframeEvent);
  QTask_DeleteQTaskEvent(AnimQTask_eReadChannelsEvent);
  AnimQTask_eUpdateAnimDataEvent = 512;
  AnimQTask_eRedrawAnimDataEvent = 512;
  AnimQTask_eGetChannelDescriptionEvent = 512;
  AnimQTask_eGetKeyframeSizeEvent = 512;
  AnimQTask_eSaveKeyframeEvent = 512;
  AnimQTask_eRestoreKeyframeEvent = 512;
}
