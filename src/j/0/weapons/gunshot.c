/* j/0/weapons/gunshot.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/weapons/gunshot.c:108  [anchor-mhash]
void __cdecl GunShot_RunInstant(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { enum bool isDoneTracing; };
    struct { char igi2_o1[4]; int nNumStoredEffectParams; };
    struct { char igi2_o2[8]; struct QIntersection_s *v56; };
    struct { char igi2_o3[12]; enum bool *p_isPenetration; };
    struct { char igi2_o4[16]; struct GunShotStoredEffectParameters_t *v58; };
    struct { char igi2_o5[20]; void **p_pxData; };
    struct { char igi2_o6[24]; float *p_vPenetrationPower; };
    struct { char igi2_o7[28]; float tVec; };
    struct { char igi2_o8[32]; float tVec_4; };
    struct { char igi2_o9[32]; float tVec_4a; };
    struct { char igi2_o10[36]; float tVec_8; };
    struct { char igi2_o11[36]; float tVec_8a; };
    struct { char igi2_o12[40]; float tDir; };
    struct { char igi2_o13[44]; float tDir_4; };
    struct { char igi2_o14[48]; float tDir_8; };
    struct { char igi2_o15[48]; float tDir_8a; };
    struct { char igi2_o16[52]; struct real32x3_t *p_tParticleDirection; };
    struct { char igi2_o17[56]; float *v71; };
    struct { char igi2_o18[60]; float vDistanceTravelled; };
    struct { char igi2_o19[64]; struct QTask_s **p_ptTail; };
    struct { char igi2_o20[68]; float tAfterHitDelta; };
    struct { char igi2_o21[72]; float tAfterHitDelta_4; };
    struct { char igi2_o22[76]; float tAfterHitDelta_8; };
    struct { char igi2_o23[76]; float tAfterHitDelta_8a; };
    struct { char igi2_o24[80]; struct real64x3_t tEnd; };
    struct { char igi2_o25[108]; int bTaskGroupsToCheck; };
    struct { char igi2_o26[112]; int iItem; };
    struct { char igi2_o27[116]; struct QTask_s *ptSoundQTask; };
    struct { char igi2_o28[120]; struct real64x3_t tStart; };
    struct { char igi2_o29[148]; struct QTask_s *ptWeaponQTask; };
    struct { char igi2_o30[152]; struct InstantItem_t *ptInstantItem; };
    struct { char igi2_o31[156]; float vInitialPenetration; };
    struct { char igi2_o32[160]; struct WeaponCollisionEvaluateContext_t tWeaponCollisionEvaluateContext; };
    struct { char igi2_o33[180]; struct GetWeaponObjectContext_t tGetWeaponObjectContext; };
    struct { char igi2_o34[192]; double v88; };
    struct { char igi2_o35[200]; struct WeaponHitContext_t tWeaponHitContext; };
    struct { char igi2_o36[232]; _DWORD v90[8]; };
    struct { char igi2_o37[264]; struct QIntersection_s tIntersection; };
    struct { char igi2_o38[384]; struct HumanAIEventContext_t tEventContext; };
    struct { char igi2_o39[448]; struct real64x3_t tTracerEnd; };
    struct { char igi2_o40[472]; struct real64x3_t tTracerStart; };
    struct { char igi2_o41[496]; struct GunShotStoredEffectParameters_t atEffectParam[50]; };
    char igi2_extent[8096];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v1; // edi
  char ptMiddle; // cl
  int v3; // ecx
  int v4; // eax
  struct QTask_s *ptNext; // esi
  int v6; // eax
  struct QTask_s *v7; // eax
  int v8; // eax
  struct QTask_s *v9; // esi
  bool v10; // cc
  struct InstantItem_t *v11; // ebx
  float *v12; // eax
  double v13; // st7
  double v14; // st7
  double v15; // st7
  double vPenetrationPower; // st7
  double v17; // st7
  double v18; // st6
  struct QObj_s *ptHitObj; // eax
  void (__cdecl *pfHandler)(struct QObj_s *, struct WeaponHitContext_t *); // ecx
  struct Game_s *v21; // eax
  unsigned int v22; // ebx
  unsigned int v23; // esi
  unsigned int v24; // ecx
  unsigned int v25; // ebx
  struct QTask_s *v26; // eax
  float v27; // edx
  float v28; // eax
  struct QTask_s *v29; // ecx
  struct QTask_s *ptTail; // eax
  struct QTask_s *v31; // eax
  struct QMaterial_t *ptEnterMaterial; // ecx
  double v33; // st7
  bool v34; // c3
  float vX; // edx
  long double v36; // st7
  double v37; // st7
  double v38; // st6
  double v39; // st5
  double v40; // st5
  struct QMaterial_t *ptLeaveMaterial; // ecx
  struct WeaponType_s *ptWeaponType; // eax
  struct QTask_s *ptHead; // eax
  struct QTask_s *ptParent; // eax
  int v45; // edi
  struct QIntersection_s *p_tIntersection; // esi
  unsigned __int16 vLight_low; // ax
  double v48; // st7
  int vY_low; // edx
  int v50; // edx
  struct WeaponType_s *v51; // edx
  struct QTask_s *v52; // eax
  int v53; // ecx

  v1 = ptQTask;
  ptMiddle = (char)ptQTask[4].tQTaskChildren.ptMiddle;
  igi2_frame.ptSoundQTask = nullptr;
  igi2_frame.bTaskGroupsToCheck = Forest_bQTaskGroup | 0x58000001;
  if ( (ptMiddle & 2) == 0 )
    igi2_frame.bTaskGroupsToCheck = Forest_bQTaskGroup | 0xD8000001;
  v3 = *(_DWORD *)&ptQTask[2].eQTaskType;
  v4 = *(_DWORD *)(v3 + 8);
  igi2_frame.ptWeaponQTask = (struct QTask_s *)v4;
  if ( v3 && v4 )
    igi2_frame.tWeaponCollisionEvaluateContext.ptIgnore1QTask = *(struct QTask_s **)(v4 + 32);
  else
    igi2_frame.tWeaponCollisionEvaluateContext.ptIgnore1QTask = nullptr;
  ptNext = ptQTask[3].ptNext;
  if ( ptNext )
    igi2_frame.tWeaponCollisionEvaluateContext.ptIgnore2QTask = ptNext->tQTaskChildren.ptHead;
  else
    igi2_frame.tWeaponCollisionEvaluateContext.ptIgnore2QTask = nullptr;
  if ( v4 )
  {
    igi2_frame.tWeaponCollisionEvaluateContext.vHitProbability = *(float *)(v4 + 100);
    v6 = *(_DWORD *)(v4 + 96);
    if ( v6 )
    {
      v7 = *(struct QTask_s **)(v6 + 8);
      if ( v7 )
      {
        igi2_frame.tWeaponHitContext.ptWeaponOwnerQTask = v7;
        goto LABEL_20;
      }
    }
  }
  else
  {
    igi2_frame.tWeaponCollisionEvaluateContext.vHitProbability = 1.0;
  }
  if ( v3 )
  {
    v8 = *(_DWORD *)(v3 + 8);
    v9 = nullptr;
    if ( v8 )
      v9 = *(struct QTask_s **)(v8 + 32);
    igi2_frame.tWeaponHitContext.ptWeaponOwnerQTask = v9;
  }
  else
  {
    igi2_frame.tWeaponHitContext.ptWeaponOwnerQTask = nullptr;
  }
LABEL_20:
  v10 = (int)ptQTask[4].ptPrev <= 0;
  igi2_frame.tWeaponCollisionEvaluateContext.tCollisionEvaluateContext.ptQTask = nullptr;
  igi2_frame.iItem = 0;
  if ( !v10 )
  {
    igi2_frame.p_ptTail = &ptQTask[4].tQTaskChildren.ptTail;
    while ( 1 )
    {
      v11 = (struct InstantItem_t *)*igi2_frame.p_ptTail;
      v12 = (float *)&(*igi2_frame.p_ptTail)[1];
      igi2_frame.tAfterHitDelta = *v12 * 40.959999084472656;
      igi2_frame.tAfterHitDelta_8a = *(float *)&(*igi2_frame.p_ptTail)[1].tQTaskChildren.ptHead;
      v13 = *(float *)&(*igi2_frame.p_ptTail)[1].ptPrev * 40.959999084472656;
      qmemcpy(&igi2_frame.tStart, &(*igi2_frame.p_ptTail)->tQTaskChildren.ptTail, sizeof(igi2_frame.tStart));
      igi2_frame.tAfterHitDelta_4 = v13;
      igi2_frame.tAfterHitDelta_8 = igi2_frame.tAfterHitDelta_8a * 40.959999084472656;
      igi2_frame.tEnd.vX = *v12;
      igi2_frame.tEnd.vY = v11->tDirection.vY;
      igi2_frame.v71 = v12;
      igi2_frame.tEnd.vZ = v11->tDirection.vZ;
      v14 = v11->vRange * igi2_frame.tEnd.vX;
      qmemcpy(&igi2_frame.tTracerStart, &igi2_frame.tStart, sizeof(igi2_frame.tTracerStart));
      igi2_frame.tEnd.vX = v14;
      igi2_frame.tEnd.vY = v11->vRange * igi2_frame.tEnd.vY;
      v15 = v11->vRange * igi2_frame.tEnd.vZ;
      igi2_frame.ptInstantItem = v11;
      igi2_frame.tEnd.vX = igi2_frame.tStart.vX + igi2_frame.tEnd.vX;
      igi2_frame.vDistanceTravelled = 0.0;
      igi2_frame.nNumStoredEffectParams = 0;
      igi2_frame.tEnd.vY = igi2_frame.tStart.vY + igi2_frame.tEnd.vY;
      igi2_frame.tEnd.vZ = igi2_frame.tStart.vZ + v15;
      vPenetrationPower = v11->vPenetrationPower;
      igi2_frame.vInitialPenetration = v11->vPenetrationPower;
      igi2_frame.isDoneTracing = vPenetrationPower == 0.0;
      if ( ((int)ptQTask[4].tQTaskChildren.ptMiddle & 4) != 0 )
        igi2_frame.tEnd.vZ = igi2_frame.tEnd.vZ - v11->vRange * 0.00020000000949949026;
      if ( vPenetrationPower != 0.0 )
        break;
LABEL_61:
      ptWeaponType = v11->ptWeaponType;
      if ( ptWeaponType->tTracerInfo.isUseTracer && ptWeaponType->tTracerInfo.ptGameTexture )
      {
        ptHead = ptQTask[4].tQTaskChildren.ptHead;
        if ( ptHead )
        {
          ptQTask[4].tQTaskChildren.ptHead = (struct QTask_s *)((char *)ptHead - 1);
        }
        else
        {
          igi2_frame.tGetWeaponObjectContext.ptWeaponObject = nullptr;
          igi2_frame.tGetWeaponObjectContext.isFirstPerson = false;
          ptParent = ptQTask->ptParent;
          igi2_frame.tGetWeaponObjectContext.nWeapon = 1;
          QTask_TriggerQTaskEventParent(ptParent, Weapon_eGetWeaponObjectEvent, &igi2_frame.tGetWeaponObjectContext);
          if ( igi2_frame.tGetWeaponObjectContext.ptWeaponObject )
            RigidDynCubeObj_GetMagicVertexPos(igi2_frame.tGetWeaponObjectContext.ptWeaponObject, 2u, &igi2_frame.tTracerStart);
          Tracerbullet_New(
            Level_ptDynamicQTask,
            &v11->ptWeaponType->tTracerInfo.ptGameTexture->tTexInfo,
            nullptr,
            &igi2_frame.tTracerStart,
            &igi2_frame.tTracerEnd,
            v11->ptWeaponType->tTracerInfo.vVelocity);
          ptQTask[4].tQTaskChildren.ptHead = (struct QTask_s *)5;
        }
      }
      if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
        Human_nFireTimeStamp = -1;
      v45 = igi2_frame.nNumStoredEffectParams;
      if ( igi2_frame.nNumStoredEffectParams && GunShot_isDisableGunShotEffects == false && igi2_frame.nNumStoredEffectParams > 0 )
      {
        p_tIntersection = &igi2_frame.atEffectParam[0].tIntersection;
        do
        {
          vLight_low = LOWORD(p_tIntersection[-1].vLight);
          if ( vLight_low )
          {
            v48 = *((float *)&p_tIntersection[1].tPos.vX + 1);
            vY_low = LODWORD(p_tIntersection[1].tPos.vY);
            igi2_frame.v90[1] = *((_DWORD *)&p_tIntersection[-1].vLight + 1);
            igi2_frame.v90[7] = vY_low;
            igi2_frame.v90[2] = p_tIntersection[1].ptHitObj;
            v50 = *((_DWORD *)&p_tIntersection[1].ptHitObj + 1);
            igi2_frame.v90[4] = LODWORD(p_tIntersection[1].tPos.vX);
            igi2_frame.v90[3] = v50;
            v51 = v11->ptWeaponType;
            igi2_frame.v90[0] = p_tIntersection;
            *(float *)&igi2_frame.v90[6] = v48;
            *(float *)&igi2_frame.v90[5] = v51->vSmokeParticleSize * 4096.0;
            ((void (__cdecl *)(_DWORD, _DWORD *))QTask_aatQTaskFinalEvent[GameMaterial_eCreateEffectQTaskEvent][vLight_low].pfHandler)(
              0,
              igi2_frame.v90);
          }
          p_tIntersection = (struct QIntersection_s *)((char *)p_tIntersection + 152);
          --v45;
        }
        while ( v45 );
      }
      v10 = ++igi2_frame.iItem < (int)ptQTask[4].ptPrev;
      ++igi2_frame.p_ptTail;
      if ( !v10 )
      {
        v1 = ptQTask;
        goto LABEL_79;
      }
    }
    igi2_frame.p_vPenetrationPower = &igi2_frame.atEffectParam[0].vPenetrationPower;
    igi2_frame.p_isPenetration = &igi2_frame.atEffectParam[0].isPenetration;
    igi2_frame.p_tParticleDirection = &igi2_frame.atEffectParam[0].tParticleDirection;
    igi2_frame.v56 = &igi2_frame.atEffectParam[0].tIntersection;
    igi2_frame.p_pxData = &igi2_frame.atEffectParam[0].pxData;
    igi2_frame.v58 = igi2_frame.atEffectParam;
    while ( 1 )
    {
      igi2_frame.tIntersection.ptEnterMaterial = nullptr;
      igi2_frame.tIntersection.ptLeaveMaterial = nullptr;
      World_TraceLines(
        Game_ptGame->ptWorld,
        &igi2_frame.tIntersection,
        &igi2_frame.tStart,
        &igi2_frame.tEnd,
        1,
        GameFunctions_eWeaponCollisionEvaluateQTaskEvent,
        &igi2_frame.tWeaponCollisionEvaluateContext.tCollisionEvaluateContext,
        igi2_frame.bTaskGroupsToCheck);
      if ( !igi2_frame.tIntersection.isHit )
      {
        qmemcpy(&igi2_frame.tTracerEnd, &igi2_frame.tEnd, sizeof(igi2_frame.tTracerEnd));
        goto LABEL_61;
      }
      igi2_frame.v88 = igi2_frame.tIntersection.tPos.vZ - igi2_frame.tStart.vZ;
      igi2_frame.vDistanceTravelled = sqrt(
                             (igi2_frame.tIntersection.tPos.vX - igi2_frame.tStart.vX) * (igi2_frame.tIntersection.tPos.vX - igi2_frame.tStart.vX)
                           + (igi2_frame.tIntersection.tPos.vY - igi2_frame.tStart.vY) * (igi2_frame.tIntersection.tPos.vY - igi2_frame.tStart.vY)
                           + igi2_frame.v88 * igi2_frame.v88)
                         + igi2_frame.vDistanceTravelled;
      if ( igi2_frame.tIntersection.ptEnterMaterial )
      {
        v17 = v11->vPenetrationPower / igi2_frame.vInitialPenetration;
        v18 = igi2_frame.vDistanceTravelled / v11->vRange;
        igi2_frame.tWeaponHitContext.ptIntersection = &igi2_frame.tIntersection;
        igi2_frame.tWeaponHitContext.vDamage = (1.0 - v18 * 0.30000001192092896) * v11->vDamage * v17;
        igi2_frame.tWeaponHitContext.ptWeaponType = v11->ptWeaponType;
        igi2_frame.tWeaponHitContext.ptAmmoType = v11->ptAmmoType;
        ptHitObj = igi2_frame.tIntersection.ptHitObj;
        igi2_frame.tWeaponHitContext.tDirection.vX = igi2_frame.tEnd.vX - igi2_frame.tStart.vX;
        igi2_frame.tWeaponHitContext.tDirection.vY = igi2_frame.tEnd.vY - igi2_frame.tStart.vY;
        igi2_frame.tWeaponHitContext.tDirection.vZ = igi2_frame.tEnd.vZ - igi2_frame.tStart.vZ;
        if ( igi2_frame.tIntersection.ptHitObj )
        {
          pfHandler = (void (__cdecl *)(struct QObj_s *, struct WeaponHitContext_t *))QTask_aatQTaskFinalEvent[GameFunctions_eWeaponHitQTaskEvent][igi2_frame.tIntersection.ptHitObj->tQTask.eQTaskType].pfHandler;
          if ( pfHandler )
          {
            pfHandler(igi2_frame.tIntersection.ptHitObj, &igi2_frame.tWeaponHitContext);
            ptHitObj = igi2_frame.tIntersection.ptHitObj;
          }
          if ( QTask_IsQTaskTypeDerived(ptHitObj->tQTask.eQTaskType, Terrain_eQTaskType) )
            igi2_frame.isDoneTracing = true;
        }
        if ( !igi2_frame.ptSoundQTask )
        {
          v21 = Game_ptGame;
          v22 = Game_ptGame->tRunRandomState.anRandom[0];
          v23 = (v22 >> 7) ^ Game_ptGame->tRunRandomState.anRandom[2];
          v24 = v23 ^ Game_ptGame->tRunRandomState.anRandom[1];
          Game_ptGame->tRunRandomState.anRandom[1] = v24;
          v25 = v24 + v22;
          v21->tRunRandomState.anRandom[2] = v23;
          v21->tRunRandomState.anRandom[0] = v25;
          v26 = SoundSys_NewSoundFn(
                  Level_ptDynamicQTask,
                  (char *)&igi2_frame.tIntersection.ptEnterMaterial[v25 % 6 + 23].tColor);
          igi2_frame.ptSoundQTask = v26;
          if ( v26 )
            ((void (__cdecl *)(struct QTask_s *, struct real64x3_t *))QTask_aatQTaskFinalEvent[SoundSys_eSetPositionQTaskEvent][v26->eQTaskType].pfHandler)(
              v26,
              &igi2_frame.tIntersection.tPos);
          igi2_frame.tEventContext.tDirection.vX = *igi2_frame.v71;
          igi2_frame.tEventContext.ptPosition = &igi2_frame.tIntersection.tPos;
          v27 = igi2_frame.v71[1];
          v28 = igi2_frame.v71[2];
          igi2_frame.tEventContext.tDirection.vX = igi2_frame.tEventContext.tDirection.vX * -1.0;
          igi2_frame.tEventContext.tDirection.vY = v27;
          igi2_frame.tEventContext.tDirection.vZ = v28;
          v29 = igi2_frame.ptWeaponQTask[2].tQTaskChildren.ptMiddle;
          ptTail = igi2_frame.ptWeaponQTask[2].tQTaskChildren.ptTail;
          igi2_frame.tEventContext.tDirection.vY = v27 * -1.0;
          igi2_frame.tEventContext.eEvent = 42;
          igi2_frame.tEventContext.bFlags = 1026;
          igi2_frame.tEventContext.vRadius = 40960.0;
          igi2_frame.tEventContext.tDirection.vZ = igi2_frame.tEventContext.tDirection.vZ * -1.0;
          igi2_frame.tEventContext.ptReferenceQTask = nullptr;
          igi2_frame.tEventContext.eTeam = (int)v29;
          if ( ptTail )
            v31 = ptTail->tQTaskChildren.ptHead;
          else
            v31 = nullptr;
          igi2_frame.tEventContext.ptHumanOriginatorQTask = v31;
          HumanAI_SendEvent(&igi2_frame.tEventContext);
          v11 = igi2_frame.ptInstantItem;
        }
        ptEnterMaterial = igi2_frame.tIntersection.ptEnterMaterial;
        v33 = v11->vPenetrationPower - igi2_frame.tIntersection.ptEnterMaterial[2].vTransparency;
        v11->vPenetrationPower = v33;
        if ( igi2_frame.nNumStoredEffectParams < (int)(*(_DWORD *)&ptQTask[3].eQTaskType) )
        {
          if ( v33 > 0.0 )
          {
            *igi2_frame.p_isPenetration = true;
          }
          else
          {
            *igi2_frame.p_isPenetration = false;
            igi2_frame.isDoneTracing = true;
          }
          v34 = igi2_frame.tIntersection.tNormal.vX == 0.0;
          igi2_frame.v58->eEffectQTaskType = LOWORD(ptEnterMaterial[31].tColor.vX);
          *igi2_frame.p_pxData = (void *)LODWORD(ptEnterMaterial[31].tColor.vY);
          vX = igi2_frame.tIntersection.tNormal.vX;
          qmemcpy(igi2_frame.v56, &igi2_frame.tIntersection, sizeof(struct QIntersection_s));
          *igi2_frame.p_vPenetrationPower = v11->vPenetrationPower;
          igi2_frame.tVec_4 = igi2_frame.tIntersection.tNormal.vY;
          igi2_frame.tVec = vX;
          igi2_frame.tVec_8 = igi2_frame.tIntersection.tNormal.vZ;
          if ( !v34 || igi2_frame.tIntersection.tNormal.vY != 0.0 || igi2_frame.tIntersection.tNormal.vZ != 0.0 )
          {
            v36 = 1.0
                / sqrt(
                    igi2_frame.tIntersection.tNormal.vX * igi2_frame.tIntersection.tNormal.vX
                  + igi2_frame.tIntersection.tNormal.vY * igi2_frame.tIntersection.tNormal.vY
                  + igi2_frame.tIntersection.tNormal.vZ * igi2_frame.tIntersection.tNormal.vZ);
            igi2_frame.tVec = igi2_frame.tIntersection.tNormal.vX * v36;
            igi2_frame.tVec_4 = igi2_frame.tIntersection.tNormal.vY * v36;
            igi2_frame.tVec_8 = igi2_frame.tIntersection.tNormal.vZ * v36;
          }
          v37 = *igi2_frame.v71 * -1.0;
          v38 = igi2_frame.v71[1] * -1.0;
          v39 = igi2_frame.v71[2] * -1.0;
          igi2_frame.tDir_8 = v39;
          ++igi2_frame.nNumStoredEffectParams;
          v40 = v39 * igi2_frame.tVec_8 + v38 * igi2_frame.tVec_4 + v37 * igi2_frame.tVec;
          igi2_frame.tVec_4a = v40 * igi2_frame.tVec_4 + v40 * igi2_frame.tVec_4;
          igi2_frame.tVec_8a = v40 * igi2_frame.tVec_8 + v40 * igi2_frame.tVec_8;
          igi2_frame.tDir = igi2_frame.tVec * v40 + igi2_frame.tVec * v40 - v37;
          igi2_frame.p_tParticleDirection->vX = igi2_frame.tDir;
          igi2_frame.tDir_4 = igi2_frame.tVec_4a - v38;
          igi2_frame.p_tParticleDirection->vY = igi2_frame.tDir_4;
          igi2_frame.tDir_8a = igi2_frame.tVec_8a - igi2_frame.tDir_8;
          igi2_frame.p_tParticleDirection->vZ = igi2_frame.tDir_8a;
          igi2_frame.p_pxData += 38;
          igi2_frame.p_tParticleDirection = (struct real32x3_t *)((char *)igi2_frame.p_tParticleDirection + 152);
          ++igi2_frame.v58;
          igi2_frame.v56 = (struct QIntersection_s *)((char *)igi2_frame.v56 + 152);
          igi2_frame.p_isPenetration += 38;
          igi2_frame.p_vPenetrationPower += 38;
          goto LABEL_58;
        }
      }
      else
      {
        ptLeaveMaterial = igi2_frame.tIntersection.ptLeaveMaterial;
        if ( igi2_frame.tIntersection.ptLeaveMaterial )
        {
          if ( igi2_frame.nNumStoredEffectParams >= (int)(*(_DWORD *)&ptQTask[3].eQTaskType)
            || v11->vPenetrationPower <= (double)igi2_frame.tIntersection.ptLeaveMaterial[2].vTransparency )
          {
            igi2_frame.isDoneTracing = true;
          }
          else
          {
            v11->vPenetrationPower = v11->vPenetrationPower - igi2_frame.tIntersection.ptLeaveMaterial[2].vTransparency;
            igi2_frame.v58->eEffectQTaskType = LOWORD(ptLeaveMaterial[31].tColor.vZ);
            *igi2_frame.p_pxData = (void *)LODWORD(ptLeaveMaterial[32].vTransparency);
            qmemcpy(igi2_frame.v56, &igi2_frame.tIntersection, sizeof(struct QIntersection_s));
            igi2_frame.p_tParticleDirection->vX = *igi2_frame.v71;
            igi2_frame.p_tParticleDirection->vY = igi2_frame.v71[1];
            igi2_frame.p_tParticleDirection->vZ = igi2_frame.v71[2];
            *igi2_frame.p_isPenetration = true;
            *igi2_frame.p_vPenetrationPower = v11->vPenetrationPower;
            ++igi2_frame.nNumStoredEffectParams;
            ++igi2_frame.v58;
            igi2_frame.p_pxData += 38;
            igi2_frame.v56 = (struct QIntersection_s *)((char *)igi2_frame.v56 + 152);
            igi2_frame.p_tParticleDirection = (struct real32x3_t *)((char *)igi2_frame.p_tParticleDirection + 152);
            igi2_frame.p_isPenetration += 38;
            igi2_frame.p_vPenetrationPower += 38;
          }
          if ( !igi2_frame.tIntersection.ptHitObj
            || QTask_IsQTaskTypeDerived(igi2_frame.tIntersection.ptHitObj->tQTask.eQTaskType, Terrain_eQTaskType) == false )
          {
            goto LABEL_58;
          }
        }
      }
      igi2_frame.isDoneTracing = true;
LABEL_58:
      igi2_frame.tStart.vX = igi2_frame.tAfterHitDelta + igi2_frame.tIntersection.tPos.vX;
      qmemcpy(&igi2_frame.tTracerEnd, &igi2_frame.tIntersection.tPos, sizeof(igi2_frame.tTracerEnd));
      igi2_frame.tStart.vY = igi2_frame.tAfterHitDelta_4 + igi2_frame.tIntersection.tPos.vY;
      igi2_frame.tStart.vZ = igi2_frame.tAfterHitDelta_8 + igi2_frame.tIntersection.tPos.vZ;
      if ( igi2_frame.isDoneTracing )
        goto LABEL_61;
    }
  }
LABEL_79:
  v52 = v1 + 6;
  v53 = 15;
  do
  {
    v52->ptNext = nullptr;
    v52 = (struct QTask_s *)((char *)v52 + 72);
    --v53;
  }
  while ( v53 );
  v1[4].ptPrev = nullptr;
}

// source: j/0/weapons/gunshot.c:499  [anchor-mhash]
void __cdecl GunShot_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v2; // eax
  int v3; // ecx

  ptQTask[2].ptParent = nullptr;
  *(_DWORD *)&ptQTask[2].eQTaskType = 0;
  ptQTask[3].ptNext = nullptr;
  ptQTask[3].tQTaskChildren.ptHead = nullptr;
  ptQTask[3].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[3].tQTaskChildren.ptTail = nullptr;
  ptQTask[3].tQTaskRefList.ptHead = nullptr;
  ptQTask[3].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[3].tQTaskRefList.ptTail = nullptr;
  ptQTask[3].ptParent = nullptr;
  ptQTask[4].ptPrev = nullptr;
  ptQTask[4].tQTaskChildren.ptHead = (struct QTask_s *)5;
  ptQTask[4].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[4].ptNext = nullptr;
  *(_DWORD *)&ptQTask[3].eQTaskType = 10;
  memset(&ptQTask[4].tQTaskChildren.ptTail, 0, 0x3Cu);
  v2 = ptQTask + 6;
  v3 = 15;
  do
  {
    v2->ptNext = nullptr;
    v2 = (struct QTask_s *)((char *)v2 + 72);
    --v3;
  }
  while ( v3 );
}

// source: j/0/weapons/gunshot.c:551  [anchor-mhash]
void __cdecl GunShot_RunHandler(struct QTask_s *ptQTask)
{
  int v1; // eax
  struct QTaskList_s *v2; // eax
  int v3; // esi
  int v4; // edi
  struct HumanEvaluateGunShotContext_t tContext; // [esp+4h] [ebp-Ch] BYREF

  v1 = *(_DWORD *)&ptQTask[2].eQTaskType;
  if ( v1 && *(_DWORD *)(v1 + 8) )
  {
    if ( ptQTask[4].ptPrev )
    {
      tContext.ptGunShotCreatorQTaskRef = *(struct QReference_s **)&ptQTask[2].eQTaskType;
      tContext.ptGunShotIgnoreQTaskRef = (struct QReference_s *)ptQTask[3].ptNext;
      v2 = Human_ptQTaskList;
      tContext.ptGunShotQTask = ptQTask;
      v3 = 0;
      if ( Human_ptQTaskList->nTask > 0 )
      {
        v4 = 8;
        do
        {
          ((void (__cdecl *)(_DWORD, struct HumanEvaluateGunShotContext_t *))QTask_aatQTaskFinalEvent[Human_eEvaluateGunShotQTaskEvent][*(unsigned __int16 *)(*(int *)((char *)&v2->nTask + v4) + 36)].pfHandler)(
            *(int *)((char *)&v2->nTask + v4),
            &tContext);
          v2 = Human_ptQTaskList;
          ++v3;
          v4 += 4;
        }
        while ( v3 < Human_ptQTaskList->nTask );
      }
      GunShot_RunInstant(ptQTask);
    }
  }
  else
  {
    ptQTask[4].ptPrev = nullptr;
  }
  if ( !ptQTask[4].ptPrev )
  {
    if ( ptQTask[2].ptParent )
      QTask_Delete(ptQTask);
  }
}

// source: j/0/weapons/gunshot.c:601  [size]
void __cdecl GunShot_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QReference_s *v1; // eax
  struct QTask_s *ptNext; // eax

  v1 = *(struct QReference_s **)&ptQTask[2].eQTaskType;
  if ( v1 )
  {
    QReference_Delete(v1, &QTask_tQTaskRefPool);
    *(_DWORD *)&ptQTask[2].eQTaskType = 0;
  }
  ptNext = ptQTask[3].ptNext;
  if ( ptNext )
  {
    QReference_Delete((struct QReference_s *)ptNext, &QTask_tQTaskRefPool);
    ptQTask[3].ptNext = nullptr;
  }
}

// source: j/0/weapons/gunshot.c:631  [size]
void __cdecl GunShot_EnterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: j/0/weapons/gunshot.c:646  [anchor-strings]
void __cdecl GunShot_CreateWeaponTypeParametersHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v2; // eax
  struct QTask_s *v3; // edi
  struct QTask_s *v4; // esi
  struct QTask_s *v5; // eax
  double v6; // st7
  struct QTask_s *v7; // edi
  struct QTask_s *v8; // eax

  v2 = QTask_NewFn(nullptr, GunShot_eGunShotParametersQTaskType, nullptr);
  v3 = *((struct QTask_s **)pxContext + 1);
  v4 = v2;
  *((_DWORD *)pxContext + 2) = v2;
  v5 = TagItem_Find(v3, (char *)&stru_691BB8.tQTaskRefList);
  if ( v5 || (v5 = TagItem_NewReal32MinMax(v3, (char *)&stru_691BB8.tQTaskRefList, 1.0, 0.0, 1.0)) != nullptr )
    v6 = *(float *)&v5[7].tQTaskRefList.ptHead;
  else
    v6 = 0.0;
  *(float *)&v4[1].ptNext = v6;
  v7 = *((struct QTask_s **)pxContext + 1);
  v8 = TagItem_Find(v7, (char *)&stru_691BB8);
  if ( v8 || (v8 = TagItem_NewReal32(v7, (char *)&stru_691BB8, 1.0)) != nullptr )
    v4[1].ptPrev = (struct QTask_s *)v8[7].tQTaskRefList.ptHead;
  else
    v4[1].ptPrev = nullptr;
}

// source: j/0/weapons/gunshot.c:671  [anchor-mhash]
void __cdecl GunShot_CreateProjectileHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v3; // eax
  int v4; // edx
  float *v5; // eax
  int v6; // esi
  float v7; // edi
  bool v8; // zf
  struct real32x3_t tDirection; // [esp+0h] [ebp-Ch] BYREF
  float pxContexta = *(float *)&pxContext; // [esp+14h] [ebp+8h] ARGSLOT

  v3 = *(_DWORD *)(*((_DWORD *)pxContext + 2) + 200);
  if ( v3 )
  {
    v4 = *(_DWORD *)(v3 + 8);
    if ( v4 )
    {
      v5 = *((float **)pxContext + 8);
      v6 = *((_DWORD *)pxContext + 17);
      tDirection.vX = v5[1];
      v7 = v5[4];
      tDirection.vZ = v5[7];
      pxContexta = *((float *)pxContext + 11);
      v8 = (*(_BYTE *)(v4 + 172) & 1) == 0;
      tDirection.vY = v7;
      if ( !v8 && *(float *)(v4 + 160) < (double)pxContexta )
        pxContexta = *(float *)(v4 + 160);
      GunShot_AddInstant(
        (struct QTask_s *)v4,
        *((struct real64x3_t **)pxContext + 4),
        &tDirection,
        pxContexta,
        *(float *)(v6 + 40),
        *(float *)(v6 + 44),
        *((struct WeaponType_s **)pxContext + 15),
        *((struct AmmoType_s **)pxContext + 16));
    }
  }
}

// source: j/0/weapons/gunshot.c:735  [anchor-mhash]
struct QTask_s *__cdecl GunShot_New(struct QTask_s *ptParent, struct QTask_s *ptCreatorQTask)
{
  struct QTask_s *v2; // esi

  v2 = QTask_NewFn(ptParent, GunShot_eQTaskType, nullptr);
  if ( ptCreatorQTask )
    *(_DWORD *)&v2[2].eQTaskType = QTask_NewQTaskRef(ptCreatorQTask);
  return v2;
}

// source: j/0/weapons/gunshot.c:774  [anchor-mhash]
void __cdecl GunShot_SetSelfDestruct(struct QTask_s *ptGunShotQTask, int isSelfDestruct)
{
  if ( ptGunShotQTask[4].ptPrev )
    ptGunShotQTask[2].ptParent = (struct QTask_s *)isSelfDestruct;
  else
    QTask_Delete(ptGunShotQTask);
}

// source: j/0/weapons/gunshot.c:806  [anchor-mhash]
void __cdecl GunShot_AddInstant(
        struct QTask_s *ptGunShotQTask,
        struct real64x3_t *ptPos,
        struct real32x3_t *ptDirection,
        float vEffectiveRange,
        float vDamageFactor,
        float vPenetrationPower,
        struct WeaponType_s *ptWeaponType,
        struct AmmoType_s *ptAmmoType)
{
  struct QTask_s *ptPrev; // edi
  int v9; // esi
  struct QTask_s **p_ptParent; // ecx
  struct QTask_s **v11; // eax

  ptPrev = ptGunShotQTask[4].ptPrev;
  if ( (int)ptPrev < 15 )
  {
    v9 = 0;
    p_ptParent = &ptGunShotQTask[7].ptParent;
    do
    {
      v11 = p_ptParent - 18;
      if ( !*(p_ptParent - 18) )
        break;
      v11 = p_ptParent;
      if ( !*p_ptParent )
        break;
      v11 = p_ptParent + 18;
      if ( !p_ptParent[18] )
        break;
      v11 = p_ptParent + 36;
      if ( !p_ptParent[36] )
        break;
      v11 = p_ptParent + 54;
      if ( !p_ptParent[54] )
        break;
      v9 += 5;
      p_ptParent += 90;
    }
    while ( v9 < 15 );
    *((_DWORD *)&ptGunShotQTask[4].tQTaskChildren.ptTail + (_DWORD)ptPrev) = v11;
    *v11 = (struct QTask_s *)1;
    qmemcpy(v11 + 4, ptPos, 0x18u);
    *(struct real32x3_t *)(v11 + 10) = *ptDirection;
    *((float *)v11 + 13) = vEffectiveRange * 4096.0;
    *((float *)v11 + 14) = vDamageFactor;
    *((float *)v11 + 15) = vPenetrationPower;
    v11[1] = &ptWeaponType->tQTask;
    v11[2] = &ptAmmoType->tQTask;
    *((_BYTE *)v11 + 64) = 0;
    *((_BYTE *)v11 + 65) = 0;
    ++*(int *)&ptGunShotQTask[4].ptPrev;
  }
  ++*(int *)&ptGunShotQTask[3].ptParent;
}

// source: j/0/weapons/gunshot.c:885  [size]
struct QTask_s *__cdecl GunShot_SetFirePos(
        struct QTask_s *ptGunShotQTask,
        struct real64x3_t *ptFirePos)
{
  qmemcpy(&ptGunShotQTask[3].tQTaskChildren, ptFirePos, 0x18u);
  return ptGunShotQTask;
}

// source: j/0/weapons/gunshot.c:904  [anchor-callee]
int __cdecl GunShot_FindHearableIntersections(
        struct real64x3_t *ptIntersection,
        int nMaxIntersections,
        struct QTask_s *ptGunShotQTask,
        struct real64x3_t *ptTargetPosition)
{
  #pragma pack(push, 1)
  union
  {
    struct { float **p_ptTail; };
    struct { char igi2_o1[4]; int iC; };
    struct { char igi2_o2[8]; float tReal32x3; };
    struct { char igi2_o3[8]; float tReal32x3a; };
    struct { char igi2_o4[8]; float tReal32x3b; };
    struct { char igi2_o5[12]; float tReal32x3_4; };
    struct { char igi2_o6[12]; float tReal32x3_4a; };
    struct { char igi2_o7[12]; float tReal32x3_4b; };
    struct { char igi2_o8[20]; double tV; };
    struct { char igi2_o9[28]; double tV_8; };
    struct { char igi2_o10[36]; double tV_16; };
    struct { char igi2_o11[44]; struct real64x3_t tP0; };
    struct { char igi2_o12[68]; struct real64x3_t tP1; };
    char igi2_extent[92];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v4; // ebx
  float *v5; // eax
  double v6; // st7
  double v7; // st6
  double v8; // st7
  struct real64x3_t *v9; // edi
  double v10; // st6
  double v11; // st6
  struct real64x3_t *v12; // edi
  bool v13; // cc

  v4 = 0;
  igi2_frame.iC = 0;
  if ( (int)ptGunShotQTask[4].ptPrev > 0 )
  {
    igi2_frame.p_ptTail = (float **)&ptGunShotQTask[4].tQTaskChildren.ptTail;
    do
    {
      if ( v4 >= nMaxIntersections )
        break;
      v5 = *igi2_frame.p_ptTail;
      if ( *(_DWORD *)*igi2_frame.p_ptTail )
      {
        v6 = v5[10];
        v7 = v5[11];
        igi2_frame.tV_16 = v5[12];
        qmemcpy(&igi2_frame.tP0, v5 + 4, sizeof(igi2_frame.tP0));
        igi2_frame.tV = v5[13] * v6;
        igi2_frame.tV_8 = v5[13] * v7;
        v8 = v5[13] * igi2_frame.tV_16;
        igi2_frame.tReal32x3 = igi2_frame.tP0.vX - ptTargetPosition->vX;
        igi2_frame.tReal32x3_4 = igi2_frame.tP0.vY - ptTargetPosition->vY;
        if ( sqrt(
               igi2_frame.tReal32x3 * igi2_frame.tReal32x3
             + igi2_frame.tReal32x3_4 * igi2_frame.tReal32x3_4
             + (igi2_frame.tP0.vZ - ptTargetPosition->vZ) * (igi2_frame.tP0.vZ - ptTargetPosition->vZ)) >= 8192.0 )
        {
          igi2_frame.tP1.vX = igi2_frame.tP0.vX + igi2_frame.tV;
          igi2_frame.tP1.vY = igi2_frame.tP0.vY + igi2_frame.tV_8;
          igi2_frame.tP1.vZ = igi2_frame.tP0.vZ + v8;
          igi2_frame.tReal32x3a = igi2_frame.tP1.vX - ptTargetPosition->vX;
          igi2_frame.tReal32x3_4a = igi2_frame.tP1.vY - ptTargetPosition->vY;
          if ( sqrt(
                 igi2_frame.tReal32x3a * igi2_frame.tReal32x3a
               + igi2_frame.tReal32x3_4a * igi2_frame.tReal32x3_4a
               + (igi2_frame.tP1.vZ - ptTargetPosition->vZ) * (igi2_frame.tP1.vZ - ptTargetPosition->vZ)) < 8192.0
            || (v10 = v8 * v8 * 0.000244140625 + igi2_frame.tV_8 * igi2_frame.tV_8 * 0.000244140625 + igi2_frame.tV * igi2_frame.tV * 0.000244140625, v10 > 0.0)
            && (v11 = ((ptTargetPosition->vY - igi2_frame.tP0.vY) * igi2_frame.tV_8 * 0.000244140625
                     + (ptTargetPosition->vZ - igi2_frame.tP0.vZ) * v8 * 0.000244140625
                     + (ptTargetPosition->vX - igi2_frame.tP0.vX) * igi2_frame.tV * 0.000244140625)
                    / v10,
                v11 >= 0.0)
            && v11 <= 1.0
            && (igi2_frame.tP1.vX = igi2_frame.tP0.vX + igi2_frame.tV * v11,
                igi2_frame.tP1.vY = igi2_frame.tP0.vY + igi2_frame.tV_8 * v11,
                igi2_frame.tP1.vZ = igi2_frame.tP0.vZ + v8 * v11,
                igi2_frame.tReal32x3b = igi2_frame.tP1.vX - ptTargetPosition->vX,
                igi2_frame.tReal32x3_4b = igi2_frame.tP1.vY - ptTargetPosition->vY,
                sqrt(
                  igi2_frame.tReal32x3b * igi2_frame.tReal32x3b
                + igi2_frame.tReal32x3_4b * igi2_frame.tReal32x3_4b
                + (igi2_frame.tP1.vZ - ptTargetPosition->vZ) * (igi2_frame.tP1.vZ - ptTargetPosition->vZ)) < 8192.0) )
          {
            v12 = ptIntersection++;
            qmemcpy(v12, &igi2_frame.tP1, sizeof(struct real64x3_t));
            ++v4;
          }
        }
        else
        {
          v9 = ptIntersection++;
          qmemcpy(v9, &igi2_frame.tP0, sizeof(struct real64x3_t));
          ++v4;
        }
      }
      v13 = ++igi2_frame.iC < (int)ptGunShotQTask[4].ptPrev;
      ++igi2_frame.p_ptTail;
    }
    while ( v13 );
  }
  return v4;
}

// source: j/0/weapons/gunshot.c:1000  [size]
int __cdecl GunShot_GetFlags(struct QTask_s *ptGunShotQTask)
{
  return (int)ptGunShotQTask[4].tQTaskChildren.ptMiddle;
}

// source: j/0/weapons/gunshot.c:1016  [size]
int __cdecl GunShot_SetFlags(struct QTask_s *ptGunShotQTask, int bFlags)
{
  ptGunShotQTask[4].tQTaskChildren.ptMiddle = (struct QTask_s *)bFlags;
  return bFlags;
}

// source: j/0/weapons/gunshot.c:1033  [size]
void __cdecl GunShot_SetRangeLimit(struct QTask_s *ptGunShotQTask, float vRange)
{
  *(float *)&ptGunShotQTask[4].ptNext = vRange;
}

// source: j/0/weapons/gunshot.c:1051  [anchor-mhash]
void __cdecl GunShot_SetIgnoreQTask(struct QTask_s *ptGunShotQTask, struct QTask_s *ptIgnoreQTask)
{
  struct QTask_s *ptNext; // eax

  ptNext = ptGunShotQTask[3].ptNext;
  if ( ptNext )
    QReference_Delete((struct QReference_s *)ptNext, &QTask_tQTaskRefPool);
  ptGunShotQTask[3].ptNext = (struct QTask_s *)QTask_NewQTaskRef(ptIgnoreQTask);
}

// source: j/0/weapons/gunshot.c:1073  [size]
unsigned __int16 __cdecl GunShot_GetQTaskType()
{
  return GunShot_eQTaskType;
}

// source: j/0/weapons/gunshot.c:1088  [anchor-mhash]
void __cdecl GunShot_ClearInstantItems(struct QTask_s *ptGunShotQTask)
{
  struct QTask_s *v1; // eax
  int v2; // ecx

  v1 = ptGunShotQTask + 6;
  v2 = 15;
  do
  {
    v1->ptNext = nullptr;
    v1 = (struct QTask_s *)((char *)v1 + 72);
    --v2;
  }
  while ( v2 );
  ptGunShotQTask[4].ptPrev = nullptr;
}

// source: j/0/weapons/gunshot.c:1115  [size]
enum bool __cdecl GunShot_IsGunShotEffectsEnabled()
{
  return GunShot_isDisableGunShotEffects == false;
}

// source: j/0/weapons/gunshot.c:1128  [size]
void __cdecl GunShot_EnableGunShotEffects(enum bool isEnabled)
{
  GunShot_isDisableGunShotEffects = isEnabled == false;
}

// source: j/0/weapons/gunshot.c:1142  [size]
int __cdecl GunShot_SetMaxPenetrations(
        struct QTask_s *ptGunShotQTask,
        int nPenetrations)
{
  if ( nPenetrations >= 50 )
    nPenetrations = 50;
  *(_DWORD *)&ptGunShotQTask[3].eQTaskType = nPenetrations;
  return nPenetrations;
}

// source: j/0/weapons/gunshot.c:1160  [anchor-hash]
void __cdecl GunShot_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // ax
  unsigned __int16 v2; // si

  BaseQTaskType = QTask_GetBaseQTaskType();
  GunShot_eQTaskType = QTask_NewQTaskType("GunShot", 1320, BaseQTaskType, 0, 0);
  v1 = QTask_NewQTaskType("GunShotParameters", 48, WeaponTypeParameters_eQTaskType, 0, 0);
  v2 = GunShot_eQTaskType;
  GunShot_eGunShotParametersQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(
    GunShot_eQTaskType,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskDontSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v2, 0, GunShot_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, 1, GunShot_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, 2, GunShot_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v2, 5, (void (__cdecl *)(struct QTask_s *, void *))GunShot_EnterHandler);
  QTask_LinkQTaskEventHandlerFn(v2, WeaponType_eCreateParametersQTaskEvent, GunShot_CreateWeaponTypeParametersHandler);
  QTask_LinkQTaskEventHandlerFn(v2, Weapon_eCreateProjectileQTaskEvent, GunShot_CreateProjectileHandler);
  Symbol_Register(
    "TASKTYPE_GUNSHOT",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)v2,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}

// source: j/0/weapons/gunshot.c:1193  [size]
void __cdecl GunShot_Close()
{
  QTask_DeleteQTaskType(GunShot_eQTaskType);
  QTask_DeleteQTaskType(GunShot_eGunShotParametersQTaskType);
}
