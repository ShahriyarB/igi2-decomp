/* j/0/objects/elevator.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/objects/elevator.c:160  [anchor-hash]
struct Elevator_s *__cdecl Elevator_UpdateChildPosition(struct Elevator_s *ptElevator)
{
  struct QTask_s *ptHead; // ecx
  int v2; // edx
  struct QTask_s *v3; // eax
  int v4; // esi
  int v5; // edx

  ptHead = ptElevator->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v2 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v3 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v3 = nullptr;
      v4 = Attach_eUpdateAttachmentEvent;
      QTask_atProtectedQTaskStack[v2].ptQTask = v3;
      ptElevator = (struct Elevator_s *)QTask_aatQTaskFinalEvent[v4][ptHead->eQTaskType].pfHandler;
      v5 = v2 + 1;
      QTask_nProtectedQTaskStackOffset = v5;
      if ( ptElevator )
      {
        ptElevator = (struct Elevator_s *)((int (__cdecl *)(struct QTask_s *))ptElevator)(ptHead);
        v5 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v5];
      v2 = v5 - 1;
      QTask_nProtectedQTaskStackOffset = v2;
    }
    while ( ptHead );
  }
  return ptElevator;
}

// source: j/0/objects/elevator.c:176  [anchor-mhash]
void __cdecl Elevator_UpdatePosition(struct Elevator_s *ptElevator)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[23]; char isValid; };
    struct { char igi2_o2[24]; float vPos; };
    struct { char igi2_o3[28]; _BYTE tPos1[40]; };
    struct { char igi2_o4[68]; struct real32x9_t tPos2; };
    char igi2_extent[112];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int nSplineObjQTaskID; // esi
  double TotalLength; // st7
  int NumberOfWaypoint; // eax
  double v4; // st7
  struct real64x3_t *p_tPos; // ebp
  double v6; // st7
  double vZ; // st7
  double vY; // st7
  struct LODVirModel_s *ptLODVirModel; // eax
  struct VirModel_s *v10; // eax
  double vRadius; // st6

  nSplineObjQTaskID = ptElevator->nSplineObjQTaskID;
  igi2_frame.isValid = 1;
  if ( nSplineObjQTaskID != -1 )
  {
    TotalLength = SplineObj_GetTotalLength(nSplineObjQTaskID);
    igi2_frame.vPos = ptElevator->vPos;
    if ( igi2_frame.vPos >= TotalLength )
    {
      igi2_frame.vPos = TotalLength - 0.10000000149011612;
      ptElevator->vPos = TotalLength;
    }
    if ( igi2_frame.vPos < 0.0 )
    {
      igi2_frame.vPos = 0.0;
      ptElevator->vPos = 0.0;
    }
    if ( ptElevator->isLinear )
    {
      SplineObj_GetWaypointPosition((struct real64x3_t *)igi2_frame.tPos1, nSplineObjQTaskID, 0);
      NumberOfWaypoint = SplineObj_GetNumberOfWaypoint(nSplineObjQTaskID);
      SplineObj_GetWaypointPosition((struct real64x3_t *)&igi2_frame.tPos2, nSplineObjQTaskID, NumberOfWaypoint - 1);
      v4 = ptElevator->vPos / TotalLength;
      p_tPos = &ptElevator->tPos;
      ptElevator->tPos.vX = (*(double *)&igi2_frame.tPos2.tX.vX - *(double *)igi2_frame.tPos1) * v4 + *(double *)igi2_frame.tPos1;
      ptElevator->tPos.vY = (*(double *)&igi2_frame.tPos2.tX.vZ - *(double *)&igi2_frame.tPos1[8]) * v4 + *(double *)&igi2_frame.tPos1[8];
      ptElevator->tPos.vZ = v4 * (*(double *)&igi2_frame.tPos2.tY.vY - *(double *)&igi2_frame.tPos1[16]) + *(double *)&igi2_frame.tPos1[16];
    }
    else
    {
      p_tPos = &ptElevator->tPos;
      memset(igi2_frame.tPos1, 0, 12);
      SplineObj_GetPosAndMatrix(
        nSplineObjQTaskID,
        &igi2_frame.tPos2,
        &ptElevator->tPos,
        &igi2_frame.isValid,
        igi2_frame.vPos,
        0,
        nullptr,
        (struct real32x3_t *)igi2_frame.tPos1);
      if ( !igi2_frame.isValid )
        return;
      if ( !ptElevator->isForceOrientation )
      {
        *(float *)igi2_frame.tPos1 = igi2_frame.tPos2.tX.vX * ptElevator->tOrientation.tX.vX
                        + igi2_frame.tPos2.tZ.vX * ptElevator->tOrientation.tX.vZ
                        + igi2_frame.tPos2.tY.vX * ptElevator->tOrientation.tX.vY;
        *(float *)&igi2_frame.tPos1[4] = igi2_frame.tPos2.tX.vY * ptElevator->tOrientation.tX.vX
                            + igi2_frame.tPos2.tZ.vY * ptElevator->tOrientation.tX.vZ
                            + igi2_frame.tPos2.tY.vY * ptElevator->tOrientation.tX.vY;
        *(float *)&igi2_frame.tPos1[8] = igi2_frame.tPos2.tX.vZ * ptElevator->tOrientation.tX.vX
                            + igi2_frame.tPos2.tZ.vZ * ptElevator->tOrientation.tX.vZ
                            + igi2_frame.tPos2.tY.vZ * ptElevator->tOrientation.tX.vY;
        *(float *)&igi2_frame.tPos1[12] = igi2_frame.tPos2.tX.vX * ptElevator->tOrientation.tY.vX
                             + igi2_frame.tPos2.tZ.vX * ptElevator->tOrientation.tY.vZ
                             + igi2_frame.tPos2.tY.vX * ptElevator->tOrientation.tY.vY;
        *(float *)&igi2_frame.tPos1[16] = igi2_frame.tPos2.tX.vY * ptElevator->tOrientation.tY.vX
                             + igi2_frame.tPos2.tZ.vY * ptElevator->tOrientation.tY.vZ
                             + igi2_frame.tPos2.tY.vY * ptElevator->tOrientation.tY.vY;
        *(float *)&igi2_frame.tPos1[20] = igi2_frame.tPos2.tX.vZ * ptElevator->tOrientation.tY.vX
                             + igi2_frame.tPos2.tZ.vZ * ptElevator->tOrientation.tY.vZ
                             + igi2_frame.tPos2.tY.vZ * ptElevator->tOrientation.tY.vY;
        *(float *)&igi2_frame.tPos1[24] = igi2_frame.tPos2.tX.vX * ptElevator->tOrientation.tZ.vX
                             + igi2_frame.tPos2.tZ.vX * ptElevator->tOrientation.tZ.vZ
                             + igi2_frame.tPos2.tY.vX * ptElevator->tOrientation.tZ.vY;
        *(float *)&igi2_frame.tPos1[28] = igi2_frame.tPos2.tX.vY * ptElevator->tOrientation.tZ.vX
                             + igi2_frame.tPos2.tZ.vY * ptElevator->tOrientation.tZ.vZ
                             + igi2_frame.tPos2.tY.vY * ptElevator->tOrientation.tZ.vY;
        v6 = igi2_frame.tPos2.tX.vZ * ptElevator->tOrientation.tZ.vX + igi2_frame.tPos2.tZ.vZ * ptElevator->tOrientation.tZ.vZ;
        *(_DWORD *)&igi2_frame.tPos1[36] = ptElevator->tOrientation.nOps + igi2_frame.tPos2.nOps + 1;
        *(float *)&igi2_frame.tPos1[32] = v6 + igi2_frame.tPos2.tY.vZ * ptElevator->tOrientation.tZ.vY;
        qmemcpy(
          &ptElevator->tRigidDynCubeObj.tModelObj.tOrientation,
          igi2_frame.tPos1,
          sizeof(ptElevator->tRigidDynCubeObj.tModelObj.tOrientation));
      }
    }
    if ( ptElevator->tRigidDynCubeObj.tModelObj.tScale.vY <= (double)ptElevator->tRigidDynCubeObj.tModelObj.tScale.vZ )
      vZ = ptElevator->tRigidDynCubeObj.tModelObj.tScale.vZ;
    else
      vZ = ptElevator->tRigidDynCubeObj.tModelObj.tScale.vY;
    if ( vZ >= ptElevator->tRigidDynCubeObj.tModelObj.tScale.vX )
    {
      if ( ptElevator->tRigidDynCubeObj.tModelObj.tScale.vY <= (double)ptElevator->tRigidDynCubeObj.tModelObj.tScale.vZ )
        vY = ptElevator->tRigidDynCubeObj.tModelObj.tScale.vZ;
      else
        vY = ptElevator->tRigidDynCubeObj.tModelObj.tScale.vY;
    }
    else
    {
      vY = ptElevator->tRigidDynCubeObj.tModelObj.tScale.vX;
    }
    ptLODVirModel = ptElevator->tRigidDynCubeObj.tModelObj.ptLODVirModel;
    if ( ptLODVirModel && (v10 = ptLODVirModel->aptVirModel[0]) != nullptr )
      vRadius = v10->ptModel->ptMesh->vRadius;
    else
      vRadius = 1.0;
    igi2_frame.ptDynCubeObj = vY * vRadius;
    World_MoveDynCubeObjRadius(
      Game_ptGame->ptWorld,
      &ptElevator->tRigidDynCubeObj.tModelObj.tDynCubeObj,
      p_tPos,
      igi2_frame.ptDynCubeObj);
  }
}

// source: j/0/objects/elevator.c:278  [anchor-mhash]
struct Elevator_s *__cdecl Elevator_Move(struct Elevator_s *ptElevator)
{
  struct Elevator_s *v1; // ebx
  int nSplineObjQTaskID; // esi
  double LengthToWaypoint; // st7
  double v4; // st6
  double v5; // st5
  double v6; // st5
  double v7; // st5
  double v8; // st5
  double v9; // st5
  double v10; // st6
  double v11; // st6
  float vSpeed; // [esp+8h] [ebp-4h]
  float vSpeeda; // [esp+8h] [ebp-4h]

  v1 = ptElevator;
  nSplineObjQTaskID = ptElevator->nSplineObjQTaskID;
  if ( nSplineObjQTaskID != -1 )
  {
    ptElevator = (struct Elevator_s *)SplineObj_GetNumberOfWaypoint(ptElevator->nSplineObjQTaskID);
    if ( ptElevator )
    {
      LengthToWaypoint = SplineObj_GetLengthToWaypoint(nSplineObjQTaskID, v1->nWantedFloor);
      v4 = LengthToWaypoint - v1->vPos;
      v5 = v4;
      if ( v4 < 0.0 )
        v5 = -v4;
      if ( v5 >= 16384.0 )
      {
        if ( v1->vSpeed >= (double)v1->vMaxSpeed )
        {
          if ( v1->vSpeed > (double)v1->vMaxSpeed )
          {
            v9 = v1->vSpeed - v1->vSpeedInertia;
            v1->vSpeed = v9;
            if ( v9 < v1->vMaxSpeed )
              v1->vSpeed = v1->vMaxSpeed;
          }
        }
        else
        {
          v8 = v1->vSpeedInertia + v1->vSpeed;
          v1->vSpeed = v8;
          if ( v8 > v1->vMaxSpeed )
            v1->vSpeed = v1->vMaxSpeed;
        }
      }
      else
      {
        v6 = v4;
        if ( v4 < 0.0 )
          v6 = -v4;
        v7 = v6 * v1->vMaxSpeed * 6.103515625e-05;
        v1->vSpeed = v7;
        if ( v7 <= 0.10000000149011612 )
          v7 = 0.10000000149011612;
        v1->vSpeed = v7;
      }
      vSpeed = v1->vSpeed * 136.53334045410156;
      if ( v4 <= 0.0010000000474974513 )
      {
        if ( v4 < -0.0010000000474974513 )
        {
          v11 = v1->vPos - vSpeed;
          vSpeeda = v11;
          if ( v11 >= LengthToWaypoint )
            goto LABEL_19;
        }
      }
      else
      {
        v10 = vSpeed + v1->vPos;
        vSpeeda = v10;
        if ( v10 <= LengthToWaypoint )
        {
LABEL_19:
          v1->vPos = vSpeeda;
          Elevator_UpdatePosition(v1);
          return Elevator_UpdateChildPosition(v1);
        }
      }
      v1->vPos = LengthToWaypoint;
      Elevator_UpdatePosition(v1);
      return Elevator_UpdateChildPosition(v1);
    }
  }
  return ptElevator;
}

// source: j/0/objects/elevator.c:369  [anchor-mhash]
void __cdecl Elevator_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
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
  int v7; // ecx
  struct QReferenceList_s *p_tQTaskRefList; // eax
  _BYTE *v9; // eax
  int v10; // ecx

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
    WORLD_DYNCUBETREE_CATEGORY_MOBILE);
  ptQTask[9].tQTaskChildren.ptHead = (struct QTask_s *)1065353216;
  ptQTask[9].tQTaskRefList.ptMiddle = (struct QReference_s *)1065353216;
  ptQTask[10].ptNext = (struct QTask_s *)1065353216;
  ptQTask[8].ptNext = nullptr;
  ptQTask[8].ptPrev = nullptr;
  ptQTask[8].tQTaskChildren.ptHead = nullptr;
  ptQTask[8].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[8].tQTaskChildren.ptTail = nullptr;
  ptQTask[8].tQTaskRefList.ptHead = nullptr;
  ptQTask[9].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[9].tQTaskChildren.ptTail = nullptr;
  ptQTask[9].tQTaskRefList.ptHead = nullptr;
  ptQTask[9].tQTaskRefList.ptTail = nullptr;
  ptQTask[9].ptParent = nullptr;
  *(_DWORD *)&ptQTask[9].eQTaskType = 0;
  ptQTask[10].ptPrev = nullptr;
  ptQTask[11].tQTaskRefList.ptMiddle = (struct QReference_s *)-1;
  LOBYTE(ptQTask[11].tQTaskChildren.ptHead) = 0;
  ptQTask[11].tQTaskRefList.ptTail = nullptr;
  ptQTask[12].ptNext = nullptr;
  ptQTask[12].ptPrev = (struct QTask_s *)1084227584;
  ptQTask[12].tQTaskChildren.ptHead = (struct QTask_s *)1065185444;
  ptQTask[12].tQTaskChildren.ptTail = nullptr;
  ptQTask[12].tQTaskRefList.ptHead = nullptr;
  ptQTask[12].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[12].tQTaskRefList.ptTail = nullptr;
  ptQTask[13].ptPrev = nullptr;
  ptQTask[12].tQTaskChildren.ptMiddle = nullptr;
  v7 = 0;
  p_tQTaskRefList = &ptQTask[13].tQTaskRefList;
  do
  {
    *((_BYTE *)&ptQTask[12].ptParent + v7) = 0;
    p_tQTaskRefList[-1].ptMiddle = nullptr;
    p_tQTaskRefList[-1].ptTail = nullptr;
    p_tQTaskRefList->ptHead = nullptr;
    p_tQTaskRefList[5].ptTail = nullptr;
    ++v7;
    p_tQTaskRefList = (struct QReferenceList_s *)((char *)p_tQTaskRefList + 80);
  }
  while ( v7 < 10 );
  ptQTask[33].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[33].tQTaskChildren.ptTail = nullptr;
  ptQTask[33].tQTaskRefList.ptHead = nullptr;
  ptQTask[35].tQTaskChildren.ptHead = nullptr;
  ptQTask[35].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[35].tQTaskChildren.ptTail = nullptr;
  ptQTask[35].tQTaskRefList.ptHead = nullptr;
  ptQTask[37].tQTaskChildren.ptHead = nullptr;
  ptQTask[37].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[37].tQTaskChildren.ptTail = nullptr;
  ptQTask[37].tQTaskRefList.ptHead = nullptr;
  ptQTask[39].tQTaskChildren.ptHead = nullptr;
  qmemcpy(&ptQTask[8].tQTaskRefList.ptMiddle, &ptQTask[1], 0x18u);
  qmemcpy(&ptQTask[10].tQTaskChildren, &ptQTask[3].ptPrev, sizeof(struct QTask_s));
  LOBYTE(ptQTask[13].tQTaskChildren.ptHead) = 0;
  LOBYTE(ptQTask[39].tQTaskChildren.ptMiddle) = 0;
  BYTE1(ptQTask[39].tQTaskChildren.ptMiddle) = 0;
  BYTE2(ptQTask[39].tQTaskChildren.ptMiddle) = 0;
  HIBYTE(ptQTask[39].tQTaskChildren.ptMiddle) = 0;
  LOBYTE(ptQTask[39].tQTaskChildren.ptTail) = 0;
  LOBYTE(ptQTask[42].ptNext) = 1;
  v9 = (char *)&ptQTask[39].tQTaskChildren.ptTail + 1;
  v10 = 3;
  do
  {
    *v9 = 0;
    v9 += 32;
    --v10;
  }
  while ( v10 );
  *(_DWORD *)&ptQTask[41].eQTaskType = 0;
  ptQTask[11].eQTaskType = 0;
  ptQTask[42].ptPrev = (struct QTask_s *)-1;
}

// source: j/0/objects/elevator.c:473  [anchor-mhash]
void __cdecl Elevator_RunHandler(struct QTask_s *ptQTask)
{
  int NumberOfWaypoint; // ebx
  int v3; // edi
  struct QTask_s *nTicks; // eax
  struct QTask_s *ptHead; // ecx
  int v6; // edx
  struct QTask_s *v7; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v9; // edx
  struct LevelExpression_s *p_ptMiddle; // esi
  struct QTask_s *v11; // eax
  struct QTask_s *ptMiddle; // eax
  struct QTask_s *ptTail; // ecx
  struct QReference_s *v14; // edx
  int v15; // esi
  struct QReference_s *v16; // edi
  double LengthToWaypoint; // st7
  bool v18; // al
  struct QTask_s *v19; // eax
  struct QTask_s *v20; // esi
  struct QReference_s *v21; // eax
  int v22; // edx
  struct QTask_s *v23; // eax
  double v24; // st7
  struct QTask_s *v25; // eax
  int iFloor; // [esp+10h] [ebp-20h]
  int nFloor; // [esp+14h] [ebp-1Ch]
  struct QReference_s *vOldPos; // [esp+18h] [ebp-18h]
  int isUp; // [esp+1Ch] [ebp-14h]
  float vLastDist; // [esp+20h] [ebp-10h]
  float vOldWantedFloorPos; // [esp+24h] [ebp-Ch]
  int ptQTaska = *(int *)&ptQTask; // [esp+34h] [ebp+4h] ARGSLOT

  NumberOfWaypoint = SplineObj_GetNumberOfWaypoint((int)ptQTask[11].tQTaskRefList.ptMiddle);
  v3 = 0;
  vOldPos = ptQTask[11].tQTaskRefList.ptTail;
  nTicks = (struct QTask_s *)Flow_ptFlow->nTicks;
  isUp = 0;
  iFloor = 0;
  ptQTaska = 1;
  vLastDist = 0.0;
  if ( ptQTask[42].ptPrev != nTicks )
  {
    ptHead = ptQTask->tQTaskChildren.ptHead;
    ptQTask[42].ptPrev = nTicks;
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
    vOldWantedFloorPos = SplineObj_GetLengthToWaypoint(
                           (int)ptQTask[11].tQTaskRefList.ptMiddle,
                           (int)ptQTask[12].tQTaskChildren.ptMiddle);
    p_ptMiddle = (struct LevelExpression_s *)&ptQTask[13].tQTaskChildren.ptMiddle;
    do
    {
      if ( p_ptMiddle->zExpression && *p_ptMiddle->zCompiledExpression && p_ptMiddle->ptExpression )
        *((_BYTE *)&ptQTask[12].ptParent + v3) = (__int64)Level_RunLevelExpression(p_ptMiddle, ptQTask);
      ++v3;
      ++p_ptMiddle;
    }
    while ( v3 < 10 );
    if ( ptQTask[33].tQTaskChildren.ptMiddle
      && ptQTask[33].tQTaskChildren.ptTail->ptNext
      && ptQTask[33].tQTaskRefList.ptHead )
    {
      isUp = (__int64)Level_RunLevelExpression(
                        (struct LevelExpression_s *)&ptQTask[33].tQTaskChildren.ptMiddle,
                        ptQTask);
    }
    if ( ptQTask[35].tQTaskChildren.ptMiddle
      && ptQTask[35].tQTaskChildren.ptTail->ptNext
      && ptQTask[35].tQTaskRefList.ptHead )
    {
      iFloor = (__int64)Level_RunLevelExpression(
                          (struct LevelExpression_s *)&ptQTask[35].tQTaskChildren.ptMiddle,
                          ptQTask);
    }
    if ( ptQTask[37].tQTaskChildren.ptMiddle
      && ptQTask[37].tQTaskChildren.ptTail->ptNext
      && ptQTask[37].tQTaskRefList.ptHead )
    {
      ptQTaska = (__int64)Level_RunLevelExpression(
                            (struct LevelExpression_s *)&ptQTask[37].tQTaskChildren.ptMiddle,
                            ptQTask);
    }
    if ( !isUp || LOBYTE(ptQTask[39].tQTaskChildren.ptMiddle) )
    {
      if ( !iFloor || BYTE1(ptQTask[39].tQTaskChildren.ptMiddle) )
      {
        if ( LOBYTE(ptQTask[12].ptParent) )
          ptQTask[12].tQTaskChildren.ptMiddle = nullptr;
        if ( BYTE1(ptQTask[12].ptParent) )
          ptQTask[12].tQTaskChildren.ptMiddle = (struct QTask_s *)1;
        if ( BYTE2(ptQTask[12].ptParent) )
          ptQTask[12].tQTaskChildren.ptMiddle = (struct QTask_s *)2;
        if ( HIBYTE(ptQTask[12].ptParent) )
          ptQTask[12].tQTaskChildren.ptMiddle = (struct QTask_s *)3;
        if ( LOBYTE(ptQTask[12].eQTaskType) )
          ptQTask[12].tQTaskChildren.ptMiddle = (struct QTask_s *)4;
        if ( HIBYTE(ptQTask[12].eQTaskType) )
          ptQTask[12].tQTaskChildren.ptMiddle = (struct QTask_s *)5;
        if ( ptQTask[12].isInMemPool )
          ptQTask[12].tQTaskChildren.ptMiddle = (struct QTask_s *)6;
        if ( *(&ptQTask[12].isInMemPool + 1) )
          ptQTask[12].tQTaskChildren.ptMiddle = (struct QTask_s *)7;
        if ( LOBYTE(ptQTask[13].ptNext) )
          ptQTask[12].tQTaskChildren.ptMiddle = (struct QTask_s *)8;
        if ( BYTE1(ptQTask[13].ptNext) )
          ptQTask[12].tQTaskChildren.ptMiddle = (struct QTask_s *)9;
      }
      else
      {
        ptMiddle = ptQTask[12].tQTaskChildren.ptMiddle;
        if ( (int)ptMiddle > 0 )
          ptQTask[12].tQTaskChildren.ptMiddle = (struct QTask_s *)((char *)ptMiddle - 1);
      }
    }
    else
    {
      v11 = ptQTask[12].tQTaskChildren.ptMiddle;
      if ( (int)v11 < NumberOfWaypoint - 1 )
        ptQTask[12].tQTaskChildren.ptMiddle = (struct QTask_s *)((char *)&v11->ptNext + 1);
    }
    qmemcpy(&ptQTask[8].tQTaskRefList.ptMiddle, &ptQTask[1], 0x18u);
    BYTE1(ptQTask[39].tQTaskChildren.ptMiddle) = iFloor;
    qmemcpy(&ptQTask[10].tQTaskChildren, &ptQTask[3].ptPrev, sizeof(struct QTask_s));
    LOBYTE(ptQTask[39].tQTaskChildren.ptMiddle) = isUp;
    if ( ptQTaska )
      Elevator_Move((struct Elevator_s *)ptQTask);
    ptTail = ptQTask[12].tQTaskChildren.ptTail;
    v14 = ptQTask[12].tQTaskRefList.ptHead;
    ptQTask[12].tQTaskChildren.ptTail = nullptr;
    ptQTask[12].tQTaskRefList.ptHead = nullptr;
    v15 = 1;
    ptQTask[12].tQTaskRefList.ptMiddle = (struct QReference_s *)ptTail;
    ptQTask[12].tQTaskRefList.ptTail = v14;
    if ( NumberOfWaypoint > 1 )
    {
      v16 = ptQTask[11].tQTaskRefList.ptMiddle;
      while ( 1 )
      {
        LengthToWaypoint = SplineObj_GetLengthToWaypoint((int)v16, v15);
        if ( LengthToWaypoint > *(float *)&ptQTask[11].tQTaskRefList.ptTail )
          break;
        vLastDist = LengthToWaypoint;
        if ( ++v15 >= NumberOfWaypoint )
          goto LABEL_65;
      }
      *(double *)&ptQTask[12].tQTaskChildren.ptTail = (double)v15
                                                    - (LengthToWaypoint - *(float *)&ptQTask[11].tQTaskRefList.ptTail)
                                                    / (LengthToWaypoint - vLastDist);
    }
LABEL_65:
    if ( v15 == NumberOfWaypoint )
      *(double *)&ptQTask[12].tQTaskChildren.ptTail = (double)(NumberOfWaypoint - 1);
    *(float *)&nFloor = SplineObj_GetLengthToWaypoint(
                          (int)ptQTask[11].tQTaskRefList.ptMiddle,
                          (int)ptQTask[12].tQTaskChildren.ptMiddle);
    v18 = *(float *)&ptQTask[11].tQTaskRefList.ptTail != *(float *)&nFloor;
    BYTE2(ptQTask[39].tQTaskChildren.ptMiddle) = v18;
    if ( v18 )
    {
      if ( !*(_DWORD *)&ptQTask[41].eQTaskType )
      {
        v19 = SoundSys_NewSoundFn(Level_ptDynamicQTask, (char *)&ptQTask[41].ptNext + 1);
        v20 = v19;
        if ( v19 )
        {
          v21 = QTask_NewQTaskRef(v19);
          v22 = 511 * SoundSys_eSetPositionQTaskEvent;
          *(_DWORD *)&ptQTask[41].eQTaskType = v21;
          ((void (__cdecl *)(struct QTask_s *, struct QTask_s *))QTask_aatQTaskFinalEvent[0][v20->eQTaskType + v22].pfHandler)(
            v20,
            &ptQTask[1]);
        }
      }
    }
    else
    {
      QTask_DeleteQTaskAndQTaskRefSafe((struct QReference_s **)&ptQTask[41].eQTaskType);
    }
    HIBYTE(ptQTask[39].tQTaskChildren.ptMiddle) = 0;
    if ( *(float *)&vOldPos == vOldWantedFloorPos && *(float *)&vOldPos != *(float *)&ptQTask[11].tQTaskRefList.ptTail )
    {
      v23 = SoundSys_NewSoundFn(Level_ptDynamicQTask, (char *)&ptQTask[39].tQTaskChildren.ptTail + 1);
      HIBYTE(ptQTask[39].tQTaskChildren.ptMiddle) = 1;
      if ( v23 )
        ((void (__cdecl *)(struct QTask_s *, struct QTask_s *))QTask_aatQTaskFinalEvent[SoundSys_eSetPositionQTaskEvent][v23->eQTaskType].pfHandler)(
          v23,
          &ptQTask[1]);
    }
    v24 = *(float *)&ptQTask[11].tQTaskRefList.ptTail;
    LOBYTE(ptQTask[39].tQTaskChildren.ptTail) = 0;
    if ( v24 == *(float *)&nFloor && *(float *)&vOldPos != *(float *)&ptQTask[11].tQTaskRefList.ptTail )
    {
      v25 = SoundSys_NewSoundFn(Level_ptDynamicQTask, (char *)&ptQTask[40].tQTaskChildren.ptHead + 1);
      LOBYTE(ptQTask[39].tQTaskChildren.ptTail) = 1;
      if ( v25 )
        ((void (__cdecl *)(struct QTask_s *, struct QTask_s *))QTask_aatQTaskFinalEvent[SoundSys_eSetPositionQTaskEvent][v25->eQTaskType].pfHandler)(
          v25,
          &ptQTask[1]);
    }
    if ( *(float *)&ptQTask[11].tQTaskRefList.ptTail == *(float *)&nFloor
      && !BYTE2(ptQTask[39].tQTaskChildren.ptMiddle)
      && ptQTaska == SLOBYTE(ptQTask[42].ptNext) )
    {
      ++*(int *)&ptQTask[13].ptPrev;
      LOBYTE(ptQTask[42].ptNext) = ptQTaska;
    }
    else
    {
      ptQTask[13].ptPrev = nullptr;
      LOBYTE(ptQTask[42].ptNext) = ptQTaska;
    }
  }
}

// source: j/0/objects/elevator.c:688  [anchor-caller]
void __cdecl Elevator_DeleteHandler(struct QTask_s *ptQTask)
{
  int v1; // eax
  struct QReference_s *v2; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  struct LevelExpression_s *p_ptMiddle; // esi
  int v5; // edi
  struct QTask_s *ptHead; // eax
  struct QTask_s *ptParent; // edi
  struct QTask_s *ptTail; // ecx
  struct QTask_s *ptMiddle; // edx

  QTask_DeleteQTaskAndQTaskRefSafe((struct QReference_s **)&ptQTask[41].eQTaskType);
  v1 = 0;
  while ( 1 )
  {
    v2 = Level_atLevelQTaskID[v1];
    if ( v2 )
    {
      if ( v2->pxObject == ptQTask )
        break;
    }
    if ( ++v1 >= 4096 )
      goto LABEL_9;
  }
  if ( v1 >= 0 )
  {
    pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Level_eRemoveLevelScriptSymbolsEvent][ptQTask->eQTaskType].pfHandler;
    if ( pfHandler )
      pfHandler(ptQTask);
  }
LABEL_9:
  p_ptMiddle = (struct LevelExpression_s *)&ptQTask[13].tQTaskChildren.ptMiddle;
  v5 = 10;
  do
  {
    Level_DeinitLevelExpression(p_ptMiddle++);
    --v5;
  }
  while ( v5 );
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[35].tQTaskChildren.ptMiddle);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[33].tQTaskChildren.ptMiddle);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[37].tQTaskChildren.ptMiddle);
  ptHead = ptQTask[2].tQTaskChildren.ptHead;
  ptParent = ptQTask[2].ptParent;
  if ( ptHead )
  {
    *((_DWORD *)&ptParent[1].tQTaskChildren.ptMiddle + (int)ptHead[1].tQTaskChildren.ptMiddle) = 0;
    ptTail = ptQTask[2].tQTaskChildren.ptTail;
    if ( ptQTask == ptHead[1].ptPrev )
    {
      ptHead[1].ptPrev = ptTail;
      if ( ptTail )
      {
        ptTail[2].tQTaskChildren.ptMiddle = nullptr;
        DynCube_DelEmptyTreeNodesUpwards((struct World_s *)ptParent, (struct DynCubeTreeItem_s *)ptHead);
        ptQTask[2].tQTaskChildren.ptHead = nullptr;
        return;
      }
    }
    else
    {
      ptMiddle = ptQTask[2].tQTaskChildren.ptMiddle;
      if ( ptTail )
        ptTail[2].tQTaskChildren.ptMiddle = ptMiddle;
      if ( ptMiddle )
        ptMiddle[2].tQTaskChildren.ptTail = ptTail;
    }
    DynCube_DelEmptyTreeNodesUpwards((struct World_s *)ptParent, (struct DynCubeTreeItem_s *)ptHead);
    ptQTask[2].tQTaskChildren.ptHead = nullptr;
  }
}

// source: j/0/objects/elevator.c:730  [size]
void __cdecl Elevator_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = Elevator_ptParameterList;
}

// source: j/0/objects/elevator.c:746  [anchor-mhash]
void __cdecl Elevator_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct LODVirModel_s *LODVirModelExistsFn; // eax
  struct QTask_s *ptTail; // edx
  struct QTask_s **p_ptPrev; // ebp
  struct QReference_s *ptHead; // eax
  struct LevelExpression_s *p_ptMiddle; // esi
  int v8; // edi
  double v9; // st7
  float ptQTaska = *(float *)&ptQTask; // [esp+18h] [ebp+4h] ARGSLOT

  LODVirModelExistsFn = MTP_GetLODVirModelExistsFn((char *)&ptQTask[11].tQTaskChildren);
  if ( LODVirModelExistsFn != *(struct LODVirModel_s **)&ptQTask[2].eQTaskType )
  {
    ModelObj_SetLODVirModel((struct ModelObj_s *)ptQTask, LODVirModelExistsFn, false);
    ptQTask[7].tQTaskRefList.ptHead = nullptr;
    ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
    ptQTask[7].tQTaskRefList.ptTail = nullptr;
    ptQTask[7].ptParent = nullptr;
    *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  }
  ptTail = ptQTask[12].tQTaskChildren.ptTail;
  p_ptPrev = &ptQTask[3].ptPrev;
  ptQTask[13].ptPrev = nullptr;
  ptQTask[12].ptNext = nullptr;
  ptHead = ptQTask[12].tQTaskRefList.ptHead;
  qmemcpy(&ptQTask[3].ptPrev, &ptQTask[9].tQTaskChildren, sizeof(struct QTask_s));
  ptQTask[12].tQTaskRefList.ptMiddle = (struct QReference_s *)ptTail;
  ptQTask[12].tQTaskRefList.ptTail = ptHead;
  p_ptMiddle = (struct LevelExpression_s *)&ptQTask[13].tQTaskChildren.ptMiddle;
  v8 = 10;
  do
  {
    Level_CompileLevelExpression(p_ptMiddle++, ptQTask);
    --v8;
  }
  while ( v8 );
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[35].tQTaskChildren.ptMiddle, ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[33].tQTaskChildren.ptMiddle, ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[37].tQTaskChildren.ptMiddle, ptQTask);
  ptQTaska = SplineObj_GetTotalLength((int)ptQTask[11].tQTaskRefList.ptMiddle);
  v9 = *(float *)&ptQTask[11].ptParent;
  ptQTask[11].tQTaskRefList.ptTail = (struct QReference_s *)ptQTask[11].ptParent;
  if ( v9 < 0.0 )
    ptQTask[11].tQTaskRefList.ptTail = nullptr;
  if ( *(float *)&ptQTask[11].ptParent > (double)ptQTaska )
    *(float *)&ptQTask[11].tQTaskRefList.ptTail = ptQTaska;
  Elevator_UpdatePosition((struct Elevator_s *)ptQTask);
  if ( pxContext && *(_DWORD *)pxContext )
  {
    qmemcpy(&ptQTask[8].tQTaskRefList.ptMiddle, &ptQTask[1], 0x18u);
    qmemcpy(&ptQTask[10].tQTaskChildren, p_ptPrev, sizeof(struct QTask_s));
  }
  qmemcpy(&ptQTask[8].tQTaskRefList.ptMiddle, &ptQTask[1], 0x18u);
  qmemcpy(&ptQTask[10].tQTaskChildren, p_ptPrev, sizeof(struct QTask_s));
  Elevator_tParameterReal32ContextPos.vMax = ptQTaska;
  HIBYTE(ptQTask[39].tQTaskChildren.ptMiddle) = 0;
  LOBYTE(ptQTask[39].tQTaskChildren.ptTail) = 0;
  LOBYTE(ptQTask[42].ptNext) = 1;
}

// source: j/0/objects/elevator.c:835  [anchor-mhash]
void __cdecl Elevator_RegisterScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int i; // edi

  if ( !LOBYTE(ptQTask[13].tQTaskChildren.ptHead) )
  {
    LOBYTE(ptQTask[13].tQTaskChildren.ptHead) = 1;
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.vFloor", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      Script_Float,
      &ptQTask[12].tQTaskChildren.ptTail,
      8,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_FLOAT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.vLastFloor", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      Script_Float,
      &ptQTask[12].tQTaskRefList.ptMiddle,
      8,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_FLOAT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    for ( i = 0; i < 10; ++i )
    {
      sprintf(igi2_frame.zTemp, "%s.isWantedFloor%d", igi2_frame.zName, i);
      Symbol_Register(
        igi2_frame.zTemp,
        (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
        (char *)&ptQTask[12].ptParent + i,
        1,
        QSCRIPT_SYMBOLCLASS_VARIABLE,
        QSCRIPT_SYMBOLTYPE_INT,
        QSCRIPT_SYMBOLLIFESPAN_FINITE);
    }
    sprintf(igi2_frame.zTemp, "%s.nInactive", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int,
      &ptQTask[13].ptPrev,
      4,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.nWantedFloor", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int,
      &ptQTask[12].tQTaskChildren.ptMiddle,
      4,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.isMoving", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      (char *)&ptQTask[39].tQTaskChildren.ptMiddle + 2,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.isStart", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      (char *)&ptQTask[39].tQTaskChildren.ptMiddle + 3,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.isStop", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      &ptQTask[39].tQTaskChildren.ptTail,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
  }
}

// source: j/0/objects/elevator.c:892  [anchor-mhash]
void __cdecl Elevator_RemoveScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int i; // edi

  if ( LOBYTE(ptQTask[13].tQTaskChildren.ptHead) )
  {
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    LOBYTE(ptQTask[13].tQTaskChildren.ptHead) = 0;
    sprintf(igi2_frame.zTemp, "%s.vFloor", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.vLastFloor", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    for ( i = 0; i < 10; ++i )
    {
      sprintf(igi2_frame.zTemp, "%s.isWantedFloor%d", igi2_frame.zName, i);
      Symbol_Remove(igi2_frame.zTemp);
    }
    sprintf(igi2_frame.zTemp, "%s.nInactive", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.nWantedFloor", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.isMoving", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.isStart", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.isStop", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    LOBYTE(ptQTask[13].tQTaskChildren.ptHead) = 0;
  }
}

// source: j/0/objects/elevator.c:1066  [anchor-strings]
void __cdecl Elevator_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // edx
  int v3; // edi
  unsigned int v4; // ebx
  char *v5; // esi
  signed int i; // esi

  v0 = QTask_NewQTaskType("Elevator", 1688, RigidDynCubeObj_eQTaskType, 0, 0);
  Elevator_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, Elevator_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, Elevator_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, Elevator_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Elevator_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, Elevator_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eRegisterLevelScriptSymbolsEvent,
    Elevator_RegisterScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Level_eRemoveLevelScriptSymbolsEvent, Elevator_RemoveScriptSymbolsHandler);
  Elevator_tParameterReal32ContextPos.vMin = 0.0;
  Elevator_tParameterReal32ContextPos.vMax = 10000000.0;
  Elevator_tParameterReal32ContextMaxSpeed.vMin = 0.0;
  Elevator_tParameterReal32ContextMaxSpeed.vMax = 10000.0;
  Elevator_tParameterReal32ContextInertia.vMin = 0.0;
  Elevator_tParameterReal32ContextInertia.vMax = 1.0;
  v1 = (struct ParameterList_s *)Mem_AllocFn(512, 4);
  v2 = Level_eParameterTypeObjectPos;
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  v1->nParameters = 0;
  v1->nMaxParameters = 25;
  Elevator_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0x140u, v2, "Position", 7u, nullptr);
  ParameterList_AddParameter(Elevator_ptParameterList, 0x170u, Level_eParameterTypeReal32x9, "Orientation", 7u, nullptr);
  ParameterList_AddParameter(Elevator_ptParameterList, 0x1C0u, Level_eParameterTypeString16, "Model", 7u, nullptr);
  ParameterList_AddParameter(
    Elevator_ptParameterList,
    0x1D0u,
    Level_eParameterTypeInt32,
    "SplineObj taskid",
    7u,
    nullptr);
  ParameterList_AddParameter(Elevator_ptParameterList, 0x1DCu, Level_eParameterTypebool8, "Linear", 7u, nullptr);
  ParameterList_AddParameter(
    Elevator_ptParameterList,
    0x1DDu,
    Level_eParameterTypebool8,
    "Force orientation",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Elevator_ptParameterList,
    0x1D8u,
    Level_eParameterTypeReal32,
    off_68D890,
    7u,
    &Elevator_tParameterReal32ContextPos);
  ParameterList_AddParameter(
    Elevator_ptParameterList,
    0x1E4u,
    Level_eParameterTypeReal32,
    "Max speed",
    7u,
    &Elevator_tParameterReal32ContextMaxSpeed);
  ParameterList_AddParameter(
    Elevator_ptParameterList,
    0x1E8u,
    Level_eParameterTypeReal32,
    "Speed inertia",
    7u,
    &Elevator_tParameterReal32ContextInertia);
  ParameterList_AddParameter(Elevator_ptParameterList, 0x584u, Level_eParameterTypeVarString, "Floor down", 7u, nullptr);
  ParameterList_AddParameter(Elevator_ptParameterList, 0x534u, Level_eParameterTypeVarString, "Floor up", 7u, nullptr);
  ParameterList_AddParameter(Elevator_ptParameterList, 0x5D4u, Level_eParameterTypeVarString, "Can start", 7u, nullptr);
  v3 = 0;
  v4 = 532;
  v5 = byte_79EE368;
  do
  {
    sprintf(v5, "Wanted floor %d", v3);
    ParameterList_AddParameter(Elevator_ptParameterList, v4, Level_eParameterTypeVarString, v5, 7u, nullptr);
    v5 += 32;
    ++v3;
    v4 += 80;
  }
  while ( (int)v5 < 127853736 );
  for ( i = 1577; i < 1673; i += 32 )
    ParameterList_AddParameter(
      Elevator_ptParameterList,
      i,
      Level_eParameterTypeString32,
      &aStartSound[i - 1577],
      7u,
      nullptr);
}

// source: j/0/objects/elevator.c:1153  [size]
void __cdecl Elevator_Close()
{
  int v0; // esi

  if ( Elevator_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&Elevator_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(Elevator_eQTaskType);
}

// source: j/0/objects/elevator.c:1170  [size]
unsigned __int16 __cdecl Elevator_GetQTaskType()
{
  return Elevator_eQTaskType;
}
