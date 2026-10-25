/* f/2/pc/pc_filter.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: f/2/pc/pc_filter.c:320  [anchor-mhash]
void __cdecl LineFilter_D3DDraw(void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct FilterVertex_t *ptVertex; };
    struct { char igi2_o1[4]; __int64 vX; };
    struct { char igi2_o2[12]; int nNumLines; };
    struct { char igi2_o3[16]; float vY; };
    struct { char igi2_o4[20]; int iStartVertex; };
    struct { char igi2_o5[24]; float vZ; };
    struct { char igi2_o6[28]; float i; };
    struct { char igi2_o7[32]; float vT; };
    struct { char igi2_o8[36]; int iLine; };
    struct { char igi2_o9[40]; struct FilterVertex_t tTemplate; };
    struct { char igi2_o10[68]; struct _D3DMATRIX tProjection; };
    char igi2_extent[132];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct RenderStateBlock_t *v1; // ecx
  double v2; // st7
  double v3; // st6
  double v4; // st6
  struct RenderStateBlock_t *v5; // edx
  struct RenderStateBlock_t *v6; // ecx
  struct IDirect3DDevice8Vtbl *lpVtbl; // edx
  int v8; // esi
  int v9; // eax
  double v10; // st7
  int v11; // edx
  int v12; // edx
  int v13; // edx
  int v14; // edx
  double v15; // st7
  int v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // eax
  double v20; // st7
  double v21; // st7
  int v22; // ebx
  double v23; // st7
  unsigned int v24; // ecx
  unsigned int v25; // ecx
  unsigned int v26; // ecx
  unsigned int v27; // esi
  int v28; // ebx
  double v29; // st6
  int nNumVertices; // eax

  if ( *((float *)pxContext + 13) <= (double)Direct3D_vWorldMinZ )
    igi2_frame.vZ = Direct3D_vWorldMinZ;
  else
    igi2_frame.vZ = *((float *)pxContext + 13);
  Direct3D_ptDevice->lpVtbl->GetTransform(Direct3D_ptDevice, D3DTS_PROJECTION, &igi2_frame.tProjection);
  v1 = Direct3D_ptBlendStateBlock;
  igi2_frame.tTemplate.vRhw = 1.0 / (Direct3D_vScale * igi2_frame.vZ);
  v2 = (1.0 - Direct3D_vD3DMinZ * igi2_frame.tTemplate.vRhw) * igi2_frame.tProjection._33;
  v3 = Direct3D_vMaxZ;
  Direct3D_ptTextureStateBlock->eCurrentState = -1;
  v4 = v3 - Direct3D_vMinZ;
  v5 = Direct3D_ptGenericStateBlock;
  v1->eCurrentState = -1;
  v6 = Direct3D_ptClippingStateBlock;
  v5->eCurrentState = -1;
  v6->eCurrentState = -1;
  lpVtbl = Direct3D_ptDevice->lpVtbl;
  igi2_frame.tTemplate.vZ = v2 * v4 + Direct3D_vMinZ;
  lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZBIAS, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SPECULARENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_CULLMODE, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_LIGHTING, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_DITHERENABLE, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHATESTENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZFUNC, 4u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZENABLE, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZWRITEENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAOP, 3u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAARG1, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAARG2, 0);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLOROP, 3u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLORARG1, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLORARG2, 0);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_COLOROP, 1u);
  if ( Direct3D_tState.aptTexture[0] )
  {
    Direct3D_tState.aptTexture[0] = nullptr;
    Direct3D_ptDevice->lpVtbl->SetTexture(Direct3D_ptDevice, 0, nullptr);
  }
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHABLENDENABLE, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SRCBLEND, 5u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_DESTBLEND, 6u);
  Direct3D_tState.aptStreamData[0] = Direct3D_atDynamicVertexBuffer[2].ptVertexBuffer;
  Direct3D_tState.anStride[0] = Direct3D_atDynamicVertexBuffer[2].nStride;
  Direct3D_ptDevice->lpVtbl->SetStreamSource(
    Direct3D_ptDevice,
    0,
    Direct3D_atDynamicVertexBuffer[2].ptVertexBuffer,
    Direct3D_atDynamicVertexBuffer[2].nStride);
  Direct3D_tState.nHandle = Direct3D_atDynamicVertexBuffer[2].nFVF;
  Direct3D_ptDevice->lpVtbl->SetVertexShader(Direct3D_ptDevice, Direct3D_atDynamicVertexBuffer[2].nFVF);
  igi2_frame.vT = *((float *)pxContext + 14);
  Direct3D_LockDynamicVertexBuffer(&Direct3D_atDynamicVertexBuffer[2], (void **)&igi2_frame.ptVertex, &igi2_frame.iStartVertex, 200);
  if ( igi2_frame.ptVertex )
  {
    igi2_frame.vY = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vY;
    v8 = 0;
    if ( RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHeight
       + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vY >= RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vY
                                                                              + 4.0 )
    {
      do
      {
        if ( v8 >= 200 )
        {
          Direct3D_atDynamicVertexBuffer[2].ptVertexBuffer->lpVtbl->Unlock(Direct3D_atDynamicVertexBuffer[2].ptVertexBuffer);
          Direct3D_ptDevice->lpVtbl->DrawPrimitive(Direct3D_ptDevice, D3DPT_LINELIST, igi2_frame.iStartVertex, v8 / 2);
          Direct3D_LockDynamicVertexBuffer(&Direct3D_atDynamicVertexBuffer[2], (void **)&igi2_frame.ptVertex, &igi2_frame.iStartVertex, 200);
          if ( !igi2_frame.ptVertex )
            return;
          v8 = 0;
          igi2_frame.vY = igi2_frame.vY - 4.0;
        }
        else
        {
          v9 = (__int64)igi2_frame.vY;
          v10 = (double)v9;
          igi2_frame.vX = (__int64)RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX;
          igi2_frame.nNumLines = igi2_frame.vX;
          igi2_frame.ptVertex->vX = (float)(int)igi2_frame.vX;
          igi2_frame.ptVertex->vY = v10;
          igi2_frame.ptVertex->vZ = igi2_frame.tTemplate.vZ;
          igi2_frame.ptVertex->vRhw = igi2_frame.tTemplate.vRhw;
          igi2_frame.vX = (__int64)(*((float *)pxContext + 10) * 255.0);
          v11 = ((unsigned __int8)igi2_frame.vX | 0x1900) << 8;
          igi2_frame.vX = (__int64)(*((float *)pxContext + 11) * 255.0);
          v12 = ((unsigned __int8)igi2_frame.vX | v11) << 8;
          igi2_frame.vX = (__int64)(*((float *)pxContext + 12) * 255.0);
          igi2_frame.ptVertex->nColor = (unsigned __int8)igi2_frame.vX | v12;
          ++igi2_frame.ptVertex;
          igi2_frame.vX = (__int64)(RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vWidth
                       + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX);
          igi2_frame.nNumLines = igi2_frame.vX;
          igi2_frame.ptVertex->vX = (float)(int)igi2_frame.vX;
          igi2_frame.ptVertex->vY = v10;
          igi2_frame.ptVertex->vZ = igi2_frame.tTemplate.vZ;
          igi2_frame.ptVertex->vRhw = igi2_frame.tTemplate.vRhw;
          igi2_frame.vX = (__int64)(*((float *)pxContext + 10) * 255.0);
          v13 = ((unsigned __int8)igi2_frame.vX | 0x7F00) << 8;
          igi2_frame.vX = (__int64)(*((float *)pxContext + 11) * 255.0);
          v14 = ((unsigned __int8)igi2_frame.vX | v13) << 8;
          igi2_frame.vX = (__int64)(*((float *)pxContext + 12) * 255.0);
          igi2_frame.ptVertex->nColor = (unsigned __int8)igi2_frame.vX | v14;
          v15 = (double)(v9 + 1);
          ++igi2_frame.ptVertex;
          igi2_frame.vX = (__int64)RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX;
          igi2_frame.nNumLines = igi2_frame.vX;
          igi2_frame.ptVertex->vX = (float)(int)igi2_frame.vX;
          igi2_frame.ptVertex->vY = v15;
          igi2_frame.ptVertex->vZ = igi2_frame.tTemplate.vZ;
          igi2_frame.ptVertex->vRhw = igi2_frame.tTemplate.vRhw;
          igi2_frame.vX = (__int64)(*((float *)pxContext + 10) * 255.0);
          v16 = ((unsigned __int8)igi2_frame.vX | 0x1900) << 8;
          igi2_frame.vX = (__int64)(*((float *)pxContext + 11) * 255.0);
          v17 = ((unsigned __int8)igi2_frame.vX | v16) << 8;
          igi2_frame.vX = (__int64)(*((float *)pxContext + 12) * 255.0);
          igi2_frame.ptVertex->nColor = (unsigned __int8)igi2_frame.vX | v17;
          ++igi2_frame.ptVertex;
          igi2_frame.vX = (__int64)(RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vWidth
                       + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX);
          igi2_frame.nNumLines = igi2_frame.vX;
          igi2_frame.ptVertex->vX = (float)(int)igi2_frame.vX;
          igi2_frame.ptVertex->vY = v15;
          igi2_frame.ptVertex->vZ = igi2_frame.tTemplate.vZ;
          igi2_frame.ptVertex->vRhw = igi2_frame.tTemplate.vRhw;
          igi2_frame.vX = (__int64)(*((float *)pxContext + 10) * 255.0);
          v18 = ((unsigned __int8)igi2_frame.vX | 0x7F00) << 8;
          igi2_frame.vX = (__int64)(*((float *)pxContext + 11) * 255.0);
          v19 = ((unsigned __int8)igi2_frame.vX | v18) << 8;
          igi2_frame.vX = (__int64)(*((float *)pxContext + 12) * 255.0);
          igi2_frame.ptVertex->nColor = (unsigned __int8)igi2_frame.vX | v19;
          v8 += 4;
          ++igi2_frame.ptVertex;
        }
        v20 = igi2_frame.vY + 4.0;
        igi2_frame.vY = v20;
      }
      while ( RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHeight
            + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vY >= v20 + 4.0 );
    }
    Direct3D_atDynamicVertexBuffer[2].ptVertexBuffer->lpVtbl->Unlock(Direct3D_atDynamicVertexBuffer[2].ptVertexBuffer);
    if ( v8 > 0 )
      Direct3D_ptDevice->lpVtbl->DrawPrimitive(Direct3D_ptDevice, D3DPT_LINELIST, igi2_frame.iStartVertex, v8 / 2);
    if ( igi2_frame.vT > 0.0 )
    {
      igi2_frame.vZ = 1.0;
      v21 = igi2_frame.vT * 10.0;
      if ( v21 < 1.0 )
      {
        igi2_frame.vZ = 1.0 / v21;
        v21 = 1.0;
      }
      igi2_frame.vX = (__int64)v21;
      igi2_frame.nNumLines = (__int64)v21;
      Direct3D_LockDynamicVertexBuffer(&Direct3D_atDynamicVertexBuffer[2], (void **)&igi2_frame.ptVertex, &igi2_frame.iStartVertex, 200);
      if ( igi2_frame.ptVertex )
      {
        igi2_frame.vY = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vY;
        v22 = 0;
        for ( igi2_frame.i = igi2_frame.vZ + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vY;
              RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHeight
            + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vY >= igi2_frame.i;
              igi2_frame.i = igi2_frame.vZ + igi2_frame.i )
        {
          for ( igi2_frame.iLine = 0; igi2_frame.iLine < igi2_frame.nNumLines; ++igi2_frame.iLine )
          {
            if ( v22 >= 200 )
            {
              Direct3D_atDynamicVertexBuffer[2].ptVertexBuffer->lpVtbl->Unlock(Direct3D_atDynamicVertexBuffer[2].ptVertexBuffer);
              Direct3D_ptDevice->lpVtbl->DrawPrimitive(Direct3D_ptDevice, D3DPT_LINELIST, igi2_frame.iStartVertex, v22 / 2);
              nNumVertices = Direct3D_atDynamicVertexBuffer[2].nNumVertices;
              if ( Direct3D_atDynamicVertexBuffer[2].nNumVertices + 200 > Direct3D_atDynamicVertexBuffer[2].nMaxVertices )
              {
                nNumVertices = 0;
                Direct3D_atDynamicVertexBuffer[2].nNumVertices = 0;
              }
              if ( Direct3D_atDynamicVertexBuffer[2].ptVertexBuffer->lpVtbl->Lock(
                     Direct3D_atDynamicVertexBuffer[2].ptVertexBuffer,
                     Direct3D_atDynamicVertexBuffer[2].nStride * nNumVertices,
                     200 * Direct3D_atDynamicVertexBuffer[2].nStride,
                     (unsigned __int8 **)&igi2_frame.ptVertex,
                     nNumVertices != 0 ? 4096 : 0x2000) )
              {
                return;
              }
              igi2_frame.iStartVertex = Direct3D_atDynamicVertexBuffer[2].nNumVertices;
              Direct3D_atDynamicVertexBuffer[2].nNumVertices += 200;
              if ( !igi2_frame.ptVertex )
                return;
              v22 = 0;
            }
            else
            {
              LODWORD(igi2_frame.vX) = (__int64)igi2_frame.vY;
              v23 = (double)(int)igi2_frame.vX;
              v24 = (Filter_tRandomState.anRandom[0] >> 7) ^ Filter_tRandomState.anRandom[2];
              Filter_tRandomState.anRandom[0] += v24 ^ Filter_tRandomState.anRandom[1];
              Filter_tRandomState.anRandom[2] = v24;
              Filter_tRandomState.anRandom[1] ^= v24;
              igi2_frame.ptVertex->vX = (double)LOWORD(Filter_tRandomState.anRandom[0])
                           * 0.0000152587890625
                           * RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vWidth
                           + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX;
              igi2_frame.ptVertex->vY = v23;
              igi2_frame.ptVertex->vZ = igi2_frame.tTemplate.vZ;
              igi2_frame.ptVertex->vRhw = igi2_frame.tTemplate.vRhw;
              v25 = (Filter_tRandomState.anRandom[0] >> 7) ^ Filter_tRandomState.anRandom[2];
              Filter_tRandomState.anRandom[0] += v25 ^ Filter_tRandomState.anRandom[1];
              Filter_tRandomState.anRandom[2] = v25;
              Filter_tRandomState.anRandom[1] ^= v25;
              igi2_frame.vX = (__int64)(igi2_frame.vT * 255.0);
              v26 = (unsigned __int8)(__int64)(255.0
                                             * ((double)LOWORD(Filter_tRandomState.anRandom[0])
                                              * 0.0000152587890625))
                  | (((unsigned __int8)(__int64)(255.0
                                               * ((double)LOWORD(Filter_tRandomState.anRandom[0])
                                                * 0.0000152587890625))
                    | (((unsigned __int8)(__int64)(255.0
                                                 * ((double)LOWORD(Filter_tRandomState.anRandom[0])
                                                  * 0.0000152587890625))
                      | ((_DWORD)igi2_frame.vX << 8)) << 8)) << 8);
              igi2_frame.ptVertex->nColor = v26;
              v27 = (Filter_tRandomState.anRandom[0] >> 7) ^ Filter_tRandomState.anRandom[2];
              Filter_tRandomState.anRandom[0] += v27 ^ Filter_tRandomState.anRandom[1];
              v28 = v22 + 1;
              LODWORD(igi2_frame.vX) = LOWORD(Filter_tRandomState.anRandom[0]);
              ++igi2_frame.ptVertex;
              Filter_tRandomState.anRandom[2] = v27;
              Filter_tRandomState.anRandom[1] ^= v27;
              igi2_frame.ptVertex->vX = (double)LOWORD(Filter_tRandomState.anRandom[0]) * 0.0000152587890625 * 50.0
                           + igi2_frame.ptVertex[-1].vX;
              v29 = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vWidth
                  + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX;
              if ( v29 > igi2_frame.ptVertex->vX )
                v29 = igi2_frame.ptVertex->vX;
              igi2_frame.ptVertex->vX = v29;
              igi2_frame.ptVertex->vY = v23;
              igi2_frame.ptVertex->vZ = igi2_frame.tTemplate.vZ;
              igi2_frame.ptVertex->vRhw = igi2_frame.tTemplate.vRhw;
              igi2_frame.ptVertex->nColor = v26;
              ++igi2_frame.ptVertex;
              v22 = v28 + 1;
            }
          }
          igi2_frame.vY = igi2_frame.i;
        }
        Direct3D_atDynamicVertexBuffer[2].ptVertexBuffer->lpVtbl->Unlock(Direct3D_atDynamicVertexBuffer[2].ptVertexBuffer);
        if ( v22 > 0 )
          Direct3D_ptDevice->lpVtbl->DrawPrimitive(Direct3D_ptDevice, D3DPT_LINELIST, igi2_frame.iStartVertex, v22 / 2);
      }
    }
  }
}

// source: f/2/pc/pc_filter.c:824  [size]
void __cdecl ComputerFilter_DrawPrim(void *pxPrimitive)
{
  void (__cdecl *v1)(void *); // eax

  v1 = RenderMode_tActiveRenderMode.apfRenderModeMethod[ComputerFilter_eRenderModeMethod];
  if ( v1 )
    v1(nullptr);
}

// source: f/2/pc/pc_filter.c:840  [size]
void __cdecl LineFilter_DrawPrim(void *pxPrimitive)
{
  void (__cdecl *v1)(void *); // eax

  v1 = RenderMode_tActiveRenderMode.apfRenderModeMethod[LineFilter_eRenderModeMethod];
  if ( v1 )
    v1(*((void **)pxPrimitive + 3));
}

// source: f/2/pc/pc_filter.c:856  [size]
void __cdecl LineFilter_RunHandler(struct QTask_s *ptQTask)
{
  ;
}

void __cdecl sub_54B570(struct QTask_s *a1)
{
  _DWORD *v1; // esi
  int v2; // eax

  v1 = Primitive_ptNextFreePrimitive;
  Primitive_ptNextFreePrimitive = (char *)Primitive_ptNextFreePrimitive + 16;
  if ( (char *)Primitive_ptNextFreePrimitive - Primitive_asPrimitive[0] > (char *)Primitive_nMaxPrimitiveUsage )
  {
    Primitive_nMaxPrimitiveUsage = (unsigned int)Primitive_ptNextFreePrimitive - Primitive_asPrimitive[0];
    if ( (char *)Primitive_ptNextFreePrimitive - Primitive_asPrimitive[0] > (char *)dword_6B9E3C )
      v1 = nullptr;
  }
  v2 = LineFilter_ePrimType;
  v1[1] = LineFilter_ePrimType;
  v1[3] = a1;
  RenderMode_tActiveRenderMode.apfRenderModeMethod[v2](v1);
  dword_834E068 = (int)v1;
}

// source: f/2/pc/pc_filter.c:892  [anchor-mhash]
void __cdecl WideScreenFilter_DrawPrim(void *pxPrimitive)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vY; };
    struct { char igi2_o1[40]; struct ClippingRect_s tClippingRect; };
    char igi2_extent[64];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  float *v1; // esi
  float v2; // ecx
  float v3; // edx
  float v4; // eax

  if ( pxPrimitive )
  {
    v1 = *((float **)pxPrimitive + 3);
    v2 = v1[17];
    v3 = v1[14];
    igi2_frame.tClippingRect.vX = v1[16];
    v4 = v1[15];
    igi2_frame.tClippingRect.vY = v2;
    igi2_frame.tClippingRect.vHeight = v4;
    igi2_frame.tClippingRect.vWidth = v3;
    RenderContext_SetClippingRect(&RenderContext_tActiveRenderContext, &igi2_frame.tClippingRect);
    igi2_frame.vY = v1[17] + v1[15] - v1[18];
    QSprite_RegisterBlankZ(v1[16], igi2_frame.vY, v1[14], v1[18], v1[10], v1[11], v1[12], 0, -1, 1.0);
    QSprite_RegisterBlankZ(v1[16], v1[17], v1[14], v1[18], v1[10], v1[11], v1[12], 0, -1, 1.0);
  }
}

// source: f/2/pc/pc_filter.c:952  [size]
void __cdecl WideScreenFilter_RunHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: f/2/pc/pc_filter.c:966  [anchor-mhash]
void __cdecl WideScreenFilter_DrawHandler(struct QTask_s *ptQTask)
{
  struct RenderPrimitive_s *v1; // ecx
  struct RenderPrimitive_s *ptRenderPrimitive; // edx
  struct QReference_s *ptMiddle; // ecx
  struct QReference_s *ptHead; // edx
  struct QTask_s *ptTail; // ecx
  struct DisplaySetClippingWindowContext_s ptClippingWindowContext; // [esp+4h] [ebp-24h] BYREF

  v1 = (struct RenderPrimitive_s *)Primitive_ptNextFreePrimitive;
  Primitive_ptNextFreePrimitive = (char *)Primitive_ptNextFreePrimitive + 16;
  if ( (char *)Primitive_ptNextFreePrimitive - Primitive_asPrimitive[0] > (char *)Primitive_nMaxPrimitiveUsage )
  {
    Primitive_nMaxPrimitiveUsage = (unsigned int)Primitive_ptNextFreePrimitive - Primitive_asPrimitive[0];
    if ( (char *)Primitive_ptNextFreePrimitive - Primitive_asPrimitive[0] > (char *)dword_6B9E3C )
      v1 = nullptr;
  }
  v1->ePrimType = WideScreenFilter_ePrimType;
  v1[1].ptNext = (struct RenderPrimitive_s *)ptQTask;
  ptRenderPrimitive = RenderContext_tActiveRenderContext.ptRenderPrimitive_;
  v1->ptNext = RenderContext_tActiveRenderContext.ptRenderPrimitive_->ptNext;
  ptRenderPrimitive->ptNext = v1;
  ptMiddle = ptQTask[1].tQTaskRefList.ptMiddle;
  LODWORD(ptClippingWindowContext.tClippingRect.vY) = ptQTask[1].tQTaskRefList.ptTail;
  ptHead = ptQTask[1].tQTaskRefList.ptHead;
  LODWORD(ptClippingWindowContext.tClippingRect.vX) = ptMiddle;
  ptTail = ptQTask[1].tQTaskChildren.ptTail;
  LODWORD(ptClippingWindowContext.tClippingRect.vHeight) = ptHead;
  LODWORD(ptClippingWindowContext.tClippingRect.vWidth) = ptTail;
  RenderContext_RegisterClippingWindow(&ptClippingWindowContext, 0);
}

// source: f/2/pc/pc_filter.c:1005  [anchor-callee]
struct QTask_s *__cdecl LineFilter_New(
        struct QTask_s *ptParent,
        float vR,
        float vG,
        float vB,
        float vZ,
        int isSort)
{
  struct QTask_s *result; // eax

  result = QTask_NewFn(ptParent, LineFilter_eQTaskType, nullptr);
  *(float *)&result[1].ptNext = vR;
  *(float *)&result[1].ptPrev = vG;
  *(float *)&result[1].tQTaskChildren.ptHead = vB;
  *(float *)&result[1].tQTaskChildren.ptMiddle = vZ;
  result[1].tQTaskChildren.ptTail = nullptr;
  result[1].tQTaskRefList.ptHead = (struct QReference_s *)isSort;
  return result;
}

// source: f/2/pc/pc_filter.c:1037  [size]
void __cdecl LineFilter_DeleteHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: f/2/pc/pc_filter.c:1063  [anchor-callee]
struct QTask_s *__cdecl WideScreenFilter_New(
        struct QTask_s *ptParent,
        float vR,
        float vG,
        float vB,
        float vZ,
        float vWidth,
        float vHeight,
        float vX,
        float vY,
        float vBorderSize)
{
  struct QTask_s *result; // eax

  result = QTask_NewFn(ptParent, WideScreenFilter_eQTaskType, nullptr);
  *(float *)&result[1].ptNext = vR;
  *(float *)&result[1].ptPrev = vG;
  *(float *)&result[1].tQTaskChildren.ptHead = vB;
  *(float *)&result[1].tQTaskChildren.ptMiddle = vZ;
  *(float *)&result[1].tQTaskChildren.ptTail = vWidth;
  *(float *)&result[1].tQTaskRefList.ptHead = vHeight;
  *(float *)&result[1].tQTaskRefList.ptMiddle = vX;
  *(float *)&result[1].tQTaskRefList.ptTail = vY;
  *(float *)&result[1].ptParent = vBorderSize;
  return result;
}

// source: f/2/pc/pc_filter.c:1106  [anchor-callee]
struct QTask_s *__cdecl BandFilter_New(
        struct QTask_s *ptParent,
        float vZ,
        float vR,
        float vG,
        float vB,
        int nMoveLoopTime,
        int nNoiseLoopTime,
        float vMaxNoise)
{
  struct QTask_s *v8; // ebp
  double v9; // st7
  char *v10; // edi
  int v11; // eax

  v8 = QTask_NewFn(ptParent, BandFilter_eQTaskType, nullptr);
  *(float *)&v8[1].ptNext = vZ;
  v8[1].ptPrev = nullptr;
  *(float *)&v8[1].tQTaskChildren.ptHead = vMaxNoise;
  Texture_Alloc((struct TexInfo_s *)&v8[1].tQTaskChildren.ptMiddle, nullptr, 64, 16, 16, 3, 0, 1u);
  v8[2].tQTaskRefList.ptMiddle = (struct QReference_s *)nNoiseLoopTime;
  v8[2].tQTaskRefList.ptTail = (struct QReference_s *)nNoiseLoopTime;
  v8[2].tQTaskChildren.ptTail = nullptr;
  v8[2].tQTaskRefList.ptHead = (struct QReference_s *)nMoveLoopTime;
  if ( vR >= 0.0 )
  {
    if ( vR > 1.0 )
      vR = 1.0;
  }
  else
  {
    vR = 0.0;
  }
  if ( vG >= 0.0 )
  {
    if ( vG > 1.0 )
      vG = 1.0;
  }
  else
  {
    vG = 0.0;
  }
  v9 = vB;
  if ( vB >= 0.0 )
  {
    if ( v9 > 1.0 )
      v9 = 1.0;
  }
  else
  {
    v9 = 0.0;
  }
  *(float *)&v8[3].ptPrev = v9;
  v10 = BandFilter_zCameraFont;
  *(float *)&v8[2].eQTaskType = vR;
  v11 = BandFilter_nCameraNumber;
  *(float *)&v8[3].ptNext = vG;
  v8[2].ptParent = (struct QTask_s *)v11;
  v8[3].tQTaskChildren.ptHead = nullptr;
  v8[3].tQTaskChildren.ptHead = (struct QTask_s *)FontManager_LoadFont(v10);
  return v8;
}

// source: f/2/pc/pc_filter.c:1176  [anchor-mhash]
void __cdecl BandFilter_DeleteHandler(struct QTask_s *ptQTask)
{
  _DWORD *p_ptMiddle; // edi

  FontManager_DeleteFont((struct QSprite_s *)ptQTask[3].tQTaskChildren.ptHead);
  p_ptMiddle = &ptQTask[1].tQTaskChildren.ptMiddle;
  if ( AppContext_tAppContext.isMainMenu == false )
    RenderMode_atRenderMode[*p_ptMiddle].apfRenderModeMethod[Texture_eDeAllocTextureMethod](&ptQTask[1].tQTaskChildren.ptMiddle);
  memset(p_ptMiddle, 0, 0x2Cu);
}

// source: f/2/pc/pc_filter.c:1197  [anchor-hash]
struct QTask_s *__cdecl BandFilter_MakeBandTexture(struct QTask_s *ptQTask)
{
  int v1; // ebp
  int v2; // esi
  int *v3; // edx
  struct QTask_s *v4; // ebx
  void *v5; // edi
  struct QTask_s *result; // eax

  v1 = 4;
  v2 = (__int64)(*(float *)&ptQTask[3].ptPrev * 128.0)
     - (((unsigned int)(__int64)(*(float *)&ptQTask[3].ptNext * -128.0)
       + ((unsigned int)(__int64)(*(float *)&ptQTask[2].eQTaskType * -128.0) << 8)) << 8);
  v3 = BandFilter_anBandTexture;
  v4 = (struct QTask_s *)((__int64)(*(float *)&ptQTask[3].ptPrev * 255.0)
                        - (((unsigned int)(__int64)(*(float *)&ptQTask[3].ptNext * -255.0)
                          + ((unsigned int)(__int64)(*(float *)&ptQTask[2].eQTaskType * -255.0) << 8)) << 8));
  do
  {
    memset32(v3, v2, 0x20u);
    v5 = v3 + 32;
    result = v4;
    v3 += 64;
    --v1;
    memset32(v5, (int)v4, 0x20u);
  }
  while ( v1 );
  return result;
}

// source: f/2/pc/pc_filter.c:1271  [anchor-hash]
struct QTask_s *__cdecl BandFilter_MakeEmptyTexture(struct QTask_s *ptQTask)
{
  struct QTask_s *result; // eax

  result = (struct QTask_s *)((__int64)(*(float *)&ptQTask[3].ptPrev * 255.0)
                            - (((unsigned int)(__int64)(*(float *)&ptQTask[3].ptNext * -255.0)
                              + ((unsigned int)(__int64)(*(float *)&ptQTask[2].eQTaskType * -255.0) << 8)) << 8));
  memset32(BandFilter_anBandTexture, (int)result, 0x100u);
  return result;
}

// source: f/2/pc/pc_filter.c:1318  [anchor-mhash]
struct QTask_s *__cdecl BandFilter_AddNoiseToBandTexture(struct QTask_s *ptQTask)
{
  double v1; // st7
  struct QTask_s *result; // eax
  int v3; // ecx
  int v4; // edx
  int v5; // edi
  unsigned int v6; // ecx
  int v7; // edx
  unsigned int v8; // eax
  int *v9; // esi
  int v10; // edi
  unsigned __int8 v11; // bl
  int v12; // ecx
  int v13; // edx
  unsigned int v14; // eax
  int v15; // ecx
  int v16; // edx
  char *v17; // eax
  int *v18; // esi
  int v19; // edi
  int v20; // edi
  int v21; // ecx
  int v22; // edx
  unsigned int v23; // eax
  int v24; // ecx
  int v25; // edx
  unsigned int v26; // eax
  int *v27; // esi
  int v28; // edi
  int v29; // edi
  int v30; // ecx
  int v31; // edx
  unsigned int v32; // eax
  int v33; // ecx
  int v34; // edx
  unsigned int v35; // eax
  int *v36; // esi
  int v37; // edi
  int v38; // edi
  bool v39; // cc
  unsigned int v40; // ecx
  int v41; // edx
  unsigned int v42; // eax
  int *v43; // esi
  int v44; // edi
  int v45; // edi
  int nG; // [esp+10h] [ebp-1Ch]
  int nGa; // [esp+10h] [ebp-1Ch]
  int nGb; // [esp+10h] [ebp-1Ch]
  int nGc; // [esp+10h] [ebp-1Ch]
  int nB; // [esp+14h] [ebp-18h]
  int nBa; // [esp+14h] [ebp-18h]
  int nBb; // [esp+14h] [ebp-18h]
  int nBc; // [esp+14h] [ebp-18h]
  int nBd; // [esp+14h] [ebp-18h]
  int nI; // [esp+18h] [ebp-14h]
  int v56; // [esp+1Ch] [ebp-10h]
  int v57; // [esp+1Ch] [ebp-10h]

  v1 = *(float *)&ptQTask[1].ptPrev;
  result = (struct QTask_s *)Filter_tRandomState.anRandom[0];
  v3 = Filter_tRandomState.anRandom[2];
  v4 = Filter_tRandomState.anRandom[1];
  v5 = (__int64)(v1 * 256.0);
  nI = 0;
  if ( v5 >= 4 )
  {
    v56 = 3;
    do
    {
      v6 = ((unsigned int)result >> 7) ^ v3;
      v7 = v6 ^ v4;
      v8 = (unsigned int)result + v7;
      v9 = &BandFilter_anBandTexture[-(__int64)((double)(unsigned __int16)v8 * 0.0000152587890625 * -256.0)];
      nB = (unsigned __int8)*v9;
      v10 = *v9 >> 8;
      v11 = BYTE1(*v9);
      *v9 = v10;
      v10 >>= 8;
      *v9 = v10;
      *v9 = v10 >> 8;
      v12 = (v8 >> 7) ^ v6;
      v13 = v12 ^ v7;
      v14 = v13 + v8;
      *v9 = ((unsigned int)(__int64)((double)nB * ((double)(unsigned __int16)v14 * 0.0000152587890625))
           + (((unsigned int)(__int64)((double)v11 * ((double)(unsigned __int16)v14 * 0.0000152587890625))
             + ((unsigned int)(__int64)((double)(unsigned __int8)v10
                                      * ((double)(unsigned __int16)v14
                                       * 0.0000152587890625)) << 8)) << 8)) << 8;
      v15 = (v14 >> 7) ^ v12;
      v16 = v15 ^ v13;
      v17 = (char *)(v16 + v14);
      v18 = &BandFilter_anBandTexture[-(__int64)((double)(unsigned __int16)v17 * 0.0000152587890625 * -256.0)];
      nBa = (unsigned __int8)*v18;
      v19 = *v18 >> 8;
      *v18 = v19;
      nG = (unsigned __int8)v19;
      v20 = *v18 >> 8;
      *v18 = v20;
      *v18 >>= 8;
      v21 = ((unsigned int)v17 >> 7) ^ v15;
      v22 = v21 ^ v16;
      v23 = (unsigned int)&v17[v22];
      *v18 = ((unsigned int)(__int64)((double)nBa * ((double)(unsigned __int16)v23 * 0.0000152587890625))
            + (((unsigned int)(__int64)((double)nG * ((double)(unsigned __int16)v23 * 0.0000152587890625))
              + ((unsigned int)(__int64)((double)(unsigned __int8)v20
                                       * ((double)(unsigned __int16)v23
                                        * 0.0000152587890625)) << 8)) << 8)) << 8;
      v24 = (v23 >> 7) ^ v21;
      v25 = v24 ^ v22;
      v26 = v25 + v23;
      v27 = &BandFilter_anBandTexture[-(__int64)((double)(unsigned __int16)v26 * 0.0000152587890625 * -256.0)];
      nBb = (unsigned __int8)*v27;
      v28 = *v27 >> 8;
      *v27 = v28;
      nGa = (unsigned __int8)v28;
      v29 = *v27 >> 8;
      *v27 = v29;
      *v27 >>= 8;
      v30 = (v26 >> 7) ^ v24;
      v31 = v30 ^ v25;
      v32 = v31 + v26;
      *v27 = ((unsigned int)(__int64)((double)nBb * ((double)(unsigned __int16)v32 * 0.0000152587890625))
            + (((unsigned int)(__int64)((double)nGa * ((double)(unsigned __int16)v32 * 0.0000152587890625))
              + ((unsigned int)(__int64)((double)(unsigned __int8)v29
                                       * ((double)(unsigned __int16)v32
                                        * 0.0000152587890625)) << 8)) << 8)) << 8;
      v33 = (v32 >> 7) ^ v30;
      v34 = v33 ^ v31;
      v35 = v34 + v32;
      v36 = &BandFilter_anBandTexture[-(__int64)((double)(unsigned __int16)v35 * 0.0000152587890625 * -256.0)];
      nBc = (unsigned __int8)*v36;
      v37 = *v36 >> 8;
      *v36 = v37;
      nGb = (unsigned __int8)v37;
      v38 = *v36 >> 8;
      *v36 = v38;
      *v36 >>= 8;
      v3 = (v35 >> 7) ^ v33;
      v4 = v3 ^ v34;
      result = (struct QTask_s *)(v4 + v35);
      *v36 = ((unsigned int)(__int64)((double)nBc * ((double)(unsigned __int16)result * 0.0000152587890625))
            + (((unsigned int)(__int64)((double)nGb * ((double)(unsigned __int16)result * 0.0000152587890625))
              + ((unsigned int)(__int64)((double)(unsigned __int8)v38
                                       * ((double)(unsigned __int16)result
                                        * 0.0000152587890625)) << 8)) << 8)) << 8;
      v5 = (__int64)(v1 * 256.0);
      v39 = v56 + 4 < v5;
      nI += 4;
      v56 += 4;
    }
    while ( v39 );
    Filter_tRandomState.anRandom[0] = (unsigned int)result;
    Filter_tRandomState.anRandom[1] = v4;
    Filter_tRandomState.anRandom[2] = v3;
  }
  if ( nI < v5 )
  {
    v57 = v5 - nI;
    do
    {
      v40 = ((unsigned int)result >> 7) ^ v3;
      v41 = v40 ^ v4;
      v42 = (unsigned int)result + v41;
      v43 = &BandFilter_anBandTexture[-(__int64)((double)(unsigned __int16)v42 * 0.0000152587890625 * -256.0)];
      nBd = (unsigned __int8)*v43;
      v44 = *v43 >> 8;
      *v43 = v44;
      nGc = (unsigned __int8)v44;
      v45 = *v43 >> 8;
      *v43 = v45;
      *v43 >>= 8;
      v3 = (v42 >> 7) ^ v40;
      v4 = v3 ^ v41;
      result = (struct QTask_s *)(v4 + v42);
      *v43 = ((unsigned int)(__int64)((double)nBd * ((double)(unsigned __int16)result * 0.0000152587890625))
            + (((unsigned int)(__int64)((double)nGc * ((double)(unsigned __int16)result * 0.0000152587890625))
              + ((unsigned int)(__int64)((double)(unsigned __int8)v45
                                       * ((double)(unsigned __int16)result
                                        * 0.0000152587890625)) << 8)) << 8)) << 8;
      --v57;
    }
    while ( v57 );
    Filter_tRandomState.anRandom[0] = (unsigned int)result;
    Filter_tRandomState.anRandom[1] = v4;
    Filter_tRandomState.anRandom[2] = v3;
  }
  return result;
}

// source: f/2/pc/pc_filter.c:1383  [size]
void __cdecl BandFilter_DrawPrim(void *pxPrimitive)
{
  void (__cdecl *v1)(void *); // eax

  v1 = RenderMode_tActiveRenderMode.apfRenderModeMethod[BandFilter_eRenderModeMethod];
  if ( v1 )
    v1(*((void **)pxPrimitive + 3));
}

// source: f/2/pc/pc_filter.c:1405  [anchor-strings]
void __cdecl BandFilter_DrawHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vX; };
    struct { char igi2_o1[4]; float vY; };
    struct { char igi2_o2[8]; float vWidth; };
    struct { char igi2_o3[12]; float vHeight; };
    struct { char igi2_o4[16]; int vR; };
    struct { char igi2_o5[16]; float vRa; };
    struct { char igi2_o6[20]; float vG; };
    struct { char igi2_o7[24]; float nX; };
    struct { char igi2_o8[24]; float nXa; };
    struct { char igi2_o9[28]; float nY; };
    struct { char igi2_o10[56]; char Buffer[52]; };
    char igi2_extent[108];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  _DWORD *v1; // esi
  int v2; // eax
  double v4; // st7
  struct StaticTilemap_s *v5; // esi
  struct QTilemap_s *ptQTilemap; // ebx
  int v7; // eax
  float vA; // edx
  struct QTask_s *ptQTaskb = *(struct QTask_s * *)&ptQTask; // [esp+70h] [ebp+4h] ARGSLOT
  float ptQTaska = *(float *)&ptQTask; // [esp+70h] [ebp+4h] ARGSLOT

  v1 = Primitive_ptNextFreePrimitive;
  Primitive_ptNextFreePrimitive = (char *)Primitive_ptNextFreePrimitive + 16;
  if ( (char *)Primitive_ptNextFreePrimitive - Primitive_asPrimitive[0] > (char *)Primitive_nMaxPrimitiveUsage )
  {
    Primitive_nMaxPrimitiveUsage = (unsigned int)Primitive_ptNextFreePrimitive - Primitive_asPrimitive[0];
    if ( (char *)Primitive_ptNextFreePrimitive - Primitive_asPrimitive[0] > (char *)dword_6B9E3C )
      v1 = nullptr;
  }
  v2 = BandFilter_ePrimType;
  v1[1] = BandFilter_ePrimType;
  v1[3] = ptQTask;
  RenderMode_tActiveRenderMode.apfRenderModeMethod[v2](v1);
  v4 = *(float *)&ptQTask[1].tQTaskChildren.ptHead;
  dword_834E068 = (int)v1;
  if ( v4 != 0.0 )
  {
    sprintf(igi2_frame.Buffer, "CAMERA %d", ptQTask[2].ptParent);
    igi2_frame.nY = (float)(int)(__int64)(RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHeight
                             * BandFilter_vYFactor
                             + BandFilter_vYOffset
                             + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vY);
    igi2_frame.nX = (float)(int)(__int64)(RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vWidth
                             * BandFilter_vXFactor
                             + BandFilter_vXOffset
                             + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX);
    v5 = Text_New((struct QSprite_s *)ptQTask[3].tQTaskChildren.ptHead, igi2_frame.nX, igi2_frame.nY, igi2_frame.Buffer);
    ptQTilemap = v5->ptQTilemap;
    v7 = v5->bQGraphicFlags | 0x40000;
    igi2_frame.vR = v5->nPri;
    vA = v5->vA;
    v5->bQGraphicFlags = v7;
    v5->vR = 100.0;
    v5->vG = 100.0;
    v5->vB = 100.0;
    ptQTaskb = ptQTask[1].ptNext;
    v5->vZ = *(float *)&ptQTaskb;
    QTilemap_Register(ptQTilemap, v5->vX, v5->vY, 100.0, 100.0, 100.0, vA, *(float *)&ptQTaskb, v7 | 0x40000000, igi2_frame.vR);
    Text_Delete(v5);
  }
  if ( *(float *)&ptQTask[1].tQTaskChildren.ptHead == 0.0 )
  {
    if ( *(float *)&ptQTask[1].ptNext <= (double)Direct3D_vWorldMinZ )
      ptQTaska = Direct3D_vWorldMinZ;
    else
      ptQTaska = *(float *)&ptQTask[1].ptNext;
    igi2_frame.nXa = *(float *)&ptQTask[3].ptPrev * 128.0;
    igi2_frame.vG = *(float *)&ptQTask[3].ptNext * 128.0;
    igi2_frame.vRa = *(float *)&ptQTask[2].eQTaskType * 128.0;
    igi2_frame.vHeight = (float)(__int64)RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHeight;
    igi2_frame.vWidth = (float)(__int64)RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vWidth;
    igi2_frame.vY = (float)(__int64)RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vY;
    igi2_frame.vX = (float)(__int64)RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX;
    QSprite_RegisterBlankZ(igi2_frame.vX, igi2_frame.vY, igi2_frame.vWidth, igi2_frame.vHeight, igi2_frame.vRa, igi2_frame.vG, igi2_frame.nXa, 0x80000000, 0, ptQTaska);
  }
}

// source: f/2/pc/pc_filter.c:1494  [anchor-mhash]
void __cdecl BandFilter_RunHandler(struct QTask_s *ptQTask)
{
  struct QReference_s *ptHead; // edx
  double v3; // st7
  struct QTask_s *ptTail; // eax
  struct QReference_s *ptMiddle; // eax
  unsigned int v6; // edx
  unsigned int v7; // edx
  float ptQTaska = *(float *)&ptQTask; // [esp+Ch] [ebp+4h] ARGSLOT

  ptHead = ptQTask[2].tQTaskRefList.ptHead;
  v3 = -*(float *)&ptQTask[1].ptPrev;
  ptQTaska = -4.0 / (double)(int)ptHead;
  if ( v3 <= ptQTaska )
    v3 = ptQTaska;
  ptTail = ptQTask[2].tQTaskChildren.ptTail;
  *(float *)&ptQTask[1].ptPrev = v3 + *(float *)&ptQTask[1].ptPrev;
  if ( (int)ptTail >= (int)ptHead )
    ptQTask[2].tQTaskChildren.ptTail = nullptr;
  else
    ptQTask[2].tQTaskChildren.ptTail = (struct QTask_s *)((char *)&ptTail->ptNext + 1);
  ptMiddle = ptQTask[2].tQTaskRefList.ptMiddle;
  if ( (int)ptMiddle >= (int)ptQTask[2].tQTaskRefList.ptTail )
  {
    v6 = (Filter_tRandomState.anRandom[0] >> 7) ^ Filter_tRandomState.anRandom[2];
    Filter_tRandomState.anRandom[0] += v6 ^ Filter_tRandomState.anRandom[1];
    Filter_tRandomState.anRandom[2] = v6;
    Filter_tRandomState.anRandom[1] ^= v6;
    ptQTask[2].tQTaskRefList.ptMiddle = (struct QReference_s *)(__int64)((double)LOWORD(Filter_tRandomState.anRandom[0])
                                                                       * 0.0000152587890625
                                                                       * (double)(int)ptQTask[2].tQTaskRefList.ptTail
                                                                       * 0.699999988079071);
    v7 = (Filter_tRandomState.anRandom[0] >> 7) ^ Filter_tRandomState.anRandom[2];
    Filter_tRandomState.anRandom[0] += v7 ^ Filter_tRandomState.anRandom[1];
    Filter_tRandomState.anRandom[2] = v7;
    Filter_tRandomState.anRandom[1] ^= v7;
    *(float *)&ptQTask[1].ptPrev = (double)LOWORD(Filter_tRandomState.anRandom[0])
                                 * 0.0000152587890625
                                 * *(float *)&ptQTask[1].tQTaskChildren.ptHead;
  }
  else
  {
    ptQTask[2].tQTaskRefList.ptMiddle = (struct QReference_s *)((char *)&ptMiddle->ptNext + 1);
  }
}

// source: f/2/pc/pc_filter.c:1534  [anchor-caller]
void __cdecl BandFilter_D3DDraw(void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct FilterVertex_t *ptVertex; };
    struct { char igi2_o1[4]; __int64 vY; };
    struct { char igi2_o2[12]; int nNumYCoords; };
    struct { char igi2_o3[16]; float vBandHeight; };
    struct { char igi2_o4[20]; __int64 iStartVertex; };
    struct { char igi2_o5[32]; struct FilterVertex_t tTemplate; };
    struct { char igi2_o6[60]; float avY[100]; };
    struct { char igi2_o7[460]; struct _D3DMATRIX tProjection; };
    char igi2_extent[524];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct RenderStateBlock_t *v1; // ecx
  double v2; // st7
  double v3; // st6
  double v4; // st6
  struct RenderStateBlock_t *v5; // edx
  struct RenderStateBlock_t *v6; // ecx
  struct IDirect3DDevice8Vtbl *lpVtbl; // edx
  double v8; // st7
  int v9; // ecx
  double v10; // st7
  struct IDirect3DBaseTexture8 *v11; // esi
  int v12; // edx
  int v13; // eax
  signed int v14; // esi
  double v15; // st7
  double vZ; // st6
  double v17; // st6
  double v18; // st6
  double v19; // st6
  double v20; // st6
  double v21; // st6
  int v22; // eax
  int v23; // edx
  struct IDirect3DBaseTexture8 *v24; // esi
  int nNumVertices; // eax
  int v26; // edx
  signed int v27; // esi
  int v28; // eax
  double v29; // st7
  double v30; // st6
  double v31; // st6
  double v32; // st6
  double v33; // st6
  double v34; // st6
  double v35; // st6

  if ( *((float *)pxContext + 10) <= (double)Direct3D_vWorldMinZ )
    *(float *)&igi2_frame.nNumYCoords = Direct3D_vWorldMinZ;
  else
    igi2_frame.nNumYCoords = *((int *)pxContext + 10);
  if ( *((float *)pxContext + 12) != 0.0 )
  {
    Direct3D_ptDevice->lpVtbl->GetTransform(Direct3D_ptDevice, D3DTS_PROJECTION, &igi2_frame.tProjection);
    v1 = Direct3D_ptBlendStateBlock;
    igi2_frame.tTemplate.vRhw = 1.0 / (Direct3D_vScale * *(float *)&igi2_frame.nNumYCoords);
    v2 = (1.0 - Direct3D_vD3DMinZ * igi2_frame.tTemplate.vRhw) * igi2_frame.tProjection._33;
    v3 = Direct3D_vMaxZ;
    Direct3D_ptTextureStateBlock->eCurrentState = -1;
    v4 = v3 - Direct3D_vMinZ;
    v5 = Direct3D_ptGenericStateBlock;
    v1->eCurrentState = -1;
    v6 = Direct3D_ptClippingStateBlock;
    v5->eCurrentState = -1;
    v6->eCurrentState = -1;
    lpVtbl = Direct3D_ptDevice->lpVtbl;
    igi2_frame.tTemplate.vZ = v2 * v4 + Direct3D_vMinZ;
    lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZBIAS, 0);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGENABLE, 0);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SPECULARENABLE, 0);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_CULLMODE, 1u);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_LIGHTING, 0);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_DITHERENABLE, 1u);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHATESTENABLE, 0);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZFUNC, 4u);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZENABLE, 0);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZWRITEENABLE, 0);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ADDRESSU, 1u);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ADDRESSV, 1u);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_MIPFILTER, 0);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_TEXCOORDINDEX, 0);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAOP, 2u);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAARG1, 2u);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAARG2, 0);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLOROP, 2u);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLORARG1, 2u);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLORARG2, 0);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_COLOROP, 1u);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHABLENDENABLE, 1u);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SRCBLEND, 9u);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_DESTBLEND, 1u);
    Direct3D_tState.aptStreamData[0] = Direct3D_atDynamicVertexBuffer[2].ptVertexBuffer;
    Direct3D_tState.anStride[0] = Direct3D_atDynamicVertexBuffer[2].nStride;
    Direct3D_ptDevice->lpVtbl->SetStreamSource(
      Direct3D_ptDevice,
      0,
      Direct3D_atDynamicVertexBuffer[2].ptVertexBuffer,
      Direct3D_atDynamicVertexBuffer[2].nStride);
    Direct3D_tState.nHandle = Direct3D_atDynamicVertexBuffer[2].nFVF;
    Direct3D_ptDevice->lpVtbl->SetVertexShader(Direct3D_ptDevice, Direct3D_atDynamicVertexBuffer[2].nFVF);
    igi2_frame.vBandHeight = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHeight * 0.05000000074505806;
    igi2_frame.vY = (__int64)RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vY;
    igi2_frame.nNumYCoords = igi2_frame.vY;
    v8 = (double)(int)igi2_frame.vY;
    *(float *)&igi2_frame.vY = v8;
    igi2_frame.avY[0] = v8;
    if ( (double)*((int *)pxContext + 24) > 45.0 )
      v8 = v8 + igi2_frame.vBandHeight * 0.5;
    igi2_frame.avY[1] = v8;
    v9 = 2;
    v10 = v8 + igi2_frame.vBandHeight;
    igi2_frame.nNumYCoords = 2;
    igi2_frame.iStartVertex = (__int64)RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHeight;
    *(float *)&igi2_frame.iStartVertex = (double)(int)igi2_frame.iStartVertex + *(float *)&igi2_frame.vY;
    if ( v10 < *(float *)&igi2_frame.iStartVertex )
    {
      do
      {
        igi2_frame.avY[v9++] = v10;
        v10 = v10 + igi2_frame.vBandHeight;
      }
      while ( v10 < *(float *)&igi2_frame.iStartVertex );
      igi2_frame.nNumYCoords = v9;
    }
    igi2_frame.avY[v9] = *(float *)&igi2_frame.iStartVertex;
    BandFilter_MakeBandTexture((struct QTask_s *)pxContext);
    BandFilter_AddNoiseToBandTexture((struct QTask_s *)pxContext);
    Texture_Download((struct TexInfo_s *)((char *)pxContext + 52), nullptr, 64, 16, 16, 3, BandFilter_anBandTexture);
    v11 = *((struct IDirect3DBaseTexture8 **)pxContext + 22);
    if ( v11 != Direct3D_tState.aptTexture[0] )
    {
      Direct3D_tState.aptTexture[0] = *((struct IDirect3DBaseTexture8 **)pxContext + 22);
      Direct3D_ptDevice->lpVtbl->SetTexture(Direct3D_ptDevice, 0, v11);
    }
    igi2_frame.ptVertex = nullptr;
    Direct3D_LockDynamicVertexBuffer(&Direct3D_atDynamicVertexBuffer[2], (void **)&igi2_frame.ptVertex, (int *)&igi2_frame.iStartVertex, 100);
    if ( igi2_frame.ptVertex )
    {
      v12 = igi2_frame.nNumYCoords;
      v13 = 1;
      v14 = 0;
      if ( igi2_frame.nNumYCoords > 1 )
      {
        v15 = igi2_frame.vBandHeight * 0.0625;
        v14 = 6 * (((unsigned int)(igi2_frame.nNumYCoords - 2) >> 1) + 1);
        do
        {
          igi2_frame.vY = (__int64)RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX;
          igi2_frame.ptVertex->vX = (float)(int)igi2_frame.vY;
          vZ = igi2_frame.tTemplate.vZ;
          igi2_frame.ptVertex->vY = igi2_frame.avY[v13];
          igi2_frame.ptVertex->vZ = vZ;
          igi2_frame.ptVertex->vRhw = igi2_frame.tTemplate.vRhw;
          igi2_frame.ptVertex->vU = 0.0;
          igi2_frame.ptVertex->vV = 0.0;
          igi2_frame.vY = (__int64)RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX;
          ++igi2_frame.ptVertex;
          igi2_frame.ptVertex->vX = (double)(int)igi2_frame.vY + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vWidth;
          v17 = igi2_frame.tTemplate.vZ;
          igi2_frame.ptVertex->vY = igi2_frame.avY[v13];
          igi2_frame.ptVertex->vZ = v17;
          igi2_frame.ptVertex->vRhw = igi2_frame.tTemplate.vRhw;
          igi2_frame.ptVertex->vU = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vWidth * 0.0625;
          igi2_frame.ptVertex->vV = 0.0;
          igi2_frame.vY = (__int64)RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX;
          ++igi2_frame.ptVertex;
          igi2_frame.ptVertex->vX = (double)(int)igi2_frame.vY + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vWidth;
          v18 = igi2_frame.tTemplate.vZ;
          igi2_frame.ptVertex->vY = igi2_frame.avY[v13 + 1];
          igi2_frame.ptVertex->vZ = v18;
          igi2_frame.ptVertex->vRhw = igi2_frame.tTemplate.vRhw;
          igi2_frame.ptVertex->vU = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vWidth * 0.0625;
          igi2_frame.ptVertex->vV = v15;
          igi2_frame.vY = (__int64)RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX;
          ++igi2_frame.ptVertex;
          igi2_frame.ptVertex->vX = (float)(int)igi2_frame.vY;
          v19 = igi2_frame.tTemplate.vZ;
          igi2_frame.ptVertex->vY = igi2_frame.avY[v13 + 1];
          igi2_frame.ptVertex->vZ = v19;
          v13 += 2;
          igi2_frame.ptVertex->vRhw = igi2_frame.tTemplate.vRhw;
          igi2_frame.ptVertex->vU = 0.0;
          igi2_frame.ptVertex->vV = v15;
          igi2_frame.vY = (__int64)RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX;
          ++igi2_frame.ptVertex;
          igi2_frame.ptVertex->vX = (double)(int)igi2_frame.vY + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vWidth;
          v20 = igi2_frame.tTemplate.vZ;
          igi2_frame.ptVertex->vY = *(&igi2_frame.tTemplate.vV + v13);
          igi2_frame.ptVertex->vZ = v20;
          igi2_frame.ptVertex->vRhw = igi2_frame.tTemplate.vRhw;
          igi2_frame.ptVertex->vU = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vWidth * 0.0625;
          igi2_frame.ptVertex->vV = v15;
          igi2_frame.vY = (__int64)RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX;
          ++igi2_frame.ptVertex;
          igi2_frame.ptVertex->vX = (float)(int)igi2_frame.vY;
          v21 = igi2_frame.tTemplate.vZ;
          igi2_frame.ptVertex->vY = *(&igi2_frame.tTemplate.vU + v13);
          igi2_frame.ptVertex->vZ = v21;
          igi2_frame.ptVertex->vRhw = igi2_frame.tTemplate.vRhw;
          igi2_frame.ptVertex->vU = 0.0;
          igi2_frame.ptVertex->vV = 0.0;
          ++igi2_frame.ptVertex;
        }
        while ( v13 < v12 );
      }
      Direct3D_atDynamicVertexBuffer[2].ptVertexBuffer->lpVtbl->Unlock(Direct3D_atDynamicVertexBuffer[2].ptVertexBuffer);
      Direct3D_ptDevice->lpVtbl->DrawPrimitive(Direct3D_ptDevice, D3DPT_TRIANGLELIST, igi2_frame.iStartVertex, v14 / 3);
      igi2_frame.vY = (__int64)(*((float *)pxContext + 29) * -255.0);
      v22 = (_DWORD)igi2_frame.vY << 8;
      igi2_frame.vY = (__int64)(*((float *)pxContext + 30) * -255.0);
      v23 = ((_DWORD)igi2_frame.vY + v22) << 8;
      igi2_frame.vY = (__int64)(*((float *)pxContext + 31) * 255.0);
      memset32(BandFilter_anBandTexture, igi2_frame.vY - v23, 0x100u);
      BandFilter_AddNoiseToBandTexture((struct QTask_s *)pxContext);
      Texture_Download((struct TexInfo_s *)((char *)pxContext + 52), nullptr, 64, 16, 16, 3, BandFilter_anBandTexture);
      v24 = *((struct IDirect3DBaseTexture8 **)pxContext + 22);
      if ( v24 != Direct3D_tState.aptTexture[0] )
      {
        Direct3D_tState.aptTexture[0] = *((struct IDirect3DBaseTexture8 **)pxContext + 22);
        Direct3D_ptDevice->lpVtbl->SetTexture(Direct3D_ptDevice, 0, v24);
      }
      nNumVertices = Direct3D_atDynamicVertexBuffer[2].nNumVertices;
      igi2_frame.ptVertex = nullptr;
      if ( Direct3D_atDynamicVertexBuffer[2].nNumVertices + 100 > Direct3D_atDynamicVertexBuffer[2].nMaxVertices )
      {
        nNumVertices = 0;
        Direct3D_atDynamicVertexBuffer[2].nNumVertices = 0;
      }
      if ( !Direct3D_atDynamicVertexBuffer[2].ptVertexBuffer->lpVtbl->Lock(
              Direct3D_atDynamicVertexBuffer[2].ptVertexBuffer,
              Direct3D_atDynamicVertexBuffer[2].nStride * nNumVertices,
              100 * Direct3D_atDynamicVertexBuffer[2].nStride,
              (unsigned __int8 **)&igi2_frame.ptVertex,
              nNumVertices != 0 ? 4096 : 0x2000) )
      {
        LODWORD(igi2_frame.iStartVertex) = Direct3D_atDynamicVertexBuffer[2].nNumVertices;
        Direct3D_atDynamicVertexBuffer[2].nNumVertices += 100;
        if ( igi2_frame.ptVertex )
        {
          v26 = igi2_frame.nNumYCoords;
          v27 = 0;
          v28 = 0;
          if ( igi2_frame.nNumYCoords > 0 )
          {
            v29 = igi2_frame.vBandHeight * 0.0625;
            v27 = 6 * (((unsigned int)(igi2_frame.nNumYCoords - 1) >> 1) + 1);
            do
            {
              igi2_frame.vY = (__int64)RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX;
              igi2_frame.ptVertex->vX = (float)(int)igi2_frame.vY;
              v30 = igi2_frame.tTemplate.vZ;
              igi2_frame.ptVertex->vY = igi2_frame.avY[v28];
              igi2_frame.ptVertex->vZ = v30;
              igi2_frame.ptVertex->vRhw = igi2_frame.tTemplate.vRhw;
              igi2_frame.ptVertex->vU = 0.0;
              igi2_frame.ptVertex->vV = 0.0;
              igi2_frame.vY = (__int64)RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX;
              ++igi2_frame.ptVertex;
              igi2_frame.ptVertex->vX = (double)(int)igi2_frame.vY + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vWidth;
              v31 = igi2_frame.tTemplate.vZ;
              igi2_frame.ptVertex->vY = igi2_frame.avY[v28];
              igi2_frame.ptVertex->vZ = v31;
              igi2_frame.ptVertex->vRhw = igi2_frame.tTemplate.vRhw;
              igi2_frame.ptVertex->vU = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vWidth * 0.0625;
              igi2_frame.ptVertex->vV = 0.0;
              igi2_frame.vY = (__int64)RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX;
              ++igi2_frame.ptVertex;
              igi2_frame.ptVertex->vX = (double)(int)igi2_frame.vY + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vWidth;
              v32 = igi2_frame.tTemplate.vZ;
              igi2_frame.ptVertex->vY = igi2_frame.avY[v28 + 1];
              igi2_frame.ptVertex->vZ = v32;
              igi2_frame.ptVertex->vRhw = igi2_frame.tTemplate.vRhw;
              igi2_frame.ptVertex->vU = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vWidth * 0.0625;
              igi2_frame.ptVertex->vV = v29;
              igi2_frame.vY = (__int64)RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX;
              ++igi2_frame.ptVertex;
              igi2_frame.ptVertex->vX = (float)(int)igi2_frame.vY;
              v33 = igi2_frame.tTemplate.vZ;
              igi2_frame.ptVertex->vY = igi2_frame.avY[v28 + 1];
              igi2_frame.ptVertex->vZ = v33;
              v28 += 2;
              igi2_frame.ptVertex->vRhw = igi2_frame.tTemplate.vRhw;
              igi2_frame.ptVertex->vU = 0.0;
              igi2_frame.ptVertex->vV = v29;
              igi2_frame.vY = (__int64)RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX;
              ++igi2_frame.ptVertex;
              igi2_frame.ptVertex->vX = (double)(int)igi2_frame.vY + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vWidth;
              v34 = igi2_frame.tTemplate.vZ;
              igi2_frame.ptVertex->vY = *(&igi2_frame.tTemplate.vV + v28);
              igi2_frame.ptVertex->vZ = v34;
              igi2_frame.ptVertex->vRhw = igi2_frame.tTemplate.vRhw;
              igi2_frame.ptVertex->vU = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vWidth * 0.0625;
              igi2_frame.ptVertex->vV = v29;
              igi2_frame.vY = (__int64)RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX;
              ++igi2_frame.ptVertex;
              igi2_frame.ptVertex->vX = (float)(int)igi2_frame.vY;
              v35 = igi2_frame.tTemplate.vZ;
              igi2_frame.ptVertex->vY = *(&igi2_frame.tTemplate.vU + v28);
              igi2_frame.ptVertex->vZ = v35;
              igi2_frame.ptVertex->vRhw = igi2_frame.tTemplate.vRhw;
              igi2_frame.ptVertex->vU = 0.0;
              igi2_frame.ptVertex->vV = 0.0;
              ++igi2_frame.ptVertex;
            }
            while ( v28 < v26 );
          }
          Direct3D_atDynamicVertexBuffer[2].ptVertexBuffer->lpVtbl->Unlock(Direct3D_atDynamicVertexBuffer[2].ptVertexBuffer);
          Direct3D_ptDevice->lpVtbl->DrawPrimitive(Direct3D_ptDevice, D3DPT_TRIANGLELIST, igi2_frame.iStartVertex, v27 / 3);
        }
      }
    }
  }
}

// source: f/2/pc/pc_filter.c:1871  [anchor-callee]
void __cdecl BandFilter_SetColor(struct QTask_s *ptQTask, float vR, float vG, float vB)
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
  *(float *)&ptQTask[2].eQTaskType = v4;
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
  *(float *)&ptQTask[3].ptNext = v5;
  if ( vB >= 0.0 )
  {
    if ( vB <= 1.0 )
      *(float *)&ptQTask[3].ptPrev = vB;
    else
      ptQTask[3].ptPrev = (struct QTask_s *)1065353216;
  }
  else
  {
    ptQTask[3].ptPrev = nullptr;
  }
}

// source: f/2/pc/pc_filter.c:1893  [size]
char *__cdecl BandFilter_SetCameraFont(
        char *zCameraFont,
        float vXFactor,
        float vYFactor,
        float vXOffset,
        float vYOffset)
{
  BandFilter_zCameraFont = zCameraFont;
  BandFilter_vXFactor = vXFactor;
  BandFilter_vYFactor = vYFactor;
  BandFilter_vXOffset = vXOffset;
  BandFilter_vYOffset = vYOffset;
  return (char *)LODWORD(vXOffset);
}

// source: f/2/pc/pc_filter.c:1911  [anchor-hash]
void __cdecl BandFilter_UpdateCameraNr()
{
  if ( BandFilter_nCameraNumber >= 9 )
    BandFilter_nCameraNumber = 1;
  else
    ++BandFilter_nCameraNumber;
}

// source: f/2/pc/pc_filter.c:1931  [size]
void __cdecl ComputerFilter_D3DDraw(void *pxContext)
{
  struct RenderStateBlock_t *v1; // edx
  struct RenderStateBlock_t *v2; // ecx
  struct RenderStateBlock_t *v3; // edx
  unsigned int v4; // edx
  unsigned int v5; // eax
  int v6; // eax
  int v7; // eax
  struct IDirect3DBaseTexture8 *ptDirect3DBaseTexture; // eax
  struct FilterVertex_t atVertex[4]; // [esp+160h] [ebp-70h] BYREF

  v1 = Direct3D_ptBlendStateBlock;
  atVertex[3].vX = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vWidth;
  atVertex[1].vX = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vWidth;
  atVertex[0].nColor = -2139062144;
  atVertex[1].nColor = -2139062144;
  atVertex[3].vY = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHeight;
  atVertex[2].nColor = -2139062144;
  atVertex[2].vY = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHeight;
  atVertex[3].nColor = -2139062144;
  memset(atVertex, 0, 12);
  atVertex[0].vRhw = 1.0;
  atVertex[0].vU = 0.0;
  atVertex[0].vV = 0.0;
  atVertex[1].vY = 0.0;
  atVertex[1].vZ = 0.0;
  atVertex[1].vRhw = 1.0;
  atVertex[1].vU = 40.0;
  atVertex[1].vV = 0.0;
  atVertex[2].vX = 0.0;
  atVertex[2].vZ = 0.0;
  atVertex[2].vRhw = 1.0;
  atVertex[2].vU = 0.0;
  atVertex[2].vV = 30.0;
  atVertex[3].vZ = 0.0;
  atVertex[3].vRhw = 1.0;
  atVertex[3].vU = 40.0;
  atVertex[3].vV = 30.0;
  Direct3D_ptTextureStateBlock->eCurrentState = -1;
  v2 = Direct3D_ptGenericStateBlock;
  v1->eCurrentState = -1;
  v3 = Direct3D_ptClippingStateBlock;
  v2->eCurrentState = -1;
  v3->eCurrentState = -1;
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZBIAS, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SPECULARENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_CULLMODE, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_LIGHTING, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_DITHERENABLE, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHATESTENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZFUNC, 4u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZWRITEENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ADDRESSU, 1u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ADDRESSV, 1u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_MAGFILTER, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_MINFILTER, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAOP, 3u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAARG1, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAARG2, 0);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLOROP, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLORARG1, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLORARG2, 0);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_COLOROP, 1u);
  if ( *(_DWORD *)pxContext
    && (v4 = (Filter_tRandomState.anRandom[0] >> 7) ^ Filter_tRandomState.anRandom[2],
        v5 = (v4 ^ Filter_tRandomState.anRandom[1]) + Filter_tRandomState.anRandom[0],
        Filter_tRandomState.anRandom[2] = v4,
        Filter_tRandomState.anRandom[1] ^= v4,
        Filter_tRandomState.anRandom[0] = v5,
        (int)(v5 % 0x64) < 2) )
  {
    v6 = dword_79F3688;
    dword_79F3680 = 5;
    *(_DWORD *)pxContext = 0;
    v7 = v6 + 2;
  }
  else if ( dword_79F3680 )
  {
    v7 = dword_79F3688 + 2;
  }
  else
  {
    v7 = dword_79F3688;
  }
  ptDirect3DBaseTexture = atLineFilterTexture[v7].tTexInfo.ptDirect3DBaseTexture;
  if ( ptDirect3DBaseTexture != Direct3D_tState.aptTexture[0] )
  {
    Direct3D_tState.aptTexture[0] = ptDirect3DBaseTexture;
    Direct3D_ptDevice->lpVtbl->SetTexture(Direct3D_ptDevice, 0, ptDirect3DBaseTexture);
  }
  if ( dword_79F3680 > 0 )
    --dword_79F3680;
  dword_79F3688 = 1 - dword_79F3688;
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHABLENDENABLE, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SRCBLEND, 9u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_DESTBLEND, 3u);
  Direct3D_tState.nHandle = 324;
  Direct3D_ptDevice->lpVtbl->SetVertexShader(Direct3D_ptDevice, 324u);
  Direct3D_tState.aptStreamData[0] = nullptr;
  Direct3D_tState.anStride[0] = 0;
  Direct3D_ptDevice->lpVtbl->DrawPrimitiveUP(Direct3D_ptDevice, D3DPT_TRIANGLESTRIP, 2u, atVertex, 28u);
}

// source: f/2/pc/pc_filter.c:2019  [anchor-mhash]
void __cdecl HandiCamFilter_D3DDraw(void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct FilterVertex_t *ptVertex; };
    struct { char igi2_o1[4]; __int64 vX; };
    struct { char igi2_o2[16]; int iStartVertex; };
    struct { char igi2_o3[20]; float vY; };
    struct { char igi2_o4[24]; struct FilterVertex_t tTemplate; };
    struct { char igi2_o5[52]; float avXFactor[4]; };
    struct { char igi2_o6[68]; float avYFactor[4]; };
    struct { char igi2_o7[84]; float avXSign[4]; };
    struct { char igi2_o8[100]; float avYSign[4]; };
    struct { char igi2_o9[116]; struct _D3DMATRIX tProjection; };
    char igi2_extent[180];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct RenderStateBlock_t *v1; // ecx
  double v2; // st7
  double v3; // st6
  double v4; // st6
  struct RenderStateBlock_t *v5; // edx
  struct RenderStateBlock_t *v6; // ecx
  struct IDirect3DDevice8Vtbl *lpVtbl; // edx
  int v8; // esi
  double v9; // st7
  int v10; // edx
  int v11; // edx
  int v12; // edx
  int v13; // edx
  double v14; // st7
  int v15; // edx
  int v16; // edx
  int v17; // edx
  int v18; // edx
  double v19; // st7
  int v20; // ebx
  int v21; // eax
  double v22; // st7
  double v23; // st6
  double v24; // st5
  double v25; // st4
  double v26; // st5
  double v27; // st5
  double v28; // st4
  double v29; // st4
  double v30; // st5
  double v31; // st5
  double v32; // st4
  double v33; // st5
  double v34; // st4
  double v35; // st4

  if ( *((float *)pxContext + 13) <= (double)Direct3D_vWorldMinZ )
    *(float *)&igi2_frame.iStartVertex = Direct3D_vWorldMinZ;
  else
    igi2_frame.iStartVertex = *((int *)pxContext + 13);
  Direct3D_ptDevice->lpVtbl->GetTransform(Direct3D_ptDevice, D3DTS_PROJECTION, &igi2_frame.tProjection);
  v1 = Direct3D_ptBlendStateBlock;
  igi2_frame.tTemplate.vRhw = 1.0 / (Direct3D_vScale * *(float *)&igi2_frame.iStartVertex);
  v2 = (1.0 - Direct3D_vD3DMinZ * igi2_frame.tTemplate.vRhw) * igi2_frame.tProjection._33;
  v3 = Direct3D_vMaxZ;
  Direct3D_ptTextureStateBlock->eCurrentState = -1;
  v4 = v3 - Direct3D_vMinZ;
  v5 = Direct3D_ptGenericStateBlock;
  v1->eCurrentState = -1;
  v6 = Direct3D_ptClippingStateBlock;
  v5->eCurrentState = -1;
  v6->eCurrentState = -1;
  lpVtbl = Direct3D_ptDevice->lpVtbl;
  igi2_frame.tTemplate.vZ = v2 * v4 + Direct3D_vMinZ;
  lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZBIAS, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SPECULARENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_CULLMODE, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_LIGHTING, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_DITHERENABLE, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHATESTENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZFUNC, 4u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZWRITEENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAOP, 3u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAARG1, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAARG2, 0);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLOROP, 3u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLORARG1, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLORARG2, 0);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_COLOROP, 1u);
  if ( Direct3D_tState.aptTexture[0] )
  {
    Direct3D_tState.aptTexture[0] = nullptr;
    Direct3D_ptDevice->lpVtbl->SetTexture(Direct3D_ptDevice, 0, nullptr);
  }
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHABLENDENABLE, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SRCBLEND, 5u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_DESTBLEND, 6u);
  Direct3D_tState.aptStreamData[0] = Direct3D_atDynamicVertexBuffer[2].ptVertexBuffer;
  Direct3D_tState.anStride[0] = Direct3D_atDynamicVertexBuffer[2].nStride;
  Direct3D_ptDevice->lpVtbl->SetStreamSource(
    Direct3D_ptDevice,
    0,
    Direct3D_atDynamicVertexBuffer[2].ptVertexBuffer,
    Direct3D_atDynamicVertexBuffer[2].nStride);
  Direct3D_tState.nHandle = Direct3D_atDynamicVertexBuffer[2].nFVF;
  Direct3D_ptDevice->lpVtbl->SetVertexShader(Direct3D_ptDevice, Direct3D_atDynamicVertexBuffer[2].nFVF);
  Direct3D_LockDynamicVertexBuffer(&Direct3D_atDynamicVertexBuffer[2], (void **)&igi2_frame.ptVertex, &igi2_frame.iStartVertex, 200);
  if ( igi2_frame.ptVertex )
  {
    igi2_frame.vY = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vY;
    v8 = 0;
    if ( RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHeight
       + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vY >= RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vY
                                                                              + 4.0 )
    {
      do
      {
        if ( v8 >= 196 )
        {
          Direct3D_atDynamicVertexBuffer[2].ptVertexBuffer->lpVtbl->Unlock(Direct3D_atDynamicVertexBuffer[2].ptVertexBuffer);
          Direct3D_ptDevice->lpVtbl->DrawPrimitive(Direct3D_ptDevice, D3DPT_LINELIST, igi2_frame.iStartVertex, v8 / 2);
          Direct3D_LockDynamicVertexBuffer(&Direct3D_atDynamicVertexBuffer[2], (void **)&igi2_frame.ptVertex, &igi2_frame.iStartVertex, 200);
          if ( !igi2_frame.ptVertex )
            return;
          v8 = 0;
          igi2_frame.vY = igi2_frame.vY - 4.0;
        }
        else
        {
          LODWORD(igi2_frame.vX) = (__int64)igi2_frame.vY;
          v9 = (double)(int)igi2_frame.vX;
          igi2_frame.vX = (__int64)RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX;
          igi2_frame.ptVertex->vX = (float)(int)igi2_frame.vX;
          igi2_frame.ptVertex->vY = v9;
          igi2_frame.ptVertex->vZ = igi2_frame.tTemplate.vZ;
          igi2_frame.ptVertex->vRhw = igi2_frame.tTemplate.vRhw;
          igi2_frame.vX = (__int64)(*((float *)pxContext + 10) * 255.0);
          v10 = ((unsigned __int8)igi2_frame.vX | 0x4C00) << 8;
          igi2_frame.vX = (__int64)(*((float *)pxContext + 11) * 255.0);
          v11 = ((unsigned __int8)igi2_frame.vX | v10) << 8;
          igi2_frame.vX = (__int64)(*((float *)pxContext + 12) * 255.0);
          igi2_frame.ptVertex->nColor = (unsigned __int8)igi2_frame.vX | v11;
          ++igi2_frame.ptVertex;
          igi2_frame.vX = (__int64)(RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vWidth
                       + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX);
          igi2_frame.ptVertex->vX = (float)(int)igi2_frame.vX;
          igi2_frame.ptVertex->vY = v9;
          igi2_frame.ptVertex->vZ = igi2_frame.tTemplate.vZ;
          igi2_frame.ptVertex->vRhw = igi2_frame.tTemplate.vRhw;
          igi2_frame.vX = (__int64)(*((float *)pxContext + 10) * 255.0);
          v12 = ((unsigned __int8)igi2_frame.vX | 0x4C00) << 8;
          igi2_frame.vX = (__int64)(*((float *)pxContext + 11) * 255.0);
          v13 = ((unsigned __int8)igi2_frame.vX | v12) << 8;
          igi2_frame.vX = (__int64)(*((float *)pxContext + 12) * 255.0);
          v14 = v9 + 1.0;
          igi2_frame.ptVertex->nColor = (unsigned __int8)igi2_frame.vX | v13;
          igi2_frame.vX = (__int64)RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX;
          ++igi2_frame.ptVertex;
          igi2_frame.ptVertex->vX = (float)(int)igi2_frame.vX;
          igi2_frame.ptVertex->vY = v14;
          igi2_frame.ptVertex->vZ = igi2_frame.tTemplate.vZ;
          igi2_frame.ptVertex->vRhw = igi2_frame.tTemplate.vRhw;
          igi2_frame.vX = (__int64)(*((float *)pxContext + 10) * 255.0);
          v15 = ((unsigned __int8)igi2_frame.vX | 0x4C00) << 8;
          igi2_frame.vX = (__int64)(*((float *)pxContext + 11) * 255.0);
          v16 = ((unsigned __int8)igi2_frame.vX | v15) << 8;
          igi2_frame.vX = (__int64)(*((float *)pxContext + 12) * 255.0);
          igi2_frame.ptVertex->nColor = (unsigned __int8)igi2_frame.vX | v16;
          ++igi2_frame.ptVertex;
          igi2_frame.vX = (__int64)(RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vWidth
                       + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX);
          igi2_frame.ptVertex->vX = (float)(int)igi2_frame.vX;
          igi2_frame.ptVertex->vY = v14;
          igi2_frame.ptVertex->vZ = igi2_frame.tTemplate.vZ;
          igi2_frame.ptVertex->vRhw = igi2_frame.tTemplate.vRhw;
          igi2_frame.vX = (__int64)(*((float *)pxContext + 10) * 255.0);
          v17 = ((unsigned __int8)igi2_frame.vX | 0x4C00) << 8;
          igi2_frame.vX = (__int64)(*((float *)pxContext + 11) * 255.0);
          v18 = ((unsigned __int8)igi2_frame.vX | v17) << 8;
          igi2_frame.vX = (__int64)(*((float *)pxContext + 12) * 255.0);
          igi2_frame.ptVertex->nColor = (unsigned __int8)igi2_frame.vX | v18;
          v8 += 4;
          ++igi2_frame.ptVertex;
        }
        v19 = igi2_frame.vY + 4.0;
        igi2_frame.vY = v19;
      }
      while ( RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHeight
            + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vY >= v19 + 4.0 );
    }
    Direct3D_atDynamicVertexBuffer[2].ptVertexBuffer->lpVtbl->Unlock(Direct3D_atDynamicVertexBuffer[2].ptVertexBuffer);
    if ( v8 > 0 )
      Direct3D_ptDevice->lpVtbl->DrawPrimitive(Direct3D_ptDevice, D3DPT_LINELIST, igi2_frame.iStartVertex, v8 / 2);
    v20 = 0;
    Direct3D_LockDynamicVertexBuffer(&Direct3D_atDynamicVertexBuffer[2], (void **)&igi2_frame.ptVertex, &igi2_frame.iStartVertex, 200);
    if ( igi2_frame.ptVertex )
    {
      igi2_frame.avXFactor[0] = 0.10000000149011612;
      igi2_frame.avXFactor[1] = 0.8999999761581421;
      igi2_frame.avXFactor[2] = 0.10000000149011612;
      igi2_frame.avXFactor[3] = 0.8999999761581421;
      igi2_frame.avYFactor[0] = 0.20000000298023224;
      igi2_frame.avYFactor[1] = 0.20000000298023224;
      igi2_frame.avYFactor[2] = 0.800000011920929;
      igi2_frame.avYFactor[3] = 0.800000011920929;
      igi2_frame.avXSign[0] = 1.0;
      igi2_frame.avXSign[1] = -1.0;
      igi2_frame.avXSign[2] = 1.0;
      igi2_frame.avXSign[3] = -1.0;
      igi2_frame.avYSign[0] = 1.0;
      igi2_frame.avYSign[1] = 1.0;
      igi2_frame.avYSign[2] = -1.0;
      igi2_frame.avYSign[3] = -1.0;
      v21 = 0;
      do
      {
        v22 = igi2_frame.avXSign[v21] * 50.0;
        v23 = igi2_frame.avYSign[v21] * 50.0;
        igi2_frame.vX = (__int64)(RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vWidth * igi2_frame.avXFactor[v21]
                     + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX);
        igi2_frame.ptVertex->vX = (float)(int)igi2_frame.vX;
        v24 = igi2_frame.avYSign[v21] * 0.0;
        igi2_frame.vX = (__int64)(RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHeight * igi2_frame.avYFactor[v21]
                     + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vY);
        igi2_frame.ptVertex->vY = (double)(int)igi2_frame.vX + v24;
        igi2_frame.ptVertex->vZ = igi2_frame.tTemplate.vZ;
        igi2_frame.ptVertex->vRhw = igi2_frame.tTemplate.vRhw;
        igi2_frame.ptVertex->nColor = -1;
        v25 = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vWidth * igi2_frame.avXFactor[v21];
        ++igi2_frame.ptVertex;
        igi2_frame.vX = (__int64)(v25 + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX);
        igi2_frame.ptVertex->vX = (double)(int)igi2_frame.vX + v22;
        igi2_frame.vX = (__int64)(RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHeight * igi2_frame.avYFactor[v21]
                     + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vY);
        igi2_frame.ptVertex->vY = (double)(int)igi2_frame.vX + v24;
        igi2_frame.ptVertex->vZ = igi2_frame.tTemplate.vZ;
        igi2_frame.ptVertex->vRhw = igi2_frame.tTemplate.vRhw;
        v26 = igi2_frame.avXSign[v21];
        igi2_frame.ptVertex->nColor = -1;
        v27 = v26 * 0.0;
        v28 = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vWidth * igi2_frame.avXFactor[v21];
        ++igi2_frame.ptVertex;
        igi2_frame.vX = (__int64)(v28 + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX);
        igi2_frame.ptVertex->vX = (double)(int)igi2_frame.vX + v27;
        igi2_frame.vX = (__int64)(RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHeight * igi2_frame.avYFactor[v21]
                     + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vY);
        igi2_frame.ptVertex->vY = (float)(int)igi2_frame.vX;
        igi2_frame.ptVertex->vZ = igi2_frame.tTemplate.vZ;
        igi2_frame.ptVertex->vRhw = igi2_frame.tTemplate.vRhw;
        igi2_frame.ptVertex->nColor = -1;
        v29 = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vWidth * igi2_frame.avXFactor[v21];
        ++igi2_frame.ptVertex;
        igi2_frame.vX = (__int64)(v29 + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX);
        igi2_frame.ptVertex->vX = (double)(int)igi2_frame.vX + v27;
        igi2_frame.vX = (__int64)(RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHeight * igi2_frame.avYFactor[v21]
                     + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vY);
        igi2_frame.ptVertex->vY = (double)(int)igi2_frame.vX + v23;
        igi2_frame.ptVertex->vZ = igi2_frame.tTemplate.vZ;
        igi2_frame.ptVertex->vRhw = igi2_frame.tTemplate.vRhw;
        igi2_frame.ptVertex->nColor = -1;
        v30 = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vWidth * igi2_frame.avXFactor[v21];
        ++igi2_frame.ptVertex;
        igi2_frame.vX = (__int64)(v30 + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX);
        igi2_frame.ptVertex->vX = (float)(int)igi2_frame.vX;
        v31 = igi2_frame.avYSign[v21];
        igi2_frame.vX = (__int64)(RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHeight * igi2_frame.avYFactor[v21]
                     + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vY);
        igi2_frame.ptVertex->vY = (double)(int)igi2_frame.vX + v31;
        igi2_frame.ptVertex->vZ = igi2_frame.tTemplate.vZ;
        igi2_frame.ptVertex->vRhw = igi2_frame.tTemplate.vRhw;
        igi2_frame.ptVertex->nColor = -1;
        v32 = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vWidth * igi2_frame.avXFactor[v21];
        ++igi2_frame.ptVertex;
        igi2_frame.vX = (__int64)(v32 + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX);
        igi2_frame.ptVertex->vX = (double)(int)igi2_frame.vX + v22;
        igi2_frame.vX = (__int64)(RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHeight * igi2_frame.avYFactor[v21]
                     + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vY);
        igi2_frame.ptVertex->vY = (double)(int)igi2_frame.vX + v31;
        igi2_frame.ptVertex->vZ = igi2_frame.tTemplate.vZ;
        igi2_frame.ptVertex->vRhw = igi2_frame.tTemplate.vRhw;
        v33 = igi2_frame.avXSign[v21];
        igi2_frame.ptVertex->nColor = -1;
        v34 = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vWidth * igi2_frame.avXFactor[v21];
        ++igi2_frame.ptVertex;
        igi2_frame.vX = (__int64)(v34 + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX);
        igi2_frame.ptVertex->vX = (double)(int)igi2_frame.vX + v33;
        igi2_frame.vX = (__int64)(RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHeight * igi2_frame.avYFactor[v21]
                     + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vY);
        igi2_frame.ptVertex->vY = (float)(int)igi2_frame.vX;
        igi2_frame.ptVertex->vZ = igi2_frame.tTemplate.vZ;
        igi2_frame.ptVertex->vRhw = igi2_frame.tTemplate.vRhw;
        igi2_frame.ptVertex->nColor = -1;
        v35 = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vWidth * igi2_frame.avXFactor[v21];
        ++igi2_frame.ptVertex;
        igi2_frame.vX = (__int64)(v35 + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX);
        igi2_frame.ptVertex->vX = (double)(int)igi2_frame.vX + v33;
        igi2_frame.vX = (__int64)(RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHeight * igi2_frame.avYFactor[v21]
                     + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vY);
        igi2_frame.ptVertex->vY = (double)(int)igi2_frame.vX + v23;
        igi2_frame.ptVertex->vZ = igi2_frame.tTemplate.vZ;
        ++v21;
        igi2_frame.ptVertex->vRhw = igi2_frame.tTemplate.vRhw;
        igi2_frame.ptVertex->nColor = -1;
        v20 += 8;
        ++igi2_frame.ptVertex;
      }
      while ( v21 < 4 );
      Direct3D_atDynamicVertexBuffer[2].ptVertexBuffer->lpVtbl->Unlock(Direct3D_atDynamicVertexBuffer[2].ptVertexBuffer);
      Direct3D_ptDevice->lpVtbl->DrawPrimitive(Direct3D_ptDevice, D3DPT_LINELIST, igi2_frame.iStartVertex, v20 / 2);
    }
  }
}

// source: f/2/pc/pc_filter.c:2304  [size]
struct QTask_s *__cdecl HandiCamFilter_New(
        struct QTask_s *ptParent,
        float vR,
        float vG,
        float vB,
        float vZ)
{
  struct QTask_s *v5; // esi
  bool v6; // zf
  DWORD TickCount; // eax
  char *v8; // edi
  struct QSprite_s *Font; // eax
  char *v11; // [esp-4h] [ebp-Ch]

  v5 = QTask_NewFn(ptParent, HandiCamFilter_eQTaskType, nullptr);
  *(float *)&v5[1].ptNext = vR;
  *(float *)&v5[1].tQTaskChildren.ptMiddle = vZ;
  v6 = Timer_isPerformanceCounter == 0;
  *(float *)&v5[1].ptPrev = vG;
  *(float *)&v5[1].tQTaskChildren.ptHead = vB;
  v5[2].ptPrev = nullptr;
  if ( v6 )
    TickCount = GetTickCount();
  else
    TickCount = Timer_GetPerformanceCounter();
  v8 = HandiCamFilter_zCounterFont;
  v5[2].tQTaskChildren.ptHead = (struct QTask_s *)(TickCount - Timer_nStartTime);
  v5[1].tQTaskChildren.ptTail = nullptr;
  Font = FontManager_LoadFont(v8);
  v11 = HandiCamFilter_zBatterySprite;
  v5[1].tQTaskChildren.ptTail = (struct QTask_s *)Font;
  QSprite_Load((struct QSprite_s *)&v5[1].tQTaskRefList, v11);
  return v5;
}

// source: f/2/pc/pc_filter.c:2358  [size]
void __cdecl HandiCamFilter_DeleteHandler(struct QTask_s *ptQTask)
{
  QSprite_DeAlloc((struct QSprite_s *)&ptQTask[1].tQTaskRefList);
  FontManager_DeleteFont((struct QSprite_s *)ptQTask[1].tQTaskChildren.ptTail);
}

// source: f/2/pc/pc_filter.c:2380  [size]
void __cdecl HandiCamFilter_DrawPrim(void *pxPrimitive)
{
  void (__cdecl *v1)(void *); // eax

  v1 = RenderMode_tActiveRenderMode.apfRenderModeMethod[HandiCamFilter_eRenderModeMethod];
  if ( v1 )
    v1(*((void **)pxPrimitive + 3));
}

// source: f/2/pc/pc_filter.c:2399  [anchor-mhash]
void __cdecl HandiCamFilter_RunHandler(struct QTask_s *ptQTask)
{
  DWORD PerformanceCounter; // eax
  double v2; // st7
  double v3; // st7

  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  v2 = (double)(int)(PerformanceCounter - Timer_nStartTime - (unsigned int)ptQTask[2].tQTaskChildren.ptHead);
  ptQTask[2].tQTaskChildren.ptHead = (struct QTask_s *)(PerformanceCounter - Timer_nStartTime);
  HandiCamFilter_vCounterFrames = 0.024000000208616257 * v2 + HandiCamFilter_vCounterFrames;
  v3 = v2 * 0.0010000000474974513 + *(float *)&ptQTask[2].ptPrev;
  *(float *)&ptQTask[2].ptPrev = v3;
  if ( v3 > 1.5 )
    ptQTask[2].ptPrev = nullptr;
}

// source: f/2/pc/pc_filter.c:2432  [anchor-strings]
void __cdecl HandiCamFilter_DrawHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v9; };
    struct { char igi2_o1[8]; float nX; };
    struct { char igi2_o2[12]; float nY; };
    struct { char igi2_o3[32]; float vX3; };
    struct { char igi2_o4[36]; float ptQSprite; };
    struct { char igi2_o5[40]; float vY1; };
    struct { char igi2_o6[44]; float vX1; };
    struct { char igi2_o7[52]; char Buffer[52]; };
    char igi2_extent[104];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  _DWORD *v1; // esi
  int v2; // eax
  struct StaticTilemap_s *v4; // esi
  int nPri; // edx
  int v6; // eax
  float vA; // edx
  double v8; // st7
  struct QTask_s *ptQTaskb = *(struct QTask_s * *)&ptQTask; // [esp+64h] [ebp+4h] ARGSLOT
  float ptQTaska = *(float *)&ptQTask; // [esp+64h] [ebp+4h] ARGSLOT

  v1 = Primitive_ptNextFreePrimitive;
  Primitive_ptNextFreePrimitive = (char *)Primitive_ptNextFreePrimitive + 16;
  if ( (char *)Primitive_ptNextFreePrimitive - Primitive_asPrimitive[0] > (char *)Primitive_nMaxPrimitiveUsage )
  {
    Primitive_nMaxPrimitiveUsage = (unsigned int)Primitive_ptNextFreePrimitive - Primitive_asPrimitive[0];
    if ( (char *)Primitive_ptNextFreePrimitive - Primitive_asPrimitive[0] > (char *)dword_6B9E3C )
      v1 = nullptr;
  }
  v2 = HandiCamFilter_ePrimType;
  v1[1] = HandiCamFilter_ePrimType;
  v1[3] = ptQTask;
  RenderMode_tActiveRenderMode.apfRenderModeMethod[v2](v1);
  dword_834E068 = (int)v1;
  sprintf(
    igi2_frame.Buffer,
    "%2.2d : %2.2d : %2.2d : %2.2d",
    (int)(__int64)HandiCamFilter_vCounterFrames / 24 / 60 % 60 / 60,
    (int)(__int64)HandiCamFilter_vCounterFrames / 24 / 60 % 60,
    (int)(__int64)HandiCamFilter_vCounterFrames / 24 % 60,
    (int)(__int64)HandiCamFilter_vCounterFrames % 24);
  igi2_frame.nY = (float)(int)(__int64)(RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHeight * 0.800000011920929
                           + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vY
                           - (double)HandiCamFilter_nCounterYOffset);
  igi2_frame.nX = (float)(int)(__int64)(RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vWidth * 0.8999999761581421
                           + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX
                           - (double)HandiCamFilter_nCounterXOffset);
  v4 = Text_New((struct QSprite_s *)ptQTask[1].tQTaskChildren.ptTail, igi2_frame.nX, igi2_frame.nY, igi2_frame.Buffer);
  nPri = v4->nPri;
  v6 = v4->bQGraphicFlags | 0x40000;
  v4->bQGraphicFlags = v6;
  igi2_frame.v9 = nPri;
  vA = v4->vA;
  v4->vR = 100.0;
  v4->vG = 100.0;
  v4->vB = 100.0;
  ptQTaskb = ptQTask[1].tQTaskChildren.ptMiddle;
  v4->vZ = *(float *)&ptQTaskb;
  QTilemap_Register(v4->ptQTilemap, v4->vX, v4->vY, 100.0, 100.0, 100.0, vA, *(float *)&ptQTaskb, v6 | 0x40000000, igi2_frame.v9);
  Text_Delete(v4);
  ptQTaska = 0.0;
  if ( *(float *)&ptQTask[2].ptPrev >= 0.75 )
    ptQTaska = 1.0;
  v8 = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vWidth * 0.07000000029802322;
  igi2_frame.ptQSprite = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vWidth * 0.10000000149011612
            + (double)HandiCamFilter_nBatteryXOffset
            + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX;
  igi2_frame.vX3 = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHeight * 0.20000000298023224
      + (double)HandiCamFilter_nBatteryYOffset
      + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vY;
  igi2_frame.vX1 = (double)SHIWORD(ptQTask[1].tQTaskRefList.ptTail[3 * LOWORD(ptQTask[2].ptNext) + 1].ptNext)
      / (double)SLOWORD(ptQTask[1].tQTaskRefList.ptTail[3 * LOWORD(ptQTask[2].ptNext) + 1].ptNext)
      * v8
      + igi2_frame.vX3;
  igi2_frame.vY1 = igi2_frame.ptQSprite + v8;
  QSprite_Register4AZ(
    (struct QSprite_s *)&ptQTask[1].tQTaskRefList,
    igi2_frame.ptQSprite,
    igi2_frame.vX1,
    igi2_frame.vY1,
    igi2_frame.vX1,
    igi2_frame.ptQSprite,
    igi2_frame.vX3,
    igi2_frame.vY1,
    igi2_frame.vX3,
    128.0,
    128.0,
    128.0,
    ptQTaska,
    *(float *)&ptQTask[1].tQTaskChildren.ptMiddle,
    0,
    (unsigned int)&MTP_atLODVirModel[49].atBoneVertexRefs[17].atVertexRefs[120],
    0);
}

// source: f/2/pc/pc_filter.c:2568  [size]
char *__cdecl HandiCamFilter_SetBatterySprite(
        char *zBatterySprite,
        int nXOffset,
        int nYOffset)
{
  HandiCamFilter_zBatterySprite = zBatterySprite;
  HandiCamFilter_nBatteryXOffset = nXOffset;
  HandiCamFilter_nBatteryYOffset = nYOffset;
  return zBatterySprite;
}

// source: f/2/pc/pc_filter.c:2585  [size]
char *__cdecl HandiCamFilter_SetCounterFont(
        char *zCounterFont,
        int nXOffset,
        int nYOffset)
{
  HandiCamFilter_zCounterFont = zCounterFont;
  HandiCamFilter_nCounterXOffset = nXOffset;
  HandiCamFilter_nCounterYOffset = nYOffset;
  return zCounterFont;
}

// source: f/2/pc/pc_filter.c:2604  [anchor-strings]
void __cdecl Filter_Open()
{
  #pragma pack(push, 1)
  union
  {
    struct { int pxContext; };
    struct { char igi2_o1[4]; void *v21; };
    char igi2_extent[8];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // ax
  unsigned __int16 v2; // ax
  unsigned __int16 v3; // ax
  unsigned __int16 v4; // ax
  unsigned __int16 v5; // bp
  int v6; // edi
  unsigned __int16 v7; // si
  unsigned __int16 v8; // bp
  unsigned __int16 v9; // bp
  int v10; // esi
  int v11; // edi
  int v12; // edx
  int v13; // ecx
  enum RenderMode_enum v14; // eax
  int v15; // ecx
  int v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // eax

  Symbol_Register(
    "CAMERAFILTER_TYPE_NONE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    nullptr,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "CAMERAFILTER_TYPE_LINE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)1,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "CAMERAFILTER_TYPE_BAND",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)2,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "CAMERAFILTER_TYPE_BAND_UPDATE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)3,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "CAMERAFILTER_TYPE_HANDICAM",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)4,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  BaseQTaskType = QTask_GetBaseQTaskType();
  LineFilter_eQTaskType = QTask_NewQTaskType("LineFilter", 64, BaseQTaskType, 0, 0);
  v1 = QTask_GetBaseQTaskType();
  WideScreenFilter_eQTaskType = QTask_NewQTaskType("WideScreenFilter", 76, v1, 0, 0);
  v2 = QTask_GetBaseQTaskType();
  BandFilter_eQTaskType = QTask_NewQTaskType("BandFilter", 132, v2, 0, 0);
  v3 = QTask_GetBaseQTaskType();
  v4 = QTask_NewQTaskType("HandiCamFilter", 92, v3, 0, 0);
  v5 = LineFilter_eQTaskType;
  v6 = Screen_eDrawQTaskEvent;
  v7 = v4;
  HandiCamFilter_eQTaskType = v4;
  QTask_LinkQTaskEventHandlerNoContextFn(LineFilter_eQTaskType, Screen_eDrawQTaskEvent, sub_54B570);
  QTask_LinkQTaskEventHandlerNoContextFn(v5, 1, (void (__cdecl *)(struct QTask_s *))LineFilter_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v5, 2, (void (__cdecl *)(struct QTask_s *))LineFilter_DeleteHandler);
  v8 = WideScreenFilter_eQTaskType;
  QTask_LinkQTaskEventHandlerNoContextFn(WideScreenFilter_eQTaskType, v6, WideScreenFilter_DrawHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v8, 1, (void (__cdecl *)(struct QTask_s *))WideScreenFilter_RunHandler);
  v9 = BandFilter_eQTaskType;
  QTask_LinkQTaskEventHandlerNoContextFn(BandFilter_eQTaskType, v6, BandFilter_DrawHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v9, 1, BandFilter_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v9, 2, BandFilter_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v7, v6, HandiCamFilter_DrawHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v7, 1, HandiCamFilter_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v7, 2, HandiCamFilter_DeleteHandler);
  v10 = 0;
  while ( RenderMode_atRenderModeMethod[v10].isAllocated )
  {
    if ( ++v10 >= 128 )
    {
      LDebug_Error("RenderMode: Failed to create new method '%s'", "DrawLineFilter");
      goto LABEL_5;
    }
  }
  RenderMode_atRenderModeMethod[v10].zName = "DrawLineFilter";
  RenderMode_atRenderModeMethod[v10].isAllocated = 1;
  LineFilter_eRenderModeMethod = v10;
  v11 = 0;
  while ( RenderMode_atRenderModeMethod[v11].isAllocated )
  {
    if ( ++v11 >= 128 )
    {
      LDebug_Error("RenderMode: Failed to create new method '%s'", "DrawBandFilter");
      goto LABEL_5;
    }
  }
  RenderMode_atRenderModeMethod[v11].zName = "DrawBandFilter";
  RenderMode_atRenderModeMethod[v11].isAllocated = 1;
  BandFilter_eRenderModeMethod = v11;
  v12 = 0;
  while ( RenderMode_atRenderModeMethod[v12].isAllocated )
  {
    if ( ++v12 >= 128 )
    {
      LDebug_Error("RenderMode: Failed to create new method '%s'", "DrawHandiCamFilter");
      goto LABEL_5;
    }
  }
  RenderMode_atRenderModeMethod[v12].zName = "DrawHandiCamFilter";
  RenderMode_atRenderModeMethod[v12].isAllocated = 1;
  HandiCamFilter_eRenderModeMethod = v12;
  v13 = 0;
  while ( RenderMode_atRenderModeMethod[v13].isAllocated )
  {
    if ( ++v13 >= 128 )
    {
      LDebug_Error("RenderMode: Failed to create new method '%s'", "DrawComputerFilter");
      goto LABEL_5;
    }
  }
  v14 = Direct3D_eRenderMode;
  RenderMode_atRenderMode[Direct3D_eRenderMode].apfRenderModeMethod[v10] = LineFilter_D3DDraw;
  RenderMode_atRenderMode[v14].apfRenderModeMethod[v11] = BandFilter_D3DDraw;
  RenderMode_atRenderModeMethod[v13].zName = "DrawComputerFilter";
  RenderMode_atRenderModeMethod[v13].isAllocated = 1;
  ComputerFilter_eRenderModeMethod = v13;
  RenderMode_atRenderMode[v14].apfRenderModeMethod[v12] = HandiCamFilter_D3DDraw;
  *((_DWORD *)&RenderMode_atRenderMode[0].apfRenderModeMethod[v13] + v14 * 130) = ComputerFilter_D3DDraw;
  v15 = 0;
  while ( RenderMode_atRenderModeMethod[v15].isAllocated )
  {
    if ( ++v15 >= 128 )
    {
      LDebug_Error("RenderMode: Failed to create new method '%s'", "LineFilter");
      goto LABEL_5;
    }
  }
  RenderMode_atRenderModeMethod[v15].zName = "LineFilter";
  RenderMode_atRenderModeMethod[v15].isAllocated = 1;
  LineFilter_ePrimType = v15;
  v16 = 0;
  while ( RenderMode_atRenderModeMethod[v16].isAllocated )
  {
    if ( ++v16 >= 128 )
    {
      LDebug_Error("RenderMode: Failed to create new method '%s'", "WideScreenFilter");
      goto LABEL_5;
    }
  }
  RenderMode_atRenderModeMethod[v16].zName = "WideScreenFilter";
  RenderMode_atRenderModeMethod[v16].isAllocated = 1;
  WideScreenFilter_ePrimType = v16;
  v17 = 0;
  while ( RenderMode_atRenderModeMethod[v17].isAllocated )
  {
    if ( ++v17 >= 128 )
    {
      LDebug_Error("RenderMode: Failed to create new method '%s'", "BandFilter");
      goto LABEL_5;
    }
  }
  RenderMode_atRenderModeMethod[v17].zName = "BandFilter";
  RenderMode_atRenderModeMethod[v17].isAllocated = 1;
  BandFilter_ePrimType = v17;
  v18 = 0;
  while ( RenderMode_atRenderModeMethod[v18].isAllocated )
  {
    if ( ++v18 >= 128 )
    {
      LDebug_Error("RenderMode: Failed to create new method '%s'", "HandiCamFilter");
      goto LABEL_5;
    }
  }
  RenderMode_atRenderModeMethod[v18].zName = "HandiCamFilter";
  RenderMode_atRenderModeMethod[v18].isAllocated = 1;
  HandiCamFilter_ePrimType = v18;
  v19 = 0;
  while ( RenderMode_atRenderModeMethod[v19].isAllocated )
  {
    if ( ++v19 >= 128 )
    {
      LDebug_Error("RenderMode: Failed to create new method '%s'", "ComputerFilter");
LABEL_5:
      abort();
    }
  }
  RenderMode_atRenderModeMethod[v19].isAllocated = 1;
  RenderMode_atRenderModeMethod[v19].zName = "ComputerFilter";
  ComputerFilter_ePrimType = v19;
  igi2_frame.pxContext = v15;
  igi2_frame.v21 = LineFilter_DrawPrim;
  RenderMode_EnumerateRenderModes(
    (void (__cdecl *)(struct RenderModeEnumerateContext_s *, void *))Primitive_SetPrimitiveDrawCallback,
    &igi2_frame.pxContext);
  igi2_frame.pxContext = WideScreenFilter_ePrimType;
  igi2_frame.v21 = WideScreenFilter_DrawPrim;
  RenderMode_EnumerateRenderModes(
    (void (__cdecl *)(struct RenderModeEnumerateContext_s *, void *))Primitive_SetPrimitiveDrawCallback,
    &igi2_frame.pxContext);
  igi2_frame.pxContext = BandFilter_ePrimType;
  igi2_frame.v21 = BandFilter_DrawPrim;
  RenderMode_EnumerateRenderModes(
    (void (__cdecl *)(struct RenderModeEnumerateContext_s *, void *))Primitive_SetPrimitiveDrawCallback,
    &igi2_frame.pxContext);
  igi2_frame.pxContext = HandiCamFilter_ePrimType;
  igi2_frame.v21 = HandiCamFilter_DrawPrim;
  RenderMode_EnumerateRenderModes(
    (void (__cdecl *)(struct RenderModeEnumerateContext_s *, void *))Primitive_SetPrimitiveDrawCallback,
    &igi2_frame.pxContext);
  igi2_frame.pxContext = ComputerFilter_ePrimType;
  igi2_frame.v21 = ComputerFilter_DrawPrim;
  RenderMode_EnumerateRenderModes(
    (void (__cdecl *)(struct RenderModeEnumerateContext_s *, void *))Primitive_SetPrimitiveDrawCallback,
    &igi2_frame.pxContext);
  Filter_tRandomState.anRandom[2] = 2120272633;
  Filter_tRandomState.anRandom[1] = 1200274863;
  Filter_tRandomState.anRandom[0] = 277206966;
  HandiCamFilter_vCounterFrames = 18200.609375;
}

// source: f/2/pc/pc_filter.c:2674  [anchor-hash]
void __cdecl Filter_Close()
{
  int v0; // edx
  int v1; // ecx
  int v2; // edx
  int v3; // ecx
  int v4; // edx
  int v5; // ecx
  int v6; // edx
  int v7; // ecx

  v0 = BandFilter_ePrimType;
  RenderMode_atRenderModeMethod[HandiCamFilter_ePrimType].isAllocated = 0;
  v1 = WideScreenFilter_ePrimType;
  RenderMode_atRenderModeMethod[v0].isAllocated = 0;
  v2 = LineFilter_ePrimType;
  RenderMode_atRenderModeMethod[v1].isAllocated = 0;
  v3 = ComputerFilter_ePrimType;
  RenderMode_atRenderModeMethod[v2].isAllocated = 0;
  v4 = HandiCamFilter_eRenderModeMethod;
  RenderMode_atRenderModeMethod[v3].isAllocated = 0;
  v5 = BandFilter_eRenderModeMethod;
  RenderMode_atRenderModeMethod[v4].isAllocated = 0;
  v6 = LineFilter_eRenderModeMethod;
  RenderMode_atRenderModeMethod[v5].isAllocated = 0;
  v7 = ComputerFilter_eRenderModeMethod;
  RenderMode_atRenderModeMethod[v6].isAllocated = 0;
  RenderMode_atRenderModeMethod[v7].isAllocated = 0;
  QTask_DeleteQTaskType(HandiCamFilter_eQTaskType);
  QTask_DeleteQTaskType(BandFilter_eQTaskType);
  QTask_DeleteQTaskType(WideScreenFilter_eQTaskType);
  QTask_DeleteQTaskType(LineFilter_eQTaskType);
}

// source: f/2/pc/pc_filter.c:2704  [size]
void __cdecl LineFilter_SetNoise(struct QTask_s *ptLineFilterQTask, float vNoise)
{
  *(float *)&ptLineFilterQTask[1].tQTaskChildren.ptTail = vNoise;
}

// source: f/2/pc/pc_filter.c:2723  [size]
void __cdecl WideScreenFilter_SetBorderSize(struct QTask_s *ptQTask, float vBorderSize)
{
  *(float *)&ptQTask[1].ptParent = vBorderSize;
}

void __cdecl sub_54E6F0(struct QTask_s *a1, void *a2)
{
  a1[1].ptPrev = (struct QTask_s *)1065353216;
  a1[1].tQTaskChildren.ptHead = (struct QTask_s *)&g_zInitialValue;
  a1[1].tQTaskChildren.ptMiddle = nullptr;
  a1[1].ptNext = (struct QTask_s *)1;
}
