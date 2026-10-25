/* j/0/objects/scameracontrol.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/objects/scameracontrol.c:70  [size]
void __cdecl SCameraControl_GetSerializeParameterListHandler(
        struct QTask_s *ptQTask,
        void *pxContext)
{
  *(_DWORD *)pxContext = SCameraControl_ptSerializeParameterList;
}

// source: j/0/objects/scameracontrol.c:89  [anchor-mhash]
void __cdecl SCameraControl_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][Terminal_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  LOBYTE(ptQTask[19].tQTaskChildren.ptHead) = 0;
  BYTE1(ptQTask[19].tQTaskChildren.ptHead) = 0;
  ptQTask[19].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[19].tQTaskChildren.ptTail = nullptr;
  ptQTask[19].tQTaskRefList.ptHead = nullptr;
  ptQTask[21].tQTaskChildren.ptHead = nullptr;
}

// source: j/0/objects/scameracontrol.c:118  [anchor-mhash]
void __cdecl SCameraControl_RunHandler(struct QTask_s *ptQTask)
{
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][Terminal_eQTaskType].pfHandler)(ptQTask);
  if ( LOBYTE(ptQTask[11].tQTaskChildren.ptTail) )
  {
    LOBYTE(ptQTask[19].tQTaskChildren.ptHead) = 0;
  }
  else if ( ptQTask[19].tQTaskChildren.ptMiddle && ptQTask[19].tQTaskChildren.ptTail->ptNext )
  {
    if ( ptQTask[19].tQTaskRefList.ptHead )
      LOBYTE(ptQTask[19].tQTaskChildren.ptHead) = (__int64)Level_RunLevelExpression(
                                                             (struct LevelExpression_s *)&ptQTask[19].tQTaskChildren.ptMiddle,
                                                             ptQTask);
  }
}

// source: j/0/objects/scameracontrol.c:152  [anchor-mhash]
void __cdecl SCameraControl_DeleteHandler(struct QTask_s *ptQTask)
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
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[19].tQTaskChildren.ptMiddle);
}

// source: j/0/objects/scameracontrol.c:181  [size]
void __cdecl SCameraControl_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = SCameraControl_ptParameterList;
}

// source: j/0/objects/scameracontrol.c:197  [size]
void __cdecl SCameraControl_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][Terminal_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[19].tQTaskChildren.ptMiddle, ptQTask);
}

// source: j/0/objects/scameracontrol.c:221  [size]
void __cdecl SCameraControl_RegisterScriptSymbolsHandler(struct QTask_s *ptQTask)
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

  if ( !BYTE1(ptQTask[19].tQTaskChildren.ptHead) )
  {
    v1 = Terminal_eQTaskType + 511 * Level_eRegisterLevelScriptSymbolsEvent;
    BYTE1(ptQTask[19].tQTaskChildren.ptHead) = 1;
    ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[0][v1].pfHandler)(ptQTask);
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.isDetection", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      &ptQTask[19].tQTaskChildren,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
  }
}

// source: j/0/objects/scameracontrol.c:257  [anchor-mhash]
void __cdecl SCameraControl_RemoveScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( BYTE1(ptQTask[19].tQTaskChildren.ptHead) )
  {
    ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Level_eRemoveLevelScriptSymbolsEvent][Terminal_eQTaskType].pfHandler)(ptQTask);
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    BYTE1(ptQTask[19].tQTaskChildren.ptHead) = 0;
    sprintf(igi2_frame.zTemp, "%s.isDetection", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
  }
}

// source: j/0/objects/scameracontrol.c:297  [anchor-strings]
void __cdecl SCameraControl_Open()
{
  unsigned __int16 v0; // si

  v0 = QTask_NewQTaskType("SCameraControl", 856, Terminal_eQTaskType, 0, 0);
  SCameraControl_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, SCameraControl_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, SCameraControl_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, SCameraControl_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))SCameraControl_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eUpdateInternalDataQTaskEvent,
    SCameraControl_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eRegisterLevelScriptSymbolsEvent,
    SCameraControl_RegisterScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eRemoveLevelScriptSymbolsEvent,
    SCameraControl_RemoveScriptSymbolsHandler);
  SCameraControl_ptParameterList = ParameterList_Derive(Terminal_ptParameterList, 1);
  ParameterList_AddParameter(
    SCameraControl_ptParameterList,
    0x304u,
    Level_eParameterTypeVarString,
    "Detection Expression",
    7u,
    nullptr);
  QTask_LinkQTaskEventHandlerFn(
    SCameraControl_eQTaskType,
    Serialize_eGetSerializeParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))SCameraControl_GetSerializeParameterListHandler);
  SCameraControl_ptSerializeParameterList = ParameterList_Derive(Terminal_ptSerializeParameterList, 1);
  ParameterList_AddParameter(
    SCameraControl_ptSerializeParameterList,
    0x300u,
    Level_eParameterTypebool8,
    "isDetection",
    7u,
    nullptr);
}

// source: j/0/objects/scameracontrol.c:335  [size]
void __cdecl SCameraControl_Close()
{
  int v0; // esi
  int v1; // esi

  if ( SCameraControl_ptSerializeParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&SCameraControl_ptSerializeParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  if ( SCameraControl_ptParameterList )
  {
    v1 = *(_DWORD *)((unsigned int)&SCameraControl_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
  QTask_DeleteQTaskType(SCameraControl_eQTaskType);
}
