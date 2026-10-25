/* b/4/multitex.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/4/multitex.c:34  [anchor-strings]
struct MultiTex_s *__cdecl MultiTex_Load(char *zFilename)
{
  #pragma pack(push, 1)
  union
  {
    struct { unsigned int nType; };
    struct { char igi2_o1[4]; char zFilenamea[4]; };
    char igi2_extent[8];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char *v1; // ecx
  int v2; // eax
  char *v3; // esi
  void *v4; // eax
  struct PalInfo *v5; // ebx
  int v6; // ebp
  int v7; // edi
  struct MultiTex_s *v8; // ebp
  unsigned int v9; // ebx
  int *v10; // edi
  unsigned int v11; // eax
  int v12; // eax
  int v14; // ebp
  struct PalInfo *v15; // eax
  int v16; // edi
  unsigned int v17; // ebx
  unsigned __int16 *v18; // edi
  unsigned int v19; // eax

  if ( Resource_IsLoadedInternal(zFilename, (struct Resource_s **)igi2_frame.zFilenamea) )
  {
    v2 = *(_DWORD *)igi2_frame.zFilenamea;
    *(_DWORD *)(*(_DWORD *)igi2_frame.zFilenamea + 44) = 1;
    v3 = *(char **)(v2 + 52);
  }
  else
  {
    Game_MPRunNetwork(v1);
    v4 = File_Load(zFilename, (unsigned int *)igi2_frame.zFilenamea);
    if ( !v4 )
    {
      LDebug_Error("Failed to load resource: '%s'", zFilename);
      goto LABEL_5;
    }
    v3 = (char *)Resource_ParseFile(File_zLastSubstitutedPath, v4, *(unsigned int *)igi2_frame.zFilenamea);
  }
  v5 = nullptr;
  if ( !v3 )
  {
    LDebug_Error("Couldn't load texture file '%s'.", zFilename);
LABEL_5:
    abort();
  }
  if ( *v3 != 76 || v3[1] != 79 )
    goto LABEL_34;
  if ( v3[2] == 79 && v3[3] == 80 && *((_DWORD *)v3 + 1) == 7 )
  {
    v6 = *((_DWORD *)v3 + 6);
    if ( v6 )
    {
      v5 = (struct PalInfo *)Mem_AllocFn(12, 4);
      igi2_frame.nType = *(_DWORD *)&v3[v6 + 12];
      v7 = igi2_frame.nType;
      Palette_Alloc(v5, &v3[v6 + 16], igi2_frame.nType);
    }
    else
    {
      igi2_frame.nType = 2;
      v7 = 2;
    }
    v8 = (struct MultiTex_s *)Mem_AllocFn(44 * *((_DWORD *)v3 + 8) + 56, 4);
    v8->ptPalInfo = v5;
    v8->nType = v7;
    v8->nFrames = *((_DWORD *)v3 + 8);
    v9 = 0;
    if ( *((_DWORD *)v3 + 8) )
    {
      *(_DWORD *)igi2_frame.zFilenamea = v8->atTexInfo;
      v10 = (int *)(v3 + 60);
      do
      {
        Texture_AllocAndDownload(
          *(struct TexInfo_s **)igi2_frame.zFilenamea,
          v8->ptPalInfo,
          *(v10 - 1),
          *v10,
          v10[1],
          igi2_frame.nType,
          *((__int16 *)v3 + 9),
          (unsigned int)&TerrainRender_atEdge[4623].iSplitVertex,
          &v3[*(v10 - 2)]);
        v11 = *((_DWORD *)v3 + 8);
        ++v9;
        v10 += 10;
        *(_DWORD *)igi2_frame.zFilenamea += (int)(44);
      }
      while ( v9 < v11 );
    }
    goto LABEL_19;
  }
  if ( v3[2] != 79 || v3[3] != 80 || *((_DWORD *)v3 + 1) != 9 )
  {
LABEL_34:
    LDebug_Error("Texture file not of required type: '%s'.", zFilename);
    goto LABEL_5;
  }
  v14 = *((_DWORD *)v3 + 6);
  if ( v14 )
  {
    v15 = (struct PalInfo *)Mem_AllocFn(12, 4);
    v16 = *(_DWORD *)&v3[v14 + 12];
    v5 = v15;
    Palette_Alloc(v15, &v3[v14 + 16], v16);
  }
  else
  {
    v16 = 2;
  }
  v8 = (struct MultiTex_s *)Mem_AllocFn(44 * *((_DWORD *)v3 + 8) + 56, 4);
  v8->ptPalInfo = v5;
  v8->nType = v16;
  v8->nFrames = *((_DWORD *)v3 + 8);
  v17 = 0;
  if ( *((_DWORD *)v3 + 8) )
  {
    *(_DWORD *)igi2_frame.zFilenamea = v8->atTexInfo;
    v18 = (unsigned __int16 *)(v3 + 64);
    do
    {
      Texture_AllocAndDownload(
        *(struct TexInfo_s **)igi2_frame.zFilenamea,
        v8->ptPalInfo,
        *(v18 - 2),
        *(v18 - 1),
        *v18,
        *((_DWORD *)v18 - 2),
        *((__int16 *)v3 + 9),
        (unsigned int)&TerrainRender_atEdge[4623].iSplitVertex,
        &v3[*((_DWORD *)v18 - 3)]);
      v19 = *((_DWORD *)v3 + 8);
      ++v17;
      v18 += 16;
      *(_DWORD *)igi2_frame.zFilenamea += (int)(44);
    }
    while ( v17 < v19 );
  }
LABEL_19:
  if ( Resource_IsLoadedInternal(zFilename, (struct Resource_s **)igi2_frame.zFilenamea) )
  {
    v12 = *(_DWORD *)(*(_DWORD *)igi2_frame.zFilenamea + 36);
    if ( v12 != 3 && v12 != 1 )
      Resource_Remove(*(struct Resource_s **)igi2_frame.zFilenamea);
  }
  return v8;
}

// source: b/4/multitex.c:207  [anchor-hash]
void __cdecl MultiTex_Delete(struct MultiTex_s *ptMultiTex)
{
  struct PalInfo *ptPalInfo; // eax
  struct PalInfo *v3; // eax
  int v4; // esi
  int v5; // ebp
  struct TexInfo_s *atTexInfo; // esi
  int v7; // esi

  ptPalInfo = ptMultiTex->ptPalInfo;
  if ( ptPalInfo )
  {
    if ( ptPalInfo->eRenderMode != -1 )
      RenderMode_atRenderMode[ptPalInfo->eRenderMode].apfRenderModeMethod[Palette_eDeAllocPaletteMethod](ptPalInfo);
    v3 = ptMultiTex->ptPalInfo;
    if ( v3 )
    {
      v4 = *(_DWORD *)((unsigned int)&v3[-1].pxPalette & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v4);
      memset(*(void **)(v4 + 8), 0xCDu, *(_DWORD *)(v4 + 16));
      free((void *)v4);
    }
    ptMultiTex->ptPalInfo = nullptr;
  }
  v5 = 0;
  if ( ptMultiTex->nFrames > 0 )
  {
    atTexInfo = ptMultiTex->atTexInfo;
    do
    {
      if ( AppContext_tAppContext.isMainMenu == false )
        RenderMode_atRenderMode[atTexInfo->eRenderMode].apfRenderModeMethod[Texture_eDeAllocTextureMethod](atTexInfo);
      memset(atTexInfo, 0, sizeof(struct TexInfo_s));
      ++v5;
      ++atTexInfo;
    }
    while ( v5 < ptMultiTex->nFrames );
  }
  v7 = *(_DWORD *)((unsigned int)&ptMultiTex[-1].atTexInfo[0].eDirect3DFormat & 0xFFFFFFFC);
  --Mem_nCurrentAllocations;
  Node_Remove((_DWORD **)v7);
  memset(*(void **)(v7 + 8), 0xCDu, *(_DWORD *)(v7 + 16));
  free((void *)v7);
}

// source: b/4/multitex.c:239  [size]
struct TexInfo_s *__cdecl MultiTex_GetFrameFn(
        struct MultiTex_s *ptMultiTex,
        int nFrame)
{
  return &ptMultiTex->atTexInfo[nFrame];
}
