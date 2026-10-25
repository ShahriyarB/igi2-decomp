/* j/0/objects/alarmcontrol.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/objects/alarmcontrol.c:78  [size]
void __cdecl AlarmControl_GetSerializeParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = AlarmControl_ptSerializeParameterList;
}

// source: j/0/objects/alarmcontrol.c:94  [anchor-mhash]
void __cdecl AlarmControl_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][Terminal_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  ptQTask[19].tQTaskChildren.ptHead = nullptr;
  ptQTask[19].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[19].tQTaskChildren.ptTail = nullptr;
  ptQTask[19].tQTaskRefList.ptHead = (struct QReference_s *)-10000;
  ptQTask[19].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[19].tQTaskRefList.ptTail = nullptr;
  ptQTask[19].ptParent = nullptr;
  *(_DWORD *)&ptQTask[19].eQTaskType = 0;
  ptQTask[21].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[21].tQTaskRefList.ptTail = nullptr;
  ptQTask[21].ptParent = nullptr;
  *(_DWORD *)&ptQTask[21].eQTaskType = 0;
  ptQTask[23].tQTaskRefList.ptMiddle = nullptr;
  dword_834DED8 = (int)ptQTask;
}

// source: j/0/objects/alarmcontrol.c:127  [anchor-mhash]
void __cdecl AlarmControl_RunHandler(struct QTask_s *ptQTask)
{
  char ptTail; // al
  struct QTask_s *ptMiddle; // edi
  struct QTask_s *v3; // eax
  struct HumanAIEventContext_t tEventContext; // [esp+18h] [ebp-40h] BYREF

  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][Terminal_eQTaskType].pfHandler)(ptQTask);
  ptTail = (char)ptQTask[11].tQTaskChildren.ptTail;
  ptMiddle = ptQTask[19].tQTaskChildren.ptMiddle;
  ptQTask[19].tQTaskChildren.ptTail = ptMiddle;
  if ( ptTail || !LOBYTE(ptQTask[18].eQTaskType) )
  {
    ptQTask[19].tQTaskChildren.ptHead = nullptr;
    ptQTask[19].tQTaskChildren.ptMiddle = nullptr;
  }
  else
  {
    if ( ptQTask[19].tQTaskRefList.ptTail && ptQTask[19].ptParent->ptNext && *(_DWORD *)&ptQTask[19].eQTaskType )
      ptQTask[19].tQTaskChildren.ptHead = (struct QTask_s *)(char)(__int64)Level_RunLevelExpression(
                                                                             (struct LevelExpression_s *)&ptQTask[19].tQTaskRefList.ptTail,
                                                                             ptQTask);
    if ( ptQTask[19].tQTaskChildren.ptHead )
      ptQTask[19].tQTaskRefList.ptHead = (struct QReference_s *)Level_ptQLevelQTask->nTicks;
    if ( ptQTask[21].tQTaskRefList.ptTail && ptQTask[21].ptParent->ptNext && *(_DWORD *)&ptQTask[21].eQTaskType )
      ptQTask[19].tQTaskChildren.ptMiddle = (struct QTask_s *)(char)(__int64)Level_RunLevelExpression(
                                                                               (struct LevelExpression_s *)&ptQTask[21].tQTaskRefList.ptTail,
                                                                               ptQTask);
    v3 = ptQTask[19].tQTaskChildren.ptMiddle;
    if ( ptMiddle )
    {
      if ( !v3 )
      {
        memset(&tEventContext.bFlags, 0, 12);
        tEventContext.ptHumanOriginatorQTask = nullptr;
        tEventContext.ptReferenceQTask = nullptr;
        tEventContext.eEvent = 8;
        tEventContext.eTeam = -1;
        HumanAI_SendEvent(&tEventContext);
      }
    }
    else if ( v3 )
    {
      memset(&tEventContext.bFlags, 0, 12);
      tEventContext.ptHumanOriginatorQTask = nullptr;
      tEventContext.ptReferenceQTask = nullptr;
      tEventContext.eEvent = 7;
      tEventContext.eTeam = -1;
      HumanAI_SendEvent(&tEventContext);
      if ( Level_atLevelQTaskID[0] )
        ++*((_DWORD *)Level_atLevelQTaskID[0]->pxObject + 126);
      else
        ++MEMORY[0x1F8];
    }
  }
}

// source: j/0/objects/alarmcontrol.c:218  [anchor-mhash]
void __cdecl AlarmControl_DeleteHandler(struct QTask_s *ptQTask)
{
  int v1; // eax
  struct QReference_s *v2; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *); // eax

  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[2][Terminal_eQTaskType].pfHandler)(ptQTask);
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
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[19].tQTaskRefList.ptTail);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[21].tQTaskRefList.ptTail);
  dword_834DED8 = 0;
}

// source: j/0/objects/alarmcontrol.c:248  [size]
void __cdecl AlarmControl_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = AlarmControl_ptParameterList;
}

// source: j/0/objects/alarmcontrol.c:264  [anchor-mhash]
void __cdecl AlarmControl_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][Terminal_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[19].tQTaskRefList.ptTail, ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[21].tQTaskRefList.ptTail, ptQTask);
}

// source: j/0/objects/alarmcontrol.c:289  [anchor-mhash]
void __cdecl AlarmControl_RegisterScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v1; // eax

  if ( !ptQTask[19].tQTaskRefList.ptMiddle )
  {
    v1 = Terminal_eQTaskType + 511 * Level_eRegisterLevelScriptSymbolsEvent;
    ptQTask[19].tQTaskRefList.ptMiddle = (struct QReference_s *)1;
    ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[0][v1].pfHandler)(ptQTask);
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.isTrigger", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int,
      &ptQTask[19].tQTaskChildren,
      4,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.isAlarm", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int,
      &ptQTask[19].tQTaskChildren.ptMiddle,
      4,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.nTriggerLastTick", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int,
      &ptQTask[19].tQTaskRefList,
      4,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
  }
}

// source: j/0/objects/alarmcontrol.c:331  [anchor-mhash]
void __cdecl AlarmControl_RemoveScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( ptQTask[19].tQTaskRefList.ptMiddle )
  {
    ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Level_eRemoveLevelScriptSymbolsEvent][Terminal_eQTaskType].pfHandler)(ptQTask);
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    ptQTask[19].tQTaskRefList.ptMiddle = nullptr;
    sprintf(igi2_frame.zTemp, "%s.isTrigger", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.isAlarm", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.nTriggerLastTick", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
  }
}

// source: j/0/objects/alarmcontrol.c:377  [size]
int __cdecl AlarmControl_GetAlarm(struct QTask_s *ptAlarmControlQTask)
{
  return (int)ptAlarmControlQTask[19].tQTaskChildren.ptMiddle;
}

// source: j/0/objects/alarmcontrol.c:395  [size]
int __cdecl AlarmControl_GetLastAlarm(struct QTask_s *ptAlarmControlQTask)
{
  return (int)ptAlarmControlQTask[19].tQTaskChildren.ptTail;
}

// source: j/0/objects/alarmcontrol.c:413  [anchor-strings]
void __cdecl AlarmControl_Open()
{
  unsigned __int16 v0; // si

  v0 = QTask_NewQTaskType("AlarmControl", 952, Terminal_eQTaskType, 0, 0);
  AlarmControl_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, AlarmControl_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, AlarmControl_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, AlarmControl_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))AlarmControl_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, AlarmControl_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eRegisterLevelScriptSymbolsEvent,
    AlarmControl_RegisterScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eRemoveLevelScriptSymbolsEvent,
    AlarmControl_RemoveScriptSymbolsHandler);
  AlarmControl_ptParameterList = ParameterList_Derive(Terminal_ptParameterList, 2);
  ParameterList_AddParameter(
    AlarmControl_ptParameterList,
    0x314u,
    Level_eParameterTypeVarString,
    "Trigger Expression",
    7u,
    nullptr);
  ParameterList_AddParameter(
    AlarmControl_ptParameterList,
    0x364u,
    Level_eParameterTypeVarString,
    "Alarm Expression",
    7u,
    nullptr);
  QTask_LinkQTaskEventHandlerFn(
    AlarmControl_eQTaskType,
    Serialize_eGetSerializeParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))AlarmControl_GetSerializeParameterListHandler);
  AlarmControl_ptSerializeParameterList = ParameterList_Derive(Terminal_ptSerializeParameterList, 4);
  ParameterList_AddParameter(
    AlarmControl_ptSerializeParameterList,
    0x300u,
    Level_eParameterTypeInt32,
    "isTrigger",
    7u,
    nullptr);
  ParameterList_AddParameter(
    AlarmControl_ptSerializeParameterList,
    0x304u,
    Level_eParameterTypeInt32,
    "isAlarm",
    7u,
    nullptr);
  ParameterList_AddParameter(
    AlarmControl_ptSerializeParameterList,
    0x308u,
    Level_eParameterTypeInt32,
    "isLastAlarm",
    7u,
    nullptr);
  ParameterList_AddParameter(
    AlarmControl_ptSerializeParameterList,
    0x30Cu,
    Level_eParameterTypeInt32,
    "nTriggerLastTick",
    7u,
    nullptr);
}

// source: j/0/objects/alarmcontrol.c:455  [size]
void __cdecl AlarmControl_Close()
{
  int v0; // esi
  int v1; // esi

  if ( AlarmControl_ptSerializeParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&AlarmControl_ptSerializeParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  if ( AlarmControl_ptParameterList )
  {
    v1 = *(_DWORD *)((unsigned int)&AlarmControl_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
  QTask_DeleteQTaskType(AlarmControl_eQTaskType);
}

int sub_4DB760()
{
  return dword_834DED8;
}
