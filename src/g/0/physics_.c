/* g/0/physics_.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: g/0/physics_.c:39  [anchor-hash]
int __cdecl Physics_AllocPointForces(struct Physics_s *ptBody, int nMaxForces)
{
  ptBody->nMaxForces = nMaxForces;
  if ( nMaxForces <= 0 )
  {
    ptBody->ptForces = nullptr;
  }
  else
  {
    nMaxForces = (int)Mem_AllocFn(24 * nMaxForces, 4);
    ptBody->ptForces = (struct PointForce_s *)nMaxForces;
  }
  return nMaxForces;
}

// source: g/0/physics_.c:68  [anchor-strings]
int __cdecl Physics_InitCylinder(struct Physics_s *ptBody, float vMass, float vH, float vR, int nDir)
{
  double v5; // st7
  double v6; // st7
  int v7; // eax
  float v8; // eax
  float v9; // ecx
  float vIxx; // [esp+0h] [ebp-4h]
  float vHa = *(float *)&vH; // [esp+10h] [ebp+Ch] ARGSLOT
  float vRb = *(float *)&vR; // [esp+14h] [ebp+10h] ARGSLOT
  float vRa = *(float *)&vR; // [esp+14h] [ebp+10h] ARGSLOT

  v5 = vR * vR;
  vRb = v5;
  v6 = v5 * vMass * 0.5;
  vRa = (vH * vH + vRb * 3.0) * vMass * 0.0833333358168602;
  if ( !nDir )
  {
    v9 = vRa;
    vIxx = v6;
LABEL_8:
    vHa = v9;
    return (int)Physics_Init(ptBody, vMass, vIxx, vHa, vRa);
  }
  v7 = nDir - 1;
  if ( v7 )
  {
    if ( v7 != 1 )
    {
      LDebug_Error("Illegal cylinder direction");
      abort();
    }
    v8 = vRa;
    vRa = v6;
    vIxx = v8;
    v9 = v8;
    goto LABEL_8;
  }
  vHa = v6;
  vIxx = vRa;
  return (int)Physics_Init(ptBody, vMass, vIxx, vHa, vRa);
}

// source: g/0/physics_.c:131  [size]
void __cdecl Physics_AllocCylinder(
        struct Physics_s *ptBody,
        float vMass,
        float vH,
        float vR,
        int nDir,
        int nMaxForces)
{
  Physics_InitCylinder(ptBody, vMass, vH, vR, nDir);
  ptBody->nMaxForces = nMaxForces;
  if ( nMaxForces <= 0 )
    ptBody->ptForces = nullptr;
  else
    ptBody->ptForces = (struct PointForce_s *)Mem_AllocFn(24 * nMaxForces, 4);
}

// source: g/0/physics_.c:153  [anchor-strings]
int __cdecl Physics_InitCone(struct Physics_s *ptBody, float vMass, float vH, float vR, int nDir)
{
  double v5; // st7
  double v6; // st7
  int v7; // eax
  float v8; // eax
  float v9; // ecx
  float vIxx; // [esp+0h] [ebp-4h]
  float vHa = *(float *)&vH; // [esp+10h] [ebp+Ch] ARGSLOT
  float vRb = *(float *)&vR; // [esp+14h] [ebp+10h] ARGSLOT
  float vRa = *(float *)&vR; // [esp+14h] [ebp+10h] ARGSLOT

  v5 = vR * vR;
  vRb = v5;
  v6 = v5 * vMass * 3.0 * 0.10000000149011612;
  vRa = (vH * vH + vRb * 4.0) * vMass * 3.0 * 0.012500000186264515;
  if ( !nDir )
  {
    v9 = vRa;
    vIxx = v6;
LABEL_8:
    vHa = v9;
    return (int)Physics_Init(ptBody, vMass, vIxx, vHa, vRa);
  }
  v7 = nDir - 1;
  if ( v7 )
  {
    if ( v7 != 1 )
    {
      LDebug_Error("Illegal cone direction");
      abort();
    }
    v8 = vRa;
    vRa = v6;
    vIxx = v8;
    v9 = v8;
    goto LABEL_8;
  }
  vHa = v6;
  vIxx = vRa;
  return (int)Physics_Init(ptBody, vMass, vIxx, vHa, vRa);
}

// source: g/0/physics_.c:216  [size]
void __cdecl Physics_AllocCone(
        struct Physics_s *ptBody,
        float vMass,
        float vH,
        float vR,
        int nDir,
        int nMaxForces)
{
  Physics_InitCone(ptBody, vMass, vH, vR, nDir);
  ptBody->nMaxForces = nMaxForces;
  if ( nMaxForces <= 0 )
    ptBody->ptForces = nullptr;
  else
    ptBody->ptForces = (struct PointForce_s *)Mem_AllocFn(24 * nMaxForces, 4);
}

// source: g/0/physics_.c:242  [anchor-mhash]
void __cdecl Physics_Alloc(
        struct Physics_s *ptBody,
        float vMass,
        float vIxx,
        float vIyy,
        float vIzz,
        int nMaxForces)
{
  Physics_Init(ptBody, vMass, vIxx, vIyy, vIzz);
  ptBody->nMaxForces = nMaxForces;
  if ( nMaxForces <= 0 )
    ptBody->ptForces = nullptr;
  else
    ptBody->ptForces = (struct PointForce_s *)Mem_AllocFn(24 * nMaxForces, 4);
}

// source: g/0/physics_.c:263  [anchor-callee]
struct Physics_s *__cdecl Physics_Init(
        struct Physics_s *ptBody,
        float vMass,
        float vIxx,
        float vIyy,
        float vIzz)
{
  ptBody->vM = vMass;
  ptBody->tCMVel.vX = 0.0;
  ptBody->tCMVel.vY = 0.0;
  ptBody->tCMVel.vZ = 0.0;
  ptBody->tCMVelDir.vX = 0.0;
  ptBody->tCMVelDir.vY = 0.0;
  ptBody->tCMVelDir.vZ = 0.0;
  ptBody->tAngMom.vX = 0.0;
  ptBody->tAngMom.vY = 0.0;
  ptBody->tAngMom.vZ = 0.0;
  ptBody->tForceTot.vX = 0.0;
  ptBody->tForceTot.vY = 0.0;
  ptBody->tForceTot.vZ = 0.0;
  ptBody->tAngVel.vX = 0.0;
  ptBody->tAngVel.vY = 0.0;
  ptBody->tAngVel.vZ = 0.0;
  ptBody->vCMSpeed = 0.0;
  ptBody->nForces = 0;
  ptBody->nPreviousForces = 0;
  ptBody->vIxxInv = 1.0 / vIxx;
  ptBody->vIyyInv = 1.0 / vIyy;
  ptBody->vIzzInv = 1.0 / vIzz;
  ptBody->vMInv = 1.0 / vMass;
  return ptBody;
}

// source: g/0/physics_.c:293  [anchor-mhash]
void __cdecl Physics_DeAlloc(struct Physics_s *ptBody)
{
  struct PointForce_s *ptForces; // eax
  int v2; // esi

  ptForces = ptBody->ptForces;
  if ( ptForces )
  {
    v2 = *(_DWORD *)((unsigned int)&ptForces[-1].tPoint.vZ & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v2);
    memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
    free((void *)v2);
    ptBody->ptForces = nullptr;
    memset(ptBody, 0, sizeof(struct Physics_s));
  }
}

// source: g/0/physics_.c:312  [anchor-hash]
struct Physics_s *__cdecl Physics_Reset(struct Physics_s *ptBody)
{
  ptBody->tCMVel.vX = 0.0;
  ptBody->tCMVel.vY = 0.0;
  ptBody->tCMVel.vZ = 0.0;
  ptBody->tCMVelDir.vX = 0.0;
  ptBody->tCMVelDir.vY = 0.0;
  ptBody->tCMVelDir.vZ = 0.0;
  ptBody->tAngMom.vX = 0.0;
  ptBody->tAngMom.vY = 0.0;
  ptBody->tAngMom.vZ = 0.0;
  ptBody->tForceTot.vX = 0.0;
  ptBody->tForceTot.vY = 0.0;
  ptBody->tForceTot.vZ = 0.0;
  ptBody->tAngVel.vX = 0.0;
  ptBody->tAngVel.vY = 0.0;
  ptBody->tAngVel.vZ = 0.0;
  ptBody->vCMSpeed = 0.0;
  ptBody->nForces = 0;
  ptBody->nPreviousForces = 0;
  return ptBody;
}

// source: g/0/physics_.c:336  [anchor-callee]
int __cdecl Physics_Update(struct Physics_s *ptBody, struct real32x9_t *ptOrientation)
{
  #pragma pack(push, 1)
  union
  {
    struct { int vSqrt; };
    struct { float vSqrta; };
    struct { float vSqrtb; };
    struct { float vSqrtc; };
    struct { float vSqrtd; };
    struct { char igi2_o5[4]; float v_I; };
    struct { char igi2_o6[4]; float v_Ia; };
    struct { char igi2_o7[4]; float v_Ib; };
    struct { char igi2_o8[8]; float v_G; };
    struct { char igi2_o9[8]; float v_Ga; };
    struct { char igi2_o10[12]; float v_F; };
    struct { char igi2_o11[12]; float v_Fa; };
    struct { char igi2_o12[16]; float v_D; };
    struct { char igi2_o13[16]; float v_Da; };
    struct { char igi2_o14[20]; float isOrientationUpdate; };
    struct { char igi2_o15[20]; float isOrientationUpdatea; };
    struct { char igi2_o16[24]; float v_A; };
    struct { char igi2_o17[28]; struct real32x3_t tForceTot; };
    struct { char igi2_o18[40]; int aiNext[3]; };
    struct { char igi2_o19[52]; struct Quat32_t tdQ; };
    struct { char igi2_o20[84]; float vIzzInv; };
    struct { char igi2_o21[92]; struct Quat32_t tQOrientation; };
    char igi2_extent[112];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v2; // st7
  long double v3; // st7
  long double v4; // st7
  double v5; // st6
  double vY; // st7
  bool v7; // c0
  bool v8; // c3
  int v9; // ecx
  int v10; // esi
  int v11; // ebx
  double v12; // st7
  int nForces; // ebx
  int v14; // ebp
  double v15; // st6
  double v16; // st5
  double v17; // st4
  double v18; // st3
  struct PointForce_s *ptForces; // ecx
  float *p_vZ; // esi
  float *p_vY; // ecx
  double v22; // st3
  double v23; // st2
  double v24; // st3
  double v25; // st2
  double v26; // st3
  double v27; // st2
  double v28; // st2
  struct PointForce_s *v29; // esi
  float *v30; // ecx
  int v31; // ebx
  double v32; // st2
  double vMInv; // st4
  double v34; // st3
  double v35; // rt2
  double v36; // st2
  double v37; // st4
  double v38; // st3
  double vIxxInv; // st6
  double vIyyInv; // st5
  double v41; // rt2
  double vX; // st4
  double v43; // st6
  double v44; // st5
  double v45; // st6
  double v46; // st5
  double v47; // st4
  double v48; // rt0
  long double v49; // st4
  double v50; // rt2
  long double v51; // st7
  long double v52; // st6
  long double v53; // st7
  long double v54; // st6
  long double v55; // st7
  double v56; // st6
  double v57; // st5
  long double v58; // st4
  long double v59; // st4
  double v60; // st7

  v2 = ptOrientation->tY.vY + ptOrientation->tX.vX + ptOrientation->tZ.vZ;
  if ( v2 <= 0.0 )
  {
    igi2_frame.aiNext[0] = 1;
    vY = ptOrientation->tY.vY;
    igi2_frame.aiNext[1] = 2;
    v7 = vY < ptOrientation->tX.vX;
    v8 = vY == ptOrientation->tX.vX;
    igi2_frame.aiNext[2] = 0;
    v9 = !v7 && !v8;
    if ( ptOrientation->tZ.vZ > (double)*(&ptOrientation->tX.vX + 4 * v9) )
      v9 = 2;
    v10 = igi2_frame.aiNext[v9];
    v11 = igi2_frame.aiNext[v10];
    v12 = sqrt(
            *(&ptOrientation->tX.vX + 4 * v9)
          - *(&ptOrientation->tX.vX + 4 * v10)
          - *(&ptOrientation->tX.vX + 4 * v11)
          + 1.0);
    *(&igi2_frame.tQOrientation.vX + v9) = 0.5 * v12;
    if ( v12 != 0.0 )
      v12 = 0.5 / v12;
    *(&igi2_frame.tQOrientation.vX + v10) = (*(&ptOrientation->tX.vX + 3 * v10 + v9) + *(&ptOrientation->tX.vX + 3 * v9 + v10))
                               * v12;
    *(&igi2_frame.tQOrientation.vX + v11) = (*(&ptOrientation->tX.vX + 3 * v11 + v9) + *(&ptOrientation->tX.vX + 3 * v9 + v11))
                               * v12;
    v4 = -(v12 * (*(&ptOrientation->tX.vX + 3 * v10 + v11) - *(&ptOrientation->tX.vX + 3 * v11 + v10)));
  }
  else
  {
    v3 = sqrt(v2 + 1.0);
    igi2_frame.vSqrta = v3;
    v4 = v3 * 0.5;
    v5 = 0.5 / igi2_frame.vSqrta;
    igi2_frame.tQOrientation.vX = -((ptOrientation->tY.vZ - ptOrientation->tZ.vY) * v5);
    igi2_frame.tQOrientation.vY = -((ptOrientation->tZ.vX - ptOrientation->tX.vZ) * v5);
    igi2_frame.tQOrientation.vZ = -((ptOrientation->tX.vY - ptOrientation->tY.vX) * v5);
  }
  nForces = ptBody->nForces;
  v14 = 0;
  ptBody->nPreviousForces = nForces;
  if ( nForces > 0 )
  {
    v15 = 0.0;
    v16 = 0.0;
    memset(&igi2_frame.tForceTot, 0, sizeof(igi2_frame.tForceTot));
    v17 = 0.0;
    igi2_frame.tdQ.vZ = 0.0;
    v18 = 0.0;
    if ( nForces >= 4 )
    {
      ptForces = ptBody->ptForces;
      p_vZ = &ptForces->tForce.vZ;
      igi2_frame.vSqrt = 3;
      p_vY = &ptForces->tPoint.vY;
      do
      {
        v22 = v18 + *(p_vZ - 2);
        igi2_frame.tForceTot.vY = igi2_frame.tForceTot.vY + *(p_vZ - 1);
        igi2_frame.tForceTot.vZ = igi2_frame.tForceTot.vZ + *p_vZ;
        if ( (p_vZ[1] != 0.0 || *p_vY != 0.0 || p_vY[1] != 0.0)
          && (*(p_vZ - 2) != 0.0 || *(p_vZ - 1) != 0.0 || *p_vZ != 0.0) )
        {
          v23 = *p_vY * *p_vZ - p_vY[1] * *(p_vZ - 1);
          *(float *)&igi2_frame.aiNext[1] = -(*p_vZ * p_vZ[1] - p_vY[1] * *(p_vZ - 2));
          *(float *)&igi2_frame.aiNext[2] = *(p_vZ - 1) * p_vZ[1] - *p_vY * *(p_vZ - 2);
          v15 = v15 + v23;
          v16 = v16 + *(float *)&igi2_frame.aiNext[1];
          v17 = v17 + *(float *)&igi2_frame.aiNext[2];
        }
        v24 = v22 + p_vZ[4];
        igi2_frame.tForceTot.vY = igi2_frame.tForceTot.vY + p_vY[3];
        igi2_frame.tForceTot.vZ = igi2_frame.tForceTot.vZ + p_vY[4];
        if ( (p_vZ[7] != 0.0 || p_vY[6] != 0.0 || p_vY[7] != 0.0)
          && (p_vZ[4] != 0.0 || p_vY[3] != 0.0 || p_vY[4] != 0.0) )
        {
          v25 = p_vY[6] * p_vY[4] - p_vY[7] * p_vY[3];
          *(float *)&igi2_frame.aiNext[1] = -(p_vY[4] * p_vZ[7] - p_vY[7] * p_vZ[4]);
          *(float *)&igi2_frame.aiNext[2] = p_vY[3] * p_vZ[7] - p_vY[6] * p_vZ[4];
          v15 = v15 + v25;
          v16 = v16 + *(float *)&igi2_frame.aiNext[1];
          v17 = v17 + *(float *)&igi2_frame.aiNext[2];
        }
        v26 = v24 + p_vZ[10];
        igi2_frame.tForceTot.vY = igi2_frame.tForceTot.vY + p_vY[9];
        igi2_frame.tForceTot.vZ = igi2_frame.tForceTot.vZ + p_vY[10];
        if ( (p_vZ[13] != 0.0 || p_vY[12] != 0.0 || p_vY[13] != 0.0)
          && (p_vZ[10] != 0.0 || p_vY[9] != 0.0 || p_vY[10] != 0.0) )
        {
          v27 = p_vY[12] * p_vY[10] - p_vY[13] * p_vY[9];
          *(float *)&igi2_frame.aiNext[1] = -(p_vY[10] * p_vZ[13] - p_vY[13] * p_vZ[10]);
          *(float *)&igi2_frame.aiNext[2] = p_vY[9] * p_vZ[13] - p_vY[12] * p_vZ[10];
          v15 = v15 + v27;
          v16 = v16 + *(float *)&igi2_frame.aiNext[1];
          v17 = v17 + *(float *)&igi2_frame.aiNext[2];
        }
        v18 = v26 + p_vZ[16];
        igi2_frame.tForceTot.vY = igi2_frame.tForceTot.vY + p_vY[15];
        igi2_frame.tForceTot.vZ = igi2_frame.tForceTot.vZ + p_vY[16];
        if ( (p_vZ[19] != 0.0 || p_vY[18] != 0.0 || p_vY[19] != 0.0)
          && (p_vZ[16] != 0.0 || p_vY[15] != 0.0 || p_vY[16] != 0.0) )
        {
          v28 = p_vY[18] * p_vY[16] - p_vY[19] * p_vY[15];
          *(float *)&igi2_frame.aiNext[1] = -(p_vY[16] * p_vZ[19] - p_vY[19] * p_vZ[16]);
          *(float *)&igi2_frame.aiNext[2] = p_vY[15] * p_vZ[19] - p_vY[18] * p_vZ[16];
          v15 = v15 + v28;
          v16 = v16 + *(float *)&igi2_frame.aiNext[1];
          v17 = v17 + *(float *)&igi2_frame.aiNext[2];
        }
        v14 += 4;
        p_vY += 24;
        p_vZ += 24;
        igi2_frame.vSqrt += 4;
      }
      while ( igi2_frame.vSqrt < nForces );
      igi2_frame.tForceTot.vX = v18;
      igi2_frame.tdQ.vZ = v17;
    }
    if ( v14 < nForces )
    {
      v29 = &ptBody->ptForces[v14];
      v30 = &v29->tPoint.vY;
      v31 = nForces - v14;
      do
      {
        v18 = v18 + v29->tForce.vX;
        igi2_frame.tForceTot.vY = igi2_frame.tForceTot.vY + *(v30 - 3);
        igi2_frame.tForceTot.vZ = igi2_frame.tForceTot.vZ + *(v30 - 2);
        if ( (*(v30 - 1) != 0.0 || *v30 != 0.0 || v30[1] != 0.0)
          && (v29->tForce.vX != 0.0 || *(v30 - 3) != 0.0 || *(v30 - 2) != 0.0) )
        {
          v32 = *(v30 - 2) * *v30 - v30[1] * *(v30 - 3);
          *(float *)&igi2_frame.aiNext[1] = -(*(v30 - 2) * *(v30 - 1) - v30[1] * v29->tForce.vX);
          *(float *)&igi2_frame.aiNext[2] = *(v30 - 3) * *(v30 - 1) - *v30 * v29->tForce.vX;
          v15 = v15 + v32;
          v16 = v16 + *(float *)&igi2_frame.aiNext[1];
          v17 = v17 + *(float *)&igi2_frame.aiNext[2];
        }
        ++v29;
        v30 += 6;
        --v31;
      }
      while ( v31 );
      igi2_frame.tForceTot.vX = v18;
      igi2_frame.tdQ.vZ = v17;
    }
    vMInv = ptBody->vMInv;
    v34 = igi2_frame.tForceTot.vX * vMInv;
    ptBody->tForceTot = igi2_frame.tForceTot;
    v35 = vMInv * igi2_frame.tForceTot.vY;
    v36 = vMInv * igi2_frame.tForceTot.vZ;
    igi2_frame.tForceTot.vZ = v36;
    *(float *)igi2_frame.aiNext = v36 * ptOrientation->tX.vZ + v35 * ptOrientation->tX.vY + v34 * ptOrientation->tX.vX;
    *(float *)&igi2_frame.aiNext[1] = igi2_frame.tForceTot.vZ * ptOrientation->tY.vZ + v34 * ptOrientation->tY.vX + v35 * ptOrientation->tY.vY;
    v37 = v35 * ptOrientation->tZ.vY + v34 * ptOrientation->tZ.vX;
    v38 = igi2_frame.tForceTot.vZ * ptOrientation->tZ.vZ;
    ptBody->nForces = 0;
    *(float *)&igi2_frame.aiNext[2] = v37 + v38;
    ptBody->tCMVel.vX = *(float *)igi2_frame.aiNext + ptBody->tCMVel.vX;
    ptBody->tCMVel.vY = *(float *)&igi2_frame.aiNext[1] + ptBody->tCMVel.vY;
    ptBody->tCMVel.vZ = *(float *)&igi2_frame.aiNext[2] + ptBody->tCMVel.vZ;
    ptBody->tAngMom.vX = v15 + ptBody->tAngMom.vX;
    ptBody->tAngMom.vY = v16 + ptBody->tAngMom.vY;
    ptBody->tAngMom.vZ = igi2_frame.tdQ.vZ + ptBody->tAngMom.vZ;
  }
  if ( ptBody->tAngMom.vX == 0.0 && ptBody->tAngMom.vY == 0.0 && ptBody->tAngMom.vZ == 0.0 )
  {
    Physics_UpdateSpeedApproximation(ptBody);
    return 0;
  }
  else
  {
    vIxxInv = ptBody->vIxxInv;
    vIyyInv = ptBody->vIyyInv;
    igi2_frame.vIzzInv = ptBody->vIzzInv;
    igi2_frame.v_I = ptBody->tAngMom.vY * 0.0;
    v41 = ptBody->tAngMom.vZ * 0.0;
    *(float *)igi2_frame.aiNext = vIxxInv * ptBody->tAngMom.vX + igi2_frame.v_I + v41;
    vX = ptBody->tAngMom.vX;
    LODWORD(ptBody->tAngVel.vX) = igi2_frame.aiNext[0];
    igi2_frame.vSqrtb = vX * 0.0;
    *(float *)&igi2_frame.aiNext[1] = vIyyInv * ptBody->tAngMom.vY + igi2_frame.vSqrtb + v41;
    LODWORD(ptBody->tAngVel.vY) = igi2_frame.aiNext[1];
    *(float *)&igi2_frame.aiNext[2] = igi2_frame.vIzzInv * ptBody->tAngMom.vZ + igi2_frame.vSqrtb + igi2_frame.v_I;
    LODWORD(ptBody->tAngVel.vZ) = igi2_frame.aiNext[2];
    *(float *)igi2_frame.aiNext = ptOrientation->tX.vY * ptBody->tAngVel.vY
                     + ptBody->tAngVel.vZ * ptOrientation->tX.vZ
                     + ptOrientation->tX.vX * ptBody->tAngVel.vX;
    *(float *)&igi2_frame.aiNext[1] = ptOrientation->tY.vZ * ptBody->tAngVel.vZ
                         + ptOrientation->tY.vY * ptBody->tAngVel.vY
                         + ptOrientation->tY.vX * ptBody->tAngVel.vX;
    v43 = ptBody->tAngVel.vZ * ptOrientation->tZ.vZ + ptBody->tAngVel.vY * ptOrientation->tZ.vY;
    v44 = ptOrientation->tZ.vX * ptBody->tAngVel.vX;
    LODWORD(ptBody->tAngVel.vX) = igi2_frame.aiNext[0];
    LODWORD(ptBody->tAngVel.vY) = igi2_frame.aiNext[1];
    *(float *)&igi2_frame.aiNext[2] = v43 + v44;
    LODWORD(ptBody->tAngVel.vZ) = igi2_frame.aiNext[2];
    v45 = ptBody->tAngVel.vX * 0.5;
    v46 = ptBody->tAngVel.vY * 0.5;
    v47 = ptBody->tAngVel.vZ * 0.5;
    igi2_frame.v_A = (v47 - v46) * (igi2_frame.tQOrientation.vY - igi2_frame.tQOrientation.vZ);
    igi2_frame.isOrientationUpdate = (igi2_frame.tQOrientation.vZ + igi2_frame.tQOrientation.vY) * -v45;
    igi2_frame.v_D = (v47 + v46) * (v4 - igi2_frame.tQOrientation.vX);
    igi2_frame.v_F = (v47 + v45) * (igi2_frame.tQOrientation.vY + igi2_frame.tQOrientation.vX);
    igi2_frame.v_G = (v4 - igi2_frame.tQOrientation.vZ) * v46;
    v48 = v47;
    v49 = (igi2_frame.tQOrientation.vZ + v4) * -v46;
    igi2_frame.vSqrtc = v49;
    igi2_frame.v_Ia = v49 + igi2_frame.v_G + igi2_frame.v_F;
    v50 = ((v48 - v45) * (igi2_frame.tQOrientation.vX - igi2_frame.tQOrientation.vY) + igi2_frame.v_Ia) * 0.5;
    igi2_frame.tdQ.vX = (igi2_frame.tQOrientation.vX + v4) * v45 + v50 - igi2_frame.v_Ia;
    igi2_frame.tdQ.vY = igi2_frame.isOrientationUpdate + v50 - igi2_frame.vSqrtc;
    igi2_frame.tdQ.vZ = igi2_frame.v_D + v50 - igi2_frame.v_G;
    igi2_frame.tQOrientation.vX = igi2_frame.tdQ.vX + igi2_frame.tQOrientation.vX;
    igi2_frame.tQOrientation.vY = igi2_frame.tdQ.vY + igi2_frame.tQOrientation.vY;
    igi2_frame.tQOrientation.vZ = igi2_frame.tdQ.vZ + igi2_frame.tQOrientation.vZ;
    v51 = v4 + v50 + igi2_frame.v_A - igi2_frame.v_F;
    v52 = 1.0
        / sqrt(
            igi2_frame.tQOrientation.vZ * igi2_frame.tQOrientation.vZ
          + igi2_frame.tQOrientation.vY * igi2_frame.tQOrientation.vY
          + igi2_frame.tQOrientation.vX * igi2_frame.tQOrientation.vX
          + v51 * v51);
    igi2_frame.tQOrientation.vX = igi2_frame.tQOrientation.vX * v52;
    igi2_frame.tQOrientation.vY = igi2_frame.tQOrientation.vY * v52;
    igi2_frame.tQOrientation.vZ = igi2_frame.tQOrientation.vZ * v52;
    v53 = v51 * v52;
    v54 = 1.0
        / sqrt(
            igi2_frame.tQOrientation.vZ * igi2_frame.tQOrientation.vZ
          + igi2_frame.tQOrientation.vY * igi2_frame.tQOrientation.vY
          + igi2_frame.tQOrientation.vX * igi2_frame.tQOrientation.vX
          + v53 * v53);
    igi2_frame.tQOrientation.vX = igi2_frame.tQOrientation.vX * v54;
    igi2_frame.tQOrientation.vY = igi2_frame.tQOrientation.vY * v54;
    igi2_frame.tQOrientation.vZ = igi2_frame.tQOrientation.vZ * v54;
    v55 = v53 * v54;
    v56 = igi2_frame.tQOrientation.vX * igi2_frame.tQOrientation.vX + igi2_frame.tQOrientation.vX * igi2_frame.tQOrientation.vX;
    v57 = igi2_frame.tQOrientation.vY * igi2_frame.tQOrientation.vX + igi2_frame.tQOrientation.vY * igi2_frame.tQOrientation.vX;
    igi2_frame.v_Ga = igi2_frame.tQOrientation.vZ * igi2_frame.tQOrientation.vX + igi2_frame.tQOrientation.vZ * igi2_frame.tQOrientation.vX;
    v58 = igi2_frame.tQOrientation.vX * v55;
    ptOrientation->nOps = 0;
    igi2_frame.v_Da = v58 + v58;
    igi2_frame.isOrientationUpdatea = igi2_frame.tQOrientation.vY * igi2_frame.tQOrientation.vY + igi2_frame.tQOrientation.vY * igi2_frame.tQOrientation.vY;
    igi2_frame.vSqrtd = igi2_frame.tQOrientation.vZ * igi2_frame.tQOrientation.vY + igi2_frame.tQOrientation.vZ * igi2_frame.tQOrientation.vY;
    igi2_frame.v_Ib = igi2_frame.tQOrientation.vY * v55 + igi2_frame.tQOrientation.vY * v55;
    igi2_frame.v_Fa = igi2_frame.tQOrientation.vZ * igi2_frame.tQOrientation.vZ + igi2_frame.tQOrientation.vZ * igi2_frame.tQOrientation.vZ;
    v59 = igi2_frame.tQOrientation.vZ * v55 + igi2_frame.tQOrientation.vZ * v55;
    ptOrientation->tX.vX = 1.0 - igi2_frame.isOrientationUpdatea - igi2_frame.v_Fa;
    ptOrientation->tX.vY = v57 - v59;
    ptOrientation->tX.vZ = igi2_frame.v_Ib + igi2_frame.v_Ga;
    ptOrientation->tY.vX = v59 + v57;
    v60 = 1.0 - v56;
    ptOrientation->tY.vY = v60 - igi2_frame.v_Fa;
    ptOrientation->tY.vZ = igi2_frame.vSqrtd - igi2_frame.v_Da;
    ptOrientation->tZ.vX = igi2_frame.v_Ga - igi2_frame.v_Ib;
    ptOrientation->tZ.vY = igi2_frame.vSqrtd + igi2_frame.v_Da;
    ptOrientation->tZ.vZ = v60 - igi2_frame.isOrientationUpdatea;
    Physics_UpdateSpeedApproximation(ptBody);
    return 1;
  }
}

// source: g/0/physics_.c:477  [anchor-callee]
struct Physics_s *__cdecl Physics_UpdateSpeedApproximation(struct Physics_s *ptBody)
{
  struct real32x3_t *p_tCMVel; // eax
  float vX; // ecx
  float vY; // edx
  double v5; // st7
  long double v6; // st7
  float v7; // edx
  struct Physics_s *result; // eax
  struct real32x3_t *p_tCMVelDir; // esi
  struct real32x3_t tVelocity; // [esp+4h] [ebp-Ch] BYREF

  p_tCMVel = &ptBody->tCMVel;
  vX = p_tCMVel->vX;
  vY = p_tCMVel->vY;
  tVelocity.vZ = p_tCMVel->vZ;
  tVelocity.vX = vX;
  tVelocity.vY = vY;
  v5 = Real32x3_FastLen(&tVelocity);
  ptBody->vCMSpeed = v5;
  if ( v5 <= 0.0 )
  {
    memset(&tVelocity, 0, sizeof(tVelocity));
  }
  else if ( tVelocity.vX != 0.0 || tVelocity.vY != 0.0 || tVelocity.vZ != 0.0 )
  {
    v6 = 1.0 / sqrt(tVelocity.vX * tVelocity.vX + tVelocity.vY * tVelocity.vY + tVelocity.vZ * tVelocity.vZ);
    tVelocity.vX = tVelocity.vX * v6;
    tVelocity.vY = tVelocity.vY * v6;
    tVelocity.vZ = tVelocity.vZ * v6;
  }
  v7 = tVelocity.vY;
  result = (struct Physics_s *)LODWORD(tVelocity.vZ);
  p_tCMVelDir = &ptBody->tCMVelDir;
  p_tCMVelDir->vX = tVelocity.vX;
  p_tCMVelDir->vY = v7;
  LODWORD(p_tCMVelDir->vZ) = result;
  return result;
}

// source: g/0/physics_.c:521  [anchor-caller]
void __cdecl Physics_AllocBox(
        struct Physics_s *ptBody,
        float vMass,
        float vX,
        float vY,
        float vZ,
        int nMaxForces)
{
  Physics_InitBox(ptBody, vMass, vX, vY, vZ);
  ptBody->nMaxForces = nMaxForces;
  if ( nMaxForces <= 0 )
    ptBody->ptForces = nullptr;
  else
    ptBody->ptForces = (struct PointForce_s *)Mem_AllocFn(24 * nMaxForces, 4);
}

// source: g/0/physics_.c:543  [anchor-callee]
void __cdecl Physics_InitBox(struct Physics_s *ptBody, float vMass, float vX, float vY, float vZ)
{
  double v5; // st7
  double v6; // st6
  double v7; // st5
  float v8; // [esp+0h] [ebp-Ch]
  float vIxx; // [esp+4h] [ebp-8h]
  float vIyy; // [esp+8h] [ebp-4h]

  v5 = vX * vX;
  v6 = vY * vY;
  v7 = vZ * vZ;
  vIyy = (v6 + v5) * vMass * 0.0833333358168602;
  vIxx = (v7 + v5) * vMass * 0.0833333358168602;
  v8 = (v7 + v6) * vMass * 0.0833333358168602;
  Physics_Init(ptBody, vMass, v8, vIxx, vIyy);
}

// source: g/0/physics_.c:586  [size]
void __cdecl Physics_AllocCylinderX(
        struct Physics_s *ptBody,
        float vMass,
        float vH,
        float vR,
        int nMaxForces)
{
  Physics_InitCylinder(ptBody, vMass, vH, vR, 0);
  ptBody->nMaxForces = nMaxForces;
  if ( nMaxForces <= 0 )
    ptBody->ptForces = nullptr;
  else
    ptBody->ptForces = (struct PointForce_s *)Mem_AllocFn(24 * nMaxForces, 4);
}

// source: g/0/physics_.c:605  [size]
void __cdecl Physics_InitCylinderX(struct Physics_s *ptBody, float vMass, float vH, float vR)
{
  Physics_InitCylinder(ptBody, vMass, vH, vR, 0);
}

// source: g/0/physics_.c:625  [anchor-mhash]
void __cdecl Physics_AllocCylinderY(
        struct Physics_s *ptBody,
        float vMass,
        float vH,
        float vR,
        int nMaxForces)
{
  double v5; // st7
  float vIxx; // [esp+0h] [ebp-4h]
  float vHa = *(float *)&vR; // [esp+10h] [ebp+Ch] ARGSLOT

  v5 = vR * vR;
  vIxx = vMass * v5 * 0.5;
  vHa = (vH * vH + v5 * 3.0) * vMass * 0.0833333358168602;
  Physics_Init(ptBody, vMass, vHa, vIxx, vHa);
  ptBody->nMaxForces = nMaxForces;
  if ( nMaxForces <= 0 )
    ptBody->ptForces = nullptr;
  else
    ptBody->ptForces = (struct PointForce_s *)Mem_AllocFn(24 * nMaxForces, 4);
}

// source: g/0/physics_.c:644  [anchor-mhash]
void __cdecl Physics_InitCylinderY(struct Physics_s *ptBody, float vMass, float vH, float vR)
{
  double v4; // st7
  float vIxx; // [esp+0h] [ebp-4h]
  float vRa = *(float *)&vR; // [esp+14h] [ebp+10h] ARGSLOT

  v4 = vR * vR;
  vIxx = vMass * v4 * 0.5;
  vRa = (vH * vH + v4 * 3.0) * vMass * 0.0833333358168602;
  Physics_Init(ptBody, vMass, vRa, vIxx, vRa);
}

// source: g/0/physics_.c:664  [anchor-mhash]
void __cdecl Physics_AllocCylinderZ(
        struct Physics_s *ptBody,
        float vMass,
        float vH,
        float vR,
        int nMaxForces)
{
  double v5; // st7
  float vMassa = *(float *)&vH; // [esp+8h] [ebp+8h] ARGSLOT
  float vHa = *(float *)&vR; // [esp+Ch] [ebp+Ch] ARGSLOT

  v5 = vR * vR;
  vHa = vMass * v5 * 0.5;
  vMassa = (vH * vH + v5 * 3.0) * vMass * 0.0833333358168602;
  Physics_Init(ptBody, vMass, vMassa, vMassa, vHa);
  ptBody->nMaxForces = nMaxForces;
  if ( nMaxForces <= 0 )
    ptBody->ptForces = nullptr;
  else
    ptBody->ptForces = (struct PointForce_s *)Mem_AllocFn(24 * nMaxForces, 4);
}

// source: g/0/physics_.c:683  [anchor-mhash]
void __cdecl Physics_InitCylinderZ(struct Physics_s *ptBody, float vMass, float vH, float vR)
{
  double v4; // st7
  float vHa = *(float *)&vH; // [esp+Ch] [ebp+Ch] ARGSLOT
  float vRa = *(float *)&vR; // [esp+10h] [ebp+10h] ARGSLOT

  v4 = vR * vR;
  vRa = vMass * v4 * 0.5;
  vHa = (vH * vH + v4 * 3.0) * vMass * 0.0833333358168602;
  Physics_Init(ptBody, vMass, vHa, vHa, vRa);
}

// source: g/0/physics_.c:702  [anchor-mhash]
void __cdecl Physics_AllocSphere(struct Physics_s *ptBody, float vMass, float vR, int nMaxForces)
{
  double v4; // st7
  float vMassa = *(float *)&vR; // [esp+8h] [ebp+8h] ARGSLOT

  v4 = vR * vR * vMass;
  vMassa = (v4 + v4) * 0.20000000298023224;
  Physics_Init(ptBody, vMass, vMassa, vMassa, vMassa);
  ptBody->nMaxForces = nMaxForces;
  if ( nMaxForces <= 0 )
    ptBody->ptForces = nullptr;
  else
    ptBody->ptForces = (struct PointForce_s *)Mem_AllocFn(24 * nMaxForces, 4);
}

// source: g/0/physics_.c:722  [anchor-mhash]
void __cdecl Physics_InitSphere(struct Physics_s *ptBody, float vMass, float vR)
{
  double v3; // st7
  float vRa = *(float *)&vR; // [esp+Ch] [ebp+Ch] ARGSLOT

  v3 = vR * vR * vMass;
  vRa = (v3 + v3) * 0.20000000298023224;
  Physics_Init(ptBody, vMass, vRa, vRa, vRa);
}

// source: g/0/physics_.c:750  [anchor-mhash]
void __cdecl Physics_AllocEllipsoid(
        struct Physics_s *ptBody,
        float vMass,
        float vRx,
        float vRy,
        float vRz,
        int nMaxForces)
{
  Physics_InitEllipsoid(ptBody, vMass, vRx, vRy, vRz);
  ptBody->nMaxForces = nMaxForces;
  if ( nMaxForces <= 0 )
    ptBody->ptForces = nullptr;
  else
    ptBody->ptForces = (struct PointForce_s *)Mem_AllocFn(24 * nMaxForces, 4);
}

// source: g/0/physics_.c:772  [anchor-mhash]
void __cdecl Physics_InitEllipsoid(
        struct Physics_s *ptBody,
        float vMass,
        float vRx,
        float vRy,
        float vRz)
{
  double v5; // st7
  double v6; // st6
  double v7; // st5
  float v8; // [esp+0h] [ebp-Ch]
  float vIxx; // [esp+4h] [ebp-8h]
  float vIyy; // [esp+8h] [ebp-4h]

  v5 = vRx * vRx;
  v6 = vRy * vRy;
  v7 = vRz * vRz;
  vIyy = (v6 + v5) * vMass * 0.20000000298023224;
  vIxx = (v7 + v5) * vMass * 0.20000000298023224;
  v8 = (v7 + v6) * vMass * 0.20000000298023224;
  Physics_Init(ptBody, vMass, v8, vIxx, vIyy);
}

// source: g/0/physics_.c:815  [size]
void __cdecl Physics_AllocConeX(
        struct Physics_s *ptBody,
        float vMass,
        float vH,
        float vR,
        int nMaxForces)
{
  Physics_InitCone(ptBody, vMass, vH, vR, 0);
  ptBody->nMaxForces = nMaxForces;
  if ( nMaxForces <= 0 )
    ptBody->ptForces = nullptr;
  else
    ptBody->ptForces = (struct PointForce_s *)Mem_AllocFn(24 * nMaxForces, 4);
}

// source: g/0/physics_.c:834  [size]
void __cdecl Physics_InitConeX(struct Physics_s *ptBody, float vMass, float vH, float vR)
{
  Physics_InitCone(ptBody, vMass, vH, vR, 0);
}

// source: g/0/physics_.c:854  [anchor-mhash]
void __cdecl Physics_AllocConeY(
        struct Physics_s *ptBody,
        float vMass,
        float vH,
        float vR,
        int nMaxForces)
{
  double v5; // st7
  float vIxx; // [esp+0h] [ebp-4h]
  float vHa = *(float *)&vR; // [esp+10h] [ebp+Ch] ARGSLOT

  v5 = vR * vR;
  vIxx = vMass * v5 * 3.0 * 0.10000000149011612;
  vHa = (vH * vH + v5 * 4.0) * vMass * 3.0 * 0.012500000186264515;
  Physics_Init(ptBody, vMass, vHa, vIxx, vHa);
  ptBody->nMaxForces = nMaxForces;
  if ( nMaxForces <= 0 )
    ptBody->ptForces = nullptr;
  else
    ptBody->ptForces = (struct PointForce_s *)Mem_AllocFn(24 * nMaxForces, 4);
}

// source: g/0/physics_.c:873  [anchor-mhash]
void __cdecl Physics_InitConeY(struct Physics_s *ptBody, float vMass, float vH, float vR)
{
  double v4; // st7
  float vIxx; // [esp+0h] [ebp-4h]
  float vRa = *(float *)&vR; // [esp+14h] [ebp+10h] ARGSLOT

  v4 = vR * vR;
  vIxx = vMass * v4 * 3.0 * 0.10000000149011612;
  vRa = (vH * vH + v4 * 4.0) * vMass * 3.0 * 0.012500000186264515;
  Physics_Init(ptBody, vMass, vRa, vIxx, vRa);
}

// source: g/0/physics_.c:893  [anchor-mhash]
void __cdecl Physics_AllocConeZ(
        struct Physics_s *ptBody,
        float vMass,
        float vH,
        float vR,
        int nMaxForces)
{
  double v5; // st7
  float vMassa = *(float *)&vH; // [esp+8h] [ebp+8h] ARGSLOT
  float vHa = *(float *)&vR; // [esp+Ch] [ebp+Ch] ARGSLOT

  v5 = vR * vR;
  vHa = vMass * v5 * 3.0 * 0.10000000149011612;
  vMassa = (vH * vH + v5 * 4.0) * vMass * 3.0 * 0.012500000186264515;
  Physics_Init(ptBody, vMass, vMassa, vMassa, vHa);
  ptBody->nMaxForces = nMaxForces;
  if ( nMaxForces <= 0 )
    ptBody->ptForces = nullptr;
  else
    ptBody->ptForces = (struct PointForce_s *)Mem_AllocFn(24 * nMaxForces, 4);
}

// source: g/0/physics_.c:912  [anchor-mhash]
void __cdecl Physics_InitConeZ(struct Physics_s *ptBody, float vMass, float vH, float vR)
{
  double v4; // st7
  float vHa = *(float *)&vH; // [esp+Ch] [ebp+Ch] ARGSLOT
  float vRa = *(float *)&vR; // [esp+10h] [ebp+10h] ARGSLOT

  v4 = vR * vR;
  vRa = vMass * v4 * 3.0 * 0.10000000149011612;
  vHa = (vH * vH + v4 * 4.0) * vMass * 3.0 * 0.012500000186264515;
  Physics_Init(ptBody, vMass, vHa, vHa, vRa);
}

// source: g/0/physics_.c:926  [anchor-mhash]
struct Physics_s *__cdecl Physics_AddPointForce(
        struct Physics_s *ptBody,
        struct PointForce_s *ptForce)
{
  qmemcpy(&ptBody->ptForces[ptBody->nForces++], ptForce, sizeof(ptBody->ptForces[ptBody->nForces++]));
  return ptBody;
}

// source: g/0/physics_.c:957  [anchor-callee]
struct Physics_s *__cdecl Physics_GetPointVelocity(
        struct real32x3_t *ptVelocity,
        struct Physics_s *ptBody,
        struct real32x3_t *ptPoint)
{
  struct real32x3_t struct_real32x3_t; // 0:^4.12

  struct_real32x3_t.vX = ptPoint->vZ * ptBody->tAngVel.vY - ptBody->tAngVel.vZ * ptPoint->vY;
  struct_real32x3_t.vY = -(ptPoint->vZ * ptBody->tAngVel.vX - ptBody->tAngVel.vZ * ptPoint->vX);
  struct_real32x3_t.vZ = ptBody->tAngVel.vX * ptPoint->vY - ptPoint->vX * ptBody->tAngVel.vY;
  *ptVelocity = struct_real32x3_t;
  ptVelocity->vX = ptBody->tCMVel.vX + ptVelocity->vX;
  ptVelocity->vY = ptBody->tCMVel.vY + ptVelocity->vY;
  ptVelocity->vZ = ptBody->tCMVel.vZ + ptVelocity->vZ;
  return ptBody;
}

// source: g/0/physics_.c:972  [size]
void __cdecl Physics_Open()
{
  Physics_ptUpdateProfileRegion = nullptr;
}

// source: g/0/physics_.c:986  [size]
void __cdecl Physics_Close()
{
  ;
}
