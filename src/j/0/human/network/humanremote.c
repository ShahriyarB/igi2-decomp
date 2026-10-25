/* j/0/human/network/humanremote.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/human/network/humanremote.c:63  [anchor-caller]
struct QTask_s *__cdecl HumanRemote_SetWeaponTypeAnim(
        struct QTask_s *ptQTask,
        enum WeaponTypeGetAnimType_e eAnimType,
        int nTimeFrame,
        enum bool isReverse)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vTimeScale; };
    struct { char igi2_o1[8]; struct WeaponTypeGetAnimContext_s tGetAnimContext; };
    char igi2_extent[44];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptTail; // esi
  struct QTask_s *result; // eax
  struct QTask_s *ptPrev; // ecx
  struct QTask_s *v8; // ecx
  unsigned __int8 *v9; // edx

  ptTail = ptQTask[33].tQTaskChildren.ptTail;
  result = ptQTask[33].ptNext;
  ptPrev = result[1].ptPrev;
  if ( ptPrev )
  {
    v8 = ptPrev->tQTaskChildren.ptTail;
    if ( v8 )
    {
      v9 = (unsigned __int8 *)ptTail[7].tQTaskRefList.ptTail;
      igi2_frame.tGetAnimContext.tIn.ptWeapon = result;
      igi2_frame.tGetAnimContext.tIn.ptHierarchy = v9;
      igi2_frame.tGetAnimContext.tIn.eAnimType = eAnimType;
      igi2_frame.tGetAnimContext.tIn.nFireType = 0;
      igi2_frame.tGetAnimContext.tIn.ptWeaponType = nullptr;
      igi2_frame.tGetAnimContext.tOut.ptAnim = nullptr;
      ((void (__cdecl *)(struct QTask_s *, struct WeaponTypeGetAnimContext_s *))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][v8->eQTaskType].pfHandler)(
        v8,
        &igi2_frame.tGetAnimContext);
      result = (struct QTask_s *)LODWORD(igi2_frame.tGetAnimContext.tOut.vTimeScale);
      igi2_frame.vTimeScale = igi2_frame.tGetAnimContext.tOut.vTimeScale;
      if ( igi2_frame.tGetAnimContext.tOut.ptAnim )
      {
        if ( isReverse )
          igi2_frame.vTimeScale = igi2_frame.tGetAnimContext.tOut.vTimeScale * -1.0;
        if ( igi2_frame.vTimeScale < 0.0 )
          nTimeFrame = igi2_frame.tGetAnimContext.tOut.ptAnim->nTotalTime - nTimeFrame;
        AnimController_SetAnimationAndTime(
          (struct AnimController_t *)ptTail[16].tQTaskRefList.ptTail,
          igi2_frame.tGetAnimContext.tOut.ptAnim,
          nTimeFrame);
        result = (struct QTask_s *)(__int64)((double)AnimController_nTicksPerFrame * igi2_frame.vTimeScale);
        ptTail[16].tQTaskRefList.ptTail[5].pxObject = result;
      }
      else
      {
        ptTail[16].tQTaskRefList.ptTail[3].pxObject = (void *)((int)ptTail[16].tQTaskRefList.ptTail[3].pxObject | 4);
      }
    }
  }
  return result;
}

// source: j/0/human/network/humanremote.c:170  [anchor-callee]
void __cdecl HumanRemote_UpdateCollision(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct World_s *ptWorld; };
    struct { char igi2_o1[40]; double pvDistance; };
    struct { char igi2_o2[48]; struct CollisionEvaluateContext_s ptEvalContext; };
    struct { char igi2_o3[56]; struct real64x3_t ptStart; };
    char igi2_extent[84];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  qmemcpy(&igi2_frame.ptStart, &ptQTask[1], sizeof(igi2_frame.ptStart));
  igi2_frame.ptStart.vZ = igi2_frame.ptStart.vZ + 4096.0;
  igi2_frame.ptEvalContext.ptQTask = ptQTask;
  igi2_frame.ptWorld = Game_ptGame->ptWorld;
  igi2_frame.pvDistance = -40960.0;
  World_GetNextZ(
    igi2_frame.ptWorld,
    (struct QIntersection_s *)&ptQTask[40].tQTaskRefList.ptMiddle,
    &igi2_frame.ptStart,
    1,
    &igi2_frame.pvDistance,
    GameFunctions_eObjectCollisionEvaluateQTaskEvent,
    &igi2_frame.ptEvalContext,
    0xFFFFFFFF);
  if ( *(_DWORD *)&ptQTask[42].eQTaskType
    || (igi2_frame.pvDistance = 40960.0,
        World_GetNextZ(
          Game_ptGame->ptWorld,
          (struct QIntersection_s *)&ptQTask[40].tQTaskRefList.ptMiddle,
          &igi2_frame.ptStart,
          1,
          &igi2_frame.pvDistance,
          GameFunctions_eObjectCollisionEvaluateQTaskEvent,
          &igi2_frame.ptEvalContext,
          0xFFFFFFFF),
        *(_DWORD *)&ptQTask[42].eQTaskType) )
  {
    *(float *)&ptQTask[49].ptParent = (*(float *)&ptQTask[43].tQTaskChildren.ptTail - *(float *)&ptQTask[49].ptParent)
                                    * 0.5
                                    + *(float *)&ptQTask[49].ptParent;
  }
}

// source: j/0/human/network/humanremote.c:220  [anchor-callee]
int __cdecl HumanRemote_UpdateAnim(struct HumanRemote_t *ptHumanRemote)
{
  int nSpeed; // eax
  struct RigidDynCubeObj_t *v3; // ecx
  struct AnimController_t *ptActiveMainController; // ebp
  int nTotalTime; // edi
  int v6; // eax
  int nTime; // esi
  int v8; // ecx
  int v9; // eax
  int v10; // ebx
  int result; // eax
  struct real64x3_t tBottom; // [esp+18h] [ebp-1Ch] BYREF

  nSpeed = ptHumanRemote->tCompressionState.nSpeed;
  if ( nSpeed == -1 || ptHumanRemote->eUpperBody != 45 )
  {
    AnimController_Step(
      ptHumanRemote->tHuman.tHumanAnim.ptActiveMainController,
      ptHumanRemote->tHuman.tHumanAnim.ptActiveMainController->nTime
    + ptHumanRemote->tHuman.tHumanAnim.ptActiveMainController->nTimeStep);
  }
  else
  {
    if ( nSpeed < 0 || nSpeed >= (signed int)Ladder_ptLadderVector->tPrivate.nElements )
      v3 = nullptr;
    else
      v3 = (struct RigidDynCubeObj_t *)Ladder_ptLadderVector->tPrivate.papxElement[nSpeed];
    RigidDynCubeObj_GetMagicVertexPos(v3, 2u, &tBottom);
    ptActiveMainController = ptHumanRemote->tHuman.tHumanAnim.ptActiveMainController;
    nTotalTime = ptActiveMainController->ptAnim->nTotalTime;
    v6 = (__int64)((ptHumanRemote->tHuman.tBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vZ - tBottom.vZ)
                 * (double)nTotalTime
                 * 0.00040690103196538985);
    if ( v6 < 0 )
      v6 = 0;
    nTime = ptActiveMainController->nTime;
    v8 = v6 % nTotalTime;
    v9 = v6 % nTotalTime - nTime;
    if ( v9 >= 0 )
      v10 = v9;
    else
      v10 = nTime - v8;
    if ( v10 > nTotalTime / 2 )
    {
      if ( v8 < nTime )
      {
        AnimController_Step(ptActiveMainController, nTotalTime + v8);
        return result;
      }
      v8 -= nTotalTime;
    }
    AnimController_Step(ptActiveMainController, v8);
  }
  return result;
}

// source: j/0/human/network/humanremote.c:287  [anchor-caller]
struct QTask_s *__cdecl HumanRemote_Update(struct QTask_s *ptQTask)
{
  int *p_ptTail; // ebx
  struct QTask_s *result; // eax

  HumanRemote_UpdateCollision(ptQTask);
  Human_UpdateBody(ptQTask);
  Human_UpdateDie((struct Human_s *)ptQTask);
  HumanView_UpdateView(ptQTask[33].tQTaskChildren.ptTail, ptQTask);
  if ( *(_DWORD *)&ptQTask[32].eQTaskType == 2 )
  {
    Human_InterpolateZAxisToAveragedGroundNormal(ptQTask);
    Human_UpdatePlatformPos(ptQTask, false, true);
    ModelObj_UpdateAttachments((struct ModelObj_s *)ptQTask);
  }
  HumanRemote_UpdateAnim((struct HumanRemote_t *)ptQTask);
  HumanView_UpdateBody(ptQTask[33].tQTaskChildren.ptTail, ptQTask, true);
  Human_Notify(ptQTask);
  p_ptTail = (int *)&ptQTask[51].tQTaskRefList.ptTail;
  result = (struct QTask_s *)Water_IsUnderWater(
                               (float *)&ptQTask[51].tQTaskRefList.ptMiddle,
                               (struct real64x3_t *)&ptQTask[1],
                               (int *)&ptQTask[51].tQTaskRefList.ptTail);
  if ( result )
  {
    result = ptQTask[31].ptPrev;
    if ( result == (struct QTask_s *)21 || result == (struct QTask_s *)1 )
    {
      return (struct QTask_s *)Water_PlayerMovementEffect((struct real64x3_t *)&ptQTask[1], *p_ptTail, false);
    }
    else if ( result )
    {
      return (struct QTask_s *)Water_PlayerMovementEffect(
                                 (struct real64x3_t *)&ptQTask[1],
                                 *p_ptTail,
                                 (enum bool)(BYTE1(ptQTask[50].ptNext) != 0));
    }
  }
  else
  {
    ptQTask[51].tQTaskRefList.ptMiddle = nullptr;
  }
  return result;
}

// source: j/0/human/network/humanremote.c:348  [size~]
struct QTask_s *__cdecl HumanRemote_SetUpperBody(struct QTask_s *ptQTask, int eUpperBody)
{
  struct QTask_s *result; // eax

  if ( eUpperBody )
  {
    if ( eUpperBody == 8 )
      HumanRemote_SetWeaponTypeAnim(ptQTask, WEAPONTYPE_GETANIMTYPE_1STRELOADSTART, 0, false);
    result = (struct QTask_s *)((char *)ptQTask[81].ptNext - 3);
    BYTE1(ptQTask[50].ptNext) = 0;
    *(_DWORD *)&ptQTask[32].eQTaskType = 0;
    switch ( (unsigned int)result )
    {
      case 0u:
      case 1u:
      case 2u:
      case 3u:
      case 4u:
      case 5u:
      case 6u:
      case 7u:
        BYTE1(ptQTask[50].ptNext) = 1;
        break;
      case 0x14u:
      case 0x15u:
      case 0x16u:
      case 0x17u:
      case 0x18u:
      case 0x19u:
      case 0x1Au:
      case 0x1Bu:
      case 0x1Cu:
      case 0x1Du:
      case 0x1Eu:
      case 0x1Fu:
      case 0x20u:
      case 0x41u:
        *(_DWORD *)&ptQTask[32].eQTaskType = 1;
        break;
      case 0x48u:
      case 0x49u:
      case 0x4Au:
      case 0x4Bu:
      case 0x4Cu:
      case 0x4Du:
      case 0x4Eu:
      case 0x4Fu:
      case 0x57u:
      case 0x58u:
        HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
        *(_DWORD *)&ptQTask[32].eQTaskType = 2;
        break;
      default:
        break;
    }
    if ( *(_DWORD *)&ptQTask[32].eQTaskType != 2 )
    {
      switch ( eUpperBody )
      {
        case 6:
          HumanAnim_SetUpperBodyAnimationAndTimeFromState(ptQTask, 83, 0, 0.0);
          break;
        case 8:
          HumanAnim_SetUpperBodyAnimationAndTimeFromState(ptQTask, 84, 0, 0.0);
          break;
        case 9:
          HumanAnim_SetUpperBodyAnimationAndTimeFromState(ptQTask, 85, 0, 0.0);
          break;
        case 10:
          HumanAnim_SetUpperBodyAnimationAndTimeFromState(ptQTask, 86, 0, 0.0);
          break;
        case 11:
          HumanAnim_SetUpperBodyAnimationAndTimeFromState(ptQTask, 88, 0, 0.0);
          break;
        case 12:
          HumanAnim_SetUpperBodyAnimationAndTimeFromState(ptQTask, 87, 0, 0.0);
          break;
        default:
          HumanAnim_SetUpperBodyAnimationAndTimeFromState(ptQTask, 0, 0, 0.0);
          break;
      }
    }
  }
  else
  {
    HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.4000000059604645);
    *(_DWORD *)&ptQTask[32].eQTaskType = 2;
  }
  return result;
}

// source: j/0/human/network/humanremote.c:488  [anchor-refs]
void __cdecl HumanRemote_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[24]; struct real64x3_t tNull; };
    char igi2_extent[48];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  bool v2; // zf
  DWORD TickCount; // eax
  double v4; // st7
  double v5; // st6
  struct Game_s *v6; // edx
  double v7; // st5
  struct QTask_s *ptNext; // eax
  struct QTask_s *v9; // eax
  struct QTask_s *ptHead; // eax
  int v11; // ecx

  memset(&igi2_frame.tNull, 0, sizeof(igi2_frame.tNull));
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][Human_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  ptQTask[81].tQTaskChildren.ptTail = (struct QTask_s *)-1;
  ptQTask[81].tQTaskRefList.ptHead = (struct QReference_s *)-1;
  ptQTask[81].ptParent = (struct QTask_s *)-1;
  v2 = Timer_isPerformanceCounter == 0;
  ptQTask[81].ptNext = nullptr;
  ptQTask[81].ptPrev = nullptr;
  ptQTask[81].tQTaskChildren.ptHead = nullptr;
  ptQTask[81].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[81].tQTaskRefList.ptMiddle = nullptr;
  LOBYTE(ptQTask[81].tQTaskRefList.ptTail) = 0;
  if ( v2 )
    TickCount = GetTickCount();
  else
    TickCount = Timer_GetPerformanceCounter();
  ptQTask[82].tQTaskChildren.ptMiddle = (struct QTask_s *)(TickCount - Timer_nStartTime);
  ptQTask[82].tQTaskRefList.ptHead = nullptr;
  ptQTask[82].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[82].tQTaskChildren.ptTail = nullptr;
  ptQTask[82].tQTaskRefList.ptTail = nullptr;
  ptQTask[82].ptParent = nullptr;
  *(_DWORD *)&ptQTask[82].eQTaskType = 0;
  v4 = *(float *)&ptQTask[7].tQTaskRefList.ptMiddle;
  v5 = *(float *)&ptQTask[7].tQTaskRefList.ptHead;
  v6 = Game_ptGame;
  v7 = *(float *)&ptQTask[7].tQTaskChildren.ptTail;
  ptQTask[36].tQTaskRefList.ptTail = nullptr;
  ptQTask[36].ptParent = nullptr;
  *(_DWORD *)&ptQTask[36].eQTaskType = 0;
  ptQTask[37].ptNext = nullptr;
  ptQTask[37].ptPrev = nullptr;
  igi2_frame.ptDynCubeObj = sqrt(v7 * v7 + v5 * v5 + v4 * v4) + *(float *)&ptQTask[8].ptNext;
  World_RegisterDynCubeObjFirstTimeRadius(
    v6->ptWorld,
    (struct DynCubeObj_s *)ptQTask,
    &igi2_frame.tNull,
    igi2_frame.ptDynCubeObj,
    WORLD_DYNCUBETREE_CATEGORY_MOBILE);
  ptQTask[25].tQTaskRefList.ptMiddle = (struct QReference_s *)1065353216;
  ptQTask[25].tQTaskRefList.ptTail = (struct QReference_s *)HumanPlayer_atDamagePartDataMultiplayer;
  HumanDamage_ClearDamage((struct HumanDamage_t *)&ptQTask[25].tQTaskRefList);
  ptQTask[29].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[29].tQTaskChildren.ptTail = nullptr;
  ptQTask[29].tQTaskChildren.ptHead = (struct QTask_s *)-1;
  ptQTask[82].ptPrev = (struct QTask_s *)-1;
  ptQTask[82].tQTaskChildren.ptHead = (struct QTask_s *)-1;
  ptNext = ptQTask[33].ptNext;
  *(_DWORD *)&ptQTask[81].eQTaskType = 0;
  ptQTask[82].ptNext = nullptr;
  ptQTask[32].tQTaskRefList.ptMiddle = (struct QReference_s *)HumanPlayer_atStateAnimData;
  BYTE1(ptQTask[81].tQTaskRefList.ptTail) = 0;
  ptQTask[79].ptParent = nullptr;
  *(_DWORD *)&ptQTask[79].eQTaskType = 0;
  ptQTask[80].ptNext = nullptr;
  ptQTask[80].ptPrev = nullptr;
  ptQTask[80].tQTaskChildren.ptHead = nullptr;
  ptQTask[80].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[80].tQTaskChildren.ptTail = nullptr;
  ptQTask[80].tQTaskRefList.ptHead = nullptr;
  ptQTask[80].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[80].tQTaskRefList.ptTail = nullptr;
  ptQTask[80].ptParent = nullptr;
  *(_DWORD *)&ptQTask[80].eQTaskType = 0;
  v9 = ptNext[5].ptNext;
  if ( v9 )
  {
    ptHead = v9->tQTaskChildren.ptHead;
    if ( ptHead )
    {
      if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
      {
        v11 = (int)ptHead[4].tQTaskChildren.ptMiddle | 1;
        ptHead[4].ptNext = (struct QTask_s *)1120403456;
        ptHead[4].tQTaskChildren.ptMiddle = (struct QTask_s *)v11;
      }
    }
  }
  Weapon_EnableWeaponType(ptQTask[33].ptNext, "WEAPON_ID_KNIFE", true);
}

// source: j/0/human/network/humanremote.c:584  [size]
int __cdecl HumanRemote_SetRadioTimer(struct HumanRemote_t *ptHumanRemote, int nTimer)
{
  ptHumanRemote->nActivateInfo = nTimer;
  ptHumanRemote->iActiveLadder = nTimer;
  return nTimer;
}

// source: j/0/human/network/humanremote.c:604  [anchor-strings]
void __cdecl HumanRemote_DrawTextAboveHead(struct HumanRemote_t *ptHumanRemote)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct TransContext_s ptTransContext; };
    struct { char igi2_o1[320]; char zText[256]; };
    struct { char igi2_o2[576]; char Buffer[256]; };
    char igi2_extent[832];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Client_s *ClientFromHumanQTask; // ebx
  float vX; // edi
  int nActivateInfo; // eax
  BOOL v4; // edx
  BOOL v5; // ecx

  ClientFromHumanQTask = NetManager_GetClientFromHumanQTask(&ptHumanRemote->tHuman.tBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask);
  LODWORD(igi2_frame.ptTransContext.tMatrix.tY.vX) = NetManager_GetClientFromNetworkID((int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
  LODWORD(igi2_frame.ptTransContext.tMatrix.tY.vY) = StatusScreen_ptStatusScreenQTask;
  if ( LODWORD(igi2_frame.ptTransContext.tMatrix.tY.vX) )
  {
    qmemcpy(
      &igi2_frame.ptTransContext.tMatrix.tZ.vZ,
      &ptHumanRemote->tHuman.tBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos,
      0x18u);
    igi2_frame.ptTransContext.tMatrix.tY.vZ = TransContext_tActiveTransContext.tMatrix.tX.vZ
                                 * (igi2_frame.ptTransContext.tPos.vY - TransContext_tActiveTransContext.tPos.vZ)
                                 + TransContext_tActiveTransContext.tMatrix.tX.vY
                                 * (igi2_frame.ptTransContext.tPos.vX - TransContext_tActiveTransContext.tPos.vY)
                                 + TransContext_tActiveTransContext.tMatrix.tX.vX
                                 * (*(double *)&igi2_frame.ptTransContext.tMatrix.tZ.vZ - TransContext_tActiveTransContext.tPos.vX);
    igi2_frame.ptTransContext.tMatrix.tZ.vX = TransContext_tActiveTransContext.tMatrix.tY.vZ
                                 * (igi2_frame.ptTransContext.tPos.vY - TransContext_tActiveTransContext.tPos.vZ)
                                 + TransContext_tActiveTransContext.tMatrix.tY.vY
                                 * (igi2_frame.ptTransContext.tPos.vX - TransContext_tActiveTransContext.tPos.vY)
                                 + TransContext_tActiveTransContext.tMatrix.tY.vX
                                 * (*(double *)&igi2_frame.ptTransContext.tMatrix.tZ.vZ - TransContext_tActiveTransContext.tPos.vX);
    _snprintf(
      igi2_frame.Buffer,
      0xFFu,
      (char *const)&g_ptPos,
      igi2_frame.ptTransContext.tMatrix.tY.vZ,
      igi2_frame.ptTransContext.tMatrix.tZ.vX,
      TransContext_tActiveTransContext.tMatrix.tZ.vZ
    * (igi2_frame.ptTransContext.tPos.vY - TransContext_tActiveTransContext.tPos.vZ)
    + TransContext_tActiveTransContext.tMatrix.tZ.vY
    * (igi2_frame.ptTransContext.tPos.vX - TransContext_tActiveTransContext.tPos.vY)
    + TransContext_tActiveTransContext.tMatrix.tZ.vX
    * (*(double *)&igi2_frame.ptTransContext.tMatrix.tZ.vZ - TransContext_tActiveTransContext.tPos.vX));
    igi2_frame.ptTransContext.tPos.vY = igi2_frame.ptTransContext.tPos.vY + 8192.0;
    TransContext_ProjectWorldPos2(
      &TransContext_tActiveTransContext,
      (struct real32x2_t *)&igi2_frame.ptTransContext.tMatrix.tX.vY,
      &igi2_frame.ptTransContext.tMatrix.tX.vX,
      (struct real64x3_t *)&igi2_frame.ptTransContext.tMatrix.tZ.vZ);
    igi2_frame.ptTransContext.tPos.vY = igi2_frame.ptTransContext.tPos.vY - 4096.0;
    TransContext_ProjectWorldPos2(
      &TransContext_tActiveTransContext,
      (struct real32x2_t *)&igi2_frame.ptTransContext.tPos.vZ,
      &igi2_frame.ptTransContext.tMatrix.tX.vX,
      (struct real64x3_t *)&igi2_frame.ptTransContext.tMatrix.tZ.vZ);
    igi2_frame.ptTransContext.tMatrix.tX.vY = igi2_frame.ptTransContext.tMatrix.tX.vY / (double)Display_tActiveMode.nWidth;
    igi2_frame.ptTransContext.tMatrix.tX.vZ = igi2_frame.ptTransContext.tMatrix.tX.vZ / (double)Display_tActiveMode.nHeight;
    _snprintf(
      igi2_frame.zText,
      0xFFu,
      (char *const)&stru_6A4CDC.tDebugConsoleLineList.ptMiddle,
      ClientFromHumanQTask->zPlayerName);
    vX = igi2_frame.ptTransContext.tMatrix.tX.vX;
    if ( ClientFromHumanQTask->eTeam == *(_DWORD *)(LODWORD(igi2_frame.ptTransContext.tMatrix.tY.vX) + 60)
      && *(_DWORD *)(LODWORD(igi2_frame.ptTransContext.tMatrix.tY.vX) + 44) != ClientFromHumanQTask->eNetworkID
      && igi2_frame.ptTransContext.tMatrix.tX.vX > 0.0
      && (igi2_frame.ptTransContext.tMatrix.tX.vX < 614400.0
       || HumanPlayer_ptQTask[33].tQTaskChildren.ptTail[16].tQTaskRefList.ptMiddle)
      && igi2_frame.ptTransContext.tMatrix.tX.vY > 0.0
      && igi2_frame.ptTransContext.tMatrix.tX.vY < 1.0
      && igi2_frame.ptTransContext.tMatrix.tX.vZ > 0.0
      && igi2_frame.ptTransContext.tMatrix.tX.vZ < 1.0 )
    {
      StatusScreen_DrawLocator(
        (struct StatusScreen_t *)LODWORD(igi2_frame.ptTransContext.tMatrix.tY.vY),
        igi2_frame.ptTransContext.tMatrix.tX.vY,
        igi2_frame.ptTransContext.tMatrix.tX.vZ,
        igi2_frame.ptTransContext.tMatrix.tX.vX,
        1.0,
        0.0,
        128.0,
        0.0,
        igi2_frame.zText);
    }
    nActivateInfo = ptHumanRemote->nActivateInfo;
    if ( nActivateInfo > 0 )
    {
      *(float *)&igi2_frame.ptTransContext.tPos.vZ = StatusScreen_GetFancyFade(nActivateInfo, ptHumanRemote->iActiveLadder);
      v4 = igi2_frame.ptTransContext.tMatrix.tX.vY > 0.05000000074505806 && igi2_frame.ptTransContext.tMatrix.tX.vY < 0.949999988079071;
      v5 = igi2_frame.ptTransContext.tMatrix.tX.vZ > 0.05000000074505806 && igi2_frame.ptTransContext.tMatrix.tX.vZ < 0.949999988079071;
      if ( igi2_frame.ptTransContext.tMatrix.tX.vX > 0.0 && v4 && v5 )
      {
        _snprintf((char *const)&igi2_frame.ptTransContext.vFOVX, 0xFFu, "RADIO");
        igi2_frame.ptTransContext.tMatrix.tX.vX = igi2_frame.ptTransContext.tMatrix.tX.vY;
        igi2_frame.ptTransContext.tMatrix.tY.vX = igi2_frame.ptTransContext.tMatrix.tX.vZ * 0.8999999761581421;
      }
      else
      {
        _snprintf((char *const)&igi2_frame.ptTransContext.vFOVX, 0xFFu, "RADIO:%s", ClientFromHumanQTask->zPlayerName);
        igi2_frame.ptTransContext.tMatrix.tY.vX = 0.5;
        igi2_frame.ptTransContext.tMatrix.tX.vX = 0.8999999761581421;
        if ( igi2_frame.ptTransContext.tMatrix.tY.vZ <= 0.0 )
          igi2_frame.ptTransContext.tMatrix.tX.vX = 0.10000000149011612;
      }
      StatusScreen_DrawLocator(
        (struct StatusScreen_t *)LODWORD(igi2_frame.ptTransContext.tMatrix.tY.vY),
        igi2_frame.ptTransContext.tMatrix.tX.vX,
        igi2_frame.ptTransContext.tMatrix.tY.vX,
        vX,
        *(float *)&igi2_frame.ptTransContext.tPos.vZ,
        0.0,
        128.0,
        0.0,
        (char *)&igi2_frame.ptTransContext.vFOVX);
    }
  }
}

// source: j/0/human/network/humanremote.c:734  [anchor-refs]
void __cdecl HumanRemote_MoveInWorld(struct HumanRemote_t *ptHumanRemote)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[16]; struct QTask_s *ptHumanViewQTask; };
    struct { char igi2_o2[28]; struct real64x3_t ptPos; };
    struct { char igi2_o3[52]; struct CollisionEvaluateContext_s nNumPoints; };
    struct { char igi2_o4[60]; struct QIntersection_s ptIntersection; };
    struct { char igi2_o5[200]; int v10; };
    char igi2_extent[232];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  enum SplineRead_e v1; // ebp
  int ePose; // eax
  int v3; // eax
  double v4; // st7

  igi2_frame.ptHumanViewQTask = ptHumanRemote->tHuman.ptHumanViewQTask;
  v1 = AppContext_tAppContext.isServer != false;
  Spline_ReadPosNow((struct Spline_s *)&ptHumanRemote->tSpline.x[1], v1, &igi2_frame.ptPos);
  ePose = ptHumanRemote->tHuman.ePose;
  if ( ePose )
  {
    v3 = ePose - 1;
    if ( v3 )
    {
      if ( v3 != 1 )
      {
        LDebug_Error("Illegal pose");
        abort();
      }
      v4 = 409.6;
    }
    else
    {
      v4 = 1228.8;
    }
  }
  else
  {
    v4 = 3686.4;
  }
  qmemcpy(&igi2_frame.ptIntersection, &ptHumanRemote->tLastIncomingPos.vY, 0x18u);
  igi2_frame.ptIntersection.tPos.vY = igi2_frame.ptIntersection.tPos.vY + v4;
  igi2_frame.ptPos.vZ = igi2_frame.ptPos.vZ + v4;
  igi2_frame.nNumPoints.ptQTask = &ptHumanRemote->tHuman.tBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask;
  World_TraceLinesSpecificMesh(
    Game_ptGame->ptWorld,
    (struct QIntersection_s *)&igi2_frame.ptIntersection.tLocalNormal.vY,
    (struct real64x3_t *)&igi2_frame.ptIntersection,
    &igi2_frame.ptPos,
    1,
    GameFunctions_eObjectCollisionEvaluateQTaskEvent,
    &igi2_frame.nNumPoints,
    0xFFFFFFFF,
    1);
  igi2_frame.ptPos.vZ = igi2_frame.ptPos.vZ - v4;
  if ( !igi2_frame.v10 )
  {
    igi2_frame.ptDynCubeObj = sqrt(
                     ptHumanRemote->tHuman.tBoneDynCubeObj.tRootTranslation.vY
                   * ptHumanRemote->tHuman.tBoneDynCubeObj.tRootTranslation.vY
                   + ptHumanRemote->tHuman.tBoneDynCubeObj.tRootTranslation.vZ
                   * ptHumanRemote->tHuman.tBoneDynCubeObj.tRootTranslation.vZ
                   + ptHumanRemote->tHuman.tBoneDynCubeObj.tRootTranslation.vX
                   * ptHumanRemote->tHuman.tBoneDynCubeObj.tRootTranslation.vX)
                 + ptHumanRemote->tHuman.tBoneDynCubeObj.vRadius;
    World_MoveDynCubeObjRadius(
      Game_ptGame->ptWorld,
      &ptHumanRemote->tHuman.tBoneDynCubeObj.tModelObj.tDynCubeObj,
      &igi2_frame.ptPos,
      igi2_frame.ptDynCubeObj);
    Spline_ReadPosNow(
      (struct Spline_s *)&ptHumanRemote->tRotationSpline.x[1],
      v1,
      (struct real64x3_t *)&igi2_frame.ptIntersection.tPos.vZ);
    *(float *)&igi2_frame.ptHumanViewQTask[12].ptNext = igi2_frame.ptIntersection.tPos.vZ;
    ptHumanRemote->tHuman.vIdealGamma = *(double *)&igi2_frame.ptIntersection.tLocalPos.vZ;
  }
}

void __cdecl sub_459250(struct QTask_s *ptVector)
{
  struct QReference_s *v1; // eax

  v1 = QTask_NewQTaskRef(ptVector);
  QVector_AddElement(RunDelayed_ptRunDelayedQTaskRefVector, v1);
}

// source: j/0/human/network/humanremote.c:801  [anchor-caller]
void __cdecl HumanRemote_RunDelayedHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { __int16 eQTaskEvent[2]; };
    struct { char igi2_o1[4]; int v8; };
    struct { char igi2_o2[8]; struct QTask_s *v9; };
    struct { char igi2_o3[12]; int v10; };
    char igi2_extent[56];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptTail; // esi
  struct QTask_s *ptNext; // ebx
  struct QTask_s *v3; // eax
  struct QTask_s *ptHead; // eax
  struct QReference_s *v5; // ecx
  int v6; // eax

  ptTail = ptQTask[33].tQTaskChildren.ptTail;
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][Human_eQTaskType].pfHandler)(ptQTask);
  HumanRemote_MoveInWorld((struct HumanRemote_t *)ptQTask);
  AnimController_Step(
    (struct AnimController_t *)ptTail[16].tQTaskRefList.ptTail,
    (int)ptTail[16].tQTaskRefList.ptTail[5].ptPrev + (unsigned int)ptTail[16].tQTaskRefList.ptTail[5].pxObject);
  ptNext = ptQTask[81].ptNext;
  if ( ptQTask[81].ptPrev != ptNext && ptNext != (struct QTask_s *)-1 )
  {
    if ( ptNext == (struct QTask_s *)46 )
    {
      HumanAnim_SetAnimationAtEndFromState(ptQTask, 46, 0.0);
      ptQTask[34].tQTaskChildren.ptTail[1].tQTaskRefList.ptTail = (struct QReference_s *)(__int64)((double)AnimController_nTicksPerFrame
                                                                                                 * -1.0);
    }
    else
    {
      HumanAnim_SetAnimationAndTimeFromState(ptQTask, (int)ptNext, 0, 0.20000000298023224);
      ptQTask[34].tQTaskChildren.ptTail[1].tQTaskRefList.ptTail = (struct QReference_s *)(__int64)(double)AnimController_nTicksPerFrame;
    }
    v3 = ptQTask[81].ptNext;
    ptQTask[81].ptPrev = v3;
    if ( v3 == (struct QTask_s *)36 )
      SoundSys_NewSoundFn(ptQTask[33].tQTaskChildren.ptTail, "jump_1");
  }
  ptHead = ptQTask[81].tQTaskChildren.ptHead;
  if ( ptQTask[81].tQTaskChildren.ptMiddle != ptHead
    || ptHead == (struct QTask_s *)6
    && (v5 = ptQTask[34].tQTaskRefList.ptHead) != nullptr
    && ((int)v5[3].pxObject & 4) != 0
    && ptQTask[33].ptNext[1].tQTaskRefList.ptMiddle )
  {
    HumanRemote_SetUpperBody(ptQTask, (int)ptQTask[81].tQTaskChildren.ptHead);
    ptQTask[81].tQTaskChildren.ptMiddle = ptQTask[81].tQTaskChildren.ptHead;
  }
  HumanRemote_Update(ptQTask);
  ModelObj_UpdateAttachments((struct ModelObj_s *)ptQTask);
  v6 = *(_DWORD *)&ptQTask[81].eQTaskType;
  if ( v6 > 0 )
    *(_DWORD *)&ptQTask[81].eQTaskType = v6 - 1;
  *(_DWORD *)igi2_frame.eQTaskEvent = ptQTask + 1;
  igi2_frame.v9 = nullptr;
  igi2_frame.v10 = 0;
  igi2_frame.v8 = 1;
  World_TriggerQTaskEventXyzSpecificTree(
    World_ptActiveWorld,
    QCube_eGetSectorQTaskEvent,
    igi2_frame.eQTaskEvent,
    (struct real64x3_t *)&ptQTask[1],
    0xFFFFFFFF,
    WORLD_DYNCUBETREE_STATIONARY);
  ptQTask[74].tQTaskChildren.ptTail = igi2_frame.v9;
}

// source: j/0/human/network/humanremote.c:888  [anchor-mhash]
enum bool __cdecl HumanRemote_IsIdleFor(struct HumanRemote_t *ptHumanRemote, int nSeconds)
{
  DWORD PerformanceCounter; // eax
  DWORD v4; // eax

  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  v4 = PerformanceCounter - Timer_nStartTime;
  return !ptHumanRemote->tHuman.isDead
      && ptHumanRemote->tHuman.isActive
      && (int)(v4 - ptHumanRemote->tCompressionState.nAlpha) > 1000 * nSeconds;
}

// source: j/0/human/network/humanremote.c:919  [anchor-caller]
void __cdecl HumanRemote_EnterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  if ( LOBYTE(ptQTask[81].tQTaskRefList.ptTail) )
  {
    HumanRemote_DrawTextAboveHead((struct HumanRemote_t *)ptQTask);
    ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[5][Human_eQTaskType].pfHandler)(
      ptQTask,
      pxContext);
  }
}

// source: j/0/human/network/humanremote.c:945  [anchor-mhash]
void __cdecl HumanRemote_DeleteHandler(struct QTask_s *ptQTask)
{
  BoneDynCubeObj_SetLODVirModel((struct BoneDynCubeObj_s *)ptQTask, nullptr);
  World_RemoveDynCubeObj(Game_ptGame->ptWorld, (struct DynCubeObj_s *)ptQTask);
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[2][Human_eQTaskType].pfHandler)(ptQTask);
}

// source: j/0/human/network/humanremote.c:975  [size]
void __cdecl HumanRemote_ShouldersCallback(
        struct BoneDynCubeObj_s *ptBoneDynCubeObj,
        struct Bone_s *ptParent,
        struct Bone_s *ptBone)
{
  double vRangeX; // st7
  double v4; // st6
  long double v5; // st7
  long double v6; // rt0
  long double v7; // st6
  long double v8; // st5
  long double v9; // st4
  int v10; // ecx
  bool v11; // sf
  double v12; // st7
  double v13; // st6
  double vY; // st5
  long double v15; // st3
  float v_G; // [esp+0h] [ebp-10h]
  float v_F; // [esp+4h] [ebp-Ch]
  float v_D; // [esp+8h] [ebp-8h]
  float v_A; // [esp+Ch] [ebp-4h]
  float ptBoneDynCubeObja = *(float *)&ptBoneDynCubeObj; // [esp+14h] [ebp+4h] ARGSLOT

  if ( !LOBYTE(ptBoneDynCubeObj[2].avMorphWeights[14]) )
  {
    vRangeX = ptBoneDynCubeObj[8].tModelObj.tDynCubeObj.tQObj.vRangeX;
    if ( vRangeX >= 0.0 )
      v4 = 0.24705882370471954;
    else
      v4 = 0.17777778208255768;
    v5 = vRangeX * v4 * 0.5;
    v6 = sin(v5);
    v7 = cos(v5);
    v_A = (ptBone->tOrientation.vY - ptBone->tOrientation.vZ) * 0.0;
    v_D = (ptBone->tOrientation.vW - ptBone->tOrientation.vX) * 0.0;
    v_F = (ptBone->tOrientation.vY + ptBone->tOrientation.vX) * v6;
    v_G = (ptBone->tOrientation.vW - ptBone->tOrientation.vZ) * v7;
    v8 = (ptBone->tOrientation.vW + ptBone->tOrientation.vZ) * v7;
    v9 = v_G + v8 + v_F;
    ptBoneDynCubeObja = ((ptBone->tOrientation.vX - ptBone->tOrientation.vY) * -v6 + v9) * 0.5;
    ptBone->tOrientation.vX = (ptBone->tOrientation.vX + ptBone->tOrientation.vW) * (v6 + v7) + ptBoneDynCubeObja - v9;
    ptBone->tOrientation.vY = (ptBone->tOrientation.vY + ptBone->tOrientation.vZ) * (v7 - v6) + ptBoneDynCubeObja - v8;
    v10 = ptBone->tOrientation.nOps + 1;
    v11 = ptBone->tOrientation.nOps - 999 < 0;
    ptBone->tOrientation.nOps = v10;
    v12 = ptBoneDynCubeObja + v_D - v_G;
    ptBone->tOrientation.vZ = v12;
    v13 = ptBoneDynCubeObja + v_A - v_F;
    ptBone->tOrientation.vW = v13;
    if ( !(v11 ^ __OFSUB__(v10, 1000) | (v10 == 1000)) )
    {
      vY = ptBone->tOrientation.vY;
      ptBone->tOrientation.nOps = 0;
      v15 = 1.0 / sqrt(v13 * v13 + v12 * v12 + ptBone->tOrientation.vX * ptBone->tOrientation.vX + vY * vY);
      ptBone->tOrientation.vX = ptBone->tOrientation.vX * v15;
      ptBone->tOrientation.vY = ptBone->tOrientation.vY * v15;
      ptBone->tOrientation.vZ = v12 * v15;
      ptBone->tOrientation.vW = v13 * v15;
    }
  }
}

// source: j/0/human/network/humanremote.c:1016  [size]
void __cdecl HumanRemote_UpperBackCallback(
        struct BoneDynCubeObj_s *ptBoneDynCubeObj,
        struct Bone_s *ptParent,
        struct Bone_s *ptBone)
{
  double vRangeX; // st7
  double v4; // st6
  long double v5; // st7
  long double v6; // rt0
  long double v7; // st6
  long double v8; // st5
  long double v9; // st4
  int v10; // ecx
  bool v11; // sf
  double v12; // st7
  double v13; // st6
  double vY; // st5
  long double v15; // st3
  float v_G; // [esp+0h] [ebp-10h]
  float v_F; // [esp+4h] [ebp-Ch]
  float v_D; // [esp+8h] [ebp-8h]
  float v_A; // [esp+Ch] [ebp-4h]
  float ptBoneDynCubeObja = *(float *)&ptBoneDynCubeObj; // [esp+14h] [ebp+4h] ARGSLOT

  if ( !LOBYTE(ptBoneDynCubeObj[2].avMorphWeights[14]) )
  {
    vRangeX = ptBoneDynCubeObj[8].tModelObj.tDynCubeObj.tQObj.vRangeX;
    if ( vRangeX >= 0.0 )
      v4 = 0.33529412746429443;
    else
      v4 = 0.31111112236976624;
    v5 = vRangeX * v4 * 0.5;
    v6 = sin(v5);
    v7 = cos(v5);
    v_A = (ptBone->tOrientation.vY - ptBone->tOrientation.vZ) * 0.0;
    v_D = (ptBone->tOrientation.vW - ptBone->tOrientation.vX) * 0.0;
    v_F = (ptBone->tOrientation.vY + ptBone->tOrientation.vX) * v6;
    v_G = (ptBone->tOrientation.vW - ptBone->tOrientation.vZ) * v7;
    v8 = (ptBone->tOrientation.vW + ptBone->tOrientation.vZ) * v7;
    v9 = v_G + v8 + v_F;
    ptBoneDynCubeObja = ((ptBone->tOrientation.vX - ptBone->tOrientation.vY) * -v6 + v9) * 0.5;
    ptBone->tOrientation.vX = (ptBone->tOrientation.vX + ptBone->tOrientation.vW) * (v6 + v7) + ptBoneDynCubeObja - v9;
    ptBone->tOrientation.vY = (ptBone->tOrientation.vY + ptBone->tOrientation.vZ) * (v7 - v6) + ptBoneDynCubeObja - v8;
    v10 = ptBone->tOrientation.nOps + 1;
    v11 = ptBone->tOrientation.nOps - 999 < 0;
    ptBone->tOrientation.nOps = v10;
    v12 = ptBoneDynCubeObja + v_D - v_G;
    ptBone->tOrientation.vZ = v12;
    v13 = ptBoneDynCubeObja + v_A - v_F;
    ptBone->tOrientation.vW = v13;
    if ( !(v11 ^ __OFSUB__(v10, 1000) | (v10 == 1000)) )
    {
      vY = ptBone->tOrientation.vY;
      ptBone->tOrientation.nOps = 0;
      v15 = 1.0 / sqrt(v13 * v13 + v12 * v12 + ptBone->tOrientation.vX * ptBone->tOrientation.vX + vY * vY);
      ptBone->tOrientation.vX = ptBone->tOrientation.vX * v15;
      ptBone->tOrientation.vY = ptBone->tOrientation.vY * v15;
      ptBone->tOrientation.vZ = v12 * v15;
      ptBone->tOrientation.vW = v13 * v15;
    }
  }
}

// source: j/0/human/network/humanremote.c:1057  [anchor-mhash]
void __cdecl HumanRemote_LowerBackCallback(
        struct BoneDynCubeObj_s *ptBoneDynCubeObj,
        struct Bone_s *ptParent,
        struct Bone_s *ptBone)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v_J; };
    struct { float v_Ja; };
    struct { float v_Jb; };
    struct { char igi2_o3[4]; float v_I; };
    struct { char igi2_o4[4]; float v_Ia; };
    struct { char igi2_o5[8]; float v_H; };
    struct { char igi2_o6[8]; float v_Ha; };
    struct { char igi2_o7[12]; float v_G; };
    struct { char igi2_o8[12]; float v_Ga; };
    struct { char igi2_o9[16]; float v_F; };
    struct { char igi2_o10[16]; float v_Fa; };
    struct { char igi2_o11[16]; float v_Fb; };
    struct { char igi2_o12[20]; float v_C; };
    struct { char igi2_o13[20]; float v_Ca; };
    struct { char igi2_o14[20]; float v_Cb; };
    struct { char igi2_o15[24]; float v_D; };
    struct { char igi2_o16[24]; float v_Da; };
    struct { char igi2_o17[28]; float v_A; };
    struct { char igi2_o18[28]; float v_Aa; };
    struct { char igi2_o19[28]; float v_Ab; };
    struct { char igi2_o20[32]; float v54; };
    struct { char igi2_o21[32]; float v55; };
    struct { char igi2_o22[36]; struct real64x3_t tQuat; };
    char igi2_extent[60];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  float vY; // eax
  double v4; // st7
  double v5; // st6
  int v6; // eax
  double v7; // st5
  double v8; // st4
  int v9; // ecx
  double v10; // st7
  double v11; // st6
  double v12; // st5
  long double v13; // rt1
  double v14; // st6
  double v15; // st7
  int v16; // eax
  double vX; // st6
  long double v18; // st6
  int iBone; // eax
  double v20; // st7
  double v21; // st7
  double v22; // st6
  long double v23; // st7
  long double v24; // rt0
  long double v25; // st6
  long double v26; // st5
  long double v27; // st4
  int v28; // eax
  bool v29; // sf
  double v30; // st7
  double v31; // st6
  double v32; // st5
  long double v33; // st3

  if ( !LOBYTE(ptBoneDynCubeObj[2].avMorphWeights[14]) )
  {
    vY = ptBoneDynCubeObj[3].tModelObj.tRelativeOrientation.tY.vY;
    if ( vY != 0.0 )
    {
      v4 = -ptParent->tOrientation.vX;
      HIDWORD(igi2_frame.tQuat.vY) = LODWORD(ptParent->tOrientation.vW);
      v5 = -ptParent->tOrientation.vY;
      v6 = **(_DWORD **)(LODWORD(vY) + 80);
      v7 = -ptParent->tOrientation.vZ;
      igi2_frame.v_A = (ptBone->tOrientation.vY - ptBone->tOrientation.vZ) * (v7 - v5);
      igi2_frame.v_C = (ptBone->tOrientation.vZ + ptBone->tOrientation.vY) * (*((float *)&igi2_frame.tQuat.vY + 1) - v4);
      igi2_frame.v_D = (ptBone->tOrientation.vW - ptBone->tOrientation.vX) * (v5 - ptParent->tOrientation.vZ);
      igi2_frame.v_F = (ptBone->tOrientation.vX + ptBone->tOrientation.vY) * (v4 - ptParent->tOrientation.vZ);
      igi2_frame.v_G = (ptBone->tOrientation.vW - ptBone->tOrientation.vZ)
          * (*((float *)&igi2_frame.tQuat.vY + 1) - ptParent->tOrientation.vY);
      v8 = (ptBone->tOrientation.vZ + ptBone->tOrientation.vW) * (*((float *)&igi2_frame.tQuat.vY + 1) - v5);
      igi2_frame.v_H = v8;
      igi2_frame.v_Ia = v8 + igi2_frame.v_G + igi2_frame.v_F;
      igi2_frame.v_Ja = ((ptBone->tOrientation.vX - ptBone->tOrientation.vY) * (v7 - v4) + igi2_frame.v_Ia) * 0.5;
      v9 = ptParent->tOrientation.nOps + ptBone->tOrientation.nOps + 1;
      v10 = (ptBone->tOrientation.vX + ptBone->tOrientation.vW) * (*((float *)&igi2_frame.tQuat.vY + 1) + v4) + igi2_frame.v_Ja - igi2_frame.v_Ia;
      v11 = igi2_frame.v_Ja + igi2_frame.v_C - igi2_frame.v_H;
      v12 = igi2_frame.v_Ja + igi2_frame.v_D - igi2_frame.v_G;
      *((float *)&igi2_frame.tQuat.vY + 1) = igi2_frame.v_Ja + igi2_frame.v_A - igi2_frame.v_F;
      if ( v9 > 1000 )
      {
        v9 = 0;
        v13 = 1.0 / sqrt(*((float *)&igi2_frame.tQuat.vY + 1) * *((float *)&igi2_frame.tQuat.vY + 1) + v12 * v12 + v11 * v11 + v10 * v10);
        v10 = v10 * v13;
        v11 = v11 * v13;
        v12 = v12 * v13;
        *((float *)&igi2_frame.tQuat.vY + 1) = *((float *)&igi2_frame.tQuat.vY + 1) * v13;
      }
      igi2_frame.v54 = (*(float *)(v6 + 20) - *(float *)(v6 + 16)) * (v11 - v12);
      igi2_frame.v_Aa = (*(float *)(v6 + 24) - *(float *)(v6 + 12)) * (v12 + v11);
      igi2_frame.v_Da = (*(float *)(v6 + 16) + *(float *)(v6 + 20)) * (*((float *)&igi2_frame.tQuat.vY + 1) - v10);
      igi2_frame.v_Ca = (v11 + v10) * (*(float *)(v6 + 20) + *(float *)(v6 + 12));
      igi2_frame.v_Ha = (*(float *)(v6 + 24) + *(float *)(v6 + 16)) * (*((float *)&igi2_frame.tQuat.vY + 1) - v12);
      igi2_frame.v_Ga = (*(float *)(v6 + 24) - *(float *)(v6 + 16)) * (*((float *)&igi2_frame.tQuat.vY + 1) + v12);
      igi2_frame.v_Fa = igi2_frame.v_Ga + igi2_frame.v_Ha + igi2_frame.v_Ca;
      v14 = ((v10 - v11) * (*(float *)(v6 + 20) - *(float *)(v6 + 12)) + igi2_frame.v_Fa) * 0.5;
      ptBone->tOrientation.vX = (*(float *)(v6 + 24) + *(float *)(v6 + 12)) * (*((float *)&igi2_frame.tQuat.vY + 1) + v10)
                              + v14
                              - igi2_frame.v_Fa;
      igi2_frame.v_J = igi2_frame.v_Aa + v14 - igi2_frame.v_Ga;
      ptBone->tOrientation.vY = igi2_frame.v_J;
      igi2_frame.v_I = igi2_frame.v_Da + v14 - igi2_frame.v_Ha;
      ptBone->tOrientation.vZ = igi2_frame.v_I;
      v15 = v14 + igi2_frame.v54 - igi2_frame.v_Ca;
      ptBone->tOrientation.vW = v15;
      v16 = *(_DWORD *)(v6 + 28) + v9 + 1;
      ptBone->tOrientation.nOps = v16;
      if ( v16 > 1000 )
      {
        vX = ptBone->tOrientation.vX;
        ptBone->tOrientation.nOps = 0;
        v18 = 1.0 / sqrt(v15 * v15 + igi2_frame.v_I * igi2_frame.v_I + igi2_frame.v_J * igi2_frame.v_J + vX * vX);
        ptBone->tOrientation.vX = ptBone->tOrientation.vX * v18;
        ptBone->tOrientation.vY = igi2_frame.v_J * v18;
        ptBone->tOrientation.vZ = igi2_frame.v_I * v18;
        ptBone->tOrientation.vW = v15 * v18;
      }
    }
    iBone = ptBoneDynCubeObj[3].tModelObj.tAttachContext.iBone;
    if ( iBone == 83 || !iBone )
    {
      Spline_ReadPosNow(
        (struct Spline_s *)&ptBoneDynCubeObj[7].isTouched,
        (enum SplineRead_e)(AppContext_tAppContext.isServer != false),
        &igi2_frame.tQuat);
      v20 = igi2_frame.tQuat.vX;
    }
    else
    {
      v20 = 0.0;
    }
    v21 = (v20 - ptBoneDynCubeObj[8].tModelObj.tDynCubeObj.tQObj.vRangeX) * 0.20000000298023224
        + ptBoneDynCubeObj[8].tModelObj.tDynCubeObj.tQObj.vRangeX;
    ptBoneDynCubeObj[8].tModelObj.tDynCubeObj.tQObj.vRangeX = v21;
    if ( v21 >= 0.0 )
      v22 = 0.3235294222831726;
    else
      v22 = 0.5;
    v23 = v21 * v22 * 0.5;
    v24 = sin(v23);
    v25 = cos(v23);
    igi2_frame.v_Ab = (ptBone->tOrientation.vY - ptBone->tOrientation.vZ) * 0.0;
    igi2_frame.v55 = (ptBone->tOrientation.vW - ptBone->tOrientation.vX) * 0.0;
    igi2_frame.v_Fb = (ptBone->tOrientation.vX + ptBone->tOrientation.vY) * v24;
    igi2_frame.v_Cb = (ptBone->tOrientation.vW - ptBone->tOrientation.vZ) * v25;
    v26 = (ptBone->tOrientation.vZ + ptBone->tOrientation.vW) * v25;
    v27 = igi2_frame.v_Cb + v26 + igi2_frame.v_Fb;
    igi2_frame.v_Jb = ((ptBone->tOrientation.vX - ptBone->tOrientation.vY) * -v24 + v27) * 0.5;
    ptBone->tOrientation.vX = (ptBone->tOrientation.vX + ptBone->tOrientation.vW) * (v25 + v24) + igi2_frame.v_Jb - v27;
    ptBone->tOrientation.vY = (ptBone->tOrientation.vZ + ptBone->tOrientation.vY) * (v25 - v24) + igi2_frame.v_Jb - v26;
    v28 = ptBone->tOrientation.nOps + 1;
    v29 = ptBone->tOrientation.nOps - 999 < 0;
    v30 = igi2_frame.v_Jb + igi2_frame.v55 - igi2_frame.v_Cb;
    ptBone->tOrientation.nOps = v28;
    ptBone->tOrientation.vZ = v30;
    v31 = igi2_frame.v_Jb + igi2_frame.v_Ab - igi2_frame.v_Fb;
    ptBone->tOrientation.vW = v31;
    if ( !(v29 ^ __OFSUB__(v28, 1000) | (v28 == 1000)) )
    {
      v32 = ptBone->tOrientation.vY;
      ptBone->tOrientation.nOps = 0;
      v33 = 1.0 / sqrt(v31 * v31 + v30 * v30 + ptBone->tOrientation.vX * ptBone->tOrientation.vX + v32 * v32);
      ptBone->tOrientation.vX = ptBone->tOrientation.vX * v33;
      ptBone->tOrientation.vY = ptBone->tOrientation.vY * v33;
      ptBone->tOrientation.vZ = v30 * v33;
      ptBone->tOrientation.vW = v31 * v33;
    }
  }
}

// source: j/0/human/network/humanremote.c:1146  [anchor-mhash]
void __cdecl HumanRemote_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptTail; // edi
  __int16 v3; // cx
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptHead; // eax

  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][Human_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  ptTail = ptQTask[33].tQTaskChildren.ptTail;
  v3 = Attach_eAttachEvent;
  LOBYTE(ptTail[10].ptNext) = 1;
  BYTE1(ptTail[10].ptNext) = 1;
  ptTail[5].tQTaskChildren.ptTail = (struct QTask_s *)-1;
  ptTail[7].ptPrev = nullptr;
  ptTail[5].tQTaskRefList.ptHead = nullptr;
  QTask_TriggerQTaskEventParent(ptTail, v3, &ptTail[5].tQTaskChildren.ptTail);
  ModelObj_CalcRelativePosAndOrientation((struct ModelObj_s *)ptTail);
  if ( *(_DWORD *)&ptQTask[2].eQTaskType )
  {
    *(_DWORD *)(80 * (int)ptQTask[35].ptParent + *(_DWORD *)&ptQTask[7].eQTaskType + 76) = HumanRemote_LowerBackCallback;
    *(_DWORD *)(80 * *(_DWORD *)&ptQTask[35].eQTaskType + *(_DWORD *)&ptQTask[7].eQTaskType + 76) = HumanRemote_UpperBackCallback;
    *(_DWORD *)(80 * (int)ptQTask[36].ptNext + *(_DWORD *)&ptQTask[7].eQTaskType + 76) = HumanRemote_ShouldersCallback;
  }
  ptNext = ptQTask[33].ptNext[5].ptNext;
  if ( ptNext )
  {
    ptHead = ptNext->tQTaskChildren.ptHead;
    if ( ptHead )
    {
      ptHead[4].tQTaskChildren.ptMiddle = (struct QTask_s *)((int)ptHead[4].tQTaskChildren.ptMiddle | 4);
      *(_DWORD *)&ptHead[3].eQTaskType = 50;
    }
  }
}

// source: j/0/human/network/humanremote.c:1194  [anchor-mhash]
void __cdecl HumanRemote_RemoveDynCubeObjHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // edx
  int v3; // ecx

  if ( BYTE1(ptQTask[29].tQTaskRefList.ptHead) )
  {
    v2 = BoneDynCubeObj_eQTaskType;
    v3 = 511 * DynCubeObj_eDynCubeObjRemoveQTaskEvent;
    BYTE1(ptQTask[29].tQTaskRefList.ptHead) = 0;
    ((void (__cdecl *)(struct QTask_s *, ...))QTask_aatQTaskFinalEvent[0][v2 + v3].pfHandler)(ptQTask, pxContext);
  }
}

// source: j/0/human/network/humanremote.c:1223  [anchor-mhash]
void __cdecl HumanRemote_HumanUpdateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  if ( !LOBYTE(ptQTask[25].tQTaskChildren.ptTail) )
  {
    qmemcpy(&ptQTask[12].ptParent, &ptQTask[19].ptPrev, 0xFCu);
    qmemcpy(&ptQTask[19].ptPrev, *(void **)pxContext, 0xFCu);
  }
  HumanRemote_Update(ptQTask);
}

// source: j/0/human/network/humanremote.c:1261  [anchor-mhash]
void __cdecl HumanRemote_WeaponHitHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct Client_s *ptKillerClient; };
    struct { char igi2_o1[4]; struct Client_s *ptVictimClient; };
    struct { char igi2_o2[12]; int eDamagePart; };
    struct { char igi2_o3[16]; struct ServerGameMessageKill_s tKillMessage; };
    struct { char igi2_o4[48]; struct ServerGameMessageDamage_s tDamageMessage; };
    char igi2_extent[120];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct HumanDamage_t *p_tQTaskRefList; // esi
  struct QTask_s *v3; // edi
  struct Client_s *ClientFromHumanQTask; // eax
  enum DamagePart_e DamagePartFromWeaponHit; // eax
  double v6; // st7
  int v7; // edi
  double v8; // st7
  int Timer; // eax
  float v10; // ecx
  int v11; // esi
  float v12; // eax
  float v13; // ecx
  float v14; // edx
  struct QTask_s *ptMiddle; // esi
  int ClientNetworkIDFromHumanQTask; // eax
  int v17; // ecx
  int v18; // ebx
  int nCounter; // edx
  struct Human_s *v20; // eax
  int nLastHiDown; // eax

  p_tQTaskRefList = (struct HumanDamage_t *)&ptQTask[25].tQTaskRefList;
  igi2_frame.ptKillerClient = nullptr;
  igi2_frame.ptVictimClient = NetManager_GetClientFromHumanQTask(ptQTask);
  if ( BYTE1(ptQTask[29].tQTaskRefList.ptHead) )
  {
    if ( !LOBYTE(ptQTask[29].tQTaskRefList.ptHead) && !Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
    {
      v3 = *((struct QTask_s **)pxContext + 5);
      if ( QTask_IsQTaskTypeDerived(v3->eQTaskType, Human_eQTaskType) == false
        || (ClientFromHumanQTask = NetManager_GetClientFromHumanQTask(v3),
            (igi2_frame.ptKillerClient = ClientFromHumanQTask) == nullptr)
        || ClientFromHumanQTask->eTeam != igi2_frame.ptVictimClient->eTeam
        || ServerConfig_tServerConfig.isPublic )
      {
        DamagePartFromWeaponHit = HumanDamage_GetDamagePartFromWeaponHit(
                                    p_tQTaskRefList,
                                    (struct BoneDynCubeObj_s *)ptQTask,
                                    (struct WeaponHitContext_t *)pxContext);
        v6 = *((float *)pxContext + 1);
        v7 = DamagePartFromWeaponHit;
        ptQTask[29].tQTaskChildren.ptHead = (struct QTask_s *)DamagePartFromWeaponHit;
        v8 = v6 * p_tQTaskRefList->atDamagePart[DamagePartFromWeaponHit].vDamageMultiplier;
        igi2_frame.eDamagePart = DamagePartFromWeaponHit;
        p_tQTaskRefList->atDamagePart[DamagePartFromWeaponHit].vDamage = v8
                                                                       + p_tQTaskRefList->atDamagePart[DamagePartFromWeaponHit].vDamage;
        p_tQTaskRefList->vDamage = v8 + p_tQTaskRefList->vDamage;
        Human_UpdateDie((struct Human_s *)ptQTask);
        if ( !Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
        {
          igi2_frame.tDamageMessage.tBaseMessage.eGameMessage = 1145130311;
          Timer = NetManager_GetTimer();
          v10 = *((float *)pxContext + 1);
          igi2_frame.tDamageMessage.tBaseMessage.nLocalTime = Timer;
          igi2_frame.tDamageMessage.iVictimID = igi2_frame.ptVictimClient->eNetworkID;
          igi2_frame.tDamageMessage.vDamage = v10;
          igi2_frame.tDamageMessage.eDamagePart = v7;
          if ( igi2_frame.ptKillerClient )
            igi2_frame.tDamageMessage.iKillerID = igi2_frame.ptKillerClient->eNetworkID;
          else
            igi2_frame.tDamageMessage.iKillerID = -1;
          v11 = *(_DWORD *)pxContext;
          v12 = *((float *)pxContext + 2);
          igi2_frame.tDamageMessage.eDamageType = *((_DWORD *)pxContext + 7) != 0 ? 0 : 3;
          qmemcpy(&igi2_frame.tDamageMessage.tHitPos, (void *)(v11 + 8), sizeof(igi2_frame.tDamageMessage.tHitPos));
          v13 = *((float *)pxContext + 3);
          v14 = *((float *)pxContext + 4);
          igi2_frame.tDamageMessage.tHitDir.vX = v12;
          igi2_frame.tDamageMessage.tHitDir.vY = v13;
          ptMiddle = Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle;
          igi2_frame.tDamageMessage.tHitDir.vZ = v14;
          ClientNetworkIDFromHumanQTask = NetManager_GetClientNetworkIDFromHumanQTask(ptQTask);
          NetManager_SendGameMessage(
            ClientNetworkIDFromHumanQTask,
            (int)ptMiddle,
            NETWORKQUEUE_GUARANTEED,
            &igi2_frame.tDamageMessage.tBaseMessage,
            0x48u);
          if ( QTask_IsQTaskTypeDerived(*(_WORD *)(*((_DWORD *)pxContext + 5) + 36), Human_eQTaskType) )
            NetManager_SendGameMessage(
              igi2_frame.ptKillerClient->eNetworkID,
              (int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle,
              NETWORKQUEUE_GUARANTEED,
              &igi2_frame.tDamageMessage.tBaseMessage,
              0x48u);
          if ( *(float *)&ptQTask[25].tQTaskRefList.ptHead >= (double)*(float *)&ptQTask[25].tQTaskRefList.ptMiddle )
          {
            DebugConsole_printf(
              "HumanRemote.WeaponHitHandler: Setting up kill message on client %d\n",
              igi2_frame.ptVictimClient->eNetworkID);
            igi2_frame.tKillMessage.tBaseMessage.eGameMessage = 1263094860;
            igi2_frame.tKillMessage.tBaseMessage.nLocalTime = NetManager_GetTimer();
            if ( igi2_frame.ptKillerClient )
            {
              v17 = *(_DWORD *)(*((_DWORD *)pxContext + 6) + 148);
              igi2_frame.tKillMessage.eKillerNetworkID = igi2_frame.ptKillerClient->eNetworkID;
              igi2_frame.tKillMessage.eWeaponID = v17;
            }
            else
            {
              igi2_frame.tKillMessage.eKillerNetworkID = -1;
              igi2_frame.tKillMessage.eWeaponID = -1;
            }
            v18 = *((_DWORD *)pxContext + 7);
            igi2_frame.tKillMessage.eVictimNetworkID = igi2_frame.ptVictimClient->eNetworkID;
            nCounter = igi2_frame.ptVictimClient->tReceiveTimeBuffer.nCounter;
            igi2_frame.tKillMessage.eDamagePart = igi2_frame.eDamagePart;
            v20 = *(struct Human_s **)(nCounter + 8);
            igi2_frame.tKillMessage.eDamageType = v18 != 0 ? 0 : 3;
            if ( Human_isInsideSpawnArea(v20) == false
              || (nLastHiDown = igi2_frame.ptVictimClient->tDownload.nLastHiDown, igi2_frame.tKillMessage.isSpawnKill = 1, nLastHiDown <= 0) )
            {
              igi2_frame.tKillMessage.isSpawnKill = 0;
            }
            NetManager_SendGameMessage(
              0,
              (int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle,
              NETWORKQUEUE_GUARANTEED,
              &igi2_frame.tKillMessage.tBaseMessage,
              0x20u);
          }
        }
      }
    }
  }
}

// source: j/0/human/network/humanremote.c:1484  [anchor-mhash]
void __cdecl HumanRemote_ExplosionHitHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptExplosionHitContext; };
    struct { char igi2_o1[20]; float ptHuman; };
    struct { char igi2_o2[20]; struct Human_s *ptHumana; };
    struct { char igi2_o3[24]; struct Client_s *ClientFromHumanQTask; };
    struct { char igi2_o4[28]; struct Client_s *v16; };
    struct { char igi2_o5[32]; struct NetManagerGameMessage_s v17; };
    struct { char igi2_o6[40]; int v18; };
    struct { char igi2_o7[44]; int v19; };
    struct { char igi2_o8[48]; int v20; };
    struct { char igi2_o9[52]; int v21; };
    struct { char igi2_o10[56]; int v22; };
    struct { char igi2_o11[60]; char v23; };
    struct { char igi2_o12[64]; struct NetManagerGameMessage_s ptGameMessage; };
    struct { char igi2_o13[72]; float v25; };
    struct { char igi2_o14[76]; int v26; };
    struct { char igi2_o15[80]; int v27; };
    struct { char igi2_o16[84]; int v28; };
    char igi2_extent[136];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v2; // edi
  double v3; // st7
  struct Human_s *v4; // eax
  int eNetworkID; // eax
  struct QTask_s *ptNetManagerQTask; // edx
  struct Human_s *ptMiddle; // eax
  int ClientNetworkIDFromHumanQTask; // eax
  int v9; // eax
  unsigned __int16 v10; // dx
  int nLastHiDown; // eax

  igi2_frame.v16 = nullptr;
  igi2_frame.ClientFromHumanQTask = NetManager_GetClientFromHumanQTask(ptQTask);
  if ( BYTE1(ptQTask[29].tQTaskRefList.ptHead)
    && !LOBYTE(ptQTask[29].tQTaskRefList.ptHead)
    && !Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    v2 = *((struct QTask_s **)pxContext + 1);
    if ( v2 && QTask_IsQTaskTypeDerived(v2->eQTaskType, Human_eQTaskType) )
      igi2_frame.v16 = NetManager_GetClientFromHumanQTask(v2);
    ptQTask[29].tQTaskChildren.ptHead = (struct QTask_s *)13;
    igi2_frame.ptExplosionHitContext = BoneDynCubeObj_GetRadius((struct BoneDynCubeObj_s *)ptQTask) * 0.3333333432674408;
    v3 = GameFunctions_ResolveExplosionHit(
           (struct ExplosionHitContext_t *)pxContext,
           ptQTask,
           (struct real64x3_t *)&ptQTask[1],
           igi2_frame.ptExplosionHitContext,
           true);
    if ( v3 != 0.0 )
    {
      igi2_frame.ptHuman = v3;
      v4 = Human_ResolveDamage((struct Human_s *)ptQTask, HUMANDAMAGE_PART_CHEST, igi2_frame.ptHuman);
      Human_UpdateDie(v4);
      igi2_frame.ptGameMessage.eGameMessage = 1145130311;
      igi2_frame.ptGameMessage.nLocalTime = NetManager_GetTimer();
      eNetworkID = igi2_frame.ClientFromHumanQTask->eNetworkID;
      igi2_frame.v25 = v3;
      ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
      igi2_frame.v28 = eNetworkID;
      ptMiddle = (struct Human_s *)ptNetManagerQTask[6].tQTaskChildren.ptMiddle;
      igi2_frame.v26 = 13;
      igi2_frame.v27 = 1;
      igi2_frame.ptHumana = ptMiddle;
      ClientNetworkIDFromHumanQTask = NetManager_GetClientNetworkIDFromHumanQTask(ptQTask);
      NetManager_SendGameMessage(
        ClientNetworkIDFromHumanQTask,
        (int)igi2_frame.ptHumana,
        NETWORKQUEUE_GUARANTEED,
        &igi2_frame.ptGameMessage,
        0x48u);
      if ( *(float *)&ptQTask[25].tQTaskRefList.ptHead >= (double)*(float *)&ptQTask[25].tQTaskRefList.ptMiddle )
      {
        DebugConsole_printf(
          "HumanRemote.WeaponHitHandler: Setting up kill message on client %d\n",
          igi2_frame.ClientFromHumanQTask->eNetworkID);
        igi2_frame.v17.eGameMessage = 1263094860;
        igi2_frame.v17.nLocalTime = NetManager_GetTimer();
        if ( igi2_frame.v16 )
        {
          v9 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(igi2_frame.v16->tReceiveTimeBuffer.nCounter + 8) + 1320) + 44);
          igi2_frame.v18 = igi2_frame.v16->eNetworkID;
          if ( v9 )
            igi2_frame.v22 = *(_DWORD *)(*(_DWORD *)(v9 + 16) + 148);
          else
            igi2_frame.v22 = MEMORY[0x94];
        }
        else
        {
          igi2_frame.v18 = -1;
          igi2_frame.v22 = -1;
        }
        v10 = *((_WORD *)pxContext + 4);
        igi2_frame.v19 = igi2_frame.ClientFromHumanQTask->eNetworkID;
        igi2_frame.v20 = 13;
        igi2_frame.v21 = 1;
        if ( QTask_IsQTaskTypeDerived(v10, Mine_eQTaskType) )
        {
          igi2_frame.v21 = 4;
        }
        else if ( QTask_IsQTaskTypeDerived(v10, MineField_eQTaskType) )
        {
          igi2_frame.v21 = 5;
        }
        if ( Human_isInsideSpawnArea(*(struct Human_s **)(igi2_frame.ClientFromHumanQTask->tReceiveTimeBuffer.nCounter + 8)) == false
          || (nLastHiDown = igi2_frame.ClientFromHumanQTask->tDownload.nLastHiDown, igi2_frame.v23 = 1, nLastHiDown <= 0) )
        {
          igi2_frame.v23 = 0;
        }
        NetManager_SendGameMessage(
          0,
          (int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle,
          NETWORKQUEUE_GUARANTEED,
          &igi2_frame.v17,
          0x20u);
      }
    }
  }
}

// source: j/0/human/network/humanremote.c:1632  [size]
void __cdecl HumanRemote_FlashBangHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: j/0/human/network/humanremote.c:1700  [anchor-callee]
void __cdecl HumanRemote_FillGameMessageUpdate(
        struct HumanRemote_t *ptHumanRemote,
        struct ClientGameMessageUpdateBody_s *ptGameMessage)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real64x3_t *ptPos; };
    struct { float ptPosa; };
    struct { char igi2_o2[4]; float ptCompression; };
    struct { char igi2_o3[8]; float vAlpha; };
    struct { char igi2_o4[16]; struct real64x3_t ptEnd; };
    struct { char igi2_o5[40]; struct real64x3_t ptSpeed; };
    struct { char igi2_o6[68]; struct CollisionEvaluateContext_s nNumPoints; };
    struct { char igi2_o7[76]; struct real32x3_t v15; };
    struct { char igi2_o8[88]; struct QIntersection_s ptIntersection; };
    struct { char igi2_o9[228]; int v17; };
    char igi2_extent[260];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // ecx
  int ePose; // eax
  int v4; // eax
  double v5; // st7
  double i; // st7
  float v7; // edi

  if ( Timer_isPerformanceCounter )
  {
    v2 = Timer_GetPerformanceCounter() - Timer_nStartTime;
    igi2_frame.ptPos = (struct real64x3_t *)v2;
  }
  else
  {
    igi2_frame.ptPos = (struct real64x3_t *)(GetTickCount() - Timer_nStartTime);
    v2 = (int)igi2_frame.ptPos;
  }
  Spline_ExtraFromEnd(&igi2_frame.ptEnd, &igi2_frame.ptSpeed, (struct Spline_s *)&ptHumanRemote->tSpline.x[1], v2);
  ePose = ptHumanRemote->tHuman.ePose;
  if ( ePose )
  {
    v4 = ePose - 1;
    if ( v4 )
    {
      if ( v4 != 1 )
      {
        LDebug_Error("Illegal pose");
        abort();
      }
      v5 = 409.6;
    }
    else
    {
      v5 = 1228.8;
    }
  }
  else
  {
    v5 = 3686.4;
  }
  qmemcpy(&igi2_frame.ptIntersection, &ptHumanRemote->tLastIncomingPos.vY, 0x18u);
  igi2_frame.ptIntersection.tPos.vY = igi2_frame.ptIntersection.tPos.vY + v5;
  igi2_frame.ptEnd.vZ = igi2_frame.ptEnd.vZ + v5;
  igi2_frame.nNumPoints.ptQTask = &ptHumanRemote->tHuman.tBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask;
  World_TraceLinesSpecificMesh(
    Game_ptGame->ptWorld,
    (struct QIntersection_s *)&igi2_frame.ptIntersection.tLocalNormal.vY,
    (struct real64x3_t *)&igi2_frame.ptIntersection,
    &igi2_frame.ptEnd,
    1,
    GameFunctions_eObjectCollisionEvaluateQTaskEvent,
    &igi2_frame.nNumPoints,
    0xFFFFFFFF,
    1);
  igi2_frame.ptEnd.vZ = igi2_frame.ptEnd.vZ - v5;
  if ( igi2_frame.v17 )
    qmemcpy(&igi2_frame.ptEnd, &ptHumanRemote->tHuman.tBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos, sizeof(igi2_frame.ptEnd));
  igi2_frame.ptSpeed.vX = igi2_frame.ptSpeed.vX * 1000.0;
  igi2_frame.ptSpeed.vY = igi2_frame.ptSpeed.vY * 1000.0;
  igi2_frame.ptSpeed.vZ = igi2_frame.ptSpeed.vZ * 1000.0;
  igi2_frame.ptEnd.vX = igi2_frame.ptEnd.vX * 0.000244140625;
  igi2_frame.ptEnd.vY = igi2_frame.ptEnd.vY * 0.000244140625;
  igi2_frame.ptEnd.vZ = igi2_frame.ptEnd.vZ * 0.000244140625;
  World_SetInt32CentimeterFromReal64Meter(&igi2_frame.ptEnd, &ptGameMessage->tPosition);
  igi2_frame.v15.vX = igi2_frame.ptSpeed.vX;
  igi2_frame.v15.vY = igi2_frame.ptSpeed.vY;
  igi2_frame.v15.vZ = igi2_frame.ptSpeed.vZ;
  Spline_ExtraFromEnd(
    (struct real64x3_t *)&igi2_frame.ptIntersection.tPos.vZ,
    &igi2_frame.ptSpeed,
    (struct Spline_s *)&ptHumanRemote->tRotationSpline.x[1],
    (int)igi2_frame.ptPos);
  igi2_frame.ptPosa = igi2_frame.ptSpeed.vX * 1000.0;
  *(float *)&igi2_frame.nNumPoints.isEvaluate = igi2_frame.ptSpeed.vZ * 1000.0;
  igi2_frame.ptCompression = igi2_frame.ptIntersection.tPos.vZ;
  for ( i = *(double *)&igi2_frame.ptIntersection.tLocalPos.vZ; i < 0.0; i = i + 6.2831854820251465 )
    ;
  for ( ; i > 6.283185307179589; i = i - 6.2831854820251465 )
    ;
  v7 = *(float *)&igi2_frame.nNumPoints.isEvaluate;
  ptGameMessage->eAnimState = ptHumanRemote->eUpperBody;
  igi2_frame.vAlpha = i - 3.1415927410125732;
  ptGameMessage->eUpperBody = ptHumanRemote->eWeaponID;
  ptGameMessage->isShowPlayer = ptHumanRemote->nRadioTimer;
  Client_CheckCompression(
    (struct ClientMessageCompression_s *)&ptHumanRemote->tCompressionState.nGamma,
    &igi2_frame.v15,
    igi2_frame.ptCompression,
    igi2_frame.ptPosa,
    igi2_frame.vAlpha,
    v7);
  Client_CompressOutput(ptGameMessage, &igi2_frame.v15, igi2_frame.ptCompression, igi2_frame.ptPosa, igi2_frame.vAlpha, v7);
}

// source: j/0/human/network/humanremote.c:1798  [anchor-callee]
int __cdecl HumanRemote_GetSplineTime(int nFuture)
{
  int result; // eax
  int v2; // edx

  result = nFuture;
  if ( ServerConfig_tServerConfig.isTeamDamage < 100 )
  {
    if ( ServerConfig_tServerConfig.isTeamDamage > false )
    {
      v2 = (__int64)((double)(int)ServerConfig_tServerConfig.isTeamDamage * (double)nFuture * -0.009999999776482582);
      if ( 1 - v2 <= nFuture )
        return 1 - v2;
    }
    else
    {
      return 1;
    }
  }
  return result;
}

// source: j/0/human/network/humanremote.c:1835  [anchor-strings]
int __cdecl HumanRemote_GetNetTime(int nRemoteTime)
{
  struct QTask_s *ptNetManagerQTask; // esi
  DWORD PerformanceCounter; // eax
  int v3; // ecx
  char zString[256]; // [esp+4h] [ebp-100h] BYREF

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  v3 = PerformanceCounter
     - Timer_nStartTime
     + (char *)ptNetManagerQTask[6].tQTaskRefList.ptMiddle
     - (char *)ptNetManagerQTask[6].tQTaskRefList.ptTail
     - nRemoteTime;
  if ( v3 >= 0 )
    return PerformanceCounter
         - Timer_nStartTime
         + (char *)ptNetManagerQTask[6].tQTaskRefList.ptMiddle
         - (char *)ptNetManagerQTask[6].tQTaskRefList.ptTail
         - nRemoteTime;
  if ( v3 <= -100 )
  {
    sprintf(zString, "nNetTime == %d\n", v3);
    NetManager_LogMessage(zString);
  }
  return 0;
}

// source: j/0/human/network/humanremote.c:1871  [anchor-mhash]
struct real64x3_t *__cdecl HumanRemote_ExtrapolatePos(
        struct real64x3_t *ptExtrapolatedPos,
        struct real64x3_t *ptNewPos,
        struct real64x3_t *ptNewSpeed,
        int nNetTime,
        int nSplineTime)
{
  double v5; // st7
  struct real64x3_t tExtraPolate; // [esp+8h] [ebp-18h] BYREF

  qmemcpy(&tExtraPolate, ptNewSpeed, sizeof(tExtraPolate));
  v5 = (double)(nSplineTime + nNetTime);
  tExtraPolate.vY = v5 * tExtraPolate.vY;
  tExtraPolate.vZ = v5 * tExtraPolate.vZ;
  ptExtrapolatedPos->vX = tExtraPolate.vX * v5 + ptNewPos->vX;
  ptExtrapolatedPos->vY = tExtraPolate.vY + ptNewPos->vY;
  ptExtrapolatedPos->vZ = tExtraPolate.vZ + ptNewPos->vZ;
  return ptNewPos;
}

// source: j/0/human/network/humanremote.c:1895  [anchor-caller]
int __cdecl HumanRemote_HandleUpdate(
        struct HumanRemote_t *ptHumanRemote,
        struct ClientGameMessageUpdateBody_s *ptBody,
        int nRemoteTime,
        int nFuture)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v20; };
    struct { char igi2_o1[16]; struct real64x3_t *ptOldSpeed; };
    struct { char igi2_o2[20]; struct real64x3_t eRead; };
    struct { char igi2_o3[44]; float pvInAlpha; };
    struct { char igi2_o4[48]; float ptInPos; };
    struct { char igi2_o5[52]; struct real64x3_t ptInPos_4; };
    struct { char igi2_o6[80]; int NetTime; };
    struct { char igi2_o7[84]; struct real64x3_t ptPos; };
    struct { char igi2_o8[108]; struct real64x3_t *ptNewPos; };
    struct { char igi2_o9[112]; enum SplineRead_e v29; };
    struct { char igi2_o10[116]; struct ClientGameMessageUpdateBody_s v30; };
    struct { char igi2_o11[148]; double v31; };
    struct { char igi2_o12[156]; struct real64x3_t v32; };
    char igi2_extent[180];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v4; // ecx
  struct Spline_s *v5; // eax
  int vX_high; // edx
  double v7; // st7
  double v8; // st7
  DWORD PerformanceCounter; // eax
  struct real64x3_t *v10; // ebx
  int v11; // eax
  double v12; // st7
  double v13; // st7
  double v14; // st6
  double v15; // st7
  unsigned __int8 eAnimState; // al
  int v17; // ecx
  int v18; // eax

  igi2_frame.ptNewPos = (struct real64x3_t *)HumanRemote_GetSplineTime(nFuture);
  igi2_frame.NetTime = HumanRemote_GetNetTime(nRemoteTime);
  if ( Timer_isPerformanceCounter )
  {
    v4 = Timer_GetPerformanceCounter() - Timer_nStartTime;
    igi2_frame.ptOldSpeed = (struct real64x3_t *)v4;
  }
  else
  {
    igi2_frame.ptOldSpeed = (struct real64x3_t *)(GetTickCount() - Timer_nStartTime);
    v4 = (int)igi2_frame.ptOldSpeed;
  }
  v5 = (struct Spline_s *)&ptHumanRemote->tRotationSpline.x[1];
  igi2_frame.v30.tPosition.nY = (int)&ptHumanRemote->tRotationSpline.x[1];
  igi2_frame.v29 = AppContext_tAppContext.isServer != false;
  if ( AppContext_tAppContext.isServer )
  {
    if ( AppContext_tAppContext.isServer == false )
    {
      if ( (AppContext_tAppContext.isServer != false) != 2 )
      {
        LDebug_Error("Unknow spline read type used");
        abort();
      }
      goto LABEL_11;
    }
    igi2_frame.v20 = v4;
    goto LABEL_9;
  }
  vX_high = HIDWORD(ptHumanRemote->tLastIncomingPos.vX);
  if ( v4 < vX_high )
  {
LABEL_11:
    Spline_ExtraFromStart((struct real64x3_t *)&igi2_frame.v30.vX, &igi2_frame.ptPos, v5, v4);
    goto LABEL_14;
  }
  igi2_frame.v20 = v4;
  if ( v4 > (int)(LODWORD(ptHumanRemote->tLastIncomingPos.vX) + vX_high) )
  {
LABEL_9:
    Spline_ExtraFromEnd((struct real64x3_t *)&igi2_frame.v30.vX, &igi2_frame.ptPos, v5, igi2_frame.v20);
    goto LABEL_14;
  }
  Spline_OnSpline((struct real64x3_t *)&igi2_frame.v30.vX, &igi2_frame.ptPos, v5, v4);
LABEL_14:
  Client_DecompressInput(
    ptBody,
    &igi2_frame.v32,
    &igi2_frame.eRead,
    (float *)&igi2_frame.v30.eNetworkID,
    &igi2_frame.ptInPos,
    (float *)&igi2_frame.v30.tPosition.nX,
    &igi2_frame.pvInAlpha);
  qmemcpy(&ptHumanRemote->tLastIncomingPos.vY, &igi2_frame.v32, 0x18u);
  if ( ptHumanRemote->nInitRadioTimer == -1
    || sqrt(igi2_frame.eRead.vY * igi2_frame.eRead.vY + igi2_frame.eRead.vZ * igi2_frame.eRead.vZ + igi2_frame.eRead.vX * igi2_frame.eRead.vX) > 0.1 )
  {
    goto LABEL_22;
  }
  v7 = igi2_frame.ptInPos;
  if ( igi2_frame.ptInPos < 0.0 )
    v7 = -v7;
  if ( v7 > 0.01 )
    goto LABEL_22;
  v8 = igi2_frame.pvInAlpha;
  if ( igi2_frame.pvInAlpha < 0.0 )
    v8 = -v8;
  if ( v8 > 0.01 )
  {
LABEL_22:
    if ( Timer_isPerformanceCounter )
      PerformanceCounter = Timer_GetPerformanceCounter();
    else
      PerformanceCounter = GetTickCount();
    ptHumanRemote->tCompressionState.nAlpha = PerformanceCounter - Timer_nStartTime;
  }
  v10 = igi2_frame.ptNewPos;
  igi2_frame.eRead.vX = igi2_frame.eRead.vX * 0.001;
  igi2_frame.eRead.vY = igi2_frame.eRead.vY * 0.001;
  igi2_frame.eRead.vZ = igi2_frame.eRead.vZ * 0.001;
  qmemcpy(&igi2_frame.ptInPos_4, &igi2_frame.eRead, sizeof(igi2_frame.ptInPos_4));
  igi2_frame.v30.tPosition.nZ = (int)igi2_frame.ptNewPos + igi2_frame.NetTime;
  v11 = LODWORD(ptHumanRemote->tRotationSpline.x[0]);
  v12 = (double)((int)igi2_frame.ptNewPos + igi2_frame.NetTime);
  igi2_frame.ptInPos_4.vY = v12 * igi2_frame.ptInPos_4.vY;
  igi2_frame.ptInPos_4.vZ = v12 * igi2_frame.ptInPos_4.vZ;
  igi2_frame.ptPos.vX = igi2_frame.v32.vX + igi2_frame.eRead.vX * v12;
  igi2_frame.ptPos.vY = igi2_frame.ptInPos_4.vY + igi2_frame.v32.vY;
  igi2_frame.ptPos.vZ = igi2_frame.v32.vZ + igi2_frame.ptInPos_4.vZ;
  if ( v11 <= 0 )
  {
    Spline_Initialize(
      (struct Spline_s *)&ptHumanRemote->tSpline.x[1],
      &igi2_frame.ptPos,
      &igi2_frame.ptPos,
      &igi2_frame.eRead,
      &igi2_frame.eRead,
      (int)igi2_frame.ptOldSpeed,
      (int)igi2_frame.ptNewPos);
    v10 = igi2_frame.ptNewPos;
  }
  else
  {
    Spline_Extend((struct Spline_s *)&ptHumanRemote->tSpline.x[1], igi2_frame.v29, &igi2_frame.ptPos, &igi2_frame.eRead, (int)igi2_frame.ptOldSpeed, (int)igi2_frame.ptNewPos);
  }
  igi2_frame.ptPos.vX = *(float *)&igi2_frame.v30.eNetworkID;
  igi2_frame.ptPos.vY = 0.0;
  igi2_frame.ptPos.vZ = *(float *)&igi2_frame.v30.tPosition.nX + 3.1415926535897944;
  qmemcpy(&ptHumanRemote->tLastIncomingRot.vY, &igi2_frame.ptPos, 0x18u);
  igi2_frame.eRead.vX = igi2_frame.ptInPos * 0.001;
  igi2_frame.eRead.vZ = igi2_frame.pvInAlpha * 0.001;
  if ( igi2_frame.eRead.vX >= -3.1415927410125732 )
  {
    if ( igi2_frame.eRead.vX <= 3.1415927410125732 )
      goto LABEL_34;
    HIDWORD(igi2_frame.eRead.vX) = 1074340347;
  }
  else
  {
    HIDWORD(igi2_frame.eRead.vX) = -1073143301;
  }
  LODWORD(igi2_frame.eRead.vX) = 1610612736;
LABEL_34:
  igi2_frame.eRead.vY = 0.0;
  if ( igi2_frame.eRead.vZ >= -3.1415927410125732 )
  {
    if ( igi2_frame.eRead.vZ <= 3.1415927410125732 )
      goto LABEL_39;
    HIDWORD(igi2_frame.eRead.vZ) = 1074340347;
  }
  else
  {
    HIDWORD(igi2_frame.eRead.vZ) = -1073143301;
  }
  LODWORD(igi2_frame.eRead.vZ) = 1610612736;
LABEL_39:
  v13 = (double)igi2_frame.NetTime;
  v14 = igi2_frame.eRead.vX * v13 + igi2_frame.ptPos.vX;
  if ( v14 >= -1.4835299054781597 )
  {
    if ( v14 <= 1.4835299054781597 )
      igi2_frame.ptInPos_4.vX = v14;
    else
      igi2_frame.ptInPos_4.vX = 1.4835299054781597;
  }
  else
  {
    igi2_frame.ptInPos_4.vX = -1.4835299054781597;
  }
  igi2_frame.ptInPos_4.vY = 0.0;
  v15 = v13 * igi2_frame.eRead.vZ + igi2_frame.ptPos.vZ;
  igi2_frame.ptInPos_4.vZ = v15;
  if ( v15 - igi2_frame.v31 < -3.1415926535897944 )
  {
    do
      v15 = v15 + 6.283185307179589;
    while ( v15 - igi2_frame.v31 < -3.1415926535897944 );
    igi2_frame.ptInPos_4.vZ = v15;
  }
  if ( v15 - igi2_frame.v31 > 3.1415926535897944 )
  {
    do
      v15 = v15 - 6.283185307179589;
    while ( v15 - igi2_frame.v31 > 3.1415926535897944 );
    igi2_frame.ptInPos_4.vZ = v15;
  }
  if ( *(int *)(igi2_frame.v30.tPosition.nY + 96) <= 0 )
    Spline_Initialize(
      (struct Spline_s *)igi2_frame.v30.tPosition.nY,
      &igi2_frame.ptInPos_4,
      &igi2_frame.ptInPos_4,
      &igi2_frame.eRead,
      &igi2_frame.eRead,
      (int)igi2_frame.ptOldSpeed,
      (int)v10);
  else
    Spline_Extend((struct Spline_s *)igi2_frame.v30.tPosition.nY, igi2_frame.v29, &igi2_frame.ptInPos_4, &igi2_frame.eRead, (int)igi2_frame.ptOldSpeed, (int)v10);
  eAnimState = ptBody->eAnimState;
  if ( eAnimState == 0xFF )
    v17 = -1;
  else
    v17 = eAnimState;
  ptHumanRemote->eUpperBody = v17;
  LOBYTE(v18) = ptBody->eUpperBody;
  if ( (_BYTE)v18 == 0xFF )
    v18 = -1;
  else
    v18 = (unsigned __int8)v18;
  ptHumanRemote->eWeaponID = v18;
  BYTE1(ptHumanRemote->nRadioTimer) = v17 == 21 || v17 == 19 || v17 == 20;
  ptHumanRemote->nInitRadioTimer = nRemoteTime;
  LOBYTE(ptHumanRemote->nRadioTimer) = ptBody->isShowPlayer;
  return nRemoteTime;
}

void __cdecl sub_45AB90(struct QTask_s *a1, struct DrawComputerObjectContext_s *ptDrawComputerObjectContext)
{
  long double v2; // st7

  if ( Game_eGameMode == GAME_GAMEMODE_SINGLEPLAYER
    || a1[10].tQTaskRefList.ptTail == HumanPlayer_ptQTask[10].tQTaskRefList.ptTail
    && LOBYTE(a1[81].tQTaskRefList.ptTail) )
  {
    ptDrawComputerObjectContext->ptPos = (struct real64x3_t *)&a1[1];
    ptDrawComputerObjectContext->ptOrientation = (struct real32x9_t *)&a1[3].ptPrev;
    v2 = sqrt(
           *(float *)&a1[7].tQTaskChildren.ptTail * *(float *)&a1[7].tQTaskChildren.ptTail
         + *(float *)&a1[7].tQTaskRefList.ptHead * *(float *)&a1[7].tQTaskRefList.ptHead
         + *(float *)&a1[7].tQTaskRefList.ptMiddle * *(float *)&a1[7].tQTaskRefList.ptMiddle)
       + *(float *)&a1[8].ptNext;
    ptDrawComputerObjectContext->eComputerObjectMarker = COMPUTEROBJECTMARKER_DIAMOND;
    ptDrawComputerObjectContext->eComputerObjectMarkerColor = COMPUTEROBJECTMARKER_COLOR_GREEN;
    ptDrawComputerObjectContext->vRadius = v2;
    ComputerObject_DrawMarker(ptDrawComputerObjectContext);
  }
}

// source: j/0/human/network/humanremote.c:2065  [anchor-strings]
void __cdecl HumanRemote_Open()
{
  unsigned __int16 v0; // si
  __int16 v1; // ax
  __int16 v2; // ax

  v0 = QTask_NewQTaskType("HumanRemote", 3320, Human_eQTaskType, 0, 0);
  HumanRemote_eQTaskType = v0;
  QTask_SetQTaskTypeGroup(v0, 1u);
  QTask_LinkQTaskEventHandlerFn(v0, 0, HumanRemote_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, nullptr);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, sub_459250);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, RunDelayed_eQTaskEvent, HumanRemote_RunDelayedHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 5, HumanRemote_EnterHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, HumanRemote_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, HumanRemote_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(v0, DynCubeObj_eDynCubeObjRemoveQTaskEvent, HumanRemote_RemoveDynCubeObjHandler);
  v1 = Human_eHumanUpdateQTaskEvent;
  if ( Human_eHumanUpdateQTaskEvent == 512 )
  {
    v1 = QTask_NewQTaskEventFn(0, "HumanUpdate");
    v0 = HumanRemote_eQTaskType;
    Human_eHumanUpdateQTaskEvent = v1;
  }
  QTask_LinkQTaskEventHandlerFn(v0, v1, HumanRemote_HumanUpdateHandler);
  QTask_LinkQTaskEventHandlerFn(v0, GameFunctions_eWeaponHitQTaskEvent, HumanRemote_WeaponHitHandler);
  QTask_LinkQTaskEventHandlerFn(v0, GameFunctions_eExplosionHitQTaskEvent, HumanRemote_ExplosionHitHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    FlashBang_eFlashBangQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))HumanRemote_FlashBangHandler);
  v2 = ComputerObject_eDrawComputerObjectQTaskEvent;
  if ( ComputerObject_eDrawComputerObjectQTaskEvent == 512 )
  {
    v2 = QTask_NewQTaskEventFn(0x200u, "DrawComputerObject");
    v0 = HumanRemote_eQTaskType;
    ComputerObject_eDrawComputerObjectQTaskEvent = v2;
  }
  QTask_LinkQTaskEventHandlerFn(v0, v2, (void (__cdecl *)(struct QTask_s *, void *))sub_45AB90);
}

// source: j/0/human/network/humanremote.c:2103  [size]
void __cdecl HumanRemote_Close()
{
  QTask_DeleteQTaskType(HumanRemote_eQTaskType);
}

// source: j/0/human/network/humanremote.c:2117  [size]
unsigned __int16 __cdecl HumanRemote_GetQTaskType()
{
  return HumanRemote_eQTaskType;
}

// source: j/0/human/network/humanremote.c:2133  [anchor-callee]
struct QTask_s *__cdecl HumanRemote_New(
        struct QTask_s *ptParent,
        struct real64x3_t *ptPosition,
        float vGamma,
        char *zModel,
        int eTeam,
        int eNetworkID)
{
  #pragma pack(push, 1)
  union
  {
    struct { signed int nNow; };
    struct { char igi2_o1[4]; struct real64x3_t tZero; };
    struct { char igi2_o2[28]; struct real64x3_t ptOldPos; };
    struct { char igi2_o3[52]; struct real64x3_t ptPos; };
    char igi2_extent[80];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v6; // ebx
  struct QTask_s *v7; // ebp
  __int16 v8; // ax
  int ptNext; // eax
  struct QTask_s *ptPrev; // ecx
  int v11; // ecx
  struct Spline_s *p_ptMiddle; // eax
  int ptMiddle; // eax
  struct QReference_s *ptTail; // ecx
  signed int v15; // ecx
  struct Spline_s *p_tQTaskChildren; // eax

  if ( Timer_isPerformanceCounter )
  {
    v6 = Timer_GetPerformanceCounter() - Timer_nStartTime;
    igi2_frame.nNow = v6;
  }
  else
  {
    igi2_frame.nNow = GetTickCount() - Timer_nStartTime;
    v6 = igi2_frame.nNow;
  }
  v7 = QTask_NewFn(ptParent, HumanRemote_eQTaskType, &eNetworkID);
  qmemcpy(&v7[10], ptPosition, 0x18u);
  strcpy((char *)&v7[10].ptParent, zModel);
  v8 = ParameterList_eUpdateInternalDataQTaskEvent;
  *(float *)&v7[10].tQTaskRefList.ptMiddle = vGamma;
  v7[10].tQTaskRefList.ptTail = (struct QReference_s *)eTeam;
  QTask_TriggerQTaskEventRecursively(v7, v8, nullptr);
  v7[77].ptNext = (struct QTask_s *)-1;
  ptNext = (int)v7[77].ptNext;
  memset(&igi2_frame.tZero, 0, sizeof(igi2_frame.tZero));
  if ( ptNext <= 0 )
  {
    Spline_Initialize(
      (struct Spline_s *)&v7[74].tQTaskRefList.ptMiddle,
      ptPosition,
      ptPosition,
      &igi2_frame.tZero,
      &igi2_frame.tZero,
      v6,
      100);
  }
  else
  {
    ptPrev = v7[77].ptPrev;
    if ( v6 >= (int)ptPrev )
    {
      v11 = (int)ptPrev + ptNext;
      p_ptMiddle = (struct Spline_s *)&v7[74].tQTaskRefList.ptMiddle;
      if ( v6 <= v11 )
      {
        Spline_OnSpline(&igi2_frame.ptOldPos, &igi2_frame.ptPos, p_ptMiddle, v6);
        Spline_Initialize(
          (struct Spline_s *)&v7[74].tQTaskRefList.ptMiddle,
          &igi2_frame.ptOldPos,
          ptPosition,
          &igi2_frame.ptPos,
          &igi2_frame.tZero,
          v6,
          100);
      }
      else
      {
        Spline_ExtraFromEnd(&igi2_frame.ptOldPos, &igi2_frame.ptPos, p_ptMiddle, v6);
        Spline_Initialize(
          (struct Spline_s *)&v7[74].tQTaskRefList.ptMiddle,
          &igi2_frame.ptOldPos,
          ptPosition,
          &igi2_frame.ptPos,
          &igi2_frame.tZero,
          igi2_frame.nNow,
          100);
      }
    }
    else
    {
      Spline_ExtraFromStart(&igi2_frame.ptOldPos, &igi2_frame.ptPos, (struct Spline_s *)&v7[74].tQTaskRefList.ptMiddle, v6);
      Spline_Initialize(
        (struct Spline_s *)&v7[74].tQTaskRefList.ptMiddle,
        &igi2_frame.ptOldPos,
        ptPosition,
        &igi2_frame.ptPos,
        &igi2_frame.tZero,
        igi2_frame.nNow,
        100);
    }
  }
  v7[79].tQTaskRefList.ptMiddle = (struct QReference_s *)-1;
  ptMiddle = (int)v7[79].tQTaskRefList.ptMiddle;
  if ( ptMiddle <= 0 )
  {
    Spline_Initialize((struct Spline_s *)&v7[77].tQTaskChildren, &igi2_frame.tZero, &igi2_frame.tZero, &igi2_frame.tZero, &igi2_frame.tZero, igi2_frame.nNow, 100);
  }
  else
  {
    ptTail = v7[79].tQTaskRefList.ptTail;
    if ( igi2_frame.nNow >= (int)ptTail )
    {
      v15 = (signed int)ptTail + ptMiddle;
      p_tQTaskChildren = (struct Spline_s *)&v7[77].tQTaskChildren;
      if ( igi2_frame.nNow <= v15 )
        Spline_OnSpline(&igi2_frame.ptPos, &igi2_frame.ptOldPos, p_tQTaskChildren, igi2_frame.nNow);
      else
        Spline_ExtraFromEnd(&igi2_frame.ptPos, &igi2_frame.ptOldPos, p_tQTaskChildren, igi2_frame.nNow);
      Spline_Initialize((struct Spline_s *)&v7[77].tQTaskChildren, &igi2_frame.ptPos, &igi2_frame.tZero, &igi2_frame.ptOldPos, &igi2_frame.tZero, igi2_frame.nNow, 100);
    }
    else
    {
      Spline_ExtraFromStart(&igi2_frame.ptPos, &igi2_frame.ptOldPos, (struct Spline_s *)&v7[77].tQTaskChildren, igi2_frame.nNow);
      Spline_Initialize((struct Spline_s *)&v7[77].tQTaskChildren, &igi2_frame.ptPos, &igi2_frame.tZero, &igi2_frame.ptOldPos, &igi2_frame.tZero, igi2_frame.nNow, 100);
    }
  }
  return v7;
}
