/* j/0/objects/generictba.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/objects/generictba.c:50  [size]
void __cdecl GenericTBA_GetSerializeParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = GenericTBA_ptSerializeParameterList;
}

// source: j/0/objects/generictba.c:68  [size]
void __cdecl GenericTBA_DeSerializeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ((void (__cdecl *)())QTask_aatQTaskFinalEvent[Serialize_eDeSerializeQTaskEvent][ExplodeObject_eQTaskType].pfHandler)(ptQTask, pxContext);
}

// source: j/0/objects/generictba.c:85  [anchor-mhash]
void __cdecl GenericTBA_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  QTaskList_Register(GameFunctions_ptActivateQTaskList, (struct QTaskList_s *)ptQTask);
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][ExplodeObject_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  ExplodeObject_SetParameters(ptQTask, 1.0, 0.5, 0.5, 1.0, 0.0, 5, 4, "explo_02_m");
  ptQTask[14].tQTaskRefList.ptMiddle = nullptr;
  LOBYTE(ptQTask[16].tQTaskChildren.ptHead) = 0;
  BYTE1(ptQTask[16].tQTaskChildren.ptHead) = 0;
  *(_DWORD *)&ptQTask[17].eQTaskType = 1082130432;
  strcpy((char *)&ptQTask[17].ptNext + 1, "tba_codepad");
  ptQTask[18].ptNext = nullptr;
  BYTE1(ptQTask[20].tQTaskChildren.ptHead) = 0;
  BYTE2(ptQTask[20].tQTaskChildren.ptHead) = 0;
  ptQTask[20].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[20].tQTaskChildren.ptTail = nullptr;
  BYTE1(ptQTask[20].tQTaskRefList.ptHead) = 0;
  BYTE2(ptQTask[20].tQTaskRefList.ptHead) = 0;
  ptQTask[20].tQTaskRefList.ptMiddle = nullptr;
  LOBYTE(ptQTask[20].tQTaskChildren.ptHead) = 0;
  ptQTask[20].tQTaskRefList.ptTail = nullptr;
  ptQTask[15].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[15].tQTaskRefList.ptTail = nullptr;
  ptQTask[15].ptParent = nullptr;
  *(_DWORD *)&ptQTask[15].eQTaskType = 0;
  ptQTask[16].ptNext = nullptr;
  ptQTask[16].ptPrev = nullptr;
  LOBYTE(ptQTask[20].tQTaskRefList.ptHead) = 1;
  ptQTask[18].tQTaskChildren.ptHead = nullptr;
  ptQTask[18].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[18].tQTaskChildren.ptTail = nullptr;
  ptQTask[20].ptPrev = nullptr;
}

// source: j/0/objects/generictba.c:156  [anchor-mhash]
void __cdecl GenericTBA_RunHandler(struct QTask_s *ptQTask)
{
  struct LevelFlow_s *v1; // eax
  struct QTask_s *ptHead; // ecx
  int v3; // edx
  struct QTask_s *v4; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v6; // edx

  if ( BYTE2(ptQTask[20].tQTaskRefList.ptHead) )
    BYTE2(ptQTask[20].tQTaskRefList.ptHead) = 0;
  if ( ptQTask[20].tQTaskChildren.ptTail )
  {
    BYTE1(ptQTask[20].tQTaskRefList.ptHead) = 1;
    BYTE2(ptQTask[20].tQTaskRefList.ptHead) = 1;
    v1 = LevelFlow_ptLevelFlow;
    ptQTask[20].tQTaskChildren.ptTail = nullptr;
    ptQTask[20].tQTaskRefList.ptMiddle = (struct QReference_s *)v1->nTick;
  }
  if ( LOBYTE(ptQTask[16].tQTaskChildren.ptHead) )
  {
    ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][ExplodeObject_eQTaskType].pfHandler)(ptQTask);
  }
  else
  {
    if ( LOBYTE(ptQTask[11].tQTaskChildren.ptTail) )
    {
LABEL_23:
      LOBYTE(ptQTask[20].tQTaskRefList.ptHead) = 0;
      goto LABEL_24;
    }
    if ( BYTE1(ptQTask[20].tQTaskRefList.ptHead) )
    {
      ExplodeObject_SetExploded(ptQTask);
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
            pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][ptHead->eQTaskType].pfHandler;
            v6 = v3 + 1;
            QTask_nProtectedQTaskStackOffset = v6;
            if ( pfHandler )
            {
              pfHandler(ptHead);
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
  }
  if ( LOBYTE(ptQTask[11].tQTaskChildren.ptTail) )
    goto LABEL_23;
  if ( ptQTask[18].tQTaskChildren.ptHead
    && ptQTask[18].tQTaskChildren.ptMiddle->ptNext
    && ptQTask[18].tQTaskChildren.ptTail )
  {
    LOBYTE(ptQTask[20].tQTaskRefList.ptHead) = (__int64)Level_RunLevelExpression(
                                                          (struct LevelExpression_s *)&ptQTask[18].tQTaskChildren,
                                                          ptQTask);
  }
LABEL_24:
  if ( LevelFlow_ptLevelFlow->nTick <= (int)&ptQTask[20].tQTaskChildren.ptMiddle->ptNext + 2 )
  {
    BYTE2(ptQTask[20].tQTaskChildren.ptHead) = BYTE1(ptQTask[20].tQTaskChildren.ptHead);
  }
  else
  {
    BYTE1(ptQTask[20].tQTaskChildren.ptHead) = 0;
    BYTE2(ptQTask[20].tQTaskChildren.ptHead) = 0;
  }
}

// source: j/0/objects/generictba.c:227  [anchor-mhash]
void __cdecl GenericTBA_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptNext; // eax
  int v2; // esi
  int v3; // eax
  struct QReference_s *v4; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *); // eax

  ptNext = ptQTask[18].ptNext;
  if ( ptNext )
  {
    v2 = *(_DWORD *)((unsigned int)&ptNext[-1].eQTaskType & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v2);
    memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
    free((void *)v2);
    ptQTask[18].ptNext = nullptr;
  }
  QTaskList_Remove(GameFunctions_ptActivateQTaskList, ptQTask);
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[2][ExplodeObject_eQTaskType].pfHandler)(ptQTask);
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
      goto LABEL_11;
  }
  if ( v3 >= 0 )
  {
    pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Level_eRemoveLevelScriptSymbolsEvent][ptQTask->eQTaskType].pfHandler;
    if ( pfHandler )
      pfHandler(ptQTask);
  }
LABEL_11:
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[18].tQTaskChildren);
}

// source: j/0/objects/generictba.c:266  [size]
void __cdecl GenericTBA_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = GenericTBA_ptParameterList;
}

// source: j/0/objects/generictba.c:282  [size]
void __cdecl GenericTBA_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptNext; // ebp
  int v3; // edi
  struct StatusScreen_t *ptStatusScreen; // [esp+10h] [ebp-4h]

  ptStatusScreen = (struct StatusScreen_t *)StatusScreen_ptStatusScreenQTask;
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][ExplodeObject_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  ptNext = ptQTask[18].ptNext;
  v3 = 0;
  ptQTask[18].ptPrev = nullptr;
  if ( ptNext )
  {
    while ( strcmp((char *)ptNext, StatusScreen_azQSpriteActivateIconPointer[v3]) )
    {
      if ( ++v3 >= 21 )
        goto LABEL_6;
    }
    ptQTask[18].ptPrev = (struct QTask_s *)&ptStatusScreen->atQSpriteActivateIcon[v3];
  }
LABEL_6:
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[18].tQTaskChildren, ptQTask);
}

// source: j/0/objects/generictba.c:332  [size]
void __cdecl GenericTBA_RegisterScriptSymbolsHandler(struct QTask_s *ptQTask)
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

  if ( !LOBYTE(ptQTask[20].tQTaskChildren.ptHead) )
  {
    v1 = ExplodeObject_eQTaskType + 511 * Level_eRegisterLevelScriptSymbolsEvent;
    LOBYTE(ptQTask[20].tQTaskChildren.ptHead) = 1;
    ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[0][v1].pfHandler)(ptQTask);
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.isInUse", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      (char *)&ptQTask[20].tQTaskChildren.ptHead + 1,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.isLastInUse", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      (char *)&ptQTask[20].tQTaskChildren.ptHead + 2,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.isActive", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      &ptQTask[20].tQTaskRefList,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.isFinished", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      (char *)&ptQTask[20].tQTaskRefList.ptHead + 1,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.isFinishedThisTick", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      (char *)&ptQTask[20].tQTaskRefList.ptHead + 2,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.nClientID", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int,
      &ptQTask[20].tQTaskRefList.ptTail,
      4,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
  }
}

// source: j/0/objects/generictba.c:383  [size]
void __cdecl GenericTBA_RemoveScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( LOBYTE(ptQTask[20].tQTaskChildren.ptHead) )
  {
    ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Level_eRemoveLevelScriptSymbolsEvent][ExplodeObject_eQTaskType].pfHandler)(ptQTask);
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    LOBYTE(ptQTask[20].tQTaskChildren.ptHead) = 0;
    sprintf(igi2_frame.zTemp, "%s.isInUse", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.isLastInUse", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.isActive", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.isFinished", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.isFinishedThisTick", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.nClientID", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
  }
}

// source: j/0/objects/generictba.c:436  [anchor-mhash]
void __cdecl GenericTBA_EvaluateActivateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real64x3_t tPos; };
    struct { char igi2_o1[24]; struct real64x3_t tOffset; };
    char igi2_extent[52];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v2; // st7
  double v3; // st6
  double v4; // st4
  double v5; // st7

  if ( LOBYTE(ptQTask[20].tQTaskRefList.ptHead) )
  {
    GameFunctions_GetMagicVertex(&igi2_frame.tPos, ptQTask, 1);
    qmemcpy(&igi2_frame.tOffset, &ptQTask[15].tQTaskRefList.ptMiddle, sizeof(igi2_frame.tOffset));
    v2 = igi2_frame.tOffset.vX * 4096.0;
    v3 = igi2_frame.tOffset.vY * 4096.0;
    igi2_frame.tOffset.vX = *(float *)&ptQTask[3].tQTaskChildren.ptMiddle * (igi2_frame.tOffset.vZ * 4096.0)
               + *(float *)&ptQTask[3].ptPrev * (igi2_frame.tOffset.vX * 4096.0)
               + *(float *)&ptQTask[3].tQTaskChildren.ptHead * (igi2_frame.tOffset.vY * 4096.0);
    igi2_frame.tOffset.vY = *(float *)&ptQTask[3].tQTaskRefList.ptMiddle * (igi2_frame.tOffset.vZ * 4096.0)
               + *(float *)&ptQTask[3].tQTaskChildren.ptTail * v2
               + *(float *)&ptQTask[3].tQTaskRefList.ptHead * (igi2_frame.tOffset.vY * 4096.0);
    v4 = *(float *)&ptQTask[3].eQTaskType * (igi2_frame.tOffset.vZ * 4096.0)
       + *(float *)&ptQTask[3].tQTaskRefList.ptTail * v2
       + *(float *)&ptQTask[3].ptParent * v3;
    igi2_frame.tPos.vX = igi2_frame.tPos.vX + igi2_frame.tOffset.vX;
    igi2_frame.tPos.vY = igi2_frame.tPos.vY + igi2_frame.tOffset.vY;
    igi2_frame.tPos.vZ = igi2_frame.tPos.vZ + v4;
    igi2_frame.tOffset.vX = *((double *)pxContext + 1) - igi2_frame.tPos.vX;
    igi2_frame.tOffset.vY = *((double *)pxContext + 2) - igi2_frame.tPos.vY;
    igi2_frame.tOffset.vZ = *((double *)pxContext + 3) - igi2_frame.tPos.vZ;
    v5 = *(float *)&ptQTask[3].tQTaskRefList.ptTail * igi2_frame.tOffset.vZ
       + *(float *)&ptQTask[3].tQTaskChildren.ptTail * igi2_frame.tOffset.vY
       + *(float *)&ptQTask[3].ptPrev * igi2_frame.tOffset.vX;
    if ( *(float *)&ptQTask[3].ptParent * igi2_frame.tOffset.vZ
       + *(float *)&ptQTask[3].tQTaskRefList.ptHead * igi2_frame.tOffset.vY
       + *(float *)&ptQTask[3].tQTaskChildren.ptHead * igi2_frame.tOffset.vX > 0.0 )
    {
      if ( v5 < 0.0 )
        v5 = -v5;
      if ( v5 < 3072.0 )
        GameFunctions_ResolveEvaluateActivate((struct EvaluateActivateContext_t *)pxContext, ptQTask, &igi2_frame.tPos);
    }
  }
}

// source: j/0/objects/generictba.c:477  [size]
void __cdecl GenericTBA_GetActivateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = 10;
}

// source: j/0/objects/generictba.c:494  [size]
void __cdecl GenericTBA_ActivateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct LevelFlow_s *v2; // ecx

  v2 = LevelFlow_ptLevelFlow;
  BYTE1(ptQTask[20].tQTaskChildren.ptHead) = 1;
  ptQTask[20].tQTaskChildren.ptMiddle = (struct QTask_s *)v2->nTick;
}

// source: j/0/objects/generictba.c:524  [size]
void __cdecl GenericTBA_DrawActionItemHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ActionMenuScreen_DrawActionItem(ActionMenuScreen_ptQTask, (struct QSprite_s *)ptQTask[18].ptPrev, pxContext);
}

// source: j/0/objects/generictba.c:542  [size]
unsigned __int16 __cdecl GenericTBA_GetQTaskType()
{
  return GenericTBA_eQTaskType;
}

// source: j/0/objects/generictba.c:557  [size]
struct ParameterList_s *__cdecl GenericTBA_GetParameterList()
{
  return GenericTBA_ptParameterList;
}

// source: j/0/objects/generictba.c:572  [size]
struct real64x3_t *__cdecl GenericTBA_GetActivatePosAndOrientation(
        struct QTask_s *ptQTask,
        struct real64x3_t *ptPos,
        struct real32x9_t *ptOrientation)
{
  qmemcpy(ptOrientation, &ptQTask[3].ptPrev, sizeof(struct real32x9_t));
  return GameFunctions_GetMagicVertex(ptPos, ptQTask, 1);
}

// source: j/0/objects/generictba.c:598  [size]
float __cdecl GenericTBA_GetActivateTime(struct QTask_s *ptQTask)
{
  return *(float *)&ptQTask[17].eQTaskType;
}

// source: j/0/objects/generictba.c:617  [size]
char *__cdecl GenericTBA_GetActivateAnim(struct QTask_s *ptQTask)
{
  return (char *)&ptQTask[16].tQTaskChildren.ptHead + 1;
}

// source: j/0/objects/generictba.c:636  [size]
char *__cdecl GenericTBA_GetActivateSound(struct QTask_s *ptQTask)
{
  return (char *)&ptQTask[17].ptNext + 1;
}

// source: j/0/objects/generictba.c:655  [size]
struct QTask_s *__cdecl GenericTBA_SetFinished(struct QTask_s *ptQTask, int nNetworkID)
{
  ptQTask[20].tQTaskChildren.ptTail = (struct QTask_s *)1;
  ptQTask[20].tQTaskRefList.ptTail = (struct QReference_s *)nNetworkID;
  return ptQTask;
}

// source: j/0/objects/generictba.c:675  [anchor-strings]
void __cdecl GenericTBA_Open()
{
  unsigned __int16 v0; // si
  unsigned __int16 v1; // si

  dword_7529C0 = 21;
  unk_7529C4 = StatusScreen_azQSpriteActivateIconPointer;
  v0 = QTask_NewQTaskType("GenericTBA", 832, ExplodeObject_eQTaskType, 0, 0);
  GenericTBA_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, GenericTBA_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, GenericTBA_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, GenericTBA_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))GenericTBA_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, GenericTBA_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eRegisterLevelScriptSymbolsEvent,
    GenericTBA_RegisterScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eRemoveLevelScriptSymbolsEvent,
    GenericTBA_RemoveScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerFn(v0, GameFunctions_eEvaluateActivateQTaskEvent, GenericTBA_EvaluateActivateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    GameFunctions_eGetActivateQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))GenericTBA_GetActivateHandler);
  QTask_LinkQTaskEventHandlerFn(v0, GameFunctions_eActivateQTaskEvent, GenericTBA_ActivateHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ActionMenuScreen_eDrawActionItemQTaskEvent, GenericTBA_DrawActionItemHandler);
  GenericTBA_ptParameterList = ParameterList_Derive(ExplodeObject_ptParameterList, 9);
  ParameterList_AddParameterMinMax(
    GenericTBA_ptParameterList,
    0x270u,
    Level_eParameterTypeReal64,
    "Activate Offset X",
    7u,
    -20480.0,
    20480.0);
  ParameterList_AddParameterMinMax(
    GenericTBA_ptParameterList,
    0x278u,
    Level_eParameterTypeReal64,
    "Activate Offset Y",
    7u,
    -20480.0,
    20480.0);
  ParameterList_AddParameterMinMax(
    GenericTBA_ptParameterList,
    0x280u,
    Level_eParameterTypeReal64,
    "Activate Offset Z",
    7u,
    -20480.0,
    20480.0);
  ParameterList_AddParameter(GenericTBA_ptParameterList, 0x288u, Level_eParameterTypebool8, "Explodable", 7u, nullptr);
  ParameterList_AddParameter(GenericTBA_ptParameterList, 0x2D8u, Level_eParameterTypeVarString, "Active", 7u, nullptr);
  ParameterList_AddParameter(
    GenericTBA_ptParameterList,
    0x289u,
    Level_eParameterTypeString32,
    "Activate Anim",
    7u,
    nullptr);
  ParameterList_AddParameter(
    GenericTBA_ptParameterList,
    0x2CCu,
    Level_eParameterTypeReal32,
    "Activate Time (s)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    GenericTBA_ptParameterList,
    0x2D0u,
    Level_eParameterTypeDropDownCombo,
    "Click to select sprite",
    7u,
    &dword_7529C0);
  ParameterList_AddParameter(
    GenericTBA_ptParameterList,
    0x2A9u,
    Level_eParameterTypeString32,
    "Activate Sound",
    7u,
    nullptr);
  v1 = GenericTBA_eQTaskType;
  QTask_LinkQTaskEventHandlerFn(
    GenericTBA_eQTaskType,
    Serialize_eGetSerializeParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))GenericTBA_GetSerializeParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    Serialize_eDeSerializeQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))GenericTBA_DeSerializeHandler);
  GenericTBA_ptSerializeParameterList = ParameterList_Derive(ExplodeObject_ptSerializeParameterList, 7);
  ParameterList_AddParameter(
    GenericTBA_ptSerializeParameterList,
    0x329u,
    Level_eParameterTypebool8,
    "isInUse",
    7u,
    nullptr);
  ParameterList_AddParameter(
    GenericTBA_ptSerializeParameterList,
    0x32Au,
    Level_eParameterTypebool8,
    "isLastInUse",
    7u,
    nullptr);
  ParameterList_AddParameter(
    GenericTBA_ptSerializeParameterList,
    0x32Cu,
    Level_eParameterTypeInt32,
    "nLastInUseTick",
    7u,
    nullptr);
  ParameterList_AddParameter(
    GenericTBA_ptSerializeParameterList,
    0x334u,
    Level_eParameterTypebool8,
    "isActive",
    7u,
    nullptr);
  ParameterList_AddParameter(
    GenericTBA_ptSerializeParameterList,
    0x335u,
    Level_eParameterTypebool8,
    "isFinished",
    7u,
    nullptr);
  ParameterList_AddParameter(
    GenericTBA_ptSerializeParameterList,
    0x336u,
    Level_eParameterTypebool8,
    "isFinishedThisFrame",
    7u,
    nullptr);
  ParameterList_AddParameter(
    GenericTBA_ptSerializeParameterList,
    0x338u,
    Level_eParameterTypeInt32,
    "nFinishedThisFrameTick",
    7u,
    nullptr);
}

// source: j/0/objects/generictba.c:738  [size]
void __cdecl GenericTBA_Close()
{
  int v0; // esi
  int v1; // esi

  if ( GenericTBA_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&GenericTBA_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  if ( GenericTBA_ptSerializeParameterList )
  {
    v1 = *(_DWORD *)((unsigned int)&GenericTBA_ptSerializeParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
  QTask_DeleteQTaskType(GenericTBA_eQTaskType);
}
