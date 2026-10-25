/* e/3/mesh3d.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: e/3/mesh3d.c:200  [size]
int __cdecl Mesh3D_GetDrawRigidMeshRenderModeMethod()
{
  return Mesh3D_eDrawRigidMeshRenderModeMethod;
}

// source: e/3/mesh3d.c:213  [size]
int __cdecl Mesh3D_GetDrawForestRenderModeMethod()
{
  return Mesh3D_eDrawForestRenderModeMethod;
}

// source: e/3/mesh3d.c:228  [size]
int __cdecl Mesh3D_GetDrawBoneMeshRenderModeMethod()
{
  return Mesh3D_eDrawBoneMeshRenderModeMethod;
}

// source: e/3/mesh3d.c:241  [size]
int __cdecl Mesh3D_GetDrawSplineMeshRenderModeMethod()
{
  return Mesh3D_eDrawSplineMeshRenderModeMethod;
}

// source: e/3/mesh3d.c:254  [size]
int __cdecl Mesh3D_GetDrawLightmapMeshRenderModeMethod()
{
  return Mesh3D_eDrawLightmapMeshRenderModeMethod;
}

// source: e/3/mesh3d.c:267  [size]
int __cdecl Mesh3D_GetExcludeObjectRenderModeMethod()
{
  return Mesh3D_eExcludeObjectRenderModeMethod;
}

// source: e/3/mesh3d.c:280  [size]
int __cdecl Mesh3D_GetIsTransparentRenderModeMethod()
{
  return Mesh3D_eIsTransparentRenderModeMethod;
}

// source: e/3/mesh3d.c:293  [size]
__int16 __cdecl Mesh3D_GetGetLightsourcingDataQTaskEvent()
{
  return Mesh3D_eGetLightsourcingDataQTaskEvent;
}

// source: e/3/mesh3d.c:308  [anchor-mhash]
int __cdecl Mesh3D_GetBoneMeshLOD(struct BoneDynCubeObj_s *ptBoneDynCubeObj)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vFirstScreenWidth; };
    struct { char igi2_o1[4]; float vClosestZ; };
    struct { char igi2_o2[8]; float vRadius; };
    struct { char igi2_o3[8]; float vRadiusa; };
    struct { char igi2_o4[12]; float vScreenWidth; };
    struct { char igi2_o5[16]; int v38; };
    struct { char igi2_o6[20]; struct Mesh3D_Mesh_t *v39; };
    struct { char igi2_o7[24]; int iLOD; };
    struct { char igi2_o8[28]; struct real32x3_t tPos; };
    char igi2_extent[48];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct LODVirModel_s *ptLODVirModel; // esi
  double vFOVX; // st7
  double v4; // st6
  struct Mesh3D_Mesh_t *ptMesh; // edx
  double v6; // st5
  int isLODDistanceSpecified; // eax
  int nLOD; // ebp
  double v9; // rt0
  double v10; // st5
  double v11; // st4
  double v12; // st5
  int v13; // ebx
  double v14; // st6
  int v15; // edi
  int v16; // ecx
  double nNumFaces; // st6
  int v18; // edx
  struct VirModel_s **v19; // eax
  struct Mesh3D_Mesh_t *v20; // ebp
  double v21; // st5
  double v22; // st5
  struct Mesh3D_Mesh_t *v23; // ebp
  double v24; // st5
  struct Mesh3D_Mesh_t *v25; // ebp
  double v26; // st5
  double v27; // st6
  int v28; // esi
  int v29; // edx
  bool v30; // zf
  int v31; // ecx
  float *i; // edx

  ptLODVirModel = ptBoneDynCubeObj->tModelObj.ptLODVirModel;
  if ( !ptLODVirModel )
    return 0;
  if ( TransContext_tActiveTransContext.vFOVX >= 1.0 )
    vFOVX = 1.0;
  else
    vFOVX = TransContext_tActiveTransContext.vFOVX;
  v4 = ptBoneDynCubeObj->tModelObj.tDynCubeObj.tQObj.tPos.vX - TransContext_tActiveTransContext.tPos.vX;
  ptMesh = ptLODVirModel->aptVirModel[0]->ptModel->ptMesh;
  v6 = ptBoneDynCubeObj->tModelObj.tDynCubeObj.tQObj.tPos.vY - TransContext_tActiveTransContext.tPos.vY;
  isLODDistanceSpecified = ptLODVirModel->isLODDistanceSpecified;
  igi2_frame.tPos.vZ = ptBoneDynCubeObj->tModelObj.tDynCubeObj.tQObj.tPos.vZ - TransContext_tActiveTransContext.tPos.vZ;
  nLOD = ptLODVirModel->nLOD;
  v9 = v6;
  v10 = v4 + ptMesh->tRenderMeshSphere.tPos.vX;
  igi2_frame.v39 = ptMesh;
  igi2_frame.tPos.vX = v10;
  v11 = TransContext_tActiveTransContext.tMatrix.tZ.vZ * (igi2_frame.tPos.vZ + ptMesh->tRenderMeshSphere.tPos.vZ)
      + TransContext_tActiveTransContext.tMatrix.tZ.vY * (v9 + ptMesh->tRenderMeshSphere.tPos.vY)
      + TransContext_tActiveTransContext.tMatrix.tZ.vX * igi2_frame.tPos.vX;
  v12 = ptBoneDynCubeObj->vRadius;
  if ( isLODDistanceSpecified )
  {
    v31 = 0;
    igi2_frame.vRadiusa = (v11 - v12) * vFOVX;
    if ( igi2_frame.vRadiusa > (double)ptLODVirModel->avLODDistance[4] )
      return -1;
    if ( ptLODVirModel->avLODDistance[0] == 0.0 )
    {
      v31 = nLOD - 1;
      if ( nLOD - 1 > 1 )
        v31 = 1;
    }
    for ( i = &ptLODVirModel->avLODDistance[v31]; igi2_frame.vRadiusa > (double)*i; ++v31 )
    {
      if ( v31 >= nLOD - 1 )
        break;
      ++i;
    }
    return v31;
  }
  else
  {
    v13 = 0;
    igi2_frame.iLOD = 0;
    igi2_frame.vRadius = (Mesh3D_vIdealRadius - v12) * (1.0 - Mesh3D_vRadiusImpact) + v12;
    v14 = v11 - igi2_frame.vRadius;
    igi2_frame.vClosestZ = v14;
    if ( v14 > 0.0 )
    {
      v15 = nLOD - 1;
      v16 = 1;
      igi2_frame.v38 = nLOD - 1;
      igi2_frame.vScreenWidth = 1.0 / igi2_frame.vClosestZ;
      igi2_frame.vFirstScreenWidth = 1.0 / (Mesh3D_vBoneObjDistance * igi2_frame.vRadius);
      igi2_frame.tPos.vX = igi2_frame.vFirstScreenWidth;
      if ( nLOD - 1 >= 4 )
      {
        nNumFaces = (double)ptMesh->tRenderMeshStats.nNumFaces;
        v18 = 4;
        v19 = &ptLODVirModel->aptVirModel[3];
        do
        {
          v20 = (*(v19 - 1))->ptModel->ptMesh;
          v21 = (double)(*(v19 - 2))->ptModel->ptMesh->tRenderMeshStats.nNumFaces / nNumFaces;
          v18 += 4;
          v16 += 4;
          v19 += 4;
          *(&igi2_frame.vScreenWidth + v16) = v21 * v21 * igi2_frame.vFirstScreenWidth;
          v22 = (double)v20->tRenderMeshStats.nNumFaces;
          v23 = (*(v19 - 4))->ptModel->ptMesh;
          *((float *)&igi2_frame.v38 + v16) = v22 / nNumFaces * (v22 / nNumFaces) * igi2_frame.vFirstScreenWidth;
          v24 = (double)v23->tRenderMeshStats.nNumFaces;
          v25 = (*(v19 - 3))->ptModel->ptMesh;
          *(float *)((char *)v19 + ((char *)&igi2_frame.tPos - (char *)ptLODVirModel) - 16) = v24
                                                                               / nNumFaces
                                                                               * (v24
                                                                                / nNumFaces)
                                                                               * igi2_frame.vFirstScreenWidth;
          v26 = (double)v25->tRenderMeshStats.nNumFaces;
          nLOD = ptLODVirModel->nLOD;
          *(float *)((char *)v19 + ((char *)&igi2_frame.tPos.vY - (char *)ptLODVirModel) - 16) = v26
                                                                                  / nNumFaces
                                                                                  * (v26
                                                                                   / nNumFaces)
                                                                                  * igi2_frame.vFirstScreenWidth;
        }
        while ( v18 < nLOD );
        v15 = igi2_frame.v38;
        ptMesh = igi2_frame.v39;
        v13 = igi2_frame.iLOD;
      }
      if ( v16 < nLOD )
      {
        v27 = (double)ptMesh->tRenderMeshStats.nNumFaces;
        v28 = (char *)ptLODVirModel - (char *)&igi2_frame.tPos;
        do
        {
          v29 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)((char *)&igi2_frame.tPos.vX + 4 * v16++ + v28) + 12) + 12);
          *((float *)&igi2_frame.iLOD + v16) = (double)*(int *)(v29 + 96)
                                  / v27
                                  * ((double)*(int *)(v29 + 96)
                                   / v27)
                                  * igi2_frame.vFirstScreenWidth;
        }
        while ( v16 < nLOD );
      }
      if ( igi2_frame.tPos.vX * vFOVX <= igi2_frame.vScreenWidth )
      {
LABEL_18:
        v30 = v13 == v15;
      }
      else
      {
        while ( 1 )
        {
          v30 = v13 == v15;
          if ( v13 >= v15 )
            break;
          ++v13;
          if ( vFOVX * *(&igi2_frame.tPos.vX + v13) <= igi2_frame.vScreenWidth )
            goto LABEL_18;
        }
      }
      if ( v30 && Mesh3D_vBoneObjCutoff * igi2_frame.vRadius < igi2_frame.vClosestZ * vFOVX )
        return -1;
    }
    return v13;
  }
}

// source: e/3/mesh3d.c:430  [anchor-mhash]
int __cdecl Mesh3D_GetSplineMeshLOD(struct SplineObjSegment_s *ptSplineObjSegment)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vFirstScreenWidth; };
    struct { char igi2_o1[4]; float vClosestZ; };
    struct { char igi2_o2[8]; float vRadius; };
    struct { char igi2_o3[12]; float vScreenWidth; };
    struct { char igi2_o4[16]; int v34; };
    struct { char igi2_o5[20]; int iLOD; };
    struct { char igi2_o6[24]; struct real32x3_t tPos; };
    char igi2_extent[44];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct LODVirModel_s *ptLODVirModel; // esi
  struct MultiMesh_Sphere_t *ptSphere; // ecx
  double v4; // st7
  double v5; // st6
  double v6; // st5
  double v7; // st7
  double vRealRadius; // st6
  int nLOD; // ebp
  int v10; // edi
  double v11; // st7
  int v12; // edx
  int v13; // ecx
  double nNumFaces; // st7
  int v15; // edx
  struct VirModel_s **v16; // eax
  struct Mesh3D_Mesh_t *ptMesh; // ebp
  double v18; // st6
  double v19; // st6
  struct Mesh3D_Mesh_t *v20; // ebp
  double v21; // st6
  struct Mesh3D_Mesh_t *v22; // ebp
  double v23; // st6
  double v24; // st7
  int v25; // esi
  int v26; // eax
  bool v27; // zf
  int v28; // ecx
  float *i; // edx

  ptLODVirModel = ptSplineObjSegment->tRigidDynCubeObj.tModelObj.ptLODVirModel;
  if ( !ptLODVirModel )
    return 0;
  ptSphere = ptSplineObjSegment->atSphereTree[0].ptSphere;
  v4 = ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vX
     - TransContext_tActiveTransContext.tPos.vX;
  v5 = ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vY
     - TransContext_tActiveTransContext.tPos.vY;
  v6 = ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vZ
     - TransContext_tActiveTransContext.tPos.vZ;
  if ( ptSphere )
  {
    igi2_frame.tPos.vZ = v6;
    igi2_frame.tPos.vX = v4 + ptSphere->tSphere.tPos.vX;
    v7 = TransContext_tActiveTransContext.tMatrix.tZ.vZ * (igi2_frame.tPos.vZ + ptSphere->tSphere.tPos.vZ)
       + TransContext_tActiveTransContext.tMatrix.tZ.vY * (v5 + ptSphere->tSphere.tPos.vY)
       + TransContext_tActiveTransContext.tMatrix.tZ.vX * igi2_frame.tPos.vX;
    vRealRadius = ptSphere->tSphere.vRadius;
  }
  else
  {
    v7 = TransContext_tActiveTransContext.tMatrix.tZ.vZ * v6
       + TransContext_tActiveTransContext.tMatrix.tZ.vY * v5
       + TransContext_tActiveTransContext.tMatrix.tZ.vX * v4;
    vRealRadius = ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.vRealRadius;
  }
  nLOD = ptLODVirModel->nLOD;
  if ( ptLODVirModel->isLODDistanceSpecified )
  {
    v28 = 0;
    igi2_frame.vRadius = TransContext_tActiveTransContext.vFOVX * (v7 - vRealRadius);
    if ( igi2_frame.vRadius > (double)ptLODVirModel->avLODDistance[4] )
      return -1;
    if ( ptLODVirModel->avLODDistance[0] == 0.0 )
    {
      v28 = nLOD - 1;
      if ( nLOD - 1 > 1 )
        v28 = 1;
    }
    for ( i = &ptLODVirModel->avLODDistance[v28]; igi2_frame.vRadius > (double)*i; ++v28 )
    {
      if ( v28 >= nLOD - 1 )
        break;
      ++i;
    }
    return v28;
  }
  else
  {
    v10 = 0;
    igi2_frame.iLOD = 0;
    igi2_frame.vRadius = (Mesh3D_vIdealRadius - vRealRadius) * (1.0 - Mesh3D_vRadiusImpact) + vRealRadius;
    v11 = v7 - igi2_frame.vRadius;
    igi2_frame.vClosestZ = v11;
    if ( v11 > 0.0 )
    {
      v12 = nLOD - 1;
      v13 = 1;
      igi2_frame.v34 = nLOD - 1;
      igi2_frame.vScreenWidth = 1.0 / igi2_frame.vClosestZ;
      igi2_frame.vFirstScreenWidth = 1.0 / (Mesh3D_vSplineObjDistance * igi2_frame.vRadius);
      igi2_frame.tPos.vX = igi2_frame.vFirstScreenWidth;
      if ( nLOD - 1 >= 4 )
      {
        nNumFaces = (double)ptLODVirModel->aptVirModel[0]->ptModel->ptMesh->tRenderMeshStats.nNumFaces;
        v15 = 4;
        v16 = &ptLODVirModel->aptVirModel[3];
        do
        {
          ptMesh = (*(v16 - 1))->ptModel->ptMesh;
          v18 = (double)(*(v16 - 2))->ptModel->ptMesh->tRenderMeshStats.nNumFaces / nNumFaces;
          v15 += 4;
          v13 += 4;
          v16 += 4;
          *(&igi2_frame.vRadius + v13) = v18 * v18 * igi2_frame.vFirstScreenWidth;
          v19 = (double)ptMesh->tRenderMeshStats.nNumFaces;
          v20 = (*(v16 - 4))->ptModel->ptMesh;
          *(&igi2_frame.vScreenWidth + v13) = v19 / nNumFaces * (v19 / nNumFaces) * igi2_frame.vFirstScreenWidth;
          v21 = (double)v20->tRenderMeshStats.nNumFaces;
          v22 = (*(v16 - 3))->ptModel->ptMesh;
          *(float *)((char *)v16 + ((char *)&igi2_frame.tPos - (char *)ptLODVirModel) - 16) = v21
                                                                               / nNumFaces
                                                                               * (v21
                                                                                / nNumFaces)
                                                                               * igi2_frame.vFirstScreenWidth;
          v23 = (double)v22->tRenderMeshStats.nNumFaces;
          nLOD = ptLODVirModel->nLOD;
          *(float *)((char *)v16 + ((char *)&igi2_frame.tPos.vY - (char *)ptLODVirModel) - 16) = v23
                                                                                  / nNumFaces
                                                                                  * (v23
                                                                                   / nNumFaces)
                                                                                  * igi2_frame.vFirstScreenWidth;
        }
        while ( v15 < nLOD );
        v12 = igi2_frame.v34;
        v10 = igi2_frame.iLOD;
      }
      if ( v13 < nLOD )
      {
        v24 = (double)ptLODVirModel->aptVirModel[0]->ptModel->ptMesh->tRenderMeshStats.nNumFaces;
        v25 = (char *)ptLODVirModel - (char *)&igi2_frame.tPos;
        do
        {
          v26 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)((char *)&igi2_frame.tPos.vX + 4 * v13++ + v25) + 12) + 12);
          *((float *)&igi2_frame.iLOD + v13) = (double)*(int *)(v26 + 96)
                                  / v24
                                  * ((double)*(int *)(v26 + 96)
                                   / v24)
                                  * igi2_frame.vFirstScreenWidth;
        }
        while ( v13 < nLOD );
      }
      if ( TransContext_tActiveTransContext.vFOVX * igi2_frame.tPos.vX <= igi2_frame.vScreenWidth )
      {
LABEL_18:
        v27 = v10 == v12;
      }
      else
      {
        while ( 1 )
        {
          v27 = v10 == v12;
          if ( v10 >= v12 )
            break;
          ++v10;
          if ( TransContext_tActiveTransContext.vFOVX * *(&igi2_frame.tPos.vX + v10) <= igi2_frame.vScreenWidth )
            goto LABEL_18;
        }
      }
      if ( v27 && Mesh3D_vSplineObjCutoff * igi2_frame.vRadius < TransContext_tActiveTransContext.vFOVX * igi2_frame.vClosestZ )
        return -1;
    }
    return v10;
  }
}

// source: e/3/mesh3d.c:562  [anchor-mhash]
enum bool __cdecl Mesh3D_ExcludeObject(
        struct real32x3_t *ptRotatedPos,
        float vRadius,
        enum bool *pisTotallyInside)
{
  double v3; // st7
  double v4; // st6
  struct ExcludeObjectContext_t tContext; // [esp+0h] [ebp-10h] BYREF

  if ( Mesh3D_nTransContextTimeStamp != TransContext_nActiveTransContextTimeStamp
    || Mesh3D_nRenderContextTimeStamp != RenderContext_nActiveRenderContextTimeStamp )
  {
    Mesh3D_nTransContextTimeStamp = TransContext_nActiveTransContextTimeStamp;
    v3 = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX
       + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHalfWidth;
    Mesh3D_nRenderContextTimeStamp = RenderContext_nActiveRenderContextTimeStamp;
    v4 = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vY
       + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHalfHeight;
    Mesh3D_vViewConeFOVLeft = (RenderContext_tActiveRenderContext.tDisplayAreaMin.vX - v3)
                            / RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHalfWidth
                            * TransContext_tActiveTransContext.vFOVX;
    Mesh3D_vViewConeFOVRight = (RenderContext_tActiveRenderContext.tDisplayAreaMax.vX - v3)
                             / RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHalfWidth
                             * TransContext_tActiveTransContext.vFOVX;
    Mesh3D_vViewConeFOVTop = (RenderContext_tActiveRenderContext.tDisplayAreaMin.vY - v4)
                           / RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHalfHeight
                           * TransContext_tActiveTransContext.vFOVY;
    Mesh3D_vViewConeFOVBottom = (RenderContext_tActiveRenderContext.tDisplayAreaMax.vY - v4)
                              / RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHalfHeight
                              * TransContext_tActiveTransContext.vFOVY;
    Mesh3D_vCosViewConeAngleLeft = cos(atan2(Mesh3D_vViewConeFOVLeft, 1.0));
    Mesh3D_vCosViewConeAngleRight = cos(atan2(Mesh3D_vViewConeFOVRight, 1.0));
    Mesh3D_vCosViewConeAngleTop = cos(atan2(Mesh3D_vViewConeFOVTop, 1.0));
    Mesh3D_vCosViewConeAngleBottom = cos(atan2(Mesh3D_vViewConeFOVBottom, 1.0));
  }
  tContext.ptRotatedPos = ptRotatedPos;
  tContext.vRadius = vRadius;
  tContext.pisTotallyInside = pisTotallyInside;
  RenderMode_tActiveRenderMode.apfRenderModeMethod[Mesh3D_eExcludeObjectRenderModeMethod](&tContext);
  return tContext.isExcluded;
}

// source: e/3/mesh3d.c:654  [anchor-mhash]
enum bool __cdecl Mesh3D_ExcludeRigidMesh(
        struct RigidDynCubeObj_t *ptRigidDynCubeObj,
        enum bool *pisTotallyInside)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vRadius; };
    struct { char igi2_o1[4]; struct real32x3_t tPos; };
    struct { char igi2_o2[16]; struct real32x3_t Real32x3_Rotate_tTemp; };
    char igi2_extent[28];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct LODVirModel_s *ptLODVirModel; // edx
  float *p_vVersion; // eax
  double v4; // st7
  double v5; // st6
  double v6; // st7
  double v7; // st6
  double vY; // st7
  double vX; // st7

  ptLODVirModel = ptRigidDynCubeObj->tModelObj.ptLODVirModel;
  igi2_frame.tPos.vX = ptRigidDynCubeObj->tModelObj.tDynCubeObj.tQObj.tPos.vX - TransContext_tActiveTransContext.tPos.vX;
  igi2_frame.tPos.vY = ptRigidDynCubeObj->tModelObj.tDynCubeObj.tQObj.tPos.vY - TransContext_tActiveTransContext.tPos.vY;
  igi2_frame.tPos.vZ = ptRigidDynCubeObj->tModelObj.tDynCubeObj.tQObj.tPos.vZ - TransContext_tActiveTransContext.tPos.vZ;
  if ( ptLODVirModel )
  {
    p_vVersion = &ptLODVirModel->aptVirModel[0]->ptModel->ptMesh->vVersion;
    v4 = ptRigidDynCubeObj->tModelObj.tOrientation.tX.vY * p_vVersion[13]
       + ptRigidDynCubeObj->tModelObj.tOrientation.tX.vX * p_vVersion[12]
       + ptRigidDynCubeObj->tModelObj.tOrientation.tX.vZ * p_vVersion[14];
    v5 = ptRigidDynCubeObj->tModelObj.tOrientation.tY.vY * p_vVersion[13]
       + ptRigidDynCubeObj->tModelObj.tOrientation.tY.vX * p_vVersion[12]
       + ptRigidDynCubeObj->tModelObj.tOrientation.tY.vZ * p_vVersion[14];
    igi2_frame.Real32x3_Rotate_tTemp.vZ = ptRigidDynCubeObj->tModelObj.tOrientation.tZ.vY * p_vVersion[13]
                             + ptRigidDynCubeObj->tModelObj.tOrientation.tZ.vX * p_vVersion[12]
                             + ptRigidDynCubeObj->tModelObj.tOrientation.tZ.vZ * p_vVersion[14];
    igi2_frame.tPos.vX = v4 + igi2_frame.tPos.vX;
    v6 = v5 + igi2_frame.tPos.vY;
    v7 = igi2_frame.Real32x3_Rotate_tTemp.vZ + igi2_frame.tPos.vZ;
    igi2_frame.Real32x3_Rotate_tTemp.vX = TransContext_tActiveTransContext.tMatrix.tX.vZ * v7
                             + TransContext_tActiveTransContext.tMatrix.tX.vY * v6
                             + TransContext_tActiveTransContext.tMatrix.tX.vX * igi2_frame.tPos.vX;
    igi2_frame.Real32x3_Rotate_tTemp.vY = TransContext_tActiveTransContext.tMatrix.tY.vZ * v7
                             + TransContext_tActiveTransContext.tMatrix.tY.vY * v6
                             + TransContext_tActiveTransContext.tMatrix.tY.vX * igi2_frame.tPos.vX;
    igi2_frame.Real32x3_Rotate_tTemp.vZ = TransContext_tActiveTransContext.tMatrix.tZ.vZ * v7
                             + TransContext_tActiveTransContext.tMatrix.tZ.vY * v6
                             + TransContext_tActiveTransContext.tMatrix.tZ.vX * igi2_frame.tPos.vX;
    igi2_frame.tPos = igi2_frame.Real32x3_Rotate_tTemp;
    if ( ptRigidDynCubeObj->tModelObj.tScale.vX <= (double)ptRigidDynCubeObj->tModelObj.tScale.vY )
      vY = ptRigidDynCubeObj->tModelObj.tScale.vY;
    else
      vY = ptRigidDynCubeObj->tModelObj.tScale.vX;
    if ( vY <= ptRigidDynCubeObj->tModelObj.tScale.vZ )
    {
      igi2_frame.vRadius = ptRigidDynCubeObj->tModelObj.tScale.vZ
              * ptLODVirModel->aptVirModel[0]->ptModel->ptMesh->tRenderMeshSphere.vRadius;
    }
    else
    {
      if ( ptRigidDynCubeObj->tModelObj.tScale.vX <= (double)ptRigidDynCubeObj->tModelObj.tScale.vY )
        vX = ptRigidDynCubeObj->tModelObj.tScale.vY;
      else
        vX = ptRigidDynCubeObj->tModelObj.tScale.vX;
      igi2_frame.vRadius = vX * ptLODVirModel->aptVirModel[0]->ptModel->ptMesh->tRenderMeshSphere.vRadius;
    }
  }
  else
  {
    igi2_frame.vRadius = 1.0;
  }
  return Mesh3D_ExcludeObject(&igi2_frame.tPos, igi2_frame.vRadius, pisTotallyInside);
}

// source: e/3/mesh3d.c:689  [anchor-mhash]
enum bool __cdecl Mesh3D_ExcludeBoneMesh(
        struct BoneDynCubeObj_s *ptBoneDynCubeObj,
        enum bool *pisTotallyInside)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vRadius; };
    struct { char igi2_o1[4]; float Real32x3_Rotate_tTemp; };
    struct { char igi2_o2[8]; float Real32x3_Rotate_tTemp_4; };
    struct { char igi2_o3[12]; float Real32x3_Rotate_tTemp_8; };
    struct { char igi2_o4[16]; struct real32x3_t tPos; };
    char igi2_extent[28];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v2; // st7
  double v3; // st6
  double v4; // st5
  struct LODVirModel_s *ptLODVirModel; // edx

  v2 = ptBoneDynCubeObj->tModelObj.tDynCubeObj.tQObj.tPos.vX - TransContext_tActiveTransContext.tPos.vX;
  v3 = ptBoneDynCubeObj->tModelObj.tDynCubeObj.tQObj.tPos.vY - TransContext_tActiveTransContext.tPos.vY;
  v4 = ptBoneDynCubeObj->tModelObj.tDynCubeObj.tQObj.tPos.vZ - TransContext_tActiveTransContext.tPos.vZ;
  igi2_frame.Real32x3_Rotate_tTemp = TransContext_tActiveTransContext.tMatrix.tX.vZ * v4
                        + TransContext_tActiveTransContext.tMatrix.tX.vY * v3
                        + TransContext_tActiveTransContext.tMatrix.tX.vX * v2;
  igi2_frame.tPos.vX = igi2_frame.Real32x3_Rotate_tTemp;
  igi2_frame.Real32x3_Rotate_tTemp_4 = TransContext_tActiveTransContext.tMatrix.tY.vZ * v4
                          + TransContext_tActiveTransContext.tMatrix.tY.vY * v3
                          + TransContext_tActiveTransContext.tMatrix.tY.vX * v2;
  igi2_frame.tPos.vY = igi2_frame.Real32x3_Rotate_tTemp_4;
  ptLODVirModel = ptBoneDynCubeObj->tModelObj.ptLODVirModel;
  igi2_frame.Real32x3_Rotate_tTemp_8 = TransContext_tActiveTransContext.tMatrix.tZ.vZ * v4
                          + TransContext_tActiveTransContext.tMatrix.tZ.vY * v3
                          + TransContext_tActiveTransContext.tMatrix.tZ.vX * v2;
  igi2_frame.tPos.vZ = igi2_frame.Real32x3_Rotate_tTemp_8;
  igi2_frame.vRadius = ptLODVirModel->aptVirModel[0]->ptModel->ptMesh->tRenderMeshSphere.vRadius * 1.409999966621399;
  return Mesh3D_ExcludeObject(&igi2_frame.tPos, igi2_frame.vRadius, pisTotallyInside);
}

// source: e/3/mesh3d.c:716  [anchor-mhash]
enum bool __cdecl Mesh3D_ExcludeSplineMesh(
        struct SplineObjSegment_s *ptSplineObjSegment,
        enum bool *pisTotallyInside)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vRadius; };
    struct { char igi2_o1[4]; struct real32x3_t tPos; };
    struct { char igi2_o2[16]; struct real32x3_t Real32x3_Rotate_tTemp; };
    char igi2_extent[28];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct MultiMesh_Sphere_t *ptSphere; // eax
  double v3; // st7
  double v4; // st7
  double v5; // st6
  double v6; // st5

  ptSphere = ptSplineObjSegment->atSphereTree[0].ptSphere;
  v3 = ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vX
     - TransContext_tActiveTransContext.tPos.vX;
  if ( ptSphere )
  {
    igi2_frame.tPos.vX = v3;
    igi2_frame.tPos.vY = ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vY
            - TransContext_tActiveTransContext.tPos.vY;
    igi2_frame.tPos.vZ = ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vZ
            - TransContext_tActiveTransContext.tPos.vZ;
    igi2_frame.tPos.vX = igi2_frame.tPos.vX + ptSphere->tSphere.tPos.vX;
    igi2_frame.tPos.vY = igi2_frame.tPos.vY + ptSphere->tSphere.tPos.vY;
    v4 = igi2_frame.tPos.vZ + ptSphere->tSphere.tPos.vZ;
    igi2_frame.Real32x3_Rotate_tTemp.vX = TransContext_tActiveTransContext.tMatrix.tX.vZ * v4
                             + TransContext_tActiveTransContext.tMatrix.tX.vY * igi2_frame.tPos.vY
                             + TransContext_tActiveTransContext.tMatrix.tX.vX * igi2_frame.tPos.vX;
    igi2_frame.Real32x3_Rotate_tTemp.vY = TransContext_tActiveTransContext.tMatrix.tY.vZ * v4
                             + TransContext_tActiveTransContext.tMatrix.tY.vY * igi2_frame.tPos.vY
                             + TransContext_tActiveTransContext.tMatrix.tY.vX * igi2_frame.tPos.vX;
    igi2_frame.Real32x3_Rotate_tTemp.vZ = TransContext_tActiveTransContext.tMatrix.tZ.vZ * v4
                             + TransContext_tActiveTransContext.tMatrix.tZ.vY * igi2_frame.tPos.vY
                             + TransContext_tActiveTransContext.tMatrix.tZ.vX * igi2_frame.tPos.vX;
    igi2_frame.tPos = igi2_frame.Real32x3_Rotate_tTemp;
    igi2_frame.vRadius = ptSphere->tSphere.vRadius;
  }
  else
  {
    v5 = ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vY
       - TransContext_tActiveTransContext.tPos.vY;
    v6 = ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vZ
       - TransContext_tActiveTransContext.tPos.vZ;
    igi2_frame.vRadius = ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.vRealRadius;
    igi2_frame.Real32x3_Rotate_tTemp.vX = TransContext_tActiveTransContext.tMatrix.tX.vZ * v6
                             + TransContext_tActiveTransContext.tMatrix.tX.vY * v5
                             + TransContext_tActiveTransContext.tMatrix.tX.vX * v3;
    igi2_frame.Real32x3_Rotate_tTemp.vY = TransContext_tActiveTransContext.tMatrix.tY.vZ * v6
                             + TransContext_tActiveTransContext.tMatrix.tY.vY * v5
                             + TransContext_tActiveTransContext.tMatrix.tY.vX * v3;
    igi2_frame.Real32x3_Rotate_tTemp.vZ = TransContext_tActiveTransContext.tMatrix.tZ.vZ * v6
                             + TransContext_tActiveTransContext.tMatrix.tZ.vY * v5
                             + TransContext_tActiveTransContext.tMatrix.tZ.vX * v3;
    igi2_frame.tPos = igi2_frame.Real32x3_Rotate_tTemp;
  }
  return Mesh3D_ExcludeObject(&igi2_frame.tPos, igi2_frame.vRadius, pisTotallyInside);
}

// source: e/3/mesh3d.c:1363  [anchor-mhash]
struct Mesh3D_MagicVertex_t *__cdecl Mesh3D_GetMagicVertex(
        struct Mesh3D_Mesh_t *ptMesh,
        unsigned int iMagicVertex)
{
  if ( iMagicVertex >= ptMesh->nMagicVertex )
    return nullptr;
  else
    return &ptMesh->ptMagicVertex[iMagicVertex];
}

// source: e/3/mesh3d.c:1386  [anchor-mhash]
unsigned int __cdecl Mesh3D_GetMagicVertexPos(
        struct Mesh3D_Mesh_t *ptMesh,
        unsigned int iMagicVertex,
        struct real32x3_t *ptPos)
{
  if ( iMagicVertex < ptMesh->nMagicVertex && (iMagicVertex = (unsigned int)&ptMesh->ptMagicVertex[iMagicVertex]) != 0 )
  {
    ptPos->vX = *(float *)iMagicVertex;
    ptPos->vY = *(float *)(iMagicVertex + 4);
    iMagicVertex = *(_DWORD *)(iMagicVertex + 8);
    LODWORD(ptPos->vZ) = iMagicVertex;
  }
  else
  {
    ptPos->vX = 0.0;
    ptPos->vY = 0.0;
    ptPos->vZ = 0.0;
  }
  return iMagicVertex;
}

// source: e/3/mesh3d.c:1541  [anchor-hash]
float __cdecl Mesh3D_GetLODVirModelRadius(struct LODVirModel_s *ptLODVirModel)
{
  struct VirModel_s *v1; // eax

  if ( ptLODVirModel && (v1 = ptLODVirModel->aptVirModel[0]) != nullptr )
    return v1->ptModel->ptMesh->vRadius;
  else
    return 1.0;
}

// source: e/3/mesh3d.c:1714  [size]
void __cdecl Mesh3D_Open()
{
  struct Mesh3D_ShininessFac_t *v0; // eax
  double v1; // st7
  int v2; // eax
  int v3; // eax
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int iShine; // [esp+0h] [ebp-4h]

  iShine = 0;
  v0 = Mesh3D_atShininessFac;
  do
  {
    ++v0;
    v1 = (double)iShine++ * 0.06666667014360428;
    v0[-1].vSub = 0.699999988079071 * v1;
    v0[-1].vCutoff = 0.699999988079071 * v1;
    v0[-1].vMultiply = v1 * v1 * v1 * 40.0 + 1.0;
  }
  while ( (int)v0 < 140420256 );
  Mesh3D_eGetLightsourcingDataQTaskEvent = QTask_NewQTaskEventFn(0, "GetLightsourcingData");
  Mesh3D_eChangeModelQTaskEventNoContext = QTask_NewQTaskEventNoContextFn(0, "ChangeModel");
  v2 = 0;
  while ( RenderMode_atRenderModeMethod[v2].isAllocated )
  {
    if ( ++v2 >= 128 )
    {
      LDebug_Error("RenderMode: Failed to create new method '%s'", "UpdateMesh");
      goto LABEL_7;
    }
  }
  RenderMode_atRenderModeMethod[v2].zName = "UpdateMesh";
  RenderMode_atRenderModeMethod[v2].isAllocated = 1;
  Mesh3D_eUpdateMeshRenderModeMethod = v2;
  v3 = 0;
  while ( RenderMode_atRenderModeMethod[v3].isAllocated )
  {
    if ( ++v3 >= 128 )
    {
      LDebug_Error("RenderMode: Failed to create new method '%s'", "GenericUVFromRenderModeUV");
      goto LABEL_7;
    }
  }
  RenderMode_atRenderModeMethod[v3].zName = "GenericUVFromRenderModeUV";
  RenderMode_atRenderModeMethod[v3].isAllocated = 1;
  Mesh3D_eGenericUVFromRenderModeUV = v3;
  v4 = 0;
  while ( RenderMode_atRenderModeMethod[v4].isAllocated )
  {
    if ( ++v4 >= 128 )
    {
      LDebug_Error("RenderMode: Failed to create new method '%s'", "RenderModeUVFromGenericUV");
      goto LABEL_7;
    }
  }
  RenderMode_atRenderModeMethod[v4].zName = "RenderModeUVFromGenericUV";
  RenderMode_atRenderModeMethod[v4].isAllocated = 1;
  Mesh3D_eRenderModeUVFromGenericUV = v4;
  v5 = 0;
  while ( RenderMode_atRenderModeMethod[v5].isAllocated )
  {
    if ( ++v5 >= 128 )
    {
      LDebug_Error("RenderMode: Failed to create new method '%s'", "DrawRigidMesh");
      goto LABEL_7;
    }
  }
  RenderMode_atRenderModeMethod[v5].zName = "DrawRigidMesh";
  RenderMode_atRenderModeMethod[v5].isAllocated = 1;
  Mesh3D_eDrawRigidMeshRenderModeMethod = v5;
  v6 = 0;
  while ( RenderMode_atRenderModeMethod[v6].isAllocated )
  {
    if ( ++v6 >= 128 )
    {
      LDebug_Error("RenderMode: Failed to create new method '%s'", "DrawForest");
      goto LABEL_7;
    }
  }
  RenderMode_atRenderModeMethod[v6].zName = "DrawForest";
  RenderMode_atRenderModeMethod[v6].isAllocated = 1;
  Mesh3D_eDrawForestRenderModeMethod = v6;
  v7 = 0;
  while ( RenderMode_atRenderModeMethod[v7].isAllocated )
  {
    if ( ++v7 >= 128 )
    {
      LDebug_Error("RenderMode: Failed to create new method '%s'", "DrawBoneMesh");
      goto LABEL_7;
    }
  }
  RenderMode_atRenderModeMethod[v7].zName = "DrawBoneMesh";
  RenderMode_atRenderModeMethod[v7].isAllocated = 1;
  Mesh3D_eDrawBoneMeshRenderModeMethod = v7;
  v8 = 0;
  while ( RenderMode_atRenderModeMethod[v8].isAllocated )
  {
    if ( ++v8 >= 128 )
    {
      LDebug_Error("RenderMode: Failed to create new method '%s'", "DrawSplineMesh");
      goto LABEL_7;
    }
  }
  RenderMode_atRenderModeMethod[v8].zName = "DrawSplineMesh";
  RenderMode_atRenderModeMethod[v8].isAllocated = 1;
  Mesh3D_eDrawSplineMeshRenderModeMethod = v8;
  v9 = 0;
  while ( RenderMode_atRenderModeMethod[v9].isAllocated )
  {
    if ( ++v9 >= 128 )
    {
      LDebug_Error("RenderMode: Failed to create new method '%s'", "DrawLightmapMesh");
      goto LABEL_7;
    }
  }
  RenderMode_atRenderModeMethod[v9].zName = "DrawLightmapMesh";
  RenderMode_atRenderModeMethod[v9].isAllocated = 1;
  Mesh3D_eDrawLightmapMeshRenderModeMethod = v9;
  v10 = 0;
  while ( RenderMode_atRenderModeMethod[v10].isAllocated )
  {
    if ( ++v10 >= 128 )
    {
      LDebug_Error("RenderMode: Failed to create new method '%s'", "ExcludeObject");
      goto LABEL_7;
    }
  }
  RenderMode_atRenderModeMethod[v10].zName = "ExcludeObject";
  RenderMode_atRenderModeMethod[v10].isAllocated = 1;
  Mesh3D_eExcludeObjectRenderModeMethod = v10;
  v11 = 0;
  while ( RenderMode_atRenderModeMethod[v11].isAllocated )
  {
    if ( ++v11 >= 128 )
    {
      LDebug_Error("RenderMode: Failed to create new method '%s'", "IsTransparent");
LABEL_7:
      abort();
    }
  }
  RenderMode_atRenderModeMethod[v11].zName = "IsTransparent";
  RenderMode_atRenderModeMethod[v11].isAllocated = 1;
  Mesh3D_eIsTransparentRenderModeMethod = v11;
  Mesh3D_avOverrideFOV[0] = 1.0;
  Mesh3D_avOverrideFOV[1] = 1.0;
  Mesh3D_avOverrideFOV[2] = 1.0;
  Mesh3D_aptPreCalcObj[0] = nullptr;
  Mesh3D_avOverrideFOV[3] = 1.0;
}

// source: e/3/mesh3d.c:1782  [size]
void __cdecl Mesh3D_Close()
{
  int v0; // edx
  int v1; // ecx
  int v2; // edx
  int v3; // ecx
  int v4; // edx
  int v5; // ecx
  int v6; // edx

  v0 = Mesh3D_eRenderModeUVFromGenericUV;
  RenderMode_atRenderModeMethod[Mesh3D_eGenericUVFromRenderModeUV].isAllocated = 0;
  v1 = Mesh3D_eDrawRigidMeshRenderModeMethod;
  RenderMode_atRenderModeMethod[v0].isAllocated = 0;
  v2 = Mesh3D_eDrawBoneMeshRenderModeMethod;
  RenderMode_atRenderModeMethod[v1].isAllocated = 0;
  v3 = Mesh3D_eDrawSplineMeshRenderModeMethod;
  RenderMode_atRenderModeMethod[v2].isAllocated = 0;
  v4 = Mesh3D_eDrawLightmapMeshRenderModeMethod;
  RenderMode_atRenderModeMethod[v3].isAllocated = 0;
  v5 = Mesh3D_eExcludeObjectRenderModeMethod;
  RenderMode_atRenderModeMethod[v4].isAllocated = 0;
  v6 = Mesh3D_eUpdateMeshRenderModeMethod;
  RenderMode_atRenderModeMethod[v5].isAllocated = 0;
  RenderMode_atRenderModeMethod[v6].isAllocated = 0;
  QTask_DeleteQTaskEventNoContext(Mesh3D_eChangeModelQTaskEventNoContext);
  QTask_DeleteQTaskEvent(Mesh3D_eGetLightsourcingDataQTaskEvent);
}

// source: e/3/mesh3d.c:1812  [size]
struct Mesh3D_AttachObject_t *__cdecl Mesh3D_GetAttachObject(
        struct VirModel_s *ptVirModel,
        int iAttachObject)
{
  return &ptVirModel->ptModel->ptMesh->ptAttachObject[iAttachObject];
}

// source: e/3/mesh3d.c:1828  [anchor-hash]
int __cdecl Mesh3D_GetNumberOfAttachObject(struct VirModel_s *ptVirModel)
{
  return ptVirModel->ptModel->ptMesh->nAttachObject;
}

// source: e/3/mesh3d.c:1843  [anchor-hash]
int __cdecl Mesh3D_GetNumberOfMagicVertex(struct VirModel_s *ptVirModel)
{
  return ptVirModel->ptModel->ptMesh->nMagicVertex;
}

// source: e/3/mesh3d.c:1858  [size]
void __cdecl Mesh3D_AllocateAnimTexIndexPointers(
        unsigned int **ptAnimTexIndex,
        struct LODVirModel_s *ptLODVirModel)
{
  ;
}

// source: e/3/mesh3d.c:1923  [anchor-mhash]
void __cdecl Mesh3D_FreeAnimTexIndexPointers(unsigned int **ptAnimTexIndex)
{
  int i; // ebx
  unsigned int *v2; // eax
  int v3; // esi

  for ( i = 0; i < 5; ++i )
  {
    v2 = ptAnimTexIndex[i];
    if ( v2 )
    {
      v3 = *(_DWORD *)((unsigned int)(v2 - 1) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v3);
      memset(*(void **)(v3 + 8), 0xCDu, *(_DWORD *)(v3 + 16));
      free((void *)v3);
      ptAnimTexIndex[i] = nullptr;
    }
  }
}

// source: e/3/mesh3d.c:1960  [size]
int __cdecl Mesh3D_GetChangeModelQTaskEventNoContext()
{
  return Mesh3D_eChangeModelQTaskEventNoContext;
}

// source: e/3/mesh3d.c:1975  [anchor-hash]
int __cdecl Mesh3D_GetAnimTextureCount(struct VirModel_s *ptVirModel)
{
  return ptVirModel->ptModel->nAnimTextures;
}

// source: e/3/mesh3d.c:1991  [size]
int __cdecl Mesh3D_GetAnimTextureFrameCount(struct VirModel_s *ptVirModel, int iAnimTexture)
{
  return ptVirModel->ptModel->atAnimTexInfo[iAnimTexture].nFrames;
}

// source: e/3/mesh3d.c:2010  [size]
int __cdecl Mesh3D_SetAnimTextureFrame(
        struct VirModel_s *ptVirModel,
        int iAnimTexture,
        int iAnimTextureFrame)
{
  int result; // eax

  result = iAnimTexture;
  ptVirModel->ptModel->atAnimTexInfo[result].nActiveFrame = iAnimTextureFrame;
  return result * 5;
}

// source: e/3/mesh3d.c:2037  [anchor-hash]
void __cdecl Mesh3D_SetDrawAnimTextures(struct VirModel_s *ptVirModel)
{
  struct Model_s *ptModel; // eax
  int nAnimTextures; // ecx
  struct ModelAnimTexInfo_s *atAnimTexInfo; // eax
  void **p_pxTempData; // eax
  int v5; // edi
  int v6; // ecx
  int v7; // ebx

  ptModel = ptVirModel->ptModel;
  nAnimTextures = ptModel->nAnimTextures;
  if ( nAnimTextures )
  {
    atAnimTexInfo = ptModel->atAnimTexInfo;
    if ( nAnimTextures > 0 )
    {
      p_pxTempData = &atAnimTexInfo->pxTempData;
      v5 = nAnimTextures;
      do
      {
        v6 = (int)*(p_pxTempData - 1);
        v7 = (int)*(p_pxTempData - 2);
        *p_pxTempData = ptVirModel->pptTexInfo[v6];
        p_pxTempData += 5;
        --v5;
        ptVirModel->pptTexInfo[v6] = ptVirModel->pptTexInfo[v7];
      }
      while ( v5 );
    }
  }
}

// source: e/3/mesh3d.c:2090  [anchor-mhash]
void __cdecl Mesh3D_RestoreAnimTextures(struct VirModel_s *ptVirModel)
{
  struct Model_s *ptModel; // eax
  int nAnimTextures; // ecx
  struct ModelAnimTexInfo_s *atAnimTexInfo; // eax
  int *p_iTextureToAnimate; // eax
  int v5; // esi
  struct TexInfo_s *v6; // ebx

  ptModel = ptVirModel->ptModel;
  nAnimTextures = ptModel->nAnimTextures;
  if ( nAnimTextures )
  {
    atAnimTexInfo = ptModel->atAnimTexInfo;
    if ( nAnimTextures > 0 )
    {
      p_iTextureToAnimate = &atAnimTexInfo->iTextureToAnimate;
      do
      {
        v5 = *p_iTextureToAnimate;
        v6 = (struct TexInfo_s *)p_iTextureToAnimate[1];
        p_iTextureToAnimate += 5;
        --nAnimTextures;
        ptVirModel->pptTexInfo[v5] = v6;
      }
      while ( nAnimTextures );
    }
  }
}

// source: e/3/mesh3d.c:2131  [anchor-hash]
unsigned int __cdecl Mesh3D_GetAnimTexBufferSize(struct VirModel_s *ptVirModel)
{
  return 4 * ptVirModel->ptModel->nAnimTextures;
}

// source: e/3/mesh3d.c:2154  [size]
void __cdecl Mesh3D_InitAnimTexBuffer(struct VirModel_s *ptVirModel, unsigned int *ptAnimTexBuffer)
{
  struct Model_s *ptModel; // eax
  int v3; // ecx
  int v4; // edx

  if ( ptAnimTexBuffer )
  {
    ptModel = ptVirModel->ptModel;
    v3 = 0;
    if ( ptModel->nAnimTextures > 0 )
    {
      v4 = 0;
      do
      {
        ptAnimTexBuffer[v3] = ptModel->atAnimTexInfo[v4].nActiveFrame;
        ptModel = ptVirModel->ptModel;
        ++v3;
        ++v4;
      }
      while ( v3 < ptModel->nAnimTextures );
    }
  }
}

// source: e/3/mesh3d.c:2181  [size]
void __cdecl Mesh3D_ApplyAnimTexBuffer(struct VirModel_s *ptVirModel, unsigned int *ptAnimTexBuffer)
{
  struct Model_s *ptModel; // eax
  int v3; // ecx
  int v4; // edx

  if ( ptAnimTexBuffer )
  {
    ptModel = ptVirModel->ptModel;
    v3 = 0;
    if ( ptModel->nAnimTextures > 0 )
    {
      v4 = 0;
      do
      {
        ptModel->atAnimTexInfo[v4].nActiveFrame = ptAnimTexBuffer[v3];
        ptModel = ptVirModel->ptModel;
        ++v3;
        ++v4;
      }
      while ( v3 < ptModel->nAnimTextures );
    }
  }
}

// source: e/3/mesh3d.c:2205  [size]
int __cdecl Mesh3D_GetUpdateMeshRenderModeMethod()
{
  return Mesh3D_eUpdateMeshRenderModeMethod;
}
