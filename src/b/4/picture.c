/* b/4/picture.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/4/picture.c:28  [anchor-mhash]
struct StaticTilemap_s *__cdecl Picture_Load(char *zFilename)
{
  struct QSprite_s *v1; // edi
  struct StaticTilemap_s *v2; // eax
  struct QTilemap_s *ptQTilemap; // ebx
  struct StaticTilemap_s *v4; // esi
  int v6; // esi

  v1 = (struct QSprite_s *)Mem_AllocFn(24, 4);
  if ( QSprite_Load(v1, zFilename) )
  {
    v2 = (struct StaticTilemap_s *)Mem_AllocFn(40, 4);
    ptQTilemap = v1->ptQTilemap;
    v4 = v2;
    v2->ptQTilemap = ptQTilemap;
    QTilemap_UpdateGraphicWidth(ptQTilemap, 0);
    v4->vA = 1.0;
    v4->vZ = 1.0;
    v4->vX = 0.0;
    v4->vY = 0.0;
    v4->nPri = 0;
    v4->bQGraphicFlags = 0;
    v4->vR = 128.0;
    v4->vG = 128.0;
    v4->vB = 128.0;
    return v4;
  }
  else
  {
    if ( v1 )
    {
      v6 = *(_DWORD *)((unsigned int)&v1[-1].nQAnimframes & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v6);
      memset(*(void **)(v6 + 8), 0xCDu, *(_DWORD *)(v6 + 16));
      free((void *)v6);
    }
    return nullptr;
  }
}

// source: b/4/picture.c:65  [anchor-callee]
void __cdecl Picture_Delete(struct StaticTilemap_s *ptQPicture)
{
  struct QSprite_s *ptQSprite; // ebx
  int v2; // esi
  int v3; // esi

  ptQSprite = ptQPicture->ptQTilemap->ptQSprite;
  QSprite_DeAlloc(ptQSprite);
  if ( ptQSprite )
  {
    v2 = *(_DWORD *)((unsigned int)&ptQSprite[-1].nQAnimframes & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v2);
    memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
    free((void *)v2);
  }
  v3 = *(_DWORD *)((unsigned int)&ptQPicture[-1].bQGraphicFlags & 0xFFFFFFFC);
  --Mem_nCurrentAllocations;
  Node_Remove((_DWORD **)v3);
  memset(*(void **)(v3 + 8), 0xCDu, *(_DWORD *)(v3 + 16));
  free((void *)v3);
}

// source: b/4/picture.c:86  [size]
struct StaticTilemap_s *__cdecl Picture_Register(struct StaticTilemap_s *ptQPicture)
{
  struct StaticTilemap_s *result; // eax

  QTilemap_Register(
    ptQPicture->ptQTilemap,
    ptQPicture->vX,
    ptQPicture->vY,
    ptQPicture->vR,
    ptQPicture->vG,
    ptQPicture->vB,
    ptQPicture->vA,
    ptQPicture->vZ,
    ptQPicture->bQGraphicFlags,
    ptQPicture->nPri);
  return result;
}

// source: b/4/picture.c:101  [size]
int __cdecl Picture_GetWidth(struct StaticTilemap_s *ptQPicture)
{
  struct QTilemap_s *ptQTilemap; // ecx
  int nHeight; // edx
  int result; // eax
  __int16 *anGraphicWidth; // esi

  ptQTilemap = ptQPicture->ptQTilemap;
  nHeight = ptQPicture->ptQTilemap->nHeight;
  result = 0;
  if ( nHeight > 0 )
  {
    anGraphicWidth = ptQTilemap->anGraphicWidth;
    do
    {
      if ( *anGraphicWidth > result )
        result = *anGraphicWidth;
      ++anGraphicWidth;
      --nHeight;
    }
    while ( nHeight );
  }
  return result;
}

// source: b/4/picture.c:116  [size]
int __cdecl Picture_GetHeight(struct StaticTilemap_s *ptQPicture)
{
  return ptQPicture->ptQTilemap->nHeight
       * ptQPicture->ptQTilemap->ptQSprite->atQAnimframe[ptQPicture->ptQTilemap->ptQSprite->nQAnimframes].nHeight;
}
