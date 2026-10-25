/* e/3/pc/pc_envmap.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: e/3/pc/pc_envmap.c:82  [size]
int __cdecl Envmap_RenderToSurface_QSortCallback(void **ppx1, void **ppx2)
{
  int v2; // eax
  int v3; // ecx

  v2 = *((_DWORD *)*ppx1 + 1);
  v3 = *((_DWORD *)*ppx2 + 1);
  if ( v2 == v3 )
    return 0;
  else
    return 2 * (v2 > v3) - 1;
}

// source: e/3/pc/pc_envmap.c:107  [size~]
void __cdecl Envmap_RenderToSurface(struct QObjectVector_s *ptTaskVector)
{
  unsigned int nAllocated; // eax
  signed int v2; // eax
  enum bool v3; // ebp
  signed int v4; // edi
  int v5; // eax
  void (__cdecl *pfHandler)(int, _DWORD); // ecx
  struct IDirect3DDevice8Vtbl *lpVtbl; // edx
  int v8; // [esp+20h] [ebp-4h]

  Direct3D_ptDevice->lpVtbl->BeginScene(Direct3D_ptDevice);
  ((void (__stdcall *)(struct IDirect3DDevice8 *, _DWORD, _DWORD, int, _DWORD, int, _DWORD))Direct3D_ptDevice->lpVtbl->Clear)(
    Direct3D_ptDevice,
    0,
    0,
    3,
    0,
    1065353216,
    0);
  nAllocated = ptTaskVector->nAllocated;
  if ( nAllocated )
    qsort(ptTaskVector->papxElement, nAllocated, 4, Envmap_RenderToSurface_QSortCallback);
  v2 = ptTaskVector->nAllocated;
  v3 = ShadowVolume_isEnabled;
  v4 = 0;
  v8 = ShadowVolume_nUseAsm;
  ShadowVolume_isEnabled = false;
  ShadowVolume_nUseAsm = 0;
  if ( v2 > 0 )
  {
    do
    {
      v5 = *(_DWORD *)ptTaskVector->papxElement[v4];
      pfHandler = (void (__cdecl *)(int, _DWORD))QTask_aatQTaskFinalEvent[Envmap_eDrawQTaskEvent][*(unsigned __int16 *)(v5 + 36)].pfHandler;
      if ( pfHandler )
        pfHandler(v5, 0);
      ++v4;
    }
    while ( v4 < (signed int)ptTaskVector->nAllocated );
  }
  ShadowVolume_isEnabled = v3
                        && (~LOBYTE(Direct3D_tCaps.StencilCaps) & 0x1D) == 0
                        && (Direct3D_tActiveParameters.AutoDepthStencilFormat == D3DFMT_D24S8
                         || Direct3D_tActiveParameters.AutoDepthStencilFormat == D3DFMT_D24X4S4);
  lpVtbl = Direct3D_ptDevice->lpVtbl;
  ShadowVolume_nUseAsm = v8;
  lpVtbl->EndScene(Direct3D_ptDevice);
}

// source: e/3/pc/pc_envmap.c:147  [size~]
void __cdecl Envmap_CubeMapRender(
        struct QObjectVector_s *ptTaskVector,
        struct real32x3_t *ptPos,
        float vFOV,
        int nResolution,
        enum Envmap_Source_e eSourceType,
        struct IDirect3DCubeTexture8 **pptOutCubeMap)
{
  #pragma pack(push, 1)
  union
  {
    struct { enum _D3DCUBEMAP_FACES v11; };
    struct { char igi2_o1[4]; struct IDirect3DSurface8 *v12; };
    struct { char igi2_o2[8]; struct IDirect3DSurface8 *v13; };
    struct { char igi2_o3[12]; struct real32x2_t v14; };
    struct { char igi2_o4[20]; float v15; };
    struct { char igi2_o5[24]; int v16; };
    struct { char igi2_o6[28]; float v17; };
    struct { char igi2_o7[32]; float v18; };
    struct { char igi2_o8[36]; struct IDirect3DCubeTexture8 *v19; };
    struct { char igi2_o9[40]; struct IDirect3DSurface8 *v20; };
    struct { char igi2_o10[44]; struct IDirect3DSurface8 *v21; };
    struct { char igi2_o11[48]; struct IDirect3DSurface8 *v22; };
    struct { char igi2_o12[52]; _BYTE ptClippingRect[40]; };
    struct { char igi2_o13[92]; int v24[3]; };
    struct { char igi2_o14[104]; int v25[16]; };
    struct { char igi2_o15[168]; struct RenderContext_s ptRenderContext; };
    struct { char igi2_o16[248]; struct TransContext_s ptTransContext; };
    char igi2_extent[416];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  __int32 v6; // eax
  double vX; // st6
  double vY; // st6
  double vZ; // st6
  enum _D3DCUBEMAP_FACES v10; // edi

  igi2_frame.v13 = nullptr;
  Direct3D_ptDevice->lpVtbl->EndScene(Direct3D_ptDevice);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_MULTISAMPLEANTIALIAS, 1u);
  Direct3D_ptDevice->lpVtbl->CreateCubeTexture(
    Direct3D_ptDevice,
    nResolution,
    1u,
    0,
    D3DFMT_X8R8G8B8,
    D3DPOOL_MANAGED,
    &igi2_frame.v19);
  Direct3D_ptDevice->lpVtbl->GetRenderTarget(Direct3D_ptDevice, &igi2_frame.v22);
  Direct3D_ptDevice->lpVtbl->GetDepthStencilSurface(Direct3D_ptDevice, &igi2_frame.v20);
  Direct3D_ptDevice->lpVtbl->CreateDepthStencilSurface(
    Direct3D_ptDevice,
    nResolution,
    nResolution,
    D3DFMT_D24X8,
    D3DMULTISAMPLE_NONE,
    &igi2_frame.v21);
  RenderContext_Alloc(&igi2_frame.ptRenderContext, 1);
  *(float *)&igi2_frame.ptClippingRect[8] = (float)nResolution;
  *(float *)&igi2_frame.ptClippingRect[12] = *(float *)&igi2_frame.ptClippingRect[8];
  igi2_frame.v12 = *(struct IDirect3DSurface8 **)&igi2_frame.ptClippingRect[8];
  igi2_frame.v14.vX = *(float *)&igi2_frame.ptClippingRect[8];
  *(_DWORD *)igi2_frame.ptClippingRect = 0;
  igi2_frame.v14.vY = *(float *)&igi2_frame.ptClippingRect[8];
  *(float *)&igi2_frame.v16 = 0.0;
  *(_DWORD *)&igi2_frame.ptClippingRect[4] = 0;
  igi2_frame.v17 = 0.0;
  *(float *)&igi2_frame.ptClippingRect[20] = (float)(nResolution >> 1);
  *(float *)&igi2_frame.ptClippingRect[16] = *(float *)&igi2_frame.ptClippingRect[20];
  RenderContext_SetClippingRect(&igi2_frame.ptRenderContext, (struct ClippingRect_s *)igi2_frame.ptClippingRect);
  igi2_frame.ptRenderContext.tDisplayAreaMin.vX = 0.0;
  igi2_frame.ptRenderContext.tDisplayAreaMax = igi2_frame.v14;
  igi2_frame.ptRenderContext.tDisplayAreaMin.vY = 0.0;
  igi2_frame.ptTransContext.vFOVY = vFOV;
  igi2_frame.ptTransContext.vFOVX = vFOV;
  qmemcpy(&RenderContext_tActiveRenderContext, &igi2_frame.ptRenderContext, sizeof(RenderContext_tActiveRenderContext));
  igi2_frame.ptTransContext.vScreenFOVX = (double)(nResolution / 2) * vFOV;
  igi2_frame.ptTransContext.vScreenFOVY = igi2_frame.ptTransContext.vScreenFOVX;
  igi2_frame.ptTransContext.vScreenOriginX = *(float *)&igi2_frame.v12 * 0.5;
  v6 = 0;
  igi2_frame.ptTransContext.vScreenOriginY = igi2_frame.ptTransContext.vScreenOriginX;
  RenderContext_nActiveRenderContextTimeStamp += 2;
  igi2_frame.ptTransContext.isDraw = 1;
  igi2_frame.ptTransContext.eLayer = TRANSCONTEXT_LAYER_HEMICUBE;
  igi2_frame.v11 = D3DCUBEMAP_FACE_POSITIVE_X;
  while ( 1 )
  {
    vX = ptPos->vX;
    *(float *)&igi2_frame.v16 = 0.0;
    igi2_frame.ptTransContext.tPos.vX = vX;
    igi2_frame.v17 = 0.0;
    vY = ptPos->vY;
    igi2_frame.v18 = 0.0;
    igi2_frame.ptTransContext.tPos.vY = vY;
    igi2_frame.v14.vX = 0.0;
    vZ = ptPos->vZ;
    igi2_frame.v14.vY = 0.0;
    igi2_frame.ptTransContext.tPos.vZ = vZ;
    igi2_frame.v15 = 0.0;
    switch ( v6 )
    {
      case 0:
        igi2_frame.v15 = -1.0;
        *(float *)&igi2_frame.v16 = 1.0;
        break;
      case 1:
        *(float *)&igi2_frame.v16 = -1.0;
        igi2_frame.v15 = -1.0;
        break;
      case 2:
        igi2_frame.v18 = 1.0;
        igi2_frame.v14.vY = 1.0;
        break;
      case 3:
        igi2_frame.v18 = -1.0;
        igi2_frame.v14.vY = 1.0;
        break;
      case 4:
        igi2_frame.v15 = -1.0;
        igi2_frame.v17 = 1.0;
        break;
      case 5:
        igi2_frame.v17 = -1.0;
        igi2_frame.v15 = -1.0;
        break;
      default:
        break;
    }
    memset(igi2_frame.v24, 0, sizeof(igi2_frame.v24));
    D3DXMatrixLookAtLH((int)igi2_frame.v25, (int)igi2_frame.v24, (int)&igi2_frame.v16, (int)&igi2_frame.v14);
    *(_DWORD *)&igi2_frame.ptClippingRect[24] = igi2_frame.v25[2];
    *(_DWORD *)&igi2_frame.ptClippingRect[12] = igi2_frame.v25[1];
    *(_DWORD *)igi2_frame.ptClippingRect = igi2_frame.v25[0];
    *(_DWORD *)&igi2_frame.ptClippingRect[28] = igi2_frame.v25[6];
    *(_DWORD *)&igi2_frame.ptClippingRect[16] = igi2_frame.v25[5];
    *(_DWORD *)&igi2_frame.ptClippingRect[4] = igi2_frame.v25[4];
    *(_DWORD *)&igi2_frame.ptClippingRect[32] = igi2_frame.v25[10];
    *(_DWORD *)&igi2_frame.ptClippingRect[20] = igi2_frame.v25[9];
    *(_DWORD *)&igi2_frame.ptClippingRect[8] = igi2_frame.v25[8];
    qmemcpy(&igi2_frame.ptTransContext, igi2_frame.ptClippingRect, 0x28u);
    TransContext_SetHemicubeTransContext(&igi2_frame.ptTransContext, nResolution, nResolution, 1.0);
    v10 = igi2_frame.v11;
    igi2_frame.v19->lpVtbl->GetCubeMapSurface(igi2_frame.v19, igi2_frame.v11, 0, &igi2_frame.v13);
    Direct3D_ptDevice->lpVtbl->CreateRenderTarget(
      Direct3D_ptDevice,
      nResolution,
      nResolution,
      D3DFMT_X8R8G8B8,
      D3DMULTISAMPLE_NONE,
      0,
      &igi2_frame.v12);
    Direct3D_ptDevice->lpVtbl->SetRenderTarget(Direct3D_ptDevice, igi2_frame.v12, igi2_frame.v21);
    Envmap_RenderToSurface(ptTaskVector);
    Direct3D_ptDevice->lpVtbl->CopyRects(Direct3D_ptDevice, igi2_frame.v12, nullptr, 0, igi2_frame.v13, nullptr);
    igi2_frame.v12->lpVtbl->Release(igi2_frame.v12);
    if ( igi2_frame.v13 )
    {
      igi2_frame.v13->lpVtbl->Release(igi2_frame.v13);
      igi2_frame.v13 = nullptr;
    }
    ++igi2_frame.v11;
    if ( v10 + 1 >= 6 )
      break;
    v6 = v10 + 1;
  }
  Direct3D_ptDevice->lpVtbl->SetRenderTarget(Direct3D_ptDevice, igi2_frame.v22, igi2_frame.v20);
  igi2_frame.v22->lpVtbl->Release(igi2_frame.v22);
  igi2_frame.v20->lpVtbl->Release(igi2_frame.v20);
  igi2_frame.v21->lpVtbl->Release(igi2_frame.v21);
  TransContext_isValid = 0;
  RenderContext_DeAlloc(&igi2_frame.ptRenderContext);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_MULTISAMPLEANTIALIAS, 0);
  *pptOutCubeMap = igi2_frame.v19;
  Direct3D_ptDevice->lpVtbl->BeginScene(Direct3D_ptDevice);
}

// source: e/3/pc/pc_envmap.c:385  [size]
void __cdecl Envmap_PlainMapRender(
        struct QObjectVector_s *ptTaskVector,
        struct real32x3_t *ptPos,
        struct real32x9_t *ptOrientation,
        float vFOV,
        int nResolution,
        enum Envmap_Source_e eSourceType,
        struct IDirect3DTexture8 **pptOutTexture)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct IDirect3DSurface8 *ptRenderTarget; };
    struct { char igi2_o1[4]; struct IDirect3DSurface8 *ptZBuffer; };
    struct { char igi2_o2[8]; int isOldTransContextValid; };
    struct { char igi2_o3[12]; struct IDirect3DSurface8 *ptBackBuffer; };
    struct { char igi2_o4[16]; int isOldRenderContextValid; };
    struct { char igi2_o5[20]; struct IDirect3DSurface8 *ptSurface; };
    struct { char igi2_o6[24]; struct IDirect3DTexture8 *ptTextureToRender; };
    struct { char igi2_o7[28]; float vWidth; };
    struct { char igi2_o8[32]; struct real32x2_t tMinCoord; };
    struct { char igi2_o9[40]; struct IDirect3DSurface8 *ptMultisampleZBuffer; };
    struct { char igi2_o10[44]; struct real32x2_t tMaxCoord; };
    struct { char igi2_o11[52]; struct ClippingRect_s tClippingRect; };
    struct { char igi2_o12[76]; struct RenderContext_s tRenderContext; };
    struct { char igi2_o13[156]; struct TransContext_s tTransContext; };
    struct { char igi2_o14[324]; struct RenderContext_s tOldRenderContext; };
    struct { char igi2_o15[404]; struct TransContext_s tOldTransContext; };
    char igi2_extent[572];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct IDirect3DDevice8Vtbl *lpVtbl; // ecx

  lpVtbl = Direct3D_ptDevice->lpVtbl;
  igi2_frame.isOldTransContextValid = 0;
  igi2_frame.isOldRenderContextValid = 0;
  lpVtbl->EndScene(Direct3D_ptDevice);
  Direct3D_ptDevice->lpVtbl->CreateTexture(
    Direct3D_ptDevice,
    nResolution,
    nResolution,
    1u,
    0,
    D3DFMT_X8R8G8B8,
    D3DPOOL_MANAGED,
    &igi2_frame.ptTextureToRender);
  Direct3D_ptDevice->lpVtbl->GetRenderTarget(Direct3D_ptDevice, &igi2_frame.ptBackBuffer);
  Direct3D_ptDevice->lpVtbl->GetDepthStencilSurface(Direct3D_ptDevice, &igi2_frame.ptZBuffer);
  Direct3D_ptDevice->lpVtbl->CreateDepthStencilSurface(
    Direct3D_ptDevice,
    nResolution,
    nResolution,
    D3DFMT_D24X8,
    D3DMULTISAMPLE_NONE,
    &igi2_frame.ptMultisampleZBuffer);
  if ( TransContext_isValid )
  {
    qmemcpy(&igi2_frame.tOldTransContext, &TransContext_tActiveTransContext, sizeof(igi2_frame.tOldTransContext));
    igi2_frame.isOldTransContextValid = 1;
  }
  if ( RenderContext_isValid )
  {
    qmemcpy(&igi2_frame.tOldRenderContext, &RenderContext_tActiveRenderContext, sizeof(igi2_frame.tOldRenderContext));
    igi2_frame.isOldRenderContextValid = 1;
  }
  RenderContext_Alloc(&igi2_frame.tRenderContext, 1);
  igi2_frame.tClippingRect.vWidth = (float)nResolution;
  igi2_frame.ptRenderTarget = (struct IDirect3DSurface8 *)(nResolution >> 1);
  igi2_frame.tClippingRect.vHeight = igi2_frame.tClippingRect.vWidth;
  igi2_frame.vWidth = igi2_frame.tClippingRect.vWidth;
  igi2_frame.tMaxCoord.vX = igi2_frame.tClippingRect.vWidth;
  igi2_frame.tClippingRect.vX = 0.0;
  igi2_frame.tMaxCoord.vY = igi2_frame.tClippingRect.vWidth;
  igi2_frame.tMinCoord.vX = 0.0;
  igi2_frame.tClippingRect.vY = 0.0;
  igi2_frame.tMinCoord.vY = 0.0;
  igi2_frame.tClippingRect.vHalfHeight = (float)(nResolution >> 1);
  igi2_frame.tClippingRect.vHalfWidth = igi2_frame.tClippingRect.vHalfHeight;
  RenderContext_SetClippingRect(&igi2_frame.tRenderContext, &igi2_frame.tClippingRect);
  igi2_frame.tRenderContext.tDisplayAreaMin = igi2_frame.tMinCoord;
  igi2_frame.tRenderContext.tDisplayAreaMax = igi2_frame.tMaxCoord;
  RenderContext_nActiveRenderContextTimeStamp += 2;
  qmemcpy(&RenderContext_tActiveRenderContext, &igi2_frame.tRenderContext, sizeof(RenderContext_tActiveRenderContext));
  igi2_frame.tTransContext.tPos.vX = ptPos->vX;
  igi2_frame.tTransContext.tPos.vY = ptPos->vY;
  igi2_frame.tTransContext.tPos.vZ = ptPos->vZ;
  igi2_frame.tTransContext.vFOVY = vFOV;
  igi2_frame.ptRenderTarget = (struct IDirect3DSurface8 *)(nResolution / 2);
  igi2_frame.tTransContext.vFOVX = vFOV;
  igi2_frame.tTransContext.isDraw = 1;
  igi2_frame.tTransContext.eLayer = TRANSCONTEXT_LAYER_HEMICUBE;
  igi2_frame.tTransContext.vScreenFOVX = (double)(nResolution / 2) * vFOV;
  igi2_frame.tTransContext.vScreenFOVY = igi2_frame.tTransContext.vScreenFOVX;
  igi2_frame.tTransContext.vScreenOriginX = igi2_frame.vWidth * 0.5;
  igi2_frame.tTransContext.vScreenOriginY = igi2_frame.tTransContext.vScreenOriginX;
  qmemcpy(&igi2_frame.tTransContext, ptOrientation, 0x28u);
  TransContext_SetHemicubeTransContext(&igi2_frame.tTransContext, nResolution, nResolution, 1.0);
  igi2_frame.ptTextureToRender->lpVtbl->GetSurfaceLevel(igi2_frame.ptTextureToRender, 0, &igi2_frame.ptSurface);
  Direct3D_ptDevice->lpVtbl->CreateRenderTarget(
    Direct3D_ptDevice,
    nResolution,
    nResolution,
    D3DFMT_X8R8G8B8,
    D3DMULTISAMPLE_NONE,
    0,
    &igi2_frame.ptRenderTarget);
  Direct3D_ptDevice->lpVtbl->SetRenderTarget(Direct3D_ptDevice, igi2_frame.ptRenderTarget, igi2_frame.ptMultisampleZBuffer);
  Envmap_RenderToSurface(ptTaskVector);
  Direct3D_ptDevice->lpVtbl->CopyRects(Direct3D_ptDevice, igi2_frame.ptRenderTarget, nullptr, 0, igi2_frame.ptSurface, nullptr);
  igi2_frame.ptRenderTarget->lpVtbl->Release(igi2_frame.ptRenderTarget);
  Envmap_RenderToSurface(ptTaskVector);
  igi2_frame.ptSurface->lpVtbl->Release(igi2_frame.ptSurface);
  Direct3D_ptDevice->lpVtbl->SetRenderTarget(Direct3D_ptDevice, igi2_frame.ptBackBuffer, igi2_frame.ptZBuffer);
  igi2_frame.ptBackBuffer->lpVtbl->Release(igi2_frame.ptBackBuffer);
  igi2_frame.ptZBuffer->lpVtbl->Release(igi2_frame.ptZBuffer);
  if ( igi2_frame.isOldTransContextValid )
    TransContext_SetActiveTransContext(&igi2_frame.tOldTransContext);
  if ( igi2_frame.isOldRenderContextValid )
  {
    qmemcpy(&RenderContext_tActiveRenderContext, &igi2_frame.tOldRenderContext, sizeof(RenderContext_tActiveRenderContext));
    ++RenderContext_nActiveRenderContextTimeStamp;
  }
  RenderContext_DeAlloc(&igi2_frame.tRenderContext);
  *pptOutTexture = igi2_frame.ptTextureToRender;
  Direct3D_ptDevice->lpVtbl->BeginScene(Direct3D_ptDevice);
}

// source: e/3/pc/pc_envmap.c:537  [size]
void __cdecl QTask_EnumerateEnvmapHandler(struct QTask_s *ptQTask, void *pxContext)
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
      pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[Envmap_eEnumerateQTaskEvent][ptHead->eQTaskType].pfHandler;
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

// source: e/3/pc/pc_envmap.c:552  [size]
void __cdecl Envmap_SetTestRenderState()
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
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_TEXTURETRANSFORMFLAGS, 0);
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

// source: e/3/pc/pc_envmap.c:600  [size]
void __cdecl Envmap_SpriteDraw(
        struct real32x2_t *ptOffset,
        float vWidth,
        float vHeight,
        struct IDirect3DBaseTexture8 *ptTexture)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v11; };
    struct { char igi2_o1[4]; struct Envmap_SpriteVertex_t atSpriteVertex[4]; };
    char igi2_extent[100];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double vX; // st7
  double vY; // st6
  double v6; // rt0
  double v7; // st6
  struct RenderStateBlock_t *v8; // ecx
  struct RenderStateBlock_t *v9; // edx
  struct RenderStateBlock_t *v10; // ecx
  float vWidtha = *(float *)&vHeight; // [esp+7Ch] [ebp+8h] ARGSLOT

  vX = ptOffset->vX;
  memset(igi2_frame.atSpriteVertex, 0, sizeof(igi2_frame.atSpriteVertex));
  igi2_frame.atSpriteVertex[0].vX = vX;
  vY = ptOffset->vY;
  igi2_frame.atSpriteVertex[0].vY = ptOffset->vY;
  v6 = vY;
  igi2_frame.atSpriteVertex[1].vX = vX;
  igi2_frame.atSpriteVertex[1].vV = 1.0;
  igi2_frame.atSpriteVertex[2].vU = 1.0;
  v7 = vHeight + ptOffset->vY;
  igi2_frame.atSpriteVertex[3].vU = 1.0;
  igi2_frame.atSpriteVertex[3].vV = 1.0;
  igi2_frame.v11 = v7;
  igi2_frame.atSpriteVertex[1].vY = v7;
  igi2_frame.atSpriteVertex[3].vY = igi2_frame.v11;
  v8 = Direct3D_ptBlendStateBlock;
  vWidtha = vWidth + ptOffset->vX;
  igi2_frame.atSpriteVertex[2].vX = vWidtha;
  igi2_frame.atSpriteVertex[3].vX = vWidtha;
  igi2_frame.atSpriteVertex[2].vY = v6;
  Direct3D_ptTextureStateBlock->eCurrentState = -1;
  v9 = Direct3D_ptGenericStateBlock;
  v8->eCurrentState = -1;
  v10 = Direct3D_ptClippingStateBlock;
  v9->eCurrentState = -1;
  v10->eCurrentState = -1;
  Envmap_SetTestRenderState();
  Direct3D_ptDevice->lpVtbl->SetVertexShader(Direct3D_ptDevice, 260u);
  Direct3D_ptDevice->lpVtbl->SetTexture(Direct3D_ptDevice, 0, ptTexture);
  Direct3D_ptDevice->lpVtbl->DrawPrimitiveUP(Direct3D_ptDevice, D3DPT_TRIANGLESTRIP, 2u, igi2_frame.atSpriteVertex, 24u);
  Direct3D_ptDevice->lpVtbl->SetTexture(Direct3D_ptDevice, 0, nullptr);
}

// source: e/3/pc/pc_envmap.c:658  [size]
struct IDirect3DSurface8 *__cdecl Envmap_SaveSurface(
        struct IDirect3DSurface8 *ptSurface,
        struct Envmap_FileHeader_t *ptHeader,
        char *zFilename)
{
  return (struct IDirect3DSurface8 *)D3DXSaveSurfaceToFileA((int)zFilename, ptHeader->eFormat, (int)ptSurface, 0, 0);
}

// source: e/3/pc/pc_envmap.c:673  [size]
struct Envmap_t *__cdecl Envmap_Draw(struct Envmap_t *ptEnvmap)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct IDirect3DSurface8 *ptDestSurface; };
    struct { char igi2_o1[4]; struct IDirect3DSurface8 *ptSrcSurface; };
    struct { char igi2_o2[8]; struct real32x2_t atTranslations[6]; };
    char igi2_extent[56];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct IDirect3DCubeTexture8 *ptCubemap; // edi
  bool v2; // zf
  enum Envmap_TextureType_e eEnvmapType; // eax
  enum _D3DCUBEMAP_FACES v4; // ebx
  struct IDirect3DTexture8 **v5; // esi
  struct real32x2_t *v6; // ebx
  struct IDirect3DBaseTexture8 **v7; // esi

  ptCubemap = ptEnvmap->ptCubemap;
  v2 = ptEnvmap->ptCubemap == nullptr;
  igi2_frame.atTranslations[0].vX = 512.0;
  igi2_frame.atTranslations[0].vY = 256.0;
  igi2_frame.atTranslations[1].vX = 0.0;
  igi2_frame.atTranslations[1].vY = 256.0;
  igi2_frame.atTranslations[2].vX = 256.0;
  igi2_frame.atTranslations[2].vY = 0.0;
  igi2_frame.atTranslations[3].vX = 256.0;
  igi2_frame.atTranslations[3].vY = 512.0;
  igi2_frame.atTranslations[4].vX = 256.0;
  igi2_frame.atTranslations[4].vY = 256.0;
  igi2_frame.atTranslations[5].vX = 768.0;
  igi2_frame.atTranslations[5].vY = 256.0;
  if ( !v2 )
  {
    eEnvmapType = ptEnvmap->eEnvmapType;
    if ( eEnvmapType )
    {
      ptEnvmap = (struct Envmap_t *)(eEnvmapType - 1);
      if ( !ptEnvmap )
      {
        ptCubemap->lpVtbl->GetLevelDesc(ptCubemap, 0, (struct _D3DSURFACE_DESC *)&unk_7EFF040);
        v4 = D3DCUBEMAP_FACE_POSITIVE_X;
        v5 = (struct IDirect3DTexture8 **)&unk_7EFF028;
        do
        {
          if ( *v5 )
          {
            (*v5)->lpVtbl->Release(*v5);
            *v5 = nullptr;
          }
          Direct3D_ptDevice->lpVtbl->CreateTexture(
            Direct3D_ptDevice,
            dword_7EFF058,
            dword_7EFF05C,
            1u,
            0,
            D3DFMT_X8R8G8B8,
            D3DPOOL_MANAGED,
            v5);
          ptCubemap->lpVtbl->GetCubeMapSurface(ptCubemap, v4, 0, &igi2_frame.ptSrcSurface);
          (*v5)->lpVtbl->GetSurfaceLevel(*v5, 0, &igi2_frame.ptDestSurface);
          Direct3D_ptDevice->lpVtbl->CopyRects(Direct3D_ptDevice, igi2_frame.ptSrcSurface, nullptr, 0, igi2_frame.ptDestSurface, nullptr);
          ++v5;
          ++v4;
        }
        while ( (int)v5 < 133165120 );
        v6 = igi2_frame.atTranslations;
        v7 = (struct IDirect3DBaseTexture8 **)&unk_7EFF028;
        do
          Envmap_SpriteDraw(v6++, 256.0, 256.0, *v7++);
        while ( (int)v7 < 133165120 );
        dword_834DAE8 = (int)ptCubemap;
      }
    }
    else
    {
      Envmap_SpriteDraw(&igi2_frame.atTranslations[4], 256.0, 256.0, (struct IDirect3DBaseTexture8 *)ptCubemap);
    }
  }
  return ptEnvmap;
}

// source: e/3/pc/pc_envmap.c:739  [size]
void __cdecl Envmap_Save(struct Envmap_t *ptEnvmap, char *zPartialFilename)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct IDirect3DSurface8 *ptSurface; };
    struct { char igi2_o1[4]; char zFilename[512]; };
    char igi2_extent[516];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  enum _D3DCUBEMAP_FACES i; // esi

  if ( strlen(zPartialFilename) + 6 > 0x200 )
  {
    LDebug_Error("Environmental map: file name is too long");
    abort();
  }
  if ( ptEnvmap->eEnvmapType == ENVMAP_TYPE_CUBIC )
  {
    for ( i = D3DCUBEMAP_FACE_POSITIVE_X; i < (D3DCUBEMAP_FACE_POSITIVE_Z|D3DCUBEMAP_FACE_POSITIVE_Y); ++i )
    {
      sprintf(igi2_frame.zFilename, "%s_%d.%s", zPartialFilename, i, "bmp");
      ptEnvmap->ptCubemap->lpVtbl->GetCubeMapSurface(ptEnvmap->ptCubemap, i, 0, &igi2_frame.ptSurface);
      D3DXSaveSurfaceToFileA((int)igi2_frame.zFilename, 0, (int)igi2_frame.ptSurface, 0, 0);
      igi2_frame.ptSurface->lpVtbl->Release(igi2_frame.ptSurface);
    }
  }
}

// source: e/3/pc/pc_envmap.c:786  [size]
struct Envmap_t *__cdecl Envmap_LoadFromMemory(
        struct Envmap_t *ptEnvmap,
        unsigned __int8 **ppxRawData,
        int nSize)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct IDirect3DSurface8 *ptSurface; };
    struct { char igi2_o1[4]; struct _D3DXIMAGE_INFO tImageInfo; };
    char igi2_extent[32];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  enum Envmap_TextureType_e eEnvmapType; // eax
  struct Envmap_t *result; // eax
  enum _D3DCUBEMAP_FACES i; // esi

  D3DXGetImageInfoFromFileInMemory((int)*ppxRawData, nSize, (int)&igi2_frame.tImageInfo);
  eEnvmapType = ptEnvmap->eEnvmapType;
  if ( eEnvmapType )
  {
    result = (struct Envmap_t *)(eEnvmapType - 1);
    if ( !result )
    {
      Direct3D_ptDevice->lpVtbl->CreateCubeTexture(
        Direct3D_ptDevice,
        igi2_frame.tImageInfo.Width,
        1u,
        0,
        D3DFMT_X8R8G8B8,
        D3DPOOL_MANAGED,
        (struct IDirect3DCubeTexture8 **)ptEnvmap);
      for ( i = D3DCUBEMAP_FACE_POSITIVE_X; i < (D3DCUBEMAP_FACE_POSITIVE_Z|D3DCUBEMAP_FACE_POSITIVE_Y); ++i )
      {
        ptEnvmap->ptCubemap->lpVtbl->GetCubeMapSurface(ptEnvmap->ptCubemap, i, 0, &igi2_frame.ptSurface);
        D3DXLoadSurfaceFromFileInMemory((int)igi2_frame.ptSurface, 0, 0, (int)ppxRawData[i], nSize, 0, -1, 0, 0);
        result = (struct Envmap_t *)igi2_frame.ptSurface->lpVtbl->Release(igi2_frame.ptSurface);
      }
    }
  }
  else
  {
    Direct3D_ptDevice->lpVtbl->CreateTexture(
      Direct3D_ptDevice,
      igi2_frame.tImageInfo.Width,
      igi2_frame.tImageInfo.Width,
      1u,
      0,
      D3DFMT_X8R8G8B8,
      D3DPOOL_MANAGED,
      (struct IDirect3DTexture8 **)ptEnvmap);
    ((void (__stdcall *)(struct IDirect3DCubeTexture8 *, _DWORD, struct IDirect3DSurface8 **))ptEnvmap->ptCubemap->lpVtbl->GetCubeMapSurface)(
      ptEnvmap->ptCubemap,
      0,
      &igi2_frame.ptSurface);
    D3DXLoadSurfaceFromFileInMemory((int)igi2_frame.ptSurface, 0, 0, (int)*ppxRawData, nSize, 0, -1, 0, 0);
    return (struct Envmap_t *)igi2_frame.ptSurface->lpVtbl->Release(igi2_frame.ptSurface);
  }
  return result;
}

// source: e/3/pc/pc_envmap.c:830  [size]
char *__cdecl Envmap_GetFileExtension(char *zExtension)
{
  *(_DWORD *)zExtension = &unk_706D62;
  return zExtension;
}

// source: e/3/pc/pc_envmap.c:843  [size]
int __cdecl Envmap_Delete(int *a1)
{
  int v1; // eax
  int result; // eax

  v1 = a1[19];
  if ( !v1 )
  {
    result = *a1;
    if ( !*a1 )
      return result;
    goto LABEL_7;
  }
  if ( v1 != 1 )
  {
    LDebug_Error("Environmental map render: unknown type of environmental map");
    abort();
  }
  result = *a1;
  if ( *a1 )
  {
LABEL_7:
    result = (*(int (__stdcall **)(int))(*(_DWORD *)result + 8))(*a1);
    *a1 = 0;
    a1[23] = 0;
  }
  return result;
}

// source: e/3/pc/pc_envmap.c:879  [size]
void __cdecl Envmap_Create(struct Envmap_t *ptEnvmap, struct real32x3_t *ptPos, float vRadius)
{
  struct QObjectVector_s *v3; // edi
  float v4; // eax
  float v5; // ecx
  struct QTask_s *ptHead; // ecx
  int v7; // edx
  struct QTask_s *v8; // eax
  void (__cdecl *pfHandler)(struct QTask_s *, struct real32x3_t *); // eax
  int v10; // edx
  enum Envmap_TextureType_e eEnvmapType; // eax
  struct real32x3_t tCameraPos; // [esp+10h] [ebp-Ch] BYREF

  v3 = (struct QObjectVector_s *)Mem_AllocFn(52, 4);
  v3->isStrictOrder = false;
  v3->nSize = 0;
  v3->nAllocated = 0;
  v3->nReallocSize = 32;
  v3->papxElement = nullptr;
  v3->nElementSize = 12;
  v3->tMemPool.nBlocks = 0;
  v3->tMemPool.nAllocatedBlocks = 0;
  v3->tMemPool.nAlignment = 4;
  v3->tMemPool.nBlockSize = 12;
  v3->tMemPool.nReAllocBlocks = 32;
  v3->tMemPool.tMemPoolFreeList.ptHead = nullptr;
  v3->tMemPool.tMemPoolSegmentList.ptHead = nullptr;
  MemPool_ReAlloc(&v3->tMemPool, 0x40u);
  QObjectVector_Realloc(v3, 0x40u);
  v4 = *(float *)&ptEnvmap->eSource;
  v5 = *(float *)&ptEnvmap->bTasksToRender;
  LODWORD(tCameraPos.vX) = v3;
  tCameraPos.vY = v4;
  tCameraPos.vZ = v5;
  ptHead = Level_ptQLevelQTask->tQTask.tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v7 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v8 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v8 = nullptr;
      QTask_atProtectedQTaskStack[v7].ptQTask = v8;
      pfHandler = (void (__cdecl *)(struct QTask_s *, struct real32x3_t *))QTask_aatQTaskFinalEvent[Envmap_eEnumerateQTaskEvent][ptHead->eQTaskType].pfHandler;
      v10 = v7 + 1;
      QTask_nProtectedQTaskStackOffset = v10;
      if ( pfHandler )
      {
        pfHandler(ptHead, &tCameraPos);
        v10 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v10];
      v7 = v10 - 1;
      QTask_nProtectedQTaskStackOffset = v7;
    }
    while ( ptHead );
  }
  if ( v3->nAllocated )
  {
    Envmap_Delete((int *)ptEnvmap);
    eEnvmapType = ptEnvmap->eEnvmapType;
    tCameraPos.vX = ptEnvmap->tCameraPos.vX;
    tCameraPos.vY = ptEnvmap->tCameraPos.vY;
    tCameraPos.vZ = ptEnvmap->tCameraPos.vZ;
    if ( eEnvmapType )
    {
      if ( eEnvmapType != ENVMAP_TYPE_CUBIC )
      {
        LDebug_Error("Environmental map render: unknown type of environmental map");
        abort();
      }
      Envmap_CubeMapRender(
        v3,
        &tCameraPos,
        ptEnvmap->vFOV,
        ptEnvmap->nResolution,
        ptEnvmap->eSource,
        &ptEnvmap->ptCubemap);
    }
    else
    {
      ptPos->vZ = ptPos->vZ - vRadius / ptEnvmap->vFOV;
      Envmap_PlainMapRender(
        v3,
        ptPos,
        &ptEnvmap->tCameraOrientation,
        ptEnvmap->vFOV,
        ptEnvmap->nResolution,
        ptEnvmap->eSource,
        (struct IDirect3DTexture8 **)ptEnvmap);
    }
    ptEnvmap->isValid = 1;
  }
  QObjectVector_Delete(v3);
}

// source: e/3/pc/pc_envmap.c:950  [size]
__int16 __cdecl Envmap_GetEnumerateEnvmapQTaskEvent()
{
  return Envmap_eEnumerateQTaskEvent;
}

// source: e/3/pc/pc_envmap.c:963  [size]
__int16 __cdecl Envmap_GetDrawEnvmapQTaskEvent()
{
  return Envmap_eDrawQTaskEvent;
}

// source: e/3/pc/pc_envmap.c:977  [size]
void __cdecl Envmap_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  __int16 v1; // [esp-8h] [ebp-8h]

  Envmap_eDrawQTaskEvent = QTask_NewQTaskEventFn(0, "DrawEnvmap");
  Envmap_eEnumerateQTaskEvent = QTask_NewQTaskEventFn(0, "EnumerateEnvmap");
  v1 = Envmap_eEnumerateQTaskEvent;
  BaseQTaskType = QTask_GetBaseQTaskType();
  QTask_LinkQTaskEventHandlerFn(BaseQTaskType, v1, QTask_EnumerateEnvmapHandler);
}

// source: e/3/pc/pc_envmap.c:994  [size]
void __cdecl Envmap_Close()
{
  QTask_DeleteQTaskEvent(Envmap_eEnumerateQTaskEvent);
  QTask_DeleteQTaskEvent(Envmap_eDrawQTaskEvent);
}
