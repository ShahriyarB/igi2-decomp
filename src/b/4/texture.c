/* b/4/texture.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/4/texture.c:161  [anchor-mhash]
int __cdecl Texture_GetNumberOfILFTextureChunks(void *pxContainer)
{
  unsigned int v1; // ebp
  unsigned int v2; // ebx
  unsigned int v3; // ecx
  char *v4; // ecx
  int v5; // edx
  unsigned int v6; // esi
  int v7; // edx
  int i; // [esp+Ch] [ebp-8h]

  i = 0;
  if ( !pxContainer )
    return i;
  v1 = *((_DWORD *)pxContainer + 1);
  if ( !v1 )
    return i;
  v2 = *((_DWORD *)pxContainer + 2);
  if ( (v2 & ~(v2 - 1)) != v2 )
  {
    ILF_nLastError = 1;
    return 0;
  }
  v3 = ~(v2 - 1) & (v2 + 19);
  if ( v3 >= v1 )
    return i;
  v4 = (char *)pxContainer + v3;
  if ( !v4 )
    return i;
  while ( 1 )
  {
    if ( *(_DWORD *)v4 != 1213744468 )
      goto LABEL_17;
    v5 = *((_DWORD *)v4 + 3);
    if ( !v5 )
      return 0;
    v4 += v5;
    if ( !v4 || *(_DWORD *)v4 != 1497648962 )
      return 0;
    if ( (v2 & ~(v2 - 1)) != v2 )
      break;
    if ( v4 - (_BYTE *)pxContainer >= v1 )
      break;
    v6 = *((_DWORD *)v4 + 2);
    if ( (v6 & ~(v6 - 1)) != v6 || v6 > v2 )
      break;
    if ( !*((_DWORD *)v4 + 1) || !((char *)pxContainer + (~(v6 - 1) & (v6 + v4 - (_BYTE *)pxContainer + 15))) )
      return 0;
    ++i;
LABEL_17:
    v7 = *((_DWORD *)v4 + 3);
    if ( v7 )
    {
      v4 += v7;
      if ( v4 )
        continue;
    }
    return i;
  }
  ILF_nLastError = 1;
  return 0;
}

// source: b/4/texture.c:204  [size]
int __cdecl Texture_AllocILFTextureChunks(
        void *pxContainer,
        struct TexInfo_s *atTexInfo,
        int nTexInfoArraySize,
        struct PalInfo *ptPalInfo)
{
  char *v4; // ebx
  int v5; // ebp
  unsigned int v6; // edx
  int v7; // eax
  unsigned int v8; // eax
  char *v9; // edi
  unsigned int v10; // ebp
  unsigned int v11; // eax
  char *v12; // ecx
  int v14; // eax
  unsigned int v15; // esi
  unsigned int v16; // eax
  unsigned int v17; // edx
  unsigned int v18; // ebx
  char *v19; // eax
  bool v20; // cc
  int v21; // eax
  int i; // [esp+10h] [ebp-Ch]

  v4 = (char *)pxContainer;
  v5 = 0;
  i = 0;
  if ( pxContainer )
  {
    v6 = *((_DWORD *)pxContainer + 1);
    if ( v6 )
    {
      v7 = *((_DWORD *)pxContainer + 2);
      if ( (v7 & ~(v7 - 1)) == v7 )
      {
        v8 = ~(v7 - 1) & (v7 + 19);
        if ( v8 < v6 )
        {
          v9 = (char *)pxContainer + v8;
          if ( (char *)pxContainer + v8 )
          {
            while ( 1 )
            {
              if ( v5 >= nTexInfoArraySize )
                return v5;
              if ( *(_DWORD *)v9 == 1213744468 )
                break;
LABEL_38:
              v21 = *((_DWORD *)v9 + 3);
              if ( !v21 )
                return v5;
              v9 += v21;
              if ( !v9 )
                return v5;
            }
            v10 = *((_DWORD *)v4 + 2);
            if ( (v10 & ~(v10 - 1)) == v10
              && (unsigned int)(v9 - v4) < *((_DWORD *)v4 + 1)
              && (v11 = *((_DWORD *)v9 + 2), (v11 & ~(v11 - 1)) == v11)
              && v11 <= v10 )
            {
              if ( *((_DWORD *)v9 + 1) )
              {
                v12 = &v4[~(v11 - 1) & (v11 + v9 - v4 + 15)];
LABEL_18:
                v14 = *((_DWORD *)v9 + 3);
                if ( v14 )
                  v9 += v14;
                else
                  v9 = nullptr;
                if ( !v12 || !v9 || *(_DWORD *)v9 != 1497648962 )
                  return 0;
                if ( (v10 & ~(v10 - 1)) != v10
                  || (v15 = *((_DWORD *)v4 + 1), v16 = v9 - v4, v9 - v4 >= v15)
                  || (v17 = *((_DWORD *)v9 + 2), (v17 & ~(v17 - 1)) != v17)
                  || v17 > v10 )
                {
                  ILF_nLastError = 1;
                  return 0;
                }
                if ( !*((_DWORD *)v9 + 1) || !((char *)pxContainer + (~(v17 - 1) & (v17 + v16 + 15))) )
                  return 0;
                v18 = *((_DWORD *)pxContainer + 2);
                if ( (v18 & ~(v18 - 1)) == v18 && v16 < v15 && (v17 & ~(v17 - 1)) == v17 )
                {
                  v20 = v17 <= v18;
                  v4 = (char *)pxContainer;
                  if ( v20 )
                  {
                    v19 = (char *)pxContainer + (~(v17 - 1) & (v17 + v16 + 15));
                  }
                  else
                  {
                    ILF_nLastError = 1;
                    v19 = nullptr;
                  }
                }
                else
                {
                  v4 = (char *)pxContainer;
                  ILF_nLastError = 1;
                  v19 = nullptr;
                }
                Texture_AllocAndDownload(
                  atTexInfo,
                  ptPalInfo,
                  *((unsigned __int16 *)v12 + 9) * *((unsigned __int16 *)v12 + 11) / 8,
                  *((unsigned __int16 *)v12 + 7),
                  *((unsigned __int16 *)v12 + 8),
                  *(_DWORD *)v12,
                  *((unsigned __int16 *)v12 + 6),
                  *((_DWORD *)v12 + 1) | 1,
                  v19);
                v5 = ++i;
                ++atTexInfo;
                goto LABEL_38;
              }
            }
            else
            {
              ILF_nLastError = 1;
            }
            v12 = nullptr;
            goto LABEL_18;
          }
        }
      }
      else
      {
        ILF_nLastError = 1;
      }
    }
  }
  return v5;
}

// source: b/4/pc/pc_direct3dtexture.c:1113  [layout]
void __cdecl Texture_Open()
{
  int v0; // eax
  int v1; // eax
  int v2; // eax
  int v3; // eax
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  enum RenderMode_enum v8; // eax
  enum RenderMode_enum v9; // eax
  enum RenderMode_enum v10; // eax
  __int32 v11; // eax
  int v12; // ecx
  __int32 v13; // edx
  int v14; // ecx
  __int32 v15; // edx
  int v16; // ecx
  __int32 v17; // edx
  int v18; // ecx
  __int32 v19; // edx
  int v20; // ecx
  __int32 v21; // edx
  enum RenderMode_enum v22; // ecx
  __int32 v23; // edx
  enum RenderMode_enum v24; // ecx
  __int32 v25; // edx
  int v26; // ecx
  __int32 v27; // edx
  int v28; // ecx
  __int32 v29; // edx
  int v30; // ecx
  __int32 v31; // edx
  __int32 v32; // eax
  void **v33; // esi
  struct QVector_s *v34; // eax

  Texture_tActiveTextureFilterContext.tAmbientColour.vX = 0.0;
  Texture_tActiveTextureFilterContext.tAmbientColour.vY = 0.0;
  Texture_tActiveTextureFilterContext.tAmbientColour.vZ = 0.0;
  Texture_tActiveTextureFilterContext.tScale.vX = 1.0;
  Texture_tActiveTextureFilterContext.tScale.vY = 1.0;
  Texture_tActiveTextureFilterContext.tScale.vZ = 1.0;
  Texture_tActiveTextureFilterContext.vGamma = 1.0;
  v0 = 0;
  while ( RenderMode_atRenderModeMethod[v0].isAllocated )
  {
    if ( ++v0 >= 128 )
    {
      LDebug_Error("RenderMode: Failed to create new method '%s'", "AllocTexture");
      goto LABEL_5;
    }
  }
  RenderMode_atRenderModeMethod[v0].zName = "AllocTexture";
  RenderMode_atRenderModeMethod[v0].isAllocated = 1;
  Texture_eAllocTextureMethod = v0;
  v1 = 0;
  while ( RenderMode_atRenderModeMethod[v1].isAllocated )
  {
    if ( ++v1 >= 128 )
    {
      LDebug_Error("RenderMode: Failed to create new method '%s'", "DeAllocTexture");
      goto LABEL_5;
    }
  }
  RenderMode_atRenderModeMethod[v1].zName = "DeAllocTexture";
  RenderMode_atRenderModeMethod[v1].isAllocated = 1;
  Texture_eDeAllocTextureMethod = v1;
  v2 = 0;
  while ( RenderMode_atRenderModeMethod[v2].isAllocated )
  {
    if ( ++v2 >= 128 )
    {
      LDebug_Error("RenderMode: Failed to create new method '%s'", "DownloadTexture");
      goto LABEL_5;
    }
  }
  RenderMode_atRenderModeMethod[v2].zName = "DownloadTexture";
  RenderMode_atRenderModeMethod[v2].isAllocated = 1;
  Texture_eDownloadTextureMethod = v2;
  v3 = 0;
  while ( RenderMode_atRenderModeMethod[v3].isAllocated )
  {
    if ( ++v3 >= 128 )
    {
      LDebug_Error("RenderMode: Failed to create new method '%s'", "BeginTextureList");
      goto LABEL_5;
    }
  }
  RenderMode_atRenderModeMethod[v3].zName = "BeginTextureList";
  RenderMode_atRenderModeMethod[v3].isAllocated = 1;
  Texture_eBeginTextureListMethod = v3;
  v4 = 0;
  while ( RenderMode_atRenderModeMethod[v4].isAllocated )
  {
    if ( ++v4 >= 128 )
    {
      LDebug_Error("RenderMode: Failed to create new method '%s'", "EndTextureList");
      goto LABEL_5;
    }
  }
  RenderMode_atRenderModeMethod[v4].zName = "EndTextureList";
  RenderMode_atRenderModeMethod[v4].isAllocated = 1;
  Texture_eEndTextureListMethod = v4;
  v5 = 0;
  while ( RenderMode_atRenderModeMethod[v5].isAllocated )
  {
    if ( ++v5 >= 128 )
    {
      LDebug_Error("RenderMode: Failed to create new method '%s'", "GetTMUs");
      goto LABEL_5;
    }
  }
  RenderMode_atRenderModeMethod[v5].zName = "GetTMUs";
  RenderMode_atRenderModeMethod[v5].isAllocated = 1;
  Texture_eGetTMUsMethod = v5;
  v6 = 0;
  while ( RenderMode_atRenderModeMethod[v6].isAllocated )
  {
    if ( ++v6 >= 128 )
    {
      LDebug_Error("RenderMode: Failed to create new method '%s'", "SetActiveTMU");
      goto LABEL_5;
    }
  }
  RenderMode_atRenderModeMethod[v6].zName = "SetActiveTMU";
  RenderMode_atRenderModeMethod[v6].isAllocated = 1;
  Texture_eSetActiveTMUMethod = v6;
  v7 = 0;
  while ( RenderMode_atRenderModeMethod[v7].isAllocated )
  {
    if ( ++v7 >= 128 )
    {
      LDebug_Error("RenderMode: Failed to create new method '%s'", "GetActiveTMU");
      goto LABEL_5;
    }
  }
  RenderMode_atRenderModeMethod[v7].zName = "GetActiveTMU";
  RenderMode_atRenderModeMethod[v7].isAllocated = 1;
  Texture_eGetActiveTMUMethod = v7;
  v8 = APPCONTEXT_RENDER_MODE_SOFTWARE;
  while ( RenderMode_atRenderModeMethod[v8].isAllocated )
  {
    if ( ++v8 >= 128 )
    {
      LDebug_Error("RenderMode: Failed to create new method '%s'", "RefreshTexture");
      goto LABEL_5;
    }
  }
  RenderMode_atRenderModeMethod[v8].zName = "RefreshTexture";
  RenderMode_atRenderModeMethod[v8].isAllocated = 1;
  Texture_eRefreshTextureMethod = v8;
  v9 = APPCONTEXT_RENDER_MODE_SOFTWARE;
  while ( RenderMode_atRenderModeMethod[v9].isAllocated )
  {
    if ( ++v9 >= 128 )
    {
      LDebug_Error("RenderMode: Failed to create new method '%s'", "ReloadTexture");
      goto LABEL_5;
    }
  }
  RenderMode_atRenderModeMethod[v9].zName = "ReloadTexture";
  RenderMode_atRenderModeMethod[v9].isAllocated = 1;
  Texture_eReloadTextureMethod = v9;
  v10 = APPCONTEXT_RENDER_MODE_SOFTWARE;
  while ( RenderMode_atRenderModeMethod[v10].isAllocated )
  {
    if ( ++v10 >= 128 )
    {
      LDebug_Error("RenderMode: Failed to create new method '%s'", "SetLOD");
LABEL_5:
      abort();
    }
  }
  RenderMode_atRenderModeMethod[v10].zName = "SetLOD";
  RenderMode_atRenderModeMethod[v10].isAllocated = 1;
  Texture_eSetLODMethod = v10;
  OffscreenBufferTexture_Open();
  v11 = 130 * Direct3D_eRenderMode;
  v12 = Texture_eDeAllocTextureMethod;
  RenderMode_atRenderMode[Direct3D_eRenderMode].apfRenderModeMethod[Texture_eAllocTextureMethod] = (void (__cdecl *)(void *))Direct3DTexture_Alloc;
  v13 = v11 + v12;
  v14 = Texture_eDownloadTextureMethod;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v13] = (void (__cdecl *)(void *))Direct3DTexture_DeAlloc;
  v15 = v11 + v14;
  v16 = Palette_eAllocPaletteMethod;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v15] = (void (__cdecl *)(void *))Direct3DTexture_Download;
  v17 = v11 + v16;
  v18 = Palette_eDeAllocPaletteMethod;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v17] = (void (__cdecl *)(void *))Direct3DTexture_AllocPalette;
  v19 = v11 + v18;
  v20 = Palette_eDownloadPaletteMethod;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v19] = (void (__cdecl *)(void *))Direct3DTexture_DeAllocPalette;
  v21 = v11 + v20;
  v22 = Texture_eRefreshTextureMethod;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v21] = (void (__cdecl *)(void *))Direct3DTexture_DownloadPalette;
  v23 = v11 + v22;
  v24 = Texture_eReloadTextureMethod;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v23] = (void (__cdecl *)(void *))Direct3DTexture_RefreshTextures;
  v25 = v11 + v24;
  v26 = Texture_eGetActiveTMUMethod;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v25] = (void (__cdecl *)(void *))Direct3DTexture_ReloadTextures;
  v27 = v11 + v26;
  v28 = Texture_eSetActiveTMUMethod;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v27] = (void (__cdecl *)(void *))Direct3DTexture_GetActiveTMU;
  v29 = v11 + v28;
  v30 = Texture_eGetTMUsMethod;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v29] = (void (__cdecl *)(void *))Direct3DTexture_SetActiveTMU;
  v31 = v11 + v30;
  v32 = Texture_eSetLODMethod + v11;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v31] = (void (__cdecl *)(void *))Direct3DTexture_GetTMUs;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v32] = (void (__cdecl *)(void *))Direct3DTexture_SetLOD;
  v33 = (void **)Mem_AllocFn(4000, 4);
  v34 = (struct QVector_s *)Mem_AllocFn(24, 4);
  v34->tPrivate.papxElement = v33;
  v34->tPrivate.nArraySize = 1000;
  v34->tPrivate.nReallocSize = 0;
  v34->tPrivate.nElements = 0;
  v34->tPrivate.isPrivateMem = false;
  v34->tPrivate.isStrictOrder = false;
  Direct3DTexture_ptPalettedTextureContainer = v34;
}

// source: b/4/texture.c:287  [size]
void __cdecl Texture_Close()
{
  int v0; // edx
  int v1; // ecx
  int v2; // edx
  int v3; // ecx
  int v4; // edx
  int v5; // ecx
  int v6; // edx
  enum RenderMode_enum v7; // ecx
  enum RenderMode_enum v8; // edx
  enum RenderMode_enum v9; // ecx

  QVector_Delete(Direct3DTexture_ptPalettedTextureContainer);
  v0 = Texture_eDeAllocTextureMethod;
  RenderMode_atRenderModeMethod[Texture_eAllocTextureMethod].isAllocated = 0;
  v1 = Texture_eDownloadTextureMethod;
  RenderMode_atRenderModeMethod[v0].isAllocated = 0;
  v2 = Texture_eBeginTextureListMethod;
  RenderMode_atRenderModeMethod[v1].isAllocated = 0;
  v3 = Texture_eEndTextureListMethod;
  RenderMode_atRenderModeMethod[v2].isAllocated = 0;
  v4 = Texture_eGetTMUsMethod;
  RenderMode_atRenderModeMethod[v3].isAllocated = 0;
  v5 = Texture_eSetActiveTMUMethod;
  RenderMode_atRenderModeMethod[v4].isAllocated = 0;
  v6 = Texture_eGetActiveTMUMethod;
  RenderMode_atRenderModeMethod[v5].isAllocated = 0;
  v7 = Texture_eReloadTextureMethod;
  RenderMode_atRenderModeMethod[v6].isAllocated = 0;
  v8 = Texture_eRefreshTextureMethod;
  RenderMode_atRenderModeMethod[v7].isAllocated = 0;
  v9 = Texture_eSetLODMethod;
  RenderMode_atRenderModeMethod[v8].isAllocated = 0;
  RenderMode_atRenderModeMethod[v9].isAllocated = 0;
}

// source: b/4/texture.c:334  [anchor-hash]
struct TexInfo_s *__cdecl Texture_Free(struct TexInfo_s *ptTexInfo)
{
  if ( AppContext_tAppContext.isMainMenu == false )
    RenderMode_atRenderMode[ptTexInfo->eRenderMode].apfRenderModeMethod[Texture_eDeAllocTextureMethod](ptTexInfo);
  memset(ptTexInfo, 0, sizeof(struct TexInfo_s));
  return nullptr;
}

// source: b/4/texture.c:357  [size]
void __cdecl Texture_AllocAndDownloadFromFile(
        struct TexInfo_s *ptTexInfo,
        struct PalInfo *ptPalInfo,
        char *zFilename,
        void *pxFile,
        unsigned int nSize,
        unsigned int bFlags)
{
  #pragma pack(push, 1)
  union
  {
    struct { unsigned int *pbData; };
    struct { char igi2_o1[4]; int nHeight; };
    struct { char igi2_o2[8]; int nWidth; };
    struct { char igi2_o3[12]; struct AllocTextureContext_s tAllocTextureContext; };
    char igi2_extent[68];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  unsigned int *v7; // edi
  int v8; // esi

  if ( strstr(zFilename, ".tga") )
  {
    if ( TGA_Read(&igi2_frame.pbData, &igi2_frame.nWidth, &igi2_frame.nHeight, (char *)zFilename) )
    {
      v7 = igi2_frame.pbData;
      Texture_AllocAndDownload(
        ptTexInfo,
        ptPalInfo,
        4 * igi2_frame.nWidth,
        igi2_frame.nWidth,
        igi2_frame.nHeight,
        3,
        0,
        (unsigned int)&TerrainRender_atEdge[4623].iSplitVertex,
        igi2_frame.pbData);
      if ( v7 )
      {
        v8 = *(_DWORD *)((unsigned int)(v7 - 1) & 0xFFFFFFFC);
        --Mem_nCurrentAllocations;
        Node_Remove((_DWORD **)v8);
        memset(*(void **)(v8 + 8), 0xCDu, *(_DWORD *)(v8 + 16));
        free((void *)v8);
      }
    }
  }
  else
  {
    memset(&igi2_frame.tAllocTextureContext, 0, sizeof(igi2_frame.tAllocTextureContext));
    igi2_frame.tAllocTextureContext.zNameOfFileInMemory = zFilename;
    igi2_frame.tAllocTextureContext.ptPalInfo = ptPalInfo;
    igi2_frame.tAllocTextureContext.ptTexInfo = ptTexInfo;
    igi2_frame.tAllocTextureContext.bFlags = bFlags | (Texture_isCompression == false);
    igi2_frame.tAllocTextureContext.nSizeOfFileInMemory = nSize;
    igi2_frame.tAllocTextureContext.pxFileInMemory = pxFile;
    if ( AppContext_tAppContext.isMainMenu )
    {
      ptTexInfo->nWidth = 0;
      ptTexInfo->nHeight = 0;
      ptTexInfo->nPitch = 0;
      ptTexInfo->nType = 0;
      ptTexInfo->vTransparency = 0.0;
      ptTexInfo->bFlags = 0;
      ptTexInfo->pxData = nullptr;
    }
    else
    {
      RenderMode_tActiveRenderMode.apfRenderModeMethod[Texture_eAllocTextureMethod](&igi2_frame.tAllocTextureContext);
      RenderMode_tActiveRenderMode.apfRenderModeMethod[Texture_eDownloadTextureMethod](&igi2_frame.tAllocTextureContext);
    }
  }
}

// source: b/4/texture.c:443  [size]
void __cdecl Texture_Alloc(
        struct TexInfo_s *ptTexInfo,
        struct PalInfo *ptPalInfo,
        int nPitch,
        int nWidth,
        int nHeight,
        int nType,
        int nTextureScaleFactor,
        unsigned int bFlags)
{
  struct AllocTextureContext_s tAllocTextureContext; // [esp+8h] [ebp-38h] BYREF

  ptTexInfo->eRenderMode = RenderMode_eActiveRenderMode;
  memset(&tAllocTextureContext, 0, sizeof(tAllocTextureContext));
  tAllocTextureContext.nTextureScaleFactor = nTextureScaleFactor;
  tAllocTextureContext.ptPalInfo = ptPalInfo;
  tAllocTextureContext.ptTexInfo = ptTexInfo;
  tAllocTextureContext.nWidth = nWidth;
  tAllocTextureContext.nHeight = nHeight;
  tAllocTextureContext.nPitch = nPitch;
  tAllocTextureContext.nType = nType;
  tAllocTextureContext.pxData = nullptr;
  tAllocTextureContext.bFlags = bFlags;
  if ( AppContext_tAppContext.isMainMenu )
  {
    ptTexInfo->nHeight = nHeight;
    ptTexInfo->nWidth = nWidth;
    ptTexInfo->nPitch = nPitch;
    ptTexInfo->nType = nType;
    ptTexInfo->vTransparency = 0.0;
    ptTexInfo->bFlags = bFlags;
  }
  else
  {
    RenderMode_tActiveRenderMode.apfRenderModeMethod[Texture_eAllocTextureMethod](&tAllocTextureContext);
  }
}

// source: b/4/texture.c:501  [size]
void __cdecl Texture_AllocAndDownload(
        struct TexInfo_s *ptTexInfo,
        struct PalInfo *ptPalInfo,
        int nPitch,
        int nWidth,
        int nHeight,
        int nType,
        int nTextureScaleFactor,
        unsigned int bFlags,
        void *pxData)
{
  struct AllocTextureContext_s tAllocTextureContext; // [esp+4h] [ebp-38h] BYREF

  ptTexInfo->eRenderMode = RenderMode_eActiveRenderMode;
  memset(&tAllocTextureContext, 0, sizeof(tAllocTextureContext));
  tAllocTextureContext.ptPalInfo = ptPalInfo;
  tAllocTextureContext.nPitch = nPitch;
  tAllocTextureContext.ptTexInfo = ptTexInfo;
  tAllocTextureContext.nWidth = nWidth;
  tAllocTextureContext.nHeight = nHeight;
  tAllocTextureContext.nType = nType;
  tAllocTextureContext.pxData = pxData;
  tAllocTextureContext.bFlags = bFlags | (Texture_isCompression == false);
  tAllocTextureContext.nTextureScaleFactor = nTextureScaleFactor;
  if ( AppContext_tAppContext.isMainMenu == false )
  {
    RenderMode_tActiveRenderMode.apfRenderModeMethod[Texture_eAllocTextureMethod](&tAllocTextureContext);
    RenderMode_tActiveRenderMode.apfRenderModeMethod[Texture_eDownloadTextureMethod](&tAllocTextureContext);
  }
}

// source: b/4/texture.c:547  [size]
void __cdecl Texture_Download(
        struct TexInfo_s *ptTexInfo,
        struct PalInfo *ptPalInfo,
        int nPitch,
        int nWidth,
        int nHeight,
        int nType,
        void *pxData)
{
  unsigned int bFlags; // ecx
  struct AllocTextureContext_s tDownloadTextureContext; // [esp+4h] [ebp-38h] BYREF

  memset(&tDownloadTextureContext, 0, sizeof(tDownloadTextureContext));
  tDownloadTextureContext.ptPalInfo = ptPalInfo;
  tDownloadTextureContext.nHeight = nHeight;
  tDownloadTextureContext.nType = nType;
  tDownloadTextureContext.nWidth = nWidth;
  tDownloadTextureContext.nPitch = nPitch;
  tDownloadTextureContext.pxData = pxData;
  bFlags = ptTexInfo->bFlags;
  tDownloadTextureContext.ptTexInfo = ptTexInfo;
  tDownloadTextureContext.nTextureScaleFactor = 0;
  tDownloadTextureContext.bFlags = bFlags | (Texture_isCompression == false);
  if ( AppContext_tAppContext.isMainMenu == false )
    RenderMode_tActiveRenderMode.apfRenderModeMethod[Texture_eDownloadTextureMethod](&tDownloadTextureContext);
}

// source: b/4/texture.c:588  [anchor-callee]
char *__cdecl Texture_Load(
        struct TexInfo_s *ptTexInfo,
        struct PalInfo *ptPalInfo,
        char *zFilename)
{
  char *v4; // ecx
  unsigned int v5; // eax
  _DWORD *v6; // eax
  void *v7; // eax
  char *result; // eax
  unsigned int nSize; // [esp+Ch] [ebp-4h] BYREF

  if ( strstr(zFilename, ".tex") )
  {
    if ( ptPalInfo )
      ptPalInfo->eRenderMode = -1;
    if ( Resource_IsLoadedInternal(zFilename, (struct Resource_s **)&nSize) )
    {
      v5 = nSize;
      *(_DWORD *)(nSize + 44) = 1;
      v6 = *(_DWORD **)(v5 + 52);
    }
    else
    {
      Game_MPRunNetwork(v4);
      v7 = File_Load(zFilename, &nSize);
      if ( !v7 )
      {
        LDebug_Error("Failed to load resource: '%s'", zFilename);
        abort();
      }
      v6 = Resource_ParseFile(File_zLastSubstitutedPath, v7, nSize);
    }
    if ( *(_BYTE *)v6 == 76 && *((_BYTE *)v6 + 1) == 79 )
    {
      if ( *((_BYTE *)v6 + 2) == 79 && *((_BYTE *)v6 + 3) == 80 && v6[1] == 2 )
      {
        Texture_AllocAndDownload(
          ptTexInfo,
          ptPalInfo,
          *((unsigned __int16 *)v6 + 8),
          *((unsigned __int16 *)v6 + 9),
          *((unsigned __int16 *)v6 + 10),
          *((unsigned __int16 *)v6 + 11),
          *((unsigned __int16 *)v6 + 4),
          (unsigned int)&TerrainRender_atEdge[4623].iSplitVertex,
          v6 + 6);
      }
      else if ( *((_BYTE *)v6 + 2) == 79 && *((_BYTE *)v6 + 3) == 80 && v6[1] == 11 )
      {
        Texture_AllocAndDownload(
          ptTexInfo,
          ptPalInfo,
          *((unsigned __int16 *)v6 + 13) * *((unsigned __int16 *)v6 + 15),
          *((unsigned __int16 *)v6 + 11),
          *((unsigned __int16 *)v6 + 12),
          v6[2],
          *((unsigned __int16 *)v6 + 10),
          v6[3] | 0x8000000,
          v6 + 8);
      }
    }
    result = (char *)Resource_IsLoadedInternal(zFilename, (struct Resource_s **)&nSize);
    goto LABEL_26;
  }
  if ( strstr(zFilename, ".tga")
    || strstr(zFilename, ".jpg")
    || strstr(zFilename, ".png")
    || (result = strstr(zFilename, ".bmp")) != nullptr )
  {
    result = (char *)Resource_Load(zFilename, &nSize);
    if ( result )
    {
      Texture_AllocAndDownloadFromFile(
        ptTexInfo,
        ptPalInfo,
        zFilename,
        result,
        nSize,
        (unsigned int)&TerrainRender_atEdge[4623].iSplitVertex);
      result = (char *)Resource_IsLoadedInternal(zFilename, (struct Resource_s **)&nSize);
LABEL_26:
      if ( result )
      {
        result = *(char **)(nSize + 36);
        if ( result != (char *)3 && result != (char *)1 )
          Resource_Remove((struct Resource_s *)nSize);
      }
    }
  }
  return result;
}

// source: b/4/texture.c:682  [anchor-mhash]
int __cdecl Texture_BeginTextureList(float vMaxVRAMFraction, int nMinVRAMLeft)
{
  int result; // eax
  struct BeginTextureListContext_s tBeginTextureListContext; // [esp+0h] [ebp-8h] BYREF

  tBeginTextureListContext.nMinVRAMLeft = nMinVRAMLeft;
  result = (int)RenderMode_tActiveRenderMode.apfRenderModeMethod[Texture_eBeginTextureListMethod];
  tBeginTextureListContext.vMaxVRAMFraction = vMaxVRAMFraction;
  if ( result )
    return ((int (__cdecl *)(struct BeginTextureListContext_s *))result)(&tBeginTextureListContext);
  return result;
}

// source: b/4/texture.c:705  [size]
void __cdecl Texture_EndTextureList()
{
  void (__cdecl *v0)(void *); // eax

  v0 = RenderMode_tActiveRenderMode.apfRenderModeMethod[Texture_eEndTextureListMethod];
  if ( v0 )
    v0(nullptr);
}

// source: b/4/texture.c:718  [anchor-mhash]
int __cdecl Texture_SetActiveTMU(int iTMU)
{
  int result; // eax
  struct SetActiveTMUContext_s tContext; // [esp+0h] [ebp-4h] BYREF

  tContext.eTMU = iTMU;
  result = (int)RenderMode_tActiveRenderMode.apfRenderModeMethod[Texture_eSetActiveTMUMethod];
  if ( result )
    return ((int (__cdecl *)(struct SetActiveTMUContext_s *))result)(&tContext);
  return result;
}

// source: b/4/texture.c:735  [anchor-mhash]
enum TextureMappingUnit_e __cdecl Texture_GetActiveTMU()
{
  enum TextureMappingUnit_e v0; // ecx
  void (__cdecl *v1)(void *); // ecx
  enum TextureMappingUnit_e result; // eax
  struct GetActiveTMUContext_s tContext; // [esp+0h] [ebp-4h] BYREF

  tContext.eTMU = v0;
  v1 = RenderMode_tActiveRenderMode.apfRenderModeMethod[Texture_eGetActiveTMUMethod];
  result = TEXTURE_TMU_0;
  tContext.eTMU = TEXTURE_TMU_0;
  if ( v1 )
  {
    v1(&tContext);
    return tContext.eTMU;
  }
  return result;
}

// source: b/4/texture.c:753  [anchor-mhash]
int __cdecl Texture_GetTMUs()
{
  int v0; // ecx
  void (__cdecl *v1)(void *); // ecx
  int result; // eax
  struct GetTMUsContext_s tContext; // [esp+0h] [ebp-4h] BYREF

  tContext.nTMUs = v0;
  v1 = RenderMode_tActiveRenderMode.apfRenderModeMethod[Texture_eGetTMUsMethod];
  result = 1;
  tContext.nTMUs = 1;
  if ( v1 )
  {
    v1(&tContext);
    return tContext.nTMUs;
  }
  return result;
}

// source: b/4/texture.c:771  [size]
void __cdecl Texture_Refresh()
{
  void (__cdecl *v0)(void *); // eax

  v0 = RenderMode_tActiveRenderMode.apfRenderModeMethod[Texture_eRefreshTextureMethod];
  if ( v0 )
    v0(nullptr);
}

// source: b/4/texture.c:784  [size]
void __cdecl Texture_Reload()
{
  void (__cdecl *v0)(void *); // eax

  v0 = RenderMode_tActiveRenderMode.apfRenderModeMethod[Texture_eReloadTextureMethod];
  if ( v0 )
    v0(nullptr);
}

// source: b/4/texture.c:797  [size]
int __cdecl Texture_GetRefreshTextureMethod()
{
  return Texture_eRefreshTextureMethod;
}

// source: b/4/texture.c:810  [size]
int __cdecl Texture_GetReloadTextureMethod()
{
  return Texture_eReloadTextureMethod;
}

// source: b/4/texture.c:823  [size]
int __cdecl Texture_GetSetLODMethod()
{
  return Texture_eSetLODMethod;
}

// source: b/4/texture.c:836  [size]
struct TextureFilterContext_s *__cdecl Texture_GetActiveTextureFilterContext()
{
  return &Texture_tActiveTextureFilterContext;
}

// source: b/4/texture.c:849  [anchor-hash]
struct TextureFilterContext_s *__cdecl Texture_SetActiveTextureFilterContext(
        struct TextureFilterContext_s *ptTextureFilterContext)
{
  qmemcpy(&Texture_tActiveTextureFilterContext, ptTextureFilterContext, sizeof(Texture_tActiveTextureFilterContext));
  return ptTextureFilterContext;
}

// source: b/4/texture.c:863  [anchor-hash]
struct TextureFilterContext_s *__cdecl Texture_InitTextureFilterContext(
        struct TextureFilterContext_s *ptTextureFilterContext)
{
  ptTextureFilterContext->tAmbientColour.vX = 0.0;
  ptTextureFilterContext->tAmbientColour.vY = 0.0;
  ptTextureFilterContext->tAmbientColour.vZ = 0.0;
  ptTextureFilterContext->tScale.vX = 1.0;
  ptTextureFilterContext->tScale.vY = 1.0;
  ptTextureFilterContext->tScale.vZ = 1.0;
  ptTextureFilterContext->vGamma = 1.0;
  return ptTextureFilterContext;
}

// source: b/4/texture.c:991  [size]
enum TextureCategory_e __cdecl Texture_SetCategory(enum TextureCategory_e eCategory)
{
  Texture_eCategory = eCategory;
  return eCategory;
}

// source: b/4/texture.c:1004  [size]
enum TextureCategory_e __cdecl Texture_GetCategory()
{
  return Texture_eCategory;
}

// source: b/4/texture.c:1017  [anchor-mhash]
enum TextureCategory_e __cdecl Texture_AddToTextureStats(
        enum TextureCategory_e eCategory,
        int nNumTextures,
        int nFootPrint)
{
  int v3; // esi
  enum TextureCategory_e result; // eax

  Texture_anTextureNum[eCategory] += nNumTextures;
  v3 = Texture_anTextureFootprint[eCategory];
  result = 4 * eCategory + 128714392;
  *(_DWORD *)result = nFootPrint + v3;
  Texture_anTextureNum[2] += nNumTextures;
  Texture_anTextureFootprint[2] += nFootPrint;
  return result;
}

// source: b/4/texture.c:1034  [size]
enum TextureCategory_e __cdecl Texture_GetTextureStats(
        enum TextureCategory_e eCategory,
        int *pnNumTextures,
        int *pnFootPrint)
{
  enum TextureCategory_e result; // eax

  *pnNumTextures = Texture_anTextureNum[eCategory];
  result = Texture_anTextureFootprint[eCategory];
  *pnFootPrint = result;
  return result;
}

// source: b/4/texture.c:1048  [size]
enum bool __cdecl Texture_EnableTextureCompression(enum bool isCompress)
{
  Texture_isCompression = isCompress;
  return isCompress;
}

// source: b/4/texture.c:1061  [size]
enum bool __cdecl Texture_IsTextureCompressionEnabled()
{
  return Texture_isCompression;
}
