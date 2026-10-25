/* e/3/pc/pc_terrainrender.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: e/3/pc/pc_terrainrender.c:575  [size]
struct TerrainRenderChunk_t *__cdecl TerrainRender_UnlockMaterialVertexBuffers(
        struct TerrainRenderChunk_t *ptRenderChunk)
{
  unsigned __int8 *v1; // ecx
  int iMaterial; // eax
  int v4; // ebx
  unsigned __int8 *v5; // edi
  unsigned __int8 *pxLockedData; // [esp+14h] [ebp-4h] BYREF

  pxLockedData = v1;
  iMaterial = ptRenderChunk->iMaterial;
  v4 = TerrainRender_ptContext->aiBuffer[iMaterial];
  if ( TerrainRender_aptMaterialVertexBuffer[v4]->lpVtbl->Lock(
         TerrainRender_aptMaterialVertexBuffer[v4],
         4 * ptRenderChunk->iMinVertex,
         4 * (ptRenderChunk->iMaxVertex - ptRenderChunk->iMinVertex) + 4,
         &pxLockedData,
         TerrainRender_atMaterialReadableBuffer[iMaterial].isInUse != 0 ? 4096 : 0x2000) )
  {
    LDebug_Error("Lost vertexbuffer");
    abort();
  }
  v5 = pxLockedData;
  TerrainRender_atMaterialReadableBuffer[ptRenderChunk->iMaterial].isInUse = 1;
  qmemcpy(
    v5,
    (void *)(4 * (ptRenderChunk->iMinVertex + 30003 * ptRenderChunk->iMaterial) + 135525312),
    4 * (ptRenderChunk->iMaxVertex - ptRenderChunk->iMinVertex) + 4);
  return (struct TerrainRenderChunk_t *)TerrainRender_aptMaterialVertexBuffer[v4]->lpVtbl->Unlock(TerrainRender_aptMaterialVertexBuffer[v4]);
}

// source: e/3/pc/pc_terrainrender.c:620  [size]
void __cdecl TerrainRender_DeleteMaterialVertexBuffers()
{
  int v0; // esi
  int v1; // eax

  v0 = 0;
  if ( TerrainRender_nNumMaterialVertexBuffers > 0 )
  {
    do
    {
      TerrainRender_aptMaterialVertexBuffer[v0]->lpVtbl->Release(TerrainRender_aptMaterialVertexBuffer[v0]);
      v1 = TerrainRender_nNumMaterialVertexBuffers;
      TerrainRender_aptMaterialVertexBuffer[v0++] = nullptr;
    }
    while ( v0 < v1 );
  }
  TerrainRender_nNumMaterialVertexBuffers = 0;
}

// source: e/3/pc/pc_terrainrender.c:648  [size]
void __cdecl TerrainRender_AllocateMaterialVertexBuffers(int nNumMaterials)
{
  struct IDirect3DVertexBuffer8 **v1; // esi
  int v2; // edi

  if ( nNumMaterials > 0 )
  {
    v1 = TerrainRender_aptMaterialVertexBuffer;
    v2 = nNumMaterials;
    do
    {
      Direct3D_ptDevice->lpVtbl->CreateVertexBuffer(
        Direct3D_ptDevice,
        120000u,
        (Direct3D_isHWVertexShader != 0 ? 0 : 0x10) | 0x208,
        0,
        D3DPOOL_DEFAULT,
        v1++);
      --v2;
    }
    while ( v2 );
  }
  TerrainRender_nNumMaterialVertexBuffers = nNumMaterials;
}

// source: e/3/pc/pc_terrainrender.c:712  [size]
void __cdecl TerrainRender_SetModeCallback()
{
  int i; // edi
  struct IDirect3DDevice8Vtbl *lpVtbl; // ebp
  unsigned int *v2; // eax
  struct IDirect3DDevice8Vtbl *v3; // ebp
  unsigned int *v4; // eax
  char *v5; // eax
  struct IDirect3DDevice8Vtbl *v6; // esi
  unsigned int *v7; // eax
  int v8; // [esp-4h] [ebp-14h]
  int v9; // [esp-4h] [ebp-14h]
  int v10; // [esp-4h] [ebp-14h]

  Direct3D_ptDevice->lpVtbl->SetRenderState(
    Direct3D_ptDevice,
    D3DRS_SOFTWAREVERTEXPROCESSING,
    Direct3D_isHWVertexShader == 0);
  Direct3D_ptDevice->lpVtbl->CreateVertexBuffer(
    Direct3D_ptDevice,
    480000u,
    (Direct3D_isHWVertexShader != 0 ? 0 : 0x10) | 0x208,
    0,
    D3DPOOL_DEFAULT,
    &TerrainRender_ptVertexBuffer);
  Direct3D_ptDevice->lpVtbl->CreateIndexBuffer(
    Direct3D_ptDevice,
    1000000u,
    (Direct3D_isHWVertexShader != 0 ? 0 : 0x10) | 0x208,
    D3DFMT_INDEX16,
    D3DPOOL_DEFAULT,
    &TerrainRender_ptIndexBuffer);
  for ( i = 0; i < 3; ++i )
  {
    D3DXAssembleShader(
      (int)TerrainRender_azVertexShader[i],
      strlen(TerrainRender_azVertexShader[i]),
      0,
      0,
      (int)&stru_866FAB0,
      (int)&TerrainRender_ptVertexShaderErrors);
    if ( TerrainRender_ptVertexShaderErrors && !stru_866FAB0 )
      goto LABEL_19;
    lpVtbl = Direct3D_ptDevice->lpVtbl;
    v8 = Direct3D_isHWVertexShader != 0 ? 0 : 0x10;
    v2 = (unsigned int *)stru_866FAB0->lpVtbl->GetBufferPointer(stru_866FAB0);
    lpVtbl->CreateVertexShader(
      Direct3D_ptDevice,
      TerrainRender_abVertexLayout,
      v2,
      &TerrainRender_anVertexShader[i],
      v8);
    if ( stru_866FAB0 )
    {
      stru_866FAB0->lpVtbl->Release(stru_866FAB0);
      stru_866FAB0 = nullptr;
    }
    if ( TerrainRender_ptVertexShaderErrors )
    {
      TerrainRender_ptVertexShaderErrors->lpVtbl->Release(TerrainRender_ptVertexShaderErrors);
      TerrainRender_ptVertexShaderErrors = nullptr;
    }
    if ( !TerrainRender_anVertexShader[i] )
      goto LABEL_28;
    D3DXAssembleShader(
      (int)TerrainRender_azVertexShaderComplete[i],
      strlen(TerrainRender_azVertexShaderComplete[i]),
      0,
      0,
      (int)&stru_866FAB0,
      (int)&TerrainRender_ptVertexShaderErrors);
    if ( TerrainRender_ptVertexShaderErrors && !stru_866FAB0 )
      goto LABEL_19;
    v3 = Direct3D_ptDevice->lpVtbl;
    v9 = Direct3D_isHWVertexShader != 0 ? 0 : 0x10;
    v4 = (unsigned int *)stru_866FAB0->lpVtbl->GetBufferPointer(stru_866FAB0);
    v3->CreateVertexShader(
      Direct3D_ptDevice,
      TerrainRender_abVertexLayout,
      v4,
      &TerrainRender_anVertexShaderComplete[i],
      v9);
    if ( stru_866FAB0 )
    {
      stru_866FAB0->lpVtbl->Release(stru_866FAB0);
      stru_866FAB0 = nullptr;
    }
    if ( TerrainRender_ptVertexShaderErrors )
    {
      TerrainRender_ptVertexShaderErrors->lpVtbl->Release(TerrainRender_ptVertexShaderErrors);
      TerrainRender_ptVertexShaderErrors = nullptr;
    }
    if ( !TerrainRender_anVertexShaderComplete[i] )
      goto LABEL_28;
  }
  D3DXAssembleShader(
    (int)off_6B0354,
    strlen((char *)off_6B0354),
    0,
    0,
    (int)&stru_866FAB0,
    (int)&TerrainRender_ptVertexShaderErrors);
  if ( TerrainRender_ptVertexShaderErrors && !stru_866FAB0 )
  {
LABEL_19:
    v5 = (char *)TerrainRender_ptVertexShaderErrors->lpVtbl->GetBufferPointer(TerrainRender_ptVertexShaderErrors);
    LDebug_Error("Fatal error in vertex shader:\n%s", v5);
    goto LABEL_20;
  }
  v6 = Direct3D_ptDevice->lpVtbl;
  v10 = Direct3D_isHWVertexShader != 0 ? 0 : 0x10;
  v7 = (unsigned int *)stru_866FAB0->lpVtbl->GetBufferPointer(stru_866FAB0);
  v6->CreateVertexShader(
    Direct3D_ptDevice,
    TerrainRender_abLightmapVertexLayout,
    v7,
    &TerrainRender_nLightmapVertexShader,
    v10);
  if ( stru_866FAB0 )
  {
    stru_866FAB0->lpVtbl->Release(stru_866FAB0);
    stru_866FAB0 = nullptr;
  }
  if ( TerrainRender_ptVertexShaderErrors )
  {
    TerrainRender_ptVertexShaderErrors->lpVtbl->Release(TerrainRender_ptVertexShaderErrors);
    TerrainRender_ptVertexShaderErrors = nullptr;
  }
  if ( !TerrainRender_nLightmapVertexShader )
  {
LABEL_28:
    LDebug_Error("Failed to create vertex shader");
LABEL_20:
    abort();
  }
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SOFTWAREVERTEXPROCESSING, 0);
}

// source: e/3/pc/pc_terrainrender.c:886  [size]
void __cdecl TerrainRender_UnsetModeCallback()
{
  int i; // esi

  TerrainRender_DeleteMaterialVertexBuffers();
  for ( i = 0; i < 3; ++i )
  {
    if ( TerrainRender_anVertexShaderComplete[i] )
      Direct3D_ptDevice->lpVtbl->DeleteVertexShader(Direct3D_ptDevice, TerrainRender_anVertexShaderComplete[i]);
    if ( TerrainRender_anVertexShader[i] )
      Direct3D_ptDevice->lpVtbl->DeleteVertexShader(Direct3D_ptDevice, TerrainRender_anVertexShader[i]);
  }
  if ( TerrainRender_nLightmapVertexShader )
    Direct3D_ptDevice->lpVtbl->DeleteVertexShader(Direct3D_ptDevice, TerrainRender_nLightmapVertexShader);
  if ( TerrainRender_ptIndexBuffer )
  {
    TerrainRender_ptIndexBuffer->lpVtbl->Release(TerrainRender_ptIndexBuffer);
    TerrainRender_ptIndexBuffer = nullptr;
  }
  if ( TerrainRender_ptVertexBuffer )
  {
    TerrainRender_ptVertexBuffer->lpVtbl->Release(TerrainRender_ptVertexBuffer);
    TerrainRender_ptVertexBuffer = nullptr;
  }
}

// source: e/3/pc/pc_terrainrender.c:949  [size]
// attributes: thunk
void __cdecl TerrainRender_DestroyCallback()
{
  TerrainRender_UnsetModeCallback();
}

// source: e/3/pc/pc_terrainrender.c:962  [size]
// attributes: thunk
void __cdecl TerrainRender_RestoreCallback()
{
  TerrainRender_SetModeCallback();
}

// source: e/3/pc/pc_terrainrender.c:975  [size~]
void __cdecl TerrainRender_SetTextureState(void *pxContext)
{
  Direct3DRender_SetTextureStageFilteringMode(0);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ADDRESSU, 1u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ADDRESSV, 1u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_TEXCOORDINDEX, 0);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAOP, 3u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAARG1, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAARG2, 0);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLOROP, 4u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLORARG1, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLORARG2, 0);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_TEXTURETRANSFORMFLAGS, 0);
  Direct3DRender_SetTextureStageFilteringMode(1u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_ADDRESSU, 1u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_ADDRESSV, 1u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_TEXCOORDINDEX, 1u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_ALPHAOP, 3u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_ALPHAARG1, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_ALPHAARG2, 1u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_COLOROP, 4u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_COLORARG1, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_COLORARG2, 1u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_TEXTURETRANSFORMFLAGS, 0);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 2u, D3DTSS_MINFILTER, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 2u, D3DTSS_MAGFILTER, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 2u, D3DTSS_ADDRESSU, 3u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 2u, D3DTSS_ADDRESSV, 3u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 2u, D3DTSS_MIPFILTER, 1u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 2u, D3DTSS_TEXCOORDINDEX, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 2u, D3DTSS_ALPHAOP, 3u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 2u, D3DTSS_ALPHAARG1, 0);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 2u, D3DTSS_ALPHAARG2, 1u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 2u, D3DTSS_COLOROP, 7u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 2u, D3DTSS_COLORARG1, 0);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 2u, D3DTSS_COLORARG2, 1u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 2u, D3DTSS_COLOROP, 1u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 2u, D3DTSS_TEXTURETRANSFORMFLAGS, 0);
}

// source: e/3/pc/pc_terrainrender.c:1030  [size~]
void __cdecl TerrainRender_SetGenericState(void *pxContext)
{
  _DWORD v1[17]; // [esp+28h] [ebp-44h] BYREF

  memset(v1, 0, sizeof(v1));
  v1[0] = 1065353216;
  v1[1] = 1065353216;
  v1[2] = 1065353216;
  v1[4] = 1065353216;
  v1[5] = 1065353216;
  v1[6] = 1065353216;
  Direct3D_ptDevice->lpVtbl->SetMaterial(Direct3D_ptDevice, (struct _D3DMATERIAL8 *)v1);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_TEXTUREFACTOR, -16777216u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_CLIPPING, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(
    Direct3D_ptDevice,
    D3DRS_FOGCOLOR,
    (__int64)(Mesh3D_atFogColor[0].vZ * 255.0)
  - (((unsigned int)(__int64)(Mesh3D_atFogColor[0].vY * -255.0)
    + ((unsigned int)(__int64)(Mesh3D_atFogColor[0].vX * -255.0) << 8)) << 8));
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGDENSITY, LODWORD(DrawTerrainMesh_vFogDensity));
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGTABLEMODE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGVERTEXMODE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGENABLE, QVertex_isFog);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SPECULARENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_CULLMODE, 2u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_COLORVERTEX, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_DITHERENABLE, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHATESTENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZENABLE, Direct3D_bZBufferMode);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZWRITEENABLE, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZFUNC, 4u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_LIGHTING, 0);
}

// source: e/3/pc/pc_terrainrender.c:1077  [size]
void __cdecl TerrainRender_SetBlendState(void *pxContext)
{
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHABLENDENABLE, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SRCBLEND, 5u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_DESTBLEND, 2u);
}

// source: e/3/pc/pc_terrainrender.c:1097  [size]
void __cdecl TerrainRender_CalculateRenderVertex(
        int iVertex,
        int iVertex0,
        int iVertex1,
        float vT,
        struct TerrainContext_t *ptContext)
{
  double v5; // st7
  struct TerrainRenderVertex_t *v7; // esi
  int v8; // edi
  double v9; // st7
  unsigned __int8 v10; // al
  double _41; // st7
  int v12; // ecx
  double v13; // st7
  struct TerrainContext_t *v16; // esi
  int v17; // eax
  double v18; // st7
  int iMaterial; // ecx
  int v20; // eax
  float vMaterialSource; // [esp+0h] [ebp-4h]
  float iVertex0a = *(float *)&iVertex1; // [esp+Ch] [ebp+8h] ARGSLOT

  v5 = TerrainRender_vMaterialMorphSpeed * vT;
  v7 = &TerrainRender_ptLockedVertex[iVertex];
  v8 = 32 * iVertex1 + 133165248;
  if ( v5 >= 1.0 )
    iVertex0a = 1.0;
  else
    iVertex0a = v5;
  if ( vT < 1.0 )
  {
    v9 = (*(float *)(v8 + 8) + TerrainRender_atManualVertex[iVertex0].tPos.vZ) * 0.5;
    TerrainRender_atManualVertex[iVertex].tPos.vZ = (1.0 - cos(vT * 3.1415927410125732))
                                                  * 0.5
                                                  * (TerrainRender_atManualVertex[iVertex].tPos.vZ - v9)
                                                  + v9;
  }
  v10 = DiscardTask_IsDiscardVertex((struct real32x3_t *)(32 * iVertex + 133165248));
  _41 = TerrainRender_tMatrix._41;
  TerrainRender_atManualVertex[iVertex].bScreenOutcode = v10;
  v7->vX = TerrainRender_atManualVertex[iVertex].tPos.vX;
  v7->vY = TerrainRender_atManualVertex[iVertex].tPos.vY;
  v7->vZ = TerrainRender_atManualVertex[iVertex].tPos.vZ;
  v12 = 0;
  v13 = (_41 * TerrainRender_atManualVertex[iVertex].tPos.vX
       + TerrainRender_tMatrix._43 * TerrainRender_atManualVertex[iVertex].tPos.vZ
       + TerrainRender_tMatrix._42 * TerrainRender_atManualVertex[iVertex].tPos.vY
       + TerrainRender_tMatrix._44)
      * DrawTerrainMesh_vFogDensity
      * 1.442695040888963407;
  v7->vFog = 1.0 / pow(2.0, v13);
  v16 = TerrainRender_ptContext;
  TerrainRender_atManualVertex[iVertex].bMaterialsEnabled = 0;
  if ( v16->nNumMaterials > 0 )
  {
    do
    {
      if ( 120012 * v16->aiMaterial[v12] != -135525312 )
      {
        vMaterialSource = (1.0 - iVertex0a) * 0.5;
        v17 = 120012 * v16->aiMaterial[v12] + 135525312;
        v18 = (*(float *)(v17 + 4 * iVertex0) + *(float *)(v17 + 4 * iVertex1)) * vMaterialSource;
        TerrainRender_atMaterialReadableBuffer[v16->aiMaterial[v12]].atBuffer[iVertex].vWeight = v18;
        if ( v18 > 0.0 )
          TerrainRender_atManualVertex[iVertex].bMaterialsEnabled |= 1 << v12;
      }
      ++v12;
    }
    while ( v12 < v16->nNumMaterials );
  }
  if ( iVertex0a > 0.0 )
  {
    iMaterial = TerrainRender_atManualVertex[iVertex].iMaterial;
    if ( 120012 * iMaterial != -135525312 )
    {
      v20 = 120012 * TerrainRender_atManualVertex[iVertex].iMaterial + 135525312;
      *(float *)(v20 + 4 * iVertex) = iVertex0a + *(float *)(v20 + 4 * iVertex);
    }
    TerrainRender_atManualVertex[iVertex].bMaterialsEnabled |= 1 << v16->aiBuffer[iMaterial];
  }
}

// source: e/3/pc/pc_terrainrender.c:1203  [size~]
void __cdecl TerrainRender_SetBlendMode(enum TerrainRenderBlendMode_e eBlendMode)
{
  int v1; // eax
  int v2; // esi
  unsigned int v3; // edi
  unsigned int v4; // esi

  v1 = 0;
  v2 = 0;
  if ( Direct3D_isHWVertexShader )
  {
    if ( Direct3D_tAdapterIdentifier.VendorId != 4139 )
      goto LABEL_10;
    v1 = 1;
  }
  else if ( Direct3D_tAdapterIdentifier.VendorId == 4318 )
  {
    v1 = 1;
  }
  else
  {
    if ( Direct3D_tAdapterIdentifier.VendorId != 4170 || Direct3D_tAdapterIdentifier.DeviceId != 16 )
      goto LABEL_10;
    v1 = 0;
  }
  v2 = 1;
LABEL_10:
  v3 = dword_6B0364 * (v1 ^ TerrainRender_isWireframe);
  v4 = TerrainRender_isWireframe ^ v2;
  switch ( eBlendMode )
  {
    case TERRAINRENDER_BLENDMODE_BLACK:
      Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLOROP, 2u);
      Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLORARG1, 3u);
      Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_COLOROP, 1u);
      Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGCOLOR, 0);
      Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZWRITEENABLE, 1u);
      Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZBIAS, 0);
      Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHABLENDENABLE, 0);
      break;
    case TERRAINRENDER_BLENDMODE_OPAQUE:
      Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHABLENDENABLE, 1u);
      Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SRCBLEND, 5u);
      Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_DESTBLEND, 1u);
      Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLOROP, 4u);
      Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLORARG1, 2u);
      Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLORARG2, 0);
      Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_COLOROP, 4u);
      Direct3D_ptDevice->lpVtbl->SetRenderState(
        Direct3D_ptDevice,
        D3DRS_FOGCOLOR,
        (__int64)(Mesh3D_atFogColor[0].vZ * 127.0)
      - (((unsigned int)(__int64)(Mesh3D_atFogColor[0].vY * -127.0)
        + ((unsigned int)(__int64)(Mesh3D_atFogColor[0].vX * -127.0) << 8)) << 8));
      Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZWRITEENABLE, 1u);
      Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZBIAS, 0);
      Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ADDRESSU, 1u);
      Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ADDRESSV, 1u);
      break;
    case TERRAINRENDER_BLENDMODE_ADDITIVE:
      Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHABLENDENABLE, 1u);
      Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SRCBLEND, 5u);
      Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_DESTBLEND, 2u);
      Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLOROP, 4u);
      Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLORARG1, 2u);
      Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLORARG2, 0);
      Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_COLOROP, 4u);
      Direct3D_ptDevice->lpVtbl->SetRenderState(
        Direct3D_ptDevice,
        D3DRS_FOGCOLOR,
        (__int64)(Mesh3D_atFogColor[0].vZ * 127.0)
      - (((unsigned int)(__int64)(Mesh3D_atFogColor[0].vY * -127.0)
        + ((unsigned int)(__int64)(Mesh3D_atFogColor[0].vX * -127.0) << 8)) << 8));
      Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZWRITEENABLE, 0);
      Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZBIAS, v3);
      Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ADDRESSU, 1u);
      Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ADDRESSV, 1u);
      break;
    case TERRAINRENDER_BLENDMODE_MULTIPLICATIVE:
      Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHABLENDENABLE, 1u);
      Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SRCBLEND, 9u);
      Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_DESTBLEND, 3u);
      Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLOROP, 2u);
      Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLORARG1, 2u);
      Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLORARG2, 0);
      Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_COLOROP, 1u);
      Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGCOLOR, -1u);
      Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZWRITEENABLE, 0);
      Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZBIAS, v4);
      Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ADDRESSU, 3u);
      Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ADDRESSV, 3u);
      break;
    case TERRAINRENDER_BLENDMODE_OPAQUE_WITH_LIGHTMAP:
      Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHABLENDENABLE, 1u);
      Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SRCBLEND, 5u);
      Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_DESTBLEND, 1u);
      Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLOROP, 4u);
      Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLORARG1, 2u);
      Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLORARG2, 0);
      Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_COLOROP, 4u);
      Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_COLORARG1, 2u);
      Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_COLORARG2, 1u);
      Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 2u, D3DTSS_COLOROP, 5u);
      Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 2u, D3DTSS_COLORARG1, 2u);
      Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 2u, D3DTSS_COLORARG2, 1u);
      Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 3u, D3DTSS_COLOROP, 1u);
      Direct3D_ptDevice->lpVtbl->SetRenderState(
        Direct3D_ptDevice,
        D3DRS_FOGCOLOR,
        (__int64)(Mesh3D_atFogColor[0].vZ * 255.0)
      - (((unsigned int)(__int64)(Mesh3D_atFogColor[0].vY * -255.0)
        + ((unsigned int)(__int64)(Mesh3D_atFogColor[0].vX * -255.0) << 8)) << 8));
      Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZWRITEENABLE, 1u);
      Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZBIAS, 0);
      break;
    case TERRAINRENDER_BLENDMODE_ADDITIVE_WITH_LIGHTMAP:
      Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHABLENDENABLE, 1u);
      Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SRCBLEND, 5u);
      Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_DESTBLEND, 2u);
      Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLOROP, 4u);
      Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLORARG1, 2u);
      Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLORARG2, 0);
      Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_COLOROP, 4u);
      Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_COLORARG1, 2u);
      Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_COLORARG2, 1u);
      Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 2u, D3DTSS_COLOROP, 5u);
      Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 2u, D3DTSS_COLORARG1, 2u);
      Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 2u, D3DTSS_COLORARG2, 1u);
      Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 3u, D3DTSS_COLOROP, 1u);
      Direct3D_ptDevice->lpVtbl->SetRenderState(
        Direct3D_ptDevice,
        D3DRS_FOGCOLOR,
        (__int64)(Mesh3D_atFogColor[0].vZ * 255.0)
      - (((unsigned int)(__int64)(Mesh3D_atFogColor[0].vY * -255.0)
        + ((unsigned int)(__int64)(Mesh3D_atFogColor[0].vX * -255.0) << 8)) << 8));
      Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZWRITEENABLE, 0);
      Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZBIAS, v4);
      break;
    default:
      return;
  }
}

// source: e/3/pc/pc_terrainrender.c:1410  [size]
struct TerrainMaterial_t *__cdecl TerrainRender_SetMaterialTextures(
        struct TerrainMaterial_t *ptTerrainMaterial)
{
  #pragma pack(push, 1)
  union
  {
    struct { float avTextureScale0[4]; };
    struct { char igi2_o1[16]; float avTextureScale1[4]; };
    char igi2_extent[32];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double vScale; // st7
  struct IDirect3DBaseTexture8 *ptDirect3DBaseTexture; // eax
  struct TerrainMaterial_t *result; // eax
  struct IDirect3DBaseTexture8 *v5; // esi

  vScale = ptTerrainMaterial->atTexture[0].vScale;
  igi2_frame.avTextureScale0[2] = 0.0;
  igi2_frame.avTextureScale0[3] = 1.0;
  igi2_frame.avTextureScale1[2] = 0.0;
  igi2_frame.avTextureScale1[3] = 1.0;
  igi2_frame.avTextureScale0[0] = 1.0 / (vScale * 4096.0);
  igi2_frame.avTextureScale0[1] = igi2_frame.avTextureScale0[0];
  igi2_frame.avTextureScale1[0] = 1.0 / (ptTerrainMaterial->atTexture[1].vScale * 4096.0);
  igi2_frame.avTextureScale1[1] = igi2_frame.avTextureScale1[0];
  Direct3D_ptDevice->lpVtbl->SetVertexShaderConstant(Direct3D_ptDevice, 11u, igi2_frame.avTextureScale0, 1u);
  Direct3D_ptDevice->lpVtbl->SetVertexShaderConstant(Direct3D_ptDevice, 12u, igi2_frame.avTextureScale1, 1u);
  if ( ptTerrainMaterial->atTexture[0].isTextureLoaded )
    ptDirect3DBaseTexture = ptTerrainMaterial->atTexture[0].tTexInfo.ptDirect3DBaseTexture;
  else
    ptDirect3DBaseTexture = nullptr;
  if ( ptDirect3DBaseTexture != Direct3D_tState.aptTexture[0] )
  {
    Direct3D_tState.aptTexture[0] = ptDirect3DBaseTexture;
    Direct3D_ptDevice->lpVtbl->SetTexture(Direct3D_ptDevice, 0, ptDirect3DBaseTexture);
  }
  result = (struct TerrainMaterial_t *)ptTerrainMaterial->atTexture[1].isTextureLoaded;
  if ( result )
    v5 = ptTerrainMaterial->atTexture[1].tTexInfo.ptDirect3DBaseTexture;
  else
    v5 = nullptr;
  if ( v5 != Direct3D_tState.aptTexture[1] )
  {
    Direct3D_tState.aptTexture[1] = v5;
    return (struct TerrainMaterial_t *)Direct3D_ptDevice->lpVtbl->SetTexture(Direct3D_ptDevice, 1u, v5);
  }
  return result;
}

// source: e/3/pc/pc_terrainrender.c:1442  [size]
struct QObjectVector_s *__cdecl TerrainRender_DrawRenderChunk_(struct TerrainRenderChunk_t *a1)
{
  #pragma pack(push, 1)
  union
  {
    struct { float avScale[4]; };
    struct { char igi2_o1[16]; float avOffset[4]; };
    char igi2_extent[32];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  enum TerrainRenderBlendMode_e eBlendMode; // edx
  int iMaterial; // eax
  struct TerrainMaterial_t *v3; // edi
  int iLightmap; // ecx
  int v5; // ecx
  struct QObjectVector_s *v6; // eax
  unsigned int v8; // eax
  struct TexInfo_s *v9; // edi
  int v10; // eax
  double v11; // st7
  struct TexInfo_s *v12; // ebx
  struct TerrainMaterial_t *v13; // edi
  int v14; // eax
  double vY; // st7
  struct QObjectVector_s *v16; // eax

  eBlendMode = a1->eBlendMode;
  if ( eBlendMode == TERRAINRENDER_BLENDMODE_OPAQUE_WITH_LIGHTMAP
    || eBlendMode == TERRAINRENDER_BLENDMODE_ADDITIVE_WITH_LIGHTMAP )
  {
    iLightmap = a1->iLightmap;
    iMaterial = a1->iMaterial;
    v12 = TerrainRender_ptContext->aptLightmap[iLightmap];
    v13 = TerrainRender_ptContext->aptTerrainMaterial[iMaterial];
    if ( !v13 )
      goto LABEL_6;
    TerrainRender_ptIndexBuffer->lpVtbl->Unlock(TerrainRender_ptIndexBuffer);
    TerrainRender_ptVertexBuffer->lpVtbl->Unlock(TerrainRender_ptVertexBuffer);
    TerrainRender_UnlockMaterialVertexBuffers(a1);
    Direct3D_tState.aptStreamData[1] = TerrainRender_aptMaterialVertexBuffer[TerrainRender_ptContext->aiBuffer[a1->iMaterial]];
    Direct3D_tState.anStride[1] = 4;
    Direct3D_ptDevice->lpVtbl->SetStreamSource(Direct3D_ptDevice, 1u, Direct3D_tState.aptStreamData[1], 4u);
    TerrainRender_SetBlendMode(a1->eBlendMode);
    TerrainRender_SetMaterialTextures(v13);
    v14 = a1->iLightmap;
    igi2_frame.avOffset[0] = TerrainRender_ptContext->atLightmapOffset[v14].vX;
    vY = TerrainRender_ptContext->atLightmapOffset[v14].vY;
    igi2_frame.avOffset[2] = 0.0;
    igi2_frame.avOffset[1] = vY;
    igi2_frame.avOffset[3] = 0.0;
    igi2_frame.avScale[0] = TerrainRender_ptContext->atLightmapScale[v14].vX;
    igi2_frame.avScale[1] = TerrainRender_ptContext->atLightmapScale[v14].vY;
    igi2_frame.avScale[2] = 0.0;
    igi2_frame.avScale[3] = 1.0;
    Direct3D_ptDevice->lpVtbl->SetVertexShaderConstant(Direct3D_ptDevice, 13u, igi2_frame.avOffset, 1u);
    Direct3D_ptDevice->lpVtbl->SetVertexShaderConstant(Direct3D_ptDevice, 14u, igi2_frame.avScale, 1u);
    if ( v12->ptDirect3DBaseTexture != Direct3D_tState.aptTexture[2] )
    {
      Direct3D_tState.aptTexture[2] = v12->ptDirect3DBaseTexture;
      Direct3D_ptDevice->lpVtbl->SetTexture(Direct3D_ptDevice, 2u, Direct3D_tState.aptTexture[2]);
    }
    Direct3D_tState.nHandle = TerrainRender_anVertexShaderComplete[v13->eMappingStyle];
    Direct3D_ptDevice->lpVtbl->SetVertexShader(Direct3D_ptDevice, Direct3D_tState.nHandle);
    if ( !TerrainRender_ptVertexShaderFunction )
    {
      Direct3D_ptDevice->lpVtbl->DrawIndexedPrimitive(
        Direct3D_ptDevice,
        D3DPT_TRIANGLELIST,
        a1->iMinVertex,
        a1->iMaxVertex - a1->iMinVertex + 1,
        a1->iStartIndex,
        a1->nNumIndices / 3);
      goto LABEL_20;
    }
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FILLMODE, 2u);
    Direct3D_ptDevice->lpVtbl->DrawIndexedPrimitive(
      Direct3D_ptDevice,
      D3DPT_TRIANGLELIST,
      a1->iMinVertex,
      a1->iMaxVertex - a1->iMinVertex + 1,
      a1->iStartIndex,
      a1->nNumIndices / 3);
LABEL_19:
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FILLMODE, 3u);
    goto LABEL_20;
  }
  if ( eBlendMode == TERRAINRENDER_BLENDMODE_MULTIPLICATIVE )
  {
    if ( TerrainRender_ptContext->isDynamicShading )
      goto LABEL_25;
    v9 = TerrainRender_ptContext->aptLightmap[a1->iMaterial];
    TerrainRender_ptIndexBuffer->lpVtbl->Unlock(TerrainRender_ptIndexBuffer);
    TerrainRender_ptVertexBuffer->lpVtbl->Unlock(TerrainRender_ptVertexBuffer);
    Direct3D_tState.aptStreamData[1] = nullptr;
    Direct3D_tState.anStride[1] = 4;
    Direct3D_ptDevice->lpVtbl->SetStreamSource(Direct3D_ptDevice, 1u, nullptr, 4u);
    TerrainRender_SetBlendMode(a1->eBlendMode);
    v10 = a1->iMaterial;
    igi2_frame.avScale[0] = TerrainRender_ptContext->atLightmapOffset[v10].vX;
    v11 = TerrainRender_ptContext->atLightmapOffset[v10].vY;
    igi2_frame.avScale[2] = 0.0;
    igi2_frame.avScale[1] = v11;
    igi2_frame.avScale[3] = 0.0;
    igi2_frame.avOffset[0] = TerrainRender_ptContext->atLightmapScale[v10].vX;
    igi2_frame.avOffset[1] = TerrainRender_ptContext->atLightmapScale[v10].vY;
    igi2_frame.avOffset[2] = 0.0;
    igi2_frame.avOffset[3] = 1.0;
    Direct3D_ptDevice->lpVtbl->SetVertexShaderConstant(Direct3D_ptDevice, 11u, igi2_frame.avScale, 1u);
    Direct3D_ptDevice->lpVtbl->SetVertexShaderConstant(Direct3D_ptDevice, 12u, igi2_frame.avOffset, 1u);
    Direct3D_SetTexture(0, v9->ptDirect3DBaseTexture);
    v8 = TerrainRender_nLightmapVertexShader;
  }
  else
  {
    iMaterial = a1->iMaterial;
    v3 = TerrainRender_ptContext->aptTerrainMaterial[iMaterial];
    if ( !v3 )
    {
      iLightmap = a1->iLightmap;
LABEL_6:
      v5 = iLightmap + 10 * iMaterial;
      v6 = TerrainRender_tRenderChunkPool;
      TerrainRender_aaptRenderChunk[0][v5][eBlendMode] = nullptr;
      return QObjectVector_RemoveElement(v6, *(_DWORD *)((char *)a1 + v6->nElementSize - 4));
    }
    TerrainRender_ptIndexBuffer->lpVtbl->Unlock(TerrainRender_ptIndexBuffer);
    TerrainRender_ptVertexBuffer->lpVtbl->Unlock(TerrainRender_ptVertexBuffer);
    TerrainRender_UnlockMaterialVertexBuffers(a1);
    Direct3D_SetStreamSource(
      1u,
      TerrainRender_aptMaterialVertexBuffer[TerrainRender_ptContext->aiBuffer[a1->iMaterial]],
      4u);
    TerrainRender_SetBlendMode(a1->eBlendMode);
    TerrainRender_SetMaterialTextures(v3);
    v8 = TerrainRender_anVertexShader[v3->eMappingStyle];
  }
  Direct3D_tState.nHandle = v8;
  Direct3D_ptDevice->lpVtbl->SetVertexShader(Direct3D_ptDevice, v8);
  if ( TerrainRender_ptVertexShaderFunction )
  {
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FILLMODE, 2u);
    Direct3D_DrawIndexedPrimitive(
      D3DPT_TRIANGLELIST,
      a1->iMinVertex,
      a1->iMaxVertex - a1->iMinVertex + 1,
      a1->iStartIndex,
      a1->nNumIndices / 3);
    goto LABEL_19;
  }
  Direct3D_DrawIndexedPrimitive(
    D3DPT_TRIANGLELIST,
    a1->iMinVertex,
    a1->iMaxVertex - a1->iMinVertex + 1,
    a1->iStartIndex,
    a1->nNumIndices / 3);
LABEL_20:
  if ( TerrainRender_ptVertexBuffer->lpVtbl->Lock(
         TerrainRender_ptVertexBuffer,
         0,
         0,
         (unsigned __int8 **)&TerrainRender_ptLockedVertex,
         4096u) )
  {
    LDebug_Error("Lost vertexbuffer");
    goto LABEL_22;
  }
  if ( TerrainRender_ptIndexBuffer->lpVtbl->Lock(
         TerrainRender_ptIndexBuffer,
         0,
         0,
         (unsigned __int8 **)&TerrainRender_piLockedIndex,
         4096u) )
  {
    TerrainRender_ptVertexBuffer->lpVtbl->Unlock(TerrainRender_ptVertexBuffer);
    LDebug_Error("Lost indexbuffer");
LABEL_22:
    abort();
  }
LABEL_25:
  v16 = TerrainRender_tRenderChunkPool;
  TerrainRender_aaptRenderChunk[a1->iMaterial][a1->iLightmap][a1->eBlendMode] = nullptr;
  QObjectVector_RemoveElement(v16, *(_DWORD *)((char *)a1 + v16->nElementSize - 4));
  return (struct QObjectVector_s *)++TerrainRender_nNumChunksDrawn;
}

// source: e/3/pc/pc_terrainrender.c:1766  [size]
void __cdecl TerrainRender_DrawRenderChunk(struct TerrainRenderChunk_t *ptRenderChunk)
{
  enum TerrainRenderBlendMode_e v1; // ebx
  struct QObjectVector_s *v2; // ecx
  int i; // edi

  v1 = TERRAINRENDER_BLENDMODE_BLACK;
  if ( ptRenderChunk->eBlendMode > TERRAINRENDER_BLENDMODE_BLACK )
  {
    v2 = TerrainRender_tRenderChunkPool;
    do
    {
      for ( i = v2->nAllocated - 1; i >= 0; --i )
      {
        if ( *((_DWORD *)v2->papxElement[i] + 2) == v1 )
        {
          TerrainRender_DrawRenderChunk((struct TerrainRenderChunk_t *)v2->papxElement[i]);
          v2 = TerrainRender_tRenderChunkPool;
        }
      }
      ++v1;
    }
    while ( v1 < ptRenderChunk->eBlendMode );
  }
  TerrainRender_DrawRenderChunk_(ptRenderChunk);
}

// source: e/3/pc/pc_terrainrender.c:1803  [size]
struct TerrainRenderChunk_t *__cdecl TerrainRender_AllocateRenderChunk(
        unsigned __int8 iMaterial,
        unsigned __int8 iLightmap,
        enum TerrainRenderBlendMode_e eBlendMode)
{
  struct QObjectVector_s *v3; // ecx
  int v4; // ebp
  void **papxElement; // ecx
  struct TerrainRenderChunk_t *v6; // edi
  int v7; // esi
  unsigned int *p_nAllocated; // esi
  struct QObjectVector_s *v9; // edi
  struct TerrainRenderChunk_t *result; // eax

  v3 = TerrainRender_tRenderChunkPool;
  v4 = 50;
  if ( TerrainRender_tRenderChunkPool->nAllocated == 50 )
  {
    papxElement = TerrainRender_tRenderChunkPool->papxElement;
    v6 = nullptr;
    v7 = 0;
    do
    {
      if ( (int)(*((_DWORD *)*papxElement + 1)) > v7 )
      {
        v7 = *((_DWORD *)*papxElement + 1);
        v6 = (struct TerrainRenderChunk_t *)*papxElement;
      }
      ++papxElement;
      --v4;
    }
    while ( v4 );
    TerrainRender_DrawRenderChunk(v6);
    v3 = TerrainRender_tRenderChunkPool;
  }
  p_nAllocated = &v3->nAllocated;
  v9 = v3;
  if ( v3->nAllocated == v3->nSize )
  {
    QObjectVector_Realloc(v3, v3->nReallocSize);
    v3 = TerrainRender_tRenderChunkPool;
  }
  result = (struct TerrainRenderChunk_t *)v9->papxElement[(*p_nAllocated)++];
  result->iStartIndex = 10000 * *(_DWORD *)((char *)result + v3->nElementSize - 4);
  result->iMaterial = iMaterial;
  result->iLightmap = iLightmap;
  result->nNumIndices = 0;
  result->iMaxVertex = 0;
  result->eBlendMode = eBlendMode;
  result->iMinVertex = -1;
  TerrainRender_aaptRenderChunk[iMaterial][iLightmap][eBlendMode] = result;
  return result;
}

// source: e/3/pc/pc_terrainrender.c:1860  [size~]
void __cdecl TerrainRender_DrawFace(
        unsigned __int16 iVertex0,
        unsigned __int16 iVertex1,
        unsigned __int16 iVertex2,
        int isCull)
{
  int v4; // eax
  int v5; // ecx
  enum TerrainRenderBlendMode_e v6; // ebx
  struct TerrainRenderChunk_t *RenderChunk; // eax
  int nNumIndices; // ecx
  int *p_nNumIndices; // edx
  unsigned __int16 *v10; // ecx
  int v11; // edx
  int iStartIndex; // ebx
  unsigned __int8 v13; // cl
  struct TerrainRenderChunk_t *v14; // eax
  int v15; // edx
  unsigned __int16 *v16; // ecx
  unsigned __int16 v17; // cx
  unsigned __int16 v18; // cx
  int v19; // ecx
  int v20; // edx
  unsigned __int16 *v21; // ecx
  unsigned __int16 iMinVertex; // cx
  unsigned __int16 iMaxVertex; // cx
  int i; // [esp+10h] [ebp-10h]

  v4 = iVertex0;
  v5 = iVertex1;
  v6 = TERRAINRENDER_BLENDMODE_OPAQUE;
  if ( TerrainRender_ptContext->isDrawBlack )
  {
    if ( ((unsigned __int8)(TerrainRender_atManualVertex[iVertex1].bScreenOutcode
                          & TerrainRender_atManualVertex[iVertex2].bScreenOutcode)
        & TerrainRender_atManualVertex[iVertex0].bScreenOutcode) != 0 )
      return;
    RenderChunk = TerrainRender_aaptRenderChunk[0][0][0];
    if ( TerrainRender_aaptRenderChunk[0][0][0] )
    {
      nNumIndices = TerrainRender_aaptRenderChunk[0][0][0]->nNumIndices;
      p_nNumIndices = &TerrainRender_aaptRenderChunk[0][0][0]->nNumIndices;
      if ( nNumIndices <= 9997 )
      {
        v10 = &TerrainRender_piLockedIndex[nNumIndices + TerrainRender_aaptRenderChunk[0][0][0]->iStartIndex];
        *v10 = iVertex0;
        v10[1] = iVertex1;
        v10[2] = iVertex2;
        *p_nNumIndices += 3;
LABEL_35:
        iMinVertex = RenderChunk->iMinVertex;
        if ( iMinVertex >= iVertex0 )
          iMinVertex = iVertex0;
        RenderChunk->iMinVertex = iMinVertex;
        if ( iMinVertex >= iVertex1 )
          iMinVertex = iVertex1;
        RenderChunk->iMinVertex = iMinVertex;
        if ( iMinVertex >= iVertex2 )
          iMinVertex = iVertex2;
        RenderChunk->iMinVertex = iMinVertex;
        iMaxVertex = RenderChunk->iMaxVertex;
        if ( iMaxVertex <= iVertex0 )
          iMaxVertex = iVertex0;
        RenderChunk->iMaxVertex = iMaxVertex;
        if ( iMaxVertex <= iVertex1 )
          iMaxVertex = iVertex1;
        RenderChunk->iMaxVertex = iMaxVertex;
        if ( iMaxVertex <= iVertex2 )
          iMaxVertex = iVertex2;
        RenderChunk->iMaxVertex = iMaxVertex;
        return;
      }
    }
    RenderChunk = TerrainRender_AllocateRenderChunk(0, 0, TERRAINRENDER_BLENDMODE_BLACK);
    v11 = RenderChunk->nNumIndices;
    iStartIndex = RenderChunk->iStartIndex;
    goto LABEL_33;
  }
  for ( i = 0; i < TerrainRender_ptContext->nNumMaterials; v4 = iVertex0 )
  {
    if ( ((TerrainRender_atManualVertex[v4].bMaterialsEnabled
         | TerrainRender_atManualVertex[iVertex2].bMaterialsEnabled
         | TerrainRender_atManualVertex[v5].bMaterialsEnabled)
        & (1 << i)) != 0 )
    {
      if ( ((unsigned __int8)(TerrainRender_atManualVertex[iVertex1].bScreenOutcode
                            & TerrainRender_atManualVertex[iVertex2].bScreenOutcode)
          & TerrainRender_atManualVertex[iVertex0].bScreenOutcode) == 0 )
      {
        v13 = TerrainRender_ptContext->aiMaterial[i];
        v14 = TerrainRender_aaptRenderChunk[v13][0][v6];
        if ( !v14 || (v15 = v14->nNumIndices, v15 > 9997) )
        {
          v14 = TerrainRender_AllocateRenderChunk(v13, 0, v6);
          v15 = v14->nNumIndices;
        }
        v16 = &TerrainRender_piLockedIndex[v15 + v14->iStartIndex];
        v16[2] = iVertex2;
        v16[1] = iVertex1;
        *v16 = iVertex0;
        v14->nNumIndices += 3;
        v17 = v14->iMinVertex;
        if ( v17 >= iVertex0 )
          v17 = iVertex0;
        v14->iMinVertex = v17;
        if ( v17 >= iVertex1 )
          v17 = iVertex1;
        v14->iMinVertex = v17;
        if ( v17 >= iVertex2 )
          v17 = iVertex2;
        v14->iMinVertex = v17;
        v18 = v14->iMaxVertex;
        if ( v18 <= iVertex0 )
          v18 = iVertex0;
        v14->iMaxVertex = v18;
        if ( v18 <= iVertex1 )
          v18 = iVertex1;
        v14->iMaxVertex = v18;
        if ( v18 <= iVertex2 )
          v18 = iVertex2;
        v14->iMaxVertex = v18;
      }
      v6 = TERRAINRENDER_BLENDMODE_ADDITIVE;
    }
    v5 = iVertex1;
    ++i;
  }
  if ( ((unsigned __int8)(TerrainRender_atManualVertex[v5].bScreenOutcode
                        & TerrainRender_atManualVertex[iVertex2].bScreenOutcode)
      & TerrainRender_atManualVertex[v4].bScreenOutcode) == 0 )
  {
    RenderChunk = TerrainRender_aaptRenderChunk[TerrainRender_iTerrainMap][0][3];
    if ( RenderChunk )
    {
      v19 = RenderChunk->nNumIndices;
      if ( v19 <= 9997 )
      {
        v20 = v19 + RenderChunk->iStartIndex;
LABEL_34:
        v21 = &TerrainRender_piLockedIndex[v20];
        v21[2] = iVertex2;
        v21[1] = iVertex1;
        *v21 = iVertex0;
        RenderChunk->nNumIndices += 3;
        goto LABEL_35;
      }
    }
    RenderChunk = TerrainRender_AllocateRenderChunk(
                    TerrainRender_iTerrainMap,
                    0,
                    TERRAINRENDER_BLENDMODE_MULTIPLICATIVE);
    v11 = RenderChunk->iStartIndex;
    iStartIndex = RenderChunk->nNumIndices;
LABEL_33:
    v20 = iStartIndex + v11;
    goto LABEL_34;
  }
}

// source: e/3/pc/pc_terrainrender.c:2049  [size]
void __cdecl TerrainRender_SetupClippingPlanes(struct real32x3_t *ptDisplacement)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v10; };
    struct { char igi2_o1[4]; float v11; };
    struct { char igi2_o2[8]; float v12; };
    struct { char igi2_o3[12]; float v13; };
    struct { char igi2_o4[16]; float vFOVY; };
    struct { char igi2_o5[20]; float vFOVX; };
    struct { char igi2_o6[24]; float v16; };
    struct { char igi2_o7[28]; float v17; };
    struct { char igi2_o8[32]; float v18; };
    struct { char igi2_o9[32]; float v19; };
    struct { char igi2_o10[32]; float v20; };
    struct { char igi2_o11[60]; struct real32x9_t Real32x9_Invert_tTemp; };
    char igi2_extent[100];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct DrawLightmapContext_t *v1; // ebp
  float v2; // ecx
  float v3; // edx
  double v4; // st7
  long double v5; // st4
  double v6; // st7
  double v7; // st6
  double v8; // st6
  double v9; // st6
  struct ClippingPlane_s struct_clippingplane_s; // 0:^34.24
  struct ClippingPlane_s struct_clippingplane_sa; // 0:^34.24

  v1 = Terrain_ptDrawLightmapContext;
  if ( Terrain_ptDrawLightmapContext )
  {
    Real32x9_InvertSafe(&g_ptDest_0, &Terrain_ptDrawLightmapContext->tOrientation);
    igi2_frame.Real32x9_Invert_tTemp.tX.vX = g_ptDest_0.tX.vX;
    igi2_frame.Real32x9_Invert_tTemp.tX.vY = g_ptDest_0.tY.vX;
    igi2_frame.Real32x9_Invert_tTemp.tX.vZ = g_ptDest_0.tZ.vX;
    igi2_frame.Real32x9_Invert_tTemp.tY.vX = g_ptDest_0.tX.vY;
    igi2_frame.Real32x9_Invert_tTemp.tY.vY = g_ptDest_0.tY.vY;
    igi2_frame.Real32x9_Invert_tTemp.tY.vZ = g_ptDest_0.tZ.vY;
    igi2_frame.Real32x9_Invert_tTemp.tZ.vX = g_ptDest_0.tX.vZ;
    igi2_frame.Real32x9_Invert_tTemp.tZ.vY = g_ptDest_0.tY.vZ;
    igi2_frame.Real32x9_Invert_tTemp.tZ.vZ = g_ptDest_0.tZ.vZ;
    igi2_frame.Real32x9_Invert_tTemp.nOps = g_ptDest_0.nOps;
    qmemcpy(&g_ptDest_0, &igi2_frame.Real32x9_Invert_tTemp, sizeof(g_ptDest_0));
    v2 = v1->vFOVX;
    v3 = v2;
  }
  else
  {
    Real32x9_InvertSafe(&g_ptDest_0, &TransContext_tActiveTransContext.tMatrix);
    igi2_frame.Real32x9_Invert_tTemp.tX.vX = g_ptDest_0.tX.vX;
    igi2_frame.Real32x9_Invert_tTemp.tX.vY = g_ptDest_0.tY.vX;
    igi2_frame.Real32x9_Invert_tTemp.tX.vZ = g_ptDest_0.tZ.vX;
    igi2_frame.Real32x9_Invert_tTemp.tY.vX = g_ptDest_0.tX.vY;
    igi2_frame.Real32x9_Invert_tTemp.tY.vY = g_ptDest_0.tY.vY;
    igi2_frame.Real32x9_Invert_tTemp.tY.vZ = g_ptDest_0.tZ.vY;
    igi2_frame.Real32x9_Invert_tTemp.tZ.vX = g_ptDest_0.tX.vZ;
    igi2_frame.Real32x9_Invert_tTemp.tZ.vY = g_ptDest_0.tY.vZ;
    igi2_frame.Real32x9_Invert_tTemp.tZ.vZ = g_ptDest_0.tZ.vZ;
    v3 = TransContext_tActiveTransContext.vFOVY;
    igi2_frame.Real32x9_Invert_tTemp.nOps = g_ptDest_0.nOps;
    qmemcpy(&g_ptDest_0, &igi2_frame.Real32x9_Invert_tTemp, sizeof(g_ptDest_0));
    v2 = TransContext_tActiveTransContext.vFOVX;
  }
  if ( Clipping_tClipData.tClipFrustumList.nNumClipWindows <= 0 || v1 )
  {
    TerrainRender_nActiveClipWindows = 1;
    TerrainRender_atClippingPlanes[1].tPos.vX = 0.0;
    TerrainRender_atClippingPlanes[1].tPos.vY = 0.0;
    TerrainRender_atClippingPlanes[1].tPos.vZ = 0.0;
    TerrainRender_atClippingPlanes[1].tNormal.vX = 0.0;
    TerrainRender_atClippingPlanes[2].tPos.vX = 0.0;
    TerrainRender_atClippingPlanes[2].tPos.vY = 0.0;
    TerrainRender_atClippingPlanes[2].tPos.vZ = 0.0;
    TerrainRender_atClippingPlanes[2].tNormal.vY = 0.0;
    TerrainRender_atClippingPlanes[3].tPos.vX = 0.0;
    TerrainRender_atClippingPlanes[3].tPos.vY = 0.0;
    TerrainRender_atClippingPlanes[3].tPos.vZ = 0.0;
    TerrainRender_atClippingPlanes[3].tNormal.vX = 0.0;
    igi2_frame.v18 = sqrt(v2 * v2 + 1.0);
    v4 = 1.0 / igi2_frame.v18;
    TerrainRender_atClippingPlanes[0].tNormal.vZ = -1.0 / igi2_frame.v18 * v2;
    TerrainRender_atClippingPlanes[1].tNormal.vY = 1.0 / sqrt(v3 * v2 + 1.0);
    v5 = sqrt(v3 * v3 + 1.0);
    igi2_frame.v19 = -1.0 / v5 * v3;
    TerrainRender_atClippingPlanes[1].tNormal.vZ = igi2_frame.v19;
    TerrainRender_atClippingPlanes[3].tNormal.vZ = igi2_frame.v19;
    TerrainRender_atClippingPlanes[2].tNormal.vX = v4;
    TerrainRender_atClippingPlanes[2].tNormal.vZ = TerrainRender_atClippingPlanes[0].tNormal.vZ;
    TerrainRender_atClippingPlanes[3].tNormal.vY = -1.0 / v5;
    v6 = -1.0 * v4;
    igi2_frame.v16 = g_ptDest_0.tX.vZ * 0.0;
    igi2_frame.v10 = g_ptDest_0.tX.vY * 0.0;
    v7 = g_ptDest_0.tX.vX * 0.0;
    igi2_frame.v13 = v7;
    struct_clippingplane_sa.tPos.vX = v7 + igi2_frame.v10 + igi2_frame.v16;
    igi2_frame.v17 = g_ptDest_0.tY.vZ * 0.0;
    igi2_frame.v11 = g_ptDest_0.tY.vY * 0.0;
    v8 = g_ptDest_0.tY.vX * 0.0;
    igi2_frame.vFOVY = v8;
    struct_clippingplane_sa.tPos.vY = v8 + igi2_frame.v11 + igi2_frame.v17;
    igi2_frame.v20 = g_ptDest_0.tZ.vZ * 0.0;
    igi2_frame.v12 = g_ptDest_0.tZ.vY * 0.0;
    v9 = g_ptDest_0.tZ.vX * 0.0;
    igi2_frame.vFOVX = v9;
    struct_clippingplane_sa.tPos.vZ = v9 + igi2_frame.v12 + igi2_frame.v20;
    struct_clippingplane_sa.tNormal.vX = TerrainRender_atClippingPlanes[0].tNormal.vZ * g_ptDest_0.tX.vZ
                                       + v6 * g_ptDest_0.tX.vX
                                       + igi2_frame.v10;
    struct_clippingplane_sa.tNormal.vY = TerrainRender_atClippingPlanes[0].tNormal.vZ * g_ptDest_0.tY.vZ
                                       + v6 * g_ptDest_0.tY.vX
                                       + igi2_frame.v11;
    struct_clippingplane_sa.tNormal.vZ = TerrainRender_atClippingPlanes[0].tNormal.vZ * g_ptDest_0.tZ.vZ
                                       + v6 * g_ptDest_0.tZ.vX
                                       + igi2_frame.v12;
    TerrainRender_atClippingPlanes[0] = struct_clippingplane_sa;
    TerrainRender_atClippingPlanes[0].tPos.vX = struct_clippingplane_sa.tPos.vX - ptDisplacement->vX;
    TerrainRender_atClippingPlanes[0].tPos.vY = struct_clippingplane_sa.tPos.vY - ptDisplacement->vY;
    TerrainRender_atClippingPlanes[0].tPos.vZ = struct_clippingplane_sa.tPos.vZ - ptDisplacement->vZ;
    struct_clippingplane_sa.tPos.vX = igi2_frame.v13 + igi2_frame.v10 + igi2_frame.v16;
    struct_clippingplane_sa.tPos.vY = igi2_frame.vFOVY + igi2_frame.v11 + igi2_frame.v17;
    struct_clippingplane_sa.tPos.vZ = igi2_frame.vFOVX + igi2_frame.v12 + igi2_frame.v20;
    struct_clippingplane_sa.tNormal.vX = TerrainRender_atClippingPlanes[1].tNormal.vZ * g_ptDest_0.tX.vZ
                                       + TerrainRender_atClippingPlanes[1].tNormal.vY * g_ptDest_0.tX.vY
                                       + igi2_frame.v13;
    struct_clippingplane_sa.tNormal.vY = TerrainRender_atClippingPlanes[1].tNormal.vZ * g_ptDest_0.tY.vZ
                                       + TerrainRender_atClippingPlanes[1].tNormal.vY * g_ptDest_0.tY.vY
                                       + igi2_frame.vFOVY;
    struct_clippingplane_sa.tNormal.vZ = TerrainRender_atClippingPlanes[1].tNormal.vZ * g_ptDest_0.tZ.vZ
                                       + TerrainRender_atClippingPlanes[1].tNormal.vY * g_ptDest_0.tZ.vY
                                       + igi2_frame.vFOVX;
    TerrainRender_atClippingPlanes[1] = struct_clippingplane_sa;
    TerrainRender_atClippingPlanes[1].tPos.vX = struct_clippingplane_sa.tPos.vX - ptDisplacement->vX;
    TerrainRender_atClippingPlanes[1].tPos.vY = struct_clippingplane_sa.tPos.vY - ptDisplacement->vY;
    TerrainRender_atClippingPlanes[1].tPos.vZ = struct_clippingplane_sa.tPos.vZ - ptDisplacement->vZ;
    struct_clippingplane_sa.tNormal.vX = TerrainRender_atClippingPlanes[2].tNormal.vZ * g_ptDest_0.tX.vZ
                                       + TerrainRender_atClippingPlanes[2].tNormal.vX * g_ptDest_0.tX.vX
                                       + igi2_frame.v10;
    struct_clippingplane_sa.tNormal.vY = TerrainRender_atClippingPlanes[2].tNormal.vZ * g_ptDest_0.tY.vZ
                                       + TerrainRender_atClippingPlanes[2].tNormal.vX * g_ptDest_0.tY.vX
                                       + igi2_frame.v11;
    struct_clippingplane_sa.tNormal.vZ = TerrainRender_atClippingPlanes[2].tNormal.vZ * g_ptDest_0.tZ.vZ
                                       + TerrainRender_atClippingPlanes[2].tNormal.vX * g_ptDest_0.tZ.vX
                                       + igi2_frame.v12;
    TerrainRender_atClippingPlanes[2] = struct_clippingplane_sa;
    TerrainRender_atClippingPlanes[2].tPos.vX = struct_clippingplane_sa.tPos.vX - ptDisplacement->vX;
    TerrainRender_atClippingPlanes[2].tPos.vY = struct_clippingplane_sa.tPos.vY - ptDisplacement->vY;
    TerrainRender_atClippingPlanes[2].tPos.vZ = struct_clippingplane_sa.tPos.vZ - ptDisplacement->vZ;
    struct_clippingplane_sa.tNormal.vX = TerrainRender_atClippingPlanes[3].tNormal.vZ * g_ptDest_0.tX.vZ
                                       + TerrainRender_atClippingPlanes[3].tNormal.vY * g_ptDest_0.tX.vY
                                       + igi2_frame.v13;
    struct_clippingplane_sa.tNormal.vY = TerrainRender_atClippingPlanes[3].tNormal.vZ * g_ptDest_0.tY.vZ
                                       + TerrainRender_atClippingPlanes[3].tNormal.vY * g_ptDest_0.tY.vY
                                       + igi2_frame.vFOVY;
    struct_clippingplane_sa.tNormal.vZ = TerrainRender_atClippingPlanes[3].tNormal.vZ * g_ptDest_0.tZ.vZ
                                       + TerrainRender_atClippingPlanes[3].tNormal.vY * g_ptDest_0.tZ.vY
                                       + igi2_frame.vFOVX;
    TerrainRender_atClippingPlanes[3] = struct_clippingplane_sa;
    TerrainRender_atClippingPlanes[3].tPos.vX = struct_clippingplane_sa.tPos.vX - ptDisplacement->vX;
    TerrainRender_atClippingPlanes[3].tPos.vY = struct_clippingplane_sa.tPos.vY - ptDisplacement->vY;
    TerrainRender_atClippingPlanes[3].tPos.vZ = struct_clippingplane_sa.tPos.vZ - ptDisplacement->vZ;
  }
  else
  {
    TerrainRender_nActiveClipWindows = 1;
    struct_clippingplane_s.tPos.vX = Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[0].tPos.vZ
                                   * g_ptDest_0.tX.vZ
                                   + Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[0].tPos.vY
                                   * g_ptDest_0.tX.vY
                                   + Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[0].tPos.vX
                                   * g_ptDest_0.tX.vX;
    struct_clippingplane_s.tPos.vY = Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[0].tPos.vZ
                                   * g_ptDest_0.tY.vZ
                                   + Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[0].tPos.vY
                                   * g_ptDest_0.tY.vY
                                   + Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[0].tPos.vX
                                   * g_ptDest_0.tY.vX;
    struct_clippingplane_s.tPos.vZ = Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[0].tPos.vZ
                                   * g_ptDest_0.tZ.vZ
                                   + Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[0].tPos.vY
                                   * g_ptDest_0.tZ.vY
                                   + Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[0].tPos.vX
                                   * g_ptDest_0.tZ.vX;
    struct_clippingplane_s.tNormal.vX = Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[0].tNormal.vZ
                                      * g_ptDest_0.tX.vZ
                                      + Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[0].tNormal.vY
                                      * g_ptDest_0.tX.vY
                                      + Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[0].tNormal.vX
                                      * g_ptDest_0.tX.vX;
    struct_clippingplane_s.tNormal.vY = Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[0].tNormal.vZ
                                      * g_ptDest_0.tY.vZ
                                      + Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[0].tNormal.vY
                                      * g_ptDest_0.tY.vY
                                      + Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[0].tNormal.vX
                                      * g_ptDest_0.tY.vX;
    struct_clippingplane_s.tNormal.vZ = Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[0].tNormal.vZ
                                      * g_ptDest_0.tZ.vZ
                                      + Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[0].tNormal.vY
                                      * g_ptDest_0.tZ.vY
                                      + Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[0].tNormal.vX
                                      * g_ptDest_0.tZ.vX;
    TerrainRender_atClippingPlanes[0] = struct_clippingplane_s;
    TerrainRender_atClippingPlanes[0].tPos.vX = Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[0].tPos.vX
                                              - ptDisplacement->vX;
    TerrainRender_atClippingPlanes[0].tPos.vY = Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[0].tPos.vY
                                              - ptDisplacement->vY;
    TerrainRender_atClippingPlanes[0].tPos.vZ = Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[0].tPos.vZ
                                              - ptDisplacement->vZ;
    struct_clippingplane_s.tPos.vX = Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[1].tPos.vZ
                                   * g_ptDest_0.tX.vZ
                                   + Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[1].tPos.vY
                                   * g_ptDest_0.tX.vY
                                   + Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[1].tPos.vX
                                   * g_ptDest_0.tX.vX;
    struct_clippingplane_s.tPos.vY = Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[1].tPos.vZ
                                   * g_ptDest_0.tY.vZ
                                   + Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[1].tPos.vY
                                   * g_ptDest_0.tY.vY
                                   + Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[1].tPos.vX
                                   * g_ptDest_0.tY.vX;
    struct_clippingplane_s.tPos.vZ = Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[1].tPos.vZ
                                   * g_ptDest_0.tZ.vZ
                                   + Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[1].tPos.vY
                                   * g_ptDest_0.tZ.vY
                                   + Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[1].tPos.vX
                                   * g_ptDest_0.tZ.vX;
    struct_clippingplane_s.tNormal.vX = Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[1].tNormal.vZ
                                      * g_ptDest_0.tX.vZ
                                      + Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[1].tNormal.vY
                                      * g_ptDest_0.tX.vY
                                      + Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[1].tNormal.vX
                                      * g_ptDest_0.tX.vX;
    struct_clippingplane_s.tNormal.vY = Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[1].tNormal.vZ
                                      * g_ptDest_0.tY.vZ
                                      + Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[1].tNormal.vY
                                      * g_ptDest_0.tY.vY
                                      + Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[1].tNormal.vX
                                      * g_ptDest_0.tY.vX;
    struct_clippingplane_s.tNormal.vZ = Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[1].tNormal.vZ
                                      * g_ptDest_0.tZ.vZ
                                      + Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[1].tNormal.vY
                                      * g_ptDest_0.tZ.vY
                                      + Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[1].tNormal.vX
                                      * g_ptDest_0.tZ.vX;
    TerrainRender_atClippingPlanes[1] = struct_clippingplane_s;
    TerrainRender_atClippingPlanes[1].tPos.vX = Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[1].tPos.vX
                                              - ptDisplacement->vX;
    TerrainRender_atClippingPlanes[1].tPos.vY = Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[1].tPos.vY
                                              - ptDisplacement->vY;
    TerrainRender_atClippingPlanes[1].tPos.vZ = Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[1].tPos.vZ
                                              - ptDisplacement->vZ;
    struct_clippingplane_s.tPos.vX = Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[2].tPos.vZ
                                   * g_ptDest_0.tX.vZ
                                   + Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[2].tPos.vY
                                   * g_ptDest_0.tX.vY
                                   + Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[2].tPos.vX
                                   * g_ptDest_0.tX.vX;
    struct_clippingplane_s.tPos.vY = Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[2].tPos.vZ
                                   * g_ptDest_0.tY.vZ
                                   + Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[2].tPos.vY
                                   * g_ptDest_0.tY.vY
                                   + Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[2].tPos.vX
                                   * g_ptDest_0.tY.vX;
    struct_clippingplane_s.tPos.vZ = Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[2].tPos.vZ
                                   * g_ptDest_0.tZ.vZ
                                   + Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[2].tPos.vY
                                   * g_ptDest_0.tZ.vY
                                   + Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[2].tPos.vX
                                   * g_ptDest_0.tZ.vX;
    struct_clippingplane_s.tNormal.vX = Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[2].tNormal.vZ
                                      * g_ptDest_0.tX.vZ
                                      + Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[2].tNormal.vY
                                      * g_ptDest_0.tX.vY
                                      + Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[2].tNormal.vX
                                      * g_ptDest_0.tX.vX;
    struct_clippingplane_s.tNormal.vY = Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[2].tNormal.vZ
                                      * g_ptDest_0.tY.vZ
                                      + Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[2].tNormal.vY
                                      * g_ptDest_0.tY.vY
                                      + Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[2].tNormal.vX
                                      * g_ptDest_0.tY.vX;
    struct_clippingplane_s.tNormal.vZ = Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[2].tNormal.vZ
                                      * g_ptDest_0.tZ.vZ
                                      + Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[2].tNormal.vY
                                      * g_ptDest_0.tZ.vY
                                      + Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[2].tNormal.vX
                                      * g_ptDest_0.tZ.vX;
    TerrainRender_atClippingPlanes[2] = struct_clippingplane_s;
    TerrainRender_atClippingPlanes[2].tPos.vX = Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[2].tPos.vX
                                              - ptDisplacement->vX;
    TerrainRender_atClippingPlanes[2].tPos.vY = Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[2].tPos.vY
                                              - ptDisplacement->vY;
    TerrainRender_atClippingPlanes[2].tPos.vZ = Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[2].tPos.vZ
                                              - ptDisplacement->vZ;
    struct_clippingplane_s.tPos.vX = Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[3].tPos.vZ
                                   * g_ptDest_0.tX.vZ
                                   + Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[3].tPos.vY
                                   * g_ptDest_0.tX.vY
                                   + Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[3].tPos.vX
                                   * g_ptDest_0.tX.vX;
    struct_clippingplane_s.tPos.vY = Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[3].tPos.vZ
                                   * g_ptDest_0.tY.vZ
                                   + Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[3].tPos.vY
                                   * g_ptDest_0.tY.vY
                                   + Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[3].tPos.vX
                                   * g_ptDest_0.tY.vX;
    struct_clippingplane_s.tPos.vZ = Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[3].tPos.vZ
                                   * g_ptDest_0.tZ.vZ
                                   + Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[3].tPos.vY
                                   * g_ptDest_0.tZ.vY
                                   + Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[3].tPos.vX
                                   * g_ptDest_0.tZ.vX;
    struct_clippingplane_s.tNormal.vX = Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[3].tNormal.vZ
                                      * g_ptDest_0.tX.vZ
                                      + Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[3].tNormal.vY
                                      * g_ptDest_0.tX.vY
                                      + Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[3].tNormal.vX
                                      * g_ptDest_0.tX.vX;
    struct_clippingplane_s.tNormal.vY = Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[3].tNormal.vZ
                                      * g_ptDest_0.tY.vZ
                                      + Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[3].tNormal.vY
                                      * g_ptDest_0.tY.vY
                                      + Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[3].tNormal.vX
                                      * g_ptDest_0.tY.vX;
    struct_clippingplane_s.tNormal.vZ = Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[3].tNormal.vZ
                                      * g_ptDest_0.tZ.vZ
                                      + Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[3].tNormal.vY
                                      * g_ptDest_0.tZ.vY
                                      + Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[3].tNormal.vX
                                      * g_ptDest_0.tZ.vX;
    TerrainRender_atClippingPlanes[3] = struct_clippingplane_s;
    TerrainRender_atClippingPlanes[3].tPos.vX = Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[3].tPos.vX
                                              - ptDisplacement->vX;
    TerrainRender_atClippingPlanes[3].tPos.vY = Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[3].tPos.vY
                                              - ptDisplacement->vY;
    TerrainRender_atClippingPlanes[3].tPos.vZ = Clipping_tClipData.tClipFrustumList.atEnclosingFrustum[3].tPos.vZ
                                              - ptDisplacement->vZ;
  }
}

// source: e/3/pc/pc_terrainrender.c:2180  [size]
void __cdecl TerrainRender_SetVertexShaderConstants(
        struct TerrainContext_t *ptContext,
        struct real32x3_t *ptDisplacement)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vX; };
    struct { char igi2_o1[4]; float vY; };
    struct { char igi2_o2[8]; float vZ; };
    struct { char igi2_o3[12]; float v17; };
    struct { char igi2_o4[16]; struct real32x3_t tFrontColor; };
    struct { char igi2_o5[28]; int v19; };
    struct { char igi2_o6[32]; _DWORD v20[4]; };
    struct { char igi2_o7[48]; float v21[4]; };
    struct { char igi2_o8[64]; _DWORD v22[4]; };
    struct { char igi2_o9[80]; int v23[16]; };
    struct { char igi2_o10[144]; _DWORD v24[16]; };
    struct { char igi2_o11[208]; _BYTE v25[4]; };
    struct { char igi2_o12[212]; int v26[16]; };
    char igi2_extent[336];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v2; // st7
  double v3; // st7
  double v4; // st7
  struct real32x3_t *p_tFrontColor; // edx
  unsigned int v6; // esi
  struct TerrainMaterial_t **aptTerrainMaterial; // edi
  struct TerrainMaterial_t *v8; // eax
  double v9; // st7
  double v10; // st7
  unsigned int v11; // edi
  float *p_vY; // esi
  double v13; // st7

  *(float *)&igi2_frame.v22[3] = DrawTerrainMesh_vFogDensity * 1.4426950408889634;
  memset(igi2_frame.v24, 0, sizeof(igi2_frame.v24));
  *(float *)igi2_frame.v24 = Direct3D_vScale;
  *(float *)&igi2_frame.v24[10] = Direct3D_vScale;
  v2 = Direct3D_vScale * ptDisplacement->vX;
  igi2_frame.v20[0] = 0;
  *(float *)&igi2_frame.v24[12] = v2;
  igi2_frame.v20[1] = 1056964608;
  igi2_frame.v20[2] = 1065353216;
  v3 = Direct3D_vScale * ptDisplacement->vY;
  igi2_frame.v20[3] = 0x40000000;
  memset(igi2_frame.v22, 0, 12);
  *(float *)&igi2_frame.v24[13] = v3;
  *(float *)&igi2_frame.v24[5] = Direct3D_vScale;
  v4 = Direct3D_vScale * ptDisplacement->vZ;
  igi2_frame.v24[15] = 1065353216;
  *(float *)&igi2_frame.v24[14] = v4;
  Direct3D_ptDevice->lpVtbl->GetTransform(Direct3D_ptDevice, D3DTS_VIEW, (struct _D3DMATRIX *)igi2_frame.v25);
  Direct3D_ptDevice->lpVtbl->GetTransform(Direct3D_ptDevice, D3DTS_PROJECTION, (struct _D3DMATRIX *)&igi2_frame.v26[15]);
  D3DXMatrixMultiply((int)igi2_frame.v23, (int)igi2_frame.v24, (int)igi2_frame.v25);
  igi2_frame.v21[0] = *(float *)&igi2_frame.v23[2] * DrawTerrainMesh_vFogDensity;
  igi2_frame.v21[1] = *(float *)&igi2_frame.v23[6] * DrawTerrainMesh_vFogDensity;
  igi2_frame.v21[2] = *(float *)&igi2_frame.v23[10] * DrawTerrainMesh_vFogDensity;
  igi2_frame.v21[3] = *(float *)&igi2_frame.v23[14] * DrawTerrainMesh_vFogDensity;
  D3DXMatrixMultiply((int)igi2_frame.v23, (int)igi2_frame.v23, (int)&igi2_frame.v26[15]);
  D3DXMatrixTranspose((int)igi2_frame.v23, (int)igi2_frame.v23);
  qmemcpy(&TerrainRender_tMatrix, igi2_frame.v23, sizeof(TerrainRender_tMatrix));
  TerrainRender_SetupClippingPlanes(ptDisplacement);
  Direct3D_ptDevice->lpVtbl->SetVertexShaderConstant(Direct3D_ptDevice, 15u, igi2_frame.v22, 1u);
  igi2_frame.vX = *(float *)&igi2_frame.v23[3];
  igi2_frame.vZ = *(float *)&igi2_frame.v23[11];
  igi2_frame.v17 = *(float *)&igi2_frame.v23[15];
  igi2_frame.vY = *(float *)&igi2_frame.v23[7];
  Direct3D_ptDevice->lpVtbl->SetVertexShaderConstant(Direct3D_ptDevice, 14u, &igi2_frame.vX, 1u);
  Direct3D_ptDevice->lpVtbl->SetVertexShaderConstant(Direct3D_ptDevice, 0, igi2_frame.v23, 4u);
  Direct3D_ptDevice->lpVtbl->SetVertexShaderConstant(Direct3D_ptDevice, 4u, igi2_frame.v21, 1u);
  Direct3D_ptDevice->lpVtbl->SetVertexShaderConstant(Direct3D_ptDevice, 5u, igi2_frame.v20, 1u);
  if ( SkyDome_ptDirlight )
  {
    igi2_frame.vX = SkyDome_ptDirlight->tDir.vX;
    igi2_frame.vY = SkyDome_ptDirlight->tDir.vY;
    igi2_frame.vZ = SkyDome_ptDirlight->tDir.vZ;
    igi2_frame.v17 = 0.0;
    igi2_frame.tFrontColor = SkyDome_ptDirlight->tFrontColor;
    igi2_frame.v19 = 0;
    Direct3D_ptDevice->lpVtbl->SetVertexShaderConstant(Direct3D_ptDevice, 8u, &igi2_frame.vX, 1u);
    p_tFrontColor = &igi2_frame.tFrontColor;
  }
  else
  {
    igi2_frame.vX = 0.0;
    igi2_frame.vY = 0.0;
    igi2_frame.vZ = 0.0;
    igi2_frame.v17 = 0.0;
    Direct3D_ptDevice->lpVtbl->SetVertexShaderConstant(Direct3D_ptDevice, 8u, &igi2_frame.vX, 1u);
    p_tFrontColor = (struct real32x3_t *)&igi2_frame.vX;
  }
  Direct3D_ptDevice->lpVtbl->SetVertexShaderConstant(Direct3D_ptDevice, 9u, p_tFrontColor, 1u);
  igi2_frame.tFrontColor = Mesh3D_atAmbientColor[0];
  igi2_frame.v19 = 0;
  Direct3D_ptDevice->lpVtbl->SetVertexShaderConstant(Direct3D_ptDevice, 10u, &igi2_frame.tFrontColor, 1u);
  if ( ptContext->nNumMaterials > 0 )
  {
    v6 = 32;
    aptTerrainMaterial = ptContext->aptTerrainMaterial;
    do
    {
      v8 = *aptTerrainMaterial;
      if ( *aptTerrainMaterial )
      {
        v9 = 1.0 / (v8->atTexture[0].vScale * 4096.0);
        igi2_frame.vZ = 0.0;
        igi2_frame.tFrontColor.vZ = 0.0;
        igi2_frame.v17 = 1.0;
        igi2_frame.v19 = 1065353216;
        igi2_frame.tFrontColor.vX = v9 * ptContext->vWorldWidth;
        igi2_frame.tFrontColor.vY = v9 * ptContext->vWorldHeight;
        v10 = 1.0 / (v8->atTexture[1].vScale * 4096.0);
        igi2_frame.vX = v10 * ptContext->vWorldWidth;
        igi2_frame.vY = v10 * ptContext->vWorldHeight;
        Direct3D_ptDevice->lpVtbl->SetVertexShaderConstant(Direct3D_ptDevice, v6 - 16, &igi2_frame.tFrontColor, 1u);
        Direct3D_ptDevice->lpVtbl->SetVertexShaderConstant(Direct3D_ptDevice, v6, &igi2_frame.vX, 1u);
      }
      ++aptTerrainMaterial;
      ++v6;
    }
    while ( (signed int)(v6 - 32) < ptContext->nNumMaterials );
  }
  if ( ptContext->nNumTerrains > 0 )
  {
    v11 = 56;
    p_vY = &ptContext->atLightmapOffset[0].vY;
    do
    {
      v13 = *(p_vY - 1) / (ptContext->vWorldWidth * 4096.0);
      igi2_frame.vZ = 0.0;
      igi2_frame.tFrontColor.vZ = 0.0;
      igi2_frame.v17 = 1.0;
      igi2_frame.v19 = 1065353216;
      igi2_frame.tFrontColor.vX = v13;
      igi2_frame.tFrontColor.vY = *p_vY / (ptContext->vWorldHeight * 4096.0);
      igi2_frame.vX = p_vY[7] * ptContext->vWorldWidth;
      igi2_frame.vY = p_vY[8] * ptContext->vWorldHeight;
      Direct3D_ptDevice->lpVtbl->SetVertexShaderConstant(Direct3D_ptDevice, v11 - 8, &igi2_frame.tFrontColor, 1u);
      Direct3D_ptDevice->lpVtbl->SetVertexShaderConstant(Direct3D_ptDevice, v11, &igi2_frame.vX, 1u);
      p_vY += 2;
      ++v11;
    }
    while ( (signed int)(v11 - 56) < ptContext->nNumTerrains );
  }
}

// source: e/3/pc/pc_terrainrender.c:2320  [size~]
void __cdecl TerrainRender_DrawGlitchPolyRecursive(unsigned int iEdge, struct TerrainContext_t *ptContext)
{
  int v2; // esi
  int iSplitVertex; // ebx
  unsigned int v4; // ebp
  int v5; // edi
  float *v6; // eax
  float *v7; // ecx
  unsigned __int16 v8; // si
  int i; // edi
  unsigned int v10; // eax
  int v11; // esi
  float iVertex1; // [esp+0h] [ebp-18h]
  signed int iEdgea = *(signed int *)&iEdge; // [esp+1Ch] [ebp+4h] ARGSLOT

  v2 = TerrainRender_atEdge[iEdge].aiVertex[1];
  iSplitVertex = TerrainRender_atEdge[iEdge].iSplitVertex;
  v4 = 20 * iEdge + 134125256;
  v5 = TerrainRender_atEdge[iEdge].aiVertex[0];
  v6 = (float *)(32 * iSplitVertex);
  v6[33291312] = (TerrainRender_atManualVertex[v5].tPos.vX + TerrainRender_atManualVertex[v2].tPos.vX) * 0.5;
  v6[33291313] = (TerrainRender_atManualVertex[v5].tPos.vY + TerrainRender_atManualVertex[v2].tPos.vY) * 0.5;
  v7 = (float *)(32 * TerrainRender_atEdge[iEdge].iGlitchConnectVertex);
  v6[33291314] = (TerrainRender_atManualVertex[v5].tPos.vZ + TerrainRender_atManualVertex[v2].tPos.vZ) * 0.5;
  v6[33291312] = (v7[33291312] - v6[33291312]) * 0.009999999776482582 + v6[33291312];
  v6[33291313] = (v7[33291313] - v6[33291313]) * 0.009999999776482582 + v6[33291313];
  iEdgea = TerrainRender_atEdge[iEdge].nMorph;
  v6[33291314] = (v7[33291314] - v6[33291314]) * 0.009999999776482582 + v6[33291314];
  iVertex1 = (double)iEdgea * 1.5259021893143654e-05;
  TerrainRender_CalculateRenderVertex(iSplitVertex, v5, v2, iVertex1, ptContext);
  v8 = *(_WORD *)(v4 + 8);
  if ( (*(_BYTE *)(v4 + 19) & 0x10) != 0 )
    TerrainRender_DrawFace(v8, *(_WORD *)(v4 + 12), *(_WORD *)(v4 + 10), 0);
  else
    TerrainRender_DrawFace(v8, *(_WORD *)(v4 + 10), *(_WORD *)(v4 + 12), 0);
  for ( i = 0; i < 2; ++i )
  {
    v10 = *(_DWORD *)(v4 + 4 * i);
    v11 = 20 * v10 + 134125256;
    if ( TerrainRender_atEdge[v10].iSplitVertex != 0xFFFF )
      TerrainRender_DrawGlitchPolyRecursive(v10, ptContext);
    *(_BYTE *)(v11 + 19) |= *(_BYTE *)(v4 + 19) & 0x10 | 4;
  }
}

// source: e/3/pc/pc_terrainrender.c:2395  [size~]
enum bool __cdecl TerrainRender_IsSquareOutOfSight(
        int nSquareSize,
        unsigned int *aiVertices,
        int iTerrainMap,
        int iMipMap)
{
  int v5; // edi
  int v6; // eax
  unsigned int v7; // edx
  unsigned int v8; // eax
  struct TerrainMinMaxHeightMipMapData_s *v9; // edi
  int v10; // ebx
  unsigned int v11; // edx
  double vZ; // st7
  int v13; // ebx
  struct real32x2_t *v14; // eax
  int v15; // ebp
  double v16; // st7
  double v17; // st7
  double v18; // st7
  double v19; // st7
  double v20; // st6
  int v21; // edi
  double v22; // st6
  int v23; // ecx
  int v24; // ebx
  double v25; // st5
  int v26; // esi
  double v27; // st7
  double v28; // st6
  int v29; // esi
  int v30; // esi
  double v31; // st6
  int v32; // esi
  int v33; // esi
  int v34; // esi
  int v35; // esi
  float *p_vY; // ecx
  double v37; // st7
  double v38; // st5
  double v39; // st7
  int v40; // esi
  double v41; // st6
  int v42; // esi
  int v43; // esi
  double v44; // st6
  int v45; // esi
  int v46; // esi
  int v47; // esi
  int v48; // esi
  float *v49; // ecx
  double v50; // st7
  double v51; // st5
  double v52; // st7
  int v53; // esi
  double v54; // st6
  int v55; // esi
  int v56; // esi
  double v57; // st6
  int v58; // esi
  int v59; // esi
  int v60; // esi
  int v61; // esi
  struct TerrainContext_t *v63; // eax
  double v64; // st7
  double v65; // st7
  double v66; // st6
  double v67; // st6
  double v68; // st6
  float *v69; // ecx
  double v70; // st7
  double v71; // st5
  double v72; // st7
  int v73; // edx
  double v74; // st6
  int v75; // edx
  int v76; // edx
  double v77; // st6
  int v78; // edx
  int v79; // edx
  int v80; // edx
  int v81; // edx
  float vX; // [esp+10h] [ebp-54h]
  float v83; // [esp+10h] [ebp-54h]
  float vY; // [esp+14h] [ebp-50h]
  float v85; // [esp+18h] [ebp-4Ch]
  float v86; // [esp+18h] [ebp-4Ch]
  float v87; // [esp+18h] [ebp-4Ch]
  float v88; // [esp+1Ch] [ebp-48h]
  float v89; // [esp+1Ch] [ebp-48h]
  float v90; // [esp+1Ch] [ebp-48h]
  float v91; // [esp+1Ch] [ebp-48h]
  float v92; // [esp+20h] [ebp-44h]
  float v93; // [esp+20h] [ebp-44h]
  float v94; // [esp+20h] [ebp-44h]
  float v95; // [esp+20h] [ebp-44h]
  float v96; // [esp+24h] [ebp-40h]
  float v97; // [esp+24h] [ebp-40h]
  float v98; // [esp+24h] [ebp-40h]
  float v99; // [esp+24h] [ebp-40h]
  float v100; // [esp+28h] [ebp-3Ch]
  int v101; // [esp+2Ch] [ebp-38h]
  float v102; // [esp+2Ch] [ebp-38h]
  float v103; // [esp+30h] [ebp-34h]
  float v104; // [esp+34h] [ebp-30h]
  float v105; // [esp+38h] [ebp-2Ch]
  float v106; // [esp+3Ch] [ebp-28h]
  float v107; // [esp+40h] [ebp-24h]
  unsigned int v108; // [esp+44h] [ebp-20h]
  float v109; // [esp+44h] [ebp-20h]
  struct real32x2_t *v110; // [esp+48h] [ebp-1Ch]
  float v111; // [esp+4Ch] [ebp-18h]
  float v112; // [esp+4Ch] [ebp-18h]
  float v113; // [esp+4Ch] [ebp-18h]
  float v114; // [esp+50h] [ebp-14h]
  float v115; // [esp+50h] [ebp-14h]
  float v116; // [esp+54h] [ebp-10h]
  float v117; // [esp+54h] [ebp-10h]
  float v118; // [esp+54h] [ebp-10h]
  float v119; // [esp+54h] [ebp-10h]
  float v120; // [esp+54h] [ebp-10h]
  float v121; // [esp+54h] [ebp-10h]
  float v122; // [esp+54h] [ebp-10h]
  float v123; // [esp+54h] [ebp-10h]
  float v124; // [esp+54h] [ebp-10h]
  float v125; // [esp+54h] [ebp-10h]
  float v126; // [esp+54h] [ebp-10h]
  float v127; // [esp+54h] [ebp-10h]
  float v128; // [esp+58h] [ebp-Ch]
  float v129; // [esp+58h] [ebp-Ch]
  float v130; // [esp+58h] [ebp-Ch]
  float v131; // [esp+58h] [ebp-Ch]
  float v132; // [esp+58h] [ebp-Ch]
  float v133; // [esp+58h] [ebp-Ch]
  float v134; // [esp+58h] [ebp-Ch]
  float v135; // [esp+58h] [ebp-Ch]
  float v136; // [esp+58h] [ebp-Ch]
  float v137; // [esp+58h] [ebp-Ch]
  float v138; // [esp+58h] [ebp-Ch]
  float v139; // [esp+58h] [ebp-Ch]
  float v140; // [esp+58h] [ebp-Ch]
  float v141; // [esp+58h] [ebp-Ch]
  float v142; // [esp+58h] [ebp-Ch]
  float v143; // [esp+58h] [ebp-Ch]
  float v144; // [esp+58h] [ebp-Ch]
  float v145; // [esp+58h] [ebp-Ch]
  float v146; // [esp+58h] [ebp-Ch]
  float v147; // [esp+58h] [ebp-Ch]
  float v148; // [esp+58h] [ebp-Ch]
  float v149; // [esp+58h] [ebp-Ch]
  float v150; // [esp+58h] [ebp-Ch]
  float v151; // [esp+58h] [ebp-Ch]
  float v152; // [esp+58h] [ebp-Ch]
  float v153; // [esp+58h] [ebp-Ch]
  float v154; // [esp+58h] [ebp-Ch]
  float v155; // [esp+5Ch] [ebp-8h]
  float v156; // [esp+5Ch] [ebp-8h]
  float v157; // [esp+5Ch] [ebp-8h]

  v5 = iTerrainMap;
  v104 = TerrainRender_atManualVertex[aiVertices[1]].tPos.vX - TerrainRender_atManualVertex[*aiVertices].tPos.vX;
  v105 = TerrainRender_atManualVertex[aiVertices[3]].tPos.vY - TerrainRender_atManualVertex[*aiVertices].tPos.vY;
  _BitScanReverse((unsigned int *)&iTerrainMap, nSquareSize >> TerrainRender_ptContext->anSubmapShift[iTerrainMap]);
  v6 = TerrainRender_ptContext->aptMinMaxHeightMipMaps[v5]->nLevels - iTerrainMap - 1;
  v7 = nSquareSize >> TerrainRender_ptContext->anSubmapShift[0];
  if ( v6 <= 7 && v7 )
  {
    _BitScanReverse(&v8, v7);
    v9 = TerrainRender_ptContext->aptMinMaxHeightMipMaps[0];
    v10 = TerrainRender_ptContext->anSubmapShift[0];
    v108 = v9->nLevels - v8 - 1;
    v11 = 32 * *aiVertices;
    vZ = TerrainRender_atManualVertex[v11 / 0x20].tPos.vZ;
    v101 = (TerrainRender_ptContext->atMapSize[0].nX >> v8)
         * ((TerrainRender_atManualVertex[v11 / 0x20].tMapPos.nY - TerrainRender_ptContext->atSubmapPos[0].nY) >> v10 >> v8);
    v13 = (TerrainRender_atManualVertex[v11 / 0x20].tMapPos.nX - TerrainRender_ptContext->atSubmapPos[0].nX) >> v10 >> v8;
    v14 = v9->pptMinMaxHeightMipMap[v108];
    v15 = v13 + v101;
    vX = v14[v13 + v101].vX;
    v110 = &v14[v13 + v101];
    vY = v110->vY;
    if ( vZ >= vX )
    {
      if ( vZ > vY )
        vY = TerrainRender_atManualVertex[*aiVertices].tPos.vZ;
    }
    else
    {
      vX = TerrainRender_atManualVertex[*aiVertices].tPos.vZ;
    }
    v16 = TerrainRender_atManualVertex[aiVertices[1]].tPos.vZ;
    if ( v16 >= vX )
    {
      if ( v16 > vY )
        vY = TerrainRender_atManualVertex[aiVertices[1]].tPos.vZ;
    }
    else
    {
      vX = TerrainRender_atManualVertex[aiVertices[1]].tPos.vZ;
    }
    v17 = TerrainRender_atManualVertex[aiVertices[2]].tPos.vZ;
    if ( v17 >= vX )
    {
      if ( v17 > vY )
        vY = TerrainRender_atManualVertex[aiVertices[2]].tPos.vZ;
    }
    else
    {
      vX = TerrainRender_atManualVertex[aiVertices[2]].tPos.vZ;
    }
    v18 = TerrainRender_atManualVertex[aiVertices[3]].tPos.vZ;
    if ( v18 >= vX )
    {
      if ( v18 > vY )
        vY = TerrainRender_atManualVertex[aiVertices[3]].tPos.vZ;
    }
    else
    {
      vX = TerrainRender_atManualVertex[aiVertices[3]].tPos.vZ;
    }
    v19 = vY - vX;
    v20 = v104 * 0.0;
    v21 = LOBYTE(vX) & 1 | (2 * (LOBYTE(vY) & 1));
    v103 = v20;
    v22 = v20 + TerrainRender_atManualVertex[*aiVertices].tPos.vX;
    v24 = v21;
    v102 = v22;
    v25 = v105 * 0.0;
    v100 = v25;
    v106 = v19 * 0.0;
    v96 = v19 * 0.0 + vX;
    v128 = v22 - TerrainRender_atClippingPlanes[v21].tPos.vX;
    v26 = 2
        * ((v96 - TerrainRender_atClippingPlanes[v21].tPos.vZ) * TerrainRender_atClippingPlanes[v21].tNormal.vZ
         + v128 * TerrainRender_atClippingPlanes[v21].tNormal.vX
         + (v25 + TerrainRender_atManualVertex[*aiVertices].tPos.vY - TerrainRender_atClippingPlanes[v21].tPos.vY)
         * TerrainRender_atClippingPlanes[v21].tNormal.vY > 0.0);
    v92 = v103 + TerrainRender_atManualVertex[*aiVertices].tPos.vX;
    v114 = v100 + TerrainRender_atManualVertex[*aiVertices].tPos.vY;
    v107 = v19;
    v27 = v19 + vX;
    v23 = 24 * v21;
    if ( (v27 - *(float *)(v23 + 137445544)) * *(float *)(v23 + 137445556)
       + (v92 - *(float *)(v23 + 137445536)) * *(float *)(v23 + 137445548)
       + (v114 - *(float *)(v23 + 137445540)) * *(float *)(v23 + 137445552) > 0.0 )
      v26 |= 1u;
    v28 = v104 + *(float *)(v11 + 133165248);
    v29 = 2 * v26;
    v88 = v28;
    v129 = v28 - TerrainRender_atClippingPlanes[v21].tPos.vX;
    if ( (v96 - TerrainRender_atClippingPlanes[v21].tPos.vZ) * TerrainRender_atClippingPlanes[v21].tNormal.vZ
       + v129 * TerrainRender_atClippingPlanes[v21].tNormal.vX
       + (v100 + *(float *)(v11 + 133165252) - TerrainRender_atClippingPlanes[v21].tPos.vY)
       * TerrainRender_atClippingPlanes[v21].tNormal.vY > 0.0 )
      v29 |= 1u;
    v30 = 2 * v29;
    v31 = v104 + *(float *)(v11 + 133165248);
    v116 = v27;
    v130 = v31 - TerrainRender_atClippingPlanes[v21].tPos.vX;
    if ( (v116 - TerrainRender_atClippingPlanes[v21].tPos.vZ) * TerrainRender_atClippingPlanes[v21].tNormal.vZ
       + v130 * TerrainRender_atClippingPlanes[v21].tNormal.vX
       + (v100 + *(float *)(v11 + 133165252) - TerrainRender_atClippingPlanes[v21].tPos.vY)
       * TerrainRender_atClippingPlanes[v21].tNormal.vY > 0.0 )
      v30 |= 1u;
    v32 = 2 * v30;
    v131 = v102 - TerrainRender_atClippingPlanes[v21].tPos.vX;
    if ( (v96 - TerrainRender_atClippingPlanes[v21].tPos.vZ) * TerrainRender_atClippingPlanes[v21].tNormal.vZ
       + v131 * TerrainRender_atClippingPlanes[v21].tNormal.vX
       + (v105 + *(float *)(v11 + 133165252) - TerrainRender_atClippingPlanes[v21].tPos.vY)
       * TerrainRender_atClippingPlanes[v21].tNormal.vY > 0.0 )
      v32 |= 1u;
    v33 = 2 * v32;
    v117 = v27;
    v132 = v92 - TerrainRender_atClippingPlanes[v21].tPos.vX;
    if ( (v117 - TerrainRender_atClippingPlanes[v21].tPos.vZ) * TerrainRender_atClippingPlanes[v21].tNormal.vZ
       + v132 * TerrainRender_atClippingPlanes[v21].tNormal.vX
       + (v105 + *(float *)(v11 + 133165252) - TerrainRender_atClippingPlanes[v21].tPos.vY)
       * TerrainRender_atClippingPlanes[v21].tNormal.vY > 0.0 )
      v33 |= 1u;
    v34 = 2 * v33;
    v133 = v88 - TerrainRender_atClippingPlanes[v21].tPos.vX;
    if ( (v96 - TerrainRender_atClippingPlanes[v21].tPos.vZ) * TerrainRender_atClippingPlanes[v21].tNormal.vZ
       + v133 * TerrainRender_atClippingPlanes[v21].tNormal.vX
       + (v105 + *(float *)(v11 + 133165252) - TerrainRender_atClippingPlanes[v21].tPos.vY)
       * TerrainRender_atClippingPlanes[v21].tNormal.vY > 0.0 )
      v34 |= 1u;
    v35 = 2 * v34;
    v115 = v105 + *(float *)(v11 + 133165252);
    v118 = v27;
    if ( (v118 - TerrainRender_atClippingPlanes[v21].tPos.vZ) * TerrainRender_atClippingPlanes[v21].tNormal.vZ
       + (v31 - TerrainRender_atClippingPlanes[v21].tPos.vX) * TerrainRender_atClippingPlanes[v21].tNormal.vX
       + (v115 - TerrainRender_atClippingPlanes[v21].tPos.vY) * TerrainRender_atClippingPlanes[v21].tNormal.vY > 0.0 )
      v35 |= 1u;
    if ( v35 == 255 )
    {
LABEL_71:
      v63 = TerrainRender_ptContext;
      LODWORD(v110->vX) = LODWORD(vX) ^ ((unsigned __int8)v24 ^ LOBYTE(vX)) & 1;
      LODWORD(v63->aptMinMaxHeightMipMaps[0]->pptMinMaxHeightMipMap[v108][v15].vY) = LODWORD(vY)
                                                                                   ^ (LOBYTE(vY)
                                                                                    ^ (unsigned __int8)(v24 >> 1))
                                                                                   & 1;
      return true;
    }
    v24 = 0;
    if ( v21 > 0 )
    {
      p_vY = &TerrainRender_atClippingPlanes[0].tPos.vY;
      do
      {
        v37 = v103 + *(float *)(v11 + 133165248);
        v93 = v37;
        v38 = v100 + *(float *)(v11 + 133165252);
        v85 = v38;
        v89 = v106 + vX;
        v134 = v37 - *(p_vY - 1);
        v111 = v37;
        v39 = v107 + vX;
        v40 = 2 * ((v89 - p_vY[1]) * p_vY[4] + (v38 - *p_vY) * p_vY[3] + v134 * p_vY[2] > 0.0);
        if ( (v39 - p_vY[1]) * p_vY[4] + (v85 - *p_vY) * p_vY[3] + (v111 - *(p_vY - 1)) * p_vY[2] > 0.0 )
          v40 |= 1u;
        v41 = v104 + *(float *)(v11 + 133165248);
        v42 = 2 * v40;
        v97 = v41;
        v135 = v41 - *(p_vY - 1);
        if ( (v89 - p_vY[1]) * p_vY[4] + (v85 - *p_vY) * p_vY[3] + v135 * p_vY[2] > 0.0 )
          v42 |= 1u;
        v43 = 2 * v42;
        v119 = v39;
        v136 = v41 - *(p_vY - 1);
        if ( (v119 - p_vY[1]) * p_vY[4] + (v85 - *p_vY) * p_vY[3] + v136 * p_vY[2] > 0.0 )
          v43 |= 1u;
        v44 = v105 + *(float *)(v11 + 133165252);
        v45 = 2 * v43;
        v137 = v93 - *(p_vY - 1);
        v155 = v44 - *p_vY;
        if ( (v89 - p_vY[1]) * p_vY[4] + v155 * p_vY[3] + v137 * p_vY[2] > 0.0 )
          v45 |= 1u;
        v46 = 2 * v45;
        v120 = v39;
        v138 = v93 - *(p_vY - 1);
        if ( (v120 - p_vY[1]) * p_vY[4] + (v44 - *p_vY) * p_vY[3] + v138 * p_vY[2] > 0.0 )
          v46 |= 1u;
        v47 = 2 * v46;
        v139 = v97 - *(p_vY - 1);
        if ( (v89 - p_vY[1]) * p_vY[4] + (v44 - *p_vY) * p_vY[3] + v139 * p_vY[2] > 0.0 )
          v47 |= 1u;
        v121 = v39;
        v48 = 2 * v47;
        v140 = v97 - *(p_vY - 1);
        if ( (v121 - p_vY[1]) * p_vY[4] + (v44 - *p_vY) * p_vY[3] + v140 * p_vY[2] > 0.0 )
          v48 |= 1u;
        if ( v48 == 255 )
          goto LABEL_71;
        ++v24;
        p_vY += 6;
      }
      while ( v24 < v21 );
    }
    v24 = v21 + 1;
    if ( v21 + 1 < 4 )
    {
      v49 = (float *)(24 * v24 + 137445540);
      while ( 1 )
      {
        v50 = v103 + *(float *)(v11 + 133165248);
        v94 = v50;
        v51 = v100 + *(float *)(v11 + 133165252);
        v86 = v51;
        v90 = v106 + vX;
        v141 = v50 - *(v49 - 1);
        v112 = v50;
        v52 = v107 + vX;
        v53 = 2 * ((v90 - v49[1]) * v49[4] + (v51 - *v49) * v49[3] + v141 * v49[2] > 0.0);
        if ( (v52 - v49[1]) * v49[4] + (v86 - *v49) * v49[3] + (v112 - *(v49 - 1)) * v49[2] > 0.0 )
          v53 |= 1u;
        v54 = v104 + *(float *)(v11 + 133165248);
        v55 = 2 * v53;
        v98 = v54;
        v142 = v54 - *(v49 - 1);
        if ( (v90 - v49[1]) * v49[4] + (v86 - *v49) * v49[3] + v142 * v49[2] > 0.0 )
          v55 |= 1u;
        v56 = 2 * v55;
        v122 = v52;
        v143 = v54 - *(v49 - 1);
        if ( (v122 - v49[1]) * v49[4] + (v86 - *v49) * v49[3] + v143 * v49[2] > 0.0 )
          v56 |= 1u;
        v57 = v105 + *(float *)(v11 + 133165252);
        v58 = 2 * v56;
        v144 = v94 - *(v49 - 1);
        v156 = v57 - *v49;
        if ( (v90 - v49[1]) * v49[4] + v156 * v49[3] + v144 * v49[2] > 0.0 )
          v58 |= 1u;
        v59 = 2 * v58;
        v123 = v52;
        v145 = v94 - *(v49 - 1);
        if ( (v123 - v49[1]) * v49[4] + (v57 - *v49) * v49[3] + v145 * v49[2] > 0.0 )
          v59 |= 1u;
        v60 = 2 * v59;
        v146 = v98 - *(v49 - 1);
        if ( (v90 - v49[1]) * v49[4] + (v57 - *v49) * v49[3] + v146 * v49[2] > 0.0 )
          v60 |= 1u;
        v124 = v52;
        v61 = 2 * v60;
        v147 = v98 - *(v49 - 1);
        if ( (v124 - v49[1]) * v49[4] + (v57 - *v49) * v49[3] + v147 * v49[2] > 0.0 )
          v61 |= 1u;
        if ( v61 == 255 )
          break;
        v49 += 6;
        ++v24;
        if ( (int)v49 >= 137445636 )
          return false;
      }
      goto LABEL_71;
    }
  }
  else if ( v6 < TerrainRender_ptContext->aptMinMaxHeightMipMaps[v5]->nLevels - 1 )
  {
    v64 = TerrainRender_ptContext->apvMipMapsDeltaZ[v5][v6];
    v83 = TerrainRender_atManualVertex[*aiVertices].tPos.vZ - v64;
    v65 = v64 + TerrainRender_atManualVertex[*aiVertices].tPos.vZ;
    v66 = TerrainRender_atManualVertex[aiVertices[1]].tPos.vZ;
    if ( v66 >= v83 )
    {
      if ( v66 > v65 )
        v65 = TerrainRender_atManualVertex[aiVertices[1]].tPos.vZ;
    }
    else
    {
      v83 = TerrainRender_atManualVertex[aiVertices[1]].tPos.vZ;
    }
    v67 = TerrainRender_atManualVertex[aiVertices[2]].tPos.vZ;
    if ( v67 >= v83 )
    {
      if ( v67 > v65 )
        v65 = TerrainRender_atManualVertex[aiVertices[2]].tPos.vZ;
    }
    else
    {
      v83 = TerrainRender_atManualVertex[aiVertices[2]].tPos.vZ;
    }
    v68 = TerrainRender_atManualVertex[aiVertices[3]].tPos.vZ;
    if ( v68 >= v83 )
    {
      if ( v68 > v65 )
        v65 = TerrainRender_atManualVertex[aiVertices[3]].tPos.vZ;
    }
    else
    {
      v83 = TerrainRender_atManualVertex[aiVertices[3]].tPos.vZ;
    }
    v69 = &TerrainRender_atClippingPlanes[0].tPos.vY;
    v109 = v65 - v83;
    while ( 1 )
    {
      v70 = v104 * 0.0 + TerrainRender_atManualVertex[*aiVertices].tPos.vX;
      v95 = v70;
      v71 = v105 * 0.0 + TerrainRender_atManualVertex[*aiVertices].tPos.vY;
      v87 = v71;
      v91 = v109 * 0.0 + v83;
      v148 = v70 - *(v69 - 1);
      v113 = v70;
      v72 = v109 + v83;
      v73 = 2 * ((v91 - v69[1]) * v69[4] + (v71 - *v69) * v69[3] + v148 * v69[2] > 0.0);
      if ( (v72 - v69[1]) * v69[4] + (v87 - *v69) * v69[3] + (v113 - *(v69 - 1)) * v69[2] > 0.0 )
        v73 |= 1u;
      v74 = v104 + TerrainRender_atManualVertex[*aiVertices].tPos.vX;
      v75 = 2 * v73;
      v99 = v74;
      v149 = v74 - *(v69 - 1);
      if ( (v91 - v69[1]) * v69[4] + (v87 - *v69) * v69[3] + v149 * v69[2] > 0.0 )
        v75 |= 1u;
      v76 = 2 * v75;
      v125 = v72;
      v150 = v74 - *(v69 - 1);
      if ( (v125 - v69[1]) * v69[4] + (v87 - *v69) * v69[3] + v150 * v69[2] > 0.0 )
        v76 |= 1u;
      v77 = v105 + TerrainRender_atManualVertex[*aiVertices].tPos.vY;
      v78 = 2 * v76;
      v151 = v95 - *(v69 - 1);
      v157 = v77 - *v69;
      if ( (v91 - v69[1]) * v69[4] + v157 * v69[3] + v151 * v69[2] > 0.0 )
        v78 |= 1u;
      v79 = 2 * v78;
      v126 = v72;
      v152 = v95 - *(v69 - 1);
      if ( (v126 - v69[1]) * v69[4] + (v77 - *v69) * v69[3] + v152 * v69[2] > 0.0 )
        v79 |= 1u;
      v80 = 2 * v79;
      v153 = v99 - *(v69 - 1);
      if ( (v91 - v69[1]) * v69[4] + (v77 - *v69) * v69[3] + v153 * v69[2] > 0.0 )
        v80 |= 1u;
      v127 = v72;
      v81 = 2 * v80;
      v154 = v99 - *(v69 - 1);
      if ( (v127 - v69[1]) * v69[4] + (v77 - *v69) * v69[3] + v154 * v69[2] > 0.0 )
        v81 |= 1u;
      if ( v81 == 255 )
        break;
      v69 += 6;
      if ( (int)v69 >= 137445636 )
        return false;
    }
    return true;
  }
  return false;
}

// source: e/3/pc/pc_terrainrender.c:2951  [size]
void __cdecl TerrainRender_AddStackSquare(
        unsigned int nX,
        unsigned int nY,
        int nSize,
        unsigned __int16 iVertex0,
        unsigned __int16 iVertex1,
        unsigned __int16 iVertex2,
        unsigned __int16 iVertex3,
        unsigned int iEdge0,
        unsigned int iEdge1,
        unsigned int iEdge2,
        unsigned int iEdge3,
        int iMipMap,
        int nPitch)
{
  unsigned __int16 v13; // bp
  struct TerrainContext_t *v14; // esi
  unsigned int v15; // eax
  unsigned __int8 v16; // bl
  unsigned __int8 v17; // al
  int v18; // ecx
  int v19; // eax
  unsigned __int8 v20; // dl
  int v21; // edi
  int v22; // ebx
  int v23; // eax
  int v24; // eax
  unsigned int aiVertices[4]; // [esp+10h] [ebp-10h] BYREF
  char nSizea = *(char *)&nSize; // [esp+2Ch] [ebp+Ch] ARGSLOT
  unsigned __int8 iMipMapa = *(unsigned __int8 *)&iMipMap; // [esp+50h] [ebp+30h] ARGSLOT

  aiVertices[0] = iVertex0;
  v13 = nSize;
  aiVertices[3] = iVertex3;
  v14 = TerrainRender_ptContext;
  aiVertices[1] = iVertex1;
  v15 = nY - TerrainRender_ptContext->atSubmapPos[TerrainRender_iTerrainMap].nY;
  aiVertices[2] = iVertex2;
  v16 = iMipMap;
  v17 = TerrainRender_ptContext->aapiSubmap[TerrainRender_iTerrainMap][iMipMap][(nX
                                                                               - TerrainRender_ptContext->atSubmapPos[TerrainRender_iTerrainMap].nX)
                                                                              / nSize
                                                                              + (nPitch >> iMipMap) * (v15 / nSize)];
  iMipMapa = v17;
  if ( v17 )
  {
    v21 = v17;
    if ( TerrainRender_IsSquareOutOfSight(nSize, aiVertices, v17, iMipMap) == false )
    {
      v22 = TerrainRender_nNumStackItems;
      if ( TerrainRender_nNumStackItems < 5000 )
      {
        v23 = v14->atMapSize[v21].nX;
        if ( v23 <= v14->atMapSize[v21].nY )
          v23 = v14->atMapSize[v21].nY;
        _BitScanReverse((unsigned int *)&v23, v23 / (nSize >> v14->anSubmapShift[v21]));
        nSizea = v23;
        v24 = TerrainRender_nNumStackItems;
        TerrainRender_atDrawSquareStack[v24].nX = nX;
        TerrainRender_atDrawSquareStack[v24].nY = nY;
        TerrainRender_atDrawSquareStack[v24].nSize = v13;
        TerrainRender_atDrawSquareStack[v24].iMipMap = LOBYTE(v14->anNumMipMaps[v21]) - nSizea - 1;
        TerrainRender_atDrawSquareStack[v24].iTerrainMap = iMipMapa;
        TerrainRender_atDrawSquareStack[v24].aiVertex[0] = iVertex0;
        TerrainRender_atDrawSquareStack[v24].aiVertex[1] = iVertex1;
        TerrainRender_atDrawSquareStack[v24].aiVertex[2] = iVertex2;
        TerrainRender_atDrawSquareStack[v24].aiVertex[3] = iVertex3;
        TerrainRender_atDrawSquareStack[v24].aiEdge[0] = iEdge0;
        TerrainRender_atDrawSquareStack[v24].aiEdge[1] = iEdge1;
        TerrainRender_atDrawSquareStack[v24].aiEdge[2] = iEdge2;
        TerrainRender_nNumStackItems = v22 + 1;
        TerrainRender_atDrawSquareStack[v24].aiEdge[3] = iEdge3;
      }
    }
  }
  else if ( TerrainRender_IsSquareOutOfSight(nSize, aiVertices, TerrainRender_iTerrainMap, iMipMap) == false )
  {
    v18 = TerrainRender_nNumStackItems;
    if ( TerrainRender_nNumStackItems < 5000 )
    {
      v19 = TerrainRender_nNumStackItems;
      TerrainRender_atDrawSquareStack[v19].nX = nX;
      TerrainRender_atDrawSquareStack[v19].nY = nY;
      v20 = TerrainRender_iTerrainMap;
      TerrainRender_atDrawSquareStack[v19].nSize = nSize;
      TerrainRender_atDrawSquareStack[v19].iMipMap = v16;
      TerrainRender_atDrawSquareStack[v19].iTerrainMap = v20;
      TerrainRender_atDrawSquareStack[v19].aiVertex[0] = iVertex0;
      TerrainRender_atDrawSquareStack[v19].aiVertex[1] = iVertex1;
      TerrainRender_atDrawSquareStack[v19].aiVertex[2] = iVertex2;
      TerrainRender_atDrawSquareStack[v19].aiVertex[3] = iVertex3;
      TerrainRender_atDrawSquareStack[v19].aiEdge[0] = iEdge0;
      TerrainRender_atDrawSquareStack[v19].aiEdge[1] = iEdge1;
      TerrainRender_atDrawSquareStack[v19].aiEdge[2] = iEdge2;
      TerrainRender_nNumStackItems = v18 + 1;
      TerrainRender_atDrawSquareStack[v19].aiEdge[3] = iEdge3;
    }
  }
}

char __cdecl sub_5F9860(int a1, int a2, int a3, int a4, float *a5, _BYTE *a6)
{
  int v6; // eax
  int v7; // edx
  int v8; // ecx
  char result; // al
  int v10; // ecx

  v6 = *(_DWORD *)(a3 + 8 * a4 + 1436);
  if ( a1 < v6 )
  {
    if ( a2 < v6 )
    {
      v10 = a1 + a2 * v6;
      *a5 = *(float *)(*(_DWORD *)(a3 + 4 * a4 + 316) + 4 * v10);
    }
    else
    {
      v10 = a1 + v6 * (v6 - 1);
      *a5 = *(float *)(*(_DWORD *)(a3 + 4 * a4 + 316) + 4 * v10)
          + *(float *)(*(_DWORD *)(a3 + 4 * a4 + 316) + 4 * v10)
          - *(float *)(*(_DWORD *)(a3 + 4 * a4 + 316) + 4 * (a1 + v6 * (v6 - 2)));
    }
    result = *(_BYTE *)(v10 + *(_DWORD *)(a3 + 4 * a4 + 1396));
    *a6 = result;
  }
  else
  {
    v7 = v6 - 1;
    if ( a2 < v6 )
    {
      v8 = a2 * v6 + v7;
      *a5 = *(float *)(*(_DWORD *)(a3 + 4 * a4 + 316) + 4 * v8)
          + *(float *)(*(_DWORD *)(a3 + 4 * a4 + 316) + 4 * v8)
          - *(float *)(*(_DWORD *)(a3 + 4 * a4 + 316) + 4 * v8 - 4);
    }
    else
    {
      v8 = v7 + v6 * v7;
      *a5 = *(float *)(*(_DWORD *)(a3 + 4 * a4 + 316) + 4 * v8) * 3.0
          - *(float *)(*(_DWORD *)(a3 + 4 * a4 + 316) + 4 * v8 - 4)
          - *(float *)(*(_DWORD *)(a3 + 4 * a4 + 316) + 4 * (v7 + v6 * (v6 - 2)));
    }
    result = *(_BYTE *)(v8 + *(_DWORD *)(a3 + 4 * a4 + 1396));
    *a6 = result;
  }
  return result;
}

// source: e/3/pc/pc_terrainrender.c:3069  [size~]
void __cdecl TerrainRender_Draw(struct TerrainContext_t *ptContext, int ltcg_arg1, int ltcg_arg2)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v137; };
    struct { char igi2_o1[24]; int nY; };
    struct { char igi2_o2[24]; unsigned __int8 *p_eSplitStatus; };
    struct { char igi2_o3[24]; unsigned int v139; };
    struct { char igi2_o4[24]; _BYTE *v141; };
    struct { char igi2_o5[28]; float v142; };
    struct { char igi2_o6[28]; int v143; };
    struct { char igi2_o7[28]; int v144; };
    struct { char igi2_o8[32]; int v145; };
    struct { char igi2_o9[32]; int v146; };
    struct { char igi2_o10[32]; _DWORD *v147; };
    struct { char igi2_o11[32]; unsigned __int16 v148; };
    struct { char igi2_o12[36]; unsigned __int16 *p_iSplitVertex; };
    struct { char igi2_o13[36]; unsigned int v149; };
    struct { char igi2_o14[36]; _WORD *v151; };
    struct { char igi2_o15[40]; unsigned __int16 *p_nMorph; };
    struct { char igi2_o16[40]; int v152; };
    struct { char igi2_o17[40]; _WORD *v154; };
    struct { char igi2_o18[44]; float v155; };
    struct { char igi2_o19[44]; unsigned int v156; };
    struct { char igi2_o20[48]; float v157; };
    struct { char igi2_o21[48]; _DWORD *v158; };
    struct { char igi2_o22[52]; float v159; };
    struct { char igi2_o23[52]; _DWORD *v160; };
    struct { char igi2_o24[56]; int v161; };
    struct { char igi2_o25[56]; int v162; };
    struct { char igi2_o26[56]; unsigned __int16 *v163; };
    struct { char igi2_o27[60]; unsigned __int16 *aiVertex; };
    struct { char igi2_o28[60]; int v164; };
    struct { char igi2_o29[60]; float v165; };
    struct { char igi2_o30[64]; float v167; };
    struct { char igi2_o31[68]; float v168; };
    struct { char igi2_o32[72]; float v169; };
    struct { char igi2_o33[76]; int nX; };
    struct { char igi2_o34[76]; unsigned int v171; };
    struct { char igi2_o35[80]; float v172; };
    struct { char igi2_o36[80]; unsigned __int16 v173; };
    struct { char igi2_o37[80]; unsigned int *v174; };
    struct { char igi2_o38[84]; struct TerrainRenderEdge_t *nPitch; };
    struct { char igi2_o39[84]; float nPitcha; };
    struct { char igi2_o40[88]; float v177; };
    struct { char igi2_o41[92]; float v178; };
    struct { char igi2_o42[96]; __int16 v179; };
    struct { char igi2_o43[100]; char v180; };
    struct { char igi2_o44[101]; __int16 v181; };
    struct { char igi2_o45[103]; char v182; };
    struct { char igi2_o46[104]; unsigned __int16 *v183; };
    struct { char igi2_o47[108]; int v184; };
    struct { char igi2_o48[112]; int v185; };
    struct { char igi2_o49[116]; float v186; };
    struct { char igi2_o50[120]; int v187; };
    struct { char igi2_o51[124]; float v188; };
    struct { char igi2_o52[128]; int iVertex; };
    struct { char igi2_o53[132]; float v190; };
    struct { char igi2_o54[136]; float v191; };
    struct { char igi2_o55[140]; float v192; };
    struct { char igi2_o56[148]; float vX; };
    struct { char igi2_o57[152]; struct real32x3_t ptDisplacement; };
    struct { char igi2_o58[164]; float v195; };
    struct { char igi2_o59[168]; float v196; };
    struct { char igi2_o60[172]; float v197; };
    struct { char igi2_o61[176]; __int64 v198; };
    struct { char igi2_o62[184]; int v199[2]; };
    struct { char igi2_o63[192]; unsigned __int16 v200[6]; };
    struct { char igi2_o64[204]; unsigned __int16 v201[2]; };
    struct { char igi2_o65[208]; unsigned __int16 iVertex2[2]; };
    struct { char igi2_o66[212]; unsigned __int16 v203; };
    struct { char igi2_o67[214]; __int16 v204; };
    struct { char igi2_o68[216]; __int16 v205; };
    struct { char igi2_o69[218]; float v206; };
    struct { char igi2_o70[222]; unsigned __int16 v207; };
    struct { char igi2_o71[224]; __int16 v208; };
    struct { char igi2_o72[226]; unsigned __int16 v209; };
    struct { char igi2_o73[228]; int v210; };
    struct { char igi2_o74[232]; int v211; };
    struct { char igi2_o75[236]; int v212; };
    struct { char igi2_o76[240]; int iVertex0[7]; };
    struct { char igi2_o77[268]; int v214; };
    struct { char igi2_o78[276]; _DWORD v215[4]; };
    struct { char igi2_o79[292]; int v216; };
    struct { char igi2_o80[296]; _DWORD v217[11]; };
    struct { char igi2_o81[340]; _DWORD v218[14]; };
    char igi2_extent[396];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  float vY; // edx
  int nNumMaterials; // eax
  int v5; // edi
  struct IDirect3DVertexBuffer8Vtbl *lpVtbl; // ecx
  int v7; // ecx
  int i; // eax
  int v9; // edx
  struct RenderStateBlock_t *v10; // eax
  int v11; // ecx
  struct RenderStateBlock_t *v12; // eax
  int v13; // ecx
  struct RenderStateBlock_t *v14; // eax
  int v15; // ecx
  struct RenderStateBlock_t *v16; // eax
  int v17; // ecx
  double v18; // st7
  double v19; // st7
  int v20; // ebp
  float *p_vY; // ebx
  int v22; // eax
  int v23; // ecx
  int v24; // esi
  int v25; // eax
  int v26; // esi
  double v27; // st7
  double v28; // st7
  int v29; // edx
  int v30; // eax
  int v31; // edx
  double v32; // st6
  double v33; // st7
  int v34; // ebx
  int v35; // esi
  int v36; // eax
  int v37; // eax
  unsigned int v38; // eax
  int iTerrainMap; // ebx
  unsigned __int16 *v40; // eax
  struct TerrainContext_t *v41; // edi
  int v42; // ebp
  int v43; // ecx
  int v44; // edx
  int v45; // ecx
  unsigned __int16 v46; // si
  unsigned int v47; // ecx
  _DWORD *v48; // eax
  int v49; // edx
  int v50; // edi
  int v51; // eax
  int v52; // esi
  unsigned __int8 eSplitStatus; // al
  int v54; // esi
  double v55; // st7
  double v56; // st6
  double v57; // st6
  double v58; // st6
  double v59; // st5
  unsigned int v60; // ecx
  double v61; // st4
  unsigned int v62; // eax
  double v63; // st6
  struct TerrainContext_t *v64; // edx
  double v65; // st6
  double v66; // st6
  double v67; // st7
  double v68; // st6
  double v69; // st7
  double v70; // st6
  double v71; // st7
  unsigned int v72; // eax
  unsigned __int8 v73; // cl
  unsigned __int8 v74; // cl
  bool v75; // cf
  unsigned __int16 v76; // dx
  unsigned __int16 v77; // cx
  unsigned __int16 iSplitVertex; // ax
  int v79; // ebp
  int v80; // eax
  float *v81; // ecx
  int v82; // eax
  unsigned __int16 v83; // si
  int v84; // ebx
  int v85; // ecx
  int v86; // ecx
  float vZ; // esi
  int v88; // edx
  int v89; // edx
  _WORD *v90; // esi
  unsigned __int16 *v91; // esi
  unsigned __int16 v92; // di
  int v93; // ecx
  unsigned int *v94; // eax
  unsigned int v95; // ebp
  unsigned int v96; // eax
  unsigned __int8 v97; // dl
  int v98; // ebx
  int v99; // eax
  int v100; // ecx
  unsigned __int16 v101; // bp
  int v102; // eax
  int v103; // ecx
  int v104; // eax
  int v105; // ecx
  unsigned __int16 v106; // bp
  int v107; // eax
  int v108; // edx
  int v109; // ecx
  unsigned int v110; // ebx
  int v111; // ebp
  int v112; // eax
  int v113; // ecx
  int v114; // eax
  int v115; // ecx
  int v116; // eax
  int v117; // esi
  int v118; // edi
  int v119; // eax
  int v120; // ebx
  int v121; // ebp
  int v122; // eax
  unsigned int v123; // esi
  unsigned int v124; // edx
  int v125; // eax
  unsigned int *v126; // esi
  int j; // edi
  unsigned int v128; // ebx
  unsigned int *v129; // ebp
  int v130; // esi
  char v131; // al
  unsigned __int16 *v132; // ebx
  struct QObjectVector_s *v133; // ecx
  int k; // edi
  int m; // esi
  void **papxElement; // edx

  igi2_frame.v182 = 16;
  igi2_frame.v212 = 0;
  igi2_frame.iVertex0[0] = 0;
  igi2_frame.iVertex0[1] = 1;
  igi2_frame.iVertex0[2] = 0;
  igi2_frame.iVertex0[3] = 1;
  igi2_frame.iVertex0[4] = 1;
  igi2_frame.iVertex0[5] = 0;
  igi2_frame.iVertex0[6] = 1;
  igi2_frame.v180 = 0;
  igi2_frame.v181 = 4096;
  TerrainRender_ptContext = ptContext;
  if ( QCube_isDrawOutside )
  {
    igi2_frame.vX = ptContext->tDisplacement.vX;
    vY = ptContext->tDisplacement.vY;
    igi2_frame.ptDisplacement.vY = ptContext->tDisplacement.vZ;
    nNumMaterials = ptContext->nNumMaterials;
    TerrainRender_vMorphSpeed = 0.5;
    TerrainRender_vMaterialMorphSpeed = 2.0;
    igi2_frame.ptDisplacement.vX = vY;
    TerrainRender_nNumChunksDrawn = 0;
    TerrainRender_nNumStackItemsProcessed = 0;
    TerrainRender_nNumVerticesProcessed = 0;
    v5 = 1;
    if ( nNumMaterials >= 1 )
      v5 = nNumMaterials;
    if ( v5 != TerrainRender_nNumMaterialVertexBuffers )
    {
      TerrainRender_DeleteMaterialVertexBuffers();
      TerrainRender_AllocateMaterialVertexBuffers(v5);
    }
    memset(TerrainRender_aaptRenderChunk, 0, sizeof(TerrainRender_aaptRenderChunk));
    lpVtbl = TerrainRender_ptVertexBuffer->lpVtbl;
    TerrainRender_nNumVertices = 0;
    if ( !lpVtbl->Lock(TerrainRender_ptVertexBuffer, 0, 0, (unsigned __int8 **)&TerrainRender_ptLockedVertex, 0x2000u) )
    {
      if ( TerrainRender_ptIndexBuffer->lpVtbl->Lock(
             TerrainRender_ptIndexBuffer,
             0,
             0,
             (unsigned __int8 **)&TerrainRender_piLockedIndex,
             0x2000u) )
      {
        TerrainRender_ptVertexBuffer->lpVtbl->Unlock(TerrainRender_ptVertexBuffer);
        return;
      }
      v7 = TerrainRender_nNumMaterialVertexBuffers;
      for ( i = 0; i < v7; TerrainRender_atMaterialReadableBuffer[v9].isInUse = 0 )
        v9 = ptContext->aiMaterial[i++];
      TerrainRender_SetVertexShaderConstants(ptContext, (struct real32x3_t *)&igi2_frame.vX);
      v10 = Direct3D_ptTextureStateBlock;
      v11 = TerrainRender_eTextureState;
      if ( Direct3D_ptTextureStateBlock->eCurrentState != TerrainRender_eTextureState )
      {
        Direct3D_ptTextureStateBlock->eCurrentState = TerrainRender_eTextureState;
        v10->atRenderState[v11].pfCallback(nullptr);
      }
      v12 = Direct3D_ptBlendStateBlock;
      v13 = TerrainRender_eBlendState;
      if ( Direct3D_ptBlendStateBlock->eCurrentState != TerrainRender_eBlendState )
      {
        Direct3D_ptBlendStateBlock->eCurrentState = TerrainRender_eBlendState;
        v12->atRenderState[v13].pfCallback(nullptr);
      }
      v14 = Direct3D_ptGenericStateBlock;
      v15 = TerrainRender_eGenericState;
      if ( Direct3D_ptGenericStateBlock->eCurrentState != TerrainRender_eGenericState )
      {
        Direct3D_ptGenericStateBlock->eCurrentState = TerrainRender_eGenericState;
        v14->atRenderState[v15].pfCallback(nullptr);
      }
      v16 = Direct3D_ptClippingStateBlock;
      v17 = Direct3D_eClippingStateOn;
      if ( Direct3D_ptClippingStateBlock->eCurrentState != Direct3D_eClippingStateOn )
      {
        Direct3D_ptClippingStateBlock->eCurrentState = Direct3D_eClippingStateOn;
        v16->atRenderState[v17].pfCallback(nullptr);
      }
      Direct3D_ptDevice->lpVtbl->SetRenderState(
        Direct3D_ptDevice,
        D3DRS_SOFTWAREVERTEXPROCESSING,
        Direct3D_isHWVertexShader == 0);
      Direct3D_tState.aptStreamData[0] = TerrainRender_ptVertexBuffer;
      Direct3D_tState.anStride[0] = 16;
      Direct3D_ptDevice->lpVtbl->SetStreamSource(Direct3D_ptDevice, 0, TerrainRender_ptVertexBuffer, 16u);
      Direct3D_tState.ptIndexData = TerrainRender_ptIndexBuffer;
      Direct3D_tState.nBaseVertexIndex = 0;
      Direct3D_ptDevice->lpVtbl->SetIndices(Direct3D_ptDevice, TerrainRender_ptIndexBuffer, 0);
      igi2_frame.nX = ptContext->atMapSize[0].nX;
      igi2_frame.nY = ptContext->atMapSize[0].nY;
      v18 = ptContext->avMapWorldWidth[0] / (double)igi2_frame.nX;
      TerrainRender_nNumVertices = 0;
      TerrainRender_iTerrainMap = 0;
      TerrainRender_nNumStackItems = 0;
      TerrainRender_nStackItemInsertionPoint = 0;
      TerrainRender_nCurrentStackItem = 0;
      TerrainRender_nNumEdges = 4;
      igi2_frame.v186 = v18;
      v19 = ptContext->avMapWorldHeight[0] / (double)igi2_frame.nY;
      TerrainRender_atEdge[0].aiVertex[1] = 1;
      TerrainRender_atEdge[1].aiVertex[0] = 1;
      TerrainRender_atEdge[0].aiVertex[0] = 0;
      TerrainRender_atEdge[0].aiChild[0] = -1;
      TerrainRender_atEdge[0].aiChild[1] = -1;
      TerrainRender_atEdge[0].iSplitVertex = -1;
      TerrainRender_atEdge[0].eSplitStatus = 0;
      TerrainRender_atEdge[0].nMorph = 0;
      TerrainRender_atEdge[1].aiVertex[1] = 2;
      TerrainRender_atEdge[1].aiChild[0] = -1;
      TerrainRender_atEdge[1].aiChild[1] = -1;
      TerrainRender_atEdge[1].iSplitVertex = -1;
      TerrainRender_atEdge[1].eSplitStatus = 0;
      TerrainRender_atEdge[1].nMorph = 0;
      TerrainRender_atEdge[2].aiVertex[0] = 3;
      TerrainRender_atEdge[2].aiVertex[1] = 2;
      TerrainRender_atEdge[2].aiChild[0] = -1;
      TerrainRender_atEdge[2].aiChild[1] = -1;
      TerrainRender_atEdge[2].iSplitVertex = -1;
      TerrainRender_atEdge[2].eSplitStatus = 0;
      TerrainRender_atEdge[2].nMorph = 0;
      TerrainRender_atEdge[3].aiVertex[0] = 0;
      TerrainRender_atEdge[3].aiVertex[1] = 3;
      TerrainRender_atEdge[3].aiChild[0] = -1;
      TerrainRender_atEdge[3].aiChild[1] = -1;
      TerrainRender_atEdge[3].iSplitVertex = -1;
      TerrainRender_atEdge[3].eSplitStatus = 0;
      TerrainRender_atEdge[3].nMorph = 0;
      igi2_frame.v142 = v19;
      igi2_frame.v172 = igi2_frame.v186 * 0.5;
      v20 = 0;
      p_vY = &TerrainRender_atManualVertex[0].tPos.vY;
      do
      {
        v22 = igi2_frame.nY;
        if ( igi2_frame.nX > igi2_frame.nY )
          v22 = igi2_frame.nX;
        v23 = ptContext->anSubmapShift[0];
        v24 = igi2_frame.nY;
        igi2_frame.v184 = igi2_frame.iVertex0[2 * v20 - 1] * (v22 << v23);
        if ( igi2_frame.nX > igi2_frame.nY )
          v24 = igi2_frame.nX;
        v25 = igi2_frame.iVertex0[2 * v20];
        igi2_frame.v145 = igi2_frame.nX;
        v26 = v25 * (v24 << v23);
        if ( igi2_frame.nX <= igi2_frame.nY )
          igi2_frame.v145 = igi2_frame.nY;
        v27 = (double)igi2_frame.v145 * igi2_frame.v186 * (double)(2 * igi2_frame.iVertex0[2 * v20 - 1] - 1);
        igi2_frame.v146 = igi2_frame.nX;
        v28 = v27 * 0.5 + ptContext->atMapPos[0].vX + igi2_frame.v172;
        if ( igi2_frame.nX <= igi2_frame.nY )
          igi2_frame.v146 = igi2_frame.nY;
        v29 = 2 * v25 - 1;
        v30 = igi2_frame.v184;
        igi2_frame.v161 = v29;
        v31 = igi2_frame.v184;
        v32 = v28;
        igi2_frame.nPitcha = igi2_frame.v142 * 0.5;
        v33 = (double)igi2_frame.v146 * igi2_frame.v142 * (double)igi2_frame.v161 * 0.5 + ptContext->atMapPos[0].vY + igi2_frame.nPitcha;
        *(p_vY - 1) = v32;
        *p_vY = v33;
        *((_DWORD *)p_vY + 3) = v30;
        *((_DWORD *)p_vY + 4) = v26;
        sub_5F9860(
          v31 >> ptContext->anSubmapShift[0],
          v26 >> ptContext->anSubmapShift[0],
          (int)ptContext,
          0,
          p_vY + 1,
          (_BYTE *)p_vY + 24);
        p_vY[2] = p_vY[1];
        p_vY += 8;
        ++v20;
      }
      while ( (int)p_vY < 133165380 );
      TerrainRender_nNumVertices = v20;
      v34 = (unsigned __int16)v20 - 4;
      v35 = 4;
      do
      {
        TerrainRender_CalculateRenderVertex(v34, v34, v34, 1.0, ptContext);
        ++v34;
        --v35;
      }
      while ( v35 );
      v36 = igi2_frame.nY;
      if ( igi2_frame.nX > igi2_frame.nY )
        v36 = igi2_frame.nX;
      TerrainRender_AddStackSquare(
        0,
        0,
        v36 << ptContext->anSubmapShift[0],
        v20 - 4,
        v20 - 3,
        v20 - 2,
        v20 - 1,
        0,
        1u,
        2u,
        3u,
        ptContext->anNumMipMaps[0] - 1,
        igi2_frame.nX);
      v37 = TerrainRender_nNumStackItems;
      if ( TerrainRender_nNumStackItems )
      {
        igi2_frame.v216 = 0;
        igi2_frame.v217[0] = 1;
        igi2_frame.v217[1] = 1;
        igi2_frame.v217[2] = 2;
        igi2_frame.v217[3] = 2;
        igi2_frame.v217[4] = 3;
        igi2_frame.v217[5] = 3;
        igi2_frame.v217[6] = 0;
        igi2_frame.v217[7] = 1;
        igi2_frame.v217[8] = 3;
        while ( 1 )
        {
          TerrainRender_nNumStackItems = v37 - 1;
          igi2_frame.v177 = IGI2_FLOAT_BITS(0xffffffffu);
          igi2_frame.v178 = IGI2_FLOAT_BITS(0xffffffffu);
          igi2_frame.v179 = -1;
          v38 = 9 * (v37 - 1);
          iTerrainMap = TerrainRender_atDrawSquareStack[v38 / 9].iTerrainMap;
          v40 = (unsigned __int16 *)(4 * v38 + 137446504);
          ++TerrainRender_nNumStackItemsProcessed;
          v41 = ptContext;
          v42 = ptContext->anSubmapShift[iTerrainMap];
          igi2_frame.v171 = ptContext->atMapSize[iTerrainMap].nX;
          igi2_frame.v139 = ptContext->atMapSize[iTerrainMap].nY;
          v43 = 32 * v40[6] + 133165248;
          igi2_frame.v215[0] = 32 * v40[5] + 133165248;
          v44 = v40[7];
          igi2_frame.v215[1] = v43;
          v45 = 32 * v40[8] + 133165248;
          v46 = v40[2];
          igi2_frame.v215[2] = 32 * v44 + 133165248;
          igi2_frame.v215[3] = v45;
          igi2_frame.v183 = v40;
          igi2_frame.v162 = iTerrainMap;
          TerrainRender_iTerrainMap = iTerrainMap;
          igi2_frame.v210 = v42;
          igi2_frame.v152 = 0;
          igi2_frame.v173 = v46;
          if ( v46 <= 1 << v42 )
            goto LABEL_100;
          v47 = 0;
          v48 = v40 + 10;
          igi2_frame.v149 = 0;
          igi2_frame.v147 = v48;
          do
          {
            v49 = igi2_frame.v215[igi2_frame.v217[2 * v47 - 1]];
            v50 = igi2_frame.v215[igi2_frame.v217[2 * v47]];
            igi2_frame.v143 = 0;
            igi2_frame.v164 = v49;
            if ( v47 >= 4 )
              goto LABEL_42;
            v51 = *v48;
            v52 = 5 * v51;
            eSplitStatus = TerrainRender_atEdge[v51].eSplitStatus;
            v54 = 4 * v52 + 134125256;
            if ( (eSplitStatus & 1) != 0 )
            {
              *((_WORD *)igi2_frame.v199 + v47) = *(_WORD *)(v54 + 16);
              ++igi2_frame.v152;
              goto LABEL_76;
            }
            if ( (eSplitStatus & 2) != 0 )
            {
              *((_WORD *)igi2_frame.v199 + v47) = 0;
            }
            else
            {
LABEL_42:
              igi2_frame.v191 = igi2_frame.vX + *(float *)v49;
              igi2_frame.v192 = igi2_frame.ptDisplacement.vX + *(float *)(v49 + 4);
              v55 = igi2_frame.ptDisplacement.vY + *(float *)(v49 + 8);
              igi2_frame.v195 = igi2_frame.vX + *(float *)v50;
              igi2_frame.v196 = igi2_frame.ptDisplacement.vX + *(float *)(v50 + 4);
              igi2_frame.v197 = igi2_frame.ptDisplacement.vY + *(float *)(v50 + 8);
              igi2_frame.v167 = igi2_frame.v195 - igi2_frame.v191;
              igi2_frame.v168 = igi2_frame.v196 - igi2_frame.v192;
              v56 = igi2_frame.v197 - v55;
              igi2_frame.v169 = v56;
              igi2_frame.v159 = igi2_frame.v167 * igi2_frame.v167 + igi2_frame.v168 * igi2_frame.v168 + v56 * v56;
              v57 = (igi2_frame.v169 * v55 + igi2_frame.v168 * igi2_frame.v192 + igi2_frame.v167 * igi2_frame.v191) * (-1.0 / igi2_frame.v159);
              igi2_frame.v155 = v57;
              if ( v57 >= 0.0 )
              {
                if ( igi2_frame.v155 <= 1.0 )
                {
                  igi2_frame.v190 = igi2_frame.v169 * igi2_frame.v155;
                  igi2_frame.v188 = igi2_frame.v155 * igi2_frame.v167 + igi2_frame.v191;
                  *(float *)&igi2_frame.iVertex = igi2_frame.v168 * igi2_frame.v155 + igi2_frame.v192;
                  v55 = v55 + igi2_frame.v190;
                  v58 = *(float *)&igi2_frame.iVertex;
                  v59 = igi2_frame.v188;
                }
                else
                {
                  v55 = igi2_frame.v197;
                  v58 = igi2_frame.v196;
                  v59 = igi2_frame.v195;
                }
              }
              else
              {
                v58 = igi2_frame.v192;
                v59 = igi2_frame.v191;
              }
              v60 = (((*(_DWORD *)(v50 + 16) - ptContext->atSubmapPos[iTerrainMap].nX) >> v42)
                   + ((*(_DWORD *)(v49 + 16) - ptContext->atSubmapPos[iTerrainMap].nX) >> v42)) >> 1;
              v61 = v59 * v59 + v58 * v58 + v55 * v55;
              v62 = (((*(_DWORD *)(v50 + 20) - ptContext->atSubmapPos[iTerrainMap].nY) >> v42)
                   + ((*(_DWORD *)(v49 + 20) - ptContext->atSubmapPos[iTerrainMap].nY) >> v42)) >> 1;
              v63 = 0.0;
              if ( v60 >= igi2_frame.v171 || v62 >= igi2_frame.v139 )
              {
                v64 = ptContext;
              }
              else
              {
                v64 = ptContext;
                v65 = (*(float *)(v50 + 12) + *(float *)(igi2_frame.v164 + 12)) * 0.5
                    - ptContext->apvHeightmap[iTerrainMap][v60 + igi2_frame.v171 * v62];
                if ( v65 < 0.0 )
                  v65 = -v65;
                v63 = v65 / ((double)(unsigned __int16)(igi2_frame.v173 >> v42) * igi2_frame.v186);
              }
              v66 = 1.0 / (v63 * v64->vAdapt * 0.5 + 1.0) * v64->vDetail;
              igi2_frame.v165 = v66 * v66 * v61;
              v67 = igi2_frame.v169;
              if ( igi2_frame.v169 < 0.0 )
                v67 = -v67;
              v68 = igi2_frame.v167;
              if ( igi2_frame.v167 < 0.0 )
                v68 = -v68;
              if ( v67 > 10.0 * v68 )
              {
                v69 = igi2_frame.v169;
                if ( igi2_frame.v169 < 0.0 )
                  v69 = -v69;
                v70 = igi2_frame.v168;
                if ( igi2_frame.v168 < 0.0 )
                  v70 = -v70;
                if ( v69 > 10.0 * v70 )
                  goto LABEL_70;
              }
              if ( igi2_frame.v159 <= (double)igi2_frame.v165 || igi2_frame.v159 <= 4194304.0 )
              {
LABEL_70:
                v72 = igi2_frame.v149;
                *((_WORD *)igi2_frame.v199 + igi2_frame.v149) = 0;
              }
              else
              {
                v71 = (igi2_frame.v159 / igi2_frame.v165 - 1.0) * TerrainRender_vMorphSpeed;
                igi2_frame.v157 = v71;
                if ( v71 > 0.0 )
                {
                  igi2_frame.v143 = 1;
                  v72 = igi2_frame.v149;
                  if ( igi2_frame.v157 < 1.0 )
                  {
                    ++igi2_frame.v152;
                    igi2_frame.v198 = (__int64)(igi2_frame.v157 * 65535.0);
                    *((_WORD *)igi2_frame.v199 + igi2_frame.v149) = igi2_frame.v198;
                  }
                  else
                  {
                    *((_WORD *)igi2_frame.v199 + igi2_frame.v149) = -1;
                    ++igi2_frame.v152;
                  }
                }
                else
                {
                  v72 = igi2_frame.v149;
                  *((_WORD *)igi2_frame.v199 + igi2_frame.v149) = 0;
                  ++igi2_frame.v152;
                }
              }
              if ( v72 < 4 )
              {
                v73 = TerrainRender_atEdge[*igi2_frame.v147].eSplitStatus;
                if ( igi2_frame.v143 )
                  v74 = v73 | 1;
                else
                  v74 = v73 | 2;
                TerrainRender_atEdge[*igi2_frame.v147].eSplitStatus = v74;
              }
            }
LABEL_76:
            v47 = igi2_frame.v149 + 1;
            v48 = igi2_frame.v147 + 1;
            v75 = ++igi2_frame.v149 < 5;
            ++igi2_frame.v147;
          }
          while ( v75 );
          if ( !igi2_frame.v152 )
          {
            v40 = igi2_frame.v183;
            v41 = ptContext;
LABEL_100:
            v128 = 0;
            v129 = (unsigned int *)(v40 + 10);
            do
            {
              v130 = 20 * *v129 + 134125256;
              if ( (TerrainRender_atEdge[*v129].eSplitStatus & 8) != 0 )
                TerrainRender_DrawGlitchPolyRecursive(*v129, v41);
              v131 = *(&igi2_frame.v180 + (((_BYTE)v128++ - 2) & 3)) | 4 | *(_BYTE *)(v130 + 19);
              ++v129;
              *(_BYTE *)(v130 + 19) = v131;
            }
            while ( v128 < 4 );
            v132 = igi2_frame.v183;
            TerrainRender_DrawFace(igi2_frame.v183[5], igi2_frame.v183[6], igi2_frame.v183[8], 1);
            TerrainRender_DrawFace(v132[8], v132[6], v132[7], 1);
            goto LABEL_105;
          }
          igi2_frame.p_nMorph = &TerrainRender_atEdge[TerrainRender_nNumEdges].nMorph;
          igi2_frame.p_eSplitStatus = &TerrainRender_atEdge[TerrainRender_nNumEdges].eSplitStatus;
          igi2_frame.p_iSplitVertex = &TerrainRender_atEdge[TerrainRender_nNumEdges].iSplitVertex;
          igi2_frame.v174 = &TerrainRender_atEdge[TerrainRender_nNumEdges].aiChild[1];
          igi2_frame.aiVertex = TerrainRender_atEdge[TerrainRender_nNumEdges].aiVertex;
          igi2_frame.nPitch = &TerrainRender_atEdge[TerrainRender_nNumEdges];
          LODWORD(igi2_frame.ptDisplacement.vZ) = &TerrainRender_atEdge[TerrainRender_nNumEdges].aiVertex[1];
          igi2_frame.v158 = igi2_frame.v217;
          igi2_frame.v160 = igi2_frame.v183 + 10;
          igi2_frame.v156 = 0;
          do
          {
            v76 = igi2_frame.v183[*(igi2_frame.v158 - 1) + 5];
            v77 = igi2_frame.v183[*igi2_frame.v158 + 5];
            if ( igi2_frame.v156 >= 8 || (iSplitVertex = TerrainRender_atEdge[*igi2_frame.v160].iSplitVertex, iSplitVertex == 0xFFFF) )
            {
              igi2_frame.v148 = TerrainRender_nNumVertices;
              LODWORD(igi2_frame.v198) = (unsigned __int16)TerrainRender_nNumVertices;
              v79 = 32 * (unsigned __int16)TerrainRender_nNumVertices++ + 133165248;
              igi2_frame.v187 = v76;
              v80 = v76;
              igi2_frame.v211 = v77;
              v81 = (float *)(32 * v77);
              *(float *)v79 = (TerrainRender_atManualVertex[v80].tPos.vX + v81[33291312]) * 0.5;
              *(float *)(v79 + 4) = (TerrainRender_atManualVertex[v80].tPos.vY + v81[33291313]) * 0.5;
              *(float *)(v79 + 8) = (TerrainRender_atManualVertex[v80].tPos.vZ + v81[33291314]) * 0.5;
              *(_DWORD *)(v79 + 16) = (*(int *)((char *)&TerrainRender_atManualVertex[0].tMapPos.nX + (_DWORD)v81)
                                     + TerrainRender_atManualVertex[v80].tMapPos.nX) >> 1;
              v82 = (*(int *)((char *)&TerrainRender_atManualVertex[0].tMapPos.nY + (_DWORD)v81)
                   + TerrainRender_atManualVertex[v80].tMapPos.nY) >> 1;
              *(_DWORD *)(v79 + 20) = v82;
              sub_5F9860(
                (*(_DWORD *)(v79 + 16) - ptContext->atSubmapPos[iTerrainMap].nX) >> igi2_frame.v210,
                (v82 - ptContext->atSubmapPos[iTerrainMap].nY) >> igi2_frame.v210,
                (int)ptContext,
                iTerrainMap,
                (float *)(v79 + 8),
                (_BYTE *)(v79 + 28));
              v83 = *(_WORD *)((char *)igi2_frame.v199 + igi2_frame.v156);
              v84 = igi2_frame.v198;
              v85 = igi2_frame.v187;
              *(_DWORD *)(v79 + 12) = *(_DWORD *)(v79 + 8);
              igi2_frame.v137 = (double)v83 * 1.5259021893143654e-05;
              TerrainRender_CalculateRenderVertex(v84, v85, igi2_frame.v211, igi2_frame.v137, ptContext);
              *(_WORD *)((char *)&igi2_frame.v177 + igi2_frame.v156) = igi2_frame.v148;
              if ( igi2_frame.v156 < 8 )
              {
                v86 = 20 * *igi2_frame.v160 + 134125256;
                *(_WORD *)(v86 + 12) = igi2_frame.v148;
                *(_WORD *)(v86 + 16) = v83;
                if ( (int)igi2_frame.aiVertex >= 135525264 )
                  goto LABEL_115;
                *igi2_frame.aiVertex = *(_WORD *)(v86 + 8);
                vZ = igi2_frame.ptDisplacement.vZ;
                v88 = TerrainRender_nNumEdges;
                *(_WORD *)LODWORD(igi2_frame.ptDisplacement.vZ) = igi2_frame.v148;
                igi2_frame.nPitch->aiChild[0] = -1;
                *igi2_frame.v174 = -1;
                *igi2_frame.p_iSplitVertex = -1;
                *igi2_frame.p_eSplitStatus = 0;
                *igi2_frame.p_nMorph = 0;
                igi2_frame.v151 = igi2_frame.p_iSplitVertex + 10;
                igi2_frame.v141 = igi2_frame.p_eSplitStatus + 20;
                igi2_frame.v144 = v88;
                v89 = v88 + 1;
                igi2_frame.v154 = igi2_frame.p_nMorph + 10;
                v90 = (_WORD *)(LODWORD(vZ) + 20);
                TerrainRender_nNumEdges = v89;
                *(_DWORD *)v86 = igi2_frame.v144;
                if ( (int)(igi2_frame.aiVertex + 10) >= 135525264 )
                  goto LABEL_115;
                igi2_frame.aiVertex[10] = igi2_frame.v148;
                *v90 = *(_WORD *)(v86 + 10);
                igi2_frame.nPitch[1].aiChild[0] = -1;
                igi2_frame.v174[5] = -1;
                *igi2_frame.v151 = -1;
                TerrainRender_nNumEdges = v89 + 1;
                *igi2_frame.v141 = 0;
                LODWORD(igi2_frame.ptDisplacement.vZ) = v90 + 10;
                igi2_frame.nPitch += 2;
                *igi2_frame.v154 = 0;
                igi2_frame.aiVertex += 20;
                igi2_frame.v174 += 10;
                igi2_frame.p_iSplitVertex = igi2_frame.v151 + 10;
                igi2_frame.p_eSplitStatus = igi2_frame.v141 + 20;
                igi2_frame.p_nMorph = igi2_frame.v154 + 10;
                *(_DWORD *)(v86 + 4) = v89;
              }
              iTerrainMap = igi2_frame.v162;
            }
            else
            {
              *(_WORD *)((char *)&igi2_frame.v177 + igi2_frame.v156) = iSplitVertex;
            }
            v75 = igi2_frame.v156 + 2 < 0xA;
            ++igi2_frame.v160;
            igi2_frame.v158 += 2;
            igi2_frame.v156 += 2;
          }
          while ( v75 );
          v91 = igi2_frame.v183;
          v92 = igi2_frame.v179;
          v93 = TerrainRender_nNumEdges;
          v94 = (unsigned int *)(igi2_frame.v183 + 10);
          v95 = 0;
          igi2_frame.v163 = igi2_frame.v183 + 10;
          do
          {
            v96 = *v94;
            v97 = TerrainRender_atEdge[v96].eSplitStatus;
            v98 = 20 * v96 + 134125256;
            TerrainRender_atEdge[v96].iGlitchConnectVertex = v92;
            if ( (v97 & 4) != 0 )
            {
              TerrainRender_DrawGlitchPolyRecursive(v96, ptContext);
              v93 = TerrainRender_nNumEdges;
            }
            *(_BYTE *)(v98 + 19) |= *(&igi2_frame.v180 + v95++) | 8;
            v94 = (unsigned int *)(igi2_frame.v163 + 2);
            igi2_frame.v163 += 2;
          }
          while ( v95 < 4 );
          if ( v93 >= 70000 )
            goto LABEL_115;
          v99 = v93;
          TerrainRender_atEdge[v99].aiVertex[0] = HIWORD(igi2_frame.v178);
          TerrainRender_atEdge[v99].aiVertex[1] = v92;
          TerrainRender_atEdge[v99].aiChild[0] = -1;
          TerrainRender_atEdge[v99].aiChild[1] = -1;
          igi2_frame.v184 = v93;
          v100 = v93 + 1;
          TerrainRender_atEdge[v99].iSplitVertex = -1;
          TerrainRender_atEdge[v99].eSplitStatus = 0;
          TerrainRender_atEdge[v99].nMorph = 0;
          TerrainRender_nNumEdges = v100;
          if ( v100 >= 70000 )
            goto LABEL_115;
          v101 = HIWORD(igi2_frame.v177);
          v102 = v100;
          TerrainRender_atEdge[v102].aiVertex[0] = v92;
          TerrainRender_atEdge[v102].aiVertex[1] = v101;
          TerrainRender_atEdge[v102].aiChild[0] = -1;
          TerrainRender_atEdge[v102].aiChild[1] = -1;
          igi2_frame.v185 = v100;
          v103 = v100 + 1;
          TerrainRender_atEdge[v102].iSplitVertex = -1;
          TerrainRender_atEdge[v102].eSplitStatus = 0;
          TerrainRender_atEdge[v102].nMorph = 0;
          TerrainRender_nNumEdges = v103;
          if ( v103 >= 70000 )
            goto LABEL_115;
          v104 = v103;
          TerrainRender_atEdge[v104].aiVertex[0] = LOWORD(igi2_frame.v177);
          TerrainRender_atEdge[v104].aiVertex[1] = v92;
          TerrainRender_atEdge[v104].aiChild[0] = -1;
          TerrainRender_atEdge[v104].aiChild[1] = -1;
          igi2_frame.v214 = v103;
          v105 = v103 + 1;
          TerrainRender_atEdge[v104].iSplitVertex = -1;
          TerrainRender_atEdge[v104].eSplitStatus = 0;
          TerrainRender_atEdge[v104].nMorph = 0;
          TerrainRender_nNumEdges = v105;
          if ( v105 >= 70000 )
          {
LABEL_115:
            LDebug_Error("TerrainRender_nNumEdges < TERRAINRENDER_MAX_EDGES");
            abort();
          }
          v106 = LOWORD(igi2_frame.v178);
          v107 = 20 * v105;
          *(unsigned __int16 *)((char *)TerrainRender_atEdge[0].aiVertex + v107) = v92;
          *(unsigned __int16 *)((char *)&TerrainRender_atEdge[0].aiVertex[1] + v107) = v106;
          *(unsigned int *)((char *)TerrainRender_atEdge[0].aiChild + v107) = -1;
          *(unsigned int *)((char *)&TerrainRender_atEdge[0].aiChild[1] + v107) = -1;
          *(unsigned __int16 *)((char *)&TerrainRender_atEdge[0].aiVertex[2] + v107) = -1;
          *(&TerrainRender_atEdge[0].eSplitStatus + v107) = 0;
          *(unsigned __int16 *)((char *)&TerrainRender_atEdge[0].nMorph + v107) = 0;
          igi2_frame.v187 = *v91;
          igi2_frame.v200[2] = v91[5];
          igi2_frame.v200[3] = LOWORD(igi2_frame.v177);
          igi2_frame.v201[0] = LOWORD(igi2_frame.v177);
          igi2_frame.v201[1] = v91[6];
          v108 = v105;
          igi2_frame.iVertex2[0] = HIWORD(igi2_frame.v177);
          igi2_frame.v204 = HIWORD(igi2_frame.v177);
          LOWORD(v107) = v91[7];
          TerrainRender_nNumEdges = v105 + 1;
          v109 = v91[1];
          igi2_frame.v205 = v107;
          v110 = v91[2];
          v111 = *((unsigned __int8 *)v91 + 6);
          igi2_frame.v206 = igi2_frame.v178;
          igi2_frame.v208 = LOWORD(igi2_frame.v178);
          v112 = *((_DWORD *)v91 + 5);
          LODWORD(igi2_frame.v198) = v109;
          igi2_frame.v200[5] = HIWORD(igi2_frame.v178);
          v112 *= 20;
          igi2_frame.v209 = v91[8];
          v113 = *(unsigned int *)((char *)TerrainRender_atEdge[0].aiChild + v112);
          v114 = *(unsigned int *)((char *)&TerrainRender_atEdge[0].aiChild[1] + v112);
          igi2_frame.v217[9] = v113;
          igi2_frame.v217[10] = igi2_frame.v214;
          igi2_frame.v218[0] = igi2_frame.v184;
          v115 = *((_DWORD *)v91 + 8);
          igi2_frame.v218[2] = v114;
          v116 = *((_DWORD *)v91 + 6);
          v117 = *((_DWORD *)v91 + 7);
          igi2_frame.v200[4] = v92;
          igi2_frame.iVertex2[1] = v92;
          igi2_frame.v203 = v92;
          igi2_frame.v207 = v92;
          v115 *= 20;
          v116 *= 20;
          igi2_frame.v218[1] = *(unsigned int *)((char *)TerrainRender_atEdge[0].aiChild + v115);
          v118 = *(unsigned int *)((char *)TerrainRender_atEdge[0].aiChild + v116);
          v119 = *(unsigned int *)((char *)&TerrainRender_atEdge[0].aiChild[1] + v116);
          igi2_frame.v218[3] = v118;
          igi2_frame.v218[7] = v119;
          v120 = v110 >> 1;
          igi2_frame.v218[4] = igi2_frame.v185;
          v121 = v111 - 1;
          v122 = v117;
          v123 = TerrainRender_atEdge[v117].aiChild[1];
          igi2_frame.v218[5] = igi2_frame.v214;
          igi2_frame.v218[8] = v123;
          igi2_frame.v218[6] = igi2_frame.v185;
          igi2_frame.v218[9] = v108;
          igi2_frame.v218[11] = v108;
          v124 = TerrainRender_atEdge[v122].aiChild[0];
          v125 = *(unsigned int *)((char *)&TerrainRender_atEdge[0].aiChild[1] + v115);
          igi2_frame.v218[10] = igi2_frame.v184;
          igi2_frame.v218[12] = v124;
          igi2_frame.v218[13] = v125;
          v126 = igi2_frame.v218;
          for ( j = 0; j < 16; j += 4 )
          {
            TerrainRender_AddStackSquare(
              igi2_frame.v187 + v120 * igi2_frame.iVertex0[j / 2u - 1],
              igi2_frame.v198 + v120 * igi2_frame.iVertex0[j / 2u],
              v120,
              igi2_frame.v200[j + 2],
              igi2_frame.v200[j + 3],
              igi2_frame.v200[j + 4],
              igi2_frame.v200[j + 5],
              *(v126 - 2),
              *(v126 - 1),
              *v126,
              v126[1],
              v121,
              igi2_frame.v171);
            v126 += 4;
          }
LABEL_105:
          v37 = TerrainRender_nNumStackItems;
          if ( !TerrainRender_nNumStackItems )
          {
            v20 = TerrainRender_nNumVertices;
            break;
          }
        }
      }
      v133 = TerrainRender_tRenderChunkPool;
      TerrainRender_nNumVerticesProcessed += v20;
      for ( k = 0; k < 6; ++k )
      {
        for ( m = v133->nAllocated - 1; m >= 0; --m )
        {
          papxElement = v133->papxElement;
          if ( *((_DWORD *)papxElement[m] + 2) == k )
          {
            TerrainRender_DrawRenderChunk((struct TerrainRenderChunk_t *)papxElement[m]);
            v133 = TerrainRender_tRenderChunkPool;
          }
        }
      }
      TerrainRender_ptIndexBuffer->lpVtbl->Unlock(TerrainRender_ptIndexBuffer);
      TerrainRender_ptVertexBuffer->lpVtbl->Unlock(TerrainRender_ptVertexBuffer);
      Direct3D_tState.aptStreamData[1] = nullptr;
      Direct3D_tState.anStride[1] = 0;
      Direct3D_ptDevice->lpVtbl->SetStreamSource(Direct3D_ptDevice, 1u, nullptr, 0);
      Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SOFTWAREVERTEXPROCESSING, 0);
    }
  }
}

// source: e/3/pc/pc_terrainrender.c:3752  [size~]
void __cdecl TerrainRender_Open()
{
  int v0; // eax
  struct RenderStateBlock_t *v1; // ecx
  int nNumStates; // eax
  struct RenderStateBlock_t *v3; // ecx
  int v4; // eax
  struct RenderStateBlock_t *v5; // ecx
  int v6; // eax
  struct QObjectVector_s *v7; // esi

  v0 = 0;
  while ( RenderMode_atRenderModeMethod[v0].isAllocated )
  {
    if ( ++v0 >= 128 )
    {
      LDebug_Error("RenderMode: Failed to create new method '%s'", "DrawTerrain");
      abort();
    }
  }
  RenderMode_atRenderMode[Direct3D_eRenderMode].apfRenderModeMethod[v0] = (void (__cdecl *)(void *))TerrainRender_Draw;
  v1 = Direct3D_ptTextureStateBlock;
  RenderMode_atRenderModeMethod[v0].zName = "DrawTerrain";
  RenderMode_atRenderModeMethod[v0].isAllocated = 1;
  TerrainRender_eDrawTerrainMethod = v0;
  nNumStates = v1->nNumStates;
  v1->nNumStates = nNumStates + 1;
  v1->atRenderState[nNumStates].pfCallback = TerrainRender_SetTextureState;
  v3 = Direct3D_ptBlendStateBlock;
  TerrainRender_eTextureState = nNumStates;
  v4 = Direct3D_ptBlendStateBlock->nNumStates;
  Direct3D_ptBlendStateBlock->nNumStates = v4 + 1;
  v3->atRenderState[v4].pfCallback = TerrainRender_SetBlendState;
  v5 = Direct3D_ptGenericStateBlock;
  TerrainRender_eBlendState = v4;
  v6 = Direct3D_ptGenericStateBlock->nNumStates;
  Direct3D_ptGenericStateBlock->nNumStates = v6 + 1;
  v5->atRenderState[v6].pfCallback = TerrainRender_SetGenericState;
  TerrainRender_eGenericState = v6;
  Direct3D_RegisterCallback(TerrainRender_SetModeCallback, &Direct3D_ptSetModeCallback);
  Direct3D_RegisterCallback(TerrainRender_UnsetModeCallback, &Direct3D_ptUnsetModeCallback);
  Direct3D_RegisterCallback(TerrainRender_RestoreCallback, &Direct3D_ptRestoreCallback);
  Direct3D_RegisterCallback(TerrainRender_DestroyCallback, &Direct3D_ptDestroyCallback);
  v7 = (struct QObjectVector_s *)Mem_AllocFn(52, 4);
  v7->nSize = 0;
  v7->nAllocated = 0;
  v7->nReallocSize = 0;
  v7->papxElement = nullptr;
  v7->tMemPool.nBlocks = 0;
  v7->tMemPool.nAllocatedBlocks = 0;
  v7->tMemPool.nReAllocBlocks = 0;
  v7->tMemPool.tMemPoolFreeList.ptHead = nullptr;
  v7->tMemPool.tMemPoolSegmentList.ptHead = nullptr;
  v7->isStrictOrder = true;
  v7->nElementSize = 24;
  v7->tMemPool.nAlignment = 4;
  v7->tMemPool.nBlockSize = 24;
  MemPool_ReAlloc(&v7->tMemPool, 0x32u);
  QObjectVector_Realloc(v7, 0x32u);
  TerrainRender_tRenderChunkPool = v7;
  if ( AppContext_tAppContext.isClient > false )
  {
    TerrainRender_isWireframe = 1;
    if ( AppContext_tAppContext.isClient == 2 )
      dword_6B0364 = 0;
  }
}

// source: e/3/pc/pc_terrainrender.c:3782  [size]
void __cdecl TerrainRender_Close()
{
  TerrainRender_DeleteMaterialVertexBuffers();
  QObjectVector_Delete(TerrainRender_tRenderChunkPool);
  Direct3D_ptTextureStateBlock->atRenderState[TerrainRender_eTextureState].pfCallback = nullptr;
  Direct3D_ptBlendStateBlock->atRenderState[TerrainRender_eBlendState].pfCallback = nullptr;
  Direct3D_ptGenericStateBlock->atRenderState[TerrainRender_eGenericState].pfCallback = nullptr;
  RenderMode_atRenderModeMethod[TerrainRender_eDrawTerrainMethod].isAllocated = 0;
}

// source: e/3/pc/pc_terrainrender.c:3807  [size]
int __cdecl TerrainRender_GetDrawTerrainMethod()
{
  return TerrainRender_eDrawTerrainMethod;
}
