/* j/0/humanai/humanaicontent.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/humanai/humanaicontent.c:190  [anchor-callee]
void __cdecl HumanAIContent_UseCombatView(struct HumanAI_s *ptHumanAI)
{
  int v1; // eax
  double vInvestigateViewCone2Alpha; // st7
  int v3; // eax
  double vInvestigateShoutFrequency; // [esp+0h] [ebp-8h]

  v1 = *(&ptHumanAI->atAnimationEntries[1].nAnimation + 1);
  ptHumanAI->tView.vViewConeAlpha = ptHumanAI->tTweakParameters.vInvestigateViewCone1Length;
  ptHumanAI->tView.vViewConeGamma = ptHumanAI->tTweakParameters.vInvestigateViewCone1Length;
  vInvestigateViewCone2Alpha = ptHumanAI->tTweakParameters.vInvestigateViewCone2Alpha;
  ptHumanAI->tView.vViewConeLength = vInvestigateViewCone2Alpha;
  ptHumanAI->tView.vSecondaryViewConeAlpha = ptHumanAI->tTweakParameters.vInvestigateViewCone2Length;
  ptHumanAI->tView.vSecondaryViewConeGamma = ptHumanAI->tTweakParameters.vInvestigateViewCone2Length;
  vInvestigateShoutFrequency = ptHumanAI->tTweakParameters.vInvestigateShoutFrequency;
  ptHumanAI->tView.vSecondaryViewConeLength = vInvestigateShoutFrequency;
  if ( v1 )
  {
    v3 = **(_DWORD **)(v1 + 116);
    if ( v3 )
    {
      if ( *(_WORD *)(*(_DWORD *)(*(_DWORD *)(v3 + 12) + 12) + 132) )
      {
        if ( vInvestigateViewCone2Alpha >= 204800.0 )
          vInvestigateViewCone2Alpha = 204800.0;
        ptHumanAI->tView.vViewConeLength = vInvestigateViewCone2Alpha;
        if ( vInvestigateShoutFrequency >= 204800.0 )
          ptHumanAI->tView.vSecondaryViewConeLength = 204800.0;
        else
          ptHumanAI->tView.vSecondaryViewConeLength = vInvestigateShoutFrequency;
      }
    }
  }
}

// source: j/0/humanai/humanaicontent.c:226  [anchor-mhash]
void __cdecl HumanAIContent_UseInvestigateView(struct HumanAI_s *ptHumanAI)
{
  int v1; // eax
  double v2; // st7
  int v3; // eax
  double v4; // [esp+0h] [ebp-8h]

  v1 = *(&ptHumanAI->atAnimationEntries[1].nAnimation + 1);
  ptHumanAI->tView.vViewConeAlpha = ptHumanAI->tTweakParameters.avDamageMultiplier[3];
  ptHumanAI->tView.vViewConeGamma = ptHumanAI->tTweakParameters.avDamageMultiplier[3];
  v2 = ptHumanAI->tTweakParameters.avDamageMultiplier[4];
  ptHumanAI->tView.vViewConeLength = v2;
  ptHumanAI->tView.vSecondaryViewConeAlpha = ptHumanAI->tTweakParameters.avDamageMultiplier[5];
  ptHumanAI->tView.vSecondaryViewConeGamma = ptHumanAI->tTweakParameters.avDamageMultiplier[5];
  v4 = ptHumanAI->tTweakParameters.avDamageMultiplier[6];
  ptHumanAI->tView.vSecondaryViewConeLength = v4;
  if ( v1 )
  {
    v3 = **(_DWORD **)(v1 + 116);
    if ( v3 )
    {
      if ( *(_WORD *)(*(_DWORD *)(*(_DWORD *)(v3 + 12) + 12) + 132) )
      {
        if ( v2 >= 204800.0 )
          v2 = 204800.0;
        ptHumanAI->tView.vViewConeLength = v2;
        if ( v4 >= 204800.0 )
          ptHumanAI->tView.vSecondaryViewConeLength = 204800.0;
        else
          ptHumanAI->tView.vSecondaryViewConeLength = v4;
      }
    }
  }
}

// source: j/0/humanai/humanaicontent.c:262  [anchor-callee]
void __cdecl HumanAIContent_UseIdleView(struct HumanAI_s *ptHumanAI)
{
  int v1; // eax
  double vDetectionToAttackTime; // st7
  int v3; // eax
  double v4; // [esp+0h] [ebp-8h]

  v1 = *(&ptHumanAI->atAnimationEntries[1].nAnimation + 1);
  ptHumanAI->tView.vViewConeAlpha = ptHumanAI->tTweakParameters.vAnimSpeedFactor;
  ptHumanAI->tView.vViewConeGamma = ptHumanAI->tTweakParameters.vAnimSpeedFactor;
  vDetectionToAttackTime = ptHumanAI->tTweakParameters.vDetectionToAttackTime;
  ptHumanAI->tView.vViewConeLength = vDetectionToAttackTime;
  ptHumanAI->tView.vSecondaryViewConeAlpha = ptHumanAI->tTweakParameters.avDamageMultiplier[0];
  ptHumanAI->tView.vSecondaryViewConeGamma = ptHumanAI->tTweakParameters.avDamageMultiplier[0];
  v4 = ptHumanAI->tTweakParameters.avDamageMultiplier[1];
  ptHumanAI->tView.vSecondaryViewConeLength = v4;
  if ( v1 )
  {
    if ( (ptHumanAI->anEventPriorityList[5] & 0x20) == 0 )
    {
      v3 = **(_DWORD **)(v1 + 116);
      if ( v3 )
      {
        if ( *(_WORD *)(*(_DWORD *)(*(_DWORD *)(v3 + 12) + 12) + 132) )
        {
          if ( vDetectionToAttackTime >= 204800.0 )
            vDetectionToAttackTime = 204800.0;
          ptHumanAI->tView.vViewConeLength = vDetectionToAttackTime;
          if ( v4 >= 204800.0 )
            ptHumanAI->tView.vSecondaryViewConeLength = 204800.0;
          else
            ptHumanAI->tView.vSecondaryViewConeLength = v4;
        }
      }
    }
  }
}

// source: j/0/humanai/humanaicontent.c:297  [anchor-hash]
void __cdecl HumanAIContent_InitLookAroundPatterns()
{
  HumanAIContent_atLookAroundPattern[0].atPatternItem[0].nTimeUntilRotation = 150;
  HumanAIContent_atLookAroundPattern[0].atPatternItem[1].nTimeUntilRotation = 150;
  HumanAIContent_atLookAroundPattern[0].atPatternItem[2].nTimeUntilRotation = 150;
  HumanAIContent_atLookAroundPattern[0].atPatternItem[3].nTimeUntilRotation = 150;
  HumanAIContent_atLookAroundPattern[3].atPatternItem[0].nTimeUntilRotation = 150;
  HumanAIContent_atLookAroundPattern[3].atPatternItem[1].nTimeUntilRotation = 150;
  HumanAIContent_atLookAroundPattern[3].atPatternItem[2].nTimeUntilRotation = 150;
  HumanAIContent_atLookAroundPattern[3].atPatternItem[3].nTimeUntilRotation = 150;
  HumanAIContent_atLookAroundPattern[4].atPatternItem[0].nTimeUntilRotation = 150;
  HumanAIContent_atLookAroundPattern[4].atPatternItem[1].nTimeUntilRotation = 150;
  HumanAIContent_atLookAroundPattern[4].atPatternItem[2].nTimeUntilRotation = 150;
  HumanAIContent_atLookAroundPattern[4].atPatternItem[3].nTimeUntilRotation = 150;
  HumanAIContent_atLookAroundPattern[0].nNumItems = 4;
  HumanAIContent_atLookAroundPattern[0].vRotationSpeed = 0.05235987901687622;
  HumanAIContent_atLookAroundPattern[0].atPatternItem[0].vRotation = -1.5707963705062866;
  HumanAIContent_atLookAroundPattern[0].atPatternItem[1].vRotation = -1.5707963705062866;
  HumanAIContent_atLookAroundPattern[0].atPatternItem[2].vRotation = 1.5707963705062866;
  HumanAIContent_atLookAroundPattern[0].atPatternItem[3].vRotation = 1.5707963705062866;
  HumanAIContent_atLookAroundPattern[1].nNumItems = 4;
  HumanAIContent_atLookAroundPattern[1].vRotationSpeed = 0.10471975803375244;
  HumanAIContent_atLookAroundPattern[1].atPatternItem[0].nTimeUntilRotation = 30;
  HumanAIContent_atLookAroundPattern[1].atPatternItem[0].vRotation = -0.7853981852531433;
  HumanAIContent_atLookAroundPattern[1].atPatternItem[1].nTimeUntilRotation = 30;
  HumanAIContent_atLookAroundPattern[1].atPatternItem[1].vRotation = 0.7853981852531433;
  HumanAIContent_atLookAroundPattern[1].atPatternItem[2].nTimeUntilRotation = 30;
  HumanAIContent_atLookAroundPattern[1].atPatternItem[2].vRotation = 0.7853981852531433;
  HumanAIContent_atLookAroundPattern[1].atPatternItem[3].nTimeUntilRotation = 30;
  HumanAIContent_atLookAroundPattern[1].atPatternItem[3].vRotation = -0.7853981852531433;
  HumanAIContent_atLookAroundPattern[2].nNumItems = 4;
  HumanAIContent_atLookAroundPattern[2].vRotationSpeed = 0.10471975803375244;
  HumanAIContent_atLookAroundPattern[2].atPatternItem[0].nTimeUntilRotation = 30;
  HumanAIContent_atLookAroundPattern[2].atPatternItem[0].vRotation = 0.7853981852531433;
  HumanAIContent_atLookAroundPattern[2].atPatternItem[1].nTimeUntilRotation = 30;
  HumanAIContent_atLookAroundPattern[2].atPatternItem[1].vRotation = -0.7853981852531433;
  HumanAIContent_atLookAroundPattern[2].atPatternItem[2].nTimeUntilRotation = 30;
  HumanAIContent_atLookAroundPattern[2].atPatternItem[2].vRotation = -0.7853981852531433;
  HumanAIContent_atLookAroundPattern[2].atPatternItem[3].nTimeUntilRotation = 30;
  HumanAIContent_atLookAroundPattern[2].atPatternItem[3].vRotation = 0.7853981852531433;
  HumanAIContent_atLookAroundPattern[3].nNumItems = 4;
  HumanAIContent_atLookAroundPattern[3].vRotationSpeed = 0.05235987901687622;
  HumanAIContent_atLookAroundPattern[3].atPatternItem[0].vRotation = 1.5707963705062866;
  HumanAIContent_atLookAroundPattern[3].atPatternItem[1].vRotation = 1.5707963705062866;
  HumanAIContent_atLookAroundPattern[3].atPatternItem[2].vRotation = -1.5707963705062866;
  HumanAIContent_atLookAroundPattern[3].atPatternItem[3].vRotation = -1.5707963705062866;
  HumanAIContent_atLookAroundPattern[4].nNumItems = 4;
  HumanAIContent_atLookAroundPattern[4].vRotationSpeed = 0.05235987901687622;
  HumanAIContent_atLookAroundPattern[4].atPatternItem[0].vRotation = 1.5707963705062866;
  HumanAIContent_atLookAroundPattern[4].atPatternItem[1].vRotation = 1.5707963705062866;
  HumanAIContent_atLookAroundPattern[4].atPatternItem[2].vRotation = 1.5707963705062866;
  HumanAIContent_atLookAroundPattern[4].atPatternItem[3].vRotation = 1.5707963705062866;
  HumanAIContent_atLookAroundPattern[5].nNumItems = 4;
  HumanAIContent_atLookAroundPattern[5].vRotationSpeed = 0.15707963705062866;
  HumanAIContent_atLookAroundPattern[5].atPatternItem[0].nTimeUntilRotation = 15;
  HumanAIContent_atLookAroundPattern[5].atPatternItem[0].vRotation = 1.5707963705062866;
  HumanAIContent_atLookAroundPattern[5].atPatternItem[1].nTimeUntilRotation = 15;
  HumanAIContent_atLookAroundPattern[5].atPatternItem[1].vRotation = 1.5707963705062866;
  HumanAIContent_atLookAroundPattern[5].atPatternItem[2].nTimeUntilRotation = 15;
  HumanAIContent_atLookAroundPattern[5].atPatternItem[2].vRotation = 1.5707963705062866;
  HumanAIContent_atLookAroundPattern[5].atPatternItem[3].nTimeUntilRotation = 15;
  HumanAIContent_atLookAroundPattern[5].atPatternItem[3].vRotation = 1.5707963705062866;
}

// source: j/0/humanai/humanaicontent.c:523  [anchor-callee]
void __cdecl HumanAIContent_InitFire(struct HumanAI_s *ptHumanAI, char isFirstFire)
{
  int v3; // ecx
  struct QTask_s *ptParent; // eax
  _DWORD *pxObject; // eax
  struct Weapon_s *ptNext; // eax
  struct WeaponTypeItem_s *ptActiveWeapon; // ecx
  struct WeaponType_s *ptWeaponType; // esi
  struct WeaponGetFireTypeAmmoContext_s tAmmoContext; // [esp+Ch] [ebp-14h] BYREF
  struct HumanAI_s *ptHumanAIa = *(struct HumanAI_s * *)&ptHumanAI; // [esp+24h] [ebp+4h] ARGSLOT

  v3 = HumanAIContent_apnStateList[LODWORD(ptHumanAI->vHearingRangeFactor)][5];
  ptParent = ptHumanAI->tQTask.ptParent;
  ptHumanAIa = (struct HumanAI_s *)ptParent;
  if ( v3 == -1 || ptParent[31].ptPrev != (struct QTask_s *)v3 )
  {
    ptNext = (struct Weapon_s *)ptParent[33].ptNext;
  }
  else
  {
    pxObject = ptParent[46].tQTaskRefList.ptHead->pxObject;
    qmemcpy(&ptHumanAI->tView.tViewOrientation, pxObject + 104, sizeof(ptHumanAI->tView.tViewOrientation));
    qmemcpy(&ptHumanAI->tView.tViewPosition, pxObject + 98, sizeof(ptHumanAI->tView.tViewPosition));
    ptNext = (struct Weapon_s *)pxObject[149];
  }
  if ( ptNext )
  {
    ptActiveWeapon = ptNext->tPrivate.ptActiveWeapon;
    if ( ptActiveWeapon )
    {
      ptWeaponType = ptActiveWeapon->ptWeaponType;
      if ( ptWeaponType )
      {
        Weapon_GetFireTypeAmmoInfoFromWeaponTypeItem(ptNext, ptActiveWeapon, 0, &tAmmoContext);
        if ( ptWeaponType->eWeaponType == WEAPONTYPE_GRENADE )
          ptHumanAIa->atEvents[9].tNode.ptPrev = (struct Node_s *)1065353216;
        qmemcpy(&ptHumanAI->tCommon.tTargetPosition.vZ, &ptHumanAI[1], 0x18u);
      }
    }
  }
}

// source: j/0/humanai/humanaicontent.c:601  [anchor-caller]
char __cdecl HumanAIContent_RunFire(struct HumanAI_s *ptHumanAI)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s *tReal32x3; };
    struct { float tReal32x3a; };
    struct { char igi2_o2[4]; float tReal32x3_4; };
    struct { char igi2_o3[12]; struct WeaponGetFireTypeAmmoContext_s tAmmoContext; };
    char igi2_extent[32];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // ecx
  struct QTask_s *ptParent; // eax
  _DWORD *pxObject; // eax
  struct Weapon_s *ptNext; // eax
  struct WeaponTypeItem_s *ptActiveWeapon; // ecx
  struct QTask_s *v7; // edi
  struct QTask_s *GunShotQTask; // eax
  double v9; // st3
  struct QTask_s *TargetQTask; // eax
  struct AIDetectionListItem_s *MatchingListItem; // eax
  double v12; // st7
  double v13; // st7
  struct HumanAI_s *ptHumanAIa = *(struct HumanAI_s * *)&ptHumanAI; // [esp+30h] [ebp+4h] ARGSLOT
  float ptHumanAIb = *(float *)&ptHumanAI; // [esp+30h] [ebp+4h] ARGSLOT
  float ptHumanAIc = *(float *)&ptHumanAI; // [esp+30h] [ebp+4h] ARGSLOT

  v2 = HumanAIContent_apnStateList[LODWORD(ptHumanAI->vHearingRangeFactor)][5];
  ptParent = ptHumanAI->tQTask.ptParent;
  igi2_frame.tReal32x3 = ptParent;
  if ( v2 == -1 || ptParent[31].ptPrev != (struct QTask_s *)v2 )
  {
    ptNext = (struct Weapon_s *)ptParent[33].ptNext;
  }
  else
  {
    pxObject = ptParent[46].tQTaskRefList.ptHead->pxObject;
    qmemcpy(&ptHumanAI->tView.tViewOrientation, pxObject + 104, sizeof(ptHumanAI->tView.tViewOrientation));
    qmemcpy(&ptHumanAI->tView.tViewPosition, pxObject + 98, sizeof(ptHumanAI->tView.tViewPosition));
    ptNext = (struct Weapon_s *)pxObject[149];
  }
  if ( !ptNext )
    return 1;
  ptActiveWeapon = ptNext->tPrivate.ptActiveWeapon;
  if ( !ptActiveWeapon )
    return 1;
  ptHumanAIa = (struct HumanAI_s *)ptActiveWeapon->ptWeaponType;
  if ( !ptHumanAIa )
    return 1;
  qmemcpy(&ptHumanAI->tCommon.tTargetPosition.vZ, &ptHumanAI[1], 0x18u);
  Weapon_GetFireTypeAmmoInfoFromWeaponTypeItem(ptNext, ptNext->tPrivate.ptActiveWeapon, 0, &igi2_frame.tAmmoContext);
  if ( LODWORD(ptHumanAIa->atEvents[1].tDirection.vY) > 2 )
    return 1;
  HumanAIContent_SetChannel(ptHumanAI, 5, 1.0);
  if ( HumanAI_FacePositionSelectSpeed(
         ptHumanAI,
         (struct real64x3_t *)&ptHumanAI->tCommon.tTargetPosition.vZ,
         1.2217304706573486,
         true) )
  {
    v7 = igi2_frame.tReal32x3;
    GunShotQTask = Weapon_GetGunShotQTask(igi2_frame.tReal32x3[33].ptNext);
    igi2_frame.tReal32x3a = ptHumanAI->tCommon.tTargetPosition.vZ - *(double *)&igi2_frame.tReal32x3[1].ptNext;
    igi2_frame.tReal32x3_4 = *(double *)&ptHumanAI->tCommon.tOriginalViewDirection.vX - *(double *)&v7[1].tQTaskChildren.ptHead;
    v9 = *(double *)&ptHumanAI->tCommon.tOriginalViewDirection.vZ - *(double *)&v7[1].tQTaskChildren.ptTail;
    ptHumanAIb = sqrt(igi2_frame.tReal32x3a * igi2_frame.tReal32x3a + igi2_frame.tReal32x3_4 * igi2_frame.tReal32x3_4 + v9 * v9);
    if ( GunShotQTask )
    {
      GunShotQTask[4].tQTaskChildren.ptMiddle = (struct QTask_s *)((int)GunShotQTask[4].tQTaskChildren.ptMiddle | 3);
      *(float *)&GunShotQTask[4].ptNext = ptHumanAIb * 0.000244140625 + 5.0;
    }
    ptHumanAIc = HumanAIConfig_CalculateAccuracy(
                   ptHumanAI->tTweakParameters.vGrenadeThrowProb,
                   ptHumanAI->tTweakParameters.vGrenadeDetonationTimer,
                   ptHumanAI->tTweakParameters.vCloseCombatDamage,
                   ptHumanAI->tTweakParameters.vHitPoints,
                   ptHumanAI->tTweakParameters.vHitRecoilThreshold,
                   ptHumanAI->tTweakParameters.vCombatViewCone1Alpha,
                   ptHumanAIb);
    TargetQTask = HumanAI_GetTargetQTask(ptHumanAI, true);
    if ( TargetQTask
      && (MatchingListItem = AIDetection_FindMatchingListItem(
                               (struct AIDetection_s *)&ptHumanAI->tAIDetection.tFriendList,
                               TargetQTask)) != nullptr )
    {
      v12 = (double)(LevelFlow_ptLevelFlow->nTick - MatchingListItem->nBecameVisibleTick);
      if ( v12 >= 240.0 )
        v12 = 240.0;
      v13 = ((double)(int)(__int64)v12 * 0.004166666883975267 + 1.0) * ptHumanAIc;
    }
    else
    {
      v13 = ptHumanAIc;
    }
    if ( v13 >= 0.0 )
    {
      if ( v13 > 1.0 )
        v13 = 1.0;
    }
    else
    {
      v13 = 0.0;
    }
    *(float *)&v7[33].ptNext[2].tQTaskRefList.ptHead = v13;
    ptHumanAI->avChannel[16] = 1.0;
    return 1;
  }
  return 0;
}

// source: j/0/humanai/humanaicontent.c:754  [anchor-mhash]
void __cdecl HumanAIContent_DelayedEventPassOnInitCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  union __anon_1ce5 *p_uContext; // esi
  struct real64x3_t *p_tPosition; // ecx
  int DelayFromDetectionTimeDistanceFactor; // eax
  double v5; // st7

  p_uContext = &ptActionStackItem->ptContext->uContext;
  p_tPosition = &ptActionStackItem->ptContext->uContext.tRunToCoverContext.tPosition;
  ptActionStackItem->pfRunCallback = HumanAIContent_DelayedEventPassOnRunCB;
  ptActionStackItem->pfDeleteCallback = HumanAIContent_DelayedEventPassOnDeleteCB;
  DelayFromDetectionTimeDistanceFactor = HumanAI_GetDelayFromDetectionTimeDistanceFactor(ptHumanAI, p_tPosition);
  v5 = (double)(10 * DelayFromDetectionTimeDistanceFactor);
  p_uContext->tIdleContext.nTicksUsed = 10 * DelayFromDetectionTimeDistanceFactor;
  if ( v5 >= 9.0 )
  {
    if ( v5 > 45.0 )
      v5 = 45.0;
    p_uContext->tIdleContext.nTicksUsed = (__int64)v5;
  }
  else
  {
    p_uContext->tIdleContext.nTicksUsed = (__int64)9.0;
  }
}

// source: j/0/humanai/humanaicontent.c:779  [anchor-mhash]
void __cdecl HumanAIContent_DelayedEventPassOnRunCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  struct HumanAIActionContext_t *ptContext; // esi
  int nTicksUsed; // eax
  union __anon_1ce5 *p_uContext; // esi
  void (__cdecl *pfDeleteCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // eax
  struct HumanAIActionContext_t *v6; // eax

  ptContext = ptActionStackItem->ptContext;
  nTicksUsed = ptContext->uContext.tIdleContext.nTicksUsed;
  p_uContext = &ptContext->uContext;
  if ( !nTicksUsed || HumanAI_GetTargetQTask(ptHumanAI, true) )
  {
    pfDeleteCallback = ptActionStackItem->pfDeleteCallback;
    if ( pfDeleteCallback )
      pfDeleteCallback(ptHumanAI, ptActionStackItem);
    Node_Remove(ptActionStackItem);
    v6 = ptActionStackItem->ptContext;
    ptActionStackItem->isUsed = 0;
    if ( v6 )
    {
      v6->tNode.ptPrev = nullptr;
      v6->tNode.ptNext = nullptr;
      List_AddTail(v6, (int)&ptHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID);
      ptActionStackItem->ptContext = nullptr;
    }
  }
  else
  {
    HumanAI_FacePositionSelectSpeed(ptHumanAI, &p_uContext->tRunToCoverContext.tPosition, 0.0872664675116539, false);
    --p_uContext->tIdleContext.nTicksUsed;
  }
}

// source: j/0/humanai/humanaicontent.c:808  [anchor-mhash]
void __cdecl HumanAIContent_DelayedEventPassOnDeleteCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s *v12; };
    struct { char igi2_o1[4]; struct AISquadEventContext_s ptQTask; };
    char igi2_extent[116];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  union __anon_1ce5 *p_uContext; // ebx
  struct QTask_s *ptParent; // edx
  struct QReference_s *v4; // eax
  int nAnimationMinimumDelay; // ecx
  int nTimer; // edx
  int v7; // edi
  int v8; // eax
  int *v9; // esi
  float v10; // edx
  float v11; // eax

  p_uContext = &ptActionStackItem->ptContext->uContext;
  if ( !HIBYTE(ptHumanAI->avChannel[5]) )
  {
    ptParent = ptHumanAI->tQTask.ptParent->ptParent;
    memset(&igi2_frame.ptQTask, 0, sizeof(igi2_frame.ptQTask));
    igi2_frame.v12 = ptParent;
    v4 = QTask_NewQTaskRef(&ptHumanAI->tQTask);
    nAnimationMinimumDelay = ptHumanAI->nAnimationMinimumDelay;
    nTimer = p_uContext->tWaitContext.nTimer;
    igi2_frame.ptQTask.aptSquadMemberQTaskRef[0] = v4;
    v7 = -1;
    v8 = 0;
    igi2_frame.ptQTask.eEvent = nTimer;
    igi2_frame.ptQTask.nNumSquadMemberQTaskRefs = 1;
    if ( nAnimationMinimumDelay > 0 )
    {
      v9 = &ptHumanAI->anEventPriorityList[6];
      while ( *v9 != nTimer )
      {
        ++v8;
        ++v9;
        if ( v8 >= nAnimationMinimumDelay )
          goto LABEL_8;
      }
      v7 = v8;
    }
LABEL_8:
    v10 = *(float *)&p_uContext->tRunPanickingEventContext.nTimer;
    v11 = *(float *)&p_uContext->tHoldAreaContext.nGraphId;
    LODWORD(igi2_frame.ptQTask.tDirection.vX) = p_uContext->tLookInApproxDirectionContext.nSectorResolution;
    igi2_frame.ptQTask.nPriority = v7;
    igi2_frame.ptQTask.tDirection.vZ = v11;
    igi2_frame.ptQTask.ptReferenceQTaskRef = nullptr;
    igi2_frame.ptQTask.tDirection.vY = v10;
    qmemcpy(&igi2_frame.ptQTask.tPosition, &p_uContext->tPatrolContext.nTimer, sizeof(igi2_frame.ptQTask.tPosition));
    AISquad_ReceiveEvent(igi2_frame.v12, &igi2_frame.ptQTask);
    QReference_Delete(igi2_frame.ptQTask.aptSquadMemberQTaskRef[0], &QTask_tQTaskRefPool);
  }
}

// source: j/0/humanai/humanaicontent.c:846  [size]
void __cdecl HumanAIContent_DeadInitCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  ptActionStackItem->pfRunCallback = HumanAIContent_DeadRunCB;
}

// source: j/0/humanai/humanaicontent.c:859  [size]
void __cdecl HumanAIContent_DeadRunCB(struct HumanAI_s *ptHumanAI, struct HumanAIActionStackItem_s *ptActionStackItem)
{
  HumanAI_LevelSight(ptHumanAI);
}

// source: j/0/humanai/humanaicontent.c:876  [size]
void __cdecl HumanAIContent_CombatStationaryGunInitCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  ptActionStackItem->pfRunCallback = HumanAIContent_CombatStationaryGunRunCB;
  ptActionStackItem->pfRunInitCallback = (void (__cdecl *)(struct HumanAI_s *, struct HumanAIActionStackItem_s *))HumanAIContent_CombatStationaryGunInitCB;
  ptActionStackItem->pfDeleteCallback = HumanAIContent_CombatStationaryGunDeleteCB;
  ptActionStackItem->ptContext->uContext.tLookAtPositionContext.nTimer = 0;
}

// source: j/0/humanai/humanaicontent.c:900  [anchor-caller]
void __cdecl HumanAIContent_CombatStationaryGunRunCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  struct QTask_s *ptParent; // ebx
  struct QReference_s *ptHead; // eax
  union __anon_1ce5 *p_uContext; // ebp
  void (__cdecl *pfDeleteCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // eax
  struct HumanAIActionContext_t *ptContext; // eax
  struct QTask_s *pxObject; // eax
  _BYTE *v8; // eax
  enum bool (__cdecl *pfChildRunCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // eax

  ptParent = ptHumanAI->tQTask.ptParent;
  ptHead = ptParent[46].tQTaskRefList.ptHead;
  p_uContext = &ptActionStackItem->ptContext->uContext;
  if ( ptHead )
  {
    if ( ptHumanAI->nAnimationEntries == -1 )
    {
      pxObject = (struct QTask_s *)ptHead->pxObject;
      if ( pxObject )
        ptHumanAI->nAnimationEntries = Level_GetLevelQTaskIDFromQTask(pxObject);
    }
    v8 = ptParent[46].tQTaskRefList.ptHead->pxObject;
    if ( v8 && ((v8[588] & 3) != 0 || (double)p_uContext->tLookAtPositionContext.nTimer > 150.0) )
    {
      HumanAI_PopActionStackItem(ptHumanAI, ptActionStackItem);
    }
    else
    {
      if ( HumanAI_GetTargetQTask(ptHumanAI, true) )
        p_uContext->tLookAtPositionContext.nTimer = 0;
      else
        ++p_uContext->tLookAtPositionContext.nTimer;
      pfChildRunCallback = ptActionStackItem->pfChildRunCallback;
      if ( pfChildRunCallback )
      {
        if ( pfChildRunCallback(ptHumanAI, ptActionStackItem) )
          ptActionStackItem->pfChildRunCallback = nullptr;
      }
      else if ( HumanAIContent_IsState(ptHumanAI, 5) == false && HumanAIContent_IsState(ptHumanAI, 4) )
      {
        HumanAIContent_SetChannel(ptHumanAI, 3, -1.0);
      }
    }
  }
  else
  {
    pfDeleteCallback = ptActionStackItem->pfDeleteCallback;
    if ( pfDeleteCallback )
      pfDeleteCallback(ptHumanAI, ptActionStackItem);
    Node_Remove(ptActionStackItem);
    ptContext = ptActionStackItem->ptContext;
    ptActionStackItem->isUsed = 0;
    if ( ptContext )
    {
      ptContext->tNode.ptPrev = nullptr;
      ptContext->tNode.ptNext = nullptr;
      List_AddTail(ptContext, (int)&ptHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID);
      ptActionStackItem->ptContext = nullptr;
    }
  }
}

// source: j/0/humanai/humanaicontent.c:989  [anchor-mhash]
void __cdecl HumanAIContent_CombatStationaryGunDeleteCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  struct QTask_s *ptParent; // ebx
  int v3; // eax
  _DWORD *pxObject; // eax
  int v5; // eax

  ptParent = ptHumanAI->tQTask.ptParent;
  if ( ptParent[46].tQTaskRefList.ptHead )
  {
    v3 = HumanAIContent_apnStateList[LODWORD(ptHumanAI->vHearingRangeFactor)][5];
    if ( v3 != -1 && ptParent[31].ptPrev == (struct QTask_s *)v3 )
      HumanAIContent_SetChannel(ptHumanAI, 3, 1.0);
    pxObject = ptParent[46].tQTaskRefList.ptHead->pxObject;
    if ( pxObject )
    {
      v5 = pxObject[149];
      *(_DWORD *)(v5 + 112) = 1;
      *(_DWORD *)(v5 + 56) = 0;
    }
  }
  ptHumanAI->nAnimationEntries = -1;
}

// source: j/0/humanai/humanaicontent.c:1024  [anchor-hash]
char __cdecl HumanAIContent_CombatStandFireRunCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{

  HumanAI_GetTargetPosition((struct real64x3_t *)&ptHumanAI[1], ptHumanAI);
  return HumanAIContent_RunFire(ptHumanAI) != 0;
}

// source: j/0/humanai/humanaicontent.c:1047  [anchor-mhash]
char __cdecl HumanAIContent_CombatStandCloseCombatRunCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  struct QTask_s *v2; // eax

  HumanAIContent_SetChannel(ptHumanAI, 8, 1.0);
  v2 = (struct QTask_s *)*HumanAIContent_apnStateList[LODWORD(ptHumanAI->vHearingRangeFactor)];
  return v2 == (struct QTask_s *)-1 || ptHumanAI->tQTask.ptParent[31].ptPrev != v2;
}

// source: j/0/humanai/humanaicontent.c:1074  [size]
void __cdecl HumanAIContent_PlayAnimationInitCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  struct QTask_s *ptParent; // ecx
  struct HumanAIActionContext_t *ptContext; // edx

  ptParent = ptHumanAI->tQTask.ptParent;
  ptContext = ptActionStackItem->ptContext;
  ptActionStackItem->pfRunCallback = HumanAIContent_PlayAnimationRunCB;
  ptContext->uContext.tPlayAnimationContext.isAnimationPlayed = 0;
  BYTE1(ptParent[75].ptPrev) = ptActionStackItem->ptContext->uContext.tPlayAnimationContext.isLoop;
}

// source: j/0/humanai/humanaicontent.c:1095  [anchor-mhash]
void __cdecl HumanAIContent_PlayAnimationRunCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  int *v2; // ecx
  struct QTask_s *v3; // eax
  struct QTask_s *v4; // ecx

  v2 = HumanAIContent_apnStateList[LODWORD(ptHumanAI->vHearingRangeFactor)];
  v3 = (struct QTask_s *)v2[4];
  if ( v3 == (struct QTask_s *)-1 || ptHumanAI->tQTask.ptParent[31].ptPrev != v3 )
  {
    if ( ptActionStackItem->ptContext->uContext.tPlayAnimationContext.isAnimationPlayed )
    {
      HumanAI_PopActionStackItem(ptHumanAI, ptActionStackItem);
    }
    else
    {
      v4 = (struct QTask_s *)*v2;
      if ( v4 != (struct QTask_s *)-1 && ptHumanAI->tQTask.ptParent[31].ptPrev == v4 )
      {
        HumanAIContent_SetChannel(ptHumanAI, 3, 1.0);
        ptActionStackItem->ptContext->uContext.tPlayAnimationContext.isAnimationPlayed = 1;
      }
    }
  }
}

// source: j/0/humanai/humanaicontent.c:1143  [size]
void __cdecl HumanAIContent_PlaySoundInitCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  ptActionStackItem->pfRunCallback = HumanAIContent_PlaySoundRunCB;
}

// source: j/0/humanai/humanaicontent.c:1158  [anchor-mhash]
void __cdecl HumanAIContent_PlaySoundRunCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  struct HumanAIActionContext_t *ptContext; // eax
  char isFirstFire; // cl
  char *p_uContext; // eax
  struct QTask_s *v5; // eax
  void (__cdecl *pfDeleteCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // eax
  struct HumanAIActionContext_t *v7; // eax

  ptContext = ptActionStackItem->ptContext;
  isFirstFire = ptContext->uContext.tCombatContext.isFirstFire;
  p_uContext = (char *)&ptContext->uContext;
  if ( isFirstFire )
  {
    SoundSys_NewSoundFn(ptHumanAI->tQTask.ptParent, p_uContext);
  }
  else
  {
    v5 = SoundSys_NewSoundFn(Level_ptDynamicQTask, p_uContext);
    if ( v5 )
      ((void (__cdecl *)(struct QTask_s *, struct HumanAIView_s *))QTask_aatQTaskFinalEvent[SoundSys_eSetPositionQTaskEvent][v5->eQTaskType].pfHandler)(
        v5,
        &ptHumanAI->tView);
  }
  pfDeleteCallback = ptActionStackItem->pfDeleteCallback;
  if ( pfDeleteCallback )
    pfDeleteCallback(ptHumanAI, ptActionStackItem);
  Node_Remove(ptActionStackItem);
  v7 = ptActionStackItem->ptContext;
  ptActionStackItem->isUsed = 0;
  if ( v7 )
  {
    v7->tNode.ptPrev = nullptr;
    v7->tNode.ptNext = nullptr;
    List_AddTail(v7, (int)&ptHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID);
    ptActionStackItem->ptContext = nullptr;
  }
}

// source: j/0/humanai/humanaicontent.c:1194  [anchor-mhash]
void __cdecl HumanAIContent_MoveToEventInitCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  struct real64x3_t *ptContext; // esi

  ptContext = (struct real64x3_t *)ptActionStackItem->ptContext;
  ptActionStackItem->pfRunCallback = HumanAIContent_MoveToEventRunCB;
  ptContext = (struct real64x3_t *)((char *)ptContext + 8);
  AIGraph_GetClosestNode(
    (struct AIGraphNode_s **)&ptActionStackItem,
    *(struct AIGraph_t **)&ptHumanAI->zScriptFile[36],
    ptContext,
    false);
  LODWORD(ptContext[1].vX) = ptActionStackItem->tNode.ptNext;
}

// source: j/0/humanai/humanaicontent.c:1218  [anchor-mhash]
void __cdecl HumanAIContent_MoveToEventRunCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  struct HumanAIActionContext_t *ptContext; // ebx
  char v3; // al
  union __anon_1ce5 *p_uContext; // ebx
  bool v6; // zf
  struct QTask_s *ptParent; // eax
  unsigned __int16 eQTaskType; // cx
  float v9; // edx
  int nTimer; // ebx
  void (__cdecl *pfDeleteCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // eax
  struct HumanAIActionContext_t *v12; // eax
  int ptHumanAIa = *(int *)&ptHumanAI; // [esp+14h] [ebp+4h] ARGSLOT
  int ptHumanAIb = *(int *)&ptHumanAI; // [esp+14h] [ebp+4h] ARGSLOT

  ptContext = ptActionStackItem->ptContext;
  v3 = ptContext->uContext.tPlaySoundContext.zSoundDef[28];
  p_uContext = &ptContext->uContext;
  v6 = v3 == 0;
  ptParent = ptHumanAI->tQTask.ptParent;
  eQTaskType = ptParent->eQTaskType;
  if ( v6 )
  {
    if ( eQTaskType != HumanSoldier_eQTaskType )
      goto LABEL_11;
    ptHumanAIb = 0;
    if ( !LOBYTE(ptParent[75].ptPrev) )
      ptHumanAIb = 1065353216;
    v9 = *(float *)&ptHumanAIb;
  }
  else
  {
    if ( eQTaskType != HumanSoldier_eQTaskType )
      goto LABEL_11;
    ptHumanAIa = 1065353216;
    if ( !LOBYTE(ptParent[75].ptPrev) )
      ptHumanAIa = 0;
    v9 = *(float *)&ptHumanAIa;
  }
  HumanAIContent_SetChannel(ptHumanAI, 0, v9);
LABEL_11:
  nTimer = p_uContext->tLookAtPositionContext.nTimer;
  ptHumanAI->avChannel[8] = 0.3141592741012573;
  ptHumanAI->avChannel[9] = 0.3141592741012573;
  if ( HumanAI_MoveCharacterToNode(ptHumanAI, nTimer) )
  {
    pfDeleteCallback = ptActionStackItem->pfDeleteCallback;
    if ( pfDeleteCallback )
      pfDeleteCallback(ptHumanAI, ptActionStackItem);
    Node_Remove(ptActionStackItem);
    v12 = ptActionStackItem->ptContext;
    ptActionStackItem->isUsed = 0;
    if ( v12 )
    {
      v12->tNode.ptPrev = nullptr;
      v12->tNode.ptNext = nullptr;
      List_AddTail(v12, (int)&ptHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID);
      ptActionStackItem->ptContext = nullptr;
    }
  }
}

// source: j/0/humanai/humanaicontent.c:1249  [size]
void __cdecl HumanAIContent_LookAtEventInitCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  ptActionStackItem->pfRunCallback = HumanAIContent_LookAtEventRunCB;
  ptActionStackItem->ptContext->uContext.tLookInApproxDirectionContext.nStartTime = -1;
}

// source: j/0/humanai/humanaicontent.c:1267  [anchor-mhash]
void __cdecl HumanAIContent_LookAtEventRunCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s *TargetQTask; };
    struct { char igi2_o1[8]; struct HumanAIEventContext_t ptQTask; };
    char igi2_extent[72];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  union __anon_1ce5 *p_uContext; // ebx
  struct HumanAI_s *v3; // edi
  struct QTask_s *v4; // esi
  struct AIDetectionListItem_s *MatchingListItem; // eax
  int nStartTime; // eax
  void (__cdecl *pfDeleteCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // eax
  struct HumanAIActionContext_t *ptContext; // eax

  p_uContext = &ptActionStackItem->ptContext->uContext;
  igi2_frame.TargetQTask = HumanAI_GetTargetQTask(ptHumanAI, true);
  if ( igi2_frame.TargetQTask )
  {
    HumanAIContent_SetChannel(ptHumanAI, 5, 1.0);
    qmemcpy(p_uContext, &igi2_frame.TargetQTask[1], 0x18u);
    v3 = ptHumanAI;
    v4 = igi2_frame.TargetQTask;
    MatchingListItem = AIDetection_FindMatchingListItem(
                         (struct AIDetection_s *)&ptHumanAI->tAIDetection.tFriendList,
                         igi2_frame.TargetQTask);
    if ( !MatchingListItem || !MatchingListItem->isIdentifying )
      goto LABEL_5;
  }
  else
  {
    HumanAIContent_SetChannel(ptHumanAI, 5, 1.0);
    qmemcpy(&ptHumanAI->tCommon.nIgnoreVisibilityFactorTimer, p_uContext, 0x18u);
    qmemcpy(&ptHumanAI[1], p_uContext, 0x18u);
    v3 = ptHumanAI;
  }
  v4 = nullptr;
LABEL_5:
  if ( (v3->anEventPriorityList[5] & 4) != 0 )
  {
    v3->avChannel[8] = 0.41887903213500977;
    v3->avChannel[9] = 0.20943951606750488;
  }
  else
  {
    v3->avChannel[8] = 0.20943951606750488;
    v3->avChannel[9] = 0.10471975803375244;
  }
  if ( HumanAI_FacePosition(v3, (struct real64x3_t *)p_uContext, 0.03490658476948738, false) || v4 )
  {
    if ( p_uContext->tLookInApproxDirectionContext.nStartTime < 0 )
      p_uContext->tLookInApproxDirectionContext.nStartTime = (__int64)(p_uContext->tLookAtEventContext.vSecondsToLook
                                                                     * 30.0);
    nStartTime = p_uContext->tLookInApproxDirectionContext.nStartTime;
    if ( nStartTime )
    {
      if ( !v4 )
      {
        p_uContext->tLookInApproxDirectionContext.nStartTime = nStartTime - 1;
        return;
      }
    }
    else if ( !v4 )
    {
      igi2_frame.ptQTask.eEvent = 40;
      igi2_frame.ptQTask.bFlags = 0;
      igi2_frame.ptQTask.ptHumanOriginatorQTask = nullptr;
      igi2_frame.ptQTask.ptPosition = nullptr;
      igi2_frame.ptQTask.ptReferenceQTask = nullptr;
      HumanAI_SendEventSpecificQTask(&v3->tQTask, &igi2_frame.ptQTask);
    }
    pfDeleteCallback = ptActionStackItem->pfDeleteCallback;
    if ( pfDeleteCallback )
      pfDeleteCallback(v3, ptActionStackItem);
    Node_Remove(ptActionStackItem);
    ptContext = ptActionStackItem->ptContext;
    ptActionStackItem->isUsed = 0;
    if ( ptContext )
    {
      ptContext->tNode.ptPrev = nullptr;
      ptContext->tNode.ptNext = nullptr;
      List_AddTail(ptContext, (int)&v3->atPatrolPathStackItems[0].nLastEndCommandQTaskID);
      ptActionStackItem->ptContext = nullptr;
    }
  }
}

// source: j/0/humanai/humanaicontent.c:1344  [size]
void __cdecl HumanAIContent_StunnedInitCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  ptActionStackItem->pfRunCallback = HumanAIContent_StunnedRunCB;
  ptActionStackItem->ptContext->uContext.tIdleContext.nTicksUsed = -1;
}

// source: j/0/humanai/humanaicontent.c:1362  [anchor-mhash]
void __cdecl HumanAIContent_StunnedRunCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  struct HumanAIActionContext_t *ptContext; // eax
  int nTicksUsed; // ecx
  union __anon_1ce5 *p_uContext; // eax
  bool v5; // sf
  struct LevelFlow_s *v6; // ecx
  void (__cdecl *pfDeleteCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // eax
  struct HumanAIActionContext_t *v8; // eax
  struct QTask_s *v9; // eax

  ptContext = ptActionStackItem->ptContext;
  nTicksUsed = ptContext->uContext.tIdleContext.nTicksUsed;
  p_uContext = &ptContext->uContext;
  v5 = nTicksUsed < 0;
  v6 = LevelFlow_ptLevelFlow;
  if ( v5 )
    p_uContext->tIdleContext.nTicksUsed = LevelFlow_ptLevelFlow->nTick
                                        - (__int64)(p_uContext->tLookAroundContext.vCurrentRotation * -30.0);
  if ( v6->nTick <= p_uContext->tIdleContext.nTicksUsed )
  {
    v9 = (struct QTask_s *)HumanAIContent_apnStateList[LODWORD(ptHumanAI->vHearingRangeFactor)][4];
    if ( v9 == (struct QTask_s *)-1 || ptHumanAI->tQTask.ptParent[31].ptPrev != v9 )
      HumanAIContent_SetChannel(ptHumanAI, 3, 1.0);
  }
  else
  {
    pfDeleteCallback = ptActionStackItem->pfDeleteCallback;
    if ( pfDeleteCallback )
      pfDeleteCallback(ptHumanAI, ptActionStackItem);
    Node_Remove(ptActionStackItem);
    v8 = ptActionStackItem->ptContext;
    ptActionStackItem->isUsed = 0;
    if ( v8 )
    {
      v8->tNode.ptPrev = nullptr;
      v8->tNode.ptNext = nullptr;
      List_AddTail(v8, (int)&ptHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID);
      ptActionStackItem->ptContext = nullptr;
    }
  }
}

// source: j/0/humanai/humanaicontent.c:1395  [anchor-mhash]
void __cdecl HumanAIContent_KickGrenadeInitCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  struct HumanAIActionStackItem_s *v2; // eax
  struct HumanAIActionContext_t *ptContext; // esi

  v2 = ptActionStackItem;
  ptContext = ptActionStackItem->ptContext;
  ptActionStackItem->pfRunCallback = (void (__cdecl *)(struct HumanAI_s *, struct HumanAIActionStackItem_s *))HumanAIContent_KickGrenadeRunCB;
  v2->pfDeleteCallback = HumanAIContent_KickGrenadeDeleteCB;
  ptContext = (struct HumanAIActionContext_t *)((char *)ptContext + 8);
  AIGraph_GetClosestNode(
    (struct AIGraphNode_s **)&ptActionStackItem,
    *(struct AIGraph_t **)&ptHumanAI->zScriptFile[36],
    (struct real64x3_t *)ptContext,
    false);
  ptContext->uContext.tCombatContext.nFireSequences = (int)ptActionStackItem->tNode.ptNext;
  ptContext->uContext.tPlaySoundContext.zSoundDef[20] = 0;
}

// source: j/0/humanai/humanaicontent.c:1423  [anchor-mhash]
void __cdecl HumanAIContent_KickGrenadeDeleteCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  struct QReference_s *ptGrenadeQTaskRef; // eax

  ptGrenadeQTaskRef = ptActionStackItem->ptContext->uContext.tKickGrenadeEventContext.ptGrenadeQTaskRef;
  if ( ptGrenadeQTaskRef )
    QReference_Delete(ptGrenadeQTaskRef, &QTask_tQTaskRefPool);
}

// source: j/0/humanai/humanaicontent.c:1443  [size]
void __cdecl HumanAIContent_KickGrenadeRunCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  ;
}

// source: j/0/humanai/humanaicontent.c:1486  [anchor-mhash]
void __cdecl HumanAIContent_RunPanickingInitCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v18; };
    struct { char igi2_o1[4]; struct AIGraphNode_s *pptAIGraphNode; };
    struct { char igi2_o2[12]; float v20; };
    struct { char igi2_o3[16]; float v21; };
    struct { char igi2_o4[20]; struct real64x3_t ptPosition; };
    char igi2_extent[44];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct HumanAIActionContext_t *ptContext; // esi
  struct QTask_s *ptParent; // ecx
  struct QTask_s *v4; // edx
  double vX; // st7
  union __anon_1ce5 *p_uContext; // esi
  double v7; // st7
  double v8; // st6
  double v9; // st5
  void (__cdecl *pfDeleteCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // eax
  struct HumanAIActionContext_t *v11; // eax
  double v12; // st7
  double v13; // st6
  long double v14; // st3
  double v15; // st7
  double v16; // st6
  struct AIGraph_t *v17; // ebx

  ptContext = ptActionStackItem->ptContext;
  ptParent = ptHumanAI->tQTask.ptParent;
  v4 = ptParent->ptParent;
  ptActionStackItem->pfRunCallback = HumanAIContent_RunPanickingRunCB;
  vX = ptContext->uContext.tLookAtPositionContext.tPosition.vX;
  p_uContext = &ptContext->uContext;
  p_uContext->tRunPanickingEventContext.nTimer = 0;
  p_uContext->tLookInApproxDirectionContext.nSectorResolution = -1;
  v7 = vX - ptHumanAI->tView.tPosition.vX;
  v8 = p_uContext->tRunToCoverContext.tPosition.vX;
  igi2_frame.pptAIGraphNode = nullptr;
  v9 = p_uContext->tRunToCoverContext.tPosition.vY - ptHumanAI->tView.tPosition.vZ;
  if ( sqrt(v9 * v9 + (v8 - ptHumanAI->tView.tPosition.vY) * (v8 - ptHumanAI->tView.tPosition.vY) + v7 * v7) <= 122880.0 )
  {
    if ( v4[218].ptPrev == (struct QTask_s *)2 )
    {
      HumanAI_PopActionStackItem(ptHumanAI, ptActionStackItem);
    }
    else
    {
      v12 = *(double *)&ptParent[1].ptNext - p_uContext->tLookAtPositionContext.tPosition.vX;
      igi2_frame.v20 = *(double *)&ptParent[1].tQTaskChildren.ptHead - p_uContext->tRunToCoverContext.tPosition.vX;
      v13 = *(double *)&ptParent[1].tQTaskChildren.ptTail - p_uContext->tRunToCoverContext.tPosition.vY;
      igi2_frame.v21 = v13;
      v14 = sqrt(v12 * v12 + igi2_frame.v20 * igi2_frame.v20 + v13 * v13);
      if ( v14 <= 0.0 )
      {
        igi2_frame.v21 = 0.0;
        v15 = 122880.0;
        v16 = 0.0;
      }
      else
      {
        igi2_frame.v18 = 122880.0 / v14;
        v15 = v12 * igi2_frame.v18;
        v16 = igi2_frame.v18 * igi2_frame.v20;
        igi2_frame.v21 = igi2_frame.v18 * igi2_frame.v21;
      }
      v17 = *(struct AIGraph_t **)&ptHumanAI->zScriptFile[36];
      igi2_frame.ptPosition.vX = v15 + *(double *)&ptParent[1].ptNext;
      igi2_frame.ptPosition.vY = v16 + *(double *)&ptParent[1].tQTaskChildren.ptHead;
      igi2_frame.ptPosition.vZ = igi2_frame.v21 + *(double *)&ptParent[1].tQTaskChildren.ptTail;
      AIGraph_GetClosestNode(&igi2_frame.pptAIGraphNode, v17, &igi2_frame.ptPosition, false);
      if ( igi2_frame.pptAIGraphNode )
        p_uContext->tLookInApproxDirectionContext.nSectorResolution = igi2_frame.pptAIGraphNode->tGraphNode.nID;
      else
        HumanAI_PopActionStackItem(ptHumanAI, ptActionStackItem);
    }
  }
  else
  {
    pfDeleteCallback = ptActionStackItem->pfDeleteCallback;
    if ( pfDeleteCallback )
      pfDeleteCallback(ptHumanAI, ptActionStackItem);
    Node_Remove(ptActionStackItem);
    v11 = ptActionStackItem->ptContext;
    ptActionStackItem->isUsed = 0;
    if ( v11 )
    {
      v11->tNode.ptPrev = nullptr;
      v11->tNode.ptNext = nullptr;
      List_AddTail(v11, (int)&ptHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID);
      ptActionStackItem->ptContext = nullptr;
    }
  }
}

// source: j/0/humanai/humanaicontent.c:1541  [anchor-mhash]
void __cdecl HumanAIContent_RunPanickingRunCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  struct HumanAIActionContext_t *ptContext; // ebx
  int nTimer; // edx
  int nSectorResolution; // ecx
  union __anon_1ce5 *p_uContext; // ebx
  int v6; // edx
  void (__cdecl *pfDeleteCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // eax
  struct HumanAIActionContext_t *v8; // eax
  int v9; // [esp-4h] [ebp-10h]

  ptContext = ptActionStackItem->ptContext;
  nTimer = ptContext->uContext.tRunPanickingEventContext.nTimer;
  nSectorResolution = ptContext->uContext.tLookInApproxDirectionContext.nSectorResolution;
  p_uContext = &ptContext->uContext;
  v6 = nTimer + 1;
  p_uContext->tRunPanickingEventContext.nTimer = v6;
  if ( nSectorResolution == -1 || v6 > 150 )
  {
    pfDeleteCallback = ptActionStackItem->pfDeleteCallback;
    if ( pfDeleteCallback )
      pfDeleteCallback(ptHumanAI, ptActionStackItem);
    Node_Remove(ptActionStackItem);
    v8 = ptActionStackItem->ptContext;
    ptActionStackItem->isUsed = 0;
    if ( v8 )
    {
      v8->tNode.ptPrev = nullptr;
      v8->tNode.ptNext = nullptr;
      List_AddTail(v8, (int)&ptHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID);
      ptActionStackItem->ptContext = nullptr;
    }
  }
  else
  {
    HumanAI_MakeAIRun(ptHumanAI);
    v9 = p_uContext->tLookInApproxDirectionContext.nSectorResolution;
    ptHumanAI->avChannel[8] = 0.3141592741012573;
    ptHumanAI->avChannel[9] = 0.3141592741012573;
    if ( HumanAI_MoveCharacterToNode(ptHumanAI, v9) )
      HumanAI_PopActionStackItem(ptHumanAI, ptActionStackItem);
  }
}

// source: j/0/humanai/humanaicontent.c:1572  [anchor-mhash]
void __cdecl HumanAIContent_IdleInitCB(struct HumanAI_s *ptHumanAI, struct HumanAIActionStackItem_s *ptActionStackItem)
{
  struct Game_s *v2; // eax
  struct HumanAIActionContext_t *ptContext; // ecx
  unsigned int v4; // edi
  int v5; // edi
  unsigned int v6; // edi

  v2 = Game_ptGame;
  ptContext = ptActionStackItem->ptContext;
  v4 = (Game_ptGame->tRunRandomState.anRandom[0] >> 7) ^ Game_ptGame->tRunRandomState.anRandom[2];
  Game_ptGame->tRunRandomState.anRandom[2] = v4;
  v5 = v4 ^ v2->tRunRandomState.anRandom[1];
  v2->tRunRandomState.anRandom[1] = v5;
  v6 = v5 + v2->tRunRandomState.anRandom[0];
  v2->tRunRandomState.anRandom[0] = v6;
  ptContext = (struct HumanAIActionContext_t *)((char *)ptContext + 8);
  ptContext->tNode.ptPrev = nullptr;
  ptContext->uContext.tWaitContext.nTimer = 0;
  ptContext->tNode.ptNext = (struct Node_s *)(30 * (v6 % 0xA + 10));
  ptActionStackItem->pfRunCallback = HumanAIContent_IdleRunCB;
  LODWORD(ptHumanAI->tCommon.tAimPosition.vZ) = HIDWORD(ptHumanAI->tCommon.tAimPosition.vY);
}

// source: j/0/humanai/humanaicontent.c:1596  [anchor-caller]
void __cdecl HumanAIContent_IdleRunCB(struct HumanAI_s *ptHumanAI, struct HumanAIActionStackItem_s *ptActionStackItem)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct HumanAIIdleActionContext_s *ptContext; };
    struct { float ptContexta; };
    struct { char igi2_o2[12]; float tReal32x3_8; };
    struct { char igi2_o3[16]; struct real64x3_t tReal64x3; };
    struct { char igi2_o4[40]; int v27; };
    struct { char igi2_o5[44]; int v28; };
    struct { char igi2_o6[48]; int v29; };
    struct { char igi2_o7[52]; int v30; };
    struct { char igi2_o8[56]; int v31; };
    char igi2_extent[64];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct HumanAIActionContext_t *v2; // ebx
  enum bool isIdleAnimPlayed; // eax
  union __anon_1ce5 *p_uContext; // ebx
  struct HumanAI_s *v5; // edi
  struct QTask_s *ptParent; // esi
  struct Game_s *v7; // eax
  unsigned int v8; // edi
  unsigned int v9; // edx
  struct QTask_s *ptNext; // eax
  unsigned int v11; // ebx
  struct QTask_s *ptPrev; // eax
  struct WeaponType_s *ptTail; // edi
  struct QTask_s *WeaponTypeAnimPtr; // eax
  unsigned __int8 *v15; // ecx
  int v16; // ebx
  struct AnimHeader_s *AnimHeaderFromWeaponTypeAnim; // eax
  double v18; // st6
  struct QTask_s *v19; // eax
  unsigned __int16 eQTaskType; // dx
  int v21; // edx
  bool v22; // zf

  v2 = ptActionStackItem->ptContext;
  isIdleAnimPlayed = v2->uContext.tIdleContext.isIdleAnimPlayed;
  p_uContext = &v2->uContext;
  v5 = ptHumanAI;
  ptParent = ptHumanAI->tQTask.ptParent;
  igi2_frame.ptContext = (struct HumanAIIdleActionContext_s *)p_uContext;
  *(_QWORD *)&igi2_frame.tReal64x3.vX = 0x6900000068LL;
  *(_QWORD *)&igi2_frame.tReal64x3.vY = 0x6B0000006ALL;
  *(_QWORD *)&igi2_frame.tReal64x3.vZ = 0x6D0000006CLL;
  igi2_frame.v27 = 110;
  igi2_frame.v28 = 111;
  igi2_frame.v29 = 112;
  igi2_frame.v30 = 113;
  igi2_frame.v31 = 114;
  if ( isIdleAnimPlayed == false && p_uContext->tIdleContext.nTicksUsed > 30 && HumanAnim_IsBlendFinished(ptParent) )
  {
    v7 = Game_ptGame;
    v8 = (Game_ptGame->tRunRandomState.anRandom[0] >> 7)
       ^ Game_ptGame->tRunRandomState.anRandom[2]
       ^ Game_ptGame->tRunRandomState.anRandom[1];
    v9 = v8 + Game_ptGame->tRunRandomState.anRandom[0];
    Game_ptGame->tRunRandomState.anRandom[2] ^= Game_ptGame->tRunRandomState.anRandom[0] >> 7;
    v7->tRunRandomState.anRandom[0] = v9;
    v7->tRunRandomState.anRandom[1] = v8;
    ptNext = ptParent[33].ptNext;
    v11 = v9 % 0xB;
    if ( ptNext
      && (ptPrev = ptNext[1].ptPrev) != nullptr
      && (ptTail = (struct WeaponType_s *)ptPrev->tQTaskChildren.ptTail) != nullptr
      && (WeaponTypeAnimPtr = Human_GetWeaponTypeAnimPtr(ptParent)) != nullptr
      && (v15 = *(unsigned __int8 **)&WeaponTypeAnimPtr[24].eQTaskType) != nullptr
      && (v16 = *((_DWORD *)&igi2_frame.tReal64x3.vX + v11),
          (AnimHeaderFromWeaponTypeAnim = WeaponType_GetAnimHeaderFromWeaponTypeAnim(
                                            ptTail,
                                            v15,
                                            (enum WeaponTypeAnim_e)HumanSoldier_atStateData[v16].iWeaponTypeAnim)) != nullptr)
      && strcmp(AnimHeaderFromWeaponTypeAnim->zName, (char *)&dword_68F6C4) )
    {
      HumanAnim_SetUpperBodyAnimationAndTimeFromState(ptParent, v16, 0, 1.0);
    }
    else
    {
      HumanAnim_SetUpperBodyAnimationAndTimeFromState(ptParent, 0, 0, 1.0);
    }
    v5 = ptHumanAI;
    igi2_frame.ptContext->isIdleAnimPlayed = true;
    p_uContext = (union __anon_1ce5 *)igi2_frame.ptContext;
  }
  v18 = *(float *)&v5[1].tQTask.tQTaskRefList.ptTail;
  v19 = v5->tQTask.ptParent;
  eQTaskType = v19->eQTaskType;
  igi2_frame.tReal32x3_8 = *(float *)&v5[1].tQTask.ptParent * 4096.0;
  igi2_frame.tReal64x3.vX = *(float *)&v5[1].tQTask.tQTaskRefList.ptMiddle * 4096.0 + *(double *)&ptParent[1].ptNext;
  igi2_frame.tReal64x3.vY = v18 * 4096.0 + *(double *)&ptParent[1].tQTaskChildren.ptHead;
  igi2_frame.tReal64x3.vZ = igi2_frame.tReal32x3_8 + *(double *)&ptParent[1].tQTaskChildren.ptTail;
  if ( eQTaskType == HumanSoldier_eQTaskType )
  {
    igi2_frame.ptContexta = 0.0;
    if ( !LOBYTE(v19[75].ptPrev) )
      igi2_frame.ptContexta = 1.0;
    HumanAIContent_SetChannel(v5, 0, igi2_frame.ptContexta);
  }
  if ( HumanAI_MoveCharacterToNode(v5, *(_DWORD *)&v5[1].tQTask.eQTaskType) )
  {
    if ( (v5->anEventPriorityList[5] & 4) != 0 )
    {
      v5->avChannel[8] = 0.41887903213500977;
      v5->avChannel[9] = 0.20943951606750488;
    }
    else
    {
      v5->avChannel[8] = 0.20943951606750488;
      v5->avChannel[9] = 0.10471975803375244;
    }
    if ( HumanAI_FacePosition(v5, &igi2_frame.tReal64x3, 0.0872664675116539, true) )
    {
      v21 = p_uContext->tIdleContext.nTicksUsed + 1;
      v22 = p_uContext->tWaitContext.nTimer-- == 1;
      p_uContext->tIdleContext.nTicksUsed = v21;
      if ( v22 )
        HumanAI_PopActionStackItem(v5, ptActionStackItem);
    }
  }
}

// source: j/0/humanai/humanaicontent.c:1707  [anchor-callee]
void __cdecl HumanAIContent_HandleCombatIdleStance(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  #pragma pack(push, 1)
  union
  {
    struct { double *v16; };
    struct { char igi2_o1[4]; int v17; };
    struct { char igi2_o2[8]; struct CollisionEvaluateContext_s ptEvalContext; };
    struct { char igi2_o3[16]; float v19; };
    struct { char igi2_o4[20]; struct CollisionEvaluateContext_s v20; };
    struct { char igi2_o5[28]; struct QTask_s *v21; };
    struct { char igi2_o6[32]; double *v22; };
    struct { char igi2_o7[36]; struct real64x3_t ptEnd; };
    struct { char igi2_o8[60]; struct real64x3_t ptStart; };
    char igi2_extent[84];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptParent; // ebp
  union __anon_1ce5 *p_uContext; // ebx
  struct QTask_s *TargetQTask; // eax
  int vY_high; // esi
  int v7; // eax
  int v8; // ecx
  _DWORD *v9; // ecx
  int nTicksUsed; // eax
  int v11; // esi
  double v12; // st7
  double v13; // st6
  double v14; // st6
  double v15; // st3
  float ptHumanAIa = *(float *)&ptActionStackItem; // [esp+6Ch] [ebp+4h] ARGSLOT

  ptParent = ptHumanAI->tQTask.ptParent;
  p_uContext = &ptActionStackItem->ptContext->uContext;
  igi2_frame.v17 = 1;
  TargetQTask = HumanAI_GetTargetQTask(ptHumanAI, true);
  vY_high = HIDWORD(ptHumanAI->tCommon.tAimPosition.vY);
  igi2_frame.v16 = (double *)TargetQTask;
  if ( vY_high != -1 )
  {
    v7 = *(_DWORD *)&ptHumanAI->zScriptFile[36];
    v8 = *(_DWORD *)(v7 + 132);
    *(_DWORD *)&igi2_frame.ptEvalContext.isEvaluate = v7;
    if ( v8 )
    {
      if ( vY_high < (int)(*(_DWORD *)(v7 + 104)) && vY_high >= 0 )
      {
        v9 = (_DWORD *)(vY_high * Graph_GetGraphNodeDataSize(v7)
                      + *(_DWORD *)(*(_DWORD *)&igi2_frame.ptEvalContext.isEvaluate + 132));
        if ( *v9 != -1 && (AIGraph_bDoorNodeCriteria & v9[14]) != 0 )
          return;
      }
    }
  }
  nTicksUsed = p_uContext->tIdleContext.nTicksUsed;
  p_uContext->tLookAroundContext.eStage = nTicksUsed;
  if ( !igi2_frame.v16 )
    igi2_frame.v17 = 0;
  if ( ptActionStackItem->pfChildRunCallback == HumanAIContent_ReloadWeaponCB && nTicksUsed == 2 )
    nTicksUsed = 1;
  if ( nTicksUsed )
  {
    if ( nTicksUsed != 1 )
      goto LABEL_17;
    v11 = 1;
  }
  else
  {
    v11 = 2;
  }
  HumanAIContent_SetChannel(ptHumanAI, v11, 1.0);
LABEL_17:
  if ( HumanAI_GetTargetQTask(ptHumanAI, true) )
  {
    switch ( p_uContext->tWaitContext.nTimer )
    {
      case 0:
        v12 = 0.0;
        *(_DWORD *)&igi2_frame.ptEvalContext.isEvaluate = 0;
        igi2_frame.ptEvalContext.ptQTask = nullptr;
        goto LABEL_22;
      case 1:
        v12 = 2048.0;
        *(_DWORD *)&igi2_frame.ptEvalContext.isEvaluate = 0;
        igi2_frame.ptEvalContext.ptQTask = nullptr;
        goto LABEL_22;
      case 2:
      case 3:
        return;
      default:
        goto LABEL_21;
    }
  }
  else
  {
LABEL_21:
    v12 = igi2_frame.v19;
LABEL_22:
    if ( igi2_frame.v17 )
    {
      v13 = *(float *)&igi2_frame.ptEvalContext.isEvaluate + *(double *)&ptParent[1].ptNext;
      igi2_frame.v22 = igi2_frame.v16;
      igi2_frame.ptStart.vX = v13;
      v14 = *(float *)&igi2_frame.ptEvalContext.ptQTask + *(double *)&ptParent[1].tQTaskChildren.ptHead;
      qmemcpy(&igi2_frame.ptEnd, igi2_frame.v16 + 5, sizeof(igi2_frame.ptEnd));
      igi2_frame.ptStart.vY = v14;
      igi2_frame.ptStart.vZ = v12 + *(double *)&ptParent[1].tQTaskChildren.ptTail;
      igi2_frame.v20.ptQTask = ptParent;
      igi2_frame.ptEnd.vZ = igi2_frame.ptEnd.vZ + 2048.0;
      igi2_frame.v21 = ptParent;
      *(float *)&igi2_frame.ptEvalContext.isEvaluate = *(double *)&ptParent[1].ptNext - igi2_frame.v16[5];
      *(float *)&igi2_frame.ptEvalContext.ptQTask = *(double *)&ptParent[1].tQTaskChildren.ptHead - igi2_frame.v16[6];
      v15 = *(double *)&ptParent[1].tQTaskChildren.ptTail - igi2_frame.v16[7];
      ptHumanAIa = sqrt(
                     *(float *)&igi2_frame.ptEvalContext.isEvaluate * *(float *)&igi2_frame.ptEvalContext.isEvaluate
                   + *(float *)&igi2_frame.ptEvalContext.ptQTask * *(float *)&igi2_frame.ptEvalContext.ptQTask
                   + v15 * v15);
      if ( World_LineOfSight(
             Game_ptGame->ptWorld,
             &igi2_frame.ptStart,
             &igi2_frame.ptEnd,
             AIDetection_eLineOfSightQTaskEvent,
             &igi2_frame.v20,
             0x18000000u,
             WORLD_DYNCUBETREE_CATEGORY_ALL,
             (struct LineOfSightOutputContext_s *)&igi2_frame.ptEvalContext)
        || *(float *)&igi2_frame.ptEvalContext.isEvaluate >= 0.800000011920929 )
      {
        if ( p_uContext->tWaitContext.nTimer )
        {
          if ( p_uContext->tWaitContext.nTimer == 1 )
          {
            p_uContext->tWaitContext.nTimer = 3;
            if ( ptHumanAIa <= 28672.0 )
              p_uContext->tIdleContext.nTicksUsed = 2;
            else
              p_uContext->tIdleContext.nTicksUsed = 1;
          }
          return;
        }
        if ( ptHumanAIa > 122880.0 )
        {
          p_uContext->tWaitContext.nTimer = 3;
          p_uContext->tIdleContext.nTicksUsed = 0;
          return;
        }
      }
      else if ( p_uContext->tWaitContext.nTimer )
      {
        if ( p_uContext->tWaitContext.nTimer == 1 )
          p_uContext->tWaitContext.nTimer = 3;
        return;
      }
      p_uContext->tWaitContext.nTimer = 1;
    }
  }
}

// source: j/0/humanai/humanaicontent.c:1894  [anchor-caller]
void __cdecl HumanAIContent_CombatIdleInitCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  struct HumanAIActionStackItem_s *v2; // ebx
  union __anon_1ce5 *p_uContext; // esi
  struct QTask_s *ptParent; // edi
  int v5; // ecx
  int i; // eax
  int v7; // et2

  v2 = ptActionStackItem;
  p_uContext = &ptActionStackItem->ptContext->uContext;
  ptParent = ptHumanAI->tQTask.ptParent;
  if ( (ptHumanAI->anEventPriorityList[5] & 0x10) != 0
    || !HumanAI_GetTargetQTask(ptHumanAI, true)
    || HumanAI_IsRPGSoldier(ptHumanAI) )
  {
    v5 = 0;
    for ( i = (int)ptParent; i > 0; v5 += v7 )
    {
      v7 = i % 10;
      i /= 10;
    }
    p_uContext->tWaitContext.nTimer = v5 % 2 != 0 ? 1 : 3;
  }
  else
  {
    AISquad_SetMemberFlags(ptParent->ptParent, 16);
    v2 = ptActionStackItem;
    p_uContext->tWaitContext.nTimer = 0;
    ptHumanAI->avChannel[4] = 0.0;
  }
  p_uContext->tIdleContext.nTicksUsed = 2;
  p_uContext->tLookAroundContext.eStage = 2;
  v2->pfRunCallback = HumanAIContent_CombatIdleRunCB;
  v2->pfDeleteCallback = (void (__cdecl *)(struct HumanAI_s *, struct HumanAIActionStackItem_s *))HumanAIContent_CombatIdleDeleteCB;
  LODWORD(ptHumanAI->tCommon.tAimPosition.vZ) = HIDWORD(ptHumanAI->tCommon.tAimPosition.vY);
}

// source: j/0/humanai/humanaicontent.c:1957  [anchor-caller]
void __cdecl HumanAIContent_CombatIdleRunCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  struct QTask_s *ptParent; // eax
  void (__cdecl *pfDeleteCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // eax
  struct HumanAIActionContext_t *v4; // eax
  double *v5; // ebx
  struct QTask_s *TargetQTask; // eax
  struct QTask_s *v7; // ebx
  _DWORD *i; // edx
  int v9; // ecx
  double v10; // st7
  double v11; // st5
  long double v12; // st7
  struct QTask_s *v13; // ecx
  double v14; // st7
  double v15; // st5
  enum bool (__cdecl *pfChildRunCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // eax
  int v17; // edx
  int v18; // eax
  int *v19; // ecx
  enum bool (__cdecl *v20)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // eax
  struct QTask_s *ptHumanQTask; // [esp+Ch] [ebp-1Ch]
  struct QTask_s *v22; // [esp+10h] [ebp-18h]
  union __anon_1ce5 *ptContext; // [esp+14h] [ebp-14h]
  struct QTask_s *ptAISquadQTask; // [esp+18h] [ebp-10h]
  float v25; // [esp+1Ch] [ebp-Ch]
  double v26; // [esp+20h] [ebp-8h]
  double v27; // [esp+20h] [ebp-8h]

  ptContext = &ptActionStackItem->ptContext->uContext;
  ptParent = ptHumanAI->tQTask.ptParent;
  ptHumanQTask = ptParent;
  ptAISquadQTask = ptParent->ptParent;
  if ( (ptHumanAI->anEventPriorityList[5] & 4) == 0 )
  {
    pfDeleteCallback = ptActionStackItem->pfDeleteCallback;
    if ( pfDeleteCallback )
      pfDeleteCallback(ptHumanAI, ptActionStackItem);
    Node_Remove(ptActionStackItem);
    v4 = ptActionStackItem->ptContext;
    ptActionStackItem->isUsed = 0;
    if ( v4 )
    {
      v4->tNode.ptPrev = nullptr;
      v4->tNode.ptNext = nullptr;
      List_AddTail(v4, (int)&ptHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID);
      ptActionStackItem->ptContext = nullptr;
    }
    return;
  }
  if ( *(_DWORD *)&ptParent[32].eQTaskType == 2 )
    AISquad_SetMemberFlags(ptParent->ptParent, 16);
  v5 = (double *)ptHumanAI->tQTask.ptParent;
  v22 = nullptr;
  TargetQTask = HumanAI_GetTargetQTask(ptHumanAI, true);
  if ( TargetQTask )
  {
    v7 = TargetQTask;
  }
  else
  {
    for ( i = (_DWORD *)ptHumanAI->tAIDetection.atListItems[0].bQTaskMask; *i && i; i = (_DWORD *)*i )
    {
      v9 = *(_DWORD *)(i[2] + 8);
      if ( v9 )
      {
        if ( !*(_BYTE *)(v9 + 1180) )
        {
          v10 = v5[5] - *(double *)(v9 + 40);
          v26 = v5[7] - *(double *)(v9 + 56);
          v11 = v5[6] - *(double *)(v9 + 48);
          v12 = sqrt(v10 * v10 + v11 * v11 + v26 * v26);
          if ( !v22 || v12 < v25 )
          {
            v25 = v12;
            v22 = *(struct QTask_s **)(i[2] + 8);
          }
        }
      }
    }
    v7 = v22;
  }
  if ( v7 )
  {
    v13 = ptHumanQTask;
    if ( QTask_IsQTaskTypeDerived(v7->eQTaskType, Human_eQTaskType) )
    {
      v14 = *(double *)&v7[1].ptNext - *(double *)&ptHumanQTask[1].ptNext;
      v27 = *(double *)&v7[1].tQTaskChildren.ptTail - *(double *)&ptHumanQTask[1].tQTaskChildren.ptTail;
      v15 = *(double *)&v7[1].tQTaskChildren.ptHead - *(double *)&ptHumanQTask[1].tQTaskChildren.ptHead;
      if ( sqrt(v14 * v14 + v15 * v15 + v27 * v27) < 6144.0 )
        LODWORD(ptHumanAI->tCommon.tAimPosition.vZ) = HIDWORD(ptHumanAI->tCommon.tAimPosition.vY);
    }
  }
  else
  {
    v13 = ptHumanQTask;
  }
  if ( HIDWORD(ptHumanAI->tCommon.tAimPosition.vY) != LODWORD(ptHumanAI->tCommon.tAimPosition.vZ)
    && ptAISquadQTask[218].ptPrev != (struct QTask_s *)2 )
  {
    v13[34].tQTaskChildren.ptTail[1].tQTaskRefList.ptTail = (struct QReference_s *)(__int64)((double)AnimController_nTicksPerFrame
                                                                                           * 1.5);
    v13[75].tQTaskChildren.ptTail = (struct QTask_s *)1069547520;
    pfChildRunCallback = ptActionStackItem->pfChildRunCallback;
    if ( pfChildRunCallback && pfChildRunCallback(ptHumanAI, ptActionStackItem) )
      ptActionStackItem->pfChildRunCallback = nullptr;
    if ( HumanAI_MoveCharacterToNode(ptHumanAI, LODWORD(ptHumanAI->tCommon.tAimPosition.vZ)) == false )
    {
      ptActionStackItem->bFlags |= 1u;
      ptActionStackItem->nPriority = HumanAI_GetEventPriority(ptHumanAI, 21);
      HumanAI_MakeAIRun(ptHumanAI);
      ptContext->tWaitContext.nTimer = 3;
      return;
    }
    ptContext->tWaitContext.nTimer = 0;
    ptContext->tIdleContext.nTicksUsed = 2;
    goto LABEL_33;
  }
  ptActionStackItem->bFlags &= ~1u;
  v17 = -1;
  v18 = 0;
  if ( ptHumanAI->nAnimationMinimumDelay > 0 )
  {
    v19 = &ptHumanAI->anEventPriorityList[6];
    while ( *v19 != 30 )
    {
      ++v18;
      ++v19;
      if ( v18 >= ptHumanAI->nAnimationMinimumDelay )
        goto LABEL_40;
    }
    v17 = v18;
  }
LABEL_40:
  v20 = ptActionStackItem->pfChildRunCallback;
  ptActionStackItem->nPriority = v17;
  if ( v20 )
  {
    if ( v20(ptHumanAI, ptActionStackItem) )
      ptActionStackItem->pfChildRunCallback = nullptr;
  }
  else
  {
    HumanAI_FaceTarget(ptHumanAI);
  }
  if ( ptAISquadQTask[218].ptPrev == (struct QTask_s *)2
    || !ptContext->tIdleContext.nTicksUsed
    || HumanAI_HandleDispersal(ptHumanAI) == false )
  {
    HumanAIContent_HandleCombatIdleStance(ptHumanAI, ptActionStackItem);
    if ( ptAISquadQTask[218].ptPrev == (struct QTask_s *)2 )
    {
      if ( ptHumanQTask[31].ptPrev != (struct QTask_s *)12 && !HumanAI_GetTargetQTask(ptHumanAI, true) && v7 )
        qmemcpy(&ptHumanAI->tCommon.nIgnoreVisibilityFactorTimer, &v7[1], 0x18u);
    }
    else
    {
      if ( !HumanAI_GetTargetQTask(ptHumanAI, true) )
      {
LABEL_33:
        HumanAI_FaceTarget(ptHumanAI);
        return;
      }
      if ( HumanAI_HandleCoverSearch(ptHumanAI, nullptr) )
        LODWORD(ptHumanAI->tCommon.tAimPosition.vZ) = ptHumanAI->tCoverNodeSearchData.nCoverNodeId;
    }
  }
}

// source: j/0/humanai/humanaicontent.c:2099  [size]
void __cdecl HumanAIContent_CombatIdleDeleteCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  ptHumanAI->anEventPriorityList[5] &= ~0x10u;
}

// source: j/0/humanai/humanaicontent.c:2117  [size]
enum bool __cdecl HumanAIContent_ActivateRecurseCB(
        struct HumanAI_s *ptHumanAI,
        struct GraphNode_s *ptCurrentNode,
        void *pxContext)
{
  *(_DWORD *)pxContext = ptCurrentNode->nID;
  return true;
}

// source: j/0/humanai/humanaicontent.c:2136  [anchor-caller]
void __cdecl HumanAIContent_ActivateInitCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s *ptAlarmControlQTask; };
    struct { char igi2_o1[4]; struct AIGraphNode_s *ptClosestNode; };
    struct { char igi2_o2[8]; struct QTask_s *ptActivateQTask; };
    char igi2_extent[12];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct HumanAIActionStackItem_s *v2; // esi
  struct HumanAIActionContext_t *ptContext; // ebp
  struct HumanAI_s *v4; // edi
  struct QTask_s *ptParent; // eax
  unsigned int nTimer; // ecx
  struct QTask_s *ptMiddle; // ebx
  struct QTask_s *v8; // edx
  unsigned int ptHead; // eax
  struct QReference_s *v10; // eax
  struct QTask_s *pxObject; // eax
  struct QReference_s *v12; // ecx
  struct QTask_s *v13; // ebx
  struct Node_s *v14; // ecx
  struct Node_s *ptNext; // eax
  struct AIGraphNode_s *v16; // ebx
  struct HumanAI_s *nID; // ebx

  v2 = ptActionStackItem;
  ptContext = ptActionStackItem->ptContext;
  v4 = ptHumanAI;
  ptParent = ptHumanAI->tQTask.ptParent->ptParent;
  ptActionStackItem->pfRunCallback = HumanAIContent_ActivateRunCB;
  v2->pfDeleteCallback = HumanAIContent_ActivateDeleteCB;
  nTimer = ptContext->uContext.tWaitContext.nTimer;
  ptMiddle = ptParent[218].tQTaskChildren.ptMiddle;
  v8 = nullptr;
  igi2_frame.ptAlarmControlQTask = nullptr;
  LOBYTE(ptActionStackItem) = 0;
  if ( (struct QTask_s *)nTimer == ptMiddle )
  {
    ptHead = (unsigned int)ptParent[218].tQTaskChildren.ptHead;
    if ( ptHead >= 0x1000 )
      goto LABEL_9;
    v10 = Level_atLevelQTaskID[ptHead];
    if ( !v10 )
      goto LABEL_9;
    pxObject = (struct QTask_s *)v10->pxObject;
    igi2_frame.ptAlarmControlQTask = pxObject;
    if ( !pxObject )
      goto LABEL_9;
    LOBYTE(ptActionStackItem) = 1;
    v8 = pxObject;
  }
  if ( nTimer >= 0x1000
    || (v12 = Level_atLevelQTaskID[nTimer]) == nullptr
    || (igi2_frame.ptActivateQTask = (struct QTask_s *)v12->pxObject, (v13 = igi2_frame.ptActivateQTask) == nullptr) )
  {
LABEL_9:
    ptContext->uContext.tIdleContext.nTicksUsed = -1;
    goto LABEL_10;
  }
  ptContext->uContext.tIdleContext.nTicksUsed = -1;
  ptContext->uContext.tLookAroundContext.eStage = -1;
  ptContext->uContext.tActivateContext.isActivating = 0;
  v14 = HumanAI_tActivationList.ptHead;
  ptNext = HumanAI_tActivationList.ptHead->ptNext;
  if ( HumanAI_tActivationList.ptHead->ptNext )
  {
    while ( (struct QTask_s *)v14[1].ptNext != v13 )
    {
      v14 = ptNext;
      ptNext = ptNext->ptNext;
      if ( !ptNext )
        goto LABEL_14;
    }
    goto LABEL_10;
  }
LABEL_14:
  if ( (_BYTE)ptActionStackItem && HumanAI_GetActivationStatus(v8)
    || v8 && v8[19].tQTaskChildren.ptMiddle
    || QTask_IsQTaskTypeDerived(v13->eQTaskType, RigidDynCubeObj_eQTaskType) == false
    || (AIGraph_GetClosestNode(
          &igi2_frame.ptClosestNode,
          *(struct AIGraph_t **)&v4->zScriptFile[36],
          (struct real64x3_t *)&v13[1],
          false),
        (v16 = igi2_frame.ptClosestNode) == nullptr) )
  {
LABEL_10:
    HumanAI_PopActionStackItem(v4, v2);
    return;
  }
  ptHumanAI = (struct HumanAI_s *)-1;
  if ( HumanAI_RecurseNodesFromNode(v4, &igi2_frame.ptClosestNode->tGraphNode, 10, HumanAIContent_ActivateRecurseCB, &ptHumanAI) )
  {
    nID = (struct HumanAI_s *)v16->tGraphNode.nID;
    if ( nID == ptHumanAI )
    {
      ptContext->uContext.tIdleContext.nTicksUsed = (int)ptHumanAI;
    }
    else
    {
      ptContext->uContext.tIdleContext.nTicksUsed = (int)nID;
      ptContext->uContext.tLookAroundContext.eStage = (int)ptHumanAI;
    }
  }
  HIDWORD(v4->atAnimationEntries[1].vProbability) = HumanAI_SetActivationStatus(igi2_frame.ptActivateQTask, true);
  if ( (_BYTE)ptActionStackItem )
    v4->atAnimationEntries[2].nAnimation = (int)HumanAI_SetActivationStatus(igi2_frame.ptAlarmControlQTask, true);
  v4->anEventPriorityList[5] |= 8u;
}

// source: j/0/humanai/humanaicontent.c:2284  [anchor-caller]
void __cdecl HumanAIContent_ActivateRunCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  struct QTask_s *ptParent; // ecx
  union __anon_1ce5 *p_uContext; // edi
  int nTimer; // eax
  struct QReference_s *v5; // eax
  _WORD *pxObject; // eax
  enum bool (__cdecl *pfChildRunCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // eax
  int v8; // eax
  int v9; // esi
  struct QReference_s *v10; // eax
  char *v11; // eax
  struct HumanAIActionStackItem_s *FreeActionStackItem; // esi
  struct HumanAI_s *nTicksUsed; // [esp+0h] [ebp-24h]
  float v14; // [esp+0h] [ebp-24h]
  float v15; // [esp+0h] [ebp-24h]
  struct QTask_s *ptHumanQTask; // [esp+14h] [ebp-10h]
  struct QTask_s *ptHumanQTaska; // [esp+14h] [ebp-10h]
  struct AISquad_s *ptAISquad; // [esp+20h] [ebp-4h]

  ptParent = ptHumanAI->tQTask.ptParent;
  p_uContext = &ptActionStackItem->ptContext->uContext;
  ptAISquad = (struct AISquad_s *)ptParent->ptParent;
  nTimer = p_uContext->tWaitContext.nTimer;
  ptHumanQTask = ptParent;
  if ( p_uContext->tWaitContext.nTimer >= 0 && nTimer < 4096 && (v5 = Level_atLevelQTaskID[nTimer]) != nullptr )
    pxObject = v5->pxObject;
  else
    pxObject = nullptr;
  if ( pxObject[18] == Switch_eQTaskType && (int)(LevelFlow_ptLevelFlow->nTick - *((_DWORD *)pxObject + 147)) < 30 )
    goto LABEL_8;
  pfChildRunCallback = ptActionStackItem->pfChildRunCallback;
  if ( pfChildRunCallback )
  {
    v8 = pfChildRunCallback(ptHumanAI, ptActionStackItem);
    ptParent = ptHumanQTask;
    if ( v8 )
      ptActionStackItem->pfChildRunCallback = nullptr;
  }
  if ( p_uContext->tActivateContext.isWalkRun )
  {
    ptParent[34].tQTaskChildren.ptTail[1].tQTaskRefList.ptTail = (struct QReference_s *)(__int64)((double)AnimController_nTicksPerFrame
                                                                                                * 1.2999999523162842);
    ptParent[75].tQTaskChildren.ptTail = (struct QTask_s *)1067869798;
    HumanAI_MakeAIRun(ptHumanAI);
  }
  else
  {
    HumanAI_MakeAIWalk(ptHumanAI);
  }
  if ( p_uContext->tIdleContext.nTicksUsed == -1 )
  {
    if ( p_uContext->tLookAroundContext.eStage == -1 )
LABEL_8:
      HumanAI_PopActionStackItem(ptHumanAI, ptActionStackItem);
  }
  else
  {
    nTicksUsed = (struct HumanAI_s *)p_uContext->tIdleContext.nTicksUsed;
    ptHumanAI->avChannel[8] = 0.3141592741012573;
    ptHumanAI->avChannel[9] = 0.3141592741012573;
    if ( HumanAI_MoveCharacterToNode(ptHumanAI, (int)nTicksUsed) )
    {
      v9 = p_uContext->tWaitContext.nTimer;
      ptHumanQTaska = (struct QTask_s *)p_uContext->tWaitContext.nTimer;
      if ( p_uContext->tWaitContext.nTimer >= 0 && v9 < 4096 && (v10 = Level_atLevelQTaskID[v9]) != nullptr )
        v11 = (char *)v10->pxObject;
      else
        v11 = nullptr;
      if ( HumanAI_FacePositionSelectSpeed(ptHumanAI, (struct real64x3_t *)(v11 + 40), 0.1745329350233078, true) )
      {
        if ( v9 != LODWORD(ptAISquad->tEditVariables.vOverrideFormationDistance) )
        {
          if ( !p_uContext->tActivateContext.isActivating )
          {
            v14 = (float)p_uContext->tWaitContext.nTimer;
            HumanAIContent_SetChannel(ptHumanAI, 10, v14);
            if ( HumanAIContent_IsState(ptHumanAI, 6) )
              p_uContext->tActivateContext.isActivating = 1;
            return;
          }
          if ( HumanAIContent_IsState(ptHumanAI, 6) )
            return;
        }
        HumanAI_NotifyTaskHasBeenActivated(ptHumanAI, p_uContext->tWaitContext.nTimer);
        v15 = (float)p_uContext->tWaitContext.nTimer;
        HumanAIContent_SetChannel(ptHumanAI, 4, v15);
        p_uContext->tIdleContext.nTicksUsed = -1;
        HumanAI_PopActionStackItem(ptHumanAI, ptActionStackItem);
        if ( ptHumanQTaska == (struct QTask_s *)LODWORD(ptAISquad->tEditVariables.vOverrideFormationDistance) )
        {
          FreeActionStackItem = (struct HumanAIActionStackItem_s *)HumanAI_GetFreeActionStackItem((int)ptHumanAI);
          FreeActionStackItem->bFlags = 1;
          FreeActionStackItem->iDelay = 0;
          FreeActionStackItem->nPriority = HumanAI_GetEventPriority(ptHumanAI, 26);
          FreeActionStackItem->pfChildRunCallback = nullptr;
          FreeActionStackItem->pfDeleteCallback = nullptr;
          FreeActionStackItem->pfRunCallback = nullptr;
          FreeActionStackItem->pfRunInitCallback = nullptr;
          FreeActionStackItem->pfInitCallback = (void (__cdecl *)(struct HumanAI_s *, struct HumanAIActionStackItem_s *))HumanAIContent_CombatStationaryGunInitCB;
          FreeActionStackItem->ptContext = HumanAI_CreateActionContext(ptHumanAI);
          HumanAI_AddAction(ptHumanAI, FreeActionStackItem);
        }
      }
    }
  }
}

// source: j/0/humanai/humanaicontent.c:2409  [anchor-caller]
void __cdecl HumanAIContent_ActivateDeleteCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  void *vProbability_high; // eax
  void *nAnimation; // eax

  vProbability_high = (void *)HIDWORD(ptHumanAI->atAnimationEntries[1].vProbability);
  if ( vProbability_high )
  {
    HumanAI_ClearActivationEntry(vProbability_high);
    HIDWORD(ptHumanAI->atAnimationEntries[1].vProbability) = 0;
  }
  nAnimation = (void *)ptHumanAI->atAnimationEntries[2].nAnimation;
  if ( nAnimation )
  {
    HumanAI_ClearActivationEntry(nAnimation);
    ptHumanAI->atAnimationEntries[2].nAnimation = 0;
  }
  ptHumanAI->anEventPriorityList[5] &= ~8u;
}

// source: j/0/humanai/humanaicontent.c:2435  [anchor-caller]
void __cdecl HumanAIContent_PatrolInitCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  struct HumanAIActionStackItem_s *v2; // ebx
  struct HumanAIActionContext_t *ptContext; // ebp
  int nAnimationDelay; // eax
  char *v6; // ecx
  struct QTask_s *v7; // eax
  struct PatrolPathControl_t *v8; // esi
  unsigned __int16 v9; // dx
  int v10; // ebx
  struct QTask_s *FirstChildOfType; // eax
  struct HumanAI_s *ptHumanAIa = *(struct HumanAI_s * *)&ptHumanAI; // [esp+14h] [ebp+4h] ARGSLOT

  v2 = ptActionStackItem;
  ptContext = ptActionStackItem->ptContext;
  ptContext->uContext.tLookAroundContext.eStage = 0;
  HumanAIContent_UseIdleView(ptHumanAI);
  ptActionStackItem->pfRunCallback = HumanAIContent_PatrolRunCB;
  ptActionStackItem->pfDeleteCallback = HumanAIContent_PatrolDeleteCB;
  nAnimationDelay = ptHumanAI->nAnimationDelay;
  if ( !nAnimationDelay )
    goto LABEL_8;
  v6 = (char *)ptHumanAI + 32 * nAnimationDelay;
  v7 = *((struct QTask_s **)v6 + 2147);
  v8 = (struct PatrolPathControl_t *)(v6 + 8588);
  if ( !v7 )
    goto LABEL_8;
  ptHumanAIa = *((struct HumanAI_s **)v6 + 2148);
  if ( !ptHumanAIa )
    goto LABEL_8;
  v9 = PatrolPathCommand_eQTaskType;
  v10 = 0;
  FirstChildOfType = QTask_GetFirstChildOfType(v7, PatrolPathCommand_eQTaskType);
  if ( !FirstChildOfType )
  {
LABEL_7:
    HumanAI_PopPatrolPathStack(ptHumanAI);
    v2 = ptActionStackItem;
LABEL_8:
    PatrolPath_InitPatrolPath(
      (struct PatrolPathControl_t *)&ptHumanAI->atPatrolPathStackItems[ptHumanAI->nAnimationDelay + 1].ptLastEndCommandQTask,
      ptContext->uContext.tWaitContext.nTimer,
      ptContext->uContext.tIdleContext.nTicksUsed);
    if ( ptHumanAI->atPatrolPathStackItems[ptHumanAI->nAnimationDelay + 1].ptLastEndCommandQTask )
      ++ptHumanAI->nAnimationDelay;
    else
      HumanAI_PopActionStackItem(ptHumanAI, v2);
    return;
  }
  while ( FirstChildOfType != (struct QTask_s *)ptHumanAIa )
  {
    ++v10;
    FirstChildOfType = QTask_GetNextSiblingOfType(FirstChildOfType, v9);
    if ( !FirstChildOfType )
      goto LABEL_7;
  }
  PatrolPath_InitPatrolPath(v8, ptContext->uContext.tWaitContext.nTimer, v10);
}

// source: j/0/humanai/humanaicontent.c:2512  [anchor-caller]
void __cdecl HumanAIContent_PatrolRunCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v21; };
    struct { char igi2_o1[19]; char v22; };
    struct { char igi2_o2[20]; struct PatrolPathControl_t *ptPatrolPathControl; };
    struct { char igi2_o3[24]; struct QTask_s *v24; };
    struct { char igi2_o4[28]; struct HumanAIActionContext_t *a1; };
    struct { char igi2_o5[36]; struct real64x3_t ptPosition; };
    struct { char igi2_o6[60]; struct HumanAIEventContext_t ptQTask; };
    char igi2_extent[124];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct HumanAIActionStackItem_s *v2; // ecx
  struct QTask_s *p_tQTask; // edi
  struct QTask_s *ptParent; // esi
  int nAnimationDelay; // edx
  struct QTask_s *v6; // ebx
  struct QTask_s **p_ptLastEndCommandQTask; // edx
  struct QTask_s *ptNext; // eax
  enum bool (__cdecl *pfChildRunCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // eax
  int v10; // eax
  int ptHead; // eax
  struct LevelFlow_s *v12; // ecx
  bool v13; // zf
  struct GraphNode_s *Node; // eax
  enum bool v15; // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *QTaskFromLevelQTaskID; // eax
  struct QTask_s *v18; // esi
  char *p_ptMiddle; // ebx
  struct QTask_s *v20; // eax

  v2 = ptActionStackItem;
  p_tQTask = &ptHumanAI->tQTask;
  ptParent = ptHumanAI->tQTask.ptParent;
  nAnimationDelay = ptHumanAI->nAnimationDelay;
  v6 = *(struct QTask_s **)&ptHumanAI->atPatrolPathStackItems[nAnimationDelay].isCrouch;
  p_ptLastEndCommandQTask = &ptHumanAI->atPatrolPathStackItems[nAnimationDelay].ptLastEndCommandQTask;
  igi2_frame.a1 = ptActionStackItem->ptContext;
  ptNext = v6->ptNext;
  igi2_frame.v22 = 0;
  igi2_frame.ptPatrolPathControl = (struct PatrolPathControl_t *)p_ptLastEndCommandQTask;
  if ( !v6->ptNext || !ptNext->ptNext )
  {
    ptNext = p_ptLastEndCommandQTask[2];
    if ( !ptNext )
    {
      ptNext = (*p_ptLastEndCommandQTask)->tQTaskChildren.ptHead->ptNext != nullptr
             ? (*p_ptLastEndCommandQTask)->tQTaskChildren.ptHead
             : nullptr;
      v2 = ptActionStackItem;
    }
  }
  igi2_frame.v24 = ptNext;
  pfChildRunCallback = v2->pfChildRunCallback;
  if ( pfChildRunCallback )
  {
    v10 = pfChildRunCallback(ptHumanAI, v2);
    p_ptLastEndCommandQTask = &igi2_frame.ptPatrolPathControl->ptPatrolPathQTask;
    if ( v10 )
      ptActionStackItem->pfChildRunCallback = nullptr;
  }
  if ( *((_BYTE *)p_ptLastEndCommandQTask + 12) )
  {
    HumanAIContent_SetChannel(ptHumanAI, 1, 1.0);
    p_ptLastEndCommandQTask = &igi2_frame.ptPatrolPathControl->ptPatrolPathQTask;
  }
  if ( v6 )
  {
    ptHead = (int)v6[1].tQTaskChildren.ptHead;
    v12 = (struct LevelFlow_s *)((char *)&v6[1].ptPrev->ptNext + 1);
    switch ( (unsigned int)v6[1].ptPrev )
    {
      case 0u:
        if ( p_ptLastEndCommandQTask[4] != (struct QTask_s *)-1 )
        {
          if ( *((_BYTE *)p_ptLastEndCommandQTask + 12) )
            v13 = HumanAIContent_IsState(ptHumanAI, 2) == false;
          else
            v13 = HumanAIContent_IsState(ptHumanAI, 0) == false;
          goto LABEL_36;
        }
        p_ptLastEndCommandQTask[4] = nullptr;
        igi2_frame.v21 = (float)ptHead;
        HumanAIContent_SetChannel(ptHumanAI, 3, igi2_frame.v21);
        return;
      case 1u:
        v12 = LevelFlow_ptLevelFlow;
        if ( p_ptLastEndCommandQTask[4] == (struct QTask_s *)-1 )
          p_ptLastEndCommandQTask[4] = (struct QTask_s *)(ptHead + LevelFlow_ptLevelFlow->nTick);
        if ( v12->nTick > (int)p_ptLastEndCommandQTask[4] )
          goto LABEL_38;
        return;
      case 2u:
        *((_BYTE *)p_ptLastEndCommandQTask + 12) = 0;
        *((_BYTE *)p_ptLastEndCommandQTask + 13) = 1;
        if ( HumanAI_PatrolMoveCharacterToNode(ptHumanAI, ptHead) )
          igi2_frame.v22 = 1;
        if ( (ptHumanAI->tAStarSearchData.bFlags & 1) != 0 )
          goto LABEL_46;
        HumanAI_MakeAIWalk(ptHumanAI);
        goto LABEL_35;
      case 3u:
        *((_BYTE *)p_ptLastEndCommandQTask + 12) = 0;
        *((_BYTE *)p_ptLastEndCommandQTask + 13) = 0;
        if ( HumanAI_AttackMoveCharacterToNode(ptHumanAI, ptHead) )
          igi2_frame.v22 = 1;
        if ( (ptHumanAI->tAStarSearchData.bFlags & 1) != 0 )
        {
LABEL_46:
          ptHumanAI->avChannel[14] = 0.0;
          goto LABEL_37;
        }
        HumanAI_MakeAIRun(ptHumanAI);
LABEL_35:
        v13 = igi2_frame.v22 == 0;
LABEL_36:
        if ( !v13 )
          goto LABEL_37;
        return;
      case 4u:
        *((_BYTE *)p_ptLastEndCommandQTask + 12) = 1;
        goto LABEL_38;
      case 5u:
        Node = Graph_GetNode(*(struct Graph_s **)&ptHumanAI->zScriptFile[36], ptHead);
        if ( !Node )
          goto LABEL_37;
        Graph_GetNodePos(&igi2_frame.ptPosition, Node);
        v15 = HumanAI_FacePositionSelectSpeed(ptHumanAI, &igi2_frame.ptPosition, 0.05235987901687622, true);
        v12 = (struct LevelFlow_s *)igi2_frame.a1;
        if ( v15 )
          ++igi2_frame.a1->uContext.tLookAroundContext.eStage;
        else
          igi2_frame.a1->uContext.tLookAroundContext.eStage = 0;
        if ( !igi2_frame.v24 )
        {
          p_ptLastEndCommandQTask = &igi2_frame.ptPatrolPathControl->ptPatrolPathQTask;
LABEL_59:
          PatrolPath_StepPatrolPathForward((int)v12, (_DWORD **)p_ptLastEndCommandQTask);
          igi2_frame.ptPatrolPathControl->nUserModify = -1;
          igi2_frame.ptQTask.eEvent = 32;
          igi2_frame.ptQTask.bFlags = 0;
          igi2_frame.ptQTask.ptHumanOriginatorQTask = nullptr;
          igi2_frame.ptQTask.ptPosition = nullptr;
          igi2_frame.ptQTask.ptReferenceQTask = nullptr;
          HumanAI_SendEventSpecificQTask(p_tQTask, &igi2_frame.ptQTask);
          return;
        }
        if ( igi2_frame.v24[1].ptPrev == (struct QTask_s *)1 || (double)igi2_frame.a1->uContext.tLookAroundContext.eStage > 60.0 )
        {
LABEL_37:
          p_ptLastEndCommandQTask = &igi2_frame.ptPatrolPathControl->ptPatrolPathQTask;
LABEL_38:
          if ( igi2_frame.v24 )
          {
            ptPrev = igi2_frame.v24[1].ptPrev;
            if ( ptPrev == (struct QTask_s *)2 || ptPrev == (struct QTask_s *)3 )
              p_tQTask[112].ptPrev = (struct QTask_s *)1065353216;
          }
          goto LABEL_59;
        }
        break;
      case 7u:
        HumanAI_PopActionStackItem(ptHumanAI, ptActionStackItem);
        return;
      case 9u:
        QTaskFromLevelQTaskID = Level_GetQTaskFromLevelQTaskID(ptHead);
        v18 = QTaskFromLevelQTaskID;
        if ( !QTaskFromLevelQTaskID )
          goto LABEL_38;
        v12 = *(struct LevelFlow_s **)&Human_eQTaskType;
        if ( QTask_IsQTaskTypeDerived(QTaskFromLevelQTaskID->eQTaskType, Human_eQTaskType) == false )
          goto LABEL_38;
        LOBYTE(v12) = v18[29].tQTaskRefList.ptHead;
        if ( (_BYTE)v12
          || (*(double *)&v18[1].tQTaskChildren.ptHead - *(double *)&ptHumanAI->tQTask.ptParent[1].tQTaskChildren.ptHead)
           * *(float *)&ptHumanAI->tAIDetectionView.vViewConeLength
           + (*(double *)&v18[1].ptNext - *(double *)&ptHumanAI->tQTask.ptParent[1].ptNext)
           * *((float *)&ptHumanAI->tAIDetectionView.vViewConeAlpha + 1)
           + *((float *)&ptHumanAI->tAIDetectionView.vSecondaryViewConeAlpha + 1) * 0.0 >= 0.0 )
        {
          goto LABEL_38;
        }
        return;
      case 0xAu:
        igi2_frame.v22 = PatrolPathCommand_isExpression(v6);
        goto LABEL_35;
      case 0xBu:
        p_ptMiddle = (char *)&v6[3].tQTaskChildren.ptMiddle;
        if ( strlen(p_ptMiddle) )
        {
          v20 = ptParent[74].ptParent;
          if ( ((unsigned __int8)v20 & 1) != 0 )
          {
            ptParent[74].ptParent = (struct QTask_s *)((unsigned int)v20 & 0xFFFFFFFE);
            HumanAnim_ClearUpperBodyAnimation(ptParent, 0.0);
          }
          HumanAnim_SetUpperBodyAnimationAndTime(ptParent, p_ptMiddle, 0, 0.5);
          p_tQTask = &ptHumanAI->tQTask;
        }
        else
        {
          HumanAnim_ClearUpperBodyAnimation(ptParent, 0.5);
          ptParent[74].ptParent = (struct QTask_s *)((int)ptParent[74].ptParent | 1);
          HumanAnim_ClearUpperBodyAnimation(ptParent, 0.0);
        }
        goto LABEL_37;
      default:
        return;
    }
  }
}

// source: j/0/humanai/humanaicontent.c:2838  [anchor-mhash]
void __cdecl HumanAIContent_PatrolDeleteCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  int nAnimationDelay; // ecx
  int v3; // ecx

  nAnimationDelay = ptHumanAI->nAnimationDelay;
  if ( nAnimationDelay )
  {
    v3 = nAnimationDelay - 1;
    ptHumanAI->nAnimationDelay = v3;
    *(_DWORD *)&ptHumanAI->atPatrolPathStackItems[v3 + 1].isCrouch = 0;
    ptHumanAI->atPatrolPathStackItems[ptHumanAI->nAnimationDelay + 1].nUserModify = 0;
    ptHumanAI->atPatrolPathStackItems[ptHumanAI->nAnimationDelay + 1].ptLastEndCommandQTask = nullptr;
  }
}

// source: j/0/humanai/humanaicontent.c:2864  [size]
void __cdecl HumanAIContent_FallFlatInitCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  ptActionStackItem->pfRunCallback = HumanAIContent_FallFlatRunCB;
  ptActionStackItem->ptContext->uContext.tIdleContext.nTicksUsed = -1;
}

// source: j/0/humanai/humanaicontent.c:2882  [anchor-mhash]
void __cdecl HumanAIContent_FallFlatRunCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  union __anon_1ce5 *p_uContext; // edi
  struct LevelFlow_s *v3; // eax
  void (__cdecl *pfDeleteCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // eax
  struct HumanAIActionContext_t *ptContext; // eax

  p_uContext = &ptActionStackItem->ptContext->uContext;
  HumanAIContent_SetChannel(ptHumanAI, 2, 1.0);
  v3 = LevelFlow_ptLevelFlow;
  if ( p_uContext->tIdleContext.nTicksUsed < 0 )
    p_uContext->tIdleContext.nTicksUsed = LevelFlow_ptLevelFlow->nTick
                                        - (__int64)(p_uContext->tLookAroundContext.vCurrentRotation * -30.0);
  if ( v3->nTick > p_uContext->tIdleContext.nTicksUsed )
  {
    pfDeleteCallback = ptActionStackItem->pfDeleteCallback;
    if ( pfDeleteCallback )
      pfDeleteCallback(ptHumanAI, ptActionStackItem);
    Node_Remove(ptActionStackItem);
    ptContext = ptActionStackItem->ptContext;
    ptActionStackItem->isUsed = 0;
    if ( ptContext )
    {
      ptContext->tNode.ptPrev = nullptr;
      ptContext->tNode.ptNext = nullptr;
      List_AddTail(ptContext, (int)&ptHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID);
      ptActionStackItem->ptContext = nullptr;
    }
  }
}

// source: j/0/humanai/humanaicontent.c:2913  [anchor-mhash]
void __cdecl HumanAIContent_WalkToNodeInitCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  int v2; // esi
  int nTimer; // ebp
  void (__cdecl *pfDeleteCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // eax
  struct HumanAIActionContext_t *ptContext; // eax

  v2 = *(_DWORD *)&ptHumanAI->zScriptFile[36];
  nTimer = ptActionStackItem->ptContext->uContext.tWaitContext.nTimer;
  if ( !*(_DWORD *)(v2 + 132)
    || nTimer >= (int)(*(_DWORD *)(v2 + 104))
    || nTimer < 0
    || *(_DWORD *)(nTimer * Graph_GetGraphNodeDataSize(*(_DWORD *)&ptHumanAI->zScriptFile[36]) + *(_DWORD *)(v2 + 132)) == -1 )
  {
    pfDeleteCallback = ptActionStackItem->pfDeleteCallback;
    if ( pfDeleteCallback )
      pfDeleteCallback(ptHumanAI, ptActionStackItem);
    Node_Remove(ptActionStackItem);
    ptContext = ptActionStackItem->ptContext;
    ptActionStackItem->isUsed = 0;
    if ( ptContext )
    {
      ptContext->tNode.ptPrev = nullptr;
      ptContext->tNode.ptNext = nullptr;
      List_AddTail(ptContext, (int)&ptHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID);
      ptActionStackItem->ptContext = nullptr;
    }
  }
  else
  {
    ptActionStackItem->pfRunCallback = HumanAIContent_WalkToNodeRunCB;
  }
}

// source: j/0/humanai/humanaicontent.c:2939  [size]
void __cdecl HumanAIContent_WalkToNodeRunCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  struct HumanAIActionContext_t *ptContext; // ebx
  struct QTask_s *ptParent; // eax
  void (__cdecl *pfDeleteCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // eax
  struct HumanAIActionContext_t *v6; // eax
  int nTimer; // [esp-4h] [ebp-14h]
  float ptActionStackItema = *(float *)&ptActionStackItem; // [esp+18h] [ebp+8h] ARGSLOT

  ptContext = ptActionStackItem->ptContext;
  ptParent = ptHumanAI->tQTask.ptParent;
  if ( ptParent->eQTaskType == HumanSoldier_eQTaskType )
  {
    ptActionStackItema = 0.0;
    if ( !LOBYTE(ptParent[75].ptPrev) )
      ptActionStackItema = 1.0;
    HumanAIContent_SetChannel(ptHumanAI, 0, ptActionStackItema);
  }
  nTimer = ptContext->uContext.tWaitContext.nTimer;
  LODWORD(ptHumanAI->tCommon.tAimPosition.vZ) = nTimer;
  ptHumanAI->avChannel[8] = 0.3141592741012573;
  ptHumanAI->avChannel[9] = 0.3141592741012573;
  if ( HumanAI_MoveCharacterToNode(ptHumanAI, nTimer) )
  {
    pfDeleteCallback = ptActionStackItem->pfDeleteCallback;
    if ( pfDeleteCallback )
      pfDeleteCallback(ptHumanAI, ptActionStackItem);
    Node_Remove(ptActionStackItem);
    v6 = ptActionStackItem->ptContext;
    ptActionStackItem->isUsed = 0;
    if ( v6 )
    {
      v6->tNode.ptPrev = nullptr;
      v6->tNode.ptNext = nullptr;
      List_AddTail(v6, (int)&ptHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID);
      ptActionStackItem->ptContext = nullptr;
    }
  }
}

// source: j/0/humanai/humanaicontent.c:2965  [anchor-mhash]
void __cdecl HumanAIContent_RunToNodeInitCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  struct HumanAIActionContext_t *ptContext; // eax
  int nTimer; // ebp
  int v4; // edi
  void (__cdecl *pfDeleteCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // eax
  struct HumanAIActionContext_t *v6; // eax

  ptContext = ptActionStackItem->ptContext;
  ptActionStackItem->pfRunCallback = HumanAIContent_RunToNodeRunCB;
  nTimer = ptContext->uContext.tWaitContext.nTimer;
  v4 = *(_DWORD *)&ptHumanAI->zScriptFile[36];
  if ( !*(_DWORD *)(v4 + 132)
    || nTimer >= (int)(*(_DWORD *)(v4 + 104))
    || nTimer < 0
    || *(_DWORD *)(nTimer * Graph_GetGraphNodeDataSize(*(_DWORD *)&ptHumanAI->zScriptFile[36]) + *(_DWORD *)(v4 + 132)) == -1 )
  {
    pfDeleteCallback = ptActionStackItem->pfDeleteCallback;
    if ( pfDeleteCallback )
      pfDeleteCallback(ptHumanAI, ptActionStackItem);
    Node_Remove(ptActionStackItem);
    v6 = ptActionStackItem->ptContext;
    ptActionStackItem->isUsed = 0;
    if ( v6 )
    {
      v6->tNode.ptPrev = nullptr;
      v6->tNode.ptNext = nullptr;
      List_AddTail(v6, (int)&ptHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID);
      ptActionStackItem->ptContext = nullptr;
    }
  }
}

// source: j/0/humanai/humanaicontent.c:2989  [size]
void __cdecl HumanAIContent_RunToNodeRunCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  struct HumanAIActionContext_t *ptContext; // ebx
  struct QTask_s *ptParent; // eax
  void (__cdecl *pfDeleteCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // eax
  struct HumanAIActionContext_t *v6; // eax
  int nTimer; // [esp-4h] [ebp-14h]
  float ptActionStackItema = *(float *)&ptActionStackItem; // [esp+18h] [ebp+8h] ARGSLOT

  ptContext = ptActionStackItem->ptContext;
  ptParent = ptHumanAI->tQTask.ptParent;
  if ( ptParent->eQTaskType == HumanSoldier_eQTaskType )
  {
    ptActionStackItema = 1.0;
    if ( !LOBYTE(ptParent[75].ptPrev) )
      ptActionStackItema = 0.0;
    HumanAIContent_SetChannel(ptHumanAI, 0, ptActionStackItema);
  }
  nTimer = ptContext->uContext.tWaitContext.nTimer;
  LODWORD(ptHumanAI->tCommon.tAimPosition.vZ) = nTimer;
  ptHumanAI->avChannel[8] = 0.3141592741012573;
  ptHumanAI->avChannel[9] = 0.3141592741012573;
  if ( HumanAI_MoveCharacterToNode(ptHumanAI, nTimer) )
  {
    pfDeleteCallback = ptActionStackItem->pfDeleteCallback;
    if ( pfDeleteCallback )
      pfDeleteCallback(ptHumanAI, ptActionStackItem);
    Node_Remove(ptActionStackItem);
    v6 = ptActionStackItem->ptContext;
    ptActionStackItem->isUsed = 0;
    if ( v6 )
    {
      v6->tNode.ptPrev = nullptr;
      v6->tNode.ptNext = nullptr;
      List_AddTail(v6, (int)&ptHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID);
      ptActionStackItem->ptContext = nullptr;
    }
  }
}

// source: j/0/humanai/humanaicontent.c:3015  [size]
void __cdecl HumanAIContent_FireAtNodeInitCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  struct HumanAIActionContext_t *ptContext; // eax

  ptContext = ptActionStackItem->ptContext;
  ptActionStackItem->pfRunCallback = HumanAIContent_FireAtNodeRunCB;
  ptContext->uContext.tFireAtNodeTaskContext.isFireState = 0;
  ptContext->uContext.tLookAroundContext.nDelay = -1;
}

// source: j/0/humanai/humanaicontent.c:3036  [anchor-mhash]
void __cdecl HumanAIContent_FireAtNodeRunCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  struct HumanAIActionContext_t *ptContext; // ebp
  int nTicksUsed; // eax
  union __anon_1ce5 *p_uContext; // ebp
  struct QTask_s *ptParent; // ecx
  struct Weapon_s *ptNext; // eax
  struct WeaponTypeItem_s *ptActiveWeapon; // ecx
  struct GraphNode_s *Node; // eax
  int nDelay; // eax
  enum bool isIdleAnimPlayed; // ecx
  void (__cdecl *pfDeleteCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // eax
  struct HumanAIActionContext_t *v13; // eax
  struct WeaponGetFireTypeAmmoContext_s tAmmoContext; // [esp+Ch] [ebp-14h] BYREF
  struct HumanAI_s *ptHumanAIa = *(struct HumanAI_s * *)&ptHumanAI; // [esp+24h] [ebp+4h] ARGSLOT

  ptContext = ptActionStackItem->ptContext;
  nTicksUsed = ptContext->uContext.tIdleContext.nTicksUsed;
  p_uContext = &ptContext->uContext;
  ptParent = ptHumanAI->tQTask.ptParent;
  ptHumanAIa = (struct HumanAI_s *)ptParent;
  p_uContext->tIdleContext.nTicksUsed = nTicksUsed - 1;
  if ( nTicksUsed >= 0 && (ptNext = (struct Weapon_s *)ptParent[33].ptNext) != nullptr )
  {
    ptActiveWeapon = ptNext->tPrivate.ptActiveWeapon;
    if ( !ptActiveWeapon || !ptActiveWeapon->ptWeaponType )
    {
      HumanAI_PopActionStackItem(ptHumanAI, ptActionStackItem);
      return;
    }
    Weapon_GetFireTypeAmmoInfoFromWeaponTypeItem(ptNext, ptNext->tPrivate.ptActiveWeapon, 0, &tAmmoContext);
    if ( !tAmmoContext.nAmmoInWeapon )
    {
      if ( p_uContext->tFireAtNodeTaskContext.isShowReload )
      {
        ptHumanAI->avChannel[18] = 1.0;
        return;
      }
      Weapon_Reload(*((struct QTask_s **)&ptHumanAIa->atEvents[8].uEventSpecificData.iInt32 + 4));
      p_uContext->tFireAtNodeTaskContext.isFireState = 0;
    }
    Node = Graph_GetNode(*(struct Graph_s **)&ptHumanAI->zScriptFile[36], p_uContext->tWaitContext.nTimer);
    Graph_GetNodePos((struct real64x3_t *)&ptHumanAI[1], Node);
    if ( p_uContext->tFireAtNodeTaskContext.isFireState
      || (HumanAIContent_InitFire(ptHumanAI, 0), (p_uContext->tFireAtNodeTaskContext.isFireState = 1) != 0) )
    {
      nDelay = p_uContext->tLookAroundContext.nDelay;
      if ( nDelay >= 0 )
      {
        p_uContext->tLookAroundContext.nDelay = nDelay - 1;
      }
      else if ( HumanAIContent_RunFire(ptHumanAI) )
      {
        isIdleAnimPlayed = p_uContext->tIdleContext.isIdleAnimPlayed;
        p_uContext->tFireAtNodeTaskContext.isFireState = 0;
        p_uContext->tLookAroundContext.nDelay = isIdleAnimPlayed;
      }
    }
  }
  else
  {
    pfDeleteCallback = ptActionStackItem->pfDeleteCallback;
    if ( pfDeleteCallback )
      pfDeleteCallback(ptHumanAI, ptActionStackItem);
    Node_Remove(ptActionStackItem);
    v13 = ptActionStackItem->ptContext;
    ptActionStackItem->isUsed = 0;
    if ( v13 )
    {
      v13->tNode.ptPrev = nullptr;
      v13->tNode.ptNext = nullptr;
      List_AddTail(v13, (int)&ptHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID);
      ptActionStackItem->ptContext = nullptr;
    }
  }
}

// source: j/0/humanai/humanaicontent.c:3121  [size]
void __cdecl HumanAIContent_FireAtTaskInitCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  struct HumanAIActionContext_t *ptContext; // eax

  ptContext = ptActionStackItem->ptContext;
  ptActionStackItem->pfRunCallback = HumanAIContent_FireAtTaskRunCB;
  ptContext->uContext.tFireAtNodeTaskContext.isFireState = 0;
  ptContext->uContext.tLookAroundContext.nDelay = -1;
}

// source: j/0/humanai/humanaicontent.c:3140  [anchor-mhash]
void __cdecl HumanAIContent_FireAtTaskRunCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  struct HumanAIActionContext_t *ptContext; // ebp
  int nTicksUsed; // eax
  union __anon_1ce5 *p_uContext; // ebp
  struct QTask_s *ptParent; // edi
  struct Weapon_s *ptNext; // eax
  struct WeaponTypeItem_s *ptActiveWeapon; // ecx
  int nTimer; // eax
  struct QReference_s *v9; // eax
  _WORD *pxObject; // edx
  int nDelay; // eax
  enum bool isIdleAnimPlayed; // eax
  void (__cdecl *pfDeleteCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // eax
  struct HumanAIActionContext_t *v14; // eax
  struct WeaponGetFireTypeAmmoContext_s tAmmoContext; // [esp+Ch] [ebp-14h] BYREF

  ptContext = ptActionStackItem->ptContext;
  nTicksUsed = ptContext->uContext.tIdleContext.nTicksUsed;
  p_uContext = &ptContext->uContext;
  ptParent = ptHumanAI->tQTask.ptParent;
  p_uContext->tIdleContext.nTicksUsed = nTicksUsed - 1;
  if ( nTicksUsed >= 0 && (ptNext = (struct Weapon_s *)ptParent[33].ptNext) != nullptr )
  {
    ptActiveWeapon = ptNext->tPrivate.ptActiveWeapon;
    if ( !ptActiveWeapon || !ptActiveWeapon->ptWeaponType )
    {
      HumanAI_PopActionStackItem(ptHumanAI, ptActionStackItem);
      return;
    }
    Weapon_GetFireTypeAmmoInfoFromWeaponTypeItem(ptNext, ptNext->tPrivate.ptActiveWeapon, 0, &tAmmoContext);
    if ( !tAmmoContext.nAmmoInWeapon )
    {
      if ( p_uContext->tFireAtNodeTaskContext.isShowReload )
      {
        ptHumanAI->avChannel[18] = 1.0;
        return;
      }
      Weapon_Reload(ptParent[33].ptNext);
      p_uContext->tFireAtNodeTaskContext.isFireState = 0;
    }
    nTimer = p_uContext->tWaitContext.nTimer;
    if ( p_uContext->tWaitContext.nTimer >= 0
      && nTimer < 4096
      && (v9 = Level_atLevelQTaskID[nTimer]) != nullptr
      && (pxObject = v9->pxObject) != nullptr
      && QTask_IsQTaskTypeDerived(pxObject[18], ShadowVolume_nShadow) )
    {
      qmemcpy(&ptHumanAI[1], pxObject + 20, 0x18u);
      if ( p_uContext->tFireAtNodeTaskContext.isFireState
        || (HumanAIContent_InitFire(ptHumanAI, 0), (p_uContext->tFireAtNodeTaskContext.isFireState = 1) != 0) )
      {
        nDelay = p_uContext->tLookAroundContext.nDelay;
        if ( nDelay >= 0 )
        {
          p_uContext->tLookAroundContext.nDelay = nDelay - 1;
        }
        else if ( HumanAIContent_RunFire(ptHumanAI) )
        {
          isIdleAnimPlayed = p_uContext->tIdleContext.isIdleAnimPlayed;
          p_uContext->tFireAtNodeTaskContext.isFireState = 0;
          p_uContext->tLookAroundContext.nDelay = isIdleAnimPlayed;
        }
      }
    }
    else
    {
      HumanAI_PopActionStackItem(ptHumanAI, ptActionStackItem);
    }
  }
  else
  {
    pfDeleteCallback = ptActionStackItem->pfDeleteCallback;
    if ( pfDeleteCallback )
      pfDeleteCallback(ptHumanAI, ptActionStackItem);
    Node_Remove(ptActionStackItem);
    v14 = ptActionStackItem->ptContext;
    ptActionStackItem->isUsed = 0;
    if ( v14 )
    {
      v14->tNode.ptPrev = nullptr;
      v14->tNode.ptNext = nullptr;
      List_AddTail(v14, (int)&ptHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID);
      ptActionStackItem->ptContext = nullptr;
    }
  }
}

// source: j/0/humanai/humanaicontent.c:3243  [anchor-mhash]
void __cdecl HumanAIContent_LookAroundInitCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  struct HumanAIActionContext_t *ptContext; // ecx
  int v3; // eax
  union __anon_1ce5 *p_uContext; // ecx
  bool v5; // zf
  double v6; // st7
  int v7; // edx
  struct Game_s *v8; // eax
  unsigned int v9; // esi
  unsigned int v10; // esi
  int v11; // esi
  unsigned int v12; // esi

  ptContext = ptActionStackItem->ptContext;
  ptActionStackItem->pfRunInitCallback = HumanAIContent_LookAroundInitCB;
  ptActionStackItem->pfRunCallback = HumanAIContent_LookAroundRunCB;
  v3 = dword_834DBC4;
  p_uContext = &ptContext->uContext;
  v5 = dword_834DBC4 == 0;
  p_uContext->tWaitContext.nTimer = 0;
  if ( v5 )
    v6 = 0.7853981852531433;
  else
    v6 = -0.7853981852531433;
  p_uContext->tLookAroundContext.vCurrentTarget = v6;
  p_uContext->tLookAroundContext.eStage = 0;
  v7 = 1 - v3;
  v8 = Game_ptGame;
  v9 = Game_ptGame->tRunRandomState.anRandom[2];
  dword_834DBC4 = v7;
  v10 = (Game_ptGame->tRunRandomState.anRandom[0] >> 7) ^ v9;
  Game_ptGame->tRunRandomState.anRandom[2] = v10;
  v11 = v10 ^ v8->tRunRandomState.anRandom[1];
  v8->tRunRandomState.anRandom[1] = v11;
  v12 = v11 + v8->tRunRandomState.anRandom[0];
  v8->tRunRandomState.anRandom[0] = v12;
  p_uContext->tLookAroundContext.nDelay = (__int64)((double)(unsigned __int16)v12 * 0.0000152587890625 * 30.0 * 0.5);
}

// source: j/0/humanai/humanaicontent.c:3271  [anchor-mhash]
void __cdecl HumanAIContent_LookAroundRunCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  struct QTask_s *ptParent; // ebp
  union __anon_1ce5 *p_uContext; // ebx
  int nDelay; // eax
  double v5; // st7
  double v6; // st6
  double vCurrentTarget; // st7
  struct Game_s *v8; // eax
  float v9; // [esp+10h] [ebp-18h]
  float v10; // [esp+14h] [ebp-14h]
  float v11; // [esp+1Ch] [ebp-Ch]
  float v12; // [esp+20h] [ebp-8h]
  float v13; // [esp+24h] [ebp-4h]

  ptParent = ptHumanAI->tQTask.ptParent;
  p_uContext = &ptActionStackItem->ptContext->uContext;
  HumanAIContent_SetChannel(ptHumanAI, 5, 1.0);
  if ( p_uContext->tCombatContext.nFireSequences )
    HumanAIContent_SetChannel(ptHumanAI, 1, 1.0);
  nDelay = p_uContext->tLookAroundContext.nDelay;
  if ( nDelay )
  {
    p_uContext->tLookAroundContext.nDelay = nDelay - 1;
  }
  else
  {
    v9 = sin(p_uContext->tLookAroundContext.vCurrentRotation) * 40960.0;
    v10 = cos(p_uContext->tLookAroundContext.vCurrentRotation) * 40960.0;
    v5 = p_uContext->tLookAroundContext.vCurrentTarget - p_uContext->tLookAroundContext.vCurrentRotation;
    if ( v5 >= -0.05235987901687622 )
    {
      if ( v5 > 0.05235987901687622 )
        v5 = 0.05235987901687622;
    }
    else
    {
      v5 = -0.05235987901687622;
    }
    v11 = v10 * *(float *)&ptParent[3].tQTaskChildren.ptHead
        + v9 * *(float *)&ptParent[3].ptPrev
        + *(float *)&ptParent[3].tQTaskChildren.ptMiddle * 4096.0;
    v12 = v10 * *(float *)&ptParent[3].tQTaskRefList.ptHead
        + v9 * *(float *)&ptParent[3].tQTaskChildren.ptTail
        + *(float *)&ptParent[3].tQTaskRefList.ptMiddle * 4096.0;
    v13 = v10 * *(float *)&ptParent[3].ptParent
        + v9 * *(float *)&ptParent[3].tQTaskRefList.ptTail
        + *(float *)&ptParent[3].eQTaskType * 4096.0;
    v6 = v5;
    if ( v5 < 0.0 )
      v6 = -v5;
    if ( v6 >= 0.05235987901687622 )
    {
      p_uContext->tLookAroundContext.vCurrentRotation = v5 + p_uContext->tLookAroundContext.vCurrentRotation;
    }
    else
    {
      vCurrentTarget = p_uContext->tLookAroundContext.vCurrentTarget;
      ++p_uContext->tLookAroundContext.eStage;
      v8 = Game_ptGame;
      p_uContext->tLookAroundContext.vCurrentTarget = -vCurrentTarget;
      p_uContext->tLookAroundContext.nDelay = (__int64)(Random_GetRandomNumberReal32(&v8->tRunRandomState) * 30.0 * 0.3);
    }
    if ( p_uContext->tLookAroundContext.eStage > 6 || HumanAI_GetTargetQTask(ptHumanAI, true) )
      HumanAI_PopActionStackItem(ptHumanAI, ptActionStackItem);
    *(double *)&ptHumanAI->tCommon.nIgnoreVisibilityFactorTimer = v11 + *(double *)&ptParent[1].ptNext;
    *(double *)&ptHumanAI->tCommon.isDetectionSoundPlayed = v12 + *(double *)&ptParent[1].tQTaskChildren.ptHead;
    ptHumanAI->tCommon.tAimPosition.vX = v13 + *(double *)&ptParent[1].tQTaskChildren.ptTail;
  }
}

void __cdecl pfActionInitCB__(struct HumanAI_s *a1, struct HumanAIActionStackItem_s *a2)
{
  a2->pfRunInitCallback = (void (__cdecl *)(struct HumanAI_s *, struct HumanAIActionStackItem_s *))pfActionInitCB__;
  a2->pfRunCallback = HumanAIContent_EnemyDetectionRunCB;
  HumanAIContent_nLastDetectionSoundPlayedTick = LevelFlow_ptLevelFlow->nTick;
}

// source: j/0/humanai/humanaicontent.c:3351  [anchor-mhash]
void __cdecl HumanAIContent_EnemyDetectionRunCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  unsigned int bQTaskMask; // eax
  union __anon_1ce5 *p_uContext; // ecx
  void (__cdecl *pfDeleteCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // eax
  struct HumanAIActionContext_t *ptContext; // eax
  int v6; // edx
  enum bool v7; // eax
  struct real64x3_t tReal64x3; // [esp+8h] [ebp-18h] BYREF

  bQTaskMask = ptHumanAI->tAIDetection.atListItems[0].bQTaskMask;
  p_uContext = &ptActionStackItem->ptContext->uContext;
  if ( !*(_DWORD *)bQTaskMask || !bQTaskMask )
    goto LABEL_6;
  while ( !*(_BYTE *)(bQTaskMask + 54) )
  {
    bQTaskMask = *(_DWORD *)bQTaskMask;
    if ( !*(_DWORD *)bQTaskMask || !bQTaskMask )
      goto LABEL_6;
  }
  v6 = *(_DWORD *)(*(_DWORD *)(bQTaskMask + 8) + 8);
  if ( v6 )
  {
    if ( p_uContext->tWaitContext.nTimer > 0 )
      --p_uContext->tWaitContext.nTimer;
    v7 = QTask_IsQTaskTypeDerived(*(_WORD *)(v6 + 36), Human_eQTaskType);
    qmemcpy(&tReal64x3, (void *)(v6 + 40), sizeof(tReal64x3));
    if ( v7 )
      tReal64x3.vZ = tReal64x3.vZ + 2048.0;
    HumanAI_FacePositionSelectSpeed(ptHumanAI, &tReal64x3, 0.03490658476948738, true);
  }
  else
  {
LABEL_6:
    pfDeleteCallback = ptActionStackItem->pfDeleteCallback;
    if ( pfDeleteCallback )
      pfDeleteCallback(ptHumanAI, ptActionStackItem);
    Node_Remove(ptActionStackItem);
    ptContext = ptActionStackItem->ptContext;
    ptActionStackItem->isUsed = 0;
    if ( ptContext )
    {
      ptContext->tNode.ptPrev = nullptr;
      ptContext->tNode.ptNext = nullptr;
      List_AddTail(ptContext, (int)&ptHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID);
      ptActionStackItem->ptContext = nullptr;
    }
  }
}

// source: j/0/humanai/humanaicontent.c:3422  [size]
void __cdecl HumanAIContent_LookAtPositionInitCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  ptActionStackItem->pfRunInitCallback = (void (__cdecl *)(struct HumanAI_s *, struct HumanAIActionStackItem_s *))HumanAIContent_LookAtPositionInitCB;
  ptActionStackItem->pfRunCallback = HumanAIContent_LookAtPositionRunCB;
  ptActionStackItem->ptContext->uContext.tLookAtPositionContext.nTimer = 0;
}

// source: j/0/humanai/humanaicontent.c:3441  [anchor-mhash]
void __cdecl HumanAIContent_LookAtPositionRunCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  union __anon_1ce5 *p_uContext; // ebp
  int v4; // edx
  int v5; // eax
  int *v6; // ecx
  struct QTask_s *TargetQTask; // eax
  struct AIDetectionListItem_s *MatchingListItem; // eax
  int nTimer; // ecx
  struct HumanAI_s *ptHumanAIa = *(struct HumanAI_s * *)&ptHumanAI; // [esp+10h] [ebp+4h] ARGSLOT

  p_uContext = &ptActionStackItem->ptContext->uContext;
  v4 = -1;
  v5 = 0;
  if ( ptHumanAI->nAnimationMinimumDelay > 0 )
  {
    v6 = &ptHumanAI->anEventPriorityList[6];
    while ( *v6 != 4 )
    {
      ++v5;
      ++v6;
      if ( v5 >= ptHumanAI->nAnimationMinimumDelay )
        goto LABEL_7;
    }
    v4 = v5;
  }
LABEL_7:
  if ( ptActionStackItem->nPriority != v4 )
  {
    qmemcpy(&ptHumanAI->tCommon.nIgnoreVisibilityFactorTimer, p_uContext, 0x18u);
    qmemcpy(&ptHumanAI[1], p_uContext, 0x18u);
    HumanAIContent_SetChannel(ptHumanAI, 5, 1.0);
  }
  if ( (ptHumanAI->anEventPriorityList[5] & 4) != 0 )
  {
    ptHumanAI->avChannel[8] = 0.41887903213500977;
    ptHumanAI->avChannel[9] = 0.20943951606750488;
  }
  else
  {
    ptHumanAI->avChannel[8] = 0.20943951606750488;
    ptHumanAI->avChannel[9] = 0.10471975803375244;
  }
  if ( HumanAI_FacePosition(ptHumanAI, (struct real64x3_t *)p_uContext, 0.03490658476948738, true) )
  {
    TargetQTask = HumanAI_GetTargetQTask(ptHumanAI, true);
    ptHumanAIa = (struct HumanAI_s *)TargetQTask;
    if ( TargetQTask )
    {
      qmemcpy(p_uContext, &TargetQTask[1], 0x18u);
      MatchingListItem = AIDetection_FindMatchingListItem(
                           (struct AIDetection_s *)&ptHumanAI->tAIDetection.tFriendList,
                           TargetQTask);
      if ( MatchingListItem && MatchingListItem->isIdentifying )
        ptHumanAIa = nullptr;
      TargetQTask = &ptHumanAIa->tQTask;
    }
    nTimer = p_uContext->tLookAtPositionContext.nTimer;
    if ( nTimer >= 150 || TargetQTask )
      HumanAI_PopActionStackItem(ptHumanAI, ptActionStackItem);
    else
      p_uContext->tLookAtPositionContext.nTimer = nTimer + 1;
  }
}

// source: j/0/humanai/humanaicontent.c:3495  [anchor-mhash]
void __cdecl HumanAIContent_DeadFriendlyDetectionInitCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  ptActionStackItem->pfRunInitCallback = (void (__cdecl *)(struct HumanAI_s *, struct HumanAIActionStackItem_s *))HumanAIContent_DeadFriendlyDetectionInitCB;
  ptActionStackItem->pfRunCallback = HumanAIContent_DeadFriendlyDetectionRunCB;
  ptActionStackItem->ptContext->uContext.tWaitContext.nTimer = 0;
  ptHumanAI->anEventPriorityList[5] |= 2u;
}

// source: j/0/humanai/humanaicontent.c:3517  [anchor-mhash]
void __cdecl HumanAIContent_DeadFriendlyDetectionRunCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  struct HumanAIActionContext_t *ptContext; // eax
  int v3; // ecx
  void (__cdecl *pfDeleteCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // eax
  struct HumanAIActionContext_t *v5; // eax
  int vZ_low; // [esp-8h] [ebp-Ch]

  ptContext = ptActionStackItem->ptContext;
  v3 = ptContext->uContext.tWaitContext.nTimer + 1;
  ptContext->uContext.tWaitContext.nTimer = v3;
  if ( (double)v3 <= 90.0 )
  {
    if ( ptHumanAI->tCoverNodeSearchData.eState == HUMANAI_COVERNODESEARCH_NODE_FOUND )
    {
      LODWORD(ptHumanAI->tCommon.tAimPosition.vZ) = ptHumanAI->tCoverNodeSearchData.nCoverNodeId;
      HumanAI_MakeAIRun(ptHumanAI);
      vZ_low = LODWORD(ptHumanAI->tCommon.tAimPosition.vZ);
      ptHumanAI->avChannel[8] = 0.3141592741012573;
      ptHumanAI->avChannel[9] = 0.3141592741012573;
      if ( HumanAI_MoveCharacterToNode(ptHumanAI, vZ_low) )
      {
        ptHumanAI->tCoverNodeSearchData.eState = HUMANAI_COVERNODESEARCH_IDLE;
        HumanAI_PopActionStackItem(ptHumanAI, ptActionStackItem);
      }
    }
  }
  else
  {
    pfDeleteCallback = ptActionStackItem->pfDeleteCallback;
    if ( pfDeleteCallback )
      pfDeleteCallback(ptHumanAI, ptActionStackItem);
    Node_Remove(ptActionStackItem);
    v5 = ptActionStackItem->ptContext;
    ptActionStackItem->isUsed = 0;
    if ( v5 )
    {
      v5->tNode.ptPrev = nullptr;
      v5->tNode.ptNext = nullptr;
      List_AddTail(v5, (int)&ptHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID);
      ptActionStackItem->ptContext = nullptr;
    }
  }
}

// source: j/0/humanai/humanaicontent.c:3549  [anchor-mhash]
void __cdecl HumanAIContent_RunToCoverInitCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  ptActionStackItem->ptContext->uContext.tWaitContext.nTimer = 0;
  ptActionStackItem->pfRunInitCallback = HumanAIContent_RunToCoverInitCB;
  ptActionStackItem->pfRunCallback = HumanAIContent_RunToCoverRunCB;
  ptHumanAI->tCoverNodeSearchData.eState = HUMANAI_COVERNODESEARCH_IDLE;
}

// source: j/0/humanai/humanaicontent.c:3571  [anchor-caller]
void __cdecl HumanAIContent_RunToCoverRunCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  union __anon_1ce5 *p_uContext; // ebx
  void (__cdecl *pfDeleteCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // eax
  struct HumanAIActionContext_t *ptContext; // eax
  int nTicksUsed; // ebx
  int v6; // esi
  int vZ_low; // [esp-4h] [ebp-1Ch]
  int v8; // [esp+10h] [ebp-8h]
  struct real64x3_t *p_tPosition; // [esp+14h] [ebp-4h]

  p_uContext = &ptActionStackItem->ptContext->uContext;
  p_tPosition = &ptActionStackItem->ptContext->uContext.tRunToCoverContext.tPosition;
  HumanAI_HandleCoverSearch(ptHumanAI, p_tPosition);
  v8 = p_uContext->tWaitContext.nTimer + 1;
  p_uContext->tWaitContext.nTimer = v8;
  if ( (double)v8 <= 90.0 )
  {
    if ( ptHumanAI->tCoverNodeSearchData.eState == HUMANAI_COVERNODESEARCH_NODE_FOUND )
    {
      LODWORD(ptHumanAI->tCommon.tAimPosition.vZ) = ptHumanAI->tCoverNodeSearchData.nCoverNodeId;
      HumanAI_MakeAIRun(ptHumanAI);
      vZ_low = LODWORD(ptHumanAI->tCommon.tAimPosition.vZ);
      ptHumanAI->avChannel[8] = 0.3141592741012573;
      ptHumanAI->avChannel[9] = 0.3141592741012573;
      if ( HumanAI_MoveCharacterToNode(ptHumanAI, vZ_low) )
      {
        ptHumanAI->tCoverNodeSearchData.eState = HUMANAI_COVERNODESEARCH_IDLE;
        if ( HumanAI_FacePositionSelectSpeed(ptHumanAI, p_tPosition, 0.1745329350233078, true) )
          HumanAI_PopActionStackItem(ptHumanAI, ptActionStackItem);
      }
    }
    else
    {
      nTicksUsed = p_uContext->tIdleContext.nTicksUsed;
      if ( nTicksUsed )
      {
        if ( nTicksUsed != 1 )
          return;
        v6 = 1;
      }
      else
      {
        v6 = 2;
      }
      HumanAIContent_SetChannel(ptHumanAI, v6, 1.0);
    }
  }
  else
  {
    pfDeleteCallback = ptActionStackItem->pfDeleteCallback;
    if ( pfDeleteCallback )
      pfDeleteCallback(ptHumanAI, ptActionStackItem);
    Node_Remove(ptActionStackItem);
    ptContext = ptActionStackItem->ptContext;
    ptActionStackItem->isUsed = 0;
    if ( ptContext )
    {
      ptContext->tNode.ptPrev = nullptr;
      ptContext->tNode.ptNext = nullptr;
      List_AddTail(ptContext, (int)&ptHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID);
      ptActionStackItem->ptContext = nullptr;
    }
  }
}

// source: j/0/humanai/humanaicontent.c:3624  [anchor-strings]
void __cdecl HumanAIContent_SetChannel(struct HumanAI_s *ptHumanAI, int nContentChannel, float vData)
{
  int v3; // eax
  int v4; // ecx
  struct QReference_s *v5; // eax
  char zTempString[256]; // [esp+0h] [ebp-100h] BYREF

  v3 = HumanAIContent_apnChannelList[LODWORD(ptHumanAI->vHearingRangeFactor)][nContentChannel];
  if ( v3 == -1 )
  {
    v4 = 0;
    while ( 1 )
    {
      v5 = Level_atLevelQTaskID[v4];
      if ( v5 )
      {
        if ( v5->pxObject == ptHumanAI )
          break;
      }
      if ( ++v4 >= 4096 )
      {
        v4 = -1;
        break;
      }
    }
    sprintf(zTempString, "AI(%d) type(%s) channel(%d)", v4, &ptHumanAI->zAIType[40], nContentChannel);
  }
  else
  {
    ptHumanAI->avChannel[v3 + 10] = vData;
  }
}

// source: j/0/humanai/humanaicontent.c:3652  [size]
int __cdecl HumanAIContent_GetHumanChannelFromContentChannel(
        struct HumanAI_s *ptHumanAI,
        int nContentChannel)
{
  return HumanAIContent_apnChannelList[LODWORD(ptHumanAI->vHearingRangeFactor)][nContentChannel];
}

// source: j/0/humanai/humanaicontent.c:3665  [anchor-callee]
enum bool __cdecl HumanAIContent_IsState(struct HumanAI_s *ptHumanAI, int nContentState)
{
  struct QTask_s *v2; // eax

  v2 = (struct QTask_s *)HumanAIContent_apnStateList[LODWORD(ptHumanAI->vHearingRangeFactor)][nContentState];
  return v2 != (struct QTask_s *)-1 && ptHumanAI->tQTask.ptParent[31].ptPrev == v2;
}

// source: j/0/humanai/humanaicontent.c:3698  [anchor-caller]
void __cdecl HumanAIContent_ReceiveSquadOrder(
        struct HumanAI_s *ptHumanAI,
        struct AISquadOrderContext_s *ptSquadOrder)
{
  struct HumanAIActionStackItem_s *v2; // esi
  struct HumanAIActionStackItem_s *v3; // esi
  struct HumanAIActionStackItem_s *v4; // esi
  struct HumanAIActionStackItem_s *v5; // esi
  struct HumanAIActionStackItem_s *v6; // esi
  void (__cdecl *v7)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // edi
  struct HumanAIActionStackItem_s *FreeActionStackItem; // esi
  void (__cdecl *v9)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // eax
  void (__cdecl *pfRunCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // edi
  struct HumanAIActionStackItem_s *v11; // esi
  void (__cdecl *v12)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // eax
  struct RandomState_s *p_tRunRandomState; // eax
  double RandomNumberReal32; // st7
  void (__cdecl *v15)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // eax
  int v16; // eax
  struct HumanAIActionStackItem_s *v17; // esi
  int nNodeId; // edx
  struct HumanAIActionStackItem_s *v19; // esi
  struct HumanAIActionStackItem_s *v20; // esi
  struct HumanAIActionStackItem_s *v21; // esi
  struct HumanAIActionContext_t *v22; // [esp+4h] [ebp-10h]
  struct HumanAIActionContext_t *v23; // [esp+4h] [ebp-10h]
  struct HumanAIActionContext_t *v24; // [esp+4h] [ebp-10h]
  struct HumanAIActionContext_t *ActionContext; // [esp+4h] [ebp-10h]
  struct HumanAIActionContext_t *v26; // [esp+4h] [ebp-10h]
  struct HumanAIActionContext_t *v27; // [esp+4h] [ebp-10h]
  struct HumanAIActionContext_t *v28; // [esp+4h] [ebp-10h]
  struct HumanAIActionContext_t *v29; // [esp+4h] [ebp-10h]
  struct HumanAIActionContext_t *v30; // [esp+4h] [ebp-10h]
  struct HumanAIActionStackItem_s *ptAction; // [esp+8h] [ebp-Ch]
  float ptActiona; // [esp+8h] [ebp-Ch]

  switch ( ptSquadOrder->eOrder )
  {
    case AISQUAD_ORDER_LOOK_AT_POSITION:
      v7 = *(_DWORD *)ptHumanAI->atActionStackItemList[0].pfRunCallback != 0
         ? ptHumanAI->atActionStackItemList[0].pfRunCallback
         : nullptr;
      ActionContext = HumanAI_CreateActionContext(ptHumanAI);
      FreeActionStackItem = (struct HumanAIActionStackItem_s *)HumanAI_GetFreeActionStackItem((int)ptHumanAI);
      FreeActionStackItem->bFlags = 0;
      if ( v7
        && ((v9 = *((void (__cdecl **)(struct HumanAI_s *, struct HumanAIActionStackItem_s *))v7 + 6),
             v9 == HumanAIContent_LookAtPositionInitCB)
         || v9 == HumanAIContent_LookAtEventInitCB
         || (char *)v9 == (char *)HumanAIContent_LookInApproxDirectionInitCB) )
      {
        FreeActionStackItem->iDelay = *((_DWORD *)v7 + 4);
      }
      else
      {
        FreeActionStackItem->iDelay = ptSquadOrder->iDelay;
      }
      HumanAI_ClearActionStack(ptHumanAI);
      FreeActionStackItem->nPriority = HumanAI_GetEventPriority(ptHumanAI, 46);
      FreeActionStackItem->ptContext = ActionContext;
      FreeActionStackItem->pfChildRunCallback = nullptr;
      FreeActionStackItem->pfDeleteCallback = nullptr;
      FreeActionStackItem->pfRunInitCallback = nullptr;
      FreeActionStackItem->pfInitCallback = (void (__cdecl *)(struct HumanAI_s *, struct HumanAIActionStackItem_s *))HumanAIContent_LookAtPositionInitCB;
      FreeActionStackItem->pfRunCallback = HumanAIContent_LookAtPositionRunCB;
      qmemcpy(&ActionContext->uContext, &ptSquadOrder->uContext, 0x18u);
      FreeActionStackItem->eSquadOrder = ptSquadOrder->eOrder;
      HumanAI_AddAction(ptHumanAI, FreeActionStackItem);
      return;
    case AISQUAD_ORDER_LOOK_AT_EVENT:
      pfRunCallback = ptHumanAI->atActionStackItemList[0].pfRunCallback;
      if ( *(_DWORD *)pfRunCallback )
      {
        if ( pfRunCallback
          && (int)(*((_DWORD *)pfRunCallback + 3)) < ptSquadOrder->uContext.tLookInApproxDirectionOrderContext.nTimer )
        {
          return;
        }
      }
      else
      {
        pfRunCallback = nullptr;
      }
      v26 = HumanAI_CreateActionContext(ptHumanAI);
      v11 = (struct HumanAIActionStackItem_s *)HumanAI_GetFreeActionStackItem((int)ptHumanAI);
      v11->bFlags = 0;
      if ( pfRunCallback
        && ((v12 = *((void (__cdecl **)(struct HumanAI_s *, struct HumanAIActionStackItem_s *))pfRunCallback
                   + 6),
             v12 == HumanAIContent_LookAtEventInitCB)
         || v12 == HumanAIContent_LookAtPositionInitCB
         || (char *)v12 == (char *)HumanAIContent_LookInApproxDirectionInitCB) )
      {
        v11->iDelay = *((_DWORD *)pfRunCallback + 4);
      }
      else
      {
        v11->iDelay = ptSquadOrder->iDelay;
      }
      HumanAI_ClearActionStack(ptHumanAI);
      v11->nPriority = ptSquadOrder->uContext.tLookInApproxDirectionOrderContext.nTimer;
      v11->pfChildRunCallback = nullptr;
      v11->pfDeleteCallback = nullptr;
      v11->pfRunInitCallback = nullptr;
      p_tRunRandomState = &Game_ptGame->tRunRandomState;
      v11->pfInitCallback = (void (__cdecl *)(struct HumanAI_s *, struct HumanAIActionStackItem_s *))HumanAIContent_LookAtEventInitCB;
      v11->pfRunCallback = HumanAIContent_LookAtEventRunCB;
      v11->ptContext = v26;
      RandomNumberReal32 = Random_GetRandomNumberReal32(p_tRunRandomState);
      qmemcpy(&v26->uContext, &ptSquadOrder->uContext, 0x18u);
      v26->uContext.tLookAtEventContext.vSecondsToLook = (RandomNumberReal32 * 0.20000000298023224 + 0.800000011920929) * 15.0;
      v26->uContext.tLookInApproxDirectionContext.nStartTime = 0;
      v11->eSquadOrder = ptSquadOrder->eOrder;
      HumanAI_AddAction(ptHumanAI, v11);
      return;
    case AISQUAD_ORDER_LOOK_IN_APPROX_DIRECTION:
      v15 = ptHumanAI->atActionStackItemList[0].pfRunCallback;
      if ( !*(_DWORD *)v15
        || !v15
        || *((void (__cdecl **)(struct HumanAI_s *, struct HumanAIActionStackItem_s *))v15 + 6) != HumanAIContent_LookInApproxDirectionInitCB
        && (int)(*((_DWORD *)v15 + 3)) >= SLODWORD(ptSquadOrder->uContext.tTakeCoverOrderContext.tDirection.vZ) )
      {
        ptActiona = Random_GetRandomNumberReal32(&Game_ptGame->tRunRandomState) * 0.20000000298023224 + 0.800000011920929;
        HumanAI_ClearActionStack(ptHumanAI);
        v27 = HumanAI_CreateActionContext(ptHumanAI);
        v16 = HumanAI_GetFreeActionStackItem((int)ptHumanAI);
        *(_DWORD *)(v16 + 20) = 0;
        *(_DWORD *)(v16 + 16) = ptSquadOrder->iDelay;
        *(float *)(v16 + 12) = ptSquadOrder->uContext.tTakeCoverOrderContext.tDirection.vZ;
        *(_DWORD *)(v16 + 44) = 0;
        *(_DWORD *)(v16 + 32) = 0;
        *(_DWORD *)(v16 + 48) = v27;
        *(_DWORD *)(v16 + 36) = HumanAIContent_LookInApproxDirectionDeleteCB;
        *(_DWORD *)(v16 + 24) = HumanAIContent_LookInApproxDirectionInitCB;
        *(_DWORD *)(v16 + 28) = HumanAIContent_LookInApproxDirectionRunCB;
        v27->uContext.tLookInApproxDirectionContext.nSectorResolution = ptSquadOrder->uContext.tLookInApproxDirectionOrderContext.nSectorResolution;
        qmemcpy(&v27->uContext, &ptSquadOrder->uContext, 0x18u);
        v27->uContext.tLookAtPositionContext.nTimer = (__int64)((double)ptSquadOrder->uContext.tLookInApproxDirectionOrderContext.nTimer
                                                              * ptActiona);
        v27->uContext.tLookInApproxDirectionContext.nStartTime = (__int64)((double)ptSquadOrder->uContext.tLookInApproxDirectionOrderContext.nTimer
                                                                         * ptActiona);
        *(_DWORD *)(v16 + 8) = ptSquadOrder->eOrder;
        HumanAI_AddAction(ptHumanAI, (struct HumanAIActionStackItem_s *)v16);
      }
      return;
    case AISQUAD_ORDER_MOVE_TO_NODE:
      v24 = HumanAI_CreateActionContext(ptHumanAI);
      v5 = (struct HumanAIActionStackItem_s *)HumanAI_GetFreeActionStackItem((int)ptHumanAI);
      v5->bFlags = 0;
      v5->iDelay = ptSquadOrder->iDelay;
      v5->nPriority = HumanAI_GetEventPriority(ptHumanAI, 28);
      v5->pfChildRunCallback = nullptr;
      v5->pfDeleteCallback = nullptr;
      v5->pfRunInitCallback = nullptr;
      v5->ptContext = v24;
      v5->pfInitCallback = (void (__cdecl *)(struct HumanAI_s *, struct HumanAIActionStackItem_s *))HumanAIContent_MoveToNodeSquadOrderInitCB;
      v5->pfRunCallback = HumanAIContent_MoveToNodeSquadOrderRunCB;
      v24->uContext.tLookAtPositionContext.tPosition.vX = ptSquadOrder->uContext.tWaitForLeapFrogContext.tTargetPosition.vX;
      v5->eSquadOrder = ptSquadOrder->eOrder;
      HumanAI_AddAction(ptHumanAI, v5);
      return;
    case AISQUAD_ORDER_FIRE:
      BYTE1(ptHumanAI->tCommon.nPrevNode) = 1;
      HumanAIContent_FireOnTarget(
        ptHumanAI,
        ptSquadOrder->uContext.tFireContext.ptEnemyTarget,
        ptSquadOrder->uContext.tMoveToNodeContext.isRun);
      return;
    case AISQUAD_ORDER_FORMATION:
      v22 = HumanAI_CreateActionContext(ptHumanAI);
      v3 = (struct HumanAIActionStackItem_s *)HumanAI_GetFreeActionStackItem((int)ptHumanAI);
      v3->bFlags = 0;
      v3->iDelay = ptSquadOrder->iDelay;
      v3->nPriority = HumanAI_GetEventPriority(ptHumanAI, 28);
      v3->pfDeleteCallback = HumanAIContent_MoveInFormationSquadOrderDeleteCB;
      v3->pfInitCallback = HumanAIContent_MoveInFormationSquadOrderInitCB;
      v3->pfRunCallback = HumanAIContent_MoveInFormationSquadOrderRunCB;
      v3->ptContext = v22;
      v3->pfChildRunCallback = nullptr;
      v3->pfRunInitCallback = nullptr;
      v22->uContext.tLookAtPositionContext.tPosition = *(struct real64x3_t *)&ptSquadOrder->uContext.tFireContext.nNumTargets;
      v22->uContext.tLookAtPositionContext.nTimer = (int)QTask_NewQTaskRef(ptSquadOrder->uContext.tSetFormationContext.ptLeader);
      v3->eSquadOrder = ptSquadOrder->eOrder;
      HumanAI_AddAction(ptHumanAI, v3);
      return;
    case AISQUAD_ORDER_INQUIRE:
      v23 = HumanAI_CreateActionContext(ptHumanAI);
      v4 = (struct HumanAIActionStackItem_s *)HumanAI_GetFreeActionStackItem((int)ptHumanAI);
      v4->bFlags = 0;
      ptAction = v4;
      v4->iDelay = ptSquadOrder->iDelay;
      v4->nPriority = HumanAI_GetEventPriority(ptHumanAI, 28);
      v4->pfChildRunCallback = nullptr;
      v4->pfDeleteCallback = nullptr;
      v4->pfInitCallback = HumanAIContent_InquireSquadOrderInitCB;
      v4->pfRunCallback = HumanAIContent_InquireSquadOrderRunCB;
      v4->pfRunInitCallback = nullptr;
      v4->ptContext = v23;
      goto LABEL_36;
    case AISQUAD_ORDER_WAIT_FOR_LEAPFROG:
      v23 = HumanAI_CreateActionContext(ptHumanAI);
      v6 = (struct HumanAIActionStackItem_s *)HumanAI_GetFreeActionStackItem((int)ptHumanAI);
      v6->bFlags = 0;
      ptAction = v6;
      v6->iDelay = ptSquadOrder->iDelay;
      v6->nPriority = HumanAI_GetEventPriority(ptHumanAI, 28);
      v6->pfChildRunCallback = nullptr;
      v6->pfDeleteCallback = nullptr;
      v6->pfInitCallback = HumanAIContent_WaitForLeapFrogSquadOrderInitCB;
      v6->pfRunCallback = HumanAIContent_WaitForLeapFrogSquadOrderRunCB;
      v6->pfRunInitCallback = nullptr;
      v6->ptContext = v23;
      goto LABEL_36;
    case AISQUAD_ORDER_ACTIVATE:
      v28 = HumanAI_CreateActionContext(ptHumanAI);
      v17 = (struct HumanAIActionStackItem_s *)HumanAI_GetFreeActionStackItem((int)ptHumanAI);
      v17->bFlags = 1;
      v17->iDelay = 0;
      v17->nPriority = HumanAI_GetEventPriority(ptHumanAI, 21);
      v17->pfChildRunCallback = nullptr;
      v17->pfRunInitCallback = nullptr;
      v17->ptContext = v28;
      v17->pfDeleteCallback = HumanAIContent_ActivateDeleteCB;
      v17->pfInitCallback = HumanAIContent_ActivateInitCB;
      v17->pfRunCallback = HumanAIContent_ActivateRunCB;
      v28->uContext.tIdleContext.nTicksUsed = -1;
      v28->uContext.tActivateContext.isWalkRun = 1;
      nNodeId = ptSquadOrder->uContext.tMoveToNodeContext.nNodeId;
      v28->uContext.tLookAroundContext.eStage = -1;
      v28->uContext.tWaitContext.nTimer = nNodeId;
      v17->eSquadOrder = ptSquadOrder->eOrder;
      HumanAI_AddAction(ptHumanAI, v17);
      return;
    case AISQUAD_ORDER_PATROL:
      v29 = HumanAI_CreateActionContext(ptHumanAI);
      v19 = (struct HumanAIActionStackItem_s *)HumanAI_GetFreeActionStackItem((int)ptHumanAI);
      v19->bFlags = 0;
      v19->iDelay = ptSquadOrder->iDelay;
      v19->nPriority = HumanAI_GetEventPriority(ptHumanAI, 28);
      v19->pfChildRunCallback = nullptr;
      v19->pfRunInitCallback = nullptr;
      v19->pfPushedFromTopCallback = nullptr;
      v19->ptContext = v29;
      v19->pfDeleteCallback = HumanAIContent_PatrolDeleteCB;
      v19->pfInitCallback = HumanAIContent_PatrolInitCB;
      v19->pfRunCallback = HumanAIContent_PatrolRunCB;
      v29->uContext.tIdleContext.nTicksUsed = 0;
      v29->uContext.tWaitContext.nTimer = ptSquadOrder->uContext.tMoveToNodeContext.nNodeId;
      v19->eSquadOrder = ptSquadOrder->eOrder;
      HumanAI_AddAction(ptHumanAI, v19);
      return;
    case AISQUAD_ORDER_THROWGRENADE:
      if ( LOBYTE(ptHumanAI->tCommon.nPrevNode) )
      {
        v2 = (struct HumanAIActionStackItem_s *)HumanAI_GetFreeActionStackItem((int)ptHumanAI);
        v2->bFlags = 1;
        v2->iDelay = 0;
        v2->nPriority = HumanAI_GetEventPriority(ptHumanAI, 21);
        v2->pfChildRunCallback = nullptr;
        v2->pfDeleteCallback = nullptr;
        v2->pfRunInitCallback = nullptr;
        v2->ptContext = nullptr;
        v2->pfInitCallback = HumanAIContent_CombatStandFireGrenadeInitCB;
        v2->pfRunCallback = HumanAIContent_CombatStandFireGrenadeRunCB;
        v2->eSquadOrder = ptSquadOrder->eOrder;
        HumanAI_AddAction(ptHumanAI, v2);
      }
      return;
    case AISQUAD_ORDER_TAKECOVER:
      v23 = HumanAI_CreateActionContext(ptHumanAI);
      v20 = (struct HumanAIActionStackItem_s *)HumanAI_GetFreeActionStackItem((int)ptHumanAI);
      v20->bFlags = 0;
      ptAction = v20;
      v20->iDelay = ptSquadOrder->iDelay;
      v20->nPriority = HumanAI_GetEventPriority(ptHumanAI, 28);
      v20->pfChildRunCallback = nullptr;
      v20->pfRunInitCallback = nullptr;
      v20->pfPushedFromTopCallback = nullptr;
      v20->ptContext = v23;
      v20->pfDeleteCallback = (void (__cdecl *)(struct HumanAI_s *, struct HumanAIActionStackItem_s *))HumanAIContent_TakeCoverDeleteCB;
      v20->pfInitCallback = HumanAIContent_TakeCoverInitCB;
      v20->pfRunCallback = HumanAIContent_TakeCoverRunCB;
      v23->uContext.tRunToCoverContext.tPosition.vZ = ptSquadOrder->uContext.tHoldAreaContext.tPosition.vY;
      v23->uContext.tLookInApproxDirectionContext.nSectorResolution = LODWORD(ptSquadOrder->uContext.tTakeCoverOrderContext.tDirection.vZ);
LABEL_36:
      qmemcpy(&v23->uContext, &ptSquadOrder->uContext, 0x18u);
      ptAction->eSquadOrder = ptSquadOrder->eOrder;
      HumanAI_AddAction(ptHumanAI, ptAction);
      return;
    case AISQUAD_ORDER_VISUALSWEEP:
      v30 = HumanAI_CreateActionContext(ptHumanAI);
      v21 = (struct HumanAIActionStackItem_s *)HumanAI_GetFreeActionStackItem((int)ptHumanAI);
      v21->bFlags = 0;
      v21->iDelay = ptSquadOrder->iDelay;
      v21->nPriority = HumanAI_GetEventPriority(ptHumanAI, 28);
      v21->pfChildRunCallback = nullptr;
      v21->pfDeleteCallback = nullptr;
      v21->pfRunInitCallback = nullptr;
      v21->pfPushedFromTopCallback = nullptr;
      v21->ptContext = v30;
      v21->pfInitCallback = HumanAIContent_LookAroundInitCB;
      v21->pfRunCallback = HumanAIContent_LookAroundRunCB;
      v30->uContext.tCombatContext.nFireSequences = ptSquadOrder->uContext.tVisualSweepOrderContext.isCrouch;
      HumanAIContent_VisualSweepPattern = (HumanAIContent_VisualSweepPattern + 1) % 6;
      HumanAI_AddAction(ptHumanAI, v21);
      return;
    default:
      return;
  }
}

// source: j/0/humanai/humanaicontent.c:4051  [anchor-mhash]
enum bool __cdecl HumanAIContent_ReloadWeaponCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  struct Weapon_s *ptNext; // eax
  struct WeaponTypeItem_s *ptActiveWeapon; // ecx
  struct WeaponGetFireTypeAmmoContext_s tAmmoContext; // [esp+8h] [ebp-14h] BYREF

  ptNext = (struct Weapon_s *)ptHumanAI->tQTask.ptParent[33].ptNext;
  if ( !ptNext )
    return true;
  ptActiveWeapon = ptNext->tPrivate.ptActiveWeapon;
  if ( !ptActiveWeapon )
    return true;
  if ( !ptActiveWeapon->ptWeaponType )
    return true;
  Weapon_GetFireTypeAmmoInfoFromWeaponTypeItem(ptNext, ptNext->tPrivate.ptActiveWeapon, 0, &tAmmoContext);
  if ( tAmmoContext.nAmmoInWeapon )
    return true;
  ptHumanAI->avChannel[16] = 0.0;
  ptHumanAI->avChannel[18] = 1.0;
  HumanAI_FaceTarget(ptHumanAI);
  return false;
}

// source: j/0/humanai/humanaicontent.c:4103  [anchor-caller]
enum bool __cdecl HumanAIContent_FireAtTargetPositionCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct WeaponType_s *ptWeaponType; };
    struct { char igi2_o1[4]; struct WeaponGetFireTypeAmmoContext_s tAmmoContext; };
    char igi2_extent[24];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptParent; // ebp
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptTail; // eax
  struct QTask_s *v7; // eax
  struct QTask_s *v9; // esi
  struct QTask_s *v10; // eax
  double v11; // st3
  long double v12; // st7
  int ptAmmoType; // eax
  double RandomNumberReal32; // st7
  struct QTask_s *v15; // eax
  float ptHumanAIa = *(float *)&ptHumanAI; // [esp+28h] [ebp+4h] ARGSLOT

  ptParent = ptHumanAI->tQTask.ptParent;
  Weapon_GetFireTypeAmmoInfoFromWeaponTypeItem(
    (struct Weapon_s *)ptParent[33].ptNext,
    (struct WeaponTypeItem_s *)ptParent[33].ptNext[1].ptPrev,
    0,
    &igi2_frame.tAmmoContext);
  ptNext = ptHumanAI->tQTask.ptParent[33].ptNext;
  if ( ptNext )
  {
    ptPrev = ptNext[1].ptPrev;
    if ( ptPrev )
    {
      ptTail = ptPrev->tQTaskChildren.ptTail;
      if ( ptTail )
      {
        if ( ptTail[16].ptParent == (struct QTask_s *)3 && ptTail[17].tQTaskRefList.ptTail == (struct QReference_s *)8 )
        {
          v7 = ptParent[31].ptPrev;
          if ( v7 )
          {
            if ( v7 != (struct QTask_s *)27 )
              return false;
          }
        }
      }
    }
  }
  if ( !igi2_frame.tAmmoContext.nAmmoInWeapon )
  {
    ptHumanAI->tCommon.nCurrentNode = 0;
    ptHumanAI->tCommon.nDestinationNode = 0;
    ptActionStackItem->pfChildRunCallback = HumanAIContent_ReloadWeaponCB;
    return false;
  }
  HumanAIContent_SetChannel(ptHumanAI, 5, 1.0);
  if ( !HumanAI_GetTargetQTask(ptHumanAI, true) )
    return true;
  v9 = ptHumanAI->tQTask.ptParent;
  v10 = v9[33].ptNext[1].ptPrev;
  if ( !v10 )
    return true;
  igi2_frame.ptWeaponType = (struct WeaponType_s *)v10->tQTaskChildren.ptTail;
  if ( !igi2_frame.ptWeaponType )
    return true;
  *(float *)&igi2_frame.tAmmoContext.ptAmmoType = *(double *)&ptHumanAI[1].tQTask.ptNext - *(double *)&v9[1].ptNext;
  *(float *)&igi2_frame.tAmmoContext.nAmmoInWeapon = *(double *)&ptHumanAI[1].tQTask.tQTaskChildren.ptHead
                                        - *(double *)&v9[1].tQTaskChildren.ptHead;
  v11 = *(double *)&ptHumanAI[1].tQTask.tQTaskChildren.ptTail - *(double *)&v9[1].tQTaskChildren.ptTail;
  v12 = sqrt(
          *(float *)&igi2_frame.tAmmoContext.ptAmmoType * *(float *)&igi2_frame.tAmmoContext.ptAmmoType
        + *(float *)&igi2_frame.tAmmoContext.nAmmoInWeapon * *(float *)&igi2_frame.tAmmoContext.nAmmoInWeapon
        + v11 * v11);
  ptHumanAIa = v12;
  if ( v12 > 450560.0 )
  {
    if ( HumanAI_IsRPGSoldier(ptHumanAI) )
      return true;
  }
  if ( ptHumanAI->tCommon.nCurrentNode )
  {
    v15 = ptParent[33].ptNext;
    if ( v15[1].tQTaskChildren.ptTail )
    {
      v15[2].ptParent = (struct QTask_s *)1;
      v15[1].tQTaskChildren.ptTail = nullptr;
    }
    --ptHumanAI->tCommon.nCurrentNode;
  }
  else if ( ptHumanAI->tCommon.nDestinationNode <= 0 )
  {
    BYTE1(ptHumanAI->tCommon.nPrevNode) = 0;
    Weapon_GetFireTypeAmmoInfoFromWeaponTypeItem(
      (struct Weapon_s *)v9[33].ptNext,
      (struct WeaponTypeItem_s *)v9[33].ptNext[1].ptPrev,
      0,
      &igi2_frame.tAmmoContext);
    *(_QWORD *)&igi2_frame.tAmmoContext.ptAmmoType = (__int64)((double)igi2_frame.tAmmoContext.nRoundsPerClip
                                                  * ptHumanAI->tTweakParameters.vTrackingTimeout);
    ptAmmoType = (int)igi2_frame.tAmmoContext.ptAmmoType;
    ptHumanAI->tCommon.nDestinationNode = (int)igi2_frame.tAmmoContext.ptAmmoType;
    if ( ptAmmoType >= 5 )
    {
      if ( ptAmmoType > 10 )
        ptAmmoType = 10;
    }
    else
    {
      ptAmmoType = 5;
    }
    ptHumanAI->tCommon.nDestinationNode = ptAmmoType;
    RandomNumberReal32 = Random_GetRandomNumberReal32(&Game_ptGame->tRunRandomState);
    if ( igi2_frame.ptWeaponType->anRoundsInSuccession[0] <= 1 )
    {
      *(_QWORD *)&igi2_frame.tAmmoContext.ptAmmoType = (__int64)((0.05000000074505806 * RandomNumberReal32 + 0.1) * 30.0);
      ptHumanAI->tCommon.nCurrentNode = (int)igi2_frame.tAmmoContext.ptAmmoType;
      return false;
    }
    *(_QWORD *)&igi2_frame.tAmmoContext.ptAmmoType = (__int64)(((double)AISquad_GetMemberCount(v9->ptParent)
                                                   * RandomNumberReal32
                                                   * 0.1
                                                   + 0.4000000059604645)
                                                  * 30.0);
    ptHumanAI->tCommon.nCurrentNode = (int)igi2_frame.tAmmoContext.ptAmmoType;
    if ( ptHumanAIa < 40960.0 )
    {
      ptHumanAI->tCommon.nDestinationNode *= 2;
      return false;
    }
  }
  else if ( BYTE1(ptHumanAI->tCommon.nPrevNode) )
  {
    HumanAIContent_InitFire(ptHumanAI, 0);
    if ( HumanAIContent_RunFire(ptHumanAI) )
    {
      --ptHumanAI->tCommon.nDestinationNode;
      return false;
    }
  }
  return false;
}

// source: j/0/humanai/humanaicontent.c:4313  [anchor-hash]
struct HumanAI_s *__cdecl HumanAIContent_FireOnTarget(
        struct HumanAI_s *ptHumanAI,
        struct AISquadEnemyTargetData_s *ptTargets,
        int nNumTargets)
{
  void (__cdecl *pfRunCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // edx
  unsigned int bQTaskMask; // ecx

  pfRunCallback = ptHumanAI->atActionStackItemList[0].pfRunCallback;
  if ( *(_DWORD *)pfRunCallback )
  {
    if ( pfRunCallback )
    {
      bQTaskMask = ptHumanAI->tAIDetection.atListItems[0].bQTaskMask;
      if ( *(_DWORD *)bQTaskMask )
      {
        if ( bQTaskMask )
        {
          while ( 2 )
          {
            for ( ptHumanAI = nullptr; (int)ptHumanAI < 3; ptHumanAI = (struct HumanAI_s *)((char *)ptHumanAI + 1) )
            {
              if ( ptHumanAI->zStandActionAnimation[bQTaskMask + 11] )
              {
                ptHumanAI = *((struct HumanAI_s **)pfRunCallback + 11);
                if ( !ptHumanAI )
                  *((_DWORD *)pfRunCallback + 11) = HumanAIContent_FireAtTargetPositionCB;
                return ptHumanAI;
              }
            }
            bQTaskMask = *(_DWORD *)bQTaskMask;
            if ( *(_DWORD *)bQTaskMask && bQTaskMask )
              continue;
            break;
          }
        }
      }
    }
  }
  return ptHumanAI;
}

// source: j/0/humanai/humanaicontent.c:4362  [anchor-mhash]
void __cdecl HumanAIContent_MoveInFormationSquadOrderInitCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  union __anon_1ce5 *p_uContext; // eax
  struct QTask_s *ptParent; // eax
  float ptActionStackItema = *(float *)&ptActionStackItem; // [esp+8h] [ebp+8h] ARGSLOT

  p_uContext = &ptActionStackItem->ptContext->uContext;
  p_uContext->tLookInApproxDirectionContext.nStartTime = -1;
  p_uContext->tLookInApproxDirectionContext.nSectorResolution = 0;
  ptParent = ptHumanAI->tQTask.ptParent;
  if ( ptParent->eQTaskType == HumanSoldier_eQTaskType )
  {
    ptActionStackItema = 0.0;
    if ( !LOBYTE(ptParent[75].ptPrev) )
      ptActionStackItema = 1.0;
    HumanAIContent_SetChannel(ptHumanAI, 0, ptActionStackItema);
  }
}

// source: j/0/humanai/humanaicontent.c:4381  [anchor-caller]
void __cdecl HumanAIContent_MoveInFormationSquadOrderRunCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct AIGraphNode_s *ptAIGraphNode; };
    struct { char igi2_o1[4]; struct HumanAI_s *ptLeaderHumanAI; };
    struct { char igi2_o2[12]; float Real32x3_Rotate_tTemp; };
    struct { char igi2_o3[16]; float Real32x3_Rotate_tTemp_4; };
    struct { char igi2_o4[20]; float Real32x3_Rotate_tTemp_8; };
    struct { char igi2_o5[20]; float Real32x3_Rotate_tTemp_8a; };
    struct { char igi2_o6[24]; struct real64x3_t tReal64x3; };
    char igi2_extent[48];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct HumanAIActionContext_t *ptContext; // ebx
  struct HumanAI_s *v3; // ecx
  union __anon_1ce5 *p_uContext; // ebx
  void (__cdecl *pfDeleteCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // eax
  struct HumanAIActionContext_t *v6; // eax
  struct QTask_s *ptParent; // edi
  double v8; // st6
  struct Graph_s *v9; // esi
  struct AIGraphNode_s *ClosestNodeFromStartingNode; // eax
  struct AIGraphNode_s *Node; // eax
  struct HumanAI_s *v12; // ebx
  struct QTask_s *v13; // esi
  enum bool (__cdecl *pfChildRunCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // eax

  ptContext = ptActionStackItem->ptContext;
  v3 = *(struct HumanAI_s **)(ptContext->uContext.tLookAtPositionContext.nTimer + 8);
  p_uContext = &ptContext->uContext;
  igi2_frame.ptLeaderHumanAI = v3;
  if ( !v3 )
  {
    pfDeleteCallback = ptActionStackItem->pfDeleteCallback;
    if ( pfDeleteCallback )
      pfDeleteCallback(ptHumanAI, ptActionStackItem);
    Node_Remove(ptActionStackItem);
    v6 = ptActionStackItem->ptContext;
    ptActionStackItem->isUsed = 0;
    if ( v6 )
    {
      v6->tNode.ptPrev = nullptr;
      v6->tNode.ptNext = nullptr;
      List_AddTail(v6, (int)&ptHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID);
      ptActionStackItem->ptContext = nullptr;
    }
    return;
  }
  ptParent = v3->tQTask.ptParent;
  if ( LOBYTE(ptParent[29].tQTaskRefList.ptHead) )
  {
    HumanAI_PopActionStackItem(ptHumanAI, ptActionStackItem);
    return;
  }
  v8 = *(float *)&ptParent[3].tQTaskChildren.ptTail * p_uContext->tLookAroundContext.vCurrentRotation
     + *(float *)&ptParent[3].tQTaskRefList.ptMiddle * p_uContext->tHoldAreaContext.tDirection.vZ
     + *(float *)&ptParent[3].tQTaskRefList.ptHead * p_uContext->tLookAroundContext.vCurrentTarget;
  igi2_frame.Real32x3_Rotate_tTemp_8a = *(float *)&ptParent[3].tQTaskRefList.ptTail
                           * p_uContext->tLookAroundContext.vCurrentRotation
                           + *(float *)&ptParent[3].eQTaskType * p_uContext->tHoldAreaContext.tDirection.vZ
                           + *(float *)&ptParent[3].ptParent * p_uContext->tLookAroundContext.vCurrentTarget;
  igi2_frame.tReal64x3.vX = *(float *)&ptParent[3].tQTaskChildren.ptMiddle * p_uContext->tHoldAreaContext.tDirection.vZ
               + *(float *)&ptParent[3].tQTaskChildren.ptHead * p_uContext->tLookAroundContext.vCurrentTarget
               + *(float *)&ptParent[3].ptPrev * p_uContext->tLookAroundContext.vCurrentRotation
               + *(double *)&ptParent[1].ptNext;
  igi2_frame.tReal64x3.vY = v8 + *(double *)&ptParent[1].tQTaskChildren.ptHead;
  igi2_frame.tReal64x3.vZ = igi2_frame.Real32x3_Rotate_tTemp_8a + *(double *)&ptParent[1].tQTaskChildren.ptTail;
  v9 = *(struct Graph_s **)&v3->zScriptFile[36];
  if ( p_uContext->tLookInApproxDirectionContext.nSectorResolution <= 0 )
  {
    Node = (struct AIGraphNode_s *)Graph_GetNode(v9, HIDWORD(v3->tCommon.tAimPosition.vY));
    ClosestNodeFromStartingNode = AIGraph_GetClosestNodeFromStartingNode(
                                    *(struct AIGraph_t **)&igi2_frame.ptLeaderHumanAI->zScriptFile[36],
                                    Node,
                                    &igi2_frame.tReal64x3,
                                    20);
    igi2_frame.ptAIGraphNode = ClosestNodeFromStartingNode;
    p_uContext->tLookInApproxDirectionContext.nStartTime = ClosestNodeFromStartingNode->tGraphNode.nID;
    p_uContext->tLookInApproxDirectionContext.nSectorResolution = 30;
  }
  else
  {
    ClosestNodeFromStartingNode = (struct AIGraphNode_s *)Graph_GetNode(
                                                            v9,
                                                            p_uContext->tLookInApproxDirectionContext.nStartTime);
    igi2_frame.ptAIGraphNode = ClosestNodeFromStartingNode;
    --p_uContext->tLookInApproxDirectionContext.nSectorResolution;
  }
  if ( ClosestNodeFromStartingNode->tGraphNode.nID == HIDWORD(igi2_frame.ptLeaderHumanAI->tCommon.tAimPosition.vY)
    || ClosestNodeFromStartingNode->tGraphNode.nID == LODWORD(igi2_frame.ptLeaderHumanAI->tCommon.tAimPosition.vZ) )
  {
    v12 = ptHumanAI;
    LODWORD(ptHumanAI->tCommon.tAimPosition.vZ) = HIDWORD(ptHumanAI->tCommon.tAimPosition.vY);
LABEL_26:
    HumanAI_PopActionStackItem(v12, ptActionStackItem);
    return;
  }
  v12 = ptHumanAI;
  v13 = ptHumanAI->tQTask.ptParent;
  Graph_GetNodePos(&igi2_frame.tReal64x3, &ClosestNodeFromStartingNode->tGraphNode);
  igi2_frame.Real32x3_Rotate_tTemp = igi2_frame.tReal64x3.vX - *(double *)&v13[1].ptNext;
  igi2_frame.Real32x3_Rotate_tTemp_4 = igi2_frame.tReal64x3.vY - *(double *)&v13[1].tQTaskChildren.ptHead;
  igi2_frame.Real32x3_Rotate_tTemp_8 = igi2_frame.tReal64x3.vZ - *(double *)&v13[1].tQTaskChildren.ptTail;
  if ( LOBYTE(ptParent[75].ptPrev) )
    HumanAI_MakeAIWalk(ptHumanAI);
  else
    HumanAI_MakeAIRun(ptHumanAI);
  if ( sqrt(
         igi2_frame.Real32x3_Rotate_tTemp * igi2_frame.Real32x3_Rotate_tTemp
       + igi2_frame.Real32x3_Rotate_tTemp_4 * igi2_frame.Real32x3_Rotate_tTemp_4
       + igi2_frame.Real32x3_Rotate_tTemp_8 * igi2_frame.Real32x3_Rotate_tTemp_8) > 8192.0 )
  {
    HumanAnim_ScaleAnimationTimeStep(v13, 1.2999999523162842);
    v13[75].tQTaskChildren.ptTail = (struct QTask_s *)1067869798;
  }
  if ( HumanAI_AttackMoveCharacterToNode(ptHumanAI, igi2_frame.ptAIGraphNode->tGraphNode.nID) )
    goto LABEL_26;
  if ( (ptHumanAI->tAStarSearchData.bFlags & 1) != 0 )
    HumanAI_FaceTarget(ptHumanAI);
  pfChildRunCallback = ptActionStackItem->pfChildRunCallback;
  if ( pfChildRunCallback && pfChildRunCallback(ptHumanAI, ptActionStackItem) )
    ptActionStackItem->pfChildRunCallback = nullptr;
}

// source: j/0/humanai/humanaicontent.c:4533  [size]
void __cdecl HumanAIContent_MoveInFormationSquadOrderDeleteCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  QReference_Delete(
    ptActionStackItem->ptContext->uContext.tSetCombatEventContext.ptReferenceQTaskRef,
    &QTask_tQTaskRefPool);
}

// source: j/0/humanai/humanaicontent.c:4549  [anchor-mhash]
void __cdecl HumanAIContent_InquireSquadOrderInitCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  union __anon_1ce5 *p_uContext; // esi

  p_uContext = &ptActionStackItem->ptContext->uContext;
  AIGraph_GetClosestNode(
    (struct AIGraphNode_s **)&ptActionStackItem,
    *(struct AIGraph_t **)&ptHumanAI->zScriptFile[36],
    (struct real64x3_t *)p_uContext,
    false);
  p_uContext->tLookAtPositionContext.nTimer = (int)ptActionStackItem->tNode.ptNext;
}

// source: j/0/humanai/humanaicontent.c:4570  [anchor-mhash]
void __cdecl HumanAIContent_InquireSquadOrderRunCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  struct HumanAIActionContext_t *ptContext; // ebx
  double vX; // st7
  struct real64x3_t *p_uContext; // ebx
  struct QTask_s *ptParent; // ecx
  double v6; // st6
  int vX_low; // [esp-4h] [ebp-1Ch]
  double v8; // [esp+10h] [ebp-8h]
  float v9; // [esp+10h] [ebp-8h]

  ptContext = ptActionStackItem->ptContext;
  vX = ptContext->uContext.tLookAtPositionContext.tPosition.vX;
  p_uContext = (struct real64x3_t *)&ptContext->uContext;
  ptParent = ptHumanAI->tQTask.ptParent;
  v6 = p_uContext->vY - *(double *)&ptParent[1].tQTaskChildren.ptHead;
  v8 = p_uContext->vZ - *(double *)&ptParent[1].tQTaskChildren.ptTail;
  if ( sqrt((vX - *(double *)&ptParent[1].ptNext) * (vX - *(double *)&ptParent[1].ptNext) + v6 * v6 + v8 * v8) <= 20480.0 )
  {
    if ( (ptHumanAI->anEventPriorityList[5] & 4) != 0 )
    {
      ptHumanAI->avChannel[8] = 0.41887903213500977;
      ptHumanAI->avChannel[9] = 0.20943951606750488;
    }
    else
    {
      ptHumanAI->avChannel[8] = 0.20943951606750488;
      ptHumanAI->avChannel[9] = 0.10471975803375244;
    }
    HumanAI_FacePosition(ptHumanAI, p_uContext, 0.0872664675116539, true);
  }
  else
  {
    if ( ptParent->eQTaskType == HumanSoldier_eQTaskType )
    {
      v9 = 1.0;
      if ( !LOBYTE(ptParent[75].ptPrev) )
        v9 = 0.0;
      HumanAIContent_SetChannel(ptHumanAI, 0, v9);
    }
    vX_low = LODWORD(p_uContext[1].vX);
    ptHumanAI->avChannel[8] = 0.3141592741012573;
    ptHumanAI->avChannel[9] = 0.3141592741012573;
    HumanAI_MoveCharacterToNode(ptHumanAI, vX_low);
  }
}

// source: j/0/humanai/humanaicontent.c:4609  [size]
void __cdecl HumanAIContent_MoveToNodeSquadOrderInitCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  ;
}

// source: j/0/humanai/humanaicontent.c:4625  [anchor-mhash]
void __cdecl HumanAIContent_MoveToNodeSquadOrderRunCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  struct HumanAIActionStackItem_s *v2; // esi
  enum bool (__cdecl *pfChildRunCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // eax
  union __anon_1ce5 *p_uContext; // ebx
  struct QTask_s *ptParent; // eax
  unsigned __int16 eQTaskType; // cx
  int nTimer; // [esp-4h] [ebp-14h]
  int v8; // [esp-4h] [ebp-14h]
  float v9; // [esp+Ch] [ebp-4h]
  float v10; // [esp+Ch] [ebp-4h]

  v2 = ptActionStackItem;
  pfChildRunCallback = ptActionStackItem->pfChildRunCallback;
  p_uContext = &ptActionStackItem->ptContext->uContext;
  if ( pfChildRunCallback && pfChildRunCallback(ptHumanAI, ptActionStackItem) )
    ptActionStackItem->pfChildRunCallback = nullptr;
  ptParent = ptHumanAI->tQTask.ptParent;
  eQTaskType = ptParent->eQTaskType;
  if ( p_uContext->tIdleContext.nTicksUsed )
  {
    if ( eQTaskType == HumanSoldier_eQTaskType )
    {
      v9 = 1.0;
      if ( !LOBYTE(ptParent[75].ptPrev) )
        v9 = 0.0;
      HumanAIContent_SetChannel(ptHumanAI, 0, v9);
      v2 = ptActionStackItem;
    }
    nTimer = p_uContext->tWaitContext.nTimer;
    ptHumanAI->avChannel[8] = 0.3141592741012573;
    ptHumanAI->avChannel[9] = 0.3141592741012573;
    if ( HumanAI_MoveCharacterToNode(ptHumanAI, nTimer) )
    {
      HumanAI_FaceTarget(ptHumanAI);
      HumanAI_PopActionStackItem(ptHumanAI, v2);
    }
  }
  else
  {
    if ( eQTaskType == HumanSoldier_eQTaskType )
    {
      v10 = 0.0;
      if ( !LOBYTE(ptParent[75].ptPrev) )
        v10 = 1.0;
      HumanAIContent_SetChannel(ptHumanAI, 0, v10);
      v2 = ptActionStackItem;
    }
    v8 = p_uContext->tWaitContext.nTimer;
    ptHumanAI->avChannel[8] = 0.20943951606750488;
    ptHumanAI->avChannel[9] = 0.20943951606750488;
    if ( HumanAI_MoveCharacterToNode(ptHumanAI, v8) )
      HumanAI_PopActionStackItem(ptHumanAI, v2);
  }
}

// source: j/0/humanai/humanaicontent.c:4671  [size]
void __cdecl HumanAIContent_WaitForLeapFrogSquadOrderInitCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  ptActionStackItem->ptContext->uContext.tLookAtPositionContext.nTimer = -1;
  LODWORD(ptHumanAI->tCommon.tAimPosition.vZ) = HIDWORD(ptHumanAI->tCommon.tAimPosition.vY);
}

// source: j/0/humanai/humanaicontent.c:4689  [anchor-mhash]
void __cdecl HumanAIContent_WaitForLeapFrogSquadOrderRunCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  enum bool (__cdecl *pfChildRunCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // ecx

  pfChildRunCallback = ptActionStackItem->pfChildRunCallback;
  if ( pfChildRunCallback )
  {
    if ( pfChildRunCallback(ptHumanAI, ptActionStackItem) )
      ptActionStackItem->pfChildRunCallback = nullptr;
  }
  else
  {
    ptActionStackItem->ptContext->uContext.tLookAtPositionContext.nTimer = -1;
    HumanAI_FaceTarget(ptHumanAI);
  }
}

// source: j/0/humanai/humanaicontent.c:4740  [size]
void __cdecl HumanAIContent_OffensiveCombatInitCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  ptActionStackItem->ptContext->uContext.tWaitContext.nTimer = -1;
  ptActionStackItem->pfRunInitCallback = (void (__cdecl *)(struct HumanAI_s *, struct HumanAIActionStackItem_s *))HumanAIContent_OffensiveCombatInitCB;
  ptActionStackItem->pfRunCallback = HumanAIContent_OffensiveCombatRunCB;
}

// source: j/0/humanai/humanaicontent.c:4759  [anchor-mhash]
void __cdecl HumanAIContent_OffensiveCombatRunCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  #pragma pack(push, 1)
  union
  {
    struct { int nTimer; };
    struct { char igi2_o1[20]; struct AIGraphNode_s *ptAIGraphNode; };
    struct { char igi2_o2[24]; struct HumanAIOffensiveCombatActionContext_s *ptContext; };
    struct { char igi2_o3[28]; double v15; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  enum bool (__cdecl *pfChildRunCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // eax
  union __anon_1ce5 *p_uContext; // ebx
  double *ptParent; // ebx
  struct QTask_s *v5; // esi
  struct QTask_s *TargetQTask; // eax
  _DWORD *i; // edx
  int v8; // ecx
  double v9; // st7
  double v10; // st6
  long double v11; // st7

  pfChildRunCallback = ptActionStackItem->pfChildRunCallback;
  p_uContext = &ptActionStackItem->ptContext->uContext;
  igi2_frame.ptContext = (struct HumanAIOffensiveCombatActionContext_s *)p_uContext;
  if ( pfChildRunCallback )
  {
    if ( pfChildRunCallback(ptHumanAI, ptActionStackItem) )
      ptActionStackItem->pfChildRunCallback = nullptr;
  }
  else if ( HumanAI_GetTargetQTask(ptHumanAI, true) )
  {
    p_uContext->tWaitContext.nTimer = -1;
    HumanAI_FaceTarget(ptHumanAI);
  }
  else if ( p_uContext->tWaitContext.nTimer == -1 )
  {
    ptParent = (double *)ptHumanAI->tQTask.ptParent;
    v5 = nullptr;
    TargetQTask = HumanAI_GetTargetQTask(ptHumanAI, true);
    if ( !TargetQTask )
    {
      for ( i = (_DWORD *)ptHumanAI->tAIDetection.atListItems[0].bQTaskMask; *i && i; i = (_DWORD *)*i )
      {
        v8 = *(_DWORD *)(i[2] + 8);
        if ( v8 )
        {
          if ( !*(_BYTE *)(v8 + 1180) )
          {
            v9 = ptParent[5] - *(double *)(v8 + 40);
            v10 = ptParent[6] - *(double *)(v8 + 48);
            igi2_frame.v15 = ptParent[7] - *(double *)(v8 + 56);
            v11 = sqrt(v9 * v9 + v10 * v10 + igi2_frame.v15 * igi2_frame.v15);
            if ( !v5 || v11 < *(float *)&igi2_frame.ptAIGraphNode )
            {
              *(float *)&igi2_frame.ptAIGraphNode = v11;
              v5 = (struct QTask_s *)v8;
            }
          }
        }
      }
      TargetQTask = v5;
      if ( !v5 )
        goto LABEL_19;
    }
    AIGraph_GetClosestNode(
      &igi2_frame.ptAIGraphNode,
      *(struct AIGraph_t **)&ptHumanAI->zScriptFile[36],
      (struct real64x3_t *)&TargetQTask[1],
      false);
    if ( *(float *)&igi2_frame.ptAIGraphNode != 0.0 )
      igi2_frame.ptContext->nDestNodeID = igi2_frame.ptAIGraphNode->tGraphNode.nID;
    else
LABEL_19:
      HumanAI_PopActionStackItem(ptHumanAI, ptActionStackItem);
  }
  else
  {
    HumanAI_MakeAIRun(ptHumanAI);
    igi2_frame.nTimer = p_uContext->tWaitContext.nTimer;
    ptHumanAI->avChannel[8] = 0.3141592741012573;
    ptHumanAI->avChannel[9] = 0.3141592741012573;
    if ( HumanAI_MoveCharacterToNode(ptHumanAI, igi2_frame.nTimer) )
      HumanAI_PopActionStackItem(ptHumanAI, ptActionStackItem);
  }
}

// source: j/0/humanai/humanaicontent.c:4826  [size]
void __cdecl HumanAIContent_DefensiveCombatInitCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  ptActionStackItem->pfRunInitCallback = (void (__cdecl *)(struct HumanAI_s *, struct HumanAIActionStackItem_s *))HumanAIContent_DefensiveCombatInitCB;
  ptActionStackItem->pfRunCallback = HumanAIContent_DefensiveCombatRunCB;
}

// source: j/0/humanai/humanaicontent.c:4840  [anchor-mhash]
void __cdecl HumanAIContent_DefensiveCombatRunCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  struct HumanAIActionStackItem_s *v2; // esi
  enum bool (__cdecl *pfChildRunCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // eax
  int v4; // ebp
  double *ptParent; // ebx
  _DWORD *i; // edx
  int v7; // ecx
  double v8; // st3
  long double v9; // st4
  float v10; // [esp+8h] [ebp-Ch]
  float v11; // [esp+Ch] [ebp-8h]

  v2 = ptActionStackItem;
  pfChildRunCallback = ptActionStackItem->pfChildRunCallback;
  v4 = 0;
  if ( pfChildRunCallback )
  {
    if ( pfChildRunCallback(ptHumanAI, ptActionStackItem) )
      ptActionStackItem->pfChildRunCallback = nullptr;
  }
  else
  {
    ptParent = (double *)ptHumanAI->tQTask.ptParent;
    if ( HumanAI_GetTargetQTask(ptHumanAI, true) )
      goto LABEL_17;
    for ( i = (_DWORD *)ptHumanAI->tAIDetection.atListItems[0].bQTaskMask; *i && i; i = (_DWORD *)*i )
    {
      v7 = *(_DWORD *)(i[2] + 8);
      if ( v7 )
      {
        if ( !*(_BYTE *)(v7 + 1180) )
        {
          v10 = ptParent[5] - *(double *)(v7 + 40);
          v11 = ptParent[6] - *(double *)(v7 + 48);
          v8 = ptParent[7] - *(double *)(v7 + 56);
          v9 = sqrt(v10 * v10 + v11 * v11 + v8 * v8);
          if ( !v4 || v9 < *(float *)&ptActionStackItem )
          {
            *(float *)&ptActionStackItem = v9;
            v4 = *(_DWORD *)(i[2] + 8);
          }
        }
      }
    }
    if ( v4 )
LABEL_17:
      HumanAI_FaceTarget(ptHumanAI);
    else
      HumanAI_PopActionStackItem(ptHumanAI, v2);
  }
}

// source: j/0/humanai/humanaicontent.c:4870  [anchor-mhash]
void __cdecl HumanAIContent_CombatStandFireGrenadeInitCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  struct QTask_s *ptParent; // ebp
  void (__cdecl *pfDeleteCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // eax
  struct HumanAIActionContext_t *ptContext; // eax
  double v6; // st4
  long double v7; // st5
  int nTask; // ecx
  int v9; // esi
  struct QTask_s **ptQTask; // ebx
  struct QTask_s *v11; // edx
  double v12; // st7
  double v13; // st7
  double v14; // st7
  float tReal32x3; // [esp+10h] [ebp-Ch]
  float tReal32x3_4a; // [esp+14h] [ebp-8h]
  float tReal32x3_4; // [esp+14h] [ebp-8h]
  float tReal32x3_8; // [esp+18h] [ebp-4h]
  struct HumanAI_s *ptHumanAIa = *(struct HumanAI_s * *)&ptHumanAI; // [esp+20h] [ebp+4h] ARGSLOT

  ptParent = ptHumanAI->tQTask.ptParent;
  if ( LOBYTE(ptHumanAI->tCommon.nPrevNode) )
  {
    tReal32x3 = *(double *)&ptParent[1].ptNext - *(double *)&ptHumanAI->tCommon.nIgnoreVisibilityFactorTimer;
    tReal32x3_4a = *(double *)&ptParent[1].tQTaskChildren.ptHead - *(double *)&ptHumanAI->tCommon.isDetectionSoundPlayed;
    v6 = *(double *)&ptParent[1].tQTaskChildren.ptTail - ptHumanAI->tCommon.tAimPosition.vX;
    v7 = sqrt(v6 * v6 + tReal32x3 * tReal32x3 + tReal32x3_4a * tReal32x3_4a);
    if ( v7 < 28672.0
      || v7 > 163840.0
      || Real64x3_NullVector((struct real64x3_t *)&ptHumanAI->tCommon.nIgnoreVisibilityFactorTimer) )
    {
LABEL_31:
      HumanAI_PopActionStackItem(ptHumanAI, ptActionStackItem);
    }
    else
    {
      nTask = Human_ptQTaskList->nTask;
      v9 = 0;
      ptHumanAIa = (struct HumanAI_s *)Human_ptQTaskList->nTask;
      if ( Human_ptQTaskList->nTask > 0 )
      {
        ptQTask = Human_ptQTaskList->ptQTask;
        do
        {
          v11 = *ptQTask;
          if ( *ptQTask != ptParent )
          {
            if ( QTask_IsQTaskTypeDerived(v11->eQTaskType, HumanSoldier_eQTaskType)
              && BYTE1(v11[29].tQTaskRefList.ptHead)
              && !LOBYTE(v11[29].tQTaskRefList.ptHead)
              && v11[10].tQTaskRefList.ptTail == ptParent[10].tQTaskRefList.ptTail )
            {
              v12 = *(double *)&v11[1].ptNext - *(double *)&ptHumanAI->tCommon.nIgnoreVisibilityFactorTimer;
              tReal32x3_4 = *(double *)&v11[1].tQTaskChildren.ptHead
                          - *(double *)&ptHumanAI->tCommon.isDetectionSoundPlayed;
              tReal32x3_8 = *(double *)&v11[1].tQTaskChildren.ptTail - ptHumanAI->tCommon.tAimPosition.vX;
              if ( v12 < 0.0 )
                v12 = -v12;
              if ( v12 < 28672.0 )
              {
                v13 = tReal32x3_4;
                if ( tReal32x3_4 < 0.0 )
                  v13 = -v13;
                if ( v13 < 28672.0 )
                {
                  v14 = tReal32x3_8;
                  if ( tReal32x3_8 < 0.0 )
                    v14 = -v14;
                  if ( v14 < 28672.0 )
                    goto LABEL_31;
                }
              }
            }
            nTask = (int)ptHumanAIa;
          }
          ++v9;
          ++ptQTask;
        }
        while ( v9 < nTask );
      }
      HumanAIContent_SetChannel(ptHumanAI, 7, 1.0);
      if ( ptParent[31].ptPrev == (struct QTask_s *)12
        && HumanAI_FacePositionSelectSpeed(
             ptHumanAI,
             (struct real64x3_t *)&ptHumanAI->tCommon.nIgnoreVisibilityFactorTimer,
             0.1745329350233078,
             true) )
      {
        ptActionStackItem->pfRunCallback = HumanAIContent_CombatStandFireGrenadeRunCB;
      }
      else
      {
        ptActionStackItem->pfRunCallback = HumanAIContent_CombatStandFireGrenadeInitCB;
      }
    }
  }
  else
  {
    pfDeleteCallback = ptActionStackItem->pfDeleteCallback;
    if ( pfDeleteCallback )
      pfDeleteCallback(ptHumanAI, ptActionStackItem);
    Node_Remove(ptActionStackItem);
    ptContext = ptActionStackItem->ptContext;
    ptActionStackItem->isUsed = 0;
    if ( ptContext )
    {
      ptContext->tNode.ptPrev = nullptr;
      ptContext->tNode.ptNext = nullptr;
      List_AddTail(ptContext, (int)&ptHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID);
      ptActionStackItem->ptContext = nullptr;
    }
  }
}

// source: j/0/humanai/humanaicontent.c:4954  [anchor-mhash]
void __cdecl HumanAIContent_CombatStandFireGrenadeRunCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  struct QTask_s *ptPrev; // eax
  void (__cdecl *pfDeleteCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // eax
  struct HumanAIActionContext_t *ptContext; // eax

  ptPrev = ptHumanAI->tQTask.ptParent[31].ptPrev;
  if ( !ptPrev || ptPrev == (struct QTask_s *)15 )
  {
    pfDeleteCallback = ptActionStackItem->pfDeleteCallback;
    if ( pfDeleteCallback )
      pfDeleteCallback(ptHumanAI, ptActionStackItem);
    Node_Remove(ptActionStackItem);
    ptContext = ptActionStackItem->ptContext;
    ptActionStackItem->isUsed = 0;
    if ( ptContext )
    {
      ptContext->tNode.ptPrev = nullptr;
      ptContext->tNode.ptNext = nullptr;
      List_AddTail(ptContext, (int)&ptHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID);
      ptActionStackItem->ptContext = nullptr;
    }
  }
}

// source: j/0/humanai/humanaicontent.c:4976  [size]
void __cdecl HumanAIContent_WaitInitCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  ptActionStackItem->pfRunCallback = HumanAIContent_WaitRunCB;
}

// source: j/0/humanai/humanaicontent.c:4990  [anchor-mhash]
void __cdecl HumanAIContent_WaitRunCB(struct HumanAI_s *ptHumanAI, struct HumanAIActionStackItem_s *ptActionStackItem)
{
  struct HumanAIActionContext_t *ptContext; // eax
  int nTimer; // ecx
  void (__cdecl *pfDeleteCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // eax
  struct HumanAIActionContext_t *v5; // eax

  ptContext = ptActionStackItem->ptContext;
  nTimer = ptContext->uContext.tWaitContext.nTimer;
  if ( nTimer )
  {
    ptContext->uContext.tWaitContext.nTimer = nTimer - 1;
  }
  else
  {
    pfDeleteCallback = ptActionStackItem->pfDeleteCallback;
    if ( pfDeleteCallback )
      pfDeleteCallback(ptHumanAI, ptActionStackItem);
    Node_Remove(ptActionStackItem);
    v5 = ptActionStackItem->ptContext;
    ptActionStackItem->isUsed = 0;
    if ( v5 )
    {
      v5->tNode.ptPrev = nullptr;
      v5->tNode.ptNext = nullptr;
      List_AddTail(v5, (int)&ptHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID);
      ptActionStackItem->ptContext = nullptr;
    }
  }
}

// source: j/0/humanai/humanaicontent.c:5012  [anchor-caller]
void __cdecl HumanAIContent_TakeCoverInitCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  #pragma pack(push, 1)
  union
  {
    struct { union __anon_1ce5 *v17; };
    struct { char igi2_o1[4]; int v18; };
    struct { char igi2_o2[8]; float v19; };
    struct { char igi2_o3[16]; float v20; };
    struct { char igi2_o4[20]; double *ptParent; };
    struct { char igi2_o5[24]; struct real64x3_t ptPosToCheck; };
    struct { char igi2_o6[48]; struct real64x3_t ptPosition; };
    char igi2_extent[72];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct HumanAI_s *v2; // edx
  struct HumanAIActionContext_t *ptContext; // ebx
  double vX; // st7
  union __anon_1ce5 *p_uContext; // ebx
  int v6; // ecx
  struct AIGraphNodeCoverItem_s *v7; // edi
  int v8; // eax
  int v9; // edx
  int nNodeId; // ecx
  __int16 v11; // si
  int i; // eax
  int v13; // eax
  int v14; // ecx
  struct GraphNode_s *v15; // eax
  long double v16; // st7

  v2 = ptHumanAI;
  ptContext = ptActionStackItem->ptContext;
  vX = ptContext->uContext.tLookAtPositionContext.tPosition.vX;
  p_uContext = &ptContext->uContext;
  v6 = 0;
  igi2_frame.ptParent = (double *)ptHumanAI->tQTask.ptParent;
  igi2_frame.v17 = p_uContext;
  igi2_frame.v18 = 0;
  if ( vX == 0.0
    && p_uContext->tRunToCoverContext.tPosition.vX == 0.0
    && p_uContext->tRunToCoverContext.tPosition.vY == 0.0 )
  {
    qmemcpy(&igi2_frame.ptPosToCheck, &ptHumanAI->tQTask.ptParent[1], sizeof(igi2_frame.ptPosToCheck));
    v6 = 0;
  }
  else
  {
    igi2_frame.ptPosToCheck.vX = p_uContext->tLookAtEventContext.vSecondsToLook + p_uContext->tLookAtPositionContext.tPosition.vX;
    igi2_frame.ptPosToCheck.vY = p_uContext->tTakeCoverContext.tDirection.vY + p_uContext->tRunToCoverContext.tPosition.vX;
    igi2_frame.ptPosToCheck.vZ = p_uContext->tTakeCoverContext.tDirection.vZ + p_uContext->tRunToCoverContext.tPosition.vY;
  }
  v7 = *(struct AIGraphNodeCoverItem_s **)(*(_DWORD *)&ptHumanAI->zScriptFile[36] + 220);
  if ( v7->ptNext && v7 )
  {
    while ( 1 )
    {
      v8 = *(_DWORD *)&v2->zScriptFile[36];
      v9 = *(_DWORD *)(v8 + 132);
      nNodeId = v7->nNodeId;
      if ( !v9 || nNodeId >= (int)(*(_DWORD *)(v8 + 104)) || nNodeId < 0 )
        break;
      v11 = *(_WORD *)(v8 + 36);
      for ( i = 0; ; ++i )
      {
        if ( i >= 4 )
        {
          LDebug_Error("Undefined GraphNodeDataSize");
          abort();
        }
        if ( v11 == Graph_atGraphNodeDataSize[i].eGraphQTaskType )
          break;
      }
      v13 = nNodeId * Graph_atGraphNodeDataSize[i].nDataSize;
      v14 = *(_DWORD *)(v13 + v9);
      v15 = (struct GraphNode_s *)(v9 + v13);
      if ( v14 == -1 )
        break;
      p_uContext->tRunPanickingEventContext.nTimer = 0;
      Graph_GetNodePos(&igi2_frame.ptPosition, v15);
      v16 = sqrt(
              (igi2_frame.ptParent[5] - igi2_frame.ptPosition.vX) * (igi2_frame.ptParent[5] - igi2_frame.ptPosition.vX)
            + (igi2_frame.ptParent[6] - igi2_frame.ptPosition.vY) * (igi2_frame.ptParent[6] - igi2_frame.ptPosition.vY)
            + (igi2_frame.ptParent[7] - igi2_frame.ptPosition.vZ) * (igi2_frame.ptParent[7] - igi2_frame.ptPosition.vZ));
      if ( v16 < 40960.0 && (v7->bFlags & 1) == 0 )
      {
        if ( AIGraph_CoverNodeProvidesCoverFromPosition(
               *(struct AIGraph_t **)&ptHumanAI->zScriptFile[36],
               v7,
               &igi2_frame.ptPosToCheck) )
        {
          if ( !igi2_frame.v18 || (igi2_frame.v19 = v16, igi2_frame.v19 < (double)igi2_frame.v20) )
          {
            igi2_frame.v20 = v16;
            igi2_frame.v18 = (int)v7;
            igi2_frame.v17->tRunPanickingEventContext.nTimer = AIGraph_GetCoverSectorFromPosition(
                                                      *(struct AIGraph_t **)&ptHumanAI->zScriptFile[36],
                                                      &igi2_frame.ptPosition,
                                                      &igi2_frame.ptPosToCheck);
          }
        }
        p_uContext = igi2_frame.v17;
      }
      v7 = v7->ptNext;
      if ( !v7->ptNext || !v7 )
        break;
      v2 = ptHumanAI;
    }
    v6 = igi2_frame.v18;
  }
  p_uContext->tHoldAreaContext.nGraphId = v6;
  if ( v6 )
    *(_DWORD *)(v6 + 8) |= 1u;
  ptActionStackItem->pfRunCallback = HumanAIContent_TakeCoverRunCB;
}

// source: j/0/humanai/humanaicontent.c:5093  [anchor-mhash]
void __cdecl HumanAIContent_TakeCoverRunCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  struct HumanAIActionContext_t *ptContext; // ebx
  int nGraphId; // eax
  struct real64x3_t *p_uContext; // ebx
  struct QTask_s *ptParent; // eax
  int v7; // [esp-4h] [ebp-10h]
  float ptHumanAIa = *(float *)&ptHumanAI; // [esp+10h] [ebp+4h] ARGSLOT

  ptContext = ptActionStackItem->ptContext;
  nGraphId = ptContext->uContext.tHoldAreaContext.nGraphId;
  p_uContext = (struct real64x3_t *)&ptContext->uContext;
  if ( nGraphId )
  {
    ptParent = ptHumanAI->tQTask.ptParent;
    if ( ptParent->eQTaskType == HumanSoldier_eQTaskType )
    {
      ptHumanAIa = 1.0;
      if ( !LOBYTE(ptParent[75].ptPrev) )
        ptHumanAIa = 0.0;
      HumanAIContent_SetChannel(ptHumanAI, 0, ptHumanAIa);
    }
    v7 = *(_DWORD *)(LODWORD(p_uContext[1].vZ) + 140);
    ptHumanAI->avChannel[8] = 0.3141592741012573;
    ptHumanAI->avChannel[9] = 0.3141592741012573;
    if ( HumanAI_MoveCharacterToNode(ptHumanAI, v7) )
    {
      HumanAI_ClearMovementQueue(ptHumanAI);
      if ( HumanAI_FacePositionSelectSpeed(ptHumanAI, p_uContext, 0.1745329350233078, true) )
      {
        if ( (*(_BYTE *)(LODWORD(p_uContext[1].vZ) + 4 * HIDWORD(p_uContext[1].vY) + 12) & 4) == 0 )
          HumanAIContent_SetChannel(ptHumanAI, 1, 1.0);
      }
    }
  }
  else
  {
    HumanAI_ClearMovementQueue(ptHumanAI);
    if ( (ptHumanAI->anEventPriorityList[5] & 4) != 0 )
    {
      ptHumanAI->avChannel[8] = 0.41887903213500977;
      ptHumanAI->avChannel[9] = 0.20943951606750488;
    }
    else
    {
      ptHumanAI->avChannel[8] = 0.20943951606750488;
      ptHumanAI->avChannel[9] = 0.10471975803375244;
    }
    HumanAI_FacePosition(ptHumanAI, p_uContext, 0.1745329350233078, true);
  }
}

// source: j/0/humanai/humanaicontent.c:5136  [size]
void __cdecl HumanAIContent_TakeCoverDeleteCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  ;
}

// source: j/0/humanai/humanaicontent.c:5151  [anchor-mhash]
void __cdecl HumanAIContent_LookInApproxDirectionInitCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real64x3_t v20; };
    struct { char igi2_o1[40]; struct real64x3_t tReal64x3; };
    struct { char igi2_o2[68]; struct real32x3_t tReal32x3; };
    char igi2_extent[84];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double *ptParent; // ebx
  struct HumanAIActionContext_t *ptContext; // edx
  double vX; // st7
  union __anon_1ce5 *p_uContext; // edx
  double v7; // st7
  double v8; // st6
  double v9; // st7
  struct Game_s *v10; // eax
  unsigned int v11; // edi
  unsigned int v12; // ecx
  int v13; // ecx
  unsigned int v14; // esi
  long double v15; // st7
  long double v16; // rt1
  long double v17; // st6
  long double v18; // st7
  double vZ; // st6
  struct HumanAIActionStackItem_s *ptActionStackItema = *(struct HumanAIActionStackItem_s * *)&ptActionStackItem; // [esp+44h] [ebp+8h] ARGSLOT
  float ptActionStackItemb = *(float *)&ptActionStackItem; // [esp+44h] [ebp+8h] ARGSLOT

  ptParent = (double *)ptHumanAI->tQTask.ptParent;
  ptContext = ptActionStackItem->ptContext;
  vX = ptContext->uContext.tLookAtPositionContext.tPosition.vX;
  p_uContext = &ptContext->uContext;
  v7 = vX - ptParent[5];
  v8 = p_uContext->tRunToCoverContext.tPosition.vX - ptParent[6];
  igi2_frame.tReal32x3.vZ = p_uContext->tRunToCoverContext.tPosition.vY - ptParent[7];
  igi2_frame.tReal64x3.vX = v7;
  igi2_frame.tReal64x3.vY = v8;
  igi2_frame.tReal64x3.vZ = igi2_frame.tReal32x3.vZ;
  qmemcpy(&igi2_frame.v20, &igi2_frame.tReal64x3, sizeof(igi2_frame.v20));
  v9 = GameFunctions_CalcGamma(igi2_frame.v20);
  if ( v9 < 0.0 )
    v9 = v9 + 6.2831854820251465;
  *(_QWORD *)&igi2_frame.tReal64x3.vX = (__int64)((double)p_uContext->tLookInApproxDirectionContext.nSectorResolution
                                     * v9
                                     * 0.15915494309189526);
  v10 = Game_ptGame;
  v11 = Game_ptGame->tRunRandomState.anRandom[1];
  ptActionStackItema = (struct HumanAIActionStackItem_s *)LODWORD(igi2_frame.tReal64x3.vX);
  v12 = (Game_ptGame->tRunRandomState.anRandom[0] >> 7) ^ Game_ptGame->tRunRandomState.anRandom[2];
  Game_ptGame->tRunRandomState.anRandom[2] = v12;
  v13 = v12 ^ v11;
  v14 = v13 + v10->tRunRandomState.anRandom[0];
  v10->tRunRandomState.anRandom[1] = v13;
  v10->tRunRandomState.anRandom[0] = v14;
  v15 = ((double)(unsigned __int16)v14 * 0.0000152587890625 + (double)(int)ptActionStackItema)
      * 6.283185307179589
      / (double)p_uContext->tLookInApproxDirectionContext.nSectorResolution;
  v16 = sin(v15);
  v17 = cos(v15);
  ptActionStackItemb = igi2_frame.tReal32x3.vZ * 0.0;
  *(float *)&igi2_frame.tReal64x3.vX = v17 * 0.0 + -v16 * 20480.0 + ptActionStackItemb;
  v18 = v17 * 20480.0 + v16 * 0.0 + ptActionStackItemb;
  vZ = igi2_frame.tReal32x3.vZ;
  p_uContext->tLookAtPositionContext.tPosition.vX = *(float *)&igi2_frame.tReal64x3.vX + ptParent[5];
  p_uContext->tRunToCoverContext.tPosition.vX = v18 + ptParent[6];
  p_uContext->tRunToCoverContext.tPosition.vY = vZ + ptParent[7];
  ptActionStackItem->pfRunCallback = HumanAIContent_LookInApproxDirectionRunCB;
}

// source: j/0/humanai/humanaicontent.c:5208  [anchor-mhash]
void __cdecl HumanAIContent_LookInApproxDirectionRunCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct HumanAILookInApproxEventDirectionActionContext_s *ptContext; };
    struct { char igi2_o1[4]; struct HumanAIEventContext_t tContext; };
    char igi2_extent[68];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  union __anon_1ce5 *p_uContext; // eax
  int v3; // esi
  int v4; // ecx
  int *v5; // edx
  int nTimeLeft; // esi
  int v7; // ecx

  p_uContext = &ptActionStackItem->ptContext->uContext;
  v3 = -1;
  v4 = 0;
  igi2_frame.ptContext = (struct HumanAILookInApproxEventDirectionActionContext_s *)p_uContext;
  if ( ptHumanAI->nAnimationMinimumDelay > 0 )
  {
    v5 = &ptHumanAI->anEventPriorityList[6];
    while ( *v5 != 4 )
    {
      ++v4;
      ++v5;
      if ( v4 >= ptHumanAI->nAnimationMinimumDelay )
        goto LABEL_7;
    }
    v3 = v4;
  }
LABEL_7:
  if ( ptActionStackItem->nPriority != v3 )
  {
    qmemcpy(&ptHumanAI->tCommon.nIgnoreVisibilityFactorTimer, p_uContext, 0x18u);
    qmemcpy(&ptHumanAI[1], p_uContext, 0x18u);
    HumanAIContent_SetChannel(ptHumanAI, 5, 1.0);
    p_uContext = (union __anon_1ce5 *)igi2_frame.ptContext;
  }
  if ( (ptHumanAI->anEventPriorityList[5] & 4) != 0 )
  {
    ptHumanAI->avChannel[8] = 0.41887903213500977;
    ptHumanAI->avChannel[9] = 0.20943951606750488;
  }
  else
  {
    ptHumanAI->avChannel[8] = 0.20943951606750488;
    ptHumanAI->avChannel[9] = 0.10471975803375244;
  }
  if ( HumanAI_FacePosition(ptHumanAI, (struct real64x3_t *)p_uContext, 0.03490658476948738, true) )
  {
    nTimeLeft = igi2_frame.ptContext->nTimeLeft;
    if ( nTimeLeft <= 0 || HumanAI_GetTargetQTask(ptHumanAI, true) )
    {
      if ( !HumanAI_GetTargetQTask(ptHumanAI, true) )
      {
        igi2_frame.tContext.eEvent = 40;
        igi2_frame.tContext.bFlags = 0;
        igi2_frame.tContext.ptHumanOriginatorQTask = nullptr;
        igi2_frame.tContext.ptPosition = nullptr;
        igi2_frame.tContext.ptReferenceQTask = nullptr;
        HumanAI_SendEventSpecificQTask(&ptHumanAI->tQTask, &igi2_frame.tContext);
      }
      HumanAI_PopActionStackItem(ptHumanAI, ptActionStackItem);
    }
    else
    {
      v7 = igi2_frame.ptContext->nStartTime - (nTimeLeft - 1);
      igi2_frame.ptContext->nTimeLeft = nTimeLeft - 1;
      if ( v7 > 30 )
      {
        *(_DWORD *)ptHumanAI->zStandActionAnimation = 1851880563;
        *(_DWORD *)&ptHumanAI->zStandActionAnimation[4] = 1818320740;
        *(_DWORD *)&ptHumanAI->zStandActionAnimation[8] = (char *)&HumanAI_atMovementQueueItems[840].tNode.ptPrev + 1;
        HumanAIContent_SetChannel(ptHumanAI, 3, 1.0);
        HumanAIContent_SetChannel(ptHumanAI, 5, 0.0);
      }
    }
  }
}

// source: j/0/humanai/humanaicontent.c:5264  [anchor-mhash]
void __cdecl HumanAIContent_LookInApproxDirectionDeleteCB(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  if ( !HumanAI_GetTargetQTask(ptHumanAI, true) )
  {
    ptHumanAI->avChannel[39] = 0.0;
    ptHumanAI->avChannel[40] = 0.0;
    ptHumanAI->tCommon.nIgnoreVisibilityFactorTimer = 0;
    ptHumanAI->tCommon.nRollDisallowedTimer = 0;
    *(_DWORD *)&ptHumanAI->tCommon.isDetectionSoundPlayed = 0;
    ptHumanAI->tCommon.ptDoorQTaskRef = nullptr;
    ptHumanAI->tCommon.tAimPosition.vX = 0.0;
  }
}
