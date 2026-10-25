/* e/3/pc/pc_direct3drender.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: e/3/pc/pc_direct3drender.c:570  [size]
void __cdecl Direct3DRender_SetRenderingDefaults()
{
  #pragma pack(push, 1)
  union
  {
    struct { float vLodBias; };
    struct { char igi2_o1[4]; float vFogStart; };
    struct { char igi2_o2[8]; float vFogEnd; };
    struct { char igi2_o3[12]; float vFogDensity; };
    char igi2_extent[16];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  signed int i; // esi
  struct RenderStateBlock_t *v1; // eax
  struct RenderStateBlock_t *v2; // ecx
  struct RenderStateBlock_t *v3; // edx

  igi2_frame.vLodBias = 0.0;
  igi2_frame.vFogStart = 0.0;
  igi2_frame.vFogEnd = 1.0;
  igi2_frame.vFogDensity = 1.0;
  for ( i = 0; i < 8; ++i )
  {
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, i, D3DTSS_COLOROP, i != 0 ? 1 : 4);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, i, D3DTSS_COLORARG1, 2u);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, i, D3DTSS_COLORARG2, 1u);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, i, D3DTSS_ALPHAOP, (i == 0) + 1);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, i, D3DTSS_ALPHAARG1, 2u);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, i, D3DTSS_ALPHAARG2, 1u);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, i, D3DTSS_BUMPENVMAT01, 0);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, i, D3DTSS_BUMPENVMAT01, 0);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, i, D3DTSS_BUMPENVMAT11, 0);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, i, D3DTSS_BUMPENVMAT11, 0);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, i, D3DTSS_TEXCOORDINDEX, i);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, i, D3DTSS_ADDRESSU, 1u);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, i, D3DTSS_ADDRESSV, 1u);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, i, D3DTSS_BORDERCOLOR, 0);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, i, D3DTSS_MAGFILTER, 1u);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, i, D3DTSS_MINFILTER, 1u);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, i, D3DTSS_MIPFILTER, 0);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, i, D3DTSS_MIPMAPLODBIAS, (unsigned int)&igi2_frame.vLodBias);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, i, D3DTSS_MAXMIPLEVEL, 0);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, i, D3DTSS_MAXANISOTROPY, 1u);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, i, D3DTSS_BUMPENVLSCALE, 0);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, i, D3DTSS_BUMPENVLOFFSET, 0);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, i, D3DTSS_TEXTURETRANSFORMFLAGS, 0);
  }
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_MULTISAMPLEANTIALIAS, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FILLMODE, 3u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SHADEMODE, 2u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_LINEPATTERN, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZWRITEENABLE, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHATESTENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_LASTPIXEL, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SRCBLEND, 2u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_DESTBLEND, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_CULLMODE, 3u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZFUNC, 4u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHAREF, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHAFUNC, 8u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_DITHERENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHABLENDENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SPECULARENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGCOLOR, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGTABLEMODE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGSTART, (unsigned int)&igi2_frame.vFogStart);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGEND, (unsigned int)&igi2_frame.vFogEnd);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGDENSITY, (unsigned int)&igi2_frame.vFogDensity);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_EDGEANTIALIAS, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZBIAS, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_RANGEFOGENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_STENCILENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_STENCILFAIL, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_STENCILZFAIL, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_STENCILPASS, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_STENCILFUNC, 8u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_STENCILREF, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_STENCILMASK, -1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_STENCILWRITEMASK, -1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_TEXTUREFACTOR, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_WRAP0, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_WRAP1, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_WRAP2, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_WRAP3, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_WRAP4, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_WRAP5, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_WRAP6, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_WRAP7, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_CLIPPING, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_LIGHTING, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_AMBIENT, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGVERTEXMODE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_COLORVERTEX, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_LOCALVIEWER, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_NORMALIZENORMALS, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_DIFFUSEMATERIALSOURCE, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SPECULARMATERIALSOURCE, 2u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_AMBIENTMATERIALSOURCE, 2u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_EMISSIVEMATERIALSOURCE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_VERTEXBLEND, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_CLIPPLANEENABLE, 0);
  v1 = Direct3D_ptTextureStateBlock;
  v2 = Direct3D_ptBlendStateBlock;
  Direct3D_ptGenericStateBlock->eCurrentState = -1;
  v3 = Direct3D_ptClippingStateBlock;
  v1->eCurrentState = -1;
  v2->eCurrentState = -1;
  v3->eCurrentState = -1;
}

// source: e/3/pc/pc_direct3drender.c:687  [size]
enum Direct3DRender_VBType_e __cdecl Direct3DRender_FlushQueue(enum Direct3DRender_VBType_e eVBType)
{
  #pragma pack(push, 1)
  union
  {
    struct { unsigned int v18; };
    struct { char igi2_o1[28]; int iStartVertex; };
    struct { char igi2_o2[32]; unsigned __int8 *ptVertex; };
    struct { char igi2_o3[36]; int iRequest; };
    struct { char igi2_o4[40]; struct Direct3DRender_VertexData_s *ptVertexData; };
    struct { char igi2_o5[44]; struct _D3DVERTEXBUFFER_DESC tVBDesc; };
    char igi2_extent[68];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  __int32 v1; // ebp
  unsigned int v2; // esi
  struct Direct3DRender_VertexBuffer_t *v3; // ebx
  unsigned int v4; // edi
  struct IDirect3DDevice8Vtbl *lpVtbl; // edx
  int v6; // edi
  struct IDirect3DVertexBuffer8 *ptVertexBuffer; // eax
  bool v8; // cc
  struct Direct3DRender_VertexData_s *v9; // eax
  int v10; // esi
  struct Direct3DRender_VertexData_s *v11; // edx
  int v12; // ecx
  char *v13; // edx
  int v14; // ecx
  unsigned __int16 nNumVertices; // cx
  int v16; // ecx
  enum Direct3DRender_VBType_e result; // eax

  v1 = 8008 * eVBType + 128069944;
  v2 = Direct3DRender_anVBStride[eVBType] * Direct3dRender_atVBQueue[eVBType].nNumVertices;
  v3 = (struct Direct3DRender_VertexBuffer_t *)(44 * Direct3DRender_nNumVertexBuffers++ + 128094768);
  igi2_frame.iRequest = 4 * eVBType + 7015064;
  v4 = Direct3DRender_abVBQueueFlags[eVBType];
  igi2_frame.v18 = Direct3DRender_abVBQueueFVF[eVBType];
  igi2_frame.tVBDesc.Size = v2;
  igi2_frame.tVBDesc.FVF = igi2_frame.v18;
  igi2_frame.tVBDesc.Pool = D3DPOOL_DEFAULT;
  lpVtbl = Direct3D_ptDevice->lpVtbl;
  igi2_frame.tVBDesc.Usage = (Direct3D_isHWTnL != 0 ? 0 : 0x10) | v4;
  lpVtbl->CreateVertexBuffer(Direct3D_ptDevice, v2, igi2_frame.tVBDesc.Usage, igi2_frame.v18, D3DPOOL_DEFAULT, &v3->ptVertexBuffer);
  qmemcpy(&v3->tVBDesc, &igi2_frame.tVBDesc, sizeof(v3->tVBDesc));
  v6 = 0;
  v3->nVertexSize = *(_DWORD *)igi2_frame.iRequest;
  v3->tVertexDataList.ptHead = (struct Direct3DRender_VertexData_s *)&v3->tVertexDataList.ptMiddle;
  v3->tVertexDataList.ptMiddle = nullptr;
  v3->tVertexDataList.ptTail = (struct Direct3DRender_VertexData_s *)&v3->tVertexDataList;
  ptVertexBuffer = v3->ptVertexBuffer;
  igi2_frame.ptVertex = nullptr;
  igi2_frame.iStartVertex = 0;
  ptVertexBuffer->lpVtbl->Lock(ptVertexBuffer, 0, 0, &igi2_frame.ptVertex, 0);
  v8 = (int)(*(_DWORD *)(v1 + 8004)) <= 0;
  igi2_frame.iRequest = 0;
  if ( !v8 )
  {
    v9 = igi2_frame.ptVertexData;
    do
    {
      v10 = *(_DWORD *)(v1 + 4 * v6);
      v11 = *(struct Direct3DRender_VertexData_s **)(v10 + 32);
      v12 = *(_DWORD *)(v1 + 4 * v6 + 4000);
      igi2_frame.ptVertexData = v11;
      if ( v11 )
      {
        v13 = (char *)&v11[-1].nVertexSize + 3;
        if ( !v13 )
          goto LABEL_9;
        if ( v13 != (char *)2 )
        {
          LDebug_Error("Mesh format not supported");
          abort();
        }
        v14 = *(_DWORD *)(*(_DWORD *)(v10 + 36) + 36) + 28 * v12;
      }
      else
      {
        v14 = *(_DWORD *)(*(_DWORD *)(v10 + 36) + 28) + 28 * v12;
      }
      v9 = (struct Direct3DRender_VertexData_s *)v14;
LABEL_9:
      if ( !igi2_frame.ptVertexData || igi2_frame.ptVertexData == (struct Direct3DRender_VertexData_s *)3 )
      {
        v9->iStartVertex = igi2_frame.iStartVertex;
        nNumVertices = v9->nNumVertices;
        v9->ptVertexBuffer = v3;
        v9->isInitialized = 1;
        if ( nNumVertices )
        {
          qmemcpy(&igi2_frame.ptVertex[igi2_frame.iStartVertex * v3->nVertexSize], v9->pxSource, nNumVertices * v9->nVertexSize);
          v9->ptPrev = nullptr;
          v9->ptNext = nullptr;
          v9 = (struct Direct3DRender_VertexData_s *)List_AddTail(v9, (int)&v3->tVertexDataList);
          v6 = igi2_frame.iRequest;
          igi2_frame.iStartVertex += v9->nNumVertices;
        }
      }
      v16 = *(_DWORD *)(v1 + 8004);
      igi2_frame.iRequest = ++v6;
    }
    while ( v6 < v16 );
  }
  result = v3->ptVertexBuffer->lpVtbl->Unlock(v3->ptVertexBuffer);
  *(_DWORD *)(v1 + 8004) = 0;
  *(_DWORD *)(v1 + 8000) = 0;
  return result;
}

// source: e/3/pc/pc_direct3drender.c:831  [size]
int __cdecl Direct3DRender_RequestVertexData(
        enum Direct3DRender_VBType_e eVBType,
        void *ptMesh,
        int nNumVertices,
        int iMeshIndex)
{
  int result; // eax
  int v5; // edx

  if ( nNumVertices + Direct3dRender_atVBQueue[eVBType].nNumVertices > 0xFFFF )
    Direct3DRender_FlushQueue(eVBType);
  Direct3dRender_atVBQueue[eVBType].aptRequest[Direct3dRender_atVBQueue[eVBType].nNumRequests] = ptMesh;
  Direct3dRender_atVBQueue[eVBType].aiRequestMesh[Direct3dRender_atVBQueue[eVBType].nNumRequests] = iMeshIndex;
  result = Direct3dRender_atVBQueue[eVBType].nNumRequests + 1;
  v5 = nNumVertices + Direct3dRender_atVBQueue[eVBType].nNumVertices;
  Direct3dRender_atVBQueue[eVBType].nNumRequests = result;
  Direct3dRender_atVBQueue[eVBType].nNumVertices = v5;
  if ( result == 1000 )
    return Direct3DRender_FlushQueue(eVBType);
  return result;
}

// source: e/3/pc/pc_direct3drender.c:872  [size]
int __cdecl Direct3DRender_CreateIndexData(
        struct Direct3DRender_IndexData_s *ptIndexData,
        unsigned __int16 *piIndex,
        int nNumIndices)
{
  unsigned __int16 *v3; // ecx
  unsigned int v4; // esi
  unsigned __int16 *piLocked; // [esp+2Ch] [ebp-4h] BYREF

  piLocked = v3;
  if ( nNumIndices > 0 )
  {
    v4 = 2 * nNumIndices;
    nNumIndices = Direct3D_ptDevice->lpVtbl->CreateIndexBuffer(
                    Direct3D_ptDevice,
                    2 * nNumIndices,
                    8u,
                    D3DFMT_INDEX16,
                    D3DPOOL_MANAGED,
                    (struct IDirect3DIndexBuffer8 **)ptIndexData);
    if ( !nNumIndices )
    {
      ptIndexData->ptIndexBuffer->lpVtbl->Lock(ptIndexData->ptIndexBuffer, 0, 0, (unsigned __int8 **)&piLocked, 0);
      qmemcpy(piLocked, piIndex, v4);
      return ptIndexData->ptIndexBuffer->lpVtbl->Unlock(ptIndexData->ptIndexBuffer);
    }
  }
  return nNumIndices;
}

// source: e/3/pc/pc_direct3drender.c:917  [size]
struct Direct3DRender_IndexData_s *__cdecl Direct3DRender_ReleaseIndexData(
        struct Direct3DRender_IndexData_s *ptIndexData)
{
  struct Direct3DRender_IndexData_s *v1; // ebx
  unsigned __int16 *paiVertex; // eax
  int v3; // esi

  v1 = ptIndexData;
  if ( ptIndexData->ptIndexBuffer )
  {
    paiVertex = ptIndexData->paiVertex;
    if ( paiVertex )
    {
      v3 = *(_DWORD *)((unsigned int)(paiVertex - 2) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v3);
      memset(*(void **)(v3 + 8), 0xCDu, *(_DWORD *)(v3 + 16));
      free((void *)v3);
      v1->paiVertex = nullptr;
    }
    return (struct Direct3DRender_IndexData_s *)v1->ptIndexBuffer->lpVtbl->Release(v1->ptIndexBuffer);
  }
  return ptIndexData;
}

// source: e/3/pc/pc_direct3drender.c:939  [size]
void __cdecl Direct3DRender_FreeEffectTexture(struct EffectTexture_t *ptTexture)
{
  struct TexInfo_s *p_tTexInfo; // edi

  if ( ptTexture->isTextureLoaded )
  {
    p_tTexInfo = &ptTexture->tTexInfo;
    if ( AppContext_tAppContext.isMainMenu == false )
      RenderMode_atRenderMode[p_tTexInfo->eRenderMode].apfRenderModeMethod[Texture_eDeAllocTextureMethod](&ptTexture->tTexInfo);
    memset(p_tTexInfo, 0, sizeof(struct TexInfo_s));
    ptTexture->isTextureLoaded = false;
  }
}

// source: e/3/pc/pc_direct3drender.c:956  [size]
struct EffectTexture_t *__cdecl Direct3DRender_LoadEffectTexture(struct EffectTexture_t *ptTexture)
{
  struct EffectTexture_t *result; // eax

  if ( ptTexture->isTextureLoaded )
    Direct3DRender_FreeEffectTexture(ptTexture);
  if ( Resource_IsLoadedInternal(ptTexture->zTextureFilename, nullptr)
    || (result = (struct EffectTexture_t *)File_Exists(ptTexture->zTextureFilename)) != nullptr )
  {
    result = (struct EffectTexture_t *)Texture_Load(&ptTexture->tTexInfo, nullptr, ptTexture->zTextureFilename);
    ptTexture->isTextureLoaded = true;
  }
  return result;
}

// source: e/3/pc/pc_direct3drender.c:982  [size]
void __cdecl Direct3DRender_LoadEffectTextures()
{
  Direct3DRender_LoadEffectTexture(&tInfraHumanTexture);
  Direct3DRender_LoadEffectTexture(&tGlowTexture);
  Direct3DRender_LoadEffectTexture(&tWaterExplosionTexture);
  Direct3DRender_LoadEffectTexture(atLineFilterTexture);
  Direct3DRender_LoadEffectTexture(&atLineFilterTexture[1]);
  Direct3DRender_LoadEffectTexture(&atLineFilterTexture[2]);
  Direct3DRender_LoadEffectTexture(&atLineFilterTexture[3]);
}

// source: e/3/pc/pc_direct3drender.c:1001  [size]
void __cdecl Direct3DRender_FreeEffectTextures()
{
  if ( tInfraHumanTexture.isTextureLoaded )
  {
    if ( AppContext_tAppContext.isMainMenu == false )
      RenderMode_atRenderMode[tInfraHumanTexture.tTexInfo.eRenderMode].apfRenderModeMethod[Texture_eDeAllocTextureMethod](&tInfraHumanTexture.tTexInfo);
    memset(&tInfraHumanTexture.tTexInfo, 0, sizeof(tInfraHumanTexture.tTexInfo));
    tInfraHumanTexture.isTextureLoaded = false;
  }
  if ( tGlowTexture.isTextureLoaded )
  {
    if ( AppContext_tAppContext.isMainMenu == false )
      RenderMode_atRenderMode[tGlowTexture.tTexInfo.eRenderMode].apfRenderModeMethod[Texture_eDeAllocTextureMethod](&tGlowTexture.tTexInfo);
    memset(&tGlowTexture.tTexInfo, 0, sizeof(tGlowTexture.tTexInfo));
    tGlowTexture.isTextureLoaded = false;
  }
  if ( tWaterExplosionTexture.isTextureLoaded )
  {
    if ( AppContext_tAppContext.isMainMenu == false )
      RenderMode_atRenderMode[tWaterExplosionTexture.tTexInfo.eRenderMode].apfRenderModeMethod[Texture_eDeAllocTextureMethod](&tWaterExplosionTexture.tTexInfo);
    memset(&tWaterExplosionTexture.tTexInfo, 0, sizeof(tWaterExplosionTexture.tTexInfo));
    tWaterExplosionTexture.isTextureLoaded = false;
  }
  if ( atLineFilterTexture[0].isTextureLoaded )
  {
    if ( AppContext_tAppContext.isMainMenu == false )
      RenderMode_atRenderMode[atLineFilterTexture[0].tTexInfo.eRenderMode].apfRenderModeMethod[Texture_eDeAllocTextureMethod](&atLineFilterTexture[0].tTexInfo);
    memset(&atLineFilterTexture[0].tTexInfo, 0, sizeof(atLineFilterTexture[0].tTexInfo));
    atLineFilterTexture[0].isTextureLoaded = false;
  }
  if ( atLineFilterTexture[1].isTextureLoaded )
  {
    if ( AppContext_tAppContext.isMainMenu == false )
      RenderMode_atRenderMode[atLineFilterTexture[1].tTexInfo.eRenderMode].apfRenderModeMethod[Texture_eDeAllocTextureMethod](&atLineFilterTexture[1].tTexInfo);
    memset(&atLineFilterTexture[1].tTexInfo, 0, sizeof(atLineFilterTexture[1].tTexInfo));
    atLineFilterTexture[1].isTextureLoaded = false;
  }
  if ( atLineFilterTexture[2].isTextureLoaded )
  {
    if ( AppContext_tAppContext.isMainMenu == false )
      RenderMode_atRenderMode[atLineFilterTexture[2].tTexInfo.eRenderMode].apfRenderModeMethod[Texture_eDeAllocTextureMethod](&atLineFilterTexture[2].tTexInfo);
    memset(&atLineFilterTexture[2].tTexInfo, 0, sizeof(atLineFilterTexture[2].tTexInfo));
    atLineFilterTexture[2].isTextureLoaded = false;
  }
  if ( atLineFilterTexture[3].isTextureLoaded )
  {
    if ( AppContext_tAppContext.isMainMenu == false )
      RenderMode_atRenderMode[atLineFilterTexture[3].tTexInfo.eRenderMode].apfRenderModeMethod[Texture_eDeAllocTextureMethod](&atLineFilterTexture[3].tTexInfo);
    memset(&atLineFilterTexture[3].tTexInfo, 0, sizeof(atLineFilterTexture[3].tTexInfo));
    atLineFilterTexture[3].isTextureLoaded = false;
  }
}

// source: e/3/pc/pc_direct3drender.c:1023  [size]
void __cdecl Direct3DRender_CreateBoneRenderMesh(struct Direct3DRender_BoneMesh_t *ptMesh)
{
  struct Direct3DRender_BoneVertex_t *v1; // ebp
  unsigned int *v2; // edi
  struct Direct3DRender_BoneVertexData_t *ptVertexData; // eax
  int v4; // eax
  float *p_vZ; // ebp
  float *v6; // edx
  struct BoneDirect3D_Vertex_t *v7; // ecx
  int nNumVertices; // edi
  unsigned int v9; // edi
  struct BoneDirect3D_Vertex_t *ptUnprocessedVertex; // edx
  int v11; // esi
  int v12; // ecx
  int v13; // edx
  char v14; // cl
  struct Direct3DRender_BoneVertex_t *v15; // edx
  char v16; // cl
  int v17; // eax
  struct BoneDirect3D_Vertex_t *v18; // eax
  struct BoneDirect3D_Vertex_t *v19; // eax
  int v20; // edx
  int v21; // eax
  struct BoneDirect3D_Vertex_t *v22; // eax
  struct BoneDirect3D_Vertex_t *v23; // eax
  struct Direct3DRender_BoneVertex_t *ptNewVertex; // [esp+Ch] [ebp-18h]
  unsigned int ptNewVertexa; // [esp+Ch] [ebp-18h]
  int iVertex; // [esp+10h] [ebp-14h]
  int iVertexa; // [esp+10h] [ebp-14h]
  struct real32x3_t *ptBones; // [esp+14h] [ebp-10h]
  struct real32x3_t *ptBonesa; // [esp+14h] [ebp-10h]
  unsigned int ptBonesb; // [esp+14h] [ebp-10h]
  unsigned int *pbBoneCount; // [esp+18h] [ebp-Ch]
  __int64 nNewWeight; // [esp+1Ch] [ebp-8h]

  v1 = (struct Direct3DRender_BoneVertex_t *)Mem_AllocFn(40 * ptMesh->nNumVertices, 4);
  ptNewVertex = v1;
  v2 = (unsigned int *)Mem_AllocFn(4 * (ptMesh->nNumVertices / 16) + 4, 4);
  ptVertexData = ptMesh->ptVertexData;
  ptVertexData->ptVertex = v1;
  ptVertexData->pbBoneCount = v2;
  ptBones = ptMesh->ptVertexData->ptBones;
  pbBoneCount = v2;
  memset(v2, 0, 4 * (ptMesh->nNumVertices / 16) + 4);
  v4 = 0;
  iVertex = 0;
  if ( ptMesh->nNumVertices > 0 )
  {
    p_vZ = &v1->tVertex.tPos.vZ;
    do
    {
      v6 = p_vZ - 2;
      qmemcpy(p_vZ - 2, &ptMesh->ptVertexData->ptUnprocessedVertex[v4], 0x20u);
      p_vZ += 10;
      *v6 = ptBones[ptMesh->ptVertexData->ptUnprocessedVertex[v4].iBone].vX
          + ptMesh->ptVertexData->ptUnprocessedVertex[v4].tVertex.tPos.vX;
      *(p_vZ - 11) = ptBones[ptMesh->ptVertexData->ptUnprocessedVertex[v4].iBone].vY
                   + ptMesh->ptVertexData->ptUnprocessedVertex[v4].tVertex.tPos.vY;
      v7 = &ptMesh->ptVertexData->ptUnprocessedVertex[v4++];
      *(p_vZ - 10) = ptBones[v7->iBone].vZ + v7->tVertex.tPos.vZ;
      *((_DWORD *)p_vZ - 4) = LOBYTE(ptMesh->ptVertexData->ptUnprocessedVertex[v4 - 1].iBone);
      *((_DWORD *)p_vZ - 3) = (unsigned __int8)(__int64)(ptMesh->ptVertexData->ptUnprocessedVertex[v4 - 1].vWeight
                                                       * 255.0);
      ++iVertex;
    }
    while ( iVertex < ptMesh->nNumVertices );
    v1 = ptNewVertex;
  }
  nNumVertices = ptMesh->nNumVertices;
  iVertexa = nNumVertices;
  if ( nNumVertices < nNumVertices + ptMesh->nNumInfluenceVertices )
  {
    v9 = nNumVertices;
    do
    {
      ptUnprocessedVertex = ptMesh->ptVertexData->ptUnprocessedVertex;
      v11 = ptUnprocessedVertex[v9].iVertex;
      ptBonesa = &ptUnprocessedVertex[v9].tVertex.tPos;
      v12 = 2 * (v11 % 16);
      v13 = (pbBoneCount[v11 / 16] >> v12) & 3;
      if ( v13 == 3 )
      {
        v14 = 0;
        ptNewVertexa = 255;
        nNewWeight = (__int64)(ptBonesa[2].vZ * 255.0);
        v15 = &v1[v11];
        ptBonesb = v15->iWeights;
        if ( (unsigned __int8)ptBonesb != 255 )
          ptNewVertexa = (unsigned __int8)ptBonesb;
        if ( BYTE1(ptBonesb) < ptNewVertexa )
        {
          ptNewVertexa = BYTE1(ptBonesb);
          v14 = 1;
        }
        if ( BYTE2(ptBonesb) < ptNewVertexa )
        {
          ptNewVertexa = BYTE2(ptBonesb);
          v14 = 2;
        }
        if ( HIBYTE(ptBonesb) < ptNewVertexa )
        {
          ptNewVertexa = HIBYTE(ptBonesb);
          v14 = 3;
        }
        if ( ptNewVertexa > (unsigned int)nNewWeight )
          goto LABEL_20;
        v16 = 8 * v14;
        v17 = ~(255 << v16);
        v15->iBones &= v17;
        v1[ptMesh->ptVertexData->ptUnprocessedVertex[v9].iVertex].iWeights &= v17;
        v18 = &ptMesh->ptVertexData->ptUnprocessedVertex[v9];
        v1[v18->iVertex].iBones |= v18->iBone << v16;
        v19 = ptMesh->ptVertexData->ptUnprocessedVertex;
        v20 = v19[v9].iVertex;
        v21 = (__int64)(v19[v9].vWeight * 255.0);
      }
      else
      {
        pbBoneCount[v11 / 16] = ((v13 + 1) << v12) | pbBoneCount[v11 / 16] & ~(3 << v12);
        v22 = &ptMesh->ptVertexData->ptUnprocessedVertex[v9];
        v16 = 8 * v13 + 8;
        v1[v22->iVertex].iBones |= v22->iBone << v16;
        v23 = ptMesh->ptVertexData->ptUnprocessedVertex;
        v20 = v23[v9].iVertex;
        v21 = (__int64)(v23[v9].vWeight * 255.0);
      }
      v1[v20].iWeights |= (unsigned __int8)v21 << v16;
LABEL_20:
      ++v9;
      ++iVertexa;
    }
    while ( iVertexa < ptMesh->nNumVertices + ptMesh->nNumInfluenceVertices );
  }
}

// source: e/3/pc/pc_direct3drender.c:1120  [size]
struct Mesh3D_Mesh_t *__cdecl Direct3DRender_SetBoneTranslations(struct Mesh3D_Mesh_t *ptMesh)
{
  unsigned __int8 *v2; // ecx
  void *pxRenderMesh; // edi
  struct real32x3_t *ptBoneTranslations; // eax
  float *p_vX; // esi
  struct real32x3_t *v6; // ebp
  struct Mesh3D_Mesh_t *result; // eax
  int *p_nMonth; // edx
  int v9; // edi
  int *v10; // ecx
  double v11; // st7
  unsigned __int8 *pcHierarchy; // [esp+10h] [ebp-Ch]
  int iBone; // [esp+14h] [ebp-8h]
  struct BoneDirect3D_Vertex_t *ptOldVertexData; // [esp+18h] [ebp-4h]

  v2 = ptMesh->pcHierarchy;
  pxRenderMesh = ptMesh->pxRenderMesh;
  ptOldVertexData = *((struct BoneDirect3D_Vertex_t **)pxRenderMesh + 6);
  ptBoneTranslations = ptMesh->ptBoneTranslations;
  p_vX = &ptBoneTranslations[1].vX;
  v6 = ptBoneTranslations;
  pcHierarchy = v2;
  iBone = 1;
  *((_DWORD *)pxRenderMesh + 6) = Mem_AllocFn(16, 4);
  result = (struct Mesh3D_Mesh_t *)Mem_AllocFn(12 * ptMesh->nBones, 4);
  *(_DWORD *)(*((_DWORD *)pxRenderMesh + 6) + 8) = result;
  *(_DWORD *)(*((_DWORD *)pxRenderMesh + 6) + 4) = ptOldVertexData;
  *(struct real32x3_t *)&result->vVersion = *v6;
  if ( p_vX != (float *)v6 )
  {
    p_nMonth = &result->tTime.nMonth;
    do
    {
      v9 = *pcHierarchy++;
      if ( v9 )
      {
        v10 = &result->tTime.nMonth + 3 * iBone;
        iBone += v9;
        do
        {
          v10 += 3;
          v11 = *((float *)p_nMonth - 2) + *p_vX;
          p_vX += 3;
          --v9;
          *((float *)v10 - 5) = v11;
          *((float *)v10 - 4) = *(p_vX - 2) + *((float *)p_nMonth - 1);
          *((float *)v10 - 3) = *(p_vX - 1) + *(float *)p_nMonth;
        }
        while ( v9 );
      }
      ++v6;
      p_nMonth += 3;
    }
    while ( p_vX != (float *)v6 );
  }
  return result;
}

// source: e/3/pc/pc_direct3drender.c:1169  [size]
void __cdecl Direct3DRender_UpdateMeshLightmapUVs(struct Mesh3D_RenderMesh_LightmapDirect3D_t *ptMesh)
{
  #pragma pack(push, 1)
  union
  {
    struct { int nWidth; };
    struct { char igi2_o1[4]; int nHeight; };
    struct { char igi2_o2[8]; int iFacegroup; };
    struct { char igi2_o3[12]; enum _D3DFORMAT eFormat; };
    struct { char igi2_o4[16]; int nNumMipLevels; };
    struct { char igi2_o5[20]; int v14; };
    char igi2_extent[24];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int nNumFaceGroups; // eax
  int v2; // ebx
  struct LightmapDirect3D_Lightmap_t *v3; // edi
  struct LightmapDirect3D_FaceGroup_t *ptFaceGroup; // eax
  int iStartVertex; // edx
  int v6; // eax
  float *p_vY; // ecx
  int v8; // ecx

  nNumFaceGroups = ptMesh->nNumFaceGroups;
  v2 = 0;
  igi2_frame.iFacegroup = 0;
  if ( nNumFaceGroups > 0 )
  {
    do
    {
      v3 = &ptMesh->ptLightmap[ptMesh->ptFaceGroup[v2].iLightmap];
      igi2_frame.nWidth = v3->nWidth;
      igi2_frame.nHeight = v3->nHeight;
      igi2_frame.nNumMipLevels = 1;
      igi2_frame.eFormat = D3DFMT_A8R8G8B8;
      D3DXCheckTextureRequirements(
        (int)Direct3D_ptDevice,
        (int)&igi2_frame.nWidth,
        (int)&igi2_frame.nHeight,
        (int)&igi2_frame.nNumMipLevels,
        0,
        (int)&igi2_frame.eFormat,
        1);
      if ( igi2_frame.nWidth != v3->nWidth || igi2_frame.nHeight != v3->nHeight )
      {
        ptFaceGroup = ptMesh->ptFaceGroup;
        iStartVertex = ptFaceGroup[v2].iStartVertex;
        if ( iStartVertex < iStartVertex + ptFaceGroup[v2].nNumVertices )
        {
          v6 = iStartVertex;
          do
          {
            igi2_frame.v14 = v3->nWidth;
            ++iStartVertex;
            ptMesh->ptVertex[v6].tLightmapUV.vX = (double)igi2_frame.v14 / (double)igi2_frame.nWidth * ptMesh->ptVertex[v6].tLightmapUV.vX;
            igi2_frame.v14 = v3->nHeight;
            p_vY = &ptMesh->ptVertex[v6++].tLightmapUV.vY;
            *p_vY = (double)igi2_frame.v14 / (double)igi2_frame.nHeight * *p_vY;
          }
          while ( iStartVertex < ptMesh->ptFaceGroup[v2].iStartVertex + ptMesh->ptFaceGroup[v2].nNumVertices );
        }
      }
      v8 = ptMesh->nNumFaceGroups;
      ++v2;
      ++igi2_frame.iFacegroup;
    }
    while ( igi2_frame.iFacegroup < v8 );
  }
}

// source: e/3/pc/pc_direct3drender.c:1219  [size]
void __cdecl Direct3D_LoadModel(void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { _DWORD *pxLastFaceNode; };
    struct { char igi2_o1[4]; _DWORD *pxLastMaterialNode; };
    struct { char igi2_o2[8]; _DWORD *pxLastSphereNode; };
    struct { char igi2_o3[12]; _DWORD *pxLastVertexNode; };
    struct { char igi2_o4[16]; int iMesh; };
    struct { char igi2_o5[20]; struct Mesh3D_CollisionMesh_MultiMesh_t *ptMesh; };
    char igi2_extent[24];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v1; // ebp
  int v2; // eax
  int v3; // eax
  void *v4; // esi
  _DWORD *FirstChunk; // eax
  int v6; // ecx
  void *v7; // esi
  struct Mesh3D_RenderMesh_LightmapDirect3D_t *v8; // ebp
  _DWORD *v9; // eax
  int v10; // ecx
  void *v11; // esi
  _DWORD *v12; // eax
  int v13; // ecx
  void *v14; // esi
  _DWORD *v15; // eax
  int v16; // ecx
  void *v17; // ebx
  _DWORD *v18; // eax
  int v19; // ecx
  struct Direct3DRender_VertexData_s *v20; // eax
  struct Direct3DRender_IndexData_s *v21; // eax
  int nNumFaces; // eax
  unsigned __int16 *piIndex; // esi
  struct IDirect3DIndexBuffer8 **p_ptIndexBuffer; // ebp
  int v25; // eax
  unsigned int v26; // edi
  void *v27; // ebx
  _DWORD *v28; // eax
  int v29; // ecx
  void *v30; // esi
  struct Direct3DRender_BoneMesh_t *v31; // ebx
  _DWORD *v32; // eax
  int v33; // ecx
  void *v34; // esi
  _DWORD *v35; // eax
  int v36; // ecx
  void *v37; // esi
  _DWORD *v38; // eax
  int v39; // ecx
  int v40; // edx
  int v41; // eax
  float *v42; // ecx
  struct Direct3DRender_IndexData_s *v43; // eax
  int v44; // eax
  unsigned __int16 *v45; // esi
  struct IDirect3DIndexBuffer8 **v46; // ebx
  int v47; // eax
  unsigned int v48; // edi
  void *v49; // ebx
  _DWORD *v50; // eax
  int v51; // ecx
  void *v52; // esi
  int v53; // ebx
  _DWORD *v54; // eax
  int v55; // ecx
  void *v56; // esi
  _DWORD *v57; // eax
  int v58; // ecx
  void *v59; // esi
  _DWORD *v60; // eax
  int v61; // ecx
  int v62; // edx
  int v63; // eax
  float *v64; // ecx
  _DWORD *v65; // eax
  _DWORD *v66; // eax
  int v67; // esi
  void *v68; // edi
  bool v69; // zf
  void *v70; // esi
  _DWORD *v71; // ebp
  unsigned int v72; // edi
  void *v73; // eax
  _DWORD *v74; // edi
  int v75; // eax
  unsigned int v76; // esi
  int v77; // ecx
  unsigned int v78; // ecx
  unsigned int v79; // esi
  int v80; // ecx
  unsigned int v81; // ecx
  unsigned int v82; // esi
  int v83; // ecx
  unsigned int v84; // ecx
  unsigned int v85; // esi
  int v86; // ecx
  unsigned int v87; // ecx
  unsigned int v88; // esi
  int v89; // ecx
  unsigned int v90; // ecx
  _DWORD *v91; // eax
  int v92; // ecx
  int v93; // edx
  unsigned int v94; // edi
  unsigned int v95; // ecx
  int v96; // eax
  _DWORD *v97; // edx
  int v98; // edi
  struct MultiMesh_Mesh_t *v99; // edi
  int v100; // eax
  _DWORD *v101; // eax
  int v102; // ecx
  _DWORD *v103; // ebp
  int v104; // eax
  _DWORD *v105; // eax
  int v106; // ecx
  int v107; // eax
  _DWORD *v108; // eax
  int v109; // ecx
  int v110; // eax
  _DWORD *v111; // eax
  int v112; // ecx
  int v113; // edx
  unsigned int v114; // eax
  unsigned int v115; // ecx
  struct MultiMesh_Vertex_t *v116; // eax
  int v117; // ecx
  unsigned int v118; // eax
  unsigned int v119; // edx
  struct MultiMesh_Face_t *v120; // eax
  int v121; // ecx
  unsigned int v122; // eax
  unsigned int v123; // edx
  struct MultiMesh_Material_t *v124; // eax
  int v125; // ecx
  unsigned int v126; // eax
  unsigned int v127; // edx
  struct MultiMesh_Sphere_t *v128; // eax

  v1 = *(_DWORD *)pxContext;
  v2 = *(_DWORD *)(*(_DWORD *)pxContext + 32);
  if ( v2 )
  {
    v3 = v2 - 1;
    if ( v3 )
    {
      if ( v3 != 2 )
      {
        LDebug_Error("Mesh format not supported");
        goto LABEL_5;
      }
      v4 = *((void **)pxContext + 1);
      FirstChunk = ILF_GetFirstChunk(v4);
      if ( FirstChunk )
      {
        while ( *FirstChunk != 1380201284 )
        {
          v6 = FirstChunk[3];
          if ( v6 )
          {
            FirstChunk = (_DWORD *)((char *)FirstChunk + v6);
            if ( FirstChunk )
              continue;
          }
          goto LABEL_10;
        }
      }
      else
      {
LABEL_10:
        FirstChunk = nullptr;
      }
      *(_DWORD *)(v1 + 36) = ILF_GetChunkData(FirstChunk, v4);
      v7 = *((void **)pxContext + 1);
      v8 = *(struct Mesh3D_RenderMesh_LightmapDirect3D_t **)(*(_DWORD *)pxContext + 36);
      v9 = ILF_GetFirstChunk(v7);
      if ( v9 )
      {
        while ( *v9 != 1448236120 )
        {
          v10 = v9[3];
          if ( v10 )
          {
            v9 = (_DWORD *)((char *)v9 + v10);
            if ( v9 )
              continue;
          }
          goto LABEL_15;
        }
      }
      else
      {
LABEL_15:
        v9 = nullptr;
      }
      v8->ptVertex = (struct LightmapDirect3D_Vertex_t *)ILF_GetChunkData(v9, v7);
      v11 = *((void **)pxContext + 1);
      v12 = ILF_GetFirstChunk(v11);
      if ( v12 )
      {
        while ( *v12 != 1380273732 )
        {
          v13 = v12[3];
          if ( v13 )
          {
            v12 = (_DWORD *)((char *)v12 + v13);
            if ( v12 )
              continue;
          }
          goto LABEL_20;
        }
      }
      else
      {
LABEL_20:
        v12 = nullptr;
      }
      v8->ptFaceGroup = (struct LightmapDirect3D_FaceGroup_t *)ILF_GetChunkData(v12, v11);
      v14 = *((void **)pxContext + 1);
      v15 = ILF_GetFirstChunk(v14);
      if ( v15 )
      {
        while ( *v15 != 1178682181 )
        {
          v16 = v15[3];
          if ( v16 )
          {
            v15 = (_DWORD *)((char *)v15 + v16);
            if ( v15 )
              continue;
          }
          goto LABEL_25;
        }
      }
      else
      {
LABEL_25:
        v15 = nullptr;
      }
      v8->piIndex = (unsigned __int16 *)ILF_GetChunkData(v15, v14);
      v17 = *((void **)pxContext + 1);
      v18 = ILF_GetFirstChunk(v17);
      if ( v18 )
      {
        while ( *v18 != 1280593232 )
        {
          v19 = v18[3];
          if ( v19 )
          {
            v18 = (_DWORD *)((char *)v18 + v19);
            if ( v18 )
              continue;
          }
          goto LABEL_30;
        }
      }
      else
      {
LABEL_30:
        v18 = nullptr;
      }
      v8->ptLightmap = (struct LightmapDirect3D_Lightmap_t *)ILF_GetChunkData(v18, v17);
      v20 = (struct Direct3DRender_VertexData_s *)Mem_AllocFn(28, 4);
      v8->ptVertexData = v20;
      v20->isInitialized = 0;
      v20->pxSource = nullptr;
      v20->nNumVertices = v8->nNumVertices;
      v20->pxSource = v8->ptVertex;
      v20->nVertexSize = 28;
      v21 = (struct Direct3DRender_IndexData_s *)Mem_AllocFn(8, 4);
      v8->ptIndexData = v21;
      v21->paiVertex = nullptr;
      v21->ptIndexBuffer = nullptr;
      if ( AppContext_tAppContext.isMainMenu == false )
      {
        Direct3DRender_UpdateMeshLightmapUVs(v8);
        Direct3DRender_RequestVertexData(
          DIRECT3DRENDER_VBTYPE_RIGID_XYZNORMALTEX2,
          *(void **)pxContext,
          v8->nNumVertices,
          0);
        nNumFaces = v8->nNumFaces;
        piIndex = v8->piIndex;
        p_ptIndexBuffer = &v8->ptIndexData->ptIndexBuffer;
        v25 = 3 * nNumFaces;
        if ( v25 > 0 )
        {
          v26 = 2 * v25;
          if ( !Direct3D_ptDevice->lpVtbl->CreateIndexBuffer(
                  Direct3D_ptDevice,
                  2 * v25,
                  8u,
                  D3DFMT_INDEX16,
                  D3DPOOL_MANAGED,
                  p_ptIndexBuffer) )
          {
            (*p_ptIndexBuffer)->lpVtbl->Lock(*p_ptIndexBuffer, 0, 0, (unsigned __int8 **)&igi2_frame.iMesh, 0);
            qmemcpy((void *)igi2_frame.iMesh, piIndex, v26);
            (*p_ptIndexBuffer)->lpVtbl->Unlock(*p_ptIndexBuffer);
          }
        }
      }
    }
    else
    {
      v27 = *((void **)pxContext + 1);
      v28 = ILF_GetFirstChunk(v27);
      if ( v28 )
      {
        while ( *v28 != 1380201284 )
        {
          v29 = v28[3];
          if ( v29 )
          {
            v28 = (_DWORD *)((char *)v28 + v29);
            if ( v28 )
              continue;
          }
          goto LABEL_39;
        }
      }
      else
      {
LABEL_39:
        v28 = nullptr;
      }
      *(_DWORD *)(v1 + 36) = ILF_GetChunkData(v28, v27);
      v30 = *((void **)pxContext + 1);
      v31 = *(struct Direct3DRender_BoneMesh_t **)(*(_DWORD *)pxContext + 36);
      v32 = ILF_GetFirstChunk(v30);
      if ( v32 )
      {
        while ( *v32 != 1448236120 )
        {
          v33 = v32[3];
          if ( v33 )
          {
            v32 = (_DWORD *)((char *)v32 + v33);
            if ( v32 )
              continue;
          }
          goto LABEL_44;
        }
      }
      else
      {
LABEL_44:
        v32 = nullptr;
      }
      v31->ptVertexData = (struct Direct3DRender_BoneVertexData_t *)ILF_GetChunkData(v32, v30);
      v34 = *((void **)pxContext + 1);
      v35 = ILF_GetFirstChunk(v34);
      if ( v35 )
      {
        while ( *v35 != 1380273732 )
        {
          v36 = v35[3];
          if ( v36 )
          {
            v35 = (_DWORD *)((char *)v35 + v36);
            if ( v35 )
              continue;
          }
          goto LABEL_49;
        }
      }
      else
      {
LABEL_49:
        v35 = nullptr;
      }
      v31->ptFaceGroup = (struct RigidDirect3D_FaceGroup_t *)ILF_GetChunkData(v35, v34);
      v37 = *((void **)pxContext + 1);
      v38 = ILF_GetFirstChunk(v37);
      if ( v38 )
      {
        while ( *v38 != 1178682181 )
        {
          v39 = v38[3];
          if ( v39 )
          {
            v38 = (_DWORD *)((char *)v38 + v39);
            if ( v38 )
              continue;
          }
          goto LABEL_54;
        }
      }
      else
      {
LABEL_54:
        v38 = nullptr;
      }
      v31->piIndex = (unsigned __int16 *)ILF_GetChunkData(v38, v37);
      v40 = 0;
      if ( v31->nNumVertices > 0 )
      {
        v41 = 0;
        do
        {
          ++v40;
          *(float *)((char *)&v31->ptVertexData->pbBoneCount + v41 * 4) = Direct3D_vScale
                                                                        * *(float *)((char *)&v31->ptVertexData->pbBoneCount
                                                                                   + v41 * 4);
          *(float *)&(&v31->ptVertexData[1].ptVertex)[v41] = Direct3D_vScale
                                                           * *(float *)&(&v31->ptVertexData[1].ptVertex)[v41];
          v42 = (float *)&(&v31->ptVertexData[1].ptUnprocessedVertex)[v41];
          v41 += 10;
          *v42 = Direct3D_vScale * *v42;
        }
        while ( v40 < v31->nNumVertices );
      }
      Direct3DRender_SetBoneTranslations(*(struct Mesh3D_Mesh_t **)pxContext);
      Direct3DRender_CreateBoneRenderMesh(v31);
      v43 = (struct Direct3DRender_IndexData_s *)Mem_AllocFn(8, 4);
      v31->ptIndexData = v43;
      v43->paiVertex = nullptr;
      v43->ptIndexBuffer = nullptr;
      if ( AppContext_tAppContext.isMainMenu == false )
      {
        v44 = v31->nNumFaces;
        v45 = v31->piIndex;
        v46 = &v31->ptIndexData->ptIndexBuffer;
        v47 = 3 * v44;
        if ( v47 > 0 )
        {
          v48 = 2 * v47;
          if ( !Direct3D_ptDevice->lpVtbl->CreateIndexBuffer(
                  Direct3D_ptDevice,
                  2 * v47,
                  8u,
                  D3DFMT_INDEX16,
                  D3DPOOL_MANAGED,
                  v46) )
          {
            (*v46)->lpVtbl->Lock(*v46, 0, 0, (unsigned __int8 **)&igi2_frame.iMesh, 0);
            qmemcpy((void *)igi2_frame.iMesh, v45, v48);
            (*v46)->lpVtbl->Unlock(*v46);
          }
        }
      }
    }
  }
  else
  {
    v49 = *((void **)pxContext + 1);
    v50 = ILF_GetFirstChunk(v49);
    if ( v50 )
    {
      while ( *v50 != 1380201284 )
      {
        v51 = v50[3];
        if ( v51 )
        {
          v50 = (_DWORD *)((char *)v50 + v51);
          if ( v50 )
            continue;
        }
        goto LABEL_66;
      }
    }
    else
    {
LABEL_66:
      v50 = nullptr;
    }
    *(_DWORD *)(v1 + 36) = ILF_GetChunkData(v50, v49);
    v52 = *((void **)pxContext + 1);
    v53 = *(_DWORD *)(*(_DWORD *)pxContext + 36);
    v54 = ILF_GetFirstChunk(v52);
    if ( v54 )
    {
      while ( *v54 != 1448236120 )
      {
        v55 = v54[3];
        if ( v55 )
        {
          v54 = (_DWORD *)((char *)v54 + v55);
          if ( v54 )
            continue;
        }
        goto LABEL_71;
      }
    }
    else
    {
LABEL_71:
      v54 = nullptr;
    }
    *(_DWORD *)(v53 + 16) = ILF_GetChunkData(v54, v52);
    v56 = *((void **)pxContext + 1);
    v57 = ILF_GetFirstChunk(v56);
    if ( v57 )
    {
      while ( *v57 != 1380273732 )
      {
        v58 = v57[3];
        if ( v58 )
        {
          v57 = (_DWORD *)((char *)v57 + v58);
          if ( v57 )
            continue;
        }
        goto LABEL_76;
      }
    }
    else
    {
LABEL_76:
      v57 = nullptr;
    }
    *(_DWORD *)(v53 + 24) = ILF_GetChunkData(v57, v56);
    v59 = *((void **)pxContext + 1);
    v60 = ILF_GetFirstChunk(v59);
    if ( v60 )
    {
      while ( *v60 != 1178682181 )
      {
        v61 = v60[3];
        if ( v61 )
        {
          v60 = (_DWORD *)((char *)v60 + v61);
          if ( v60 )
            continue;
        }
        goto LABEL_81;
      }
    }
    else
    {
LABEL_81:
      v60 = nullptr;
    }
    *(_DWORD *)(v53 + 20) = ILF_GetChunkData(v60, v59);
    v62 = 0;
    if ( *(int *)(v53 + 12) > 0 )
    {
      v63 = 0;
      do
      {
        ++v62;
        *(float *)(v63 + *(_DWORD *)(v53 + 16) + 12) = Direct3D_vScale * *(float *)(v63 + *(_DWORD *)(v53 + 16) + 12);
        *(float *)(v63 + *(_DWORD *)(v53 + 16) + 16) = Direct3D_vScale * *(float *)(v63 + *(_DWORD *)(v53 + 16) + 16);
        v64 = (float *)(v63 + *(_DWORD *)(v53 + 16) + 20);
        v63 += 32;
        *v64 = Direct3D_vScale * *v64;
      }
      while ( v62 < (int)(*(_DWORD *)(v53 + 12)) );
    }
    v65 = Mem_AllocFn(28, 4);
    *(_DWORD *)(v53 + 28) = v65;
    v65[2] = 0;
    v65[5] = 0;
    *((_WORD *)v65 + 7) = *(_WORD *)(v53 + 12);
    v65[5] = *(_DWORD *)(v53 + 16);
    v65[6] = 32;
    v66 = Mem_AllocFn(8, 4);
    *(_DWORD *)(v53 + 32) = v66;
    v66[1] = 0;
    *v66 = 0;
    if ( AppContext_tAppContext.isMainMenu == false )
    {
      v67 = *(_DWORD *)(v53 + 12);
      v68 = *(void **)pxContext;
      if ( v67 + Direct3dRender_atVBQueue[0].nNumVertices > 0xFFFF )
        Direct3DRender_FlushQueue(DIRECT3DRENDER_VBTYPE_RIGID_XYZNORMALTEX1);
      Direct3dRender_atVBQueue[0].aptRequest[Direct3dRender_atVBQueue[0].nNumRequests] = v68;
      Direct3dRender_atVBQueue[0].aiRequestMesh[Direct3dRender_atVBQueue[0].nNumRequests] = 0;
      v69 = Direct3dRender_atVBQueue[0].nNumRequests++ == 999;
      Direct3dRender_atVBQueue[0].nNumVertices += v67;
      if ( v69 )
        Direct3DRender_FlushQueue(DIRECT3DRENDER_VBTYPE_RIGID_XYZNORMALTEX1);
      v70 = *(void **)(v53 + 20);
      v71 = *(_DWORD **)(v53 + 32);
      if ( (int)(3 * *(_DWORD *)(v53 + 4)) > 0 )
      {
        v72 = 6 * *(_DWORD *)(v53 + 4);
        if ( !Direct3D_ptDevice->lpVtbl->CreateIndexBuffer(
                Direct3D_ptDevice,
                v72,
                8u,
                D3DFMT_INDEX16,
                D3DPOOL_MANAGED,
                *(struct IDirect3DIndexBuffer8 ***)(v53 + 32)) )
        {
          (*(void (__stdcall **)(_DWORD, _DWORD, _DWORD, int *, _DWORD))(*(_DWORD *)*v71 + 44))(*v71, 0, 0, &igi2_frame.iMesh, 0);
          qmemcpy((void *)igi2_frame.iMesh, v70, v72);
          (*(void (__stdcall **)(_DWORD))(*(_DWORD *)*v71 + 48))(*v71);
        }
      }
    }
    v73 = Mem_AllocFn(32 * *(_DWORD *)(v53 + 12), 16);
    qmemcpy(v73, *(void **)(v53 + 16), 32 * *(_DWORD *)(v53 + 12));
    *(_DWORD *)(v53 + 16) = v73;
  }
  v74 = *(_DWORD **)pxContext;
  if ( *(_DWORD *)(*(_DWORD *)pxContext + 40) )
  {
    LDebug_Error("Mesh format not supported");
LABEL_5:
    abort();
  }
  v75 = *((_DWORD *)pxContext + 1);
  if ( !v75 )
    goto LABEL_102;
  v76 = *(_DWORD *)(v75 + 4);
  if ( !v76 )
    goto LABEL_102;
  v77 = *(_DWORD *)(v75 + 8);
  if ( (v77 & ~(v77 - 1)) != v77 )
  {
    ILF_nLastError = 1;
    goto LABEL_102;
  }
  v78 = ~(v77 - 1) & (v77 + 19);
  if ( v78 >= v76 )
  {
LABEL_102:
    igi2_frame.pxLastVertexNode = nullptr;
    goto LABEL_103;
  }
  igi2_frame.pxLastVertexNode = (_DWORD *)(v75 + v78);
LABEL_103:
  if ( !v75 )
    goto LABEL_109;
  v79 = *(_DWORD *)(v75 + 4);
  if ( !v79 )
    goto LABEL_109;
  v80 = *(_DWORD *)(v75 + 8);
  if ( (v80 & ~(v80 - 1)) != v80 )
  {
    ILF_nLastError = 1;
    goto LABEL_109;
  }
  v81 = ~(v80 - 1) & (v80 + 19);
  if ( v81 >= v79 )
  {
LABEL_109:
    igi2_frame.pxLastFaceNode = nullptr;
    goto LABEL_110;
  }
  igi2_frame.pxLastFaceNode = (_DWORD *)(v75 + v81);
LABEL_110:
  if ( !v75 )
    goto LABEL_116;
  v82 = *(_DWORD *)(v75 + 4);
  if ( !v82 )
    goto LABEL_116;
  v83 = *(_DWORD *)(v75 + 8);
  if ( (v83 & ~(v83 - 1)) != v83 )
  {
    ILF_nLastError = 1;
    goto LABEL_116;
  }
  v84 = ~(v83 - 1) & (v83 + 19);
  if ( v84 >= v82 )
  {
LABEL_116:
    igi2_frame.pxLastMaterialNode = nullptr;
    goto LABEL_117;
  }
  igi2_frame.pxLastMaterialNode = (_DWORD *)(v75 + v84);
LABEL_117:
  if ( !v75 )
    goto LABEL_123;
  v85 = *(_DWORD *)(v75 + 4);
  if ( !v85 )
    goto LABEL_123;
  v86 = *(_DWORD *)(v75 + 8);
  if ( (v86 & ~(v86 - 1)) != v86 )
  {
    ILF_nLastError = 1;
    goto LABEL_123;
  }
  v87 = ~(v86 - 1) & (v86 + 19);
  if ( v87 >= v85 )
  {
LABEL_123:
    igi2_frame.pxLastSphereNode = nullptr;
    goto LABEL_124;
  }
  igi2_frame.pxLastSphereNode = (_DWORD *)(v75 + v87);
LABEL_124:
  if ( v75 )
  {
    v88 = *(_DWORD *)(v75 + 4);
    if ( v88 )
    {
      v89 = *(_DWORD *)(v75 + 8);
      if ( (v89 & ~(v89 - 1)) == v89 )
      {
        v90 = ~(v89 - 1) & (v89 + 19);
        if ( v90 < v88 )
        {
          v91 = (_DWORD *)(v90 + v75);
          goto LABEL_131;
        }
      }
      else
      {
        ILF_nLastError = 1;
      }
    }
  }
  v91 = nullptr;
LABEL_131:
  if ( v91 )
  {
    while ( *v91 != 1129141064 )
    {
      v92 = v91[3];
      if ( v92 )
      {
        v91 = (_DWORD *)((char *)v91 + v92);
        if ( v91 )
          continue;
      }
      goto LABEL_135;
    }
  }
  else
  {
LABEL_135:
    v91 = nullptr;
  }
  v74[11] = 0;
  if ( v91 )
  {
    v93 = *((_DWORD *)pxContext + 1);
    if ( v93 )
    {
      v94 = *(_DWORD *)(v93 + 8);
      if ( (v94 & ~(v94 - 1)) == v94
        && (unsigned int)v91 - v93 < *(_DWORD *)(v93 + 4)
        && (v95 = v91[2], (v95 & ~(v95 - 1)) == v95)
        && v95 <= v94 )
      {
        if ( v91[1] )
        {
          v96 = v93 + (((unsigned int)v91 + v95 - v93 + 15) & ~(v95 - 1));
LABEL_146:
          v97 = pxContext;
          *(_DWORD *)(*(_DWORD *)pxContext + 44) = v96;
          v98 = 0;
          igi2_frame.ptMesh = *(struct Mesh3D_CollisionMesh_MultiMesh_t **)(*(_DWORD *)pxContext + 44);
          igi2_frame.iMesh = 0;
          while ( 1 )
          {
            v99 = &igi2_frame.ptMesh->atMesh[v98];
            if ( igi2_frame.pxLastVertexNode && (v100 = igi2_frame.pxLastVertexNode[3]) != 0 )
              v101 = (_DWORD *)((char *)igi2_frame.pxLastVertexNode + v100);
            else
              v101 = nullptr;
            if ( v101 )
            {
              while ( *v101 != 1129731160 )
              {
                v102 = v101[3];
                if ( v102 )
                {
                  v101 = (_DWORD *)((char *)v101 + v102);
                  if ( v101 )
                    continue;
                }
                goto LABEL_156;
              }
              v103 = v101;
            }
            else
            {
LABEL_156:
              v103 = nullptr;
            }
            igi2_frame.pxLastVertexNode = v103;
            if ( igi2_frame.pxLastFaceNode && (v104 = igi2_frame.pxLastFaceNode[3]) != 0 )
              v105 = (_DWORD *)((char *)igi2_frame.pxLastFaceNode + v104);
            else
              v105 = nullptr;
            if ( v105 )
            {
              while ( *v105 != 1128678213 )
              {
                v106 = v105[3];
                if ( v106 )
                {
                  v105 = (_DWORD *)((char *)v105 + v106);
                  if ( v105 )
                    continue;
                }
                goto LABEL_166;
              }
              igi2_frame.pxLastFaceNode = v105;
            }
            else
            {
LABEL_166:
              igi2_frame.pxLastFaceNode = nullptr;
            }
            if ( igi2_frame.pxLastMaterialNode && (v107 = igi2_frame.pxLastMaterialNode[3]) != 0 )
              v108 = (_DWORD *)((char *)igi2_frame.pxLastMaterialNode + v107);
            else
              v108 = nullptr;
            if ( v108 )
            {
              while ( *v108 != 1129136468 )
              {
                v109 = v108[3];
                if ( v109 )
                {
                  v108 = (_DWORD *)((char *)v108 + v109);
                  if ( v108 )
                    continue;
                }
                goto LABEL_176;
              }
              igi2_frame.pxLastMaterialNode = v108;
            }
            else
            {
LABEL_176:
              igi2_frame.pxLastMaterialNode = nullptr;
            }
            if ( igi2_frame.pxLastSphereNode && (v110 = igi2_frame.pxLastSphereNode[3]) != 0 )
              v111 = (_DWORD *)((char *)igi2_frame.pxLastSphereNode + v110);
            else
              v111 = nullptr;
            if ( v111 )
            {
              while ( *v111 != 1129533512 )
              {
                v112 = v111[3];
                if ( v112 )
                {
                  v111 = (_DWORD *)((char *)v111 + v112);
                  if ( v111 )
                    continue;
                }
                goto LABEL_186;
              }
              igi2_frame.pxLastSphereNode = v111;
            }
            else
            {
LABEL_186:
              igi2_frame.pxLastSphereNode = nullptr;
            }
            v113 = v97[1];
            if ( !v113 || !v103 )
              goto LABEL_197;
            v114 = *(_DWORD *)(v113 + 8);
            if ( (v114 & ~(v114 - 1)) != v114 )
              break;
            if ( (unsigned int)v103 - v113 >= *(_DWORD *)(v113 + 4) )
              break;
            v115 = v103[2];
            if ( (v115 & ~(v115 - 1)) != v115 || v115 > v114 )
              break;
            if ( !v103[1] )
              goto LABEL_197;
            v116 = (struct MultiMesh_Vertex_t *)(v113 + (((unsigned int)v103 + v115 - v113 + 15) & ~(v115 - 1)));
LABEL_198:
            v99->ptVertex = v116;
            v117 = *((_DWORD *)pxContext + 1);
            if ( !v117 || !igi2_frame.pxLastFaceNode )
              goto LABEL_207;
            v118 = *(_DWORD *)(v117 + 8);
            if ( (v118 & ~(v118 - 1)) != v118
              || (unsigned int)igi2_frame.pxLastFaceNode - v117 >= *(_DWORD *)(v117 + 4)
              || (v119 = igi2_frame.pxLastFaceNode[2], (v119 & ~(v119 - 1)) != v119)
              || v119 > v118 )
            {
              ILF_nLastError = 1;
LABEL_207:
              v120 = nullptr;
              goto LABEL_208;
            }
            if ( !igi2_frame.pxLastFaceNode[1] )
              goto LABEL_207;
            v120 = (struct MultiMesh_Face_t *)(v117 + (((unsigned int)igi2_frame.pxLastFaceNode + v119 - v117 + 15) & ~(v119 - 1)));
LABEL_208:
            v99->ptFace = v120;
            v121 = *((_DWORD *)pxContext + 1);
            if ( !v121 || !igi2_frame.pxLastMaterialNode )
              goto LABEL_217;
            v122 = *(_DWORD *)(v121 + 8);
            if ( (v122 & ~(v122 - 1)) != v122
              || (unsigned int)igi2_frame.pxLastMaterialNode - v121 >= *(_DWORD *)(v121 + 4)
              || (v123 = igi2_frame.pxLastMaterialNode[2], (v123 & ~(v123 - 1)) != v123)
              || v123 > v122 )
            {
              ILF_nLastError = 1;
LABEL_217:
              v124 = nullptr;
              goto LABEL_218;
            }
            if ( !igi2_frame.pxLastMaterialNode[1] )
              goto LABEL_217;
            v124 = (struct MultiMesh_Material_t *)(v121
                                                 + (((unsigned int)igi2_frame.pxLastMaterialNode + v123 - v121 + 15) & ~(v123 - 1)));
LABEL_218:
            v99->ptMaterial = v124;
            v125 = *((_DWORD *)pxContext + 1);
            if ( v125 && igi2_frame.pxLastSphereNode )
            {
              v126 = *(_DWORD *)(v125 + 8);
              if ( (v126 & ~(v126 - 1)) == v126
                && (unsigned int)igi2_frame.pxLastSphereNode - v125 < *(_DWORD *)(v125 + 4)
                && (v127 = igi2_frame.pxLastSphereNode[2], (v127 & ~(v127 - 1)) == v127)
                && v127 <= v126 )
              {
                if ( igi2_frame.pxLastSphereNode[1] )
                {
                  v128 = (struct MultiMesh_Sphere_t *)(v125
                                                     + (((unsigned int)igi2_frame.pxLastSphereNode + v127 - v125 + 15) & ~(v127 - 1)));
                  goto LABEL_228;
                }
              }
              else
              {
                ILF_nLastError = 1;
              }
            }
            v128 = nullptr;
LABEL_228:
            v99->ptSphere = v128;
            v98 = ++igi2_frame.iMesh;
            if ( igi2_frame.iMesh >= 2 )
              return;
            v97 = pxContext;
          }
          ILF_nLastError = 1;
LABEL_197:
          v116 = nullptr;
          goto LABEL_198;
        }
      }
      else
      {
        ILF_nLastError = 1;
      }
    }
    v96 = 0;
    goto LABEL_146;
  }
}

// source: e/3/pc/pc_direct3drender.c:1535  [size]
void __cdecl Direct3D_UnloadModel(void *pxContext)
{
  struct Mesh3D_Mesh_t *v1; // eax
  int v2; // ecx
  int v3; // ecx
  void *pxRenderMesh; // ebx
  struct Direct3DRender_IndexData_s *v5; // eax
  int v6; // eax
  int v7; // esi
  int v8; // eax
  int v9; // esi
  void *v10; // ebx
  struct Direct3DRender_IndexData_s *v11; // eax
  int v12; // eax
  int v13; // esi
  int v14; // eax
  int v15; // esi
  int v16; // eax
  int v17; // esi
  int v18; // eax
  int v19; // esi
  int v20; // eax
  int v21; // esi
  _DWORD *v22; // ebx
  void *v23; // eax
  struct Direct3DRender_IndexData_s *v24; // eax
  int v25; // eax
  int v26; // esi
  int v27; // eax
  int v28; // esi

  v1 = *(struct Mesh3D_Mesh_t **)pxContext;
  v2 = *(_DWORD *)(*(_DWORD *)pxContext + 32);
  if ( v2 )
  {
    v3 = v2 - 1;
    if ( v3 )
    {
      if ( v3 != 2 )
      {
        LDebug_Error("Mesh format not supported");
        abort();
      }
      pxRenderMesh = v1->pxRenderMesh;
      if ( pxRenderMesh )
      {
        v5 = *((struct Direct3DRender_IndexData_s **)pxRenderMesh + 10);
        if ( v5 )
        {
          Direct3DRender_ReleaseIndexData(v5);
          v6 = *((_DWORD *)pxRenderMesh + 10);
          if ( v6 )
          {
            v7 = *(_DWORD *)((v6 - 4) & 0xFFFFFFFC);
            --Mem_nCurrentAllocations;
            Node_Remove((_DWORD **)v7);
            memset(*(void **)(v7 + 8), 0xCDu, *(_DWORD *)(v7 + 16));
            free((void *)v7);
          }
          *((_DWORD *)pxRenderMesh + 10) = 0;
        }
        v8 = *((_DWORD *)pxRenderMesh + 9);
        if ( v8 )
        {
          v9 = *(_DWORD *)((v8 - 4) & 0xFFFFFFFC);
          --Mem_nCurrentAllocations;
          Node_Remove((_DWORD **)v9);
          memset(*(void **)(v9 + 8), 0xCDu, *(_DWORD *)(v9 + 16));
          free((void *)v9);
          *((_DWORD *)pxRenderMesh + 9) = 0;
        }
      }
    }
    else
    {
      v10 = v1->pxRenderMesh;
      if ( v10 )
      {
        v11 = *((struct Direct3DRender_IndexData_s **)v10 + 9);
        if ( v11 )
        {
          Direct3DRender_ReleaseIndexData(v11);
          v12 = *((_DWORD *)v10 + 9);
          if ( v12 )
          {
            v13 = *(_DWORD *)((v12 - 4) & 0xFFFFFFFC);
            --Mem_nCurrentAllocations;
            Node_Remove((_DWORD **)v13);
            memset(*(void **)(v13 + 8), 0xCDu, *(_DWORD *)(v13 + 16));
            free((void *)v13);
          }
          *((_DWORD *)v10 + 9) = 0;
        }
      }
      v14 = **((_DWORD **)v10 + 6);
      if ( v14 )
      {
        v15 = *(_DWORD *)((v14 - 4) & 0xFFFFFFFC);
        --Mem_nCurrentAllocations;
        Node_Remove((_DWORD **)v15);
        memset(*(void **)(v15 + 8), 0xCDu, *(_DWORD *)(v15 + 16));
        free((void *)v15);
      }
      **((_DWORD **)v10 + 6) = 0;
      v16 = *(_DWORD *)(*((_DWORD *)v10 + 6) + 8);
      if ( v16 )
      {
        v17 = *(_DWORD *)((v16 - 4) & 0xFFFFFFFC);
        --Mem_nCurrentAllocations;
        Node_Remove((_DWORD **)v17);
        memset(*(void **)(v17 + 8), 0xCDu, *(_DWORD *)(v17 + 16));
        free((void *)v17);
      }
      *(_DWORD *)(*((_DWORD *)v10 + 6) + 8) = 0;
      v18 = *(_DWORD *)(*((_DWORD *)v10 + 6) + 12);
      if ( v18 )
      {
        v19 = *(_DWORD *)((v18 - 4) & 0xFFFFFFFC);
        --Mem_nCurrentAllocations;
        Node_Remove((_DWORD **)v19);
        memset(*(void **)(v19 + 8), 0xCDu, *(_DWORD *)(v19 + 16));
        free((void *)v19);
      }
      *(_DWORD *)(*((_DWORD *)v10 + 6) + 12) = 0;
      v20 = *((_DWORD *)v10 + 6);
      if ( v20 )
      {
        v21 = *(_DWORD *)((v20 - 4) & 0xFFFFFFFC);
        --Mem_nCurrentAllocations;
        Node_Remove((_DWORD **)v21);
        memset(*(void **)(v21 + 8), 0xCDu, *(_DWORD *)(v21 + 16));
        free((void *)v21);
      }
      *((_DWORD *)v10 + 6) = 0;
    }
  }
  else
  {
    v22 = v1->pxRenderMesh;
    if ( v22 )
    {
      ForestRender_UnloadModel(v1);
      v23 = (void *)v22[4];
      if ( v23 )
      {
        Mem_DeAllocFn(v23);
        v22[4] = 0;
      }
      v24 = (struct Direct3DRender_IndexData_s *)v22[8];
      if ( v24 )
      {
        Direct3DRender_ReleaseIndexData(v24);
        v25 = v22[8];
        if ( v25 )
        {
          v26 = *(_DWORD *)((v25 - 4) & 0xFFFFFFFC);
          --Mem_nCurrentAllocations;
          Node_Remove((_DWORD **)v26);
          memset(*(void **)(v26 + 8), 0xCDu, *(_DWORD *)(v26 + 16));
          free((void *)v26);
        }
        v22[8] = 0;
      }
      v27 = v22[7];
      if ( v27 )
      {
        v28 = *(_DWORD *)((v27 - 4) & 0xFFFFFFFC);
        --Mem_nCurrentAllocations;
        Node_Remove((_DWORD **)v28);
        memset(*(void **)(v28 + 8), 0xCDu, *(_DWORD *)(v28 + 16));
        free((void *)v28);
        v22[7] = 0;
      }
    }
  }
}

// source: e/3/pc/pc_direct3drender.c:1667  [size]
void __cdecl Direct3DRender_DestroyCallback()
{
  int v0; // edi
  struct Direct3DRender_VertexBuffer_t *v1; // esi
  int v2; // eax

  v0 = 0;
  if ( Direct3DRender_nNumVertexBuffers > 0 )
  {
    v1 = Direct3DRender_atVertexBuffer;
    do
    {
      v1->ptVertexBuffer->lpVtbl->Release(v1->ptVertexBuffer);
      v2 = Direct3DRender_nNumVertexBuffers;
      v1->ptVertexBuffer = nullptr;
      ++v0;
      ++v1;
    }
    while ( v0 < v2 );
  }
}

// source: e/3/pc/pc_direct3drender.c:1694  [size]
void __cdecl Direct3DRender_RestoreCallback()
{
  #pragma pack(push, 1)
  union
  {
    struct { int v5; };
    struct { char igi2_o1[4]; unsigned __int8 *pnVertex[2]; };
    char igi2_extent[12];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v0; // ebx
  unsigned int *p_FVF; // ebx
  int v2; // esi
  _DWORD *v3; // eax
  _DWORD *v4; // edx

  igi2_frame.pnVertex[1] = nullptr;
  if ( Direct3DRender_nNumVertexBuffers > 0 )
  {
    igi2_frame.v5 = v0;
    p_FVF = &Direct3DRender_atVertexBuffer[0].tVBDesc.FVF;
    do
    {
      Direct3D_ptDevice->lpVtbl->CreateVertexBuffer(
        Direct3D_ptDevice,
        *(p_FVF - 1),
        *(p_FVF - 3),
        *p_FVF,
        (enum _D3DPOOL)*(p_FVF - 2),
        (struct IDirect3DVertexBuffer8 **)(p_FVF - 6));
      v2 = *(p_FVF - 6);
      igi2_frame.pnVertex[0] = nullptr;
      if ( !(*(int (__stdcall **)(int, _DWORD, _DWORD, unsigned __int8 **))(*(_DWORD *)v2 + 44))(v2, 0, 0, igi2_frame.pnVertex) )
      {
        v3 = (_DWORD *)p_FVF[2];
        v4 = (_DWORD *)*v3;
        if ( *v3 )
        {
          do
          {
            qmemcpy(
              (void *)(igi2_frame.v5 + p_FVF[1] * *((unsigned __int16 *)v3 + 6)),
              (void *)v3[5],
              p_FVF[1] * *((unsigned __int16 *)v3 + 7));
            v3 = v4;
            v4 = (_DWORD *)*v4;
          }
          while ( v4 );
        }
      }
      (*(void (__stdcall **)(_DWORD))(*(_DWORD *)*(p_FVF - 6) + 48))(*(p_FVF - 6));
      p_FVF += 11;
      ++igi2_frame.v5;
    }
    while ( igi2_frame.v5 < Direct3DRender_nNumVertexBuffers );
  }
}

// source: e/3/pc/pc_direct3drender.c:1746  [size]
void __cdecl SplineObjSegment_GetClosestVertex(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct MultiMesh_TransformedVertex_t v75; };
    struct { char igi2_o1[28]; struct MultiMesh_TransformedVertex_t v76; };
    struct { char igi2_o2[56]; struct MultiMesh_TransformedVertex_t v77; };
    struct { char igi2_o3[108]; float vRadius; };
    struct { char igi2_o4[112]; float vClipZ; };
    struct { char igi2_o5[116]; __int64 ptFaceGroup; };
    struct { char igi2_o6[124]; float v81; };
    struct { char igi2_o7[128]; int iVertex; };
    struct { char igi2_o8[132]; int iFace; };
    struct { char igi2_o9[136]; struct Mesh3D_RenderMesh_RigidDirect3D_t *ptRenderMesh; };
    struct { char igi2_o10[140]; struct real32x3_t tPos; };
    struct { char igi2_o11[152]; struct real32x3_t tStartPos; };
    struct { char igi2_o12[164]; struct real32x3_t Real32x3_Rotate_tTemp; };
    struct { char igi2_o13[176]; struct real32x3_t tDisplacement; };
    struct { char igi2_o14[188]; struct real32x9_t Real32x9_Multiply_tTemp; };
    char igi2_extent[228];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int *v2; // eax
  int v3; // ecx
  float *ptNext; // eax
  double v5; // st7
  int v6; // edi
  double v7; // st7
  double v8; // st6
  double v9; // st5
  double v10; // st7
  double v11; // st7
  struct Mesh3D_RenderMesh_RigidDirect3D_t *v12; // edx
  char ptHead; // bl
  float *p_vX; // ecx
  float *v15; // eax
  int nNumVertices; // ebx
  int v17; // edi
  float *v18; // ebx
  double v19; // st7
  double v20; // st6
  double v21; // st5
  double v22; // rt0
  double v23; // st5
  double v24; // st6
  char v25; // al
  double v26; // st7
  double v27; // st7
  double v28; // st6
  int v29; // eax
  float *v30; // ebx
  double v31; // st5
  int v32; // edx
  bool v33; // zf
  double v34; // st5
  float *v35; // eax
  double v36; // st4
  float *v37; // edi
  double v38; // st3
  double v39; // st4
  double v40; // st3
  double v41; // st4
  double v42; // st3
  double v43; // st2
  double v44; // st1
  double v45; // st0
  int v46; // eax
  double v47; // st3
  double v48; // st2
  double v49; // st7
  double v50; // st6
  double v51; // st5
  int v52; // eax
  int v53; // ebp
  float *v54; // ecx
  double v55; // st7
  double v56; // st7
  double v57; // st7
  double v58; // st6
  BOOL v59; // ebx
  BOOL v60; // edi
  BOOL v61; // esi
  int v62; // eax
  float vX; // edi
  struct RigidDirect3D_FaceGroup_t *v64; // eax
  unsigned int v65; // edx
  struct RigidDirect3D_FaceGroup_t *v66; // ebp
  int iStartVertex; // eax
  int v68; // ebx
  float *v69; // esi
  struct Mesh3D_RenderMesh_RigidDirect3D_t *v70; // ecx
  float *v71; // edx
  int v72; // eax
  int v73; // ebx
  int v74; // edx

  igi2_frame.vClipZ = Direct3D_vWorldMinZ;
  v2 = *(int **)&ptQTask[2].eQTaskType;
  if ( v2 )
  {
    v3 = *v2;
    ptNext = (float *)ptQTask[38].ptNext;
    v5 = *(double *)&ptQTask[1].ptNext - TransContext_tActiveTransContext.tPos.vX;
    v6 = *(_DWORD *)(*(_DWORD *)(v3 + 12) + 12);
    if ( ptNext )
    {
      igi2_frame.tPos.vX = v5;
      igi2_frame.tPos.vY = *(double *)&ptQTask[1].tQTaskChildren.ptHead - TransContext_tActiveTransContext.tPos.vY;
      igi2_frame.tPos.vZ = *(double *)&ptQTask[1].tQTaskChildren.ptTail - TransContext_tActiveTransContext.tPos.vZ;
      igi2_frame.tPos.vX = igi2_frame.tPos.vX + *ptNext;
      igi2_frame.tPos.vY = igi2_frame.tPos.vY + ptNext[1];
      v7 = igi2_frame.tPos.vZ + ptNext[2];
      igi2_frame.Real32x3_Rotate_tTemp.vX = TransContext_tActiveTransContext.tMatrix.tX.vZ * v7
                               + TransContext_tActiveTransContext.tMatrix.tX.vY * igi2_frame.tPos.vY
                               + TransContext_tActiveTransContext.tMatrix.tX.vX * igi2_frame.tPos.vX;
      igi2_frame.Real32x3_Rotate_tTemp.vY = TransContext_tActiveTransContext.tMatrix.tY.vZ * v7
                               + TransContext_tActiveTransContext.tMatrix.tY.vY * igi2_frame.tPos.vY
                               + TransContext_tActiveTransContext.tMatrix.tY.vX * igi2_frame.tPos.vX;
      igi2_frame.Real32x3_Rotate_tTemp.vZ = TransContext_tActiveTransContext.tMatrix.tZ.vZ * v7
                               + TransContext_tActiveTransContext.tMatrix.tZ.vY * igi2_frame.tPos.vY
                               + TransContext_tActiveTransContext.tMatrix.tZ.vX * igi2_frame.tPos.vX;
      igi2_frame.tPos = igi2_frame.Real32x3_Rotate_tTemp;
      igi2_frame.vRadius = ptNext[3];
    }
    else
    {
      v8 = *(double *)&ptQTask[1].tQTaskChildren.ptHead - TransContext_tActiveTransContext.tPos.vY;
      v9 = *(double *)&ptQTask[1].tQTaskChildren.ptTail - TransContext_tActiveTransContext.tPos.vZ;
      igi2_frame.Real32x3_Rotate_tTemp.vX = TransContext_tActiveTransContext.tMatrix.tX.vZ * v9
                               + TransContext_tActiveTransContext.tMatrix.tX.vY * v8
                               + TransContext_tActiveTransContext.tMatrix.tX.vX * v5;
      igi2_frame.tPos.vX = igi2_frame.Real32x3_Rotate_tTemp.vX;
      igi2_frame.vRadius = *(float *)&ptQTask[1].eQTaskType;
      igi2_frame.Real32x3_Rotate_tTemp.vY = TransContext_tActiveTransContext.tMatrix.tY.vZ * v9
                               + TransContext_tActiveTransContext.tMatrix.tY.vY * v8
                               + TransContext_tActiveTransContext.tMatrix.tY.vX * v5;
      igi2_frame.tPos.vY = igi2_frame.Real32x3_Rotate_tTemp.vY;
      igi2_frame.Real32x3_Rotate_tTemp.vZ = TransContext_tActiveTransContext.tMatrix.tZ.vZ * v9
                               + TransContext_tActiveTransContext.tMatrix.tZ.vY * v8
                               + TransContext_tActiveTransContext.tMatrix.tZ.vX * v5;
      igi2_frame.tPos.vZ = igi2_frame.Real32x3_Rotate_tTemp.vZ;
    }
    if ( Mesh3D_ExcludeObject(&igi2_frame.tPos, igi2_frame.vRadius, nullptr) == false )
    {
      v10 = igi2_frame.tPos.vZ - igi2_frame.vRadius;
      *(float *)&igi2_frame.iFace = v10;
      if ( v10 <= *((float *)pxContext + 2) && !*(_DWORD *)(v6 + 32) )
      {
        v11 = *(float *)&ptQTask[8].tQTaskChildren.ptTail;
        v12 = *(struct Mesh3D_RenderMesh_RigidDirect3D_t **)(v6 + 36);
        ptHead = (char)ptQTask[38].tQTaskRefList.ptHead;
        igi2_frame.vRadius = *((float *)pxContext + 2);
        p_vX = &v12->ptVertex->tPos.vX;
        igi2_frame.ptRenderMesh = v12;
        v15 = (float *)&unk_7A2B608;
        if ( ptHead )
        {
          nNumVertices = v12->nNumVertices;
          v17 = 0;
          igi2_frame.tDisplacement.vX = (v11 + *(float *)&ptQTask[8].tQTaskChildren.ptMiddle) * 0.5;
          if ( nNumVertices > 0 )
          {
            do
            {
              v18 = v15;
              v19 = *p_vX - igi2_frame.tDisplacement.vX;
              ++v17;
              v20 = p_vX[1];
              p_vX += 8;
              v21 = *(p_vX - 6);
              v15 += 7;
              igi2_frame.Real32x3_Rotate_tTemp.vX = v21 * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle
                                       + v19 * *(float *)&ptQTask[3].ptPrev
                                       + v20 * *(float *)&ptQTask[3].tQTaskChildren.ptHead;
              igi2_frame.Real32x3_Rotate_tTemp.vY = v21 * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle
                                       + v19 * *(float *)&ptQTask[3].tQTaskChildren.ptTail
                                       + v20 * *(float *)&ptQTask[3].tQTaskRefList.ptHead;
              v22 = v21 * *(float *)&ptQTask[3].eQTaskType;
              v23 = v19 * *(float *)&ptQTask[3].tQTaskRefList.ptTail;
              v24 = v20 * *(float *)&ptQTask[3].ptParent;
              *v18 = igi2_frame.Real32x3_Rotate_tTemp.vX;
              v18[1] = igi2_frame.Real32x3_Rotate_tTemp.vY;
              igi2_frame.Real32x3_Rotate_tTemp.vZ = v22 + v23 + v24;
              v18[2] = igi2_frame.Real32x3_Rotate_tTemp.vZ;
            }
            while ( v17 < v12->nNumVertices );
          }
        }
        else
        {
          v25 = BYTE1(ptQTask[38].tQTaskRefList.ptHead);
          *(float *)&igi2_frame.ptFaceGroup = 1.0 / (v11 - *(float *)&ptQTask[8].tQTaskChildren.ptMiddle);
          if ( v25 )
            v26 = *(float *)&ptQTask[8].tQTaskChildren.ptTail;
          else
            v26 = *(float *)&ptQTask[8].tQTaskChildren.ptMiddle;
          v27 = -v26;
          v28 = (double)*(int *)&ptQTask[37].eQTaskType * *(float *)&igi2_frame.ptFaceGroup;
          if ( v25 )
            v28 = -v28;
          v29 = v12->nNumVertices;
          igi2_frame.iVertex = 0;
          if ( v29 > 0 )
          {
            v30 = (float *)&unk_7A2B610;
            do
            {
              v31 = (v27 + *p_vX) * v28;
              igi2_frame.ptFaceGroup = (__int64)v31;
              v32 = (__int64)v31;
              v33 = v32 == *(_DWORD *)&ptQTask[37].eQTaskType;
              LODWORD(igi2_frame.ptFaceGroup) = v32;
              if ( v33 )
                LODWORD(igi2_frame.ptFaceGroup) = --v32;
              v34 = v31 - (double)(int)igi2_frame.ptFaceGroup;
              if ( v34 >= 0.0 )
              {
                if ( v34 > 1.0 )
                  v34 = 1.0;
              }
              else
              {
                v34 = 0.0;
              }
              v35 = (float *)&ptQTask[v32];
              v36 = v35[150] * p_vX[2];
              v37 = (float *)((char *)ptQTask + 12 * v32);
              v38 = v35[149] * p_vX[1];
              p_vX += 8;
              v39 = v36 + v38;
              v30 += 7;
              v40 = v35[153] * *(p_vX - 6) + v35[152] * *(p_vX - 7);
              igi2_frame.tStartPos.vZ = v35[156] * *(p_vX - 6) + v35[155] * *(p_vX - 7);
              igi2_frame.tStartPos.vX = v39 + v37[85];
              v41 = v40 + v37[86];
              igi2_frame.tStartPos.vZ = igi2_frame.tStartPos.vZ + *(float *)&(&ptQTask[8].tQTaskRefList.ptTail)[3 * v32];
              v42 = v35[160] * *(p_vX - 6) + v35[159] * *(p_vX - 7);
              v43 = v35[163] * *(p_vX - 6) + v35[162] * *(p_vX - 7);
              v44 = v35[166] * *(p_vX - 6);
              v45 = v35[165] * *(p_vX - 7);
              v46 = ++igi2_frame.iVertex;
              igi2_frame.Real32x3_Rotate_tTemp.vZ = v44 + v45;
              igi2_frame.Real32x3_Rotate_tTemp.vX = v42 + v37[88];
              v47 = v43 + v37[89];
              v48 = igi2_frame.Real32x3_Rotate_tTemp.vZ + *((float *)&ptQTask[9].ptNext + 3 * v32);
              v12 = igi2_frame.ptRenderMesh;
              igi2_frame.Real32x3_Rotate_tTemp.vZ = v48;
              *(v30 - 9) = (igi2_frame.Real32x3_Rotate_tTemp.vX - igi2_frame.tStartPos.vX) * v34 + igi2_frame.tStartPos.vX;
              *(v30 - 8) = (v47 - v41) * v34 + v41;
              *(v30 - 7) = (igi2_frame.Real32x3_Rotate_tTemp.vZ - igi2_frame.tStartPos.vZ) * v34 + igi2_frame.tStartPos.vZ;
            }
            while ( v46 < v12->nNumVertices );
          }
        }
        v49 = *(double *)&ptQTask[1].ptNext - TransContext_tActiveTransContext.tPos.vX;
        v50 = *(double *)&ptQTask[1].tQTaskChildren.ptHead - TransContext_tActiveTransContext.tPos.vY;
        v51 = *(double *)&ptQTask[1].tQTaskChildren.ptTail - TransContext_tActiveTransContext.tPos.vZ;
        igi2_frame.tDisplacement.vX = TransContext_tActiveTransContext.tMatrix.tX.vZ * v51
                         + v50 * TransContext_tActiveTransContext.tMatrix.tX.vY
                         + v49 * TransContext_tActiveTransContext.tMatrix.tX.vX;
        igi2_frame.tDisplacement.vY = TransContext_tActiveTransContext.tMatrix.tY.vZ * v51
                         + v50 * TransContext_tActiveTransContext.tMatrix.tY.vY
                         + v49 * TransContext_tActiveTransContext.tMatrix.tY.vX;
        igi2_frame.tDisplacement.vZ = v51 * TransContext_tActiveTransContext.tMatrix.tZ.vZ
                         + v50 * TransContext_tActiveTransContext.tMatrix.tZ.vY
                         + v49 * TransContext_tActiveTransContext.tMatrix.tZ.vX;
        igi2_frame.Real32x9_Multiply_tTemp.tX.vX = TransContext_tActiveTransContext.tMatrix.tX.vZ
                                      * *(float *)&ptQTask[3].tQTaskRefList.ptTail
                                      + TransContext_tActiveTransContext.tMatrix.tX.vX * *(float *)&ptQTask[3].ptPrev
                                      + TransContext_tActiveTransContext.tMatrix.tX.vY
                                      * *(float *)&ptQTask[3].tQTaskChildren.ptTail;
        igi2_frame.Real32x9_Multiply_tTemp.tX.vY = TransContext_tActiveTransContext.tMatrix.tX.vZ * *(float *)&ptQTask[3].ptParent
                                      + TransContext_tActiveTransContext.tMatrix.tX.vX
                                      * *(float *)&ptQTask[3].tQTaskChildren.ptHead
                                      + TransContext_tActiveTransContext.tMatrix.tX.vY
                                      * *(float *)&ptQTask[3].tQTaskRefList.ptHead;
        igi2_frame.Real32x9_Multiply_tTemp.tX.vZ = TransContext_tActiveTransContext.tMatrix.tX.vZ
                                      * *(float *)&ptQTask[3].eQTaskType
                                      + TransContext_tActiveTransContext.tMatrix.tX.vX
                                      * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle
                                      + TransContext_tActiveTransContext.tMatrix.tX.vY
                                      * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle;
        igi2_frame.Real32x9_Multiply_tTemp.tY.vX = TransContext_tActiveTransContext.tMatrix.tY.vZ
                                      * *(float *)&ptQTask[3].tQTaskRefList.ptTail
                                      + TransContext_tActiveTransContext.tMatrix.tY.vX * *(float *)&ptQTask[3].ptPrev
                                      + TransContext_tActiveTransContext.tMatrix.tY.vY
                                      * *(float *)&ptQTask[3].tQTaskChildren.ptTail;
        v52 = v12->nNumVertices;
        v53 = 0;
        igi2_frame.Real32x9_Multiply_tTemp.tY.vY = TransContext_tActiveTransContext.tMatrix.tY.vZ * *(float *)&ptQTask[3].ptParent
                                      + TransContext_tActiveTransContext.tMatrix.tY.vX
                                      * *(float *)&ptQTask[3].tQTaskChildren.ptHead
                                      + TransContext_tActiveTransContext.tMatrix.tY.vY
                                      * *(float *)&ptQTask[3].tQTaskRefList.ptHead;
        igi2_frame.Real32x9_Multiply_tTemp.tY.vZ = TransContext_tActiveTransContext.tMatrix.tY.vZ
                                      * *(float *)&ptQTask[3].eQTaskType
                                      + TransContext_tActiveTransContext.tMatrix.tY.vX
                                      * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle
                                      + TransContext_tActiveTransContext.tMatrix.tY.vY
                                      * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle;
        igi2_frame.Real32x9_Multiply_tTemp.tZ.vX = TransContext_tActiveTransContext.tMatrix.tZ.vZ
                                      * *(float *)&ptQTask[3].tQTaskRefList.ptTail
                                      + TransContext_tActiveTransContext.tMatrix.tZ.vX * *(float *)&ptQTask[3].ptPrev
                                      + TransContext_tActiveTransContext.tMatrix.tZ.vY
                                      * *(float *)&ptQTask[3].tQTaskChildren.ptTail;
        igi2_frame.Real32x9_Multiply_tTemp.tZ.vY = TransContext_tActiveTransContext.tMatrix.tZ.vZ * *(float *)&ptQTask[3].ptParent
                                      + TransContext_tActiveTransContext.tMatrix.tZ.vX
                                      * *(float *)&ptQTask[3].tQTaskChildren.ptHead
                                      + TransContext_tActiveTransContext.tMatrix.tZ.vY
                                      * *(float *)&ptQTask[3].tQTaskRefList.ptHead;
        igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ = TransContext_tActiveTransContext.tMatrix.tZ.vZ
                                      * *(float *)&ptQTask[3].eQTaskType
                                      + TransContext_tActiveTransContext.tMatrix.tZ.vX
                                      * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle
                                      + TransContext_tActiveTransContext.tMatrix.tZ.vY
                                      * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle;
        if ( v52 > 0 )
        {
          v54 = (float *)&unk_7A2B60C;
          do
          {
            igi2_frame.Real32x3_Rotate_tTemp.vX = igi2_frame.Real32x9_Multiply_tTemp.tX.vY * *v54
                                     + igi2_frame.Real32x9_Multiply_tTemp.tX.vX * *(v54 - 1)
                                     + igi2_frame.Real32x9_Multiply_tTemp.tX.vZ * v54[1];
            *(float *)&igi2_frame.ptFaceGroup = igi2_frame.Real32x3_Rotate_tTemp.vX;
            igi2_frame.Real32x3_Rotate_tTemp.vY = igi2_frame.Real32x9_Multiply_tTemp.tY.vY * *v54
                                     + igi2_frame.Real32x9_Multiply_tTemp.tY.vX * *(v54 - 1)
                                     + igi2_frame.Real32x9_Multiply_tTemp.tY.vZ * v54[1];
            HIDWORD(igi2_frame.ptFaceGroup) = LODWORD(igi2_frame.Real32x3_Rotate_tTemp.vY);
            igi2_frame.Real32x3_Rotate_tTemp.vZ = igi2_frame.Real32x9_Multiply_tTemp.tZ.vX * *(v54 - 1)
                                     + igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ * v54[1]
                                     + igi2_frame.Real32x9_Multiply_tTemp.tZ.vY * *v54;
            *(float *)&igi2_frame.ptFaceGroup = igi2_frame.Real32x3_Rotate_tTemp.vX + igi2_frame.tDisplacement.vX;
            *((float *)&igi2_frame.ptFaceGroup + 1) = igi2_frame.Real32x3_Rotate_tTemp.vY + igi2_frame.tDisplacement.vY;
            v55 = igi2_frame.Real32x3_Rotate_tTemp.vZ + igi2_frame.tDisplacement.vZ;
            igi2_frame.v81 = v55;
            if ( v55 < igi2_frame.vClipZ )
            {
              v62 = 16;
            }
            else
            {
              v56 = 1.0 / igi2_frame.v81;
              igi2_frame.tStartPos.vZ = v56;
              v57 = v56 * *(float *)&igi2_frame.ptFaceGroup * TransContext_tActiveTransContext.vScreenFOVX
                  + TransContext_tActiveTransContext.vScreenOriginX;
              igi2_frame.tStartPos.vX = v57;
              v58 = TransContext_tActiveTransContext.vScreenFOVY * igi2_frame.tStartPos.vZ * *((float *)&igi2_frame.ptFaceGroup + 1)
                  + TransContext_tActiveTransContext.vScreenOriginY;
              igi2_frame.tStartPos.vY = v58;
              v59 = v57 < RenderContext_tActiveRenderContext.tDisplayAreaMin.vX;
              v60 = v58 < RenderContext_tActiveRenderContext.tDisplayAreaMin.vY;
              v61 = v57 > RenderContext_tActiveRenderContext.tDisplayAreaMax.vX;
              if ( igi2_frame.tStartPos.vY <= (double)RenderContext_tActiveRenderContext.tDisplayAreaMax.vY )
                v62 = v59 | (2 * (v60 | (2 * v61)));
              else
                v62 = v59 | (2 * (v60 | (2 * (v61 | 2))));
            }
            vX = igi2_frame.tStartPos.vX;
            *(_QWORD *)(v54 - 1) = igi2_frame.ptFaceGroup;
            v54[1] = igi2_frame.v81;
            v54[2] = vX;
            v54[3] = igi2_frame.tStartPos.vY;
            v54[4] = igi2_frame.tStartPos.vZ;
            *((_DWORD *)v54 + 5) = v62;
            if ( !v62 && igi2_frame.v81 < (double)igi2_frame.vRadius )
              igi2_frame.vRadius = igi2_frame.v81;
            ++v53;
            v54 += 7;
          }
          while ( v53 < v12->nNumVertices );
        }
        if ( *(float *)&igi2_frame.iFace < (double)igi2_frame.vClipZ )
        {
          v64 = v12->ptFaceGroup;
          v65 = (unsigned int)&v64[v12->nNumFaceGroups];
          igi2_frame.iVertex = v65;
          LODWORD(igi2_frame.ptFaceGroup) = v64;
          if ( v64 )
          {
            do
            {
              v33 = v64->nNumFaces == 0;
              v66 = v64 + 1;
              *(float *)&igi2_frame.iFace = 0.0;
              if ( !v33 )
              {
                do
                {
                  iStartVertex = v64->iStartVertex;
                  v68 = 28 * (iStartVertex + *(unsigned __int16 *)&v66->nShininessStrength);
                  v69 = (float *)(28 * (iStartVertex + LOWORD(v66->tAveragePos.vX)) + 128103944);
                  v70 = (struct Mesh3D_RenderMesh_RigidDirect3D_t *)dword_7A2B620[7 * iStartVertex
                                                                                + 7 * LOWORD(v66->tAveragePos.vX)];
                  v71 = (float *)(28 * (iStartVertex + *(unsigned __int16 *)&v66->bMaterialProperties) + 128103944);
                  v72 = dword_7A2B620[7 * iStartVertex + 7 * *(unsigned __int16 *)&v66->bMaterialProperties];
                  v73 = v68 + 128103944;
                  igi2_frame.ptRenderMesh = v70;
                  if ( (unsigned int)v70 | *(_DWORD *)(v73 + 24) | v72
                    && (*(_DWORD *)(v73 + 24) & v72 & (unsigned int)v70) == 0
                    && (v71[2] < (double)igi2_frame.vRadius || *(float *)(v73 + 8) < (double)igi2_frame.vRadius || v69[2] < (double)igi2_frame.vRadius) )
                  {
                    qmemcpy(&igi2_frame.v77, v69, sizeof(igi2_frame.v77));
                    qmemcpy(&igi2_frame.v76, (void *)v73, sizeof(igi2_frame.v76));
                    qmemcpy(&igi2_frame.v75, v71, sizeof(igi2_frame.v75));
                    RigidDynCubeObj_CheckTriangle(igi2_frame.v75, igi2_frame.v76, igi2_frame.v77, &igi2_frame.vRadius, igi2_frame.vClipZ);
                  }
                  v64 = (struct RigidDirect3D_FaceGroup_t *)igi2_frame.ptFaceGroup;
                  v74 = *(unsigned __int16 *)(igi2_frame.ptFaceGroup + 18);
                  v66 = (struct RigidDirect3D_FaceGroup_t *)((char *)v66 + 6);
                  ++igi2_frame.iFace;
                }
                while ( igi2_frame.iFace < v74 );
                v65 = igi2_frame.iVertex;
              }
              LODWORD(igi2_frame.ptFaceGroup) = ++v64;
            }
            while ( (unsigned int)v64 < v65 );
          }
        }
        *((float *)pxContext + 2) = igi2_frame.vRadius;
      }
    }
  }
}

// source: e/3/pc/pc_direct3drender.c:2047  [size]
void __cdecl Direct3DRender_SetFogParameters(struct real64x3_t *ptPos, float vRadius)
{
  double v2; // st7
  double v3; // st6
  double v4; // st6
  double v7; // st6
  long double v10; // st6
  long double v11; // st7
  double v12; // st7
  float vEnd; // [esp+Ch] [ebp-20h]
  float vEnda; // [esp+Ch] [ebp-20h]
  float vNear; // [esp+10h] [ebp-1Ch]
  float vNeara; // [esp+10h] [ebp-1Ch]
  float vFogFar; // [esp+14h] [ebp-18h]
  float vFar; // [esp+18h] [ebp-14h]
  float v19; // [esp+1Ch] [ebp-10h]
  float tVector; // [esp+20h] [ebp-Ch]
  float tVector_8; // [esp+28h] [ebp-4h]

  v2 = Mesh3D_avFogDensity[1];
  if ( Mesh3D_avFogDensity[1] == 0.0 )
  {
    vNeara = 2040109440.0;
    vEnda = 2147483648.0;
  }
  else
  {
    tVector_8 = ptPos->vZ;
    tVector = ptPos->vX - TransContext_tActiveTransContext.tPos.vX;
    v3 = TransContext_tActiveTransContext.tMatrix.tZ.vZ * (tVector_8 - TransContext_tActiveTransContext.tPos.vZ)
       + TransContext_tActiveTransContext.tMatrix.tZ.vY * (ptPos->vY - TransContext_tActiveTransContext.tPos.vY)
       + TransContext_tActiveTransContext.tMatrix.tZ.vX * tVector;
    vNear = v3 - vRadius;
    vFar = v3 + vRadius;
    v4 = Direct3D_vScale * vNear * v2 * 1.442695040888963407;
    vEnd = 1.0 / pow(2.0, v4);
    v7 = Direct3D_vScale * vFar * v2 * 1.442695040888963407;
    v10 = pow(2.0, v7);
    v11 = 1.0 / v10 - vEnd;
    if ( v11 == 0.0 || vEnd == 0.0 )
    {
      vNeara = 0.0;
      vEnda = 0.0;
    }
    else
    {
      vFogFar = 1.0 / v10;
      v19 = v11;
      v12 = (vFogFar * vNear - vEnd * vFar) / v19;
      vNeara = (v12 - (v12 - vNear) / vEnd) * Direct3D_vScale;
      vEnda = Direct3D_vScale * v12;
    }
  }
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGSTART, LODWORD(vNeara));
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGEND, LODWORD(vEnda));
}

// source: e/3/pc/pc_direct3drender.c:2112  [size]
struct RigidDynCubeObj_t *__cdecl Direct3DRender_SetFogParametersRigid(
        struct RigidDynCubeObj_t *ptRigidDynCubeObj,
        struct Mesh3D_Mesh_t *ptMesh)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vRadius; };
    struct { char igi2_o1[16]; float Real32x3_Rotate_tTemp_8; };
    struct { char igi2_o2[20]; struct real64x3_t tPos; };
    char igi2_extent[48];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v2; // rt0
  struct RigidDynCubeObj_t *result; // eax

  igi2_frame.Real32x3_Rotate_tTemp_8 = ptRigidDynCubeObj->tModelObj.tOrientation.tZ.vZ * ptMesh->tRenderMeshSphere.tPos.vZ
                          + ptRigidDynCubeObj->tModelObj.tOrientation.tZ.vY * ptMesh->tRenderMeshSphere.tPos.vY
                          + ptRigidDynCubeObj->tModelObj.tOrientation.tZ.vX * ptMesh->tRenderMeshSphere.tPos.vX;
  v2 = ptRigidDynCubeObj->tModelObj.tOrientation.tY.vZ * ptMesh->tRenderMeshSphere.tPos.vZ
     + ptRigidDynCubeObj->tModelObj.tOrientation.tY.vY * ptMesh->tRenderMeshSphere.tPos.vY
     + ptRigidDynCubeObj->tModelObj.tOrientation.tY.vX * ptMesh->tRenderMeshSphere.tPos.vX;
  igi2_frame.tPos.vX = ptRigidDynCubeObj->tModelObj.tOrientation.tX.vZ * ptMesh->tRenderMeshSphere.tPos.vZ
          + ptRigidDynCubeObj->tModelObj.tOrientation.tX.vY * ptMesh->tRenderMeshSphere.tPos.vY
          + ptRigidDynCubeObj->tModelObj.tOrientation.tX.vX * ptMesh->tRenderMeshSphere.tPos.vX
          + ptRigidDynCubeObj->tModelObj.tDynCubeObj.tQObj.tPos.vX;
  igi2_frame.tPos.vY = v2 + ptRigidDynCubeObj->tModelObj.tDynCubeObj.tQObj.tPos.vY;
  igi2_frame.vRadius = ptMesh->tRenderMeshSphere.vRadius;
  igi2_frame.tPos.vZ = igi2_frame.Real32x3_Rotate_tTemp_8 + ptRigidDynCubeObj->tModelObj.tDynCubeObj.tQObj.tPos.vZ;
  Direct3DRender_SetFogParameters(&igi2_frame.tPos, igi2_frame.vRadius);
  return result;
}

// source: e/3/pc/pc_direct3drender.c:2495  [size]
void __cdecl Direct3D_InitModels(void *pxContext)
{
  enum Direct3DRender_VBType_e v1; // edi
  int *p_nNumRequests; // esi

  v1 = DIRECT3DRENDER_VBTYPE_RIGID_XYZNORMALTEX1;
  p_nNumRequests = &Direct3dRender_atVBQueue[0].nNumRequests;
  do
  {
    if ( *p_nNumRequests )
      Direct3DRender_FlushQueue(v1);
    p_nNumRequests += 2002;
    ++v1;
  }
  while ( (int)p_nNumRequests < 128101972 );
}

// source: e/3/pc/pc_direct3drender.c:2518  [size]
void __cdecl Direct3D_DeinitModels(void *pxContext)
{
  int v1; // edi
  struct Direct3DRender_VertexBuffer_t *v2; // esi
  int v3; // eax

  v1 = 0;
  if ( Direct3DRender_nNumVertexBuffers > 0 )
  {
    v2 = Direct3DRender_atVertexBuffer;
    do
    {
      v2->ptVertexBuffer->lpVtbl->Release(v2->ptVertexBuffer);
      v3 = Direct3DRender_nNumVertexBuffers;
      v2->ptVertexBuffer = nullptr;
      ++v1;
      ++v2;
    }
    while ( v1 < v3 );
  }
  Direct3DRender_nNumVertexBuffers = 0;
}

// source: e/3/pc/pc_direct3drender.c:2543  [size]
void __cdecl Direct3DRender_ProcessVerticesLightmap(
        struct Mesh3D_RenderMesh_LightmapDirect3D_t *ptSource,
        struct Mesh3D_LightmapVirModel_t *ptLightmapVirModel)
{
  ;
}

// source: e/3/pc/pc_direct3drender.c:2627  [size]
void __cdecl Direct3DRender_UpdateMesh(void *pxContext)
{
  ;
}

// source: e/3/pc/pc_direct3drender.c:2649  [size]
int __cdecl Direct3DRender_SortedFaceGroup_ProcessVerticesSpline(
        struct Mesh3D_RenderMesh_RigidDirect3D_t *ptSource,
        struct SplineObjSegment_s *ptSplineObjSegment,
        struct RigidDirect3D_FaceGroup_t *ptFaceGroup)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v1DivDeltaX; };
    struct { int v1DivDeltaXa; };
    struct { char igi2_o2[8]; struct Direct3DRender_XYZNormalTex1Vertex_t *ptSourceVertex; };
    struct { char igi2_o3[12]; int iIndex; };
    struct { char igi2_o4[16]; int iDynamicVBOffset; };
    struct { char igi2_o5[20]; struct real32x3_t Real32x3_Rotate_tTemp; };
    struct { char igi2_o6[32]; struct real32x3_t tEndPos; };
    struct { char igi2_o7[44]; struct real32x3_t tDisplacement; };
    char igi2_extent[56];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct RigidDirect3D_FaceGroup_t *v3; // ebp
  double vEndX; // st7
  int v5; // edx
  int v6; // ecx
  struct Direct3DRender_XYZNormalTex1Vertex_t *v7; // eax
  struct RigidDirect3D_FaceGroup_t *v8; // edx
  double v9; // st7
  double vY; // st6
  double vZ; // st5
  double v12; // rt1
  double v13; // st5
  double v14; // st6
  float *p_vZ; // esi
  int v16; // eax
  char isFlip; // al
  double vStartX; // st7
  double v19; // st7
  double v20; // st6
  int v21; // ecx
  struct Direct3DRender_XYZNormalTex1Vertex_t *v22; // ecx
  double v23; // st5
  int v24; // edx
  double v25; // st5
  float *v26; // eax
  float *v27; // esi
  double v28; // st4
  double v29; // st3
  double v30; // st4
  double v31; // st3
  double v32; // st2
  double v33; // st3
  double v34; // st5
  double v35; // st4
  float *v36; // eax
  int nNumFaces; // eax

  v3 = ptFaceGroup;
  Direct3D_LockDynamicVertexBuffer(
    Direct3D_atDynamicVertexBuffer,
    (void **)&ptFaceGroup,
    &igi2_frame.iDynamicVBOffset,
    3 * ptFaceGroup->nNumFaces);
  if ( ptFaceGroup )
  {
    vEndX = ptSplineObjSegment->vEndX;
    igi2_frame.ptSourceVertex = ptSource->ptVertex;
    if ( ptSplineObjSegment->isLinear )
    {
      v5 = 3 * v3->nNumFaces;
      v6 = 0;
      igi2_frame.tDisplacement.vX = (vEndX + ptSplineObjSegment->vStartX) * 0.5;
      if ( v5 > 0 )
      {
        do
        {
          v7 = &igi2_frame.ptSourceVertex[ptSource->piIndex[v6 + v3->iStartIndex]];
          v8 = ptFaceGroup;
          v9 = v7->tPos.vX - igi2_frame.tDisplacement.vX;
          vY = v7->tPos.vY;
          vZ = v7->tPos.vZ;
          igi2_frame.Real32x3_Rotate_tTemp.vX = v9 * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tX.vX
                                   + vZ * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tX.vZ
                                   + vY * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tX.vY;
          igi2_frame.Real32x3_Rotate_tTemp.vY = vZ * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tY.vZ
                                   + vY * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tY.vY
                                   + v9 * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tY.vX;
          v12 = v9 * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vX;
          v13 = vZ * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vZ;
          v14 = vY * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vY;
          *(float *)&ptFaceGroup->bMaterialProperties = igi2_frame.Real32x3_Rotate_tTemp.vX;
          v8->tAveragePos.vX = igi2_frame.Real32x3_Rotate_tTemp.vY;
          igi2_frame.Real32x3_Rotate_tTemp.vZ = v12 + v13 + v14;
          v8->tAveragePos.vY = igi2_frame.Real32x3_Rotate_tTemp.vZ;
          p_vZ = &ptFaceGroup->tAveragePos.vZ;
          ptFaceGroup->tAveragePos.vZ = v7->tNormal.vX;
          p_vZ[1] = v7->tNormal.vY;
          p_vZ[2] = v7->tNormal.vZ;
          *(float *)&ptFaceGroup->iTexture = v7->tUV.vX;
          *(float *)&ptFaceGroup->iEnvMap = v7->tUV.vY;
          ++v6;
          v16 = 3 * v3->nNumFaces;
          ++ptFaceGroup;
        }
        while ( v6 < v16 );
      }
    }
    else
    {
      isFlip = ptSplineObjSegment->isFlip;
      igi2_frame.v1DivDeltaX = 1.0 / (vEndX - ptSplineObjSegment->vStartX);
      if ( isFlip )
        vStartX = ptSplineObjSegment->vEndX;
      else
        vStartX = ptSplineObjSegment->vStartX;
      v19 = -vStartX;
      v20 = (double)ptSplineObjSegment->nAreas * igi2_frame.v1DivDeltaX;
      if ( isFlip )
        v20 = -v20;
      v21 = 0;
      igi2_frame.iIndex = 0;
      if ( 3 * v3->nNumFaces > 0 )
      {
        do
        {
          v22 = &igi2_frame.ptSourceVertex[ptSource->piIndex[v21 + v3->iStartIndex]];
          v23 = (v19 + v22->tPos.vX) * v20;
          v24 = (__int64)v23;
          igi2_frame.v1DivDeltaXa = v24;
          if ( v24 == ptSplineObjSegment->nAreas )
            igi2_frame.v1DivDeltaXa = --v24;
          v25 = v23 - (double)igi2_frame.v1DivDeltaXa;
          if ( v25 >= 0.0 )
          {
            if ( v25 > 1.0 )
              v25 = 1.0;
          }
          else
          {
            v25 = 0.0;
          }
          v26 = (float *)(&ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask + v24);
          v27 = (float *)((char *)ptSplineObjSegment + 12 * v24);
          v28 = v26[150] * v22->tPos.vZ + v26[149] * v22->tPos.vY;
          v29 = v26[153] * v22->tPos.vZ + v26[152] * v22->tPos.vY;
          igi2_frame.Real32x3_Rotate_tTemp.vZ = v26[156] * v22->tPos.vZ + v26[155] * v22->tPos.vY;
          igi2_frame.Real32x3_Rotate_tTemp.vX = v28 + v27[85];
          v30 = v29 + v27[86];
          igi2_frame.Real32x3_Rotate_tTemp.vZ = igi2_frame.Real32x3_Rotate_tTemp.vZ + ptSplineObjSegment->atAreaPos[v24].vZ;
          v31 = v26[160] * v22->tPos.vZ + v26[159] * v22->tPos.vY;
          v32 = v26[163] * v22->tPos.vZ + v26[162] * v22->tPos.vY;
          igi2_frame.tEndPos.vZ = v26[166] * v22->tPos.vZ + v26[165] * v22->tPos.vY;
          igi2_frame.tEndPos.vX = v31 + v27[88];
          v33 = v32 + v27[89];
          igi2_frame.tEndPos.vZ = igi2_frame.tEndPos.vZ + ptSplineObjSegment->atAreaPos[v24 + 1].vZ;
          *(float *)&ptFaceGroup->bMaterialProperties = (igi2_frame.tEndPos.vX - igi2_frame.Real32x3_Rotate_tTemp.vX) * v25
                                                      + igi2_frame.Real32x3_Rotate_tTemp.vX;
          ptFaceGroup->tAveragePos.vX = (v33 - v30) * v25 + v30;
          ptFaceGroup->tAveragePos.vY = (igi2_frame.tEndPos.vZ - igi2_frame.Real32x3_Rotate_tTemp.vZ) * v25 + igi2_frame.Real32x3_Rotate_tTemp.vZ;
          igi2_frame.tDisplacement.vX = ptSplineObjSegment->atAreaOrientation[v24].tX.vZ * v22->tNormal.vZ
                           + v26[149] * v22->tNormal.vY
                           + v22->tNormal.vX * v26[148];
          igi2_frame.tDisplacement.vY = v26[152] * v22->tNormal.vY + v26[153] * v22->tNormal.vZ + v26[151] * v22->tNormal.vX;
          v34 = v26[155] * v22->tNormal.vY + v26[156] * v22->tNormal.vZ;
          v35 = v26[154] * v22->tNormal.vX;
          v36 = &ptFaceGroup->tAveragePos.vZ;
          ptFaceGroup->tAveragePos.vZ = igi2_frame.tDisplacement.vX;
          v36[1] = igi2_frame.tDisplacement.vY;
          igi2_frame.tDisplacement.vZ = v34 + v35;
          v36[2] = igi2_frame.tDisplacement.vZ;
          *(float *)&ptFaceGroup->iTexture = v22->tUV.vX;
          *(float *)&ptFaceGroup->iEnvMap = v22->tUV.vY;
          nNumFaces = v3->nNumFaces;
          v21 = igi2_frame.iIndex + 1;
          ++ptFaceGroup;
          ++igi2_frame.iIndex;
        }
        while ( igi2_frame.iIndex < 3 * nNumFaces );
      }
    }
    Direct3D_atDynamicVertexBuffer[0].ptVertexBuffer->lpVtbl->Unlock(Direct3D_atDynamicVertexBuffer[0].ptVertexBuffer);
  }
  return igi2_frame.iDynamicVBOffset;
}

// source: e/3/pc/pc_direct3drender.c:2777  [size]
int __cdecl Direct3DRender_ProcessVerticesSplineRigid(
        struct Mesh3D_RenderMesh_RigidDirect3D_t *ptSource,
        struct SplineObjSegment_s *ptSplineObjSegment)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v1DivDeltaX; };
    struct { int v1DivDeltaXa; };
    struct { char igi2_o2[8]; int iVertex; };
    struct { char igi2_o3[12]; int iDynamicVBOffset; };
    struct { char igi2_o4[16]; struct real32x3_t Real32x3_Rotate_tTemp; };
    struct { char igi2_o5[28]; struct real32x3_t tEndPos; };
    struct { char igi2_o6[40]; struct real32x3_t tDisplacement; };
    char igi2_extent[52];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Mesh3D_RenderMesh_RigidDirect3D_t *v2; // ebp
  double vEndX; // st7
  struct Direct3DRender_XYZNormalTex1Vertex_t *ptVertex; // ecx
  int nNumVertices; // edx
  int v6; // eax
  struct Mesh3D_RenderMesh_RigidDirect3D_t *v7; // edx
  double v8; // st7
  double vY; // st6
  double vZ; // st5
  double v11; // rt1
  double v12; // st5
  double v13; // st6
  int *p_nNumVertices; // esi
  int v15; // edx
  char isFlip; // al
  double vStartX; // st7
  double v18; // st7
  double v19; // st6
  double v20; // st5
  int v21; // edx
  double v22; // st5
  float *v23; // eax
  float *v24; // esi
  double v25; // st4
  double v26; // st3
  double v27; // st4
  double v28; // st3
  double v29; // st2
  double v30; // st3
  double v31; // st5
  double v32; // st4
  double v33; // st5
  double v34; // st4
  int *v35; // eax
  bool v36; // cc

  v2 = ptSource;
  Direct3D_LockDynamicVertexBuffer(
    Direct3D_atDynamicVertexBuffer,
    (void **)&ptSource,
    &igi2_frame.iDynamicVBOffset,
    ptSource->nNumVertices);
  if ( ptSource )
  {
    vEndX = ptSplineObjSegment->vEndX;
    ptVertex = v2->ptVertex;
    if ( ptSplineObjSegment->isLinear )
    {
      nNumVertices = v2->nNumVertices;
      v6 = 0;
      igi2_frame.tDisplacement.vX = (vEndX + ptSplineObjSegment->vStartX) * 0.5;
      if ( nNumVertices > 0 )
      {
        do
        {
          v7 = ptSource;
          v8 = ptVertex->tPos.vX - igi2_frame.tDisplacement.vX;
          vY = ptVertex->tPos.vY;
          vZ = ptVertex->tPos.vZ;
          igi2_frame.Real32x3_Rotate_tTemp.vX = v8 * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tX.vX
                                   + vZ * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tX.vZ
                                   + vY * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tX.vY;
          igi2_frame.Real32x3_Rotate_tTemp.vY = v8 * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tY.vX
                                   + vZ * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tY.vZ
                                   + vY * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tY.vY;
          v11 = v8 * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vX;
          v12 = vZ * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vZ;
          v13 = vY * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vY;
          ptSource->nPrimitiveType = LODWORD(igi2_frame.Real32x3_Rotate_tTemp.vX);
          v7->nNumFaces = LODWORD(igi2_frame.Real32x3_Rotate_tTemp.vY);
          igi2_frame.Real32x3_Rotate_tTemp.vZ = v11 + v12 + v13;
          v7->nNumFaceGroups = LODWORD(igi2_frame.Real32x3_Rotate_tTemp.vZ);
          p_nNumVertices = &ptSource->nNumVertices;
          ptSource->nNumVertices = LODWORD(ptVertex->tNormal.vX);
          p_nNumVertices[1] = LODWORD(ptVertex->tNormal.vY);
          p_nNumVertices[2] = LODWORD(ptVertex->tNormal.vZ);
          ptSource->ptFaceGroup = (struct RigidDirect3D_FaceGroup_t *)LODWORD(ptVertex->tUV.vX);
          ptSource->ptVertexData = (struct Direct3DRender_VertexData_s *)LODWORD(ptVertex->tUV.vY);
          v15 = v2->nNumVertices;
          ++v6;
          ++ptVertex;
          ptSource = (struct Mesh3D_RenderMesh_RigidDirect3D_t *)((char *)ptSource + 32);
        }
        while ( v6 < v15 );
      }
    }
    else
    {
      isFlip = ptSplineObjSegment->isFlip;
      igi2_frame.v1DivDeltaX = 1.0 / (vEndX - ptSplineObjSegment->vStartX);
      if ( isFlip )
        vStartX = ptSplineObjSegment->vEndX;
      else
        vStartX = ptSplineObjSegment->vStartX;
      v18 = -vStartX;
      v19 = (double)ptSplineObjSegment->nAreas * igi2_frame.v1DivDeltaX;
      if ( isFlip )
        v19 = -v19;
      igi2_frame.iVertex = 0;
      if ( v2->nNumVertices > 0 )
      {
        do
        {
          v20 = (v18 + ptVertex->tPos.vX) * v19;
          v21 = (__int64)v20;
          igi2_frame.v1DivDeltaXa = v21;
          if ( v21 == ptSplineObjSegment->nAreas )
            igi2_frame.v1DivDeltaXa = --v21;
          v22 = v20 - (double)igi2_frame.v1DivDeltaXa;
          if ( v22 >= 0.0 )
          {
            if ( v22 > 1.0 )
              v22 = 1.0;
          }
          else
          {
            v22 = 0.0;
          }
          v23 = (float *)(&ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask + v21);
          v24 = (float *)((char *)ptSplineObjSegment + 12 * v21);
          v25 = v23[150] * ptVertex->tPos.vZ + v23[149] * ptVertex->tPos.vY;
          v26 = v23[153] * ptVertex->tPos.vZ + v23[152] * ptVertex->tPos.vY;
          igi2_frame.Real32x3_Rotate_tTemp.vZ = v23[156] * ptVertex->tPos.vZ + v23[155] * ptVertex->tPos.vY;
          igi2_frame.Real32x3_Rotate_tTemp.vX = v25 + v24[85];
          v27 = v26 + v24[86];
          igi2_frame.Real32x3_Rotate_tTemp.vZ = igi2_frame.Real32x3_Rotate_tTemp.vZ + ptSplineObjSegment->atAreaPos[v21].vZ;
          v28 = v23[160] * ptVertex->tPos.vZ + v23[159] * ptVertex->tPos.vY;
          v29 = v23[163] * ptVertex->tPos.vZ + v23[162] * ptVertex->tPos.vY;
          igi2_frame.tEndPos.vZ = v23[166] * ptVertex->tPos.vZ + v23[165] * ptVertex->tPos.vY;
          igi2_frame.tEndPos.vX = v28 + v24[88];
          v30 = v29 + v24[89];
          igi2_frame.tEndPos.vZ = igi2_frame.tEndPos.vZ + ptSplineObjSegment->atAreaPos[v21 + 1].vZ;
          *(float *)&ptSource->nPrimitiveType = (igi2_frame.tEndPos.vX - igi2_frame.Real32x3_Rotate_tTemp.vX) * v22 + igi2_frame.Real32x3_Rotate_tTemp.vX;
          *(float *)&ptSource->nNumFaces = (v30 - v27) * v22 + v27;
          *(float *)&ptSource->nNumFaceGroups = (igi2_frame.tEndPos.vZ - igi2_frame.Real32x3_Rotate_tTemp.vZ) * v22 + igi2_frame.Real32x3_Rotate_tTemp.vZ;
          v31 = ptSplineObjSegment->atAreaOrientation[v21].tX.vZ * ptVertex->tNormal.vZ
              + v23[149] * ptVertex->tNormal.vY;
          v32 = v23[148] * ptVertex->tNormal.vX;
          ++ptVertex;
          igi2_frame.tDisplacement.vX = v31 + v32;
          igi2_frame.tDisplacement.vY = v23[153] * ptVertex[-1].tNormal.vZ
                           + v23[152] * ptVertex[-1].tNormal.vY
                           + v23[151] * ptVertex[-1].tNormal.vX;
          v33 = v23[156] * ptVertex[-1].tNormal.vZ + v23[155] * ptVertex[-1].tNormal.vY;
          v34 = v23[154] * ptVertex[-1].tNormal.vX;
          v35 = &ptSource->nNumVertices;
          ptSource->nNumVertices = LODWORD(igi2_frame.tDisplacement.vX);
          v35[1] = LODWORD(igi2_frame.tDisplacement.vY);
          igi2_frame.tDisplacement.vZ = v33 + v34;
          v35[2] = LODWORD(igi2_frame.tDisplacement.vZ);
          ptSource->ptFaceGroup = (struct RigidDirect3D_FaceGroup_t *)LODWORD(ptVertex[-1].tUV.vX);
          ptSource->ptVertexData = (struct Direct3DRender_VertexData_s *)LODWORD(ptVertex[-1].tUV.vY);
          v36 = ++igi2_frame.iVertex < v2->nNumVertices;
          ptSource = (struct Mesh3D_RenderMesh_RigidDirect3D_t *)((char *)ptSource + 32);
        }
        while ( v36 );
      }
    }
    Direct3D_atDynamicVertexBuffer[0].ptVertexBuffer->lpVtbl->Unlock(Direct3D_atDynamicVertexBuffer[0].ptVertexBuffer);
  }
  return igi2_frame.iDynamicVBOffset;
}

// source: e/3/pc/pc_direct3drender.c:2901  [size]
int __cdecl Direct3DRender_ProcessVerticesSplineLightmap(
        struct Mesh3D_RenderMesh_LightmapDirect3D_t *ptSource,
        struct SplineObjSegment_s *ptSplineObjSegment)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v1DivDeltaX; };
    struct { int v1DivDeltaXa; };
    struct { char igi2_o2[8]; int iVertex; };
    struct { char igi2_o3[12]; int iDynamicVBOffset; };
    struct { char igi2_o4[16]; struct real32x3_t Real32x3_Rotate_tTemp; };
    struct { char igi2_o5[28]; struct real32x3_t tDisplacement; };
    char igi2_extent[40];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Mesh3D_RenderMesh_LightmapDirect3D_t *v2; // ebp
  double vEndX; // st7
  struct LightmapDirect3D_Vertex_t *ptVertex; // ecx
  int nNumVertices; // edx
  int v6; // eax
  struct Mesh3D_RenderMesh_LightmapDirect3D_t *v7; // esi
  double v8; // st7
  double vY; // st6
  double vZ; // st5
  double v11; // rt1
  double v12; // st5
  double v13; // st6
  int v14; // esi
  char isFlip; // al
  double vStartX; // st7
  double v17; // st7
  double v18; // st6
  double v19; // st5
  int v20; // edx
  double v21; // st5
  float *v22; // eax
  float *v23; // esi
  double v24; // st4
  double v25; // st3
  double v26; // st4
  double v27; // st3
  double v28; // st2
  double v29; // st3
  bool v30; // cc

  v2 = ptSource;
  Direct3D_LockDynamicVertexBuffer(
    &Direct3D_atDynamicVertexBuffer[3],
    (void **)&ptSource,
    &igi2_frame.iDynamicVBOffset,
    ptSource->nNumVertices);
  if ( ptSource )
  {
    vEndX = ptSplineObjSegment->vEndX;
    ptVertex = v2->ptVertex;
    if ( ptSplineObjSegment->isLinear )
    {
      nNumVertices = v2->nNumVertices;
      v6 = 0;
      igi2_frame.tDisplacement.vX = (vEndX + ptSplineObjSegment->vStartX) * 0.5;
      if ( nNumVertices > 0 )
      {
        do
        {
          v7 = ptSource;
          v8 = ptVertex->tPos.vX - igi2_frame.tDisplacement.vX;
          ++v6;
          vY = ptVertex->tPos.vY;
          vZ = ptVertex->tPos.vZ;
          igi2_frame.Real32x3_Rotate_tTemp.vX = v8 * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tX.vX
                                   + vZ * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tX.vZ
                                   + vY * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tX.vY;
          igi2_frame.Real32x3_Rotate_tTemp.vY = v8 * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tY.vX
                                   + vZ * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tY.vZ
                                   + vY * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tY.vY;
          v11 = v8 * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vX;
          v12 = vZ * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vZ;
          v13 = vY * ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vY;
          ptSource->nPrimitiveType = LODWORD(igi2_frame.Real32x3_Rotate_tTemp.vX);
          v7->nNumLightmaps = LODWORD(igi2_frame.Real32x3_Rotate_tTemp.vY);
          igi2_frame.Real32x3_Rotate_tTemp.vZ = v11 + v12 + v13;
          v7->nNumFaces = LODWORD(igi2_frame.Real32x3_Rotate_tTemp.vZ);
          ptSource->nNumFaceGroups = LODWORD(ptVertex->tUV.vX);
          ptSource->nNumVertices = LODWORD(ptVertex->tUV.vY);
          ptSource->ptVertex = (struct LightmapDirect3D_Vertex_t *)LODWORD(ptVertex->tLightmapUV.vX);
          ptSource->ptLightmap = (struct LightmapDirect3D_Lightmap_t *)LODWORD(ptVertex->tLightmapUV.vY);
          v14 = v2->nNumVertices;
          ++ptVertex;
          ptSource = (struct Mesh3D_RenderMesh_LightmapDirect3D_t *)((char *)ptSource + 28);
        }
        while ( v6 < v14 );
      }
    }
    else
    {
      isFlip = ptSplineObjSegment->isFlip;
      igi2_frame.v1DivDeltaX = 1.0 / (vEndX - ptSplineObjSegment->vStartX);
      if ( isFlip )
        vStartX = ptSplineObjSegment->vEndX;
      else
        vStartX = ptSplineObjSegment->vStartX;
      v17 = -vStartX;
      v18 = (double)ptSplineObjSegment->nAreas * igi2_frame.v1DivDeltaX;
      if ( isFlip )
        v18 = -v18;
      igi2_frame.iVertex = 0;
      if ( v2->nNumVertices > 0 )
      {
        do
        {
          v19 = (v17 + ptVertex->tPos.vX) * v18;
          v20 = (__int64)v19;
          igi2_frame.v1DivDeltaXa = v20;
          if ( v20 == ptSplineObjSegment->nAreas )
            igi2_frame.v1DivDeltaXa = --v20;
          v21 = v19 - (double)igi2_frame.v1DivDeltaXa;
          if ( v21 >= 0.0 )
          {
            if ( v21 > 1.0 )
              v21 = 1.0;
          }
          else
          {
            v21 = 0.0;
          }
          v22 = (float *)(&ptSplineObjSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask + v20);
          v23 = (float *)((char *)ptSplineObjSegment + 12 * v20);
          v24 = v22[150] * ptVertex->tPos.vZ + v22[149] * ptVertex->tPos.vY;
          v25 = v22[153] * ptVertex->tPos.vZ + v22[152] * ptVertex->tPos.vY;
          igi2_frame.Real32x3_Rotate_tTemp.vZ = v22[156] * ptVertex->tPos.vZ + v22[155] * ptVertex->tPos.vY;
          igi2_frame.Real32x3_Rotate_tTemp.vX = v24 + v23[85];
          v26 = v25 + v23[86];
          igi2_frame.Real32x3_Rotate_tTemp.vZ = igi2_frame.Real32x3_Rotate_tTemp.vZ + ptSplineObjSegment->atAreaPos[v20].vZ;
          v27 = v22[160] * ptVertex->tPos.vZ + v22[159] * ptVertex->tPos.vY;
          v28 = v22[163] * ptVertex->tPos.vZ + v22[162] * ptVertex->tPos.vY;
          igi2_frame.tDisplacement.vZ = v22[166] * ptVertex->tPos.vZ + v22[165] * ptVertex->tPos.vY;
          igi2_frame.tDisplacement.vX = v27 + v23[88];
          v29 = v28 + v23[89];
          igi2_frame.tDisplacement.vZ = igi2_frame.tDisplacement.vZ + ptSplineObjSegment->atAreaPos[v20 + 1].vZ;
          *(float *)&ptSource->nPrimitiveType = (igi2_frame.tDisplacement.vX - igi2_frame.Real32x3_Rotate_tTemp.vX) * v21
                                              + igi2_frame.Real32x3_Rotate_tTemp.vX;
          *(float *)&ptSource->nNumLightmaps = (v29 - v26) * v21 + v26;
          *(float *)&ptSource->nNumFaces = (igi2_frame.tDisplacement.vZ - igi2_frame.Real32x3_Rotate_tTemp.vZ) * v21
                                         + igi2_frame.Real32x3_Rotate_tTemp.vZ;
          ptSource->nNumFaceGroups = LODWORD(ptVertex->tUV.vX);
          ptSource->nNumVertices = LODWORD(ptVertex->tUV.vY);
          ptSource->ptVertex = (struct LightmapDirect3D_Vertex_t *)LODWORD(ptVertex->tLightmapUV.vX);
          ptSource->ptLightmap = (struct LightmapDirect3D_Lightmap_t *)LODWORD(ptVertex->tLightmapUV.vY);
          ++ptVertex;
          v30 = ++igi2_frame.iVertex < v2->nNumVertices;
          ptSource = (struct Mesh3D_RenderMesh_LightmapDirect3D_t *)((char *)ptSource + 28);
        }
        while ( v30 );
      }
    }
    Direct3D_atDynamicVertexBuffer[3].ptVertexBuffer->lpVtbl->Unlock(Direct3D_atDynamicVertexBuffer[3].ptVertexBuffer);
  }
  return igi2_frame.iDynamicVBOffset;
}

// source: e/3/pc/pc_direct3drender.c:3108  [size]
struct Direct3DRender_BoneMesh_t *__cdecl Direct3DRender_MorphVerticesBone(
        struct Direct3DRender_BoneMesh_t *ptSource,
        struct Mesh3D_Morph_t *ptMorph,
        struct BoneDynCubeObj_s *ptBoneDynCubeObj)
{
  struct Direct3DRender_BoneMesh_t *v3; // ebx
  int v4; // esi
  int *v5; // ecx
  float *v6; // edx
  float *v7; // ecx
  float *i; // edx
  int v9; // edx
  unsigned int v10; // eax
  float *avMorphWeights; // edx
  struct Mesh3D_MorphVertex_t *atMorphVertices; // ecx
  struct Mesh3D_Morph_t *v13; // edi
  int v14; // ebp
  int j; // esi
  double v16; // st7
  int v17; // eax

  v3 = ptSource;
  if ( ptMorph )
  {
    v4 = 0;
    v5 = &ptMorph->anMorphChannelVertices[2];
    v6 = &ptBoneDynCubeObj->avMorphWeights[1];
    while ( *(v6 - 1) == 0.0 || !*(v5 - 2) )
    {
      if ( *v6 != 0.0 && *(v5 - 1) )
      {
        ++v4;
        break;
      }
      if ( v6[1] != 0.0 && *v5 )
      {
        v4 += 2;
        break;
      }
      if ( v6[2] != 0.0 && v5[1] )
      {
        v4 += 3;
        break;
      }
      if ( v6[3] != 0.0 && v5[2] )
      {
        v4 += 4;
        break;
      }
      if ( v6[4] != 0.0 && v5[3] )
      {
        v4 += 5;
        break;
      }
      if ( v6[5] != 0.0 && v5[4] )
      {
        v4 += 6;
        break;
      }
      if ( v6[6] != 0.0 && v5[5] )
      {
        v4 += 7;
        break;
      }
      v4 += 8;
      v6 += 8;
      v5 += 8;
      if ( v4 >= 16 )
        break;
    }
    if ( v4 != 16 )
    {
      if ( (struct Direct3DRender_BoneMesh_t *)dword_7A23134 == ptSource )
      {
        v7 = (float *)&unk_7A230F0;
        for ( i = ptBoneDynCubeObj->avMorphWeights;
              !*(_DWORD *)((char *)v7 + ((char *)ptMorph - (char *)&unk_7A230F0)) || *i == *v7;
              ++i )
        {
          if ( (int)++v7 >= 128069936 )
            return (struct Direct3DRender_BoneMesh_t *)&unk_7AB418C;
        }
      }
      if ( ptSource->nNumVertices <= 4096 )
      {
        qmemcpy(&unk_7AB418C, ptSource, 0x28u);
        dword_7AB41A4 = (int)&xmmword_7A28F10;
        memcpy(&xmmword_7A28F10, ptSource->ptVertexData, 16);
        LODWORD(xmmword_7A28F10) = flt_79FB0F0;
        v9 = 0;
        if ( ptSource->nNumVertices > 0 )
        {
          v10 = 0;
          do
          {
            qmemcpy(&flt_79FB0F0[v10 / 4], &v3->ptVertexData->ptVertex[v10 / 0x28], 0x28u);
            ++v9;
            v10 += 40;
          }
          while ( v9 < v3->nNumVertices );
        }
        avMorphWeights = ptBoneDynCubeObj->avMorphWeights;
        atMorphVertices = ptMorph->atMorphVertices;
        v13 = ptMorph;
        v14 = 16;
        do
        {
          *(int *)((char *)v13->anMorphChannelVertices + ((char *)(&unk_7A230F0) - (char *)(ptMorph))) = *(int *)avMorphWeights;
          if ( *avMorphWeights == 0.0 )
          {
            atMorphVertices += v13->anMorphChannelVertices[0];
          }
          else
          {
            for ( j = 0;
                  j < v13->anMorphChannelVertices[0];
                  flt_79FB0F8[10 * atMorphVertices[-1].iIndex] = atMorphVertices[-1].tDelta.vZ * *avMorphWeights
                                                               + flt_79FB0F8[10 * atMorphVertices[-1].iIndex] )
            {
              v16 = atMorphVertices->tDelta.vX * *avMorphWeights;
              v17 = 5 * atMorphVertices->iIndex;
              ++atMorphVertices;
              ++j;
              flt_79FB0F0[2 * v17] = v16 + flt_79FB0F0[2 * v17];
              flt_79FB0F4[10 * atMorphVertices[-1].iIndex] = atMorphVertices[-1].tDelta.vY * *avMorphWeights
                                                           + flt_79FB0F4[10 * atMorphVertices[-1].iIndex];
            }
          }
          ++avMorphWeights;
          v13 = (struct Mesh3D_Morph_t *)((char *)v13 + 4);
          --v14;
        }
        while ( v14 );
        return (struct Direct3DRender_BoneMesh_t *)&unk_7AB418C;
      }
    }
  }
  return ptSource;
}

// source: e/3/pc/pc_direct3drender.c:3217  [size]
int __cdecl Direct3DRender_ProcessVerticesBone(
        struct Direct3DRender_BoneMesh_t *ptSource,
        struct LODVirModel_s *ptLODVirModel,
        struct BoneDynCubeObj_s *ptBoneObj,
        int nLOD)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct Bone_s *v108; };
    struct { struct Bone_s *v109; };
    struct { char igi2_o2[4]; struct Direct3DRender_XYZNormalTex1Vertex_t *ptLockedVertex; };
    struct { char igi2_o3[8]; int iVertex; };
    struct { char igi2_o4[12]; int i; };
    struct { char igi2_o5[16]; int v113; };
    struct { char igi2_o6[20]; struct Direct3DRender_XYZNormalDiffuseTex1Vertex_t *ptLockedBloodyVertex; };
    struct { char igi2_o7[24]; unsigned int v115; };
    struct { char igi2_o8[28]; int iBone; };
    struct { char igi2_o9[32]; int v117; };
    struct { char igi2_o10[36]; int iDynamicVBOffset; };
    struct { char igi2_o11[40]; int v119; };
    struct { char igi2_o12[44]; struct real32x3_t tVertexPos; };
    struct { char igi2_o13[56]; struct real32x3_t Real32x3_Rotate_tTemp; };
    struct { char igi2_o14[68]; struct real32x3_t tRotatedPos; };
    struct { char igi2_o15[80]; float v123; };
    struct { char igi2_o16[84]; float v124; };
    struct { char igi2_o17[88]; float v125; };
    char igi2_extent[92];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Direct3DRender_BoneMesh_t *v4; // ebx
  int nNumVertices; // eax
  int v6; // eax
  int v7; // edx
  int v8; // esi
  struct Direct3DRender_BoneVertexData_t *ptVertexData; // edi
  struct Direct3DRender_BoneVertex_t *ptVertex; // eax
  struct real32x3_t *ptBones; // edi
  double vX; // st7
  struct Direct3DRender_BoneVertex_t *v13; // ecx
  int iBones; // eax
  double v15; // st7
  struct real32x3_t *v16; // edi
  double v17; // st6
  double v18; // st5
  int v19; // ecx
  struct Bone_s *v20; // eax
  double v21; // st7
  struct Bone_s *patBone; // edi
  struct Direct3DRender_BoneVertex_t *v23; // eax
  double v24; // st7
  float *p_vX; // ecx
  double v26; // st7
  double v27; // st6
  struct real32x3_t *p_tNormal; // eax
  struct Direct3DRender_BoneVertex_t *v29; // ecx
  int v30; // ecx
  int v32; // eax
  int v33; // ecx
  struct Direct3DRender_BoneVertexData_t *v34; // edi
  double v35; // st7
  struct Direct3DRender_BoneVertex_t *v36; // eax
  int v37; // esi
  int v38; // ecx
  int v39; // ebp
  struct real32x3_t *v40; // ebx
  char v41; // di
  int v42; // edx
  double v43; // st6
  double v44; // st5
  struct real32x3_t *v45; // ecx
  double v46; // st4
  double v47; // st3
  float *v48; // ecx
  double v49; // st5
  double v50; // st4
  unsigned int v51; // edx
  double v52; // st7
  double v53; // st6
  double v54; // st5
  struct real32x3_t *v55; // ecx
  double v56; // st4
  double v57; // st3
  float *v58; // ecx
  double v59; // st5
  double v60; // st4
  unsigned int v61; // edx
  double v62; // st7
  double v63; // st6
  double v64; // st5
  struct real32x3_t *v65; // ecx
  double v66; // st4
  double v67; // st3
  float *v68; // ecx
  double v69; // st5
  double v70; // st4
  unsigned int v71; // edx
  double v72; // st7
  double v73; // st6
  double v74; // st5
  struct real32x3_t *v75; // ecx
  double v76; // st4
  double v77; // st3
  float *v78; // ecx
  double v79; // st5
  double v80; // st4
  bool v81; // cc
  double v82; // st6
  char v83; // cl
  int v84; // edx
  double v85; // st5
  double v86; // st4
  int v87; // edi
  double v88; // st3
  double v89; // st2
  float *v90; // edx
  double v91; // st4
  double v92; // st3
  int v93; // edx
  struct Bone_s *v94; // ebp
  float *v95; // eax
  int v96; // ecx
  double vY; // st7
  float *v98; // ecx
  double v99; // st7
  unsigned int v100; // esi
  double v101; // st6
  double v102; // st7
  double v103; // st6
  float *v104; // ecx
  int v105; // eax
  struct Direct3DRender_BoneVertex_t *v106; // ecx
  int v107; // ecx

  v4 = ptSource;
  nNumVertices = ptSource->nNumVertices;
  if ( nNumVertices > 4000 )
  {
    LDebug_Error(
      "Bone model too large. Model %s has %d vertices.",
      ptLODVirModel->zFirstVirModelName,
      ptSource->nNumVertices);
    abort();
  }
  if ( nLOD )
  {
    Direct3D_LockDynamicVertexBuffer(
      Direct3D_atDynamicVertexBuffer,
      (void **)&igi2_frame.ptLockedVertex,
      &igi2_frame.iDynamicVBOffset,
      nNumVertices);
    v6 = ptSource->nNumVertices;
    igi2_frame.iVertex = 0;
    if ( v6 > 0 )
    {
      v7 = 0;
      v8 = 0;
      do
      {
        ptVertexData = ptSource->ptVertexData;
        ptVertex = ptVertexData->ptVertex;
        ptBones = ptVertexData->ptBones;
        vX = ptVertex[v8].tVertex.tPos.vX;
        v13 = &ptVertex[v8];
        iBones = (unsigned __int8)ptVertex[v8].iBones;
        v15 = vX - ptBones[iBones].vX;
        v16 = &ptBones[iBones];
        v17 = v13->tVertex.tPos.vY - v16->vY;
        v18 = v13->tVertex.tPos.vZ - v16->vZ;
        v19 = iBones;
        v20 = &ptBoneObj->patBone[iBones];
        igi2_frame.tRotatedPos.vX = v18 * v20->tMatrix.tX.vZ + v17 * v20->tMatrix.tX.vY + v15 * v20->tMatrix.tX.vX;
        igi2_frame.tRotatedPos.vY = v18 * v20->tMatrix.tY.vZ + v17 * v20->tMatrix.tY.vY + v15 * v20->tMatrix.tY.vX;
        v21 = v18 * v20->tMatrix.tZ.vZ + v17 * v20->tMatrix.tZ.vY + v15 * v20->tMatrix.tZ.vX;
        igi2_frame.ptLockedVertex[v7].tPos.vX = igi2_frame.tRotatedPos.vX + v20->tTranslation.vX;
        igi2_frame.ptLockedVertex[v7].tPos.vY = igi2_frame.tRotatedPos.vY + ptBoneObj->patBone[v19].tTranslation.vY;
        igi2_frame.ptLockedVertex[v7].tPos.vZ = v21 + ptBoneObj->patBone[v19].tTranslation.vZ;
        patBone = ptBoneObj->patBone;
        v23 = &ptSource->ptVertexData->ptVertex[v8];
        v24 = patBone[v19].tMatrix.tX.vZ * v23->tVertex.tNormal.vZ;
        p_vX = &patBone[v19].tTranslation.vX;
        igi2_frame.v123 = v24 + p_vX[4] * v23->tVertex.tNormal.vX + p_vX[5] * v23->tVertex.tNormal.vY;
        igi2_frame.v124 = p_vX[9] * v23->tVertex.tNormal.vZ + p_vX[7] * v23->tVertex.tNormal.vX + p_vX[8] * v23->tVertex.tNormal.vY;
        ++v8;
        v26 = p_vX[12] * v23->tVertex.tNormal.vZ + p_vX[10] * v23->tVertex.tNormal.vX;
        v27 = p_vX[11] * v23->tVertex.tNormal.vY;
        p_tNormal = &igi2_frame.ptLockedVertex[v7].tNormal;
        p_tNormal->vX = igi2_frame.v123;
        p_tNormal->vY = igi2_frame.v124;
        ++v7;
        igi2_frame.v125 = v26 + v27;
        p_tNormal->vZ = igi2_frame.v125;
        v29 = ptSource->ptVertexData->ptVertex;
        igi2_frame.ptLockedVertex[v7 - 1].tUV.vX = v29[v8 - 1].tVertex.tUV.vX;
        igi2_frame.ptLockedVertex[v7 - 1].tUV.vY = v29[v8 - 1].tVertex.tUV.vY;
        v30 = ptSource->nNumVertices;
        ++igi2_frame.iVertex;
      }
      while ( igi2_frame.iVertex < v30 );
    }
    Direct3D_atDynamicVertexBuffer[0].ptVertexBuffer->lpVtbl->Unlock(Direct3D_atDynamicVertexBuffer[0].ptVertexBuffer);
    return igi2_frame.iDynamicVBOffset;
  }
  else
  {
    Direct3D_LockDynamicVertexBuffer(
      &Direct3D_atDynamicVertexBuffer[4],
      (void **)&igi2_frame.ptLockedBloodyVertex,
      &igi2_frame.iDynamicVBOffset,
      nNumVertices);
    v32 = ptSource->nNumVertices;
    v33 = 0;
    igi2_frame.iVertex = 0;
    if ( v32 > 0 )
    {
      igi2_frame.v117 = 0;
      igi2_frame.v115 = 0;
      while ( 1 )
      {
        v34 = v4->ptVertexData;
        v35 = 0.0;
        v36 = &v34->ptVertex[igi2_frame.v115 / 0x28];
        v37 = (v34->pbBoneCount[v33 / 16] >> (2 * (v33 % 16))) & 3;
        v38 = (unsigned __int8)v36->iBones;
        v39 = 0;
        memset(&igi2_frame.tVertexPos, 0, sizeof(igi2_frame.tVertexPos));
        igi2_frame.iBone = v38;
        igi2_frame.i = 0;
        if ( v37 + 1 >= 4 )
        {
          v40 = v34->ptBones;
          igi2_frame.v108 = ptBoneObj->patBone;
          igi2_frame.v113 = 3;
          v41 = 16;
          do
          {
            v42 = (unsigned __int8)(v36->iBones >> (v41 - 16));
            if ( v39 == v37 )
            {
              v43 = 1.0 - v35;
            }
            else
            {
              igi2_frame.v119 = (unsigned __int8)(v36->iWeights >> (v41 - 16));
              v43 = (double)igi2_frame.v119 * 0.003921568859368563;
              v39 = igi2_frame.i;
            }
            v44 = v36->tVertex.tPos.vX - v40[v42].vX;
            v45 = &v40[v42];
            v46 = v36->tVertex.tPos.vY - v45->vY;
            v47 = v36->tVertex.tPos.vZ - v45->vZ;
            v48 = &igi2_frame.v108[v42].tTranslation.vX;
            igi2_frame.Real32x3_Rotate_tTemp.vX = v47 * v48[6] + v46 * v48[5] + v44 * v48[4];
            igi2_frame.tRotatedPos.vX = igi2_frame.Real32x3_Rotate_tTemp.vX;
            igi2_frame.Real32x3_Rotate_tTemp.vY = v47 * v48[9] + v46 * v48[8] + v44 * v48[7];
            igi2_frame.tRotatedPos.vY = igi2_frame.Real32x3_Rotate_tTemp.vY;
            igi2_frame.Real32x3_Rotate_tTemp.vZ = v47 * v48[12] + v46 * v48[11] + v44 * v48[10];
            igi2_frame.tRotatedPos.vZ = igi2_frame.Real32x3_Rotate_tTemp.vZ;
            v49 = igi2_frame.Real32x3_Rotate_tTemp.vX + *v48;
            v50 = igi2_frame.Real32x3_Rotate_tTemp.vY + v48[1];
            v51 = v36->iBones >> (v41 - 8);
            igi2_frame.tRotatedPos.vZ = igi2_frame.Real32x3_Rotate_tTemp.vZ + v48[2];
            igi2_frame.tVertexPos.vX = v49 * v43 + igi2_frame.tVertexPos.vX;
            igi2_frame.tVertexPos.vY = v50 * v43 + igi2_frame.tVertexPos.vY;
            igi2_frame.tVertexPos.vZ = igi2_frame.tRotatedPos.vZ * v43 + igi2_frame.tVertexPos.vZ;
            v52 = v35 + v43;
            if ( igi2_frame.v113 - 2 == v37 )
            {
              v53 = 1.0 - v52;
            }
            else
            {
              igi2_frame.v119 = (unsigned __int8)(v36->iWeights >> (v41 - 8));
              v53 = (double)igi2_frame.v119 * 0.003921568859368563;
              v39 = igi2_frame.i;
            }
            v54 = v36->tVertex.tPos.vX - v40[(unsigned __int8)v51].vX;
            v55 = &v40[(unsigned __int8)v51];
            v56 = v36->tVertex.tPos.vY - v55->vY;
            v57 = v36->tVertex.tPos.vZ - v55->vZ;
            v58 = &igi2_frame.v108[(unsigned __int8)v51].tTranslation.vX;
            igi2_frame.Real32x3_Rotate_tTemp.vX = v57 * v58[6] + v56 * v58[5] + v54 * v58[4];
            igi2_frame.tRotatedPos.vX = igi2_frame.Real32x3_Rotate_tTemp.vX;
            igi2_frame.Real32x3_Rotate_tTemp.vY = v57 * v58[9] + v56 * v58[8] + v54 * v58[7];
            igi2_frame.tRotatedPos.vY = igi2_frame.Real32x3_Rotate_tTemp.vY;
            igi2_frame.Real32x3_Rotate_tTemp.vZ = v57 * v58[12] + v56 * v58[11] + v54 * v58[10];
            igi2_frame.tRotatedPos.vZ = igi2_frame.Real32x3_Rotate_tTemp.vZ;
            v59 = igi2_frame.Real32x3_Rotate_tTemp.vX + *v58;
            v60 = igi2_frame.Real32x3_Rotate_tTemp.vY + v58[1];
            v61 = v36->iBones >> v41;
            igi2_frame.tRotatedPos.vZ = igi2_frame.Real32x3_Rotate_tTemp.vZ + v58[2];
            igi2_frame.tVertexPos.vX = v59 * v53 + igi2_frame.tVertexPos.vX;
            igi2_frame.tVertexPos.vY = v60 * v53 + igi2_frame.tVertexPos.vY;
            igi2_frame.tVertexPos.vZ = igi2_frame.tRotatedPos.vZ * v53 + igi2_frame.tVertexPos.vZ;
            v62 = v52 + v53;
            if ( igi2_frame.v113 - 1 == v37 )
            {
              v63 = 1.0 - v62;
            }
            else
            {
              igi2_frame.v119 = (unsigned __int8)(v36->iWeights >> v41);
              v63 = (double)igi2_frame.v119 * 0.003921568859368563;
              v39 = igi2_frame.i;
            }
            v64 = v36->tVertex.tPos.vX - v40[(unsigned __int8)v61].vX;
            v65 = &v40[(unsigned __int8)v61];
            v66 = v36->tVertex.tPos.vY - v65->vY;
            v67 = v36->tVertex.tPos.vZ - v65->vZ;
            v68 = &igi2_frame.v108[(unsigned __int8)v61].tTranslation.vX;
            igi2_frame.Real32x3_Rotate_tTemp.vX = v67 * v68[6] + v66 * v68[5] + v64 * v68[4];
            igi2_frame.tRotatedPos.vX = igi2_frame.Real32x3_Rotate_tTemp.vX;
            igi2_frame.Real32x3_Rotate_tTemp.vY = v67 * v68[9] + v66 * v68[8] + v64 * v68[7];
            igi2_frame.tRotatedPos.vY = igi2_frame.Real32x3_Rotate_tTemp.vY;
            igi2_frame.Real32x3_Rotate_tTemp.vZ = v67 * v68[12] + v66 * v68[11] + v64 * v68[10];
            igi2_frame.tRotatedPos.vZ = igi2_frame.Real32x3_Rotate_tTemp.vZ;
            v69 = igi2_frame.Real32x3_Rotate_tTemp.vX + *v68;
            v70 = igi2_frame.Real32x3_Rotate_tTemp.vY + v68[1];
            v71 = v36->iBones >> (v41 + 8);
            igi2_frame.tRotatedPos.vZ = igi2_frame.Real32x3_Rotate_tTemp.vZ + v68[2];
            igi2_frame.tVertexPos.vX = v69 * v63 + igi2_frame.tVertexPos.vX;
            igi2_frame.tVertexPos.vY = v70 * v63 + igi2_frame.tVertexPos.vY;
            igi2_frame.tVertexPos.vZ = igi2_frame.tRotatedPos.vZ * v63 + igi2_frame.tVertexPos.vZ;
            v72 = v62 + v63;
            if ( igi2_frame.v113 == v37 )
            {
              v73 = 1.0 - v72;
            }
            else
            {
              igi2_frame.v119 = (unsigned __int8)(v36->iWeights >> (v41 + 8));
              v73 = (double)igi2_frame.v119 * 0.003921568859368563;
              v39 = igi2_frame.i;
            }
            v74 = v36->tVertex.tPos.vX - v40[(unsigned __int8)v71].vX;
            v75 = &v40[(unsigned __int8)v71];
            v76 = v36->tVertex.tPos.vY - v75->vY;
            v39 += 4;
            v77 = v36->tVertex.tPos.vZ - v75->vZ;
            v78 = &igi2_frame.v108[(unsigned __int8)v71].tTranslation.vX;
            v41 += 32;
            igi2_frame.i = v39;
            igi2_frame.Real32x3_Rotate_tTemp.vX = v77 * v78[6] + v76 * v78[5] + v74 * v78[4];
            igi2_frame.tRotatedPos.vX = igi2_frame.Real32x3_Rotate_tTemp.vX;
            igi2_frame.Real32x3_Rotate_tTemp.vY = v77 * v78[9] + v76 * v78[8] + v74 * v78[7];
            igi2_frame.tRotatedPos.vY = igi2_frame.Real32x3_Rotate_tTemp.vY;
            igi2_frame.Real32x3_Rotate_tTemp.vZ = v77 * v78[12] + v76 * v78[11] + v74 * v78[10];
            igi2_frame.tRotatedPos.vZ = igi2_frame.Real32x3_Rotate_tTemp.vZ;
            v79 = igi2_frame.Real32x3_Rotate_tTemp.vX + *v78;
            v80 = igi2_frame.Real32x3_Rotate_tTemp.vY + v78[1];
            v81 = igi2_frame.v113 + 4 < v37;
            igi2_frame.tRotatedPos.vZ = igi2_frame.Real32x3_Rotate_tTemp.vZ + v78[2];
            igi2_frame.v113 += 4;
            igi2_frame.tVertexPos.vX = v79 * v73 + igi2_frame.tVertexPos.vX;
            igi2_frame.tVertexPos.vY = v80 * v73 + igi2_frame.tVertexPos.vY;
            igi2_frame.tVertexPos.vZ = igi2_frame.tRotatedPos.vZ * v73 + igi2_frame.tVertexPos.vZ;
            v35 = v72 + v73;
          }
          while ( v81 );
          v38 = igi2_frame.iBone;
          v4 = ptSource;
        }
        if ( v39 <= v37 )
        {
          v82 = igi2_frame.tVertexPos.vX;
          igi2_frame.i = (int)v4->ptVertexData->ptBones;
          igi2_frame.v109 = ptBoneObj->patBone;
          v83 = 8 * v39;
          igi2_frame.v113 = 8 * v39;
          do
          {
            v84 = (unsigned __int8)(v36->iBones >> v83);
            if ( v39 == v37 )
            {
              v85 = 1.0 - v35;
            }
            else
            {
              igi2_frame.v119 = (unsigned __int8)(v36->iWeights >> v83);
              v85 = (double)igi2_frame.v119 * 0.003921568859368563;
            }
            v86 = v36->tVertex.tPos.vX - *(float *)(igi2_frame.i + 12 * v84);
            v87 = igi2_frame.i + 12 * v84;
            v88 = v36->tVertex.tPos.vY - *(float *)(v87 + 4);
            v89 = v36->tVertex.tPos.vZ - *(float *)(v87 + 8);
            v90 = &igi2_frame.v109[v84].tTranslation.vX;
            ++v39;
            igi2_frame.Real32x3_Rotate_tTemp.vX = v89 * v90[6] + v88 * v90[5] + v86 * v90[4];
            igi2_frame.tRotatedPos.vX = igi2_frame.Real32x3_Rotate_tTemp.vX;
            igi2_frame.Real32x3_Rotate_tTemp.vY = v89 * v90[9] + v88 * v90[8] + v86 * v90[7];
            igi2_frame.tRotatedPos.vY = igi2_frame.Real32x3_Rotate_tTemp.vY;
            igi2_frame.Real32x3_Rotate_tTemp.vZ = v89 * v90[12] + v88 * v90[11] + v86 * v90[10];
            igi2_frame.tRotatedPos.vZ = igi2_frame.Real32x3_Rotate_tTemp.vZ;
            v91 = igi2_frame.Real32x3_Rotate_tTemp.vX + *v90;
            v83 = igi2_frame.v113 + 8;
            v92 = igi2_frame.Real32x3_Rotate_tTemp.vY + v90[1];
            igi2_frame.v113 += 8;
            igi2_frame.tRotatedPos.vZ = igi2_frame.Real32x3_Rotate_tTemp.vZ + v90[2];
            v82 = v82 + v91 * v85;
            igi2_frame.tVertexPos.vY = v92 * v85 + igi2_frame.tVertexPos.vY;
            igi2_frame.tVertexPos.vZ = igi2_frame.tRotatedPos.vZ * v85 + igi2_frame.tVertexPos.vZ;
            v35 = v35 + v85;
          }
          while ( v39 <= v37 );
          v38 = igi2_frame.iBone;
          igi2_frame.tVertexPos.vX = v82;
        }
        v93 = igi2_frame.v117;
        *(struct real32x3_t *)((char *)&igi2_frame.ptLockedBloodyVertex->tPos + igi2_frame.v117) = igi2_frame.tVertexPos;
        v94 = ptBoneObj->patBone;
        v95 = &v4->ptVertexData->ptVertex[igi2_frame.v115 / 0x28].tVertex.tPos.vX;
        v96 = v38;
        vY = v94[v96].tMatrix.tX.vY;
        v98 = &v94[v96].tTranslation.vX;
        v99 = vY * v95[4];
        v101 = v98[6];
        igi2_frame.v115 += 40;
        v100 = igi2_frame.v115;
        igi2_frame.v123 = v99 + v101 * v95[5] + v98[4] * v95[3];
        igi2_frame.v124 = v98[8] * v95[4] + v98[9] * v95[5] + v98[7] * v95[3];
        v102 = v98[11] * v95[4] + v98[12] * v95[5];
        v103 = v98[10] * v95[3];
        v104 = (float *)((char *)&igi2_frame.ptLockedBloodyVertex->tNormal.vX + v93);
        *v104 = igi2_frame.v123;
        v104[1] = igi2_frame.v124;
        igi2_frame.v125 = v102 + v103;
        v104[2] = igi2_frame.v125;
        v105 = igi2_frame.iVertex;
        *(unsigned int *)((char *)&igi2_frame.ptLockedBloodyVertex->bDiffuse + v93) = ptBoneObj->abBloodStains[igi2_frame.iVertex];
        v106 = v4->ptVertexData->ptVertex;
        *(float *)((char *)&igi2_frame.ptLockedBloodyVertex->tUV.vX + v93) = *(float *)((char *)v106 + v100 - 16);
        *(float *)((char *)&igi2_frame.ptLockedBloodyVertex->tUV.vY + v93) = *(float *)((char *)v106 + v100 - 12);
        v107 = v4->nNumVertices;
        igi2_frame.iVertex = v105 + 1;
        igi2_frame.v117 = v93 + 36;
        if ( v105 + 1 >= v107 )
          break;
        v33 = igi2_frame.iVertex;
      }
    }
    Direct3D_atDynamicVertexBuffer[4].ptVertexBuffer->lpVtbl->Unlock(Direct3D_atDynamicVertexBuffer[4].ptVertexBuffer);
    return igi2_frame.iDynamicVBOffset;
  }
}

// source: e/3/pc/pc_direct3drender.c  [override: the original skins bone vertices with SSE
// intrinsics the decompiler cannot express; the x87 path computes the same transform]
long __cdecl Direct3DRender_ProcessVerticesBone_SSE(struct Direct3DRender_BoneMesh_t *ptSource,
                                                    struct LODVirModel_s *ptLODVirModel,
                                                    struct BoneDynCubeObj_s *ptBoneObj, long iLOD)
{
  return Direct3DRender_ProcessVerticesBone(ptSource, ptLODVirModel, ptBoneObj, iLOD);
}

// source: e/3/pc/pc_direct3drender.c:3592  [size~]
struct VirModel_s *__cdecl Direct3DRender_DrawRigidFacegroup(
        struct RigidDirect3D_FaceGroup_t *ptFaceGroup,
        struct VirModel_s *ptVirModel,
        enum bool isIndexed,
        int iStartVertex)
{
  #pragma pack(push, 1)
  union
  {
    struct { unsigned int nNumFaces; };
    struct { char igi2_o1[8]; struct real32x3_t *ptPos[2]; };
    char igi2_extent[76];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v4; // ecx
  struct RenderStateBlock_t *v6; // eax
  unsigned __int8 bMaterialProperties; // al
  int v8; // ecx
  bool v9; // zf
  struct RenderStateBlock_t *v10; // eax
  int eCurrentState; // edx
  int v12; // ecx
  unsigned __int16 iTexture; // ax
  struct IDirect3DBaseTexture8 *ptDirect3DBaseTexture; // eax
  unsigned __int16 iEnvMap; // ax
  struct TexInfo_s *v16; // edi
  struct IDirect3DDevice8Vtbl *lpVtbl; // ecx
  struct VirModel_s *result; // eax

  v4 = Direct3DRender_eTextureStateRigid;
  v6 = Direct3D_ptTextureStateBlock;
  if ( Direct3D_ptTextureStateBlock->eCurrentState != Direct3DRender_eTextureStateRigid )
  {
    Direct3D_ptTextureStateBlock->eCurrentState = Direct3DRender_eTextureStateRigid;
    v6->atRenderState[v4].pfCallback(nullptr);
  }
  bMaterialProperties = ptFaceGroup->bMaterialProperties;
  if ( (ptFaceGroup->bMaterialProperties & 0x40) != 0 )
  {
    v8 = Direct3DRender_eBlendStateAlphaTest;
LABEL_12:
    v10 = Direct3D_ptBlendStateBlock;
    eCurrentState = Direct3D_ptBlendStateBlock->eCurrentState;
LABEL_13:
    if ( eCurrentState != v8 )
    {
      v10->eCurrentState = v8;
      v10->atRenderState[v8].pfCallback(nullptr);
    }
    goto LABEL_15;
  }
  if ( (bMaterialProperties & 4) == 0 )
  {
    v8 = Direct3DRender_eBlendStateOpaque;
    goto LABEL_12;
  }
  v9 = (bMaterialProperties & 1) == 0;
  v10 = Direct3D_ptBlendStateBlock;
  eCurrentState = Direct3D_ptBlendStateBlock->eCurrentState;
  if ( v9 )
  {
    v8 = Direct3DRender_eBlendStateTransparent;
    goto LABEL_13;
  }
  v12 = Direct3DRender_eBlendStateAdditive;
  if ( eCurrentState != Direct3DRender_eBlendStateAdditive )
  {
    Direct3D_ptBlendStateBlock->eCurrentState = Direct3DRender_eBlendStateAdditive;
    v10->atRenderState[v12].pfCallback(nullptr);
  }
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_LIGHTING, 0);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLOROP, 2u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGENABLE, 0);
LABEL_15:
  iTexture = ptFaceGroup->iTexture;
  if ( iTexture == 0xFFFF )
  {
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLOROP, 3u);
    if ( Direct3D_tState.aptTexture[0] )
    {
      Direct3D_tState.aptTexture[0] = nullptr;
      Direct3D_ptDevice->lpVtbl->SetTexture(Direct3D_ptDevice, 0, nullptr);
    }
  }
  else
  {
    ptDirect3DBaseTexture = ptVirModel->pptTexInfo[iTexture]->ptDirect3DBaseTexture;
    if ( ptDirect3DBaseTexture != Direct3D_tState.aptTexture[0] )
    {
      Direct3D_tState.aptTexture[0] = ptDirect3DBaseTexture;
      Direct3D_ptDevice->lpVtbl->SetTexture(Direct3D_ptDevice, 0, ptDirect3DBaseTexture);
    }
    iEnvMap = ptFaceGroup->iEnvMap;
    if ( iEnvMap != 0xFFFF && ((ptFaceGroup->bMaterialProperties & 0x20) == 0 || !LODWORD(Direct3D_vOverlayMaxZ)) )
    {
      v16 = ptVirModel->pptTexInfo[iEnvMap];
      Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_NORMALIZENORMALS, 1u);
      if ( v16->ptDirect3DBaseTexture != Direct3D_tState.aptTexture[1] )
      {
        Direct3D_tState.aptTexture[1] = v16->ptDirect3DBaseTexture;
        Direct3D_ptDevice->lpVtbl->SetTexture(Direct3D_ptDevice, 1u, Direct3D_tState.aptTexture[1]);
      }
      Direct3D_ptDevice->lpVtbl->SetRenderState(
        Direct3D_ptDevice,
        D3DRS_TEXTUREFACTOR,
        ((unsigned int)(__int64)((double)ptFaceGroup->nReflectivity * 255.0) << 24) | 0xFFFFFF);
      Direct3D_ptDevice->lpVtbl->SetTextureStageState(
        Direct3D_ptDevice,
        1u,
        D3DTSS_COLOROP,
        (ptFaceGroup->bMaterialProperties & 0x20) != 0 ? 16 : 14);
      Direct3D_D3DMATRIXFromReal32x9((struct _D3DMATRIX *)&igi2_frame.ptPos[1], &TransContext_tActiveTransContext.tMatrix, nullptr);
      Direct3D_ptDevice->lpVtbl->SetTransform(Direct3D_ptDevice, D3DTS_TEXTURE1, (struct _D3DMATRIX *)&igi2_frame.ptPos[1]);
    }
  }
  lpVtbl = Direct3D_ptDevice->lpVtbl;
  igi2_frame.nNumFaces = ptFaceGroup->nNumFaces;
  if ( isIndexed )
    result = (struct VirModel_s *)lpVtbl->DrawIndexedPrimitive(
                                    Direct3D_ptDevice,
                                    D3DPT_TRIANGLELIST,
                                    ptFaceGroup->iStartVertex,
                                    ptFaceGroup->nNumVertices,
                                    ptFaceGroup->iStartIndex,
                                    igi2_frame.nNumFaces);
  else
    result = (struct VirModel_s *)lpVtbl->DrawPrimitive(Direct3D_ptDevice, D3DPT_TRIANGLELIST, iStartVertex, igi2_frame.nNumFaces);
  if ( ptFaceGroup->iTexture == 0xFFFF )
  {
    result = (struct VirModel_s *)Direct3D_ptDevice->lpVtbl->SetTextureStageState(
                                    Direct3D_ptDevice,
                                    0,
                                    D3DTSS_COLOROP,
                                    4u);
  }
  else if ( ptFaceGroup->iEnvMap != 0xFFFF
         && ((ptFaceGroup->bMaterialProperties & 0x20) == 0
          || (result = (struct VirModel_s *)LODWORD(Direct3D_vOverlayMaxZ)) == nullptr) )
  {
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_NORMALIZENORMALS, 0);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAOP, 3u);
    result = (struct VirModel_s *)Direct3D_ptDevice->lpVtbl->SetTextureStageState(
                                    Direct3D_ptDevice,
                                    1u,
                                    D3DTSS_COLOROP,
                                    1u);
  }
  if ( (ptFaceGroup->bMaterialProperties & 1) != 0 )
  {
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_LIGHTING, 1u);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLOROP, 4u);
    return (struct VirModel_s *)Direct3D_ptDevice->lpVtbl->SetRenderState(
                                  Direct3D_ptDevice,
                                  D3DRS_FOGENABLE,
                                  QVertex_isFog);
  }
  return result;
}

// source: e/3/pc/pc_direct3drender.c:3701  [size]
void __cdecl Direct3DRender_DrawSortedFaceGroup_Spline(struct SplineDirect3D_SortedFaceGroup_t *ptSortedFaceGroup)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vRadius; };
    struct { char igi2_o1[20]; struct real64x3_t tPos; };
    struct { char igi2_o2[44]; struct real32x9_t tTempMatrix; };
    struct { char igi2_o3[84]; struct _D3DMATRIX tLocalMatrix; };
    char igi2_extent[148];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct RenderStateBlock_t *v1; // eax
  int v2; // ecx
  struct VirModel_s *ptVirModel; // ebp
  struct RigidDirect3D_FaceGroup_t *ptFaceGroup; // esi
  struct RenderStateBlock_t *v5; // eax
  int v6; // ecx
  struct RenderStateBlock_t *v7; // eax
  int v8; // ecx
  struct Mesh3D_Mesh_t *ptMesh; // eax
  double v10; // st7
  double vY; // st6
  int v12; // edi

  if ( ptSortedFaceGroup )
  {
    v1 = Direct3D_ptTextureStateBlock;
    v2 = Direct3DRender_eTextureStateRigid;
    ptVirModel = ptSortedFaceGroup->ptVirModel;
    ptFaceGroup = ptSortedFaceGroup->ptFaceGroup;
    if ( Direct3D_ptTextureStateBlock->eCurrentState != Direct3DRender_eTextureStateRigid )
    {
      Direct3D_ptTextureStateBlock->eCurrentState = Direct3DRender_eTextureStateRigid;
      v1->atRenderState[v2].pfCallback(nullptr);
    }
    v5 = Direct3D_ptGenericStateBlock;
    v6 = Direct3DRender_eGenericStateRigid;
    if ( Direct3D_ptGenericStateBlock->eCurrentState != Direct3DRender_eGenericStateRigid )
    {
      Direct3D_ptGenericStateBlock->eCurrentState = Direct3DRender_eGenericStateRigid;
      v5->atRenderState[v6].pfCallback(nullptr);
    }
    v7 = Direct3D_ptClippingStateBlock;
    v8 = Direct3D_eClippingStateOn;
    if ( Direct3D_ptClippingStateBlock->eCurrentState != Direct3D_eClippingStateOn )
    {
      Direct3D_ptClippingStateBlock->eCurrentState = Direct3D_eClippingStateOn;
      v7->atRenderState[v8].pfCallback(nullptr);
    }
    ptMesh = ptSortedFaceGroup->ptVirModel->ptModel->ptMesh;
    igi2_frame.vRadius = ptMesh->tRenderMeshSphere.vRadius;
    igi2_frame.tPos.vX = ptMesh->tRenderMeshSphere.tPos.vX + ptSortedFaceGroup->tPos.vX;
    igi2_frame.tPos.vY = ptMesh->tRenderMeshSphere.tPos.vY + ptSortedFaceGroup->tPos.vY;
    igi2_frame.tPos.vZ = ptMesh->tRenderMeshSphere.tPos.vZ + ptSortedFaceGroup->tPos.vZ;
    Direct3DRender_SetFogParameters(&igi2_frame.tPos, igi2_frame.vRadius);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZWRITEENABLE, 0);
    Direct3D_ptDevice->lpVtbl->SetRenderState(
      Direct3D_ptDevice,
      D3DRS_TEXTUREFACTOR,
      (-1 - ptFaceGroup->nTransparency) << 24);
    v10 = ptSortedFaceGroup->tPos.vX - TransContext_tActiveTransContext.tPos.vX;
    vY = ptSortedFaceGroup->tPos.vY;
    igi2_frame.tTempMatrix.nOps = 0;
    *(float *)&igi2_frame.tPos.vY = ptSortedFaceGroup->tPos.vZ - TransContext_tActiveTransContext.tPos.vZ;
    *(float *)&igi2_frame.tPos.vX = Direct3D_vScale * v10;
    *((float *)&igi2_frame.tPos.vX + 1) = Direct3D_vScale * (vY - TransContext_tActiveTransContext.tPos.vY);
    *(float *)&igi2_frame.tPos.vY = Direct3D_vScale * *(float *)&igi2_frame.tPos.vY;
    igi2_frame.tTempMatrix.tX.vX = Direct3D_vScale;
    igi2_frame.tTempMatrix.tX.vY = Direct3D_vScale * 0.0;
    igi2_frame.tTempMatrix.tX.vZ = igi2_frame.tTempMatrix.tX.vY;
    igi2_frame.tTempMatrix.tY.vX = igi2_frame.tTempMatrix.tX.vY;
    igi2_frame.tTempMatrix.tY.vY = Direct3D_vScale;
    igi2_frame.tTempMatrix.tY.vZ = igi2_frame.tTempMatrix.tX.vY;
    igi2_frame.tTempMatrix.tZ.vX = igi2_frame.tTempMatrix.tX.vY;
    igi2_frame.tTempMatrix.tZ.vY = igi2_frame.tTempMatrix.tX.vY;
    igi2_frame.tTempMatrix.tZ.vZ = Direct3D_vScale;
    Direct3D_D3DMATRIXFromReal32x9(&igi2_frame.tLocalMatrix, &igi2_frame.tTempMatrix, (struct real32x3_t *)&igi2_frame.tPos);
    Direct3D_ptDevice->lpVtbl->SetTransform(Direct3D_ptDevice, (enum _D3DTRANSFORMSTATETYPE)256, &igi2_frame.tLocalMatrix);
    v12 = Direct3DRender_SortedFaceGroup_ProcessVerticesSpline(
            ptSortedFaceGroup->ptRenderMesh,
            ptSortedFaceGroup->ptSplineObjSegment,
            ptFaceGroup);
    Direct3D_tState.aptStreamData[0] = Direct3D_atDynamicVertexBuffer[0].ptVertexBuffer;
    Direct3D_tState.anStride[0] = Direct3D_atDynamicVertexBuffer[0].nStride;
    Direct3D_ptDevice->lpVtbl->SetStreamSource(
      Direct3D_ptDevice,
      0,
      Direct3D_atDynamicVertexBuffer[0].ptVertexBuffer,
      Direct3D_atDynamicVertexBuffer[0].nStride);
    Direct3D_tState.nHandle = Direct3D_atDynamicVertexBuffer[0].nFVF;
    Direct3D_ptDevice->lpVtbl->SetVertexShader(Direct3D_ptDevice, Direct3D_atDynamicVertexBuffer[0].nFVF);
    Direct3DRender_DrawRigidFacegroup(ptFaceGroup, ptVirModel, false, v12);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZWRITEENABLE, 1u);
  }
}

// source: e/3/pc/pc_direct3drender.c:3791  [size]
void __cdecl Direct3DRender_DrawSplineMesh(struct DrawSplineMeshContext_t *ptContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { int iLOD; };
    struct { struct RigidDirect3D_FaceGroup_t *iLODa; };
    struct { char igi2_o2[4]; int i; };
    struct { char igi2_o3[4]; int ia; };
    struct { char igi2_o4[4]; float ib; };
    struct { char igi2_o5[8]; enum bool isTotallyInside; };
    struct { char igi2_o6[12]; struct SplineObjSegment_s *ptSplineObjSegment; };
    struct { char igi2_o7[16]; struct VirModel_s *ptVirModel; };
    struct { char igi2_o8[20]; struct RigidDirect3D_FaceGroup_t *ptEnd; };
    struct { char igi2_o9[24]; struct real32x3_t tPos; };
    struct { char igi2_o10[36]; struct real32x3_t tDeltaPos; };
    struct { char igi2_o11[48]; struct real32x3_t Real32x3_Rotate_tTemp; };
    struct { char igi2_o12[60]; struct real32x9_t tTempMatrix; };
    struct { char igi2_o13[100]; struct TransContext_s tNewTransContext; };
    struct { char igi2_o14[268]; struct _D3DMATRIX tLocalMatrix; };
    struct { char igi2_o15[332]; struct TransContext_s tOldTransContext; };
    char igi2_extent[500];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct SplineObjSegment_s *v1; // ebx
  struct LODVirModel_s *ptLODVirModel; // esi
  int SplineMeshLOD; // eax
  struct VirModel_s *v4; // esi
  struct Mesh3D_Mesh_t *ptMesh; // ebp
  void *pxRenderMesh; // eax
  double AspectRatio; // st7
  double v8; // st7
  double v9; // st6
  enum Mesh3D_DrawMode_e eDrawMode; // ecx
  struct SortRenderList_t *v11; // edi
  int v12; // esi
  double v13; // st7
  int v14; // eax
  int v15; // ecx
  double v16; // st7
  unsigned __int8 *v17; // eax
  _DWORD *p_vX; // edx
  unsigned __int8 *v19; // ecx
  enum Mesh3D_RenderMeshType_e eRenderMeshType; // eax
  struct Mesh3D_RenderMesh_RigidDirect3D_t *v21; // esi
  int v22; // eax
  int v23; // ecx
  unsigned int v24; // edi
  struct RenderStateBlock_t *v25; // eax
  struct RenderStateBlock_t *v26; // eax
  int v27; // ecx
  int v28; // eax
  int v29; // ecx
  struct RenderStateBlock_t *v30; // edx
  int v31; // ecx
  struct real64x3_t *v32; // eax
  struct VirModel_s *v33; // ecx
  struct Mesh3D_RenderMesh_LightmapDirect3D_t *v34; // edi
  struct Mesh3D_LightmapVirModel_t *v35; // eax
  struct RenderStateBlock_t *v36; // eax
  int v37; // ecx
  int v38; // ecx
  struct RenderStateBlock_t *v39; // eax
  int v40; // ecx
  struct RenderStateBlock_t *v41; // eax
  int v42; // eax
  int v43; // ecx
  struct RenderStateBlock_t *v44; // edx
  int v45; // ecx
  unsigned int v46; // esi
  unsigned __int16 v47; // ax
  struct IDirect3DBaseTexture8 *ptDirect3DBaseTexture; // eax
  struct Mesh3D_LightmapVirModel_t *v49; // eax
  struct Mesh3D_LightmapList_s *ptLightmapList; // eax
  char v51; // al
  int v52; // ecx
  bool v53; // zf
  struct RenderStateBlock_t *v54; // eax
  int eCurrentState; // edx
  int v56; // ecx

  v1 = ptContext->ptSplineObjSegment;
  ptLODVirModel = ptContext->ptSplineObjSegment->tRigidDynCubeObj.tModelObj.ptLODVirModel;
  igi2_frame.ptSplineObjSegment = ptContext->ptSplineObjSegment;
  if ( !ptLODVirModel )
    ptLODVirModel = MTP_ptMissingModel;
  if ( ptLODVirModel->nLOD && Mesh3D_ExcludeSplineMesh(v1, &igi2_frame.isTotallyInside) == false )
  {
    SplineMeshLOD = Mesh3D_GetSplineMeshLOD(v1);
    igi2_frame.iLOD = SplineMeshLOD;
    if ( v1->tRigidDynCubeObj.tModelObj.eLayer )
    {
      if ( SplineMeshLOD == -1 )
        return;
    }
    else
    {
      SplineMeshLOD = 0;
      igi2_frame.iLOD = 0;
    }
    v4 = ptLODVirModel->aptVirModel[SplineMeshLOD];
    ptMesh = v4->ptModel->ptMesh;
    pxRenderMesh = ptMesh->pxRenderMesh;
    igi2_frame.ptVirModel = v4;
    if ( pxRenderMesh )
    {
      Mesh3D_SetDrawAnimTextures(v4);
      if ( v1->tRigidDynCubeObj.tModelObj.eLayer == TRANSCONTEXT_LAYER_FRONT )
      {
        qmemcpy(&igi2_frame.tOldTransContext, &TransContext_tActiveTransContext, sizeof(igi2_frame.tOldTransContext));
        igi2_frame.ib = Mesh3D_avOverrideFOV[0] * RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHeight;
        qmemcpy(&igi2_frame.tNewTransContext, &igi2_frame.tOldTransContext, sizeof(igi2_frame.tNewTransContext));
        igi2_frame.tNewTransContext.vFOVX = Mesh3D_avOverrideFOV[0];
        igi2_frame.tNewTransContext.vFOVY = igi2_frame.ib
                               / (Display_GetAspectRatio()
                                * RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vWidth);
        igi2_frame.tNewTransContext.vScreenFOVX = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHalfWidth
                                     / igi2_frame.tNewTransContext.vFOVX;
        AspectRatio = Display_GetAspectRatio();
        igi2_frame.tNewTransContext.eLayer = TRANSCONTEXT_LAYER_FRONT;
        igi2_frame.tNewTransContext.vScreenFOVY = AspectRatio * igi2_frame.tNewTransContext.vScreenFOVX;
        TransContext_SetActiveTransContext(&igi2_frame.tNewTransContext);
      }
      v8 = v1->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vX - TransContext_tActiveTransContext.tPos.vX;
      v9 = v1->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vY - TransContext_tActiveTransContext.tPos.vY;
      igi2_frame.tTempMatrix.nOps = 0;
      igi2_frame.tDeltaPos.vZ = v1->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vZ - TransContext_tActiveTransContext.tPos.vZ;
      igi2_frame.tDeltaPos.vX = Direct3D_vScale * v8;
      igi2_frame.tDeltaPos.vY = Direct3D_vScale * v9;
      igi2_frame.tDeltaPos.vZ = Direct3D_vScale * igi2_frame.tDeltaPos.vZ;
      igi2_frame.tTempMatrix.tX.vX = Direct3D_vScale;
      igi2_frame.tTempMatrix.tX.vY = Direct3D_vScale * 0.0;
      igi2_frame.tTempMatrix.tX.vZ = igi2_frame.tTempMatrix.tX.vY;
      igi2_frame.tTempMatrix.tY.vX = igi2_frame.tTempMatrix.tX.vY;
      igi2_frame.tTempMatrix.tY.vY = Direct3D_vScale;
      igi2_frame.tTempMatrix.tY.vZ = igi2_frame.tTempMatrix.tX.vY;
      igi2_frame.tTempMatrix.tZ.vX = igi2_frame.tTempMatrix.tX.vY;
      igi2_frame.tTempMatrix.tZ.vY = igi2_frame.tTempMatrix.tX.vY;
      igi2_frame.tTempMatrix.tZ.vZ = Direct3D_vScale;
      Direct3D_D3DMATRIXFromReal32x9(&igi2_frame.tLocalMatrix, &igi2_frame.tTempMatrix, &igi2_frame.tDeltaPos);
      Direct3D_ptDevice->lpVtbl->SetTransform(Direct3D_ptDevice, (enum _D3DTRANSFORMSTATETYPE)256, &igi2_frame.tLocalMatrix);
      eDrawMode = ptContext->eDrawMode;
      igi2_frame.Real32x3_Rotate_tTemp.vZ = (v1->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vZ
                                - TransContext_tActiveTransContext.tPos.vZ)
                               * TransContext_tActiveTransContext.tMatrix.tZ.vZ
                               + (v1->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vY
                                - TransContext_tActiveTransContext.tPos.vY)
                               * TransContext_tActiveTransContext.tMatrix.tZ.vY
                               + (v1->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vX
                                - TransContext_tActiveTransContext.tPos.vX)
                               * TransContext_tActiveTransContext.tMatrix.tZ.vX;
      if ( eDrawMode != MESH3D_DRAWMODE_ENVMAP )
      {
        igi2_frame.i = 0;
        if ( ptMesh->nGlows > 0 )
        {
          v11 = SortRender_ptActiveList;
          v12 = 0;
          do
          {
            SplineObjSegment_TransformVertex(v1, &igi2_frame.tPos, &ptMesh->ptGlows[v12].tPos);
            v13 = igi2_frame.tPos.vZ + igi2_frame.Real32x3_Rotate_tTemp.vZ;
            v14 = (int)&v11->atItem[v11->nNumItems++];
            *(float *)(v14 + 8) = v13;
            v15 = SortRender_nBufferPos;
            v16 = igi2_frame.tPos.vX * Direct3D_vScale;
            *(_DWORD *)v14 = Glow_DrawSorted;
            *(_DWORD *)(v14 + 4) = &SortRender_anSortBuffer[v15];
            igi2_frame.tPos.vX = v16;
            v17 = &SortRender_anSortBuffer[v15];
            SortRender_nBufferPos = v15 + 28;
            igi2_frame.tPos.vY = igi2_frame.tPos.vY * Direct3D_vScale;
            igi2_frame.tPos.vZ = igi2_frame.tPos.vZ * Direct3D_vScale;
            *(float *)v17 = igi2_frame.tPos.vX + igi2_frame.tDeltaPos.vX;
            *((float *)v17 + 1) = igi2_frame.tPos.vY + igi2_frame.tDeltaPos.vY;
            *((float *)v17 + 2) = igi2_frame.tPos.vZ + igi2_frame.tDeltaPos.vZ;
            p_vX = (_DWORD *)&ptMesh->ptGlows[v12].tColor.vX;
            v19 = &SortRender_anSortBuffer[v15 + 16];
            *(_DWORD *)v19 = *p_vX;
            *((_DWORD *)v19 + 1) = p_vX[1];
            v1 = igi2_frame.ptSplineObjSegment;
            *((_DWORD *)v19 + 2) = p_vX[2];
            *((_DWORD *)v17 + 3) = LODWORD(ptMesh->ptGlows[v12++].vRadius);
            ++igi2_frame.i;
          }
          while ( igi2_frame.i < ptMesh->nGlows );
        }
      }
      eRenderMeshType = ptMesh->eRenderMeshType;
      if ( eRenderMeshType == MESH3D_RENDERMESHTYPE_DIRECT3D_RIGID )
      {
        v21 = (struct Mesh3D_RenderMesh_RigidDirect3D_t *)ptMesh->pxRenderMesh;
        igi2_frame.iLODa = v21->ptFaceGroup;
        igi2_frame.ptEnd = &igi2_frame.iLODa[v21->nNumFaceGroups];
        v22 = Direct3DRender_ProcessVerticesSplineRigid(v21, v1);
        v23 = Direct3DRender_eTextureStateRigid;
        v24 = v22;
        v25 = Direct3D_ptTextureStateBlock;
        if ( Direct3D_ptTextureStateBlock->eCurrentState != Direct3DRender_eTextureStateRigid )
        {
          Direct3D_ptTextureStateBlock->eCurrentState = Direct3DRender_eTextureStateRigid;
          v25->atRenderState[v23].pfCallback(nullptr);
        }
        v26 = Direct3D_ptGenericStateBlock;
        v27 = Direct3DRender_eGenericStateRigid;
        if ( Direct3D_ptGenericStateBlock->eCurrentState != Direct3DRender_eGenericStateRigid )
        {
          Direct3D_ptGenericStateBlock->eCurrentState = Direct3DRender_eGenericStateRigid;
          v26->atRenderState[v27].pfCallback(nullptr);
        }
        v28 = Direct3D_eClippingStateOn;
        v29 = Direct3D_eClippingStateOff;
        if ( igi2_frame.isTotallyInside == false )
          v29 = Direct3D_eClippingStateOn;
        v30 = Direct3D_ptClippingStateBlock;
        if ( Direct3D_ptClippingStateBlock->eCurrentState != v29 )
        {
          v31 = Direct3D_eClippingStateOff;
          if ( igi2_frame.isTotallyInside == false )
            v31 = Direct3D_eClippingStateOn;
          Direct3D_ptClippingStateBlock->eCurrentState = v31;
          if ( igi2_frame.isTotallyInside )
            v28 = Direct3D_eClippingStateOff;
          v30->atRenderState[v28].pfCallback(nullptr);
        }
        Direct3D_tState.aptStreamData[0] = Direct3D_atDynamicVertexBuffer[0].ptVertexBuffer;
        Direct3D_tState.anStride[0] = Direct3D_atDynamicVertexBuffer[0].nStride;
        Direct3D_ptDevice->lpVtbl->SetStreamSource(
          Direct3D_ptDevice,
          0,
          Direct3D_atDynamicVertexBuffer[0].ptVertexBuffer,
          Direct3D_atDynamicVertexBuffer[0].nStride);
        Direct3D_tState.ptIndexData = v21->ptIndexData->ptIndexBuffer;
        Direct3D_tState.nBaseVertexIndex = v24;
        Direct3D_ptDevice->lpVtbl->SetIndices(Direct3D_ptDevice, Direct3D_tState.ptIndexData, v24);
        Direct3D_tState.nHandle = Direct3D_atDynamicVertexBuffer[0].nFVF;
        Direct3D_ptDevice->lpVtbl->SetVertexShader(Direct3D_ptDevice, Direct3D_atDynamicVertexBuffer[0].nFVF);
        v1 = igi2_frame.ptSplineObjSegment;
        Direct3DRender_SetFogParametersRigid(&igi2_frame.ptSplineObjSegment->tRigidDynCubeObj, ptMesh);
        if ( igi2_frame.iLODa )
        {
          do
          {
            if ( (igi2_frame.iLODa->bMaterialProperties & 4) == 0 || ptContext->eDrawMode == MESH3D_DRAWMODE_ENVMAP )
            {
              Direct3DRender_DrawRigidFacegroup(igi2_frame.iLODa, igi2_frame.ptVirModel, true, -1);
            }
            else
            {
              igi2_frame.Real32x3_Rotate_tTemp.vZ = (v1->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vZ
                                        - TransContext_tActiveTransContext.tPos.vZ)
                                       * TransContext_tActiveTransContext.tMatrix.tZ.vZ
                                       + (v1->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vY
                                        - TransContext_tActiveTransContext.tPos.vY)
                                       * TransContext_tActiveTransContext.tMatrix.tZ.vY
                                       + (v1->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vX
                                        - TransContext_tActiveTransContext.tPos.vX)
                                       * TransContext_tActiveTransContext.tMatrix.tZ.vX;
              v32 = (struct real64x3_t *)SortRender_AllocItem(
                                           (void (__cdecl *)(void *))Direct3DRender_DrawSortedFaceGroup_Spline,
                                           48,
                                           igi2_frame.Real32x3_Rotate_tTemp.vZ);
              qmemcpy(v32, &v1->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos, sizeof(struct real64x3_t));
              v33 = igi2_frame.ptVirModel;
              LODWORD(v32[1].vX) = v1->tRigidDynCubeObj.tModelObj.iLightCategory;
              HIDWORD(v32[1].vX) = v33;
              LODWORD(v32[1].vY) = v21;
              HIDWORD(v32[1].vY) = igi2_frame.iLODa;
              LODWORD(v32[1].vZ) = v1;
            }
            ++igi2_frame.iLODa;
          }
          while ( igi2_frame.iLODa < igi2_frame.ptEnd );
        }
        goto LABEL_77;
      }
      if ( eRenderMeshType != MESH3D_RENDERMESHTYPE_DIRECT3D_BUILDING )
      {
LABEL_77:
        if ( v1->tRigidDynCubeObj.tModelObj.eLayer == TRANSCONTEXT_LAYER_FRONT )
          TransContext_SetActiveTransContext(&igi2_frame.tOldTransContext);
        Mesh3D_RestoreAnimTextures(igi2_frame.ptVirModel);
        return;
      }
      v34 = (struct Mesh3D_RenderMesh_LightmapDirect3D_t *)ptMesh->pxRenderMesh;
      igi2_frame.ia = (int)v34->ptFaceGroup;
      igi2_frame.ptSplineObjSegment = (struct SplineObjSegment_s *)(igi2_frame.ia + 28 * v34->nNumFaceGroups);
      igi2_frame.ptEnd = (struct RigidDirect3D_FaceGroup_t *)Direct3DRender_ProcessVerticesSplineLightmap(v34, v1);
      v35 = v1->tRigidDynCubeObj.aptLightmapVirModel[igi2_frame.iLOD + 1];
      if ( v35 && v35->ptLightmapList )
      {
        v36 = Direct3D_ptTextureStateBlock;
        v37 = Direct3DRender_eTextureStateLightmap;
        if ( Direct3D_ptTextureStateBlock->eCurrentState != Direct3DRender_eTextureStateLightmap )
        {
          Direct3D_ptTextureStateBlock->eCurrentState = Direct3DRender_eTextureStateLightmap;
          v36->atRenderState[v37].pfCallback(nullptr);
        }
        v38 = Direct3DRender_eGenericStateLightmap;
      }
      else
      {
        v39 = Direct3D_ptTextureStateBlock;
        v40 = Direct3DRender_eTextureStateRigid;
        if ( Direct3D_ptTextureStateBlock->eCurrentState != Direct3DRender_eTextureStateRigid )
        {
          Direct3D_ptTextureStateBlock->eCurrentState = Direct3DRender_eTextureStateRigid;
          v39->atRenderState[v40].pfCallback(nullptr);
        }
        v38 = Direct3DRender_eGenericStateRigid;
      }
      v41 = Direct3D_ptGenericStateBlock;
      if ( Direct3D_ptGenericStateBlock->eCurrentState != v38 )
      {
        Direct3D_ptGenericStateBlock->eCurrentState = v38;
        v41->atRenderState[v38].pfCallback(nullptr);
      }
      v42 = Direct3D_eClippingStateOn;
      v43 = Direct3D_eClippingStateOff;
      if ( igi2_frame.isTotallyInside == false )
        v43 = Direct3D_eClippingStateOn;
      v44 = Direct3D_ptClippingStateBlock;
      if ( Direct3D_ptClippingStateBlock->eCurrentState != v43 )
      {
        v45 = Direct3D_eClippingStateOff;
        if ( igi2_frame.isTotallyInside == false )
          v45 = Direct3D_eClippingStateOn;
        Direct3D_ptClippingStateBlock->eCurrentState = v45;
        if ( igi2_frame.isTotallyInside )
          v42 = Direct3D_eClippingStateOff;
        v44->atRenderState[v42].pfCallback(nullptr);
      }
      Direct3D_SetStreamSource(
        0,
        Direct3D_atDynamicVertexBuffer[3].ptVertexBuffer,
        Direct3D_atDynamicVertexBuffer[3].nStride);
      Direct3D_SetIndices(v34->ptIndexData->ptIndexBuffer, (unsigned int)igi2_frame.ptEnd);
      Direct3D_SetVertexShader(Direct3D_atDynamicVertexBuffer[3].nFVF);
      Direct3DRender_SetFogParametersRigid(&v1->tRigidDynCubeObj, ptMesh);
      v46 = igi2_frame.ia;
      while ( 1 )
      {
        v47 = *(_WORD *)(v46 + 24);
        if ( v47 == 0xFFFF || (*(_BYTE *)v46 & 4) != 0 && ptContext->eDrawMode != MESH3D_DRAWMODE_ENVMAP )
          goto LABEL_76;
        ptDirect3DBaseTexture = igi2_frame.ptVirModel->pptTexInfo[v47]->ptDirect3DBaseTexture;
        if ( ptDirect3DBaseTexture != Direct3D_tState.aptTexture[0] )
        {
          Direct3D_tState.aptTexture[0] = ptDirect3DBaseTexture;
          Direct3D_ptDevice->lpVtbl->SetTexture(Direct3D_ptDevice, 0, ptDirect3DBaseTexture);
        }
        v49 = v1->tRigidDynCubeObj.aptLightmapVirModel[igi2_frame.iLOD + 1];
        if ( v49 )
        {
          ptLightmapList = v49->ptLightmapList;
          if ( ptLightmapList )
            Direct3D_SetTexture(
              1u,
              ptLightmapList->atLightmap[*(unsigned __int16 *)(v46 + 26)].tTexInfo.ptDirect3DBaseTexture);
        }
        v51 = *(_BYTE *)v46;
        if ( (*(_BYTE *)v46 & 0x40) != 0 )
          break;
        if ( (v51 & 4) == 0 )
        {
          v52 = Direct3DRender_eBlendStateOpaque;
          goto LABEL_72;
        }
        v53 = (v51 & 1) == 0;
        v54 = Direct3D_ptBlendStateBlock;
        eCurrentState = Direct3D_ptBlendStateBlock->eCurrentState;
        if ( !v53 )
        {
          v56 = Direct3DRender_eBlendStateAdditive;
          if ( eCurrentState != Direct3DRender_eBlendStateAdditive )
          {
            Direct3D_ptBlendStateBlock->eCurrentState = Direct3DRender_eBlendStateAdditive;
            v54->atRenderState[v56].pfCallback(nullptr);
          }
          Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_LIGHTING, 0);
          Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLOROP, 2u);
          Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGENABLE, 0);
          goto LABEL_75;
        }
        v52 = Direct3DRender_eBlendStateTransparent;
LABEL_73:
        if ( eCurrentState != v52 )
        {
          v54->eCurrentState = v52;
          v54->atRenderState[v52].pfCallback(nullptr);
        }
LABEL_75:
        Direct3D_ptDevice->lpVtbl->DrawIndexedPrimitive(
          Direct3D_ptDevice,
          D3DPT_TRIANGLELIST,
          *(unsigned __int16 *)(v46 + 20),
          *(unsigned __int16 *)(v46 + 22),
          *(unsigned __int16 *)(v46 + 16),
          *(unsigned __int16 *)(v46 + 18));
LABEL_76:
        v46 += 28;
        if ( v46 >= (unsigned int)igi2_frame.ptSplineObjSegment )
          goto LABEL_77;
      }
      v52 = Direct3DRender_eBlendStateAlphaTest;
LABEL_72:
      v54 = Direct3D_ptBlendStateBlock;
      eCurrentState = Direct3D_ptBlendStateBlock->eCurrentState;
      goto LABEL_73;
    }
  }
}

// source: e/3/pc/pc_direct3drender.c:4210  [size]
void __cdecl Direct3DRender_AddLightsource(void *pxContext)
{
  float *v1; // edx
  unsigned int v2; // esi
  struct _D3DLIGHT8 tLight; // [esp+10h] [ebp-68h] BYREF

  if ( *(_DWORD *)pxContext == 196608 )
  {
    v1 = *((float **)pxContext + 1);
    v2 = *((_DWORD *)pxContext + 2);
    memset(&tLight, 0, sizeof(tLight));
    tLight.Type = D3DLIGHT_DIRECTIONAL;
    tLight.Diffuse.r = v1[3];
    tLight.Diffuse.g = v1[4];
    tLight.Diffuse.b = v1[5];
    tLight.Direction.x = -*v1;
    tLight.Direction.y = -v1[1];
    tLight.Direction.z = -v1[2];
    Direct3D_ptDevice->lpVtbl->SetLight(Direct3D_ptDevice, v2, &tLight);
    Direct3D_ptDevice->lpVtbl->LightEnable(Direct3D_ptDevice, v2, 1);
  }
  else
  {
    if ( *(_DWORD *)pxContext != 0x40000 )
    {
      LDebug_Error("Lightsource type not supported");
      abort();
    }
    Direct3D_ptDevice->lpVtbl->SetRenderState(
      Direct3D_ptDevice,
      D3DRS_AMBIENT,
      (__int64)(*(float *)(*((_DWORD *)pxContext + 1) + 8) * 255.0)
    | (((unsigned int)(__int64)(*(float *)(*((_DWORD *)pxContext + 1) + 4) * 255.0)
      | ((unsigned int)(__int64)(**((float **)pxContext + 1) * 255.0) << 8)) << 8));
  }
}

// source: e/3/pc/pc_direct3drender.c:4266  [size]
void __cdecl Direct3DRender_RemoveLightsource(void *pxContext)
{
  Direct3D_ptDevice->lpVtbl->LightEnable(Direct3D_ptDevice, *((_DWORD *)pxContext + 2), 0);
}

// source: e/3/pc/pc_direct3drender.c:4293  [size]
void __cdecl Direct3DRender_SetBlendStateOpaque(void *pxContext)
{
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHABLENDENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHATESTENABLE, 0);
}

// source: e/3/pc/pc_direct3drender.c:4307  [size]
void __cdecl Direct3DRender_SetBlendStateAlphaTest(void *pxContext)
{
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHABLENDENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHAREF, 64u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHAFUNC, 5u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHATESTENABLE, 1u);
}

// source: e/3/pc/pc_direct3drender.c:4323  [size]
void __cdecl Direct3DRender_SetBlendStateTransparent(void *pxContext)
{
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHABLENDENABLE, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SRCBLEND, 5u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_DESTBLEND, 6u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHAREF, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHAFUNC, 5u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHATESTENABLE, 1u);
}

// source: e/3/pc/pc_direct3drender.c:4341  [size]
void __cdecl Direct3DRender_SetBlendStateAdditive(void *pxContext)
{
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHABLENDENABLE, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SRCBLEND, 5u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_DESTBLEND, 2u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHAREF, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHAFUNC, 5u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHATESTENABLE, 1u);
}

// source: e/3/pc/pc_direct3drender.c:4359  [size]
void __cdecl Direct3DRender_SetGenericStateRigid(void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { unsigned int vFog; };
    struct { char igi2_o1[12]; struct _D3DMATERIAL8 tMaterial; };
    char igi2_extent[80];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  igi2_frame.vFog = LODWORD(Mesh3D_avFogDensity[1]);
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
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGDENSITY, igi2_frame.vFog);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGTABLEMODE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGVERTEXMODE, 3u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGENABLE, QVertex_isFog);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZBIAS, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SPECULARENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_CULLMODE, 3u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_LIGHTING, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_COLORVERTEX, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_DITHERENABLE, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZENABLE, Direct3D_bZBufferMode);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZWRITEENABLE, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZFUNC, 4u);
}

// source: e/3/pc/pc_direct3drender.c:4412  [size]
void __cdecl Direct3DRender_SetGenericStateBone(void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { unsigned int vFog; };
    struct { char igi2_o1[12]; struct _D3DMATERIAL8 tMaterial; };
    char igi2_extent[80];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  igi2_frame.vFog = LODWORD(Mesh3D_avFogDensity[1]);
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
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGDENSITY, igi2_frame.vFog);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGTABLEMODE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGVERTEXMODE, 3u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGENABLE, QVertex_isFog);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZBIAS, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SPECULARENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_CULLMODE, 3u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_LIGHTING, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_COLORVERTEX, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_DIFFUSEMATERIALSOURCE, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_DITHERENABLE, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZENABLE, Direct3D_bZBufferMode);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZWRITEENABLE, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZFUNC, 4u);
}

// source: e/3/pc/pc_direct3drender.c:4466  [size]
void __cdecl Direct3DRender_SetTextureStateRigid(void *pxContext)
{
  Direct3DRender_SetTextureStageFilteringMode(0);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ADDRESSU, 1u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ADDRESSV, 1u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_TEXCOORDINDEX, 0);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAOP, 3u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAARG1, 3u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAARG2, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLOROP, 4u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLORARG1, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLORARG2, 0);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_TEXTURETRANSFORMFLAGS, 0);
  Direct3DRender_SetTextureStageFilteringMode(1u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_ADDRESSU, 1u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_ADDRESSV, 1u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_TEXCOORDINDEX, 196608u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_ALPHAOP, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_ALPHAARG1, 1u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_ALPHAARG2, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_COLORARG1, 1u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_COLORARG2, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_TEXTURETRANSFORMFLAGS, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_COLOROP, 1u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 2u, D3DTSS_COLOROP, 1u);
}

// source: e/3/pc/pc_direct3drender.c:4506  [size]
void __cdecl Direct3DRender_SetGenericStateLightmap(void *pxContext)
{
  unsigned int vFog; // [esp+Ch] [ebp-Ch]

  vFog = LODWORD(Mesh3D_avFogDensity[1]);
  Direct3D_ptDevice->lpVtbl->SetRenderState(
    Direct3D_ptDevice,
    D3DRS_FOGCOLOR,
    (__int64)(Mesh3D_atFogColor[1].vZ * 255.0)
  - (((unsigned int)(__int64)(Mesh3D_atFogColor[1].vY * -255.0)
    + ((unsigned int)(__int64)(Mesh3D_atFogColor[1].vX * -255.0) << 8)) << 8));
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGDENSITY, vFog);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGTABLEMODE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGVERTEXMODE, 3u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGENABLE, QVertex_isFog);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZBIAS, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SPECULARENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_CULLMODE, 3u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_LIGHTING, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_COLORVERTEX, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_DITHERENABLE, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZENABLE, Direct3D_bZBufferMode);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZWRITEENABLE, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZFUNC, 4u);
}

// source: e/3/pc/pc_direct3drender.c:4548  [size]
void __cdecl Direct3DRender_SetTextureStateLightmap(void *pxContext)
{
  Direct3DRender_SetTextureStageFilteringMode(0);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ADDRESSU, 1u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ADDRESSV, 1u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_TEXCOORDINDEX, 0);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAOP, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAARG1, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAARG2, 0);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLOROP, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLORARG1, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLORARG2, 0);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_TEXTURETRANSFORMFLAGS, 0);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_ADDRESSU, 3u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_ADDRESSV, 3u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_MIPFILTER, 0);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_TEXCOORDINDEX, 1u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_ALPHAARG1, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_ALPHAARG2, 1u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_COLORARG1, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_COLORARG2, 1u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_TEXTURETRANSFORMFLAGS, 0);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_COLOROP, 5u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_ALPHAOP, 3u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_MINFILTER, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_MAGFILTER, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 2u, D3DTSS_COLOROP, 1u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 2u, D3DTSS_ALPHAOP, 1u);
}

// source: e/3/pc/pc_direct3drender.c:4615  [size]
void __cdecl Direct3DRender_SetGenericStateTransparentRigid(void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { unsigned int vFog; };
    struct { char igi2_o1[12]; struct _D3DMATERIAL8 tMaterial; };
    char igi2_extent[80];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  igi2_frame.vFog = LODWORD(Mesh3D_avFogDensity[1]);
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
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGDENSITY, igi2_frame.vFog);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGTABLEMODE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGVERTEXMODE, 3u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGENABLE, QVertex_isFog);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZBIAS, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SPECULARENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_CULLMODE, 3u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_LIGHTING, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_COLORVERTEX, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_DITHERENABLE, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZENABLE, Direct3D_bZBufferMode);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZWRITEENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZFUNC, 4u);
}

// source: e/3/pc/pc_direct3drender.c:4671  [size]
void __cdecl Direct3DRender_SetGenericStateTransparentLightmap(void *pxContext)
{
  unsigned int vFog; // [esp+Ch] [ebp-Ch]

  vFog = LODWORD(Mesh3D_avFogDensity[1]);
  Direct3D_ptDevice->lpVtbl->SetRenderState(
    Direct3D_ptDevice,
    D3DRS_FOGCOLOR,
    (__int64)(Mesh3D_atFogColor[1].vZ * 255.0)
  - (((unsigned int)(__int64)(Mesh3D_atFogColor[1].vY * -255.0)
    + ((unsigned int)(__int64)(Mesh3D_atFogColor[1].vX * -255.0) << 8)) << 8));
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGDENSITY, vFog);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGTABLEMODE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGVERTEXMODE, 3u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGENABLE, QVertex_isFog);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZBIAS, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SPECULARENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_CULLMODE, 3u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_LIGHTING, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_COLORVERTEX, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_DITHERENABLE, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZENABLE, Direct3D_bZBufferMode);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZWRITEENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZFUNC, 4u);
}

// source: e/3/pc/pc_direct3drender.c:4713  [size]
void __cdecl Direct3DRender_SetInfrared(void *pxContext)
{
  struct _D3DMATRIX tMatrix; // [esp+E0h] [ebp-40h] BYREF

  memset(&tMatrix, 0, 32);
  *(_QWORD *)&tMatrix.m[2][0] = 1065353216;
  *(_QWORD *)&tMatrix.m[2][2] = 0;
  *(_QWORD *)&tMatrix.m[3][0] = 1065353216;
  *(_QWORD *)&tMatrix.m[3][2] = 0;
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_MINFILTER, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_MAGFILTER, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ADDRESSU, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ADDRESSV, 1u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_MIPFILTER, 1u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_TEXCOORDINDEX, 0x10000u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAOP, 4u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLOROP, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAARG1, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAARG2, 3u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLORARG1, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLORARG2, 0);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_TEXTURETRANSFORMFLAGS, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_COLOROP, 1u);
  Direct3D_ptDevice->lpVtbl->SetTransform(Direct3D_ptDevice, D3DTS_TEXTURE0, &tMatrix);
}

// source: e/3/pc/pc_direct3drender.c:4751  [size]
void __cdecl Direct3DRender_SortedFaceGroup_Rigid_SetStates(struct Batch_SetStatesContext_s *ptContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct _D3DMATRIX tViewMatrix; };
    struct { char igi2_o1[64]; struct TransContext_s tNewTransContext; };
    char igi2_extent[232];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  _DWORD *pxUserContext; // ebx
  double v2; // st7
  struct RenderStateBlock_t *v3; // eax
  int v4; // ecx
  struct RenderStateBlock_t *v5; // eax
  int v6; // ecx
  char v7; // al
  int v8; // ecx
  bool v9; // zf
  struct RenderStateBlock_t *v10; // eax
  int eCurrentState; // edx
  int v12; // ecx

  pxUserContext = ptContext->pxUserContext;
  if ( !pxUserContext[2] )
  {
    qmemcpy(pxUserContext + 4, &TransContext_tActiveTransContext, 0xA8u);
    v2 = (double)Display_tActiveMode.nHeight * 4.0 / ((double)Display_tActiveMode.nWidth * 3.0);
    qmemcpy(&igi2_frame.tNewTransContext, pxUserContext + 4, sizeof(igi2_frame.tNewTransContext));
    igi2_frame.tNewTransContext.vFOVX = Mesh3D_avOverrideFOV[0];
    igi2_frame.tNewTransContext.eLayer = TRANSCONTEXT_LAYER_FRONT;
    igi2_frame.tNewTransContext.vFOVY = Mesh3D_avOverrideFOV[0]
                           * RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHeight
                           / (v2
                            * RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vWidth);
    igi2_frame.tNewTransContext.vScreenFOVX = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHalfWidth
                                 / Mesh3D_avOverrideFOV[0];
    igi2_frame.tNewTransContext.vScreenFOVY = v2 * igi2_frame.tNewTransContext.vScreenFOVX;
    TransContext_SetActiveTransContext(&igi2_frame.tNewTransContext);
  }
  v3 = Direct3D_ptGenericStateBlock;
  v4 = Direct3DRender_eGenericStateTransparentRigid;
  if ( Direct3D_ptGenericStateBlock->eCurrentState != Direct3DRender_eGenericStateTransparentRigid )
  {
    Direct3D_ptGenericStateBlock->eCurrentState = Direct3DRender_eGenericStateTransparentRigid;
    v3->atRenderState[v4].pfCallback(nullptr);
  }
  v5 = Direct3D_ptTextureStateBlock;
  v6 = Direct3DRender_eTextureStateRigid;
  if ( Direct3D_ptTextureStateBlock->eCurrentState != Direct3DRender_eTextureStateRigid )
  {
    Direct3D_ptTextureStateBlock->eCurrentState = Direct3DRender_eTextureStateRigid;
    v5->atRenderState[v6].pfCallback(nullptr);
  }
  v7 = *((_BYTE *)pxUserContext + 12);
  if ( (v7 & 0x40) != 0 )
  {
    v8 = Direct3DRender_eBlendStateAlphaTest;
LABEL_16:
    v10 = Direct3D_ptBlendStateBlock;
    eCurrentState = Direct3D_ptBlendStateBlock->eCurrentState;
LABEL_17:
    if ( eCurrentState != v8 )
    {
      v10->eCurrentState = v8;
      v10->atRenderState[v8].pfCallback(nullptr);
    }
    goto LABEL_19;
  }
  if ( (v7 & 4) == 0 )
  {
    v8 = Direct3DRender_eBlendStateOpaque;
    goto LABEL_16;
  }
  v9 = (v7 & 1) == 0;
  v10 = Direct3D_ptBlendStateBlock;
  eCurrentState = Direct3D_ptBlendStateBlock->eCurrentState;
  if ( v9 )
  {
    v8 = Direct3DRender_eBlendStateTransparent;
    goto LABEL_17;
  }
  v12 = Direct3DRender_eBlendStateAdditive;
  if ( eCurrentState != Direct3DRender_eBlendStateAdditive )
  {
    Direct3D_ptBlendStateBlock->eCurrentState = Direct3DRender_eBlendStateAdditive;
    v10->atRenderState[v12].pfCallback(nullptr);
  }
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_LIGHTING, 0);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLOROP, 2u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGENABLE, 0);
LABEL_19:
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZWRITEENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(
    Direct3D_ptDevice,
    D3DRS_TEXTUREFACTOR,
    (-1 - *((unsigned __int8 *)pxUserContext + 13)) << 24);
  if ( *pxUserContext )
  {
    if ( (struct IDirect3DBaseTexture8 *)*pxUserContext != Direct3D_tState.aptTexture[0] )
    {
      Direct3D_tState.aptTexture[0] = (struct IDirect3DBaseTexture8 *)*pxUserContext;
      Direct3D_ptDevice->lpVtbl->SetTexture(Direct3D_ptDevice, 0, Direct3D_tState.aptTexture[0]);
    }
    if ( pxUserContext[1] )
    {
      Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_NORMALIZENORMALS, 1u);
      if ( (struct IDirect3DBaseTexture8 *)pxUserContext[1] != Direct3D_tState.aptTexture[1] )
      {
        Direct3D_tState.aptTexture[1] = (struct IDirect3DBaseTexture8 *)pxUserContext[1];
        Direct3D_ptDevice->lpVtbl->SetTexture(Direct3D_ptDevice, 1u, Direct3D_tState.aptTexture[1]);
      }
      Direct3D_ptDevice->lpVtbl->SetRenderState(
        Direct3D_ptDevice,
        D3DRS_TEXTUREFACTOR,
        ((unsigned int)(__int64)((double)*((unsigned __int8 *)pxUserContext + 14) * 255.0) << 24) | 0xFFFFFF);
      Direct3D_ptDevice->lpVtbl->SetTextureStageState(
        Direct3D_ptDevice,
        1u,
        D3DTSS_COLOROP,
        (pxUserContext[3] & 0x20) != 0 ? 16 : 14);
      *(_QWORD *)&igi2_frame.tViewMatrix.m[0][2] = LODWORD(TransContext_tActiveTransContext.tMatrix.tZ.vX);
      *(_QWORD *)&igi2_frame.tViewMatrix._11 = __PAIR64__(
                                      LODWORD(TransContext_tActiveTransContext.tMatrix.tY.vX),
                                      LODWORD(TransContext_tActiveTransContext.tMatrix.tX.vX));
      *(_QWORD *)&igi2_frame.tViewMatrix.m[1][2] = LODWORD(TransContext_tActiveTransContext.tMatrix.tZ.vY);
      *(_QWORD *)&igi2_frame.tViewMatrix.m[1][0] = __PAIR64__(
                                          LODWORD(TransContext_tActiveTransContext.tMatrix.tY.vY),
                                          LODWORD(TransContext_tActiveTransContext.tMatrix.tX.vY));
      *(_QWORD *)&igi2_frame.tViewMatrix.m[2][2] = LODWORD(TransContext_tActiveTransContext.tMatrix.tZ.vZ);
      *(_QWORD *)&igi2_frame.tViewMatrix.m[2][0] = __PAIR64__(
                                          LODWORD(TransContext_tActiveTransContext.tMatrix.tY.vZ),
                                          LODWORD(TransContext_tActiveTransContext.tMatrix.tX.vZ));
      *(_QWORD *)&igi2_frame.tViewMatrix.m[3][0] = 0;
      *(_QWORD *)&igi2_frame.tViewMatrix.m[3][2] = 0x3F80000000000000LL;
      Direct3D_ptDevice->lpVtbl->SetTransform(Direct3D_ptDevice, D3DTS_TEXTURE1, &igi2_frame.tViewMatrix);
    }
  }
  else
  {
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLOROP, 3u);
    if ( Direct3D_tState.aptTexture[0] )
    {
      Direct3D_tState.aptTexture[0] = nullptr;
      Direct3D_ptDevice->lpVtbl->SetTexture(Direct3D_ptDevice, 0, nullptr);
    }
  }
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGVERTEXMODE, 1u);
}

// source: e/3/pc/pc_direct3drender.c:4859  [size]
void __cdecl Direct3DRender_SortedFaceGroup_Rigid_UnsetStates(struct Batch_SetStatesContext_s *ptContext)
{
  char *pxUserContext; // esi

  pxUserContext = (char *)ptContext->pxUserContext;
  if ( *(_DWORD *)pxUserContext )
  {
    if ( *((_DWORD *)pxUserContext + 1) )
    {
      Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_NORMALIZENORMALS, 0);
      Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAOP, 3u);
      Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_COLOROP, 1u);
    }
  }
  else
  {
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLOROP, 4u);
  }
  if ( (pxUserContext[12] & 1) != 0 )
  {
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_LIGHTING, 1u);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLOROP, 4u);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGENABLE, QVertex_isFog);
  }
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZWRITEENABLE, 1u);
  if ( !*((_DWORD *)pxUserContext + 2) )
    TransContext_SetActiveTransContext((struct TransContext_s *)(pxUserContext + 16));
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGVERTEXMODE, 3u);
}

// source: e/3/pc/pc_direct3drender.c:4901  [size]
void __cdecl Direct3DRender_DrawSortedFaceGroup_Rigid(struct RigidDirect3D_SortedFaceGroup_t *ptSortedFaceGroup)
{
  #pragma pack(push, 1)
  union
  {
    struct { void *v34; };
    struct { char igi2_o1[4]; int iStartVertex; };
    struct { char igi2_o2[12]; void (__cdecl *v36)(struct Batch_SetStatesContext_s *); };
    struct { char igi2_o3[44]; struct Direct3DRender_XYZNormalTex1Vertex_t *ptVertices; };
    struct { char igi2_o4[48]; struct Mesh3D_RenderMesh_RigidDirect3D_t *ptRenderMesh; };
    struct { char igi2_o5[52]; struct real32x3_t tDeltaPos; };
    struct { char igi2_o6[64]; struct real32x3_t tScale; };
    struct { char igi2_o7[76]; struct real32x3_t Real32x3_Rotate_tTemp; };
    struct { char igi2_o8[88]; struct real32x9_t tTempMatrix; };
    char igi2_extent[128];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct RigidDirect3D_SortedFaceGroup_t *v1; // ebx
  struct RigidDirect3D_FaceGroup_t *ptFaceGroup; // ebp
  void (__cdecl *v3)(struct Batch_SetStatesContext_s *); // eax
  unsigned __int16 iTexture; // cx
  unsigned __int16 iEnvMap; // cx
  double v6; // st7
  double v7; // st6
  struct Mesh3D_RenderMesh_RigidDirect3D_t *v8; // edx
  int iStartIndex; // ecx
  double v10; // st7
  double v11; // st6
  int v12; // eax
  int nNumVertices; // ecx
  int nNumFaces; // eax
  struct Direct3DRender_XYZNormalTex1Vertex_t *v15; // edi
  int v16; // esi
  struct Direct3DRender_XYZNormalTex1Vertex_t *v17; // edx
  struct real32x3_t *p_tNormal; // ecx
  struct RigidDirect3D_SortedFaceGroup_t *v19; // edi
  float *p_vY; // eax
  float *p_vX; // edx
  double v22; // st7
  double v23; // st7
  double v24; // st6
  double v25; // st7
  double v26; // st6
  struct VirModel_s *ptVirModel; // ebx
  struct Model_s *ptModel; // eax
  int nAnimTextures; // ecx
  struct ModelAnimTexInfo_s *atAnimTexInfo; // eax
  int *p_iTextureToAnimate; // eax
  int v32; // edx
  struct TexInfo_s *v33; // edi

  v1 = ptSortedFaceGroup;
  g_pfCallback = (void (__cdecl *)(struct Batch_SetStatesContext_s *))(192 * dword_834DCD8 + 128093992);
  g_pxContext = (void *)(192 * (dword_834DCD8 ^ 1) + 128093992);
  if ( !ptSortedFaceGroup )
  {
    Batch_Flush((unsigned int *)&g_pnHandler, (void *)(192 * (dword_834DCD8 ^ 1) + 128093992));
    return;
  }
  Mesh3D_ApplyAnimTexBuffer(ptSortedFaceGroup->ptVirModel, ptSortedFaceGroup->ptAnimTexBuffer);
  Mesh3D_SetDrawAnimTextures(v1->ptVirModel);
  ptFaceGroup = v1->ptFaceGroup;
  v3 = g_pfCallback;
  *((_BYTE *)g_pfCallback + 12) = ptFaceGroup->bMaterialProperties;
  *((_DWORD *)v3 + 2) = v1->eLayer;
  *((_BYTE *)v3 + 13) = ptFaceGroup->nTransparency;
  *((_BYTE *)v3 + 14) = ptFaceGroup->nReflectivity;
  *((_DWORD *)v3 + 46) = 1;
  iTexture = ptFaceGroup->iTexture;
  if ( iTexture == 0xFFFF )
  {
    *(_DWORD *)v3 = 0;
    goto LABEL_7;
  }
  *(_DWORD *)v3 = v1->ptVirModel->pptTexInfo[iTexture]->ptDirect3DBaseTexture;
  iEnvMap = ptFaceGroup->iEnvMap;
  if ( iEnvMap == 0xFFFF )
  {
LABEL_7:
    *((_DWORD *)v3 + 1) = 0;
    goto LABEL_8;
  }
  *((_DWORD *)v3 + 1) = v1->ptVirModel->pptTexInfo[iEnvMap]->ptDirect3DBaseTexture;
LABEL_8:
  if ( memcmp(v3, g_pxContext, 0x10u) )
  {
    Batch_Flush((unsigned int *)&g_pnHandler, g_pxContext);
    v3 = g_pfCallback;
  }
  v6 = v1->tPos.vX - TransContext_tActiveTransContext.tPos.vX;
  v7 = v1->tPos.vY - TransContext_tActiveTransContext.tPos.vY;
  qmemcpy(&igi2_frame.tTempMatrix, &v1->tOrientation, sizeof(igi2_frame.tTempMatrix));
  igi2_frame.tDeltaPos.vZ = v1->tPos.vZ - TransContext_tActiveTransContext.tPos.vZ;
  igi2_frame.tDeltaPos.vX = Direct3D_vScale * v6;
  v8 = v1->ptRenderMesh;
  igi2_frame.tDeltaPos.vY = Direct3D_vScale * v7;
  iStartIndex = ptFaceGroup->iStartIndex;
  igi2_frame.v36 = v3;
  igi2_frame.tDeltaPos.vZ = Direct3D_vScale * igi2_frame.tDeltaPos.vZ;
  v10 = Direct3D_vScale * v1->tScale.vX;
  v11 = Direct3D_vScale * v1->tScale.vY;
  igi2_frame.iStartVertex = ptFaceGroup->iStartVertex;
  igi2_frame.ptRenderMesh = v8;
  v12 = (int)&v8->piIndex[iStartIndex];
  nNumVertices = ptFaceGroup->nNumVertices;
  igi2_frame.tScale.vZ = Direct3D_vScale * v1->tScale.vZ;
  igi2_frame.v34 = (void *)v12;
  nNumFaces = ptFaceGroup->nNumFaces;
  igi2_frame.tTempMatrix.tX.vX = igi2_frame.tTempMatrix.tX.vX * v10;
  igi2_frame.tTempMatrix.tX.vY = igi2_frame.tTempMatrix.tX.vY * v11;
  igi2_frame.tTempMatrix.tX.vZ = igi2_frame.tTempMatrix.tX.vZ * igi2_frame.tScale.vZ;
  igi2_frame.tTempMatrix.tY.vX = igi2_frame.tTempMatrix.tY.vX * v10;
  igi2_frame.tTempMatrix.tY.vY = igi2_frame.tTempMatrix.tY.vY * v11;
  igi2_frame.tTempMatrix.tY.vZ = igi2_frame.tTempMatrix.tY.vZ * igi2_frame.tScale.vZ;
  igi2_frame.tTempMatrix.tZ.vX = igi2_frame.tTempMatrix.tZ.vX * v10;
  igi2_frame.tTempMatrix.tZ.vY = igi2_frame.tTempMatrix.tZ.vY * v11;
  igi2_frame.tTempMatrix.tZ.vZ = igi2_frame.tTempMatrix.tZ.vZ * igi2_frame.tScale.vZ;
  Batch_GetLockedVertex(
    BATCH_XYZNORMALTEX1,
    BATCH_INDEX16,
    nNumVertices,
    nNumFaces,
    0,
    igi2_frame.v34,
    igi2_frame.iStartVertex,
    Direct3DRender_SortedFaceGroup_Rigid_SetStates,
    Direct3DRender_SortedFaceGroup_Rigid_UnsetStates,
    igi2_frame.v36,
    (unsigned __int8 **)&igi2_frame.ptVertices,
    (int *)&ptSortedFaceGroup,
    (unsigned int *)&g_pnHandler);
  v15 = &igi2_frame.ptVertices[(_DWORD)ptSortedFaceGroup];
  v16 = 0;
  v17 = &igi2_frame.ptRenderMesh->ptVertex[ptFaceGroup->iStartVertex];
  if ( ptFaceGroup->nNumVertices )
  {
    p_tNormal = &v15->tNormal;
    v19 = (struct RigidDirect3D_SortedFaceGroup_t *)((char *)v15 - (char *)v17);
    p_vY = &v17->tPos.vY;
    for ( ptSortedFaceGroup = v19; ; v19 = ptSortedFaceGroup )
    {
      p_vX = &p_tNormal->vX;
      v22 = igi2_frame.tTempMatrix.tX.vZ * p_vY[1];
      ++v16;
      p_vY += 8;
      p_tNormal = (struct real32x3_t *)((char *)p_tNormal + 32);
      v23 = v22 + igi2_frame.tTempMatrix.tX.vY * *(p_vY - 8) + igi2_frame.tTempMatrix.tX.vX * *(p_vY - 9);
      v24 = igi2_frame.tTempMatrix.tY.vZ * *(p_vY - 7) + igi2_frame.tTempMatrix.tY.vY * *(p_vY - 8) + igi2_frame.tTempMatrix.tY.vX * *(p_vY - 9);
      igi2_frame.Real32x3_Rotate_tTemp.vZ = igi2_frame.tTempMatrix.tZ.vZ * *(p_vY - 7)
                               + igi2_frame.tTempMatrix.tZ.vY * *(p_vY - 8)
                               + igi2_frame.tTempMatrix.tZ.vX * *(p_vY - 9);
      p_tNormal[-4].vY = v23 + igi2_frame.tDeltaPos.vX;
      *(float *)((char *)p_vY + (_DWORD)v19 - 32) = v24 + igi2_frame.tDeltaPos.vY;
      p_tNormal[-3].vX = igi2_frame.Real32x3_Rotate_tTemp.vZ + igi2_frame.tDeltaPos.vZ;
      igi2_frame.tScale.vX = igi2_frame.tTempMatrix.tX.vZ * *(p_vY - 4) + igi2_frame.tTempMatrix.tX.vY * *(p_vY - 5) + igi2_frame.tTempMatrix.tX.vX * *(p_vY - 6);
      igi2_frame.tScale.vY = igi2_frame.tTempMatrix.tY.vZ * *(p_vY - 4) + igi2_frame.tTempMatrix.tY.vY * *(p_vY - 5) + igi2_frame.tTempMatrix.tY.vX * *(p_vY - 6);
      v25 = igi2_frame.tTempMatrix.tZ.vZ * *(p_vY - 4) + igi2_frame.tTempMatrix.tZ.vY * *(p_vY - 5);
      v26 = igi2_frame.tTempMatrix.tZ.vX * *(p_vY - 6);
      *p_vX = igi2_frame.tScale.vX;
      p_vX[1] = igi2_frame.tScale.vY;
      igi2_frame.tScale.vZ = v25 + v26;
      p_vX[2] = igi2_frame.tScale.vZ;
      p_tNormal[-2].vY = *(p_vY - 3);
      p_tNormal[-2].vZ = *(p_vY - 2);
      if ( v16 >= ptFaceGroup->nNumVertices )
        break;
    }
  }
  ptVirModel = v1->ptVirModel;
  ptModel = ptVirModel->ptModel;
  nAnimTextures = ptModel->nAnimTextures;
  dword_834DCD8 ^= 1u;
  if ( nAnimTextures )
  {
    atAnimTexInfo = ptModel->atAnimTexInfo;
    if ( nAnimTextures > 0 )
    {
      p_iTextureToAnimate = &atAnimTexInfo->iTextureToAnimate;
      do
      {
        v32 = *p_iTextureToAnimate;
        v33 = (struct TexInfo_s *)p_iTextureToAnimate[1];
        p_iTextureToAnimate += 5;
        --nAnimTextures;
        ptVirModel->pptTexInfo[v32] = v33;
      }
      while ( nAnimTextures );
    }
  }
}

// source: e/3/pc/pc_direct3drender.c:5046  [size]
void __cdecl Direct3DRender_DrawSortedFaceGroup_Bone(struct BoneDirect3D_SortedFaceGroup_t *ptSortedFaceGroup)
{
  #pragma pack(push, 1)
  union
  {
    struct { unsigned __int16 *v78; };
    struct { char igi2_o1[4]; int v79; };
    struct { char igi2_o2[44]; float tNormalScale; };
    struct { char igi2_o3[44]; float tNormalScalea; };
    struct { char igi2_o4[48]; float tNormalScale_4; };
    struct { char igi2_o5[48]; float tNormalScale_4a; };
    struct { char igi2_o6[52]; float tNormalScale_8; };
    struct { char igi2_o7[52]; float tNormalScale_8a; };
    struct { char igi2_o8[56]; int nOffset; };
    struct { char igi2_o9[60]; int iVertex; };
    struct { char igi2_o10[64]; struct real32x3_t tPosScale; };
    struct { char igi2_o11[76]; struct real32x9_t tNormalRotationMatrix; };
    struct { char igi2_o12[116]; struct real32x3_t Real32x3_Rotate_tTemp; };
    struct { char igi2_o13[128]; struct Direct3DRender_BoneMesh_t *ptRenderMesh; };
    struct { char igi2_o14[132]; struct real32x3_t tDeltaPos; };
    struct { char igi2_o15[144]; struct real32x3_t tRotatedPos; };
    struct { char igi2_o16[156]; struct real32x9_t tPosRotationMatrix; };
    struct { char igi2_o17[196]; float v95; };
    struct { char igi2_o18[200]; float v96; };
    char igi2_extent[208];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  _BYTE *v1; // ebp
  struct RigidDirect3D_FaceGroup_t *ptFaceGroup; // ebx
  struct BoneDirect3D_SortedFaceGroup_t *v3; // eax
  unsigned __int16 iTexture; // cx
  unsigned __int16 iEnvMap; // cx
  struct Direct3DRender_BoneMesh_t *v6; // edx
  double *ptBoneDynCubeObj; // eax
  double v8; // st7
  double v9; // st6
  unsigned __int16 *piIndex; // edx
  int iStartVertex; // eax
  int iStartIndex; // ecx
  unsigned __int16 *v13; // eax
  int nNumVertices; // ecx
  int nNumFaces; // eax
  int v16; // edx
  int v17; // eax
  struct Direct3DRender_BoneVertex_t *v18; // ecx
  int v19; // edi
  bool v20; // zf
  float *v21; // esi
  float *p_iBones; // eax
  struct Direct3DRender_BoneVertexData_t *ptVertexData; // ebp
  char v24; // cl
  int v25; // edx
  struct real32x3_t *v26; // ebp
  int v27; // edx
  double v28; // st7
  struct real32x3_t *v29; // ecx
  double v30; // st6
  double v31; // st5
  int v32; // ecx
  int v33; // edx
  int v34; // ebp
  double v35; // st4
  float *v36; // ecx
  int v37; // edi
  double v38; // st7
  double v39; // st6
  double v40; // st5
  int v41; // ecx
  int v42; // edi
  double v43; // st7
  int v44; // edx
  double v45; // st7
  float *v46; // ecx
  double v47; // st7
  double v48; // st6
  double v49; // st7
  double v50; // st6
  double v51; // st5
  double v52; // st4
  float *v53; // ecx
  double v54; // st5
  double vZ; // st4
  int v56; // edx
  float *p_vZ; // ecx
  struct real32x3_t *ptBones; // esi
  int v59; // eax
  double v60; // st7
  struct real32x3_t *v61; // esi
  double v62; // st6
  double v63; // st5
  float *v64; // eax
  double v65; // st7
  double v66; // st6
  double v67; // st5
  double v68; // st4
  float *v69; // eax
  double v70; // st7
  struct VirModel_s *ptVirModel; // edx
  struct Model_s *ptModel; // eax
  int nAnimTextures; // ecx
  struct ModelAnimTexInfo_s *atAnimTexInfo; // eax
  int *p_iTextureToAnimate; // eax
  int v76; // esi
  struct TexInfo_s *v77; // ebx

  v1 = (_BYTE *)(192 * dword_834DCE0 + 128094384);
  dword_7A290A8 = (int)v1;
  g_pxContext_0 = (void *)(192 * (dword_834DCE0 ^ 1) + 128094384);
  if ( !ptSortedFaceGroup )
  {
    Batch_Flush((unsigned int *)&g_pnHandler_0, (void *)(192 * (dword_834DCE0 ^ 1) + 128094384));
    return;
  }
  Mesh3D_ApplyAnimTexBuffer(ptSortedFaceGroup->ptVirModel, ptSortedFaceGroup->ptAnimTexBuffer);
  Mesh3D_SetDrawAnimTextures(ptSortedFaceGroup->ptVirModel);
  ptFaceGroup = ptSortedFaceGroup->ptFaceGroup;
  v1[12] = ptFaceGroup->bMaterialProperties;
  v3 = ptSortedFaceGroup;
  *((_DWORD *)v1 + 2) = ptSortedFaceGroup->eLayer;
  v1[13] = ptFaceGroup->nTransparency;
  v1[14] = ptFaceGroup->nReflectivity;
  *((_DWORD *)v1 + 46) = 2;
  iTexture = ptFaceGroup->iTexture;
  if ( iTexture == 0xFFFF )
  {
    *(_DWORD *)v1 = 0;
    goto LABEL_7;
  }
  *(_DWORD *)v1 = ptSortedFaceGroup->ptVirModel->pptTexInfo[iTexture]->ptDirect3DBaseTexture;
  iEnvMap = ptFaceGroup->iEnvMap;
  if ( iEnvMap == 0xFFFF )
  {
LABEL_7:
    *((_DWORD *)v1 + 1) = 0;
    goto LABEL_8;
  }
  *((_DWORD *)v1 + 1) = ptSortedFaceGroup->ptVirModel->pptTexInfo[iEnvMap]->ptDirect3DBaseTexture;
LABEL_8:
  if ( memcmp(v1, g_pxContext_0, 0x10u) )
  {
    Batch_Flush((unsigned int *)&g_pnHandler_0, g_pxContext_0);
    v1 = (_BYTE *)dword_7A290A8;
    v3 = ptSortedFaceGroup;
  }
  v6 = v3->ptRenderMesh;
  ptBoneDynCubeObj = (double *)v3->ptBoneDynCubeObj;
  v8 = ptBoneDynCubeObj[5] - TransContext_tActiveTransContext.tPos.vX;
  igi2_frame.tPosScale.vZ = Direct3D_vScale;
  v9 = ptBoneDynCubeObj[6] - TransContext_tActiveTransContext.tPos.vY;
  igi2_frame.tDeltaPos.vZ = ptBoneDynCubeObj[7] - TransContext_tActiveTransContext.tPos.vZ;
  qmemcpy(&igi2_frame.tNormalRotationMatrix, (char *)ptBoneDynCubeObj + 124, sizeof(igi2_frame.tNormalRotationMatrix));
  igi2_frame.tDeltaPos.vX = Direct3D_vScale * v8;
  igi2_frame.tDeltaPos.vY = Direct3D_vScale * v9;
  igi2_frame.ptRenderMesh = v6;
  igi2_frame.tDeltaPos.vZ = Direct3D_vScale * igi2_frame.tDeltaPos.vZ;
  igi2_frame.tPosRotationMatrix.tX.vX = igi2_frame.tNormalRotationMatrix.tX.vX * Direct3D_vScale;
  igi2_frame.tPosRotationMatrix.tX.vY = igi2_frame.tNormalRotationMatrix.tX.vY * Direct3D_vScale;
  igi2_frame.tPosRotationMatrix.tX.vZ = igi2_frame.tNormalRotationMatrix.tX.vZ * Direct3D_vScale;
  igi2_frame.tPosRotationMatrix.tY.vX = igi2_frame.tNormalRotationMatrix.tY.vX * Direct3D_vScale;
  igi2_frame.tPosRotationMatrix.tY.vY = igi2_frame.tNormalRotationMatrix.tY.vY * Direct3D_vScale;
  igi2_frame.tPosRotationMatrix.tY.vZ = igi2_frame.tNormalRotationMatrix.tY.vZ * Direct3D_vScale;
  igi2_frame.tPosRotationMatrix.tZ.vX = igi2_frame.tNormalRotationMatrix.tZ.vX * Direct3D_vScale;
  igi2_frame.tPosRotationMatrix.tZ.vY = igi2_frame.tNormalRotationMatrix.tZ.vY * Direct3D_vScale;
  igi2_frame.tPosRotationMatrix.tZ.vZ = igi2_frame.tNormalRotationMatrix.tZ.vZ * Direct3D_vScale;
  igi2_frame.tNormalRotationMatrix.tX.vX = igi2_frame.tNormalRotationMatrix.tX.vX * Direct3D_vInverseScale;
  igi2_frame.tNormalRotationMatrix.tX.vY = igi2_frame.tNormalRotationMatrix.tX.vY * Direct3D_vInverseScale;
  igi2_frame.tNormalRotationMatrix.tX.vZ = igi2_frame.tNormalRotationMatrix.tX.vZ * Direct3D_vInverseScale;
  igi2_frame.tNormalRotationMatrix.tY.vX = igi2_frame.tNormalRotationMatrix.tY.vX * Direct3D_vInverseScale;
  igi2_frame.tNormalRotationMatrix.tY.vY = igi2_frame.tNormalRotationMatrix.tY.vY * Direct3D_vInverseScale;
  piIndex = v6->piIndex;
  igi2_frame.tNormalRotationMatrix.tY.vZ = igi2_frame.tNormalRotationMatrix.tY.vZ * Direct3D_vInverseScale;
  iStartVertex = ptFaceGroup->iStartVertex;
  iStartIndex = ptFaceGroup->iStartIndex;
  igi2_frame.tNormalRotationMatrix.tZ.vX = igi2_frame.tNormalRotationMatrix.tZ.vX * Direct3D_vInverseScale;
  igi2_frame.v79 = iStartVertex;
  v13 = &piIndex[iStartIndex];
  igi2_frame.tNormalRotationMatrix.tZ.vY = igi2_frame.tNormalRotationMatrix.tZ.vY * Direct3D_vInverseScale;
  nNumVertices = ptFaceGroup->nNumVertices;
  igi2_frame.v78 = v13;
  nNumFaces = ptFaceGroup->nNumFaces;
  igi2_frame.tNormalRotationMatrix.tZ.vZ = igi2_frame.tNormalRotationMatrix.tZ.vZ * Direct3D_vInverseScale;
  Batch_GetLockedVertex(
    BATCH_XYZNORMALTEX1,
    BATCH_INDEX16,
    nNumVertices,
    nNumFaces,
    0,
    igi2_frame.v78,
    igi2_frame.v79,
    Direct3DRender_SortedFaceGroup_Rigid_SetStates,
    Direct3DRender_SortedFaceGroup_Rigid_UnsetStates,
    v1,
    (unsigned __int8 **)&igi2_frame.iVertex,
    &igi2_frame.nOffset,
    (unsigned int *)&g_pnHandler_0);
  v16 = 32 * igi2_frame.nOffset + igi2_frame.iVertex;
  v17 = ptFaceGroup->iStartVertex;
  igi2_frame.nOffset = (int)ptSortedFaceGroup->ptBoneDynCubeObj;
  v18 = &igi2_frame.ptRenderMesh->ptVertexData->ptVertex[v17];
  v19 = 0;
  if ( ptSortedFaceGroup->iLOD )
  {
    if ( ptFaceGroup->nNumVertices )
    {
      v56 = v16 + 8;
      p_vZ = &v18->tVertex.tNormal.vZ;
      do
      {
        ptBones = igi2_frame.ptRenderMesh->ptVertexData->ptBones;
        v59 = (unsigned __int8)*((_DWORD *)p_vZ + 3);
        v60 = *(p_vZ - 5) - ptBones[v59].vX;
        v61 = &ptBones[v59];
        v62 = *(p_vZ - 4) - v61->vY;
        v63 = *(p_vZ - 3) - v61->vZ;
        v64 = (float *)(*(_DWORD *)(igi2_frame.nOffset + 316) + 80 * v59);
        igi2_frame.Real32x3_Rotate_tTemp.vX = v60 * v64[4] + v63 * v64[6] + v62 * v64[5];
        igi2_frame.tRotatedPos.vX = igi2_frame.Real32x3_Rotate_tTemp.vX;
        igi2_frame.Real32x3_Rotate_tTemp.vY = v60 * v64[7] + v63 * v64[9] + v62 * v64[8];
        igi2_frame.tRotatedPos.vY = igi2_frame.Real32x3_Rotate_tTemp.vY;
        igi2_frame.Real32x3_Rotate_tTemp.vZ = v60 * v64[10] + v63 * v64[12] + v62 * v64[11];
        igi2_frame.tRotatedPos.vZ = igi2_frame.Real32x3_Rotate_tTemp.vZ;
        v65 = igi2_frame.Real32x3_Rotate_tTemp.vX + *v64;
        v66 = igi2_frame.Real32x3_Rotate_tTemp.vY + v64[1];
        v67 = igi2_frame.Real32x3_Rotate_tTemp.vZ + v64[2];
        igi2_frame.tNormalScalea = v64[6] * *p_vZ + v64[4] * *(p_vZ - 2) + *(p_vZ - 1) * v64[5];
        igi2_frame.tNormalScale_4a = v64[8] * *(p_vZ - 1) + *(p_vZ - 2) * v64[7] + v64[9] * *p_vZ;
        v68 = v64[12] * *p_vZ + v64[10] * *(p_vZ - 2) + *(p_vZ - 1) * v64[11];
        v69 = (float *)(v56 + 4);
        ++v19;
        p_vZ += 10;
        igi2_frame.tNormalScale_8a = v68;
        v56 += 32;
        igi2_frame.v95 = igi2_frame.tPosRotationMatrix.tX.vZ * v67 + v66 * igi2_frame.tPosRotationMatrix.tX.vY + v65 * igi2_frame.tPosRotationMatrix.tX.vX;
        igi2_frame.v96 = igi2_frame.tPosRotationMatrix.tY.vZ * v67 + v66 * igi2_frame.tPosRotationMatrix.tY.vY + v65 * igi2_frame.tPosRotationMatrix.tY.vX;
        v70 = v67 * igi2_frame.tPosRotationMatrix.tZ.vZ + v66 * igi2_frame.tPosRotationMatrix.tZ.vY + v65 * igi2_frame.tPosRotationMatrix.tZ.vX;
        *(float *)(v56 - 40) = igi2_frame.v95 + igi2_frame.tDeltaPos.vX;
        *(float *)(v56 - 36) = igi2_frame.v96 + igi2_frame.tDeltaPos.vY;
        *(float *)(v56 - 32) = v70 + igi2_frame.tDeltaPos.vZ;
        igi2_frame.tPosScale.vX = igi2_frame.tNormalScale_8a * igi2_frame.tNormalRotationMatrix.tX.vZ
                     + igi2_frame.tNormalScale_4a * igi2_frame.tNormalRotationMatrix.tX.vY
                     + igi2_frame.tNormalScalea * igi2_frame.tNormalRotationMatrix.tX.vX;
        *v69 = igi2_frame.tPosScale.vX;
        igi2_frame.tPosScale.vY = igi2_frame.tNormalScale_8a * igi2_frame.tNormalRotationMatrix.tY.vZ
                     + igi2_frame.tNormalScale_4a * igi2_frame.tNormalRotationMatrix.tY.vY
                     + igi2_frame.tNormalScalea * igi2_frame.tNormalRotationMatrix.tY.vX;
        v69[1] = igi2_frame.tPosScale.vY;
        igi2_frame.tPosScale.vZ = igi2_frame.tNormalScale_8a * igi2_frame.tNormalRotationMatrix.tZ.vZ
                     + igi2_frame.tNormalScale_4a * igi2_frame.tNormalRotationMatrix.tZ.vY
                     + igi2_frame.tNormalScalea * igi2_frame.tNormalRotationMatrix.tZ.vX;
        v69[2] = igi2_frame.tPosScale.vZ;
        *(float *)(v56 - 16) = *(p_vZ - 9);
        *(float *)(v56 - 12) = *(p_vZ - 8);
      }
      while ( v19 < ptFaceGroup->nNumVertices );
    }
  }
  else
  {
    v20 = ptFaceGroup->nNumVertices == 0;
    igi2_frame.iVertex = 0;
    if ( !v20 )
    {
      v21 = (float *)(v16 + 8);
      p_iBones = (float *)&v18->iBones;
      do
      {
        ptVertexData = igi2_frame.ptRenderMesh->ptVertexData;
        v24 = 0;
        v25 = (ptVertexData->pbBoneCount[(v19 + ptFaceGroup->iStartVertex) >> 4] >> (2
                                                                                   * ((v19 + ptFaceGroup->iStartVertex)
                                                                                    & 0xF)))
            & 3;
        if ( v25 )
          v24 = v25;
        v26 = ptVertexData->ptBones;
        v27 = (unsigned __int8)(*(_DWORD *)p_iBones >> (8 * v24));
        v28 = *(p_iBones - 8) - v26[v27].vX;
        v29 = &v26[v27];
        v30 = *(p_iBones - 7) - v29->vY;
        v31 = *(p_iBones - 6) - v29->vZ;
        v32 = 5 * v27;
        v33 = igi2_frame.nOffset;
        v34 = *(_DWORD *)(igi2_frame.nOffset + 316);
        v32 *= 16;
        v35 = v31 * *(float *)(v32 + v34 + 24);
        v36 = (float *)(v34 + v32);
        v37 = (unsigned __int8)*(_DWORD *)p_iBones;
        igi2_frame.tNormalScale = v35 + v30 * v36[5] + v28 * v36[4];
        igi2_frame.tRotatedPos.vX = igi2_frame.tNormalScale;
        igi2_frame.tNormalScale_4 = v31 * v36[9] + v30 * v36[8] + v28 * v36[7];
        igi2_frame.tRotatedPos.vY = igi2_frame.tNormalScale_4;
        igi2_frame.tNormalScale_8 = v31 * v36[12] + v30 * v36[11] + v28 * v36[10];
        igi2_frame.tRotatedPos.vZ = igi2_frame.tNormalScale_8;
        v38 = igi2_frame.tNormalScale + *v36;
        v39 = igi2_frame.tNormalScale_4 + v36[1];
        v40 = igi2_frame.tNormalScale_8 + v36[2];
        igi2_frame.tPosScale.vX = igi2_frame.tPosRotationMatrix.tX.vZ * v40 + v39 * igi2_frame.tPosRotationMatrix.tX.vY + v38 * igi2_frame.tPosRotationMatrix.tX.vX;
        igi2_frame.tPosScale.vY = igi2_frame.tPosRotationMatrix.tY.vZ * v40 + v39 * igi2_frame.tPosRotationMatrix.tY.vY + v38 * igi2_frame.tPosRotationMatrix.tY.vX;
        v41 = 80 * v37;
        v42 = igi2_frame.iVertex;
        v43 = v40 * igi2_frame.tPosRotationMatrix.tZ.vZ + v39 * igi2_frame.tPosRotationMatrix.tZ.vY + v38 * igi2_frame.tPosRotationMatrix.tZ.vX;
        p_iBones += 10;
        *(v21 - 2) = igi2_frame.tPosScale.vX + igi2_frame.tDeltaPos.vX;
        *(v21 - 1) = igi2_frame.tPosScale.vY + igi2_frame.tDeltaPos.vY;
        *v21 = v43 + igi2_frame.tDeltaPos.vZ;
        v44 = *(_DWORD *)(v33 + 316);
        v45 = *(float *)(v41 + v44 + 24);
        v46 = (float *)(v44 + v41);
        v47 = v45 * *(p_iBones - 13);
        v19 = v42 + 1;
        v48 = v46[5];
        igi2_frame.iVertex = v19;
        v49 = v47 + v48 * *(p_iBones - 14) + v46[4] * *(p_iBones - 15);
        v50 = v46[9] * *(p_iBones - 13) + v46[8] * *(p_iBones - 14) + v46[7] * *(p_iBones - 15);
        v51 = v46[12] * *(p_iBones - 13) + v46[11] * *(p_iBones - 14);
        v52 = v46[10];
        v53 = v21 + 1;
        v21 += 8;
        v54 = v51 + v52 * *(p_iBones - 15);
        igi2_frame.Real32x3_Rotate_tTemp.vX = igi2_frame.tNormalRotationMatrix.tX.vZ * v54
                                 + v50 * igi2_frame.tNormalRotationMatrix.tX.vY
                                 + v49 * igi2_frame.tNormalRotationMatrix.tX.vX;
        vZ = igi2_frame.tNormalRotationMatrix.tY.vZ;
        *v53 = igi2_frame.Real32x3_Rotate_tTemp.vX;
        igi2_frame.Real32x3_Rotate_tTemp.vY = vZ * v54 + v50 * igi2_frame.tNormalRotationMatrix.tY.vY + v49 * igi2_frame.tNormalRotationMatrix.tY.vX;
        v53[1] = igi2_frame.Real32x3_Rotate_tTemp.vY;
        igi2_frame.Real32x3_Rotate_tTemp.vZ = v54 * igi2_frame.tNormalRotationMatrix.tZ.vZ
                                 + v50 * igi2_frame.tNormalRotationMatrix.tZ.vY
                                 + v49 * igi2_frame.tNormalRotationMatrix.tZ.vX;
        v53[2] = igi2_frame.Real32x3_Rotate_tTemp.vZ;
        *(v21 - 4) = *(p_iBones - 12);
        *(v21 - 3) = *(p_iBones - 11);
      }
      while ( v19 < ptFaceGroup->nNumVertices );
    }
  }
  ptVirModel = ptSortedFaceGroup->ptVirModel;
  ptModel = ptVirModel->ptModel;
  nAnimTextures = ptModel->nAnimTextures;
  dword_834DCE0 ^= 1u;
  if ( nAnimTextures )
  {
    atAnimTexInfo = ptModel->atAnimTexInfo;
    if ( nAnimTextures > 0 )
    {
      p_iTextureToAnimate = &atAnimTexInfo->iTextureToAnimate;
      do
      {
        v76 = *p_iTextureToAnimate;
        v77 = (struct TexInfo_s *)p_iTextureToAnimate[1];
        p_iTextureToAnimate += 5;
        --nAnimTextures;
        ptVirModel->pptTexInfo[v76] = v77;
      }
      while ( nAnimTextures );
    }
  }
}

// source: e/3/pc/pc_direct3drender.c:5286  [size]
void __cdecl Direct3DRender_SortedFaceGroup_Lightmap_SetStates(struct Batch_SetStatesContext_s *ptContext)
{
  char *pxUserContext; // ebx
  double v2; // st7
  struct RenderStateBlock_t *v3; // eax
  int eCurrentState; // edx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  struct RenderStateBlock_t *v8; // eax
  struct RenderStateBlock_t *v9; // eax
  int v10; // ecx
  char v11; // al
  int v12; // ecx
  bool v13; // zf
  struct RenderStateBlock_t *v14; // eax
  int v15; // edx
  int v16; // ecx
  int v17; // ecx
  struct IDirect3DDevice8Vtbl *lpVtbl; // ecx
  struct RenderStateBlock_t *v19; // eax
  struct IDirect3DBaseTexture8 *v20; // eax
  struct TransContext_s tNewTransContext; // [esp+10h] [ebp-A8h] BYREF

  pxUserContext = (char *)ptContext->pxUserContext;
  if ( !*((_DWORD *)pxUserContext + 2) )
  {
    qmemcpy(pxUserContext + 16, &TransContext_tActiveTransContext, 0xA8u);
    v2 = (double)Display_tActiveMode.nHeight * 4.0 / ((double)Display_tActiveMode.nWidth * 3.0);
    qmemcpy(&tNewTransContext, pxUserContext + 16, sizeof(tNewTransContext));
    tNewTransContext.vFOVX = Mesh3D_avOverrideFOV[0];
    tNewTransContext.eLayer = TRANSCONTEXT_LAYER_FRONT;
    tNewTransContext.vFOVY = Mesh3D_avOverrideFOV[0]
                           * RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHeight
                           / (v2
                            * RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vWidth);
    tNewTransContext.vScreenFOVX = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHalfWidth
                                 / Mesh3D_avOverrideFOV[0];
    tNewTransContext.vScreenFOVY = v2 * tNewTransContext.vScreenFOVX;
    TransContext_SetActiveTransContext(&tNewTransContext);
  }
  v3 = Direct3D_ptTextureStateBlock;
  eCurrentState = Direct3D_ptTextureStateBlock->eCurrentState;
  if ( *((_DWORD *)pxUserContext + 1) )
  {
    v5 = Direct3DRender_eTextureStateLightmap;
    if ( eCurrentState != Direct3DRender_eTextureStateLightmap )
    {
      Direct3D_ptTextureStateBlock->eCurrentState = Direct3DRender_eTextureStateLightmap;
      v3->atRenderState[v5].pfCallback(nullptr);
    }
    v6 = Direct3DRender_eGenericStateTransparentLightmap;
  }
  else
  {
    v7 = Direct3DRender_eTextureStateRigid;
    if ( eCurrentState != Direct3DRender_eTextureStateRigid )
    {
      Direct3D_ptTextureStateBlock->eCurrentState = Direct3DRender_eTextureStateRigid;
      v3->atRenderState[v7].pfCallback(nullptr);
    }
    v6 = Direct3DRender_eGenericStateTransparentRigid;
  }
  v8 = Direct3D_ptGenericStateBlock;
  if ( Direct3D_ptGenericStateBlock->eCurrentState != v6 )
  {
    Direct3D_ptGenericStateBlock->eCurrentState = v6;
    v8->atRenderState[v6].pfCallback(nullptr);
  }
  v9 = Direct3D_ptClippingStateBlock;
  v10 = Direct3D_eClippingStateOn;
  if ( Direct3D_ptClippingStateBlock->eCurrentState != Direct3D_eClippingStateOn )
  {
    Direct3D_ptClippingStateBlock->eCurrentState = Direct3D_eClippingStateOn;
    v9->atRenderState[v10].pfCallback(nullptr);
  }
  v11 = pxUserContext[12];
  if ( (v11 & 0x40) != 0 )
  {
    v12 = Direct3DRender_eBlendStateAlphaTest;
    goto LABEL_27;
  }
  if ( (v11 & 4) == 0 )
  {
    v12 = Direct3DRender_eBlendStateOpaque;
LABEL_27:
    v19 = Direct3D_ptBlendStateBlock;
    if ( Direct3D_ptBlendStateBlock->eCurrentState != v12 )
    {
      Direct3D_ptBlendStateBlock->eCurrentState = v12;
      v19->atRenderState[v12].pfCallback(nullptr);
    }
    goto LABEL_29;
  }
  v13 = (v11 & 1) == 0;
  v14 = Direct3D_ptBlendStateBlock;
  v15 = Direct3D_ptBlendStateBlock->eCurrentState;
  if ( v13 )
  {
    v17 = Direct3DRender_eBlendStateTransparent;
    if ( v15 != Direct3DRender_eBlendStateTransparent )
    {
      Direct3D_ptBlendStateBlock->eCurrentState = Direct3DRender_eBlendStateTransparent;
      v14->atRenderState[v17].pfCallback(nullptr);
    }
    lpVtbl = Direct3D_ptDevice->lpVtbl;
    if ( *((_DWORD *)pxUserContext + 1) )
    {
      lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_LIGHTING, 0);
      Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLOROP, 2u);
    }
    else
    {
      lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_LIGHTING, 1u);
      Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLOROP, 4u);
    }
  }
  else
  {
    v16 = Direct3DRender_eBlendStateAdditive;
    if ( v15 != Direct3DRender_eBlendStateAdditive )
    {
      Direct3D_ptBlendStateBlock->eCurrentState = Direct3DRender_eBlendStateAdditive;
      v14->atRenderState[v16].pfCallback(nullptr);
    }
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_LIGHTING, 0);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLOROP, 2u);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGENABLE, 0);
  }
LABEL_29:
  Direct3D_ptDevice->lpVtbl->SetRenderState(
    Direct3D_ptDevice,
    D3DRS_TEXTUREFACTOR,
    (-1 - (unsigned __int8)pxUserContext[13]) << 24);
  if ( *(_DWORD *)pxUserContext )
  {
    if ( *(struct IDirect3DBaseTexture8 **)pxUserContext != Direct3D_tState.aptTexture[0] )
    {
      Direct3D_tState.aptTexture[0] = *(struct IDirect3DBaseTexture8 **)pxUserContext;
      Direct3D_ptDevice->lpVtbl->SetTexture(Direct3D_ptDevice, 0, Direct3D_tState.aptTexture[0]);
    }
    v20 = *((struct IDirect3DBaseTexture8 **)pxUserContext + 1);
    if ( v20 && v20 != Direct3D_tState.aptTexture[1] )
    {
      Direct3D_tState.aptTexture[1] = *((struct IDirect3DBaseTexture8 **)pxUserContext + 1);
      Direct3D_ptDevice->lpVtbl->SetTexture(Direct3D_ptDevice, 1u, Direct3D_tState.aptTexture[1]);
    }
  }
  else if ( Direct3D_tState.aptTexture[0] )
  {
    Direct3D_tState.aptTexture[0] = nullptr;
    Direct3D_ptDevice->lpVtbl->SetTexture(Direct3D_ptDevice, 0, nullptr);
  }
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGVERTEXMODE, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZWRITEENABLE, 0);
}

// source: e/3/pc/pc_direct3drender.c:5404  [size]
void __cdecl Direct3DRender_SortedFaceGroup_Lightmap_UnsetStates(struct Batch_SetStatesContext_s *ptContext)
{
  char *pxUserContext; // eax

  pxUserContext = (char *)ptContext->pxUserContext;
  if ( !*((_DWORD *)pxUserContext + 2) )
    TransContext_SetActiveTransContext((struct TransContext_s *)(pxUserContext + 16));
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGVERTEXMODE, 3u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZWRITEENABLE, 1u);
}

// source: e/3/pc/pc_direct3drender.c:5425  [size]
void __cdecl Direct3DRender_DrawSortedFaceGroup_Lightmap(struct LightmapDirect3D_SortedFaceGroup_t *ptSortedFaceGroup)
{
  #pragma pack(push, 1)
  union
  {
    struct { void *v25; };
    struct { char igi2_o1[4]; int iStartVertex; };
    struct { char igi2_o2[12]; struct IDirect3DBaseTexture8 **v27; };
    struct { char igi2_o3[44]; struct LightmapDirect3D_Vertex_t *ptVertices; };
    struct { char igi2_o4[48]; struct Mesh3D_RenderMesh_LightmapDirect3D_t *ptRenderMesh; };
    struct { char igi2_o5[52]; struct real32x3_t tDeltaPos; };
    struct { char igi2_o6[64]; struct real32x3_t tScale; };
    struct { char igi2_o7[76]; struct real32x9_t tTempMatrix; };
    char igi2_extent[116];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct LightmapDirect3D_SortedFaceGroup_t *v1; // ebx
  struct IDirect3DBaseTexture8 **v2; // eax
  void *v3; // edi
  struct LightmapDirect3D_FaceGroup_t *ptFaceGroup; // ebp
  unsigned __int16 iTexture; // cx
  struct Mesh3D_LightmapList_s *ptLightmapList; // ecx
  double v7; // st7
  double v8; // st6
  struct Mesh3D_RenderMesh_LightmapDirect3D_t *v9; // edx
  int iStartIndex; // ecx
  double v11; // st7
  double v12; // st6
  int v13; // eax
  int nNumVertices; // ecx
  int nNumFaces; // eax
  struct LightmapDirect3D_Vertex_t *v16; // edi
  int v17; // esi
  struct LightmapDirect3D_Vertex_t *v18; // edx
  struct real32x2_t *p_tUV; // ecx
  float *p_vY; // eax
  int v21; // edi
  double v22; // st7
  double v23; // st7
  double v24; // st6

  v1 = ptSortedFaceGroup;
  v2 = (struct IDirect3DBaseTexture8 **)(184 * dword_834DCE8 + 128103568);
  v3 = (void *)(184 * (dword_834DCE8 ^ 1) + 128103568);
  dword_7AB4188 = (int)v2;
  g_pxContext_1 = v3;
  if ( !ptSortedFaceGroup )
  {
    Batch_Flush((unsigned int *)&g_pnHandler_1, (void *)(184 * (dword_834DCE8 ^ 1) + 128103568));
    return;
  }
  ptFaceGroup = ptSortedFaceGroup->ptFaceGroup;
  byte_7A2B49C[184 * dword_834DCE8] = ptFaceGroup->bMaterialProperties;
  v2[2] = (struct IDirect3DBaseTexture8 *)v1->eLayer;
  *((_BYTE *)v2 + 13) = ptFaceGroup->nTransparency;
  iTexture = ptFaceGroup->iTexture;
  if ( iTexture == 0xFFFF )
  {
    *v2 = nullptr;
    goto LABEL_7;
  }
  *v2 = v1->ptVirModel->pptTexInfo[iTexture]->ptDirect3DBaseTexture;
  ptLightmapList = v1->ptLightmapList;
  if ( !ptLightmapList )
  {
LABEL_7:
    v2[1] = nullptr;
    goto LABEL_8;
  }
  v2[1] = ptLightmapList->atLightmap[ptFaceGroup->iLightmap].tTexInfo.ptDirect3DBaseTexture;
LABEL_8:
  if ( memcmp(v2, v3, 0x10u) )
  {
    Batch_Flush((unsigned int *)&g_pnHandler_1, g_pxContext_1);
    v2 = (struct IDirect3DBaseTexture8 **)dword_7AB4188;
  }
  v7 = v1->tPos.vX - TransContext_tActiveTransContext.tPos.vX;
  v8 = v1->tPos.vY - TransContext_tActiveTransContext.tPos.vY;
  qmemcpy(&igi2_frame.tTempMatrix, &v1->tOrientation, sizeof(igi2_frame.tTempMatrix));
  igi2_frame.tDeltaPos.vZ = v1->tPos.vZ - TransContext_tActiveTransContext.tPos.vZ;
  igi2_frame.tDeltaPos.vX = Direct3D_vScale * v7;
  v9 = v1->ptRenderMesh;
  igi2_frame.tDeltaPos.vY = Direct3D_vScale * v8;
  iStartIndex = ptFaceGroup->iStartIndex;
  igi2_frame.v27 = v2;
  igi2_frame.tDeltaPos.vZ = Direct3D_vScale * igi2_frame.tDeltaPos.vZ;
  v11 = Direct3D_vScale * v1->tScale.vX;
  v12 = Direct3D_vScale * v1->tScale.vY;
  igi2_frame.iStartVertex = ptFaceGroup->iStartVertex;
  igi2_frame.ptRenderMesh = v9;
  v13 = (int)&v9->piIndex[iStartIndex];
  nNumVertices = ptFaceGroup->nNumVertices;
  igi2_frame.tScale.vZ = Direct3D_vScale * v1->tScale.vZ;
  igi2_frame.v25 = (void *)v13;
  nNumFaces = ptFaceGroup->nNumFaces;
  igi2_frame.tTempMatrix.tX.vX = igi2_frame.tTempMatrix.tX.vX * v11;
  igi2_frame.tTempMatrix.tX.vY = igi2_frame.tTempMatrix.tX.vY * v12;
  igi2_frame.tTempMatrix.tX.vZ = igi2_frame.tTempMatrix.tX.vZ * igi2_frame.tScale.vZ;
  igi2_frame.tTempMatrix.tY.vX = igi2_frame.tTempMatrix.tY.vX * v11;
  igi2_frame.tTempMatrix.tY.vY = igi2_frame.tTempMatrix.tY.vY * v12;
  igi2_frame.tTempMatrix.tY.vZ = igi2_frame.tTempMatrix.tY.vZ * igi2_frame.tScale.vZ;
  igi2_frame.tTempMatrix.tZ.vX = igi2_frame.tTempMatrix.tZ.vX * v11;
  igi2_frame.tTempMatrix.tZ.vY = igi2_frame.tTempMatrix.tZ.vY * v12;
  igi2_frame.tTempMatrix.tZ.vZ = igi2_frame.tTempMatrix.tZ.vZ * igi2_frame.tScale.vZ;
  Batch_GetLockedVertex(
    BATCH_XYZTEX2,
    BATCH_INDEX16,
    nNumVertices,
    nNumFaces,
    0,
    igi2_frame.v25,
    igi2_frame.iStartVertex,
    Direct3DRender_SortedFaceGroup_Lightmap_SetStates,
    Direct3DRender_SortedFaceGroup_Lightmap_UnsetStates,
    igi2_frame.v27,
    (unsigned __int8 **)&igi2_frame.ptVertices,
    (int *)&ptSortedFaceGroup,
    (unsigned int *)&g_pnHandler_1);
  v16 = &igi2_frame.ptVertices[(_DWORD)ptSortedFaceGroup];
  v17 = 0;
  v18 = &igi2_frame.ptRenderMesh->ptVertex[ptFaceGroup->iStartVertex];
  if ( ptFaceGroup->nNumVertices )
  {
    p_tUV = &v16->tUV;
    p_vY = &v18->tPos.vY;
    v21 = (char *)v16 - (char *)v18;
    do
    {
      ++v17;
      v22 = igi2_frame.tTempMatrix.tX.vZ * p_vY[1];
      p_vY += 7;
      p_tUV = (struct real32x2_t *)((char *)p_tUV + 28);
      v23 = v22 + igi2_frame.tTempMatrix.tX.vX * *(p_vY - 8) + igi2_frame.tTempMatrix.tX.vY * *(p_vY - 7);
      v24 = igi2_frame.tTempMatrix.tY.vZ * *(p_vY - 6) + igi2_frame.tTempMatrix.tY.vX * *(p_vY - 8) + igi2_frame.tTempMatrix.tY.vY * *(p_vY - 7);
      igi2_frame.tScale.vZ = igi2_frame.tTempMatrix.tZ.vZ * *(p_vY - 6) + igi2_frame.tTempMatrix.tZ.vX * *(p_vY - 8) + igi2_frame.tTempMatrix.tZ.vY * *(p_vY - 7);
      p_tUV[-5].vX = v23 + igi2_frame.tDeltaPos.vX;
      *(float *)((char *)p_vY + v21 - 28) = v24 + igi2_frame.tDeltaPos.vY;
      p_tUV[-4].vX = igi2_frame.tScale.vZ + igi2_frame.tDeltaPos.vZ;
      p_tUV[-4].vY = *(p_vY - 5);
      p_tUV[-3].vX = *(p_vY - 4);
      p_tUV[-3].vY = *(p_vY - 3);
      p_tUV[-2].vX = *(p_vY - 2);
    }
    while ( v17 < ptFaceGroup->nNumVertices );
  }
  dword_834DCE8 ^= 1u;
}

// source: e/3/pc/pc_direct3drender.c:5562  [size]
void __cdecl Direct3DRender_IsTransparent(struct IsTransparentContext_t *ptContext)
{
  struct RigidDynCubeObj_t *ptRigidDynCubeObj; // eax
  struct LODVirModel_s *ptLODVirModel; // eax
  struct VirModel_s *v3; // eax
  struct Mesh3D_Mesh_t *ptMesh; // esi
  _DWORD *pxRenderMesh; // edx
  int v6; // ecx
  int v7; // eax
  _BYTE *v8; // edx
  _DWORD *v9; // esi
  int v10; // ecx
  int v11; // eax
  _BYTE *i; // edx

  ptRigidDynCubeObj = ptContext->ptRigidDynCubeObj;
  ptContext->isTransparent = 0;
  ptLODVirModel = ptRigidDynCubeObj->tModelObj.ptLODVirModel;
  if ( ptLODVirModel )
  {
    v3 = ptLODVirModel->aptVirModel[ptContext->iLOD];
    if ( v3 )
    {
      ptMesh = v3->ptModel->ptMesh;
      if ( ptMesh->eRenderMeshType == MESH3D_RENDERMESHTYPE_DIRECT3D_RIGID )
      {
        pxRenderMesh = ptMesh->pxRenderMesh;
        v6 = pxRenderMesh[2];
        v7 = 0;
        if ( v6 > 0 )
        {
          v8 = (_BYTE *)pxRenderMesh[6];
          while ( (*v8 & 0x44) == 0 )
          {
            ++v7;
            v8 += 32;
            if ( v7 >= v6 )
              goto LABEL_10;
          }
          ptContext->isTransparent = 1;
        }
      }
LABEL_10:
      if ( ptMesh->eRenderMeshType == MESH3D_RENDERMESHTYPE_DIRECT3D_BUILDING )
      {
        v9 = ptMesh->pxRenderMesh;
        v10 = v9[3];
        v11 = 0;
        if ( v10 > 0 )
        {
          for ( i = (_BYTE *)v9[8]; (*i & 0x44) == 0; i += 28 )
          {
            if ( ++v11 >= v10 )
              return;
          }
          ptContext->isTransparent = 1;
        }
      }
    }
  }
}

// source: e/3/pc/pc_direct3drender.c:5620  [size]
void __cdecl Direct3DRender_DrawRigidMesh(struct DrawRigidMeshContext_t *ptContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vZ; };
    struct { float vZa; };
    struct { char igi2_o2[20]; struct LODVirModel_s *ptLODVirModel; };
    struct { char igi2_o3[20]; struct LODVirModel_s *ptLODVirModela; };
    struct { char igi2_o4[20]; unsigned int ptLODVirModelb; };
    struct { char igi2_o5[20]; float *ptLODVirModelc; };
    struct { char igi2_o6[20]; float *ptLODVirModeld; };
    struct { char igi2_o7[20]; struct LODVirModel_s *ptLODVirModele; };
    struct { char igi2_o8[24]; int i; };
    struct { char igi2_o9[28]; enum bool isExclude; };
    struct { char igi2_o10[32]; enum bool isTotallyInside; };
    struct { char igi2_o11[36]; struct RigidDirect3D_SortedFaceGroup_t *ptSortedFaceGroup; };
    struct { char igi2_o12[40]; struct real32x3_t tOldClipMin; };
    struct { char igi2_o13[52]; struct real32x2_t tOldClipMax; };
    struct { char igi2_o14[60]; float v142; };
    struct { char igi2_o15[64]; struct real32x3_t tPos; };
    struct { char igi2_o16[76]; struct real32x3_t tAveragePos; };
    struct { char igi2_o17[88]; struct real32x9_t tTempMatrix; };
    struct { char igi2_o18[128]; struct real32x3_t tScale; };
    struct { char igi2_o19[140]; struct TransContext_s tNewTransContext; };
    struct { char igi2_o20[308]; struct _D3DMATRIX tLocalMatrix; };
    struct { char igi2_o21[372]; struct TransContext_s tOldTransContext; };
    char igi2_extent[540];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct RigidDynCubeObj_t *ptRigidDynCubeObj; // ebx
  int v2; // esi
  struct LODVirModel_s *v3; // eax
  _DWORD *ptSector; // edi
  int v5; // eax
  struct real32x2_t *v6; // eax
  float vX; // edx
  enum bool v8; // ecx
  unsigned int *p_nAllocated; // edi
  struct real32x2_t *v10; // eax
  enum bool v11; // eax
  bool v12; // cc
  unsigned __int16 eQTaskType; // ax
  int v14; // eax
  enum TransContext_Layer_e eLayer; // ecx
  struct VirModel_s *v16; // esi
  struct LODVirModel_s *ptMesh; // ecx
  int isLODDistanceSpecified; // edx
  void (__cdecl *pfHandler)(struct RigidDynCubeObj_t *, int *); // ecx
  double AspectRatio; // st7
  struct RenderStateBlock_t *v21; // eax
  int v22; // ecx
  double v23; // st7
  double v24; // st6
  double v25; // st7
  double v26; // st6
  enum Mesh3D_DrawMode_e eDrawMode; // ecx
  struct LODVirModel_s *v28; // esi
  int v29; // edx
  float *v30; // ecx
  float v31; // eax
  int nNumItems; // ecx
  double v33; // st6
  struct SortRenderItem_t *v34; // eax
  double v35; // st7
  int v36; // ecx
  double v37; // st6
  unsigned __int8 *v38; // ecx
  int iVertex; // eax
  double v40; // st7
  float *v41; // eax
  double v42; // st7
  double v43; // st6
  double v44; // st7
  _DWORD *v45; // eax
  int iVertex_low; // ecx
  int v47; // eax
  float v48; // edi
  int v49; // ecx
  int v50; // edx
  struct RenderStateBlock_t *v51; // eax
  int eCurrentState; // edx
  int v53; // ecx
  struct RenderStateBlock_t *v54; // eax
  int v55; // ecx
  int v56; // ecx
  struct RenderStateBlock_t *v57; // edx
  int v58; // ecx
  int v59; // eax
  struct IDirect3DIndexBuffer8 *v60; // eax
  struct SortRenderList_t *v61; // esi
  struct RigidDirect3D_FaceGroup_t *v62; // edi
  float v63; // eax
  float v64; // ecx
  int v65; // edx
  double v66; // st7
  int v67; // ecx
  double v68; // st6
  int v69; // eax
  int v70; // edx
  int v71; // ecx
  double v72; // st7
  struct RigidDirect3D_SortedFaceGroup_t *v73; // esi
  unsigned int *v74; // edi
  struct VirModel_s *v75; // esi
  struct RigidDirect3D_SortedFaceGroup_t *v76; // eax
  enum bool v77; // ecx
  float v78; // edx
  int v79; // ecx
  struct RigidDirect3D_SortedFaceGroup_t **v80; // eax
  _DWORD *v81; // ecx
  float *v82; // edi
  int v83; // eax
  float v84; // edx
  int v85; // ecx
  struct RenderStateBlock_t *v86; // eax
  struct RenderStateBlock_t *v87; // eax
  int v88; // ecx
  int v89; // ecx
  struct RenderStateBlock_t *v90; // edx
  int v91; // ecx
  int v92; // eax
  unsigned __int16 v93; // ax
  float v94; // ecx
  float v95; // edx
  struct real64x3_t *v96; // eax
  int iLightCategory; // edx
  int v98; // edx
  struct RigidDirect3D_SortedFaceGroup_t *v99; // ecx
  int *v100; // esi
  char v101; // al
  int v102; // ecx
  bool v103; // zf
  struct RenderStateBlock_t *v104; // eax
  int v105; // edx
  int v106; // ecx
  struct LODVirModel_s *v107; // ecx
  unsigned int v108; // edi
  int v109; // eax
  float v110; // edx
  int v111; // ecx
  struct RenderStateBlock_t *v112; // eax
  struct RenderStateBlock_t *v113; // eax
  int v114; // ecx
  int v115; // ecx
  struct RenderStateBlock_t *v116; // edx
  int v117; // ecx
  int v118; // eax
  float v119; // edx
  float v120; // eax
  struct real64x3_t *v121; // eax
  enum bool v122; // ecx
  int v123; // ecx
  unsigned __int16 v124; // ax
  struct IDirect3DBaseTexture8 *v125; // eax
  int v126; // ecx
  struct RenderStateBlock_t *v127; // eax

  igi2_frame.tOldClipMin.vX = RenderContext_tActiveRenderContext.tDisplayAreaMin.vX;
  igi2_frame.tOldClipMin.vY = RenderContext_tActiveRenderContext.tDisplayAreaMin.vY;
  ptRigidDynCubeObj = ptContext->ptRigidDynCubeObj;
  v2 = 0;
  igi2_frame.tOldClipMax.vY = RenderContext_tActiveRenderContext.tDisplayAreaMax.vY;
  igi2_frame.isTotallyInside = false;
  v3 = ptRigidDynCubeObj->tModelObj.ptLODVirModel;
  igi2_frame.tOldClipMax.vX = RenderContext_tActiveRenderContext.tDisplayAreaMax.vX;
  igi2_frame.isExclude = true;
  igi2_frame.ptLODVirModel = v3;
  if ( !v3 )
  {
    v3 = MTP_ptMissingModel;
    igi2_frame.ptLODVirModel = MTP_ptMissingModel;
  }
  if ( v3 == MTP_ptMissingModel && ptContext->eDrawMode == MESH3D_DRAWMODE_ENVMAP || !v3->nLOD )
    return;
  ptSector = ptRigidDynCubeObj->tModelObj.tDynCubeObj.ptSector;
  if ( ptContext->isExcludeTestPassed )
  {
    igi2_frame.isTotallyInside = false;
    goto LABEL_23;
  }
  if ( ptSector )
  {
    if ( !ptSector[98] )
      return;
    v5 = ptSector[81];
    if ( *(int *)(v5 + 36) > 0 )
    {
      do
      {
        v6 = *(struct real32x2_t **)(*(_DWORD *)(v5 + 48) + 4 * v2);
        RenderContext_tActiveRenderContext.tDisplayAreaMin = *v6;
        vX = v6[1].vX;
        ++RenderContext_nActiveRenderContextTimeStamp;
        RenderContext_tActiveRenderContext.tDisplayAreaMax.vX = vX;
        RenderContext_tActiveRenderContext.tDisplayAreaMax.vY = v6[1].vY;
        v8 = ModelObj_Exclude(&ptRigidDynCubeObj->tModelObj, &igi2_frame.isTotallyInside) & igi2_frame.isExclude;
        v5 = ptSector[81];
        igi2_frame.isExclude = v8;
        ++v2;
      }
      while ( v2 < (int)(*(_DWORD *)(v5 + 36)) );
    }
  }
  else
  {
    if ( !Clipping_tClipData.tClipWindows.ptClipWindowsList )
    {
      if ( QCube_ptInsideSectorObject )
      {
        eQTaskType = ptRigidDynCubeObj->tModelObj.tDynCubeObj.tQObj.tQTask.eQTaskType;
        if ( eQTaskType != ConveyorBelt_eQTaskType && eQTaskType != Door_eQTaskType )
          return;
      }
      igi2_frame.isExclude = ModelObj_Exclude(&ptRigidDynCubeObj->tModelObj, &igi2_frame.isTotallyInside);
      goto LABEL_22;
    }
    p_nAllocated = &Clipping_tClipData.tClipWindows.ptClipWindowsList->nAllocated;
    if ( (int)Clipping_tClipData.tClipWindows.ptClipWindowsList->nAllocated > 0 )
    {
      igi2_frame.ptSortedFaceGroup = (struct RigidDirect3D_SortedFaceGroup_t *)&Clipping_tClipData.tClipWindows.ptClipWindowsList->papxElement;
      do
      {
        v10 = *(struct real32x2_t **)(LODWORD(igi2_frame.ptSortedFaceGroup->tPos.vX) + 4 * v2);
        RenderContext_tActiveRenderContext.tDisplayAreaMin = *v10;
        RenderContext_tActiveRenderContext.tDisplayAreaMax = v10[1];
        ++RenderContext_nActiveRenderContextTimeStamp;
        v11 = ModelObj_Exclude(&ptRigidDynCubeObj->tModelObj, &igi2_frame.isTotallyInside);
        v12 = ++v2 < (int)*p_nAllocated;
        igi2_frame.isExclude &= v11;
      }
      while ( v12 );
    }
  }
  RenderContext_tActiveRenderContext.tDisplayAreaMin.vY = igi2_frame.tOldClipMin.vY;
  RenderContext_tActiveRenderContext.tDisplayAreaMin.vX = igi2_frame.tOldClipMin.vX;
  RenderContext_tActiveRenderContext.tDisplayAreaMax = igi2_frame.tOldClipMax;
  ++RenderContext_nActiveRenderContextTimeStamp;
LABEL_22:
  if ( igi2_frame.isExclude )
    return;
LABEL_23:
  *(float *)&v14 = COERCE_FLOAT(ModelObj_GetLOD(&ptRigidDynCubeObj->tModelObj));
  eLayer = ptRigidDynCubeObj->tModelObj.eLayer;
  igi2_frame.ptSortedFaceGroup = (struct RigidDirect3D_SortedFaceGroup_t *)v14;
  if ( eLayer )
  {
    if ( *(unsigned int *)&v14 == 0xffffffffu )
      return;
  }
  else
  {
    *(float *)&v14 = 0.0;
    igi2_frame.ptSortedFaceGroup = nullptr;
  }
  v16 = igi2_frame.ptLODVirModel->aptVirModel[v14];
  ptMesh = (struct LODVirModel_s *)v16->ptModel->ptMesh;
  isLODDistanceSpecified = ptMesh->isLODDistanceSpecified;
  igi2_frame.isExclude = (enum bool)v16;
  igi2_frame.ptLODVirModela = ptMesh;
  if ( isLODDistanceSpecified )
  {
    pfHandler = (void (__cdecl *)(struct RigidDynCubeObj_t *, int *))QTask_aatQTaskFinalEvent[RigidDynCubeObj_eRenderStartEvent][ptRigidDynCubeObj->tModelObj.tDynCubeObj.tQObj.tQTask.eQTaskType].pfHandler;
    if ( pfHandler )
    {
      igi2_frame.i = v14;
      pfHandler(ptRigidDynCubeObj, &igi2_frame.i);
    }
    Mesh3D_SetDrawAnimTextures(v16);
    if ( ptRigidDynCubeObj->tModelObj.eLayer == TRANSCONTEXT_LAYER_FRONT )
    {
      if ( ptContext->eDrawMode == MESH3D_DRAWMODE_ENVMAP )
        return;
      qmemcpy(&igi2_frame.tOldTransContext, &TransContext_tActiveTransContext, sizeof(igi2_frame.tOldTransContext));
      *(float *)&igi2_frame.i = Mesh3D_avOverrideFOV[0] * RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHeight;
      qmemcpy(&igi2_frame.tNewTransContext, &igi2_frame.tOldTransContext, sizeof(igi2_frame.tNewTransContext));
      igi2_frame.tNewTransContext.vFOVX = Mesh3D_avOverrideFOV[0];
      igi2_frame.tNewTransContext.vFOVY = *(float *)&igi2_frame.i
                             / (Display_GetAspectRatio()
                              * RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vWidth);
      igi2_frame.tNewTransContext.vScreenFOVX = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHalfWidth
                                   / igi2_frame.tNewTransContext.vFOVX;
      AspectRatio = Display_GetAspectRatio();
      igi2_frame.tNewTransContext.eLayer = TRANSCONTEXT_LAYER_FRONT;
      igi2_frame.tNewTransContext.vScreenFOVY = AspectRatio * igi2_frame.tNewTransContext.vScreenFOVX;
      TransContext_SetActiveTransContext(&igi2_frame.tNewTransContext);
      v21 = Direct3D_ptTextureStateBlock;
      v22 = Direct3DRender_eTextureStateRigid;
      if ( Direct3D_ptTextureStateBlock->eCurrentState != Direct3DRender_eTextureStateRigid )
      {
        Direct3D_ptTextureStateBlock->eCurrentState = Direct3DRender_eTextureStateRigid;
        v21->atRenderState[v22].pfCallback(nullptr);
      }
      Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_MIPFILTER, 0);
      Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_MIPFILTER, 0);
    }
    v23 = ptRigidDynCubeObj->tModelObj.tDynCubeObj.tQObj.tPos.vX - TransContext_tActiveTransContext.tPos.vX;
    v24 = ptRigidDynCubeObj->tModelObj.tDynCubeObj.tQObj.tPos.vY - TransContext_tActiveTransContext.tPos.vY;
    qmemcpy(&igi2_frame.tTempMatrix, &ptRigidDynCubeObj->tModelObj.tOrientation, sizeof(igi2_frame.tTempMatrix));
    igi2_frame.tOldClipMin.vZ = ptRigidDynCubeObj->tModelObj.tDynCubeObj.tQObj.tPos.vZ - TransContext_tActiveTransContext.tPos.vZ;
    igi2_frame.tOldClipMin.vX = v23 * Direct3D_vScale;
    igi2_frame.tOldClipMin.vY = v24 * Direct3D_vScale;
    igi2_frame.tOldClipMin.vZ = igi2_frame.tOldClipMin.vZ * Direct3D_vScale;
    v25 = Direct3D_vScale * ptRigidDynCubeObj->tModelObj.tScale.vX;
    v26 = Direct3D_vScale * ptRigidDynCubeObj->tModelObj.tScale.vY;
    igi2_frame.tScale.vZ = Direct3D_vScale * ptRigidDynCubeObj->tModelObj.tScale.vZ;
    igi2_frame.tTempMatrix.tX.vX = igi2_frame.tTempMatrix.tX.vX * v25;
    igi2_frame.tTempMatrix.tX.vY = igi2_frame.tTempMatrix.tX.vY * v26;
    igi2_frame.tTempMatrix.tX.vZ = igi2_frame.tTempMatrix.tX.vZ * igi2_frame.tScale.vZ;
    igi2_frame.tTempMatrix.tY.vX = igi2_frame.tTempMatrix.tY.vX * v25;
    igi2_frame.tTempMatrix.tY.vY = igi2_frame.tTempMatrix.tY.vY * v26;
    igi2_frame.tTempMatrix.tY.vZ = igi2_frame.tTempMatrix.tY.vZ * igi2_frame.tScale.vZ;
    igi2_frame.tTempMatrix.tZ.vX = igi2_frame.tTempMatrix.tZ.vX * v25;
    igi2_frame.tTempMatrix.tZ.vY = igi2_frame.tTempMatrix.tZ.vY * v26;
    igi2_frame.tTempMatrix.tZ.vZ = igi2_frame.tTempMatrix.tZ.vZ * igi2_frame.tScale.vZ;
    Direct3D_D3DMATRIXFromReal32x9(&igi2_frame.tLocalMatrix, &igi2_frame.tTempMatrix, &igi2_frame.tOldClipMin);
    Direct3D_ptDevice->lpVtbl->SetTransform(Direct3D_ptDevice, (enum _D3DTRANSFORMSTATETYPE)256, &igi2_frame.tLocalMatrix);
    igi2_frame.tTempMatrix.tZ.vX = TransContext_tActiveTransContext.tMatrix.tZ.vX * ptRigidDynCubeObj->tModelObj.tOrientation.tX.vX
                      + TransContext_tActiveTransContext.tMatrix.tZ.vZ * ptRigidDynCubeObj->tModelObj.tOrientation.tZ.vX
                      + TransContext_tActiveTransContext.tMatrix.tZ.vY * ptRigidDynCubeObj->tModelObj.tOrientation.tY.vX;
    eDrawMode = ptContext->eDrawMode;
    v28 = igi2_frame.ptLODVirModela;
    igi2_frame.tTempMatrix.tZ.vY = TransContext_tActiveTransContext.tMatrix.tZ.vX * ptRigidDynCubeObj->tModelObj.tOrientation.tX.vY
                      + TransContext_tActiveTransContext.tMatrix.tZ.vZ * ptRigidDynCubeObj->tModelObj.tOrientation.tZ.vY
                      + TransContext_tActiveTransContext.tMatrix.tZ.vY * ptRigidDynCubeObj->tModelObj.tOrientation.tY.vY;
    igi2_frame.tTempMatrix.tZ.vZ = TransContext_tActiveTransContext.tMatrix.tZ.vX * ptRigidDynCubeObj->tModelObj.tOrientation.tX.vZ
                      + TransContext_tActiveTransContext.tMatrix.tZ.vZ * ptRigidDynCubeObj->tModelObj.tOrientation.tZ.vZ
                      + TransContext_tActiveTransContext.tMatrix.tZ.vY * ptRigidDynCubeObj->tModelObj.tOrientation.tY.vZ;
    igi2_frame.tScale.vZ = (ptRigidDynCubeObj->tModelObj.tDynCubeObj.tQObj.tPos.vZ - TransContext_tActiveTransContext.tPos.vZ)
              * TransContext_tActiveTransContext.tMatrix.tZ.vZ
              + (ptRigidDynCubeObj->tModelObj.tDynCubeObj.tQObj.tPos.vY - TransContext_tActiveTransContext.tPos.vY)
              * TransContext_tActiveTransContext.tMatrix.tZ.vY
              + (ptRigidDynCubeObj->tModelObj.tDynCubeObj.tQObj.tPos.vX - TransContext_tActiveTransContext.tPos.vX)
              * TransContext_tActiveTransContext.tMatrix.tZ.vX;
    if ( eDrawMode != MESH3D_DRAWMODE_ENVMAP )
    {
      v29 = 0;
      v12 = SLOWORD(igi2_frame.ptLODVirModela->atBoneVertexRefs[0].atVertexRefs[15].iVertex) <= 0;
      *(float *)&igi2_frame.i = 0.0;
      if ( !v12 )
      {
        do
        {
          v30 = (float *)(v29 + v28->atBoneVertexRefs[0].atVertexRefs[23].iVertex);
          igi2_frame.tAveragePos.vX = *v30;
          v31 = v30[1];
          igi2_frame.tAveragePos.vZ = v30[2];
          nNumItems = SortRender_ptActiveList->nNumItems;
          igi2_frame.tAveragePos.vY = v31;
          v33 = v31 * igi2_frame.tTempMatrix.tZ.vY;
          v34 = &SortRender_ptActiveList->atItem[nNumItems];
          v35 = igi2_frame.tAveragePos.vZ * igi2_frame.tTempMatrix.tZ.vZ + v33;
          SortRender_ptActiveList->nNumItems = nNumItems + 1;
          v36 = SortRender_nBufferPos;
          v37 = igi2_frame.tAveragePos.vX * igi2_frame.tTempMatrix.tZ.vX;
          v34->pfCallback = (void (__cdecl *)(void *))Glow_DrawSorted;
          v34->pxData = &SortRender_anSortBuffer[v36];
          SortRender_nBufferPos = v36 + 28;
          v38 = &SortRender_anSortBuffer[v36];
          v34->vZ = v35 + v37 + igi2_frame.tScale.vZ;
          iVertex = v28->atBoneVertexRefs[0].atVertexRefs[23].iVertex;
          v40 = *(float *)(iVertex + v29 + 4);
          v41 = (float *)(v29 + iVertex);
          igi2_frame.tOldClipMax.vX = v40 * ptRigidDynCubeObj->tModelObj.tOrientation.tX.vY
                         + ptRigidDynCubeObj->tModelObj.tOrientation.tX.vZ * v41[2]
                         + *v41 * ptRigidDynCubeObj->tModelObj.tOrientation.tX.vX;
          igi2_frame.tOldClipMax.vY = v41[1] * ptRigidDynCubeObj->tModelObj.tOrientation.tY.vY
                         + *v41 * ptRigidDynCubeObj->tModelObj.tOrientation.tY.vX
                         + v41[2] * ptRigidDynCubeObj->tModelObj.tOrientation.tY.vZ;
          v42 = v41[1] * ptRigidDynCubeObj->tModelObj.tOrientation.tZ.vY
              + *v41 * ptRigidDynCubeObj->tModelObj.tOrientation.tZ.vX;
          v43 = v41[2] * ptRigidDynCubeObj->tModelObj.tOrientation.tZ.vZ;
          igi2_frame.tPos.vX = igi2_frame.tOldClipMax.vX;
          igi2_frame.tPos.vY = igi2_frame.tOldClipMax.vY;
          igi2_frame.v142 = v42 + v43;
          igi2_frame.tPos.vZ = igi2_frame.v142 * Direct3D_vScale;
          v44 = igi2_frame.tOldClipMax.vY * Direct3D_vScale;
          *(float *)v38 = igi2_frame.tOldClipMax.vX * Direct3D_vScale + igi2_frame.tOldClipMin.vX;
          *((float *)v38 + 1) = v44 + igi2_frame.tOldClipMin.vY;
          *((float *)v38 + 2) = igi2_frame.tPos.vZ + igi2_frame.tOldClipMin.vZ;
          v45 = (_DWORD *)(v29 + v28->atBoneVertexRefs[0].atVertexRefs[23].iVertex + 16);
          *((_DWORD *)v38 + 4) = *v45;
          *((_DWORD *)v38 + 5) = v45[1];
          *((_DWORD *)v38 + 6) = v45[2];
          v28 = igi2_frame.ptLODVirModela;
          *((_DWORD *)v38 + 3) = *(_DWORD *)(v29 + igi2_frame.ptLODVirModela->atBoneVertexRefs[0].atVertexRefs[23].iVertex + 12);
          iVertex_low = SLOWORD(igi2_frame.ptLODVirModela->atBoneVertexRefs[0].atVertexRefs[15].iVertex);
          v29 += 32;
          ++igi2_frame.i;
        }
        while ( igi2_frame.i < iVertex_low );
      }
    }
    v47 = *(_DWORD *)&v28->zFirstVirModelName[12];
    if ( !v47 )
    {
      v48 = *(float *)&v28->isLODDistanceSpecified;
      v49 = *(int *)(LODWORD(v48) + 24);
      v50 = *(_DWORD *)(LODWORD(v48) + 28);
      LODWORD(igi2_frame.tOldClipMin.vX) = v49 + 32 * *(_DWORD *)(LODWORD(v48) + 8);
      igi2_frame.ptLODVirModelb = *(unsigned __int16 *)(v50 + 12);
      v51 = Direct3D_ptTextureStateBlock;
      eCurrentState = Direct3D_ptTextureStateBlock->eCurrentState;
      igi2_frame.i = v49;
      v53 = Direct3DRender_eTextureStateRigid;
      igi2_frame.tOldClipMax.vX = v48;
      if ( eCurrentState != Direct3DRender_eTextureStateRigid )
      {
        Direct3D_ptTextureStateBlock->eCurrentState = Direct3DRender_eTextureStateRigid;
        v51->atRenderState[v53].pfCallback(nullptr);
      }
      v54 = Direct3D_ptGenericStateBlock;
      v55 = Direct3DRender_eGenericStateRigid;
      if ( Direct3D_ptGenericStateBlock->eCurrentState != Direct3DRender_eGenericStateRigid )
      {
        Direct3D_ptGenericStateBlock->eCurrentState = Direct3DRender_eGenericStateRigid;
        v54->atRenderState[v55].pfCallback(nullptr);
      }
      v56 = Direct3D_eClippingStateOff;
      if ( igi2_frame.isTotallyInside == false )
        v56 = Direct3D_eClippingStateOn;
      v57 = Direct3D_ptClippingStateBlock;
      if ( Direct3D_ptClippingStateBlock->eCurrentState != v56 )
      {
        v58 = Direct3D_eClippingStateOff;
        if ( igi2_frame.isTotallyInside == false )
          v58 = Direct3D_eClippingStateOn;
        Direct3D_ptClippingStateBlock->eCurrentState = v58;
        v59 = Direct3D_eClippingStateOff;
        if ( igi2_frame.isTotallyInside == false )
          v59 = Direct3D_eClippingStateOn;
        v57->atRenderState[v59].pfCallback(nullptr);
      }
      Direct3D_tState.aptStreamData[0] = **(struct IDirect3DVertexBuffer8 ***)(*(_DWORD *)(LODWORD(v48) + 28) + 16);
      Direct3D_tState.anStride[0] = 32;
      Direct3D_ptDevice->lpVtbl->SetStreamSource(Direct3D_ptDevice, 0, Direct3D_tState.aptStreamData[0], 32u);
      v60 = **(struct IDirect3DIndexBuffer8 ***)(LODWORD(v48) + 32);
      Direct3D_tState.nBaseVertexIndex = igi2_frame.ptLODVirModelb;
      Direct3D_tState.ptIndexData = v60;
      Direct3D_ptDevice->lpVtbl->SetIndices(Direct3D_ptDevice, v60, igi2_frame.ptLODVirModelb);
      Direct3D_tState.nHandle = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(LODWORD(v48) + 28) + 16) + 24);
      Direct3D_ptDevice->lpVtbl->SetVertexShader(Direct3D_ptDevice, Direct3D_tState.nHandle);
      Direct3DRender_SetFogParametersRigid(ptRigidDynCubeObj, (struct Mesh3D_Mesh_t *)v28);
      if ( *(float *)&igi2_frame.i != 0.0 )
      {
        v61 = SortRender_ptActiveList;
        v62 = (struct RigidDirect3D_FaceGroup_t *)igi2_frame.i;
        igi2_frame.ptLODVirModelc = (float *)(igi2_frame.i + 4);
        do
        {
          if ( (v62->bMaterialProperties & 4) != 0 && ptContext->isSort )
          {
            v63 = *igi2_frame.ptLODVirModelc;
            v64 = igi2_frame.ptLODVirModelc[1];
            igi2_frame.tAveragePos.vZ = igi2_frame.ptLODVirModelc[2];
            v65 = v61->nNumItems;
            igi2_frame.tAveragePos.vY = v64;
            igi2_frame.tAveragePos.vX = v63;
            v66 = igi2_frame.tAveragePos.vZ * igi2_frame.tTempMatrix.tZ.vZ + v64 * igi2_frame.tTempMatrix.tZ.vY;
            v67 = v65;
            v68 = v63 * igi2_frame.tTempMatrix.tZ.vX;
            v69 = 4 * *(_DWORD *)(*(_DWORD *)(igi2_frame.isExclude + 12) + 16);
            v61->nNumItems = v65 + 1;
            v70 = SortRender_nBufferPos;
            v71 = (int)&v61->atItem[v67];
            v72 = v66 + v68 + igi2_frame.tScale.vZ;
            v73 = (struct RigidDirect3D_SortedFaceGroup_t *)&SortRender_anSortBuffer[SortRender_nBufferPos];
            *(_DWORD *)(v71 + 4) = &SortRender_anSortBuffer[SortRender_nBufferPos];
            *(_DWORD *)v71 = Direct3DRender_DrawSortedFaceGroup_Rigid;
            *(float *)(v71 + 8) = v72;
            SortRender_nBufferPos = v70 + v69 + 104;
            igi2_frame.ptSortedFaceGroup = v73;
            if ( v69 )
              v74 = (unsigned int *)&v73[1];
            else
              v74 = nullptr;
            v75 = (struct VirModel_s *)igi2_frame.isExclude;
            igi2_frame.ptSortedFaceGroup->ptAnimTexBuffer = v74;
            Mesh3D_InitAnimTexBuffer(v75, v74);
            v76 = igi2_frame.ptSortedFaceGroup;
            qmemcpy(igi2_frame.ptSortedFaceGroup, &ptRigidDynCubeObj->tModelObj.tDynCubeObj.tQObj.tPos, 0x18u);
            qmemcpy(&v76->tOrientation, &ptRigidDynCubeObj->tModelObj.tOrientation, sizeof(v76->tOrientation));
            v76->tScale = ptRigidDynCubeObj->tModelObj.tScale;
            v77 = igi2_frame.isExclude;
            v76->iLightCategory = ptRigidDynCubeObj->tModelObj.iLightCategory;
            v78 = igi2_frame.tOldClipMax.vX;
            v76->ptVirModel = (struct VirModel_s *)v77;
            v79 = igi2_frame.i;
            *(float *)&v76->ptRenderMesh = v78;
            v76->ptFaceGroup = (struct RigidDirect3D_FaceGroup_t *)v79;
            v76->eLayer = ptRigidDynCubeObj->tModelObj.eLayer;
            v62 = (struct RigidDirect3D_FaceGroup_t *)v79;
          }
          else
          {
            Direct3DRender_DrawRigidFacegroup(v62, (struct VirModel_s *)igi2_frame.isExclude, true, -1);
          }
          v61 = SortRender_ptActiveList;
          igi2_frame.i = (int)++v62;
          igi2_frame.ptLODVirModelc += 8;
        }
        while ( (unsigned int)v62 < LODWORD(igi2_frame.tOldClipMin.vX) );
      }
      goto LABEL_126;
    }
    if ( v47 != 3 )
      goto LABEL_126;
    v80 = (struct RigidDirect3D_SortedFaceGroup_t **)ptRigidDynCubeObj->aptLightmapVirModel[(_DWORD)igi2_frame.ptSortedFaceGroup
                                                                                          + 1];
    if ( !v80 || (igi2_frame.ptSortedFaceGroup = *v80) == nullptr )
    {
      v107 = (struct LODVirModel_s *)v28->isLODDistanceSpecified;
      v108 = *(unsigned int *)&v107->zFirstVirModelName[12];
      v109 = 28 * (int)v107->aptVirModel[3];
      igi2_frame.ptLODVirModele = v107;
      LODWORD(v110) = *(unsigned __int16 *)(v107->isLODDistanceSpecified + 12);
      v111 = Direct3DRender_eTextureStateRigid;
      LODWORD(igi2_frame.tOldClipMax.vX) = v108 + v109;
      v112 = Direct3D_ptTextureStateBlock;
      igi2_frame.tOldClipMin.vX = v110;
      v103 = Direct3D_ptTextureStateBlock->eCurrentState == Direct3DRender_eTextureStateRigid;
      igi2_frame.i = v108;
      if ( !v103 )
      {
        Direct3D_ptTextureStateBlock->eCurrentState = Direct3DRender_eTextureStateRigid;
        v112->atRenderState[v111].pfCallback(nullptr);
      }
      v113 = Direct3D_ptGenericStateBlock;
      v114 = Direct3DRender_eGenericStateRigid;
      if ( Direct3D_ptGenericStateBlock->eCurrentState != Direct3DRender_eGenericStateRigid )
      {
        Direct3D_ptGenericStateBlock->eCurrentState = Direct3DRender_eGenericStateRigid;
        v113->atRenderState[v114].pfCallback(nullptr);
      }
      v115 = Direct3D_eClippingStateOff;
      if ( igi2_frame.isTotallyInside == false )
        v115 = Direct3D_eClippingStateOn;
      v116 = Direct3D_ptClippingStateBlock;
      if ( Direct3D_ptClippingStateBlock->eCurrentState != v115 )
      {
        v117 = Direct3D_eClippingStateOff;
        if ( igi2_frame.isTotallyInside == false )
          v117 = Direct3D_eClippingStateOn;
        Direct3D_ptClippingStateBlock->eCurrentState = v117;
        v118 = Direct3D_eClippingStateOff;
        if ( igi2_frame.isTotallyInside == false )
          v118 = Direct3D_eClippingStateOn;
        v116->atRenderState[v118].pfCallback(nullptr);
      }
      Direct3D_SetStreamSource(
        0,
        **(struct IDirect3DVertexBuffer8 ***)(igi2_frame.ptLODVirModele->isLODDistanceSpecified + 16),
        0x1Cu);
      Direct3D_SetIndices(
        *(struct IDirect3DIndexBuffer8 **)LODWORD(igi2_frame.ptLODVirModele->avLODDistance[0]),
        LODWORD(igi2_frame.tOldClipMin.vX));
      Direct3D_tState.nHandle = *(_DWORD *)(*(_DWORD *)(igi2_frame.ptLODVirModele->isLODDistanceSpecified + 16) + 24);
      Direct3D_ptDevice->lpVtbl->SetVertexShader(Direct3D_ptDevice, Direct3D_tState.nHandle);
      Direct3DRender_SetFogParametersRigid(ptRigidDynCubeObj, (struct Mesh3D_Mesh_t *)v28);
      if ( *(float *)&v108 != 0.0 )
      {
        do
        {
          if ( (*(_BYTE *)v108 & 4) != 0 && ptContext->isSort )
          {
            v119 = *(float *)(igi2_frame.i + 4);
            v120 = *(float *)(igi2_frame.i + 8);
            igi2_frame.tPos.vZ = *(float *)(igi2_frame.i + 12);
            igi2_frame.tPos.vY = v120;
            igi2_frame.tPos.vX = v119;
            igi2_frame.vZa = igi2_frame.tPos.vZ * igi2_frame.tTempMatrix.tZ.vZ + v120 * igi2_frame.tTempMatrix.tZ.vY + v119 * igi2_frame.tTempMatrix.tZ.vX + igi2_frame.tScale.vZ;
            v121 = (struct real64x3_t *)SortRender_AllocItem(
                                          (void (__cdecl *)(void *))Direct3DRender_DrawSortedFaceGroup_Lightmap,
                                          104,
                                          igi2_frame.vZa);
            qmemcpy(v121, &ptRigidDynCubeObj->tModelObj.tDynCubeObj.tQObj.tPos, sizeof(struct real64x3_t));
            qmemcpy(&v121[1], &ptRigidDynCubeObj->tModelObj.tOrientation, 0x28u);
            *(float *)&v121[2].vZ = ptRigidDynCubeObj->tModelObj.tScale.vX;
            HIDWORD(v121[2].vZ) = LODWORD(ptRigidDynCubeObj->tModelObj.tScale.vY);
            *(float *)&v121[3].vX = ptRigidDynCubeObj->tModelObj.tScale.vZ;
            v122 = igi2_frame.isExclude;
            HIDWORD(v121[3].vX) = ptRigidDynCubeObj->tModelObj.iLightCategory;
            LODWORD(v121[3].vY) = v122;
            v123 = igi2_frame.i;
            HIDWORD(v121[3].vY) = igi2_frame.ptLODVirModele;
            LODWORD(v121[3].vZ) = v123;
            HIDWORD(v121[3].vZ) = ptRigidDynCubeObj->tModelObj.eLayer;
            LODWORD(v121[4].vX) = 0;
            v108 = v123;
          }
          else
          {
            v124 = *(_WORD *)(v108 + 24);
            if ( v124 == 0xFFFF )
            {
              Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLOROP, 3u);
              if ( Direct3D_tState.aptTexture[0] )
              {
                Direct3D_tState.aptTexture[0] = nullptr;
                Direct3D_ptDevice->lpVtbl->SetTexture(Direct3D_ptDevice, 0, nullptr);
              }
              Direct3D_ptDevice->lpVtbl->DrawIndexedPrimitive(
                Direct3D_ptDevice,
                D3DPT_TRIANGLELIST,
                *(unsigned __int16 *)(v108 + 20),
                *(unsigned __int16 *)(v108 + 22),
                *(unsigned __int16 *)(v108 + 16),
                *(unsigned __int16 *)(v108 + 18));
              Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLOROP, 4u);
            }
            else
            {
              v125 = *(struct IDirect3DBaseTexture8 **)(*(_DWORD *)(*(_DWORD *)(igi2_frame.isExclude + 16) + 4 * v124) + 36);
              if ( v125 != Direct3D_tState.aptTexture[0] )
              {
                Direct3D_tState.aptTexture[0] = v125;
                Direct3D_ptDevice->lpVtbl->SetTexture(Direct3D_ptDevice, 0, v125);
              }
              if ( (*(_BYTE *)v108 & 0x40) != 0 )
              {
                v126 = Direct3DRender_eBlendStateAlphaTest;
              }
              else
              {
                v126 = Direct3DRender_eBlendStateTransparent;
                if ( (*(_BYTE *)v108 & 4) == 0 )
                  v126 = Direct3DRender_eBlendStateOpaque;
              }
              v127 = Direct3D_ptBlendStateBlock;
              if ( Direct3D_ptBlendStateBlock->eCurrentState != v126 )
              {
                Direct3D_ptBlendStateBlock->eCurrentState = v126;
                v127->atRenderState[v126].pfCallback(nullptr);
              }
              Direct3D_ptDevice->lpVtbl->DrawIndexedPrimitive(
                Direct3D_ptDevice,
                D3DPT_TRIANGLELIST,
                *(unsigned __int16 *)(v108 + 20),
                *(unsigned __int16 *)(v108 + 22),
                *(unsigned __int16 *)(v108 + 16),
                *(unsigned __int16 *)(v108 + 18));
            }
          }
          v108 += 28;
          igi2_frame.i = v108;
        }
        while ( v108 < LODWORD(igi2_frame.tOldClipMax.vX) );
      }
      goto LABEL_126;
    }
    v81 = (_DWORD *)v28->isLODDistanceSpecified;
    v82 = (float *)v81[8];
    v83 = 7 * v81[3];
    igi2_frame.i = (int)v81;
    LODWORD(v84) = *(unsigned __int16 *)(v81[9] + 12);
    v85 = Direct3DRender_eTextureStateLightmap;
    LODWORD(igi2_frame.tOldClipMax.vX) = &v82[v83];
    v86 = Direct3D_ptTextureStateBlock;
    igi2_frame.tOldClipMin.vX = v84;
    igi2_frame.ptLODVirModeld = v82;
    if ( Direct3D_ptTextureStateBlock->eCurrentState != Direct3DRender_eTextureStateLightmap )
    {
      Direct3D_ptTextureStateBlock->eCurrentState = Direct3DRender_eTextureStateLightmap;
      v86->atRenderState[v85].pfCallback(nullptr);
    }
    v87 = Direct3D_ptGenericStateBlock;
    v88 = Direct3DRender_eGenericStateLightmap;
    if ( Direct3D_ptGenericStateBlock->eCurrentState != Direct3DRender_eGenericStateLightmap )
    {
      Direct3D_ptGenericStateBlock->eCurrentState = Direct3DRender_eGenericStateLightmap;
      v87->atRenderState[v88].pfCallback(nullptr);
    }
    v89 = Direct3D_eClippingStateOff;
    if ( igi2_frame.isTotallyInside == false )
      v89 = Direct3D_eClippingStateOn;
    v90 = Direct3D_ptClippingStateBlock;
    if ( Direct3D_ptClippingStateBlock->eCurrentState != v89 )
    {
      v91 = Direct3D_eClippingStateOff;
      if ( igi2_frame.isTotallyInside == false )
        v91 = Direct3D_eClippingStateOn;
      Direct3D_ptClippingStateBlock->eCurrentState = v91;
      v92 = Direct3D_eClippingStateOff;
      if ( igi2_frame.isTotallyInside == false )
        v92 = Direct3D_eClippingStateOn;
      v90->atRenderState[v92].pfCallback(nullptr);
    }
    Direct3D_SetStreamSource(0, **(struct IDirect3DVertexBuffer8 ***)(*(_DWORD *)(igi2_frame.i + 36) + 16), 0x1Cu);
    Direct3D_SetIndices(**(struct IDirect3DIndexBuffer8 ***)(igi2_frame.i + 40), LODWORD(igi2_frame.tOldClipMin.vX));
    Direct3D_SetVertexShader(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(igi2_frame.i + 36) + 16) + 24));
    Direct3DRender_SetFogParametersRigid(ptRigidDynCubeObj, (struct Mesh3D_Mesh_t *)v28);
    if ( !v82 )
    {
LABEL_126:
      if ( ptRigidDynCubeObj->tModelObj.eLayer == TRANSCONTEXT_LAYER_FRONT )
      {
        TransContext_SetActiveTransContext(&igi2_frame.tOldTransContext);
        Direct3DRender_SetTextureStageFilteringMode(0);
        Direct3DRender_SetTextureStageFilteringMode(1u);
      }
      Mesh3D_RestoreAnimTextures((struct VirModel_s *)igi2_frame.isExclude);
      return;
    }
    while ( 1 )
    {
      v93 = *((_WORD *)v82 + 12);
      if ( v93 != 0xFFFF )
      {
        if ( (*(_BYTE *)v82 & 4) == 0 || ptContext->isSort == false )
        {
          v100 = &igi2_frame.ptSortedFaceGroup->tOrientation.nOps + 13 * *((unsigned __int16 *)v82 + 13);
          Direct3D_SetTexture(
            0,
            *(struct IDirect3DBaseTexture8 **)(*(_DWORD *)(*(_DWORD *)(igi2_frame.isExclude + 16) + 4 * v93) + 36));
          Direct3D_SetTexture(1u, (struct IDirect3DBaseTexture8 *)v100[9]);
          v101 = *(_BYTE *)v82;
          if ( (*(_BYTE *)v82 & 0x40) != 0 )
          {
            v102 = Direct3DRender_eBlendStateAlphaTest;
            goto LABEL_90;
          }
          if ( (v101 & 4) != 0 )
          {
            v103 = (v101 & 1) == 0;
            v104 = Direct3D_ptBlendStateBlock;
            v105 = Direct3D_ptBlendStateBlock->eCurrentState;
            if ( !v103 )
            {
              v106 = Direct3DRender_eBlendStateAdditive;
              if ( v105 != Direct3DRender_eBlendStateAdditive )
              {
                Direct3D_ptBlendStateBlock->eCurrentState = Direct3DRender_eBlendStateAdditive;
                v104->atRenderState[v106].pfCallback(nullptr);
              }
              Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_LIGHTING, 0);
              Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLOROP, 2u);
              Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGENABLE, 0);
              goto LABEL_93;
            }
            v102 = Direct3DRender_eBlendStateTransparent;
          }
          else
          {
            v102 = Direct3DRender_eBlendStateOpaque;
LABEL_90:
            v104 = Direct3D_ptBlendStateBlock;
            v105 = Direct3D_ptBlendStateBlock->eCurrentState;
          }
          if ( v105 != v102 )
          {
            v104->eCurrentState = v102;
            v104->atRenderState[v102].pfCallback(nullptr);
          }
LABEL_93:
          Direct3D_DrawIndexedPrimitive(
            D3DPT_TRIANGLELIST,
            *((unsigned __int16 *)v82 + 10),
            *((unsigned __int16 *)v82 + 11),
            *((unsigned __int16 *)v82 + 8),
            *((unsigned __int16 *)v82 + 9));
          goto LABEL_94;
        }
        v94 = igi2_frame.ptLODVirModeld[1];
        v95 = igi2_frame.ptLODVirModeld[2];
        igi2_frame.tPos.vZ = igi2_frame.ptLODVirModeld[3];
        igi2_frame.tPos.vY = v95;
        igi2_frame.tPos.vX = v94;
        igi2_frame.vZ = igi2_frame.tPos.vZ * igi2_frame.tTempMatrix.tZ.vZ + v95 * igi2_frame.tTempMatrix.tZ.vY + v94 * igi2_frame.tTempMatrix.tZ.vX + igi2_frame.tScale.vZ;
        v96 = (struct real64x3_t *)SortRender_AllocItem(
                                     (void (__cdecl *)(void *))Direct3DRender_DrawSortedFaceGroup_Lightmap,
                                     104,
                                     igi2_frame.vZ);
        qmemcpy(v96, &ptRigidDynCubeObj->tModelObj.tDynCubeObj.tQObj.tPos, sizeof(struct real64x3_t));
        qmemcpy(&v96[1], &ptRigidDynCubeObj->tModelObj.tOrientation, 0x28u);
        v82 = igi2_frame.ptLODVirModeld;
        *(float *)&v96[2].vZ = ptRigidDynCubeObj->tModelObj.tScale.vX;
        HIDWORD(v96[2].vZ) = LODWORD(ptRigidDynCubeObj->tModelObj.tScale.vY);
        *(float *)&v96[3].vX = ptRigidDynCubeObj->tModelObj.tScale.vZ;
        iLightCategory = ptRigidDynCubeObj->tModelObj.iLightCategory;
        LODWORD(v96[3].vY) = igi2_frame.isExclude;
        HIDWORD(v96[3].vX) = iLightCategory;
        v98 = igi2_frame.i;
        LODWORD(v96[3].vZ) = igi2_frame.ptLODVirModeld;
        v99 = igi2_frame.ptSortedFaceGroup;
        HIDWORD(v96[3].vY) = v98;
        HIDWORD(v96[3].vZ) = ptRigidDynCubeObj->tModelObj.eLayer;
        LODWORD(v96[4].vX) = v99;
      }
LABEL_94:
      v82 += 7;
      igi2_frame.ptLODVirModeld = v82;
      if ( (unsigned int)v82 >= LODWORD(igi2_frame.tOldClipMax.vX) )
        goto LABEL_126;
    }
  }
}

// source: e/3/pc/pc_direct3drender.c:6348  [size~]
void __cdecl Direct3DRender_DrawBoneMesh(struct DrawBoneMeshContext_t *ptContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { int ptBoneObj; };
    struct { char igi2_o1[4]; struct RigidDirect3D_FaceGroup_t *ptFaceGroup; };
    struct { char igi2_o2[4]; float ptFaceGroupa; };
    struct { char igi2_o3[8]; struct LODVirModel_s *ptSource; };
    struct { char igi2_o4[8]; struct Direct3DRender_BoneMesh_t *ptSourcea; };
    struct { char igi2_o5[8]; float *ptSourceb; };
    struct { char igi2_o6[12]; struct VirModel_s *ptVirModel; };
    struct { char igi2_o7[12]; float ptVirModela; };
    struct { char igi2_o8[16]; struct real32x3_t ptPos; };
    struct { char igi2_o9[28]; float v64; };
    struct { char igi2_o10[32]; struct BoneDynCubeObj_s ptBoneDynCubeObj; };
    struct { char igi2_o11[432]; struct TransContext_s ptTransContext; };
    char igi2_extent[600];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct BoneDynCubeObj_s *v1; // ebp
  struct LODVirModel_s *ptLODVirModel; // ebx
  int BoneMeshLOD; // edx
  int nLOD; // eax
  int v5; // eax
  int v6; // ecx
  int v7; // ecx
  enum TransContext_Layer_e eLayer; // eax
  double v9; // st7
  double v10; // st7
  struct VirModel_s *v11; // eax
  double v12; // st6
  struct Mesh3D_Mesh_t *ptMesh; // ebx
  double v14; // st4
  struct Direct3DRender_BoneMesh_t *pxRenderMesh; // edx
  int nNumFaceGroups; // ecx
  struct RigidDirect3D_FaceGroup_t *v17; // esi
  int v18; // eax
  struct Direct3DRender_BoneMesh_t *v19; // eax
  int v20; // ecx
  struct RenderStateBlock_t *v21; // eax
  int v22; // esi
  int v23; // eax
  int v24; // ecx
  struct RenderStateBlock_t *v25; // edx
  int v26; // ecx
  int v27; // edi
  int v28; // edx
  int v29; // eax
  struct RenderStateBlock_t *v30; // ecx
  int v31; // eax
  int v32; // eax
  unsigned int nFVF; // eax
  struct RenderStateBlock_t *v34; // eax
  int v35; // ecx
  double v36; // st4
  double v37; // st7
  struct RigidDirect3D_FaceGroup_t *v38; // esi
  struct RenderStateBlock_t *v39; // eax
  int v40; // ecx
  float v41; // edx
  float v42; // eax
  struct SortRenderList_t *v43; // esi
  double v44; // st7
  int nNumItems; // ecx
  double v46; // st6
  int v47; // eax
  int v48; // ecx
  double v49; // st7
  unsigned __int8 *v50; // esi
  int v51; // edx
  unsigned int *v52; // edi
  float v53; // eax
  bool v54; // cf

  v1 = ptContext->ptBoneDynCubeObj;
  ptLODVirModel = ptContext->ptBoneDynCubeObj->tModelObj.ptLODVirModel;
  igi2_frame.ptSource = ptLODVirModel;
  if ( !ptLODVirModel )
  {
    Direct3DRender_DrawRigidMesh((struct DrawRigidMeshContext_t *)ptContext);
    return;
  }
  if ( ptContext->isExcludeTestPassed || v1->tModelObj.eLayer == TRANSCONTEXT_LAYER_FRONT )
  {
    igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.ptNext = nullptr;
  }
  else if ( BoneDynCubeObj_Exclude(v1, (enum bool *)&igi2_frame.ptBoneDynCubeObj) )
  {
    return;
  }
  BoneMeshLOD = Mesh3D_GetBoneMeshLOD(v1);
  igi2_frame.ptBoneObj = BoneMeshLOD;
  if ( ModelObj_vLODBias != 0.0 && !CutScene_isRunning )
  {
    nLOD = ptLODVirModel->nLOD;
    if ( ModelObj_vLODBias >= 0.5 )
    {
      v5 = nLOD - 1;
      v7 = 2;
      if ( v5 <= 2 )
        v7 = v5;
      if ( BoneMeshLOD <= v7 )
      {
        igi2_frame.ptBoneObj = 2;
        if ( v5 <= 2 )
LABEL_20:
          igi2_frame.ptBoneObj = v5;
      }
    }
    else
    {
      v5 = nLOD - 1;
      v6 = 1;
      if ( v5 <= 1 )
        v6 = v5;
      if ( BoneMeshLOD <= v6 )
      {
        if ( v5 > 1 )
        {
          igi2_frame.ptBoneObj = 1;
          goto LABEL_21;
        }
        goto LABEL_20;
      }
    }
  }
LABEL_21:
  eLayer = v1->tModelObj.eLayer;
  if ( eLayer )
  {
    if ( igi2_frame.ptBoneObj == -1 )
      return;
  }
  else
  {
    igi2_frame.ptBoneObj = 0;
  }
  if ( eLayer == TRANSCONTEXT_LAYER_FRONT )
  {
    qmemcpy(&igi2_frame.ptTransContext, &TransContext_tActiveTransContext, sizeof(igi2_frame.ptTransContext));
    v9 = (double)Display_tActiveMode.nHeight * 4.0 / ((double)Display_tActiveMode.nWidth * 3.0);
    qmemcpy(&igi2_frame.ptBoneDynCubeObj.tModelObj.tAttachContext.ptBonePos, &igi2_frame.ptTransContext, 0xA8u);
    igi2_frame.ptBoneDynCubeObj.tRootTranslation.vX = Mesh3D_avOverrideFOV[0];
    igi2_frame.ptBoneDynCubeObj.avMorphWeights[1] = 0.0;
    igi2_frame.ptBoneDynCubeObj.tRootTranslation.vY = Mesh3D_avOverrideFOV[0]
                                         * RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHeight
                                         / (v9
                                          * RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vWidth);
    igi2_frame.ptBoneDynCubeObj.tRootTranslation.vZ = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHalfWidth
                                         / Mesh3D_avOverrideFOV[0];
    *(float *)&igi2_frame.ptBoneDynCubeObj.pcHierarchy = v9 * igi2_frame.ptBoneDynCubeObj.tRootTranslation.vZ;
    TransContext_SetActiveTransContext((struct TransContext_s *)&igi2_frame.ptBoneDynCubeObj.tModelObj.tAttachContext.ptBonePos);
  }
  v10 = v1->tModelObj.tDynCubeObj.tQObj.tPos.vX - TransContext_tActiveTransContext.tPos.vX;
  v11 = ptLODVirModel->aptVirModel[igi2_frame.ptBoneObj];
  igi2_frame.ptPos.vX = v10;
  igi2_frame.ptVirModel = v11;
  v12 = v1->tModelObj.tDynCubeObj.tQObj.tPos.vY - TransContext_tActiveTransContext.tPos.vY;
  ptMesh = v11->ptModel->ptMesh;
  v14 = v1->tModelObj.tDynCubeObj.tQObj.tPos.vZ - TransContext_tActiveTransContext.tPos.vZ;
  qmemcpy(&igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.ptPrev, &v1->tModelObj.tOrientation, 0x28u);
  igi2_frame.v64 = v14;
  igi2_frame.ptPos.vX = Direct3D_vScale * igi2_frame.ptPos.vX;
  igi2_frame.ptPos.vY = Direct3D_vScale * v12;
  igi2_frame.ptPos.vZ = Direct3D_vScale * v14;
  *(float *)&igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.ptPrev = Direct3D_vScale
                                                                        * *(float *)&igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.ptPrev;
  *(float *)&igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.tQTaskChildren.ptHead = Direct3D_vScale
                                                                                       * *(float *)&igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.tQTaskChildren.ptHead;
  *(float *)&igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.tQTaskChildren.ptMiddle = *(float *)&igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.tQTaskChildren.ptMiddle
                                                                                         * Direct3D_vScale;
  *(float *)&igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.tQTaskChildren.ptTail = *(float *)&igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.tQTaskChildren.ptTail
                                                                                       * Direct3D_vScale;
  *(float *)&igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.tQTaskRefList.ptHead = *(float *)&igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.tQTaskRefList.ptHead
                                                                                      * Direct3D_vScale;
  *(float *)&igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.tQTaskRefList.ptMiddle = *(float *)&igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.tQTaskRefList.ptMiddle
                                                                                        * Direct3D_vScale;
  *(float *)&igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.tQTaskRefList.ptTail = *(float *)&igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.tQTaskRefList.ptTail
                                                                                      * Direct3D_vScale;
  *(float *)&igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.ptParent = *(float *)&igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.ptParent
                                                                          * Direct3D_vScale;
  *(float *)&igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.eQTaskType = *(float *)&igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.eQTaskType
                                                                            * Direct3D_vScale;
  *((float *)&igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.pxQData + 1) = TransContext_tActiveTransContext.tMatrix.tZ.vZ
                                                                        * v1->tModelObj.tOrientation.tZ.vX
                                                                        + TransContext_tActiveTransContext.tMatrix.tZ.vY
                                                                        * v1->tModelObj.tOrientation.tY.vX
                                                                        + TransContext_tActiveTransContext.tMatrix.tZ.vX
                                                                        * v1->tModelObj.tOrientation.tX.vX;
  *(float *)&igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.ptDynCubeObjTreeItem = TransContext_tActiveTransContext.tMatrix.tZ.vZ
                                                                         * v1->tModelObj.tOrientation.tZ.vY
                                                                         + TransContext_tActiveTransContext.tMatrix.tZ.vY
                                                                         * v1->tModelObj.tOrientation.tY.vY
                                                                         + TransContext_tActiveTransContext.tMatrix.tZ.vX
                                                                         * v1->tModelObj.tOrientation.tX.vY;
  *(float *)&igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.ptPrev = TransContext_tActiveTransContext.tMatrix.tZ.vZ
                                                           * v1->tModelObj.tOrientation.tZ.vZ
                                                           + TransContext_tActiveTransContext.tMatrix.tZ.vY
                                                           * v1->tModelObj.tOrientation.tY.vZ
                                                           + TransContext_tActiveTransContext.tMatrix.tZ.vX
                                                           * v1->tModelObj.tOrientation.tX.vZ;
  *(float *)&igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vY = v10;
  *(float *)&igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vZ = igi2_frame.v64 * TransContext_tActiveTransContext.tMatrix.tZ.vZ
                                                                  + v12 * TransContext_tActiveTransContext.tMatrix.tZ.vY
                                                                  + *(float *)&igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vY
                                                                  * TransContext_tActiveTransContext.tMatrix.tZ.vX;
  Direct3D_D3DMATRIXFromReal32x9(
    (struct _D3DMATRIX *)&igi2_frame.ptBoneDynCubeObj.tModelObj.tRelativeOrientation.tX.vY,
    (struct real32x9_t *)&igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.ptPrev,
    &igi2_frame.ptPos);
  Direct3D_ptDevice->lpVtbl->SetTransform(
    Direct3D_ptDevice,
    (enum _D3DTRANSFORMSTATETYPE)256,
    (struct _D3DMATRIX *)&igi2_frame.ptBoneDynCubeObj.tModelObj.tRelativeOrientation.tX.vY);
  Direct3DRender_SetFogParameters(&v1->tModelObj.tDynCubeObj.tQObj.tPos, ptMesh->tRenderMeshSphere.vRadius);
  if ( ptMesh->eRenderMeshType == MESH3D_RENDERMESHTYPE_DIRECT3D_BONE )
  {
    pxRenderMesh = (struct Direct3DRender_BoneMesh_t *)ptMesh->pxRenderMesh;
    nNumFaceGroups = pxRenderMesh->nNumFaceGroups;
    v17 = pxRenderMesh->ptFaceGroup;
    igi2_frame.v64 = *(float *)&pxRenderMesh;
    igi2_frame.ptFaceGroup = v17;
    HIDWORD(igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vX) = &v17[nNumFaceGroups];
    if ( !nNumFaceGroups )
      return;
    if ( igi2_frame.ptBoneObj > 0 && CPU_tCaps.isSSE )
    {
      v18 = Direct3DRender_ProcessVerticesBone_SSE(pxRenderMesh, igi2_frame.ptSource, v1, igi2_frame.ptBoneObj);
    }
    else
    {
      v19 = Direct3DRender_MorphVerticesBone(pxRenderMesh, ptMesh->ptMorph, v1);
      v18 = Direct3DRender_ProcessVerticesBone(v19, igi2_frame.ptSource, v1, igi2_frame.ptBoneObj);
    }
    v20 = Direct3DRender_eBlendStateOpaque;
    igi2_frame.ptSourcea = (struct Direct3DRender_BoneMesh_t *)v18;
    v21 = Direct3D_ptBlendStateBlock;
    if ( Direct3D_ptBlendStateBlock->eCurrentState != Direct3DRender_eBlendStateOpaque )
    {
      Direct3D_ptBlendStateBlock->eCurrentState = Direct3DRender_eBlendStateOpaque;
      v21->atRenderState[v20].pfCallback(nullptr);
    }
    v22 = Direct3D_eClippingStateOff;
    v23 = Direct3D_eClippingStateOn;
    v24 = Direct3D_eClippingStateOff;
    if ( !igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.ptNext )
      v24 = Direct3D_eClippingStateOn;
    v25 = Direct3D_ptClippingStateBlock;
    if ( Direct3D_ptClippingStateBlock->eCurrentState != v24 )
    {
      v26 = Direct3D_eClippingStateOff;
      if ( !igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.ptNext )
        v26 = Direct3D_eClippingStateOn;
      Direct3D_ptClippingStateBlock->eCurrentState = v26;
      if ( igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.ptNext )
        v23 = v22;
      v25->atRenderState[v23].pfCallback(nullptr);
    }
    v27 = Direct3DRender_eGenericStateRigid;
    v28 = Direct3DRender_eGenericStateBone;
    v29 = Direct3DRender_eGenericStateRigid;
    if ( !igi2_frame.ptBoneObj )
      v29 = Direct3DRender_eGenericStateBone;
    v30 = Direct3D_ptGenericStateBlock;
    if ( Direct3D_ptGenericStateBlock->eCurrentState != v29 )
    {
      v31 = Direct3DRender_eGenericStateRigid;
      if ( !igi2_frame.ptBoneObj )
        v31 = Direct3DRender_eGenericStateBone;
      Direct3D_ptGenericStateBlock->eCurrentState = v31;
      v32 = v27;
      if ( !igi2_frame.ptBoneObj )
        v32 = v28;
      v30->atRenderState[v32].pfCallback(nullptr);
    }
    memset(&igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.iSector, 0, 0x44u);
    igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.iSector = 1065353216;
    igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.ptSector = (void *)1065353216;
    igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.iRenderGroup = 1065353216;
    igi2_frame.ptBoneDynCubeObj.tModelObj.ptLODVirModel = (struct LODVirModel_s *)1065353216;
    igi2_frame.ptBoneDynCubeObj.tModelObj.ptMagicObjContainer = (struct QTask_s *)1065353216;
    igi2_frame.ptBoneDynCubeObj.tModelObj.tOrientation.tX.vX = 1.0;
    Direct3D_ptDevice->lpVtbl->SetMaterial(
      Direct3D_ptDevice,
      (struct _D3DMATERIAL8 *)&igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.iSector);
    if ( igi2_frame.ptBoneObj )
    {
      Direct3D_SetStreamSource(
        0,
        Direct3D_atDynamicVertexBuffer[0].ptVertexBuffer,
        Direct3D_atDynamicVertexBuffer[0].nStride);
      nFVF = Direct3D_atDynamicVertexBuffer[0].nFVF;
    }
    else
    {
      Direct3D_SetStreamSource(
        0,
        Direct3D_atDynamicVertexBuffer[4].ptVertexBuffer,
        Direct3D_atDynamicVertexBuffer[4].nStride);
      nFVF = Direct3D_atDynamicVertexBuffer[4].nFVF;
    }
    Direct3D_SetVertexShader(nFVF);
    Direct3D_SetIndices(**(struct IDirect3DIndexBuffer8 ***)(LODWORD(igi2_frame.v64) + 36), (unsigned int)igi2_frame.ptSourcea);
    if ( isDrawInfra && tInfraHumanTexture.isTextureLoaded )
    {
      igi2_frame.ptFaceGroupa = Direct3D_vScale * 40960.0;
      igi2_frame.ptVirModela = Direct3D_vScale * 819.2000122070312;
      Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGENABLE, 0);
      Direct3D_SetTexture(0, tInfraHumanTexture.tTexInfo.ptDirect3DBaseTexture);
      v34 = Direct3D_ptTextureStateBlock;
      v35 = Direct3DRender_eInfraredFilter;
      if ( Direct3D_ptTextureStateBlock->eCurrentState != Direct3DRender_eInfraredFilter )
      {
        Direct3D_ptTextureStateBlock->eCurrentState = Direct3DRender_eInfraredFilter;
        v34->atRenderState[v35].pfCallback(nullptr);
      }
      Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_TEXTUREFACTOR, -2130706433u);
      Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_NORMALIZENORMALS, 1u);
      Direct3D_DrawIndexedPrimitive(
        D3DPT_TRIANGLELIST,
        0,
        ptMesh->tRenderMeshStats.nNumVertices,
        0,
        ptMesh->tRenderMeshStats.nNumFaces);
      v36 = sqrt(igi2_frame.ptPos.vX * igi2_frame.ptPos.vX + igi2_frame.ptPos.vY * igi2_frame.ptPos.vY + igi2_frame.ptPos.vZ * igi2_frame.ptPos.vZ);
      if ( v36 >= igi2_frame.ptVirModela )
      {
        if ( v36 < igi2_frame.ptVirModela + igi2_frame.ptFaceGroupa )
          igi2_frame.ptFaceGroupa = v36 - igi2_frame.ptVirModela;
        v37 = (v36 - igi2_frame.ptFaceGroupa) / v36;
      }
      else
      {
        v37 = 1.0;
      }
      igi2_frame.ptPos.vX = igi2_frame.ptPos.vX * v37;
      igi2_frame.ptPos.vY = igi2_frame.ptPos.vY * v37;
      igi2_frame.ptPos.vZ = igi2_frame.ptPos.vZ * v37;
      *(float *)&igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.ptPrev = *(float *)&igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.ptPrev
                                                                            * v37;
      *(float *)&igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.tQTaskChildren.ptHead = *(float *)&igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.tQTaskChildren.ptHead
                                                                                           * v37;
      *(float *)&igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.tQTaskChildren.ptMiddle = *(float *)&igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.tQTaskChildren.ptMiddle
                                                                                             * v37;
      *(float *)&igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.tQTaskChildren.ptTail = *(float *)&igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.tQTaskChildren.ptTail
                                                                                           * v37;
      *(float *)&igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.tQTaskRefList.ptHead = *(float *)&igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.tQTaskRefList.ptHead
                                                                                          * v37;
      *(float *)&igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.tQTaskRefList.ptMiddle = *(float *)&igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.tQTaskRefList.ptMiddle
                                                                                            * v37;
      *(float *)&igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.tQTaskRefList.ptTail = *(float *)&igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.tQTaskRefList.ptTail
                                                                                          * v37;
      *(float *)&igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.ptParent = *(float *)&igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.ptParent
                                                                              * v37;
      *(float *)&igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.eQTaskType = v37
                                                                                * *(float *)&igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.eQTaskType;
      Direct3D_D3DMATRIXFromReal32x9(
        (struct _D3DMATRIX *)&igi2_frame.ptBoneDynCubeObj.tModelObj.tRelativeOrientation.tX.vY,
        (struct real32x9_t *)&igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.ptPrev,
        &igi2_frame.ptPos);
      Direct3D_ptDevice->lpVtbl->SetTransform(
        Direct3D_ptDevice,
        (enum _D3DTRANSFORMSTATETYPE)256,
        (struct _D3DMATRIX *)&igi2_frame.ptBoneDynCubeObj.tModelObj.tRelativeOrientation.tX.vY);
      Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_TEXTUREFACTOR, -2130706433u);
      Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHABLENDENABLE, 1u);
      Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SRCBLEND, 5u);
      Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_DESTBLEND, 6u);
      Direct3D_DrawIndexedPrimitive(
        D3DPT_TRIANGLELIST,
        0,
        ptMesh->tRenderMeshStats.nNumVertices,
        0,
        ptMesh->tRenderMeshStats.nNumFaces);
      Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHABLENDENABLE, 0);
      Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_NORMALIZENORMALS, 0);
      Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGENABLE, QVertex_isFog);
    }
    else
    {
      v38 = igi2_frame.ptFaceGroup;
      igi2_frame.ptSourceb = &igi2_frame.ptFaceGroup->tAveragePos.vX;
      while ( 1 )
      {
        if ( (v38->bMaterialProperties & 4) != 0 )
        {
          v41 = *igi2_frame.ptSourceb;
          v42 = igi2_frame.ptSourceb[1];
          v43 = SortRender_ptActiveList;
          igi2_frame.ptPos.vZ = igi2_frame.ptSourceb[2];
          igi2_frame.ptPos.vY = v42;
          igi2_frame.ptPos.vX = v41;
          v44 = igi2_frame.ptPos.vZ * *(float *)&igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.ptPrev
              + v42 * *(float *)&igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.ptDynCubeObjTreeItem;
          nNumItems = SortRender_ptActiveList->nNumItems;
          v46 = v41 * *((float *)&igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.pxQData + 1);
          v47 = 4 * igi2_frame.ptVirModel->ptModel->nAnimTextures;
          ++SortRender_ptActiveList->nNumItems;
          v48 = (int)&v43->atItem[nNumItems];
          v49 = v44 + v46 + *(float *)&igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vZ;
          v50 = &SortRender_anSortBuffer[SortRender_nBufferPos];
          v51 = SortRender_nBufferPos + v47 + 104;
          *(_DWORD *)(v48 + 4) = &SortRender_anSortBuffer[SortRender_nBufferPos];
          *(float *)(v48 + 8) = v49;
          SortRender_nBufferPos = v51;
          *(_DWORD *)v48 = Direct3DRender_DrawSortedFaceGroup_Bone;
          v52 = v47 ? (unsigned int *)(v50 + 32) : nullptr;
          *((_DWORD *)v50 + 7) = v52;
          Mesh3D_InitAnimTexBuffer(igi2_frame.ptVirModel, v52);
          *((_DWORD *)v50 + 1) = v1->tModelObj.iLightCategory;
          v53 = igi2_frame.v64;
          *(_DWORD *)v50 = igi2_frame.ptBoneObj;
          *((_DWORD *)v50 + 2) = igi2_frame.ptVirModel;
          *((float *)v50 + 3) = v53;
          *((_DWORD *)v50 + 4) = igi2_frame.ptFaceGroup;
          *((_DWORD *)v50 + 6) = v1->tModelObj.eLayer;
          *((_DWORD *)v50 + 5) = v1;
        }
        else
        {
          v39 = Direct3D_ptTextureStateBlock;
          v40 = Direct3DRender_eTextureStateRigid;
          if ( Direct3D_ptTextureStateBlock->eCurrentState != Direct3DRender_eTextureStateRigid )
          {
            Direct3D_ptTextureStateBlock->eCurrentState = Direct3DRender_eTextureStateRigid;
            v39->atRenderState[v40].pfCallback(nullptr);
          }
          Direct3DRender_DrawRigidFacegroup(v38, igi2_frame.ptVirModel, true, 0);
        }
        v54 = (unsigned int)&igi2_frame.ptFaceGroup[1] < HIDWORD(igi2_frame.ptBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vX);
        ++igi2_frame.ptFaceGroup;
        igi2_frame.ptSourceb += 8;
        if ( !v54 )
          break;
        v38 = igi2_frame.ptFaceGroup;
      }
    }
  }
  if ( v1->tModelObj.eLayer == TRANSCONTEXT_LAYER_FRONT )
    TransContext_SetActiveTransContext(&igi2_frame.ptTransContext);
}

_DWORD *__cdecl sub_565430(_DWORD *a1)
{
  int v2; // edx

  v2 = a1[3];
  a1[4] = a1[2];
  a1[5] = v2;
  return a1;
}

_DWORD *__cdecl sub_565450(_DWORD *a1)
{
  int v2; // edx

  v2 = a1[3];
  a1[4] = a1[2];
  a1[5] = v2;
  return a1;
}

int sub_565470()
{
  int result; // eax
  int v1; // edi
  enum _D3DPOOL *p_Pool; // esi

  result = Direct3DRender_nNumVertexBuffers;
  v1 = 0;
  if ( Direct3DRender_nNumVertexBuffers > 0 )
  {
    p_Pool = &Direct3DRender_atVertexBuffer[0].tVBDesc.Pool;
    do
    {
      Direct3D_ptDevice->lpVtbl->CreateVertexBuffer(
        Direct3D_ptDevice,
        *((_DWORD *)p_Pool + 1),
        *((_DWORD *)p_Pool - 1),
        *((_DWORD *)p_Pool + 2),
        *p_Pool,
        (struct IDirect3DVertexBuffer8 **)(p_Pool - 4));
      result = Direct3DRender_nNumVertexBuffers;
      ++v1;
      p_Pool += 11;
    }
    while ( v1 < Direct3DRender_nNumVertexBuffers );
  }
  return result;
}

int sub_5654B0()
{
  int result; // eax
  int v1; // edi
  struct Direct3DRender_VertexBuffer_t *v2; // esi

  if ( tInfraHumanTexture.isTextureLoaded )
  {
    if ( AppContext_tAppContext.isMainMenu == false )
      RenderMode_atRenderMode[tInfraHumanTexture.tTexInfo.eRenderMode].apfRenderModeMethod[Texture_eDeAllocTextureMethod](&tInfraHumanTexture.tTexInfo);
    memset(&tInfraHumanTexture.tTexInfo, 0, sizeof(tInfraHumanTexture.tTexInfo));
    tInfraHumanTexture.isTextureLoaded = false;
  }
  if ( tGlowTexture.isTextureLoaded )
  {
    if ( AppContext_tAppContext.isMainMenu == false )
      RenderMode_atRenderMode[tGlowTexture.tTexInfo.eRenderMode].apfRenderModeMethod[Texture_eDeAllocTextureMethod](&tGlowTexture.tTexInfo);
    memset(&tGlowTexture.tTexInfo, 0, sizeof(tGlowTexture.tTexInfo));
    tGlowTexture.isTextureLoaded = false;
  }
  result = Direct3DRender_nNumVertexBuffers;
  v1 = 0;
  if ( Direct3DRender_nNumVertexBuffers > 0 )
  {
    v2 = Direct3DRender_atVertexBuffer;
    do
    {
      v2->ptVertexBuffer->lpVtbl->Release(v2->ptVertexBuffer);
      result = Direct3DRender_nNumVertexBuffers;
      v2->ptVertexBuffer = nullptr;
      ++v1;
      ++v2;
    }
    while ( v1 < result );
  }
  return result;
}

// source: e/3/pc/pc_direct3drender.c:6797  [size]
void __cdecl Direct3D_ExcludeObject(void *pxContext)
{
  float *v2; // esi
  double v3; // st7
  double v4; // st6
  BOOL *v5; // edi
  BOOL v6; // eax
  _DWORD *v7; // eax
  char isOutZ; // [esp+Bh] [ebp-19h]
  float vRadius; // [esp+Ch] [ebp-18h]
  float v10; // [esp+10h] [ebp-14h]
  float vDistanceFromViewConeTop; // [esp+14h] [ebp-10h]
  float vDistanceFromViewConeBottom; // [esp+18h] [ebp-Ch]
  float vNear; // [esp+1Ch] [ebp-8h]
  float vFar; // [esp+20h] [ebp-4h]
  float pxContextb = *(float *)&pxContext; // [esp+28h] [ebp+4h] ARGSLOT
  bool pxContexta = *(bool *)&pxContext; // [esp+28h] [ebp+4h] ARGSLOT

  vRadius = *((float *)pxContext + 1);
  v2 = *(float **)pxContext;
  v10 = -vRadius;
  isOutZ = *(float *)(*(_DWORD *)pxContext + 8) < (double)v10;
  vNear = Direct3D_vWorldOverlayMinZ;
  vFar = Direct3D_vWorldMaxZ;
  if ( vRadius + *(float *)(*(_DWORD *)pxContext + 8) < Direct3D_vWorldOverlayMinZ
    || v2[2] - vRadius > Direct3D_vWorldMaxZ )
  {
    v7 = *((_DWORD **)pxContext + 2);
    if ( v7 )
      *v7 = 0;
    *((_DWORD *)pxContext + 3) = 1;
  }
  else
  {
    v3 = (*v2 - Mesh3D_vViewConeFOVLeft * v2[2]) * Mesh3D_vCosViewConeAngleLeft;
    v4 = (*v2 - Mesh3D_vViewConeFOVRight * v2[2]) * Mesh3D_vCosViewConeAngleRight;
    vDistanceFromViewConeTop = (v2[1] - Mesh3D_vViewConeFOVTop * v2[2]) * Mesh3D_vCosViewConeAngleTop;
    vDistanceFromViewConeBottom = (v2[1] - Mesh3D_vViewConeFOVBottom * v2[2]) * Mesh3D_vCosViewConeAngleBottom;
    v5 = *((BOOL **)pxContext + 2);
    if ( v5 )
    {
      pxContextb = v4;
      pxContexta = pxContextb < (double)v10;
      v6 = v3 > vRadius
        && pxContexta
        && vDistanceFromViewConeTop > (double)vRadius
        && vDistanceFromViewConeBottom < (double)v10
        && vRadius + 409.6000061035156 < v2[2];
      *v5 = v6;
      if ( v2[2] - vRadius <= vNear || vRadius + v2[2] >= vFar )
        **((_DWORD **)pxContext + 2) = 0;
      else
        **((_DWORD **)pxContext + 2) &= 1u;
    }
    *((_DWORD *)pxContext + 3) = v3 < v10
                              || v4 > vRadius
                              || vDistanceFromViewConeTop < (double)v10
                              || vDistanceFromViewConeBottom > (double)vRadius
                              || isOutZ;
  }
}

// source: e/3/pc/pc_direct3drender.c:6869  [size]
void __cdecl Direct3DRender_BlitCallback(struct DisplayBlitContext_s *ptDisplayBlitContext)
{
  ;
}

// source: e/3/pc/pc_direct3drender.c:6882  [size]
void __cdecl Direct3DRender_CreateBruise(void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float tUntransformedLocalPos; };
    struct { char igi2_o1[4]; float tUntransformedLocalPos_4; };
    struct { char igi2_o2[8]; float tUntransformedLocalPos_8; };
    struct { char igi2_o3[12]; float Real32x3_RotateInverse_tTemp; };
    struct { char igi2_o4[12]; float Real32x3_RotateInverse_tTempa; };
    struct { char igi2_o5[16]; float Real32x3_RotateInverse_tTemp_4; };
    struct { char igi2_o6[16]; float Real32x3_RotateInverse_tTemp_4a; };
    struct { char igi2_o7[20]; float Real32x3_RotateInverse_tTemp_8; };
    struct { char igi2_o8[20]; float Real32x3_RotateInverse_tTemp_8a; };
    struct { char igi2_o9[24]; struct real32x9_t tInversedBoneMatrix; };
    char igi2_extent[64];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  float *v1; // edi
  struct BoneDynCubeObj_s *v2; // esi
  int v3; // ebx
  int v4; // ebp
  double v5; // st7
  double v6; // st6
  double v7; // st5
  float *v8; // eax
  int v9; // edi
  int v10; // ebx
  _DWORD *v11; // ebp
  int v12; // edx
  double v13; // st7
  int v14; // edx
  _DWORD *pxContexta = *(_DWORD * *)&pxContext; // [esp+54h] [ebp+4h] ARGSLOT

  v1 = *(float **)pxContext;
  v2 = **(struct BoneDynCubeObj_s ***)pxContext;
  v3 = *(_DWORD *)(*(_DWORD *)pxContext + 68);
  BoneDynCubeObj_UpdateHierarchy(v2);
  v4 = (int)&v2->patBone[v3];
  pxContexta = v2->tModelObj.ptLODVirModel->aptVirModel[0]->ptModel->ptMesh->pxRenderMesh;
  Real32x9_InvertSafe(&igi2_frame.tInversedBoneMatrix, (struct real32x9_t *)(v4 + 16));
  igi2_frame.Real32x3_RotateInverse_tTemp = v2->tModelObj.tOrientation.tY.vX * v1[9]
                               + v2->tModelObj.tOrientation.tX.vX * v1[8]
                               + v2->tModelObj.tOrientation.tZ.vX * v1[10];
  igi2_frame.Real32x3_RotateInverse_tTemp_4 = v2->tModelObj.tOrientation.tY.vY * v1[9]
                                 + v2->tModelObj.tOrientation.tX.vY * v1[8]
                                 + v2->tModelObj.tOrientation.tZ.vY * v1[10];
  igi2_frame.Real32x3_RotateInverse_tTemp_8 = v2->tModelObj.tOrientation.tY.vZ * v1[9]
                                 + v2->tModelObj.tOrientation.tX.vZ * v1[8]
                                 + v2->tModelObj.tOrientation.tZ.vZ * v1[10];
  v5 = igi2_frame.Real32x3_RotateInverse_tTemp - *(float *)v4;
  v6 = igi2_frame.Real32x3_RotateInverse_tTemp_4 - *(float *)(v4 + 4);
  v7 = igi2_frame.Real32x3_RotateInverse_tTemp_8 - *(float *)(v4 + 8);
  igi2_frame.Real32x3_RotateInverse_tTempa = igi2_frame.tInversedBoneMatrix.tX.vZ * v7
                                + igi2_frame.tInversedBoneMatrix.tX.vY * v6
                                + igi2_frame.tInversedBoneMatrix.tX.vX * v5;
  igi2_frame.Real32x3_RotateInverse_tTemp_4a = igi2_frame.tInversedBoneMatrix.tY.vZ * v7
                                  + igi2_frame.tInversedBoneMatrix.tY.vY * v6
                                  + igi2_frame.tInversedBoneMatrix.tY.vX * v5;
  igi2_frame.Real32x3_RotateInverse_tTemp_8a = igi2_frame.tInversedBoneMatrix.tZ.vZ * v7
                                  + igi2_frame.tInversedBoneMatrix.tZ.vY * v6
                                  + igi2_frame.tInversedBoneMatrix.tZ.vX * v5;
  v8 = (float *)(*(_DWORD *)(pxContexta[6] + 8) + 12 * v3);
  v9 = 0;
  igi2_frame.tUntransformedLocalPos = igi2_frame.Real32x3_RotateInverse_tTempa + *v8;
  igi2_frame.tUntransformedLocalPos_4 = igi2_frame.Real32x3_RotateInverse_tTemp_4a + v8[1];
  v10 = (int)v2->tModelObj.ptLODVirModel + 4004 * v3;
  igi2_frame.tUntransformedLocalPos_8 = igi2_frame.Real32x3_RotateInverse_tTemp_8a + v8[2];
  if ( *(int *)(v10 + 72) > 0 )
  {
    v11 = (_DWORD *)(v10 + 76);
    do
    {
      v12 = *(_DWORD *)pxContexta[6];
      v13 = *(float *)(v12 + 40 * *v11);
      v14 = v12 + 40 * *v11;
      if ( fabs(v13 - igi2_frame.tUntransformedLocalPos) < 491.5199890136719
        && fabs(*(float *)(v14 + 4) - igi2_frame.tUntransformedLocalPos_4) < 491.5199890136719
        && fabs(*(float *)(v14 + 8) - igi2_frame.tUntransformedLocalPos_8) < 491.5199890136719 )
      {
        v2->abBloodStains[*v11] = (unsigned int)&MTP_atLODVirModel[45].atBoneVertexRefs[4].atVertexRefs[413];
      }
      ++v9;
      ++v11;
    }
    while ( v9 < (int)(*(_DWORD *)(v10 + 72)) );
  }
}

// source: e/3/pc/pc_direct3drender.c:6952  [size]
int __cdecl Direct3DRender_SetFilteringMode(enum Direct3DRender_FilteringType_e eMode)
{
  int result; // eax
  enum bool aisCapable[3]; // [esp+0h] [ebp-Ch] BYREF

  memset(aisCapable, 0, sizeof(aisCapable));
  if ( (Direct3D_tCaps.TextureFilterCaps & 0x2000000) == 0
    || (Direct3D_tCaps.TextureFilterCaps & 0x200) == 0
    || (aisCapable[0] = true, (Direct3D_tCaps.TextureFilterCaps & 0x10000) == 0) )
  {
    aisCapable[0] = false;
  }
  if ( (Direct3D_tCaps.TextureFilterCaps & 0x2000000) == 0
    || (Direct3D_tCaps.TextureFilterCaps & 0x200) == 0
    || (aisCapable[1] = true, (Direct3D_tCaps.TextureFilterCaps & 0x20000) == 0) )
  {
    aisCapable[1] = false;
  }
  if ( Direct3D_tCaps.MaxAnisotropy <= 1
    || (Direct3D_tCaps.RasterCaps & 0x20000) == 0
    || (aisCapable[2] = true, (Direct3D_tCaps.TextureFilterCaps & 0x20000) == 0) )
  {
    aisCapable[2] = false;
  }
  for ( result = 2; result >= 0; --result )
  {
    if ( aisCapable[result] )
      break;
  }
  Direct3DRender_eFilteringType = eMode;
  if ( eMode >= result )
    Direct3DRender_eFilteringType = result;
  return result;
}

// source: e/3/pc/pc_direct3drender.c:7001  [size]
int __cdecl Direct3DRender_GetHighestSupportedFilteringMode()
{
  return Direct3DRender_SetFilteringMode(Direct3DRender_eFilteringType);
}

// source: e/3/pc/pc_direct3drender.c:7014  [size]
int __cdecl Direct3DRender_SetTextureStageFilteringMode(unsigned int a1)
{
  unsigned int v2; // [esp-4h] [ebp-4h]

  if ( Direct3DRender_eFilteringType == DIRECT3DRENDER_FILTERINGTYPE_BILINEAR )
  {
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, a1, D3DTSS_MINFILTER, 2u);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, a1, D3DTSS_MAGFILTER, 2u);
    v2 = 1;
    goto LABEL_8;
  }
  if ( Direct3DRender_eFilteringType == DIRECT3DRENDER_FILTERINGTYPE_TRILINEAR )
  {
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, a1, D3DTSS_MINFILTER, 2u);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, a1, D3DTSS_MAGFILTER, 2u);
    v2 = 2;
LABEL_8:
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, a1, D3DTSS_MIPFILTER, v2);
    return Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, a1, D3DTSS_MAXANISOTROPY, 1u);
  }
  if ( Direct3DRender_eFilteringType != DIRECT3DRENDER_FILTERINGTYPE_ANISOTROPIC )
  {
    LDebug_Error("Direct3DRender: Texture filtering type unknown");
    abort();
  }
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(
    Direct3D_ptDevice,
    a1,
    D3DTSS_MAXANISOTROPY,
    Direct3D_tCaps.MaxAnisotropy);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(
    Direct3D_ptDevice,
    a1,
    D3DTSS_MINFILTER,
    (Direct3D_tCaps.TextureFilterCaps & 0x400 | 0x800u) >> 10);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(
    Direct3D_ptDevice,
    a1,
    D3DTSS_MAGFILTER,
    (Direct3D_tCaps.TextureFilterCaps & 0x4000000 | 0x8000000) >> 26);
  return Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, a1, D3DTSS_MIPFILTER, 2u);
}

enum bool __cdecl sub_565BE0(enum bool result)
{
  isDrawInfra = result;
  return result;
}

// source: e/3/pc/pc_direct3drender.c:7060  [size]
void __cdecl Direct3DRender_SetInfraMode(int isOn)
{
  ;
}

// source: e/3/pc/pc_direct3drender.c:7073  [size]
void __cdecl Direct3DRender_SetupBoneVertexRefs(struct LODVirModel_s *ptLODVirModel)
{
  _DWORD *pxRenderMesh; // edi
  struct MTP_BoneVertexRefPool_s *atBoneVertexRefs; // eax
  int v3; // ecx
  int v4; // ebp
  int v5; // ecx
  int v6; // esi
  int v7; // eax
  int v8; // ecx
  int v9; // edx
  int v10; // eax
  int iFaceGroup; // [esp+8h] [ebp-4h]

  pxRenderMesh = ptLODVirModel->aptVirModel[0]->ptModel->ptMesh->pxRenderMesh;
  atBoneVertexRefs = ptLODVirModel->atBoneVertexRefs;
  v3 = 50;
  do
  {
    atBoneVertexRefs->nVertices = 0;
    ++atBoneVertexRefs;
    --v3;
  }
  while ( v3 );
  v4 = 0;
  iFaceGroup = 0;
  if ( (int)pxRenderMesh[2] > 0 )
  {
    v5 = pxRenderMesh[8];
    do
    {
      v6 = 0;
      v7 = v5 + v4;
      if ( *(_WORD *)(v5 + v4 + 22) )
      {
        do
        {
          v8 = v6 + *(unsigned __int16 *)(v7 + 20);
          v9 = (unsigned __int8)*(_DWORD *)(*(_DWORD *)pxRenderMesh[6] + 40 * v8 + 32);
          v10 = 1001 * v9;
          v9 *= 4004;
          *((_DWORD *)&ptLODVirModel->aptVirModel[(*(int *)((char *)&ptLODVirModel->atBoneVertexRefs[0].nVertices + v9))++]
          + v10
          + 19) = v8;
          v5 = pxRenderMesh[8];
          v7 = v5 + v4;
          ++v6;
        }
        while ( v6 < *(unsigned __int16 *)(v5 + v4 + 22) );
      }
      v4 += 32;
      ++iFaceGroup;
    }
    while ( iFaceGroup < (int)(pxRenderMesh[2]) );
  }
}

// source: e/3/pc/pc_direct3drender.c:7113  [size]
void __cdecl Direct3DRender_Open()
{
  __int32 v0; // eax
  int v1; // ecx
  __int32 v2; // edx
  int v3; // ecx
  __int32 v4; // edx
  int v5; // ecx
  __int32 v6; // edx
  int v7; // ecx
  __int32 v8; // edx
  int v9; // ecx
  __int32 v10; // edx
  enum RenderMode_enum v11; // ecx
  __int32 v12; // edx
  enum RenderMode_enum v13; // ecx
  __int32 v14; // edx
  enum RenderMode_enum v15; // ecx
  __int32 v16; // edx
  enum RenderMode_enum v17; // ecx
  __int32 v18; // edx
  int v19; // ecx
  __int32 v20; // edx
  int v21; // ecx
  __int32 v22; // edx
  int v23; // ecx
  __int32 v24; // edx
  int v25; // ecx
  __int32 v26; // edx
  __int32 v27; // eax
  int *p_nNumVertices; // eax
  struct RenderStateBlock_t *v29; // eax
  int nNumStates; // ecx
  int v31; // ecx
  int v32; // ecx
  int v33; // ecx
  struct RenderStateBlock_t *v34; // eax
  int v35; // ecx
  int v36; // ecx
  int v37; // ecx
  struct RenderStateBlock_t *v38; // eax
  int v39; // ecx
  int v40; // ecx
  int v41; // ecx
  int v42; // ecx
  int v43; // ecx
  int v44; // eax
  struct DisplayCallbackChain_s *v45; // esi
  int v46; // eax
  struct DisplayCallbackChain_s *v47; // esi
  int v48; // eax
  struct DisplayCallbackChain_s *v49; // esi
  int v50; // eax
  struct DisplayCallbackChain_s *v51; // edx
  struct DisplayCallbackChain_s *v52; // ecx
  __int16 v53; // ax

  v0 = 130 * Direct3D_eRenderMode;
  v1 = Mesh3D_eDrawBoneMeshRenderModeMethod;
  RenderMode_atRenderMode[Direct3D_eRenderMode].apfRenderModeMethod[Mesh3D_eDrawRigidMeshRenderModeMethod] = (void (__cdecl *)(void *))Direct3DRender_DrawRigidMesh;
  v2 = v0 + v1;
  v3 = Mesh3D_eDrawSplineMeshRenderModeMethod;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v2] = (void (__cdecl *)(void *))Direct3DRender_DrawBoneMesh;
  v4 = v0 + v3;
  v5 = Mesh3D_eGenericUVFromRenderModeUV;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v4] = (void (__cdecl *)(void *))Direct3DRender_DrawSplineMesh;
  v6 = v0 + v5;
  v7 = Mesh3D_eRenderModeUVFromGenericUV;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v6] = (void (__cdecl *)(void *))sub_565430;
  v8 = v0 + v7;
  v9 = Mesh3D_eExcludeObjectRenderModeMethod;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v8] = (void (__cdecl *)(void *))sub_565450;
  v10 = v0 + v9;
  v11 = MTP_eLoadModelRenderModeMethod;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v10] = Direct3D_ExcludeObject;
  v12 = v0 + v11;
  v13 = MTP_eUnloadModelRenderModeMethod;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v12] = Direct3D_LoadModel;
  v14 = v0 + v13;
  v15 = MTP_eInitModelsRenderModeMethod;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v14] = Direct3D_UnloadModel;
  v16 = v0 + v15;
  v17 = MTP_eDeinitModelsRenderModeMethod;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v16] = Direct3D_InitModels;
  v18 = v0 + v17;
  v19 = Lightsource_eAddLightsourceRenderModeMethod;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v18] = Direct3D_DeinitModels;
  v20 = v0 + v19;
  v21 = Lightsource_eRemoveLightsourceRenderModeMethod;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v20] = Direct3DRender_AddLightsource;
  v22 = v0 + v21;
  v23 = Mesh3D_eUpdateMeshRenderModeMethod;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v22] = Direct3DRender_RemoveLightsource;
  v24 = v0 + v23;
  v25 = Mesh3D_eIsTransparentRenderModeMethod;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v24] = (void (__cdecl *)(void *))Direct3DRender_UpdateMesh;
  v26 = v0 + v25;
  v27 = BoneDynCubeObj_eCreateBruiseRenderModeMethode + v0;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v26] = (void (__cdecl *)(void *))Direct3DRender_IsTransparent;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v27] = Direct3DRender_CreateBruise;
  p_nNumVertices = &Direct3dRender_atVBQueue[0].nNumVertices;
  do
  {
    p_nNumVertices[1] = 0;
    *p_nNumVertices = 0;
    p_nNumVertices += 2002;
  }
  while ( (int)p_nNumVertices < 128101968 );
  v29 = Direct3D_ptBlendStateBlock;
  nNumStates = Direct3D_ptBlendStateBlock->nNumStates;
  Direct3D_ptBlendStateBlock->nNumStates = nNumStates + 1;
  v29->atRenderState[nNumStates].pfCallback = Direct3DRender_SetBlendStateOpaque;
  Direct3DRender_eBlendStateOpaque = nNumStates;
  v31 = v29->nNumStates;
  v29->nNumStates = v31 + 1;
  v29->atRenderState[v31].pfCallback = Direct3DRender_SetBlendStateAlphaTest;
  Direct3DRender_eBlendStateAlphaTest = v31;
  v32 = v29->nNumStates;
  v29->nNumStates = v32 + 1;
  v29->atRenderState[v32].pfCallback = Direct3DRender_SetBlendStateTransparent;
  Direct3DRender_eBlendStateTransparent = v32;
  v33 = v29->nNumStates;
  v29->nNumStates = v33 + 1;
  v29->atRenderState[v33].pfCallback = Direct3DRender_SetBlendStateAdditive;
  v34 = Direct3D_ptTextureStateBlock;
  Direct3DRender_eBlendStateAdditive = v33;
  v35 = Direct3D_ptTextureStateBlock->nNumStates;
  Direct3D_ptTextureStateBlock->nNumStates = v35 + 1;
  v34->atRenderState[v35].pfCallback = Direct3DRender_SetTextureStateRigid;
  Direct3DRender_eTextureStateRigid = v35;
  v36 = v34->nNumStates;
  v34->nNumStates = v36 + 1;
  v34->atRenderState[v36].pfCallback = Direct3DRender_SetTextureStateLightmap;
  Direct3DRender_eTextureStateLightmap = v36;
  v37 = v34->nNumStates;
  v34->nNumStates = v37 + 1;
  v34->atRenderState[v37].pfCallback = Direct3DRender_SetInfrared;
  v38 = Direct3D_ptGenericStateBlock;
  Direct3DRender_eInfraredFilter = v37;
  v39 = Direct3D_ptGenericStateBlock->nNumStates;
  Direct3D_ptGenericStateBlock->nNumStates = v39 + 1;
  v38->atRenderState[v39].pfCallback = Direct3DRender_SetGenericStateRigid;
  Direct3DRender_eGenericStateRigid = v39;
  v40 = v38->nNumStates;
  v38->nNumStates = v40 + 1;
  v38->atRenderState[v40].pfCallback = Direct3DRender_SetGenericStateLightmap;
  Direct3DRender_eGenericStateLightmap = v40;
  v41 = v38->nNumStates;
  v38->nNumStates = v41 + 1;
  v38->atRenderState[v41].pfCallback = Direct3DRender_SetGenericStateTransparentRigid;
  Direct3DRender_eGenericStateTransparentRigid = v41;
  v42 = v38->nNumStates;
  v38->nNumStates = v42 + 1;
  v38->atRenderState[v42].pfCallback = Direct3DRender_SetGenericStateTransparentLightmap;
  Direct3DRender_eGenericStateTransparentLightmap = v42;
  v43 = v38->nNumStates;
  v38->nNumStates = v43 + 1;
  v38->atRenderState[v43].pfCallback = Direct3DRender_SetGenericStateBone;
  Direct3DRender_nNumVertexBuffers = 0;
  Direct3DRender_eGenericStateBone = v43;
  v44 = 0;
  while ( Direct3D_atCallback[v44].pfCallback )
  {
    if ( ++v44 >= 32 )
    {
LABEL_6:
      LDebug_Error("No more Direct3D callbacks available.");
      abort();
    }
  }
  v45 = Direct3D_ptRestoreCallback;
  Direct3D_atCallback[v44].pfCallback = Direct3DRender_RestoreCallback;
  Direct3D_atCallback[v44].ptNext = v45;
  Direct3D_ptRestoreCallback = (struct DisplayCallbackChain_s *)(8 * v44 + 139166048);
  v46 = 0;
  while ( Direct3D_atCallback[v46].pfCallback )
  {
    if ( ++v46 >= 32 )
      goto LABEL_6;
  }
  v47 = Direct3D_ptDestroyCallback;
  Direct3D_atCallback[v46].pfCallback = Direct3DRender_DestroyCallback;
  Direct3D_atCallback[v46].ptNext = v47;
  Direct3D_ptDestroyCallback = (struct DisplayCallbackChain_s *)(8 * v46 + 139166048);
  v48 = 0;
  while ( Direct3D_atCallback[v48].pfCallback )
  {
    if ( ++v48 >= 32 )
      goto LABEL_6;
  }
  v49 = Direct3D_ptSetModeCallback;
  Direct3D_atCallback[v48].pfCallback = (void (__cdecl *)())sub_565470;
  Direct3D_atCallback[v48].ptNext = v49;
  Direct3D_ptSetModeCallback = (struct DisplayCallbackChain_s *)(8 * v48 + 139166048);
  v50 = 0;
  while ( Direct3D_atCallback[v50].pfCallback )
  {
    if ( ++v50 >= 32 )
      goto LABEL_6;
  }
  v51 = Direct3D_ptUnsetModeCallback;
  v52 = (struct DisplayCallbackChain_s *)(8 * v50 + 139166048);
  Direct3D_atCallback[v50].pfCallback = (void (__cdecl *)())sub_5654B0;
  v53 = QCube_eGetClosestVertexQTaskEvent;
  v52->ptNext = v51;
  Direct3D_ptUnsetModeCallback = v52;
  Direct3D_pfBlitCallback = (void (__cdecl *)(struct DisplayBlitContext_s *))Direct3DRender_BlitCallback;
  QTask_LinkQTaskEventHandlerFn(SplineObjSegment_eQTaskType, v53, SplineObjSegment_GetClosestVertex);
}

// source: e/3/pc/pc_direct3drender.c:7182  [size]
void __cdecl Direct3DRender_Close()
{
  int v0; // edx
  struct RenderStateBlock_t *v1; // esi
  struct RenderStateBlock_t *v2; // ecx
  struct RenderStateBlock_t *v3; // edx

  v0 = Direct3DRender_eGenericStateTransparentLightmap;
  v1 = Direct3D_ptBlendStateBlock;
  Direct3D_ptBlendStateBlock->atRenderState[Direct3DRender_eBlendStateTransparent].pfCallback = nullptr;
  v2 = Direct3D_ptGenericStateBlock;
  Direct3D_ptGenericStateBlock->atRenderState[v0].pfCallback = nullptr;
  v2->atRenderState[Direct3DRender_eGenericStateTransparentRigid].pfCallback = nullptr;
  v3 = Direct3D_ptTextureStateBlock;
  Direct3D_ptTextureStateBlock->atRenderState[Direct3DRender_eTextureStateLightmap].pfCallback = nullptr;
  v2->atRenderState[Direct3DRender_eGenericStateLightmap].pfCallback = nullptr;
  v3->atRenderState[Direct3DRender_eTextureStateRigid].pfCallback = nullptr;
  v1->atRenderState[Direct3DRender_eBlendStateOpaque].pfCallback = nullptr;
  v2->atRenderState[Direct3DRender_eGenericStateRigid].pfCallback = nullptr;
  v2->atRenderState[Direct3DRender_eGenericStateBone].pfCallback = nullptr;
  v3->atRenderState[Direct3DRender_eInfraredFilter].pfCallback = nullptr;
  Direct3D_pfBlitCallback = nullptr;
}
