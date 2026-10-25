/* j/0/humanai/humanai.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/humanai/humanai.c:543  [anchor-callee]
void __cdecl HumanAI_SetCurrentNode(struct HumanAI_s *ptHumanAI, int nNewNodeID)
{
  struct Graph_s *v2; // esi
  int vY_high; // edi
  struct Graph_s *v4; // esi

  v2 = *(struct Graph_s **)&ptHumanAI->zScriptFile[36];
  if ( v2 )
  {
    vY_high = HIDWORD(ptHumanAI->tCommon.tAimPosition.vY);
    if ( nNewNodeID != vY_high )
    {
      Graph_AddWeightToNode(v2, vY_high, -20480.0);
      v4 = *(struct Graph_s **)&ptHumanAI->zScriptFile[36];
      HIDWORD(ptHumanAI->tCommon.tAimPosition.vY) = nNewNodeID;
      Graph_AddWeightToNode(v4, nNewNodeID, 20480.0);
    }
  }
}

// source: j/0/humanai/humanai.c:563  [anchor-callee]
void __cdecl HumanAI_AddSoundQueueItem(struct HumanAI_s *ptHumanAI, char *zSoundItem)
{
  int v2; // eax

  v2 = *(_DWORD *)&ptHumanAI->zAIType[32];
  if ( v2 < 5 )
  {
    *(_DWORD *)&ptHumanAI->zAIType[32] = v2 + 1;
    strcpy(&ptHumanAI->azSoundQueue[v2 + 1][8], zSoundItem);
  }
}

// source: j/0/humanai/humanai.c:580  [anchor-hash]
void __cdecl HumanAI_MaintainSoundQueue(struct HumanAI_s *ptHumanAI)
{
  int v1; // eax
  int v2; // ebx
  bool v3; // zf
  char *v4; // edi
  char *v5; // eax
  char v6; // cl

  if ( *(_DWORD *)&ptHumanAI->zAIType[32] )
  {
    if ( !LODWORD(ptHumanAI->avChannel[2]) )
    {
      HumanAI_PlaySoundAtPosition(&ptHumanAI->tQTask, &ptHumanAI->azSoundQueue[1][8], false);
      v1 = *(_DWORD *)&ptHumanAI->zAIType[32] - 1;
      v2 = 0;
      v3 = *(_DWORD *)&ptHumanAI->zAIType[32] == 1;
      *(_DWORD *)&ptHumanAI->zAIType[32] = v1;
      if ( v1 >= 0 && !v3 )
      {
        v4 = &ptHumanAI->azSoundQueue[2][8];
        do
        {
          v5 = v4;
          do
          {
            v6 = *v5;
            *(v5 - 32) = *v5;
            ++v5;
          }
          while ( v6 );
          ++v2;
          v4 += 32;
        }
        while ( v2 < (int)(*(_DWORD *)&ptHumanAI->zAIType[32]) );
      }
    }
  }
}

// source: j/0/humanai/humanai.c:605  [anchor-callee]
void __cdecl HumanAI_FindCurrentSectorFromNodes(struct HumanAI_s *ptHumanAI)
{
  int v1; // esi
  int v2; // eax
  int nNodeId1; // ebx
  int GraphNodeDataSize; // eax
  int v5; // ebp
  int v6; // esi
  int nNodeId2; // ebx
  int v8; // eax
  int v9; // eax
  int v10; // ecx
  int vY_high; // ebx
  int v12; // eax
  int v13; // eax

  v1 = *(_DWORD *)&ptHumanAI->zScriptFile[36];
  v2 = *(_DWORD *)(v1 + 132);
  if ( ptHumanAI->tLegalNodesData.isUseLegalNodes )
  {
    nNodeId1 = ptHumanAI->tLegalNodesData.nNodeId1;
    if ( v2 && nNodeId1 < (int)(*(_DWORD *)(v1 + 104)) && nNodeId1 >= 0 )
    {
      GraphNodeDataSize = Graph_GetGraphNodeDataSize(v1);
      v5 = *(_DWORD *)(*(_DWORD *)(v1 + 132) + nNodeId1 * GraphNodeDataSize) == -1
         ? 0
         : nNodeId1 * GraphNodeDataSize + *(_DWORD *)(v1 + 132);
    }
    else
    {
      v5 = 0;
    }
    v6 = *(_DWORD *)&ptHumanAI->zScriptFile[36];
    nNodeId2 = ptHumanAI->tLegalNodesData.nNodeId2;
    if ( *(_DWORD *)(v6 + 132) && nNodeId2 < (int)(*(_DWORD *)(v6 + 104)) && nNodeId2 >= 0 )
    {
      v8 = Graph_GetGraphNodeDataSize(*(_DWORD *)&ptHumanAI->zScriptFile[36]);
      v9 = *(_DWORD *)(*(_DWORD *)(v6 + 132) + nNodeId2 * v8) == -1 ? 0 : nNodeId2 * v8 + *(_DWORD *)(v6 + 132);
    }
    else
    {
      v9 = 0;
    }
    v10 = *(_DWORD *)(v5 + 580);
    if ( v10 != *(_DWORD *)(v9 + 580) )
    {
      *(&ptHumanAI->atAnimationEntries[1].nAnimation + 1) = 0;
      LODWORD(ptHumanAI->atAnimationEntries[1].vProbability) = 1;
      return;
    }
  }
  else
  {
    vY_high = HIDWORD(ptHumanAI->tCommon.tAimPosition.vY);
    if ( v2 && vY_high < (int)(*(_DWORD *)(v1 + 104)) && vY_high >= 0 )
    {
      v12 = Graph_GetGraphNodeDataSize(*(_DWORD *)&ptHumanAI->zScriptFile[36]);
      v13 = *(_DWORD *)(*(_DWORD *)(v1 + 132) + vY_high * v12) == -1 ? 0 : vY_high * v12 + *(_DWORD *)(v1 + 132);
    }
    else
    {
      v13 = 0;
    }
    v10 = *(_DWORD *)(v13 + 580);
  }
  *(&ptHumanAI->atAnimationEntries[1].nAnimation + 1) = v10;
  LODWORD(ptHumanAI->atAnimationEntries[1].vProbability) = 0;
}

// source: j/0/humanai/humanai.c:651  [size]
void __cdecl HumanAI_RegisterScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( !BYTE1(ptQTask[111].tQTaskChildren.ptHead) )
  {
    BYTE1(ptQTask[111].tQTaskChildren.ptHead) = 1;
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.isDetection", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      (char *)&ptQTask[111].tQTaskChildren.ptHead + 2,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
  }
}

// source: j/0/humanai/humanai.c:681  [size]
void __cdecl HumanAI_RemoveScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( BYTE1(ptQTask[111].tQTaskChildren.ptHead) )
  {
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    BYTE1(ptQTask[111].tQTaskChildren.ptHead) = 0;
    sprintf(igi2_frame.zTemp, "%s.isDetection", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
  }
}

// source: j/0/humanai/humanai.c:712  [anchor-hash]
struct HumanAI_s *__cdecl HumanAI_UpdateAlertedStatus(struct HumanAI_s *ptHumanAI)
{
  struct QTask_s *ptParent; // edx
  unsigned int v2; // ecx

  ptParent = ptHumanAI->tQTask.ptParent->ptParent;
  v2 = ptHumanAI->anEventPriorityList[5] & 0xFFFFFFFB;
  ptHumanAI->anEventPriorityList[5] = v2;
  if ( (int)ptParent[216].tQTaskChildren.ptHead > 0 )
    ptHumanAI->anEventPriorityList[5] = v2 | 4;
  return ptHumanAI;
}

// source: j/0/humanai/humanai.c:740  [anchor-callee]
char __cdecl HumanAI_IsPositionInsideView(
        struct HumanAIView_s *ptView,
        struct real64x3_t *ptPosition,
        enum bool isIgnoreDistance)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real64x3_t v11; };
    struct { char igi2_o1[36]; float vAlphaDelta; };
    struct { char igi2_o2[40]; double vViewLength; };
    struct { char igi2_o3[48]; double vLength; };
    struct { char igi2_o4[56]; struct real64x3_t Real64x3_RotateInverse_tTemp; };
    char igi2_extent[84];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v3; // st7
  double v4; // st6
  double v5; // st5
  double v6; // st4
  int vViewConeLength_low; // eax
  double v9; // st7
  double v10; // st7

  v3 = ptPosition->vX - ptView->tViewPosition.vX;
  v4 = ptPosition->vY - ptView->tViewPosition.vY;
  v5 = ptPosition->vZ - ptView->tViewPosition.vZ;
  igi2_frame.Real64x3_RotateInverse_tTemp.vX = ptView->tViewOrientation.tZ.vX * v5
                                  + ptView->tViewOrientation.tY.vX * v4
                                  + ptView->tViewOrientation.tX.vX * v3;
  igi2_frame.Real64x3_RotateInverse_tTemp.vY = ptView->tViewOrientation.tZ.vY * v5
                                  + ptView->tViewOrientation.tY.vY * v4
                                  + ptView->tViewOrientation.tX.vY * v3;
  v6 = ptView->tViewOrientation.tZ.vZ * v5 + ptView->tViewOrientation.tY.vZ * v4 + ptView->tViewOrientation.tX.vZ * v3;
  igi2_frame.Real64x3_RotateInverse_tTemp.vZ = v6;
  if ( igi2_frame.Real64x3_RotateInverse_tTemp.vY < 0.0 )
    return 0;
  vViewConeLength_low = LODWORD(ptView->vViewConeLength);
  HIDWORD(igi2_frame.vViewLength) = HIDWORD(ptView->vViewConeLength);
  LODWORD(igi2_frame.vViewLength) = vViewConeLength_low;
  qmemcpy(&igi2_frame.v11, &igi2_frame.Real64x3_RotateInverse_tTemp, sizeof(igi2_frame.v11));
  igi2_frame.vLength = sqrt(
              igi2_frame.Real64x3_RotateInverse_tTemp.vY * igi2_frame.Real64x3_RotateInverse_tTemp.vY
            + v6 * v6
            + igi2_frame.Real64x3_RotateInverse_tTemp.vX * igi2_frame.Real64x3_RotateInverse_tTemp.vX);
  v9 = GameFunctions_CalcAlpha(igi2_frame.v11);
  if ( v9 < 0.0 )
    v9 = -v9;
  igi2_frame.vAlphaDelta = v9;
  qmemcpy(&igi2_frame.v11, &igi2_frame.Real64x3_RotateInverse_tTemp, sizeof(igi2_frame.v11));
  v10 = GameFunctions_CalcGamma(igi2_frame.v11);
  if ( v10 < 0.0 )
    v10 = -v10;
  if ( isIgnoreDistance == false && igi2_frame.vLength > igi2_frame.vViewLength )
    goto LABEL_13;
  if ( igi2_frame.vAlphaDelta < ptView->vViewConeAlpha && v10 < ptView->vViewConeGamma )
    return 1;
  if ( isIgnoreDistance == false )
  {
LABEL_13:
    if ( ptView->vSecondaryViewConeLength < igi2_frame.vLength )
      return 0;
  }
  return igi2_frame.vAlphaDelta < ptView->vSecondaryViewConeAlpha && v10 < ptView->vSecondaryViewConeGamma;
}

// source: j/0/humanai/humanai.c:803  [anchor-callee]
float __cdecl HumanAI_GetLevelSightDelta(struct HumanAIView_s *ptView)
{
  #pragma pack(push, 1)
  union
  {
    struct { float x; };
    struct { char igi2_o1[12]; struct real64x3_t Real64x3_RotateInverse_tTemp; };
    struct { char igi2_o2[36]; struct real64x3_t tAimView; };
    char igi2_extent[64];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v1; // st7
  double v2; // st6
  double v3; // st5
  double v4; // st4
  long double v5; // st5
  double v6; // st7

  v1 = (ptView->tOrientation.tX.vZ + ptView->tOrientation.tX.vX) * 0.0 + ptView->tOrientation.tX.vY;
  v2 = (ptView->tOrientation.tY.vZ + ptView->tOrientation.tY.vX) * 0.0 + ptView->tOrientation.tY.vY;
  v3 = (ptView->tOrientation.tZ.vZ + ptView->tOrientation.tZ.vX) * 0.0 + ptView->tOrientation.tZ.vY;
  igi2_frame.Real64x3_RotateInverse_tTemp.vX = ptView->tViewOrientation.tZ.vX * v3
                                  + ptView->tViewOrientation.tY.vX * v2
                                  + ptView->tViewOrientation.tX.vX * v1;
  igi2_frame.Real64x3_RotateInverse_tTemp.vY = ptView->tViewOrientation.tZ.vY * v3
                                  + ptView->tViewOrientation.tY.vY * v2
                                  + ptView->tViewOrientation.tX.vY * v1;
  v4 = ptView->tViewOrientation.tZ.vZ * v3 + ptView->tViewOrientation.tY.vZ * v2 + ptView->tViewOrientation.tX.vZ * v1;
  igi2_frame.Real64x3_RotateInverse_tTemp.vZ = v4;
  qmemcpy(&igi2_frame.tAimView, &igi2_frame.Real64x3_RotateInverse_tTemp, sizeof(igi2_frame.tAimView));
  if ( igi2_frame.Real64x3_RotateInverse_tTemp.vY != 0.0 || v4 != 0.0 )
  {
    v5 = 1.0 / sqrt(igi2_frame.Real64x3_RotateInverse_tTemp.vY * igi2_frame.Real64x3_RotateInverse_tTemp.vY + v4 * v4);
    igi2_frame.tAimView.vY = igi2_frame.Real64x3_RotateInverse_tTemp.vY * v5;
    igi2_frame.tAimView.vZ = v5 * igi2_frame.tAimView.vZ;
  }
  igi2_frame.x = igi2_frame.tAimView.vY;
  v6 = Real32_Acos(igi2_frame.x);
  if ( igi2_frame.tAimView.vZ < 0.0 )
    return -v6;
  return v6;
}

// source: j/0/humanai/humanai.c:843  [anchor-callee]
void __cdecl HumanAI_FindWeapons(struct HumanAI_s *ptHumanAI)
{
  struct QTask_s *ptHead; // esi
  unsigned __int16 v2; // bx
  struct WeaponTypeItem_s *WeaponTypeItemFromWeaponType; // eax
  struct WeaponType_s *ptWeaponType; // eax

  ptHead = ptHumanAI->tQTask.ptParent->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v2 = Weapon_eQTaskType;
    while ( 1 )
    {
      if ( QTask_IsQTaskTypeDerived(ptHead->eQTaskType, v2) )
      {
        WeaponTypeItemFromWeaponType = Weapon_GetWeaponTypeItemFromWeaponType(ptHead, "WEAPON_ID_GRENADE");
        if ( WeaponTypeItemFromWeaponType )
        {
          if ( WeaponTypeItemFromWeaponType->isActive )
            break;
        }
      }
      ptHead = ptHead->ptNext;
      if ( !ptHead || !ptHead->ptNext )
        return;
    }
    ptWeaponType = Weapon_GetWeaponTypeItemFromWeaponType(ptHead, "WEAPON_ID_GRENADE")->ptWeaponType;
    LOBYTE(ptHumanAI->tCommon.nPrevNode) = 1;
    ptHumanAI->tCommon.nCurrentStartNode = ptWeaponType->eID;
  }
}

// source: j/0/humanai/humanai.c:884  [anchor-hash]
struct HumanAIEvent_t *__cdecl HumanAI_GetEvent()
{
  return HumanAI_ptCurrentEventStack->ptHead->ptNext != nullptr
       ? (struct HumanAIEvent_t *)HumanAI_ptCurrentEventStack->ptHead
       : nullptr;
}

// source: j/0/humanai/humanai.c:898  [anchor-mhash]
void __cdecl HumanAI_GetEventPosition(struct real64x3_t *ptPosition)
{
  qmemcpy(
    ptPosition,
    HumanAI_ptCurrentEventStack->ptHead->ptNext != nullptr ? &HumanAI_ptCurrentEventStack->ptHead[2] : (void *)16,
    sizeof(struct real64x3_t));
}

// source: j/0/humanai/humanai.c:920  [anchor-mhash]
struct Result_s *__cdecl HumanAI_SetMinRangeAccuracyCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  double v4; // st7
  struct HumanAI_s *v5; // esi
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      *(float *)&ptArgList = 0.0;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 2);
      v4 = *(float *)&ptArgList;
    }
    else
    {
      v4 = Expression_EvalFloat(*ptArgList->aptExpression);
    }
    *(float *)&ptArgList = v4 * 0.009999999776482582;
    if ( *(float *)&ptArgList >= 0.009999999776482582 )
    {
      if ( *(float *)&ptArgList > 1.0 )
        *(float *)&ptArgList = 1.0;
    }
    else
    {
      *(float *)&ptArgList = 0.009999999776482582;
    }
    v5 = HumanAI_ptCurrentHumanAI;
    HumanAI_ptCurrentHumanAI->tTweakParameters.vGrenadeThrowProb = *(float *)&ptArgList;
    v5->tTweakParameters.vHitRecoilThreshold = pow(
                                                 v5->tTweakParameters.vGrenadeDetonationTimer / *(float *)&ptArgList,
                                                 1.0 / v5->tTweakParameters.vCloseCombatDamage);
  }
  Rs.zResult = (char *)&g_zInitialValue;
  Rs.vResult = 1.0;
  Rs.nResult = 1;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:953  [anchor-mhash]
struct Result_s *__cdecl HumanAI_SetMedRangeAccuracyCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  double v4; // st7
  struct HumanAI_s *v5; // esi
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      *(float *)&ptArgList = 0.0;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 2);
      v4 = *(float *)&ptArgList;
    }
    else
    {
      v4 = Expression_EvalFloat(*ptArgList->aptExpression);
    }
    *(float *)&ptArgList = v4 * 0.009999999776482582;
    if ( *(float *)&ptArgList >= 0.009999999776482582 )
    {
      if ( *(float *)&ptArgList > 1.0 )
        *(float *)&ptArgList = 1.0;
    }
    else
    {
      *(float *)&ptArgList = 0.009999999776482582;
    }
    v5 = HumanAI_ptCurrentHumanAI;
    HumanAI_ptCurrentHumanAI->tTweakParameters.vGrenadeDetonationTimer = *(float *)&ptArgList;
    v5->tTweakParameters.vHitRecoilThreshold = pow(
                                                 *(float *)&ptArgList / v5->tTweakParameters.vGrenadeThrowProb,
                                                 1.0 / v5->tTweakParameters.vCloseCombatDamage);
    v5->tTweakParameters.vCombatViewCone1Alpha = pow(
                                                   v5->tTweakParameters.vGrenadeLandingReactionProb
                                                 / v5->tTweakParameters.vGrenadeDetonationTimer,
                                                   1.0
                                                 / (v5->tTweakParameters.vHitPoints
                                                  - v5->tTweakParameters.vCloseCombatDamage));
  }
  Rs.zResult = (char *)&g_zInitialValue;
  Rs.vResult = 1.0;
  Rs.nResult = 1;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:991  [anchor-mhash]
struct Result_s *__cdecl HumanAI_SetMaxRangeAccuracyCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  double v4; // st7
  struct HumanAI_s *v5; // esi
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      *(float *)&ptArgList = 0.0;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 2);
      v4 = *(float *)&ptArgList;
    }
    else
    {
      v4 = Expression_EvalFloat(*ptArgList->aptExpression);
    }
    *(float *)&ptArgList = v4 * 0.009999999776482582;
    if ( *(float *)&ptArgList >= 0.0 )
    {
      if ( *(float *)&ptArgList > 1.0 )
        *(float *)&ptArgList = 1.0;
    }
    else
    {
      *(float *)&ptArgList = 0.0;
    }
    v5 = HumanAI_ptCurrentHumanAI;
    HumanAI_ptCurrentHumanAI->tTweakParameters.vGrenadeLandingReactionProb = *(float *)&ptArgList;
    v5->tTweakParameters.vCombatViewCone1Alpha = pow(
                                                   *(float *)&ptArgList / v5->tTweakParameters.vGrenadeDetonationTimer,
                                                   1.0
                                                 / (v5->tTweakParameters.vHitPoints
                                                  - v5->tTweakParameters.vCloseCombatDamage));
  }
  Rs.zResult = (char *)&g_zInitialValue;
  Rs.vResult = 1.0;
  Rs.nResult = 1;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:1023  [anchor-mhash]
struct Result_s *__cdecl HumanAI_SetAccuracyMedRangeCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  double v4; // st7
  double v5; // st7
  struct HumanAI_s *v6; // esi
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      *(float *)&ptArgList = 0.0;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 2);
      v4 = *(float *)&ptArgList;
    }
    else
    {
      v4 = Expression_EvalFloat(*ptArgList->aptExpression);
    }
    v5 = v4 * 4096.0;
    if ( v5 <= 1.0 )
      v5 = 1.0;
    v6 = HumanAI_ptCurrentHumanAI;
    HumanAI_ptCurrentHumanAI->tTweakParameters.vHitPoints = v5;
    v6->tTweakParameters.vHitRecoilThreshold = pow(
                                                 v6->tTweakParameters.vGrenadeDetonationTimer
                                               / v6->tTweakParameters.vGrenadeThrowProb,
                                                 1.0 / v6->tTweakParameters.vCloseCombatDamage);
    v6->tTweakParameters.vCombatViewCone1Alpha = pow(
                                                   v6->tTweakParameters.vGrenadeLandingReactionProb
                                                 / v6->tTweakParameters.vGrenadeDetonationTimer,
                                                   1.0
                                                 / (v6->tTweakParameters.vHitPoints
                                                  - v6->tTweakParameters.vCloseCombatDamage));
  }
  Rs.zResult = (char *)&g_zInitialValue;
  Rs.vResult = 1.0;
  Rs.nResult = 1;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:1060  [anchor-mhash]
struct Result_s *__cdecl HumanAI_SetAccuracyMaxRangeCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  double v4; // st7
  double v5; // st7
  struct HumanAI_s *v6; // esi
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      *(float *)&ptArgList = 0.0;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 2);
      v4 = *(float *)&ptArgList;
    }
    else
    {
      v4 = Expression_EvalFloat(*ptArgList->aptExpression);
    }
    v5 = v4 * 4096.0;
    *(float *)&ptArgList = v5;
    if ( v5 <= 1.0 )
      *(float *)&ptArgList = 1.0;
    v6 = HumanAI_ptCurrentHumanAI;
    HumanAI_ptCurrentHumanAI->tTweakParameters.vHitPoints = *(float *)&ptArgList;
    v6->tTweakParameters.vCombatViewCone1Alpha = pow(
                                                   v6->tTweakParameters.vGrenadeLandingReactionProb
                                                 / v6->tTweakParameters.vGrenadeDetonationTimer,
                                                   1.0
                                                 / (*(float *)&ptArgList - v6->tTweakParameters.vCloseCombatDamage));
  }
  Rs.zResult = (char *)&g_zInitialValue;
  Rs.vResult = 1.0;
  Rs.nResult = 1;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:1093  [size]
struct Result_s *__cdecl HumanAI_SetPercentageFiredPerBurstCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  double v4; // st7
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      *(float *)&ptArgList = 0.0;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 2);
      v4 = *(float *)&ptArgList;
    }
    else
    {
      v4 = Expression_EvalFloat(*ptArgList->aptExpression);
    }
    HumanAI_ptCurrentHumanAI->tTweakParameters.vTrackingTimeout = v4 * 0.009999999776482582;
  }
  Rs.nResult = 1;
  Rs.zResult = (char *)&g_zInitialValue;
  Rs.vResult = 1.0;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:1116  [size]
struct Result_s *__cdecl HumanAI_SetEvasiveActionProbCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  double v4; // st7
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      *(float *)&ptArgList = 0.0;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 2);
      v4 = *(float *)&ptArgList;
    }
    else
    {
      v4 = Expression_EvalFloat(*ptArgList->aptExpression);
    }
    HumanAI_ptCurrentHumanAI->tTweakParameters.vTrackingMaxDistance = v4 * 0.009999999776482582;
  }
  Rs.nResult = 1;
  Rs.zResult = (char *)&g_zInitialValue;
  Rs.vResult = 1.0;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:1139  [size]
struct Result_s *__cdecl HumanAI_SetMinDelayBetweenFiringCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  double v4; // st7
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      *(float *)&ptArgList = 0.0;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 2);
      v4 = *(float *)&ptArgList;
    }
    else
    {
      v4 = Expression_EvalFloat(*ptArgList->aptExpression);
    }
    HumanAI_ptCurrentHumanAI->tTweakParameters.vCombatViewCone1Length = v4 * 30.0;
  }
  Rs.nResult = 1;
  Rs.zResult = (char *)&g_zInitialValue;
  Rs.vResult = 1.0;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:1161  [size]
struct Result_s *__cdecl HumanAI_SetTrackingTimeoutCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  double v4; // st7
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      *(float *)&ptArgList = 0.0;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 2);
      v4 = *(float *)&ptArgList;
    }
    else
    {
      v4 = Expression_EvalFloat(*ptArgList->aptExpression);
    }
    HumanAI_ptCurrentHumanAI->tTweakParameters.vCombatViewCone2Alpha = v4 * 30.0;
  }
  Rs.nResult = 1;
  Rs.zResult = (char *)&g_zInitialValue;
  Rs.vResult = 1.0;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:1184  [size]
struct Result_s *__cdecl HumanAI_SetTrackingMaxDistanceCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  double v4; // st7
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      *(float *)&ptArgList = 0.0;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 2);
      v4 = *(float *)&ptArgList;
    }
    else
    {
      v4 = Expression_EvalFloat(*ptArgList->aptExpression);
    }
    HumanAI_ptCurrentHumanAI->tTweakParameters.vCombatViewCone2Length = v4 * 4096.0;
  }
  Rs.nResult = 1;
  Rs.zResult = (char *)&g_zInitialValue;
  Rs.vResult = 1.0;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:1207  [size]
struct Result_s *__cdecl HumanAI_SetGrenadeThrowProbCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  double v4; // st7
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      *(float *)&ptArgList = 0.0;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 2);
      v4 = *(float *)&ptArgList;
    }
    else
    {
      v4 = Expression_EvalFloat(*ptArgList->aptExpression);
    }
    HumanAI_ptCurrentHumanAI->tTweakParameters.vIdleViewCone1Alpha = v4 * 0.009999999776482582;
  }
  Rs.nResult = 1;
  Rs.zResult = (char *)&g_zInitialValue;
  Rs.vResult = 1.0;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:1230  [size]
struct Result_s *__cdecl HumanAI_SetGrenadeDetonationTimerCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  double v4; // st7
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      *(float *)&ptArgList = 0.0;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 2);
      v4 = *(float *)&ptArgList;
    }
    else
    {
      v4 = Expression_EvalFloat(*ptArgList->aptExpression);
    }
    HumanAI_ptCurrentHumanAI->tTweakParameters.vIdleViewCone1Length = v4 * 30.0;
  }
  Rs.nResult = 1;
  Rs.zResult = (char *)&g_zInitialValue;
  Rs.vResult = 1.0;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:1253  [size]
struct Result_s *__cdecl HumanAI_SetGrenadeLandingReactionProbCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  double v4; // st7
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      *(float *)&ptArgList = 0.0;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 2);
      v4 = *(float *)&ptArgList;
    }
    else
    {
      v4 = Expression_EvalFloat(*ptArgList->aptExpression);
    }
    HumanAI_ptCurrentHumanAI->tTweakParameters.vIdleViewCone2Alpha = v4 * 0.009999999776482582;
  }
  Rs.nResult = 1;
  Rs.zResult = (char *)&g_zInitialValue;
  Rs.vResult = 1.0;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:1276  [size]
struct Result_s *__cdecl HumanAI_SetCloseCombatDamageCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  double v4; // st7
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      *(float *)&ptArgList = 0.0;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 2);
      v4 = *(float *)&ptArgList;
    }
    else
    {
      v4 = Expression_EvalFloat(*ptArgList->aptExpression);
    }
    HumanAI_ptCurrentHumanAI->tTweakParameters.vIdleViewCone2Length = v4;
  }
  Rs.nResult = 1;
  Rs.zResult = (char *)&g_zInitialValue;
  Rs.vResult = 1.0;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:1299  [anchor-mhash]
struct Result_s *__cdecl HumanAI_SetHitPointsCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  double v4; // st7
  struct HumanAI_s *v5; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      *(float *)&ptArgList = 0.0;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 2);
      v4 = *(float *)&ptArgList;
    }
    else
    {
      v4 = Expression_EvalFloat(*ptArgList->aptExpression);
    }
    v5 = HumanAI_ptCurrentHumanAI;
    HumanAI_ptCurrentHumanAI->tTweakParameters.vIdleAnimationFrequency = v4;
    v5->tQTask.ptParent[25].tQTaskRefList.ptMiddle = (struct QReference_s *)LODWORD(v5->tTweakParameters.vIdleAnimationFrequency);
  }
  Rs.nResult = 1;
  Rs.zResult = (char *)&g_zInitialValue;
  Rs.vResult = 1.0;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:1329  [size]
struct Result_s *__cdecl HumanAI_SetHitRecoilThresholdCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  double v4; // st7
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      *(float *)&ptArgList = 0.0;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 2);
      v4 = *(float *)&ptArgList;
    }
    else
    {
      v4 = Expression_EvalFloat(*ptArgList->aptExpression);
    }
    HumanAI_ptCurrentHumanAI->tTweakParameters.vInvestigateViewCone1Alpha = v4;
  }
  Rs.nResult = 1;
  Rs.zResult = (char *)&g_zInitialValue;
  Rs.vResult = 1.0;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:1352  [size]
struct Result_s *__cdecl HumanAI_SetCombatViewCone1AlphaCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  double v4; // st7
  double v5; // st7
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      *(float *)&ptArgList = 0.0;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 2);
      v4 = *(float *)&ptArgList;
    }
    else
    {
      v4 = Expression_EvalFloat(*ptArgList->aptExpression);
    }
    v5 = v4 * 0.017453293005625408;
    if ( v5 >= 0.0 )
    {
      if ( v5 > 1.5707963705062866 )
        v5 = 1.5707963705062866;
    }
    else
    {
      v5 = 0.0;
    }
    HumanAI_ptCurrentHumanAI->tTweakParameters.vInvestigateViewCone1Length = v5;
  }
  Rs.nResult = 1;
  Rs.zResult = (char *)&g_zInitialValue;
  Rs.vResult = 1.0;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:1380  [size]
struct Result_s *__cdecl HumanAI_SetCombatViewCone1LengthCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  double v4; // st7
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      *(float *)&ptArgList = 0.0;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 2);
      v4 = *(float *)&ptArgList;
    }
    else
    {
      v4 = Expression_EvalFloat(*ptArgList->aptExpression);
    }
    HumanAI_ptCurrentHumanAI->tTweakParameters.vInvestigateViewCone2Alpha = v4 * 4096.0;
  }
  Rs.nResult = 1;
  Rs.zResult = (char *)&g_zInitialValue;
  Rs.vResult = 1.0;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:1403  [size]
struct Result_s *__cdecl HumanAI_SetCombatViewCone2AlphaCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  double v4; // st7
  double v5; // st7
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      *(float *)&ptArgList = 0.0;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 2);
      v4 = *(float *)&ptArgList;
    }
    else
    {
      v4 = Expression_EvalFloat(*ptArgList->aptExpression);
    }
    v5 = v4 * 0.017453293005625408;
    if ( v5 >= 0.0 )
    {
      if ( v5 > 1.5707963705062866 )
        v5 = 1.5707963705062866;
    }
    else
    {
      v5 = 0.0;
    }
    HumanAI_ptCurrentHumanAI->tTweakParameters.vInvestigateViewCone2Length = v5;
  }
  Rs.nResult = 1;
  Rs.zResult = (char *)&g_zInitialValue;
  Rs.vResult = 1.0;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:1430  [size]
struct Result_s *__cdecl HumanAI_SetCombatViewCone2LengthCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  double v4; // st7
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      *(float *)&ptArgList = 0.0;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 2);
      v4 = *(float *)&ptArgList;
    }
    else
    {
      v4 = Expression_EvalFloat(*ptArgList->aptExpression);
    }
    HumanAI_ptCurrentHumanAI->tTweakParameters.vInvestigateShoutFrequency = v4 * 4096.0;
  }
  Rs.nResult = 1;
  Rs.zResult = (char *)&g_zInitialValue;
  Rs.vResult = 1.0;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:1452  [size]
struct Result_s *__cdecl HumanAI_SetIdleViewCone1AlphaCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  double v4; // st7
  double v5; // st7
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      *(float *)&ptArgList = 0.0;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 2);
      v4 = *(float *)&ptArgList;
    }
    else
    {
      v4 = Expression_EvalFloat(*ptArgList->aptExpression);
    }
    v5 = v4 * 0.017453293005625408;
    if ( v5 >= 0.0 )
    {
      if ( v5 > 1.5707963705062866 )
        v5 = 1.5707963705062866;
    }
    else
    {
      v5 = 0.0;
    }
    HumanAI_ptCurrentHumanAI->tTweakParameters.vAnimSpeedFactor = v5;
  }
  Rs.nResult = 1;
  Rs.zResult = (char *)&g_zInitialValue;
  Rs.vResult = 1.0;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:1478  [size]
struct Result_s *__cdecl HumanAI_SetIdleViewCone1LengthCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  double v4; // st7
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      *(float *)&ptArgList = 0.0;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 2);
      v4 = *(float *)&ptArgList;
    }
    else
    {
      v4 = Expression_EvalFloat(*ptArgList->aptExpression);
    }
    HumanAI_ptCurrentHumanAI->tTweakParameters.vDetectionToAttackTime = v4 * 4096.0;
  }
  Rs.nResult = 1;
  Rs.zResult = (char *)&g_zInitialValue;
  Rs.vResult = 1.0;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:1500  [size]
struct Result_s *__cdecl HumanAI_SetIdleViewCone2AlphaCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  double v4; // st7
  double v5; // st7
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      *(float *)&ptArgList = 0.0;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 2);
      v4 = *(float *)&ptArgList;
    }
    else
    {
      v4 = Expression_EvalFloat(*ptArgList->aptExpression);
    }
    v5 = v4 * 0.017453293005625408;
    if ( v5 >= 0.0 )
    {
      if ( v5 > 1.5707963705062866 )
        v5 = 1.5707963705062866;
    }
    else
    {
      v5 = 0.0;
    }
    HumanAI_ptCurrentHumanAI->tTweakParameters.avDamageMultiplier[0] = v5;
  }
  Rs.nResult = 1;
  Rs.zResult = (char *)&g_zInitialValue;
  Rs.vResult = 1.0;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:1526  [size]
struct Result_s *__cdecl HumanAI_SetIdleViewCone2LengthCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  double v4; // st7
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      *(float *)&ptArgList = 0.0;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 2);
      v4 = *(float *)&ptArgList;
    }
    else
    {
      v4 = Expression_EvalFloat(*ptArgList->aptExpression);
    }
    HumanAI_ptCurrentHumanAI->tTweakParameters.avDamageMultiplier[1] = v4 * 4096.0;
  }
  Rs.nResult = 1;
  Rs.zResult = (char *)&g_zInitialValue;
  Rs.vResult = 1.0;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:1548  [size]
struct Result_s *__cdecl HumanAI_SetIdleAnimationFrequencyCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  double v4; // st7
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      *(float *)&ptArgList = 0.0;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 2);
      v4 = *(float *)&ptArgList;
    }
    else
    {
      v4 = Expression_EvalFloat(*ptArgList->aptExpression);
    }
    HumanAI_ptCurrentHumanAI->tTweakParameters.avDamageMultiplier[2] = v4 * 30.0;
  }
  Rs.nResult = 1;
  Rs.zResult = (char *)&g_zInitialValue;
  Rs.vResult = 1.0;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:1570  [size]
struct Result_s *__cdecl HumanAI_SetInvestigateViewCone1AlphaCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  double v4; // st7
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      *(float *)&ptArgList = 0.0;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 2);
      v4 = *(float *)&ptArgList;
    }
    else
    {
      v4 = Expression_EvalFloat(*ptArgList->aptExpression);
    }
    HumanAI_ptCurrentHumanAI->tTweakParameters.avDamageMultiplier[3] = v4 * 0.01745329238474369;
  }
  Rs.nResult = 1;
  Rs.zResult = (char *)&g_zInitialValue;
  Rs.vResult = 1.0;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:1592  [size]
struct Result_s *__cdecl HumanAI_SetInvestigateViewCone1LengthCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  double v4; // st7
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      *(float *)&ptArgList = 0.0;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 2);
      v4 = *(float *)&ptArgList;
    }
    else
    {
      v4 = Expression_EvalFloat(*ptArgList->aptExpression);
    }
    HumanAI_ptCurrentHumanAI->tTweakParameters.avDamageMultiplier[4] = v4 * 4096.0;
  }
  Rs.nResult = 1;
  Rs.zResult = (char *)&g_zInitialValue;
  Rs.vResult = 1.0;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:1614  [size]
struct Result_s *__cdecl HumanAI_SetInvestigateViewCone2AlphaCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  double v4; // st7
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      *(float *)&ptArgList = 0.0;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 2);
      v4 = *(float *)&ptArgList;
    }
    else
    {
      v4 = Expression_EvalFloat(*ptArgList->aptExpression);
    }
    HumanAI_ptCurrentHumanAI->tTweakParameters.avDamageMultiplier[5] = v4 * 0.01745329238474369;
  }
  Rs.nResult = 1;
  Rs.zResult = (char *)&g_zInitialValue;
  Rs.vResult = 1.0;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:1636  [size]
struct Result_s *__cdecl HumanAI_SetInvestigateViewCone2LengthCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  double v4; // st7
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      *(float *)&ptArgList = 0.0;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 2);
      v4 = *(float *)&ptArgList;
    }
    else
    {
      v4 = Expression_EvalFloat(*ptArgList->aptExpression);
    }
    HumanAI_ptCurrentHumanAI->tTweakParameters.avDamageMultiplier[6] = v4 * 4096.0;
  }
  Rs.nResult = 1;
  Rs.zResult = (char *)&g_zInitialValue;
  Rs.vResult = 1.0;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:1658  [size]
struct Result_s *__cdecl HumanAI_SetInvestigateShoutFrequencyCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  double v4; // st7
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      *(float *)&ptArgList = 0.0;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 2);
      v4 = *(float *)&ptArgList;
    }
    else
    {
      v4 = Expression_EvalFloat(*ptArgList->aptExpression);
    }
    HumanAI_ptCurrentHumanAI->tTweakParameters.avDamageMultiplier[7] = v4 * 30.0;
  }
  Rs.nResult = 1;
  Rs.zResult = (char *)&g_zInitialValue;
  Rs.vResult = 1.0;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:1680  [size]
struct Result_s *__cdecl HumanAI_SetAnimSpeedFactorCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  double v4; // st7
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      *(float *)&ptArgList = 0.0;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 2);
      v4 = *(float *)&ptArgList;
    }
    else
    {
      v4 = Expression_EvalFloat(*ptArgList->aptExpression);
    }
    HumanAI_ptCurrentHumanAI->tTweakParameters.avDamageMultiplier[8] = v4;
  }
  Rs.nResult = 1;
  Rs.zResult = (char *)&g_zInitialValue;
  Rs.vResult = 1.0;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:1702  [anchor-mhash]
struct Result_s *__cdecl HumanAI_SetHearingRangeFactorCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  double v4; // st7
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      *(float *)&ptArgList = 0.0;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 2);
      v4 = *(float *)&ptArgList;
    }
    else
    {
      v4 = Expression_EvalFloat(*ptArgList->aptExpression);
    }
    if ( v4 >= 0.0 )
    {
      if ( v4 > 1.0 )
        v4 = 1.0;
    }
    else
    {
      v4 = 0.0;
    }
    HumanAI_ptCurrentHumanAI->avChannel[7] = v4;
  }
  Rs.nResult = 1;
  Rs.zResult = (char *)&g_zInitialValue;
  Rs.vResult = 1.0;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:1730  [anchor-mhash]
struct Result_s *__cdecl HumanAI_SetSideKickCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // eax
  int v5; // ecx
  int v6; // ecx
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      ptArgList = nullptr;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
      v4 = ptArgList;
    }
    else
    {
      v4 = (struct ArgList_s *)Expression_EvalInt(*ptArgList->aptExpression);
    }
    v5 = HumanAI_ptCurrentHumanAI->anEventPriorityList[5];
    if ( v4 )
      v6 = v5 | 1;
    else
      v6 = v5 & 0xFFFFFFFE;
    HumanAI_ptCurrentHumanAI->anEventPriorityList[5] = v6;
  }
  Rs.nResult = 1;
  Rs.zResult = (char *)&g_zInitialValue;
  Rs.vResult = 1.0;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:1766  [anchor-caller]
struct Result_s *__cdecl HumanAI_UseCombatViewCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  HumanAIContent_UseCombatView(HumanAI_ptCurrentHumanAI);
  Rs.nResult = 1;
  Rs.vResult = 1.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:1782  [anchor-caller]
struct Result_s *__cdecl HumanAI_UseIdleViewCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  HumanAIContent_UseIdleView(HumanAI_ptCurrentHumanAI);
  Rs.nResult = 1;
  Rs.vResult = 1.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:1799  [anchor-callee]
int __cdecl HumanAI_GetEventPriority(struct HumanAI_s *ptHumanAI, int nEvent)
{
  int nAnimationMinimumDelay; // edx
  int result; // eax
  int v5; // ecx
  int *i; // esi

  nAnimationMinimumDelay = ptHumanAI->nAnimationMinimumDelay;
  result = -1;
  v5 = 0;
  if ( nAnimationMinimumDelay > 0 )
  {
    for ( i = &ptHumanAI->anEventPriorityList[6]; *i != nEvent; ++i )
    {
      if ( ++v5 >= nAnimationMinimumDelay )
        return result;
    }
    return v5;
  }
  return result;
}

// source: j/0/humanai/humanai.c:1830  [anchor-mhash]
struct Result_s *__cdecl HumanAI_DelayedEventPassOnCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct ArgList_s *v9; };
    struct { char igi2_o1[20]; _DWORD v10[6]; };
    char igi2_extent[44];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct ArgList_s *v3; // edi
  _DWORD *v4; // ebp
  struct Node_s *v5; // ebx
  _DWORD **nLastEndCommandQTaskID; // eax
  struct Node_s *v7; // ebx

  v3 = ptArgList;
  if ( ptArgList->nArguments == 1 )
  {
    v4 = nullptr;
    if ( ptArgList->isQVM )
    {
      ptArgList = nullptr;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
    }
    else
    {
      ptArgList = (struct ArgList_s *)Expression_EvalInt(*ptArgList->aptExpression);
    }
    v5 = HumanAI_ptCurrentEventStack->ptHead->ptNext != nullptr ? HumanAI_ptCurrentEventStack->ptHead : nullptr;
    nLastEndCommandQTaskID = (_DWORD **)HumanAI_ptCurrentHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID;
    if ( *nLastEndCommandQTaskID )
    {
      v4 = (_DWORD *)HumanAI_ptCurrentHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID;
      Node_Remove(nLastEndCommandQTaskID);
    }
    v4[2] = v5[1].ptNext;
    qmemcpy(v4 + 4, &v5[2], 0x18u);
    v7 = v5 + 5;
    v4[10] = v7->ptNext;
    v4[11] = v7->ptPrev;
    igi2_frame.v9 = ptArgList;
    v4[12] = v7[1].ptNext;
    HumanAI_AddActionToLocalList(HumanAIContent_DelayedEventPassOnInitCB, v4, (unsigned int)igi2_frame.v9);
    igi2_frame.v10[0] = 0;
    igi2_frame.v10[3] = 0;
  }
  else
  {
    igi2_frame.v10[0] = 1;
    igi2_frame.v10[3] = 1072693248;
  }
  igi2_frame.v10[4] = &g_zInitialValue;
  igi2_frame.v10[2] = 0;
  qmemcpy(retstr, igi2_frame.v10, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:1877  [anchor-mhash]
struct Result_s *__cdecl HumanAI_PatrolCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  _DWORD **nLastEndCommandQTaskID; // eax
  _DWORD *v5; // esi
  struct ArgList_s *v6; // eax
  struct ArgList_s *v7; // eax
  struct ArgList_s *v8; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 3 )
  {
    nLastEndCommandQTaskID = (_DWORD **)HumanAI_ptCurrentHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID;
    v5 = nullptr;
    if ( *nLastEndCommandQTaskID )
    {
      v5 = (_DWORD *)HumanAI_ptCurrentHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID;
      Node_Remove(nLastEndCommandQTaskID);
    }
    if ( v3->isQVM )
    {
      ptArgList = nullptr;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
      v6 = ptArgList;
    }
    else
    {
      v6 = (struct ArgList_s *)Expression_EvalInt(*v3->aptExpression);
    }
    v5[2] = v6;
    if ( v3->isQVM )
    {
      ptArgList = nullptr;
      QVM_EvalArg(&ptArgList, 4, v3, 1, 1);
      v7 = ptArgList;
    }
    else
    {
      v7 = (struct ArgList_s *)Expression_EvalInt(v3->aptExpression[1]);
    }
    v5[3] = v7;
    if ( v3->isQVM )
    {
      ptArgList = nullptr;
      QVM_EvalArg(&ptArgList, 4, v3, 2, 1);
      v8 = ptArgList;
    }
    else
    {
      v8 = (struct ArgList_s *)Expression_EvalInt(v3->aptExpression[2]);
    }
    HumanAI_AddActionToLocalList(HumanAIContent_PatrolInitCB, v5, (unsigned int)v8);
    Rs.nResult = 3;
    HIDWORD(Rs.vResult) = 1074266112;
  }
  else
  {
    Rs.nResult = 1;
    HIDWORD(Rs.vResult) = 1072693248;
  }
  Rs.zResult = (char *)&g_zInitialValue;
  LODWORD(Rs.vResult) = 0;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:1921  [anchor-mhash]
struct Result_s *__cdecl HumanAI_DeadCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      ptArgList = nullptr;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
      v4 = ptArgList;
    }
    else
    {
      v4 = (struct ArgList_s *)Expression_EvalInt(*ptArgList->aptExpression);
    }
    HumanAI_AddActionToLocalList(
      (void (__cdecl *)(struct HumanAI_s *, struct HumanAIActionStackItem_s *))HumanAIContent_DeadInitCB,
      nullptr,
      (unsigned int)v4);
  }
  Rs.nResult = 1;
  Rs.zResult = (char *)&g_zInitialValue;
  Rs.vResult = 1.0;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:1949  [anchor-mhash]
struct Result_s *__cdecl HumanAI_FallFlatCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct HumanAI_s *v3; // edx
  int v4; // esi
  int vY_high; // edi
  int GraphNodeDataSize; // eax
  int v7; // eax
  struct Node_s *ptNext; // eax
  struct Node_s *v9; // ecx
  _DWORD **nLastEndCommandQTaskID; // eax
  float *v11; // esi
  unsigned int v12; // eax
  struct Result_s Rs; // [esp+10h] [ebp-18h] BYREF

  if ( ptArgList->nArguments == 2 )
  {
    v3 = HumanAI_ptCurrentHumanAI;
    v4 = *(_DWORD *)&HumanAI_ptCurrentHumanAI->zScriptFile[36];
    vY_high = HIDWORD(HumanAI_ptCurrentHumanAI->tCommon.tAimPosition.vY);
    if ( *(_DWORD *)(v4 + 132) && vY_high < (int)(*(_DWORD *)(v4 + 104)) && vY_high >= 0 )
    {
      GraphNodeDataSize = Graph_GetGraphNodeDataSize(*(_DWORD *)&HumanAI_ptCurrentHumanAI->zScriptFile[36]);
      v3 = HumanAI_ptCurrentHumanAI;
      v7 = *(_DWORD *)(*(_DWORD *)(v4 + 132) + vY_high * GraphNodeDataSize) == -1
         ? 0
         : vY_high * GraphNodeDataSize + *(_DWORD *)(v4 + 132);
    }
    else
    {
      v7 = 0;
    }
    if ( (AIGraph_bStairNodeCriteria & *(_DWORD *)(v7 + 56)) == 0 )
    {
      ptNext = (HumanAI_ptCurrentEventStack->ptHead->ptNext != nullptr
              ? &HumanAI_ptCurrentEventStack->ptHead[7]
              : (struct Node_s *)56)->ptNext;
      if ( !ptNext
        || (v9 = ptNext[1].ptNext) == nullptr
        || Real64x3_Distance((struct real64x3_t *)&v9[5], (struct real64x3_t *)&v3->tQTask.ptParent[1]) >= 122880.0 )
      {
        nLastEndCommandQTaskID = (_DWORD **)v3->atPatrolPathStackItems[0].nLastEndCommandQTaskID;
        v11 = nullptr;
        if ( *nLastEndCommandQTaskID )
        {
          v11 = (float *)v3->atPatrolPathStackItems[0].nLastEndCommandQTaskID;
          Node_Remove(nLastEndCommandQTaskID);
        }
        v11[2] = Script_EvalArgFloat(ptArgList, 0);
        v12 = Script_EvalArgInt(ptArgList, 1);
        HumanAI_AddActionToLocalList(
          (void (__cdecl *)(struct HumanAI_s *, struct HumanAIActionStackItem_s *))HumanAIContent_FallFlatInitCB,
          v11,
          v12);
      }
    }
    Rs.nResult = 2;
    HIDWORD(Rs.vResult) = 0x40000000;
  }
  else
  {
    Rs.nResult = 1;
    HIDWORD(Rs.vResult) = 1072693248;
  }
  Rs.zResult = (char *)&g_zInitialValue;
  LODWORD(Rs.vResult) = 0;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:2015  [anchor-mhash]
struct Result_s *__cdecl HumanAI_ActivateCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { unsigned int pxData; };
    struct { char igi2_o1[4]; struct Result_s Rs; };
    char igi2_extent[28];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v3; // esi
  unsigned int v4; // ebx
  struct QReference_s *v5; // eax
  _WORD *pxObject; // eax
  _DWORD **nLastEndCommandQTaskID; // eax
  unsigned int v8; // eax

  if ( ptArgList->nArguments == 3 )
  {
    v3 = 0;
    if ( ptArgList->isQVM )
    {
      igi2_frame.pxData = 0;
      QVM_EvalArg(&igi2_frame.pxData, 4, ptArgList, 0, 1);
      v4 = igi2_frame.pxData;
    }
    else
    {
      v4 = Expression_EvalInt(*ptArgList->aptExpression);
    }
    if ( v4 >= 0x1000
      || (v5 = Level_atLevelQTaskID[v4]) == nullptr
      || (pxObject = v5->pxObject) == nullptr
      || pxObject[18] == StationaryGun_eQTaskType && *((_BYTE *)pxObject + 592)
      || HumanAI_GetActivatingAI(v4) )
    {
      igi2_frame.Rs.nResult = 0;
      HIDWORD(igi2_frame.Rs.vResult) = 0;
    }
    else
    {
      nLastEndCommandQTaskID = (_DWORD **)HumanAI_ptCurrentHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID;
      if ( *nLastEndCommandQTaskID )
      {
        v3 = HumanAI_ptCurrentHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID;
        Node_Remove(nLastEndCommandQTaskID);
      }
      *(_DWORD *)(v3 + 8) = v4;
      *(_BYTE *)(v3 + 21) = Script_EvalArgInt(ptArgList, 1);
      v8 = Script_EvalArgInt(ptArgList, 2);
      HumanAI_AddActionToLocalList(HumanAIContent_ActivateInitCB, (void *)v3, v8);
      igi2_frame.Rs.nResult = 3;
      HIDWORD(igi2_frame.Rs.vResult) = 1074266112;
    }
  }
  else
  {
    igi2_frame.Rs.nResult = 1;
    HIDWORD(igi2_frame.Rs.vResult) = 1072693248;
  }
  LODWORD(igi2_frame.Rs.vResult) = 0;
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:2083  [size]
struct Result_s *__cdecl HumanAI_WalkToNodeCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  _DWORD **nLastEndCommandQTaskID; // eax
  _DWORD *v5; // esi
  struct ArgList_s *v6; // eax
  struct ArgList_s *v7; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 2 )
  {
    nLastEndCommandQTaskID = (_DWORD **)HumanAI_ptCurrentHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID;
    v5 = nullptr;
    if ( *nLastEndCommandQTaskID )
    {
      v5 = (_DWORD *)HumanAI_ptCurrentHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID;
      Node_Remove(nLastEndCommandQTaskID);
    }
    if ( v3->isQVM )
    {
      ptArgList = nullptr;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
      v6 = ptArgList;
    }
    else
    {
      v6 = (struct ArgList_s *)Expression_EvalInt(*v3->aptExpression);
    }
    v5[2] = v6;
    if ( v3->isQVM )
    {
      ptArgList = nullptr;
      QVM_EvalArg(&ptArgList, 4, v3, 1, 1);
      v7 = ptArgList;
    }
    else
    {
      v7 = (struct ArgList_s *)Expression_EvalInt(v3->aptExpression[1]);
    }
    HumanAI_AddActionToLocalList(HumanAIContent_WalkToNodeInitCB, v5, (unsigned int)v7);
    Rs.nResult = 2;
    HIDWORD(Rs.vResult) = 0x40000000;
  }
  else
  {
    Rs.nResult = 1;
    HIDWORD(Rs.vResult) = 1072693248;
  }
  Rs.zResult = (char *)&g_zInitialValue;
  LODWORD(Rs.vResult) = 0;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:2119  [size]
struct Result_s *__cdecl HumanAI_RunToNodeCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  _DWORD **nLastEndCommandQTaskID; // eax
  _DWORD *v5; // esi
  struct ArgList_s *v6; // eax
  struct ArgList_s *v7; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 2 )
  {
    nLastEndCommandQTaskID = (_DWORD **)HumanAI_ptCurrentHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID;
    v5 = nullptr;
    if ( *nLastEndCommandQTaskID )
    {
      v5 = (_DWORD *)HumanAI_ptCurrentHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID;
      Node_Remove(nLastEndCommandQTaskID);
    }
    if ( v3->isQVM )
    {
      ptArgList = nullptr;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
      v6 = ptArgList;
    }
    else
    {
      v6 = (struct ArgList_s *)Expression_EvalInt(*v3->aptExpression);
    }
    v5[2] = v6;
    if ( v3->isQVM )
    {
      ptArgList = nullptr;
      QVM_EvalArg(&ptArgList, 4, v3, 1, 1);
      v7 = ptArgList;
    }
    else
    {
      v7 = (struct ArgList_s *)Expression_EvalInt(v3->aptExpression[1]);
    }
    HumanAI_AddActionToLocalList(HumanAIContent_RunToNodeInitCB, v5, (unsigned int)v7);
    Rs.nResult = 2;
    HIDWORD(Rs.vResult) = 0x40000000;
  }
  else
  {
    Rs.nResult = 1;
    HIDWORD(Rs.vResult) = 1072693248;
  }
  Rs.zResult = (char *)&g_zInitialValue;
  LODWORD(Rs.vResult) = 0;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:2155  [size]
struct Result_s *__cdecl HumanAI_FireAtNodeCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { __int64 pxData; };
    struct { char igi2_o1[8]; struct Result_s Rs; };
    char igi2_extent[32];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  _DWORD **nLastEndCommandQTaskID; // eax
  int v4; // esi
  int v5; // eax
  double v6; // st7
  double v7; // st7
  char v8; // al
  unsigned int v9; // eax

  if ( ptArgList->nArguments == 5 )
  {
    nLastEndCommandQTaskID = (_DWORD **)HumanAI_ptCurrentHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID;
    v4 = 0;
    if ( *nLastEndCommandQTaskID )
    {
      v4 = HumanAI_ptCurrentHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID;
      Node_Remove(nLastEndCommandQTaskID);
    }
    if ( ptArgList->isQVM )
    {
      LODWORD(igi2_frame.pxData) = 0;
      QVM_EvalArg(&igi2_frame.pxData, 4, ptArgList, 0, 1);
      v5 = igi2_frame.pxData;
    }
    else
    {
      v5 = Expression_EvalInt(*ptArgList->aptExpression);
    }
    *(_DWORD *)(v4 + 8) = v5;
    if ( ptArgList->isQVM )
    {
      LODWORD(igi2_frame.pxData) = 0;
      QVM_EvalArg(&igi2_frame.pxData, 4, ptArgList, 1, 2);
      v6 = *(float *)&igi2_frame.pxData;
    }
    else
    {
      v6 = Expression_EvalFloat((struct QExpression_s *)*((_DWORD *)ptArgList->aptExpression + 1));
    }
    igi2_frame.pxData = (__int64)(30.0 * v6);
    *(_DWORD *)(v4 + 12) = igi2_frame.pxData;
    if ( ptArgList->isQVM )
    {
      LODWORD(igi2_frame.pxData) = 0;
      QVM_EvalArg(&igi2_frame.pxData, 4, ptArgList, 2, 2);
      v7 = *(float *)&igi2_frame.pxData;
    }
    else
    {
      v7 = Expression_EvalFloat((struct QExpression_s *)*((_DWORD *)ptArgList->aptExpression + 2));
    }
    igi2_frame.pxData = (__int64)(30.0 * v7);
    *(_DWORD *)(v4 + 16) = igi2_frame.pxData;
    if ( ptArgList->isQVM )
    {
      LODWORD(igi2_frame.pxData) = 0;
      QVM_EvalArg(&igi2_frame.pxData, 4, ptArgList, 3, 1);
      v8 = igi2_frame.pxData;
    }
    else
    {
      v8 = Expression_EvalInt(ptArgList->aptExpression[3]);
    }
    *(_BYTE *)(v4 + 24) = v8;
    if ( ptArgList->isQVM )
    {
      LODWORD(igi2_frame.pxData) = 0;
      QVM_EvalArg(&igi2_frame.pxData, 4, ptArgList, 4, 1);
      v9 = igi2_frame.pxData;
    }
    else
    {
      v9 = Expression_EvalInt(ptArgList->aptExpression[4]);
    }
    HumanAI_AddActionToLocalList(
      (void (__cdecl *)(struct HumanAI_s *, struct HumanAIActionStackItem_s *))HumanAIContent_FireAtNodeInitCB,
      (void *)v4,
      v9);
    igi2_frame.Rs.nResult = 5;
    HIDWORD(igi2_frame.Rs.vResult) = 1075052544;
  }
  else
  {
    igi2_frame.Rs.nResult = 1;
    HIDWORD(igi2_frame.Rs.vResult) = 1072693248;
  }
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  LODWORD(igi2_frame.Rs.vResult) = 0;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:2196  [size]
struct Result_s *__cdecl HumanAI_FireAtTaskCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { __int64 pxData; };
    struct { char igi2_o1[8]; struct Result_s Rs; };
    char igi2_extent[32];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  _DWORD **nLastEndCommandQTaskID; // eax
  int v4; // esi
  int v5; // eax
  double v6; // st7
  double v7; // st7
  char v8; // al
  unsigned int v9; // eax

  if ( ptArgList->nArguments == 5 )
  {
    nLastEndCommandQTaskID = (_DWORD **)HumanAI_ptCurrentHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID;
    v4 = 0;
    if ( *nLastEndCommandQTaskID )
    {
      v4 = HumanAI_ptCurrentHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID;
      Node_Remove(nLastEndCommandQTaskID);
    }
    if ( ptArgList->isQVM )
    {
      LODWORD(igi2_frame.pxData) = 0;
      QVM_EvalArg(&igi2_frame.pxData, 4, ptArgList, 0, 1);
      v5 = igi2_frame.pxData;
    }
    else
    {
      v5 = Expression_EvalInt(*ptArgList->aptExpression);
    }
    *(_DWORD *)(v4 + 8) = v5;
    if ( ptArgList->isQVM )
    {
      LODWORD(igi2_frame.pxData) = 0;
      QVM_EvalArg(&igi2_frame.pxData, 4, ptArgList, 1, 2);
      v6 = *(float *)&igi2_frame.pxData;
    }
    else
    {
      v6 = Expression_EvalFloat((struct QExpression_s *)*((_DWORD *)ptArgList->aptExpression + 1));
    }
    igi2_frame.pxData = (__int64)(30.0 * v6);
    *(_DWORD *)(v4 + 12) = igi2_frame.pxData;
    if ( ptArgList->isQVM )
    {
      LODWORD(igi2_frame.pxData) = 0;
      QVM_EvalArg(&igi2_frame.pxData, 4, ptArgList, 2, 2);
      v7 = *(float *)&igi2_frame.pxData;
    }
    else
    {
      v7 = Expression_EvalFloat((struct QExpression_s *)*((_DWORD *)ptArgList->aptExpression + 2));
    }
    igi2_frame.pxData = (__int64)(30.0 * v7);
    *(_DWORD *)(v4 + 16) = igi2_frame.pxData;
    if ( ptArgList->isQVM )
    {
      LODWORD(igi2_frame.pxData) = 0;
      QVM_EvalArg(&igi2_frame.pxData, 4, ptArgList, 3, 1);
      v8 = igi2_frame.pxData;
    }
    else
    {
      v8 = Expression_EvalInt(ptArgList->aptExpression[3]);
    }
    *(_BYTE *)(v4 + 24) = v8;
    if ( ptArgList->isQVM )
    {
      LODWORD(igi2_frame.pxData) = 0;
      QVM_EvalArg(&igi2_frame.pxData, 4, ptArgList, 4, 1);
      v9 = igi2_frame.pxData;
    }
    else
    {
      v9 = Expression_EvalInt(ptArgList->aptExpression[4]);
    }
    HumanAI_AddActionToLocalList(
      (void (__cdecl *)(struct HumanAI_s *, struct HumanAIActionStackItem_s *))HumanAIContent_FireAtTaskInitCB,
      (void *)v4,
      v9);
    igi2_frame.Rs.nResult = 5;
    HIDWORD(igi2_frame.Rs.vResult) = 1075052544;
  }
  else
  {
    igi2_frame.Rs.nResult = 1;
    HIDWORD(igi2_frame.Rs.vResult) = 1072693248;
  }
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  LODWORD(igi2_frame.Rs.vResult) = 0;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:2237  [size]
struct Result_s *__cdecl HumanAI_PlayAnimationCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  _DWORD **nLastEndCommandQTaskID; // eax
  _BYTE *v5; // esi
  char v6; // al
  struct ArgList_s *v7; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 2 )
  {
    nLastEndCommandQTaskID = (_DWORD **)HumanAI_ptCurrentHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID;
    v5 = nullptr;
    if ( *nLastEndCommandQTaskID )
    {
      v5 = (_BYTE *)HumanAI_ptCurrentHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID;
      Node_Remove(nLastEndCommandQTaskID);
    }
    if ( v3->isQVM )
    {
      ptArgList = nullptr;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
      v6 = (char)ptArgList;
    }
    else
    {
      v6 = Expression_EvalInt(*v3->aptExpression);
    }
    v5[8] = v6;
    if ( v3->isQVM )
    {
      ptArgList = nullptr;
      QVM_EvalArg(&ptArgList, 4, v3, 1, 1);
      v7 = ptArgList;
    }
    else
    {
      v7 = (struct ArgList_s *)Expression_EvalInt(v3->aptExpression[1]);
    }
    HumanAI_AddActionToLocalList(HumanAIContent_PlayAnimationInitCB, v5, (unsigned int)v7);
    Rs.nResult = 2;
    HIDWORD(Rs.vResult) = 0x40000000;
  }
  else
  {
    Rs.nResult = 1;
    HIDWORD(Rs.vResult) = 1072693248;
  }
  Rs.zResult = (char *)&g_zInitialValue;
  LODWORD(Rs.vResult) = 0;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:2273  [anchor-mhash]
struct Result_s *__cdecl HumanAI_PlaySoundCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  _DWORD **nLastEndCommandQTaskID; // eax
  _BYTE *v5; // esi
  char v6; // al
  struct ArgList_s *v7; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 3 )
  {
    nLastEndCommandQTaskID = (_DWORD **)HumanAI_ptCurrentHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID;
    v5 = nullptr;
    if ( *nLastEndCommandQTaskID )
    {
      v5 = (_BYTE *)HumanAI_ptCurrentHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID;
      Node_Remove(nLastEndCommandQTaskID);
    }
    if ( v3->isQVM )
    {
      v5[8] = 0;
      QVM_EvalArg(v5 + 8, 32, v3, 0, 3);
    }
    else
    {
      Expression_EvalString(*v3->aptExpression, v5 + 8, 32);
    }
    if ( v3->isQVM )
    {
      ptArgList = nullptr;
      QVM_EvalArg(&ptArgList, 4, v3, 1, 1);
      v6 = (char)ptArgList;
    }
    else
    {
      v6 = Expression_EvalInt(v3->aptExpression[1]);
    }
    v5[40] = v6;
    if ( v3->isQVM )
    {
      ptArgList = nullptr;
      QVM_EvalArg(&ptArgList, 4, v3, 2, 1);
      v7 = ptArgList;
    }
    else
    {
      v7 = (struct ArgList_s *)Expression_EvalInt(v3->aptExpression[2]);
    }
    HumanAI_AddActionToLocalList(
      (void (__cdecl *)(struct HumanAI_s *, struct HumanAIActionStackItem_s *))HumanAIContent_PlaySoundInitCB,
      v5,
      (unsigned int)v7);
    Rs.nResult = 3;
    HIDWORD(Rs.vResult) = 1074266112;
  }
  else
  {
    Rs.nResult = 1;
    HIDWORD(Rs.vResult) = 1072693248;
  }
  Rs.zResult = (char *)&g_zInitialValue;
  LODWORD(Rs.vResult) = 0;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:2310  [anchor-mhash]
struct Result_s *__cdecl HumanAI_MoveToEventCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // ebx
  _DWORD **nLastEndCommandQTaskID; // eax
  _BYTE *v5; // ebp
  char v6; // al
  struct ArgList_s *v7; // eax
  struct Result_s Rs; // [esp+Ch] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 2 )
  {
    nLastEndCommandQTaskID = (_DWORD **)HumanAI_ptCurrentHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID;
    v5 = nullptr;
    if ( *nLastEndCommandQTaskID )
    {
      v5 = (_BYTE *)HumanAI_ptCurrentHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID;
      Node_Remove(nLastEndCommandQTaskID);
    }
    qmemcpy(
      v5 + 8,
      HumanAI_ptCurrentEventStack->ptHead->ptNext != nullptr
    ? &HumanAI_ptCurrentEventStack->ptHead[2]
    : (void *)16,
      0x18u);
    if ( v3->isQVM )
    {
      ptArgList = nullptr;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
      v6 = (char)ptArgList;
    }
    else
    {
      v6 = Expression_EvalInt(*v3->aptExpression);
    }
    v5[36] = v6;
    if ( v3->isQVM )
    {
      ptArgList = nullptr;
      QVM_EvalArg(&ptArgList, 4, v3, 1, 1);
      v7 = ptArgList;
    }
    else
    {
      v7 = (struct ArgList_s *)Expression_EvalInt(v3->aptExpression[1]);
    }
    HumanAI_AddActionToLocalList(HumanAIContent_MoveToEventInitCB, v5, (unsigned int)v7);
    Rs.nResult = 2;
    HIDWORD(Rs.vResult) = 0x40000000;
  }
  else
  {
    Rs.nResult = 1;
    HIDWORD(Rs.vResult) = 1072693248;
  }
  Rs.zResult = (char *)&g_zInitialValue;
  LODWORD(Rs.vResult) = 0;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:2349  [anchor-mhash]
struct Result_s *__cdecl HumanAI_LookAtEventCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // ebx
  _DWORD **nLastEndCommandQTaskID; // eax
  float *v5; // ebp
  double v6; // st7
  struct ArgList_s *v7; // eax
  struct Result_s Rs; // [esp+Ch] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 2 )
  {
    nLastEndCommandQTaskID = (_DWORD **)HumanAI_ptCurrentHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID;
    v5 = nullptr;
    if ( *nLastEndCommandQTaskID )
    {
      v5 = (float *)HumanAI_ptCurrentHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID;
      Node_Remove(nLastEndCommandQTaskID);
    }
    qmemcpy(
      v5 + 2,
      HumanAI_ptCurrentEventStack->ptHead->ptNext != nullptr
    ? &HumanAI_ptCurrentEventStack->ptHead[2]
    : (void *)16,
      0x18u);
    if ( v3->isQVM )
    {
      *(float *)&ptArgList = 0.0;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 2);
      v6 = *(float *)&ptArgList;
    }
    else
    {
      v6 = Expression_EvalFloat(*v3->aptExpression);
    }
    v5[8] = v6;
    if ( v3->isQVM )
    {
      *(float *)&ptArgList = 0.0;
      QVM_EvalArg(&ptArgList, 4, v3, 1, 1);
      v7 = ptArgList;
    }
    else
    {
      v7 = (struct ArgList_s *)Expression_EvalInt(v3->aptExpression[1]);
    }
    HumanAI_AddActionToLocalList(
      (void (__cdecl *)(struct HumanAI_s *, struct HumanAIActionStackItem_s *))HumanAIContent_LookAtEventInitCB,
      v5,
      (unsigned int)v7);
    Rs.nResult = 2;
    HIDWORD(Rs.vResult) = 0x40000000;
  }
  else
  {
    Rs.nResult = 1;
    HIDWORD(Rs.vResult) = 1072693248;
  }
  Rs.zResult = (char *)&g_zInitialValue;
  LODWORD(Rs.vResult) = 0;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:2387  [anchor-mhash]
struct Result_s *__cdecl HumanAI_LookInApproxEventDirectionCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { _DWORD *ptContext; };
    struct { char igi2_o1[4]; __int64 pxData; };
    struct { char igi2_o2[12]; struct Result_s Rs; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  _DWORD **nLastEndCommandQTaskID; // eax
  double v4; // st7
  int v5; // eax
  int v6; // eax
  unsigned int v7; // eax

  if ( ptArgList->nArguments == 3 )
  {
    nLastEndCommandQTaskID = (_DWORD **)HumanAI_ptCurrentHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID;
    igi2_frame.ptContext = nullptr;
    if ( *nLastEndCommandQTaskID )
    {
      igi2_frame.ptContext = (_DWORD *)HumanAI_ptCurrentHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID;
      Node_Remove(nLastEndCommandQTaskID);
    }
    qmemcpy(
      igi2_frame.ptContext + 2,
      HumanAI_ptCurrentEventStack->ptHead->ptNext != nullptr
    ? &HumanAI_ptCurrentEventStack->ptHead[2]
    : (void *)16,
      0x18u);
    if ( ptArgList->isQVM )
    {
      LODWORD(igi2_frame.pxData) = 0;
      QVM_EvalArg(&igi2_frame.pxData, 4, ptArgList, 0, 2);
      v4 = *(float *)&igi2_frame.pxData;
    }
    else
    {
      v4 = Expression_EvalFloat(*ptArgList->aptExpression);
    }
    igi2_frame.pxData = (__int64)(30.0 * v4);
    v5 = igi2_frame.pxData;
    igi2_frame.ptContext[8] = igi2_frame.pxData;
    igi2_frame.ptContext[9] = v5;
    if ( ptArgList->isQVM )
    {
      LODWORD(igi2_frame.pxData) = 0;
      QVM_EvalArg(&igi2_frame.pxData, 4, ptArgList, 1, 1);
      v6 = igi2_frame.pxData;
    }
    else
    {
      v6 = Expression_EvalInt(ptArgList->aptExpression[1]);
    }
    igi2_frame.ptContext[10] = v6;
    if ( v6 <= 1 )
      v6 = 1;
    igi2_frame.ptContext[10] = v6;
    if ( ptArgList->isQVM )
    {
      LODWORD(igi2_frame.pxData) = 0;
      QVM_EvalArg(&igi2_frame.pxData, 4, ptArgList, 2, 1);
      v7 = igi2_frame.pxData;
    }
    else
    {
      v7 = Expression_EvalInt(ptArgList->aptExpression[2]);
    }
    HumanAI_AddActionToLocalList(HumanAIContent_LookInApproxDirectionInitCB, igi2_frame.ptContext, v7);
    igi2_frame.Rs.nResult = 3;
    HIDWORD(igi2_frame.Rs.vResult) = 1074266112;
  }
  else
  {
    igi2_frame.Rs.nResult = 1;
    HIDWORD(igi2_frame.Rs.vResult) = 1072693248;
  }
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  LODWORD(igi2_frame.Rs.vResult) = 0;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:2428  [anchor-mhash]
struct Result_s *__cdecl HumanAI_StunnedCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  _DWORD **nLastEndCommandQTaskID; // eax
  float *v5; // esi
  double v6; // st7
  struct ArgList_s *v7; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 2 )
  {
    nLastEndCommandQTaskID = (_DWORD **)HumanAI_ptCurrentHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID;
    v5 = nullptr;
    if ( *nLastEndCommandQTaskID )
    {
      v5 = (float *)HumanAI_ptCurrentHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID;
      Node_Remove(nLastEndCommandQTaskID);
    }
    if ( v3->isQVM )
    {
      *(float *)&ptArgList = 0.0;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 2);
      v6 = *(float *)&ptArgList;
    }
    else
    {
      v6 = Expression_EvalFloat(*v3->aptExpression);
    }
    v5[2] = v6;
    if ( v3->isQVM )
    {
      *(float *)&ptArgList = 0.0;
      QVM_EvalArg(&ptArgList, 4, v3, 1, 1);
      v7 = ptArgList;
    }
    else
    {
      v7 = (struct ArgList_s *)Expression_EvalInt(v3->aptExpression[1]);
    }
    HumanAI_AddActionToLocalList(
      (void (__cdecl *)(struct HumanAI_s *, struct HumanAIActionStackItem_s *))HumanAIContent_StunnedInitCB,
      v5,
      (unsigned int)v7);
    Rs.nResult = 2;
    HIDWORD(Rs.vResult) = 0x40000000;
  }
  else
  {
    Rs.nResult = 1;
    HIDWORD(Rs.vResult) = 1072693248;
  }
  Rs.zResult = (char *)&g_zInitialValue;
  LODWORD(Rs.vResult) = 0;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:2464  [anchor-mhash]
struct Result_s *__cdecl HumanAI_KickGrenadeCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct ArgList_s *v9; };
    struct { char igi2_o1[20]; struct Result_s Rs; };
    char igi2_extent[44];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct ArgList_s *v3; // edi
  struct Node_s *v4; // ebx
  _DWORD *v5; // ebp
  _DWORD **nLastEndCommandQTaskID; // eax
  struct QReference_s *v7; // eax

  v3 = ptArgList;
  if ( ptArgList->nArguments == 1 )
  {
    v4 = HumanAI_ptCurrentEventStack->ptHead->ptNext != nullptr ? HumanAI_ptCurrentEventStack->ptHead : nullptr;
    v5 = nullptr;
    if ( ptArgList->isQVM )
    {
      ptArgList = nullptr;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
    }
    else
    {
      ptArgList = (struct ArgList_s *)Expression_EvalInt(*ptArgList->aptExpression);
    }
    if ( v4[6].ptPrev[1].ptNext )
    {
      nLastEndCommandQTaskID = (_DWORD **)HumanAI_ptCurrentHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID;
      if ( *nLastEndCommandQTaskID )
      {
        v5 = (_DWORD *)HumanAI_ptCurrentHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID;
        Node_Remove(nLastEndCommandQTaskID);
      }
      qmemcpy(v5 + 2, &v4[2], 0x18u);
      v7 = QTask_NewQTaskRef((struct QTask_s *)v4[6].ptPrev[1].ptNext);
      igi2_frame.v9 = ptArgList;
      v5[10] = v7;
      HumanAI_AddActionToLocalList(HumanAIContent_KickGrenadeInitCB, v5, (unsigned int)igi2_frame.v9);
    }
  }
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  igi2_frame.Rs.vResult = 1.0;
  igi2_frame.Rs.nResult = 1;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:2511  [anchor-mhash]
struct Result_s *__cdecl HumanAI_RunPanickingCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct HumanAIActionContext_t *v16; };
    struct { char igi2_o1[4]; float pxData; };
    struct { char igi2_o2[8]; struct QTask_s *ptParent; };
    struct { char igi2_o3[12]; struct HumanAI_s *ptHumanAI; };
    struct { char igi2_o4[16]; float v20; };
    struct { char igi2_o5[20]; float v21; };
    struct { char igi2_o6[24]; float v22; };
    struct { char igi2_o7[28]; float v23[6]; };
    struct { char igi2_o8[52]; struct HumanAIEventContext_t ptEventContext; };
    char igi2_extent[116];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  bool v3; // zf
  struct HumanAIActionContext_t *nLastEndCommandQTaskID; // eax
  struct HumanAIActionContext_t *v5; // ebx
  double v6; // st7
  float v7; // eax
  struct Node_s *v8; // eax
  struct Node_s *ptPrev; // ecx
  float v10; // eax
  double v11; // st7
  long double v12; // st4
  long double v13; // st3
  int ptTail; // eax

  v3 = ptArgList->nArguments == 2;
  igi2_frame.ptHumanAI = HumanAI_ptCurrentHumanAI;
  if ( v3 )
  {
    nLastEndCommandQTaskID = (struct HumanAIActionContext_t *)HumanAI_ptCurrentHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID;
    igi2_frame.ptParent = HumanAI_ptCurrentHumanAI->tQTask.ptParent;
    v5 = nullptr;
    igi2_frame.v16 = nullptr;
    if ( nLastEndCommandQTaskID->tNode.ptNext )
    {
      igi2_frame.v16 = nLastEndCommandQTaskID;
      v5 = (struct HumanAIActionContext_t *)Node_Remove(nLastEndCommandQTaskID);
    }
    if ( ptArgList->isQVM )
    {
      igi2_frame.pxData = 0.0;
      QVM_EvalArg(&igi2_frame.pxData, 4, ptArgList, 0, 2);
      v6 = igi2_frame.pxData;
    }
    else
    {
      v6 = Expression_EvalFloat(*ptArgList->aptExpression);
    }
    v5->uContext.tRunToCoverContext.tPosition.vZ = v6;
    if ( ptArgList->isQVM )
    {
      igi2_frame.pxData = 0.0;
      QVM_EvalArg(&igi2_frame.pxData, 4, ptArgList, 1, 1);
      v7 = igi2_frame.pxData;
    }
    else
    {
      v7 = COERCE_FLOAT(Expression_EvalInt(ptArgList->aptExpression[1]));
    }
    igi2_frame.pxData = v7;
    qmemcpy(
      &v5->uContext,
      HumanAI_ptCurrentEventStack->ptHead->ptNext != nullptr
    ? &HumanAI_ptCurrentEventStack->ptHead[2]
    : (void *)16,
      0x18u);
    if ( (HumanAI_ptCurrentEventStack->ptHead->ptNext != nullptr
        ? &HumanAI_ptCurrentEventStack->ptHead[1]
        : (struct Node_s *)8)->ptNext == (struct Node_s *)16 )
    {
      v8 = HumanAI_ptCurrentEventStack->ptHead->ptNext != nullptr
         ? &HumanAI_ptCurrentEventStack->ptHead[8]
         : (struct Node_s *)64;
      igi2_frame.v20 = *(float *)&(HumanAI_ptCurrentEventStack->ptHead->ptNext != nullptr
                      ? &HumanAI_ptCurrentEventStack->ptHead[8]
                      : (struct Node_s *)64)->ptNext;
      ptPrev = v8->ptPrev;
      v10 = *(float *)&v8[1].ptNext;
      igi2_frame.v21 = *(float *)&ptPrev;
      v11 = *(double *)&igi2_frame.ptParent[1].ptNext;
      igi2_frame.v22 = v10;
      igi2_frame.v23[0] = v11 - v5->uContext.tLookAtPositionContext.tPosition.vX;
      igi2_frame.v23[1] = *(double *)&igi2_frame.ptParent[1].tQTaskChildren.ptHead - v5->uContext.tRunToCoverContext.tPosition.vX;
      igi2_frame.v23[2] = *(double *)&igi2_frame.ptParent[1].tQTaskChildren.ptTail - v5->uContext.tRunToCoverContext.tPosition.vY;
      v12 = sqrt(igi2_frame.v20 * igi2_frame.v20 + igi2_frame.v21 * igi2_frame.v21 + v10 * v10);
      if ( v12 > 0.0 )
      {
        igi2_frame.v20 = igi2_frame.v20 * (1.0 / v12);
        igi2_frame.v21 = igi2_frame.v21 * (1.0 / v12);
        v13 = sqrt(igi2_frame.v23[0] * igi2_frame.v23[0] + igi2_frame.v23[1] * igi2_frame.v23[1] + igi2_frame.v23[2] * igi2_frame.v23[2]);
        if ( v13 > 0.0
          && 1.0 / v12 * igi2_frame.v22 * (1.0 / v13 * igi2_frame.v23[2]) + igi2_frame.v21 * (1.0 / v13 * igi2_frame.v23[1]) + igi2_frame.v20 * (igi2_frame.v23[0] * (1.0 / v13)) < 0.5 )
        {
          HumanAI_RemoveActionContext(igi2_frame.ptHumanAI, v5);
LABEL_18:
          igi2_frame.v23[0] = 0.0;
          igi2_frame.v23[3] = 0.0;
          goto LABEL_19;
        }
      }
      ptTail = (int)igi2_frame.ptParent[10].tQTaskRefList.ptTail;
      igi2_frame.ptEventContext.eEvent = 37;
      igi2_frame.ptEventContext.eTeam = ptTail;
      igi2_frame.ptEventContext.bFlags = 1314;
      igi2_frame.ptEventContext.ptReferenceQTask = nullptr;
      igi2_frame.ptEventContext.ptHumanOriginatorQTask = igi2_frame.ptParent;
      igi2_frame.ptEventContext.ptPosition = (struct real64x3_t *)&v5->uContext;
      igi2_frame.ptEventContext.vRadius = 40960.0;
      HumanAI_SendEvent(&igi2_frame.ptEventContext);
      v5 = igi2_frame.v16;
    }
    HumanAI_AddActionToLocalList(HumanAIContent_RunPanickingInitCB, v5, LODWORD(igi2_frame.pxData));
    goto LABEL_18;
  }
  LODWORD(igi2_frame.v23[0]) = 1;
  igi2_frame.v23[3] = 1.875;
LABEL_19:
  igi2_frame.v23[2] = 0.0;
  LODWORD(igi2_frame.v23[4]) = &g_zInitialValue;
  qmemcpy(retstr, igi2_frame.v23, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:2614  [size]
struct Result_s *__cdecl HumanAI_IdleCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  void *v4; // esi
  struct ArgList_s *v5; // edi
  _DWORD **nLastEndCommandQTaskID; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 1 )
  {
    v4 = nullptr;
    if ( ptArgList->isQVM )
    {
      ptArgList = nullptr;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
      v5 = ptArgList;
    }
    else
    {
      v5 = (struct ArgList_s *)Expression_EvalInt(*ptArgList->aptExpression);
    }
    nLastEndCommandQTaskID = (_DWORD **)HumanAI_ptCurrentHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID;
    if ( *nLastEndCommandQTaskID )
    {
      v4 = (void *)HumanAI_ptCurrentHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID;
      Node_Remove(nLastEndCommandQTaskID);
    }
    HumanAI_AddActionToLocalList(HumanAIContent_IdleInitCB, v4, (unsigned int)v5);
  }
  Rs.zResult = (char *)&g_zInitialValue;
  Rs.vResult = 1.0;
  Rs.nResult = 1;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:2647  [size]
struct Result_s *__cdecl HumanAI_CombatIdleCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  void *v4; // esi
  struct ArgList_s *v5; // edi
  _DWORD **nLastEndCommandQTaskID; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 1 )
  {
    v4 = nullptr;
    if ( ptArgList->isQVM )
    {
      ptArgList = nullptr;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
      v5 = ptArgList;
    }
    else
    {
      v5 = (struct ArgList_s *)Expression_EvalInt(*ptArgList->aptExpression);
    }
    nLastEndCommandQTaskID = (_DWORD **)HumanAI_ptCurrentHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID;
    if ( *nLastEndCommandQTaskID )
    {
      v4 = (void *)HumanAI_ptCurrentHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID;
      Node_Remove(nLastEndCommandQTaskID);
    }
    HumanAI_AddActionToLocalList(HumanAIContent_CombatIdleInitCB, v4, (unsigned int)v5);
  }
  Rs.zResult = (char *)&g_zInitialValue;
  Rs.vResult = 1.0;
  Rs.nResult = 1;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:2681  [anchor-mhash]
struct Result_s *__cdecl HumanAI_EnemyDetectionCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { __int64 pxData; };
    struct { char igi2_o1[8]; struct Result_s Rs; };
    struct { char igi2_o2[32]; struct AIDetectionGetDetectionInfoContext_s tContext; };
    char igi2_extent[120];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  unsigned int v3; // ebx
  _DWORD *bQTaskMask; // eax
  int v5; // esi
  struct HumanAI_s *v6; // edi
  _DWORD **nLastEndCommandQTaskID; // eax
  _DWORD **v8; // eax

  if ( ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      LODWORD(igi2_frame.pxData) = 0;
      QVM_EvalArg(&igi2_frame.pxData, 4, ptArgList, 0, 1);
      v3 = igi2_frame.pxData;
    }
    else
    {
      v3 = Expression_EvalInt(*ptArgList->aptExpression);
    }
    bQTaskMask = (_DWORD *)HumanAI_ptCurrentHumanAI->tAIDetection.atListItems[0].bQTaskMask;
    if ( *bQTaskMask )
    {
      if ( bQTaskMask )
      {
        v5 = *(_DWORD *)(bQTaskMask[2] + 8);
        if ( v5 )
        {
          igi2_frame.tContext.isAlive = 1;
          ((void (__cdecl *)(int, struct AIDetectionGetDetectionInfoContext_s *))QTask_aatQTaskFinalEvent[AIDetection_eGetDetectionInfoQTaskEvent][*(unsigned __int16 *)(v5 + 36)].pfHandler)(
            v5,
            &igi2_frame.tContext);
          if ( igi2_frame.tContext.isAlive )
          {
            v6 = HumanAI_ptCurrentHumanAI;
            nLastEndCommandQTaskID = (_DWORD **)HumanAI_ptCurrentHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID;
            if ( *nLastEndCommandQTaskID )
            {
              v8 = Node_Remove(nLastEndCommandQTaskID);
              igi2_frame.pxData = (__int64)v6->tTweakParameters.avDamageMultiplier[9];
              v8[2] = (_DWORD *)igi2_frame.pxData;
              qmemcpy(v8 + 4, (void *)(v5 + 40), 0x18u);
              HumanAI_AddActionToLocalList(
                (void (__cdecl *)(struct HumanAI_s *, struct HumanAIActionStackItem_s *))pfActionInitCB__,
                v8,
                v3);
            }
          }
        }
      }
    }
  }
  igi2_frame.Rs.nResult = 1;
  igi2_frame.Rs.vResult = 1.0;
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:2752  [anchor-mhash]
struct Result_s *__cdecl HumanAI_LookAtNodeCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // esi
  int v5; // ebx
  struct GraphNode_s *v6; // esi
  int v7; // eax
  _DWORD *nLastEndCommandQTaskID; // edi
  unsigned int v9; // ebx
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 2 )
  {
    if ( ptArgList->isQVM )
    {
      ptArgList = nullptr;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
      v4 = ptArgList;
    }
    else
    {
      v4 = (struct ArgList_s *)Expression_EvalInt(*ptArgList->aptExpression);
    }
    v5 = *(_DWORD *)&HumanAI_ptCurrentHumanAI->zScriptFile[36];
    if ( *(_DWORD *)(v5 + 132) )
    {
      if ( (int)v4 < (int)(*(_DWORD *)(v5 + 104)) && (int)v4 >= 0 )
      {
        v6 = (struct GraphNode_s *)((_DWORD)v4
                                  * Graph_GetGraphNodeDataSize(*(_DWORD *)&HumanAI_ptCurrentHumanAI->zScriptFile[36])
                                  + *(_DWORD *)(v5 + 132));
        if ( v6->nID != -1 )
        {
          v7 = Script_EvalArgInt(v3, 1);
          nLastEndCommandQTaskID = (_DWORD *)HumanAI_ptCurrentHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID;
          v9 = v7;
          if ( *nLastEndCommandQTaskID )
          {
            Node_Remove((_DWORD **)HumanAI_ptCurrentHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID);
            Graph_GetNodePos((struct real64x3_t *)(nLastEndCommandQTaskID + 2), v6);
            HumanAI_AddActionToLocalList(
              (void (__cdecl *)(struct HumanAI_s *, struct HumanAIActionStackItem_s *))HumanAIContent_LookAtPositionInitCB,
              nLastEndCommandQTaskID,
              v9);
          }
        }
      }
    }
  }
  Rs.zResult = (char *)&g_zInitialValue;
  Rs.vResult = 1.0;
  Rs.nResult = 1;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:2800  [anchor-mhash]
struct Result_s *__cdecl HumanAI_HasSeenDeadFriendlyBeforeCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  Rs.nResult = HumanAI_ptCurrentHumanAI->anEventPriorityList[5] & 2;
  Rs.vResult = (double)Rs.nResult;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:2814  [anchor-mhash]
struct Result_s *__cdecl HumanAI_SetStandActionAnimationCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  char *zStandActionAnimation; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  if ( ptArgList->nArguments == 1 )
  {
    zStandActionAnimation = HumanAI_ptCurrentHumanAI->zStandActionAnimation;
    if ( ptArgList->isQVM )
    {
      *zStandActionAnimation = 0;
      QVM_EvalArg(zStandActionAnimation, 32, ptArgList, 0, 3);
    }
    else
    {
      Expression_EvalString(*ptArgList->aptExpression, HumanAI_ptCurrentHumanAI->zStandActionAnimation, 32);
    }
  }
  Rs.nResult = 1;
  Rs.zResult = (char *)&g_zInitialValue;
  Rs.vResult = 1.0;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:2835  [anchor-mhash]
struct Result_s *__cdecl HumanAI_HasTargetCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  bool v3; // zf
  struct Result_s *result; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = HumanAI_GetTargetQTask(HumanAI_ptCurrentHumanAI, true) == nullptr;
  result = retstr;
  Rs.zResult = (char *)&g_zInitialValue;
  LODWORD(Rs.vResult) = 0;
  if ( v3 )
  {
    Rs.nResult = 0;
    HIDWORD(Rs.vResult) = 0;
  }
  else
  {
    Rs.nResult = 1;
    HIDWORD(Rs.vResult) = 1072693248;
  }
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return result;
}

// source: j/0/humanai/humanai.c:2857  [anchor-mhash]
struct Result_s *__cdecl HumanAI_LimitViewRangeCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // eax
  int v5; // ecx
  int v6; // ecx
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      ptArgList = nullptr;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
      v4 = ptArgList;
    }
    else
    {
      v4 = (struct ArgList_s *)Expression_EvalInt(*ptArgList->aptExpression);
    }
    v5 = HumanAI_ptCurrentHumanAI->anEventPriorityList[5];
    if ( v4 )
      v6 = v5 & 0xFFFFFFDF;
    else
      v6 = v5 | 0x20;
    HumanAI_ptCurrentHumanAI->anEventPriorityList[5] = v6;
  }
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:2886  [anchor-mhash]
struct Result_s *__cdecl HumanAI_DeadFriendlyDetectionCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // ebx
  _DWORD **nLastEndCommandQTaskID; // eax
  _DWORD **v6; // eax
  struct List_s *v7; // ecx
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      ptArgList = nullptr;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
      v4 = ptArgList;
    }
    else
    {
      v4 = (struct ArgList_s *)Expression_EvalInt(*ptArgList->aptExpression);
    }
    nLastEndCommandQTaskID = (_DWORD **)HumanAI_ptCurrentHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID;
    if ( *nLastEndCommandQTaskID )
    {
      v6 = Node_Remove(nLastEndCommandQTaskID);
      v7 = HumanAI_ptCurrentEventStack;
      v6[2] = nullptr;
      qmemcpy(v6 + 4, v7->ptHead->ptNext != nullptr ? &v7->ptHead[2] : (void *)16, 0x18u);
      HumanAI_AddActionToLocalList(
        (void (__cdecl *)(struct HumanAI_s *, struct HumanAIActionStackItem_s *))HumanAIContent_DeadFriendlyDetectionInitCB,
        v6,
        (unsigned int)v4);
    }
  }
  Rs.nResult = 1;
  Rs.vResult = 1.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:2925  [anchor-mhash]
struct Result_s *__cdecl HumanAI_RunToCoverCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  _DWORD *nLastEndCommandQTaskID; // ebx
  struct List_s *v4; // ecx
  unsigned int v5; // eax
  struct Result_s Rs; // [esp+Ch] [ebp-18h] BYREF

  if ( ptArgList->nArguments == 2 )
  {
    nLastEndCommandQTaskID = (_DWORD *)HumanAI_ptCurrentHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID;
    if ( *nLastEndCommandQTaskID )
    {
      Node_Remove((_DWORD **)HumanAI_ptCurrentHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID);
      v4 = HumanAI_ptCurrentEventStack;
      nLastEndCommandQTaskID[2] = 0;
      qmemcpy(nLastEndCommandQTaskID + 4, v4->ptHead->ptNext != nullptr ? &v4->ptHead[2] : (void *)16, 0x18u);
      nLastEndCommandQTaskID[3] = Script_EvalArgInt(ptArgList, 0);
      v5 = Script_EvalArgInt(ptArgList, 1);
      HumanAI_AddActionToLocalList(HumanAIContent_RunToCoverInitCB, nLastEndCommandQTaskID, v5);
    }
  }
  Rs.nResult = 1;
  Rs.vResult = 1.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:2965  [anchor-mhash]
struct Result_s *__cdecl HumanAI_WaitCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  _DWORD *nLastEndCommandQTaskID; // esi
  unsigned int v4; // eax
  struct Result_s Rs; // [esp+10h] [ebp-18h] BYREF

  if ( ptArgList->nArguments == 2 )
  {
    nLastEndCommandQTaskID = (_DWORD *)HumanAI_ptCurrentHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID;
    if ( *nLastEndCommandQTaskID )
    {
      Node_Remove((_DWORD **)HumanAI_ptCurrentHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID);
      nLastEndCommandQTaskID[2] = (__int64)(Script_EvalArgFloat(ptArgList, 0) * 30.0);
      v4 = Script_EvalArgInt(ptArgList, 1);
      HumanAI_AddActionToLocalList(
        (void (__cdecl *)(struct HumanAI_s *, struct HumanAIActionStackItem_s *))HumanAIContent_WaitInitCB,
        nLastEndCommandQTaskID,
        v4);
    }
  }
  Rs.nResult = 1;
  Rs.vResult = 1.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:3004  [size]
struct Result_s *__cdecl HumanAI_OffensiveCombatCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  _DWORD *nLastEndCommandQTaskID; // esi
  unsigned int v4; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  if ( ptArgList->nArguments == 1 )
  {
    nLastEndCommandQTaskID = (_DWORD *)HumanAI_ptCurrentHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID;
    if ( *nLastEndCommandQTaskID )
    {
      Node_Remove((_DWORD **)HumanAI_ptCurrentHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID);
      v4 = Script_EvalArgInt(ptArgList, 0);
      HumanAI_AddActionToLocalList(
        (void (__cdecl *)(struct HumanAI_s *, struct HumanAIActionStackItem_s *))HumanAIContent_OffensiveCombatInitCB,
        nLastEndCommandQTaskID,
        v4);
    }
  }
  Rs.nResult = 1;
  Rs.vResult = 1.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:3040  [size]
struct Result_s *__cdecl HumanAI_DefensiveCombatCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  _DWORD *nLastEndCommandQTaskID; // esi
  unsigned int v4; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  if ( ptArgList->nArguments == 1 )
  {
    nLastEndCommandQTaskID = (_DWORD *)HumanAI_ptCurrentHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID;
    if ( *nLastEndCommandQTaskID )
    {
      Node_Remove((_DWORD **)HumanAI_ptCurrentHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID);
      v4 = Script_EvalArgInt(ptArgList, 0);
      HumanAI_AddActionToLocalList(
        (void (__cdecl *)(struct HumanAI_s *, struct HumanAIActionStackItem_s *))HumanAIContent_DefensiveCombatInitCB,
        nLastEndCommandQTaskID,
        v4);
    }
  }
  Rs.nResult = 1;
  Rs.vResult = 1.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:3079  [anchor-mhash]
struct Result_s *__cdecl HumanAI_LookAroundCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  _DWORD **nLastEndCommandQTaskID; // eax
  void *v5; // ebx
  struct ArgList_s *v6; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 2 )
  {
    nLastEndCommandQTaskID = (_DWORD **)HumanAI_ptCurrentHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID;
    v5 = nullptr;
    if ( *nLastEndCommandQTaskID )
    {
      v5 = (void *)HumanAI_ptCurrentHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID;
      Node_Remove(nLastEndCommandQTaskID);
    }
    if ( v3->isQVM )
    {
      ptArgList = nullptr;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
    }
    else
    {
      Expression_EvalInt(*v3->aptExpression);
    }
    if ( v3->isQVM )
    {
      ptArgList = nullptr;
      QVM_EvalArg(&ptArgList, 4, v3, 1, 1);
      v6 = ptArgList;
    }
    else
    {
      v6 = (struct ArgList_s *)Expression_EvalInt(v3->aptExpression[1]);
    }
    HumanAI_AddActionToLocalList(HumanAIContent_LookAroundInitCB, v5, (unsigned int)v6);
  }
  Rs.zResult = (char *)&g_zInitialValue;
  Rs.vResult = 1.0;
  Rs.nResult = 1;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:3125  [anchor-mhash]
struct Result_s *__cdecl HumanAI_CallForBackupCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct Result_s Rs; };
    struct { char igi2_o1[24]; struct HumanAIEventContext_t tEventContext; };
    char igi2_extent[88];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptParent; // edi
  _DWORD *bQTaskMask; // eax
  int v5; // esi
  double v6; // st7
  int ptTail; // ecx

  ptParent = HumanAI_ptCurrentHumanAI->tQTask.ptParent;
  if ( ptArgList->nArguments != 1 )
    goto LABEL_7;
  bQTaskMask = (_DWORD *)HumanAI_ptCurrentHumanAI->tAIDetection.atListItems[0].bQTaskMask;
  if ( !*bQTaskMask || !bQTaskMask )
    goto LABEL_7;
  v5 = *(_DWORD *)(bQTaskMask[2] + 8);
  if ( v5 )
  {
    v6 = Script_EvalArgFloat(ptArgList, 0);
    igi2_frame.tEventContext.bFlags = 38;
    igi2_frame.tEventContext.eEvent = 25;
    ptTail = (int)ptParent[10].tQTaskRefList.ptTail;
    igi2_frame.tEventContext.vRadius = v6 * 4096.0;
    igi2_frame.tEventContext.eTeam = ptTail;
    igi2_frame.tEventContext.ptHumanOriginatorQTask = ptParent;
    igi2_frame.tEventContext.ptPosition = (struct real64x3_t *)(v5 + 40);
    igi2_frame.tEventContext.ptReferenceQTask = (struct QTask_s *)v5;
    HumanAI_SendEvent(&igi2_frame.tEventContext);
LABEL_7:
    HIDWORD(igi2_frame.Rs.vResult) = 1072693248;
    igi2_frame.Rs.nResult = 1;
    goto LABEL_8;
  }
  igi2_frame.Rs.nResult = 0;
  HIDWORD(igi2_frame.Rs.vResult) = 0;
LABEL_8:
  LODWORD(igi2_frame.Rs.vResult) = 0;
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:3185  [anchor-mhash]
struct Result_s *__cdecl HumanAI_RemoveAlarmActionsCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int nAlarmOnPriority; };
    struct { char igi2_o1[4]; struct Result_s Rs; };
    char igi2_extent[28];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct HumanAI_s *v3; // ebp
  void (__cdecl *pfRunCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // esi
  void (__cdecl *v5)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // edi
  void (__cdecl *v6)(struct HumanAI_s *, _DWORD); // eax
  struct HumanAI_s *v7; // ebx
  _DWORD *v8; // eax

  v3 = HumanAI_ptCurrentHumanAI;
  pfRunCallback = HumanAI_ptCurrentHumanAI->atActionStackItemList[0].pfRunCallback;
  v5 = *(void (__cdecl **)(struct HumanAI_s *, struct HumanAIActionStackItem_s *))pfRunCallback;
  igi2_frame.nAlarmOnPriority = HumanAI_ptCurrentHumanAI->anEventPriorityList[13];
  if ( *(_DWORD *)pfRunCallback )
  {
    do
    {
      if ( *((_DWORD *)pfRunCallback + 3) == igi2_frame.nAlarmOnPriority )
      {
        v6 = *((void (__cdecl **)(struct HumanAI_s *, _DWORD))pfRunCallback + 9);
        v7 = v3;
        if ( v6 )
        {
          v6(v3, pfRunCallback);
          v3 = HumanAI_ptCurrentHumanAI;
        }
        Node_Remove((_DWORD **)pfRunCallback);
        v8 = *((_DWORD **)pfRunCallback + 12);
        *((_BYTE *)pfRunCallback + 52) = 0;
        if ( v8 )
        {
          v8[1] = 0;
          *v8 = 0;
          List_AddTail(v8, (int)&v7->atPatrolPathStackItems[0].nLastEndCommandQTaskID);
          *((_DWORD *)pfRunCallback + 12) = 0;
        }
      }
      pfRunCallback = v5;
      v5 = *(void (__cdecl **)(struct HumanAI_s *, struct HumanAIActionStackItem_s *))v5;
    }
    while ( v5 );
  }
  igi2_frame.Rs.nResult = 1;
  igi2_frame.Rs.vResult = 1.0;
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:3221  [size]
struct Result_s *__cdecl HumanAI_SetViewLengthCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  double v4; // st7
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      *(float *)&ptArgList = 0.0;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 2);
      v4 = *(float *)&ptArgList;
    }
    else
    {
      v4 = Expression_EvalFloat(*ptArgList->aptExpression);
    }
    HumanAI_ptCurrentHumanAI->tView.vViewConeLength = v4 * 4096.0;
  }
  Rs.nResult = 1;
  Rs.zResult = (char *)&g_zInitialValue;
  Rs.vResult = 1.0;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:3244  [size]
struct Result_s *__cdecl HumanAI_SetViewAlphaCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  double v4; // st7
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      *(float *)&ptArgList = 0.0;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 2);
      v4 = *(float *)&ptArgList;
    }
    else
    {
      v4 = Expression_EvalFloat(*ptArgList->aptExpression);
    }
    HumanAI_ptCurrentHumanAI->tView.vViewConeAlpha = v4 * 0.01745329238474369;
  }
  Rs.nResult = 1;
  Rs.zResult = (char *)&g_zInitialValue;
  Rs.vResult = 1.0;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:3272  [size]
struct Result_s *__cdecl HumanAI_SetViewGammaCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  double v4; // st7
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      *(float *)&ptArgList = 0.0;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 2);
      v4 = *(float *)&ptArgList;
    }
    else
    {
      v4 = Expression_EvalFloat(*ptArgList->aptExpression);
    }
    HumanAI_ptCurrentHumanAI->tView.vViewConeGamma = v4 * 0.01745329238474369;
  }
  Rs.nResult = 1;
  Rs.zResult = (char *)&g_zInitialValue;
  Rs.vResult = 1.0;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:3300  [size]
struct Result_s *__cdecl HumanAI_SetSecondaryViewLengthCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  double v4; // st7
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      *(float *)&ptArgList = 0.0;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 2);
      v4 = *(float *)&ptArgList;
    }
    else
    {
      v4 = Expression_EvalFloat(*ptArgList->aptExpression);
    }
    HumanAI_ptCurrentHumanAI->tView.vSecondaryViewConeLength = v4 * 4096.0;
  }
  Rs.nResult = 1;
  Rs.zResult = (char *)&g_zInitialValue;
  Rs.vResult = 1.0;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:3324  [size]
struct Result_s *__cdecl HumanAI_SetSecondaryViewAlphaCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  double v4; // st7
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      *(float *)&ptArgList = 0.0;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 2);
      v4 = *(float *)&ptArgList;
    }
    else
    {
      v4 = Expression_EvalFloat(*ptArgList->aptExpression);
    }
    HumanAI_ptCurrentHumanAI->tView.vSecondaryViewConeAlpha = v4 * 0.01745329238474369;
  }
  Rs.nResult = 1;
  Rs.zResult = (char *)&g_zInitialValue;
  Rs.vResult = 1.0;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:3352  [size]
struct Result_s *__cdecl HumanAI_SetSecondaryViewGammaCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  double v4; // st7
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      *(float *)&ptArgList = 0.0;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 2);
      v4 = *(float *)&ptArgList;
    }
    else
    {
      v4 = Expression_EvalFloat(*ptArgList->aptExpression);
    }
    HumanAI_ptCurrentHumanAI->tView.vSecondaryViewConeGamma = v4 * 0.01745329238474369;
  }
  Rs.nResult = 1;
  Rs.zResult = (char *)&g_zInitialValue;
  Rs.vResult = 1.0;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:3380  [anchor-strings]
struct Result_s *__cdecl HumanAI_GetCurrentEventTypeCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+4h] [ebp-18h] BYREF

  if ( !HumanAI_ptCurrentEventStack->ptHead->ptNext )
  {
    LDebug_Error("EventStack empty");
    abort();
  }
  Rs.nResult = (int)HumanAI_ptCurrentEventStack->ptHead[1].ptNext;
  Rs.vResult = (double)Rs.nResult;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:3414  [anchor-mhash]
struct Result_s *__cdecl HumanAI_GetRandomValueCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  double v4; // st7
  struct Game_s *v5; // eax
  unsigned int v6; // ecx
  unsigned int v7; // edx
  double v8; // st6
  struct Result_s Rs; // [esp+10h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      *(float *)&ptArgList = 0.0;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 2);
      v4 = *(float *)&ptArgList;
    }
    else
    {
      v4 = Expression_EvalFloat(*ptArgList->aptExpression);
    }
    v5 = Game_ptGame;
    v6 = (Game_ptGame->tRunRandomState.anRandom[0] >> 7)
       ^ Game_ptGame->tRunRandomState.anRandom[2]
       ^ Game_ptGame->tRunRandomState.anRandom[1];
    v7 = v6 + Game_ptGame->tRunRandomState.anRandom[0];
    Game_ptGame->tRunRandomState.anRandom[2] ^= Game_ptGame->tRunRandomState.anRandom[0] >> 7;
    v5->tRunRandomState.anRandom[1] = v6;
    v5->tRunRandomState.anRandom[0] = v7;
    ptArgList = (struct ArgList_s *)(unsigned __int16)v7;
    v8 = (double)(unsigned __int16)v7 * 0.0000152587890625 * v4;
    Rs.nResult = (__int64)v8;
    Rs.vResult = v8;
  }
  else
  {
    Rs.nResult = 1;
    Rs.vResult = 1.0;
  }
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:3441  [size]
struct Result_s *__cdecl HumanAI_DefaultHandlerCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  Script_Execute(HumanAI_ptDefaultScript);
  Rs.nResult = 1;
  Rs.vResult = 1.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:3463  [anchor-mhash]
struct Result_s *__cdecl HumanAI_SetEventPriorityCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // eax
  struct HumanAI_s *v5; // ecx
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      ptArgList = nullptr;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
      v4 = ptArgList;
    }
    else
    {
      v4 = (struct ArgList_s *)Expression_EvalInt(*ptArgList->aptExpression);
    }
    v5 = HumanAI_ptCurrentHumanAI;
    if ( !*((_BYTE *)&v4[279].isQVM + (_DWORD)HumanAI_ptCurrentHumanAI) )
    {
      *((_BYTE *)&v4[279].isQVM + (_DWORD)HumanAI_ptCurrentHumanAI) = 1;
      v5->anEventPriorityList[v5->nAnimationMinimumDelay++ + 6] = (int)v4;
    }
  }
  Rs.zResult = (char *)&g_zInitialValue;
  Rs.vResult = 1.0;
  Rs.nResult = 1;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:3504  [size]
struct Result_s *__cdecl HumanAI_SetInvulnerabilityCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  char v4; // al
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      ptArgList = nullptr;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
      v4 = (char)ptArgList;
    }
    else
    {
      v4 = Expression_EvalInt(*ptArgList->aptExpression);
    }
    BYTE1(HumanAI_ptCurrentHumanAI->avChannel[6]) = v4;
  }
  Rs.nResult = 1;
  Rs.zResult = (char *)&g_zInitialValue;
  Rs.vResult = 1.0;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:3527  [anchor-mhash]
struct Result_s *__cdecl HumanAI_SetInstantDeathCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  char v4; // al
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      ptArgList = nullptr;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
      v4 = (char)ptArgList;
    }
    else
    {
      v4 = Expression_EvalInt(*ptArgList->aptExpression);
    }
    BYTE2(HumanAI_ptCurrentHumanAI->avChannel[6]) = v4 == 0;
  }
  Rs.nResult = 1;
  Rs.zResult = (char *)&g_zInitialValue;
  Rs.vResult = 1.0;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:3550  [size]
struct Result_s *__cdecl HumanAI_SetDeathAnimationCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      ptArgList = nullptr;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
      v4 = ptArgList;
    }
    else
    {
      v4 = (struct ArgList_s *)Expression_EvalInt(*ptArgList->aptExpression);
    }
    HumanAI_ptCurrentHumanAI->nAnimType = (int)v4;
  }
  Rs.nResult = 1;
  Rs.zResult = (char *)&g_zInitialValue;
  Rs.vResult = 1.0;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:3573  [size]
struct Result_s *__cdecl HumanAI_SetAlarmAccessCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      ptArgList = nullptr;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
      v4 = ptArgList;
    }
    else
    {
      v4 = (struct ArgList_s *)Expression_EvalInt(*ptArgList->aptExpression);
    }
    HumanAI_ptCurrentHumanAI->nAIType = (int)v4;
  }
  Rs.nResult = 1;
  Rs.zResult = (char *)&g_zInitialValue;
  Rs.vResult = 1.0;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:3596  [size]
struct Result_s *__cdecl HumanAI_SetGunnerIDCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      ptArgList = nullptr;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
      v4 = ptArgList;
    }
    else
    {
      v4 = (struct ArgList_s *)Expression_EvalInt(*ptArgList->aptExpression);
    }
    HumanAI_ptCurrentHumanAI->nAnimationEntries = (int)v4;
  }
  Rs.nResult = 1;
  Rs.zResult = (char *)&g_zInitialValue;
  Rs.vResult = 1.0;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:3621  [size]
struct Result_s *__cdecl HumanAI_GetGunnerIDCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  Rs.nResult = HumanAI_ptCurrentHumanAI->nAnimationEntries;
  Rs.vResult = (double)Rs.nResult;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:3642  [anchor-mhash]
struct Result_s *__cdecl HumanAI_GetGunnerStatusCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  unsigned int nAnimationEntries; // eax
  struct QReference_s *v4; // eax
  char *pxObject; // eax
  struct Result_s Rs; // [esp+Ch] [ebp-18h] BYREF

  nAnimationEntries = HumanAI_ptCurrentHumanAI->nAnimationEntries;
  if ( nAnimationEntries < 0x1000
    && (v4 = Level_atLevelQTaskID[nAnimationEntries]) != nullptr
    && (pxObject = (char *)v4->pxObject) != nullptr )
  {
    Rs.nResult = pxObject[592];
    Rs.vResult = (double)Rs.nResult;
  }
  else
  {
    Rs.nResult = 0;
    Rs.vResult = 0.0;
  }
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:3674  [anchor-mhash]
struct Result_s *__cdecl HumanAI_SetScriptIntegerValueCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v7; };
    struct { char igi2_o1[4]; struct Result_s Rs; };
    char igi2_extent[28];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // esi
  int v5; // eax

  v3 = ptArgList;
  if ( ptArgList->nArguments == 2 )
  {
    if ( ptArgList->isQVM )
    {
      ptArgList = nullptr;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
      v4 = ptArgList;
    }
    else
    {
      v4 = (struct ArgList_s *)Expression_EvalInt(*ptArgList->aptExpression);
    }
    if ( v3->isQVM )
    {
      igi2_frame.v7 = 0;
      QVM_EvalArg(&igi2_frame.v7, 4, v3, 1, 1);
      v5 = igi2_frame.v7;
    }
    else
    {
      v5 = Expression_EvalInt(v3->aptExpression[1]);
    }
    *(&HumanAI_ptCurrentHumanAI->nDeadRemoveTimeOut + (_DWORD)v4) = v5;
  }
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  igi2_frame.Rs.vResult = 1.0;
  igi2_frame.Rs.nResult = 1;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:3703  [anchor-mhash]
struct Result_s *__cdecl HumanAI_GetScriptIntegerValueCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->isQVM )
  {
    ptArgList = nullptr;
    QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
    v4 = ptArgList;
  }
  else
  {
    v4 = (struct ArgList_s *)Expression_EvalInt(*ptArgList->aptExpression);
  }
  ptArgList = (struct ArgList_s *)*(&HumanAI_ptCurrentHumanAI->nDeadRemoveTimeOut + (_DWORD)v4);
  Rs.nResult = (int)ptArgList;
  Rs.vResult = (double)(int)ptArgList;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:3724  [anchor-mhash]
struct Result_s *__cdecl HumanAI_SetScriptRealValueCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v7; };
    struct { char igi2_o1[4]; struct Result_s Rs; };
    char igi2_extent[28];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // esi
  double v5; // st7

  v3 = ptArgList;
  if ( ptArgList->nArguments == 2 )
  {
    if ( ptArgList->isQVM )
    {
      ptArgList = nullptr;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
      v4 = ptArgList;
    }
    else
    {
      v4 = (struct ArgList_s *)Expression_EvalInt(*ptArgList->aptExpression);
    }
    if ( v3->isQVM )
    {
      igi2_frame.v7 = 0.0;
      QVM_EvalArg(&igi2_frame.v7, 4, v3, 1, 2);
      v5 = igi2_frame.v7;
    }
    else
    {
      v5 = Expression_EvalFloat((struct QExpression_s *)*((_DWORD *)v3->aptExpression + 1));
    }
    *(double *)&(&HumanAI_ptCurrentHumanAI->tActionStack.ptTail)[2 * (_DWORD)v4] = v5;
  }
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  igi2_frame.Rs.vResult = 1.0;
  igi2_frame.Rs.nResult = 1;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:3753  [anchor-mhash]
struct Result_s *__cdecl HumanAI_GetScriptRealValueCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { __int64 v6; };
    struct { char igi2_o1[8]; struct Result_s Rs; };
    char igi2_extent[32];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // eax

  v3 = ptArgList;
  if ( ptArgList->isQVM )
  {
    ptArgList = nullptr;
    QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
    v4 = ptArgList;
  }
  else
  {
    v4 = (struct ArgList_s *)Expression_EvalInt(*ptArgList->aptExpression);
  }
  igi2_frame.v6 = (__int64)*(double *)&(&HumanAI_ptCurrentHumanAI->tActionStack.ptTail)[2 * (_DWORD)v4];
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  igi2_frame.Rs.nResult = igi2_frame.v6;
  igi2_frame.Rs.vResult = *(double *)&(&HumanAI_ptCurrentHumanAI->tActionStack.ptTail)[2 * (_DWORD)v4];
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:3774  [anchor-mhash]
struct Result_s *__cdecl HumanAI_IsEventBehindCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  double *ptHead; // eax
  struct Node_s *ptNext; // ecx
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  ptHead = (double *)HumanAI_ptCurrentEventStack->ptHead;
  ptNext = HumanAI_ptCurrentEventStack->ptHead->ptNext;
  if ( ptNext )
  {
    while ( HumanAI_ptCurrentHumanAI->tView.tViewOrientation.tZ.vY
          * (ptHead[4] - HumanAI_ptCurrentHumanAI->tView.tViewPosition.vZ)
          + HumanAI_ptCurrentHumanAI->tView.tViewOrientation.tX.vY
          * (ptHead[2] - HumanAI_ptCurrentHumanAI->tView.tViewPosition.vX)
          + HumanAI_ptCurrentHumanAI->tView.tViewOrientation.tY.vY
          * (ptHead[3] - HumanAI_ptCurrentHumanAI->tView.tViewPosition.vY) >= 0.0 )
    {
      ptHead = (double *)ptNext;
      ptNext = ptNext->ptNext;
      if ( !ptNext )
        goto LABEL_4;
    }
    Rs.nResult = 1;
    HIDWORD(Rs.vResult) = 1072693248;
  }
  else
  {
LABEL_4:
    Rs.nResult = 0;
    HIDWORD(Rs.vResult) = 0;
  }
  Rs.zResult = (char *)&g_zInitialValue;
  LODWORD(Rs.vResult) = 0;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:3811  [anchor-strings]
struct Result_s *__cdecl HumanAI_GetEventDistanceCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  double *ptHead; // eax
  double v4; // st7
  double v5; // st6
  double v6; // st5
  double v7; // st7
  double v8; // st6
  double v9; // st5
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  ptHead = (double *)HumanAI_ptCurrentEventStack->ptHead;
  if ( !HumanAI_ptCurrentEventStack->ptHead->ptNext || !ptHead )
  {
    LDebug_Error("No EVENT to distance");
    abort();
  }
  v4 = ptHead[2] - HumanAI_ptCurrentHumanAI->tView.tViewPosition.vX;
  v5 = ptHead[3] - HumanAI_ptCurrentHumanAI->tView.tViewPosition.vY;
  v6 = ptHead[4];
  Rs.zResult = (char *)&g_zInitialValue;
  Rs.nResult = (__int64)sqrt(
                          (v6 - HumanAI_ptCurrentHumanAI->tView.tViewPosition.vZ)
                        * (v6 - HumanAI_ptCurrentHumanAI->tView.tViewPosition.vZ)
                        + v5 * v5
                        + v4 * v4);
  v7 = ptHead[2] - HumanAI_ptCurrentHumanAI->tView.tViewPosition.vX;
  v8 = ptHead[3] - HumanAI_ptCurrentHumanAI->tView.tViewPosition.vY;
  v9 = ptHead[4] - HumanAI_ptCurrentHumanAI->tView.tViewPosition.vZ;
  Rs.vResult = sqrt(v9 * v9 + v8 * v8 + v7 * v7);
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:3838  [anchor-mhash]
struct Result_s *__cdecl HumanAI_SetAnimationIntervalCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { float pxData; };
    struct { char igi2_o1[4]; __int64 v12; };
    struct { char igi2_o2[12]; struct Result_s Rs; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v3; // st7
  double v4; // st7
  struct Game_s *v5; // eax
  struct HumanAI_s *v6; // ecx
  int v7; // edi
  int v8; // edi
  unsigned int v9; // edi

  if ( ptArgList->nArguments == 2 )
  {
    if ( ptArgList->isQVM )
    {
      igi2_frame.pxData = 0.0;
      QVM_EvalArg(&igi2_frame.pxData, 4, ptArgList, 0, 2);
      v3 = igi2_frame.pxData;
    }
    else
    {
      v3 = Expression_EvalFloat(*ptArgList->aptExpression);
    }
    igi2_frame.v12 = (__int64)(30.0 * v3);
    HumanAI_ptCurrentHumanAI->nTargetPosUpdateTimer = igi2_frame.v12;
    if ( ptArgList->isQVM )
    {
      igi2_frame.pxData = 0.0;
      QVM_EvalArg(&igi2_frame.pxData, 4, ptArgList, 1, 2);
      v4 = igi2_frame.pxData;
    }
    else
    {
      v4 = Expression_EvalFloat((struct QExpression_s *)*((_DWORD *)ptArgList->aptExpression + 1));
    }
    v5 = Game_ptGame;
    v6 = HumanAI_ptCurrentHumanAI;
    igi2_frame.Rs.nResult = 2;
    HIDWORD(igi2_frame.Rs.vResult) = 0x40000000;
    igi2_frame.v12 = (__int64)(30.0 * v4);
    HumanAI_ptCurrentHumanAI->nMemberTimer = igi2_frame.v12;
    v7 = (v5->tRunRandomState.anRandom[0] >> 7) ^ v5->tRunRandomState.anRandom[2];
    v5->tRunRandomState.anRandom[2] = v7;
    v8 = v7 ^ v5->tRunRandomState.anRandom[1];
    v5->tRunRandomState.anRandom[1] = v8;
    v9 = v8 + v5->tRunRandomState.anRandom[0];
    v5->tRunRandomState.anRandom[0] = v9;
    *(_DWORD *)&v6->isDetectionInitialzed = v6->nTargetPosUpdateTimer + v9 % (unsigned int)(__int64)(30.0 * v4);
  }
  else
  {
    igi2_frame.Rs.nResult = 1;
    HIDWORD(igi2_frame.Rs.vResult) = 1072693248;
  }
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  LODWORD(igi2_frame.Rs.vResult) = 0;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:3864  [anchor-mhash]
struct Result_s *__cdecl HumanAI_AddAnimationEntryCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  int v3; // eax
  struct HumanAI_s *v4; // ecx
  char *p_isAlarmed; // esi
  _DWORD v7[6]; // [esp+8h] [ebp-18h] BYREF

  if ( ptArgList->nArguments == 2 )
  {
    if ( *(int *)&HumanAI_ptCurrentHumanAI->isAlarmed < 5 )
    {
      v3 = Script_EvalArgInt(ptArgList, 0);
      v4 = HumanAI_ptCurrentHumanAI;
      LODWORD(HumanAI_ptCurrentHumanAI->atAnimationEntries[*(_DWORD *)&HumanAI_ptCurrentHumanAI->isAlarmed + 2].vProbability) = v3;
      p_isAlarmed = &v4->isAlarmed;
      *(double *)&HumanAI_ptCurrentHumanAI->atAnimationEntries[*(_DWORD *)p_isAlarmed + 3].nAnimation = Script_EvalArgFloat(ptArgList, 1);
      ++*(_DWORD *)p_isAlarmed;
    }
    else
    {
      Script_EvalArgInt(ptArgList, 0);
      Script_EvalArgFloat(ptArgList, 1);
    }
    v7[0] = 2;
    v7[3] = 0x40000000;
  }
  else
  {
    v7[0] = 1;
    v7[3] = 1072693248;
  }
  v7[2] = 0;
  v7[4] = &g_zInitialValue;
  qmemcpy(retstr, v7, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:3906  [anchor-mhash]
struct Result_s *__cdecl HumanAI_GetAnimationToPlayCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct HumanAI_s *v3; // esi
  int v4; // ecx
  double v5; // st7
  double *p_nAnimation; // edi
  double *v7; // eax
  int v8; // edx
  struct Game_s *v9; // eax
  unsigned int v10; // edi
  int v11; // edi
  unsigned int v12; // edi
  double v13; // st7
  struct Game_s *v14; // eax
  unsigned int v15; // edx
  int v16; // edx
  unsigned int v17; // edx
  double v18; // st6
  int v19; // edx
  int v20; // ecx
  double v21; // st7
  int vProbability_low; // ecx
  double v24[3]; // [esp+10h] [ebp-18h] BYREF

  v3 = HumanAI_ptCurrentHumanAI;
  v4 = *(_DWORD *)&HumanAI_ptCurrentHumanAI->isAlarmed;
  if ( v4 > 0 )
  {
    v5 = 0.0;
    p_nAnimation = (double *)&HumanAI_ptCurrentHumanAI->atAnimationEntries[3].nAnimation;
    v7 = (double *)&HumanAI_ptCurrentHumanAI->atAnimationEntries[3].nAnimation;
    v8 = *(_DWORD *)&HumanAI_ptCurrentHumanAI->isAlarmed;
    do
    {
      v5 = v5 + *v7;
      v7 += 2;
      --v8;
    }
    while ( v8 );
    if ( v5 >= 0.01 )
    {
      v14 = Game_ptGame;
      v15 = (Game_ptGame->tRunRandomState.anRandom[0] >> 7) ^ Game_ptGame->tRunRandomState.anRandom[2];
      Game_ptGame->tRunRandomState.anRandom[2] = v15;
      v16 = v15 ^ v14->tRunRandomState.anRandom[1];
      v14->tRunRandomState.anRandom[1] = v16;
      v17 = v16 + v14->tRunRandomState.anRandom[0];
      v14->tRunRandomState.anRandom[0] = v17;
      v18 = (double)(unsigned __int16)v17;
      v19 = *(_DWORD *)&v3->isAlarmed;
      v20 = 0;
      v21 = v5 * (v18 * 0.0000152587890625);
      if ( v19 <= 0 )
      {
LABEL_10:
        vProbability_low = LODWORD(v3->atAnimationEntries[v20 + 1].vProbability);
        v13 = (double)vProbability_low;
      }
      else
      {
        while ( 1 )
        {
          v21 = v21 - *p_nAnimation;
          if ( v21 <= 0.0 )
            break;
          ++v20;
          p_nAnimation += 2;
          if ( v20 >= v19 )
            goto LABEL_10;
        }
        vProbability_low = LODWORD(v3->atAnimationEntries[v20 + 2].vProbability);
        v13 = (double)vProbability_low;
      }
      LODWORD(v24[0]) = vProbability_low;
    }
    else
    {
      v9 = Game_ptGame;
      v10 = (Game_ptGame->tRunRandomState.anRandom[0] >> 7) ^ Game_ptGame->tRunRandomState.anRandom[2];
      Game_ptGame->tRunRandomState.anRandom[2] = v10;
      v11 = v10 ^ v9->tRunRandomState.anRandom[1];
      v9->tRunRandomState.anRandom[1] = v11;
      v12 = v11 + v9->tRunRandomState.anRandom[0];
      v9->tRunRandomState.anRandom[0] = v12;
      v13 = (double)SLODWORD(v3->atAnimationEntries[v12 % v4 + 2].vProbability);
      LODWORD(v24[0]) = LODWORD(v3->atAnimationEntries[v12 % v4 + 2].vProbability);
    }
    v24[1] = v13;
  }
  else
  {
    LODWORD(v24[0]) = -1;
    v24[1] = -1.0;
  }
  LODWORD(v24[2]) = &g_zInitialValue;
  qmemcpy(retstr, v24, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:3963  [anchor-strings]
struct Result_s *__cdecl HumanAI_SendResponseCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+0h] [ebp-18h] BYREF

  if ( !HumanAI_ptCurrentEventStack->ptHead->ptNext )
  {
    LDebug_Error("No EVENT to respond");
    abort();
  }
  HumanAI_SendEventNoContextSpecificQTask(
    (struct QTask_s *)HumanAI_ptCurrentEventStack->ptHead[6].ptPrev[1].ptNext,
    6,
    0x20u);
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:3995  [anchor-mhash]
struct Result_s *__cdecl HumanAI_PassEventOnToSquadCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s *v12; };
    struct { char igi2_o1[4]; _DWORD v13[6]; };
    struct { char igi2_o2[28]; struct AISquadEventContext_s ptQTask; };
    char igi2_extent[140];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptParent; // edx
  struct Node_s *v4; // ebx
  struct Node_s *ptNext; // eax
  struct QTask_s *v6; // eax
  float v7; // edx
  float v8; // eax
  struct Node_s *ptPrev; // eax
  struct QTask_s *v11; // edx

  ptParent = HumanAI_ptCurrentHumanAI->tQTask.ptParent;
  igi2_frame.v12 = ptParent->ptParent;
  if ( QTask_IsQTaskTypeDerived(igi2_frame.v12->eQTaskType, AISquad_eQTaskType) == false
    || LOBYTE(ptParent[29].tQTaskRefList.ptHead) )
  {
    goto LABEL_9;
  }
  v4 = HumanAI_ptCurrentEventStack->ptHead->ptNext != nullptr ? HumanAI_ptCurrentEventStack->ptHead : nullptr;
  ptNext = v4[7].ptNext;
  igi2_frame.ptQTask.eEvent = (int)v4[1].ptNext;
  if ( !ptNext )
  {
    ptPrev = v4[6].ptPrev;
    if ( !ptPrev )
      goto LABEL_5;
    v11 = (struct QTask_s *)ptPrev[1].ptNext;
    igi2_frame.ptQTask.ptReferenceQTaskRef = nullptr;
    if ( !v11 || QTask_IsQTaskTypeDerived(v11->eQTaskType, Human_eQTaskType) == false )
      goto LABEL_6;
    v6 = v11;
LABEL_14:
    igi2_frame.ptQTask.ptReferenceQTaskRef = QTask_NewQTaskRef(v6);
    goto LABEL_6;
  }
  v6 = (struct QTask_s *)ptNext[1].ptNext;
  if ( v6 )
    goto LABEL_14;
LABEL_5:
  igi2_frame.ptQTask.ptReferenceQTaskRef = nullptr;
LABEL_6:
  igi2_frame.ptQTask.aptSquadMemberQTaskRef[0] = QTask_NewQTaskRef(&HumanAI_ptCurrentHumanAI->tQTask);
  igi2_frame.ptQTask.nNumSquadMemberQTaskRefs = 1;
  qmemcpy(&igi2_frame.ptQTask.tPosition, &v4[2], sizeof(igi2_frame.ptQTask.tPosition));
  v7 = *(float *)&v4[5].ptPrev;
  v8 = *(float *)&v4[6].ptNext;
  LODWORD(igi2_frame.ptQTask.tDirection.vX) = v4[5].ptNext;
  igi2_frame.ptQTask.tDirection.vY = v7;
  igi2_frame.ptQTask.tDirection.vZ = v8;
  qmemcpy(&igi2_frame.ptQTask.uSpecificData, &v4[8], sizeof(igi2_frame.ptQTask.uSpecificData));
  igi2_frame.ptQTask.nPriority = HumanAI_nHandlerPriority;
  AISquad_ReceiveEvent(igi2_frame.v12, &igi2_frame.ptQTask);
  if ( igi2_frame.ptQTask.ptReferenceQTaskRef )
    QReference_Delete(igi2_frame.ptQTask.ptReferenceQTaskRef, &QTask_tQTaskRefPool);
  QReference_Delete(igi2_frame.ptQTask.aptSquadMemberQTaskRef[0], &QTask_tQTaskRefPool);
LABEL_9:
  igi2_frame.v13[0] = 0;
  igi2_frame.v13[2] = 0;
  igi2_frame.v13[3] = 0;
  igi2_frame.v13[4] = &g_zInitialValue;
  qmemcpy(retstr, igi2_frame.v13, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/humanai.c:4088  [anchor-hash]
void __cdecl HumanAI_RegisterScriptFunctions()
{
  Symbol_Register(
    "AIFunction_SetMinRangeAccuracy",
    HumanAI_SetMinRangeAccuracyCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_SetMedRangeAccuracy",
    HumanAI_SetMedRangeAccuracyCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_SetMaxRangeAccuracy",
    HumanAI_SetMaxRangeAccuracyCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_SetAccuracyMedRange",
    HumanAI_SetAccuracyMedRangeCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_SetAccuracyMaxRange",
    HumanAI_SetAccuracyMaxRangeCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_SetPercentageFiredPerBurst",
    HumanAI_SetPercentageFiredPerBurstCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_SetEvasiveActionProb",
    HumanAI_SetEvasiveActionProbCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_SetMinDelayBetweenFiring",
    HumanAI_SetMinDelayBetweenFiringCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_SetTrackingTimeout",
    HumanAI_SetTrackingTimeoutCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_SetTrackingMaxDistance",
    HumanAI_SetTrackingMaxDistanceCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_SetGrenadeThrowProb",
    HumanAI_SetGrenadeThrowProbCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_SetGrenadeDetonationTimer",
    HumanAI_SetGrenadeDetonationTimerCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_SetGrenadeLandingReactionProb",
    HumanAI_SetGrenadeLandingReactionProbCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_SetCloseCombatDamage",
    HumanAI_SetCloseCombatDamageCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_SetHitPoints",
    HumanAI_SetHitPointsCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_SetHitRecoilThreshold",
    HumanAI_SetHitRecoilThresholdCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_SetCombatViewCone1Alpha",
    HumanAI_SetCombatViewCone1AlphaCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_SetCombatViewCone1Length",
    HumanAI_SetCombatViewCone1LengthCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_SetCombatViewCone2Alpha",
    HumanAI_SetCombatViewCone2AlphaCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_SetCombatViewCone2Length",
    HumanAI_SetCombatViewCone2LengthCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_SetIdleViewCone1Alpha",
    HumanAI_SetIdleViewCone1AlphaCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_SetIdleViewCone1Length",
    HumanAI_SetIdleViewCone1LengthCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_SetIdleViewCone2Alpha",
    HumanAI_SetIdleViewCone2AlphaCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_SetIdleViewCone2Length",
    HumanAI_SetIdleViewCone2LengthCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_SetIdleAnimationFrequency",
    HumanAI_SetIdleAnimationFrequencyCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_SetInvestigateViewCone1Alpha",
    HumanAI_SetInvestigateViewCone1AlphaCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_SetInvestigateViewCone1Length",
    HumanAI_SetInvestigateViewCone1LengthCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_SetInvestigateViewCone2Alpha",
    HumanAI_SetInvestigateViewCone2AlphaCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_SetInvestigateViewCone2Length",
    HumanAI_SetInvestigateViewCone2LengthCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_SetInvestigateShoutFrequency",
    HumanAI_SetInvestigateShoutFrequencyCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_SetAnimSpeedFactor",
    HumanAI_SetAnimSpeedFactorCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_SetHearingRangeFactor",
    HumanAI_SetHearingRangeFactorCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_SetSideKick",
    HumanAI_SetSideKickCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_UseCombatView",
    HumanAI_UseCombatViewCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_UseIdleView",
    HumanAI_UseIdleViewCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_HasSeenDeadFriendlyBefore",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))HumanAI_HasSeenDeadFriendlyBeforeCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_SetStandActionAnimation",
    HumanAI_SetStandActionAnimationCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_HasTarget",
    HumanAI_HasTargetCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_LimitViewRange",
    HumanAI_LimitViewRangeCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIAction_DelayedEventPassOn",
    HumanAI_DelayedEventPassOnCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIAction_Patrol",
    HumanAI_PatrolCB,
    nullptr,
    3,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIAction_Dead",
    HumanAI_DeadCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIAction_FallFlat",
    HumanAI_FallFlatCB,
    nullptr,
    2,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIAction_Activate",
    HumanAI_ActivateCB,
    nullptr,
    3,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIAction_WalkToNode",
    HumanAI_WalkToNodeCB,
    nullptr,
    2,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIAction_RunToNode",
    HumanAI_RunToNodeCB,
    nullptr,
    2,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIAction_FireAtNode",
    HumanAI_FireAtNodeCB,
    nullptr,
    5,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIAction_FireAtTask",
    HumanAI_FireAtTaskCB,
    nullptr,
    5,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIAction_PlayAnimation",
    HumanAI_PlayAnimationCB,
    nullptr,
    2,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIAction_PlaySound",
    HumanAI_PlaySoundCB,
    nullptr,
    3,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIAction_MoveToEvent",
    HumanAI_MoveToEventCB,
    nullptr,
    2,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIAction_LookAtEvent",
    HumanAI_LookAtEventCB,
    nullptr,
    2,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIAction_LookInApproximateEventDirection",
    HumanAI_LookInApproxEventDirectionCB,
    nullptr,
    3,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIAction_Stunned",
    HumanAI_StunnedCB,
    nullptr,
    2,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIAction_KickGrenade",
    HumanAI_KickGrenadeCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIAction_RunPanicking",
    HumanAI_RunPanickingCB,
    nullptr,
    2,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIAction_Idle",
    HumanAI_IdleCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIAction_CombatIdle",
    HumanAI_CombatIdleCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIAction_LookAround",
    HumanAI_LookAroundCB,
    nullptr,
    2,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIAction_CallForBackup",
    HumanAI_CallForBackupCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIAction_EnemyDetection",
    HumanAI_EnemyDetectionCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIAction_LookAtNode",
    HumanAI_LookAtNodeCB,
    nullptr,
    2,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIAction_FriendlyDetection",
    HumanAI_DeadFriendlyDetectionCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIAction_RunToCover",
    HumanAI_RunToCoverCB,
    nullptr,
    2,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIAction_Wait",
    HumanAI_WaitCB,
    nullptr,
    2,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIAction_OffensiveCombat",
    HumanAI_OffensiveCombatCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIAction_DefensiveCombat",
    HumanAI_DefensiveCombatCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_DefaultHandler",
    HumanAI_DefaultHandlerCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_RemoveAlarmActions",
    HumanAI_RemoveAlarmActionsCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_SetViewLength",
    HumanAI_SetViewLengthCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_SetViewAlpha",
    HumanAI_SetViewAlphaCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_SetViewGamma",
    HumanAI_SetViewGammaCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_SetSecondaryViewLength",
    HumanAI_SetSecondaryViewLengthCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_SetSecondaryViewAlpha",
    HumanAI_SetSecondaryViewAlphaCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_SetSecondaryViewGamma",
    HumanAI_SetSecondaryViewGammaCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_SetEventPriority",
    HumanAI_SetEventPriorityCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_SetInvulnerability",
    HumanAI_SetInvulnerabilityCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_SetInstantDeath",
    HumanAI_SetInstantDeathCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_SetDeathAnimation",
    HumanAI_SetDeathAnimationCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_SetAlarmAccess",
    HumanAI_SetAlarmAccessCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_SetGunnerID",
    HumanAI_SetGunnerIDCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_SetScriptIntegerValue",
    HumanAI_SetScriptIntegerValueCB,
    nullptr,
    2,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_SetScriptRealValue",
    HumanAI_SetScriptRealValueCB,
    nullptr,
    2,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_GetGunnerID",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))HumanAI_GetGunnerIDCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_GetGunnerStatus",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))HumanAI_GetGunnerStatusCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_GetScriptIntegerValue",
    HumanAI_GetScriptIntegerValueCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_GetCurrentEventType",
    HumanAI_GetCurrentEventTypeCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_IsEventBehind",
    HumanAI_IsEventBehindCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_GetScriptRealValue",
    HumanAI_GetScriptRealValueCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_FLOAT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_GetRandomValue",
    HumanAI_GetRandomValueCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_FLOAT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_GetEventDistance",
    HumanAI_GetEventDistanceCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_FLOAT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_SetAnimationInterval",
    HumanAI_SetAnimationIntervalCB,
    nullptr,
    2,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_AddAnimationEntry",
    HumanAI_AddAnimationEntryCB,
    nullptr,
    2,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_GetAnimationToPlay",
    HumanAI_GetAnimationToPlayCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_SendResponse",
    HumanAI_SendResponseCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIFunction_PassEventOnToSquad",
    HumanAI_PassEventOnToSquadCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}

// source: j/0/humanai/humanai.c:4215  [anchor-hash]
void __cdecl HumanAI_RemoveScriptFunctions()
{
  Symbol_Remove("AIFunction_SetMinRangeAccuracy");
  Symbol_Remove("AIFunction_SetMedRangeAccuracy");
  Symbol_Remove("AIFunction_SetMaxRangeAccuracy");
  Symbol_Remove("AIFunction_SetAccuracyMedRange");
  Symbol_Remove("AIFunction_SetAccuracyMaxRange");
  Symbol_Remove("AIFunction_SetPercentageFiredPerBurst");
  Symbol_Remove("AIFunction_SetEvasiveActionProb");
  Symbol_Remove("AIFunction_SetMinDelayBetweenFiring");
  Symbol_Remove("AIFunction_SetTrackingTimeout");
  Symbol_Remove("AIFunction_SetTrackingMaxDistance");
  Symbol_Remove("AIFunction_SetGrenadeThrowProb");
  Symbol_Remove("AIFunction_SetGrenadeDetonationTimer");
  Symbol_Remove("AIFunction_SetGrenadeLandingReactionProb");
  Symbol_Remove("AIFunction_SetCloseCombatDamage");
  Symbol_Remove("AIFunction_SetHitPoints");
  Symbol_Remove("AIFunction_SetHitRecoilThreshold");
  Symbol_Remove("AIFunction_SetCombatViewCone1Alpha");
  Symbol_Remove("AIFunction_SetCombatViewCone1Length");
  Symbol_Remove("AIFunction_SetCombatViewCone2Alpha");
  Symbol_Remove("AIFunction_SetCombatViewCone2Length");
  Symbol_Remove("AIFunction_SetIdleViewCone1Alpha");
  Symbol_Remove("AIFunction_SetIdleViewCone1Length");
  Symbol_Remove("AIFunction_SetIdleViewCone2Alpha");
  Symbol_Remove("AIFunction_SetIdleViewCone2Length");
  Symbol_Remove("AIFunction_SetIdleAnimationFrequency");
  Symbol_Remove("AIFunction_SetInvestigateViewCone1Alpha");
  Symbol_Remove("AIFunction_SetInvestigateViewCone1Length");
  Symbol_Remove("AIFunction_SetInvestigateViewCone2Alpha");
  Symbol_Remove("AIFunction_SetInvestigateViewCone2Length");
  Symbol_Remove("AIFunction_SetInvestigateShoutFrequency");
  Symbol_Remove("AIFunction_SetAnimSpeedFactor");
  Symbol_Remove("AIFunction_SetHearingRangeFactor");
  Symbol_Remove("AIFunction_SetSideKick");
  Symbol_Remove("AIFunction_UseCombatView");
  Symbol_Remove("AIFunction_UseIdleView");
  Symbol_Remove("AIFunction_HasSeenDeadFriendlyBefore");
  Symbol_Remove("AIFunction_SetStandActionAnimation");
  Symbol_Remove("AIFunction_HasTarget");
  Symbol_Remove("AIFunction_LimitViewRange");
  Symbol_Remove("AIAction_DelayedEventPassOn");
  Symbol_Remove("AIAction_Patrol");
  Symbol_Remove("AIAction_Dead");
  Symbol_Remove("AIAction_FallFlat");
  Symbol_Remove("AIAction_Activate");
  Symbol_Remove("AIAction_WalkToNode");
  Symbol_Remove("AIAction_RunToNode");
  Symbol_Remove("AIAction_FireAtNode");
  Symbol_Remove("AIAction_FireAtTask");
  Symbol_Remove("AIAction_PlayAnimation");
  Symbol_Remove("AIAction_MoveToEvent");
  Symbol_Remove("AIAction_LookAtEvent");
  Symbol_Remove("AIAction_LookInApproximateEventDirection");
  Symbol_Remove("AIAction_Stunned");
  Symbol_Remove("AIAction_KickGrenade");
  Symbol_Remove("AIAction_RunPanicking");
  Symbol_Remove("AIAction_Idle");
  Symbol_Remove("AIAction_CombatIdle");
  Symbol_Remove("AIAction_LookAround");
  Symbol_Remove("AIAction_CallForBackup");
  Symbol_Remove("AIAction_EnemyDetection");
  Symbol_Remove("AIAction_LookAtNode");
  Symbol_Remove("AIAction_FriendlyDetection");
  Symbol_Remove("AIAction_RunToCover");
  Symbol_Remove("AIAction_Wait");
  Symbol_Remove("AIAction_OffensiveCombat");
  Symbol_Remove("AIAction_DefensiveCombat");
  Symbol_Remove("AIFunction_RemoveAlarmActions");
  Symbol_Remove("AIFunction_SetViewLength");
  Symbol_Remove("AIFunction_SetViewAlpha");
  Symbol_Remove("AIFunction_SetViewGamma");
  Symbol_Remove("AIFunction_SetSecondaryViewLength");
  Symbol_Remove("AIFunction_SetSecondaryViewAlpha");
  Symbol_Remove("AIFunction_SetSecondaryViewGamma");
  Symbol_Remove("AIFunction_SetEventPriority");
  Symbol_Remove("AIFunction_SetInvulnerability");
  Symbol_Remove("AIFunction_SetInstantDeath");
  Symbol_Remove("AIFunction_SetDeathAnimation");
  Symbol_Remove("AIFunction_SetAlarmAccess");
  Symbol_Remove("AIFunction_SetGunnerID");
  Symbol_Remove("AIFunction_GetGunnerID");
  Symbol_Remove("AIFunction_GetGunnerStatus");
  Symbol_Remove("AIFunction_SetScriptIntegerValue");
  Symbol_Remove("AIFunction_SetScriptRealValue");
  Symbol_Remove("AIFunction_GetScriptIntegerValue");
  Symbol_Remove("AIFunction_GetScriptRealValue");
  Symbol_Remove("AIFunction_GetCurrentEventType");
  Symbol_Remove("AIFunction_GetRandomValue");
  Symbol_Remove("AIFunction_DefaultHandler");
  Symbol_Remove("AIAction_PlaySound");
  Symbol_Remove("AIFunction_IsEventBehind");
  Symbol_Remove("AIFunction_GetEventDistance");
  Symbol_Remove("AIFunction_SetAnimationInterval");
  Symbol_Remove("AIFunction_AddAnimationEntry");
  Symbol_Remove("AIFunction_GetAnimationToPlay");
  Symbol_Remove("AIFunction_SendResponse");
  Symbol_Remove("AIFunction_PassEventOnToSquad");
}

// source: j/0/humanai/humanai.c:4346  [anchor-hash]
void __cdecl HumanAI_RegisterConstants()
{
  int i; // esi
  int j; // esi

  Symbol_Register(
    "AIEVENT_CREATE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    nullptr,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIEVENT_DELETE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)1,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIEVENT_DEAD",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)2,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIEVENT_ANIMATION",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)3,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIEVENT_IDLE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)4,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIEVENT_ALERT",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)5,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIEVENT_ALERT_RESPONSE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)6,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIEVENT_ALARMON",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)7,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIEVENT_ALARMOFF",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)8,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIEVENT_WALK",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)9,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIEVENT_GROUNDIMPACT",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0xA,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIEVENT_DOOR",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0xB,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIEVENT_FENCE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0xC,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIEVENT_LADDER",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0xD,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIEVENT_TAKINGDAMAGE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0xE,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIEVENT_GUNSHOT",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0xF,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIEVENT_GRENADETHROWN",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0x10,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIEVENT_GRENADELAND",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0x11,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIEVENT_FLASHBANG",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0x12,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIEVENT_GUNSHOTMISS",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0x13,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIEVENT_EXPLOSION",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0x14,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIEVENT_ENEMYDETECTION",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0x15,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIEVENT_ENEMYDETECTION_NO_LOF",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0x21,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIEVENT_FRIENDLYDETECTION",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0x16,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIEVENT_FRIENDLY_GUNSHOT",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0x17,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIEVENT_DEATH_CRY",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0x18,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIEVENT_BACKUP_REQUEST",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0x19,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIEVENT_SEENSOMETHING",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0x1A,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIEVENT_LOSTSIGHTOFENEMY",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0x1B,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIEVENT_SQUADCOMMAND",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0x1C,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIEVENT_INQUIRETIMEOUT",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0x1D,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIEVENT_SQUADCOMBATIDLE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0x1E,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIEVENT_WOUNDED_CRY",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0x1F,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIEVENT_PATROLCOMMANDPROCESSED",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0x20,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIEVENT_FRIENDLY_DYING",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0x22,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIEVENT_DESTROYED_CAMERA",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0x23,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIEVENT_FRIENDLY_DAMAGE_SEEN",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0x24,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIEVENT_GRENADESHOUT",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0x25,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIEVENT_DANGERSTATETIMEOUT",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0x26,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIEVENT_VISUAL_GUNSHOT",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0x27,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIEVENT_DONELOOKING",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0x28,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIEVENT_DISTRESSCALL",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0x29,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIEVENT_BULLETIMPACT",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0x2A,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIEVENT_SEARCHOVER",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0x2B,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIEVENT_HANDLEWEAPON",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0x2C,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIEVENT_CAMERAALARMUPDATE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0x2D,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIEVENT_REACTTOSUSPICION",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0x2E,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIACTIONFLAG_NONE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    nullptr,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIACTIONFLAG_PUSHABLE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)1,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "HUMANAI_DETECTIONEVENT_GUNSHOT_SILENCED_RANGE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0x5000,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "HUMANAI_DETECTIONEVENT_GUNSHOT_PISTOL_RANGE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0x32000,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "HUMANAI_DETECTIONEVENT_GUNSHOT_RANGE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0x64000,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "HUMANAI_DETECTIONEVENT_CANNON_RANGE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0x64000,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  for ( i = 0; i < 6; ++i )
    Symbol_Register(
      HumanAI_azAITypeStrings[i],
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
      (void *)i,
      4,
      QSCRIPT_SYMBOLCLASS_CONSTANT,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  for ( j = 0; j < 7; ++j )
    Symbol_Register(
      HumanAI_azAnimTypeStrings[j],
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
      (void *)j,
      4,
      QSCRIPT_SYMBOLCLASS_CONSTANT,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "HUMANAI_ANIMTYPE_PRIBOY",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)1,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "HUMANAI_ANIMTYPE_SOLDIER",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)2,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIALARMACCESS_BEFORECOMBAT",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    nullptr,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIALARMACCESS_AFTERCOMBAT",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)1,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AILOOKAROUND_PATTERN_180_CLOCKWISE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    nullptr,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AILOOKAROUND_PATTERN_90_CLOCKWISE_QUICK",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)1,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AILOOKAROUND_PATTERN_180_COUNTERCLOCKWISE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)3,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AILOOKAROUND_PATTERN_360_SLOW",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)4,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AILOOKAROUND_PATTERN_360_FAST",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)5,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}

// source: j/0/humanai/humanai.c:4444  [anchor-hash]
void __cdecl HumanAI_RemoveConstants()
{
  char **v0; // esi

  Symbol_Remove("AIEVENT_CREATE");
  Symbol_Remove("AIEVENT_DELETE");
  Symbol_Remove("AIEVENT_DEAD");
  Symbol_Remove("AIEVENT_ANIMATION");
  Symbol_Remove("AIEVENT_IDLE");
  Symbol_Remove("AIEVENT_ALERT");
  Symbol_Remove("AIEVENT_ALERT_RESPONSE");
  Symbol_Remove("AIEVENT_ALARMON");
  Symbol_Remove("AIEVENT_ALARMOFF");
  Symbol_Remove("AIEVENT_WALK");
  Symbol_Remove("AIEVENT_GROUNDIMPACT");
  Symbol_Remove("AIEVENT_DOOR");
  Symbol_Remove("AIEVENT_FENCE");
  Symbol_Remove("AIEVENT_LADDER");
  Symbol_Remove("AIEVENT_TAKINGDAMAGE");
  Symbol_Remove("AIEVENT_GUNSHOT");
  Symbol_Remove("AIEVENT_GRENADETHROWN");
  Symbol_Remove("AIEVENT_GRENADELAND");
  Symbol_Remove("AIEVENT_FLASHBANG");
  Symbol_Remove("AIEVENT_GUNSHOTMISS");
  Symbol_Remove("AIEVENT_EXPLOSION");
  Symbol_Remove("AIEVENT_ENEMYDETECTION");
  Symbol_Remove("AIEVENT_ENEMYDETECTION_NO_LOF");
  Symbol_Remove("AIEVENT_FRIENDLYDETECTION");
  Symbol_Remove("AIEVENT_FRIENDLY_GUNSHOT");
  Symbol_Remove("AIEVENT_DEATH_CRY");
  Symbol_Remove("AIEVENT_BACKUP_REQUEST");
  Symbol_Remove("AIEVENT_SEENSOMETHING");
  Symbol_Remove("AIEVENT_LOSTSIGHTOFENEMY");
  Symbol_Remove("AIEVENT_SQUADCOMMAND");
  Symbol_Remove("AIEVENT_INQUIRETIMEOUT");
  Symbol_Remove("AIEVENT_SQUADCOMBATIDLE");
  Symbol_Remove("AIEVENT_WOUNDED_CRY");
  Symbol_Remove("AIEVENT_PATROLCOMMANDPROCESSED");
  Symbol_Remove("AIEVENT_FRIENDLY_DYING");
  Symbol_Remove("AIEVENT_DESTROYED_CAMERA");
  Symbol_Remove("AIEVENT_FRIENDLY_DAMAGE_SEEN");
  Symbol_Remove("AIEVENT_GRENADESHOUT");
  Symbol_Remove("AIEVENT_DANGERSTATETIMEOUT");
  Symbol_Remove("AIEVENT_VISUAL_GUNSHOT");
  Symbol_Remove("AIEVENT_DONELOOKING");
  Symbol_Remove("AIEVENT_DISTRESSCALL");
  Symbol_Remove("AIEVENT_BULLETIMPACT");
  Symbol_Remove("AIEVENT_SEARCHOVER");
  Symbol_Remove("AIEVENT_HANDLEWEAPON");
  Symbol_Remove("AIEVENT_CAMERAALARMUPDATE");
  Symbol_Remove("AIEVENT_REACTTOSUSPICION");
  Symbol_Remove("AIACTIONFLAG_NONE");
  Symbol_Remove("AIACTIONFLAG_PUSHABLE");
  Symbol_Remove("HUMANAI_DETECTIONEVENT_GUNSHOT_SILENCED_RANGE");
  Symbol_Remove("HUMANAI_DETECTIONEVENT_GUNSHOT_PISTOL_RANGE");
  Symbol_Remove("HUMANAI_DETECTIONEVENT_GUNSHOT_RANGE");
  Symbol_Remove("HUMANAI_DETECTIONEVENT_CANNON_RANGE");
  v0 = HumanAI_azAITypeStrings;
  do
    Symbol_Remove(*v0++);
  while ( (int)v0 < 7050968 );
  Symbol_Remove("HUMANAI_ANIMTYPE_PRIBOY");
  Symbol_Remove("HUMANAI_ANIMTYPE_SOLDIER");
  Symbol_Remove("AIALARMACCESS_BEFORECOMBAT");
  Symbol_Remove("AIALARMACCESS_AFTERCOMBAT");
  Symbol_Remove("AILOOKAROUND_PATTERN_180_CLOCKWISE");
  Symbol_Remove("AILOOKAROUND_PATTERN_90_CLOCKWISE_QUICK");
  Symbol_Remove("AILOOKAROUND_PATTERN_180_COUNTERCLOCKWISE");
  Symbol_Remove("AILOOKAROUND_PATTERN_360_SLOW");
  Symbol_Remove("AILOOKAROUND_PATTERN_360_FAST");
}

// source: j/0/humanai/humanai.c:4536  [anchor-callee]
struct HumanAIEvent_t *__cdecl HumanAI_CreateEvent(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIEventContext_t *ptContext)
{
  struct HumanAIEvent_t *v2; // ebx
  struct real64x3_t *ptPosition; // esi
  struct QTask_s *ptHumanOriginatorQTask; // eax
  struct QTask_s *ptReferenceQTask; // eax

  v2 = (struct HumanAIEvent_t *)ptHumanAI->anEventPriorityList[1];
  if ( !v2->tNode.ptNext )
    return nullptr;
  Node_Remove(v2);
  v2->tNode.ptPrev = nullptr;
  v2->tNode.ptNext = nullptr;
  v2->eEvent = ptContext->eEvent;
  v2->eTeam = ptContext->eTeam;
  ptPosition = ptContext->ptPosition;
  if ( ptPosition )
    qmemcpy(&v2->tPosition, ptPosition, sizeof(v2->tPosition));
  ptHumanOriginatorQTask = ptContext->ptHumanOriginatorQTask;
  if ( ptHumanOriginatorQTask )
    v2->ptHumanOriginatorQTaskRef = QTask_NewQTaskRef(ptHumanOriginatorQTask);
  else
    v2->ptHumanOriginatorQTaskRef = nullptr;
  ptReferenceQTask = ptContext->ptReferenceQTask;
  if ( ptReferenceQTask )
    v2->ptReferenceQTaskRef = QTask_NewQTaskRef(ptReferenceQTask);
  else
    v2->ptReferenceQTaskRef = nullptr;
  qmemcpy(&v2->uEventSpecificData, &ptContext->uEventSpecificData, sizeof(v2->uEventSpecificData));
  ++ptHumanAI->nAnimationRandomDelay;
  return v2;
}

// source: j/0/humanai/humanai.c:4604  [anchor-hash]
void __cdecl HumanAI_RemoveEvent(struct HumanAI_s *ptHumanAI, struct HumanAIEvent_t *ptEvent)
{
  struct QReference_s *ptHumanOriginatorQTaskRef; // eax
  struct QReference_s *ptReferenceQTaskRef; // eax

  Node_Remove(ptEvent);
  ptHumanOriginatorQTaskRef = ptEvent->ptHumanOriginatorQTaskRef;
  if ( ptHumanOriginatorQTaskRef )
  {
    QReference_Delete(ptHumanOriginatorQTaskRef, &QTask_tQTaskRefPool);
    ptEvent->ptHumanOriginatorQTaskRef = nullptr;
  }
  ptReferenceQTaskRef = ptEvent->ptReferenceQTaskRef;
  if ( ptReferenceQTaskRef )
  {
    QReference_Delete(ptReferenceQTaskRef, &QTask_tQTaskRefPool);
    ptEvent->ptReferenceQTaskRef = nullptr;
  }
  ptEvent->tNode.ptPrev = nullptr;
  ptEvent->tNode.ptNext = nullptr;
  List_AddTail(ptEvent, (int)&ptHumanAI->anEventPriorityList[1]);
  --ptHumanAI->nAnimationRandomDelay;
}

// source: j/0/humanai/humanai.c:4642  [anchor-callee]
void __cdecl HumanAI_RemoveEvents(struct HumanAI_s *ptHumanAI)
{
  struct Node_s *ptHead; // esi
  struct Node_s *i; // edi
  struct MemPoolFreeItem_s *ptNext; // eax
  struct MemPoolFreeItem_s *ptPrev; // eax
  bool v5; // zf
  struct List_s *atEventTypeStacks; // [esp+10h] [ebp-8h]
  int v7; // [esp+14h] [ebp-4h]

  atEventTypeStacks = ptHumanAI->atEventTypeStacks;
  v7 = 47;
  do
  {
    ptHead = atEventTypeStacks->ptHead;
    for ( i = atEventTypeStacks->ptHead->ptNext; i; i = i->ptNext )
    {
      Node_Remove(ptHead);
      ptNext = (struct MemPoolFreeItem_s *)ptHead[7].ptNext;
      if ( ptNext )
      {
        if ( ptNext->ptNext )
          ptNext = (struct MemPoolFreeItem_s *)Node_Remove(ptNext);
        --QTask_tQTaskRefPool.nAllocatedBlocks;
        ptNext->ptNext = QTask_tQTaskRefPool.tMemPoolFreeList.ptHead;
        QTask_tQTaskRefPool.tMemPoolFreeList.ptHead = ptNext;
        ptHead[7].ptNext = nullptr;
      }
      ptPrev = (struct MemPoolFreeItem_s *)ptHead[6].ptPrev;
      if ( ptPrev )
      {
        if ( ptPrev->ptNext )
          ptPrev = (struct MemPoolFreeItem_s *)Node_Remove(ptPrev);
        --QTask_tQTaskRefPool.nAllocatedBlocks;
        ptPrev->ptNext = QTask_tQTaskRefPool.tMemPoolFreeList.ptHead;
        QTask_tQTaskRefPool.tMemPoolFreeList.ptHead = ptPrev;
        ptHead[6].ptPrev = nullptr;
      }
      ptHead->ptPrev = nullptr;
      ptHead->ptNext = nullptr;
      List_AddTail(ptHead, (int)&ptHumanAI->anEventPriorityList[1]);
      --ptHumanAI->nAnimationRandomDelay;
      ptHead = i;
    }
    v5 = v7 == 1;
    ++atEventTypeStacks;
    --v7;
  }
  while ( !v5 );
}

// source: j/0/humanai/humanai.c:4675  [anchor-mhash]
void __cdecl HumanAI_RemoveEventsOfType(struct HumanAI_s *ptHumanAI, int eEvent)
{
  struct Node_s *ptHead; // esi
  struct Node_s *i; // edi
  struct MemPoolFreeItem_s *ptNext; // eax
  struct MemPoolFreeItem_s *ptPrev; // eax
  bool v6; // zf
  struct List_s *atEventTypeStacks; // [esp+10h] [ebp-8h]
  int v8; // [esp+14h] [ebp-4h]

  atEventTypeStacks = ptHumanAI->atEventTypeStacks;
  v8 = 47;
  do
  {
    ptHead = atEventTypeStacks->ptHead;
    for ( i = atEventTypeStacks->ptHead->ptNext; i; i = i->ptNext )
    {
      if ( ptHead[1].ptNext == (struct Node_s *)eEvent )
      {
        Node_Remove(ptHead);
        ptNext = (struct MemPoolFreeItem_s *)ptHead[7].ptNext;
        if ( ptNext )
        {
          if ( ptNext->ptNext )
            ptNext = (struct MemPoolFreeItem_s *)Node_Remove(ptNext);
          --QTask_tQTaskRefPool.nAllocatedBlocks;
          ptNext->ptNext = QTask_tQTaskRefPool.tMemPoolFreeList.ptHead;
          QTask_tQTaskRefPool.tMemPoolFreeList.ptHead = ptNext;
          ptHead[7].ptNext = nullptr;
        }
        ptPrev = (struct MemPoolFreeItem_s *)ptHead[6].ptPrev;
        if ( ptPrev )
        {
          if ( ptPrev->ptNext )
            ptPrev = (struct MemPoolFreeItem_s *)Node_Remove(ptPrev);
          --QTask_tQTaskRefPool.nAllocatedBlocks;
          ptPrev->ptNext = QTask_tQTaskRefPool.tMemPoolFreeList.ptHead;
          QTask_tQTaskRefPool.tMemPoolFreeList.ptHead = ptPrev;
          ptHead[6].ptPrev = nullptr;
        }
        ptHead->ptPrev = nullptr;
        ptHead->ptNext = nullptr;
        List_AddTail(ptHead, (int)&ptHumanAI->anEventPriorityList[1]);
        --ptHumanAI->nAnimationRandomDelay;
      }
      ptHead = i;
    }
    v6 = v8 == 1;
    ++atEventTypeStacks;
    --v8;
  }
  while ( !v6 );
}

// source: j/0/humanai/humanai.c:4711  [anchor-callee]
char __cdecl HumanAI_RunScriptEvent(struct HumanAI_s *ptHumanAI, int nEventNumber, int nPriority)
{
  struct List_s *v3; // edx
  struct Script_s *v4; // eax
  struct Node_s *ptNext; // esi
  struct Node_s *v6; // eax
  struct Node_s *ptHead; // eax
  struct HumanAIActionStackItem_s *v9; // eax
  struct List_s ptActionStackList; // [esp+Ch] [ebp-Ch] BYREF

  ptActionStackList.ptHead = (struct Node_s *)&ptActionStackList.ptMiddle;
  ptActionStackList.ptTail = (struct Node_s *)&ptActionStackList;
  HumanAI_ptLocalActionList = &ptActionStackList;
  v3 = &ptHumanAI->atEventTypeStacks[nEventNumber];
  HumanAI_ptCurrentHumanAI = ptHumanAI;
  v4 = *(struct Script_s **)&ptHumanAI->zAIType[36];
  ptActionStackList.ptMiddle = nullptr;
  HumanAI_ptCurrentEventStack = v3;
  HumanAI_nHandlerPriority = nPriority;
  Script_Execute(v4);
  ptNext = ptActionStackList.ptHead->ptNext;
  v6 = ptActionStackList.ptHead->ptNext != nullptr ? ptActionStackList.ptHead : nullptr;
  if ( v6 == (ptActionStackList.ptTail->ptPrev != nullptr ? ptActionStackList.ptTail : nullptr) )
  {
    if ( v6 && (ptHead = ptActionStackList.ptHead, ptNext) )
    {
      do
      {
        v9 = (struct HumanAIActionStackItem_s *)Node_Remove(ptHead);
        HumanAI_PushActionStackItem(HumanAI_ptCurrentHumanAI, v9);
        ptHead = ptNext;
        ptNext = ptNext->ptNext;
      }
      while ( ptNext );
      return 1;
    }
    else
    {
      return 0;
    }
  }
  else
  {
    HumanAI_PushActionStackList(HumanAI_ptCurrentHumanAI, &ptActionStackList);
    return 1;
  }
}

// source: j/0/humanai/humanai.c:4786  [anchor-callee]
void __cdecl HumanAI_RunScript(struct HumanAI_s *ptHumanAI)
{
  void (__cdecl *pfRunCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // ecx
  int v2; // eax
  int v3; // ebx
  struct Node_s *ptHead; // ecx
  struct Node_s *v5; // esi
  struct Node_s *ptNext; // ebp
  struct MemPoolFreeItem_s *v7; // eax
  struct MemPoolFreeItem_s *ptPrev; // eax
  char isRun; // [esp+3h] [ebp-Dh]
  int iC; // [esp+4h] [ebp-Ch]
  int *v11; // [esp+8h] [ebp-8h]
  int iEventPriority; // [esp+Ch] [ebp-4h]

  iEventPriority = 47;
  isRun = 0;
  if ( *(_DWORD *)&ptHumanAI->zAIType[36] )
  {
    pfRunCallback = ptHumanAI->atActionStackItemList[0].pfRunCallback;
    if ( *(_DWORD *)pfRunCallback )
      iEventPriority = *(*(_DWORD *)pfRunCallback != 0 ? (_DWORD *)((char *)pfRunCallback + 12) : (_DWORD *)12);
    v2 = 0;
    iC = 0;
    if ( ptHumanAI->nAnimationMinimumDelay > 0 )
    {
      v11 = &ptHumanAI->anEventPriorityList[6];
      do
      {
        v3 = *v11;
        if ( v2 < iEventPriority )
        {
          ptHead = ptHumanAI->atEventTypeStacks[v3].ptHead;
          if ( ptHead->ptNext )
          {
            if ( ptHead && !isRun )
            {
              isRun = HumanAI_RunScriptEvent(ptHumanAI, v3, v2);
              v2 = iC;
            }
          }
        }
        v5 = ptHumanAI->atEventTypeStacks[v3].ptHead;
        ptHumanAI->anEventCountLastTick[v3 + 8] = 0;
        ptNext = v5->ptNext;
        if ( v5->ptNext )
        {
          do
          {
            Node_Remove(v5);
            v7 = (struct MemPoolFreeItem_s *)v5[7].ptNext;
            if ( v7 )
            {
              if ( v7->ptNext )
                v7 = (struct MemPoolFreeItem_s *)Node_Remove(v7);
              --QTask_tQTaskRefPool.nAllocatedBlocks;
              v7->ptNext = QTask_tQTaskRefPool.tMemPoolFreeList.ptHead;
              QTask_tQTaskRefPool.tMemPoolFreeList.ptHead = v7;
              v5[7].ptNext = nullptr;
            }
            ptPrev = (struct MemPoolFreeItem_s *)v5[6].ptPrev;
            if ( ptPrev )
            {
              if ( ptPrev->ptNext )
                ptPrev = (struct MemPoolFreeItem_s *)Node_Remove(ptPrev);
              --QTask_tQTaskRefPool.nAllocatedBlocks;
              ptPrev->ptNext = QTask_tQTaskRefPool.tMemPoolFreeList.ptHead;
              QTask_tQTaskRefPool.tMemPoolFreeList.ptHead = ptPrev;
              v5[6].ptPrev = nullptr;
            }
            v5->ptPrev = nullptr;
            v5->ptNext = nullptr;
            List_AddTail(v5, (int)&ptHumanAI->anEventPriorityList[1]);
            --ptHumanAI->nAnimationRandomDelay;
            ++ptHumanAI->anEventCountLastTick[v3 + 8];
            v5 = ptNext;
            ptNext = ptNext->ptNext;
          }
          while ( ptNext );
          v2 = iC;
        }
        iC = ++v2;
        ++v11;
      }
      while ( v2 < ptHumanAI->nAnimationMinimumDelay );
    }
  }
}

// source: j/0/humanai/humanai.c:4849  [anchor-callee]
void __cdecl HumanAI_RunActionStack(struct HumanAI_s *ptHumanAI)
{
  void (__cdecl *pfRunCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // eax
  void (__cdecl *v2)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // ecx
  char v3; // dl
  int v4; // esi

  pfRunCallback = ptHumanAI->atActionStackItemList[0].pfRunCallback;
  v2 = *(void (__cdecl **)(struct HumanAI_s *, struct HumanAIActionStackItem_s *))pfRunCallback;
  v3 = 0;
  if ( *(_DWORD *)pfRunCallback )
  {
    do
    {
      v4 = *((_DWORD *)pfRunCallback + 4);
      if ( v4 )
      {
        if ( !v3 )
        {
          *((_DWORD *)pfRunCallback + 4) = v4 - 1;
          v3 = 1;
        }
      }
      else if ( *((_DWORD *)pfRunCallback + 7) )
      {
        (*((void (__cdecl **)(struct HumanAI_s *, _DWORD))pfRunCallback + 7))(ptHumanAI, pfRunCallback);
        return;
      }
      pfRunCallback = v2;
      v2 = *(void (__cdecl **)(struct HumanAI_s *, struct HumanAIActionStackItem_s *))v2;
    }
    while ( v2 );
  }
}

// source: j/0/humanai/humanai.c:4950  [anchor-callee]
void __cdecl HumanAI_ClearMovementQueue(struct HumanAI_s *ptHumanAI)
{
  struct Node_s *ptHead; // esi
  struct Node_s *i; // ebp
  int v3; // edi
  int ptPrev; // ebx
  int v5; // ecx
  double v6; // st7

  ptHead = ptHumanAI->tMovementQueue.ptHead;
  for ( i = ptHead->ptNext; i; i = i->ptNext )
  {
    Node_Remove(ptHead);
    v3 = *(_DWORD *)&ptHumanAI->zScriptFile[36];
    ptPrev = (int)ptHead[4].ptPrev;
    if ( v3 )
    {
      if ( *(_DWORD *)(v3 + 132) )
      {
        if ( ptPrev < (int)(*(_DWORD *)(v3 + 104)) && ptPrev >= 0 )
        {
          v5 = ptPrev * Graph_GetGraphNodeDataSize(*(_DWORD *)&ptHumanAI->zScriptFile[36]) + *(_DWORD *)(v3 + 132);
          if ( *(_DWORD *)v5 != -1 )
          {
            v6 = *(float *)(v5 + 584) - 20480.0;
            *(float *)(v5 + 584) = v6;
            if ( v6 <= 0.0 )
              v6 = 0.0;
            *(float *)(v5 + 584) = v6;
          }
        }
      }
    }
    ptHead->ptPrev = nullptr;
    ptHead->ptNext = nullptr;
    List_AddTail(ptHead, (int)&HumanAI_tFreeMovementQueue);
    ptHead = i;
  }
}

// source: j/0/humanai/humanai.c:4971  [anchor-hash]
void __cdecl HumanAI_CleanUpMovement(struct HumanAI_s *ptHumanAI)
{
  struct QReference_s *vY_high; // eax

  HumanAI_ClearMovementQueue(ptHumanAI);
  if ( BYTE2(ptHumanAI->tCommon.tTargetPosition.vY) )
  {
    vY_high = (struct QReference_s *)HIDWORD(ptHumanAI->tCommon.tTargetPosition.vY);
    if ( vY_high )
    {
      QReference_Delete(vY_high, &QTask_tQTaskRefPool);
      HIDWORD(ptHumanAI->tCommon.tTargetPosition.vY) = 0;
    }
    BYTE2(ptHumanAI->tCommon.tTargetPosition.vY) = 0;
  }
}

// source: j/0/humanai/humanai.c:4997  [anchor-callee]
struct HumanAIMovementQueueItem_t *__cdecl HumanAI_GetFreeMovementQueueItem(struct HumanAI_s *ptHumanAI)
{
  struct Node_s *ptHead; // esi
  _DWORD *v2; // eax

  ptHead = HumanAI_tFreeMovementQueue.ptHead;
  if ( !HumanAI_tFreeMovementQueue.ptHead->ptNext )
    return nullptr;
  v2 = Node_Remove(HumanAI_tFreeMovementQueue.ptHead);
  ptHead->ptPrev = nullptr;
  ptHead->ptNext = nullptr;
  return (struct HumanAIMovementQueueItem_t *)List_AddTail(v2, (int)&ptHumanAI->tMovementQueue);
}

// source: j/0/humanai/humanai.c:5025  [anchor-hash]
struct HumanAI_s *__cdecl HumanAI_AddToFreeMovementQueue(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIMovementQueueItem_t *ptNode)
{
  Graph_AddWeightToNode(*(struct Graph_s **)&ptHumanAI->zScriptFile[36], ptNode->nNodeID, -20480.0);
  ptNode->tNode.ptPrev = nullptr;
  ptNode->tNode.ptNext = nullptr;
  return (struct HumanAI_s *)List_AddTail(ptNode, (int)&HumanAI_tFreeMovementQueue);
}

// source: j/0/humanai/humanai.c:5117  [size]
void __cdecl HumanAI_GetSerializeParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = HumanAI_ptSerializeParameterList;
}

// source: j/0/humanai/humanai.c:5136  [anchor-caller]
void __cdecl HumanAI_DeSerializeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct Graph_s *ptHead; // esi
  struct QReference_s *ptTail; // edi
  struct Graph_s *v5; // esi
  struct QReference_s *v6; // edi
  struct Graph_s *v7; // esi
  struct QTask_s *ptParent; // edi
  int i; // esi
  struct QTask_s *ptMiddle; // eax
  _DWORD *p_ptMiddle; // ecx
  int v12; // edx
  unsigned int v13; // eax
  struct QReference_s *v14; // eax
  unsigned int v15; // eax
  struct QReference_s *v16; // eax
  unsigned int v17; // eax
  struct QReference_s *v18; // eax
  struct QTask_s *v19; // eax
  struct QTask_s *v20; // edi
  struct HumanAIActionStackItem_s *FreeActionStackItem; // eax
  int v22; // esi
  int v23; // ecx
  struct QReference_s **v24; // edx
  struct QReference_s *v25; // ecx
  struct QTask_s *v26; // ebx
  struct QTask_s *ptQTaska = *(struct QTask_s * *)&ptQTask; // [esp+18h] [ebp+4h] ARGSLOT

  if ( LOBYTE(ptQTask[111].tQTaskChildren.ptHead) )
    AIDetection_ClearDetection((struct AIDetection_s *)&ptQTask[222]);
  HumanAI_RemoveEvents((struct HumanAI_s *)ptQTask);
  HumanAI_ClearActionStack((struct HumanAI_s *)ptQTask);
  ptHead = (struct Graph_s *)ptQTask[728].tQTaskChildren.ptHead;
  if ( ptHead )
  {
    ptTail = ptQTask[748].tQTaskRefList.ptTail;
    if ( ptTail != (struct QReference_s *)-1 )
    {
      Graph_AddWeightToNode(ptHead, (int)ptTail, -20480.0);
      v5 = (struct Graph_s *)ptQTask[728].tQTaskChildren.ptHead;
      ptQTask[748].tQTaskRefList.ptTail = (struct QReference_s *)-1;
      Graph_AddWeightToNode(v5, -1, 20480.0);
    }
  }
  Serialize_DeSerializeHandler(ptQTask, pxContext);
  v6 = ptQTask[748].tQTaskRefList.ptTail;
  v7 = (struct Graph_s *)ptQTask[728].tQTaskChildren.ptHead;
  HIBYTE(ptQTask[111].tQTaskChildren.ptMiddle) = 0;
  Graph_AddWeightToNode(v7, (int)v6, 20480.0);
  ptParent = ptQTask[748].ptParent;
  ptQTaska = ptParent;
  for ( i = 0; i < 11; ++i )
    HumanAIContent_SetChannel((struct HumanAI_s *)ptQTask, i, 0.0);
  HumanAIContent_UseIdleView((struct HumanAI_s *)ptQTask);
  ptQTask[222].ptNext = (struct QTask_s *)((int)ptQTask[222].ptNext & ~1u);
  AIGraphAStarSearch_Clear((struct AIGraphAStarSearchData_s *)&ptQTask[7].tQTaskChildren);
  ptQTask[748].ptParent = (struct QTask_s *)ptQTask[748].tQTaskRefList.ptTail;
  HumanAI_ClearMovementQueue((struct HumanAI_s *)ptQTask);
  HumanAI_ClearMovementQueue((struct HumanAI_s *)ptQTask);
  if ( BYTE2(ptQTask[749].tQTaskChildren.ptHead) )
  {
    ptMiddle = ptQTask[749].tQTaskChildren.ptMiddle;
    if ( ptMiddle )
    {
      QReference_Delete((struct QReference_s *)ptMiddle, &QTask_tQTaskRefPool);
      ptQTask[749].tQTaskChildren.ptMiddle = nullptr;
    }
    BYTE2(ptQTask[749].tQTaskChildren.ptHead) = 0;
  }
  ptQTask[738].tQTaskRefList.ptTail = nullptr;
  ptQTask[12].tQTaskChildren.ptTail = nullptr;
  p_ptMiddle = &ptQTask[215].tQTaskRefList.ptMiddle;
  v12 = 8;
  do
  {
    v13 = p_ptMiddle[5];
    if ( v13 == -1 )
    {
      *p_ptMiddle = 0;
    }
    else if ( v13 < 0x1000 && (v14 = Level_atLevelQTaskID[v13]) != nullptr )
    {
      *p_ptMiddle = v14->pxObject;
    }
    else
    {
      *p_ptMiddle = 0;
    }
    v15 = p_ptMiddle[6];
    if ( v15 == -1 )
    {
      p_ptMiddle[1] = 0;
    }
    else if ( v15 < 0x1000 && (v16 = Level_atLevelQTaskID[v15]) != nullptr )
    {
      p_ptMiddle[1] = v16->pxObject;
    }
    else
    {
      p_ptMiddle[1] = 0;
    }
    v17 = p_ptMiddle[4];
    if ( v17 == -1 )
    {
      *(p_ptMiddle - 1) = 0;
    }
    else if ( v17 < 0x1000 && (v18 = Level_atLevelQTaskID[v17]) != nullptr )
    {
      *(p_ptMiddle - 1) = v18->pxObject;
    }
    else
    {
      *(p_ptMiddle - 1) = 0;
    }
    p_ptMiddle += 8;
    --v12;
  }
  while ( v12 );
  if ( ptQTask[109].tQTaskChildren.ptHead
    && ptQTask[748].tQTaskRefList.ptTail != (struct QReference_s *)-1
    && ptParent != (struct QTask_s *)-1 )
  {
    v19 = ptQTask[215].tQTaskChildren.ptHead;
    v20 = nullptr;
    if ( v19->ptNext )
    {
      v20 = ptQTask[215].tQTaskChildren.ptHead;
      Node_Remove(v19);
    }
    FreeActionStackItem = (struct HumanAIActionStackItem_s *)HumanAI_GetFreeActionStackItem((int)ptQTask);
    FreeActionStackItem->bFlags = 0;
    FreeActionStackItem->iDelay = 0;
    v22 = -1;
    v23 = 0;
    if ( (int)ptQTask[109].ptNext > 0 )
    {
      v24 = &ptQTask[99].tQTaskRefList.ptMiddle;
      while ( *v24 != (struct QReference_s *)28 )
      {
        ++v23;
        ++v24;
        if ( v23 >= (int)ptQTask[109].ptNext )
          goto LABEL_43;
      }
      v22 = v23;
    }
LABEL_43:
    FreeActionStackItem->nPriority = v22;
    FreeActionStackItem->pfChildRunCallback = nullptr;
    FreeActionStackItem->pfDeleteCallback = HumanAIContent_PatrolDeleteCB;
    FreeActionStackItem->pfInitCallback = HumanAIContent_PatrolInitCB;
    FreeActionStackItem->pfRunCallback = HumanAIContent_PatrolRunCB;
    FreeActionStackItem->pfRunInitCallback = nullptr;
    FreeActionStackItem->pfPushedFromTopCallback = nullptr;
    FreeActionStackItem->ptContext = (struct HumanAIActionContext_t *)v20;
    v20->tQTaskChildren.ptMiddle = nullptr;
    v20->tQTaskChildren.ptHead = *(&ptQTask->ptNext
                                 + 8 * ((int)&ptQTask[109].tQTaskChildren.ptHead[6].tQTaskRefList.ptTail + 1));
    FreeActionStackItem->eSquadOrder = 0;
    HumanAI_AddAction((struct HumanAI_s *)ptQTask, FreeActionStackItem);
    if ( AIGraphAStarSearch_CreatePath(
           (struct AIGraphAStarSearchData_s *)&ptQTask[7].tQTaskChildren,
           (int)ptQTask[728].tQTaskChildren.ptHead[2].tQTaskChildren.ptTail,
           (int)ptQTask[748].tQTaskRefList.ptTail,
           (int)ptQTaska,
           0xFFFFFFFF) )
    {
      v25 = ptQTask[748].tQTaskRefList.ptTail;
      ptQTask[748].ptParent = ptQTaska;
      *(_DWORD *)&ptQTask[748].eQTaskType = v25;
      HumanAI_CreateQueueItemListFromAStarSearchPath(
        (struct HumanAI_s *)ptQTask,
        (struct AIGraphAStarSearchData_s *)&ptQTask[7].tQTaskChildren);
      v26 = ptQTask[6].ptParent;
      if ( v26->ptNext )
      {
        if ( v26 )
        {
          Node_Remove(ptQTask[6].ptParent);
          Graph_AddWeightToNode(
            (struct Graph_s *)ptQTask[728].tQTaskChildren.ptHead,
            *(_DWORD *)&v26->eQTaskType,
            -20480.0);
          v26->ptPrev = nullptr;
          v26->ptNext = nullptr;
          List_AddTail(v26, (int)&HumanAI_tFreeMovementQueue);
        }
      }
    }
  }
}

// source: j/0/humanai/humanai.c:5271  [anchor-mhash]
void __cdecl HumanAI_SerializeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  _DWORD *p_ptPrev; // esi
  int v3; // ebx
  void *v4; // edx
  int v5; // eax
  struct QReference_s *v6; // ecx
  void *v7; // edx
  int v8; // eax
  struct QReference_s *v9; // ecx
  void *v10; // edx
  int v11; // eax
  struct QReference_s *v12; // ecx

  p_ptPrev = &ptQTask[216].ptPrev;
  v3 = 8;
  do
  {
    v4 = (void *)*(p_ptPrev - 5);
    if ( v4 )
    {
      v5 = 0;
      while ( 1 )
      {
        v6 = Level_atLevelQTaskID[v5];
        if ( v6 )
        {
          if ( v6->pxObject == v4 )
            break;
        }
        if ( ++v5 >= 4096 )
        {
          v5 = -1;
          break;
        }
      }
      *p_ptPrev = v5;
    }
    else
    {
      *p_ptPrev = -1;
    }
    v7 = (void *)*(p_ptPrev - 4);
    if ( v7 )
    {
      v8 = 0;
      while ( 1 )
      {
        v9 = Level_atLevelQTaskID[v8];
        if ( v9 )
        {
          if ( v9->pxObject == v7 )
            break;
        }
        if ( ++v8 >= 4096 )
        {
          v8 = -1;
          break;
        }
      }
      p_ptPrev[1] = v8;
    }
    else
    {
      p_ptPrev[1] = -1;
    }
    v10 = (void *)*(p_ptPrev - 6);
    if ( v10 )
    {
      v11 = 0;
      while ( 1 )
      {
        v12 = Level_atLevelQTaskID[v11];
        if ( v12 )
        {
          if ( v12->pxObject == v10 )
            break;
        }
        if ( ++v11 >= 4096 )
        {
          v11 = -1;
          break;
        }
      }
      *(p_ptPrev - 1) = v11;
    }
    else
    {
      *(p_ptPrev - 1) = -1;
    }
    p_ptPrev += 8;
    --v3;
  }
  while ( v3 );
  Serialize_SerializeHandler(ptQTask, pxContext);
}

// source: j/0/humanai/humanai.c:5324  [anchor-mhash]
void __cdecl HumanAI_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s **p_ptTail; // eax
  int v3; // ecx
  struct QTask_s *v4; // eax
  struct QReference_s **v5; // eax
  int v6; // ecx
  struct QTask_s **v7; // eax
  int v8; // ecx
  struct QTask_s *v9; // eax
  int v10; // edi
  struct QTask_s *ptTail; // eax
  int v12; // [esp+Ch] [ebp-4h]
  struct QTask_s **p_ptMiddle; // [esp+Ch] [ebp-4h]

  ptQTask->ptParent[48].ptParent = ptQTask;
  *(_DWORD *)&ptQTask[6].eQTaskType = 0;
  ptQTask[5].ptNext = (struct QTask_s *)1610612736;
  ptQTask[5].tQTaskChildren.ptHead = (struct QTask_s *)1610612736;
  ptQTask[5].tQTaskRefList.ptMiddle = (struct QReference_s *)1610612736;
  ptQTask[5].ptParent = (struct QTask_s *)1610612736;
  ptQTask[5].tQTaskChildren.ptMiddle = (struct QTask_s *)1072426206;
  ptQTask[5].tQTaskChildren.ptTail = nullptr;
  *(_DWORD *)&ptQTask[5].eQTaskType = 1073108760;
  ptQTask[6].ptNext = nullptr;
  ptQTask[5].tQTaskRefList.ptHead = (struct QReference_s *)1085276160;
  ptQTask[6].ptPrev = (struct QTask_s *)1085276160;
  ptQTask[6].ptParent = (struct QTask_s *)((char *)ptQTask + 276);
  ptQTask[7].ptNext = (struct QTask_s *)((char *)ptQTask + 272);
  ptQTask[5].ptPrev = (struct QTask_s *)1072243195;
  ptQTask[5].tQTaskRefList.ptTail = (struct QReference_s *)1072243195;
  ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
  *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  ptQTask[8].ptPrev = nullptr;
  ptQTask[8].tQTaskRefList.ptHead = nullptr;
  ptQTask[7].tQTaskChildren.ptTail = (struct QTask_s *)((char *)ptQTask + 288);
  ptQTask[7].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[7].tQTaskRefList.ptHead = (struct QReference_s *)&ptQTask[7].tQTaskRefList.ptMiddle;
  ptQTask[7].tQTaskRefList.ptTail = (struct QReference_s *)&ptQTask[7].tQTaskRefList;
  ptQTask[7].ptParent = (struct QTask_s *)((char *)ptQTask + 316);
  ptQTask[8].ptNext = (struct QTask_s *)((char *)ptQTask + 312);
  ptQTask[7].tQTaskChildren.ptHead = (struct QTask_s *)((char *)ptQTask + 292);
  ptQTask[8].tQTaskChildren.ptTail = (struct QTask_s *)-1;
  ptQTask[8].tQTaskChildren.ptHead = (struct QTask_s *)-1;
  ptQTask[8].tQTaskChildren.ptMiddle = (struct QTask_s *)-1;
  ptQTask[99].ptPrev = (struct QTask_s *)((char *)ptQTask + 3968);
  ptQTask[99].tQTaskChildren.ptHead = nullptr;
  ptQTask[8].tQTaskRefList.ptMiddle = nullptr;
  *(_DWORD *)&ptQTask[11].eQTaskType = 0;
  ptQTask[12].ptNext = (struct QTask_s *)-1;
  ptQTask[12].tQTaskChildren.ptTail = nullptr;
  ptQTask[12].tQTaskChildren.ptHead = (struct QTask_s *)-1;
  ptQTask[12].tQTaskChildren.ptMiddle = (struct QTask_s *)-1;
  ptQTask[13].tQTaskChildren.ptHead = nullptr;
  ptQTask[12].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[12].tQTaskRefList.ptTail = nullptr;
  ptQTask[12].ptParent = nullptr;
  *(_DWORD *)&ptQTask[12].eQTaskType = 0;
  ptQTask[13].ptNext = nullptr;
  ptQTask[13].ptPrev = nullptr;
  ptQTask[13].tQTaskChildren.ptMiddle = (struct QTask_s *)-1;
  ptQTask[99].tQTaskChildren.ptMiddle = (struct QTask_s *)((char *)ptQTask + 3964);
  p_ptTail = &ptQTask[13].tQTaskChildren.ptTail;
  v12 = 32;
  do
  {
    p_ptTail[1] = nullptr;
    *p_ptTail = nullptr;
    p_ptTail = (struct QTask_s **)(List_AddTail(p_ptTail, (int)&ptQTask[99].ptPrev) + 22);
    --v12;
  }
  while ( v12 );
  v3 = 0;
  p_ptMiddle = &ptQTask[104].tQTaskChildren.ptMiddle;
  v4 = ptQTask + 85;
  do
  {
    v4->ptNext = (struct QTask_s *)&v4->ptPrev;
    v4->ptPrev = nullptr;
    v4->tQTaskChildren.ptHead = v4;
    *((_BYTE *)&ptQTask[83].ptParent + v3) = 0;
    *p_ptMiddle = nullptr;
    ++v3;
    v4 = (struct QTask_s *)((char *)v4 + 12);
    ++p_ptMiddle;
  }
  while ( v3 < 47 );
  v5 = &ptQTask[215].tQTaskRefList.ptTail;
  v6 = 8;
  do
  {
    *(v5 - 1) = nullptr;
    *v5 = nullptr;
    *(v5 - 2) = nullptr;
    v5 += 8;
    --v6;
  }
  while ( v6 );
  ptQTask[111].tQTaskRefList.ptHead = (struct QReference_s *)1034342036;
  ptQTask[111].tQTaskRefList.ptMiddle = (struct QReference_s *)1034342036;
  ptQTask[109].tQTaskChildren.ptMiddle = (struct QTask_s *)-1;
  ptQTask[109].tQTaskRefList.ptHead = (struct QReference_s *)-1;
  ptQTask[110].ptParent = (struct QTask_s *)-1;
  ptQTask[7].ptPrev = nullptr;
  ptQTask[99].tQTaskRefList.ptHead = nullptr;
  ptQTask[109].ptNext = nullptr;
  ptQTask[109].ptPrev = nullptr;
  ptQTask[109].tQTaskChildren.ptHead = nullptr;
  ptQTask[738].tQTaskRefList.ptTail = nullptr;
  ptQTask[109].tQTaskChildren.ptTail = nullptr;
  ptQTask[99].tQTaskChildren.ptTail = nullptr;
  ptQTask[110].ptNext = nullptr;
  ptQTask[110].tQTaskChildren.ptHead = nullptr;
  ptQTask[110].ptPrev = nullptr;
  ptQTask[110].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[110].tQTaskChildren.ptTail = nullptr;
  ptQTask[110].tQTaskRefList.ptHead = (struct QReference_s *)2;
  ptQTask[110].tQTaskRefList.ptTail = nullptr;
  ptQTask[110].tQTaskRefList.ptMiddle = (struct QReference_s *)300;
  *(_DWORD *)&ptQTask[110].eQTaskType = 0;
  ptQTask[111].ptNext = nullptr;
  ptQTask[111].ptPrev = nullptr;
  LOBYTE(ptQTask[111].tQTaskChildren.ptHead) = 0;
  BYTE1(ptQTask[111].tQTaskChildren.ptHead) = 0;
  BYTE2(ptQTask[111].tQTaskChildren.ptHead) = 0;
  HIBYTE(ptQTask[111].tQTaskChildren.ptHead) = 0;
  LOBYTE(ptQTask[111].tQTaskChildren.ptMiddle) = 0;
  BYTE1(ptQTask[111].tQTaskChildren.ptMiddle) = 0;
  BYTE2(ptQTask[111].tQTaskChildren.ptMiddle) = 0;
  HIBYTE(ptQTask[111].tQTaskChildren.ptMiddle) = 0;
  ptQTask[111].tQTaskChildren.ptTail = (struct QTask_s *)1065353216;
  memset(&ptQTask[111].tQTaskRefList.ptTail, 0, 0xFCu);
  ptQTask[118].ptParent = (struct QTask_s *)((char *)ptQTask + 4756);
  ptQTask[119].ptNext = (struct QTask_s *)((char *)ptQTask + 4752);
  *(_DWORD *)&ptQTask[118].eQTaskType = 0;
  v7 = &ptQTask[120].tQTaskChildren.ptTail;
  v8 = 32;
  do
  {
    *(_BYTE *)v7 = 0;
    v7 += 14;
    --v8;
  }
  while ( v8 );
  ptQTask[215].tQTaskChildren.ptHead = (struct QTask_s *)((char *)ptQTask + 8612);
  ptQTask[215].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[215].tQTaskChildren.ptTail = (struct QTask_s *)((char *)ptQTask + 8608);
  v9 = ptQTask + 164;
  v10 = 32;
  do
  {
    v9->ptPrev = nullptr;
    v9->ptNext = nullptr;
    v9 = (struct QTask_s *)(List_AddTail(v9, (int)&ptQTask[215].tQTaskChildren) + 16);
    --v10;
  }
  while ( v10 );
  ptTail = ptQTask[110].tQTaskChildren.ptTail;
  ptQTask[725].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[725].tQTaskRefList.ptTail = nullptr;
  *(_DWORD *)&ptQTask[725].eQTaskType = 0;
  ptQTask[726].ptNext = nullptr;
  ptQTask[728].tQTaskChildren.ptHead = nullptr;
  LOBYTE(ptQTask[728].tQTaskChildren.ptMiddle) = 0;
  ptQTask[738].ptParent = nullptr;
  strcpy((char *)&ptQTask[738].eQTaskType, HumanAI_azAITypeStrings[(_DWORD)ptTail]);
  strcpy((char *)&ptQTask[740].tQTaskRefList, HumanAI_azAnimTypeStrings[(int)ptQTask[110].tQTaskRefList.ptHead]);
  LOBYTE(ptQTask[747].tQTaskRefList.ptMiddle) = 0;
  BYTE1(ptQTask[747].tQTaskRefList.ptMiddle) = 0;
  ptQTask[747].tQTaskRefList.ptTail = nullptr;
  ptQTask[747].ptParent = nullptr;
  ptQTask[748].ptNext = nullptr;
  ptQTask[748].ptPrev = nullptr;
  ptQTask[748].tQTaskChildren.ptHead = nullptr;
  ptQTask[748].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[748].tQTaskChildren.ptTail = nullptr;
  ptQTask[748].tQTaskRefList.ptHead = nullptr;
  BYTE2(ptQTask[749].tQTaskChildren.ptHead) = 0;
  ptQTask[749].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[749].ptNext = nullptr;
  ptQTask[749].ptPrev = nullptr;
  LOBYTE(ptQTask[749].tQTaskChildren.ptHead) = 0;
  ptQTask[750].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[750].tQTaskRefList.ptTail = nullptr;
  ptQTask[750].ptParent = nullptr;
  *(_DWORD *)&ptQTask[747].eQTaskType = -1;
  ptQTask[748].tQTaskRefList.ptMiddle = (struct QReference_s *)-1;
  ptQTask[748].ptParent = (struct QTask_s *)-1;
  ptQTask[748].tQTaskRefList.ptTail = (struct QReference_s *)-1;
  *(_DWORD *)&ptQTask[748].eQTaskType = -1;
  *(_DWORD *)&ptQTask[750].eQTaskType = -1;
  memset(&ptQTask[742].ptPrev, 0, 0xD8u);
  ptQTask[749].tQTaskChildren.ptTail = nullptr;
  ptQTask[749].tQTaskRefList.ptHead = nullptr;
  ptQTask[749].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[749].tQTaskRefList.ptTail = nullptr;
  ptQTask[749].ptParent = nullptr;
  *(_DWORD *)&ptQTask[749].eQTaskType = 0;
  ptQTask[750].ptNext = nullptr;
  ptQTask[750].ptPrev = nullptr;
  ptQTask[750].tQTaskChildren.ptHead = nullptr;
  ptQTask[750].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[750].tQTaskChildren.ptTail = nullptr;
  ptQTask[750].tQTaskRefList.ptHead = nullptr;
  ptQTask[6].tQTaskChildren.ptHead = nullptr;
  ptQTask[6].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[6].tQTaskChildren.ptTail = nullptr;
  ptQTask[6].tQTaskRefList.ptHead = nullptr;
  ptQTask[6].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[6].tQTaskRefList.ptTail = nullptr;
  strcpy((char *)&ptQTask[1], "stand");
}

// source: j/0/humanai/humanai.c:5524  [anchor-callee]
enum bool __cdecl HumanAI_IsUseIdleViewConeRotation(struct HumanAI_s *ptHumanAI)
{
  void (__cdecl *pfRunCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // ecx
  struct QTask_s *ptParent; // ebx
  struct QTask_s *v3; // edx
  int ptHead; // eax
  enum bool result; // eax

  pfRunCallback = ptHumanAI->atActionStackItemList[0].pfRunCallback;
  ptParent = ptHumanAI->tQTask.ptParent;
  v3 = ptParent->ptParent;
  result = (*(_DWORD *)pfRunCallback
         && pfRunCallback
         && *((void (__cdecl **)(struct HumanAI_s *, struct HumanAIActionStackItem_s *))pfRunCallback + 6) == HumanAIContent_PatrolInitCB
         || (ptHead = (int)v3[215].tQTaskChildren.ptHead, ptHead > 0)
         && v3[7 * ptHead + 187].ptNext == (struct QTask_s *)6
         || !*(_DWORD *)pfRunCallback
         || !pfRunCallback
         || *((void (__cdecl **)(struct HumanAI_s *, struct HumanAIActionStackItem_s *))pfRunCallback + 6) == HumanAIContent_IdleInitCB)
        && !HumanAI_GetTargetQTask(ptHumanAI, true)
        && (*(_DWORD *)&ptParent[30].eQTaskType & 0x1000000) == 0;
  return result;
}

// source: j/0/humanai/humanai.c:5560  [anchor-callee]
void __cdecl HumanAI_UpdateIdleViewConeRotation(struct HumanAI_s *ptHumanAI)
{
  #pragma pack(push, 1)
  union
  {
    struct { float avAlphaSign[4]; };
    struct { char igi2_o1[16]; float avGammaSign[4]; };
    char igi2_extent[32];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int nTimer; // eax
  int v3; // ebx
  int v4; // esi
  double v5; // st7
  int iIndex; // ecx
  double v7; // st7
  double v8; // st7
  double v9; // st7
  double v10; // st7
  double v11; // st7

  nTimer = ptHumanAI->tViewConeRotationInfo.nTimer;
  v3 = 0;
  v4 = 0;
  igi2_frame.avAlphaSign[0] = 0.0;
  igi2_frame.avAlphaSign[1] = -1.0;
  igi2_frame.avAlphaSign[2] = 0.0;
  igi2_frame.avAlphaSign[3] = 1.0;
  igi2_frame.avGammaSign[0] = 1.0;
  igi2_frame.avGammaSign[1] = 0.0;
  igi2_frame.avGammaSign[2] = -1.0;
  igi2_frame.avGammaSign[3] = 0.0;
  if ( nTimer )
  {
    v4 = 1;
    ptHumanAI->tViewConeRotationInfo.nTimer = nTimer - 1;
  }
  if ( HumanAI_IsUseIdleViewConeRotation(ptHumanAI) == false || v4 )
  {
    v10 = -ptHumanAI->tViewConeRotationInfo.vAlpha;
    if ( v10 >= -0.01745329238474369 )
    {
      if ( v10 > 0.01745329238474369 )
        v10 = 0.01745329238474369;
    }
    else
    {
      v10 = -0.01745329238474369;
    }
    ptHumanAI->tViewConeRotationInfo.vAlpha = v10 + ptHumanAI->tViewConeRotationInfo.vAlpha;
    v11 = -ptHumanAI->tViewConeRotationInfo.vGamma;
    if ( v11 >= -0.01745329238474369 )
    {
      if ( v11 > 0.01745329238474369 )
        v11 = 0.01745329238474369;
      ptHumanAI->tViewConeRotationInfo.vGamma = v11 + ptHumanAI->tViewConeRotationInfo.vGamma;
    }
    else
    {
      ptHumanAI->tViewConeRotationInfo.vGamma = ptHumanAI->tViewConeRotationInfo.vGamma + -0.01745329238474369;
    }
    return;
  }
  v5 = ptHumanAI->tViewConeRotationInfo.vAlphaFactor - ptHumanAI->tViewConeRotationInfo.vAlpha;
  if ( v5 >= -0.01745329238474369 )
  {
    if ( v5 > 0.01745329238474369 )
      v5 = 0.01745329238474369;
  }
  else
  {
    v5 = -0.01745329238474369;
  }
  iIndex = ptHumanAI->tViewConeRotationInfo.iIndex;
  ptHumanAI->tViewConeRotationInfo.vAlpha = v5 + ptHumanAI->tViewConeRotationInfo.vAlpha;
  v7 = igi2_frame.avAlphaSign[iIndex] * 0.01745329238474369 + ptHumanAI->tViewConeRotationInfo.vAlphaFactor;
  ptHumanAI->tViewConeRotationInfo.vAlphaFactor = v7;
  if ( v7 > 0.1745329350233078 )
  {
    ptHumanAI->tViewConeRotationInfo.vAlphaFactor = 0.1745329350233078;
LABEL_13:
    v3 = 1;
    goto LABEL_14;
  }
  if ( v7 < -0.1745329350233078 )
  {
    ptHumanAI->tViewConeRotationInfo.vAlphaFactor = -0.1745329350233078;
    goto LABEL_13;
  }
LABEL_14:
  v8 = ptHumanAI->tViewConeRotationInfo.vGammaFactor - ptHumanAI->tViewConeRotationInfo.vGamma;
  if ( v8 >= -0.01745329238474369 )
  {
    if ( v8 > 0.01745329238474369 )
      v8 = 0.01745329238474369;
  }
  else
  {
    v8 = -0.01745329238474369;
  }
  ptHumanAI->tViewConeRotationInfo.vGamma = v8 + ptHumanAI->tViewConeRotationInfo.vGamma;
  v9 = igi2_frame.avGammaSign[iIndex] * 0.01745329238474369 + ptHumanAI->tViewConeRotationInfo.vGammaFactor;
  ptHumanAI->tViewConeRotationInfo.vGammaFactor = v9;
  if ( v9 <= 0.7853981852531433 )
  {
    if ( v9 >= -0.7853981852531433 )
    {
      if ( !v3 )
        return;
    }
    else
    {
      ptHumanAI->tViewConeRotationInfo.vGammaFactor = -0.7853981852531433;
    }
  }
  else
  {
    ptHumanAI->tViewConeRotationInfo.vGammaFactor = 0.7853981852531433;
  }
  if ( iIndex >= 3 )
  {
    ptHumanAI->tViewConeRotationInfo.nTimer = 150;
    ptHumanAI->tViewConeRotationInfo.iIndex = 0;
  }
  else
  {
    ptHumanAI->tViewConeRotationInfo.iIndex = iIndex + 1;
  }
}

// source: j/0/humanai/humanai.c:5650  [anchor-callee]
void __cdecl HumanAI_RunDeathChecks(struct HumanAI_s *ptHumanAI)
{
  #pragma pack(push, 1)
  union
  {
    struct { int nEventPriority; };
    struct { char igi2_o1[4]; struct DynCubeObjRemoveObjContext_s tContext; };
    struct { char igi2_o2[8]; struct HumanAIEvent_t tEvent; };
    char igi2_extent[100];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct World_s *ptParent; // eax
  char v2; // cl
  void (__cdecl *pfRunCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // edi
  void (__cdecl *v4)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // ebp
  void (__cdecl *v5)(struct HumanAI_s *, _DWORD); // eax
  _DWORD *v6; // eax
  int v7; // eax
  int *v8; // ecx
  _DWORD *v9; // eax
  struct QReference_s *vY_high; // eax
  void *vProbability_high; // eax
  void *nAnimation; // eax
  struct World_s *ptWorld; // ecx
  int v14; // eax
  void (__cdecl *pfHandler)(struct World_s *, struct DynCubeObjRemoveObjContext_s *); // eax

  ptParent = (struct World_s *)ptHumanAI->tQTask.ptParent;
  v2 = ptParent[1].zLightmapFile[100];
  igi2_frame.tContext.ptWorld = ptParent;
  if ( v2 && !HIBYTE(ptHumanAI->avChannel[5]) )
  {
    pfRunCallback = ptHumanAI->atActionStackItemList[0].pfRunCallback;
    v4 = *(void (__cdecl **)(struct HumanAI_s *, struct HumanAIActionStackItem_s *))pfRunCallback;
    igi2_frame.nEventPriority = -1;
    if ( *(_DWORD *)pfRunCallback )
    {
      do
      {
        v5 = *((void (__cdecl **)(struct HumanAI_s *, _DWORD))pfRunCallback + 9);
        if ( v5 )
          v5(ptHumanAI, pfRunCallback);
        Node_Remove((_DWORD **)pfRunCallback);
        v6 = *((_DWORD **)pfRunCallback + 12);
        *((_BYTE *)pfRunCallback + 52) = 0;
        if ( v6 )
        {
          v6[1] = 0;
          *v6 = 0;
          List_AddTail(v6, (int)&ptHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID);
          *((_DWORD *)pfRunCallback + 12) = 0;
        }
        pfRunCallback = v4;
        v4 = *(void (__cdecl **)(struct HumanAI_s *, struct HumanAIActionStackItem_s *))v4;
      }
      while ( v4 );
    }
    v7 = 0;
    if ( ptHumanAI->nAnimationMinimumDelay > 0 )
    {
      v8 = &ptHumanAI->anEventPriorityList[6];
      do
      {
        if ( *v8 == 2 )
          igi2_frame.nEventPriority = v7;
        ++v7;
        ++v8;
      }
      while ( v7 < ptHumanAI->nAnimationMinimumDelay );
    }
    igi2_frame.tEvent.eEvent = 2;
    igi2_frame.tEvent.ptHumanOriginatorQTaskRef = nullptr;
    igi2_frame.tEvent.ptReferenceQTaskRef = nullptr;
    igi2_frame.tEvent.tNode.ptPrev = nullptr;
    igi2_frame.tEvent.tNode.ptNext = nullptr;
    List_AddTail(&igi2_frame.tEvent, (int)&ptHumanAI->atEventTypeStacks[2]);
    HumanAI_RunScriptEvent(ptHumanAI, 2, igi2_frame.nEventPriority);
    Node_Remove(&igi2_frame.tEvent);
    HIBYTE(ptHumanAI->avChannel[5]) = 1;
    AIDetection_ClearDetection((struct AIDetection_s *)&ptHumanAI->tAIDetection.tFriendList);
    v9 = *(_DWORD **)(*(_DWORD *)&ptHumanAI->zScriptFile[36] + 220);
    if ( *v9 && v9 )
    {
      while ( v9[35] != HIDWORD(ptHumanAI->tCommon.tAimPosition.vY) )
      {
        v9 = (_DWORD *)*v9;
        if ( !*v9 || !v9 )
          goto LABEL_21;
      }
      v9[2] &= ~1u;
    }
LABEL_21:
    HumanAI_RemoveEvents(ptHumanAI);
    ptParent = igi2_frame.tContext.ptWorld;
  }
  if ( LOBYTE(ptHumanAI->tQTask.ptParent[29].tQTaskRefList.ptHead)
    && ptParent[1].zLightmapFile[101]
    && ptParent[1].zLightmapFile[228] )
  {
    HumanAI_ClearMovementQueue(ptHumanAI);
    if ( BYTE2(ptHumanAI->tCommon.tTargetPosition.vY) )
    {
      vY_high = (struct QReference_s *)HIDWORD(ptHumanAI->tCommon.tTargetPosition.vY);
      if ( vY_high )
      {
        QReference_Delete(vY_high, &QTask_tQTaskRefPool);
        HIDWORD(ptHumanAI->tCommon.tTargetPosition.vY) = 0;
      }
      BYTE2(ptHumanAI->tCommon.tTargetPosition.vY) = 0;
    }
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
    if ( ptHumanAI->vMaxRotationDelta < 0.0 )
    {
      ptWorld = igi2_frame.tContext.ptWorld;
      v14 = *(_DWORD *)&igi2_frame.tContext.ptWorld[2].zLightmapFile[120];
      if ( v14 == -1 || Flow_ptFlow->nTicksDrawn - v14 > 1 )
      {
        igi2_frame.tContext.ptWorld = Game_ptGame->ptWorld;
        pfHandler = (void (__cdecl *)(struct World_s *, struct DynCubeObjRemoveObjContext_s *))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRemoveQTaskEvent][WORD2(ptWorld->atStartDynCubePos[0].vY)].pfHandler;
        if ( pfHandler )
          pfHandler(ptWorld, &igi2_frame.tContext);
      }
    }
  }
}

// source: j/0/humanai/humanai.c:5762  [anchor-strings]
void __cdecl HumanAI_RunDetection(struct HumanAI_s *ptHumanAI, char *pisAlarmed)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real64x3_t v96; };
    struct { char igi2_o1[44]; int v97; };
    struct { char igi2_o2[48]; unsigned int v98; };
    struct { char igi2_o3[52]; struct QTask_s *ptSourceQTask; };
    struct { char igi2_o4[56]; __int64 v100; };
    struct { char igi2_o5[64]; float v101; };
    struct { char igi2_o6[72]; int v102; };
    struct { char igi2_o7[76]; int *v103; };
    struct { char igi2_o8[80]; struct WeaponGetFireTypeAmmoContext_s nFireType[2]; };
    struct { char igi2_o9[120]; struct real32x9_t ptDest; };
    struct { char igi2_o10[160]; _DWORD *v106; };
    struct { char igi2_o11[164]; int v107; };
    struct { char igi2_o12[168]; int v108; };
    struct { char igi2_o13[172]; int v109; };
    struct { char igi2_o14[176]; int v110; };
    struct { char igi2_o15[180]; int v111; };
    struct { char igi2_o16[184]; unsigned int v112; };
    struct { char igi2_o17[200]; int v113; };
    struct { char igi2_o18[204]; int v114; };
    struct { char igi2_o19[212]; int v115; };
    struct { char igi2_o20[216]; int v116; };
    struct { char igi2_o21[220]; int v117; };
    struct { char igi2_o22[236]; float v118; };
    struct { char igi2_o23[252]; float v119; };
    struct { char igi2_o24[272]; _BYTE v120[8]; };
    struct { char igi2_o25[280]; struct real64x3_t ptPosition[3]; };
    char igi2_extent[364];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptParent; // ecx
  struct QTask_s *ptTail; // eax
  char ptHead; // dl
  char v5; // cl
  struct QTask_s **p_ptPrev; // esi
  double *v7; // ebx
  double v8; // st7
  double v9; // st6
  double v10; // st7
  double v11; // st6
  float *v12; // ecx
  double v13; // st7
  double v14; // st6
  double v15; // st6
  double v16; // rt2
  long double v17; // st7
  long double v18; // rtt
  double v19; // st6
  double v20; // st5
  long double v21; // st4
  double v22; // st6
  long double v23; // st7
  long double v24; // rt1
  double v25; // st6
  double v26; // st6
  int v27; // ecx
  struct WeaponGetFireTypeAmmoContext_s *p_ptTail; // esi
  double *p_vViewConeAlpha; // edi
  int vViewConeAlpha_high; // eax
  int vViewConeAlpha_low; // edx
  void *vSecondaryViewConeAlpha_high; // ecx
  int vSecondaryViewConeAlpha_low; // eax
  struct AIDetectionListItem_s *vViewConeLength_low; // ecx
  int vViewConeGamma_high; // edx
  int vSecondaryViewConeGamma_high; // eax
  int vSecondaryViewConeLength_high; // ecx
  void *vSecondaryViewConeGamma_low; // edx
  int vSecondaryViewConeLength_low; // eax
  int vX_low; // ecx
  struct QTask_s *vViewConeLength_high; // edx
  struct AIDetectionList_s *p_tFriendList; // eax
  unsigned int bQTaskMask; // ebx
  int v44; // esi
  int v45; // eax
  double v46; // st3
  long double v47; // st4
  float v48; // edx
  unsigned __int16 v49; // ax
  enum GameDifficulty_e eDifficultyLevel; // eax
  _BYTE *v51; // eax
  _DWORD *v52; // ecx
  int v53; // edx
  char v54; // al
  int v55; // eax
  struct HumanAI_s *v56; // eax
  struct HumanAI_s *v57; // edi
  struct HumanAI_s *v58; // esi
  int v59; // eax
  int v60; // esi
  struct real64x3_t *v61; // edi
  int v62; // eax
  int v63; // edx
  int v64; // eax
  int v65; // eax
  int v66; // edx
  __int16 v67; // ax
  int nDetectionTick; // eax
  _DWORD *v69; // esi
  int v70; // ecx
  _BYTE *v71; // edx
  struct QTask_s *ptPrev; // eax
  struct QTask_s *v73; // eax
  struct QTask_s *v74; // ecx
  int v75; // eax
  bool v76; // zf
  int v77; // eax
  int v78; // ecx
  int v79; // ecx
  __int16 v80; // ax
  struct QTask_s *TargetQTask; // eax
  struct QTask_s *v82; // edx
  int eQTaskType; // edi
  unsigned int v84; // esi
  int v85; // eax
  struct real64x3_t *v86; // esi
  struct QTask_s *ptNext; // esi
  struct QTask_s *ptNetManagerQTask; // edi
  DWORD PerformanceCounter; // eax
  int v90; // edx
  struct QTask_s *v91; // eax
  struct QTask_s *v92; // eax
  struct Client_s *ClientFromHumanQTask; // eax
  int v94; // eax
  bool v95; // sf

  ptParent = ptHumanAI->tQTask.ptParent;
  ptTail = ptParent[33].tQTaskChildren.ptTail;
  igi2_frame.v103 = (int *)ptParent->ptParent;
  ptHead = (char)ptParent[29].tQTaskRefList.ptHead;
  igi2_frame.ptSourceQTask = ptParent;
  if ( ptHead )
    goto LABEL_108;
  v5 = BYTE2(ptTail[12].tQTaskRefList.ptTail);
  igi2_frame.v108 = -1;
  if ( v5 )
  {
    qmemcpy(&ptHumanAI->tAIDetectionView.tViewOrientation.tY.vY, &ptTail[12].ptParent, 0x18u);
    p_ptTail = (struct WeaponGetFireTypeAmmoContext_s *)&ptTail[13].tQTaskChildren.ptTail;
    p_vViewConeAlpha = &ptHumanAI->tAIDetectionView.vViewConeAlpha;
    goto LABEL_7;
  }
  p_ptPrev = &HumanSoldier_GetCheapHeadBonePosition(
                igi2_frame.ptSourceQTask,
                nullptr,
                (struct real64x3_t *)&ptHumanAI->tAIDetectionView.tViewOrientation.tY.vY)[3].ptPrev;
  v7 = &ptHumanAI->tAIDetectionView.vViewConeAlpha;
  HIDWORD(igi2_frame.v96.vZ) = LODWORD(ptHumanAI->tViewConeRotationInfo.vGamma);
  qmemcpy(&ptHumanAI->tAIDetectionView.vViewConeAlpha, p_ptPrev, 0x28u);
  Real32x9_Create(&igi2_frame.ptDest, ptHumanAI->tViewConeRotationInfo.vAlpha, 0.0, *((float *)&igi2_frame.v96.vZ + 1));
  *(float *)&igi2_frame.nFireType[0].ptAmmoType = igi2_frame.ptDest.tX.vX * *(float *)&ptHumanAI->tAIDetectionView.vViewConeAlpha
                                     + igi2_frame.ptDest.tZ.vX * *(float *)&ptHumanAI->tAIDetectionView.vViewConeGamma
                                     + igi2_frame.ptDest.tY.vX * *((float *)&ptHumanAI->tAIDetectionView.vViewConeAlpha + 1);
  *(float *)&igi2_frame.nFireType[0].nAmmoInWeapon = igi2_frame.ptDest.tX.vY * *(float *)&ptHumanAI->tAIDetectionView.vViewConeAlpha
                                        + igi2_frame.ptDest.tZ.vY * *(float *)&ptHumanAI->tAIDetectionView.vViewConeGamma
                                        + igi2_frame.ptDest.tY.vY * *((float *)&ptHumanAI->tAIDetectionView.vViewConeAlpha + 1);
  *(float *)&igi2_frame.nFireType[0].nAmmoAvailable = igi2_frame.ptDest.tX.vZ * *(float *)&ptHumanAI->tAIDetectionView.vViewConeAlpha
                                         + igi2_frame.ptDest.tZ.vZ * *(float *)&ptHumanAI->tAIDetectionView.vViewConeGamma
                                         + igi2_frame.ptDest.tY.vZ * *((float *)&ptHumanAI->tAIDetectionView.vViewConeAlpha + 1);
  *(float *)&igi2_frame.nFireType[0].nBulletsPerRound = igi2_frame.ptDest.tX.vX * *((float *)&ptHumanAI->tAIDetectionView.vViewConeGamma + 1)
                                           + igi2_frame.ptDest.tZ.vX * *((float *)&ptHumanAI->tAIDetectionView.vViewConeLength + 1)
                                           + igi2_frame.ptDest.tY.vX * *(float *)&ptHumanAI->tAIDetectionView.vViewConeLength;
  *(float *)&igi2_frame.nFireType[0].nRoundsPerClip = igi2_frame.ptDest.tX.vY * *((float *)&ptHumanAI->tAIDetectionView.vViewConeGamma + 1)
                                         + igi2_frame.ptDest.tZ.vY * *((float *)&ptHumanAI->tAIDetectionView.vViewConeLength + 1)
                                         + igi2_frame.ptDest.tY.vY * *(float *)&ptHumanAI->tAIDetectionView.vViewConeLength;
  *(float *)&igi2_frame.nFireType[1].ptAmmoType = igi2_frame.ptDest.tX.vZ * *((float *)&ptHumanAI->tAIDetectionView.vViewConeGamma + 1)
                                     + igi2_frame.ptDest.tZ.vZ * *((float *)&ptHumanAI->tAIDetectionView.vViewConeLength + 1)
                                     + igi2_frame.ptDest.tY.vZ * *(float *)&ptHumanAI->tAIDetectionView.vViewConeLength;
  v8 = igi2_frame.ptDest.tX.vX * *(float *)&ptHumanAI->tAIDetectionView.vSecondaryViewConeAlpha
     + igi2_frame.ptDest.tZ.vX * *(float *)&ptHumanAI->tAIDetectionView.vSecondaryViewConeGamma;
  v9 = igi2_frame.ptDest.tY.vX * *((float *)&ptHumanAI->tAIDetectionView.vSecondaryViewConeAlpha + 1);
  igi2_frame.nFireType[1].nRoundsPerClip = igi2_frame.ptDest.nOps + HIDWORD(ptHumanAI->tAIDetectionView.vSecondaryViewConeGamma) + 1;
  *(float *)&igi2_frame.nFireType[1].nAmmoInWeapon = v8 + v9;
  *(float *)&igi2_frame.nFireType[1].nAmmoAvailable = igi2_frame.ptDest.tX.vY * *(float *)&ptHumanAI->tAIDetectionView.vSecondaryViewConeAlpha
                                         + igi2_frame.ptDest.tZ.vY * *(float *)&ptHumanAI->tAIDetectionView.vSecondaryViewConeGamma
                                         + igi2_frame.ptDest.tY.vY
                                         * *((float *)&ptHumanAI->tAIDetectionView.vSecondaryViewConeAlpha + 1);
  *(float *)&igi2_frame.nFireType[1].nBulletsPerRound = igi2_frame.ptDest.tX.vZ
                                           * *(float *)&ptHumanAI->tAIDetectionView.vSecondaryViewConeAlpha
                                           + igi2_frame.ptDest.tZ.vZ
                                           * *(float *)&ptHumanAI->tAIDetectionView.vSecondaryViewConeGamma
                                           + igi2_frame.ptDest.tY.vZ
                                           * *((float *)&ptHumanAI->tAIDetectionView.vSecondaryViewConeAlpha + 1);
  qmemcpy(&ptHumanAI->tAIDetectionView.vViewConeAlpha, igi2_frame.nFireType, 0x28u);
  if ( *(float *)&igi2_frame.ptSourceQTask[15].ptParent != 0.0 || (*(_DWORD *)&igi2_frame.ptSourceQTask[30].eQTaskType & 0x1000000) != 0 )
  {
    HumanAI_GetTargetPosition((struct real64x3_t *)&igi2_frame.ptDest, ptHumanAI);
    v10 = *(double *)&igi2_frame.ptDest.tX.vX - *(double *)&igi2_frame.ptSourceQTask[1].ptNext;
    v11 = *(double *)&igi2_frame.ptDest.tX.vZ - *(double *)&igi2_frame.ptSourceQTask[1].tQTaskChildren.ptHead;
    v12 = (float *)(*(_DWORD *)&igi2_frame.ptSourceQTask[7].eQTaskType + 80 * (int)igi2_frame.ptSourceQTask[35].tQTaskRefList.ptMiddle);
    igi2_frame.v101 = *(double *)&igi2_frame.ptDest.tY.vY - *(double *)&igi2_frame.ptSourceQTask[1].tQTaskChildren.ptTail;
    *(float *)&igi2_frame.v100 = v10 - *v12;
    v13 = v11 - v12[1];
    v14 = igi2_frame.v101 - v12[2];
    igi2_frame.v101 = v14;
    v15 = v14 * *(float *)&igi2_frame.ptSourceQTask[3].tQTaskRefList.ptTail
        + v13 * *(float *)&igi2_frame.ptSourceQTask[3].tQTaskChildren.ptTail
        + *(float *)&igi2_frame.v100 * *(float *)&igi2_frame.ptSourceQTask[3].ptPrev;
    v16 = igi2_frame.v101 * *(float *)&igi2_frame.ptSourceQTask[3].ptParent
        + v13 * *(float *)&igi2_frame.ptSourceQTask[3].tQTaskRefList.ptHead
        + *(float *)&igi2_frame.v100 * *(float *)&igi2_frame.ptSourceQTask[3].tQTaskChildren.ptHead;
    *(float *)&igi2_frame.nFireType[0].nAmmoAvailable = igi2_frame.v101 * *(float *)&igi2_frame.ptSourceQTask[3].eQTaskType
                                           + v13 * *(float *)&igi2_frame.ptSourceQTask[3].tQTaskRefList.ptMiddle
                                           + *(float *)&igi2_frame.v100 * *(float *)&igi2_frame.ptSourceQTask[3].tQTaskChildren.ptMiddle;
    *(double *)&igi2_frame.ptDest.tX.vX = v15;
    *(double *)&igi2_frame.ptDest.tX.vZ = v16;
    *(double *)&igi2_frame.ptDest.tY.vY = *(float *)&igi2_frame.nFireType[0].nAmmoAvailable;
    qmemcpy(&igi2_frame.v96, &igi2_frame.ptDest, sizeof(igi2_frame.v96));
    v17 = GameFunctions_CalcAlpha(igi2_frame.v96);
    v18 = sin(v17);
    *(float *)&igi2_frame.v97 = cos(v17);
    igi2_frame.v119 = -v18;
    *(float *)&igi2_frame.nFireType[0].ptAmmoType = (*(float *)&ptHumanAI->tAIDetectionView.vViewConeGamma
                                        + *((float *)&ptHumanAI->tAIDetectionView.vViewConeAlpha + 1))
                                       * 0.0
                                       + *(float *)v7;
    v19 = *(float *)v7 * 0.0;
    v20 = *(float *)&igi2_frame.v97 * *((float *)&ptHumanAI->tAIDetectionView.vViewConeAlpha + 1);
    v21 = v18 * *(float *)&ptHumanAI->tAIDetectionView.vViewConeGamma;
    igi2_frame.nFireType[1].nRoundsPerClip = HIDWORD(ptHumanAI->tAIDetectionView.vSecondaryViewConeGamma) + 1;
    *(float *)&igi2_frame.nFireType[0].nAmmoInWeapon = v20 + v21 + v19;
    *(float *)&igi2_frame.nFireType[0].nAmmoAvailable = *(float *)&igi2_frame.v97 * *(float *)&ptHumanAI->tAIDetectionView.vViewConeGamma
                                           + igi2_frame.v119 * *((float *)&ptHumanAI->tAIDetectionView.vViewConeAlpha + 1)
                                           + v19;
    *(float *)&igi2_frame.nFireType[0].nBulletsPerRound = (*((float *)&ptHumanAI->tAIDetectionView.vViewConeLength + 1)
                                              + *(float *)&ptHumanAI->tAIDetectionView.vViewConeLength)
                                             * 0.0
                                             + *((float *)&ptHumanAI->tAIDetectionView.vViewConeGamma + 1);
    v22 = *((float *)&ptHumanAI->tAIDetectionView.vViewConeGamma + 1) * 0.0;
    *(float *)&igi2_frame.nFireType[0].nRoundsPerClip = *(float *)&igi2_frame.v97 * *(float *)&ptHumanAI->tAIDetectionView.vViewConeLength
                                           + v18 * *((float *)&ptHumanAI->tAIDetectionView.vViewConeLength + 1)
                                           + v22;
    *(float *)&igi2_frame.nFireType[1].ptAmmoType = *(float *)&igi2_frame.v97 * *((float *)&ptHumanAI->tAIDetectionView.vViewConeLength + 1)
                                       + igi2_frame.v119 * *(float *)&ptHumanAI->tAIDetectionView.vViewConeLength
                                       + v22;
    *(float *)&igi2_frame.nFireType[1].nAmmoInWeapon = (*(float *)&ptHumanAI->tAIDetectionView.vSecondaryViewConeGamma
                                           + *((float *)&ptHumanAI->tAIDetectionView.vSecondaryViewConeAlpha + 1))
                                          * 0.0
                                          + *(float *)&ptHumanAI->tAIDetectionView.vSecondaryViewConeAlpha;
    *(float *)&igi2_frame.v98 = *(float *)&ptHumanAI->tAIDetectionView.vSecondaryViewConeAlpha * 0.0;
    *(float *)&igi2_frame.nFireType[1].nAmmoAvailable = *(float *)&igi2_frame.v97
                                           * *((float *)&ptHumanAI->tAIDetectionView.vSecondaryViewConeAlpha + 1)
                                           + v18 * *(float *)&ptHumanAI->tAIDetectionView.vSecondaryViewConeGamma
                                           + *(float *)&igi2_frame.v98;
    *(float *)&igi2_frame.nFireType[1].nBulletsPerRound = igi2_frame.v119
                                             * *((float *)&ptHumanAI->tAIDetectionView.vSecondaryViewConeAlpha + 1)
                                             + *(float *)&igi2_frame.v97
                                             * *(float *)&ptHumanAI->tAIDetectionView.vSecondaryViewConeGamma
                                             + *(float *)&igi2_frame.v98;
    qmemcpy(v7, igi2_frame.nFireType, 0x28u);
    qmemcpy(&igi2_frame.v96, &igi2_frame.ptDest, sizeof(igi2_frame.v96));
    v23 = GameFunctions_CalcGamma(igi2_frame.v96);
    v24 = sin(v23);
    *(float *)&igi2_frame.v97 = cos(v23);
    igi2_frame.v118 = -v24;
    v25 = *(float *)&ptHumanAI->tAIDetectionView.vViewConeGamma * 0.0;
    *(float *)&igi2_frame.nFireType[0].ptAmmoType = v24 * *((float *)&ptHumanAI->tAIDetectionView.vViewConeAlpha + 1)
                                       + *(float *)&igi2_frame.v97 * *(float *)v7
                                       + v25;
    *(float *)&igi2_frame.nFireType[0].nAmmoInWeapon = *(float *)&igi2_frame.v97 * *((float *)&ptHumanAI->tAIDetectionView.vViewConeAlpha + 1)
                                          + igi2_frame.v118 * *(float *)v7
                                          + v25;
    *(float *)&igi2_frame.nFireType[0].nAmmoAvailable = (*(float *)v7 + *((float *)&ptHumanAI->tAIDetectionView.vViewConeAlpha + 1))
                                           * 0.0
                                           + *(float *)&ptHumanAI->tAIDetectionView.vViewConeGamma;
    v26 = *((float *)&ptHumanAI->tAIDetectionView.vViewConeLength + 1) * 0.0;
    *(float *)&igi2_frame.nFireType[0].nBulletsPerRound = v24 * *(float *)&ptHumanAI->tAIDetectionView.vViewConeLength
                                             + *(float *)&igi2_frame.v97
                                             * *((float *)&ptHumanAI->tAIDetectionView.vViewConeGamma + 1)
                                             + v26;
    *(float *)&igi2_frame.nFireType[0].nRoundsPerClip = *(float *)&igi2_frame.v97 * *(float *)&ptHumanAI->tAIDetectionView.vViewConeLength
                                           + igi2_frame.v118 * *((float *)&ptHumanAI->tAIDetectionView.vViewConeGamma + 1)
                                           + v26;
    *(float *)&igi2_frame.nFireType[1].ptAmmoType = (*((float *)&ptHumanAI->tAIDetectionView.vViewConeGamma + 1)
                                        + *(float *)&ptHumanAI->tAIDetectionView.vViewConeLength)
                                       * 0.0
                                       + *((float *)&ptHumanAI->tAIDetectionView.vViewConeLength + 1);
    *(float *)&igi2_frame.v98 = *(float *)&ptHumanAI->tAIDetectionView.vSecondaryViewConeGamma * 0.0;
    *(float *)&igi2_frame.nFireType[1].nAmmoInWeapon = *(float *)&igi2_frame.v97
                                          * *(float *)&ptHumanAI->tAIDetectionView.vSecondaryViewConeAlpha
                                          + v24 * *((float *)&ptHumanAI->tAIDetectionView.vSecondaryViewConeAlpha + 1)
                                          + *(float *)&igi2_frame.v98;
    *(float *)&igi2_frame.nFireType[1].nAmmoAvailable = igi2_frame.v118 * *(float *)&ptHumanAI->tAIDetectionView.vSecondaryViewConeAlpha
                                           + *(float *)&igi2_frame.v97
                                           * *((float *)&ptHumanAI->tAIDetectionView.vSecondaryViewConeAlpha + 1)
                                           + *(float *)&igi2_frame.v98;
    v27 = HIDWORD(ptHumanAI->tAIDetectionView.vSecondaryViewConeGamma) + 1;
    *(float *)&igi2_frame.nFireType[1].nBulletsPerRound = (*(float *)&ptHumanAI->tAIDetectionView.vSecondaryViewConeAlpha
                                              + *((float *)&ptHumanAI->tAIDetectionView.vSecondaryViewConeAlpha + 1))
                                             * 0.0
                                             + *(float *)&ptHumanAI->tAIDetectionView.vSecondaryViewConeGamma;
    igi2_frame.nFireType[1].nRoundsPerClip = v27;
    p_ptTail = igi2_frame.nFireType;
    p_vViewConeAlpha = &ptHumanAI->tAIDetectionView.vViewConeAlpha;
LABEL_7:
    qmemcpy(p_vViewConeAlpha, p_ptTail, 0x28u);
  }
  vViewConeAlpha_high = HIDWORD(ptHumanAI->tView.vViewConeAlpha);
  vViewConeAlpha_low = LODWORD(ptHumanAI->tView.vViewConeAlpha);
  *(_DWORD *)&ptHumanAI->tAIDetectionView.isSecondaryViewUsed = LODWORD(ptHumanAI->tView.vViewConeGamma);
  vSecondaryViewConeAlpha_high = (void *)HIDWORD(ptHumanAI->tView.vSecondaryViewConeAlpha);
  HIDWORD(ptHumanAI->tAIDetectionView.vSecondaryViewConeLength) = vViewConeAlpha_high;
  vSecondaryViewConeAlpha_low = LODWORD(ptHumanAI->tView.vSecondaryViewConeAlpha);
  ptHumanAI->pxActivationEntry1 = vSecondaryViewConeAlpha_high;
  vViewConeLength_low = (struct AIDetectionListItem_s *)LODWORD(ptHumanAI->tView.vViewConeLength);
  LODWORD(ptHumanAI->tAIDetectionView.vSecondaryViewConeLength) = vViewConeAlpha_low;
  vViewConeGamma_high = HIDWORD(ptHumanAI->tView.vViewConeGamma);
  ptHumanAI->isBetweenSectors = vSecondaryViewConeAlpha_low;
  vSecondaryViewConeGamma_high = HIDWORD(ptHumanAI->tView.vSecondaryViewConeGamma);
  ptHumanAI->ptCurrentHumanListItem = vViewConeLength_low;
  vSecondaryViewConeLength_high = HIDWORD(ptHumanAI->tView.vSecondaryViewConeLength);
  *((_DWORD *)&ptHumanAI->tAIDetectionView.isSecondaryViewUsed + 1) = vViewConeGamma_high;
  vSecondaryViewConeGamma_low = (void *)LODWORD(ptHumanAI->tView.vSecondaryViewConeGamma);
  *((_DWORD *)&ptHumanAI->pxActivationEntry2 + 1) = vSecondaryViewConeGamma_high;
  vSecondaryViewConeLength_low = LODWORD(ptHumanAI->tView.vSecondaryViewConeLength);
  *(&ptHumanAI->atAnimationEntries[0].nAnimation + 1) = vSecondaryViewConeLength_high;
  vX_low = LODWORD(ptHumanAI->tCommon.tTargetPosition.vX);
  ptHumanAI->pxActivationEntry2 = vSecondaryViewConeGamma_low;
  vViewConeLength_high = (struct QTask_s *)HIDWORD(ptHumanAI->tView.vViewConeLength);
  ptHumanAI->atAnimationEntries[0].nAnimation = vSecondaryViewConeLength_low;
  ptHumanAI->ptCurrentSectorQTask = vViewConeLength_high;
  LOBYTE(ptHumanAI->atAnimationEntries[0].vProbability) = 1;
  p_tFriendList = &ptHumanAI->tAIDetection.tFriendList;
  if ( vX_low <= 0 )
  {
    p_tFriendList->ptHead = (struct AIDetectionListItem_s *)((int)p_tFriendList->ptHead & ~1u);
  }
  else
  {
    p_tFriendList->ptHead = (struct AIDetectionListItem_s *)((int)p_tFriendList->ptHead | 1);
    LODWORD(ptHumanAI->tCommon.tTargetPosition.vX) = vX_low - 1;
  }
  AIDetection_RunDetection(
    (struct AIDetection_s *)&ptHumanAI->tAIDetection.tFriendList,
    (struct AIDetectionView_s *)&ptHumanAI->tAIDetectionView.tViewOrientation.tY.vY,
    igi2_frame.ptSourceQTask,
    (int)igi2_frame.ptSourceQTask[10].tQTaskRefList.ptTail);
  bQTaskMask = ptHumanAI->tAIDetection.atListItems[0].bQTaskMask;
  igi2_frame.v106 = *(_DWORD **)bQTaskMask;
  if ( igi2_frame.v106 )
  {
    while ( 1 )
    {
      v44 = *(_DWORD *)(*(_DWORD *)(bQTaskMask + 8) + 8);
      *(float *)&igi2_frame.v97 = 0.0;
      igi2_frame.v102 = v44;
      if ( v44 )
        ((void (__cdecl *)(int, _BYTE *))QTask_aatQTaskFinalEvent[AIDetection_eGetDetectionInfoQTaskEvent][*(unsigned __int16 *)(v44 + 36)].pfHandler)(
          v44,
          igi2_frame.v120);
      if ( igi2_frame.v103[2181] == 2 )
      {
        v45 = 0;
        while ( !*(_BYTE *)(bQTaskMask + v45 + 51) )
        {
          if ( ++v45 >= 3 )
          {
            if ( v44 )
            {
              qmemcpy((void *)(bQTaskMask + 64), igi2_frame.ptPosition, 0x18u);
              v44 = igi2_frame.v102;
            }
            break;
          }
        }
      }
      *(float *)&igi2_frame.nFireType[0].ptAmmoType = *(double *)&igi2_frame.ptSourceQTask[1].ptNext - *(double *)(bQTaskMask + 64);
      *(float *)&igi2_frame.nFireType[0].nAmmoInWeapon = *(double *)&igi2_frame.ptSourceQTask[1].tQTaskChildren.ptHead
                                            - *(double *)(bQTaskMask + 72);
      v46 = *(double *)&igi2_frame.ptSourceQTask[1].tQTaskChildren.ptTail - *(double *)(bQTaskMask + 80);
      v47 = sqrt(
              *(float *)&igi2_frame.nFireType[0].ptAmmoType * *(float *)&igi2_frame.nFireType[0].ptAmmoType
            + *(float *)&igi2_frame.nFireType[0].nAmmoInWeapon * *(float *)&igi2_frame.nFireType[0].nAmmoInWeapon
            + v46 * v46);
      *(float *)&igi2_frame.v98 = v47;
      if ( v47 > 40960.0 && ((ptHumanAI->anEventPriorityList[5] & 4) == 0 || *(_BYTE *)(bQTaskMask + 56)) )
        break;
LABEL_31:
      if ( *(float *)&igi2_frame.v98 < 10240.0 )
      {
        v51 = (_BYTE *)(bQTaskMask + 51);
        v52 = (_DWORD *)(bQTaskMask + 88);
        v53 = 3;
        do
        {
          *(v51 - 3) = 1;
          *v51 = 1;
          *v52++ = 0;
          ++v51;
          --v53;
        }
        while ( v53 );
      }
      if ( *(_BYTE *)(bQTaskMask + 54) && igi2_frame.v102 && LevelFlow_ptLevelFlow->nTick < (int)(igi2_frame.v97 + *(_DWORD *)(bQTaskMask + 28)) )
      {
        v54 = *(_BYTE *)(bQTaskMask + 56);
        *(_BYTE *)(bQTaskMask + 57) = 1;
        if ( v54 )
        {
          v56 = ptHumanAI + 1;
          v58 = (struct HumanAI_s *)(bQTaskMask + 64);
          v57 = ptHumanAI + 1;
        }
        else
        {
          v55 = 0;
          while ( !*(_BYTE *)(bQTaskMask + v55 + 51) )
          {
            if ( ++v55 >= 3 )
              goto LABEL_45;
          }
          v56 = (struct HumanAI_s *)&igi2_frame.ptPosition[v55];
          v57 = ptHumanAI + 1;
          v58 = v56;
        }
        qmemcpy(v57, v58, 0x18u);
        qmemcpy(&ptHumanAI->tCommon.nIgnoreVisibilityFactorTimer, v56, 0x18u);
      }
LABEL_45:
      v59 = 0;
      while ( !*(_BYTE *)(bQTaskMask + v59 + 51) )
      {
        if ( ++v59 >= 3 )
          goto LABEL_80;
      }
      if ( !igi2_frame.v102 || *(_BYTE *)(*(_DWORD *)(*(_DWORD *)(bQTaskMask + 8) + 8) + 1180) )
        goto LABEL_80;
      LODWORD(igi2_frame.v100) = 0;
      igi2_frame.v107 = 0;
      if ( *(float *)&igi2_frame.v98 < 10240.0 )
        goto LABEL_60;
      LOBYTE(ptHumanAI->atAnimationEntries[0].vProbability) = 0;
      v60 = 0;
      v61 = igi2_frame.ptPosition;
      while ( !AIDetection_IsPositionInsideView(
                 (struct AIDetectionView_s *)&ptHumanAI->tAIDetectionView.tViewOrientation.tY.vY,
                 v61)
           || !*(_BYTE *)(bQTaskMask + v60 + 51) )
      {
        ++v60;
        ++v61;
        if ( v60 >= 3 )
        {
          v62 = igi2_frame.v100;
          goto LABEL_58;
        }
      }
      v62 = 1;
LABEL_58:
      LOBYTE(ptHumanAI->atAnimationEntries[0].vProbability) = 1;
      if ( v62 || *(_BYTE *)(bQTaskMask + 56) )
      {
LABEL_60:
        if ( LevelFlow_ptLevelFlow->nTick >= (int)(igi2_frame.v97 + *(_DWORD *)(bQTaskMask + 28)) )
          goto LABEL_86;
      }
      if ( igi2_frame.v103[2181] == 2 )
      {
LABEL_86:
        v71 = (_BYTE *)(bQTaskMask + 51);
        *(_BYTE *)(bQTaskMask + 57) = 0;
        igi2_frame.v98 = bQTaskMask + 88;
        igi2_frame.v97 = 3;
        do
        {
          if ( *v71 )
          {
            if ( *(_DWORD *)igi2_frame.v98 )
            {
              ptPrev = igi2_frame.ptSourceQTask[33].ptNext[1].ptPrev;
              if ( ptPrev )
              {
                v73 = ptPrev->tQTaskChildren.ptTail;
                if ( v73 )
                {
                  if ( v73[16].tQTaskRefList.ptTail <= (struct QReference_s *)2 )
                  {
                    v74 = v73[32].ptParent->tQTaskChildren.ptHead;
                    v75 = *(_DWORD *)&v74[2].eQTaskType;
                    if ( v75 == Missile_eQTaskType
                      || v75 != GunShot_eQTaskType
                      || *(float *)&v74[3].ptPrev->tQTaskChildren.ptHead[1].ptPrev < (double)*(float *)(*(_DWORD *)igi2_frame.v98 + 64) )
                    {
                      *v71 = 0;
                    }
                  }
                }
              }
            }
          }
          ++v71;
          v76 = igi2_frame.v97 == 1;
          igi2_frame.v98 += 4;
          --igi2_frame.v97;
        }
        while ( !v76 );
        igi2_frame.v108 = 33;
        v77 = 0;
        while ( !*(_BYTE *)(bQTaskMask + v77 + 51) )
        {
          if ( ++v77 >= 3 )
          {
            v63 = igi2_frame.v102;
            igi2_frame.v110 = 0;
            goto LABEL_74;
          }
        }
        v63 = igi2_frame.v102;
        igi2_frame.v108 = 21;
        LODWORD(ptHumanAI->tCommon.tTargetPosition.vX) = 150;
        igi2_frame.v110 = 0;
      }
      else
      {
        v63 = igi2_frame.v102;
        if ( *(_DWORD *)(bQTaskMask + 8) && QTask_IsQTaskTypeDerived(*(_WORD *)(igi2_frame.v102 + 36), HumanPlayer_eQTaskType) )
        {
          if ( (v64 = *(_DWORD *)(v63 + 1316), v64 == 1) && *(_DWORD *)(v63 + 1244) == 23
            || v64 == 2 && ((v65 = *(_DWORD *)(v63 + 1244), v65 == 75) || v65 == 80) )
          {
            if ( *(float *)&igi2_frame.v98 > 10240.0 )
              igi2_frame.v107 = 1;
          }
        }
        igi2_frame.v108 = 26;
        igi2_frame.v110 = 0;
        if ( !*(_BYTE *)(bQTaskMask + 56) )
        {
          *(_BYTE *)(bQTaskMask + 51) = 0;
          *(_BYTE *)(bQTaskMask + 52) = 0;
          *(_BYTE *)(bQTaskMask + 53) = 0;
        }
        if ( igi2_frame.v107 )
          goto LABEL_80;
      }
LABEL_74:
      if ( igi2_frame.v103[2181] == 2 && *(_WORD *)(v63 + 36) == HumanPlayer_eQTaskType )
        *(_BYTE *)(bQTaskMask + 58) = 1;
      igi2_frame.v109 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(bQTaskMask + 8) + 8) + 428);
      igi2_frame.v114 = *(_DWORD *)(*(_DWORD *)(bQTaskMask + 8) + 8);
      v66 = *(_DWORD *)(*(_DWORD *)(bQTaskMask + 8) + 8);
      igi2_frame.v112 = bQTaskMask + 64;
      igi2_frame.v113 = v66;
      igi2_frame.v111 = 0;
      igi2_frame.v115 = *(_DWORD *)(bQTaskMask + 88);
      v67 = HumanAI_eSendEventQTaskEvent;
      igi2_frame.v116 = *(_DWORD *)(bQTaskMask + 92);
      igi2_frame.v117 = *(_DWORD *)(bQTaskMask + 96);
      if ( HumanAI_eSendEventQTaskEvent == 512 )
      {
        v67 = QTask_NewQTaskEventFn(0, "HumanAISendEvent");
        HumanAI_eSendEventQTaskEvent = v67;
      }
      ((void (__cdecl *)(struct HumanAI_s *, int *))QTask_aatQTaskFinalEvent[v67][ptHumanAI->tQTask.eQTaskType].pfHandler)(
        ptHumanAI,
        &igi2_frame.v108);
LABEL_80:
      bQTaskMask = (unsigned int)igi2_frame.v106;
      igi2_frame.v106 = (_DWORD *)*igi2_frame.v106;
      if ( !igi2_frame.v106 )
        goto LABEL_81;
    }
    igi2_frame.v100 = (__int64)(*(float *)&igi2_frame.v98 * 2.441406286379788e-05 * ptHumanAI->tTweakParameters.vMinDelayBetweenFiring * 30.0);
    v48 = *(float *)&igi2_frame.v100;
    v49 = *(_WORD *)(v44 + 36);
    igi2_frame.v97 = igi2_frame.v100;
    if ( QTask_IsQTaskTypeDerived(v49, Human_eQTaskType) )
    {
      igi2_frame.v100 = (__int64)((1.0 - *(float *)(v44 + 1984)) * 30.0);
      LODWORD(v48) += igi2_frame.v100;
      *(float *)&igi2_frame.v97 = v48;
      eDifficultyLevel = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eDifficultyLevel;
      if ( eDifficultyLevel )
      {
        if ( eDifficultyLevel != GAMEDIFFICULTY_2 )
          goto LABEL_29;
        igi2_frame.v100 = (__int64)((double)igi2_frame.v97 * 1.149999976158142);
        v48 = *(float *)&igi2_frame.v100;
      }
      else
      {
        igi2_frame.v100 = (__int64)((double)igi2_frame.v97 * 1.2999999523162842);
        v48 = *(float *)&igi2_frame.v100;
      }
      *(float *)&igi2_frame.v97 = v48;
    }
LABEL_29:
    if ( SLODWORD(v48) >= 60 )
      igi2_frame.v97 = 60;
    goto LABEL_31;
  }
LABEL_81:
  nDetectionTick = ptHumanAI->tAIDetection.atListItems[0].nDetectionTick;
  v69 = *(_DWORD **)nDetectionTick;
  if ( *(_DWORD *)nDetectionTick )
  {
    do
    {
      v70 = 0;
      while ( !*(_BYTE *)(v70 + nDetectionTick + 51) )
      {
        if ( ++v70 >= 3 )
          goto LABEL_107;
      }
      v78 = *(_DWORD *)(*(_DWORD *)(nDetectionTick + 8) + 8);
      if ( v78 && *(_BYTE *)(v78 + 1180) )
      {
        igi2_frame.v108 = 22;
        igi2_frame.v110 = 256;
        igi2_frame.v109 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(nDetectionTick + 8) + 8) + 428);
        igi2_frame.v114 = *(_DWORD *)(*(_DWORD *)(nDetectionTick + 8) + 8);
        igi2_frame.v113 = *(_DWORD *)(*(_DWORD *)(nDetectionTick + 8) + 8);
        v79 = *(_DWORD *)(*(_DWORD *)(nDetectionTick + 8) + 8);
        v80 = HumanAI_eSendEventQTaskEvent;
        igi2_frame.v112 = v79 + 40;
        igi2_frame.v111 = 0;
        if ( HumanAI_eSendEventQTaskEvent == 512 )
        {
          v80 = QTask_NewQTaskEventFn(0, "HumanAISendEvent");
          HumanAI_eSendEventQTaskEvent = v80;
        }
        ((void (__cdecl *)(struct HumanAI_s *, int *))QTask_aatQTaskFinalEvent[v80][ptHumanAI->tQTask.eQTaskType].pfHandler)(
          ptHumanAI,
          &igi2_frame.v108);
      }
LABEL_107:
      nDetectionTick = (int)v69;
      v69 = (_DWORD *)*v69;
    }
    while ( v69 );
  }
LABEL_108:
  TargetQTask = HumanAI_GetTargetQTask(ptHumanAI, true);
  v82 = TargetQTask;
  if ( TargetQTask )
  {
    eQTaskType = TargetQTask->eQTaskType;
    if ( QTask_IsQTaskTypeDerived(TargetQTask->eQTaskType, Human_eQTaskType) )
    {
      v84 = ptHumanAI->tAIDetection.atListItems[0].bQTaskMask;
      if ( !*(_DWORD *)v84 || !v84 )
        goto LABEL_125;
      while ( *(struct QTask_s **)(*(_DWORD *)(v84 + 8) + 8) != v82 )
      {
        v84 = *(_DWORD *)v84;
        if ( !*(_DWORD *)v84 || !v84 )
          goto LABEL_125;
      }
      if ( *(_BYTE *)(v84 + 56) )
      {
        v86 = (struct real64x3_t *)(v84 + 64);
      }
      else
      {
        ((void (__cdecl *)(struct QTask_s *, _BYTE *))QTask_aatQTaskFinalEvent[AIDetection_eGetDetectionInfoQTaskEvent][(unsigned __int16)eQTaskType].pfHandler)(
          v82,
          igi2_frame.v120);
        v85 = 0;
        while ( !*(_BYTE *)(v85 + v84 + 51) )
        {
          if ( ++v85 >= 3 )
            goto LABEL_125;
        }
        v86 = &igi2_frame.ptPosition[v85];
      }
    }
    else
    {
      v86 = (struct real64x3_t *)&v82[1];
    }
    qmemcpy(&ptHumanAI[1], v86, 0x18u);
LABEL_125:
    qmemcpy(&ptHumanAI->tCommon.nIgnoreVisibilityFactorTimer, &ptHumanAI[1], 0x18u);
    ptHumanAI->avChannel[3] = 0.0;
    return;
  }
  Weapon_GetFireTypeAmmoInfoFromWeaponTypeItem(
    (struct Weapon_s *)ptHumanAI->tQTask.ptParent[33].ptNext,
    (struct WeaponTypeItem_s *)ptHumanAI->tQTask.ptParent[33].ptNext[1].ptPrev,
    0,
    igi2_frame.nFireType);
  igi2_frame.v100 = (__int64)((double)igi2_frame.nFireType[0].nRoundsPerClip * 0.8999999761581421);
  if ( igi2_frame.nFireType[0].nAmmoInWeapon < (int)igi2_frame.v100 )
  {
    ptNext = igi2_frame.ptSourceQTask[33].ptNext;
    if ( Game_eGameMode )
    {
      if ( Game_eGameMode != GAME_GAMEMODE_MULTIPLAYER )
      {
        LDebug_Error("Weapon: GameMode (%d) not defined", Game_eGameMode);
        abort();
      }
      igi2_frame.nFireType[0].ptAmmoType = (struct AmmoType_s *)1465078348;
      ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
      if ( Timer_isPerformanceCounter )
        PerformanceCounter = Timer_GetPerformanceCounter();
      else
        PerformanceCounter = GetTickCount();
      v90 = PerformanceCounter
          - Timer_nStartTime
          + (char *)ptNetManagerQTask[6].tQTaskRefList.ptMiddle
          - (char *)ptNetManagerQTask[6].tQTaskRefList.ptTail;
      igi2_frame.nFireType[0].nBulletsPerRound = (int)ptNext[16].tQTaskRefList.ptTail;
      v91 = ptNext[2].tQTaskChildren.ptTail;
      igi2_frame.nFireType[0].nAmmoInWeapon = v90;
      igi2_frame.nFireType[0].nAmmoAvailable = -1;
      if ( v91 )
      {
        LOBYTE(igi2_frame.nFireType[0].nRoundsPerClip) = 1;
        v92 = v91->tQTaskChildren.ptHead;
        if ( v92 )
        {
          ClientFromHumanQTask = NetManager_GetClientFromHumanQTask(v92);
          if ( ClientFromHumanQTask )
            igi2_frame.nFireType[0].nAmmoAvailable = ClientFromHumanQTask->eNetworkID;
        }
      }
      else
      {
        LOBYTE(igi2_frame.nFireType[0].nRoundsPerClip) = 0;
        igi2_frame.nFireType[0].nAmmoAvailable = 0;
      }
      NetManager_SendGameMessage(
        0,
        (int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle,
        NETWORKQUEUE_GUARANTEED,
        (struct NetManagerGameMessage_s *)igi2_frame.nFireType,
        0x14u);
      ptNext[1].tQTaskChildren.ptTail = (struct QTask_s *)5;
    }
    else if ( Weapon_eReloadQTaskEvent != 512 )
    {
      ((void (__cdecl *)(struct QTask_s *, struct WeaponGetFireTypeAmmoContext_s *))QTask_aatQTaskFinalEvent[Weapon_eReloadQTaskEvent][ptNext->eQTaskType].pfHandler)(
        ptNext,
        igi2_frame.nFireType);
    }
  }
  if ( igi2_frame.ptSourceQTask[31].ptPrev != (struct QTask_s *)12 && ptHumanAI->avChannel[42] == 0.0 )
  {
    if ( igi2_frame.v103[2156] <= 0 )
    {
      v94 = LODWORD(ptHumanAI->avChannel[3]) + 1;
      v95 = (int)(LODWORD(ptHumanAI->avChannel[3]) - 299) < 0;
      LODWORD(ptHumanAI->avChannel[3]) = v94;
      if ( !(v95 ^ __OFSUB__(v94, 300) | (v94 == 300)) && ptHumanAI->avChannel[40] == 0.0 )
      {
        ptHumanAI[1].tQTask.ptNext = nullptr;
        ptHumanAI[1].tQTask.ptPrev = nullptr;
        ptHumanAI[1].tQTask.tQTaskChildren.ptHead = nullptr;
        ptHumanAI[1].tQTask.tQTaskChildren.ptMiddle = nullptr;
        ptHumanAI[1].tQTask.tQTaskChildren.ptTail = nullptr;
        ptHumanAI[1].tQTask.tQTaskRefList.ptHead = nullptr;
        ptHumanAI->tCommon.nIgnoreVisibilityFactorTimer = 0;
        ptHumanAI->tCommon.nRollDisallowedTimer = 0;
        *(_DWORD *)&ptHumanAI->tCommon.isDetectionSoundPlayed = 0;
        ptHumanAI->tCommon.ptDoorQTaskRef = nullptr;
        ptHumanAI->tCommon.tAimPosition.vX = 0.0;
      }
    }
    else
    {
      qmemcpy(&igi2_frame.ptDest, igi2_frame.v103 + 1824, 0x18u);
      qmemcpy(&ptHumanAI[1], &igi2_frame.ptDest, 0x18u);
      qmemcpy(&ptHumanAI->tCommon.nIgnoreVisibilityFactorTimer, &igi2_frame.ptDest, 0x18u);
      ptHumanAI->avChannel[3] = 0.0;
    }
  }
}

// source: j/0/humanai/humanai.c:6294  [anchor-strings]
void __cdecl HumanAI_RunHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QReference_s **v27; };
    struct { char igi2_o1[4]; struct QTask_s *ptTail; };
    struct { char igi2_o2[8]; struct QTask_s *v29; };
    struct { char igi2_o3[12]; __int64 v30; };
    struct { char igi2_o4[20]; struct HumanAIEventContext_t v31; };
    char igi2_extent[108];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v1; // ebp
  struct QTask_s *ptParent; // esi
  struct QTask_s *v3; // ecx
  struct HumanAI_s *v4; // eax
  struct QTask_s *v5; // eax
  struct QReference_s *v6; // eax
  struct QTask_s *ptPrev; // eax
  int v8; // eax
  struct QTask_s *v9; // eax
  struct QTask_s *TargetQTask; // eax
  int v11; // edi
  struct QTask_s *v12; // ecx
  unsigned int v13; // esi
  struct QReference_s *v14; // eax
  struct QTask_s *CheapHeadBonePosition; // eax
  struct QTask_s **p_ptPrev; // ebx
  struct QTask_s **p_ptTail; // esi
  bool v18; // zf
  __int16 v19; // ax
  struct QTask_s *v20; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, struct QReference_s ***); // eax
  struct QTask_s *v22; // eax
  __int16 v23; // ax
  struct QReference_s **v24; // edi
  struct QTask_s *v25; // ebp
  void (__cdecl *v26)(struct QTask_s *, struct QReference_s ***); // eax

  v1 = ptQTask;
  ptParent = ptQTask->ptParent;
  v3 = ptParent->ptParent;
  igi2_frame.ptTail = ptParent[33].tQTaskChildren.ptTail;
  v4 = (struct HumanAI_s *)ptQTask;
  ptQTask = ptParent;
  igi2_frame.v29 = v3;
  HumanAI_UpdateIdleViewConeRotation(v4);
  HumanAI_FindCurrentSectorFromNodes((struct HumanAI_s *)v1);
  v5 = ptParent[34].tQTaskChildren.ptTail;
  igi2_frame.v30 = (__int64)(*(float *)&v1[745].tQTaskRefList.ptMiddle * (double)AnimController_nTicksPerFrame);
  v5[1].tQTaskRefList.ptTail = (struct QReference_s *)igi2_frame.v30;
  v6 = v1[110].tQTaskRefList.ptTail;
  if ( v6 )
    v1[110].tQTaskRefList.ptTail = (struct QReference_s *)((char *)v6 - 1);
  ptPrev = v1[749].ptPrev;
  if ( ptPrev )
    v1[749].ptPrev = (struct QTask_s *)((char *)ptPrev - 1);
  v8 = *(_DWORD *)&v1[110].eQTaskType;
  if ( v8 )
    *(_DWORD *)&v1[110].eQTaskType = v8 - 1;
  v9 = v1[99].tQTaskChildren.ptTail;
  if ( v9 )
    v1[99].tQTaskChildren.ptTail = (struct QTask_s *)((char *)v9 - 1);
  TargetQTask = HumanAI_GetTargetQTask((struct HumanAI_s *)v1, true);
  v11 = (int)&v1[111].ptPrev->ptNext + 1;
  BYTE2(v1[111].tQTaskChildren.ptHead) = TargetQTask != nullptr;
  v1[111].ptPrev = (struct QTask_s *)v11;
  *(_DWORD *)&v1[113].eQTaskType = 0;
  HumanAI_MaintainSoundQueue((struct HumanAI_s *)v1);
  v12 = v1->ptParent->ptParent;
  v13 = (int)v1[99].tQTaskRefList.ptHead & 0xFFFFFFFB;
  v1[99].tQTaskRefList.ptHead = (struct QReference_s *)v13;
  if ( (int)v12[216].tQTaskChildren.ptHead > 0 )
    v1[99].tQTaskRefList.ptHead = (struct QReference_s *)(v13 | 4);
  if ( ((int)v1[99].tQTaskRefList.ptHead & 4) != 0 )
    goto LABEL_20;
  v14 = v1[222].tQTaskRefList.ptTail;
  if ( !v14->ptNext || !v14 )
    goto LABEL_17;
  while ( !BYTE1(v14[4].pxObject) )
  {
    v14 = v14->ptNext;
    if ( !v14->ptNext || !v14 )
      goto LABEL_17;
  }
  if ( sub_46D9F0((int)v1) )
  {
LABEL_20:
    HumanAIContent_UseCombatView((struct HumanAI_s *)v1);
    v1[114].tQTaskRefList.ptMiddle = (struct QReference_s *)1065353216;
  }
  else
  {
LABEL_17:
    HumanAIContent_UseIdleView((struct HumanAI_s *)v1);
  }
  if ( BYTE2(igi2_frame.ptTail[12].tQTaskRefList.ptTail) )
  {
    qmemcpy(&v1[1].ptParent, &igi2_frame.ptTail[12].ptParent, 0x18u);
    qmemcpy(&v1[3], &igi2_frame.ptTail[13].tQTaskChildren.ptTail, sizeof(struct QTask_s));
    qmemcpy(&v1[2].tQTaskChildren.ptTail, &igi2_frame.ptTail[12].ptParent, 0x18u);
    p_ptTail = &igi2_frame.ptTail[13].tQTaskChildren.ptTail;
  }
  else
  {
    CheapHeadBonePosition = HumanSoldier_GetCheapHeadBonePosition(
                              ptQTask,
                              nullptr,
                              (struct real64x3_t *)&v1[1].ptParent);
    p_ptPrev = &CheapHeadBonePosition[3].ptPrev;
    qmemcpy(&v1[3], &CheapHeadBonePosition[3].ptPrev, sizeof(struct QTask_s));
    HumanSoldier_GetCheapHeadBonePosition(
      CheapHeadBonePosition,
      nullptr,
      (struct real64x3_t *)&v1[2].tQTaskChildren.ptTail);
    p_ptTail = p_ptPrev;
  }
  v18 = v1[738].ptParent == nullptr;
  qmemcpy(&v1[4], p_ptTail, sizeof(struct QTask_s));
  if ( !v18 && v1[728].tQTaskChildren.ptHead )
  {
    if ( HIBYTE(v1[111].tQTaskChildren.ptMiddle) )
    {
      HumanAI_RunDeathChecks((struct HumanAI_s *)v1);
      if ( !v1[118].ptParent->ptNext )
      {
        igi2_frame.v31.ptReferenceQTask = nullptr;
        igi2_frame.v31.ptHumanOriginatorQTask = nullptr;
        igi2_frame.v31.eTeam = -1;
        memset(&igi2_frame.v31.bFlags, 0, 12);
        if ( AISquad_GetState(igi2_frame.v29) )
          igi2_frame.v31.eEvent = 30;
        else
          igi2_frame.v31.eEvent = 4;
        HumanAI_SendEventSpecificQTask(v1, &igi2_frame.v31);
      }
    }
    else
    {
      igi2_frame.v27 = &v1[111].tQTaskRefList.ptTail;
      v19 = Human_eHumanUpdateQTaskEvent;
      if ( Human_eHumanUpdateQTaskEvent == 512 )
      {
        v19 = QTask_NewQTaskEventFn(0, "HumanUpdate");
        Human_eHumanUpdateQTaskEvent = v19;
      }
      v20 = v1->ptParent;
      pfHandler = (void (__cdecl *)(struct QTask_s *, struct QReference_s ***))QTask_aatQTaskFinalEvent[v19][v20->eQTaskType].pfHandler;
      if ( pfHandler )
        pfHandler(v20, &igi2_frame.v27);
      HumanAI_FindWeapons((struct HumanAI_s *)v1);
      HIBYTE(v1[111].tQTaskChildren.ptMiddle) = 1;
      memset(&igi2_frame.v31, 0, 12);
      List_AddTail(&igi2_frame.v31, (int)&v1[85]);
      HumanAI_RunScriptEvent((struct HumanAI_s *)v1, 0, -1);
      Node_Remove(&igi2_frame.v31);
    }
    HumanAI_RunScript((struct HumanAI_s *)v1);
    HumanAI_RunActionStack((struct HumanAI_s *)v1);
    HumanAI_RunDetection((struct HumanAI_s *)v1, (char *)&ptQTask);
    v22 = ptQTask;
    LOBYTE(v1[111].tQTaskChildren.ptMiddle) = 0;
    if ( BYTE1(v22[29].tQTaskRefList.ptHead) )
    {
      v23 = Human_eHumanUpdateQTaskEvent;
      v24 = &v1[111].tQTaskRefList.ptTail;
      igi2_frame.v27 = &v1[111].tQTaskRefList.ptTail;
      if ( Human_eHumanUpdateQTaskEvent == 512 )
      {
        v23 = QTask_NewQTaskEventFn(0, "HumanUpdate");
        Human_eHumanUpdateQTaskEvent = v23;
      }
      v25 = v1->ptParent;
      v26 = (void (__cdecl *)(struct QTask_s *, struct QReference_s ***))QTask_aatQTaskFinalEvent[v23][v25->eQTaskType].pfHandler;
      if ( v26 )
        v26(v25, &igi2_frame.v27);
      memset(v24, 0, 0xFCu);
    }
  }
}

// source: j/0/humanai/humanai.c:6902  [anchor-caller]
void __cdecl HumanAI_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptMiddle; // eax
  struct QTask_s *ptParent; // eax
  struct QTask_s *v3; // eax
  void *v4; // eax
  struct QTask_s *ptNext; // eax
  int v6; // ecx
  struct QReference_s *v7; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  struct QTask_s *i; // eax
  struct QTask_s *j; // eax
  struct QTask_s *k; // esi
  void (__cdecl *v12)(struct QTask_s *, struct QTask_s *); // eax
  struct QTask_s *ptHead; // eax
  struct QTask_s *m; // eax

  ptQTask[728].tQTaskChildren.ptHead = nullptr;
  AIGraphAStarSearch_Clear((struct AIGraphAStarSearchData_s *)&ptQTask[7].tQTaskChildren);
  ptQTask[748].ptParent = (struct QTask_s *)ptQTask[748].tQTaskRefList.ptTail;
  HumanAI_ClearMovementQueue((struct HumanAI_s *)ptQTask);
  ptMiddle = ptQTask[749].tQTaskChildren.ptMiddle;
  if ( ptMiddle )
  {
    QReference_Delete((struct QReference_s *)ptMiddle, &QTask_tQTaskRefPool);
    ptQTask[749].tQTaskChildren.ptMiddle = nullptr;
  }
  ptParent = ptQTask[738].ptParent;
  if ( ptParent )
    Script_Delete((struct Script_s *)ptParent);
  HumanAI_ClearMovementQueue((struct HumanAI_s *)ptQTask);
  if ( BYTE2(ptQTask[749].tQTaskChildren.ptHead) )
  {
    v3 = ptQTask[749].tQTaskChildren.ptMiddle;
    if ( v3 )
    {
      QReference_Delete((struct QReference_s *)v3, &QTask_tQTaskRefPool);
      ptQTask[749].tQTaskChildren.ptMiddle = nullptr;
    }
    BYTE2(ptQTask[749].tQTaskChildren.ptHead) = 0;
  }
  HumanAI_RemoveEvents((struct HumanAI_s *)ptQTask);
  v4 = *(void **)&ptQTask[725].eQTaskType;
  if ( v4 )
    HumanAI_ClearActivationEntry(v4);
  ptNext = ptQTask[726].ptNext;
  if ( ptNext )
    HumanAI_ClearActivationEntry(ptNext);
  v6 = 0;
  while ( 1 )
  {
    v7 = Level_atLevelQTaskID[v6];
    if ( v7 )
    {
      if ( v7->pxObject == ptQTask )
        break;
    }
    if ( ++v6 >= 4096 )
      goto LABEL_21;
  }
  if ( v6 >= 0 )
  {
    pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Level_eRemoveLevelScriptSymbolsEvent][ptQTask->eQTaskType].pfHandler;
    if ( pfHandler )
      pfHandler(ptQTask);
  }
LABEL_21:
  for ( i = ptQTask[6].ptParent; i->ptNext && i; i = ptQTask[6].ptParent )
    Node_Remove(i);
  for ( j = ptQTask[99].ptPrev; j->ptNext && j; j = ptQTask[99].ptPrev )
    Node_Remove(j);
  for ( k = ptQTask[118].ptParent; k->ptNext && k; k = ptQTask[118].ptParent )
  {
    v12 = *(void (__cdecl **)(struct QTask_s *, struct QTask_s *))&k->eQTaskType;
    if ( v12 )
      v12(ptQTask, k);
    Node_Remove(k);
    ptHead = k[1].tQTaskChildren.ptHead;
    LOBYTE(k[1].tQTaskChildren.ptMiddle) = 0;
    if ( ptHead )
    {
      ptHead->ptPrev = nullptr;
      ptHead->ptNext = nullptr;
      List_AddTail(ptHead, (int)&ptQTask[215].tQTaskChildren);
      k[1].tQTaskChildren.ptHead = nullptr;
    }
  }
  for ( m = ptQTask[215].tQTaskChildren.ptHead; m->ptNext && m; m = ptQTask[215].tQTaskChildren.ptHead )
    Node_Remove(m);
  if ( LOBYTE(ptQTask[111].tQTaskChildren.ptHead) )
    AIDetection_ClearDetection((struct AIDetection_s *)&ptQTask[222]);
}

// source: j/0/humanai/humanai.c:6999  [anchor-caller]
void __cdecl HumanAI_SendEventHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { char v26; };
    struct { char igi2_o1[1]; struct QTask_s *v27; };
    struct { char igi2_o2[5]; int iTeam; };
    struct { char igi2_o3[9]; struct CollisionEvaluateContext_s v29; };
    struct { char igi2_o4[17]; int a2; };
    struct { char igi2_o5[21]; struct real32x3_t ptEvalContext; };
    struct { char igi2_o6[37]; struct real64x3_t ptWorldPosition; };
    char igi2_extent[65];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v2; // edx
  bool v3; // zf
  struct QTask_s *ptParent; // ecx
  struct QTask_s *v5; // eax
  int v7; // ebx
  int v8; // edi
  int v9; // esi
  struct real64x3_t *v10; // ecx
  struct real64x3_t *p_ptParent; // edx
  char IsPositionInsideView; // al
  char v13; // al
  int v14; // eax
  struct HumanAIEvent_t *Event; // eax
  struct HumanAIEvent_t *v16; // ebx
  double NoiseLevelAtPosition; // st7
  double *v18; // eax
  int v19; // edx
  int v20; // eax
  struct QTask_s **v21; // ecx
  BOOL v22; // esi
  struct AIDetectionListItem_s *v23; // eax
  char *aisFullVisible; // ecx
  int v25; // edx
  float pxContexta = *(float *)&pxContext; // [esp+5Ch] [ebp+8h] ARGSLOT

  v2 = ptQTask;
  v3 = HIBYTE(ptQTask[111].tQTaskChildren.ptHead) == 0;
  ptParent = ptQTask->ptParent;
  v5 = ptParent->ptParent;
  v7 = *((_DWORD *)pxContext + 2);
  igi2_frame.v27 = ptParent;
  igi2_frame.iTeam = (int)v5;
  igi2_frame.v26 = 1;
  *(_DWORD *)&igi2_frame.v29.isEvaluate = ptQTask[111].tQTaskChildren.ptTail;
  if ( v3 && BYTE1(ptParent[29].tQTaskRefList.ptHead) && ptQTask[738].ptParent && v5 )
  {
    v8 = *(_DWORD *)pxContext;
    if ( HIBYTE(ptQTask[111].tQTaskChildren.ptMiddle) )
    {
      if ( !*((_BYTE *)&ptQTask[83].ptParent + v8) )
        return;
    }
    else if ( v8 )
    {
      return;
    }
    v9 = *((_DWORD *)pxContext + 9);
    if ( v9 && QTask_IsQTaskTypeDerived(*(_WORD *)(v9 + 36), HumanSoldier_eQTaskType) )
    {
      if ( sub_4F8050(v9, igi2_frame.iTeam) )
        return;
      v2 = ptQTask;
    }
    switch ( v8 )
    {
      case 14:
      case 19:
        v2[110].tQTaskRefList.ptTail = (struct QReference_s *)300;
        goto LABEL_17;
      case 24:
      case 34:
        if ( (struct QTask_s *)v9 != igi2_frame.v27 )
          goto LABEL_17;
        return;
      default:
LABEL_17:
        igi2_frame.a2 = (int)&v2[85] + 12 * *(_DWORD *)pxContext;
        if ( !v7 )
          goto LABEL_59;
        if ( (v7 & 0x100) != 0 )
        {
          LOWORD(v7) = v7 & 0xFEFF;
          if ( *((struct QTask_s **)pxContext + 9) == igi2_frame.v27 )
            igi2_frame.v26 = 0;
        }
        if ( (v7 & 2) == 0 )
          goto LABEL_25;
        v10 = *((struct real64x3_t **)pxContext + 4);
        p_ptParent = (struct real64x3_t *)&v2[1].ptParent;
        LOWORD(v7) = v7 & 0xFFFD;
        if ( *((float *)pxContext + 3) < Real64x3_Distance(v10, p_ptParent) )
        {
          igi2_frame.v26 = 0;
LABEL_24:
          v2 = ptQTask;
          goto LABEL_25;
        }
        if ( (v7 & 0x400) == 0 )
          goto LABEL_24;
        *(double *)&igi2_frame.ptEvalContext.vX = Real64x3_Distance(v10, p_ptParent);
        pxContexta = AmbientArea_GetNoiseLevelAtPosition(v10);
        NoiseLevelAtPosition = AmbientArea_GetNoiseLevelAtPosition((struct real64x3_t *)&igi2_frame.v27[1]);
        if ( pxContexta <= NoiseLevelAtPosition )
          pxContexta = NoiseLevelAtPosition;
        if ( pxContexta >= 1.0 )
          pxContexta = 1.0;
        v2 = ptQTask;
        if ( (1.0 - pxContexta) * *(float *)&igi2_frame.v29.isEvaluate * *((float *)pxContext + 3) < *(double *)&igi2_frame.ptEvalContext.vX )
          igi2_frame.v26 = 0;
LABEL_25:
        if ( (v7 & 1) != 0 )
        {
          if ( igi2_frame.v26 )
          {
            IsPositionInsideView = HumanAI_IsPositionInsideView(
                                     (struct HumanAIView_s *)&v2[1].ptParent,
                                     *((struct real64x3_t **)pxContext + 4),
                                     false);
            v2 = ptQTask;
            LOWORD(v7) = v7 & 0xFFFE;
            if ( !IsPositionInsideView )
              igi2_frame.v26 = 0;
          }
        }
        if ( (v7 & 0x200) != 0 )
        {
          if ( igi2_frame.v26 )
          {
            v13 = HumanAI_IsPositionInsideView(
                    (struct HumanAIView_s *)&v2[1].ptParent,
                    *((struct real64x3_t **)pxContext + 4),
                    true);
            v2 = ptQTask;
            if ( !v13 )
              igi2_frame.v26 = 0;
          }
        }
        if ( (v7 & 4) != 0 )
        {
          if ( igi2_frame.v26 )
          {
            v14 = *((_DWORD *)pxContext + 9);
            LOBYTE(v7) = v7 & 0xFB;
            if ( !v14 || QTask_IsQTaskTypeDerived(*(_WORD *)(v14 + 36), Human_eQTaskType) == false )
              igi2_frame.v26 = 0;
          }
        }
        if ( (v7 & 0xC) != 0 )
        {
          if ( igi2_frame.v26 )
          {
            LOBYTE(v7) = v7 & 0xF3;
            if ( *(_BYTE *)(*((_DWORD *)pxContext + 9) + 1180) )
              igi2_frame.v26 = 0;
          }
        }
        if ( (v7 & 0x14) != 0 )
        {
          if ( igi2_frame.v26 )
          {
            LOBYTE(v7) = v7 & 0xEB;
            if ( !*(_BYTE *)(*((_DWORD *)pxContext + 9) + 1180) )
              igi2_frame.v26 = 0;
          }
        }
        if ( (v7 & 0x20) != 0 )
        {
          if ( igi2_frame.v26 )
          {
            LOBYTE(v7) = v7 & 0xDF;
            if ( *((struct QReference_s **)pxContext + 1) != igi2_frame.v27[10].tQTaskRefList.ptTail )
              igi2_frame.v26 = 0;
          }
        }
        if ( (v7 & 0x40) != 0 )
        {
          if ( igi2_frame.v26 )
          {
            LOBYTE(v7) = v7 & 0xBF;
            if ( *((struct QReference_s **)pxContext + 1) == igi2_frame.v27[10].tQTaskRefList.ptTail )
              igi2_frame.v26 = 0;
          }
        }
        if ( (v7 & 0x80u) == 0 )
          goto LABEL_58;
        if ( igi2_frame.v26 )
        {
          HumanSoldier_GetCheapHeadBonePosition(igi2_frame.v27, &igi2_frame.ptEvalContext, &igi2_frame.ptWorldPosition);
          if ( World_LineOfSight(
                 Game_ptGame->ptWorld,
                 &igi2_frame.ptWorldPosition,
                 *((struct real64x3_t **)pxContext + 4),
                 AIDetection_eLineOfSightQTaskEvent,
                 &igi2_frame.v29,
                 Forest_bQTaskGroup | 0x98000000,
                 WORLD_DYNCUBETREE_CATEGORY_ALL,
                 (struct LineOfSightOutputContext_s *)&igi2_frame.ptEvalContext) )
          {
            v2 = ptQTask;
LABEL_58:
            if ( igi2_frame.v26 )
            {
LABEL_59:
              Event = HumanAI_CreateEvent((struct HumanAI_s *)v2, (struct HumanAIEventContext_t *)pxContext);
              v16 = Event;
              if ( Event )
              {
                switch ( *(_DWORD *)pxContext )
                {
                  case 0xE:
                  case 0x17:
                  case 0x18:
                  case 0x1F:
                  case 0x22:
                  case 0x2A:
                    Event->tDirection.vX = *((float *)pxContext + 5);
                    Event->tDirection.vY = *((float *)pxContext + 6);
                    Event->tDirection.vZ = *((float *)pxContext + 7);
                    break;
                  case 0xF:
                  case 0x13:
                    Event->tDirection.vX = *((float *)pxContext + 5);
                    Event->tDirection.vY = *((float *)pxContext + 6);
                    Event->tDirection.vZ = *((float *)pxContext + 7);
                    Event->tDirection.vX = Event->tDirection.vX * -1.0;
                    Event->tDirection.vY = Event->tDirection.vY * -1.0;
                    Event->tDirection.vZ = Event->tDirection.vZ * -1.0;
                    break;
                  default:
                    v18 = *((double **)pxContext + 4);
                    if ( v18 )
                    {
                      v16->tDirection.vX = *v18 - *(double *)&igi2_frame.v27[1].ptNext;
                      v16->tDirection.vY = *(double *)(*((_DWORD *)pxContext + 4) + 8)
                                         - *(double *)&igi2_frame.v27[1].tQTaskChildren.ptHead;
                      v16->tDirection.vZ = *(double *)(*((_DWORD *)pxContext + 4) + 16)
                                         - *(double *)&igi2_frame.v27[1].tQTaskChildren.ptTail;
                    }
                    else
                    {
                      LODWORD(v16->tPosition.vX) = 0;
                      HIDWORD(v16->tPosition.vX) = 0;
                      LODWORD(v16->tPosition.vY) = 0;
                      HIDWORD(v16->tPosition.vY) = 0;
                      LODWORD(v16->tPosition.vZ) = 0;
                      HIDWORD(v16->tPosition.vZ) = 0;
                      v16->tDirection.vX = 0.0;
                      v16->tDirection.vY = 0.0;
                      v16->tDirection.vZ = 0.0;
                    }
                    break;
                }
                v19 = *((_DWORD *)pxContext + 9);
                if ( v19
                  && QTask_IsQTaskTypeDerived(*(_WORD *)(v19 + 36), HumanSoldier_eQTaskType)
                  && (*(_DWORD *)pxContext == 22 || *(_DWORD *)pxContext == 34) )
                {
                  sub_4F8090((_DWORD *)v19, igi2_frame.iTeam);
                }
                if ( *(_DWORD *)pxContext == 39 )
                {
                  v20 = 0;
                  if ( AIDetection_ptDetectionQTaskList->nTask > 0 )
                  {
                    v21 = AIDetection_ptDetectionQTaskList->ptQTask;
                    while ( *v21 != *((struct QTask_s **)pxContext + 9) )
                    {
                      ++v20;
                      ++v21;
                      if ( v20 >= AIDetection_ptDetectionQTaskList->nTask )
                        goto LABEL_89;
                    }
                    v22 = AIDetection_FindMatchingListItem(
                            (struct AIDetection_s *)&ptQTask[222],
                            *((struct QTask_s **)pxContext + 9)) == nullptr;
                    v23 = AIDetection_NewListItem(
                            (struct AIDetection_s *)&ptQTask[222],
                            (struct AIDetectionList_s *)&ptQTask[222].tQTaskRefList.ptTail,
                            *((struct QTask_s **)pxContext + 9));
                    aisFullVisible = v23->aisFullVisible;
                    v25 = 3;
                    do
                    {
                      *(aisFullVisible - 3) = 1;
                      *aisFullVisible++ = 1;
                      --v25;
                    }
                    while ( v25 );
                    v23->isHasBeenFullVisible = 1;
                    v23->isCreatedByGunShot = 1;
                    if ( v22 )
                    {
                      v23->nTicksToConeUpdate = 52;
                      v23->nTicksToFullUpdate = 52;
                    }
                    qmemcpy(
                      &v16->tPosition,
                      HumanView_GetOriginalViewPosition(&v23->tLastVisiblePosition, *((struct QTask_s **)pxContext + 9)),
                      sizeof(v16->tPosition));
                  }
LABEL_89:
                  ptQTask[749].ptNext = (struct QTask_s *)150;
                }
                switch ( v16->eEvent )
                {
                  case 9:
                  case 0xA:
                  case 0xB:
                  case 0xC:
                  case 0xD:
                  case 0x13:
                  case 0x17:
                  case 0x1A:
                  case 0x1F:
                  case 0x29:
                  case 0x2A:
                  case 0x2C:
                    AISquad_RefreshTeamFormationPositions((struct QTask_s *)&v16->tPosition, igi2_frame.iTeam);
                    break;
                  default:
                    break;
                }
                List_AddTail(v16, igi2_frame.a2);
              }
            }
          }
        }
        break;
    }
  }
}

// source: j/0/humanai/humanai.c:7364  [size]
void __cdecl HumanAI_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = HumanAI_ptParameterList;
}

// source: j/0/humanai/humanai.c:7380  [anchor-strings]
void __cdecl HumanAI_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptParent; // eax
  int v3; // ecx
  struct QReference_s *v4; // eax
  int v5; // eax
  struct QReference_s *v6; // ecx

  HumanAI_ptCurrentHumanAI = (struct HumanAI_s *)ptQTask;
  ptQTask[110].tQTaskChildren.ptTail = (struct QTask_s *)Script_ParseLineInt32((char *)&ptQTask[738].eQTaskType);
  ptQTask[110].tQTaskRefList.ptHead = (struct QReference_s *)Script_ParseLineInt32((char *)&ptQTask[740].tQTaskRefList);
  ptParent = ptQTask[738].ptParent;
  if ( ptParent )
  {
    Script_Delete((struct Script_s *)ptParent);
    ptQTask[738].ptParent = nullptr;
  }
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
      goto LABEL_15;
  }
  if ( v3 != -1 )
  {
    v5 = 0;
    while ( 1 )
    {
      v6 = Level_atLevelQTaskID[v5];
      if ( v6 )
      {
        if ( v6->pxObject == ptQTask )
          break;
      }
      if ( ++v5 >= 4096 )
      {
        v5 = -1;
        break;
      }
    }
    sprintf((char *const)&ptQTask[728].tQTaskChildren.ptMiddle, "MISSION:AI/%d.qsc", v5);
    ptQTask[738].ptParent = (struct QTask_s *)Script_New((char *)&ptQTask[728].tQTaskChildren.ptMiddle);
    ptQTask[109].ptNext = nullptr;
  }
LABEL_15:
  AIDetection_InitDetection(
    (struct AIDetection_s *)&ptQTask[222],
    (int)ptQTask->ptParent[10].tQTaskRefList.ptTail,
    6u,
    Human_bAIDetectionQTaskMask,
    4,
    8);
  LOBYTE(ptQTask[111].tQTaskChildren.ptHead) = 1;
}

// source: j/0/humanai/humanai.c:7444  [anchor-caller]
void __cdecl HumanAI_UpdateInternalDataAfterLoadHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptParent; // ebp
  struct QTask_s *v2; // ebx
  struct QTask_s *v3; // edi
  struct AIGraph_t *Graph; // eax
  struct AIGraphNode_s *v5; // edi
  struct Game_s *v6; // eax
  unsigned int v7; // ebp
  unsigned int v8; // edi
  unsigned int v9; // edx
  struct QTask_s *ptHead; // eax
  struct AIGraphNode_s *ptNode; // [esp+14h] [ebp-4h] BYREF

  ptParent = ptQTask->ptParent;
  v2 = ptParent->ptParent;
  v3 = ptQTask[110].ptParent;
  if ( v3 != (struct QTask_s *)-1 )
  {
    Graph = (struct AIGraph_t *)Graph_GetGraph((int)v3);
    ptQTask[728].tQTaskChildren.ptHead = &Graph->tGraph.tQTask;
    if ( Graph )
    {
      AIGraph_GetClosestNode(&ptNode, Graph, (struct real64x3_t *)&ptQTask->ptParent[1], true);
      v5 = ptNode;
      if ( ptNode )
      {
        HumanAI_SetCurrentNode((struct HumanAI_s *)ptQTask, ptNode->tGraphNode.nID);
        *(_DWORD *)&ptQTask[750].eQTaskType = v5->tGraphNode.nID;
      }
    }
  }
  ptQTask[750].tQTaskRefList.ptMiddle = (struct QReference_s *)ptParent[3].tQTaskChildren.ptHead;
  ptQTask[750].tQTaskRefList.ptTail = ptParent[3].tQTaskRefList.ptHead;
  ptQTask[750].ptParent = ptParent[3].ptParent;
  HumanAIConfig_SetAISettingsFromConfig((struct HumanAI_s *)ptQTask);
  v6 = Game_ptGame;
  v7 = (Game_ptGame->tRunRandomState.anRandom[0] >> 7) ^ Game_ptGame->tRunRandomState.anRandom[2];
  v8 = v7 ^ Game_ptGame->tRunRandomState.anRandom[1];
  v9 = v8 + Game_ptGame->tRunRandomState.anRandom[0];
  Game_ptGame->tRunRandomState.anRandom[0] = v9;
  v6->tRunRandomState.anRandom[2] = v7;
  v6->tRunRandomState.anRandom[1] = v8;
  ptQTask[6].tQTaskRefList.ptTail = (struct QReference_s *)(v9 % 0x96);
  if ( v2[1].ptParent )
    ptHead = v2[1].ptNext->tQTaskChildren.ptHead;
  else
    ptHead = nullptr;
  if ( ptHead == ptQTask )
  {
    *(_DWORD *)&v2[217].eQTaskType = ptQTask[742].ptPrev;
    v2[217].ptParent = ptQTask[742].tQTaskChildren.ptHead;
  }
}

// source: j/0/humanai/humanai.c:7506  [size]
void __cdecl HumanAI_CommunicationHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: j/0/humanai/humanai.c:7547  [anchor-mhash]
void __cdecl HumanAI_AreaActivateSideKickCB(struct AreaActivateContext_s *ptContext)
{
  unsigned __int16 v1; // dx
  struct QTask_s **ptQTask; // edi
  int nTask; // ebp
  struct QTask_s *v4; // esi
  struct QTask_s *FirstChildOfType; // eax
  struct real64x3_t ptPos; // [esp+10h] [ebp-18h] BYREF

  if ( Human_ptQTaskList->nTask > 0 )
  {
    v1 = HumanAI_eQTaskType;
    ptQTask = Human_ptQTaskList->ptQTask;
    nTask = Human_ptQTaskList->nTask;
    do
    {
      v4 = *ptQTask;
      FirstChildOfType = QTask_GetFirstChildOfType(*ptQTask, v1);
      if ( FirstChildOfType && ((int)FirstChildOfType[99].tQTaskRefList.ptHead & 1) != 0 )
      {
        sub_580CA0((int)v4, &ptPos.vX);
        if ( AreaActivateQTask_IsInsideArea(ptContext->ptAreaActivateQTask, &ptPos) )
          ++ptContext->nHitCount;
      }
      ++ptQTask;
      --nTask;
    }
    while ( nTask );
  }
}

// source: j/0/humanai/humanai.c:7601  [anchor-strings]
void __cdecl HumanAI_Open()
{
  #pragma pack(push, 1)
  union
  {
    struct { char v13[256]; };
    struct { char igi2_o1[256]; char Buffer[256]; };
    struct { char igi2_o2[512]; char v15[260]; };
    char igi2_extent[772];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v0; // edi
  int i; // esi
  unsigned __int16 BaseQTaskType; // ax
  __int16 v3; // ax
  unsigned __int16 v4; // si
  __int16 v5; // ax
  struct ParameterList_s *v6; // eax
  unsigned __int16 v7; // si
  struct ParameterList_s *v8; // eax
  int v9; // edx
  signed int j; // esi
  struct HumanAIMovementQueueItem_t *v11; // eax
  struct HumanAIActivationEntry_t *v12; // eax

  v0 = 0;
  for ( i = 0; i < 256; i += 32 )
  {
    sprintf(&igi2_frame.Buffer[i], "nCurrentCommandQTaskID%i", v0);
    sprintf(&igi2_frame.v13[i], "nLastEndCommandQTaskID%i", v0);
    sprintf(&igi2_frame.v15[i], "nPatroPath%i", v0++);
  }
  BaseQTaskType = QTask_GetBaseQTaskType();
  HumanAI_eQTaskType = QTask_NewQTaskType("HumanAI", 30040, BaseQTaskType, 0, 0);
  v3 = QTask_NewQTaskEventFn(0, "HumanAICommunicateEvent");
  v4 = HumanAI_eQTaskType;
  HumanAI_eCommunicationEvent = v3;
  QTask_LinkQTaskEventHandlerFn(HumanAI_eQTaskType, 0, HumanAI_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v4, 1, HumanAI_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v4, 2, HumanAI_DeleteHandler);
  v5 = HumanAI_eSendEventQTaskEvent;
  if ( HumanAI_eSendEventQTaskEvent == 512 )
  {
    v5 = QTask_NewQTaskEventFn(0, "HumanAISendEvent");
    v4 = HumanAI_eQTaskType;
    HumanAI_eSendEventQTaskEvent = v5;
  }
  QTask_LinkQTaskEventHandlerFn(v4, v5, HumanAI_SendEventHandler);
  QTask_LinkQTaskEventHandlerFn(
    v4,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))HumanAI_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v4, ParameterList_eUpdateInternalDataQTaskEvent, HumanAI_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v4,
    HumanAI_eCommunicationEvent,
    (void (__cdecl *)(struct QTask_s *, void *))HumanAI_CommunicationHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v4,
    Level_eRegisterLevelScriptSymbolsEvent,
    HumanAI_RegisterScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v4, Level_eRemoveLevelScriptSymbolsEvent, HumanAI_RemoveScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v4,
    Level_eUpdateInternalDataAfterLoadEvent,
    HumanAI_UpdateInternalDataAfterLoadHandler);
  QTask_LinkQTaskEventHandlerFn(v4, 5, nullptr);
  QTask_LinkQTaskEventHandlerFn(
    v4,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveNoChildrenHandler);
  v6 = (struct ParameterList_s *)Mem_AllocFn(92, 4);
  v6->nParameters = 0;
  v6->nMaxParameters = 4;
  v6->ptParameterListItem = (struct ParameterListItem_s *)&v6[1];
  HumanAI_ptParameterList = v6;
  ParameterList_AddParameter(v6, 0x7374u, Level_eParameterTypeString32, "AI Type", 7u, nullptr);
  ParameterList_AddParameter(HumanAI_ptParameterList, 0x73B4u, Level_eParameterTypeString32, "Anim Type", 7u, nullptr);
  ParameterList_AddParameter(HumanAI_ptParameterList, 0x1150u, Level_eParameterTypeInt32, "Graph ID", 7u, nullptr);
  ParameterList_AddParameter(
    HumanAI_ptParameterList,
    0x71CCu,
    Level_eParameterTypeScriptFile,
    "Script File",
    2u,
    nullptr);
  v7 = HumanAI_eQTaskType;
  QTask_LinkQTaskEventHandlerFn(
    HumanAI_eQTaskType,
    Serialize_eGetSerializeParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))HumanAI_GetSerializeParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v7, Serialize_eDeSerializeQTaskEvent, HumanAI_DeSerializeHandler);
  QTask_LinkQTaskEventHandlerFn(v7, Serialize_eSerializeQTaskEvent, HumanAI_SerializeHandler);
  v8 = (struct ParameterList_s *)Mem_AllocFn(692, 4);
  v9 = Level_eParameterTypeInt32;
  v8->ptParameterListItem = (struct ParameterListItem_s *)&v8[1];
  v8->nParameters = 0;
  v8->nMaxParameters = 34;
  HumanAI_ptSerializeParameterList = v8;
  ParameterList_AddParameter(v8, 0xF8Cu, v9, "Flags", 7u, nullptr);
  ParameterList_AddParameter(
    HumanAI_ptSerializeParameterList,
    0x1167u,
    Level_eParameterTypebool8,
    "FirstUpdate",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanAI_ptSerializeParameterList,
    0x7508u,
    Level_eParameterTypeInt32,
    "nIgnoreVisibilityFactorTimer",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanAI_ptSerializeParameterList,
    0x74FCu,
    Level_eParameterTypeInt32,
    "CurrentNode",
    2u,
    nullptr);
  ParameterList_AddParameter(
    HumanAI_ptSerializeParameterList,
    0x7504u,
    Level_eParameterTypeInt32,
    "nCurrentStartNode",
    2u,
    nullptr);
  ParameterList_AddParameter(
    HumanAI_ptSerializeParameterList,
    0x7500u,
    Level_eParameterTypeInt32,
    "nDestinationNode",
    2u,
    nullptr);
  ParameterList_AddParameter(
    HumanAI_ptSerializeParameterList,
    0x1E8u,
    Level_eParameterTypeInt32,
    "legalnode1",
    2u,
    nullptr);
  ParameterList_AddParameter(
    HumanAI_ptSerializeParameterList,
    0x1ECu,
    Level_eParameterTypeInt32,
    "legalnode2",
    2u,
    nullptr);
  ParameterList_AddParameter(
    HumanAI_ptSerializeParameterList,
    0x1F0u,
    Level_eParameterTypeInt32,
    "uselegalnodes",
    2u,
    nullptr);
  ParameterList_AddParameter(
    HumanAI_ptSerializeParameterList,
    0x1110u,
    Level_eParameterTypeInt32,
    "nPatrolPathStackPos",
    2u,
    nullptr);
  for ( j = 8644; j < 8900; j += 32 )
  {
    ParameterList_AddParameter(
      HumanAI_ptSerializeParameterList,
      j,
      Level_eParameterTypeInt32,
      &igi2_frame.Buffer[j - 8644],
      7u,
      nullptr);
    ParameterList_AddParameter(
      HumanAI_ptSerializeParameterList,
      j + 4,
      Level_eParameterTypeInt32,
      &igi2_frame.v13[j - 8644],
      7u,
      nullptr);
    ParameterList_AddParameter(
      HumanAI_ptSerializeParameterList,
      j - 4,
      Level_eParameterTypeInt32,
      &igi2_frame.v15[j - 8644],
      7u,
      nullptr);
  }
  HumanAI_RegisterScriptFunctions();
  HumanAI_RegisterConstants();
  HumanAI_tFreeMovementQueue.ptHead = (struct Node_s *)&HumanAI_tFreeMovementQueue.ptMiddle;
  HumanAI_tFreeMovementQueue.ptTail = (struct Node_s *)&HumanAI_tFreeMovementQueue;
  HumanAI_tFreeMovementQueue.ptMiddle = nullptr;
  v11 = HumanAI_atMovementQueueItems;
  do
  {
    v11->tNode.ptPrev = nullptr;
    v11->tNode.ptNext = nullptr;
    v11 = (struct HumanAIMovementQueueItem_t *)(List_AddTail(v11, (int)&HumanAI_tFreeMovementQueue) + 12);
  }
  while ( (int)v11 < 7652576 );
  HumanAI_ptDefaultScript = Script_New("LOCAL:common/ai/default.qsc");
  HumanAI_tActivationList.ptHead = (struct Node_s *)&HumanAI_tActivationList.ptMiddle;
  HumanAI_tActivationList.ptTail = (struct Node_s *)&HumanAI_tActivationList;
  HumanAI_tActivationList.ptMiddle = nullptr;
  HumanAI_tActivationFreeList.ptHead = (struct Node_s *)&HumanAI_tActivationFreeList.ptMiddle;
  HumanAI_tActivationFreeList.ptTail = (struct Node_s *)&HumanAI_tActivationFreeList;
  HumanAI_tActivationFreeList.ptMiddle = nullptr;
  v12 = HumanAI_atActivationEntries;
  do
  {
    v12->tNode.ptPrev = nullptr;
    v12->tNode.ptNext = nullptr;
    v12 = (struct HumanAIActivationEntry_t *)(List_AddTail(v12, (int)&HumanAI_tActivationFreeList) + 3);
  }
  while ( (int)v12 < 7591112 );
  HumanAI_ptRunScriptProfileRegion = nullptr;
  HumanAI_ptRunActionStackProfileRegion = nullptr;
  HumanAI_ptScriptExecuteProfileRegion = nullptr;
  HumanAI_ptSendEventProfileRegion = nullptr;
  HumanAI_ptUpdateHumanSoldierProfileRegion = nullptr;
  HumanAI_ptScriptFunctionInvestigateProfileRegion = nullptr;
  HumanAI_ptScriptFunctionPatrolProfileRegion = nullptr;
  HumanAI_ptScriptFunctionCombatProfileRegion = nullptr;
  HumanAI_ptScriptFunctionSetEventPriorityProfileRegion = nullptr;
  HumanAI_ptScriptFunctionGetCurrentEventTypeProfileRegion = nullptr;
  HumanAI_ptScriptFunctionDefaultHandlerProfileRegion = nullptr;
  HumanAI_ptScriptFunctionPassEventOnProfileRegion = nullptr;
  HumanAIContent_InitLookAroundPatterns();
  Human_bAreaActivateCriteriaSideKick = AreaActivateQTask_RegisterCriteria(
                                          "CRITERIA_HUMANAI_SIDEKICK",
                                          HumanAI_AreaActivateSideKickCB);
  Symbol_Register(
    "HumanAI_nEvent",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int,
    &HumanAI_nScriptEvent,
    4,
    QSCRIPT_SYMBOLCLASS_VARIABLE,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_FINITE);
}

// source: j/0/humanai/humanai.c:7742  [anchor-hash]
void __cdecl HumanAI_Close()
{
  int v0; // ecx
  int i; // eax
  int v2; // eax
  int v3; // esi
  int v4; // esi

  Symbol_Remove("HumanAI_nEvent");
  v0 = Human_bAreaActivateCriteriaSideKick;
  for ( i = 0; (v0 & 1) == 0; ++i )
    v0 >>= 1;
  v2 = i;
  AreaActivate_atCriteria[v2].isUsed = 0;
  Symbol_Remove(AreaActivate_atCriteria[v2].zName);
  if ( HumanAI_ptSerializeParameterList )
  {
    v3 = *(_DWORD *)((unsigned int)&HumanAI_ptSerializeParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v3);
    memset(*(void **)(v3 + 8), 0xCDu, *(_DWORD *)(v3 + 16));
    free((void *)v3);
  }
  if ( HumanAI_ptParameterList )
  {
    v4 = *(_DWORD *)((unsigned int)&HumanAI_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v4);
    memset(*(void **)(v4 + 8), 0xCDu, *(_DWORD *)(v4 + 16));
    free((void *)v4);
  }
  QTask_DeleteQTaskType(HumanAI_eQTaskType);
  QTask_DeleteQTaskEvent(HumanAI_eCommunicationEvent);
  if ( HumanAI_eSendEventQTaskEvent != 512 )
    QTask_DeleteQTaskEvent(HumanAI_eSendEventQTaskEvent);
  if ( HumanAI_eFindActivateQTaskEvent != 512 )
    QTask_DeleteQTaskEvent(HumanAI_eFindActivateQTaskEvent);
  if ( HumanAI_eCheckFirePathQTaskEvent != 512 )
    QTask_DeleteQTaskEvent(HumanAI_eCheckFirePathQTaskEvent);
  HumanAI_RemoveConstants();
  HumanAI_RemoveScriptFunctions();
  if ( HumanAI_ptDefaultScript )
    Script_Delete(HumanAI_ptDefaultScript);
}

// source: j/0/humanai/humanai.c:7793  [size]
unsigned __int16 __cdecl HumanAI_GetQTaskType()
{
  return HumanAI_eQTaskType;
}

// source: j/0/humanai/humanai.c:7808  [size]
__int16 __cdecl HumanAI_GetSendEventQTaskEvent()
{
  __int16 result; // ax

  result = HumanAI_eSendEventQTaskEvent;
  if ( HumanAI_eSendEventQTaskEvent == 512 )
  {
    result = QTask_NewQTaskEventFn(0, "HumanAISendEvent");
    HumanAI_eSendEventQTaskEvent = result;
  }
  return result;
}

// source: j/0/humanai/humanai.c:7827  [anchor-strings]
__int16 __cdecl HumanAI_GetFindActivateQTaskEvent()
{
  __int16 result; // ax

  result = HumanAI_eFindActivateQTaskEvent;
  if ( HumanAI_eFindActivateQTaskEvent == 512 )
  {
    result = QTask_NewQTaskEventFn(0, "HumanAIFindActivate");
    HumanAI_eFindActivateQTaskEvent = result;
  }
  return result;
}

// source: j/0/humanai/humanai.c:7849  [anchor-strings]
__int16 __cdecl HumanAI_GetCheckFirePathQTaskEvent()
{
  __int16 result; // ax

  result = HumanAI_eCheckFirePathQTaskEvent;
  if ( HumanAI_eCheckFirePathQTaskEvent == 512 )
  {
    result = QTask_NewQTaskEventFn(0, "HumanAICheckFirePath");
    HumanAI_eCheckFirePathQTaskEvent = result;
  }
  return result;
}

// source: j/0/humanai/humanai.c:7869  [size]
__int16 __cdecl HumanAI_GetCommunicationQTaskEvent()
{
  return HumanAI_eCommunicationEvent;
}

// source: j/0/humanai/humanai.c:7885  [anchor-callee]
void __cdecl HumanAI_SendEvent(struct HumanAIEventContext_t *ptEventContext)
{
  int v1; // esi
  int v2; // edi
  __int16 v3; // ax

  v1 = 0;
  if ( Human_ptQTaskList->nTask > 0 )
  {
    v2 = 8;
    do
    {
      v3 = HumanAI_eSendEventQTaskEvent;
      if ( HumanAI_eSendEventQTaskEvent == 512 )
      {
        v3 = QTask_NewQTaskEventFn(0, "HumanAISendEvent");
        HumanAI_eSendEventQTaskEvent = v3;
      }
      ((void (__cdecl *)(_DWORD, struct HumanAIEventContext_t *))QTask_aatQTaskFinalEvent[v3][*(unsigned __int16 *)(*(int *)((char *)&Human_ptQTaskList->nTask + v2) + 36)].pfHandler)(
        *(int *)((char *)&Human_ptQTaskList->nTask + v2),
        ptEventContext);
      ++v1;
      v2 += 4;
    }
    while ( v1 < Human_ptQTaskList->nTask );
  }
}

// source: j/0/humanai/humanai.c:7903  [anchor-callee]
void __cdecl HumanAI_SendEventSpecificQTask(
        struct QTask_s *ptQTask,
        struct HumanAIEventContext_t *ptEventContext)
{
  __int16 v2; // ax

  v2 = HumanAI_eSendEventQTaskEvent;
  if ( HumanAI_eSendEventQTaskEvent == 512 )
  {
    v2 = QTask_NewQTaskEventFn(0, "HumanAISendEvent");
    HumanAI_eSendEventQTaskEvent = v2;
  }
  ((void (__cdecl *)(struct QTask_s *, struct HumanAIEventContext_t *))QTask_aatQTaskFinalEvent[v2][ptQTask->eQTaskType].pfHandler)(
    ptQTask,
    ptEventContext);
}

// source: j/0/humanai/humanai.c:7919  [anchor-mhash]
int __cdecl HumanAI_SendEventNoContext(int eEvent, unsigned int bFlags)
{
  int result; // eax
  struct HumanAIEventContext_t tContext; // [esp+4h] [ebp-40h] BYREF

  tContext.eEvent = eEvent;
  tContext.bFlags = bFlags;
  tContext.ptHumanOriginatorQTask = nullptr;
  tContext.ptReferenceQTask = nullptr;
  tContext.ptPosition = nullptr;
  HumanAI_SendEvent(&tContext);
  return result;
}

// source: j/0/humanai/humanai.c:7944  [anchor-callee]
int __cdecl HumanAI_SendEventNoContextSpecificQTask(
        struct QTask_s *ptQTask,
        int eEvent,
        unsigned int bFlags)
{
  __int16 v3; // ax
  struct HumanAIEventContext_t tContext; // [esp+0h] [ebp-40h] BYREF

  tContext.eEvent = eEvent;
  v3 = HumanAI_eSendEventQTaskEvent;
  tContext.bFlags = bFlags;
  tContext.ptHumanOriginatorQTask = nullptr;
  tContext.ptReferenceQTask = nullptr;
  tContext.ptPosition = nullptr;
  if ( HumanAI_eSendEventQTaskEvent == 512 )
  {
    v3 = QTask_NewQTaskEventFn(0, "HumanAISendEvent");
    HumanAI_eSendEventQTaskEvent = v3;
  }
  return ((int (__cdecl *)(struct QTask_s *, struct HumanAIEventContext_t *))QTask_aatQTaskFinalEvent[v3][ptQTask->eQTaskType].pfHandler)(
           ptQTask,
           &tContext);
}

// source: j/0/humanai/humanai.c:7971  [anchor-callee]
void __cdecl HumanAI_PopTopActionStackItems(struct HumanAI_s *ptHumanAI)
{
  void (__cdecl *pfRunCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // esi
  void (__cdecl *v2)(struct HumanAI_s *, _DWORD); // eax
  _DWORD *v3; // eax

  pfRunCallback = ptHumanAI->atActionStackItemList[0].pfRunCallback;
  if ( *(_DWORD *)pfRunCallback && pfRunCallback )
  {
    do
    {
      if ( (*((_BYTE *)pfRunCallback + 20) & 1) != 0 )
        break;
      v2 = *((void (__cdecl **)(struct HumanAI_s *, _DWORD))pfRunCallback + 9);
      if ( v2 )
        v2(ptHumanAI, pfRunCallback);
      Node_Remove((_DWORD **)pfRunCallback);
      v3 = *((_DWORD **)pfRunCallback + 12);
      *((_BYTE *)pfRunCallback + 52) = 0;
      if ( v3 )
      {
        v3[1] = 0;
        *v3 = 0;
        List_AddTail(v3, (int)&ptHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID);
        *((_DWORD *)pfRunCallback + 12) = 0;
      }
      pfRunCallback = ptHumanAI->atActionStackItemList[0].pfRunCallback;
      if ( !*(_DWORD *)pfRunCallback )
        break;
    }
    while ( pfRunCallback );
  }
}

// source: j/0/humanai/humanai.c:8003  [size]
struct HumanAIActionStackItem_s *__cdecl HumanAI_GetTopActionStackItem(
        struct HumanAI_s *ptHumanAI)
{
  return *(_DWORD *)ptHumanAI->atActionStackItemList[0].pfRunCallback != 0
       ? (struct HumanAIActionStackItem_s *)ptHumanAI->atActionStackItemList[0].pfRunCallback
       : nullptr;
}

// source: j/0/humanai/humanai.c:8027  [anchor-hash]
int __cdecl HumanAI_GetFreeActionStackItem(int a1)
{
  int v1; // ecx
  int result; // eax

  v1 = 0;
  for ( result = a1 + 4764; *(_BYTE *)(result + 52); result += 56 )
  {
    if ( ++v1 >= 32 )
    {
      LDebug_Error("ActionStack full");
      abort();
    }
  }
  *(_DWORD *)(result + 44) = 0;
  *(_DWORD *)(result + 36) = 0;
  *(_DWORD *)(result + 24) = 0;
  *(_DWORD *)(result + 28) = 0;
  *(_DWORD *)(result + 32) = 0;
  *(_DWORD *)(result + 40) = 0;
  *(_DWORD *)(result + 48) = 0;
  *(_BYTE *)(result + 52) = 1;
  *(_DWORD *)(result + 8) = 0;
  *(_DWORD *)(result + 16) = 0;
  return result;
}

// source: j/0/humanai/humanai.c:8067  [anchor-caller]
void __cdecl HumanAI_AddActionToLocalList(
        void (__cdecl *pfActionInitCB__)(struct HumanAI_s *, struct HumanAIActionStackItem_s *),
        void *ptContext,
        unsigned int bFlags)
{
  int FreeActionStackItem; // eax
  struct List_s *v4; // ecx

  FreeActionStackItem = HumanAI_GetFreeActionStackItem((int)HumanAI_ptCurrentHumanAI);
  *(_DWORD *)(FreeActionStackItem + 12) = HumanAI_nHandlerPriority;
  *(_DWORD *)(FreeActionStackItem + 4) = 0;
  *(_DWORD *)FreeActionStackItem = 0;
  *(_DWORD *)(FreeActionStackItem + 28) = 0;
  *(_DWORD *)(FreeActionStackItem + 32) = 0;
  *(_DWORD *)(FreeActionStackItem + 36) = 0;
  *(_DWORD *)(FreeActionStackItem + 44) = 0;
  *(_DWORD *)(FreeActionStackItem + 20) = bFlags;
  *(_DWORD *)(FreeActionStackItem + 48) = ptContext;
  v4 = HumanAI_ptLocalActionList;
  *(_DWORD *)(FreeActionStackItem + 24) = pfActionInitCB__;
  *(_BYTE *)(FreeActionStackItem + 52) = 1;
  List_AddTail((_DWORD *)FreeActionStackItem, (int)v4);
}

// source: j/0/humanai/humanai.c:8099  [anchor-hash]
struct HumanAI_s *__cdecl HumanAI_PushActionStackItem(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  void (__cdecl *pfRunCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // eax
  void (__cdecl *v4)(struct HumanAI_s *, _DWORD); // ecx

  pfRunCallback = ptHumanAI->atActionStackItemList[0].pfRunCallback;
  if ( *(_DWORD *)pfRunCallback
    && pfRunCallback
    && (*((_BYTE *)pfRunCallback + 20) & 1) != 0
    && (v4 = *((void (__cdecl **)(struct HumanAI_s *, _DWORD))pfRunCallback + 10)) != nullptr )
  {
    v4(ptHumanAI, pfRunCallback);
  }
  else
  {
    HumanAI_PopTopActionStackItems(ptHumanAI);
  }
  ptActionStackItem->tNode.ptPrev = nullptr;
  ptActionStackItem->tNode.ptNext = nullptr;
  List_AddHead(ptActionStackItem, (int)&ptHumanAI->atActionStackItemList[0].pfRunCallback);
  AIGraphAStarSearch_Clear(&ptHumanAI->tAStarSearchData);
  LODWORD(ptHumanAI->tCommon.tAimPosition.vZ) = HIDWORD(ptHumanAI->tCommon.tAimPosition.vY);
  HumanAI_ClearMovementQueue(ptHumanAI);
  return ((struct HumanAI_s *(__cdecl *)(struct HumanAI_s *, struct HumanAIActionStackItem_s *))ptActionStackItem->pfInitCallback)(
           ptHumanAI,
           ptActionStackItem);
}

// source: j/0/humanai/humanai.c:8138  [anchor-callee]
struct HumanAI_s *__cdecl HumanAI_PushActionStackList(
        struct HumanAI_s *ptHumanAI,
        struct List_s *ptActionStackList)
{
  char v3; // bl
  struct HumanAI_s *result; // eax
  struct HumanAI_s *i; // esi
  _DWORD *v6; // eax

  v3 = 0;
  HumanAI_PopTopActionStackItems(ptHumanAI);
  result = (struct HumanAI_s *)ptActionStackList->ptTail;
  for ( i = (struct HumanAI_s *)result->tQTask.ptPrev; i; i = (struct HumanAI_s *)i->tQTask.ptPrev )
  {
    if ( !v3 )
    {
      ptActionStackList = (struct List_s *)result->tQTask.tQTaskRefList.ptHead;
      v3 = 1;
    }
    result->tQTask.tQTaskRefList.ptHead = (struct QReference_s *)ptActionStackList;
    result->tQTask.ptNext = nullptr;
    result->tQTask.ptPrev = nullptr;
    v6 = List_AddHead(result, (int)&ptHumanAI->atActionStackItemList[0].pfRunCallback);
    ((void (__cdecl *)(struct HumanAI_s *, _DWORD *))v6[6])(ptHumanAI, v6);
    result = i;
  }
  return result;
}

// source: j/0/humanai/humanai.c:8200  [anchor-callee]
void __cdecl HumanAI_PopActionStackItem(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptActionStackItem)
{
  void (__cdecl *pfDeleteCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // eax
  struct HumanAIActionContext_t *ptContext; // eax

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

// source: j/0/humanai/humanai.c:8228  [anchor-hash]
struct HumanAIActionContext_t *__cdecl HumanAI_CreateActionContext(struct HumanAI_s *ptHumanAI)
{
  _DWORD **nLastEndCommandQTaskID; // eax

  nLastEndCommandQTaskID = (_DWORD **)ptHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID;
  if ( *nLastEndCommandQTaskID )
    return (struct HumanAIActionContext_t *)Node_Remove(nLastEndCommandQTaskID);
  else
    return nullptr;
}

// source: j/0/humanai/humanai.c:8264  [anchor-callee]
struct HumanAIActionContext_t *__cdecl HumanAI_RemoveActionContext(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionContext_t *ptContext)
{
  ptContext->tNode.ptPrev = nullptr;
  ptContext->tNode.ptNext = nullptr;
  return (struct HumanAIActionContext_t *)List_AddTail(
                                            ptContext,
                                            (int)&ptHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID);
}

// source: j/0/humanai/humanai.c:8285  [anchor-mhash]
void __cdecl HumanAI_PushPatrolPathStack(
        struct HumanAI_s *ptHumanAI,
        int nPatrolPathQTaskID,
        int nOffset)
{
  struct PatrolPathControl_t *p_ptLastEndCommandQTask; // esi

  p_ptLastEndCommandQTask = (struct PatrolPathControl_t *)&ptHumanAI->atPatrolPathStackItems[ptHumanAI->nAnimationDelay
                                                                                           + 1].ptLastEndCommandQTask;
  PatrolPath_InitPatrolPath(p_ptLastEndCommandQTask, nPatrolPathQTaskID, nOffset);
  if ( p_ptLastEndCommandQTask->ptPatrolPathQTask )
    ++ptHumanAI->nAnimationDelay;
}

// source: j/0/humanai/humanai.c:8311  [anchor-hash]
struct HumanAI_s *__cdecl HumanAI_PopPatrolPathStack(struct HumanAI_s *ptHumanAI)
{
  int nAnimationDelay; // ecx
  int v2; // ecx

  nAnimationDelay = ptHumanAI->nAnimationDelay;
  if ( nAnimationDelay )
  {
    v2 = nAnimationDelay - 1;
    ptHumanAI->nAnimationDelay = v2;
    *(_DWORD *)&ptHumanAI->atPatrolPathStackItems[v2 + 1].isCrouch = 0;
    ptHumanAI->atPatrolPathStackItems[ptHumanAI->nAnimationDelay + 1].nUserModify = 0;
    ptHumanAI->atPatrolPathStackItems[ptHumanAI->nAnimationDelay + 1].ptLastEndCommandQTask = nullptr;
  }
  return ptHumanAI;
}

// source: j/0/humanai/humanai.c:8333  [size]
void HumanAI_PrintDebugTextOnPlayer(struct HumanAI_s *ptHumanAI, int nLine, char *zFormat, ...)
{
  ;
}

// source: j/0/humanai/humanai.c:8363  [size]
enum bool __cdecl HumanAI_IsDead(struct HumanAI_s *ptHumanAI)
{
  return SLOBYTE(ptHumanAI->tQTask.ptParent[29].tQTaskRefList.ptHead);
}

// source: j/0/humanai/humanai.c:8380  [anchor-callee]
struct real64x3_t *__cdecl HumanAI_GetTargetPosition(
        struct real64x3_t *ptTargetPos,
        struct HumanAI_s *ptHumanAI)
{
  struct real64x3_t *result; // eax
  double *ptParent; // esi
  struct real64x3_t *v5; // ebx
  _DWORD *i; // edx
  int v7; // ecx
  double v8; // st3
  long double v9; // st4
  float v10; // [esp+Ch] [ebp-10h]
  float v11; // [esp+10h] [ebp-Ch]
  float v12; // [esp+14h] [ebp-8h]

  result = (struct real64x3_t *)HumanAI_GetTargetQTask(ptHumanAI, true);
  if ( result )
    goto LABEL_14;
  ptParent = (double *)ptHumanAI->tQTask.ptParent;
  v5 = nullptr;
  result = (struct real64x3_t *)HumanAI_GetTargetQTask(ptHumanAI, true);
  if ( !result )
  {
    for ( i = (_DWORD *)ptHumanAI->tAIDetection.atListItems[0].bQTaskMask; *i && i; i = (_DWORD *)*i )
    {
      v7 = *(_DWORD *)(i[2] + 8);
      if ( v7 )
      {
        if ( !*(_BYTE *)(v7 + 1180) )
        {
          v11 = ptParent[5] - *(double *)(v7 + 40);
          v12 = ptParent[6] - *(double *)(v7 + 48);
          v8 = ptParent[7] - *(double *)(v7 + 56);
          v9 = sqrt(v11 * v11 + v12 * v12 + v8 * v8);
          if ( !v5 || v9 < v10 )
          {
            v10 = v9;
            v5 = *(struct real64x3_t **)(i[2] + 8);
          }
        }
      }
    }
    result = v5;
  }
  if ( result )
LABEL_14:
    qmemcpy(ptTargetPos, &ptHumanAI[1], sizeof(struct real64x3_t));
  else
    qmemcpy(ptTargetPos, &ptHumanAI->tCommon.nIgnoreVisibilityFactorTimer, sizeof(struct real64x3_t));
  return result;
}

// source: j/0/humanai/humanai.c:8409  [anchor-callee]
struct QTask_s *__cdecl HumanAI_GetTargetQTask(struct HumanAI_s *ptHumanAI, enum bool isVisiblesOnly)
{
  struct QTask_s *v2; // ebx
  double *ptParent; // edi
  struct QTask_s *result; // eax
  _DWORD *i; // edx
  int v6; // ecx
  int v7; // eax
  double v8; // st3
  long double v9; // st4
  float tReal32x3; // [esp+10h] [ebp-Ch]
  float tReal32x3_4; // [esp+14h] [ebp-8h]

  v2 = nullptr;
  ptParent = (double *)ptHumanAI->tQTask.ptParent;
  if ( isVisiblesOnly || (result = HumanAI_GetTargetQTask(ptHumanAI, true)) == nullptr )
  {
    for ( i = (_DWORD *)ptHumanAI->tAIDetection.atListItems[0].bQTaskMask; *i && i; i = (_DWORD *)*i )
    {
      v6 = *(_DWORD *)(i[2] + 8);
      if ( isVisiblesOnly )
      {
        v7 = 0;
        while ( !*((_BYTE *)i + v7 + 51) )
        {
          if ( ++v7 >= 3 )
            goto LABEL_15;
        }
      }
      if ( v6 )
      {
        if ( !*(_BYTE *)(v6 + 1180) )
        {
          tReal32x3 = ptParent[5] - *(double *)(v6 + 40);
          tReal32x3_4 = ptParent[6] - *(double *)(v6 + 48);
          v8 = ptParent[7] - *(double *)(v6 + 56);
          v9 = sqrt(tReal32x3 * tReal32x3 + tReal32x3_4 * tReal32x3_4 + v8 * v8);
          if ( !v2 || v9 < *(float *)&ptHumanAI )
          {
            *(float *)&ptHumanAI = v9;
            v2 = *(struct QTask_s **)(i[2] + 8);
          }
        }
      }
LABEL_15:
      ;
    }
    return v2;
  }
  return result;
}

// source: j/0/humanai/humanai.c:8482  [anchor-hash]
enum bool __cdecl HumanAI_IsIdentifyingTarget(struct HumanAI_s *ptHumanAI)
{
  unsigned int bQTaskMask; // eax

  bQTaskMask = ptHumanAI->tAIDetection.atListItems[0].bQTaskMask;
  if ( !*(_DWORD *)bQTaskMask || !bQTaskMask )
    return false;
  while ( !*(_BYTE *)(bQTaskMask + 57) )
  {
    bQTaskMask = *(_DWORD *)bQTaskMask;
    if ( !*(_DWORD *)bQTaskMask || !bQTaskMask )
      return false;
  }
  return true;
}

// source: j/0/humanai/humanai.c:8508  [anchor-hash]
enum bool __cdecl HumanAI_QTaskIsVisibleTarget(
        struct HumanAI_s *ptHumanAI,
        struct QTask_s *ptTargetQTask)
{
  _DWORD *i; // ecx
  struct QTask_s *v3; // edx
  int v4; // eax

  for ( i = (_DWORD *)ptHumanAI->tAIDetection.atListItems[0].bQTaskMask; *i && i; i = (_DWORD *)*i )
  {
    v3 = *(struct QTask_s **)(i[2] + 8);
    v4 = 0;
    while ( !*((_BYTE *)i + v4 + 51) )
    {
      if ( ++v4 >= 3 )
        goto LABEL_9;
    }
    if ( v3 && v3 == ptTargetQTask )
      return true;
LABEL_9:
    ;
  }
  return false;
}

// source: j/0/humanai/humanai.c:8542  [anchor-caller]
void __cdecl HumanAI_LevelSight(struct HumanAI_s *ptHumanAI)
{
  double LevelSightDelta; // st7
  float v2; // [esp+0h] [ebp-4h]

  LevelSightDelta = HumanAI_GetLevelSightDelta(&ptHumanAI->tView);
  v2 = -ptHumanAI->avChannel[8];
  if ( LevelSightDelta >= v2 )
  {
    if ( LevelSightDelta > ptHumanAI->avChannel[8] )
      LevelSightDelta = ptHumanAI->avChannel[8];
    ptHumanAI->avChannel[11] = LevelSightDelta * 0.31830987334251404;
  }
  else
  {
    ptHumanAI->avChannel[11] = v2 * 0.31830987334251404;
  }
}

// source: j/0/humanai/humanai.c:8566  [anchor-callee]
enum bool __cdecl HumanAI_IsDestinationReached(
        struct HumanAI_s *ptHumanAI,
        struct real64x3_t *ptDestPos)
{
  double *ptParent; // eax
  double v3; // st7
  double v4; // st7
  double v5; // st7
  float tReal32x3_4; // [esp+4h] [ebp-8h]
  float tReal32x3_8; // [esp+8h] [ebp-4h]

  ptParent = (double *)ptHumanAI->tQTask.ptParent;
  v3 = ptDestPos->vX - ptParent[5];
  tReal32x3_4 = ptDestPos->vY - ptParent[6];
  tReal32x3_8 = ptDestPos->vZ - ptParent[7];
  if ( v3 < 0.0 )
    v3 = -v3;
  if ( v3 > 1228.8 )
    return false;
  v4 = tReal32x3_4;
  if ( tReal32x3_4 < 0.0 )
    v4 = -v4;
  if ( v4 > 1228.8 )
    return false;
  v5 = tReal32x3_8;
  if ( tReal32x3_8 < 0.0 )
    v5 = -v5;
  return v5 <= 8192.0;
}

// source: j/0/humanai/humanai.c:8594  [anchor-callee]
void __cdecl HumanAI_PointCharacterTowardsDestinationForward(
        struct HumanAI_s *ptHumanAI,
        struct real64x3_t *ptDestPos)
{
  struct QTask_s *ptParent; // edx
  struct QTask_s *ptPrev; // eax
  double v4; // st7
  double v5; // st6
  double v6; // st5
  double v7; // st7
  double v8; // st7
  double v9; // st7
  double LevelSightDelta; // st7
  double v11; // st6
  double v12; // st6
  float vGamma; // [esp+4h] [ebp-18h]
  float Real32x3_RotateInverse_tTemp; // [esp+8h] [ebp-14h]
  float Real32x3_RotateInverse_tTempa; // [esp+8h] [ebp-14h]

  ptParent = ptHumanAI->tQTask.ptParent;
  ptPrev = ptParent[31].ptPrev;
  if ( ptPrev == (struct QTask_s *)6
    || ptPrev == (struct QTask_s *)7
    || ptPrev == (struct QTask_s *)5
    || ptPrev == (struct QTask_s *)4 )
  {
    ptHumanAI->avChannel[14] = 1.0;
  }
  if ( HumanAI_IsDestinationReached(ptHumanAI, ptDestPos) == false )
  {
    v4 = ptDestPos->vX - *(double *)&ptParent[1].ptNext;
    v5 = ptDestPos->vY - *(double *)&ptParent[1].tQTaskChildren.ptHead;
    v6 = ptDestPos->vZ - *(double *)&ptParent[1].tQTaskChildren.ptTail;
    Real32x3_RotateInverse_tTemp = v6 * *(float *)&ptParent[3].tQTaskRefList.ptTail
                                 + v5 * *(float *)&ptParent[3].tQTaskChildren.ptTail
                                 + v4 * *(float *)&ptParent[3].ptPrev;
    v7 = v6 * *(float *)&ptParent[3].ptParent
       + v5 * *(float *)&ptParent[3].tQTaskRefList.ptHead
       + v4 * *(float *)&ptParent[3].tQTaskChildren.ptHead;
    if ( v7 == 0.0 )
    {
      vGamma = 0.0;
    }
    else
    {
      vGamma = atan2(Real32x3_RotateInverse_tTemp / v7, 1.0);
      if ( v7 < 0.0 )
      {
        v8 = vGamma;
        if ( Real32x3_RotateInverse_tTemp <= 0.0 )
          v9 = v8 - 3.1415927410125732;
        else
          v9 = v8 + 3.1415927410125732;
        vGamma = v9;
      }
    }
    LevelSightDelta = HumanAI_GetLevelSightDelta(&ptHumanAI->tView);
    v11 = vGamma;
    if ( vGamma < 0.0 )
      v11 = -v11;
    if ( v11 <= 0.1745329350233078 )
    {
      ptHumanAI->avChannel[14] = 1.0;
    }
    else
    {
      ptParent[34].tQTaskChildren.ptTail[1].tQTaskRefList.ptTail = (struct QReference_s *)(__int64)((double)AnimController_nTicksPerFrame
                                                                                                  * 0.20000000298023224);
      ptParent[75].tQTaskChildren.ptTail = (struct QTask_s *)1045220557;
    }
    Real32x3_RotateInverse_tTempa = -ptHumanAI->avChannel[8];
    if ( LevelSightDelta >= Real32x3_RotateInverse_tTempa )
    {
      if ( LevelSightDelta > ptHumanAI->avChannel[8] )
        LevelSightDelta = ptHumanAI->avChannel[8];
    }
    else
    {
      LevelSightDelta = Real32x3_RotateInverse_tTempa;
    }
    v12 = -ptHumanAI->avChannel[9];
    if ( vGamma >= v12 )
    {
      if ( vGamma > (double)ptHumanAI->avChannel[9] )
        vGamma = ptHumanAI->avChannel[9];
    }
    else
    {
      vGamma = v12;
    }
    ptHumanAI->eLastMovementDirection = HUMANAI_MOVEMENTDIRECTION_FORWARD;
    ptHumanAI->avChannel[10] = vGamma * 0.31830987334251404;
    ptHumanAI->avChannel[11] = LevelSightDelta * 0.31830987334251404;
  }
}

// source: j/0/humanai/humanai.c:8683  [anchor-callee]
void __cdecl HumanAI_PointCharacterTowardsDestinationLeft(
        struct HumanAI_s *ptHumanAI,
        struct real64x3_t *ptDestPos)
{
  struct QTask_s *ptParent; // edx
  double v3; // st7
  double v4; // st6
  double v5; // st5
  double v6; // st7
  double v7; // st6
  bool v8; // c0
  bool v9; // c3
  double v10; // st7
  double v11; // st7
  double v12; // st7
  double v13; // st7
  double v14; // st7
  double v15; // st7
  float vGamma; // [esp+4h] [ebp-18h]
  float vAlpha; // [esp+8h] [ebp-14h]
  float Real32x3_RotateInverse_tTemp; // [esp+Ch] [ebp-10h]

  ptParent = ptHumanAI->tQTask.ptParent;
  ptHumanAI->avChannel[12] = 1.0;
  if ( HumanAI_IsDestinationReached(ptHumanAI, ptDestPos) == false )
  {
    v3 = ptDestPos->vX - *(double *)&ptParent[1].ptNext;
    v4 = ptDestPos->vY - *(double *)&ptParent[1].tQTaskChildren.ptHead;
    v5 = ptDestPos->vZ - *(double *)&ptParent[1].tQTaskChildren.ptTail;
    Real32x3_RotateInverse_tTemp = v5 * *(float *)&ptParent[3].tQTaskRefList.ptTail
                                 + v4 * *(float *)&ptParent[3].tQTaskChildren.ptTail
                                 + v3 * *(float *)&ptParent[3].ptPrev;
    v6 = v5 * *(float *)&ptParent[3].ptParent
       + v4 * *(float *)&ptParent[3].tQTaskRefList.ptHead
       + v3 * *(float *)&ptParent[3].tQTaskChildren.ptHead;
    v7 = -Real32x3_RotateInverse_tTemp;
    if ( v7 == 0.0 )
    {
      vGamma = 0.0;
    }
    else
    {
      vGamma = atan2(v6 / v7, 1.0);
      if ( v7 < 0.0 )
      {
        v8 = v6 < 0.0;
        v9 = v6 == 0.0;
        v10 = vGamma;
        if ( v8 || v9 )
          v11 = v10 - 3.1415927410125732;
        else
          v11 = v10 + 3.1415927410125732;
        vGamma = v11;
      }
    }
    vAlpha = HumanAI_GetLevelSightDelta(&ptHumanAI->tView);
    v12 = vGamma;
    if ( vGamma < 0.0 )
      v12 = -v12;
    if ( v12 <= 0.1745329350233078 )
    {
      v13 = vGamma;
      if ( vGamma < 0.0 )
        v13 = -v13;
      if ( v13 < 0.03490658476948738
        && HumanAI_GetTargetQTask(ptHumanAI, true)
        && Real32x3_RotateInverse_tTemp > -12288.0
        && Real32x3_RotateInverse_tTemp < -10240.0
        && !HIDWORD(ptHumanAI->tCommon.tTargetPosition.vX) )
      {
        HIDWORD(ptHumanAI->tCommon.tTargetPosition.vX) = 300;
        ptHumanAI->avChannel[46] = 1.0;
      }
    }
    else
    {
      ptHumanAI->avChannel[12] = 0.0;
    }
    v14 = -ptHumanAI->avChannel[8];
    if ( vAlpha >= v14 )
    {
      if ( vAlpha > (double)ptHumanAI->avChannel[8] )
        vAlpha = ptHumanAI->avChannel[8];
    }
    else
    {
      vAlpha = v14;
    }
    v15 = -ptHumanAI->avChannel[9];
    if ( vGamma >= v15 )
    {
      if ( vGamma > (double)ptHumanAI->avChannel[9] )
        vGamma = ptHumanAI->avChannel[9];
    }
    else
    {
      vGamma = v15;
    }
    ptHumanAI->eLastMovementDirection = HUMANAI_MOVEMENTDIRECTION_LEFT;
    ptHumanAI->avChannel[10] = vGamma * 0.31830987334251404;
    ptHumanAI->avChannel[11] = vAlpha * 0.31830987334251404;
  }
}

// source: j/0/humanai/humanai.c:8772  [anchor-callee]
void __cdecl HumanAI_PointCharacterTowardsDestinationRight(
        struct HumanAI_s *ptHumanAI,
        struct real64x3_t *ptDestPos)
{
  struct QTask_s *ptParent; // edx
  double v3; // st7
  double v4; // st6
  double v5; // st5
  double v6; // st7
  bool v7; // c0
  bool v8; // c3
  double v9; // st7
  double v10; // st7
  double v11; // st7
  double v12; // st7
  double v13; // st7
  double v14; // st7
  float vGamma; // [esp+4h] [ebp-18h]
  float vAlpha; // [esp+8h] [ebp-14h]
  float Real32x3_RotateInverse_tTemp; // [esp+Ch] [ebp-10h]

  ptParent = ptHumanAI->tQTask.ptParent;
  ptHumanAI->avChannel[13] = 1.0;
  if ( HumanAI_IsDestinationReached(ptHumanAI, ptDestPos) == false )
  {
    v3 = ptDestPos->vX - *(double *)&ptParent[1].ptNext;
    v4 = ptDestPos->vY - *(double *)&ptParent[1].tQTaskChildren.ptHead;
    v5 = ptDestPos->vZ - *(double *)&ptParent[1].tQTaskChildren.ptTail;
    Real32x3_RotateInverse_tTemp = v5 * *(float *)&ptParent[3].tQTaskRefList.ptTail
                                 + v4 * *(float *)&ptParent[3].tQTaskChildren.ptTail
                                 + v3 * *(float *)&ptParent[3].ptPrev;
    v6 = -(v5 * *(float *)&ptParent[3].ptParent
         + v4 * *(float *)&ptParent[3].tQTaskRefList.ptHead
         + v3 * *(float *)&ptParent[3].tQTaskChildren.ptHead);
    if ( Real32x3_RotateInverse_tTemp == 0.0 )
    {
      vGamma = 0.0;
    }
    else
    {
      vGamma = atan2(v6 / Real32x3_RotateInverse_tTemp, 1.0);
      if ( Real32x3_RotateInverse_tTemp < 0.0 )
      {
        v7 = v6 < 0.0;
        v8 = v6 == 0.0;
        v9 = vGamma;
        if ( v7 || v8 )
          v10 = v9 - 3.1415927410125732;
        else
          v10 = v9 + 3.1415927410125732;
        vGamma = v10;
      }
    }
    vAlpha = HumanAI_GetLevelSightDelta(&ptHumanAI->tView);
    v11 = vGamma;
    if ( vGamma < 0.0 )
      v11 = -v11;
    if ( v11 <= 0.1745329350233078 )
    {
      v12 = vGamma;
      if ( vGamma < 0.0 )
        v12 = -v12;
      if ( v12 < 0.03490658476948738
        && HumanAI_GetTargetQTask(ptHumanAI, true)
        && Real32x3_RotateInverse_tTemp > 10240.0
        && Real32x3_RotateInverse_tTemp < 12288.0
        && !HIDWORD(ptHumanAI->tCommon.tTargetPosition.vX) )
      {
        HIDWORD(ptHumanAI->tCommon.tTargetPosition.vX) = 300;
        ptHumanAI->avChannel[47] = 1.0;
      }
    }
    else
    {
      ptHumanAI->avChannel[13] = 0.0;
    }
    v13 = -ptHumanAI->avChannel[8];
    if ( vAlpha >= v13 )
    {
      if ( vAlpha > (double)ptHumanAI->avChannel[8] )
        vAlpha = ptHumanAI->avChannel[8];
    }
    else
    {
      vAlpha = v13;
    }
    v14 = -ptHumanAI->avChannel[9];
    if ( vGamma >= v14 )
    {
      if ( vGamma > (double)ptHumanAI->avChannel[9] )
        vGamma = ptHumanAI->avChannel[9];
    }
    else
    {
      vGamma = v14;
    }
    ptHumanAI->eLastMovementDirection = HUMANAI_MOVEMENTDIRECTION_RIGHT;
    ptHumanAI->avChannel[10] = vGamma * 0.31830987334251404;
    ptHumanAI->avChannel[11] = vAlpha * 0.31830987334251404;
  }
}

// source: j/0/humanai/humanai.c:8861  [anchor-callee]
void __cdecl HumanAI_PointCharacterTowardsDestinationBackward(
        struct HumanAI_s *ptHumanAI,
        struct real64x3_t *ptDestPos)
{
  struct QTask_s *ptParent; // edx
  double v3; // st7
  double v4; // st6
  double v5; // st5
  double v6; // st7
  double v7; // st6
  bool v8; // c0
  bool v9; // c3
  double v10; // st7
  double v11; // st7
  double LevelSightDelta; // st7
  double v13; // st6
  double v14; // st6
  float vGamma; // [esp+0h] [ebp-24h]
  float v16; // [esp+4h] [ebp-20h]
  float Real32x3_RotateInverse_tTemp; // [esp+8h] [ebp-1Ch]
  float Real32x3_RotateInverse_tTemp_4; // [esp+Ch] [ebp-18h]

  ptParent = ptHumanAI->tQTask.ptParent;
  ptHumanAI->avChannel[15] = 1.0;
  if ( HumanAI_IsDestinationReached(ptHumanAI, ptDestPos) == false )
  {
    v3 = ptDestPos->vX - *(double *)&ptParent[1].ptNext;
    v4 = ptDestPos->vY - *(double *)&ptParent[1].tQTaskChildren.ptHead;
    v5 = ptDestPos->vZ - *(double *)&ptParent[1].tQTaskChildren.ptTail;
    Real32x3_RotateInverse_tTemp = v5 * *(float *)&ptParent[3].tQTaskRefList.ptTail
                                 + v4 * *(float *)&ptParent[3].tQTaskChildren.ptTail
                                 + v3 * *(float *)&ptParent[3].ptPrev;
    Real32x3_RotateInverse_tTemp_4 = v5 * *(float *)&ptParent[3].ptParent
                                   + v4 * *(float *)&ptParent[3].tQTaskRefList.ptHead
                                   + v3 * *(float *)&ptParent[3].tQTaskChildren.ptHead;
    v6 = -Real32x3_RotateInverse_tTemp;
    v7 = -Real32x3_RotateInverse_tTemp_4;
    if ( v7 == 0.0 )
    {
      vGamma = 0.0;
    }
    else
    {
      vGamma = atan2(v6 / v7, 1.0);
      if ( v7 < 0.0 )
      {
        v8 = v6 < 0.0;
        v9 = v6 == 0.0;
        v10 = vGamma;
        if ( v8 || v9 )
          v11 = v10 - 3.1415927410125732;
        else
          v11 = v10 + 3.1415927410125732;
        vGamma = v11;
      }
    }
    LevelSightDelta = HumanAI_GetLevelSightDelta(&ptHumanAI->tView);
    v13 = vGamma;
    if ( vGamma < 0.0 )
      v13 = -v13;
    if ( v13 > 0.1745329350233078 )
      ptHumanAI->avChannel[15] = 0.0;
    v16 = -ptHumanAI->avChannel[8];
    if ( LevelSightDelta >= v16 )
    {
      if ( LevelSightDelta > ptHumanAI->avChannel[8] )
        LevelSightDelta = ptHumanAI->avChannel[8];
    }
    else
    {
      LevelSightDelta = v16;
    }
    v14 = -ptHumanAI->avChannel[9];
    if ( vGamma >= v14 )
    {
      if ( vGamma > (double)ptHumanAI->avChannel[9] )
        vGamma = ptHumanAI->avChannel[9];
    }
    else
    {
      vGamma = v14;
    }
    ptHumanAI->eLastMovementDirection = HUMANAI_MOVEMENTDIRECTION_BACKWARD;
    ptHumanAI->avChannel[10] = vGamma * 0.31830987334251404;
    ptHumanAI->avChannel[11] = LevelSightDelta * 0.31830987334251404;
  }
}

// source: j/0/humanai/humanai.c:8937  [anchor-callee]
void __cdecl HumanAI_PointCharacterTowardsDestination(
        struct HumanAI_s *ptHumanAI,
        struct real64x3_t *ptDestPos)
{
  int v3; // eax
  struct QTask_s *ptParent; // edx
  double v5; // st7
  double v6; // st6
  long double v7; // st4
  long double v8; // st7
  long double v9; // st4
  long double v10; // st7
  int v11; // eax
  enum HumanAIMovementDirection_e eLastMovementDirection; // ecx
  float v13; // [esp+8h] [ebp-1Ch]
  float v14; // [esp+8h] [ebp-1Ch]
  float v15; // [esp+Ch] [ebp-18h]
  float v16; // [esp+Ch] [ebp-18h]
  float v17; // [esp+14h] [ebp-10h]
  float v18; // [esp+18h] [ebp-Ch]
  float v19; // [esp+18h] [ebp-Ch]

  v3 = ptHumanAI->anEventPriorityList[5];
  ptParent = ptHumanAI->tQTask.ptParent;
  if ( (v3 & 4) == 0 )
    goto LABEL_6;
  if ( (v3 & 8) != 0 )
    goto LABEL_6;
  if ( Real64x3_NullVector((struct real64x3_t *)&ptHumanAI->tCommon.nIgnoreVisibilityFactorTimer) )
    goto LABEL_6;
  v5 = *(double *)&ptHumanAI->tCommon.nIgnoreVisibilityFactorTimer - *(double *)&ptParent[1].ptNext;
  v6 = *(double *)&ptHumanAI->tCommon.isDetectionSoundPlayed - *(double *)&ptParent[1].tQTaskChildren.ptHead;
  v13 = ptDestPos->vX - *(double *)&ptParent[1].ptNext;
  v15 = ptDestPos->vY - *(double *)&ptParent[1].tQTaskChildren.ptHead;
  v7 = sqrt(v5 * v5 + v6 * v6);
  if ( v7 == 0.0
    || (v17 = 1.0 / v7 * v5,
        v18 = v6,
        v19 = v18 * (1.0 / v7),
        v8 = 1.0 / v7 * 0.0,
        v9 = sqrt(v13 * v13 + v15 * v15),
        v9 == 0.0) )
  {
LABEL_6:
    HumanAI_PointCharacterTowardsDestinationForward(ptHumanAI, ptDestPos);
  }
  else
  {
    v14 = v13 * (1.0 / v9);
    v16 = v15 * (1.0 / v9);
    v10 = v8 * (1.0 / v9 * 0.0) + v16 * v19 + v14 * v17;
    if ( v10 <= 0.699999988079071 )
    {
      if ( v10 >= -0.699999988079071 )
      {
        v11 = 3;
        if ( v14 * v19 - v16 * v17 <= 0.0 )
          v11 = 2;
      }
      else
      {
        v11 = HumanAI_GetTargetQTask(ptHumanAI, true) != nullptr ? 4 : 1;
      }
    }
    else
    {
      v11 = 1;
    }
    eLastMovementDirection = ptHumanAI->eLastMovementDirection;
    switch ( v11 )
    {
      case 1:
      case 4:
        if ( eLastMovementDirection == HUMANAI_MOVEMENTDIRECTION_FORWARD
          || eLastMovementDirection == HUMANAI_MOVEMENTDIRECTION_BACKWARD )
        {
          goto LABEL_22;
        }
        if ( !ptHumanAI->anEventPriorityList[4] )
          eLastMovementDirection = v11;
        break;
      case 2:
      case 3:
        if ( eLastMovementDirection == HUMANAI_MOVEMENTDIRECTION_LEFT
          || eLastMovementDirection == HUMANAI_MOVEMENTDIRECTION_RIGHT
          || !ptHumanAI->anEventPriorityList[4] )
        {
LABEL_22:
          eLastMovementDirection = v11;
        }
        break;
    }
    switch ( eLastMovementDirection )
    {
      case HUMANAI_MOVEMENTDIRECTION_LEFT:
        HumanAI_PointCharacterTowardsDestinationLeft(ptHumanAI, ptDestPos);
        break;
      case HUMANAI_MOVEMENTDIRECTION_RIGHT:
        HumanAI_PointCharacterTowardsDestinationRight(ptHumanAI, ptDestPos);
        break;
      case HUMANAI_MOVEMENTDIRECTION_BACKWARD:
        HumanAI_PointCharacterTowardsDestinationBackward(ptHumanAI, ptDestPos);
        break;
      default:
        HumanAI_PointCharacterTowardsDestinationForward(ptHumanAI, ptDestPos);
        break;
    }
    if ( !ptHumanAI->anEventPriorityList[4] )
      ptHumanAI->anEventPriorityList[4] = 30;
  }
}

// source: j/0/humanai/humanai.c:9089  [anchor-caller]
int __cdecl HumanAI_MoveCharacter(struct HumanAI_s *ptHumanAI)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct Node_s *result; };
    struct { char igi2_o1[4]; struct HumanAI_s *v35; };
    struct { char igi2_o2[4]; struct real64x3_t *v36; };
    struct { char igi2_o3[8]; struct real64x3_t *v37; };
    struct { char igi2_o4[12]; double *v38; };
    struct { char igi2_o5[16]; float v39; };
    struct { char igi2_o6[20]; float v40; };
    struct { char igi2_o7[28]; struct HumanAIEventContext_t Buffer[2]; };
    char igi2_extent[156];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptParent; // ebx
  struct Node_s *ptHead; // esi
  int v3; // eax
  int v4; // eax
  struct WeaponType_s *WeaponTypeFromID; // edi
  struct real64x3_t *v6; // esi
  struct Node_s *v7; // eax
  int v8; // eax
  struct WeaponType_s *v9; // eax
  int v10; // edi
  __int16 v11; // ax
  int v12; // esi
  int v13; // ecx
  void (__cdecl *v14)(int, struct HumanAIEventContext_t *); // edx
  int v15; // edi
  __int16 v16; // ax
  int v17; // esi
  int v18; // ecx
  void (__cdecl *pfHandler)(int, struct HumanAIEventContext_t *); // edx
  struct QReference_s *vY_high; // eax
  int v21; // eax
  int v22; // ebx
  struct QTask_s *v23; // ecx
  int DoorStatus; // esi
  struct Node_s *ptNext; // edx
  double v26; // st3
  struct QReference_s *ptTail; // eax
  unsigned int bQTaskMask; // eax
  int LevelQTaskIDFromQTask; // eax
  int v30; // eax
  struct Node_s *v31; // eax
  struct HumanAIMovementQueueItem_t *v32; // eax
  struct QReference_s *v33; // eax

  ptParent = ptHumanAI->tQTask.ptParent;
  igi2_frame.v38 = (double *)ptParent;
  if ( !ptParent )
    return 2;
  igi2_frame.v35 = (struct HumanAI_s *)ptParent->ptParent;
  if ( !igi2_frame.v35 )
    return 2;
  ptHead = ptHumanAI->tMovementQueue.ptHead;
  igi2_frame.result = ptHead;
  if ( !ptHead->ptNext || !ptHead )
    return 2;
  if ( HumanAnim_IsBlendFinished(ptParent) == false )
    return 1;
  switch ( (unsigned int)ptHead[4].ptNext )
  {
    case 1u:
      igi2_frame.v36 = (struct real64x3_t *)&ptHead[1];
      if ( HumanAI_IsDestinationReached(ptHumanAI, (struct real64x3_t *)&ptHead[1]) )
      {
        if ( !BYTE2(ptHumanAI->tCommon.tTargetPosition.vY) )
        {
          qmemcpy(igi2_frame.Buffer, &ptHead[1], 0x18u);
          igi2_frame.Buffer[0].tDirection.vY = 0.0;
          igi2_frame.Buffer[0].tDirection.vZ = -1.875;
          igi2_frame.Buffer[0].ptReferenceQTask = nullptr;
          v15 = 0;
          if ( GameFunctions_ptActivateQTaskList->nTask > 0 )
          {
            v16 = HumanAI_eFindActivateQTaskEvent;
            v17 = 8;
            do
            {
              if ( v16 == 512 )
              {
                v16 = QTask_NewQTaskEventFn(0, "HumanAIFindActivate");
                HumanAI_eFindActivateQTaskEvent = v16;
              }
              v18 = *(int *)((char *)&GameFunctions_ptActivateQTaskList->nTask + v17);
              pfHandler = (void (__cdecl *)(int, struct HumanAIEventContext_t *))QTask_aatQTaskFinalEvent[v16][*(unsigned __int16 *)(v18 + 36)].pfHandler;
              if ( pfHandler )
              {
                pfHandler(v18, igi2_frame.Buffer);
                v16 = HumanAI_eFindActivateQTaskEvent;
              }
              ++v15;
              v17 += 4;
            }
            while ( v15 < GameFunctions_ptActivateQTaskList->nTask );
          }
          vY_high = (struct QReference_s *)HIDWORD(ptHumanAI->tCommon.tTargetPosition.vY);
          if ( vY_high )
          {
            QReference_Delete(vY_high, &QTask_tQTaskRefPool);
            HIDWORD(ptHumanAI->tCommon.tTargetPosition.vY) = 0;
          }
          if ( igi2_frame.Buffer[0].ptReferenceQTask )
            HIDWORD(ptHumanAI->tCommon.tTargetPosition.vY) = QTask_NewQTaskRef(igi2_frame.Buffer[0].ptReferenceQTask);
          ptHead = igi2_frame.result;
          BYTE2(ptHumanAI->tCommon.tTargetPosition.vY) = 1;
        }
        v21 = HIDWORD(ptHumanAI->tCommon.tTargetPosition.vY);
        if ( v21 )
        {
          v22 = *(_DWORD *)(v21 + 8);
          if ( v22 )
          {
            v23 = *(struct QTask_s **)(v21 + 8);
            DoorStatus = Door_GetDoorStatus(v23);
            if ( sub_5437C0((int)v23) )
            {
              ptNext = igi2_frame.result->ptNext;
              if ( igi2_frame.result->ptNext->ptNext )
              {
                if ( ptNext )
                {
                  igi2_frame.v39 = *(double *)&HumanPlayer_ptQTask[1].ptNext - igi2_frame.v38[5];
                  igi2_frame.v40 = *(double *)&HumanPlayer_ptQTask[1].tQTaskChildren.ptHead - igi2_frame.v38[6];
                  v26 = *(double *)&HumanPlayer_ptQTask[1].tQTaskChildren.ptTail - igi2_frame.v38[7];
                  if ( sqrt(igi2_frame.v39 * igi2_frame.v39 + igi2_frame.v40 * igi2_frame.v40 + v26 * v26) < 12288.0 )
                  {
                    igi2_frame.Buffer[0].eEvent = 39;
                    igi2_frame.Buffer[0].bFlags = 0;
                    igi2_frame.Buffer[0].vRadius = 614400.0;
                    igi2_frame.Buffer[0].ptPosition = (struct real64x3_t *)&ptNext[1];
                    igi2_frame.Buffer[0].tDirection.vX = 0.0;
                    igi2_frame.Buffer[0].tDirection.vY = 0.0;
                    igi2_frame.Buffer[0].tDirection.vZ = 0.0;
                    igi2_frame.Buffer[0].ptReferenceQTask = nullptr;
                    ptTail = HumanPlayer_ptQTask[10].tQTaskRefList.ptTail;
                    igi2_frame.Buffer[0].ptHumanOriginatorQTask = HumanPlayer_ptQTask;
                    igi2_frame.Buffer[0].eTeam = (int)ptTail;
                    HumanAI_SendEventSpecificQTask(&ptHumanAI->tQTask, igi2_frame.Buffer);
                  }
                }
              }
            }
            else
            {
              bQTaskMask = ptHumanAI->tAIDetection.atListItems[0].bQTaskMask;
              if ( *(_DWORD *)bQTaskMask && bQTaskMask && *(_BYTE *)(bQTaskMask + 56) )
                AIDetection_ClearDetection((struct AIDetection_s *)&ptHumanAI->tAIDetection.tFriendList);
            }
            switch ( DoorStatus )
            {
              case 0:
                *(_DWORD *)(v22 + 928) = 300;
                goto LABEL_64;
              case 1:
                *(_BYTE *)(v22 + 942) ^= 1u;
                *(_BYTE *)(v22 + 941) = 1;
                HumanAI_FacePositionSelectSpeed(ptHumanAI, igi2_frame.v36, 0.03490658476948738, true);
                return 1;
              case 2:
                LevelQTaskIDFromQTask = Level_GetLevelQTaskIDFromQTask((struct QTask_s *)v22);
                sprintf((char *const)igi2_frame.Buffer, "Waiting for door %i to open", LevelQTaskIDFromQTask);
                HumanAI_FacePositionSelectSpeed(ptHumanAI, igi2_frame.v36, 0.03490658476948738, true);
                return 1;
              case 3:
                v30 = Level_GetLevelQTaskIDFromQTask((struct QTask_s *)v22);
                sprintf((char *const)igi2_frame.Buffer, "Waiting for door %i to close", v30);
                *(_BYTE *)(v22 + 942) ^= 1u;
                *(_BYTE *)(v22 + 941) = 1;
                HumanAI_FacePositionSelectSpeed(ptHumanAI, igi2_frame.v36, 0.03490658476948738, true);
                return 1;
              default:
                goto LABEL_64;
            }
          }
          goto LABEL_64;
        }
        goto LABEL_65;
      }
      HumanAI_PointCharacterTowardsDestination(ptHumanAI, (struct real64x3_t *)&ptHead[1]);
      v3 = 1;
      break;
    case 2u:
    case 3u:
      if ( ptHead[5].ptNext )
      {
        if ( ptParent[31].ptPrev != (struct QTask_s *)84 )
        {
          igi2_frame.v37 = ptHead->ptNext->ptNext != nullptr ? (struct real64x3_t *)&ptHead->ptNext[1] : (struct real64x3_t *)8;
          Human_PopPosition(ptParent, igi2_frame.v37);
          qmemcpy(&ptHead[1], igi2_frame.v37, 0x18u);
LABEL_64:
          ptHead = igi2_frame.result;
          goto LABEL_65;
        }
        ptHumanAI->avChannel[36] = 1.0;
        v3 = 1;
      }
      else
      {
        ptHumanAI->avChannel[36] = 1.0;
        if ( ptParent[31].ptPrev != (struct QTask_s *)84 )
          return 1;
        ptHead[5].ptNext = (struct Node_s *)1;
        v3 = 1;
      }
      break;
    case 4u:
      v4 = Script_ParseLineInt32("WEAPON_ID_FLASHBANG");
      WeaponTypeFromID = WeaponType_GetWeaponTypeFromID(v4);
      if ( !WeaponTypeFromID )
        goto LABEL_65;
      v6 = (struct real64x3_t *)&ptHead[1];
      if ( HumanAI_FacePosition(ptHumanAI, v6, 0.0872664675116539, true) == false )
        return 1;
      ptHumanAI->avChannel[42] = 1.0;
      ptHumanAI->tCommon.nCurrentStartNode = WeaponTypeFromID->eID;
      qmemcpy(&ptHumanAI->tCommon.nIgnoreVisibilityFactorTimer, v6, 0x18u);
      if ( ptParent[31].ptPrev != (struct QTask_s *)12 )
        return 1;
      igi2_frame.result[4].ptNext = (struct Node_s *)5;
      v3 = 1;
      break;
    case 5u:
      v7 = ptHead + 1;
      qmemcpy(&ptHumanAI->tCommon.nIgnoreVisibilityFactorTimer, &ptHead[1], 0x18u);
      if ( ptParent[31].ptPrev != (struct QTask_s *)12 )
      {
        qmemcpy(v7, &ptParent[1], 0x18u);
        v8 = Script_ParseLineInt32("WEAPON_ID_GRENADE");
        v9 = WeaponType_GetWeaponTypeFromID(v8);
        if ( v9 )
          ptHumanAI->tCommon.nCurrentStartNode = v9->eID;
        goto LABEL_65;
      }
      qmemcpy(igi2_frame.Buffer, v7, 0x18u);
      igi2_frame.Buffer[0].tDirection.vY = 0.0;
      igi2_frame.Buffer[0].tDirection.vZ = -1.875;
      igi2_frame.Buffer[0].ptReferenceQTask = nullptr;
      v10 = 0;
      if ( GameFunctions_ptActivateQTaskList->nTask > 0 )
      {
        v11 = HumanAI_eFindActivateQTaskEvent;
        v12 = 8;
        do
        {
          if ( v11 == 512 )
          {
            v11 = QTask_NewQTaskEventFn(0, "HumanAIFindActivate");
            HumanAI_eFindActivateQTaskEvent = v11;
          }
          v13 = *(int *)((char *)&GameFunctions_ptActivateQTaskList->nTask + v12);
          v14 = (void (__cdecl *)(int, struct HumanAIEventContext_t *))QTask_aatQTaskFinalEvent[v11][*(unsigned __int16 *)(v13 + 36)].pfHandler;
          if ( v14 )
          {
            v14(v13, igi2_frame.Buffer);
            v11 = HumanAI_eFindActivateQTaskEvent;
          }
          ++v10;
          v12 += 4;
        }
        while ( v10 < GameFunctions_ptActivateQTaskList->nTask );
        if ( igi2_frame.Buffer[0].ptReferenceQTask && igi2_frame.Buffer[0].ptReferenceQTask->eQTaskType == Door_eQTaskType )
          igi2_frame.Buffer[0].ptReferenceQTask[23].tQTaskChildren.ptHead = (struct QTask_s *)300;
      }
      igi2_frame.v35->atPatrolPathStackItems[2].nCurrentCommandQTaskID = 150;
      v3 = 1;
      break;
    default:
LABEL_65:
      HumanAI_PointCharacterTowardsDestination(ptHumanAI, (struct real64x3_t *)&ptHead[1]);
      if ( HumanAI_IsDestinationReached(ptHumanAI, (struct real64x3_t *)&ptHead[1]) == false )
        return 1;
      v31 = (struct Node_s *)HIDWORD(ptHumanAI->tCommon.tAimPosition.vY);
      if ( v31 != ptHead[4].ptPrev )
        LODWORD(ptHumanAI->tCommon.tAimPosition.vY) = v31;
      HumanAI_SetCurrentNode(ptHumanAI, (int)ptHead[4].ptPrev);
      v32 = (struct HumanAIMovementQueueItem_t *)Node_Remove(igi2_frame.result);
      HumanAI_AddToFreeMovementQueue(ptHumanAI, v32);
      ptHumanAI->tLegalNodesData.isUseLegalNodes = 0;
      HumanAI_SetLegalNodes(ptHumanAI);
      if ( BYTE2(ptHumanAI->tCommon.tTargetPosition.vY) )
      {
        v33 = (struct QReference_s *)HIDWORD(ptHumanAI->tCommon.tTargetPosition.vY);
        if ( v33 )
        {
          QReference_Delete(v33, &QTask_tQTaskRefPool);
          HIDWORD(ptHumanAI->tCommon.tTargetPosition.vY) = 0;
        }
        BYTE2(ptHumanAI->tCommon.tTargetPosition.vY) = 0;
      }
      v3 = 0;
      break;
  }
  return v3;
}

// source: j/0/humanai/humanai.c:9396  [anchor-callee]
void __cdecl HumanAI_CreateQueueItemListFromAStarSearchPath(
        struct HumanAI_s *ptHumanAI,
        struct AIGraphAStarSearchData_s *ptSearchData)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct AIGraphAStarSearchNode_s *v49; };
    struct { char igi2_o1[4]; struct AIGraphAStarSearchNode_s *v50; };
    struct { char igi2_o2[8]; struct List_s *a2; };
    struct { char igi2_o3[8]; struct GraphLink_s **a2a; };
    struct { char igi2_o4[12]; int v53; };
    struct { char igi2_o5[16]; float v54; };
    struct { char igi2_o6[20]; float v55; };
    struct { char igi2_o7[24]; float v56; };
    struct { char igi2_o8[24]; float v57; };
    struct { char igi2_o9[28]; double v58[3]; };
    char igi2_extent[56];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Node_s *ptHead; // esi
  int ptPrev; // ebp
  int v4; // edi
  int v5; // ecx
  double v6; // st7
  struct QReference_s *vY_high; // eax
  _DWORD *v8; // ebp
  struct AIGraphAStarSearchNode_s *v9; // ecx
  struct AIAStarSearchList_s *p_tCurrentPath; // eax
  struct AIGraphAStarSearchNode_s *v11; // esi
  int nNodeId; // edi
  struct Node_s *v13; // ebx
  int GraphNodeDataSize; // eax
  struct Node_s *v15; // edi
  _DWORD *v16; // eax
  struct Node_s *v17; // ebp
  int v18; // esi
  struct Node_s *v19; // esi
  struct QTask_s *p_tQTask; // edx
  int v21; // edi
  int v22; // ebx
  int v23; // eax
  struct GraphNode_s *v24; // ebx
  struct QTask_s *ptParent; // eax
  struct QTask_s *ptTail; // ecx
  int v27; // ecx
  struct HumanAIMovementQueueItem_t *FreeMovementQueueItem; // eax
  int v29; // edi
  struct HumanAIMovementQueueItem_t *v30; // ebp
  double v31; // st7
  double v32; // st6
  long double v33; // st3
  struct HumanAIMovementQueueItem_t *v34; // ebp
  int v35; // edi
  struct GraphLink_s *v36; // eax
  int v37; // eax
  struct HumanAIMovementQueueItem_t *v38; // ebp
  int v39; // edi
  bool v40; // zf
  struct Node_s *v41; // esi
  _DWORD *v42; // eax
  struct Node_s *v43; // edi
  int v44; // ebp
  int v45; // esi
  int v46; // ecx
  double v47; // st7
  struct AIGraphAStarSearchNode_s *ptNext; // eax
  struct GraphNode_s *ptSearchDataa = *(struct GraphNode_s * *)&ptSearchData; // [esp+54h] [ebp+8h] ARGSLOT

  ptHead = ptHumanAI->tMovementQueue.ptHead;
  igi2_frame.a2 = &ptHumanAI->tMovementQueue;
  if ( ptHead->ptNext && ptHead )
  {
    do
    {
      Node_Remove(ptHead);
      ptPrev = (int)ptHead[4].ptPrev;
      ptHead->ptPrev = nullptr;
      ptHead->ptNext = nullptr;
      v4 = *(_DWORD *)&ptHumanAI->zScriptFile[36];
      if ( v4 )
      {
        if ( *(_DWORD *)(v4 + 132) )
        {
          if ( ptPrev < (int)(*(_DWORD *)(v4 + 104)) && ptPrev >= 0 )
          {
            v5 = ptPrev * Graph_GetGraphNodeDataSize(*(_DWORD *)&ptHumanAI->zScriptFile[36]) + *(_DWORD *)(v4 + 132);
            if ( *(_DWORD *)v5 != -1 )
            {
              v6 = *(float *)(v5 + 584) - 20480.0;
              *(float *)(v5 + 584) = v6;
              if ( v6 <= 0.0 )
                v6 = 0.0;
              *(float *)(v5 + 584) = v6;
            }
          }
        }
      }
      ptHead->ptPrev = nullptr;
      ptHead->ptNext = nullptr;
      List_AddTail(ptHead, (int)&HumanAI_tFreeMovementQueue);
      ptHead = igi2_frame.a2->ptHead;
    }
    while ( igi2_frame.a2->ptHead->ptNext && ptHead );
  }
  HumanAI_ClearMovementQueue(ptHumanAI);
  if ( BYTE2(ptHumanAI->tCommon.tTargetPosition.vY) )
  {
    vY_high = (struct QReference_s *)HIDWORD(ptHumanAI->tCommon.tTargetPosition.vY);
    if ( vY_high )
    {
      QReference_Delete(vY_high, &QTask_tQTaskRefPool);
      HIDWORD(ptHumanAI->tCommon.tTargetPosition.vY) = 0;
    }
    BYTE2(ptHumanAI->tCommon.tTargetPosition.vY) = 0;
  }
  v8 = *(_DWORD **)&ptHumanAI->zScriptFile[36];
  if ( ptSearchData->nGraphId != v8[24]
    || ptSearchData->nSourceNodeId != HIDWORD(ptHumanAI->tCommon.tAimPosition.vZ)
    || ptSearchData->nDestNodeId != LODWORD(ptHumanAI->tCommon.tAimPosition.vZ)
    || (v9 = ptSearchData->tCurrentPath.ptHead, p_tCurrentPath = &ptSearchData->tCurrentPath, !v9->ptNext)
    || !v9 )
  {
    p_tCurrentPath = nullptr;
  }
  v11 = p_tCurrentPath->ptHead->ptNext != nullptr ? p_tCurrentPath->ptHead : nullptr;
  nNodeId = v11->nNodeId;
  igi2_frame.v49 = v11->ptNext->ptNext != nullptr ? v11->ptNext : nullptr;
  v13 = nullptr;
  igi2_frame.v50 = v11;
  if ( v8[33] && nNodeId < (int)(v8[26]) && nNodeId >= 0 )
  {
    GraphNodeDataSize = Graph_GetGraphNodeDataSize((int)v8);
    ptSearchDataa = *(_DWORD *)(v8[33] + nNodeId * GraphNodeDataSize) == -1
                  ? nullptr
                  : (struct GraphNode_s *)(nNodeId * GraphNodeDataSize + v8[33]);
  }
  else
  {
    ptSearchDataa = nullptr;
  }
  v15 = HumanAI_tFreeMovementQueue.ptHead;
  if ( HumanAI_tFreeMovementQueue.ptHead->ptNext )
  {
    v16 = Node_Remove(HumanAI_tFreeMovementQueue.ptHead);
    v15->ptPrev = nullptr;
    v15->ptNext = nullptr;
    List_AddTail(v16, (int)igi2_frame.a2);
    v13 = v15;
  }
  v17 = v13 + 4;
  v13[4].ptNext = nullptr;
  v18 = v11->nNodeId;
  v13[4].ptPrev = (struct Node_s *)v18;
  Graph_AddWeightToNode(*(struct Graph_s **)&ptHumanAI->zScriptFile[36], v18, 20480.0);
  v19 = v13 + 1;
  Graph_GetNodePos((struct real64x3_t *)&v13[1], ptSearchDataa);
  if ( igi2_frame.v49 )
  {
    do
    {
      p_tQTask = &ptHumanAI->tQTask;
      v21 = *(_DWORD *)&ptHumanAI->zScriptFile[36];
      v22 = igi2_frame.v49->nNodeId;
      if ( *(_DWORD *)(v21 + 132) && v22 < (int)(*(_DWORD *)(v21 + 104)) && v22 >= 0 )
      {
        v23 = Graph_GetGraphNodeDataSize(*(_DWORD *)&ptHumanAI->zScriptFile[36]);
        p_tQTask = &ptHumanAI->tQTask;
        v24 = *(_DWORD *)(*(_DWORD *)(v21 + 132) + v22 * v23) == -1
            ? nullptr
            : (struct GraphNode_s *)(v22 * v23 + *(_DWORD *)(v21 + 132));
      }
      else
      {
        v24 = nullptr;
      }
      if ( (AIGraph_bDoorNodeCriteria & ptSearchDataa->bCriteria) != 0
        && (AIGraph_bDoorNodeCriteria & v24->bCriteria) != 0 )
      {
        ptParent = p_tQTask->ptParent->ptParent;
        v17->ptNext = (struct Node_s *)1;
        ptTail = p_tQTask[110].tQTaskChildren.ptTail;
        if ( ptTail == (struct QTask_s *)1 || ptTail == (struct QTask_s *)3 || ptTail == (struct QTask_s *)5 )
        {
          v27 = (int)ptParent[215].tQTaskChildren.ptHead;
          if ( v27 > 0
            && (ptParent[7 * v27 + 187].ptNext == (struct QTask_s *)3
             || ptParent[7 * v27 + 187].ptNext == (struct QTask_s *)7
             || ptParent[7 * v27 + 187].ptNext == (struct QTask_s *)8)
            && AISquad_IsTeamLeader(ptParent, p_tQTask)
            && v24->ptSectorQTask )
          {
            qmemcpy(igi2_frame.v58, v19, sizeof(igi2_frame.v58));
            FreeMovementQueueItem = HumanAI_GetFreeMovementQueueItem(ptHumanAI);
            v29 = igi2_frame.v50->nNodeId;
            v30 = FreeMovementQueueItem;
            FreeMovementQueueItem->nNodeID = v29;
            Graph_AddWeightToNode(*(struct Graph_s **)&ptHumanAI->zScriptFile[36], v29, 20480.0);
            v30->eAction = 4;
            Graph_GetNodePos(&v30->tPosition, v24);
            igi2_frame.v54 = v30->tPosition.vX - igi2_frame.v58[0];
            v31 = v30->tPosition.vY - igi2_frame.v58[1];
            v32 = v30->tPosition.vZ - igi2_frame.v58[2];
            v33 = sqrt(igi2_frame.v54 * igi2_frame.v54 + v31 * v31 + v32 * v32);
            if ( v33 != 0.0 )
            {
              igi2_frame.v55 = 6144.0 / v33 * v31;
              igi2_frame.v56 = v32;
              igi2_frame.v57 = 6144.0 / v33 * igi2_frame.v56;
              v30->tPosition.vX = igi2_frame.v54 * (6144.0 / v33) + v30->tPosition.vX;
              v30->tPosition.vY = igi2_frame.v55 + v30->tPosition.vY;
              v30->tPosition.vZ = igi2_frame.v57 + v30->tPosition.vZ + 2048.0;
            }
            v34 = HumanAI_GetFreeMovementQueueItem(ptHumanAI);
            v34->eAction = 1;
            v35 = igi2_frame.v50->nNodeId;
            v34->nNodeID = v35;
            Graph_AddWeightToNode(*(struct Graph_s **)&ptHumanAI->zScriptFile[36], v35, 20480.0);
            Graph_GetNodePos(&v34->tPosition, v24);
            igi2_frame.a2a = v24->aptLinks;
            igi2_frame.v53 = 64;
            do
            {
              v36 = *igi2_frame.a2a;
              if ( *igi2_frame.a2a && (AIGraph_bDoorNodeCriteria & ptSearchDataa->bCriteria) == 0 )
              {
                v37 = v36->nID1 == v24->nID ? v36->nID2 : v36->nID1;
                if ( Graph_GetNode(*(struct Graph_s **)&ptHumanAI->zScriptFile[36], v37) )
                {
                  v38 = HumanAI_GetFreeMovementQueueItem(ptHumanAI);
                  v38->eAction = 0;
                  v39 = igi2_frame.v50->nNodeId;
                  v38->nNodeID = v39;
                  Graph_AddWeightToNode(*(struct Graph_s **)&ptHumanAI->zScriptFile[36], v39, 20480.0);
                  Graph_GetNodePos(&v38->tPosition, v24);
                }
              }
              v40 = igi2_frame.v53 == 1;
              ++igi2_frame.a2a;
              --igi2_frame.v53;
            }
            while ( !v40 );
          }
        }
      }
      v41 = HumanAI_tFreeMovementQueue.ptHead;
      if ( HumanAI_tFreeMovementQueue.ptHead->ptNext )
      {
        v42 = Node_Remove(HumanAI_tFreeMovementQueue.ptHead);
        v41->ptPrev = nullptr;
        v41->ptNext = nullptr;
        List_AddTail(v42, (int)&ptHumanAI->tMovementQueue);
        v43 = v41;
      }
      else
      {
        v43 = nullptr;
      }
      v44 = igi2_frame.v49->nNodeId;
      v43[4].ptPrev = (struct Node_s *)v44;
      v45 = *(_DWORD *)&ptHumanAI->zScriptFile[36];
      if ( v45 )
      {
        if ( *(_DWORD *)(v45 + 132) )
        {
          if ( v44 < (int)(*(_DWORD *)(v45 + 104)) && v44 >= 0 )
          {
            v46 = v44 * Graph_GetGraphNodeDataSize(v45) + *(_DWORD *)(v45 + 132);
            if ( *(_DWORD *)v46 != -1 )
            {
              v47 = *(float *)(v46 + 584) + 20480.0;
              *(float *)(v46 + 584) = v47;
              if ( v47 <= 0.0 )
                v47 = 0.0;
              *(float *)(v46 + 584) = v47;
            }
          }
        }
      }
      v19 = v43 + 1;
      v17 = v43 + 4;
      v43[4].ptNext = nullptr;
      Graph_GetNodePos((struct real64x3_t *)&v43[1], v24);
      igi2_frame.v50 = igi2_frame.v49;
      ptNext = igi2_frame.v49->ptNext;
      ptSearchDataa = v24;
      if ( !igi2_frame.v49->ptNext->ptNext )
        break;
      igi2_frame.v49 = igi2_frame.v49->ptNext;
    }
    while ( ptNext );
  }
}

// source: j/0/humanai/humanai.c:9567  [anchor-caller]
enum bool __cdecl HumanAI_MoveCharacterToNode(struct HumanAI_s *ptHumanAI, int nNodeId)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real64x3_t tP1; };
    struct { char igi2_o1[24]; double v22; };
    struct { char igi2_o2[32]; struct real32x3_t tD1; };
    struct { char igi2_o3[48]; struct real64x3_t tP0; };
    struct { char igi2_o4[72]; struct real64x3_t tNodePos; };
    char igi2_extent[100];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptParent; // ebx
  int v4; // esi
  int GraphNodeDataSize; // eax
  struct GraphNode_s *v6; // eax
  struct AIGraphAStarSearchData_s *p_tAStarSearchData; // esi
  struct Graph_s *v8; // esi
  struct AIGraphAStarSearchNode_s *ptHead; // eax
  struct GraphNode_s *Node; // eax
  struct GraphNode_s *v12; // eax
  struct GraphNode_s *v13; // eax
  double vY; // st6
  double vX; // st5
  int vY_high; // edi
  struct Node_s *v17; // eax
  struct Node_s *ptNext; // ecx
  struct Node_s *ptPrev; // ecx
  struct HumanAIMovementQueueItem_t *v20; // eax
  struct Human_s *ptHumanAIa = *(struct Human_s * *)&ptHumanAI; // [esp+78h] [ebp+4h] ARGSLOT

  ptParent = ptHumanAI->tQTask.ptParent->ptParent;
  ptHumanAIa = (struct Human_s *)ptHumanAI->tQTask.ptParent;
  if ( nNodeId == HIDWORD(ptHumanAI->tCommon.tAimPosition.vY) )
  {
    v4 = *(_DWORD *)&ptHumanAI->zScriptFile[36];
    if ( *(_DWORD *)(v4 + 132) && nNodeId < (int)(*(_DWORD *)(v4 + 104)) && nNodeId >= 0 )
    {
      GraphNodeDataSize = Graph_GetGraphNodeDataSize(*(_DWORD *)&ptHumanAI->zScriptFile[36]);
      v6 = *(_DWORD *)(*(_DWORD *)(v4 + 132) + nNodeId * GraphNodeDataSize) == -1
         ? nullptr
         : (struct GraphNode_s *)(nNodeId * GraphNodeDataSize + *(_DWORD *)(v4 + 132));
    }
    else
    {
      v6 = nullptr;
    }
    Graph_GetNodePos(&igi2_frame.tNodePos, v6);
    if ( HumanAI_IsDestinationReached(ptHumanAI, &igi2_frame.tNodePos) )
    {
      p_tAStarSearchData = &ptHumanAI->tAStarSearchData;
LABEL_18:
      AIGraphAStarSearch_Clear(p_tAStarSearchData);
      LODWORD(ptHumanAI->tCommon.tAimPosition.vZ) = HIDWORD(ptHumanAI->tCommon.tAimPosition.vY);
      HumanAI_ClearMovementQueue(ptHumanAI);
      return true;
    }
    if ( ptParent[218].ptPrev == (struct QTask_s *)2 )
      return true;
  }
  v8 = *(struct Graph_s **)&ptHumanAI->zScriptFile[36];
  if ( ptHumanAI->tAStarSearchData.nGraphId == v8->nGraphID
    && ptHumanAI->tAStarSearchData.nSourceNodeId == HIDWORD(ptHumanAI->tCommon.tAimPosition.vZ)
    && ptHumanAI->tAStarSearchData.nDestNodeId == nNodeId )
  {
    ptHead = ptHumanAI->tAStarSearchData.tCurrentPath.ptHead;
    if ( ptHead->ptNext )
    {
      if ( ptHead && ptHumanAI != (struct HumanAI_s *)-312 )
      {
        if ( HumanAI_MoveCharacter(ptHumanAI) == 2 )
        {
          p_tAStarSearchData = &ptHumanAI->tAStarSearchData;
          goto LABEL_18;
        }
        return false;
      }
    }
  }
  if ( !ptHumanAI->tLegalNodesData.isUseLegalNodes )
    goto LABEL_39;
  Node = Graph_GetNode(v8, ptHumanAI->tLegalNodesData.nNodeId1);
  Graph_GetNodePos(&igi2_frame.tP1, Node);
  v12 = Graph_GetNode(*(struct Graph_s **)&ptHumanAI->zScriptFile[36], ptHumanAI->tLegalNodesData.nNodeId2);
  Graph_GetNodePos(&igi2_frame.tNodePos, v12);
  v13 = Graph_GetNode(*(struct Graph_s **)&ptHumanAI->zScriptFile[36], nNodeId);
  Graph_GetNodePos(&igi2_frame.tP0, v13);
  igi2_frame.tD1.vX = igi2_frame.tP1.vX - igi2_frame.tP0.vX;
  igi2_frame.tD1.vY = igi2_frame.tP1.vY - igi2_frame.tP0.vY;
  *(float *)&igi2_frame.tP1.vX = igi2_frame.tNodePos.vX - igi2_frame.tP0.vX;
  *((float *)&igi2_frame.tP1.vX + 1) = igi2_frame.tNodePos.vY - igi2_frame.tP0.vY;
  *(float *)&igi2_frame.tP1.vY = igi2_frame.tNodePos.vZ - igi2_frame.tP0.vZ;
  vY = igi2_frame.tD1.vY;
  vX = igi2_frame.tD1.vX;
  *(double *)&igi2_frame.tD1.vX = *(float *)&igi2_frame.tP1.vY;
  igi2_frame.v22 = *((float *)&igi2_frame.tP1.vX + 1);
  igi2_frame.tP1.vX = *(float *)&igi2_frame.tP1.vX;
  vY_high = sqrt(igi2_frame.tP1.vX * igi2_frame.tP1.vX + igi2_frame.v22 * igi2_frame.v22 + *(float *)&igi2_frame.tP1.vY * *(float *)&igi2_frame.tP1.vY) <= sqrt(
                                                                                           vX * vX
                                                                                         + vY * vY
                                                                                         + (igi2_frame.tP1.vZ - igi2_frame.tP0.vZ)
                                                                                         * (igi2_frame.tP1.vZ - igi2_frame.tP0.vZ))
          ? ptHumanAI->tLegalNodesData.nNodeId2
          : ptHumanAI->tLegalNodesData.nNodeId1;
  if ( vY_high == nNodeId )
  {
LABEL_39:
    vY_high = HIDWORD(ptHumanAI->tCommon.tAimPosition.vY);
    if ( nNodeId == vY_high )
    {
      AIGraphAStarSearch_Clear(&ptHumanAI->tAStarSearchData);
      LODWORD(ptHumanAI->tCommon.tAimPosition.vZ) = HIDWORD(ptHumanAI->tCommon.tAimPosition.vY);
      HumanAI_ClearMovementQueue(ptHumanAI);
      return true;
    }
  }
  AIGraphAStarSearch_Clear(&ptHumanAI->tAStarSearchData);
  if ( !AIGraphAStarSearch_CreatePath(
          &ptHumanAI->tAStarSearchData,
          *(_DWORD *)(*(_DWORD *)&ptHumanAI->zScriptFile[36] + 96),
          vY_high,
          nNodeId,
          0xFFFFFFFF) )
  {
    ptHumanAIa->tHumanDamage.vDamage = ptHumanAIa->tHumanDamage.vMaxDamage + 1.0;
    Human_UpdateDie(ptHumanAIa);
    return false;
  }
  AIGraph_UnlockCoverNode(
    *(struct AIGraph_t **)&ptHumanAI->zScriptFile[36],
    HIDWORD(ptHumanAI->tCommon.tAimPosition.vY));
  HIDWORD(ptHumanAI->tCommon.tAimPosition.vZ) = vY_high;
  LODWORD(ptHumanAI->tCommon.tAimPosition.vZ) = nNodeId;
  HumanAI_CreateQueueItemListFromAStarSearchPath(ptHumanAI, &ptHumanAI->tAStarSearchData);
  v17 = ptHumanAI->tMovementQueue.ptHead->ptNext != nullptr ? ptHumanAI->tMovementQueue.ptHead : nullptr;
  if ( ptHumanAI->tLegalNodesData.isUseLegalNodes )
  {
    ptNext = v17->ptNext;
    if ( v17->ptNext->ptNext )
    {
      if ( ptNext )
      {
        ptPrev = ptNext[4].ptPrev;
        if ( ptPrev == (struct Node_s *)ptHumanAI->tLegalNodesData.nNodeId1
          || ptPrev == (struct Node_s *)ptHumanAI->tLegalNodesData.nNodeId2 )
        {
          v20 = (struct HumanAIMovementQueueItem_t *)Node_Remove(v17);
          HumanAI_AddToFreeMovementQueue(ptHumanAI, v20);
          v17 = ptHumanAI->tMovementQueue.ptHead->ptNext != nullptr ? ptHumanAI->tMovementQueue.ptHead : nullptr;
        }
      }
    }
  }
  HumanAI_PointCharacterTowardsDestination(ptHumanAI, (struct real64x3_t *)&v17[1]);
  return false;
}

// source: j/0/humanai/humanai.c:9728  [anchor-callee]
enum bool __cdecl HumanAI_PatrolMoveCharacterToNode(
        struct HumanAI_s *ptHumanAI,
        int nDestinationNode)
{
  ptHumanAI->avChannel[8] = 0.20943951606750488;
  ptHumanAI->avChannel[9] = 0.20943951606750488;
  return HumanAI_MoveCharacterToNode(ptHumanAI, nDestinationNode);
}

// source: j/0/humanai/humanai.c:9746  [anchor-callee]
enum bool __cdecl HumanAI_AttackMoveCharacterToNode(
        struct HumanAI_s *ptHumanAI,
        int nDestinationNode)
{
  ptHumanAI->avChannel[8] = 0.3141592741012573;
  ptHumanAI->avChannel[9] = 0.3141592741012573;
  return HumanAI_MoveCharacterToNode(ptHumanAI, nDestinationNode);
}

// source: j/0/humanai/humanai.c:9764  [anchor-callee]
enum bool __cdecl HumanAI_FacePosition(
        struct HumanAI_s *ptHumanAI,
        struct real64x3_t *ptTargetPos,
        float vAngleTolerence,
        enum bool isLevelHeight)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real64x3_t v18; };
    struct { char igi2_o1[40]; float v19; };
    struct { char igi2_o2[44]; float v20; };
    struct { char igi2_o3[48]; double v21[3]; };
    char igi2_extent[76];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptParent; // ebx
  void (__cdecl *pfRunCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // eax
  struct real64x3_t *p_tViewPosition; // eax
  int vZ_high; // esi
  double v9; // st7
  double v10; // st6
  double v11; // st5
  double v12; // st7
  double v13; // st7
  double v14; // st6
  double v15; // st6
  double v16; // st7
  float ptTargetPosa = *(float *)&isLevelHeight; // [esp+3Ch] [ebp+8h] ARGSLOT

  ptParent = ptHumanAI->tQTask.ptParent;
  pfRunCallback = ptHumanAI->atActionStackItemList[0].pfRunCallback;
  qmemcpy(igi2_frame.v21, ptTargetPos, sizeof(igi2_frame.v21));
  if ( *(_DWORD *)pfRunCallback
    && pfRunCallback
    && *((void (__cdecl **)(struct HumanAI_s *, struct HumanAIActionStackItem_s *))pfRunCallback + 6) == HumanAIContent_CombatStationaryGunInitCB )
  {
    p_tViewPosition = (struct real64x3_t *)((char *)ptParent[46].tQTaskRefList.ptHead->pxObject + 392);
  }
  else
  {
    p_tViewPosition = &ptHumanAI->tView.tViewPosition;
  }
  if ( isLevelHeight )
  {
    vZ_high = HIDWORD(p_tViewPosition->vZ);
    LODWORD(igi2_frame.v21[2]) = LODWORD(p_tViewPosition->vZ);
    HIDWORD(igi2_frame.v21[2]) = vZ_high;
  }
  v9 = igi2_frame.v21[0] - p_tViewPosition->vX;
  v10 = igi2_frame.v21[1] - p_tViewPosition->vY;
  v11 = igi2_frame.v21[2] - p_tViewPosition->vZ;
  igi2_frame.v21[0] = ptHumanAI->tView.tViewOrientation.tY.vX * v10
         + ptHumanAI->tView.tViewOrientation.tX.vX * v9
         + ptHumanAI->tView.tViewOrientation.tZ.vX * v11;
  igi2_frame.v21[1] = ptHumanAI->tView.tViewOrientation.tY.vY * v10
         + ptHumanAI->tView.tViewOrientation.tZ.vY * v11
         + ptHumanAI->tView.tViewOrientation.tX.vY * v9;
  igi2_frame.v21[2] = ptHumanAI->tView.tViewOrientation.tY.vZ * v10
         + ptHumanAI->tView.tViewOrientation.tZ.vZ * v11
         + ptHumanAI->tView.tViewOrientation.tX.vZ * v9;
  qmemcpy(&igi2_frame.v18, igi2_frame.v21, sizeof(igi2_frame.v18));
  v12 = -GameFunctions_CalcGamma(igi2_frame.v18);
  ptTargetPosa = v12;
  igi2_frame.v19 = v12;
  if ( v12 < 0.0 )
    v12 = -v12;
  if ( v12 <= 1.5707963705062866 )
  {
    qmemcpy(&igi2_frame.v18, igi2_frame.v21, sizeof(igi2_frame.v18));
    v13 = GameFunctions_CalcAlpha(igi2_frame.v18);
  }
  else
  {
    igi2_frame.v21[0] = (ptHumanAI->tView.tViewOrientation.tX.vX + ptHumanAI->tView.tViewOrientation.tX.vZ) * 0.0
           + ptHumanAI->tView.tViewOrientation.tX.vY;
    igi2_frame.v21[1] = (ptHumanAI->tView.tViewOrientation.tY.vZ + ptHumanAI->tView.tViewOrientation.tY.vX) * 0.0
           + ptHumanAI->tView.tViewOrientation.tY.vY;
    igi2_frame.v21[2] = (ptHumanAI->tView.tViewOrientation.tZ.vZ + ptHumanAI->tView.tViewOrientation.tZ.vX) * 0.0
           + ptHumanAI->tView.tViewOrientation.tZ.vY;
    qmemcpy(&igi2_frame.v18, igi2_frame.v21, sizeof(igi2_frame.v18));
    v13 = -GameFunctions_CalcAlpha(igi2_frame.v18);
    v14 = v13;
    if ( v13 < 0.0 )
      v14 = -v13;
    if ( v14 > 1.5707963705062866 )
    {
      if ( v13 >= 0.0 )
        v13 = 3.1415927410125732 - v13;
      else
        v13 = -3.1415927410125732 - v13;
    }
  }
  igi2_frame.v20 = -ptHumanAI->avChannel[8];
  if ( v13 >= igi2_frame.v20 )
  {
    if ( v13 > ptHumanAI->avChannel[8] )
      v13 = ptHumanAI->avChannel[8];
  }
  else
  {
    v13 = igi2_frame.v20;
  }
  v15 = -ptHumanAI->avChannel[9];
  if ( ptTargetPosa >= v15 )
  {
    if ( ptTargetPosa > (double)ptHumanAI->avChannel[9] )
      ptTargetPosa = ptHumanAI->avChannel[9];
  }
  else
  {
    ptTargetPosa = v15;
  }
  ptHumanAI->avChannel[10] = ptTargetPosa * 0.31830987334251404;
  ptHumanAI->avChannel[11] = v13 * 0.31830987334251404;
  v16 = igi2_frame.v19;
  if ( igi2_frame.v19 < 0.0 )
    v16 = -v16;
  if ( v16 <= vAngleTolerence )
    return true;
  HumanAIContent_SetChannel(ptHumanAI, 9, 1.0);
  return false;
}

// source: j/0/humanai/humanai.c:9869  [anchor-callee]
enum bool __cdecl HumanAI_FacePositionSelectSpeed(
        struct HumanAI_s *ptHumanAI,
        struct real64x3_t *ptTargetPos,
        float vAngleTolerence,
        enum bool isLevelHeight)
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
  return HumanAI_FacePosition(ptHumanAI, ptTargetPos, vAngleTolerence, isLevelHeight);
}

// source: j/0/humanai/humanai.c:9893  [anchor-callee]
void __cdecl HumanAI_MakeAIWalk(struct HumanAI_s *ptHumanAI)
{
  struct QTask_s *ptParent; // eax
  float v2; // [esp+0h] [ebp-4h]

  ptParent = ptHumanAI->tQTask.ptParent;
  if ( ptParent->eQTaskType == HumanSoldier_eQTaskType )
  {
    v2 = 0.0;
    if ( !LOBYTE(ptParent[75].ptPrev) )
      v2 = 1.0;
    HumanAIContent_SetChannel(ptHumanAI, 0, v2);
  }
}

// source: j/0/humanai/humanai.c:9918  [anchor-callee]
void __cdecl HumanAI_MakeAIRun(struct HumanAI_s *ptHumanAI)
{
  struct QTask_s *ptParent; // eax
  float v2; // [esp+0h] [ebp-4h]

  ptParent = ptHumanAI->tQTask.ptParent;
  if ( ptParent->eQTaskType == HumanSoldier_eQTaskType )
  {
    v2 = 1.0;
    if ( !LOBYTE(ptParent[75].ptPrev) )
      v2 = 0.0;
    HumanAIContent_SetChannel(ptHumanAI, 0, v2);
  }
}

// source: j/0/humanai/humanai.c:9943  [anchor-mhash]
unsigned int __cdecl HumanAI_ValidateRollDirection(struct HumanAI_s *ptHumanAI)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real64x3_t tLeftPos; };
    struct { char igi2_o1[24]; struct real64x3_t Real64x3_Rotate_tTemp; };
    struct { char igi2_o2[48]; struct real64x3_t tRightPos; };
    char igi2_extent[72];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptParent; // eax
  unsigned int v2; // ebx
  int v3; // esi
  int vY_high; // edi
  double v5; // st7
  int v6; // eax
  struct GraphNode_s *v7; // edi

  ptParent = ptHumanAI->tQTask.ptParent;
  v2 = 3;
  igi2_frame.Real64x3_Rotate_tTemp.vX = (*(float *)&ptParent[3].tQTaskChildren.ptMiddle
                            + *(float *)&ptParent[3].tQTaskChildren.ptHead)
                           * 0.0
                           - *(float *)&ptParent[3].ptPrev * 12288.0;
  igi2_frame.Real64x3_Rotate_tTemp.vY = (*(float *)&ptParent[3].tQTaskRefList.ptMiddle + *(float *)&ptParent[3].tQTaskRefList.ptHead)
                           * 0.0
                           - *(float *)&ptParent[3].tQTaskChildren.ptTail * 12288.0;
  igi2_frame.Real64x3_Rotate_tTemp.vZ = (*(float *)&ptParent[3].eQTaskType + *(float *)&ptParent[3].ptParent) * 0.0
                           - *(float *)&ptParent[3].tQTaskRefList.ptTail * 12288.0;
  qmemcpy(&igi2_frame.tLeftPos, &igi2_frame.Real64x3_Rotate_tTemp, sizeof(igi2_frame.tLeftPos));
  qmemcpy(&igi2_frame.tRightPos, &igi2_frame.Real64x3_Rotate_tTemp, sizeof(igi2_frame.tRightPos));
  igi2_frame.tLeftPos.vX = igi2_frame.Real64x3_Rotate_tTemp.vX + *(double *)&ptParent[1].ptNext;
  igi2_frame.tLeftPos.vY = igi2_frame.tLeftPos.vY + *(double *)&ptParent[1].tQTaskChildren.ptHead;
  v3 = *(_DWORD *)&ptHumanAI->zScriptFile[36];
  vY_high = HIDWORD(ptHumanAI->tCommon.tAimPosition.vY);
  igi2_frame.tLeftPos.vZ = igi2_frame.tLeftPos.vZ + *(double *)&ptParent[1].tQTaskChildren.ptTail;
  igi2_frame.tRightPos.vX = *(double *)&ptParent[1].ptNext - igi2_frame.Real64x3_Rotate_tTemp.vX;
  igi2_frame.tRightPos.vY = *(double *)&ptParent[1].tQTaskChildren.ptHead - igi2_frame.tRightPos.vY;
  v5 = igi2_frame.Real64x3_Rotate_tTemp.vZ + *(double *)&ptParent[1].tQTaskChildren.ptTail;
  v6 = *(_DWORD *)(v3 + 132);
  igi2_frame.tRightPos.vZ = v5;
  if ( !v6 )
    return 0;
  if ( vY_high >= (int)(*(_DWORD *)(v3 + 104)) )
    return 0;
  if ( vY_high < 0 )
    return 0;
  v7 = (struct GraphNode_s *)(vY_high * Graph_GetGraphNodeDataSize(v3) + *(_DWORD *)(v3 + 132));
  if ( v7->nID == -1 )
    return 0;
  if ( !Graph_IsPositionOnNode(&igi2_frame.tLeftPos, v7, 0.0, 0) )
    v2 = 2;
  if ( !Graph_IsPositionOnNode(&igi2_frame.tRightPos, v7, 0.0, 0) )
    v2 &= ~2u;
  return v2;
}

// source: j/0/humanai/humanai.c:10005  [size]
char *__cdecl HumanAI_GetAITypeFromID(int nID)
{
  return HumanAI_azAITypeStrings[nID];
}

// source: j/0/humanai/humanai.c:10020  [size]
struct real64x3_t *__cdecl HumanAI_GetMovementQueueItemPosition(
        struct Node_s *ptMovementQueueItem)
{
  return (struct real64x3_t *)&ptMovementQueueItem[1];
}

// source: j/0/humanai/humanai.c:10040  [anchor-callee]
enum bool __cdecl TraceTrajectory(
        struct real64x3_t *ptPosition,
        struct real32x3_t *ptVelocity,
        struct real64x3_t *ptDest,
        float vAbortDistance,
        int *pnFlyTime)
{
  #pragma pack(push, 1)
  union
  {
    struct { float tDelta; };
    struct { char igi2_o1[4]; float tDelta_4; };
    struct { char igi2_o2[8]; float tDelta_8; };
    struct { char igi2_o3[12]; float tVelocity; };
    struct { char igi2_o4[16]; float tVelocity_4; };
    struct { char igi2_o5[20]; float tVelocity_8; };
    struct { char igi2_o6[24]; float tReal32x3; };
    struct { char igi2_o7[28]; float tReal32x3_4; };
    struct { char igi2_o8[32]; float tReal32x3_8; };
    struct { char igi2_o9[36]; double v28; };
    struct { char igi2_o10[44]; struct real64x3_t ptEnd; };
    struct { char igi2_o11[68]; struct real64x3_t ptStart; };
    struct { char igi2_o12[92]; struct QIntersection_s tIntersection; };
    char igi2_extent[212];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  float vY; // edx
  float vX; // ecx
  float vZ; // eax
  struct real64x3_t *v8; // edx
  int v9; // ebp
  int v10; // eax
  double v11; // st7
  double v12; // st6
  double v13; // st7
  double v14; // st7
  double v15; // st6
  double v16; // st6
  double v17; // st6

  vY = ptVelocity->vY;
  vX = ptVelocity->vX;
  vZ = ptVelocity->vZ;
  igi2_frame.tVelocity = vX;
  igi2_frame.tVelocity_4 = vY;
  v8 = ptPosition;
  qmemcpy(&igi2_frame.ptEnd, ptPosition, sizeof(igi2_frame.ptEnd));
  v9 = 1;
  igi2_frame.tVelocity_8 = vZ;
  *pnFlyTime = 0;
  while ( 1 )
  {
    v10 = 24 * v9;
    igi2_frame.tVelocity_8 = igi2_frame.tVelocity_8 - 44.600887298583984;
    v11 = igi2_frame.tVelocity + *(&igi2_frame.ptStart.vX - 3 * v9);
    *(&igi2_frame.ptEnd.vX + 3 * v9) = v11;
    v12 = igi2_frame.tVelocity_4 + *(&igi2_frame.ptStart.vY - 3 * v9);
    *(double *)((char *)&igi2_frame.ptEnd.vY + v10) = v12;
    igi2_frame.v28 = igi2_frame.tVelocity_8 + *(&igi2_frame.ptStart.vZ - 3 * v9);
    *(double *)((char *)&igi2_frame.ptEnd.vZ + v10) = igi2_frame.v28;
    igi2_frame.tReal32x3 = ptDest->vX - v8->vX;
    igi2_frame.tReal32x3_4 = ptDest->vY - v8->vY;
    igi2_frame.tReal32x3_8 = ptDest->vZ - v8->vZ;
    igi2_frame.tDelta = ptDest->vX - v11;
    igi2_frame.tDelta_4 = ptDest->vY - v12;
    v13 = ptDest->vZ - igi2_frame.v28;
    igi2_frame.tDelta_8 = v13;
    v14 = v13 * igi2_frame.tReal32x3_8 + igi2_frame.tDelta_4 * igi2_frame.tReal32x3_4 + igi2_frame.tDelta * igi2_frame.tReal32x3;
    v15 = igi2_frame.tDelta;
    if ( igi2_frame.tDelta < 0.0 )
      v15 = -v15;
    if ( v15 < vAbortDistance )
    {
      v16 = igi2_frame.tDelta_4;
      if ( igi2_frame.tDelta_4 < 0.0 )
        v16 = -v16;
      if ( v16 < vAbortDistance )
      {
        v17 = igi2_frame.tDelta_8;
        if ( igi2_frame.tDelta_8 < 0.0 )
          v17 = -v17;
        if ( v17 < vAbortDistance )
          return true;
      }
    }
    if ( v14 < 0.0 )
      return true;
    World_TraceLines(
      Game_ptGame->ptWorld,
      &igi2_frame.tIntersection,
      &igi2_frame.ptStart - v9,
      &igi2_frame.ptEnd + v9,
      1,
      512,
      nullptr,
      Forest_bQTaskGroup | 0x18000000);
    if ( igi2_frame.tIntersection.isHit )
      break;
    v8 = ptPosition;
    ++*pnFlyTime;
    v9 = ((_BYTE)v9 - 1) & 1;
  }
  return false;
}

// source: j/0/humanai/humanai.c:10109  [anchor-callee]
enum bool __cdecl HumanAI_GetGrenadeOrientationAndSpeedToTarget(
        struct real32x9_t *ptGrenadeOrientation,
        struct real32x3_t *ptGrenadeSpeed,
        struct HumanAI_s *ptHumanAI,
        struct real64x3_t *ptGrenadePosition,
        int *pnFlyTime)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v15; };
    struct { float v16; };
    struct { char igi2_o2[4]; float v17; };
    struct { char igi2_o3[8]; int v18; };
    struct { char igi2_o4[20]; float v19; };
    struct { char igi2_o5[24]; float v20; };
    struct { char igi2_o6[32]; _DWORD v21[3]; };
    char igi2_extent[44];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct HumanAI_s *v5; // ecx
  int v6; // edx
  struct real64x3_t *p_nIgnoreVisibilityFactorTimer; // ebx
  long double v8; // st7
  double v9; // st7
  long double v10; // st7
  long double v11; // st7
  long double v12; // st7
  long double v13; // st7

  v5 = ptHumanAI;
  v6 = 0;
  igi2_frame.v21[0] = 1065749138;
  igi2_frame.v21[1] = 1061752795;
  igi2_frame.v21[2] = 1057360530;
  igi2_frame.v18 = 0;
  p_nIgnoreVisibilityFactorTimer = (struct real64x3_t *)&ptHumanAI->tCommon.nIgnoreVisibilityFactorTimer;
  while ( 1 )
  {
    v8 = tan(*(float *)&igi2_frame.v21[v6]);
    ptGrenadeOrientation->tX.vX = 1.0;
    ptGrenadeOrientation->tY.vY = 1.0;
    ptGrenadeOrientation->tZ.vZ = 1.0;
    ptGrenadeOrientation->tX.vY = 0.0;
    ptGrenadeOrientation->tX.vZ = 0.0;
    ptGrenadeOrientation->tY.vX = 0.0;
    ptGrenadeOrientation->tY.vZ = 0.0;
    ptGrenadeOrientation->tZ.vX = 0.0;
    ptGrenadeOrientation->tZ.vY = 0.0;
    ptGrenadeOrientation->nOps = 0;
    igi2_frame.v17 = v8;
    igi2_frame.v19 = (p_nIgnoreVisibilityFactorTimer->vX - ptGrenadePosition->vX) * 0.000244140625;
    v9 = (*(double *)&v5->tCommon.isDetectionSoundPlayed - ptGrenadePosition->vY) * 0.000244140625;
    igi2_frame.v20 = v9;
    v10 = sqrt(v9 * igi2_frame.v20 + igi2_frame.v19 * igi2_frame.v19);
    igi2_frame.v15 = v10;
    if ( v10 <= 0.0 )
      goto LABEL_10;
    if ( igi2_frame.v15 >= 50.0 )
      goto LABEL_10;
    v11 = igi2_frame.v15
        * igi2_frame.v15
        * -9.800000190734863
        / (v5->tCommon.tAimPosition.vX * 0.000244140625
         - ptGrenadePosition->vZ * 0.000244140625
         - igi2_frame.v15 * igi2_frame.v17
         + v5->tCommon.tAimPosition.vX * 0.000244140625
         - ptGrenadePosition->vZ * 0.000244140625
         - igi2_frame.v15 * igi2_frame.v17);
    if ( v11 < 0.0 )
      goto LABEL_10;
    v12 = sqrt(v11) * 136.0;
    igi2_frame.v16 = v12;
    ptGrenadeSpeed->vZ = v12 * igi2_frame.v17;
    if ( igi2_frame.v19 != 0.0 || igi2_frame.v20 != 0.0 )
    {
      v13 = 1.0 / sqrt(igi2_frame.v19 * igi2_frame.v19 + igi2_frame.v20 * igi2_frame.v20);
      igi2_frame.v19 = igi2_frame.v19 * v13;
      igi2_frame.v20 = igi2_frame.v20 * v13;
    }
    ptGrenadeSpeed->vX = igi2_frame.v16 * igi2_frame.v19;
    ptGrenadeSpeed->vY = igi2_frame.v16 * igi2_frame.v20;
    if ( TraceTrajectory(ptGrenadePosition, ptGrenadeSpeed, p_nIgnoreVisibilityFactorTimer, 6144.0, pnFlyTime) )
      return true;
    v5 = ptHumanAI;
    v6 = igi2_frame.v18;
LABEL_10:
    igi2_frame.v18 = ++v6;
    if ( v6 >= 3 )
      return false;
  }
}

// source: j/0/humanai/humanai.c:10190  [anchor-callee]
enum bool __cdecl HumanAI_GetActivationStatus(struct QTask_s *ptQTask)
{
  struct Node_s *ptHead; // ecx
  struct Node_s *ptNext; // eax

  ptHead = HumanAI_tActivationList.ptHead;
  ptNext = HumanAI_tActivationList.ptHead->ptNext;
  if ( !HumanAI_tActivationList.ptHead->ptNext )
    return false;
  while ( (struct QTask_s *)ptHead[1].ptNext != ptQTask )
  {
    ptHead = ptNext;
    ptNext = ptNext->ptNext;
    if ( !ptNext )
      return false;
  }
  return true;
}

// source: j/0/humanai/humanai.c:10218  [anchor-hash]
void *__cdecl HumanAI_SetActivationStatus(struct QTask_s *ptQTask, enum bool isStatus)
{
  struct Node_s *ptHead; // esi
  struct Node_s *v3; // edi
  _DWORD *v4; // eax
  void *result; // eax
  struct Node_s *v6; // eax
  struct Node_s *ptNext; // ecx
  _DWORD **v8; // eax

  if ( isStatus )
  {
    ptHead = HumanAI_tActivationFreeList.ptHead;
    if ( HumanAI_tActivationFreeList.ptHead->ptNext )
    {
      v3 = HumanAI_tActivationFreeList.ptHead;
      v4 = Node_Remove(HumanAI_tActivationFreeList.ptHead);
      ptHead->ptPrev = nullptr;
      ptHead->ptNext = nullptr;
      result = List_AddTail(v4, (int)&HumanAI_tActivationList);
      v3[1].ptNext = (struct Node_s *)ptQTask;
      return result;
    }
  }
  else
  {
    v6 = HumanAI_tActivationList.ptHead;
    ptNext = HumanAI_tActivationList.ptHead->ptNext;
    if ( HumanAI_tActivationList.ptHead->ptNext )
    {
      while ( (struct QTask_s *)v6[1].ptNext != ptQTask )
      {
        v6 = ptNext;
        ptNext = ptNext->ptNext;
        if ( !ptNext )
          return nullptr;
      }
      v8 = Node_Remove(v6);
      v8[1] = nullptr;
      *v8 = nullptr;
      List_AddTail(v8, (int)&HumanAI_tActivationFreeList);
    }
  }
  return nullptr;
}

// source: j/0/humanai/humanai.c:10271  [anchor-hash]
void *__cdecl HumanAI_ClearActivationEntry(void *pxActivationEntry)
{
  int v1; // edx
  void *result; // eax
  struct Node_s *ptNext; // ecx
  _DWORD **v4; // eax

  v1 = *((_DWORD *)pxActivationEntry + 2);
  result = HumanAI_tActivationList.ptHead;
  ptNext = HumanAI_tActivationList.ptHead->ptNext;
  if ( HumanAI_tActivationList.ptHead->ptNext )
  {
    while ( *((_DWORD *)result + 2) != v1 )
    {
      result = ptNext;
      ptNext = ptNext->ptNext;
      if ( !ptNext )
        return result;
    }
    v4 = Node_Remove((_DWORD **)result);
    v4[1] = nullptr;
    *v4 = nullptr;
    return List_AddTail(v4, (int)&HumanAI_tActivationFreeList);
  }
  return result;
}

// source: j/0/humanai/humanai.c:10288  [anchor-callee]
enum bool __cdecl HumanAI_HandleCoverSearch(struct HumanAI_s *ptHumanAI, struct real64x3_t *ptPosition)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vDistanceToCover; };
    struct { char igi2_o1[4]; float tReal32x3; };
    struct { char igi2_o2[4]; float tReal32x3a; };
    struct { char igi2_o3[4]; float tReal32x3b; };
    struct { char igi2_o4[4]; float tReal32x3c; };
    struct { char igi2_o5[8]; float tReal32x3_4; };
    struct { char igi2_o6[8]; float tReal32x3_4a; };
    struct { char igi2_o7[8]; float tReal32x3_4b; };
    struct { char igi2_o8[8]; float tReal32x3_4c; };
    struct { char igi2_o9[16]; float vDistanceToTarget; };
    struct { char igi2_o10[20]; struct QTask_s *ptTargetQTask; };
    struct { char igi2_o11[24]; int nCount; };
    struct { char igi2_o12[28]; struct real64x3_t tAIPos; };
    struct { char igi2_o13[52]; struct real64x3_t tNodePos; };
    struct { char igi2_o14[76]; struct real64x3_t tTargetPos; };
    struct { char igi2_o15[100]; struct AIDetectionGetDetectionInfoContext_s tContext; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *TargetQTask; // edi
  enum HumanAICoverNodeSearchState_e eState; // eax
  int v5; // ebx
  int v6; // eax
  struct GraphNode_s *Node; // esi
  double v8; // st7
  long double v9; // st6
  int *abCoverCircle; // ecx
  int *v11; // eax
  int v12; // edx
  double v13; // st7
  long double v14; // st6
  double v15; // st6

  TargetQTask = HumanAI_GetTargetQTask(ptHumanAI, true);
  eState = ptHumanAI->tCoverNodeSearchData.eState;
  igi2_frame.ptTargetQTask = TargetQTask;
  if ( eState == HUMANAI_COVERNODESEARCH_IDLE )
  {
    ptHumanAI->tCoverNodeSearchData.nCoverNodeId = -1;
    ptHumanAI->tCoverNodeSearchData.nCoverNodeToCheck = 0;
    ptHumanAI->tCoverNodeSearchData.eState = HUMANAI_COVERNODESEARCH_FIND_NODE;
    ptHumanAI->tCoverNodeSearchData.vDistance = 0.0;
    return false;
  }
  if ( eState != HUMANAI_COVERNODESEARCH_FIND_NODE )
    return true;
  igi2_frame.nCount = 0;
  while ( 1 )
  {
    v5 = *(_DWORD *)(*(_DWORD *)&ptHumanAI->zScriptFile[36] + 220);
    v6 = 0;
    if ( *(_DWORD *)v5 )
    {
      for ( ; v5; ++v6 )
      {
        if ( v6 >= ptHumanAI->tCoverNodeSearchData.nCoverNodeToCheck )
          break;
        v5 = **(_DWORD **)v5 != 0 ? *(_DWORD *)v5 : 0;
      }
    }
    else
    {
      v5 = 0;
    }
    ++ptHumanAI->tCoverNodeSearchData.nCoverNodeToCheck;
    if ( !v5 )
    {
      ptHumanAI->tCoverNodeSearchData.eState = HUMANAI_COVERNODESEARCH_IDLE;
      return false;
    }
    if ( (*(_BYTE *)(v5 + 8) & 1) != 0 )
      return false;
    Node = Graph_GetNode(*(struct Graph_s **)&ptHumanAI->zScriptFile[36], *(_DWORD *)(v5 + 140));
    if ( !Node )
    {
      ptHumanAI->tCoverNodeSearchData.eState = HUMANAI_COVERNODESEARCH_IDLE;
      return false;
    }
    if ( !ptPosition )
      break;
    Graph_GetNodePos(&igi2_frame.tNodePos, Node);
    qmemcpy(&igi2_frame.tAIPos, &ptHumanAI->tQTask.ptParent[1], sizeof(igi2_frame.tAIPos));
    igi2_frame.tReal32x3 = igi2_frame.tNodePos.vX - igi2_frame.tAIPos.vX;
    igi2_frame.tReal32x3_4 = igi2_frame.tNodePos.vY - igi2_frame.tAIPos.vY;
    v8 = igi2_frame.tNodePos.vZ - igi2_frame.tAIPos.vZ;
    v9 = sqrt(igi2_frame.tReal32x3 * igi2_frame.tReal32x3 + igi2_frame.tReal32x3_4 * igi2_frame.tReal32x3_4 + (igi2_frame.tNodePos.vZ - igi2_frame.tAIPos.vZ) * (igi2_frame.tNodePos.vZ - igi2_frame.tAIPos.vZ));
    igi2_frame.vDistanceToCover = v9;
    if ( v9 < 20480.0 )
    {
      if ( v8 < 0.0 )
        v8 = -v8;
      if ( v8 < 8192.0
        && AIGraph_CoverNodeProvidesCoverFromPosition(
             *(struct AIGraph_t **)&ptHumanAI->zScriptFile[36],
             (struct AIGraphNodeCoverItem_s *)v5,
             ptPosition) )
      {
        goto LABEL_19;
      }
    }
LABEL_34:
    if ( ptHumanAI->tCoverNodeSearchData.nCoverNodeToCheck >= List_Length((_DWORD **)(*(_DWORD *)&ptHumanAI->zScriptFile[36]
                                                                                    + 220)) )
      ptHumanAI->tCoverNodeSearchData.eState = HUMANAI_COVERNODESEARCH_IDLE;
    if ( ++igi2_frame.nCount >= 2 )
      return false;
    TargetQTask = igi2_frame.ptTargetQTask;
  }
  if ( !TargetQTask )
    goto LABEL_34;
  ((void (__cdecl *)(struct QTask_s *, struct AIDetectionGetDetectionInfoContext_s *))QTask_aatQTaskFinalEvent[AIDetection_eGetDetectionInfoQTaskEvent][TargetQTask->eQTaskType].pfHandler)(
    TargetQTask,
    &igi2_frame.tContext);
  Graph_GetNodePos(&igi2_frame.tNodePos, Node);
  qmemcpy(&igi2_frame.tAIPos, &ptHumanAI->tQTask.ptParent[1], sizeof(igi2_frame.tAIPos));
  igi2_frame.tReal32x3a = igi2_frame.tNodePos.vX - igi2_frame.tAIPos.vX;
  igi2_frame.tReal32x3_4a = igi2_frame.tNodePos.vY - igi2_frame.tAIPos.vY;
  v13 = igi2_frame.tNodePos.vZ - igi2_frame.tAIPos.vZ;
  v14 = sqrt(igi2_frame.tReal32x3a * igi2_frame.tReal32x3a + igi2_frame.tReal32x3_4a * igi2_frame.tReal32x3_4a + (igi2_frame.tNodePos.vZ - igi2_frame.tAIPos.vZ)
                                                                   * (igi2_frame.tNodePos.vZ - igi2_frame.tAIPos.vZ));
  igi2_frame.vDistanceToCover = v14;
  if ( v14 >= 81920.0 )
    goto LABEL_34;
  if ( v13 < 0.0 )
    v13 = -v13;
  if ( v13 >= 8192.0 )
    goto LABEL_34;
  qmemcpy(&igi2_frame.tTargetPos, &igi2_frame.ptTargetQTask[1], sizeof(igi2_frame.tTargetPos));
  igi2_frame.tReal32x3b = igi2_frame.tTargetPos.vX - igi2_frame.tAIPos.vX;
  igi2_frame.tReal32x3_4b = igi2_frame.tTargetPos.vY - igi2_frame.tAIPos.vY;
  igi2_frame.vDistanceToTarget = sqrt(
                        igi2_frame.tReal32x3b * igi2_frame.tReal32x3b
                      + igi2_frame.tReal32x3_4b * igi2_frame.tReal32x3_4b
                      + (igi2_frame.tTargetPos.vZ - igi2_frame.tAIPos.vZ) * (igi2_frame.tTargetPos.vZ - igi2_frame.tAIPos.vZ));
  v15 = igi2_frame.tTargetPos.vZ - igi2_frame.tNodePos.vZ;
  if ( v15 < 0.0 )
    v15 = -v15;
  if ( v15 >= 8192.0 )
    goto LABEL_34;
  igi2_frame.tReal32x3c = igi2_frame.tTargetPos.vX - igi2_frame.tNodePos.vX;
  igi2_frame.tReal32x3_4c = igi2_frame.tTargetPos.vY - igi2_frame.tNodePos.vY;
  if ( sqrt(
         igi2_frame.tReal32x3c * igi2_frame.tReal32x3c
       + igi2_frame.tReal32x3_4c * igi2_frame.tReal32x3_4c
       + (igi2_frame.tTargetPos.vZ - igi2_frame.tNodePos.vZ) * (igi2_frame.tTargetPos.vZ - igi2_frame.tNodePos.vZ)) >= igi2_frame.vDistanceToTarget
    || igi2_frame.vDistanceToCover >= (double)igi2_frame.vDistanceToTarget
    || igi2_frame.vDistanceToTarget <= 20480.0
    || !AIGraph_CoverNodeProvidesCoverFromPosition(
          *(struct AIGraph_t **)&ptHumanAI->zScriptFile[36],
          (struct AIGraphNodeCoverItem_s *)v5,
          igi2_frame.tContext.atPosition) )
  {
    goto LABEL_34;
  }
LABEL_19:
  abCoverCircle = ptHumanAI->tCoverNodeSearchData.abCoverCircle;
  v11 = (int *)(v5 + 12);
  v12 = 32;
  do
  {
    *abCoverCircle++ = *v11++;
    --v12;
  }
  while ( v12 );
  ptHumanAI->tCoverNodeSearchData.vDistance = igi2_frame.vDistanceToCover;
  ptHumanAI->tCoverNodeSearchData.nCoverNodeId = *(_DWORD *)(v5 + 140);
  ptHumanAI->tCoverNodeSearchData.eState = HUMANAI_COVERNODESEARCH_NODE_FOUND;
  *(_DWORD *)(v5 + 8) |= 1u;
  return true;
}

// source: j/0/humanai/humanai.c:10463  [anchor-hash]
struct HumanAI_s *__cdecl HumanAI_SetLegalNodes(struct HumanAI_s *ptHumanAI)
{
  int vY_high; // edx
  struct Node_s *ptHead; // ecx
  int ptPrev; // ecx

  if ( !ptHumanAI->tLegalNodesData.isUseLegalNodes )
  {
    vY_high = HIDWORD(ptHumanAI->tCommon.tAimPosition.vY);
    ptHead = ptHumanAI->tMovementQueue.ptHead;
    ptHumanAI->tLegalNodesData.isUseLegalNodes = 1;
    ptHumanAI->tLegalNodesData.nNodeId1 = vY_high;
    if ( ptHead->ptNext && ptHead && (ptPrev = (int)ptHead[4].ptPrev, ptPrev != vY_high) )
      ptHumanAI->tLegalNodesData.nNodeId2 = ptPrev;
    else
      ptHumanAI->tLegalNodesData.isUseLegalNodes = 0;
  }
  return ptHumanAI;
}

// source: j/0/humanai/humanai.c:10497  [anchor-hash]
enum bool __cdecl HumanAI_IsOnCoverNode(struct HumanAI_s *ptHumanAI)
{
  return ptHumanAI->tCoverNodeSearchData.eState == HUMANAI_COVERNODESEARCH_NODE_FOUND
      && ptHumanAI->tCoverNodeSearchData.nCoverNodeId == HIDWORD(ptHumanAI->tCommon.tAimPosition.vY);
}

// source: j/0/humanai/humanai.c:10517  [anchor-hash]
enum bool __cdecl HumanAI_IsOnTheWayToCoverNode(struct HumanAI_s *ptHumanAI)
{
  return ptHumanAI->tCoverNodeSearchData.eState == HUMANAI_COVERNODESEARCH_NODE_FOUND
      && ptHumanAI->tCoverNodeSearchData.nCoverNodeId == LODWORD(ptHumanAI->tCommon.tAimPosition.vZ);
}

// source: j/0/humanai/humanai.c:10537  [anchor-mhash]
void __cdecl HumanAI_TriggerCommunicationEventOnHumanAIs(struct HumanAICommunicationContext_s *ptContext)
{
  struct QTaskList_s *v1; // edi
  int v2; // ebp
  int v3; // ebx
  struct QTask_s *v4; // esi
  struct QTask_s *FirstChildOfType; // eax

  v1 = Human_ptQTaskList;
  v2 = 0;
  if ( Human_ptQTaskList->nTask > 0 )
  {
    v3 = 8;
    do
    {
      v4 = *(struct QTask_s **)((char *)&v1->nTask + v3);
      if ( QTask_IsQTaskTypeDerived(v4->eQTaskType, HumanSoldier_eQTaskType) )
      {
        FirstChildOfType = QTask_GetFirstChildOfType(v4, HumanAI_eQTaskType);
        if ( FirstChildOfType )
        {
          ((void (__cdecl *)(struct QTask_s *, struct HumanAICommunicationContext_s *))QTask_aatQTaskFinalEvent[HumanAI_eCommunicationEvent][FirstChildOfType->eQTaskType].pfHandler)(
            FirstChildOfType,
            ptContext);
          v1 = Human_ptQTaskList;
        }
      }
      ++v2;
      v3 += 4;
    }
    while ( v2 < v1->nTask );
  }
}

// source: j/0/humanai/humanai.c:10575  [anchor-callee]
enum bool __cdecl HumanAI_RecurseNodesFromNode(
        struct HumanAI_s *ptHumanAI,
        struct GraphNode_s *ptStartNode,
        int nMaxChecks,
        enum bool (__cdecl *pfCallback)(struct HumanAI_s *, struct GraphNode_s *, void *),
        void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { int *pnCurrent; };
    struct { char igi2_o1[4]; int nSearches; };
    struct { char igi2_o2[8]; char aisScannedItems[2048]; };
    struct { char igi2_o3[2056]; int anScanList[2048]; };
    char igi2_extent[10248];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int nID; // edx
  int v6; // ebx
  int v7; // esi
  int v8; // edi
  int GraphNodeDataSize; // eax
  struct GraphNode_s *v10; // esi
  int v11; // edx
  struct GraphLink_s **aptLinks; // esi
  struct GraphLink_s *v13; // ecx
  int nID1; // eax
  int v15; // ecx

  igi2_frame.pnCurrent = igi2_frame.anScanList;
  igi2_frame.nSearches = 0;
  if ( !ptStartNode )
    return false;
  if ( !pfCallback )
    return false;
  nID = ptStartNode->nID;
  v6 = 1;
  memset(igi2_frame.aisScannedItems, 0, sizeof(igi2_frame.aisScannedItems));
  igi2_frame.anScanList[0] = nID;
  igi2_frame.anScanList[1] = -1;
  igi2_frame.aisScannedItems[nID] = 1;
  if ( nID == -1 )
    return false;
  while ( 1 )
  {
    v7 = *(_DWORD *)&ptHumanAI->zScriptFile[36];
    v8 = *igi2_frame.pnCurrent;
    if ( *(_DWORD *)(v7 + 132) && v8 < (int)(*(_DWORD *)(v7 + 104)) && v8 >= 0 )
    {
      GraphNodeDataSize = Graph_GetGraphNodeDataSize(*(_DWORD *)&ptHumanAI->zScriptFile[36]);
      v10 = *(_DWORD *)(*(_DWORD *)(v7 + 132) + v8 * GraphNodeDataSize) == -1
          ? nullptr
          : (struct GraphNode_s *)(v8 * GraphNodeDataSize + *(_DWORD *)(v7 + 132));
    }
    else
    {
      v10 = nullptr;
    }
    if ( pfCallback(ptHumanAI, v10, pxContext) )
      break;
    v11 = 0;
    aptLinks = v10->aptLinks;
    do
    {
      if ( igi2_frame.nSearches >= nMaxChecks )
        break;
      v13 = *aptLinks;
      if ( *aptLinks )
      {
        nID1 = v13->nID1;
        if ( *igi2_frame.pnCurrent == nID1 )
          nID1 = v13->nID2;
        if ( nID1 >= 2048 )
          return false;
        if ( !igi2_frame.aisScannedItems[nID1] )
        {
          igi2_frame.anScanList[v6] = nID1;
          igi2_frame.aisScannedItems[nID1] = 1;
          igi2_frame.anScanList[++v6] = -1;
          ++igi2_frame.nSearches;
        }
      }
      ++v11;
      ++aptLinks;
    }
    while ( v11 < 64 );
    v15 = igi2_frame.pnCurrent[1];
    ++igi2_frame.pnCurrent;
    if ( v15 == -1 )
      return false;
  }
  return true;
}

// source: j/0/humanai/humanai.c:10667  [anchor-mhash]
enum bool __cdecl HumanAI_NodeLineOfSightCheck(
        struct GraphNode_s *ptNode,
        struct HumanAI_s *ptHumanAI)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct ObjectCollisionEvaluateContext_t tContext; };
    struct { char igi2_o1[8]; struct LineOfSightOutputContext_s tOutputContext; };
    struct { char igi2_o2[16]; struct real64x3_t tSourcePosition; };
    struct { char igi2_o3[40]; struct real64x3_t tTargetPosition; };
    char igi2_extent[64];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  Graph_GetNodePos(&igi2_frame.tSourcePosition, ptNode);
  igi2_frame.tSourcePosition.vZ = *(double *)(*(_DWORD *)&ptHumanAI->zScriptFile[36] + 152) * 4096.0 + igi2_frame.tSourcePosition.vZ;
  HumanAI_GetTargetPosition(&igi2_frame.tTargetPosition, ptHumanAI);
  igi2_frame.tContext.tCollisionEvaluateContext.ptQTask = ptHumanAI->tQTask.ptParent;
  igi2_frame.tContext.tCollisionEvaluateContext.isEvaluate = 1;
  return World_LineOfSight(
           Game_ptGame->ptWorld,
           &igi2_frame.tSourcePosition,
           &igi2_frame.tTargetPosition,
           GameFunctions_eObjectCollisionEvaluateQTaskEvent,
           &igi2_frame.tContext.tCollisionEvaluateContext,
           0xFFFFFFFF,
           WORLD_DYNCUBETREE_CATEGORY_ALL,
           &igi2_frame.tOutputContext)
      || igi2_frame.tOutputContext.vTransparency >= 0.7900000214576721;
}

// source: j/0/humanai/humanai.c:10717  [anchor-callee]
void __cdecl HumanAI_ClearActionStack(struct HumanAI_s *ptHumanAI)
{
  void (__cdecl *i)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // esi
  void (__cdecl *v2)(struct HumanAI_s *, _DWORD); // eax
  _DWORD *v3; // eax

  for ( i = ptHumanAI->atActionStackItemList[0].pfRunCallback;
        *(_DWORD *)i && i;
        i = ptHumanAI->atActionStackItemList[0].pfRunCallback )
  {
    v2 = *((void (__cdecl **)(struct HumanAI_s *, _DWORD))i + 9);
    if ( v2 )
      v2(ptHumanAI, i);
    Node_Remove((_DWORD **)i);
    v3 = *((_DWORD **)i + 12);
    *((_BYTE *)i + 52) = 0;
    if ( v3 )
    {
      v3[1] = 0;
      *v3 = 0;
      List_AddTail(v3, (int)&ptHumanAI->atPatrolPathStackItems[0].nLastEndCommandQTaskID);
      *((_DWORD *)i + 12) = 0;
    }
  }
}

// source: j/0/humanai/humanai.c:10740  [anchor-caller]
struct HumanAIActionStackItem_s *__cdecl HumanAI_AddAction(
        struct HumanAI_s *ptHumanAI,
        struct HumanAIActionStackItem_s *ptAction)
{
  void (__cdecl **p_pfRunCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // ebx
  void (__cdecl *pfRunCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // eax
  struct HumanAIActionStackItem_s *result; // eax

  p_pfRunCallback = &ptHumanAI->atActionStackItemList[0].pfRunCallback;
  pfRunCallback = ptHumanAI->atActionStackItemList[0].pfRunCallback;
  if ( *(_DWORD *)pfRunCallback && pfRunCallback && (int)(*((_DWORD *)pfRunCallback + 3)) < ptAction->nPriority )
  {
    ptAction->tNode.ptPrev = nullptr;
    ptAction->tNode.ptNext = nullptr;
    List_AddHead(ptAction, (int)&ptHumanAI->atActionStackItemList[0].pfRunCallback);
    ptAction->pfInitCallback(ptHumanAI, ptAction);
    result = *(_DWORD *)*p_pfRunCallback != 0 ? (struct HumanAIActionStackItem_s *)*p_pfRunCallback : nullptr;
    if ( result == ptAction )
      HumanAI_PopActionStackItem(ptHumanAI, ptAction);
  }
  else
  {
    LODWORD(ptHumanAI->tCommon.tAimPosition.vZ) = HIDWORD(ptHumanAI->tCommon.tAimPosition.vY);
    return (struct HumanAIActionStackItem_s *)HumanAI_PushActionStackItem(ptHumanAI, ptAction);
  }
  return result;
}

// source: j/0/humanai/humanai.c:10778  [anchor-callee]
int __cdecl HumanAI_GetNumberOfVisibleTargets(struct QTask_s *ptQTask)
{
  struct QReference_s *ptTail; // ecx
  int result; // eax
  int v3; // edx
  int v4; // edx

  ptTail = ptQTask[222].tQTaskRefList.ptTail;
  for ( result = 0; ptTail->ptNext && ptTail; ptTail = ptTail->ptNext )
  {
    v3 = 0;
    while ( !*((_BYTE *)&ptTail[4].ptNext + v3 + 3) )
    {
      if ( ++v3 >= 3 )
        goto LABEL_10;
    }
    v4 = *((_DWORD *)ptTail->pxObject + 2);
    if ( v4 && !*(_BYTE *)(v4 + 1180) )
      ++result;
LABEL_10:
    ;
  }
  return result;
}

// source: j/0/humanai/humanai.c:10813  [anchor-callee]
void __cdecl HumanAI_FaceTarget(struct HumanAI_s *ptHumanAI)
{
  if ( *(double *)&ptHumanAI->tCommon.nIgnoreVisibilityFactorTimer != 0.0
    || *(double *)&ptHumanAI->tCommon.isDetectionSoundPlayed != 0.0
    || ptHumanAI->tCommon.tAimPosition.vX != 0.0 )
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
    HumanAI_FacePosition(
      ptHumanAI,
      (struct real64x3_t *)&ptHumanAI->tCommon.nIgnoreVisibilityFactorTimer,
      0.0872664675116539,
      true);
  }
}

// source: j/0/humanai/humanai.c:10831  [anchor-hash]
struct HumanAI_s *__cdecl HumanAI_ClearTargetList(struct HumanAI_s *ptHumanAI)
{
  struct HumanAI_s *result; // eax

  AIDetection_ClearDetection((struct AIDetection_s *)&ptHumanAI->tAIDetection.tFriendList);
  return result;
}

// source: j/0/humanai/humanai.c:10845  [anchor-hash]
enum bool __cdecl HumanAI_IsEmptyMovementQueue(struct HumanAI_s *ptHumanAI)
{
  return (ptHumanAI->tMovementQueue.ptHead->ptNext != nullptr ? ptHumanAI->tMovementQueue.ptHead : nullptr) == nullptr;
}

// source: j/0/humanai/humanai.c:10859  [anchor-hash]
enum bool __cdecl HumanAI_IsIdle(struct HumanAI_s *ptHumanAI)
{
  void (__cdecl *pfRunCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // eax

  pfRunCallback = ptHumanAI->atActionStackItemList[0].pfRunCallback;
  return !*(_DWORD *)pfRunCallback
      || !pfRunCallback
      || *((void (__cdecl **)(struct HumanAI_s *, struct HumanAIActionStackItem_s *))pfRunCallback + 6) == HumanAIContent_IdleInitCB;
}

// source: j/0/humanai/humanai.c:10884  [size]
enum bool __cdecl HumanAI_IsWaitingForLeapfrog(struct HumanAI_s *ptHumanAI)
{
  void (__cdecl *pfRunCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // ecx
  enum bool result; // eax

  pfRunCallback = ptHumanAI->atActionStackItemList[0].pfRunCallback;
  result = false;
  if ( *(_DWORD *)pfRunCallback )
  {
    if ( pfRunCallback )
      return *((_DWORD *)pfRunCallback + 6) == (_DWORD)HumanAIContent_WaitForLeapFrogSquadOrderInitCB;
  }
  return result;
}

// source: j/0/humanai/humanai.c:10910  [size]
enum bool __cdecl HumanAI_IsCombatIdle(struct HumanAI_s *ptHumanAI)
{
  void (__cdecl *pfRunCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // ecx
  enum bool result; // eax

  pfRunCallback = ptHumanAI->atActionStackItemList[0].pfRunCallback;
  result = false;
  if ( *(_DWORD *)pfRunCallback )
  {
    if ( pfRunCallback )
      return *((_DWORD *)pfRunCallback + 6) == (_DWORD)HumanAIContent_CombatIdleInitCB;
  }
  return result;
}

// source: j/0/humanai/humanai.c:10936  [size]
enum bool __cdecl HumanAI_IsMovingInFormation(struct HumanAI_s *ptHumanAI)
{
  void (__cdecl *pfRunCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // ecx
  enum bool result; // eax

  pfRunCallback = ptHumanAI->atActionStackItemList[0].pfRunCallback;
  result = false;
  if ( *(_DWORD *)pfRunCallback )
  {
    if ( pfRunCallback )
      return *((_DWORD *)pfRunCallback + 6) == (_DWORD)HumanAIContent_MoveInFormationSquadOrderInitCB;
  }
  return result;
}

// source: j/0/humanai/humanai.c:10962  [size]
enum bool __cdecl HumanAI_IsReloading(struct HumanAI_s *ptHumanAI)
{
  void (__cdecl *pfRunCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // ecx
  enum bool result; // eax

  pfRunCallback = ptHumanAI->atActionStackItemList[0].pfRunCallback;
  result = false;
  if ( *(_DWORD *)pfRunCallback )
  {
    if ( pfRunCallback )
      return *((_DWORD *)pfRunCallback + 11) == (_DWORD)HumanAIContent_ReloadWeaponCB;
  }
  return result;
}

// source: j/0/humanai/humanai.c:10991  [anchor-mhash]
enum bool __cdecl HumanAI_IsFiring(struct HumanAI_s *ptHumanAI)
{
  void (__cdecl *pfRunCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // ecx
  enum bool result; // eax

  pfRunCallback = ptHumanAI->atActionStackItemList[0].pfRunCallback;
  result = false;
  if ( *(_DWORD *)pfRunCallback
    && pfRunCallback
    && *((enum bool (__cdecl **)(struct HumanAI_s *, struct HumanAIActionStackItem_s *))pfRunCallback + 11) == HumanAIContent_FireAtTargetPositionCB
    && !ptHumanAI->tCommon.nCurrentNode )
  {
    return BYTE1(ptHumanAI->tCommon.nPrevNode) != 0;
  }
  return result;
}

// source: j/0/humanai/humanai.c:11022  [anchor-callee]
enum bool __cdecl HumanAI_IsActivating(struct HumanAI_s *ptHumanAI)
{
  void (__cdecl *pfRunCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // ecx
  enum bool result; // eax

  pfRunCallback = ptHumanAI->atActionStackItemList[0].pfRunCallback;
  result = false;
  if ( *(_DWORD *)pfRunCallback )
  {
    if ( pfRunCallback )
      return *((_DWORD *)pfRunCallback + 6) == (_DWORD)HumanAIContent_ActivateInitCB;
  }
  return result;
}

// source: j/0/humanai/humanai.c:11048  [size]
enum bool __cdecl HumanAI_IsPatrolling(struct HumanAI_s *ptHumanAI)
{
  void (__cdecl *pfRunCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // ecx
  enum bool result; // eax

  pfRunCallback = ptHumanAI->atActionStackItemList[0].pfRunCallback;
  result = false;
  if ( *(_DWORD *)pfRunCallback )
  {
    if ( pfRunCallback )
      return *((_DWORD *)pfRunCallback + 6) == (_DWORD)HumanAIContent_PatrolInitCB;
  }
  return result;
}

// source: j/0/humanai/humanai.c:11074  [anchor-callee]
enum bool __cdecl HumanAI_IsMoving(struct HumanAI_s *ptHumanAI)
{
  void (__cdecl *pfRunCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // ecx
  enum bool result; // eax

  pfRunCallback = ptHumanAI->atActionStackItemList[0].pfRunCallback;
  result = false;
  if ( *(_DWORD *)pfRunCallback )
  {
    if ( pfRunCallback )
      return *((_DWORD *)pfRunCallback + 6) == (_DWORD)HumanAIContent_MoveToNodeSquadOrderInitCB;
  }
  return result;
}

int __cdecl sub_46D9F0(int a1)
{
  #pragma pack(push, 1)
  union
  {
    struct { _BYTE v7[8]; };
    struct { char igi2_o1[8]; struct real64x3_t ptPosition; };
    char igi2_extent[88];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  _DWORD *v1; // edi
  int v2; // eax
  int v3; // eax
  int v4; // esi
  struct real64x3_t *p_ptPosition; // ebx

  v1 = **(_DWORD **)(a1 + 8908) != 0 ? *(_DWORD **)(a1 + 8908) : nullptr;
  *(_BYTE *)(a1 + 29016) = 0;
  if ( v1 )
  {
    while ( 1 )
    {
      v2 = v1[2];
      if ( v2 )
      {
        v3 = *(_DWORD *)(v2 + 8);
        if ( v3 )
          break;
      }
LABEL_8:
      v1 = (_DWORD *)*v1;
      if ( !*v1 || !v1 )
        goto LABEL_10;
    }
    ((void (__cdecl *)(int, _BYTE *))QTask_aatQTaskFinalEvent[AIDetection_eGetDetectionInfoQTaskEvent][*(unsigned __int16 *)(v3 + 36)].pfHandler)(
      v3,
      igi2_frame.v7);
    v4 = 0;
    p_ptPosition = &igi2_frame.ptPosition;
    while ( !AIDetection_IsPositionInsideView((struct AIDetectionView_s *)(a1 + 28904), p_ptPosition)
         || !*((_BYTE *)v1 + v4 + 51) )
    {
      ++v4;
      ++p_ptPosition;
      if ( v4 >= 3 )
        goto LABEL_8;
    }
    *(_BYTE *)(a1 + 29016) = 1;
    return 1;
  }
  else
  {
LABEL_10:
    *(_BYTE *)(a1 + 29016) = 1;
    return 0;
  }
}

// source: j/0/humanai/humanai.c:11184  [anchor-mhash]
enum bool __cdecl HumanAI_FindAlternativeNodeCB(
        struct HumanAI_s *ptHumanAI,
        struct GraphNode_s *ptCurrentNode,
        void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vReal32; };
    struct { float vReal32a; };
    struct { char igi2_o2[4]; struct QTask_s *ptHumanQTask; };
    struct { char igi2_o3[8]; float tReal32x3; };
    struct { char igi2_o4[8]; float tReal32x3a; };
    struct { char igi2_o5[8]; float tReal32x3b; };
    struct { char igi2_o6[12]; float tReal32x3_4; };
    struct { char igi2_o7[12]; float tReal32x3_4a; };
    struct { char igi2_o8[12]; float tReal32x3_4b; };
    struct { char igi2_o9[20]; struct real64x3_t tNodePos; };
    char igi2_extent[44];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Game_s *v3; // eax
  unsigned int v4; // edi
  unsigned int v5; // esi
  unsigned int v6; // edx
  double *ptParent; // esi
  struct QTask_s *v8; // edi
  struct QTask_s *TargetQTask; // eax
  _DWORD *i; // edx
  int v11; // ecx
  double v12; // st3
  long double v13; // st4
  long double v14; // st7
  struct GraphNode_s *Node; // eax
  int nTask; // ebx
  int v17; // esi
  unsigned __int16 v18; // dx
  struct QTask_s **ptQTask; // edi
  struct QTask_s *v20; // eax
  struct QTask_s *FirstChildOfType; // eax

  Graph_GetNodePos(&igi2_frame.tNodePos, ptCurrentNode);
  igi2_frame.ptHumanQTask = ptHumanAI->tQTask.ptParent;
  if ( ptCurrentNode->nID != HIDWORD(ptHumanAI->tCommon.tAimPosition.vY) )
  {
    v3 = Game_ptGame;
    v4 = (Game_ptGame->tRunRandomState.anRandom[0] >> 7) ^ Game_ptGame->tRunRandomState.anRandom[2];
    v5 = v4 ^ Game_ptGame->tRunRandomState.anRandom[1];
    v6 = v5 + Game_ptGame->tRunRandomState.anRandom[0];
    Game_ptGame->tRunRandomState.anRandom[0] = v6;
    v3->tRunRandomState.anRandom[2] = v4;
    v3->tRunRandomState.anRandom[1] = v5;
    if ( v6 % 0x64 >= 0x32 )
    {
      ptParent = (double *)ptHumanAI->tQTask.ptParent;
      v8 = nullptr;
      TargetQTask = HumanAI_GetTargetQTask(ptHumanAI, true);
      if ( TargetQTask )
      {
        v8 = TargetQTask;
      }
      else
      {
        for ( i = (_DWORD *)ptHumanAI->tAIDetection.atListItems[0].bQTaskMask; *i && i; i = (_DWORD *)*i )
        {
          v11 = *(_DWORD *)(i[2] + 8);
          if ( v11 )
          {
            if ( !*(_BYTE *)(v11 + 1180) )
            {
              igi2_frame.tReal32x3 = ptParent[5] - *(double *)(v11 + 40);
              igi2_frame.tReal32x3_4 = ptParent[6] - *(double *)(v11 + 48);
              v12 = ptParent[7] - *(double *)(v11 + 56);
              v13 = sqrt(igi2_frame.tReal32x3 * igi2_frame.tReal32x3 + igi2_frame.tReal32x3_4 * igi2_frame.tReal32x3_4 + v12 * v12);
              if ( !v8 || v13 < igi2_frame.vReal32 )
              {
                igi2_frame.vReal32 = v13;
                v8 = *(struct QTask_s **)(i[2] + 8);
              }
            }
          }
        }
      }
      if ( !v8 )
        goto LABEL_18;
      if ( QTask_IsQTaskTypeDerived(v8->eQTaskType, Human_eQTaskType) == false )
        goto LABEL_18;
      igi2_frame.tReal32x3a = *(double *)&v8[1].ptNext - igi2_frame.tNodePos.vX;
      igi2_frame.tReal32x3_4a = *(double *)&v8[1].tQTaskChildren.ptHead - igi2_frame.tNodePos.vY;
      v14 = sqrt(
              igi2_frame.tReal32x3a * igi2_frame.tReal32x3a
            + igi2_frame.tReal32x3_4a * igi2_frame.tReal32x3_4a
            + (*(double *)&v8[1].tQTaskChildren.ptTail - igi2_frame.tNodePos.vZ)
            * (*(double *)&v8[1].tQTaskChildren.ptTail - igi2_frame.tNodePos.vZ));
      if ( v14 >= 4096.0 )
      {
        Node = Graph_GetNode(
                 *(struct Graph_s **)&ptHumanAI->zScriptFile[36],
                 HIDWORD(ptHumanAI->tCommon.tAimPosition.vY));
        Graph_GetNodePos(&igi2_frame.tNodePos, Node);
        igi2_frame.tReal32x3b = *(double *)&v8[1].ptNext - igi2_frame.tNodePos.vX;
        igi2_frame.tReal32x3_4b = *(double *)&v8[1].tQTaskChildren.ptHead - igi2_frame.tNodePos.vY;
        igi2_frame.vReal32a = v14;
        if ( sqrt(
               igi2_frame.tReal32x3b * igi2_frame.tReal32x3b
             + igi2_frame.tReal32x3_4b * igi2_frame.tReal32x3_4b
             + (*(double *)&v8[1].tQTaskChildren.ptTail - igi2_frame.tNodePos.vZ)
             * (*(double *)&v8[1].tQTaskChildren.ptTail - igi2_frame.tNodePos.vZ)) >= igi2_frame.vReal32a )
        {
LABEL_18:
          nTask = Human_ptQTaskList->nTask;
          v17 = 0;
          if ( Human_ptQTaskList->nTask <= 0 )
          {
LABEL_26:
            *(_DWORD *)pxContext = ptCurrentNode->nID;
            return true;
          }
          v18 = HumanAI_eQTaskType;
          ptQTask = Human_ptQTaskList->ptQTask;
          while ( 1 )
          {
            v20 = *ptQTask;
            if ( *ptQTask != igi2_frame.ptHumanQTask && !LOBYTE(v20[29].tQTaskRefList.ptHead) )
            {
              FirstChildOfType = QTask_GetFirstChildOfType(v20, v18);
              if ( FirstChildOfType )
              {
                if ( FirstChildOfType[748].ptParent == (struct QTask_s *)ptCurrentNode->nID
                  || FirstChildOfType[748].tQTaskRefList.ptTail == (struct QReference_s *)ptCurrentNode->nID )
                {
                  break;
                }
              }
            }
            ++v17;
            ++ptQTask;
            if ( v17 >= nTask )
              goto LABEL_26;
          }
        }
      }
    }
  }
  return false;
}

// source: j/0/humanai/humanai.c:11330  [anchor-caller]
void __cdecl HumanAI_FindAlternativeNode(struct HumanAI_s *ptHumanAI)
{
  int v1; // esi
  int vY_high; // edi
  struct GraphNode_s *v3; // ecx
  struct HumanAIFindAlternativeNodeContext_s tContext; // [esp+8h] [ebp-4h] BYREF

  v1 = *(_DWORD *)&ptHumanAI->zScriptFile[36];
  vY_high = HIDWORD(ptHumanAI->tCommon.tAimPosition.vY);
  if ( *(_DWORD *)(v1 + 132) )
  {
    if ( vY_high < (int)(*(_DWORD *)(v1 + 104)) && vY_high >= 0 )
    {
      v3 = (struct GraphNode_s *)(vY_high * Graph_GetGraphNodeDataSize(*(_DWORD *)&ptHumanAI->zScriptFile[36])
                                + *(_DWORD *)(v1 + 132));
      if ( v3->nID != -1 )
      {
        tContext.nNodeId = -1;
        HumanAI_RecurseNodesFromNode(ptHumanAI, v3, 100, HumanAI_FindAlternativeNodeCB, &tContext);
        if ( tContext.nNodeId != -1 )
          LODWORD(ptHumanAI->tCommon.tAimPosition.vZ) = *(_DWORD *)&tContext;
      }
    }
  }
}

// source: j/0/humanai/humanai.c:11366  [anchor-caller]
enum bool __cdecl HumanAI_HandleDispersal(struct HumanAI_s *ptHumanAI)
{
  int vY_high; // esi
  struct QTaskList_s *v3; // eax
  int nTask; // ebx
  int v5; // ebp
  unsigned __int16 v6; // dx
  struct QTask_s **i; // edi
  struct QTask_s *v8; // esi
  struct QTask_s *FirstChildOfType; // eax
  double v10; // st3
  struct QTask_s *ptHumanQTask; // [esp+8h] [ebp-10h]
  float tReal32x3; // [esp+Ch] [ebp-Ch]
  float tReal32x3_4; // [esp+10h] [ebp-8h]

  vY_high = HIDWORD(ptHumanAI->tCommon.tAimPosition.vY);
  if ( vY_high != LODWORD(ptHumanAI->tCommon.tAimPosition.vZ) )
    return false;
  ptHumanQTask = ptHumanAI->tQTask.ptParent;
  if ( AISquad_IsTeamLeader(ptHumanQTask->ptParent, &ptHumanAI->tQTask) )
    return false;
  v3 = Human_ptQTaskList;
  LODWORD(ptHumanAI->tCommon.tAimPosition.vZ) = vY_high;
  nTask = v3->nTask;
  v5 = 0;
  if ( v3->nTask > 0 )
  {
    v6 = HumanAI_eQTaskType;
    for ( i = v3->ptQTask; ; ++i )
    {
      v8 = *i;
      if ( *i != ptHumanQTask )
      {
        FirstChildOfType = QTask_GetFirstChildOfType(*i, v6);
        if ( FirstChildOfType )
        {
          if ( !LOBYTE(v8[29].tQTaskRefList.ptHead)
            && FirstChildOfType[748].tQTaskRefList.ptTail == (struct QReference_s *)FirstChildOfType[748].ptParent )
          {
            tReal32x3 = *(double *)&ptHumanQTask[1].ptNext - *(double *)&v8[1].ptNext;
            tReal32x3_4 = *(double *)&ptHumanQTask[1].tQTaskChildren.ptHead - *(double *)&v8[1].tQTaskChildren.ptHead;
            v10 = *(double *)&ptHumanQTask[1].tQTaskChildren.ptTail - *(double *)&v8[1].tQTaskChildren.ptTail;
            if ( sqrt(tReal32x3 * tReal32x3 + tReal32x3_4 * tReal32x3_4 + v10 * v10) < 4096.0 )
              break;
          }
        }
      }
      if ( ++v5 >= nTask )
        return false;
    }
    LODWORD(ptHumanAI->tCommon.tAimPosition.vZ) = -1;
    HumanAI_FindAlternativeNode(ptHumanAI);
    if ( LODWORD(ptHumanAI->tCommon.tAimPosition.vZ) != -1 )
      return true;
    LODWORD(ptHumanAI->tCommon.tAimPosition.vZ) = HIDWORD(ptHumanAI->tCommon.tAimPosition.vY);
  }
  return false;
}

// source: j/0/humanai/humanai.c:11457  [size]
struct HumanAIActionStackItem_s *__cdecl HumanAI_GetCurrentActionItem(
        struct HumanAI_s *ptHumanAI)
{
  return *(_DWORD *)ptHumanAI->atActionStackItemList[0].pfRunCallback != 0
       ? (struct HumanAIActionStackItem_s *)ptHumanAI->atActionStackItemList[0].pfRunCallback
       : nullptr;
}

// source: j/0/humanai/humanai.c:11472  [anchor-callee]
struct QTask_s *__cdecl HumanAI_PlaySoundAtPosition(
        struct QTask_s *ptQTask,
        char *zSoundName,
        enum bool isQueueable)
{
  struct QTask_s *v4; // edi
  int v6; // eax

  v4 = nullptr;
  if ( ptQTask->ptParent[76].tQTaskChildren.ptHead )
    return nullptr;
  if ( *(_DWORD *)&ptQTask[110].eQTaskType )
  {
    if ( isQueueable )
      HumanAI_AddSoundQueueItem((struct HumanAI_s *)ptQTask, zSoundName);
  }
  else
  {
    v4 = SoundSys_NewSoundFn(Level_ptDynamicQTask, zSoundName);
    if ( v4 )
    {
      v6 = 511 * SoundSys_eSetPositionQTaskEvent;
      *(_DWORD *)&ptQTask[110].eQTaskType = 60;
      ((void (__cdecl *)(struct QTask_s *, struct QTask_s **))QTask_aatQTaskFinalEvent[0][v4->eQTaskType + v6].pfHandler)(
        v4,
        &ptQTask[1].ptParent);
      return v4;
    }
  }
  return v4;
}

// source: j/0/humanai/humanai.c:11518  [anchor-callee]
void __cdecl HumanAI_PlayRandomSoundAtPosition(struct QTask_s *ptQTask, int nSoundsToChooseFrom, char **azSoundNames)
{
  struct Game_s *v3; // eax
  unsigned int v4; // edx
  int v5; // edx
  unsigned int v6; // edx

  v3 = Game_ptGame;
  v4 = (Game_ptGame->tRunRandomState.anRandom[0] >> 7) ^ Game_ptGame->tRunRandomState.anRandom[2];
  Game_ptGame->tRunRandomState.anRandom[2] = v4;
  v5 = v4 ^ v3->tRunRandomState.anRandom[1];
  v3->tRunRandomState.anRandom[1] = v5;
  v6 = v5 + v3->tRunRandomState.anRandom[0];
  v3->tRunRandomState.anRandom[0] = v6;
  HumanAI_PlaySoundAtPosition(ptQTask, azSoundNames[v6 % nSoundsToChooseFrom], false);
}

// source: j/0/humanai/humanai.c:11537  [anchor-caller]
struct real64x3_t *__cdecl HumanAI_UpdateNodeIdFromPostition(
        struct QTask_s *ptQTask,
        struct real64x3_t *ptReal64x3)
{
  struct real64x3_t *result; // eax
  struct QTask_s **v3; // edi
  struct AIGraphNode_s *ptNode; // [esp+8h] [ebp-4h] BYREF

  result = (struct real64x3_t *)AIGraph_GetClosestNode(
                                  &ptNode,
                                  (struct AIGraph_t *)ptQTask[728].tQTaskChildren.ptHead,
                                  ptReal64x3,
                                  true);
  v3 = (struct QTask_s **)ptNode;
  if ( ptNode )
  {
    HumanAI_SetCurrentNode((struct HumanAI_s *)ptQTask, ptNode->tGraphNode.nID);
    result = (struct real64x3_t *)*v3;
    *(_DWORD *)&ptQTask[748].eQTaskType = *v3;
    ptQTask[748].ptParent = *v3;
  }
  return result;
}

// source: j/0/humanai/humanai.c:11568  [anchor-mhash]
void __cdecl HumanAI_ClearMovementData(struct QTask_s *ptQTask)
{
  AIGraphAStarSearch_Clear((struct AIGraphAStarSearchData_s *)&ptQTask[7].tQTaskChildren);
  ptQTask[748].ptParent = (struct QTask_s *)ptQTask[748].tQTaskRefList.ptTail;
  HumanAI_ClearMovementQueue((struct HumanAI_s *)ptQTask);
}

// source: j/0/humanai/humanai.c:11592  [anchor-callee]
enum bool __cdecl HumanAI_IsLessThanPercentageAmmoLeftInWeapon(
        struct HumanAI_s *ptHumanAI,
        float vPercentage)
{
  struct WeaponGetFireTypeAmmoContext_s tAmmoContext; // [esp+Ch] [ebp-14h] BYREF

  Weapon_GetFireTypeAmmoInfoFromWeaponTypeItem(
    (struct Weapon_s *)ptHumanAI->tQTask.ptParent[33].ptNext,
    (struct WeaponTypeItem_s *)ptHumanAI->tQTask.ptParent[33].ptNext[1].ptPrev,
    0,
    &tAmmoContext);
  return tAmmoContext.nAmmoInWeapon < (int)(__int64)((double)tAmmoContext.nRoundsPerClip * vPercentage * 0.009999999776482582);
}

// source: j/0/humanai/humanai.c:11614  [anchor-callee]
enum bool __cdecl HumanAI_IsRPGSoldier(struct HumanAI_s *ptHumanAI)
{
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptTail; // eax
  enum bool result; // eax

  ptPrev = ptHumanAI->tQTask.ptParent[33].ptNext[1].ptPrev;
  result = false;
  if ( ptPrev )
  {
    ptTail = ptPrev->tQTaskChildren.ptTail;
    if ( ptTail )
    {
      if ( ptTail[32].tQTaskRefList.ptHead == (struct QReference_s *)Gun_eQTaskType
        && *(_DWORD *)&ptTail[32].ptParent->tQTaskChildren.ptHead[2].eQTaskType == Missile_eQTaskType )
      {
        return true;
      }
    }
  }
  return result;
}

// source: j/0/humanai/humanai.c:11660  [anchor-callee]
enum bool __cdecl HumanAI_IsShotGunSholdier(struct HumanAI_s *ptHumanAI)
{
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptTail; // eax
  enum bool result; // eax

  ptPrev = ptHumanAI->tQTask.ptParent[33].ptNext[1].ptPrev;
  result = false;
  if ( ptPrev )
  {
    ptTail = ptPrev->tQTaskChildren.ptTail;
    if ( ptTail )
    {
      if ( ptTail[16].tQTaskRefList.ptTail == (struct QReference_s *)2 )
        return true;
    }
  }
  return result;
}

// source: j/0/humanai/humanai.c:11687  [anchor-mhash]
int __cdecl HumanAI_GetDelayFromDetectionTimeDistanceFactor(
        struct HumanAI_s *ptHumanAI,
        struct real64x3_t *ptPosition)
{
  double *ptParent; // eax
  double v3; // st3
  float tReal32x3; // [esp+0h] [ebp-Ch]
  float tReal32x3_4; // [esp+4h] [ebp-8h]

  ptParent = (double *)ptHumanAI->tQTask.ptParent;
  tReal32x3 = ptParent[5] - ptPosition->vX;
  tReal32x3_4 = ptParent[6] - ptPosition->vY;
  v3 = ptParent[7] - ptPosition->vZ;
  return (__int64)(sqrt(tReal32x3 * tReal32x3 + tReal32x3_4 * tReal32x3_4 + v3 * v3)
                 * 2.441406286379788e-05
                 * ptHumanAI->tTweakParameters.vMinDelayBetweenFiring
                 * 30.0);
}

// source: j/0/humanai/humanai.c:11714  [anchor-hash]
int __cdecl HumanAI_GetCurrentActionPriority(struct HumanAI_s *ptHumanAI)
{
  void (__cdecl *pfRunCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // eax

  pfRunCallback = ptHumanAI->atActionStackItemList[0].pfRunCallback;
  if ( *(_DWORD *)pfRunCallback && pfRunCallback )
    return *((_DWORD *)pfRunCallback + 3);
  else
    return -1;
}

// source: j/0/humanai/humanai.c:11739  [anchor-caller]
void __cdecl HumanAI_RefreshFormationPosition(struct HumanAI_s *ptHumanAI, float vFormationDistance)
{
  #pragma pack(push, 1)
  union
  {
    struct { float tReal32x3; };
    struct { char igi2_o1[4]; float tReal32x3_4; };
    struct { char igi2_o2[4]; float tReal32x3_4a; };
    struct { char igi2_o3[8]; float tReal32x3_8; };
    struct { char igi2_o4[8]; float tReal32x3_8a; };
    struct { char igi2_o5[8]; float tReal32x3_8b; };
    struct { char igi2_o6[12]; struct real64x3_t tReal64x3; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  void (__cdecl *pfRunCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // eax
  int v3; // ebx
  int v4; // ecx
  int v5; // ebx
  int v6; // edi
  int v7; // ecx
  long double v8; // st4
  long double v9; // st7
  int v10; // eax
  struct Graph_s *v11; // esi
  double v12; // rt0
  struct AIGraphNode_s *Node; // eax

  pfRunCallback = ptHumanAI->atActionStackItemList[0].pfRunCallback;
  if ( *(_DWORD *)pfRunCallback )
  {
    if ( pfRunCallback )
    {
      if ( *((void (__cdecl **)(struct HumanAI_s *, struct HumanAIActionStackItem_s *))pfRunCallback + 6) == HumanAIContent_MoveInFormationSquadOrderInitCB )
      {
        v3 = *((_DWORD *)pfRunCallback + 12);
        v4 = *(_DWORD *)(v3 + 32);
        v5 = v3 + 8;
        v6 = *(_DWORD *)(v4 + 8);
        if ( v6 )
        {
          v7 = *(_DWORD *)(v6 + 32);
          igi2_frame.tReal32x3_4 = *(float *)(v5 + 4);
          igi2_frame.tReal32x3_8 = *(float *)(v5 + 8);
          v8 = sqrt(*(float *)v5 * *(float *)v5 + igi2_frame.tReal32x3_4 * igi2_frame.tReal32x3_4 + igi2_frame.tReal32x3_8 * igi2_frame.tReal32x3_8);
          if ( v8 != 0.0 )
          {
            v9 = vFormationDistance / v8;
            igi2_frame.tReal32x3 = *(float *)v5 * v9;
            *(float *)v5 = igi2_frame.tReal32x3;
            igi2_frame.tReal32x3_4a = igi2_frame.tReal32x3_4 * v9;
            *(float *)(v5 + 4) = igi2_frame.tReal32x3_4a;
            igi2_frame.tReal32x3_8a = v9 * igi2_frame.tReal32x3_8;
            *(float *)(v5 + 8) = igi2_frame.tReal32x3_8a;
            v10 = *(_DWORD *)(v6 + 29948);
            v11 = *(struct Graph_s **)(v6 + 29128);
            igi2_frame.tReal32x3_8b = *(float *)(v7 + 156) * *(float *)(v5 + 8)
                         + *(float *)(v7 + 152) * *(float *)(v5 + 4)
                         + *(float *)(v7 + 148) * *(float *)v5;
            v12 = *(float *)(v7 + 144) * *(float *)(v5 + 8)
                + *(float *)(v7 + 140) * *(float *)(v5 + 4)
                + *(float *)(v7 + 136) * *(float *)v5;
            igi2_frame.tReal64x3.vX = *(float *)(v7 + 132) * *(float *)(v5 + 8)
                         + *(float *)(v7 + 128) * *(float *)(v5 + 4)
                         + *(float *)(v7 + 124) * *(float *)v5
                         + *(double *)(v7 + 40);
            igi2_frame.tReal64x3.vY = v12 + *(double *)(v7 + 48);
            igi2_frame.tReal64x3.vZ = igi2_frame.tReal32x3_8b + *(double *)(v7 + 56);
            Node = (struct AIGraphNode_s *)Graph_GetNode(v11, v10);
            *(_DWORD *)(v5 + 28) = AIGraph_GetClosestNodeFromStartingNode(
                                     *(struct AIGraph_t **)(v6 + 29128),
                                     Node,
                                     &igi2_frame.tReal64x3,
                                     20)->tGraphNode.nID;
          }
        }
      }
    }
  }
}

// source: j/0/humanai/humanai.c:11805  [anchor-mhash]
void __cdecl HumanAI_NotifyTaskHasBeenActivated(struct HumanAI_s *ptActivatingHumanAI, int iTaskID)
{
  int v2; // ebx
  struct QTask_s **ptQTask; // ebp
  struct QTask_s *v4; // eax
  struct HumanAI_s *ptParent; // eax
  struct HumanAIActionStackItem_s *pfRunCallback; // esi
  struct QTaskList_s *ptHumanQTaskList; // [esp+0h] [ebp-4h]

  v2 = 0;
  ptHumanQTaskList = Human_ptQTaskList;
  if ( Human_ptQTaskList->nTask > 0 )
  {
    ptQTask = Human_ptQTaskList->ptQTask;
    do
    {
      v4 = *ptQTask;
      if ( *ptQTask )
      {
        if ( v4->eQTaskType == HumanSoldier_eQTaskType )
        {
          ptParent = (struct HumanAI_s *)v4[48].ptParent;
          pfRunCallback = (struct HumanAIActionStackItem_s *)ptParent->atActionStackItemList[0].pfRunCallback;
          if ( pfRunCallback->tNode.ptNext )
          {
            if ( pfRunCallback
              && pfRunCallback->pfInitCallback == HumanAIContent_ActivateInitCB
              && ptParent != ptActivatingHumanAI
              && pfRunCallback->ptContext->uContext.tWaitContext.nTimer == iTaskID )
            {
              HumanAI_PopActionStackItem(ptParent, pfRunCallback);
            }
          }
        }
      }
      ++v2;
      ++ptQTask;
    }
    while ( v2 < ptHumanQTaskList->nTask );
  }
}

// source: j/0/humanai/humanai.c:11852  [anchor-mhash]
struct HumanAI_s *__cdecl HumanAI_GetActivatingAI(int iActivatingID)
{
  int v1; // edx
  struct QTask_s **i; // esi
  struct QTask_s *v3; // eax
  struct HumanAI_s *result; // eax
  void (__cdecl *pfRunCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // ecx

  v1 = 0;
  if ( Human_ptQTaskList->nTask <= 0 )
    return nullptr;
  for ( i = Human_ptQTaskList->ptQTask; ; ++i )
  {
    v3 = *i;
    if ( *i )
    {
      if ( v3->eQTaskType == HumanSoldier_eQTaskType )
      {
        result = (struct HumanAI_s *)v3[48].ptParent;
        pfRunCallback = result->atActionStackItemList[0].pfRunCallback;
        if ( *(_DWORD *)pfRunCallback )
        {
          if ( pfRunCallback
            && *((void (__cdecl **)(struct HumanAI_s *, struct HumanAIActionStackItem_s *))pfRunCallback + 6) == HumanAIContent_ActivateInitCB
            && *(_DWORD *)(*((_DWORD *)pfRunCallback + 12) + 8) == iActivatingID )
          {
            break;
          }
        }
      }
    }
    if ( ++v1 >= Human_ptQTaskList->nTask )
      return nullptr;
  }
  return result;
}
