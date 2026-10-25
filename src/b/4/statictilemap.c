/* b/4/statictilemap.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/4/statictilemap.c:28  [size]
struct StaticTilemap_s *__cdecl StaticTilemap_SetPos(
        struct StaticTilemap_s *ptTilemap,
        float vX,
        float vY)
{
  ptTilemap->vX = vX;
  ptTilemap->vY = vY;
  return ptTilemap;
}

// source: b/4/statictilemap.c:43  [size]
struct StaticTilemap_s *__cdecl StaticTilemap_SetRGB(
        struct StaticTilemap_s *ptTilemap,
        float vR,
        float vG,
        float vB)
{
  ptTilemap->vR = vR;
  ptTilemap->vG = vG;
  ptTilemap->vB = vB;
  return ptTilemap;
}

// source: b/4/statictilemap.c:59  [size]
int __cdecl StaticTilemap_SetPri(struct StaticTilemap_s *ptTilemap, int nPri)
{
  ptTilemap->nPri = nPri;
  return nPri;
}

// source: b/4/statictilemap.c:73  [size]
struct StaticTilemap_s *__cdecl StaticTilemap_SetTile(
        struct StaticTilemap_s *ptTilemap,
        int nX,
        int nY,
        int nTile)
{
  char *v4; // ecx

  v4 = (char *)ptTilemap->ptQTilemap + nY * ptTilemap->ptQTilemap->nWidth;
  v4[nX + 16] = nTile;
  return (struct StaticTilemap_s *)nX;
}

// source: b/4/statictilemap.c:87  [size]
unsigned int __cdecl StaticTilemap_SetFlags(
        struct StaticTilemap_s *ptTilemap,
        unsigned int bFlags,
        unsigned int bClearMask)
{
  unsigned int result; // eax

  result = bFlags | ptTilemap->bQGraphicFlags & ~bClearMask;
  ptTilemap->bQGraphicFlags = result;
  return result;
}

// source: b/4/statictilemap.c:101  [anchor-mhash]
struct StaticTilemap_s *__cdecl StaticTilemap_New(
        struct QSpriteEx_s *ptQSpriteEx,
        int nWidth,
        int nHeight)
{
  struct StaticTilemap_s *v3; // esi

  v3 = (struct StaticTilemap_s *)Mem_AllocFn(40, 4);
  memset(v3, 0, sizeof(struct StaticTilemap_s));
  v3->ptQTilemap = QTilemap_New(nWidth, nHeight, &ptQSpriteEx->tQSprite);
  v3->vR = 128.0;
  v3->vG = 128.0;
  v3->vB = 128.0;
  return v3;
}

// source: b/4/statictilemap.c:121  [anchor-hash]
void __cdecl StaticTilemap_Delete(struct StaticTilemap_s *ptTilemap)
{
  int v2; // esi

  QTilemap_Delete(ptTilemap->ptQTilemap);
  v2 = *(_DWORD *)((unsigned int)&ptTilemap[-1].bQGraphicFlags & 0xFFFFFFFC);
  --Mem_nCurrentAllocations;
  Node_Remove((_DWORD **)v2);
  memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
  free((void *)v2);
}

// source: b/4/statictilemap.c:137  [size]
struct StaticTilemap_s *__cdecl StaticTilemap_Register(struct StaticTilemap_s *ptTilemap)
{
  struct StaticTilemap_s *result; // eax

  QTilemap_Register(
    ptTilemap->ptQTilemap,
    ptTilemap->vX,
    ptTilemap->vY,
    ptTilemap->vR,
    ptTilemap->vG,
    ptTilemap->vB,
    ptTilemap->vA,
    ptTilemap->vZ,
    ptTilemap->bQGraphicFlags,
    ptTilemap->nPri);
  return result;
}

// source: b/4/statictilemap.c:151  [size]
int __cdecl StaticTilemap_GetWidth(struct StaticTilemap_s *ptTilemap)
{
  struct QTilemap_s *ptQTilemap; // ecx
  int nHeight; // edx
  int result; // eax
  __int16 *anGraphicWidth; // esi

  ptQTilemap = ptTilemap->ptQTilemap;
  nHeight = ptTilemap->ptQTilemap->nHeight;
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

// source: b/4/statictilemap.c:165  [size]
int __cdecl StaticTilemap_GetHeight(struct StaticTilemap_s *ptTilemap)
{
  return ptTilemap->ptQTilemap->nHeight
       * ptTilemap->ptQTilemap->ptQSprite->atQAnimframe[ptTilemap->ptQTilemap->ptQSprite->nQAnimframes].nHeight;
}

// source: b/4/statictilemap.c:179  [size]
struct StaticTilemap_s *__cdecl StaticTilemap_SetZ(
        struct StaticTilemap_s *ptTilemap,
        float vZ)
{
  ptTilemap->bQGraphicFlags |= 0x40000u;
  ptTilemap->vZ = vZ;
  return ptTilemap;
}

// source: b/4/statictilemap.c:193  [size]
struct StaticTilemap_s *__cdecl StaticTilemap_SetA(
        struct StaticTilemap_s *ptTilemap,
        float vA)
{
  ptTilemap->bQGraphicFlags |= 0x80000u;
  ptTilemap->vA = vA;
  return ptTilemap;
}
