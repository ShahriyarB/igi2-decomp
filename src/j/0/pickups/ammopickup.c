/* j/0/pickups/ammopickup.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/pickups/ammopickup.c:111  [size]
void __cdecl AmmoPickup_GetGameItemDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: j/0/pickups/ammopickup.c:132  [size]
void __cdecl AmmoPickup_GameItemUpdateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  HIBYTE(ptQTask[10].tQTaskRefList.ptMiddle) = *((_BYTE *)pxContext + 16);
}

// source: j/0/pickups/ammopickup.c:153  [anchor-mhash]
void __cdecl AmmoPickup_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct World_s *ptDynCubeObj; };
    struct { float ptDynCubeObja; };
    struct { char igi2_o2[24]; struct real64x3_t ptPos; };
    char igi2_extent[52];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v2; // st7
  double v3; // st7
  int *v4; // eax
  int v5; // eax
  double v6; // st6
  bool v7; // zf

  igi2_frame.ptDynCubeObj = Game_ptGame->ptWorld;
  memset(&igi2_frame.ptPos, 0, sizeof(igi2_frame.ptPos));
  ModelObj_Init((struct ModelObj_s *)ptQTask, igi2_frame.ptDynCubeObj, nullptr);
  ptQTask[7].tQTaskChildren.ptHead = nullptr;
  ptQTask[7].tQTaskChildren.ptMiddle = (struct QTask_s *)2;
  ptQTask[7].tQTaskRefList.ptHead = nullptr;
  ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[7].tQTaskRefList.ptTail = nullptr;
  ptQTask[7].ptParent = nullptr;
  *(_DWORD *)&ptQTask[7].eQTaskType = 0;
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
  igi2_frame.ptDynCubeObja = v3 * v6;
  World_RegisterDynCubeObjFirstTimeRadius(
    Game_ptGame->ptWorld,
    (struct DynCubeObj_s *)ptQTask,
    &igi2_frame.ptPos,
    igi2_frame.ptDynCubeObja,
    WORLD_DYNCUBETREE_CATEGORY_STATIONARY);
  if ( ptQTask[7].tQTaskChildren.ptTail )
  {
    ptQTask[2].tQTaskRefList.ptHead = nullptr;
    ptQTask[2].tQTaskRefList.ptMiddle = nullptr;
  }
  else
  {
    SectorObject_RegisterInteriorDynCubeObjSpecificSectorObject(
      (struct World_s *)ptQTask[2].ptParent,
      nullptr,
      (struct DynCubeObj_s *)ptQTask,
      (struct real64x3_t *)&ptQTask[1]);
  }
  v7 = Game_eGameMode == GAME_GAMEMODE_SINGLEPLAYER;
  ptQTask[8].ptNext = nullptr;
  ptQTask[8].ptPrev = nullptr;
  ptQTask[8].tQTaskChildren.ptHead = nullptr;
  ptQTask[8].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[8].tQTaskChildren.ptTail = nullptr;
  ptQTask[8].tQTaskRefList.ptHead = nullptr;
  ptQTask[8].tQTaskRefList.ptTail = nullptr;
  LOBYTE(ptQTask[8].ptParent) = 0;
  LOWORD(ptQTask[10].tQTaskRefList.ptMiddle) = 0;
  strcpy((char *)&ptQTask[9].tQTaskRefList.ptMiddle, "10 * GAME_FREQUENCY");
  ptQTask[10].tQTaskChildren.ptTail = nullptr;
  ptQTask[10].tQTaskRefList.ptHead = nullptr;
  if ( v7 )
  {
    HIBYTE(ptQTask[10].tQTaskRefList.ptMiddle) = 1;
    BYTE2(ptQTask[10].tQTaskRefList.ptMiddle) = 1;
  }
  else if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    BYTE2(ptQTask[10].tQTaskRefList.ptMiddle) = 0;
    HIBYTE(ptQTask[10].tQTaskRefList.ptMiddle) = 0;
  }
  else
  {
    BYTE2(ptQTask[10].tQTaskRefList.ptMiddle) = 1;
    HIBYTE(ptQTask[10].tQTaskRefList.ptMiddle) = 1;
  }
  if ( BYTE2(ptQTask[10].tQTaskRefList.ptMiddle) )
    QTaskList_Register(GameFunctions_ptPickupQTaskList, (struct QTaskList_s *)ptQTask);
}

void __cdecl sub_532480(struct QTask_s *a1)
{
  struct QReference_s *ptHead; // eax

  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER
    && !Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle
    && !HIBYTE(a1[10].tQTaskRefList.ptMiddle) )
  {
    ptHead = a1[10].tQTaskRefList.ptHead;
    if ( (int)ptHead > 0 )
      a1[10].tQTaskRefList.ptHead = (struct QReference_s *)((char *)ptHead - 1);
  }
}

void __cdecl sub_5324C0(struct QTask_s *a1, void *a2)
{
  if ( HIBYTE(a1[10].tQTaskRefList.ptMiddle) )
    ((void (__cdecl *)())QTask_aatQTaskFinalEvent[5][SectorInteriorObject_eQTaskType].pfHandler)(a1, a2);
}

// source: j/0/pickups/ammopickup.c:299  [anchor-mhash]
void __cdecl AmmoPickup_DeleteHandler(struct QTask_s *ptQTask)
{
  if ( *(_DWORD *)&ptQTask[2].eQTaskType )
  {
    ModelObj_SetLODVirModel((struct ModelObj_s *)ptQTask, nullptr, false);
    ptQTask[7].tQTaskRefList.ptHead = nullptr;
    ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
    ptQTask[7].tQTaskRefList.ptTail = nullptr;
    ptQTask[7].ptParent = nullptr;
    *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  }
  if ( BYTE2(ptQTask[10].tQTaskRefList.ptMiddle) )
    QTaskList_Remove(GameFunctions_ptPickupQTaskList, ptQTask);
  SectorObject_RemoveInteriorDynCubeObj((struct DynCubeObj_s *)ptQTask);
  World_RemoveDynCubeObj(Game_ptGame->ptWorld, (struct DynCubeObj_s *)ptQTask);
}

// source: j/0/pickups/ammopickup.c:330  [size]
void __cdecl AmmoPickup_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = AmmoPickup_ptParameterList;
}

// source: j/0/pickups/ammopickup.c:346  [size~]
void __cdecl AmmoPickup_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v2; // eax
  struct QReference_s *ptTail; // edi
  struct AmmoType_s *AmmoTypeFromID; // eax
  struct LODVirModel_s *LODVirModelExistsFn; // eax
  double v6; // st7
  double v7; // st7
  int *v8; // eax
  int v9; // eax
  double v10; // st6
  struct QTask_s *ptParent; // ebx
  __int16 v12; // cx
  float ptDynCubeObj; // [esp+0h] [ebp-10h]

  ptQTask[8].tQTaskRefList.ptTail = (struct QReference_s *)Script_ParseLineInt32((char *)&ptQTask[8].ptParent);
  v2 = (struct QTask_s *)Script_ParseLineInt32((char *)&ptQTask[9].tQTaskRefList.ptMiddle);
  ptTail = ptQTask[8].tQTaskRefList.ptTail;
  ptQTask[10].tQTaskChildren.ptTail = v2;
  AmmoTypeFromID = AmmoType_GetAmmoTypeFromID((int)ptTail);
  if ( AmmoTypeFromID )
  {
    LODVirModelExistsFn = MTP_GetLODVirModelExistsFn(AmmoTypeFromID->zModel);
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
      v6 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v6 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
    if ( v6 >= *(float *)&ptQTask[6].ptPrev )
    {
      if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
        v7 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
      else
        v7 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
    }
    else
    {
      v7 = *(float *)&ptQTask[6].ptPrev;
    }
    v8 = *(int **)&ptQTask[2].eQTaskType;
    if ( v8 && (v9 = *v8) != 0 )
      v10 = *(float *)(*(_DWORD *)(*(_DWORD *)(v9 + 12) + 12) + 120);
    else
      v10 = 1.0;
    ptDynCubeObj = v7 * v10;
    World_MoveDynCubeObjRadius(
      Game_ptGame->ptWorld,
      (struct DynCubeObj_s *)ptQTask,
      (struct real64x3_t *)&ptQTask[8],
      ptDynCubeObj);
    ptParent = ptQTask[2].ptParent;
    SectorObject_RemoveInteriorDynCubeObj((struct DynCubeObj_s *)ptQTask);
    if ( ptQTask[7].tQTaskChildren.ptTail )
    {
      ptQTask[2].tQTaskRefList.ptHead = nullptr;
      ptQTask[2].tQTaskRefList.ptMiddle = nullptr;
    }
    else
    {
      SectorObject_RegisterInteriorDynCubeObjSpecificSectorObject(
        (struct World_s *)ptParent,
        nullptr,
        (struct DynCubeObj_s *)ptQTask,
        (struct real64x3_t *)&ptQTask[1]);
    }
    v12 = Attach_eAttachEvent;
    ptQTask[5].tQTaskChildren.ptTail = (struct QTask_s *)-1;
    ptQTask[5].tQTaskRefList.ptHead = nullptr;
    QTask_TriggerQTaskEventParent(ptQTask, v12, &ptQTask[5].tQTaskChildren.ptTail);
    ModelObj_CalcRelativePosAndOrientation((struct ModelObj_s *)ptQTask);
    RigidDynCubeObj_UpdateAttachments((struct RigidDynCubeObj_t *)ptQTask);
  }
}

// source: j/0/pickups/ammopickup.c:434  [size]
void __cdecl AmmoPickup_UpdateAttachmentHandler(struct QTask_s *ptQTask)
{
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Attach_eUpdateAttachmentEvent][SectorInteriorObject_eQTaskType].pfHandler)(ptQTask);
  qmemcpy(&ptQTask[8], &ptQTask[1], 0x18u);
}

// source: j/0/pickups/ammopickup.c:455  [size]
void __cdecl AmmoPickup_ObjectCollisionEvaluateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_BYTE *)pxContext = 0;
}

// source: j/0/pickups/ammopickup.c:475  [size]
void __cdecl AmmoPickup_GetNextZEvaluateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_BYTE *)pxContext = 0;
}

// source: j/0/pickups/ammopickup.c:495  [anchor-strings]
void __cdecl AmmoPickup_PickupHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s *v13; };
    struct { char igi2_o1[28]; double vHeight; };
    struct { char igi2_o2[36]; int v15; };
    char igi2_extent[48];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v2; // st7
  double v3; // st7
  int *v4; // eax
  int v5; // eax
  double v6; // st6
  double v7; // st7
  double v8; // st6
  double v9; // st5
  int ptMiddle_low; // eax
  int v11; // eax
  void (__cdecl *pfHandler)(int, double *); // ecx

  if ( HIBYTE(ptQTask[10].tQTaskRefList.ptMiddle) )
  {
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
    igi2_frame.vHeight = *(double *)&ptQTask[1].tQTaskChildren.ptTail - *((double *)pxContext + 3);
    if ( sqrt(v9 * v9 + v8 * v8) < v7
      && -v7 < igi2_frame.vHeight
      && igi2_frame.vHeight < v7 + 7372.8
      && Game_eGameMode == GAME_GAMEMODE_SINGLEPLAYER )
    {
      ptMiddle_low = SLOWORD(ptQTask[10].tQTaskRefList.ptMiddle);
      LODWORD(igi2_frame.vHeight) = ptQTask[8].tQTaskRefList.ptTail;
      HIDWORD(igi2_frame.vHeight) = ptMiddle_low;
      v11 = *(_DWORD *)pxContext;
      igi2_frame.v15 = 0;
      pfHandler = (void (__cdecl *)(int, double *))QTask_aatQTaskFinalEvent[AmmoPickup_eAmmoPickupQTaskEvent][*(unsigned __int16 *)(v11 + 36)].pfHandler;
      if ( pfHandler )
        pfHandler(v11, &igi2_frame.vHeight);
      igi2_frame.v13 = Level_ptDynamicQTask;
      HIBYTE(ptQTask[10].tQTaskRefList.ptMiddle) = 0;
      StatusMessage_New(igi2_frame.v13, "PICKEDUPAMMO", "STATUSSCREEN:ammo.spr", (char *)&g_zInitialValue, true);
    }
  }
}

// source: j/0/pickups/ammopickup.c:634  [size]
__int16 __cdecl AmmoPickup_GetAmmoPickupQTaskEvent()
{
  return AmmoPickup_eAmmoPickupQTaskEvent;
}

// source: j/0/pickups/ammopickup.c:648  [anchor-strings]
void __cdecl AmmoPickup_Open()
{
  __int16 v0; // ax
  unsigned __int16 v1; // si
  struct ParameterList_s *v2; // eax
  int v3; // edx

  AmmoPickup_eQTaskType = QTask_NewQTaskType("AmmoPickup", 432, SectorInteriorObject_eQTaskType, 0, 0);
  v0 = QTask_NewQTaskEventFn(0, "AmmoPickup");
  v1 = AmmoPickup_eQTaskType;
  AmmoPickup_eAmmoPickupQTaskEvent = v0;
  QTask_LinkQTaskEventHandlerFn(
    AmmoPickup_eQTaskType,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveNoChildrenHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 0, AmmoPickup_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, (void (__cdecl *)(struct QTask_s *))sub_532480);
  QTask_LinkQTaskEventHandlerFn(v1, 5, (void (__cdecl *)(struct QTask_s *, void *))sub_5324C0);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, AmmoPickup_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))AmmoPickup_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v1, ParameterList_eUpdateInternalDataQTaskEvent, AmmoPickup_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    GameFunctions_eObjectCollisionEvaluateQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))AmmoPickup_ObjectCollisionEvaluateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    GameFunctions_eGetNextZEvaluateQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))AmmoPickup_GetNextZEvaluateHandler);
  QTask_LinkQTaskEventHandlerFn(v1, GameFunctions_ePickupQTaskEvent, AmmoPickup_PickupHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, Attach_eUpdateAttachmentEvent, AmmoPickup_UpdateAttachmentHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    NetworkGameItem_eGetGameItemDataQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))AmmoPickup_GetGameItemDataHandler);
  QTask_LinkQTaskEventHandlerFn(v1, NetworkGameItem_eGameItemUpdateQTaskEvent, AmmoPickup_GameItemUpdateHandler);
  v2 = (struct ParameterList_s *)Mem_AllocFn(112, 4);
  v3 = Level_eParameterTypeObjectPos;
  v2->ptParameterListItem = (struct ParameterListItem_s *)&v2[1];
  v2->nParameters = 0;
  v2->nMaxParameters = 5;
  AmmoPickup_ptParameterList = v2;
  ParameterList_AddParameter(v2, 0x140u, v3, "Position", 7u, nullptr);
  ParameterList_AddParameter(
    AmmoPickup_ptParameterList,
    0x7Cu,
    Level_eParameterTypeReal32x9,
    "Orientation",
    7u,
    nullptr);
  ParameterList_AddParameter(
    AmmoPickup_ptParameterList,
    0x160u,
    ParameterEnumList_eParameterTypeString32,
    "ID",
    7u,
    &AmmoType_tEnumList);
  ParameterList_AddParameter(
    AmmoPickup_ptParameterList,
    0x1A8u,
    Level_eParameterTypeInt16,
    (char *)&g_zMessage.anDR[24],
    7u,
    nullptr);
  ParameterList_AddParameter(
    AmmoPickup_ptParameterList,
    0x180u,
    Level_eParameterTypeString32,
    "Respawn Time",
    7u,
    nullptr);
}

// source: j/0/pickups/ammopickup.c:700  [size]
void __cdecl AmmoPickup_Close()
{
  int v0; // esi

  if ( AmmoPickup_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&AmmoPickup_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskEvent(AmmoPickup_eAmmoPickupQTaskEvent);
  QTask_DeleteQTaskType(AmmoPickup_eQTaskType);
}
