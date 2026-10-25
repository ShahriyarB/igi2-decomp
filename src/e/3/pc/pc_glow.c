/* e/3/pc/pc_glow.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: e/3/pc/pc_glow.c:56  [size]
void __cdecl Glow_SetStates(struct Batch_SetStatesContext_s *ptContext)
{
  struct RenderStateBlock_t *v1; // eax
  int v2; // ecx
  struct RenderStateBlock_t *v3; // eax
  int v4; // ecx
  struct RenderStateBlock_t *v5; // ecx
  int v6; // edx
  int v7; // ecx
  struct RenderStateBlock_t *v8; // eax

  v1 = Direct3D_ptTextureStateBlock;
  v2 = Direct3DRender_eTextureStateRigid;
  if ( Direct3D_ptTextureStateBlock->eCurrentState != Direct3DRender_eTextureStateRigid )
  {
    Direct3D_ptTextureStateBlock->eCurrentState = Direct3DRender_eTextureStateRigid;
    v1->atRenderState[v2].pfCallback(nullptr);
  }
  v3 = Direct3D_ptGenericStateBlock;
  v4 = Direct3DRender_eGenericStateRigid;
  if ( Direct3D_ptGenericStateBlock->eCurrentState != Direct3DRender_eGenericStateRigid )
  {
    Direct3D_ptGenericStateBlock->eCurrentState = Direct3DRender_eGenericStateRigid;
    v3->atRenderState[v4].pfCallback(nullptr);
    v3 = Direct3D_ptGenericStateBlock;
  }
  v5 = Direct3D_ptClippingStateBlock;
  v6 = Direct3D_eClippingStateOn;
  if ( Direct3D_ptClippingStateBlock->eCurrentState != Direct3D_eClippingStateOn )
  {
    Direct3D_ptClippingStateBlock->eCurrentState = Direct3D_eClippingStateOn;
    v5->atRenderState[v6].pfCallback(nullptr);
    v3 = Direct3D_ptGenericStateBlock;
  }
  v7 = Direct3DRender_eBlendStateAdditive;
  v3->eCurrentState = -1;
  v8 = Direct3D_ptBlendStateBlock;
  if ( Direct3D_ptBlendStateBlock->eCurrentState != v7 )
  {
    Direct3D_ptBlendStateBlock->eCurrentState = v7;
    v8->atRenderState[v7].pfCallback(nullptr);
  }
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZWRITEENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_LIGHTING, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGENABLE, 0);
  if ( tGlowTexture.tTexInfo.ptDirect3DBaseTexture != Direct3D_tState.aptTexture[0] )
  {
    Direct3D_tState.aptTexture[0] = tGlowTexture.tTexInfo.ptDirect3DBaseTexture;
    Direct3D_ptDevice->lpVtbl->SetTexture(Direct3D_ptDevice, 0, tGlowTexture.tTexInfo.ptDirect3DBaseTexture);
  }
}

// source: e/3/pc/pc_glow.c:87  [size]
void __cdecl Glow_DrawSorted(struct Glow_SortedGlow_t *ptGlow)
{
  #pragma pack(push, 1)
  union
  {
    struct { int iVertexBufferPosition; };
    struct { char igi2_o1[4]; int vLimit; };
    struct { char igi2_o2[8]; unsigned __int16 aiIndices[6]; };
    struct { char igi2_o3[20]; __int64 pLockedVertices; };
    struct { char igi2_o4[28]; float v26; };
    struct { char igi2_o5[32]; struct real32x9_t tTempMatrix; };
    struct { char igi2_o6[72]; struct GlowVertex_t atVertices[4]; };
    char igi2_extent[168];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v1; // ecx
  int v2; // ebp
  unsigned int v3; // edx
  unsigned int v4; // edx
  int v5; // edx
  double v6; // st7
  long double v7; // st6
  double v8; // st7
  double v9; // st6
  double v10; // st7
  char *v11; // esi
  char *v12; // edi
  struct GlowVertex_t *v13; // ecx
  int v14; // eax
  double v15; // st7
  int v16; // ebp
  double v17; // st6
  double v18; // st6
  double v19; // st5
  double v20; // st6
  int v21; // ebp

  igi2_frame.atVertices[0].tPos.vX = -1.0;
  igi2_frame.atVertices[0].tPos.vY = 0.0;
  igi2_frame.atVertices[0].tPos.vZ = -1.0;
  igi2_frame.atVertices[0].bColor = 0;
  igi2_frame.atVertices[0].tUV.vX = 0.0;
  igi2_frame.atVertices[0].tUV.vY = 0.0;
  igi2_frame.atVertices[1].tPos.vX = 1.0;
  igi2_frame.atVertices[1].tPos.vY = 0.0;
  igi2_frame.atVertices[1].tPos.vZ = -1.0;
  igi2_frame.atVertices[1].bColor = 0;
  igi2_frame.atVertices[1].tUV.vX = 1.0;
  igi2_frame.atVertices[1].tUV.vY = 0.0;
  igi2_frame.atVertices[2].tPos.vX = -1.0;
  igi2_frame.atVertices[2].tPos.vY = 0.0;
  igi2_frame.atVertices[2].tPos.vZ = 1.0;
  igi2_frame.atVertices[2].bColor = 0;
  igi2_frame.atVertices[2].tUV.vX = 0.0;
  igi2_frame.atVertices[2].tUV.vY = 1.0;
  igi2_frame.atVertices[3].tPos.vX = 1.0;
  igi2_frame.atVertices[3].tPos.vY = 0.0;
  igi2_frame.atVertices[3].tPos.vZ = 1.0;
  igi2_frame.atVertices[3].bColor = 0;
  igi2_frame.atVertices[3].tUV.vX = 1.0;
  igi2_frame.atVertices[3].tUV.vY = 1.0;
  igi2_frame.aiIndices[0] = 0;
  igi2_frame.aiIndices[1] = 1;
  igi2_frame.aiIndices[2] = 2;
  igi2_frame.aiIndices[3] = 1;
  igi2_frame.aiIndices[4] = 3;
  igi2_frame.aiIndices[5] = 2;
  if ( ptGlow )
  {
    *(float *)&igi2_frame.vLimit = Direct3D_vScale * 409.6000061035156;
    Batch_GetLockedVertex(
      BATCH_XYZDIFFUSETEX1,
      BATCH_INDEX16,
      4,
      2,
      1,
      igi2_frame.aiIndices,
      0,
      Glow_SetStates,
      nullptr,
      nullptr,
      (unsigned __int8 **)&igi2_frame.pLockedVertices,
      &igi2_frame.iVertexBufferPosition,
      (unsigned int *)&dword_7DDD430);
    v1 = igi2_frame.pLockedVertices;
    igi2_frame.pLockedVertices = (__int64)(ptGlow->tColor.vX * 255.0);
    v2 = v1 + 24 * igi2_frame.iVertexBufferPosition;
    v3 = ((unsigned __int8)igi2_frame.pLockedVertices | 0xFFFFFF00) << 8;
    igi2_frame.pLockedVertices = (__int64)(ptGlow->tColor.vY * 255.0);
    v4 = ((unsigned int)igi2_frame.pLockedVertices | v3) << 8;
    igi2_frame.pLockedVertices = (__int64)(ptGlow->tColor.vZ * 255.0);
    v5 = igi2_frame.pLockedVertices | v4;
    v6 = Direct3D_vScale * ptGlow->vRadius;
    v7 = sqrt(
           ptGlow->tTranslation.vX * ptGlow->tTranslation.vX
         + ptGlow->tTranslation.vY * ptGlow->tTranslation.vY
         + ptGlow->tTranslation.vZ * ptGlow->tTranslation.vZ);
    *(float *)&igi2_frame.iVertexBufferPosition = v7;
    if ( v7 >= *(float *)&igi2_frame.vLimit )
    {
      if ( *(float *)&igi2_frame.vLimit + v6 > *(float *)&igi2_frame.iVertexBufferPosition )
        v6 = *(float *)&igi2_frame.iVertexBufferPosition - *(float *)&igi2_frame.vLimit;
      v8 = (*(float *)&igi2_frame.iVertexBufferPosition - v6) / *(float *)&igi2_frame.iVertexBufferPosition;
    }
    else
    {
      v8 = 1.0;
    }
    v9 = v8 * ptGlow->tTranslation.vX;
    igi2_frame.vLimit = 4;
    ptGlow->tTranslation.vX = v9;
    ptGlow->tTranslation.vY = v8 * ptGlow->tTranslation.vY;
    ptGlow->tTranslation.vZ = v8 * ptGlow->tTranslation.vZ;
    qmemcpy(&igi2_frame.tTempMatrix, &TransContext_tActiveTransContext, sizeof(igi2_frame.tTempMatrix));
    v10 = v8 * Direct3D_vScale * ptGlow->vRadius;
    igi2_frame.tTempMatrix.tX.vX = igi2_frame.tTempMatrix.tX.vX * v10;
    v11 = (char *)igi2_frame.atVertices - v2;
    v12 = (char *)&igi2_frame.atVertices[0].tPos.vZ - v2;
    igi2_frame.tTempMatrix.tX.vY = igi2_frame.tTempMatrix.tX.vY * v10;
    igi2_frame.tTempMatrix.tX.vZ = igi2_frame.tTempMatrix.tX.vZ * v10;
    igi2_frame.tTempMatrix.tY.vX = igi2_frame.tTempMatrix.tY.vX * v10;
    igi2_frame.tTempMatrix.tY.vY = igi2_frame.tTempMatrix.tY.vY * v10;
    v13 = igi2_frame.atVertices;
    igi2_frame.tTempMatrix.tY.vZ = igi2_frame.tTempMatrix.tY.vZ * v10;
    *(struct real32x3_t *)igi2_frame.aiIndices = igi2_frame.tTempMatrix.tY;
    v14 = v2 + 8;
    igi2_frame.tTempMatrix.tZ.vX = igi2_frame.tTempMatrix.tZ.vX * v10;
    igi2_frame.tTempMatrix.tZ.vY = igi2_frame.tTempMatrix.tZ.vY * v10;
    v15 = v10 * igi2_frame.tTempMatrix.tZ.vZ;
    do
    {
      v16 = *(_DWORD *)&v12[v14];
      v17 = igi2_frame.tTempMatrix.tZ.vX * v13->tPos.vY;
      ++v13;
      v14 += 24;
      v18 = v17 + igi2_frame.tTempMatrix.tX.vX * v13[-1].tPos.vX + *(float *)igi2_frame.aiIndices * *(float *)&v11[v14 - 24];
      v19 = igi2_frame.tTempMatrix.tZ.vY * v13[-1].tPos.vY
          + igi2_frame.tTempMatrix.tX.vY * v13[-1].tPos.vX
          + *(float *)&igi2_frame.aiIndices[2] * *(float *)&v11[v14 - 24];
      igi2_frame.v26 = v15 * v13[-1].tPos.vY
          + igi2_frame.tTempMatrix.tX.vZ * v13[-1].tPos.vX
          + *(float *)&igi2_frame.aiIndices[4] * *(float *)&v11[v14 - 24];
      *(float *)(v14 - 32) = v18 + ptGlow->tTranslation.vX;
      *(float *)(v14 - 28) = v19 + ptGlow->tTranslation.vY;
      v20 = igi2_frame.v26 + ptGlow->tTranslation.vZ;
      *(_DWORD *)(v14 - 16) = v16;
      *(_DWORD *)(v14 - 12) = *(_DWORD *)&v12[v14 - 20];
      v21 = igi2_frame.vLimit;
      *(float *)(v14 - 24) = v20;
      *(_DWORD *)(v14 - 20) = v5;
      igi2_frame.vLimit = v21 - 1;
    }
    while ( v21 != 1 );
  }
  else
  {
    Batch_Flush((unsigned int *)&dword_7DDD430, nullptr);
  }
}
