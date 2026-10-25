/* j/0/objects/door.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/objects/door.c:218  [anchor-mhash]
void __cdecl Door_SetPosition(struct Door_s *ptDoor)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { float ptDynCubeObja; };
    struct { char igi2_o2[28]; double Real64x3_Rotate_tTemp_8; };
    struct { char igi2_o3[44]; struct real32x9_t tNewOrientation; };
    char igi2_extent[88];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v1; // st7
  double v2; // st6
  double v3; // st5
  double vZ; // st7
  double vY; // st7
  struct LODVirModel_s *ptLODVirModel; // eax
  struct VirModel_s *v7; // eax
  double vRadius; // st6
  struct real32x9_t *p_tNewOrientation; // esi

  v1 = ptDoor->vOriginalStopX * ptDoor->vRealPos * 4096.0;
  v2 = ptDoor->vOriginalStopY * ptDoor->vRealPos * 4096.0;
  igi2_frame.Real64x3_Rotate_tTemp_8 = ptDoor->tOriginalOrientation.tY.vY * v2
                          + ptDoor->tOriginalOrientation.tY.vX * v1
                          + ptDoor->tOriginalOrientation.tY.vZ * 0.0;
  v3 = ptDoor->tOriginalOrientation.tZ.vY * v2
     + ptDoor->tOriginalOrientation.tZ.vX * v1
     + ptDoor->tOriginalOrientation.tZ.vZ * 0.0;
  *(double *)&igi2_frame.tNewOrientation.tX.vX = ptDoor->tOriginalOrientation.tX.vY * v2
                                    + ptDoor->tOriginalOrientation.tX.vX * v1
                                    + ptDoor->tOriginalOrientation.tX.vZ * 0.0
                                    + ptDoor->tOriginalPosStart.vX;
  *(double *)&igi2_frame.tNewOrientation.tX.vZ = igi2_frame.Real64x3_Rotate_tTemp_8 + ptDoor->tOriginalPosStart.vY;
  *(double *)&igi2_frame.tNewOrientation.tY.vY = v3 + ptDoor->tOriginalPosStart.vZ;
  if ( ptDoor->tRigidDynCubeObj.tModelObj.tScale.vY <= (double)ptDoor->tRigidDynCubeObj.tModelObj.tScale.vZ )
    vZ = ptDoor->tRigidDynCubeObj.tModelObj.tScale.vZ;
  else
    vZ = ptDoor->tRigidDynCubeObj.tModelObj.tScale.vY;
  if ( vZ >= ptDoor->tRigidDynCubeObj.tModelObj.tScale.vX )
  {
    if ( ptDoor->tRigidDynCubeObj.tModelObj.tScale.vY <= (double)ptDoor->tRigidDynCubeObj.tModelObj.tScale.vZ )
      vY = ptDoor->tRigidDynCubeObj.tModelObj.tScale.vZ;
    else
      vY = ptDoor->tRigidDynCubeObj.tModelObj.tScale.vY;
  }
  else
  {
    vY = ptDoor->tRigidDynCubeObj.tModelObj.tScale.vX;
  }
  ptLODVirModel = ptDoor->tRigidDynCubeObj.tModelObj.ptLODVirModel;
  if ( ptLODVirModel && (v7 = ptLODVirModel->aptVirModel[0]) != nullptr )
    vRadius = v7->ptModel->ptMesh->vRadius;
  else
    vRadius = 1.0;
  igi2_frame.ptDynCubeObj = vY * vRadius;
  World_MoveDynCubeObjRadius(
    Game_ptGame->ptWorld,
    &ptDoor->tRigidDynCubeObj.tModelObj.tDynCubeObj,
    (struct real64x3_t *)&igi2_frame.tNewOrientation,
    igi2_frame.ptDynCubeObj);
  if ( ptDoor->tParameters.vMaxAngle > 0.0010000000474974513 || ptDoor->tParameters.vMaxAngle < -0.0010000000474974513 )
  {
    igi2_frame.ptDynCubeObja = ptDoor->tParameters.vMaxAngle * ptDoor->vRealPos * 0.01745329238474369;
    Real32x9_RotateGamma(&igi2_frame.tNewOrientation, &ptDoor->tOriginalOrientation, igi2_frame.ptDynCubeObja);
    p_tNewOrientation = &igi2_frame.tNewOrientation;
  }
  else
  {
    p_tNewOrientation = &ptDoor->tOriginalOrientation;
  }
  qmemcpy(
    &ptDoor->tRigidDynCubeObj.tModelObj.tOrientation,
    p_tNewOrientation,
    sizeof(ptDoor->tRigidDynCubeObj.tModelObj.tOrientation));
  RigidDynCubeObj_UpdateAttachments(&ptDoor->tRigidDynCubeObj);
}

// source: j/0/objects/door.c:276  [size]
void __cdecl Door_GetGameItemDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *((_WORD *)pxContext + 1) = 2;
  *(_WORD *)pxContext = ptQTask[23].ptPrev;
  *((_WORD *)pxContext + 2) = Door_eQTaskType;
  *((_BYTE *)pxContext + 6) = BYTE2(ptQTask[23].tQTaskChildren.ptMiddle);
  *((_BYTE *)pxContext + 7) = HIBYTE(ptQTask[23].tQTaskChildren.ptMiddle);
}

// source: j/0/objects/door.c:307  [anchor-mhash]
void __cdecl Door_GameItemUpdateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  double v2; // st7

  v2 = *(float *)&ptQTask[10].tQTaskChildren.ptTail;
  BYTE2(ptQTask[23].tQTaskChildren.ptMiddle) = *((_BYTE *)pxContext + 6);
  if ( v2 <= 0.0 || *(float *)&ptQTask[10].tQTaskChildren.ptTail >= 1.0 )
  {
    if ( *((_BYTE *)pxContext + 7) )
    {
      if ( !LOBYTE(ptQTask[23].tQTaskChildren.ptTail) )
        return;
    }
    else if ( !HIBYTE(ptQTask[23].tQTaskChildren.ptMiddle) )
    {
      return;
    }
    BYTE2(ptQTask[23].tQTaskRefList.ptHead) ^= 1u;
    BYTE1(ptQTask[23].tQTaskRefList.ptHead) = 1;
  }
}

// source: j/0/objects/door.c:346  [anchor-mhash]
void __cdecl Door_AttachToParent(struct Door_s *ptDoor)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v14; };
    struct { char igi2_o1[28]; float Real32x9_Invert_tTemp_12; };
    struct { char igi2_o2[32]; float Real32x9_Invert_tTemp_16; };
    struct { char igi2_o3[36]; float Real32x9_Invert_tTemp_20; };
    struct { char igi2_o4[40]; float Real32x9_Invert_tTemp_24; };
    struct { char igi2_o5[44]; float Real32x9_Invert_tTemp_28; };
    struct { char igi2_o6[56]; struct real32x9_t Real32x9_Multiply_tTemp; };
    char igi2_extent[100];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  __int16 v1; // cx
  struct real64x3_t *ptParentPos; // edx
  struct real32x9_t *ptParentOrientation; // eax
  double vX; // st7
  double v5; // st6
  double v6; // st5
  float vZ; // ecx
  int nOps; // eax
  double v9; // st4
  double v10; // st3
  double v11; // st4
  double v12; // rt0
  double v13; // st5
  struct real32x3_t struct_real32x3_t; // 0:^10.12

  memset(
    &ptDoor->tRigidDynCubeObj.tModelObj.tAttachContext,
    0,
    sizeof(ptDoor->tRigidDynCubeObj.tModelObj.tAttachContext));
  v1 = Attach_eAttachEvent;
  ptDoor->tRigidDynCubeObj.tModelObj.tAttachContext.iID = -1;
  QTask_TriggerQTaskEventParent(
    &ptDoor->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask,
    v1,
    &ptDoor->tRigidDynCubeObj.tModelObj.tAttachContext);
  ptParentPos = ptDoor->tRigidDynCubeObj.tModelObj.tAttachContext.ptParentPos;
  if ( ptParentPos )
  {
    ptParentOrientation = ptDoor->tRigidDynCubeObj.tModelObj.tAttachContext.ptParentOrientation;
    vX = ptParentOrientation->tX.vX;
    v5 = ptParentOrientation->tY.vX;
    igi2_frame.Real32x9_Invert_tTemp_12 = ptParentOrientation->tX.vY;
    v6 = ptParentOrientation->tZ.vX;
    igi2_frame.Real32x9_Invert_tTemp_16 = ptParentOrientation->tY.vY;
    igi2_frame.Real32x9_Invert_tTemp_20 = ptParentOrientation->tZ.vY;
    igi2_frame.Real32x9_Invert_tTemp_24 = ptParentOrientation->tX.vZ;
    igi2_frame.Real32x9_Invert_tTemp_28 = ptParentOrientation->tY.vZ;
    vZ = ptParentOrientation->tZ.vZ;
    nOps = ptParentOrientation->nOps;
    igi2_frame.Real32x9_Multiply_tTemp.tX.vX = vX * ptDoor->tOriginalOrientation.tX.vX
                                  + v6 * ptDoor->tOriginalOrientation.tZ.vX
                                  + v5 * ptDoor->tOriginalOrientation.tY.vX;
    igi2_frame.Real32x9_Multiply_tTemp.tX.vY = vX * ptDoor->tOriginalOrientation.tX.vY
                                  + v6 * ptDoor->tOriginalOrientation.tZ.vY
                                  + v5 * ptDoor->tOriginalOrientation.tY.vY;
    igi2_frame.Real32x9_Multiply_tTemp.tX.vZ = vX * ptDoor->tOriginalOrientation.tX.vZ
                                  + v6 * ptDoor->tOriginalOrientation.tZ.vZ
                                  + v5 * ptDoor->tOriginalOrientation.tY.vZ;
    igi2_frame.Real32x9_Multiply_tTemp.tY.vX = igi2_frame.Real32x9_Invert_tTemp_12 * ptDoor->tOriginalOrientation.tX.vX
                                  + igi2_frame.Real32x9_Invert_tTemp_20 * ptDoor->tOriginalOrientation.tZ.vX
                                  + igi2_frame.Real32x9_Invert_tTemp_16 * ptDoor->tOriginalOrientation.tY.vX;
    igi2_frame.Real32x9_Multiply_tTemp.tY.vY = igi2_frame.Real32x9_Invert_tTemp_12 * ptDoor->tOriginalOrientation.tX.vY
                                  + igi2_frame.Real32x9_Invert_tTemp_20 * ptDoor->tOriginalOrientation.tZ.vY
                                  + igi2_frame.Real32x9_Invert_tTemp_16 * ptDoor->tOriginalOrientation.tY.vY;
    igi2_frame.Real32x9_Multiply_tTemp.tY.vZ = igi2_frame.Real32x9_Invert_tTemp_12 * ptDoor->tOriginalOrientation.tX.vZ
                                  + igi2_frame.Real32x9_Invert_tTemp_20 * ptDoor->tOriginalOrientation.tZ.vZ
                                  + igi2_frame.Real32x9_Invert_tTemp_16 * ptDoor->tOriginalOrientation.tY.vZ;
    v9 = igi2_frame.Real32x9_Invert_tTemp_24 * ptDoor->tOriginalOrientation.tX.vX + vZ * ptDoor->tOriginalOrientation.tZ.vX;
    v10 = igi2_frame.Real32x9_Invert_tTemp_28 * ptDoor->tOriginalOrientation.tY.vX;
    igi2_frame.Real32x9_Multiply_tTemp.nOps = ptDoor->tOriginalOrientation.nOps + nOps + 1;
    igi2_frame.Real32x9_Multiply_tTemp.tZ.vX = v9 + v10;
    igi2_frame.Real32x9_Multiply_tTemp.tZ.vY = igi2_frame.Real32x9_Invert_tTemp_24 * ptDoor->tOriginalOrientation.tX.vY
                                  + vZ * ptDoor->tOriginalOrientation.tZ.vY
                                  + igi2_frame.Real32x9_Invert_tTemp_28 * ptDoor->tOriginalOrientation.tY.vY;
    igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ = igi2_frame.Real32x9_Invert_tTemp_24 * ptDoor->tOriginalOrientation.tX.vZ
                                  + vZ * ptDoor->tOriginalOrientation.tZ.vZ
                                  + igi2_frame.Real32x9_Invert_tTemp_28 * ptDoor->tOriginalOrientation.tY.vZ;
    v11 = ptDoor->tOriginalPosStart.vX;
    qmemcpy(
      &ptDoor->tRigidDynCubeObj.tModelObj.tRelativeOrientation,
      &igi2_frame.Real32x9_Multiply_tTemp,
      sizeof(ptDoor->tRigidDynCubeObj.tModelObj.tRelativeOrientation));
    ptDoor->tRigidDynCubeObj.tModelObj.tRelativePos.vX = v11 - ptParentPos->vX;
    ptDoor->tRigidDynCubeObj.tModelObj.tRelativePos.vY = ptDoor->tOriginalPosStart.vY - ptParentPos->vY;
    igi2_frame.v14 = ptDoor->tOriginalPosStart.vZ - ptParentPos->vZ;
    v12 = v6;
    v13 = vX * ptDoor->tRigidDynCubeObj.tModelObj.tRelativePos.vX;
    ptDoor->tRigidDynCubeObj.tModelObj.tRelativePos.vZ = igi2_frame.v14;
    struct_real32x3_t.vX = v13 + v5 * ptDoor->tRigidDynCubeObj.tModelObj.tRelativePos.vY + v12 * igi2_frame.v14;
    struct_real32x3_t.vY = igi2_frame.Real32x9_Invert_tTemp_12 * ptDoor->tRigidDynCubeObj.tModelObj.tRelativePos.vX
                         + igi2_frame.Real32x9_Invert_tTemp_16 * ptDoor->tRigidDynCubeObj.tModelObj.tRelativePos.vY
                         + igi2_frame.Real32x9_Invert_tTemp_20 * igi2_frame.v14;
    struct_real32x3_t.vZ = igi2_frame.Real32x9_Invert_tTemp_24 * ptDoor->tRigidDynCubeObj.tModelObj.tRelativePos.vX
                         + igi2_frame.Real32x9_Invert_tTemp_28 * ptDoor->tRigidDynCubeObj.tModelObj.tRelativePos.vY
                         + vZ * igi2_frame.v14;
    ptDoor->tRigidDynCubeObj.tModelObj.tRelativePos = struct_real32x3_t;
  }
}

// source: j/0/objects/door.c:387  [anchor-mhash]
struct real64x3_t *__cdecl Door_TraceForPortals(
        struct Door_s *ptDoor,
        struct real64x3_t *ptStart,
        struct real64x3_t *ptEnd,
        unsigned __int16 *piPortal,
        struct QReference_s **pptSectorRef,
        struct real64x3_t *ptPos)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct World_s *ptWorld; };
    struct { char igi2_o1[48]; struct TraceLinesContext_s tContext; };
    struct { char igi2_o2[88]; struct QIntersection_s tIntersection; };
    char igi2_extent[208];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct real64x3_t *result; // eax
  unsigned __int16 iPortal; // si
  struct QObj_s *ptHitObj; // edx

  memset(&igi2_frame.tIntersection, 0, sizeof(igi2_frame.tIntersection));
  igi2_frame.tContext.ptIntersection = &igi2_frame.tIntersection;
  igi2_frame.tContext.isTracePortals = 1;
  igi2_frame.tContext.nNumLines = 1;
  igi2_frame.tContext.eEvalQTaskEvent = Door_eAttachToPortalQTaskEvent;
  igi2_frame.ptWorld = ptDoor->tRigidDynCubeObj.tModelObj.ptWorld;
  igi2_frame.tIntersection.iPortal = -1;
  igi2_frame.tContext.ptEvalContext = nullptr;
  igi2_frame.tContext.ptStart = ptStart;
  igi2_frame.tContext.ptEnd = ptEnd;
  igi2_frame.tContext.nValidationNumber = 1094861636;
  igi2_frame.tContext.iMesh = 0;
  igi2_frame.tContext.iIgnoreMaterial = 0;
  World_TriggerQTaskEventAlongLineSpecificTree(
    igi2_frame.ptWorld,
    10,
    &igi2_frame.tContext,
    ptStart,
    ptEnd,
    1,
    (unsigned int)&TerrainRender_atEdge[4623].iSplitVertex,
    WORLD_DYNCUBETREE_STATIONARY);
  result = (struct real64x3_t *)igi2_frame.tContext.ptIntersection;
  if ( igi2_frame.tContext.ptIntersection->isHit )
  {
    iPortal = igi2_frame.tContext.ptIntersection->iPortal;
    if ( iPortal != 0xFFFF )
    {
      ptHitObj = igi2_frame.tContext.ptIntersection->ptHitObj;
      if ( igi2_frame.tContext.ptIntersection->ptHitObj )
      {
        result = (struct real64x3_t *)QTask_IsQTaskTypeDerived(ptHitObj->tQTask.eQTaskType, Sector_eQTaskType);
        if ( result )
        {
          *piPortal = iPortal;
          result = (struct real64x3_t *)QTask_NewQTaskRef(&ptHitObj->tQTask);
          *pptSectorRef = (struct QReference_s *)result;
          qmemcpy(ptPos, &igi2_frame.tIntersection.tPos, sizeof(struct real64x3_t));
        }
        else
        {
          *piPortal = -1;
          *pptSectorRef = nullptr;
        }
      }
    }
  }
  return result;
}

// source: j/0/objects/door.c:457  [anchor-mhash]
void __cdecl Door_AttachToPortal(struct Door_s *ptDoor)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real64x3_t v24; };
    struct { char igi2_o1[24]; int v25; };
    struct { char igi2_o2[28]; struct QReference_s *v26; };
    struct { char igi2_o3[32]; struct real64x3_t v27; };
    struct { char igi2_o4[56]; struct QReference_s *pptSectorRef; };
    struct { char igi2_o5[60]; int ptStart; };
    struct { char igi2_o6[64]; struct real64x3_t ptStart_4; };
    struct { char igi2_o7[88]; struct real64x3_t ptPos; };
    struct { char igi2_o8[112]; struct real64x3_t ptEnd; };
    char igi2_extent[136];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QReference_s *ptSectorRef1; // eax
  _BYTE *pxObject; // eax
  unsigned __int16 iPortal1; // cx
  struct QReference_s *v4; // eax
  struct QReference_s *ptSectorRef2; // eax
  unsigned __int16 iPortal2; // cx
  _BYTE *v7; // eax
  struct QReference_s *v8; // eax
  char isLinkUpToPortal; // al
  struct LODVirModel_s *ptLODVirModel; // eax
  struct LODVirModel_s *v11; // eax
  unsigned __int16 v12; // di
  unsigned __int16 v13; // bx
  struct QReference_s *v14; // eax
  struct QReference_s *v15; // ecx
  void *v16; // edx
  unsigned int DoorStatus; // eax
  struct Mesh3D_Mesh_t *ptMesh; // eax
  double v19; // st7
  double v20; // st6
  double vX; // st7
  double v22; // st6
  double v23; // st5

  ptSectorRef1 = ptDoor->ptSectorRef1;
  if ( ptSectorRef1 )
  {
    pxObject = ptSectorRef1->pxObject;
    if ( pxObject )
    {
      iPortal1 = ptDoor->iPortal1;
      if ( iPortal1 != 0xFFFF )
        pxObject[iPortal1 + 328] = 1;
    }
    v4 = ptDoor->ptSectorRef1;
    if ( v4 )
    {
      QReference_Delete(v4, &QTask_tQTaskRefPool);
      ptDoor->ptSectorRef1 = nullptr;
    }
  }
  ptSectorRef2 = ptDoor->ptSectorRef2;
  if ( ptSectorRef2 )
  {
    iPortal2 = ptDoor->iPortal2;
    if ( iPortal2 != 0xFFFF )
    {
      v7 = ptSectorRef2->pxObject;
      if ( v7 )
        v7[iPortal2 + 328] = 1;
      v8 = ptDoor->ptSectorRef2;
      if ( v8 )
      {
        QReference_Delete(v8, &QTask_tQTaskRefPool);
        ptDoor->ptSectorRef2 = nullptr;
      }
    }
  }
  isLinkUpToPortal = ptDoor->isLinkUpToPortal;
  igi2_frame.ptStart = 0xFFFF;
  ptDoor->iPortal1 = -1;
  igi2_frame.v25 = 0xFFFF;
  ptDoor->iPortal2 = -1;
  igi2_frame.pptSectorRef = nullptr;
  ptDoor->ptSectorRef1 = nullptr;
  igi2_frame.v26 = nullptr;
  ptDoor->ptSectorRef2 = nullptr;
  ptDoor->isAttachedToPortal = 0;
  if ( isLinkUpToPortal )
  {
    ptLODVirModel = ptDoor->tRigidDynCubeObj.tModelObj.ptLODVirModel;
    if ( ptLODVirModel )
    {
      if ( ptLODVirModel->aptVirModel[0] )
      {
        if ( RigidDynCubeObj_IsTransparent(&ptDoor->tRigidDynCubeObj) == false )
        {
          v11 = ptDoor->tRigidDynCubeObj.tModelObj.ptLODVirModel;
          igi2_frame.v27.vX = v11->aptVirModel[0]->ptModel->ptMesh->tRenderMeshSphere.tPos.vX;
          igi2_frame.v27.vY = v11->aptVirModel[0]->ptModel->ptMesh->tRenderMeshSphere.tPos.vY;
          igi2_frame.v27.vZ = v11->aptVirModel[0]->ptModel->ptMesh->tRenderMeshSphere.tPos.vZ;
          qmemcpy(&igi2_frame.v24, &igi2_frame.v27, sizeof(igi2_frame.v24));
          igi2_frame.v27.vY = igi2_frame.v27.vY - 2048.0;
          igi2_frame.v24.vY = igi2_frame.v24.vY + 2048.0;
          igi2_frame.ptStart_4.vX = ptDoor->tOriginalOrientation.tX.vX * igi2_frame.v27.vX
                       + ptDoor->tOriginalOrientation.tX.vY * igi2_frame.v27.vY
                       + ptDoor->tOriginalOrientation.tX.vZ * igi2_frame.v27.vZ;
          igi2_frame.ptStart_4.vY = ptDoor->tOriginalOrientation.tY.vY * igi2_frame.v27.vY
                       + ptDoor->tOriginalOrientation.tY.vZ * igi2_frame.v27.vZ
                       + ptDoor->tOriginalOrientation.tY.vX * igi2_frame.v27.vX;
          igi2_frame.ptStart_4.vZ = ptDoor->tOriginalOrientation.tZ.vY * igi2_frame.v27.vY
                       + ptDoor->tOriginalOrientation.tZ.vZ * igi2_frame.v27.vZ
                       + ptDoor->tOriginalOrientation.tZ.vX * igi2_frame.v27.vX;
          qmemcpy(&igi2_frame.v27, &igi2_frame.ptStart_4, sizeof(igi2_frame.v27));
          igi2_frame.ptPos.vX = ptDoor->tOriginalOrientation.tX.vX * igi2_frame.v24.vX
                   + ptDoor->tOriginalOrientation.tX.vY * igi2_frame.v24.vY
                   + ptDoor->tOriginalOrientation.tX.vZ * igi2_frame.v24.vZ;
          igi2_frame.ptPos.vY = ptDoor->tOriginalOrientation.tY.vY * igi2_frame.v24.vY
                   + ptDoor->tOriginalOrientation.tY.vZ * igi2_frame.v24.vZ
                   + ptDoor->tOriginalOrientation.tY.vX * igi2_frame.v24.vX;
          igi2_frame.ptPos.vZ = ptDoor->tOriginalOrientation.tZ.vY * igi2_frame.v24.vY
                   + ptDoor->tOriginalOrientation.tZ.vZ * igi2_frame.v24.vZ
                   + ptDoor->tOriginalOrientation.tZ.vX * igi2_frame.v24.vX;
          qmemcpy(&igi2_frame.v24, &igi2_frame.ptPos, sizeof(igi2_frame.v24));
          igi2_frame.v27.vX = igi2_frame.ptStart_4.vX + ptDoor->tOriginalPosStart.vX;
          igi2_frame.v27.vY = igi2_frame.v27.vY + ptDoor->tOriginalPosStart.vY;
          igi2_frame.v27.vZ = igi2_frame.v27.vZ + ptDoor->tOriginalPosStart.vZ;
          igi2_frame.v24.vX = igi2_frame.ptPos.vX + ptDoor->tOriginalPosStart.vX;
          igi2_frame.v24.vY = igi2_frame.v24.vY + ptDoor->tOriginalPosStart.vY;
          igi2_frame.v24.vZ = igi2_frame.v24.vZ + ptDoor->tOriginalPosStart.vZ;
          Door_TraceForPortals(ptDoor, &igi2_frame.v27, &igi2_frame.v24, (unsigned __int16 *)&igi2_frame.ptStart, &igi2_frame.pptSectorRef, &igi2_frame.ptEnd);
          v12 = igi2_frame.ptStart;
          if ( (unsigned __int16)igi2_frame.ptStart < 0x40u )
          {
            if ( igi2_frame.pptSectorRef )
            {
              Door_TraceForPortals(ptDoor, &igi2_frame.v24, &igi2_frame.v27, (unsigned __int16 *)&igi2_frame.v25, &igi2_frame.v26, &igi2_frame.ptPos);
              v13 = igi2_frame.v25;
              if ( (unsigned __int16)igi2_frame.v25 < 0x40u )
              {
                v14 = igi2_frame.v26;
                if ( igi2_frame.v26 )
                {
                  v15 = igi2_frame.pptSectorRef;
                  ptDoor->ptSectorRef1 = igi2_frame.pptSectorRef;
                  ptDoor->iPortal1 = v12;
                  ptDoor->iPortal2 = v13;
                  ptDoor->ptSectorRef2 = v14;
                  v16 = v14->pxObject;
                  igi2_frame.v26 = (struct QReference_s *)v15->pxObject;
                  igi2_frame.v25 = (int)v16;
                  DoorStatus = Door_GetDoorStatus(&ptDoor->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask);
                  ptDoor->eStatus = DoorStatus;
                  LOBYTE(DoorStatus) = DoorStatus != 1;
                  *((_BYTE *)&igi2_frame.v26[27].ptPrev + v12) = DoorStatus;
                  *(_BYTE *)(v13 + igi2_frame.v25 + 328) = DoorStatus;
                  ptMesh = ptDoor->tRigidDynCubeObj.tModelObj.ptLODVirModel->aptVirModel[0]->ptModel->ptMesh;
                  *(float *)&igi2_frame.ptStart_4.vX = ptDoor->tOriginalOrientation.tX.vX * ptMesh->tRenderMeshSphere.tPos.vX
                                          + ptMesh->tRenderMeshSphere.tPos.vZ * ptDoor->tOriginalOrientation.tX.vZ
                                          + ptMesh->tRenderMeshSphere.tPos.vY * ptDoor->tOriginalOrientation.tX.vY;
                  *((float *)&igi2_frame.ptStart_4.vX + 1) = ptMesh->tRenderMeshSphere.tPos.vY * ptDoor->tOriginalOrientation.tY.vY
                                                + ptMesh->tRenderMeshSphere.tPos.vX * ptDoor->tOriginalOrientation.tY.vX
                                                + ptMesh->tRenderMeshSphere.tPos.vZ * ptDoor->tOriginalOrientation.tY.vZ;
                  v19 = ptDoor->tOriginalOrientation.tZ.vY * ptMesh->tRenderMeshSphere.tPos.vY
                      + ptMesh->tRenderMeshSphere.tPos.vZ * ptDoor->tOriginalOrientation.tZ.vZ;
                  v20 = ptMesh->tRenderMeshSphere.tPos.vX * ptDoor->tOriginalOrientation.tZ.vX;
                  igi2_frame.v27.vX = igi2_frame.ptStart_4.vX;
                  *(float *)&igi2_frame.ptStart_4.vY = v19 + v20;
                  vX = ptDoor->tOriginalPosStart.vX;
                  LODWORD(igi2_frame.v27.vY) = LODWORD(igi2_frame.ptStart_4.vY);
                  v22 = ptDoor->tOriginalPosStart.vY + *((float *)&igi2_frame.ptStart_4.vX + 1);
                  *(float *)&igi2_frame.v27.vY = ptDoor->tOriginalPosStart.vZ + *(float *)&igi2_frame.ptStart_4.vY;
                  igi2_frame.v24.vZ = igi2_frame.ptPos.vZ + igi2_frame.ptEnd.vZ;
                  igi2_frame.v24.vX = (igi2_frame.ptPos.vX + igi2_frame.ptEnd.vX) * 0.5;
                  igi2_frame.v24.vZ = igi2_frame.v24.vZ * 0.5;
                  igi2_frame.v24.vX = igi2_frame.v24.vX - (vX + *(float *)&igi2_frame.ptStart_4.vX);
                  igi2_frame.v24.vX = *(float *)(&ptDoor->iPortal2 + 1) * igi2_frame.v24.vX;
                  igi2_frame.v24.vY = *(float *)(&ptDoor->iPortal2 + 1) * ((igi2_frame.ptPos.vY + igi2_frame.ptEnd.vY) * 0.5 - v22);
                  v23 = *(float *)(&ptDoor->iPortal2 + 1) * (igi2_frame.v24.vZ - *(float *)&igi2_frame.v27.vY);
                  ptDoor->tPortalPos.vX = igi2_frame.v24.vX + ptDoor->tOriginalPosStart.vX;
                  ptDoor->tPortalPos.vY = igi2_frame.v24.vY + ptDoor->tOriginalPosStart.vY;
                  ptDoor->tPortalPos.vZ = v23 + ptDoor->tOriginalPosStart.vZ;
                }
              }
            }
          }
        }
      }
    }
  }
}

// source: j/0/objects/door.c:588  [size]
void __cdecl Door_GetSerializeParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = Door_ptSerializeParameterList;
}

// source: j/0/objects/door.c:606  [anchor-mhash]
void __cdecl Door_DeSerializeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  unsigned __int16 ptNext; // cx
  struct QTask_s *ptParent; // eax
  struct QTask_s *ptHead; // edx
  int v5; // eax
  int v6; // esi
  int v7; // eax
  char v8; // cl
  int ptNext_high; // ecx
  char v10; // al

  QTask_DeleteQTaskAndQTaskRefSafe((struct QReference_s **)&ptQTask[23]);
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[Serialize_eDeSerializeQTaskEvent][RigidDynCubeObj_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  ptNext = (unsigned __int16)ptQTask[24].ptNext;
  if ( ptNext != 0xFFFF )
  {
    ptParent = ptQTask[23].ptParent;
    if ( ptParent )
      ptHead = ptParent->tQTaskChildren.ptHead;
    else
      ptHead = nullptr;
    v5 = *(_DWORD *)&ptQTask[23].eQTaskType;
    if ( v5 )
      v6 = *(_DWORD *)(v5 + 8);
    else
      v6 = 0;
    if ( ptHead )
    {
      v7 = ptNext;
      if ( LOBYTE(ptQTask[23].tQTaskChildren.ptTail) )
      {
        v8 = *((_BYTE *)&ptHead[8].tQTaskChildren.ptHead + ptNext);
        if ( v8 <= 0 )
          *((_BYTE *)&ptHead[8].tQTaskChildren.ptHead + v7) = 0;
        else
          *((_BYTE *)&ptHead[8].tQTaskChildren.ptHead + v7) = v8 - 1;
      }
      else
      {
        ++*((_BYTE *)&ptHead[8].tQTaskChildren.ptHead + ptNext);
      }
    }
    if ( v6 )
    {
      ptNext_high = HIWORD(ptQTask[24].ptNext);
      if ( LOBYTE(ptQTask[23].tQTaskChildren.ptTail) )
      {
        v10 = *(_BYTE *)(ptNext_high + v6 + 328);
        if ( v10 <= 0 )
          *(_BYTE *)(ptNext_high + v6 + 328) = 0;
        else
          *(_BYTE *)(ptNext_high + v6 + 328) = v10 - 1;
      }
      else
      {
        ++*(_BYTE *)(ptNext_high + v6 + 328);
      }
    }
  }
}

void __cdecl sub_5420C0(struct QTask_s *a1, void *a2)
{
  ((void (__cdecl *)())QTask_aatQTaskFinalEvent[Serialize_eSerializeQTaskEvent][RigidDynCubeObj_eQTaskType].pfHandler)(a1, a2);
}

// source: j/0/objects/door.c:660  [anchor-mhash]
void __cdecl Door_OpenCloseDoorHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptParent; // eax
  struct QTask_s *ptHead; // esi
  int v5; // eax
  int v6; // ecx
  unsigned __int16 ptNext; // ax
  double v9; // st7
  unsigned __int8 v10; // c0
  unsigned __int8 v11; // c2
  struct QReference_s *ptQTaska = *(struct QReference_s * *)&ptQTask; // [esp+10h] [ebp+4h] ARGSLOT

  ptQTaska = ptQTask[10].tQTaskRefList.ptTail;
  ptParent = ptQTask[23].ptParent;
  if ( ptParent )
    ptHead = ptParent->tQTaskChildren.ptHead;
  else
    ptHead = nullptr;
  v5 = *(_DWORD *)&ptQTask[23].eQTaskType;
  if ( v5 )
    v6 = *(_DWORD *)(v5 + 8);
  else
    v6 = 0;
  if ( *(_DWORD *)pxContext )
  {
    ptQTask[10].tQTaskChildren.ptTail = (struct QTask_s *)1065353216;
    ptQTask[14].tQTaskChildren.ptMiddle = (struct QTask_s *)1065353216;
    ptNext = (unsigned __int16)ptQTask[24].ptNext;
    if ( ptNext != 0xFFFF && HIWORD(ptQTask[24].ptNext) != 0xFFFF )
    {
      *((_BYTE *)&ptHead[8].tQTaskChildren.ptHead + ptNext) = 1;
      *(_BYTE *)(HIWORD(ptQTask[24].ptNext) + v6 + 328) = 1;
    }
  }
  else
  {
    ptQTask[10].tQTaskChildren.ptTail = nullptr;
    ptQTask[14].tQTaskChildren.ptMiddle = nullptr;
  }
  if ( LOBYTE(ptQTask[10].tQTaskRefList.ptHead) )
  {
    v9 = *(float *)&ptQTask[10].tQTaskRefList.ptMiddle;
    if ( *((_DWORD *)pxContext + 1) )
    {
      if ( !(v10 | v11) )
        goto LABEL_19;
    }
    else if ( v10 | v11 )
    {
      v9 = -v9;
    }
    v9 = -v9;
LABEL_19:
    *(float *)&ptQTask[10].tQTaskRefList.ptTail = v9;
  }
  Door_SetPosition((struct Door_s *)ptQTask);
  ptQTask[10].tQTaskRefList.ptMiddle = ptQTaska;
}

void __cdecl sub_5421C0(struct QTask_s *ptQTask, void *eQTaskType)
{
  QTask_TriggerBaseHandler(ptQTask, ptQTask->eQTaskType, 5, eQTaskType);
}

// source: j/0/objects/door.c:717  [anchor-mhash]
void __cdecl Door_TraceLinesHandler(struct QTask_s *ptQTask, void *pxContext)
{
  __int16 v2; // ax
  int v3; // eax
  int v4; // eax
  int v5; // ebx
  int v6; // ecx
  int v7; // edx
  int v8; // eax
  double v9; // st7
  double v10; // st6
  bool v11; // c0
  bool v12; // c3

  if ( *((_WORD *)pxContext + 6) != Door_eAttachToPortalQTaskEvent )
  {
    v2 = AIGraph_eNodeLinkCheckQTaskEvent;
    if ( AIGraph_eNodeLinkCheckQTaskEvent == 512 )
    {
      v2 = QTask_NewQTaskEventFn(0, "AIGraph_NodeLinkCheck");
      AIGraph_eNodeLinkCheckQTaskEvent = v2;
    }
    if ( *((_WORD *)pxContext + 6) != v2 || !*(_BYTE *)(*((_DWORD *)pxContext + 4) + 8) )
    {
      QTask_TriggerBaseHandler(ptQTask, ptQTask->eQTaskType, 10, pxContext);
      if ( LOBYTE(ptQTask[23].tQTaskRefList.ptHead)
        && (*(float *)&ptQTask[10].tQTaskRefList.ptTail != 0.0 || !BYTE2(ptQTask[23].tQTaskRefList.ptHead))
        && *((_WORD *)pxContext + 6) == GameFunctions_eObjectCollisionEvaluateQTaskEvent )
      {
        v3 = *((_DWORD *)pxContext + 4);
        if ( v3 )
        {
          v4 = *(_DWORD *)(v3 + 4);
          if ( v4 )
          {
            if ( QTask_IsQTaskTypeDerived(*(_WORD *)(v4 + 36), Human_eQTaskType) )
            {
              v5 = 0;
              if ( *((int *)pxContext + 2) > 0 )
              {
                v6 = 0;
                v7 = 0;
                do
                {
                  v8 = v7 + *((_DWORD *)pxContext + 9);
                  if ( *(_DWORD *)(v8 + 92) && *(struct QTask_s **)v8 == ptQTask )
                  {
                    v9 = (*(double *)(v6 + *(_DWORD *)pxContext + 16) - *(double *)&ptQTask[1].tQTaskChildren.ptTail)
                       * *(float *)&ptQTask[3].ptParent
                       + (*(double *)(v6 + *(_DWORD *)pxContext + 8) - *(double *)&ptQTask[1].tQTaskChildren.ptHead)
                       * *(float *)&ptQTask[3].tQTaskRefList.ptHead
                       + (*(double *)(*(_DWORD *)pxContext + v6) - *(double *)&ptQTask[1].ptNext)
                       * *(float *)&ptQTask[3].tQTaskChildren.ptHead;
                    v10 = *(float *)&ptQTask[10].tQTaskRefList.ptTail;
                    v11 = v10 < 0.0;
                    v12 = v10 == 0.0;
                    if ( BYTE2(ptQTask[23].tQTaskRefList.ptHead) )
                    {
                      if ( !v11 && !v12 && v9 < 0.0 || *(float *)&ptQTask[10].tQTaskRefList.ptTail < 0.0 && v9 > 0.0 )
                        return;
                    }
                    else if ( !v11 && !v12 && v9 > 0.0 || *(float *)&ptQTask[10].tQTaskRefList.ptTail < 0.0 && v9 < 0.0 )
                    {
                      return;
                    }
                    ptQTask[23].tQTaskChildren.ptHead = (struct QTask_s *)15;
                  }
                  ++v5;
                  v7 += 120;
                  v6 += 24;
                }
                while ( v5 < (int)(*((_DWORD *)pxContext + 2)) );
              }
            }
          }
        }
      }
    }
  }
}

// source: j/0/objects/door.c:812  [anchor-mhash]
void __cdecl Door_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  double v2; // st7
  bool v3; // c0
  bool v4; // c3
  double v5; // st7
  double v6; // st7
  int *v7; // eax
  int v8; // eax
  double v9; // st6
  struct QTask_s **p_ptMiddle; // eax
  int v11; // ecx
  struct QReference_s *ptHead; // edi
  struct QReference_s *ptNext; // esi
  int v14; // eax
  float ptDynCubeObj; // [esp+0h] [ebp-18h]

  QTaskList_Register(GameFunctions_ptActivateQTaskList, (struct QTaskList_s *)ptQTask);
  ModelObj_Init((struct ModelObj_s *)ptQTask, Game_ptGame->ptWorld, nullptr);
  ptQTask[7].tQTaskChildren.ptHead = nullptr;
  ptQTask[7].tQTaskChildren.ptMiddle = (struct QTask_s *)2;
  ptQTask[7].tQTaskRefList.ptHead = nullptr;
  ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[7].tQTaskRefList.ptTail = nullptr;
  ptQTask[7].ptParent = nullptr;
  *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  v2 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  v3 = v2 < *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  v4 = v2 == *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  ptQTask[8].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[8].tQTaskRefList.ptTail = nullptr;
  ptQTask[8].ptParent = nullptr;
  *(_DWORD *)&ptQTask[8].eQTaskType = 0;
  ptQTask[9].ptNext = nullptr;
  ptQTask[9].ptPrev = nullptr;
  if ( v3 || v4 )
    v5 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  else
    v5 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  if ( v5 >= *(float *)&ptQTask[6].ptPrev )
  {
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
      v6 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v6 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  }
  else
  {
    v6 = *(float *)&ptQTask[6].ptPrev;
  }
  v7 = *(int **)&ptQTask[2].eQTaskType;
  if ( v7 && (v8 = *v7) != 0 )
    v9 = *(float *)(*(_DWORD *)(*(_DWORD *)(v8 + 12) + 12) + 120);
  else
    v9 = 1.0;
  ptDynCubeObj = v6 * v9;
  World_RegisterDynCubeObjFirstTimeRadius(
    Game_ptGame->ptWorld,
    (struct DynCubeObj_s *)ptQTask,
    (struct real64x3_t *)&ptQTask[8].tQTaskRefList.ptMiddle,
    ptDynCubeObj,
    WORLD_DYNCUBETREE_CATEGORY_MOBILE);
  ptQTask[3].tQTaskChildren.ptHead = nullptr;
  ptQTask[3].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[3].tQTaskChildren.ptTail = nullptr;
  ptQTask[3].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[3].tQTaskRefList.ptTail = nullptr;
  ptQTask[3].ptParent = nullptr;
  ptQTask[4].ptNext = nullptr;
  ptQTask[3].ptPrev = (struct QTask_s *)1065353216;
  ptQTask[3].tQTaskRefList.ptHead = (struct QReference_s *)1065353216;
  *(_DWORD *)&ptQTask[3].eQTaskType = 1065353216;
  BYTE1(ptQTask[10].tQTaskRefList.ptHead) = 0;
  LOBYTE(ptQTask[10].tQTaskRefList.ptHead) = 0;
  ptQTask[10].tQTaskRefList.ptTail = (struct QReference_s *)1119092736;
  ptQTask[10].ptParent = (struct QTask_s *)1056964608;
  LOBYTE(ptQTask[10].eQTaskType) = 0;
  ptQTask[14].ptPrev = nullptr;
  ptQTask[14].tQTaskChildren.ptHead = nullptr;
  ptQTask[9].tQTaskChildren.ptHead = nullptr;
  ptQTask[9].tQTaskChildren.ptMiddle = nullptr;
  BYTE2(ptQTask[23].tQTaskChildren.ptMiddle) = 0;
  HIBYTE(ptQTask[23].tQTaskChildren.ptTail) = 0;
  LOBYTE(ptQTask[23].tQTaskRefList.ptHead) = 1;
  HIBYTE(ptQTask[23].tQTaskRefList.ptHead) = 0;
  qmemcpy(&ptQTask[9].tQTaskChildren.ptTail, &ptQTask[3].ptPrev, sizeof(struct QTask_s));
  ptQTask[14].tQTaskRefList.ptHead = nullptr;
  ptQTask[14].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[14].tQTaskRefList.ptTail = nullptr;
  ptQTask[16].tQTaskChildren.ptTail = nullptr;
  ptQTask[16].tQTaskRefList.ptHead = nullptr;
  ptQTask[16].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[16].tQTaskRefList.ptTail = nullptr;
  ptQTask[18].tQTaskChildren.ptTail = nullptr;
  ptQTask[18].tQTaskRefList.ptHead = nullptr;
  ptQTask[18].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[18].tQTaskRefList.ptTail = nullptr;
  ptQTask[20].tQTaskChildren.ptTail = nullptr;
  BYTE2(ptQTask[23].tQTaskRefList.ptHead) = 0;
  ptQTask[20].tQTaskRefList.ptHead = (struct QReference_s *)1082130432;
  ptQTask[20].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[23].tQTaskChildren.ptHead = nullptr;
  ptQTask[10].tQTaskChildren.ptTail = nullptr;
  ptQTask[14].tQTaskChildren.ptTail = nullptr;
  p_ptMiddle = &ptQTask[11].tQTaskChildren.ptMiddle;
  v11 = 5;
  do
  {
    *(_BYTE *)p_ptMiddle = 0;
    p_ptMiddle += 4;
    --v11;
  }
  while ( v11 );
  strcpy((char *)&ptQTask[13].tQTaskChildren.ptMiddle, "tba_picklock");
  ptQTask[23].ptNext = nullptr;
  Door_AttachToParent((struct Door_s *)ptQTask);
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    ptHead = Flow_ptFlow->ptNetManagerQTask[6].tQTaskRefList.ptHead;
    ptNext = ptHead[4].ptNext;
    v14 = 0;
    while ( LOWORD(ptNext->ptNext) )
    {
      ++v14;
      ptNext = (struct QReference_s *)((char *)ptNext + 16);
      if ( v14 >= 256 )
      {
        LDebug_Error("Too many game items!");
        abort();
      }
    }
    LOWORD(ptNext->ptNext) = LOWORD(ptHead[3].ptPrev)++;
    ptNext->ptPrev = QTask_NewQTaskRef(ptQTask);
    LOWORD(ptNext->pxObject) = 2;
    ptNext[1].ptNext = nullptr;
    ++HIWORD(ptHead[3].ptPrev);
    LOWORD(ptHead[3].pxObject) += 8;
    ptQTask[23].ptPrev = (struct QTask_s *)LOWORD(ptNext->ptNext);
  }
  BYTE1(ptQTask[23].tQTaskRefList.ptHead) = 0;
  ptQTask[23].ptParent = nullptr;
  *(_DWORD *)&ptQTask[23].eQTaskType = 0;
  ptQTask[23].tQTaskRefList.ptTail = nullptr;
  LOBYTE(ptQTask[23].tQTaskChildren.ptTail) = 1;
  LOBYTE(ptQTask[23].tQTaskChildren.ptMiddle) = 1;
  LOWORD(ptQTask[24].ptNext) = -1;
  HIWORD(ptQTask[24].ptNext) = -1;
  BYTE1(ptQTask[23].tQTaskChildren.ptMiddle) = 1;
  ptQTask[24].ptPrev = (struct QTask_s *)1065353216;
}

// source: j/0/objects/door.c:922  [anchor-mhash]
void __cdecl Door_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptParent; // eax
  struct QReference_s *v2; // eax
  int v3; // ecx
  struct QReference_s *v4; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax

  QTask_DeleteQTaskAndQTaskRefSafe((struct QReference_s **)&ptQTask[23]);
  ptParent = ptQTask[23].ptParent;
  if ( ptParent )
  {
    QReference_Delete((struct QReference_s *)ptParent, &QTask_tQTaskRefPool);
    ptQTask[23].ptParent = nullptr;
  }
  v2 = *(struct QReference_s **)&ptQTask[23].eQTaskType;
  if ( v2 )
  {
    QReference_Delete(v2, &QTask_tQTaskRefPool);
    *(_DWORD *)&ptQTask[23].eQTaskType = 0;
  }
  QTaskList_Remove(GameFunctions_ptActivateQTaskList, ptQTask);
  if ( *(_DWORD *)&ptQTask[2].eQTaskType )
  {
    ModelObj_SetLODVirModel((struct ModelObj_s *)ptQTask, nullptr, false);
    ptQTask[7].tQTaskRefList.ptHead = nullptr;
    ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
    ptQTask[7].tQTaskRefList.ptTail = nullptr;
    ptQTask[7].ptParent = nullptr;
    *(_DWORD *)&ptQTask[7].eQTaskType = 0;
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
  if ( v3 >= 0 )
  {
    pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Level_eRemoveLevelScriptSymbolsEvent][ptQTask->eQTaskType].pfHandler;
    if ( pfHandler )
      pfHandler(ptQTask);
  }
LABEL_15:
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[14].tQTaskRefList);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[16].tQTaskRefList);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[18].tQTaskRefList);
  World_RemoveDynCubeObj((struct World_s *)ptQTask[2].ptParent, (struct DynCubeObj_s *)ptQTask);
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
    NetworkGameItem_RemoveGameItem((int)ptQTask[23].ptPrev);
}

// source: j/0/objects/door.c:973  [anchor-caller]
void __cdecl Door_EvaluateActivateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { double Real64x3_RotateInverse_tTemp; };
    struct { char igi2_o1[16]; double Real64x3_RotateInverse_tTemp_16; };
    struct { char igi2_o2[16]; double Real64x3_RotateInverse_tTemp_16a; };
    struct { char igi2_o3[24]; struct real64x3_t tPos; };
    char igi2_extent[48];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v2; // st7
  double v3; // st6
  double v4; // st5
  double v5; // st7
  double v6; // st6

  if ( !BYTE2(ptQTask[23].tQTaskChildren.ptMiddle) || Door_IsPickable(ptQTask) )
  {
    GameFunctions_GetMagicVertex(&igi2_frame.tPos, ptQTask, 0);
    v2 = *((double *)pxContext + 1) - igi2_frame.tPos.vX;
    v3 = *((double *)pxContext + 2) - igi2_frame.tPos.vY;
    v4 = *((double *)pxContext + 3) - igi2_frame.tPos.vZ;
    igi2_frame.Real64x3_RotateInverse_tTemp = *(float *)&ptQTask[3].ptPrev * v2
                                 + *(float *)&ptQTask[3].tQTaskRefList.ptTail * v4
                                 + *(float *)&ptQTask[3].tQTaskChildren.ptTail * v3;
    igi2_frame.Real64x3_RotateInverse_tTemp_16 = *(float *)&ptQTask[3].eQTaskType * v4
                                    + *(float *)&ptQTask[3].tQTaskChildren.ptMiddle * v2
                                    + *(float *)&ptQTask[3].tQTaskRefList.ptMiddle * v3;
    if ( igi2_frame.Real64x3_RotateInverse_tTemp > -4096.0
      && igi2_frame.Real64x3_RotateInverse_tTemp < 1843.2
      && igi2_frame.Real64x3_RotateInverse_tTemp_16 > -4096.0
      && igi2_frame.Real64x3_RotateInverse_tTemp_16 < 4096.0 )
    {
      GameFunctions_ResolveEvaluateActivate((struct EvaluateActivateContext_t *)pxContext, ptQTask, &igi2_frame.tPos);
      v5 = *(float *)&ptQTask[3].tQTaskChildren.ptMiddle * igi2_frame.Real64x3_RotateInverse_tTemp_16
         + *(float *)&ptQTask[3].ptPrev * igi2_frame.Real64x3_RotateInverse_tTemp
         + *(float *)&ptQTask[3].tQTaskChildren.ptHead * 0.0;
      v6 = *(float *)&ptQTask[3].tQTaskRefList.ptMiddle * igi2_frame.Real64x3_RotateInverse_tTemp_16
         + *(float *)&ptQTask[3].tQTaskChildren.ptTail * igi2_frame.Real64x3_RotateInverse_tTemp
         + *(float *)&ptQTask[3].tQTaskRefList.ptHead * 0.0;
      igi2_frame.Real64x3_RotateInverse_tTemp_16a = *(float *)&ptQTask[3].eQTaskType * igi2_frame.Real64x3_RotateInverse_tTemp_16
                                       + *(float *)&ptQTask[3].tQTaskRefList.ptTail * igi2_frame.Real64x3_RotateInverse_tTemp
                                       + *(float *)&ptQTask[3].ptParent * 0.0;
      igi2_frame.tPos.vX = v5 + igi2_frame.tPos.vX;
      igi2_frame.tPos.vY = v6 + igi2_frame.tPos.vY;
      igi2_frame.tPos.vZ = igi2_frame.Real64x3_RotateInverse_tTemp_16a + igi2_frame.tPos.vZ;
      GameFunctions_ResolveEvaluateActivate((struct EvaluateActivateContext_t *)pxContext, ptQTask, &igi2_frame.tPos);
    }
  }
}

// source: j/0/objects/door.c:1031  [size]
void __cdecl Door_GetActivateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = 2;
}

// source: j/0/objects/door.c:1048  [size]
void __cdecl Door_ActivateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: j/0/objects/door.c:1071  [anchor-mhash]
void __cdecl Door_RunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // ecx
  int v2; // edx
  struct QTask_s *v3; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v5; // edx
  char ptTail; // al
  struct QTask_s *v7; // eax
  double v8; // st7
  int v9; // ecx
  double v10; // st7
  bool v11; // al
  struct QTask_s *v12; // eax
  struct QTask_s *v13; // eax
  struct QTask_s *v14; // eax
  struct QTask_s *ptNext; // eax
  struct QTask_s *v16; // esi
  struct QTask_s *v17; // eax
  struct QTask_s *v18; // eax
  struct QReference_s *DoorStatus; // edi
  double v20; // st7
  struct QTask_s *v21; // esi
  double v22; // st6
  double v23; // st5
  double v24; // st4
  double v25; // st3
  struct QTask_s *ptParent; // eax
  struct QTask_s *v27; // eax
  int v28; // ecx
  int v29; // edx
  int ptNext_low; // esi
  char v31; // cl
  int ptNext_high; // ecx
  char v33; // al
  struct real64x3_t *eDoorStatus; // [esp+10h] [ebp-28h]
  double v35; // [esp+30h] [ebp-8h]

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
  ptTail = (char)ptQTask[23].tQTaskChildren.ptTail;
  BYTE1(ptQTask[23].tQTaskChildren.ptTail) = HIBYTE(ptQTask[23].tQTaskChildren.ptMiddle);
  eDoorStatus = (struct real64x3_t *)&ptQTask[1];
  qmemcpy(&ptQTask[22].tQTaskChildren.ptTail, &ptQTask[1], 0x18u);
  BYTE2(ptQTask[23].tQTaskChildren.ptTail) = ptTail;
  qmemcpy(&ptQTask[20].tQTaskRefList.ptTail, &ptQTask[3].ptPrev, sizeof(struct QTask_s));
  if ( ptTail
    && ptQTask[14].tQTaskRefList.ptHead
    && ptQTask[14].tQTaskRefList.ptMiddle->ptNext
    && ptQTask[14].tQTaskRefList.ptTail
    && Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[14].tQTaskRefList, ptQTask) != 0.0 )
  {
    BYTE1(ptQTask[23].tQTaskRefList.ptHead) |= BYTE2(ptQTask[23].tQTaskRefList.ptHead) == 0;
    BYTE2(ptQTask[23].tQTaskRefList.ptHead) = 1;
  }
  if ( HIBYTE(ptQTask[23].tQTaskChildren.ptMiddle) )
  {
    ++*(int *)&ptQTask[20].tQTaskRefList.ptMiddle;
    if ( ptQTask[16].tQTaskRefList.ptHead
      && ptQTask[16].tQTaskRefList.ptMiddle->ptNext
      && ptQTask[16].tQTaskRefList.ptTail
      && Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[16].tQTaskRefList, ptQTask) != 0.0 )
    {
      BYTE1(ptQTask[23].tQTaskRefList.ptHead) |= BYTE2(ptQTask[23].tQTaskRefList.ptHead);
      BYTE2(ptQTask[23].tQTaskRefList.ptHead) = 0;
    }
  }
  else
  {
    ptQTask[20].tQTaskRefList.ptMiddle = nullptr;
  }
  if ( ptQTask[18].tQTaskRefList.ptHead
    && ptQTask[18].tQTaskRefList.ptMiddle->ptNext
    && ptQTask[18].tQTaskRefList.ptTail )
  {
    BYTE2(ptQTask[23].tQTaskChildren.ptMiddle) = (__int64)Level_RunLevelExpression(
                                                            (struct LevelExpression_s *)&ptQTask[18].tQTaskRefList,
                                                            ptQTask);
  }
  if ( HIBYTE(ptQTask[23].tQTaskChildren.ptTail) )
    BYTE2(ptQTask[23].tQTaskChildren.ptMiddle) = 0;
  v7 = ptQTask[23].tQTaskChildren.ptHead;
  if ( v7 )
  {
    ptQTask[14].tQTaskChildren.ptMiddle = ptQTask[10].tQTaskChildren.ptTail;
    ptQTask[23].tQTaskChildren.ptHead = (struct QTask_s *)((char *)v7 - 1);
  }
  else if ( BYTE2(ptQTask[23].tQTaskRefList.ptHead) )
  {
    ptQTask[14].tQTaskChildren.ptMiddle = (struct QTask_s *)1065353216;
  }
  else
  {
    ptQTask[14].tQTaskChildren.ptMiddle = nullptr;
  }
  if ( *(float *)&ptQTask[10].tQTaskChildren.ptTail == *(float *)&ptQTask[14].tQTaskChildren.ptMiddle )
  {
    ptQTask[10].tQTaskChildren.ptTail = ptQTask[14].tQTaskChildren.ptMiddle;
    v9 = 0;
    goto LABEL_43;
  }
  if ( *(float *)&ptQTask[10].tQTaskChildren.ptTail >= (double)*(float *)&ptQTask[14].tQTaskChildren.ptMiddle )
  {
    if ( *(float *)&ptQTask[10].tQTaskChildren.ptTail > (double)*(float *)&ptQTask[14].tQTaskChildren.ptMiddle )
    {
      v10 = *(float *)&ptQTask[10].tQTaskChildren.ptTail - 1.0 / (*(float *)&ptQTask[10].ptParent * 30.0);
      *(float *)&ptQTask[10].tQTaskChildren.ptTail = v10;
      if ( v10 < *(float *)&ptQTask[14].tQTaskChildren.ptMiddle )
        ptQTask[10].tQTaskChildren.ptTail = ptQTask[14].tQTaskChildren.ptMiddle;
    }
    goto LABEL_41;
  }
  v8 = 1.0 / (*(float *)&ptQTask[10].ptParent * 30.0) + *(float *)&ptQTask[10].tQTaskChildren.ptTail;
  *(float *)&ptQTask[10].tQTaskChildren.ptTail = v8;
  if ( v8 <= *(float *)&ptQTask[14].tQTaskChildren.ptMiddle )
  {
LABEL_41:
    Door_SetPosition((struct Door_s *)ptQTask);
    v9 = 1;
    goto LABEL_43;
  }
  ptQTask[10].tQTaskChildren.ptTail = ptQTask[14].tQTaskChildren.ptMiddle;
  Door_SetPosition((struct Door_s *)ptQTask);
  v9 = 1;
LABEL_43:
  if ( *(float *)&ptQTask[14].tQTaskChildren.ptMiddle == *(float *)&ptQTask[10].tQTaskChildren.ptTail )
  {
    v11 = *(float *)&ptQTask[14].tQTaskChildren.ptMiddle == 0.0;
    LOBYTE(ptQTask[23].tQTaskChildren.ptTail) = v11;
    HIBYTE(ptQTask[23].tQTaskChildren.ptMiddle) = !v11;
  }
  else
  {
    LOBYTE(ptQTask[23].tQTaskChildren.ptTail) = 0;
    HIBYTE(ptQTask[23].tQTaskChildren.ptMiddle) = 0;
  }
  if ( v9 && !*(_DWORD *)&ptQTask[2].eQTaskType )
    return;
  if ( BYTE1(ptQTask[23].tQTaskRefList.ptHead) )
  {
    v12 = SoundSys_NewSoundFn(
            ptQTask,
            (char *)&ptQTask[11].tQTaskChildren.ptMiddle
          + 16 * (4 - (BYTE2(ptQTask[23].tQTaskRefList.ptHead) != 0)));
    BYTE1(ptQTask[23].tQTaskRefList.ptHead) = 0;
    if ( v12 )
      ((void (__cdecl *)(struct QTask_s *, struct real64x3_t *))QTask_aatQTaskFinalEvent[SoundSys_eSetPositionQTaskEvent][v12->eQTaskType].pfHandler)(
        v12,
        eDoorStatus);
  }
  if ( LOBYTE(ptQTask[23].tQTaskChildren.ptTail) )
  {
    if ( !BYTE2(ptQTask[23].tQTaskChildren.ptTail) )
    {
      v13 = SoundSys_NewSoundFn(ptQTask, (char *)&ptQTask[11].tQTaskRefList.ptTail);
      if ( v13 )
        SoundSys_SetSoundPosition(v13, eDoorStatus);
    }
  }
  if ( HIBYTE(ptQTask[23].tQTaskChildren.ptMiddle) )
  {
    if ( !BYTE1(ptQTask[23].tQTaskChildren.ptTail) )
    {
      v14 = SoundSys_NewSoundFn(ptQTask, (char *)&ptQTask[11].tQTaskChildren.ptMiddle);
      if ( v14 )
        SoundSys_SetSoundPosition(v14, eDoorStatus);
    }
  }
  if ( LOBYTE(ptQTask[23].tQTaskChildren.ptTail) || HIBYTE(ptQTask[23].tQTaskChildren.ptMiddle) )
  {
    QTask_DeleteQTaskAndQTaskRefSafe((struct QReference_s **)&ptQTask[23]);
  }
  else
  {
    ptNext = ptQTask[23].ptNext;
    if ( !ptNext || !ptNext->tQTaskChildren.ptHead )
    {
      v16 = SoundSys_NewSoundFn(ptQTask, (char *)&ptQTask[12].ptPrev);
      if ( v16 )
      {
        v17 = ptQTask[23].ptNext;
        if ( v17 )
        {
          QReference_Delete((struct QReference_s *)v17, &QTask_tQTaskRefPool);
          ptQTask[23].ptNext = nullptr;
        }
        ptQTask[23].ptNext = (struct QTask_s *)QTask_NewQTaskRef(v16);
        SoundSys_SetSoundPosition(v16, eDoorStatus);
      }
    }
  }
  v18 = ptQTask[3].ptNext;
  if ( v18 )
    ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][v18->eQTaskType].pfHandler)(ptQTask[3].ptNext);
  if ( LOWORD(ptQTask[24].ptNext) == 0xFFFF )
    return;
  DoorStatus = (struct QReference_s *)Door_GetDoorStatus(ptQTask);
  if ( Game_ptGame )
  {
    v20 = *(double *)&ptQTask[8].ptNext - Game_ptGame->tQCamera.tPos.vX;
    v21 = (struct QTask_s *)((char *)ptQTask + 872);
    v22 = *(double *)&ptQTask[8].tQTaskChildren.ptHead - Game_ptGame->tQCamera.tPos.vY;
    v23 = *(double *)&ptQTask[8].tQTaskChildren.ptTail - Game_ptGame->tQCamera.tPos.vZ;
    v24 = *(double *)&ptQTask[21].ptParent - Game_ptGame->tQCamera.tPos.vX;
    v25 = *(double *)&ptQTask[22].ptNext - Game_ptGame->tQCamera.tPos.vY;
    v35 = *(double *)&ptQTask[22].tQTaskChildren.ptHead - Game_ptGame->tQCamera.tPos.vZ;
    if ( v35 * v35 + v25 * v25 + v24 * v24 < v23 * v23 + v22 * v22 + v20 * v20 && DoorStatus == (struct QReference_s *)1 )
    {
      if ( ptQTask[23].tQTaskRefList.ptTail )
        goto LABEL_79;
      ptQTask[23].tQTaskRefList.ptTail = (struct QReference_s *)1;
    }
    else
    {
      if ( !ptQTask[23].tQTaskRefList.ptTail )
        goto LABEL_79;
      v21 = ptQTask + 8;
      ptQTask[23].tQTaskRefList.ptTail = nullptr;
    }
    qmemcpy(&ptQTask[8].tQTaskRefList.ptMiddle, v21, 0x18u);
    Door_SetPosition((struct Door_s *)ptQTask);
  }
LABEL_79:
  if ( DoorStatus == ptQTask[23].tQTaskRefList.ptMiddle )
    return;
  ptParent = ptQTask[23].ptParent;
  if ( ptParent )
    v27 = ptParent->tQTaskChildren.ptHead;
  else
    v27 = nullptr;
  v28 = *(_DWORD *)&ptQTask[23].eQTaskType;
  if ( v28 )
    v29 = *(_DWORD *)(v28 + 8);
  else
    v29 = 0;
  if ( v27 && v29 )
  {
    if ( DoorStatus == (struct QReference_s *)2 )
    {
      ++*((_BYTE *)&v27[8].tQTaskChildren.ptHead + LOWORD(ptQTask[24].ptNext));
      ++*(_BYTE *)(HIWORD(ptQTask[24].ptNext) + v29 + 328);
      ptQTask[23].tQTaskRefList.ptMiddle = (struct QReference_s *)2;
      return;
    }
    if ( DoorStatus == (struct QReference_s *)1 )
    {
      ptNext_low = LOWORD(ptQTask[24].ptNext);
      v31 = *((_BYTE *)&v27[8].tQTaskChildren.ptHead + ptNext_low);
      if ( v31 <= 0 )
        *((_BYTE *)&v27[8].tQTaskChildren.ptHead + ptNext_low) = 0;
      else
        *((_BYTE *)&v27[8].tQTaskChildren.ptHead + ptNext_low) = v31 - 1;
      ptNext_high = HIWORD(ptQTask[24].ptNext);
      v33 = *(_BYTE *)(ptNext_high + v29 + 328);
      if ( v33 > 0 )
      {
        *(_BYTE *)(ptNext_high + v29 + 328) = v33 - 1;
        ptQTask[23].tQTaskRefList.ptMiddle = (struct QReference_s *)1;
        return;
      }
      *(_BYTE *)(ptNext_high + v29 + 328) = 0;
    }
  }
  ptQTask[23].tQTaskRefList.ptMiddle = DoorStatus;
}

// source: j/0/objects/door.c:1406  [anchor-caller]
void __cdecl Door_UpdateInternalDataAfterLoadHandler(struct QTask_s *ptQTask)
{
  Door_AttachToPortal((struct Door_s *)ptQTask);
  LOBYTE(ptQTask[23].tQTaskChildren.ptMiddle) = 0;
}

// source: j/0/objects/door.c:1423  [anchor-mhash]
void __cdecl Door_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct LODVirModel_s *LODVirModelExistsFn; // eax
  double v3; // st7
  double v4; // st6
  long double v5; // st5
  long double v6; // st7
  char ptMiddle; // al

  qmemcpy(&ptQTask[8].tQTaskRefList.ptMiddle, &ptQTask[8], 0x18u);
  LODVirModelExistsFn = MTP_GetLODVirModelExistsFn((char *)&ptQTask[10].eQTaskType);
  if ( LODVirModelExistsFn != *(struct LODVirModel_s **)&ptQTask[2].eQTaskType )
  {
    ModelObj_SetLODVirModel((struct ModelObj_s *)ptQTask, LODVirModelExistsFn, false);
    ptQTask[7].tQTaskRefList.ptHead = nullptr;
    ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
    ptQTask[7].tQTaskRefList.ptTail = nullptr;
    ptQTask[7].ptParent = nullptr;
    *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  }
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[14].tQTaskRefList, ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[16].tQTaskRefList, ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[18].tQTaskRefList, ptQTask);
  v3 = *(float *)&ptQTask[9].tQTaskChildren.ptMiddle;
  v4 = *(float *)&ptQTask[9].tQTaskChildren.ptHead;
  LOBYTE(ptQTask[23].tQTaskChildren.ptTail) = 1;
  BYTE2(ptQTask[23].tQTaskChildren.ptTail) = 1;
  HIBYTE(ptQTask[23].tQTaskChildren.ptMiddle) = 0;
  BYTE2(ptQTask[23].tQTaskRefList.ptHead) = 0;
  BYTE1(ptQTask[23].tQTaskChildren.ptTail) = 0;
  v5 = sqrt(v4 * v4 + v3 * v3);
  v6 = v5;
  if ( v5 < 0.0 )
    v6 = -v5;
  *(float *)&ptQTask[14].tQTaskChildren.ptTail = v6;
  QTask_DeleteQTaskAndQTaskRefSafe((struct QReference_s **)&ptQTask[23]);
  qmemcpy(&ptQTask[22].tQTaskChildren.ptTail, &ptQTask[1], 0x18u);
  qmemcpy(&ptQTask[20].tQTaskRefList.ptTail, &ptQTask[3].ptPrev, sizeof(struct QTask_s));
  Door_AttachToParent((struct Door_s *)ptQTask);
  Door_SetPosition((struct Door_s *)ptQTask);
  ptMiddle = (char)ptQTask[23].tQTaskChildren.ptMiddle;
  ptQTask[10].tQTaskRefList.ptMiddle = ptQTask[10].tQTaskRefList.ptTail;
  if ( !ptMiddle )
    Door_AttachToPortal((struct Door_s *)ptQTask);
}

// source: j/0/objects/door.c:1486  [anchor-mhash]
void __cdecl Door_RemoveHandler(struct QTask_s *ptQTask, void *pxContext)
{
  unsigned __int16 ptNext; // si
  struct QTask_s *ptParent; // eax
  struct QTask_s *ptHead; // ecx
  int v5; // eax
  int v6; // eax

  ptNext = (unsigned __int16)ptQTask[24].ptNext;
  if ( ptNext != 0xFFFF )
  {
    ptParent = ptQTask[23].ptParent;
    if ( ptParent )
      ptHead = ptParent->tQTaskChildren.ptHead;
    else
      ptHead = nullptr;
    v5 = *(_DWORD *)&ptQTask[23].eQTaskType;
    if ( v5 )
      v6 = *(_DWORD *)(v5 + 8);
    else
      v6 = 0;
    if ( ptHead )
      *((_BYTE *)&ptHead[8].tQTaskChildren.ptHead + ptNext) = 1;
    if ( v6 )
      *(_BYTE *)(HIWORD(ptQTask[24].ptNext) + v6 + 328) = 1;
    ptQTask[23].tQTaskRefList.ptMiddle = nullptr;
  }
  ((void (__cdecl *)(struct QTask_s *, ...))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRemoveQTaskEvent][RigidDynCubeObj_eQTaskType].pfHandler)(ptQTask, pxContext);
}

// source: j/0/objects/door.c:1540  [size]
void __cdecl Door_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = Door_ptParameterList;
}

// source: j/0/objects/door.c:1556  [anchor-mhash]
void __cdecl Door_RegisterScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( !HIBYTE(ptQTask[23].tQTaskRefList.ptHead) )
  {
    HIBYTE(ptQTask[23].tQTaskRefList.ptHead) = 1;
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.isLocked", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      (char *)&ptQTask[23].tQTaskChildren.ptMiddle + 2,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.isOpen", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      (char *)&ptQTask[23].tQTaskChildren.ptMiddle + 3,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.isClosed", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      &ptQTask[23].tQTaskChildren.ptTail,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.isLastClosed", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      (char *)&ptQTask[23].tQTaskChildren.ptTail + 2,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.isLastOpen", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      (char *)&ptQTask[23].tQTaskChildren.ptTail + 1,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.isPicked", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      (char *)&ptQTask[23].tQTaskChildren.ptTail + 3,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.nDoorOpenTicks", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int,
      &ptQTask[20].tQTaskRefList.ptMiddle,
      4,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
  }
}

// source: j/0/objects/door.c:1604  [anchor-mhash]
void __cdecl Door_RemoveScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( HIBYTE(ptQTask[23].tQTaskRefList.ptHead) )
  {
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    HIBYTE(ptQTask[23].tQTaskRefList.ptHead) = 0;
    sprintf(igi2_frame.zTemp, "%s.isLocked", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.isOpen", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.isClosed", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.isLastClosed", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.isLastOpen", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.isPicked", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.nDoorOpenTicks", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    HIBYTE(ptQTask[23].tQTaskRefList.ptHead) = 0;
  }
}

// source: j/0/objects/door.c:1659  [anchor-mhash]
void __cdecl Door_UpdateAttachmentHandler(struct QTask_s *ptQTask)
{
  ModelObj_UpdateAttachment((struct ModelObj_s *)ptQTask);
  qmemcpy(&ptQTask[9].tQTaskChildren.ptTail, &ptQTask[3].ptPrev, sizeof(struct QTask_s));
  qmemcpy(&ptQTask[8].tQTaskRefList.ptMiddle, &ptQTask[1], 0x18u);
  qmemcpy(&ptQTask[8], &ptQTask[1], 0x18u);
  Door_SetPosition((struct Door_s *)ptQTask);
  ModelObj_UpdateAttachments((struct ModelObj_s *)ptQTask);
}

// source: j/0/objects/door.c:1691  [anchor-mhash]
void __cdecl Door_AIFindActivateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  double v2; // st5
  double v3; // st3
  double v4; // st4
  double v5; // st3
  double v6; // st4

  v2 = *((double *)pxContext + 2) - *(double *)&ptQTask[1].tQTaskChildren.ptTail;
  v3 = *((double *)pxContext + 1) - *(double *)&ptQTask[1].tQTaskChildren.ptHead;
  v4 = v2 * v2 + v3 * v3;
  v5 = *(double *)pxContext - *(double *)&ptQTask[1].ptNext;
  v6 = v4 + v5 * v5;
  if ( *((double *)pxContext + 3) < 0.0 || v6 < *((double *)pxContext + 3) )
  {
    *((_DWORD *)pxContext + 8) = ptQTask;
    *((double *)pxContext + 3) = v6;
  }
}

// source: j/0/objects/door.c:1767  [size]
void __cdecl Door_DrawActionItemHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ActionMenuScreen_DrawActionItem(
    ActionMenuScreen_ptQTask,
    (struct QSprite_s *)&StatusScreen_ptStatusScreenQTask[15].ptPrev
  + (BYTE2(ptQTask[23].tQTaskChildren.ptMiddle) != 0 ? 2 : 5),
    pxContext);
}

// source: j/0/objects/door.c:1787  [size]
unsigned __int16 __cdecl Door_GetQTaskType()
{
  return Door_eQTaskType;
}

// source: j/0/objects/door.c:1802  [size]
struct real64x3_t *__cdecl Door_GetActivatePosAndOrientation(
        struct QTask_s *ptQTask,
        struct real64x3_t *ptPos,
        struct real32x9_t *ptOrientation)
{
  qmemcpy(ptOrientation, &ptQTask[3].ptPrev, sizeof(struct real32x9_t));
  return GameFunctions_GetMagicVertex(ptPos, ptQTask, 0);
}

// source: j/0/objects/door.c:1825  [size]
float __cdecl Door_GetActivateTime(struct QTask_s *ptQTask)
{
  return *(float *)&ptQTask[20].tQTaskRefList.ptHead;
}

// source: j/0/objects/door.c:1841  [size]
enum bool __cdecl Door_IsLocked(struct QTask_s *ptQTask)
{
  return SBYTE2(ptQTask[23].tQTaskChildren.ptMiddle);
}

// source: j/0/objects/door.c:1857  [anchor-callee]
enum bool __cdecl Door_IsPickable(struct QTask_s *ptQTask)
{
  return (!HIBYTE(ptQTask[23].tQTaskChildren.ptMiddle) || *(float *)&ptQTask[10].tQTaskChildren.ptTail <= 0.6000000238418579)
      && !BYTE2(ptQTask[23].tQTaskRefList.ptHead)
      && LOBYTE(ptQTask[23].tQTaskChildren.ptTail)
      && BYTE1(ptQTask[10].tQTaskRefList.ptHead);
}

// source: j/0/objects/door.c:1873  [size]
void __cdecl Door_SetPicked(struct QTask_s *ptQTask, enum bool isPicked)
{
  HIBYTE(ptQTask[23].tQTaskChildren.ptTail) = isPicked;
}

// source: j/0/objects/door.c:1891  [anchor-callee]
int __cdecl Door_GetDoorStatus(struct QTask_s *ptQTask)
{
  if ( HIBYTE(ptQTask[23].tQTaskChildren.ptMiddle) && *(float *)&ptQTask[10].tQTaskChildren.ptTail > 0.6000000238418579 )
    return 0;
  if ( BYTE2(ptQTask[23].tQTaskRefList.ptHead) )
    return 2;
  return 2 * (LOBYTE(ptQTask[23].tQTaskChildren.ptTail) == 0) + 1;
}

// source: j/0/objects/door.c:1924  [size]
struct QTask_s *__cdecl Door_ToggleOpenDoor(struct QTask_s *ptQTask)
{
  BYTE2(ptQTask[23].tQTaskRefList.ptHead) ^= 1u;
  BYTE1(ptQTask[23].tQTaskRefList.ptHead) = 1;
  return ptQTask;
}

// source: j/0/objects/door.c:1944  [anchor-callee]
void __cdecl Door_ToggleOpenDoorEx(
        struct QTask_s *ptQTask,
        struct real64x3_t *ptOpenerPos)
{
  bool v2; // zf
  double v3; // st4
  char v4; // fps^1
  bool v5; // c0
  char v6; // c2
  bool v7; // c3
  char v8; // ah
  double v10; // st7
  unsigned __int8 v11; // c0
  unsigned __int8 v12; // c2

  v2 = BYTE2(ptQTask[23].tQTaskRefList.ptHead) == 1;
  BYTE2(ptQTask[23].tQTaskRefList.ptHead) ^= 1u;
  BYTE1(ptQTask[23].tQTaskRefList.ptHead) = 1;
  if ( !v2 )
  {
    if ( LOBYTE(ptQTask[10].tQTaskRefList.ptHead) )
    {
      v3 = *(float *)&ptQTask[10].ptPrev * (ptOpenerPos->vZ - *(double *)&ptQTask[9].ptNext)
         + *(float *)&ptQTask[9].ptParent * (ptOpenerPos->vY - *(double *)&ptQTask[8].ptParent)
         + *(float *)&ptQTask[9].tQTaskRefList.ptHead
         * (ptOpenerPos->vX - *(double *)&ptQTask[8].tQTaskRefList.ptMiddle);
      v5 = v3 < 0.0;
      v6 = 0;
      v7 = v3 == 0.0;
      v4 = (char)(v5 | (v6 << 2) | (v7 << 6));
      v8 = v4;
      v10 = *(float *)&ptQTask[10].tQTaskRefList.ptMiddle;
      if ( __SETP__(v8 & 5, 0) )
      {
        if ( v11 | v12 )
          v10 = -v10;
        *(float *)&ptQTask[10].tQTaskRefList.ptTail = -v10;
      }
      else
      {
        if ( v11 | v12 )
          v10 = -v10;
        *(float *)&ptQTask[10].tQTaskRefList.ptTail = v10;
      }
    }
    else
    {
      ptQTask[10].tQTaskRefList.ptTail = ptQTask[10].tQTaskRefList.ptMiddle;
    }
  }
}

// source: j/0/objects/door.c:1984  [size]
__int16 __cdecl Door_GetOpenCloseDoorQTaskEvent()
{
  return Door_eOpenCloseDoorQTaskEvent;
}

// source: j/0/objects/door.c:1998  [size]
char *__cdecl Door_GetActivateSound(struct QTask_s *ptQTask)
{
  return (char *)&ptQTask[13].tQTaskChildren.ptMiddle;
}

BOOL __cdecl sub_5437C0(int this)
{
  return *(_BYTE *)(this + 940) && *(_DWORD *)(this + 928) && Door_GetDoorStatus((struct QTask_s *)this);
}

// source: j/0/objects/door.c:2017  [anchor-strings]
void __cdecl Door_Open()
{
  __int16 v0; // ax
  unsigned __int16 v1; // si
  __int16 v2; // ax
  struct ParameterList_s *v3; // eax
  unsigned int v4; // edi
  char **v5; // esi
  unsigned __int16 v6; // si
  struct ParameterList_s *v7; // ebx
  int v8; // esi
  struct ParameterList_s *v9; // eax
  struct ParameterListItem_s *ptParameterListItem; // esi
  unsigned int v11; // edx
  int *v12; // edi
  unsigned int *v13; // esi
  char v14; // cl
  int v15; // edx

  Door_eQTaskType = QTask_NewQTaskType("Door", 968, RigidDynCubeObj_eQTaskType, 0, 0);
  Door_eOpenCloseDoorQTaskEvent = QTask_NewQTaskEventFn(0, "Door_OpenClose");
  v0 = QTask_NewQTaskEventFn(0, "Door_AttachToPortal");
  v1 = Door_eQTaskType;
  Door_eAttachToPortalQTaskEvent = v0;
  QTask_LinkQTaskEventHandlerFn(
    Door_eQTaskType,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 0, Door_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, Door_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, Door_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, Attach_eUpdateAttachmentEvent, Door_UpdateAttachmentHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Door_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v1, ParameterList_eUpdateInternalDataQTaskEvent, Door_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(v1, GameFunctions_eEvaluateActivateQTaskEvent, Door_EvaluateActivateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    GameFunctions_eGetActivateQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Door_GetActivateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    GameFunctions_eActivateQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Door_ActivateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v1,
    Level_eUpdateInternalDataAfterLoadEvent,
    Door_UpdateInternalDataAfterLoadHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, Level_eRegisterLevelScriptSymbolsEvent, Door_RegisterScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, Level_eRemoveLevelScriptSymbolsEvent, Door_RemoveScriptSymbolsHandler);
  v2 = HumanAI_eFindActivateQTaskEvent;
  if ( HumanAI_eFindActivateQTaskEvent == 512 )
  {
    v2 = QTask_NewQTaskEventFn(0, "HumanAIFindActivate");
    v1 = Door_eQTaskType;
    HumanAI_eFindActivateQTaskEvent = v2;
  }
  QTask_LinkQTaskEventHandlerFn(v1, v2, Door_AIFindActivateHandler);
  QTask_LinkQTaskEventHandlerFn(v1, ActionMenuScreen_eDrawActionItemQTaskEvent, Door_DrawActionItemHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 10, Door_TraceLinesHandler);
  QTask_LinkQTaskEventHandlerFn(v1, Door_eOpenCloseDoorQTaskEvent, Door_OpenCloseDoorHandler);
  QTask_LinkQTaskEventHandlerFn(v1, DynCubeObj_eDynCubeObjRemoveQTaskEvent, Door_RemoveHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 5, sub_5421C0);
  QTask_LinkQTaskEventHandlerFn(v1, NetworkGameItem_eGetGameItemDataQTaskEvent, Door_GetGameItemDataHandler);
  QTask_LinkQTaskEventHandlerFn(v1, NetworkGameItem_eGameItemUpdateQTaskEvent, Door_GameItemUpdateHandler);
  v3 = (struct ParameterList_s *)Mem_AllocFn(472, 4);
  v3->nParameters = 0;
  v3->nMaxParameters = 23;
  v3->ptParameterListItem = (struct ParameterListItem_s *)&v3[1];
  Door_ptParameterList = v3;
  dword_79EF568 = 0;
  dword_79EF56C = -1071382528;
  dword_79EF570 = 0;
  dword_79EF574 = 1076101120;
  dword_79EF558 = 0;
  dword_79EF55C = 0;
  dword_79EF560 = 0;
  dword_79EF564 = 1072693248;
  dword_79EF580 = 0;
  dword_79EF584 = -1065975808;
  dword_79EF588 = 0;
  dword_79EF58C = 1081507840;
  dword_79EF548 = -1610612736;
  dword_79EF54C = 1068079513;
  dword_79EF550 = 0;
  dword_79EF554 = 1079574528;
  ParameterList_AddParameter(v3, 0x140u, Level_eParameterTypeObjectPos, "Position start", 7u, nullptr);
  ParameterList_AddParameter(
    Door_ptParameterList,
    0x170u,
    Level_eParameterTypeReal32,
    "Position stop X",
    7u,
    &dword_79EF568);
  ParameterList_AddParameter(
    Door_ptParameterList,
    0x174u,
    Level_eParameterTypeReal32,
    "Position stop Y",
    7u,
    &dword_79EF568);
  ParameterList_AddParameter(
    Door_ptParameterList,
    0x1A0u,
    Level_eParameterTypeReal32,
    "Position slider",
    7u,
    &dword_79EF558);
  ParameterList_AddParameter(Door_ptParameterList, 0x178u, Level_eParameterTypeReal32x9, "Orientation", 7u, nullptr);
  ParameterList_AddParameter(Door_ptParameterList, 0x1B4u, Level_eParameterTypeString16, "Model", 7u, nullptr);
  ParameterList_AddParameter(Door_ptParameterList, 0x1ACu, Level_eParameterTypeReal32, "Max angle", 7u, &dword_79EF580);
  ParameterList_AddParameter(Door_ptParameterList, 0x1B0u, Level_eParameterTypeReal32, "Open time", 7u, &dword_79EF548);
  ParameterList_AddParameter(Door_ptParameterList, 0x1A5u, Level_eParameterTypebool8, "Pickable", 7u, nullptr);
  ParameterList_AddParameter(Door_ptParameterList, 0x1A4u, Level_eParameterTypebool8, "Open Both Ways", 7u, nullptr);
  ParameterList_AddParameter(
    Door_ptParameterList,
    0x334u,
    Level_eParameterTypeReal32,
    "Pick lock time (s)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Door_ptParameterList,
    0x2E4u,
    Level_eParameterTypeVarString,
    "Locked expression",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Door_ptParameterList,
    0x244u,
    Level_eParameterTypeVarString,
    "Open door expression",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Door_ptParameterList,
    0x294u,
    Level_eParameterTypeVarString,
    "Close door expression",
    7u,
    nullptr);
  ParameterList_AddParameter(Door_ptParameterList, 0x3ACu, Level_eParameterTypebool8, "StopOnCollision", 7u, nullptr);
  ParameterList_AddParameter(
    Door_ptParameterList,
    0x3A5u,
    Level_eParameterTypebool8,
    "Link up to a portal",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Door_ptParameterList,
    0x3C4u,
    Level_eParameterTypeReal32,
    "Delta scale factor",
    7u,
    nullptr);
  v4 = 452;
  v5 = Door_azSoundName;
  do
  {
    ParameterList_AddParameter(Door_ptParameterList, v4, Level_eParameterTypeString16, *v5++, 7u, nullptr);
    v4 += 16;
  }
  while ( (int)v5 < 7038620 );
  ParameterList_AddParameter(Door_ptParameterList, 0x214u, Level_eParameterTypeString32, "Activate Sound", 7u, nullptr);
  v6 = Door_eQTaskType;
  QTask_LinkQTaskEventHandlerFn(
    Door_eQTaskType,
    Serialize_eGetSerializeParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Door_GetSerializeParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v6, Serialize_eDeSerializeQTaskEvent, Door_DeSerializeHandler);
  QTask_LinkQTaskEventHandlerFn(
    v6,
    Serialize_eSerializeQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))sub_5420C0);
  v7 = ModelObjParameters_ptSerializeParameterList;
  v8 = ModelObjParameters_ptSerializeParameterList->nParameters + 21;
  v9 = (struct ParameterList_s *)Mem_AllocFn(20 * v8 + 12, 4);
  v9->nParameters = 0;
  v9->nMaxParameters = v8;
  v9->ptParameterListItem = (struct ParameterListItem_s *)&v9[1];
  ptParameterListItem = v7->ptParameterListItem;
  v11 = 20 * v7->nParameters;
  qmemcpy(&v9[1], ptParameterListItem, 4 * (v11 >> 2));
  v13 = &ptParameterListItem->nOffset + (v11 >> 2);
  v12 = &v9[1].nParameters + (v11 >> 2);
  v14 = v11;
  v15 = Level_eParameterTypeReal32;
  qmemcpy(v12, v13, v14 & 3);
  v9->nParameters = v7->nParameters;
  Door_ptSerializeParameterList = v9;
  ParameterList_AddParameter(v9, 0x170u, v15, "vOriginalStopX", 7u, nullptr);
  ParameterList_AddParameter(
    Door_ptSerializeParameterList,
    0x174u,
    Level_eParameterTypeReal32,
    "vOriginalStopY",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Door_ptSerializeParameterList,
    0x178u,
    Level_eParameterTypeReal32x9,
    "OriginalOrientation",
    7u,
    nullptr);
  ParameterList_AddParameter(Door_ptSerializeParameterList, 0x1A0u, Level_eParameterTypeReal32, "vRealPos", 7u, nullptr);
  ParameterList_AddParameter(
    Door_ptSerializeParameterList,
    0x234u,
    Level_eParameterTypeReal32,
    "vIdealAngle",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Door_ptSerializeParameterList,
    0x238u,
    Level_eParameterTypeReal32,
    "vRealAngle",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Door_ptSerializeParameterList,
    0x23Cu,
    Level_eParameterTypeReal32,
    "vIdealPos",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Door_ptSerializeParameterList,
    0x240u,
    Level_eParameterTypeReal32,
    "vDistance",
    7u,
    nullptr);
  ParameterList_AddParameter(Door_ptSerializeParameterList, 0x3A6u, Level_eParameterTypebool8, "isLocked", 7u, nullptr);
  ParameterList_AddParameter(Door_ptSerializeParameterList, 0x3A7u, Level_eParameterTypebool8, "isOpen", 7u, nullptr);
  ParameterList_AddParameter(Door_ptSerializeParameterList, 0x3A8u, Level_eParameterTypebool8, "isClosed", 7u, nullptr);
  ParameterList_AddParameter(
    Door_ptSerializeParameterList,
    0x3A9u,
    Level_eParameterTypebool8,
    "isLastOpen",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Door_ptSerializeParameterList,
    0x3AAu,
    Level_eParameterTypebool8,
    "isLastClosed",
    7u,
    nullptr);
  ParameterList_AddParameter(Door_ptSerializeParameterList, 0x3ABu, Level_eParameterTypebool8, "isPicked", 7u, nullptr);
  ParameterList_AddParameter(
    Door_ptSerializeParameterList,
    0x3ACu,
    Level_eParameterTypebool8,
    "isStopOnCollision",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Door_ptSerializeParameterList,
    0x3ADu,
    Level_eParameterTypebool8,
    "isOpenDoorChanged",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Door_ptSerializeParameterList,
    0x3AEu,
    Level_eParameterTypebool8,
    "isOpenDoor",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Door_ptSerializeParameterList,
    0x334u,
    Level_eParameterTypebool8,
    "vActivateTime",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Door_ptSerializeParameterList,
    0x338u,
    Level_eParameterTypeInt32,
    "nOpenTicks",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Door_ptSerializeParameterList,
    0x33Cu,
    Level_eParameterTypeReal32x9,
    "tLastOrientation",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Door_ptSerializeParameterList,
    0x380u,
    Level_eParameterTypeReal64x3,
    "tLastPosition",
    7u,
    nullptr);
}

// source: j/0/objects/door.c:2144  [anchor-hash]
void __cdecl Door_Close()
{
  int v0; // esi
  int v1; // esi

  QTask_DeleteQTaskEvent(Door_eOpenCloseDoorQTaskEvent);
  QTask_DeleteQTaskEvent(Door_eAttachToPortalQTaskEvent);
  if ( Door_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&Door_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  if ( Door_ptSerializeParameterList )
  {
    v1 = *(_DWORD *)((unsigned int)&Door_ptSerializeParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
  QTask_DeleteQTaskType(Door_eQTaskType);
}

int __cdecl Door_IsBlocked(int result, int a2)
{
  *(_DWORD *)(a2 + 928) = result;
  return result;
}

void __cdecl sub_544170(struct QTask_s *a1, void *a2)
{
  struct QReference_s *ptHead; // eax
  _DWORD *pxObject; // eax

  ptHead = a1[7].tQTaskRefList.ptHead;
  if ( ptHead )
  {
    pxObject = ptHead->pxObject;
    if ( pxObject )
      pxObject[62] = 0;
  }
}
