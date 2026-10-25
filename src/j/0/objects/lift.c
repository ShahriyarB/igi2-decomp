/* j/0/objects/lift.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/objects/lift.c:181  [size]
void __cdecl Lift_GetSerializeParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = Lift_ptSerializeParameterList;
}

// source: j/0/objects/lift.c:199  [size]
void __cdecl Lift_DeSerializeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[Serialize_eDeSerializeQTaskEvent][RigidDynCubeObj_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  QTask_DeleteQTaskAndQTaskRefSafe((struct QReference_s **)&ptQTask[23].eQTaskType);
}

// source: j/0/objects/lift.c:217  [anchor-mhash]
void __cdecl Lift_UpdatePosition(struct Lift_s *ptLift)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[16]; float vZZ; };
    struct { char igi2_o2[20]; float vXZ; };
    struct { char igi2_o3[24]; float vYW; };
    struct { char igi2_o4[28]; float vYZ; };
    struct { char igi2_o5[32]; float vXW; };
    struct { char igi2_o6[36]; float vYY; };
    struct { char igi2_o7[40]; struct Quat32_t tInterpolatedOrientation; };
    struct { char igi2_o8[60]; struct real64x3_t tStopPos; };
    struct { char igi2_o9[84]; struct real64x3_t tStartPos; };
    struct { char igi2_o10[108]; struct real64x3_t tPos; };
    char igi2_extent[136];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QReference_s *ptActiveFloor; // eax
  double v2; // st7
  long double v3; // st7
  long double v4; // st7
  double vY; // st7
  bool v6; // c0
  bool v7; // c3
  int v8; // ecx
  int v9; // edx
  int v10; // esi
  double v11; // st7
  double vZ; // st7
  double v13; // st7
  long double v14; // st7
  long double v15; // st7
  double v16; // st7
  bool v17; // c0
  bool v18; // c3
  int v19; // ecx
  int v20; // edx
  int v21; // esi
  double v22; // st7
  float vPos; // eax
  int nOps; // ecx
  double v25; // st7
  double v26; // st6
  double v27; // st5
  double v28; // st7
  double v29; // st7
  double vX; // st7
  struct LODVirModel_s *ptLODVirModel; // eax
  struct VirModel_s *v32; // eax
  double vRadius; // st6

  ptActiveFloor = ptLift->ptActiveFloor;
  if ( ptActiveFloor && ptActiveFloor->pxObject )
  {
    qmemcpy(&igi2_frame.tStartPos, &ptLift->tStartPos, sizeof(igi2_frame.tStartPos));
    qmemcpy(&igi2_frame.tStopPos, &ptLift->tStopPos, sizeof(igi2_frame.tStopPos));
    igi2_frame.tPos.vX = (igi2_frame.tStopPos.vX - igi2_frame.tStartPos.vX) * ptLift->vPos + igi2_frame.tStartPos.vX;
    igi2_frame.tPos.vY = (igi2_frame.tStopPos.vY - igi2_frame.tStartPos.vY) * ptLift->vPos + igi2_frame.tStartPos.vY;
    igi2_frame.tPos.vZ = (igi2_frame.tStopPos.vZ - igi2_frame.tStartPos.vZ) * ptLift->vPos + igi2_frame.tStartPos.vZ;
    v2 = ptLift->tStartOrientation.tZ.vZ + ptLift->tStartOrientation.tY.vY + ptLift->tStartOrientation.tX.vX;
    if ( v2 <= 0.0 )
    {
      vY = ptLift->tStartOrientation.tY.vY;
      LODWORD(igi2_frame.tInterpolatedOrientation.vX) = 1;
      v6 = vY < ptLift->tStartOrientation.tX.vX;
      v7 = vY == ptLift->tStartOrientation.tX.vX;
      LODWORD(igi2_frame.tInterpolatedOrientation.vY) = 2;
      igi2_frame.tInterpolatedOrientation.vZ = 0.0;
      v8 = !v6 && !v7;
      if ( ptLift->tStartOrientation.tZ.vZ > (double)*(&ptLift->tStartOrientation.tX.vX + 4 * v8) )
        v8 = 2;
      v9 = *((_DWORD *)&igi2_frame.tInterpolatedOrientation.vX + v8);
      v10 = *((_DWORD *)&igi2_frame.tInterpolatedOrientation.vX + v9);
      v11 = sqrt(
              *(&ptLift->tStartOrientation.tX.vX + 4 * v8)
            - *(&ptLift->tStartOrientation.tX.vX + 4 * v9)
            - *(&ptLift->tStartOrientation.tX.vX + 4 * v10)
            + 1.0);
      *((float *)&igi2_frame.tStartPos.vX + v8) = 0.5 * v11;
      if ( v11 != 0.0 )
        v11 = 0.5 / v11;
      *((float *)&igi2_frame.tStartPos.vX + v9) = (*(&ptLift->tStartOrientation.tX.vX + 3 * v9 + v8)
                                      + *(&ptLift->tStartOrientation.tX.vX + 3 * v8 + v9))
                                     * v11;
      *((float *)&igi2_frame.tStartPos.vX + v10) = (*(&ptLift->tStartOrientation.tX.vX + 3 * v10 + v8)
                                       + *(&ptLift->tStartOrientation.tX.vX + 3 * v8 + v10))
                                      * v11;
      *((float *)&igi2_frame.tStartPos.vY + 1) = -((*(&ptLift->tStartOrientation.tX.vX + 3 * v9 + v10)
                                       - *(&ptLift->tStartOrientation.tX.vX + 3 * v10 + v9))
                                      * v11);
    }
    else
    {
      v3 = sqrt(v2 + 1.0);
      *((float *)&igi2_frame.tStartPos.vY + 1) = 0.5 * v3;
      v4 = 0.5 / v3;
      *(float *)&igi2_frame.tStartPos.vX = -((ptLift->tStartOrientation.tY.vZ - ptLift->tStartOrientation.tZ.vY) * v4);
      *((float *)&igi2_frame.tStartPos.vX + 1) = -((ptLift->tStartOrientation.tZ.vX - ptLift->tStartOrientation.tX.vZ) * v4);
      *(float *)&igi2_frame.tStartPos.vY = -((ptLift->tStartOrientation.tX.vY - ptLift->tStartOrientation.tY.vX) * v4);
    }
    vZ = ptLift->tStopOrientation.tZ.vZ;
    LODWORD(igi2_frame.tStartPos.vZ) = ptLift->tStartOrientation.nOps;
    v13 = vZ + ptLift->tStopOrientation.tY.vY + ptLift->tStopOrientation.tX.vX;
    if ( v13 <= 0.0 )
    {
      v16 = ptLift->tStopOrientation.tY.vY;
      LODWORD(igi2_frame.tInterpolatedOrientation.vX) = 1;
      v17 = v16 < ptLift->tStopOrientation.tX.vX;
      v18 = v16 == ptLift->tStopOrientation.tX.vX;
      LODWORD(igi2_frame.tInterpolatedOrientation.vY) = 2;
      igi2_frame.tInterpolatedOrientation.vZ = 0.0;
      v19 = !v17 && !v18;
      if ( ptLift->tStopOrientation.tZ.vZ > (double)*(&ptLift->tStopOrientation.tX.vX + 4 * v19) )
        v19 = 2;
      v20 = *((_DWORD *)&igi2_frame.tInterpolatedOrientation.vX + v19);
      v21 = *((_DWORD *)&igi2_frame.tInterpolatedOrientation.vX + v20);
      v22 = sqrt(
              *(&ptLift->tStopOrientation.tX.vX + 4 * v19)
            - *(&ptLift->tStopOrientation.tX.vX + 4 * v20)
            - *(&ptLift->tStopOrientation.tX.vX + 4 * v21)
            + 1.0);
      *((float *)&igi2_frame.tStopPos.vX + v19) = 0.5 * v22;
      if ( v22 != 0.0 )
        v22 = 0.5 / v22;
      *((float *)&igi2_frame.tStopPos.vX + v20) = (*(&ptLift->tStopOrientation.tX.vX + 3 * v20 + v19)
                                      + *(&ptLift->tStopOrientation.tX.vX + 3 * v19 + v20))
                                     * v22;
      *((float *)&igi2_frame.tStopPos.vX + v21) = (*(&ptLift->tStopOrientation.tX.vX + 3 * v21 + v19)
                                      + *(&ptLift->tStopOrientation.tX.vX + 3 * v19 + v21))
                                     * v22;
      *((float *)&igi2_frame.tStopPos.vY + 1) = -((*(&ptLift->tStopOrientation.tX.vX + 3 * v20 + v21)
                                      - *(&ptLift->tStopOrientation.tX.vX + 3 * v21 + v20))
                                     * v22);
    }
    else
    {
      v14 = sqrt(v13 + 1.0);
      *((float *)&igi2_frame.tStopPos.vY + 1) = 0.5 * v14;
      v15 = 0.5 / v14;
      *(float *)&igi2_frame.tStopPos.vX = -((ptLift->tStopOrientation.tY.vZ - ptLift->tStopOrientation.tZ.vY) * v15);
      *((float *)&igi2_frame.tStopPos.vX + 1) = -((ptLift->tStopOrientation.tZ.vX - ptLift->tStopOrientation.tX.vZ) * v15);
      *(float *)&igi2_frame.tStopPos.vY = -((ptLift->tStopOrientation.tX.vY - ptLift->tStopOrientation.tY.vX) * v15);
    }
    vPos = ptLift->vPos;
    LODWORD(igi2_frame.tStopPos.vZ) = ptLift->tStopOrientation.nOps;
    Quat32_SLERP(&igi2_frame.tInterpolatedOrientation, (struct Quat32_t *)&igi2_frame.tStartPos, (struct Quat32_t *)&igi2_frame.tStopPos, vPos);
    nOps = igi2_frame.tInterpolatedOrientation.nOps;
    v25 = igi2_frame.tInterpolatedOrientation.vX * igi2_frame.tInterpolatedOrientation.vX
        + igi2_frame.tInterpolatedOrientation.vX * igi2_frame.tInterpolatedOrientation.vX;
    v26 = igi2_frame.tInterpolatedOrientation.vY * igi2_frame.tInterpolatedOrientation.vX
        + igi2_frame.tInterpolatedOrientation.vY * igi2_frame.tInterpolatedOrientation.vX;
    igi2_frame.vXZ = igi2_frame.tInterpolatedOrientation.vZ * igi2_frame.tInterpolatedOrientation.vX
        + igi2_frame.tInterpolatedOrientation.vZ * igi2_frame.tInterpolatedOrientation.vX;
    igi2_frame.vXW = igi2_frame.tInterpolatedOrientation.vW * igi2_frame.tInterpolatedOrientation.vX
        + igi2_frame.tInterpolatedOrientation.vW * igi2_frame.tInterpolatedOrientation.vX;
    igi2_frame.vYY = igi2_frame.tInterpolatedOrientation.vY * igi2_frame.tInterpolatedOrientation.vY
        + igi2_frame.tInterpolatedOrientation.vY * igi2_frame.tInterpolatedOrientation.vY;
    igi2_frame.vYZ = igi2_frame.tInterpolatedOrientation.vZ * igi2_frame.tInterpolatedOrientation.vY
        + igi2_frame.tInterpolatedOrientation.vZ * igi2_frame.tInterpolatedOrientation.vY;
    igi2_frame.vYW = igi2_frame.tInterpolatedOrientation.vW * igi2_frame.tInterpolatedOrientation.vY
        + igi2_frame.tInterpolatedOrientation.vW * igi2_frame.tInterpolatedOrientation.vY;
    igi2_frame.vZZ = igi2_frame.tInterpolatedOrientation.vZ * igi2_frame.tInterpolatedOrientation.vZ
        + igi2_frame.tInterpolatedOrientation.vZ * igi2_frame.tInterpolatedOrientation.vZ;
    v27 = igi2_frame.tInterpolatedOrientation.vW * igi2_frame.tInterpolatedOrientation.vZ
        + igi2_frame.tInterpolatedOrientation.vW * igi2_frame.tInterpolatedOrientation.vZ;
    ptLift->tRigidDynCubeObj.tModelObj.tOrientation.tX.vX = 1.0 - igi2_frame.vYY - igi2_frame.vZZ;
    ptLift->tRigidDynCubeObj.tModelObj.tOrientation.tX.vY = v26 - v27;
    ptLift->tRigidDynCubeObj.tModelObj.tOrientation.tX.vZ = igi2_frame.vYW + igi2_frame.vXZ;
    ptLift->tRigidDynCubeObj.tModelObj.tOrientation.tY.vX = v27 + v26;
    v28 = 1.0 - v25;
    ptLift->tRigidDynCubeObj.tModelObj.tOrientation.tY.vY = v28 - igi2_frame.vZZ;
    ptLift->tRigidDynCubeObj.tModelObj.tOrientation.tY.vZ = igi2_frame.vYZ - igi2_frame.vXW;
    ptLift->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vX = igi2_frame.vXZ - igi2_frame.vYW;
    ptLift->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vY = igi2_frame.vYZ + igi2_frame.vXW;
    ptLift->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vZ = v28 - igi2_frame.vYY;
    ptLift->tRigidDynCubeObj.tModelObj.tOrientation.nOps = nOps;
  }
  else
  {
    qmemcpy(&igi2_frame.tPos, &ptLift->tStartPos, sizeof(igi2_frame.tPos));
    qmemcpy(
      &ptLift->tRigidDynCubeObj.tModelObj.tOrientation,
      &ptLift->tStartOrientation,
      sizeof(ptLift->tRigidDynCubeObj.tModelObj.tOrientation));
  }
  if ( ptLift->tRigidDynCubeObj.tModelObj.tScale.vY <= (double)ptLift->tRigidDynCubeObj.tModelObj.tScale.vZ )
    v29 = ptLift->tRigidDynCubeObj.tModelObj.tScale.vZ;
  else
    v29 = ptLift->tRigidDynCubeObj.tModelObj.tScale.vY;
  if ( v29 >= ptLift->tRigidDynCubeObj.tModelObj.tScale.vX )
  {
    if ( ptLift->tRigidDynCubeObj.tModelObj.tScale.vY <= (double)ptLift->tRigidDynCubeObj.tModelObj.tScale.vZ )
      vX = ptLift->tRigidDynCubeObj.tModelObj.tScale.vZ;
    else
      vX = ptLift->tRigidDynCubeObj.tModelObj.tScale.vY;
  }
  else
  {
    vX = ptLift->tRigidDynCubeObj.tModelObj.tScale.vX;
  }
  ptLODVirModel = ptLift->tRigidDynCubeObj.tModelObj.ptLODVirModel;
  if ( ptLODVirModel && (v32 = ptLODVirModel->aptVirModel[0]) != nullptr )
    vRadius = v32->ptModel->ptMesh->vRadius;
  else
    vRadius = 1.0;
  igi2_frame.ptDynCubeObj = vX * vRadius;
  World_MoveDynCubeObjRadius(Game_ptGame->ptWorld, &ptLift->tRigidDynCubeObj.tModelObj.tDynCubeObj, &igi2_frame.tPos, igi2_frame.ptDynCubeObj);
}

// source: j/0/objects/lift.c:281  [anchor-mhash]
enum bool __cdecl Lift_Move(struct Lift_s *ptLift)
{
  double v2; // st7
  long double v3; // st7
  double v4; // st6
  double v5; // st6
  long double v6; // st7
  long double v7; // st6
  long double v8; // st6
  double v9; // st7
  float vDiff; // [esp+8h] [ebp-14h]
  float vOldPos; // [esp+Ch] [ebp-10h]
  float tDiff; // [esp+10h] [ebp-Ch]
  float tDiff_4; // [esp+14h] [ebp-8h]

  vOldPos = ptLift->vPos;
  tDiff = ptLift->tStopPos.vX - ptLift->tStartPos.vX;
  tDiff_4 = ptLift->tStopPos.vY - ptLift->tStartPos.vY;
  v2 = ptLift->tStopPos.vZ - ptLift->tStartPos.vZ;
  vDiff = 1.0 - vOldPos;
  v3 = ptLift->vMaxSpeed * 4096.0 * 0.03333333507180214 / sqrt(tDiff * tDiff + tDiff_4 * tDiff_4 + v2 * v2);
  v4 = vDiff;
  if ( vDiff < 0.0 )
    v4 = -v4;
  if ( v4 >= 0.10000000149011612 )
  {
    if ( v3 <= ptLift->vSpeed )
    {
      if ( v3 < ptLift->vSpeed )
      {
        v8 = ptLift->vSpeed - ptLift->vSpeedInertia;
        ptLift->vSpeed = v8;
        if ( v8 < v3 )
          ptLift->vSpeed = v3;
      }
    }
    else
    {
      v7 = ptLift->vSpeedInertia + ptLift->vSpeed;
      ptLift->vSpeed = v7;
      if ( v7 > v3 )
        ptLift->vSpeed = v3;
    }
  }
  else
  {
    v5 = vDiff;
    if ( vDiff < 0.0 )
      v5 = -v5;
    v6 = v3 * v5 * 10.0;
    ptLift->vSpeed = v6;
    if ( v6 <= 0.0010000000474974513 )
      v6 = 0.0010000000474974513;
    ptLift->vSpeed = v6;
  }
  v9 = ptLift->vSpeed + ptLift->vPos;
  if ( v9 >= 1.0 )
    v9 = 1.0;
  ptLift->vPos = v9;
  Lift_UpdatePosition(ptLift);
  RigidDynCubeObj_UpdateAttachments(&ptLift->tRigidDynCubeObj);
  return ptLift->vPos != vOldPos;
}

// source: j/0/objects/lift.c:338  [anchor-caller]
struct Lift_s *__cdecl Lift_SetPositionToFirstFloor(struct Lift_s *ptLift)
{
  struct QReference_s *ptActiveFloor; // eax
  int nFirstFloorID; // eax
  struct QReference_s *v4; // eax
  struct QTask_s *FirstChildOfType; // ebp
  struct QReference_s *v6; // eax
  struct QTask_s *v7; // eax
  struct QReference_s **p_ptMiddle; // ebp
  __int16 v9; // cx
  struct Lift_s *result; // eax
  unsigned __int16 v11; // cx
  struct QTask_s *i; // eax

  ptLift->nCurrentFloor = 0;
  ptActiveFloor = ptLift->ptActiveFloor;
  if ( ptActiveFloor )
  {
    QReference_Delete(ptActiveFloor, &QTask_tQTaskRefPool);
    ptLift->ptActiveFloor = nullptr;
  }
  nFirstFloorID = ptLift->nFirstFloorID;
  if ( nFirstFloorID <= 0 )
  {
    FirstChildOfType = QTask_GetFirstChildOfType(
                         &ptLift->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask,
                         Floor_eQTaskType);
  }
  else
  {
    if ( nFirstFloorID >= 4096 || (v4 = Level_atLevelQTaskID[nFirstFloorID]) == nullptr )
    {
      FirstChildOfType = nullptr;
LABEL_7:
      v6 = nullptr;
      goto LABEL_8;
    }
    FirstChildOfType = (struct QTask_s *)v4->pxObject;
    if ( !FirstChildOfType )
      goto LABEL_7;
    v11 = Floor_eQTaskType;
    for ( i = QTask_GetPrevSiblingOfType((struct QTask_s *)v4->pxObject, Floor_eQTaskType);
          i;
          i = QTask_GetPrevSiblingOfType(i, v11) )
    {
      ++ptLift->nCurrentFloor;
    }
  }
  if ( !FirstChildOfType )
    goto LABEL_7;
  v6 = QTask_NewQTaskRef(FirstChildOfType);
LABEL_8:
  ptLift->ptActiveFloor = v6;
  ptLift->nFloorCache = ptLift->nCurrentFloor;
  if ( FirstChildOfType )
  {
    v7 = FirstChildOfType + 1;
    qmemcpy(&ptLift->tStartPos, &FirstChildOfType[1], sizeof(ptLift->tStartPos));
    p_ptMiddle = &FirstChildOfType[1].tQTaskRefList.ptMiddle;
    qmemcpy(&ptLift->tStartOrientation, p_ptMiddle, sizeof(ptLift->tStartOrientation));
    qmemcpy(&ptLift->tStopPos, v7, sizeof(ptLift->tStopPos));
    qmemcpy(&ptLift->tStopOrientation, p_ptMiddle, sizeof(ptLift->tStopOrientation));
    ptLift->vPos = 1.0;
  }
  Lift_UpdatePosition(ptLift);
  qmemcpy(
    &ptLift->tLastPosition,
    &ptLift->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos,
    sizeof(ptLift->tLastPosition));
  qmemcpy(&ptLift->tLastOrientation, &ptLift->tRigidDynCubeObj.tModelObj.tOrientation, sizeof(ptLift->tLastOrientation));
  Lift_tParameterReal32ContextPos.vMax = 1.0;
  ptLift->isStart = 0;
  ptLift->isStop = 0;
  ptLift->tRigidDynCubeObj.tModelObj.tAttachContext.iID = -1;
  ptLift->tRigidDynCubeObj.tModelObj.tAttachContext.iBone = 0;
  v9 = Attach_eAttachEvent;
  ptLift->isLastCanStart = 1;
  QTask_TriggerQTaskEventParent(
    &ptLift->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask,
    v9,
    &ptLift->tRigidDynCubeObj.tModelObj.tAttachContext);
  ModelObj_CalcRelativePosAndOrientation(&ptLift->tRigidDynCubeObj.tModelObj);
  RigidDynCubeObj_UpdateAttachments(&ptLift->tRigidDynCubeObj);
  return result;
}

// source: j/0/objects/lift.c:412  [anchor-caller]
void __cdecl Lift_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct World_s *ptDynCubeObj; };
    struct { float ptDynCubeObja; };
    struct { char igi2_o2[24]; struct real64x3_t tNull; };
    char igi2_extent[52];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v2; // st7
  double v3; // st7
  int *v4; // eax
  int v5; // eax
  double v6; // st6
  struct QReferenceList_s *p_tQTaskRefList; // eax
  int v8; // ecx
  __int16 v9; // cx

  igi2_frame.ptDynCubeObj = World_ptActiveWorld;
  memset(&igi2_frame.tNull, 0, sizeof(igi2_frame.tNull));
  ptQTask[8].ptNext = nullptr;
  ptQTask[15].tQTaskChildren.ptTail = nullptr;
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
    World_ptActiveWorld,
    (struct DynCubeObj_s *)ptQTask,
    &igi2_frame.tNull,
    igi2_frame.ptDynCubeObja,
    WORLD_DYNCUBETREE_CATEGORY_MOBILE);
  ptQTask[8].tQTaskChildren.ptHead = nullptr;
  ptQTask[8].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[8].tQTaskChildren.ptTail = nullptr;
  ptQTask[8].tQTaskRefList.ptHead = nullptr;
  ptQTask[8].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[8].tQTaskRefList.ptTail = nullptr;
  ptQTask[8].ptParent = nullptr;
  *(_DWORD *)&ptQTask[8].eQTaskType = 0;
  ptQTask[9].ptNext = nullptr;
  ptQTask[9].ptPrev = nullptr;
  ptQTask[9].tQTaskChildren.ptHead = nullptr;
  ptQTask[9].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[10].ptPrev = nullptr;
  ptQTask[10].tQTaskChildren.ptHead = nullptr;
  ptQTask[10].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[10].tQTaskRefList.ptHead = nullptr;
  ptQTask[10].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[10].tQTaskRefList.ptTail = nullptr;
  *(_DWORD *)&ptQTask[10].eQTaskType = 0;
  ptQTask[11].ptPrev = nullptr;
  ptQTask[11].tQTaskChildren.ptHead = nullptr;
  ptQTask[11].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[11].tQTaskRefList.ptHead = nullptr;
  ptQTask[11].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[11].tQTaskRefList.ptTail = nullptr;
  *(_DWORD *)&ptQTask[11].eQTaskType = 0;
  ptQTask[12].ptPrev = nullptr;
  ptQTask[12].tQTaskChildren.ptHead = nullptr;
  ptQTask[12].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[12].tQTaskRefList.ptHead = nullptr;
  ptQTask[12].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[12].tQTaskRefList.ptTail = nullptr;
  *(_DWORD *)&ptQTask[12].eQTaskType = 0;
  LOBYTE(ptQTask[14].eQTaskType) = 0;
  ptQTask[14].ptPrev = nullptr;
  ptQTask[14].ptNext = nullptr;
  ptQTask[14].tQTaskRefList.ptTail = (struct QReference_s *)1084227584;
  ptQTask[14].ptParent = (struct QTask_s *)1065185444;
  ptQTask[14].tQTaskChildren.ptHead = nullptr;
  ptQTask[10].ptNext = (struct QTask_s *)1065353216;
  ptQTask[10].tQTaskChildren.ptTail = (struct QTask_s *)1065353216;
  ptQTask[10].ptParent = (struct QTask_s *)1065353216;
  ptQTask[11].ptNext = (struct QTask_s *)1065353216;
  ptQTask[11].tQTaskChildren.ptTail = (struct QTask_s *)1065353216;
  ptQTask[11].ptParent = (struct QTask_s *)1065353216;
  ptQTask[12].ptNext = (struct QTask_s *)1065353216;
  ptQTask[12].tQTaskChildren.ptTail = (struct QTask_s *)1065353216;
  ptQTask[12].ptParent = (struct QTask_s *)1065353216;
  ptQTask[15].tQTaskRefList.ptHead = nullptr;
  ptQTask[15].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[15].tQTaskRefList.ptTail = nullptr;
  ptQTask[17].tQTaskChildren.ptTail = nullptr;
  ptQTask[17].tQTaskRefList.ptHead = nullptr;
  ptQTask[17].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[17].tQTaskRefList.ptTail = nullptr;
  ptQTask[19].tQTaskChildren.ptTail = nullptr;
  ptQTask[19].tQTaskRefList.ptHead = nullptr;
  ptQTask[19].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[19].tQTaskRefList.ptTail = nullptr;
  ptQTask[21].tQTaskChildren.ptTail = nullptr;
  qmemcpy(&ptQTask[9].tQTaskChildren.ptTail, &ptQTask[1], 0x18u);
  ptQTask[15].tQTaskChildren.ptMiddle = nullptr;
  qmemcpy(&ptQTask[13], &ptQTask[3].ptPrev, sizeof(struct QTask_s));
  LOBYTE(ptQTask[14].tQTaskChildren.ptMiddle) = 0;
  BYTE1(ptQTask[14].tQTaskChildren.ptMiddle) = 0;
  BYTE2(ptQTask[14].tQTaskChildren.ptMiddle) = 0;
  HIBYTE(ptQTask[14].tQTaskChildren.ptMiddle) = 0;
  LOBYTE(ptQTask[14].tQTaskRefList.ptMiddle) = 1;
  p_tQTaskRefList = &ptQTask[21].tQTaskRefList;
  v8 = 3;
  do
  {
    LOBYTE(p_tQTaskRefList->ptHead) = 0;
    p_tQTaskRefList = (struct QReferenceList_s *)((char *)p_tQTaskRefList + 32);
    --v8;
  }
  while ( v8 );
  v9 = Attach_eAttachEvent;
  ptQTask[5].tQTaskChildren.ptTail = (struct QTask_s *)-1;
  *(_DWORD *)&ptQTask[23].eQTaskType = 0;
  ptQTask[24].ptNext = (struct QTask_s *)-1;
  ptQTask[24].ptPrev = nullptr;
  ptQTask[14].tQTaskChildren.ptTail = nullptr;
  ptQTask[14].tQTaskRefList.ptHead = nullptr;
  ptQTask[5].tQTaskRefList.ptHead = nullptr;
  QTask_TriggerQTaskEventParent(ptQTask, v9, &ptQTask[5].tQTaskChildren.ptTail);
  ModelObj_CalcRelativePosAndOrientation((struct ModelObj_s *)ptQTask);
}

// source: j/0/objects/lift.c:509  [anchor-mhash]
void __cdecl Floor_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[1].ptNext = nullptr;
  ptQTask[1].ptPrev = nullptr;
  ptQTask[1].tQTaskChildren.ptHead = nullptr;
  ptQTask[1].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[1].tQTaskChildren.ptTail = nullptr;
  ptQTask[1].tQTaskRefList.ptHead = nullptr;
  ptQTask[1].tQTaskRefList.ptMiddle = (struct QReference_s *)1065353216;
  ptQTask[1].tQTaskRefList.ptTail = nullptr;
  ptQTask[1].ptParent = nullptr;
  *(_DWORD *)&ptQTask[1].eQTaskType = 0;
  ptQTask[2].ptNext = (struct QTask_s *)1065353216;
  ptQTask[2].ptPrev = nullptr;
  ptQTask[2].tQTaskChildren.ptHead = nullptr;
  ptQTask[2].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[2].tQTaskChildren.ptTail = (struct QTask_s *)1065353216;
  ptQTask[2].tQTaskRefList.ptHead = nullptr;
}

// source: j/0/objects/lift.c:574  [anchor-caller]
void __cdecl Lift_RunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *nTicks; // eax
  struct QTask_s *NextSiblingOfType; // ebx
  int v3; // edi
  struct QTask_s *ptHead; // ecx
  int v5; // edx
  struct QTask_s *v6; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v8; // edx
  struct QReference_s *v9; // edx
  unsigned __int16 v10; // cx
  struct QReference_s *ptNext; // eax
  char *pxObject; // edx
  char v13; // al
  char ptMiddle; // al
  bool v15; // cl
  bool v16; // al
  struct QReference_s **p_eQTaskType; // esi
  char *p_tQTaskRefList; // eax
  int v19; // eax
  struct QTask_s *v20; // eax
  __int64 isCanStart; // [esp+10h] [ebp-18h]
  enum bool isDown; // [esp+1Ch] [ebp-Ch]

  nTicks = (struct QTask_s *)Flow_ptFlow->nTicks;
  NextSiblingOfType = nullptr;
  v3 = 0;
  isDown = false;
  LODWORD(isCanStart) = 1;
  if ( ptQTask[24].ptNext == nTicks )
    return;
  ptHead = ptQTask->tQTaskChildren.ptHead;
  ptQTask[24].ptNext = nTicks;
  if ( ptHead->ptNext && ptHead )
  {
    v5 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v6 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v6 = nullptr;
      QTask_atProtectedQTaskStack[v5].ptQTask = v6;
      pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][ptHead->eQTaskType].pfHandler;
      v8 = v5 + 1;
      QTask_nProtectedQTaskStackOffset = v8;
      if ( pfHandler )
      {
        pfHandler(ptHead);
        v8 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v8];
      v5 = v8 - 1;
      QTask_nProtectedQTaskStackOffset = v5;
    }
    while ( ptHead );
  }
  if ( ptQTask[19].tQTaskRefList.ptHead
    && ptQTask[19].tQTaskRefList.ptMiddle->ptNext
    && ptQTask[19].tQTaskRefList.ptTail )
  {
    isCanStart = (__int64)Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[19].tQTaskRefList, ptQTask);
  }
  if ( ptQTask[15].tQTaskRefList.ptHead
    && ptQTask[15].tQTaskRefList.ptMiddle->ptNext
    && ptQTask[15].tQTaskRefList.ptTail )
  {
    v3 = (__int64)Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[15].tQTaskRefList, ptQTask);
  }
  if ( ptQTask[17].tQTaskRefList.ptHead
    && ptQTask[17].tQTaskRefList.ptMiddle->ptNext
    && ptQTask[17].tQTaskRefList.ptTail )
  {
    isDown = (unsigned int)(__int64)Level_RunLevelExpression(
                                      (struct LevelExpression_s *)&ptQTask[17].tQTaskRefList,
                                      ptQTask);
  }
  if ( !BYTE1(ptQTask[14].tQTaskChildren.ptMiddle) )
  {
    v9 = ptQTask[14].tQTaskRefList.ptHead;
    v10 = Floor_eQTaskType;
    ptQTask[14].tQTaskChildren.ptTail = (struct QTask_s *)v9;
    if ( v3 )
    {
      NextSiblingOfType = QTask_GetNextSiblingOfType(ptQTask[8].ptNext->tQTaskChildren.ptHead, v10);
      if ( NextSiblingOfType )
        ptQTask[14].tQTaskRefList.ptHead = (struct QReference_s *)((char *)&v9->ptNext + 1);
    }
    if ( isDown )
    {
      NextSiblingOfType = QTask_GetPrevSiblingOfType(ptQTask[8].ptNext->tQTaskChildren.ptHead, v10);
      if ( !NextSiblingOfType )
        goto LABEL_32;
      --*(int *)&ptQTask[14].tQTaskRefList.ptHead;
    }
    if ( NextSiblingOfType )
    {
      ptNext = (struct QReference_s *)ptQTask[8].ptNext;
      pxObject = (char *)ptNext->pxObject;
      qmemcpy(&ptQTask[8].tQTaskChildren, pxObject + 40, 0x18u);
      qmemcpy(&ptQTask[11], pxObject + 64, sizeof(struct QTask_s));
      QReference_Delete(ptNext, &QTask_tQTaskRefPool);
      ptQTask[8].ptNext = (struct QTask_s *)QTask_NewQTaskRef(NextSiblingOfType);
      qmemcpy(&ptQTask[8].ptParent, &NextSiblingOfType[1], 0x18u);
      qmemcpy(&ptQTask[12], &NextSiblingOfType[1].tQTaskRefList.ptMiddle, sizeof(struct QTask_s));
      ptQTask[14].ptPrev = nullptr;
    }
  }
LABEL_32:
  v13 = BYTE1(ptQTask[14].tQTaskChildren.ptMiddle);
  qmemcpy(&ptQTask[9].tQTaskChildren.ptTail, &ptQTask[1], 0x18u);
  LOBYTE(ptQTask[14].tQTaskChildren.ptMiddle) = v13;
  qmemcpy(&ptQTask[13], &ptQTask[3].ptPrev, sizeof(struct QTask_s));
  if ( (_DWORD)isCanStart )
    BYTE1(ptQTask[14].tQTaskChildren.ptMiddle) = Lift_Move((struct Lift_s *)ptQTask);
  else
    BYTE1(ptQTask[14].tQTaskChildren.ptMiddle) = 0;
  ptMiddle = (char)ptQTask[14].tQTaskChildren.ptMiddle;
  v15 = ptMiddle && !BYTE1(ptQTask[14].tQTaskChildren.ptMiddle);
  HIBYTE(ptQTask[14].tQTaskChildren.ptMiddle) = v15;
  v16 = !ptMiddle && BYTE1(ptQTask[14].tQTaskChildren.ptMiddle);
  BYTE2(ptQTask[14].tQTaskChildren.ptMiddle) = v16;
  if ( v16 )
  {
    p_eQTaskType = (struct QReference_s **)&ptQTask[23].eQTaskType;
    QTask_DeleteQTaskAndQTaskRefSafe((struct QReference_s **)&ptQTask[23].eQTaskType);
    p_tQTaskRefList = (char *)&ptQTask[21].tQTaskRefList;
LABEL_51:
    v20 = SoundSys_NewSoundFn(ptQTask, p_tQTaskRefList);
    *p_eQTaskType = QTask_NewQTaskRef(v20);
    goto LABEL_52;
  }
  if ( BYTE1(ptQTask[14].tQTaskChildren.ptMiddle) )
  {
    v19 = *(_DWORD *)&ptQTask[23].eQTaskType;
    p_eQTaskType = (struct QReference_s **)&ptQTask[23].eQTaskType;
    if ( !v19 || !*(_DWORD *)(v19 + 8) )
    {
      QTask_DeleteQTaskAndQTaskRefSafe(p_eQTaskType);
      p_tQTaskRefList = (char *)&ptQTask[23].ptPrev;
      goto LABEL_51;
    }
  }
  else if ( v15 )
  {
    p_eQTaskType = (struct QReference_s **)&ptQTask[23].eQTaskType;
    QTask_DeleteQTaskAndQTaskRefSafe((struct QReference_s **)&ptQTask[23].eQTaskType);
    p_tQTaskRefList = (char *)&ptQTask[22].tQTaskChildren.ptMiddle;
    goto LABEL_51;
  }
LABEL_52:
  if ( *(float *)&ptQTask[14].ptPrev == 0.0
    && !BYTE1(ptQTask[14].tQTaskChildren.ptMiddle)
    && (_DWORD)isCanStart == SLOBYTE(ptQTask[14].tQTaskRefList.ptMiddle) )
  {
    ++*(int *)&ptQTask[14].tQTaskChildren.ptHead;
    LOBYTE(ptQTask[14].tQTaskRefList.ptMiddle) = isCanStart;
  }
  else
  {
    ptQTask[14].tQTaskChildren.ptHead = nullptr;
    LOBYTE(ptQTask[14].tQTaskRefList.ptMiddle) = isCanStart;
  }
}

// source: j/0/objects/lift.c:777  [size]
void __cdecl Lift_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptNext; // eax
  int v2; // eax
  struct QReference_s *v3; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *); // eax

  ptNext = ptQTask[8].ptNext;
  if ( ptNext )
  {
    QReference_Delete((struct QReference_s *)ptNext, &QTask_tQTaskRefPool);
    ptQTask[8].ptNext = nullptr;
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
  QTask_DeleteQTaskAndQTaskRefSafe((struct QReference_s **)&ptQTask[23].eQTaskType);
  v2 = 0;
  while ( 1 )
  {
    v3 = Level_atLevelQTaskID[v2];
    if ( v3 )
    {
      if ( v3->pxObject == ptQTask )
        break;
    }
    if ( ++v2 >= 4096 )
      goto LABEL_13;
  }
  if ( v2 >= 0 )
  {
    pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Level_eRemoveLevelScriptSymbolsEvent][ptQTask->eQTaskType].pfHandler;
    if ( pfHandler )
      pfHandler(ptQTask);
  }
LABEL_13:
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[17].tQTaskRefList);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[15].tQTaskRefList);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[19].tQTaskRefList);
  World_RemoveDynCubeObj((struct World_s *)ptQTask[2].ptParent, (struct DynCubeObj_s *)ptQTask);
}

// source: j/0/objects/lift.c:817  [size]
void __cdecl Floor_DeleteHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: j/0/objects/lift.c:841  [size]
void __cdecl Lift_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = Lift_ptParameterList;
}

// source: j/0/objects/lift.c:857  [size]
void __cdecl Floor_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = Floor_ptParameterList;
}

// source: j/0/objects/lift.c:874  [anchor-mhash]
void __cdecl Lift_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct LODVirModel_s *LODVirModelExistsFn; // eax

  LODVirModelExistsFn = MTP_GetLODVirModelExistsFn((char *)&ptQTask[14].eQTaskType);
  if ( LODVirModelExistsFn != *(struct LODVirModel_s **)&ptQTask[2].eQTaskType )
  {
    ModelObj_SetLODVirModel((struct ModelObj_s *)ptQTask, LODVirModelExistsFn, false);
    ptQTask[7].tQTaskRefList.ptHead = nullptr;
    ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
    ptQTask[7].tQTaskRefList.ptTail = nullptr;
    ptQTask[7].ptParent = nullptr;
    *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  }
  ptQTask[14].tQTaskChildren.ptHead = nullptr;
  ptQTask[14].ptNext = nullptr;
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[17].tQTaskRefList, ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[15].tQTaskRefList, ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[19].tQTaskRefList, ptQTask);
  Lift_SetPositionToFirstFloor((struct Lift_s *)ptQTask);
}

// source: j/0/objects/lift.c:931  [anchor-mhash]
void __cdecl Floor_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *FirstParentOfType; // eax

  FirstParentOfType = QTask_GetFirstParentOfType(ptQTask, Lift_eQTaskType);
  if ( FirstParentOfType )
    ((void (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][FirstParentOfType->eQTaskType].pfHandler)(
      FirstParentOfType,
      0);
}

// source: j/0/objects/lift.c:997  [anchor-refs]
void __cdecl Lift_RegisterScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( !ptQTask[15].tQTaskChildren.ptMiddle )
  {
    ptQTask[15].tQTaskChildren.ptMiddle = (struct QTask_s *)1;
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.nInactive", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int,
      &ptQTask[14].tQTaskChildren,
      4,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.nCurrentFloor", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int,
      &ptQTask[14].tQTaskChildren.ptTail,
      4,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.isMoving", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      (char *)&ptQTask[14].tQTaskChildren.ptMiddle + 1,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.isStart", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      (char *)&ptQTask[14].tQTaskChildren.ptMiddle + 2,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.isStop", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      (char *)&ptQTask[14].tQTaskChildren.ptMiddle + 3,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
  }
}

// source: j/0/objects/lift.c:1039  [anchor-mhash]
void __cdecl Lift_RemoveScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( ptQTask[15].tQTaskChildren.ptMiddle )
  {
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    ptQTask[15].tQTaskChildren.ptMiddle = nullptr;
    sprintf(igi2_frame.zTemp, "%s.nInactive", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.nCurrentFloor", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.isMoving", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.isStart", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.isStop", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    ptQTask[15].tQTaskChildren.ptMiddle = nullptr;
  }
}

// source: j/0/objects/lift.c:1085  [size]
void __cdecl Lift_EnterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ((void (__cdecl *)())QTask_aatQTaskFinalEvent[5][RigidDynCubeObj_eQTaskType].pfHandler)(ptQTask, pxContext);
}

// source: j/0/objects/lift.c:1107  [anchor-mhash]
void __cdecl Lift_UpdateAttachmentHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // eax
  int v2; // edx
  struct QTask_s *v3; // ecx
  int eQTaskType; // ecx

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
      eQTaskType = ptHead->eQTaskType;
      QTask_nProtectedQTaskStackOffset = v2 + 1;
      ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Attach_eUpdateAttachmentEvent][eQTaskType].pfHandler)(ptHead);
      ptHead = (struct QTask_s *)dword_849C7DC[QTask_nProtectedQTaskStackOffset];
      v2 = --QTask_nProtectedQTaskStackOffset;
    }
    while ( ptHead );
  }
  Lift_UpdatePosition((struct Lift_s *)ptQTask);
}

// source: j/0/objects/lift.c:1309  [anchor-strings]
void __cdecl Lift_Open()
{
  unsigned __int16 v0; // ax
  __int16 v1; // bx
  unsigned __int16 v2; // si
  unsigned __int16 v3; // di
  __int16 v4; // bx
  __int16 v5; // bp
  struct ParameterList_s *v6; // eax
  unsigned int v7; // edi
  char **v8; // esi
  struct ParameterList_s *v9; // eax
  int v10; // edx
  unsigned __int16 v11; // si
  struct ParameterList_s *v12; // ebx
  int v13; // esi
  struct ParameterList_s *v14; // eax
  int v15; // edx

  Lift_eQTaskType = QTask_NewQTaskType("Lift", 968, RigidDynCubeObj_eQTaskType, 0, 0);
  v0 = QTask_NewQTaskType("Floor", 112, EditorRigidObj_eQTaskType, 0, 0);
  v1 = Level_eAllowSaveQTaskEvent;
  v2 = Lift_eQTaskType;
  v3 = v0;
  Floor_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    Lift_eQTaskType,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v3, v1, (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v2, 0, Lift_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, 1, Lift_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, 2, Lift_DeleteHandler);
  v4 = ParameterList_eGetParameterListQTaskEvent;
  QTask_LinkQTaskEventHandlerFn(
    v2,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Lift_GetParameterListHandler);
  v5 = ParameterList_eUpdateInternalDataQTaskEvent;
  QTask_LinkQTaskEventHandlerFn(v2, ParameterList_eUpdateInternalDataQTaskEvent, Lift_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, Level_eRegisterLevelScriptSymbolsEvent, Lift_RegisterScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, Level_eRemoveLevelScriptSymbolsEvent, Lift_RemoveScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, Attach_eUpdateAttachmentEvent, Lift_UpdateAttachmentHandler);
  QTask_LinkQTaskEventHandlerFn(v2, 5, (void (__cdecl *)(struct QTask_s *, void *))Lift_EnterHandler);
  QTask_LinkQTaskEventHandlerFn(v3, 0, Floor_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v3, 2, (void (__cdecl *)(struct QTask_s *))Floor_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v3, v4, (void (__cdecl *)(struct QTask_s *, void *))Floor_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v3, v5, Floor_UpdateInternalDataHandler);
  Lift_tParameterReal32ContextPos.vMin = 0.0;
  Lift_tParameterReal32ContextPos.vMax = 10000000.0;
  Lift_tParameterReal32ContextMaxSpeed.vMin = 0.0;
  Lift_tParameterReal32ContextMaxSpeed.vMax = 10000.0;
  Lift_tParameterReal32ContextInertia.vMin = 0.0;
  Lift_tParameterReal32ContextInertia.vMax = 1.0;
  v6 = (struct ParameterList_s *)Mem_AllocFn(252, 4);
  v6->nParameters = 0;
  v6->nMaxParameters = 12;
  v6->ptParameterListItem = (struct ParameterListItem_s *)&v6[1];
  Lift_ptParameterList = v6;
  ParameterList_AddParameter(v6, 0x254u, Level_eParameterTypeString16, "Model", 7u, nullptr);
  ParameterList_AddParameter(
    Lift_ptParameterList,
    0x3C4u,
    Level_eParameterTypeInt32,
    "Start floor task ID",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Lift_ptParameterList,
    0x24Cu,
    Level_eParameterTypeReal32,
    "Max speed",
    7u,
    &Lift_tParameterReal32ContextMaxSpeed);
  ParameterList_AddParameter(
    Lift_ptParameterList,
    0x250u,
    Level_eParameterTypeReal32,
    "Speed inertia",
    7u,
    &Lift_tParameterReal32ContextInertia);
  ParameterList_AddParameter(Lift_ptParameterList, 0x2BCu, Level_eParameterTypeVarString, "Floor down", 7u, nullptr);
  ParameterList_AddParameter(Lift_ptParameterList, 0x26Cu, Level_eParameterTypeVarString, "Floor up", 7u, nullptr);
  ParameterList_AddParameter(Lift_ptParameterList, 0x30Cu, Level_eParameterTypeVarString, "Can start", 7u, nullptr);
  v7 = 860;
  v8 = (char **)off_6B9678;
  do
  {
    ParameterList_AddParameter(Lift_ptParameterList, v7, Level_eParameterTypeString32, *v8++, 7u, nullptr);
    v7 += 32;
  }
  while ( (int)v8 < 7050884 );
  ParameterList_AddParameter(Lift_ptParameterList, 0x148u, Level_eParameterTypeObjectPos, "Start Position", 1u, nullptr);
  ParameterList_AddParameter(
    Lift_ptParameterList,
    0x1B8u,
    Level_eParameterTypeReal32x9,
    "Start Orientation",
    1u,
    nullptr);
  v9 = (struct ParameterList_s *)Mem_AllocFn(52, 4);
  v9->ptParameterListItem = (struct ParameterListItem_s *)&v9[1];
  v10 = Level_eParameterTypeObjectPos;
  v9->nParameters = 0;
  v9->nMaxParameters = 2;
  Floor_ptParameterList = v9;
  ParameterList_AddParameter(v9, 0x28u, v10, "Position", 7u, nullptr);
  ParameterList_AddParameter(Floor_ptParameterList, 0x40u, Level_eParameterTypeReal32x9, "Orientation", 7u, nullptr);
  v11 = Lift_eQTaskType;
  QTask_LinkQTaskEventHandlerFn(
    Lift_eQTaskType,
    Serialize_eGetSerializeParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Lift_GetSerializeParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v11, Serialize_eDeSerializeQTaskEvent, Lift_DeSerializeHandler);
  v12 = ModelObjParameters_ptSerializeParameterList;
  v13 = ModelObjParameters_ptSerializeParameterList->nParameters + 18;
  v14 = (struct ParameterList_s *)Mem_AllocFn(20 * v13 + 12, 4);
  v14->nParameters = 0;
  v14->nMaxParameters = v13;
  v14->ptParameterListItem = (struct ParameterListItem_s *)&v14[1];
  qmemcpy(&v14[1], v12->ptParameterListItem, 20 * v12->nParameters);
  v15 = SerializeQTaskRef_eParameterType;
  v14->nParameters = v12->nParameters;
  Lift_ptSerializeParameterList = v14;
  ParameterList_AddParameter(v14, 0x140u, v15, "ptActiveFloor", 7u, nullptr);
  ParameterList_AddParameter(
    Lift_ptSerializeParameterList,
    0x148u,
    Level_eParameterTypeObjectPos,
    "tStartPos",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Lift_ptSerializeParameterList,
    0x160u,
    Level_eParameterTypeObjectPos,
    "tStopPos",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Lift_ptSerializeParameterList,
    0x178u,
    Level_eParameterTypeObjectPos,
    "tLastPosition",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Lift_ptSerializeParameterList,
    0x190u,
    Level_eParameterTypeReal32x9,
    "tOriginalOrientation",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Lift_ptSerializeParameterList,
    0x1B8u,
    Level_eParameterTypeReal32x9,
    "tStartOrientation",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Lift_ptSerializeParameterList,
    0x1E0u,
    Level_eParameterTypeReal32x9,
    "tStopOrientation",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Lift_ptSerializeParameterList,
    0x208u,
    Level_eParameterTypeReal32x9,
    "tLastOrientation",
    7u,
    nullptr);
  ParameterList_AddParameter(Lift_ptSerializeParameterList, 0x230u, Level_eParameterTypeReal32, "vSpeed", 7u, nullptr);
  ParameterList_AddParameter(Lift_ptSerializeParameterList, 0x234u, Level_eParameterTypeReal32, "vPos", 7u, nullptr);
  ParameterList_AddParameter(Lift_ptSerializeParameterList, 0x238u, Level_eParameterTypeInt32, "nInactive", 7u, nullptr);
  ParameterList_AddParameter(
    Lift_ptSerializeParameterList,
    0x23Cu,
    Level_eParameterTypebool8,
    "isMovingLastFrame",
    7u,
    nullptr);
  ParameterList_AddParameter(Lift_ptSerializeParameterList, 0x23Du, Level_eParameterTypebool8, "isMoving", 7u, nullptr);
  ParameterList_AddParameter(Lift_ptSerializeParameterList, 0x23Eu, Level_eParameterTypebool8, "isStart", 7u, nullptr);
  ParameterList_AddParameter(Lift_ptSerializeParameterList, 0x23Fu, Level_eParameterTypebool8, "isStop", 7u, nullptr);
  ParameterList_AddParameter(
    Lift_ptSerializeParameterList,
    0x240u,
    Level_eParameterTypeInt32,
    "nCurrentFloor",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Lift_ptSerializeParameterList,
    0x244u,
    Level_eParameterTypeInt32,
    "nFloorCache",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Lift_ptSerializeParameterList,
    0x248u,
    Level_eParameterTypebool8,
    "isLastCanStart",
    7u,
    nullptr);
}

// source: j/0/objects/lift.c:1425  [size]
void __cdecl Lift_Close()
{
  int v0; // esi
  int v1; // esi
  int v2; // esi

  if ( Lift_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&Lift_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  if ( Lift_ptSerializeParameterList )
  {
    v1 = *(_DWORD *)((unsigned int)&Lift_ptSerializeParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
  if ( Floor_ptParameterList )
  {
    v2 = *(_DWORD *)((unsigned int)&Floor_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v2);
    memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
    free((void *)v2);
  }
  QTask_DeleteQTaskType(Lift_eQTaskType);
  QTask_DeleteQTaskType(Floor_eQTaskType);
}

// source: j/0/objects/lift.c:1445  [size]
unsigned __int16 __cdecl Lift_GetQTaskType()
{
  return Lift_eQTaskType;
}
