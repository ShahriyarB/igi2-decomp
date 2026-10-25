/* j/0/effects/birdflock.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/effects/birdflock.c:103  [anchor-mhash]
void __cdecl BirdFlock_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct World_s *ptWorld; // eax
  struct DynCubeObj_s *ptManualRedrawList; // ecx
  struct DynCubeObj_s *ptPrev; // ecx
  struct QTask_s *v5; // edx
  struct QTask_s *v6; // ecx
  struct QTask_s **p_ptTail; // eax
  int v8; // esi
  struct QTask_s **p_ptMiddle; // ecx
  struct World_s *v10; // esi
  struct QTask_s *v11; // eax
  struct real32x9_t tOrientation; // [esp+10h] [ebp-28h] BYREF

  ptQTask[3].ptParent = (struct QTask_s *)1;
  *(_DWORD *)&ptQTask[3].eQTaskType = 1;
  ptWorld = Game_ptGame->ptWorld;
  ptManualRedrawList = ptWorld->ptManualRedrawList;
  if ( ptManualRedrawList )
  {
    ptManualRedrawList->ptPrev = (struct DynCubeObj_s *)ptQTask;
    ptWorld->ptManualRedrawList->ptPrev->ptNext = ptWorld->ptManualRedrawList;
    ptPrev = ptWorld->ptManualRedrawList->ptPrev;
    ptWorld->ptManualRedrawList = ptPrev;
    ptPrev->ptPrev = nullptr;
  }
  else
  {
    ptWorld->ptManualRedrawList = (struct DynCubeObj_s *)ptQTask;
    ptQTask[2].tQTaskChildren.ptTail = nullptr;
    ptWorld->ptManualRedrawList->ptPrev = nullptr;
  }
  v5 = ptQTask + 484;
  ptQTask[2].ptParent = nullptr;
  *(_DWORD *)&ptQTask[2].eQTaskType = 0;
  ptQTask[3].ptNext = nullptr;
  ptQTask[3].ptPrev = nullptr;
  ptQTask[3].tQTaskChildren.ptHead = nullptr;
  ptQTask[3].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[3].tQTaskRefList.ptHead = (struct QReference_s *)1120403456;
  ptQTask[3].tQTaskRefList.ptMiddle = (struct QReference_s *)1148846080;
  ptQTask[3].tQTaskRefList.ptTail = (struct QReference_s *)10;
  ptQTask[484].ptNext = nullptr;
  ptQTask[484].ptPrev = nullptr;
  ptQTask[484].tQTaskChildren.ptHead = nullptr;
  v6 = ptQTask + 124;
  p_ptTail = &ptQTask[484].tQTaskChildren.ptTail;
  v8 = 400;
  do
  {
    *(p_ptTail - 1) = v6;
    p_ptMiddle = &v6->tQTaskChildren.ptMiddle;
    *p_ptTail = (struct QTask_s *)p_ptMiddle;
    p_ptMiddle += 3;
    p_ptTail[1] = (struct QTask_s *)p_ptMiddle;
    p_ptTail[2] = v5;
    p_ptTail[3] = v5;
    p_ptTail[4] = v5;
    p_ptTail[5] = nullptr;
    p_ptTail[6] = nullptr;
    p_ptTail[7] = nullptr;
    p_ptTail[8] = nullptr;
    p_ptTail[9] = nullptr;
    p_ptTail[10] = nullptr;
    p_ptTail[11] = (struct QTask_s *)1065353216;
    p_ptTail[12] = (struct QTask_s *)1065353216;
    p_ptTail[13] = (struct QTask_s *)1065353216;
    p_ptTail[18] = nullptr;
    p_ptTail[17] = nullptr;
    p_ptTail[14] = nullptr;
    p_ptTail[15] = nullptr;
    p_ptTail[16] = (struct QTask_s *)1065353216;
    v6 = (struct QTask_s *)(p_ptMiddle + 3);
    p_ptTail += 20;
    --v8;
  }
  while ( v8 );
  v10 = Game_ptGame->ptWorld;
  tOrientation.tX.vX = 1.0;
  memset(&tOrientation.tX.vY, 0, 12);
  tOrientation.tY.vY = 1.0;
  memset(&tOrientation.tY.vZ, 0, 12);
  tOrientation.tZ.vZ = 1.0;
  tOrientation.nOps = 0;
  v11 = QTask_NewFn(nullptr, PolyListDynCubeObj_eQTaskType, nullptr);
  *(_DWORD *)&v11[2].eQTaskType = (char *)ptQTask + 19372;
  v11[2].ptParent = (struct QTask_s *)v10;
  v11[4].tQTaskChildren.ptMiddle = (struct QTask_s *)1;
  v11[4].ptParent = (struct QTask_s *)1;
  v11[4].tQTaskChildren.ptHead = nullptr;
  v11[4].tQTaskChildren.ptTail = nullptr;
  v11[4].tQTaskRefList.ptHead = nullptr;
  v11[4].tQTaskRefList.ptTail = nullptr;
  v11[4].tQTaskRefList.ptMiddle = nullptr;
  v11[4].ptNext = nullptr;
  *(_DWORD *)&v11[4].eQTaskType = 0;
  v11[4].ptPrev = (struct QTask_s *)400;
  qmemcpy(&v11[1], &ptQTask[2].ptParent, 0x18u);
  qmemcpy(&v11[3], &tOrientation, sizeof(struct QTask_s));
  ptQTask[1284].tQTaskChildren.ptTail = nullptr;
  ptQTask[1284].tQTaskChildren.ptMiddle = v11;
}

// source: j/0/effects/birdflock.c:180  [anchor-mhash]
void __cdecl BirdFlock_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptMiddle; // eax
  struct QTask_s *ptTail; // eax

  QTask_Delete(ptQTask[1284].tQTaskChildren.ptMiddle);
  if ( *(_DWORD *)&ptQTask[3].eQTaskType )
  {
    ptMiddle = ptQTask[2].tQTaskChildren.ptMiddle;
    if ( ptMiddle )
      ptMiddle[2].tQTaskChildren.ptTail = ptQTask[2].tQTaskChildren.ptTail;
    else
      Game_ptGame->ptWorld->ptManualRedrawList = (struct DynCubeObj_s *)ptQTask[2].tQTaskChildren.ptTail;
    ptTail = ptQTask[2].tQTaskChildren.ptTail;
    if ( ptTail )
      ptTail[2].tQTaskChildren.ptMiddle = ptQTask[2].tQTaskChildren.ptMiddle;
  }
}

// source: j/0/effects/birdflock.c:202  [anchor-mhash]
void __cdecl BirdFlock_RunHandler(struct QTask_s *ptQTask)
{
  int v1; // ebx
  float *p_ptMiddle; // ecx
  int v3; // edx
  int v4; // eax
  unsigned int v5; // edx
  int v6; // edx
  int v7; // eax
  unsigned int v8; // edx
  int v9; // edx
  int v10; // eax
  unsigned int v11; // edx
  double v12; // st7
  double v13; // st3
  double v14; // st6
  double v15; // st3
  double v16; // st7
  double v17; // st6
  double v18; // st5
  long double v19; // st7
  int v20; // [esp+10h] [ebp-30h]
  float v21; // [esp+10h] [ebp-30h]
  float vRadiusScale; // [esp+18h] [ebp-28h]
  float vRadius; // [esp+1Ch] [ebp-24h]
  float vAngle2; // [esp+20h] [ebp-20h]
  int vAngle2a; // [esp+20h] [ebp-20h]
  float vAngle3; // [esp+28h] [ebp-18h]
  float tPos; // [esp+34h] [ebp-Ch]
  float tPos_4; // [esp+38h] [ebp-8h]
  float tPos_8; // [esp+3Ch] [ebp-4h]

  vRadius = *(float *)&ptQTask[3].tQTaskRefList.ptHead * 4096.0;
  vRadiusScale = *(float *)&ptQTask[3].tQTaskRefList.ptHead * 0.019999999552965164;
  if ( ptQTask[3].ptParent )
  {
    v1 = 0;
    if ( (int)ptQTask[3].tQTaskRefList.ptTail > 0 )
    {
      p_ptMiddle = (float *)&ptQTask[4].tQTaskRefList.ptMiddle;
      do
      {
        v3 = *((_DWORD *)p_ptMiddle + 1);
        v4 = *(_DWORD *)p_ptMiddle + 1;
        *(_DWORD *)p_ptMiddle = v4;
        if ( v4 > v3 )
        {
          *p_ptMiddle = 0.0;
          v5 = (Flock_tRandomState.anRandom[0] >> 7) ^ Flock_tRandomState.anRandom[2];
          Flock_tRandomState.anRandom[0] += v5 ^ Flock_tRandomState.anRandom[1];
          Flock_tRandomState.anRandom[2] = v5;
          Flock_tRandomState.anRandom[1] ^= v5;
          *((_DWORD *)p_ptMiddle + 1) = (__int64)(((double)LOWORD(Flock_tRandomState.anRandom[0])
                                                 * 0.0000152587890625
                                                 * 40.0
                                                 + 20.0)
                                                * vRadiusScale
                                                * 30.0);
        }
        v6 = *((_DWORD *)p_ptMiddle + 3);
        v7 = *((_DWORD *)p_ptMiddle + 2) + 1;
        *((_DWORD *)p_ptMiddle + 2) = v7;
        if ( v7 > v6 )
        {
          p_ptMiddle[2] = 0.0;
          v8 = (Flock_tRandomState.anRandom[0] >> 7) ^ Flock_tRandomState.anRandom[2];
          Flock_tRandomState.anRandom[0] += v8 ^ Flock_tRandomState.anRandom[1];
          Flock_tRandomState.anRandom[2] = v8;
          Flock_tRandomState.anRandom[1] ^= v8;
          *((_DWORD *)p_ptMiddle + 3) = (__int64)(((double)LOWORD(Flock_tRandomState.anRandom[0])
                                                 * 0.0000152587890625
                                                 * 40.0
                                                 + 20.0)
                                                * vRadiusScale
                                                * 30.0);
        }
        v9 = *((_DWORD *)p_ptMiddle + 5);
        v10 = *((_DWORD *)p_ptMiddle + 4) + 1;
        *((_DWORD *)p_ptMiddle + 4) = v10;
        if ( v10 > v9 )
        {
          p_ptMiddle[4] = 0.0;
          v11 = (Flock_tRandomState.anRandom[0] >> 7) ^ Flock_tRandomState.anRandom[2];
          Flock_tRandomState.anRandom[0] += v11 ^ Flock_tRandomState.anRandom[1];
          Flock_tRandomState.anRandom[2] = v11;
          Flock_tRandomState.anRandom[1] ^= v11;
          *((_DWORD *)p_ptMiddle + 5) = (__int64)(((double)LOWORD(Flock_tRandomState.anRandom[0])
                                                 * 0.0000152587890625
                                                 * 40.0
                                                 + 20.0)
                                                * vRadiusScale
                                                * 30.0);
        }
        vAngle2 = (double)*((int *)p_ptMiddle + 2) / (double)*((int *)p_ptMiddle + 3) + 3.1415927410125732;
        vAngle3 = (double)*((int *)p_ptMiddle + 4) / (double)*((int *)p_ptMiddle + 5) + 3.1415927410125732;
        v12 = ((double)*(int *)p_ptMiddle / (double)*((int *)p_ptMiddle + 1) + 3.1415927410125732) * 4096.0;
        v20 = (__int64)v12;
        v13 = vAngle2 * 4096.0;
        tPos = ((v12 - (double)v20) * Real32_avSin[v20 & 0xFFF].vY
              + (v13 - (double)(int)(__int64)v13) * Real32_avSin[(__int64)v13 & 0xFFF].vY
              + Real32_avSin[v20 & 0xFFF].vX
              + Real32_avSin[(__int64)v13 & 0xFFF].vX)
             * vRadius;
        vAngle2a = (__int64)v13;
        v14 = v13 - (double)vAngle2a;
        v15 = vAngle3 * 4096.0;
        tPos_4 = (v14 * Real32_avSin[vAngle2a & 0xFFF].vY
                + (v15 - (double)(int)(__int64)v15) * Real32_avSin[(__int64)v15 & 0xFFF].vY
                + Real32_avSin[vAngle2a & 0xFFF].vX
                + Real32_avSin[(__int64)v15 & 0xFFF].vX)
               * vRadius;
        tPos_8 = ((v12 - (double)v20) * Real32_avSin[v20 & 0xFFF].vY
                + (v15 - (double)(int)(__int64)v15) * Real32_avSin[(__int64)v15 & 0xFFF].vY
                + Real32_avSin[(__int64)v15 & 0xFFF].vX
                + Real32_avSin[v20 & 0xFFF].vX)
               * 40960.0;
        v16 = tPos - *(p_ptMiddle - 6);
        *(p_ptMiddle - 3) = v16;
        v21 = tPos_4 - *(p_ptMiddle - 5);
        v17 = tPos_8 - *(p_ptMiddle - 4);
        *(p_ptMiddle - 2) = v21;
        *(p_ptMiddle - 1) = v17;
        if ( v16 != 0.0 || v21 != 0.0 || v17 != 0.0 )
        {
          v18 = v16;
          v19 = 1.0 / sqrt(v16 * v16 + v21 * v21 + v17 * v17);
          *(p_ptMiddle - 3) = v18 * v19;
          *(p_ptMiddle - 2) = v21 * v19;
          *(p_ptMiddle - 1) = v17 * v19;
        }
        *(p_ptMiddle - 6) = tPos;
        *(p_ptMiddle - 5) = tPos_4;
        *(p_ptMiddle - 4) = tPos_8;
        ++v1;
        p_ptMiddle += 12;
      }
      while ( v1 < (int)ptQTask[3].tQTaskRefList.ptTail );
    }
  }
}

// source: j/0/effects/birdflock.c:271  [anchor-mhash]
void __cdecl BirdFlock_EnterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float tNormalY; };
    struct { char igi2_o1[4]; float tNormalY_4; };
    struct { char igi2_o2[4]; float tNormalY_4a; };
    struct { char igi2_o3[8]; float tNormalY_8; };
    struct { char igi2_o4[12]; struct real32x2_t tScreenPos; };
    struct { char igi2_o5[20]; int vDepth; };
    struct { char igi2_o6[24]; struct real32x3_t tPos3; };
    struct { char igi2_o7[36]; struct real32x3_t tPos1; };
    struct { char igi2_o8[48]; struct real32x3_t tPos4; };
    struct { char igi2_o9[60]; struct real32x3_t tPos2; };
    struct { char igi2_o10[72]; struct real32x3_t tPos6; };
    struct { char igi2_o11[84]; struct real32x3_t tNormalX; };
    struct { char igi2_o12[96]; struct real32x3_t tPos5; };
    struct { char igi2_o13[108]; struct real32x9_t tOrientation; };
    char igi2_extent[148];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v2; // ebx
  struct QReference_s *ptTail; // eax
  struct real32x3_t *p_ptMiddle; // ecx
  float *v5; // edx
  float v6; // eax
  long double v7; // st7
  long double v8; // st6
  long double v9; // st5
  long double v10; // rt0
  double v11; // st6
  double v12; // st7
  double v13; // st6
  double v14; // st4
  double v15; // st5
  float vY; // edi
  float vZ; // ebx
  float vX; // ebp
  float *p_vX; // esi
  float v20; // eax
  double v21; // st7
  float *v22; // esi
  float v23; // ebp
  float v24; // ebp
  struct QReference_s *v25; // esi
  struct QTask_s *v26; // edi

  v2 = ptQTask;
  TransContext_ProjectWorldPos2(
    &TransContext_tActiveTransContext,
    &igi2_frame.tScreenPos,
    (float *)&igi2_frame.vDepth,
    (struct real64x3_t *)&ptQTask[2].ptParent);
  if ( *(float *)&ptQTask[3].tQTaskRefList.ptMiddle * 4096.0 >= *(float *)&igi2_frame.vDepth )
  {
    ptTail = ptQTask[3].tQTaskRefList.ptTail;
    ptQTask[3].ptParent = (struct QTask_s *)1;
    *(float *)&igi2_frame.vDepth = 0.0;
    if ( (int)ptTail > 0 )
    {
      p_ptMiddle = (struct real32x3_t *)&ptQTask[124].tQTaskRefList.ptMiddle;
      v5 = (float *)&ptQTask[4].tQTaskChildren.ptMiddle;
      do
      {
        v6 = v5[2];
        igi2_frame.tNormalY_4a = v5[1];
        igi2_frame.tNormalY = *v5 * -819.2000122070312;
        igi2_frame.tNormalX.vZ = 0.0;
        igi2_frame.tNormalY_4 = igi2_frame.tNormalY_4a * -819.2000122070312;
        igi2_frame.tNormalY_8 = v6 * -819.2000122070312;
        v7 = v5[1];
        v8 = -*v5;
        if ( v7 != 0.0 || v8 != 0.0 )
        {
          v9 = 1.0 / sqrt(v7 * v7 + v8 * v8);
          v7 = v5[1] * v9;
          v8 = v8 * v9;
          igi2_frame.tNormalX.vZ = v9 * 0.0;
        }
        v10 = v8;
        igi2_frame.tNormalX.vX = v7 * 4096.0;
        v11 = igi2_frame.tNormalX.vZ * 4096.0;
        igi2_frame.tPos1.vX = igi2_frame.tNormalY + *(v5 - 3);
        igi2_frame.tPos1.vY = igi2_frame.tNormalY_4 + *(v5 - 2);
        igi2_frame.tPos1.vZ = igi2_frame.tNormalY_8 + *(v5 - 1);
        igi2_frame.tPos2.vX = *(v5 - 3) - igi2_frame.tNormalY;
        igi2_frame.tPos2.vY = *(v5 - 2) - igi2_frame.tNormalY_4;
        igi2_frame.tPos2.vZ = *(v5 - 1) - igi2_frame.tNormalY_8;
        igi2_frame.tPos3.vX = igi2_frame.tPos1.vX + igi2_frame.tNormalX.vX;
        igi2_frame.tPos3.vY = igi2_frame.tPos1.vY + v10 * 4096.0;
        igi2_frame.tPos3.vZ = igi2_frame.tPos1.vZ + v11;
        igi2_frame.tPos4.vX = igi2_frame.tPos1.vX - igi2_frame.tNormalX.vX;
        igi2_frame.tPos4.vY = igi2_frame.tPos1.vY - v10 * 4096.0;
        v12 = igi2_frame.tPos1.vZ - v11;
        igi2_frame.tPos5.vX = igi2_frame.tPos3.vX + igi2_frame.tNormalY;
        igi2_frame.tPos5.vY = igi2_frame.tPos3.vY + igi2_frame.tNormalY_4;
        v13 = igi2_frame.tPos3.vZ + igi2_frame.tNormalY_8;
        igi2_frame.tPos6.vX = igi2_frame.tPos4.vX + igi2_frame.tNormalY;
        igi2_frame.tPos6.vY = igi2_frame.tPos4.vY + igi2_frame.tNormalY_4;
        igi2_frame.tPos6.vZ = v12 + igi2_frame.tNormalY_8;
        v14 = (double)*((int *)v5 + 3) / (double)*((int *)v5 + 4) * 61440.0;
        igi2_frame.tScreenPos = (*(struct real32x2_t *)&(__int64){(__int64)v14});
        LODWORD(igi2_frame.tScreenPos.vX) = (__int64)v14;
        v15 = ((v14 - (double)SLODWORD(igi2_frame.tScreenPos.vX)) * Real32_avSin[LOWORD(igi2_frame.tScreenPos.vX) & 0xFFF].vY
             + Real32_avSin[LOWORD(igi2_frame.tScreenPos.vX) & 0xFFF].vX)
            * 3276.800048828125;
        igi2_frame.tScreenPos.vX = v15;
        igi2_frame.tPos3.vZ = v15 + igi2_frame.tPos3.vZ;
        igi2_frame.tPos4.vZ = igi2_frame.tScreenPos.vX + v12;
        vY = igi2_frame.tPos1.vY;
        igi2_frame.tPos5.vZ = igi2_frame.tScreenPos.vX + v13;
        vZ = igi2_frame.tPos1.vZ;
        vX = igi2_frame.tPos2.vX;
        p_vX = &p_ptMiddle[-2].vX;
        v20 = igi2_frame.tPos1.vX;
        v21 = igi2_frame.tScreenPos.vX + igi2_frame.tPos6.vZ;
        *p_vX = igi2_frame.tPos1.vX;
        p_vX[1] = vY;
        p_vX[2] = vZ;
        igi2_frame.tPos6.vZ = v21;
        v22 = &p_ptMiddle[-1].vX;
        *v22 = vX;
        v22[1] = igi2_frame.tPos2.vY;
        v22[2] = igi2_frame.tPos2.vZ;
        *p_ptMiddle = igi2_frame.tPos4;
        p_ptMiddle[1] = igi2_frame.tPos2;
        v23 = igi2_frame.tPos3.vX;
        p_ptMiddle[2].vX = v20;
        p_ptMiddle[2].vY = vY;
        p_ptMiddle[2].vZ = vZ;
        p_ptMiddle[3].vX = v23;
        p_ptMiddle[3].vY = igi2_frame.tPos3.vY;
        p_ptMiddle[3].vZ = igi2_frame.tPos3.vZ;
        v24 = igi2_frame.tPos5.vX;
        p_ptMiddle[4].vX = v20;
        p_ptMiddle[4].vY = vY;
        p_ptMiddle[4].vZ = vZ;
        p_ptMiddle[5].vX = v24;
        p_ptMiddle[5].vY = igi2_frame.tPos5.vY;
        p_ptMiddle[5].vZ = igi2_frame.tPos5.vZ;
        p_ptMiddle[6] = igi2_frame.tPos3;
        p_ptMiddle[7].vX = v20;
        p_ptMiddle[7].vY = vY;
        p_ptMiddle[7].vZ = vZ;
        p_ptMiddle[8] = igi2_frame.tPos4;
        p_ptMiddle[9] = igi2_frame.tPos6;
        v2 = ptQTask;
        v25 = ptQTask[3].tQTaskRefList.ptTail;
        v5 += 12;
        p_ptMiddle += 12;
        ++igi2_frame.vDepth;
      }
      while ( igi2_frame.vDepth < (int)v25 );
    }
    qmemcpy(&v2[1284].tQTaskChildren.ptMiddle[1], &v2[2].ptParent, 0x18u);
    v26 = v2[1284].tQTaskChildren.ptMiddle + 3;
    igi2_frame.tOrientation.tX.vX = 1.0;
    memset(&igi2_frame.tOrientation.tX.vY, 0, 12);
    igi2_frame.tOrientation.tY.vY = 1.0;
    memset(&igi2_frame.tOrientation.tY.vZ, 0, 12);
    igi2_frame.tOrientation.tZ.vZ = 1.0;
    igi2_frame.tOrientation.nOps = 0;
    qmemcpy(v26, &igi2_frame.tOrientation, sizeof(struct QTask_s));
    ((void (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[5][v2[1284].tQTaskChildren.ptMiddle->eQTaskType].pfHandler)(
      v2[1284].tQTaskChildren.ptMiddle,
      0);
  }
  else
  {
    ptQTask[3].ptParent = nullptr;
  }
}

// source: j/0/effects/birdflock.c:393  [size]
void __cdecl BirdFlock_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int ptTail; // eax
  int v3; // edx
  struct QTask_s **p_ptParent; // eax
  unsigned int v5; // esi
  unsigned int v6; // esi
  unsigned int v7; // esi

  ptTail = (int)ptQTask[3].tQTaskRefList.ptTail;
  if ( ptTail >= 100 )
    ptTail = 100;
  v3 = 0;
  ptQTask[3].tQTaskRefList.ptTail = (struct QReference_s *)ptTail;
  if ( ptTail > 0 )
  {
    p_ptParent = &ptQTask[4].ptParent;
    do
    {
      *(p_ptParent - 2) = nullptr;
      *p_ptParent = nullptr;
      p_ptParent[2] = nullptr;
      v5 = (Flock_tRandomState.anRandom[0] >> 7) ^ Flock_tRandomState.anRandom[2];
      Flock_tRandomState.anRandom[0] += v5 ^ Flock_tRandomState.anRandom[1];
      Flock_tRandomState.anRandom[2] = v5;
      Flock_tRandomState.anRandom[1] ^= v5;
      *(p_ptParent - 1) = (struct QTask_s *)(__int64)((double)LOWORD(Flock_tRandomState.anRandom[0])
                                                    * 0.0000152587890625
                                                    * 1200.0
                                                    + 40.0);
      v6 = (Flock_tRandomState.anRandom[0] >> 7) ^ Flock_tRandomState.anRandom[2];
      Flock_tRandomState.anRandom[0] += v6 ^ Flock_tRandomState.anRandom[1];
      Flock_tRandomState.anRandom[2] = v6;
      Flock_tRandomState.anRandom[1] ^= v6;
      p_ptParent[1] = (struct QTask_s *)(__int64)((double)LOWORD(Flock_tRandomState.anRandom[0])
                                                * 0.0000152587890625
                                                * 1200.0
                                                + 40.0);
      v7 = (Flock_tRandomState.anRandom[0] >> 7) ^ Flock_tRandomState.anRandom[2];
      Flock_tRandomState.anRandom[0] += v7 ^ Flock_tRandomState.anRandom[1];
      Flock_tRandomState.anRandom[2] = v7;
      Flock_tRandomState.anRandom[1] ^= v7;
      ++v3;
      p_ptParent += 12;
      *(p_ptParent - 9) = (struct QTask_s *)(__int64)((double)LOWORD(Flock_tRandomState.anRandom[0])
                                                    * 0.0000152587890625
                                                    * 1200.0
                                                    + 40.0);
    }
    while ( v3 < (int)ptQTask[3].tQTaskRefList.ptTail );
  }
}

// source: j/0/effects/birdflock.c:428  [size]
void __cdecl BirdFlock_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = Flock_ptParameterList;
}

// source: j/0/effects/birdflock.c:444  [anchor-mhash]
void __cdecl BirdFlock_RegisterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct World_s *ptWorld; // eax
  struct DynCubeObj_s *ptManualRedrawList; // ecx
  struct DynCubeObj_s *ptPrev; // ecx
  struct QTask_s *ptHead; // eax
  int v6; // edx
  struct QTask_s *v7; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // ecx
  int v9; // edx

  if ( !*(_DWORD *)&ptQTask[3].eQTaskType )
  {
    ptWorld = Game_ptGame->ptWorld;
    ptManualRedrawList = ptWorld->ptManualRedrawList;
    if ( ptManualRedrawList )
    {
      ptManualRedrawList->ptPrev = (struct DynCubeObj_s *)ptQTask;
      ptWorld->ptManualRedrawList->ptPrev->ptNext = ptWorld->ptManualRedrawList;
      ptPrev = ptWorld->ptManualRedrawList->ptPrev;
      ptWorld->ptManualRedrawList = ptPrev;
      ptPrev->ptPrev = nullptr;
    }
    else
    {
      ptWorld->ptManualRedrawList = (struct DynCubeObj_s *)ptQTask;
      ptQTask[2].tQTaskChildren.ptTail = nullptr;
      ptWorld->ptManualRedrawList->ptPrev = nullptr;
    }
    *(_DWORD *)&ptQTask[3].eQTaskType = 1;
  }
  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v6 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v7 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v7 = nullptr;
      QTask_atProtectedQTaskStack[v6].ptQTask = v7;
      pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRegisterQTaskEvent][ptHead->eQTaskType].pfHandler;
      v9 = v6 + 1;
      QTask_nProtectedQTaskStackOffset = v9;
      if ( pfHandler )
      {
        pfHandler(ptHead, pxContext);
        v9 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v9];
      v6 = v9 - 1;
      QTask_nProtectedQTaskStackOffset = v6;
    }
    while ( ptHead );
  }
}

// source: j/0/effects/birdflock.c:471  [anchor-mhash]
void __cdecl BirdFlock_RemoveHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptMiddle; // ecx
  struct QTask_s *ptTail; // ecx
  struct QTask_s *ptHead; // eax
  int v5; // edx
  struct QTask_s *v6; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // ecx
  int v8; // edx

  if ( *(_DWORD *)&ptQTask[3].eQTaskType )
  {
    ptMiddle = ptQTask[2].tQTaskChildren.ptMiddle;
    if ( ptMiddle )
      ptMiddle[2].tQTaskChildren.ptTail = ptQTask[2].tQTaskChildren.ptTail;
    else
      Game_ptGame->ptWorld->ptManualRedrawList = (struct DynCubeObj_s *)ptQTask[2].tQTaskChildren.ptTail;
    ptTail = ptQTask[2].tQTaskChildren.ptTail;
    if ( ptTail )
      ptTail[2].tQTaskChildren.ptMiddle = ptQTask[2].tQTaskChildren.ptMiddle;
    *(_DWORD *)&ptQTask[3].eQTaskType = 0;
  }
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
      pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRemoveQTaskEvent][ptHead->eQTaskType].pfHandler;
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

// source: j/0/effects/birdflock.c:500  [size]
unsigned __int16 __cdecl BirdFlock_GetQTaskType()
{
  return BirdFlock_eQTaskType;
}

// source: j/0/effects/birdflock.c:513  [anchor-hash]
void __cdecl BirdFlock_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax

  v0 = QTask_NewQTaskType("BirdFlock", 51384, DynCubeObj_eQTaskType, 0, 0);
  BirdFlock_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 0, BirdFlock_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, BirdFlock_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, BirdFlock_RunHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 5, BirdFlock_EnterHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, BirdFlock_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))BirdFlock_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, DynCubeObj_eDynCubeObjRegisterQTaskEvent, BirdFlock_RegisterHandler);
  QTask_LinkQTaskEventHandlerFn(v0, DynCubeObj_eDynCubeObjRemoveQTaskEvent, BirdFlock_RemoveHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  v1 = (struct ParameterList_s *)Mem_AllocFn(212, 4);
  v1->nParameters = 0;
  v1->nMaxParameters = 10;
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  Flock_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0x70u, Level_eParameterTypeObjectPos, "Position", 7u, nullptr);
  ParameterList_AddParameter(Flock_ptParameterList, 0x8Cu, Level_eParameterTypeReal32, "Radius (meter)", 7u, nullptr);
  ParameterList_AddParameter(
    Flock_ptParameterList,
    0x90u,
    Level_eParameterTypeReal32,
    "Cutoff Distance (meter)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Flock_ptParameterList,
    0x94u,
    Level_eParameterTypeInt32,
    "Individuals (max 100)",
    7u,
    nullptr);
  Flock_tRandomState.anRandom[0] = -227095208;
  Flock_tRandomState.anRandom[1] = 630847318;
  Flock_tRandomState.anRandom[2] = 1682079437;
}

// source: j/0/effects/birdflock.c:552  [size]
void __cdecl BirdFlock_Close()
{
  int v0; // esi

  if ( Flock_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&Flock_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(BirdFlock_eQTaskType);
}
