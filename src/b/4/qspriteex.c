/* b/4/qspriteex.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/4/qspriteex.c:31  [anchor-mhash]
struct QSpriteEx_s *__cdecl QSpriteEx_Load(char *zFilename)
{
  struct QSpriteEx_s *v1; // esi
  int v3; // esi

  v1 = (struct QSpriteEx_s *)Mem_AllocFn(188, 4);
  memset(v1, 0, sizeof(struct QSpriteEx_s));
  if ( QSprite_Load(&v1->tQSprite, zFilename) )
  {
    v1->tQSpriteDrawInfo.atQVertex[0].vR = 1.0;
    v1->tQSpriteDrawInfo.atQVertex[0].vG = 1.0;
    v1->tQSpriteDrawInfo.atQVertex[0].vB = 1.0;
    v1->tQSpriteDrawInfo.nRGB = 1;
    return v1;
  }
  else
  {
    if ( v1 )
    {
      v3 = *(_DWORD *)((unsigned int)&v1[-1].vHotY & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v3);
      memset(*(void **)(v3 + 8), 0xCDu, *(_DWORD *)(v3 + 16));
      free((void *)v3);
    }
    return nullptr;
  }
}

// source: b/4/qspriteex.c:55  [size]
void __cdecl QSpriteEx_Delete(struct QSpriteEx_s *ptQSpriteEx)
{
  int v2; // esi

  QSprite_DeAlloc(&ptQSpriteEx->tQSprite);
  if ( ptQSpriteEx )
  {
    v2 = *(_DWORD *)((unsigned int)&ptQSpriteEx[-1].vHotY & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v2);
    memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
    free((void *)v2);
  }
}

// source: b/4/qspriteex.c:69  [anchor-strings]
struct QSpriteEx_s *__cdecl QSpriteEx_SetPos(struct QSpriteEx_s *ptQSpriteEx, float nXpos, float nYpos)
{
  unsigned int bQGraphicFlags; // ecx
  double v4; // st7
  double v5; // st6
  struct QAnimframe_s *v6; // edx
  int nHeight; // [esp+0h] [ebp-4h]

  bQGraphicFlags = ptQSpriteEx->tQSpriteDrawInfo.bQGraphicFlags;
  if ( (bQGraphicFlags & 0xE000) != 0 )
  {
    LDebug_Error("Rotation and scaling for QSpriteEx not implemented.");
    abort();
  }
  v4 = nXpos - ptQSpriteEx->vHotX;
  v5 = nYpos - ptQSpriteEx->vHotY;
  v6 = &ptQSpriteEx->tQSprite.atQAnimframe[ptQSpriteEx->tQSprite.nQAnimframes];
  ptQSpriteEx->tQSpriteDrawInfo.atQVertex[0].vX = v4;
  ptQSpriteEx->tQSpriteDrawInfo.atQVertex[0].vY = v5;
  ptQSpriteEx->tQSpriteDrawInfo.atQVertex[1].vX = (double)v6->nWidth + v4;
  nHeight = v6->nHeight;
  ptQSpriteEx->tQSpriteDrawInfo.bQGraphicFlags = bQGraphicFlags & 0xFFFFEFFF;
  ptQSpriteEx->tQSpriteDrawInfo.atQVertex[1].vY = (double)nHeight + v5;
  return ptQSpriteEx;
}

// source: b/4/qspriteex.c:96  [size]
int __cdecl QSpriteEx_SetPri(struct QSpriteEx_s *ptQSpriteEx, int nPri)
{
  ptQSpriteEx->nPri = nPri;
  return nPri;
}

// source: b/4/qspriteex.c:115  [anchor-mhash]
struct QSpriteEx_s *__cdecl QSpriteEx_SetRGB(
        struct QSpriteEx_s *ptQSpriteEx,
        float vR,
        float vG,
        float vB)
{
  ptQSpriteEx->tQSpriteDrawInfo.nRGB = 1;
  ptQSpriteEx->tQSpriteDrawInfo.atQVertex[0].vR = vR * 0.0078125;
  ptQSpriteEx->tQSpriteDrawInfo.atQVertex[0].vG = vG * 0.0078125;
  ptQSpriteEx->tQSpriteDrawInfo.atQVertex[0].vB = vB * 0.0078125;
  return ptQSpriteEx;
}

// source: b/4/qspriteex.c:141  [anchor-mhash]
struct QSpriteEx_s *__cdecl QSpriteEx_SetVertices(
        struct QSpriteEx_s *ptQSpriteEx,
        float vX1,
        float vY1,
        float vX2,
        float vY2,
        float vX3,
        float vY3,
        float vX4,
        float vY4)
{
  unsigned int bQGraphicFlags; // ecx

  ptQSpriteEx->tQSpriteDrawInfo.atQVertex[0].vX = vX1;
  ptQSpriteEx->tQSpriteDrawInfo.atQVertex[1].vX = vX2;
  ptQSpriteEx->tQSpriteDrawInfo.atQVertex[0].vY = vY1;
  ptQSpriteEx->tQSpriteDrawInfo.atQVertex[2].vX = vX3;
  ptQSpriteEx->tQSpriteDrawInfo.atQVertex[1].vY = vY2;
  ptQSpriteEx->tQSpriteDrawInfo.atQVertex[3].vX = vX4;
  bQGraphicFlags = ptQSpriteEx->tQSpriteDrawInfo.bQGraphicFlags;
  ptQSpriteEx->tQSpriteDrawInfo.atQVertex[2].vY = vY3;
  ptQSpriteEx->tQSpriteDrawInfo.atQVertex[3].vY = vY4;
  ptQSpriteEx->tQSpriteDrawInfo.bQGraphicFlags = bQGraphicFlags | 0x1000;
  return ptQSpriteEx;
}

// source: b/4/qspriteex.c:176  [anchor-mhash]
struct QSpriteEx_s *__cdecl QSpriteEx_SetVertexColours(
        struct QSpriteEx_s *ptQSpriteEx,
        float vR1,
        float vG1,
        float vB1,
        float vR2,
        float vG2,
        float vB2,
        float vR3,
        float vG3,
        float vB3,
        float vR4,
        float vG4,
        float vB4)
{
  ptQSpriteEx->tQSpriteDrawInfo.nRGB = 4;
  ptQSpriteEx->tQSpriteDrawInfo.atQVertex[0].vR = vR1 * 0.0078125;
  ptQSpriteEx->tQSpriteDrawInfo.atQVertex[0].vG = vG1 * 0.0078125;
  ptQSpriteEx->tQSpriteDrawInfo.atQVertex[0].vB = vB1 * 0.0078125;
  ptQSpriteEx->tQSpriteDrawInfo.atQVertex[1].vR = vR2 * 0.0078125;
  ptQSpriteEx->tQSpriteDrawInfo.atQVertex[1].vG = vG2 * 0.0078125;
  ptQSpriteEx->tQSpriteDrawInfo.atQVertex[1].vB = vB2 * 0.0078125;
  ptQSpriteEx->tQSpriteDrawInfo.atQVertex[2].vR = vR3 * 0.0078125;
  ptQSpriteEx->tQSpriteDrawInfo.atQVertex[2].vG = vG3 * 0.0078125;
  ptQSpriteEx->tQSpriteDrawInfo.atQVertex[2].vB = vB3 * 0.0078125;
  ptQSpriteEx->tQSpriteDrawInfo.atQVertex[3].vR = vR4 * 0.0078125;
  ptQSpriteEx->tQSpriteDrawInfo.atQVertex[3].vG = vG4 * 0.0078125;
  ptQSpriteEx->tQSpriteDrawInfo.atQVertex[3].vB = vB4 * 0.0078125;
  return ptQSpriteEx;
}

// source: b/4/qspriteex.c:208  [anchor-mhash]
struct QSpriteEx_s *__cdecl QSpriteEx_SetHotspot(
        struct QSpriteEx_s *ptQSpriteEx,
        float vX,
        float vY,
        unsigned int bFlags)
{
  double nHeight; // st7
  double nWidth; // st6
  float vOrgX; // [esp+4h] [ebp-8h]

  nHeight = 0.0;
  vOrgX = 0.0;
  if ( (bFlags & 0x80u) == 0 )
  {
    if ( (bFlags & 0x100) == 0 )
      goto LABEL_6;
    nWidth = (double)ptQSpriteEx->tQSprite.atQAnimframe[ptQSpriteEx->tQSprite.nQAnimframes].nWidth;
  }
  else
  {
    nWidth = (double)ptQSpriteEx->tQSprite.atQAnimframe[ptQSpriteEx->tQSprite.nQAnimframes].nWidth * 0.5;
  }
  vOrgX = nWidth;
LABEL_6:
  if ( (bFlags & 0x400) != 0 )
  {
    nHeight = (double)ptQSpriteEx->tQSprite.atQAnimframe[ptQSpriteEx->tQSprite.nQAnimframes].nHeight * 0.5;
  }
  else if ( (bFlags & 0x800) != 0 )
  {
    nHeight = (double)ptQSpriteEx->tQSprite.atQAnimframe[ptQSpriteEx->tQSprite.nQAnimframes].nHeight;
  }
  ptQSpriteEx->vHotX = vOrgX + vX;
  ptQSpriteEx->vHotY = nHeight + vY;
  return ptQSpriteEx;
}

// source: b/4/qspriteex.c:247  [size]
struct QSpriteEx_s *__cdecl QSpriteEx_SetFlags(
        struct QSpriteEx_s *ptQSpriteEx,
        unsigned int bFlags,
        unsigned int bClearMask)
{
  ptQSpriteEx->tQSpriteDrawInfo.bQGraphicFlags |= bFlags;
  return ptQSpriteEx;
}

// source: b/4/qspriteex.c:261  [anchor-mhash]
struct QSpriteEx_s *__cdecl QSpriteEx_Register(struct QSpriteEx_s *ptQSpriteEx, int nFrame)
{
  unsigned int bQGraphicFlags; // ecx
  struct QSpriteDrawInfo_s *p_tQSpriteDrawInfo; // edx
  int nPri; // eax
  struct QVertexStripContext_s tStrip; // [esp+0h] [ebp-14h] BYREF

  bQGraphicFlags = ptQSpriteEx->tQSpriteDrawInfo.bQGraphicFlags;
  tStrip.nStripLength = (bQGraphicFlags & 0x1000) != 0 ? 4 : 2;
  p_tQSpriteDrawInfo = &ptQSpriteEx->tQSpriteDrawInfo;
  nPri = ptQSpriteEx->nPri;
  tStrip.bFlags = bQGraphicFlags;
  tStrip.atQVertex = (struct QVertex_s *)p_tQSpriteDrawInfo;
  tStrip.nDepth = nPri;
  tStrip.isLine = 0;
  return ((struct QSpriteEx_s *(__cdecl *)(struct QVertexStripContext_s *))RenderMode_tActiveRenderMode.apfRenderModeMethod[QVertex_eRegisterQVertexStripMethod])(&tStrip);
}

// source: b/4/qspriteex.c:300  [anchor-mhash]
struct QSpriteEx_s *__cdecl QSpriteEx_SetUV(
        struct QSpriteEx_s *ptQSpriteEx,
        float vU0,
        float vV0,
        float vU1,
        float vV1,
        float vU2,
        float vV2,
        float vU3,
        float vV3)
{
  ptQSpriteEx->tQSpriteDrawInfo.atQVertex[0].vU = vU0;
  ptQSpriteEx->tQSpriteDrawInfo.atQVertex[0].vV = vV0;
  ptQSpriteEx->tQSpriteDrawInfo.atQVertex[1].vU = vU1;
  ptQSpriteEx->tQSpriteDrawInfo.atQVertex[1].vV = vV1;
  ptQSpriteEx->tQSpriteDrawInfo.atQVertex[2].vU = vU2;
  ptQSpriteEx->tQSpriteDrawInfo.atQVertex[2].vV = vV2;
  ptQSpriteEx->tQSpriteDrawInfo.atQVertex[3].vU = vU3;
  ptQSpriteEx->tQSpriteDrawInfo.atQVertex[3].vV = vV3;
  ptQSpriteEx->tQSpriteDrawInfo.nUV = 4;
  return ptQSpriteEx;
}

// source: b/4/qspriteex.c:323  [anchor-mhash]
void __cdecl QSpriteEx_SetZ(struct QSpriteEx_s *ptQSpriteEx, float vZ)
{
  double v2; // st7

  v2 = vZ;
  ptQSpriteEx->tQSpriteDrawInfo.bQGraphicFlags |= 0x40000u;
  if ( vZ < 1.0 )
    v2 = 1.0;
  ptQSpriteEx->tQSpriteDrawInfo.atQVertex[0].vZ = v2;
  ptQSpriteEx->tQSpriteDrawInfo.atQVertex[1].vZ = v2;
  ptQSpriteEx->tQSpriteDrawInfo.atQVertex[2].vZ = v2;
  ptQSpriteEx->tQSpriteDrawInfo.atQVertex[3].vZ = v2;
}
