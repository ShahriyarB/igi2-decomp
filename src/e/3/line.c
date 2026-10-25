/* e/3/line.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: e/3/line.c:34  [anchor-mhash]
void __cdecl Line_RegisterLine3D(
        struct real64x3_t *ptStart,
        struct real64x3_t *ptEnd,
        struct real32x3_t *ptStartColor,
        float vStartAlpha,
        struct real32x3_t *ptEndColor,
        float vEndAlpha)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vStopDist; };
    struct { char igi2_o1[4]; float vStartDist; };
    struct { char igi2_o2[8]; struct real64x3_t tStartPos; };
    struct { char igi2_o3[32]; struct real64x3_t tEndPos; };
    struct { char igi2_o4[56]; struct real32x2_t tEndScreenPos; };
    struct { char igi2_o5[64]; struct real32x2_t tStartScreenPos; };
    struct { char igi2_o6[72]; struct QVertex_s atQVertex[2]; };
    char igi2_extent[144];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char v6; // fps^1
  bool v7; // c0
  char v8; // c2
  bool v9; // c3
  char v10; // ah
  bool v11; // c0
  bool v12; // c3
  double v13; // st7
  double v14; // st7
  float vY; // ecx
  float vZ; // edx
  float v17; // eax
  float vX; // ecx
  float v19; // edx

  if ( vStartAlpha != 0.0 || vEndAlpha != 0.0 )
  {
    qmemcpy(&igi2_frame.tStartPos, ptStart, sizeof(igi2_frame.tStartPos));
    qmemcpy(&igi2_frame.tEndPos, ptEnd, sizeof(igi2_frame.tEndPos));
    igi2_frame.vStartDist = TransContext_tActiveTransContext.tMatrix.tZ.vZ
               * (igi2_frame.tStartPos.vZ - TransContext_tActiveTransContext.tPos.vZ)
               + TransContext_tActiveTransContext.tMatrix.tZ.vY
               * (igi2_frame.tStartPos.vY - TransContext_tActiveTransContext.tPos.vY)
               + TransContext_tActiveTransContext.tMatrix.tZ.vX
               * (igi2_frame.tStartPos.vX - TransContext_tActiveTransContext.tPos.vX);
    igi2_frame.vStopDist = TransContext_tActiveTransContext.tMatrix.tZ.vZ * (igi2_frame.tEndPos.vZ - TransContext_tActiveTransContext.tPos.vZ)
              + TransContext_tActiveTransContext.tMatrix.tZ.vY * (igi2_frame.tEndPos.vY - TransContext_tActiveTransContext.tPos.vY)
              + TransContext_tActiveTransContext.tMatrix.tZ.vX * (igi2_frame.tEndPos.vX - TransContext_tActiveTransContext.tPos.vX);
    v7 = igi2_frame.vStartDist < 409.6000061035156;
    v8 = 0;
    v9 = igi2_frame.vStartDist == 409.6000061035156;
    v6 = (char)(v7 | (v8 << 2) | (v9 << 6));
    v10 = v6;
    v11 = igi2_frame.vStopDist < 409.6000061035156;
    v12 = igi2_frame.vStopDist == 409.6000061035156;
    v6 = (char)(v11 | (0 << 2) | (v12 << 6));
    if ( __SETP__(v10 & 0x41, 0) )
    {
      if ( v11 || v12 )
      {
        v14 = (409.6000061035156 - igi2_frame.vStopDist) / (igi2_frame.vStartDist - igi2_frame.vStopDist);
        igi2_frame.tEndPos.vX = (igi2_frame.tStartPos.vX - igi2_frame.tEndPos.vX) * v14 + igi2_frame.tEndPos.vX;
        igi2_frame.tEndPos.vY = (igi2_frame.tStartPos.vY - igi2_frame.tEndPos.vY) * v14 + igi2_frame.tEndPos.vY;
        igi2_frame.tEndPos.vZ = v14 * (igi2_frame.tStartPos.vZ - igi2_frame.tEndPos.vZ) + igi2_frame.tEndPos.vZ;
      }
    }
    else
    {
      if ( v11 || v12 )
        return;
      v13 = (409.6000061035156 - igi2_frame.vStartDist) / (igi2_frame.vStopDist - igi2_frame.vStartDist);
      igi2_frame.tStartPos.vX = (igi2_frame.tEndPos.vX - igi2_frame.tStartPos.vX) * v13 + igi2_frame.tStartPos.vX;
      igi2_frame.tStartPos.vY = (igi2_frame.tEndPos.vY - igi2_frame.tStartPos.vY) * v13 + igi2_frame.tStartPos.vY;
      igi2_frame.tStartPos.vZ = v13 * (igi2_frame.tEndPos.vZ - igi2_frame.tStartPos.vZ) + igi2_frame.tStartPos.vZ;
    }
    TransContext_ProjectWorldPos2(&TransContext_tActiveTransContext, &igi2_frame.tStartScreenPos, &igi2_frame.vStartDist, &igi2_frame.tStartPos);
    TransContext_ProjectWorldPos2(&TransContext_tActiveTransContext, &igi2_frame.tEndScreenPos, &igi2_frame.vStopDist, &igi2_frame.tEndPos);
    vY = ptStartColor->vY;
    igi2_frame.atQVertex[0].vR = ptStartColor->vX;
    vZ = ptStartColor->vZ;
    igi2_frame.atQVertex[0].vA = vStartAlpha;
    igi2_frame.atQVertex[0].vG = vY;
    igi2_frame.atQVertex[0].vY = igi2_frame.tStartScreenPos.vY;
    v17 = ptEndColor->vZ;
    igi2_frame.atQVertex[0].vB = vZ;
    igi2_frame.atQVertex[0].vZ = igi2_frame.vStartDist;
    vX = ptEndColor->vX;
    igi2_frame.atQVertex[1].vB = v17;
    igi2_frame.atQVertex[0].vX = igi2_frame.tStartScreenPos.vX;
    v19 = ptEndColor->vY;
    igi2_frame.atQVertex[1].vR = vX;
    igi2_frame.atQVertex[1].vX = igi2_frame.tEndScreenPos.vX;
    igi2_frame.atQVertex[1].vG = v19;
    igi2_frame.atQVertex[1].vA = vEndAlpha;
    igi2_frame.atQVertex[0].vU = 0.0;
    igi2_frame.atQVertex[0].vV = 0.0;
    igi2_frame.atQVertex[1].vU = 0.0;
    igi2_frame.atQVertex[1].vV = 0.0;
    igi2_frame.atQVertex[1].vZ = igi2_frame.vStopDist;
    igi2_frame.atQVertex[1].vY = igi2_frame.tEndScreenPos.vY;
    if ( vStartAlpha != 1.0 || (HIDWORD(igi2_frame.tStartPos.vX) = 1074135040, vEndAlpha != 1.0) )
      HIDWORD(igi2_frame.tStartPos.vX) = 786432;
    *(_QWORD *)&igi2_frame.tStartPos.vY = 0x200000000LL;
    QVertex_ptActiveTexture = nullptr;
    QVertex_ptActivePalette = nullptr;
    LODWORD(igi2_frame.tStartPos.vX) = 1;
    LODWORD(igi2_frame.tStartPos.vZ) = igi2_frame.atQVertex;
    RenderMode_tActiveRenderMode.apfRenderModeMethod[QVertex_eRegisterQVertexStripMethod](&igi2_frame.tStartPos);
  }
}

// source: e/3/line.c:167  [anchor-mhash]
void __cdecl Line_DrawLine3D(
        struct real64x3_t *ptStart,
        struct real64x3_t *ptEnd,
        struct real32x3_t *ptStartColor,
        float vStartAlpha,
        struct real32x3_t *ptEndColor,
        float vEndAlpha)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vStopDist; };
    struct { char igi2_o1[4]; float vStartDist; };
    struct { char igi2_o2[8]; struct real64x3_t tStartPos; };
    struct { char igi2_o3[32]; struct real64x3_t tEndPos; };
    struct { char igi2_o4[56]; struct real32x2_t tEndScreenPos; };
    struct { char igi2_o5[64]; struct real32x2_t tStartScreenPos; };
    struct { char igi2_o6[72]; struct QVertex_s atQVertex[2]; };
    char igi2_extent[148];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char v6; // fps^1
  bool v7; // c0
  char v8; // c2
  bool v9; // c3
  char v10; // ah
  bool v11; // c0
  bool v12; // c3
  double v13; // st7
  double v14; // st7
  float vX; // edx
  float vZ; // ecx
  float v17; // eax
  float vY; // ecx
  float v19; // edx

  if ( vStartAlpha != 0.0 || vEndAlpha != 0.0 )
  {
    qmemcpy(&igi2_frame.tStartPos, ptStart, sizeof(igi2_frame.tStartPos));
    qmemcpy(&igi2_frame.tEndPos, ptEnd, sizeof(igi2_frame.tEndPos));
    igi2_frame.vStartDist = TransContext_tActiveTransContext.tMatrix.tZ.vZ
               * (igi2_frame.tStartPos.vZ - TransContext_tActiveTransContext.tPos.vZ)
               + TransContext_tActiveTransContext.tMatrix.tZ.vY
               * (igi2_frame.tStartPos.vY - TransContext_tActiveTransContext.tPos.vY)
               + TransContext_tActiveTransContext.tMatrix.tZ.vX
               * (igi2_frame.tStartPos.vX - TransContext_tActiveTransContext.tPos.vX);
    igi2_frame.vStopDist = TransContext_tActiveTransContext.tMatrix.tZ.vZ * (igi2_frame.tEndPos.vZ - TransContext_tActiveTransContext.tPos.vZ)
              + TransContext_tActiveTransContext.tMatrix.tZ.vY * (igi2_frame.tEndPos.vY - TransContext_tActiveTransContext.tPos.vY)
              + TransContext_tActiveTransContext.tMatrix.tZ.vX * (igi2_frame.tEndPos.vX - TransContext_tActiveTransContext.tPos.vX);
    v7 = igi2_frame.vStartDist < 409.6000061035156;
    v8 = 0;
    v9 = igi2_frame.vStartDist == 409.6000061035156;
    v6 = (char)(v7 | (v8 << 2) | (v9 << 6));
    v10 = v6;
    v11 = igi2_frame.vStopDist < 409.6000061035156;
    v12 = igi2_frame.vStopDist == 409.6000061035156;
    v6 = (char)(v11 | (0 << 2) | (v12 << 6));
    if ( __SETP__(v10 & 0x41, 0) )
    {
      if ( v11 || v12 )
      {
        v14 = (409.6000061035156 - igi2_frame.vStopDist) / (igi2_frame.vStartDist - igi2_frame.vStopDist);
        igi2_frame.tEndPos.vX = (igi2_frame.tStartPos.vX - igi2_frame.tEndPos.vX) * v14 + igi2_frame.tEndPos.vX;
        igi2_frame.tEndPos.vY = (igi2_frame.tStartPos.vY - igi2_frame.tEndPos.vY) * v14 + igi2_frame.tEndPos.vY;
        igi2_frame.tEndPos.vZ = v14 * (igi2_frame.tStartPos.vZ - igi2_frame.tEndPos.vZ) + igi2_frame.tEndPos.vZ;
      }
    }
    else
    {
      if ( v11 || v12 )
        return;
      v13 = (409.6000061035156 - igi2_frame.vStartDist) / (igi2_frame.vStopDist - igi2_frame.vStartDist);
      igi2_frame.tStartPos.vX = (igi2_frame.tEndPos.vX - igi2_frame.tStartPos.vX) * v13 + igi2_frame.tStartPos.vX;
      igi2_frame.tStartPos.vY = (igi2_frame.tEndPos.vY - igi2_frame.tStartPos.vY) * v13 + igi2_frame.tStartPos.vY;
      igi2_frame.tStartPos.vZ = v13 * (igi2_frame.tEndPos.vZ - igi2_frame.tStartPos.vZ) + igi2_frame.tStartPos.vZ;
    }
    TransContext_ProjectWorldPos2(&TransContext_tActiveTransContext, &igi2_frame.tStartScreenPos, &igi2_frame.vStartDist, &igi2_frame.tStartPos);
    TransContext_ProjectWorldPos2(&TransContext_tActiveTransContext, &igi2_frame.tEndScreenPos, &igi2_frame.vStopDist, &igi2_frame.tEndPos);
    vX = ptStartColor->vX;
    vZ = ptStartColor->vZ;
    igi2_frame.atQVertex[0].vG = ptStartColor->vY;
    igi2_frame.atQVertex[0].vZ = igi2_frame.vStartDist;
    v17 = ptEndColor->vX;
    igi2_frame.atQVertex[0].vR = vX;
    igi2_frame.atQVertex[1].vR = v17;
    igi2_frame.atQVertex[0].vB = vZ;
    igi2_frame.atQVertex[0].vA = vStartAlpha;
    igi2_frame.atQVertex[1].vA = vEndAlpha;
    igi2_frame.atQVertex[0].vX = igi2_frame.tStartScreenPos.vX;
    vY = ptEndColor->vY;
    igi2_frame.atQVertex[0].vY = igi2_frame.tStartScreenPos.vY;
    v19 = ptEndColor->vZ;
    igi2_frame.atQVertex[1].vY = igi2_frame.tEndScreenPos.vY;
    igi2_frame.atQVertex[1].vG = vY;
    igi2_frame.atQVertex[1].vB = v19;
    igi2_frame.atQVertex[0].vU = 0.0;
    igi2_frame.atQVertex[0].vV = 0.0;
    igi2_frame.atQVertex[1].vU = 0.0;
    igi2_frame.atQVertex[1].vV = 0.0;
    igi2_frame.atQVertex[1].vZ = igi2_frame.vStopDist;
    igi2_frame.atQVertex[1].vX = igi2_frame.tEndScreenPos.vX;
    if ( vStartAlpha != 1.0 || (HIDWORD(igi2_frame.tStartPos.vX) = 1074135040, vEndAlpha != 1.0) )
      HIDWORD(igi2_frame.tStartPos.vX) = 786432;
    QVertex_ptActiveTexture = nullptr;
    QVertex_ptActivePalette = nullptr;
    LODWORD(igi2_frame.tStartPos.vX) = 1;
    *(_QWORD *)&igi2_frame.tStartPos.vY = 0x2FFFFFFFFLL;
    LODWORD(igi2_frame.tStartPos.vZ) = igi2_frame.atQVertex;
    RenderMode_tActiveRenderMode.apfRenderModeMethod[QVertex_eRegisterQVertexStripMethod](&igi2_frame.tStartPos);
  }
}

// source: e/3/line.c:301  [anchor-callee]
struct real32x3_t *__cdecl Line_RegisterLine2D(
        struct real32x3_t *ptStart,
        struct real32x3_t *ptEnd,
        struct real32x3_t *ptColor,
        float vAlpha)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QVertexStripContext_s tContext; };
    struct { char igi2_o1[20]; struct QVertex_s atQVertex[2]; };
    char igi2_extent[92];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  float vX; // esi
  float vY; // edx
  float v6; // eax
  float v7; // edx

  *(struct real32x3_t *)&igi2_frame.atQVertex[0].vR = *ptColor;
  igi2_frame.atQVertex[0].vA = vAlpha;
  igi2_frame.atQVertex[0].vZ = ptStart->vZ;
  vX = ptStart->vX;
  igi2_frame.atQVertex[0].vY = ptStart->vY;
  igi2_frame.atQVertex[1].vR = ptColor->vX;
  vY = ptColor->vY;
  igi2_frame.atQVertex[1].vB = ptColor->vZ;
  igi2_frame.atQVertex[1].vZ = ptEnd->vZ;
  v6 = ptEnd->vY;
  igi2_frame.atQVertex[1].vG = vY;
  igi2_frame.atQVertex[1].vY = v6;
  igi2_frame.atQVertex[1].vA = vAlpha;
  v7 = ptEnd->vX;
  igi2_frame.atQVertex[0].vX = vX;
  igi2_frame.atQVertex[0].vU = 0.0;
  igi2_frame.atQVertex[0].vV = 0.0;
  igi2_frame.atQVertex[1].vU = 0.0;
  igi2_frame.atQVertex[1].vV = 0.0;
  igi2_frame.atQVertex[1].vX = v7;
  igi2_frame.tContext.bFlags = 1074135040;
  if ( vAlpha != 1.0 )
    igi2_frame.tContext.bFlags = 786432;
  igi2_frame.tContext.nDepth = 0;
  QVertex_ptActiveTexture = nullptr;
  QVertex_ptActivePalette = nullptr;
  igi2_frame.tContext.isLine = 1;
  igi2_frame.tContext.nStripLength = 2;
  igi2_frame.tContext.atQVertex = igi2_frame.atQVertex;
  return ((struct real32x3_t *(__cdecl *)(struct QVertexStripContext_s *))RenderMode_tActiveRenderMode.apfRenderModeMethod[QVertex_eRegisterQVertexStripMethod])(&igi2_frame.tContext);
}

// source: e/3/line.c:366  [anchor-mhash]
struct real32x3_t *__cdecl Line_DrawLine2D(
        struct real32x3_t *ptStart,
        struct real32x3_t *ptEnd,
        struct real32x3_t *ptColor,
        float vAlpha)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QVertexStripContext_s tContext; };
    struct { char igi2_o1[20]; struct QVertex_s atQVertex[2]; };
    char igi2_extent[92];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  float vX; // esi
  float vY; // edx
  float v6; // eax
  float v7; // edx

  *(struct real32x3_t *)&igi2_frame.atQVertex[0].vR = *ptColor;
  igi2_frame.atQVertex[0].vA = vAlpha;
  igi2_frame.atQVertex[0].vZ = ptStart->vZ;
  vX = ptStart->vX;
  igi2_frame.atQVertex[0].vY = ptStart->vY;
  igi2_frame.atQVertex[1].vR = ptColor->vX;
  vY = ptColor->vY;
  igi2_frame.atQVertex[1].vB = ptColor->vZ;
  igi2_frame.atQVertex[1].vZ = ptEnd->vZ;
  v6 = ptEnd->vY;
  igi2_frame.atQVertex[1].vG = vY;
  igi2_frame.atQVertex[1].vY = v6;
  igi2_frame.atQVertex[1].vA = vAlpha;
  v7 = ptEnd->vX;
  igi2_frame.atQVertex[0].vX = vX;
  igi2_frame.atQVertex[0].vU = 0.0;
  igi2_frame.atQVertex[0].vV = 0.0;
  igi2_frame.atQVertex[1].vU = 0.0;
  igi2_frame.atQVertex[1].vV = 0.0;
  igi2_frame.atQVertex[1].vX = v7;
  igi2_frame.tContext.bFlags = 1074135040;
  if ( vAlpha != 1.0 )
    igi2_frame.tContext.bFlags = 786432;
  QVertex_ptActiveTexture = nullptr;
  QVertex_ptActivePalette = nullptr;
  igi2_frame.tContext.isLine = 1;
  igi2_frame.tContext.nDepth = -1;
  igi2_frame.tContext.nStripLength = 2;
  igi2_frame.tContext.atQVertex = igi2_frame.atQVertex;
  return ((struct real32x3_t *(__cdecl *)(struct QVertexStripContext_s *))RenderMode_tActiveRenderMode.apfRenderModeMethod[QVertex_eRegisterQVertexStripMethod])(&igi2_frame.tContext);
}
