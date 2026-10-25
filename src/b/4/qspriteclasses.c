/* b/4/qspriteclasses.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/4/qspriteclasses.c:42  [anchor-callee]
void __cdecl QSprite_RegisterBlank(
        float vX,
        float vY,
        float vWidth,
        float vHeight,
        float vR,
        float vG,
        float vB,
        unsigned int bQGraphicFlags,
        int nDepth)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QVertexStripContext_s tQVertexStripContext; };
    struct { char igi2_o1[20]; struct QVertex_s atQVertex[2]; };
    char igi2_extent[92];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  igi2_frame.atQVertex[0].vX = vX;
  igi2_frame.atQVertex[0].vR = vR * 0.0078125;
  igi2_frame.atQVertex[0].vY = vY;
  igi2_frame.atQVertex[1].vR = igi2_frame.atQVertex[0].vR;
  igi2_frame.tQVertexStripContext.isLine = 0;
  QVertex_ptActiveTexture = nullptr;
  QVertex_ptActivePalette = nullptr;
  igi2_frame.atQVertex[0].vG = vG * 0.0078125;
  igi2_frame.tQVertexStripContext.atQVertex = igi2_frame.atQVertex;
  igi2_frame.atQVertex[1].vG = igi2_frame.atQVertex[0].vG;
  igi2_frame.tQVertexStripContext.bFlags = bQGraphicFlags;
  igi2_frame.atQVertex[0].vB = vB * 0.0078125;
  igi2_frame.atQVertex[0].vA = 1.0;
  igi2_frame.atQVertex[1].vB = igi2_frame.atQVertex[0].vB;
  igi2_frame.atQVertex[1].vA = 1.0;
  igi2_frame.atQVertex[0].vZ = 1.0;
  igi2_frame.atQVertex[1].vZ = 1.0;
  igi2_frame.atQVertex[0].vU = 0.0;
  igi2_frame.atQVertex[0].vV = 0.0;
  igi2_frame.atQVertex[1].vX = vX + vWidth;
  igi2_frame.atQVertex[1].vU = 1.0;
  igi2_frame.atQVertex[1].vV = 1.0;
  igi2_frame.tQVertexStripContext.nDepth = nDepth;
  igi2_frame.tQVertexStripContext.nStripLength = 2;
  igi2_frame.atQVertex[1].vY = vY + vHeight;
  RenderMode_tActiveRenderMode.apfRenderModeMethod[QVertex_eRegisterQVertexStripMethod](&igi2_frame.tQVertexStripContext);
}

// source: b/4/qspriteclasses.c:103  [anchor-callee]
void __cdecl QSprite_RegisterBlankZ(
        float vX,
        float vY,
        float vWidth,
        float vHeight,
        float vR,
        float vG,
        float vB,
        unsigned int bQGraphicFlags,
        int nDepth,
        float vZ)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QVertexStripContext_s tQVertexStripContext; };
    struct { char igi2_o1[20]; struct QVertex_s atQVertex[2]; };
    char igi2_extent[92];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  igi2_frame.atQVertex[0].vZ = vZ;
  igi2_frame.atQVertex[0].vR = vR * 0.0078125;
  igi2_frame.atQVertex[1].vR = igi2_frame.atQVertex[0].vR;
  igi2_frame.atQVertex[0].vX = vX;
  igi2_frame.atQVertex[1].vZ = vZ;
  igi2_frame.atQVertex[0].vY = vY;
  igi2_frame.atQVertex[0].vG = vG * 0.0078125;
  igi2_frame.atQVertex[1].vG = igi2_frame.atQVertex[0].vG;
  igi2_frame.tQVertexStripContext.bFlags = bQGraphicFlags;
  igi2_frame.tQVertexStripContext.atQVertex = igi2_frame.atQVertex;
  igi2_frame.tQVertexStripContext.isLine = 0;
  igi2_frame.atQVertex[0].vB = vB * 0.0078125;
  QVertex_ptActiveTexture = nullptr;
  igi2_frame.atQVertex[1].vB = igi2_frame.atQVertex[0].vB;
  QVertex_ptActivePalette = nullptr;
  igi2_frame.atQVertex[0].vA = 1.0;
  igi2_frame.atQVertex[1].vA = 1.0;
  igi2_frame.atQVertex[1].vX = vX + vWidth;
  igi2_frame.atQVertex[0].vU = 0.0;
  igi2_frame.atQVertex[0].vV = 0.0;
  igi2_frame.atQVertex[1].vU = 1.0;
  igi2_frame.atQVertex[1].vV = 1.0;
  igi2_frame.tQVertexStripContext.nDepth = nDepth;
  igi2_frame.atQVertex[1].vY = vY + vHeight;
  igi2_frame.tQVertexStripContext.nStripLength = 2;
  RenderMode_tActiveRenderMode.apfRenderModeMethod[QVertex_eRegisterQVertexStripMethod](&igi2_frame.tQVertexStripContext);
}

// source: b/4/qspriteclasses.c:162  [anchor-callee]
void __cdecl QSprite_RegisterBlankA(
        float vX,
        float vY,
        float vWidth,
        float vHeight,
        float vR,
        float vG,
        float vB,
        float vA,
        unsigned int bQGraphicFlags,
        int nDepth)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QVertexStripContext_s tQVertexStripContext; };
    struct { char igi2_o1[20]; struct QVertex_s atQVertex[2]; };
    char igi2_extent[92];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  igi2_frame.atQVertex[0].vA = vA;
  igi2_frame.atQVertex[0].vR = vR * 0.0078125;
  igi2_frame.atQVertex[1].vR = igi2_frame.atQVertex[0].vR;
  igi2_frame.atQVertex[0].vX = vX;
  igi2_frame.atQVertex[1].vA = vA;
  igi2_frame.atQVertex[0].vY = vY;
  igi2_frame.atQVertex[0].vG = vG * 0.0078125;
  igi2_frame.atQVertex[1].vG = igi2_frame.atQVertex[0].vG;
  igi2_frame.tQVertexStripContext.bFlags = bQGraphicFlags;
  igi2_frame.tQVertexStripContext.atQVertex = igi2_frame.atQVertex;
  igi2_frame.tQVertexStripContext.isLine = 0;
  igi2_frame.atQVertex[0].vB = vB * 0.0078125;
  QVertex_ptActiveTexture = nullptr;
  igi2_frame.atQVertex[1].vB = igi2_frame.atQVertex[0].vB;
  QVertex_ptActivePalette = nullptr;
  igi2_frame.atQVertex[0].vZ = 1.0;
  igi2_frame.atQVertex[1].vZ = 1.0;
  igi2_frame.atQVertex[1].vX = vX + vWidth;
  igi2_frame.atQVertex[0].vU = 0.0;
  igi2_frame.atQVertex[0].vV = 0.0;
  igi2_frame.atQVertex[1].vU = 1.0;
  igi2_frame.atQVertex[1].vV = 1.0;
  igi2_frame.tQVertexStripContext.nDepth = nDepth;
  igi2_frame.atQVertex[1].vY = vY + vHeight;
  igi2_frame.tQVertexStripContext.nStripLength = 2;
  RenderMode_tActiveRenderMode.apfRenderModeMethod[QVertex_eRegisterQVertexStripMethod](&igi2_frame.tQVertexStripContext);
}

// source: b/4/qspriteclasses.c:222  [anchor-callee]
void __cdecl QSprite_RegisterBlankAZ(
        float vX,
        float vY,
        float vWidth,
        float vHeight,
        float vR,
        float vG,
        float vB,
        float vA,
        float vZ,
        unsigned int bQGraphicFlags,
        int nDepth)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QVertexStripContext_s tQVertexStripContext; };
    struct { char igi2_o1[20]; struct QVertex_s atQVertex[2]; };
    char igi2_extent[92];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  igi2_frame.atQVertex[0].vA = vA;
  igi2_frame.atQVertex[0].vR = vR * 0.0078125;
  igi2_frame.atQVertex[1].vR = igi2_frame.atQVertex[0].vR;
  igi2_frame.atQVertex[0].vZ = vZ;
  igi2_frame.atQVertex[1].vA = vA;
  igi2_frame.atQVertex[0].vY = vY;
  igi2_frame.atQVertex[0].vG = vG * 0.0078125;
  igi2_frame.atQVertex[1].vG = igi2_frame.atQVertex[0].vG;
  igi2_frame.atQVertex[0].vX = vX;
  igi2_frame.atQVertex[1].vZ = vZ;
  igi2_frame.tQVertexStripContext.bFlags = bQGraphicFlags;
  igi2_frame.atQVertex[0].vB = vB * 0.0078125;
  igi2_frame.tQVertexStripContext.atQVertex = igi2_frame.atQVertex;
  igi2_frame.atQVertex[1].vB = igi2_frame.atQVertex[0].vB;
  igi2_frame.tQVertexStripContext.isLine = 0;
  QVertex_ptActiveTexture = nullptr;
  QVertex_ptActivePalette = nullptr;
  igi2_frame.atQVertex[1].vX = vX + vWidth;
  igi2_frame.atQVertex[0].vU = 0.0;
  igi2_frame.atQVertex[0].vV = 0.0;
  igi2_frame.atQVertex[1].vU = 1.0;
  igi2_frame.atQVertex[1].vY = vY + vHeight;
  igi2_frame.atQVertex[1].vV = 1.0;
  igi2_frame.tQVertexStripContext.nDepth = nDepth;
  igi2_frame.tQVertexStripContext.nStripLength = 2;
  RenderMode_tActiveRenderMode.apfRenderModeMethod[QVertex_eRegisterQVertexStripMethod](&igi2_frame.tQVertexStripContext);
}

// source: b/4/qspriteclasses.c:294  [anchor-callee]
void __cdecl QSprite_RegisterBlank4RGBAZ(
        float vX,
        float vY,
        float vWidth,
        float vHeight,
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
        float vB4,
        float vA1,
        float vA2,
        float vA3,
        float vA4,
        float vZ,
        unsigned int bQGraphicFlags,
        int nDepth)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QVertexStripContext_s tQVertexStripContext; };
    struct { char igi2_o1[20]; struct QVertex_s atQVertex[4]; };
    char igi2_extent[164];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  igi2_frame.atQVertex[0].vA = vA1;
  igi2_frame.atQVertex[0].vR = vR1 * 0.0078125;
  igi2_frame.atQVertex[1].vA = vA2;
  igi2_frame.atQVertex[3].vA = vA4;
  igi2_frame.atQVertex[1].vR = vR2 * 0.0078125;
  igi2_frame.atQVertex[2].vA = vA3;
  igi2_frame.atQVertex[2].vZ = vZ;
  igi2_frame.atQVertex[0].vZ = vZ;
  igi2_frame.atQVertex[2].vR = vR3 * 0.0078125;
  igi2_frame.atQVertex[1].vZ = vZ;
  igi2_frame.atQVertex[3].vZ = vZ;
  igi2_frame.atQVertex[0].vX = vX;
  igi2_frame.atQVertex[3].vR = vR4 * 0.0078125;
  igi2_frame.atQVertex[0].vY = vY;
  igi2_frame.atQVertex[1].vY = vY;
  igi2_frame.atQVertex[2].vX = vX;
  igi2_frame.atQVertex[0].vG = vG1 * 0.0078125;
  igi2_frame.atQVertex[0].vU = 0.0;
  igi2_frame.atQVertex[0].vV = 0.0;
  igi2_frame.atQVertex[1].vU = 1.0;
  igi2_frame.atQVertex[1].vV = 0.0;
  igi2_frame.atQVertex[1].vG = vG2 * 0.0078125;
  igi2_frame.atQVertex[2].vU = 0.0;
  igi2_frame.atQVertex[2].vV = 1.0;
  igi2_frame.atQVertex[3].vU = 1.0;
  igi2_frame.atQVertex[3].vV = 1.0;
  igi2_frame.tQVertexStripContext.isLine = 0;
  igi2_frame.atQVertex[2].vG = vG3 * 0.0078125;
  igi2_frame.tQVertexStripContext.atQVertex = igi2_frame.atQVertex;
  igi2_frame.tQVertexStripContext.bFlags = bQGraphicFlags;
  igi2_frame.atQVertex[3].vG = vG4 * 0.0078125;
  igi2_frame.atQVertex[0].vB = vB1 * 0.0078125;
  igi2_frame.atQVertex[1].vB = vB2 * 0.0078125;
  igi2_frame.atQVertex[2].vB = vB3 * 0.0078125;
  igi2_frame.atQVertex[3].vB = vB4 * 0.0078125;
  igi2_frame.atQVertex[1].vX = vX + vWidth;
  igi2_frame.atQVertex[2].vY = vY + vHeight;
  igi2_frame.atQVertex[3].vX = igi2_frame.atQVertex[1].vX;
  igi2_frame.atQVertex[3].vY = igi2_frame.atQVertex[2].vY;
  QVertex_ptActiveTexture = nullptr;
  QVertex_ptActivePalette = nullptr;
  igi2_frame.tQVertexStripContext.nDepth = nDepth;
  igi2_frame.tQVertexStripContext.nStripLength = 4;
  RenderMode_tActiveRenderMode.apfRenderModeMethod[QVertex_eRegisterQVertexStripMethod](&igi2_frame.tQVertexStripContext);
}

// source: b/4/qspriteclasses.c:371  [anchor-callee]
int __cdecl QSprite_Register(
        struct QSprite_s *ptQSprite,
        float vX,
        float vY,
        float vR,
        float vG,
        float vB,
        int nFrame,
        unsigned int bQGraphicFlags,
        int nDepth)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QVertexStripContext_s tQVertexStripContext; };
    struct { char igi2_o1[20]; struct QVertex_s atQVertex[2]; };
    char igi2_extent[92];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QAnimframe_s *atQAnimframe; // edx
  struct QAnimframe_s *v10; // eax
  float vV1; // edx
  double nHeight; // st7
  struct QSprite_s *ptQSpritea = *(struct QSprite_s * *)&vX; // [esp+60h] [ebp+4h] ARGSLOT

  atQAnimframe = ptQSprite->atQAnimframe;
  igi2_frame.atQVertex[0].vA = 1.0;
  igi2_frame.atQVertex[1].vA = 1.0;
  igi2_frame.atQVertex[0].vZ = 1.0;
  igi2_frame.atQVertex[1].vZ = 1.0;
  v10 = &atQAnimframe[nFrame];
  igi2_frame.atQVertex[0].vU = v10->vU0;
  igi2_frame.atQVertex[0].vV = v10->vV0;
  igi2_frame.atQVertex[1].vU = v10->vU1;
  vV1 = v10->vV1;
  igi2_frame.atQVertex[0].vR = vR * 0.0078125;
  igi2_frame.atQVertex[1].vR = igi2_frame.atQVertex[0].vR;
  igi2_frame.atQVertex[1].vV = vV1;
  QVertex_ptActivePalette = ptQSprite->ptPalInfo;
  igi2_frame.atQVertex[0].vG = vG * 0.0078125;
  igi2_frame.atQVertex[1].vG = igi2_frame.atQVertex[0].vG;
  igi2_frame.atQVertex[0].vB = vB * 0.0078125;
  igi2_frame.atQVertex[1].vB = igi2_frame.atQVertex[0].vB;
  igi2_frame.atQVertex[0].vX = (double)v10->nX + vX;
  igi2_frame.atQVertex[0].vY = (double)v10->nY + vY;
  igi2_frame.atQVertex[1].vX = (double)v10->nWidth + (double)v10->nX + vX;
  nHeight = (double)v10->nHeight;
  ptQSpritea = (struct QSprite_s *)v10->nY;
  igi2_frame.tQVertexStripContext.atQVertex = igi2_frame.atQVertex;
  igi2_frame.tQVertexStripContext.bFlags = bQGraphicFlags;
  igi2_frame.tQVertexStripContext.nDepth = nDepth;
  igi2_frame.tQVertexStripContext.isLine = 0;
  igi2_frame.tQVertexStripContext.nStripLength = 2;
  igi2_frame.atQVertex[1].vY = nHeight + (double)(int)ptQSpritea + vY;
  QVertex_ptActiveTexture = v10->ptTexInfo;
  return ((int (__cdecl *)(struct QVertexStripContext_s *))RenderMode_tActiveRenderMode.apfRenderModeMethod[QVertex_eRegisterQVertexStripMethod])(&igi2_frame.tQVertexStripContext);
}

// source: b/4/qspriteclasses.c:435  [anchor-mhash]
int __cdecl QSprite_RegisterZ(
        struct QSprite_s *ptQSprite,
        float vX,
        float vY,
        float vR,
        float vG,
        float vB,
        int nFrame,
        unsigned int bQGraphicFlags,
        int nDepth,
        float vZ)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QVertexStripContext_s tQVertexStripContext; };
    struct { char igi2_o1[20]; struct QVertex_s atQVertex[2]; };
    char igi2_extent[92];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QAnimframe_s *atQAnimframe; // edx
  struct QAnimframe_s *v11; // eax
  float vV1; // edx
  double nHeight; // st7
  signed int bQGraphicFlagsa = *(signed int *)&vZ; // [esp+7Ch] [ebp+20h] ARGSLOT

  igi2_frame.atQVertex[0].vZ = vZ;
  igi2_frame.atQVertex[1].vZ = vZ;
  atQAnimframe = ptQSprite->atQAnimframe;
  igi2_frame.atQVertex[0].vA = 1.0;
  igi2_frame.atQVertex[1].vA = 1.0;
  v11 = &atQAnimframe[nFrame];
  igi2_frame.atQVertex[0].vU = v11->vU0;
  igi2_frame.atQVertex[0].vV = v11->vV0;
  igi2_frame.atQVertex[1].vU = v11->vU1;
  vV1 = v11->vV1;
  igi2_frame.atQVertex[0].vR = vR * 0.0078125;
  igi2_frame.atQVertex[1].vR = igi2_frame.atQVertex[0].vR;
  igi2_frame.atQVertex[1].vV = vV1;
  QVertex_ptActivePalette = ptQSprite->ptPalInfo;
  igi2_frame.atQVertex[0].vG = vG * 0.0078125;
  igi2_frame.atQVertex[1].vG = igi2_frame.atQVertex[0].vG;
  igi2_frame.atQVertex[0].vB = vB * 0.0078125;
  igi2_frame.atQVertex[1].vB = igi2_frame.atQVertex[0].vB;
  igi2_frame.atQVertex[0].vX = (double)v11->nX + vX;
  igi2_frame.atQVertex[0].vY = (double)v11->nY + vY;
  igi2_frame.atQVertex[1].vX = (double)v11->nWidth + (double)v11->nX + vX;
  nHeight = (double)v11->nHeight;
  bQGraphicFlagsa = v11->nY;
  igi2_frame.tQVertexStripContext.atQVertex = igi2_frame.atQVertex;
  igi2_frame.tQVertexStripContext.bFlags = bQGraphicFlags;
  igi2_frame.tQVertexStripContext.nDepth = nDepth;
  igi2_frame.tQVertexStripContext.isLine = 0;
  igi2_frame.tQVertexStripContext.nStripLength = 2;
  igi2_frame.atQVertex[1].vY = nHeight + (double)bQGraphicFlagsa + vY;
  QVertex_ptActiveTexture = v11->ptTexInfo;
  return ((int (__cdecl *)(struct QVertexStripContext_s *))RenderMode_tActiveRenderMode.apfRenderModeMethod[QVertex_eRegisterQVertexStripMethod])(&igi2_frame.tQVertexStripContext);
}

// source: b/4/qspriteclasses.c:500  [anchor-callee]
int __cdecl QSprite_RegisterAZ(
        struct QSprite_s *ptQSprite,
        float vX,
        float vY,
        float vR,
        float vG,
        float vB,
        float vA,
        float vZ,
        int nFrame,
        unsigned int bQGraphicFlags,
        int nDepth)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QVertexStripContext_s tQVertexStripContext; };
    struct { char igi2_o1[20]; struct QVertex_s atQVertex[2]; };
    char igi2_extent[92];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QAnimframe_s *v11; // eax
  float vV1; // edx
  double nHeight; // st7
  int vBa = *(int *)&vA; // [esp+74h] [ebp+18h] ARGSLOT

  igi2_frame.atQVertex[0].vA = vA;
  igi2_frame.atQVertex[1].vA = vA;
  igi2_frame.atQVertex[0].vZ = vZ;
  igi2_frame.atQVertex[1].vZ = vZ;
  v11 = &ptQSprite->atQAnimframe[nFrame];
  igi2_frame.atQVertex[0].vU = v11->vU0;
  igi2_frame.atQVertex[0].vV = v11->vV0;
  igi2_frame.atQVertex[1].vU = v11->vU1;
  vV1 = v11->vV1;
  igi2_frame.atQVertex[0].vR = vR * 0.0078125;
  igi2_frame.atQVertex[1].vR = igi2_frame.atQVertex[0].vR;
  igi2_frame.atQVertex[1].vV = vV1;
  QVertex_ptActivePalette = ptQSprite->ptPalInfo;
  igi2_frame.atQVertex[0].vG = vG * 0.0078125;
  igi2_frame.atQVertex[1].vG = igi2_frame.atQVertex[0].vG;
  igi2_frame.atQVertex[0].vB = vB * 0.0078125;
  igi2_frame.atQVertex[1].vB = igi2_frame.atQVertex[0].vB;
  igi2_frame.atQVertex[0].vX = (double)v11->nX + vX;
  igi2_frame.atQVertex[0].vY = (double)v11->nY + vY;
  igi2_frame.atQVertex[1].vX = (double)v11->nWidth + (double)v11->nX + vX;
  nHeight = (double)v11->nHeight;
  vBa = v11->nY;
  igi2_frame.tQVertexStripContext.atQVertex = igi2_frame.atQVertex;
  igi2_frame.tQVertexStripContext.bFlags = bQGraphicFlags;
  igi2_frame.tQVertexStripContext.nDepth = nDepth;
  igi2_frame.tQVertexStripContext.isLine = 0;
  igi2_frame.tQVertexStripContext.nStripLength = 2;
  igi2_frame.atQVertex[1].vY = nHeight + (double)vBa + vY;
  QVertex_ptActiveTexture = v11->ptTexInfo;
  return ((int (__cdecl *)(struct QVertexStripContext_s *))RenderMode_tActiveRenderMode.apfRenderModeMethod[QVertex_eRegisterQVertexStripMethod])(&igi2_frame.tQVertexStripContext);
}

// source: b/4/qspriteclasses.c:568  [anchor-callee]
void __cdecl QSprite_Register4(
        struct QSprite_s *ptQSprite,
        float vX1,
        float vY1,
        float vX2,
        float vY2,
        float vX3,
        float vY3,
        float vX4,
        float vY4,
        float vR1,
        float vG1,
        float vB1,
        int nFrame,
        unsigned int bQGraphicFlags,
        int nDepth)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QVertexStripContext_s tQVertexStripContext; };
    struct { char igi2_o1[20]; struct QVertex_s atQVertex[4]; };
    char igi2_extent[164];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QAnimframe_s *atQAnimframe; // edx
  struct QAnimframe_s *v16; // eax
  float vV1; // edx
  struct PalInfo *ptPalInfo; // ecx

  atQAnimframe = ptQSprite->atQAnimframe;
  igi2_frame.atQVertex[0].vA = 1.0;
  igi2_frame.atQVertex[1].vA = 1.0;
  igi2_frame.atQVertex[2].vA = 1.0;
  igi2_frame.atQVertex[3].vA = 1.0;
  igi2_frame.atQVertex[0].vZ = 1.0;
  igi2_frame.atQVertex[1].vZ = 1.0;
  igi2_frame.atQVertex[2].vZ = 1.0;
  igi2_frame.atQVertex[3].vZ = 1.0;
  v16 = &atQAnimframe[nFrame];
  igi2_frame.atQVertex[0].vU = v16->vU0;
  igi2_frame.atQVertex[0].vV = v16->vV0;
  igi2_frame.atQVertex[1].vU = v16->vU1;
  igi2_frame.atQVertex[1].vV = v16->vV0;
  igi2_frame.atQVertex[2].vU = v16->vU0;
  igi2_frame.atQVertex[2].vV = v16->vV1;
  igi2_frame.atQVertex[3].vU = v16->vU1;
  vV1 = v16->vV1;
  igi2_frame.atQVertex[0].vR = vR1 * 0.0078125;
  igi2_frame.atQVertex[3].vV = vV1;
  igi2_frame.atQVertex[1].vR = igi2_frame.atQVertex[0].vR;
  igi2_frame.atQVertex[2].vR = igi2_frame.atQVertex[0].vR;
  igi2_frame.atQVertex[0].vX = vX1;
  igi2_frame.atQVertex[3].vR = igi2_frame.atQVertex[0].vR;
  igi2_frame.atQVertex[0].vY = vY1;
  igi2_frame.atQVertex[1].vX = vX2;
  igi2_frame.atQVertex[0].vG = vG1 * 0.0078125;
  igi2_frame.atQVertex[1].vY = vY2;
  igi2_frame.atQVertex[1].vG = igi2_frame.atQVertex[0].vG;
  igi2_frame.atQVertex[2].vG = igi2_frame.atQVertex[0].vG;
  ptPalInfo = ptQSprite->ptPalInfo;
  igi2_frame.atQVertex[3].vG = igi2_frame.atQVertex[0].vG;
  igi2_frame.atQVertex[2].vX = vX3;
  igi2_frame.atQVertex[2].vY = vY3;
  igi2_frame.atQVertex[3].vX = vX4;
  igi2_frame.atQVertex[0].vB = vB1 * 0.0078125;
  igi2_frame.atQVertex[1].vB = igi2_frame.atQVertex[0].vB;
  igi2_frame.atQVertex[3].vY = vY4;
  igi2_frame.atQVertex[2].vB = igi2_frame.atQVertex[0].vB;
  igi2_frame.atQVertex[3].vB = igi2_frame.atQVertex[0].vB;
  igi2_frame.tQVertexStripContext.atQVertex = igi2_frame.atQVertex;
  igi2_frame.tQVertexStripContext.bFlags = bQGraphicFlags;
  igi2_frame.tQVertexStripContext.nDepth = nDepth;
  igi2_frame.tQVertexStripContext.isLine = 0;
  igi2_frame.tQVertexStripContext.nStripLength = 4;
  QVertex_ptActiveTexture = v16->ptTexInfo;
  QVertex_ptActivePalette = ptPalInfo;
  RenderMode_tActiveRenderMode.apfRenderModeMethod[QVertex_eRegisterQVertexStripMethod](&igi2_frame.tQVertexStripContext);
}

// source: b/4/qspriteclasses.c:673  [anchor-callee]
void __cdecl QSprite_Register4AZ(
        struct QSprite_s *ptQSprite,
        float vX1,
        float vY1,
        float vX2,
        float vY2,
        float vX3,
        float vY3,
        float vX4,
        float vY4,
        float vR1,
        float vG1,
        float vB1,
        float vA,
        float vZ,
        int nFrame,
        unsigned int bQGraphicFlags,
        int nDepth)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QVertexStripContext_s tQVertexStripContext; };
    struct { char igi2_o1[20]; struct QVertex_s atQVertex[4]; };
    char igi2_extent[164];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QAnimframe_s *v17; // eax
  float vV1; // edx
  struct PalInfo *ptPalInfo; // ecx

  igi2_frame.atQVertex[0].vA = vA;
  igi2_frame.atQVertex[1].vA = vA;
  igi2_frame.atQVertex[2].vA = vA;
  igi2_frame.atQVertex[3].vA = vA;
  igi2_frame.atQVertex[0].vZ = vZ;
  igi2_frame.atQVertex[1].vZ = vZ;
  igi2_frame.atQVertex[2].vZ = vZ;
  igi2_frame.atQVertex[3].vZ = vZ;
  v17 = &ptQSprite->atQAnimframe[nFrame];
  igi2_frame.atQVertex[0].vU = v17->vU0;
  igi2_frame.atQVertex[0].vV = v17->vV0;
  igi2_frame.atQVertex[1].vU = v17->vU1;
  igi2_frame.atQVertex[1].vV = v17->vV0;
  igi2_frame.atQVertex[2].vU = v17->vU0;
  igi2_frame.atQVertex[2].vV = v17->vV1;
  igi2_frame.atQVertex[3].vU = v17->vU1;
  vV1 = v17->vV1;
  igi2_frame.atQVertex[0].vR = vR1 * 0.0078125;
  igi2_frame.atQVertex[3].vV = vV1;
  igi2_frame.atQVertex[1].vR = igi2_frame.atQVertex[0].vR;
  igi2_frame.atQVertex[2].vR = igi2_frame.atQVertex[0].vR;
  igi2_frame.atQVertex[0].vX = vX1;
  igi2_frame.atQVertex[3].vR = igi2_frame.atQVertex[0].vR;
  igi2_frame.atQVertex[0].vY = vY1;
  igi2_frame.atQVertex[1].vX = vX2;
  igi2_frame.atQVertex[0].vG = vG1 * 0.0078125;
  igi2_frame.atQVertex[1].vY = vY2;
  igi2_frame.atQVertex[1].vG = igi2_frame.atQVertex[0].vG;
  igi2_frame.atQVertex[2].vG = igi2_frame.atQVertex[0].vG;
  ptPalInfo = ptQSprite->ptPalInfo;
  igi2_frame.atQVertex[3].vG = igi2_frame.atQVertex[0].vG;
  igi2_frame.atQVertex[2].vX = vX3;
  igi2_frame.atQVertex[2].vY = vY3;
  igi2_frame.atQVertex[3].vX = vX4;
  igi2_frame.atQVertex[0].vB = vB1 * 0.0078125;
  igi2_frame.atQVertex[1].vB = igi2_frame.atQVertex[0].vB;
  igi2_frame.atQVertex[3].vY = vY4;
  igi2_frame.atQVertex[2].vB = igi2_frame.atQVertex[0].vB;
  igi2_frame.atQVertex[3].vB = igi2_frame.atQVertex[0].vB;
  igi2_frame.tQVertexStripContext.atQVertex = igi2_frame.atQVertex;
  igi2_frame.tQVertexStripContext.bFlags = bQGraphicFlags;
  igi2_frame.tQVertexStripContext.nDepth = nDepth;
  igi2_frame.tQVertexStripContext.isLine = 0;
  igi2_frame.tQVertexStripContext.nStripLength = 4;
  QVertex_ptActiveTexture = v17->ptTexInfo;
  QVertex_ptActivePalette = ptPalInfo;
  RenderMode_tActiveRenderMode.apfRenderModeMethod[QVertex_eRegisterQVertexStripMethod](&igi2_frame.tQVertexStripContext);
}

// source: b/4/qspriteclasses.c:775  [anchor-callee]
void __cdecl QSprite_Register4AZUV(
        struct QSprite_s *ptQSprite,
        float vX1,
        float vY1,
        float vX2,
        float vY2,
        float vX3,
        float vY3,
        float vX4,
        float vY4,
        float vU1,
        float vV1,
        float vU2,
        float vV2,
        float vU3,
        float vV3,
        float vU4,
        float vV4,
        float vR1,
        float vG1,
        float vB1,
        float vA,
        float vZ,
        int nFrame,
        unsigned int bQGraphicFlags,
        int nDepth)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QVertexStripContext_s tQVertexStripContext; };
    struct { char igi2_o1[20]; struct QVertex_s atQVertex[4]; };
    char igi2_extent[164];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QAnimframe_s *atQAnimframe; // edx
  struct PalInfo *ptPalInfo; // ecx

  igi2_frame.atQVertex[0].vA = vA;
  igi2_frame.atQVertex[1].vA = vA;
  igi2_frame.atQVertex[2].vA = vA;
  igi2_frame.atQVertex[3].vA = vA;
  igi2_frame.atQVertex[0].vR = vR1 * 0.0078125;
  igi2_frame.atQVertex[1].vR = igi2_frame.atQVertex[0].vR;
  igi2_frame.atQVertex[0].vZ = vZ;
  igi2_frame.atQVertex[2].vR = igi2_frame.atQVertex[0].vR;
  igi2_frame.atQVertex[1].vZ = vZ;
  igi2_frame.atQVertex[3].vR = igi2_frame.atQVertex[0].vR;
  igi2_frame.atQVertex[2].vZ = vZ;
  igi2_frame.atQVertex[3].vZ = vZ;
  igi2_frame.atQVertex[0].vU = vU1;
  igi2_frame.atQVertex[0].vG = vG1 * 0.0078125;
  igi2_frame.atQVertex[0].vV = vV1;
  igi2_frame.atQVertex[1].vG = igi2_frame.atQVertex[0].vG;
  igi2_frame.atQVertex[2].vG = igi2_frame.atQVertex[0].vG;
  igi2_frame.atQVertex[1].vU = vU2;
  igi2_frame.atQVertex[3].vG = igi2_frame.atQVertex[0].vG;
  igi2_frame.atQVertex[1].vV = vV2;
  igi2_frame.atQVertex[2].vU = vU3;
  igi2_frame.atQVertex[0].vB = vB1 * 0.0078125;
  igi2_frame.atQVertex[2].vV = vV3;
  igi2_frame.atQVertex[1].vB = igi2_frame.atQVertex[0].vB;
  igi2_frame.atQVertex[2].vB = igi2_frame.atQVertex[0].vB;
  igi2_frame.atQVertex[3].vU = vU4;
  igi2_frame.atQVertex[3].vB = igi2_frame.atQVertex[0].vB;
  igi2_frame.atQVertex[3].vV = vV4;
  igi2_frame.atQVertex[0].vX = vX1;
  igi2_frame.atQVertex[0].vY = vY1;
  igi2_frame.atQVertex[1].vX = vX2;
  igi2_frame.atQVertex[1].vY = vY2;
  igi2_frame.atQVertex[2].vX = vX3;
  igi2_frame.atQVertex[2].vY = vY3;
  igi2_frame.atQVertex[3].vX = vX4;
  igi2_frame.atQVertex[3].vY = vY4;
  igi2_frame.tQVertexStripContext.atQVertex = igi2_frame.atQVertex;
  igi2_frame.tQVertexStripContext.bFlags = bQGraphicFlags;
  igi2_frame.tQVertexStripContext.nDepth = nDepth;
  atQAnimframe = ptQSprite->atQAnimframe;
  ptPalInfo = ptQSprite->ptPalInfo;
  igi2_frame.tQVertexStripContext.isLine = 0;
  igi2_frame.tQVertexStripContext.nStripLength = 4;
  QVertex_ptActiveTexture = atQAnimframe[nFrame].ptTexInfo;
  QVertex_ptActivePalette = ptPalInfo;
  RenderMode_tActiveRenderMode.apfRenderModeMethod[QVertex_eRegisterQVertexStripMethod](&igi2_frame.tQVertexStripContext);
}

// source: b/4/qspriteclasses.c:881  [anchor-mhash]
void __cdecl QSprite_Register4RGBAZ(
        struct QSprite_s *ptQSprite,
        float vX1,
        float vY1,
        float vX2,
        float vY2,
        float vX3,
        float vY3,
        float vX4,
        float vY4,
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
        float vB4,
        float vA1,
        float vA2,
        float vA3,
        float vA4,
        float vZ,
        int nFrame,
        unsigned int bQGraphicFlags,
        int nDepth)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QVertexStripContext_s tQVertexStripContext; };
    struct { char igi2_o1[20]; struct QVertex_s atQVertex[4]; };
    char igi2_extent[164];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QAnimframe_s *v29; // eax
  float vV1; // edx
  struct PalInfo *ptPalInfo; // ecx

  igi2_frame.atQVertex[0].vA = vA1;
  igi2_frame.atQVertex[1].vA = vA2;
  igi2_frame.atQVertex[2].vA = vA3;
  igi2_frame.atQVertex[3].vA = vA4;
  igi2_frame.atQVertex[0].vZ = vZ;
  igi2_frame.atQVertex[1].vZ = vZ;
  igi2_frame.atQVertex[2].vZ = vZ;
  igi2_frame.atQVertex[3].vZ = vZ;
  v29 = &ptQSprite->atQAnimframe[nFrame];
  igi2_frame.atQVertex[0].vU = v29->vU0;
  igi2_frame.atQVertex[0].vV = v29->vV0;
  igi2_frame.atQVertex[1].vU = v29->vU1;
  igi2_frame.atQVertex[1].vV = v29->vV0;
  igi2_frame.atQVertex[2].vU = v29->vU0;
  igi2_frame.atQVertex[2].vV = v29->vV1;
  igi2_frame.atQVertex[3].vU = v29->vU1;
  vV1 = v29->vV1;
  igi2_frame.atQVertex[0].vR = vR1 * 0.0078125;
  igi2_frame.atQVertex[3].vV = vV1;
  igi2_frame.atQVertex[0].vX = vX1;
  igi2_frame.atQVertex[1].vR = vR2 * 0.0078125;
  igi2_frame.atQVertex[0].vY = vY1;
  igi2_frame.atQVertex[1].vX = vX2;
  igi2_frame.atQVertex[1].vY = vY2;
  igi2_frame.atQVertex[2].vR = vR3 * 0.0078125;
  igi2_frame.atQVertex[2].vX = vX3;
  igi2_frame.atQVertex[2].vY = vY3;
  igi2_frame.atQVertex[3].vR = vR4 * 0.0078125;
  igi2_frame.atQVertex[0].vG = vG1 * 0.0078125;
  igi2_frame.atQVertex[1].vG = vG2 * 0.0078125;
  igi2_frame.atQVertex[2].vG = vG3 * 0.0078125;
  igi2_frame.atQVertex[3].vG = vG4 * 0.0078125;
  igi2_frame.atQVertex[0].vB = vB1 * 0.0078125;
  igi2_frame.atQVertex[1].vB = vB2 * 0.0078125;
  igi2_frame.atQVertex[2].vB = vB3 * 0.0078125;
  igi2_frame.atQVertex[3].vB = vB4 * 0.0078125;
  ptPalInfo = ptQSprite->ptPalInfo;
  igi2_frame.atQVertex[3].vX = vX4;
  igi2_frame.atQVertex[3].vY = vY4;
  igi2_frame.tQVertexStripContext.atQVertex = igi2_frame.atQVertex;
  igi2_frame.tQVertexStripContext.bFlags = bQGraphicFlags;
  igi2_frame.tQVertexStripContext.nDepth = nDepth;
  igi2_frame.tQVertexStripContext.isLine = 0;
  igi2_frame.tQVertexStripContext.nStripLength = 4;
  QVertex_ptActiveTexture = v29->ptTexInfo;
  QVertex_ptActivePalette = ptPalInfo;
  RenderMode_tActiveRenderMode.apfRenderModeMethod[QVertex_eRegisterQVertexStripMethod](&igi2_frame.tQVertexStripContext);
}

// source: b/4/qspriteclasses.c:978  [anchor-callee]
void __cdecl QSprite_RegisterLine(
        float vX1,
        float vY1,
        float vZ1,
        float vX2,
        float vY2,
        float vZ2,
        float vR1,
        float vG1,
        float vB1,
        float vR2,
        float vG2,
        float vB2,
        float vAlpha,
        float vThickness,
        unsigned int bFlags,
        int nDepth)
{
  #pragma pack(push, 1)
  union
  {
    struct { float tNormal; };
    struct { float tNormala; };
    struct { float tNormalb; };
    struct { char igi2_o3[4]; float tNormal_4; };
    struct { char igi2_o4[4]; float tNormal_4a; };
    struct { char igi2_o5[8]; float tDelta; };
    struct { char igi2_o6[8]; float tDeltaa; };
    struct { char igi2_o7[8]; float tDeltab; };
    struct { char igi2_o8[12]; float tDelta_4; };
    struct { char igi2_o9[16]; float tEndPoint1; };
    struct { char igi2_o10[16]; float tEndPoint1a; };
    struct { char igi2_o11[20]; float tEndPoint1_4; };
    struct { char igi2_o12[24]; float tEndPoint2; };
    struct { char igi2_o13[28]; float tEndPoint2_4; };
    struct { char igi2_o14[32]; struct QVertexStripContext_s tQVertexStripContext; };
    struct { char igi2_o15[52]; struct QVertex_s atQVertex[4]; };
    struct { char igi2_o16[196]; struct real32x2_t atVertex[4]; };
    char igi2_extent[232];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v16; // st7
  double v17; // st6
  long double v18; // st3
  long double v19; // st7
  long double v20; // rt0
  double v21; // st7

  igi2_frame.tQVertexStripContext.bFlags = bFlags;
  igi2_frame.tQVertexStripContext.nDepth = nDepth;
  igi2_frame.tQVertexStripContext.atQVertex = igi2_frame.atQVertex;
  if ( vThickness == 1.0 )
  {
    igi2_frame.atQVertex[0].vZ = vZ1;
    igi2_frame.atQVertex[0].vR = vR1 * 0.0078125;
    igi2_frame.atQVertex[0].vA = vAlpha;
    igi2_frame.atQVertex[0].vU = 0.0;
    igi2_frame.atQVertex[0].vV = 0.0;
    igi2_frame.atQVertex[1].vA = vAlpha;
    igi2_frame.atQVertex[1].vU = 0.0;
    igi2_frame.atQVertex[0].vG = vG1 * 0.0078125;
    igi2_frame.atQVertex[1].vV = 0.0;
    igi2_frame.atQVertex[1].vZ = vZ2;
    igi2_frame.tQVertexStripContext.isLine = 1;
    igi2_frame.tQVertexStripContext.nStripLength = 2;
    igi2_frame.atQVertex[0].vB = vB1 * 0.0078125;
    igi2_frame.atQVertex[0].vX = vX1 - 0.5;
    igi2_frame.atQVertex[0].vY = vY1 - 0.5;
    igi2_frame.atQVertex[1].vR = vR2 * 0.0078125;
    igi2_frame.atQVertex[1].vG = vG2 * 0.0078125;
    igi2_frame.atQVertex[1].vB = vB2 * 0.0078125;
    igi2_frame.atQVertex[1].vX = vX2 - 0.5;
    igi2_frame.atQVertex[1].vY = vY2 - 0.5;
  }
  else
  {
    v16 = vX2 - vX1;
    v17 = vY2 - vY1;
    v18 = sqrt(v16 * v16 + v17 * v17);
    if ( v18 == 0.0 )
    {
      igi2_frame.tDelta = 1.0;
      v19 = 0.0;
    }
    else
    {
      v20 = 1.0 / v18;
      igi2_frame.tDelta = v16 * v20;
      v19 = v17 * v20;
    }
    igi2_frame.tNormal_4 = igi2_frame.tDelta;
    igi2_frame.atQVertex[0].vA = vAlpha;
    igi2_frame.atQVertex[0].vZ = vZ1;
    igi2_frame.atQVertex[0].vU = 0.0;
    igi2_frame.atQVertex[0].vV = 0.0;
    igi2_frame.tDeltaa = igi2_frame.tDelta * vThickness * 0.5;
    igi2_frame.tDelta_4 = v19 * vThickness * 0.5;
    igi2_frame.tNormal = -v19 * vThickness * 0.5;
    igi2_frame.tNormal_4a = igi2_frame.tNormal_4 * vThickness * 0.5;
    igi2_frame.tEndPoint1 = vX1 - igi2_frame.tDeltaa;
    igi2_frame.tEndPoint1_4 = vY1 - igi2_frame.tDelta_4;
    igi2_frame.tEndPoint2 = igi2_frame.tDeltaa + vX2;
    igi2_frame.tEndPoint2_4 = igi2_frame.tDelta_4 + vY2;
    v21 = igi2_frame.tEndPoint1 - igi2_frame.tNormal;
    igi2_frame.atVertex[1].vX = igi2_frame.tEndPoint1 + igi2_frame.tNormal;
    igi2_frame.atVertex[1].vY = igi2_frame.tEndPoint1_4 + igi2_frame.tNormal_4a;
    igi2_frame.atVertex[2].vX = igi2_frame.tEndPoint2 + igi2_frame.tNormal;
    igi2_frame.atVertex[2].vY = igi2_frame.tEndPoint2_4 + igi2_frame.tNormal_4a;
    igi2_frame.atVertex[3].vX = igi2_frame.tEndPoint2 - igi2_frame.tNormal;
    igi2_frame.atVertex[3].vY = igi2_frame.tEndPoint2_4 - igi2_frame.tNormal_4a;
    igi2_frame.tEndPoint1a = vR1 * 0.0078125;
    igi2_frame.atQVertex[0].vR = igi2_frame.tEndPoint1a;
    igi2_frame.atQVertex[1].vR = igi2_frame.tEndPoint1a;
    igi2_frame.tDeltab = vG1 * 0.0078125;
    igi2_frame.atQVertex[0].vG = igi2_frame.tDeltab;
    igi2_frame.atQVertex[1].vG = igi2_frame.tDeltab;
    igi2_frame.tNormala = vB1 * 0.0078125;
    igi2_frame.atQVertex[0].vB = igi2_frame.tNormala;
    igi2_frame.atQVertex[1].vB = igi2_frame.tNormala;
    igi2_frame.atQVertex[0].vX = v21;
    igi2_frame.atQVertex[0].vY = igi2_frame.tEndPoint1_4 - igi2_frame.tNormal_4a;
    igi2_frame.atQVertex[1].vA = vAlpha;
    igi2_frame.atQVertex[1].vX = igi2_frame.atVertex[1].vX;
    igi2_frame.atQVertex[2].vR = vR2 * 0.0078125;
    igi2_frame.atQVertex[1].vY = igi2_frame.atVertex[1].vY;
    igi2_frame.atQVertex[1].vZ = vZ1;
    igi2_frame.atQVertex[2].vG = vG2 * 0.0078125;
    igi2_frame.atQVertex[2].vA = vAlpha;
    igi2_frame.atQVertex[2].vX = igi2_frame.atVertex[3].vX;
    igi2_frame.atQVertex[2].vY = igi2_frame.atVertex[3].vY;
    igi2_frame.tNormalb = vB2 * 0.0078125;
    igi2_frame.atQVertex[2].vZ = vZ2;
    igi2_frame.atQVertex[2].vB = igi2_frame.tNormalb;
    igi2_frame.atQVertex[3].vB = igi2_frame.tNormalb;
    igi2_frame.atQVertex[3].vR = igi2_frame.atQVertex[2].vR;
    igi2_frame.atQVertex[3].vA = vAlpha;
    igi2_frame.atQVertex[3].vG = igi2_frame.atQVertex[2].vG;
    igi2_frame.atQVertex[3].vX = igi2_frame.atVertex[2].vX;
    igi2_frame.atQVertex[1].vU = 0.0;
    igi2_frame.atQVertex[1].vV = 0.0;
    igi2_frame.atQVertex[2].vU = 0.0;
    igi2_frame.atQVertex[2].vV = 0.0;
    igi2_frame.atQVertex[3].vU = 0.0;
    igi2_frame.atQVertex[3].vV = 0.0;
    igi2_frame.atQVertex[3].vY = igi2_frame.atVertex[2].vY;
    igi2_frame.atQVertex[3].vZ = vZ2;
    igi2_frame.tQVertexStripContext.isLine = 0;
    igi2_frame.tQVertexStripContext.nStripLength = 4;
  }
  QVertex_ptActiveTexture = nullptr;
  QVertex_ptActivePalette = nullptr;
  RenderMode_tActiveRenderMode.apfRenderModeMethod[QVertex_eRegisterQVertexStripMethod](&igi2_frame.tQVertexStripContext);
}

// source: b/4/qspriteclasses.c:1121  [anchor-callee]
int __cdecl QSprite_RegisterLineMesh(
        struct real32x2_t *atMesh,
        int nVertices,
        float vX,
        float vY,
        float vZ,
        float vR,
        float vG,
        float vB,
        float vAlpha,
        float vThickness,
        float vGamma,
        float vXScale,
        float vYScale,
        unsigned int bFlags,
        int nDepth)
{
  int result; // eax
  struct real32x2_t *v16; // ecx
  double v17; // st7
  double v18; // st6
  double v19; // st5
  bool v20; // zf
  float vX1; // [esp+0h] [ebp-6Ch]
  float vY1; // [esp+4h] [ebp-68h]
  float vX2; // [esp+Ch] [ebp-60h]
  float vY2; // [esp+10h] [ebp-5Ch]
  float vSin; // [esp+50h] [ebp-1Ch]
  float vCos; // [esp+54h] [ebp-18h]
  float v27; // [esp+58h] [ebp-14h]
  struct real32x2_t *v28; // [esp+5Ch] [ebp-10h]
  float v29; // [esp+60h] [ebp-Ch]
  int v30; // [esp+64h] [ebp-8h]
  float vYTemp; // [esp+68h] [ebp-4h]

  result = nVertices - 1;
  vCos = cos(vGamma);
  vSin = sin(vGamma);
  if ( result > 0 )
  {
    v16 = atMesh + 1;
    v28 = v16;
    v30 = result;
    while ( 1 )
    {
      v17 = vXScale * v16[-1].vX;
      v18 = vYScale * v16[-1].vY;
      v27 = vXScale * v16->vX;
      v19 = vYScale * v16->vY;
      v29 = v19;
      if ( vGamma != 0.0 )
      {
        vYTemp = v17 * vSin + v18 * vCos;
        v17 = -(v18 * vSin - v17 * vCos);
        v18 = vYTemp;
        v19 = v27 * vSin + v29 * vCos;
        v27 = -(v29 * vSin - v27 * vCos);
      }
      vY2 = v19 + vY;
      vX2 = v27 + vX;
      vY1 = v18 + vY;
      vX1 = v17 + vX;
      QSprite_RegisterLine(vX1, vY1, vZ, vX2, vY2, vZ, vR, vG, vB, vR, vG, vB, vAlpha, vThickness, bFlags, nDepth);
      result = v30 - 1;
      v20 = v30 == 1;
      ++v28;
      --v30;
      if ( v20 )
        break;
      v16 = v28;
    }
  }
  return result;
}

// source: b/4/qspriteclasses.c:1181  [anchor-mhash]
int __cdecl QSprite_CalcCircleSegmentVertices(
        float vStartAngle,
        float vEndAngle,
        float vRadius,
        float vDetail)
{
  int result; // eax

  result = (__int64)(sqrt(vRadius) * (vEndAngle - vStartAngle) * vDetail * 0.5) + 1;
  if ( result < 2 )
    return 2;
  return result;
}

// source: b/4/qspriteclasses.c:1208  [anchor-mhash]
void __cdecl QSprite_CreateCircleSegment(
        struct real32x2_t *patMesh,
        float vStartAngle,
        float vEndAngle,
        float vRadius,
        int nVertices)
{
  long double v5; // st7
  int v6; // eax
  float vStep; // [esp+0h] [ebp-4h]

  if ( nVertices > 1 )
  {
    v5 = vStartAngle;
    v6 = 0;
    do
    {
      patMesh[v6++].vX = cos(v5) * vRadius;
      patMesh[v6 - 1].vY = sin(v5) * vRadius;
      vStep = (vEndAngle - vStartAngle) / (double)(nVertices - 1);
      v5 = v5 + vStep;
    }
    while ( v6 < nVertices );
  }
}
