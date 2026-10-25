/* b/4/qsprite.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/4/qsprite.c:69  [size]
unsigned int __cdecl QSprite_AllocTexture(
        struct QSprite_s *ptQSprite,
        int iTexture,
        void *pxData,
        int nPitch,
        int nWidth,
        int nHeight,
        unsigned int nType,
        int nTextureScaleFactor,
        unsigned int bQGraphicFlags)
{
  unsigned int result; // eax

  Texture_AllocAndDownload(
    &ptQSprite->atTexInfo[iTexture],
    ptQSprite->ptPalInfo,
    nPitch,
    nWidth,
    nHeight,
    nType,
    nTextureScaleFactor,
    bQGraphicFlags | 1,
    pxData);
  return result;
}

// source: b/4/qsprite.c:106  [anchor-mhash]
int __cdecl QSprite_InitFrame(
        struct QSprite_s *ptQSprite,
        int iAnimFrame,
        int iTexture,
        int nWidth,
        int nHeight,
        int nX,
        int nY,
        int nSpace,
        unsigned int bQGraphicFlags,
        float vU0,
        float vV0,
        float vU1,
        float vV1)
{
  int result; // eax

  result = iAnimFrame;
  ptQSprite->atQAnimframe[result].nX = nX;
  ptQSprite->atQAnimframe[result].nY = nY;
  ptQSprite->atQAnimframe[result].nWidth = nWidth;
  ptQSprite->atQAnimframe[result].nHeight = nHeight;
  ptQSprite->atQAnimframe[result].nSpace = nSpace;
  ptQSprite->atQAnimframe[result].bFlags = bQGraphicFlags;
  ptQSprite->atQAnimframe[result].ptTexInfo = &ptQSprite->atTexInfo[iTexture];
  ptQSprite->atQAnimframe[result].vU0 = vU0;
  ptQSprite->atQAnimframe[result].vV0 = vV0;
  ptQSprite->atQAnimframe[result].vU1 = vU1;
  ptQSprite->atQAnimframe[result].vV1 = vV1;
  return result * 36;
}

// source: b/4/qsprite.c:145  [size]
int __cdecl QSprite_Alloc(
        struct QSprite_s *ptQSprite,
        int nType,
        int nXOffset,
        int nYOffset,
        int nMaxWidth,
        int nMaxHeight,
        int nDefaultSpace,
        unsigned int bQGraphicFlags,
        struct PalInfo *ptPalInfo,
        int nFrames,
        int nTextures)
{
  int v11; // ebx
  unsigned int v12; // ebp
  struct QAnimframe_s *v13; // eax
  int result; // eax

  v11 = nFrames;
  ptQSprite->nQAnimframes = nFrames;
  v12 = 36 * nFrames + 36;
  ptQSprite->ptPalInfo = ptPalInfo;
  ptQSprite->ptQTilemap = nullptr;
  ptQSprite->nType = nType;
  v13 = (struct QAnimframe_s *)Mem_AllocFn(v12 + 44 * nTextures, 4);
  ptQSprite->atQAnimframe = v13;
  ptQSprite->nTextures = nTextures;
  ptQSprite->atTexInfo = (struct TexInfo_s *)((char *)v13 + v12);
  memset(v13, 0, v12);
  ptQSprite->atQAnimframe[v11].bFlags = bQGraphicFlags;
  ptQSprite->atQAnimframe[v11].nX = nXOffset;
  ptQSprite->atQAnimframe[v11].nY = nYOffset;
  result = (int)ptQSprite->atQAnimframe;
  *(_WORD *)(result + v11 * 36 + 12) = nMaxWidth;
  LOWORD(result) = nMaxHeight;
  ptQSprite->atQAnimframe[v11].nHeight = nMaxHeight;
  ptQSprite->atQAnimframe[v11].nSpace = nDefaultSpace;
  return result;
}

// source: b/4/qsprite.c:183  [anchor-callee]
void __cdecl QSprite_DeAlloc(struct QSprite_s *ptQSprite)
{
  struct PalInfo *ptPalInfo; // eax
  int v2; // esi
  struct QTilemap_s *ptQTilemap; // eax
  int nTextures; // eax
  int v5; // esi
  int v6; // ebp
  struct TexInfo_s *v7; // edi
  struct QAnimframe_s *atQAnimframe; // eax
  int v9; // esi

  ptPalInfo = ptQSprite->ptPalInfo;
  if ( ptQSprite->ptPalInfo )
  {
    if ( ptPalInfo->eRenderMode != -1 )
      RenderMode_atRenderMode[ptPalInfo->eRenderMode].apfRenderModeMethod[Palette_eDeAllocPaletteMethod](ptQSprite->ptPalInfo);
    if ( ptQSprite->ptPalInfo )
    {
      v2 = *(_DWORD *)((int)&ptQSprite->ptPalInfo[-1].pxPalette & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v2);
      memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
      free((void *)v2);
    }
    ptQSprite->ptPalInfo = nullptr;
  }
  ptQTilemap = ptQSprite->ptQTilemap;
  if ( ptQTilemap )
    QTilemap_Delete(ptQTilemap);
  nTextures = ptQSprite->nTextures;
  if ( nTextures )
  {
    v5 = 0;
    if ( nTextures > 0 )
    {
      v6 = 0;
      do
      {
        v7 = &ptQSprite->atTexInfo[v6];
        if ( AppContext_tAppContext.isMainMenu == false )
          RenderMode_atRenderMode[v7->eRenderMode].apfRenderModeMethod[Texture_eDeAllocTextureMethod](v7);
        memset(v7, 0, sizeof(struct TexInfo_s));
        ++v5;
        ++v6;
      }
      while ( v5 < ptQSprite->nTextures );
    }
  }
  atQAnimframe = ptQSprite->atQAnimframe;
  if ( atQAnimframe )
  {
    v9 = *(_DWORD *)((unsigned int)&atQAnimframe[-1].vV1 & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v9);
    memset(*(void **)(v9 + 8), 0xCDu, *(_DWORD *)(v9 + 16));
    free((void *)v9);
  }
  ptQSprite->atQAnimframe = nullptr;
}

// source: b/4/qsprite.c:227  [anchor-callee]
struct QSprite_s *__cdecl QSprite_Load(struct QSprite_s *ptQSprite, char *zFilename)
{
  #pragma pack(push, 1)
  union
  {
    struct { int NumberOfILFTextureChunks; };
    struct { char igi2_o1[20]; struct QSprite_s *nType; };
    struct { char igi2_o2[20]; void *nTypea; };
    struct { char igi2_o3[20]; int nTypeb; };
    struct { char igi2_o4[20]; unsigned int nTypec; };
    struct { char igi2_o5[20]; unsigned int nTyped; };
    struct { char igi2_o6[24]; unsigned int nSize; };
    char igi2_extent[28];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct PalInfo *v2; // edi
  _DWORD *v3; // eax
  _DWORD *v4; // ebx
  void *FirstChunk; // eax
  void *v6; // esi
  void *Chunk; // edi
  void *v8; // eax
  _DWORD *ChunkData; // esi
  void *v10; // eax
  int nTextures; // eax
  int i; // eax
  int v13; // edi
  int v14; // esi
  struct PalInfo *v16; // eax
  int v17; // esi
  struct PalInfo *v18; // eax
  int v19; // esi
  int v20; // edi
  int *v21; // esi
  struct PalInfo *v22; // eax
  int v23; // esi
  int v24; // edi
  unsigned int *v25; // esi
  int v26; // eax
  void *v27; // ebx
  struct QTilemap_s *v28; // eax
  int v29; // eax

  if ( !strstr(zFilename, ".tga")
    && !strstr(zFilename, ".jpg")
    && !strstr(zFilename, ".png")
    && !strstr(zFilename, ".bmp") )
  {
    v2 = nullptr;
    igi2_frame.nType = nullptr;
    v3 = Resource_Load(zFilename, nullptr);
    v4 = v3;
    if ( !v3 )
      return igi2_frame.nType;
    if ( *v3 == 1179012169 && v3[4] == 1414418246 )
    {
      FirstChunk = ILF_GetFirstChunk(v3);
      v6 = FirstChunk;
      if ( FirstChunk )
      {
        Chunk = ILF_FindChunk(FirstChunk, 0x48544E46u);
        igi2_frame.nSize = (unsigned int)ILF_FindChunk(v6, 0x4E415254u);
        v8 = ILF_FindChunk(v6, 0x464D4E41u);
        igi2_frame.nTypea = v8;
        if ( Chunk )
        {
          if ( igi2_frame.nSize )
          {
            if ( v8 )
            {
              ChunkData = ILF_GetChunkData(Chunk, v4);
              igi2_frame.nSize = (unsigned int)ILF_GetChunkData((void *)igi2_frame.nSize, v4);
              v10 = ILF_GetChunkData(igi2_frame.nTypea, v4);
              igi2_frame.nTypeb = (int)v10;
              if ( ChunkData )
              {
                if ( igi2_frame.nSize )
                {
                  if ( v10 )
                  {
                    igi2_frame.NumberOfILFTextureChunks = Texture_GetNumberOfILFTextureChunks(v4);
                    QSprite_Alloc(
                      ptQSprite,
                      0,
                      0,
                      0,
                      ChunkData[4],
                      ChunkData[5],
                      ChunkData[3],
                      *ChunkData != 0 ? 0 : 0x10000,
                      nullptr,
                      ChunkData[1],
                      igi2_frame.NumberOfILFTextureChunks);
                    nTextures = ptQSprite->nTextures;
                    if ( nTextures > 0 )
                    {
                      Texture_AllocILFTextureChunks(v4, ptQSprite->atTexInfo, nTextures, nullptr);
                      ptQSprite->ptQTilemap = QTilemap_New(256, 1, ptQSprite);
                      for ( i = 0; i < 256; ++i )
                        ptQSprite->ptQTilemap->anID[i] = *(_BYTE *)(igi2_frame.nSize + 2 * i);
                      v13 = 0;
                      if ( ptQSprite->nQAnimframes )
                      {
                        v14 = igi2_frame.nTypeb + 12;
                        do
                        {
                          QSprite_InitFrame(
                            ptQSprite,
                            v13++,
                            *(__int16 *)(v14 + 8),
                            *(__int16 *)(v14 + 10),
                            *(__int16 *)(v14 + 12),
                            *(__int16 *)(v14 + 22),
                            *(__int16 *)(v14 + 24),
                            *(__int16 *)(v14 + 14),
                            *(_DWORD *)(v14 - 12),
                            *(float *)(v14 - 8),
                            *(float *)(v14 - 4),
                            *(float *)v14,
                            *(float *)(v14 + 4));
                          v14 += 40;
                        }
                        while ( v13 < ptQSprite->nQAnimframes );
                      }
                      return ptQSprite;
                    }
                  }
                }
              }
            }
          }
        }
      }
      LDebug_Error("ILF file corrupt: %s", zFilename);
LABEL_10:
      abort();
    }
    if ( *(_BYTE *)v3 == 76 && *((_BYTE *)v3 + 1) == 79 )
    {
      if ( *((_BYTE *)v3 + 2) == 79 && *((_BYTE *)v3 + 3) == 80 && v3[1] == 1 )
      {
        igi2_frame.nSize = v3[3];
        if ( igi2_frame.nSize )
        {
          v16 = (struct PalInfo *)Mem_AllocFn(12, 4);
          v17 = *(_DWORD *)((char *)v4 + igi2_frame.nSize + 12);
          v2 = v16;
          igi2_frame.nTypec = v17;
          Palette_Alloc(v16, (char *)v4 + igi2_frame.nSize + 16, v17);
        }
        else
        {
          igi2_frame.nTypec = 2;
          v17 = 2;
        }
        QSprite_Alloc(
          ptQSprite,
          v17,
          0,
          0,
          *((unsigned __int16 *)v4 + 12),
          *((unsigned __int16 *)v4 + 13),
          0,
          0x10000u,
          v2,
          1,
          1);
        QSprite_AllocTexture(
          ptQSprite,
          0,
          v4 + 7,
          *((unsigned __int16 *)v4 + 11),
          *((unsigned __int16 *)v4 + 12),
          *((unsigned __int16 *)v4 + 13),
          igi2_frame.nTypec,
          0,
          0);
        QSprite_InitFrame(
          ptQSprite,
          0,
          0,
          *((unsigned __int16 *)v4 + 12),
          *((unsigned __int16 *)v4 + 13),
          0,
          0,
          0,
          0,
          0.0,
          0.0,
          1.0,
          1.0);
LABEL_56:
        igi2_frame.nType = ptQSprite;
        Resource_Unload(zFilename);
        return igi2_frame.nType;
      }
      if ( *((_BYTE *)v3 + 2) == 79 && *((_BYTE *)v3 + 3) == 80 && v3[1] == 7 )
      {
        igi2_frame.nSize = v3[6];
        if ( igi2_frame.nSize )
        {
          v18 = (struct PalInfo *)Mem_AllocFn(12, 4);
          v19 = *(_DWORD *)((char *)v4 + igi2_frame.nSize + 12);
          v2 = v18;
          igi2_frame.nTyped = v19;
          Palette_Alloc(v18, (char *)v4 + igi2_frame.nSize + 16, v19);
        }
        else
        {
          igi2_frame.nTyped = v3[12];
          v19 = igi2_frame.nTyped;
        }
        QSprite_Alloc(ptQSprite, v19, 0, 0, v4[10], v4[11], 0, v4[8] != 1 ? 0 : 0x10000, v2, v4[8], v4[8]);
        v20 = 0;
        if ( (int)v4[8] > 0 )
        {
          v21 = v4 + 17;
          do
          {
            QSprite_AllocTexture(
              ptQSprite,
              v20,
              (char *)v4 + *(v21 - 4),
              *(v21 - 3),
              *(v21 - 2),
              *(v21 - 1),
              igi2_frame.nTyped,
              *((__int16 *)v4 + 9),
              0);
            QSprite_InitFrame(ptQSprite, v20, v20, *(v21 - 2), *(v21 - 1), v21[4], v21[5], *v21, 0, 0.0, 0.0, 1.0, 1.0);
            ++v20;
            v21 += 10;
          }
          while ( v20 < (int)(v4[8]) );
        }
LABEL_54:
        v26 = v4[7];
        if ( v26 )
          ptQSprite->ptQTilemap = QTilemap_FromROMTilemap((struct ROMTilemap *)((char *)v4 + v26), ptQSprite);
        goto LABEL_56;
      }
      if ( *((_BYTE *)v3 + 2) == 79 && *((_BYTE *)v3 + 3) == 80 && v3[1] == 9 )
      {
        igi2_frame.nSize = v3[6];
        if ( igi2_frame.nSize )
        {
          v22 = (struct PalInfo *)Mem_AllocFn(12, 4);
          v23 = *(_DWORD *)((char *)v4 + igi2_frame.nSize + 12);
          v2 = v22;
          Palette_Alloc(v22, (char *)v4 + igi2_frame.nSize + 16, v23);
        }
        else
        {
          v23 = v3[12];
        }
        QSprite_Alloc(ptQSprite, v23, 0, 0, v4[10], v4[11], 0, v4[8] != 1 ? 0 : 0x10000, v2, v4[8], v4[8]);
        v24 = 0;
        if ( (int)v4[8] > 0 )
        {
          v25 = v4 + 20;
          do
          {
            QSprite_AllocTexture(
              ptQSprite,
              v24,
              (char *)v4 + *(v25 - 7),
              *((unsigned __int16 *)v25 - 10),
              *((unsigned __int16 *)v25 - 9),
              *((unsigned __int16 *)v25 - 8),
              *(v25 - 6),
              *((__int16 *)v4 + 9),
              *v25);
            QSprite_InitFrame(
              ptQSprite,
              v24,
              v24,
              *((unsigned __int16 *)v25 - 9),
              *((unsigned __int16 *)v25 - 8),
              *((__int16 *)v25 - 3),
              *((__int16 *)v25 - 2),
              *((__int16 *)v25 - 7),
              *v25,
              0.0,
              0.0,
              1.0,
              1.0);
            ++v24;
            v25 += 8;
          }
          while ( v24 < (int)(v4[8]) );
        }
        goto LABEL_54;
      }
      if ( *((_BYTE *)v3 + 2) == 79 && *((_BYTE *)v3 + 3) == 80 && v3[1] == 5
        || *((_BYTE *)v3 + 2) == 79 && *((_BYTE *)v3 + 3) == 80 && v3[1] == 10 )
      {
        LDebug_Error("The font '%s' must be packed. Ask Stein.", zFilename);
        goto LABEL_10;
      }
    }
    LDebug_Error("Invalid sprite file: %s", zFilename);
    goto LABEL_10;
  }
  v27 = Resource_Load(zFilename, &igi2_frame.nSize);
  if ( !v27 )
    return nullptr;
  QSprite_Alloc(ptQSprite, -1, 0, 0, 0, 0, 0, 0, nullptr, 1, 1);
  Texture_AllocAndDownloadFromFile(ptQSprite->atTexInfo, ptQSprite->ptPalInfo, zFilename, v27, igi2_frame.nSize, 1u);
  ptQSprite->atQAnimframe->nWidth = ptQSprite->atTexInfo->nWidth;
  ptQSprite->atQAnimframe->nHeight = ptQSprite->atTexInfo->nHeight;
  ptQSprite->atQAnimframe->nSpace = ptQSprite->atQAnimframe->nWidth;
  ptQSprite->atQAnimframe->vU0 = 0.0;
  ptQSprite->atQAnimframe->vV0 = 0.0;
  ptQSprite->atQAnimframe->vU1 = 1.0;
  ptQSprite->atQAnimframe->vV1 = 1.0;
  ptQSprite->atQAnimframe->ptTexInfo = ptQSprite->atTexInfo;
  ptQSprite->atQAnimframe[1].nWidth = ptQSprite->atQAnimframe->nWidth;
  ptQSprite->atQAnimframe[1].nHeight = ptQSprite->atQAnimframe->nHeight;
  ptQSprite->atQAnimframe[1].nSpace = ptQSprite->atQAnimframe->nSpace;
  ptQSprite->nType = ptQSprite->atTexInfo->nType;
  v28 = QTilemap_New(1, 1, ptQSprite);
  ptQSprite->ptQTilemap = v28;
  v28->anID[0] = 1;
  QTilemap_UpdateGraphicWidth(ptQSprite->ptQTilemap, 0);
  if ( Resource_IsLoadedInternal(zFilename, (struct Resource_s **)&igi2_frame.nSize) )
  {
    v29 = *(_DWORD *)(igi2_frame.nSize + 36);
    if ( v29 != 3 && v29 != 1 )
      Resource_Remove((struct Resource_s *)igi2_frame.nSize);
  }
  return ptQSprite;
}

// source: b/4/qsprite.c:843  [size]
int __cdecl QSprite_GetWidth(struct QSprite_s *ptQSprite)
{
  return ptQSprite->atQAnimframe[ptQSprite->nQAnimframes].nWidth;
}

// source: b/4/qsprite.c:859  [size]
int __cdecl QSprite_GetHeight(struct QSprite_s *ptQSprite)
{
  return ptQSprite->atQAnimframe[ptQSprite->nQAnimframes].nHeight;
}

// source: b/4/qsprite.c:875  [size]
int __cdecl QSprite_GetSpace(struct QSprite_s *ptQSprite)
{
  return ptQSprite->atQAnimframe[ptQSprite->nQAnimframes].nSpace;
}

// source: b/4/qsprite.c:891  [size]
int __cdecl QSprite_isOneSize(struct QSprite_s *ptQSprite)
{
  return BYTE2(ptQSprite->atQAnimframe[ptQSprite->nQAnimframes].bFlags) & 1;
}

// source: b/4/qsprite.c:908  [anchor-mhash]
struct QSprite_s *__cdecl QSprite_SetOneSize(struct QSprite_s *ptQSprite, int isOneSize)
{
  bool v2; // zf
  struct QSprite_s *result; // eax
  struct PalInfo *ptPalInfo; // ecx

  v2 = isOneSize == 0;
  result = (struct QSprite_s *)&ptQSprite->atQAnimframe[ptQSprite->nQAnimframes].bFlags;
  ptPalInfo = result->ptPalInfo;
  if ( v2 )
    result->ptPalInfo = (struct PalInfo *)((unsigned int)ptPalInfo & 0xFFFEFFFF);
  else
    result->ptPalInfo = (struct PalInfo *)((unsigned int)ptPalInfo | 0x10000);
  return result;
}
