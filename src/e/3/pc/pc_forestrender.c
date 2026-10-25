/* e/3/pc/pc_forestrender.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: e/3/pc/pc_forestrender.c:285  [size]
void __cdecl ForestRender_CreateBSPModel(
        struct DrawForestContext_t *ptContext,
        struct LODVirModel_s *ptLODVirModel,
        struct ForestRender_BSPTree_t **pptBSPTree)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct ForestRender_BSPNode_s **v52; };
    struct { char igi2_o1[4]; int iFaceGroup; };
    struct { char igi2_o2[4]; struct Mesh3D_MorphVertex_t *iFaceGroupa; };
    struct { char igi2_o3[4]; int iFaceGroupb; };
    struct { char igi2_o4[8]; struct LODVirModel_s *v56; };
    struct { char igi2_o5[12]; int iModel; };
    struct { char igi2_o6[16]; struct real32x3_t *p_tDelta; };
    struct { char igi2_o7[20]; char *iChannel; };
    struct { char igi2_o8[20]; int iChannela; };
    struct { char igi2_o9[24]; int iLOD; };
    struct { char igi2_o10[28]; int v62; };
    struct { char igi2_o11[32]; int iFace; };
    struct { char igi2_o12[32]; int iFacea; };
    struct { char igi2_o13[32]; int iFaceb; };
    struct { char igi2_o14[36]; struct Mesh3D_RenderMesh_RigidDirect3D_t *ptRenderMesh; };
    struct { char igi2_o15[40]; int nNumVertices; };
    struct { char igi2_o16[40]; int nNumVerticesa; };
    struct { char igi2_o17[44]; struct QObjectVector_s *aptMorphFaceGroups[2]; };
    struct { char igi2_o18[52]; struct real32x3_t tAveragePos; };
    char igi2_extent[64];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v3; // ebx
  int v4; // ecx
  struct ForestRender_BSPLODModel_t *atBSPModels; // esi
  struct LODVirModel_s *v6; // edx
  struct ForestRender_BSPNode_s **p_ptBSPTree; // eax
  struct Mesh3D_RenderMesh_RigidDirect3D_t *pxRenderMesh; // ebp
  unsigned int v9; // edi
  struct QObjectVector_s *v10; // esi
  struct MemPoolSegment_s *v11; // ebx
  int v12; // eax
  unsigned int v13; // ecx
  struct MemPoolFreeItem_s *v14; // eax
  struct Mesh3D_Morph_t *ptMorph; // eax
  struct Mesh3D_MorphVertex_t *atMorphVertices; // ebx
  int v17; // ecx
  int nNumFaceGroups; // edi
  int iIndex; // edx
  int v20; // esi
  unsigned __int16 *p_iStartVertex; // eax
  int v22; // ecx
  struct QObjectVector_s *v23; // edi
  unsigned int nAllocated; // eax
  int *v25; // ecx
  bool v26; // zf
  void **v27; // esi
  struct QObjectVector_s *v28; // ebx
  int v29; // edi
  int v30; // eax
  int v31; // ecx
  _DWORD *v32; // edx
  _DWORD *v33; // edi
  int v34; // eax
  int v35; // ebx
  int v36; // edi
  struct RigidDirect3D_FaceGroup_t *ptFaceGroup; // ecx
  int v38; // edi
  int v39; // esi
  int v40; // edx
  int piIndex; // ecx
  int v42; // eax
  struct Direct3DRender_XYZNormalTex1Vertex_t *ptVertex; // ebp
  float *p_vX; // ecx
  float *v45; // eax
  double v46; // st7
  float *v47; // edx
  double v48; // st6
  double v49; // st7
  float *v50; // ecx
  bool v51; // cc

  v3 = 0;
  v4 = 0;
  igi2_frame.iModel = 0;
  if ( tBSPStorage.nNumModels <= 0 )
  {
    v6 = ptLODVirModel;
  }
  else
  {
    atBSPModels = tBSPStorage.atBSPModels;
    do
    {
      v6 = ptLODVirModel;
      if ( atBSPModels->ptLODVirModel == ptLODVirModel )
        break;
      ++v4;
      ++atBSPModels;
    }
    while ( v4 < tBSPStorage.nNumModels );
    igi2_frame.iModel = v4;
  }
  if ( v4 == tBSPStorage.nNumModels )
  {
    if ( tBSPStorage.nNumModels >= 20 )
    {
      LDebug_Error("Forest renderer: BSP storage full");
      abort();
    }
    tBSPStorage.atBSPModels[v4].ptLODVirModel = v6;
    ++tBSPStorage.nNumModels;
    igi2_frame.iLOD = 0;
    if ( v6->nLOD > 0 )
    {
      p_ptBSPTree = &tBSPStorage.atBSPModels[v4].atLOD[0].ptBSPTree;
      igi2_frame.v62 = 0;
      igi2_frame.v56 = v6;
      igi2_frame.v52 = p_ptBSPTree;
      while ( 1 )
      {
        *(p_ptBSPTree - 2) = nullptr;
        *(p_ptBSPTree - 1) = (struct ForestRender_BSPNode_s *)-1;
        *p_ptBSPTree = nullptr;
        pxRenderMesh = (struct Mesh3D_RenderMesh_RigidDirect3D_t *)igi2_frame.v56->aptVirModel[0]->ptModel->ptMesh->pxRenderMesh;
        igi2_frame.ptRenderMesh = pxRenderMesh;
        igi2_frame.iFaceGroup = 0;
        igi2_frame.iChannel = (char *)(p_ptBSPTree + 3);
        do
        {
          v9 = pxRenderMesh->nNumVertices;
          v10 = (struct QObjectVector_s *)Mem_AllocFn(52, 4);
          v10->isStrictOrder = false;
          v10->nSize = 0;
          v10->nAllocated = 0;
          v10->nReallocSize = 1;
          v10->papxElement = nullptr;
          v10->nElementSize = 20;
          v10->tMemPool.nBlocks = 0;
          v10->tMemPool.nAllocatedBlocks = 0;
          v10->tMemPool.nAlignment = 4;
          v10->tMemPool.nBlockSize = 20;
          v10->tMemPool.nReAllocBlocks = 1;
          v10->tMemPool.tMemPoolFreeList.ptHead = nullptr;
          v10->tMemPool.tMemPoolSegmentList.ptHead = nullptr;
          if ( v9 )
          {
            v11 = (struct MemPoolSegment_s *)Mem_AllocFn(12, 4);
            v12 = v9 * v10->tMemPool.nBlockSize;
            v11->nByteSize = v12;
            v11->pxData = Mem_AllocFn(v12, v10->tMemPool.nAlignment);
            v11->ptNext = v10->tMemPool.tMemPoolSegmentList.ptHead;
            v10->tMemPool.nBlocks += v9;
            v13 = 0;
            v10->tMemPool.tMemPoolSegmentList.ptHead = v11;
            do
            {
              v14 = (struct MemPoolFreeItem_s *)((char *)v11->pxData + v13 * v10->tMemPool.nBlockSize);
              ++v13;
              v14->ptNext = v10->tMemPool.tMemPoolFreeList.ptHead;
              v10->tMemPool.tMemPoolFreeList.ptHead = v14;
            }
            while ( v13 < v9 );
            QObjectVector_Realloc(v10, v9);
            v3 = igi2_frame.iFaceGroup;
          }
          igi2_frame.aptMorphFaceGroups[v3++] = v10;
          memset(igi2_frame.iChannel, 0, 0x40u);
          igi2_frame.iFaceGroup = v3;
          igi2_frame.iChannel += 68;
        }
        while ( v3 < 2 );
        ptMorph = igi2_frame.v56->aptVirModel[0]->ptModel->ptMesh->ptMorph;
        if ( ptMorph && ptContext->nWindLODs > igi2_frame.iLOD && ForestRender_isWind )
        {
          atMorphVertices = ptMorph->atMorphVertices;
          v17 = 0;
          igi2_frame.iFaceGroupa = ptMorph->atMorphVertices;
          igi2_frame.iChannela = 0;
          do
          {
            if ( igi2_frame.v56->aptVirModel[0]->ptModel->ptMesh->ptMorph->anMorphChannelVertices[v17] > 0 )
            {
              igi2_frame.p_tDelta = &atMorphVertices->tDelta;
              igi2_frame.iFace = igi2_frame.v56->aptVirModel[0]->ptModel->ptMesh->ptMorph->anMorphChannelVertices[v17];
              do
              {
                nNumFaceGroups = pxRenderMesh->nNumFaceGroups;
                iIndex = atMorphVertices->iIndex;
                v20 = 0;
                if ( nNumFaceGroups > 0 )
                {
                  p_iStartVertex = &pxRenderMesh->ptFaceGroup->iStartVertex;
                  while ( 1 )
                  {
                    v22 = *p_iStartVertex;
                    if ( iIndex >= v22 && iIndex < v22 + p_iStartVertex[1] )
                      break;
                    ++v20;
                    p_iStartVertex += 16;
                    if ( v20 >= nNumFaceGroups )
                    {
                      atMorphVertices = igi2_frame.iFaceGroupa;
                      goto LABEL_34;
                    }
                  }
                  v23 = igi2_frame.aptMorphFaceGroups[v20];
                  if ( v23->nAllocated == v23->nSize )
                    QObjectVector_Realloc(igi2_frame.aptMorphFaceGroups[v20], v23->nReallocSize);
                  nAllocated = v23->nAllocated;
                  v25 = (int *)v23->papxElement[nAllocated];
                  atMorphVertices = igi2_frame.iFaceGroupa;
                  v23->nAllocated = nAllocated + 1;
                  *v25++ = igi2_frame.iFaceGroupa->iIndex - pxRenderMesh->ptFaceGroup[v20].iStartVertex;
                  *v25 = LODWORD(igi2_frame.p_tDelta->vX);
                  v25[1] = LODWORD(igi2_frame.p_tDelta->vY);
                  v25[2] = LODWORD(igi2_frame.p_tDelta->vZ);
                  ++tBSPStorage.atBSPModels[igi2_frame.iModel].atLOD[0].atMorphFaceGroups[v20].anMorphChannelVertices[igi2_frame.iChannela + igi2_frame.v62];
                }
LABEL_34:
                ++atMorphVertices;
                v26 = igi2_frame.iFace == 1;
                igi2_frame.iFaceGroupa = atMorphVertices;
                igi2_frame.p_tDelta = (struct real32x3_t *)((char *)igi2_frame.p_tDelta + 16);
                --igi2_frame.iFace;
              }
              while ( !v26 );
              v17 = igi2_frame.iChannela;
            }
            igi2_frame.iChannela = ++v17;
          }
          while ( v17 < 16 );
        }
        igi2_frame.iFaceGroupb = 0;
        v27 = (void **)(igi2_frame.v52 + 19);
        do
        {
          v28 = igi2_frame.aptMorphFaceGroups[igi2_frame.iFaceGroupb];
          v29 = v28->nAllocated;
          igi2_frame.iFacea = (int)v28;
          igi2_frame.nNumVertices = v29;
          if ( v29 <= 0 )
          {
            *v27 = nullptr;
          }
          else
          {
            *v27 = Mem_AllocFn(16 * v29, 4);
            v30 = 0;
            v31 = 0;
            do
            {
              v32 = v28->papxElement[v30];
              *(_DWORD *)((char *)*v27 + v31) = *v32++;
              v33 = (char *)*v27 + v31 + 4;
              *v33 = *v32;
              v33[1] = v32[1];
              v28 = (struct QObjectVector_s *)igi2_frame.iFacea;
              v33[2] = v32[2];
              ++v30;
              v31 += 16;
            }
            while ( v30 < igi2_frame.nNumVertices );
          }
          QObjectVector_Delete(v28);
          v27 += 17;
          ++igi2_frame.iFaceGroupb;
        }
        while ( igi2_frame.iFaceGroupb < 2 );
        v34 = pxRenderMesh->nNumFaceGroups;
        v35 = 0;
        v36 = 0;
        if ( v34 > 0 )
        {
          ptFaceGroup = pxRenderMesh->ptFaceGroup;
          do
          {
            if ( (ptFaceGroup->bMaterialProperties & 2) != 0 )
              break;
            ++v36;
            ++ptFaceGroup;
          }
          while ( v36 < v34 );
        }
        if ( v36 < v34 )
        {
          *(igi2_frame.v52 - 1) = (struct ForestRender_BSPNode_s *)v36;
          v38 = (int)&pxRenderMesh->ptFaceGroup[v36];
          igi2_frame.v52[1] = (struct ForestRender_BSPNode_s *)Mem_AllocFn(28 * *(unsigned __int16 *)(v38 + 18), 4);
          igi2_frame.v52[2] = (struct ForestRender_BSPNode_s *)Mem_AllocFn(4 * *(unsigned __int16 *)(v38 + 18), 4);
          igi2_frame.iFaceb = 0;
          if ( *(_WORD *)(v38 + 18) )
          {
            v39 = 0;
            while ( 1 )
            {
              *(struct QObjectVector_s **)((char *)&igi2_frame.v52[1]->ptFaces + v39 * 4) = (struct QObjectVector_s *)pxRenderMesh->piIndex[v35 + *(unsigned __int16 *)(v38 + 16)];
              LODWORD(igi2_frame.v52[1]->tPlane.avCoeffs[v39]) = pxRenderMesh->piIndex[v35 + 1 + *(unsigned __int16 *)(v38 + 16)];
              LODWORD(igi2_frame.v52[1]->tPlane.avCoeffs[v39 + 1]) = pxRenderMesh->piIndex[v35
                                                                              + 2
                                                                              + *(unsigned __int16 *)(v38 + 16)];
              v40 = *(unsigned __int16 *)(v38 + 16) + v35;
              piIndex = (int)pxRenderMesh->piIndex;
              v42 = *(unsigned __int16 *)(piIndex + 2 * v40);
              ptVertex = pxRenderMesh->ptVertex;
              igi2_frame.nNumVerticesa = piIndex;
              p_vX = &ptVertex[*(unsigned __int16 *)(piIndex + 2 * v40 + 2)].tPos.vX;
              v45 = &ptVertex[v42].tPos.vX;
              v46 = (*p_vX + *v45) * 0.5;
              v47 = &igi2_frame.ptRenderMesh->ptVertex[*(unsigned __int16 *)(igi2_frame.nNumVerticesa + 2 * v40 + 4)].tPos.vX;
              v35 += 3;
              v48 = (p_vX[1] + v45[1]) * 0.5;
              igi2_frame.tAveragePos.vZ = (p_vX[2] + v45[2]) * 0.5;
              igi2_frame.tAveragePos.vX = (v46 + *v47) * 0.5;
              igi2_frame.tAveragePos.vY = (v48 + v47[1]) * 0.5;
              v49 = igi2_frame.tAveragePos.vZ + v47[2];
              v50 = &igi2_frame.v52[1]->tPlane.avCoeffs[v39 + 2];
              *v50 = igi2_frame.tAveragePos.vX;
              v50[1] = igi2_frame.tAveragePos.vY;
              igi2_frame.tAveragePos.vZ = v49 * 0.5;
              v50[2] = igi2_frame.tAveragePos.vZ;
              *((_DWORD *)&igi2_frame.v52[2]->ptFaces + igi2_frame.iFaceb++) = (char *)igi2_frame.v52[1] + v39 * 4;
              v39 += 7;
              if ( igi2_frame.iFaceb >= *(unsigned __int16 *)(v38 + 18) )
                break;
              pxRenderMesh = igi2_frame.ptRenderMesh;
            }
          }
        }
        else
        {
          *(igi2_frame.v52 - 1) = (struct ForestRender_BSPNode_s *)-1;
        }
        v51 = ++igi2_frame.iLOD < ptLODVirModel->nLOD;
        igi2_frame.v56 = (struct LODVirModel_s *)((char *)igi2_frame.v56 + 4);
        igi2_frame.v62 += 39;
        igi2_frame.v52 += 39;
        if ( !v51 )
          break;
        p_ptBSPTree = igi2_frame.v52;
        v3 = 0;
      }
      v4 = igi2_frame.iModel;
    }
  }
  *pptBSPTree = (struct ForestRender_BSPTree_t *)(784 * v4 + 129448824);
}

// source: e/3/pc/pc_forestrender.c:462  [size]
void __cdecl ForestRender_GetLOD(
        struct ModelObj_s *ptModelObj,
        float vMorphRatio,
        int *piLOD,
        int *piMorphLOD,
        float *pvMorphFactor)
{
  struct LODVirModel_s *ptLODVirModel; // edx
  double vFOVX; // st7
  float *p_vVersion; // eax
  double v8; // st6
  double v9; // st5
  double vY; // st7
  double vZ; // st7
  int nLOD; // edi
  double v13; // st7
  int v14; // edi
  int v15; // esi
  int v16; // ecx
  float *avLODDistance; // ebx
  double v18; // st7
  double v19; // st7
  double v20; // st6
  double v21; // st6
  float vDistanceWithFOVX; // [esp+4h] [ebp-18h]
  float vDistanceWithFOVXa; // [esp+4h] [ebp-18h]
  float vDistanceWithFOVXSquared; // [esp+8h] [ebp-14h]
  float vDistanceWithFOVXSquareda; // [esp+8h] [ebp-14h]
  float vDistanceWithFOVXSquaredb; // [esp+8h] [ebp-14h]
  float vRadiusb; // [esp+Ch] [ebp-10h]
  float vRadius; // [esp+Ch] [ebp-10h]
  float vRadiusa; // [esp+Ch] [ebp-10h]
  float tPos; // [esp+10h] [ebp-Ch]
  float tPos_8; // [esp+18h] [ebp-4h]

  ptLODVirModel = ptModelObj->ptLODVirModel;
  if ( ptLODVirModel )
  {
    if ( TransContext_tActiveTransContext.vFOVX >= 1.0 )
      vFOVX = 1.0;
    else
      vFOVX = ForestRender_ptTransContext->vFOVX;
    tPos_8 = ptModelObj->tDynCubeObj.tQObj.tPos.vZ - ForestRender_ptTransContext->tPos.vZ;
    p_vVersion = &ptLODVirModel->aptVirModel[0]->ptModel->ptMesh->vVersion;
    tPos = ptModelObj->tDynCubeObj.tQObj.tPos.vX - ForestRender_ptTransContext->tPos.vX + p_vVersion[12];
    v8 = ptModelObj->tDynCubeObj.tQObj.tPos.vY - ForestRender_ptTransContext->tPos.vY + p_vVersion[13];
    v9 = tPos_8 + p_vVersion[14];
    vDistanceWithFOVXSquared = (v9 * v9 + v8 * v8 + tPos * tPos) * g_ptRotationMatrix.tY.vX * vFOVX * vFOVX;
    if ( ptModelObj->tScale.vX <= (double)ptModelObj->tScale.vY )
      vY = ptModelObj->tScale.vY;
    else
      vY = ptModelObj->tScale.vX;
    if ( vY <= ptModelObj->tScale.vZ )
    {
      vZ = ptModelObj->tScale.vZ;
    }
    else if ( ptModelObj->tScale.vX <= (double)ptModelObj->tScale.vY )
    {
      vZ = ptModelObj->tScale.vY;
    }
    else
    {
      vZ = ptModelObj->tScale.vX;
    }
    nLOD = ptLODVirModel->nLOD;
    if ( ptLODVirModel->isLODDistanceSpecified )
    {
      *piLOD = -1;
      vDistanceWithFOVX = sqrt(vDistanceWithFOVXSquared);
      if ( nLOD <= 1 )
        vRadiusa = 0.0;
      else
        vRadiusa = vZ * ptLODVirModel->avLODDistance[0] * vMorphRatio;
      v15 = nLOD - 1;
      v16 = 0;
      if ( nLOD - 1 <= 0 )
      {
LABEL_28:
        vDistanceWithFOVXSquaredb = vZ * ptLODVirModel->avLODDistance[4];
        if ( nLOD <= 1 )
          v18 = 0.0;
        else
          v18 = vZ * (ptLODVirModel->avLODDistance[4] - ptLODVirModel->avLODDistance[3]) * vMorphRatio;
        v20 = ForestRender_vLODBiasInversed * vDistanceWithFOVX;
        vDistanceWithFOVXa = v20;
        if ( v20 >= vDistanceWithFOVXSquaredb )
        {
          *piLOD = -1;
        }
        else
        {
          v21 = vDistanceWithFOVXSquaredb - v18;
          *piLOD = v15;
          *piMorphLOD = -1;
          if ( vDistanceWithFOVXa <= v21 )
            *pvMorphFactor = 0.0;
          else
            *pvMorphFactor = (vDistanceWithFOVXa - v21) / v18;
        }
      }
      else
      {
        avLODDistance = ptLODVirModel->avLODDistance;
        while ( 1 )
        {
          vDistanceWithFOVXSquareda = vZ * *avLODDistance;
          if ( vDistanceWithFOVX < (double)vDistanceWithFOVXSquareda )
            break;
          ++v16;
          ++avLODDistance;
          if ( v16 >= v15 )
            goto LABEL_28;
        }
        *piLOD = v16;
        v19 = vDistanceWithFOVXSquareda - vRadiusa;
        if ( vDistanceWithFOVX <= v19 )
        {
          *piMorphLOD = -1;
          *pvMorphFactor = 0.0;
        }
        else
        {
          *pvMorphFactor = (vDistanceWithFOVX - v19) / vRadiusa;
          *piMorphLOD = v16 + 1;
        }
      }
    }
    else
    {
      v13 = vZ * p_vVersion[15] * Mesh3D_vRigidObjCutoff;
      if ( v13 * v13 >= vDistanceWithFOVXSquared )
      {
        v14 = nLOD - 1;
        vRadiusb = v13;
        for ( vRadius = vRadiusb / (double)ptLODVirModel->nLOD; v14; --v14 )
        {
          v13 = v13 - vRadius;
          if ( v13 * v13 < vDistanceWithFOVXSquared )
            break;
        }
        *piLOD = v14;
        *piMorphLOD = -1;
        *pvMorphFactor = 0.0;
      }
      else
      {
        *piLOD = 1;
        *piMorphLOD = -1;
        *pvMorphFactor = 0.0;
      }
    }
  }
  else
  {
    *piLOD = 0;
  }
}

// source: e/3/pc/pc_forestrender.c:590  [size]
void __cdecl ForestRender_SetTextureState_Trunk(void *pxContext)
{
  Direct3DRender_SetTextureStageFilteringMode(0);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ADDRESSU, 1u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ADDRESSV, 1u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_TEXCOORDINDEX, 0);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_TEXTURETRANSFORMFLAGS, 0);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAOP, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAARG1, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAARG2, 0);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLOROP, 4u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLORARG1, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLORARG2, 0);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_COLOROP, 1u);
}

// source: e/3/pc/pc_forestrender.c:619  [size]
void __cdecl ForestRender_SetTextureState_AlphaBlendFoliage(void *pxContext)
{
  Direct3DRender_SetTextureStageFilteringMode(0);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ADDRESSU, 1u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ADDRESSV, 1u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_TEXCOORDINDEX, 0);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_TEXTURETRANSFORMFLAGS, 0);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAOP, 4u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAARG1, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAARG2, 0);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLOROP, 5u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLORARG1, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLORARG2, 0);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_COLOROP, 1u);
}

// source: e/3/pc/pc_forestrender.c:647  [size]
void __cdecl ForestRender_SetTextureState_AlphaTestFoliage(void *pxContext)
{
  Direct3DRender_SetTextureStageFilteringMode(0);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ADDRESSU, 1u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ADDRESSV, 1u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_TEXCOORDINDEX, 0);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_TEXTURETRANSFORMFLAGS, 0);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAOP, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAARG1, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAARG2, 0);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLOROP, 5u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLORARG1, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLORARG2, 0);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_COLOROP, 1u);
}

// source: e/3/pc/pc_forestrender.c:675  [size]
void __cdecl ForestRender_SetGenericState_Trunk(void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vFog; };
    struct { char igi2_o1[12]; struct _D3DMATERIAL8 tMaterial; };
    char igi2_extent[80];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  igi2_frame.vFog = DrawTerrainMesh_vFogDensity * 0.800000011920929;
  memset(&igi2_frame.tMaterial, 0, sizeof(igi2_frame.tMaterial));
  igi2_frame.tMaterial.Diffuse.r = 1.0;
  igi2_frame.tMaterial.Diffuse.g = 1.0;
  igi2_frame.tMaterial.Diffuse.b = 1.0;
  igi2_frame.tMaterial.Ambient.r = 1.0;
  igi2_frame.tMaterial.Ambient.g = 1.0;
  igi2_frame.tMaterial.Ambient.b = 1.0;
  Direct3D_ptDevice->lpVtbl->SetMaterial(Direct3D_ptDevice, &igi2_frame.tMaterial);
  Direct3D_ptDevice->lpVtbl->SetRenderState(
    Direct3D_ptDevice,
    D3DRS_FOGCOLOR,
    (__int64)(Mesh3D_atFogColor[1].vZ * 255.0)
  - (((unsigned int)(__int64)(Mesh3D_atFogColor[1].vY * -255.0)
    + ((unsigned int)(__int64)(Mesh3D_atFogColor[1].vX * -255.0) << 8)) << 8));
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGTABLEMODE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGVERTEXMODE, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGDENSITY, LODWORD(igi2_frame.vFog));
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGENABLE, QVertex_isFog);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SPECULARENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_CULLMODE, 3u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_LIGHTING, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_COLORVERTEX, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_DIFFUSEMATERIALSOURCE, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_DITHERENABLE, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZENABLE, Direct3D_bZBufferMode);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZWRITEENABLE, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZFUNC, 4u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_NORMALIZENORMALS, 1u);
}

// source: e/3/pc/pc_forestrender.c:735  [size]
void __cdecl ForestRender_SetGenericState_AlphaTestFoliage(void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vFog; };
    struct { char igi2_o1[12]; struct _D3DMATERIAL8 tMaterial; };
    char igi2_extent[80];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  igi2_frame.vFog = DrawTerrainMesh_vFogDensity * 0.800000011920929;
  memset(&igi2_frame.tMaterial, 0, sizeof(igi2_frame.tMaterial));
  igi2_frame.tMaterial.Diffuse.r = 1.0;
  igi2_frame.tMaterial.Diffuse.g = 1.0;
  igi2_frame.tMaterial.Diffuse.b = 1.0;
  igi2_frame.tMaterial.Ambient.r = 1.0;
  igi2_frame.tMaterial.Ambient.g = 1.0;
  igi2_frame.tMaterial.Ambient.b = 1.0;
  Direct3D_ptDevice->lpVtbl->SetMaterial(Direct3D_ptDevice, &igi2_frame.tMaterial);
  Direct3D_ptDevice->lpVtbl->SetRenderState(
    Direct3D_ptDevice,
    D3DRS_FOGCOLOR,
    (__int64)(Mesh3D_atFogColor[1].vZ * 255.0)
  - (((unsigned int)(__int64)(Mesh3D_atFogColor[1].vY * -255.0)
    + ((unsigned int)(__int64)(Mesh3D_atFogColor[1].vX * -255.0) << 8)) << 8));
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGTABLEMODE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGVERTEXMODE, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGDENSITY, LODWORD(igi2_frame.vFog));
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGENABLE, QVertex_isFog);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SPECULARENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_CULLMODE, 3u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_LIGHTING, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_DITHERENABLE, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZENABLE, Direct3D_bZBufferMode);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZWRITEENABLE, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZFUNC, 4u);
}

// source: e/3/pc/pc_forestrender.c:791  [size]
void __cdecl ForestRender_SetGenericState_AlphaBlendFoliage(void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vFog; };
    struct { char igi2_o1[12]; struct _D3DMATERIAL8 tMaterial; };
    char igi2_extent[80];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  igi2_frame.vFog = DrawTerrainMesh_vFogDensity * 0.800000011920929;
  memset(&igi2_frame.tMaterial, 0, sizeof(igi2_frame.tMaterial));
  igi2_frame.tMaterial.Diffuse.r = 1.0;
  igi2_frame.tMaterial.Diffuse.g = 1.0;
  igi2_frame.tMaterial.Diffuse.b = 1.0;
  igi2_frame.tMaterial.Ambient.r = 1.0;
  igi2_frame.tMaterial.Ambient.g = 1.0;
  igi2_frame.tMaterial.Ambient.b = 1.0;
  Direct3D_ptDevice->lpVtbl->SetMaterial(Direct3D_ptDevice, &igi2_frame.tMaterial);
  Direct3D_ptDevice->lpVtbl->SetRenderState(
    Direct3D_ptDevice,
    D3DRS_FOGCOLOR,
    (__int64)(Mesh3D_atFogColor[1].vZ * 255.0)
  - (((unsigned int)(__int64)(Mesh3D_atFogColor[1].vY * -255.0)
    + ((unsigned int)(__int64)(Mesh3D_atFogColor[1].vX * -255.0) << 8)) << 8));
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGTABLEMODE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGVERTEXMODE, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGDENSITY, LODWORD(igi2_frame.vFog));
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGENABLE, QVertex_isFog);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SPECULARENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_CULLMODE, 3u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_LIGHTING, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_DITHERENABLE, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZENABLE, Direct3D_bZBufferMode);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZWRITEENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZFUNC, 4u);
}

// source: e/3/pc/pc_forestrender.c:846  [size]
void __cdecl ForestRender_SetStates_Trunk(struct Batch_SetStatesContext_s *ptContext)
{
  _DWORD *pxUserContext; // esi
  int v2; // edx
  struct RenderStateBlock_t *v3; // eax
  int v4; // ecx
  struct RenderStateBlock_t *v5; // eax
  int v6; // ecx
  struct RenderStateBlock_t *v7; // eax
  int v8; // ecx
  struct RenderStateBlock_t *v9; // eax
  int v10; // ecx

  pxUserContext = ptContext->pxUserContext;
  v2 = *(_DWORD *)(*pxUserContext + 16);
  if ( *(struct IDirect3DBaseTexture8 **)(*(_DWORD *)v2 + 36) != Direct3D_tState.aptTexture[0] )
  {
    Direct3D_tState.aptTexture[0] = *(struct IDirect3DBaseTexture8 **)(*(_DWORD *)v2 + 36);
    Direct3D_ptDevice->lpVtbl->SetTexture(Direct3D_ptDevice, 0, Direct3D_tState.aptTexture[0]);
  }
  if ( pxUserContext[2] == 1 )
  {
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLOROP, 4u);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHAREF, 32u);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_TEXTUREFACTOR, -16777216u);
  }
  else
  {
    v3 = Direct3D_ptClippingStateBlock;
    v4 = Direct3D_eClippingStateOn;
    if ( Direct3D_ptClippingStateBlock->eCurrentState != Direct3D_eClippingStateOn )
    {
      Direct3D_ptClippingStateBlock->eCurrentState = Direct3D_eClippingStateOn;
      v3->atRenderState[v4].pfCallback(nullptr);
    }
    v5 = Direct3D_ptBlendStateBlock;
    v6 = Direct3DRender_eBlendStateAlphaTest;
    if ( Direct3D_ptBlendStateBlock->eCurrentState != Direct3DRender_eBlendStateAlphaTest )
    {
      Direct3D_ptBlendStateBlock->eCurrentState = Direct3DRender_eBlendStateAlphaTest;
      v5->atRenderState[v6].pfCallback(nullptr);
    }
    v7 = Direct3D_ptGenericStateBlock;
    v8 = ForestRender_eGenericState_Trunk;
    if ( Direct3D_ptGenericStateBlock->eCurrentState != ForestRender_eGenericState_Trunk )
    {
      Direct3D_ptGenericStateBlock->eCurrentState = ForestRender_eGenericState_Trunk;
      v7->atRenderState[v8].pfCallback(nullptr);
    }
    v9 = Direct3D_ptTextureStateBlock;
    v10 = ForestRender_eTextureState_Trunk;
    if ( Direct3D_ptTextureStateBlock->eCurrentState != ForestRender_eTextureState_Trunk )
    {
      Direct3D_ptTextureStateBlock->eCurrentState = ForestRender_eTextureState_Trunk;
      v9->atRenderState[v10].pfCallback(nullptr);
    }
  }
}

// source: e/3/pc/pc_forestrender.c:883  [size]
void __cdecl ForestRender_SetStates_Foliage(struct Batch_SetStatesContext_s *ptContext)
{
  _DWORD *pxUserContext; // esi
  int v2; // edx
  struct RenderStateBlock_t *v3; // eax
  int v4; // ecx
  struct RenderStateBlock_t *v5; // eax
  int v6; // ecx
  struct RenderStateBlock_t *v7; // eax
  int v8; // ecx
  struct RenderStateBlock_t *v9; // eax
  int v10; // ecx
  struct RenderStateBlock_t *v11; // eax
  int v12; // ecx
  struct RenderStateBlock_t *v13; // eax
  int v14; // ecx
  struct RenderStateBlock_t *v15; // eax
  int v16; // ecx

  pxUserContext = ptContext->pxUserContext;
  v2 = *(_DWORD *)(*pxUserContext + 16);
  if ( *(struct IDirect3DBaseTexture8 **)(*(_DWORD *)v2 + 36) != Direct3D_tState.aptTexture[0] )
  {
    Direct3D_tState.aptTexture[0] = *(struct IDirect3DBaseTexture8 **)(*(_DWORD *)v2 + 36);
    Direct3D_ptDevice->lpVtbl->SetTexture(Direct3D_ptDevice, 0, Direct3D_tState.aptTexture[0]);
  }
  if ( pxUserContext[2] == 1 )
  {
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLOROP, 4u);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHAREF, 32u);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_TEXTUREFACTOR, -16777216u);
  }
  else
  {
    v3 = Direct3D_ptClippingStateBlock;
    v4 = Direct3D_eClippingStateOn;
    if ( Direct3D_ptClippingStateBlock->eCurrentState != Direct3D_eClippingStateOn )
    {
      Direct3D_ptClippingStateBlock->eCurrentState = Direct3D_eClippingStateOn;
      v3->atRenderState[v4].pfCallback(nullptr);
    }
    if ( pxUserContext[1] || pxUserContext[2] == 2 )
    {
      v11 = Direct3D_ptBlendStateBlock;
      v12 = Direct3DRender_eBlendStateTransparent;
      if ( Direct3D_ptBlendStateBlock->eCurrentState != Direct3DRender_eBlendStateTransparent )
      {
        Direct3D_ptBlendStateBlock->eCurrentState = Direct3DRender_eBlendStateTransparent;
        v11->atRenderState[v12].pfCallback(nullptr);
      }
      v13 = Direct3D_ptGenericStateBlock;
      v14 = ForestRender_eGenericState_AlphaBlendFoliage;
      if ( Direct3D_ptGenericStateBlock->eCurrentState != ForestRender_eGenericState_AlphaBlendFoliage )
      {
        Direct3D_ptGenericStateBlock->eCurrentState = ForestRender_eGenericState_AlphaBlendFoliage;
        v13->atRenderState[v14].pfCallback(nullptr);
      }
      v15 = Direct3D_ptTextureStateBlock;
      v16 = ForestRender_eTextureState_AlphaBlendFoliage;
      if ( Direct3D_ptTextureStateBlock->eCurrentState != ForestRender_eTextureState_AlphaBlendFoliage )
      {
        Direct3D_ptTextureStateBlock->eCurrentState = ForestRender_eTextureState_AlphaBlendFoliage;
        v15->atRenderState[v16].pfCallback(nullptr);
      }
    }
    else
    {
      v5 = Direct3D_ptBlendStateBlock;
      v6 = Direct3DRender_eBlendStateAlphaTest;
      if ( Direct3D_ptBlendStateBlock->eCurrentState != Direct3DRender_eBlendStateAlphaTest )
      {
        Direct3D_ptBlendStateBlock->eCurrentState = Direct3DRender_eBlendStateAlphaTest;
        v5->atRenderState[v6].pfCallback(nullptr);
      }
      v7 = Direct3D_ptGenericStateBlock;
      v8 = ForestRender_eGenericState_AlphaTestFoliage;
      if ( Direct3D_ptGenericStateBlock->eCurrentState != ForestRender_eGenericState_AlphaTestFoliage )
      {
        Direct3D_ptGenericStateBlock->eCurrentState = ForestRender_eGenericState_AlphaTestFoliage;
        v7->atRenderState[v8].pfCallback(nullptr);
      }
      v9 = Direct3D_ptTextureStateBlock;
      v10 = ForestRender_eTextureState_AlphaTestFoliage;
      if ( Direct3D_ptTextureStateBlock->eCurrentState != ForestRender_eTextureState_AlphaTestFoliage )
      {
        Direct3D_ptTextureStateBlock->eCurrentState = ForestRender_eTextureState_AlphaTestFoliage;
        v9->atRenderState[v10].pfCallback(nullptr);
      }
    }
  }
}

// source: e/3/pc/pc_forestrender.c:940  [size]
struct ForestRender_Morph_t *__cdecl ForestRender_DrawTrunkFaceGroup(
        struct Mesh3D_RenderMesh_RigidDirect3D_t *ptRenderMesh,
        struct ForestRender_Morph_t *atMorphFaceGroups,
        int iFaceGroup,
        struct ForestRender_States_t *ptStates,
        struct real32x9_t *ptRotationMatrix,
        struct real32x3_t *ptTranslation,
        struct real32x3_t *ptScale,
        float vRadius,
        unsigned int bLight,
        int isFlush)
{
  #pragma pack(push, 1)
  union
  {
    struct { int iVertex; };
    struct { int iVertexa; };
    struct { int iVertexb; };
    struct { int iVertexc; };
    struct { char igi2_o4[4]; BOOL isWind; };
    struct { char igi2_o5[4]; float *isWinda; };
    struct { char igi2_o6[4]; struct real32x3_t *isWindb; };
    struct { char igi2_o7[8]; struct ForestRender_TrunkVertex_t *ptVertices; };
    struct { char igi2_o8[12]; float v51; };
    struct { char igi2_o9[16]; struct ForestRender_Morph_t *v52; };
    struct { char igi2_o10[20]; int nOffset; };
    struct { char igi2_o11[24]; struct real32x3_t Real32x3_Rotate_tTemp; };
    struct { char igi2_o12[44]; float v55; };
    char igi2_extent[48];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct ForestRender_Morph_t *result; // eax
  struct ForestRender_Morph_t *v11; // ebp
  struct RigidDirect3D_FaceGroup_t *v12; // ebx
  struct ForestRender_TrunkVertex_t *v13; // ecx
  float *p_vZ; // ecx
  float *v15; // eax
  double v16; // st7
  double v17; // st6
  double v18; // st7
  double v19; // st6
  struct Wind_s *v20; // edx
  struct Mesh3D_MorphVertex_t *atMorphVertices; // ecx
  int v22; // edi
  struct real32x3_t *v23; // eax
  double v24; // st7
  double v25; // st6
  double v26; // st7
  double v27; // st5
  bool v28; // cc
  struct real32x2_t *p_tUV; // ecx
  _DWORD *p_vY; // edx
  double v31; // st7
  float *p_vX; // edx
  double v33; // st6
  double v34; // st7
  double v35; // st6
  float *v36; // ecx
  float *v37; // edx
  double v38; // st7
  double v39; // st7
  double v40; // st6
  double v41; // st7
  double v42; // st6

  if ( isFlush )
    return (struct ForestRender_Morph_t *)Batch_Flush((unsigned int *)&dword_834DC04, ptStates);
  if ( atMorphFaceGroups )
  {
    v11 = &atMorphFaceGroups[iFaceGroup];
    igi2_frame.isWind = v11->atMorphVertices != nullptr;
  }
  else
  {
    v11 = nullptr;
    igi2_frame.isWind = 0;
  }
  v12 = &ptRenderMesh->ptFaceGroup[iFaceGroup];
  Batch_GetLockedVertex(
    BATCH_XYZNORMALDIFFUSETEX1,
    BATCH_INDEX16,
    v12->nNumVertices,
    v12->nNumFaces,
    0,
    &ptRenderMesh->piIndex[v12->iStartIndex],
    v12->iStartVertex,
    ForestRender_SetStates_Trunk,
    nullptr,
    ptStates,
    (unsigned __int8 **)&igi2_frame.ptVertices,
    &igi2_frame.nOffset,
    (unsigned int *)&dword_834DC04);
  v13 = &igi2_frame.ptVertices[igi2_frame.nOffset];
  result = (struct ForestRender_Morph_t *)&ptRenderMesh->ptVertex[v12->iStartVertex];
  igi2_frame.ptVertices = v13;
  igi2_frame.nOffset = (int)result;
  if ( igi2_frame.isWind )
  {
    Wind_Init(ptTranslation, vRadius);
    igi2_frame.iVertex = 0;
    if ( v12->nNumVertices )
    {
      p_vZ = &ForestRender_atMorphBuffer->vZ;
      v15 = (float *)(igi2_frame.nOffset + 4);
      do
      {
        v16 = *v15 * ptRotationMatrix->tX.vY;
        ++igi2_frame.iVertex;
        v17 = ptRotationMatrix->tX.vX * *(v15 - 1);
        v15 += 8;
        p_vZ += 3;
        v18 = v16 + v17 + *(v15 - 7) * ptRotationMatrix->tX.vZ;
        v19 = ptRotationMatrix->tY.vX * *(v15 - 9)
            + *(v15 - 7) * ptRotationMatrix->tY.vZ
            + ptRotationMatrix->tY.vY * *(v15 - 8);
        igi2_frame.Real32x3_Rotate_tTemp.vZ = *(v15 - 7) * ptRotationMatrix->tZ.vZ
                                 + *(v15 - 8) * ptRotationMatrix->tZ.vY
                                 + *(v15 - 9) * ptRotationMatrix->tZ.vX;
        *(p_vZ - 5) = v18 + ptTranslation->vX;
        *(p_vZ - 4) = v19 + ptTranslation->vY;
        *(p_vZ - 3) = igi2_frame.Real32x3_Rotate_tTemp.vZ + ptTranslation->vZ;
      }
      while ( igi2_frame.iVertex < v12->nNumVertices );
    }
    v20 = Wind_ptWindTask;
    atMorphVertices = v11->atMorphVertices;
    result = v11;
    igi2_frame.iVertexa = 0;
    igi2_frame.v52 = v11;
    igi2_frame.isWinda = Wind_ptWindTask->avInterpolationCoeffs;
    do
    {
      v22 = 0;
      if ( result->anMorphChannelVertices[0] > 0 )
      {
        do
        {
          v23 = &ForestRender_atMorphBuffer[atMorphVertices->iIndex];
          if ( v20 )
          {
            v26 = (v23->vY * v20->tWindDirection.vY + v20->tWindDirection.vX * v23->vX - Wind_vX1) * *igi2_frame.isWinda
                + *(float *)(igi2_frame.iVertexa + 137630568);
            igi2_frame.v51 = v26;
            v24 = v26 * v20->tWindDirection.vX;
            v25 = igi2_frame.v51 * v20->tWindDirection.vY;
          }
          else
          {
            v24 = 0.0;
            v25 = 0.0;
          }
          v27 = atMorphVertices->tDelta.vZ * ptScale->vX;
          ++atMorphVertices;
          ++v22;
          v23->vX = v27 * v24 + v23->vX;
          v23->vY = v23->vY - atMorphVertices[-1].tDelta.vX * ptScale->vY * v25;
          v23->vZ = atMorphVertices[-1].tDelta.vY * ptScale->vZ * 0.0 + v23->vZ;
          result = igi2_frame.v52;
        }
        while ( v22 < igi2_frame.v52->anMorphChannelVertices[0] );
      }
      result = (struct ForestRender_Morph_t *)((char *)result + 4);
      v28 = igi2_frame.iVertexa + 4 < 64;
      igi2_frame.iVertexa += 4;
      igi2_frame.v52 = result;
      ++igi2_frame.isWinda;
    }
    while ( v28 );
    igi2_frame.iVertexb = 0;
    if ( v12->nNumVertices )
    {
      igi2_frame.isWindb = ForestRender_atMorphBuffer;
      p_tUV = &igi2_frame.ptVertices->tUV;
      result = (struct ForestRender_Morph_t *)(igi2_frame.nOffset + 16);
      do
      {
        p_vY = (_DWORD *)&p_tUV[-4].vY;
        *p_vY = LODWORD(igi2_frame.isWindb->vX);
        p_vY[1] = LODWORD(igi2_frame.isWindb->vY);
        p_vY[2] = LODWORD(igi2_frame.isWindb->vZ);
        v31 = *(float *)&result->anMorphChannelVertices[1] * ptRotationMatrix->tX.vZ;
        p_vX = &p_tUV[-2].vX;
        v33 = *(float *)&result[-1].atMorphVertices;
        result = (struct ForestRender_Morph_t *)((char *)result + 32);
        p_tUV = (struct real32x2_t *)((char *)p_tUV + 36);
        igi2_frame.Real32x3_Rotate_tTemp.vX = v31
                                 + v33 * ptRotationMatrix->tX.vX
                                 + *(float *)&result[-1].anMorphChannelVertices[9] * ptRotationMatrix->tX.vY;
        igi2_frame.Real32x3_Rotate_tTemp.vY = *(float *)&result[-1].anMorphChannelVertices[10] * ptRotationMatrix->tY.vZ
                                 + *(float *)&result[-1].anMorphChannelVertices[9] * ptRotationMatrix->tY.vY
                                 + *(float *)&result[-1].anMorphChannelVertices[8] * ptRotationMatrix->tY.vX;
        v34 = *(float *)&result[-1].anMorphChannelVertices[10] * ptRotationMatrix->tZ.vZ
            + *(float *)&result[-1].anMorphChannelVertices[9] * ptRotationMatrix->tZ.vY;
        v35 = *(float *)&result[-1].anMorphChannelVertices[8] * ptRotationMatrix->tZ.vX;
        *p_vX = igi2_frame.Real32x3_Rotate_tTemp.vX;
        p_vX[1] = igi2_frame.Real32x3_Rotate_tTemp.vY;
        igi2_frame.Real32x3_Rotate_tTemp.vZ = v34 + v35;
        p_vX[2] = igi2_frame.Real32x3_Rotate_tTemp.vZ;
        LODWORD(p_tUV[-5].vY) = result[-1].anMorphChannelVertices[11];
        LODWORD(p_tUV[-4].vX) = result[-1].anMorphChannelVertices[12];
        LODWORD(p_tUV[-5].vX) = bLight;
        ++igi2_frame.isWindb;
        ++igi2_frame.iVertexb;
      }
      while ( igi2_frame.iVertexb < v12->nNumVertices );
    }
  }
  else
  {
    igi2_frame.iVertexc = 0;
    if ( v12->nNumVertices )
    {
      v36 = &v13->tPos.vZ;
      result = (struct ForestRender_Morph_t *)((char *)result + 4);
      do
      {
        v37 = v36 + 1;
        v38 = ptRotationMatrix->tX.vZ * *(float *)&result->anMorphChannelVertices[1];
        result = (struct ForestRender_Morph_t *)((char *)result + 32);
        v36 += 9;
        v39 = v38
            + *(float *)&result[-1].anMorphChannelVertices[8] * ptRotationMatrix->tX.vX
            + *(float *)&result[-1].anMorphChannelVertices[9] * ptRotationMatrix->tX.vY;
        v40 = *(float *)&result[-1].anMorphChannelVertices[9] * ptRotationMatrix->tY.vY
            + ptRotationMatrix->tY.vZ * *(float *)&result[-1].anMorphChannelVertices[10]
            + *(float *)&result[-1].anMorphChannelVertices[8] * ptRotationMatrix->tY.vX;
        igi2_frame.v55 = *(float *)&result[-1].anMorphChannelVertices[9] * ptRotationMatrix->tZ.vY
            + *(float *)&result[-1].anMorphChannelVertices[8] * ptRotationMatrix->tZ.vX
            + *(float *)&result[-1].anMorphChannelVertices[10] * ptRotationMatrix->tZ.vZ;
        *(v36 - 11) = v39 + ptTranslation->vX;
        *(v36 - 10) = v40 + ptTranslation->vY;
        *(v36 - 9) = igi2_frame.v55 + ptTranslation->vZ;
        igi2_frame.Real32x3_Rotate_tTemp.vX = ptRotationMatrix->tX.vX * *(float *)&result[-1].anMorphChannelVertices[11]
                                 + ptRotationMatrix->tX.vZ * *(float *)&result[-1].anMorphChannelVertices[13]
                                 + ptRotationMatrix->tX.vY * *(float *)&result[-1].anMorphChannelVertices[12];
        igi2_frame.Real32x3_Rotate_tTemp.vY = ptRotationMatrix->tY.vX * *(float *)&result[-1].anMorphChannelVertices[11]
                                 + ptRotationMatrix->tY.vZ * *(float *)&result[-1].anMorphChannelVertices[13]
                                 + ptRotationMatrix->tY.vY * *(float *)&result[-1].anMorphChannelVertices[12];
        v41 = ptRotationMatrix->tZ.vX * *(float *)&result[-1].anMorphChannelVertices[11]
            + *(float *)&result[-1].anMorphChannelVertices[13] * ptRotationMatrix->tZ.vZ;
        v42 = *(float *)&result[-1].anMorphChannelVertices[12] * ptRotationMatrix->tZ.vY;
        *v37 = igi2_frame.Real32x3_Rotate_tTemp.vX;
        v37[1] = igi2_frame.Real32x3_Rotate_tTemp.vY;
        igi2_frame.Real32x3_Rotate_tTemp.vZ = v41 + v42;
        v37[2] = igi2_frame.Real32x3_Rotate_tTemp.vZ;
        *((_DWORD *)v36 - 5) = bLight;
        *(v36 - 4) = *(float *)&result[-1].anMorphChannelVertices[14];
        *(v36 - 3) = *(float *)&result[-1].anMorphChannelVertices[15];
        ++igi2_frame.iVertexc;
      }
      while ( igi2_frame.iVertexc < v12->nNumVertices );
    }
  }
  return result;
}

// source: e/3/pc/pc_forestrender.c:1071  [size~]
struct ForestRender_Morph_t *__cdecl ForestRender_DrawFoliageFaceGroup(
        struct Mesh3D_RenderMesh_RigidDirect3D_t *ptRenderMesh,
        struct ForestRender_Morph_t *atMorphFaceGroups,
        int iFaceGroup,
        struct ForestRender_States_t *ptStates,
        struct real32x9_t *ptRotationMatrix,
        struct real32x3_t *ptTranslation,
        struct real32x3_t *ptScale,
        float vRadius,
        unsigned int bLight,
        int isFlush)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v38; };
    struct { int v39; };
    struct { int v40; };
    struct { int v41; };
    struct { char igi2_o4[4]; float *avInterpolationCoeffs; };
    struct { char igi2_o5[4]; BOOL v42; };
    struct { char igi2_o6[8]; unsigned __int8 *ppxLockedVertex; };
    struct { char igi2_o7[12]; float v45; };
    struct { char igi2_o8[16]; struct ForestRender_Morph_t *pxContext; };
    struct { char igi2_o9[28]; float v47; };
    char igi2_extent[32];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct ForestRender_Morph_t *result; // eax
  struct ForestRender_Morph_t *v12; // ebp
  struct RigidDirect3D_FaceGroup_t *v13; // ebx
  unsigned __int8 *v14; // ecx
  float *p_vZ; // ecx
  int *v16; // eax
  double v17; // st7
  double v18; // st6
  double v19; // st7
  double v20; // st6
  struct Wind_s *v21; // edx
  struct Mesh3D_MorphVertex_t *atMorphVertices; // ecx
  struct ForestRender_Morph_t *v23; // edi
  int i; // esi
  struct real32x3_t *v25; // eax
  double v26; // st7
  double v27; // st6
  double v28; // st7
  double v29; // st5
  bool v30; // cc
  struct real32x3_t *v31; // edx
  int *v32; // ecx
  int *v33; // esi
  unsigned __int8 *v34; // ecx
  double v35; // st7
  double v36; // st7
  double v37; // st6

  if ( ptStates )
    return (struct ForestRender_Morph_t *)Batch_Flush((unsigned int *)&dword_834DC08, ptRotationMatrix);
  if ( atMorphFaceGroups )
  {
    v12 = &atMorphFaceGroups[iFaceGroup];
    igi2_frame.v42 = v12->atMorphVertices != nullptr;
  }
  else
  {
    v12 = nullptr;
    igi2_frame.v42 = 0;
  }
  v13 = &ptRenderMesh->ptFaceGroup[iFaceGroup];
  Batch_GetLockedVertex(
    BATCH_XYZDIFFUSETEX1,
    BATCH_INDEX16,
    v13->nNumVertices,
    v13->nNumFaces,
    0,
    &ptRenderMesh->piIndex[v13->iStartIndex],
    v13->iStartVertex,
    ForestRender_SetStates_Foliage,
    nullptr,
    ptRotationMatrix,
    &igi2_frame.ppxLockedVertex,
    (int *)&igi2_frame.pxContext,
    (unsigned int *)&dword_834DC08);
  v14 = &igi2_frame.ppxLockedVertex[24 * (_DWORD)igi2_frame.pxContext];
  result = (struct ForestRender_Morph_t *)&ptRenderMesh->ptVertex[v13->iStartVertex];
  igi2_frame.ppxLockedVertex = v14;
  igi2_frame.pxContext = result;
  if ( !igi2_frame.v42 || LODWORD(ptRotationMatrix->tX.vZ) )
  {
    igi2_frame.v41 = 0;
    if ( v13->nNumVertices )
    {
      v34 = v14 + 8;
      result = (struct ForestRender_Morph_t *)((char *)result + 4);
      do
      {
        v35 = ptTranslation->vZ * *(float *)&result->anMorphChannelVertices[1];
        result = (struct ForestRender_Morph_t *)((char *)result + 32);
        v34 += 24;
        v36 = v35
            + *(float *)&result[-1].anMorphChannelVertices[8] * ptTranslation->vX
            + *(float *)&result[-1].anMorphChannelVertices[9] * ptTranslation->vY;
        v37 = *(float *)&result[-1].anMorphChannelVertices[9] * ptTranslation[1].vY
            + ptTranslation[1].vZ * *(float *)&result[-1].anMorphChannelVertices[10]
            + *(float *)&result[-1].anMorphChannelVertices[8] * ptTranslation[1].vX;
        igi2_frame.v47 = *(float *)&result[-1].anMorphChannelVertices[9] * ptTranslation[2].vY
            + *(float *)&result[-1].anMorphChannelVertices[8] * ptTranslation[2].vX
            + *(float *)&result[-1].anMorphChannelVertices[10] * ptTranslation[2].vZ;
        *((float *)v34 - 8) = v36 + *(float *)isFlush;
        *((float *)v34 - 7) = v37 + *(float *)(isFlush + 4);
        *((float *)v34 - 6) = igi2_frame.v47 + *(float *)(isFlush + 8);
        *((_DWORD *)v34 - 5) = bLight;
        *((_DWORD *)v34 - 4) = result[-1].anMorphChannelVertices[14];
        *((_DWORD *)v34 - 3) = result[-1].anMorphChannelVertices[15];
        ++igi2_frame.v41;
      }
      while ( igi2_frame.v41 < v13->nNumVertices );
    }
  }
  else
  {
    Wind_Init((struct real32x3_t *)isFlush, vRadius);
    igi2_frame.v38 = 0;
    if ( v13->nNumVertices )
    {
      p_vZ = &ForestRender_atMorphBuffer->vZ;
      v16 = &igi2_frame.pxContext->anMorphChannelVertices[1];
      do
      {
        v17 = *((float *)v16 + 1) * ptTranslation->vZ;
        v18 = *((float *)v16 - 1);
        ++igi2_frame.v38;
        v16 += 8;
        p_vZ += 3;
        v19 = v17 + v18 * ptTranslation->vX + *((float *)v16 - 8) * ptTranslation->vY;
        v20 = *((float *)v16 - 7) * ptTranslation[1].vZ
            + *((float *)v16 - 8) * ptTranslation[1].vY
            + *((float *)v16 - 9) * ptTranslation[1].vX;
        igi2_frame.v47 = *((float *)v16 - 7) * ptTranslation[2].vZ
            + *((float *)v16 - 8) * ptTranslation[2].vY
            + *((float *)v16 - 9) * ptTranslation[2].vX;
        *(p_vZ - 5) = v19 + *(float *)isFlush;
        *(p_vZ - 4) = v20 + *(float *)(isFlush + 4);
        *(p_vZ - 3) = igi2_frame.v47 + *(float *)(isFlush + 8);
      }
      while ( igi2_frame.v38 < v13->nNumVertices );
    }
    v21 = Wind_ptWindTask;
    atMorphVertices = v12->atMorphVertices;
    igi2_frame.v39 = 0;
    v23 = v12;
    igi2_frame.avInterpolationCoeffs = Wind_ptWindTask->avInterpolationCoeffs;
    do
    {
      for ( i = 0; i < v23->anMorphChannelVertices[0]; v25->vZ = atMorphVertices[-1].tDelta.vY * ptScale->vZ * 0.0
                                                               + v25->vZ )
      {
        v25 = &ForestRender_atMorphBuffer[atMorphVertices->iIndex];
        if ( v21 )
        {
          v28 = (v25->vY * v21->tWindDirection.vY + v25->vX * v21->tWindDirection.vX - Wind_vX1)
              * *igi2_frame.avInterpolationCoeffs
              + *(float *)(igi2_frame.v39 + 137630568);
          igi2_frame.v45 = v28;
          v26 = v28 * v21->tWindDirection.vX;
          v27 = igi2_frame.v45 * v21->tWindDirection.vY;
        }
        else
        {
          v26 = 0.0;
          v27 = 0.0;
        }
        v29 = atMorphVertices->tDelta.vZ * ptScale->vX;
        ++atMorphVertices;
        ++i;
        v25->vX = v29 * v26 + v25->vX;
        v25->vY = v25->vY - atMorphVertices[-1].tDelta.vX * ptScale->vY * v27;
      }
      result = (struct ForestRender_Morph_t *)(igi2_frame.v39 + 4);
      v23 = (struct ForestRender_Morph_t *)((char *)v23 + 4);
      v30 = igi2_frame.v39 + 4 < 64;
      igi2_frame.v39 += 4;
      ++igi2_frame.avInterpolationCoeffs;
    }
    while ( v30 );
    igi2_frame.v40 = 0;
    if ( v13->nNumVertices )
    {
      v31 = ForestRender_atMorphBuffer;
      result = (struct ForestRender_Morph_t *)(igi2_frame.ppxLockedVertex + 12);
      v32 = &igi2_frame.pxContext->anMorphChannelVertices[6];
      do
      {
        v33 = &result[-1].anMorphChannelVertices[14];
        *v33 = LODWORD(v31->vX);
        v33[1] = LODWORD(v31->vY);
        v33[2] = LODWORD(v31->vZ);
        result->anMorphChannelVertices[1] = *v32;
        result->anMorphChannelVertices[2] = v32[1];
        result->anMorphChannelVertices[0] = bLight;
        ++v31;
        v32 += 8;
        result = (struct ForestRender_Morph_t *)((char *)result + 24);
        ++igi2_frame.v40;
      }
      while ( igi2_frame.v40 < v13->nNumVertices );
    }
  }
  return result;
}

// source: e/3/pc/pc_forestrender.c:1190  [size]
int __cdecl ForestRender_SortedFacesCompare(void *pxElem1, void *pxElem2)
{
  float pxElem2a = *(float *)&pxElem2; // [esp+8h] [ebp+8h] ARGSLOT

  pxElem2a = *(float *)(*(_DWORD *)pxElem2 + 24) - *(float *)(*(_DWORD *)pxElem1 + 24);
  return LODWORD(pxElem2a) & 0x80000000 | 1;
}

// source: e/3/pc/pc_forestrender.c:1229  [size]
int __cdecl ForestRender_DrawSortedFaces(
        struct Mesh3D_RenderMesh_RigidDirect3D_t *ptRenderMesh,
        struct ForestRender_Morph_t *ptMorph,
        struct RigidDirect3D_FaceGroup_t *ptFaceGroup,
        struct ForestRender_BSPTree_t *ptBSPTree,
        struct ForestRender_States_t *ptStates,
        unsigned int *pnHandler,
        struct real32x9_t *ptRotationMatrix,
        struct real32x3_t *ptTranslation,
        struct real32x9_t *ptMatrix,
        struct real32x3_t *ptDisplacement,
        struct real32x3_t *ptScale,
        float vRadius,
        unsigned int bAlpha,
        unsigned int bLight)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct ForestRender_FoliageVertex_t *ptVertices; };
    struct { char igi2_o1[4]; float v65; };
    struct { char igi2_o2[8]; struct Direct3DRender_XYZNormalTex1Vertex_t *ptSource; };
    struct { char igi2_o3[12]; unsigned __int16 *piIndices; };
    struct { char igi2_o4[16]; int nIBOffset; };
    struct { char igi2_o5[20]; int nVBOffset; };
    struct { char igi2_o6[24]; struct real32x3_t Real32x3_Rotate_tTemp; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct ForestRender_FoliageVertex_t *v17; // ecx
  struct Direct3DRender_XYZNormalTex1Vertex_t *v18; // eax
  unsigned int v19; // edx
  unsigned __int16 *v20; // ebp
  int v21; // edx
  struct real32x3_t *v22; // ebp
  float *p_vZ; // ecx
  float *p_vY; // eax
  double v25; // st7
  double v26; // st6
  double v27; // st7
  double v28; // st6
  struct ForestRender_Morph_t *p_isAlphaBlend; // eax
  struct Wind_s *v30; // edx
  struct Mesh3D_MorphVertex_t *atMorphVertices; // ecx
  int v32; // ebx
  float *p_vX; // eax
  double v34; // st7
  double v35; // st6
  double v36; // st7
  double v37; // st5
  bool v38; // cc
  unsigned int *p_bDiffuse; // eax
  struct real32x2_t *p_tUV; // ecx
  unsigned int *v41; // edx
  int v42; // esi
  int v43; // ebx
  struct ForestRender_SortedFace_s *v44; // eax
  float *v45; // ecx
  float *v46; // edx
  double v47; // st7
  double v48; // st6
  double v49; // st5
  float *v50; // ecx
  float *v51; // ecx
  float *v52; // eax
  double v53; // st7
  double v54; // st6
  int v55; // edx
  int v56; // esi
  struct ForestRender_SortedFace_s *ptSortedFaces; // eax
  double v58; // st7
  float *aiIndices; // eax
  int result; // eax
  unsigned __int16 *v61; // ecx
  __int16 v62; // dx
  float *ptRenderMesha = *(float * *)&ptRenderMesh; // [esp+34h] [ebp+4h] ARGSLOT
  struct ForestRender_Morph_t *ptMorpha = *(struct ForestRender_Morph_t * *)&ptMorph; // [esp+38h] [ebp+8h] ARGSLOT
  struct ForestRender_Morph_t *ptMorphb = *(struct ForestRender_Morph_t * *)&ptMorph; // [esp+38h] [ebp+8h] ARGSLOT
  BOOL ptStatesa = *(BOOL *)&pnHandler; // [esp+44h] [ebp+14h] ARGSLOT
  struct ForestRender_States_t *ptStatesb = *(struct ForestRender_States_t * *)&pnHandler; // [esp+44h] [ebp+14h] ARGSLOT
  struct ForestRender_States_t *ptStatesc = *(struct ForestRender_States_t * *)&pnHandler; // [esp+44h] [ebp+14h] ARGSLOT
  struct ForestRender_States_t *ptStatesd = *(struct ForestRender_States_t * *)&pnHandler; // [esp+44h] [ebp+14h] ARGSLOT
  struct ForestRender_States_t *ptStatese = *(struct ForestRender_States_t * *)&pnHandler; // [esp+44h] [ebp+14h] ARGSLOT

  ptStatesa = ptMorph->atMorphVertices != nullptr;
  Batch_GetLockedVertex(
    BATCH_XYZDIFFUSETEX1,
    BATCH_INDEX16,
    ptFaceGroup->nNumVertices,
    ptFaceGroup->nNumFaces,
    0,
    nullptr,
    ptFaceGroup->iStartVertex,
    ForestRender_SetStates_Foliage,
    nullptr,
    ptStates,
    (unsigned __int8 **)&igi2_frame.ptVertices,
    &igi2_frame.nVBOffset,
    pnHandler);
  v17 = &igi2_frame.ptVertices[igi2_frame.nVBOffset];
  v18 = &ptRenderMesh->ptVertex[ptFaceGroup->iStartVertex];
  v19 = *pnHandler;
  v20 = nullptr;
  igi2_frame.ptVertices = v17;
  igi2_frame.ptSource = v18;
  if ( v19 )
  {
    v21 = *(_DWORD *)(v19 + 8);
    v20 = *(unsigned __int16 **)(v21 + 8);
    igi2_frame.nIBOffset = *(_DWORD *)(v21 + 16);
  }
  else
  {
    igi2_frame.nIBOffset = 0;
  }
  igi2_frame.piIndices = v20;
  if ( ptStatesa )
  {
    Wind_Init(ptTranslation, vRadius);
    ptStatesb = nullptr;
    v22 = ForestRender_atMorphBuffer;
    if ( ptFaceGroup->nNumVertices )
    {
      p_vZ = &ForestRender_atMorphBuffer->vZ;
      p_vY = &igi2_frame.ptSource->tPos.vY;
      do
      {
        v25 = p_vY[1] * ptRotationMatrix->tX.vZ;
        v26 = *(p_vY - 1);
        ptStatesb = (struct ForestRender_States_t *)((char *)ptStatesb + 1);
        p_vY += 8;
        p_vZ += 3;
        v27 = v25 + v26 * ptRotationMatrix->tX.vX + ptRotationMatrix->tX.vY * *(p_vY - 8);
        v28 = ptRotationMatrix->tY.vX * *(p_vY - 9)
            + *(p_vY - 7) * ptRotationMatrix->tY.vZ
            + ptRotationMatrix->tY.vY * *(p_vY - 8);
        igi2_frame.Real32x3_Rotate_tTemp.vZ = *(p_vY - 7) * ptRotationMatrix->tZ.vZ
                                 + *(p_vY - 8) * ptRotationMatrix->tZ.vY
                                 + *(p_vY - 9) * ptRotationMatrix->tZ.vX;
        *(p_vZ - 5) = v27 + ptTranslation->vX;
        *(p_vZ - 4) = v28 + ptTranslation->vY;
        *(p_vZ - 3) = igi2_frame.Real32x3_Rotate_tTemp.vZ + ptTranslation->vZ;
      }
      while ( (int)ptStatesb < ptFaceGroup->nNumVertices );
    }
    p_isAlphaBlend = ptMorph;
    v30 = Wind_ptWindTask;
    atMorphVertices = ptMorph->atMorphVertices;
    ptMorpha = nullptr;
    ptStatesc = (struct ForestRender_States_t *)p_isAlphaBlend;
    ptRenderMesha = Wind_ptWindTask->avInterpolationCoeffs;
    do
    {
      v32 = 0;
      if ( p_isAlphaBlend->anMorphChannelVertices[0] > 0 )
      {
        do
        {
          p_vX = &v22[atMorphVertices->iIndex].vX;
          if ( v30 )
          {
            v36 = (p_vX[1] * v30->tWindDirection.vY + v30->tWindDirection.vX * *p_vX - Wind_vX1) * *ptRenderMesha
                + *(float *)&ptMorpha[2023978].atMorphVertices;
            igi2_frame.v65 = v36;
            v34 = v36 * v30->tWindDirection.vX;
            v35 = igi2_frame.v65 * v30->tWindDirection.vY;
          }
          else
          {
            v34 = 0.0;
            v35 = 0.0;
          }
          v37 = atMorphVertices->tDelta.vZ * ptScale->vX;
          ++atMorphVertices;
          ++v32;
          *p_vX = v37 * v34 + *p_vX;
          p_vX[1] = p_vX[1] - v35 * atMorphVertices[-1].tDelta.vX * ptScale->vY;
          p_vX[2] = atMorphVertices[-1].tDelta.vY * ptScale->vZ * 0.0 + p_vX[2];
        }
        while ( v32 < (int)ptStatesc->ptVirModel );
      }
      p_isAlphaBlend = (struct ForestRender_Morph_t *)&ptStatesc->isAlphaBlend;
      v38 = (int)&ptMorpha->anMorphChannelVertices[1] < 64;
      ptMorpha = (struct ForestRender_Morph_t *)((char *)ptMorpha + 4);
      ptStatesc = (struct ForestRender_States_t *)((char *)ptStatesc + 4);
      ++ptRenderMesha;
    }
    while ( v38 );
    ptStatesd = nullptr;
    if ( ptFaceGroup->nNumVertices )
    {
      p_bDiffuse = &igi2_frame.ptVertices->bDiffuse;
      ptMorphb = (struct ForestRender_Morph_t *)v22;
      p_tUV = &igi2_frame.ptSource->tUV;
      do
      {
        v41 = p_bDiffuse - 3;
        *v41 = ptMorphb->anMorphChannelVertices[0];
        v41[1] = ptMorphb->anMorphChannelVertices[1];
        v41[2] = ptMorphb->anMorphChannelVertices[2];
        p_bDiffuse[1] = LODWORD(p_tUV->vX);
        p_bDiffuse[2] = LODWORD(p_tUV->vY);
        *p_bDiffuse = bLight | (bAlpha << 24);
        ptMorphb = (struct ForestRender_Morph_t *)((char *)ptMorphb + 12);
        p_tUV += 4;
        p_bDiffuse += 6;
        ptStatesd = (struct ForestRender_States_t *)((char *)ptStatesd + 1);
      }
      while ( (int)ptStatesd < ptFaceGroup->nNumVertices );
    }
    v42 = 0;
    if ( ptFaceGroup->nNumFaces )
    {
      v43 = 0;
      do
      {
        v44 = &ptBSPTree->ptSortedFaces[v43];
        v45 = &v22[v44->tFace.aiIndices[1]].vX;
        v46 = &v22[v44->tFace.aiIndices[0]].vX;
        ++v42;
        ++v43;
        v47 = (*v45 + *v46) * 0.5;
        v48 = (v46[1] + v45[1]) * 0.5;
        v49 = v46[2] + v45[2];
        v50 = &v22[v44->tFace.aiIndices[2]].vX;
        igi2_frame.Real32x3_Rotate_tTemp.vZ = v49 * 0.5;
        igi2_frame.Real32x3_Rotate_tTemp.vX = (v47 + *v50) * 0.5;
        v44->vZ = igi2_frame.Real32x3_Rotate_tTemp.vX * ptMatrix->tZ.vX
                + (igi2_frame.Real32x3_Rotate_tTemp.vZ + v50[2]) * 0.5 * ptMatrix->tZ.vZ
                + (v48 + v50[1]) * 0.5 * ptMatrix->tZ.vY
                + ptDisplacement->vZ;
      }
      while ( v42 < ptFaceGroup->nNumFaces );
    }
  }
  else
  {
    ptStatese = nullptr;
    if ( ptFaceGroup->nNumVertices )
    {
      v51 = &v17->tPos.vZ;
      v52 = &v18->tPos.vY;
      do
      {
        v52 += 8;
        v51 += 6;
        v53 = ptRotationMatrix->tX.vY * *(v52 - 8)
            + *(v52 - 7) * ptRotationMatrix->tX.vZ
            + *(v52 - 9) * ptRotationMatrix->tX.vX;
        v54 = *(v52 - 7) * ptRotationMatrix->tY.vZ
            + ptRotationMatrix->tY.vY * *(v52 - 8)
            + ptRotationMatrix->tY.vX * *(v52 - 9);
        igi2_frame.Real32x3_Rotate_tTemp.vZ = *(v52 - 9) * ptRotationMatrix->tZ.vX
                                 + *(v52 - 7) * ptRotationMatrix->tZ.vZ
                                 + *(v52 - 8) * ptRotationMatrix->tZ.vY;
        *(v51 - 8) = v53 + ptTranslation->vX;
        *(v51 - 7) = v54 + ptTranslation->vY;
        *(v51 - 6) = igi2_frame.Real32x3_Rotate_tTemp.vZ + ptTranslation->vZ;
        *((_DWORD *)v51 - 5) = bLight | (bAlpha << 24);
        *(v51 - 4) = *(v52 - 3);
        *(v51 - 3) = *(v52 - 2);
        ptStatese = (struct ForestRender_States_t *)((char *)ptStatese + 1);
      }
      while ( (int)ptStatese < ptFaceGroup->nNumVertices );
    }
    v55 = 0;
    if ( ptFaceGroup->nNumFaces )
    {
      v56 = 0;
      do
      {
        ptSortedFaces = ptBSPTree->ptSortedFaces;
        v58 = ptSortedFaces[v56].tAveragePos.vX * ptMatrix->tZ.vX;
        aiIndices = (float *)ptSortedFaces[v56].tFace.aiIndices;
        ++v55;
        ++v56;
        aiIndices[6] = v58 + aiIndices[5] * ptMatrix->tZ.vZ + aiIndices[4] * ptMatrix->tZ.vY + ptDisplacement->vZ;
      }
      while ( v55 < ptFaceGroup->nNumFaces );
    }
  }
  qsort(ptBSPTree->ptSortVector, ptFaceGroup->nNumFaces, 4, ForestRender_SortedFacesCompare);
  result = 0;
  if ( ptFaceGroup->nNumFaces )
  {
    v61 = &igi2_frame.piIndices[igi2_frame.nIBOffset + 2];
    do
    {
      v62 = igi2_frame.nVBOffset;
      v61 += 3;
      *(v61 - 5) = igi2_frame.nVBOffset + ptBSPTree->ptSortVector[result]->tFace.aiIndices[0] - ptFaceGroup->iStartVertex;
      *(v61 - 4) = v62 + LOWORD(ptBSPTree->ptSortVector[result]->tFace.iIndex1) - ptFaceGroup->iStartVertex;
      *(v61 - 3) = v62 + LOWORD(ptBSPTree->ptSortVector[result++]->tFace.iIndex2) - ptFaceGroup->iStartVertex;
    }
    while ( result < ptFaceGroup->nNumFaces );
  }
  return result;
}

// source: e/3/pc/pc_forestrender.c:1366  [size]
void __cdecl ForestRender_DrawSortedFaceGroup(struct ForestRender_SortedFaceGroup_t *ptSortedFaceGroup)
{
  struct VirModel_s **v2; // edx
  struct VirModel_s **v3; // ecx
  struct VirModel_s *v4; // eax
  int iLOD; // ecx
  double v6; // st7
  struct Mesh3D_RenderMesh_RigidDirect3D_t *pxRenderMesh; // edx
  int iAlphaMorphLOD; // ecx
  int iAlphaMorphFaceGroup; // eax
  struct Mesh3D_RenderMesh_RigidDirect3D_t *v10; // edx
  struct real32x3_t *ptSortedFaceGroupa = *(struct real32x3_t * *)&ptSortedFaceGroup; // [esp+20h] [ebp+4h] ARGSLOT

  v2 = (struct VirModel_s **)(12 * dword_834DC0C + 129448764);
  v3 = (struct VirModel_s **)(12 * (dword_834DC0C ^ 1) + 129448764);
  LODWORD(g_ptRotationMatrix.tY.vY) = v2;
  LODWORD(g_ptRotationMatrix.tY.vZ) = v3;
  if ( ptSortedFaceGroup )
  {
    dword_7B73B40[3 * dword_834DC0C] = 1;
    v4 = ptSortedFaceGroup->ptLODVirModel->aptVirModel[0];
    *v2 = v4;
    if ( v4 != *v3 )
      Batch_Flush((unsigned int *)&g_ptStates, v3);
    iLOD = ptSortedFaceGroup->iLOD;
    v6 = 1.0 - ptSortedFaceGroup->vAlphaMorphFactor;
    pxRenderMesh = (struct Mesh3D_RenderMesh_RigidDirect3D_t *)ptSortedFaceGroup->ptLODVirModel->aptVirModel[iLOD]->ptModel->ptMesh->pxRenderMesh;
    ptSortedFaceGroupa = &ptSortedFaceGroup->tDisplacement;
    ForestRender_DrawSortedFaces(
      pxRenderMesh,
      &ptSortedFaceGroup->atBSPTree[iLOD].atMorphFaceGroups[ptSortedFaceGroup->iFaceGroup],
      &pxRenderMesh->ptFaceGroup[ptSortedFaceGroup->iFaceGroup],
      &ptSortedFaceGroup->atBSPTree[iLOD],
      (struct ForestRender_States_t *)LODWORD(g_ptRotationMatrix.tY.vY),
      (unsigned int *)&g_ptStates,
      &ptSortedFaceGroup->tOrientation,
      &ptSortedFaceGroup->tTranslation,
      &ptSortedFaceGroup->tMatrix,
      &ptSortedFaceGroup->tDisplacement,
      &ptSortedFaceGroup->tScale,
      ptSortedFaceGroup->vRadius,
      (__int64)(v6 * 255.0),
      ptSortedFaceGroup->bLight);
    iAlphaMorphLOD = ptSortedFaceGroup->iAlphaMorphLOD;
    if ( iAlphaMorphLOD >= 0 )
    {
      iAlphaMorphFaceGroup = ptSortedFaceGroup->iAlphaMorphFaceGroup;
      if ( iAlphaMorphFaceGroup >= 0 )
      {
        v10 = (struct Mesh3D_RenderMesh_RigidDirect3D_t *)ptSortedFaceGroup->ptLODVirModel->aptVirModel[iAlphaMorphLOD]->ptModel->ptMesh->pxRenderMesh;
        ForestRender_DrawSortedFaces(
          v10,
          &ptSortedFaceGroup->atBSPTree[iAlphaMorphLOD].atMorphFaceGroups[iAlphaMorphFaceGroup],
          &v10->ptFaceGroup[iAlphaMorphFaceGroup],
          &ptSortedFaceGroup->atBSPTree[iAlphaMorphLOD],
          (struct ForestRender_States_t *)LODWORD(g_ptRotationMatrix.tY.vY),
          (unsigned int *)&g_ptStates,
          &ptSortedFaceGroup->tOrientation,
          &ptSortedFaceGroup->tTranslation,
          &ptSortedFaceGroup->tMatrix,
          ptSortedFaceGroupa,
          &ptSortedFaceGroup->tScale,
          ptSortedFaceGroup->vRadius,
          (__int64)(ptSortedFaceGroup->vAlphaMorphFactor * 255.0),
          ptSortedFaceGroup->bLight);
      }
    }
    dword_834DC0C ^= 1u;
  }
  else
  {
    Batch_Flush((unsigned int *)&g_ptStates, (void *)(12 * (dword_834DC0C ^ 1) + 129448764));
  }
}

// source: e/3/pc/pc_forestrender.c:1460  [size~]
void __cdecl ForestRender_Draw(struct DrawForestContext_t *ptContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptTranslation; };
    struct { float ptTranslationa; };
    struct { float ptTranslationb; };
    struct { float ptTranslationc; };
    struct { char igi2_o4[4]; float vZ; };
    struct { char igi2_o5[24]; int vMorphRatio; };
    struct { char igi2_o6[28]; struct real32x9_t ptRotationMatrix; };
    struct { char igi2_o7[68]; unsigned int v41; };
    struct { char igi2_o8[72]; struct real32x9_t ptStates; };
    struct { char igi2_o9[112]; float v43; };
    struct { char igi2_o10[116]; float v44; };
    struct { char igi2_o11[120]; float v45; };
    struct { char igi2_o12[124]; int piMorphLOD; };
    struct { char igi2_o13[128]; float v47[10]; };
    struct { char igi2_o14[168]; float v48; };
    char igi2_extent[180];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct RigidDynCubeObj_t *ptRigidDynCubeObj; // ebp
  struct TransContext_s *ptTransContext; // ebx
  struct LODVirModel_s *ptLODVirModel; // edi
  int nLOD; // ecx
  enum ForestAction_e eAction; // eax
  __int32 v6; // eax
  int v7; // edx
  double v8; // st7
  int v9; // ecx
  double v10; // st6
  double v11; // st4
  unsigned int v12; // edx
  unsigned int v13; // edx
  double v14; // st5
  double v15; // st5
  enum Mesh3D_DrawMode_e eDrawMode; // eax
  double v17; // st4
  int v18; // ebp
  struct Mesh3D_RenderMesh_RigidDirect3D_t *v19; // ecx
  double v20; // st7
  double v21; // st6
  int v22; // ebx
  bool v23; // zf
  int nNumFaceGroups; // eax
  float vX; // edi
  char *v26; // eax
  float vY; // edx
  int nOps; // edx
  int v29; // edi
  int v30; // ebx
  unsigned int v31; // eax
  int v32; // eax
  struct MTP_BoneVertexRef_s *v33; // edi

  ptRigidDynCubeObj = ptContext->ptRigidDynCubeObj;
  ptTransContext = ptContext->ptTransContext;
  ptLODVirModel = ptContext->ptRigidDynCubeObj->tModelObj.ptLODVirModel;
  igi2_frame.vMorphRatio = -1;
  igi2_frame.ptRotationMatrix.nOps = -1;
  ForestRender_ptTransContext = ptTransContext;
  LODWORD(igi2_frame.ptRotationMatrix.tY.vY) = ptLODVirModel;
  if ( ptLODVirModel )
  {
    ForestRender_CreateBSPModel(ptContext, ptLODVirModel, (struct ForestRender_BSPTree_t **)&g_ptRotationMatrix.tZ);
    ptTransContext = ForestRender_ptTransContext;
  }
  else
  {
    LODWORD(igi2_frame.ptRotationMatrix.tY.vY) = MTP_ptMissingModel;
    ptLODVirModel = MTP_ptMissingModel;
  }
  nLOD = ptLODVirModel->nLOD;
  if ( !ptLODVirModel->nLOD )
    return;
  eAction = ptContext->eAction;
  if ( eAction )
  {
    v6 = eAction - 1;
    if ( v6 )
    {
      if ( v6 != 1 )
      {
        LDebug_Error("Forest renderer: command unknown");
        abort();
      }
      Batch_Flush((unsigned int *)&dword_834DC08, &g_ptRotationMatrix);
      Batch_Flush((unsigned int *)&dword_834DC04, &g_ptRotationMatrix);
      return;
    }
    if ( ptContext->eDrawMode )
    {
      igi2_frame.vMorphRatio = 0;
    }
    else
    {
      if ( ForestRender_isAlphaBlend )
        ForestRender_GetLOD(
          &ptRigidDynCubeObj->tModelObj,
          0.5,
          &igi2_frame.vMorphRatio,
          &igi2_frame.ptRotationMatrix.nOps,
          (float *)&igi2_frame.piMorphLOD);
      else
        igi2_frame.vMorphRatio = ModelObj_GetLOD(&ptRigidDynCubeObj->tModelObj);
      if ( igi2_frame.vMorphRatio == -1 )
        return;
    }
    v7 = BYTE1(ptContext->bLight);
    v8 = ptRigidDynCubeObj->tModelObj.tDynCubeObj.tQObj.tPos.vX - ptTransContext->tPos.vX;
    v9 = BYTE2(ptContext->bLight);
    igi2_frame.ptRotationMatrix.tY.vZ = v8;
    v10 = ptRigidDynCubeObj->tModelObj.tDynCubeObj.tQObj.tPos.vY - ptTransContext->tPos.vY;
    v11 = ptRigidDynCubeObj->tModelObj.tDynCubeObj.tQObj.tPos.vZ - ptTransContext->tPos.vZ;
    v12 = ((unsigned int)(unsigned __int8)ptContext->bLight + v7 + v9) / 3;
    igi2_frame.ptRotationMatrix.tY.vX = v11;
    igi2_frame.ptRotationMatrix.tY.vZ = Direct3D_vScale * igi2_frame.ptRotationMatrix.tY.vZ;
    v13 = (((unsigned __int8)v12 | ((unsigned __int8)v12 << 8)) << 8) | (unsigned __int8)v12;
    igi2_frame.ptRotationMatrix.tZ.vX = Direct3D_vScale * v10;
    qmemcpy(&igi2_frame.ptStates, &ptRigidDynCubeObj->tModelObj.tOrientation, sizeof(igi2_frame.ptStates));
    igi2_frame.ptRotationMatrix.tZ.vY = Direct3D_vScale * v11;
    v14 = Direct3D_vScale * ptRigidDynCubeObj->tModelObj.tScale.vX;
    igi2_frame.v41 = v13;
    igi2_frame.ptRotationMatrix.tX.vX = v14;
    igi2_frame.ptRotationMatrix.tX.vY = Direct3D_vScale * ptRigidDynCubeObj->tModelObj.tScale.vY;
    igi2_frame.ptRotationMatrix.tX.vZ = Direct3D_vScale * ptRigidDynCubeObj->tModelObj.tScale.vZ;
    igi2_frame.ptStates.tX.vX = igi2_frame.ptStates.tX.vX * igi2_frame.ptRotationMatrix.tX.vX;
    igi2_frame.ptStates.tX.vY = igi2_frame.ptStates.tX.vY * igi2_frame.ptRotationMatrix.tX.vY;
    igi2_frame.ptStates.tX.vZ = igi2_frame.ptStates.tX.vZ * igi2_frame.ptRotationMatrix.tX.vZ;
    igi2_frame.ptStates.tY.vX = igi2_frame.ptStates.tY.vX * igi2_frame.ptRotationMatrix.tX.vX;
    igi2_frame.ptStates.tY.vY = igi2_frame.ptStates.tY.vY * igi2_frame.ptRotationMatrix.tX.vY;
    igi2_frame.ptStates.tY.vZ = igi2_frame.ptStates.tY.vZ * igi2_frame.ptRotationMatrix.tX.vZ;
    igi2_frame.ptStates.tZ.vX = igi2_frame.ptStates.tZ.vX * igi2_frame.ptRotationMatrix.tX.vX;
    igi2_frame.ptStates.tZ.vY = igi2_frame.ptStates.tZ.vY * igi2_frame.ptRotationMatrix.tX.vY;
    igi2_frame.ptStates.tZ.vZ = igi2_frame.ptStates.tZ.vZ * igi2_frame.ptRotationMatrix.tX.vZ;
    igi2_frame.v47[0] = ptTransContext->tMatrix.tX.vY * ptRigidDynCubeObj->tModelObj.tOrientation.tY.vX
           + ptRigidDynCubeObj->tModelObj.tOrientation.tZ.vX * ptTransContext->tMatrix.tX.vZ
           + ptRigidDynCubeObj->tModelObj.tOrientation.tX.vX * ptTransContext->tMatrix.tX.vX;
    igi2_frame.v47[1] = ptTransContext->tMatrix.tX.vY * ptRigidDynCubeObj->tModelObj.tOrientation.tY.vY
           + ptRigidDynCubeObj->tModelObj.tOrientation.tX.vY * ptTransContext->tMatrix.tX.vX
           + ptRigidDynCubeObj->tModelObj.tOrientation.tZ.vY * ptTransContext->tMatrix.tX.vZ;
    igi2_frame.v47[2] = ptRigidDynCubeObj->tModelObj.tOrientation.tX.vZ * ptTransContext->tMatrix.tX.vX
           + ptRigidDynCubeObj->tModelObj.tOrientation.tZ.vZ * ptTransContext->tMatrix.tX.vZ
           + ptTransContext->tMatrix.tX.vY * ptRigidDynCubeObj->tModelObj.tOrientation.tY.vZ;
    igi2_frame.v47[3] = ptTransContext->tMatrix.tY.vX * ptRigidDynCubeObj->tModelObj.tOrientation.tX.vX
           + ptRigidDynCubeObj->tModelObj.tOrientation.tZ.vX * ptTransContext->tMatrix.tY.vZ
           + ptTransContext->tMatrix.tY.vY * ptRigidDynCubeObj->tModelObj.tOrientation.tY.vX;
    igi2_frame.v47[4] = ptRigidDynCubeObj->tModelObj.tOrientation.tZ.vY * ptTransContext->tMatrix.tY.vZ
           + ptRigidDynCubeObj->tModelObj.tOrientation.tY.vY * ptTransContext->tMatrix.tY.vY
           + ptRigidDynCubeObj->tModelObj.tOrientation.tX.vY * ptTransContext->tMatrix.tY.vX;
    igi2_frame.v47[5] = ptRigidDynCubeObj->tModelObj.tOrientation.tZ.vZ * ptTransContext->tMatrix.tY.vZ
           + ptRigidDynCubeObj->tModelObj.tOrientation.tY.vZ * ptTransContext->tMatrix.tY.vY
           + ptRigidDynCubeObj->tModelObj.tOrientation.tX.vZ * ptTransContext->tMatrix.tY.vX;
    igi2_frame.v47[6] = ptTransContext->tMatrix.tZ.vY * ptRigidDynCubeObj->tModelObj.tOrientation.tY.vX
           + ptRigidDynCubeObj->tModelObj.tOrientation.tX.vX * ptTransContext->tMatrix.tZ.vX
           + ptTransContext->tMatrix.tZ.vZ * ptRigidDynCubeObj->tModelObj.tOrientation.tZ.vX;
    igi2_frame.v47[7] = ptTransContext->tMatrix.tZ.vZ * ptRigidDynCubeObj->tModelObj.tOrientation.tZ.vY
           + ptTransContext->tMatrix.tZ.vY * ptRigidDynCubeObj->tModelObj.tOrientation.tY.vY
           + ptRigidDynCubeObj->tModelObj.tOrientation.tX.vY * ptTransContext->tMatrix.tZ.vX;
    v15 = ptRigidDynCubeObj->tModelObj.tOrientation.tX.vZ * ptTransContext->tMatrix.tZ.vX
        + ptTransContext->tMatrix.tZ.vZ * ptRigidDynCubeObj->tModelObj.tOrientation.tZ.vZ;
    LODWORD(igi2_frame.v47[9]) = ptTransContext->tMatrix.nOps + ptRigidDynCubeObj->tModelObj.tOrientation.nOps + 1;
    eDrawMode = ptContext->eDrawMode;
    v17 = ptTransContext->tMatrix.tZ.vY * ptRigidDynCubeObj->tModelObj.tOrientation.tY.vZ;
    v18 = igi2_frame.vMorphRatio;
    v19 = (struct Mesh3D_RenderMesh_RigidDirect3D_t *)*(&g_ptStates.isAlphaBlend + igi2_frame.vMorphRatio);
    igi2_frame.v47[8] = v15 + v17;
    igi2_frame.v48 = v8;
    igi2_frame.v43 = igi2_frame.ptRotationMatrix.tY.vX * ptTransContext->tMatrix.tX.vZ
        + igi2_frame.v48 * ptTransContext->tMatrix.tX.vX
        + v10 * ptTransContext->tMatrix.tX.vY;
    igi2_frame.v44 = igi2_frame.v48 * ptTransContext->tMatrix.tY.vX
        + igi2_frame.ptRotationMatrix.tY.vX * ptTransContext->tMatrix.tY.vZ
        + v10 * ptTransContext->tMatrix.tY.vY;
    v20 = igi2_frame.v48 * ptTransContext->tMatrix.tZ.vX + igi2_frame.ptRotationMatrix.tY.vX * ptTransContext->tMatrix.tZ.vZ;
    v21 = v10 * ptTransContext->tMatrix.tZ.vY;
    v22 = 0;
    v23 = eDrawMode == MESH3D_DRAWMODE_NORMAL;
    nNumFaceGroups = v19->nNumFaceGroups;
    igi2_frame.v45 = v20 + v21;
    if ( v23 )
    {
      if ( nNumFaceGroups > 0 )
      {
        LODWORD(vX) = 156 * igi2_frame.vMorphRatio;
        LODWORD(igi2_frame.ptRotationMatrix.tY.vX) = 156 * igi2_frame.vMorphRatio;
        igi2_frame.ptRotationMatrix.tZ.vZ = 0.0;
        while ( 1 )
        {
          if ( v22 == *(_DWORD *)(LODWORD(vX) + LODWORD(g_ptRotationMatrix.tZ.vX) + 4) )
          {
            if ( ForestRender_isAlphaBlend )
            {
              igi2_frame.vZ = igi2_frame.v47[8] * *(float *)((char *)&v19->ptFaceGroup->tAveragePos.vZ + LODWORD(igi2_frame.ptRotationMatrix.tZ.vZ))
                 + igi2_frame.v47[7] * *(float *)((char *)&v19->ptFaceGroup->tAveragePos.vY + LODWORD(igi2_frame.ptRotationMatrix.tZ.vZ))
                 + igi2_frame.v47[6] * *(float *)((char *)&v19->ptFaceGroup->tAveragePos.vX + LODWORD(igi2_frame.ptRotationMatrix.tZ.vZ))
                 + igi2_frame.v45;
              v26 = (char *)SortRender_AllocItem((void (__cdecl *)(void *))ForestRender_DrawSortedFaceGroup, 152, igi2_frame.vZ);
              vY = igi2_frame.ptRotationMatrix.tY.vY;
              *((_DWORD *)v26 + 37) = igi2_frame.piMorphLOD;
              qmemcpy(v26 + 44, &igi2_frame.ptStates, 0x28u);
              *((_DWORD *)v26 + 5) = LODWORD(igi2_frame.ptRotationMatrix.tY.vZ);
              *((_DWORD *)v26 + 6) = LODWORD(igi2_frame.ptRotationMatrix.tZ.vX);
              *((_DWORD *)v26 + 7) = LODWORD(igi2_frame.ptRotationMatrix.tZ.vY);
              *(struct real32x3_t *)(v26 + 8) = igi2_frame.ptRotationMatrix.tX;
              *(float *)v26 = vY;
              nOps = igi2_frame.ptRotationMatrix.nOps;
              *((_DWORD *)v26 + 33) = v18;
              *((_DWORD *)v26 + 31) = v22;
              *((_DWORD *)v26 + 34) = nOps;
              *((float *)v26 + 36) = ptContext->ptRigidDynCubeObj->tModelObj.tDynCubeObj.tQObj.vRealRadius
                                   * igi2_frame.ptRotationMatrix.tX.vX;
              *((_DWORD *)v26 + 1) = LODWORD(g_ptRotationMatrix.tZ.vX);
              qmemcpy(v26 + 84, igi2_frame.v47, 0x28u);
              vX = igi2_frame.ptRotationMatrix.tY.vX;
              *((float *)v26 + 8) = igi2_frame.v43;
              *((float *)v26 + 9) = igi2_frame.v44;
              *((float *)v26 + 10) = igi2_frame.v45;
              v18 = igi2_frame.vMorphRatio;
              *((_DWORD *)v26 + 35) = ptContext->bLight;
              if ( nOps >= 0 )
                *((_DWORD *)v26 + 32) = *(_DWORD *)(156 * nOps + LODWORD(g_ptRotationMatrix.tZ.vX) + 4);
            }
            else
            {
              igi2_frame.ptTranslation = ptContext->ptRigidDynCubeObj->tModelObj.tDynCubeObj.tQObj.vRealRadius
                            * igi2_frame.ptRotationMatrix.tX.vX;
              ForestRender_DrawFoliageFaceGroup(
                v19,
                (struct ForestRender_Morph_t *)(LODWORD(vX) + LODWORD(g_ptRotationMatrix.tZ.vX) + 20),
                v22,
                nullptr,
                &g_ptRotationMatrix,
                &igi2_frame.ptStates.tX,
                &igi2_frame.ptRotationMatrix.tX,
                igi2_frame.ptTranslation,
                ptContext->bLight,
                (int)&igi2_frame.ptRotationMatrix.tY.vZ);
            }
          }
          else
          {
            igi2_frame.ptTranslationa = ptContext->ptRigidDynCubeObj->tModelObj.tDynCubeObj.tQObj.vRealRadius
                           * igi2_frame.ptRotationMatrix.tX.vX;
            ForestRender_DrawTrunkFaceGroup(
              v19,
              (struct ForestRender_Morph_t *)(LODWORD(vX) + LODWORD(g_ptRotationMatrix.tZ.vX) + 20),
              v22,
              (struct ForestRender_States_t *)&g_ptRotationMatrix,
              &igi2_frame.ptStates,
              (struct real32x3_t *)&igi2_frame.ptRotationMatrix.tY.vZ,
              &igi2_frame.ptRotationMatrix.tX,
              igi2_frame.ptTranslationa,
              v13,
              0);
          }
          LODWORD(igi2_frame.ptRotationMatrix.tZ.vZ) += 32;
          v19 = (struct Mesh3D_RenderMesh_RigidDirect3D_t *)*(&g_ptStates.isAlphaBlend + v18);
          if ( ++v22 >= v19->nNumFaceGroups )
            break;
          v13 = igi2_frame.v41;
        }
      }
    }
    else
    {
      v29 = 0;
      if ( nNumFaceGroups > 0 )
      {
        v30 = 156 * igi2_frame.vMorphRatio;
        while ( 1 )
        {
          if ( v29 == *(_DWORD *)(v30 + LODWORD(g_ptRotationMatrix.tZ.vX) + 4) )
          {
            v31 = ptContext->eDrawMode == MESH3D_DRAWMODE_LIGHTMAP ? -16777216 : ptContext->bLight | 0xFF000000;
            igi2_frame.ptTranslationb = ptContext->ptRigidDynCubeObj->tModelObj.tDynCubeObj.tQObj.vRealRadius
                           * igi2_frame.ptRotationMatrix.tX.vX;
            ForestRender_DrawFoliageFaceGroup(
              v19,
              (struct ForestRender_Morph_t *)(v30 + LODWORD(g_ptRotationMatrix.tZ.vX) + 20),
              v29,
              nullptr,
              &g_ptRotationMatrix,
              &igi2_frame.ptStates.tX,
              &igi2_frame.ptRotationMatrix.tX,
              igi2_frame.ptTranslationb,
              v31,
              (int)&igi2_frame.ptRotationMatrix.tY.vZ);
          }
          else
          {
            igi2_frame.ptTranslationc = ptContext->ptRigidDynCubeObj->tModelObj.tDynCubeObj.tQObj.vRealRadius
                           * igi2_frame.ptRotationMatrix.tX.vX;
            ForestRender_DrawTrunkFaceGroup(
              v19,
              (struct ForestRender_Morph_t *)(v30 + LODWORD(g_ptRotationMatrix.tZ.vX) + 20),
              v29,
              (struct ForestRender_States_t *)&g_ptRotationMatrix,
              &igi2_frame.ptStates,
              (struct real32x3_t *)&igi2_frame.ptRotationMatrix.tY.vZ,
              &igi2_frame.ptRotationMatrix.tX,
              igi2_frame.ptTranslationc,
              ptContext->eDrawMode != MESH3D_DRAWMODE_LIGHTMAP ? v13 : 0,
              0);
            v18 = igi2_frame.vMorphRatio;
          }
          v19 = (struct Mesh3D_RenderMesh_RigidDirect3D_t *)*(&g_ptStates.isAlphaBlend + v18);
          if ( ++v29 >= v19->nNumFaceGroups )
            break;
          v13 = igi2_frame.v41;
        }
      }
    }
  }
  else
  {
    g_ptRotationMatrix.tX.vY = 0.0;
    LODWORD(g_ptRotationMatrix.tX.vZ) = ptContext->eDrawMode;
    LODWORD(g_ptRotationMatrix.tX.vX) = ptLODVirModel->aptVirModel[0];
    v32 = 0;
    g_ptRotationMatrix.tY.vX = (ModelObj_vLODBias * 16.0 + 1.0) * (ModelObj_vLODBias * 16.0 + 1.0);
    if ( nLOD > 0 )
    {
      v33 = &ptLODVirModel[-688].atBoneVertexRefs[26].atVertexRefs[254];
      do
      {
        *(&g_ptStates.isAlphaBlend + v32) = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(*(int *)((char *)&g_ptStates.isAlphaBlend
                                                                                       + (_DWORD)&v33[v32])
                                                                              + 12)
                                                                  + 12)
                                                      + 36);
        ++v32;
      }
      while ( v32 < nLOD );
    }
  }
}

// source: e/3/pc/pc_forestrender.c:1704  [size]
enum bool __cdecl ForestRender_EnableHighQualityForest(enum bool isHighQuality)
{
  ForestRender_isAlphaBlend = isHighQuality;
  return isHighQuality;
}

// source: e/3/pc/pc_forestrender.c:1717  [size]
enum bool __cdecl ForestRender_EnableWindOnForest(enum bool isWind)
{
  ForestRender_isWind = isWind;
  return isWind;
}

// source: e/3/pc/pc_forestrender.c:1730  [size]
struct Mesh3D_Mesh_t *__cdecl ForestRender_UnloadModel(struct Mesh3D_Mesh_t *ptMesh)
{
  struct Mesh3D_Mesh_t *result; // eax
  int v3; // ebp
  struct ForestRender_BSPLODModel_t *i; // esi
  struct LODVirModel_s *v5; // ebx
  int nLOD; // ecx
  int v7; // eax
  _DWORD *v8; // ebp
  int v9; // eax
  int v10; // esi
  int v11; // esi
  struct Mesh3D_Mesh_t *v12; // ecx
  _DWORD *v13; // ebx
  int v14; // esi
  int j; // ecx
  int iLOD; // [esp+8h] [ebp-10h]
  int iLODModel; // [esp+Ch] [ebp-Ch]
  int v18; // [esp+10h] [ebp-8h]
  struct LODVirModel_s *ptLODVirModel; // [esp+14h] [ebp-4h]

  result = (struct Mesh3D_Mesh_t *)tBSPStorage.nNumModels;
  v3 = 0;
  iLODModel = 0;
  if ( tBSPStorage.nNumModels > 0 )
  {
    for ( i = tBSPStorage.atBSPModels; ; ++i )
    {
      v5 = i->ptLODVirModel;
      nLOD = i->ptLODVirModel->nLOD;
      v7 = 0;
      ptLODVirModel = i->ptLODVirModel;
      if ( nLOD > 0 )
      {
        do
        {
          if ( v5->aptVirModel[v7]->ptModel->ptMesh == ptMesh )
            break;
          ++v7;
        }
        while ( v7 < nLOD );
        v3 = iLODModel;
      }
      if ( v7 < nLOD )
        break;
      result = (struct Mesh3D_Mesh_t *)tBSPStorage.nNumModels;
      iLODModel = ++v3;
      if ( v3 >= tBSPStorage.nNumModels )
        return result;
    }
    iLOD = 0;
    if ( v5->nLOD > 0 )
    {
      v8 = (_DWORD *)(784 * v3 + 129448840);
      do
      {
        v9 = *(v8 - 1);
        if ( v9 )
        {
          v10 = *(_DWORD *)((v9 - 4) & 0xFFFFFFFC);
          --Mem_nCurrentAllocations;
          Node_Remove((_DWORD **)v10);
          memset(*(void **)(v10 + 8), 0xCDu, *(_DWORD *)(v10 + 16));
          free((void *)v10);
          *(v8 - 1) = 0;
        }
        if ( *v8 )
        {
          v11 = *(_DWORD *)((*v8 - 4) & 0xFFFFFFFC);
          --Mem_nCurrentAllocations;
          Node_Remove((_DWORD **)v11);
          memset(*(void **)(v11 + 8), 0xCDu, *(_DWORD *)(v11 + 16));
          free((void *)v11);
          *v8 = 0;
        }
        v12 = v5->aptVirModel[iLOD]->ptModel->ptMesh;
        if ( *((int *)v12->pxRenderMesh + 2) > 0 )
        {
          v13 = v8 + 17;
          v18 = *((_DWORD *)v12->pxRenderMesh + 2);
          do
          {
            if ( *v13 )
            {
              v14 = *(_DWORD *)((*v13 - 4) & 0xFFFFFFFC);
              --Mem_nCurrentAllocations;
              Node_Remove((_DWORD **)v14);
              memset(*(void **)(v14 + 8), 0xCDu, *(_DWORD *)(v14 + 16));
              free((void *)v14);
              *v13 = 0;
            }
            v13 += 17;
            --v18;
          }
          while ( v18 );
          v5 = ptLODVirModel;
        }
        v8 += 39;
        ++iLOD;
      }
      while ( iLOD < v5->nLOD );
      v3 = iLODModel;
    }
    --tBSPStorage.nNumModels;
    qmemcpy((void *)(784 * v3 + 129448820), (void *)(784 * tBSPStorage.nNumModels + 129448820), 0x310u);
    tBSPStorage.atBSPModels[tBSPStorage.nNumModels].ptLODVirModel = nullptr;
    for ( j = 0; j < 5; ++j )
    {
      tBSPStorage.atBSPModels[tBSPStorage.nNumModels].atLOD[j].ptSortedFaces = nullptr;
      tBSPStorage.atBSPModels[tBSPStorage.nNumModels].atLOD[j].ptSortVector = nullptr;
      for ( result = nullptr; (int)result < 136; result = (struct Mesh3D_Mesh_t *)((char *)result + 68) )
        *(int *)((char *)&tBSPStorage.atBSPModels[0].atLOD[0].atMorphFaceGroups[0].anMorphChannelVertices[16]
               + (_DWORD)result
               + 784 * tBSPStorage.nNumModels
               + j * 156) = 0;
    }
  }
  return result;
}

// source: e/3/pc/pc_forestrender.c:1831  [size]
void __cdecl ForestRender_Close()
{
  struct RenderStateBlock_t *v0; // eax
  int v1; // edx
  int v2; // ecx
  int v3; // edx
  struct RenderStateBlock_t *v4; // eax
  int v5; // ecx
  int v6; // edx
  int v7; // esi

  v0 = Direct3D_ptTextureStateBlock;
  v1 = ForestRender_eTextureState_AlphaBlendFoliage;
  Direct3D_ptTextureStateBlock->atRenderState[ForestRender_eTextureState_Trunk].pfCallback = nullptr;
  v2 = ForestRender_eTextureState_AlphaTestFoliage;
  v0->atRenderState[v1].pfCallback = nullptr;
  v3 = ForestRender_eGenericState_Trunk;
  v0->atRenderState[v2].pfCallback = nullptr;
  v4 = Direct3D_ptGenericStateBlock;
  v5 = ForestRender_eGenericState_AlphaBlendFoliage;
  Direct3D_ptGenericStateBlock->atRenderState[v3].pfCallback = nullptr;
  v6 = ForestRender_eGenericState_AlphaTestFoliage;
  v4->atRenderState[v5].pfCallback = nullptr;
  v4->atRenderState[v6].pfCallback = nullptr;
  if ( ForestRender_atMorphBuffer )
  {
    v7 = *(_DWORD *)((unsigned int)&ForestRender_atMorphBuffer[-1].vZ & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v7);
    memset(*(void **)(v7 + 8), 0xCDu, *(_DWORD *)(v7 + 16));
    free((void *)v7);
    ForestRender_atMorphBuffer = nullptr;
  }
}
