/* b/4/text.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/4/text.c:30  [anchor-callee]
void __cdecl Text_SetString(struct StaticTilemap_s *ptQText, char *zString)
{
  struct QTilemap_s *ptQTilemap; // edx

  ptQTilemap = ptQText->ptQTilemap;
  memset(ptQText->ptQTilemap->anGraphicWidth, 0, 2 * ptQText->ptQTilemap->nHeight);
  memset(ptQTilemap->anID, 0, ptQTilemap->nHeight * ptQTilemap->nWidth);
  QTilemap_SetTranslatedString(ptQText->ptQTilemap, zString, 0, 0);
}

// source: b/4/text.c:49  [anchor-mhash]
struct StaticTilemap_s *__cdecl Text_SetARGB(
        struct StaticTilemap_s *ptQText,
        float vAlpha,
        float vR,
        float vG,
        float vB)
{
  ptQText->vA = vAlpha;
  ptQText->vR = vR * 128.0;
  ptQText->vG = vG * 128.0;
  ptQText->vB = vB * 128.0;
  return ptQText;
}

// source: b/4/text.c:76  [anchor-callee]
struct StaticTilemap_s *__cdecl Text_New(struct QSprite_s *ptQSprite, float nX, float nY, char *zString)
{
  struct StaticTilemap_s *v4; // esi

  v4 = (struct StaticTilemap_s *)Mem_AllocFn(40, 4);
  memset(v4, 0, sizeof(struct StaticTilemap_s));
  v4->ptQTilemap = QTilemap_New(256, 1, ptQSprite);
  v4->vR = 128.0;
  v4->vG = 128.0;
  v4->vB = 128.0;
  v4->nPri = 0;
  v4->bQGraphicFlags = 0;
  v4->vX = (float)(__int64)nX;
  v4->vA = 1.0;
  v4->vY = (float)(__int64)nY;
  Text_SetString(v4, zString);
  return v4;
}

// source: b/4/text.c:107  [anchor-callee]
void __cdecl Text_Delete(struct StaticTilemap_s *ptQText)
{
  int v2; // esi

  QTilemap_Delete(ptQText->ptQTilemap);
  v2 = *(_DWORD *)((unsigned int)&ptQText[-1].bQGraphicFlags & 0xFFFFFFFC);
  --Mem_nCurrentAllocations;
  Node_Remove((_DWORD **)v2);
  memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
  free((void *)v2);
}

// source: b/4/text.c:123  [anchor-hash]
struct StaticTilemap_s *__cdecl Text_Register(struct StaticTilemap_s *ptQText)
{
  struct StaticTilemap_s *result; // eax

  QTilemap_Register(
    ptQText->ptQTilemap,
    ptQText->vX,
    ptQText->vY,
    ptQText->vR,
    ptQText->vG,
    ptQText->vB,
    ptQText->vA,
    ptQText->vZ,
    ptQText->bQGraphicFlags | 0x40000000,
    ptQText->nPri);
  return result;
}

// source: b/4/text.c:147  [anchor-callee]
int __cdecl Text_GetWidth(struct StaticTilemap_s *ptQText)
{
  struct QTilemap_s *ptQTilemap; // ecx
  int nHeight; // edx
  int result; // eax
  __int16 *anGraphicWidth; // esi

  ptQTilemap = ptQText->ptQTilemap;
  nHeight = ptQText->ptQTilemap->nHeight;
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

// source: b/4/text.c:163  [size]
int __cdecl Text_GetHeight(struct StaticTilemap_s *ptQText)
{
  return ptQText->ptQTilemap->nHeight
       * ptQText->ptQTilemap->ptQSprite->atQAnimframe[ptQText->ptQTilemap->ptQSprite->nQAnimframes].nHeight;
}

// source: b/4/text.c:179  [anchor-mhash]
void __cdecl Text_GetClippingRect(
        struct StaticTilemap_s *ptQText,
        struct ClippingRect_s *ptClippingRect)
{
  int v2; // ebx
  int nHeight; // ecx
  __int16 *anGraphicWidth; // edx
  int v5; // [esp+4h] [ebp-8h]

  v2 = 0;
  ptClippingRect->vX = (float)(__int64)ptQText->vX;
  v5 = 0;
  ptClippingRect->vY = (float)(__int64)ptQText->vY;
  nHeight = ptQText->ptQTilemap->nHeight;
  if ( nHeight > 0 )
  {
    anGraphicWidth = ptQText->ptQTilemap->anGraphicWidth;
    do
    {
      if ( *anGraphicWidth > v2 )
        v2 = *anGraphicWidth;
      ++anGraphicWidth;
      --nHeight;
    }
    while ( nHeight );
    v5 = v2;
  }
  ptClippingRect->vWidth = (float)v5;
  ptClippingRect->vHeight = (float)(ptQText->ptQTilemap->nHeight
                                  * ptQText->ptQTilemap->ptQSprite->atQAnimframe[ptQText->ptQTilemap->ptQSprite->nQAnimframes].nHeight);
}
