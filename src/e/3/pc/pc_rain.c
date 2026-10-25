/* e/3/pc/pc_rain.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: e/3/pc/pc_rain.c:273  [anchor-hash]
void __cdecl Rain_DestroyCallback()
{
  if ( Rain_ptActiveTask )
    Rain_ptActiveTask->ptVertexBuffer->lpVtbl->Release(Rain_ptActiveTask->ptVertexBuffer);
}

// source: e/3/pc/pc_rain.c:297  [anchor-hash]
void __cdecl Rain_RestoreCallback()
{
  if ( Rain_ptActiveTask )
    Direct3D_ptDevice->lpVtbl->CreateVertexBuffer(
      Direct3D_ptDevice,
      1474560u,
      520u,
      322u,
      D3DPOOL_DEFAULT,
      &Rain_ptActiveTask->ptVertexBuffer);
}

// source: e/3/pc/pc_rain.c:332  [anchor-mhash]
void __cdecl Rain_UpdateVertexBuffer(struct Rain_s *ptRain)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vSnowSizeX; };
    struct { char igi2_o1[4]; float vSnowSizeY; };
    struct { char igi2_o2[8]; int i; };
    struct { char igi2_o3[12]; int iParticle; };
    struct { char igi2_o4[20]; float tTempPos; };
    struct { char igi2_o5[32]; struct real32x3_t Real32x3_Rotate_tTemp; };
    struct { char igi2_o6[44]; struct RainFlexibleVertex_s *aptRainVerts[4]; };
    char igi2_extent[60];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  enum RainMode_e eRainMode; // eax
  int nRainRGBA; // esi
  int nActiveParticles; // eax
  struct RainParticle_s *atRainParticle; // ecx
  struct RainParticle_s *v6; // ebx
  int v7; // edx
  struct IDirect3DVertexBuffer8 *ptVertexBuffer; // eax
  int v9; // eax
  struct RainParticleSystem_s *v10; // ecx
  int v11; // edx
  int iParticleSystem; // ecx
  struct RainFlexibleVertex_s *v13; // eax
  float *p_vY; // edx
  double v15; // st7
  double v16; // st6
  double v17; // st5
  double vX; // st4
  double v19; // st7
  double v20; // st6
  double v21; // st5
  double v22; // st6
  double v23; // st6
  bool v24; // cc
  double vZ; // st7
  double v26; // st7
  double v27; // st7
  int ptRaina = *(int *)&ptRain; // [esp+54h] [ebp+4h] ARGSLOT

  eRainMode = ptRain->eRainMode;
  igi2_frame.vSnowSizeX = (double)(2 * (eRainMode != RAINMODE_SNOW) + 1) * ptRain->vFade * 81.91999816894531;
  igi2_frame.vSnowSizeY = (double)(eRainMode != RAINMODE_SNOW ? 10 : 1) * ptRain->vFade * 81.91999816894531;
  if ( eRainMode == RAINMODE_SNOW )
  {
    nRainRGBA = -1;
    ptRaina = -1;
  }
  else
  {
    ptRaina = ptRain->nRainRGBA;
    nRainRGBA = ptRain->nRainRGBA;
  }
  nActiveParticles = ptRain->nActiveParticles;
  atRainParticle = ptRain->atRainParticle;
  v6 = ptRain->atRainParticle;
  if ( nActiveParticles > 1 )
  {
    v7 = nActiveParticles - 1;
    do
    {
      if ( atRainParticle->tPos.vZ > (double)v6->tPos.vZ )
        v6 = atRainParticle;
      ++atRainParticle;
      --v7;
    }
    while ( v7 );
  }
  ptVertexBuffer = ptRain->ptVertexBuffer;
  igi2_frame.aptRainVerts[0] = nullptr;
  if ( !ptVertexBuffer->lpVtbl->Lock(ptVertexBuffer, 0, 0, (unsigned __int8 **)igi2_frame.aptRainVerts, 0x2000u) )
  {
    ptRain->atParticleSystems[0].nParticle = 0;
    v9 = 1;
    v10 = &ptRain->atParticleSystems[1];
    do
    {
      v11 = *((_DWORD *)&igi2_frame.Real32x3_Rotate_tTemp.vZ + v9++) + 11520 * ptRain->nDensity;
      *((_DWORD *)&igi2_frame.Real32x3_Rotate_tTemp.vZ + v9) = v11;
      v10->nParticle = 0;
      ++v10;
    }
    while ( v9 < 4 );
    for ( igi2_frame.iParticle = 0; igi2_frame.iParticle < ptRain->nActiveParticles; ++igi2_frame.iParticle )
    {
      iParticleSystem = v6->iParticleSystem;
      v13 = igi2_frame.aptRainVerts[iParticleSystem];
      igi2_frame.i = 0;
      if ( ptRain->nDensity > 0 )
      {
        p_vY = &Rain_atRainOffset[0].vY;
        do
        {
          igi2_frame.tTempPos = *(p_vY - 1) + v6->tPos.vX;
          v15 = *p_vY + v6->tPos.vY;
          v16 = p_vY[1] + v6->tPos.vZ;
          igi2_frame.Real32x3_Rotate_tTemp.vX = TransContext_tActiveTransContext.tMatrix.tX.vZ * v16
                                   + TransContext_tActiveTransContext.tMatrix.tX.vY * v15
                                   + TransContext_tActiveTransContext.tMatrix.tX.vX * igi2_frame.tTempPos;
          igi2_frame.Real32x3_Rotate_tTemp.vY = TransContext_tActiveTransContext.tMatrix.tY.vZ * v16
                                   + TransContext_tActiveTransContext.tMatrix.tY.vY * v15
                                   + TransContext_tActiveTransContext.tMatrix.tY.vX * igi2_frame.tTempPos;
          v17 = TransContext_tActiveTransContext.tMatrix.tZ.vZ * v16
              + TransContext_tActiveTransContext.tMatrix.tZ.vY * v15;
          vX = TransContext_tActiveTransContext.tMatrix.tZ.vX;
          v13->nRGBA = nRainRGBA;
          v13[1].nRGBA = nRainRGBA;
          v13[2].nRGBA = nRainRGBA;
          v13[3].nRGBA = nRainRGBA;
          v13->vU = 0.0;
          v13->vV = 0.0;
          v19 = v17 + vX * igi2_frame.tTempPos;
          v13[1].vU = 1.0;
          v13[1].vV = 0.0;
          v13[2].vU = 0.0;
          v20 = igi2_frame.Real32x3_Rotate_tTemp.vX - igi2_frame.vSnowSizeX;
          v13[2].vV = 1.0;
          v13[3].vU = 1.0;
          v13[3].vV = 1.0;
          v13->vX = v20;
          v21 = igi2_frame.Real32x3_Rotate_tTemp.vX + igi2_frame.vSnowSizeX;
          v13[1].vX = v21;
          v13[2].vX = v20;
          v13[3].vX = v21;
          v22 = igi2_frame.Real32x3_Rotate_tTemp.vY - igi2_frame.vSnowSizeY;
          v13->vY = v22;
          v13[1].vY = v22;
          v23 = igi2_frame.Real32x3_Rotate_tTemp.vY + igi2_frame.vSnowSizeY;
          v13[2].vY = v23;
          v13[3].vY = v23;
          v13[1].vZ = v19;
          qmemcpy(&v13[4], &v13[1], sizeof(struct RainFlexibleVertex_s));
          v13[2].vZ = v19;
          v13->vZ = v19;
          v13[3].vZ = v19;
          qmemcpy(&v13[5], &v13[2], sizeof(struct RainFlexibleVertex_s));
          v13 += 6;
          p_vY += 3;
          v24 = igi2_frame.i + 1 < ptRain->nDensity;
          nRainRGBA = ptRaina;
          ++igi2_frame.i;
        }
        while ( v24 );
      }
      if ( --v6 < ptRain->atRainParticle )
        v6 += ptRain->nActiveParticles;
      igi2_frame.aptRainVerts[iParticleSystem] = v13;
      ptRain->atParticleSystems[iParticleSystem].avZ[ptRain->atParticleSystems[iParticleSystem].nParticle++] = v6->tPos.vZ;
    }
    ptRain->ptVertexBuffer->lpVtbl->Unlock(ptRain->ptVertexBuffer);
    ptRain->tMatrix._11 = TransContext_tActiveTransContext.tMatrix.tX.vX * Direct3D_vScale;
    ptRain->tMatrix._12 = TransContext_tActiveTransContext.tMatrix.tX.vY * Direct3D_vScale;
    vZ = TransContext_tActiveTransContext.tMatrix.tX.vZ;
    ptRain->tMatrix._14 = 0.0;
    ptRain->tMatrix._13 = vZ * Direct3D_vScale;
    ptRain->tMatrix._21 = TransContext_tActiveTransContext.tMatrix.tY.vX * Direct3D_vScale;
    ptRain->tMatrix._22 = TransContext_tActiveTransContext.tMatrix.tY.vY * Direct3D_vScale;
    v26 = TransContext_tActiveTransContext.tMatrix.tY.vZ;
    ptRain->tMatrix._24 = 0.0;
    ptRain->tMatrix._23 = v26 * Direct3D_vScale;
    ptRain->tMatrix._31 = TransContext_tActiveTransContext.tMatrix.tZ.vX * Direct3D_vScale;
    ptRain->tMatrix._32 = TransContext_tActiveTransContext.tMatrix.tZ.vY * Direct3D_vScale;
    v27 = TransContext_tActiveTransContext.tMatrix.tZ.vZ;
    ptRain->tMatrix._34 = 0.0;
    ptRain->tMatrix._33 = v27 * Direct3D_vScale;
  }
}

// source: e/3/pc/pc_rain.c:503  [anchor-mhash]
void __cdecl Rain_SortRenderCallbackVB(void *pxData)
{
  double *v2; // ebx
  int v3; // esi
  double v4; // st7
  double v5; // st6
  double v6; // st7
  int v7; // edi
  int v8; // edi
  struct RenderStateBlock_t *v9; // ecx
  struct RenderStateBlock_t *v10; // edx
  int v11; // eax
  struct IDirect3DBaseTexture8 *v12; // eax
  double v13; // st7
  double v14; // st7
  int nParticle; // ebx
  float *v16; // edx
  int v17; // eax
  int v18; // ecx
  struct IDirect3DVertexBuffer8 *X; // [esp+14Ch] [ebp-28h]
  struct RainParticleSystem_s *ptParticleSystem; // [esp+168h] [ebp-Ch]
  int i; // [esp+16Ch] [ebp-8h]
  float pxDataa = *(float *)&pxData; // [esp+178h] [ebp+4h] ARGSLOT

  if ( pxData && Rain_isEnabled )
  {
    v2 = *((double **)pxData + 1);
    v3 = *(_DWORD *)pxData;
    if ( v2[2] <= v2[98] )
      v4 = v2[98];
    else
      v4 = v2[2];
    if ( v2[6] <= v2[102] )
      v5 = v2[102];
    else
      v5 = v2[6];
    if ( v4 <= v5 )
    {
      if ( v2[6] <= v2[102] )
        v6 = v2[102];
      else
        v6 = v2[6];
    }
    else if ( v2[2] <= v2[98] )
    {
      v6 = v2[98];
    }
    else
    {
      v6 = v2[2];
    }
    pxDataa = v6 - *((double *)pxData + 1) - 73728.0;
    v7 = 2 * ((__int64)floor(v2[1] * 0.00009178218688807207) & 1);
    v8 = (__int64)floor(*v2 * 0.00009178218688807207) & 1 | v7;
    Direct3D_ptTextureStateBlock->eCurrentState = -1;
    v9 = Direct3D_ptGenericStateBlock;
    ptParticleSystem = (struct RainParticleSystem_s *)(324 * v8 + v3 + 116);
    Direct3D_ptBlendStateBlock->eCurrentState = -1;
    v10 = Direct3D_ptClippingStateBlock;
    v9->eCurrentState = -1;
    v10->eCurrentState = -1;
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHABLENDENABLE, 1u);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SRCBLEND, 5u);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_DESTBLEND, 6u);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGENABLE, 0);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZENABLE, Direct3D_bZBufferMode);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZBIAS, 0);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZFUNC, 2u);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZWRITEENABLE, 0);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_CULLMODE, 1u);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SPECULARENABLE, 0);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_LIGHTING, 0);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_DITHERENABLE, 0);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHATESTENABLE, 0);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_CLIPPING, 1u);
    v11 = *(_DWORD *)(v3 + 22108);
    if ( v11 )
    {
      v12 = *(struct IDirect3DBaseTexture8 **)(v11 + 36);
      if ( v12 != Direct3D_tState.aptTexture[0] )
      {
        Direct3D_tState.aptTexture[0] = v12;
        Direct3D_ptDevice->lpVtbl->SetTexture(Direct3D_ptDevice, 0, v12);
      }
      Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLOROP, 4u);
      Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAOP, 4u);
    }
    else
    {
      Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLOROP, 3u);
      Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAOP, 3u);
    }
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLORARG1, 2u);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLORARG2, 0);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAARG1, 2u);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAARG2, 0);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_MAGFILTER, 2u);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_MINFILTER, 1u);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_COLOROP, 1u);
    X = *(struct IDirect3DVertexBuffer8 **)(v3 + 22244);
    *(float *)(v3 + 22160) = (*v2 - TransContext_tActiveTransContext.tPos.vX) * Direct3D_vScale;
    *(float *)(v3 + 22164) = (v2[1] - TransContext_tActiveTransContext.tPos.vY) * Direct3D_vScale;
    v13 = *((double *)pxData + 1) - TransContext_tActiveTransContext.tPos.vZ;
    *(_DWORD *)(v3 + 22172) = 1065353216;
    *(float *)(v3 + 22168) = (v13 + 73728.0) * Direct3D_vScale;
    Direct3D_tState.aptStreamData[0] = X;
    Direct3D_tState.anStride[0] = 24;
    Direct3D_ptDevice->lpVtbl->SetStreamSource(Direct3D_ptDevice, 0, X, 24u);
    Direct3D_tState.nHandle = 322;
    Direct3D_ptDevice->lpVtbl->SetVertexShader(Direct3D_ptDevice, 322u);
    for ( i = 3; i; --i )
    {
      *(float *)(v3 + 22168) = *(float *)(v3 + 22168) - Direct3D_vScale * 24576.0;
      v14 = pxDataa + 24576.0;
      pxDataa = v14;
      if ( v14 >= 0.0 )
      {
        if ( pxDataa > 24576.0 )
          continue;
        nParticle = 0;
        v16 = (float *)(324 * v8 + v3 + 120);
        if ( ptParticleSystem->nParticle <= 0 )
          continue;
        do
        {
          if ( *v16 <= (double)pxDataa )
            break;
          ++v16;
          ++nParticle;
        }
        while ( nParticle < ptParticleSystem->nParticle );
      }
      else
      {
        nParticle = ptParticleSystem->nParticle;
      }
      if ( nParticle )
      {
        Direct3D_ptDevice->lpVtbl->SetTransform(
          Direct3D_ptDevice,
          (enum _D3DTRANSFORMSTATETYPE)256,
          (struct _D3DMATRIX *)(v3 + 22112));
        Direct3D_ptDevice->lpVtbl->DrawPrimitive(
          Direct3D_ptDevice,
          D3DPT_TRIANGLELIST,
          480 * v8 * *(_DWORD *)(v3 + 22252),
          2 * nParticle * *(_DWORD *)(v3 + 22252));
        v17 = nParticle * *(_DWORD *)(v3 + 22252);
        v18 = *(_DWORD *)(v3 + 22260);
        ++*(_DWORD *)(v3 + 22256);
        *(_DWORD *)(v3 + 22260) = v17 + v18;
      }
    }
  }
}

// source: e/3/pc/pc_rain.c:671  [anchor-mhash]
struct Rain_s *__cdecl Rain_ComputeGridOutcodes(struct Rain_s *ptRain, double vZ)
{
  double nWidth; // st7
  double nHeight; // st6
  double v4; // st4
  struct RainVertex_s *v5; // edx
  int v6; // edi
  int v7; // esi
  double v8; // st3
  double v9; // st2
  double v10; // st2
  double v11; // st3
  int v12; // ecx
  int v13; // eax
  char v14; // al
  int v15; // ecx
  double v16; // st3
  double v17; // st2
  double v18; // st2
  double v19; // st3
  int v20; // ecx
  struct Rain_s *result; // eax
  int v22; // eax
  float tScreenPos; // [esp+0h] [ebp-3Ch]
  float tScreenPosa; // [esp+0h] [ebp-3Ch]
  float tCameraPos; // [esp+8h] [ebp-34h]
  float tCameraPos_4; // [esp+Ch] [ebp-30h]
  float tCameraPos_8; // [esp+10h] [ebp-2Ch]
  float tCameraPos2; // [esp+14h] [ebp-28h]
  float tCameraPos2_4; // [esp+18h] [ebp-24h]
  float tCameraPos2_8; // [esp+1Ch] [ebp-20h]
  float Real32x3_Rotate_tTemp; // [esp+20h] [ebp-1Ch]
  float Real32x3_Rotate_tTemp_8; // [esp+28h] [ebp-14h]
  float v33; // [esp+2Ch] [ebp-10h]
  float v34; // [esp+34h] [ebp-8h]

  nWidth = (double)Display_tActiveMode.nWidth;
  nHeight = (double)Display_tActiveMode.nHeight;
  v4 = vZ + 73728.0;
  v5 = &ptRain->atRainVert[24 * ptRain->iArrayX + 25 + ptRain->iArrayY];
  v6 = 10;
  do
  {
    v7 = 10;
    do
    {
      tCameraPos = v5->tPos.vX - TransContext_tActiveTransContext.tPos.vX;
      tCameraPos_4 = v5->tPos.vY - TransContext_tActiveTransContext.tPos.vY;
      tCameraPos_8 = vZ - TransContext_tActiveTransContext.tPos.vZ;
      v33 = TransContext_tActiveTransContext.tMatrix.tX.vZ * tCameraPos_8
          + TransContext_tActiveTransContext.tMatrix.tX.vY * tCameraPos_4
          + TransContext_tActiveTransContext.tMatrix.tX.vX * tCameraPos;
      v8 = TransContext_tActiveTransContext.tMatrix.tY.vZ * tCameraPos_8
         + TransContext_tActiveTransContext.tMatrix.tY.vY * tCameraPos_4
         + TransContext_tActiveTransContext.tMatrix.tY.vX * tCameraPos;
      v9 = TransContext_tActiveTransContext.tMatrix.tZ.vZ * tCameraPos_8
         + TransContext_tActiveTransContext.tMatrix.tZ.vY * tCameraPos_4
         + TransContext_tActiveTransContext.tMatrix.tZ.vX * tCameraPos;
      v34 = v9;
      if ( v9 <= 0.0 )
      {
        v14 = -2;
        if ( v33 <= 0.0 )
          v14 = -5;
        v12 = v14 & 0x3F;
        v13 = -3;
        if ( v8 <= 0.0 )
          v13 = -9;
      }
      else
      {
        v10 = 1.0 / v34;
        v11 = v8 * TransContext_tActiveTransContext.vScreenFOVY * v10 + TransContext_tActiveTransContext.vScreenOriginY;
        tScreenPos = TransContext_tActiveTransContext.vScreenFOVX * v33 * v10
                   + TransContext_tActiveTransContext.vScreenOriginX;
        v12 = ~(4 * (tScreenPos < nWidth)) & ~(2 * (v11 > 0.0)) & ~(tScreenPos > 0.0) & 0x3F;
        if ( v11 >= nHeight )
          v13 = -17;
        else
          v13 = -25;
      }
      v15 = v13 & v12;
      tCameraPos2 = v5->tPos.vX - TransContext_tActiveTransContext.tPos.vX;
      tCameraPos2_4 = v5->tPos.vY - TransContext_tActiveTransContext.tPos.vY;
      tCameraPos2_8 = v4 - TransContext_tActiveTransContext.tPos.vZ;
      Real32x3_Rotate_tTemp = (v4 - TransContext_tActiveTransContext.tPos.vZ)
                            * TransContext_tActiveTransContext.tMatrix.tX.vZ
                            + tCameraPos2_4 * TransContext_tActiveTransContext.tMatrix.tX.vY
                            + tCameraPos2 * TransContext_tActiveTransContext.tMatrix.tX.vX;
      v16 = tCameraPos2_8 * TransContext_tActiveTransContext.tMatrix.tY.vZ
          + tCameraPos2_4 * TransContext_tActiveTransContext.tMatrix.tY.vY
          + tCameraPos2 * TransContext_tActiveTransContext.tMatrix.tY.vX;
      v17 = tCameraPos2_8 * TransContext_tActiveTransContext.tMatrix.tZ.vZ
          + tCameraPos2_4 * TransContext_tActiveTransContext.tMatrix.tZ.vY
          + tCameraPos2 * TransContext_tActiveTransContext.tMatrix.tZ.vX;
      Real32x3_Rotate_tTemp_8 = v17;
      if ( v17 <= 0.0 )
      {
        v22 = -2;
        if ( Real32x3_Rotate_tTemp <= 0.0 )
          v22 = -5;
        v20 = v22 & v15;
        result = (struct Rain_s *)-3;
        if ( v16 <= 0.0 )
          result = (struct Rain_s *)-9;
      }
      else
      {
        v18 = 1.0 / Real32x3_Rotate_tTemp_8;
        tScreenPosa = Real32x3_Rotate_tTemp * TransContext_tActiveTransContext.vScreenFOVX * v18
                    + TransContext_tActiveTransContext.vScreenOriginX;
        v19 = v16 * TransContext_tActiveTransContext.vScreenFOVY * v18 + TransContext_tActiveTransContext.vScreenOriginY;
        v20 = ~(4 * (tScreenPosa < nWidth)) & ~(2 * (v19 > 0.0)) & ~(tScreenPosa > 0.0) & v15;
        if ( v19 >= nHeight )
          result = (struct Rain_s *)-17;
        else
          result = (struct Rain_s *)-25;
      }
      v5->nOutCode = (unsigned int)result & v20;
      ++v5;
      --v7;
      v5[-1].vZ = (Real32x3_Rotate_tTemp_8 + v34) * 0.5;
    }
    while ( v7 );
    v5 += 14;
    --v6;
  }
  while ( v6 );
  return result;
}

// source: e/3/pc/pc_rain.c:767  [anchor-mhash]
void __cdecl Rain_UpdateGridPosition(struct Rain_s *ptRain)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct World_s *ptWorld; };
    struct { char igi2_o1[48]; int iX; };
    struct { char igi2_o2[48]; float iXa; };
    struct { char igi2_o3[52]; int nYPos; };
    struct { char igi2_o4[56]; double vYPos2; };
    struct { char igi2_o5[56]; __int64 vYPos2a; };
    struct { char igi2_o6[64]; double vXPos; };
    struct { char igi2_o7[72]; double vXPos2; };
    struct { char igi2_o8[80]; int nXPosMod; };
    struct { char igi2_o9[88]; struct CollisionEvaluateContext_s tEvaluateContext; };
    struct { char igi2_o10[96]; double vYPos; };
    struct { char igi2_o11[104]; double vTraceLineLength; };
    struct { char igi2_o12[112]; struct QIntersection_s tIntersection; };
    char igi2_extent[236];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct RainVertex_s *atRainVert; // ebp
  int v2; // edi
  int v3; // esi
  char isLastCameraPosValid; // al
  double v5; // st7
  double v6; // st6
  __int16 v7; // cx
  int vZ_low; // edx
  bool v9; // cc

  atRainVert = ptRain->atRainVert;
  v2 = (__int64)floor((TransContext_tActiveTransContext.tPos.vX - 59924.48193359375) * 0.00009178218688807207 + 0.5);
  igi2_frame.vYPos2a = (__int64)floor((TransContext_tActiveTransContext.tPos.vY - 59924.48193359375) * 0.00009178218688807207 + 0.5);
  igi2_frame.nXPosMod = (v2 % 12 >= 0 ? 0 : 0xC) + v2 % 12;
  ptRain->iArrayX = igi2_frame.nXPosMod;
  v3 = ((int)igi2_frame.vYPos2a % 12 >= 0 ? 0 : 0xC) + (int)igi2_frame.vYPos2a % 12;
  igi2_frame.vXPos = (double)(v2 - igi2_frame.nXPosMod) * 10895.3603515625;
  isLastCameraPosValid = ptRain->isLastCameraPosValid;
  ptRain->iArrayY = v3;
  igi2_frame.vYPos = (double)((int)igi2_frame.vYPos2a - v3) * 10895.3603515625;
  if ( isLastCameraPosValid )
  {
    igi2_frame.iXa = fabs(TransContext_tActiveTransContext.tPos.vY - ptRain->tLastCameraPos.vY);
    floor(fabs(TransContext_tActiveTransContext.tPos.vX - ptRain->tLastCameraPos.vX) * 9.178218897432089e-05 * 12.0);
    floor(igi2_frame.iXa * 9.178218897432089e-05 * 12.0);
  }
  qmemcpy(&ptRain->tLastCameraPos, &TransContext_tActiveTransContext.tPos, sizeof(ptRain->tLastCameraPos));
  ptRain->isLastCameraPosValid = 1;
  igi2_frame.iX = 0;
  do
  {
    if ( igi2_frame.iX >= igi2_frame.nXPosMod )
      igi2_frame.vXPos2 = igi2_frame.vXPos;
    else
      igi2_frame.vXPos2 = igi2_frame.vXPos + 130744.32421875;
    v5 = igi2_frame.vYPos;
    igi2_frame.nYPos = 0;
    igi2_frame.vYPos2 = igi2_frame.vYPos;
    do
    {
      if ( igi2_frame.nYPos < v3 )
        v5 = v5 + 130744.32421875;
      v6 = -ptRain->vTraceLineLength;
      LODWORD(atRainVert->tPos.vX) = LODWORD(igi2_frame.vXPos2);
      igi2_frame.vTraceLineLength = v6;
      v7 = GameFunctions_eGetNextZEvaluateQTaskEvent;
      atRainVert->tPos.vY = v5;
      HIDWORD(atRainVert->tPos.vX) = HIDWORD(igi2_frame.vXPos2);
      atRainVert->tPos.vZ = TransContext_tActiveTransContext.tPos.vZ + ptRain->vTraceLineHeight;
      igi2_frame.ptWorld = ptRain->ptWorld;
      igi2_frame.tEvaluateContext.ptQTask = &ptRain->tDynCubeObj.tQObj.tQTask;
      igi2_frame.tEvaluateContext.isEvaluate = 1;
      World_GetNextZ(
        igi2_frame.ptWorld,
        &igi2_frame.tIntersection,
        &atRainVert->tPos,
        1,
        &igi2_frame.vTraceLineLength,
        v7,
        &igi2_frame.tEvaluateContext,
        0xC8000000);
      v5 = igi2_frame.vYPos2 + 10895.3603515625;
      vZ_low = LODWORD(igi2_frame.tIntersection.tPos.vZ);
      HIDWORD(atRainVert->tPos.vZ) = HIDWORD(igi2_frame.tIntersection.tPos.vZ);
      igi2_frame.vYPos2 = igi2_frame.vYPos2 + 10895.3603515625;
      LODWORD(atRainVert->tPos.vZ) = vZ_low;
      qmemcpy(&atRainVert[12], atRainVert, 0x18u);
      qmemcpy(&atRainVert[288], atRainVert, 0x18u);
      qmemcpy(&atRainVert[300], atRainVert, 0x18u);
      atRainVert->nOutCode = 32;
      atRainVert[12].nOutCode = 32;
      atRainVert[288].nOutCode = 32;
      atRainVert[300].nOutCode = 32;
      ++atRainVert;
      ++igi2_frame.nYPos;
    }
    while ( igi2_frame.nYPos <= 11 );
    atRainVert += 12;
    v9 = ++igi2_frame.iX <= 11;
    igi2_frame.vXPos = igi2_frame.vXPos + 10895.3603515625;
  }
  while ( v9 );
  ptRain->nMaxAllowedTraceLines = 0;
}

// source: e/3/pc/pc_rain.c:905  [anchor-mhash]
void __cdecl Rain_DrawGrid(struct Rain_s *ptRain)
{
  struct RainVertex_s *v1; // esi
  struct SortRenderList_t *v2; // edx
  int v3; // edi
  int v4; // ebp
  double vZ; // st6
  double v6; // st5
  double v7; // st6
  int v8; // eax
  struct SortRenderItem_t *v9; // eax
  unsigned __int8 *v10; // eax
  int v11; // [esp+14h] [ebp-10h]
  double vZOffset; // [esp+18h] [ebp-Ch]

  v1 = &ptRain->atRainVert[24 * ptRain->iArrayX + 25 + ptRain->iArrayY];
  vZOffset = floor((TransContext_tActiveTransContext.tPos.vZ - 36864.0) * 4.0690104166666664e-05 + 0.5) * 24576.0;
  Rain_UpdateVertexBuffer(ptRain);
  Rain_ComputeGridOutcodes(ptRain, vZOffset);
  v2 = SortRender_ptActiveList;
  v3 = SortRender_nBufferPos;
  v11 = 9;
  do
  {
    v4 = 9;
    do
    {
      if ( (v1[24].nOutCode & v1[25].nOutCode & v1[1].nOutCode & v1->nOutCode) == 0x20 )
      {
        if ( v1->vZ <= (double)v1[24].vZ )
          vZ = v1[24].vZ;
        else
          vZ = v1->vZ;
        if ( v1[1].vZ <= (double)v1[25].vZ )
          v6 = v1[25].vZ;
        else
          v6 = v1[1].vZ;
        if ( vZ <= v6 )
        {
          if ( v1[1].vZ <= (double)v1[25].vZ )
            v7 = v1[25].vZ;
          else
            v7 = v1[1].vZ;
        }
        else if ( v1->vZ <= (double)v1[24].vZ )
        {
          v7 = v1[24].vZ;
        }
        else
        {
          v7 = v1->vZ;
        }
        if ( g__isRain )
        {
          v8 = v2->nNumItems++;
          v2->atItem[v8].vZ = v7;
          v9 = &v2->atItem[v8];
          v9->pxData = &SortRender_anSortBuffer[v3];
          v9->pfCallback = Rain_SortRenderCallbackVB;
          v10 = &SortRender_anSortBuffer[v3];
          *((double *)v10 + 1) = vZOffset;
          v3 += 16;
          *(_DWORD *)v10 = ptRain;
          *((_DWORD *)v10 + 1) = v1;
        }
      }
      ++v1;
      --v4;
    }
    while ( v4 );
    v1 += 15;
    --v11;
  }
  while ( v11 );
  SortRender_nBufferPos = v3;
}

// source: e/3/pc/pc_rain.c:976  [anchor-mhash]
void __cdecl Rain_RegisterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptParent; // eax
  struct QTask_s *ptPrev; // edx
  struct QTask_s *ptMiddle; // edx

  if ( !ptQTask[556].tQTaskChildren.ptHead )
  {
    ptParent = ptQTask[2].ptParent;
    ptPrev = ptParent[2].ptPrev;
    if ( ptPrev )
    {
      ptPrev[2].tQTaskChildren.ptMiddle = ptQTask;
      ptParent[2].ptPrev[2].tQTaskChildren.ptMiddle[2].tQTaskChildren.ptTail = ptParent[2].ptPrev;
      ptMiddle = ptParent[2].ptPrev[2].tQTaskChildren.ptMiddle;
      ptParent[2].ptPrev = ptMiddle;
      ptMiddle[2].tQTaskChildren.ptMiddle = nullptr;
    }
    else
    {
      ptParent[2].ptPrev = ptQTask;
      ptQTask[2].tQTaskChildren.ptTail = nullptr;
      ptParent[2].ptPrev[2].tQTaskChildren.ptMiddle = nullptr;
    }
    ptQTask[556].tQTaskChildren.ptHead = (struct QTask_s *)1;
  }
}

// source: e/3/pc/pc_rain.c:996  [anchor-mhash]
void __cdecl Rain_RemoveHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptMiddle; // ecx
  struct QTask_s *ptTail; // ecx

  if ( ptQTask[556].tQTaskChildren.ptHead )
  {
    ptMiddle = ptQTask[2].tQTaskChildren.ptMiddle;
    if ( ptMiddle )
      ptMiddle[2].tQTaskChildren.ptTail = ptQTask[2].tQTaskChildren.ptTail;
    else
      ptQTask[2].ptParent[2].ptPrev = ptQTask[2].tQTaskChildren.ptTail;
    ptTail = ptQTask[2].tQTaskChildren.ptTail;
    if ( ptTail )
      ptTail[2].tQTaskChildren.ptMiddle = ptQTask[2].tQTaskChildren.ptMiddle;
    ptQTask[556].tQTaskChildren.ptHead = nullptr;
  }
}

// source: e/3/pc/pc_rain.c:1016  [anchor-mhash]
void __cdecl Rain_EnterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  if ( RenderMode_eActiveRenderMode == Direct3D_eRenderMode )
  {
    if ( *(float *)&ptQTask[554].ptParent == 0.0 )
    {
      HIBYTE(ptQTask[554].eQTaskType) = 0;
      ptQTask[556].tQTaskRefList.ptHead = nullptr;
      ptQTask[556].tQTaskChildren.ptTail = nullptr;
    }
    else
    {
      if ( isTracelines )
      {
        Rain_UpdateGridPosition((struct Rain_s *)ptQTask);
        Rain_DrawGrid((struct Rain_s *)ptQTask);
      }
      ptQTask[556].tQTaskRefList.ptHead = nullptr;
      ptQTask[556].tQTaskChildren.ptTail = nullptr;
    }
  }
  else
  {
    ptQTask[556].tQTaskRefList.ptHead = nullptr;
    ptQTask[556].tQTaskChildren.ptTail = nullptr;
  }
}

// source: e/3/pc/pc_rain.c:1083  [size]
unsigned __int16 __cdecl Rain_GetQTaskType()
{
  return Rain_eQTaskType;
}

// source: e/3/pc/pc_rain.c:1097  [anchor-mhash]
struct QTask_s *__cdecl Rain_New(
        struct World_s *ptWorld,
        struct TexInfo_s *ptTexInfo,
        enum bool isRain,
        float vTraceLineTop,
        float vTraceLineBottom)
{
  struct QTask_s *v5; // esi
  struct DynCubeObj_s *ptManualRedrawList; // eax
  struct DynCubeObj_s *ptPrev; // eax
  struct QTask_s **p_ptPrev; // eax
  int v9; // ecx

  v5 = QTask_NewFn(nullptr, Rain_eQTaskType, nullptr);
  v5[91].tQTaskChildren.ptMiddle = nullptr;
  v5[552].tQTaskRefList.ptHead = nullptr;
  ptManualRedrawList = ptWorld->ptManualRedrawList;
  if ( ptManualRedrawList )
  {
    ptManualRedrawList->ptPrev = (struct DynCubeObj_s *)v5;
    ptWorld->ptManualRedrawList->ptPrev->ptNext = ptWorld->ptManualRedrawList;
    ptPrev = ptWorld->ptManualRedrawList->ptPrev;
    ptWorld->ptManualRedrawList = ptPrev;
  }
  else
  {
    ptWorld->ptManualRedrawList = (struct DynCubeObj_s *)v5;
    v5[2].tQTaskChildren.ptTail = nullptr;
    ptPrev = ptWorld->ptManualRedrawList;
  }
  ptPrev->ptPrev = nullptr;
  v5[555].tQTaskRefList.ptMiddle = (struct QReference_s *)1065353216;
  v5[555].tQTaskRefList.ptTail = (struct QReference_s *)1065353216;
  v5[555].ptParent = (struct QTask_s *)1065353216;
  *(_DWORD *)&v5[555].eQTaskType = 1065353216;
  v5[552].tQTaskRefList.ptMiddle = (struct QReference_s *)(isRain == false);
  v5[2].ptParent = (struct QTask_s *)ptWorld;
  v5[556].tQTaskChildren.ptHead = (struct QTask_s *)1;
  v5[552].tQTaskRefList.ptTail = (struct QReference_s *)ptTexInfo;
  v5[554].ptParent = nullptr;
  v5[552].tQTaskChildren.ptTail = nullptr;
  v5[556].tQTaskChildren.ptMiddle = (struct QTask_s *)32;
  p_ptPrev = &v5[92].ptPrev;
  v9 = 576;
  do
  {
    *p_ptPrev = nullptr;
    p_ptPrev += 8;
    --v9;
  }
  while ( v9 );
  *(double *)&v5[554].tQTaskRefList.ptMiddle = vTraceLineTop;
  v5[555].tQTaskRefList.ptMiddle = (struct QReference_s *)1050673152;
  *(double *)&v5[554].tQTaskChildren.ptTail = vTraceLineTop + vTraceLineBottom;
  Direct3D_ptDevice->lpVtbl->CreateVertexBuffer(
    Direct3D_ptDevice,
    1474560u,
    520u,
    322u,
    D3DPOOL_DEFAULT,
    (struct IDirect3DVertexBuffer8 **)&v5[556].ptPrev);
  isTracelines = true;
  g__isRain = true;
  HIBYTE(v5[554].eQTaskType) = 0;
  Rain_ptActiveTask = (struct Rain_s *)v5;
  return v5;
}

// source: e/3/pc/pc_rain.c:1183  [anchor-mhash]
void __cdecl Rain_Delete(struct QTask_s *ptQTask, struct World_s *ptWorld)
{
  struct QTask_s *ptNext; // ecx
  struct QTask_s *ptMiddle; // eax
  struct QTask_s *ptTail; // eax
  struct QTask_s *ptPrev; // [esp-4h] [ebp-4h]

  ptNext = ptQTask[556].ptPrev->ptNext;
  ptPrev = ptQTask[556].ptPrev;
  Rain_ptActiveTask = nullptr;
  ((void (__stdcall *)(struct QTask_s *))ptNext->tQTaskChildren.ptHead)(ptPrev);
  if ( ptQTask[556].tQTaskChildren.ptHead )
  {
    ptMiddle = ptQTask[2].tQTaskChildren.ptMiddle;
    if ( ptMiddle )
      ptMiddle[2].tQTaskChildren.ptTail = ptQTask[2].tQTaskChildren.ptTail;
    else
      ptWorld->ptManualRedrawList = (struct DynCubeObj_s *)ptQTask[2].tQTaskChildren.ptTail;
    ptTail = ptQTask[2].tQTaskChildren.ptTail;
    if ( ptTail )
      ptTail[2].tQTaskChildren.ptMiddle = ptQTask[2].tQTaskChildren.ptMiddle;
  }
  QTask_Delete(ptQTask);
}

// source: e/3/pc/pc_rain.c:1223  [anchor-strings]
void __cdecl Rain_Open()
{
  unsigned int v0; // eax
  int v1; // edx
  int v2; // ecx
  float *i; // esi
  int v4; // ecx
  int v5; // edx
  unsigned int v6; // eax
  double v7; // st7
  int v8; // ecx
  int v9; // edx
  unsigned int v10; // eax
  double v11; // st7
  unsigned __int16 v12; // si
  int v13; // eax
  struct DisplayCallbackChain_s *v14; // edx
  int v15; // eax
  struct DisplayCallbackChain_s *v16; // edx

  v0 = -923067897;
  v1 = 971667286;
  v2 = 2146516173;
  for ( i = nullptr;
        (unsigned int)i < 0x180;
        i[32457567] = ((double)(unsigned __int16)v0 * 0.0000152587890625 - 0.5) * 4096.0 )
  {
    v4 = (v0 >> 7) ^ v2;
    v5 = v4 ^ v1;
    v6 = v5 + v0;
    v7 = (double)(unsigned __int16)v6;
    v8 = (v6 >> 7) ^ v4;
    v9 = v8 ^ v5;
    v10 = v9 + v6;
    i[32457568] = (v7 * 0.0000152587890625 - 0.5) * 4096.0;
    v11 = (double)(unsigned __int16)v10;
    v2 = (v10 >> 7) ^ v8;
    v1 = v2 ^ v9;
    v0 = v1 + v10;
    i[32457569] = (v11 * 0.0000152587890625 - 0.5) * 4096.0;
    i += 3;
  }
  Rain_tRandomState.anRandom[0] = v0;
  Rain_tRandomState.anRandom[2] = v2;
  Rain_tRandomState.anRandom[1] = v1;
  v12 = QTask_NewQTaskType("Rain", 22264, DynCubeObj_eQTaskType, 0, 0);
  Rain_eQTaskType = v12;
  QTask_LinkQTaskEventHandlerFn(v12, 5, Rain_EnterHandler);
  QTask_LinkQTaskEventHandlerFn(v12, DynCubeObj_eDynCubeObjRegisterQTaskEvent, Rain_RegisterHandler);
  QTask_LinkQTaskEventHandlerFn(v12, DynCubeObj_eDynCubeObjRemoveQTaskEvent, Rain_RemoveHandler);
  v13 = 0;
  while ( Direct3D_atCallback[v13].pfCallback )
  {
    if ( ++v13 >= 32 )
    {
LABEL_6:
      LDebug_Error("No more Direct3D callbacks available.");
      abort();
    }
  }
  v14 = Direct3D_ptRestoreCallback;
  Direct3D_atCallback[v13].pfCallback = Rain_RestoreCallback;
  Direct3D_atCallback[v13].ptNext = v14;
  Direct3D_ptRestoreCallback = (struct DisplayCallbackChain_s *)(8 * v13 + 139166048);
  v15 = 0;
  while ( Direct3D_atCallback[v15].pfCallback )
  {
    if ( ++v15 >= 32 )
      goto LABEL_6;
  }
  v16 = Direct3D_ptDestroyCallback;
  Direct3D_atCallback[v15].pfCallback = Rain_DestroyCallback;
  Direct3D_atCallback[v15].ptNext = v16;
  Direct3D_ptDestroyCallback = (struct DisplayCallbackChain_s *)(8 * v15 + 139166048);
  Rain_tConsoleID = DebugConsole_Alloc("Rain", 100);
}

// source: e/3/pc/pc_rain.c:1265  [anchor-hash]
void __cdecl Rain_Close()
{
  DebugConsole_DeAlloc(Rain_tConsoleID);
  QTask_DeleteQTaskType(Rain_eQTaskType);
}

// source: e/3/pc/pc_rain.c:1283  [anchor-mhash]
void __cdecl Rain_UpdateParticles(struct QTask_s *ptQTask)
{
  struct QTask_s **p_ptMiddle; // ecx
  struct QTask_s *ptTail; // edx
  double v3; // st7
  char eQTaskType; // al
  double v5; // st7
  int i; // ebp
  int v7; // eax
  unsigned int v8; // edx
  unsigned int v9; // eax
  unsigned int v10; // edx
  unsigned int v11; // edx
  double v12; // st7
  double v13; // st7
  struct QTask_s *v14; // eax
  double v15; // st7
  double v16; // st7
  struct QTask_s *v17; // eax
  double v18; // st7
  struct QTask_s *ptMiddle; // eax
  struct QTask_s **v20; // ecx
  unsigned int v21; // edx
  unsigned int v22; // edi
  unsigned int v23; // eax
  double v24; // st7
  int v25; // edx
  int v26; // edi
  unsigned int v27; // edx
  double v28; // st7
  float v29; // [esp+0h] [ebp-10h]
  float v30; // [esp+4h] [ebp-Ch]
  float v31; // [esp+4h] [ebp-Ch]
  float vGravity; // [esp+Ch] [ebp-4h]

  p_ptMiddle = &ptQTask[35].tQTaskChildren.ptMiddle;
  vGravity = 2048.0;
  if ( ptQTask[552].tQTaskRefList.ptMiddle )
    vGravity = 204.8000030517578;
  ptTail = ptQTask[552].tQTaskChildren.ptTail;
  v3 = *(float *)&ptQTask[554].ptParent;
  ptQTask[556].ptNext = (struct QTask_s *)((__int64)(*(float *)&ptQTask[555].eQTaskType * 255.0)
                                         | (((unsigned int)(__int64)(*(float *)&ptQTask[555].ptParent * 255.0)
                                           | (((unsigned int)(__int64)(*(float *)&ptQTask[555].tQTaskRefList.ptTail
                                                                     * 255.0)
                                             | ((unsigned int)(__int64)(*(float *)&ptQTask[555].tQTaskRefList.ptMiddle
                                                                      * 255.0) << 8)) << 8)) << 8));
  eQTaskType = ptQTask[554].eQTaskType;
  ptQTask[552].tQTaskChildren.ptTail = (struct QTask_s *)((char *)&ptTail->ptNext + 3);
  if ( eQTaskType )
  {
    v5 = v3 + 0.01666666753590107;
    if ( v5 >= 1.0 )
      v5 = 1.0;
  }
  else
  {
    v5 = v3 - 0.01666666753590107;
    if ( v5 <= 0.0 )
      v5 = 0.0;
  }
  *(float *)&ptQTask[554].ptParent = v5;
  if ( *(float *)&ptQTask[554].ptParent != 0.0 )
  {
    for ( i = 0; i < (int)ptQTask[91].tQTaskChildren.ptMiddle; ++i )
    {
      v30 = *((float *)p_ptMiddle + 2) - vGravity;
      *((float *)p_ptMiddle + 2) = v30;
      if ( v30 < 0.0 )
        *((float *)p_ptMiddle + 2) = v30 + 24576.0;
      if ( !ptQTask[552].tQTaskRefList.ptMiddle )
        goto LABEL_25;
      v7 = (int)p_ptMiddle[3];
      p_ptMiddle[3] = (struct QTask_s *)(v7 - 1);
      if ( v7 < 0 )
      {
        v8 = (Rain_tRandomState.anRandom[0] >> 7) ^ Rain_tRandomState.anRandom[2];
        v9 = (v8 ^ Rain_tRandomState.anRandom[1]) + Rain_tRandomState.anRandom[0];
        Rain_tRandomState.anRandom[1] ^= v8;
        Rain_tRandomState.anRandom[2] = v8;
        Rain_tRandomState.anRandom[0] = v9;
        p_ptMiddle[3] = (struct QTask_s *)((char *)p_ptMiddle[3] + v9 % 0x1E + 30);
        v10 = (Rain_tRandomState.anRandom[0] >> 7) ^ Rain_tRandomState.anRandom[2];
        Rain_tRandomState.anRandom[0] += v10 ^ Rain_tRandomState.anRandom[1];
        Rain_tRandomState.anRandom[2] = v10;
        Rain_tRandomState.anRandom[1] ^= v10;
        *((float *)p_ptMiddle + 4) = ((double)LOWORD(Rain_tRandomState.anRandom[0]) * 0.0000152587890625 - 0.5)
                                   * 136.53334045410156;
        v11 = (Rain_tRandomState.anRandom[0] >> 7) ^ Rain_tRandomState.anRandom[2];
        Rain_tRandomState.anRandom[0] += v11 ^ Rain_tRandomState.anRandom[1];
        Rain_tRandomState.anRandom[2] = v11;
        Rain_tRandomState.anRandom[1] ^= v11;
        *((float *)p_ptMiddle + 5) = ((double)LOWORD(Rain_tRandomState.anRandom[0]) * 0.0000152587890625 - 0.5)
                                   * 136.53334045410156;
      }
      v29 = *((float *)p_ptMiddle + 4) + *(float *)p_ptMiddle;
      *(float *)p_ptMiddle = v29;
      v31 = *((float *)p_ptMiddle + 5) + *((float *)p_ptMiddle + 1);
      *((float *)p_ptMiddle + 1) = v31;
      v12 = v29;
      if ( v29 >= 0.0 )
      {
        if ( v12 <= 10895.3603515625 )
          goto LABEL_20;
        v13 = v29 - 10895.3603515625;
      }
      else
      {
        v13 = v12 + 10895.3603515625;
      }
      v14 = p_ptMiddle[6];
      *(float *)p_ptMiddle = v13;
      p_ptMiddle[6] = (struct QTask_s *)((unsigned int)v14 ^ 1);
LABEL_20:
      v15 = v31;
      if ( v31 < 0.0 )
      {
        v16 = v15 + 10895.3603515625;
LABEL_24:
        v17 = p_ptMiddle[6];
        *((float *)p_ptMiddle + 1) = v16;
        p_ptMiddle[6] = (struct QTask_s *)((unsigned int)v17 ^ 2);
        goto LABEL_25;
      }
      if ( v15 > 10895.3603515625 )
      {
        v16 = v31 - 10895.3603515625;
        goto LABEL_24;
      }
LABEL_25:
      p_ptMiddle += 7;
    }
    v18 = vGravity + *(float *)&ptQTask[552].tQTaskRefList.ptHead;
    *(float *)&ptQTask[552].tQTaskRefList.ptHead = v18;
    if ( v18 > 307.20001220703125 )
    {
      do
      {
        ptMiddle = ptQTask[91].tQTaskChildren.ptMiddle;
        if ( ptMiddle == (struct QTask_s *)80 )
          break;
        v20 = &ptQTask[35].tQTaskChildren.ptMiddle + 7 * (_DWORD)ptMiddle;
        v21 = (Rain_tRandomState.anRandom[0] >> 7) ^ Rain_tRandomState.anRandom[2];
        v22 = v21 ^ Rain_tRandomState.anRandom[1];
        v23 = (v21 ^ Rain_tRandomState.anRandom[1]) + Rain_tRandomState.anRandom[0];
        v24 = (double)(unsigned __int16)((v21 ^ LOWORD(Rain_tRandomState.anRandom[1]))
                                       + LOWORD(Rain_tRandomState.anRandom[0]))
            * 0.0000152587890625;
        v25 = (v23 >> 7) ^ v21;
        v26 = v25 ^ v22;
        Rain_tRandomState.anRandom[0] = v26 + v23;
        Rain_tRandomState.anRandom[2] = v25;
        Rain_tRandomState.anRandom[1] = v26;
        v20[3] = nullptr;
        *(float *)v20 = v24 * 10895.3603515625;
        *((float *)v20 + 1) = (double)(unsigned __int16)(v26 + v23) * 0.0000152587890625 * 10895.3603515625;
        *((float *)v20 + 2) = 24576.0 - vGravity;
        v27 = (Rain_tRandomState.anRandom[0] >> 7) ^ Rain_tRandomState.anRandom[2];
        Rain_tRandomState.anRandom[0] += v27 ^ Rain_tRandomState.anRandom[1];
        Rain_tRandomState.anRandom[2] = v27;
        Rain_tRandomState.anRandom[1] ^= v27;
        v20[6] = (struct QTask_s *)(Rain_tRandomState.anRandom[0] & 3);
        v28 = *(float *)&ptQTask[552].tQTaskRefList.ptHead - 307.20001220703125;
        ++*(int *)&ptQTask[91].tQTaskChildren.ptMiddle;
        *(float *)&ptQTask[552].tQTaskRefList.ptHead = v28;
      }
      while ( *(float *)&ptQTask[552].tQTaskRefList.ptHead > 307.20001220703125 );
    }
  }
}

// source: e/3/pc/pc_rain.c:1409  [size]
void __cdecl Rain_UpdateStatus(struct QTask_s *ptQTask, int isRaining)
{
  LOBYTE(ptQTask[554].eQTaskType) = isRaining;
}

// source: e/3/pc/pc_rain.c:1428  [anchor-callee]
void __cdecl Rain_SetAlpha(struct QTask_s *ptQTask, float vAlpha)
{
  if ( vAlpha >= 0.0 )
  {
    if ( vAlpha <= 1.0 )
      *(float *)&ptQTask[555].tQTaskRefList.ptMiddle = vAlpha;
    else
      ptQTask[555].tQTaskRefList.ptMiddle = (struct QReference_s *)1065353216;
  }
  else
  {
    ptQTask[555].tQTaskRefList.ptMiddle = nullptr;
  }
}

// source: e/3/pc/pc_rain.c:1445  [size]
enum bool __cdecl Rain_SetEnabled(enum bool isEnabled)
{
  Rain_isEnabled = isEnabled;
  return isEnabled;
}

// source: e/3/pc/pc_rain.c:1458  [size]
enum bool __cdecl Rain_GetEnabled()
{
  return Rain_isEnabled;
}

// source: e/3/pc/pc_rain.c:1471  [size]
struct QTask_s *__cdecl Rain_RemoveParticles(struct QTask_s *ptQTask)
{
  ptQTask[554].ptParent = nullptr;
  return ptQTask;
}

// source: e/3/pc/pc_rain.c:1488  [anchor-mhash]
int __cdecl Rain_SetDensity(struct QTask_s *ptQTask, int nDensity)
{
  if ( nDensity >= 1 )
  {
    if ( nDensity > 32 )
      nDensity = 32;
    ptQTask[556].tQTaskChildren.ptMiddle = (struct QTask_s *)nDensity;
  }
  else
  {
    ptQTask[556].tQTaskChildren.ptMiddle = (struct QTask_s *)1;
    return 1;
  }
  return nDensity;
}

// source: e/3/pc/pc_rain.c:1505  [anchor-mhash]
void __cdecl Rain_SetRGB(struct QTask_s *ptQTask, float vR, float vG, float vB)
{
  double v4; // st7
  double v5; // st7

  if ( vR >= 0.0 )
  {
    if ( vR <= 1.0 )
      v4 = vR;
    else
      v4 = 1.0;
  }
  else
  {
    v4 = 0.0;
  }
  *(float *)&ptQTask[555].tQTaskRefList.ptTail = v4;
  if ( vG >= 0.0 )
  {
    if ( vG <= 1.0 )
      v5 = vG;
    else
      v5 = 1.0;
  }
  else
  {
    v5 = 0.0;
  }
  *(float *)&ptQTask[555].ptParent = v5;
  if ( vB >= 0.0 )
  {
    if ( vB <= 1.0 )
      *(float *)&ptQTask[555].eQTaskType = vB;
    else
      *(_DWORD *)&ptQTask[555].eQTaskType = 1065353216;
  }
  else
  {
    *(_DWORD *)&ptQTask[555].eQTaskType = 0;
  }
}
