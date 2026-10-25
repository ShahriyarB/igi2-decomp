/* j/0/objects/terminal.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/objects/terminal.c:49  [size]
void __cdecl Terminal_GetSerializeParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = Terminal_ptSerializeParameterList;
}

// source: j/0/objects/terminal.c:67  [size]
void __cdecl Terminal_DeSerializeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ((void (__cdecl *)())QTask_aatQTaskFinalEvent[Serialize_eDeSerializeQTaskEvent][ExplodeObject_eQTaskType].pfHandler)(ptQTask, pxContext);
}

// source: j/0/objects/terminal.c:85  [anchor-caller]
void __cdecl Terminal_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  QTaskList_Register(GameFunctions_ptActivateQTaskList, (struct QTaskList_s *)ptQTask);
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][ExplodeObject_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  ExplodeObject_SetParameters(ptQTask, 1.0, 0.5, 0.5, 1.0, 0.0, 5, 4, "explo_02_m");
  ptQTask[15].tQTaskRefList.ptTail = (struct QReference_s *)1082130432;
  strcpy((char *)&ptQTask[15].ptParent, "tba_hackcomp");
  LOBYTE(ptQTask[18].tQTaskRefList.ptMiddle) = 0;
  BYTE1(ptQTask[18].tQTaskRefList.ptMiddle) = 0;
  ptQTask[18].tQTaskRefList.ptTail = nullptr;
  HIBYTE(ptQTask[18].eQTaskType) = 0;
  ptQTask[18].isInMemPool = 0;
  ptQTask[19].ptNext = nullptr;
  LOBYTE(ptQTask[15].tQTaskRefList.ptMiddle) = 0;
  ptQTask[18].ptParent = nullptr;
  ptQTask[19].ptPrev = nullptr;
  LOBYTE(ptQTask[18].eQTaskType) = 1;
  ptQTask[16].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[16].tQTaskRefList.ptTail = nullptr;
  ptQTask[16].ptParent = nullptr;
  ptQTask[18].tQTaskRefList.ptHead = nullptr;
}

// source: j/0/objects/terminal.c:146  [size]
void __cdecl Terminal_RunHandler(struct QTask_s *ptQTask)
{
  struct LevelFlow_s *v1; // eax

  if ( ptQTask[18].isInMemPool )
    ptQTask[18].isInMemPool = 0;
  if ( ptQTask[18].ptParent )
  {
    HIBYTE(ptQTask[18].eQTaskType) = 1;
    ptQTask[18].isInMemPool = 1;
    v1 = LevelFlow_ptLevelFlow;
    ptQTask[18].ptParent = nullptr;
    ptQTask[19].ptNext = (struct QTask_s *)v1->nTick;
  }
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][ExplodeObject_eQTaskType].pfHandler)(ptQTask);
  if ( LOBYTE(ptQTask[11].tQTaskChildren.ptTail) )
  {
    LOBYTE(ptQTask[18].eQTaskType) = 0;
  }
  else if ( ptQTask[16].tQTaskRefList.ptMiddle && ptQTask[16].tQTaskRefList.ptTail->ptNext && ptQTask[16].ptParent )
  {
    LOBYTE(ptQTask[18].eQTaskType) = (__int64)Level_RunLevelExpression(
                                                (struct LevelExpression_s *)&ptQTask[16].tQTaskRefList.ptMiddle,
                                                ptQTask);
  }
  if ( LevelFlow_ptLevelFlow->nTick <= (int)&ptQTask[18].tQTaskRefList.ptTail->ptNext + 2 )
  {
    BYTE1(ptQTask[18].tQTaskRefList.ptMiddle) = ptQTask[18].tQTaskRefList.ptMiddle;
  }
  else
  {
    LOBYTE(ptQTask[18].tQTaskRefList.ptMiddle) = 0;
    BYTE1(ptQTask[18].tQTaskRefList.ptMiddle) = 0;
  }
}

// source: j/0/objects/terminal.c:206  [anchor-mhash]
void __cdecl Terminal_DeleteHandler(struct QTask_s *ptQTask)
{
  int v1; // eax
  struct QReference_s *v2; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *); // eax

  QTaskList_Remove(GameFunctions_ptActivateQTaskList, ptQTask);
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[2][ExplodeObject_eQTaskType].pfHandler)(ptQTask);
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
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[16].tQTaskRefList.ptMiddle);
}

// source: j/0/objects/terminal.c:238  [size]
void __cdecl Terminal_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = Terminal_ptParameterList;
}

// source: j/0/objects/terminal.c:254  [size]
void __cdecl Terminal_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][ExplodeObject_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[16].tQTaskRefList.ptMiddle, ptQTask);
}

// source: j/0/objects/terminal.c:278  [size]
void __cdecl Terminal_RegisterScriptSymbolsHandler(struct QTask_s *ptQTask)
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

  if ( !LOBYTE(ptQTask[15].tQTaskRefList.ptMiddle) )
  {
    v1 = ExplodeObject_eQTaskType + 511 * Level_eRegisterLevelScriptSymbolsEvent;
    LOBYTE(ptQTask[15].tQTaskRefList.ptMiddle) = 1;
    ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[0][v1].pfHandler)(ptQTask);
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.isInUse", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      &ptQTask[18].tQTaskRefList.ptMiddle,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.isLastInUse", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      (char *)&ptQTask[18].tQTaskRefList.ptMiddle + 1,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.isActive", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      &ptQTask[18].eQTaskType,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.isHacked", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      (char *)&ptQTask[18].eQTaskType + 1,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.isHackedThisTick", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      &ptQTask[18].isInMemPool,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.nClientID", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int,
      &ptQTask[19].ptPrev,
      4,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
  }
}

// source: j/0/objects/terminal.c:329  [size]
void __cdecl Terminal_RemoveScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( LOBYTE(ptQTask[15].tQTaskRefList.ptMiddle) )
  {
    ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Level_eRemoveLevelScriptSymbolsEvent][ExplodeObject_eQTaskType].pfHandler)(ptQTask);
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    LOBYTE(ptQTask[15].tQTaskRefList.ptMiddle) = 0;
    sprintf(igi2_frame.zTemp, "%s.isInUse", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.isLastInUse", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.isActive", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.isHacked", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.isHackedThisTick", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.nClientID", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
  }
}

// source: j/0/objects/terminal.c:382  [anchor-caller]
void __cdecl Terminal_EvaluateActivateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real64x3_t tPos; };
    struct { char igi2_o1[24]; struct real64x3_t Real64x3_RotateInverse_tTemp; };
    char igi2_extent[48];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v2; // st7
  double v3; // st6
  double v4; // st5
  double vX; // st7

  if ( LOBYTE(ptQTask[18].eQTaskType) )
  {
    GameFunctions_GetMagicVertex(&igi2_frame.tPos, ptQTask, 1);
    v2 = *((double *)pxContext + 1) - igi2_frame.tPos.vX;
    v3 = *((double *)pxContext + 2) - igi2_frame.tPos.vY;
    v4 = *((double *)pxContext + 3) - igi2_frame.tPos.vZ;
    igi2_frame.Real64x3_RotateInverse_tTemp.vX = *(float *)&ptQTask[3].tQTaskRefList.ptTail * v4
                                    + *(float *)&ptQTask[3].tQTaskChildren.ptTail * v3
                                    + *(float *)&ptQTask[3].ptPrev * v2;
    if ( *(float *)&ptQTask[3].ptParent * v4
       + *(float *)&ptQTask[3].tQTaskRefList.ptHead * v3
       + *(float *)&ptQTask[3].tQTaskChildren.ptHead * v2 > 0.0 )
    {
      vX = igi2_frame.Real64x3_RotateInverse_tTemp.vX;
      if ( igi2_frame.Real64x3_RotateInverse_tTemp.vX < 0.0 )
        vX = -igi2_frame.Real64x3_RotateInverse_tTemp.vX;
      if ( vX < 3072.0 )
        GameFunctions_ResolveEvaluateActivate((struct EvaluateActivateContext_t *)pxContext, ptQTask, &igi2_frame.tPos);
    }
  }
}

// source: j/0/objects/terminal.c:428  [size]
void __cdecl Terminal_GetActivateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = 4;
}

// source: j/0/objects/terminal.c:445  [size]
void __cdecl Terminal_ActivateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct LevelFlow_s *v2; // ecx

  v2 = LevelFlow_ptLevelFlow;
  LOBYTE(ptQTask[18].tQTaskRefList.ptMiddle) = 1;
  ptQTask[18].tQTaskRefList.ptTail = (struct QReference_s *)v2->nTick;
}

// source: j/0/objects/terminal.c:477  [size]
unsigned __int16 __cdecl Terminal_GetQTaskType()
{
  return Terminal_eQTaskType;
}

// source: j/0/objects/terminal.c:492  [size]
struct ParameterList_s *__cdecl Terminal_GetParameterList()
{
  return Terminal_ptParameterList;
}

// source: j/0/objects/terminal.c:507  [size]
struct ParameterList_s *__cdecl Terminal_GetSerializeParameterList()
{
  return Terminal_ptSerializeParameterList;
}

// source: j/0/objects/terminal.c:522  [size]
struct real64x3_t *__cdecl Terminal_GetActivatePosAndOrientation(
        struct QTask_s *ptQTask,
        struct real64x3_t *ptPos,
        struct real32x9_t *ptOrientation)
{
  qmemcpy(ptOrientation, &ptQTask[3].ptPrev, sizeof(struct real32x9_t));
  return GameFunctions_GetMagicVertex(ptPos, ptQTask, 1);
}

// source: j/0/objects/terminal.c:545  [size]
float __cdecl Terminal_GetActivateTime(struct QTask_s *ptQTask)
{
  return *(float *)&ptQTask[15].tQTaskRefList.ptTail;
}

// source: j/0/objects/terminal.c:561  [size]
char *__cdecl Terminal_GetActivateSound(struct QTask_s *ptQTask)
{
  return (char *)&ptQTask[15].ptParent;
}

// source: j/0/objects/terminal.c:580  [size]
struct QTask_s *__cdecl Terminal_Hacked(struct QTask_s *ptQTask, int nClientID)
{
  ptQTask[18].ptParent = (struct QTask_s *)1;
  ptQTask[19].ptPrev = (struct QTask_s *)nClientID;
  return ptQTask;
}

// source: j/0/objects/terminal.c:598  [anchor-caller]
void __cdecl Terminal_Open()
{
  unsigned __int16 v0; // si
  unsigned __int16 v1; // si

  v0 = QTask_NewQTaskType("Terminal", 768, ExplodeObject_eQTaskType, 0, 0);
  Terminal_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, Terminal_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, Terminal_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, Terminal_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Terminal_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, Terminal_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eRegisterLevelScriptSymbolsEvent,
    Terminal_RegisterScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Level_eRemoveLevelScriptSymbolsEvent, Terminal_RemoveScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerFn(v0, GameFunctions_eEvaluateActivateQTaskEvent, Terminal_EvaluateActivateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    GameFunctions_eGetActivateQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Terminal_GetActivateHandler);
  QTask_LinkQTaskEventHandlerFn(v0, GameFunctions_eActivateQTaskEvent, Terminal_ActivateHandler);
  Terminal_ptParameterList = ParameterList_Derive(ExplodeObject_ptParameterList, 3);
  ParameterList_AddParameter(Terminal_ptParameterList, 0x298u, Level_eParameterTypeVarString, "Active", 7u, nullptr);
  ParameterList_AddParameter(Terminal_ptParameterList, 0x274u, Level_eParameterTypeReal32, "Hack Time (s)", 7u, nullptr);
  ParameterList_AddParameter(
    Terminal_ptParameterList,
    0x278u,
    Level_eParameterTypeString32,
    "Activate Sound",
    7u,
    nullptr);
  v1 = Terminal_eQTaskType;
  QTask_LinkQTaskEventHandlerFn(
    Terminal_eQTaskType,
    Serialize_eGetSerializeParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Terminal_GetSerializeParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    Serialize_eDeSerializeQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Terminal_DeSerializeHandler);
  Terminal_ptSerializeParameterList = ParameterList_Derive(ExplodeObject_ptSerializeParameterList, 7);
  ParameterList_AddParameter(
    Terminal_ptSerializeParameterList,
    0x2E8u,
    Level_eParameterTypebool8,
    "isInUse",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Terminal_ptSerializeParameterList,
    0x2E9u,
    Level_eParameterTypebool8,
    "isLastInUse",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Terminal_ptSerializeParameterList,
    0x2ECu,
    Level_eParameterTypeInt32,
    "nLastInUseTick",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Terminal_ptSerializeParameterList,
    0x2F4u,
    Level_eParameterTypebool8,
    "isActive",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Terminal_ptSerializeParameterList,
    0x2F5u,
    Level_eParameterTypebool8,
    "isHacked",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Terminal_ptSerializeParameterList,
    0x2F6u,
    Level_eParameterTypebool8,
    "isHackedThisTick",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Terminal_ptSerializeParameterList,
    0x2F8u,
    Level_eParameterTypeInt32,
    "nHackedThisFrameTick",
    7u,
    nullptr);
}

// source: j/0/objects/terminal.c:649  [size]
void __cdecl Terminal_Close()
{
  int v0; // esi
  int v1; // esi

  if ( Terminal_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&Terminal_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  if ( Terminal_ptSerializeParameterList )
  {
    v1 = *(_DWORD *)((unsigned int)&Terminal_ptSerializeParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
  QTask_DeleteQTaskType(Terminal_eQTaskType);
}
