/* j/0/objects/elevatorfloorindicator.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/objects/elevatorfloorindicator.c:91  [anchor-mhash]
void __cdecl ElevatorFloorIndicator_SetRelativeOrientation(
        struct ElevatorFloorIndicator_s *ptElevatorFloorIndicator)
{
  struct QTask_s *FirstParentDerivedOfType; // eax
  double v2; // st7
  struct QTask_s *ptTail; // edx
  struct QReference_s *v4; // ecx
  struct QTask_s *ptHead; // edx
  struct QReference_s *v6; // ecx
  struct QTask_s *ptParent; // edx
  struct QTask_s *ptMiddle; // ecx
  struct QReference_s *v9; // edx
  int v10; // ecx
  struct QTask_s *ptNext; // edx
  double v12; // st7
  double v13; // st6
  _BYTE Real64x3_RotateInverse_tTemp[40]; // [esp+8h] [ebp-2Ch] BYREF

  FirstParentDerivedOfType = QTask_GetFirstParentDerivedOfType(
                               &ptElevatorFloorIndicator->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask,
                               RigidDynCubeObj_eQTaskType);
  if ( FirstParentDerivedOfType )
  {
    ptElevatorFloorIndicator->tRelativePos.vX = ptElevatorFloorIndicator->tOriginalPos.vX
                                              - *(double *)&FirstParentDerivedOfType[1].ptNext;
    ptElevatorFloorIndicator->tRelativePos.vY = ptElevatorFloorIndicator->tOriginalPos.vY
                                              - *(double *)&FirstParentDerivedOfType[1].tQTaskChildren.ptHead;
    v2 = ptElevatorFloorIndicator->tOriginalPos.vZ - *(double *)&FirstParentDerivedOfType[1].tQTaskChildren.ptTail;
    ptElevatorFloorIndicator->tRelativePos.vZ = v2;
    *(double *)Real64x3_RotateInverse_tTemp = *(float *)&FirstParentDerivedOfType[3].tQTaskRefList.ptTail * v2
                                            + *(float *)&FirstParentDerivedOfType[3].ptPrev
                                            * ptElevatorFloorIndicator->tRelativePos.vX
                                            + *(float *)&FirstParentDerivedOfType[3].tQTaskChildren.ptTail
                                            * ptElevatorFloorIndicator->tRelativePos.vY;
    *(double *)&Real64x3_RotateInverse_tTemp[8] = *(float *)&FirstParentDerivedOfType[3].ptParent * v2
                                                + *(float *)&FirstParentDerivedOfType[3].tQTaskChildren.ptHead
                                                * ptElevatorFloorIndicator->tRelativePos.vX
                                                + *(float *)&FirstParentDerivedOfType[3].tQTaskRefList.ptHead
                                                * ptElevatorFloorIndicator->tRelativePos.vY;
    *(double *)&Real64x3_RotateInverse_tTemp[16] = *(float *)&FirstParentDerivedOfType[3].eQTaskType * v2
                                                 + *(float *)&FirstParentDerivedOfType[3].tQTaskChildren.ptMiddle
                                                 * ptElevatorFloorIndicator->tRelativePos.vX
                                                 + *(float *)&FirstParentDerivedOfType[3].tQTaskRefList.ptMiddle
                                                 * ptElevatorFloorIndicator->tRelativePos.vY;
    qmemcpy(
      &ptElevatorFloorIndicator->tRelativePos,
      Real64x3_RotateInverse_tTemp,
      sizeof(ptElevatorFloorIndicator->tRelativePos));
    ptTail = FirstParentDerivedOfType[3].tQTaskChildren.ptTail;
    *(_DWORD *)Real64x3_RotateInverse_tTemp = FirstParentDerivedOfType[3].ptPrev;
    v4 = FirstParentDerivedOfType[3].tQTaskRefList.ptTail;
    *(_DWORD *)&Real64x3_RotateInverse_tTemp[4] = ptTail;
    ptHead = FirstParentDerivedOfType[3].tQTaskChildren.ptHead;
    *(_DWORD *)&Real64x3_RotateInverse_tTemp[8] = v4;
    v6 = FirstParentDerivedOfType[3].tQTaskRefList.ptHead;
    *(_DWORD *)&Real64x3_RotateInverse_tTemp[12] = ptHead;
    ptParent = FirstParentDerivedOfType[3].ptParent;
    *(_DWORD *)&Real64x3_RotateInverse_tTemp[16] = v6;
    ptMiddle = FirstParentDerivedOfType[3].tQTaskChildren.ptMiddle;
    *(_DWORD *)&Real64x3_RotateInverse_tTemp[20] = ptParent;
    v9 = FirstParentDerivedOfType[3].tQTaskRefList.ptMiddle;
    *(_DWORD *)&Real64x3_RotateInverse_tTemp[24] = ptMiddle;
    v10 = *(_DWORD *)&FirstParentDerivedOfType[3].eQTaskType;
    *(_DWORD *)&Real64x3_RotateInverse_tTemp[28] = v9;
    ptNext = FirstParentDerivedOfType[4].ptNext;
    *(_DWORD *)&Real64x3_RotateInverse_tTemp[32] = v10;
    *(_DWORD *)&Real64x3_RotateInverse_tTemp[36] = ptNext;
    qmemcpy(
      &ptElevatorFloorIndicator->tRelativeOrientation,
      Real64x3_RotateInverse_tTemp,
      sizeof(ptElevatorFloorIndicator->tRelativeOrientation));
    *(float *)Real64x3_RotateInverse_tTemp = ptElevatorFloorIndicator->tRelativeOrientation.tY.vX
                                           * ptElevatorFloorIndicator->tOriginalOrientation.tX.vY
                                           + ptElevatorFloorIndicator->tOriginalOrientation.tX.vX
                                           * ptElevatorFloorIndicator->tRelativeOrientation.tX.vX
                                           + ptElevatorFloorIndicator->tOriginalOrientation.tX.vZ
                                           * ptElevatorFloorIndicator->tRelativeOrientation.tZ.vX;
    v12 = ptElevatorFloorIndicator->tRelativeOrientation.tY.vY * ptElevatorFloorIndicator->tOriginalOrientation.tX.vY
        + ptElevatorFloorIndicator->tOriginalOrientation.tX.vX * ptElevatorFloorIndicator->tRelativeOrientation.tX.vY;
    v13 = ptElevatorFloorIndicator->tRelativeOrientation.tZ.vY * ptElevatorFloorIndicator->tOriginalOrientation.tX.vZ;
    *(_DWORD *)&Real64x3_RotateInverse_tTemp[36] = ptElevatorFloorIndicator->tRelativeOrientation.nOps
                                                 + ptElevatorFloorIndicator->tOriginalOrientation.nOps
                                                 + 1;
    *(float *)&Real64x3_RotateInverse_tTemp[4] = v12 + v13;
    *(float *)&Real64x3_RotateInverse_tTemp[8] = ptElevatorFloorIndicator->tRelativeOrientation.tY.vZ
                                               * ptElevatorFloorIndicator->tOriginalOrientation.tX.vY
                                               + ptElevatorFloorIndicator->tRelativeOrientation.tX.vZ
                                               * ptElevatorFloorIndicator->tOriginalOrientation.tX.vX
                                               + ptElevatorFloorIndicator->tRelativeOrientation.tZ.vZ
                                               * ptElevatorFloorIndicator->tOriginalOrientation.tX.vZ;
    *(float *)&Real64x3_RotateInverse_tTemp[12] = ptElevatorFloorIndicator->tRelativeOrientation.tX.vX
                                                * ptElevatorFloorIndicator->tOriginalOrientation.tY.vX
                                                + ptElevatorFloorIndicator->tOriginalOrientation.tY.vZ
                                                * ptElevatorFloorIndicator->tRelativeOrientation.tZ.vX
                                                + ptElevatorFloorIndicator->tRelativeOrientation.tY.vX
                                                * ptElevatorFloorIndicator->tOriginalOrientation.tY.vY;
    *(float *)&Real64x3_RotateInverse_tTemp[16] = ptElevatorFloorIndicator->tOriginalOrientation.tY.vX
                                                * ptElevatorFloorIndicator->tRelativeOrientation.tX.vY
                                                + ptElevatorFloorIndicator->tRelativeOrientation.tZ.vY
                                                * ptElevatorFloorIndicator->tOriginalOrientation.tY.vZ
                                                + ptElevatorFloorIndicator->tRelativeOrientation.tY.vY
                                                * ptElevatorFloorIndicator->tOriginalOrientation.tY.vY;
    *(float *)&Real64x3_RotateInverse_tTemp[20] = ptElevatorFloorIndicator->tRelativeOrientation.tX.vZ
                                                * ptElevatorFloorIndicator->tOriginalOrientation.tY.vX
                                                + ptElevatorFloorIndicator->tRelativeOrientation.tZ.vZ
                                                * ptElevatorFloorIndicator->tOriginalOrientation.tY.vZ
                                                + ptElevatorFloorIndicator->tRelativeOrientation.tY.vZ
                                                * ptElevatorFloorIndicator->tOriginalOrientation.tY.vY;
    *(float *)&Real64x3_RotateInverse_tTemp[24] = ptElevatorFloorIndicator->tRelativeOrientation.tY.vX
                                                * ptElevatorFloorIndicator->tOriginalOrientation.tZ.vY
                                                + ptElevatorFloorIndicator->tRelativeOrientation.tZ.vX
                                                * ptElevatorFloorIndicator->tOriginalOrientation.tZ.vZ
                                                + ptElevatorFloorIndicator->tRelativeOrientation.tX.vX
                                                * ptElevatorFloorIndicator->tOriginalOrientation.tZ.vX;
    *(float *)&Real64x3_RotateInverse_tTemp[28] = ptElevatorFloorIndicator->tRelativeOrientation.tZ.vY
                                                * ptElevatorFloorIndicator->tOriginalOrientation.tZ.vZ
                                                + ptElevatorFloorIndicator->tRelativeOrientation.tY.vY
                                                * ptElevatorFloorIndicator->tOriginalOrientation.tZ.vY
                                                + ptElevatorFloorIndicator->tOriginalOrientation.tZ.vX
                                                * ptElevatorFloorIndicator->tRelativeOrientation.tX.vY;
    *(float *)&Real64x3_RotateInverse_tTemp[32] = ptElevatorFloorIndicator->tRelativeOrientation.tZ.vZ
                                                * ptElevatorFloorIndicator->tOriginalOrientation.tZ.vZ
                                                + ptElevatorFloorIndicator->tRelativeOrientation.tY.vZ
                                                * ptElevatorFloorIndicator->tOriginalOrientation.tZ.vY
                                                + ptElevatorFloorIndicator->tRelativeOrientation.tX.vZ
                                                * ptElevatorFloorIndicator->tOriginalOrientation.tZ.vX;
    qmemcpy(
      &ptElevatorFloorIndicator->tRelativeOrientation,
      Real64x3_RotateInverse_tTemp,
      sizeof(ptElevatorFloorIndicator->tRelativeOrientation));
  }
  else
  {
    ptElevatorFloorIndicator->tRelativePos.vX = 0.0;
    ptElevatorFloorIndicator->tRelativePos.vY = 0.0;
    ptElevatorFloorIndicator->tRelativePos.vZ = 0.0;
    ptElevatorFloorIndicator->tRelativeOrientation.tX.vX = 1.0;
    ptElevatorFloorIndicator->tRelativeOrientation.tX.vY = 0.0;
    ptElevatorFloorIndicator->tRelativeOrientation.tX.vZ = 0.0;
    ptElevatorFloorIndicator->tRelativeOrientation.tY.vX = 0.0;
    ptElevatorFloorIndicator->tRelativeOrientation.tY.vY = 1.0;
    ptElevatorFloorIndicator->tRelativeOrientation.tY.vZ = 0.0;
    ptElevatorFloorIndicator->tRelativeOrientation.tZ.vX = 0.0;
    ptElevatorFloorIndicator->tRelativeOrientation.tZ.vY = 0.0;
    ptElevatorFloorIndicator->tRelativeOrientation.tZ.vZ = 1.0;
    ptElevatorFloorIndicator->tRelativeOrientation.nOps = 0;
  }
}

// source: j/0/objects/elevatorfloorindicator.c:142  [anchor-mhash]
void __cdecl ElevatorFloorIndicator_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[24]; struct real64x3_t tNull; };
    char igi2_extent[52];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v2; // st7
  double v3; // st7
  int *v4; // eax
  int v5; // eax
  double v6; // st6

  memset(&igi2_frame.tNull, 0, sizeof(igi2_frame.tNull));
  ModelObj_Init((struct ModelObj_s *)ptQTask, World_ptActiveWorld, nullptr);
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
  igi2_frame.ptDynCubeObj = v3 * v6;
  World_RegisterDynCubeObjFirstTimeRadius(
    World_ptActiveWorld,
    (struct DynCubeObj_s *)ptQTask,
    &igi2_frame.tNull,
    igi2_frame.ptDynCubeObj,
    WORLD_DYNCUBETREE_CATEGORY_STATIONARY);
  ptQTask[3].tQTaskChildren.ptHead = nullptr;
  ptQTask[3].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[3].tQTaskChildren.ptTail = nullptr;
  ptQTask[3].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[3].tQTaskRefList.ptTail = nullptr;
  ptQTask[3].ptParent = nullptr;
  ptQTask[4].ptNext = nullptr;
  LOBYTE(ptQTask[11].tQTaskChildren.ptHead) = 0;
  LOBYTE(ptQTask[11].tQTaskRefList.ptMiddle) = 0;
  LOBYTE(ptQTask[12].ptNext) = 0;
  LOBYTE(ptQTask[12].tQTaskChildren.ptTail) = 0;
  ptQTask[3].ptPrev = (struct QTask_s *)1065353216;
  ptQTask[3].tQTaskRefList.ptHead = (struct QReference_s *)1065353216;
  *(_DWORD *)&ptQTask[3].eQTaskType = 1065353216;
  ptQTask[12].tQTaskRefList.ptHead = nullptr;
  ptQTask[12].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[12].tQTaskRefList.ptTail = nullptr;
  ptQTask[14].tQTaskChildren.ptTail = nullptr;
  ptQTask[14].tQTaskRefList.ptHead = nullptr;
  ptQTask[14].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[14].tQTaskRefList.ptTail = nullptr;
  ptQTask[16].tQTaskChildren.ptTail = nullptr;
}

// source: j/0/objects/elevatorfloorindicator.c:189  [anchor-mhash]
void __cdecl ElevatorFloorIndicator_RunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // ecx
  int v2; // edx
  struct QTask_s *v3; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v5; // edx
  struct QTask_s *v6; // edi
  struct QTask_s *v7; // ebx
  char *p_tQTaskChildren; // eax
  struct LODVirModel_s *LODVirModelExistsFn; // eax
  struct QTask_s *v10; // eax

  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v2 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v3 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v3 = nullptr;
      QTask_atProtectedQTaskStack[v2].ptQTask = v3;
      pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][ptHead->eQTaskType].pfHandler;
      v5 = v2 + 1;
      QTask_nProtectedQTaskStackOffset = v5;
      if ( pfHandler )
      {
        pfHandler(ptHead);
        v5 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v5];
      v2 = v5 - 1;
      QTask_nProtectedQTaskStackOffset = v2;
    }
    while ( ptHead );
  }
  if ( ptQTask[12].tQTaskRefList.ptHead
    && ptQTask[12].tQTaskRefList.ptMiddle->ptNext
    && ptQTask[12].tQTaskRefList.ptTail )
  {
    v6 = (struct QTask_s *)(__int64)Level_RunLevelExpression(
                                      (struct LevelExpression_s *)&ptQTask[12].tQTaskRefList,
                                      ptQTask);
  }
  else
  {
    v6 = ptQTask;
  }
  if ( ptQTask[14].tQTaskRefList.ptHead
    && ptQTask[14].tQTaskRefList.ptMiddle->ptNext
    && ptQTask[14].tQTaskRefList.ptTail )
  {
    v7 = (struct QTask_s *)(__int64)Level_RunLevelExpression(
                                      (struct LevelExpression_s *)&ptQTask[14].tQTaskRefList,
                                      ptQTask);
  }
  else
  {
    v7 = ptQTask;
  }
  p_tQTaskChildren = (char *)&ptQTask[11].tQTaskChildren;
  if ( !v6 )
    p_tQTaskChildren = (char *)&ptQTask[11].tQTaskRefList.ptMiddle;
  LODVirModelExistsFn = MTP_GetLODVirModelExistsFn(p_tQTaskChildren);
  if ( LODVirModelExistsFn != *(struct LODVirModel_s **)&ptQTask[2].eQTaskType )
  {
    ModelObj_SetLODVirModel((struct ModelObj_s *)ptQTask, LODVirModelExistsFn, false);
    ptQTask[7].tQTaskRefList.ptHead = nullptr;
    ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
    ptQTask[7].tQTaskRefList.ptTail = nullptr;
    ptQTask[7].ptParent = nullptr;
    *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  }
  if ( v7 )
  {
    v10 = SoundSys_NewSoundFn(Level_ptDynamicQTask, (char *)&ptQTask[12]);
    if ( v10 )
      ((void (__cdecl *)(struct QTask_s *, struct QTask_s *))QTask_aatQTaskFinalEvent[SoundSys_eSetPositionQTaskEvent][v10->eQTaskType].pfHandler)(
        v10,
        &ptQTask[1]);
  }
}

// source: j/0/objects/elevatorfloorindicator.c:244  [anchor-mhash]
void __cdecl ElevatorFloorIndicator_DeleteHandler(struct QTask_s *ptQTask)
{
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[12].tQTaskRefList);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[14].tQTaskRefList);
  World_RemoveDynCubeObj((struct World_s *)ptQTask[2].ptParent, (struct DynCubeObj_s *)ptQTask);
}

// source: j/0/objects/elevatorfloorindicator.c:268  [size]
void __cdecl ElevatorFloorIndicator_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = ElevatorFloorIndicator_ptParameterList;
}

// source: j/0/objects/elevatorfloorindicator.c:284  [anchor-mhash]
void __cdecl ElevatorFloorIndicator_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct LODVirModel_s *LODVirModelExistsFn; // eax
  double v3; // st7
  double v4; // st7
  int *v5; // eax
  int v6; // eax
  double v7; // st6
  float ptDynCubeObj; // [esp+0h] [ebp-10h]

  LODVirModelExistsFn = MTP_GetLODVirModelExistsFn((char *)&ptQTask[11].tQTaskRefList.ptMiddle);
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
    (struct World_s *)ptQTask[2].ptParent,
    (struct DynCubeObj_s *)ptQTask,
    (struct real64x3_t *)&ptQTask[8],
    ptDynCubeObj);
  qmemcpy(&ptQTask[3].ptPrev, &ptQTask[8].tQTaskRefList.ptMiddle, sizeof(struct QTask_s));
  ElevatorFloorIndicator_SetRelativeOrientation((struct ElevatorFloorIndicator_s *)ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[12].tQTaskRefList, ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[14].tQTaskRefList, ptQTask);
}

// source: j/0/objects/elevatorfloorindicator.c:325  [size]
void __cdecl ElevatorFloorIndicator_WeaponHitHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: j/0/objects/elevatorfloorindicator.c:386  [anchor-mhash]
void __cdecl ElevatorFloorIndicator_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // edx

  v0 = QTask_NewQTaskType("ElevatorFloorIndicator", 664, RigidDynCubeObj_eQTaskType, 0, 0);
  ElevatorFloorIndicator_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, ElevatorFloorIndicator_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, ElevatorFloorIndicator_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, ElevatorFloorIndicator_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))ElevatorFloorIndicator_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eUpdateInternalDataQTaskEvent,
    ElevatorFloorIndicator_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    GameFunctions_eWeaponHitQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))ElevatorFloorIndicator_WeaponHitHandler);
  QTask_LinkQTaskEventHandlerFn(v0, BulletHole_eCreateBulletHoleTaskEvent, nullptr);
  v1 = (struct ParameterList_s *)Mem_AllocFn(152, 4);
  v1->nParameters = 0;
  v2 = Level_eParameterTypeObjectPos;
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  v1->nMaxParameters = 7;
  ElevatorFloorIndicator_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0x140u, v2, "Position", 7u, nullptr);
  ParameterList_AddParameter(
    ElevatorFloorIndicator_ptParameterList,
    0x158u,
    Level_eParameterTypeReal32x9,
    "Orientation",
    7u,
    nullptr);
  ParameterList_AddParameter(
    ElevatorFloorIndicator_ptParameterList,
    0x1C0u,
    Level_eParameterTypeString16,
    "On model",
    7u,
    nullptr);
  ParameterList_AddParameter(
    ElevatorFloorIndicator_ptParameterList,
    0x1D0u,
    Level_eParameterTypeString16,
    "Off model",
    7u,
    nullptr);
  ParameterList_AddParameter(
    ElevatorFloorIndicator_ptParameterList,
    0x1E0u,
    Level_eParameterTypeString16,
    "Sound",
    7u,
    nullptr);
  ParameterList_AddParameter(
    ElevatorFloorIndicator_ptParameterList,
    0x1F4u,
    Level_eParameterTypeVarString,
    "On",
    7u,
    nullptr);
  ParameterList_AddParameter(
    ElevatorFloorIndicator_ptParameterList,
    0x244u,
    Level_eParameterTypeVarString,
    "SoundOnExpression",
    7u,
    nullptr);
}

// source: j/0/objects/elevatorfloorindicator.c:438  [size]
void __cdecl ElevatorFloorIndicator_Close()
{
  int v0; // esi

  if ( ElevatorFloorIndicator_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&ElevatorFloorIndicator_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(ElevatorFloorIndicator_eQTaskType);
}
