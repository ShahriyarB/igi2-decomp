/* h/2/flatwater.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/flatwater.c:108  [anchor-mhash]
void __cdecl FlatWater_EnterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { int nNumVertices; };
    struct { int nNumVerticesa; };
    struct { int nNumVerticesb; };
    struct { char igi2_o3[4]; float vDistance; };
    struct { char igi2_o4[4]; float vDistancea; };
    struct { char igi2_o5[4]; float vDistanceb; };
    struct { char igi2_o6[4]; int vDistancec; };
    struct { char igi2_o7[8]; int iSplit; };
    struct { char igi2_o8[8]; int iSplita; };
    struct { char igi2_o9[8]; int iSplitb; };
    struct { char igi2_o10[8]; float iSplitc; };
    struct { char igi2_o11[8]; float iSplitd; };
    struct { char igi2_o12[8]; float iSplite; };
    struct { char igi2_o13[8]; float iSplitf; };
    struct { char igi2_o14[20]; float tTempScreenRef0; };
    struct { char igi2_o15[24]; float tTempScreenRef0_4; };
    struct { char igi2_o16[24]; float tTempScreenRef0_4a; };
    struct { char igi2_o17[28]; struct real32x2_t tTempScreenRef1; };
    struct { char igi2_o18[36]; float vPosZ; };
    struct { char igi2_o19[40]; float v121; };
    struct { char igi2_o20[40]; int v122; };
    struct { char igi2_o21[40]; float v123; };
    struct { char igi2_o22[52]; int v124; };
    struct { char igi2_o23[56]; float v125; };
    struct { char igi2_o24[56]; int v126; };
    struct { char igi2_o25[68]; struct FlatWaterLayer_t *ptLayer; };
    struct { char igi2_o26[72]; float tScreenRef0; };
    struct { char igi2_o27[76]; float tScreenRef0_4; };
    struct { char igi2_o28[80]; int isUpperFill; };
    struct { char igi2_o29[80]; double isUpperFilla; };
    struct { char igi2_o30[92]; float tViewVector; };
    struct { char igi2_o31[96]; float tViewVector_4; };
    struct { char igi2_o32[100]; float tViewVector_8; };
    struct { char igi2_o33[104]; float tTemp_; };
    struct { char igi2_o34[104]; float tTemp_a; };
    struct { char igi2_o35[108]; float tTemp__4; };
    struct { char igi2_o36[112]; float tTemp__8; };
    struct { char igi2_o37[116]; float Real32x3_Rotate_tTemp; };
    struct { char igi2_o38[120]; float Real32x3_Rotate_tTemp_4; };
    struct { char igi2_o39[124]; float Real32x3_Rotate_tTemp_8; };
    struct { char igi2_o40[128]; float v142; };
    struct { char igi2_o41[132]; float v143; };
    struct { char igi2_o42[136]; float v144; };
    struct { char igi2_o43[140]; float Real32x3_RotateInverse_tTemp; };
    struct { char igi2_o44[144]; float Real32x3_RotateInverse_tTemp_4; };
    struct { char igi2_o45[148]; float Real32x3_RotateInverse_tTemp_8; };
    struct { char igi2_o46[152]; float tCenter; };
    struct { char igi2_o47[156]; float tCenter_4; };
    struct { char igi2_o48[160]; double tScreenRef1; };
    struct { char igi2_o49[172]; float v151; };
    struct { char igi2_o50[176]; float v152; };
    struct { char igi2_o51[180]; float v153; };
    struct { char igi2_o52[184]; struct real32x9_t tMatrix; };
    struct { char igi2_o53[224]; struct real32x3_t tPos; };
    struct { char igi2_o54[236]; struct real32x3_t tRelativePos; };
    struct { char igi2_o55[248]; struct real64x2_t tTexturePos; };
    struct { char igi2_o56[264]; struct real32x2_t atScreenPos[1000]; };
    struct { char igi2_o57[8264]; int aiVertex[1000]; };
    struct { char igi2_o58[12264]; float avZPos[2000]; };
    struct { char igi2_o59[20264]; struct real32x2_t atTexturePos[1000]; };
    struct { char igi2_o60[28264]; float avFogValue[1000]; };
    struct { char igi2_o61[32264]; struct QVertex_s atQVertex[1000]; };
    char igi2_extent[68264];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v2; // st7
  bool v3; // c0
  double v4; // st7
  long double v5; // st5
  long double v6; // st7
  long double v7; // st6
  double v8; // st5
  double v9; // st4
  double v10; // st4
  int v11; // edi
  int v12; // esi
  int v13; // edx
  double v14; // st7
  double v15; // st6
  double v16; // st5
  double v17; // st4
  double v18; // st3
  double v19; // st3
  double v20; // st4
  double v21; // st4
  double v22; // st4
  double v23; // st4
  double v24; // st4
  double v25; // st4
  int v26; // ecx
  double v27; // st7
  double v28; // st6
  double v29; // st5
  double v30; // st5
  int v31; // ebx
  int v32; // edi
  int v33; // ecx
  int i; // esi
  double vX; // st7
  double v36; // st6
  double v37; // st6
  int v38; // ecx
  float *p_vY; // edx
  int v40; // edi
  int v41; // esi
  int v42; // edx
  int v43; // eax
  int v44; // eax
  double vY; // st7
  bool v46; // c0
  int v47; // eax
  int *v48; // ecx
  int v49; // edx
  int v50; // ebx
  int v51; // esi
  int v52; // edi
  int v53; // esi
  int v54; // edi
  int v55; // esi
  int v56; // edi
  int v57; // esi
  int v58; // edi
  int v59; // esi
  int v60; // edi
  bool v61; // zf
  int v62; // ecx
  double v63; // st7
  double v64; // st6
  long double v65; // st7
  long double v66; // st7
  long double v67; // st6
  long double v68; // st6
  double v69; // st7
  double v70; // st6
  double v71; // rtt
  double v72; // st6
  double vScale; // st5
  double v74; // st7
  double v75; // st7
  float v76; // ebx
  int isTextureLoaded; // eax
  int v78; // ecx
  int v79; // esi
  float *p_vR; // eax
  int v81; // edx
  float v82; // ebx
  float v83; // edx
  int v84; // edx
  float v85; // ebx
  float v86; // edx
  int v87; // edx
  float v88; // ebx
  float v89; // edx
  int v90; // edx
  float v91; // ebx
  float v92; // edx
  float *v93; // eax
  int v94; // edx
  float v95; // esi
  float v96; // edx
  int v97; // edx
  float *v98; // eax
  int v99; // ecx
  float v100; // esi
  float v101; // ecx

  igi2_frame.vDistance = *(float *)&ptQTask[3].tQTaskChildren.ptHead * 4096.0;
  v2 = *(double *)&ptQTask[3].ptNext - TransContext_tActiveTransContext.tPos.vZ;
  igi2_frame.vPosZ = v2;
  v3 = v2 < 0.0;
  v4 = igi2_frame.vPosZ;
  if ( v3 )
    v4 = -v4;
  if ( v4 >= 409.6000061035156 )
  {
    qmemcpy(&igi2_frame.tMatrix, &TransContext_tActiveTransContext, sizeof(igi2_frame.tMatrix));
    if ( igi2_frame.tMatrix.tZ.vX == 0.0 && igi2_frame.tMatrix.tZ.vY == 0.0 )
      igi2_frame.tMatrix.tZ.vX = 1.0;
    igi2_frame.tScreenRef1 = igi2_frame.tMatrix.tZ.vX;
    v5 = sqrt(igi2_frame.tMatrix.tZ.vX * igi2_frame.tMatrix.tZ.vX + igi2_frame.tMatrix.tZ.vY * igi2_frame.tMatrix.tZ.vY);
    igi2_frame.tMatrix.tZ.vX = igi2_frame.tMatrix.tZ.vX * (1.0 / v5);
    igi2_frame.tMatrix.tZ.vY = igi2_frame.tMatrix.tZ.vY * (1.0 / v5);
    v6 = 1.0 / v5 * 0.0;
    igi2_frame.tTemp_ = 0.0 * v6 - igi2_frame.tMatrix.tZ.vY;
    v7 = -(0.0 * v6 - igi2_frame.tMatrix.tZ.vX);
    igi2_frame.tTemp__8 = igi2_frame.tMatrix.tZ.vY * 0.0 - igi2_frame.tMatrix.tZ.vX * 0.0;
    igi2_frame.ptLayer = (struct FlatWaterLayer_t *)QTask_GetFirstChildOfType(ptQTask, FlatWaterLayer_eQTaskType);
    if ( igi2_frame.ptLayer )
    {
      v8 = -igi2_frame.vDistance;
      v9 = igi2_frame.vPosZ * 0.0;
      igi2_frame.iSplitc = igi2_frame.tMatrix.tZ.vX * igi2_frame.vDistance + v9;
      igi2_frame.Real32x3_Rotate_tTemp = v8 * igi2_frame.tTemp_ + igi2_frame.iSplitc;
      v10 = v9 + igi2_frame.tMatrix.tZ.vY * igi2_frame.vDistance;
      igi2_frame.Real32x3_Rotate_tTemp_4 = v8 * v7 + v10;
      *(float *)&igi2_frame.isUpperFill = v6 * igi2_frame.vDistance;
      igi2_frame.Real32x3_Rotate_tTemp_8 = v8 * igi2_frame.tTemp__8 + *(float *)&igi2_frame.isUpperFill + igi2_frame.vPosZ;
      igi2_frame.v142 = igi2_frame.tTemp_ * igi2_frame.vDistance + igi2_frame.iSplitc;
      igi2_frame.v143 = v7 * igi2_frame.vDistance + v10;
      igi2_frame.v144 = igi2_frame.tTemp__8 * igi2_frame.vDistance + *(float *)&igi2_frame.isUpperFill + igi2_frame.vPosZ;
      do
      {
        v11 = igi2_frame.isUpperFill;
        v12 = 0;
        v13 = 0;
        igi2_frame.tCenter = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHalfWidth
                + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX;
        igi2_frame.iSplit = 0;
        igi2_frame.tCenter_4 = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHalfHeight
                  + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vY;
        v14 = igi2_frame.Real32x3_Rotate_tTemp_8 * TransContext_tActiveTransContext.tMatrix.tX.vZ
            + igi2_frame.Real32x3_Rotate_tTemp_4 * TransContext_tActiveTransContext.tMatrix.tX.vY
            + igi2_frame.Real32x3_Rotate_tTemp * TransContext_tActiveTransContext.tMatrix.tX.vX;
        v15 = igi2_frame.Real32x3_Rotate_tTemp_8 * TransContext_tActiveTransContext.tMatrix.tY.vZ
            + igi2_frame.Real32x3_Rotate_tTemp_4 * TransContext_tActiveTransContext.tMatrix.tY.vY
            + igi2_frame.Real32x3_Rotate_tTemp * TransContext_tActiveTransContext.tMatrix.tY.vX;
        v16 = igi2_frame.Real32x3_Rotate_tTemp_8 * TransContext_tActiveTransContext.tMatrix.tZ.vZ
            + igi2_frame.Real32x3_Rotate_tTemp_4 * TransContext_tActiveTransContext.tMatrix.tZ.vY
            + igi2_frame.Real32x3_Rotate_tTemp * TransContext_tActiveTransContext.tMatrix.tZ.vX;
        igi2_frame.v151 = igi2_frame.v144 * TransContext_tActiveTransContext.tMatrix.tX.vZ
             + igi2_frame.v143 * TransContext_tActiveTransContext.tMatrix.tX.vY
             + igi2_frame.v142 * TransContext_tActiveTransContext.tMatrix.tX.vX;
        igi2_frame.v152 = igi2_frame.v144 * TransContext_tActiveTransContext.tMatrix.tY.vZ
             + igi2_frame.v143 * TransContext_tActiveTransContext.tMatrix.tY.vY
             + igi2_frame.v142 * TransContext_tActiveTransContext.tMatrix.tY.vX;
        igi2_frame.v153 = igi2_frame.v144 * TransContext_tActiveTransContext.tMatrix.tZ.vZ
             + igi2_frame.v143 * TransContext_tActiveTransContext.tMatrix.tZ.vY
             + igi2_frame.v142 * TransContext_tActiveTransContext.tMatrix.tZ.vX;
        do
        {
          if ( v16 > 0.0 && igi2_frame.v153 > 0.0 )
          {
            igi2_frame.tTempScreenRef0 = v14 * (1.0 / v16) * TransContext_tActiveTransContext.vScreenFOVX
                            + TransContext_tActiveTransContext.vScreenOriginX;
            igi2_frame.tTempScreenRef0_4a = v15 * (1.0 / v16) * TransContext_tActiveTransContext.vScreenFOVY
                               + TransContext_tActiveTransContext.vScreenOriginY;
            igi2_frame.isUpperFilla = 1.0 / igi2_frame.v153;
            igi2_frame.tTempScreenRef1.vX = igi2_frame.v151 * igi2_frame.isUpperFilla * TransContext_tActiveTransContext.vScreenFOVX
                               + TransContext_tActiveTransContext.vScreenOriginX;
            v17 = igi2_frame.v152 * igi2_frame.isUpperFilla * TransContext_tActiveTransContext.vScreenFOVY
                + TransContext_tActiveTransContext.vScreenOriginY;
            v18 = igi2_frame.tTempScreenRef1.vX - igi2_frame.tTempScreenRef0;
            v11 = (igi2_frame.vPosZ < 0.0) ^ (igi2_frame.tTempScreenRef0 < (double)igi2_frame.tTempScreenRef1.vX);
            igi2_frame.vDistancea = v18;
            v19 = (igi2_frame.tCenter_4 - v18 * 0.5 - (igi2_frame.tTempScreenRef0_4a + v17) * 0.5)
                * ((double)igi2_frame.iSplit
                 * 0.10000000149011612
                 * ((double)igi2_frame.iSplit
                  * 0.10000000149011612));
            igi2_frame.tTempScreenRef0_4 = igi2_frame.tTempScreenRef0_4a + v19;
            igi2_frame.tTempScreenRef1.vY = v19 + v17;
            if ( v16 >= 0.0 && igi2_frame.v153 >= 0.0 )
            {
              if ( igi2_frame.tTempScreenRef0 <= (double)igi2_frame.tTempScreenRef1.vX )
              {
                v20 = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vWidth
                    + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX;
                *(float *)&igi2_frame.nNumVertices = igi2_frame.tTempScreenRef1.vY - igi2_frame.tTempScreenRef0_4;
                igi2_frame.atScreenPos[v12].vY = (v20 - igi2_frame.tTempScreenRef0) * *(float *)&igi2_frame.nNumVertices / igi2_frame.vDistancea + igi2_frame.tTempScreenRef0_4;
                igi2_frame.atScreenPos[v12].vX = v20;
              }
              else
              {
                igi2_frame.atScreenPos[v12].vX = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX;
                *(float *)&igi2_frame.nNumVertices = igi2_frame.tTempScreenRef1.vY - igi2_frame.tTempScreenRef0_4;
                igi2_frame.atScreenPos[v12].vY = (RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX
                                     - igi2_frame.tTempScreenRef0)
                                    * *(float *)&igi2_frame.nNumVertices
                                    / igi2_frame.vDistancea
                                    + igi2_frame.tTempScreenRef0_4;
              }
              if ( igi2_frame.atScreenPos[v12].vY < (double)RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vY
                || RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHeight
                 + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vY < igi2_frame.atScreenPos[v12].vY )
              {
                if ( igi2_frame.tTempScreenRef0_4 <= (double)igi2_frame.tTempScreenRef1.vY )
                {
                  v22 = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHeight
                      + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vY;
                  igi2_frame.atScreenPos[v12].vX = (v22 - igi2_frame.tTempScreenRef0_4) * igi2_frame.vDistancea / *(float *)&igi2_frame.nNumVertices
                                      + igi2_frame.tTempScreenRef0;
                  igi2_frame.atScreenPos[v12].vY = v22;
                }
                else
                {
                  v21 = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vY - igi2_frame.tTempScreenRef0_4;
                  igi2_frame.atScreenPos[v12].vY = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vY;
                  igi2_frame.atScreenPos[v12].vX = v21 * igi2_frame.vDistancea / *(float *)&igi2_frame.nNumVertices + igi2_frame.tTempScreenRef0;
                }
              }
              if ( (!v13
                 || igi2_frame.atScreenPos[v12].vX == RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX
                 || RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vWidth
                  + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX == igi2_frame.atScreenPos[v12].vX)
                && igi2_frame.atScreenPos[v12].vX >= (double)RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX
                && RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vWidth
                 + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX >= igi2_frame.atScreenPos[v12].vX )
              {
                LODWORD(igi2_frame.avZPos[++v12 + 999]) = v13 == 0;
              }
              if ( igi2_frame.tTempScreenRef1.vX <= (double)igi2_frame.tTempScreenRef0 )
              {
                v23 = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vWidth
                    + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX;
                *(float *)&igi2_frame.nNumVerticesa = igi2_frame.tTempScreenRef0_4 - igi2_frame.tTempScreenRef1.vY;
                igi2_frame.vDistanceb = igi2_frame.tTempScreenRef0 - igi2_frame.tTempScreenRef1.vX;
                igi2_frame.atScreenPos[v12].vY = (v23 - igi2_frame.tTempScreenRef1.vX) * *(float *)&igi2_frame.nNumVerticesa / igi2_frame.vDistanceb
                                    + igi2_frame.tTempScreenRef1.vY;
                igi2_frame.atScreenPos[v12].vX = v23;
              }
              else
              {
                igi2_frame.atScreenPos[v12].vX = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX;
                *(float *)&igi2_frame.nNumVerticesa = igi2_frame.tTempScreenRef0_4 - igi2_frame.tTempScreenRef1.vY;
                igi2_frame.vDistanceb = igi2_frame.tTempScreenRef0 - igi2_frame.tTempScreenRef1.vX;
                igi2_frame.atScreenPos[v12].vY = (RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX
                                     - igi2_frame.tTempScreenRef1.vX)
                                    * *(float *)&igi2_frame.nNumVerticesa
                                    / igi2_frame.vDistanceb
                                    + igi2_frame.tTempScreenRef1.vY;
              }
              if ( igi2_frame.atScreenPos[v12].vY < (double)RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vY
                || RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHeight
                 + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vY < igi2_frame.atScreenPos[v12].vY )
              {
                if ( igi2_frame.tTempScreenRef1.vY <= (double)igi2_frame.tTempScreenRef0_4 )
                {
                  v25 = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHeight
                      + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vY;
                  igi2_frame.atScreenPos[v12].vX = (v25 - igi2_frame.tTempScreenRef1.vY) * igi2_frame.vDistanceb / *(float *)&igi2_frame.nNumVerticesa
                                      + igi2_frame.tTempScreenRef1.vX;
                  igi2_frame.atScreenPos[v12].vY = v25;
                }
                else
                {
                  v24 = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vY - igi2_frame.tTempScreenRef1.vY;
                  igi2_frame.atScreenPos[v12].vY = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vY;
                  igi2_frame.atScreenPos[v12].vX = v24 * igi2_frame.vDistanceb / *(float *)&igi2_frame.nNumVerticesa + igi2_frame.tTempScreenRef1.vX;
                }
              }
              if ( (!v13
                 || igi2_frame.atScreenPos[v12].vX == RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX
                 || RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vWidth
                  + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX == igi2_frame.atScreenPos[v12].vX)
                && igi2_frame.atScreenPos[v12].vX >= (double)RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX
                && RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vWidth
                 + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX >= igi2_frame.atScreenPos[v12].vX )
              {
                LODWORD(igi2_frame.avZPos[++v12 + 999]) = v13 == 0;
              }
              if ( !v13 )
              {
                igi2_frame.tScreenRef0 = igi2_frame.tTempScreenRef0;
                igi2_frame.tScreenRef0_4 = igi2_frame.tTempScreenRef0_4;
                igi2_frame.tScreenRef1 = *(double *)&igi2_frame.tTempScreenRef1;
              }
            }
          }
          igi2_frame.iSplit = ++v13;
        }
        while ( v13 < 10 );
        igi2_frame.isUpperFill = v11;
        v26 = 0;
        igi2_frame.v125 = *(float *)&igi2_frame.tScreenRef1 - igi2_frame.tScreenRef0;
        igi2_frame.v121 = *((float *)&igi2_frame.tScreenRef1 + 1) - igi2_frame.tScreenRef0_4;
        do
        {
          v27 = (double)(v26 & 1) * RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vWidth
              + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX;
          v28 = (double)((v26 >> 1) & 1) * RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHeight
              + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vY;
          v29 = (v27 - igi2_frame.tScreenRef0) * igi2_frame.v121;
          if ( igi2_frame.v125 == 0.0 )
          {
            if ( v29 <= 0.0 )
              v30 = -3.4028234663852886e+38;
            else
              v30 = 3.4028234663852886e+38;
          }
          else
          {
            v30 = v29 / igi2_frame.v125 + igi2_frame.tScreenRef0_4;
          }
          if ( v28 < v30 != v11 )
          {
            igi2_frame.atScreenPos[v12].vX = v27;
            igi2_frame.iSplitd = v28;
            igi2_frame.atScreenPos[v12++].vY = igi2_frame.iSplitd;
            LODWORD(igi2_frame.avZPos[v12 + 999]) = v13 == 0;
          }
          ++v26;
        }
        while ( v26 < 4 );
        v31 = 0;
        igi2_frame.nNumVerticesb = v12;
        for ( igi2_frame.vDistancec = 0; v31 < igi2_frame.nNumVerticesb; igi2_frame.vDistancec = v31 )
        {
          v32 = 0;
          v33 = 0;
          if ( igi2_frame.nNumVerticesb >= 4 )
          {
            for ( i = 3; i < igi2_frame.nNumVerticesb; i += 4 )
            {
              if ( v33 != v31 && igi2_frame.atScreenPos[v31].vY == igi2_frame.atScreenPos[v33].vY )
                v32 = 1;
              v31 = igi2_frame.vDistancec;
              if ( i - 2 != igi2_frame.vDistancec && igi2_frame.atScreenPos[igi2_frame.vDistancec].vY == igi2_frame.atScreenPos[v33 + 1].vY )
                v32 = 1;
              if ( i - 1 != igi2_frame.vDistancec && igi2_frame.atScreenPos[igi2_frame.vDistancec].vY == igi2_frame.atScreenPos[v33 + 2].vY )
                v32 = 1;
              if ( i != igi2_frame.vDistancec && igi2_frame.atScreenPos[igi2_frame.vDistancec].vY == igi2_frame.atScreenPos[v33 + 3].vY )
                v32 = 1;
              v33 += 4;
            }
          }
          for ( ; v33 < igi2_frame.nNumVerticesb; ++v33 )
          {
            if ( v33 != v31 && igi2_frame.atScreenPos[v31].vY == igi2_frame.atScreenPos[v33].vY )
              v32 = 1;
          }
          if ( igi2_frame.atScreenPos[v31].vX == RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX )
            vX = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vWidth
               + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX;
          else
            vX = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX;
          v36 = (vX - igi2_frame.tScreenRef0) * igi2_frame.v121;
          if ( igi2_frame.v125 == 0.0 )
          {
            if ( v36 <= 0.0 )
              v37 = -3.4028234663852886e+38;
            else
              v37 = 3.4028234663852886e+38;
          }
          else
          {
            v37 = v36 / igi2_frame.v125 + igi2_frame.tScreenRef0_4;
          }
          v38 = 0;
          if ( !v32 )
          {
            p_vY = &igi2_frame.atScreenPos[v31].vY;
            if ( v37 >= *p_vY != igi2_frame.isUpperFill || v37 <= *p_vY == igi2_frame.isUpperFill )
            {
              igi2_frame.atScreenPos[igi2_frame.nNumVerticesb].vX = vX;
              igi2_frame.atScreenPos[igi2_frame.nNumVerticesb].vY = *p_vY;
              igi2_frame.avZPos[igi2_frame.nNumVerticesb++ + 1000] = 0.0;
              v31 = 0;
            }
            else
            {
              v40 = -1;
              v41 = -1;
              igi2_frame.iSplita = igi2_frame.atScreenPos[v31].vX != RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX;
              if ( igi2_frame.nNumVerticesb > 0 )
              {
                v42 = 0;
                igi2_frame.v124 = 0;
                do
                {
                  if ( v38 != v31 )
                  {
                    if ( *(float *)((char *)&igi2_frame.atScreenPos[0].vY + v42) < (double)igi2_frame.atScreenPos[v31].vY )
                    {
                      if ( v40 == -1
                        || *(float *)((char *)&igi2_frame.atScreenPos[0].vY + v42) >= (double)igi2_frame.atScreenPos[v40].vY
                        && (*(float *)((char *)&igi2_frame.atScreenPos[0].vY + v42) != igi2_frame.atScreenPos[v40].vY
                         || (v43 = *(float *)((char *)&igi2_frame.atScreenPos[0].vX + v42) > (double)igi2_frame.atScreenPos[v40].vX,
                             v31 = igi2_frame.vDistancec,
                             v42 = igi2_frame.v124,
                             v43 != igi2_frame.iSplita)) )
                      {
                        if ( LODWORD(igi2_frame.avZPos[v38 + 1000]) )
                          v40 = v38;
                      }
                    }
                    if ( *(float *)((char *)&igi2_frame.atScreenPos[0].vY + v42) > (double)igi2_frame.atScreenPos[v31].vY )
                    {
                      if ( v41 == -1
                        || *(float *)((char *)&igi2_frame.atScreenPos[0].vY + v42) <= (double)igi2_frame.atScreenPos[v41].vY
                        && (*(float *)((char *)&igi2_frame.atScreenPos[0].vY + v42) != igi2_frame.atScreenPos[v41].vY
                         || (v44 = *(float *)((char *)&igi2_frame.atScreenPos[0].vX + v42) > (double)igi2_frame.atScreenPos[v41].vX,
                             v31 = igi2_frame.vDistancec,
                             v42 = igi2_frame.v124,
                             v44 != igi2_frame.iSplita)) )
                      {
                        if ( LODWORD(igi2_frame.avZPos[v38 + 1000]) )
                          v41 = v38;
                      }
                    }
                  }
                  ++v38;
                  v42 += 8;
                  igi2_frame.v124 = v42;
                }
                while ( v38 < igi2_frame.nNumVerticesb );
                if ( v40 != -1 && v41 != -1 && igi2_frame.atScreenPos[v40].vX != igi2_frame.atScreenPos[v41].vX )
                {
                  igi2_frame.atScreenPos[igi2_frame.nNumVerticesb].vX = (igi2_frame.atScreenPos[v41].vX - igi2_frame.atScreenPos[v40].vX)
                                                * (igi2_frame.atScreenPos[v31].vY - igi2_frame.atScreenPos[v40].vY)
                                                / (igi2_frame.atScreenPos[v41].vY - igi2_frame.atScreenPos[v40].vY)
                                                + igi2_frame.atScreenPos[v40].vX;
                  vY = igi2_frame.atScreenPos[v31].vY;
                  v46 = vY < RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vY;
                  igi2_frame.atScreenPos[igi2_frame.nNumVerticesb].vY = igi2_frame.atScreenPos[v31].vY;
                  if ( !v46
                    && vY <= RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHeight
                           + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vY )
                  {
                    v31 = 0;
                    igi2_frame.avZPos[igi2_frame.nNumVerticesb++ + 1000] = 0.0;
                  }
                }
              }
            }
          }
          ++v31;
        }
        v47 = 0;
        if ( igi2_frame.nNumVerticesb > 0 )
        {
          do
          {
            igi2_frame.aiVertex[v47] = v47;
            ++v47;
          }
          while ( v47 < igi2_frame.nNumVerticesb );
          igi2_frame.v122 = 1;
          v48 = igi2_frame.aiVertex;
          igi2_frame.iSplitb = igi2_frame.nNumVerticesb - 1;
          igi2_frame.v126 = igi2_frame.nNumVerticesb;
          do
          {
            v49 = igi2_frame.v122;
            if ( igi2_frame.iSplitb >= 4 )
            {
              v50 = igi2_frame.v122 + 3;
              do
              {
                v51 = igi2_frame.aiVertex[v49];
                v52 = *v48;
                if ( igi2_frame.atScreenPos[v51].vY < (double)igi2_frame.atScreenPos[*v48].vY
                  || igi2_frame.atScreenPos[v51].vX < (double)igi2_frame.atScreenPos[v52].vX && igi2_frame.atScreenPos[v51].vY == igi2_frame.atScreenPos[v52].vY )
                {
                  igi2_frame.aiVertex[v49] = v52;
                  *v48 = v51;
                }
                v53 = igi2_frame.aiVertex[v49 + 1];
                v54 = *v48;
                if ( igi2_frame.atScreenPos[v53].vY < (double)igi2_frame.atScreenPos[*v48].vY
                  || igi2_frame.atScreenPos[v53].vX < (double)igi2_frame.atScreenPos[v54].vX && igi2_frame.atScreenPos[v53].vY == igi2_frame.atScreenPos[v54].vY )
                {
                  igi2_frame.aiVertex[v49 + 1] = v54;
                  *v48 = v53;
                }
                v55 = igi2_frame.aiVertex[v49 + 2];
                v56 = *v48;
                if ( igi2_frame.atScreenPos[v55].vY < (double)igi2_frame.atScreenPos[*v48].vY
                  || igi2_frame.atScreenPos[v55].vX < (double)igi2_frame.atScreenPos[v56].vX && igi2_frame.atScreenPos[v55].vY == igi2_frame.atScreenPos[v56].vY )
                {
                  igi2_frame.aiVertex[v49 + 2] = v56;
                  *v48 = v55;
                }
                v57 = igi2_frame.aiVertex[v49 + 3];
                v58 = *v48;
                if ( igi2_frame.atScreenPos[v57].vY < (double)igi2_frame.atScreenPos[*v48].vY
                  || igi2_frame.atScreenPos[v57].vX < (double)igi2_frame.atScreenPos[v58].vX && igi2_frame.atScreenPos[v57].vY == igi2_frame.atScreenPos[v58].vY )
                {
                  igi2_frame.aiVertex[v49 + 3] = v58;
                  *v48 = v57;
                }
                v50 += 4;
                v49 += 4;
              }
              while ( v50 < igi2_frame.nNumVerticesb );
            }
            for ( ; v49 < igi2_frame.nNumVerticesb; ++v49 )
            {
              v59 = igi2_frame.aiVertex[v49];
              v60 = *v48;
              if ( igi2_frame.atScreenPos[v59].vY < (double)igi2_frame.atScreenPos[*v48].vY
                || igi2_frame.atScreenPos[v59].vX < (double)igi2_frame.atScreenPos[v60].vX && igi2_frame.atScreenPos[v59].vY == igi2_frame.atScreenPos[v60].vY )
              {
                igi2_frame.aiVertex[v49] = v60;
                *v48 = v59;
              }
            }
            ++v48;
            v61 = igi2_frame.v126 == 1;
            --igi2_frame.iSplitb;
            ++igi2_frame.v122;
            --igi2_frame.v126;
          }
          while ( !v61 );
        }
        v62 = 0;
        if ( igi2_frame.nNumVerticesb > 0 )
        {
          igi2_frame.v123 = -igi2_frame.vPosZ;
          do
          {
            v63 = (igi2_frame.atScreenPos[v62].vX - igi2_frame.tCenter) / TransContext_tActiveTransContext.vScreenFOVX;
            v64 = (igi2_frame.atScreenPos[v62].vY - igi2_frame.tCenter_4) / TransContext_tActiveTransContext.vScreenFOVY;
            igi2_frame.Real32x3_RotateInverse_tTemp = TransContext_tActiveTransContext.tMatrix.tY.vX * v64
                                         + v63 * TransContext_tActiveTransContext.tMatrix.tX.vX
                                         + TransContext_tActiveTransContext.tMatrix.tZ.vX;
            igi2_frame.tViewVector = igi2_frame.Real32x3_RotateInverse_tTemp;
            igi2_frame.Real32x3_RotateInverse_tTemp_4 = TransContext_tActiveTransContext.tMatrix.tY.vY * v64
                                           + v63 * TransContext_tActiveTransContext.tMatrix.tX.vY
                                           + TransContext_tActiveTransContext.tMatrix.tZ.vY;
            igi2_frame.tViewVector_4 = igi2_frame.Real32x3_RotateInverse_tTemp_4;
            igi2_frame.Real32x3_RotateInverse_tTemp_8 = v64 * TransContext_tActiveTransContext.tMatrix.tY.vZ
                                           + v63 * TransContext_tActiveTransContext.tMatrix.tX.vZ
                                           + TransContext_tActiveTransContext.tMatrix.tZ.vZ;
            igi2_frame.tViewVector_8 = igi2_frame.Real32x3_RotateInverse_tTemp_8;
            if ( igi2_frame.Real32x3_RotateInverse_tTemp != 0.0
              || igi2_frame.Real32x3_RotateInverse_tTemp_4 != 0.0
              || igi2_frame.Real32x3_RotateInverse_tTemp_8 != 0.0 )
            {
              v65 = 1.0
                  / sqrt(
                      igi2_frame.Real32x3_RotateInverse_tTemp * igi2_frame.Real32x3_RotateInverse_tTemp
                    + igi2_frame.Real32x3_RotateInverse_tTemp_4 * igi2_frame.Real32x3_RotateInverse_tTemp_4
                    + igi2_frame.Real32x3_RotateInverse_tTemp_8 * igi2_frame.Real32x3_RotateInverse_tTemp_8);
              igi2_frame.tViewVector = igi2_frame.Real32x3_RotateInverse_tTemp * v65;
              igi2_frame.tViewVector_4 = igi2_frame.Real32x3_RotateInverse_tTemp_4 * v65;
              igi2_frame.tViewVector_8 = igi2_frame.Real32x3_RotateInverse_tTemp_8 * v65;
            }
            v66 = igi2_frame.v123;
            igi2_frame.tRelativePos.vZ = -igi2_frame.vPosZ;
            igi2_frame.tTemp_a = 0.0;
            igi2_frame.tTemp__4 = 0.0;
            if ( igi2_frame.v123 != 0.0 )
            {
              v67 = 1.0 / sqrt(v66 * v66);
              igi2_frame.tTemp_a = 0.0 * v67;
              igi2_frame.tTemp__4 = igi2_frame.tTemp_a;
              v66 = v66 * v67;
            }
            v68 = igi2_frame.tViewVector_8 * v66 + igi2_frame.tTemp__4 * igi2_frame.tViewVector_4 + igi2_frame.tTemp_a * igi2_frame.tViewVector;
            if ( v68 > 9.999999747378752e-06 || v68 < -9.999999747378752e-06 )
            {
              igi2_frame.iSplite = ((igi2_frame.tTemp__4 + igi2_frame.tTemp_a) * 0.0 + v66 * igi2_frame.tRelativePos.vZ) / v68;
              v69 = -(igi2_frame.iSplite * igi2_frame.tViewVector);
              v70 = -(igi2_frame.iSplite * igi2_frame.tViewVector_4);
              igi2_frame.tPos.vZ = igi2_frame.tRelativePos.vZ - igi2_frame.iSplite * igi2_frame.tViewVector_8;
            }
            else
            {
              igi2_frame.tPos.vZ = 0.0;
              v69 = 0.0;
              v70 = 0.0;
            }
            v71 = v70;
            igi2_frame.tPos.vX = v69;
            v72 = igi2_frame.tPos.vZ - igi2_frame.tRelativePos.vZ;
            vScale = igi2_frame.ptLayer->vScale;
            igi2_frame.tTexturePos.vY = (TransContext_tActiveTransContext.tPos.vY + 1073741824.0) * vScale;
            igi2_frame.tTexturePos.vY = igi2_frame.tTexturePos.vY - (double)(int)(__int64)igi2_frame.tTexturePos.vY;
            igi2_frame.atTexturePos[v62].vX = (TransContext_tActiveTransContext.tPos.vX + 1073741824.0) * vScale
                                 - (double)(int)(__int64)((TransContext_tActiveTransContext.tPos.vX + 1073741824.0)
                                                        * vScale)
                                 + igi2_frame.tPos.vX * igi2_frame.ptLayer->vScale
                                 + igi2_frame.ptLayer->vPosX;
            igi2_frame.atTexturePos[v62].vY = v71 * igi2_frame.ptLayer->vScale + igi2_frame.tTexturePos.vY + igi2_frame.ptLayer->vPosY;
            v74 = v72 * TransContext_tActiveTransContext.tMatrix.tZ.vZ
                + v71 * TransContext_tActiveTransContext.tMatrix.tZ.vY
                + igi2_frame.tPos.vX * TransContext_tActiveTransContext.tMatrix.tZ.vX;
            igi2_frame.avZPos[v62] = v74;
            if ( v74 <= 4096.0 )
              v74 = 4096.0;
            igi2_frame.iSplitf = v74;
            igi2_frame.avZPos[v62] = v74;
            v75 = ((double)Viewport_GetLogZ(igi2_frame.iSplitf) - 130.0) * DrawTerrainMesh_vFogDensity * 2000.0 * 0.00390625;
            if ( v75 >= 0.0 )
            {
              if ( v75 > 1.0 )
                v75 = 1.0;
            }
            else
            {
              v75 = 0.0;
            }
            igi2_frame.avFogValue[v62++] = v75;
          }
          while ( v62 < igi2_frame.nNumVerticesb );
        }
        v76 = *(float *)&igi2_frame.nNumVerticesb;
        if ( igi2_frame.nNumVerticesb > 2 )
        {
          isTextureLoaded = igi2_frame.ptLayer->isTextureLoaded;
          LODWORD(igi2_frame.tMatrix.tY.vY) = igi2_frame.atQVertex;
          v78 = 0;
          igi2_frame.tMatrix.tX.vY = 52076478464.0;
          igi2_frame.tMatrix.tX.vX = 0.0;
          igi2_frame.tMatrix.tX.vZ = IGI2_FLOAT_BITS(0xffffffffu);
          LODWORD(igi2_frame.tMatrix.tY.vX) = igi2_frame.nNumVerticesb;
          if ( isTextureLoaded )
            QVertex_ptActiveTexture = &igi2_frame.ptLayer->tTexInfo;
          else
            QVertex_ptActiveTexture = nullptr;
          if ( igi2_frame.nNumVerticesb >= 4 )
          {
            v79 = 3;
            p_vR = &igi2_frame.atQVertex[0].vR;
            do
            {
              *(p_vR - 1) = igi2_frame.ptLayer->vAlpha;
              v81 = igi2_frame.aiVertex[v78];
              *p_vR = igi2_frame.ptLayer->tColor.vX;
              p_vR[1] = igi2_frame.ptLayer->tColor.vY;
              p_vR[2] = igi2_frame.ptLayer->tColor.vZ;
              *(p_vR - 3) = igi2_frame.atTexturePos[v81].vX;
              *(p_vR - 2) = igi2_frame.atTexturePos[v81].vY;
              *(p_vR - 6) = igi2_frame.atScreenPos[v81].vX;
              v82 = igi2_frame.atScreenPos[v81].vY;
              v83 = igi2_frame.avZPos[v81];
              *(p_vR - 5) = v82;
              p_vR[8] = igi2_frame.ptLayer->vAlpha;
              p_vR[9] = igi2_frame.ptLayer->tColor.vX;
              p_vR[10] = igi2_frame.ptLayer->tColor.vY;
              p_vR[11] = igi2_frame.ptLayer->tColor.vZ;
              *(p_vR - 4) = v83;
              v84 = igi2_frame.aiVertex[v78 + 1];
              p_vR[6] = igi2_frame.atTexturePos[v84].vX;
              p_vR[7] = igi2_frame.atTexturePos[v84].vY;
              p_vR[3] = igi2_frame.atScreenPos[v84].vX;
              v85 = igi2_frame.atScreenPos[v84].vY;
              v86 = igi2_frame.avZPos[v84];
              p_vR[4] = v85;
              p_vR[17] = igi2_frame.ptLayer->vAlpha;
              p_vR[18] = igi2_frame.ptLayer->tColor.vX;
              p_vR[19] = igi2_frame.ptLayer->tColor.vY;
              p_vR[20] = igi2_frame.ptLayer->tColor.vZ;
              p_vR[5] = v86;
              v87 = igi2_frame.aiVertex[v78 + 2];
              p_vR[15] = igi2_frame.atTexturePos[v87].vX;
              p_vR[16] = igi2_frame.atTexturePos[v87].vY;
              p_vR[12] = igi2_frame.atScreenPos[v87].vX;
              v88 = igi2_frame.atScreenPos[v87].vY;
              v89 = igi2_frame.avZPos[v87];
              p_vR[13] = v88;
              p_vR[26] = igi2_frame.ptLayer->vAlpha;
              p_vR[27] = igi2_frame.ptLayer->tColor.vX;
              p_vR[28] = igi2_frame.ptLayer->tColor.vY;
              p_vR[29] = igi2_frame.ptLayer->tColor.vZ;
              p_vR[14] = v89;
              v90 = igi2_frame.aiVertex[v78 + 3];
              p_vR[24] = igi2_frame.atTexturePos[v90].vX;
              p_vR[25] = igi2_frame.atTexturePos[v90].vY;
              p_vR[21] = igi2_frame.atScreenPos[v90].vX;
              v91 = igi2_frame.atScreenPos[v90].vY;
              v92 = igi2_frame.avZPos[v90];
              p_vR[22] = v91;
              v76 = *(float *)&igi2_frame.nNumVerticesb;
              p_vR[23] = v92;
              v79 += 4;
              v78 += 4;
              p_vR += 36;
            }
            while ( v79 < igi2_frame.nNumVerticesb );
          }
          if ( v78 < SLODWORD(v76) )
          {
            v93 = &igi2_frame.atQVertex[v78].vR;
            do
            {
              v94 = igi2_frame.aiVertex[v78];
              *(v93 - 1) = igi2_frame.ptLayer->vAlpha;
              *v93 = igi2_frame.ptLayer->tColor.vX;
              v93[1] = igi2_frame.ptLayer->tColor.vY;
              v93[2] = igi2_frame.ptLayer->tColor.vZ;
              *(v93 - 3) = igi2_frame.atTexturePos[v94].vX;
              *(v93 - 2) = igi2_frame.atTexturePos[v94].vY;
              *(v93 - 6) = igi2_frame.atScreenPos[v94].vX;
              v95 = igi2_frame.atScreenPos[v94].vY;
              v96 = igi2_frame.avZPos[v94];
              *(v93 - 5) = v95;
              *(v93 - 4) = v96;
              ++v78;
              v93 += 9;
            }
            while ( v78 < SLODWORD(v76) );
          }
          RenderMode_tActiveRenderMode.apfRenderModeMethod[QVertex_eRegisterQVertexStripMethod](&igi2_frame.tMatrix);
        }
        if ( igi2_frame.ptLayer == (struct FlatWaterLayer_t *)QTask_GetLastChildOfType(ptQTask, FlatWaterLayer_eQTaskType)
          && SLODWORD(v76) > 2 )
        {
          LODWORD(igi2_frame.tMatrix.tY.vY) = igi2_frame.atQVertex;
          v97 = 0;
          igi2_frame.tMatrix.tX.vY = 51539607552.0;
          igi2_frame.tMatrix.tX.vX = 0.0;
          igi2_frame.tMatrix.tX.vZ = IGI2_FLOAT_BITS(0xffffffffu);
          igi2_frame.tMatrix.tY.vX = v76;
          QVertex_ptActiveTexture = nullptr;
          v98 = &igi2_frame.atQVertex[0].vR;
          do
          {
            v99 = igi2_frame.aiVertex[v97];
            *(v98 - 1) = igi2_frame.avFogValue[v99];
            *v98 = *(float *)&ptQTask[3].tQTaskChildren.ptTail;
            v98[1] = *(float *)&ptQTask[3].tQTaskRefList.ptHead;
            v98[2] = *(float *)&ptQTask[3].tQTaskRefList.ptMiddle;
            *(v98 - 3) = 0.0;
            *(v98 - 2) = 0.0;
            *(v98 - 6) = igi2_frame.atScreenPos[v99].vX;
            v100 = igi2_frame.atScreenPos[v99].vY;
            v101 = igi2_frame.avZPos[v99];
            *(v98 - 5) = v100;
            *(v98 - 4) = v101;
            ++v97;
            v98 += 9;
          }
          while ( v97 < SLODWORD(v76) );
          RenderMode_tActiveRenderMode.apfRenderModeMethod[QVertex_eRegisterQVertexStripMethod](&igi2_frame.tMatrix);
        }
        igi2_frame.ptLayer = (struct FlatWaterLayer_t *)QTask_GetNextSiblingOfType(&igi2_frame.ptLayer->tQTask, FlatWaterLayer_eQTaskType);
      }
      while ( igi2_frame.ptLayer );
    }
  }
}

// source: h/2/flatwater.c:789  [anchor-mhash]
void __cdecl FlatWater_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct World_s *v2; // edi
  struct World_s *v3; // ecx
  struct DynCubeObj_s *ptManualRedrawList; // edx
  struct DynCubeObj_s *ptPrev; // edx
  struct QTask_s *v6; // eax

  v2 = World_ptActiveWorld;
  v3 = World_ptActiveWorld;
  ptQTask[2].ptParent = (struct QTask_s *)World_ptActiveWorld;
  ptQTask[3].tQTaskChildren.ptMiddle = (struct QTask_s *)1062557008;
  ptQTask[3].tQTaskChildren.ptHead = (struct QTask_s *)1189765120;
  ptQTask[3].ptNext = nullptr;
  ptQTask[3].ptPrev = (struct QTask_s *)1075052544;
  ptQTask[3].tQTaskChildren.ptTail = nullptr;
  ptQTask[3].tQTaskRefList.ptHead = nullptr;
  ptQTask[3].tQTaskRefList.ptMiddle = nullptr;
  ptManualRedrawList = v3->ptManualRedrawList;
  if ( ptManualRedrawList )
  {
    ptManualRedrawList->ptPrev = (struct DynCubeObj_s *)ptQTask;
    v3->ptManualRedrawList->ptPrev->ptNext = v3->ptManualRedrawList;
    ptPrev = v3->ptManualRedrawList->ptPrev;
    v3->ptManualRedrawList = ptPrev;
    ptPrev->ptPrev = nullptr;
  }
  else
  {
    v3->ptManualRedrawList = (struct DynCubeObj_s *)ptQTask;
    ptQTask[2].tQTaskChildren.ptTail = nullptr;
    v3->ptManualRedrawList->ptPrev = nullptr;
  }
  v2->ptWater = &FlatWater_tWorldWater;
  v6 = ptQTask[3].ptPrev;
  LODWORD(FlatWater_tWorldWater.vWaterLevel) = ptQTask[3].ptNext;
  HIDWORD(FlatWater_tWorldWater.vWaterLevel) = v6;
}

// source: h/2/flatwater.c:822  [anchor-mhash]
void __cdecl FlatWater_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptMiddle; // ecx
  struct QTask_s *ptTail; // ecx

  World_ptActiveWorld->ptWater = nullptr;
  ptMiddle = ptQTask[2].tQTaskChildren.ptMiddle;
  if ( ptMiddle )
    ptMiddle[2].tQTaskChildren.ptTail = ptQTask[2].tQTaskChildren.ptTail;
  else
    ptQTask[2].ptParent[2].ptPrev = ptQTask[2].tQTaskChildren.ptTail;
  ptTail = ptQTask[2].tQTaskChildren.ptTail;
  if ( ptTail )
    ptTail[2].tQTaskChildren.ptMiddle = ptQTask[2].tQTaskChildren.ptMiddle;
}

// source: h/2/flatwater.c:843  [size]
void __cdecl FlatWater_RunHandler(struct QTask_s *ptQTask)
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

// source: h/2/flatwater.c:858  [size]
void __cdecl FlatWater_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = FlatWater_ptParameterList;
}

// source: h/2/flatwater.c:874  [anchor-mhash]
void __cdecl FlatWater_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  unsigned __int16 v2; // dx
  struct QTask_s *ptPrev; // ecx
  int v4; // edi
  struct QTask_s *FirstChildOfType; // eax
  double v6; // st7
  double v7; // st7
  double v8; // st7

  v2 = FlatWaterLayer_eQTaskType;
  ptPrev = ptQTask[3].ptPrev;
  v4 = 0;
  LODWORD(FlatWater_tWorldWater.vWaterLevel) = ptQTask[3].ptNext;
  HIDWORD(FlatWater_tWorldWater.vWaterLevel) = ptPrev;
  FlatWater_tWorldWater.tColor.vX = 0.0;
  FlatWater_tWorldWater.tColor.vY = 0.0;
  FlatWater_tWorldWater.tColor.vZ = 0.0;
  FirstChildOfType = QTask_GetFirstChildOfType(ptQTask, FlatWaterLayer_eQTaskType);
  if ( FirstChildOfType )
  {
    do
    {
      ++v4;
      FlatWater_tWorldWater.tColor.vX = FlatWater_tWorldWater.tColor.vX
                                      + *(float *)&FirstChildOfType[15].tQTaskRefList.ptMiddle;
      FlatWater_tWorldWater.tColor.vY = FlatWater_tWorldWater.tColor.vY
                                      + *(float *)&FirstChildOfType[15].tQTaskRefList.ptTail;
      FlatWater_tWorldWater.tColor.vZ = FlatWater_tWorldWater.tColor.vZ + *(float *)&FirstChildOfType[15].ptParent;
      FirstChildOfType = QTask_GetNextSiblingOfType(FirstChildOfType, v2);
    }
    while ( FirstChildOfType );
    if ( v4 > 0 )
    {
      v6 = 1.0 / (double)v4;
      FlatWater_tWorldWater.tColor.vX = FlatWater_tWorldWater.tColor.vX * v6;
      FlatWater_tWorldWater.tColor.vY = FlatWater_tWorldWater.tColor.vY * v6;
      FlatWater_tWorldWater.tColor.vZ = v6 * FlatWater_tWorldWater.tColor.vZ;
    }
  }
  if ( *(float *)&ptQTask[3].tQTaskChildren.ptTail >= 0.0 )
  {
    if ( *(float *)&ptQTask[3].tQTaskChildren.ptTail <= 1.0 )
      v7 = *(float *)&ptQTask[3].tQTaskChildren.ptTail;
    else
      v7 = 1.0;
  }
  else
  {
    v7 = 0.0;
  }
  *(float *)&ptQTask[3].tQTaskChildren.ptTail = v7;
  if ( *(float *)&ptQTask[3].tQTaskRefList.ptHead >= 0.0 )
  {
    if ( *(float *)&ptQTask[3].tQTaskRefList.ptHead <= 1.0 )
      v8 = *(float *)&ptQTask[3].tQTaskRefList.ptHead;
    else
      v8 = 1.0;
  }
  else
  {
    v8 = 0.0;
  }
  *(float *)&ptQTask[3].tQTaskRefList.ptHead = v8;
  if ( *(float *)&ptQTask[3].tQTaskRefList.ptMiddle >= 0.0 )
  {
    if ( *(float *)&ptQTask[3].tQTaskRefList.ptMiddle <= 1.0 )
      ptQTask[3].tQTaskRefList.ptMiddle = ptQTask[3].tQTaskRefList.ptMiddle;
    else
      ptQTask[3].tQTaskRefList.ptMiddle = (struct QReference_s *)1065353216;
  }
  else
  {
    ptQTask[3].tQTaskRefList.ptMiddle = nullptr;
  }
}

// source: h/2/flatwater.c:917  [size]
void __cdecl FlatWaterLayer_RunHandler(struct QTask_s *ptQTask)
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

// source: h/2/flatwater.c:954  [size]
void __cdecl FlatWaterLayer_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
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

// source: h/2/flatwater.c:980  [size]
void __cdecl FlatWaterLayer_DeleteHandler(struct QTask_s *ptQTask)
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

// source: h/2/flatwater.c:1001  [anchor-strings]
void __cdecl FlatWaterLayer_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  double v2; // st7
  double v3; // st7
  double v4; // st7
  char zTemp[512]; // [esp+8h] [ebp-200h] BYREF

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
  sprintf(zTemp, "LOCAL:%s%s", (char *)&g_zInitialValue, (char *)&ptQTask[8].tQTaskRefList.ptMiddle);
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

// source: h/2/flatwater.c:1052  [size]
void __cdecl FlatWaterLayer_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = FlatWaterLayer_ptParameterList;
}

// source: h/2/flatwater.c:1070  [anchor-hash]
void __cdecl FlatWater_Open()
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

  FlatWater_eQTaskType = QTask_NewQTaskType("FlatWater", 152, DynCubeObj_eQTaskType, 0, 0);
  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("FlatWaterLayer", 636, BaseQTaskType, 0, 0);
  v2 = FlatWater_eQTaskType;
  v3 = v1;
  FlatWaterLayer_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(FlatWater_eQTaskType, 0, FlatWater_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, 2, FlatWater_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v2, 5, FlatWater_EnterHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, 1, FlatWater_RunHandler);
  v4 = ParameterList_eGetParameterListQTaskEvent;
  QTask_LinkQTaskEventHandlerFn(
    v2,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))FlatWater_GetParameterListHandler);
  v5 = ParameterList_eUpdateInternalDataQTaskEvent;
  QTask_LinkQTaskEventHandlerFn(v2, ParameterList_eUpdateInternalDataQTaskEvent, FlatWater_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(v3, 0, FlatWaterLayer_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v3, 2, FlatWaterLayer_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v3,
    v4,
    (void (__cdecl *)(struct QTask_s *, void *))FlatWaterLayer_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v3, v5, FlatWaterLayer_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v3, 1, (void (__cdecl *)(struct QTask_s *))FlatWaterLayer_RunHandler);
  QTask_LinkQTaskEventHandlerFn(v2, DynCubeObj_eDynCubeObjRegisterQTaskEvent, nullptr);
  QTask_LinkQTaskEventHandlerFn(v2, DynCubeObj_eDynCubeObjRemoveQTaskEvent, nullptr);
  v6 = (struct ParameterList_s *)Mem_AllocFn(92, 4);
  v7 = Level_eParameterTypeReal32;
  v6->ptParameterListItem = (struct ParameterListItem_s *)&v6[1];
  v6->nParameters = 0;
  v6->nMaxParameters = 4;
  FlatWater_ptParameterList = v6;
  ParameterList_AddParameter(v6, 0x84u, v7, "Fog Amount", 7u, &unk_6B0080);
  ParameterList_AddParameter(FlatWater_ptParameterList, 0x78u, Level_eParameterTypeReal64, "Z Pos", 7u, nullptr);
  ParameterList_AddParameter(FlatWater_ptParameterList, 0x80u, Level_eParameterTypeReal32, "Distance", 7u, nullptr);
  ParameterList_AddParameter(FlatWater_ptParameterList, 0x88u, Level_eParameterTypeRGB, "Fog Color", 7u, nullptr);
  v8 = (struct ParameterList_s *)Mem_AllocFn(132, 4);
  v8->ptParameterListItem = (struct ParameterListItem_s *)&v8[1];
  v9 = Level_eParameterTypeString256;
  v8->nParameters = 0;
  v8->nMaxParameters = 6;
  FlatWaterLayer_ptParameterList = v8;
  ParameterList_AddParameter(v8, 0x158u, v9, "Texture File Name", 7u, nullptr);
  ParameterList_AddParameter(FlatWaterLayer_ptParameterList, 0x258u, Level_eParameterTypeReal32, "Scale", 7u, nullptr);
  ParameterList_AddParameter(
    FlatWaterLayer_ptParameterList,
    0x25Cu,
    Level_eParameterTypeReal32,
    "X Speed",
    7u,
    &unk_6B0090);
  ParameterList_AddParameter(
    FlatWaterLayer_ptParameterList,
    0x260u,
    Level_eParameterTypeReal32,
    "Y Speed",
    7u,
    &unk_6B0090);
  ParameterList_AddParameter(
    FlatWaterLayer_ptParameterList,
    0x26Cu,
    Level_eParameterTypeReal32,
    "Alpha",
    7u,
    &unk_6B0080);
  ParameterList_AddParameter(FlatWaterLayer_ptParameterList, 0x270u, Level_eParameterTypeRGB, "Color", 7u, nullptr);
}

// source: h/2/flatwater.c:1123  [anchor-hash]
void __cdecl FlatWater_Close()
{
  int v0; // esi
  int v1; // esi

  if ( FlatWaterLayer_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&FlatWaterLayer_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  if ( FlatWater_ptParameterList )
  {
    v1 = *(_DWORD *)((unsigned int)&FlatWater_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
  QTask_DeleteQTaskType(FlatWaterLayer_eQTaskType);
  QTask_DeleteQTaskType(FlatWater_eQTaskType);
}

// source: h/2/flatwater.c:1142  [size]
unsigned __int16 __cdecl FlatWater_GetQTaskType()
{
  return FlatWater_eQTaskType;
}

// source: h/2/flatwater.c:1155  [size]
unsigned __int16 __cdecl FlatWaterLayer_GetQTaskType()
{
  return FlatWaterLayer_eQTaskType;
}
