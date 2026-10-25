/* h/0/particle2ddyncubeobj.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/0/particle2ddyncubeobj.c:181  [anchor-hash]
float __cdecl Particle2DDynCubeObj_FindRadius(
        struct Particle2DDynCubeObj_s *ptParticle2DDynCubeObj)
{
  double v1; // st7
  double v2; // st6
  double v3; // st5
  long double v4; // st7

  v1 = ptParticle2DDynCubeObj->tMaxParticlePos.vX - ptParticle2DDynCubeObj->tMinParticlePos.vX;
  v2 = ptParticle2DDynCubeObj->tMaxParticlePos.vY - ptParticle2DDynCubeObj->tMinParticlePos.vY;
  v3 = ptParticle2DDynCubeObj->tMaxParticlePos.vZ - ptParticle2DDynCubeObj->tMinParticlePos.vZ;
  if ( v1 == 0.0 && v2 == 0.0 && v3 == 0.0 )
  {
    return 1.0;
  }
  else
  {
    v4 = sqrt(v2 * v2 + v3 * v3 + v1 * v1) * 0.5 + 8192.0;
    if ( v4 < 1.0 )
      return 1.0;
  }
  return v4;
}

// source: h/0/particle2ddyncubeobj.c:218  [anchor-mhash]
struct real64x3_t *__cdecl Particle2DDynCubeObj_FindPosition(
        struct real64x3_t *ptPos,
        struct Particle2DDynCubeObj_s *ptParticle2DDynCubeObj)
{
  ptPos->vX = ptParticle2DDynCubeObj->tMaxParticlePos.vX + ptParticle2DDynCubeObj->tMinParticlePos.vX;
  ptPos->vY = ptParticle2DDynCubeObj->tMaxParticlePos.vY + ptParticle2DDynCubeObj->tMinParticlePos.vY;
  ptPos->vZ = ptParticle2DDynCubeObj->tMaxParticlePos.vZ + ptParticle2DDynCubeObj->tMinParticlePos.vZ;
  ptPos->vX = ptPos->vX * 0.5;
  ptPos->vY = ptPos->vY * 0.5;
  ptPos->vZ = ptPos->vZ * 0.5;
  return ptPos;
}

// source: h/0/particle2ddyncubeobj.c:232  [anchor-mhash]
void __cdecl Particle2DDynCubeObj_RemoveParticle(struct QTask_s *ptQTask, int nItem)
{
  struct QTask_s *ptHead; // edx
  int v3; // eax
  int v4; // edi

  ptHead = ptQTask[6].tQTaskChildren.ptHead;
  if ( ptHead )
  {
    if ( &ptHead[-1].isInMemPool + 1 != (char *)nItem )
    {
      v3 = *(_DWORD *)&ptQTask[2].eQTaskType;
      v4 = *(_DWORD *)(v3 + 4 * nItem);
      *(_DWORD *)(v3 + 4 * nItem) = *(_DWORD *)(v3 + 4 * (_DWORD)ptHead - 4);
      *(_DWORD *)(*(_DWORD *)&ptQTask[2].eQTaskType + 4 * (int)ptQTask[6].tQTaskChildren.ptHead - 4) = v4;
    }
    --*(int *)&ptQTask[6].tQTaskChildren.ptHead;
  }
}

// source: h/0/particle2ddyncubeobj.c:305  [anchor-mhash]
struct real32x3_t *__cdecl Particle2DDynCubeObj_SetWorldColor(
        struct Particle2DDynCubeObj_s *ptParticle2D,
        struct real32x3_t *ptRGB)
{
  double vX; // st7
  float vZ; // edx
  float tAmbientColor_4; // [esp+8h] [ebp-8h]

  vX = Mesh3D_atAmbientColor[0].vX;
  tAmbientColor_4 = Mesh3D_atAmbientColor[0].vY;
  vZ = Mesh3D_atAmbientColor[0].vZ;
  ptRGB->vX = Mesh3D_atAmbientColor[0].vX;
  ptRGB->vY = tAmbientColor_4;
  ptRGB->vZ = vZ;
  ptRGB->vX = vX * ptParticle2D->vShinyness * 255.0;
  ptRGB->vY = tAmbientColor_4 * ptParticle2D->vShinyness * 255.0;
  ptRGB->vZ = vZ * ptParticle2D->vShinyness * 255.0;
  return ptRGB;
}

// source: h/0/particle2ddyncubeobj.c:349  [anchor-mhash]
void __cdecl Particle2DDynCubeObj_EnterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { unsigned int v28; };
    struct { char igi2_o1[24]; float v29; };
    struct { char igi2_o2[28]; float v30; };
    struct { char igi2_o3[32]; float vCos; };
    struct { char igi2_o4[36]; float vAlpha; };
    struct { char igi2_o5[40]; int nItem; };
    struct { char igi2_o6[44]; float v34; };
    struct { char igi2_o7[44]; float v35; };
    struct { char igi2_o8[44]; float v36; };
    struct { char igi2_o9[48]; struct real32x2_t tScreenPos; };
    struct { char igi2_o10[56]; struct real32x2_t tCorner3; };
    struct { char igi2_o11[64]; struct real32x2_t tCorner1; };
    struct { char igi2_o12[72]; struct real32x2_t tCorner0; };
    struct { char igi2_o13[80]; struct real32x2_t tCorner2; };
    struct { char igi2_o14[88]; struct real32x2_t tSpriteSize; };
    struct { char igi2_o15[96]; struct real32x3_t tWorldRGB; };
    struct { char igi2_o16[108]; struct real32x3_t tRGB; };
    char igi2_extent[120];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v2; // edi
  double v3; // st7
  double v4; // st7
  double v5; // st6
  double vY; // st5
  double v7; // st5
  double v8; // st5
  double v9; // st5
  double v10; // st5
  float vX; // ebp
  float v12; // ebx
  int v13; // esi
  double v14; // st7
  float v15; // edx
  double v16; // st7
  double v17; // st6
  double v18; // st7
  long double v19; // st6
  long double v20; // st4
  double v21; // st3
  long double v22; // st6
  double v23; // st6
  double v24; // st7
  struct QTask_s *ptNext; // eax
  double v26; // st7
  float v27; // ecx

  v2 = ptQTask;
  v3 = *(float *)&ptQTask[5].tQTaskRefList.ptTail;
  memset(&igi2_frame.tWorldRGB, 0, sizeof(igi2_frame.tWorldRGB));
  igi2_frame.nItem = 0;
  if ( v3 <= 0.0 )
  {
    vX = *(float *)&ptQTask[5].tQTaskChildren.ptTail;
    v12 = *(float *)&ptQTask[5].tQTaskRefList.ptHead;
    LODWORD(igi2_frame.tRGB.vZ) = ptQTask[5].tQTaskRefList.ptMiddle;
  }
  else
  {
    Particle2DDynCubeObj_SetWorldColor((struct Particle2DDynCubeObj_s *)ptQTask, &igi2_frame.tWorldRGB);
    v4 = igi2_frame.tWorldRGB.vX + *(float *)&v2[5].tQTaskChildren.ptTail;
    igi2_frame.tRGB.vY = igi2_frame.tWorldRGB.vY + *(float *)&v2[5].tQTaskRefList.ptHead;
    v5 = igi2_frame.tWorldRGB.vZ + *(float *)&v2[5].tQTaskRefList.ptMiddle;
    if ( igi2_frame.tRGB.vY <= v5 )
      vY = v5;
    else
      vY = igi2_frame.tRGB.vY;
    if ( v4 <= vY )
    {
      if ( igi2_frame.tRGB.vY <= v5 )
        v7 = v5;
      else
        v7 = igi2_frame.tRGB.vY;
    }
    else
    {
      v7 = v4;
    }
    if ( v7 >= 1.0 )
    {
      if ( igi2_frame.tRGB.vY <= v5 )
        v9 = v5;
      else
        v9 = igi2_frame.tRGB.vY;
      if ( v4 <= v9 )
      {
        if ( igi2_frame.tRGB.vY <= v5 )
          v8 = v5;
        else
          v8 = igi2_frame.tRGB.vY;
      }
      else
      {
        v8 = v4;
      }
    }
    else
    {
      v8 = 1.0;
    }
    v10 = 1.0 / (v8 * 0.007874015718698502);
    igi2_frame.tRGB.vX = v10 * v4;
    vX = igi2_frame.tRGB.vX;
    igi2_frame.tRGB.vY = igi2_frame.tRGB.vY * v10;
    v12 = igi2_frame.tRGB.vY;
    igi2_frame.tRGB.vZ = v10 * v5;
  }
  if ( v2[6].tQTaskChildren.ptHead )
  {
    do
    {
      v13 = *(_DWORD *)(*(_DWORD *)&v2[2].eQTaskType + 4 * igi2_frame.nItem);
      TransContext_ProjectWorldPos2(
        &TransContext_tActiveTransContext,
        &igi2_frame.tScreenPos,
        (float *)&ptQTask,
        (struct real64x3_t *)v13);
      if ( *(float *)&ptQTask > 2048.0 && *(float *)&ptQTask < (double)*(float *)&v2[5].ptParent )
      {
        v14 = *(float *)&v2[5].eQTaskType;
        v15 = *(float *)&v2[5].ptNext;
        igi2_frame.tSpriteSize.vX = *(float *)&v2[4].eQTaskType;
        igi2_frame.tSpriteSize.vY = v15;
        if ( v14 == 0.0 )
        {
          v16 = igi2_frame.tSpriteSize.vY;
        }
        else
        {
          igi2_frame.tSpriteSize.vX = igi2_frame.tSpriteSize.vX * *(float *)(v13 + 60);
          v16 = igi2_frame.tSpriteSize.vY * *(float *)(v13 + 60);
        }
        v17 = 1.0 / *(float *)&ptQTask;
        igi2_frame.tWorldRGB.vX = TransContext_tActiveTransContext.vScreenFOVX * igi2_frame.tSpriteSize.vX * v17;
        v18 = v16 * TransContext_tActiveTransContext.vScreenFOVY * v17;
        if ( igi2_frame.tWorldRGB.vX < 0.5 )
          igi2_frame.tWorldRGB.vX = 0.5;
        if ( v18 < 0.5 )
          v18 = 0.5;
        if ( *(float *)(v13 + 44) == 0.0 )
        {
          igi2_frame.tCorner0.vX = igi2_frame.tScreenPos.vX - igi2_frame.tWorldRGB.vX;
          igi2_frame.tCorner0.vY = igi2_frame.tScreenPos.vY - v18;
          igi2_frame.v36 = igi2_frame.tScreenPos.vX + igi2_frame.tWorldRGB.vX;
          igi2_frame.tCorner1.vX = igi2_frame.v36;
          igi2_frame.tCorner3.vX = igi2_frame.v36;
          igi2_frame.tCorner1.vY = igi2_frame.tCorner0.vY;
          igi2_frame.tCorner2.vX = igi2_frame.tCorner0.vX;
          v24 = v18 + igi2_frame.tScreenPos.vY;
          igi2_frame.tCorner2.vY = v24;
        }
        else
        {
          igi2_frame.vCos = cos(*(float *)(v13 + 56));
          v19 = sin(*(float *)(v13 + 56));
          v20 = -v18 * v19;
          v21 = igi2_frame.vCos * igi2_frame.tWorldRGB.vX;
          igi2_frame.v29 = v21;
          igi2_frame.tCorner0.vX = v20 - v21;
          igi2_frame.v34 = -v18 * igi2_frame.vCos;
          igi2_frame.v30 = -v19 * igi2_frame.tWorldRGB.vX;
          igi2_frame.tCorner0.vY = igi2_frame.v34 - igi2_frame.v30;
          igi2_frame.tCorner1.vX = igi2_frame.v29 + v20;
          igi2_frame.tCorner1.vY = igi2_frame.v30 + igi2_frame.v34;
          v22 = v19 * v18;
          igi2_frame.v35 = v22;
          igi2_frame.tCorner2.vX = v22 - igi2_frame.v29;
          igi2_frame.tCorner3.vX = igi2_frame.v35 + igi2_frame.v29;
          v23 = v18 * igi2_frame.vCos;
          igi2_frame.tCorner3.vY = v23 + igi2_frame.v30;
          igi2_frame.tCorner0.vX = igi2_frame.tScreenPos.vX + igi2_frame.tCorner0.vX;
          igi2_frame.tCorner0.vY = igi2_frame.tScreenPos.vY + igi2_frame.tCorner0.vY;
          igi2_frame.tCorner1.vX = igi2_frame.tScreenPos.vX + igi2_frame.tCorner1.vX;
          igi2_frame.tCorner1.vY = igi2_frame.tScreenPos.vY + igi2_frame.tCorner1.vY;
          igi2_frame.tCorner2.vX = igi2_frame.tScreenPos.vX + igi2_frame.tCorner2.vX;
          igi2_frame.tCorner2.vY = igi2_frame.tScreenPos.vY + v23 - igi2_frame.v30;
          igi2_frame.tCorner3.vX = igi2_frame.tScreenPos.vX + igi2_frame.tCorner3.vX;
          v24 = igi2_frame.tScreenPos.vY + igi2_frame.tCorner3.vY;
        }
        ptNext = v2[6].ptNext;
        igi2_frame.tCorner3.vY = v24;
        if ( ptNext )
        {
          if ( ((unsigned int)ptNext & 0x80000) != 0 )
          {
            igi2_frame.vAlpha = *(float *)(v13 + 48);
          }
          else
          {
            LODWORD(igi2_frame.tRGB.vX) = v2[5].tQTaskChildren.ptTail;
            v26 = igi2_frame.tRGB.vX * *(float *)(v13 + 48);
            v27 = *(float *)&v2[5].tQTaskRefList.ptMiddle;
            LODWORD(igi2_frame.tRGB.vY) = v2[5].tQTaskRefList.ptHead;
            igi2_frame.tRGB.vX = v26;
            vX = igi2_frame.tRGB.vX;
            igi2_frame.tRGB.vZ = v27;
            igi2_frame.vAlpha = 1.0;
            igi2_frame.tRGB.vY = igi2_frame.tRGB.vY * *(float *)(v13 + 48);
            v12 = igi2_frame.tRGB.vY;
            igi2_frame.tRGB.vZ = v27 * *(float *)(v13 + 48);
          }
        }
        igi2_frame.v28 = (unsigned int)ptNext | 0x1000000;
        if ( LOBYTE(v2[6].tQTaskRefList.ptHead) )
          QSprite_Register4AZ(
            (struct QSprite_s *)v2[3].tQTaskChildren.ptTail,
            igi2_frame.tCorner0.vX,
            igi2_frame.tCorner0.vY,
            igi2_frame.tCorner1.vX,
            igi2_frame.tCorner1.vY,
            igi2_frame.tCorner2.vX,
            igi2_frame.tCorner2.vY,
            igi2_frame.tCorner3.vX,
            igi2_frame.tCorner3.vY,
            vX,
            v12,
            igi2_frame.tRGB.vZ,
            igi2_frame.vAlpha,
            *(float *)&ptQTask,
            *((unsigned __int8 *)&v2[3].tQTaskChildren.ptTail->tQTaskChildren.ptMiddle->tQTaskChildren.ptTail
            + *(__int16 *)(v13 + 40))
          - 1,
            igi2_frame.v28,
            0);
        else
          QSprite_Register4AZ(
            (struct QSprite_s *)v2[3].tQTaskChildren.ptTail,
            igi2_frame.tCorner0.vX,
            igi2_frame.tCorner0.vY,
            igi2_frame.tCorner1.vX,
            igi2_frame.tCorner1.vY,
            igi2_frame.tCorner2.vX,
            igi2_frame.tCorner2.vY,
            igi2_frame.tCorner3.vX,
            igi2_frame.tCorner3.vY,
            vX,
            v12,
            igi2_frame.tRGB.vZ,
            igi2_frame.vAlpha,
            *(float *)&ptQTask,
            0,
            igi2_frame.v28,
            0);
      }
      ++igi2_frame.nItem;
    }
    while ( igi2_frame.nItem < (int)v2[6].tQTaskChildren.ptHead );
  }
}

// source: h/0/particle2ddyncubeobj.c:573  [anchor-mhash]
void __cdecl Particle2DDynCubeObj_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[3].tQTaskRefList.ptTail = (struct QReference_s *)2146435071;
  *(_DWORD *)&ptQTask[3].eQTaskType = 2146435071;
  ptQTask[4].ptPrev = (struct QTask_s *)2146435071;
  ptQTask[4].tQTaskChildren.ptMiddle = (struct QTask_s *)-1048577;
  ptQTask[4].tQTaskRefList.ptHead = (struct QReference_s *)-1048577;
  ptQTask[4].tQTaskRefList.ptTail = (struct QReference_s *)-1048577;
  *(_DWORD *)&ptQTask[2].eQTaskType = 0;
  ptQTask[6].tQTaskChildren.ptHead = nullptr;
  BYTE1(ptQTask[6].tQTaskRefList.ptHead) = 1;
  LOBYTE(ptQTask[6].tQTaskRefList.ptHead) = 0;
  ptQTask[3].tQTaskRefList.ptMiddle = (struct QReference_s *)-1;
  ptQTask[3].ptParent = (struct QTask_s *)-1;
  ptQTask[4].ptNext = (struct QTask_s *)-1;
  ptQTask[4].tQTaskChildren.ptHead = (struct QTask_s *)-1;
  ptQTask[4].tQTaskChildren.ptTail = (struct QTask_s *)-1;
  ptQTask[4].tQTaskRefList.ptMiddle = (struct QReference_s *)-1;
  ptQTask[3].ptNext = nullptr;
  ptQTask[3].ptPrev = nullptr;
  ptQTask[3].tQTaskChildren.ptHead = nullptr;
  ptQTask[3].tQTaskChildren.ptMiddle = nullptr;
}

// source: h/0/particle2ddyncubeobj.c:603  [anchor-mhash]
void __cdecl Particle2DDynCubeObj_RunHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[20]; int iCollisionItem; };
    struct { char igi2_o2[20]; int iCollisionItema; };
    struct { char igi2_o3[24]; int nItem; };
    struct { char igi2_o4[24]; int nItema; };
    struct { char igi2_o5[28]; int nCollisionItem; };
    struct { char igi2_o6[32]; int v50; };
    struct { char igi2_o7[36]; struct real64x3_t tMaxParticlePos; };
    struct { char igi2_o8[60]; struct real64x3_t tDiffNewOldMax; };
    struct { char igi2_o9[84]; struct real64x3_t tMinParticlePos; };
    struct { char igi2_o10[112]; struct QIntersection_s *ptIntersection; };
    struct { char igi2_o11[116]; struct real64x3_t tDiffNewOldMin; };
    struct { char igi2_o12[140]; struct Particle2DCollisionEvaluateContext_t tParticle2DCollisionEvaluateContext; };
    struct { char igi2_o13[148]; struct Particle2DCollisionContext_t tParticle2DCollisionContext; };
    char igi2_extent[204];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v1; // edi
  struct QTask_s *v2; // edx
  char ptHead; // al
  double v4; // st7
  struct QTask_s *ptTail; // eax
  int v6; // ecx
  __int16 v7; // ax
  __int16 v8; // ax
  struct QTask_s *v9; // eax
  double **v10; // edx
  struct QTask_s *v11; // esi
  double *v12; // ecx
  int v13; // edi
  int v14; // edi
  int v15; // edi
  int v16; // edi
  int v17; // edi
  double *p_ptMiddle; // edx
  double v19; // st5
  double v20; // rt0
  double v21; // st6
  struct QTask_s *v22; // ecx
  int v23; // eax
  int v24; // esi
  int v25; // ecx
  int v26; // esi
  _WORD *v27; // eax
  __int16 v28; // dx
  struct QTask_s *ptPrev; // edx
  struct QTask_s *ptParent; // eax
  int v31; // edx
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptMiddle; // ecx
  int v34; // eax
  struct real64x3_t *v35; // edi
  int v36; // eax
  bool v37; // zf
  struct QTask_s *v38; // esi
  struct QTask_s *v39; // edx
  struct QTask_s *v40; // eax
  int v41; // ecx
  int v42; // esi
  bool v43; // cc

  v1 = 0;
  v2 = nullptr;
  if ( ptQTask[6].tQTaskChildren.ptHead )
  {
    ptHead = (char)ptQTask[6].tQTaskRefList.ptHead;
    v4 = 1.7976931348623157e+308;
    igi2_frame.tMinParticlePos.vZ = 1.7976931348623157e+308;
    igi2_frame.tMinParticlePos.vX = 1.7976931348623157e+308;
    igi2_frame.tMinParticlePos.vY = 1.7976931348623157e+308;
    igi2_frame.tMaxParticlePos.vX = -1.7976931348623157e+308;
    igi2_frame.tMaxParticlePos.vY = -1.7976931348623157e+308;
    igi2_frame.tMaxParticlePos.vZ = -1.7976931348623157e+308;
    if ( ptHead )
    {
      ptTail = ptQTask[3].tQTaskChildren.ptTail;
      if ( ptTail )
        v1 = SLOWORD(ptTail->tQTaskChildren.ptMiddle->ptPrev) - 1;
    }
    while ( 1 )
    {
      v6 = *(_DWORD *)(*(_DWORD *)&ptQTask[2].eQTaskType + 4 * (_DWORD)v2);
      *(float *)(v6 + 24) = *(float *)(v6 + 24) + *(float *)&ptQTask[5].ptPrev;
      *(float *)(v6 + 28) = *(float *)&ptQTask[5].tQTaskChildren.ptHead + *(float *)(v6 + 28);
      *(float *)(v6 + 32) = *(float *)&ptQTask[5].tQTaskChildren.ptMiddle + *(float *)(v6 + 32);
      *(double *)v6 = *(float *)(v6 + 24) + *(double *)v6;
      *(double *)(v6 + 8) = *(float *)(v6 + 28) + *(double *)(v6 + 8);
      *(double *)(v6 + 16) = *(float *)(v6 + 32) + *(double *)(v6 + 16);
      *(float *)(v6 + 56) = *(float *)(v6 + 44) + *(float *)(v6 + 56);
      *(float *)(v6 + 60) = *(float *)&ptQTask[5].eQTaskType + *(float *)(v6 + 60);
      if ( v1 )
      {
        if ( (__int16)++*(_WORD *)(v6 + 42) >= (int)ptQTask[6].tQTaskChildren.ptMiddle )
        {
          v7 = *(_WORD *)(v6 + 40);
          *(_WORD *)(v6 + 42) = 0;
          if ( v7 < v1 )
            *(_WORD *)(v6 + 40) = v7 + 1;
        }
      }
      v8 = *(_WORD *)(v6 + 38);
      if ( v8 )
      {
        *(_WORD *)(v6 + 38) = v8 - 1;
      }
      else
      {
        v21 = *(float *)(v6 + 48) - *(float *)(v6 + 52);
        *(float *)(v6 + 48) = v21;
        if ( v21 <= 0.0 || *(float *)(v6 + 60) <= 0.0 )
        {
          v22 = ptQTask[6].tQTaskChildren.ptHead;
          if ( v22 )
          {
            if ( &v22[-1].isInMemPool + 1 != (char *)v2 )
            {
              v23 = *(_DWORD *)&ptQTask[2].eQTaskType;
              v24 = *(_DWORD *)(v23 + 4 * (_DWORD)v2);
              *(_DWORD *)(v23 + 4 * (_DWORD)v2) = *(_DWORD *)(v23 + 4 * (_DWORD)v22 - 4);
              *(_DWORD *)(*(_DWORD *)&ptQTask[2].eQTaskType + 4 * (int)ptQTask[6].tQTaskChildren.ptHead - 4) = v24;
            }
            --*(int *)&ptQTask[6].tQTaskChildren.ptHead;
          }
          goto LABEL_12;
        }
      }
      v2 = (struct QTask_s *)((char *)v2 + 1);
LABEL_12:
      v9 = ptQTask[6].tQTaskChildren.ptHead;
      if ( (int)v2 >= (int)v9 )
      {
        if ( v9 )
        {
          if ( (int)v9 > 0 )
          {
            v10 = *(double ***)&ptQTask[2].eQTaskType;
            v11 = ptQTask[6].tQTaskChildren.ptHead;
            do
            {
              v12 = *v10;
              if ( igi2_frame.tMaxParticlePos.vX < **v10 )
              {
                v13 = *((_DWORD *)v12 + 1);
                LODWORD(igi2_frame.tMaxParticlePos.vX) = *(_DWORD *)v12;
                HIDWORD(igi2_frame.tMaxParticlePos.vX) = v13;
              }
              if ( igi2_frame.tMaxParticlePos.vY < v12[1] )
              {
                v14 = *((_DWORD *)v12 + 3);
                LODWORD(igi2_frame.tMaxParticlePos.vY) = *((_DWORD *)v12 + 2);
                HIDWORD(igi2_frame.tMaxParticlePos.vY) = v14;
              }
              if ( igi2_frame.tMaxParticlePos.vZ < v12[2] )
              {
                v15 = *((_DWORD *)v12 + 5);
                LODWORD(igi2_frame.tMaxParticlePos.vZ) = *((_DWORD *)v12 + 4);
                HIDWORD(igi2_frame.tMaxParticlePos.vZ) = v15;
              }
              if ( igi2_frame.tMinParticlePos.vX > *v12 )
              {
                v16 = *((_DWORD *)v12 + 1);
                LODWORD(igi2_frame.tMinParticlePos.vX) = *(_DWORD *)v12;
                HIDWORD(igi2_frame.tMinParticlePos.vX) = v16;
              }
              if ( igi2_frame.tMinParticlePos.vY > v12[1] )
              {
                v17 = *((_DWORD *)v12 + 3);
                LODWORD(igi2_frame.tMinParticlePos.vY) = *((_DWORD *)v12 + 2);
                HIDWORD(igi2_frame.tMinParticlePos.vY) = v17;
              }
              if ( v4 > v12[2] )
                v4 = v12[2];
              ++v10;
              v11 = (struct QTask_s *)((char *)v11 - 1);
            }
            while ( v11 );
            igi2_frame.tMinParticlePos.vZ = v4;
          }
          p_ptMiddle = (double *)&ptQTask[3].tQTaskRefList.ptMiddle;
          igi2_frame.tDiffNewOldMin.vX = igi2_frame.tMinParticlePos.vX - *(double *)&ptQTask[3].tQTaskRefList.ptMiddle;
          igi2_frame.tDiffNewOldMin.vY = igi2_frame.tMinParticlePos.vY - *(double *)&ptQTask[3].ptParent;
          igi2_frame.tDiffNewOldMin.vZ = v4 - *(double *)&ptQTask[4].ptNext;
          igi2_frame.tDiffNewOldMax.vX = igi2_frame.tMaxParticlePos.vX - *(double *)&ptQTask[4].tQTaskChildren.ptHead;
          igi2_frame.tDiffNewOldMax.vY = igi2_frame.tMaxParticlePos.vY - *(double *)&ptQTask[4].tQTaskChildren.ptTail;
          igi2_frame.tDiffNewOldMax.vZ = igi2_frame.tMaxParticlePos.vZ - *(double *)&ptQTask[4].tQTaskRefList.ptMiddle;
          if ( igi2_frame.tDiffNewOldMin.vX < 0.0
            || igi2_frame.tDiffNewOldMin.vY < 0.0
            || igi2_frame.tDiffNewOldMin.vZ < 0.0
            || igi2_frame.tDiffNewOldMax.vX > 0.0
            || igi2_frame.tDiffNewOldMax.vY > 0.0
            || igi2_frame.tDiffNewOldMax.vZ > 0.0
            || igi2_frame.tDiffNewOldMin.vX > 12288.0
            || igi2_frame.tDiffNewOldMin.vY > 12288.0
            || igi2_frame.tDiffNewOldMin.vZ > 12288.0
            || igi2_frame.tDiffNewOldMax.vX < 12288.0
            || igi2_frame.tDiffNewOldMax.vY < 12288.0
            || igi2_frame.tDiffNewOldMax.vZ < 12288.0 )
          {
            qmemcpy(p_ptMiddle, &igi2_frame.tMinParticlePos, 0x18u);
            qmemcpy(&ptQTask[4].tQTaskChildren, &igi2_frame.tMaxParticlePos, 0x18u);
            v19 = *(double *)&ptQTask[4].tQTaskRefList.ptMiddle + *(double *)&ptQTask[4].ptNext;
            v20 = *(double *)&ptQTask[4].tQTaskChildren.ptTail + *(double *)&ptQTask[3].ptParent;
            igi2_frame.tDiffNewOldMax.vX = (*(double *)&ptQTask[4].tQTaskChildren.ptHead + *p_ptMiddle) * 0.5;
            igi2_frame.tDiffNewOldMax.vY = v20 * 0.5;
            igi2_frame.tDiffNewOldMax.vZ = v19 * 0.5;
            igi2_frame.ptDynCubeObj = Particle2DDynCubeObj_FindRadius((struct Particle2DDynCubeObj_s *)ptQTask);
            World_MoveDynCubeObjRadius(
              (struct World_s *)ptQTask[4].ptParent,
              (struct DynCubeObj_s *)ptQTask,
              &igi2_frame.tDiffNewOldMax,
              igi2_frame.ptDynCubeObj);
          }
        }
        if ( ptQTask[6].ptPrev )
        {
          v25 = 0;
          v26 = 0;
          igi2_frame.nCollisionItem = 0;
          igi2_frame.nItem = 0;
          if ( (int)ptQTask[6].tQTaskChildren.ptHead > 0 )
          {
            igi2_frame.iCollisionItem = 0;
            do
            {
              v27 = *(_WORD **)(*(_DWORD *)&ptQTask[2].eQTaskType + 4 * v25);
              v28 = v27[18];
              if ( v28 )
                v27[18] = v28 - 1;
              if ( !v27[18] )
              {
                *((_DWORD *)&ptQTask[3].tQTaskChildren.ptMiddle->ptNext + v26) = v25;
                qmemcpy((char *)ptQTask[3].ptPrev + igi2_frame.iCollisionItem, v27 + 32, 0x18u);
                qmemcpy((char *)ptQTask[3].tQTaskChildren.ptHead + igi2_frame.iCollisionItem, v27, 0x18u);
                igi2_frame.iCollisionItem += 24;
                ++igi2_frame.nCollisionItem;
                qmemcpy(v27 + 32, v27, 0x18u);
                v25 = igi2_frame.nItem;
                v27[18] = 15;
              }
              v26 = igi2_frame.nCollisionItem;
              igi2_frame.nItem = ++v25;
            }
            while ( v25 < (int)ptQTask[6].tQTaskChildren.ptHead );
          }
          ptPrev = ptQTask[3].ptPrev;
          ptParent = ptQTask[4].ptParent;
          igi2_frame.tParticle2DCollisionEvaluateContext.tCollisionEvaluateContext.ptQTask = nullptr;
          World_TraceLines(
            (struct World_s *)ptParent,
            (struct QIntersection_s *)ptQTask[3].ptNext,
            (struct real64x3_t *)ptPrev,
            (struct real64x3_t *)ptQTask[3].tQTaskChildren.ptHead,
            v26,
            Particle2DDynCubeObj_eParticle2DCollisionEvaluateQTaskEvent,
            &igi2_frame.tParticle2DCollisionEvaluateContext.tCollisionEvaluateContext,
            0x20000000u);
          igi2_frame.iCollisionItema = 0;
          if ( v26 > 0 )
          {
            v31 = 0;
            igi2_frame.nItema = 0;
            igi2_frame.v50 = 0;
            do
            {
              ptNext = ptQTask[3].ptNext;
              ptMiddle = ptNext[igi2_frame.v50 + 2].tQTaskChildren.ptMiddle;
              igi2_frame.ptIntersection = (struct QIntersection_s *)&ptNext[igi2_frame.v50];
              if ( ptMiddle )
              {
                v34 = 2 * nCollisionLines;
                qmemcpy(
                  &atCollisionLines[2 * nCollisionLines],
                  (char *)ptQTask[3].ptPrev + v31,
                  sizeof(struct real64x3_t));
                v35 = &atCollisionLines[v34 + 1];
                v36 = nCollisionLines + 1;
                v37 = nCollisionLines == 255;
                qmemcpy(v35, (char *)ptQTask[3].tQTaskChildren.ptHead + v31, sizeof(struct real64x3_t));
                nCollisionLines = v36;
                if ( v37 )
                  nCollisionLines = 0;
                v38 = ptQTask[3].ptPrev;
                igi2_frame.tParticle2DCollisionContext.ptIntersection = igi2_frame.ptIntersection;
                qmemcpy(
                  &igi2_frame.tParticle2DCollisionContext.tPos0,
                  (char *)v38 + v31,
                  sizeof(igi2_frame.tParticle2DCollisionContext.tPos0));
                qmemcpy(
                  &igi2_frame.tParticle2DCollisionContext.tPos1,
                  (char *)ptQTask[3].tQTaskChildren.ptHead + v31,
                  sizeof(igi2_frame.tParticle2DCollisionContext.tPos1));
                ((void (__cdecl *)(struct Particle2DCollisionContext_t *))ptQTask[6].ptPrev)(&igi2_frame.tParticle2DCollisionContext);
                v39 = *(&ptQTask[3].tQTaskChildren.ptMiddle->ptNext + igi2_frame.iCollisionItema);
                v40 = ptQTask[6].tQTaskChildren.ptHead;
                if ( v40 )
                {
                  if ( &v40[-1].isInMemPool + 1 != (char *)v39 )
                  {
                    v41 = *(_DWORD *)&ptQTask[2].eQTaskType;
                    v42 = *(_DWORD *)(v41 + 4 * (_DWORD)v39);
                    *(_DWORD *)(v41 + 4 * (_DWORD)v39) = *(_DWORD *)(v41 + 4 * (_DWORD)v40 - 4);
                    *(_DWORD *)(*(_DWORD *)&ptQTask[2].eQTaskType + 4 * (int)ptQTask[6].tQTaskChildren.ptHead - 4) = v42;
                  }
                  --*(int *)&ptQTask[6].tQTaskChildren.ptHead;
                }
                v31 = igi2_frame.nItema;
              }
              v31 += 24;
              v43 = ++igi2_frame.iCollisionItema < igi2_frame.nCollisionItem;
              igi2_frame.v50 += 3;
              igi2_frame.nItema = v31;
            }
            while ( v43 );
          }
        }
        return;
      }
    }
  }
  if ( BYTE1(ptQTask[6].tQTaskRefList.ptHead) )
    QTask_Delete(ptQTask);
}

// source: h/0/particle2ddyncubeobj.c:906  [anchor-mhash]
void __cdecl Particle2DDynCubeObj_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptParent; // eax
  int v2; // ebx
  int v3; // eax
  int v4; // ebx
  struct QTask_s *ptNext; // eax
  int v6; // ebx
  struct QTask_s *ptMiddle; // eax
  int v8; // ebx
  struct QTask_s *ptPrev; // eax
  int v10; // ebx
  struct QTask_s *ptHead; // eax
  int v12; // ebx
  struct QTask_s *v13; // eax

  ptParent = ptQTask[2].ptParent;
  if ( ptParent )
  {
    --Mem_nCurrentAllocations;
    v2 = *(_DWORD *)((unsigned int)&ptParent[-1].eQTaskType & 0xFFFFFFFC);
    Node_Remove((_DWORD **)v2);
    memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
    free((void *)v2);
  }
  v3 = *(_DWORD *)&ptQTask[2].eQTaskType;
  ptQTask[2].ptParent = nullptr;
  if ( v3 )
  {
    --Mem_nCurrentAllocations;
    v4 = *(_DWORD *)((v3 - 4) & 0xFFFFFFFC);
    Node_Remove((_DWORD **)v4);
    memset(*(void **)(v4 + 8), 0xCDu, *(_DWORD *)(v4 + 16));
    free((void *)v4);
  }
  ptNext = ptQTask[3].ptNext;
  *(_DWORD *)&ptQTask[2].eQTaskType = 0;
  if ( ptNext )
  {
    --Mem_nCurrentAllocations;
    v6 = *(_DWORD *)((unsigned int)&ptNext[-1].eQTaskType & 0xFFFFFFFC);
    Node_Remove((_DWORD **)v6);
    memset(*(void **)(v6 + 8), 0xCDu, *(_DWORD *)(v6 + 16));
    free((void *)v6);
  }
  ptMiddle = ptQTask[3].tQTaskChildren.ptMiddle;
  ptQTask[3].ptNext = nullptr;
  if ( ptMiddle )
  {
    --Mem_nCurrentAllocations;
    v8 = *(_DWORD *)((unsigned int)&ptMiddle[-1].eQTaskType & 0xFFFFFFFC);
    Node_Remove((_DWORD **)v8);
    memset(*(void **)(v8 + 8), 0xCDu, *(_DWORD *)(v8 + 16));
    free((void *)v8);
  }
  ptPrev = ptQTask[3].ptPrev;
  ptQTask[3].tQTaskChildren.ptMiddle = nullptr;
  if ( ptPrev )
  {
    --Mem_nCurrentAllocations;
    v10 = *(_DWORD *)((unsigned int)&ptPrev[-1].eQTaskType & 0xFFFFFFFC);
    Node_Remove((_DWORD **)v10);
    memset(*(void **)(v10 + 8), 0xCDu, *(_DWORD *)(v10 + 16));
    free((void *)v10);
  }
  ptHead = ptQTask[3].tQTaskChildren.ptHead;
  ptQTask[3].ptPrev = nullptr;
  if ( ptHead )
  {
    --Mem_nCurrentAllocations;
    v12 = *(_DWORD *)((unsigned int)&ptHead[-1].eQTaskType & 0xFFFFFFFC);
    Node_Remove((_DWORD **)v12);
    memset(*(void **)(v12 + 8), 0xCDu, *(_DWORD *)(v12 + 16));
    free((void *)v12);
  }
  v13 = ptQTask[4].ptParent;
  ptQTask[3].tQTaskChildren.ptHead = nullptr;
  World_RemoveDynCubeObj((struct World_s *)v13, (struct DynCubeObj_s *)ptQTask);
  Particle2DDynCubeObj_nMemSize += 88 * (-3 - (unsigned int)ptQTask[6].tQTaskChildren.ptTail);
}

// source: h/0/particle2ddyncubeobj.c:952  [anchor-mhash]
void __cdecl Particle2DDynCubeObj_RegisterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[20]; struct real64x3_t tPos; };
    char igi2_extent[44];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v2; // st5
  double v3; // rt0
  struct QTask_s *ptHead; // eax
  int v5; // edx
  struct QTask_s *v6; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // ecx
  int v8; // edx

  v2 = *(double *)&ptQTask[4].tQTaskRefList.ptMiddle + *(double *)&ptQTask[4].ptNext;
  v3 = *(double *)&ptQTask[4].tQTaskChildren.ptTail + *(double *)&ptQTask[3].ptParent;
  igi2_frame.tPos.vX = (*(double *)&ptQTask[4].tQTaskChildren.ptHead + *(double *)&ptQTask[3].tQTaskRefList.ptMiddle) * 0.5;
  igi2_frame.tPos.vY = v3 * 0.5;
  igi2_frame.tPos.vZ = v2 * 0.5;
  igi2_frame.ptDynCubeObj = Particle2DDynCubeObj_FindRadius((struct Particle2DDynCubeObj_s *)ptQTask);
  World_RegisterDynCubeObjFirstTimeRadius(
    *((struct World_s **)pxContext + 1),
    (struct DynCubeObj_s *)ptQTask,
    &igi2_frame.tPos,
    igi2_frame.ptDynCubeObj,
    WORLD_DYNCUBETREE_CATEGORY_MOBILE);
  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v5 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v6 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v6 = nullptr;
      QTask_atProtectedQTaskStack[v5].ptQTask = v6;
      pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRegisterQTaskEvent][ptHead->eQTaskType].pfHandler;
      v8 = v5 + 1;
      QTask_nProtectedQTaskStackOffset = v8;
      if ( pfHandler )
      {
        pfHandler(ptHead, pxContext);
        v8 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v8];
      v5 = v8 - 1;
      QTask_nProtectedQTaskStackOffset = v5;
    }
    while ( ptHead );
  }
}

// source: h/0/particle2ddyncubeobj.c:991  [size]
void __cdecl Particle2DDynCubeObj_RemoveHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptHead; // eax
  int v3; // edx
  struct QTask_s *v4; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // ecx
  int v6; // edx

  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v3 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v4 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v4 = nullptr;
      QTask_atProtectedQTaskStack[v3].ptQTask = v4;
      pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRemoveQTaskEvent][ptHead->eQTaskType].pfHandler;
      v6 = v3 + 1;
      QTask_nProtectedQTaskStackOffset = v6;
      if ( pfHandler )
      {
        pfHandler(ptHead, pxContext);
        v6 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v6];
      v3 = v6 - 1;
      QTask_nProtectedQTaskStackOffset = v3;
    }
    while ( ptHead );
  }
  World_RemoveDynCubeObj(*(struct World_s **)pxContext, (struct DynCubeObj_s *)ptQTask);
}

// source: h/0/particle2ddyncubeobj.c:1018  [anchor-hash]
void __cdecl Particle2DDynCubeObj_Open()
{
  __int16 v0; // ax
  unsigned __int16 v1; // si

  Particle2DDynCubeObj_eQTaskType = QTask_NewQTaskType("Particle2DDynCubeObjTask", 264, DynCubeObj_eQTaskType, 25, 0);
  v0 = QTask_NewQTaskEventFn(0, "Particle2DCollisionEvaluate");
  v1 = Particle2DDynCubeObj_eQTaskType;
  Particle2DDynCubeObj_eParticle2DCollisionEvaluateQTaskEvent = v0;
  QTask_LinkQTaskEventHandlerFn(Particle2DDynCubeObj_eQTaskType, 0, Particle2DDynCubeObj_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, Particle2DDynCubeObj_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, Particle2DDynCubeObj_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 5, Particle2DDynCubeObj_EnterHandler);
  QTask_LinkQTaskEventHandlerFn(v1, DynCubeObj_eDynCubeObjRegisterQTaskEvent, Particle2DDynCubeObj_RegisterHandler);
  QTask_LinkQTaskEventHandlerFn(v1, DynCubeObj_eDynCubeObjRemoveQTaskEvent, Particle2DDynCubeObj_RemoveHandler);
  Particle2DDynCubeObj_tRandomState.anRandom[0] = -624411820;
  Particle2DDynCubeObj_tRandomState.anRandom[1] = -896272554;
  Particle2DDynCubeObj_tRandomState.anRandom[2] = 430872269;
  Particle2DDynCubeObj_nMemSize = 0;
  Particle2DDynCubeObj_nMaxMemSize = 0;
}

// source: h/0/particle2ddyncubeobj.c:1057  [anchor-hash]
void __cdecl Particle2DDynCubeObj_Close()
{
  QTask_DeleteQTaskEvent(Particle2DDynCubeObj_eParticle2DCollisionEvaluateQTaskEvent);
  QTask_DeleteQTaskType(Particle2DDynCubeObj_eQTaskType);
  Particle2DDynCubeObj_eQTaskType = 512;
}

// source: h/0/particle2ddyncubeobj.c:1086  [size]
__int16 __cdecl Particle2DDynCubeObj_GetParticle2DCollisionEvaluateQTaskEvent()
{
  return Particle2DDynCubeObj_eParticle2DCollisionEvaluateQTaskEvent;
}

// source: h/0/particle2ddyncubeobj.c:1118  [anchor-callee]
struct QTask_s *__cdecl Particle2DDynCubeObj_New(
        struct QTask_s *ptParent,
        struct World_s *ptWorld,
        struct QSprite_s *ptQSprite,
        struct real32x3_t *ptAccel,
        struct real32x3_t *ptvRGB,
        struct real32x2_t *ptvSize,
        float vRange,
        int nTransparency,
        int nAnimDelta,
        float vSizeDelta,
        float vShinyness,
        int nMaxParticles,
        void (__cdecl *pfParticle2DCollisionCallback)(struct Particle2DCollisionContext_t *))
{
  struct QTask_s *v13; // ebx
  void *v14; // eax
  int v15; // ecx
  struct QTask_s *v16; // eax
  int v17; // edx
  struct QTask_s *v18; // eax
  int ptTail; // ecx
  int v20; // eax
  int v21; // ecx
  struct real64x3_t tVNull; // [esp+10h] [ebp-1Ch] BYREF

  memset(&tVNull, 0, sizeof(tVNull));
  v13 = QTask_NewFn(ptParent, Particle2DDynCubeObj_eQTaskType, nullptr);
  memset(&v13[1], 0, 0x48u);
  v13[2].tQTaskRefList.ptTail = (struct QReference_s *)5;
  World_RegisterDynCubeObjFirstTimeRadius(
    ptWorld,
    (struct DynCubeObj_s *)v13,
    &tVNull,
    4096.0,
    WORLD_DYNCUBETREE_CATEGORY_MOBILE);
  v13[6].tQTaskChildren.ptTail = (struct QTask_s *)nMaxParticles;
  v13[4].ptParent = (struct QTask_s *)ptWorld;
  *(struct real32x3_t *)&v13[5].ptPrev = *ptAccel;
  *(struct real32x3_t *)&v13[5].tQTaskChildren.ptTail = *ptvRGB;
  *(struct real32x2_t *)&v13[4].eQTaskType = *ptvSize;
  *(float *)&v13[5].ptParent = vRange;
  v13[6].tQTaskChildren.ptMiddle = (struct QTask_s *)nAnimDelta;
  v13[6].ptNext = (struct QTask_s *)(nTransparency | 0x40000);
  *(float *)&v13[5].eQTaskType = vSizeDelta;
  LOBYTE(v13[6].tQTaskRefList.ptHead) = 0;
  v13[3].tQTaskChildren.ptTail = (struct QTask_s *)ptQSprite;
  if ( ptQSprite->ptQTilemap )
    LOBYTE(v13[6].tQTaskRefList.ptHead) = 1;
  *(float *)&v13[5].tQTaskRefList.ptTail = vShinyness;
  v13[6].ptPrev = (struct QTask_s *)pfParticle2DCollisionCallback;
  v13[2].ptParent = (struct QTask_s *)Mem_AllocFn(88 * nMaxParticles, 4);
  v14 = Mem_AllocFn(4 * (int)v13[6].tQTaskChildren.ptTail, 4);
  v15 = 4 * (int)v13[6].tQTaskChildren.ptTail;
  *(_DWORD *)&v13[2].eQTaskType = v14;
  v16 = (struct QTask_s *)Mem_AllocFn(v15, 4);
  v17 = 120 * (int)v13[6].tQTaskChildren.ptTail;
  v13[3].tQTaskChildren.ptMiddle = v16;
  v13[3].ptNext = (struct QTask_s *)Mem_AllocFn(v17, 4);
  v13[3].ptPrev = (struct QTask_s *)Mem_AllocFn(24 * (int)v13[6].tQTaskChildren.ptTail, 4);
  v18 = (struct QTask_s *)Mem_AllocFn(24 * (int)v13[6].tQTaskChildren.ptTail, 4);
  ptTail = (int)v13[6].tQTaskChildren.ptTail;
  v13[3].tQTaskChildren.ptHead = v18;
  v20 = 0;
  if ( ptTail > 0 )
  {
    v21 = 0;
    do
    {
      *(_DWORD *)(*(_DWORD *)&v13[2].eQTaskType + 4 * v20++) = (char *)v13[2].ptParent + v21;
      v21 += 88;
    }
    while ( v20 < (int)v13[6].tQTaskChildren.ptTail );
  }
  Particle2DDynCubeObj_nMemSize += 88 * ((int)&v13[6].tQTaskChildren.ptTail->ptNext + 3);
  if ( Particle2DDynCubeObj_nMaxMemSize <= Particle2DDynCubeObj_nMemSize )
    Particle2DDynCubeObj_nMaxMemSize = Particle2DDynCubeObj_nMemSize;
  return v13;
}

// source: h/0/particle2ddyncubeobj.c:1227  [anchor-callee]
void __cdecl Particle2DDynCubeObj_AddParticle(
        struct QTask_s *ptQTask,
        struct real64x3_t *ptPos,
        struct real32x3_t *ptVel,
        float vIntensity,
        float vRotDelta,
        float vRotation,
        float vSize,
        int nLifeTime,
        int nFadeTime)
{
  struct QTask_s *ptHead; // eax
  int v10; // eax
  __int16 v11; // dx

  ptHead = ptQTask[6].tQTaskChildren.ptHead;
  if ( (int)ptHead < (int)ptQTask[6].tQTaskChildren.ptTail )
  {
    v10 = *(_DWORD *)(*(_DWORD *)&ptQTask[2].eQTaskType + 4 * (_DWORD)ptHead);
    qmemcpy((void *)v10, ptPos, 0x18u);
    qmemcpy((void *)(v10 + 64), ptPos, 0x18u);
    *(struct real32x3_t *)(v10 + 24) = *ptVel;
    v11 = dword_834DB98 + 1;
    *(_WORD *)(v10 + 36) = dword_834DB98;
    *(_WORD *)(v10 + 38) = nLifeTime;
    *(float *)(v10 + 48) = vIntensity;
    *(float *)(v10 + 56) = vRotation;
    *(float *)(v10 + 60) = vSize;
    LOWORD(dword_834DB98) = v11 % 16;
    *(float *)(v10 + 44) = vRotDelta;
    *(_WORD *)(v10 + 40) = 0;
    *(_WORD *)(v10 + 42) = 0;
    if ( nFadeTime )
      *(float *)(v10 + 52) = 1.0 / (double)nFadeTime;
    else
      *(_DWORD *)(v10 + 52) = 1065353216;
    ++*(int *)&ptQTask[6].tQTaskChildren.ptHead;
  }
}

// source: h/0/particle2ddyncubeobj.c:1308  [anchor-callee]
struct real32x3_t *__cdecl Particle2DDynCubeObj_AddConeParticle(
        struct QTask_s *ptQTask,
        struct real64x3_t *ptPos,
        struct real32x3_t *ptDir,
        float vMaxAngle,
        float vMinVel,
        float vMaxVel,
        float vIntensity,
        float vRotDelta,
        float vRotation,
        float vSize,
        int nLifeTime,
        int nFadeTime)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDest; };
    struct { char igi2_o1[8]; float vBeta; };
    struct { char igi2_o2[56]; struct real32x3_t tPartVel; };
    struct { char igi2_o3[68]; struct real32x9_t Real32x9_Multiply_tTemp; };
    struct { char igi2_o4[108]; struct real32x9_t tvRotation; };
    char igi2_extent[148];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  long double v12; // st7
  double v13; // st7
  double v14; // st6
  long double v15; // st7
  unsigned int v16; // edi
  unsigned int v17; // ebx
  unsigned int v18; // esi
  double v19; // st7
  int v20; // edi
  int v21; // ebx
  unsigned int v22; // esi
  int v23; // edi
  int v24; // ebx
  double v25; // st7
  long double vZ; // st6
  long double v27; // st3
  struct real32x3_t *result; // eax
  struct real32x3_t tvZ; // 0:^30.12
  struct real32x3_t tvY; // 0:^3C.12

  tvZ = *ptDir;
  if ( ptDir->vX != 0.0 || tvZ.vY != 0.0 || tvZ.vZ != 0.0 )
  {
    v12 = 1.0 / sqrt(tvZ.vX * tvZ.vX + tvZ.vY * tvZ.vY + tvZ.vZ * tvZ.vZ);
    tvZ.vX = tvZ.vX * v12;
    tvZ.vY = tvZ.vY * v12;
    tvZ.vZ = tvZ.vZ * v12;
  }
  v13 = 1.0;
  v14 = 0.0;
  if ( fabs(tvZ.vX) > 0.75 )
  {
    v13 = 0.0;
    v14 = 1.0;
  }
  igi2_frame.tPartVel.vX = tvZ.vZ * v14 - tvZ.vY * 0.0;
  igi2_frame.tPartVel.vY = -(v13 * tvZ.vZ - tvZ.vX * 0.0);
  igi2_frame.tPartVel.vZ = v13 * tvZ.vY - v14 * tvZ.vX;
  tvY = igi2_frame.tPartVel;
  if ( igi2_frame.tPartVel.vX != 0.0 || igi2_frame.tPartVel.vY != 0.0 || igi2_frame.tPartVel.vZ != 0.0 )
  {
    v15 = 1.0 / sqrt(igi2_frame.tPartVel.vX * igi2_frame.tPartVel.vX + igi2_frame.tPartVel.vY * igi2_frame.tPartVel.vY + igi2_frame.tPartVel.vZ * igi2_frame.tPartVel.vZ);
    tvY.vX = igi2_frame.tPartVel.vX * v15;
    tvY.vY = igi2_frame.tPartVel.vY * v15;
    tvY.vZ = igi2_frame.tPartVel.vZ * v15;
  }
  v16 = (Particle2DDynCubeObj_tRandomState.anRandom[0] >> 7) ^ Particle2DDynCubeObj_tRandomState.anRandom[2];
  v17 = v16 ^ Particle2DDynCubeObj_tRandomState.anRandom[1];
  v18 = (v16 ^ Particle2DDynCubeObj_tRandomState.anRandom[1]) + Particle2DDynCubeObj_tRandomState.anRandom[0];
  igi2_frame.tPartVel.vX = tvY.vY * tvZ.vZ - tvY.vZ * tvZ.vY;
  igi2_frame.tPartVel.vY = -(tvY.vX * tvZ.vZ - tvY.vZ * tvZ.vX);
  igi2_frame.tPartVel.vZ = tvY.vX * tvZ.vY - tvY.vY * tvZ.vX;
  v19 = (double)(unsigned __int16)((v16 ^ LOWORD(Particle2DDynCubeObj_tRandomState.anRandom[1]))
                                 + LOWORD(Particle2DDynCubeObj_tRandomState.anRandom[0]))
      * 0.0000152587890625;
  v20 = (v18 >> 7) ^ v16;
  v21 = v20 ^ v17;
  v22 = v21 + v18;
  igi2_frame.vBeta = 3.1415927410125732 - (double)(unsigned __int16)v22 * 0.0000152587890625 * 6.2831854820251465;
  igi2_frame.ptDest = vMaxAngle * 0.5 - v19 * vMaxAngle;
  Real32x9_Create(&igi2_frame.tvRotation, igi2_frame.ptDest, 0.0, igi2_frame.vBeta);
  v23 = (v22 >> 7) ^ v20;
  v24 = v23 ^ v21;
  Particle2DDynCubeObj_tRandomState.anRandom[0] = v24 + v22;
  Particle2DDynCubeObj_tRandomState.anRandom[2] = v23;
  Particle2DDynCubeObj_tRandomState.anRandom[1] = v24;
  igi2_frame.Real32x9_Multiply_tTemp.tX.vZ = igi2_frame.tvRotation.tX.vZ * igi2_frame.tPartVel.vX + igi2_frame.tvRotation.tY.vZ * tvY.vX + igi2_frame.tvRotation.tZ.vZ * tvZ.vX;
  igi2_frame.Real32x9_Multiply_tTemp.tY.vZ = igi2_frame.tvRotation.tX.vZ * igi2_frame.tPartVel.vY + igi2_frame.tvRotation.tY.vZ * tvY.vY + igi2_frame.tvRotation.tZ.vZ * tvZ.vY;
  igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ = igi2_frame.tvRotation.tX.vZ * igi2_frame.tPartVel.vZ + igi2_frame.tvRotation.tY.vZ * tvY.vZ + igi2_frame.tvRotation.tZ.vZ * tvZ.vZ;
  igi2_frame.tPartVel.vX = igi2_frame.Real32x9_Multiply_tTemp.tX.vZ;
  igi2_frame.tPartVel.vY = igi2_frame.Real32x9_Multiply_tTemp.tY.vZ;
  v25 = (double)(unsigned __int16)(v24 + v22) * 0.0000152587890625 * (vMaxVel - vMinVel) + vMinVel;
  vZ = igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ;
  if ( igi2_frame.Real32x9_Multiply_tTemp.tX.vZ != 0.0
    || igi2_frame.Real32x9_Multiply_tTemp.tY.vZ != 0.0
    || igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ != 0.0 )
  {
    v27 = sqrt(
            igi2_frame.Real32x9_Multiply_tTemp.tX.vZ * igi2_frame.Real32x9_Multiply_tTemp.tX.vZ
          + igi2_frame.Real32x9_Multiply_tTemp.tY.vZ * igi2_frame.Real32x9_Multiply_tTemp.tY.vZ
          + igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ * igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ);
    igi2_frame.tPartVel.vX = igi2_frame.Real32x9_Multiply_tTemp.tX.vZ * (1.0 / v27);
    igi2_frame.tPartVel.vY = igi2_frame.Real32x9_Multiply_tTemp.tY.vZ * (1.0 / v27);
    vZ = 1.0 / v27 * igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ;
  }
  igi2_frame.tPartVel.vX = igi2_frame.tPartVel.vX * v25;
  igi2_frame.tPartVel.vY = igi2_frame.tPartVel.vY * v25;
  igi2_frame.tPartVel.vZ = vZ * v25;
  Particle2DDynCubeObj_AddParticle(
    ptQTask,
    ptPos,
    &igi2_frame.tPartVel,
    vIntensity,
    vRotDelta,
    vRotation,
    vSize,
    nLifeTime,
    nFadeTime);
  return result;
}

// source: h/0/particle2ddyncubeobj.c:1388  [size]
void __cdecl Particle2DDynCubeObj_SetDestruct(struct QTask_s *ptQTask, int isSelfDestruct)
{
  BYTE1(ptQTask[6].tQTaskRefList.ptHead) = isSelfDestruct;
}

// source: h/0/particle2ddyncubeobj.c:1406  [anchor-mhash]
void __cdecl Particle2DDynCubeObj_SetIntensity(struct QTask_s *ptQTask, float vIntensity)
{
  int i; // eax

  for ( i = 0; i < (int)ptQTask[6].tQTaskChildren.ptHead; ++i )
    *(float *)(*(_DWORD *)(*(_DWORD *)&ptQTask[2].eQTaskType + 4 * i) + 48) = vIntensity;
}

// source: h/0/particle2ddyncubeobj.c:1434  [size]
void __cdecl Particle2DDynCubeObj_SetRange(struct QTask_s *ptQTask, float vRange)
{
  *(float *)&ptQTask[5].ptParent = vRange;
}

// source: h/0/particle2ddyncubeobj.c:1450  [anchor-callee]
void __cdecl Particle2DDynCubeObj_MoveParticles(
        struct QTask_s *ptQTask,
        struct real64x3_t *ptMove)
{
  int i; // ecx
  double *v3; // eax

  for ( i = 0; i < (int)ptQTask[6].tQTaskChildren.ptHead; v3[2] = v3[2] + ptMove->vZ )
  {
    v3 = *(double **)(*(_DWORD *)&ptQTask[2].eQTaskType + 4 * i++);
    *v3 = *v3 + ptMove->vX;
    v3[1] = ptMove->vY + v3[1];
  }
}

// source: h/0/particle2ddyncubeobj.c:1476  [size]
struct QTask_s *__cdecl Particle2DDynCubeObj_RemoveParticles(struct QTask_s *ptQTask)
{
  ptQTask[6].tQTaskChildren.ptHead = nullptr;
  return ptQTask;
}
