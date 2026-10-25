/* j/0/sound/conditionalsound.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/sound/conditionalsound.c:86  [anchor-hash]
void __cdecl ConditionalSound_StopSound(struct ConditionalSound_s *ptConditionalSound)
{
  struct QReference_s *ptSoundQTaskRef; // eax
  struct QTask_s *pxObject; // eax

  ptSoundQTaskRef = ptConditionalSound->ptSoundQTaskRef;
  if ( ptSoundQTaskRef )
  {
    pxObject = (struct QTask_s *)ptSoundQTaskRef->pxObject;
    if ( pxObject )
      QTask_Delete(pxObject);
    QReference_Delete(ptConditionalSound->ptSoundQTaskRef, &QTask_tQTaskRefPool);
    ptConditionalSound->ptSoundQTaskRef = nullptr;
    ptConditionalSound->isPlaying = 0;
  }
}

// source: j/0/sound/conditionalsound.c:116  [anchor-callee]
void __cdecl ConditionalSound_PlaySound(struct ConditionalSound_s *ptConditionalSound)
{
  struct QReference_s *ptSoundQTaskRef; // eax
  struct QTask_s *pxObject; // eax
  char *zSoundDef; // eax
  unsigned int v4; // eax
  struct QTask_s *v5; // eax
  struct QTask_s *v6; // esi
  int eQTaskType; // edx
  int v8; // ecx
  struct real64x3_t *p_tPosition; // eax
  char v10; // [esp+Bh] [ebp-1h] BYREF

  ptSoundQTaskRef = ptConditionalSound->ptSoundQTaskRef;
  if ( ptSoundQTaskRef )
  {
    pxObject = (struct QTask_s *)ptSoundQTaskRef->pxObject;
    if ( pxObject )
      QTask_Delete(pxObject);
    QReference_Delete(ptConditionalSound->ptSoundQTaskRef, &QTask_tQTaskRefPool);
    ptConditionalSound->ptSoundQTaskRef = nullptr;
    ptConditionalSound->isPlaying = 0;
  }
  zSoundDef = ptConditionalSound->zSoundDef;
  if ( !ptConditionalSound->isPlaySimple )
  {
    v5 = SoundSys_NewSoundFn(&ptConditionalSound->tQTask, zSoundDef);
    v6 = v5;
    if ( !v5 )
      return;
    ptConditionalSound->ptSoundQTaskRef = QTask_NewQTaskRef(v5);
    eQTaskType = v6->eQTaskType;
    if ( ptConditionalSound->isRelativeToMicrophone )
    {
      v8 = SoundSys_eSetRelativeToMicrophoneQTaskEvent;
      v10 = 1;
      p_tPosition = (struct real64x3_t *)&v10;
    }
    else
    {
      v8 = SoundSys_eSetPositionQTaskEvent;
      p_tPosition = &ptConditionalSound->tPosition;
    }
    ((void (__cdecl *)(struct QTask_s *, struct real64x3_t *))QTask_aatQTaskFinalEvent[v8][eQTaskType].pfHandler)(
      v6,
      p_tPosition);
    goto LABEL_15;
  }
  SoundSys_InitRequest(&ptConditionalSound->tSoundRequest, zSoundDef, 1u);
  if ( SoundSys_isSoundDisabled )
  {
LABEL_15:
    ptConditionalSound->isPlayed = 1;
    ptConditionalSound->isPlaying = 1;
    return;
  }
  if ( !ptConditionalSound->tSoundRequest.nSoundID )
  {
    v4 = SoundSys_nCurrentID;
    ptConditionalSound->tSoundRequest.nSoundID = SoundSys_nCurrentID;
    SoundSys_nCurrentID = v4 + 1;
  }
  SoundSys_AddSoundToRequestlist(
    ptConditionalSound->tSoundRequest.nSoundID,
    ptConditionalSound->tSoundRequest.ptSample,
    ptConditionalSound->tSoundRequest.bFlags,
    &ptConditionalSound->tSoundRequest.tModify);
  ptConditionalSound->isPlayed = 1;
  ptConditionalSound->isPlaying = 1;
}

// source: j/0/sound/conditionalsound.c:162  [size]
void __cdecl ConditionalSound_MaintainSound(struct ConditionalSound_s *ptConditionalSound)
{
  char v1; // al
  struct QReference_s *ptSoundQTaskRef; // eax

  if ( ptConditionalSound->isPlaySimple )
  {
    v1 = SoundSys_SoundPlaying(&ptConditionalSound->tSoundRequest);
    ptConditionalSound->isPlaying = v1;
    if ( v1 )
      SoundSys_RequestSoundFn(&ptConditionalSound->tSoundRequest);
  }
  else
  {
    ptSoundQTaskRef = ptConditionalSound->ptSoundQTaskRef;
    if ( ptSoundQTaskRef )
      ptConditionalSound->isPlaying = ptSoundQTaskRef->pxObject != nullptr;
  }
}

// source: j/0/sound/conditionalsound.c:199  [size]
void __cdecl ConditionalSound_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[1].ptNext = nullptr;
  ptQTask[1].ptPrev = nullptr;
  ptQTask[1].tQTaskChildren.ptHead = nullptr;
  *(_DWORD *)&ptQTask[2].eQTaskType = 0;
  ptQTask[3].ptParent = nullptr;
  *(_DWORD *)&ptQTask[3].eQTaskType = 0;
  ptQTask[4].ptNext = nullptr;
  ptQTask[4].ptPrev = nullptr;
  ptQTask[4].tQTaskChildren.ptHead = nullptr;
  ptQTask[4].tQTaskChildren.ptMiddle = nullptr;
  LOBYTE(ptQTask[3].ptNext) = 0;
  LOBYTE(ptQTask[4].tQTaskChildren.ptTail) = 0;
  BYTE1(ptQTask[4].tQTaskChildren.ptTail) = 0;
  LOBYTE(ptQTask[4].tQTaskRefList.ptMiddle) = 0;
  BYTE1(ptQTask[4].tQTaskRefList.ptMiddle) = 0;
  BYTE2(ptQTask[4].tQTaskRefList.ptMiddle) = 0;
  LOBYTE(ptQTask[4].tQTaskRefList.ptTail) = 0;
  HIBYTE(ptQTask[4].tQTaskRefList.ptMiddle) = 0;
  ptQTask[4].tQTaskRefList.ptHead = (struct QReference_s *)-1;
  ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
  LOBYTE(ptQTask[7].tQTaskRefList.ptTail) = 0;
}

// source: j/0/sound/conditionalsound.c:234  [anchor-caller]
void __cdecl ConditionalSound_RunHandler(struct QTask_s *ptQTask)
{
  char v1; // al
  struct QReference_s *ptMiddle; // eax
  struct QTask_s *ptHead; // ecx
  int v4; // edx
  struct QTask_s *v5; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v7; // edx

  if ( ptQTask[1].ptNext && ptQTask[1].ptPrev->ptNext && ptQTask[1].tQTaskChildren.ptHead )
  {
    BYTE1(ptQTask[4].tQTaskRefList.ptMiddle) = ptQTask[4].tQTaskRefList.ptMiddle;
    LOBYTE(ptQTask[4].tQTaskRefList.ptMiddle) = (__int64)Level_RunLevelExpression(
                                                           (struct LevelExpression_s *)&ptQTask[1],
                                                           ptQTask);
  }
  if ( LOBYTE(ptQTask[4].tQTaskChildren.ptTail) )
  {
    v1 = SoundSys_SoundPlaying((struct SoundSysRequest_s *)&ptQTask[4].ptParent);
    BYTE2(ptQTask[4].tQTaskRefList.ptMiddle) = v1;
    if ( v1 )
      SoundSys_RequestSoundFn((struct SoundSysRequest_s *)&ptQTask[4].ptParent);
  }
  else
  {
    ptMiddle = ptQTask[7].tQTaskRefList.ptMiddle;
    if ( ptMiddle )
      BYTE2(ptQTask[4].tQTaskRefList.ptMiddle) = ptMiddle->pxObject != nullptr;
  }
  if ( !BYTE1(ptQTask[4].tQTaskChildren.ptTail) || !LOBYTE(ptQTask[7].tQTaskRefList.ptTail) )
  {
    if ( LOBYTE(ptQTask[4].tQTaskRefList.ptMiddle) )
    {
      if ( !BYTE1(ptQTask[4].tQTaskRefList.ptMiddle) )
        ConditionalSound_PlaySound((struct ConditionalSound_s *)ptQTask);
    }
    else
    {
      ConditionalSound_StopSound((struct ConditionalSound_s *)ptQTask);
    }
    ptHead = ptQTask->tQTaskChildren.ptHead;
    if ( ptHead->ptNext && ptHead )
    {
      v4 = QTask_nProtectedQTaskStackOffset;
      do
      {
        if ( ptHead->ptNext )
          v5 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
        else
          v5 = nullptr;
        QTask_atProtectedQTaskStack[v4].ptQTask = v5;
        pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][ptHead->eQTaskType].pfHandler;
        v7 = v4 + 1;
        QTask_nProtectedQTaskStackOffset = v7;
        if ( pfHandler )
        {
          pfHandler(ptHead);
          v7 = QTask_nProtectedQTaskStackOffset;
        }
        ptHead = (struct QTask_s *)dword_849C7DC[v7];
        v4 = v7 - 1;
        QTask_nProtectedQTaskStackOffset = v4;
      }
      while ( ptHead );
    }
  }
}

// source: j/0/sound/conditionalsound.c:277  [anchor-mhash]
void __cdecl ConditionalSound_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QReference_s *ptMiddle; // eax
  struct QTask_s *pxObject; // eax
  int v3; // ecx
  struct QReference_s *v4; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax

  ptMiddle = ptQTask[7].tQTaskRefList.ptMiddle;
  if ( ptMiddle )
  {
    pxObject = (struct QTask_s *)ptMiddle->pxObject;
    if ( pxObject )
      QTask_Delete(pxObject);
    QReference_Delete(ptQTask[7].tQTaskRefList.ptMiddle, &QTask_tQTaskRefPool);
    ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
    BYTE2(ptQTask[4].tQTaskRefList.ptMiddle) = 0;
  }
  v3 = 0;
  while ( 1 )
  {
    v4 = Level_atLevelQTaskID[v3];
    if ( v4 )
    {
      if ( v4->pxObject == ptQTask )
        break;
    }
    if ( ++v3 >= 4096 )
      goto LABEL_13;
  }
  if ( v3 >= 0 )
  {
    pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Level_eRemoveLevelScriptSymbolsEvent][ptQTask->eQTaskType].pfHandler;
    if ( pfHandler )
      pfHandler(ptQTask);
  }
LABEL_13:
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[1]);
}

// source: j/0/sound/conditionalsound.c:302  [size]
void __cdecl ConditionalSound_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = ConditionalSound_ptParameterList;
}

// source: j/0/sound/conditionalsound.c:318  [size]
void __cdecl ConditionalSound_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[1], ptQTask);
}

// source: j/0/sound/conditionalsound.c:335  [size]
void __cdecl ConditionalSound_RegisterScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( !LOBYTE(ptQTask[4].tQTaskRefList.ptTail) )
  {
    LOBYTE(ptQTask[4].tQTaskRefList.ptTail) = 1;
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.isRun", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      &ptQTask[4].tQTaskRefList.ptMiddle,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.isLastRun", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      (char *)&ptQTask[4].tQTaskRefList.ptMiddle + 1,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.isPlaying", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      (char *)&ptQTask[4].tQTaskRefList.ptMiddle + 2,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.nPlayTick", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int,
      &ptQTask[4].tQTaskRefList,
      4,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
  }
}

// source: j/0/sound/conditionalsound.c:371  [size]
void __cdecl ConditionalSound_RemoveScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( LOBYTE(ptQTask[4].tQTaskRefList.ptTail) )
  {
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    LOBYTE(ptQTask[4].tQTaskRefList.ptTail) = 0;
    sprintf(igi2_frame.zTemp, "%s.isRun", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.isLastRun", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.isPlaying", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.nPlayTick", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
  }
}

// source: j/0/sound/conditionalsound.c:409  [anchor-mhash]
void __cdecl ConditionalSound_RemoveHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QReference_s *ptMiddle; // eax
  struct QTask_s *pxObject; // eax

  ptMiddle = ptQTask[7].tQTaskRefList.ptMiddle;
  if ( ptMiddle )
  {
    pxObject = (struct QTask_s *)ptMiddle->pxObject;
    if ( pxObject )
      QTask_Delete(pxObject);
    QReference_Delete(ptQTask[7].tQTaskRefList.ptMiddle, &QTask_tQTaskRefPool);
    ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
    BYTE2(ptQTask[4].tQTaskRefList.ptMiddle) = 0;
  }
  LOBYTE(ptQTask[4].tQTaskRefList.ptMiddle) = 0;
  BYTE1(ptQTask[4].tQTaskRefList.ptMiddle) = 0;
}

// source: j/0/sound/conditionalsound.c:430  [anchor-hash]
void __cdecl ConditionalSound_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si
  struct ParameterList_s *v2; // eax

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("ConditionalSound", 312, BaseQTaskType, 0, 0);
  ConditionalSound_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(
    v1,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 0, (void (__cdecl *)(struct QTask_s *, void *))ConditionalSound_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, ConditionalSound_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, ConditionalSound_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))ConditionalSound_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eUpdateInternalDataQTaskEvent,
    ConditionalSound_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v1,
    Level_eRegisterLevelScriptSymbolsEvent,
    ConditionalSound_RegisterScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v1,
    Level_eRemoveLevelScriptSymbolsEvent,
    ConditionalSound_RemoveScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerFn(v1, DynCubeObj_eDynCubeObjRemoveQTaskEvent, ConditionalSound_RemoveHandler);
  v2 = (struct ParameterList_s *)Mem_AllocFn(132, 4);
  v2->nParameters = 0;
  v2->nMaxParameters = 6;
  v2->ptParameterListItem = (struct ParameterListItem_s *)&v2[1];
  ConditionalSound_ptParameterList = v2;
  ParameterList_AddParameter(v2, 0x28u, Level_eParameterTypeVarString, "Condition", 7u, nullptr);
  ParameterList_AddParameter(
    ConditionalSound_ptParameterList,
    0x78u,
    Level_eParameterTypeString32,
    "SoundDef",
    7u,
    nullptr);
  ParameterList_AddParameter(
    ConditionalSound_ptParameterList,
    0x98u,
    Level_eParameterTypeObjectPos,
    "Position",
    7u,
    nullptr);
  ParameterList_AddParameter(ConditionalSound_ptParameterList, 0xB0u, Level_eParameterTypebool8, "Simple", 7u, nullptr);
  ParameterList_AddParameter(ConditionalSound_ptParameterList, 0xB1u, Level_eParameterTypebool8, "OneShot", 7u, nullptr);
  ParameterList_AddParameter(
    ConditionalSound_ptParameterList,
    0xBBu,
    Level_eParameterTypebool8,
    "Relative to microphone",
    7u,
    nullptr);
}

// source: j/0/sound/conditionalsound.c:469  [size]
void __cdecl ConditionalSound_Close()
{
  int v0; // esi

  QTask_DeleteQTaskType(ConditionalSound_eQTaskType);
  if ( ConditionalSound_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&ConditionalSound_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
}

// source: j/0/sound/conditionalsound.c:486  [size]
unsigned __int16 __cdecl ConditionalSound_GetQTaskType()
{
  return ConditionalSound_eQTaskType;
}
