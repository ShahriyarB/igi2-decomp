/* j/0/weapons/grenade.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/weapons/grenade.c:172  [size]
void __cdecl Grenade_DeSerializeDoneHandler(struct QTask_s *ptQTask, void *pxContext)
{
  QTask_Delete(ptQTask);
}

// source: j/0/weapons/grenade.c:188  [anchor-callee]
void __cdecl Grenade_Interpolate(struct Grenade_s *ptGrenade)
{
  DWORD PerformanceCounter; // eax
  int v2; // eax
  double vZ; // st7
  double vY; // st7
  struct LODVirModel_s *ptLODVirModel; // eax
  struct VirModel_s *v6; // eax
  double vRadius; // st6
  float ptDynCubeObj; // [esp+0h] [ebp-10h]

  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  v2 = PerformanceCounter - Timer_nStartTime;
  qmemcpy(
    &ptGrenade->tPosition,
    &ptGrenade->tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos,
    sizeof(ptGrenade->tPosition));
  Spline_Auto(&ptGrenade->tPosition, &ptGrenade->tSpeed, &ptGrenade->tSpline, v2);
  ptGrenade->tSpeed.vX = ptGrenade->tSpeed.vX * 1000.0;
  ptGrenade->tSpeed.vY = ptGrenade->tSpeed.vY * 1000.0;
  ptGrenade->tSpeed.vZ = ptGrenade->tSpeed.vZ * 1000.0;
  if ( ptGrenade->tPhysicsObj.tRigidDynCubeObj.tModelObj.tScale.vY <= (double)ptGrenade->tPhysicsObj.tRigidDynCubeObj.tModelObj.tScale.vZ )
    vZ = ptGrenade->tPhysicsObj.tRigidDynCubeObj.tModelObj.tScale.vZ;
  else
    vZ = ptGrenade->tPhysicsObj.tRigidDynCubeObj.tModelObj.tScale.vY;
  if ( vZ >= ptGrenade->tPhysicsObj.tRigidDynCubeObj.tModelObj.tScale.vX )
  {
    if ( ptGrenade->tPhysicsObj.tRigidDynCubeObj.tModelObj.tScale.vY <= (double)ptGrenade->tPhysicsObj.tRigidDynCubeObj.tModelObj.tScale.vZ )
      vY = ptGrenade->tPhysicsObj.tRigidDynCubeObj.tModelObj.tScale.vZ;
    else
      vY = ptGrenade->tPhysicsObj.tRigidDynCubeObj.tModelObj.tScale.vY;
  }
  else
  {
    vY = ptGrenade->tPhysicsObj.tRigidDynCubeObj.tModelObj.tScale.vX;
  }
  ptLODVirModel = ptGrenade->tPhysicsObj.tRigidDynCubeObj.tModelObj.ptLODVirModel;
  if ( ptLODVirModel && (v6 = ptLODVirModel->aptVirModel[0]) != nullptr )
    vRadius = v6->ptModel->ptMesh->vRadius;
  else
    vRadius = 1.0;
  ptDynCubeObj = vY * vRadius;
  World_MoveDynCubeObjRadius(
    Game_ptGame->ptWorld,
    &ptGrenade->tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj,
    &ptGrenade->tPosition,
    ptDynCubeObj);
}

// source: j/0/weapons/grenade.c:220  [anchor-callee]
struct Grenade_s *__cdecl Grenade_SendDetectionEvent(
        struct Grenade_s *ptGrenade,
        int eEvent,
        unsigned int bFlags,
        float vRadius)
{
  struct real64x3_t *p_tPos; // edx
  struct real32x3_t *p_tCMVel; // eax
  float vX; // ecx
  float vY; // edx
  struct QMaterial_t *vZ_low; // eax
  struct Grenade_s *result; // eax
  struct HumanAIEventContext_t tEventContext; // [esp+8h] [ebp-40h] BYREF

  tEventContext.ptReferenceQTask = &ptGrenade->tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask;
  tEventContext.eEvent = eEvent;
  tEventContext.bFlags = bFlags;
  p_tPos = &ptGrenade->tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos;
  p_tCMVel = &ptGrenade->tPhysicsObj.tPhysics.tCMVel;
  tEventContext.vRadius = vRadius;
  vX = p_tCMVel->vX;
  tEventContext.ptPosition = p_tPos;
  vY = p_tCMVel->vY;
  vZ_low = (struct QMaterial_t *)LODWORD(p_tCMVel->vZ);
  tEventContext.eTeam = -1;
  tEventContext.ptHumanOriginatorQTask = nullptr;
  *(_QWORD *)&tEventContext.uEventSpecificData.tReal64x3.vX = __PAIR64__(LODWORD(vY), LODWORD(vX));
  tEventContext.uEventSpecificData.tEnemyDetection.aptQMaterial[1] = vZ_low;
  HumanAI_SendEvent(&tEventContext);
  return result;
}

// source: j/0/weapons/grenade.c:248  [anchor-strings]
void __cdecl Grenade_ControlSound(struct Grenade_s *ptGrenade)
{
  struct QTask_s *v1; // eax
  struct Flow_t *v2; // edx

  if ( ptGrenade->tPhysicsObj.nContact )
  {
    if ( !ptGrenade->isSoundPlayed )
    {
      v1 = SoundSys_NewSoundFn(Level_ptDynamicQTask, "grenade_bnc_1");
      if ( v1 )
        ((void (__cdecl *)(struct QTask_s *, struct real64x3_t *))QTask_aatQTaskFinalEvent[SoundSys_eSetPositionQTaskEvent][v1->eQTaskType].pfHandler)(
          v1,
          &ptGrenade->tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos);
      if ( !*((_DWORD *)ptGrenade->tPhysicsObj.ptType->pxData + 1) )
        Grenade_SendDetectionEvent(ptGrenade, 17, 2u, 20480.0);
      v2 = Flow_ptFlow;
      ptGrenade->isSoundPlayed = 1;
      ptGrenade->nLastPlayed = v2->nTicks;
    }
  }
  else if ( Flow_ptFlow->nTicks - ptGrenade->nLastPlayed > 10 )
  {
    ptGrenade->isSoundPlayed = 0;
  }
}

// source: j/0/weapons/grenade.c:297  [anchor-callee]
struct Grenade_s *__cdecl Grenade_Move(struct Grenade_s *ptGrenade)
{
  struct Grenade_s *result; // eax
  DWORD v3; // eax
  DWORD PerformanceCounter; // eax
  struct ObjectCollisionEvaluateContext_t tObjectCollisionEvaluateContext; // [esp+8h] [ebp-Ch] BYREF

  result = (struct Grenade_s *)PhysicsObj_IsIdle(&ptGrenade->tPhysicsObj);
  if ( !result )
  {
    tObjectCollisionEvaluateContext.tCollisionEvaluateContext.ptQTask = &ptGrenade->tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask;
    PhysicsObj_Update(
      &ptGrenade->tPhysicsObj,
      44.600887298583984,
      1.0,
      0.9200000166893005,
      Game_ptGame->ptWorld,
      GameFunctions_eObjectCollisionEvaluateQTaskEvent,
      &tObjectCollisionEvaluateContext);
    v3 = Timer_isPerformanceCounter ? Timer_GetPerformanceCounter() : GetTickCount();
    result = (struct Grenade_s *)(v3 - Timer_nStartTime - ptGrenade->nLastForcedTime);
    if ( (int)result > 150 )
    {
      result = (struct Grenade_s *)ptGrenade->tPhysicsObj.nContact;
      if ( (int)result > 0 )
      {
        if ( Timer_isPerformanceCounter )
          PerformanceCounter = Timer_GetPerformanceCounter();
        else
          PerformanceCounter = GetTickCount();
        ptGrenade->nLastForcedTime = PerformanceCounter - Timer_nStartTime;
        if ( Timer_isPerformanceCounter )
          result = (struct Grenade_s *)(Timer_GetPerformanceCounter() - Timer_nStartTime);
        else
          result = (struct Grenade_s *)(GetTickCount() - Timer_nStartTime);
        ptGrenade->nNextUpdateTime = (int)result;
      }
    }
  }
  return result;
}

// source: j/0/weapons/grenade.c:346  [anchor-mhash]
void __cdecl Grenade_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[24]; struct real64x3_t tVNull; };
    char igi2_extent[52];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Flow_t *v2; // eax
  struct QTask_s *nTicks; // ecx
  bool v4; // zf
  DWORD TickCount; // eax
  struct Game_s *v6; // edx
  double v7; // st7
  double v8; // st7
  int *v9; // eax
  int v10; // eax
  double v11; // st6

  v2 = Flow_ptFlow;
  LOBYTE(ptQTask[47].eQTaskType) = 0;
  nTicks = (struct QTask_s *)v2->nTicks;
  v4 = Timer_isPerformanceCounter == 0;
  memset(&igi2_frame.tVNull, 0, sizeof(igi2_frame.tVNull));
  ptQTask[47].ptParent = nTicks;
  ptQTask[48].ptNext = nullptr;
  ptQTask[48].ptPrev = nullptr;
  ptQTask[48].tQTaskChildren.ptHead = nullptr;
  ptQTask[47].tQTaskRefList.ptTail = nullptr;
  ptQTask[54].ptPrev = nullptr;
  ptQTask[54].tQTaskChildren.ptHead = (struct QTask_s *)-1;
  ptQTask[54].tQTaskChildren.ptTail = nullptr;
  if ( v4 )
    TickCount = GetTickCount();
  else
    TickCount = Timer_GetPerformanceCounter();
  v6 = Game_ptGame;
  ptQTask[54].tQTaskChildren.ptMiddle = (struct QTask_s *)(TickCount - Timer_nStartTime + 150);
  ModelObj_Init((struct ModelObj_s *)ptQTask, v6->ptWorld, nullptr);
  ptQTask[7].tQTaskChildren.ptHead = nullptr;
  ptQTask[7].tQTaskChildren.ptMiddle = (struct QTask_s *)2;
  ptQTask[7].tQTaskRefList.ptHead = nullptr;
  ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[7].tQTaskRefList.ptTail = nullptr;
  ptQTask[7].ptParent = nullptr;
  *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
    v7 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  else
    v7 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  if ( v7 >= *(float *)&ptQTask[6].ptPrev )
  {
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
      v8 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v8 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  }
  else
  {
    v8 = *(float *)&ptQTask[6].ptPrev;
  }
  v9 = *(int **)&ptQTask[2].eQTaskType;
  if ( v9 && (v10 = *v9) != 0 )
    v11 = *(float *)(*(_DWORD *)(*(_DWORD *)(v10 + 12) + 12) + 120);
  else
    v11 = 1.0;
  igi2_frame.ptDynCubeObj = v8 * v11;
  World_RegisterDynCubeObjFirstTimeRadius(
    Game_ptGame->ptWorld,
    (struct DynCubeObj_s *)ptQTask,
    &igi2_frame.tVNull,
    igi2_frame.ptDynCubeObj,
    WORLD_DYNCUBETREE_CATEGORY_MOBILE);
  QTaskList_RegisterSafe(Grenade_ptQTaskList, ptQTask);
  QTaskList_Register(GameFunctions_ptCutsceneDeleteQTaskList, (struct QTaskList_s *)ptQTask);
}

// source: j/0/weapons/grenade.c:396  [anchor-strings]
void __cdecl Grenade_RunHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vFallOffRange; };
    struct { char igi2_o1[4]; float vFullRange; };
    struct { char igi2_o2[8]; struct real64x3_t vDistance; };
    struct { char igi2_o3[32]; int v41; };
    struct { char igi2_o4[40]; struct ClientGameMessageUpdateGrenade_s tGrenadeUpdate; };
    struct { char igi2_o5[96]; struct GetNextZEvaluateContext_t tGetNextZEvaluateContext; };
    struct { char igi2_o6[104]; struct QIntersection_s tIntersection; };
    char igi2_extent[224];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v1; // edi
  struct QReference_s *ptMiddle; // eax
  struct QTask_s *v3; // esi
  int v4; // eax
  int v5; // eax
  struct QTask_s *v6; // ecx
  struct QTask_s *v7; // eax
  struct QTask_s *v8; // eax
  struct QReference_s *v9; // edx
  struct QTask_s *v10; // ebx
  struct QTask_s *v11; // eax
  struct QTask_s *v12; // edx
  int ptTail; // edx
  struct QTask_s *v14; // eax
  float *pxObject; // ecx
  struct QTask_s *ptParent; // eax
  struct QTask_s *v17; // eax
  struct QReference_s *v18; // eax
  struct QTask_s *v19; // eax
  struct QTask_s *v20; // eax
  double v21; // st7
  struct QTask_s *vX_low; // ebx
  DWORD PerformanceCounter; // eax
  int Timer; // eax
  unsigned __int16 v25; // cx
  unsigned __int8 ptNext; // dl
  unsigned __int16 v27; // dx
  struct QTask_s *v28; // eax
  int v29; // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptHead; // eax
  struct QTask_s *v32; // ebp
  struct QTask_s *v33; // ecx
  int v34; // edx
  struct QTask_s *v35; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v37; // edx

  v1 = *(_DWORD *)(*(_DWORD *)&ptQTask[12].eQTaskType + 724);
  ptMiddle = ptQTask[47].tQTaskRefList.ptMiddle;
  if ( ptMiddle )
  {
    ptQTask[47].tQTaskRefList.ptMiddle = (struct QReference_s *)((char *)ptMiddle - 1);
LABEL_33:
    if ( !((int)ptQTask[47].tQTaskRefList.ptMiddle % 5)
      && !*(_DWORD *)(*(_DWORD *)(*(_DWORD *)&ptQTask[12].eQTaskType + 724) + 4) )
    {
      Grenade_SendDetectionEvent((struct Grenade_s *)ptQTask, 16, 1u, -1.0);
    }
    Grenade_ControlSound((struct Grenade_s *)ptQTask);
    if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
    {
      if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
      {
        if ( ptQTask[54].tQTaskChildren.ptHead != (struct QTask_s *)-1 )
          Grenade_Interpolate((struct Grenade_s *)ptQTask);
      }
      else
      {
        vX_low = nullptr;
        qmemcpy(&igi2_frame.vDistance, &ptQTask[1], sizeof(igi2_frame.vDistance));
        Grenade_Move((struct Grenade_s *)ptQTask);
        if ( Timer_isPerformanceCounter )
          PerformanceCounter = Timer_GetPerformanceCounter();
        else
          PerformanceCounter = GetTickCount();
        if ( (signed int)(PerformanceCounter - Timer_nStartTime) >= (int)ptQTask[54].tQTaskChildren.ptMiddle )
        {
          ptQTask[54].tQTaskChildren.ptMiddle = (struct QTask_s *)(Timer_Read() + 150);
          igi2_frame.tGrenadeUpdate.tBaseMessage.eGameMessage = 1431324498;
          Timer = NetManager_GetTimer();
          v25 = (unsigned __int16)ptQTask[47].tQTaskRefList.ptMiddle;
          ptNext = (unsigned __int8)ptQTask[13].ptNext;
          igi2_frame.tGrenadeUpdate.tBaseMessage.nLocalTime = Timer;
          LOBYTE(Timer) = ptQTask[54].ptNext;
          igi2_frame.tGrenadeUpdate.nExplodeTimer = v25;
          igi2_frame.tGrenadeUpdate.nContact = ptNext;
          igi2_frame.tGrenadeUpdate.iGrenadeID = Timer;
          qmemcpy(&igi2_frame.tGrenadeUpdate.tPos, &ptQTask[1], sizeof(igi2_frame.tGrenadeUpdate.tPos));
          igi2_frame.tGrenadeUpdate.tSpeed.vZ = igi2_frame.tGrenadeUpdate.tPos.vZ - igi2_frame.vDistance.vZ;
          v27 = Client_eQTaskType;
          igi2_frame.tGrenadeUpdate.tSpeed.vX = (igi2_frame.tGrenadeUpdate.tPos.vX - igi2_frame.vDistance.vX) * 30.0;
          igi2_frame.tGrenadeUpdate.tSpeed.vY = (igi2_frame.tGrenadeUpdate.tPos.vY - igi2_frame.vDistance.vY) * 30.0;
          igi2_frame.tGrenadeUpdate.tSpeed.vZ = igi2_frame.tGrenadeUpdate.tSpeed.vZ * 30.0;
          while ( 1 )
          {
            v28 = vX_low
                ? QTask_GetNextSiblingOfType(vX_low, v27)
                : QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, v27);
            LODWORD(igi2_frame.vDistance.vX) = v28;
            if ( !v28 )
              break;
            v29 = (int)v28[1].ptNext;
            if ( v29 )
            {
              NetManager_SendGameMessage(v29, 0, NETWORKQUEUE_MEDIUMPRIORITY, &igi2_frame.tGrenadeUpdate.tBaseMessage, 0x38u);
              v27 = Client_eQTaskType;
            }
            vX_low = (struct QTask_s *)LODWORD(igi2_frame.vDistance.vX);
          }
        }
      }
    }
    else
    {
      Grenade_Move((struct Grenade_s *)ptQTask);
    }
    ptPrev = ptQTask[48].ptPrev;
    if ( ptPrev )
    {
      ptHead = ptPrev->tQTaskChildren.ptHead;
      if ( ptHead->eQTaskType == Smoke_eQTaskType )
        qmemcpy(&ptHead[2].ptParent, &ptQTask[1], 0x18u);
    }
    v32 = ptQTask->tQTaskChildren.ptHead;
    if ( v32->ptNext )
    {
      v33 = ptQTask->tQTaskChildren.ptHead;
      if ( v32 )
      {
        v34 = QTask_nProtectedQTaskStackOffset;
        do
        {
          if ( v33->ptNext )
            v35 = v33->ptNext->ptNext != nullptr ? v33->ptNext : nullptr;
          else
            v35 = nullptr;
          QTask_atProtectedQTaskStack[v34].ptQTask = v35;
          pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][v33->eQTaskType].pfHandler;
          v37 = v34 + 1;
          QTask_nProtectedQTaskStackOffset = v37;
          if ( pfHandler )
          {
            pfHandler(v33);
            v37 = QTask_nProtectedQTaskStackOffset;
          }
          v33 = (struct QTask_s *)dword_849C7DC[v37];
          v34 = v37 - 1;
          QTask_nProtectedQTaskStackOffset = v34;
        }
        while ( v33 );
      }
    }
    return;
  }
  igi2_frame.vDistance.vX = -4096.0;
  v3 = ptQTask + 1;
  igi2_frame.tGetNextZEvaluateContext.tCollisionEvaluateContext.ptQTask = ptQTask;
  World_GetNextZNoMaterial(
    Game_ptGame->ptWorld,
    &igi2_frame.tIntersection,
    (struct real64x3_t *)&ptQTask[1],
    1,
    &igi2_frame.vDistance.vX,
    GameFunctions_eGetNextZEvaluateQTaskEvent,
    &igi2_frame.tGetNextZEvaluateContext.tCollisionEvaluateContext,
    0xFFFFFFFF);
  v4 = *(_DWORD *)(v1 + 4);
  if ( v4 )
  {
    v5 = v4 - 1;
    if ( !v5 )
    {
      v11 = ptQTask[48].ptNext;
      if ( v11
        && (v12 = v11->tQTaskChildren.ptHead) != nullptr
        && QTask_IsQTaskTypeDerived(v12->eQTaskType, Human_eQTaskType) )
      {
        ptTail = (int)v12[10].tQTaskRefList.ptTail;
      }
      else
      {
        ptTail = -1;
      }
      FlashBang_New((struct real64x3_t *)&ptQTask[1], &igi2_frame.tIntersection, 122880.0, 122880.0, ptTail);
      QTask_Delete(ptQTask);
      return;
    }
    if ( v5 == 1 )
    {
      v6 = ptQTask[48].ptPrev;
      if ( v6 )
      {
        v9 = (struct QReference_s *)((char *)&ptQTask[47].tQTaskRefList.ptTail->ptNext + 1);
        ptQTask[47].tQTaskRefList.ptTail = v9;
        v10 = v6->tQTaskChildren.ptHead;
        if ( !((int)v9 % 30) )
        {
          qmemcpy(&igi2_frame.vDistance, v3, sizeof(igi2_frame.vDistance));
          igi2_frame.v41 = 1178599424;
          World_TriggerQTaskEventSphereSpecificTree(
            Game_ptGame->ptWorld,
            Grenade_eSmokeAreaQTaskEvent,
            &igi2_frame.vDistance,
            &igi2_frame.vDistance,
            12288.0,
            0x20000000u,
            WORLD_DYNCUBETREE_STATIONARY);
        }
        if ( (int)ptQTask[47].tQTaskRefList.ptTail > 900 )
        {
          v10[5].tQTaskChildren.ptHead = nullptr;
          v10[5].tQTaskChildren.ptMiddle = nullptr;
          if ( (int)ptQTask[47].tQTaskRefList.ptTail > 1080 )
          {
            QTask_Delete(v10);
            QTask_Delete(ptQTask);
            return;
          }
        }
      }
      else
      {
        igi2_frame.vDistance.vX = 3.0517585287270776e-05;
        LODWORD(igi2_frame.vDistance.vY) = 1056964608;
        v7 = SoundSys_NewSoundFn(Level_ptDynamicQTask, "explo_smoke");
        if ( v7 )
          SoundSys_SetSoundPosition(v7, (struct real64x3_t *)&ptQTask[1]);
        v8 = Smoke_New(
               ptQTask,
               (struct real64x3_t *)&ptQTask[1],
               0.5,
               0.0,
               30,
               1.0,
               3.1415927410125732,
               0.10000000149011612,
               0.5,
               (struct real32x3_t *)&igi2_frame.vDistance,
               4.0,
               2.0,
               SMOKE_MODE_ALPHA,
               3,
               1.0,
               0.6000000238418579,
               0.0,
               0.0,
               1.0,
               6.0);
        qmemcpy(&v8[2].ptParent, v3, 0x18u);
        ptQTask[48].ptPrev = (struct QTask_s *)QTask_NewQTaskRef(v8);
      }
    }
    goto LABEL_33;
  }
  v14 = ptQTask[48].tQTaskChildren.ptHead;
  pxObject = nullptr;
  if ( v14[32].tQTaskRefList.ptHead == (struct QReference_s *)ProjectileLauncher_eQTaskType )
  {
    ptParent = v14[32].ptParent;
    if ( ptParent )
    {
      v17 = ptParent->tQTaskChildren.ptHead;
      if ( v17[7].tQTaskChildren.ptTail == (struct QTask_s *)Grenade_eQTaskType )
      {
        v18 = v17[7].tQTaskRefList.ptMiddle;
        if ( v18 )
          pxObject = (float *)v18->pxObject;
      }
    }
  }
  v19 = ptQTask[48].ptNext;
  if ( v19 )
    v20 = v19->tQTaskChildren.ptHead;
  else
    v20 = nullptr;
  if ( pxObject )
  {
    igi2_frame.vFallOffRange = pxObject[15] * 4096.0;
    v21 = pxObject[14];
    *(float *)&igi2_frame.vDistance.vX = pxObject[13];
    igi2_frame.vFullRange = v21 * 4096.0;
    Explosion0_New(
      (struct real64x3_t *)&ptQTask[1],
      1,
      1,
      *(float *)&igi2_frame.vDistance.vX,
      igi2_frame.vFullRange,
      igi2_frame.vFallOffRange,
      6144.0,
      3,
      1,
      &igi2_frame.tIntersection,
      "1009_01_1",
      "explo_grenade",
      20,
      0x402u,
      204800.0,
      nullptr,
      v20,
      EXPLOSIONDAMAGE_EXPONENTIAL_FALLOFF);
  }
  else
  {
    LODWORD(igi2_frame.vDistance.vX) = 1065353216;
    Explosion0_New(
      (struct real64x3_t *)&ptQTask[1],
      1,
      1,
      1.0,
      20480.0,
      0.0,
      6144.0,
      3,
      1,
      &igi2_frame.tIntersection,
      "1009_01_1",
      "explo_grenade",
      20,
      0x402u,
      204800.0,
      nullptr,
      v20,
      EXPLOSIONDAMAGE_EXPONENTIAL_FALLOFF);
  }
  QTask_Delete(ptQTask);
}

// source: j/0/weapons/grenade.c:681  [anchor-mhash]
void __cdecl Grenade_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptPrev; // eax

  ptNext = ptQTask[48].ptNext;
  if ( ptNext )
  {
    QReference_Delete((struct QReference_s *)ptNext, &QTask_tQTaskRefPool);
    ptQTask[48].ptNext = nullptr;
  }
  ptPrev = ptQTask[48].ptPrev;
  if ( ptPrev )
  {
    QReference_Delete((struct QReference_s *)ptPrev, &QTask_tQTaskRefPool);
    ptQTask[48].ptPrev = nullptr;
  }
  *(_DWORD *)&ptQTask[12].eQTaskType = 0;
  Physics_DeAlloc((struct Physics_s *)&ptQTask[8]);
  World_RemoveDynCubeObj(Game_ptGame->ptWorld, (struct DynCubeObj_s *)ptQTask);
  QTaskList_RemoveSafe(Grenade_ptQTaskList, ptQTask);
  QTaskList_Remove(GameFunctions_ptCutsceneDeleteQTaskList, ptQTask);
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

// source: j/0/weapons/grenade.c:723  [size]
void __cdecl Grenade_WeaponHitHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[47].tQTaskRefList.ptMiddle = nullptr;
}

// source: j/0/weapons/grenade.c:743  [anchor-mhash]
void __cdecl Grenade_ExplosionHitHandler(struct QTask_s *ptQTask, void *pxContext)
{
  double v2; // st7
  double v3; // st7
  int *v4; // eax
  int v5; // eax
  double v6; // st6
  float ptExplosionHitContext; // [esp+0h] [ebp-Ch]

  if ( ptQTask[47].tQTaskRefList.ptMiddle )
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
    ptExplosionHitContext = v3 * v6;
    if ( GameFunctions_ResolveExplosionHit(
           (struct ExplosionHitContext_t *)pxContext,
           ptQTask,
           (struct real64x3_t *)&ptQTask[1],
           ptExplosionHitContext,
           false) != 0.0 )
      ptQTask[47].tQTaskRefList.ptMiddle = nullptr;
  }
}

// source: j/0/weapons/grenade.c:786  [size]
void __cdecl Grenade_ObjectCollisionEvaluateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_BYTE *)pxContext = 0;
}

// source: j/0/weapons/grenade.c:806  [size]
void __cdecl Grenade_GetNextZEvaluateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_BYTE *)pxContext = 0;
}

// source: j/0/weapons/grenade.c:826  [anchor-mhash]
void __cdecl Grenade_ParsePhysicsObjTypeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // ebx
  float *v3; // esi
  struct ArgList_s *v4; // edi
  double v5; // st7
  int v6; // eax

  v2 = *((_DWORD *)pxContext + 2);
  v3 = *(float **)pxContext;
  v4 = *((struct ArgList_s **)pxContext + 1);
  if ( v4->isQVM )
  {
    *(float *)&pxContext = 0.0;
    QVM_EvalArg(&pxContext, 4, v4, v2, 2);
    v5 = *(float *)&pxContext;
  }
  else
  {
    v5 = Expression_EvalFloat(v4->aptExpression[v2]);
  }
  *v3 = v5;
  v6 = v2 + 1;
  if ( v4->isQVM )
  {
    *(float *)&pxContext = 0.0;
    QVM_EvalArg(&pxContext, 4, v4, v6, 1);
    v3[1] = *(float *)&pxContext;
  }
  else
  {
    *((_DWORD *)v3 + 1) = Expression_EvalInt(v4->aptExpression[v6]);
  }
}

// source: j/0/weapons/grenade.c:852  [size]
void __cdecl Grenade_GetGetPhysicsObjTypeSizeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = 8;
}

// source: j/0/weapons/grenade.c:868  [anchor-strings]
void __cdecl Grenade_CreateWeaponTypeParametersHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v2; // eax
  struct QTask_s *v3; // edi
  struct QTask_s *v4; // esi
  struct QTask_s *v5; // eax
  char *v6; // ecx
  char v7; // dl
  struct QTask_s *v8; // edi
  struct QTask_s *v9; // eax
  double v10; // st7
  struct QTask_s *v11; // edi
  struct QTask_s *v12; // eax
  double v13; // st7
  struct QTask_s *v14; // edi
  struct QTask_s *v15; // eax
  double v16; // st7
  struct QTask_s *v17; // edi
  struct QTask_s *v18; // eax
  double v19; // st7
  struct QTask_s *v20; // edi
  struct QTask_s *v21; // eax

  v2 = QTask_NewFn(nullptr, Grenade_eGrenadeParametersQTaskType, nullptr);
  v3 = *((struct QTask_s **)pxContext + 1);
  v4 = v2;
  *((_DWORD *)pxContext + 2) = v2;
  v5 = TagItem_Find(v3, "Explosion Type");
  if ( !v5 )
  {
    v5 = QTask_NewFn(v3, TagItem_eInt32QTaskType, nullptr);
    v6 = "Explosion Type";
    do
    {
      v7 = *v6;
      v6[(char *)v5 - "Explosion Type" + 40] = *v6;
      ++v6;
    }
    while ( v7 );
    v5[7].tQTaskRefList.ptHead = nullptr;
  }
  v4[1].ptNext = (struct QTask_s *)v5[7].tQTaskRefList.ptHead;
  v8 = *((struct QTask_s **)pxContext + 1);
  v9 = TagItem_Find(v8, "Explosion Radius (meters)");
  if ( v9 || (v9 = TagItem_NewReal32(v8, "Explosion Radius (meters)", 5.0)) != nullptr )
    v10 = *(float *)&v9[7].tQTaskRefList.ptHead;
  else
    v10 = 0.0;
  *(float *)&v4[1].tQTaskChildren.ptTail = v10;
  v11 = *((struct QTask_s **)pxContext + 1);
  v12 = TagItem_Find(v11, "Explosion Falloff (meters)");
  if ( v12 || (v12 = TagItem_NewReal32(v11, "Explosion Falloff (meters)", 0.0)) != nullptr )
    v13 = *(float *)&v12[7].tQTaskRefList.ptHead;
  else
    v13 = 0.0;
  *(float *)&v4[1].tQTaskRefList.ptHead = v13;
  v14 = *((struct QTask_s **)pxContext + 1);
  v15 = TagItem_Find(v14, "Explosion Damage Factor");
  if ( v15 || (v15 = TagItem_NewReal32MinMax(v14, "Explosion Damage Factor", 1.0, 0.0, 1.0)) != nullptr )
    v16 = *(float *)&v15[7].tQTaskRefList.ptHead;
  else
    v16 = 0.0;
  *(float *)&v4[1].tQTaskChildren.ptMiddle = v16;
  v17 = *((struct QTask_s **)pxContext + 1);
  v18 = TagItem_Find(v17, (char *)&stru_69552C.tQTaskRefList.ptMiddle);
  if ( v18
    || (v18 = TagItem_NewReal32MinMax(v17, (char *)&stru_69552C.tQTaskRefList.ptMiddle, 120.0, 1.0, 180.0)) != nullptr )
  {
    v19 = *(float *)&v18[7].tQTaskRefList.ptHead;
  }
  else
  {
    v19 = 0.0;
  }
  *(float *)&v4[1].ptPrev = v19;
  v20 = *((struct QTask_s **)pxContext + 1);
  v21 = TagItem_Find(v20, (char *)&stru_69552C);
  if ( v21 || (v21 = TagItem_NewReal32MinMax(v20, (char *)&stru_69552C, 1.0, 0.009999999776482582, 10.0)) != nullptr )
    v4[1].tQTaskChildren.ptHead = (struct QTask_s *)v21[7].tQTaskRefList.ptHead;
  else
    v4[1].tQTaskChildren.ptHead = nullptr;
}

// source: j/0/weapons/grenade.c:896  [anchor-caller]
void __cdecl Grenade_CreateProjectileHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real32x9_t *v16; };
    struct { char igi2_o1[8]; struct WeaponType_s *v17; };
    struct { char igi2_o2[12]; int v18; };
    struct { char igi2_o3[28]; float vIdealAlpha; };
    struct { char igi2_o4[32]; float vGamma; };
    struct { char igi2_o5[36]; float vBeta; };
    struct { char igi2_o6[40]; struct real32x3_t tSpeed; };
    char igi2_extent[52];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  unsigned __int8 *v2; // esi
  int v3; // edi
  double v4; // st7
  double v5; // st7
  float *v6; // eax
  int v7; // edx
  long double v8; // st7
  struct real32x9_t *v9; // edx
  long double v10; // st7
  double v11; // rt0
  double v12; // st5
  struct real64x3_t *v13; // eax
  struct QTask_s *v14; // ecx
  int v15; // edx

  v2 = (unsigned __int8 *)pxContext;
  v3 = *((_DWORD *)pxContext + 17);
  igi2_frame.vIdealAlpha = *(float *)(v3 + 44) * 0.0055555556900799274;
  Real32x9_GetAngles(*((struct real32x9_t **)pxContext + 8), (float *)&pxContext, &igi2_frame.vBeta, &igi2_frame.vGamma);
  v4 = *(float *)&pxContext;
  if ( *(float *)&pxContext >= 1.5707963705062866 && v4 < 3.1415927410125732 )
    v4 = 3.1415927410125732 - v4;
  if ( v4 >= 3.1415927410125732 && v4 < 4.71238899230957 )
    v4 = 6.2831854820251465 - (v4 - 3.1415927410125732);
  if ( v4 <= 1.5707963705062866 )
    v4 = v4 + 6.2831854820251465;
  v5 = (v4 - 4.71238899230957) * 0.31830987334251404;
  if ( v5 >= 0.0 )
  {
    if ( igi2_frame.vIdealAlpha >= v5 )
      *(float *)&pxContext = v5;
    else
      *(float *)&pxContext = igi2_frame.vIdealAlpha;
  }
  else
  {
    *(float *)&pxContext = 0.0;
  }
  v6 = *((float **)v2 + 8);
  v7 = *((_DWORD *)v2 + 13);
  v8 = pow(*(float *)&pxContext / igi2_frame.vIdealAlpha, *(float *)(v3 + 48)) * *((float *)v2 + 10) * 4096.0;
  igi2_frame.tSpeed.vZ = v6[7];
  igi2_frame.v18 = v7;
  v9 = *((struct real32x9_t **)v2 + 9);
  v10 = v8 * 0.03333333507180214;
  v11 = v6[4];
  v12 = v6[1];
  igi2_frame.v17 = *((struct WeaponType_s **)v2 + 15);
  v13 = *((struct real64x3_t **)v2 + 4);
  v14 = *((struct QTask_s **)v2 + 1);
  igi2_frame.tSpeed.vX = v12 * v10;
  igi2_frame.v16 = v9;
  v15 = v2[56];
  igi2_frame.tSpeed.vZ = igi2_frame.tSpeed.vZ * v10;
  igi2_frame.tSpeed.vX = igi2_frame.tSpeed.vX + *((float *)v2 + 5);
  igi2_frame.tSpeed.vY = v11 * v10 + *((float *)v2 + 6);
  igi2_frame.tSpeed.vZ = igi2_frame.tSpeed.vZ + *((float *)v2 + 7);
  Grenade_New(Level_ptDynamicQTask, v15, v14, v13, igi2_frame.v16, &igi2_frame.tSpeed, igi2_frame.v17, igi2_frame.v18);
}

// source: j/0/weapons/grenade.c:979  [anchor-strings]
void __cdecl Grenade_HandleUpdatePacket(struct ClientGameMessageUpdateGrenade_s *ptGameMessage)
{
  #pragma pack(push, 1)
  union
  {
    struct { int nNow; };
    struct { char igi2_o1[4]; float vNetTime; };
    struct { char igi2_o2[8]; struct Grenade_s *ptCheckGrenade; };
    struct { char igi2_o3[12]; struct real64x3_t tSplineSpeed; };
    struct { char igi2_o4[36]; struct real64x3_t ptPos; };
    struct { char igi2_o5[60]; struct real64x3_t ptSpeed; };
    char igi2_extent[84];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v1; // ecx
  struct QTask_s **ptQTask; // eax
  struct QTask_s *v3; // ebx
  struct QTask_s *ptNetManagerQTask; // esi
  DWORD PerformanceCounter; // eax
  DWORD TickCount; // eax
  double v7; // st7
  double vX; // st6
  double vY; // st5
  int ptParent; // eax
  struct Spline_s *p_ptTail; // esi
  int v12; // edx

  v1 = 0;
  if ( Grenade_ptQTaskList->nTask <= 0 )
  {
LABEL_5:
    NetManager_LogMessage((char *)&stru_6954D4.tQTaskRefList);
  }
  else
  {
    ptQTask = Grenade_ptQTaskList->ptQTask;
    while ( 1 )
    {
      v3 = *ptQTask;
      igi2_frame.ptCheckGrenade = (struct Grenade_s *)*ptQTask;
      if ( (*ptQTask)[54].ptNext == (struct QTask_s *)ptGameMessage->iGrenadeID )
        break;
      ++v1;
      ++ptQTask;
      if ( v1 >= Grenade_ptQTaskList->nTask )
        goto LABEL_5;
    }
    ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
    if ( Timer_isPerformanceCounter )
      PerformanceCounter = Timer_GetPerformanceCounter();
    else
      PerformanceCounter = GetTickCount();
    igi2_frame.vNetTime = (double)(int)(PerformanceCounter
                           - Timer_nStartTime
                           + (char *)ptNetManagerQTask[6].tQTaskRefList.ptMiddle
                           - (char *)ptNetManagerQTask[6].tQTaskRefList.ptTail
                           - ptGameMessage->tBaseMessage.nLocalTime)
             * 0.001;
    if ( Timer_isPerformanceCounter )
      TickCount = Timer_GetPerformanceCounter();
    else
      TickCount = GetTickCount();
    igi2_frame.nNow = TickCount - Timer_nStartTime;
    if ( igi2_frame.vNetTime < 0.0 )
      igi2_frame.vNetTime = 0.0;
    v7 = igi2_frame.vNetTime + 0.15000000596046448;
    qmemcpy(&v3[52].ptParent, &v3[51].tQTaskRefList.ptMiddle, 0x18u);
    vX = ptGameMessage->tSpeed.vX;
    vY = ptGameMessage->tSpeed.vY;
    igi2_frame.tSplineSpeed.vZ = ptGameMessage->tSpeed.vZ;
    igi2_frame.tSplineSpeed.vX = v7 * vX;
    qmemcpy(&v3[52].tQTaskChildren, &ptGameMessage->tPos, 0x18u);
    igi2_frame.tSplineSpeed.vZ = v7 * igi2_frame.tSplineSpeed.vZ;
    *(double *)&v3[52].tQTaskChildren.ptHead = igi2_frame.tSplineSpeed.vX + ptGameMessage->tPos.vX;
    *(double *)&v3[52].tQTaskChildren.ptTail = v7 * vY + ptGameMessage->tPos.vY;
    *(double *)&v3[52].tQTaskRefList.ptMiddle = igi2_frame.tSplineSpeed.vZ + ptGameMessage->tPos.vZ;
    *(double *)&v3[53].tQTaskChildren.ptTail = ptGameMessage->tSpeed.vX;
    *(double *)&v3[53].tQTaskRefList.ptMiddle = ptGameMessage->tSpeed.vY;
    *(double *)&v3[53].ptParent = ptGameMessage->tSpeed.vZ;
    ptParent = (int)v3[50].ptParent;
    qmemcpy(&igi2_frame.tSplineSpeed, &v3[53].tQTaskChildren.ptTail, sizeof(igi2_frame.tSplineSpeed));
    igi2_frame.tSplineSpeed.vX = igi2_frame.tSplineSpeed.vX * 0.001;
    igi2_frame.tSplineSpeed.vY = igi2_frame.tSplineSpeed.vY * 0.001;
    p_ptTail = (struct Spline_s *)&v3[48].tQTaskChildren.ptTail;
    igi2_frame.tSplineSpeed.vZ = igi2_frame.tSplineSpeed.vZ * 0.001;
    if ( ptParent <= 0 )
    {
      Spline_Initialize(
        p_ptTail,
        (struct real64x3_t *)&v3[52].tQTaskChildren,
        (struct real64x3_t *)&v3[52].tQTaskChildren,
        &igi2_frame.tSplineSpeed,
        &igi2_frame.tSplineSpeed,
        igi2_frame.nNow,
        150);
    }
    else
    {
      v12 = *(_DWORD *)&v3[50].eQTaskType;
      if ( igi2_frame.nNow >= v12 )
      {
        if ( igi2_frame.nNow <= ptParent + v12 )
          Spline_OnSpline(&igi2_frame.ptPos, &igi2_frame.ptSpeed, (struct Spline_s *)&v3[48].tQTaskChildren.ptTail, igi2_frame.nNow);
        else
          Spline_ExtraFromEnd(&igi2_frame.ptPos, &igi2_frame.ptSpeed, (struct Spline_s *)&v3[48].tQTaskChildren.ptTail, igi2_frame.nNow);
      }
      else
      {
        Spline_ExtraFromStart(&igi2_frame.ptPos, &igi2_frame.ptSpeed, (struct Spline_s *)&v3[48].tQTaskChildren.ptTail, igi2_frame.nNow);
      }
      Spline_Initialize(
        p_ptTail,
        &igi2_frame.ptPos,
        (struct real64x3_t *)&v3[52].tQTaskChildren,
        &igi2_frame.ptSpeed,
        &igi2_frame.tSplineSpeed,
        igi2_frame.nNow,
        150);
    }
    igi2_frame.ptCheckGrenade->nExplodeTimer = ptGameMessage->nExplodeTimer;
    igi2_frame.ptCheckGrenade->tPhysicsObj.nContact = ptGameMessage->nContact;
    igi2_frame.ptCheckGrenade->nLastReceivedRemoteTime = ptGameMessage->tBaseMessage.nLocalTime;
  }
}

// source: j/0/weapons/grenade.c:1067  [size]
__int16 __cdecl Grenade_GetGetGrenadeHeldTimeQTaskEvent()
{
  return Grenade_eGetGrenadeHeldTimeQTaskEvent;
}

// source: j/0/weapons/grenade.c:1082  [size]
__int16 __cdecl Grenade_GetSmokeAreaQTaskEvent()
{
  return Grenade_eSmokeAreaQTaskEvent;
}

// source: j/0/weapons/grenade.c:1104  [anchor-strings]
struct QTask_s *__cdecl Grenade_New(
        struct QTask_s *ptParent,
        unsigned __int8 iTaskID,
        struct QTask_s *ptCreator,
        struct real64x3_t *ptPos,
        struct real32x9_t *ptOrientation,
        struct real32x3_t *ptSpeed,
        struct WeaponType_s *ptWeaponType,
        int nExplodeTime)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[20]; struct real64x3_t tSplineSpeed; };
    struct { char igi2_o2[44]; struct real64x3_t v37; };
    struct { char igi2_o3[68]; struct real64x3_t v38; };
    char igi2_extent[96];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  DWORD PerformanceCounter; // eax
  int v9; // esi
  struct QTask_s *v10; // ebp
  double vX; // st7
  double vY; // st6
  double vZ; // st5
  int v14; // eax
  int v15; // ecx
  int v16; // ecx
  struct Spline_s *p_ptTail; // eax
  struct WeaponType_s *v18; // esi
  struct QTask_s *v19; // eax
  char *p_tQTaskRefList; // eax
  struct LODVirModel_s *LODVirModelExistsFn; // eax
  struct PhysicsObjType_s *Type; // edi
  double v23; // st7
  double v24; // st7
  int *v25; // eax
  int v26; // eax
  double v27; // st6
  bool v28; // zf
  float v29; // ecx
  double v30; // st7
  float v31; // edx
  double v32; // st6
  double v33; // st5

  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  v9 = PerformanceCounter - Timer_nStartTime;
  v10 = QTask_NewFn(ptParent, Grenade_eQTaskType, nullptr);
  v10[54].ptNext = (struct QTask_s *)iTaskID;
  v10[48].tQTaskChildren.ptHead = &ptWeaponType->tQTask;
  vX = ptSpeed->vX;
  vY = ptSpeed->vY;
  vZ = ptSpeed->vZ;
  v10[50].ptParent = (struct QTask_s *)-1;
  v14 = (int)v10[50].ptParent;
  igi2_frame.tSplineSpeed.vX = vX * 0.001;
  igi2_frame.tSplineSpeed.vY = vY * 0.001;
  igi2_frame.tSplineSpeed.vZ = vZ * 0.001;
  if ( v14 <= 0 )
  {
    Spline_Initialize(
      (struct Spline_s *)&v10[48].tQTaskChildren.ptTail,
      ptPos,
      ptPos,
      &igi2_frame.tSplineSpeed,
      &igi2_frame.tSplineSpeed,
      v9,
      100);
  }
  else
  {
    v15 = *(_DWORD *)&v10[50].eQTaskType;
    if ( v9 >= v15 )
    {
      v16 = v14 + v15;
      p_ptTail = (struct Spline_s *)&v10[48].tQTaskChildren.ptTail;
      if ( v9 <= v16 )
        Spline_OnSpline(&igi2_frame.v37, &igi2_frame.v38, p_ptTail, v9);
      else
        Spline_ExtraFromEnd(&igi2_frame.v37, &igi2_frame.v38, p_ptTail, v9);
      Spline_Initialize((struct Spline_s *)&v10[48].tQTaskChildren.ptTail, &igi2_frame.v37, ptPos, &igi2_frame.v38, &igi2_frame.tSplineSpeed, v9, 100);
    }
    else
    {
      Spline_ExtraFromStart(&igi2_frame.v37, &igi2_frame.v38, (struct Spline_s *)&v10[48].tQTaskChildren.ptTail, v9);
      Spline_Initialize((struct Spline_s *)&v10[48].tQTaskChildren.ptTail, &igi2_frame.v37, ptPos, &igi2_frame.v38, &igi2_frame.tSplineSpeed, v9, 100);
    }
  }
  if ( ptCreator )
    v10[48].ptNext = (struct QTask_s *)QTask_NewQTaskRef(ptCreator);
  else
    v10[48].ptNext = nullptr;
  v18 = ptWeaponType;
  v10[7].tQTaskChildren.ptHead = (struct QTask_s *)-1;
  v19 = TagItem_Find(&ptWeaponType->tQTask, (char *)&stru_6954D4);
  if ( v19 )
  {
    p_tQTaskRefList = (char *)&v19[7].tQTaskRefList;
    if ( !p_tQTaskRefList )
      p_tQTaskRefList = ptWeaponType->zFixedModel;
  }
  else
  {
    p_tQTaskRefList = (char *)&g_zInitialValue;
  }
  LODVirModelExistsFn = MTP_GetLODVirModelExistsFn(p_tQTaskRefList);
  if ( LODVirModelExistsFn != *(struct LODVirModel_s **)&v10[2].eQTaskType )
  {
    ModelObj_SetLODVirModel((struct ModelObj_s *)v10, LODVirModelExistsFn, false);
    v18 = ptWeaponType;
    v10[7].tQTaskRefList.ptHead = nullptr;
    v10[7].tQTaskRefList.ptMiddle = nullptr;
    v10[7].tQTaskRefList.ptTail = nullptr;
    v10[7].ptParent = nullptr;
    *(_DWORD *)&v10[7].eQTaskType = 0;
  }
  PhysicsObj_Create(v10);
  Type = PhysicsObjType_FindType(v18->zFixedModel);
  v10[47].tQTaskRefList.ptMiddle = nExplodeTime < 0 ? nullptr : (struct QReference_s *)nExplodeTime;
  if ( *(float *)&v10[6].tQTaskChildren.ptHead <= (double)*(float *)&v10[6].tQTaskChildren.ptMiddle )
    v23 = *(float *)&v10[6].tQTaskChildren.ptMiddle;
  else
    v23 = *(float *)&v10[6].tQTaskChildren.ptHead;
  if ( v23 >= *(float *)&v10[6].ptPrev )
  {
    if ( *(float *)&v10[6].tQTaskChildren.ptHead <= (double)*(float *)&v10[6].tQTaskChildren.ptMiddle )
      v24 = *(float *)&v10[6].tQTaskChildren.ptMiddle;
    else
      v24 = *(float *)&v10[6].tQTaskChildren.ptHead;
  }
  else
  {
    v24 = *(float *)&v10[6].ptPrev;
  }
  v25 = *(int **)&v10[2].eQTaskType;
  if ( v25 && (v26 = *v25) != 0 )
    v27 = *(float *)(*(_DWORD *)(*(_DWORD *)(v26 + 12) + 12) + 120);
  else
    v27 = 1.0;
  igi2_frame.ptDynCubeObj = v24 * v27;
  World_MoveDynCubeObjRadius(Game_ptGame->ptWorld, (struct DynCubeObj_s *)v10, ptPos, igi2_frame.ptDynCubeObj);
  PhysicsObj_Init(v10, Type);
  *(struct real32x3_t *)&v10[8].tQTaskRefList.ptMiddle = *ptSpeed;
  Physics_UpdateSpeedApproximation((struct Physics_s *)&v10[8]);
  v28 = Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER;
  qmemcpy(&v10[3].ptPrev, ptOrientation, sizeof(struct QTask_s));
  if ( v28 )
  {
    v29 = ptSpeed->vY;
    *(float *)&igi2_frame.tSplineSpeed.vX = ptSpeed->vX;
    v30 = *(float *)&igi2_frame.tSplineSpeed.vX * 4.5;
    v31 = ptSpeed->vZ;
    *((float *)&igi2_frame.tSplineSpeed.vX + 1) = v29;
    v32 = v29 * 4.5;
    v33 = v31 * 4.5;
    qmemcpy(&v10[51], ptPos, 0x18u);
    *(float *)&igi2_frame.tSplineSpeed.vY = v33;
    qmemcpy(&v10[52].tQTaskChildren, ptPos, 0x18u);
    *(double *)&v10[51].tQTaskRefList.ptMiddle = v30;
    *(double *)&v10[51].ptParent = v32;
    *(double *)&v10[52].ptNext = v33;
    *(double *)&v10[53].tQTaskChildren.ptTail = v30;
    *(double *)&v10[53].tQTaskRefList.ptMiddle = v32;
    *(double *)&v10[53].ptParent = v33;
    *(double *)&v10[52].ptParent = v30;
    *(double *)&v10[53].ptNext = v32;
    *(double *)&v10[53].tQTaskChildren.ptHead = *(float *)&igi2_frame.tSplineSpeed.vY;
  }
  return v10;
}

// source: j/0/weapons/grenade.c:1257  [anchor-hash]
unsigned __int8 __cdecl Grenade_GetNextTaskID()
{
  unsigned __int8 v0; // cl

  v0 = Grenade_nGrenadeID;
  if ( Grenade_nGrenadeID == 0xFF )
    v0 = 0;
  Grenade_nGrenadeID = v0 + 1;
  return v0;
}

// source: j/0/weapons/grenade.c:1275  [anchor-hash]
struct GrenadeType_s *__cdecl Grenade_GetGrenadeType(struct WeaponType_s *ptWeaponType)
{
  struct PhysicsObjType_s *Type; // eax

  Type = PhysicsObjType_FindType(ptWeaponType->zFixedModel);
  if ( Type )
    return (struct GrenadeType_s *)Type->pxData;
  else
    return nullptr;
}

// source: j/0/weapons/grenade.c:1301  [anchor-strings]
void __cdecl Grenade_Open()
{
  __int16 v0; // ax
  unsigned __int16 v1; // si
  _DWORD *v2; // esi

  Grenade_ptQTaskList = QTaskList_New(255);
  Grenade_eQTaskType = QTask_NewQTaskType("Grenade", 2184, PhysicsObj_eQTaskType, 0, 0);
  Grenade_eGrenadeParametersQTaskType = QTask_NewQTaskType(
                                          "GrenadeParameters",
                                          64,
                                          WeaponTypeParameters_eQTaskType,
                                          0,
                                          0);
  Grenade_eGetGrenadeHeldTimeQTaskEvent = QTask_NewQTaskEventFn(0, "GetGrenadeHeldTime");
  v0 = QTask_NewQTaskEventFn(0, "SmokeArea");
  v1 = Grenade_eQTaskType;
  Grenade_eSmokeAreaQTaskEvent = v0;
  QTask_LinkQTaskEventHandlerFn(Grenade_eQTaskType, 0, Grenade_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, Grenade_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, Grenade_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    GameFunctions_eWeaponHitQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Grenade_WeaponHitHandler);
  QTask_LinkQTaskEventHandlerFn(v1, GameFunctions_eExplosionHitQTaskEvent, Grenade_ExplosionHitHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    GameFunctions_eObjectCollisionEvaluateQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Grenade_ObjectCollisionEvaluateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    GameFunctions_eGetNextZEvaluateQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Grenade_GetNextZEvaluateHandler);
  QTask_LinkQTaskEventHandlerFn(v1, PhysicsObjType_eParsePhysicsObjTypeEvent, Grenade_ParsePhysicsObjTypeHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    PhysicsObjType_eGetPhysicsObjTypeSizeEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Grenade_GetGetPhysicsObjTypeSizeHandler);
  QTask_LinkQTaskEventHandlerFn(v1, WeaponType_eCreateParametersQTaskEvent, Grenade_CreateWeaponTypeParametersHandler);
  QTask_LinkQTaskEventHandlerFn(v1, Weapon_eCreateProjectileQTaskEvent, Grenade_CreateProjectileHandler);
  QTask_LinkQTaskEventHandlerFn(v1, Serialize_eDeSerializeDoneQTaskEvent, Grenade_DeSerializeDoneHandler);
  Symbol_Register(
    "TASKTYPE_GRENADE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)v1,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "GRENADE_EXPLOSIONTYPE_NORMAL",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    nullptr,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "GRENADE_EXPLOSIONTYPE_FLASHBANG",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)1,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "GRENADE_EXPLOSIONTYPE_SMOKE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)2,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Grenade_tGrenadeTypeEnumList.pfEnumItemsCallback = ParameterEnumList_EnumerateItemsCallback;
  Grenade_tGrenadeTypeEnumList.ptHead = (struct ParameterEnumItem_s *)&Grenade_tGrenadeTypeEnumList.ptMiddle;
  Grenade_tGrenadeTypeEnumList.ptTail = (struct ParameterEnumItem_s *)&Grenade_tGrenadeTypeEnumList;
  Grenade_tGrenadeTypeEnumList.ptMiddle = nullptr;
  v2 = Mem_AllocFn(18444, 4);
  v2[1] = 0;
  *v2 = 0;
  v2[4610] = "GRENADE_EXPLOSIONTYPE_.*";
  Wildcard_CreateNFA("GRENADE_EXPLOSIONTYPE_.*", v2 + 2, (char *)v2 + 10248);
  List_AddTail(v2, (int)&Grenade_tGrenadeTypeEnumList);
}

// source: j/0/weapons/grenade.c:1355  [anchor-hash]
void __cdecl Grenade_Close()
{
  QTaskList_Delete(Grenade_ptQTaskList);
  Symbol_Remove("GRENADE_EXPLOSIONTYPE_NORMAL");
  Symbol_Remove("GRENADE_EXPLOSIONTYPE_FLASHBANG");
  Symbol_Remove("GRENADE_EXPLOSIONTYPE_SMOKE");
  ParameterEnumList_DeAlloc(&Grenade_tGrenadeTypeEnumList);
  QTask_DeleteQTaskEvent(Grenade_eGetGrenadeHeldTimeQTaskEvent);
  QTask_DeleteQTaskEvent(Grenade_eSmokeAreaQTaskEvent);
  QTask_DeleteQTaskType(Grenade_eQTaskType);
  QTask_DeleteQTaskType(Grenade_eGrenadeParametersQTaskType);
}
