/* e/3/pc/pc_billboard.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: e/3/pc/pc_billboard.c:58  [size]
void __cdecl Billboard_SetTextureState(void *pxContext)
{
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_MINFILTER, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_MAGFILTER, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ADDRESSU, 3u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ADDRESSV, 3u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_MIPFILTER, 1u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_TEXCOORDINDEX, 0);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAOP, 4u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAARG1, 0);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAARG2, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLOROP, 4u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLORARG1, 0);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLORARG2, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_TEXTURETRANSFORMFLAGS, 0);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_COLOROP, 1u);
}

// source: e/3/pc/pc_billboard.c:84  [size]
void __cdecl Billboard_SetStates(struct Batch_SetStatesContext_s *ptContext)
{
  int v1; // ecx
  void *pxUserContext; // esi
  struct RenderStateBlock_t *v3; // eax
  struct RenderStateBlock_t *v4; // eax
  int v5; // ecx
  struct RenderStateBlock_t *v6; // ecx
  int v7; // edx
  int v8; // ecx
  struct RenderStateBlock_t *v9; // eax

  v1 = Billboard_eTextureState;
  pxUserContext = ptContext->pxUserContext;
  v3 = Direct3D_ptTextureStateBlock;
  if ( Direct3D_ptTextureStateBlock->eCurrentState != Billboard_eTextureState )
  {
    Direct3D_ptTextureStateBlock->eCurrentState = Billboard_eTextureState;
    v3->atRenderState[v1].pfCallback(nullptr);
  }
  v4 = Direct3D_ptGenericStateBlock;
  v5 = Direct3DRender_eGenericStateRigid;
  if ( Direct3D_ptGenericStateBlock->eCurrentState != Direct3DRender_eGenericStateRigid )
  {
    Direct3D_ptGenericStateBlock->eCurrentState = Direct3DRender_eGenericStateRigid;
    v4->atRenderState[v5].pfCallback(nullptr);
    v4 = Direct3D_ptGenericStateBlock;
  }
  v6 = Direct3D_ptClippingStateBlock;
  v7 = Direct3D_eClippingStateOn;
  if ( Direct3D_ptClippingStateBlock->eCurrentState != Direct3D_eClippingStateOn )
  {
    Direct3D_ptClippingStateBlock->eCurrentState = Direct3D_eClippingStateOn;
    v6->atRenderState[v7].pfCallback(nullptr);
    v4 = Direct3D_ptGenericStateBlock;
  }
  v8 = Direct3DRender_eBlendStateTransparent;
  v4->eCurrentState = -1;
  v9 = Direct3D_ptBlendStateBlock;
  if ( Direct3D_ptBlendStateBlock->eCurrentState != v8 )
  {
    Direct3D_ptBlendStateBlock->eCurrentState = v8;
    v9->atRenderState[v8].pfCallback(nullptr);
  }
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZWRITEENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_LIGHTING, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGENABLE, 0);
  if ( *(struct IDirect3DBaseTexture8 **)(*(_DWORD *)pxUserContext + 36) != Direct3D_tState.aptTexture[0] )
  {
    Direct3D_tState.aptTexture[0] = *(struct IDirect3DBaseTexture8 **)(*(_DWORD *)pxUserContext + 36);
    Direct3D_ptDevice->lpVtbl->SetTexture(Direct3D_ptDevice, 0, Direct3D_tState.aptTexture[0]);
  }
}

// source: e/3/pc/pc_billboard.c:118  [size]
void __cdecl Billboard_DrawSorted(struct Billboard_t *ptBillboard)
{
  #pragma pack(push, 1)
  union
  {
    struct { __int64 v29; };
    struct { char igi2_o1[8]; unsigned __int16 aiIndices[6]; };
    struct { char igi2_o2[20]; int iVertexBufferPosition; };
    struct { char igi2_o3[24]; char *pLockedVertices; };
    struct { char igi2_o4[28]; struct real32x3_t tTemp; };
    struct { char igi2_o5[40]; struct real32x9_t tTempMatrix; };
    struct { char igi2_o6[80]; struct Billboard_Vertex_t atVertices[4]; };
    char igi2_extent[176];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  void *v1; // ecx
  struct TexInfo_s **v2; // eax
  struct TexInfo_s *ptTexture; // edx
  char *v4; // edx
  double v5; // st7
  double v6; // st6
  double v7; // st5
  double v8; // st6
  float vY; // eax
  float vX; // ecx
  double v11; // st6
  double v12; // st5
  double v13; // st6
  double v14; // st6
  float v15; // eax
  float v16; // ecx
  double v17; // st6
  double v18; // st5
  double v19; // st6
  double v20; // st6
  float v21; // eax
  float v22; // ecx
  double v23; // st6
  double v24; // st5
  double v25; // st5
  double v26; // st7
  unsigned int v27; // ecx
  int v28; // eax

  v1 = (void *)(4 * dword_834DAE4 + 137630900);
  v2 = (struct TexInfo_s **)(4 * (dword_834DAE4 ^ 1) + 137630900);
  igi2_frame.atVertices[0].tUV.vX = 0.0;
  igi2_frame.atVertices[0].tUV.vY = 1.0;
  igi2_frame.atVertices[1].tUV.vX = 1.0;
  igi2_frame.atVertices[1].tUV.vY = 1.0;
  igi2_frame.atVertices[2].tUV.vX = 0.0;
  igi2_frame.atVertices[2].tUV.vY = 0.0;
  igi2_frame.atVertices[3].tUV.vX = 1.0;
  igi2_frame.atVertices[3].tUV.vY = 0.0;
  igi2_frame.aiIndices[0] = 0;
  igi2_frame.aiIndices[1] = 2;
  igi2_frame.aiIndices[2] = 1;
  igi2_frame.aiIndices[3] = 1;
  igi2_frame.aiIndices[4] = 2;
  igi2_frame.aiIndices[5] = 3;
  dword_83414B0 = (int)v1;
  dword_83414C0 = (int)v2;
  if ( ptBillboard )
  {
    ptTexture = ptBillboard->ptTexture;
    dword_83414B4[dword_834DAE4] = ptTexture;
    if ( ptTexture != *v2 )
    {
      Batch_Flush((unsigned int *)&dword_83414BC, v2);
      v1 = (void *)dword_83414B0;
    }
    Batch_GetLockedVertex(
      BATCH_XYZDIFFUSETEX1,
      BATCH_INDEX16,
      4,
      2,
      1,
      igi2_frame.aiIndices,
      0,
      Billboard_SetStates,
      nullptr,
      v1,
      (unsigned __int8 **)&igi2_frame.pLockedVertices,
      &igi2_frame.iVertexBufferPosition,
      (unsigned int *)&dword_83414BC);
    v4 = &igi2_frame.pLockedVertices[24 * igi2_frame.iVertexBufferPosition];
    qmemcpy(&igi2_frame.tTempMatrix, &TransContext_tActiveTransContext, sizeof(igi2_frame.tTempMatrix));
    igi2_frame.tTempMatrix.tX.vX = igi2_frame.tTempMatrix.tX.vX * Direct3D_vScale;
    igi2_frame.tTempMatrix.tX.vY = igi2_frame.tTempMatrix.tX.vY * Direct3D_vScale;
    igi2_frame.tTempMatrix.tX.vZ = igi2_frame.tTempMatrix.tX.vZ * Direct3D_vScale;
    igi2_frame.tTempMatrix.tY.vX = igi2_frame.tTempMatrix.tY.vX * Direct3D_vScale;
    igi2_frame.tTempMatrix.tY.vY = igi2_frame.tTempMatrix.tY.vY * Direct3D_vScale;
    igi2_frame.tTempMatrix.tY.vZ = igi2_frame.tTempMatrix.tY.vZ * Direct3D_vScale;
    igi2_frame.tTemp = igi2_frame.tTempMatrix.tY;
    igi2_frame.tTempMatrix.tZ.vY = igi2_frame.tTempMatrix.tZ.vY * Direct3D_vScale;
    igi2_frame.tTempMatrix.tZ.vZ = igi2_frame.tTempMatrix.tZ.vZ * Direct3D_vScale;
    *(float *)igi2_frame.aiIndices = ptBillboard->tSize.vX * -1.0;
    *(float *)&igi2_frame.aiIndices[4] = ptBillboard->tSize.vY * 0.0;
    v5 = igi2_frame.tTempMatrix.tZ.vX * Direct3D_vScale * 0.0;
    v6 = igi2_frame.tTempMatrix.tY.vX * *(float *)&igi2_frame.aiIndices[4] + *(float *)igi2_frame.aiIndices * igi2_frame.tTempMatrix.tX.vX + v5;
    *(float *)&igi2_frame.pLockedVertices = igi2_frame.tTempMatrix.tZ.vY * 0.0;
    v7 = igi2_frame.tTempMatrix.tY.vY * *(float *)&igi2_frame.aiIndices[4]
       + *(float *)igi2_frame.aiIndices * igi2_frame.tTempMatrix.tX.vY
       + *(float *)&igi2_frame.pLockedVertices;
    *(float *)&igi2_frame.iVertexBufferPosition = igi2_frame.tTempMatrix.tZ.vZ * 0.0;
    *(float *)&igi2_frame.aiIndices[4] = igi2_frame.tTempMatrix.tY.vZ * *(float *)&igi2_frame.aiIndices[4]
                            + *(float *)igi2_frame.aiIndices * igi2_frame.tTempMatrix.tX.vZ
                            + *(float *)&igi2_frame.iVertexBufferPosition;
    *(float *)v4 = v6 + ptBillboard->tTranslation.vX;
    *((float *)v4 + 1) = v7 + ptBillboard->tTranslation.vY;
    *((float *)v4 + 2) = *(float *)&igi2_frame.aiIndices[4] + ptBillboard->tTranslation.vZ;
    v8 = (ptBillboard->vAlphaTop - ptBillboard->vAlphaBottom) * 0.0 + ptBillboard->vAlphaBottom;
    if ( v8 >= 1.0 )
      v8 = 1.0;
    vY = igi2_frame.atVertices[0].tUV.vY;
    *((_DWORD *)v4 + 3) = (__int64)(ptBillboard->tColor.vZ * 255.0)
                        | (((unsigned int)(__int64)(ptBillboard->tColor.vY * 255.0)
                          | (((unsigned int)(__int64)(ptBillboard->tColor.vX * 255.0)
                            | ((unsigned int)(__int64)(255.0 * v8) << 8)) << 8)) << 8);
    vX = igi2_frame.atVertices[0].tUV.vX;
    *((float *)v4 + 5) = vY;
    *((float *)v4 + 4) = vX;
    v11 = ptBillboard->tSize.vX;
    v12 = ptBillboard->tSize.vY * 0.0;
    *(float *)igi2_frame.aiIndices = igi2_frame.tTemp.vX * v12 + v11 * igi2_frame.tTempMatrix.tX.vX + v5;
    *(float *)&igi2_frame.aiIndices[2] = igi2_frame.tTemp.vY * v12 + v11 * igi2_frame.tTempMatrix.tX.vY + *(float *)&igi2_frame.pLockedVertices;
    v13 = igi2_frame.tTemp.vZ * v12 + v11 * igi2_frame.tTempMatrix.tX.vZ + *(float *)&igi2_frame.iVertexBufferPosition;
    *((float *)v4 + 6) = *(float *)igi2_frame.aiIndices + ptBillboard->tTranslation.vX;
    *((float *)v4 + 7) = *(float *)&igi2_frame.aiIndices[2] + ptBillboard->tTranslation.vY;
    *((float *)v4 + 8) = v13 + ptBillboard->tTranslation.vZ;
    v14 = (ptBillboard->vAlphaTop - ptBillboard->vAlphaBottom) * 0.0 + ptBillboard->vAlphaBottom;
    if ( v14 >= 1.0 )
      v14 = 1.0;
    v15 = igi2_frame.atVertices[1].tUV.vY;
    *((_DWORD *)v4 + 9) = (__int64)(ptBillboard->tColor.vZ * 255.0)
                        | (((unsigned int)(__int64)(ptBillboard->tColor.vY * 255.0)
                          | (((unsigned int)(__int64)(ptBillboard->tColor.vX * 255.0)
                            | ((unsigned int)(__int64)(255.0 * v14) << 8)) << 8)) << 8);
    v16 = igi2_frame.atVertices[1].tUV.vX;
    *((float *)v4 + 11) = v15;
    *((float *)v4 + 10) = v16;
    v17 = ptBillboard->tSize.vX * -1.0;
    v18 = ptBillboard->tSize.vY * -1.0;
    *(float *)igi2_frame.aiIndices = igi2_frame.tTemp.vX * v18 + v17 * igi2_frame.tTempMatrix.tX.vX + v5;
    *(float *)&igi2_frame.aiIndices[2] = igi2_frame.tTemp.vY * v18 + v17 * igi2_frame.tTempMatrix.tX.vY + *(float *)&igi2_frame.pLockedVertices;
    v19 = igi2_frame.tTemp.vZ * v18 + v17 * igi2_frame.tTempMatrix.tX.vZ + *(float *)&igi2_frame.iVertexBufferPosition;
    *((float *)v4 + 12) = *(float *)igi2_frame.aiIndices + ptBillboard->tTranslation.vX;
    *((float *)v4 + 13) = *(float *)&igi2_frame.aiIndices[2] + ptBillboard->tTranslation.vY;
    *((float *)v4 + 14) = v19 + ptBillboard->tTranslation.vZ;
    v20 = ptBillboard->vAlphaTop - ptBillboard->vAlphaBottom + ptBillboard->vAlphaBottom;
    if ( v20 >= 1.0 )
      v20 = 1.0;
    v21 = igi2_frame.atVertices[2].tUV.vY;
    *((_DWORD *)v4 + 15) = (__int64)(ptBillboard->tColor.vZ * 255.0)
                         | (((unsigned int)(__int64)(ptBillboard->tColor.vY * 255.0)
                           | (((unsigned int)(__int64)(ptBillboard->tColor.vX * 255.0)
                             | ((unsigned int)(__int64)(255.0 * v20) << 8)) << 8)) << 8);
    v22 = igi2_frame.atVertices[2].tUV.vX;
    *((float *)v4 + 17) = v21;
    *((float *)v4 + 16) = v22;
    v23 = ptBillboard->tSize.vX;
    v24 = ptBillboard->tSize.vY * -1.0;
    *(float *)igi2_frame.aiIndices = igi2_frame.tTemp.vX * v24 + v23 * igi2_frame.tTempMatrix.tX.vX + v5;
    *(float *)&igi2_frame.aiIndices[2] = igi2_frame.tTemp.vY * v24 + v23 * igi2_frame.tTempMatrix.tX.vY + *(float *)&igi2_frame.pLockedVertices;
    v25 = igi2_frame.tTemp.vZ * v24 + v23 * igi2_frame.tTempMatrix.tX.vZ + *(float *)&igi2_frame.iVertexBufferPosition;
    *((float *)v4 + 18) = *(float *)igi2_frame.aiIndices + ptBillboard->tTranslation.vX;
    *((float *)v4 + 19) = *(float *)&igi2_frame.aiIndices[2] + ptBillboard->tTranslation.vY;
    *((float *)v4 + 20) = v25 + ptBillboard->tTranslation.vZ;
    v26 = ptBillboard->vAlphaTop - ptBillboard->vAlphaBottom + ptBillboard->vAlphaBottom;
    if ( v26 >= 1.0 )
      v26 = 1.0;
    v27 = ((unsigned int)(__int64)(ptBillboard->tColor.vY * 255.0)
         | (((unsigned int)(__int64)(ptBillboard->tColor.vX * 255.0) | ((unsigned int)(__int64)(255.0 * v26) << 8)) << 8)) << 8;
    igi2_frame.v29 = (__int64)(ptBillboard->tColor.vZ * 255.0);
    *((_DWORD *)v4 + 23) = LODWORD(igi2_frame.atVertices[3].tUV.vY);
    v28 = dword_834DAE4;
    *((_DWORD *)v4 + 21) = igi2_frame.v29 | v27;
    *((_DWORD *)v4 + 22) = LODWORD(igi2_frame.atVertices[3].tUV.vX);
    dword_834DAE4 = v28 ^ 1;
  }
  else
  {
    Batch_Flush((unsigned int *)&dword_83414BC, (void *)(4 * (dword_834DAE4 ^ 1) + 137630900));
  }
}

// source: e/3/pc/pc_billboard.c:221  [size]
void __cdecl Billboard_Open()
{
  struct RenderStateBlock_t *v0; // ecx
  int nNumStates; // eax

  v0 = Direct3D_ptTextureStateBlock;
  nNumStates = Direct3D_ptTextureStateBlock->nNumStates;
  Direct3D_ptTextureStateBlock->nNumStates = nNumStates + 1;
  v0->atRenderState[nNumStates].pfCallback = Billboard_SetTextureState;
  Billboard_eTextureState = nNumStates;
}

// source: e/3/pc/pc_billboard.c:235  [anchor-hash]
void __cdecl Billboard_Close()
{
  Direct3D_ptTextureStateBlock->atRenderState[Billboard_eTextureState].pfCallback = nullptr;
}
