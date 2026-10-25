/* e/3/splineobjsegment.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: e/3/splineobjsegment.c:54  [size]
void __cdecl SplineObjSegment_BspTreeGenerationSizeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // eax
  int ptHead; // ecx
  int v4; // eax
  _DWORD *v5; // esi
  _DWORD *v6; // eax
  int v7; // ecx

  v2 = *(_DWORD *)&ptQTask[2].eQTaskType;
  if ( v2 )
  {
    ptHead = (int)ptQTask[7].tQTaskChildren.ptHead;
    if ( ptHead != -1 )
    {
      v4 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v2 + 4 * ptHead) + 12) + 12);
      if ( !*(_DWORD *)(v4 + 40) )
      {
        v5 = *(_DWORD **)(v4 + 44);
        if ( v5 )
        {
          if ( *v5 )
          {
            Mesh3D_GetSplineMultiMeshVertexList((struct SplineObjSegment_s *)ptQTask, ptHead, 0, 1, 0, (int *)&ptQTask);
            v6 = pxContext;
            v7 = *(_DWORD *)pxContext;
            *((_DWORD *)pxContext + 1) += (int)(3 * *v5);
            *v6 = (char *)ptQTask + v7;
          }
        }
      }
    }
  }
}

// source: e/3/splineobjsegment.c:129  [size]
void __cdecl SplineObjSegment_BspTreeGenerationListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { int nI; };
    struct { int nIa; };
    struct { char igi2_o2[4]; int v37; };
    struct { char igi2_o3[8]; struct real32x3_t *ptVertexList; };
    struct { char igi2_o4[12]; struct MultiMesh_Mesh_t *ptCollMesh; };
    struct { char igi2_o5[16]; struct real32x3_t tTemp_; };
    struct { char igi2_o6[28]; struct real32x3_t tNormal; };
    struct { char igi2_o7[40]; struct real32x3_t tEdge1; };
    char igi2_extent[52];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double *v2; // esi
  int v3; // eax
  int ptHead; // ecx
  int v5; // eax
  struct MultiMesh_Mesh_t *v6; // edi
  struct real32x3_t *SplineMultiMeshVertexList; // ebx
  bool v8; // cc
  struct MultiMesh_Face_t *ptFace; // esi
  int v10; // edi
  unsigned __int16 *aiVertex; // esi
  float *p_vX; // eax
  float *v13; // edi
  float *v14; // edx
  double v15; // st7
  double v16; // st6
  double v17; // st5
  double v18; // st4
  float vX; // edi
  long double v20; // st7
  unsigned int v21; // eax
  float vY; // edx
  unsigned __int16 *p_iMaterial; // ebx
  int v24; // eax
  unsigned int v25; // edx
  int v26; // ebx
  int v27; // eax
  int v28; // ebx
  int v29; // eax
  float *p_vZ; // eax
  double v31; // st7
  int v32; // ebx
  int v33; // edx
  int v34; // ebx

  v2 = (double *)ptQTask;
  v3 = *(_DWORD *)&ptQTask[2].eQTaskType;
  if ( v3 )
  {
    ptHead = (int)ptQTask[7].tQTaskChildren.ptHead;
    if ( ptHead != -1 )
    {
      v5 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v3 + 4 * ptHead) + 12) + 12);
      if ( !*(_DWORD *)(v5 + 40) )
      {
        igi2_frame.ptCollMesh = *(struct MultiMesh_Mesh_t **)(v5 + 44);
        v6 = igi2_frame.ptCollMesh;
        if ( igi2_frame.ptCollMesh )
        {
          if ( igi2_frame.ptCollMesh->nNumFaces )
          {
            SplineMultiMeshVertexList = Mesh3D_GetSplineMultiMeshVertexList(
                                          (struct SplineObjSegment_s *)ptQTask,
                                          ptHead,
                                          0,
                                          1,
                                          0,
                                          (int *)&igi2_frame.ptVertexList);
            v8 = v6->nNumFaces <= 0;
            igi2_frame.ptVertexList = SplineMultiMeshVertexList;
            igi2_frame.nI = 0;
            if ( !v8 )
            {
              igi2_frame.v37 = 0;
              do
              {
                ptFace = v6->ptFace;
                v10 = ptFace[igi2_frame.v37].aiVertex[2];
                aiVertex = ptFace[igi2_frame.v37].aiVertex;
                p_vX = &SplineMultiMeshVertexList[*aiVertex].vX;
                v13 = &SplineMultiMeshVertexList[v10].vX;
                v14 = &SplineMultiMeshVertexList[aiVertex[1]].vX;
                v15 = *v13 - *p_vX;
                v16 = v13[1] - p_vX[1];
                v17 = v13[2] - p_vX[2];
                igi2_frame.tEdge1.vX = *v14 - *p_vX;
                igi2_frame.tEdge1.vY = v14[1] - p_vX[1];
                v18 = v14[2] - p_vX[2];
                igi2_frame.tTemp_.vX = v18 * v16 - igi2_frame.tEdge1.vY * v17;
                vX = igi2_frame.tTemp_.vX;
                igi2_frame.tTemp_.vY = -(v18 * v15 - igi2_frame.tEdge1.vX * v17);
                igi2_frame.tNormal.vY = igi2_frame.tTemp_.vY;
                igi2_frame.tTemp_.vZ = igi2_frame.tEdge1.vY * v15 - igi2_frame.tEdge1.vX * v16;
                igi2_frame.tNormal.vZ = igi2_frame.tTemp_.vZ;
                if ( igi2_frame.tTemp_.vX != 0.0 || igi2_frame.tTemp_.vY != 0.0 || igi2_frame.tTemp_.vZ != 0.0 )
                {
                  v20 = 1.0 / sqrt(igi2_frame.tTemp_.vX * igi2_frame.tTemp_.vX + igi2_frame.tTemp_.vY * igi2_frame.tTemp_.vY + igi2_frame.tTemp_.vZ * igi2_frame.tTemp_.vZ);
                  igi2_frame.tNormal.vX = igi2_frame.tTemp_.vX * v20;
                  vX = igi2_frame.tNormal.vX;
                  igi2_frame.tNormal.vY = igi2_frame.tNormal.vY * v20;
                  igi2_frame.tNormal.vZ = igi2_frame.tNormal.vZ * v20;
                }
                v21 = *((_DWORD *)pxContext + 3) + 12 * (*((_DWORD *)pxContext + 7) / 3u);
                vY = igi2_frame.tNormal.vY;
                *(float *)v21 = vX;
                v6 = igi2_frame.ptCollMesh;
                *(float *)(v21 + 4) = vY;
                *(float *)(v21 + 8) = igi2_frame.tNormal.vZ;
                p_iMaterial = &v6->ptMaterial[aiVertex[3]].iMaterial;
                v24 = *((_DWORD *)pxContext + 2);
                v25 = *((_DWORD *)pxContext + 7) / 3u;
                if ( *p_iMaterial == 0xFFFF )
                  *(_BYTE *)(v25 + v24) = 1;
                else
                  *(_BYTE *)(v25 + v24) = *(_BYTE *)p_iMaterial;
                *(_DWORD *)(*((_DWORD *)pxContext + 1) + 4 * *((_DWORD *)pxContext + 7)) = *((_DWORD *)pxContext + 6)
                                                                                         + *aiVertex;
                v26 = *((_DWORD *)pxContext + 6);
                v27 = *((_DWORD *)pxContext + 7) + 1;
                *((_DWORD *)pxContext + 7) = v27;
                *(_DWORD *)(*((_DWORD *)pxContext + 1) + 4 * v27) = v26 + aiVertex[1];
                v28 = *((_DWORD *)pxContext + 7) + 1;
                *((_DWORD *)pxContext + 7) = v28;
                v29 = v28;
                SplineMultiMeshVertexList = igi2_frame.ptVertexList;
                *(_DWORD *)(*((_DWORD *)pxContext + 1) + 4 * v29) = *((_DWORD *)pxContext + 6) + aiVertex[2];
                ++*((_DWORD *)pxContext + 7);
                v8 = ++igi2_frame.nI < v6->nNumFaces;
                ++igi2_frame.v37;
              }
              while ( v8 );
              v2 = (double *)ptQTask;
            }
            igi2_frame.nIa = 0;
            if ( v6->nNumVertices > 0 )
            {
              p_vZ = &SplineMultiMeshVertexList->vZ;
              do
              {
                v31 = *(p_vZ - 2) + v2[5];
                p_vZ += 3;
                *(double *)(*(_DWORD *)pxContext + 24 * *((_DWORD *)pxContext + 6)) = v31;
                v32 = *(_DWORD *)pxContext;
                v33 = *((_DWORD *)pxContext + 6) + 1;
                *((_DWORD *)pxContext + 6) = v33;
                *(double *)(v32 + 24 * v33 + 8) = *(p_vZ - 4) + v2[6];
                v34 = *((_DWORD *)pxContext + 6) + 1;
                *((_DWORD *)pxContext + 6) = v34;
                *(double *)(*(_DWORD *)pxContext + 24 * v34 + 16) = *(p_vZ - 3) + v2[7];
                ++*((_DWORD *)pxContext + 6);
                ++igi2_frame.nIa;
              }
              while ( igi2_frame.nIa < v6->nNumVertices );
            }
          }
        }
      }
    }
  }
}

// source: e/3/splineobjsegment.c:250  [size]
void __cdecl SplineObjSegment_CollisionEvalHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_BYTE *)pxContext = 1;
}

// source: e/3/splineobjsegment.c:274  [size]
void __cdecl SplineObjSegment_TransformSpherePos(
        struct SplineObjSegment_s *ptSplineObjSegment,
        struct CollisionSphereTree_t *ptTree)
{
  struct MultiMesh_Sphere_t *ptSphere; // ecx
  int v3; // eax
  float *p_vX; // edi
  double v5; // st7
  double vY; // st6
  double vZ; // st5
  double v8; // rt1
  double v9; // st5
  double v10; // st6
  char isFlip; // al
  double vEndX; // st7
  double v13; // st7
  double v14; // st6
  int i; // ebx
  double v16; // st5
  int v17; // esi
  double v18; // st5
  float *v19; // eax
  double v20; // st4
  float *v21; // edi
  double v22; // st3
  double v23; // st4
  double v24; // st3
  float v1DivDeltaXa; // [esp+Ch] [ebp-20h]
  int v1DivDeltaX; // [esp+Ch] [ebp-20h]
  float Real32x3_Rotate_tTemp; // [esp+14h] [ebp-18h]
  float Real32x3_Rotate_tTempa; // [esp+14h] [ebp-18h]
  float Real32x3_Rotate_tTemp_4; // [esp+18h] [ebp-14h]
  float Real32x3_Rotate_tTemp_8; // [esp+1Ch] [ebp-10h]
  float Real32x3_Rotate_tTemp_8a; // [esp+1Ch] [ebp-10h]
  float Real32x3_Rotate_tTemp_8b; // [esp+1Ch] [ebp-10h]
  float tDisplacement; // [esp+20h] [ebp-Ch]
  float tDisplacementa; // [esp+20h] [ebp-Ch]
  float tDisplacement_8; // [esp+28h] [ebp-4h]
  float tDisplacement_8a; // [esp+28h] [ebp-4h]

  ptSphere = ptTree->ptSphere;
  if ( ptSplineObjSegment->isLinear )
  {
    v3 = 0;
    for ( tDisplacement = (ptSplineObjSegment->vStartX + ptSplineObjSegment->vEndX) * 0.5;
          v3 < ptTree->nNumSpheres;
          p_vX[2] = Real32x3_Rotate_tTemp_8 )
    {
      p_vX = &ptSphere->tSphere.tPos.vX;
      v5 = ptSphere->tSphere.tPos.vX - tDisplacement;
      ++v3;
      vY = ptSphere->tSphere.tPos.vY;
      ++ptSphere;
      vZ = ptSphere[-1].tSphere.tPos.vZ;
      Real32x3_Rotate_tTemp = v5 * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tX.vX
                            + vZ * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tX.vZ
                            + vY * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tX.vY;
      Real32x3_Rotate_tTemp_4 = vZ * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tY.vZ
                              + vY * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tY.vY
                              + v5 * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tY.vX;
      v8 = v5 * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vX;
      v9 = vZ * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vZ;
      v10 = vY * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vY;
      *p_vX = Real32x3_Rotate_tTemp;
      p_vX[1] = Real32x3_Rotate_tTemp_4;
      Real32x3_Rotate_tTemp_8 = v8 + v9 + v10;
    }
  }
  else
  {
    isFlip = ptSplineObjSegment->isFlip;
    if ( isFlip )
      vEndX = ptSplineObjSegment->vEndX;
    else
      vEndX = ptSplineObjSegment->vStartX;
    v13 = -vEndX;
    v1DivDeltaXa = 1.0 / (ptSplineObjSegment->vEndX - ptSplineObjSegment->vStartX);
    v14 = (double)ptSplineObjSegment->nAreas * v1DivDeltaXa;
    if ( isFlip )
      v14 = -v14;
    for ( i = 0;
          i < ptTree->nNumSpheres;
          ptSphere[-1].tSphere.tPos.vZ = (tDisplacement_8a - Real32x3_Rotate_tTemp_8b) * v18 + Real32x3_Rotate_tTemp_8b )
    {
      v16 = (v13 + ptSphere->tSphere.tPos.vX) * v14;
      v17 = (__int64)v16;
      v1DivDeltaX = v17;
      if ( v17 == ptSplineObjSegment->nAreas )
        v1DivDeltaX = --v17;
      v18 = v16 - (double)v1DivDeltaX;
      if ( v18 >= 0.0 )
      {
        if ( v18 > 1.0 )
          v18 = 1.0;
      }
      else
      {
        v18 = 0.0;
      }
      v19 = (float *)(&ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask + v17);
      v20 = v19[150] * ptSphere->tSphere.tPos.vZ;
      v21 = (float *)((char *)ptSplineObjSegment + 12 * v17);
      v22 = v19[149] * ptSphere->tSphere.tPos.vY;
      ++i;
      ++ptSphere;
      Real32x3_Rotate_tTemp_8a = v19[156] * ptSphere[-1].tSphere.tPos.vZ + v19[155] * ptSphere[-1].tSphere.tPos.vY;
      Real32x3_Rotate_tTempa = v20 + v22 + v21[85];
      v23 = v19[153] * ptSphere[-1].tSphere.tPos.vZ + v19[152] * ptSphere[-1].tSphere.tPos.vY + v21[86];
      Real32x3_Rotate_tTemp_8b = Real32x3_Rotate_tTemp_8a + ptSplineObjSegment->atAreaPos[v17].vZ;
      tDisplacement_8 = v19[166] * ptSphere[-1].tSphere.tPos.vZ + v19[165] * ptSphere[-1].tSphere.tPos.vY;
      tDisplacementa = v19[160] * ptSphere[-1].tSphere.tPos.vZ + v19[159] * ptSphere[-1].tSphere.tPos.vY + v21[88];
      v24 = v19[163] * ptSphere[-1].tSphere.tPos.vZ + v19[162] * ptSphere[-1].tSphere.tPos.vY + v21[89];
      tDisplacement_8a = tDisplacement_8 + ptSplineObjSegment->atAreaPos[v17 + 1].vZ;
      ptSphere[-1].tSphere.tPos.vX = (tDisplacementa - Real32x3_Rotate_tTempa) * v18 + Real32x3_Rotate_tTempa;
      ptSphere[-1].tSphere.tPos.vY = (v24 - v23) * v18 + v23;
    }
  }
}

// source: e/3/splineobjsegment.c:375  [anchor-caller]
void __cdecl SplineObjSegment_TraceLinesHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { char isHitFrontFace; };
    struct { char igi2_o1[1]; float tStartPos; };
    struct { char igi2_o2[1]; float tStartPosa; };
    struct { char igi2_o3[5]; float tStartPos_4; };
    struct { char igi2_o4[9]; float tStartPos_8; };
    struct { char igi2_o5[13]; float *vT; };
    struct { char igi2_o6[13]; float vTa; };
    struct { char igi2_o7[13]; float *vTb; };
    struct { char igi2_o8[13]; float vTc; };
    struct { char igi2_o9[20]; char isHit; };
    struct { char igi2_o10[21]; int nLevel; };
    struct { char igi2_o11[27]; char isFirstIteration; };
    struct { char igi2_o12[28]; char isHitCurrentObject; };
    struct { char igi2_o13[29]; double vDistance; };
    struct { char igi2_o14[29]; double vDistancea; };
    struct { char igi2_o15[29]; double vDistanceb; };
    struct { char igi2_o16[29]; double vDistancec; };
    struct { char igi2_o17[29]; double vDistanced; };
    struct { char igi2_o18[29]; double vDistancee; };
    struct { char igi2_o19[41]; float v177; };
    struct { char igi2_o20[41]; float v178; };
    struct { char igi2_o21[41]; float v179; };
    struct { char igi2_o22[41]; float v180; };
    struct { char igi2_o23[41]; float v181; };
    struct { char igi2_o24[41]; float v182; };
    struct { char igi2_o25[45]; struct QMaterial_t *ptMaterial; };
    struct { char igi2_o26[45]; float ptMateriala; };
    struct { char igi2_o27[45]; struct QTask_s *ptMaterialb; };
    struct { char igi2_o28[45]; float ptMaterialc; };
    struct { char igi2_o29[45]; struct QTask_s *ptMateriald; };
    struct { char igi2_o30[49]; float tHitPos; };
    struct { char igi2_o31[49]; float tHitPosa; };
    struct { char igi2_o32[49]; float tHitPosb; };
    struct { char igi2_o33[53]; float tHitPos_4; };
    struct { char igi2_o34[53]; float tHitPos_4a; };
    struct { char igi2_o35[53]; float tHitPos_4b; };
    struct { char igi2_o36[57]; float tHitPos_8; };
    struct { char igi2_o37[57]; float tHitPos_8a; };
    struct { char igi2_o38[57]; float tHitPos_8b; };
    struct { char igi2_o39[61]; unsigned int bColor; };
    struct { char igi2_o40[61]; double bColora; };
    struct { char igi2_o41[61]; double bColorb; };
    struct { char igi2_o42[61]; double bColorc; };
    struct { char igi2_o43[69]; struct QIntersection_s *ptIntersection; };
    struct { char igi2_o44[73]; float v202; };
    struct { char igi2_o45[73]; float v203; };
    struct { char igi2_o46[73]; float v204; };
    struct { char igi2_o47[73]; float v205; };
    struct { char igi2_o48[77]; float tMax; };
    struct { char igi2_o49[77]; float tMaxa; };
    struct { char igi2_o50[81]; float tMax_4; };
    struct { char igi2_o51[81]; float tMax_4a; };
    struct { char igi2_o52[85]; float tMax_8; };
    struct { char igi2_o53[85]; float tMax_8a; };
    struct { char igi2_o54[89]; float tEdge0; };
    struct { char igi2_o55[93]; float tEdge0_4; };
    struct { char igi2_o56[97]; float tEdge0_8; };
    struct { char igi2_o57[101]; float v215; };
    struct { char igi2_o58[105]; float v216; };
    struct { char igi2_o59[109]; float v217; };
    struct { char igi2_o60[113]; float tMin; };
    struct { char igi2_o61[113]; float tMina; };
    struct { char igi2_o62[117]; float tMin_4; };
    struct { char igi2_o63[117]; float tMin_4a; };
    struct { char igi2_o64[121]; float tMin_8; };
    struct { char igi2_o65[121]; float tMin_8a; };
    struct { char igi2_o66[125]; struct real32x3_t *ptVertex2; };
    struct { char igi2_o67[125]; struct real32x3_t *ptVertex2a; };
    struct { char igi2_o68[125]; struct real32x3_t *ptVertex2b; };
    struct { char igi2_o69[125]; struct real32x3_t *ptVertex2c; };
    struct { char igi2_o70[125]; struct real32x3_t *ptVertex2d; };
    struct { char igi2_o71[125]; float ptVertex2e; };
    struct { char igi2_o72[132]; char isVerticesCalculated; };
    struct { char igi2_o73[133]; float v231; };
    struct { char igi2_o74[133]; float v232; };
    struct { char igi2_o75[133]; float v233; };
    struct { char igi2_o76[133]; float v234; };
    struct { char igi2_o77[133]; float v235; };
    struct { char igi2_o78[133]; double v236; };
    struct { char igi2_o79[141]; double vDot; };
    struct { char igi2_o80[141]; double vDota; };
    struct { char igi2_o81[141]; double vDotb; };
    struct { char igi2_o82[141]; double vDotc; };
    struct { char igi2_o83[141]; double vDotd; };
    struct { char igi2_o84[141]; double vDote; };
    struct { char igi2_o85[153]; float tEndPos; };
    struct { char igi2_o86[153]; float tEndPosa; };
    struct { char igi2_o87[157]; float tEndPos_4; };
    struct { char igi2_o88[161]; float tEndPos_8; };
    struct { char igi2_o89[165]; struct MultiMesh_Mesh_t *ptCollMesh; };
    struct { char igi2_o90[169]; float tDelta; };
    struct { char igi2_o91[169]; float tDeltaa; };
    struct { char igi2_o92[173]; float tDelta_4; };
    struct { char igi2_o93[173]; float tDelta_4a; };
    struct { char igi2_o94[177]; float tDelta_8; };
    struct { char igi2_o95[177]; float tDelta_8a; };
    struct { char igi2_o96[181]; double vClosest; };
    struct { char igi2_o97[189]; struct MultiMesh_Sphere_t *ptFirstSphere; };
    struct { char igi2_o98[189]; struct MultiMesh_Sphere_t *ptFirstSpherea; };
    struct { char igi2_o99[193]; float tPos; };
    struct { char igi2_o100[197]; float tPos_4; };
    struct { char igi2_o101[201]; float tPos_8; };
    struct { char igi2_o102[205]; float v260; };
    struct { char igi2_o103[209]; float v261; };
    struct { char igi2_o104[213]; float v262; };
    struct { char igi2_o105[217]; float tNormal; };
    struct { char igi2_o106[221]; float tNormal_4; };
    struct { char igi2_o107[225]; float tNormal_8; };
    struct { char igi2_o108[229]; double v1DivSquaredDistance; };
    struct { char igi2_o109[229]; double v1DivSquaredDistancea; };
    struct { char igi2_o110[229]; double v1DivSquaredDistanceb; };
    struct { char igi2_o111[241]; float tTemp__4; };
    struct { char igi2_o112[249]; float v270; };
    struct { char igi2_o113[249]; float v271; };
    struct { char igi2_o114[253]; int iFace; };
    struct { char igi2_o115[253]; int iFacea; };
    struct { char igi2_o116[257]; float v274; };
    struct { char igi2_o117[257]; float vRadius; };
    struct { char igi2_o118[261]; struct MultiMesh_Face_t *ptHitFace; };
    struct { char igi2_o119[265]; float tHitUV; };
    struct { char igi2_o120[269]; float tHitUV_4; };
    struct { char igi2_o121[273]; int iHitLightmap; };
    struct { char igi2_o122[277]; float vLineLength; };
    struct { char igi2_o123[277]; float *vLineLengtha; };
    struct { char igi2_o124[277]; float vLineLengthb; };
    struct { char igi2_o125[281]; struct real64x3_t *ptEndPos; };
    struct { char igi2_o126[285]; float tEdge1; };
    struct { char igi2_o127[289]; float tEdge1_4; };
    struct { char igi2_o128[293]; float tEdge1_8; };
    struct { char igi2_o129[297]; struct MultiMesh_Vertex_t *ptVertexPos; };
    struct { char igi2_o130[301]; struct real64x3_t *ptStartPos; };
    struct { char igi2_o131[305]; float v289; };
    struct { char igi2_o132[309]; float v290; };
    struct { char igi2_o133[313]; float v291; };
    struct { char igi2_o134[317]; float v292; };
    struct { char igi2_o135[321]; float v293; };
    struct { char igi2_o136[325]; float v294; };
    struct { char igi2_o137[329]; float tLight; };
    struct { char igi2_o138[333]; float tLight_4; };
    struct { char igi2_o139[341]; float v297; };
    struct { char igi2_o140[345]; float vY; };
    struct { char igi2_o141[353]; struct Mesh3D_Mesh_t *ptMesh; };
    struct { char igi2_o142[357]; int iCheck; };
    struct { char igi2_o143[361]; float tUVEdge1; };
    struct { char igi2_o144[365]; float tUVEdge1_4; };
    struct { char igi2_o145[365]; float tUVEdge1_4a; };
    struct { char igi2_o146[369]; float v304; };
    struct { char igi2_o147[373]; float v305; };
    struct { char igi2_o148[373]; float v306; };
    struct { char igi2_o149[377]; struct real32x3_t *ptVertexList; };
    struct { char igi2_o150[381]; float tUV; };
    struct { char igi2_o151[385]; float tUV_4; };
    struct { char igi2_o152[385]; float tUV_4a; };
    struct { char igi2_o153[389]; float v311; };
    struct { char igi2_o154[393]; float v312; };
    struct { char igi2_o155[393]; float v313; };
    struct { char igi2_o156[413]; float v314; };
    struct { char igi2_o157[421]; float Real32x3_RotateInverse_tTemp; };
    struct { char igi2_o158[425]; float Real32x3_RotateInverse_tTemp_4; };
    struct { char igi2_o159[429]; float Real32x3_RotateInverse_tTemp_8; };
    struct { char igi2_o160[433]; float Real32x3_Rotate_tTemp; };
    struct { char igi2_o161[437]; float Real32x3_Rotate_tTemp_4; };
    struct { char igi2_o162[441]; float Real32x3_Rotate_tTemp_8; };
    struct { char igi2_o163[445]; float v321; };
    struct { char igi2_o164[449]; float v322; };
    struct { char igi2_o165[453]; float v323; };
    struct { char igi2_o166[457]; float v324; };
    struct { char igi2_o167[461]; float v325; };
    struct { char igi2_o168[465]; float v326; };
    struct { char igi2_o169[469]; float v327; };
    struct { char igi2_o170[473]; float v328; };
    struct { char igi2_o171[477]; float v329; };
    struct { char igi2_o172[481]; float v330; };
    struct { char igi2_o173[485]; float v331; };
    struct { char igi2_o174[489]; float v332; };
    struct { char igi2_o175[493]; float v333; };
    struct { char igi2_o176[497]; float v334; };
    struct { char igi2_o177[505]; float v335; };
    struct { char igi2_o178[509]; float v336; };
    struct { char igi2_o179[517]; double v337; };
    struct { char igi2_o180[525]; float tAbsNormal; };
    struct { char igi2_o181[541]; float v339; };
    struct { char igi2_o182[545]; float v340; };
    struct { char igi2_o183[549]; struct real64x3_t tTempPos; };
    struct { char igi2_o184[577]; float v342; };
    struct { char igi2_o185[589]; struct real32x2_t tUVEdge0; };
    struct { char igi2_o186[597]; float v344; };
    struct { char igi2_o187[605]; struct MultiMesh_Sphere_t *aptSphereStack[100]; };
    struct { char igi2_o188[1005]; _DWORD v346[100]; };
    char igi2_extent[1405];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // eax
  struct QTask_s *ptHead; // ecx
  int v4; // ecx
  int v5; // edx
  int v6; // eax
  bool v7; // zf
  struct MultiMesh_Mesh_t *v8; // eax
  struct MultiMesh_Vertex_t *ptVertex; // edx
  __int16 v10; // ax
  void (__cdecl *pfHandler)(struct QTask_s *, _DWORD); // eax
  double v12; // st7
  double *p_vX; // edx
  double v14; // st7
  double v15; // st7
  double v16; // st7
  double v17; // st7
  double v18; // st7
  double v19; // st7
  struct MultiMesh_Sphere_t *v20; // esi
  double vX; // st7
  double v22; // st7
  double v23; // st6
  double v24; // st5
  double v25; // st7
  double v26; // st7
  double v27; // st7
  double v28; // st7
  double v29; // st7
  double v30; // st7
  double v31; // st7
  struct real32x3_t *SplineMultiMeshVertexList; // eax
  int v33; // edx
  unsigned __int16 iNext; // si
  double v35; // st7
  double v36; // st5
  unsigned __int16 iChild; // ax
  double v38; // st7
  double v39; // st5
  unsigned __int16 nFace; // cx
  int v41; // eax
  unsigned __int16 *aiVertex; // edx
  float *v43; // ecx
  float *v44; // edi
  double v45; // st7
  double v46; // st7
  double v47; // st7
  double v48; // st7
  double v49; // st6
  double v50; // st7
  double v51; // st6
  double v52; // st7
  double v53; // st7
  double v54; // st6
  double v55; // st7
  double v56; // st7
  double v57; // st6
  double v58; // st7
  double v59; // st7
  double v60; // st7
  double v61; // st7
  double v62; // st7
  double v63; // st7
  float *v64; // ecx
  unsigned __int16 iMaterial; // ax
  double v66; // st7
  double v67; // st6
  double v68; // st5
  double v69; // st4
  float *v70; // ecx
  long double v71; // st7
  float vZ; // ecx
  double v73; // st7
  struct QReference_s *v74; // eax
  float *v75; // eax
  double v76; // st6
  double v77; // st7
  double v78; // st7
  double v79; // st6
  struct MultiMesh_Sphere_t *ptSphere; // esi
  double v81; // st5
  double v82; // st7
  double v83; // st7
  double v84; // st6
  double v85; // st5
  double v86; // st7
  double v87; // st6
  double v88; // st5
  double v89; // st7
  double v90; // st7
  double v91; // st6
  double v92; // st6
  double v93; // st6
  double v94; // st6
  double v95; // st6
  double v96; // st6
  double v97; // st4
  int v98; // edx
  unsigned __int16 v99; // si
  double v100; // st7
  double v101; // st5
  unsigned __int16 v102; // ax
  double v103; // st7
  double v104; // st5
  unsigned __int16 v105; // cx
  int v106; // eax
  unsigned __int16 *v107; // edi
  float *v108; // ecx
  float *v109; // edx
  double v110; // st7
  double v111; // st7
  double v112; // st7
  double v113; // st7
  double v114; // st6
  double v115; // st7
  double v116; // st7
  double v117; // st6
  double v118; // st7
  double v119; // st7
  double v120; // st7
  double v121; // st6
  double v122; // st7
  double v123; // st7
  double v124; // st6
  double v125; // st7
  double v126; // st7
  double v127; // st7
  double v128; // st7
  double v129; // st7
  double v130; // st7
  double v131; // st7
  float *v132; // edi
  float *v133; // ecx
  float *v134; // esi
  unsigned __int16 v135; // ax
  double v136; // st7
  double v137; // st6
  double v138; // st5
  double v139; // st7
  double v140; // st6
  double v141; // st5
  double v142; // st4
  float *v143; // esi
  long double v144; // st7
  double v145; // st7
  float v146; // ecx
  double v147; // st7
  struct QReference_s *v148; // eax
  struct QReference_s *ptNext; // edi
  float *v150; // eax
  double v151; // st6
  unsigned int Texel; // eax
  double v153; // st7
  struct QIntersection_s *v154; // edx
  double v155; // st7
  double v156; // st7
  bool v157; // cc

  igi2_frame.ptIntersection = *((struct QIntersection_s **)pxContext + 9);
  v2 = *(_DWORD *)&ptQTask[2].eQTaskType;
  igi2_frame.ptStartPos = *(struct real64x3_t **)pxContext;
  igi2_frame.ptEndPos = *((struct real64x3_t **)pxContext + 1);
  igi2_frame.isVerticesCalculated = 0;
  if ( v2 )
  {
    ptHead = ptQTask[7].tQTaskChildren.ptHead;
    if ( ptHead != (struct QTask_s *)-1 )
    {
      v4 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v2 + 4 * (_DWORD)ptHead) + 12) + 12);
      igi2_frame.ptMesh = (struct Mesh3D_Mesh_t *)v4;
      if ( !*(_DWORD *)(v4 + 40) )
      {
        v5 = *(_DWORD *)(v4 + 44);
        v6 = 32 * *((_DWORD *)pxContext + 5);
        v7 = v5 + v6 == 0;
        v8 = (struct MultiMesh_Mesh_t *)(v5 + v6);
        igi2_frame.ptCollMesh = v8;
        if ( !v7 )
        {
          if ( v8->nNumFaces )
          {
            ptVertex = v8->ptVertex;
            v10 = *((_WORD *)pxContext + 6);
            igi2_frame.ptVertexPos = ptVertex;
            if ( v10 == 512
              || (pfHandler = (void (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[v10][ptQTask->eQTaskType].pfHandler) == nullptr
              || (pfHandler(ptQTask, *((_DWORD *)pxContext + 4)), **((_BYTE **)pxContext + 4)) )
            {
              igi2_frame.iCheck = 0;
              if ( *((int *)pxContext + 2) > 0 )
              {
                while ( 1 )
                {
                  igi2_frame.bColor = igi2_frame.ptIntersection->isHit;
                  if ( igi2_frame.bColor )
                    igi2_frame.isHitFrontFace = igi2_frame.ptIntersection->ptEnterMaterial != nullptr;
                  else
                    igi2_frame.isHitFrontFace = 0;
                  v12 = *(double *)&ptQTask[1].ptNext - *(float *)&ptQTask[8].ptPrev;
                  p_vX = &igi2_frame.ptEndPos->vX;
                  igi2_frame.isHit = igi2_frame.ptIntersection->isHit;
                  igi2_frame.isHitCurrentObject = 0;
                  if ( v12 > igi2_frame.ptStartPos->vX && v12 > igi2_frame.ptEndPos->vX )
                    return;
                  v14 = *(float *)&ptQTask[8].ptPrev + *(double *)&ptQTask[1].ptNext;
                  if ( v14 < igi2_frame.ptStartPos->vX && v14 < igi2_frame.ptEndPos->vX )
                    return;
                  v15 = *(double *)&ptQTask[1].tQTaskChildren.ptHead - *(float *)&ptQTask[8].ptPrev;
                  if ( v15 > igi2_frame.ptStartPos->vY && v15 > igi2_frame.ptEndPos->vY )
                    return;
                  v16 = *(float *)&ptQTask[8].ptPrev + *(double *)&ptQTask[1].tQTaskChildren.ptHead;
                  if ( v16 < igi2_frame.ptStartPos->vY && v16 < igi2_frame.ptEndPos->vY )
                    return;
                  v17 = *(double *)&ptQTask[1].tQTaskChildren.ptTail - *(float *)&ptQTask[8].ptPrev;
                  if ( v17 > igi2_frame.ptStartPos->vZ && v17 > igi2_frame.ptEndPos->vZ )
                    return;
                  v18 = *(float *)&ptQTask[8].ptPrev + *(double *)&ptQTask[1].tQTaskChildren.ptTail;
                  if ( v18 < igi2_frame.ptStartPos->vZ && v18 < igi2_frame.ptEndPos->vZ )
                    return;
                  v19 = igi2_frame.ptStartPos->vX - *(double *)&ptQTask[1].ptNext;
                  igi2_frame.nLevel = 0;
                  igi2_frame.isFirstIteration = 1;
                  if ( !LOBYTE(ptQTask[38].tQTaskRefList.ptHead) )
                  {
                    igi2_frame.tStartPos = v19;
                    v20 = *((struct MultiMesh_Sphere_t **)&ptQTask[38].ptNext + 2 * *((_DWORD *)pxContext + 5));
                    igi2_frame.tStartPos_4 = igi2_frame.ptStartPos->vY - *(double *)&ptQTask[1].tQTaskChildren.ptHead;
                    igi2_frame.ptMaterial = *((struct QMaterial_t **)pxContext + 5);
                    igi2_frame.tStartPos_8 = igi2_frame.ptStartPos->vZ - *(double *)&ptQTask[1].tQTaskChildren.ptTail;
                    igi2_frame.ptFirstSphere = v20;
                    vX = igi2_frame.ptEndPos->vX;
                    igi2_frame.aptSphereStack[0] = v20;
                    igi2_frame.tEndPos = vX - *(double *)&ptQTask[1].ptNext;
                    igi2_frame.tEndPos_4 = igi2_frame.ptEndPos->vY - *(double *)&ptQTask[1].tQTaskChildren.ptHead;
                    igi2_frame.tEndPos_8 = igi2_frame.ptEndPos->vZ - *(double *)&ptQTask[1].tQTaskChildren.ptTail;
                    igi2_frame.vLineLength = Real64x3_Distance(igi2_frame.ptStartPos, igi2_frame.ptEndPos);
                    if ( igi2_frame.isHit )
                    {
                      v22 = igi2_frame.ptIntersection->tPos.vX - *(double *)&ptQTask[1].ptNext;
                      v23 = igi2_frame.ptIntersection->tPos.vY - *(double *)&ptQTask[1].tQTaskChildren.ptHead;
                      v24 = igi2_frame.ptIntersection->tPos.vZ - *(double *)&ptQTask[1].tQTaskChildren.ptTail;
                      igi2_frame.Real32x3_RotateInverse_tTemp = v24 * *(float *)&ptQTask[3].tQTaskRefList.ptTail
                                                   + v23 * *(float *)&ptQTask[3].tQTaskChildren.ptTail
                                                   + v22 * *(float *)&ptQTask[3].ptPrev;
                      igi2_frame.Real32x3_RotateInverse_tTemp_4 = v24 * *(float *)&ptQTask[3].ptParent
                                                     + v23 * *(float *)&ptQTask[3].tQTaskRefList.ptHead
                                                     + v22 * *(float *)&ptQTask[3].tQTaskChildren.ptHead;
                      igi2_frame.Real32x3_RotateInverse_tTemp_8 = v24 * *(float *)&ptQTask[3].eQTaskType
                                                     + v23 * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle
                                                     + v22 * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle;
                      v25 = 1.0 / *(float *)&ptQTask[6].ptPrev;
                      igi2_frame.tHitPos_8b = v25 * igi2_frame.Real32x3_RotateInverse_tTemp_8;
                      igi2_frame.vDotb = v25 * igi2_frame.Real32x3_RotateInverse_tTemp_4 - igi2_frame.tStartPos_4;
                      igi2_frame.vClosest = sqrt(
                                   (igi2_frame.tHitPos_8b - igi2_frame.tStartPos_8) * (igi2_frame.tHitPos_8b - igi2_frame.tStartPos_8)
                                 + (igi2_frame.Real32x3_RotateInverse_tTemp * v25 - igi2_frame.tStartPos)
                                 * (igi2_frame.Real32x3_RotateInverse_tTemp * v25 - igi2_frame.tStartPos)
                                 + igi2_frame.vDotb * igi2_frame.vDotb);
                    }
                    if ( igi2_frame.tStartPos >= (double)igi2_frame.tEndPos )
                      v26 = igi2_frame.tEndPos;
                    else
                      v26 = igi2_frame.tStartPos;
                    igi2_frame.tMin = v26 - 40.959999084472656;
                    if ( igi2_frame.tStartPos_4 >= (double)igi2_frame.tEndPos_4 )
                      v27 = igi2_frame.tEndPos_4;
                    else
                      v27 = igi2_frame.tStartPos_4;
                    igi2_frame.tMin_4 = v27 - 40.959999084472656;
                    if ( igi2_frame.tStartPos_8 >= (double)igi2_frame.tEndPos_8 )
                      v28 = igi2_frame.tEndPos_8;
                    else
                      v28 = igi2_frame.tStartPos_8;
                    igi2_frame.tMin_8 = v28 - 40.959999084472656;
                    if ( igi2_frame.tStartPos <= (double)igi2_frame.tEndPos )
                      v29 = igi2_frame.tEndPos;
                    else
                      v29 = igi2_frame.tStartPos;
                    igi2_frame.tMax = v29 + 40.959999084472656;
                    if ( igi2_frame.tStartPos_4 <= (double)igi2_frame.tEndPos_4 )
                      v30 = igi2_frame.tEndPos_4;
                    else
                      v30 = igi2_frame.tStartPos_4;
                    igi2_frame.tMax_4 = v30 + 40.959999084472656;
                    if ( igi2_frame.tStartPos_8 <= (double)igi2_frame.tEndPos_8 )
                      v31 = igi2_frame.tEndPos_8;
                    else
                      v31 = igi2_frame.tStartPos_8;
                    igi2_frame.tHitPos = igi2_frame.tEndPos;
                    igi2_frame.tMax_8 = v31 + 40.959999084472656;
                    igi2_frame.tHitPos_8 = igi2_frame.tEndPos_8;
                    igi2_frame.tHitPos_4 = igi2_frame.tEndPos_4;
                    igi2_frame.v1DivSquaredDistance = 1.0
                                         / ((igi2_frame.tEndPos_8 - igi2_frame.tStartPos_8) * (igi2_frame.tEndPos_8 - igi2_frame.tStartPos_8)
                                          + (igi2_frame.tEndPos - igi2_frame.tStartPos) * (igi2_frame.tEndPos - igi2_frame.tStartPos)
                                          + (igi2_frame.tEndPos_4 - igi2_frame.tStartPos_4) * (igi2_frame.tEndPos_4 - igi2_frame.tStartPos_4));
                    if ( !igi2_frame.isVerticesCalculated )
                    {
                      SplineMultiMeshVertexList = Mesh3D_GetSplineMultiMeshVertexList(
                                                    (struct SplineObjSegment_s *)ptQTask,
                                                    (int)ptQTask[7].tQTaskChildren.ptHead,
                                                    (int)igi2_frame.ptMaterial,
                                                    0,
                                                    0,
                                                    nullptr);
                      p_vX = &igi2_frame.ptEndPos->vX;
                      igi2_frame.ptVertexList = SplineMultiMeshVertexList;
                      igi2_frame.isVerticesCalculated = 1;
                    }
                    igi2_frame.tDelta = *p_vX - igi2_frame.ptStartPos->vX;
                    igi2_frame.tDelta_4 = p_vX[1] - igi2_frame.ptStartPos->vY;
                    igi2_frame.tDelta_8 = p_vX[2] - igi2_frame.ptStartPos->vZ;
                    if ( igi2_frame.ptCollMesh->nNumSpheres )
                    {
LABEL_49:
                      v33 = igi2_frame.nLevel;
                      while ( 1 )
                      {
                        if ( igi2_frame.isFirstIteration )
                        {
LABEL_59:
                          iChild = v20->iChild;
                          igi2_frame.isFirstIteration = 0;
                          if ( iChild )
                          {
                            do
                            {
                              v20 = &igi2_frame.ptFirstSphere[iChild];
                              igi2_frame.vRadius = v20->tSphere.vRadius;
                              ++v33;
                              v38 = v20->tSphere.tPos.vX - igi2_frame.tStartPos;
                              igi2_frame.aptSphereStack[v33] = v20;
                              igi2_frame.bColorc = v20->tSphere.tPos.vZ - igi2_frame.tStartPos_8;
                              igi2_frame.vDistancec = v20->tSphere.tPos.vY - igi2_frame.tStartPos_4;
                              v39 = igi2_frame.bColorc * igi2_frame.tDelta_8 + igi2_frame.vDistancec * igi2_frame.tDelta_4 + v38 * igi2_frame.tDelta;
                              if ( igi2_frame.vRadius * igi2_frame.vRadius < v38 * v38
                                                     + igi2_frame.vDistancec * igi2_frame.vDistancec
                                                     + igi2_frame.bColorc * igi2_frame.bColorc
                                                     - v39 * v39 * igi2_frame.v1DivSquaredDistance )
                                break;
                              if ( v20->tSphere.vRadius + v20->tSphere.tPos.vX < igi2_frame.tMin )
                                break;
                              if ( v20->tSphere.vRadius + v20->tSphere.tPos.vY < igi2_frame.tMin_4 )
                                break;
                              if ( v20->tSphere.vRadius + v20->tSphere.tPos.vZ < igi2_frame.tMin_8 )
                                break;
                              if ( v20->tSphere.tPos.vX - v20->tSphere.vRadius > igi2_frame.tMax )
                                break;
                              if ( v20->tSphere.tPos.vY - v20->tSphere.vRadius > igi2_frame.tMax_4 )
                                break;
                              if ( v20->tSphere.tPos.vZ - v20->tSphere.vRadius > igi2_frame.tMax_8 )
                                break;
                              iChild = v20->iChild;
                            }
                            while ( iChild );
                            igi2_frame.nLevel = v33;
                          }
                          nFace = v20->nFace;
                          if ( nFace )
                          {
                            v41 = v20->iFace;
                            igi2_frame.iFace = v41;
                            aiVertex = igi2_frame.ptCollMesh->ptFace[v41].aiVertex;
                            igi2_frame.ptVertex2 = (struct real32x3_t *)(v41 + nFace);
                            if ( v41 < (int)igi2_frame.ptVertex2 )
                            {
                              while ( 1 )
                              {
                                v43 = &igi2_frame.ptVertexList[*aiVertex].vX;
                                igi2_frame.vT = &igi2_frame.ptVertexList[aiVertex[1]].vX;
                                v44 = &igi2_frame.ptVertexList[aiVertex[2]].vX;
                                if ( igi2_frame.tMin > (double)*v43 && igi2_frame.tMin > (double)*igi2_frame.vT && igi2_frame.tMin > (double)*v44
                                  || igi2_frame.tMin_4 > (double)v43[1] && igi2_frame.tMin_4 > (double)igi2_frame.vT[1] && igi2_frame.tMin_4 > (double)v44[1]
                                  || igi2_frame.tMin_8 > (double)v43[2] && igi2_frame.tMin_8 > (double)igi2_frame.vT[2] && igi2_frame.tMin_8 > (double)v44[2]
                                  || igi2_frame.tMax < (double)*v43 && igi2_frame.tMax < (double)*igi2_frame.vT && igi2_frame.tMax < (double)*v44
                                  || igi2_frame.tMax_4 < (double)v43[1] && igi2_frame.tMax_4 < (double)igi2_frame.vT[1] && igi2_frame.tMax_4 < (double)v44[1]
                                  || igi2_frame.tMax_8 < (double)v43[2] && igi2_frame.tMax_8 < (double)igi2_frame.vT[2] && igi2_frame.tMax_8 < (double)v44[2] )
                                {
                                  goto LABEL_128;
                                }
                                igi2_frame.v215 = *v44 - *v43;
                                igi2_frame.v216 = v44[1] - v43[1];
                                igi2_frame.v217 = v44[2] - v43[2];
                                igi2_frame.tEdge1 = *igi2_frame.vT - *v43;
                                igi2_frame.tEdge1_4 = igi2_frame.vT[1] - v43[1];
                                v45 = igi2_frame.vT[2] - v43[2];
                                igi2_frame.tEdge1_8 = v45;
                                igi2_frame.ptMateriala = v45 * igi2_frame.v216 - igi2_frame.tEdge1_4 * igi2_frame.v217;
                                v46 = igi2_frame.tEdge1_8 * igi2_frame.v215 - igi2_frame.tEdge1 * igi2_frame.v217;
                                igi2_frame.v231 = v46;
                                igi2_frame.v314 = -v46;
                                igi2_frame.v177 = igi2_frame.tEdge1_4 * igi2_frame.v215 - igi2_frame.tEdge1 * igi2_frame.v216;
                                igi2_frame.tNormal = igi2_frame.ptMateriala;
                                igi2_frame.tNormal_4 = igi2_frame.v314;
                                igi2_frame.tNormal_8 = igi2_frame.v177;
                                if ( BYTE1(ptQTask[38].tQTaskRefList.ptHead) )
                                {
                                  igi2_frame.tNormal = -igi2_frame.ptMateriala;
                                  igi2_frame.tNormal_4 = -igi2_frame.v314;
                                  igi2_frame.tNormal_8 = -igi2_frame.v177;
                                }
                                igi2_frame.vDot = igi2_frame.tNormal_8 * igi2_frame.tDelta_8 + igi2_frame.tNormal_4 * igi2_frame.tDelta_4 + igi2_frame.tNormal * igi2_frame.tDelta;
                                if ( igi2_frame.vDot == 0.0 )
                                  goto LABEL_128;
                                v47 = ((v43[2] - igi2_frame.tStartPos_8) * igi2_frame.tNormal_8
                                     + (v43[1] - igi2_frame.tStartPos_4) * igi2_frame.tNormal_4
                                     + (*v43 - igi2_frame.tStartPos) * igi2_frame.tNormal)
                                    / igi2_frame.vDot;
                                igi2_frame.vTa = v47;
                                if ( v47 < 0.0 || igi2_frame.vTa > 1.0 )
                                  goto LABEL_128;
                                igi2_frame.v260 = igi2_frame.vTa * igi2_frame.tDelta + igi2_frame.tStartPos;
                                igi2_frame.v261 = igi2_frame.vTa * igi2_frame.tDelta_4 + igi2_frame.tStartPos_4;
                                igi2_frame.v262 = igi2_frame.vTa * igi2_frame.tDelta_8 + igi2_frame.tStartPos_8;
                                if ( igi2_frame.tNormal >= 0.0 )
                                  igi2_frame.tAbsNormal = igi2_frame.tNormal;
                                else
                                  igi2_frame.tAbsNormal = -igi2_frame.tNormal;
                                v48 = igi2_frame.tNormal_4;
                                if ( igi2_frame.tNormal_4 < 0.0 )
                                  v48 = -v48;
                                v49 = igi2_frame.tNormal_8;
                                if ( igi2_frame.tNormal_8 < 0.0 )
                                  v49 = -v49;
                                if ( igi2_frame.tAbsNormal <= v48 || igi2_frame.tAbsNormal <= v49 )
                                {
                                  if ( v48 <= v49 )
                                  {
                                    v55 = igi2_frame.v177;
                                    if ( igi2_frame.v177 == 0.0 )
                                      goto LABEL_128;
                                    igi2_frame.v233 = igi2_frame.v261 - v43[1];
                                    igi2_frame.v179 = igi2_frame.v260 - *v43;
                                    igi2_frame.bColora = (igi2_frame.v233 * igi2_frame.v215 - igi2_frame.v179 * igi2_frame.v216) / v55;
                                    if ( igi2_frame.bColora < 0.0 || igi2_frame.bColora > 1.0 )
                                      goto LABEL_128;
                                    v56 = igi2_frame.v215;
                                    if ( igi2_frame.v215 < 0.0 )
                                      v56 = -v56;
                                    v57 = igi2_frame.v216;
                                    if ( igi2_frame.v216 < 0.0 )
                                      v57 = -v57;
                                    if ( v56 <= v57 )
                                    {
                                      if ( igi2_frame.v216 == 0.0 )
                                        goto LABEL_128;
                                      v52 = (igi2_frame.v233 - igi2_frame.tEdge1_4 * igi2_frame.bColora) / igi2_frame.v216;
                                    }
                                    else
                                    {
                                      v52 = (igi2_frame.v179 - igi2_frame.tEdge1 * igi2_frame.bColora) / igi2_frame.v215;
                                    }
                                    if ( v52 < 0.0 || igi2_frame.bColora + v52 > 1.0 )
                                      goto LABEL_128;
                                    goto LABEL_143;
                                  }
                                  if ( igi2_frame.v231 == 0.0 )
                                    goto LABEL_128;
                                  igi2_frame.v202 = igi2_frame.v262 - v43[2];
                                  igi2_frame.v178 = igi2_frame.v260 - *v43;
                                  igi2_frame.bColora = (igi2_frame.v202 * igi2_frame.v215 - igi2_frame.v178 * igi2_frame.v217) / igi2_frame.v231;
                                  if ( igi2_frame.bColora < 0.0 || igi2_frame.bColora > 1.0 )
                                    goto LABEL_128;
                                  v53 = igi2_frame.v215;
                                  if ( igi2_frame.v215 < 0.0 )
                                    v53 = -v53;
                                  v54 = igi2_frame.v217;
                                  if ( igi2_frame.v217 < 0.0 )
                                    v54 = -v54;
                                  if ( v53 <= v54 )
                                  {
LABEL_124:
                                    if ( igi2_frame.v217 == 0.0 )
                                      goto LABEL_128;
                                    v52 = (igi2_frame.v202 - igi2_frame.tEdge1_8 * igi2_frame.bColora) / igi2_frame.v217;
                                    goto LABEL_126;
                                  }
                                  v52 = (igi2_frame.v178 - igi2_frame.tEdge1 * igi2_frame.bColora) / igi2_frame.v215;
                                }
                                else
                                {
                                  if ( igi2_frame.ptMateriala == 0.0 )
                                    goto LABEL_128;
                                  igi2_frame.v202 = igi2_frame.v262 - v43[2];
                                  igi2_frame.v232 = igi2_frame.v261 - v43[1];
                                  igi2_frame.bColora = (igi2_frame.v202 * igi2_frame.v216 - igi2_frame.v232 * igi2_frame.v217) / igi2_frame.ptMateriala;
                                  if ( igi2_frame.bColora < 0.0 || igi2_frame.bColora > 1.0 )
                                    goto LABEL_128;
                                  v50 = igi2_frame.v216;
                                  if ( igi2_frame.v216 < 0.0 )
                                    v50 = -v50;
                                  v51 = igi2_frame.v217;
                                  if ( igi2_frame.v217 < 0.0 )
                                    v51 = -v51;
                                  if ( v50 <= v51 )
                                    goto LABEL_124;
                                  v52 = (igi2_frame.v232 - igi2_frame.tEdge1_4 * igi2_frame.bColora) / igi2_frame.v216;
                                }
LABEL_126:
                                if ( v52 < 0.0 || igi2_frame.bColora + v52 > 1.0 )
                                  goto LABEL_128;
LABEL_143:
                                igi2_frame.vDistance = igi2_frame.vTa * igi2_frame.vLineLength;
                                if ( !igi2_frame.isHit || igi2_frame.vDistance + 40.96 < igi2_frame.vClosest )
                                {
LABEL_151:
                                  igi2_frame.tHitUV = v52;
                                  igi2_frame.tHitUV_4 = igi2_frame.bColora;
                                  igi2_frame.isHitFrontFace = igi2_frame.vDot < 0.0;
                                  igi2_frame.tHitPos_4 = igi2_frame.vTa * igi2_frame.tDelta_4 + igi2_frame.tStartPos_4;
                                  igi2_frame.vClosest = igi2_frame.vTa * igi2_frame.vLineLength;
                                  igi2_frame.iHitLightmap = aiVertex[4];
                                  igi2_frame.tHitPos = igi2_frame.vTa * igi2_frame.tDelta + igi2_frame.tStartPos;
                                  igi2_frame.isHitCurrentObject = 1;
                                  igi2_frame.isHit = 1;
                                  igi2_frame.ptHitFace = (struct MultiMesh_Face_t *)aiVertex;
                                  igi2_frame.tHitPos_8 = igi2_frame.vTa * igi2_frame.tDelta_8 + igi2_frame.tStartPos_8;
                                  if ( igi2_frame.tStartPos >= (double)igi2_frame.v260 )
                                    v58 = igi2_frame.v260;
                                  else
                                    v58 = igi2_frame.tStartPos;
                                  igi2_frame.tMin = v58 - 40.959999084472656;
                                  if ( igi2_frame.tStartPos_4 >= (double)igi2_frame.v261 )
                                    v59 = igi2_frame.v261;
                                  else
                                    v59 = igi2_frame.tStartPos_4;
                                  igi2_frame.tMin_4 = v59 - 40.959999084472656;
                                  if ( igi2_frame.tStartPos_8 >= (double)igi2_frame.v262 )
                                    v60 = igi2_frame.v262;
                                  else
                                    v60 = igi2_frame.tStartPos_8;
                                  igi2_frame.tMin_8 = v60 - 40.959999084472656;
                                  if ( igi2_frame.tStartPos <= (double)igi2_frame.v260 )
                                    v61 = igi2_frame.v260;
                                  else
                                    v61 = igi2_frame.tStartPos;
                                  igi2_frame.tMax = v61 + 40.959999084472656;
                                  if ( igi2_frame.tStartPos_4 <= (double)igi2_frame.v261 )
                                    v62 = igi2_frame.v261;
                                  else
                                    v62 = igi2_frame.tStartPos_4;
                                  igi2_frame.tMax_4 = v62 + 40.959999084472656;
                                  if ( igi2_frame.tStartPos_8 <= (double)igi2_frame.v262 )
                                    v63 = igi2_frame.v262 + 40.959999084472656;
                                  else
                                    v63 = igi2_frame.tStartPos_8 + 40.959999084472656;
                                  igi2_frame.tMax_8 = v63;
                                  goto LABEL_128;
                                }
                                if ( igi2_frame.vDistance >= igi2_frame.vClosest )
                                {
                                  if ( igi2_frame.vDistance - 40.96 >= igi2_frame.vClosest || igi2_frame.vDot >= 0.0 )
                                    goto LABEL_128;
                                }
                                else if ( igi2_frame.vDot < 0.0 )
                                {
                                  goto LABEL_151;
                                }
                                if ( !igi2_frame.isHitFrontFace )
                                  goto LABEL_151;
LABEL_128:
                                aiVertex += 6;
                                if ( ++igi2_frame.iFace >= (int)igi2_frame.ptVertex2 )
                                  goto LABEL_49;
                              }
                            }
                            goto LABEL_49;
                          }
                        }
                        else
                        {
                          iNext = v20->iNext;
                          if ( iNext )
                          {
                            v20 = &igi2_frame.ptFirstSphere[iNext];
                            igi2_frame.v274 = v20->tSphere.vRadius;
                            v35 = v20->tSphere.tPos.vX;
                            igi2_frame.aptSphereStack[v33] = v20;
                            igi2_frame.bColorb = v20->tSphere.tPos.vZ - igi2_frame.tStartPos_8;
                            igi2_frame.vDistanceb = v20->tSphere.tPos.vY - igi2_frame.tStartPos_4;
                            igi2_frame.vDotc = v35 - igi2_frame.tStartPos;
                            v36 = igi2_frame.bColorb * igi2_frame.tDelta_8 + igi2_frame.vDistanceb * igi2_frame.tDelta_4 + igi2_frame.vDotc * igi2_frame.tDelta;
                            if ( igi2_frame.v274 * igi2_frame.v274 >= igi2_frame.vDotc * igi2_frame.vDotc
                                              + igi2_frame.vDistanceb * igi2_frame.vDistanceb
                                              + igi2_frame.bColorb * igi2_frame.bColorb
                                              - v36 * v36 * igi2_frame.v1DivSquaredDistance
                              && v20->tSphere.vRadius + v20->tSphere.tPos.vX >= igi2_frame.tMin
                              && v20->tSphere.vRadius + v20->tSphere.tPos.vY >= igi2_frame.tMin_4
                              && v20->tSphere.vRadius + v20->tSphere.tPos.vZ >= igi2_frame.tMin_8
                              && v20->tSphere.tPos.vX - v20->tSphere.vRadius <= igi2_frame.tMax
                              && v20->tSphere.tPos.vY - v20->tSphere.vRadius <= igi2_frame.tMax_4
                              && v20->tSphere.tPos.vZ - v20->tSphere.vRadius <= igi2_frame.tMax_8 )
                            {
                              goto LABEL_59;
                            }
                          }
                          else
                          {
                            igi2_frame.nLevel = --v33;
                            if ( v33 < 0 )
                            {
                              if ( igi2_frame.isHitCurrentObject
                                && (!igi2_frame.ptIntersection->isHit || igi2_frame.vClosest < igi2_frame.ptIntersection->vDistance) )
                              {
                                igi2_frame.vLineLengtha = &igi2_frame.ptVertexList[igi2_frame.ptHitFace->aiVertex[1]].vX;
                                v64 = &igi2_frame.ptVertexList[igi2_frame.ptHitFace->aiVertex[0]].vX;
                                igi2_frame.ptVertex2a = &igi2_frame.ptVertexList[igi2_frame.ptHitFace->aiVertex[2]];
                                iMaterial = igi2_frame.ptCollMesh->ptMaterial[igi2_frame.ptHitFace->iMaterial].iMaterial;
                                if ( iMaterial == 0xFFFF )
                                  igi2_frame.ptMaterialb = ptQTask[2].ptParent[2].tQTaskChildren.ptMiddle;
                                else
                                  igi2_frame.ptMaterialb = *(&ptQTask[2].ptParent[2].tQTaskChildren.ptHead + iMaterial);
                                v66 = igi2_frame.ptVertex2a->vX - *v64;
                                v67 = igi2_frame.ptVertex2a->vY - v64[1];
                                v68 = igi2_frame.ptVertex2a->vZ - v64[2];
                                igi2_frame.v333 = *igi2_frame.vLineLengtha - *v64;
                                igi2_frame.v334 = igi2_frame.vLineLengtha[1] - v64[1];
                                v69 = igi2_frame.vLineLengtha[2] - v64[2];
                                v70 = &igi2_frame.ptIntersection->tNormal.vX;
                                igi2_frame.v327 = v69 * v67 - igi2_frame.v334 * v68;
                                igi2_frame.ptIntersection->tNormal.vX = igi2_frame.v327;
                                igi2_frame.v328 = -(v69 * v66 - igi2_frame.v333 * v68);
                                igi2_frame.ptIntersection->tNormal.vY = igi2_frame.v328;
                                igi2_frame.v329 = igi2_frame.v334 * v66 - igi2_frame.v333 * v67;
                                igi2_frame.ptIntersection->tNormal.vZ = igi2_frame.v329;
                                if ( igi2_frame.ptIntersection->tNormal.vX != 0.0
                                  || igi2_frame.ptIntersection->tNormal.vY != 0.0
                                  || igi2_frame.ptIntersection->tNormal.vZ != 0.0 )
                                {
                                  v71 = 1.0
                                      / sqrt(
                                          *v70 * *v70
                                        + igi2_frame.ptIntersection->tNormal.vY * igi2_frame.ptIntersection->tNormal.vY
                                        + igi2_frame.ptIntersection->tNormal.vZ * igi2_frame.ptIntersection->tNormal.vZ);
                                  *v70 = *v70 * v71;
                                  igi2_frame.ptIntersection->tNormal.vY = igi2_frame.ptIntersection->tNormal.vY * v71;
                                  igi2_frame.ptIntersection->tNormal.vZ = igi2_frame.ptIntersection->tNormal.vZ * v71;
                                }
                                if ( BYTE1(ptQTask[38].tQTaskRefList.ptHead) )
                                {
                                  *v70 = -*v70;
                                  igi2_frame.ptIntersection->tNormal.vY = -igi2_frame.ptIntersection->tNormal.vY;
                                  igi2_frame.ptIntersection->tNormal.vZ = -igi2_frame.ptIntersection->tNormal.vZ;
                                }
                                igi2_frame.ptIntersection->tLocalNormal.vX = *v70;
                                vZ = igi2_frame.ptIntersection->tNormal.vZ;
                                igi2_frame.ptIntersection->tLocalNormal.vY = igi2_frame.ptIntersection->tNormal.vY;
                                igi2_frame.ptIntersection->tLocalNormal.vZ = vZ;
                                igi2_frame.ptIntersection->tPos.vX = igi2_frame.tHitPos + *(double *)&ptQTask[1].ptNext;
                                igi2_frame.ptIntersection->tPos.vY = igi2_frame.tHitPos_4 + *(double *)&ptQTask[1].tQTaskChildren.ptHead;
                                v73 = igi2_frame.tHitPos_8 + *(double *)&ptQTask[1].tQTaskChildren.ptTail;
                                igi2_frame.ptIntersection->tLocalPos.vX = igi2_frame.tHitPos;
                                igi2_frame.ptIntersection->tLocalPos.vY = igi2_frame.tHitPos_4;
                                igi2_frame.ptIntersection->tPos.vZ = v73;
                                igi2_frame.ptIntersection->tLocalPos.vZ = igi2_frame.tHitPos_8;
                                igi2_frame.ptIntersection->ptHitObj = (struct QObj_s *)ptQTask;
                                igi2_frame.ptIntersection->ptEnterMaterial = igi2_frame.isHitFrontFace != 0
                                                                ? (struct QMaterial_t *)igi2_frame.ptMaterialb
                                                                : nullptr;
                                igi2_frame.ptIntersection->isDoubleFace = 1;
                                igi2_frame.ptIntersection->isHit = 1;
                                LODWORD(igi2_frame.ptIntersection->vDistance) = LODWORD(igi2_frame.vClosest);
                                igi2_frame.ptIntersection->ptLeaveMaterial = igi2_frame.isHitFrontFace != 0
                                                                ? nullptr
                                                                : (struct QMaterial_t *)igi2_frame.ptMaterialb;
                                HIDWORD(igi2_frame.ptIntersection->vDistance) = HIDWORD(igi2_frame.vClosest);
                                igi2_frame.ptIntersection->iFace = igi2_frame.ptHitFace - igi2_frame.ptCollMesh->ptFace;
                                if ( igi2_frame.ptMesh->eRenderMeshType == MESH3D_RENDERMESHTYPE_DIRECT3D_BUILDING
                                  && igi2_frame.iHitLightmap != 0xFFFF
                                  && (v74 = ptQTask[7].tQTaskRefList.ptHead) != nullptr
                                  && (igi2_frame.ptVertex2b = (struct real32x3_t *)v74->ptNext) != nullptr )
                                {
                                  v75 = &igi2_frame.ptVertexPos[igi2_frame.ptHitFace->aiVertex[0]].u.tLightmapUV.vX;
                                  v76 = igi2_frame.ptVertexPos[igi2_frame.ptHitFace->aiVertex[2]].u.tLightmapUV.vY
                                      - igi2_frame.ptVertexPos[igi2_frame.ptHitFace->aiVertex[0]].u.tLightmapUV.vY;
                                  igi2_frame.tUVEdge1 = igi2_frame.ptVertexPos[igi2_frame.ptHitFace->aiVertex[1]].u.tLightmapUV.vX - *v75;
                                  igi2_frame.tUVEdge1_4 = igi2_frame.ptVertexPos[igi2_frame.ptHitFace->aiVertex[1]].u.tLightmapUV.vY
                                             - igi2_frame.ptVertexPos[igi2_frame.ptHitFace->aiVertex[0]].u.tLightmapUV.vY;
                                  igi2_frame.v344 = (igi2_frame.ptVertexPos[igi2_frame.ptHitFace->aiVertex[2]].u.tLightmapUV.vX - *v75) * igi2_frame.tHitUV;
                                  igi2_frame.tUVEdge1_4a = igi2_frame.tUVEdge1_4 * igi2_frame.tHitUV_4;
                                  igi2_frame.v312 = igi2_frame.tUVEdge1_4a + v76 * igi2_frame.tHitUV;
                                  igi2_frame.v311 = igi2_frame.tUVEdge1 * igi2_frame.tHitUV_4 + igi2_frame.v344 + *v75;
                                  igi2_frame.v313 = igi2_frame.v312 + v75[1];
                                  igi2_frame.ptVertex2d = (struct real32x3_t *)Lightmap_ReadTexel(
                                                                      (struct Mesh3D_Lightmap_t *)&igi2_frame.ptVertex2b[5]
                                                                    + igi2_frame.iHitLightmap,
                                                                      igi2_frame.v311,
                                                                      igi2_frame.v313);
                                  igi2_frame.ptIntersection->vLight = (double)((unsigned __int8)igi2_frame.ptVertex2d
                                                                  + BYTE1(igi2_frame.ptVertex2d)
                                                                  + (unsigned int)BYTE2(igi2_frame.ptVertex2d))
                                                         * 0.0026143791619688272;
                                }
                                else
                                {
                                  igi2_frame.v297 = Mesh3D_atAmbientColor[1].vX;
                                  igi2_frame.vY = Mesh3D_atAmbientColor[1].vY;
                                  if ( SkyDome_ptDirlight
                                    && (v77 = SkyDome_ptDirlight->tDir.vZ * igi2_frame.ptIntersection->tNormal.vZ
                                            + SkyDome_ptDirlight->tDir.vY * igi2_frame.ptIntersection->tNormal.vY
                                            + igi2_frame.ptIntersection->tNormal.vX * SkyDome_ptDirlight->tDir.vX,
                                        v77 > 0.0) )
                                  {
                                    igi2_frame.v297 = v77 * SkyDome_ptDirlight->tFrontColor.vX + Mesh3D_atAmbientColor[1].vX;
                                    igi2_frame.vY = v77 * SkyDome_ptDirlight->tFrontColor.vY + Mesh3D_atAmbientColor[1].vY;
                                    v78 = v77 * SkyDome_ptDirlight->tFrontColor.vZ + Mesh3D_atAmbientColor[1].vZ;
                                  }
                                  else
                                  {
                                    v78 = Mesh3D_atAmbientColor[1].vZ;
                                  }
                                  igi2_frame.ptIntersection->vLight = (v78 + igi2_frame.vY + igi2_frame.v297) * 0.3333333432674408;
                                }
                              }
                              goto LABEL_355;
                            }
                            v20 = igi2_frame.aptSphereStack[v33];
                          }
                        }
                      }
                    }
                    goto LABEL_355;
                  }
                  v79 = igi2_frame.ptStartPos->vY - *(double *)&ptQTask[1].tQTaskChildren.ptHead;
                  ptSphere = igi2_frame.ptCollMesh->ptSphere;
                  igi2_frame.ptFirstSpherea = ptSphere;
                  v81 = igi2_frame.ptStartPos->vZ - *(double *)&ptQTask[1].tQTaskChildren.ptTail;
                  igi2_frame.v346[0] = ptSphere;
                  igi2_frame.Real32x3_Rotate_tTemp = v79 * *(float *)&ptQTask[34].eQTaskType
                                        + v19 * *(float *)&ptQTask[34].ptParent
                                        + v81 * *(float *)&ptQTask[35].ptNext;
                  igi2_frame.Real32x3_Rotate_tTemp_4 = v19 * *(float *)&ptQTask[35].ptPrev
                                          + v81 * *(float *)&ptQTask[35].tQTaskChildren.ptMiddle
                                          + v79 * *(float *)&ptQTask[35].tQTaskChildren.ptHead;
                  igi2_frame.Real32x3_Rotate_tTemp_8 = v19 * *(float *)&ptQTask[35].tQTaskChildren.ptTail
                                          + v81 * *(float *)&ptQTask[35].tQTaskRefList.ptMiddle
                                          + v79 * *(float *)&ptQTask[35].tQTaskRefList.ptHead;
                  v82 = (*(float *)&ptQTask[8].tQTaskChildren.ptTail + *(float *)&ptQTask[8].tQTaskChildren.ptMiddle)
                      * 0.5;
                  igi2_frame.ptMaterialc = v82;
                  igi2_frame.tStartPosa = v82 + igi2_frame.Real32x3_Rotate_tTemp;
                  v83 = igi2_frame.ptEndPos->vX - *(double *)&ptQTask[1].ptNext;
                  v84 = igi2_frame.ptEndPos->vY - *(double *)&ptQTask[1].tQTaskChildren.ptHead;
                  v85 = igi2_frame.ptEndPos->vZ - *(double *)&ptQTask[1].tQTaskChildren.ptTail;
                  igi2_frame.v324 = v83 * *(float *)&ptQTask[34].ptParent
                       + v85 * *(float *)&ptQTask[35].ptNext
                       + v84 * *(float *)&ptQTask[34].eQTaskType;
                  igi2_frame.v325 = v83 * *(float *)&ptQTask[35].ptPrev
                       + v85 * *(float *)&ptQTask[35].tQTaskChildren.ptMiddle
                       + v84 * *(float *)&ptQTask[35].tQTaskChildren.ptHead;
                  igi2_frame.v326 = v85 * *(float *)&ptQTask[35].tQTaskRefList.ptMiddle
                       + v84 * *(float *)&ptQTask[35].tQTaskRefList.ptHead
                       + v83 * *(float *)&ptQTask[35].tQTaskChildren.ptTail;
                  igi2_frame.tEndPosa = igi2_frame.ptMaterialc + igi2_frame.v324;
                  igi2_frame.vLineLengthb = Real64x3_Distance(igi2_frame.ptStartPos, igi2_frame.ptEndPos);
                  igi2_frame.tHitPosa = igi2_frame.tEndPosa;
                  igi2_frame.tHitPos_4a = igi2_frame.v325;
                  if ( igi2_frame.isHit )
                  {
                    v86 = igi2_frame.ptIntersection->tPos.vX - *(double *)&ptQTask[1].ptNext;
                    v87 = igi2_frame.ptIntersection->tPos.vY - *(double *)&ptQTask[1].tQTaskChildren.ptHead;
                    v88 = igi2_frame.ptIntersection->tPos.vZ - *(double *)&ptQTask[1].tQTaskChildren.ptTail;
                    igi2_frame.v321 = v88 * *(float *)&ptQTask[3].tQTaskRefList.ptTail
                         + v87 * *(float *)&ptQTask[3].tQTaskChildren.ptTail
                         + v86 * *(float *)&ptQTask[3].ptPrev;
                    igi2_frame.v322 = v88 * *(float *)&ptQTask[3].ptParent
                         + v87 * *(float *)&ptQTask[3].tQTaskRefList.ptHead
                         + v86 * *(float *)&ptQTask[3].tQTaskChildren.ptHead;
                    igi2_frame.v323 = v88 * *(float *)&ptQTask[3].eQTaskType
                         + v87 * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle
                         + v86 * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle;
                    v89 = 1.0 / *(float *)&ptQTask[6].ptPrev;
                    igi2_frame.tHitPosa = igi2_frame.v321 * v89;
                    igi2_frame.tHitPos_4a = igi2_frame.v322 * v89;
                    v90 = v89 * igi2_frame.v323;
                    igi2_frame.vClosest = sqrt(
                                 (v90 - igi2_frame.Real32x3_Rotate_tTemp_8) * (v90 - igi2_frame.Real32x3_Rotate_tTemp_8)
                               + (igi2_frame.tHitPosa - igi2_frame.tStartPosa) * (igi2_frame.tHitPosa - igi2_frame.tStartPosa)
                               + (igi2_frame.tHitPos_4a - igi2_frame.Real32x3_Rotate_tTemp_4) * (igi2_frame.tHitPos_4a - igi2_frame.Real32x3_Rotate_tTemp_4));
                  }
                  else
                  {
                    v90 = igi2_frame.v326;
                  }
                  if ( igi2_frame.tStartPosa >= (double)igi2_frame.tHitPosa )
                    v91 = igi2_frame.tHitPosa;
                  else
                    v91 = igi2_frame.tStartPosa;
                  igi2_frame.tMina = v91 - 40.959999084472656;
                  if ( igi2_frame.Real32x3_Rotate_tTemp_4 >= (double)igi2_frame.tHitPos_4a )
                    v92 = igi2_frame.tHitPos_4a;
                  else
                    v92 = igi2_frame.Real32x3_Rotate_tTemp_4;
                  igi2_frame.tMin_4a = v92 - 40.959999084472656;
                  if ( igi2_frame.Real32x3_Rotate_tTemp_8 >= v90 )
                    v93 = v90;
                  else
                    v93 = igi2_frame.Real32x3_Rotate_tTemp_8;
                  igi2_frame.tMin_8a = v93 - 40.959999084472656;
                  if ( igi2_frame.tStartPosa <= (double)igi2_frame.tHitPosa )
                    v94 = igi2_frame.tHitPosa;
                  else
                    v94 = igi2_frame.tStartPosa;
                  igi2_frame.tMaxa = v94 + 40.959999084472656;
                  if ( igi2_frame.Real32x3_Rotate_tTemp_4 <= (double)igi2_frame.tHitPos_4a )
                    v95 = igi2_frame.tHitPos_4a;
                  else
                    v95 = igi2_frame.Real32x3_Rotate_tTemp_4;
                  igi2_frame.tMax_4a = v95 + 40.959999084472656;
                  if ( igi2_frame.Real32x3_Rotate_tTemp_8 > v90 )
                    v90 = igi2_frame.Real32x3_Rotate_tTemp_8;
                  igi2_frame.tHitPosb = igi2_frame.ptMaterialc + igi2_frame.v324;
                  igi2_frame.tMax_8a = v90 + 40.959999084472656;
                  igi2_frame.tHitPos_4b = igi2_frame.v325;
                  igi2_frame.tHitPos_8a = igi2_frame.v326;
                  igi2_frame.v1DivSquaredDistancea = igi2_frame.v325 - igi2_frame.Real32x3_Rotate_tTemp_4;
                  v96 = igi2_frame.tEndPosa - igi2_frame.tStartPosa;
                  v97 = igi2_frame.v326 - igi2_frame.Real32x3_Rotate_tTemp_8;
                  igi2_frame.ptVertex2e = v97;
                  igi2_frame.tDelta_8a = igi2_frame.ptVertex2e;
                  igi2_frame.v337 = 1.0 / (v97 * v97 + v96 * v96 + igi2_frame.v1DivSquaredDistancea * igi2_frame.v1DivSquaredDistancea);
                  igi2_frame.tDeltaa = v96;
                  igi2_frame.tDelta_4a = igi2_frame.v1DivSquaredDistancea;
                  if ( igi2_frame.ptCollMesh->nNumSpheres )
                    break;
LABEL_355:
                  ++igi2_frame.ptStartPos;
                  v157 = ++igi2_frame.iCheck < (int)(*((_DWORD *)pxContext + 2));
                  ++igi2_frame.ptEndPos;
                  ++igi2_frame.ptIntersection;
                  if ( !v157 )
                    return;
                }
LABEL_213:
                v98 = igi2_frame.nLevel;
                while ( 1 )
                {
                  if ( igi2_frame.isFirstIteration )
                  {
LABEL_223:
                    v102 = ptSphere->iChild;
                    igi2_frame.isFirstIteration = 0;
                    if ( v102 )
                    {
                      do
                      {
                        ptSphere = &igi2_frame.ptFirstSpherea[v102];
                        igi2_frame.v271 = ptSphere->tSphere.vRadius;
                        ++v98;
                        v103 = ptSphere->tSphere.tPos.vX - igi2_frame.tStartPosa;
                        igi2_frame.v346[v98] = ptSphere;
                        igi2_frame.vDistancee = ptSphere->tSphere.tPos.vZ - igi2_frame.Real32x3_Rotate_tTemp_8;
                        igi2_frame.vDote = ptSphere->tSphere.tPos.vY - igi2_frame.Real32x3_Rotate_tTemp_4;
                        v104 = igi2_frame.vDistancee * igi2_frame.tDelta_8a + igi2_frame.vDote * igi2_frame.tDelta_4a + v103 * igi2_frame.tDeltaa;
                        if ( igi2_frame.v271 * igi2_frame.v271 < v103 * v103 + igi2_frame.vDote * igi2_frame.vDote + igi2_frame.vDistancee * igi2_frame.vDistancee - v104 * v104 * igi2_frame.v337 )
                          break;
                        if ( ptSphere->tSphere.tPos.vX + ptSphere->tSphere.vRadius < igi2_frame.tMina )
                          break;
                        if ( ptSphere->tSphere.vRadius + ptSphere->tSphere.tPos.vY < igi2_frame.tMin_4a )
                          break;
                        if ( ptSphere->tSphere.vRadius + ptSphere->tSphere.tPos.vZ < igi2_frame.tMin_8a )
                          break;
                        if ( ptSphere->tSphere.tPos.vX - ptSphere->tSphere.vRadius > igi2_frame.tMaxa )
                          break;
                        if ( ptSphere->tSphere.tPos.vY - ptSphere->tSphere.vRadius > igi2_frame.tMax_4a )
                          break;
                        if ( ptSphere->tSphere.tPos.vZ - ptSphere->tSphere.vRadius > igi2_frame.tMax_8a )
                          break;
                        v102 = ptSphere->iChild;
                      }
                      while ( v102 );
                      igi2_frame.nLevel = v98;
                    }
                    v105 = ptSphere->nFace;
                    if ( v105 )
                    {
                      v106 = ptSphere->iFace;
                      igi2_frame.iFacea = v106;
                      v107 = igi2_frame.ptCollMesh->ptFace[v106].aiVertex;
                      igi2_frame.ptVertex2c = (struct real32x3_t *)(v106 + v105);
                      if ( v106 < (int)igi2_frame.ptVertex2c )
                      {
                        while ( 1 )
                        {
                          v108 = &igi2_frame.ptVertexPos[*v107].tPos.vX;
                          igi2_frame.vTb = &igi2_frame.ptVertexPos[v107[1]].tPos.vX;
                          v109 = &igi2_frame.ptVertexPos[v107[2]].tPos.vX;
                          if ( igi2_frame.tMina > (double)*v108 && igi2_frame.tMina > (double)*igi2_frame.vTb && igi2_frame.tMina > (double)*v109 )
                            goto LABEL_290;
                          if ( igi2_frame.tMin_4a > (double)v108[1] && igi2_frame.tMin_4a > (double)igi2_frame.vTb[1] && igi2_frame.tMin_4a > (double)v109[1] )
                            goto LABEL_290;
                          if ( igi2_frame.tMin_8a > (double)v108[2] && igi2_frame.tMin_8a > (double)igi2_frame.vTb[2] && igi2_frame.tMin_8a > (double)v109[2] )
                            goto LABEL_290;
                          if ( igi2_frame.tMaxa < (double)*v108 && igi2_frame.tMaxa < (double)*igi2_frame.vTb && igi2_frame.tMaxa < (double)*v109 )
                            goto LABEL_290;
                          if ( igi2_frame.tMax_4a < (double)v108[1] && igi2_frame.tMax_4a < (double)igi2_frame.vTb[1] && igi2_frame.tMax_4a < (double)v109[1] )
                            goto LABEL_290;
                          if ( igi2_frame.tMax_8a < (double)v108[2] && igi2_frame.tMax_8a < (double)igi2_frame.vTb[2] && igi2_frame.tMax_8a < (double)v109[2] )
                            goto LABEL_290;
                          igi2_frame.tEdge0 = *v109 - *v108;
                          igi2_frame.tEdge0_4 = v109[1] - v108[1];
                          igi2_frame.tEdge0_8 = v109[2] - v108[2];
                          igi2_frame.v289 = *igi2_frame.vTb - *v108;
                          igi2_frame.v290 = igi2_frame.vTb[1] - v108[1];
                          v110 = igi2_frame.vTb[2] - v108[2];
                          igi2_frame.v291 = v110;
                          igi2_frame.v234 = v110 * igi2_frame.tEdge0_4 - igi2_frame.v290 * igi2_frame.tEdge0_8;
                          v111 = igi2_frame.v291 * igi2_frame.tEdge0 - igi2_frame.v289 * igi2_frame.tEdge0_8;
                          igi2_frame.v180 = v111;
                          igi2_frame.tTemp__4 = -v111;
                          igi2_frame.v203 = igi2_frame.v290 * igi2_frame.tEdge0 - igi2_frame.v289 * igi2_frame.tEdge0_4;
                          igi2_frame.vDota = igi2_frame.v203 * igi2_frame.tDelta_8a + igi2_frame.tTemp__4 * igi2_frame.tDelta_4a + igi2_frame.v234 * igi2_frame.tDeltaa;
                          if ( igi2_frame.vDota == 0.0 )
                            goto LABEL_290;
                          v112 = ((v108[1] - igi2_frame.Real32x3_Rotate_tTemp_4) * igi2_frame.tTemp__4
                                + (v108[2] - igi2_frame.Real32x3_Rotate_tTemp_8) * igi2_frame.v203
                                + (*v108 - igi2_frame.tStartPosa) * igi2_frame.v234)
                               / igi2_frame.vDota;
                          igi2_frame.vTc = v112;
                          if ( v112 < 0.0 || igi2_frame.vTc > 1.0 )
                            goto LABEL_290;
                          igi2_frame.tPos = igi2_frame.vTc * igi2_frame.tDeltaa + igi2_frame.tStartPosa;
                          igi2_frame.tPos_4 = igi2_frame.vTc * igi2_frame.tDelta_4a + igi2_frame.Real32x3_Rotate_tTemp_4;
                          igi2_frame.tPos_8 = igi2_frame.vTc * igi2_frame.tDelta_8a + igi2_frame.Real32x3_Rotate_tTemp_8;
                          if ( igi2_frame.v234 >= 0.0 )
                            igi2_frame.v342 = igi2_frame.v234;
                          else
                            igi2_frame.v342 = -igi2_frame.v234;
                          v113 = igi2_frame.tTemp__4;
                          if ( igi2_frame.tTemp__4 < 0.0 )
                            v113 = -v113;
                          v114 = igi2_frame.v203;
                          if ( igi2_frame.v203 < 0.0 )
                            v114 = -v114;
                          if ( igi2_frame.v342 <= v113 || igi2_frame.v342 <= v114 )
                          {
                            if ( v113 <= v114 )
                            {
                              v122 = igi2_frame.v203;
                              if ( igi2_frame.v203 == 0.0 )
                                goto LABEL_290;
                              igi2_frame.v205 = igi2_frame.tPos_4 - v108[1];
                              igi2_frame.v182 = igi2_frame.tPos - *v108;
                              igi2_frame.vDistancea = (igi2_frame.tEdge0 * igi2_frame.v205 - igi2_frame.tEdge0_4 * igi2_frame.v182) / v122;
                              if ( igi2_frame.vDistancea < 0.0 || igi2_frame.vDistancea > 1.0 )
                                goto LABEL_290;
                              v123 = igi2_frame.tEdge0;
                              if ( igi2_frame.tEdge0 < 0.0 )
                                v123 = -v123;
                              v124 = igi2_frame.tEdge0_4;
                              if ( igi2_frame.tEdge0_4 < 0.0 )
                                v124 = -v124;
                              if ( v123 <= v124 )
                              {
                                if ( igi2_frame.tEdge0_4 == 0.0 )
                                  goto LABEL_290;
                                v118 = (igi2_frame.v205 - igi2_frame.v290 * igi2_frame.vDistancea) / igi2_frame.tEdge0_4;
                              }
                              else
                              {
                                v118 = (igi2_frame.v182 - igi2_frame.v289 * igi2_frame.vDistancea) / igi2_frame.tEdge0;
                              }
                              if ( v118 < 0.0 || igi2_frame.vDistancea + v118 > 1.0 )
                                goto LABEL_290;
                              goto LABEL_305;
                            }
                            v119 = igi2_frame.v180;
                            if ( igi2_frame.v180 == 0.0 )
                              goto LABEL_290;
                            igi2_frame.v235 = igi2_frame.tPos_8 - v108[2];
                            igi2_frame.v181 = igi2_frame.tPos - *v108;
                            igi2_frame.vDistancea = (igi2_frame.tEdge0 * igi2_frame.v235 - igi2_frame.tEdge0_8 * igi2_frame.v181) / v119;
                            if ( igi2_frame.vDistancea < 0.0 || igi2_frame.vDistancea > 1.0 )
                              goto LABEL_290;
                            v120 = igi2_frame.tEdge0;
                            if ( igi2_frame.tEdge0 < 0.0 )
                              v120 = -v120;
                            v121 = igi2_frame.tEdge0_8;
                            if ( igi2_frame.tEdge0_8 < 0.0 )
                              v121 = -v121;
                            if ( v120 <= v121 )
                            {
LABEL_286:
                              if ( igi2_frame.tEdge0_8 == 0.0 )
                                goto LABEL_290;
                              v118 = (igi2_frame.v235 - igi2_frame.v291 * igi2_frame.vDistancea) / igi2_frame.tEdge0_8;
                              goto LABEL_288;
                            }
                            v118 = (igi2_frame.v181 - igi2_frame.v289 * igi2_frame.vDistancea) / igi2_frame.tEdge0;
                          }
                          else
                          {
                            v115 = igi2_frame.v234;
                            if ( igi2_frame.v234 == 0.0 )
                              goto LABEL_290;
                            igi2_frame.v235 = igi2_frame.tPos_8 - v108[2];
                            igi2_frame.v204 = igi2_frame.tPos_4 - v108[1];
                            igi2_frame.vDistancea = (igi2_frame.tEdge0_4 * igi2_frame.v235 - igi2_frame.tEdge0_8 * igi2_frame.v204) / v115;
                            if ( igi2_frame.vDistancea < 0.0 || igi2_frame.vDistancea > 1.0 )
                              goto LABEL_290;
                            v116 = igi2_frame.tEdge0_4;
                            if ( igi2_frame.tEdge0_4 < 0.0 )
                              v116 = -v116;
                            v117 = igi2_frame.tEdge0_8;
                            if ( igi2_frame.tEdge0_8 < 0.0 )
                              v117 = -v117;
                            if ( v116 <= v117 )
                              goto LABEL_286;
                            v118 = (igi2_frame.v204 - igi2_frame.v290 * igi2_frame.vDistancea) / igi2_frame.tEdge0_4;
                          }
LABEL_288:
                          if ( v118 < 0.0 || igi2_frame.vDistancea + v118 > 1.0 )
                            goto LABEL_290;
LABEL_305:
                          igi2_frame.v236 = igi2_frame.vTc * igi2_frame.vLineLengthb;
                          if ( !igi2_frame.isHit || igi2_frame.v236 + 40.96 < igi2_frame.vClosest )
                          {
LABEL_313:
                            igi2_frame.tHitUV = v118;
                            igi2_frame.tHitUV_4 = igi2_frame.vDistancea;
                            igi2_frame.vClosest = igi2_frame.vTc * igi2_frame.vLineLengthb;
                            igi2_frame.isHitFrontFace = igi2_frame.vDota < 0.0;
                            igi2_frame.tHitPosb = igi2_frame.vTc * igi2_frame.tDeltaa + igi2_frame.tStartPosa;
                            igi2_frame.tHitPos_4b = igi2_frame.vTc * igi2_frame.tDelta_4a + igi2_frame.Real32x3_Rotate_tTemp_4;
                            igi2_frame.isHitCurrentObject = 1;
                            igi2_frame.isHit = 1;
                            igi2_frame.ptHitFace = (struct MultiMesh_Face_t *)v107;
                            igi2_frame.tHitPos_8a = igi2_frame.vTc * igi2_frame.tDelta_8a + igi2_frame.Real32x3_Rotate_tTemp_8;
                            igi2_frame.iHitLightmap = v107[4];
                            if ( igi2_frame.tStartPosa >= (double)igi2_frame.tPos )
                              v125 = igi2_frame.tPos;
                            else
                              v125 = igi2_frame.tStartPosa;
                            igi2_frame.tMina = v125 - 40.959999084472656;
                            if ( igi2_frame.Real32x3_Rotate_tTemp_4 >= (double)igi2_frame.tPos_4 )
                              v126 = igi2_frame.tPos_4;
                            else
                              v126 = igi2_frame.Real32x3_Rotate_tTemp_4;
                            igi2_frame.tMin_4a = v126 - 40.959999084472656;
                            if ( igi2_frame.Real32x3_Rotate_tTemp_8 >= (double)igi2_frame.tPos_8 )
                              v127 = igi2_frame.tPos_8;
                            else
                              v127 = igi2_frame.Real32x3_Rotate_tTemp_8;
                            igi2_frame.tMin_8a = v127 - 40.959999084472656;
                            if ( igi2_frame.tStartPosa <= (double)igi2_frame.tPos )
                              v128 = igi2_frame.tPos;
                            else
                              v128 = igi2_frame.tStartPosa;
                            igi2_frame.tMaxa = v128 + 40.959999084472656;
                            if ( igi2_frame.Real32x3_Rotate_tTemp_4 <= (double)igi2_frame.tPos_4 )
                              v129 = igi2_frame.tPos_4;
                            else
                              v129 = igi2_frame.Real32x3_Rotate_tTemp_4;
                            igi2_frame.tMax_4a = v129 + 40.959999084472656;
                            if ( igi2_frame.Real32x3_Rotate_tTemp_8 <= (double)igi2_frame.tPos_8 )
                              v130 = igi2_frame.tPos_8 + 40.959999084472656;
                            else
                              v130 = igi2_frame.Real32x3_Rotate_tTemp_8 + 40.959999084472656;
                            igi2_frame.tMax_8a = v130;
                            goto LABEL_290;
                          }
                          if ( igi2_frame.v236 >= igi2_frame.vClosest )
                          {
                            if ( igi2_frame.v236 - 40.96 >= igi2_frame.vClosest || igi2_frame.vDota >= 0.0 )
                              goto LABEL_290;
                          }
                          else if ( igi2_frame.vDota < 0.0 )
                          {
                            goto LABEL_313;
                          }
                          if ( !igi2_frame.isHitFrontFace )
                            goto LABEL_313;
LABEL_290:
                          v107 += 6;
                          if ( ++igi2_frame.iFacea >= (int)igi2_frame.ptVertex2c )
                            goto LABEL_213;
                        }
                      }
                      goto LABEL_213;
                    }
                  }
                  else
                  {
                    v99 = ptSphere->iNext;
                    if ( v99 )
                    {
                      ptSphere = &igi2_frame.ptFirstSpherea[v99];
                      igi2_frame.v270 = ptSphere->tSphere.vRadius;
                      v100 = ptSphere->tSphere.tPos.vX;
                      igi2_frame.v346[v98] = ptSphere;
                      igi2_frame.vDistanced = ptSphere->tSphere.tPos.vZ - igi2_frame.Real32x3_Rotate_tTemp_8;
                      igi2_frame.vDotd = ptSphere->tSphere.tPos.vY - igi2_frame.Real32x3_Rotate_tTemp_4;
                      igi2_frame.v1DivSquaredDistanceb = v100 - igi2_frame.tStartPosa;
                      v101 = igi2_frame.vDistanced * igi2_frame.tDelta_8a + igi2_frame.vDotd * igi2_frame.tDelta_4a + igi2_frame.v1DivSquaredDistanceb * igi2_frame.tDeltaa;
                      if ( igi2_frame.v270 * igi2_frame.v270 >= igi2_frame.v1DivSquaredDistanceb * igi2_frame.v1DivSquaredDistanceb
                                        + igi2_frame.vDotd * igi2_frame.vDotd
                                        + igi2_frame.vDistanced * igi2_frame.vDistanced
                                        - v101 * v101 * igi2_frame.v337
                        && ptSphere->tSphere.tPos.vX + ptSphere->tSphere.vRadius >= igi2_frame.tMina
                        && ptSphere->tSphere.vRadius + ptSphere->tSphere.tPos.vY >= igi2_frame.tMin_4a
                        && ptSphere->tSphere.vRadius + ptSphere->tSphere.tPos.vZ >= igi2_frame.tMin_8a
                        && ptSphere->tSphere.tPos.vX - ptSphere->tSphere.vRadius <= igi2_frame.tMaxa
                        && ptSphere->tSphere.tPos.vY - ptSphere->tSphere.vRadius <= igi2_frame.tMax_4a
                        && ptSphere->tSphere.tPos.vZ - ptSphere->tSphere.vRadius <= igi2_frame.tMax_8a )
                      {
                        goto LABEL_223;
                      }
                    }
                    else
                    {
                      igi2_frame.nLevel = --v98;
                      if ( v98 < 0 )
                      {
                        if ( igi2_frame.isHitCurrentObject )
                        {
                          v131 = igi2_frame.tHitPosb - igi2_frame.ptMaterialc;
                          igi2_frame.v339 = igi2_frame.tHitPos_4b * *(float *)&ptQTask[3].tQTaskRefList.ptHead
                               + v131 * *(float *)&ptQTask[3].tQTaskChildren.ptTail
                               + igi2_frame.tHitPos_8a * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle;
                          igi2_frame.v340 = igi2_frame.tHitPos_4b * *(float *)&ptQTask[3].ptParent
                               + v131 * *(float *)&ptQTask[3].tQTaskRefList.ptTail
                               + igi2_frame.tHitPos_8a * *(float *)&ptQTask[3].eQTaskType;
                          igi2_frame.tTempPos.vX = igi2_frame.tHitPos_4b * *(float *)&ptQTask[3].tQTaskChildren.ptHead
                                      + v131 * *(float *)&ptQTask[3].ptPrev
                                      + igi2_frame.tHitPos_8a * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle
                                      + *(double *)&ptQTask[1].ptNext;
                          igi2_frame.tTempPos.vY = igi2_frame.v339 + *(double *)&ptQTask[1].tQTaskChildren.ptHead;
                          igi2_frame.tTempPos.vZ = igi2_frame.v340 + *(double *)&ptQTask[1].tQTaskChildren.ptTail;
                          igi2_frame.vClosest = Real64x3_Distance(igi2_frame.ptStartPos, &igi2_frame.tTempPos);
                          if ( !igi2_frame.bColor || igi2_frame.vClosest < igi2_frame.ptIntersection->vDistance )
                          {
                            v132 = &igi2_frame.ptVertexPos[igi2_frame.ptHitFace->aiVertex[1]].tPos.vX;
                            v133 = &igi2_frame.ptVertexPos[igi2_frame.ptHitFace->aiVertex[0]].tPos.vX;
                            v134 = &igi2_frame.ptVertexPos[igi2_frame.ptHitFace->aiVertex[2]].tPos.vX;
                            v135 = igi2_frame.ptCollMesh->ptMaterial[igi2_frame.ptHitFace->iMaterial].iMaterial;
                            if ( v135 == 0xFFFF )
                              igi2_frame.ptMateriald = ptQTask[2].ptParent[2].tQTaskChildren.ptMiddle;
                            else
                              igi2_frame.ptMateriald = *(&ptQTask[2].ptParent[2].tQTaskChildren.ptHead + v135);
                            v136 = *v134 - *v133;
                            v137 = v134[1] - v133[1];
                            v138 = v134[2] - v133[2];
                            igi2_frame.v292 = *v132 - *v133;
                            igi2_frame.v293 = v132[1] - v133[1];
                            igi2_frame.v294 = v132[2] - v133[2];
                            igi2_frame.v335 = v138 * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle
                                 + v136 * *(float *)&ptQTask[3].ptPrev
                                 + v137 * *(float *)&ptQTask[3].tQTaskChildren.ptHead;
                            igi2_frame.v336 = v137 * *(float *)&ptQTask[3].tQTaskRefList.ptHead
                                 + v138 * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle
                                 + v136 * *(float *)&ptQTask[3].tQTaskChildren.ptTail;
                            v139 = v138 * *(float *)&ptQTask[3].eQTaskType
                                 + v136 * *(float *)&ptQTask[3].tQTaskRefList.ptTail
                                 + v137 * *(float *)&ptQTask[3].ptParent;
                            v140 = igi2_frame.v294 * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle
                                 + igi2_frame.v292 * *(float *)&ptQTask[3].ptPrev
                                 + igi2_frame.v293 * *(float *)&ptQTask[3].tQTaskChildren.ptHead;
                            v141 = igi2_frame.v293 * *(float *)&ptQTask[3].tQTaskRefList.ptHead
                                 + igi2_frame.v294 * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle
                                 + igi2_frame.v292 * *(float *)&ptQTask[3].tQTaskChildren.ptTail;
                            v142 = igi2_frame.v294 * *(float *)&ptQTask[3].eQTaskType
                                 + igi2_frame.v292 * *(float *)&ptQTask[3].tQTaskRefList.ptTail
                                 + igi2_frame.v293 * *(float *)&ptQTask[3].ptParent;
                            igi2_frame.v330 = igi2_frame.v336 * v142 - v141 * v139;
                            igi2_frame.v331 = -(v142 * igi2_frame.v335 - v140 * v139);
                            v143 = &igi2_frame.ptIntersection->tNormal.vX;
                            igi2_frame.ptIntersection->tNormal.vX = igi2_frame.v330;
                            igi2_frame.ptIntersection->tNormal.vY = igi2_frame.v331;
                            igi2_frame.v332 = v141 * igi2_frame.v335 - v140 * igi2_frame.v336;
                            igi2_frame.ptIntersection->tNormal.vZ = igi2_frame.v332;
                            if ( igi2_frame.ptIntersection->tNormal.vX != 0.0
                              || igi2_frame.ptIntersection->tNormal.vY != 0.0
                              || igi2_frame.ptIntersection->tNormal.vZ != 0.0 )
                            {
                              v144 = 1.0
                                   / sqrt(
                                       *v143 * *v143
                                     + igi2_frame.ptIntersection->tNormal.vY * igi2_frame.ptIntersection->tNormal.vY
                                     + igi2_frame.ptIntersection->tNormal.vZ * igi2_frame.ptIntersection->tNormal.vZ);
                              *v143 = *v143 * v144;
                              igi2_frame.ptIntersection->tNormal.vY = igi2_frame.ptIntersection->tNormal.vY * v144;
                              igi2_frame.ptIntersection->tNormal.vZ = igi2_frame.ptIntersection->tNormal.vZ * v144;
                            }
                            if ( BYTE1(ptQTask[38].tQTaskRefList.ptHead) )
                            {
                              *v143 = -*v143;
                              igi2_frame.ptIntersection->tNormal.vY = -igi2_frame.ptIntersection->tNormal.vY;
                              igi2_frame.ptIntersection->tNormal.vZ = -igi2_frame.ptIntersection->tNormal.vZ;
                            }
                            v145 = igi2_frame.tTempPos.vX;
                            igi2_frame.ptIntersection->tLocalNormal.vX = igi2_frame.ptIntersection->tNormal.vX;
                            v146 = igi2_frame.ptIntersection->tNormal.vZ;
                            igi2_frame.ptIntersection->tLocalNormal.vY = igi2_frame.ptIntersection->tNormal.vY;
                            igi2_frame.ptIntersection->tLocalNormal.vZ = v146;
                            igi2_frame.ptIntersection->tLocalPos.vX = v145 - *(double *)&ptQTask[1].ptNext;
                            igi2_frame.ptIntersection->tLocalPos.vY = igi2_frame.tTempPos.vY - *(double *)&ptQTask[1].tQTaskChildren.ptHead;
                            v147 = igi2_frame.tTempPos.vZ - *(double *)&ptQTask[1].tQTaskChildren.ptTail;
                            qmemcpy(&igi2_frame.ptIntersection->tPos, &igi2_frame.tTempPos, sizeof(igi2_frame.ptIntersection->tPos));
                            igi2_frame.ptIntersection->tLocalPos.vZ = v147;
                            igi2_frame.ptIntersection->ptHitObj = (struct QObj_s *)ptQTask;
                            igi2_frame.ptIntersection->ptEnterMaterial = igi2_frame.isHitFrontFace != 0
                                                            ? (struct QMaterial_t *)igi2_frame.ptMateriald
                                                            : nullptr;
                            igi2_frame.ptIntersection->isDoubleFace = 1;
                            igi2_frame.ptIntersection->isHit = 1;
                            LODWORD(igi2_frame.ptIntersection->vDistance) = LODWORD(igi2_frame.vClosest);
                            igi2_frame.ptIntersection->ptLeaveMaterial = igi2_frame.isHitFrontFace != 0
                                                            ? nullptr
                                                            : (struct QMaterial_t *)igi2_frame.ptMateriald;
                            HIDWORD(igi2_frame.ptIntersection->vDistance) = HIDWORD(igi2_frame.vClosest);
                            igi2_frame.ptIntersection->iFace = igi2_frame.ptHitFace - igi2_frame.ptCollMesh->ptFace;
                            if ( igi2_frame.ptMesh->eRenderMeshType == MESH3D_RENDERMESHTYPE_DIRECT3D_BUILDING
                              && igi2_frame.iHitLightmap != 0xFFFF
                              && (v148 = ptQTask[7].tQTaskRefList.ptHead) != nullptr
                              && (ptNext = v148->ptNext) != nullptr )
                            {
                              v150 = &igi2_frame.ptVertexPos[igi2_frame.ptHitFace->aiVertex[0]].u.tLightmapUV.vX;
                              v151 = igi2_frame.ptVertexPos[igi2_frame.ptHitFace->aiVertex[2]].u.tLightmapUV.vY
                                   - igi2_frame.ptVertexPos[igi2_frame.ptHitFace->aiVertex[0]].u.tLightmapUV.vY;
                              igi2_frame.v304 = igi2_frame.ptVertexPos[igi2_frame.ptHitFace->aiVertex[1]].u.tLightmapUV.vX - *v150;
                              igi2_frame.v305 = igi2_frame.ptVertexPos[igi2_frame.ptHitFace->aiVertex[1]].u.tLightmapUV.vY
                                   - igi2_frame.ptVertexPos[igi2_frame.ptHitFace->aiVertex[0]].u.tLightmapUV.vY;
                              igi2_frame.tUVEdge0.vX = igi2_frame.tHitUV * (igi2_frame.ptVertexPos[igi2_frame.ptHitFace->aiVertex[2]].u.tLightmapUV.vX - *v150);
                              igi2_frame.v306 = igi2_frame.tHitUV_4 * igi2_frame.v305;
                              igi2_frame.tUV_4 = igi2_frame.v306 + igi2_frame.tHitUV * v151;
                              igi2_frame.tUV = igi2_frame.tHitUV_4 * igi2_frame.v304 + igi2_frame.tUVEdge0.vX + *v150;
                              igi2_frame.tUV_4a = igi2_frame.tUV_4 + v150[1];
                              Texel = Lightmap_ReadTexel(
                                        (struct Mesh3D_Lightmap_t *)&ptNext[5] + igi2_frame.iHitLightmap,
                                        igi2_frame.tUV,
                                        igi2_frame.tUV_4a);
                              v153 = (double)((unsigned __int8)Texel + BYTE1(Texel) + (unsigned int)BYTE2(Texel))
                                   * 0.0026143791619688272;
                              v154 = igi2_frame.ptIntersection;
                            }
                            else
                            {
                              igi2_frame.tLight_4 = Mesh3D_atAmbientColor[1].vY;
                              v154 = igi2_frame.ptIntersection;
                              igi2_frame.tLight = Mesh3D_atAmbientColor[1].vX;
                              if ( SkyDome_ptDirlight
                                && (v155 = SkyDome_ptDirlight->tDir.vZ * igi2_frame.ptIntersection->tNormal.vZ
                                         + SkyDome_ptDirlight->tDir.vY * igi2_frame.ptIntersection->tNormal.vY
                                         + igi2_frame.ptIntersection->tNormal.vX * SkyDome_ptDirlight->tDir.vX,
                                    v155 > 0.0) )
                              {
                                igi2_frame.tLight = v155 * SkyDome_ptDirlight->tFrontColor.vX + Mesh3D_atAmbientColor[1].vX;
                                igi2_frame.tLight_4 = v155 * SkyDome_ptDirlight->tFrontColor.vY + Mesh3D_atAmbientColor[1].vY;
                                v156 = v155 * SkyDome_ptDirlight->tFrontColor.vZ + Mesh3D_atAmbientColor[1].vZ;
                              }
                              else
                              {
                                v156 = Mesh3D_atAmbientColor[1].vZ;
                              }
                              v153 = (v156 + igi2_frame.tLight_4 + igi2_frame.tLight) * 0.3333333432674408;
                            }
                            v154->vLight = v153;
                          }
                        }
                        goto LABEL_355;
                      }
                      ptSphere = (struct MultiMesh_Sphere_t *)igi2_frame.v346[v98];
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}

// source: e/3/splineobjsegment.c:1678  [anchor-mhash]
void __cdecl SplineObjSegment_LineOfSightHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float tDelta; };
    struct { char igi2_o1[4]; float tDelta_4; };
    struct { char igi2_o2[8]; float tDelta_8; };
    struct { char igi2_o3[12]; float tReal32x3; };
    struct { char igi2_o4[16]; float tReal32x3_4; };
    struct { char igi2_o5[16]; float tReal32x3_4a; };
    struct { char igi2_o6[16]; float tReal32x3_4b; };
    struct { char igi2_o7[20]; float tReal32x3_8; };
    struct { char igi2_o8[20]; float tReal32x3_8a; };
    struct { char igi2_o9[24]; float v25; };
    struct { char igi2_o10[28]; float vLOSDistance; };
    struct { char igi2_o11[32]; struct real64x3_t tStart; };
    struct { char igi2_o12[60]; float v28; };
    struct { char igi2_o13[64]; float v29; };
    struct { char igi2_o14[72]; struct TraceLinesContext_s tTraceLinesContext; };
    struct { char igi2_o15[112]; struct real64x3_t tEnd; };
    struct { char igi2_o16[136]; struct QIntersection_s tQIntersection; };
    char igi2_extent[256];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  __int16 v2; // ax
  void (__cdecl *pfHandler)(struct QTask_s *, _DWORD); // eax
  long double v4; // st4
  double v5; // st7
  double v6; // st7
  double v7; // st6
  struct CollisionEvaluateContext_s *v8; // ecx
  struct QIntersection_s *ptIntersection; // ecx
  double *v10; // eax
  double v11; // st7
  long double v12; // st4
  struct QMaterial_t *ptEnterMaterial; // edx
  double v14; // st6
  double v15; // st7

  qmemcpy(&igi2_frame.tStart, *(void **)pxContext, sizeof(igi2_frame.tStart));
  qmemcpy(&igi2_frame.tEnd, *((void **)pxContext + 1), sizeof(igi2_frame.tEnd));
  igi2_frame.tDelta = igi2_frame.tEnd.vX - igi2_frame.tStart.vX;
  igi2_frame.tDelta_4 = igi2_frame.tEnd.vY - igi2_frame.tStart.vY;
  igi2_frame.tDelta_8 = igi2_frame.tEnd.vZ - igi2_frame.tStart.vZ;
  if ( igi2_frame.tDelta != 0.0 || igi2_frame.tDelta_4 != 0.0 || igi2_frame.tDelta_8 != 0.0 )
  {
    v2 = *((_WORD *)pxContext + 4);
    if ( v2 == 512
      || (pfHandler = (void (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[v2][ptQTask->eQTaskType].pfHandler) == nullptr
      || (pfHandler(ptQTask, *((_DWORD *)pxContext + 3)), **((_BYTE **)pxContext + 3)) )
    {
      v4 = sqrt(igi2_frame.tDelta * igi2_frame.tDelta + igi2_frame.tDelta_4 * igi2_frame.tDelta_4 + igi2_frame.tDelta_8 * igi2_frame.tDelta_8);
      if ( *((_BYTE *)pxContext + 20) )
      {
        igi2_frame.v25 = v4;
        igi2_frame.tReal32x3 = igi2_frame.tDelta;
        igi2_frame.tReal32x3_4 = igi2_frame.tDelta_4;
        igi2_frame.vLOSDistance = igi2_frame.v25 * *((float *)pxContext + 7);
        if ( igi2_frame.tDelta == 0.0 && igi2_frame.tDelta_4 == 0.0 && igi2_frame.tDelta_8 == 0.0 )
        {
          v6 = igi2_frame.tDelta_8;
        }
        else
        {
          v5 = 1.0 / igi2_frame.v25;
          igi2_frame.tReal32x3 = igi2_frame.tDelta * v5;
          igi2_frame.tReal32x3_4 = igi2_frame.tDelta_4 * v5;
          v6 = v5 * igi2_frame.tDelta_8;
        }
        v7 = igi2_frame.vLOSDistance + 40.959999084472656;
        igi2_frame.tReal32x3_4a = v7 * igi2_frame.tReal32x3_4;
        igi2_frame.tReal32x3_8 = v7 * v6;
        igi2_frame.tStart.vX = igi2_frame.tReal32x3 * v7 + igi2_frame.tStart.vX;
        igi2_frame.tStart.vY = igi2_frame.tReal32x3_4a + igi2_frame.tStart.vY;
        igi2_frame.tStart.vZ = igi2_frame.tReal32x3_8 + igi2_frame.tStart.vZ;
      }
      else
      {
        igi2_frame.v25 = v4;
        igi2_frame.vLOSDistance = v4;
      }
      igi2_frame.tTraceLinesContext.eEvalQTaskEvent = *((_WORD *)pxContext + 4);
      igi2_frame.tTraceLinesContext.ptStart = &igi2_frame.tStart;
      v8 = *((struct CollisionEvaluateContext_s **)pxContext + 3);
      igi2_frame.tQIntersection.isHit = 0;
      igi2_frame.tTraceLinesContext.nNumLines = 1;
      igi2_frame.tTraceLinesContext.ptEnd = &igi2_frame.tEnd;
      igi2_frame.tTraceLinesContext.ptIntersection = &igi2_frame.tQIntersection;
      igi2_frame.tTraceLinesContext.ptEvalContext = v8;
      memset(&igi2_frame.tTraceLinesContext.iMesh, 0, 12);
      igi2_frame.tTraceLinesContext.nValidationNumber = 1094861636;
      while ( 1 )
      {
        SplineObjSegment_TraceLinesHandler(ptQTask, &igi2_frame.tTraceLinesContext);
        ptIntersection = igi2_frame.tTraceLinesContext.ptIntersection;
        if ( !igi2_frame.tTraceLinesContext.ptIntersection->isHit )
          break;
        v10 = *(double **)pxContext;
        igi2_frame.v28 = igi2_frame.tTraceLinesContext.ptIntersection->tPos.vX - *(double *)*(_DWORD *)pxContext;
        igi2_frame.v29 = igi2_frame.tTraceLinesContext.ptIntersection->tPos.vY - v10[1];
        v11 = igi2_frame.tTraceLinesContext.ptIntersection->tPos.vZ - v10[2];
        v12 = sqrt(igi2_frame.v28 * igi2_frame.v28 + igi2_frame.v29 * igi2_frame.v29 + v11 * v11);
        if ( *((_BYTE *)pxContext + 20) )
        {
          if ( v12 >= igi2_frame.vLOSDistance && *((float *)pxContext + 8) <= 0.0 )
            break;
        }
        ptEnterMaterial = igi2_frame.tTraceLinesContext.ptIntersection->ptEnterMaterial;
        if ( (ptEnterMaterial || (ptEnterMaterial = igi2_frame.tTraceLinesContext.ptIntersection->ptLeaveMaterial) != nullptr)
          && igi2_frame.tDelta_8 * igi2_frame.tTraceLinesContext.ptIntersection->tNormal.vZ
           + igi2_frame.tDelta_4 * igi2_frame.tTraceLinesContext.ptIntersection->tNormal.vY
           + igi2_frame.tDelta * igi2_frame.tTraceLinesContext.ptIntersection->tNormal.vX < 0.0 )
        {
          *((_BYTE *)pxContext + 20) = 1;
          *((float *)pxContext + 7) = v12 / igi2_frame.v25;
          v14 = *((float *)pxContext + 8) * ptEnterMaterial->vTransparency;
          *((_DWORD *)pxContext + 6) = ptEnterMaterial;
          *((float *)pxContext + 8) = v14;
          if ( *((float *)pxContext + 8) == 0.0 )
            break;
        }
        igi2_frame.vLOSDistance = v12;
        v15 = 40.959999084472656 / igi2_frame.v25;
        igi2_frame.tReal32x3_4b = v15 * igi2_frame.tDelta_4;
        igi2_frame.tReal32x3_8a = v15 * igi2_frame.tDelta_8;
        igi2_frame.tStart.vX = igi2_frame.tDelta * v15 + ptIntersection->tPos.vX;
        igi2_frame.tStart.vY = igi2_frame.tReal32x3_4b + ptIntersection->tPos.vY;
        igi2_frame.tStart.vZ = igi2_frame.tReal32x3_8a + ptIntersection->tPos.vZ;
        ptIntersection->isHit = 0;
      }
    }
  }
}

// source: e/3/splineobjsegment.c:1851  [size]
void __cdecl SplineObjSegment_GetMaterialHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: e/3/splineobjsegment.c:2554  [size]
void __cdecl SplineObjSegment_EnterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct DrawSplineMeshContext_t tContext; };
    struct { char igi2_o1[24]; struct MagicObjEnterContext_s tMagicObjEnterContext; };
    char igi2_extent[96];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // ebp
  int v3; // edx
  int v4; // eax
  struct QTask_s *ptHead; // ecx
  int v6; // edx
  struct QTask_s *v7; // eax
  int v8; // esi
  void (__cdecl *pfHandler)(struct QTask_s *, struct MagicObjEnterContext_s *); // eax
  int v10; // edx

  v2 = Lightsource_nLightDataStackPos + Lightsource_nLightDataBufferPos;
  igi2_frame.tContext.tLightContext.nLightNum = Lightsource_nLightDataStackPos;
  v3 = Hazinglayers_iHazingBuffer;
  igi2_frame.tContext.tLightContext.pnLightList = (int *)(4 * Lightsource_nLightDataBufferPos + 140666816);
  v4 = Hazinglayers_iHazingStack;
  qmemcpy(igi2_frame.tContext.tLightContext.pnLightList, Lightsource_anLightDataStack, 4 * Lightsource_nLightDataStackPos);
  igi2_frame.tContext.ptSplineObjSegment = (struct SplineObjSegment_s *)ptQTask;
  igi2_frame.tContext.tLightContext.pptHazingList = (struct HazingDynCubeObj_t **)(4 * v3 + 129834072);
  qmemcpy(igi2_frame.tContext.tLightContext.pptHazingList, Hazinglayers_aptHazingStack, 4 * v4);
  igi2_frame.tContext.tLightContext.nNumHazingBox = v4;
  Lightsource_nLightDataBufferPos = v2;
  Hazinglayers_iHazingBuffer = v4 + v3;
  igi2_frame.tContext.eDrawMode = MESH3D_DRAWMODE_NORMAL;
  RenderMode_tActiveRenderMode.apfRenderModeMethod[Mesh3D_eDrawSplineMeshRenderModeMethod](&igi2_frame.tContext);
  qmemcpy(&igi2_frame.tMagicObjEnterContext, &ptQTask[1], 0x18u);
  ptHead = ptQTask->tQTaskChildren.ptHead;
  igi2_frame.tMagicObjEnterContext.tParentOrientation.tX.vX = 1.0;
  memset(&igi2_frame.tMagicObjEnterContext.tParentOrientation.tX.vY, 0, 12);
  igi2_frame.tMagicObjEnterContext.tParentOrientation.tY.vY = 1.0;
  memset(&igi2_frame.tMagicObjEnterContext.tParentOrientation.tY.vZ, 0, 12);
  igi2_frame.tMagicObjEnterContext.tParentOrientation.tZ.vZ = 1.0;
  igi2_frame.tMagicObjEnterContext.tParentOrientation.nOps = 0;
  if ( ptHead->ptNext && ptHead )
  {
    v6 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v7 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v7 = nullptr;
      v8 = MagicObj_eMagicObjEnterEvent;
      QTask_atProtectedQTaskStack[v6].ptQTask = v7;
      pfHandler = (void (__cdecl *)(struct QTask_s *, struct MagicObjEnterContext_s *))QTask_aatQTaskFinalEvent[v8][ptHead->eQTaskType].pfHandler;
      v10 = v6 + 1;
      QTask_nProtectedQTaskStackOffset = v10;
      if ( pfHandler )
      {
        pfHandler(ptHead, &igi2_frame.tMagicObjEnterContext);
        v10 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v10];
      v6 = v10 - 1;
      QTask_nProtectedQTaskStackOffset = v6;
    }
    while ( ptHead );
  }
}

// source: e/3/splineobjsegment.c:2640  [anchor-mhash]
void __cdecl SplineObjSegment_DrawEnvmapHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // ebx
  int v3; // edx
  int v4; // eax
  struct DrawSplineMeshContext_t tContext; // [esp+Ch] [ebp-18h] BYREF

  tContext.ptSplineObjSegment = (struct SplineObjSegment_s *)ptQTask;
  v2 = Lightsource_nLightDataStackPos + Lightsource_nLightDataBufferPos;
  tContext.tLightContext.nLightNum = Lightsource_nLightDataStackPos;
  v3 = Hazinglayers_iHazingBuffer;
  tContext.tLightContext.pnLightList = (int *)(4 * Lightsource_nLightDataBufferPos + 140666816);
  v4 = Hazinglayers_iHazingStack;
  qmemcpy(tContext.tLightContext.pnLightList, Lightsource_anLightDataStack, 4 * Lightsource_nLightDataStackPos);
  tContext.eDrawMode = MESH3D_DRAWMODE_ENVMAP;
  tContext.tLightContext.pptHazingList = (struct HazingDynCubeObj_t **)(4 * v3 + 129834072);
  qmemcpy(tContext.tLightContext.pptHazingList, Hazinglayers_aptHazingStack, 4 * v4);
  Hazinglayers_iHazingBuffer = v4 + v3;
  Lightsource_nLightDataBufferPos = v2;
  tContext.tLightContext.nNumHazingBox = v4;
  RenderMode_tActiveRenderMode.apfRenderModeMethod[Mesh3D_eDrawSplineMeshRenderModeMethod](&tContext);
}

// source: e/3/splineobjsegment.c:2665  [size]
void __cdecl SplineObjSegment_EnumerateEnvmapHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QObjectVector_s *v2; // esi
  unsigned int nAllocated; // eax
  struct QTask_s **v4; // edi
  _DWORD v5[3]; // [esp+0h] [ebp-Ch] BYREF

  if ( (*((_BYTE *)pxContext + 8) & 0x10) != 0 )
  {
    v2 = *(struct QObjectVector_s **)pxContext;
    if ( *(_DWORD *)(*(_DWORD *)pxContext + 36) == *(_DWORD *)(*(_DWORD *)pxContext + 40) )
      QObjectVector_Realloc(v2, v2->nReallocSize);
    nAllocated = v2->nAllocated;
    v4 = (struct QTask_s **)v2->papxElement[nAllocated];
    v2->nAllocated = nAllocated + 1;
    *v4 = ptQTask;
    v5[0] = ptQTask;
    v5[1] = 0;
    RenderMode_tActiveRenderMode.apfRenderModeMethod[Mesh3D_eIsTransparentRenderModeMethod](v5);
    v4[1] = (struct QTask_s *)((v5[2] != 0) + 2);
  }
}

// source: e/3/splineobjsegment.c:2702  [anchor-mhash]
void __cdecl SplineObjSegment_CreateSphere()
{
  #pragma pack(push, 1)
  union
  {
    struct { int iFace; };
    struct { char igi2_o1[4]; struct MultiMesh_Sphere_t *ptSphere; };
    struct { char igi2_o2[8]; struct real32x3_t *aptVertex[3]; };
    char igi2_extent[20];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct MultiMesh_Sphere_t *v0; // edi
  unsigned __int16 iChild; // ax
  int v2; // ebx
  struct MultiMesh_Sphere_t *v3; // esi
  unsigned __int16 i; // ax
  struct MultiMesh_Sphere_t *v5; // esi
  unsigned __int16 nFace; // ax
  int v7; // edx
  struct real32x3_t *v8; // edi
  int v9; // ebp
  struct MultiMesh_Face_t *ptFace; // eax
  int v11; // ecx
  struct MultiMesh_Face_t *v12; // eax
  int v13; // ecx
  int v14; // eax
  int v15; // esi
  struct MultiMesh_Sphere_t *v16; // ecx
  int j; // edx
  struct real32x3_t *v18; // eax
  double v19; // st6
  double v20; // st5
  double v21; // st3
  long double vRadius; // st7

  v0 = SplineObjSegment_aptNewSphere[SplineObjSegment_nNewSphere];
  iChild = v0->iChild;
  v2 = SplineObjSegment_nNewSphere + 1;
  igi2_frame.ptSphere = v0;
  v0->tSphere.vRadius = 0.0;
  SplineObjSegment_nNewSphere = v2;
  if ( iChild )
  {
    v3 = &SplineObjSegment_ptActiveSphereTree->ptSphere[iChild];
    SplineObjSegment_aptNewSphere[v2] = v3;
    SplineObjSegment_CreateSphere();
    for ( i = v3->iNext; i; i = v5->iNext )
    {
      v5 = &SplineObjSegment_ptActiveSphereTree->ptSphere[i];
      SplineObjSegment_aptNewSphere[SplineObjSegment_nNewSphere] = v5;
      SplineObjSegment_CreateSphere();
    }
    v2 = SplineObjSegment_nNewSphere;
  }
  nFace = v0->nFace;
  if ( nFace )
  {
    v7 = v0->iFace;
    igi2_frame.iFace = v7;
    if ( v7 < v7 + nFace )
    {
      v8 = SplineObjSegment_ptActiveVertexList;
      v9 = v7;
      do
      {
        ptFace = SplineObjSegment_ptActiveMesh->ptFace;
        v11 = ptFace[v9].aiVertex[0];
        v12 = &ptFace[v9];
        igi2_frame.aptVertex[0] = &v8[v11];
        v13 = v12->aiVertex[1];
        v14 = v12->aiVertex[2];
        igi2_frame.aptVertex[1] = &v8[v13];
        v15 = 0;
        igi2_frame.aptVertex[2] = &v8[v14];
        if ( v2 > 0 )
        {
          do
          {
            v16 = SplineObjSegment_aptNewSphere[v15];
            for ( j = 0; j < 3; ++j )
            {
              v18 = igi2_frame.aptVertex[j];
              v19 = v18->vY - v16->tSphere.tPos.vY;
              v20 = v18->vX - v16->tSphere.tPos.vX;
              v21 = v18->vZ - v16->tSphere.tPos.vZ;
              vRadius = sqrt(v20 * v20 + v19 * v19 + v21 * v21);
              if ( vRadius < v16->tSphere.vRadius )
                vRadius = v16->tSphere.vRadius;
              v16->tSphere.vRadius = vRadius;
            }
            ++v15;
          }
          while ( v15 < v2 );
          v7 = igi2_frame.iFace;
        }
        ++v7;
        ++v9;
        igi2_frame.iFace = v7;
      }
      while ( v7 < igi2_frame.ptSphere->iFace + igi2_frame.ptSphere->nFace );
    }
  }
  SplineObjSegment_nNewSphere = v2 - 1;
}

// source: e/3/splineobjsegment.c:2788  [anchor-mhash]
void __cdecl SplineObjSegment_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *v1; // ebx
  int v2; // ebp
  int v3; // esi

  World_RemoveDynCubeObj((struct World_s *)ptQTask[8].ptNext, (struct DynCubeObj_s *)ptQTask);
  v1 = ptQTask + 38;
  v2 = 2;
  do
  {
    if ( v1->ptNext )
    {
      v3 = *(_DWORD *)((int)&v1->ptNext[-1].eQTaskType & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v3);
      memset(*(void **)(v3 + 8), 0xCDu, *(_DWORD *)(v3 + 16));
      free((void *)v3);
      v1->ptNext = nullptr;
    }
    v1 = (struct QTask_s *)((char *)v1 + 8);
    --v2;
  }
  while ( v2 );
}

// source: e/3/splineobjsegment.c:2828  [size]
void __cdecl SplineObjSegment_TransformVertex(
        struct SplineObjSegment_s *ptSplineObjSegment,
        struct real32x3_t *ptTransformedPos,
        struct real32x3_t *ptVertexPos)
{
  double vEndX; // st7
  double v4; // st7
  double vY; // st6
  double vZ; // st5
  char isFlip; // al
  double vStartX; // st7
  double v9; // st7
  double v10; // st6
  double v11; // st7
  int v12; // esi
  double v13; // st7
  float *v14; // eax
  float *v15; // edi
  double v16; // st6
  double v17; // st5
  int iArea; // [esp+8h] [ebp-18h]
  __int64 iAreaa; // [esp+8h] [ebp-18h]
  float iAreab; // [esp+8h] [ebp-18h]
  float v21; // [esp+10h] [ebp-10h]
  float v22; // [esp+10h] [ebp-10h]
  float tEndPos; // [esp+14h] [ebp-Ch]
  float tEndPos_8; // [esp+1Ch] [ebp-4h]
  float tEndPos_8a; // [esp+1Ch] [ebp-4h]
  struct real32x3_t struct_real32x3_t; // 0:^14.12

  vEndX = ptSplineObjSegment->vEndX;
  if ( ptSplineObjSegment->isLinear )
  {
    v4 = ptVertexPos->vX - (vEndX + ptSplineObjSegment->vStartX) * 0.5;
    vY = ptVertexPos->vY;
    vZ = ptVertexPos->vZ;
    struct_real32x3_t.vX = vZ * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tX.vZ
                         + vY * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tX.vY
                         + v4 * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tX.vX;
    struct_real32x3_t.vY = vZ * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tY.vZ
                         + vY * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tY.vY
                         + v4 * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tY.vX;
    struct_real32x3_t.vZ = vZ * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vZ
                         + vY * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vY
                         + v4 * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vX;
    *ptTransformedPos = struct_real32x3_t;
  }
  else
  {
    isFlip = ptSplineObjSegment->isFlip;
    *(float *)&iArea = 1.0 / (vEndX - ptSplineObjSegment->vStartX);
    if ( isFlip )
      vStartX = ptSplineObjSegment->vEndX;
    else
      vStartX = ptSplineObjSegment->vStartX;
    v9 = -vStartX;
    v10 = (double)ptSplineObjSegment->nAreas * *(float *)&iArea;
    if ( isFlip )
      v10 = -v10;
    v11 = v10 * (v9 + ptVertexPos->vX);
    iAreaa = (__int64)v11;
    v12 = (__int64)v11;
    if ( v12 == ptSplineObjSegment->nAreas )
      LODWORD(iAreaa) = --v12;
    v13 = v11 - (double)(int)iAreaa;
    if ( v13 >= 0.0 )
    {
      if ( v13 > 1.0 )
        v13 = 1.0;
    }
    else
    {
      v13 = 0.0;
    }
    v14 = (float *)(&ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask + v12);
    v15 = (float *)((char *)ptSplineObjSegment + 12 * v12);
    v21 = v14[156] * ptVertexPos->vZ + v14[155] * ptVertexPos->vY;
    iAreab = v14[150] * ptVertexPos->vZ + v14[149] * ptVertexPos->vY + v15[85];
    v16 = v14[153] * ptVertexPos->vZ + v14[152] * ptVertexPos->vY + v15[86];
    v22 = v21 + ptSplineObjSegment->atAreaPos[v12].vZ;
    tEndPos_8 = v14[166] * ptVertexPos->vZ + v14[165] * ptVertexPos->vY;
    tEndPos = v14[160] * ptVertexPos->vZ + v14[159] * ptVertexPos->vY + v15[88];
    v17 = v14[163] * ptVertexPos->vZ + v14[162] * ptVertexPos->vY + v15[89];
    tEndPos_8a = tEndPos_8 + ptSplineObjSegment->atAreaPos[v12 + 1].vZ;
    ptTransformedPos->vX = (tEndPos - iAreab) * v13 + iAreab;
    ptTransformedPos->vY = (v17 - v16) * v13 + v16;
    ptTransformedPos->vZ = (tEndPos_8a - v22) * v13 + v22;
  }
}

// source: e/3/splineobjsegment.c:2909  [anchor-strings]
void __cdecl SplineObjSegment_Open()
{
  unsigned __int16 v0; // si
  unsigned int SystemGroup; // eax

  v0 = QTask_NewQTaskType("SplineObjSegment", 1544, RigidDynCubeObj_eQTaskType, 0, 0);
  SplineObjSegment_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, SplineObjSegment_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 5, SplineObjSegment_EnterHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 11, SplineObjSegment_TraceLinesHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 12, (void (__cdecl *)(struct QTask_s *, void *))SplineObjSegment_GetMaterialHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 10, SplineObjSegment_TraceLinesHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 9, SplineObjSegment_LineOfSightHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    13,
    (void (__cdecl *)(struct QTask_s *, void *))SplineObjSegment_CollisionEvalHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    BspTreeDynCubeObj_eGenerationSizeEvent,
    SplineObjSegment_BspTreeGenerationSizeHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    BspTreeDynCubeObj_eGenerationListEvent,
    SplineObjSegment_BspTreeGenerationListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, Envmap_eDrawQTaskEvent, SplineObjSegment_DrawEnvmapHandler);
  QTask_LinkQTaskEventHandlerFn(v0, Envmap_eEnumerateQTaskEvent, SplineObjSegment_EnumerateEnvmapHandler);
  SystemGroup = QTask_AllocateSystemGroup(0x10000000u);
  QTask_SetQTaskTypeGroup(SplineObjSegment_eQTaskType, SystemGroup);
}

// source: e/3/splineobjsegment.c:2943  [anchor-hash]
void __cdecl SplineObjSegment_Close()
{
  QTask_FreeGroup(0x10000000u);
  QTask_DeleteQTaskType(SplineObjSegment_eQTaskType);
}

// source: e/3/splineobjsegment.c:2972  [anchor-mhash]
struct SplineObjSegment_s *__cdecl SplineObjSegment_New(
        struct QTask_s *ptParent,
        struct World_s *ptWorld,
        struct real64x3_t *ptStartPos,
        struct real64x3_t *ptEndPos,
        struct real32x9_t *ptStartOrientation,
        struct real32x9_t *ptEndOrientation,
        char isLinear,
        char isFlip,
        int nNumAreas,
        int iCollisionLOD,
        char *zModel)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[24]; struct real64x3_t tFakePos; };
    char igi2_extent[52];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v13; // edi
  struct LODVirModel_s *LODVirModelExistsFn; // eax
  struct QTask_s **p_ptPrev; // eax
  int v16; // ecx
  double v17; // st6
  double v18; // st5

  v13 = QTask_NewFn(ptParent, SplineObjSegment_eQTaskType, nullptr);
  LODVirModelExistsFn = MTP_GetLODVirModelExistsFn(zModel);
  ModelObj_Init((struct ModelObj_s *)v13, ptWorld, LODVirModelExistsFn);
  v13[7].tQTaskChildren.ptMiddle = (struct QTask_s *)2;
  v13[7].tQTaskChildren.ptHead = nullptr;
  v13[7].tQTaskRefList.ptHead = nullptr;
  v13[7].tQTaskRefList.ptMiddle = nullptr;
  v13[7].tQTaskRefList.ptTail = nullptr;
  v13[7].ptParent = nullptr;
  *(_DWORD *)&v13[7].eQTaskType = 0;
  p_ptPrev = &v13[38].ptPrev;
  v16 = 2;
  do
  {
    *(p_ptPrev - 1) = nullptr;
    *p_ptPrev = nullptr;
    p_ptPrev += 2;
    --v16;
  }
  while ( v16 );
  v13[8].ptNext = (struct QTask_s *)ptWorld;
  *(_DWORD *)&v13[37].eQTaskType = nNumAreas;
  v13[38].tQTaskChildren.ptTail = nullptr;
  if ( isLinear )
    *(_DWORD *)&v13[37].eQTaskType = 1;
  BYTE1(v13[38].tQTaskRefList.ptHead) = 0;
  LOBYTE(v13[38].tQTaskRefList.ptHead) = 0;
  igi2_frame.tFakePos.vX = (ptStartPos->vX + ptEndPos->vX) * 0.5;
  igi2_frame.tFakePos.vY = (ptStartPos->vY + ptEndPos->vY) * 0.5;
  igi2_frame.tFakePos.vZ = (ptStartPos->vZ + ptEndPos->vZ) * 0.5;
  v17 = ptStartPos->vY - ptEndPos->vY;
  v18 = ptStartPos->vZ - ptEndPos->vZ;
  igi2_frame.ptDynCubeObj = sqrt(v18 * v18 + v17 * v17 + (ptStartPos->vX - ptEndPos->vX) * (ptStartPos->vX - ptEndPos->vX));
  World_RegisterDynCubeObjFirstTimeRadius(
    ptWorld,
    (struct DynCubeObj_s *)v13,
    &igi2_frame.tFakePos,
    igi2_frame.ptDynCubeObj,
    WORLD_DYNCUBETREE_CATEGORY_STATIONARY);
  if ( !LODWORD(ptStartPos->vX) && HIDWORD(ptStartPos->vX) == -1055657250 )
    ptStartPos->vX = -326839.5;
  SplineObjSegment_Update(
    (struct SplineObjSegment_s *)v13,
    ptStartPos,
    ptEndPos,
    ptStartOrientation,
    ptEndOrientation,
    isLinear,
    isFlip,
    nNumAreas,
    iCollisionLOD,
    zModel);
  return (struct SplineObjSegment_s *)v13;
}

// source: e/3/splineobjsegment.c:3071  [anchor-caller]
void __cdecl SplineObjSegment_Update(
        struct SplineObjSegment_s *ptSplineObjSegment,
        struct real64x3_t *ptStartPos,
        struct real64x3_t *ptEndPos,
        struct real32x9_t *ptStartOrientation,
        struct real32x9_t *ptEndOrientation,
        char isLinear,
        char isFlip,
        int nNumAreas,
        int iCollisionLOD,
        char *zModel)
{
  #pragma pack(push, 1)
  union
  {
    struct { int iCount; };
    struct { int iCounta; };
    struct { float iCountb; };
    struct { float iCountc; };
    struct { struct CollisionSphereTree_t *iCountd; };
    struct { char igi2_o5[4]; int iLOD; };
    struct { char igi2_o6[4]; int iLODa; };
    struct { char igi2_o7[4]; struct CollisionSphereTree_t *iLODb; };
    struct { char igi2_o8[4]; int iLODc; };
    struct { char igi2_o9[8]; float vStartAlpha; };
    struct { char igi2_o10[8]; int vStartAlphaa; };
    struct { char igi2_o11[12]; float vT; };
    struct { char igi2_o12[16]; double vLen; };
    struct { char igi2_o13[24]; float v117; };
    struct { char igi2_o14[32]; double v118; };
    struct { char igi2_o15[44]; struct real32x3_t tEndAngles; };
    struct { char igi2_o16[56]; _BYTE tTempPos[40]; };
    struct { char igi2_o17[96]; struct real32x3_t tTempVector; };
    struct { char igi2_o18[108]; float v1DivAreas; };
    struct { char igi2_o19[112]; float v123; };
    struct { char igi2_o20[116]; float v124; };
    struct { char igi2_o21[120]; float v125; };
    struct { char igi2_o22[124]; struct real32x3_t tStartAngles; };
    struct { char igi2_o23[136]; struct real32x3_t ptSource; };
    struct { char igi2_o24[148]; struct real32x3_t tTempAngles; };
    struct { char igi2_o25[160]; struct real64x3_t tFakePos; };
    struct { char igi2_o26[192]; float pvBeta; };
    struct { char igi2_o27[196]; float pvGamma; };
    struct { char igi2_o28[200]; struct Hermite64_s atChannel[3]; };
    struct { char igi2_o29[300]; float v133; };
    char igi2_extent[312];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct real64x3_t *v10; // esi
  unsigned int vY_low; // edx
  double v12; // st4
  double v13; // st3
  double v14; // st7
  double vX; // st5
  double v16; // st4
  int v17; // eax
  double v18; // st7
  int v19; // ecx
  float *v20; // esi
  double v21; // st7
  double v22; // st6
  float *v23; // edi
  long double v24; // st7
  long double v25; // st6
  long double v26; // st7
  double v27; // st7
  float *v28; // esi
  double v29; // st7
  double v30; // st6
  double v31; // st4
  double v32; // st6
  double v33; // st6
  double v34; // st4
  struct LODVirModel_s *LODVirModelExistsFn; // eax
  enum Mesh3D_RenderMeshType_e eRenderMeshType; // ecx
  int v37; // eax
  int v38; // ecx
  int v39; // edx
  float *v40; // ecx
  int j; // edi
  int v42; // edx
  float *v43; // ecx
  int i; // edi
  double v45; // st7
  float v46; // edx
  double v47; // st7
  float v48; // ecx
  float vY; // eax
  double v50; // st7
  float v51; // ecx
  float v52; // edx
  float vZ; // eax
  float v54; // ecx
  float v55; // edx
  int nOps; // eax
  struct real32x9_t *p_tOrientation; // edx
  double v58; // st7
  float v59; // eax
  float v60; // ecx
  float v61; // eax
  float v62; // ecx
  float v63; // eax
  float v64; // ecx
  float v65; // eax
  float v66; // ecx
  int v67; // eax
  long double v68; // st7
  float v69; // ecx
  float v70; // eax
  float v71; // edx
  float v72; // ecx
  float v73; // eax
  float v74; // ecx
  float v75; // edx
  float v76; // eax
  int v77; // ecx
  float v78; // edx
  struct LODVirModel_s *ptLODVirModel; // ecx
  double vRadius; // st7
  int nLOD; // esi
  struct Mesh3D_Mesh_t *ptMesh; // edx
  int k; // edi
  struct real32x3_t *SplineMultiMeshVertexList; // eax
  int v85; // edx
  float *p_vZ; // ecx
  double v87; // st7
  double v88; // st6
  double v89; // st5
  double v90; // st4
  double v91; // st3
  long double v92; // st4
  int v93; // eax
  int v94; // esi
  bool v95; // zf
  int v96; // ecx
  int v97; // eax
  struct CollisionSphereTree_t *atSphereTree; // edi
  char *pxCollisionMesh; // esi
  int v100; // edx
  struct MultiMesh_Mesh_t *v101; // esi
  int nNumSpheres; // esi
  struct MultiMesh_Sphere_t *v103; // eax

  v10 = ptStartPos;
  ptSplineObjSegment->isLinear = isLinear;
  ptSplineObjSegment->isFlip = isFlip;
  ptSplineObjSegment->tRigidDynCubeObj.iCollisionLOD = 0;
  ptSplineObjSegment->nAreas = nNumAreas;
  if ( isLinear )
    ptSplineObjSegment->nAreas = 1;
  vY_low = LODWORD(ptEndPos->vY);
  v12 = ptStartPos->vZ - ptEndPos->vZ;
  v13 = ptStartPos->vY - ptEndPos->vY;
  igi2_frame.vLen = sqrt(v12 * v12 + v13 * v13 + (ptStartPos->vX - ptEndPos->vX) * (ptStartPos->vX - ptEndPos->vX));
  v14 = ptEndOrientation->tX.vX * igi2_frame.vLen;
  vX = ptEndPos->vX;
  v16 = ptStartPos->vX;
  igi2_frame.atChannel[0].vS1 = ptStartOrientation->tX.vX * igi2_frame.vLen;
  igi2_frame.atChannel[0].vN1 = v16;
  igi2_frame.atChannel[0].vA = v16 + v16 - (vX + vX) + v14 + igi2_frame.atChannel[0].vS1;
  igi2_frame.atChannel[0].vB = vX * 3.0 - v16 * 3.0 - (igi2_frame.atChannel[0].vS1 + igi2_frame.atChannel[0].vS1) - v14;
  Hermite64_Init(
    &igi2_frame.atChannel[1],
    ptStartPos->vY,
    COERCE_DOUBLE(__PAIR64__(HIDWORD(ptEndPos->vY), vY_low)),
    ptStartOrientation->tY.vX * igi2_frame.vLen,
    ptEndOrientation->tY.vX * igi2_frame.vLen);
  Hermite64_Init(
    &igi2_frame.atChannel[2],
    ptStartPos->vZ,
    ptEndPos->vZ,
    ptStartOrientation->tZ.vX * igi2_frame.vLen,
    ptEndOrientation->tZ.vX * igi2_frame.vLen);
  Real32x9_GetAngles(ptStartOrientation, &igi2_frame.tStartAngles.vX, &igi2_frame.tStartAngles.vY, &igi2_frame.tStartAngles.vZ);
  Real32x9_GetAngles(ptEndOrientation, &igi2_frame.tEndAngles.vX, &igi2_frame.tEndAngles.vY, &igi2_frame.tEndAngles.vZ);
  igi2_frame.iCount = 0;
  igi2_frame.tFakePos.vX = (ptStartPos->vX + ptEndPos->vX) * 0.5;
  igi2_frame.tFakePos.vY = (ptEndPos->vY + ptStartPos->vY) * 0.5;
  v18 = ptEndPos->vZ + ptStartPos->vZ;
  LODWORD(igi2_frame.v118) = ptSplineObjSegment->nAreas;
  v17 = LODWORD(igi2_frame.v118);
  ptSplineObjSegment->vLength = 0.0;
  igi2_frame.tFakePos.vZ = v18 * 0.5;
  igi2_frame.v1DivAreas = 1.0 / (double)SLODWORD(igi2_frame.v118);
  if ( v17 >= 0 )
  {
    while ( 1 )
    {
      igi2_frame.vT = (double)igi2_frame.iCount * igi2_frame.v1DivAreas;
      if ( isLinear )
        break;
      igi2_frame.iLOD = SLODWORD(igi2_frame.tEndAngles.vX);
      for ( igi2_frame.vStartAlpha = igi2_frame.tStartAngles.vX; igi2_frame.tEndAngles.vX - igi2_frame.vStartAlpha > 3.1415927410125732; igi2_frame.vStartAlpha = igi2_frame.vStartAlpha
                                                                                                + 6.2831854820251465 )
        ;
      if ( igi2_frame.tEndAngles.vX - igi2_frame.vStartAlpha < -3.1415927410125732 )
      {
        do
        {
          v27 = *(float *)&igi2_frame.iLOD + 6.2831854820251465;
          *(float *)&igi2_frame.iLOD = v27;
        }
        while ( v27 - igi2_frame.vStartAlpha < -3.1415927410125732 );
      }
      v28 = (float *)((char *)ptSplineObjSegment + 12 * igi2_frame.iCount);
      LODWORD(igi2_frame.v118) = v28;
      igi2_frame.v123 = igi2_frame.vT * igi2_frame.vT * igi2_frame.vT * igi2_frame.atChannel[0].vA
           + igi2_frame.atChannel[0].vB * (igi2_frame.vT * igi2_frame.vT)
           + igi2_frame.vT * igi2_frame.atChannel[0].vS1
           + igi2_frame.atChannel[0].vN1
           - igi2_frame.tFakePos.vX;
      v28[85] = igi2_frame.v123;
      igi2_frame.v125 = igi2_frame.vT * igi2_frame.vT * igi2_frame.vT * igi2_frame.atChannel[1].vA
           + igi2_frame.atChannel[1].vB * (igi2_frame.vT * igi2_frame.vT)
           + igi2_frame.atChannel[1].vS1 * igi2_frame.vT
           + igi2_frame.atChannel[1].vN1
           - igi2_frame.tFakePos.vY;
      v28[86] = igi2_frame.v125;
      LODWORD(igi2_frame.vLen) = &ptSplineObjSegment->atAreaPos[igi2_frame.iCount].vZ;
      igi2_frame.v124 = igi2_frame.vT * igi2_frame.vT * igi2_frame.vT * igi2_frame.atChannel[2].vA
           + igi2_frame.atChannel[2].vB * (igi2_frame.vT * igi2_frame.vT)
           + igi2_frame.atChannel[2].vS1 * igi2_frame.vT
           + igi2_frame.atChannel[2].vN1
           - igi2_frame.tFakePos.vZ;
      *(float *)LODWORD(igi2_frame.vLen) = igi2_frame.v124;
      if ( igi2_frame.iCount )
      {
        if ( igi2_frame.iCount == ptSplineObjSegment->nAreas )
        {
          v29 = igi2_frame.v123;
          qmemcpy(
            &ptSplineObjSegment->atAreaOrientation[igi2_frame.iCount],
            ptEndOrientation,
            sizeof(ptSplineObjSegment->atAreaOrientation[igi2_frame.iCount]));
          igi2_frame.v133 = v29 - *(float *)(LODWORD(igi2_frame.v118) + 328);
          v30 = igi2_frame.v124 - *(&ptSplineObjSegment->vEndX + 3 * igi2_frame.iCount);
          v31 = igi2_frame.v125 - *(float *)(LODWORD(igi2_frame.v118) + 332);
          igi2_frame.vLen = igi2_frame.v133;
          v26 = sqrt(v30 * v30 + v31 * v31 + igi2_frame.vLen * igi2_frame.vLen);
          *((float *)&ptSplineObjSegment->atAreaOrientation[20].nOps + igi2_frame.iCount) = v26;
        }
        else
        {
          v32 = igi2_frame.atChannel[0].vA * igi2_frame.vT * igi2_frame.vT * 3.0 + igi2_frame.atChannel[0].vB * igi2_frame.vT + igi2_frame.atChannel[0].vB * igi2_frame.vT + igi2_frame.atChannel[0].vS1;
          igi2_frame.ptSource.vX = v32;
          igi2_frame.ptSource.vY = igi2_frame.atChannel[1].vA * igi2_frame.vT * igi2_frame.vT * 3.0 + igi2_frame.atChannel[1].vB * igi2_frame.vT + igi2_frame.atChannel[1].vB * igi2_frame.vT + igi2_frame.atChannel[1].vS1;
          igi2_frame.ptSource.vZ = igi2_frame.atChannel[2].vA * igi2_frame.vT * igi2_frame.vT * 3.0 + igi2_frame.atChannel[2].vB * igi2_frame.vT + igi2_frame.atChannel[2].vB * igi2_frame.vT + igi2_frame.atChannel[2].vS1;
          if ( v32 == 0.0 && igi2_frame.ptSource.vY == 0.0 && igi2_frame.ptSource.vZ == 0.0 )
          {
            igi2_frame.tTempAngles.vY = 0.0;
            igi2_frame.tTempAngles.vZ = 0.0;
          }
          else
          {
            Real32x3_GetAngles(&igi2_frame.ptSource, &igi2_frame.tTempAngles.vY, &igi2_frame.tTempAngles.vZ);
            v28 = (float *)LODWORD(igi2_frame.v118);
          }
          igi2_frame.tTempAngles.vX = (*(float *)&igi2_frame.iLOD - igi2_frame.vStartAlpha) * igi2_frame.vT + igi2_frame.vStartAlpha;
          Real32x9_Create(
            &ptSplineObjSegment->atAreaOrientation[igi2_frame.iCount],
            igi2_frame.tTempAngles.vX,
            igi2_frame.tTempAngles.vY,
            igi2_frame.tTempAngles.vZ);
          igi2_frame.ptSource.vX = v28[85] - v28[82];
          v33 = *(float *)LODWORD(igi2_frame.vLen) - *(&ptSplineObjSegment->vEndX + 3 * igi2_frame.iCount);
          v34 = v28[86] - v28[83];
          igi2_frame.vLen = igi2_frame.ptSource.vX;
          v26 = sqrt(v33 * v33 + v34 * v34 + igi2_frame.vLen * igi2_frame.vLen);
          *((float *)&ptSplineObjSegment->atAreaOrientation[20].nOps + igi2_frame.iCount) = v26;
        }
LABEL_26:
        ptSplineObjSegment->vLength = v26 + ptSplineObjSegment->vLength;
        goto LABEL_27;
      }
      qmemcpy(ptSplineObjSegment->atAreaOrientation, ptStartOrientation, 0x28u);
LABEL_27:
      if ( ++igi2_frame.iCount > ptSplineObjSegment->nAreas )
      {
        v10 = ptStartPos;
        goto LABEL_29;
      }
    }
    v19 = igi2_frame.iCount;
    v20 = (float *)((char *)ptSplineObjSegment + 12 * igi2_frame.iCount);
    v21 = (ptEndPos->vX - ptStartPos->vX) * igi2_frame.vT + ptStartPos->vX;
    v22 = (ptEndPos->vY - ptStartPos->vY) * igi2_frame.vT + ptStartPos->vY;
    *(double *)&igi2_frame.tTempPos[16] = (ptEndPos->vZ - ptStartPos->vZ) * igi2_frame.vT + ptStartPos->vZ;
    v20[85] = v21 - igi2_frame.tFakePos.vX;
    v20[86] = v22 - igi2_frame.tFakePos.vY;
    ptSplineObjSegment->atAreaPos[igi2_frame.iCount].vZ = *(double *)&igi2_frame.tTempPos[16] - igi2_frame.tFakePos.vZ;
    v23 = (float *)(&ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask + igi2_frame.iCount);
    v23[148] = 0.0;
    v23[149] = 0.0;
    ptSplineObjSegment->atAreaOrientation[igi2_frame.iCount].tX.vZ = 0.0;
    v23[151] = 0.0;
    v23[152] = 0.0;
    v23[153] = 0.0;
    v23[154] = 0.0;
    v23[155] = 0.0;
    v23[156] = 0.0;
    v23[157] = 0.0;
    igi2_frame.tTempVector.vX = ptEndPos->vX - ptStartPos->vX;
    igi2_frame.tTempVector.vY = ptEndPos->vY - ptStartPos->vY;
    igi2_frame.tTempVector.vZ = ptEndPos->vZ - ptStartPos->vZ;
    if ( igi2_frame.tTempVector.vX == 0.0 && igi2_frame.tTempVector.vY == 0.0 && igi2_frame.tTempVector.vZ == 0.0 )
    {
      igi2_frame.pvGamma = 0.0;
    }
    else
    {
      Real32x3_GetAngles(&igi2_frame.tTempVector, &igi2_frame.pvBeta, &igi2_frame.pvGamma);
      v19 = igi2_frame.iCount;
    }
    v24 = sin(igi2_frame.pvGamma);
    v23[150] = 0.0;
    v23[153] = 0.0;
    v23[154] = 0.0;
    v23[155] = 0.0;
    v23[156] = 1.0;
    v23[157] = 0.0;
    v25 = cos(igi2_frame.pvGamma);
    v23[148] = v25;
    v23[149] = -v24;
    v23[151] = v24;
    v23[152] = v25;
    if ( v19 )
      goto LABEL_27;
    v26 = sqrt(igi2_frame.tTempVector.vX * igi2_frame.tTempVector.vX + igi2_frame.tTempVector.vY * igi2_frame.tTempVector.vY + igi2_frame.tTempVector.vZ * igi2_frame.tTempVector.vZ)
        * igi2_frame.v1DivAreas;
    ptSplineObjSegment->avAreaLength[0] = v26;
    goto LABEL_26;
  }
LABEL_29:
  ptSplineObjSegment->avAreaLength[ptSplineObjSegment->nAreas] = 0.0;
  LODVirModelExistsFn = MTP_GetLODVirModelExistsFn(zModel);
  if ( LODVirModelExistsFn
    && ((eRenderMeshType = LODVirModelExistsFn->aptVirModel[0]->ptModel->ptMesh->eRenderMeshType) == MESH3D_RENDERMESHTYPE_DIRECT3D_RIGID
     || eRenderMeshType == MESH3D_RENDERMESHTYPE_DIRECT3D_BUILDING) )
  {
    ptSplineObjSegment->tRigidDynCubeObj.tModelObj.ptLODVirModel = LODVirModelExistsFn;
    ptSplineObjSegment->vStartX = 0.0;
    ptSplineObjSegment->vEndX = 0.0;
    igi2_frame.iLODa = 0;
    if ( LODVirModelExistsFn->nLOD > 0 )
    {
      igi2_frame.iCounta = (int)LODVirModelExistsFn;
      do
      {
        v37 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)igi2_frame.iCounta + 12) + 12);
        v38 = *(_DWORD *)(v37 + 32);
        if ( v38 )
        {
          if ( v38 == 3 )
          {
            v42 = *(_DWORD *)(v37 + 36);
            v43 = *(float **)(v42 + 20);
            for ( i = 0; i < (int)(*(_DWORD *)(v42 + 16)); v43 += 7 )
            {
              if ( *v43 < (double)ptSplineObjSegment->vStartX )
                ptSplineObjSegment->vStartX = *v43;
              if ( *v43 > (double)ptSplineObjSegment->vEndX )
                ptSplineObjSegment->vEndX = *v43;
              ++i;
            }
          }
        }
        else
        {
          v39 = *(_DWORD *)(v37 + 36);
          v40 = *(float **)(v39 + 16);
          for ( j = 0; j < (int)(*(_DWORD *)(v39 + 12)); v40 += 8 )
          {
            if ( *v40 < (double)ptSplineObjSegment->vStartX )
              ptSplineObjSegment->vStartX = *v40;
            if ( *v40 > (double)ptSplineObjSegment->vEndX )
              ptSplineObjSegment->vEndX = *v40;
            ++j;
          }
        }
        igi2_frame.iCounta += 4;
        ++igi2_frame.iLODa;
      }
      while ( igi2_frame.iLODa < ptSplineObjSegment->tRigidDynCubeObj.tModelObj.ptLODVirModel->nLOD );
    }
    if ( ptSplineObjSegment->isLinear )
    {
      igi2_frame.iCountb = 1.0;
      if ( v10->vX != ptEndPos->vX || v10->vY != ptEndPos->vY || v10->vZ != ptEndPos->vZ )
      {
        v45 = ptEndPos->vX - v10->vX;
        *(float *)&igi2_frame.vLen = v45;
        *((float *)&igi2_frame.vLen + 1) = ptEndPos->vY - v10->vY;
        igi2_frame.v117 = ptEndPos->vZ - v10->vZ;
        if ( v45 == 0.0 && *((float *)&igi2_frame.vLen + 1) == 0.0 && igi2_frame.v117 == 0.0 )
        {
          *(_QWORD *)&igi2_frame.vLen = 1065353216;
          igi2_frame.v117 = 0.0;
        }
        v46 = ptSplineObjSegment->atAreaOrientation[0].tZ.vX;
        v47 = ptSplineObjSegment->vEndX - ptSplineObjSegment->vStartX;
        v48 = ptSplineObjSegment->atAreaOrientation[0].tY.vX;
        *(float *)igi2_frame.tTempPos = ptSplineObjSegment->atAreaOrientation[0].tX.vX;
        vY = ptSplineObjSegment->atAreaOrientation[0].tX.vY;
        v50 = 1.0 / v47;
        *(float *)&igi2_frame.tTempPos[4] = v48;
        v51 = ptSplineObjSegment->atAreaOrientation[0].tY.vY;
        *(float *)&igi2_frame.tTempPos[8] = v46;
        v52 = ptSplineObjSegment->atAreaOrientation[0].tZ.vY;
        *(float *)&igi2_frame.tTempPos[12] = vY;
        vZ = ptSplineObjSegment->atAreaOrientation[0].tX.vZ;
        *(float *)&igi2_frame.tTempPos[16] = v51;
        v54 = ptSplineObjSegment->atAreaOrientation[0].tY.vZ;
        *(float *)&igi2_frame.tTempPos[20] = v52;
        v55 = ptSplineObjSegment->atAreaOrientation[0].tZ.vZ;
        *(float *)&igi2_frame.tTempPos[24] = vZ;
        nOps = ptSplineObjSegment->atAreaOrientation[0].nOps;
        *(float *)&igi2_frame.tTempPos[28] = v54;
        *(float *)&igi2_frame.tTempPos[32] = v55;
        p_tOrientation = &ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation;
        *(_DWORD *)&igi2_frame.tTempPos[36] = nOps;
        qmemcpy(
          &ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation,
          igi2_frame.tTempPos,
          sizeof(ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation));
        *(double *)&ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tX.vX = igi2_frame.vLen;
        ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tX.vZ = igi2_frame.v117;
        LOBYTE(nOps) = ptSplineObjSegment->isFlip;
        *(float *)&igi2_frame.vLen = v50 * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tX.vX;
        ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tX.vX = *(float *)&igi2_frame.vLen;
        *(float *)&igi2_frame.v118 = v50 * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tX.vY;
        ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tX.vY = *(float *)&igi2_frame.v118;
        v58 = v50 * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tX.vZ;
        ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tX.vZ = v58;
        if ( (_BYTE)nOps )
        {
          p_tOrientation->tX.vX = -*(float *)&igi2_frame.vLen;
          ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tX.vY = -*(float *)&igi2_frame.v118;
          ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tX.vZ = -v58;
        }
        v59 = ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tY.vX;
        *(float *)igi2_frame.tTempPos = p_tOrientation->tX.vX;
        v60 = ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vX;
        *(float *)&igi2_frame.tTempPos[4] = v59;
        v61 = ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tX.vY;
        *(float *)&igi2_frame.tTempPos[8] = v60;
        v62 = ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tY.vY;
        *(float *)&igi2_frame.tTempPos[12] = v61;
        v63 = ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vY;
        *(float *)&igi2_frame.tTempPos[16] = v62;
        v64 = ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tX.vZ;
        *(float *)&igi2_frame.tTempPos[20] = v63;
        v65 = ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tY.vZ;
        *(float *)&igi2_frame.tTempPos[24] = v64;
        v66 = ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vZ;
        *(float *)&igi2_frame.tTempPos[28] = v65;
        v67 = ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.nOps;
        *(float *)&igi2_frame.tTempPos[32] = v66;
        *(_DWORD *)&igi2_frame.tTempPos[36] = v67;
        qmemcpy(p_tOrientation, igi2_frame.tTempPos, sizeof(struct real32x9_t));
        v68 = sqrt(
                p_tOrientation->tX.vX * p_tOrientation->tX.vX
              + ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tX.vY
              * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tX.vY
              + ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tX.vZ
              * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tX.vZ);
        igi2_frame.tEndAngles.vY = sqrt(
                          ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tY.vX
                        * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tY.vX
                        + ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tY.vY
                        * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tY.vY
                        + ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tY.vZ
                        * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tY.vZ);
        igi2_frame.tEndAngles.vZ = sqrt(
                          ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vX
                        * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vX
                        + ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vY
                        * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vY
                        + ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vZ
                        * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vZ);
        igi2_frame.iCountb = v68;
        if ( v68 < igi2_frame.tEndAngles.vY )
          igi2_frame.iCountb = igi2_frame.tEndAngles.vY;
        if ( igi2_frame.iCountb < (double)igi2_frame.tEndAngles.vZ )
          igi2_frame.iCountb = igi2_frame.tEndAngles.vZ;
        v69 = p_tOrientation->tX.vX;
        v70 = ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vX;
        v71 = ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tY.vX;
        *(float *)igi2_frame.tTempPos = v69;
        v72 = ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tX.vY;
        *(float *)&igi2_frame.tTempPos[8] = v70;
        v73 = ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vY;
        *(float *)&igi2_frame.tTempPos[12] = v72;
        v74 = ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tX.vZ;
        *(float *)&igi2_frame.tTempPos[4] = v71;
        v75 = ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tY.vY;
        *(float *)&igi2_frame.tTempPos[20] = v73;
        v76 = ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vZ;
        *(float *)&igi2_frame.tTempPos[24] = v74;
        v77 = ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.nOps;
        *(float *)&igi2_frame.tTempPos[16] = v75;
        v78 = ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tY.vZ;
        *(float *)&igi2_frame.tTempPos[32] = v76;
        *(_DWORD *)&igi2_frame.tTempPos[36] = v77;
        *(float *)&igi2_frame.tTempPos[28] = v78;
        qmemcpy(&ptSplineObjSegment->atAreaOrientation[20], igi2_frame.tTempPos, sizeof(ptSplineObjSegment->atAreaOrientation[20]));
        Real32x9_InvertSafe(&ptSplineObjSegment->atAreaOrientation[20], &ptSplineObjSegment->atAreaOrientation[20]);
      }
      ptLODVirModel = ptSplineObjSegment->tRigidDynCubeObj.tModelObj.ptLODVirModel;
      vRadius = 0.0;
      if ( ptLODVirModel->nLOD > 0 )
      {
        nLOD = ptLODVirModel->nLOD;
        do
        {
          ptMesh = ptLODVirModel->aptVirModel[0]->ptModel->ptMesh;
          if ( vRadius < ptMesh->vRadius )
            vRadius = ptMesh->vRadius;
          ptLODVirModel = (struct LODVirModel_s *)((char *)ptLODVirModel + 4);
          --nLOD;
        }
        while ( nLOD );
      }
      igi2_frame.iCountc = vRadius * igi2_frame.iCountb * 1.100000023841858;
      World_MoveDynCubeObjRadius(
        ptSplineObjSegment->ptWorld,
        &ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj,
        &igi2_frame.tFakePos,
        igi2_frame.iCountc);
    }
    else
    {
      igi2_frame.iCountc = 0.0;
      for ( k = 0; k < 2; ++k )
      {
        SplineMultiMeshVertexList = Mesh3D_GetSplineMultiMeshVertexList(ptSplineObjSegment, 0, k, 1, 0, (int *)&igi2_frame.vLen);
        v85 = LODWORD(igi2_frame.vLen);
        if ( SLODWORD(igi2_frame.vLen) > 0 )
        {
          p_vZ = &SplineMultiMeshVertexList->vZ;
          v87 = igi2_frame.tFakePos.vX - v10->vX;
          v88 = igi2_frame.tFakePos.vY - v10->vY;
          v89 = igi2_frame.tFakePos.vZ - v10->vZ;
          do
          {
            igi2_frame.tStartAngles.vY = v88;
            igi2_frame.tStartAngles.vZ = v89;
            v90 = v87 + *(p_vZ - 2);
            v91 = igi2_frame.tStartAngles.vY + *(p_vZ - 1);
            igi2_frame.v118 = igi2_frame.tStartAngles.vZ + *p_vZ;
            v92 = sqrt(v90 * v90 + v91 * v91 + igi2_frame.v118 * igi2_frame.v118);
            if ( igi2_frame.iCountc <= v92 )
              igi2_frame.iCountc = v92;
            p_vZ += 3;
            --v85;
          }
          while ( v85 );
        }
        if ( igi2_frame.iCountc <= 1.0 )
          igi2_frame.iCountc = 1.0;
      }
      World_MoveDynCubeObjRadius(
        ptSplineObjSegment->ptWorld,
        &ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj,
        &igi2_frame.tFakePos,
        igi2_frame.iCountc);
    }
    ptSplineObjSegment->vRadius = igi2_frame.iCountc;
    v93 = 0;
    while ( ptSplineObjSegment != (struct SplineObjSegment_s *)Mesh3D_aptPreCalcObj[v93] )
    {
      if ( ++v93 >= 1 )
        goto LABEL_86;
    }
    Mesh3D_aptPreCalcObj[v93] = nullptr;
    Mesh3D_aiPreCalcObjLOD[v93] = 0;
LABEL_86:
    if ( ptSplineObjSegment->ptCollSphereModel == ptSplineObjSegment->tRigidDynCubeObj.tModelObj.ptLODVirModel
      && !isLinear )
    {
      goto LABEL_104;
    }
    igi2_frame.iLODb = ptSplineObjSegment->atSphereTree;
    LODWORD(igi2_frame.v118) = 2;
    do
    {
      if ( igi2_frame.iLODb->ptSphere )
      {
        v94 = *(_DWORD *)((int)&igi2_frame.iLODb->ptSphere[-1].iChild & 0xFFFFFFFC);
        --Mem_nCurrentAllocations;
        Node_Remove((_DWORD **)v94);
        memset(*(void **)(v94 + 8), 0xCDu, *(_DWORD *)(v94 + 16));
        free((void *)v94);
        igi2_frame.iLODb->ptSphere = nullptr;
      }
      v95 = LODWORD(igi2_frame.v118) == 1;
      ++igi2_frame.iLODb;
      --LODWORD(igi2_frame.v118);
    }
    while ( !v95 );
    if ( !isLinear )
    {
LABEL_104:
      if ( ptSplineObjSegment->tRigidDynCubeObj.tModelObj.ptLODVirModel )
      {
        v96 = ptSplineObjSegment->tRigidDynCubeObj.iCollisionLOD;
        v97 = 0;
        atSphereTree = ptSplineObjSegment->atSphereTree;
        igi2_frame.iLODc = v96;
        igi2_frame.vStartAlphaa = 0;
        LODWORD(igi2_frame.v118) = 0;
        igi2_frame.iCountd = ptSplineObjSegment->atSphereTree;
        do
        {
          pxCollisionMesh = (char *)ptSplineObjSegment->tRigidDynCubeObj.tModelObj.ptLODVirModel->aptVirModel[v96]->ptModel->ptMesh->pxCollisionMesh;
          v100 = *(_DWORD *)&pxCollisionMesh[v97 + 12];
          v101 = (struct MultiMesh_Mesh_t *)&pxCollisionMesh[v97];
          SplineObjSegment_ptActiveMesh = v101;
          if ( v100 )
          {
            SplineObjSegment_ptActiveVertexList = Mesh3D_GetSplineMultiMeshVertexList(
                                                    ptSplineObjSegment,
                                                    v96,
                                                    igi2_frame.vStartAlphaa,
                                                    1,
                                                    0,
                                                    nullptr);
            if ( !atSphereTree->ptSphere )
            {
              nNumSpheres = v101->nNumSpheres;
              atSphereTree->nNumSpheres = nNumSpheres;
              v103 = (struct MultiMesh_Sphere_t *)Mem_AllocFn(24 * nNumSpheres, 4);
              v101 = SplineObjSegment_ptActiveMesh;
              atSphereTree->ptSphere = v103;
            }
            qmemcpy(igi2_frame.iCountd->ptSphere, v101->ptSphere, 24 * igi2_frame.iCountd->nNumSpheres);
            SplineObjSegment_ptActiveSphereTree = igi2_frame.iCountd;
            SplineObjSegment_TransformSpherePos(ptSplineObjSegment, igi2_frame.iCountd);
            SplineObjSegment_aptNewSphere[0] = igi2_frame.iCountd->ptSphere;
            SplineObjSegment_nNewSphere = 0;
            SplineObjSegment_CreateSphere();
            atSphereTree = igi2_frame.iCountd;
            v97 = LODWORD(igi2_frame.v118);
            v96 = igi2_frame.iLODc;
          }
          v97 += 32;
          ++atSphereTree;
          ++igi2_frame.vStartAlphaa;
          igi2_frame.iCountd = atSphereTree;
          LODWORD(igi2_frame.v118) = v97;
        }
        while ( v97 < 64 );
      }
    }
    ptSplineObjSegment->ptCollSphereModel = ptSplineObjSegment->tRigidDynCubeObj.tModelObj.ptLODVirModel;
  }
  else
  {
    ptSplineObjSegment->tRigidDynCubeObj.tModelObj.ptLODVirModel = nullptr;
  }
}

// source: e/3/splineobjsegment.c:3605  [size]
void __cdecl SplineObjSegment_Delete(struct SplineObjSegment_s *ptSplineObjSegment)
{
  QTask_Delete(&ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask);
}

// source: e/3/splineobjsegment.c:3619  [size]
unsigned __int16 __cdecl SplineObjSegment_GetTaskType()
{
  return SplineObjSegment_eQTaskType;
}
