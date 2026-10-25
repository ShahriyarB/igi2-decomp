/* b/4/pc/pc_offscreenbuffertexture.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/4/pc/pc_offscreenbuffertexture.c:47  [anchor-mhash]
void __cdecl OffscreenBufferTexture_Alloc(struct AllocTextureContext_s *ptAllocTextureContext)
{
  struct TexInfo_s *ptTexInfo; // ebp
  void *v2; // eax

  ptTexInfo = ptAllocTextureContext->ptTexInfo;
  v2 = Mem_AllocFn(ptAllocTextureContext->nHeight * ptAllocTextureContext->nPitch, 4);
  ptTexInfo->pxData = v2;
  qmemcpy(v2, ptAllocTextureContext->pxData, ptAllocTextureContext->nHeight * ptAllocTextureContext->nPitch);
  ptTexInfo->nWidth = ptAllocTextureContext->nWidth;
  ptTexInfo->nHeight = ptAllocTextureContext->nHeight;
  ptTexInfo->nPitch = ptAllocTextureContext->nPitch;
  ptTexInfo->nType = ptAllocTextureContext->nType;
}

// source: b/4/pc/pc_offscreenbuffertexture.c:77  [size]
void __cdecl OffscreenBufferTexture_Download(struct AllocTextureContext_s *ptDownloadTextureContext)
{
  ;
}

// source: b/4/pc/pc_offscreenbuffertexture.c:103  [size]
void __cdecl OffscreenBufferTexture_DeAlloc(struct TexInfo_s *ptTexInfo)
{
  void *pxData; // eax
  int v2; // esi

  pxData = ptTexInfo->pxData;
  if ( pxData )
  {
    v2 = *(_DWORD *)(((int)pxData - 4) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v2);
    memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
    free((void *)v2);
  }
  ptTexInfo->pxData = nullptr;
}

// source: b/4/pc/pc_offscreenbuffertexture.c:120  [anchor-mhash]
void __cdecl OffscreenBufferTexture_AllocPalette(struct AllocPaletteContext_s *ptAllocPaletteContext)
{
  struct PalInfo *ptPalInfo; // eax
  unsigned __int16 *v2; // ecx
  char *v3; // eax
  unsigned __int8 v4; // bl
  __int16 v5; // si
  unsigned __int8 v6; // bl
  unsigned __int16 v7; // dx
  __int16 v8; // si
  __int16 v9; // dx
  __int16 v10; // si
  unsigned __int8 v11; // bl
  unsigned __int16 v12; // dx
  __int16 v13; // si
  __int16 v14; // dx
  __int16 v15; // si
  unsigned __int8 v16; // bl
  unsigned __int16 v17; // dx
  __int16 v18; // si
  __int16 v19; // dx
  __int16 v20; // si
  unsigned __int8 v21; // bl
  unsigned __int16 v22; // dx
  __int16 v23; // si
  __int16 v24; // dx
  __int16 v25; // si
  unsigned __int8 v26; // bl
  unsigned __int16 v27; // dx
  __int16 v28; // si
  __int16 v29; // dx
  __int16 v30; // si
  unsigned __int8 v31; // bl
  unsigned __int16 v32; // dx
  __int16 v33; // si

  ptPalInfo = ptAllocPaletteContext->ptPalInfo;
  while ( OffscreenBufferTexture_aisPaletteAllocated[0] )
    ;
  OffscreenBufferTexture_aisPaletteAllocated[0] = 1;
  ptPalInfo->nPalette = 1;
  ptPalInfo->pxPalette = OffscreenBufferTexture_aanPalette;
  qmemcpy(OffscreenBufferTexture_aanPaletteSourceData, ptAllocPaletteContext->pxData, 0x400u);
  v2 = &OffscreenBufferTexture_aanPalette[0][1];
  v3 = (char *)&OffscreenBufferTexture_aanPaletteSourceData[0][0] + 1;
  do
  {
    v4 = (unsigned __int8)v3[3] >> 3;
    *(v2 - 1) = ((unsigned __int8)*(v3 - 1) >> 3) | (8 * (*v3 & 0xFC | (32 * (v3[1] & 0xF8))));
    v5 = v4;
    v6 = (unsigned __int8)v3[7] >> 3;
    v7 = v5 | (8 * (v3[4] & 0xFC | (32 * (v3[5] & 0xF8))));
    v8 = (unsigned __int8)v3[8];
    *v2 = v7;
    v9 = 8 * (v8 & 0xFFFC | (32 * (v3[9] & 0xF8)));
    v10 = v6;
    v11 = (unsigned __int8)v3[11] >> 3;
    v12 = v10 | v9;
    v13 = (unsigned __int8)v3[12];
    v2[1] = v12;
    v14 = 8 * (v13 & 0xFFFC | (32 * (v3[13] & 0xF8)));
    v15 = v11;
    v16 = (unsigned __int8)v3[15] >> 3;
    v17 = v15 | v14;
    v18 = (unsigned __int8)v3[16];
    v2[2] = v17;
    v19 = v18 & 0xFFFC | (32 * (v3[17] & 0xF8));
    v20 = v16;
    v21 = (unsigned __int8)v3[19] >> 3;
    v22 = v20 | (8 * v19);
    v23 = (unsigned __int8)v3[20];
    v2[3] = v22;
    v24 = v23 | (32 * (v3[21] & 0xF8));
    v25 = v21;
    v26 = v3[23];
    v27 = v25 | (8 * (v24 & 0xFFFC));
    v28 = (unsigned __int8)v3[24];
    v2[4] = v27;
    v29 = 8 * (v28 & 0xFFFC | (32 * (v3[25] & 0xF8)));
    v30 = v26 >> 3;
    v31 = (unsigned __int8)v3[27] >> 3;
    v3 += 32;
    v2 += 8;
    v32 = v30 | v29;
    v33 = (unsigned __int8)*(v3 - 4);
    *(v2 - 3) = v32;
    *(v2 - 2) = v31 | (unsigned __int16)(8 * (v33 & 0xFFFC | (32 * (*(v3 - 3) & 0xF8))));
  }
  while ( (int)v3 < 140967713 );
}

// source: b/4/pc/pc_offscreenbuffertexture.c:168  [size]
void __cdecl OffscreenBufferTexture_DownloadPalette(struct PalInfo *ptPalInfo)
{
  ;
}

// source: b/4/pc/pc_offscreenbuffertexture.c:182  [size]
void __cdecl OffscreenBufferTexture_DeAllocPalette(struct PalInfo *ptPalInfo)
{
  *(_BYTE *)(ptPalInfo->nPalette + 137641991) = 0;
}

// source: b/4/pc/pc_offscreenbuffertexture.c:198  [anchor-hash]
void __cdecl OffscreenBufferTexture_Open()
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

  v0 = 130 * dword_73D31C;
  v1 = Texture_eDeAllocTextureMethod;
  RenderMode_atRenderMode[dword_73D31C].apfRenderModeMethod[Texture_eAllocTextureMethod] = (void (__cdecl *)(void *))OffscreenBufferTexture_Alloc;
  v2 = v0 + v1;
  v3 = Texture_eDownloadTextureMethod;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v2] = (void (__cdecl *)(void *))OffscreenBufferTexture_DeAlloc;
  v4 = v0 + v3;
  v5 = Palette_eAllocPaletteMethod;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v4] = (void (__cdecl *)(void *))OffscreenBufferTexture_Download;
  v6 = v0 + v5;
  v7 = Palette_eDeAllocPaletteMethod;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v6] = (void (__cdecl *)(void *))OffscreenBufferTexture_AllocPalette;
  v8 = v0 + v7;
  v9 = Palette_eDownloadPaletteMethod;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v8] = (void (__cdecl *)(void *))OffscreenBufferTexture_DeAllocPalette;
  *(_DWORD *)OffscreenBufferTexture_aisPaletteAllocated = 0;
  *((_DWORD *)&RenderMode_atRenderMode[0].apfRenderModeMethod[v9] + v0) = OffscreenBufferTexture_DownloadPalette;
  *(_DWORD *)&OffscreenBufferTexture_aisPaletteAllocated[4] = 0;
}

// source: b/4/pc/pc_offscreenbuffertexture.c:225  [size]
void __cdecl OffscreenBufferTexture_Close()
{
  ;
}
