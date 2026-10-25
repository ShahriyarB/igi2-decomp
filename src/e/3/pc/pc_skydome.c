/* e/3/pc/pc_skydome.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: e/3/pc/pc_skydome.c:110  [anchor-callee]
unsigned int __cdecl SkyDome_InterpolateVertexColour(
        struct real32x3_t *ptCol0,
        struct real32x3_t *ptCol1,
        struct real32x3_t *ptCol2,
        struct real32x3_t *ptCol3,
        float vScale0,
        float vScale1)
{
  double v6; // st7
  double v7; // st6
  double v8; // st7
  float tTempCol1_4; // [esp+4h] [ebp-20h]
  float tTempCol1_8; // [esp+8h] [ebp-1Ch]
  float tTempCol2; // [esp+Ch] [ebp-18h]
  float tTempCol2_4; // [esp+10h] [ebp-14h]
  float tTempCol0_8; // [esp+20h] [ebp-4h]

  v6 = (ptCol1->vX - ptCol0->vX) * vScale0 + ptCol0->vX;
  v7 = (ptCol1->vY - ptCol0->vY) * vScale0 + ptCol0->vY;
  tTempCol0_8 = (ptCol1->vZ - ptCol0->vZ) * vScale0 + ptCol0->vZ;
  tTempCol1_4 = (ptCol3->vY - ptCol2->vY) * vScale0 + ptCol2->vY;
  tTempCol1_8 = (ptCol3->vZ - ptCol2->vZ) * vScale0 + ptCol2->vZ;
  tTempCol2 = ((ptCol3->vX - ptCol2->vX) * vScale0 + ptCol2->vX - v6) * vScale1 + v6;
  tTempCol2_4 = (tTempCol1_4 - v7) * vScale1 + v7;
  v8 = (tTempCol1_8 - tTempCol0_8) * vScale1 + tTempCol0_8;
  if ( tTempCol2 >= 0.0 )
  {
    if ( tTempCol2 > 1.0 )
      tTempCol2 = 1.0;
  }
  else
  {
    tTempCol2 = 0.0;
  }
  if ( tTempCol2_4 >= 0.0 )
  {
    if ( tTempCol2_4 > 1.0 )
      tTempCol2_4 = 1.0;
  }
  else
  {
    tTempCol2_4 = 0.0;
  }
  if ( v8 >= 0.0 )
  {
    if ( v8 > 1.0 )
      v8 = 1.0;
  }
  else
  {
    v8 = 0.0;
  }
  return (__int64)(255.0 * v8)
       | (((unsigned int)(__int64)(tTempCol2_4 * 255.0) | ((unsigned int)(__int64)(tTempCol2 * 255.0) << 8)) << 8);
}

// source: e/3/pc/pc_skydome.c:145  [anchor-callee]
void __cdecl SkyDome_InitialiseVertexBuffer(struct SkyDome_s *ptSkyDome)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v22; };
    struct { char igi2_o1[4]; float v23; };
    struct { char igi2_o2[8]; _DWORD *v24; };
    struct { char igi2_o3[12]; float v25; };
    struct { char igi2_o4[16]; struct real32x3_t *ptCol0; };
    struct { char igi2_o5[20]; float v27; };
    struct { char igi2_o6[24]; int v28; };
    struct { char igi2_o7[28]; float v29; };
    struct { char igi2_o8[32]; struct real32x3_t *ptCol1; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct SkyDome_s *v1; // esi
  struct IDirect3DVertexBuffer8 *ptVertexBuffer; // eax
  _DWORD *v3; // edi
  _DWORD *v4; // edi
  long double v5; // st7
  double v6; // st6
  struct real32x3_t *v7; // ebx
  double v8; // st6
  double v9; // st6
  int v10; // ebp
  double v11; // st7
  int v12; // ecx
  _DWORD *v13; // edi
  int v14; // edx
  int v15; // edx
  int v16; // edx
  int v17; // edx
  int v18; // edx
  int v19; // edx
  int v20; // edx
  int v21; // edx

  v1 = ptSkyDome;
  ptVertexBuffer = ptSkyDome->ptVertexBuffer;
  igi2_frame.v24 = nullptr;
  ptVertexBuffer->lpVtbl->Lock(ptVertexBuffer, 0, 5136u, (unsigned __int8 **)&igi2_frame.v24, 0x2000u);
  v3 = igi2_frame.v24;
  *igi2_frame.v24 = 0;
  v3[1] = 0;
  v3[2] = 1174011904;
  v3[3] = SkyDome_InterpolateVertexColour(
            ptSkyDome->atColours,
            ptSkyDome->atColours,
            ptSkyDome->atColours,
            ptSkyDome->atColours,
            0.0,
            0.0);
  v4 = v3 + 4;
  igi2_frame.v22 = 1.5707963705062866;
  igi2_frame.v28 = 15;
  while ( 1 )
  {
    v5 = 0.0;
    igi2_frame.v23 = 0.0;
    igi2_frame.v27 = 0.0;
    v6 = igi2_frame.v22 - 0.10471975803375244;
    igi2_frame.v22 = v6;
    if ( v6 < v1->vHalfAngle )
    {
      v7 = &v1->atColours[2];
      v9 = v1->vHalfAngle * 0.5;
      v8 = igi2_frame.v22 < v9 ? 0.0 : igi2_frame.v22 / v9 - 1.0;
    }
    else
    {
      v7 = (struct real32x3_t *)v1;
      v8 = (igi2_frame.v22 - v1->vHalfAngle) / (1.5707963705062866 - v1->vHalfAngle);
    }
    v10 = 20;
    igi2_frame.v25 = cos(igi2_frame.v22);
    igi2_frame.v29 = sin(igi2_frame.v22) * 8000.0;
    *(float *)&igi2_frame.ptCol1 = 1.0 - v8;
    do
    {
      *((float *)v4 + 2) = igi2_frame.v29;
      *(float *)v4 = cos(v5) * igi2_frame.v25 * 8000.0;
      *((float *)v4 + 1) = sin(v5) * igi2_frame.v25 * 8000.0;
      if ( igi2_frame.v23 >= 1.0 )
        v11 = igi2_frame.v23 - 1.0;
      else
        v11 = 1.0 - igi2_frame.v23;
      *(float *)&igi2_frame.ptCol0 = v11;
      v4[3] = SkyDome_InterpolateVertexColour(v7, v7 + 1, v7 + 2, v7 + 3, *(float *)&igi2_frame.ptCol0, *(float *)&igi2_frame.ptCol1);
      v4 += 4;
      --v10;
      igi2_frame.v23 = igi2_frame.v23 + 0.10000000149011612;
      v5 = igi2_frame.v27 + 0.3141592741012573;
      igi2_frame.v27 = v5;
    }
    while ( v10 );
    if ( !--igi2_frame.v28 )
      break;
    v1 = ptSkyDome;
  }
  v12 = 2;
  do
  {
    *v4 = *(v4 - 80);
    v4[1] = *(v4 - 79);
    v4[3] = *(v4 - 77);
    v4[4] = *(v4 - 76);
    v4[5] = *(v4 - 75);
    v4[7] = *(v4 - 73);
    v4[2] = -981860352;
    v13 = v4 + 4;
    v13[4] = *(v13 - 76);
    v13[5] = *(v13 - 75);
    v13[7] = *(v13 - 73);
    v13[2] = -981860352;
    v13 += 4;
    v13[4] = *(v13 - 76);
    v13[5] = *(v13 - 75);
    v13[7] = *(v13 - 73);
    v13[2] = -981860352;
    v13 += 4;
    v13[4] = *(v13 - 76);
    v13[5] = *(v13 - 75);
    v13[7] = *(v13 - 73);
    v13[2] = -981860352;
    v13 += 4;
    v13[4] = *(v13 - 76);
    v13[5] = *(v13 - 75);
    v14 = *(v13 - 73);
    v13 += 4;
    *(v13 - 2) = -981860352;
    v13[3] = v14;
    v13[4] = *(v13 - 76);
    v15 = *(v13 - 75);
    v13 += 4;
    *(v13 - 2) = -981860352;
    v13[1] = v15;
    v13[3] = *(v13 - 77);
    v16 = *(v13 - 76);
    v13 += 4;
    *v13 = v16;
    v17 = *(v13 - 79);
    *(v13 - 2) = -981860352;
    v13[1] = v17;
    v13[3] = *(v13 - 77);
    v18 = *(v13 - 76);
    v13 += 4;
    *(v13 - 2) = -981860352;
    *v13 = v18;
    v13[1] = *(v13 - 79);
    v19 = *(v13 - 77);
    v13 += 4;
    *(v13 - 1) = v19;
    v20 = *(v13 - 80);
    *(v13 - 2) = -981860352;
    *v13 = v20;
    v13[1] = *(v13 - 79);
    v21 = *(v13 - 77);
    v13[2] = -981860352;
    v13[3] = v21;
    v4 = v13 + 4;
    --v12;
  }
  while ( v12 );
  ptSkyDome->ptVertexBuffer->lpVtbl->Unlock(ptSkyDome->ptVertexBuffer);
}

// source: e/3/pc/pc_skydome.c:265  [anchor-callee]
void __cdecl SkyDome_InitialiseIndexBuffer(struct SkyDome_s *ptSkyDome)
{
  struct SkyDome_s *v1; // ebp
  struct IDirect3DIndexBuffer8 *ptIndexBuffer; // eax
  struct SkyDome_s *v3; // eax
  int v4; // ecx
  __int16 v5; // si
  _WORD *v6; // eax
  int v7; // ebx
  int v8; // esi
  __int16 v9; // dx
  int v10; // ecx
  _WORD *v11; // eax
  __int16 v12; // di

  v1 = ptSkyDome;
  ptIndexBuffer = ptSkyDome->ptIndexBuffer;
  ptSkyDome = nullptr;
  ptIndexBuffer->lpVtbl->Lock(ptIndexBuffer, 0, 3720u, (unsigned __int8 **)&ptSkyDome, 0x2000u);
  v3 = ptSkyDome;
  v4 = 0;
  v5 = 19;
  do
  {
    LOWORD(v3->atColours[0].vX) = 0;
    v6 = (_WORD *)&v3->atColours[0].vX + 1;
    *v6++ = v5 + 1;
    v5 = v4;
    *v6 = ++v4;
    v3 = (struct SkyDome_s *)(v6 + 1);
  }
  while ( (unsigned __int16)v4 < 0x14u );
  v7 = 21;
  do
  {
    v8 = 0;
    v9 = 19;
    v10 = v7;
    do
    {
      v11 = (_WORD *)&v3->atColours[0].vX + 1;
      *(v11++ - 1) = v10 - 20;
      v12 = v7 + v9 - 20;
      *(v11 - 1) = v12;
      *v11++ = v10;
      *v11++ = v12;
      *v11++ = v7 + v9;
      *v11 = v10;
      v3 = (struct SkyDome_s *)(v11 + 1);
      v9 = v8++;
      ++v10;
    }
    while ( (unsigned __int16)v8 < 0x14u );
    v7 += 20;
  }
  while ( (unsigned __int16)v7 < 0x141u );
  v1->ptIndexBuffer->lpVtbl->Unlock(v1->ptIndexBuffer);
}

// source: e/3/pc/pc_skydome.c:326  [anchor-hash]
void __cdecl SkyDome_DestroyCallback()
{
  struct SkyDome_s *v0; // esi

  if ( SkyDome_ptActiveTask )
  {
    v0 = SkyDome_ptActiveTask;
    SkyDome_ptActiveTask->ptVertexBuffer->lpVtbl->Release(SkyDome_ptActiveTask->ptVertexBuffer);
    v0->ptIndexBuffer->lpVtbl->Release(v0->ptIndexBuffer);
  }
}

// source: e/3/pc/pc_skydome.c:353  [anchor-hash]
void __cdecl SkyDome_RestoreCallback()
{
  struct SkyDome_s *v0; // esi

  v0 = SkyDome_ptActiveTask;
  if ( SkyDome_ptActiveTask )
  {
    Direct3D_ptDevice->lpVtbl->CreateVertexBuffer(
      Direct3D_ptDevice,
      5136u,
      520u,
      66u,
      D3DPOOL_DEFAULT,
      &SkyDome_ptActiveTask->ptVertexBuffer);
    Direct3D_ptDevice->lpVtbl->CreateIndexBuffer(
      Direct3D_ptDevice,
      3720u,
      520u,
      D3DFMT_INDEX16,
      D3DPOOL_DEFAULT,
      &v0->ptIndexBuffer);
    SkyDome_InitialiseIndexBuffer(v0);
    SkyDome_InitialiseVertexBuffer(v0);
  }
}

// source: e/3/pc/pc_skydome.c:404  [anchor-caller]
void *__cdecl SkyDome_New()
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real32x3_t ptBottomNorthColour; };
    struct { char igi2_o1[12]; struct real32x3_t ptHalfNorthColour; };
    struct { char igi2_o2[24]; struct real32x3_t ptTopColour; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct SkyDome_s *v0; // esi

  v0 = (struct SkyDome_s *)Mem_AllocFn(88, 4);
  if ( AppContext_tAppContext.isMainMenu == false )
  {
    Direct3D_ptDevice->lpVtbl->CreateVertexBuffer(
      Direct3D_ptDevice,
      5136u,
      520u,
      66u,
      D3DPOOL_DEFAULT,
      &v0->ptVertexBuffer);
    Direct3D_ptDevice->lpVtbl->CreateIndexBuffer(
      Direct3D_ptDevice,
      3720u,
      520u,
      D3DFMT_INDEX16,
      D3DPOOL_DEFAULT,
      &v0->ptIndexBuffer);
    SkyDome_InitialiseIndexBuffer(v0);
  }
  igi2_frame.ptHalfNorthColour.vX = 1.0;
  igi2_frame.ptHalfNorthColour.vY = 0.0;
  igi2_frame.ptHalfNorthColour.vZ = 0.0;
  igi2_frame.ptBottomNorthColour.vX = 1.0;
  igi2_frame.ptBottomNorthColour.vY = 1.0;
  igi2_frame.ptBottomNorthColour.vZ = 1.0;
  igi2_frame.ptTopColour.vX = 0.0;
  igi2_frame.ptTopColour.vY = 0.0;
  igi2_frame.ptTopColour.vZ = 1.0;
  SkyDome_SetColour(
    v0,
    &igi2_frame.ptTopColour,
    &igi2_frame.ptBottomNorthColour,
    &igi2_frame.ptBottomNorthColour,
    &igi2_frame.ptHalfNorthColour,
    &igi2_frame.ptHalfNorthColour);
  v0->vHalfAngle = 0.39269909262657166;
  SkyDome_ptActiveTask = v0;
  return v0;
}

// source: e/3/pc/pc_skydome.c:472  [anchor-hash]
void __cdecl SkyDome_Delete(void *pxSkyDome)
{
  int v2; // esi

  SkyDome_ptActiveTask = nullptr;
  if ( AppContext_tAppContext.isMainMenu == false )
  {
    (*(void (__stdcall **)(_DWORD))(**((_DWORD **)pxSkyDome + 20) + 8))(*((_DWORD *)pxSkyDome + 20));
    (*(void (__stdcall **)(_DWORD))(**((_DWORD **)pxSkyDome + 21) + 8))(*((_DWORD *)pxSkyDome + 21));
  }
  if ( pxSkyDome )
  {
    v2 = *(_DWORD *)(((int)pxSkyDome - 4) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v2);
    memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
    free((void *)v2);
  }
}

// source: e/3/pc/pc_skydome.c:508  [size]
struct Dirlight_s *__cdecl SkyDome_SetDirlight(struct Dirlight_s *ptDirlight)
{
  SkyDome_ptDirlight = ptDirlight;
  return ptDirlight;
}

// source: e/3/pc/pc_skydome.c:523  [size]
struct Dirlight_s *__cdecl SkyDome_GetDirlight()
{
  return SkyDome_ptDirlight;
}

// source: e/3/pc/pc_skydome.c:537  [anchor-mhash]
void __cdecl SkyDome_Draw(int ltcg_esi)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vAngle; };
    struct { char igi2_o1[4]; struct _D3DMATRIX tMatrix; };
    char igi2_extent[68];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct RenderStateBlock_t *v1; // edx
  struct RenderStateBlock_t *v2; // ecx
  struct RenderStateBlock_t *v3; // edx
  long double v4; // st6

  igi2_frame.vAngle = 0.0;
  if ( SkyDome_ptDirlight )
    igi2_frame.vAngle = atan2(SkyDome_ptDirlight->tDir.vX, SkyDome_ptDirlight->tDir.vY) + 1.5707963705062866;
  v1 = Direct3D_ptBlendStateBlock;
  Direct3D_ptTextureStateBlock->eCurrentState = -1;
  v2 = Direct3D_ptGenericStateBlock;
  v1->eCurrentState = -1;
  v3 = Direct3D_ptClippingStateBlock;
  v2->eCurrentState = -1;
  v3->eCurrentState = -1;
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHABLENDENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZWRITEENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_CULLMODE, 3u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SPECULARENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_LIGHTING, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_DITHERENABLE, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHATESTENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_CLIPPING, 1u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLOROP, 3u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLORARG1, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLORARG2, 0);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAOP, 1u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_COLOROP, 1u);
  *(_QWORD *)&igi2_frame.tMatrix.m[2][2] = LODWORD(Direct3D_vScale);
  *(_QWORD *)&igi2_frame.tMatrix.m[0][2] = 0;
  memset(&igi2_frame.tMatrix.m[1][2], 0, 16);
  *(_QWORD *)&igi2_frame.tMatrix.m[3][0] = 0;
  *(_QWORD *)&igi2_frame.tMatrix.m[3][2] = 0x3F80000000000000LL;
  igi2_frame.tMatrix._11 = cos(igi2_frame.vAngle) * Direct3D_vScale;
  v4 = sin(igi2_frame.vAngle) * Direct3D_vScale;
  igi2_frame.tMatrix._12 = -v4;
  igi2_frame.tMatrix._21 = v4;
  igi2_frame.tMatrix._22 = igi2_frame.tMatrix._11;
  Direct3D_ptDevice->lpVtbl->SetTransform(Direct3D_ptDevice, (enum _D3DTRANSFORMSTATETYPE)256, &igi2_frame.tMatrix);
  Direct3D_tState.aptStreamData[0] = *(struct IDirect3DVertexBuffer8 **)(ltcg_esi + 80);
  Direct3D_tState.anStride[0] = 16;
  Direct3D_ptDevice->lpVtbl->SetStreamSource(Direct3D_ptDevice, 0, Direct3D_tState.aptStreamData[0], 16u);
  Direct3D_tState.ptIndexData = *(struct IDirect3DIndexBuffer8 **)(ltcg_esi + 84);
  Direct3D_tState.nBaseVertexIndex = 0;
  Direct3D_ptDevice->lpVtbl->SetIndices(Direct3D_ptDevice, Direct3D_tState.ptIndexData, 0);
  Direct3D_tState.nHandle = 66;
  Direct3D_ptDevice->lpVtbl->SetVertexShader(Direct3D_ptDevice, 66u);
  Direct3D_ptDevice->lpVtbl->DrawIndexedPrimitive(Direct3D_ptDevice, D3DPT_TRIANGLELIST, 0, 321u, 0, 620u);
}

// source: e/3/pc/pc_skydome.c:662  [anchor-caller]
void *__cdecl SkyDome_SetColour(
        void *pxSkyDome,
        struct real32x3_t *ptTopColour,
        struct real32x3_t *ptHalfNorthColour,
        struct real32x3_t *ptHalfSouthColour,
        struct real32x3_t *ptBottomNorthColour,
        struct real32x3_t *ptBottomSouthColour)
{
  *(struct real32x3_t *)pxSkyDome = *ptTopColour;
  *((struct real32x3_t *)pxSkyDome + 1) = *ptTopColour;
  *((struct real32x3_t *)pxSkyDome + 2) = *ptHalfNorthColour;
  *((struct real32x3_t *)pxSkyDome + 3) = *ptHalfSouthColour;
  *((struct real32x3_t *)pxSkyDome + 4) = *ptBottomNorthColour;
  *((struct real32x3_t *)pxSkyDome + 5) = *ptBottomSouthColour;
  if ( AppContext_tAppContext.isMainMenu == false )
    SkyDome_InitialiseVertexBuffer((struct SkyDome_s *)pxSkyDome);
  return pxSkyDome;
}

// source: e/3/pc/pc_skydome.c:690  [size]
void __cdecl SkyDome_SetHalfAngle(void *pxSkyDome, float vAngle)
{
  *((float *)pxSkyDome + 18) = vAngle;
}

// source: e/3/pc/pc_skydome.c:706  [size]
void __cdecl SkyDome_NorthPoleAngle(void *pxSkyDome, float vAngle)
{
  *((float *)pxSkyDome + 19) = vAngle;
}

// source: e/3/pc/pc_skydome.c:723  [anchor-hash]
void __cdecl SkyDome_Open()
{
  Direct3D_RegisterCallback(SkyDome_RestoreCallback, &Direct3D_ptRestoreCallback);
  Direct3D_RegisterCallback(SkyDome_DestroyCallback, &Direct3D_ptDestroyCallback);
}

// source: e/3/pc/pc_skydome.c:739  [size]
void __cdecl SkyDome_Close()
{
  ;
}
