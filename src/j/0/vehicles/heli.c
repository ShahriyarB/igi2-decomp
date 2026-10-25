/* j/0/vehicles/heli.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/vehicles/heli.c:106  [size]
struct Heli_s *__cdecl Heli_RemoveSounds(struct Heli_s *ptHeli)
{
  struct Heli_s *result; // eax

  QTask_DeleteQTaskAndQTaskRefSafe(&ptHeli->ptEngineSoundDefQTaskRef);
  return result;
}

// source: j/0/vehicles/heli.c:119  [anchor-mhash]
void __cdecl Heli_AddWheelForces(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[16]; struct real32x3_t *v22; };
    struct { char igi2_o2[16]; struct real32x3_t *v23; };
    struct { char igi2_o3[20]; int nTracePos; };
    struct { char igi2_o4[24]; int isHardContact; };
    struct { char igi2_o5[28]; double vMaxHardCollisionDistance; };
    struct { char igi2_o6[36]; double vSpringRadius; };
    struct { char igi2_o7[44]; struct PointForce_s tForce; };
    struct { char igi2_o8[68]; double vWheelRadius; };
    struct { char igi2_o9[76]; struct CollisionEvaluateContext_s tContext; };
    struct { char igi2_o10[84]; double avTraceLength[4]; };
    struct { char igi2_o11[116]; struct real64x3_t atTracePosStop[4]; };
    struct { char igi2_o12[212]; struct real32x3_t atForcePos[4]; };
    struct { char igi2_o13[260]; struct real64x3_t atTracePos[4]; };
    struct { char igi2_o14[356]; struct QIntersection_s atIntersection[4]; };
    char igi2_extent[840];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v1; // ebp
  struct QTask_s *FirstChildOfType; // eax
  float *ptHead; // ecx
  double v4; // st7
  struct QTask_s *ptMiddle; // ecx
  double v6; // st7
  int v7; // ebp
  double v8; // st7
  double *p_vDistance; // edx
  double v10; // st5
  double v11; // st5
  double v12; // st4
  double v13; // st5
  float vZ; // ecx
  struct QTask_s *v15; // eax
  double v16; // st7
  double v17; // st7
  int *v18; // eax
  int v19; // eax
  double v20; // st6

  v1 = 0;
  igi2_frame.nTracePos = 0;
  FirstChildOfType = QTask_GetFirstChildOfType(ptQTask[3].ptNext, HeliWheel_eQTaskType);
  igi2_frame.isHardContact = 0;
  igi2_frame.vMaxHardCollisionDistance = -1.7976931348623157e+308;
  ptQTask[13].ptNext = nullptr;
  if ( FirstChildOfType )
  {
    igi2_frame.v22 = igi2_frame.atForcePos;
    do
    {
      if ( v1 >= 4 )
        break;
      qmemcpy(&igi2_frame.atTracePos[v1], &FirstChildOfType[1], sizeof(struct real64x3_t));
      igi2_frame.atTracePos[v1].vZ = igi2_frame.atTracePos[v1].vZ + 8192.0;
      ptHead = (float *)FirstChildOfType[8].tQTaskChildren.ptHead;
      igi2_frame.vWheelRadius = *ptHead;
      igi2_frame.vSpringRadius = ptHead[1];
      v4 = igi2_frame.vWheelRadius;
      LODWORD(igi2_frame.v22->vX) = FirstChildOfType[5].ptPrev;
      ptMiddle = FirstChildOfType[5].tQTaskChildren.ptMiddle;
      LODWORD(igi2_frame.v22->vY) = FirstChildOfType[5].tQTaskChildren.ptHead;
      LODWORD(igi2_frame.v22->vZ) = ptMiddle;
      v6 = -(v4 + 8192.0);
      igi2_frame.avTraceLength[igi2_frame.nTracePos] = v6;
      qmemcpy(&igi2_frame.atTracePosStop[v1], &igi2_frame.atTracePos[v1], sizeof(struct real64x3_t));
      igi2_frame.atTracePosStop[v1].vZ = v6 + igi2_frame.atTracePosStop[v1].vZ;
      ++igi2_frame.nTracePos;
      ++igi2_frame.v22;
      ++v1;
      FirstChildOfType = QTask_GetNextSiblingOfType(FirstChildOfType, HeliWheel_eQTaskType);
    }
    while ( FirstChildOfType );
    if ( igi2_frame.nTracePos )
    {
      igi2_frame.tContext.ptQTask = ptQTask;
      World_TraceLines(
        Game_ptGame->ptWorld,
        igi2_frame.atIntersection,
        igi2_frame.atTracePos,
        igi2_frame.atTracePosStop,
        igi2_frame.nTracePos,
        13,
        &igi2_frame.tContext,
        0xFFFFFFFF);
      v7 = 0;
      if ( igi2_frame.nTracePos > 0 )
      {
        v8 = igi2_frame.vWheelRadius;
        igi2_frame.v23 = igi2_frame.atForcePos;
        p_vDistance = &igi2_frame.atIntersection[0].vDistance;
        do
        {
          if ( *((_DWORD *)p_vDistance - 1) )
          {
            v10 = igi2_frame.avTraceLength[v7];
            if ( v10 < 0.0 )
              v10 = -v10;
            if ( v10 >= *p_vDistance )
            {
              v11 = *p_vDistance;
              if ( v11 < 0.0 )
                v11 = -v11;
              igi2_frame.tForce.tForce.vX = 0.0;
              igi2_frame.tForce.tForce.vY = 0.0;
              if ( igi2_frame.vSpringRadius + 8192.0 <= *p_vDistance )
              {
                igi2_frame.isHardContact = 0;
                igi2_frame.tForce.tForce.vZ = (v8 - (v11 - 8192.0))
                                 / v8
                                 * *(float *)(*(_DWORD *)&ptQTask[12].eQTaskType + 8)
                                 * 11.150221824645996;
              }
              else
              {
                igi2_frame.isHardContact = 1;
                v12 = *p_vDistance;
                if ( v12 < 0.0 )
                  v12 = -v12;
                igi2_frame.tForce.tForce.vZ = ((igi2_frame.vSpringRadius + 8192.0 - v12) / (igi2_frame.vSpringRadius + 8192.0) + 1.0)
                                 * *(float *)(*(_DWORD *)&ptQTask[12].eQTaskType + 8)
                                 * 11.150221824645996;
                v13 = igi2_frame.vSpringRadius + 8192.0 - *p_vDistance;
                if ( v13 > igi2_frame.vMaxHardCollisionDistance )
                  igi2_frame.vMaxHardCollisionDistance = v13;
              }
              igi2_frame.tForce.tPoint.vX = igi2_frame.v23->vX;
              vZ = igi2_frame.v23->vZ;
              igi2_frame.tForce.tPoint.vY = igi2_frame.v23->vY;
              v15 = ptQTask[10].tQTaskChildren.ptMiddle;
              igi2_frame.tForce.tPoint.vZ = vZ;
              qmemcpy((char *)ptQTask[10].ptPrev + 24 * (_DWORD)v15, &igi2_frame.tForce, 0x18u);
              ++*(int *)&ptQTask[10].tQTaskChildren.ptMiddle;
              ++*(int *)&ptQTask[13].ptNext;
              *(float *)&ptQTask[8].tQTaskRefList.ptMiddle = *(float *)&ptQTask[8].tQTaskRefList.ptMiddle * 0.949999988079071;
              *(float *)&ptQTask[8].tQTaskRefList.ptTail = *(float *)&ptQTask[8].tQTaskRefList.ptTail * 0.949999988079071;
              *(float *)&ptQTask[8].ptParent = *(float *)&ptQTask[8].ptParent * 0.9700000286102295;
              *(float *)&ptQTask[9].tQTaskChildren.ptHead = *(float *)&ptQTask[9].tQTaskChildren.ptHead * 0.9800000190734863;
              *(float *)&ptQTask[9].tQTaskChildren.ptMiddle = *(float *)&ptQTask[9].tQTaskChildren.ptMiddle * 0.9800000190734863;
              *(float *)&ptQTask[9].tQTaskChildren.ptTail = *(float *)&ptQTask[9].tQTaskChildren.ptTail * 0.9800000190734863;
            }
          }
          ++v7;
          p_vDistance += 15;
          ++igi2_frame.v23;
        }
        while ( v7 < igi2_frame.nTracePos );
        if ( igi2_frame.isHardContact )
        {
          qmemcpy(&igi2_frame.tForce, &ptQTask[1], sizeof(igi2_frame.tForce));
          *(double *)&igi2_frame.tForce.tPoint.vY = *(double *)&igi2_frame.tForce.tPoint.vY + igi2_frame.vMaxHardCollisionDistance;
          if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
            v16 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
          else
            v16 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
          if ( v16 >= *(float *)&ptQTask[6].ptPrev )
          {
            if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
              v17 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
            else
              v17 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
          }
          else
          {
            v17 = *(float *)&ptQTask[6].ptPrev;
          }
          v18 = *(int **)&ptQTask[2].eQTaskType;
          if ( v18 && (v19 = *v18) != 0 )
            v20 = *(float *)(*(_DWORD *)(*(_DWORD *)(v19 + 12) + 12) + 120);
          else
            v20 = 1.0;
          igi2_frame.ptDynCubeObj = v17 * v20;
          World_MoveDynCubeObjRadius(
            Game_ptGame->ptWorld,
            (struct DynCubeObj_s *)ptQTask,
            (struct real64x3_t *)&igi2_frame.tForce,
            igi2_frame.ptDynCubeObj);
        }
      }
    }
  }
}

// source: j/0/vehicles/heli.c:302  [size]
struct QTask_s *__cdecl Heli_FindHeliDoor(struct Heli_s *ptHeli)
{
  return QTask_GetFirstChildOfType(
           ptHeli->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.ptMagicObjContainer,
           HeliDoor_eQTaskType);
}

// source: j/0/vehicles/heli.c:315  [anchor-mhash]
void __cdecl Heli_Init(struct QTask_s *ptQTask)
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
  v6 = (struct QReference_s *)Mem_AllocFn(12, 4);
  if ( v6 )
  {
    v6->ptNext = (struct QReference_s *)2;
    v6->ptPrev = nullptr;
    v6->pxObject = nullptr;
  }
  ptQTask[48].tQTaskRefList.ptMiddle = v6;
  ptQTask[48].tQTaskRefList.ptTail = nullptr;
  LOBYTE(ptQTask[10].tQTaskRefList.ptHead) = 0;
  Vehicle_Create((struct Vehicle_s *)ptQTask);
  v7 = GameFunctions_ptVehicleQTaskList;
  ptQTask[48].tQTaskChildren.ptTail = (struct QTask_s *)1065353216;
  LOBYTE(ptQTask[48].ptParent) = 0;
  *(_DWORD *)&ptQTask[48].eQTaskType = -1;
  ptQTask[49].ptNext = nullptr;
  ptQTask[49].ptPrev = nullptr;
  ptQTask[49].tQTaskChildren.ptHead = nullptr;
  *(_DWORD *)&ptQTask[50].eQTaskType = 0;
  ptQTask[51].ptNext = nullptr;
  ptQTask[51].ptPrev = nullptr;
  ptQTask[51].tQTaskChildren.ptHead = nullptr;
  *(_DWORD *)&ptQTask[52].eQTaskType = 0;
  ptQTask[53].ptNext = nullptr;
  ptQTask[53].ptPrev = nullptr;
  ptQTask[53].tQTaskChildren.ptHead = nullptr;
  *(_DWORD *)&ptQTask[54].eQTaskType = 0;
  BYTE1(ptQTask[48].ptParent) = 0;
  QTaskList_Register(v7, (struct QTaskList_s *)ptQTask);
  ptQTask[558].tQTaskRefList.ptMiddle = (struct QReference_s *)1119092736;
  ptQTask[558].tQTaskRefList.ptTail = (struct QReference_s *)1119092736;
  ptQTask[558].ptParent = (struct QTask_s *)1114636288;
}

// source: j/0/vehicles/heli.c:388  [anchor-caller]
void __cdecl Heli_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  Heli_Init(ptQTask);
  QTaskList_Register(GameFunctions_ptExplosionQTaskList, (struct QTaskList_s *)ptQTask);
}

// source: j/0/vehicles/heli.c:404  [anchor-strings]
void __cdecl Heli_RunHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vFullRange; };
    struct { char igi2_o1[4]; float vFallOffRange; };
    struct { char igi2_o2[8]; float vBurnRange; };
    struct { char igi2_o3[80]; struct real32x9_t tExplosionPos; };
    char igi2_extent[120];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v2; // eax
  double v3; // st7
  double v4; // st7
  int *v5; // eax
  int v6; // eax
  double v7; // st6
  int v8; // edx
  int v9; // ecx
  int v10; // eax
  int *v11; // edi
  struct Game_s *v12; // eax
  unsigned int v13; // ebx
  unsigned int v14; // ecx
  unsigned int v15; // edx
  unsigned int v16; // esi
  int v17; // ebx
  struct QTask_s *FirstChildOfType; // eax
  char v19; // al
  struct QTask_s *ptHead; // ebp
  int v21; // ecx
  int v22; // edx
  struct QTask_s *v23; // eax
  void (__cdecl *pfHandler)(int); // eax
  int v25; // edx
  float ptQTaska = *(float *)&ptQTask; // [esp+7Ch] [ebp+4h] ARGSLOT
  struct QTask_s *ptQTaskb = *(struct QTask_s * *)&ptQTask; // [esp+7Ch] [ebp+4h] ARGSLOT
  struct QTask_s *ptQTaskc = *(struct QTask_s * *)&ptQTask; // [esp+7Ch] [ebp+4h] ARGSLOT

  if ( ptQTask[53].ptNext
    && ptQTask[53].ptPrev->ptNext
    && ptQTask[53].tQTaskChildren.ptHead
    && !(unsigned int)(__int64)Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[53], ptQTask) )
  {
    QTask_DeleteQTaskAndQTaskRefSafe(&ptQTask[48].tQTaskRefList.ptTail);
  }
  else if ( !ptQTask[48].tQTaskRefList.ptTail )
  {
    v2 = SoundSys_NewSoundFn(ptQTask, "helicopter_1");
    if ( v2 )
      ptQTask[48].tQTaskRefList.ptTail = QTask_NewQTaskRef(v2);
  }
  if ( LOBYTE(ptQTask[48].ptParent) )
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
    v8 = *(_DWORD *)(*(_DWORD *)&ptQTask[12].eQTaskType + 724);
    v9 = *(_DWORD *)&ptQTask[48].eQTaskType;
    v10 = *(_DWORD *)(v8 + 336);
    ptQTaska = v4 * v7;
    if ( v9 == -1 )
    {
      if ( v10 )
      {
        if ( v10 > 0 )
        {
          v11 = (int *)(v8 + 296);
          ptQTaskb = *(struct QTask_s **)(v8 + 336);
          do
          {
            v12 = Game_ptGame;
            v13 = (Game_ptGame->tRunRandomState.anRandom[0] >> 7) ^ Game_ptGame->tRunRandomState.anRandom[2];
            v14 = v13 ^ Game_ptGame->tRunRandomState.anRandom[1];
            v15 = v14 + Game_ptGame->tRunRandomState.anRandom[0];
            Game_ptGame->tRunRandomState.anRandom[1] = v14;
            v12->tRunRandomState.anRandom[0] = v15;
            v12->tRunRandomState.anRandom[2] = v13;
            v16 = v15;
            GameFunctions_GetMagicVertex((struct real64x3_t *)&igi2_frame.tExplosionPos, ptQTask, *v11);
            Explosion0_New(
              (struct real64x3_t *)&igi2_frame.tExplosionPos,
              1,
              v16 % 0x1E,
              1.0,
              12288.0,
              3072.0,
              3072.0,
              3,
              2,
              nullptr,
              "1009_01_1",
              "explo_03_l",
              -1,
              0,
              307200.0,
              nullptr,
              nullptr,
              EXPLOSIONDAMAGE_LINEAR_FALLOFF);
            ++v11;
            ptQTaskb = (struct QTask_s *)((char *)ptQTaskb - 1);
          }
          while ( ptQTaskb );
        }
      }
      else
      {
        igi2_frame.vBurnRange = ptQTaska * 0.004999999888241291;
        igi2_frame.vFallOffRange = ptQTaska * 0.05000000074505806;
        igi2_frame.vFullRange = ptQTaska * 0.25;
        Explosion0_New(
          (struct real64x3_t *)&ptQTask[1],
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
          -1,
          0,
          307200.0,
          nullptr,
          nullptr,
          EXPLOSIONDAMAGE_LINEAR_FALLOFF);
      }
      *(_DWORD *)&ptQTask[48].eQTaskType = 30;
    }
    else
    {
      *(_DWORD *)&ptQTask[48].eQTaskType = v9 - 1;
      if ( v9 == 1 )
      {
        QTask_Delete(ptQTask);
        return;
      }
    }
  }
  if ( ptQTask[49].ptNext )
  {
    if ( ptQTask[49].ptPrev->ptNext )
    {
      if ( ptQTask[49].tQTaskChildren.ptHead )
      {
        v17 = (__int64)Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[49], ptQTask);
        FirstChildOfType = QTask_GetFirstChildOfType(ptQTask[3].ptNext, HeliDoor_eQTaskType);
        if ( FirstChildOfType )
          LOBYTE(FirstChildOfType[8].tQTaskChildren.ptTail) = v17;
      }
    }
  }
  if ( ptQTask[51].ptNext && ptQTask[51].ptPrev->ptNext && ptQTask[51].tQTaskChildren.ptHead )
  {
    ptQTaskc = (struct QTask_s *)SBYTE1(ptQTask[48].ptParent);
    v19 = (__int64)Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[51], ptQTask);
    BYTE1(ptQTask[48].ptParent) = v19;
    if ( v19 )
    {
      qmemcpy(&igi2_frame.tExplosionPos, &ptQTask[3].ptPrev, sizeof(igi2_frame.tExplosionPos));
      Real32x9_RotateAlpha(&igi2_frame.tExplosionPos, &igi2_frame.tExplosionPos, -1.5707963705062866);
      qmemcpy(&ptQTask[55], &ptQTask[1], 0x18u);
      qmemcpy(&ptQTask[55].tQTaskRefList.ptMiddle, &igi2_frame.tExplosionPos, sizeof(struct QTask_s));
      LOBYTE(ptQTask[57].ptParent) = 0;
      AIDetection_RunDetection(
        (struct AIDetection_s *)&ptQTask[58],
        (struct AIDetectionView_s *)&ptQTask[55],
        ptQTask,
        1);
    }
    if ( !BYTE1(ptQTask[48].ptParent) && ptQTaskc )
    {
      AIDetection_ClearDetection((struct AIDetection_s *)&ptQTask[58]);
      AIDetection_InitDetection((struct AIDetection_s *)&ptQTask[58], 1, 4u, Human_bAIDetectionQTaskMask, 4, 8);
    }
  }
  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext )
  {
    v21 = (int)ptHead;
    if ( ptHead )
    {
      v22 = QTask_nProtectedQTaskStackOffset;
      do
      {
        if ( *(_DWORD *)v21 )
          v23 = **(_DWORD **)v21 != 0 ? *(struct QTask_s **)v21 : nullptr;
        else
          v23 = nullptr;
        QTask_atProtectedQTaskStack[v22].ptQTask = v23;
        pfHandler = (void (__cdecl *)(int))QTask_aatQTaskFinalEvent[1][*(unsigned __int16 *)(v21 + 36)].pfHandler;
        v25 = v22 + 1;
        QTask_nProtectedQTaskStackOffset = v25;
        if ( pfHandler )
        {
          pfHandler(v21);
          v25 = QTask_nProtectedQTaskStackOffset;
        }
        v21 = dword_849C7DC[v25];
        v22 = v25 - 1;
        QTask_nProtectedQTaskStackOffset = v22;
      }
      while ( v21 );
    }
  }
}

// source: j/0/vehicles/heli.c:598  [anchor-mhash]
void __cdecl Heli_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QReference_s *ptMiddle; // eax
  int v2; // esi

  if ( ptQTask[3].ptNext )
  {
    QTask_Delete(ptQTask[3].ptNext);
    ptQTask[3].ptNext = nullptr;
  }
  *(_DWORD *)&ptQTask[12].eQTaskType = 0;
  Physics_DeAlloc((struct Physics_s *)&ptQTask[8]);
  World_RemoveDynCubeObj(Game_ptGame->ptWorld, (struct DynCubeObj_s *)ptQTask);
  QTaskList_Remove(GameFunctions_ptExplosionQTaskList, ptQTask);
  ptMiddle = ptQTask[48].tQTaskRefList.ptMiddle;
  if ( ptMiddle )
  {
    v2 = *(_DWORD *)((unsigned int)&ptMiddle[-1].pxObject & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v2);
    memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
    free((void *)v2);
  }
  QTask_DeleteQTaskAndQTaskRefSafe(&ptQTask[48].tQTaskRefList.ptTail);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[49]);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[51]);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[53]);
  QTaskList_Remove(GameFunctions_ptVehicleQTaskList, ptQTask);
  AIDetection_ClearDetection((struct AIDetection_s *)&ptQTask[58]);
}

// source: j/0/vehicles/heli.c:645  [size]
void __cdecl Heli_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = Heli_ptParameterList;
}

// source: j/0/vehicles/heli.c:661  [anchor-caller]
void __cdecl Heli_Move(struct Heli_s *ptHeli)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vThrustInertia; };
    struct { float vThrustInertiaa; };
    struct { char igi2_o2[4]; float v52; };
    struct { char igi2_o3[4]; float v53; };
    struct { char igi2_o4[8]; float vGammaInertia[2]; };
    struct { char igi2_o5[16]; struct real32x3_t tWindVelocity[2]; };
    struct { char igi2_o6[40]; struct PointForce_s tY; };
    struct { char igi2_o7[80]; _BYTE tZ[40]; };
    char igi2_extent[120];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct PhysicsObjType_s *ptType; // ecx
  float *pxData; // edx
  float v3; // eax
  double vRealThrust; // st7
  double v5; // st6
  double v6; // st5
  double v7; // rt1
  double vIdealDeltaBeta; // st5
  double vIdealDeltaGamma; // st6
  float *v10; // eax
  double v11; // st6
  struct PointForce_s *ptForces; // edx
  double v13; // st6
  double v14; // st6
  double v15; // st6
  double v16; // st6
  int v17; // edx
  struct PointForce_s *v18; // edi
  int v19; // ecx
  struct PointForce_s *v20; // eax
  double vX; // st7
  double v22; // st6
  float vZ; // ecx
  float v24; // edx
  double v25; // st5
  struct real32x9_t *p_tOrientation; // edi
  double v27; // st4
  double v28; // st7
  double v29; // rt0
  double v30; // st4
  double v31; // st7
  double v32; // st7
  long double v33; // st7
  long double v34; // rtt
  double v35; // st6
  double v36; // st6
  double v37; // st7
  char *v38; // eax
  int v39; // edx
  float vY; // esi
  float v41; // ecx
  struct QTask_s *ptMagicObjContainer; // eax
  int ptHead; // ecx
  int v44; // edx
  struct QTask_s *v45; // eax
  int v46; // esi
  void (__cdecl *pfHandler)(int, struct real32x3_t *); // eax
  int v48; // edx
  struct SoundSysChannelList_t *ptChannelList; // eax

  ptType = ptHeli->tVehicle.tPhysicsObj.ptType;
  pxData = (float *)ptType->pxData;
  if ( ptHeli->tVehicle.vRealThrust >= 0.8 )
    v3 = pxData[8];
  else
    v3 = pxData[9];
  vRealThrust = ptHeli->tVehicle.vRealThrust;
  if ( vRealThrust >= ptHeli->tVehicle.vIdealThrust )
  {
    if ( vRealThrust > ptHeli->tVehicle.vIdealThrust )
    {
      vRealThrust = vRealThrust - v3;
      if ( vRealThrust < ptHeli->tVehicle.vIdealThrust )
        goto LABEL_9;
    }
  }
  else
  {
    vRealThrust = vRealThrust + v3;
    if ( vRealThrust > ptHeli->tVehicle.vIdealThrust )
LABEL_9:
      vRealThrust = ptHeli->tVehicle.vIdealThrust;
  }
  if ( vRealThrust < 0.0010000000474974513 && ptHeli->tVehicle.vIdealThrust == 0.0 )
    vRealThrust = 0.0;
  v5 = pxData[2];
  v6 = pxData[4];
  igi2_frame.vGammaInertia[0] = pxData[6];
  ptHeli->tVehicle.vRealThrust = vRealThrust;
  v7 = v6;
  igi2_frame.vThrustInertia = ptHeli->tVehicle.vIdealDeltaAlpha * (1.0 - v5) + v5 * ptHeli->tVehicle.vRealDeltaAlpha;
  vIdealDeltaBeta = ptHeli->tVehicle.vIdealDeltaBeta;
  ptHeli->tVehicle.vRealDeltaAlpha = igi2_frame.vThrustInertia;
  igi2_frame.v52 = vIdealDeltaBeta * (1.0 - v7) + v7 * ptHeli->tVehicle.vRealDeltaBeta;
  vIdealDeltaGamma = ptHeli->tVehicle.vIdealDeltaGamma;
  ptHeli->tVehicle.vRealDeltaBeta = igi2_frame.v52;
  igi2_frame.vGammaInertia[0] = vIdealDeltaGamma * (1.0 - igi2_frame.vGammaInertia[0]) + igi2_frame.vGammaInertia[0] * ptHeli->tVehicle.vRealDeltaGamma;
  ptHeli->tVehicle.vRealDeltaGamma = igi2_frame.vGammaInertia[0];
  if ( (igi2_frame.vThrustInertia != 0.0 || igi2_frame.v52 != 0.0 || igi2_frame.vGammaInertia[0] != 0.0)
    && (!ptHeli->tVehicle.tPhysicsObj.nContact || ptHeli->tVehicle.tPhysicsObj.tPhysics.vCMSpeed > 2.0) )
  {
    v10 = (float *)ptType->pxData;
    v11 = igi2_frame.vThrustInertia * v10[1];
    ptForces = ptHeli->tVehicle.tPhysicsObj.tPhysics.ptForces;
    igi2_frame.tWindVelocity[1].vX = 0.0;
    v13 = v11 * ptType->vMass;
    igi2_frame.tWindVelocity[1].vY = 0.0;
    igi2_frame.tWindVelocity[1].vZ = 819.2000122070312;
    igi2_frame.tWindVelocity[0].vX = 0.0;
    igi2_frame.tWindVelocity[0].vZ = 0.0;
    igi2_frame.tWindVelocity[0].vY = v13 * -0.800000011920929;
    igi2_frame.tY.tPoint.vZ = 409.6000061035156;
    v14 = igi2_frame.v52 * v10[3];
    memset(&igi2_frame.tY.tForce.vY, 0, 16);
    v15 = v14 * ptType->vMass;
    *(_DWORD *)&igi2_frame.tZ[16] = 1178599424;
    *(_DWORD *)&igi2_frame.tZ[20] = 0;
    igi2_frame.tY.tForce.vX = v15;
    memset(&igi2_frame.tZ[4], 0, 12);
    v16 = igi2_frame.vGammaInertia[0] * v10[5] * vRealThrust * ptType->vMass * 0.07999999821186066;
    qmemcpy(&ptForces[ptHeli->tVehicle.tPhysicsObj.tPhysics.nForces], igi2_frame.tWindVelocity, sizeof(struct PointForce_s));
    *(float *)igi2_frame.tZ = v16;
    v17 = ptHeli->tVehicle.tPhysicsObj.tPhysics.nForces + 1;
    v18 = &ptHeli->tVehicle.tPhysicsObj.tPhysics.ptForces[v17];
    ptHeli->tVehicle.tPhysicsObj.tPhysics.nForces = v17;
    qmemcpy(v18, &igi2_frame.tY, sizeof(struct PointForce_s));
    v19 = ptHeli->tVehicle.tPhysicsObj.tPhysics.nForces + 1;
    v20 = ptHeli->tVehicle.tPhysicsObj.tPhysics.ptForces;
    ptHeli->tVehicle.tPhysicsObj.tPhysics.nForces = v19;
    qmemcpy(&v20[v19], igi2_frame.tZ, sizeof(struct PointForce_s));
    ++ptHeli->tVehicle.tPhysicsObj.tPhysics.nForces;
  }
  if ( !ptHeli->tVehicle.tPhysicsObj.nContact && ptHeli->tVehicle.tPhysicsObj.tPhysics.vCMSpeed > 2.0 )
  {
    vX = ptHeli->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vX;
    v22 = ptHeli->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vX;
    vZ = ptHeli->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vZ;
    v24 = ptHeli->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vZ;
    v25 = ptHeli->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vX * 0.0;
    p_tOrientation = &ptHeli->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation;
    igi2_frame.tWindVelocity[0].vZ = ptHeli->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vZ;
    igi2_frame.tWindVelocity[0].vX = vZ;
    igi2_frame.vGammaInertia[0] = v25;
    igi2_frame.tWindVelocity[0].vY = v24;
    if ( vX != 0.0 )
      goto LABEL_27;
    if ( v22 == 0.0 && v25 == 0.0 )
    {
      v32 = igi2_frame.vGammaInertia[0];
LABEL_32:
      v33 = v32 * *((float *)ptHeli->tVehicle.tPhysicsObj.ptType->pxData + 5) * 0.0002908882086657217;
      v34 = sin(v33);
      igi2_frame.vThrustInertiaa = cos(v33);
      igi2_frame.tY.tPoint.vZ = -v34;
      *(float *)igi2_frame.tZ = (ptHeli->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vY
                    + ptHeli->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vZ)
                   * 0.0
                   + p_tOrientation->tX.vX;
      v35 = p_tOrientation->tX.vX * 0.0;
      *(float *)&igi2_frame.tZ[4] = v34 * ptHeli->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vZ
                       + igi2_frame.vThrustInertiaa * ptHeli->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vY
                       + v35;
      *(float *)&igi2_frame.tZ[8] = igi2_frame.tY.tPoint.vZ * ptHeli->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vY
                       + igi2_frame.vThrustInertiaa * ptHeli->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vZ
                       + v35;
      *(float *)&igi2_frame.tZ[12] = (ptHeli->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vZ
                         + ptHeli->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vY)
                        * 0.0
                        + ptHeli->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vX;
      v36 = ptHeli->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vX * 0.0;
      *(float *)&igi2_frame.tZ[16] = igi2_frame.vThrustInertiaa * ptHeli->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vY
                        + v34 * ptHeli->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vZ
                        + v36;
      *(float *)&igi2_frame.tZ[20] = igi2_frame.tY.tPoint.vZ * ptHeli->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vY
                        + igi2_frame.vThrustInertiaa * ptHeli->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vZ
                        + v36;
      *(float *)&igi2_frame.tZ[24] = (ptHeli->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vZ
                         + ptHeli->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vY)
                        * 0.0
                        + ptHeli->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vX;
      *(float *)&igi2_frame.tZ[28] = igi2_frame.vThrustInertiaa * ptHeli->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vY
                        + v34 * ptHeli->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vZ
                        + igi2_frame.vGammaInertia[0];
      v37 = igi2_frame.vThrustInertiaa * ptHeli->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vZ
          + igi2_frame.tY.tPoint.vZ * ptHeli->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vY;
      *(_DWORD *)&igi2_frame.tZ[36] = ptHeli->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.nOps + 1;
      *(float *)&igi2_frame.tZ[32] = v37 + igi2_frame.vGammaInertia[0];
      qmemcpy(p_tOrientation, igi2_frame.tZ, sizeof(struct real32x9_t));
      goto LABEL_33;
    }
    if ( vX != 0.0 || v22 != 0.0 || v25 != 0.0 )
    {
LABEL_27:
      igi2_frame.v53 = sqrt(vX * vX + v22 * v22 + v25 * v25);
      v27 = vX;
      v28 = 1.0 / igi2_frame.v53;
      v29 = v27 * v28;
      v30 = v28;
      vX = v29;
      v22 = v22 * v30;
      v25 = v25 * v30;
    }
    v31 = v25 * igi2_frame.tWindVelocity[0].vZ + v22 * igi2_frame.tWindVelocity[0].vY + vX * igi2_frame.tWindVelocity[0].vX;
    if ( igi2_frame.tWindVelocity[0].vZ <= 0.0 )
      v32 = v31 * 0.699999988079071;
    else
      v32 = v31 * -0.699999988079071;
    goto LABEL_32;
  }
LABEL_33:
  if ( !PhysicsObj_IsIdle(&ptHeli->tVehicle.tPhysicsObj) )
  {
    LODWORD(igi2_frame.vGammaInertia[1]) = ptHeli;
    Heli_AddWheelForces(&ptHeli->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask);
    v38 = (char *)ptHeli->tVehicle.tPhysicsObj.ptType->pxData;
    v39 = *((_DWORD *)v38 + 10);
    if ( v39 )
    {
      igi2_frame.tWindVelocity[0].vX = ptHeli->tVehicle.tPhysicsObj.tPhysics.tCMVel.vX;
      vY = ptHeli->tVehicle.tPhysicsObj.tPhysics.tCMVel.vY;
      v41 = ptHeli->tVehicle.tPhysicsObj.tPhysics.tCMVel.vZ;
      igi2_frame.tWindVelocity[0].vX = -igi2_frame.tWindVelocity[0].vX;
      igi2_frame.tWindVelocity[0].vY = -vY;
      igi2_frame.tWindVelocity[0].vZ = -v41;
      Wing_ApplyAirResistance(
        (struct Wing_t *)(v38 + 44),
        v39,
        0.00032699998700991273,
        &ptHeli->tVehicle.tPhysicsObj.tPhysics,
        &ptHeli->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation,
        igi2_frame.tWindVelocity);
    }
    PhysicsObj_Update(
      &ptHeli->tVehicle.tPhysicsObj,
      44.600887298583984,
      1.0,
      0.9200000166893005,
      Game_ptGame->ptWorld,
      13,
      igi2_frame.vGammaInertia);
  }
  ptMagicObjContainer = ptHeli->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.ptMagicObjContainer;
  if ( ptMagicObjContainer )
  {
    LODWORD(igi2_frame.tWindVelocity[0].vX) = &ptHeli->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos;
    LODWORD(igi2_frame.tWindVelocity[0].vY) = &ptHeli->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation;
    LODWORD(igi2_frame.tWindVelocity[0].vZ) = ptHeli;
    ptHead = (int)ptMagicObjContainer->tQTaskChildren.ptHead;
    if ( *(_DWORD *)ptHead )
    {
      if ( ptHead )
      {
        v44 = QTask_nProtectedQTaskStackOffset;
        do
        {
          if ( *(_DWORD *)ptHead )
            v45 = **(_DWORD **)ptHead != 0 ? *(struct QTask_s **)ptHead : nullptr;
          else
            v45 = nullptr;
          v46 = MagicObj_eUpdateMagicObjEvent;
          QTask_atProtectedQTaskStack[v44].ptQTask = v45;
          pfHandler = (void (__cdecl *)(int, struct real32x3_t *))QTask_aatQTaskFinalEvent[v46][*(unsigned __int16 *)(ptHead + 36)].pfHandler;
          v48 = v44 + 1;
          QTask_nProtectedQTaskStackOffset = v48;
          if ( pfHandler )
          {
            pfHandler(ptHead, igi2_frame.tWindVelocity);
            v48 = QTask_nProtectedQTaskStackOffset;
          }
          ptHead = dword_849C7DC[v48];
          v44 = v48 - 1;
          QTask_nProtectedQTaskStackOffset = v44;
        }
        while ( ptHead );
      }
    }
  }
  ptChannelList = ptHeli->ptChannelList;
  if ( ptChannelList )
  {
    ptChannelList->auData[0].vChannelData = ptHeli->tVehicle.vRealThrust;
    LODWORD(igi2_frame.vGammaInertia[0]) = ptHeli->tVehicle.vRealThrust > 0.009999999776482582;
    ptHeli->ptChannelList->auData[1].vChannelData = (float)SLODWORD(igi2_frame.vGammaInertia[0]);
  }
}

// source: j/0/vehicles/heli.c:891  [anchor-caller]
void __cdecl Heli_UpdateAnimDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[20]; struct real32x3_t Real32x3_Rotate_tTemp; };
    char igi2_extent[32];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v2; // ecx
  bool v3; // cc
  double v4; // st7
  double v5; // st7
  int *v6; // eax
  int v7; // eax
  double v8; // st6
  struct PhysicsObjType_s *v9; // eax
  struct QTask_s *ptTail; // ecx
  struct QTask_s *ptNext; // eax
  struct QTask_s *v12; // eax
  double v13; // st7
  double v14; // st6
  struct QTask_s *v15; // eax
  struct QTask_s *ptHead; // eax
  int v17; // ecx
  int v18; // edx
  struct QTask_s *v19; // eax
  void (__cdecl *pfHandler)(int, struct real32x3_t *); // eax
  int v21; // edx
  struct QTask_s *v22; // eax

  v2 = *(struct QTask_s **)(*((_DWORD *)pxContext + 1) + 12);
  if ( v2 != (struct QTask_s *)-1082130432 )
    ptQTask[48].ptNext = v2;
  ptQTask[48].ptPrev = **((struct QTask_s ***)pxContext + 1);
  ptQTask[48].tQTaskChildren.ptHead = *(struct QTask_s **)(*((_DWORD *)pxContext + 1) + 4);
  ptQTask[48].tQTaskChildren.ptMiddle = *(struct QTask_s **)(*((_DWORD *)pxContext + 1) + 8);
  v3 = (int)(*(_DWORD *)pxContext) <= 0;
  if ( !*(_DWORD *)pxContext )
  {
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
      v4 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v4 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
    if ( v4 >= *(float *)&ptQTask[6].ptPrev )
    {
      if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
        v5 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
      else
        v5 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
    }
    else
    {
      v5 = *(float *)&ptQTask[6].ptPrev;
    }
    v6 = *(int **)&ptQTask[2].eQTaskType;
    if ( v6 && (v7 = *v6) != 0 )
      v8 = *(float *)(*(_DWORD *)(*(_DWORD *)(v7 + 12) + 12) + 120);
    else
      v8 = 1.0;
    igi2_frame.ptDynCubeObj = v5 * v8;
    World_MoveDynCubeObjRadius(
      Game_ptGame->ptWorld,
      (struct DynCubeObj_s *)ptQTask,
      (struct real64x3_t *)&ptQTask[11],
      igi2_frame.ptDynCubeObj);
    *(_DWORD *)(*((_DWORD *)pxContext + 1) + 12) = -1082130432;
    *(_DWORD *)(*((_DWORD *)pxContext + 1) + 16) = -1073741824;
    **((_DWORD **)pxContext + 1) = 0;
    *(_DWORD *)(*((_DWORD *)pxContext + 1) + 4) = 0;
    *(_DWORD *)(*((_DWORD *)pxContext + 1) + 8) = 0;
    v9 = *(struct PhysicsObjType_s **)&ptQTask[12].eQTaskType;
    qmemcpy(&ptQTask[3].ptPrev, &ptQTask[11].eQTaskType, sizeof(struct QTask_s));
    PhysicsObj_Init(ptQTask, v9);
    ptTail = ptQTask[48].tQTaskChildren.ptTail;
    ptQTask[47].tQTaskRefList.ptMiddle = (struct QReference_s *)ptTail;
    ptNext = ptQTask[3].ptNext;
    ptQTask[2].tQTaskRefList.ptTail = (struct QReference_s *)7;
    LOBYTE(ptQTask[48].tQTaskRefList.ptHead) = 0;
    ptQTask[47].tQTaskRefList.ptTail = nullptr;
    ptQTask[47].ptParent = nullptr;
    *(_DWORD *)&ptQTask[47].eQTaskType = 0;
    ptQTask[48].ptPrev = nullptr;
    ptQTask[48].tQTaskChildren.ptHead = nullptr;
    ptQTask[48].tQTaskChildren.ptMiddle = nullptr;
    ptQTask[48].ptNext = ptTail;
    if ( ptNext )
    {
      QTask_Delete(ptNext);
      ptQTask[3].ptNext = nullptr;
    }
    v12 = QTask_NewFn(nullptr, MagicObjContainer_eQTaskType, nullptr);
    v12[1].ptNext = ptQTask;
    ptQTask[3].ptNext = v12;
    ModelObj_CreateAttachObjects((struct ModelObj_s *)ptQTask, v12, ptQTask, false, true);
    igi2_frame.Real32x3_Rotate_tTemp.vX = *(float *)&ptQTask[3].tQTaskChildren.ptMiddle * *(float *)&ptQTask[11].ptParent
                             + *(float *)&ptQTask[3].tQTaskChildren.ptHead * *(float *)&ptQTask[11].tQTaskRefList.ptTail
                             + *(float *)&ptQTask[11].tQTaskRefList.ptMiddle * *(float *)&ptQTask[3].ptPrev;
    igi2_frame.Real32x3_Rotate_tTemp.vY = *(float *)&ptQTask[3].tQTaskRefList.ptMiddle * *(float *)&ptQTask[11].ptParent
                             + *(float *)&ptQTask[3].tQTaskRefList.ptHead * *(float *)&ptQTask[11].tQTaskRefList.ptTail
                             + *(float *)&ptQTask[3].tQTaskChildren.ptTail
                             * *(float *)&ptQTask[11].tQTaskRefList.ptMiddle;
    v13 = *(float *)&ptQTask[3].eQTaskType * *(float *)&ptQTask[11].ptParent
        + *(float *)&ptQTask[3].ptParent * *(float *)&ptQTask[11].tQTaskRefList.ptTail;
    v14 = *(float *)&ptQTask[3].tQTaskRefList.ptTail * *(float *)&ptQTask[11].tQTaskRefList.ptMiddle;
    ptQTask[8].tQTaskRefList.ptMiddle = (struct QReference_s *)LODWORD(igi2_frame.Real32x3_Rotate_tTemp.vX);
    ptQTask[8].tQTaskRefList.ptTail = (struct QReference_s *)LODWORD(igi2_frame.Real32x3_Rotate_tTemp.vY);
    igi2_frame.Real32x3_Rotate_tTemp.vZ = v13 + v14;
    ptQTask[8].ptParent = (struct QTask_s *)LODWORD(igi2_frame.Real32x3_Rotate_tTemp.vZ);
    Physics_UpdateSpeedApproximation((struct Physics_s *)&ptQTask[8]);
    v15 = ptQTask[3].ptNext;
    if ( v15 )
    {
      LODWORD(igi2_frame.Real32x3_Rotate_tTemp.vX) = &ptQTask[1];
      LODWORD(igi2_frame.Real32x3_Rotate_tTemp.vY) = &ptQTask[3].ptPrev;
      LODWORD(igi2_frame.Real32x3_Rotate_tTemp.vZ) = ptQTask;
      ptHead = v15->tQTaskChildren.ptHead;
      if ( ptHead->ptNext )
      {
        v17 = (int)ptHead;
        if ( ptHead )
        {
          v18 = QTask_nProtectedQTaskStackOffset;
          do
          {
            if ( *(_DWORD *)v17 )
              v19 = **(_DWORD **)v17 != 0 ? *(struct QTask_s **)v17 : nullptr;
            else
              v19 = nullptr;
            QTask_atProtectedQTaskStack[v18].ptQTask = v19;
            pfHandler = (void (__cdecl *)(int, struct real32x3_t *))QTask_aatQTaskFinalEvent[MagicObj_eUpdateMagicObjEvent][*(unsigned __int16 *)(v17 + 36)].pfHandler;
            v21 = v18 + 1;
            QTask_nProtectedQTaskStackOffset = v21;
            if ( pfHandler )
            {
              pfHandler(v17, &igi2_frame.Real32x3_Rotate_tTemp);
              v21 = QTask_nProtectedQTaskStackOffset;
            }
            v17 = dword_849C7DC[v21];
            v18 = v21 - 1;
            QTask_nProtectedQTaskStackOffset = v18;
          }
          while ( v17 );
        }
      }
    }
    v3 = (int)(*(_DWORD *)pxContext) <= 0;
  }
  if ( !v3 )
  {
    v22 = ptQTask[3].ptNext;
    if ( v22 )
      ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][v22->eQTaskType].pfHandler)(ptQTask[3].ptNext);
    Heli_Move((struct Heli_s *)ptQTask);
  }
}

// source: j/0/vehicles/heli.c:1004  [anchor-mhash]
void __cdecl Heli_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[20]; char zTempModel[128]; };
    struct { char igi2_o2[148]; char zString[132]; };
    char igi2_extent[280];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char *p_tQTaskRefList; // edi
  struct LODVirModel_s *LODVirModelExistsFn; // eax
  bool v4; // zf
  struct PhysicsObjType_s *Type; // eax
  char *v6; // eax
  char v7; // cl
  unsigned int v8; // ecx
  double v9; // st7
  struct QTask_s *ptTail; // edx
  bool v11; // c0
  bool v12; // c3
  double v13; // st7
  double v14; // st7
  int *v15; // eax
  int v16; // eax
  double v17; // st6
  struct QTask_s *ptNext; // eax
  struct QTask_s *v19; // eax
  struct QTask_s *ptHead; // eax
  int v21; // edx
  struct QTask_s *v22; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, _DWORD); // ecx
  int v24; // edx

  p_tQTaskRefList = (char *)&ptQTask[10].tQTaskRefList;
  LODVirModelExistsFn = MTP_GetLODVirModelExistsFn((char *)&ptQTask[10].tQTaskRefList);
  if ( LODVirModelExistsFn )
  {
    v4 = LODVirModelExistsFn == *(struct LODVirModel_s **)&ptQTask[2].eQTaskType;
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
    if ( !v4 )
    {
      ModelObj_SetLODVirModel((struct ModelObj_s *)ptQTask, LODVirModelExistsFn, false);
      ptQTask[7].tQTaskRefList.ptHead = nullptr;
      ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
      ptQTask[7].tQTaskRefList.ptTail = nullptr;
      ptQTask[7].ptParent = nullptr;
      *(_DWORD *)&ptQTask[7].eQTaskType = 0;
    }
    Type = PhysicsObjType_FindType(p_tQTaskRefList);
    PhysicsObj_Init(ptQTask, Type);
  }
  else if ( *p_tQTaskRefList && BYTE1(ptQTask[10].tQTaskRefList.ptHead) != 42 )
  {
    sprintf(igi2_frame.zString, "Model \"%s\" not available", p_tQTaskRefList);
    v6 = (char *)&ptQTask[10].tQTaskRefList;
    do
    {
      v7 = *v6;
      v6[igi2_frame.zTempModel - p_tQTaskRefList] = *v6;
      ++v6;
    }
    while ( v7 );
    sprintf(p_tQTaskRefList, "** %s **", igi2_frame.zTempModel);
  }
  v8 = Human_bAIDetectionQTaskMask;
  *(double *)&ptQTask[56].tQTaskRefList.ptMiddle = *(float *)&ptQTask[558].tQTaskRefList.ptMiddle * 0.01745329238474369;
  *(double *)&ptQTask[56].ptParent = *(float *)&ptQTask[558].tQTaskRefList.ptTail * 0.01745329238474369;
  *(double *)&ptQTask[57].ptNext = *(float *)&ptQTask[558].ptParent * 4096.0;
  AIDetection_InitDetection((struct AIDetection_s *)&ptQTask[58], 1, 4u, v8, 4, 8);
  v9 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  ptTail = ptQTask[48].tQTaskChildren.ptTail;
  v11 = v9 < *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  v12 = v9 == *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  ptQTask[47].tQTaskRefList.ptMiddle = (struct QReference_s *)ptTail;
  ptQTask[48].ptNext = ptTail;
  if ( v11 || v12 )
    v13 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  else
    v13 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  if ( v13 >= *(float *)&ptQTask[6].ptPrev )
  {
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
      v14 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v14 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  }
  else
  {
    v14 = *(float *)&ptQTask[6].ptPrev;
  }
  v15 = *(int **)&ptQTask[2].eQTaskType;
  if ( v15 && (v16 = *v15) != 0 )
    v17 = *(float *)(*(_DWORD *)(*(_DWORD *)(v16 + 12) + 12) + 120);
  else
    v17 = 1.0;
  igi2_frame.ptDynCubeObj = v14 * v17;
  World_MoveDynCubeObjRadius(
    Game_ptGame->ptWorld,
    (struct DynCubeObj_s *)ptQTask,
    (struct real64x3_t *)&ptQTask[11],
    igi2_frame.ptDynCubeObj);
  ptNext = ptQTask[3].ptNext;
  qmemcpy(&ptQTask[3].ptPrev, &ptQTask[11].eQTaskType, sizeof(struct QTask_s));
  if ( ptNext )
  {
    QTask_Delete(ptNext);
    ptQTask[3].ptNext = nullptr;
  }
  v19 = QTask_NewFn(nullptr, MagicObjContainer_eQTaskType, nullptr);
  v19[1].ptNext = ptQTask;
  ptQTask[3].ptNext = v19;
  ModelObj_CreateAttachObjects((struct ModelObj_s *)ptQTask, v19, ptQTask, false, true);
  ptHead = ptQTask[3].ptNext->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v21 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v22 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v22 = nullptr;
      QTask_atProtectedQTaskStack[v21].ptQTask = v22;
      pfHandler = (void (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][ptHead->eQTaskType].pfHandler;
      v24 = v21 + 1;
      QTask_nProtectedQTaskStackOffset = v24;
      if ( pfHandler )
      {
        pfHandler(ptHead, 0);
        v24 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v24];
      v21 = v24 - 1;
      QTask_nProtectedQTaskStackOffset = v21;
    }
    while ( ptHead );
  }
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[49], ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[51], ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[53], ptQTask);
  BYTE1(ptQTask[48].ptParent) = 0;
}

// source: j/0/vehicles/heli.c:1118  [size]
void __cdecl Heli_SoundUpdateParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = ptQTask + 1;
  *((_DWORD *)pxContext + 1) = 0;
  *((_DWORD *)pxContext + 2) = ptQTask[48].tQTaskRefList.ptMiddle;
}

// source: j/0/vehicles/heli.c:1145  [size]
void __cdecl Heli_GetKeyframeSizeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = 120;
}

// source: j/0/vehicles/heli.c:1161  [size]
void __cdecl Heli_GetChannelDescriptionHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // eax

  v2 = *(_DWORD *)pxContext;
  if ( *(int *)pxContext < 0 || v2 >= 5 )
    *((_DWORD *)pxContext + 1) = 0;
  else
    *((_DWORD *)pxContext + 1) = 16 * v2 + 7043952;
}

// source: j/0/vehicles/heli.c:1190  [anchor-mhash]
void __cdecl Heli_ReadChannelsHandler(struct QTask_s *ptQTask, void *pxContext)
{
  double v2; // st7
  double v3; // st7

  *(_DWORD *)(*(_DWORD *)pxContext + 4) = 0;
  **(_DWORD **)pxContext = 0;
  if ( (Keyboard_tKeyboard.anCurrentKey[157] & 0x80u) == 0 && (Keyboard_tKeyboard.anCurrentKey[29] & 0x80) == 0 )
  {
    *(float *)(*(_DWORD *)pxContext + 4) = (float)((Keyboard_tKeyboard.anCurrentKey[205] >> 7)
                                                 - (Keyboard_tKeyboard.anCurrentKey[203] >> 7));
    **(float **)pxContext = (float)((Keyboard_tKeyboard.anCurrentKey[208] >> 7)
                                  - (Keyboard_tKeyboard.anCurrentKey[200] >> 7));
  }
  *(float *)(*(_DWORD *)pxContext + 8) = (float)((Keyboard_tKeyboard.anCurrentKey[45] >> 7)
                                               - (Keyboard_tKeyboard.anCurrentKey[44] >> 7));
  *(_DWORD *)(*(_DWORD *)pxContext + 12) = -1082130432;
  if ( (Keyboard_tKeyboard.anCurrentKey[29] & 0x80) == 0 && (Keyboard_tKeyboard.anCurrentKey[157] & 0x80) == 0 )
  {
    if ( (Keyboard_tKeyboard.anCurrentKey[41] & 0x80) != 0 )
      *(_DWORD *)(*(_DWORD *)pxContext + 12) = 0;
    if ( (Keyboard_tKeyboard.anCurrentKey[2] & 0x80) != 0 )
      *(_DWORD *)(*(_DWORD *)pxContext + 12) = 1062668861;
    if ( (Keyboard_tKeyboard.anCurrentKey[3] & 0x80) != 0 )
      *(_DWORD *)(*(_DWORD *)pxContext + 12) = 1063339950;
    if ( (Keyboard_tKeyboard.anCurrentKey[4] & 0x80) != 0 )
      *(_DWORD *)(*(_DWORD *)pxContext + 12) = 1064011039;
    if ( (Keyboard_tKeyboard.anCurrentKey[5] & 0x80) != 0 )
      *(_DWORD *)(*(_DWORD *)pxContext + 12) = 1064682127;
    if ( (Keyboard_tKeyboard.anCurrentKey[6] & 0x80) != 0 )
      *(_DWORD *)(*(_DWORD *)pxContext + 12) = 1065353216;
    if ( (Keyboard_tKeyboard.anCurrentKey[7] & 0x80) != 0 )
      *(_DWORD *)(*(_DWORD *)pxContext + 12) = 1065688760;
    if ( (Keyboard_tKeyboard.anCurrentKey[8] & 0x80) != 0 )
      *(_DWORD *)(*(_DWORD *)pxContext + 12) = 1066024305;
    if ( (Keyboard_tKeyboard.anCurrentKey[9] & 0x80) != 0 )
      *(_DWORD *)(*(_DWORD *)pxContext + 12) = 1066359849;
    if ( (Keyboard_tKeyboard.anCurrentKey[10] & 0x80) != 0 )
      *(_DWORD *)(*(_DWORD *)pxContext + 12) = 1066695393;
    if ( (Keyboard_tKeyboard.anCurrentKey[11] & 0x80) != 0 )
      *(_DWORD *)(*(_DWORD *)pxContext + 12) = 1067030938;
    if ( (Keyboard_tKeyboard.anCurrentKey[49] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[49] & 0x80) == 0 )
    {
      v2 = *(float *)&ptQTask[48].ptNext - 0.01;
      if ( v2 < 0.8 )
        v2 = 0.8;
      *(float *)(*(_DWORD *)pxContext + 12) = v2;
    }
    if ( (Keyboard_tKeyboard.anCurrentKey[50] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[50] & 0x80) == 0 )
    {
      v3 = *(float *)&ptQTask[48].ptNext + 0.01;
      if ( v3 > 1.25 )
        v3 = 1.25;
      *(float *)(*(_DWORD *)pxContext + 12) = v3;
    }
  }
  *(_DWORD *)(*(_DWORD *)pxContext + 16) = -1073741824;
  if ( (Keyboard_tKeyboard.anCurrentKey[30] & 0x80) != 0 )
  {
    if ( (Keyboard_tKeyboard.anCurrentKey[41] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[41] & 0x80) == 0 )
      *(_DWORD *)(*(_DWORD *)pxContext + 16) = -1082130432;
    if ( (Keyboard_tKeyboard.anCurrentKey[2] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[2] & 0x80) == 0 )
      *(_DWORD *)(*(_DWORD *)pxContext + 16) = 1065353216;
    if ( (Keyboard_tKeyboard.anCurrentKey[3] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[3] & 0x80) == 0 )
      *(_DWORD *)(*(_DWORD *)pxContext + 16) = 0x40000000;
    if ( (Keyboard_tKeyboard.anCurrentKey[4] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[4] & 0x80) == 0 )
      *(_DWORD *)(*(_DWORD *)pxContext + 16) = 1077936128;
    if ( (Keyboard_tKeyboard.anCurrentKey[5] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[5] & 0x80) == 0 )
      *(_DWORD *)(*(_DWORD *)pxContext + 16) = 1082130432;
    if ( (Keyboard_tKeyboard.anCurrentKey[6] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[6] & 0x80) == 0 )
      *(_DWORD *)(*(_DWORD *)pxContext + 16) = 1084227584;
    if ( (Keyboard_tKeyboard.anCurrentKey[7] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[7] & 0x80) == 0 )
      *(_DWORD *)(*(_DWORD *)pxContext + 16) = 1086324736;
    if ( (Keyboard_tKeyboard.anCurrentKey[8] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[8] & 0x80) == 0 )
      *(_DWORD *)(*(_DWORD *)pxContext + 16) = 1088421888;
    if ( (Keyboard_tKeyboard.anCurrentKey[9] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[9] & 0x80) == 0 )
      *(_DWORD *)(*(_DWORD *)pxContext + 16) = 1090519040;
    if ( (Keyboard_tKeyboard.anCurrentKey[10] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[10] & 0x80) == 0 )
      *(_DWORD *)(*(_DWORD *)pxContext + 16) = 1091567616;
    if ( (Keyboard_tKeyboard.anCurrentKey[11] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[11] & 0x80) == 0 )
      *(_DWORD *)(*(_DWORD *)pxContext + 16) = 0;
  }
}

// source: j/0/vehicles/heli.c:1342  [size]
void __cdecl Heli_RestoreKeyframeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  Vehicle_RestoreKeyframeHandler(ptQTask, pxContext);
}

// source: j/0/vehicles/heli.c:1378  [anchor-mhash]
void __cdecl Heli_SaveKeyframeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // esi

  v2 = *(_DWORD *)pxContext;
  Vehicle_SaveKeyframeHandler(ptQTask, pxContext);
  *(_DWORD *)(v2 + 112) = 0;
}

// source: j/0/vehicles/heli.c:1410  [size]
void __cdecl Heli_WeaponHitHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: j/0/vehicles/heli.c:1491  [anchor-mhash]
void __cdecl Heli_ParsePhysicsObjTypeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  HeliType_DefineHeliType(*(struct HeliType_s **)pxContext, (int *)pxContext + 2, *((struct ArgList_s **)pxContext + 1));
}

// source: j/0/vehicles/heli.c:1510  [size]
void __cdecl Heli_GetGetPhysicsObjTypeSizeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = 340;
}

// source: j/0/vehicles/heli.c:1526  [size]
void __cdecl Heli_RemoveHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRemoveQTaskEvent][Vehicle_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  QTask_DeleteQTaskAndQTaskRefSafe(&ptQTask[48].tQTaskRefList.ptTail);
}

// source: j/0/vehicles/heli.c:1661  [size]
struct QTask_s *__cdecl Heli_HitZoneDestroyedHandler(
        struct QTask_s *ptQTask,
        void *pxContext)
{
  LOBYTE(ptQTask[48].ptParent) = 1;
  return ptQTask;
}

// source: j/0/vehicles/heli.c:1680  [size]
void __cdecl Heli_ExplosionHitHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: j/0/vehicles/heli.c:1723  [size]
void __cdecl Heli_AILineOfSightHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_BYTE *)pxContext = *((struct QTask_s **)pxContext + 2) != ptQTask && *((struct QTask_s **)pxContext + 3) != ptQTask;
}

// source: j/0/vehicles/heli.c:1751  [size]
void __cdecl Heli_ComputerMapFollowQTaskEventHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_BYTE *)pxContext = 1;
}

// source: j/0/vehicles/heli.c:1770  [size]
void __cdecl Heli_GetAIDetectionHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = ptQTask + 58;
  *((_DWORD *)pxContext + 1) = ptQTask + 55;
}

// source: j/0/vehicles/heli.c:1792  [anchor-strings]
void __cdecl Heli_Open()
{
  unsigned __int16 v0; // si
  __int16 v1; // ax
  struct ParameterList_s *v2; // eax
  int v3; // edx

  v0 = QTask_NewQTaskType("Heli", 22360, Vehicle_eQTaskType, 0, 0);
  Heli_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 0, Heli_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, Heli_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, Heli_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Heli_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, Heli_UpdateInternalDataHandler);
  v1 = SoundSys_eUpdateParameterListQTaskEvent;
  if ( SoundSys_eUpdateParameterListQTaskEvent == 512 )
  {
    v1 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.nRealFadeCount);
    v0 = Heli_eQTaskType;
    SoundSys_eUpdateParameterListQTaskEvent = v1;
  }
  QTask_LinkQTaskEventHandlerFn(v0, v1, Heli_SoundUpdateParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    GameFunctions_eWeaponHitQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Heli_WeaponHitHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    GameFunctions_eExplosionHitQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Heli_ExplosionHitHandler);
  QTask_LinkQTaskEventHandlerFn(v0, AnimQTask_eUpdateAnimDataEvent, Heli_UpdateAnimDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    AnimQTask_eGetChannelDescriptionEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Heli_GetChannelDescriptionHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    AnimQTask_eGetKeyframeSizeEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Heli_GetKeyframeSizeHandler);
  QTask_LinkQTaskEventHandlerFn(v0, AnimQTask_eReadChannelsEvent, Heli_ReadChannelsHandler);
  QTask_LinkQTaskEventHandlerFn(v0, AnimQTask_eRestoreKeyframeEvent, Heli_RestoreKeyframeHandler);
  QTask_LinkQTaskEventHandlerFn(v0, AnimQTask_eSaveKeyframeEvent, Heli_SaveKeyframeHandler);
  QTask_LinkQTaskEventHandlerFn(v0, PhysicsObjType_eParsePhysicsObjTypeEvent, Heli_ParsePhysicsObjTypeHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    PhysicsObjType_eGetPhysicsObjTypeSizeEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Heli_GetGetPhysicsObjTypeSizeHandler);
  QTask_LinkQTaskEventHandlerFn(v0, DynCubeObj_eDynCubeObjRemoveQTaskEvent, Heli_RemoveHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    AIDetection_eLineOfSightQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Heli_AILineOfSightHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ComputerMap_eFollowQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Heli_ComputerMapFollowQTaskEventHandler);
  QTask_LinkQTaskEventHandlerFn(v0, AIDetection_eGetAIDetectionEvent, Heli_GetAIDetectionHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  v2 = (struct ParameterList_s *)Mem_AllocFn(272, 4);
  v2->ptParameterListItem = (struct ParameterListItem_s *)&v2[1];
  v3 = Level_eParameterTypeObjectPos;
  v2->nParameters = 0;
  v2->nMaxParameters = 13;
  Heli_ptParameterList = v2;
  dword_79EE590 = 0;
  dword_79EE594 = 0;
  dword_79EE598 = 0;
  dword_79EE59C = 1083129856;
  ParameterList_AddParameter(v2, 0x1B8u, v3, "Position", 7u, nullptr);
  ParameterList_AddParameter(Heli_ptParameterList, 0x1DCu, Level_eParameterTypeReal32x9, "Orientation", 7u, nullptr);
  ParameterList_AddParameter(
    Heli_ptParameterList,
    0x790u,
    Level_eParameterTypeReal32,
    "Original Thrust",
    7u,
    &unk_6B09E8);
  ParameterList_AddParameter(Heli_ptParameterList, 0x1D0u, Level_eParameterTypeReal32x3, "Speed", 7u, nullptr);
  ParameterList_AddParameter(Heli_ptParameterList, 0x1A4u, Level_eParameterTypeString16, "Model", 7u, nullptr);
  ParameterList_AddParameter(
    Heli_ptParameterList,
    0x728u,
    Level_eParameterTypebool8,
    "Collision detection",
    7u,
    nullptr);
  ParameterList_AddParameter(Heli_ptParameterList, 0x729u, Level_eParameterTypebool8, "Force Z", 7u, nullptr);
  ParameterList_AddParameter(Heli_ptParameterList, 0x7A8u, Level_eParameterTypeVarString, "Open door", 7u, nullptr);
  ParameterList_AddParameter(Heli_ptParameterList, 0x7F8u, Level_eParameterTypeVarString, "Can fire", 7u, nullptr);
  ParameterList_AddParameter(Heli_ptParameterList, 0x848u, Level_eParameterTypeVarString, "Play sound", 7u, nullptr);
  ParameterList_AddParameter(
    Heli_ptParameterList,
    0x5748u,
    Level_eParameterTypeDegrees,
    "ViewCone Alpha (degrees)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Heli_ptParameterList,
    0x574Cu,
    Level_eParameterTypeDegrees,
    "ViewCone Gamma (degrees)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Heli_ptParameterList,
    0x5750u,
    Level_eParameterTypeReal32,
    "ViewCone Length (meter)",
    7u,
    &dword_79EE590);
  Symbol_Register(
    "TASKTYPE_HELI",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)Heli_eQTaskType,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}

// source: j/0/vehicles/heli.c:1872  [size]
void __cdecl Heli_Close()
{
  int v0; // esi

  if ( Heli_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&Heli_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(Heli_eQTaskType);
}

// source: j/0/vehicles/heli.c:1889  [size]
unsigned __int16 __cdecl Heli_GetQTaskType()
{
  return Heli_eQTaskType;
}
