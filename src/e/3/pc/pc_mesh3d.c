/* e/3/pc/pc_mesh3d.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: e/3/pc/pc_mesh3d.c:175  [size]
enum bool __cdecl Mesh3D_TraceTexture(
        struct VirModel_s *ptVirModel,
        struct MultiMesh_Face_t *ptCollFace,
        float vU,
        float vV)
{
  return false;
}

// source: e/3/pc/pc_mesh3d.c:344  [anchor-mhash]
void __cdecl Mesh3D_InvalidateSplineMeshVertexList(
        struct SplineObjSegment_s *ptSplineObjSegment)
{
  int v1; // eax

  v1 = 0;
  while ( ptSplineObjSegment != (struct SplineObjSegment_s *)Mesh3D_aptPreCalcObj[v1] )
  {
    if ( ++v1 >= 1 )
      return;
  }
  Mesh3D_aptPreCalcObj[v1] = nullptr;
  Mesh3D_aiPreCalcObjLOD[v1] = 0;
}

// source: e/3/pc/pc_mesh3d.c:378  [size]
struct real32x3_t *__cdecl Mesh3D_GetSplineMeshVertexList(
        struct SplineObjSegment_s *ptSplineObjSegment,
        int iLOD,
        char isForceCalculation,
        char isTemporary)
{
  return nullptr;
}

// source: e/3/pc/pc_mesh3d.c:535  [size]
struct real32x3_t *__cdecl Mesh3D_GetSplineMultiMeshVertexList(
        struct SplineObjSegment_s *ptSplineObjSegment,
        int iLOD,
        int iMesh,
        char isForceCalculation,
        char isTemporary,
        int *pnNumVertices)
{
  struct MultiMesh_Mesh_t *v6; // esi
  float *p_vX; // ecx
  struct real32x3_t *v8; // edi
  int v9; // eax
  float *v10; // ebx
  double v11; // st7
  double v12; // st6
  double v13; // st5
  double v14; // rt1
  double v15; // st5
  double v16; // st6
  char isFlip; // al
  double vEndX; // st7
  double v19; // st7
  double v20; // st6
  double v21; // st5
  int v22; // esi
  double v23; // st5
  float *v24; // eax
  double v25; // st4
  float *v26; // ebx
  double v27; // st3
  double v28; // st4
  double v29; // st3
  double v30; // st2
  double v31; // st1
  double v32; // st0
  int v33; // eax
  double v34; // st3
  float v1DivDeltaXa; // [esp+10h] [ebp-28h]
  int v1DivDeltaX; // [esp+10h] [ebp-28h]
  int iVertex; // [esp+18h] [ebp-20h]
  struct MultiMesh_Mesh_t *ptCollMesh; // [esp+1Ch] [ebp-1Ch]
  float Real32x3_Rotate_tTemp; // [esp+20h] [ebp-18h]
  float Real32x3_Rotate_tTempa; // [esp+20h] [ebp-18h]
  float Real32x3_Rotate_tTemp_4; // [esp+24h] [ebp-14h]
  float Real32x3_Rotate_tTemp_8; // [esp+28h] [ebp-10h]
  float Real32x3_Rotate_tTemp_8a; // [esp+28h] [ebp-10h]
  float Real32x3_Rotate_tTemp_8b; // [esp+28h] [ebp-10h]
  float tDisplacement; // [esp+2Ch] [ebp-Ch]
  float tDisplacementa; // [esp+2Ch] [ebp-Ch]
  float tDisplacement_8; // [esp+34h] [ebp-4h]
  float tDisplacement_8a; // [esp+34h] [ebp-4h]

  v6 = (struct MultiMesh_Mesh_t *)((char *)ptSplineObjSegment->tRigidDynCubeObj.tModelObj.ptLODVirModel->aptVirModel[iLOD]->ptModel->ptMesh->pxCollisionMesh
                                 + 32 * iMesh);
  p_vX = &v6->ptVertex->tPos.vX;
  ptCollMesh = v6;
  v8 = Mesh3D_atTempPos;
  if ( ptSplineObjSegment->isLinear )
  {
    v9 = 0;
    for ( tDisplacement = (ptSplineObjSegment->vStartX + ptSplineObjSegment->vEndX) * 0.5;
          v9 < v6->nNumVertices;
          v10[2] = Real32x3_Rotate_tTemp_8 )
    {
      v10 = &v8->vX;
      v11 = *p_vX - tDisplacement;
      ++v9;
      v12 = p_vX[1];
      p_vX += 5;
      v13 = *(p_vX - 3);
      ++v8;
      Real32x3_Rotate_tTemp = v11 * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tX.vX
                            + v13 * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tX.vZ
                            + v12 * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tX.vY;
      Real32x3_Rotate_tTemp_4 = v11 * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tY.vX
                              + v13 * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tY.vZ
                              + v12 * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tY.vY;
      v14 = v11 * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vX;
      v15 = v13 * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vZ;
      v16 = v12 * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vY;
      *v10 = Real32x3_Rotate_tTemp;
      v10[1] = Real32x3_Rotate_tTemp_4;
      Real32x3_Rotate_tTemp_8 = v14 + v15 + v16;
    }
  }
  else
  {
    isFlip = ptSplineObjSegment->isFlip;
    if ( isFlip )
      vEndX = ptSplineObjSegment->vEndX;
    else
      vEndX = ptSplineObjSegment->vStartX;
    v19 = -vEndX;
    v1DivDeltaXa = 1.0 / (ptSplineObjSegment->vEndX - ptSplineObjSegment->vStartX);
    v20 = (double)ptSplineObjSegment->nAreas * v1DivDeltaXa;
    if ( isFlip )
      v20 = -v20;
    iVertex = 0;
    if ( v6->nNumVertices > 0 )
    {
      do
      {
        v21 = (v19 + *p_vX) * v20;
        v22 = (__int64)v21;
        v1DivDeltaX = v22;
        if ( v22 == ptSplineObjSegment->nAreas )
          v1DivDeltaX = --v22;
        v23 = v21 - (double)v1DivDeltaX;
        if ( v23 >= 0.0 )
        {
          if ( v23 > 1.0 )
            v23 = 1.0;
        }
        else
        {
          v23 = 0.0;
        }
        v24 = (float *)(&ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask + v22);
        v25 = v24[150] * p_vX[2];
        v26 = (float *)((char *)ptSplineObjSegment + 12 * v22);
        v27 = v24[149] * p_vX[1];
        p_vX += 5;
        ++v8;
        Real32x3_Rotate_tTemp_8a = v24[156] * *(p_vX - 3) + v24[155] * *(p_vX - 4);
        Real32x3_Rotate_tTempa = v25 + v27 + v26[85];
        v28 = v24[153] * *(p_vX - 3) + v24[152] * *(p_vX - 4) + v26[86];
        Real32x3_Rotate_tTemp_8b = Real32x3_Rotate_tTemp_8a + ptSplineObjSegment->atAreaPos[v22].vZ;
        v29 = v24[160] * *(p_vX - 3) + v24[159] * *(p_vX - 4);
        v30 = v24[163] * *(p_vX - 3) + v24[162] * *(p_vX - 4);
        v31 = v24[166] * *(p_vX - 3);
        v32 = v24[165];
        v33 = 3 * v22 + 90;
        v6 = ptCollMesh;
        tDisplacement_8 = v31 + v32 * *(p_vX - 4);
        tDisplacementa = v29 + v26[88];
        v34 = v30 + v26[89];
        ++iVertex;
        tDisplacement_8a = tDisplacement_8
                         + *((float *)&ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.ptNext
                           + v33);
        v8[-1].vX = (tDisplacementa - Real32x3_Rotate_tTempa) * v23 + Real32x3_Rotate_tTempa;
        v8[-1].vY = (v34 - v28) * v23 + v28;
        v8[-1].vZ = (tDisplacement_8a - Real32x3_Rotate_tTemp_8b) * v23 + Real32x3_Rotate_tTemp_8b;
      }
      while ( iVertex < ptCollMesh->nNumVertices );
    }
  }
  if ( pnNumVertices )
    *pnNumVertices = v6->nNumVertices;
  return &v8[-v6->nNumVertices];
}

// source: e/3/pc/pc_mesh3d.c:664  [size]
void __cdecl Mesh3D_HardwareOpen()
{
  Mesh3D_aptPreCalcObj[0] = nullptr;
}

// source: e/3/pc/pc_mesh3d.c:684  [size]
void __cdecl Mesh3D_StaticMeshIlluminationFade(
        struct RigidDynCubeObj_t *ptRigidDynCubeObj,
        int iParentLOD,
        void *pxData,
        int *pnLightList,
        int nLightNum,
        struct HazingDynCubeObj_t **pptHazingList,
        int nNumHazingBox,
        struct real32x3_t *ptIlluminationFadeColor)
{
  ;
}
