/* b/4/pc/pc_texture.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/4/pc/pc_texture.c:28  [size]
void __cdecl Texture_HardwareOpen()
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
  int v15; // ecx
  __int32 v16; // edx
  int v17; // ecx
  __int32 v18; // edx
  int v19; // ecx
  __int32 v20; // edx
  __int32 v21; // eax
  void **v22; // esi
  struct QVector_s *v23; // eax

  OffscreenBufferTexture_Open();
  v0 = 130 * Direct3D_eRenderMode;
  v1 = Texture_eDeAllocTextureMethod;
  RenderMode_atRenderMode[Direct3D_eRenderMode].apfRenderModeMethod[Texture_eAllocTextureMethod] = (void (__cdecl *)(void *))Direct3DTexture_Alloc;
  v2 = v0 + v1;
  v3 = Texture_eDownloadTextureMethod;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v2] = (void (__cdecl *)(void *))Direct3DTexture_DeAlloc;
  v4 = v0 + v3;
  v5 = Palette_eAllocPaletteMethod;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v4] = (void (__cdecl *)(void *))Direct3DTexture_Download;
  v6 = v0 + v5;
  v7 = Palette_eDeAllocPaletteMethod;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v6] = (void (__cdecl *)(void *))Direct3DTexture_AllocPalette;
  v8 = v0 + v7;
  v9 = Palette_eDownloadPaletteMethod;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v8] = (void (__cdecl *)(void *))Direct3DTexture_DeAllocPalette;
  v10 = v0 + v9;
  v11 = Texture_eRefreshTextureMethod;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v10] = (void (__cdecl *)(void *))Direct3DTexture_DownloadPalette;
  v12 = v0 + v11;
  v13 = Texture_eReloadTextureMethod;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v12] = (void (__cdecl *)(void *))Direct3DTexture_RefreshTextures;
  v14 = v0 + v13;
  v15 = Texture_eGetActiveTMUMethod;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v14] = (void (__cdecl *)(void *))Direct3DTexture_ReloadTextures;
  v16 = v0 + v15;
  v17 = Texture_eSetActiveTMUMethod;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v16] = (void (__cdecl *)(void *))Direct3DTexture_GetActiveTMU;
  v18 = v0 + v17;
  v19 = Texture_eGetTMUsMethod;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v18] = (void (__cdecl *)(void *))Direct3DTexture_SetActiveTMU;
  v20 = v0 + v19;
  v21 = Texture_eSetLODMethod + v0;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v20] = (void (__cdecl *)(void *))Direct3DTexture_GetTMUs;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v21] = (void (__cdecl *)(void *))Direct3DTexture_SetLOD;
  v22 = (void **)Mem_AllocFn(4000, 4);
  v23 = (struct QVector_s *)Mem_AllocFn(24, 4);
  v23->tPrivate.papxElement = v22;
  v23->tPrivate.nArraySize = 1000;
  v23->tPrivate.nReallocSize = 0;
  v23->tPrivate.nElements = 0;
  v23->tPrivate.isPrivateMem = false;
  v23->tPrivate.isStrictOrder = false;
  Direct3DTexture_ptPalettedTextureContainer = v23;
}

// source: b/4/pc/pc_texture.c:42  [size]
void __cdecl Texture_HardwareClose()
{
  QVector_Delete(Direct3DTexture_ptPalettedTextureContainer);
}
