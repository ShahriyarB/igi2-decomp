/* e/3/pc/pc_lightmap.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: e/3/pc/pc_lightmap.c:212  [size]
enum bool __cdecl Lightmap_LineToSphereIntersection(
        struct real64x3_t *ptSpherePos,
        float vSphereRadius,
        struct real64x3_t *ptLineStart,
        struct real64x3_t *ptLineEnd)
{
  double v4; // st7
  float v6; // [esp+0h] [ebp-34h]
  float tDelta; // [esp+1Ch] [ebp-18h]
  float tDelta_4; // [esp+20h] [ebp-14h]
  float tDelta_8; // [esp+24h] [ebp-10h]
  float tCurrentDelta; // [esp+28h] [ebp-Ch]
  float tCurrentDelta_4; // [esp+2Ch] [ebp-8h]
  float tCurrentDelta_8; // [esp+30h] [ebp-4h]

  tDelta = ptLineEnd->vX - ptLineStart->vX;
  tDelta_4 = ptLineEnd->vY - ptLineStart->vY;
  tDelta_8 = ptLineEnd->vZ - ptLineStart->vZ;
  tCurrentDelta = ptSpherePos->vX - ptLineStart->vX;
  tCurrentDelta_4 = ptSpherePos->vY - ptLineStart->vY;
  v4 = ptSpherePos->vZ - ptLineStart->vZ;
  tCurrentDelta_8 = v4;
  v6 = tCurrentDelta_8 * tDelta_8 + tCurrentDelta_4 * tDelta_4 + tCurrentDelta * tDelta;
  return vSphereRadius * vSphereRadius >= tCurrentDelta * tCurrentDelta
                                        + tCurrentDelta_4 * tCurrentDelta_4
                                        + v4 * v4
                                        - 1.0
                                        / (tDelta * tDelta + tDelta_4 * tDelta_4 + tDelta_8 * tDelta_8)
                                        * (v6
                                         * v6);
}

// source: e/3/pc/pc_lightmap.c:242  [size]
void __cdecl Lightmap_DownloadHemicube(struct LightmapHemicube_t *ptHemicube)
{
  struct LightmapRenderTarget_t *ptMainFace; // eax
  struct IDirect3DSurface8 ***aptSideFace; // esi
  int v3; // edi

  if ( ptHemicube->isDownloaded == false )
  {
    ptMainFace = ptHemicube->ptMainFace;
    if ( ptMainFace )
      Direct3D_ptDevice->lpVtbl->CopyRects(
        Direct3D_ptDevice,
        ptMainFace->ptSurface,
        nullptr,
        0,
        ptMainFace->ptLockableSurface,
        nullptr);
    aptSideFace = (struct IDirect3DSurface8 ***)ptHemicube->aptSideFace;
    v3 = 4;
    do
    {
      if ( *aptSideFace )
        Direct3D_ptDevice->lpVtbl->CopyRects(Direct3D_ptDevice, (*aptSideFace)[1], nullptr, 0, **aptSideFace, nullptr);
      ++aptSideFace;
      --v3;
    }
    while ( v3 );
    ptHemicube->isDownloaded = true;
  }
}

// source: e/3/pc/pc_lightmap.c:318  [size]
void __cdecl Lightmap_DrawDirlight()
{
  #pragma pack(push, 1)
  union
  {
    struct { int v14; };
    struct { char igi2_o1[4]; int v15; };
    struct { char igi2_o2[8]; struct real32x9_t tMatrix; };
    struct { char igi2_o3[48]; int v17; };
    struct { char igi2_o4[52]; struct real32x3_t tPos; };
    struct { char igi2_o5[64]; struct _D3DMATRIX tLocalMatrix; };
    struct { char igi2_o6[128]; struct LightmapDirlightVertex_t atVertex[300]; };
    char igi2_extent[4932];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double vX; // st7
  double vY; // st6
  double vZ; // st5
  int v3; // edi
  float *p_vZ; // esi
  char v5; // cl
  int v6; // ebp
  int v7; // ebx
  double v8; // st4
  int v9; // edx
  unsigned int v10; // ecx
  float *v11; // eax
  double v12; // st4
  long double v13; // st4

  if ( SkyDome_ptDirlight )
  {
    vX = Lightmap_tDirlightColor.vX;
    vY = Lightmap_tDirlightColor.vY;
    vZ = Lightmap_tDirlightColor.vZ;
    memset(&igi2_frame.tPos, 0, sizeof(igi2_frame.tPos));
    v3 = 0;
    igi2_frame.v15 = (__int64)Lightmap_tDirlightColor.vX;
    p_vZ = &igi2_frame.atVertex[2].vZ;
    igi2_frame.v14 = (__int64)Lightmap_tDirlightColor.vY;
    igi2_frame.v17 = (__int64)Lightmap_tDirlightColor.vZ;
    do
    {
      v5 = igi2_frame.v15;
      v6 = igi2_frame.v14;
      v7 = igi2_frame.v17;
      v8 = (double)(v3 % 8) * 0.125;
      if ( vX - (double)igi2_frame.v15 > v8 )
        v5 = igi2_frame.v15 + 1;
      if ( vY - (double)igi2_frame.v14 > v8 )
        v6 = igi2_frame.v14 + 1;
      if ( vZ - (double)igi2_frame.v17 > v8 )
        v7 = igi2_frame.v17 + 1;
      v9 = 0;
      v10 = v7 | ((v6 | ((*(_DWORD *)&v5 | 0xFFFFFF00) << 8)) << 8);
      v11 = p_vZ - 8;
      do
      {
        v12 = (double)(v9 + v3);
        *v11 = 1.0;
        *((_DWORD *)v11 + 1) = v10;
        ++v9;
        v11 += 4;
        v13 = v12 * 0.009999999776482582 * 6.2831854820251465;
        *(v11 - 6) = cos(v13) * *(float *)&dword_7EFEE4C;
        *(v11 - 5) = sin(v13) * *(float *)&dword_7EFEE4C;
      }
      while ( v9 < 2 );
      *(p_vZ - 2) = 0.0;
      *(p_vZ - 1) = 0.0;
      *p_vZ = 1.0;
      *((_DWORD *)p_vZ + 1) = v10;
      ++v3;
      p_vZ += 12;
    }
    while ( v3 < 100 );
    Real32x9_FromReal32x3(&igi2_frame.tMatrix, &SkyDome_ptDirlight->tDir);
    igi2_frame.tMatrix.tX.vX = Direct3D_vScale * igi2_frame.tMatrix.tX.vX * 4096.0;
    igi2_frame.tMatrix.tX.vY = Direct3D_vScale * igi2_frame.tMatrix.tX.vY * 4096.0;
    igi2_frame.tMatrix.tX.vZ = igi2_frame.tMatrix.tX.vZ * Direct3D_vScale * 4096.0;
    igi2_frame.tMatrix.tY.vX = igi2_frame.tMatrix.tY.vX * Direct3D_vScale * 4096.0;
    igi2_frame.tMatrix.tY.vY = igi2_frame.tMatrix.tY.vY * Direct3D_vScale * 4096.0;
    igi2_frame.tMatrix.tY.vZ = igi2_frame.tMatrix.tY.vZ * Direct3D_vScale * 4096.0;
    igi2_frame.tMatrix.tZ.vX = igi2_frame.tMatrix.tZ.vX * Direct3D_vScale * 4096.0;
    igi2_frame.tMatrix.tZ.vY = igi2_frame.tMatrix.tZ.vY * Direct3D_vScale * 4096.0;
    igi2_frame.tMatrix.tZ.vZ = igi2_frame.tMatrix.tZ.vZ * Direct3D_vScale * 4096.0;
    Direct3D_D3DMATRIXFromReal32x9(&igi2_frame.tLocalMatrix, &igi2_frame.tMatrix, &igi2_frame.tPos);
    Direct3D_ptDevice->lpVtbl->SetTransform(Direct3D_ptDevice, (enum _D3DTRANSFORMSTATETYPE)256, &igi2_frame.tLocalMatrix);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLORARG1, 3u);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLORARG2, 0);
    Direct3D_ptDevice->lpVtbl->SetRenderState(
      Direct3D_ptDevice,
      D3DRS_TEXTUREFACTOR,
      (unsigned int)&MTP_atLODVirModel[45].atBoneVertexRefs[20].atVertexRefs[780].iVertex + 3);
    Direct3D_ptDevice->lpVtbl->SetTexture(Direct3D_ptDevice, 0, nullptr);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZENABLE, 0);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGENABLE, 0);
    Direct3D_ptDevice->lpVtbl->SetVertexShader(Direct3D_ptDevice, 66u);
    Direct3D_ptDevice->lpVtbl->DrawPrimitiveUP(Direct3D_ptDevice, D3DPT_TRIANGLELIST, 100u, igi2_frame.atVertex, 16u);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLORARG2, 3u);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZENABLE, Direct3D_bZBufferMode);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGENABLE, 1u);
  }
}

// source: e/3/pc/pc_lightmap.c:480  [size]
struct real32x3_t *__cdecl Lightmap_GetRenderTargetColor(
        struct real32x3_t *retstr,
        struct LightmapRenderTarget_t *ptRenderTarget,
        float *pvFormFactorTable)
{
  #pragma pack(push, 1)
  union
  {
    struct { int nHeight; };
    struct { char igi2_o1[12]; struct _D3DLOCKED_RECT tLocked; };
    struct { char igi2_o2[20]; struct real32x3_t tColor; };
    char igi2_extent[32];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct LightmapRenderTarget_t *v3; // ebp
  float *v4; // edi
  double vX; // st7
  double vY; // st6
  char *pBits; // ebx
  double vZ; // st5
  int nWidth; // esi
  float *v10; // edx
  _DWORD *v11; // ecx
  double v12; // st4
  double v13; // st3

  v3 = ptRenderTarget;
  v4 = pvFormFactorTable;
  memset(&igi2_frame.tColor, 0, sizeof(igi2_frame.tColor));
  if ( pvFormFactorTable && ptRenderTarget )
  {
    ptRenderTarget->ptLockable->lpVtbl->LockRect(ptRenderTarget->ptLockable, 0, &igi2_frame.tLocked, nullptr, 2064u);
    if ( ptRenderTarget->nHeight > 0 )
    {
      vX = igi2_frame.tColor.vX;
      vY = igi2_frame.tColor.vY;
      pBits = (char *)igi2_frame.tLocked.pBits;
      vZ = igi2_frame.tColor.vZ;
      nWidth = ptRenderTarget->nWidth;
      igi2_frame.nHeight = ptRenderTarget->nHeight;
      do
      {
        if ( nWidth > 0 )
        {
          v10 = v4;
          v11 = pBits;
          do
          {
            v12 = *v10;
            vX = vX + (double)(unsigned __int8)BYTE2(*v11) * v12 * 0.003921568859368563;
            vY = vY + (double)(unsigned __int8)BYTE1(*v11) * v12 * 0.003921568859368563;
            v13 = (double)(unsigned __int8)*v11++;
            ++v10;
            --nWidth;
            vZ = vZ + v13 * v12 * 0.003921568859368563;
          }
          while ( nWidth );
          v3 = ptRenderTarget;
          nWidth = ptRenderTarget->nWidth;
        }
        v4 += nWidth;
        pBits += igi2_frame.tLocked.Pitch;
        --igi2_frame.nHeight;
      }
      while ( igi2_frame.nHeight );
      igi2_frame.tColor.vZ = vZ;
      igi2_frame.tColor.vY = vY;
      igi2_frame.tColor.vX = vX;
    }
    v3->ptLockable->lpVtbl->UnlockRect(v3->ptLockable, 0);
  }
  *retstr = igi2_frame.tColor;
  return retstr;
}

// source: e/3/pc/pc_lightmap.c:554  [size]
unsigned int __cdecl Lightmap_GetHemicubeColor(
        struct LightmapHemicube_t *ptHemicube,
        struct real32x3_t *ptAmbientColor)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real32x3_t tTempColor; };
    struct { char igi2_o1[12]; struct real32x3_t tColor; };
    struct { char igi2_o2[24]; struct real32x3_t v17; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct real32x3_t *RenderTargetColor; // eax
  float vY; // ecx
  float vZ; // edx
  struct LightmapRenderTarget_t **aptSideFace; // esi
  int v7; // edi
  struct real32x3_t *v8; // eax
  float v9; // ecx
  float v10; // edx
  double v11; // st7
  double v12; // st7
  double v13; // st6

  Lightmap_DownloadHemicube(ptHemicube);
  RenderTargetColor = Lightmap_GetRenderTargetColor(&igi2_frame.tTempColor, ptHemicube->ptMainFace, Lightmap_pvMainFormFactorTable);
  vY = RenderTargetColor->vY;
  igi2_frame.tColor.vX = RenderTargetColor->vX;
  vZ = RenderTargetColor->vZ;
  igi2_frame.tColor.vY = vY;
  igi2_frame.tColor.vZ = vZ;
  aptSideFace = ptHemicube->aptSideFace;
  v7 = 4;
  do
  {
    v8 = Lightmap_GetRenderTargetColor(&igi2_frame.v17, *aptSideFace, Lightmap_pvHalfFormFactorTable);
    v9 = v8->vY;
    igi2_frame.tTempColor.vX = v8->vX;
    v10 = v8->vZ;
    igi2_frame.tTempColor.vY = v9;
    igi2_frame.tTempColor.vZ = v10;
    igi2_frame.tColor.vX = igi2_frame.tTempColor.vX + igi2_frame.tColor.vX;
    ++aptSideFace;
    --v7;
    igi2_frame.tColor.vY = v9 + igi2_frame.tColor.vY;
    igi2_frame.tColor.vZ = v10 + igi2_frame.tColor.vZ;
  }
  while ( v7 );
  v11 = Lightmap_vScale * Lightmap_vIntensity;
  igi2_frame.tColor.vX = igi2_frame.tColor.vX * v11;
  igi2_frame.tColor.vY = igi2_frame.tColor.vY * v11;
  igi2_frame.tColor.vZ = v11 * igi2_frame.tColor.vZ;
  Real32x3_HSVFromRGB(&igi2_frame.tColor, &igi2_frame.tColor);
  igi2_frame.tColor.vZ = pow(igi2_frame.tColor.vZ * 1.25, Lightmap_vGamma) * 0.800000011920929;
  Real32x3_RGBFromHSV(&igi2_frame.tColor, &igi2_frame.tColor);
  v12 = igi2_frame.tColor.vX + ptAmbientColor->vX;
  v13 = igi2_frame.tColor.vY + ptAmbientColor->vY;
  igi2_frame.tColor.vZ = igi2_frame.tColor.vZ + ptAmbientColor->vZ;
  igi2_frame.tColor.vX = v12 * 0.5;
  igi2_frame.tColor.vY = v13 * 0.5;
  igi2_frame.tColor.vZ = igi2_frame.tColor.vZ * 0.5;
  Real32x3_HSVFromRGB(&igi2_frame.tColor, &igi2_frame.tColor);
  if ( igi2_frame.tColor.vZ >= 1.0 )
    igi2_frame.tColor.vZ = 1.0;
  Real32x3_RGBFromHSV(&igi2_frame.tColor, &igi2_frame.tColor);
  if ( igi2_frame.tColor.vX >= 1.0 )
    igi2_frame.tColor.vX = 1.0;
  if ( igi2_frame.tColor.vY >= 1.0 )
    igi2_frame.tColor.vY = 1.0;
  if ( igi2_frame.tColor.vZ >= 1.0 )
    igi2_frame.tColor.vZ = 1.0;
  return (__int64)(igi2_frame.tColor.vZ * 255.0)
       | (((unsigned int)(__int64)(igi2_frame.tColor.vY * 255.0)
         | (((unsigned __int8)(__int64)(igi2_frame.tColor.vX * 255.0) | 0xFFFFFF00) << 8)) << 8);
}

// source: e/3/pc/pc_lightmap.c:631  [size]
struct LightmapRenderTarget_t *__cdecl Lightmap_NewRenderTarget(int nWidth, int nHeight)
{
  struct LightmapRenderTarget_t *v2; // esi
  struct IDirect3DSurface8 **p_ptSurface; // edi
  struct IDirect3DSurface8 **p_ptDepthStencil; // ebx
  struct IDirect3DTexture8 **p_ptLockable; // ebp
  int v6; // esi

  v2 = (struct LightmapRenderTarget_t *)Mem_AllocFn(24, 4);
  p_ptSurface = &v2->ptSurface;
  v2->nWidth = nWidth;
  v2->nHeight = nHeight;
  v2->ptSurface = nullptr;
  p_ptDepthStencil = &v2->ptDepthStencil;
  v2->ptDepthStencil = nullptr;
  p_ptLockable = &v2->ptLockable;
  v2->ptLockable = nullptr;
  v2->ptLockableSurface = nullptr;
  Direct3D_ptDevice->lpVtbl->CreateRenderTarget(
    Direct3D_ptDevice,
    nWidth,
    nHeight,
    D3DFMT_X8R8G8B8,
    D3DMULTISAMPLE_4_SAMPLES,
    0,
    &v2->ptSurface);
  if ( !v2->ptSurface )
    goto LABEL_6;
  Direct3D_ptDevice->lpVtbl->CreateDepthStencilSurface(
    Direct3D_ptDevice,
    nWidth,
    nHeight,
    D3DFMT_D24S8,
    D3DMULTISAMPLE_4_SAMPLES,
    &v2->ptDepthStencil);
  if ( !*p_ptDepthStencil )
  {
    (*p_ptSurface)->lpVtbl->Release(*p_ptSurface);
LABEL_6:
    v6 = *(_DWORD *)((unsigned int)&v2[-1].nHeight & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v6);
    memset(*(void **)(v6 + 8), 0xCDu, *(_DWORD *)(v6 + 16));
    free((void *)v6);
    return nullptr;
  }
  Direct3D_ptDevice->lpVtbl->CreateTexture(
    Direct3D_ptDevice,
    nWidth,
    nHeight,
    1u,
    0,
    D3DFMT_X8R8G8B8,
    D3DPOOL_MANAGED,
    &v2->ptLockable);
  if ( !*p_ptLockable )
  {
    (*p_ptDepthStencil)->lpVtbl->Release(*p_ptDepthStencil);
    (*p_ptSurface)->lpVtbl->Release(*p_ptSurface);
    goto LABEL_6;
  }
  (*p_ptLockable)->lpVtbl->GetSurfaceLevel(*p_ptLockable, 0, &v2->ptLockableSurface);
  if ( v2->ptLockableSurface )
    return v2;
  (*p_ptLockable)->lpVtbl->Release(*p_ptLockable);
  (*p_ptDepthStencil)->lpVtbl->Release(*p_ptDepthStencil);
  (*p_ptSurface)->lpVtbl->Release(*p_ptSurface);
  Mem_DeAllocFn(v2);
  return nullptr;
}

// source: e/3/pc/pc_lightmap.c:741  [size]
void __cdecl Lightmap_DeleteRenderTarget(struct LightmapRenderTarget_t *ptRenderTarget)
{
  int v2; // esi

  if ( ptRenderTarget )
  {
    ptRenderTarget->ptLockableSurface->lpVtbl->Release(ptRenderTarget->ptLockableSurface);
    ptRenderTarget->ptLockable->lpVtbl->Release(ptRenderTarget->ptLockable);
    ptRenderTarget->ptDepthStencil->lpVtbl->Release(ptRenderTarget->ptDepthStencil);
    ptRenderTarget->ptSurface->lpVtbl->Release(ptRenderTarget->ptSurface);
    v2 = *(_DWORD *)((unsigned int)&ptRenderTarget[-1].nHeight & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v2);
    memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
    free((void *)v2);
  }
}

// source: e/3/pc/pc_lightmap.c:766  [size]
struct LightmapHemicube_t *__cdecl Lightmap_NewHemicube(int nSize)
{
  struct LightmapHemicube_t *v1; // ebx
  struct LightmapRenderTarget_t **aptSideFace; // edi
  int v4; // [esp+Ch] [ebp-4h]

  v1 = (struct LightmapHemicube_t *)Mem_AllocFn(36, 4);
  v1->isDownloaded = true;
  Direct3D_ptDevice->lpVtbl->ResourceManagerDiscardBytes(Direct3D_ptDevice, 36 * nSize * nSize);
  v1->ptMainFace = Lightmap_NewRenderTarget(nSize, nSize);
  aptSideFace = v1->aptSideFace;
  v4 = 4;
  do
  {
    *aptSideFace++ = Lightmap_NewRenderTarget(nSize, nSize >> 1);
    --v4;
  }
  while ( v4 );
  return v1;
}

// source: e/3/pc/pc_lightmap.c:802  [size]
void __cdecl Lightmap_DeleteHemicube(struct LightmapHemicube_t *ptHemicube)
{
  struct LightmapRenderTarget_t **aptSideFace; // esi
  int v3; // edi
  int v4; // esi

  Lightmap_DeleteRenderTarget(ptHemicube->ptMainFace);
  aptSideFace = ptHemicube->aptSideFace;
  v3 = 4;
  do
  {
    Lightmap_DeleteRenderTarget(*aptSideFace++);
    --v3;
  }
  while ( v3 );
  v4 = *(_DWORD *)((unsigned int)&ptHemicube[-1].aptSideFace[3] & 0xFFFFFFFC);
  --Mem_nCurrentAllocations;
  Node_Remove((_DWORD **)v4);
  memset(*(void **)(v4 + 8), 0xCDu, *(_DWORD *)(v4 + 16));
  free((void *)v4);
}

// source: e/3/pc/pc_lightmap.c:827  [size]
enum bool __cdecl Lightmap_ExcludeObject(
        struct real64x3_t *ptWorldPos,
        struct real32x3_t *ptRotatedPos,
        float vRadius)
{
  double v3; // st5
  enum bool v4; // esi
  struct real64x3_t *v5; // ecx
  float v7; // [esp+4h] [ebp-Ch]
  float vDistanceFromViewConeTop; // [esp+8h] [ebp-8h]
  float vDistanceFromViewConeBottom; // [esp+Ch] [ebp-4h]

  v3 = ptRotatedPos->vZ * -1.0;
  vDistanceFromViewConeTop = (ptRotatedPos->vY - v3) * flt_7EFED50;
  vDistanceFromViewConeBottom = (ptRotatedPos->vY - ptRotatedPos->vZ) * Lightmap_vCosViewConeAngleBottom;
  v7 = -vRadius;
  v4 = (ptRotatedPos->vX - ptRotatedPos->vZ) * Lightmap_vCosViewConeAngleRight > vRadius
    || (ptRotatedPos->vX - v3) * Lightmap_vCosViewConeAngleLeft < v7
    || vDistanceFromViewConeTop < (double)v7
    || vDistanceFromViewConeBottom > (double)vRadius
    || ptRotatedPos->vZ - vRadius > Lightmap_vFadeout * 4096.0;
  if ( v4 )
  {
    v5 = Lightmap_atDirlightPos;
    do
    {
      if ( (int)v5 >= 133164096 )
        break;
      if ( Lightmap_LineToSphereIntersection(ptWorldPos, vRadius, &Lightmap_tActivePos, v5) )
        v4 = false;
      ++v5;
    }
    while ( v4 );
  }
  return v4;
}

// source: e/3/pc/pc_lightmap.c:872  [size]
void __cdecl Lightmap_SetTestRenderState()
{
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_MINFILTER, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_MAGFILTER, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ADDRESSU, 1u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ADDRESSV, 1u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_MIPFILTER, 1u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_TEXCOORDINDEX, 0);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAOP, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAARG1, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLOROP, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLORARG1, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_COLOROP, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZBIAS, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SPECULARENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_CULLMODE, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_LIGHTING, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_COLORVERTEX, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_DITHERENABLE, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHATESTENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZENABLE, Direct3D_bZBufferMode);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZWRITEENABLE, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZFUNC, 4u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHABLENDENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SRCBLEND, 5u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_DESTBLEND, 6u);
}

// source: e/3/pc/pc_lightmap.c:915  [size]
void __cdecl Lightmap_SetRenderState()
{
  double v0; // st7
  struct RenderStateBlock_t *v1; // ecx
  struct RenderStateBlock_t *v2; // edx
  struct RenderStateBlock_t *v3; // ecx
  float vFogEnd; // [esp+FCh] [ebp-8h]
  float vFogStart; // [esp+100h] [ebp-4h]

  v0 = Direct3D_vScale * Lightmap_vFadeout * 4096.0;
  vFogEnd = v0;
  vFogStart = v0 * 0.5;
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_MINFILTER, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_MAGFILTER, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ADDRESSU, 1u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ADDRESSV, 1u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_MIPFILTER, 1u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_TEXCOORDINDEX, 0);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAOP, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAARG1, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLOROP, 4u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLORARG1, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLORARG2, 3u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_COLOROP, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_RANGEFOGENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGTABLEMODE, 3u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGVERTEXMODE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGENABLE, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGSTART, LODWORD(vFogStart));
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGEND, LODWORD(vFogEnd));
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGCOLOR, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZBIAS, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SPECULARENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_CULLMODE, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_LIGHTING, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_COLORVERTEX, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_DITHERENABLE, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZENABLE, Direct3D_bZBufferMode);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZWRITEENABLE, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZFUNC, 4u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHATESTENABLE, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHAREF, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHAFUNC, 5u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHABLENDENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SRCBLEND, 5u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_DESTBLEND, 6u);
  v1 = Direct3D_ptBlendStateBlock;
  Direct3D_ptTextureStateBlock->eCurrentState = -1;
  v2 = Direct3D_ptGenericStateBlock;
  v1->eCurrentState = -1;
  v3 = Direct3D_ptClippingStateBlock;
  v2->eCurrentState = -1;
  v3->eCurrentState = -1;
}

// source: e/3/pc/pc_lightmap.c:978  [size]
void __cdecl QTask_EnumerateLightmapHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptHead; // eax
  int v3; // edx
  struct QTask_s *v4; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // ecx
  int v6; // edx

  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v3 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v4 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v4 = nullptr;
      QTask_atProtectedQTaskStack[v3].ptQTask = v4;
      pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[Lightmap_eEnumerateQTaskEvent][ptHead->eQTaskType].pfHandler;
      v6 = v3 + 1;
      QTask_nProtectedQTaskStackOffset = v6;
      if ( pfHandler )
      {
        pfHandler(ptHead, pxContext);
        v6 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v6];
      v3 = v6 - 1;
      QTask_nProtectedQTaskStackOffset = v3;
    }
    while ( ptHead );
  }
}

// source: e/3/pc/pc_lightmap.c:991  [size]
void __cdecl RigidDynCubeObj_EnumerateLightmapHandler(struct QTask_s *ptQTask, void *pxContext)
{
  unsigned int *p_nAllocated; // esi
  struct QObjectVector_s *v3; // edi
  struct QTask_s **v4; // ecx
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptHead; // eax
  int v7; // ecx
  int v8; // edx
  struct QTask_s *v9; // eax
  void (__cdecl *pfHandler)(int, struct EnumerateLightmapContext_t *); // eax
  int v11; // edx
  struct QTask_s *v12; // eax
  int v13; // eax
  struct QTask_s *v14; // ecx
  void (__cdecl *v15)(int, struct EnumerateLightmapContext_t *); // ecx
  int v16; // edx
  struct QTask_s *v17; // eax
  struct QTask_s *v18; // ecx
  void (__cdecl *v19)(struct QTask_s *, void *); // ecx
  int v20; // edx
  struct EnumerateLightmapContext_t tContext; // [esp+Ch] [ebp-8h] BYREF

  if ( ptQTask[2].tQTaskChildren.ptHead || *((_DWORD *)pxContext + 1) )
  {
    p_nAllocated = &Lightmap_ptTaskVector->nAllocated;
    v3 = Lightmap_ptTaskVector;
    if ( Lightmap_ptTaskVector->nAllocated == Lightmap_ptTaskVector->nSize )
      QObjectVector_Realloc(Lightmap_ptTaskVector, Lightmap_ptTaskVector->nReallocSize);
    v4 = (struct QTask_s **)v3->papxElement[(*p_nAllocated)++];
    *v4 = ptQTask;
  }
  tContext.ptVector = *(struct QObjectVector_s **)pxContext;
  ptNext = ptQTask[3].ptNext;
  tContext.isOwned = true;
  if ( ptNext && (ptHead = ptNext->tQTaskChildren.ptHead, ptHead->ptNext) && (v7 = (int)ptHead) != 0 )
  {
    v8 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( *(_DWORD *)v7 )
        v9 = **(_DWORD **)v7 != 0 ? *(struct QTask_s **)v7 : nullptr;
      else
        v9 = nullptr;
      QTask_atProtectedQTaskStack[v8].ptQTask = v9;
      pfHandler = (void (__cdecl *)(int, struct EnumerateLightmapContext_t *))QTask_aatQTaskFinalEvent[Lightmap_eEnumerateQTaskEvent][*(unsigned __int16 *)(v7 + 36)].pfHandler;
      v11 = v8 + 1;
      QTask_nProtectedQTaskStackOffset = v11;
      if ( pfHandler )
      {
        pfHandler(v7, &tContext);
        v11 = QTask_nProtectedQTaskStackOffset;
      }
      v7 = dword_849C7DC[v11];
      v8 = v11 - 1;
      QTask_nProtectedQTaskStackOffset = v8;
    }
    while ( v7 );
  }
  else
  {
    v8 = QTask_nProtectedQTaskStackOffset;
  }
  if ( QTask_IsQTaskTypeDerived(ptQTask->eQTaskType, SectorObject_eQTaskType) )
  {
    v12 = ptQTask[10].ptNext;
    if ( v12 )
    {
      v13 = (int)v12->tQTaskChildren.ptHead;
      if ( *(_DWORD *)v13 )
      {
        for ( ; v13; QTask_nProtectedQTaskStackOffset = v8 )
        {
          if ( *(_DWORD *)v13 )
            v14 = **(_DWORD **)v13 != 0 ? *(struct QTask_s **)v13 : nullptr;
          else
            v14 = nullptr;
          QTask_atProtectedQTaskStack[v8].ptQTask = v14;
          v15 = (void (__cdecl *)(int, struct EnumerateLightmapContext_t *))QTask_aatQTaskFinalEvent[Lightmap_eEnumerateQTaskEvent][*(unsigned __int16 *)(v13 + 36)].pfHandler;
          v16 = v8 + 1;
          QTask_nProtectedQTaskStackOffset = v16;
          if ( v15 )
          {
            v15(v13, &tContext);
            v16 = QTask_nProtectedQTaskStackOffset;
          }
          v13 = dword_849C7DC[v16];
          v8 = v16 - 1;
        }
      }
    }
  }
  v17 = ptQTask->tQTaskChildren.ptHead;
  if ( v17->ptNext && v17 )
  {
    do
    {
      if ( v17->ptNext )
        v18 = v17->ptNext->ptNext != nullptr ? v17->ptNext : nullptr;
      else
        v18 = nullptr;
      QTask_atProtectedQTaskStack[v8].ptQTask = v18;
      v19 = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[Lightmap_eEnumerateQTaskEvent][v17->eQTaskType].pfHandler;
      v20 = v8 + 1;
      QTask_nProtectedQTaskStackOffset = v20;
      if ( v19 )
      {
        v19(v17, pxContext);
        v20 = QTask_nProtectedQTaskStackOffset;
      }
      v17 = (struct QTask_s *)dword_849C7DC[v20];
      v8 = v20 - 1;
      QTask_nProtectedQTaskStackOffset = v8;
    }
    while ( v17 );
  }
}

// source: e/3/pc/pc_lightmap.c:1045  [size]
void __cdecl RigidDynCubeObj_DrawLightmapHandler(
        struct QTask_s *ptQTask,
        void *pxContext,
        int ltcg_arg2,
        int ltcg_arg3,
        int ltcg_arg4)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptEnd; };
    struct { struct LightmapDirect3D_FaceGroup_t *ptEnda; };
    struct { struct LightmapDirect3D_FaceGroup_t *ptEndb; };
    struct { char igi2_o3[4]; struct real32x3_t tPos; };
    struct { char igi2_o4[16]; struct real64x3_t tWorldPos; };
    struct { char igi2_o5[40]; __int64 v63; };
    struct { char igi2_o6[48]; float vRadius; };
    struct { char igi2_o7[52]; float v65; };
    struct { char igi2_o8[56]; struct VirModel_s *ptVirModel; };
    struct { char igi2_o9[60]; struct real32x9_t tTempMatrix; };
    struct { char igi2_o10[100]; struct _D3DMATRIX tLocalMatrix; };
    char igi2_extent[164];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v5; // eax
  struct VirModel_s *v6; // eax
  struct Mesh3D_Mesh_t *ptMesh; // ebp
  unsigned __int16 eQTaskType; // si
  unsigned __int16 v9; // di
  enum bool v10; // eax
  double v11; // st7
  double v12; // st6
  double v13; // st5
  float *ptNext; // eax
  double v15; // st7
  double v16; // st6
  double v17; // st4
  double v18; // st5
  double v19; // st7
  double v20; // st6
  double v21; // st7
  double v22; // st7
  double vZ; // st7
  double v24; // st6
  double v25; // st5
  enum Mesh3D_RenderMeshType_e eRenderMeshType; // eax
  struct Mesh3D_RenderMesh_LightmapDirect3D_t *pxRenderMesh; // esi
  unsigned int iStartVertex; // ebx
  unsigned int nFVF; // edx
  struct Direct3DRender_VertexData_s *ptVertexData; // eax
  struct IDirect3DIndexBuffer8 **p_ptIndexBuffer; // edx
  struct Mesh3D_RenderMesh_RigidDirect3D_t *v32; // esi
  unsigned int FVF; // edx
  struct Direct3DRender_VertexData_s *v34; // eax
  enum Mesh3D_RenderMeshType_e v35; // eax
  _DWORD *v36; // ebp
  _DWORD *v37; // edi
  unsigned int v38; // esi
  struct LightmapDirect3D_FaceGroup_t *v39; // ecx
  unsigned int v40; // ebp
  unsigned int v41; // ebx
  unsigned int v42; // edi
  int v43; // eax
  int v44; // edx
  unsigned int v45; // ebx
  unsigned __int8 v46; // al
  int v47; // edi
  _DWORD *v48; // ebp
  _DWORD *v49; // edi
  unsigned int v50; // esi
  struct LightmapDirect3D_FaceGroup_t *v51; // eax
  unsigned int v52; // ebp
  unsigned int v53; // ebx
  unsigned int v54; // edi
  int v55; // ecx
  int v56; // edx
  unsigned int v57; // ebx

  v5 = *(_DWORD *)&ptQTask[2].eQTaskType;
  if ( !v5 )
    return;
  v6 = *(struct VirModel_s **)(v5 + 4 * *(_DWORD *)pxContext);
  igi2_frame.ptVirModel = v6;
  if ( !v6 )
    return;
  ptMesh = v6->ptModel->ptMesh;
  eQTaskType = ptQTask->eQTaskType;
  v9 = SplineObjSegment_eQTaskType;
  v10 = QTask_IsQTaskTypeDerived(eQTaskType, SplineObjSegment_eQTaskType);
  v11 = *(double *)&ptQTask[1].ptNext - Lightmap_tActivePos.vX;
  igi2_frame.v65 = v11;
  v12 = *(double *)&ptQTask[1].tQTaskChildren.ptHead - Lightmap_tActivePos.vY;
  *(float *)&igi2_frame.v63 = v12;
  v13 = *(double *)&ptQTask[1].tQTaskChildren.ptTail - Lightmap_tActivePos.vZ;
  igi2_frame.ptEnd = v13;
  if ( v10 )
  {
    ptNext = (float *)ptQTask[38].ptNext;
    if ( ptNext )
    {
      igi2_frame.tPos.vZ = v13;
      igi2_frame.tPos.vX = v11 + *ptNext;
      v15 = v12 + ptNext[1];
      v16 = igi2_frame.tPos.vZ + ptNext[2];
      *(float *)&igi2_frame.tWorldPos.vX = Lightmap_tActiveMatrix.tX.vZ * v16
                              + Lightmap_tActiveMatrix.tX.vY * v15
                              + Lightmap_tActiveMatrix.tX.vX * igi2_frame.tPos.vX;
      *((float *)&igi2_frame.tWorldPos.vX + 1) = Lightmap_tActiveMatrix.tY.vZ * v16
                                    + Lightmap_tActiveMatrix.tY.vY * v15
                                    + Lightmap_tActiveMatrix.tY.vX * igi2_frame.tPos.vX;
      igi2_frame.vRadius = ptNext[3];
      v17 = Lightmap_tActiveMatrix.tZ.vX * igi2_frame.tPos.vX;
      *(double *)&igi2_frame.tPos.vX = igi2_frame.tWorldPos.vX;
      *(float *)&igi2_frame.tWorldPos.vY = Lightmap_tActiveMatrix.tZ.vZ * v16 + Lightmap_tActiveMatrix.tZ.vY * v15 + v17;
    }
    else
    {
      *(float *)&igi2_frame.tWorldPos.vX = Lightmap_tActiveMatrix.tX.vZ * v13
                              + Lightmap_tActiveMatrix.tX.vY * v12
                              + Lightmap_tActiveMatrix.tX.vX * v11;
      igi2_frame.tPos.vX = *(float *)&igi2_frame.tWorldPos.vX;
      igi2_frame.vRadius = *(float *)&ptQTask[1].eQTaskType;
      *((float *)&igi2_frame.tWorldPos.vX + 1) = Lightmap_tActiveMatrix.tY.vZ * v13
                                    + Lightmap_tActiveMatrix.tY.vY * v12
                                    + Lightmap_tActiveMatrix.tY.vX * v11;
      igi2_frame.tPos.vY = *((float *)&igi2_frame.tWorldPos.vX + 1);
      *(float *)&igi2_frame.tWorldPos.vY = Lightmap_tActiveMatrix.tZ.vZ * v13
                              + Lightmap_tActiveMatrix.tZ.vY * v12
                              + Lightmap_tActiveMatrix.tZ.vX * v11;
    }
    igi2_frame.tPos.vZ = *(float *)&igi2_frame.tWorldPos.vY;
  }
  else
  {
    igi2_frame.tPos.vZ = v13;
    v18 = *(float *)&ptQTask[3].tQTaskChildren.ptHead * ptMesh->tRenderMeshSphere.tPos.vY
        + *(float *)&ptQTask[3].ptPrev * ptMesh->tRenderMeshSphere.tPos.vX
        + *(float *)&ptQTask[3].tQTaskChildren.ptMiddle * ptMesh->tRenderMeshSphere.tPos.vZ;
    *((float *)&igi2_frame.tWorldPos.vX + 1) = *(float *)&ptQTask[3].tQTaskRefList.ptHead * ptMesh->tRenderMeshSphere.tPos.vY
                                  + *(float *)&ptQTask[3].tQTaskChildren.ptTail * ptMesh->tRenderMeshSphere.tPos.vX
                                  + *(float *)&ptQTask[3].tQTaskRefList.ptMiddle * ptMesh->tRenderMeshSphere.tPos.vZ;
    *(float *)&igi2_frame.tWorldPos.vY = *(float *)&ptQTask[3].ptParent * ptMesh->tRenderMeshSphere.tPos.vY
                            + *(float *)&ptQTask[3].tQTaskRefList.ptTail * ptMesh->tRenderMeshSphere.tPos.vX
                            + *(float *)&ptQTask[3].eQTaskType * ptMesh->tRenderMeshSphere.tPos.vZ;
    igi2_frame.tPos.vX = v18 + v11;
    v19 = *((float *)&igi2_frame.tWorldPos.vX + 1) + v12;
    v20 = *(float *)&igi2_frame.tWorldPos.vY + igi2_frame.tPos.vZ;
    *(float *)&igi2_frame.tWorldPos.vX = Lightmap_tActiveMatrix.tX.vZ * v20
                            + Lightmap_tActiveMatrix.tX.vY * v19
                            + Lightmap_tActiveMatrix.tX.vX * igi2_frame.tPos.vX;
    *((float *)&igi2_frame.tWorldPos.vX + 1) = Lightmap_tActiveMatrix.tY.vZ * v20
                                  + Lightmap_tActiveMatrix.tY.vY * v19
                                  + Lightmap_tActiveMatrix.tY.vX * igi2_frame.tPos.vX;
    *(float *)&igi2_frame.tWorldPos.vY = Lightmap_tActiveMatrix.tZ.vZ * v20
                            + Lightmap_tActiveMatrix.tZ.vY * v19
                            + Lightmap_tActiveMatrix.tZ.vX * igi2_frame.tPos.vX;
    igi2_frame.tPos = *(struct real32x3_t *)&igi2_frame.tWorldPos.vX;
    v21 = *(float *)&ptQTask[6].ptPrev <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptHead
        ? *(float *)&ptQTask[6].tQTaskChildren.ptHead
        : *(float *)&ptQTask[6].ptPrev;
    if ( v21 <= *(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
      v22 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v22 = *(float *)&ptQTask[6].ptPrev <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptHead
          ? *(float *)&ptQTask[6].tQTaskChildren.ptHead
          : *(float *)&ptQTask[6].ptPrev;
    igi2_frame.vRadius = v22 * ptMesh->tRenderMeshSphere.vRadius;
  }
  igi2_frame.tWorldPos.vX = igi2_frame.tPos.vX + Lightmap_tActivePos.vX;
  igi2_frame.tWorldPos.vY = igi2_frame.tPos.vY + Lightmap_tActivePos.vY;
  igi2_frame.tWorldPos.vZ = igi2_frame.tPos.vZ + Lightmap_tActivePos.vZ;
  if ( Lightmap_ExcludeObject(&igi2_frame.tWorldPos, &igi2_frame.tPos, igi2_frame.vRadius) )
    return;
  *(float *)&igi2_frame.tWorldPos.vX = igi2_frame.v65 * Direct3D_vScale;
  *((float *)&igi2_frame.tWorldPos.vX + 1) = *(float *)&igi2_frame.v63 * Direct3D_vScale;
  *(float *)&igi2_frame.tWorldPos.vY = igi2_frame.ptEnd * Direct3D_vScale;
  if ( QTask_IsQTaskTypeDerived(eQTaskType, v9) )
  {
    vZ = 1.0;
    igi2_frame.tTempMatrix.tX.vX = 1.0;
    memset(&igi2_frame.tTempMatrix.tX.vY, 0, 12);
    igi2_frame.tTempMatrix.tY.vY = 1.0;
    memset(&igi2_frame.tTempMatrix.tY.vZ, 0, 12);
    igi2_frame.tTempMatrix.nOps = 0;
  }
  else
  {
    qmemcpy(&igi2_frame.tTempMatrix, &ptQTask[3].ptPrev, sizeof(igi2_frame.tTempMatrix));
    vZ = igi2_frame.tTempMatrix.tZ.vZ;
  }
  v24 = Direct3D_vScale * *(float *)&ptQTask[6].ptPrev;
  v25 = Direct3D_vScale * *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  igi2_frame.tPos.vZ = Direct3D_vScale * *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  igi2_frame.tTempMatrix.tX.vX = v24 * igi2_frame.tTempMatrix.tX.vX;
  igi2_frame.tTempMatrix.tX.vY = igi2_frame.tTempMatrix.tX.vY * v25;
  igi2_frame.tTempMatrix.tX.vZ = igi2_frame.tPos.vZ * igi2_frame.tTempMatrix.tX.vZ;
  igi2_frame.tTempMatrix.tY.vX = v24 * igi2_frame.tTempMatrix.tY.vX;
  igi2_frame.tTempMatrix.tY.vY = igi2_frame.tTempMatrix.tY.vY * v25;
  igi2_frame.tTempMatrix.tY.vZ = igi2_frame.tPos.vZ * igi2_frame.tTempMatrix.tY.vZ;
  igi2_frame.tTempMatrix.tZ.vX = v24 * igi2_frame.tTempMatrix.tZ.vX;
  igi2_frame.tTempMatrix.tZ.vY = v25 * igi2_frame.tTempMatrix.tZ.vY;
  igi2_frame.tTempMatrix.tZ.vZ = igi2_frame.tPos.vZ * vZ;
  Direct3D_D3DMATRIXFromReal32x9(&igi2_frame.tLocalMatrix, &igi2_frame.tTempMatrix, (struct real32x3_t *)&igi2_frame.tWorldPos);
  Direct3D_ptDevice->lpVtbl->SetTransform(Direct3D_ptDevice, (enum _D3DTRANSFORMSTATETYPE)256, &igi2_frame.tLocalMatrix);
  Lightmap_SetRenderState();
  eRenderMeshType = ptMesh->eRenderMeshType;
  if ( eRenderMeshType == MESH3D_RENDERMESHTYPE_DIRECT3D_BUILDING )
  {
    pxRenderMesh = (struct Mesh3D_RenderMesh_LightmapDirect3D_t *)ptMesh->pxRenderMesh;
    if ( QTask_IsQTaskTypeDerived(ptQTask->eQTaskType, SplineObjSegment_eQTaskType) )
    {
      iStartVertex = Direct3DRender_ProcessVerticesSplineLightmap(pxRenderMesh, (struct SplineObjSegment_s *)ptQTask);
      Direct3D_ptDevice->lpVtbl->SetStreamSource(
        Direct3D_ptDevice,
        0,
        Direct3D_atDynamicVertexBuffer[3].ptVertexBuffer,
        Direct3D_atDynamicVertexBuffer[3].nStride);
      nFVF = Direct3D_atDynamicVertexBuffer[3].nFVF;
    }
    else
    {
      ptVertexData = pxRenderMesh->ptVertexData;
      iStartVertex = ptVertexData->iStartVertex;
      Direct3D_ptDevice->lpVtbl->SetStreamSource(
        Direct3D_ptDevice,
        0,
        ptVertexData->ptVertexBuffer->ptVertexBuffer,
        28u);
      nFVF = pxRenderMesh->ptVertexData->ptVertexBuffer->tVBDesc.FVF;
    }
    Direct3D_ptDevice->lpVtbl->SetVertexShader(Direct3D_ptDevice, nFVF);
    p_ptIndexBuffer = &pxRenderMesh->ptIndexData->ptIndexBuffer;
  }
  else
  {
    if ( eRenderMeshType )
      goto LABEL_32;
    v32 = (struct Mesh3D_RenderMesh_RigidDirect3D_t *)ptMesh->pxRenderMesh;
    if ( QTask_IsQTaskTypeDerived(ptQTask->eQTaskType, SplineObjSegment_eQTaskType) )
    {
      iStartVertex = Direct3DRender_ProcessVerticesSplineRigid(v32, (struct SplineObjSegment_s *)ptQTask);
      Direct3D_ptDevice->lpVtbl->SetStreamSource(
        Direct3D_ptDevice,
        0,
        Direct3D_atDynamicVertexBuffer[0].ptVertexBuffer,
        Direct3D_atDynamicVertexBuffer[0].nStride);
      FVF = Direct3D_atDynamicVertexBuffer[0].nFVF;
    }
    else
    {
      v34 = v32->ptVertexData;
      iStartVertex = v34->iStartVertex;
      Direct3D_ptDevice->lpVtbl->SetStreamSource(Direct3D_ptDevice, 0, v34->ptVertexBuffer->ptVertexBuffer, 32u);
      FVF = v32->ptVertexData->ptVertexBuffer->tVBDesc.FVF;
    }
    Direct3D_ptDevice->lpVtbl->SetVertexShader(Direct3D_ptDevice, FVF);
    p_ptIndexBuffer = &v32->ptIndexData->ptIndexBuffer;
  }
  Direct3D_ptDevice->lpVtbl->SetIndices(Direct3D_ptDevice, *p_ptIndexBuffer, iStartVertex);
LABEL_32:
  v35 = ptMesh->eRenderMeshType;
  if ( v35 == MESH3D_RENDERMESHTYPE_DIRECT3D_BUILDING )
  {
    v36 = ptMesh->pxRenderMesh;
    v37 = pxContext;
    v38 = v36[8];
    v39 = (struct LightmapDirect3D_FaceGroup_t *)(v38 + 28 * v36[3]);
    igi2_frame.ptEnda = v39;
    if ( *((_DWORD *)pxContext + 2) )
    {
      v40 = 0;
      v41 = 0;
      v42 = v38;
      if ( v38 >= (unsigned int)v39 )
        return;
      do
      {
        if ( (*(_BYTE *)v38 & 4) != 0 )
          break;
        if ( *(_BYTE *)(v38 + 2) )
          break;
        if ( *(_WORD *)(v38 + 24) == 0xFFFF )
          break;
        v43 = *(unsigned __int16 *)(v38 + 22);
        v44 = *(unsigned __int16 *)(v38 + 18);
        v38 += 28;
        v40 += v43;
        v41 += v44;
      }
      while ( v38 < (unsigned int)v39 );
      if ( v41 )
      {
        Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLOROP, 3u);
        Direct3D_ptDevice->lpVtbl->SetTexture(Direct3D_ptDevice, 0, nullptr);
        Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_TEXTUREFACTOR, 0);
        Direct3D_ptDevice->lpVtbl->DrawIndexedPrimitive(
          Direct3D_ptDevice,
          D3DPT_TRIANGLELIST,
          *(unsigned __int16 *)(v42 + 20),
          v40,
          *(unsigned __int16 *)(v42 + 16),
          v41);
        v39 = igi2_frame.ptEnda;
      }
      v37 = pxContext;
    }
    if ( v38 < (unsigned int)v39 )
    {
      while ( 1 )
      {
        if ( *(_WORD *)(v38 + 24) != 0xFFFF )
        {
          v45 = *(_BYTE *)v38 & 4;
          if ( v37[1] )
          {
            v46 = *(_BYTE *)(v38 + 2);
            if ( v46 )
            {
              igi2_frame.v63 = (__int64)((double)v46 / Lightmap_vScale + 0.5);
              v47 = igi2_frame.v63;
              if ( (int)igi2_frame.v63 < 1 )
                v47 = 1;
              Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLOROP, 4u);
              Direct3D_ptDevice->lpVtbl->SetRenderState(
                Direct3D_ptDevice,
                D3DRS_TEXTUREFACTOR,
                v47 | ((v47 | ((v47 | 0xFFFFFF00) << 8)) << 8));
              v37 = pxContext;
              goto LABEL_57;
            }
          }
          if ( v37[3] && (*(_BYTE *)v38 & 4) != 0 && !*(_BYTE *)(v38 + 2) )
          {
            Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLOROP, 4u);
            Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_TEXTUREFACTOR, -16777216u);
LABEL_57:
            if ( (*(_BYTE *)v38 & 0x40) != 0 )
              Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHAREF, 64u);
            Direct3D_ptDevice->lpVtbl->SetTexture(
              Direct3D_ptDevice,
              0,
              igi2_frame.ptVirModel->pptTexInfo[*(unsigned __int16 *)(v38 + 24)]->ptDirect3DBaseTexture);
            Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHABLENDENABLE, v45);
            Direct3D_ptDevice->lpVtbl->DrawIndexedPrimitive(
              Direct3D_ptDevice,
              D3DPT_TRIANGLELIST,
              *(unsigned __int16 *)(v38 + 20),
              *(unsigned __int16 *)(v38 + 22),
              *(unsigned __int16 *)(v38 + 16),
              *(unsigned __int16 *)(v38 + 18));
            if ( (*(_BYTE *)v38 & 0x40) != 0 )
              Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHAREF, 0);
            v39 = igi2_frame.ptEnda;
            goto LABEL_62;
          }
          if ( v37[2] && (*(_BYTE *)v38 & 4) == 0 && !*(_BYTE *)(v38 + 2) )
          {
            Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLOROP, 3u);
            Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_TEXTUREFACTOR, 0);
            goto LABEL_57;
          }
        }
LABEL_62:
        v38 += 28;
        if ( v38 >= (unsigned int)v39 )
          return;
      }
    }
    return;
  }
  if ( v35 )
    return;
  v48 = ptMesh->pxRenderMesh;
  v49 = pxContext;
  v50 = v48[6];
  v51 = (struct LightmapDirect3D_FaceGroup_t *)(v50 + 32 * v48[2]);
  igi2_frame.ptEndb = v51;
  if ( *((_DWORD *)pxContext + 2) )
  {
    v52 = 0;
    v53 = 0;
    v54 = v50;
    if ( v50 >= (unsigned int)v51 )
      return;
    do
    {
      if ( (*(_BYTE *)v50 & 4) != 0 )
        break;
      if ( *(_WORD *)(v50 + 24) == 0xFFFF )
        break;
      v55 = *(unsigned __int16 *)(v50 + 22);
      v56 = *(unsigned __int16 *)(v50 + 18);
      v50 += 32;
      v52 += v55;
      v53 += v56;
    }
    while ( v50 < (unsigned int)v51 );
    if ( v53 )
    {
      Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLOROP, 3u);
      Direct3D_ptDevice->lpVtbl->SetTexture(Direct3D_ptDevice, 0, nullptr);
      Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_TEXTUREFACTOR, 0);
      Direct3D_ptDevice->lpVtbl->DrawIndexedPrimitive(
        Direct3D_ptDevice,
        D3DPT_TRIANGLELIST,
        *(unsigned __int16 *)(v54 + 20),
        v52,
        *(unsigned __int16 *)(v54 + 16),
        v53);
      v51 = igi2_frame.ptEndb;
    }
    v49 = pxContext;
  }
  while ( v50 < (unsigned int)v51 )
  {
    if ( *(_WORD *)(v50 + 24) != 0xFFFF )
    {
      v57 = *(_BYTE *)v50 & 4;
      if ( v49[3] && (*(_BYTE *)v50 & 4) != 0 )
      {
        Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLOROP, 4u);
        Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_TEXTUREFACTOR, -16777216u);
LABEL_81:
        if ( (*(_BYTE *)v50 & 0x40) != 0 )
          Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHAREF, 64u);
        Direct3D_ptDevice->lpVtbl->SetTexture(
          Direct3D_ptDevice,
          0,
          igi2_frame.ptVirModel->pptTexInfo[*(unsigned __int16 *)(v50 + 24)]->ptDirect3DBaseTexture);
        Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHABLENDENABLE, v57);
        Direct3D_ptDevice->lpVtbl->DrawIndexedPrimitive(
          Direct3D_ptDevice,
          D3DPT_TRIANGLELIST,
          *(unsigned __int16 *)(v50 + 20),
          *(unsigned __int16 *)(v50 + 22),
          *(unsigned __int16 *)(v50 + 16),
          *(unsigned __int16 *)(v50 + 18));
        if ( (*(_BYTE *)v50 & 0x40) != 0 )
          Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHAREF, 0);
        v51 = igi2_frame.ptEndb;
        goto LABEL_86;
      }
      if ( v49[2] && (*(_BYTE *)v50 & 4) == 0 )
      {
        Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLOROP, 3u);
        Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_TEXTUREFACTOR, 0);
        goto LABEL_81;
      }
    }
LABEL_86:
    v50 += 32;
  }
}

// source: e/3/pc/pc_lightmap.c:1565  [size]
struct real32x3_t *__cdecl Lightmap_Initialize(
        struct QTask_s *ptLevel,
        int nResolution,
        float vIntensity,
        float vGamma,
        float vFadeout,
        float vDirlightRadius,
        float *pvMainFormFactorTable,
        float *pvHalfFormFactorTable,
        struct real32x3_t *ptAmbientColor,
        enum bool isTerrainShadows,
        struct Mesh3D_LightmapVirModel_t *ptLightmapVirModel)
{
  double v11; // st7
  float vX; // edx
  float vZ; // edx
  int v15; // ecx
  int v16; // edi
  double v17; // st6
  int v18; // edx
  double v19; // st4
  double v20; // st5
  double v21; // st4
  double v22; // st3
  double v23; // st4
  double v24; // st3
  double v25; // st4
  struct QObjectVector_s *v26; // eax
  struct QTask_s *ptHead; // ecx
  int v28; // edx
  struct QTask_s *v29; // eax
  void (__cdecl *pfHandler)(struct QTask_s *, struct real32x3_t *); // eax
  int v31; // edx
  struct IDirect3DDevice8Vtbl *lpVtbl; // ecx
  struct real32x3_t *result; // eax
  float vY; // ecx
  float v35; // edx
  double v36; // st7
  double v37; // st7
  double v38; // st6
  double v39; // st5
  double v40; // st5
  double v41; // st5
  double v42; // st7
  struct real32x3_t tContext; // [esp+14h] [ebp-Ch] BYREF
  float nResolutiona = *(float *)&vIntensity; // [esp+28h] [ebp+8h] ARGSLOT
  int vIntensitya = *(int *)&vGamma; // [esp+2Ch] [ebp+Ch] ARGSLOT
  float vIntensityb = *(float *)&vGamma; // [esp+2Ch] [ebp+Ch] ARGSLOT
  float vIntensityc = *(float *)&vGamma; // [esp+2Ch] [ebp+Ch] ARGSLOT
  int vDirlightRadiusa = *(int *)&pvMainFormFactorTable; // [esp+38h] [ebp+18h] ARGSLOT

  v11 = 0.0;
  Lightmap_vIntensity = vIntensity;
  Lightmap_vGamma = vGamma;
  Lightmap_pvMainFormFactorTable = pvMainFormFactorTable;
  Lightmap_pvHalfFormFactorTable = pvHalfFormFactorTable;
  Lightmap_vFadeout = vFadeout;
  dword_7EFEE4C = LODWORD(vDirlightRadius);
  vX = ptAmbientColor->vX;
  Lightmap_isTerrainShadows = isTerrainShadows;
  Lightmap_tAmbientColor.vX = vX;
  Lightmap_tAmbientColor.vY = ptAmbientColor->vY;
  vZ = ptAmbientColor->vZ;
  v15 = 4 * nResolution;
  v16 = 0;
  Lightmap_isInitialized = true;
  Lightmap_nActiveWidth = nResolution;
  Lightmap_nActiveHeight = nResolution;
  Lightmap_tAmbientColor.vZ = vZ;
  vDirlightRadiusa = 0;
  if ( v15 > 0 )
  {
    nResolutiona = (float)v15;
    do
    {
      v17 = (double)vDirlightRadiusa;
      v18 = 0;
      vIntensitya = 0;
      v19 = (v17 + 0.5) / nResolutiona + (v17 + 0.5) / nResolutiona - 1.0;
      v20 = v19 * v19;
      do
      {
        v21 = (double)vIntensitya;
        vIntensityb = v21;
        v22 = (v21 + 0.5) / nResolutiona + (v21 + 0.5) / nResolutiona - 1.0;
        if ( sqrt(v22 * v22 + v20) < vDirlightRadius )
        {
          v23 = nResolutiona * 0.5;
          v24 = (vIntensityb - v23 + 0.5) / v23;
          vIntensityc = 2.0 / nResolutiona;
          v25 = (v17 - v23 + 0.5) / v23 * ((v17 - v23 + 0.5) / v23) + v24 * v24 + 1.0;
          v11 = v11 + 1.0 / (v25 * v25 * 3.1415927410125732) * (vIntensityc * vIntensityc);
        }
        vIntensitya = ++v18;
      }
      while ( v18 < v15 );
      vDirlightRadiusa = ++v16;
    }
    while ( v16 < v15 );
  }
  flt_7EFED48 = 1.0 / v11;
  v26 = (struct QObjectVector_s *)Mem_AllocFn(52, 4);
  v26->nElementSize = 8;
  v26->tMemPool.nBlockSize = 8;
  v26->isStrictOrder = false;
  v26->nSize = 0;
  v26->nAllocated = 0;
  v26->nReallocSize = 100;
  v26->papxElement = nullptr;
  v26->tMemPool.nBlocks = 0;
  v26->tMemPool.nAllocatedBlocks = 0;
  v26->tMemPool.nAlignment = 4;
  v26->tMemPool.nReAllocBlocks = 100;
  v26->tMemPool.tMemPoolFreeList.ptHead = nullptr;
  v26->tMemPool.tMemPoolSegmentList.ptHead = nullptr;
  Lightmap_ptTaskVector = v26;
  LODWORD(tContext.vX) = v26;
  tContext.vY = 0.0;
  QTask_LinkQTaskEventHandlerFn(EditorRigidObj_eQTaskType, Lightmap_eEnumerateQTaskEvent, nullptr);
  ptHead = ptLevel->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v28 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v29 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v29 = nullptr;
      QTask_atProtectedQTaskStack[v28].ptQTask = v29;
      pfHandler = (void (__cdecl *)(struct QTask_s *, struct real32x3_t *))QTask_aatQTaskFinalEvent[Lightmap_eEnumerateQTaskEvent][ptHead->eQTaskType].pfHandler;
      v31 = v28 + 1;
      QTask_nProtectedQTaskStackOffset = v31;
      if ( pfHandler )
      {
        pfHandler(ptHead, &tContext);
        v31 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v31];
      v28 = v31 - 1;
      QTask_nProtectedQTaskStackOffset = v28;
    }
    while ( ptHead );
  }
  Lightmap_aptHemicube[0] = Lightmap_NewHemicube(nResolution);
  Lightmap_apnRequest[0] = nullptr;
  lpVtbl = Direct3D_ptDevice->lpVtbl;
  Lightmap_iHemicube = 0;
  lpVtbl->EndScene(Direct3D_ptDevice);
  Direct3D_ptDevice->lpVtbl->GetRenderTarget(Direct3D_ptDevice, &Lightmap_ptOldRenderTarget);
  Direct3D_ptDevice->lpVtbl->GetDepthStencilSurface(Direct3D_ptDevice, &Lightmap_ptOldDepthBuffer);
  if ( TransContext_isValid )
  {
    qmemcpy(&Lightmap_tOldTransContext, &TransContext_tActiveTransContext, sizeof(Lightmap_tOldTransContext));
    dword_7EFED4C = 1;
  }
  result = &SkyDome_ptDirlight->tDir;
  if ( SkyDome_ptDirlight )
  {
    vY = SkyDome_ptDirlight->tFrontColor.vY;
    tContext.vX = SkyDome_ptDirlight->tFrontColor.vX;
    v35 = SkyDome_ptDirlight->tFrontColor.vZ;
    tContext.vY = vY;
    tContext.vZ = v35;
    Real32x3_HSVFromRGB(&tContext, &tContext);
    tContext.vZ = pow(tContext.vZ * 1.25, 1.0 / Lightmap_vGamma) * 0.800000011920929;
    Real32x3_RGBFromHSV(&tContext, &tContext);
    v36 = 1.0 / Lightmap_vIntensity;
    tContext.vY = v36 * tContext.vY;
    tContext.vZ = v36 * tContext.vZ;
    v37 = tContext.vX * v36 * flt_7EFED48;
    tContext.vY = tContext.vY * flt_7EFED48;
    v38 = tContext.vZ * flt_7EFED48;
    if ( tContext.vY <= v38 )
      v39 = v38;
    else
      v39 = tContext.vY;
    if ( v37 <= v39 )
    {
      if ( tContext.vY <= v38 )
        Lightmap_vScale = v38;
      else
        Lightmap_vScale = tContext.vY;
    }
    else
    {
      Lightmap_vScale = v37;
    }
    if ( Lightmap_vScale < 1.0 )
      Lightmap_vScale = 1.0;
    v40 = 1.0 / Lightmap_vScale;
    tContext.vX = v40 * v37;
    tContext.vY = tContext.vY * v40;
    v41 = v40 * v38;
    v42 = v41;
    if ( tContext.vX > 1.0 )
      tContext.vX = 1.0;
    if ( tContext.vY > 1.0 )
      tContext.vY = 1.0;
    if ( v41 > 1.0 )
      v42 = 1.0;
    tContext.vX = tContext.vX * 255.0;
    Lightmap_ptCurrentLightmapVirModel = ptLightmapVirModel;
    tContext.vY = tContext.vY * 255.0;
    tContext.vZ = v42 * 255.0;
    Lightmap_tDirlightColor = tContext;
    return (struct real32x3_t *)LODWORD(tContext.vZ);
  }
  else
  {
    Lightmap_vScale = 1.0;
    Lightmap_tDirlightColor.vX = 0.0;
    Lightmap_tDirlightColor.vY = 0.0;
    Lightmap_tDirlightColor.vZ = 0.0;
    Lightmap_ptCurrentLightmapVirModel = ptLightmapVirModel;
  }
  return result;
}

// source: e/3/pc/pc_lightmap.c:1726  [size]
void __cdecl Lightmap_Deinitialize(enum bool isDraw)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v30; };
    struct { int v31; };
    struct { int v32; };
    struct { unsigned __int16 *v33; };
    struct { char igi2_o4[4]; unsigned __int16 aiTempIndex[20]; };
    struct { char igi2_o5[44]; struct LightmapVertex_t atTempVertex[12]; };
    char igi2_extent[332];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v1; // st7
  int v2; // ecx
  double v3; // st6
  double v4; // st5
  double v5; // st4
  float *p_vY; // eax
  double v7; // st3
  double v8; // st2
  int v9; // ecx
  float *v10; // eax
  double v11; // st3
  double v12; // st2
  int v13; // ecx
  float *v14; // eax
  double v15; // st3
  double v16; // st2
  struct RenderStateBlock_t *v17; // edx
  struct RenderStateBlock_t *v18; // ecx
  struct RenderStateBlock_t *v19; // edx
  struct LightmapRenderTarget_t *ptMainFace; // eax
  int v21; // ebx
  unsigned __int16 *v22; // esi
  int v23; // eax
  struct LightmapHemicube_t *v24; // ecx
  int v25; // eax
  int v26; // eax
  int v27; // eax
  int v28; // eax
  struct LightmapHemicube_t *v29; // eax

  Direct3D_ptDevice->lpVtbl->SetRenderTarget(Direct3D_ptDevice, Lightmap_ptOldRenderTarget, Lightmap_ptOldDepthBuffer);
  if ( dword_7EFED4C )
  {
    TransContext_SetActiveTransContext(&Lightmap_tOldTransContext);
    dword_7EFED4C = 0;
  }
  Lightmap_ptOldRenderTarget->lpVtbl->Release(Lightmap_ptOldRenderTarget);
  Lightmap_ptOldDepthBuffer->lpVtbl->Release(Lightmap_ptOldDepthBuffer);
  Direct3D_ptDevice->lpVtbl->BeginScene(Direct3D_ptDevice);
  if ( Lightmap_apnRequest[0] )
    *Lightmap_apnRequest[0] = Lightmap_GetHemicubeColor(Lightmap_aptHemicube[0], &Lightmap_tAmbientColor);
  Lightmap_isInitialized = false;
  if ( Lightmap_nActiveWidth <= 300 && isDraw )
  {
    v1 = (double)Lightmap_nActiveWidth;
    igi2_frame.aiTempIndex[1] = 3;
    igi2_frame.aiTempIndex[12] = 3;
    igi2_frame.aiTempIndex[19] = 3;
    v2 = 0;
    igi2_frame.aiTempIndex[0] = 2;
    igi2_frame.aiTempIndex[2] = 6;
    igi2_frame.aiTempIndex[3] = 7;
    igi2_frame.aiTempIndex[4] = 0;
    v3 = (double)(Display_tActiveMode.nWidth - 2 * Lightmap_nActiveWidth) + v1 * 0.5 - 0.5;
    igi2_frame.aiTempIndex[5] = 2;
    v4 = (double)Lightmap_nActiveHeight;
    igi2_frame.aiTempIndex[6] = 8;
    igi2_frame.aiTempIndex[7] = 10;
    igi2_frame.aiTempIndex[8] = 1;
    igi2_frame.aiTempIndex[9] = 0;
    igi2_frame.aiTempIndex[10] = 5;
    igi2_frame.aiTempIndex[11] = 4;
    v5 = 0.5 * v4 - 0.5;
    igi2_frame.aiTempIndex[13] = 1;
    igi2_frame.aiTempIndex[14] = 11;
    igi2_frame.aiTempIndex[15] = 9;
    igi2_frame.aiTempIndex[16] = 0;
    igi2_frame.aiTempIndex[17] = 1;
    igi2_frame.aiTempIndex[18] = 2;
    p_vY = &igi2_frame.atTempVertex[0].vY;
    do
    {
      v7 = (double)(v2 & 1);
      igi2_frame.v30 = (v2 >> 1) & 1;
      p_vY[1] = 0.0;
      p_vY[2] = 0.0;
      ++v2;
      p_vY += 6;
      *(p_vY - 7) = v7 * v1 + v3;
      v8 = (double)igi2_frame.v30;
      *(p_vY - 6) = v4 * v8 + v5;
      *(p_vY - 3) = v7;
      *(p_vY - 2) = v8;
    }
    while ( v2 < 4 );
    v9 = 0;
    v10 = &igi2_frame.atTempVertex[4].vY;
    do
    {
      v11 = (double)(v9 & 1);
      igi2_frame.v31 = (v9 >> 1) & 1;
      v10[1] = 0.0;
      v10[2] = 0.0;
      ++v9;
      v10 += 6;
      *(v10 - 7) = v11 * v1 + v3;
      v12 = (double)igi2_frame.v31;
      *(v10 - 6) = (v12 + v12 - 0.5) * v4 + v5;
      *(v10 - 3) = v11;
      *(v10 - 2) = v12;
    }
    while ( v9 < 4 );
    v13 = 0;
    v14 = &igi2_frame.atTempVertex[8].vY;
    do
    {
      v15 = (double)(v13 & 1);
      igi2_frame.v32 = (v13 >> 1) & 1;
      v14[1] = 0.0;
      v14[2] = 0.0;
      ++v13;
      v14 += 6;
      *(v14 - 7) = (v15 + v15 - 0.5) * v1 + v3;
      v16 = (double)igi2_frame.v32;
      *(v14 - 6) = v4 * v16 + v5;
      *(v14 - 3) = v15;
      *(v14 - 2) = v16;
    }
    while ( v13 < 4 );
    v17 = Direct3D_ptBlendStateBlock;
    Direct3D_ptTextureStateBlock->eCurrentState = -1;
    v18 = Direct3D_ptGenericStateBlock;
    v17->eCurrentState = -1;
    v19 = Direct3D_ptClippingStateBlock;
    v18->eCurrentState = -1;
    v19->eCurrentState = -1;
    Lightmap_SetTestRenderState();
    Direct3D_ptDevice->lpVtbl->SetVertexShader(Direct3D_ptDevice, 260u);
    ptMainFace = Lightmap_aptHemicube[0]->ptMainFace;
    if ( ptMainFace )
    {
      Direct3D_ptDevice->lpVtbl->SetTexture(
        Direct3D_ptDevice,
        0,
        (struct IDirect3DBaseTexture8 *)ptMainFace->ptLockable);
      Direct3D_ptDevice->lpVtbl->DrawIndexedPrimitiveUP(
        Direct3D_ptDevice,
        D3DPT_TRIANGLESTRIP,
        0,
        12u,
        2u,
        &igi2_frame.aiTempIndex[16],
        D3DFMT_INDEX16,
        igi2_frame.atTempVertex,
        24u);
    }
    igi2_frame.v33 = igi2_frame.aiTempIndex;
    v21 = 20;
    v22 = &igi2_frame.aiTempIndex[1];
    do
    {
      v23 = *(v22 - 1);
      igi2_frame.atTempVertex[v23].vU = 0.0;
      igi2_frame.atTempVertex[v23].vV = 0.0;
      v24 = Lightmap_aptHemicube[0];
      v25 = *v22;
      igi2_frame.atTempVertex[v25].vU = 1.0;
      igi2_frame.atTempVertex[v25].vV = 0.0;
      v26 = v22[1];
      igi2_frame.atTempVertex[v26].vU = 0.0;
      igi2_frame.atTempVertex[v26].vV = 1.0;
      v27 = v22[2];
      igi2_frame.atTempVertex[v27].vU = 1.0;
      igi2_frame.atTempVertex[v27].vV = 1.0;
      v28 = *(int *)((char *)&v24->nRenderTime + v21);
      if ( v28 )
      {
        Direct3D_ptDevice->lpVtbl->SetTexture(Direct3D_ptDevice, 0, *(struct IDirect3DBaseTexture8 **)(v28 + 12));
        Direct3D_ptDevice->lpVtbl->DrawIndexedPrimitiveUP(
          Direct3D_ptDevice,
          D3DPT_TRIANGLESTRIP,
          0,
          12u,
          2u,
          igi2_frame.v33,
          D3DFMT_INDEX16,
          igi2_frame.atTempVertex,
          24u);
      }
      v21 += 4;
      v22 += 4;
      igi2_frame.v33 += 4;
    }
    while ( v21 < 36 );
  }
  v29 = Lightmap_aptHemicube[0];
  Lightmap_aptHemicube[0] = nullptr;
  Lightmap_DeleteHemicube(v29);
  QObjectVector_Delete(Lightmap_ptTaskVector);
}

// source: e/3/pc/pc_lightmap.c:1916  [size]
struct LightmapRenderTarget_t *__cdecl Lightmap_RenderHemicubeFace(
        struct LightmapRenderTarget_t *ptRenderTarget,
        struct real64x3_t *ptPos,
        struct real32x9_t *ptOrientation)
{
  #pragma pack(push, 1)
  union
  {
    struct { int nWidth; };
    struct { char igi2_o1[4]; int nHeight; };
    struct { char igi2_o2[8]; float vAspectRatio; };
    struct { char igi2_o3[12]; float tPos; };
    struct { char igi2_o4[16]; float tPos_4; };
    struct { char igi2_o5[24]; float v24; };
    struct { char igi2_o6[28]; float v25; };
    struct { char igi2_o7[32]; int iCount; };
    struct { char igi2_o8[36]; struct real32x9_t tMatrix; };
    struct { char igi2_o9[76]; struct DrawLightmapContext_t tContext; };
    struct { char igi2_o10[176]; struct real32x3_t Real32x3_Rotate_tTemp; };
    struct { char igi2_o11[188]; struct TransContext_s tTransContext; };
    char igi2_extent[360];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v3; // ebp
  struct Dirlight_s *v4; // eax
  bool v5; // zf
  long double v6; // st7
  double v7; // st7
  struct QObjectVector_s *v8; // eax
  signed int i; // edi
  struct QTask_s *v10; // esi
  void (__cdecl *pfHandler)(struct QTask_s *, struct DrawLightmapContext_t *); // eax
  int eQTaskType; // eax
  int v13; // edx
  void (__cdecl *v14)(struct QTask_s *, struct DrawLightmapContext_t *); // eax
  struct QObjectVector_s *v15; // eax
  signed int j; // edi
  struct QTask_s *v17; // esi
  void (__cdecl *v18)(struct QTask_s *, struct DrawLightmapContext_t *); // eax

  if ( ptRenderTarget )
  {
    igi2_frame.nHeight = ptRenderTarget->nHeight;
    igi2_frame.nWidth = ptRenderTarget->nWidth;
    igi2_frame.v24 = (float)igi2_frame.nHeight;
    igi2_frame.v25 = (float)igi2_frame.nWidth;
    igi2_frame.vAspectRatio = igi2_frame.v24 / igi2_frame.v25;
    Direct3D_ptDevice->lpVtbl->SetRenderTarget(
      Direct3D_ptDevice,
      ptRenderTarget->ptSurface,
      ptRenderTarget->ptDepthStencil);
    qmemcpy(&Lightmap_tActivePos, ptPos, sizeof(Lightmap_tActivePos));
    v3 = 0;
    qmemcpy(&Lightmap_tActiveMatrix, ptOrientation, sizeof(Lightmap_tActiveMatrix));
    igi2_frame.iCount = 0;
    do
    {
      v4 = SkyDome_ptDirlight;
      v5 = SkyDome_ptDirlight == nullptr;
      qmemcpy(&Lightmap_atDirlightPos[v3], &Lightmap_tActivePos, sizeof(struct real64x3_t));
      if ( !v5 )
      {
        v6 = (double)igi2_frame.iCount * 0.125 * 6.2831854820251465;
        if ( v3 == 8 )
        {
          igi2_frame.tPos = 0.0;
          igi2_frame.tPos_4 = 0.0;
        }
        else
        {
          igi2_frame.tPos = cos(v6) * *(float *)&dword_7EFEE4C;
          igi2_frame.tPos_4 = sin(v6) * *(float *)&dword_7EFEE4C;
        }
        Real32x9_FromReal32x3(&igi2_frame.tMatrix, &v4->tDir);
        igi2_frame.tMatrix.tX.vX = igi2_frame.tMatrix.tX.vX * 4096000.0;
        igi2_frame.tMatrix.tX.vY = igi2_frame.tMatrix.tX.vY * 4096000.0;
        igi2_frame.tMatrix.tX.vZ = igi2_frame.tMatrix.tX.vZ * 4096000.0;
        igi2_frame.tMatrix.tY.vX = igi2_frame.tMatrix.tY.vX * 4096000.0;
        igi2_frame.tMatrix.tY.vY = igi2_frame.tMatrix.tY.vY * 4096000.0;
        igi2_frame.tMatrix.tY.vZ = igi2_frame.tMatrix.tY.vZ * 4096000.0;
        igi2_frame.tMatrix.tZ.vX = igi2_frame.tMatrix.tZ.vX * 4096000.0;
        igi2_frame.tMatrix.tZ.vY = igi2_frame.tMatrix.tZ.vY * 4096000.0;
        igi2_frame.tMatrix.tZ.vZ = igi2_frame.tMatrix.tZ.vZ * 4096000.0;
        igi2_frame.Real32x3_Rotate_tTemp.vZ = igi2_frame.tMatrix.tZ.vY * igi2_frame.tPos_4 + igi2_frame.tMatrix.tZ.vX * igi2_frame.tPos + igi2_frame.tMatrix.tZ.vZ;
        v7 = igi2_frame.tMatrix.tY.vY * igi2_frame.tPos_4 + igi2_frame.tMatrix.tY.vX * igi2_frame.tPos + igi2_frame.tMatrix.tY.vZ;
        Lightmap_atDirlightPos[v3].vX = igi2_frame.tMatrix.tX.vY * igi2_frame.tPos_4
                                      + igi2_frame.tMatrix.tX.vX * igi2_frame.tPos
                                      + igi2_frame.tMatrix.tX.vZ
                                      + Lightmap_atDirlightPos[v3].vX;
        Lightmap_atDirlightPos[v3].vY = v7 + Lightmap_atDirlightPos[v3].vY;
        Lightmap_atDirlightPos[v3].vZ = igi2_frame.Real32x3_Rotate_tTemp.vZ + Lightmap_atDirlightPos[v3].vZ;
      }
      igi2_frame.iCount = ++v3;
    }
    while ( v3 < 9 );
    qmemcpy(&igi2_frame.tTransContext.tPos, ptPos, sizeof(igi2_frame.tTransContext.tPos));
    igi2_frame.tTransContext.vFOVY = igi2_frame.v24 / igi2_frame.v25;
    igi2_frame.tTransContext.vFOVX = 1.0;
    igi2_frame.tTransContext.isDraw = 1;
    igi2_frame.tTransContext.eLayer = TRANSCONTEXT_LAYER_HEMICUBE;
    Lightmap_vCosViewConeAngleLeft = cos(atan2(-1.0, 1.0));
    Lightmap_vCosViewConeAngleRight = cos(atan2(1.0, 1.0));
    flt_7EFED50 = Lightmap_vCosViewConeAngleLeft;
    Lightmap_vCosViewConeAngleBottom = cos(atan2(igi2_frame.vAspectRatio + igi2_frame.vAspectRatio - 1.0, 1.0));
    igi2_frame.tTransContext.vScreenFOVX = (float)(igi2_frame.nWidth / 2);
    igi2_frame.tTransContext.vScreenFOVY = (double)(igi2_frame.nHeight / 2) * igi2_frame.vAspectRatio;
    igi2_frame.tTransContext.vScreenOriginX = igi2_frame.v25 * 0.5;
    igi2_frame.tTransContext.vScreenOriginY = igi2_frame.v24 * 0.5;
    qmemcpy(&igi2_frame.tTransContext, &Lightmap_tActiveMatrix, 0x28u);
    TransContext_SetHemicubeTransContext(&igi2_frame.tTransContext, igi2_frame.nWidth, igi2_frame.nHeight, igi2_frame.vAspectRatio);
    Direct3D_ptDevice->lpVtbl->BeginScene(Direct3D_ptDevice);
    Lightmap_SetRenderState();
    ((void (__stdcall *)(struct IDirect3DDevice8 *, _DWORD, _DWORD, int, _DWORD, int, _DWORD))Direct3D_ptDevice->lpVtbl->Clear)(
      Direct3D_ptDevice,
      0,
      0,
      7,
      0,
      1065353216,
      0);
    Lightmap_DrawDirlight();
    qmemcpy(&igi2_frame.tContext.tOrientation, ptOrientation, sizeof(igi2_frame.tContext.tOrientation));
    qmemcpy(&igi2_frame.tContext.tPos, ptPos, sizeof(igi2_frame.tContext.tPos));
    LODWORD(igi2_frame.tContext.vDirlightRadius) = dword_7EFEE4C;
    v8 = Lightmap_ptTaskVector;
    igi2_frame.tContext.vFOVX = 1.0;
    igi2_frame.tContext.isTerrainShadows = Lightmap_isTerrainShadows;
    for ( i = 0; i < (signed int)Lightmap_ptTaskVector->nAllocated; ++i )
    {
      v10 = *(struct QTask_s **)v8->papxElement[i];
      if ( Lightmap_ptCurrentLightmapVirModel && v10 == Lightmap_ptCurrentLightmapVirModel->ptQTask )
      {
        igi2_frame.tContext.isDrawOpaque = true;
        igi2_frame.tContext.isDrawLights = false;
        igi2_frame.tContext.isDrawTransparent = false;
        igi2_frame.tContext.iLOD = Lightmap_ptCurrentLightmapVirModel->iLOD;
        Lightmap_SetRenderState();
        pfHandler = (void (__cdecl *)(struct QTask_s *, struct DrawLightmapContext_t *))QTask_aatQTaskFinalEvent[Lightmap_eDrawQTaskEvent][v10->eQTaskType].pfHandler;
        if ( pfHandler )
          pfHandler(v10, &igi2_frame.tContext);
        igi2_frame.tContext.isDrawOpaque = false;
        igi2_frame.tContext.isDrawLights = true;
        igi2_frame.tContext.isDrawTransparent = false;
        igi2_frame.tContext.iLOD = 0;
        Lightmap_SetRenderState();
        eQTaskType = v10->eQTaskType;
        v13 = 511 * Lightmap_eDrawQTaskEvent;
      }
      else
      {
        igi2_frame.tContext.isDrawOpaque = true;
        igi2_frame.tContext.isDrawLights = true;
        igi2_frame.tContext.isDrawTransparent = false;
        igi2_frame.tContext.iLOD = 0;
        Lightmap_SetRenderState();
        v13 = v10->eQTaskType;
        eQTaskType = 511 * Lightmap_eDrawQTaskEvent;
      }
      v14 = (void (__cdecl *)(struct QTask_s *, struct DrawLightmapContext_t *))QTask_aatQTaskFinalEvent[0][eQTaskType + v13].pfHandler;
      if ( v14 )
        v14(v10, &igi2_frame.tContext);
      v8 = Lightmap_ptTaskVector;
    }
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZWRITEENABLE, 0);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_CULLMODE, 3u);
    v15 = Lightmap_ptTaskVector;
    for ( j = 0; j < (signed int)Lightmap_ptTaskVector->nAllocated; ++j )
    {
      v17 = *(struct QTask_s **)v15->papxElement[j];
      if ( Lightmap_ptCurrentLightmapVirModel && v17 == Lightmap_ptCurrentLightmapVirModel->ptQTask )
      {
        igi2_frame.tContext.isDrawOpaque = false;
        igi2_frame.tContext.isDrawLights = false;
        igi2_frame.tContext.isDrawTransparent = true;
        igi2_frame.tContext.iLOD = Lightmap_ptCurrentLightmapVirModel->iLOD;
      }
      else
      {
        igi2_frame.tContext.isDrawTransparent = true;
        memset(&igi2_frame.tContext, 0, 12);
      }
      Lightmap_SetRenderState();
      v18 = (void (__cdecl *)(struct QTask_s *, struct DrawLightmapContext_t *))QTask_aatQTaskFinalEvent[Lightmap_eDrawQTaskEvent][v17->eQTaskType].pfHandler;
      if ( v18 )
        v18(v17, &igi2_frame.tContext);
      v15 = Lightmap_ptTaskVector;
    }
    return (struct LightmapRenderTarget_t *)Direct3D_ptDevice->lpVtbl->EndScene(Direct3D_ptDevice);
  }
  return ptRenderTarget;
}

// source: e/3/pc/pc_lightmap.c:2130  [size]
struct real32x9_t *__cdecl Lightmap_RenderHemicube(
        unsigned int *pnDestColor,
        struct real64x3_t *ptPos,
        struct real32x9_t *ptOrientation)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct LightmapRenderTarget_t **aptSideFace; };
    struct { char igi2_o1[4]; struct real32x9_t Real32x9_Multiply_tTemp; };
    struct { char igi2_o2[44]; struct real32x9_t Real32x9_Normalize_tTemp; };
    struct { char igi2_o3[84]; struct LightmapHemicube_t *ptHemicube; };
    struct { char igi2_o4[88]; struct real32x9_t tCurrentOrientation; };
    char igi2_extent[132];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v4; // esi
  struct LightmapHemicube_t *v5; // esi
  struct LightmapRenderTarget_t *ptMainFace; // eax
  float *v7; // ebp
  int nOps; // edx
  bool v9; // sf
  double v10; // st7
  double v11; // st6
  long double v12; // st7
  long double v13; // st7
  long double v14; // st7
  DWORD PerformanceCounter; // eax
  struct LightmapHemicube_t *v16; // ebx
  struct real32x9_t *result; // eax
  struct real32x3_t tTemp_; // 0:^18.12
  struct real32x3_t v28; // 0:^24.12

  v4 = Lightmap_iHemicube;
  if ( Lightmap_apnRequest[Lightmap_iHemicube] )
  {
    v4 = Lightmap_iHemicube;
    *Lightmap_apnRequest[v4] = Lightmap_GetHemicubeColor(
                                 Lightmap_aptHemicube[Lightmap_iHemicube],
                                 &Lightmap_tAmbientColor);
  }
  Lightmap_apnRequest[v4] = pnDestColor;
  v5 = Lightmap_aptHemicube[v4];
  ptMainFace = v5->ptMainFace;
  igi2_frame.ptHemicube = v5;
  v5->isDownloaded = true;
  Lightmap_iHemicube = 0;
  Lightmap_RenderHemicubeFace(ptMainFace, ptPos, ptOrientation);
  v7 = (float *)&unk_7EFED5C;
  igi2_frame.aptSideFace = v5->aptSideFace;
  do
  {
    igi2_frame.Real32x9_Multiply_tTemp.tX.vX = *v7 * ptOrientation->tY.vX
                                  + *(v7 - 1) * ptOrientation->tX.vX
                                  + v7[1] * ptOrientation->tZ.vX;
    igi2_frame.Real32x9_Multiply_tTemp.tX.vY = ptOrientation->tZ.vY * v7[1]
                                  + *(v7 - 1) * ptOrientation->tX.vY
                                  + *v7 * ptOrientation->tY.vY;
    igi2_frame.Real32x9_Multiply_tTemp.tX.vZ = *v7 * ptOrientation->tY.vZ
                                  + ptOrientation->tX.vZ * *(v7 - 1)
                                  + v7[1] * ptOrientation->tZ.vZ;
    igi2_frame.Real32x9_Multiply_tTemp.tY.vX = v7[2] * ptOrientation->tX.vX
                                  + v7[3] * ptOrientation->tY.vX
                                  + v7[4] * ptOrientation->tZ.vX;
    igi2_frame.Real32x9_Multiply_tTemp.tY.vY = ptOrientation->tZ.vY * v7[4]
                                  + ptOrientation->tY.vY * v7[3]
                                  + v7[2] * ptOrientation->tX.vY;
    igi2_frame.Real32x9_Multiply_tTemp.tY.vZ = ptOrientation->tX.vZ * v7[2]
                                  + v7[4] * ptOrientation->tZ.vZ
                                  + v7[3] * ptOrientation->tY.vZ;
    igi2_frame.Real32x9_Multiply_tTemp.tZ.vX = v7[5] * ptOrientation->tX.vX
                                  + v7[6] * ptOrientation->tY.vX
                                  + v7[7] * ptOrientation->tZ.vX;
    igi2_frame.Real32x9_Multiply_tTemp.tZ.vY = ptOrientation->tZ.vY * v7[7]
                                  + ptOrientation->tY.vY * v7[6]
                                  + v7[5] * ptOrientation->tX.vY;
    nOps = ptOrientation->nOps;
    v9 = (int)(*((_DWORD *)v7 + 8) + nOps - 999) < 0;
    v10 = ptOrientation->tX.vZ * v7[5] + v7[7] * ptOrientation->tZ.vZ;
    v11 = v7[6] * ptOrientation->tY.vZ;
    igi2_frame.Real32x9_Multiply_tTemp.nOps = *((_DWORD *)v7 + 8) + nOps + 1;
    igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ = v10 + v11;
    qmemcpy(&igi2_frame.tCurrentOrientation, &igi2_frame.Real32x9_Multiply_tTemp, sizeof(igi2_frame.tCurrentOrientation));
    if ( !(v9 ^ __OFSUB__(igi2_frame.Real32x9_Multiply_tTemp.nOps, 1000) | (igi2_frame.Real32x9_Multiply_tTemp.nOps == 1000)) )
    {
      igi2_frame.Real32x9_Normalize_tTemp.tX = igi2_frame.Real32x9_Multiply_tTemp.tX;
      if ( igi2_frame.Real32x9_Multiply_tTemp.tX.vX != 0.0
        || igi2_frame.Real32x9_Multiply_tTemp.tX.vY != 0.0
        || igi2_frame.Real32x9_Multiply_tTemp.tX.vZ != 0.0 )
      {
        v12 = 1.0
            / sqrt(
                igi2_frame.Real32x9_Multiply_tTemp.tX.vX * igi2_frame.Real32x9_Multiply_tTemp.tX.vX
              + igi2_frame.Real32x9_Multiply_tTemp.tX.vY * igi2_frame.Real32x9_Multiply_tTemp.tX.vY
              + igi2_frame.Real32x9_Multiply_tTemp.tX.vZ * igi2_frame.Real32x9_Multiply_tTemp.tX.vZ);
        igi2_frame.Real32x9_Normalize_tTemp.tX.vX = igi2_frame.Real32x9_Multiply_tTemp.tX.vX * v12;
        igi2_frame.Real32x9_Normalize_tTemp.tX.vY = igi2_frame.Real32x9_Normalize_tTemp.tX.vY * v12;
        igi2_frame.Real32x9_Normalize_tTemp.tX.vZ = igi2_frame.Real32x9_Normalize_tTemp.tX.vZ * v12;
      }
      tTemp_.vX = igi2_frame.Real32x9_Multiply_tTemp.tZ.vY * igi2_frame.Real32x9_Multiply_tTemp.tX.vZ
                - igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ * igi2_frame.Real32x9_Multiply_tTemp.tX.vY;
      tTemp_.vY = -(igi2_frame.Real32x9_Multiply_tTemp.tZ.vX * igi2_frame.Real32x9_Multiply_tTemp.tX.vZ
                  - igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ * igi2_frame.Real32x9_Multiply_tTemp.tX.vX);
      tTemp_.vZ = igi2_frame.Real32x9_Multiply_tTemp.tZ.vX * igi2_frame.Real32x9_Multiply_tTemp.tX.vY
                - igi2_frame.Real32x9_Multiply_tTemp.tZ.vY * igi2_frame.Real32x9_Multiply_tTemp.tX.vX;
      igi2_frame.Real32x9_Normalize_tTemp.tY = tTemp_;
      v28.vX = tTemp_.vZ * igi2_frame.Real32x9_Normalize_tTemp.tX.vY - tTemp_.vY * igi2_frame.Real32x9_Normalize_tTemp.tX.vZ;
      v28.vY = -(tTemp_.vZ * igi2_frame.Real32x9_Normalize_tTemp.tX.vX - tTemp_.vX * igi2_frame.Real32x9_Normalize_tTemp.tX.vZ);
      v28.vZ = tTemp_.vY * igi2_frame.Real32x9_Normalize_tTemp.tX.vX - tTemp_.vX * igi2_frame.Real32x9_Normalize_tTemp.tX.vY;
      igi2_frame.Real32x9_Normalize_tTemp.tZ = v28;
      if ( tTemp_.vX != 0.0 || tTemp_.vY != 0.0 || tTemp_.vZ != 0.0 )
      {
        v13 = 1.0 / sqrt(tTemp_.vY * tTemp_.vY + tTemp_.vX * tTemp_.vX + tTemp_.vZ * tTemp_.vZ);
        igi2_frame.Real32x9_Normalize_tTemp.tY.vX = tTemp_.vX * v13;
        igi2_frame.Real32x9_Normalize_tTemp.tY.vY = igi2_frame.Real32x9_Normalize_tTemp.tY.vY * v13;
        igi2_frame.Real32x9_Normalize_tTemp.tY.vZ = igi2_frame.Real32x9_Normalize_tTemp.tY.vZ * v13;
      }
      if ( v28.vX != 0.0 || v28.vY != 0.0 || v28.vZ != 0.0 )
      {
        v14 = 1.0 / sqrt(v28.vX * v28.vX + v28.vY * v28.vY + v28.vZ * v28.vZ);
        igi2_frame.Real32x9_Normalize_tTemp.tZ.vX = v28.vX * v14;
        igi2_frame.Real32x9_Normalize_tTemp.tZ.vY = igi2_frame.Real32x9_Normalize_tTemp.tZ.vY * v14;
        igi2_frame.Real32x9_Normalize_tTemp.tZ.vZ = igi2_frame.Real32x9_Normalize_tTemp.tZ.vZ * v14;
      }
      qmemcpy(&igi2_frame.Real32x9_Multiply_tTemp, &igi2_frame.Real32x9_Normalize_tTemp, sizeof(igi2_frame.Real32x9_Multiply_tTemp));
      igi2_frame.Real32x9_Multiply_tTemp.nOps = 0;
    }
    Lightmap_RenderHemicubeFace(*igi2_frame.aptSideFace, ptPos, &igi2_frame.tCurrentOrientation);
    v7 += 10;
    ++igi2_frame.aptSideFace;
  }
  while ( (int)v7 < 133164540 );
  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  v16 = igi2_frame.ptHemicube;
  igi2_frame.ptHemicube->nRenderTime = PerformanceCounter - Timer_nStartTime;
  v16->isDownloaded = false;
  Lightmap_DownloadHemicube(v16);
  return result;
}

// source: e/3/pc/pc_lightmap.c:2196  [size]
void __cdecl Lightmap_Open()
{
  __int16 v0; // si
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v2; // si
  float *v3; // esi
  __int16 v4; // [esp-Ch] [ebp-2Ch]
  struct real32x9_t *v5; // [esp-8h] [ebp-28h]
  float vAlpha; // [esp+0h] [ebp-20h]
  int iSide; // [esp+10h] [ebp-10h]
  float v8; // [esp+14h] [ebp-Ch]
  float v9; // [esp+18h] [ebp-8h]
  float v10; // [esp+1Ch] [ebp-4h]

  Lightmap_eDrawQTaskEvent = QTask_NewQTaskEventFn(0, "DrawLightmap");
  v0 = QTask_NewQTaskEventFn(0, "EnumerateLightmap");
  Lightmap_eEnumerateQTaskEvent = v0;
  BaseQTaskType = QTask_GetBaseQTaskType();
  QTask_LinkQTaskEventHandlerFn(BaseQTaskType, v0, QTask_EnumerateLightmapHandler);
  v4 = v0;
  v2 = RigidDynCubeObj_eQTaskType;
  QTask_LinkQTaskEventHandlerFn(RigidDynCubeObj_eQTaskType, v4, RigidDynCubeObj_EnumerateLightmapHandler);
  QTask_LinkQTaskEventHandlerFn(
    v2,
    Lightmap_eDrawQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))RigidDynCubeObj_DrawLightmapHandler);
  iSide = 0;
  v3 = (float *)&unk_7EFED60;
  v8 = sin(1.5707963705062866);
  v9 = cos(1.5707963705062866);
  do
  {
    v3[2] = v9;
    vAlpha = (double)iSide * 1.5707963705062866;
    v10 = -v8;
    v3[3] = v10;
    v5 = (struct real32x9_t *)(v3 - 2);
    v5->tX.vX = 1.0;
    *(v3 - 1) = 0.0;
    *v3 = 0.0;
    v3[1] = 0.0;
    v3[4] = 0.0;
    v3[5] = v8;
    v3[6] = v9;
    v3[7] = 0.0;
    Real32x9_Rotate(v5, v5, 0.0, vAlpha, 0.0);
    v3 += 10;
    ++iSide;
  }
  while ( (int)v3 < 133164544 );
}

// source: e/3/pc/pc_lightmap.c:2226  [size]
void __cdecl Lightmap_Close()
{
  QTask_DeleteQTaskEvent(Lightmap_eEnumerateQTaskEvent);
  QTask_DeleteQTaskEvent(Lightmap_eDrawQTaskEvent);
}

// source: e/3/pc/pc_lightmap.c:2245  [size]
enum bool __cdecl Lightmap_LockReadOnly(struct Mesh3D_Lightmap_t *ptLightmap)
{
  if ( AppContext_tAppContext.isMainMenu
    || ptLightmap->tTexInfo.ptDirect3DTexture->lpVtbl->LockRect(
         ptLightmap->tTexInfo.ptDirect3DTexture,
         0,
         &Lightmap_tLockInfo,
         nullptr,
         16u) < 0 )
  {
    return false;
  }
  Lightmap_ptLocked = ptLightmap;
  return true;
}

// source: e/3/pc/pc_lightmap.c:2279  [size]
void __cdecl Lightmap_Unlock(struct Mesh3D_Lightmap_t *ptLightmap)
{
  if ( AppContext_tAppContext.isMainMenu == false )
  {
    ptLightmap->tTexInfo.ptDirect3DTexture->lpVtbl->UnlockRect(ptLightmap->tTexInfo.ptDirect3DTexture, 0);
    Lightmap_ptLocked = nullptr;
  }
}

// source: e/3/pc/pc_lightmap.c:2312  [size]
unsigned int __cdecl Lightmap_ReadTexel(struct Mesh3D_Lightmap_t *ptLightmap, float vU, float vV)
{
  #pragma pack(push, 1)
  union
  {
    struct { enum _D3DFORMAT eDirect3DFormat; };
    struct { char igi2_o1[32]; int nRPos; };
    struct { char igi2_o2[36]; int nRSize; };
    struct { char igi2_o3[40]; int nGPos; };
    struct { char igi2_o4[44]; int nGSize; };
    struct { char igi2_o5[48]; int nBPos; };
    struct { char igi2_o6[52]; int nAPos; };
    struct { char igi2_o7[56]; __int64 nASize; };
    char igi2_extent[64];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v3; // ebp
  int Depth; // eax
  unsigned int v6; // edx
  unsigned int v7; // eax
  unsigned int v8; // esi
  unsigned int v9; // edx
  unsigned int v10; // eax
  unsigned int v11; // esi
  unsigned int v12; // edx
  unsigned int v13; // esi
  int vUa = *(int *)&vU; // [esp+3Ch] [ebp+8h] ARGSLOT

  igi2_frame.nRPos = ptLightmap->tTexInfo.nWidth;
  igi2_frame.nASize = (__int64)((double)igi2_frame.nRPos * ptLightmap->tTexInfo.tUVScale.vX * vU);
  v3 = igi2_frame.nASize;
  igi2_frame.nASize = (__int64)((double)ptLightmap->tTexInfo.nHeight * ptLightmap->tTexInfo.tUVScale.vY * vV);
  vUa = igi2_frame.nASize;
  if ( AppContext_tAppContext.isMainMenu
    || ptLightmap->tTexInfo.ptDirect3DTexture->lpVtbl->LockRect(
         ptLightmap->tTexInfo.ptDirect3DTexture,
         0,
         &Lightmap_tLockInfo,
         nullptr,
         16u) < 0 )
  {
    return 0;
  }
  igi2_frame.eDirect3DFormat = ptLightmap->tTexInfo.eDirect3DFormat;
  Lightmap_ptLocked = ptLightmap;
  Direct3D_GetColorLayout(igi2_frame.eDirect3DFormat, &igi2_frame.nAPos, &igi2_frame.nRPos, &igi2_frame.nGPos, &igi2_frame.nBPos, (int *)&igi2_frame.nASize, &igi2_frame.nRSize, &igi2_frame.nGSize, (int *)&vV);
  Depth = Direct3D_GetDepth(ptLightmap->tTexInfo.eDirect3DFormat);
  if ( Depth == 16 )
  {
    v6 = *(unsigned __int16 *)((char *)Lightmap_tLockInfo.pBits + 2 * v3 + vUa * Lightmap_tLockInfo.Pitch);
  }
  else
  {
    if ( Depth != 32 )
    {
      LDebug_Error("Lightmap format not supported");
      abort();
    }
    v6 = *(_DWORD *)((char *)Lightmap_tLockInfo.pBits + 4 * v3 + vUa * Lightmap_tLockInfo.Pitch);
  }
  v7 = ((1 << igi2_frame.nRSize) - 1) & (v6 >> igi2_frame.nRPos);
  v8 = ((1 << igi2_frame.nGSize) - 1) & (v6 >> igi2_frame.nGPos);
  v9 = ((1 << SLOBYTE(vV)) - 1) & (v6 >> igi2_frame.nBPos);
  if ( igi2_frame.nRSize > 8 )
    v10 = v7 >> (igi2_frame.nRSize - 8);
  else
    v10 = v7 << (8 - igi2_frame.nRSize);
  if ( igi2_frame.nGSize > 8 )
    v11 = v8 >> (igi2_frame.nGSize - 8);
  else
    v11 = v8 << (8 - igi2_frame.nGSize);
  if ( SLODWORD(vV) > 8 )
    v12 = v9 >> (LOBYTE(vV) - 8);
  else
    v12 = v9 << (8 - LOBYTE(vV));
  v13 = v12 | ((v11 | (v10 << 8)) << 8);
  if ( AppContext_tAppContext.isMainMenu == false )
  {
    ptLightmap->tTexInfo.ptDirect3DTexture->lpVtbl->UnlockRect(ptLightmap->tTexInfo.ptDirect3DTexture, 0);
    Lightmap_ptLocked = nullptr;
  }
  return v13;
}

// source: e/3/pc/pc_lightmap.c:2395  [size]
__int16 __cdecl Lightmap_GetEnumerateLightmapQTaskEvent()
{
  return Lightmap_eEnumerateQTaskEvent;
}

// source: e/3/pc/pc_lightmap.c:2408  [size]
__int16 __cdecl Lightmap_GetDrawLightmapQTaskEvent()
{
  return Lightmap_eDrawQTaskEvent;
}
