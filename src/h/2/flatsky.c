/* h/2/flatsky.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/flatsky.c:122  [anchor-mhash]
void __cdecl FlatSky_EnterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vDist; };
    struct { float vDista; };
    struct { float vDistb; };
    struct { float vDistc; };
    struct { float vDistd; };
    struct { char igi2_o5[4]; float vBoxHeight; };
    struct { char igi2_o6[4]; float vBoxHeighta; };
    struct { char igi2_o7[4]; float vBoxHeightb; };
    struct { char igi2_o8[4]; float vBoxHeightc; };
    struct { char igi2_o9[8]; float vBoxLeft; };
    struct { char igi2_o10[8]; float vBoxLefta; };
    struct { char igi2_o11[8]; float vBoxLeftb; };
    struct { char igi2_o12[8]; float vBoxLeftc; };
    struct { char igi2_o13[12]; float vDistance; };
    struct { char igi2_o14[16]; float tRightScreen; };
    struct { char igi2_o15[16]; float tRightScreena; };
    struct { char igi2_o16[16]; long double tRightScreenb; };
    struct { char igi2_o17[16]; double tRightScreenc; };
    struct { char igi2_o18[16]; float tRightScreend; };
    struct { char igi2_o19[20]; float tRightScreen_4; };
    struct { char igi2_o20[20]; float tRightScreen_4a; };
    struct { char igi2_o21[20]; float tRightScreen_4b; };
    struct { char igi2_o22[24]; float v76; };
    struct { char igi2_o23[24]; float v77; };
    struct { char igi2_o24[32]; float tDirection2; };
    struct { char igi2_o25[32]; double tDirection2a; };
    struct { char igi2_o26[36]; float tDirection2_4; };
    struct { char igi2_o27[36]; float tDirection2_4a; };
    struct { char igi2_o28[40]; float v82; };
    struct { char igi2_o29[48]; float tTemp; };
    struct { char igi2_o30[52]; float tTemp_4; };
    struct { char igi2_o31[60]; struct real32x2_t tDirection; };
    struct { char igi2_o32[68]; float v86; };
    struct { char igi2_o33[72]; int v87; };
    struct { char igi2_o34[76]; struct QVertex_s *v88; };
    struct { char igi2_o35[80]; struct real32x2_t tLeftScreen; };
    struct { char igi2_o36[88]; float v90; };
    struct { char igi2_o37[92]; float vNearDistance; };
    struct { char igi2_o38[96]; float vPosZ; };
    struct { char igi2_o39[100]; struct real32x2_t atScreenCorners[5]; };
    struct { char igi2_o40[140]; float vDelta; };
    struct { char igi2_o41[144]; struct QVertex_s atQVertex[26]; };
    char igi2_extent[1080];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QReference_s *ptHead; // esi
  double v3; // st7
  long double v4; // st7
  long double v5; // st6
  long double v6; // st5
  long double v7; // st4
  long double v8; // st7
  double v9; // st6
  double v10; // st5
  double v11; // st4
  double v12; // st7
  double v13; // st7
  double v14; // st7
  double v15; // st5
  double v16; // st7
  double v17; // st7
  double v18; // st6
  double v19; // st5
  double v20; // st4
  double v21; // st6
  double v22; // st5
  double v23; // st4
  double v24; // st6
  double v25; // st5
  double v26; // st4
  double v27; // st6
  double v28; // st5
  double v29; // st4
  float *p_vY; // eax
  int v31; // ecx
  double v32; // st7
  double v33; // st6
  double v34; // st5
  double v35; // st4
  struct QTask_s *i; // esi
  double v37; // st7
  float *v38; // ecx
  int v39; // edx
  double v40; // st6
  double v41; // st5
  double v42; // st4
  double v43; // st5
  double v44; // st4
  double v45; // st3
  double v46; // st5
  double v47; // st5
  unsigned __int8 v49; // c0
  unsigned __int8 v50; // c2
  double v51; // st4
  double v52; // st4
  struct QTask_s *ptPrev; // eax
  struct real32x2_t struct_real32x2_t; // 0:^34.8

  ptHead = ptQTask[3].tQTaskRefList.ptHead;
  igi2_frame.vDistance = *(float *)&ptQTask[3].ptNext * 4096.0;
  igi2_frame.vPosZ = *(float *)&ptQTask[2].eQTaskType * 4096.0;
  v3 = igi2_frame.vDistance - (igi2_frame.vDistance - 409.6000061035156) * *(float *)&ptQTask[3].ptPrev;
  igi2_frame.vNearDistance = v3;
  igi2_frame.vDelta = 1.0 / (v3 - igi2_frame.vDistance);
  SkyDome_Draw((int)ptHead);
  qmemcpy(igi2_frame.atScreenCorners, &TransContext_tActiveTransContext, sizeof(igi2_frame.atScreenCorners));
  if ( igi2_frame.atScreenCorners[3].vX == 0.0 && igi2_frame.atScreenCorners[3].vY == 0.0 )
    igi2_frame.atScreenCorners[3].vX = 1.0;
  igi2_frame.tRightScreenb = 1.0
                / sqrt(igi2_frame.atScreenCorners[3].vX * igi2_frame.atScreenCorners[3].vX + igi2_frame.atScreenCorners[3].vY * igi2_frame.atScreenCorners[3].vY);
  v4 = igi2_frame.atScreenCorners[3].vX * igi2_frame.tRightScreenb;
  v5 = igi2_frame.atScreenCorners[3].vY * igi2_frame.tRightScreenb;
  v6 = igi2_frame.tRightScreenb * 0.0;
  v7 = 0.0 * (igi2_frame.tRightScreenb * 0.0) - v5;
  *((float *)&igi2_frame.tRightScreenb + 1) = -(0.0 * (igi2_frame.tRightScreenb * 0.0) - v4);
  igi2_frame.v76 = v5 * 0.0 - v4 * 0.0;
  igi2_frame.atScreenCorners[0].vX = TransContext_tActiveTransContext.tMatrix.tX.vZ * igi2_frame.v76
                        + TransContext_tActiveTransContext.tMatrix.tX.vY * *((float *)&igi2_frame.tRightScreenb + 1)
                        + TransContext_tActiveTransContext.tMatrix.tX.vX * v7;
  igi2_frame.atScreenCorners[0].vY = (TransContext_tActiveTransContext.tMatrix.tX.vY
                         + TransContext_tActiveTransContext.tMatrix.tX.vX)
                        * 0.0
                        + TransContext_tActiveTransContext.tMatrix.tX.vZ;
  igi2_frame.atScreenCorners[1].vX = TransContext_tActiveTransContext.tMatrix.tX.vY * v5
                        + TransContext_tActiveTransContext.tMatrix.tX.vX * v4
                        + TransContext_tActiveTransContext.tMatrix.tX.vZ * v6;
  igi2_frame.atScreenCorners[1].vY = TransContext_tActiveTransContext.tMatrix.tY.vZ * igi2_frame.v76
                        + TransContext_tActiveTransContext.tMatrix.tY.vY * *((float *)&igi2_frame.tRightScreenb + 1)
                        + TransContext_tActiveTransContext.tMatrix.tY.vX * v7;
  igi2_frame.atScreenCorners[2].vX = (TransContext_tActiveTransContext.tMatrix.tY.vY
                         + TransContext_tActiveTransContext.tMatrix.tY.vX)
                        * 0.0
                        + TransContext_tActiveTransContext.tMatrix.tY.vZ;
  igi2_frame.atScreenCorners[2].vY = TransContext_tActiveTransContext.tMatrix.tY.vY * v5
                        + TransContext_tActiveTransContext.tMatrix.tY.vX * v4
                        + TransContext_tActiveTransContext.tMatrix.tY.vZ * v6;
  igi2_frame.atScreenCorners[3].vX = TransContext_tActiveTransContext.tMatrix.tZ.vZ * igi2_frame.v76
                        + TransContext_tActiveTransContext.tMatrix.tZ.vY * *((float *)&igi2_frame.tRightScreenb + 1)
                        + TransContext_tActiveTransContext.tMatrix.tZ.vX * v7;
  igi2_frame.atScreenCorners[3].vY = (TransContext_tActiveTransContext.tMatrix.tZ.vY
                         + TransContext_tActiveTransContext.tMatrix.tZ.vX)
                        * 0.0
                        + TransContext_tActiveTransContext.tMatrix.tZ.vZ;
  v8 = TransContext_tActiveTransContext.tMatrix.tZ.vY * v5
     + TransContext_tActiveTransContext.tMatrix.tZ.vX * v4
     + TransContext_tActiveTransContext.tMatrix.tZ.vZ * v6;
  v9 = -igi2_frame.vDistance;
  v10 = igi2_frame.atScreenCorners[1].vX * igi2_frame.vDistance + igi2_frame.atScreenCorners[0].vY * igi2_frame.vPosZ;
  igi2_frame.tRightScreen = igi2_frame.atScreenCorners[0].vX * igi2_frame.vDistance + v10;
  v11 = igi2_frame.atScreenCorners[2].vY * igi2_frame.vDistance + igi2_frame.atScreenCorners[2].vX * igi2_frame.vPosZ;
  igi2_frame.tRightScreen_4 = igi2_frame.atScreenCorners[1].vY * igi2_frame.vDistance + v11;
  igi2_frame.vBoxHeightb = igi2_frame.atScreenCorners[3].vY * igi2_frame.vPosZ;
  igi2_frame.vBoxLeftb = v8 * igi2_frame.vDistance;
  igi2_frame.v77 = igi2_frame.atScreenCorners[3].vX * igi2_frame.vDistance + igi2_frame.vBoxLeftb + igi2_frame.vBoxHeightb;
  igi2_frame.tDirection.vX = v9 * igi2_frame.atScreenCorners[0].vX + v10;
  igi2_frame.tDirection.vY = v9 * igi2_frame.atScreenCorners[1].vY + v11;
  igi2_frame.v86 = v9 * igi2_frame.atScreenCorners[3].vX + igi2_frame.vBoxLeftb + igi2_frame.vBoxHeightb;
  if ( igi2_frame.v77 >= 409.6000061035156 && igi2_frame.v86 >= 409.6000061035156 )
  {
    v12 = 1.0 / igi2_frame.v77;
    igi2_frame.atScreenCorners[0] = *(struct real32x2_t *)&RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX;
    igi2_frame.atScreenCorners[1].vY = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vY;
    igi2_frame.atScreenCorners[2].vX = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX;
    igi2_frame.tLeftScreen.vX = igi2_frame.tRightScreen * v12 * TransContext_tActiveTransContext.vScreenFOVX
                   + TransContext_tActiveTransContext.vScreenOriginX;
    igi2_frame.tLeftScreen.vY = igi2_frame.tRightScreen_4 * v12 * TransContext_tActiveTransContext.vScreenFOVY
                   + TransContext_tActiveTransContext.vScreenOriginY;
    igi2_frame.tRightScreenc = 1.0 / igi2_frame.v86;
    v13 = igi2_frame.tDirection.vX * igi2_frame.tRightScreenc * TransContext_tActiveTransContext.vScreenFOVX
        + TransContext_tActiveTransContext.vScreenOriginX;
    *((float *)&igi2_frame.tRightScreenc + 1) = igi2_frame.tDirection.vY * igi2_frame.tRightScreenc * TransContext_tActiveTransContext.vScreenFOVY
                                   + TransContext_tActiveTransContext.vScreenOriginY;
    igi2_frame.atScreenCorners[1].vX = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vWidth
                          + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX;
    igi2_frame.atScreenCorners[2].vY = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHeight
                          + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vY;
    igi2_frame.atScreenCorners[3].vX = igi2_frame.atScreenCorners[1].vX;
    igi2_frame.atScreenCorners[3].vY = igi2_frame.atScreenCorners[2].vY;
    v14 = v13 - igi2_frame.tLeftScreen.vX;
    v15 = *((float *)&igi2_frame.tRightScreenc + 1) - igi2_frame.tLeftScreen.vY;
    igi2_frame.vBoxHeightc = v15;
    igi2_frame.vBoxLeftc = sqrt(v14 * v14 + v15 * v15);
    igi2_frame.tDirection2a = 1.0 / igi2_frame.vBoxLeftc;
    igi2_frame.tDirection.vX = v14 * igi2_frame.tDirection2a;
    igi2_frame.tDirection.vY = v15 * igi2_frame.tDirection2a;
    igi2_frame.vBoxLeft = 100000.0;
    igi2_frame.tDirection2_4 = -igi2_frame.tDirection.vX;
    igi2_frame.tTemp = v14 * 0.5 + igi2_frame.tLeftScreen.vX;
    v16 = igi2_frame.vBoxHeightc;
    igi2_frame.vBoxHeight = -1.0;
    igi2_frame.tTemp_4 = v16 * 0.5 + igi2_frame.tLeftScreen.vY;
    v17 = -100000.0;
    v18 = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX - igi2_frame.tTemp;
    v19 = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vY - igi2_frame.tTemp_4;
    v20 = igi2_frame.tDirection2_4 * v19 + v18 * igi2_frame.tDirection.vY;
    if ( v20 >= -1.0 )
      igi2_frame.vBoxHeight = v20;
    igi2_frame.vDist = v19 * igi2_frame.tDirection.vY + v18 * igi2_frame.tDirection.vX;
    if ( igi2_frame.vDist <= 100000.0 )
      igi2_frame.vBoxLeft = v19 * igi2_frame.tDirection.vY + v18 * igi2_frame.tDirection.vX;
    if ( igi2_frame.vDist >= -100000.0 )
      v17 = igi2_frame.vDist;
    v21 = igi2_frame.atScreenCorners[1].vX - igi2_frame.tTemp;
    v22 = igi2_frame.atScreenCorners[1].vY - igi2_frame.tTemp_4;
    v23 = igi2_frame.tDirection2_4 * v22 + v21 * igi2_frame.tDirection.vY;
    if ( igi2_frame.vBoxHeight <= v23 )
      igi2_frame.vBoxHeight = v23;
    igi2_frame.vDista = v22 * igi2_frame.tDirection.vY + v21 * igi2_frame.tDirection.vX;
    if ( igi2_frame.vBoxLeft >= (double)igi2_frame.vDista )
      igi2_frame.vBoxLeft = v22 * igi2_frame.tDirection.vY + v21 * igi2_frame.tDirection.vX;
    if ( v17 <= igi2_frame.vDista )
      v17 = igi2_frame.vDista;
    v24 = igi2_frame.atScreenCorners[2].vX - igi2_frame.tTemp;
    v25 = igi2_frame.atScreenCorners[2].vY - igi2_frame.tTemp_4;
    v26 = igi2_frame.tDirection2_4 * v25 + v24 * igi2_frame.tDirection.vY;
    if ( igi2_frame.vBoxHeight <= v26 )
      igi2_frame.vBoxHeight = v26;
    igi2_frame.vDistb = v25 * igi2_frame.tDirection.vY + v24 * igi2_frame.tDirection.vX;
    if ( igi2_frame.vBoxLeft >= (double)igi2_frame.vDistb )
      igi2_frame.vBoxLeft = v25 * igi2_frame.tDirection.vY + v24 * igi2_frame.tDirection.vX;
    if ( v17 <= igi2_frame.vDistb )
      v17 = igi2_frame.vDistb;
    v27 = igi2_frame.atScreenCorners[3].vX - igi2_frame.tTemp;
    v28 = igi2_frame.atScreenCorners[3].vY - igi2_frame.tTemp_4;
    v29 = igi2_frame.tDirection2_4 * v28 + v27 * igi2_frame.tDirection.vY;
    if ( igi2_frame.vBoxHeight <= v29 )
      igi2_frame.vBoxHeight = v29;
    igi2_frame.vDistc = v28 * igi2_frame.tDirection.vY + v27 * igi2_frame.tDirection.vX;
    if ( igi2_frame.vBoxLeft >= (double)igi2_frame.vDistc )
      igi2_frame.vBoxLeft = v28 * igi2_frame.tDirection.vY + v27 * igi2_frame.tDirection.vX;
    if ( v17 <= igi2_frame.vDistc )
      v17 = igi2_frame.vDistc;
    if ( igi2_frame.vBoxHeight >= 0.0 )
    {
      p_vY = &igi2_frame.atQVertex[0].vY;
      igi2_frame.tDirection2 = igi2_frame.vBoxHeight * igi2_frame.tDirection.vY * 0.08341667056083679;
      v31 = 13;
      igi2_frame.tDirection2_4a = igi2_frame.vBoxHeight * igi2_frame.tDirection2_4 * 0.08341667056083679;
      igi2_frame.tRightScreend = igi2_frame.tDirection.vX * v17 * 1.0010000467300415;
      igi2_frame.tRightScreen_4b = v17 * igi2_frame.tDirection.vY * 1.0010000467300415;
      igi2_frame.tLeftScreen.vX = igi2_frame.vBoxLeft * igi2_frame.tDirection.vX * 1.0010000467300415;
      igi2_frame.tLeftScreen.vY = igi2_frame.vBoxLeft * igi2_frame.tDirection.vY * 1.0010000467300415;
      v32 = igi2_frame.tTemp + igi2_frame.tRightScreend;
      v33 = igi2_frame.tTemp_4 + igi2_frame.tRightScreen_4b;
      v34 = igi2_frame.tTemp + igi2_frame.tLeftScreen.vX;
      v35 = igi2_frame.tTemp_4 + igi2_frame.tLeftScreen.vY;
      do
      {
        p_vY += 18;
        --v31;
        *(p_vY - 19) = v34;
        *(p_vY - 18) = v35;
        *(p_vY - 10) = v32;
        *(p_vY - 9) = v33;
        v34 = v34 + igi2_frame.tDirection2;
        v35 = v35 + igi2_frame.tDirection2_4a;
        v32 = v32 + igi2_frame.tDirection2;
        v33 = v33 + igi2_frame.tDirection2_4a;
      }
      while ( v31 );
      igi2_frame.tRightScreena = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHalfWidth
                    + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX;
      igi2_frame.tRightScreen_4a = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHalfHeight
                      + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vY;
      for ( i = QTask_GetFirstChildOfType(ptQTask, FlatSkyLayer_eQTaskType);
            i;
            i = QTask_GetNextSiblingOfType(i, FlatSkyLayer_eQTaskType) )
      {
        v37 = 1.0 / TransContext_tActiveTransContext.vScreenFOVX;
        igi2_frame.vBoxLefta = TransContext_tActiveTransContext.tMatrix.tZ.vX;
        igi2_frame.vDistd = TransContext_tActiveTransContext.tMatrix.tZ.vZ;
        igi2_frame.vBoxHeighta = TransContext_tActiveTransContext.tMatrix.tZ.vY;
        v38 = &igi2_frame.atQVertex[0].vY;
        v39 = 26;
        v40 = 1.0 / TransContext_tActiveTransContext.vScreenFOVY;
        do
        {
          v41 = (*(v38 - 1) - igi2_frame.tRightScreena) * v37;
          v42 = (*v38 - igi2_frame.tRightScreen_4a) * v40;
          struct_real32x2_t.vX = TransContext_tActiveTransContext.tMatrix.tY.vX * v42
                               + v41 * TransContext_tActiveTransContext.tMatrix.tX.vX
                               + igi2_frame.vBoxLefta;
          struct_real32x2_t.vY = TransContext_tActiveTransContext.tMatrix.tY.vY * v42
                               + v41 * TransContext_tActiveTransContext.tMatrix.tX.vY
                               + igi2_frame.vBoxHeighta;
          igi2_frame.tLeftScreen = struct_real32x2_t;
          igi2_frame.v82 = v42 * TransContext_tActiveTransContext.tMatrix.tY.vZ
              + v41 * TransContext_tActiveTransContext.tMatrix.tX.vZ
              + igi2_frame.vDistd;
          igi2_frame.v90 = igi2_frame.v82;
          v43 = igi2_frame.vPosZ / igi2_frame.v82;
          v44 = struct_real32x2_t.vX * v43;
          v45 = v43;
          v46 = v43 * struct_real32x2_t.vY;
          v38[2] = v44 * *(float *)&i[15].ptNext + *(float *)&i[15].tQTaskChildren.ptMiddle;
          v38[3] = v46 * *(float *)&i[15].ptNext + *(float *)&i[15].tQTaskChildren.ptTail;
          v47 = v45 * igi2_frame.v82 * TransContext_tActiveTransContext.tMatrix.tZ.vZ
              + v46 * TransContext_tActiveTransContext.tMatrix.tZ.vY
              + v44 * TransContext_tActiveTransContext.tMatrix.tZ.vX;
          v38[1] = v47;
          v38[5] = *(float *)&i[15].tQTaskRefList.ptMiddle;
          v38[6] = *(float *)&i[15].tQTaskRefList.ptTail;
          v38[7] = *(float *)&i[15].ptParent;
          if ( v49 | v50 || *(float *)&ptQTask[3].ptPrev < 0.01 )
          {
            v38[4] = 1.0;
          }
          else
          {
            v51 = (igi2_frame.vNearDistance - 1.0 / v47 * igi2_frame.vNearDistance * igi2_frame.vDistance) * igi2_frame.vDelta;
            v38[4] = v51;
            if ( v51 >= 0.0 )
            {
              if ( v51 > 0.9990000128746033 )
                v38[4] = 0.9990000128746033;
            }
            else
            {
              v38[4] = 0.0;
            }
          }
          v52 = v38[4];
          v38 += 9;
          --v39;
          *(v38 - 5) = v52 * *(float *)&i[15].tQTaskRefList.ptHead;
          *(v38 - 8) = v47 * 16.0;
        }
        while ( v39 );
        ptPrev = i[2].ptPrev;
        igi2_frame.v88 = igi2_frame.atQVertex;
        igi2_frame.tDirection.vY = 12.500007629394531;
        igi2_frame.tDirection.vX = 0.0;
        igi2_frame.v86 = IGI2_FLOAT_BITS(0xffffffffu);
        igi2_frame.v87 = 26;
        if ( ptPrev )
          QVertex_ptActiveTexture = (struct TexInfo_s *)&i[1];
        else
          QVertex_ptActiveTexture = nullptr;
        RenderMode_tActiveRenderMode.apfRenderModeMethod[QVertex_eRegisterQVertexStripMethod](&igi2_frame.tDirection);
      }
    }
  }
}

// source: h/2/flatsky.c:349  [anchor-caller]
void __cdecl FlatSky_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptParent; // eax
  struct QTask_s *ptPrev; // ecx
  struct QTask_s *ptMiddle; // ecx
  struct QVector_s *v5; // eax

  ptQTask[2].ptParent = (struct QTask_s *)World_ptActiveWorld;
  ptQTask[3].ptPrev = (struct QTask_s *)1056964608;
  ptQTask[3].ptNext = (struct QTask_s *)1120403456;
  *(_DWORD *)&ptQTask[2].eQTaskType = 1084227584;
  ptQTask[3].tQTaskChildren.ptHead = nullptr;
  ptQTask[3].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[3].tQTaskChildren.ptTail = nullptr;
  memset(&ptQTask[1], 0, 0x48u);
  ptParent = ptQTask[2].ptParent;
  ptQTask[2].tQTaskRefList.ptTail = nullptr;
  ptPrev = ptParent[2].ptPrev;
  if ( ptPrev )
  {
    ptPrev[2].tQTaskChildren.ptMiddle = ptQTask;
    ptParent[2].ptPrev[2].tQTaskChildren.ptMiddle[2].tQTaskChildren.ptTail = ptParent[2].ptPrev;
    ptMiddle = ptParent[2].ptPrev[2].tQTaskChildren.ptMiddle;
    ptParent[2].ptPrev = ptMiddle;
    ptMiddle[2].tQTaskChildren.ptMiddle = nullptr;
  }
  else
  {
    ptParent[2].ptPrev = ptQTask;
    ptQTask[2].tQTaskChildren.ptTail = nullptr;
    ptParent[2].ptPrev[2].tQTaskChildren.ptMiddle = nullptr;
  }
  ptQTask[3].tQTaskRefList.ptHead = (struct QReference_s *)SkyDome_New();
  ptQTask[3].tQTaskRefList.ptTail = (struct QReference_s *)1044549468;
  ptQTask[3].ptParent = (struct QTask_s *)1050253722;
  *(_DWORD *)&ptQTask[3].eQTaskType = 1054615798;
  ptQTask[4].tQTaskChildren.ptMiddle = (struct QTask_s *)1044549468;
  ptQTask[4].tQTaskChildren.ptTail = (struct QTask_s *)1050253722;
  ptQTask[4].tQTaskRefList.ptHead = (struct QReference_s *)1054615798;
  *(_DWORD *)&ptQTask[4].eQTaskType = 1044549468;
  ptQTask[5].ptNext = (struct QTask_s *)1050253722;
  ptQTask[5].ptPrev = (struct QTask_s *)1054615798;
  ptQTask[4].ptNext = (struct QTask_s *)1044549468;
  ptQTask[4].ptPrev = (struct QTask_s *)1050253722;
  ptQTask[4].tQTaskChildren.ptHead = (struct QTask_s *)1054615798;
  ptQTask[4].tQTaskRefList.ptMiddle = (struct QReference_s *)1044549468;
  v5 = FlatSky_ptQVector;
  ptQTask[4].tQTaskRefList.ptTail = (struct QReference_s *)1050253722;
  ptQTask[3].tQTaskRefList.ptMiddle = (struct QReference_s *)1097859072;
  ptQTask[4].ptParent = (struct QTask_s *)1054615798;
  LOBYTE(ptQTask[5].tQTaskChildren.ptHead) = 0;
  ptQTask[5].tQTaskChildren.ptMiddle = nullptr;
  QVector_AddElement(v5, ptQTask);
}

// source: h/2/flatsky.c:392  [anchor-caller]
void __cdecl FlatSky_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptMiddle; // eax
  struct QTask_s *ptTail; // eax

  QVector_RemoveElementByPointer(FlatSky_ptQVector, ptQTask);
  SkyDome_Delete(ptQTask[3].tQTaskRefList.ptHead);
  ptMiddle = ptQTask[2].tQTaskChildren.ptMiddle;
  if ( ptMiddle )
    ptMiddle[2].tQTaskChildren.ptTail = ptQTask[2].tQTaskChildren.ptTail;
  else
    ptQTask[2].ptParent[2].ptPrev = ptQTask[2].tQTaskChildren.ptTail;
  ptTail = ptQTask[2].tQTaskChildren.ptTail;
  if ( ptTail )
    ptTail[2].tQTaskChildren.ptMiddle = ptQTask[2].tQTaskChildren.ptMiddle;
}

// source: h/2/flatsky.c:413  [size]
void __cdecl FlatSky_RunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // ecx
  int v2; // edx
  struct QTask_s *v3; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v5; // edx

  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v2 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v3 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v3 = nullptr;
      QTask_atProtectedQTaskStack[v2].ptQTask = v3;
      pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][ptHead->eQTaskType].pfHandler;
      v5 = v2 + 1;
      QTask_nProtectedQTaskStackOffset = v5;
      if ( pfHandler )
      {
        pfHandler(ptHead);
        v5 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v5];
      v2 = v5 - 1;
      QTask_nProtectedQTaskStackOffset = v2;
    }
    while ( ptHead );
  }
}

// source: h/2/flatsky.c:428  [size]
void __cdecl FlatSky_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = FlatSky_ptParameterList;
}

// source: h/2/flatsky.c:444  [anchor-caller]
void __cdecl FlatSky_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // ecx
  double v3; // st7
  struct QTask_s *ptPrev; // edx
  struct QTask_s *ptHead; // ecx

  v2 = (unsigned __int8)(__int64)(*(float *)&ptQTask[3].tQTaskChildren.ptTail * 255.0);
  v3 = *(float *)&ptQTask[3].tQTaskChildren.ptHead * 255.0;
  Display_tBackgroundColor.nY = (unsigned __int8)(__int64)(*(float *)&ptQTask[3].tQTaskChildren.ptMiddle * 255.0);
  Display_tBackgroundColor.nZ = v2;
  Display_tBackgroundColor.nX = (unsigned __int8)(__int64)v3;
  if ( LOBYTE(ptQTask[5].tQTaskChildren.ptHead) )
  {
    ptQTask[4].tQTaskRefList.ptMiddle = *(struct QReference_s **)&ptQTask[4].eQTaskType;
    ptPrev = ptQTask[5].ptPrev;
    ptQTask[4].tQTaskRefList.ptTail = (struct QReference_s *)ptQTask[5].ptNext;
    ptQTask[4].ptParent = ptPrev;
    ptQTask[4].ptNext = ptQTask[4].tQTaskChildren.ptMiddle;
    ptHead = (struct QTask_s *)ptQTask[4].tQTaskRefList.ptHead;
    ptQTask[4].ptPrev = ptQTask[4].tQTaskChildren.ptTail;
    ptQTask[4].tQTaskChildren.ptHead = ptHead;
  }
  *(float *)&ptQTask[3].tQTaskRefList.ptHead[6].ptNext = *(float *)&ptQTask[3].tQTaskRefList.ptMiddle
                                                       * 3.1415927410125732
                                                       * 0.0055555556900799274;
  SkyDome_SetColour(
    ptQTask[3].tQTaskRefList.ptHead,
    (struct real32x3_t *)&ptQTask[3].tQTaskRefList.ptTail,
    (struct real32x3_t *)&ptQTask[4].tQTaskChildren.ptMiddle,
    (struct real32x3_t *)&ptQTask[4],
    (struct real32x3_t *)&ptQTask[4].eQTaskType,
    (struct real32x3_t *)&ptQTask[4].tQTaskRefList.ptMiddle);
}

// source: h/2/flatsky.c:480  [size]
void __cdecl FlatSkyLayer_RunHandler(struct QTask_s *ptQTask)
{
  double v2; // st7
  double v3; // st6
  double v4; // st7
  double v5; // st7
  double v6; // st7
  struct QTask_s *ptQTaska = *(struct QTask_s * *)&ptQTask; // [esp+4h] [ebp+4h] ARGSLOT

  *(float *)&ptQTaska = *(float *)&ptQTask[15].ptPrev + *(float *)&ptQTask[15].tQTaskChildren.ptMiddle;
  ptQTask[15].tQTaskChildren.ptMiddle = ptQTaska;
  v2 = *(float *)&ptQTask[15].tQTaskChildren.ptHead + *(float *)&ptQTask[15].tQTaskChildren.ptTail;
  *(float *)&ptQTask[15].tQTaskChildren.ptTail = v2;
  if ( *(float *)&ptQTaska > 1.0 )
  {
    v3 = *(float *)&ptQTask[15].tQTaskChildren.ptMiddle;
    do
      v3 = v3 - 1.0;
    while ( v3 > 1.0 );
    *(float *)&ptQTask[15].tQTaskChildren.ptMiddle = v3;
  }
  if ( v2 > 1.0 )
  {
    v4 = *(float *)&ptQTask[15].tQTaskChildren.ptTail;
    do
      v4 = v4 - 1.0;
    while ( v4 > 1.0 );
    *(float *)&ptQTask[15].tQTaskChildren.ptTail = v4;
  }
  if ( *(float *)&ptQTask[15].tQTaskChildren.ptMiddle < 0.0 )
  {
    v5 = *(float *)&ptQTask[15].tQTaskChildren.ptMiddle;
    do
      v5 = v5 + 1.0;
    while ( v5 < 0.0 );
    *(float *)&ptQTask[15].tQTaskChildren.ptMiddle = v5;
  }
  if ( *(float *)&ptQTask[15].tQTaskChildren.ptTail < 0.0 )
  {
    v6 = *(float *)&ptQTask[15].tQTaskChildren.ptTail;
    do
      v6 = v6 + 1.0;
    while ( v6 < 0.0 );
    *(float *)&ptQTask[15].tQTaskChildren.ptTail = v6;
  }
}

// source: h/2/flatsky.c:517  [size]
void __cdecl FlatSkyLayer_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[2].ptPrev = nullptr;
  ptQTask[15].ptPrev = nullptr;
  ptQTask[15].tQTaskChildren.ptHead = nullptr;
  ptQTask[15].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[15].tQTaskChildren.ptTail = nullptr;
  ptQTask[15].ptNext = (struct QTask_s *)953267991;
  ptQTask[15].tQTaskRefList.ptHead = (struct QReference_s *)1065353216;
  ptQTask[15].tQTaskRefList.ptMiddle = (struct QReference_s *)1065353216;
  ptQTask[15].tQTaskRefList.ptTail = (struct QReference_s *)1065353216;
  ptQTask[15].ptParent = (struct QTask_s *)1065353216;
  sprintf((char *const)&ptQTask[2].tQTaskChildren, (char *const)&g_zInitialValue);
  sprintf((char *const)&ptQTask[8].tQTaskRefList.ptMiddle, (char *const)&g_zInitialValue);
}

// source: h/2/flatsky.c:543  [size]
void __cdecl FlatSkyLayer_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *v1; // edi

  if ( ptQTask[2].ptPrev )
  {
    v1 = ptQTask + 1;
    if ( AppContext_tAppContext.isMainMenu == false )
      RenderMode_atRenderMode[(int)v1->ptNext].apfRenderModeMethod[Texture_eDeAllocTextureMethod](&ptQTask[1]);
    memset(v1, 0, 0x2Cu);
    ptQTask[2].ptPrev = nullptr;
  }
}

// source: h/2/flatsky.c:567  [anchor-callee]
void __cdecl FlatSkyLayer_FixFilename(char *zFilename)
{
  unsigned int v1; // ecx
  unsigned int v2; // edx
  char v4; // al
  signed int v5; // edx
  signed int i; // eax
  char zTemp[256]; // [esp+0h] [ebp-100h] BYREF

  if ( strlen(zFilename) >= 0xFF )
    v1 = 255;
  else
    v1 = strlen(zFilename);
  v2 = v1;
  do
  {
    if ( !v1-- )
      break;
    v4 = zFilename[v1 - 1];
    if ( v4 == 47 )
      break;
  }
  while ( v4 != 92 );
  v5 = v2 - v1;
  for ( i = 0; i < v5; ++i )
    zTemp[i] = zFilename[v1 + i];
  zTemp[i] = 0;
  sprintf(zFilename, (char *const)&g_zFileName.aptSelectableItems[28], "MISSION:textures/", zTemp);
}

// source: h/2/flatsky.c:596  [anchor-strings]
void __cdecl FlatSkyLayer_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  double v2; // st7
  double v3; // st7
  double v4; // st7
  char zTemp[512]; // [esp+Ch] [ebp-200h] BYREF

  if ( *(float *)&ptQTask[15].tQTaskRefList.ptMiddle >= 0.0 )
  {
    if ( *(float *)&ptQTask[15].tQTaskRefList.ptMiddle <= 1.0 )
      v2 = *(float *)&ptQTask[15].tQTaskRefList.ptMiddle;
    else
      v2 = 1.0;
  }
  else
  {
    v2 = 0.0;
  }
  *(float *)&ptQTask[15].tQTaskRefList.ptMiddle = v2;
  if ( *(float *)&ptQTask[15].tQTaskRefList.ptTail >= 0.0 )
  {
    if ( *(float *)&ptQTask[15].tQTaskRefList.ptTail <= 1.0 )
      v3 = *(float *)&ptQTask[15].tQTaskRefList.ptTail;
    else
      v3 = 1.0;
  }
  else
  {
    v3 = 0.0;
  }
  *(float *)&ptQTask[15].tQTaskRefList.ptTail = v3;
  if ( *(float *)&ptQTask[15].ptParent >= 0.0 )
  {
    if ( *(float *)&ptQTask[15].ptParent <= 1.0 )
      v4 = *(float *)&ptQTask[15].ptParent;
    else
      v4 = 1.0;
  }
  else
  {
    v4 = 0.0;
  }
  *(float *)&ptQTask[15].ptParent = v4;
  FlatSkyLayer_FixFilename((char *)&ptQTask[8].tQTaskRefList.ptMiddle);
  strncpy(zTemp, (char *)&ptQTask[8].tQTaskRefList.ptMiddle, 0x100u);
  if ( LOBYTE(ptQTask[8].tQTaskRefList.ptMiddle)
    && (!strstr((char *)&ptQTask[2].tQTaskChildren, (char *)&ptQTask[8].tQTaskRefList.ptMiddle)
     || strlen((char *)&ptQTask[8].tQTaskRefList.ptMiddle) != strlen((char *)&ptQTask[2].tQTaskChildren)) )
  {
    if ( !strstr((char *)&ptQTask[8].tQTaskRefList.ptMiddle, "File not found")
      && (Resource_IsLoadedInternal(zTemp, nullptr) || File_Exists(zTemp)) )
    {
      if ( ptQTask[2].ptPrev )
      {
        Texture_Free((struct TexInfo_s *)&ptQTask[1]);
        ptQTask[2].ptPrev = nullptr;
      }
      Texture_Load((struct TexInfo_s *)&ptQTask[1], nullptr, zTemp);
      ptQTask[2].ptPrev = (struct QTask_s *)1;
    }
    else
    {
      sprintf((char *const)&ptQTask[8].tQTaskRefList.ptMiddle, "File not found");
    }
  }
  sprintf((char *const)&ptQTask[2].tQTaskChildren, (char *const)&ptQTask[8].tQTaskRefList.ptMiddle);
}

// source: h/2/flatsky.c:649  [size]
void __cdecl FlatSkyLayer_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = FlatSkyLayer_ptParameterList;
}

// source: h/2/flatsky.c:665  [size]
// attributes: thunk
void __cdecl FlatSky_DrawEnvmapHandler(struct QTask_s *ptQTask, void *pxContext)
{
  FlatSky_EnterHandler(ptQTask, pxContext);
}

// source: h/2/flatsky.c:678  [size]
void __cdecl FlatSky_EnumerateEnvmapHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QObjectVector_s *v2; // esi
  unsigned int nAllocated; // eax
  struct QTask_s **v4; // ecx

  if ( (*((_BYTE *)pxContext + 8) & 1) != 0 )
  {
    v2 = *(struct QObjectVector_s **)pxContext;
    if ( *(_DWORD *)(*(_DWORD *)pxContext + 36) == *(_DWORD *)(*(_DWORD *)pxContext + 40) )
      QObjectVector_Realloc(v2, v2->nReallocSize);
    nAllocated = v2->nAllocated;
    v4 = (struct QTask_s **)v2->papxElement[nAllocated];
    v2->nAllocated = nAllocated + 1;
    *v4 = ptQTask;
    v4[1] = nullptr;
  }
}

// source: h/2/flatsky.c:708  [anchor-strings]
void __cdecl FlatSky_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // ax
  unsigned __int16 v2; // si
  unsigned __int16 v3; // di
  __int16 v4; // bx
  __int16 v5; // bp
  struct ParameterList_s *v6; // eax
  int v7; // edx
  struct ParameterList_s *v8; // eax
  int v9; // edx
  void **v10; // esi
  struct QVector_s *v11; // eax

  FlatSky_eQTaskType = QTask_NewQTaskType("FlatSky", 216, DynCubeObj_eQTaskType, 0, 0);
  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("FlatSkyLayer", 636, BaseQTaskType, 0, 0);
  v2 = FlatSky_eQTaskType;
  v3 = v1;
  FlatSkyLayer_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(FlatSky_eQTaskType, 0, FlatSky_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, 2, FlatSky_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v2, 5, FlatSky_EnterHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, 1, FlatSky_RunHandler);
  v4 = ParameterList_eGetParameterListQTaskEvent;
  QTask_LinkQTaskEventHandlerFn(
    v2,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))FlatSky_GetParameterListHandler);
  v5 = ParameterList_eUpdateInternalDataQTaskEvent;
  QTask_LinkQTaskEventHandlerFn(v2, ParameterList_eUpdateInternalDataQTaskEvent, FlatSky_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(v3, 0, FlatSkyLayer_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v3, 2, FlatSkyLayer_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v3,
    v4,
    (void (__cdecl *)(struct QTask_s *, void *))FlatSkyLayer_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v3, v5, FlatSkyLayer_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v3, 1, (void (__cdecl *)(struct QTask_s *))FlatSkyLayer_RunHandler);
  QTask_LinkQTaskEventHandlerFn(v2, DynCubeObj_eDynCubeObjRegisterQTaskEvent, nullptr);
  QTask_LinkQTaskEventHandlerFn(v2, DynCubeObj_eDynCubeObjRemoveQTaskEvent, nullptr);
  QTask_LinkQTaskEventHandlerFn(v2, Envmap_eDrawQTaskEvent, FlatSky_DrawEnvmapHandler);
  QTask_LinkQTaskEventHandlerFn(v2, Envmap_eEnumerateQTaskEvent, FlatSky_EnumerateEnvmapHandler);
  v6 = (struct ParameterList_s *)Mem_AllocFn(232, 4);
  v6->ptParameterListItem = (struct ParameterListItem_s *)&v6[1];
  v7 = Level_eParameterTypeReal32;
  v6->nParameters = 0;
  v6->nMaxParameters = 11;
  FlatSky_ptParameterList = v6;
  ParameterList_AddParameter(v6, 0x7Cu, v7, "Fog Amount", 7u, &unk_6B0238);
  ParameterList_AddParameter(FlatSky_ptParameterList, 0x74u, Level_eParameterTypeReal32, "Z Pos", 7u, nullptr);
  ParameterList_AddParameter(FlatSky_ptParameterList, 0x78u, Level_eParameterTypeReal32, "Distance", 7u, nullptr);
  ParameterList_AddParameter(FlatSky_ptParameterList, 0x80u, Level_eParameterTypeRGB, "Fog Color", 7u, nullptr);
  ParameterList_AddParameter(
    FlatSky_ptParameterList,
    0xD0u,
    Level_eParameterTypebool8,
    "SkyDome Snap Colours",
    7u,
    nullptr);
  ParameterList_AddParameter(
    FlatSky_ptParameterList,
    0x90u,
    Level_eParameterTypeDegrees,
    "SkyDome Angle",
    7u,
    &unk_6B0258);
  ParameterList_AddParameter(FlatSky_ptParameterList, 0x94u, Level_eParameterTypeRGB, "SkyDome Top Colour", 7u, nullptr);
  ParameterList_AddParameter(
    FlatSky_ptParameterList,
    0xACu,
    Level_eParameterTypeRGB,
    "SkyDome Middle Colour 1",
    7u,
    nullptr);
  ParameterList_AddParameter(
    FlatSky_ptParameterList,
    0xA0u,
    Level_eParameterTypeRGB,
    "SkyDome Middle Colour 2",
    7u,
    nullptr);
  ParameterList_AddParameter(
    FlatSky_ptParameterList,
    0xC4u,
    Level_eParameterTypeRGB,
    "SkyDome Bottom Colour 1",
    7u,
    nullptr);
  ParameterList_AddParameter(
    FlatSky_ptParameterList,
    0xB8u,
    Level_eParameterTypeRGB,
    "SkyDome Bottom Colour 2",
    7u,
    nullptr);
  v8 = (struct ParameterList_s *)Mem_AllocFn(132, 4);
  v9 = Level_eParameterTypeString256;
  v8->ptParameterListItem = (struct ParameterListItem_s *)&v8[1];
  v8->nParameters = 0;
  v8->nMaxParameters = 6;
  FlatSkyLayer_ptParameterList = v8;
  ParameterList_AddParameter(v8, 0x158u, v9, "Texture File Name", 7u, nullptr);
  ParameterList_AddParameter(FlatSkyLayer_ptParameterList, 0x258u, Level_eParameterTypeReal32, "Scale", 7u, nullptr);
  ParameterList_AddParameter(
    FlatSkyLayer_ptParameterList,
    0x25Cu,
    Level_eParameterTypeReal32,
    "X Speed",
    7u,
    &unk_6B0248);
  ParameterList_AddParameter(
    FlatSkyLayer_ptParameterList,
    0x260u,
    Level_eParameterTypeReal32,
    "Y Speed",
    7u,
    &unk_6B0248);
  ParameterList_AddParameter(FlatSkyLayer_ptParameterList, 0x26Cu, Level_eParameterTypeReal32, "Alpha", 7u, &unk_6B0238);
  ParameterList_AddParameter(FlatSkyLayer_ptParameterList, 0x270u, Level_eParameterTypeRGB, "Color", 7u, nullptr);
  v10 = (void **)Mem_AllocFn(128, 4);
  v11 = (struct QVector_s *)Mem_AllocFn(24, 4);
  v11->tPrivate.nElements = 0;
  v11->tPrivate.isPrivateMem = false;
  v11->tPrivate.isStrictOrder = false;
  v11->tPrivate.papxElement = v10;
  v11->tPrivate.nArraySize = 32;
  v11->tPrivate.nReallocSize = 32;
  FlatSky_ptQVector = v11;
}

// source: h/2/flatsky.c:774  [anchor-hash]
void __cdecl FlatSky_Close()
{
  int v0; // esi
  int v1; // esi

  QVector_Delete(FlatSky_ptQVector);
  if ( FlatSkyLayer_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&FlatSkyLayer_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  if ( FlatSky_ptParameterList )
  {
    v1 = *(_DWORD *)((unsigned int)&FlatSky_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
  QTask_DeleteQTaskType(FlatSkyLayer_eQTaskType);
  QTask_DeleteQTaskType(FlatSky_eQTaskType);
}

// source: h/2/flatsky.c:795  [size]
unsigned __int16 __cdecl FlatSky_GetQTaskType()
{
  return FlatSky_eQTaskType;
}

// source: h/2/flatsky.c:808  [size]
unsigned __int16 __cdecl FlatSkyLayer_GetQTaskType()
{
  return FlatSkyLayer_eQTaskType;
}

// source: h/2/flatsky.c:821  [anchor-callee]
void __cdecl FlatSky_SetTimeCallback(struct FlatSky_s *ptFlatSky, float *pvTime)
{
  float pvTimea = *(float *)&pvTime; // [esp+18h] [ebp+8h] ARGSLOT

  pvTimea = *pvTime;
  ptFlatSky->vTime = pvTimea;
  FlatSkyKeyframe_ApplyTime(
    &ptFlatSky->tDynCubeObj.tQObj.tQTask,
    pvTimea,
    &ptFlatSky->tSkyColourTop,
    &ptFlatSky->tSkyColourMiddleSouth,
    &ptFlatSky->tSkyColourMiddleNorth,
    &ptFlatSky->tSkyColourBottomSouth,
    &ptFlatSky->tSkyColourBottomNorth);
  SkyDome_SetColour(
    ptFlatSky->pxSkyDome,
    &ptFlatSky->tSkyColourTop,
    &ptFlatSky->tSkyColourMiddleNorth,
    &ptFlatSky->tSkyColourMiddleSouth,
    &ptFlatSky->tSkyColourBottomNorth,
    &ptFlatSky->tSkyColourBottomSouth);
}

// source: h/2/flatsky.c:850  [anchor-callee]
void __cdecl FlatSky_SetTime(float vTime)
{
  unsigned int v1; // esi
  struct QVector_s *v2; // edi
  void ***p_papxElement; // ebx

  v1 = 0;
  v2 = FlatSky_ptQVector;
  if ( FlatSky_ptQVector->tPrivate.nElements )
  {
    p_papxElement = &FlatSky_ptQVector->tPrivate.papxElement;
    do
      FlatSky_SetTimeCallback((struct FlatSky_s *)(*p_papxElement)[v1++], &vTime);
    while ( v1 < v2->tPrivate.nElements );
  }
}
