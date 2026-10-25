/* j/0/objects/glassshatter.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/objects/glassshatter.c:175  [anchor-strings]
void __cdecl GlassShatter_Sound(struct real64x3_t *ptPos)
{
  struct Game_s *v1; // eax
  unsigned int v2; // edx
  int v3; // edx
  unsigned int v4; // edx
  struct QTask_s *v5; // eax

  v1 = Game_ptGame;
  v2 = (Game_ptGame->tRunRandomState.anRandom[0] >> 7) ^ Game_ptGame->tRunRandomState.anRandom[2];
  Game_ptGame->tRunRandomState.anRandom[2] = v2;
  v3 = v2 ^ v1->tRunRandomState.anRandom[1];
  v1->tRunRandomState.anRandom[1] = v3;
  v4 = v3 + v1->tRunRandomState.anRandom[0];
  v1->tRunRandomState.anRandom[0] = v4;
  v5 = SoundSys_NewSoundFn(Level_ptDynamicQTask, (char *)(32 * (v4 % 3) + 7043064));
  if ( v5 )
    ((void (__cdecl *)(struct QTask_s *, struct real64x3_t *))QTask_aatQTaskFinalEvent[SoundSys_eSetPositionQTaskEvent][v5->eQTaskType].pfHandler)(
      v5,
      ptPos);
}

// source: j/0/objects/glassshatter.c:211  [anchor-mhash]
void __cdecl GlassShatter_CreateShards(struct real32x3_t *ptPos0, struct real32x3_t *ptPos1, struct real32x3_t *ptPos2)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vT2; };
    struct { float vT2a; };
    struct { float vT2b; };
    struct { float vT2c; };
    struct { float vT2d; };
    struct { float vT2e; };
    struct { float vT2f; };
    struct { char igi2_o7[4]; float tEdge0; };
    struct { char igi2_o8[8]; float tEdge0_4; };
    struct { char igi2_o9[12]; float tEdge0_8; };
    struct { char igi2_o10[16]; float vT1; };
    struct { char igi2_o11[16]; float vT1a; };
    struct { char igi2_o12[20]; float vT0; };
    struct { char igi2_o13[20]; float vT0a; };
    struct { char igi2_o14[24]; float tEdge1; };
    struct { char igi2_o15[28]; float tEdge1_4; };
    struct { char igi2_o16[32]; float tEdge1_8; };
    struct { char igi2_o17[36]; float vSquaredDistance2; };
    struct { char igi2_o18[40]; float vCompareSize1; };
    struct { char igi2_o19[40]; float vCompareSize1a; };
    struct { char igi2_o20[40]; float vCompareSize1b; };
    struct { char igi2_o21[44]; float vSquaredDistance1; };
    struct { char igi2_o22[44]; float vSquaredDistance1a; };
    struct { char igi2_o23[44]; float vSquaredDistance1b; };
    struct { char igi2_o24[44]; float vSquaredDistance1c; };
    struct { char igi2_o25[48]; float tNearestPos; };
    struct { char igi2_o26[48]; float tNearestPosa; };
    struct { char igi2_o27[48]; float tNearestPosb; };
    struct { char igi2_o28[48]; float tNearestPosc; };
    struct { char igi2_o29[48]; float tNearestPosd; };
    struct { char igi2_o30[52]; float tNearestPos_4; };
    struct { char igi2_o31[52]; float tNearestPos_4a; };
    struct { char igi2_o32[52]; float tNearestPos_4b; };
    struct { char igi2_o33[52]; float tNearestPos_4c; };
    struct { char igi2_o34[52]; float tNearestPos_4d; };
    struct { char igi2_o35[56]; float tNearestPos_8; };
    struct { char igi2_o36[56]; float tNearestPos_8a; };
    struct { char igi2_o37[60]; float vSquaredEdge0; };
    struct { char igi2_o38[64]; float vSquaredEdge1; };
    struct { char igi2_o39[68]; float vSquaredEdge2; };
    struct { char igi2_o40[72]; struct real32x3_t tEdge2; };
    struct { char igi2_o41[84]; float vCompareSize2; };
    struct { char igi2_o42[88]; float v139; };
    struct { char igi2_o43[92]; float v140; };
    struct { char igi2_o44[96]; __int64 v141; };
    struct { char igi2_o45[104]; struct real32x3_t tDelta; };
    struct { char igi2_o46[116]; float v143; };
    struct { char igi2_o47[120]; float v144; };
    struct { char igi2_o48[124]; float v145; };
    struct { char igi2_o49[128]; float v146; };
    struct { char igi2_o50[132]; float v147; };
    char igi2_extent[136];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v3; // st7
  double v4; // st6
  double v5; // st5
  double v6; // st7
  double v7; // st6
  double v8; // st5
  double v9; // st4
  double v10; // st3
  double v11; // st2
  double v12; // st3
  double v13; // st2
  char v14; // cl
  double v15; // st6
  double v16; // st4
  double v17; // st3
  double v18; // st5
  double v19; // st3
  double v20; // st2
  double v21; // st3
  double v22; // st2
  double v23; // st0
  double v24; // st4
  double v25; // st4
  double vY; // st6
  double vX; // st5
  double v28; // st6
  double vZ; // st5
  double v30; // st6
  double v31; // st5
  double v32; // st6
  double v33; // st6
  double v34; // st5
  double v35; // st4
  double v36; // st5
  double v37; // st6
  double v38; // st5
  double v39; // st4
  double v40; // st6
  double v41; // st6
  double v42; // st5
  double v43; // st4
  double v44; // st5
  unsigned int v45; // ecx
  long double v46; // st7
  long double v47; // st7
  long double v48; // st7
  double v49; // st4
  double v50; // st6
  double v51; // st2
  double v52; // st3
  double v53; // st4
  double v54; // st6
  double v55; // st2
  double v56; // st3
  double v57; // st4
  double v58; // st6
  double v59; // st6
  long double v60; // st7
  long double v61; // st7
  long double v62; // st7
  long double v63; // st7
  long double v64; // st7
  long double v65; // st7
  long double v66; // st7
  double v67; // st7
  double v68; // st7
  struct GlassShard_t *v69; // ebx
  double v70; // st6
  struct real32x3_t *p_tColor; // edi
  bool v72; // c0
  bool v73; // c3
  struct real32x3_t *v74; // eax
  double v75; // st7
  long double v76; // st7
  double RandomNumberReal32; // st7
  struct RandomPoly_t *v78; // ecx
  struct real32x3_t *p_tNormal; // edx
  long double v80; // st7
  int v81; // ecx
  double v82; // st7
  double v83; // st7
  struct GlassShard_t *v84; // ebx
  double v85; // st6
  struct real32x3_t *v86; // edi
  bool v87; // c0
  bool v88; // c3
  struct real32x3_t *v89; // ecx
  double v90; // st7
  long double v91; // st7
  double v92; // st7
  struct RandomPoly_t *v93; // ecx
  struct real32x3_t *v94; // edx
  long double v95; // st7
  int v96; // ecx
  struct real32x3_t struct_real32x3_t; // 0:^4C.12
  struct real32x3_t struct_real32x3_ta; // 0:^4C.12

  v3 = GlassShatter_tImpactPos.vZ - ptPos0->vZ;
  igi2_frame.vCompareSize1 = v3;
  igi2_frame.vT0 = 0.0;
  igi2_frame.vT1 = 0.0;
  v4 = GlassShatter_tImpactPos.vY - ptPos0->vY;
  igi2_frame.vT2 = 0.0;
  igi2_frame.vCompareSize2 = v4;
  v5 = GlassShatter_tImpactPos.vX - ptPos0->vX;
  igi2_frame.v140 = v5;
  v6 = v5 * v5 + v4 * v4 + v3 * v3;
  v7 = GlassShatter_tImpactPos.vZ - ptPos1->vZ;
  *(float *)&igi2_frame.v141 = v7;
  v8 = GlassShatter_tImpactPos.vY - ptPos1->vY;
  igi2_frame.v144 = v8;
  v9 = GlassShatter_tImpactPos.vX - ptPos1->vX;
  igi2_frame.v146 = v9;
  igi2_frame.vSquaredDistance1 = v9 * v9 + v8 * v8 + v7 * v7;
  v10 = GlassShatter_tImpactPos.vX - ptPos2->vX;
  v11 = GlassShatter_tImpactPos.vY - ptPos2->vY;
  v12 = v10 * v10 + v11 * v11;
  v13 = GlassShatter_tImpactPos.vZ - ptPos2->vZ;
  igi2_frame.vSquaredDistance2 = v12 + v13 * v13;
  v14 = 1;
  v15 = ptPos1->vZ - ptPos0->vZ;
  v16 = ptPos1->vY - ptPos0->vY;
  igi2_frame.v147 = v16;
  v17 = ptPos1->vX - ptPos0->vX;
  igi2_frame.v143 = v17;
  igi2_frame.vSquaredEdge0 = v15 * v15 + v17 * v17 + v16 * v16;
  v18 = ptPos2->vZ - ptPos1->vZ;
  v19 = ptPos2->vY - ptPos1->vY;
  igi2_frame.v139 = v19;
  v20 = ptPos2->vX - ptPos1->vX;
  igi2_frame.v145 = v20;
  igi2_frame.vSquaredEdge1 = v20 * v20 + v19 * v19 + v18 * v18;
  v21 = ptPos0->vY - ptPos2->vY;
  v22 = ptPos0->vX - ptPos2->vX;
  v23 = ptPos0->vZ - ptPos2->vZ;
  igi2_frame.vSquaredEdge2 = v22 * v22 + v21 * v21 + v23 * v23;
  igi2_frame.tEdge0 = ptPos2->vX - ptPos0->vX;
  v24 = ptPos2->vY - ptPos0->vY;
  igi2_frame.tEdge1 = igi2_frame.v143;
  igi2_frame.tEdge2.vX = igi2_frame.v145;
  igi2_frame.tEdge0_4 = v24;
  igi2_frame.tEdge1_4 = igi2_frame.v147;
  v25 = ptPos2->vZ - ptPos0->vZ;
  igi2_frame.tEdge2.vY = igi2_frame.v139;
  igi2_frame.tEdge0_8 = v25;
  igi2_frame.tEdge1_8 = v15;
  igi2_frame.tEdge2.vZ = v18;
  vY = GlassShatter_tImpactNormal.vY;
  if ( GlassShatter_tImpactNormal.vY < 0.0 )
    vY = -vY;
  vX = GlassShatter_tImpactNormal.vX;
  if ( GlassShatter_tImpactNormal.vX < 0.0 )
    vX = -vX;
  if ( vY <= vX )
    goto LABEL_11;
  v28 = GlassShatter_tImpactNormal.vY;
  if ( GlassShatter_tImpactNormal.vY < 0.0 )
    v28 = -v28;
  vZ = GlassShatter_tImpactNormal.vZ;
  if ( GlassShatter_tImpactNormal.vZ < 0.0 )
    vZ = -vZ;
  if ( v28 > vZ )
  {
    v37 = igi2_frame.tEdge1_8 * igi2_frame.tEdge0 - igi2_frame.v143 * igi2_frame.tEdge0_8;
    if ( v37 == 0.0 )
      v14 = 0;
    v33 = (igi2_frame.vCompareSize1 * igi2_frame.tEdge0 - igi2_frame.v140 * igi2_frame.tEdge0_8) / v37;
    if ( v33 < 0.0 || v33 > 1.0 )
      v14 = 0;
    v38 = igi2_frame.tEdge0;
    if ( igi2_frame.tEdge0 < 0.0 )
      v38 = -v38;
    v39 = igi2_frame.tEdge0_8;
    if ( igi2_frame.tEdge0_8 < 0.0 )
      v39 = -v39;
    if ( v38 > v39 )
    {
      v36 = (igi2_frame.v140 - igi2_frame.v143 * v33) / igi2_frame.tEdge0;
      goto LABEL_41;
    }
  }
  else
  {
LABEL_11:
    v30 = GlassShatter_tImpactNormal.vZ;
    if ( GlassShatter_tImpactNormal.vZ < 0.0 )
      v30 = -v30;
    v31 = GlassShatter_tImpactNormal.vX;
    if ( GlassShatter_tImpactNormal.vX < 0.0 )
      v31 = -v31;
    if ( v30 > v31 )
    {
      v40 = igi2_frame.v147 * igi2_frame.tEdge0 - igi2_frame.v143 * igi2_frame.tEdge0_4;
      if ( v40 == 0.0 )
        v14 = 0;
      v41 = (igi2_frame.vCompareSize2 * igi2_frame.tEdge0 - igi2_frame.v140 * igi2_frame.tEdge0_4) / v40;
      if ( v41 < 0.0 || v41 > 1.0 )
        v14 = 0;
      v42 = igi2_frame.tEdge0;
      if ( igi2_frame.tEdge0 < 0.0 )
        v42 = -v42;
      v43 = igi2_frame.tEdge0_4;
      if ( igi2_frame.tEdge0_4 < 0.0 )
        v43 = -v43;
      if ( v42 <= v43 )
      {
        if ( igi2_frame.tEdge0_4 == 0.0 )
          v14 = 0;
        v44 = (igi2_frame.vCompareSize2 - igi2_frame.v147 * v41) / igi2_frame.tEdge0_4;
      }
      else
      {
        v44 = (igi2_frame.v140 - igi2_frame.v143 * v41) / igi2_frame.tEdge0;
      }
      if ( v44 < 0.0 || v44 + v41 > 1.0 )
        goto LABEL_70;
      goto LABEL_60;
    }
    v32 = igi2_frame.tEdge1_8 * igi2_frame.tEdge0_4 - igi2_frame.v147 * igi2_frame.tEdge0_8;
    if ( v32 == 0.0 )
      v14 = 0;
    v33 = (igi2_frame.vCompareSize1 * igi2_frame.tEdge0_4 - igi2_frame.vCompareSize2 * igi2_frame.tEdge0_8) / v32;
    if ( v33 < 0.0 || v33 > 1.0 )
      v14 = 0;
    v34 = igi2_frame.tEdge0_4;
    if ( igi2_frame.tEdge0_4 < 0.0 )
      v34 = -v34;
    v35 = igi2_frame.tEdge0_8;
    if ( igi2_frame.tEdge0_8 < 0.0 )
      v35 = -v35;
    if ( v34 > v35 )
    {
      v36 = (igi2_frame.vCompareSize2 - igi2_frame.v147 * v33) / igi2_frame.tEdge0_4;
      goto LABEL_41;
    }
  }
  if ( igi2_frame.tEdge0_8 == 0.0 )
    v14 = 0;
  v36 = (igi2_frame.vCompareSize1 - igi2_frame.tEdge1_8 * v33) / igi2_frame.tEdge0_8;
LABEL_41:
  if ( v36 < 0.0 || v36 + v33 > 1.0 )
  {
LABEL_70:
    if ( igi2_frame.vSquaredDistance2 >= v6 )
      igi2_frame.vT0a = v6;
    else
      igi2_frame.vT0a = igi2_frame.vSquaredDistance2;
    if ( igi2_frame.vSquaredDistance1 >= v6 )
      igi2_frame.vT1a = v6;
    else
      igi2_frame.vT1a = igi2_frame.vSquaredDistance1;
    if ( igi2_frame.vSquaredDistance2 >= (double)igi2_frame.vSquaredDistance1 )
      v48 = igi2_frame.vSquaredDistance1;
    else
      v48 = igi2_frame.vSquaredDistance2;
    igi2_frame.tDelta.vZ = igi2_frame.vCompareSize1;
    igi2_frame.v139 = sqrt(igi2_frame.v140 * igi2_frame.v140 + igi2_frame.vCompareSize2 * igi2_frame.vCompareSize2 + igi2_frame.vCompareSize1 * igi2_frame.vCompareSize1);
    igi2_frame.vSquaredDistance1a = igi2_frame.v139;
    igi2_frame.vT2d = 1.0 / igi2_frame.v139;
    igi2_frame.tDelta.vX = igi2_frame.v140 * igi2_frame.vT2d;
    igi2_frame.v139 = sqrt(igi2_frame.tEdge0 * igi2_frame.tEdge0 + igi2_frame.tEdge0_4 * igi2_frame.tEdge0_4 + igi2_frame.tEdge0_8 * igi2_frame.tEdge0_8);
    v49 = 1.0 / igi2_frame.v139;
    igi2_frame.tEdge0 = igi2_frame.tEdge0 * v49;
    igi2_frame.tEdge0_4 = igi2_frame.tEdge0_4 * v49;
    igi2_frame.tEdge0_8 = v49 * igi2_frame.tEdge0_8;
    v50 = (igi2_frame.vCompareSize1 * igi2_frame.vT2d * igi2_frame.tEdge0_8 + igi2_frame.vCompareSize2 * igi2_frame.vT2d * igi2_frame.tEdge0_4 + igi2_frame.tDelta.vX * igi2_frame.tEdge0) * igi2_frame.vSquaredDistance1a;
    igi2_frame.vT2a = v50;
    if ( v50 > 0.0 && igi2_frame.vT2a < (double)igi2_frame.v139 )
    {
      igi2_frame.tEdge0 = igi2_frame.vT2a * igi2_frame.tEdge0;
      igi2_frame.tEdge0_4 = igi2_frame.vT2a * igi2_frame.tEdge0_4;
      igi2_frame.tEdge0_8 = igi2_frame.vT2a * igi2_frame.tEdge0_8;
      igi2_frame.tNearestPosb = igi2_frame.tEdge0 + ptPos0->vX;
      igi2_frame.tNearestPos_4b = igi2_frame.tEdge0_4 + ptPos0->vY;
      v51 = igi2_frame.tEdge0_8 + ptPos0->vZ - GlassShatter_tImpactPos.vZ;
      v52 = (igi2_frame.tNearestPosb - GlassShatter_tImpactPos.vX) * (igi2_frame.tNearestPosb - GlassShatter_tImpactPos.vX)
          + (igi2_frame.tNearestPos_4b - GlassShatter_tImpactPos.vY) * (igi2_frame.tNearestPos_4b - GlassShatter_tImpactPos.vY)
          + v51 * v51;
      if ( igi2_frame.vT0a >= v52 )
        igi2_frame.vT0a = v52;
    }
    igi2_frame.vT0 = sqrt(igi2_frame.vT0a) * 0.00019531250291038305;
    if ( igi2_frame.vT0 >= 0.0 )
    {
      if ( igi2_frame.vT0 > 1.0 )
        igi2_frame.vT0 = 1.0;
    }
    else
    {
      igi2_frame.vT0 = 0.0;
    }
    igi2_frame.tDelta.vZ = igi2_frame.vCompareSize1;
    igi2_frame.v139 = sqrt(igi2_frame.v140 * igi2_frame.v140 + igi2_frame.vCompareSize2 * igi2_frame.vCompareSize2 + igi2_frame.vCompareSize1 * igi2_frame.vCompareSize1);
    igi2_frame.vSquaredDistance1b = igi2_frame.v139;
    igi2_frame.vT2e = 1.0 / igi2_frame.v139;
    igi2_frame.tDelta.vX = igi2_frame.v140 * igi2_frame.vT2e;
    igi2_frame.v139 = sqrt(igi2_frame.v143 * igi2_frame.v143 + igi2_frame.v147 * igi2_frame.v147 + igi2_frame.tEdge1_8 * igi2_frame.tEdge1_8);
    v53 = 1.0 / igi2_frame.v139;
    igi2_frame.tEdge1 = igi2_frame.v143 * v53;
    igi2_frame.tEdge1_4 = igi2_frame.v147 * v53;
    igi2_frame.tEdge1_8 = v53 * igi2_frame.tEdge1_8;
    v54 = (igi2_frame.vCompareSize1 * igi2_frame.vT2e * igi2_frame.tEdge1_8 + igi2_frame.vCompareSize2 * igi2_frame.vT2e * igi2_frame.tEdge1_4 + igi2_frame.tDelta.vX * igi2_frame.tEdge1) * igi2_frame.vSquaredDistance1b;
    igi2_frame.vT2b = v54;
    if ( v54 > 0.0 && igi2_frame.vT2b < (double)igi2_frame.v139 )
    {
      igi2_frame.tEdge1 = igi2_frame.vT2b * igi2_frame.tEdge1;
      igi2_frame.tEdge1_4 = igi2_frame.vT2b * igi2_frame.tEdge1_4;
      igi2_frame.tEdge1_8 = igi2_frame.vT2b * igi2_frame.tEdge1_8;
      igi2_frame.tNearestPosc = igi2_frame.tEdge1 + ptPos0->vX;
      igi2_frame.tNearestPos_4c = igi2_frame.tEdge1_4 + ptPos0->vY;
      v55 = igi2_frame.tEdge1_8 + ptPos0->vZ - GlassShatter_tImpactPos.vZ;
      v56 = (igi2_frame.tNearestPosc - GlassShatter_tImpactPos.vX) * (igi2_frame.tNearestPosc - GlassShatter_tImpactPos.vX)
          + (igi2_frame.tNearestPos_4c - GlassShatter_tImpactPos.vY) * (igi2_frame.tNearestPos_4c - GlassShatter_tImpactPos.vY)
          + v55 * v55;
      if ( igi2_frame.vT1a >= v56 )
        igi2_frame.vT1a = v56;
    }
    igi2_frame.vT1 = sqrt(igi2_frame.vT1a) * 0.00019531250291038305;
    if ( igi2_frame.vT1 >= 0.0 )
    {
      if ( igi2_frame.vT1 > 1.0 )
        igi2_frame.vT1 = 1.0;
    }
    else
    {
      igi2_frame.vT1 = 0.0;
    }
    igi2_frame.tDelta.vZ = *(float *)&igi2_frame.v141;
    *(float *)&igi2_frame.v141 = sqrt(igi2_frame.v146 * igi2_frame.v146 + igi2_frame.v144 * igi2_frame.v144 + *(float *)&igi2_frame.v141 * *(float *)&igi2_frame.v141);
    igi2_frame.vSquaredDistance1c = *(float *)&igi2_frame.v141;
    igi2_frame.vT2f = 1.0 / *(float *)&igi2_frame.v141;
    igi2_frame.tDelta.vX = igi2_frame.v146 * igi2_frame.vT2f;
    *(float *)&igi2_frame.v141 = sqrt(igi2_frame.tEdge2.vX * igi2_frame.tEdge2.vX + igi2_frame.tEdge2.vY * igi2_frame.tEdge2.vY + igi2_frame.tEdge2.vZ * igi2_frame.tEdge2.vZ);
    v57 = 1.0 / *(float *)&igi2_frame.v141;
    igi2_frame.tEdge2.vX = igi2_frame.tEdge2.vX * v57;
    igi2_frame.tEdge2.vY = igi2_frame.tEdge2.vY * v57;
    igi2_frame.tEdge2.vZ = v57 * igi2_frame.tEdge2.vZ;
    v58 = (igi2_frame.tDelta.vZ * igi2_frame.vT2f * igi2_frame.tEdge2.vZ + igi2_frame.v144 * igi2_frame.vT2f * igi2_frame.tEdge2.vY + igi2_frame.tDelta.vX * igi2_frame.tEdge2.vX) * igi2_frame.vSquaredDistance1c;
    igi2_frame.vT2c = v58;
    if ( v58 > 0.0 && igi2_frame.vT2c < (double)*(float *)&igi2_frame.v141 )
    {
      igi2_frame.tEdge2.vZ = igi2_frame.vT2c * igi2_frame.tEdge2.vZ;
      igi2_frame.tNearestPosd = igi2_frame.vT2c * igi2_frame.tEdge2.vX + ptPos1->vX;
      igi2_frame.tNearestPos_4d = igi2_frame.vT2c * igi2_frame.tEdge2.vY + ptPos1->vY;
      v59 = igi2_frame.tEdge2.vZ + ptPos1->vZ - GlassShatter_tImpactPos.vZ;
      igi2_frame.vCompareSize1a = (igi2_frame.tNearestPosd - GlassShatter_tImpactPos.vX) * (igi2_frame.tNearestPosd - GlassShatter_tImpactPos.vX)
                     + (igi2_frame.tNearestPos_4d - GlassShatter_tImpactPos.vY) * (igi2_frame.tNearestPos_4d - GlassShatter_tImpactPos.vY)
                     + v59 * v59;
      if ( v48 >= igi2_frame.vCompareSize1a )
        v48 = igi2_frame.vCompareSize1a;
    }
    igi2_frame.vT2 = sqrt(v48) * 0.00019531250291038305;
    if ( igi2_frame.vT2 >= 0.0 )
    {
      if ( igi2_frame.vT2 > 1.0 )
        igi2_frame.vT2 = 1.0;
    }
    else
    {
      igi2_frame.vT2 = 0.0;
    }
    goto LABEL_61;
  }
LABEL_60:
  if ( !v14 )
    goto LABEL_70;
LABEL_61:
  igi2_frame.vCompareSize2 = igi2_frame.vT2 * 4505.60009765625 + 409.6000061035156;
  if ( igi2_frame.vSquaredEdge0 <= (igi2_frame.vT0 * 4505.60009765625 + 409.6000061035156) * (igi2_frame.vT0 * 4505.60009765625 + 409.6000061035156) )
  {
    igi2_frame.vCompareSize1b = igi2_frame.vT1 * 4505.60009765625 + 409.6000061035156;
    if ( igi2_frame.vCompareSize1b * igi2_frame.vCompareSize1b >= igi2_frame.vSquaredEdge1 && igi2_frame.vCompareSize2 * igi2_frame.vCompareSize2 >= igi2_frame.vSquaredEdge2 )
      goto LABEL_127;
  }
  v45 = (GlassShatter_tRandomState.anRandom[0] >> 7) ^ GlassShatter_tRandomState.anRandom[2];
  GlassShatter_tRandomState.anRandom[0] += v45 ^ GlassShatter_tRandomState.anRandom[1];
  GlassShatter_tRandomState.anRandom[2] = v45;
  GlassShatter_tRandomState.anRandom[1] ^= v45;
  if ( igi2_frame.vSquaredEdge0 >= (double)igi2_frame.vSquaredEdge1 && igi2_frame.vSquaredEdge0 >= (double)igi2_frame.vSquaredEdge2 )
  {
    if ( igi2_frame.vSquaredEdge2 >= (double)igi2_frame.vSquaredEdge1 )
    {
      v60 = 1.0 - sqrt(igi2_frame.vSquaredEdge1) / sqrt(igi2_frame.vSquaredEdge0);
      if ( v60 <= 0.5 )
        v60 = 0.5;
      v47 = v60 - Random_GetRandomNumberReal32(&GlassShatter_tRandomState) * 0.10000000149011612;
    }
    else
    {
      v46 = sqrt(igi2_frame.vSquaredEdge2) / sqrt(igi2_frame.vSquaredEdge0);
      if ( v46 >= 0.5 )
        v46 = 0.5;
      v47 = v46 + Random_GetRandomNumberReal32(&GlassShatter_tRandomState) * 0.10000000149011612;
    }
    igi2_frame.tEdge2.vX = (ptPos1->vX - ptPos0->vX) * v47 + ptPos0->vX;
    igi2_frame.tEdge2.vY = (ptPos1->vY - ptPos0->vY) * v47 + ptPos0->vY;
    igi2_frame.tEdge2.vZ = (ptPos1->vZ - ptPos0->vZ) * v47 + ptPos0->vZ;
    GlassShatter_CreateShards(ptPos1, ptPos2, &igi2_frame.tEdge2);
    GlassShatter_CreateShards(&igi2_frame.tEdge2, ptPos2, ptPos0);
    return;
  }
  if ( igi2_frame.vSquaredEdge1 >= (double)igi2_frame.vSquaredEdge0 && igi2_frame.vSquaredEdge1 >= (double)igi2_frame.vSquaredEdge2 )
  {
    if ( igi2_frame.vSquaredEdge0 >= (double)igi2_frame.vSquaredEdge2 )
    {
      v63 = 1.0 - sqrt(igi2_frame.vSquaredEdge2) / sqrt(igi2_frame.vSquaredEdge1);
      if ( v63 <= 0.5 )
        v63 = 0.5;
      v62 = v63 - Random_GetRandomNumberReal32(&GlassShatter_tRandomState) * 0.10000000149011612;
    }
    else
    {
      v61 = sqrt(igi2_frame.vSquaredEdge0) / sqrt(igi2_frame.vSquaredEdge1);
      if ( v61 >= 0.5 )
        v61 = 0.5;
      v62 = v61 + Random_GetRandomNumberReal32(&GlassShatter_tRandomState) * 0.10000000149011612;
    }
    igi2_frame.tEdge2.vX = (ptPos2->vX - ptPos1->vX) * v62 + ptPos1->vX;
    igi2_frame.tEdge2.vY = (ptPos2->vY - ptPos1->vY) * v62 + ptPos1->vY;
    igi2_frame.tEdge2.vZ = (ptPos2->vZ - ptPos1->vZ) * v62 + ptPos1->vZ;
    GlassShatter_CreateShards(ptPos2, ptPos0, &igi2_frame.tEdge2);
    GlassShatter_CreateShards(&igi2_frame.tEdge2, ptPos0, ptPos1);
    return;
  }
  if ( igi2_frame.vSquaredEdge2 < (double)igi2_frame.vSquaredEdge0 || igi2_frame.vSquaredEdge2 < (double)igi2_frame.vSquaredEdge1 )
  {
LABEL_127:
    if ( GlassShatter_eMode )
    {
      if ( GlassShatter_eMode == GLASSSHATTER_MODE_EXPLOSION )
      {
        v67 = igi2_frame.vT1 >= (double)igi2_frame.vT2 ? igi2_frame.vT2 : igi2_frame.vT1;
        if ( igi2_frame.vT0 >= v67 )
          v68 = igi2_frame.vT1 >= (double)igi2_frame.vT2 ? igi2_frame.vT2 : igi2_frame.vT1;
        else
          v68 = igi2_frame.vT0;
        if ( GlassShatter_ptActiveGlassShatter->nShards < 1000 )
        {
          v69 = GlassShatter_ptShard;
          igi2_frame.tNearestPos = (ptPos0->vX + ptPos1->vX + ptPos2->vX) * 0.3333333432674408;
          igi2_frame.tNearestPos_4 = (ptPos1->vY + ptPos0->vY + ptPos2->vY) * 0.3333333432674408;
          v70 = ptPos1->vZ + ptPos0->vZ + ptPos2->vZ;
          GlassShatter_ptShard->tPos0 = *ptPos0;
          v69->tPos1 = *ptPos1;
          v69->tPos2 = *ptPos2;
          igi2_frame.tNearestPos_8 = v70 * 0.3333333432674408;
          p_tColor = &v69->tColor;
          igi2_frame.v141 = (__int64)((Random_GetRandomNumberReal32(&GlassShatter_tRandomState) + 1.0 - v68) * 0.5 * 30.0);
          v69->iRandomMatrix = igi2_frame.v141;
          v69->tCenterPos.vX = igi2_frame.tNearestPos;
          v72 = GlassShatter_vHitVelocity < 0.0;
          v73 = GlassShatter_vHitVelocity == 0.0;
          v69->tCenterPos.vY = igi2_frame.tNearestPos_4;
          v74 = GlassShatter_ptColor;
          v69->tCenterPos.vZ = igi2_frame.tNearestPos_8;
          v69->tOriginalColor = *v74;
          v69->tColor = v69->tOriginalColor;
          if ( v72 || v73 )
          {
            v69->tVelocity.vX = 0.0;
            v69->tVelocity.vY = 0.0;
            v69->tVelocity.vZ = 0.0;
          }
          else
          {
            v69->tVelocity.vX = igi2_frame.tNearestPos - GlassShatter_tSpreadFromPos.vX;
            v69->tVelocity.vY = igi2_frame.tNearestPos_4 - GlassShatter_tSpreadFromPos.vY;
            v75 = igi2_frame.tNearestPos_8 - GlassShatter_tSpreadFromPos.vZ;
            v69->tVelocity.vZ = v75;
            v76 = GlassShatter_vHitVelocity
                / sqrt(v75 * v75 + v69->tVelocity.vX * v69->tVelocity.vX + v69->tVelocity.vY * v69->tVelocity.vY);
            v69->tVelocity.vX = v69->tVelocity.vX * v76;
            v69->tVelocity.vY = v69->tVelocity.vY * v76;
            v69->tVelocity.vZ = v69->tVelocity.vZ * v76;
          }
          v69->tVelocity.vX = (Random_GetRandomNumberReal32(&GlassShatter_tRandomState) * 4096.0 - 2048.0) * 0.03333333507180214
                            + v69->tVelocity.vX;
          v69->tVelocity.vY = (Random_GetRandomNumberReal32(&GlassShatter_tRandomState) * 4096.0 - 2048.0) * 0.03333333507180214
                            + v69->tVelocity.vY;
          RandomNumberReal32 = Random_GetRandomNumberReal32(&GlassShatter_tRandomState);
          v78 = GlassShatter_ptPoly;
          p_tNormal = &GlassShatter_ptPoly->tNormal;
          v69->tVelocity.vZ = (RandomNumberReal32 * 4096.0 - 2048.0) * 0.03333333507180214 + v69->tVelocity.vZ;
          v69->isEnabled = 1;
          v78->aptPos[0] = &v69->tPos0;
          v78->aptPos[1] = &v69->tPos1;
          v78->aptPos[2] = &v69->tPos2;
          v78->aptColor[0] = p_tColor;
          v78->aptColor[1] = p_tColor;
          v78->aptColor[2] = p_tColor;
          v78->ptTexInfo = nullptr;
          v78->ptPalInfo = nullptr;
          struct_real32x3_t.vX = igi2_frame.tEdge1_8 * igi2_frame.tEdge0_4 - igi2_frame.tEdge1_4 * igi2_frame.tEdge0_8;
          struct_real32x3_t.vY = -(igi2_frame.tEdge1_8 * igi2_frame.tEdge0 - igi2_frame.tEdge1 * igi2_frame.tEdge0_8);
          struct_real32x3_t.vZ = igi2_frame.tEdge1_4 * igi2_frame.tEdge0 - igi2_frame.tEdge1 * igi2_frame.tEdge0_4;
          *p_tNormal = struct_real32x3_t;
          if ( p_tNormal->vX != 0.0 || v78->tNormal.vY != 0.0 || v78->tNormal.vZ != 0.0 )
          {
            v80 = 1.0
                / sqrt(
                    p_tNormal->vX * p_tNormal->vX
                  + v78->tNormal.vY * v78->tNormal.vY
                  + v78->tNormal.vZ * v78->tNormal.vZ);
            p_tNormal->vX = p_tNormal->vX * v80;
            v78->tNormal.vY = v78->tNormal.vY * v80;
            v78->tNormal.vZ = v78->tNormal.vZ * v80;
          }
          GlassShatter_ptPoly = v78 + 1;
          v81 = GlassShatter_ptActiveGlassShatter->nShards + 1;
          GlassShatter_ptShard = v69 + 1;
          GlassShatter_ptActiveGlassShatter->nShards = v81;
        }
      }
    }
    else
    {
      if ( igi2_frame.vT1 >= (double)igi2_frame.vT2 )
        v82 = igi2_frame.vT2;
      else
        v82 = igi2_frame.vT1;
      if ( igi2_frame.vT0 >= v82 )
      {
        if ( igi2_frame.vT1 >= (double)igi2_frame.vT2 )
          v83 = igi2_frame.vT2;
        else
          v83 = igi2_frame.vT1;
      }
      else
      {
        v83 = igi2_frame.vT0;
      }
      if ( GlassShatter_ptActiveGlassShatter->nShards < 1000 )
      {
        v84 = GlassShatter_ptShard;
        igi2_frame.tNearestPosa = (ptPos0->vX + ptPos1->vX + ptPos2->vX) * 0.3333333432674408;
        igi2_frame.tNearestPos_4a = (ptPos1->vY + ptPos0->vY + ptPos2->vY) * 0.3333333432674408;
        v85 = ptPos1->vZ + ptPos0->vZ + ptPos2->vZ;
        GlassShatter_ptShard->tPos0 = *ptPos0;
        v84->tPos1 = *ptPos1;
        v84->tPos2 = *ptPos2;
        igi2_frame.tNearestPos_8a = v85 * 0.3333333432674408;
        v86 = &v84->tColor;
        igi2_frame.v141 = (__int64)((Random_GetRandomNumberReal32(&GlassShatter_tRandomState) + 1.0 - v83) * 0.5 * 30.0);
        v84->iRandomMatrix = igi2_frame.v141;
        v84->tCenterPos.vX = igi2_frame.tNearestPosa;
        v87 = GlassShatter_vHitVelocity < 0.0;
        v88 = GlassShatter_vHitVelocity == 0.0;
        v84->tCenterPos.vY = igi2_frame.tNearestPos_4a;
        v89 = GlassShatter_ptColor;
        v84->tCenterPos.vZ = igi2_frame.tNearestPos_8a;
        v84->tOriginalColor = *v89;
        v84->tColor = v84->tOriginalColor;
        if ( v87 || v88 )
        {
          v84->tVelocity.vX = 0.0;
          v84->tVelocity.vY = 0.0;
          v84->tVelocity.vZ = 0.0;
        }
        else
        {
          v84->tVelocity.vX = igi2_frame.tNearestPosa - GlassShatter_tSpreadFromPos.vX;
          v84->tVelocity.vY = igi2_frame.tNearestPos_4a - GlassShatter_tSpreadFromPos.vY;
          v90 = igi2_frame.tNearestPos_8a - GlassShatter_tSpreadFromPos.vZ;
          v84->tVelocity.vZ = v90;
          v91 = GlassShatter_vHitVelocity
              / sqrt(v90 * v90 + v84->tVelocity.vX * v84->tVelocity.vX + v84->tVelocity.vY * v84->tVelocity.vY);
          v84->tVelocity.vX = v84->tVelocity.vX * v91;
          v84->tVelocity.vY = v84->tVelocity.vY * v91;
          v84->tVelocity.vZ = v84->tVelocity.vZ * v91;
        }
        v84->tVelocity.vX = (Random_GetRandomNumberReal32(&GlassShatter_tRandomState) * 4096.0 - 2048.0) * 0.03333333507180214
                          + v84->tVelocity.vX;
        v84->tVelocity.vY = (Random_GetRandomNumberReal32(&GlassShatter_tRandomState) * 4096.0 - 2048.0) * 0.03333333507180214
                          + v84->tVelocity.vY;
        v92 = Random_GetRandomNumberReal32(&GlassShatter_tRandomState);
        v93 = GlassShatter_ptPoly;
        v94 = &GlassShatter_ptPoly->tNormal;
        v84->tVelocity.vZ = (v92 * 4096.0 - 2048.0) * 0.03333333507180214 + v84->tVelocity.vZ;
        v84->isEnabled = 1;
        v93->aptPos[0] = &v84->tPos0;
        v93->aptPos[1] = &v84->tPos1;
        v93->aptPos[2] = &v84->tPos2;
        v93->aptColor[0] = v86;
        v93->aptColor[1] = v86;
        v93->aptColor[2] = v86;
        v93->ptTexInfo = nullptr;
        v93->ptPalInfo = nullptr;
        struct_real32x3_ta.vX = igi2_frame.tEdge1_8 * igi2_frame.tEdge0_4 - igi2_frame.tEdge1_4 * igi2_frame.tEdge0_8;
        struct_real32x3_ta.vY = -(igi2_frame.tEdge1_8 * igi2_frame.tEdge0 - igi2_frame.tEdge1 * igi2_frame.tEdge0_8);
        struct_real32x3_ta.vZ = igi2_frame.tEdge1_4 * igi2_frame.tEdge0 - igi2_frame.tEdge1 * igi2_frame.tEdge0_4;
        *v94 = struct_real32x3_ta;
        if ( v94->vX != 0.0 || v93->tNormal.vY != 0.0 || v93->tNormal.vZ != 0.0 )
        {
          v95 = 1.0 / sqrt(v94->vX * v94->vX + v93->tNormal.vY * v93->tNormal.vY + v93->tNormal.vZ * v93->tNormal.vZ);
          v94->vX = v94->vX * v95;
          v93->tNormal.vY = v93->tNormal.vY * v95;
          v93->tNormal.vZ = v93->tNormal.vZ * v95;
        }
        GlassShatter_ptPoly = v93 + 1;
        v96 = GlassShatter_ptActiveGlassShatter->nShards + 1;
        GlassShatter_ptShard = v84 + 1;
        GlassShatter_ptActiveGlassShatter->nShards = v96;
      }
    }
  }
  else
  {
    if ( igi2_frame.vSquaredEdge1 >= (double)igi2_frame.vSquaredEdge0 )
    {
      v66 = 1.0 - sqrt(igi2_frame.vSquaredEdge0) / sqrt(igi2_frame.vSquaredEdge2);
      if ( v66 <= 0.5 )
        v66 = 0.5;
      v65 = v66 - Random_GetRandomNumberReal32(&GlassShatter_tRandomState) * 0.10000000149011612;
    }
    else
    {
      v64 = sqrt(igi2_frame.vSquaredEdge1) / sqrt(igi2_frame.vSquaredEdge2);
      if ( v64 >= 0.5 )
        v64 = 0.5;
      v65 = v64 + Random_GetRandomNumberReal32(&GlassShatter_tRandomState) * 0.10000000149011612;
    }
    igi2_frame.tEdge2.vX = (ptPos0->vX - ptPos2->vX) * v65 + ptPos2->vX;
    igi2_frame.tEdge2.vY = (ptPos0->vY - ptPos2->vY) * v65 + ptPos2->vY;
    igi2_frame.tEdge2.vZ = (ptPos0->vZ - ptPos2->vZ) * v65 + ptPos2->vZ;
    GlassShatter_CreateShards(ptPos0, ptPos1, &igi2_frame.tEdge2);
    GlassShatter_CreateShards(&igi2_frame.tEdge2, ptPos1, ptPos2);
  }
}

// source: j/0/objects/glassshatter.c:696  [anchor-mhash]
void __cdecl GlassShatter_RunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptPrev; // edx
  int v3; // ecx
  int v4; // edx
  float v5; // edi
  float *v6; // eax
  int v7; // edi
  float *p_ptMiddle; // eax
  float *v9; // edx
  double v10; // st7
  double v11; // st6
  double v12; // st5
  double v13; // st7
  double v14; // st6
  char *v15; // ebx
  double v16; // st5
  double v17; // st4
  double v18; // st5
  int v19; // ebp
  int v20; // ecx
  double v21; // st5
  double v22; // st5
  float v24; // [esp+8h] [ebp-5Ch]
  float v25; // [esp+Ch] [ebp-58h]
  float tTempPos1; // [esp+10h] [ebp-54h]
  float tTempPos1_4; // [esp+14h] [ebp-50h]
  float tTempPos1_8; // [esp+18h] [ebp-4Ch]
  float tTempPos2; // [esp+1Ch] [ebp-48h]
  float tTempPos2_4; // [esp+20h] [ebp-44h]
  float tTempPos2_8; // [esp+24h] [ebp-40h]
  float Real32x3_Rotate_tTemp; // [esp+28h] [ebp-3Ch]
  float Real32x3_Rotate_tTemp_4; // [esp+2Ch] [ebp-38h]
  float Real32x3_Rotate_tTemp_8; // [esp+30h] [ebp-34h]
  float v35; // [esp+34h] [ebp-30h]
  float v36; // [esp+38h] [ebp-2Ch]
  float v37; // [esp+3Ch] [ebp-28h]
  float Real32x3_RotateInverse_tTemp; // [esp+40h] [ebp-24h]
  float Real32x3_RotateInverse_tTemp_4; // [esp+44h] [ebp-20h]
  float Real32x3_RotateInverse_tTemp_8; // [esp+48h] [ebp-1Ch]
  float v41; // [esp+4Ch] [ebp-18h]
  float v42; // [esp+50h] [ebp-14h]
  float v43; // [esp+5Ch] [ebp-8h]
  float v44; // [esp+60h] [ebp-4h]
  float ptQTaska = *(float *)&ptQTask; // [esp+68h] [ebp+4h] ARGSLOT

  ptPrev = ptQTask[4405].ptNext[4].ptPrev;
  v3 = 0;
  Real32x3_RotateInverse_tTemp = (*(float *)&ptQTask[4].ptPrev + *(float *)&ptQTask[3].ptParent) * 0.0
                               - *(float *)&ptQTask[4].tQTaskChildren.ptTail * 44.600887298583984;
  Real32x3_RotateInverse_tTemp_4 = (*(float *)&ptQTask[4].tQTaskChildren.ptHead + *(float *)&ptQTask[3].eQTaskType)
                                 * 0.0
                                 - *(float *)&ptQTask[4].tQTaskRefList.ptHead * 44.600887298583984;
  Real32x3_RotateInverse_tTemp_8 = (*(float *)&ptQTask[4].tQTaskChildren.ptMiddle + *(float *)&ptQTask[4].ptNext) * 0.0
                                 - *(float *)&ptQTask[4].tQTaskRefList.ptMiddle * 44.600887298583984;
  flt_79EEB48 = (double)*(int *)&ptQTask[4].eQTaskType * 0.03333333507180214;
  if ( (int)ptPrev > 0 )
  {
    v4 = 0;
    do
    {
      v5 = flt_79EEB48;
      v6 = (float *)(v4 + *(_DWORD *)&ptQTask[4405].ptNext[2].eQTaskType);
      v6[12] = flt_79EEB48;
      v6[13] = v5;
      v6[14] = v5;
      ++v3;
      v4 += 80;
    }
    while ( v3 < (int)ptQTask[4405].ptNext[4].ptPrev );
  }
  v7 = 0;
  if ( (int)ptQTask[4].ptParent > 0 )
  {
    p_ptMiddle = (float *)&ptQTask[5].tQTaskRefList.ptMiddle;
    v9 = (float *)&ptQTask[2406].tQTaskRefList.ptMiddle;
    do
    {
      if ( *((_DWORD *)p_ptMiddle + 17) )
      {
        v10 = p_ptMiddle[3] - *p_ptMiddle;
        v11 = p_ptMiddle[4] - p_ptMiddle[1];
        v12 = p_ptMiddle[5] - p_ptMiddle[2];
        tTempPos1 = p_ptMiddle[6] - *p_ptMiddle;
        tTempPos1_4 = p_ptMiddle[7] - p_ptMiddle[1];
        tTempPos1_8 = p_ptMiddle[8] - p_ptMiddle[2];
        tTempPos2 = p_ptMiddle[9] - *p_ptMiddle;
        tTempPos2_4 = p_ptMiddle[10] - p_ptMiddle[1];
        tTempPos2_8 = p_ptMiddle[11] - p_ptMiddle[2];
        v41 = v10 * GlassShatter_atRandomMatrix[*((_DWORD *)p_ptMiddle + 12)].tX.vX
            + v12 * GlassShatter_atRandomMatrix[*((_DWORD *)p_ptMiddle + 12)].tX.vZ
            + v11 * GlassShatter_atRandomMatrix[*((_DWORD *)p_ptMiddle + 12)].tX.vY;
        v42 = v10 * GlassShatter_atRandomMatrix[*((_DWORD *)p_ptMiddle + 12)].tY.vX
            + v12 * GlassShatter_atRandomMatrix[*((_DWORD *)p_ptMiddle + 12)].tY.vZ
            + v11 * GlassShatter_atRandomMatrix[*((_DWORD *)p_ptMiddle + 12)].tY.vY;
        v13 = v12 * GlassShatter_atRandomMatrix[*((_DWORD *)p_ptMiddle + 12)].tZ.vZ
            + v11 * GlassShatter_atRandomMatrix[*((_DWORD *)p_ptMiddle + 12)].tZ.vY
            + v10 * GlassShatter_atRandomMatrix[*((_DWORD *)p_ptMiddle + 12)].tZ.vX;
        v14 = tTempPos1 * GlassShatter_atRandomMatrix[*((_DWORD *)p_ptMiddle + 12)].tX.vX
            + tTempPos1_8 * GlassShatter_atRandomMatrix[*((_DWORD *)p_ptMiddle + 12)].tX.vZ
            + tTempPos1_4 * GlassShatter_atRandomMatrix[*((_DWORD *)p_ptMiddle + 12)].tX.vY;
        v43 = tTempPos1 * GlassShatter_atRandomMatrix[*((_DWORD *)p_ptMiddle + 12)].tY.vX
            + tTempPos1_8 * GlassShatter_atRandomMatrix[*((_DWORD *)p_ptMiddle + 12)].tY.vZ
            + tTempPos1_4 * GlassShatter_atRandomMatrix[*((_DWORD *)p_ptMiddle + 12)].tY.vY;
        v44 = tTempPos1_8 * GlassShatter_atRandomMatrix[*((_DWORD *)p_ptMiddle + 12)].tZ.vZ
            + tTempPos1_4 * GlassShatter_atRandomMatrix[*((_DWORD *)p_ptMiddle + 12)].tZ.vY
            + tTempPos1 * GlassShatter_atRandomMatrix[*((_DWORD *)p_ptMiddle + 12)].tZ.vX;
        v15 = (char *)(p_ptMiddle - 3);
        v35 = tTempPos2 * GlassShatter_atRandomMatrix[*((_DWORD *)p_ptMiddle + 12)].tX.vX
            + tTempPos2_8 * GlassShatter_atRandomMatrix[*((_DWORD *)p_ptMiddle + 12)].tX.vZ
            + tTempPos2_4 * GlassShatter_atRandomMatrix[*((_DWORD *)p_ptMiddle + 12)].tX.vY;
        v36 = tTempPos2 * GlassShatter_atRandomMatrix[*((_DWORD *)p_ptMiddle + 12)].tY.vX
            + tTempPos2_8 * GlassShatter_atRandomMatrix[*((_DWORD *)p_ptMiddle + 12)].tY.vZ
            + tTempPos2_4 * GlassShatter_atRandomMatrix[*((_DWORD *)p_ptMiddle + 12)].tY.vY;
        v37 = tTempPos2_8 * GlassShatter_atRandomMatrix[*((_DWORD *)p_ptMiddle + 12)].tZ.vZ
            + tTempPos2_4 * GlassShatter_atRandomMatrix[*((_DWORD *)p_ptMiddle + 12)].tZ.vY
            + tTempPos2 * GlassShatter_atRandomMatrix[*((_DWORD *)p_ptMiddle + 12)].tZ.vX;
        Real32x3_Rotate_tTemp = *v9 * GlassShatter_atRandomMatrix[*((_DWORD *)p_ptMiddle + 12)].tX.vY
                              + v9[1] * GlassShatter_atRandomMatrix[*((_DWORD *)p_ptMiddle + 12)].tX.vZ
                              + GlassShatter_atRandomMatrix[*((_DWORD *)p_ptMiddle + 12)].tX.vX * *(v9 - 1);
        Real32x3_Rotate_tTemp_4 = v9[1] * GlassShatter_atRandomMatrix[*((_DWORD *)p_ptMiddle + 12)].tY.vZ
                                + *v9 * GlassShatter_atRandomMatrix[*((_DWORD *)p_ptMiddle + 12)].tY.vY
                                + GlassShatter_atRandomMatrix[*((_DWORD *)p_ptMiddle + 12)].tY.vX * *(v9 - 1);
        v16 = GlassShatter_atRandomMatrix[*((_DWORD *)p_ptMiddle + 12)].tZ.vZ * v9[1]
            + *v9 * GlassShatter_atRandomMatrix[*((_DWORD *)p_ptMiddle + 12)].tZ.vY;
        v17 = *(v9 - 1) * GlassShatter_atRandomMatrix[*((_DWORD *)p_ptMiddle + 12)].tZ.vX;
        *(v9 - 1) = Real32x3_Rotate_tTemp;
        *v9 = Real32x3_Rotate_tTemp_4;
        Real32x3_Rotate_tTemp_8 = v16 + v17;
        v9[1] = Real32x3_Rotate_tTemp_8;
        v18 = p_ptMiddle[13] + *p_ptMiddle;
        *(float *)v15 = *(p_ptMiddle - 6);
        v19 = *((_DWORD *)p_ptMiddle - 5);
        ptQTaska = v18;
        v20 = *((_DWORD *)p_ptMiddle - 4);
        *p_ptMiddle = v18;
        v21 = p_ptMiddle[14];
        *((_DWORD *)v15 + 1) = v19;
        v22 = v21 + p_ptMiddle[1];
        *((_DWORD *)v15 + 2) = v20;
        v24 = v22;
        p_ptMiddle[1] = v22;
        v25 = p_ptMiddle[15] + p_ptMiddle[2];
        p_ptMiddle[2] = v25;
        p_ptMiddle[3] = ptQTaska + v41;
        p_ptMiddle[4] = v24 + v42;
        p_ptMiddle[5] = v25 + v13;
        p_ptMiddle[6] = ptQTaska + v14;
        p_ptMiddle[7] = v24 + v43;
        p_ptMiddle[8] = v25 + v44;
        p_ptMiddle[9] = ptQTaska + v35;
        p_ptMiddle[10] = v24 + v36;
        p_ptMiddle[11] = v25 + v37;
        p_ptMiddle[13] = Real32x3_RotateInverse_tTemp + p_ptMiddle[13];
        p_ptMiddle[14] = Real32x3_RotateInverse_tTemp_4 + p_ptMiddle[14];
        p_ptMiddle[15] = Real32x3_RotateInverse_tTemp_8 + p_ptMiddle[15];
      }
      ++v7;
      p_ptMiddle += 24;
      v9 += 20;
    }
    while ( v7 < (int)ptQTask[4].ptParent );
  }
  if ( (*(_DWORD *)&ptQTask[4].eQTaskType)-- == 1 )
    QTask_Delete(ptQTask);
}

// source: j/0/objects/glassshatter.c:874  [size]
void __cdecl GlassShatter_DeleteHandler(struct QTask_s *ptQTask)
{
  QTask_Delete(ptQTask[4405].ptNext);
}

// source: j/0/objects/glassshatter.c:892  [anchor-strings]
void __cdecl GlassShatter_Open()
{
  unsigned int v0; // esi
  int v1; // ebx
  int v2; // edi
  struct real32x9_t *v3; // eax
  int v4; // edi
  int v5; // ebx
  unsigned int v6; // esi
  double v7; // st7
  int v8; // edi
  int v9; // ebx
  unsigned int v10; // esi
  double v11; // st6
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v13; // si
  float ptDest; // [esp+0h] [ebp-28h]
  float vAlpha; // [esp+4h] [ebp-24h]
  float vBeta; // [esp+8h] [ebp-20h]
  float v17; // [esp+1Ch] [ebp-Ch]
  int iCount; // [esp+20h] [ebp-8h]

  v0 = -923067897;
  v1 = 971667286;
  v2 = 2146516173;
  iCount = 0;
  v3 = GlassShatter_atRandomMatrix;
  do
  {
    v4 = (v0 >> 7) ^ v2;
    v5 = v4 ^ v1;
    v6 = v5 + v0;
    v7 = (double)(unsigned __int16)v6 * 0.0000152587890625;
    v8 = (v6 >> 7) ^ v4;
    v9 = v8 ^ v5;
    v10 = v9 + v6;
    v11 = (double)(unsigned __int16)v10 * 0.0000152587890625;
    v2 = (v10 >> 7) ^ v8;
    v1 = v2 ^ v9;
    v0 = v1 + v10;
    v17 = (float)iCount;
    vBeta = ((double)(unsigned __int16)v0 * 0.0000152587890625 * 40.0 - 20.0) * v17 * 0.0011111111380159855;
    vAlpha = (v11 * 40.0 - 20.0) * v17 * 0.0011111111380159855;
    ptDest = (v7 * 40.0 - 20.0) * v17 * 0.0011111111380159855;
    v3 = Real32x9_Create(v3, ptDest, vAlpha, vBeta) + 1;
    ++iCount;
  }
  while ( (int)v3 < 127855416 );
  GlassShatter_tRandomState.anRandom[0] = v0;
  GlassShatter_tRandomState.anRandom[1] = v1;
  GlassShatter_tRandomState.anRandom[2] = v2;
  BaseQTaskType = QTask_GetBaseQTaskType();
  v13 = QTask_NewQTaskType(&stru_68C1E0.zFilename[56], 176208, BaseQTaskType, 0, 0);
  GlassShatter_eQTaskType = v13;
  QTask_LinkQTaskEventHandlerNoContextFn(v13, 1, GlassShatter_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v13, 2, GlassShatter_DeleteHandler);
}

// source: j/0/objects/glassshatter.c:930  [size]
void __cdecl GlassShatter_Close()
{
  QTask_DeleteQTaskType(GlassShatter_eQTaskType);
}

// source: j/0/objects/glassshatter.c:949  [anchor-mhash]
void __cdecl GlassShatter_NewLocalImpact(
        struct LODVirModel_s *ptModel,
        struct real32x3_t *ptHitVelocity,
        struct real64x3_t *ptObjectPos,
        struct real32x9_t *ptObjectOrientation,
        struct QIntersection_s *ptIntersection)
{
  struct Mesh3D_Mesh_t *ptMesh; // esi
  struct QTask_s *v6; // eax
  struct MultiMesh_Mesh_t *pxCollisionMesh; // esi
  struct GlassShatter_t *v8; // ebp
  bool v9; // zf
  struct real32x3_t *v10; // edx
  long double v11; // st7
  long double v12; // st6
  long double v13; // st5
  long double v14; // st4
  long double v15; // rt1
  long double v16; // st4
  long double v17; // st5
  struct real64x3_t *v18; // ecx
  double v20; // st7
  double v21; // st7
  double v22; // st7
  double v23; // st6
  double v24; // st7
  double v25; // st6
  struct MultiMesh_Face_t *ptFace; // eax
  struct MultiMesh_Vertex_t *ptVertex; // edi
  int v28; // esi
  unsigned __int16 *v29; // eax
  struct real32x3_t *p_tPos; // ecx
  struct real32x3_t *v31; // esi
  struct real32x3_t *v32; // edi
  double v33; // st7
  double v34; // st6
  double v35; // st5
  double v36; // st4
  bool v37; // cc
  struct MultiMesh_Mesh_t *ptCollMesh; // [esp+10h] [ebp-24h]
  int iFace; // [esp+14h] [ebp-20h]
  float Real32x3_RotateInverse_tTemp; // [esp+18h] [ebp-1Ch]
  float Real32x3_RotateInverse_tTempa; // [esp+18h] [ebp-1Ch]
  float Real32x3_RotateInverse_tTemp_4; // [esp+1Ch] [ebp-18h]
  float Real32x3_RotateInverse_tTemp_4a; // [esp+1Ch] [ebp-18h]
  float Real32x3_RotateInverse_tTemp_8; // [esp+20h] [ebp-14h]
  float tTemp_; // [esp+24h] [ebp-10h]
  float tTemp__4; // [esp+28h] [ebp-Ch]
  struct LODVirModel_s *ptModela = *(struct LODVirModel_s * *)&ptModel; // [esp+38h] [ebp+4h] ARGSLOT
  struct real32x3_t struct_real32x3_t; // 0:^44.12

  ptMesh = ptModel->aptVirModel[0]->ptModel->ptMesh;
  v6 = QTask_NewFn(Level_ptDynamicQTask, GlassShatter_eQTaskType, nullptr);
  pxCollisionMesh = (struct MultiMesh_Mesh_t *)ptMesh->pxCollisionMesh;
  v8 = (struct GlassShatter_t *)v6;
  v9 = pxCollisionMesh->nNumFaces == 0;
  GlassShatter_eMode = GLASSSHATTER_MODE_LOCAL_IMPACT;
  ptCollMesh = pxCollisionMesh;
  if ( !v9 )
  {
    v10 = ptHitVelocity;
    *(struct real32x3_t *)&v6[2].eQTaskType = *ptHitVelocity;
    v11 = 10.0
        / sqrt(
            *(float *)&v6[2].eQTaskType * *(float *)&v6[2].eQTaskType
          + *(float *)&v6[3].ptNext * *(float *)&v6[3].ptNext
          + *(float *)&v6[3].ptPrev * *(float *)&v6[3].ptPrev);
    v12 = *(float *)&v6[2].eQTaskType * v11;
    *(float *)&v6[2].eQTaskType = v12;
    v13 = *(float *)&v6[3].ptNext * v11;
    *(float *)&v6[3].ptNext = v13;
    v14 = *(float *)&v6[3].ptPrev * v11;
    *(float *)&v6[3].ptPrev = v14;
    Real32x3_RotateInverse_tTemp = v14 * ptObjectOrientation->tZ.vX
                                 + v13 * ptObjectOrientation->tY.vX
                                 + v12 * ptObjectOrientation->tX.vX;
    Real32x3_RotateInverse_tTemp_4 = v14 * ptObjectOrientation->tZ.vY
                                   + v13 * ptObjectOrientation->tY.vY
                                   + v12 * ptObjectOrientation->tX.vY;
    v15 = v12 * ptObjectOrientation->tX.vZ;
    v16 = v14 * ptObjectOrientation->tZ.vZ;
    v17 = v13 * ptObjectOrientation->tY.vZ;
    *(float *)&v6[2].eQTaskType = Real32x3_RotateInverse_tTemp;
    *(float *)&v6[3].ptNext = Real32x3_RotateInverse_tTemp_4;
    Real32x3_RotateInverse_tTemp_8 = v15 + v16 + v17;
    *(float *)&v6[3].ptPrev = Real32x3_RotateInverse_tTemp_8;
    qmemcpy(&v6[3].tQTaskChildren, ptObjectPos, 0x18u);
    qmemcpy(&v6[3].ptParent, ptObjectOrientation, sizeof(struct QTask_s));
    v18 = ptObjectPos;
    v6[2].ptParent = (struct QTask_s *)ptModel;
    v8->nTicks = 30;
    GlassShatter_tSpreadFromPos.vX = ptIntersection->tPos.vX - ptObjectPos->vX;
    GlassShatter_tSpreadFromPos.vY = ptIntersection->tPos.vY - ptObjectPos->vY;
    v20 = ptIntersection->tPos.vZ - ptObjectPos->vZ;
    GlassShatter_tSpreadFromPos.vZ = v20;
    struct_real32x3_t.vX = v20 * ptObjectOrientation->tZ.vX
                         + GlassShatter_tSpreadFromPos.vY * ptObjectOrientation->tY.vX
                         + GlassShatter_tSpreadFromPos.vX * ptObjectOrientation->tX.vX;
    struct_real32x3_t.vY = GlassShatter_tSpreadFromPos.vX * ptObjectOrientation->tX.vY
                         + GlassShatter_tSpreadFromPos.vZ * ptObjectOrientation->tZ.vY
                         + GlassShatter_tSpreadFromPos.vY * ptObjectOrientation->tY.vY;
    struct_real32x3_t.vZ = GlassShatter_tSpreadFromPos.vX * ptObjectOrientation->tX.vZ
                         + GlassShatter_tSpreadFromPos.vZ * ptObjectOrientation->tZ.vZ
                         + GlassShatter_tSpreadFromPos.vY * ptObjectOrientation->tY.vZ;
    GlassShatter_tSpreadFromPos = struct_real32x3_t;
    GlassShatter_tImpactPos.vX = ptIntersection->tPos.vX - ptObjectPos->vX;
    GlassShatter_tImpactPos.vY = ptIntersection->tPos.vY - ptObjectPos->vY;
    v21 = ptIntersection->tPos.vZ - ptObjectPos->vZ;
    GlassShatter_tImpactPos.vZ = v21;
    struct_real32x3_t.vX = v21 * ptObjectOrientation->tZ.vX
                         + GlassShatter_tImpactPos.vY * ptObjectOrientation->tY.vX
                         + GlassShatter_tImpactPos.vX * ptObjectOrientation->tX.vX;
    struct_real32x3_t.vY = GlassShatter_tImpactPos.vX * ptObjectOrientation->tX.vY
                         + GlassShatter_tImpactPos.vZ * ptObjectOrientation->tZ.vY
                         + GlassShatter_tImpactPos.vY * ptObjectOrientation->tY.vY;
    v22 = GlassShatter_tImpactPos.vX * ptObjectOrientation->tX.vZ;
    v23 = GlassShatter_tImpactPos.vZ * ptObjectOrientation->tZ.vZ;
    GlassShatter_vHitVelocity = 10.0;
    GlassShatter_ptColor = (struct real32x3_t *)&unk_6B7858;
    GlassShatter_ptActiveGlassShatter = v8;
    iFace = 0;
    struct_real32x3_t.vZ = v22 + v23 + GlassShatter_tImpactPos.vY * ptObjectOrientation->tY.vZ;
    GlassShatter_tImpactPos = struct_real32x3_t;
    struct_real32x3_t.vX = ptIntersection->tNormal.vX * ptObjectOrientation->tX.vX
                         + ptObjectOrientation->tZ.vX * ptIntersection->tNormal.vZ
                         + ptObjectOrientation->tY.vX * ptIntersection->tNormal.vY;
    struct_real32x3_t.vY = ptIntersection->tNormal.vX * ptObjectOrientation->tX.vY
                         + ptIntersection->tNormal.vZ * ptObjectOrientation->tZ.vY
                         + ptIntersection->tNormal.vY * ptObjectOrientation->tY.vY;
    v24 = ptObjectOrientation->tZ.vZ * ptIntersection->tNormal.vZ
        + ptObjectOrientation->tY.vZ * ptIntersection->tNormal.vY;
    v25 = ptObjectOrientation->tX.vZ * ptIntersection->tNormal.vX;
    GlassShatter_tImpactNormal.vX = struct_real32x3_t.vX;
    GlassShatter_tImpactNormal.vY = struct_real32x3_t.vY;
    v8->nShards = 0;
    struct_real32x3_t.vZ = v24 + v25;
    GlassShatter_tImpactNormal.vZ = struct_real32x3_t.vZ;
    GlassShatter_ptPoly = v8->atPoly;
    GlassShatter_ptShard = v8->atShard;
    if ( pxCollisionMesh->nNumFaces > 0 )
    {
      ptModela = nullptr;
      while ( 1 )
      {
        ptFace = pxCollisionMesh->ptFace;
        ptVertex = pxCollisionMesh->ptVertex;
        v28 = *(unsigned __int16 *)((char *)ptModela->aptVirModel + (_DWORD)ptFace + 2);
        v29 = (unsigned __int16 *)((char *)ptFace->aiVertex + (_DWORD)ptModela);
        p_tPos = &ptVertex[*v29].tPos;
        v31 = &ptVertex[v28].tPos;
        v32 = &ptVertex[v29[2]].tPos;
        v33 = v32->vX - p_tPos->vX;
        v34 = v32->vY - p_tPos->vY;
        v35 = v32->vZ - p_tPos->vZ;
        Real32x3_RotateInverse_tTempa = v31->vX - p_tPos->vX;
        Real32x3_RotateInverse_tTemp_4a = v31->vY - p_tPos->vY;
        v36 = v31->vZ - p_tPos->vZ;
        tTemp_ = v36 * v34 - Real32x3_RotateInverse_tTemp_4a * v35;
        tTemp__4 = -(v36 * v33 - Real32x3_RotateInverse_tTempa * v35);
        if ( tTemp_ * v10->vX
           + (v33 * Real32x3_RotateInverse_tTemp_4a - Real32x3_RotateInverse_tTempa * v34) * v10->vZ
           + tTemp__4 * v10->vY < 0.0 )
        {
          GlassShatter_CreateShards(p_tPos, v31, v32);
          v10 = ptHitVelocity;
        }
        v37 = ++iFace < ptCollMesh->nNumFaces;
        ptModela = (struct LODVirModel_s *)((char *)ptModela + 12);
        if ( !v37 )
          break;
        pxCollisionMesh = ptCollMesh;
      }
      v18 = ptObjectPos;
    }
    v8->ptPolyListDynCubeObj = PolyListDynCubeObj_New(
                                 Game_ptGame->ptWorld,
                                 nullptr,
                                 v18,
                                 ptObjectOrientation,
                                 v8->atPoly,
                                 v8->nShards,
                                 0,
                                 1,
                                 0,
                                 1,
                                 nullptr,
                                 nullptr);
    GlassShatter_Sound(ptObjectPos);
  }
}

// source: j/0/objects/glassshatter.c:1069  [anchor-mhash]
void __cdecl GlassShatter_NewExplosion(
        struct LODVirModel_s *ptModel,
        struct real32x9_t *ptObjectOrientation,
        struct real64x3_t *ptObjectPos,
        struct real64x3_t *ptHitPos,
        float vRange,
        float vMaxSpeed)
{
  struct Mesh3D_Mesh_t *ptMesh; // esi
  struct GlassShatter_t *v7; // eax
  struct MultiMesh_Mesh_t *pxCollisionMesh; // esi
  struct GlassShatter_t *v9; // ebp
  bool v10; // zf
  struct real64x3_t *v11; // edx
  double v12; // st7
  double v13; // st7
  double v14; // st7
  double v15; // st6
  double v16; // st5
  double v17; // st4
  double v18; // rt0
  double v19; // st4
  double v20; // rt2
  double v21; // st4
  double v22; // st5
  double v23; // st6
  double v24; // st5
  double v25; // st6
  double v26; // st5
  struct MultiMesh_Mesh_t *v27; // ecx
  struct MultiMesh_Face_t *ptFace; // eax
  struct MultiMesh_Vertex_t *ptVertex; // edi
  int v30; // ecx
  char *v31; // eax
  int v32; // esi
  int v33; // eax
  struct real32x3_t *p_tPos; // ecx
  struct real32x3_t *v35; // esi
  double v36; // st7
  struct real32x3_t *v37; // edi
  double v38; // st6
  double v39; // st5
  double v40; // st4
  bool v41; // cc
  float vLen; // [esp+10h] [ebp-20h]
  int vLena; // [esp+10h] [ebp-20h]
  struct MultiMesh_Mesh_t *ptCollMesh; // [esp+14h] [ebp-1Ch]
  float Real32x3_RotateInverse_tTemp; // [esp+18h] [ebp-18h]
  float Real32x3_RotateInverse_tTempa; // [esp+18h] [ebp-18h]
  float Real32x3_RotateInverse_tTemp_4; // [esp+1Ch] [ebp-14h]
  float Real32x3_RotateInverse_tTemp_4a; // [esp+1Ch] [ebp-14h]
  float Real32x3_RotateInverse_tTemp_8; // [esp+20h] [ebp-10h]
  float tTemp_; // [esp+24h] [ebp-Ch]
  float tTemp__4; // [esp+28h] [ebp-8h]
  struct LODVirModel_s *ptModela = *(struct LODVirModel_s * *)&ptModel; // [esp+34h] [ebp+4h] ARGSLOT
  struct real32x3_t struct_real32x3_t; // 0:^44.12

  ptMesh = ptModel->aptVirModel[0]->ptModel->ptMesh;
  v7 = (struct GlassShatter_t *)QTask_NewFn(Level_ptDynamicQTask, GlassShatter_eQTaskType, nullptr);
  pxCollisionMesh = (struct MultiMesh_Mesh_t *)ptMesh->pxCollisionMesh;
  v9 = v7;
  v10 = pxCollisionMesh->nNumFaces == 0;
  GlassShatter_eMode = GLASSSHATTER_MODE_EXPLOSION;
  ptCollMesh = pxCollisionMesh;
  if ( !v10 )
  {
    v11 = ptObjectPos;
    v7->tHitVelocity.vX = ptObjectPos->vX - ptHitPos->vX;
    v7->tHitVelocity.vY = ptObjectPos->vY - ptHitPos->vY;
    v12 = ptObjectPos->vZ - ptHitPos->vZ;
    v7->tHitVelocity.vZ = v12;
    vLen = sqrt(v7->tHitVelocity.vX * v7->tHitVelocity.vX + v7->tHitVelocity.vY * v7->tHitVelocity.vY + v12 * v12);
    if ( vLen >= 0.0 )
    {
      if ( vLen <= 1.0 )
        v13 = vLen;
      else
        v13 = 1.0;
    }
    else
    {
      v13 = 0.0;
    }
    v14 = v13 * vMaxSpeed;
    v15 = v14 / vLen;
    v16 = v15 * v7->tHitVelocity.vX;
    v7->tHitVelocity.vX = v16;
    v17 = v15 * v7->tHitVelocity.vY;
    v7->tHitVelocity.vY = v17;
    v18 = v17;
    v19 = v15 * v7->tHitVelocity.vZ;
    v7->tHitVelocity.vZ = v19;
    Real32x3_RotateInverse_tTemp = v16 * ptObjectOrientation->tX.vX
                                 + v19 * ptObjectOrientation->tZ.vX
                                 + v18 * ptObjectOrientation->tY.vX;
    Real32x3_RotateInverse_tTemp_4 = v19 * ptObjectOrientation->tZ.vY
                                   + v18 * ptObjectOrientation->tY.vY
                                   + v16 * ptObjectOrientation->tX.vY;
    v20 = v16 * ptObjectOrientation->tX.vZ;
    v21 = v19 * ptObjectOrientation->tZ.vZ;
    v22 = v18 * ptObjectOrientation->tY.vZ;
    v7->tHitVelocity.vX = Real32x3_RotateInverse_tTemp;
    v7->tHitVelocity.vY = Real32x3_RotateInverse_tTemp_4;
    Real32x3_RotateInverse_tTemp_8 = v20 + v21 + v22;
    v7->tHitVelocity.vZ = Real32x3_RotateInverse_tTemp_8;
    qmemcpy(&v7->tPos, ptObjectPos, sizeof(v7->tPos));
    qmemcpy(&v7->tOrientation, ptObjectOrientation, sizeof(v7->tOrientation));
    v7->ptModel = ptModel;
    v7->nTicks = 30;
    GlassShatter_tSpreadFromPos.vX = ptHitPos->vX - ptObjectPos->vX;
    GlassShatter_tSpreadFromPos.vY = ptHitPos->vY - ptObjectPos->vY;
    GlassShatter_tSpreadFromPos.vZ = ptHitPos->vZ - ptObjectPos->vZ;
    struct_real32x3_t.vX = GlassShatter_tSpreadFromPos.vX * ptObjectOrientation->tX.vX
                         + GlassShatter_tSpreadFromPos.vZ * ptObjectOrientation->tZ.vX
                         + GlassShatter_tSpreadFromPos.vY * ptObjectOrientation->tY.vX;
    v23 = GlassShatter_tSpreadFromPos.vZ * ptObjectOrientation->tZ.vY;
    v24 = GlassShatter_tSpreadFromPos.vY * ptObjectOrientation->tY.vY;
    GlassShatter_ptColor = (struct real32x3_t *)&unk_6B7864;
    GlassShatter_ptActiveGlassShatter = v7;
    vLena = 0;
    struct_real32x3_t.vY = v23 + v24 + GlassShatter_tSpreadFromPos.vX * ptObjectOrientation->tX.vY;
    v25 = GlassShatter_tSpreadFromPos.vX * ptObjectOrientation->tX.vZ
        + GlassShatter_tSpreadFromPos.vZ * ptObjectOrientation->tZ.vZ;
    v26 = GlassShatter_tSpreadFromPos.vY * ptObjectOrientation->tY.vZ;
    GlassShatter_ptShard = v7->atShard;
    v27 = pxCollisionMesh;
    struct_real32x3_t.vZ = v25 + v26;
    GlassShatter_tSpreadFromPos = struct_real32x3_t;
    GlassShatter_vHitVelocity = v14;
    GlassShatter_ptPoly = v7->atPoly;
    v7->nShards = 0;
    if ( pxCollisionMesh->nNumFaces > 0 )
    {
      ptModela = nullptr;
      while ( 1 )
      {
        ptFace = v27->ptFace;
        ptVertex = v27->ptVertex;
        v30 = *(unsigned __int16 *)((char *)ptModela->aptVirModel + (_DWORD)ptFace);
        v31 = (char *)ptFace + (_DWORD)ptModela;
        v32 = *((unsigned __int16 *)v31 + 1);
        v33 = *((unsigned __int16 *)v31 + 2);
        p_tPos = &ptVertex[v30].tPos;
        v35 = &ptVertex[v32].tPos;
        v36 = ptVertex[v33].tPos.vX - p_tPos->vX;
        v37 = &ptVertex[v33].tPos;
        v38 = v37->vY - p_tPos->vY;
        v39 = v37->vZ - p_tPos->vZ;
        Real32x3_RotateInverse_tTempa = v35->vX - p_tPos->vX;
        Real32x3_RotateInverse_tTemp_4a = v35->vY - p_tPos->vY;
        v40 = v35->vZ - p_tPos->vZ;
        tTemp_ = v40 * v38 - Real32x3_RotateInverse_tTemp_4a * v39;
        tTemp__4 = -(v40 * v36 - Real32x3_RotateInverse_tTempa * v39);
        if ( (v11->vZ - ptHitPos->vZ) * (v36 * Real32x3_RotateInverse_tTemp_4a - Real32x3_RotateInverse_tTempa * v38)
           + (v11->vY - ptHitPos->vY) * tTemp__4
           + (v11->vX - ptHitPos->vX) * tTemp_ < 0.0 )
        {
          GlassShatter_CreateShards(p_tPos, v35, v37);
          v11 = ptObjectPos;
        }
        v41 = ++vLena < ptCollMesh->nNumFaces;
        ptModela = (struct LODVirModel_s *)((char *)ptModela + 12);
        if ( !v41 )
          break;
        v27 = ptCollMesh;
      }
    }
    v9->ptPolyListDynCubeObj = PolyListDynCubeObj_New(
                                 Game_ptGame->ptWorld,
                                 nullptr,
                                 v11,
                                 ptObjectOrientation,
                                 v9->atPoly,
                                 v9->nShards,
                                 0,
                                 1,
                                 0,
                                 0,
                                 nullptr,
                                 nullptr);
    GlassShatter_Sound(ptObjectPos);
  }
}
