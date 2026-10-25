/* g/0/wing.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: g/0/wing.c:42  [anchor-callee]
void __cdecl Wing_ApplyAirResistance(
        struct Wing_t *ptWingList,
        int nWings,
        float vARCoeff,
        struct Physics_s *ptPhysics,
        struct real32x9_t *ptOrientation,
        struct real32x3_t *ptWindVel)
{
  #pragma pack(push, 1)
  union
  {
    struct { int nWing; };
    struct { char igi2_o1[4]; int v45; };
    struct { char igi2_o2[12]; float tARForcea; };
    struct { char igi2_o3[12]; float tARForceb; };
    struct { char igi2_o4[12]; float tARForcec; };
    struct { char igi2_o5[12]; float tARForced; };
    struct { char igi2_o6[12]; float tARForcee; };
    struct { char igi2_o7[12]; float tARForcef; };
    struct { char igi2_o8[12]; float tARForceg; };
    struct { char igi2_o9[16]; float tARForce_4a; };
    struct { char igi2_o10[16]; float tARForce_4b; };
    struct { char igi2_o11[16]; float tARForce_4c; };
    struct { char igi2_o12[16]; float tARForce_4d; };
    struct { char igi2_o13[20]; float tARForce_8a; };
    struct { char igi2_o14[20]; float tARForce_8b; };
    struct { char igi2_o15[24]; struct real32x3_t tWindDir; };
    struct { char igi2_o16[36]; struct PointForce_s tPointForce; };
    char igi2_extent[60];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double vY; // st7
  double vZ; // st7
  double v8; // st7
  long double v9; // st7
  int v10; // eax
  float *p_vZ; // edx
  double v12; // st7
  double v13; // st6
  float v14; // eax
  float v15; // ecx
  double v16; // st7
  double v17; // st7
  double v18; // st6
  float v19; // ecx
  float v20; // eax
  double v21; // st7
  double v22; // st6
  int nForces; // eax
  double v24; // st7
  double v25; // st6
  float v26; // eax
  float v27; // ecx
  double v28; // st7
  double v29; // st7
  double v30; // st6
  float v31; // ecx
  float v32; // eax
  double v33; // st7
  double v34; // st6
  int v35; // eax
  bool v36; // cc
  float *v37; // edx
  int v38; // ebp
  double v39; // st7
  double v40; // st6
  float v41; // eax
  float v42; // ecx
  double v43; // st7
  float vARCoeffa = *(float *)&vARCoeff; // [esp+54h] [ebp+Ch] ARGSLOT
  struct real32x3_t tARForce; // 0:^18.12
  struct real32x3_t struct_real32x3_t; // 0:^18.12
  struct real32x3_t struct_real32x3_ta; // 0:^18.12
  struct real32x3_t struct_real32x3_tb; // 0:^18.12

  tARForce.vX = ptOrientation->tZ.vX * ptWindVel->vZ
              + ptOrientation->tY.vX * ptWindVel->vY
              + ptOrientation->tX.vX * ptWindVel->vX;
  vY = ptOrientation->tZ.vY;
  igi2_frame.tWindDir.vX = tARForce.vX;
  tARForce.vY = vY * ptWindVel->vZ + ptOrientation->tX.vY * ptWindVel->vX + ptOrientation->tY.vY * ptWindVel->vY;
  vZ = ptOrientation->tZ.vZ;
  igi2_frame.tWindDir.vY = tARForce.vY;
  tARForce.vZ = vZ * ptWindVel->vZ + ptOrientation->tX.vZ * ptWindVel->vX + ptOrientation->tY.vZ * ptWindVel->vY;
  igi2_frame.tWindDir.vZ = tARForce.vZ;
  v8 = Real32x3_FastLen(&igi2_frame.tWindDir);
  vARCoeffa = v8 * v8 * vARCoeff;
  if ( vARCoeffa > 0.0 )
  {
    igi2_frame.tWindDir = tARForce;
    if ( tARForce.vX != 0.0 || tARForce.vY != 0.0 || tARForce.vZ != 0.0 )
    {
      v9 = 1.0 / sqrt(tARForce.vX * tARForce.vX + tARForce.vY * tARForce.vY + tARForce.vZ * tARForce.vZ);
      igi2_frame.tWindDir.vX = tARForce.vX * v9;
      igi2_frame.tWindDir.vY = igi2_frame.tWindDir.vY * v9;
      igi2_frame.tWindDir.vZ = igi2_frame.tWindDir.vZ * v9;
    }
    v10 = 0;
    igi2_frame.nWing = 0;
    if ( nWings >= 4 )
    {
      igi2_frame.v45 = 3;
      p_vZ = &ptWingList->tNormal.vZ;
      do
      {
        if ( *(p_vZ - 3) > 0.0 )
        {
          v12 = igi2_frame.tWindDir.vY * *(p_vZ - 1);
          igi2_frame.tPointForce.tPoint.vX = p_vZ[1];
          v13 = igi2_frame.tWindDir.vZ * *p_vZ;
          v14 = p_vZ[3];
          igi2_frame.tPointForce.tPoint.vY = p_vZ[2];
          igi2_frame.tARForcea = *(p_vZ - 2);
          v15 = *p_vZ;
          igi2_frame.tPointForce.tPoint.vZ = v14;
          v16 = (v12 + v13 + igi2_frame.tWindDir.vX * igi2_frame.tARForcea) * *(p_vZ - 3) * vARCoeffa;
          struct_real32x3_t.vX = igi2_frame.tARForcea * v16;
          struct_real32x3_t.vY = *(p_vZ - 1) * v16;
          struct_real32x3_t.vZ = v15 * v16;
          igi2_frame.tPointForce.tForce = struct_real32x3_t;
          qmemcpy(
            &ptPhysics->ptForces[ptPhysics->nForces++],
            &igi2_frame.tPointForce,
            sizeof(ptPhysics->ptForces[ptPhysics->nForces++]));
        }
        if ( p_vZ[4] > 0.0 )
        {
          v17 = igi2_frame.tWindDir.vZ * p_vZ[7];
          igi2_frame.tPointForce.tPoint.vX = p_vZ[8];
          v18 = igi2_frame.tWindDir.vY * p_vZ[6];
          v19 = p_vZ[10];
          igi2_frame.tPointForce.tPoint.vY = p_vZ[9];
          igi2_frame.tARForceb = p_vZ[5];
          v20 = p_vZ[7];
          igi2_frame.tPointForce.tPoint.vZ = v19;
          igi2_frame.tARForce_4a = p_vZ[6];
          v21 = (v17 + v18 + igi2_frame.tWindDir.vX * igi2_frame.tARForceb) * p_vZ[4] * vARCoeffa;
          igi2_frame.tARForcec = igi2_frame.tARForceb * v21;
          igi2_frame.tPointForce.tForce.vX = igi2_frame.tARForcec;
          igi2_frame.tARForce_4b = igi2_frame.tARForce_4a * v21;
          igi2_frame.tPointForce.tForce.vY = igi2_frame.tARForce_4b;
          v22 = v20 * v21;
          nForces = ptPhysics->nForces;
          igi2_frame.tARForce_8a = v22;
          igi2_frame.tPointForce.tForce.vZ = igi2_frame.tARForce_8a;
          qmemcpy(&ptPhysics->ptForces[nForces], &igi2_frame.tPointForce, sizeof(ptPhysics->ptForces[nForces]));
          ++ptPhysics->nForces;
        }
        if ( p_vZ[11] > 0.0 )
        {
          v24 = igi2_frame.tWindDir.vZ * p_vZ[14];
          igi2_frame.tPointForce.tPoint.vX = p_vZ[15];
          v25 = igi2_frame.tWindDir.vY * p_vZ[13];
          v26 = p_vZ[17];
          igi2_frame.tPointForce.tPoint.vY = p_vZ[16];
          igi2_frame.tARForced = p_vZ[12];
          v27 = p_vZ[14];
          igi2_frame.tPointForce.tPoint.vZ = v26;
          v28 = (v24 + v25 + igi2_frame.tWindDir.vX * igi2_frame.tARForced) * p_vZ[11] * vARCoeffa;
          struct_real32x3_ta.vX = igi2_frame.tARForced * v28;
          struct_real32x3_ta.vY = p_vZ[13] * v28;
          struct_real32x3_ta.vZ = v27 * v28;
          igi2_frame.tPointForce.tForce = struct_real32x3_ta;
          qmemcpy(
            &ptPhysics->ptForces[ptPhysics->nForces++],
            &igi2_frame.tPointForce,
            sizeof(ptPhysics->ptForces[ptPhysics->nForces++]));
        }
        if ( p_vZ[18] > 0.0 )
        {
          v29 = igi2_frame.tWindDir.vZ * p_vZ[21];
          igi2_frame.tPointForce.tPoint.vX = p_vZ[22];
          v30 = igi2_frame.tWindDir.vY * p_vZ[20];
          v31 = p_vZ[24];
          igi2_frame.tPointForce.tPoint.vY = p_vZ[23];
          igi2_frame.tARForcee = p_vZ[19];
          v32 = p_vZ[21];
          igi2_frame.tPointForce.tPoint.vZ = v31;
          igi2_frame.tARForce_4c = p_vZ[20];
          v33 = (v29 + v30 + igi2_frame.tWindDir.vX * igi2_frame.tARForcee) * p_vZ[18] * vARCoeffa;
          igi2_frame.tARForcef = igi2_frame.tARForcee * v33;
          igi2_frame.tPointForce.tForce.vX = igi2_frame.tARForcef;
          igi2_frame.tARForce_4d = igi2_frame.tARForce_4c * v33;
          igi2_frame.tPointForce.tForce.vY = igi2_frame.tARForce_4d;
          v34 = v32 * v33;
          v35 = ptPhysics->nForces;
          igi2_frame.tARForce_8b = v34;
          igi2_frame.tPointForce.tForce.vZ = igi2_frame.tARForce_8b;
          qmemcpy(&ptPhysics->ptForces[v35], &igi2_frame.tPointForce, sizeof(ptPhysics->ptForces[v35]));
          ++ptPhysics->nForces;
        }
        v10 = igi2_frame.nWing + 4;
        p_vZ += 28;
        v36 = igi2_frame.v45 + 4 < nWings;
        igi2_frame.nWing += 4;
        igi2_frame.v45 += 4;
      }
      while ( v36 );
    }
    if ( v10 < nWings )
    {
      v37 = &ptWingList[v10].tNormal.vZ;
      v38 = nWings - v10;
      do
      {
        if ( *(v37 - 3) > 0.0 )
        {
          v39 = igi2_frame.tWindDir.vY * *(v37 - 1);
          igi2_frame.tPointForce.tPoint.vX = v37[1];
          v40 = igi2_frame.tWindDir.vZ * *v37;
          v41 = v37[3];
          igi2_frame.tPointForce.tPoint.vY = v37[2];
          igi2_frame.tARForceg = *(v37 - 2);
          v42 = *v37;
          igi2_frame.tPointForce.tPoint.vZ = v41;
          v43 = (v39 + v40 + igi2_frame.tWindDir.vX * igi2_frame.tARForceg) * *(v37 - 3) * vARCoeffa;
          struct_real32x3_tb.vX = igi2_frame.tARForceg * v43;
          struct_real32x3_tb.vY = *(v37 - 1) * v43;
          struct_real32x3_tb.vZ = v42 * v43;
          igi2_frame.tPointForce.tForce = struct_real32x3_tb;
          qmemcpy(
            &ptPhysics->ptForces[ptPhysics->nForces++],
            &igi2_frame.tPointForce,
            sizeof(ptPhysics->ptForces[ptPhysics->nForces++]));
        }
        v37 += 7;
        --v38;
      }
      while ( v38 );
    }
  }
}

// source: g/0/wing.c:124  [anchor-mhash]
void __cdecl Wing_Init(
        struct Wing_t *ptWing,
        float vArea,
        float vPosX,
        float vPosY,
        float vPosZ,
        float vNormalX,
        float vNormalY,
        float vNormalZ)
{
  long double v8; // st7
  struct real32x3_t tNormal; // 0:^0.12

  tNormal.vX = vNormalX;
  tNormal.vZ = vNormalZ;
  tNormal.vY = vNormalY;
  if ( vNormalX != 0.0 || vNormalY != 0.0 || vNormalZ != 0.0 )
  {
    v8 = 1.0 / sqrt(vNormalX * vNormalX + vNormalY * vNormalY + vNormalZ * vNormalZ);
    tNormal.vX = vNormalX * v8;
    tNormal.vY = vNormalY * v8;
    tNormal.vZ = vNormalZ * v8;
  }
  ptWing->tNormal = tNormal;
  ptWing->tPos.vX = vPosX;
  ptWing->tPos.vY = vPosY;
  ptWing->tPos.vZ = vPosZ;
  ptWing->vArea = vArea;
}
