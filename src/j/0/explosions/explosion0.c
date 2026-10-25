/* j/0/explosions/explosion0.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/explosions/explosion0.c:211  [size]
void __cdecl Explosion0_DeSerializeDoneHandler(struct QTask_s *ptQTask, void *pxContext)
{
  QTask_Delete(ptQTask);
}

// source: j/0/explosions/explosion0.c:234  [anchor-strings]
struct QTask_s *__cdecl Explosion0_FireBallNew(
        struct real64x3_t *ptPos,
        char *zModel,
        float vRadius,
        int nLifetime,
        int nFadeinTime,
        int nFadeoutTime,
        int nDelay,
        int nAnimationDuration,
        float vStartRotation,
        float vDeltaRotationZ)
{
  struct QTask_s *v10; // esi
  struct LODVirModel_s *LODVirModelExistsFn; // eax
  double v12; // st7
  double v13; // st7
  int *v14; // eax
  int v15; // eax
  double v16; // st6
  float ptDynCubeObj; // [esp+0h] [ebp-10h]

  v10 = QTask_NewFn(Level_ptDynamicQTask, Explosion0_eFireBallQTaskType, nullptr);
  LODVirModelExistsFn = MTP_GetLODVirModelExistsFn(zModel);
  if ( !LODVirModelExistsFn )
  {
    LDebug_Error("VirModel is null");
    abort();
  }
  if ( LODVirModelExistsFn != *(struct LODVirModel_s **)&v10[2].eQTaskType )
  {
    ModelObj_SetLODVirModel((struct ModelObj_s *)v10, LODVirModelExistsFn, false);
    v10[7].tQTaskRefList.ptHead = nullptr;
    v10[7].tQTaskRefList.ptMiddle = nullptr;
    v10[7].tQTaskRefList.ptTail = nullptr;
    v10[7].ptParent = nullptr;
    *(_DWORD *)&v10[7].eQTaskType = 0;
  }
  if ( *(float *)&v10[6].tQTaskChildren.ptHead <= (double)*(float *)&v10[6].tQTaskChildren.ptMiddle )
    v12 = *(float *)&v10[6].tQTaskChildren.ptMiddle;
  else
    v12 = *(float *)&v10[6].tQTaskChildren.ptHead;
  if ( v12 >= *(float *)&v10[6].ptPrev )
  {
    if ( *(float *)&v10[6].tQTaskChildren.ptHead <= (double)*(float *)&v10[6].tQTaskChildren.ptMiddle )
      v13 = *(float *)&v10[6].tQTaskChildren.ptMiddle;
    else
      v13 = *(float *)&v10[6].tQTaskChildren.ptHead;
  }
  else
  {
    v13 = *(float *)&v10[6].ptPrev;
  }
  v14 = *(int **)&v10[2].eQTaskType;
  if ( v14 && (v15 = *v14) != 0 )
    v16 = *(float *)(*(_DWORD *)(*(_DWORD *)(v15 + 12) + 12) + 120);
  else
    v16 = 1.0;
  ptDynCubeObj = v13 * v16;
  World_MoveDynCubeObjRadius(Game_ptGame->ptWorld, (struct DynCubeObj_s *)v10, ptPos, ptDynCubeObj);
  v10[6].ptPrev = (struct QTask_s *)981668463;
  v10[6].tQTaskChildren.ptHead = (struct QTask_s *)981668463;
  v10[6].tQTaskChildren.ptMiddle = (struct QTask_s *)981668463;
  v10[8].tQTaskChildren.ptMiddle = (struct QTask_s *)nDelay;
  *(float *)&v10[8].ptParent = vStartRotation;
  *(float *)&v10[8].tQTaskRefList.ptTail = vRadius * 0.00048828125;
  v10[8].ptPrev = (struct QTask_s *)nLifetime;
  v10[8].tQTaskChildren.ptHead = (struct QTask_s *)nLifetime;
  v10[8].tQTaskChildren.ptTail = (struct QTask_s *)nFadeinTime;
  v10[8].tQTaskRefList.ptHead = (struct QReference_s *)nFadeinTime;
  v10[8].tQTaskRefList.ptMiddle = (struct QReference_s *)nAnimationDuration;
  *(float *)&v10[8].eQTaskType = vDeltaRotationZ;
  return v10;
}

// source: j/0/explosions/explosion0.c:311  [anchor-mhash]
struct QTask_s *__cdecl Explosion0_AddSmoke(
        struct Explosion0Smoke_s *ptSmoke,
        int nQGraphicsFlag,
        struct real32x2_t *ptSize,
        float vSizeDelta,
        int nPartLifetime,
        int nPartFadetime,
        float vIntensity)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct World_s *ptWorld; };
    struct { char igi2_o1[28]; float ptVel; };
    struct { char igi2_o2[32]; float vRotation; };
    struct { char igi2_o3[56]; IGI2_INT128 tRGB; };
    struct { char igi2_o4[72]; int tAccel_4; };
    struct { char igi2_o5[76]; int tAccel_8; };
    char igi2_extent[80];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v7; // ebx
  struct Game_s *v8; // eax
  int v9; // ecx
  int v10; // ecx
  unsigned int v11; // edx
  double v12; // st7
  int v13; // ecx
  int v14; // edx
  unsigned int v15; // edx

  igi2_frame.ptWorld = Game_ptGame->ptWorld;
  BYTE13(igi2_frame.tRGB) = 0;
  HIWORD(igi2_frame.tRGB) = 0;
  igi2_frame.tAccel_4 = 0;
  igi2_frame.tAccel_8 = 1074706700;
  strcpy((char *)&igi2_frame.tRGB, "33KA33KA33KA");
  v7 = Particle2DDynCubeObj_New(
         Level_ptDynamicQTask,
         igi2_frame.ptWorld,
         &Explosion0_ptSmoke->tQSprite,
         (struct real32x3_t *)&igi2_frame.tRGB + 1,
         (struct real32x3_t *)&igi2_frame.tRGB,
         ptSize,
         819200.0,
         nQGraphicsFlag,
         0,
         vSizeDelta,
         0.0,
         1,
         nullptr);
  v8 = Game_ptGame;
  BYTE1(v7[6].tQTaskRefList.ptHead) = 1;
  v9 = (v8->tRunRandomState.anRandom[0] >> 7) ^ v8->tRunRandomState.anRandom[2];
  v8->tRunRandomState.anRandom[2] = v9;
  v10 = v9 ^ v8->tRunRandomState.anRandom[1];
  v8->tRunRandomState.anRandom[1] = v10;
  v11 = v10 + v8->tRunRandomState.anRandom[0];
  v12 = (double)(unsigned __int16)(v10 + LOWORD(v8->tRunRandomState.anRandom[0]));
  HIDWORD(igi2_frame.tRGB) = 0;
  igi2_frame.tAccel_4 = 0;
  igi2_frame.tAccel_8 = 1065353216;
  v8->tRunRandomState.anRandom[0] = v11;
  v13 = (v8->tRunRandomState.anRandom[0] >> 7) ^ v8->tRunRandomState.anRandom[2];
  v14 = v13 ^ v8->tRunRandomState.anRandom[1];
  v8->tRunRandomState.anRandom[2] = v13;
  v8->tRunRandomState.anRandom[1] = v14;
  v15 = v14 + v8->tRunRandomState.anRandom[0];
  v8->tRunRandomState.anRandom[0] = v15;
  igi2_frame.vRotation = v12 * 0.0000152587890625 * 6.2831854820251465;
  igi2_frame.ptVel = (0.5 - (double)(unsigned __int16)v15 * 0.0000152587890625) * 0.018849557265639305;
  Particle2DDynCubeObj_AddParticle(
    v7,
    &ptSmoke->tPos,
    (struct real32x3_t *)&igi2_frame.tRGB + 1,
    vIntensity,
    igi2_frame.ptVel,
    igi2_frame.vRotation,
    1.0,
    nPartLifetime,
    nPartFadetime);
  return v7;
}

// source: j/0/explosions/explosion0.c:381  [anchor-callee]
void __cdecl Explosion0_FragmentInitTail(struct Fragment_t *ptFragment, float vRadius)
{
  #pragma pack(push, 1)
  union
  {
    struct { float nAnimDelta; };
    struct { char igi2_o1[24]; struct real32x2_t tSize; };
    struct { char igi2_o2[32]; char tRGB[13]; };
    struct { char igi2_o3[45]; char tAccel_1; };
    struct { char igi2_o4[46]; __int16 tAccel_2; };
    struct { char igi2_o5[48]; int tAccel_4; };
    struct { char igi2_o6[52]; int tAccel_8; };
    char igi2_extent[56];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  enum FragmentType_e eFragmentType; // eax
  double vScale; // st7
  double v4; // st7
  struct QTask_s *v5; // eax
  struct GameSprite_t *v6; // edx
  struct QTask_s *v7; // eax
  struct QTask_s *v8; // eax
  float ptFragmenta = *(float *)&vRadius; // [esp+3Ch] [ebp+4h] ARGSLOT

  eFragmentType = ptFragment->eFragmentType;
  igi2_frame.tAccel_1 = 0;
  igi2_frame.tAccel_2 = 0;
  igi2_frame.tSize.vX = vRadius * 0.5;
  igi2_frame.tAccel_4 = 0;
  igi2_frame.tSize.vY = igi2_frame.tSize.vX;
  igi2_frame.tAccel_8 = 1066318092;
  vScale = ptFragment->vScale;
  strcpy(igi2_frame.tRGB, "33KA33KA33KA");
  v4 = vScale * 15.0;
  if ( eFragmentType == FRAGMENTTYPE_FIRE )
  {
    ptFragmenta = 1.0 / v4;
    v5 = Particle2DDynCubeObj_New(
           &ptFragment->tSimpointObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask,
           Game_ptGame->ptWorld,
           &Explosion0_ptFireball->tQSprite,
           (struct real32x3_t *)&igi2_frame.tRGB[12],
           (struct real32x3_t *)igi2_frame.tRGB,
           &igi2_frame.tSize,
           819200.0,
           8,
           0,
           ptFragmenta,
           0.0,
           200,
           nullptr);
    v6 = Explosion0_ptSmoke;
    ptFragment->ptFire = v5;
    BYTE1(v5[6].tQTaskRefList.ptHead) = 0;
    v7 = Particle2DDynCubeObj_New(
           Level_ptDynamicQTask,
           Game_ptGame->ptWorld,
           &v6->tQSprite,
           (struct real32x3_t *)&igi2_frame.tRGB[12],
           (struct real32x3_t *)igi2_frame.tRGB,
           &igi2_frame.tSize,
           819200.0,
           16,
           0,
           ptFragmenta,
           0.0,
           200,
           nullptr);
    ptFragment->ptSmoke = v7;
    BYTE1(v7[6].tQTaskRefList.ptHead) = 0;
  }
  else if ( eFragmentType == FRAGMENTTYPE_SMOKE )
  {
    igi2_frame.nAnimDelta = 1.0 / v4;
    v8 = Particle2DDynCubeObj_New(
           Level_ptDynamicQTask,
           Game_ptGame->ptWorld,
           &Explosion0_ptSmoke->tQSprite,
           (struct real32x3_t *)&igi2_frame.tRGB[12],
           (struct real32x3_t *)igi2_frame.tRGB,
           &igi2_frame.tSize,
           819200.0,
           8,
           0,
           igi2_frame.nAnimDelta,
           0.0,
           200,
           nullptr);
    ptFragment->ptSmoke = v8;
    BYTE1(v8[6].tQTaskRefList.ptHead) = 0;
  }
}

// source: j/0/explosions/explosion0.c:482  [anchor-mhash]
void __cdecl Explosion0_FragmentAddTail(struct Fragment_t *ptFragment)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v27; };
    struct { char igi2_o1[4]; float ptVel; };
    struct { char igi2_o2[4]; float ptVela; };
    struct { char igi2_o3[4]; float ptVelb; };
    struct { char igi2_o4[8]; float ptRandomState; };
    struct { char igi2_o5[8]; float ptRandomStatea; };
    struct { char igi2_o6[8]; float ptRandomStateb; };
    struct { char igi2_o7[40]; float vHalfTotalLifetime; };
    struct { char igi2_o8[44]; float vIntensity; };
    struct { char igi2_o9[44]; float vIntensitya; };
    struct { char igi2_o10[44]; float vIntensityb; };
    struct { char igi2_o11[48]; int nPartFadetime; };
    struct { char igi2_o12[52]; int nPartLifetime; };
    struct { char igi2_o13[64]; double vSpeed; };
    struct { char igi2_o14[72]; double vPos; };
    struct { char igi2_o15[80]; double vStep; };
    struct { char igi2_o16[92]; struct real32x3_t tSpeed; };
    struct { char igi2_o17[104]; struct real64x3_t tStep; };
    struct { char igi2_o18[128]; struct real64x3_t tPos; };
    char igi2_extent[152];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct RandomState_s *p_tRunRandomState; // esi
  double v2; // st7
  double nTotalLifetime; // st6
  unsigned int v4; // eax
  unsigned int v5; // edx
  unsigned int v6; // ecx
  int v7; // ebx
  enum FragmentType_e eFragmentType; // eax
  double nLifetime; // st7
  double v10; // st7
  double v11; // st6
  double v12; // st7
  double v13; // st7
  double vX; // st6
  double vY; // st5
  struct RandomState_s *v16; // eax
  int v17; // edi
  unsigned int v18; // edx
  double v19; // st7
  double v20; // st6
  int v21; // ebx
  unsigned int v22; // edi
  double v23; // st5
  int v24; // ebx
  int v25; // edi
  int v26; // edx

  p_tRunRandomState = &Game_ptGame->tRunRandomState;
  v2 = ptFragment->vScale * 27.0;
  nTotalLifetime = (double)ptFragment->nTotalLifetime;
  v4 = (Game_ptGame->tRunRandomState.anRandom[0] >> 7) ^ Game_ptGame->tRunRandomState.anRandom[2];
  v5 = v4 ^ Game_ptGame->tRunRandomState.anRandom[1];
  Game_ptGame->tRunRandomState.anRandom[2] = v4;
  v6 = v5 + p_tRunRandomState->anRandom[0];
  igi2_frame.vHalfTotalLifetime = nTotalLifetime * 0.5;
  memset(&igi2_frame.tSpeed, 0, sizeof(igi2_frame.tSpeed));
  v7 = (__int64)(0.10000000149011612 * v2);
  igi2_frame.nPartLifetime = v7;
  p_tRunRandomState->anRandom[1] = v5;
  p_tRunRandomState->anRandom[0] = v6;
  eFragmentType = ptFragment->eFragmentType;
  igi2_frame.nPartFadetime = (__int64)(((double)(unsigned __int16)v6 * 0.0000152587890625 * 0.20000000298023224 + 0.800000011920929) * v2);
  if ( eFragmentType == FRAGMENTTYPE_FIRE )
  {
    nLifetime = (double)ptFragment->tSimpointObj.nLifetime;
    if ( nLifetime > igi2_frame.vHalfTotalLifetime )
    {
      igi2_frame.vIntensity = Random_GetRandomNumberReal32(p_tRunRandomState)
                 * ((nLifetime - igi2_frame.vHalfTotalLifetime)
                  / igi2_frame.vHalfTotalLifetime
                  * 0.20000000298023224);
      igi2_frame.ptRandomState = Random_GetRandomNumberReal32(p_tRunRandomState) * 6.2831854820251465;
      igi2_frame.ptVel = (0.5 - Random_GetRandomNumberReal32(p_tRunRandomState)) * 0.006283185910433531;
      Particle2DDynCubeObj_AddParticle(
        ptFragment->ptFire,
        &ptFragment->tSimpointObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos,
        &igi2_frame.tSpeed,
        igi2_frame.vIntensity,
        igi2_frame.ptVel,
        igi2_frame.ptRandomState,
        1.0,
        v7,
        igi2_frame.nPartFadetime);
    }
    v10 = (double)ptFragment->tSimpointObj.nLifetime;
    v11 = igi2_frame.vHalfTotalLifetime * 1.5;
    if ( v10 < v11 )
    {
      igi2_frame.vIntensitya = Random_GetRandomNumberReal32(p_tRunRandomState) * (v10 / v11 * 0.20000000298023224);
      igi2_frame.ptRandomStatea = Random_GetRandomNumberReal32(p_tRunRandomState) * 6.2831854820251465;
      igi2_frame.ptVela = (0.5 - Random_GetRandomNumberReal32(p_tRunRandomState)) * 0.006283185910433531;
      Particle2DDynCubeObj_AddParticle(
        ptFragment->ptSmoke,
        &ptFragment->tSimpointObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos,
        &igi2_frame.tSpeed,
        igi2_frame.vIntensitya,
        igi2_frame.ptVela,
        igi2_frame.ptRandomStatea,
        1.0,
        v7,
        igi2_frame.nPartFadetime);
    }
  }
  else if ( eFragmentType == FRAGMENTTYPE_SMOKE && (double)ptFragment->tSimpointObj.nLifetime > igi2_frame.vHalfTotalLifetime )
  {
    igi2_frame.vPos = 0.0;
    v12 = ptFragment->vScale * 4096.0;
    igi2_frame.vSpeed = sqrt(
               ptFragment->tSimpointObj.tVelocity.vX * ptFragment->tSimpointObj.tVelocity.vX
             + ptFragment->tSimpointObj.tVelocity.vY * ptFragment->tSimpointObj.tVelocity.vY
             + ptFragment->tSimpointObj.tVelocity.vZ * ptFragment->tSimpointObj.tVelocity.vZ);
    v13 = igi2_frame.vSpeed <= v12 ? igi2_frame.vSpeed : igi2_frame.vSpeed / v12;
    igi2_frame.vStep = v13;
    vX = ptFragment->tSimpointObj.tVelocity.vX;
    vY = ptFragment->tSimpointObj.tVelocity.vY;
    igi2_frame.tStep.vZ = ptFragment->tSimpointObj.tVelocity.vZ;
    qmemcpy(&igi2_frame.tPos, &ptFragment->tSimpointObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos, sizeof(igi2_frame.tPos));
    igi2_frame.tStep.vX = vX * v13;
    igi2_frame.tStep.vY = vY * v13;
    igi2_frame.tStep.vZ = igi2_frame.tStep.vZ * v13;
    if ( igi2_frame.vSpeed > 0.0 )
    {
      do
      {
        v16 = p_tRunRandomState;
        v17 = (p_tRunRandomState->anRandom[0] >> 7) ^ p_tRunRandomState->anRandom[2] ^ p_tRunRandomState->anRandom[1];
        v18 = v17 + p_tRunRandomState->anRandom[0];
        igi2_frame.vIntensityb = 1.0 / igi2_frame.vHalfTotalLifetime;
        v19 = ((double)ptFragment->tSimpointObj.nLifetime - igi2_frame.vHalfTotalLifetime) * igi2_frame.vIntensityb * 0.20000000298023224;
        v20 = (double)(unsigned __int16)(((p_tRunRandomState->anRandom[0] >> 7)
                                        ^ LOWORD(p_tRunRandomState->anRandom[2])
                                        ^ LOWORD(p_tRunRandomState->anRandom[1]))
                                       + LOWORD(p_tRunRandomState->anRandom[0]));
        p_tRunRandomState->anRandom[2] ^= p_tRunRandomState->anRandom[0] >> 7;
        p_tRunRandomState->anRandom[1] = v17;
        p_tRunRandomState->anRandom[0] = v18;
        v21 = (v16->anRandom[0] >> 7) ^ v16->anRandom[2] ^ v16->anRandom[1];
        v22 = v21 + p_tRunRandomState->anRandom[0];
        v23 = (double)(unsigned __int16)(((v16->anRandom[0] >> 7) ^ LOWORD(v16->anRandom[2]) ^ LOWORD(v16->anRandom[1]))
                                       + LOWORD(v16->anRandom[0]));
        p_tRunRandomState->anRandom[2] ^= p_tRunRandomState->anRandom[0] >> 7;
        p_tRunRandomState->anRandom[1] = v21;
        p_tRunRandomState->anRandom[0] = v22;
        v24 = (v16->anRandom[0] >> 7) ^ v16->anRandom[2];
        v25 = v24 ^ p_tRunRandomState->anRandom[1];
        v26 = (v24 ^ v16->anRandom[1]) + v16->anRandom[0];
        p_tRunRandomState->anRandom[0] = v26;
        p_tRunRandomState->anRandom[2] = v24;
        p_tRunRandomState->anRandom[1] = v25;
        igi2_frame.ptRandomStateb = v23 * 0.0000152587890625 * 6.2831854820251465;
        igi2_frame.ptVelb = (0.5 - (double)(unsigned __int16)v26 * 0.0000152587890625) * 0.006283185910433531;
        igi2_frame.v27 = v20 * 0.0000152587890625 * v19;
        Particle2DDynCubeObj_AddParticle(
          ptFragment->ptSmoke,
          &igi2_frame.tPos,
          &igi2_frame.tSpeed,
          igi2_frame.v27,
          igi2_frame.ptVelb,
          igi2_frame.ptRandomStateb,
          1.0,
          igi2_frame.nPartLifetime,
          igi2_frame.nPartFadetime);
        igi2_frame.tPos.vX = igi2_frame.tPos.vX + igi2_frame.tStep.vX;
        igi2_frame.tPos.vY = igi2_frame.tPos.vY + igi2_frame.tStep.vY;
        igi2_frame.tPos.vZ = igi2_frame.tPos.vZ + igi2_frame.tStep.vZ;
        igi2_frame.vPos = igi2_frame.vStep + igi2_frame.vPos;
      }
      while ( igi2_frame.vPos < igi2_frame.vSpeed );
    }
  }
}

// source: j/0/explosions/explosion0.c:629  [anchor-callee]
struct QTask_s *__cdecl Explosion0_FragmentNew(
        struct Explosion0_t *ptExplosion,
        struct real64x3_t *ptPos,
        struct real32x3_t *ptSpeed,
        enum FragmentType_e eFragmentType,
        float vRadius)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDest; };
    struct { char igi2_o1[4]; float vAlpha; };
    struct { char igi2_o2[8]; float vBeta; };
    struct { char igi2_o3[8]; float vBetaa; };
    struct { char igi2_o4[20]; struct real32x9_t tOrientation; };
    char igi2_extent[60];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Game_s *v5; // eax
  unsigned int v6; // ecx
  unsigned int v7; // edx
  unsigned int v8; // esi
  double v9; // st7
  int v10; // ecx
  int v11; // edx
  unsigned int v12; // esi
  double v13; // st6
  int v14; // ecx
  int v15; // esi
  unsigned int v16; // edx
  double v17; // st7
  struct SimpointObj_s *v18; // esi
  int nLifetime; // ecx

  v5 = Game_ptGame;
  v6 = (Game_ptGame->tRunRandomState.anRandom[0] >> 7) ^ Game_ptGame->tRunRandomState.anRandom[2];
  v7 = v6 ^ Game_ptGame->tRunRandomState.anRandom[1];
  Game_ptGame->tRunRandomState.anRandom[2] = v6;
  v8 = v7 + v5->tRunRandomState.anRandom[0];
  v9 = (double)(unsigned __int16)(v7 + LOWORD(v5->tRunRandomState.anRandom[0]));
  v5->tRunRandomState.anRandom[1] = v7;
  v5->tRunRandomState.anRandom[0] = v8;
  v10 = (v5->tRunRandomState.anRandom[0] >> 7) ^ v5->tRunRandomState.anRandom[2];
  v11 = v10 ^ v5->tRunRandomState.anRandom[1];
  v5->tRunRandomState.anRandom[2] = v10;
  v12 = v11 + v5->tRunRandomState.anRandom[0];
  v13 = (double)(unsigned __int16)(v11 + LOWORD(v5->tRunRandomState.anRandom[0]));
  v5->tRunRandomState.anRandom[1] = v11;
  v5->tRunRandomState.anRandom[0] = v12;
  v14 = (v5->tRunRandomState.anRandom[0] >> 7) ^ v5->tRunRandomState.anRandom[2];
  v15 = v14 ^ v5->tRunRandomState.anRandom[1];
  v5->tRunRandomState.anRandom[2] = v14;
  v16 = v15 + v5->tRunRandomState.anRandom[0];
  igi2_frame.vBeta = v9 * 0.0000152587890625 * 0.03141592815518379;
  v5->tRunRandomState.anRandom[1] = v15;
  v5->tRunRandomState.anRandom[0] = v16;
  igi2_frame.vAlpha = v13 * 0.0000152587890625 * 0.03141592815518379;
  igi2_frame.ptDest = (double)(unsigned __int16)v16 * 0.0000152587890625 * 0.03141592815518379;
  Real32x9_Create(&igi2_frame.tOrientation, igi2_frame.ptDest, igi2_frame.vAlpha, igi2_frame.vBeta);
  v17 = vRadius * 0.00048828125;
  v18 = SimpointObjContainer_Add(
          ptExplosion->ptSimpointObjContainer,
          Explosion0_eFragmentQTaskType,
          ptPos,
          &igi2_frame.tOrientation,
          ptSpeed);
  nLifetime = ptExplosion->ptSimpointObjContainer->nLifetime;
  *(float *)&v18[1].tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.tQTaskChildren.ptTail = v17;
  v18->tRigidDynCubeObj.tModelObj.tScale.vX = v17;
  v18->tRigidDynCubeObj.tModelObj.tScale.vY = v17;
  v18->tRigidDynCubeObj.tModelObj.tScale.vZ = v17;
  v18[1].tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.ptNext = (struct QTask_s *)nLifetime;
  v18[1].tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.tQTaskChildren.ptHead = nullptr;
  v18[1].tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.tQTaskChildren.ptMiddle = nullptr;
  v18[1].tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.ptPrev = (struct QTask_s *)eFragmentType;
  if ( eFragmentType )
  {
    igi2_frame.vBetaa = vRadius + vRadius;
    Explosion0_FragmentInitTail((struct Fragment_t *)v18, igi2_frame.vBetaa);
  }
  return &v18->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask;
}

// source: j/0/explosions/explosion0.c:697  [anchor-mhash]
void __cdecl Explosion0_SmokeNew(struct real64x3_t *ptPos, float vRadius, int nLifetime)
{
  struct QTask_s *v3; // eax

  v3 = QTask_NewFn(Level_ptDynamicQTask, Explosion0_eSmokeQTaskType, nullptr);
  qmemcpy(&v3[1].tQTaskChildren, ptPos, 0x18u);
  v3[1].ptNext = (struct QTask_s *)nLifetime;
  v3[1].ptPrev = (struct QTask_s *)nLifetime;
  *(float *)&v3[1].ptParent = vRadius;
  *(_DWORD *)&v3[1].eQTaskType = 0;
}

// source: j/0/explosions/explosion0.c:733  [anchor-strings]
void __cdecl Explosion0_CreateExplosion(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vRadius; };
    struct { float vRadiusa; };
    struct { char igi2_o2[12]; int v69; };
    struct { char igi2_o3[16]; int v70; };
    struct { char igi2_o4[28]; float v71; };
    struct { char igi2_o5[40]; int nSmokeLifetime; };
    struct { char igi2_o6[40]; int nSmokeLifetimea; };
    struct { char igi2_o7[44]; struct QTask_s *ptFireBallQTask; };
    struct { char igi2_o8[64]; float *p_eQTaskType; };
    struct { char igi2_o9[64]; float v75; };
    struct { char igi2_o10[68]; double ltcg_edx[2]; };
    struct { char igi2_o11[84]; struct real32x3_t tSpeed; };
    struct { char igi2_o12[100]; struct real64x3_t tPos; };
    struct { char igi2_o13[124]; struct QTask_s *ptTail; };
    struct { char igi2_o14[128]; int v81; };
    struct { char igi2_o15[132]; struct QReference_s *v82; };
    struct { char igi2_o16[136]; int v83; };
    struct { char igi2_o17[140]; struct QTask_s *v84; };
    struct { char igi2_o18[148]; struct real64x3_t ptPos; };
    char igi2_extent[172];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v1; // ebx
  int v2; // eax
  int v3; // edx
  struct Game_s *v4; // eax
  unsigned int v5; // edi
  unsigned int v6; // esi
  double v7; // st7
  int v8; // ebx
  int v9; // esi
  unsigned int v10; // ecx
  int v11; // ebx
  int v12; // edi
  unsigned int v13; // esi
  double v14; // st6
  int v15; // ebx
  unsigned int v16; // edi
  double v17; // st5
  int v18; // esi
  unsigned int v19; // ebx
  double v20; // st4
  unsigned int v21; // ecx
  unsigned int v22; // ebx
  unsigned int v23; // edi
  int v24; // ebx
  int v25; // edi
  unsigned int v26; // edi
  double v27; // st4
  int v28; // ecx
  int v29; // ecx
  unsigned int v30; // esi
  int v31; // esi
  double v32; // st6
  int v33; // eax
  struct QTask_s *v34; // eax
  int ptParent; // eax
  int v36; // esi
  struct Game_s *v37; // edi
  float v38; // eax
  float v39; // ecx
  unsigned int v40; // edx
  unsigned int v41; // eax
  unsigned int v42; // edx
  unsigned int v43; // ecx
  unsigned int v44; // edx
  long double v45; // st4
  struct real32x3_t *RandomUnitVectorInCone; // eax
  float vX; // ecx
  float vY; // edx
  float vZ; // eax
  unsigned int v50; // eax
  unsigned int v51; // edx
  double v52; // st7
  int v53; // edx
  double v54; // st7
  int v55; // ecx
  struct QTask_s *v56; // eax
  struct QReference_s *ptMiddle; // edx
  int v58; // esi
  void *pxObject; // edi
  struct QTask_s *ptHead; // eax
  struct QTask_s *v61; // ecx
  struct QReference_s *v62; // ecx
  int v63; // esi
  struct QTask_s *v64; // ecx
  struct QTaskList_s *v65; // eax
  int v66; // edi

  v1 = ptQTask;
  igi2_frame.ltcg_edx[0] = *(float *)&ptQTask[2].tQTaskChildren.ptTail + *(float *)&ptQTask[2].tQTaskChildren.ptMiddle;
  if ( igi2_frame.ltcg_edx[0] != 0.0 )
  {
    v2 = *(_DWORD *)&ptQTask[2].eQTaskType;
    qmemcpy(&igi2_frame.ptPos, &ptQTask[1], sizeof(igi2_frame.ptPos));
    if ( v2 )
    {
      igi2_frame.vRadius = igi2_frame.ltcg_edx[0];
      v1 = ptQTask;
      igi2_frame.ptFireBallQTask = Explosion0_FireBallNew(&igi2_frame.ptPos, "1006_01_1", igi2_frame.vRadius, 30, 0, 24, 0, 30, 0.0, 0.0);
    }
    v3 = 0;
    if ( (int)(*(_DWORD *)&v1[2].eQTaskType - 1) > 0 )
    {
      igi2_frame.v75 = igi2_frame.ltcg_edx[0];
      do
      {
        v4 = Game_ptGame;
        v5 = (Game_ptGame->tRunRandomState.anRandom[0] >> 7)
           ^ Game_ptGame->tRunRandomState.anRandom[2]
           ^ Game_ptGame->tRunRandomState.anRandom[1];
        v6 = v5 + Game_ptGame->tRunRandomState.anRandom[0];
        v7 = (double)(unsigned __int16)(((Game_ptGame->tRunRandomState.anRandom[0] >> 7)
                                       ^ LOWORD(Game_ptGame->tRunRandomState.anRandom[2])
                                       ^ LOWORD(Game_ptGame->tRunRandomState.anRandom[1]))
                                      + LOWORD(Game_ptGame->tRunRandomState.anRandom[0]));
        Game_ptGame->tRunRandomState.anRandom[2] ^= Game_ptGame->tRunRandomState.anRandom[0] >> 7;
        v4->tRunRandomState.anRandom[1] = v5;
        v4->tRunRandomState.anRandom[0] = v6;
        v8 = (v4->tRunRandomState.anRandom[0] >> 7) ^ v4->tRunRandomState.anRandom[2];
        v9 = v8 ^ v4->tRunRandomState.anRandom[1];
        v10 = v9 + v4->tRunRandomState.anRandom[0];
        v4->tRunRandomState.anRandom[0] = v10;
        v4->tRunRandomState.anRandom[2] = v8;
        v11 = (v10 >> 7) ^ v8;
        v4->tRunRandomState.anRandom[1] = v9;
        v12 = v11 ^ v4->tRunRandomState.anRandom[1];
        v13 = v12 + v4->tRunRandomState.anRandom[0];
        v14 = (double)(unsigned __int16)((v11 ^ LOWORD(v4->tRunRandomState.anRandom[1]))
                                       + LOWORD(v4->tRunRandomState.anRandom[0]));
        v4->tRunRandomState.anRandom[2] = v11;
        v4->tRunRandomState.anRandom[1] = v12;
        v4->tRunRandomState.anRandom[0] = v13;
        v15 = (v4->tRunRandomState.anRandom[0] >> 7) ^ v4->tRunRandomState.anRandom[2] ^ v4->tRunRandomState.anRandom[1];
        v16 = v15 + v4->tRunRandomState.anRandom[0];
        v17 = (double)(unsigned __int16)(((v4->tRunRandomState.anRandom[0] >> 7)
                                        ^ LOWORD(v4->tRunRandomState.anRandom[2])
                                        ^ LOWORD(v4->tRunRandomState.anRandom[1]))
                                       + LOWORD(v4->tRunRandomState.anRandom[0]));
        v4->tRunRandomState.anRandom[2] ^= v4->tRunRandomState.anRandom[0] >> 7;
        v4->tRunRandomState.anRandom[1] = v15;
        v4->tRunRandomState.anRandom[0] = v16;
        v18 = (v4->tRunRandomState.anRandom[0] >> 7) ^ v4->tRunRandomState.anRandom[2] ^ v4->tRunRandomState.anRandom[1];
        v19 = v18 + v4->tRunRandomState.anRandom[0];
        v20 = (double)(unsigned __int16)(((v4->tRunRandomState.anRandom[0] >> 7)
                                        ^ LOWORD(v4->tRunRandomState.anRandom[2])
                                        ^ LOWORD(v4->tRunRandomState.anRandom[1]))
                                       + LOWORD(v4->tRunRandomState.anRandom[0]));
        v4->tRunRandomState.anRandom[2] ^= v4->tRunRandomState.anRandom[0] >> 7;
        v4->tRunRandomState.anRandom[1] = v18;
        v4->tRunRandomState.anRandom[0] = v19;
        v21 = v4->tRunRandomState.anRandom[0];
        v22 = v4->tRunRandomState.anRandom[2];
        v23 = v4->tRunRandomState.anRandom[1];
        *(double *)&igi2_frame.tSpeed.vX = v20 * 0.0000152587890625;
        v24 = (v21 >> 7) ^ v22;
        v25 = v24 ^ v23;
        LOWORD(v18) = v25 + v21;
        v4->tRunRandomState.anRandom[2] = v24;
        v4->tRunRandomState.anRandom[1] = v25;
        v4->tRunRandomState.anRandom[0] = v25 + v21;
        v26 = v4->tRunRandomState.anRandom[1];
        v27 = ((double)(unsigned __int16)v18 * 0.0000152587890625 + 1.0)
            * (double)(int)igi2_frame.ptFireBallQTask[8].tQTaskChildren.ptHead;
        v28 = (v4->tRunRandomState.anRandom[0] >> 7) ^ v4->tRunRandomState.anRandom[2];
        v4->tRunRandomState.anRandom[2] = v28;
        v29 = v28 ^ v26;
        v30 = v29 + v4->tRunRandomState.anRandom[0];
        v4->tRunRandomState.anRandom[0] = v30;
        v4->tRunRandomState.anRandom[1] = v29;
        LOWORD(v4) = v30;
        qmemcpy(&igi2_frame.tPos, &igi2_frame.ptFireBallQTask[1], sizeof(igi2_frame.tPos));
        v31 = v3 + 1;
        igi2_frame.tPos.vX = (v14 * 0.0000152587890625 - 0.5) * igi2_frame.ltcg_edx[0] + igi2_frame.tPos.vX;
        igi2_frame.v70 = (__int64)(v27 * 0.5);
        igi2_frame.tPos.vY = (v17 * 0.0000152587890625 - 0.5) * igi2_frame.ltcg_edx[0] + igi2_frame.tPos.vY;
        igi2_frame.tPos.vZ = (*(double *)&igi2_frame.tSpeed.vX - 0.5) * igi2_frame.ltcg_edx[0] + igi2_frame.tPos.vZ;
        v32 = (double)igi2_frame.v70;
        igi2_frame.v69 = (__int64)((double)(unsigned __int16)v4 * 0.0000152587890625 * 6.0
                      + (double)(v3 + 1) / (double)*(int *)&ptQTask[2].eQTaskType * 30.0);
        *(_QWORD *)&igi2_frame.tSpeed.vX = (__int64)(0.0 * v32);
        igi2_frame.vRadiusa = (v7 * 0.0000152587890625 * 0.25 + 0.5) * igi2_frame.v75;
        Explosion0_FireBallNew(
          &igi2_frame.tPos,
          "1006_01_1",
          igi2_frame.vRadiusa,
          igi2_frame.v70,
          SLODWORD(igi2_frame.tSpeed.vX),
          (__int64)(0.8999999761581421 * v32),
          igi2_frame.v69,
          igi2_frame.v70,
          0.0,
          0.0);
        v3 = v31;
      }
      while ( v31 < (int)(*(_DWORD *)&ptQTask[2].eQTaskType - 1) );
      v1 = ptQTask;
    }
    v33 = *(_DWORD *)&v1[2].eQTaskType;
    if ( v33 <= 1 )
    {
      igi2_frame.nSmokeLifetime = 60;
    }
    else
    {
      *(_QWORD *)&igi2_frame.tSpeed.vX = (__int64)(60.0 - 60.0 / (double)v33 - 1.0 + 60.0);
      igi2_frame.nSmokeLifetime = LODWORD(igi2_frame.tSpeed.vX);
    }
    if ( v33 )
    {
      v34 = QTask_NewFn(Level_ptDynamicQTask, Explosion0_eSmokeQTaskType, nullptr);
      qmemcpy(&v34[1].tQTaskChildren, &igi2_frame.ptPos, 0x18u);
      *(float *)&v34[1].ptParent = igi2_frame.ltcg_edx[0] * 0.8999999761581421;
      v34[1].ptNext = (struct QTask_s *)igi2_frame.nSmokeLifetime;
      v34[1].ptPrev = (struct QTask_s *)igi2_frame.nSmokeLifetime;
      *(_DWORD *)&v34[1].eQTaskType = 0;
    }
    ptParent = (int)v1[2].ptParent;
    if ( ptParent )
    {
      v36 = 0;
      if ( ptParent > 0 )
      {
        igi2_frame.p_eQTaskType = (float *)&v1[1].eQTaskType;
        do
        {
          v37 = Game_ptGame;
          v38 = igi2_frame.p_eQTaskType[1];
          v39 = igi2_frame.p_eQTaskType[2];
          igi2_frame.tSpeed.vX = *igi2_frame.p_eQTaskType;
          v40 = Game_ptGame->tRunRandomState.anRandom[0];
          igi2_frame.tSpeed.vY = v38;
          v41 = (v40 >> 7) ^ Game_ptGame->tRunRandomState.anRandom[2];
          v42 = Game_ptGame->tRunRandomState.anRandom[0];
          igi2_frame.tSpeed.vZ = v39;
          v43 = v41 ^ Game_ptGame->tRunRandomState.anRandom[1];
          Game_ptGame->tRunRandomState.anRandom[2] = v41;
          v44 = v43 + v42;
          v37->tRunRandomState.anRandom[1] = v43;
          v37->tRunRandomState.anRandom[0] = v44;
          *(float *)&igi2_frame.nSmokeLifetimea = (double)(unsigned __int16)v44
                                     * 0.0000152587890625
                                     * (*(float *)&v1[2].tQTaskRefList.ptTail - *(float *)&v1[2].tQTaskRefList.ptMiddle)
                                     + *(float *)&v1[2].tQTaskRefList.ptMiddle;
          if ( igi2_frame.tSpeed.vX != 0.0 || igi2_frame.tSpeed.vY != 0.0 || igi2_frame.tSpeed.vZ != 0.0 )
          {
            v45 = sqrt(igi2_frame.tSpeed.vX * igi2_frame.tSpeed.vX + igi2_frame.tSpeed.vY * igi2_frame.tSpeed.vY + igi2_frame.tSpeed.vZ * igi2_frame.tSpeed.vZ);
            igi2_frame.tSpeed.vX = igi2_frame.tSpeed.vX * (1.0 / v45);
            igi2_frame.tSpeed.vY = igi2_frame.tSpeed.vY * (1.0 / v45);
            igi2_frame.tSpeed.vZ = igi2_frame.tSpeed.vZ * (1.0 / v45);
          }
          RandomUnitVectorInCone = GameFunctions_GetRandomUnitVectorInCone(
                                     (struct real32x3_t *)v1[2].tQTaskRefList.ptHead,
                                     igi2_frame.v71,
                                     &igi2_frame.tSpeed,
                                     (int)igi2_frame.ltcg_edx);
          vX = RandomUnitVectorInCone->vX;
          vY = RandomUnitVectorInCone->vY;
          vZ = RandomUnitVectorInCone->vZ;
          igi2_frame.tSpeed.vX = vX;
          igi2_frame.tSpeed.vZ = vZ;
          v50 = v37->tRunRandomState.anRandom[0];
          igi2_frame.tSpeed.vY = vY;
          v51 = v37->tRunRandomState.anRandom[2];
          igi2_frame.tSpeed.vX = vX * *(float *)&igi2_frame.nSmokeLifetimea;
          v52 = igi2_frame.tSpeed.vY * *(float *)&igi2_frame.nSmokeLifetimea;
          v53 = (v50 >> 7) ^ v51;
          v37->tRunRandomState.anRandom[2] = v53;
          igi2_frame.tSpeed.vY = v52;
          v54 = igi2_frame.tSpeed.vZ * *(float *)&igi2_frame.nSmokeLifetimea;
          v55 = v53 ^ v37->tRunRandomState.anRandom[1];
          v37->tRunRandomState.anRandom[1] = v55;
          igi2_frame.tSpeed.vZ = v54;
          v37->tRunRandomState.anRandom[0] = v55 + v50;
          Explosion0_FragmentNew((struct Explosion0_t *)v1, &igi2_frame.ptPos, &igi2_frame.tSpeed, FRAGMENTTYPE_NONE, 204.8000030517578);
          ++v36;
          v1 = ptQTask;
        }
        while ( v36 < (int)ptQTask[2].ptParent );
      }
      LOBYTE(v1[3].tQTaskChildren.ptTail[2].tQTaskRefList.ptMiddle) = 1;
    }
    v56 = SoundSys_NewSoundFn(Level_ptDynamicQTask, (char *)&v1[3]);
    if ( v56 )
      ((void (__cdecl *)(struct QTask_s *, struct real64x3_t *))QTask_aatQTaskFinalEvent[SoundSys_eSetPositionQTaskEvent][v56->eQTaskType].pfHandler)(
        v56,
        &igi2_frame.ptPos);
    if ( *(float *)&v1[2].tQTaskChildren.ptHead != 0.0 )
    {
      ptMiddle = v1[3].tQTaskRefList.ptMiddle;
      v58 = -1;
      if ( ptMiddle )
      {
        pxObject = ptMiddle->pxObject;
        if ( pxObject )
        {
          if ( QTask_IsQTaskTypeDerived(*((_WORD *)pxObject + 18), Human_eQTaskType) )
            v58 = *((_DWORD *)pxObject + 107);
        }
      }
      LODWORD(igi2_frame.tPos.vX) = igi2_frame.ptFireBallQTask;
      ptHead = v1[2].tQTaskChildren.ptHead;
      HIDWORD(igi2_frame.tPos.vY) = &igi2_frame.ptPos;
      v61 = v1[2].tQTaskChildren.ptMiddle;
      igi2_frame.v83 = v58;
      *(_QWORD *)&igi2_frame.tPos.vZ = __PAIR64__((unsigned int)v61, (unsigned int)ptHead);
      v62 = v1[3].tQTaskRefList.ptHead;
      v63 = 0;
      igi2_frame.ptTail = v1[2].tQTaskChildren.ptTail;
      igi2_frame.v81 = 90;
      igi2_frame.v82 = v62;
      if ( ptMiddle )
        HIDWORD(igi2_frame.tPos.vX) = ptMiddle->pxObject;
      else
        HIDWORD(igi2_frame.tPos.vX) = 0;
      v64 = v1[3].ptParent;
      LOWORD(igi2_frame.tPos.vY) = v1[3].tQTaskRefList.ptTail;
      v65 = GameFunctions_ptExplosionQTaskList;
      igi2_frame.v84 = v64;
      if ( GameFunctions_ptExplosionQTaskList->nTask > 0 )
      {
        v66 = 8;
        do
        {
          ((void (__cdecl *)(_DWORD, struct real64x3_t *))QTask_aatQTaskFinalEvent[GameFunctions_eExplosionHitQTaskEvent][*(unsigned __int16 *)(*(int *)((char *)&v65->nTask + v66) + 36)].pfHandler)(
            *(int *)((char *)&v65->nTask + v66),
            &igi2_frame.tPos);
          v65 = GameFunctions_ptExplosionQTaskList;
          ++v63;
          v66 += 4;
        }
        while ( v63 < GameFunctions_ptExplosionQTaskList->nTask );
      }
    }
  }
}

// source: j/0/explosions/explosion0.c:983  [size]
void __cdecl Explosion0_SmokeCreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: j/0/explosions/explosion0.c:995  [anchor-mhash]
void __cdecl Explosion0_SmokeRunHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v14; };
    struct { char igi2_o1[8]; float vSizeDelta; };
    struct { char igi2_o2[12]; struct real32x2_t tSize; };
    char igi2_extent[20];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptNext; // eax
  int vX_low; // ebx
  struct RandomState_s *p_tRunRandomState; // edi
  double ptPrev; // st7
  int v6; // ebp
  struct QTask_s *v7; // eax
  double v8; // st7
  struct QTask_s *v9; // ecx
  double v10; // st7
  double v11; // st6
  double v12; // st6
  double v13; // st7
  struct QTask_s *ptQTaska = *(struct QTask_s * *)&ptQTask; // [esp+18h] [ebp+4h] ARGSLOT
  float ptQTaskc = *(float *)&ptQTask; // [esp+18h] [ebp+4h] ARGSLOT
  float ptQTaskd = *(float *)&ptQTask; // [esp+18h] [ebp+4h] ARGSLOT
  float ptQTaskb = *(float *)&ptQTask; // [esp+18h] [ebp+4h] ARGSLOT

  ptNext = ptQTask[1].ptNext;
  if ( (int)ptNext > 0 )
  {
    ptQTaska = ptQTask[1].ptPrev;
    if ( ptNext == ptQTaska )
    {
      igi2_frame.tSize = (*(struct real32x2_t *)&(__int64){(__int64)((double)(int)ptQTaska * 0.10000000149011612)});
      vX_low = LODWORD(igi2_frame.tSize.vX);
      p_tRunRandomState = &Game_ptGame->tRunRandomState;
      ptPrev = (double)(int)ptQTask[1].ptPrev;
      igi2_frame.tSize = (*(struct real32x2_t *)&(__int64){(__int64)((Random_GetRandomNumberReal32(&Game_ptGame->tRunRandomState) * 0.20000000298023224
                                          + 0.800000011920929)
                                         * ptPrev)});
      v6 = LODWORD(igi2_frame.tSize.vX);
      LODWORD(igi2_frame.tSize.vX) = ptQTask[1].ptParent;
      igi2_frame.tSize.vY = igi2_frame.tSize.vX;
      igi2_frame.vSizeDelta = 1.0 / ptPrev;
      ptQTaskc = (Random_GetRandomNumberReal32(p_tRunRandomState) + 1.0) * 0.10000000149011612;
      Explosion0_AddSmoke(
        (struct Explosion0Smoke_s *)ptQTask,
        (int)&MTP_atLODVirModel[45].atBoneVertexRefs[20].atVertexRefs[783],
        &igi2_frame.tSize,
        igi2_frame.vSizeDelta,
        vX_low,
        v6,
        ptQTaskc);
    }
    v7 = ptQTask[1].ptPrev;
    v8 = (double)(int)v7;
    igi2_frame.tSize = (*(struct real32x2_t *)&(__int64){(__int64)(0.8999999761581421 * v8)});
    if ( ptQTask[1].ptNext == (struct QTask_s *)LODWORD(igi2_frame.tSize.vX) )
    {
      LODWORD(igi2_frame.tSize.vX) = ptQTask[1].ptParent;
      igi2_frame.tSize.vY = igi2_frame.tSize.vX;
      ptQTaskd = 1.0 / v8;
      *(_DWORD *)&ptQTask[1].eQTaskType = Explosion0_AddSmoke(
                                            (struct Explosion0Smoke_s *)ptQTask,
                                            (int)&MTP_atLODVirModel[45].atBoneVertexRefs[20].atVertexRefs[785],
                                            &igi2_frame.tSize,
                                            ptQTaskd,
                                            (int)v7,
                                            0,
                                            0.0010000000474974513);
    }
    v9 = *(struct QTask_s **)&ptQTask[1].eQTaskType;
    if ( v9 )
    {
      v10 = (double)(int)ptQTask[1].ptNext;
      v11 = (double)(int)ptQTask[1].ptPrev;
      ptQTaskb = v11;
      v12 = v11 * 0.5;
      if ( v10 <= v12 )
        v13 = v10 / v12;
      else
        v13 = 1.0 - (v10 - v12) / (ptQTaskb * 0.8999999761581421 - v12);
      igi2_frame.v14 = v13 * 0.30000001192092896;
      Particle2DDynCubeObj_SetIntensity(v9, igi2_frame.v14);
    }
    --*(int *)&ptQTask[1].ptNext;
  }
  else
  {
    QTask_Delete(ptQTask);
  }
}

// source: j/0/explosions/explosion0.c:1112  [size]
void __cdecl Explosion0_SmokeDeleteHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: j/0/explosions/explosion0.c:1124  [anchor-mhash]
void __cdecl Explosion0_FragmentRunHandler(struct QTask_s *ptQTask)
{
  if ( ptQTask[8].tQTaskRefList.ptHead )
    Explosion0_FragmentAddTail((struct Fragment_t *)ptQTask);
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][SimpointObj_eQTaskType].pfHandler)(ptQTask);
}

// source: j/0/explosions/explosion0.c:1152  [anchor-mhash]
void __cdecl Explosion0_FireBallCreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct World_s *ptDynCubeObj; };
    struct { float ptDynCubeObja; };
    struct { char igi2_o2[16]; struct real64x3_t tNull; };
    char igi2_extent[40];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v2; // st7
  double v3; // st7
  int *v4; // eax
  int v5; // eax
  double v6; // st6

  igi2_frame.ptDynCubeObj = Game_ptGame->ptWorld;
  memset(&igi2_frame.tNull, 0, sizeof(igi2_frame.tNull));
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
    &igi2_frame.tNull,
    igi2_frame.ptDynCubeObja,
    WORLD_DYNCUBETREE_CATEGORY_MOBILE);
  ptQTask[8].ptParent = nullptr;
  ptQTask[8].ptNext = (struct QTask_s *)-1;
}

// source: j/0/explosions/explosion0.c:1185  [anchor-mhash]
void __cdecl Explosion0_FireBallRunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptMiddle; // eax
  int v2; // eax
  struct QTask_s *ptPrev; // eax

  ptMiddle = ptQTask[8].tQTaskChildren.ptMiddle;
  if ( (int)ptMiddle <= 0 )
  {
    v2 = *(_DWORD *)(**(_DWORD **)&ptQTask[2].eQTaskType + 12);
    if ( *(_DWORD *)(v2 + 16) )
      ptQTask[8].ptNext = (struct QTask_s *)((int)(__int64)((double)((char *)ptQTask[8].tQTaskChildren.ptHead
                                                                   - (char *)ptQTask[8].ptPrev)
                                                          / (double)(int)ptQTask[8].tQTaskRefList.ptMiddle
                                                          * (double)**(int **)(v2 + 20))
                                           % (int)(**(_DWORD **)(v2 + 20)));
    else
      ptQTask[8].ptNext = (struct QTask_s *)-1;
    ptPrev = ptQTask[8].ptPrev;
    if ( ptPrev )
      ptQTask[8].ptPrev = (struct QTask_s *)((char *)ptPrev - 1);
    else
      QTask_Delete(ptQTask);
  }
  else
  {
    ptQTask[8].tQTaskChildren.ptMiddle = (struct QTask_s *)((char *)ptMiddle - 1);
  }
}

// source: j/0/explosions/explosion0.c:1238  [anchor-caller]
void __cdecl Explosion0_FireBallEnterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s *tScalea; };
    struct { float tScaleb; };
    struct { float tScalec; };
    struct { char igi2_o3[4]; float tScale_4a; };
    struct { char igi2_o4[4]; float tScale_4b; };
    struct { char igi2_o5[8]; float tScale_8a; };
    struct { char igi2_o6[8]; float tScale_8b; };
    struct { char igi2_o7[8]; float tScale_8c; };
    struct { char igi2_o8[12]; struct real32x9_t tRot; };
    struct { char igi2_o9[52]; struct real32x3_t tTemp_; };
    struct { char igi2_o10[64]; struct MagicObjEnterContext_s tMagicObjEnterContext; };
    char igi2_extent[136];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  float *p_ptPrev; // ebx
  double v3; // st7
  double v4; // st7
  long double v5; // st5
  double v6; // st7
  double v7; // st7
  double v8; // st7
  double v9; // st7
  double v10; // st7
  double v11; // st7
  struct QTask_s *ptHead; // ecx
  long double v13; // st4
  double v14; // st7
  double v15; // st7
  long double v16; // st4
  long double v17; // st4
  struct QTask_s *ptParent; // ecx
  struct QReference_s *ptTail; // ecx
  double vX; // st7
  struct QTask_s *v21; // eax
  struct QTask_s *v22; // ecx
  struct QReference_s *v23; // eax
  struct QTask_s *ptMiddle; // edx
  float v25; // ecx
  struct QReference_s *v26; // eax
  struct QTask_s *ptNext; // edx
  double v28; // st7
  double v29; // st6
  int v30; // eax
  int v31; // edx
  int *v32; // edi
  int v33; // edx
  int v34; // ecx
  int v35; // eax
  int v36; // edx
  int v37; // edx
  struct QTask_s *v38; // eax
  struct QTask_s *v39; // ebp
  int v40; // ecx
  int v41; // edx
  struct QTask_s *v42; // eax
  int v43; // esi
  void (__cdecl *pfHandler)(int, struct MagicObjEnterContext_s *); // eax
  int v45; // edx
  struct real32x3_t tScale; // 0:^18.12

  p_ptPrev = (float *)&ptQTask[3].ptPrev;
  if ( (int)ptQTask[8].tQTaskChildren.ptMiddle <= 0 )
  {
    igi2_frame.tScalea = (struct QTask_s *)ptQTask[8].tQTaskRefList.ptTail;
    v3 = (double)(int)ptQTask[8].ptPrev / (double)(int)ptQTask[8].tQTaskChildren.ptHead;
    ptQTask[6].ptPrev = igi2_frame.tScalea;
    ptQTask[6].tQTaskChildren.ptHead = igi2_frame.tScalea;
    igi2_frame.tScale_8a = (1.0 - v3) * *(float *)&ptQTask[8].tQTaskRefList.ptTail + 0.009999999776482582;
    *(float *)&ptQTask[6].tQTaskChildren.ptMiddle = igi2_frame.tScale_8a;
    *(float *)&ptQTask[3].tQTaskRefList.ptTail = TransContext_tActiveTransContext.tPos.vX
                                               - *(double *)&ptQTask[1].ptNext;
    *(float *)&ptQTask[3].ptParent = TransContext_tActiveTransContext.tPos.vY
                                   - *(double *)&ptQTask[1].tQTaskChildren.ptHead;
    v4 = TransContext_tActiveTransContext.tPos.vZ - *(double *)&ptQTask[1].tQTaskChildren.ptTail;
    *(float *)&ptQTask[3].eQTaskType = v4;
    if ( *(float *)&ptQTask[3].tQTaskRefList.ptTail == 0.0 && *(float *)&ptQTask[3].ptParent == 0.0 && v4 == 0.0 )
    {
      ptQTask[3].tQTaskRefList.ptTail = (struct QReference_s *)1065353216;
    }
    else if ( *(float *)&ptQTask[3].tQTaskRefList.ptTail != 0.0 || *(float *)&ptQTask[3].ptParent != 0.0 || v4 != 0.0 )
    {
      v5 = sqrt(
             v4 * v4
           + *(float *)&ptQTask[3].tQTaskRefList.ptTail * *(float *)&ptQTask[3].tQTaskRefList.ptTail
           + *(float *)&ptQTask[3].ptParent * *(float *)&ptQTask[3].ptParent);
      *(float *)&ptQTask[3].tQTaskRefList.ptTail = *(float *)&ptQTask[3].tQTaskRefList.ptTail * (1.0 / v5);
      *(float *)&ptQTask[3].ptParent = *(float *)&ptQTask[3].ptParent * (1.0 / v5);
      *(float *)&ptQTask[3].eQTaskType = *(float *)&ptQTask[3].eQTaskType * (1.0 / v5);
    }
    if ( 0.0 == *(float *)&ptQTask[3].tQTaskRefList.ptTail
      && 0.0 == *(float *)&ptQTask[3].ptParent
      && *(_DWORD *)&ptQTask[3].eQTaskType == 1065353216 )
    {
      *p_ptPrev = 1.0;
      ptQTask[3].tQTaskChildren.ptHead = nullptr;
      ptQTask[3].tQTaskChildren.ptMiddle = nullptr;
      ptQTask[3].tQTaskChildren.ptTail = nullptr;
      ptQTask[3].tQTaskRefList.ptHead = (struct QReference_s *)1065353216;
      ptQTask[3].tQTaskRefList.ptMiddle = nullptr;
    }
    else
    {
      v6 = *(float *)&ptQTask[3].eQTaskType * 0.0;
      igi2_frame.tScaleb = v6 - *(float *)&ptQTask[3].ptParent;
      v7 = v6 - *(float *)&ptQTask[3].tQTaskRefList.ptTail;
      *p_ptPrev = igi2_frame.tScaleb;
      igi2_frame.tScale_4a = -v7;
      v8 = *(float *)&ptQTask[3].ptParent;
      *(float *)&ptQTask[3].tQTaskChildren.ptHead = igi2_frame.tScale_4a;
      igi2_frame.tScale_8b = v8 * 0.0 - *(float *)&ptQTask[3].tQTaskRefList.ptTail * 0.0;
      v9 = *(float *)&ptQTask[3].ptParent;
      *(float *)&ptQTask[3].tQTaskChildren.ptMiddle = igi2_frame.tScale_8b;
      igi2_frame.tScalec = v9 * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle
              - *(float *)&ptQTask[3].eQTaskType * *(float *)&ptQTask[3].tQTaskChildren.ptHead;
      v10 = *(float *)&ptQTask[3].tQTaskRefList.ptTail * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle;
      *(float *)&ptQTask[3].tQTaskChildren.ptTail = igi2_frame.tScalec;
      igi2_frame.tScale_4b = -(v10 - *(float *)&ptQTask[3].eQTaskType * *(float *)&ptQTask[3].ptPrev);
      v11 = *(float *)&ptQTask[3].tQTaskRefList.ptTail;
      *(float *)&ptQTask[3].tQTaskRefList.ptHead = igi2_frame.tScale_4b;
      igi2_frame.tScale_8c = v11 * *(float *)&ptQTask[3].tQTaskChildren.ptHead
                - *(float *)&ptQTask[3].ptParent * *(float *)&ptQTask[3].ptPrev;
      *(float *)&ptQTask[3].tQTaskRefList.ptMiddle = igi2_frame.tScale_8c;
    }
    igi2_frame.tRot.tX.vX = *p_ptPrev;
    ptHead = ptQTask[3].tQTaskChildren.ptHead;
    LODWORD(igi2_frame.tRot.tX.vZ) = ptQTask[3].tQTaskChildren.ptMiddle;
    LODWORD(igi2_frame.tRot.tX.vY) = ptHead;
    if ( igi2_frame.tRot.tX.vX != 0.0 || igi2_frame.tRot.tX.vY != 0.0 || igi2_frame.tRot.tX.vZ != 0.0 )
    {
      v13 = sqrt(igi2_frame.tRot.tX.vX * igi2_frame.tRot.tX.vX + igi2_frame.tRot.tX.vY * igi2_frame.tRot.tX.vY + igi2_frame.tRot.tX.vZ * igi2_frame.tRot.tX.vZ);
      igi2_frame.tRot.tX.vX = igi2_frame.tRot.tX.vX * (1.0 / v13);
      igi2_frame.tRot.tX.vY = igi2_frame.tRot.tX.vY * (1.0 / v13);
      igi2_frame.tRot.tX.vZ = igi2_frame.tRot.tX.vZ * (1.0 / v13);
    }
    igi2_frame.tTemp_.vX = *(float *)&ptQTask[3].ptParent * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle
              - *(float *)&ptQTask[3].eQTaskType * *(float *)&ptQTask[3].tQTaskChildren.ptHead;
    v14 = *(float *)&ptQTask[3].tQTaskRefList.ptTail * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle;
    igi2_frame.tRot.tY.vX = igi2_frame.tTemp_.vX;
    igi2_frame.tTemp_.vY = -(v14 - *(float *)&ptQTask[3].eQTaskType * *(float *)&ptQTask[3].ptPrev);
    v15 = *(float *)&ptQTask[3].tQTaskRefList.ptTail;
    igi2_frame.tRot.tY.vY = igi2_frame.tTemp_.vY;
    igi2_frame.tTemp_.vZ = v15 * *(float *)&ptQTask[3].tQTaskChildren.ptHead
              - *(float *)&ptQTask[3].ptParent * *(float *)&ptQTask[3].ptPrev;
    igi2_frame.tRot.tY.vZ = igi2_frame.tTemp_.vZ;
    tScale.vX = igi2_frame.tTemp_.vZ * igi2_frame.tRot.tX.vY - igi2_frame.tTemp_.vY * igi2_frame.tRot.tX.vZ;
    tScale.vY = -(igi2_frame.tTemp_.vZ * igi2_frame.tRot.tX.vX - igi2_frame.tTemp_.vX * igi2_frame.tRot.tX.vZ);
    tScale.vZ = igi2_frame.tTemp_.vY * igi2_frame.tRot.tX.vX - igi2_frame.tTemp_.vX * igi2_frame.tRot.tX.vY;
    igi2_frame.tRot.tZ = tScale;
    if ( igi2_frame.tTemp_.vX != 0.0 || igi2_frame.tTemp_.vY != 0.0 || igi2_frame.tTemp_.vZ != 0.0 )
    {
      v16 = sqrt(igi2_frame.tTemp_.vZ * igi2_frame.tTemp_.vZ + igi2_frame.tTemp_.vY * igi2_frame.tTemp_.vY + igi2_frame.tTemp_.vX * igi2_frame.tTemp_.vX);
      igi2_frame.tRot.tY.vX = igi2_frame.tTemp_.vX * (1.0 / v16);
      igi2_frame.tRot.tY.vY = igi2_frame.tRot.tY.vY * (1.0 / v16);
      igi2_frame.tRot.tY.vZ = igi2_frame.tRot.tY.vZ * (1.0 / v16);
    }
    if ( tScale.vX != 0.0 || tScale.vY != 0.0 || tScale.vZ != 0.0 )
    {
      v17 = sqrt(tScale.vX * tScale.vX + tScale.vY * tScale.vY + tScale.vZ * tScale.vZ);
      igi2_frame.tRot.tZ.vX = tScale.vX * (1.0 / v17);
      igi2_frame.tRot.tZ.vY = igi2_frame.tRot.tZ.vY * (1.0 / v17);
      igi2_frame.tRot.tZ.vZ = igi2_frame.tRot.tZ.vZ * (1.0 / v17);
    }
    qmemcpy(p_ptPrev, &igi2_frame.tRot, 0x28u);
    ptQTask[4].ptNext = nullptr;
    ptParent = ptQTask[8].ptParent;
    igi2_frame.tRot.nOps = 0;
    igi2_frame.tRot.tX.vX = 1.0;
    memset(&igi2_frame.tRot.tX.vY, 0, 12);
    igi2_frame.tRot.tY.vY = 1.0;
    memset(&igi2_frame.tRot.tY.vZ, 0, 12);
    igi2_frame.tRot.tZ.vZ = 1.0;
    Real32x9_RotateGamma(&igi2_frame.tRot, &igi2_frame.tRot, *(float *)&ptParent);
    *(float *)&ptQTask[8].ptParent = *(float *)&ptQTask[8].eQTaskType + *(float *)&ptQTask[8].ptParent;
    ptTail = ptQTask[3].tQTaskRefList.ptTail;
    vX = igi2_frame.tRot.tX.vX;
    v21 = ptQTask[3].tQTaskChildren.ptTail;
    *(float *)&igi2_frame.tMagicObjEnterContext.tParentPos.vX = *p_ptPrev;
    *(_QWORD *)&igi2_frame.tMagicObjEnterContext.tParentPos.vY = __PAIR64__(ptQTask[3].tQTaskChildren.ptHead, (unsigned int)ptTail);
    v22 = ptQTask[3].ptParent;
    HIDWORD(igi2_frame.tMagicObjEnterContext.tParentPos.vX) = v21;
    v23 = ptQTask[3].tQTaskRefList.ptHead;
    ptMiddle = ptQTask[3].tQTaskChildren.ptMiddle;
    HIDWORD(igi2_frame.tMagicObjEnterContext.tParentPos.vZ) = v22;
    v25 = *(float *)&ptQTask[3].eQTaskType;
    LODWORD(igi2_frame.tMagicObjEnterContext.tParentPos.vZ) = v23;
    v26 = ptQTask[3].tQTaskRefList.ptMiddle;
    LODWORD(igi2_frame.tMagicObjEnterContext.tParentOrientation.tX.vX) = ptMiddle;
    ptNext = ptQTask[4].ptNext;
    igi2_frame.tMagicObjEnterContext.tParentOrientation.tX.vZ = v25;
    LODWORD(igi2_frame.tMagicObjEnterContext.tParentOrientation.tX.vY) = v26;
    LODWORD(igi2_frame.tMagicObjEnterContext.tParentOrientation.tY.vX) = ptNext;
    qmemcpy(p_ptPrev, &igi2_frame.tMagicObjEnterContext, 0x28u);
    *(float *)&igi2_frame.tMagicObjEnterContext.tParentPos.vX = vX * *(float *)&ptQTask[3].ptPrev
                                                   + igi2_frame.tRot.tY.vX * *(float *)&ptQTask[3].tQTaskChildren.ptHead
                                                   + igi2_frame.tRot.tZ.vX * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle;
    *((float *)&igi2_frame.tMagicObjEnterContext.tParentPos.vX + 1) = igi2_frame.tRot.tX.vY * *(float *)&ptQTask[3].ptPrev
                                                         + igi2_frame.tRot.tY.vY * *(float *)&ptQTask[3].tQTaskChildren.ptHead
                                                         + igi2_frame.tRot.tZ.vY * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle;
    *(float *)&igi2_frame.tMagicObjEnterContext.tParentPos.vY = igi2_frame.tRot.tX.vZ * *(float *)&ptQTask[3].ptPrev
                                                   + igi2_frame.tRot.tY.vZ * *(float *)&ptQTask[3].tQTaskChildren.ptHead
                                                   + igi2_frame.tRot.tZ.vZ * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle;
    v28 = igi2_frame.tRot.tZ.vX * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle;
    v29 = igi2_frame.tRot.tX.vX * *(float *)&ptQTask[3].tQTaskChildren.ptTail;
    v30 = Lightsource_nLightDataStackPos;
    LODWORD(igi2_frame.tMagicObjEnterContext.tParentOrientation.tY.vX) = (char *)&ptQTask[4].ptNext->ptNext + igi2_frame.tRot.nOps + 1;
    v31 = Lightsource_nLightDataBufferPos;
    *((float *)&igi2_frame.tMagicObjEnterContext.tParentPos.vY + 1) = v28
                                                         + v29
                                                         + igi2_frame.tRot.tY.vX * *(float *)&ptQTask[3].tQTaskRefList.ptHead;
    *(float *)&igi2_frame.tMagicObjEnterContext.tParentPos.vZ = igi2_frame.tRot.tZ.vY * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle
                                                   + igi2_frame.tRot.tX.vY * *(float *)&ptQTask[3].tQTaskChildren.ptTail
                                                   + igi2_frame.tRot.tY.vY * *(float *)&ptQTask[3].tQTaskRefList.ptHead;
    *((float *)&igi2_frame.tMagicObjEnterContext.tParentPos.vZ + 1) = igi2_frame.tRot.tZ.vZ * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle
                                                         + igi2_frame.tRot.tX.vZ * *(float *)&ptQTask[3].tQTaskChildren.ptTail
                                                         + igi2_frame.tRot.tY.vZ * *(float *)&ptQTask[3].tQTaskRefList.ptHead;
    igi2_frame.tMagicObjEnterContext.tParentOrientation.tX.vX = igi2_frame.tRot.tZ.vX * *(float *)&ptQTask[3].eQTaskType
                                                   + igi2_frame.tRot.tY.vX * *(float *)&ptQTask[3].ptParent
                                                   + igi2_frame.tRot.tX.vX * *(float *)&ptQTask[3].tQTaskRefList.ptTail;
    igi2_frame.tMagicObjEnterContext.tParentOrientation.tX.vY = igi2_frame.tRot.tZ.vY * *(float *)&ptQTask[3].eQTaskType
                                                   + igi2_frame.tRot.tY.vY * *(float *)&ptQTask[3].ptParent
                                                   + igi2_frame.tRot.tX.vY * *(float *)&ptQTask[3].tQTaskRefList.ptTail;
    igi2_frame.tMagicObjEnterContext.tParentOrientation.tX.vZ = igi2_frame.tRot.tZ.vZ * *(float *)&ptQTask[3].eQTaskType
                                                   + igi2_frame.tRot.tY.vZ * *(float *)&ptQTask[3].ptParent
                                                   + igi2_frame.tRot.tX.vZ * *(float *)&ptQTask[3].tQTaskRefList.ptTail;
    qmemcpy(p_ptPrev, &igi2_frame.tMagicObjEnterContext, 0x28u);
    v32 = (int *)(4 * v31 + 140666816);
    v33 = v30 + v31;
    v34 = v30;
    v35 = Hazinglayers_iHazingStack;
    qmemcpy(v32, Lightsource_anLightDataStack, 4 * v34);
    Lightsource_nLightDataBufferPos = v33;
    v36 = Hazinglayers_iHazingBuffer;
    qmemcpy((void *)(4 * Hazinglayers_iHazingBuffer + 129834072), Hazinglayers_aptHazingStack, 4 * v35);
    v37 = v35 + v36;
    v38 = ptQTask[8].ptNext;
    Hazinglayers_iHazingBuffer = v37;
    if ( (int)v38 >= 0 )
    {
      *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(**(_DWORD **)&ptQTask[2].eQTaskType + 12) + 20) + 4) = v38;
      ((void (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[5][RigidDynCubeObj_eQTaskType].pfHandler)(
        ptQTask,
        0);
    }
    v39 = ptQTask->tQTaskChildren.ptHead;
    qmemcpy(&igi2_frame.tMagicObjEnterContext, &ptQTask[1], 0x18u);
    qmemcpy(&igi2_frame.tMagicObjEnterContext.tParentOrientation, p_ptPrev, sizeof(igi2_frame.tMagicObjEnterContext.tParentOrientation));
    if ( v39->ptNext )
    {
      v40 = (int)v39;
      if ( v39 )
      {
        v41 = QTask_nProtectedQTaskStackOffset;
        do
        {
          if ( *(_DWORD *)v40 )
            v42 = **(_DWORD **)v40 != 0 ? *(struct QTask_s **)v40 : nullptr;
          else
            v42 = nullptr;
          v43 = MagicObj_eMagicObjEnterEvent;
          QTask_atProtectedQTaskStack[v41].ptQTask = v42;
          pfHandler = (void (__cdecl *)(int, struct MagicObjEnterContext_s *))QTask_aatQTaskFinalEvent[v43][*(unsigned __int16 *)(v40 + 36)].pfHandler;
          v45 = v41 + 1;
          QTask_nProtectedQTaskStackOffset = v45;
          if ( pfHandler )
          {
            pfHandler(v40, &igi2_frame.tMagicObjEnterContext);
            v45 = QTask_nProtectedQTaskStackOffset;
          }
          v40 = dword_849C7DC[v45];
          v41 = v45 - 1;
          QTask_nProtectedQTaskStackOffset = v41;
        }
        while ( v40 );
      }
    }
  }
}

// source: j/0/explosions/explosion0.c:1373  [anchor-mhash]
void __cdecl Explosion0_FireBallDeleteHandler(struct QTask_s *ptQTask)
{
  Mesh3D_FreeAnimTexIndexPointers((unsigned int **)&ptQTask[6].tQTaskChildren.ptTail);
  World_RemoveDynCubeObj(Game_ptGame->ptWorld, (struct DynCubeObj_s *)ptQTask);
}

// source: j/0/explosions/explosion0.c:1396  [size]
void __cdecl Explosion0_FireBallWeaponCollisionEvaluateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_BYTE *)pxContext = 0;
}

// source: j/0/explosions/explosion0.c:1416  [size]
void __cdecl Explosion0_FireBallObjectCollisionEvaluateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_BYTE *)pxContext = 0;
}

// source: j/0/explosions/explosion0.c:1436  [size]
void __cdecl Explosion0_FireBallGetNextZEvaluateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_BYTE *)pxContext = 0;
}

// source: j/0/explosions/explosion0.c:1456  [size]
void __cdecl Explosion0_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[1].ptParent = nullptr;
  ptQTask[3].tQTaskRefList.ptHead = nullptr;
  ptQTask[3].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[3].ptParent = nullptr;
}

// source: j/0/explosions/explosion0.c:1476  [anchor-caller]
void __cdecl Explosion0_RunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptParent; // eax
  struct QReference_s *v2; // eax
  struct Game_s *v3; // eax
  struct QReference_s *ptTail; // ecx
  unsigned int v5; // edi
  int v6; // edi
  unsigned int v7; // edi

  ptParent = ptQTask[1].ptParent;
  if ( ptParent )
    ptQTask[1].ptParent = (struct QTask_s *)((char *)ptParent - 1);
  if ( !ptQTask[1].ptParent && ptQTask[1].tQTaskRefList.ptMiddle )
  {
    Explosion0_CreateExplosion(ptQTask);
    v2 = (struct QReference_s *)((char *)ptQTask[1].tQTaskRefList.ptMiddle - 1);
    ptQTask[1].tQTaskRefList.ptMiddle = v2;
    if ( v2 )
    {
      v3 = Game_ptGame;
      ptTail = ptQTask[1].tQTaskRefList.ptTail;
      v5 = (Game_ptGame->tRunRandomState.anRandom[0] >> 7) ^ Game_ptGame->tRunRandomState.anRandom[2];
      Game_ptGame->tRunRandomState.anRandom[2] = v5;
      v6 = v5 ^ v3->tRunRandomState.anRandom[1];
      v3->tRunRandomState.anRandom[1] = v6;
      v7 = v6 + v3->tRunRandomState.anRandom[0];
      v3->tRunRandomState.anRandom[0] = v7;
      ptQTask[1].ptParent = (struct QTask_s *)(v7 % (unsigned int)ptTail);
    }
    else
    {
      QTask_Delete(ptQTask);
    }
  }
}

// source: j/0/explosions/explosion0.c:1522  [size]
void __cdecl Explosion0_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QReference_s *ptMiddle; // eax

  ptMiddle = ptQTask[3].tQTaskRefList.ptMiddle;
  if ( ptMiddle )
    QReference_Delete(ptMiddle, &QTask_tQTaskRefPool);
}

// source: j/0/explosions/explosion0.c:1541  [size]
void __cdecl Explosion0_FireBallCollisionEvalHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_BYTE *)pxContext = 0;
}

// source: j/0/explosions/explosion0.c:1557  [size]
void __cdecl Explosion0_FragmentCollisionEvalHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_BYTE *)pxContext = 0;
}

// source: j/0/explosions/explosion0.c:1573  [size]
void __cdecl Explosion0_FireBallAILineOfSightHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_BYTE *)pxContext = 0;
}

// source: j/0/explosions/explosion0.c:1592  [anchor-strings]
void __cdecl Explosion0_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si
  unsigned __int16 v2; // si
  unsigned __int16 v3; // si
  unsigned __int16 v4; // ax
  unsigned __int16 v5; // si

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("Explosion0", 160, BaseQTaskType, 32, 0);
  Explosion0_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 0, (void (__cdecl *)(struct QTask_s *, void *))Explosion0_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, Explosion0_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, Explosion0_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v1, Serialize_eDeSerializeDoneQTaskEvent, Explosion0_DeSerializeDoneHandler);
  v2 = QTask_NewQTaskType("FireBall", 360, RigidDynCubeObj_eQTaskType, 96, 0);
  Explosion0_eFireBallQTaskType = v2;
  QTask_LinkQTaskEventHandlerFn(v2, 0, Explosion0_FireBallCreateHandler);
  QTask_LinkQTaskEventHandlerFn(v2, 5, Explosion0_FireBallEnterHandler);
  QTask_LinkQTaskEventHandlerFn(
    v2,
    GameFunctions_eWeaponCollisionEvaluateQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Explosion0_FireBallWeaponCollisionEvaluateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v2,
    GameFunctions_eObjectCollisionEvaluateQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Explosion0_FireBallObjectCollisionEvaluateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v2,
    GameFunctions_eGetNextZEvaluateQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Explosion0_FireBallGetNextZEvaluateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v2,
    13,
    (void (__cdecl *)(struct QTask_s *, void *))Explosion0_FireBallCollisionEvalHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, 1, Explosion0_FireBallRunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, 2, Explosion0_FireBallDeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v2,
    AIDetection_eLineOfSightQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Explosion0_FireBallAILineOfSightHandler);
  QTask_LinkQTaskEventHandlerFn(v2, Serialize_eDeSerializeDoneQTaskEvent, Explosion0_DeSerializeDoneHandler);
  v3 = QTask_NewQTaskType("Fragment", 360, SimpointObj_eQTaskType, 160, 0);
  Explosion0_eFragmentQTaskType = v3;
  QTask_LinkQTaskEventHandlerNoContextFn(v3, 1, Explosion0_FragmentRunHandler);
  QTask_LinkQTaskEventHandlerFn(
    v3,
    13,
    (void (__cdecl *)(struct QTask_s *, void *))Explosion0_FragmentCollisionEvalHandler);
  QTask_LinkQTaskEventHandlerFn(v3, GameFunctions_eWeaponCollisionEvaluateQTaskEvent, nullptr);
  QTask_LinkQTaskEventHandlerFn(v3, GameFunctions_eObjectCollisionEvaluateQTaskEvent, nullptr);
  QTask_LinkQTaskEventHandlerFn(v3, GameFunctions_eGetNextZEvaluateQTaskEvent, nullptr);
  QTask_LinkQTaskEventHandlerFn(v3, AIDetection_eLineOfSightQTaskEvent, nullptr);
  QTask_LinkQTaskEventHandlerFn(v3, Serialize_eDeSerializeDoneQTaskEvent, Explosion0_DeSerializeDoneHandler);
  v4 = QTask_GetBaseQTaskType();
  v5 = QTask_NewQTaskType("ExplosionSmoke", 80, v4, 64, 0);
  Explosion0_eSmokeQTaskType = v5;
  QTask_LinkQTaskEventHandlerFn(v5, 0, (void (__cdecl *)(struct QTask_s *, void *))Explosion0_SmokeCreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v5, 1, Explosion0_SmokeRunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v5, 2, (void (__cdecl *)(struct QTask_s *))Explosion0_SmokeDeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v5, Serialize_eDeSerializeDoneQTaskEvent, Explosion0_DeSerializeDoneHandler);
  Explosion0_ptBurnMark = GameFunctions_RegisterGameTexture("burn1.tex");
  Explosion0_ptSmoke = GameFunctions_RegisterGameSprite("smoke2.spr");
  Explosion0_ptFireball = GameFunctions_RegisterGameSprite("fireball.spr");
}

// source: j/0/explosions/explosion0.c:1657  [size]
void __cdecl Explosion0_Close()
{
  QTask_DeleteQTaskType(Explosion0_eSmokeQTaskType);
  QTask_DeleteQTaskType(Explosion0_eFragmentQTaskType);
  QTask_DeleteQTaskType(Explosion0_eFireBallQTaskType);
  QTask_DeleteQTaskType(Explosion0_eQTaskType);
}

// source: j/0/explosions/explosion0.c:1692  [anchor-callee]
struct QTask_s *__cdecl Explosion0_New(
        struct real64x3_t *ptPos,
        int nExplosion,
        int nExplosionTime,
        float vDamage,
        float vFullRange,
        float vFallOffRange,
        float vBurnRange,
        int nFragment,
        int nFireball,
        struct QIntersection_s *ptIntersection,
        char *pzModelName,
        char *pzSound,
        int eHumanAIEvent,
        unsigned int bHumanAIEventFlags,
        float vHumanAIEventRange,
        struct WeaponType_s *ptWeaponType,
        struct QTask_s *ptOwnerQTask,
        enum ExplosionDamageFalloffType_e eDamageFalloffType)
{
  struct Game_s *v18; // eax
  unsigned int v19; // ecx
  int v20; // ecx
  double v21; // st7
  int v22; // ecx
  int v23; // edx
  unsigned int v24; // edx
  double v25; // st7
  int v26; // edx
  int v27; // edx
  unsigned int v28; // edx
  struct real32x3_t tDirection; // [esp+8h] [ebp-Ch] BYREF

  v18 = Game_ptGame;
  v19 = (Game_ptGame->tRunRandomState.anRandom[0] >> 7) ^ Game_ptGame->tRunRandomState.anRandom[2];
  Game_ptGame->tRunRandomState.anRandom[2] = v19;
  v20 = v19 ^ v18->tRunRandomState.anRandom[1];
  v18->tRunRandomState.anRandom[1] = v20;
  v21 = (double)(unsigned __int16)(v20 + LOWORD(v18->tRunRandomState.anRandom[0]));
  v18->tRunRandomState.anRandom[0] += v20;
  v22 = (v18->tRunRandomState.anRandom[0] >> 7) ^ v18->tRunRandomState.anRandom[2];
  v23 = v22 ^ v18->tRunRandomState.anRandom[1];
  v18->tRunRandomState.anRandom[2] = v22;
  v18->tRunRandomState.anRandom[1] = v23;
  v24 = v23 + v18->tRunRandomState.anRandom[0];
  tDirection.vX = v21 * 0.0000152587890625 - 0.5;
  v25 = (double)(unsigned __int16)v24;
  v18->tRunRandomState.anRandom[0] = v24;
  v26 = (v18->tRunRandomState.anRandom[0] >> 7) ^ v18->tRunRandomState.anRandom[2];
  v18->tRunRandomState.anRandom[2] = v26;
  v27 = v26 ^ v18->tRunRandomState.anRandom[1];
  v18->tRunRandomState.anRandom[1] = v27;
  v28 = v27 + v18->tRunRandomState.anRandom[0];
  v18->tRunRandomState.anRandom[0] = v28;
  tDirection.vY = v25 * 0.0000152587890625 - 0.5;
  tDirection.vZ = (double)(unsigned __int16)v28 * 0.0000152587890625 - 0.30000001192092896;
  return Explosion0_NewEx(
           ptPos,
           nExplosion,
           nExplosionTime,
           vDamage,
           vFullRange,
           vFallOffRange,
           vBurnRange,
           nFragment,
           nFireball,
           ptIntersection,
           pzModelName,
           pzSound,
           eHumanAIEvent,
           bHumanAIEventFlags,
           vHumanAIEventRange,
           &tDirection,
           1.5707963705062866,
           272.0,
           1360.0,
           ptWeaponType,
           ptOwnerQTask,
           eDamageFalloffType);
}

// source: j/0/explosions/explosion0.c:1761  [anchor-callee]
struct QTask_s *__cdecl Explosion0_NewEx(
        struct real64x3_t *ptPos,
        int nExplosion,
        int nExplosionTime,
        float vDamage,
        float vFullRange,
        float vFallOffRange,
        float vBurnRange,
        int nFragment,
        int nFireball,
        struct QIntersection_s *ptIntersection,
        char *pzModelName,
        char *pzSound,
        int eHumanAIEvent,
        unsigned int bHumanAIEventFlags,
        float vHumanAIEventRange,
        struct real32x3_t *ptDirection,
        float vMaxAlpha,
        float vMinSpeed,
        float vMaxSpeed,
        struct WeaponType_s *ptWeaponType,
        struct QTask_s *ptOwnerQTask,
        enum ExplosionDamageFalloffType_e eDamageFalloffType)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real64x3_t tRotationVelocity; };
    struct { char igi2_o1[24]; struct HumanAIEventContext_t tEventContext; };
    char igi2_extent[92];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char *v22; // ebx
  struct QTask_s *v23; // esi
  struct QTask_s *v24; // eax
  struct QTask_s *v25; // ebp
  unsigned int vX_low; // ecx
  double v27; // st7
  unsigned int vX_high; // edx
  int v29; // edx
  char *v30; // eax
  int v31; // edx
  char v32; // cl
  struct real32x3_t *v33; // eax
  float *p_eQTaskType; // ecx
  long double v35; // st7
  float v36; // eax
  float v37; // ecx
  enum ExplosionDamageFalloffType_e v38; // eax
  struct QObj_s *ptHitObj; // eax
  int v40; // ecx
  struct Game_s *v41; // eax
  unsigned int v42; // esi
  unsigned int v43; // edx
  double v44; // st7
  int v45; // edx
  int v46; // edi
  unsigned int v47; // esi
  int v48; // ecx
  double v49; // st7
  int v50; // ecx
  unsigned int v51; // edx
  struct QTask_s *v52; // eax
  struct QReference_s *vY_low; // ecx
  float vDamagea = *(float *)&vDamage; // [esp+7Ch] [ebp+10h] ARGSLOT

  v22 = pzModelName;
  v23 = ptOwnerQTask;
  v24 = QTask_NewFn(Level_ptDynamicQTask, Explosion0_eQTaskType, nullptr);
  v25 = v24;
  if ( v23 )
  {
    v24[3].tQTaskRefList.ptMiddle = QTask_NewQTaskRef(v23);
    LOWORD(v25[3].tQTaskRefList.ptTail) = v23->eQTaskType;
  }
  else
  {
    LOWORD(v24[3].tQTaskRefList.ptTail) = 512;
  }
  vX_low = LODWORD(ptPos->vX);
  v27 = ptPos->vZ - 2048.0;
  vX_high = HIDWORD(ptPos->vX);
  LODWORD(igi2_frame.tRotationVelocity.vY) = LODWORD(ptPos->vY);
  igi2_frame.tRotationVelocity.vZ = v27;
  *(_QWORD *)&igi2_frame.tRotationVelocity.vX = __PAIR64__(vX_high, vX_low);
  HIDWORD(igi2_frame.tRotationVelocity.vY) = HIDWORD(ptPos->vY);
  if ( eHumanAIEvent == 20 && Water_IsUnderWater((float *)&pzModelName, &igi2_frame.tRotationVelocity, (int *)&ptOwnerQTask) )
  {
    Water_GunShotEffect(ptPos, ptIntersection, vDamage, nullptr, (int)ptOwnerQTask, true);
    v25[3].ptNext = (struct QTask_s *)1819310181;
    v25[3].ptPrev = (struct QTask_s *)1635213167;
    v29 = 0;
    v25[3].tQTaskChildren.ptHead = (struct QTask_s *)&unk_726574;
  }
  else
  {
    v30 = pzSound;
    v31 = (char *)&v25[3] - pzSound;
    do
    {
      v32 = *v30;
      v30[v31] = *v30;
      ++v30;
    }
    while ( v32 );
    v29 = nFireball;
  }
  qmemcpy(&v25[1], ptPos, 0x18u);
  v25[1].tQTaskRefList.ptTail = (struct QReference_s *)nExplosionTime;
  v25[1].ptParent = (struct QTask_s *)nExplosionTime;
  *(float *)&v25[2].tQTaskChildren.ptHead = vDamage;
  v25[1].tQTaskRefList.ptMiddle = (struct QReference_s *)nExplosion;
  *(float *)&v25[2].tQTaskChildren.ptTail = vFallOffRange;
  v33 = ptDirection;
  *(float *)&v25[2].tQTaskChildren.ptMiddle = vFullRange;
  p_eQTaskType = (float *)&v25[1].eQTaskType;
  *(struct real32x3_t *)&v25[1].eQTaskType = *v33;
  if ( *(float *)&v25[1].eQTaskType != 0.0 || *(float *)&v25[2].ptNext != 0.0 || *(float *)&v25[2].ptPrev != 0.0 )
  {
    v35 = 1.0
        / sqrt(
            *p_eQTaskType * *p_eQTaskType
          + *(float *)&v25[2].ptNext * *(float *)&v25[2].ptNext
          + *(float *)&v25[2].ptPrev * *(float *)&v25[2].ptPrev);
    *p_eQTaskType = *p_eQTaskType * v35;
    *(float *)&v25[2].ptNext = *(float *)&v25[2].ptNext * v35;
    *(float *)&v25[2].ptPrev = *(float *)&v25[2].ptPrev * v35;
  }
  v36 = vMinSpeed;
  *(float *)&v25[2].tQTaskRefList.ptHead = vMaxAlpha;
  v37 = vMaxSpeed;
  *(_DWORD *)&v25[2].eQTaskType = v29;
  *(float *)&v25[2].tQTaskRefList.ptMiddle = v36;
  v38 = eDamageFalloffType;
  *(float *)&v25[2].tQTaskRefList.ptTail = v37;
  v25[3].ptParent = (struct QTask_s *)v38;
  v25[2].ptParent = (struct QTask_s *)nFragment;
  if ( ptIntersection )
  {
    ptHitObj = ptIntersection->ptHitObj;
    if ( ptIntersection->ptHitObj )
    {
      v40 = BulletHole_eCreateBulletHoleTaskEvent;
      if ( QTask_aatQTaskFinalEvent[v40][ptHitObj->tQTask.eQTaskType].pfHandler )
      {
        *(_QWORD *)&igi2_frame.tRotationVelocity.vX = (unsigned int)ptIntersection;
        LODWORD(igi2_frame.tRotationVelocity.vY) = &Explosion0_ptBurnMark->tTexInfo;
        *((float *)&igi2_frame.tRotationVelocity.vY + 1) = vBurnRange;
        ((void (__cdecl *)(struct QObj_s *, struct real64x3_t *))QTask_aatQTaskFinalEvent[v40][ptHitObj->tQTask.eQTaskType].pfHandler)(
          ptHitObj,
          &igi2_frame.tRotationVelocity);
      }
    }
  }
  v41 = Game_ptGame;
  v42 = (Game_ptGame->tRunRandomState.anRandom[0] >> 7)
      ^ Game_ptGame->tRunRandomState.anRandom[2]
      ^ Game_ptGame->tRunRandomState.anRandom[1];
  v43 = v42 + Game_ptGame->tRunRandomState.anRandom[0];
  v44 = (double)(unsigned __int16)(((Game_ptGame->tRunRandomState.anRandom[0] >> 7)
                                  ^ LOWORD(Game_ptGame->tRunRandomState.anRandom[2])
                                  ^ LOWORD(Game_ptGame->tRunRandomState.anRandom[1]))
                                 + LOWORD(Game_ptGame->tRunRandomState.anRandom[0]));
  Game_ptGame->tRunRandomState.anRandom[2] ^= Game_ptGame->tRunRandomState.anRandom[0] >> 7;
  v41->tRunRandomState.anRandom[1] = v42;
  v41->tRunRandomState.anRandom[0] = v43;
  v45 = (v41->tRunRandomState.anRandom[0] >> 7) ^ v41->tRunRandomState.anRandom[2];
  v46 = v45 ^ v41->tRunRandomState.anRandom[1];
  v47 = v46 + v41->tRunRandomState.anRandom[0];
  v48 = (unsigned __int16)(((v41->tRunRandomState.anRandom[0] >> 7)
                          ^ LOWORD(v41->tRunRandomState.anRandom[2])
                          ^ LOWORD(v41->tRunRandomState.anRandom[1]))
                         + LOWORD(v41->tRunRandomState.anRandom[0]));
  *(float *)&igi2_frame.tRotationVelocity.vX = v44 * 0.0000152587890625 * 0.6283185482025146;
  v49 = (double)v48;
  v41->tRunRandomState.anRandom[2] = v45;
  v41->tRunRandomState.anRandom[1] = v46;
  v41->tRunRandomState.anRandom[0] = v47;
  v50 = (v41->tRunRandomState.anRandom[0] >> 7) ^ v41->tRunRandomState.anRandom[2] ^ v41->tRunRandomState.anRandom[1];
  v51 = v50 + v41->tRunRandomState.anRandom[0];
  v41->tRunRandomState.anRandom[2] ^= v41->tRunRandomState.anRandom[0] >> 7;
  v41->tRunRandomState.anRandom[1] = v50;
  v41->tRunRandomState.anRandom[0] = v51;
  *((float *)&igi2_frame.tRotationVelocity.vX + 1) = v49 * 0.0000152587890625 * 0.6283185482025146;
  *(float *)&igi2_frame.tRotationVelocity.vY = (double)(unsigned __int16)v51 * 0.0000152587890625 * 0.6283185482025146;
  vDamagea = *(float *)&v25[2].tQTaskChildren.ptMiddle * 0.0002197265566792339;
  v52 = QTask_NewFn(Level_ptDynamicQTask, SimpointObjContainer_eQTaskType, nullptr);
  v52[1].ptNext = (struct QTask_s *)15;
  strcpy((char *)&v52[1].ptPrev, v22);
  LOBYTE(v52[1].tQTaskRefList.ptHead) = 0;
  *(float *)&v52[2].tQTaskChildren.ptHead = vDamagea;
  *(double *)&v52[2].tQTaskChildren.ptMiddle = igi2_frame.tRotationVelocity.vX;
  vY_low = (struct QReference_s *)LODWORD(igi2_frame.tRotationVelocity.vY);
  *(_DWORD *)&v52[1].eQTaskType = 1065017672;
  v52[2].ptNext = (struct QTask_s *)1058642330;
  v52[2].ptPrev = (struct QTask_s *)1110599503;
  LOBYTE(v52[2].tQTaskRefList.ptMiddle) = 0;
  v52[2].tQTaskRefList.ptHead = vY_low;
  v25[3].tQTaskChildren.ptTail = v52;
  if ( eHumanAIEvent != -1 )
  {
    igi2_frame.tEventContext.eEvent = eHumanAIEvent;
    igi2_frame.tEventContext.eTeam = 1;
    igi2_frame.tEventContext.bFlags = bHumanAIEventFlags;
    igi2_frame.tEventContext.ptPosition = ptPos;
    igi2_frame.tEventContext.vRadius = vHumanAIEventRange;
    igi2_frame.tEventContext.ptHumanOriginatorQTask = nullptr;
    igi2_frame.tEventContext.ptReferenceQTask = v25;
    HumanAI_SendEvent(&igi2_frame.tEventContext);
  }
  v25[3].tQTaskRefList.ptHead = (struct QReference_s *)ptWeaponType;
  return v25;
}
