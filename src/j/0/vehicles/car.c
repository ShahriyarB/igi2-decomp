/* j/0/vehicles/car.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/vehicles/car.c:112  [anchor-mhash]
void __cdecl Car_Notify(struct QTask_s *ptQTask)
{
  double v1; // st7
  double v2; // st7
  int *v3; // edx
  int v4; // edx
  double v5; // st6
  struct QTaskList_s *v6; // eax
  int v7; // esi
  int v8; // edi
  struct NotifyContext_t tNotifyContext; // [esp+8h] [ebp-2Ch] BYREF

  tNotifyContext.ptQTask = ptQTask;
  qmemcpy(&tNotifyContext.tPos, &ptQTask[1], sizeof(tNotifyContext.tPos));
  tNotifyContext.tPos.vZ = tNotifyContext.tPos.vZ + 4096.0;
  if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
    v1 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  else
    v1 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  if ( v1 >= *(float *)&ptQTask[6].ptPrev )
  {
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
      v2 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v2 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  }
  else
  {
    v2 = *(float *)&ptQTask[6].ptPrev;
  }
  v3 = *(int **)&ptQTask[2].eQTaskType;
  if ( v3 && (v4 = *v3) != 0 )
    v5 = *(float *)(*(_DWORD *)(*(_DWORD *)(v4 + 12) + 12) + 120);
  else
    v5 = 1.0;
  v6 = GameFunctions_ptNotifyQTaskList;
  v7 = 0;
  tNotifyContext.vRadius = v2 * v5;
  if ( GameFunctions_ptNotifyQTaskList->nTask > 0 )
  {
    v8 = 8;
    do
    {
      ((void (__cdecl *)(_DWORD, struct NotifyContext_t *))QTask_aatQTaskFinalEvent[GameFunctions_eNotifyQTaskEvent][*(unsigned __int16 *)(*(int *)((char *)&v6->nTask + v8) + 36)].pfHandler)(
        *(int *)((char *)&v6->nTask + v8),
        &tNotifyContext);
      v6 = GameFunctions_ptNotifyQTaskList;
      ++v7;
      v8 += 4;
    }
    while ( v7 < GameFunctions_ptNotifyQTaskList->nTask );
  }
}

// source: j/0/vehicles/car.c:140  [anchor-strings]
void __cdecl Car_Explode(struct Car_s *ptCar)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vFullRange; };
    struct { char igi2_o1[4]; float vFallOffRange; };
    struct { char igi2_o2[8]; float vBurnRange; };
    struct { char igi2_o3[68]; float vRadius; };
    struct { char igi2_o4[72]; struct real64x3_t tExplosionPos; };
    char igi2_extent[100];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double vZ; // st7
  double vY; // st7
  struct LODVirModel_s *ptLODVirModel; // eax
  struct VirModel_s *v4; // eax
  double v5; // st6
  int nTicksToDie; // ecx
  char *pxData; // edx
  float v8; // eax
  int *v9; // ebp
  struct Game_s *v10; // eax
  unsigned int v11; // ebx
  unsigned int v12; // ecx
  unsigned int v13; // edx
  unsigned int v14; // esi
  struct QTask_s *v15; // eax

  if ( ptCar->isExplode )
  {
    if ( ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tScale.vY <= (double)ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tScale.vZ )
      vZ = ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tScale.vZ;
    else
      vZ = ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tScale.vY;
    if ( vZ >= ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tScale.vX )
    {
      if ( ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tScale.vY <= (double)ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tScale.vZ )
        vY = ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tScale.vZ;
      else
        vY = ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tScale.vY;
    }
    else
    {
      vY = ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tScale.vX;
    }
    ptLODVirModel = ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.ptLODVirModel;
    if ( ptLODVirModel && (v4 = ptLODVirModel->aptVirModel[0]) != nullptr )
      v5 = v4->ptModel->ptMesh->vRadius;
    else
      v5 = 1.0;
    nTicksToDie = ptCar->nTicksToDie;
    pxData = (char *)ptCar->tVehicle.tPhysicsObj.ptType->pxData;
    v8 = *((float *)pxData + 171);
    igi2_frame.vRadius = vY * v5;
    if ( nTicksToDie == -1 )
    {
      if ( v8 == 0.0 )
      {
        igi2_frame.vBurnRange = igi2_frame.vRadius * 0.004999999888241291;
        igi2_frame.vFallOffRange = igi2_frame.vRadius * 0.05000000074505806;
        igi2_frame.vFullRange = igi2_frame.vRadius * 0.25;
        Explosion0_New(
          &ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos,
          1,
          0,
          1.0,
          igi2_frame.vFullRange,
          igi2_frame.vFallOffRange,
          igi2_frame.vBurnRange,
          3,
          1,
          nullptr,
          "1009_01_1",
          "explo_03_l",
          20,
          0x402u,
          307200.0,
          nullptr,
          nullptr,
          EXPLOSIONDAMAGE_LINEAR_FALLOFF);
        ptCar->nTicksToDie = 10;
      }
      else
      {
        if ( SLODWORD(v8) > 0 )
        {
          v9 = (int *)(pxData + 644);
          igi2_frame.vRadius = v8;
          do
          {
            v10 = Game_ptGame;
            v11 = (Game_ptGame->tRunRandomState.anRandom[0] >> 7) ^ Game_ptGame->tRunRandomState.anRandom[2];
            v12 = v11 ^ Game_ptGame->tRunRandomState.anRandom[1];
            v13 = v12 + Game_ptGame->tRunRandomState.anRandom[0];
            Game_ptGame->tRunRandomState.anRandom[1] = v12;
            v10->tRunRandomState.anRandom[0] = v13;
            v10->tRunRandomState.anRandom[2] = v11;
            v14 = v13;
            GameFunctions_GetMagicVertex(
              &igi2_frame.tExplosionPos,
              &ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask,
              *v9);
            Explosion0_New(
              &igi2_frame.tExplosionPos,
              1,
              v14 % 0x1E,
              3.0,
              24576.0,
              6144.0,
              6144.0,
              3,
              2,
              nullptr,
              "1009_01_1",
              "explo_03_l",
              20,
              0x402u,
              307200.0,
              nullptr,
              nullptr,
              EXPLOSIONDAMAGE_LINEAR_FALLOFF);
            ++v9;
            --LODWORD(igi2_frame.vRadius);
          }
          while ( igi2_frame.vRadius != 0.0 );
        }
        ptCar->nTicksToDie = 30;
      }
    }
    else
    {
      ptCar->nTicksToDie = nTicksToDie - 1;
      if ( nTicksToDie == 1 )
      {
        v15 = EditRigidObj_New(
                Level_ptDynamicQTask,
                pxData + 688,
                &ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos,
                &ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation);
        if ( v15 )
          ptCar->ptExplodedCarModelRef = QTask_NewQTaskRef(v15);
        igi2_frame.vRadius = *(float *)&Game_ptGame->ptWorld;
        QTask_DeleteQTaskAndQTaskRefSafe(&ptCar->ptEngineSoundRef);
        if ( ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.ptMagicObjContainer )
        {
          QTask_Delete(ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.ptMagicObjContainer);
          ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.ptMagicObjContainer = nullptr;
        }
        Car_RemoveHandler(&ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask, &igi2_frame.vRadius);
        ptCar->isExploded = 1;
      }
    }
  }
}

// source: j/0/vehicles/car.c:282  [anchor-mhash]
void __cdecl Car_OpenDoor(struct Car_s *ptCar)
{
  int v1; // ebx
  struct QTask_s *FirstChildOfType; // eax

  if ( ptCar->tOpenDoorExpression.zExpression
    && *ptCar->tOpenDoorExpression.zCompiledExpression
    && ptCar->tOpenDoorExpression.ptExpression )
  {
    v1 = (__int64)Level_RunLevelExpression(
                    &ptCar->tOpenDoorExpression,
                    &ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask);
    FirstChildOfType = QTask_GetFirstChildOfType(
                         ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.ptMagicObjContainer,
                         CarDoor_eQTaskType);
    if ( FirstChildOfType )
      LOBYTE(FirstChildOfType[8].tQTaskChildren.ptTail) = v1;
  }
}

// source: j/0/vehicles/car.c:311  [anchor-mhash]
void __cdecl Car_RunDetection(struct Car_s *ptCar)
{
  char v1; // al
  struct QTask_s *FirstChildOfType; // esi
  struct real32x9_t *p_ptTail; // esi
  int isLastFire; // [esp+Ch] [ebp-10h]

  if ( ptCar->tCanFireExpression.zExpression
    && *ptCar->tCanFireExpression.zCompiledExpression
    && ptCar->tCanFireExpression.ptExpression )
  {
    isLastFire = ptCar->isFire;
    v1 = (__int64)Level_RunLevelExpression(
                    &ptCar->tCanFireExpression,
                    &ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask);
    ptCar->isFire = v1;
    if ( v1 )
    {
      FirstChildOfType = QTask_GetFirstChildOfType(
                           ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.ptMagicObjContainer,
                           AIStationaryGun_eQTaskType);
      if ( FirstChildOfType )
      {
        AIStationaryGun_GetMuzzlePosition(FirstChildOfType, &ptCar->tAIDetectionView.tViewPosition);
        p_ptTail = (struct real32x9_t *)&FirstChildOfType[10].tQTaskChildren.ptTail;
      }
      else
      {
        qmemcpy(
          &ptCar->tAIDetectionView,
          &ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos,
          0x18u);
        p_ptTail = &ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation;
      }
      qmemcpy(&ptCar->tAIDetectionView.tViewOrientation, p_ptTail, sizeof(ptCar->tAIDetectionView.tViewOrientation));
      ptCar->tAIDetectionView.isSecondaryViewUsed = 0;
      AIDetection_RunDetection(
        &ptCar->tAIDetection,
        &ptCar->tAIDetectionView,
        &ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask,
        1);
    }
    if ( !ptCar->isFire )
    {
      if ( isLastFire )
      {
        AIDetection_ClearDetection(&ptCar->tAIDetection);
        AIDetection_InitDetection(&ptCar->tAIDetection, 1, 4u, Human_bAIDetectionQTaskMask, 4, 8);
      }
    }
  }
}

// source: j/0/vehicles/car.c:370  [anchor-mhash]
void __cdecl Car_AdjustWheelCollPoints(struct Car_s *ptCar)
{
  struct PhysicsObjType_s *ptType; // eax
  char *pxData; // ecx
  int v3; // edx
  int *v4; // esi

  ptType = ptCar->tVehicle.tPhysicsObj.ptType;
  if ( ptType )
  {
    pxData = (char *)ptType->pxData;
    v3 = 0;
    if ( *((int *)pxData + 70) > 0 )
    {
      v4 = (int *)(pxData + 292);
      do
      {
        if ( *v4 >= 0 )
          ptCar->tVehicle.tPhysicsObj.atCollPoint[*v4].tPos.vZ = ptCar->tVehicle.tPhysicsObj.atCollPoint[*v4].tPos.vZ
                                                               - *((float *)pxData + 151);
        ++v3;
        v4 += 5;
      }
      while ( v3 < (int)(*((_DWORD *)pxData + 70)) );
    }
  }
}

// source: j/0/vehicles/car.c:405  [anchor-caller]
void __cdecl Car_AddSpringForces(struct Car_s *ptCar)
{
  #pragma pack(push, 1)
  union
  {
    struct { unsigned int nCollisionTaskGroups; };
    struct { char igi2_o1[4]; float ptDynCubeObj; };
    struct { char igi2_o2[24]; float *vMaxDistance; };
    struct { char igi2_o3[24]; float vMaxDistancea; };
    struct { char igi2_o4[28]; int iWheel; };
    struct { char igi2_o5[28]; int iWheela; };
    struct { char igi2_o6[32]; struct CarWheelState_s *v42; };
    struct { char igi2_o7[32]; double *v43; };
    struct { char igi2_o8[36]; int nCollPoint; };
    struct { char igi2_o9[40]; int iCollPoint; };
    struct { char igi2_o10[40]; float iCollPointa; };
    struct { char igi2_o11[44]; int iCollPointCount; };
    struct { char igi2_o12[48]; int isHardCollision; };
    struct { char igi2_o13[52]; struct CarType_s *ptCarType; };
    struct { char igi2_o14[56]; struct real64x3_t Real64x3_Rotate_tTemp; };
    struct { char igi2_o15[80]; double vMaxHardCollisionDistance; };
    struct { char igi2_o16[92]; struct PhysicsObjType_s *ptType; };
    struct { char igi2_o17[96]; struct CollisionEvaluateContext_s tContext; };
    struct { char igi2_o18[104]; int aiWheelIndex[16]; };
    struct { char igi2_o19[168]; struct real64x3_t atCheckPointWorldStartSuspension[16]; };
    struct { char igi2_o20[552]; struct real64x3_t atCheckPointWorldStopSuspension[16]; };
    struct { char igi2_o21[936]; struct QIntersection_s atIntersectionSuspension[16]; };
    char igi2_extent[2856];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char *pxData; // esi
  int v2; // edi
  bool v3; // cc
  struct CarWheelState_s *atWheelState; // edx
  float *v5; // ecx
  unsigned int v6; // ebx
  int v7; // eax
  int v8; // eax
  double v9; // st7
  double vZ; // st6
  struct real64x3_t *v11; // esi
  double v12; // st6
  struct real64x3_t *v13; // edi
  double *p_vDistance; // edi
  double v15; // st7
  int v16; // edx
  int v17; // ebx
  int v18; // ecx
  double v19; // st6
  double v20; // st6
  float vY; // ecx
  int nForces; // eax
  double v23; // st6
  char *v24; // esi
  double v25; // st6
  char *v26; // ecx
  double *v27; // edi
  long double v28; // st7
  _DWORD *v29; // ecx
  _DWORD *v30; // esi
  double v31; // st7
  double vX; // st7
  struct LODVirModel_s *ptLODVirModel; // eax
  struct VirModel_s *v34; // eax
  double vRadius; // st6

  pxData = (char *)ptCar->tVehicle.tPhysicsObj.ptType->pxData;
  v2 = 0;
  igi2_frame.ptType = ptCar->tVehicle.tPhysicsObj.ptType;
  v3 = (int)(*((_DWORD *)pxData + 70)) <= 0;
  igi2_frame.ptCarType = (struct CarType_s *)pxData;
  igi2_frame.nCollPoint = 0;
  igi2_frame.isHardCollision = 0;
  igi2_frame.vMaxHardCollisionDistance = -1.7976931348623157e+308;
  igi2_frame.iWheel = 0;
  if ( !v3 )
  {
    atWheelState = ptCar->atWheelState;
    v5 = (float *)(pxData + 296);
    igi2_frame.v42 = ptCar->atWheelState;
    igi2_frame.vMaxDistance = (float *)(pxData + 296);
    v6 = 0;
    while ( 1 )
    {
      v7 = *((_DWORD *)v5 - 1);
      igi2_frame.iCollPoint = v7;
      if ( v7 >= 0 )
      {
        if ( !atWheelState->isAttached )
          goto LABEL_7;
        v8 = v7;
        v9 = *v5 + 2048.0;
        igi2_frame.atCheckPointWorldStartSuspension[v6 / 0x18].vX = ptCar->tVehicle.tPhysicsObj.atCollPoint[v8].tPos.vX;
        igi2_frame.atCheckPointWorldStartSuspension[v6 / 0x18].vY = ptCar->tVehicle.tPhysicsObj.atCollPoint[v8].tPos.vY;
        vZ = ptCar->tVehicle.tPhysicsObj.atCollPoint[v8].tPos.vZ;
        igi2_frame.atCheckPointWorldStartSuspension[v6 / 0x18].vZ = vZ;
        igi2_frame.Real64x3_Rotate_tTemp.vX = ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vZ * vZ
                                 + ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vY
                                 * igi2_frame.atCheckPointWorldStartSuspension[v6 / 0x18].vY
                                 + ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vX
                                 * igi2_frame.atCheckPointWorldStartSuspension[v6 / 0x18].vX;
        igi2_frame.Real64x3_Rotate_tTemp.vY = ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vZ * vZ
                                 + ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vY
                                 * igi2_frame.atCheckPointWorldStartSuspension[v6 / 0x18].vY
                                 + ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vX
                                 * igi2_frame.atCheckPointWorldStartSuspension[v6 / 0x18].vX;
        igi2_frame.Real64x3_Rotate_tTemp.vZ = ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vZ * vZ
                                 + ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vY
                                 * igi2_frame.atCheckPointWorldStartSuspension[v6 / 0x18].vY
                                 + ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vX
                                 * igi2_frame.atCheckPointWorldStartSuspension[v6 / 0x18].vX;
        qmemcpy(&igi2_frame.atCheckPointWorldStartSuspension[v6 / 0x18], &igi2_frame.Real64x3_Rotate_tTemp, sizeof(struct real64x3_t));
        igi2_frame.atCheckPointWorldStartSuspension[v6 / 0x18].vX = ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vX
                                                       + igi2_frame.atCheckPointWorldStartSuspension[v6 / 0x18].vX;
        igi2_frame.atCheckPointWorldStartSuspension[v6 / 0x18].vY = ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vY
                                                       + igi2_frame.atCheckPointWorldStartSuspension[v6 / 0x18].vY;
        v11 = &igi2_frame.atCheckPointWorldStartSuspension[v6 / 0x18];
        v12 = ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vZ
            + igi2_frame.atCheckPointWorldStartSuspension[v6 / 0x18].vZ;
        v13 = &igi2_frame.atCheckPointWorldStopSuspension[v6 / 0x18];
        ++igi2_frame.nCollPoint;
        igi2_frame.atCheckPointWorldStartSuspension[v6 / 0x18].vZ = v12;
        v6 += 24;
        *(double *)&igi2_frame.aiWheelIndex[v6 / 4 + 14] = *igi2_frame.vMaxDistance + v12 + 4096.0;
        qmemcpy(v13, v11, sizeof(struct real64x3_t));
        igi2_frame.atCheckPointWorldStartSuspension[v6 / 0x18 + 15].vZ = igi2_frame.atCheckPointWorldStartSuspension[v6 / 0x18 + 15].vZ
                                                            - v9
                                                            - 4096.0;
        v5 = igi2_frame.vMaxDistance;
        pxData = (char *)igi2_frame.ptCarType;
        ptCar->tVehicle.tPhysicsObj.atCollPoint[v8].isActive = 0;
        *((_DWORD *)&igi2_frame.tContext.ptQTask + igi2_frame.nCollPoint) = igi2_frame.iWheel;
        atWheelState = igi2_frame.v42;
        v7 = igi2_frame.iCollPoint;
      }
      if ( !atWheelState->isAttached )
LABEL_7:
        ptCar->tVehicle.tPhysicsObj.atCollPoint[v7].isActive = 1;
      v5 += 5;
      ++atWheelState;
      v3 = ++igi2_frame.iWheel < (int)(*((_DWORD *)pxData + 70));
      igi2_frame.vMaxDistance = v5;
      igi2_frame.v42 = atWheelState;
      if ( !v3 )
      {
        v2 = igi2_frame.nCollPoint;
        break;
      }
    }
  }
  igi2_frame.nCollisionTaskGroups = ptCar->tVehicle.tPhysicsObj.nCollisionTaskGroups;
  igi2_frame.tContext.ptQTask = &ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask;
  World_TraceLinesSpecificMesh(
    Game_ptGame->ptWorld,
    igi2_frame.atIntersectionSuspension,
    igi2_frame.atCheckPointWorldStartSuspension,
    igi2_frame.atCheckPointWorldStopSuspension,
    v2,
    13,
    &igi2_frame.tContext,
    igi2_frame.nCollisionTaskGroups,
    1);
  igi2_frame.iCollPointCount = 0;
  if ( v2 <= 0 )
    return;
  p_vDistance = &igi2_frame.atIntersectionSuspension[0].vDistance;
  igi2_frame.v43 = &igi2_frame.atIntersectionSuspension[0].vDistance;
  while ( 1 )
  {
    v15 = 0.0;
    v16 = igi2_frame.aiWheelIndex[igi2_frame.iCollPointCount];
    igi2_frame.vMaxDistancea = *(float *)&pxData[20 * v16 + 296];
    igi2_frame.iWheela = *(_DWORD *)&pxData[20 * v16 + 292];
    v17 = 0;
    v18 = 0;
    if ( !*((_DWORD *)p_vDistance - 1) )
      goto LABEL_23;
    if ( *p_vDistance >= 4096.0 )
    {
      if ( *p_vDistance <= 4096.0 )
        goto LABEL_23;
      v20 = igi2_frame.vMaxDistancea + 4096.0;
      if ( v20 <= *p_vDistance )
        goto LABEL_23;
      v17 = 1;
      igi2_frame.iCollPointa = v20;
      v15 = igi2_frame.iCollPointa - *p_vDistance;
    }
    else
    {
      v18 = 1;
      v15 = igi2_frame.vMaxDistancea;
      igi2_frame.isHardCollision = 1;
      v17 = 1;
      v19 = 4096.0 - *p_vDistance;
      if ( igi2_frame.vMaxHardCollisionDistance < v19 )
        igi2_frame.vMaxHardCollisionDistance = v19;
    }
    igi2_frame.Real64x3_Rotate_tTemp.vX = 0.0;
    *(float *)&igi2_frame.Real64x3_Rotate_tTemp.vY = v15
                                        / igi2_frame.vMaxDistancea
                                        * *(float *)&pxData[20 * v16 + 300]
                                        * igi2_frame.ptType->vMass
                                        * 44.600887298583984;
    if ( v18 )
      *(float *)&igi2_frame.Real64x3_Rotate_tTemp.vY = (2.0 - *p_vDistance * 0.000244140625) * *(float *)&igi2_frame.Real64x3_Rotate_tTemp.vY;
    HIDWORD(igi2_frame.Real64x3_Rotate_tTemp.vY) = LODWORD(ptCar->tVehicle.tPhysicsObj.atCollPoint[igi2_frame.iWheela].tPos.vX);
    vY = ptCar->tVehicle.tPhysicsObj.atCollPoint[igi2_frame.iWheela].tPos.vY;
    HIDWORD(igi2_frame.Real64x3_Rotate_tTemp.vZ) = LODWORD(ptCar->tVehicle.tPhysicsObj.atCollPoint[igi2_frame.iWheela].tPos.vZ);
    nForces = ptCar->tVehicle.tPhysicsObj.tPhysics.nForces;
    *(float *)&igi2_frame.Real64x3_Rotate_tTemp.vZ = vY;
    qmemcpy(
      &ptCar->tVehicle.tPhysicsObj.tPhysics.ptForces[nForces],
      &igi2_frame.Real64x3_Rotate_tTemp,
      sizeof(ptCar->tVehicle.tPhysicsObj.tPhysics.ptForces[nForces]));
    p_vDistance = igi2_frame.v43;
    ++ptCar->tVehicle.tPhysicsObj.tPhysics.nForces;
LABEL_23:
    v23 = ptCar->tVehicle.tPhysicsObj.atCollPoint[igi2_frame.iWheela].vZDisplacement - v15;
    v24 = (char *)ptCar + 56 * igi2_frame.iWheela;
    if ( v23 < 0.0 )
      v23 = -v23;
    if ( v23 > 0.0010000000474974513 )
    {
      v25 = *((float *)v24 + 145);
      if ( v15 <= v25 )
        *((float *)v24 + 145) = v25 * 0.05000000074505806 + v15 * 0.949999988079071;
      else
        *((float *)v24 + 145) = v15;
    }
    v26 = (char *)ptCar + 28 * v16;
    v26[1965] = v17;
    v24[554] = v17;
    if ( v17 )
    {
      v27 = p_vDistance - 5;
      *((_DWORD *)v26 + 492) = *(_DWORD *)v27;
      *((_DWORD *)v26 + 493) = *((_DWORD *)v27 + 1);
      *((_DWORD *)v26 + 494) = *((_DWORD *)v27 + 2);
      if ( *((float *)v26 + 492) != 0.0 || *((float *)v26 + 493) != 0.0 || *((float *)v26 + 494) != 0.0 )
      {
        v28 = 1.0
            / sqrt(
                *((float *)v26 + 492) * *((float *)v26 + 492)
              + *((float *)v26 + 493) * *((float *)v26 + 493)
              + *((float *)v26 + 494) * *((float *)v26 + 494));
        *((float *)v26 + 492) = *((float *)v26 + 492) * v28;
        *((float *)v26 + 493) = *((float *)v26 + 493) * v28;
        *((float *)v26 + 494) = *((float *)v26 + 494) * v28;
      }
      v29 = v26 + 1980;
      v30 = v24 + 540;
      *v29 = *v30;
      v29[1] = v30[1];
      v29[2] = v30[2];
      ptCar->atWheelState[v16].tContactPoint.vZ = ptCar->atWheelState[v16].tContactPoint.vZ + 1638.4000244140625;
      ptCar->tVehicle.tPhysicsObj.nContact = 1;
      Wheel_AddForces(ptCar, v16, igi2_frame.iWheela);
      p_vDistance = igi2_frame.v43;
    }
    p_vDistance += 15;
    v3 = ++igi2_frame.iCollPointCount < igi2_frame.nCollPoint;
    igi2_frame.v43 = p_vDistance;
    if ( !v3 )
      break;
    pxData = (char *)igi2_frame.ptCarType;
  }
  if ( igi2_frame.isHardCollision )
  {
    qmemcpy(
      &igi2_frame.Real64x3_Rotate_tTemp,
      &ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos,
      sizeof(igi2_frame.Real64x3_Rotate_tTemp));
    igi2_frame.Real64x3_Rotate_tTemp.vZ = igi2_frame.Real64x3_Rotate_tTemp.vZ + igi2_frame.vMaxHardCollisionDistance;
    if ( ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tScale.vY <= (double)ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tScale.vZ )
      v31 = ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tScale.vZ;
    else
      v31 = ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tScale.vY;
    if ( v31 >= ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tScale.vX )
    {
      if ( ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tScale.vY <= (double)ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tScale.vZ )
        vX = ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tScale.vZ;
      else
        vX = ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tScale.vY;
    }
    else
    {
      vX = ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tScale.vX;
    }
    ptLODVirModel = ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.ptLODVirModel;
    if ( ptLODVirModel && (v34 = ptLODVirModel->aptVirModel[0]) != nullptr )
      vRadius = v34->ptModel->ptMesh->vRadius;
    else
      vRadius = 1.0;
    igi2_frame.ptDynCubeObj = vX * vRadius;
    World_MoveDynCubeObjRadius(
      Game_ptGame->ptWorld,
      &ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj,
      &igi2_frame.Real64x3_Rotate_tTemp,
      igi2_frame.ptDynCubeObj);
  }
}

// source: j/0/vehicles/car.c:658  [anchor-mhash]
void __cdecl Car_SetWheelCount(struct Car_s *ptCar)
{
  struct PhysicsObjType_s *ptType; // eax
  char *pxData; // eax
  int v3; // edi
  struct CarWheelState_s *atWheelState; // ecx
  _BYTE *v5; // esi

  ptType = ptCar->tVehicle.tPhysicsObj.ptType;
  ptCar->nWheel = 0;
  ptCar->nEngineWheel = 0;
  ptCar->nSteeringWheel = 0;
  if ( ptType )
  {
    pxData = (char *)ptType->pxData;
    if ( !pxData[608] )
      ptCar->nWheel = *((_DWORD *)pxData + 70);
    v3 = 0;
    if ( *((int *)pxData + 70) > 0 )
    {
      atWheelState = ptCar->atWheelState;
      v5 = pxData + 284;
      do
      {
        if ( v5[1] )
          ++ptCar->nEngineWheel;
        if ( *v5 )
          ++ptCar->nSteeringWheel;
        atWheelState->isAttached = pxData[608] == 0;
        ++v3;
        v5 += 20;
        ++atWheelState;
      }
      while ( v3 < (int)(*((_DWORD *)pxData + 70)) );
    }
  }
}

// source: j/0/vehicles/car.c:715  [anchor-mhash]
void __cdecl Car_Init(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct World_s *ptDynCubeObj; };
    struct { float ptDynCubeObja; };
    struct { char igi2_o2[16]; struct real64x3_t tVNull; };
    char igi2_extent[44];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v1; // st7
  double v2; // st7
  int *v3; // eax
  int v4; // eax
  double v5; // st6
  struct QReference_s *v6; // eax
  struct QTaskList_s *v7; // eax
  __int16 v8; // cx

  igi2_frame.ptDynCubeObj = Game_ptGame->ptWorld;
  memset(&igi2_frame.tVNull, 0, sizeof(igi2_frame.tVNull));
  ModelObj_Init((struct ModelObj_s *)ptQTask, igi2_frame.ptDynCubeObj, nullptr);
  ptQTask[7].tQTaskChildren.ptHead = nullptr;
  ptQTask[7].tQTaskChildren.ptMiddle = (struct QTask_s *)2;
  ptQTask[7].tQTaskRefList.ptHead = nullptr;
  ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[7].tQTaskRefList.ptTail = nullptr;
  ptQTask[7].ptParent = nullptr;
  *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
    v1 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  else
    v1 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  if ( v1 >= *(float *)&ptQTask[6].ptPrev )
  {
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
      v2 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v2 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  }
  else
  {
    v2 = *(float *)&ptQTask[6].ptPrev;
  }
  v3 = *(int **)&ptQTask[2].eQTaskType;
  if ( v3 && (v4 = *v3) != 0 )
    v5 = *(float *)(*(_DWORD *)(*(_DWORD *)(v4 + 12) + 12) + 120);
  else
    v5 = 1.0;
  igi2_frame.ptDynCubeObja = v2 * v5;
  World_RegisterDynCubeObjFirstTimeRadius(
    Game_ptGame->ptWorld,
    (struct DynCubeObj_s *)ptQTask,
    &igi2_frame.tVNull,
    igi2_frame.ptDynCubeObja,
    WORLD_DYNCUBETREE_CATEGORY_MOBILE);
  v6 = (struct QReference_s *)Mem_AllocFn(16, 4);
  if ( v6 )
  {
    v6->ptNext = (struct QReference_s *)3;
    v6->ptPrev = nullptr;
    v6->pxObject = nullptr;
    v6[1].ptNext = nullptr;
  }
  ptQTask[48].tQTaskRefList.ptTail = v6;
  ptQTask[48].tQTaskRefList.ptMiddle = nullptr;
  LOBYTE(ptQTask[10].tQTaskRefList.ptHead) = 0;
  *(_DWORD *)&ptQTask[48].eQTaskType = 0;
  ptQTask[48].ptParent = nullptr;
  ptQTask[49].ptNext = nullptr;
  Vehicle_Create((struct Vehicle_s *)ptQTask);
  v7 = GameFunctions_ptVehicleQTaskList;
  ptQTask[48].tQTaskChildren.ptTail = nullptr;
  BYTE1(ptQTask[60].tQTaskChildren.ptMiddle) = 0;
  ptQTask[60].tQTaskRefList.ptHead = (struct QReference_s *)-1;
  QTaskList_Register(v7, (struct QTaskList_s *)ptQTask);
  LOBYTE(ptQTask[60].tQTaskChildren.ptMiddle) = 0;
  BYTE1(ptQTask[570].ptParent) = 0;
  ptQTask[60].tQTaskChildren.ptTail = (struct QTask_s *)-1;
  ptQTask[60].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[60].tQTaskRefList.ptTail = nullptr;
  ptQTask[60].ptParent = nullptr;
  ptQTask[62].tQTaskRefList.ptHead = nullptr;
  ptQTask[62].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[62].tQTaskRefList.ptTail = nullptr;
  ptQTask[62].ptParent = nullptr;
  ptQTask[64].tQTaskRefList.ptHead = nullptr;
  ptQTask[64].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[64].tQTaskRefList.ptTail = nullptr;
  ptQTask[64].ptParent = nullptr;
  ptQTask[66].tQTaskRefList.ptHead = nullptr;
  ptQTask[570].tQTaskChildren.ptTail = (struct QTask_s *)1112014848;
  LOBYTE(ptQTask[570].tQTaskRefList.ptHead) = 1;
  ptQTask[570].tQTaskRefList.ptMiddle = nullptr;
  LOBYTE(ptQTask[570].ptParent) = 0;
  ptQTask[572].ptNext = (struct QTask_s *)10000;
  *(_DWORD *)&ptQTask[573].eQTaskType = 1148846080;
  ptQTask[571].ptParent = nullptr;
  ptQTask[570].tQTaskChildren.ptHead = (struct QTask_s *)1119092736;
  ptQTask[570].tQTaskChildren.ptMiddle = (struct QTask_s *)1119092736;
  ptQTask[571].tQTaskRefList.ptTail = (struct QReference_s *)1119092736;
  ptQTask[572].ptPrev = (struct QTask_s *)1135869952;
  ptQTask[572].tQTaskChildren.ptHead = (struct QTask_s *)1135869952;
  *(_DWORD *)&ptQTask[571].eQTaskType = 1135869952;
  strcpy((char *)&ptQTask[570].eQTaskType, "661_04_1");
  LOBYTE(ptQTask[572].tQTaskChildren.ptMiddle) = 0;
  ptQTask[574].ptNext = (struct QTask_s *)1050253722;
  strcpy((char *)&ptQTask[573].ptPrev, "WEAPON_ID_M2HB");
  v8 = Attach_eAttachEvent;
  ptQTask[5].tQTaskChildren.ptTail = (struct QTask_s *)-1;
  ptQTask[570].tQTaskRefList.ptTail = nullptr;
  ptQTask[5].tQTaskRefList.ptHead = nullptr;
  QTask_TriggerQTaskEventParent(ptQTask, v8, &ptQTask[5].tQTaskChildren.ptTail);
  ModelObj_CalcRelativePosAndOrientation((struct ModelObj_s *)ptQTask);
}

// source: j/0/vehicles/car.c:823  [size]
void __cdecl Car_GetGunParametersHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = (char *)ptQTask + 22836;
}

// source: j/0/vehicles/car.c:843  [size]
void __cdecl Car_WeaponCollisionEvaluateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_BYTE *)pxContext = ptQTask != *((struct QTask_s **)pxContext + 1)
                     && ptQTask != *((struct QTask_s **)pxContext + 2)
                     && ptQTask != *((struct QTask_s **)pxContext + 3);
}

// source: j/0/vehicles/car.c:872  [anchor-caller]
void __cdecl Car_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  Car_Init(ptQTask);
  QTaskList_Register(GameFunctions_ptExplosionQTaskList, (struct QTaskList_s *)ptQTask);
}

// source: j/0/vehicles/car.c:889  [size]
void __cdecl Car_RunHandler(struct QTask_s *ptQTask)
{
  struct QReference_s *nTicks; // eax
  struct QReference_s *ptMiddle; // eax
  int v3; // eax
  struct QTask_s *v4; // eax
  struct QTask_s *ptHead; // edx
  int v6; // eax
  struct QTask_s *v7; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *); // ecx
  int v9; // eax
  struct QTask_s *ptNext; // ecx
  int v11; // edx
  struct QTask_s *v12; // ecx
  void (__cdecl *v13)(int); // ecx
  int v14; // eax
  struct QTask_s *v15; // ecx
  int v16; // edx
  struct QTask_s *v17; // ecx
  void (__cdecl *v18)(int, struct UpdateMagicObjContext_t *); // ecx
  int v19; // eax
  struct QTask_s *i; // esi
  struct UpdateMagicObjContext_t tUpdateMagicObjContext; // [esp+10h] [ebp-10h] BYREF

  nTicks = (struct QReference_s *)Flow_ptFlow->nTicks;
  if ( ptQTask[60].tQTaskRefList.ptHead != nTicks )
  {
    ptQTask[60].tQTaskRefList.ptHead = nTicks;
    if ( !BYTE1(ptQTask[570].ptParent) )
    {
      Car_Notify(ptQTask);
      if ( ptQTask[64].tQTaskRefList.ptMiddle
        && ptQTask[64].tQTaskRefList.ptTail->ptNext
        && ptQTask[64].ptParent
        && (*(_QWORD *)&tUpdateMagicObjContext.ptParentPos = (__int64)Level_RunLevelExpression(
                                                                        (struct LevelExpression_s *)&ptQTask[64].tQTaskRefList.ptMiddle,
                                                                        ptQTask),
            !tUpdateMagicObjContext.ptParentPos) )
      {
        QTask_DeleteQTaskAndQTaskRefSafe(&ptQTask[48].tQTaskRefList.ptMiddle);
      }
      else
      {
        ptMiddle = ptQTask[48].tQTaskRefList.ptMiddle;
        if ( !ptMiddle || !ptMiddle->pxObject )
        {
          v3 = *(_DWORD *)&ptQTask[12].eQTaskType;
          if ( v3 )
          {
            v4 = SoundSys_NewSoundFn(ptQTask, (char *)(*(_DWORD *)(v3 + 724) + 610));
            if ( v4 )
              ptQTask[48].tQTaskRefList.ptMiddle = QTask_NewQTaskRef(v4);
          }
        }
      }
      Car_OpenDoor((struct Car_s *)ptQTask);
      Car_RunDetection((struct Car_s *)ptQTask);
      ptHead = ptQTask->tQTaskChildren.ptHead;
      if ( ptHead->ptNext && ptHead )
      {
        v6 = QTask_nProtectedQTaskStackOffset;
        do
        {
          if ( ptHead->ptNext )
            v7 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
          else
            v7 = nullptr;
          QTask_atProtectedQTaskStack[v6].ptQTask = v7;
          pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][ptHead->eQTaskType].pfHandler;
          v9 = v6 + 1;
          QTask_nProtectedQTaskStackOffset = v9;
          if ( pfHandler )
          {
            pfHandler(ptHead);
            v9 = QTask_nProtectedQTaskStackOffset;
          }
          ptHead = (struct QTask_s *)dword_849C7DC[v9];
          v6 = v9 - 1;
          QTask_nProtectedQTaskStackOffset = v6;
        }
        while ( ptHead );
      }
      else
      {
        v6 = QTask_nProtectedQTaskStackOffset;
      }
      ptNext = ptQTask[3].ptNext;
      if ( ptNext )
      {
        v11 = (int)ptNext->tQTaskChildren.ptHead;
        if ( *(_DWORD *)v11 )
        {
          for ( ; v11; QTask_nProtectedQTaskStackOffset = v6 )
          {
            if ( *(_DWORD *)v11 )
              v12 = **(_DWORD **)v11 != 0 ? *(struct QTask_s **)v11 : nullptr;
            else
              v12 = nullptr;
            QTask_atProtectedQTaskStack[v6].ptQTask = v12;
            v13 = (void (__cdecl *)(int))QTask_aatQTaskFinalEvent[1][*(unsigned __int16 *)(v11 + 36)].pfHandler;
            v14 = v6 + 1;
            QTask_nProtectedQTaskStackOffset = v14;
            if ( v13 )
            {
              v13(v11);
              v14 = QTask_nProtectedQTaskStackOffset;
            }
            v11 = dword_849C7DC[v14];
            v6 = v14 - 1;
          }
        }
      }
      if ( !LOBYTE(ptQTask[570].tQTaskRefList.ptHead) )
      {
        v15 = ptQTask[3].ptNext;
        if ( v15 )
        {
          tUpdateMagicObjContext.ptParentPos = (struct real64x3_t *)&ptQTask[1];
          tUpdateMagicObjContext.ptParentOrientation = (struct real32x9_t *)&ptQTask[3].ptPrev;
          tUpdateMagicObjContext.ptTriggeredBy = ptQTask;
          v16 = (int)v15->tQTaskChildren.ptHead;
          if ( *(_DWORD *)v16 && v16 )
          {
            do
            {
              if ( *(_DWORD *)v16 )
                v17 = **(_DWORD **)v16 != 0 ? *(struct QTask_s **)v16 : nullptr;
              else
                v17 = nullptr;
              QTask_atProtectedQTaskStack[v6].ptQTask = v17;
              v18 = (void (__cdecl *)(int, struct UpdateMagicObjContext_t *))QTask_aatQTaskFinalEvent[MagicObj_eUpdateMagicObjEvent][*(unsigned __int16 *)(v16 + 36)].pfHandler;
              v19 = v6 + 1;
              QTask_nProtectedQTaskStackOffset = v19;
              if ( v18 )
              {
                v18(v16, &tUpdateMagicObjContext);
                v19 = QTask_nProtectedQTaskStackOffset;
              }
              v16 = dword_849C7DC[v19];
              v6 = v19 - 1;
              QTask_nProtectedQTaskStackOffset = v6;
            }
            while ( v16 );
          }
          for ( i = QTask_GetFirstChildOfType(ptQTask[3].ptNext, AIStationaryGun_eQTaskType);
                i;
                i = QTask_GetNextSiblingOfType(i, AIStationaryGun_eQTaskType) )
          {
            ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][i->eQTaskType].pfHandler)(i);
          }
        }
      }
      LOBYTE(ptQTask[570].tQTaskRefList.ptHead) = 0;
      ptQTask[570].tQTaskRefList.ptMiddle = nullptr;
      Car_Explode((struct Car_s *)ptQTask);
    }
  }
}

// source: j/0/vehicles/car.c:1009  [anchor-mhash]
void __cdecl Car_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QReference_s *ptTail; // eax
  struct QReference_s *ptMiddle; // eax
  struct QReference_s *v3; // eax
  int v4; // ecx
  struct QReference_s *v5; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax

  if ( ptQTask[3].ptNext )
  {
    QTask_Delete(ptQTask[3].ptNext);
    ptQTask[3].ptNext = nullptr;
  }
  *(_DWORD *)&ptQTask[12].eQTaskType = 0;
  Physics_DeAlloc((struct Physics_s *)&ptQTask[8]);
  ptTail = ptQTask[570].tQTaskRefList.ptTail;
  if ( ptTail )
  {
    QReference_Delete(ptTail, &QTask_tQTaskRefPool);
    ptQTask[570].tQTaskRefList.ptTail = nullptr;
  }
  ptMiddle = ptQTask[48].tQTaskRefList.ptMiddle;
  if ( ptMiddle )
  {
    QReference_Delete(ptMiddle, &QTask_tQTaskRefPool);
    ptQTask[48].tQTaskRefList.ptMiddle = nullptr;
  }
  if ( !BYTE1(ptQTask[570].ptParent) )
    World_RemoveDynCubeObj(Game_ptGame->ptWorld, (struct DynCubeObj_s *)ptQTask);
  QTaskList_Remove(GameFunctions_ptExplosionQTaskList, ptQTask);
  v3 = ptQTask[48].tQTaskRefList.ptTail;
  if ( v3 )
    SoundSys_DeleteChannelList((struct SoundSysChannelList_t *)v3);
  v4 = 0;
  while ( 1 )
  {
    v5 = Level_atLevelQTaskID[v4];
    if ( v5 )
    {
      if ( v5->pxObject == ptQTask )
        break;
    }
    if ( ++v4 >= 4096 )
      goto LABEL_19;
  }
  if ( v4 >= 0 )
  {
    pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Level_eRemoveLevelScriptSymbolsEvent][ptQTask->eQTaskType].pfHandler;
    if ( pfHandler )
      pfHandler(ptQTask);
  }
LABEL_19:
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[60].tQTaskRefList.ptMiddle);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[62].tQTaskRefList.ptMiddle);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[64].tQTaskRefList.ptMiddle);
  QTaskList_Remove(GameFunctions_ptVehicleQTaskList, ptQTask);
  AIDetection_ClearDetection((struct AIDetection_s *)&ptQTask[69].tQTaskRefList.ptMiddle);
}

// source: j/0/vehicles/car.c:1068  [size]
void __cdecl Car_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = Car_ptParameterList;
}

// source: j/0/vehicles/car.c:1084  [anchor-mhash]
void __cdecl Car_Move(struct Car_s *ptCar)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct CollisionEvaluateContext_s tContext; };
    struct { char igi2_o1[8]; struct real32x3_t tWindVelocity; };
    char igi2_extent[24];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct PhysicsObjType_s *ptType; // eax
  double vRealThrust; // st7
  char *pxData; // eax
  int v4; // edx
  float vY; // edi
  float vZ; // ecx
  struct SoundSysChannelList_t *ptChannelList; // eax
  double v8; // st7

  ptType = ptCar->tVehicle.tPhysicsObj.ptType;
  if ( ptType )
  {
    ptCar->tVehicle.vRealThrust = (1.0 - *((float *)ptType->pxData + 8)) * ptCar->tVehicle.vIdealThrust
                                + *((float *)ptType->pxData + 8) * ptCar->tVehicle.vRealThrust;
    ptCar->tVehicle.vRealDeltaGamma = (1.0 - *((float *)ptType->pxData + 6)) * ptCar->tVehicle.vIdealDeltaGamma
                                    + ptCar->tVehicle.vRealDeltaGamma * *((float *)ptType->pxData + 6);
    if ( ptCar->tVehicle.vIdealThrust == 0.0 )
    {
      vRealThrust = ptCar->tVehicle.vRealThrust;
      if ( vRealThrust < 0.0 )
        vRealThrust = -vRealThrust;
      if ( vRealThrust < 0.009999999776482582 )
        ptCar->tVehicle.vRealThrust = 0.0;
    }
    if ( !ptCar->isExploded )
    {
      igi2_frame.tContext.ptQTask = &ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask;
      Car_AddSpringForces(ptCar);
      pxData = (char *)ptCar->tVehicle.tPhysicsObj.ptType->pxData;
      v4 = *((_DWORD *)pxData + 10);
      if ( v4 )
      {
        igi2_frame.tWindVelocity.vX = ptCar->tVehicle.tPhysicsObj.tPhysics.tCMVel.vX;
        vY = ptCar->tVehicle.tPhysicsObj.tPhysics.tCMVel.vY;
        vZ = ptCar->tVehicle.tPhysicsObj.tPhysics.tCMVel.vZ;
        igi2_frame.tWindVelocity.vX = -igi2_frame.tWindVelocity.vX;
        igi2_frame.tWindVelocity.vY = -vY;
        igi2_frame.tWindVelocity.vZ = -vZ;
        Wing_ApplyAirResistance(
          (struct Wing_t *)(pxData + 44),
          v4,
          0.00032699998700991273,
          &ptCar->tVehicle.tPhysicsObj.tPhysics,
          &ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation,
          &igi2_frame.tWindVelocity);
      }
      PhysicsObj_Update(
        &ptCar->tVehicle.tPhysicsObj,
        44.600887298583984,
        0.9700000286102295,
        0.8999999761581421,
        Game_ptGame->ptWorld,
        13,
        &igi2_frame.tContext);
    }
    ptChannelList = ptCar->ptChannelList;
    if ( ptChannelList )
    {
      ptChannelList->auData[0].vChannelData = ptCar->tVehicle.vRealThrust;
      *(_DWORD *)&igi2_frame.tContext.isEvaluate = ptCar->tVehicle.vRealThrust > 0.009999999776482582;
      ptCar->ptChannelList->auData[1].vChannelData = (float)*(int *)&igi2_frame.tContext.isEvaluate;
      v8 = ptCar->tVehicle.tPhysicsObj.tPhysics.vCMSpeed * 0.0010000000474974513;
      if ( v8 >= 1.0 )
        v8 = 1.0;
      ptCar->ptChannelList->auData[2].vChannelData = v8;
    }
  }
}

// source: j/0/vehicles/car.c:1186  [size]
void __cdecl Car_UpdateAnimDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[20]; struct UpdateMagicObjContext_t tUpdateMagicObjContext; };
    char igi2_extent[32];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v2; // edx
  double v3; // st7
  double v4; // st7
  int *v5; // eax
  int v6; // eax
  double v7; // st6
  struct QTask_s *ptTail; // ecx
  struct QTask_s *v9; // eax
  struct QTask_s *ptHead; // eax
  int v11; // ecx
  int v12; // edx
  struct QTask_s *v13; // eax
  void (__cdecl *pfHandler)(int, struct UpdateMagicObjContext_t *); // eax
  int v15; // edx
  struct QTask_s *ptNext; // eax

  v2 = *(struct QTask_s **)(*((_DWORD *)pxContext + 1) + 4);
  if ( v2 != (struct QTask_s *)-1082130432 )
    ptQTask[48].ptNext = v2;
  ptQTask[48].tQTaskChildren.ptMiddle = **((struct QTask_s ***)pxContext + 1);
  LOBYTE(ptQTask[48].tQTaskRefList.ptHead) = *(float *)(*((_DWORD *)pxContext + 1) + 12) != -1.0;
  if ( *(_DWORD *)pxContext )
  {
    ptNext = ptQTask[3].ptNext;
    if ( ptNext )
      ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][ptNext->eQTaskType].pfHandler)(ptQTask[3].ptNext);
    LOBYTE(ptQTask[570].tQTaskRefList.ptHead) = 1;
    Car_Move((struct Car_s *)ptQTask);
  }
  else
  {
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
    igi2_frame.ptDynCubeObj = v4 * v7;
    World_MoveDynCubeObjRadius(
      Game_ptGame->ptWorld,
      (struct DynCubeObj_s *)ptQTask,
      (struct real64x3_t *)&ptQTask[11],
      igi2_frame.ptDynCubeObj);
    qmemcpy(&ptQTask[3].ptPrev, &ptQTask[11].eQTaskType, sizeof(struct QTask_s));
    *(_DWORD *)(*((_DWORD *)pxContext + 1) + 4) = -1082130432;
    *(_DWORD *)(*((_DWORD *)pxContext + 1) + 8) = -1073741824;
    PhysicsObj_Init(ptQTask, *(struct PhysicsObjType_s **)&ptQTask[12].eQTaskType);
    ptQTask[13].ptPrev = (struct QTask_s *)-1744830464;
    ptQTask[2].tQTaskRefList.ptTail = (struct QReference_s *)7;
    ptQTask[47].tQTaskRefList.ptTail = nullptr;
    ptQTask[47].ptParent = nullptr;
    *(_DWORD *)&ptQTask[47].eQTaskType = 0;
    ptQTask[47].tQTaskRefList.ptMiddle = nullptr;
    ptQTask[48].ptPrev = nullptr;
    ptQTask[48].tQTaskChildren.ptHead = nullptr;
    ptQTask[48].tQTaskChildren.ptMiddle = nullptr;
    ptQTask[48].ptNext = nullptr;
    LOBYTE(ptQTask[48].tQTaskRefList.ptHead) = 0;
    Car_AdjustWheelCollPoints((struct Car_s *)ptQTask);
    ptTail = ptQTask[48].tQTaskChildren.ptTail;
    ptQTask[47].tQTaskRefList.ptMiddle = (struct QReference_s *)ptTail;
    v9 = ptQTask[3].ptNext;
    LOBYTE(ptQTask[60].tQTaskChildren.ptMiddle) = 0;
    BYTE1(ptQTask[570].ptParent) = 0;
    *(_DWORD *)&ptQTask[47].eQTaskType = 0;
    ptQTask[48].tQTaskChildren.ptMiddle = nullptr;
    ptQTask[48].ptNext = ptTail;
    if ( v9 )
    {
      igi2_frame.tUpdateMagicObjContext.ptParentPos = (struct real64x3_t *)&ptQTask[1];
      igi2_frame.tUpdateMagicObjContext.ptParentOrientation = (struct real32x9_t *)&ptQTask[3].ptPrev;
      igi2_frame.tUpdateMagicObjContext.ptTriggeredBy = ptQTask;
      ptHead = v9->tQTaskChildren.ptHead;
      if ( ptHead->ptNext )
      {
        v11 = (int)ptHead;
        if ( ptHead )
        {
          v12 = QTask_nProtectedQTaskStackOffset;
          do
          {
            if ( *(_DWORD *)v11 )
              v13 = **(_DWORD **)v11 != 0 ? *(struct QTask_s **)v11 : nullptr;
            else
              v13 = nullptr;
            QTask_atProtectedQTaskStack[v12].ptQTask = v13;
            pfHandler = (void (__cdecl *)(int, struct UpdateMagicObjContext_t *))QTask_aatQTaskFinalEvent[MagicObj_eUpdateMagicObjEvent][*(unsigned __int16 *)(v11 + 36)].pfHandler;
            v15 = v12 + 1;
            QTask_nProtectedQTaskStackOffset = v15;
            if ( pfHandler )
            {
              pfHandler(v11, &igi2_frame.tUpdateMagicObjContext);
              v15 = QTask_nProtectedQTaskStackOffset;
            }
            v11 = dword_849C7DC[v15];
            v12 = v15 - 1;
            QTask_nProtectedQTaskStackOffset = v12;
          }
          while ( v11 );
        }
      }
    }
  }
}

// source: j/0/vehicles/car.c:1296  [anchor-mhash]
void __cdecl Car_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { unsigned int v23; };
    struct { char igi2_o1[8]; float ptDynCubeObj; };
    struct { char igi2_o2[28]; char zTempModel[128]; };
    struct { char igi2_o3[156]; char zString[132]; };
    char igi2_extent[288];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v2; // st7
  bool v3; // c0
  bool v4; // c3
  struct QTask_s *ptTail; // edx
  double v6; // st7
  double v7; // st7
  int *v8; // eax
  int v9; // eax
  double v10; // st6
  struct QReferenceList_s *p_tQTaskRefList; // esi
  struct LODVirModel_s *LODVirModelExistsFn; // eax
  struct LODVirModel_s *v13; // ebx
  struct PhysicsObjType_s *Type; // eax
  char *v15; // eax
  char v16; // cl
  struct QTask_s *ptNext; // eax
  int ptHead; // eax
  int v19; // edx
  struct QTask_s *v20; // ecx
  void (__cdecl *pfHandler)(int, _DWORD); // ecx
  int v22; // edx

  igi2_frame.v23 = Human_bAIDetectionQTaskMask;
  LOBYTE(ptQTask[60].tQTaskChildren.ptMiddle) = 0;
  BYTE1(ptQTask[570].ptParent) = 0;
  AIDetection_InitDetection((struct AIDetection_s *)&ptQTask[69].tQTaskRefList.ptMiddle, 1, 4u, igi2_frame.v23, 4, 8);
  v2 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  v3 = v2 < *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  v4 = v2 == *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  ptTail = ptQTask[48].tQTaskChildren.ptTail;
  BYTE1(ptQTask[60].tQTaskChildren.ptMiddle) = 0;
  ptQTask[48].ptNext = ptTail;
  ptQTask[47].tQTaskRefList.ptMiddle = (struct QReference_s *)ptTail;
  if ( v3 || v4 )
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
  igi2_frame.ptDynCubeObj = v7 * v10;
  World_MoveDynCubeObjRadius(
    Game_ptGame->ptWorld,
    (struct DynCubeObj_s *)ptQTask,
    (struct real64x3_t *)&ptQTask[11],
    igi2_frame.ptDynCubeObj);
  qmemcpy(&ptQTask[3].ptPrev, &ptQTask[11].eQTaskType, sizeof(struct QTask_s));
  p_tQTaskRefList = &ptQTask[10].tQTaskRefList;
  LODVirModelExistsFn = MTP_GetLODVirModelExistsFn((char *)&ptQTask[10].tQTaskRefList);
  v13 = LODVirModelExistsFn;
  if ( LODVirModelExistsFn )
  {
    if ( LODVirModelExistsFn != *(struct LODVirModel_s **)&ptQTask[2].eQTaskType )
    {
      Vehicle_Init((struct Vehicle_s *)ptQTask);
      Type = PhysicsObjType_FindType((char *)&ptQTask[10].tQTaskRefList);
      if ( Type )
      {
        PhysicsObj_Init(ptQTask, Type);
        Car_AdjustWheelCollPoints((struct Car_s *)ptQTask);
        Car_SetWheelCount((struct Car_s *)ptQTask);
        *(double *)&ptQTask[68].tQTaskChildren.ptHead = *(float *)&ptQTask[570].tQTaskChildren.ptHead * 0.01745329238474369;
        *(double *)&ptQTask[68].tQTaskChildren.ptTail = *(float *)&ptQTask[570].tQTaskChildren.ptMiddle * 0.01745329238474369;
        *(double *)&ptQTask[68].tQTaskRefList.ptMiddle = *(float *)&ptQTask[570].tQTaskChildren.ptTail * 4096.0;
      }
      if ( v13 != *(struct LODVirModel_s **)&ptQTask[2].eQTaskType )
      {
        ModelObj_SetLODVirModel((struct ModelObj_s *)ptQTask, v13, false);
        ptQTask[7].tQTaskRefList.ptHead = nullptr;
        ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
        ptQTask[7].tQTaskRefList.ptTail = nullptr;
        ptQTask[7].ptParent = nullptr;
        *(_DWORD *)&ptQTask[7].eQTaskType = 0;
      }
    }
  }
  else
  {
    if ( LOBYTE(p_tQTaskRefList->ptHead) && BYTE1(ptQTask[10].tQTaskRefList.ptHead) != 42 )
    {
      sprintf(igi2_frame.zString, "Model \"%s\" not available", (char *)&ptQTask[10].tQTaskRefList);
      v15 = (char *)&ptQTask[10].tQTaskRefList;
      do
      {
        v16 = *v15;
        v15[igi2_frame.zTempModel - (char *)p_tQTaskRefList] = *v15;
        ++v15;
      }
      while ( v16 );
      sprintf((char *const)&ptQTask[10].tQTaskRefList, "** %s **", igi2_frame.zTempModel);
    }
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
  ptNext = ptQTask[3].ptNext;
  if ( ptNext )
  {
    ptHead = (int)ptNext->tQTaskChildren.ptHead;
    if ( *(_DWORD *)ptHead )
    {
      if ( ptHead )
      {
        v19 = QTask_nProtectedQTaskStackOffset;
        do
        {
          if ( *(_DWORD *)ptHead )
            v20 = **(_DWORD **)ptHead != 0 ? *(struct QTask_s **)ptHead : nullptr;
          else
            v20 = nullptr;
          QTask_atProtectedQTaskStack[v19].ptQTask = v20;
          pfHandler = (void (__cdecl *)(int, _DWORD))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][*(unsigned __int16 *)(ptHead + 36)].pfHandler;
          v22 = v19 + 1;
          QTask_nProtectedQTaskStackOffset = v22;
          if ( pfHandler )
          {
            pfHandler(ptHead, 0);
            v22 = QTask_nProtectedQTaskStackOffset;
          }
          ptHead = dword_849C7DC[v22];
          v19 = v22 - 1;
          QTask_nProtectedQTaskStackOffset = v19;
        }
        while ( ptHead );
      }
    }
  }
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[60].tQTaskRefList.ptMiddle, ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[62].tQTaskRefList.ptMiddle, ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[64].tQTaskRefList.ptMiddle, ptQTask);
}

// source: j/0/vehicles/car.c:1415  [size]
void __cdecl Car_SoundUpdateParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = ptQTask + 1;
  *((_DWORD *)pxContext + 1) = 0;
  *((_DWORD *)pxContext + 2) = ptQTask[48].tQTaskRefList.ptTail;
}

// source: j/0/vehicles/car.c:1439  [size]
void __cdecl Car_GetKeyframeSizeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = 120;
}

// source: j/0/vehicles/car.c:1455  [size]
void __cdecl Car_GetChannelDescriptionHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // eax

  v2 = *(_DWORD *)pxContext;
  if ( *(int *)pxContext < 0 || v2 >= 5 )
    *((_DWORD *)pxContext + 1) = 0;
  else
    *((_DWORD *)pxContext + 1) = 16 * v2 + 7050576;
}

// source: j/0/vehicles/car.c:1484  [anchor-mhash]
void __cdecl Car_ReadChannelsHandler(struct QTask_s *ptQTask, void *pxContext)
{
  double v2; // st7
  double v3; // st7

  **(_DWORD **)pxContext = 0;
  if ( (Keyboard_tKeyboard.anCurrentKey[29] & 0x80u) == 0 && (Keyboard_tKeyboard.anCurrentKey[157] & 0x80) == 0 )
    **(float **)pxContext = (float)((Keyboard_tKeyboard.anCurrentKey[205] >> 7)
                                  - (Keyboard_tKeyboard.anCurrentKey[203] >> 7));
  *(_DWORD *)(*(_DWORD *)pxContext + 4) = -1082130432;
  if ( (Keyboard_tKeyboard.anCurrentKey[41] & 0x80) != 0 )
    *(_DWORD *)(*(_DWORD *)pxContext + 4) = 0;
  if ( (Keyboard_tKeyboard.anCurrentKey[2] & 0x80) != 0 )
    *(_DWORD *)(*(_DWORD *)pxContext + 4) = -1098907648;
  if ( (Keyboard_tKeyboard.anCurrentKey[3] & 0x80) != 0 )
    *(_DWORD *)(*(_DWORD *)pxContext + 4) = -1107296256;
  if ( (Keyboard_tKeyboard.anCurrentKey[4] & 0x80) != 0 )
    *(_DWORD *)(*(_DWORD *)pxContext + 4) = 1040187392;
  if ( (Keyboard_tKeyboard.anCurrentKey[5] & 0x80) != 0 )
    *(_DWORD *)(*(_DWORD *)pxContext + 4) = 1048576000;
  if ( (Keyboard_tKeyboard.anCurrentKey[6] & 0x80) != 0 )
    *(_DWORD *)(*(_DWORD *)pxContext + 4) = 1052770304;
  if ( (Keyboard_tKeyboard.anCurrentKey[7] & 0x80) != 0 )
    *(_DWORD *)(*(_DWORD *)pxContext + 4) = 1056964608;
  if ( (Keyboard_tKeyboard.anCurrentKey[8] & 0x80) != 0 )
    *(_DWORD *)(*(_DWORD *)pxContext + 4) = 1059061760;
  if ( (Keyboard_tKeyboard.anCurrentKey[9] & 0x80) != 0 )
    *(_DWORD *)(*(_DWORD *)pxContext + 4) = 1061158912;
  if ( (Keyboard_tKeyboard.anCurrentKey[10] & 0x80) != 0 )
    *(_DWORD *)(*(_DWORD *)pxContext + 4) = 1063256064;
  if ( (Keyboard_tKeyboard.anCurrentKey[11] & 0x80) != 0 )
    *(_DWORD *)(*(_DWORD *)pxContext + 4) = 1065353216;
  if ( (Keyboard_tKeyboard.anCurrentKey[49] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[49] & 0x80) == 0 )
  {
    v2 = *(float *)&ptQTask[48].ptNext - 0.01;
    if ( v2 < 0.0 )
      v2 = 0.0;
    *(float *)(*(_DWORD *)pxContext + 4) = v2;
  }
  if ( (Keyboard_tKeyboard.anCurrentKey[50] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[50] & 0x80) == 0 )
  {
    v3 = *(float *)&ptQTask[48].ptNext + 0.01;
    if ( v3 > 1.0 )
      v3 = 1.0;
    *(float *)(*(_DWORD *)pxContext + 4) = v3;
  }
  *(_DWORD *)(*(_DWORD *)pxContext + 12) = -1082130432;
  if ( (Keyboard_tKeyboard.anCurrentKey[48] & 0x80) != 0 )
    *(_DWORD *)(*(_DWORD *)pxContext + 12) = 1065353216;
  *(_DWORD *)(*(_DWORD *)pxContext + 16) = -1082130432;
  if ( (Keyboard_tKeyboard.anCurrentKey[38] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[38] & 0x80) == 0 )
    *(_DWORD *)(*(_DWORD *)pxContext + 16) = 1065353216;
}

// source: j/0/vehicles/car.c:1591  [anchor-mhash]
void __cdecl Car_RestoreKeyframeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // esi
  double v3; // st7
  bool v4; // c0
  bool v5; // c3
  double v6; // st7
  double v7; // st7
  int *v8; // eax
  int v9; // eax
  double v10; // st6
  float ptDynCubeObj; // [esp+0h] [ebp-8h]

  v2 = *(_DWORD *)pxContext;
  Vehicle_RestoreKeyframeHandler(ptQTask, pxContext);
  v3 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  v4 = v3 < *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  v5 = v3 == *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  LOBYTE(ptQTask[48].tQTaskRefList.ptHead) = *(_BYTE *)(v2 + 116);
  if ( v4 || v5 )
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
    (struct real64x3_t *)(v2 + 16),
    ptDynCubeObj);
}

// source: j/0/vehicles/car.c:1636  [anchor-mhash]
void __cdecl Car_SaveKeyframeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // esi

  v2 = *(_DWORD *)pxContext;
  Vehicle_SaveKeyframeHandler(ptQTask, pxContext);
  *(_DWORD *)(v2 + 112) = 0;
  *(_BYTE *)(v2 + 116) = ptQTask[48].tQTaskRefList.ptHead;
  *(_BYTE *)(v2 + 117) = 0;
}

// source: j/0/vehicles/car.c:1747  [anchor-mhash]
void __cdecl Car_ExplosionHitHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // eax
  double v3; // st7
  double v4; // st7
  int *v5; // eax
  int v6; // eax
  double v7; // st6
  float ptExplosionHitContext; // [esp+0h] [ebp-14h]

  v2 = *((_DWORD *)pxContext + 8);
  if ( v2
    && !*(_DWORD *)(v2 + 668)
    && (strstr((char *)(v2 + 84), "WEAPON_ID_RPG7")
     || strstr((char *)(*((_DWORD *)pxContext + 8) + 84), "WEAPON_ID_RPG18")) )
  {
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
    ptExplosionHitContext = v4 * v7;
    if ( GameFunctions_ResolveExplosionHit(
           (struct ExplosionHitContext_t *)pxContext,
           ptQTask,
           (struct real64x3_t *)&ptQTask[1],
           ptExplosionHitContext,
           true) != 0.0 )
      LOBYTE(ptQTask[60].tQTaskChildren.ptMiddle) = 1;
  }
}

// source: j/0/vehicles/car.c:1851  [size]
void __cdecl Car_HitZoneDestroyedHandler(struct QTask_s *ptQTask, void *pxContext)
{
  LOBYTE(ptQTask[60].tQTaskChildren.ptMiddle) = 1;
}

// source: j/0/vehicles/car.c:1870  [size]
void __cdecl Car_AILineOfSightHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_BYTE *)pxContext = *((struct QTask_s **)pxContext + 2) != ptQTask && *((struct QTask_s **)pxContext + 3) != ptQTask;
}

// source: j/0/vehicles/car.c:1898  [size]
void __cdecl Car_ComputerMapFollowQTaskEventHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_BYTE *)pxContext = 1;
}

// source: j/0/vehicles/car.c:1917  [size]
void __cdecl Car_GetAIDetectionHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = (char *)ptQTask + 2784;
  *((_DWORD *)pxContext + 1) = (char *)ptQTask + 2664;
}

// source: j/0/vehicles/car.c:1937  [anchor-mhash]
void __cdecl Car_RegisterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  if ( !BYTE1(ptQTask[570].ptParent) )
    ((void (__cdecl *)())QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRegisterQTaskEvent][Vehicle_eQTaskType].pfHandler)(ptQTask, pxContext);
}

// source: j/0/vehicles/car.c:1956  [anchor-callee]
void __cdecl Car_RemoveHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRemoveQTaskEvent][Vehicle_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  QTask_DeleteQTaskAndQTaskRefSafe(&ptQTask[48].tQTaskRefList.ptMiddle);
}

// source: j/0/vehicles/car.c:1973  [size]
void __cdecl Car_RegisterScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( !LOBYTE(ptQTask[570].ptParent) )
  {
    LOBYTE(ptQTask[570].ptParent) = 1;
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.isExploded", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      (char *)&ptQTask[570].ptParent + 1,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
  }
}

// source: j/0/vehicles/car.c:2003  [anchor-mhash]
void __cdecl Car_RemoveScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( LOBYTE(ptQTask[570].ptParent) )
  {
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    LOBYTE(ptQTask[570].ptParent) = 0;
    sprintf(igi2_frame.zTemp, "%s.isExploded", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    LOBYTE(ptQTask[570].ptParent) = 0;
  }
}

// source: j/0/vehicles/car.c:2037  [anchor-caller]
void __cdecl Car_DeSerializeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptNext; // eax
  struct QTask_s *v3; // eax
  struct QTask_s *v4; // eax

  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[Serialize_eDeSerializeQTaskEvent][Vehicle_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  Physics_UpdateSpeedApproximation((struct Physics_s *)&ptQTask[8]);
  AIDetection_ClearDetection((struct AIDetection_s *)&ptQTask[69].tQTaskRefList.ptMiddle);
  ptNext = ptQTask[3].ptNext;
  ptQTask[570].tQTaskRefList.ptMiddle = nullptr;
  LOBYTE(ptQTask[60].tQTaskChildren.ptMiddle) = 0;
  ptQTask[60].tQTaskChildren.ptTail = (struct QTask_s *)-1;
  if ( !ptNext )
  {
    v3 = QTask_NewFn(nullptr, MagicObjContainer_eQTaskType, nullptr);
    v3[1].ptNext = ptQTask;
    ptQTask[3].ptNext = v3;
    ModelObj_CreateAttachObjects((struct ModelObj_s *)ptQTask, v3, ptQTask, false, true);
  }
  QTask_DeleteQTaskAndQTaskRefSafe(&ptQTask[570].tQTaskRefList.ptTail);
  if ( BYTE1(ptQTask[570].ptParent) )
  {
    v4 = EditRigidObj_New(
           Level_ptDynamicQTask,
           (char *)(*(_DWORD *)(*(_DWORD *)&ptQTask[12].eQTaskType + 724) + 688),
           (struct real64x3_t *)&ptQTask[1],
           (struct real32x9_t *)&ptQTask[3].ptPrev);
    if ( v4 )
      ptQTask[570].tQTaskRefList.ptTail = QTask_NewQTaskRef(v4);
  }
}

// source: j/0/vehicles/car.c:2087  [size]
void __cdecl Car_GetSerializeParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = SpyBrowser_isUnreal;
}

// source: j/0/vehicles/car.c:2109  [anchor-mhash]
void __cdecl Car_Open()
{
  unsigned __int16 v0; // si
  __int16 v1; // ax
  __int16 v2; // ax
  struct ParameterList_s *v3; // eax
  int v4; // edx
  unsigned __int16 v5; // si

  v0 = QTask_NewQTaskType(off_694BEC, 22968, Vehicle_eQTaskType, 0, 0);
  Car_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 0, Car_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, Car_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, Car_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Car_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, Car_UpdateInternalDataHandler);
  v1 = SoundSys_eUpdateParameterListQTaskEvent;
  if ( SoundSys_eUpdateParameterListQTaskEvent == 512 )
  {
    v1 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.nRealFadeCount);
    v0 = Car_eQTaskType;
    SoundSys_eUpdateParameterListQTaskEvent = v1;
  }
  QTask_LinkQTaskEventHandlerFn(v0, v1, Car_SoundUpdateParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, GameFunctions_eExplosionHitQTaskEvent, Car_ExplosionHitHandler);
  QTask_LinkQTaskEventHandlerFn(v0, AnimQTask_eUpdateAnimDataEvent, Car_UpdateAnimDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    AnimQTask_eGetChannelDescriptionEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Car_GetChannelDescriptionHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    AnimQTask_eGetKeyframeSizeEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Car_GetKeyframeSizeHandler);
  QTask_LinkQTaskEventHandlerFn(v0, AnimQTask_eReadChannelsEvent, Car_ReadChannelsHandler);
  QTask_LinkQTaskEventHandlerFn(v0, AnimQTask_eRestoreKeyframeEvent, Car_RestoreKeyframeHandler);
  QTask_LinkQTaskEventHandlerFn(v0, AnimQTask_eSaveKeyframeEvent, Car_SaveKeyframeHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    AIDetection_eLineOfSightQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Car_AILineOfSightHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Vehicle_eHitZoneDestroyedQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Car_HitZoneDestroyedHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ComputerMap_eFollowQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Car_ComputerMapFollowQTaskEventHandler);
  QTask_LinkQTaskEventHandlerFn(v0, AIDetection_eGetAIDetectionEvent, Car_GetAIDetectionHandler);
  QTask_LinkQTaskEventHandlerFn(v0, DynCubeObj_eDynCubeObjRemoveQTaskEvent, Car_RemoveHandler);
  QTask_LinkQTaskEventHandlerFn(v0, DynCubeObj_eDynCubeObjRegisterQTaskEvent, Car_RegisterHandler);
  v2 = AIStationaryGun_eGetGunParametersEvent;
  if ( AIStationaryGun_eGetGunParametersEvent == 512 )
  {
    v2 = QTask_NewQTaskEventFn(0, "AIStationaryGunGetGunParams");
    v0 = Car_eQTaskType;
    AIStationaryGun_eGetGunParametersEvent = v2;
  }
  QTask_LinkQTaskEventHandlerFn(v0, v2, (void (__cdecl *)(struct QTask_s *, void *))Car_GetGunParametersHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    GameFunctions_eWeaponCollisionEvaluateQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Car_WeaponCollisionEvaluateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Level_eRegisterLevelScriptSymbolsEvent, Car_RegisterScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Level_eRemoveLevelScriptSymbolsEvent, Car_RemoveScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  v3 = (struct ParameterList_s *)Mem_AllocFn(492, 4);
  v4 = Level_eParameterTypeObjectPos;
  v3->ptParameterListItem = (struct ParameterListItem_s *)&v3[1];
  v3->nParameters = 0;
  v3->nMaxParameters = 24;
  Car_ptParameterList = v3;
  dword_750F20 = 0;
  unk_750F24 = 0;
  unk_750F28 = 0;
  unk_750F2C = 1083129856;
  ParameterList_AddParameter(v3, 0x1B8u, v4, "Position", 7u, nullptr);
  ParameterList_AddParameter(Car_ptParameterList, 0x1DCu, Level_eParameterTypeReal32x9, "Orientation", 7u, nullptr);
  ParameterList_AddParameter(Car_ptParameterList, 0x790u, Level_eParameterTypeReal32, "Original Thrust", 7u, nullptr);
  ParameterList_AddParameter(Car_ptParameterList, 0x1D0u, Level_eParameterTypeReal32x3, "Speed", 7u, nullptr);
  ParameterList_AddParameter(Car_ptParameterList, 0x1A4u, Level_eParameterTypeString16, "Model", 7u, nullptr);
  ParameterList_AddParameter(Car_ptParameterList, 0x728u, Level_eParameterTypebool8, "Collision detection", 7u, nullptr);
  ParameterList_AddParameter(Car_ptParameterList, 0x729u, Level_eParameterTypebool8, "Force Z", 7u, nullptr);
  ParameterList_AddParameter(Car_ptParameterList, 0x978u, Level_eParameterTypeVarString, "Open door", 7u, nullptr);
  ParameterList_AddParameter(Car_ptParameterList, 0x9C8u, Level_eParameterTypeVarString, "Can fire", 7u, nullptr);
  ParameterList_AddParameter(Car_ptParameterList, 0xA18u, Level_eParameterTypeVarString, "Play sound", 7u, nullptr);
  ParameterList_AddParameter(
    Car_ptParameterList,
    0x5918u,
    Level_eParameterTypeDegrees,
    "ViewCone Alpha (degrees)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Car_ptParameterList,
    0x591Cu,
    Level_eParameterTypeDegrees,
    "ViewCone Gamma (degrees)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Car_ptParameterList,
    0x5920u,
    Level_eParameterTypeReal32,
    "ViewCone Length (meter)",
    7u,
    &dword_750F20);
  dword_750F10 = 0;
  unk_750F14 = -1065975808;
  unk_750F18 = 0;
  unk_750F1C = 1081507840;
  ParameterList_AddParameter(Car_ptParameterList, 0x5934u, Level_eParameterTypeString16, "Barrel model", 7u, nullptr);
  ParameterList_AddParameter(Car_ptParameterList, 0x596Cu, Level_eParameterTypeString16, "Rotationsound", 7u, nullptr);
  ParameterList_AddParameter(
    Car_ptParameterList,
    0x5958u,
    Level_eParameterTypeReal32,
    "Min Alpha (deg)",
    7u,
    &dword_750F10);
  ParameterList_AddParameter(
    Car_ptParameterList,
    0x5954u,
    Level_eParameterTypeReal32,
    "Max Alpha (deg)",
    7u,
    &dword_750F10);
  ParameterList_AddParameter(
    Car_ptParameterList,
    0x595Cu,
    Level_eParameterTypeReal32,
    "Max Gamma (deg)",
    7u,
    &dword_750F10);
  ParameterList_AddParameter(
    Car_ptParameterList,
    0x5960u,
    Level_eParameterTypeInt32,
    (char *)&g_zMessage.anDR[24],
    7u,
    nullptr);
  ParameterList_AddParameter(
    Car_ptParameterList,
    0x5964u,
    Level_eParameterTypeReal32,
    "Alpha speed (deg/sec)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Car_ptParameterList,
    0x5968u,
    Level_eParameterTypeReal32,
    "Gamma speed (deg/sec)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Car_ptParameterList,
    0x59ACu,
    Level_eParameterTypeReal32,
    "Beta speed (deg/sec)",
    7u,
    nullptr);
  ParameterList_AddParameter(Car_ptParameterList, 0x59B0u, Level_eParameterTypeReal32, "Accuracy", 7u, &unk_6B09D8);
  ParameterList_AddParameter(Car_ptParameterList, 0x598Cu, Level_eParameterTypeString32, "WeaponID", 7u, nullptr);
  v5 = Car_eQTaskType;
  QTask_LinkQTaskEventHandlerFn(
    Car_eQTaskType,
    Serialize_eGetSerializeParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Car_GetSerializeParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v5, Serialize_eDeSerializeQTaskEvent, Car_DeSerializeHandler);
  SpyBrowser_isUnreal = (enum bool)ParameterList_Derive(ModelObjParameters_ptSerializeParameterList, 5);
  ParameterList_AddParameter(
    (struct ParameterList_s *)SpyBrowser_isUnreal,
    0x158u,
    Level_eParameterTypeReal32x3,
    "Velocity",
    7u,
    nullptr);
  ParameterList_AddParameter(
    (struct ParameterList_s *)SpyBrowser_isUnreal,
    0x164u,
    Level_eParameterTypeReal32x3,
    "VelocityDir",
    7u,
    nullptr);
  ParameterList_AddParameter(
    (struct ParameterList_s *)SpyBrowser_isUnreal,
    0x5931u,
    Level_eParameterTypebool8,
    "isExploded",
    7u,
    nullptr);
  ParameterList_AddParameter(
    (struct ParameterList_s *)SpyBrowser_isUnreal,
    0x770u,
    Level_eParameterTypeReal32,
    "vRealThrust",
    7u,
    nullptr);
  ParameterList_AddParameter(
    (struct ParameterList_s *)SpyBrowser_isUnreal,
    0x780u,
    Level_eParameterTypeReal32,
    "vIdealThrust",
    7u,
    nullptr);
  Symbol_Register(
    "TASKTYPE_CAR",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)Car_eQTaskType,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}

// source: j/0/vehicles/car.c:2221  [size]
void __cdecl Car_Close()
{
  int v0; // esi
  int v1; // esi

  if ( Car_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&Car_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  if ( SpyBrowser_isUnreal )
  {
    v1 = *(_DWORD *)((SpyBrowser_isUnreal - 4) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
  QTask_DeleteQTaskType(Car_eQTaskType);
}

// source: j/0/vehicles/car.c:2240  [size]
unsigned __int16 __cdecl Car_GetQTaskType()
{
  return Car_eQTaskType;
}

// source: j/0/vehicles/car.c:2253  [size]
struct QTask_s *__cdecl Car_GetStationaryGunQTask(struct QTask_s *ptQTask)
{
  return QTask_GetFirstChildOfType(ptQTask[3].ptNext, StationaryGun_eQTaskType);
}

// source: j/0/vehicles/car.c:2273  [size]
struct real64x3_t *__cdecl Car_GetActivatePosAndOrientation(
        struct QTask_s *ptQTask,
        struct real64x3_t *ptPos,
        struct real32x9_t *ptOrientation)
{
  qmemcpy(ptOrientation, &ptQTask[3].ptPrev, sizeof(struct real32x9_t));
  return GameFunctions_GetMagicVertex(ptPos, ptQTask, 8);
}
