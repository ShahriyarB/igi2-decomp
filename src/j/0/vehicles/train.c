/* j/0/vehicles/train.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/vehicles/train.c:143  [size]
void __cdecl Train_GetSerializeParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = Train_ptSerializeParameterList;
}

// source: j/0/vehicles/train.c:161  [anchor-mhash]
void __cdecl Train_DeSerializeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // eax

  QTask_DeleteQTaskAndQTaskRefSafe(&ptQTask[56].tQTaskRefList.ptMiddle);
  v2 = Vehicle_eQTaskType + 511 * Serialize_eDeSerializeQTaskEvent;
  ptQTask[56].tQTaskRefList.ptHead = (struct QReference_s *)-1;
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][v2].pfHandler)(ptQTask, pxContext);
}

// source: j/0/vehicles/train.c:187  [anchor-mhash]
enum bool __cdecl Train_GetPositions(struct Train_t *ptTrain, struct real64x3_t *patPos)
{
  #pragma pack(push, 1)
  union
  {
    struct { char isValid; };
    struct { char igi2_o1[1]; float avDistance[22]; };
    char igi2_extent[89];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  unsigned __int16 v2; // dx
  struct QTask_s *FirstChildOfType; // eax
  enum bool isFlipDirection; // ebx
  float *v5; // esi
  double v6; // st7

  v2 = Train_eQTaskType;
  FirstChildOfType = QTask_GetFirstChildOfType(
                       &ptTrain->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask,
                       Train_eQTaskType);
  isFlipDirection = ptTrain->isFlipDirection;
  if ( isFlipDirection )
    igi2_frame.avDistance[0] = ptTrain->vLength;
  else
    igi2_frame.avDistance[0] = -ptTrain->vLength;
  if ( FirstChildOfType )
  {
    v5 = igi2_frame.avDistance;
    do
    {
      v6 = *(float *)&FirstChildOfType[48].tQTaskRefList.ptTail;
      ++v5;
      if ( isFlipDirection == false )
        v6 = -v6;
      *v5 = v6;
      FirstChildOfType = QTask_GetNextSiblingOfType(FirstChildOfType, v2);
    }
    while ( FirstChildOfType );
  }
  SplineObj_GetPosAndMatrix(
    ptTrain->nSplineObjQTaskID,
    nullptr,
    patPos,
    &igi2_frame.isValid,
    ptTrain->vPos,
    ptTrain->nNumCarriages + 1,
    igi2_frame.avDistance,
    nullptr);
  return igi2_frame.isValid;
}

// source: j/0/vehicles/train.c:239  [anchor-callee]
int __cdecl Train_MoveCarriage(
        struct Train_t *ptCarriage,
        struct real64x3_t *patPos,
        int iCarriage)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[24]; float tY; };
    struct { char igi2_o2[28]; float tY_4; };
    struct { char igi2_o3[36]; float tDirection; };
    struct { char igi2_o4[36]; float tDirectiona; };
    struct { char igi2_o5[40]; float tDirection_4; };
    struct { char igi2_o6[40]; float tDirection_4a; };
    struct { char igi2_o7[44]; float tDirection_8; };
    struct { char igi2_o8[48]; float tTemp_; };
    struct { char igi2_o9[48]; float tTemp_a; };
    struct { char igi2_o10[52]; float tTemp__4; };
    struct { char igi2_o11[52]; float tTemp__4a; };
    struct { char igi2_o12[56]; float tTemp__8; };
    struct { char igi2_o13[56]; float tTemp__8a; };
    struct { char igi2_o14[60]; struct real64x3_t tPos; };
    struct { char igi2_o15[88]; struct real32x3_t tDisplacement; };
    char igi2_extent[104];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v4; // st7
  struct real64x3_t *v5; // edx
  double v6; // st7
  struct real32x9_t *p_tOrientation; // ebp
  long double v8; // st4
  long double v9; // st7
  long double v10; // st3
  long double v11; // st6
  long double v12; // st2
  long double v13; // st5
  float v14; // ecx
  float v15; // eax
  double vZ; // st7
  double v17; // st6
  double v18; // st5
  double vY; // st7
  double vX; // st7
  struct LODVirModel_s *ptLODVirModel; // eax
  struct VirModel_s *v22; // eax
  double vRadius; // st6
  int result; // eax
  struct QTask_s *ptHead; // ecx
  struct QTask_s *v26; // edx
  int v27; // esi
  void (__cdecl *pfHandler)(struct QTask_s *, _DWORD); // edx
  int v29; // eax
  struct QTask_s *ptMagicObjContainer; // ebx
  int v31; // ecx
  struct QTask_s *v32; // edx
  int v33; // esi
  void (__cdecl *v34)(int, _DWORD); // edx
  int v35; // eax

  v4 = ptCarriage->vDisplacementX * 4096.0;
  v5 = &patPos[iCarriage];
  igi2_frame.tDisplacement.vX = v4;
  v6 = ptCarriage->vDisplacementZ * 4096.0;
  qmemcpy(
    &ptCarriage->tVehicle.tPhysicsObj.tLastPosition,
    &ptCarriage->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos,
    sizeof(ptCarriage->tVehicle.tPhysicsObj.tLastPosition));
  igi2_frame.tDisplacement.vZ = v6;
  p_tOrientation = &ptCarriage->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation;
  qmemcpy(
    &ptCarriage->tVehicle.tPhysicsObj.tLastOrientation,
    &ptCarriage->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation,
    sizeof(ptCarriage->tVehicle.tPhysicsObj.tLastOrientation));
  if ( v5->vX == v5[1].vX && v5->vY == v5[1].vY && v5->vZ == v5[1].vZ )
  {
    p_tOrientation->tX.vX = 1.0;
    ptCarriage->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vY = 1.0;
    ptCarriage->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vZ = 1.0;
    ptCarriage->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vY = 0.0;
    ptCarriage->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vZ = 0.0;
    ptCarriage->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vX = 0.0;
    ptCarriage->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vZ = 0.0;
    ptCarriage->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vX = 0.0;
    ptCarriage->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vY = 0.0;
    ptCarriage->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.nOps = 0;
    qmemcpy(&igi2_frame.tPos, v5, sizeof(igi2_frame.tPos));
    vZ = igi2_frame.tPos.vZ;
  }
  else
  {
    igi2_frame.tDirection = v5->vX - v5[1].vX;
    igi2_frame.tY = igi2_frame.tDirection;
    igi2_frame.tDirection_4 = v5->vY - v5[1].vY;
    igi2_frame.tY_4 = igi2_frame.tDirection_4;
    igi2_frame.tDirection_8 = v5->vZ - v5[1].vZ;
    if ( igi2_frame.tDirection == 0.0 && igi2_frame.tDirection_4 == 0.0 && igi2_frame.tDirection_8 == 0.0 )
    {
      v9 = igi2_frame.tDirection_8;
    }
    else
    {
      v8 = sqrt(igi2_frame.tDirection * igi2_frame.tDirection + igi2_frame.tDirection_4 * igi2_frame.tDirection_4 + igi2_frame.tDirection_8 * igi2_frame.tDirection_8);
      igi2_frame.tY = igi2_frame.tDirection * (1.0 / v8);
      igi2_frame.tY_4 = igi2_frame.tDirection_4 * (1.0 / v8);
      v9 = 1.0 / v8 * igi2_frame.tDirection_8;
    }
    igi2_frame.tTemp_ = igi2_frame.tY_4 - 0.0 * v9;
    igi2_frame.tDirectiona = igi2_frame.tTemp_;
    igi2_frame.tTemp__4 = -(igi2_frame.tY - 0.0 * v9);
    igi2_frame.tDirection_4a = igi2_frame.tTemp__4;
    igi2_frame.tTemp__8 = igi2_frame.tY * 0.0 - igi2_frame.tY_4 * 0.0;
    if ( igi2_frame.tTemp_ == 0.0 && igi2_frame.tTemp__4 == 0.0 && igi2_frame.tTemp__8 == 0.0 )
    {
      v11 = igi2_frame.tTemp__8;
    }
    else
    {
      v10 = sqrt(igi2_frame.tTemp_ * igi2_frame.tTemp_ + igi2_frame.tTemp__4 * igi2_frame.tTemp__4 + igi2_frame.tTemp__8 * igi2_frame.tTemp__8);
      igi2_frame.tDirectiona = igi2_frame.tTemp_ * (1.0 / v10);
      igi2_frame.tDirection_4a = igi2_frame.tTemp__4 * (1.0 / v10);
      v11 = 1.0 / v10 * igi2_frame.tTemp__8;
    }
    igi2_frame.tTemp_a = igi2_frame.tDirection_4a * v9 - v11 * igi2_frame.tY_4;
    *(float *)&igi2_frame.tPos.vX = igi2_frame.tTemp_a;
    igi2_frame.tTemp__4a = -(igi2_frame.tDirectiona * v9 - v11 * igi2_frame.tY);
    *((float *)&igi2_frame.tPos.vX + 1) = igi2_frame.tTemp__4a;
    igi2_frame.tTemp__8a = igi2_frame.tDirectiona * igi2_frame.tY_4 - igi2_frame.tDirection_4a * igi2_frame.tY;
    *(float *)&igi2_frame.tPos.vY = igi2_frame.tTemp__8a;
    if ( igi2_frame.tTemp_a == 0.0 && igi2_frame.tTemp__4a == 0.0 && igi2_frame.tTemp__8a == 0.0 )
    {
      v13 = *(float *)&igi2_frame.tPos.vY;
    }
    else
    {
      v12 = sqrt(igi2_frame.tTemp_a * igi2_frame.tTemp_a + igi2_frame.tTemp__4a * igi2_frame.tTemp__4a + igi2_frame.tTemp__8a * igi2_frame.tTemp__8a);
      *(float *)&igi2_frame.tPos.vX = igi2_frame.tTemp_a * (1.0 / v12);
      *((float *)&igi2_frame.tPos.vX + 1) = *((float *)&igi2_frame.tPos.vX + 1) * (1.0 / v12);
      v13 = 1.0 / v12 * *(float *)&igi2_frame.tPos.vY;
    }
    ptCarriage->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vX = v11;
    p_tOrientation->tX.vX = igi2_frame.tDirectiona;
    ptCarriage->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vY = v9;
    ptCarriage->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vX = igi2_frame.tDirection_4a;
    ptCarriage->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vZ = v13;
    ptCarriage->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vY = igi2_frame.tY;
    v14 = *(float *)&igi2_frame.tPos.vX;
    ptCarriage->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vY = igi2_frame.tY_4;
    v15 = *((float *)&igi2_frame.tPos.vX + 1);
    ptCarriage->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vZ = v14;
    ptCarriage->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vZ = v15;
    igi2_frame.tPos.vX = (v5[1].vX - v5->vX) * ptCarriage->vCenter + v5->vX;
    igi2_frame.tPos.vY = (v5[1].vY - v5->vY) * ptCarriage->vCenter + v5->vY;
    vZ = (v5[1].vZ - v5->vZ) * ptCarriage->vCenter + v5->vZ;
  }
  v17 = igi2_frame.tDisplacement.vZ * ptCarriage->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vZ
      + igi2_frame.tDisplacement.vX * p_tOrientation->tX.vX
      + ptCarriage->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vY * 0.0;
  v18 = igi2_frame.tDisplacement.vZ * ptCarriage->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vZ
      + igi2_frame.tDisplacement.vX * ptCarriage->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vX
      + ptCarriage->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vY * 0.0;
  igi2_frame.tDisplacement.vZ = igi2_frame.tDisplacement.vZ * ptCarriage->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vZ
                   + igi2_frame.tDisplacement.vX * ptCarriage->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vX
                   + ptCarriage->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vY * 0.0;
  igi2_frame.tPos.vX = v17 + igi2_frame.tPos.vX;
  igi2_frame.tPos.vY = v18 + igi2_frame.tPos.vY;
  igi2_frame.tPos.vZ = igi2_frame.tDisplacement.vZ + vZ;
  if ( ptCarriage->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tScale.vY <= (double)ptCarriage->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tScale.vZ )
    vY = ptCarriage->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tScale.vZ;
  else
    vY = ptCarriage->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tScale.vY;
  if ( vY >= ptCarriage->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tScale.vX )
  {
    if ( ptCarriage->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tScale.vY <= (double)ptCarriage->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tScale.vZ )
      vX = ptCarriage->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tScale.vZ;
    else
      vX = ptCarriage->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tScale.vY;
  }
  else
  {
    vX = ptCarriage->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tScale.vX;
  }
  ptLODVirModel = ptCarriage->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.ptLODVirModel;
  if ( ptLODVirModel && (v22 = ptLODVirModel->aptVirModel[0]) != nullptr )
    vRadius = v22->ptModel->ptMesh->vRadius;
  else
    vRadius = 1.0;
  igi2_frame.ptDynCubeObj = vX * vRadius;
  World_MoveDynCubeObjRadius(
    Game_ptGame->ptWorld,
    &ptCarriage->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj,
    &igi2_frame.tPos,
    igi2_frame.ptDynCubeObj);
  if ( ptCarriage->isValidPosition )
  {
    RigidDynCubeObj_UpdateAttachments(&ptCarriage->tVehicle.tPhysicsObj.tRigidDynCubeObj);
  }
  else
  {
    ptHead = ptCarriage->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.tQTaskChildren.ptHead;
    ptCarriage->isValidPosition = true;
    if ( ptHead->ptNext && ptHead )
    {
      result = QTask_nProtectedQTaskStackOffset;
      do
      {
        if ( ptHead->ptNext )
          v26 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
        else
          v26 = nullptr;
        v27 = ParameterList_eUpdateInternalDataQTaskEvent;
        QTask_atProtectedQTaskStack[result].ptQTask = v26;
        pfHandler = (void (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[v27][ptHead->eQTaskType].pfHandler;
        v29 = result + 1;
        QTask_nProtectedQTaskStackOffset = v29;
        if ( pfHandler )
        {
          pfHandler(ptHead, 0);
          v29 = QTask_nProtectedQTaskStackOffset;
        }
        ptHead = (struct QTask_s *)dword_849C7DC[v29];
        result = v29 - 1;
        QTask_nProtectedQTaskStackOffset = result;
      }
      while ( ptHead );
    }
    else
    {
      result = QTask_nProtectedQTaskStackOffset;
    }
    ptMagicObjContainer = ptCarriage->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.ptMagicObjContainer;
    if ( ptMagicObjContainer )
    {
      v31 = (int)ptMagicObjContainer->tQTaskChildren.ptHead;
      if ( *(_DWORD *)v31 )
      {
        for ( ; v31; QTask_nProtectedQTaskStackOffset = result )
        {
          if ( *(_DWORD *)v31 )
            v32 = **(_DWORD **)v31 != 0 ? *(struct QTask_s **)v31 : nullptr;
          else
            v32 = nullptr;
          v33 = ParameterList_eUpdateInternalDataQTaskEvent;
          QTask_atProtectedQTaskStack[result].ptQTask = v32;
          v34 = (void (__cdecl *)(int, _DWORD))QTask_aatQTaskFinalEvent[v33][*(unsigned __int16 *)(v31 + 36)].pfHandler;
          v35 = result + 1;
          QTask_nProtectedQTaskStackOffset = v35;
          if ( v34 )
          {
            v34(v31, 0);
            v35 = QTask_nProtectedQTaskStackOffset;
          }
          v31 = dword_849C7DC[v35];
          result = v35 - 1;
        }
      }
    }
  }
  return result;
}

// source: j/0/vehicles/train.c:328  [anchor-mhash]
struct Train_t *__cdecl Train_Move(struct Train_t *ptTrain)
{
  struct QTask_s *FirstChildOfType; // eax
  enum bool isValidPosition; // ebx
  struct Train_t *v4; // esi
  struct Train_t *result; // eax
  int v6; // edi
  BOOL v7; // eax
  struct real64x3_t atPos[22]; // [esp+10h] [ebp-214h] BYREF

  FirstChildOfType = QTask_GetFirstChildOfType(
                       &ptTrain->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask,
                       Train_eQTaskType);
  isValidPosition = ptTrain->isValidPosition;
  v4 = (struct Train_t *)FirstChildOfType;
  Train_GetPositions(ptTrain, atPos);
  result = (struct Train_t *)Train_MoveCarriage(ptTrain, atPos, 0);
  v6 = 1;
  if ( v4 )
  {
    do
    {
      v7 = v4->isValidPosition && isValidPosition;
      v4->isValidPosition = v7;
      Train_MoveCarriage(v4, atPos, v6++);
      result = (struct Train_t *)QTask_GetNextSiblingOfType(
                                   &v4->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask,
                                   Train_eQTaskType);
      v4 = result;
    }
    while ( result );
  }
  return result;
}

// source: j/0/vehicles/train.c:367  [anchor-mhash]
void __cdecl Train_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptParent; // eax
  struct Game_s *v3; // edx
  double v4; // st7
  double v5; // st7
  int *v6; // eax
  int v7; // eax
  double v8; // st6
  struct QTask_s *v9; // eax
  float ptDynCubeObj; // [esp+0h] [ebp-14h]

  ptParent = ptQTask->ptParent;
  if ( ptParent->eQTaskType == Train_eQTaskType )
    ++*(int *)&ptParent[49].tQTaskRefList.ptMiddle;
  v3 = Game_ptGame;
  ptQTask[49].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[49].tQTaskChildren.ptHead = nullptr;
  ptQTask[49].ptPrev = nullptr;
  ptQTask[49].ptNext = nullptr;
  *(_DWORD *)&ptQTask[48].eQTaskType = 1128792064;
  ptQTask[48].ptParent = (struct QTask_s *)1028443341;
  ptQTask[49].tQTaskRefList.ptTail = (struct QReference_s *)-1;
  ptQTask[49].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[56].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[56].tQTaskChildren.ptHead = nullptr;
  ptQTask[49].tQTaskChildren.ptTail = nullptr;
  ptQTask[49].tQTaskRefList.ptHead = nullptr;
  ptQTask[3].ptPrev = (struct QTask_s *)1065353216;
  ptQTask[3].tQTaskChildren.ptHead = nullptr;
  ptQTask[3].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[3].tQTaskChildren.ptTail = nullptr;
  ptQTask[3].tQTaskRefList.ptHead = (struct QReference_s *)1065353216;
  ptQTask[3].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[3].tQTaskRefList.ptTail = nullptr;
  ptQTask[3].ptParent = nullptr;
  *(_DWORD *)&ptQTask[3].eQTaskType = 1065353216;
  ptQTask[4].ptNext = nullptr;
  ptQTask[1].ptNext = nullptr;
  ptQTask[1].ptPrev = nullptr;
  ptQTask[1].tQTaskChildren.ptHead = nullptr;
  ptQTask[1].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[1].tQTaskChildren.ptTail = nullptr;
  ptQTask[1].tQTaskRefList.ptHead = nullptr;
  LOBYTE(ptQTask[49].ptParent) = 0;
  ModelObj_Init((struct ModelObj_s *)ptQTask, v3->ptWorld, nullptr);
  ptQTask[7].tQTaskChildren.ptHead = nullptr;
  ptQTask[7].tQTaskChildren.ptMiddle = (struct QTask_s *)2;
  ptQTask[7].tQTaskRefList.ptHead = nullptr;
  ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[7].tQTaskRefList.ptTail = nullptr;
  ptQTask[7].ptParent = nullptr;
  *(_DWORD *)&ptQTask[7].eQTaskType = 0;
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
  ptDynCubeObj = v5 * v8;
  World_RegisterDynCubeObjFirstTimeRadius(
    Game_ptGame->ptWorld,
    (struct DynCubeObj_s *)ptQTask,
    (struct real64x3_t *)&ptQTask[1],
    ptDynCubeObj,
    WORLD_DYNCUBETREE_CATEGORY_MOBILE);
  v9 = (struct QTask_s *)Mem_AllocFn(12, 4);
  if ( v9 )
  {
    v9->ptNext = (struct QTask_s *)2;
    v9->ptPrev = nullptr;
    v9->tQTaskChildren.ptHead = nullptr;
  }
  ptQTask[56].tQTaskChildren.ptTail = v9;
  Vehicle_Create((struct Vehicle_s *)ptQTask);
  ptQTask[56].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[56].tQTaskRefList.ptHead = (struct QReference_s *)-1;
  ptQTask[56].tQTaskRefList.ptTail = nullptr;
  ptQTask[56].ptParent = nullptr;
  *(_DWORD *)&ptQTask[56].eQTaskType = 0;
  ptQTask[58].tQTaskRefList.ptMiddle = nullptr;
}

// source: j/0/vehicles/train.c:433  [size]
void __cdecl Train_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = Train_ptParameterList;
}

// source: j/0/vehicles/train.c:449  [anchor-mhash]
void __cdecl Train_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptParent; // eax
  struct QTask_s *ptTail; // edi
  int v3; // esi

  QTask_DeleteQTaskAndQTaskRefSafe(&ptQTask[56].tQTaskRefList.ptMiddle);
  if ( ptQTask[3].ptNext )
  {
    QTask_Delete(ptQTask[3].ptNext);
    ptQTask[3].ptNext = nullptr;
  }
  *(_DWORD *)&ptQTask[12].eQTaskType = 0;
  Physics_DeAlloc((struct Physics_s *)&ptQTask[8]);
  ptParent = ptQTask->ptParent;
  if ( ptParent->eQTaskType == Train_eQTaskType )
    --*(int *)&ptParent[49].tQTaskRefList.ptMiddle;
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[56].tQTaskRefList.ptTail);
  World_RemoveDynCubeObj(Game_ptGame->ptWorld, (struct DynCubeObj_s *)ptQTask);
  ptTail = ptQTask[56].tQTaskChildren.ptTail;
  if ( ptTail )
  {
    v3 = *(_DWORD *)((unsigned int)&ptTail[-1].eQTaskType & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v3);
    memset(*(void **)(v3 + 8), 0xCDu, *(_DWORD *)(v3 + 16));
    free((void *)v3);
  }
}

// source: j/0/vehicles/train.c:487  [anchor-caller]
void __cdecl Train_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real32x3_t tVertex0; };
    struct { char igi2_o1[12]; struct real32x3_t tVertex1; };
    struct { char igi2_o2[24]; struct real32x3_t tReal32x3; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct LODVirModel_s *LODVirModelExistsFn; // eax
  double v3; // st7
  struct QTask_s *v4; // eax

  ptQTask[49].tQTaskChildren.ptHead = ptQTask[49].tQTaskChildren.ptMiddle;
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
  LODVirModelExistsFn = MTP_GetLODVirModelExistsFn((char *)&ptQTask[49].ptParent);
  if ( !LODVirModelExistsFn )
    LODVirModelExistsFn = nullptr;
  if ( LODVirModelExistsFn != *(struct LODVirModel_s **)&ptQTask[2].eQTaskType )
  {
    ModelObj_SetLODVirModel((struct ModelObj_s *)ptQTask, LODVirModelExistsFn, false);
    ptQTask[7].tQTaskRefList.ptHead = nullptr;
    ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
    ptQTask[7].tQTaskRefList.ptTail = nullptr;
    ptQTask[7].ptParent = nullptr;
    *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  }
  GameFunctions_GetMagicVertexLocal(&igi2_frame.tVertex0, ptQTask, 0);
  GameFunctions_GetMagicVertexLocal(&igi2_frame.tVertex1, ptQTask, 1);
  v3 = igi2_frame.tVertex0.vX - igi2_frame.tVertex1.vX;
  ptQTask[48].tQTaskRefList.ptMiddle = nullptr;
  igi2_frame.tReal32x3.vX = v3;
  igi2_frame.tReal32x3.vY = igi2_frame.tVertex0.vY - igi2_frame.tVertex1.vY;
  *(float *)&ptQTask[48].tQTaskRefList.ptTail = sqrt(
                                                  igi2_frame.tReal32x3.vX * igi2_frame.tReal32x3.vX
                                                + igi2_frame.tReal32x3.vY * igi2_frame.tReal32x3.vY
                                                + (igi2_frame.tVertex0.vZ - igi2_frame.tVertex1.vZ) * (igi2_frame.tVertex0.vZ - igi2_frame.tVertex1.vZ));
  PhysicsObj_Init(ptQTask, nullptr);
  if ( ptQTask[3].ptNext )
  {
    QTask_Delete(ptQTask[3].ptNext);
    ptQTask[3].ptNext = nullptr;
  }
  v4 = QTask_NewFn(nullptr, MagicObjContainer_eQTaskType, nullptr);
  v4[1].ptNext = ptQTask;
  ptQTask[3].ptNext = v4;
  ModelObj_CreateAttachObjects((struct ModelObj_s *)ptQTask, v4, ptQTask, false, true);
  if ( ptQTask->ptParent->eQTaskType != Train_eQTaskType )
    Train_Move((struct Train_t *)ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[56].tQTaskRefList.ptTail, ptQTask);
}

// source: j/0/vehicles/train.c:547  [size]
void __cdecl Train_UpdateInternalDataAfterLoadHandler(struct QTask_s *ptQTask)
{
  if ( ptQTask->ptParent->eQTaskType != Train_eQTaskType )
  {
    ptQTask[56].tQTaskChildren.ptHead = nullptr;
    Train_Move((struct Train_t *)ptQTask);
  }
}

// source: j/0/vehicles/train.c:568  [anchor-mhash]
void __cdecl Train_UpdateAnimDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v2; // edx
  struct QTask_s *v3; // eax
  struct QTask_s *v4; // eax
  double v5; // st7
  double v6; // st7
  double v7; // st7
  double v8; // st7
  double v9; // st7
  struct QTask_s *ptNext; // eax
  float tVel; // [esp+10h] [ebp-Ch]
  float tVela; // [esp+10h] [ebp-Ch]

  v2 = **((struct QTask_s ***)pxContext + 1);
  if ( v2 != (struct QTask_s *)-1082130432 )
    ptQTask[48].ptNext = v2;
  if ( *(_DWORD *)pxContext )
  {
    if ( *(float *)&ptQTask[48].tQTaskRefList.ptTail == 0.0 )
      ptQTask[48].tQTaskRefList.ptTail = (struct QReference_s *)1065353216;
    v7 = (*(float *)&ptQTask[48].ptNext - *(float *)&ptQTask[47].tQTaskRefList.ptMiddle)
       * *(float *)&ptQTask[48].ptParent
       + *(float *)&ptQTask[47].tQTaskRefList.ptMiddle;
    *(float *)&ptQTask[47].tQTaskRefList.ptMiddle = v7;
    v8 = v7 * *(float *)&ptQTask[48].eQTaskType * 4096000.0 * 9.259259059035685e-06;
    *(float *)&ptQTask[49].ptPrev = v8;
    tVela = v8;
    *(float *)&ptQTask[8].tQTaskRefList.ptMiddle = tVela;
    ptQTask[8].tQTaskRefList.ptTail = nullptr;
    ptQTask[8].ptParent = nullptr;
    Physics_UpdateSpeedApproximation((struct Physics_s *)&ptQTask[8]);
    v9 = *(float *)&ptQTask[49].ptPrev;
    if ( ptQTask[56].tQTaskChildren.ptMiddle )
      v9 = -v9;
    ptNext = ptQTask[3].ptNext;
    *(float *)&ptQTask[49].tQTaskChildren.ptHead = v9 + *(float *)&ptQTask[49].tQTaskChildren.ptHead;
    if ( ptNext )
      ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][ptNext->eQTaskType].pfHandler)(ptNext);
    Train_Move((struct Train_t *)ptQTask);
  }
  else
  {
    *(_DWORD *)(*((_DWORD *)pxContext + 1) + 4) = -1073741824;
    ptQTask[49].tQTaskChildren.ptHead = ptQTask[49].tQTaskChildren.ptMiddle;
    PhysicsObj_Init(ptQTask, nullptr);
    v3 = ptQTask[3].ptNext;
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
    if ( v3 )
    {
      QTask_Delete(v3);
      ptQTask[3].ptNext = nullptr;
    }
    v4 = QTask_NewFn(nullptr, MagicObjContainer_eQTaskType, nullptr);
    v4[1].ptNext = ptQTask;
    ptQTask[3].ptNext = v4;
    ModelObj_CreateAttachObjects((struct ModelObj_s *)ptQTask, v4, ptQTask, false, true);
    ptQTask[56].tQTaskChildren.ptHead = nullptr;
    Train_Move((struct Train_t *)ptQTask);
    v5 = *(float *)&ptQTask[48].eQTaskType * *(float *)&ptQTask[49].ptNext * 37.925926208496094;
    *(float *)&ptQTask[49].ptPrev = v5;
    tVel = v5;
    *(float *)&ptQTask[8].tQTaskRefList.ptMiddle = tVel;
    ptQTask[8].tQTaskRefList.ptTail = nullptr;
    ptQTask[8].ptParent = nullptr;
    Physics_UpdateSpeedApproximation((struct Physics_s *)&ptQTask[8]);
    v6 = *(float *)&ptQTask[49].ptNext;
    ptQTask[48].ptNext = ptQTask[49].ptNext;
    *(float *)&ptQTask[47].tQTaskRefList.ptMiddle = v6;
  }
}

// source: j/0/vehicles/train.c:659  [size]
void __cdecl Train_SoundUpdateParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = ptQTask + 1;
  *((_DWORD *)pxContext + 1) = 0;
  *((_DWORD *)pxContext + 2) = ptQTask[56].tQTaskChildren.ptTail;
}

// source: j/0/vehicles/train.c:683  [size]
void __cdecl Train_GetKeyframeSizeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = 20;
}

// source: j/0/vehicles/train.c:699  [anchor-mhash]
void __cdecl Train_SaveKeyframeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s **v2; // eax

  v2 = *(struct QTask_s ***)pxContext;
  qmemcpy(*((void **)pxContext + 2), &ptQTask[1], 0x18u);
  *v2 = ptQTask[49].ptPrev;
  v2[1] = ptQTask[49].tQTaskChildren.ptHead;
  v2[2] = (struct QTask_s *)ptQTask[47].tQTaskRefList.ptMiddle;
  v2[3] = ptQTask[48].ptNext;
}

// source: j/0/vehicles/train.c:736  [anchor-mhash]
void __cdecl Train_RestoreKeyframeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s **v2; // ecx

  v2 = *(struct QTask_s ***)pxContext;
  ptQTask[49].ptPrev = **(struct QTask_s ***)pxContext;
  ptQTask[49].tQTaskChildren.ptHead = v2[1];
  ptQTask[47].tQTaskRefList.ptMiddle = (struct QReference_s *)v2[2];
  ptQTask[48].ptNext = v2[3];
  Train_Move((struct Train_t *)ptQTask);
}

// source: j/0/vehicles/train.c:771  [size]
void __cdecl Train_GetChannelDescriptionHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // eax

  v2 = *(_DWORD *)pxContext;
  if ( *(int *)pxContext < 0 || v2 >= 2 )
    *((_DWORD *)pxContext + 1) = 0;
  else
    *((_DWORD *)pxContext + 1) = 16 * v2 + 7044476;
}

// source: j/0/vehicles/train.c:798  [anchor-mhash]
void __cdecl Train_ReadChannelsHandler(struct QTask_s *ptQTask, void *pxContext)
{
  double v3; // st7
  float pxContexta = *(float *)&pxContext; // [esp+8h] [ebp+8h] ARGSLOT

  **(_DWORD **)pxContext = -1082130432;
  if ( (Keyboard_tKeyboard.anCurrentKey[29] & 0x80u) == 0 && (Keyboard_tKeyboard.anCurrentKey[157] & 0x80) == 0 )
  {
    v3 = **(float **)pxContext;
    if ( (Keyboard_tKeyboard.anCurrentKey[42] & 0x80) != 0
      || (pxContexta = 1.0, (Keyboard_tKeyboard.anCurrentKey[54] & 0x80) != 0) )
    {
      pxContexta = -1.0;
    }
    if ( (Keyboard_tKeyboard.anCurrentKey[41] & 0x80) != 0 )
      v3 = pxContexta * 0.0;
    if ( (Keyboard_tKeyboard.anCurrentKey[2] & 0x80) != 0 )
      v3 = pxContexta * 0.10000000149011612;
    if ( (Keyboard_tKeyboard.anCurrentKey[3] & 0x80) != 0 )
      v3 = pxContexta * 0.20000000298023224;
    if ( (Keyboard_tKeyboard.anCurrentKey[4] & 0x80) != 0 )
      v3 = pxContexta * 0.30000001192092896;
    if ( (Keyboard_tKeyboard.anCurrentKey[5] & 0x80) != 0 )
      v3 = pxContexta * 0.4000000059604645;
    if ( (Keyboard_tKeyboard.anCurrentKey[6] & 0x80) != 0 )
      v3 = pxContexta * 0.5;
    if ( (Keyboard_tKeyboard.anCurrentKey[7] & 0x80) != 0 )
      v3 = pxContexta * 0.6000000238418579;
    if ( (Keyboard_tKeyboard.anCurrentKey[8] & 0x80) != 0 )
      v3 = pxContexta * 0.699999988079071;
    if ( (Keyboard_tKeyboard.anCurrentKey[9] & 0x80) != 0 )
      v3 = pxContexta * 0.800000011920929;
    if ( (Keyboard_tKeyboard.anCurrentKey[10] & 0x80) != 0 )
      v3 = pxContexta * 0.8999999761581421;
    if ( (Keyboard_tKeyboard.anCurrentKey[11] & 0x80) != 0 )
      v3 = pxContexta;
    **(float **)pxContext = v3;
  }
  *(_DWORD *)(*(_DWORD *)pxContext + 4) = -1073741824;
  if ( (Keyboard_tKeyboard.anCurrentKey[29] & 0x80) != 0 || (Keyboard_tKeyboard.anCurrentKey[157] & 0x80) != 0 )
  {
    if ( (Keyboard_tKeyboard.anCurrentKey[41] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[41] & 0x80) == 0 )
      *(_DWORD *)(*(_DWORD *)pxContext + 4) = -1082130432;
    if ( (Keyboard_tKeyboard.anCurrentKey[2] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[2] & 0x80) == 0 )
      *(_DWORD *)(*(_DWORD *)pxContext + 4) = 1065353216;
    if ( (Keyboard_tKeyboard.anCurrentKey[3] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[3] & 0x80) == 0 )
      *(_DWORD *)(*(_DWORD *)pxContext + 4) = 0x40000000;
    if ( (Keyboard_tKeyboard.anCurrentKey[4] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[4] & 0x80) == 0 )
      *(_DWORD *)(*(_DWORD *)pxContext + 4) = 1077936128;
    if ( (Keyboard_tKeyboard.anCurrentKey[5] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[5] & 0x80) == 0 )
      *(_DWORD *)(*(_DWORD *)pxContext + 4) = 1082130432;
    if ( (Keyboard_tKeyboard.anCurrentKey[6] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[6] & 0x80) == 0 )
      *(_DWORD *)(*(_DWORD *)pxContext + 4) = 1084227584;
    if ( (Keyboard_tKeyboard.anCurrentKey[7] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[7] & 0x80) == 0 )
      *(_DWORD *)(*(_DWORD *)pxContext + 4) = 1086324736;
    if ( (Keyboard_tKeyboard.anCurrentKey[8] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[8] & 0x80) == 0 )
      *(_DWORD *)(*(_DWORD *)pxContext + 4) = 1088421888;
    if ( (Keyboard_tKeyboard.anCurrentKey[9] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[9] & 0x80) == 0 )
      *(_DWORD *)(*(_DWORD *)pxContext + 4) = 1090519040;
    if ( (Keyboard_tKeyboard.anCurrentKey[10] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[10] & 0x80) == 0 )
      *(_DWORD *)(*(_DWORD *)pxContext + 4) = 1091567616;
    if ( (Keyboard_tKeyboard.anCurrentKey[11] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[11] & 0x80) == 0 )
      *(_DWORD *)(*(_DWORD *)pxContext + 4) = 0;
  }
}

// source: j/0/vehicles/train.c:922  [anchor-mhash]
void __cdecl Train_GetCameraTargetInfoHandler(struct QTask_s *ptQTask, void *pxContext)
{
  long double v3; // st7
  long double v4; // st6
  long double v5; // st5
  double v6; // st4
  double v7; // st4
  long double v8; // st4
  double v9; // st7
  double v10; // st7
  double v11; // st7
  int *v12; // ebx
  int v13; // ebx
  double v14; // st6
  char *v15; // edx
  struct real32x9_t Real32x9_Multiply_tTemp; // [esp+10h] [ebp-2Ch] BYREF

  v3 = sin(-1.5707963705062866);
  qmemcpy(pxContext, &ptQTask[1], 0x18u);
  *((_DWORD *)pxContext + 6) = 0;
  *((_DWORD *)pxContext + 7) = 0;
  *((_DWORD *)pxContext + 8) = 0;
  qmemcpy((char *)pxContext + 36, &ptQTask[3].ptPrev, 0x28u);
  v4 = cos(-1.5707963705062866);
  v5 = -v3;
  v6 = *((float *)pxContext + 11) * 0.0;
  Real32x9_Multiply_tTemp.tX.vX = v4 * *((float *)pxContext + 9) + v3 * *((float *)pxContext + 10) + v6;
  Real32x9_Multiply_tTemp.tX.vY = -v3 * *((float *)pxContext + 9) + v4 * *((float *)pxContext + 10) + v6;
  Real32x9_Multiply_tTemp.tX.vZ = (*((float *)pxContext + 9) + *((float *)pxContext + 10)) * 0.0
                                + *((float *)pxContext + 11);
  v7 = *((float *)pxContext + 14) * 0.0;
  Real32x9_Multiply_tTemp.tY.vX = v4 * *((float *)pxContext + 12) + v3 * *((float *)pxContext + 13) + v7;
  Real32x9_Multiply_tTemp.tY.vY = v4 * *((float *)pxContext + 13) + -v3 * *((float *)pxContext + 12) + v7;
  Real32x9_Multiply_tTemp.tY.vZ = (*((float *)pxContext + 13) + *((float *)pxContext + 12)) * 0.0
                                + *((float *)pxContext + 14);
  v8 = v4 * *((float *)pxContext + 15) + v3 * *((float *)pxContext + 16);
  v9 = *((float *)pxContext + 17) * 0.0;
  Real32x9_Multiply_tTemp.nOps = *((_DWORD *)pxContext + 18) + 1;
  Real32x9_Multiply_tTemp.tZ.vX = v8 + v9;
  Real32x9_Multiply_tTemp.tZ.vY = v5 * *((float *)pxContext + 15) + v4 * *((float *)pxContext + 16) + v9;
  Real32x9_Multiply_tTemp.tZ.vZ = (*((float *)pxContext + 15) + *((float *)pxContext + 16)) * 0.0
                                + *((float *)pxContext + 17);
  qmemcpy((char *)pxContext + 36, &Real32x9_Multiply_tTemp, 0x28u);
  if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
    v10 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  else
    v10 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  if ( v10 >= *(float *)&ptQTask[6].ptPrev )
  {
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
      v11 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v11 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  }
  else
  {
    v11 = *(float *)&ptQTask[6].ptPrev;
  }
  v12 = *(int **)&ptQTask[2].eQTaskType;
  if ( v12 && (v13 = *v12) != 0 )
    v14 = *(float *)(*(_DWORD *)(*(_DWORD *)(v13 + 12) + 12) + 120);
  else
    v14 = 1.0;
  *((float *)pxContext + 19) = v11 * v14;
  v15 = *((char **)pxContext + 20);
  if ( v15 )
    strcpy(v15, "Train");
}

// source: j/0/vehicles/train.c:973  [anchor-strings]
void __cdecl Train_RunHandler(struct QTask_s *ptQTask)
{
  struct QReference_s *nTicks; // eax
  char *v3; // eax
  struct QTask_s *v4; // eax
  struct QTask_s *ptTail; // ecx
  struct QTask_s *ptParent; // eax
  double v7; // st7
  double v8; // st7
  struct QTask_s *ptHead; // edx
  int v10; // eax
  struct QTask_s *v11; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *); // ecx
  int v13; // eax
  struct QTask_s *ptNext; // ecx
  int v15; // edx
  struct QTask_s *v16; // ecx
  void (__cdecl *v17)(int); // ecx
  int v18; // eax
  float ptQTaska = *(float *)&ptQTask; // [esp+14h] [ebp+4h] ARGSLOT

  nTicks = (struct QReference_s *)Flow_ptFlow->nTicks;
  if ( ptQTask[56].tQTaskRefList.ptHead != nTicks )
  {
    ptQTask[56].tQTaskRefList.ptHead = nTicks;
    if ( ptQTask[56].tQTaskRefList.ptTail
      && ptQTask[56].ptParent->ptNext
      && *(_DWORD *)&ptQTask[56].eQTaskType
      && (unsigned int)(__int64)Level_RunLevelExpression(
                                  (struct LevelExpression_s *)&ptQTask[56].tQTaskRefList.ptTail,
                                  ptQTask) )
    {
      if ( !ptQTask[56].tQTaskRefList.ptMiddle )
      {
        v3 = "train_loop_1";
        if ( !ptQTask[49].tQTaskRefList.ptMiddle )
          v3 = "train_loop_2";
        v4 = SoundSys_NewSoundFn(ptQTask, v3);
        ptQTask[56].tQTaskRefList.ptMiddle = QTask_NewQTaskRef(v4);
      }
    }
    else
    {
      QTask_DeleteQTaskAndQTaskRefSafe(&ptQTask[56].tQTaskRefList.ptMiddle);
    }
    ptTail = ptQTask[56].tQTaskChildren.ptTail;
    if ( ptTail )
    {
      ptParent = ptQTask->ptParent;
      if ( ptParent->eQTaskType == Train_eQTaskType )
      {
        v7 = *(float *)&ptParent[47].tQTaskRefList.ptMiddle;
        ptQTaska = *(float *)&ptParent[47].tQTaskRefList.ptMiddle;
      }
      else
      {
        v7 = *(float *)&ptQTask[47].tQTaskRefList.ptMiddle;
        ptQTaska = *(float *)&ptQTask[47].tQTaskRefList.ptMiddle;
      }
      v8 = v7 * 5.0;
      if ( v8 >= 0.800000011920929 )
      {
        if ( v8 > 1.0 )
          v8 = 1.0;
      }
      else
      {
        v8 = 0.800000011920929;
      }
      *(float *)&ptTail->ptPrev = v8;
      *(float *)&ptQTask[56].tQTaskChildren.ptTail->tQTaskChildren.ptHead = (float)(ptQTaska > 0.0010000000474974513);
    }
    ptHead = ptQTask->tQTaskChildren.ptHead;
    if ( ptHead->ptNext && ptHead )
    {
      v10 = QTask_nProtectedQTaskStackOffset;
      do
      {
        if ( ptHead->ptNext )
          v11 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
        else
          v11 = nullptr;
        QTask_atProtectedQTaskStack[v10].ptQTask = v11;
        pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][ptHead->eQTaskType].pfHandler;
        v13 = v10 + 1;
        QTask_nProtectedQTaskStackOffset = v13;
        if ( pfHandler )
        {
          pfHandler(ptHead);
          v13 = QTask_nProtectedQTaskStackOffset;
        }
        ptHead = (struct QTask_s *)dword_849C7DC[v13];
        v10 = v13 - 1;
        QTask_nProtectedQTaskStackOffset = v10;
      }
      while ( ptHead );
    }
    else
    {
      v10 = QTask_nProtectedQTaskStackOffset;
    }
    ptNext = ptQTask[3].ptNext;
    if ( ptNext )
    {
      if ( !ptQTask[49].tQTaskRefList.ptMiddle )
      {
        v15 = (int)ptNext->tQTaskChildren.ptHead;
        if ( *(_DWORD *)v15 )
        {
          for ( ; v15; QTask_nProtectedQTaskStackOffset = v10 )
          {
            if ( *(_DWORD *)v15 )
              v16 = **(_DWORD **)v15 != 0 ? *(struct QTask_s **)v15 : nullptr;
            else
              v16 = nullptr;
            QTask_atProtectedQTaskStack[v10].ptQTask = v16;
            v17 = (void (__cdecl *)(int))QTask_aatQTaskFinalEvent[1][*(unsigned __int16 *)(v15 + 36)].pfHandler;
            v18 = v10 + 1;
            QTask_nProtectedQTaskStackOffset = v18;
            if ( v17 )
            {
              v17(v15);
              v18 = QTask_nProtectedQTaskStackOffset;
            }
            v15 = dword_849C7DC[v18];
            v10 = v18 - 1;
          }
        }
      }
    }
  }
}

// source: j/0/vehicles/train.c:1056  [size]
void __cdecl Train_RegisterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ((void (__cdecl *)())QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRegisterQTaskEvent][Vehicle_eQTaskType].pfHandler)(ptQTask, pxContext);
}

// source: j/0/vehicles/train.c:1080  [size]
void __cdecl Train_RemoveHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRemoveQTaskEvent][Vehicle_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  QTask_DeleteQTaskAndQTaskRefSafe(&ptQTask[56].tQTaskRefList.ptMiddle);
}

// source: j/0/vehicles/train.c:1112  [size]
unsigned __int16 __cdecl Train_GetQTaskType()
{
  return Train_eQTaskType;
}

// source: j/0/vehicles/train.c:1125  [size]
int __cdecl Train_GetNumCarriges(struct QTask_s *ptQTask)
{
  return (int)ptQTask[49].tQTaskRefList.ptMiddle;
}

// source: j/0/vehicles/train.c:1141  [anchor-caller]
void __cdecl Train_Open()
{
  unsigned __int16 v0; // si
  __int16 v1; // ax
  struct ParameterList_s *v2; // eax
  int v3; // edx
  unsigned __int16 v4; // si

  v0 = QTask_NewQTaskType("Train", 2352, Vehicle_eQTaskType, 0, 0);
  Train_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, Train_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, Train_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, Train_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Train_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 8, Train_GetCameraTargetInfoHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, Train_RunHandler);
  v1 = SoundSys_eUpdateParameterListQTaskEvent;
  if ( SoundSys_eUpdateParameterListQTaskEvent == 512 )
  {
    v1 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.nRealFadeCount);
    v0 = Train_eQTaskType;
    SoundSys_eUpdateParameterListQTaskEvent = v1;
  }
  QTask_LinkQTaskEventHandlerFn(v0, v1, Train_SoundUpdateParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, AnimQTask_eUpdateAnimDataEvent, Train_UpdateAnimDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    AnimQTask_eGetChannelDescriptionEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Train_GetChannelDescriptionHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    AnimQTask_eGetKeyframeSizeEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Train_GetKeyframeSizeHandler);
  QTask_LinkQTaskEventHandlerFn(v0, AnimQTask_eSaveKeyframeEvent, Train_SaveKeyframeHandler);
  QTask_LinkQTaskEventHandlerFn(v0, AnimQTask_eRestoreKeyframeEvent, Train_RestoreKeyframeHandler);
  QTask_LinkQTaskEventHandlerFn(v0, AnimQTask_eReadChannelsEvent, Train_ReadChannelsHandler);
  QTask_LinkQTaskEventHandlerFn(v0, DynCubeObj_eDynCubeObjRemoveQTaskEvent, Train_RemoveHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    DynCubeObj_eDynCubeObjRegisterQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Train_RegisterHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Attach_eUpdateAttachmentEvent, nullptr);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eUpdateInternalDataAfterLoadEvent,
    Train_UpdateInternalDataAfterLoadHandler);
  v2 = (struct ParameterList_s *)Mem_AllocFn(212, 4);
  v3 = Level_eParameterTypeReal32;
  v2->ptParameterListItem = (struct ParameterListItem_s *)&v2[1];
  v2->nParameters = 0;
  v2->nMaxParameters = 10;
  Train_ptParameterList = v2;
  ParameterList_AddParameter(v2, 0x7B4u, v3, "Position", 7u, nullptr);
  ParameterList_AddParameter(Train_ptParameterList, 0x7A8u, Level_eParameterTypeReal32, "Original thrust", 7u, nullptr);
  ParameterList_AddParameter(Train_ptParameterList, 0x7C4u, Level_eParameterTypeInt32, "RailroadQTaskID", 7u, nullptr);
  ParameterList_AddParameter(Train_ptParameterList, 0x7C8u, Level_eParameterTypeString256, "Model", 7u, nullptr);
  ParameterList_AddParameterMinMax(
    Train_ptParameterList,
    0x7A0u,
    Level_eParameterTypeReal32,
    "Acceleration",
    7u,
    0.0,
    1.0);
  ParameterList_AddParameter(Train_ptParameterList, 0x7A4u, Level_eParameterTypeReal32, "MaxSpeed", 7u, nullptr);
  ParameterList_AddParameter(Train_ptParameterList, 0x8CCu, Level_eParameterTypebool8, "Flip Direction", 7u, nullptr);
  ParameterList_AddParameterMinMax(
    Train_ptParameterList,
    0x7B8u,
    Level_eParameterTypeReal32,
    "Displacement X",
    7u,
    -5.0,
    5.0);
  ParameterList_AddParameterMinMax(
    Train_ptParameterList,
    0x7BCu,
    Level_eParameterTypeReal32,
    "Displacement Z",
    7u,
    -5.0,
    5.0);
  ParameterList_AddParameter(Train_ptParameterList, 0x8DCu, Level_eParameterTypeVarString, "Play Sound", 7u, nullptr);
  v4 = Train_eQTaskType;
  QTask_LinkQTaskEventHandlerFn(
    Train_eQTaskType,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(
    v4,
    Serialize_eGetSerializeParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Train_GetSerializeParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v4, Serialize_eDeSerializeQTaskEvent, Train_DeSerializeHandler);
  Train_ptSerializeParameterList = ParameterList_Derive(ModelObjParameters_ptSerializeParameterList, 4);
  ParameterList_AddParameter(
    Train_ptSerializeParameterList,
    0x770u,
    Level_eParameterTypeReal32,
    "vRealThrust",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Train_ptSerializeParameterList,
    0x780u,
    Level_eParameterTypeReal32,
    "vIdealThrust",
    7u,
    nullptr);
  ParameterList_AddParameter(Train_ptSerializeParameterList, 0x7ACu, Level_eParameterTypeReal32, "vSpeed", 7u, nullptr);
  ParameterList_AddParameter(Train_ptSerializeParameterList, 0x7B0u, Level_eParameterTypeReal32, "vPos", 7u, nullptr);
}

// source: j/0/vehicles/train.c:1201  [size]
void __cdecl Train_Close()
{
  int v0; // esi
  int v1; // esi

  QTask_DeleteQTaskType(Train_eQTaskType);
  if ( Train_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&Train_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  if ( Train_ptSerializeParameterList )
  {
    v1 = *(_DWORD *)((unsigned int)&Train_ptSerializeParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
}
