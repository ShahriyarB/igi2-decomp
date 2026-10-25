/* j/0/pickups/genericpickup.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/pickups/genericpickup.c:79  [anchor-mhash]
struct QTask_s *__cdecl GenericPickup_Unregister(struct QTask_s *ptQTask)
{
  struct QTask_s *result; // eax
  struct Game_s *v3; // ebx
  struct QTask_s *ptHead; // ecx
  int v5; // edx
  struct QTask_s *v6; // eax
  int v7; // edx
  struct DynCubeObjRemoveObjContext_s tRemoveContext; // [esp+4h] [ebp-4h] BYREF

  result = ptQTask[2].tQTaskChildren.ptHead;
  if ( result )
  {
    SectorObject_RemoveInteriorDynCubeObj((struct DynCubeObj_s *)ptQTask);
    v3 = Game_ptGame;
    World_RemoveDynCubeObj(Game_ptGame->ptWorld, (struct DynCubeObj_s *)ptQTask);
    QTaskList_Remove(GameFunctions_ptPickupQTaskList, ptQTask);
    result = (struct QTask_s *)v3->ptWorld;
    ptHead = ptQTask->tQTaskChildren.ptHead;
    tRemoveContext.ptWorld = (struct World_s *)result;
    if ( ptHead->ptNext )
    {
      if ( ptHead )
      {
        v5 = QTask_nProtectedQTaskStackOffset;
        do
        {
          if ( ptHead->ptNext )
            v6 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
          else
            v6 = nullptr;
          QTask_atProtectedQTaskStack[v5].ptQTask = v6;
          result = (struct QTask_s *)QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRemoveQTaskEvent][ptHead->eQTaskType].pfHandler;
          v7 = v5 + 1;
          QTask_nProtectedQTaskStackOffset = v7;
          if ( result )
          {
            result = (struct QTask_s *)((int (__cdecl *)(struct QTask_s *, struct DynCubeObjRemoveObjContext_s *))result)(
                                         ptHead,
                                         &tRemoveContext);
            v7 = QTask_nProtectedQTaskStackOffset;
          }
          ptHead = (struct QTask_s *)dword_849C7DC[v7];
          v5 = v7 - 1;
          QTask_nProtectedQTaskStackOffset = v5;
        }
        while ( ptHead );
      }
    }
  }
  return result;
}

// source: j/0/pickups/genericpickup.c:109  [anchor-mhash]
struct QTask_s *__cdecl GenericPickup_Register(struct QTask_s *ptQTask)
{
  struct QTask_s *result; // eax
  double v3; // st7
  double v4; // st7
  int *v5; // eax
  int v6; // eax
  double v7; // st6
  float ptDynCubeObj; // [esp+0h] [ebp-14h]

  result = ptQTask[2].tQTaskChildren.ptHead;
  if ( !result )
  {
    QTaskList_Register(GameFunctions_ptPickupQTaskList, (struct QTaskList_s *)ptQTask);
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
      v3 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v3 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
    if ( v3 >= *(float *)&ptQTask[6].ptPrev )
    {
      if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
        v4 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
      else
        v4 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
    }
    else
    {
      v4 = *(float *)&ptQTask[6].ptPrev;
    }
    v5 = *(int **)&ptQTask[2].eQTaskType;
    if ( v5 && (v6 = *v5) != 0 )
      v7 = *(float *)(*(_DWORD *)(*(_DWORD *)(v6 + 12) + 12) + 120);
    else
      v7 = 1.0;
    ptDynCubeObj = v4 * v7;
    World_RegisterDynCubeObjFirstTimeRadius(
      Game_ptGame->ptWorld,
      (struct DynCubeObj_s *)ptQTask,
      (struct real64x3_t *)&ptQTask[1],
      ptDynCubeObj,
      WORLD_DYNCUBETREE_CATEGORY_MOBILE);
    result = (struct QTask_s *)Game_ptGame->ptWorld;
    if ( ptQTask[7].tQTaskChildren.ptTail )
    {
      ptQTask[2].tQTaskRefList.ptHead = nullptr;
      ptQTask[2].tQTaskRefList.ptMiddle = nullptr;
    }
    else
    {
      return (struct QTask_s *)SectorObject_RegisterInteriorDynCubeObjSpecificSectorObject(
                                 (struct World_s *)result,
                                 nullptr,
                                 (struct DynCubeObj_s *)ptQTask,
                                 (struct real64x3_t *)&ptQTask[1]);
    }
  }
  return result;
}

// source: j/0/pickups/genericpickup.c:141  [size]
void __cdecl GenericPickup_GetSerializeInfoHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = 1;
  *((_DWORD *)pxContext + 1) = 1;
}

// source: j/0/pickups/genericpickup.c:160  [size]
void __cdecl GenericPickup_GetSerializeParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = GenericPickup_ptSerializeParameterList;
}

// source: j/0/pickups/genericpickup.c:178  [anchor-mhash]
void __cdecl GenericPickup_DeSerializeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct LODVirModel_s *LODVirModelExistsFn; // eax

  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[Serialize_eDeSerializeQTaskEvent][SectorInteriorObject_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  LODVirModelExistsFn = MTP_GetLODVirModelExistsFn((char *)&ptQTask[8].tQTaskRefList.ptMiddle);
  if ( LODVirModelExistsFn != *(struct LODVirModel_s **)&ptQTask[2].eQTaskType )
  {
    ModelObj_SetLODVirModel((struct ModelObj_s *)ptQTask, LODVirModelExistsFn, false);
    ptQTask[7].tQTaskRefList.ptHead = nullptr;
    ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
    ptQTask[7].tQTaskRefList.ptTail = nullptr;
    ptQTask[7].ptParent = nullptr;
    *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  }
}

// source: j/0/pickups/genericpickup.c:197  [anchor-mhash]
void __cdecl GenericPickup_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct Game_s *v2; // eax

  v2 = Game_ptGame;
  ptQTask[8].ptNext = nullptr;
  ptQTask[8].ptPrev = nullptr;
  ptQTask[8].tQTaskChildren.ptHead = nullptr;
  ptQTask[8].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[8].tQTaskChildren.ptTail = nullptr;
  ptQTask[8].tQTaskRefList.ptHead = nullptr;
  ModelObj_Init((struct ModelObj_s *)ptQTask, v2->ptWorld, nullptr);
  ptQTask[7].tQTaskChildren.ptHead = nullptr;
  ptQTask[7].tQTaskChildren.ptMiddle = (struct QTask_s *)2;
  ptQTask[7].tQTaskRefList.ptHead = nullptr;
  ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[7].tQTaskRefList.ptTail = nullptr;
  ptQTask[7].ptParent = nullptr;
  *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  LOBYTE(ptQTask[9].ptNext) = 0;
  BYTE1(ptQTask[9].ptNext) = 0;
  LOBYTE(ptQTask[8].tQTaskRefList.ptMiddle) = 0;
  GenericPickup_Register(ptQTask);
}

// source: j/0/pickups/genericpickup.c:231  [anchor-mhash]
void __cdecl GenericPickup_RunHandler(struct QTask_s *ptQTask)
{
  if ( BYTE1(ptQTask[9].ptNext) )
  {
    if ( ptQTask[2].tQTaskChildren.ptHead )
    {
      SoundSys_PlaySimpleSoundDefFn("pickup", 0, nullptr);
      GenericPickup_Unregister(ptQTask);
    }
  }
}

// source: j/0/pickups/genericpickup.c:256  [anchor-mhash]
void __cdecl GenericPickup_DeleteHandler(struct QTask_s *ptQTask)
{
  int v1; // eax
  struct QReference_s *v2; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *); // eax

  GenericPickup_Unregister(ptQTask);
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
  if ( *(_DWORD *)&ptQTask[2].eQTaskType )
  {
    ModelObj_SetLODVirModel((struct ModelObj_s *)ptQTask, nullptr, false);
    ptQTask[7].tQTaskRefList.ptHead = nullptr;
    ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
    ptQTask[7].tQTaskRefList.ptTail = nullptr;
    ptQTask[7].ptParent = nullptr;
    *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  }
}

// source: j/0/pickups/genericpickup.c:283  [size]
void __cdecl GenericPickup_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = GenericPickup_ptParameterList;
}

// source: j/0/pickups/genericpickup.c:299  [anchor-mhash]
void __cdecl GenericPickup_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct LODVirModel_s *LODVirModelExistsFn; // eax
  double v3; // st7
  double v4; // st7
  int *v5; // eax
  int v6; // eax
  double v7; // st6
  struct World_s *ptWorld; // ebx
  __int16 v9; // cx
  float ptDynCubeObj; // [esp+0h] [ebp-10h]

  LODVirModelExistsFn = MTP_GetLODVirModelExistsFn((char *)&ptQTask[8].tQTaskRefList.ptMiddle);
  if ( LODVirModelExistsFn != *(struct LODVirModel_s **)&ptQTask[2].eQTaskType )
  {
    ModelObj_SetLODVirModel((struct ModelObj_s *)ptQTask, LODVirModelExistsFn, false);
    ptQTask[7].tQTaskRefList.ptHead = nullptr;
    ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
    ptQTask[7].tQTaskRefList.ptTail = nullptr;
    ptQTask[7].ptParent = nullptr;
    *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  }
  if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
    v3 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  else
    v3 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  if ( v3 >= *(float *)&ptQTask[6].ptPrev )
  {
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
      v4 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v4 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  }
  else
  {
    v4 = *(float *)&ptQTask[6].ptPrev;
  }
  v5 = *(int **)&ptQTask[2].eQTaskType;
  if ( v5 && (v6 = *v5) != 0 )
    v7 = *(float *)(*(_DWORD *)(*(_DWORD *)(v6 + 12) + 12) + 120);
  else
    v7 = 1.0;
  ptDynCubeObj = v4 * v7;
  World_MoveDynCubeObjRadius(
    Game_ptGame->ptWorld,
    (struct DynCubeObj_s *)ptQTask,
    (struct real64x3_t *)&ptQTask[8],
    ptDynCubeObj);
  ptWorld = Game_ptGame->ptWorld;
  SectorObject_RemoveInteriorDynCubeObj((struct DynCubeObj_s *)ptQTask);
  if ( ptQTask[7].tQTaskChildren.ptTail )
  {
    ptQTask[2].tQTaskRefList.ptHead = nullptr;
    ptQTask[2].tQTaskRefList.ptMiddle = nullptr;
  }
  else
  {
    SectorObject_RegisterInteriorDynCubeObjSpecificSectorObject(
      ptWorld,
      nullptr,
      (struct DynCubeObj_s *)ptQTask,
      (struct real64x3_t *)&ptQTask[1]);
  }
  v9 = Attach_eAttachEvent;
  ptQTask[5].tQTaskChildren.ptTail = (struct QTask_s *)-1;
  ptQTask[5].tQTaskRefList.ptHead = nullptr;
  QTask_TriggerQTaskEventParent(ptQTask, v9, &ptQTask[5].tQTaskChildren.ptTail);
  ModelObj_CalcRelativePosAndOrientation((struct ModelObj_s *)ptQTask);
  RigidDynCubeObj_UpdateAttachments((struct RigidDynCubeObj_t *)ptQTask);
}

// source: j/0/pickups/genericpickup.c:365  [size]
void __cdecl GenericPickup_UpdateAttachmentHandler(struct QTask_s *ptQTask)
{
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Attach_eUpdateAttachmentEvent][SectorInteriorObject_eQTaskType].pfHandler)(ptQTask);
  qmemcpy(&ptQTask[8], &ptQTask[1], 0x18u);
}

// source: j/0/pickups/genericpickup.c:386  [size]
void __cdecl GenericPickup_RegisterScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( !LOBYTE(ptQTask[9].ptNext) )
  {
    LOBYTE(ptQTask[9].ptNext) = 1;
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.isPickedUp", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      (char *)&ptQTask[9].ptNext + 1,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
  }
}

// source: j/0/pickups/genericpickup.c:416  [size]
void __cdecl GenericPickup_RemoveScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( LOBYTE(ptQTask[9].ptNext) )
  {
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    LOBYTE(ptQTask[9].ptNext) = 0;
    sprintf(igi2_frame.zTemp, "%s.isPickedUp", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
  }
}

// source: j/0/pickups/genericpickup.c:446  [size]
void __cdecl GenericPickup_ObjectCollisionEvaluateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_BYTE *)pxContext = 0;
}

// source: j/0/pickups/genericpickup.c:466  [size]
void __cdecl GenericPickup_GetNextZEvaluateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_BYTE *)pxContext = 0;
}

// source: j/0/pickups/genericpickup.c:486  [anchor-mhash]
void __cdecl GenericPickup_PickupHandler(struct QTask_s *ptQTask, void *pxContext)
{
  double v2; // st7
  double v3; // st7
  int *v4; // eax
  int v5; // eax
  double v6; // st6
  double v7; // st7
  double v8; // st6
  double v9; // st5
  double vHeight; // [esp+0h] [ebp-Ch]

  if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
    v2 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  else
    v2 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  if ( v2 >= *(float *)&ptQTask[6].ptPrev )
  {
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
      v3 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v3 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  }
  else
  {
    v3 = *(float *)&ptQTask[6].ptPrev;
  }
  v4 = *(int **)&ptQTask[2].eQTaskType;
  if ( v4 && (v5 = *v4) != 0 )
    v6 = *(float *)(*(_DWORD *)(*(_DWORD *)(v5 + 12) + 12) + 120);
  else
    v6 = 1.0;
  v7 = v3 * v6;
  if ( v7 < 4096.0 )
    v7 = 4096.0;
  v8 = *(double *)&ptQTask[1].ptNext - *((double *)pxContext + 1);
  v9 = *(double *)&ptQTask[1].tQTaskChildren.ptHead - *((double *)pxContext + 2);
  vHeight = *(double *)&ptQTask[1].tQTaskChildren.ptTail - *((double *)pxContext + 3);
  if ( sqrt(v9 * v9 + v8 * v8) < v7 && -6144.0 - v7 < vHeight && vHeight < v7 + 4096.0 )
    BYTE1(ptQTask[9].ptNext) = 1;
}

// source: j/0/pickups/genericpickup.c:542  [anchor-mhash]
void __cdecl GenericPickup_RegisterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptHead; // eax
  int v3; // edx
  struct QTask_s *v4; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // ecx
  int v6; // edx

  if ( !ptQTask[2].tQTaskChildren.ptHead && !BYTE1(ptQTask[9].ptNext) )
    GenericPickup_Register(ptQTask);
  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v3 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v4 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v4 = nullptr;
      QTask_atProtectedQTaskStack[v3].ptQTask = v4;
      pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRegisterQTaskEvent][ptHead->eQTaskType].pfHandler;
      v6 = v3 + 1;
      QTask_nProtectedQTaskStackOffset = v6;
      if ( pfHandler )
      {
        pfHandler(ptHead, pxContext);
        v6 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v6];
      v3 = v6 - 1;
      QTask_nProtectedQTaskStackOffset = v3;
    }
    while ( ptHead );
  }
}

// source: j/0/pickups/genericpickup.c:565  [size]
void __cdecl GenericPickup_RemoveHandler(struct QTask_s *ptQTask, void *pxContext)
{
  if ( ptQTask[2].tQTaskChildren.ptHead )
    GenericPickup_Unregister(ptQTask);
}

// source: j/0/pickups/genericpickup.c:592  [anchor-strings]
void __cdecl GenericPickup_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // edx

  v0 = QTask_NewQTaskType("GenericPickup", 368, SectorInteriorObject_eQTaskType, 0, 0);
  GenericPickup_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveNoChildrenHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, GenericPickup_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, GenericPickup_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, GenericPickup_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))GenericPickup_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eUpdateInternalDataQTaskEvent,
    GenericPickup_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eRegisterLevelScriptSymbolsEvent,
    GenericPickup_RegisterScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eRemoveLevelScriptSymbolsEvent,
    GenericPickup_RemoveScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    GameFunctions_eObjectCollisionEvaluateQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))GenericPickup_ObjectCollisionEvaluateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    GameFunctions_eGetNextZEvaluateQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))GenericPickup_GetNextZEvaluateHandler);
  QTask_LinkQTaskEventHandlerFn(v0, GameFunctions_ePickupQTaskEvent, GenericPickup_PickupHandler);
  QTask_LinkQTaskEventHandlerFn(v0, DynCubeObj_eDynCubeObjRemoveQTaskEvent, GenericPickup_RemoveHandler);
  QTask_LinkQTaskEventHandlerFn(v0, DynCubeObj_eDynCubeObjRegisterQTaskEvent, GenericPickup_RegisterHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Attach_eUpdateAttachmentEvent, GenericPickup_UpdateAttachmentHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Serialize_eGetSerializeParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))GenericPickup_GetSerializeParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, Serialize_eDeSerializeQTaskEvent, GenericPickup_DeSerializeHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Serialize_eGetSerializeInfoQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))GenericPickup_GetSerializeInfoHandler);
  v1 = (struct ParameterList_s *)Mem_AllocFn(72, 4);
  v1->nParameters = 0;
  v1->nMaxParameters = 3;
  v2 = Level_eParameterTypeObjectPos;
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  GenericPickup_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0x140u, v2, "Position", 7u, nullptr);
  ParameterList_AddParameter(
    GenericPickup_ptParameterList,
    0x7Cu,
    Level_eParameterTypeReal32x9,
    "Orientation",
    7u,
    nullptr);
  ParameterList_AddParameter(GenericPickup_ptParameterList, 0x158u, Level_eParameterTypeString16, "Model", 7u, nullptr);
  GenericPickup_ptSerializeParameterList = ParameterList_Derive(ModelObjParameters_ptSerializeParameterList, 2);
  ParameterList_AddParameter(
    GenericPickup_ptSerializeParameterList,
    0x169u,
    Level_eParameterTypebool8,
    "isPickedUp",
    7u,
    nullptr);
  ParameterList_AddParameter(
    GenericPickup_ptSerializeParameterList,
    0x158u,
    Level_eParameterTypeString16,
    "zModel",
    7u,
    nullptr);
}

// source: j/0/pickups/genericpickup.c:646  [size]
void __cdecl GenericPickup_Close()
{
  int v0; // esi
  int v1; // esi

  if ( GenericPickup_ptSerializeParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&GenericPickup_ptSerializeParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  if ( GenericPickup_ptParameterList )
  {
    v1 = *(_DWORD *)((unsigned int)&GenericPickup_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
  QTask_DeleteQTaskType(GenericPickup_eQTaskType);
}
