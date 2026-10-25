/* b/1/real.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/1/real.c:68  [anchor-callee]
float __cdecl Real32_Acos(float x)
{
  double v1; // st7
  long double v2; // st7
  long double v4; // st7
  double v5; // st6

  v1 = x;
  if ( x <= 0.7071067690849304 )
  {
    if ( v1 >= -0.7071067690849304 )
    {
      v5 = v1 * v1;
      return 1.5707963705062866
           - v1
           * (v1 * v1 * 75.4773941040039 - v5 * v5 * 17.736614227294922 - 65.96189880371094)
           / (v5 * v5 * v5 - v5 * v5 * 27.20241355895996 + v1 * v1 * 86.47110748291016 - 65.96189880371094);
    }
    else
    {
      if ( v1 <= -1.0 )
        v1 = -1.0;
      v4 = 1.0 - v1 * v1;
      return 3.1415927410125732
           - sqrt(v4)
           * (v4 * 75.4773941040039 - v4 * v4 * 17.736614227294922 - 65.96189880371094)
           / (v4 * v4 * v4 - v4 * v4 * 27.20241355895996 + v4 * 86.47110748291016 - 65.96189880371094);
    }
  }
  else
  {
    if ( v1 >= 1.0 )
      v1 = 1.0;
    v2 = 1.0 - v1 * v1;
    return sqrt(v2)
         * (v2 * 75.4773941040039 - v2 * v2 * 17.736614227294922 - 65.96189880371094)
         / (v2 * v2 * v2 - v2 * v2 * 27.20241355895996 + v2 * 86.47110748291016 - 65.96189880371094);
  }
}

// source: b/1/real.c:120  [anchor-callee]
float __cdecl Real32_Asin(float vValue)
{
  long double vValue64; // [esp+0h] [ebp-8h]

  vValue64 = vValue;
  if ( vValue < -1.0 )
  {
    HIDWORD(vValue64) = -1074790400;
LABEL_5:
    LODWORD(vValue64) = 0;
    return asin(vValue64);
  }
  if ( vValue > 1.0 )
  {
    HIDWORD(vValue64) = 1072693248;
    goto LABEL_5;
  }
  return asin(vValue64);
}

// source: b/1/real.c:144  [anchor-mhash]
float __cdecl Real32_FastAsin(float vSin)
{
  double v1; // st7
  double v2; // st7
  int v3; // eax

  v1 = vSin;
  if ( vSin >= -1.0 )
  {
    if ( v1 > 1.0 )
      v1 = 1.0;
  }
  else
  {
    v1 = -1.0;
  }
  v2 = (v1 + 1.0) * 4096.0;
  v3 = (__int64)v2;
  if ( v3 == 0x2000 )
    return Real32_avASin[0x2000];
  else
    return (Real32_avASin[v3 + 1] - Real32_avASin[v3]) * (v2 - (double)(int)(__int64)v2) + Real32_avASin[v3];
}

// source: b/1/real.c:190  [override: IDA decodes this function from the wrong byte]
// acos(x) = pi/2 - asin(x): the original calls Real32_FastAsin, then fsubr's it from the float
// constant at 0x6A6BD8 (pi/2).
float __cdecl Real32_FastAcos(float vCos)
{
  return flt_6A6BD8 - Real32_FastAsin(vCos);
}

// source: b/1/real.c:435  [override: the original clamps its argument in place and jumps into asin]
// The decompiler cannot follow the stack argument reused by the tail jump.
double __cdecl Real64_Asin(double vValue)
{
  if ( vValue < -1.0 )
    vValue = -1.0;
  else if ( vValue > 1.0 )
    vValue = 1.0;
  return asin(vValue);
}

// source: b/1/real.c:456  [override: the original clamps its argument in place and jumps into acos]
// The decompiler cannot follow the stack argument reused by the tail jump.
double __cdecl Real64_Acos(double vValue)
{
  if ( vValue < -1.0 )
    vValue = -1.0;
  else if ( vValue > 1.0 )
    vValue = 1.0;
  return acos(vValue);
}

// source: b/1/real.c:859  [anchor-mhash]
struct real32x2_t *__cdecl Real32x2_ScaleToLength(struct real32x2_t *ptDest, float vNewLen)
{
  long double v2; // st7

  v2 = 1.0 / sqrt(ptDest->vX * ptDest->vX + ptDest->vY * ptDest->vY);
  ptDest->vX = ptDest->vX * vNewLen * v2;
  ptDest->vY = vNewLen * ptDest->vY * v2;
  return ptDest;
}

// source: b/1/real.c:889  [anchor-hash]
struct real32x2_t *__cdecl Real32x2_Normalize(struct real32x2_t *ptDest)
{
  long double v1; // st7

  v1 = 1.0 / sqrt(ptDest->vX * ptDest->vX + ptDest->vY * ptDest->vY);
  ptDest->vX = ptDest->vX * v1;
  ptDest->vY = ptDest->vY * v1;
  return ptDest;
}

// source: b/1/real.c:918  [anchor-hash]
float __cdecl Real32x2_Len(struct real32x2_t *ptSource)
{
  return sqrt(ptSource->vX * ptSource->vX + ptSource->vY * ptSource->vY);
}

// source: b/1/real.c:934  [anchor-hash]
float __cdecl Real32x2_SquaredLen(struct real32x2_t *ptSource)
{
  return ptSource->vX * ptSource->vX + ptSource->vY * ptSource->vY;
}

// source: b/1/real.c:950  [anchor-mhash]
float __cdecl Real32x2_Distance(
        struct real32x2_t *ptSource0,
        struct real32x2_t *ptSource1)
{
  double v2; // st6
  double v3; // st4

  v2 = ptSource0->vY - ptSource1->vY;
  v3 = ptSource0->vX - ptSource1->vX;
  return sqrt(v2 * v2 + v3 * v3);
}

// source: b/1/real.c:972  [size]
float __cdecl Real32x2_DotProduct(
        struct real32x2_t *ptSource0,
        struct real32x2_t *ptSource1)
{
  return ptSource0->vY * ptSource1->vY + ptSource0->vX * ptSource1->vX;
}

// source: b/1/real.c:991  [size]
float __cdecl Real32x2_CrossProduct(
        struct real32x2_t *ptSource0,
        struct real32x2_t *ptSource1)
{
  return ptSource1->vY * ptSource0->vX - ptSource0->vY * ptSource1->vX;
}

// source: b/1/real.c:1007  [anchor-mhash]
enum bool __cdecl Real32x2_PointOnTriangle(
        float *pvU,
        float *pvV,
        struct real32x2_t *ptRelativePos,
        struct real32x2_t *ptEdge0,
        struct real32x2_t *ptEdge1)
{
  #pragma pack(push, 1)
  union
  {
    struct { float Real32x2_Rotate_tTemp; };
    struct { char igi2_o1[4]; float Real32x2_Rotate_tTemp_4; };
    struct { char igi2_o2[8]; struct real32x4_t tMatrix; };
    char igi2_extent[24];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  float vX; // edx
  float vY; // ecx
  float v7; // edx
  float v8; // eax

  vX = ptEdge0->vX;
  vY = ptEdge0->vY;
  igi2_frame.tMatrix.tX.vX = vX;
  v7 = ptEdge1->vX;
  v8 = ptEdge1->vY;
  igi2_frame.tMatrix.tX.vY = vY;
  igi2_frame.tMatrix.tY.vY = v8;
  igi2_frame.tMatrix.tY.vX = v7;
  if ( Real32x4_InvertSafe(&igi2_frame.tMatrix, &igi2_frame.tMatrix) == false )
    return false;
  igi2_frame.Real32x2_Rotate_tTemp = igi2_frame.tMatrix.tX.vX * ptRelativePos->vX + igi2_frame.tMatrix.tY.vX * ptRelativePos->vY;
  igi2_frame.Real32x2_Rotate_tTemp_4 = igi2_frame.tMatrix.tX.vY * ptRelativePos->vX + igi2_frame.tMatrix.tY.vY * ptRelativePos->vY;
  if ( pvU )
    *pvU = igi2_frame.Real32x2_Rotate_tTemp;
  if ( pvV )
    *pvV = igi2_frame.Real32x2_Rotate_tTemp_4;
  return igi2_frame.Real32x2_Rotate_tTemp > 0.0
      && igi2_frame.Real32x2_Rotate_tTemp_4 > 0.0
      && igi2_frame.Real32x2_Rotate_tTemp_4 + igi2_frame.Real32x2_Rotate_tTemp < 1.0;
}

// source: b/1/real.c:1229  [anchor-mhash]
struct real64x2_t *__cdecl Real64x2_ScaleToLength(struct real64x2_t *ptDest, double vNewLen)
{
  long double v2; // st5

  v2 = 1.0 / sqrt(ptDest->vX * ptDest->vX + ptDest->vY * ptDest->vY);
  ptDest->vX = v2 * ptDest->vX * vNewLen;
  ptDest->vY = v2 * vNewLen * ptDest->vY;
  return ptDest;
}

// source: b/1/real.c:1257  [anchor-hash]
struct real64x2_t *__cdecl Real64x2_Normalize(struct real64x2_t *ptDest)
{
  long double v1; // st5

  v1 = 1.0 / sqrt(ptDest->vX * ptDest->vX + ptDest->vY * ptDest->vY);
  ptDest->vX = v1 * ptDest->vX;
  ptDest->vY = v1 * ptDest->vY;
  return ptDest;
}

// source: b/1/real.c:1284  [anchor-hash]
double __cdecl Real64x2_Len(struct real64x2_t *ptSource)
{
  return sqrt(ptSource->vX * ptSource->vX + ptSource->vY * ptSource->vY);
}

// source: b/1/real.c:1300  [anchor-hash]
double __cdecl Real64x2_SquaredLen(struct real64x2_t *ptSource)
{
  return ptSource->vX * ptSource->vX + ptSource->vY * ptSource->vY;
}

// source: b/1/real.c:1316  [size]
double __cdecl Real64x2_DotProduct(
        struct real64x2_t *ptSource0,
        struct real64x2_t *ptSource1)
{
  return ptSource0->vY * ptSource1->vY + ptSource0->vX * ptSource1->vX;
}

// source: b/1/real.c:1335  [size]
double __cdecl Real64x2_CrossProduct(
        struct real64x2_t *ptSource0,
        struct real64x2_t *ptSource1)
{
  return ptSource1->vY * ptSource0->vX - ptSource0->vY * ptSource1->vX;
}

// source: b/1/real.c:1985  [anchor-callee]
float __cdecl Real32x3_FastLen(struct real32x3_t *ptSource)
{
  double vZ; // st7
  double vX; // st6
  double vY; // st5
  struct real32x3_t tAbs; // 0:^0.12

  tAbs = *ptSource;
  if ( ptSource->vX < 0.0 )
    tAbs.vX = -tAbs.vX;
  if ( tAbs.vY < 0.0 )
    tAbs.vY = -tAbs.vY;
  if ( tAbs.vZ < 0.0 )
    tAbs.vZ = -tAbs.vZ;
  if ( tAbs.vX <= (double)tAbs.vY || tAbs.vX <= (double)tAbs.vZ )
  {
    if ( tAbs.vY <= (double)tAbs.vZ )
    {
      vZ = tAbs.vZ;
      if ( tAbs.vX > (double)tAbs.vY )
      {
        vX = tAbs.vX;
        vY = tAbs.vY;
        return vZ + vY * 0.3178372383117676 + vX * 0.4142135679721832;
      }
      vX = tAbs.vY;
    }
    else
    {
      vZ = tAbs.vY;
      if ( tAbs.vX > (double)tAbs.vZ )
      {
        vX = tAbs.vX;
        vY = tAbs.vZ;
        return vZ + vY * 0.3178372383117676 + vX * 0.4142135679721832;
      }
      vX = tAbs.vZ;
    }
    vY = tAbs.vX;
    return vZ + vY * 0.3178372383117676 + vX * 0.4142135679721832;
  }
  vZ = tAbs.vX;
  if ( tAbs.vY <= (double)tAbs.vZ )
  {
    vX = tAbs.vZ;
    vY = tAbs.vY;
  }
  else
  {
    vX = tAbs.vY;
    vY = tAbs.vZ;
  }
  return vZ + vY * 0.3178372383117676 + vX * 0.4142135679721832;
}

// source: b/1/real.c:2064  [anchor-mhash]
float __cdecl Real32x3_Angle(struct real32x3_t *ptSource0, struct real32x3_t *ptSource1)
{
  long double vCos; // [esp+0h] [ebp-1Ch]

  if ( ptSource0->vX == 0.0 && ptSource0->vY == 0.0 && ptSource0->vZ == 0.0 )
    return 0.0;
  if ( ptSource1->vX == 0.0 && ptSource1->vY == 0.0 && ptSource1->vZ == 0.0 )
    return 0.0;
  vCos = (ptSource0->vZ * ptSource1->vZ + ptSource0->vY * ptSource1->vY + ptSource0->vX * ptSource1->vX)
       / (sqrt(ptSource0->vX * ptSource0->vX + ptSource0->vY * ptSource0->vY + ptSource0->vZ * ptSource0->vZ)
        * sqrt(ptSource1->vX * ptSource1->vX + ptSource1->vY * ptSource1->vY + ptSource1->vZ * ptSource1->vZ));
  if ( vCos >= 1.0 )
  {
    return 0.0;
  }
  else if ( vCos > -1.0 )
  {
    return acos(vCos);
  }
  else
  {
    return 3.1415927410125732;
  }
}

// source: b/1/real.c:2110  [anchor-mhash]
int __cdecl Real32x3_ProjectPointToPlane(
        struct real32x3_t *ptDest,
        struct real32x3_t *ptRelativePos,
        struct real32x3_t *ptDirection,
        struct real32x3_t *ptPlaneNormal)
{
  double v4; // st7
  double v6; // st7

  v4 = ptDirection->vY * ptPlaneNormal->vY + ptDirection->vX * ptPlaneNormal->vX + ptPlaneNormal->vZ * ptDirection->vZ;
  if ( v4 > 9.999999747378752e-06 || v4 < -9.999999747378752e-06 )
  {
    v6 = (ptRelativePos->vZ * ptPlaneNormal->vZ
        + ptRelativePos->vX * ptPlaneNormal->vX
        + ptRelativePos->vY * ptPlaneNormal->vY)
       / v4;
    ptDest->vX = ptRelativePos->vX - v6 * ptDirection->vX;
    ptDest->vY = ptRelativePos->vY - v6 * ptDirection->vY;
    ptDest->vZ = ptRelativePos->vZ - v6 * ptDirection->vZ;
    return 1;
  }
  else
  {
    ptDest->vX = 0.0;
    ptDest->vY = 0.0;
    ptDest->vZ = 0.0;
    return 0;
  }
}

// source: b/1/real.c:2152  [anchor-callee]
void __cdecl Real32x3_GetAngles(struct real32x3_t *ptSource, float *pvBeta, float *pvGamma)
{
  long double v3; // st4
  float vValue; // [esp+0h] [ebp-8h]

  if ( ptSource->vX == 0.0 )
    *pvGamma = 0.0;
  else
    *pvGamma = atan2(ptSource->vY, ptSource->vX);
  v3 = sqrt(ptSource->vX * ptSource->vX + ptSource->vY * ptSource->vY + ptSource->vZ * ptSource->vZ);
  if ( v3 == 0.0 )
  {
    *pvBeta = 0.0;
  }
  else
  {
    vValue = ptSource->vZ / v3;
    *pvBeta = -Real32_Asin(vValue);
  }
}

// source: b/1/real.c:2199  [anchor-mhash]
char __cdecl Real32x3_PointOnTriangle(
        float *pvU,
        float *pvV,
        struct real32x3_t *ptRelativePos,
        struct real32x3_t *ptEdge0,
        struct real32x3_t *ptEdge1,
        struct real32x3_t *ptNormal)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real32x2_t tEdge1; };
    struct { char igi2_o1[8]; struct real32x2_t tEdge0; };
    struct { char igi2_o2[16]; float v18; };
    struct { char igi2_o3[20]; struct real32x3_t tNormal; };
    char igi2_extent[32];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v6; // st7
  double vX; // st7
  double vY; // st7
  float v9; // eax
  float vZ; // edx
  float v11; // eax
  float v12; // ecx
  float v13; // eax
  float v14; // eax

  igi2_frame.tEdge0.vX = ptEdge1->vZ * ptEdge0->vY - ptEdge0->vZ * ptEdge1->vY;
  v6 = ptEdge0->vX * ptEdge1->vZ;
  igi2_frame.tNormal.vX = igi2_frame.tEdge0.vX;
  igi2_frame.tEdge0.vY = -(v6 - ptEdge0->vZ * ptEdge1->vX);
  vX = ptEdge0->vX;
  igi2_frame.tNormal.vY = igi2_frame.tEdge0.vY;
  igi2_frame.v18 = vX * ptEdge1->vY - ptEdge1->vX * ptEdge0->vY;
  igi2_frame.tNormal.vZ = igi2_frame.v18;
  if ( igi2_frame.tEdge0.vX < 0.0 )
    igi2_frame.tNormal.vX = -igi2_frame.tEdge0.vX;
  vY = igi2_frame.tNormal.vY;
  if ( igi2_frame.tNormal.vY < 0.0 )
    vY = -vY;
  if ( igi2_frame.tNormal.vZ < 0.0 )
    igi2_frame.tNormal.vZ = -igi2_frame.tNormal.vZ;
  if ( igi2_frame.tNormal.vX > vY && igi2_frame.tNormal.vX > (double)igi2_frame.tNormal.vZ )
  {
    igi2_frame.tNormal.vX = ptRelativePos->vY;
    igi2_frame.tNormal.vY = ptRelativePos->vZ;
    v9 = ptEdge0->vY;
    vZ = ptEdge0->vZ;
    igi2_frame.tEdge0.vX = v9;
    v11 = ptEdge1->vY;
    v12 = ptEdge1->vZ;
LABEL_14:
    igi2_frame.tEdge1.vX = v11;
    igi2_frame.tEdge1.vY = v12;
    igi2_frame.tEdge0.vY = vZ;
    return Real32x2_PointOnTriangle(pvU, pvV, (struct real32x2_t *)&igi2_frame.tNormal, &igi2_frame.tEdge0, &igi2_frame.tEdge1);
  }
  if ( vY > igi2_frame.tNormal.vZ )
  {
    igi2_frame.tNormal.vX = ptRelativePos->vX;
    igi2_frame.tNormal.vY = ptRelativePos->vZ;
    v13 = ptEdge0->vX;
    vZ = ptEdge0->vZ;
    igi2_frame.tEdge0.vX = v13;
    v11 = ptEdge1->vX;
    v12 = ptEdge1->vZ;
    goto LABEL_14;
  }
  if ( igi2_frame.tNormal.vZ != 0.0 )
  {
    igi2_frame.tNormal.vX = ptRelativePos->vX;
    igi2_frame.tNormal.vY = ptRelativePos->vY;
    v14 = ptEdge0->vX;
    vZ = ptEdge0->vY;
    igi2_frame.tEdge0.vX = v14;
    v11 = ptEdge1->vX;
    v12 = ptEdge1->vY;
    goto LABEL_14;
  }
  return 0;
}

// source: b/1/real.c:2442  [anchor-mhash]
void __cdecl Real32x3_HSLFromRGB(
        struct real32x3_t *ptDest,
        struct real32x3_t *ptSource)
{
  double vY; // st7
  double vZ; // st7
  double vX; // st6
  float v5; // eax
  double v6; // st6
  double v7; // st7
  double v8; // st6
  double v9; // st6
  double v10; // st6
  float vDelta; // [esp+4h] [ebp-Ch]
  float v12; // [esp+8h] [ebp-8h]
  float vLight; // [esp+Ch] [ebp-4h]

  if ( ptSource->vX >= (double)ptSource->vY )
    vY = ptSource->vY;
  else
    vY = ptSource->vX;
  if ( vY >= ptSource->vZ )
  {
    vZ = ptSource->vZ;
  }
  else if ( ptSource->vX >= (double)ptSource->vY )
  {
    vZ = ptSource->vY;
  }
  else
  {
    vZ = ptSource->vX;
  }
  if ( ptSource->vX <= (double)ptSource->vY )
    vX = ptSource->vY;
  else
    vX = ptSource->vX;
  if ( vX <= ptSource->vZ )
  {
    v5 = ptSource->vZ;
  }
  else if ( ptSource->vX <= (double)ptSource->vY )
  {
    v5 = ptSource->vY;
  }
  else
  {
    v5 = ptSource->vX;
  }
  v6 = v5 + vZ;
  v12 = v6;
  vLight = v6 * 0.5;
  if ( v5 == vZ )
  {
    ptDest->vZ = vLight;
    ptDest->vX = -1.0;
    ptDest->vY = 0.0;
  }
  else
  {
    vDelta = v5 - vZ;
    if ( vLight > 0.5 )
      v7 = vDelta / (2.0 - v12);
    else
      v7 = vDelta / v12;
    v8 = ptSource->vY;
    if ( ptSource->vX == v5 )
    {
      v9 = (v8 - ptSource->vZ) / vDelta;
    }
    else if ( v8 == v5 )
    {
      v9 = (ptSource->vZ - ptSource->vX) / vDelta + 2.0;
    }
    else
    {
      v9 = (ptSource->vX - ptSource->vY) / vDelta + 4.0;
    }
    v10 = v9 * 60.0;
    if ( v10 < 0.0 )
      v10 = v10 + 360.0;
    ptDest->vX = v10;
    ptDest->vZ = vLight;
    ptDest->vY = v7;
  }
}

// source: b/1/real.c:2514  [anchor-mhash]
float __cdecl Real32_RGBFromHSL_Value(float vN1, float vN2, float vHue)
{
  double i; // st7

  for ( i = vHue; i > 360.0; i = i - 360.0 )
    ;
  for ( ; i < 0.0; i = i + 360.0 )
    ;
  if ( i >= 60.0 )
  {
    if ( i >= 180.0 )
    {
      if ( i >= 240.0 )
        return vN1;
      else
        return (vN2 - vN1) * (240.0 - i) * 0.01666666753590107 + vN1;
    }
    else
    {
      return vN2;
    }
  }
  else
  {
    return i * (vN2 - vN1) * 0.01666666753590107 + vN1;
  }
}

// source: b/1/real.c:2553  [anchor-mhash]
void __cdecl Real32x3_RGBFromHSL(
        struct real32x3_t *ptDest,
        struct real32x3_t *ptSource)
{
  double vY; // st7
  double v3; // st6
  double v4; // st6
  float vHue; // [esp+0h] [ebp-18h]
  float vHuea; // [esp+0h] [ebp-18h]
  float vLight; // [esp+8h] [ebp-10h]
  float vM2; // [esp+Ch] [ebp-Ch]
  float vX; // [esp+10h] [ebp-8h]
  float vM1; // [esp+14h] [ebp-4h]

  vY = ptSource->vY;
  vLight = ptSource->vZ;
  vX = ptSource->vX;
  v3 = vLight + vY;
  if ( vLight > 0.5 )
    v4 = v3 - vLight * vY;
  else
    v4 = v3 * vLight;
  vM2 = v4;
  vM1 = vLight + vLight - vM2;
  if ( vY == 0.0 )
  {
    ptDest->vX = vLight;
    ptDest->vY = vLight;
    ptDest->vZ = vLight;
  }
  else
  {
    vHue = vX + 120.0;
    ptDest->vX = Real32_RGBFromHSL_Value(vM1, vM2, vHue);
    ptDest->vY = Real32_RGBFromHSL_Value(vM1, vM2, vX);
    vHuea = vX - 120.0;
    ptDest->vZ = Real32_RGBFromHSL_Value(vM1, vM2, vHuea);
  }
}

// source: b/1/real.c:2596  [anchor-mhash]
void __cdecl Real32x3_HSVFromRGB(
        struct real32x3_t *ptDest,
        struct real32x3_t *ptSource)
{
  double vY; // st7
  float vZ; // eax
  double vX; // st7
  double v5; // st7
  double v6; // st6
  double v7; // st6
  double v8; // st5
  double v9; // st4
  double v10; // st5
  double i; // st5
  float vMin; // [esp+0h] [ebp-4h]

  if ( ptSource->vX >= (double)ptSource->vY )
    vY = ptSource->vY;
  else
    vY = ptSource->vX;
  if ( vY >= ptSource->vZ )
  {
    vZ = ptSource->vZ;
  }
  else if ( ptSource->vX >= (double)ptSource->vY )
  {
    vZ = ptSource->vY;
  }
  else
  {
    vZ = ptSource->vX;
  }
  if ( ptSource->vX <= (double)ptSource->vY )
    vX = ptSource->vY;
  else
    vX = ptSource->vX;
  if ( vX <= ptSource->vZ )
  {
    v5 = ptSource->vZ;
  }
  else if ( ptSource->vX <= (double)ptSource->vY )
  {
    v5 = ptSource->vY;
  }
  else
  {
    v5 = ptSource->vX;
  }
  if ( v5 == 0.0 )
  {
    ptDest->vX = -1.0;
    ptDest->vY = 0.0;
    ptDest->vZ = v5;
  }
  else
  {
    v6 = v5 - vZ;
    vMin = v6;
    v7 = v6 / v5;
    if ( v7 == 0.0 )
    {
      ptDest->vX = -1.0;
      ptDest->vY = v7;
      ptDest->vZ = v5;
    }
    else
    {
      v8 = vMin;
      v9 = ptSource->vY;
      if ( ptSource->vX == v5 )
      {
        v10 = (v9 - ptSource->vZ) / v8;
      }
      else if ( v9 == v5 )
      {
        v10 = (ptSource->vZ - ptSource->vX) / v8 + 2.0;
      }
      else
      {
        v10 = (ptSource->vX - ptSource->vY) / v8 + 4.0;
      }
      for ( i = v10 * 60.0; i < 0.0; i = i + 360.0 )
        ;
      for ( ; i >= 360.0; i = i - 360.0 )
        ;
      ptDest->vX = i;
      ptDest->vY = v7;
      ptDest->vZ = v5;
    }
  }
}

// source: b/1/real.c:2672  [anchor-mhash]
void __cdecl Real32x3_RGBFromHSV(
        struct real32x3_t *ptDest,
        struct real32x3_t *ptSource)
{
  double vZ; // st7
  double v3; // st5
  double v4; // st6
  float v5; // [esp+0h] [ebp-10h]
  float vY; // [esp+4h] [ebp-Ch]
  float v7; // [esp+4h] [ebp-Ch]
  float v8; // [esp+8h] [ebp-8h]

  vZ = ptSource->vZ;
  vY = ptSource->vY;
  if ( vY == 0.0 )
  {
    ptDest->vX = ptSource->vZ;
    ptDest->vY = vZ;
    ptDest->vZ = vZ;
  }
  else
  {
    v3 = ptSource->vX * 0.01666666753590107;
    v4 = v3 - (double)(int)(__int64)v3;
    v5 = (1.0 - vY) * vZ;
    v8 = (1.0 - vY * v4) * vZ;
    v7 = (1.0 - (1.0 - v4) * vY) * vZ;
    switch ( (unsigned int)(__int64)v3 )
    {
      case 0u:
        ptDest->vX = ptSource->vZ;
        ptDest->vY = v7;
        ptDest->vZ = v5;
        break;
      case 1u:
        ptDest->vY = ptSource->vZ;
        ptDest->vX = v8;
        ptDest->vZ = v5;
        break;
      case 2u:
        ptDest->vY = ptSource->vZ;
        ptDest->vX = v5;
        ptDest->vZ = v7;
        break;
      case 3u:
        ptDest->vZ = ptSource->vZ;
        ptDest->vX = v5;
        ptDest->vY = v8;
        break;
      case 4u:
        ptDest->vZ = ptSource->vZ;
        ptDest->vX = v7;
        ptDest->vY = v5;
        break;
      case 5u:
        ptDest->vX = ptSource->vZ;
        ptDest->vY = v5;
        ptDest->vZ = v8;
        break;
      default:
        return;
    }
  }
}

// source: b/1/real.c:3130  [anchor-mhash]
struct real64x3_t *__cdecl Real64x3_ScaleToLength(struct real64x3_t *ptDest, double vNewLen)
{
  long double v2; // st4

  v2 = 1.0 / sqrt(ptDest->vX * ptDest->vX + ptDest->vY * ptDest->vY + ptDest->vZ * ptDest->vZ);
  ptDest->vX = v2 * ptDest->vX * vNewLen;
  ptDest->vY = v2 * ptDest->vY * vNewLen;
  ptDest->vZ = v2 * vNewLen * ptDest->vZ;
  return ptDest;
}

// source: b/1/real.c:3161  [anchor-hash]
struct real64x3_t *__cdecl Real64x3_Normalize(struct real64x3_t *ptDest)
{
  long double v1; // st4

  v1 = 1.0 / sqrt(ptDest->vX * ptDest->vX + ptDest->vY * ptDest->vY + ptDest->vZ * ptDest->vZ);
  ptDest->vX = v1 * ptDest->vX;
  ptDest->vY = v1 * ptDest->vY;
  ptDest->vZ = v1 * ptDest->vZ;
  return ptDest;
}

// source: b/1/real.c:3193  [anchor-callee]
double __cdecl Real64x3_Len(struct real64x3_t *ptSource)
{
  return sqrt(ptSource->vX * ptSource->vX + ptSource->vY * ptSource->vY + ptSource->vZ * ptSource->vZ);
}

// source: b/1/real.c:3215  [anchor-hash]
double __cdecl Real64x3_FastLen(struct real64x3_t *ptSource)
{
  return sqrt(ptSource->vX * ptSource->vX + ptSource->vY * ptSource->vY + ptSource->vZ * ptSource->vZ);
}

// source: b/1/real.c:3233  [anchor-hash]
double __cdecl Real64x3_SquaredLen(struct real64x3_t *ptSource)
{
  return ptSource->vX * ptSource->vX + ptSource->vY * ptSource->vY + ptSource->vZ * ptSource->vZ;
}

// source: b/1/real.c:3249  [anchor-mhash]
struct real64x3_t *__cdecl Real64x3_CrossProduct(
        struct real64x3_t *ptDest,
        struct real64x3_t *ptSource0,
        struct real64x3_t *ptSource1)
{
  struct real64x3_t tTemp; // [esp+8h] [ebp-1Ch] BYREF

  tTemp.vX = ptSource1->vZ * ptSource0->vY - ptSource0->vZ * ptSource1->vY;
  tTemp.vY = -(ptSource1->vZ * ptSource0->vX - ptSource0->vZ * ptSource1->vX);
  tTemp.vZ = ptSource0->vX * ptSource1->vY - ptSource1->vX * ptSource0->vY;
  qmemcpy(ptDest, &tTemp, sizeof(struct real64x3_t));
  return ptSource1;
}

// source: b/1/real.c:3274  [anchor-callee]
double __cdecl Real64x3_Angle(struct real64x3_t *ptSource0, struct real64x3_t *ptSource1)
{
  long double vCos; // [esp+10h] [ebp-Ch]

  if ( ptSource0->vX == 0.0 && ptSource0->vY == 0.0 && ptSource0->vZ == 0.0 )
    return 0.0;
  if ( ptSource1->vX == 0.0 && ptSource1->vY == 0.0 && ptSource1->vZ == 0.0 )
    return 0.0;
  vCos = (ptSource0->vX * ptSource1->vX + ptSource0->vZ * ptSource1->vZ + ptSource0->vY * ptSource1->vY)
       / (sqrt(ptSource0->vY * ptSource0->vY + ptSource0->vZ * ptSource0->vZ + ptSource0->vX * ptSource0->vX)
        * sqrt(ptSource1->vY * ptSource1->vY + ptSource1->vZ * ptSource1->vZ + ptSource1->vX * ptSource1->vX));
  if ( vCos >= 1.0 )
    return 0.0;
  if ( vCos > -1.0 )
    return acos(vCos);
  return 3.1415926535897944;
}

// source: b/1/real.c:3317  [anchor-callee]
double __cdecl Real64x3_Distance(
        struct real64x3_t *ptSource0,
        struct real64x3_t *ptSource1)
{
  double v2; // st6
  double v3; // st5

  v2 = ptSource0->vY - ptSource1->vY;
  v3 = ptSource0->vZ - ptSource1->vZ;
  return sqrt(v3 * v3 + v2 * v2 + (ptSource0->vX - ptSource1->vX) * (ptSource0->vX - ptSource1->vX));
}

// source: b/1/real.c:3339  [anchor-mhash]
double __cdecl Real64x3_SquaredDistance(
        struct real64x3_t *ptSource0,
        struct real64x3_t *ptSource1)
{
  double v2; // st6
  double v3; // st5

  v2 = ptSource0->vY - ptSource1->vY;
  v3 = ptSource0->vZ - ptSource1->vZ;
  return v3 * v3 + v2 * v2 + (ptSource0->vX - ptSource1->vX) * (ptSource0->vX - ptSource1->vX);
}

// source: b/1/real.c:3361  [anchor-callee]
char __cdecl Real64x3_NullVector(struct real64x3_t *ptSource)
{
  return ptSource->vX == 0.0 && ptSource->vY == 0.0 && ptSource->vZ == 0.0;
}

// source: b/1/real.c:3380  [anchor-mhash]
char __cdecl Real64x3_Equal(
        struct real64x3_t *ptSource0,
        struct real64x3_t *ptSource1)
{
  return ptSource0->vX == ptSource1->vX && ptSource0->vY == ptSource1->vY && ptSource0->vZ == ptSource1->vZ;
}

// source: b/1/real.c:3541  [anchor-mhash]
enum bool __cdecl Real32x4_InvertSafe(
        struct real32x4_t *ptDest,
        struct real32x4_t *ptSource)
{
  double v2; // st7
  double v3; // st7
  enum bool result; // eax
  struct real32x4_t tTemp; // 0:^0.16

  tTemp = *ptSource;
  v2 = tTemp.tY.vY * ptSource->tX.vX - tTemp.tY.vX * tTemp.tX.vY;
  if ( v2 == 0.0 )
    return false;
  v3 = 1.0 / v2;
  result = true;
  ptDest->tX.vX = tTemp.tY.vY * v3;
  ptDest->tX.vY = -(tTemp.tX.vY * v3);
  ptDest->tY.vX = -(tTemp.tY.vX * v3);
  ptDest->tY.vY = tTemp.tX.vX * v3;
  return result;
}

// source: b/1/real.c:4039  [anchor-callee]
struct real32x9_t *__cdecl Real32x9_Rotate(
        struct real32x9_t *ptDest,
        struct real32x9_t *ptSource,
        float vAlpha,
        float vBeta,
        float vGamma)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real32x9_t tTemp; };
    struct { char igi2_o1[40]; struct real32x9_t Real32x9_Multiply_tTemp; };
    char igi2_extent[84];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct real32x9_t *result; // eax
  double v7; // st7
  double v8; // st6

  Real32x9_Create(&igi2_frame.tTemp, vAlpha, vBeta, vGamma);
  igi2_frame.Real32x9_Multiply_tTemp.tX.vX = igi2_frame.tTemp.tX.vX * ptSource->tX.vX
                                + igi2_frame.tTemp.tX.vZ * ptSource->tZ.vX
                                + igi2_frame.tTemp.tX.vY * ptSource->tY.vX;
  igi2_frame.Real32x9_Multiply_tTemp.tX.vY = igi2_frame.tTemp.tX.vX * ptSource->tX.vY
                                + igi2_frame.tTemp.tX.vZ * ptSource->tZ.vY
                                + igi2_frame.tTemp.tX.vY * ptSource->tY.vY;
  igi2_frame.Real32x9_Multiply_tTemp.tX.vZ = igi2_frame.tTemp.tX.vX * ptSource->tX.vZ
                                + igi2_frame.tTemp.tX.vZ * ptSource->tZ.vZ
                                + igi2_frame.tTemp.tX.vY * ptSource->tY.vZ;
  igi2_frame.Real32x9_Multiply_tTemp.tY.vX = igi2_frame.tTemp.tY.vX * ptSource->tX.vX
                                + igi2_frame.tTemp.tY.vZ * ptSource->tZ.vX
                                + igi2_frame.tTemp.tY.vY * ptSource->tY.vX;
  igi2_frame.Real32x9_Multiply_tTemp.tY.vY = igi2_frame.tTemp.tY.vX * ptSource->tX.vY
                                + igi2_frame.tTemp.tY.vZ * ptSource->tZ.vY
                                + igi2_frame.tTemp.tY.vY * ptSource->tY.vY;
  igi2_frame.Real32x9_Multiply_tTemp.tY.vZ = igi2_frame.tTemp.tY.vX * ptSource->tX.vZ
                                + igi2_frame.tTemp.tY.vZ * ptSource->tZ.vZ
                                + igi2_frame.tTemp.tY.vY * ptSource->tY.vZ;
  igi2_frame.Real32x9_Multiply_tTemp.tZ.vX = igi2_frame.tTemp.tZ.vX * ptSource->tX.vX
                                + igi2_frame.tTemp.tZ.vZ * ptSource->tZ.vX
                                + igi2_frame.tTemp.tZ.vY * ptSource->tY.vX;
  result = (struct real32x9_t *)ptSource->nOps;
  v7 = igi2_frame.tTemp.tZ.vX * ptSource->tX.vY;
  v8 = igi2_frame.tTemp.tZ.vZ * ptSource->tZ.vY;
  igi2_frame.Real32x9_Multiply_tTemp.nOps = (int)&result->tX.vX + igi2_frame.tTemp.nOps + 1;
  igi2_frame.Real32x9_Multiply_tTemp.tZ.vY = v7 + v8 + igi2_frame.tTemp.tZ.vY * ptSource->tY.vY;
  igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ = igi2_frame.tTemp.tZ.vX * ptSource->tX.vZ
                                + igi2_frame.tTemp.tZ.vZ * ptSource->tZ.vZ
                                + igi2_frame.tTemp.tZ.vY * ptSource->tY.vZ;
  qmemcpy(ptDest, &igi2_frame.Real32x9_Multiply_tTemp, sizeof(struct real32x9_t));
  return result;
}

// source: b/1/real.c:4063  [anchor-callee]
struct real32x9_t *__cdecl Real32x9_RotateAlpha(
        struct real32x9_t *ptDest,
        struct real32x9_t *ptSource,
        float vAngle)
{
  long double v3; // st7
  long double v4; // st6
  long double v5; // st5
  double v6; // st4
  double v7; // st4
  long double v8; // st3
  double v9; // st7
  long double v10; // rtt
  long double v11; // st5
  struct real32x9_t *result; // eax
  struct real32x9_t Real32x9_Multiply_tTemp; // [esp+0h] [ebp-28h] BYREF

  v3 = sin(vAngle);
  v4 = cos(vAngle);
  v5 = -v3;
  Real32x9_Multiply_tTemp.tX.vX = (ptSource->tX.vZ + ptSource->tX.vY) * 0.0 + ptSource->tX.vX;
  v6 = ptSource->tX.vX * 0.0;
  Real32x9_Multiply_tTemp.tX.vY = v4 * ptSource->tX.vY + v3 * ptSource->tX.vZ + v6;
  Real32x9_Multiply_tTemp.tX.vZ = v4 * ptSource->tX.vZ + -v3 * ptSource->tX.vY + v6;
  Real32x9_Multiply_tTemp.tY.vX = (ptSource->tY.vZ + ptSource->tY.vY) * 0.0 + ptSource->tY.vX;
  v7 = ptSource->tY.vX * 0.0;
  Real32x9_Multiply_tTemp.tY.vY = v4 * ptSource->tY.vY + v3 * ptSource->tY.vZ + v7;
  Real32x9_Multiply_tTemp.tY.vZ = v4 * ptSource->tY.vZ + -v3 * ptSource->tY.vY + v7;
  Real32x9_Multiply_tTemp.tZ.vX = (ptSource->tZ.vZ + ptSource->tZ.vY) * 0.0 + ptSource->tZ.vX;
  v8 = v3 * ptSource->tZ.vZ;
  v9 = ptSource->tZ.vX * 0.0;
  Real32x9_Multiply_tTemp.tZ.vY = v4 * ptSource->tZ.vY + v8 + v9;
  v10 = v4 * ptSource->tZ.vZ;
  v11 = v5 * ptSource->tZ.vY;
  result = (struct real32x9_t *)(ptSource->nOps + 1);
  Real32x9_Multiply_tTemp.nOps = (int)result;
  Real32x9_Multiply_tTemp.tZ.vZ = v10 + v11 + v9;
  qmemcpy(ptDest, &Real32x9_Multiply_tTemp, sizeof(struct real32x9_t));
  return result;
}

// source: b/1/real.c:4085  [anchor-mhash]
struct real32x9_t *__cdecl Real32x9_RotateBeta(
        struct real32x9_t *ptDest,
        struct real32x9_t *ptSource,
        float vAngle)
{
  long double v3; // st7
  long double v4; // st6
  double v5; // st4
  double v6; // st4
  long double v7; // rt2
  long double v8; // st6
  struct real32x9_t *result; // eax
  struct real32x9_t Real32x9_Multiply_tTemp; // [esp+0h] [ebp-28h] BYREF
  float ptDesta = *(float *)&vAngle; // [esp+2Ch] [ebp+4h] ARGSLOT

  v3 = sin(vAngle);
  v4 = cos(vAngle);
  v5 = ptSource->tX.vY * 0.0;
  Real32x9_Multiply_tTemp.tX.vX = v4 * ptSource->tX.vX + -v3 * ptSource->tX.vZ + v5;
  Real32x9_Multiply_tTemp.tX.vY = (ptSource->tX.vX + ptSource->tX.vZ) * 0.0 + ptSource->tX.vY;
  Real32x9_Multiply_tTemp.tX.vZ = v3 * ptSource->tX.vX + v4 * ptSource->tX.vZ + v5;
  v6 = ptSource->tY.vY * 0.0;
  Real32x9_Multiply_tTemp.tY.vX = -v3 * ptSource->tY.vZ + v4 * ptSource->tY.vX + v6;
  Real32x9_Multiply_tTemp.tY.vY = (ptSource->tY.vX + ptSource->tY.vZ) * 0.0 + ptSource->tY.vY;
  Real32x9_Multiply_tTemp.tY.vZ = v4 * ptSource->tY.vZ + v3 * ptSource->tY.vX + v6;
  ptDesta = ptSource->tZ.vY * 0.0;
  Real32x9_Multiply_tTemp.tZ.vX = v4 * ptSource->tZ.vX + -v3 * ptSource->tZ.vZ + ptDesta;
  Real32x9_Multiply_tTemp.tZ.vY = (ptSource->tZ.vX + ptSource->tZ.vZ) * 0.0 + ptSource->tZ.vY;
  v7 = v3 * ptSource->tZ.vX;
  v8 = v4 * ptSource->tZ.vZ;
  result = (struct real32x9_t *)(ptSource->nOps + 1);
  Real32x9_Multiply_tTemp.nOps = (int)result;
  Real32x9_Multiply_tTemp.tZ.vZ = v7 + v8 + ptDesta;
  qmemcpy(ptDest, &Real32x9_Multiply_tTemp, sizeof(struct real32x9_t));
  return result;
}

// source: b/1/real.c:4107  [anchor-callee]
struct real32x9_t *__cdecl Real32x9_RotateGamma(
        struct real32x9_t *ptDest,
        struct real32x9_t *ptSource,
        float vAngle)
{
  long double v3; // st7
  long double v4; // st6
  long double v5; // st5
  double v6; // st4
  double v7; // st4
  long double v8; // st3
  double v9; // st7
  double v10; // st7
  struct real32x9_t *result; // eax
  struct real32x9_t Real32x9_Multiply_tTemp; // [esp+0h] [ebp-28h] BYREF

  v3 = sin(vAngle);
  v4 = cos(vAngle);
  v5 = -v3;
  v6 = ptSource->tX.vZ * 0.0;
  Real32x9_Multiply_tTemp.tX.vX = v4 * ptSource->tX.vX + v3 * ptSource->tX.vY + v6;
  Real32x9_Multiply_tTemp.tX.vY = -v3 * ptSource->tX.vX + v4 * ptSource->tX.vY + v6;
  Real32x9_Multiply_tTemp.tX.vZ = (ptSource->tX.vX + ptSource->tX.vY) * 0.0 + ptSource->tX.vZ;
  v7 = ptSource->tY.vZ * 0.0;
  Real32x9_Multiply_tTemp.tY.vX = v3 * ptSource->tY.vY + v4 * ptSource->tY.vX + v7;
  Real32x9_Multiply_tTemp.tY.vY = v4 * ptSource->tY.vY + -v3 * ptSource->tY.vX + v7;
  Real32x9_Multiply_tTemp.tY.vZ = (ptSource->tY.vX + ptSource->tY.vY) * 0.0 + ptSource->tY.vZ;
  v8 = v3 * ptSource->tZ.vY;
  v9 = ptSource->tZ.vZ * 0.0;
  Real32x9_Multiply_tTemp.tZ.vX = v4 * ptSource->tZ.vX + v8 + v9;
  Real32x9_Multiply_tTemp.tZ.vY = v4 * ptSource->tZ.vY + v5 * ptSource->tZ.vX + v9;
  v10 = (ptSource->tZ.vX + ptSource->tZ.vY) * 0.0 + ptSource->tZ.vZ;
  result = (struct real32x9_t *)(ptSource->nOps + 1);
  Real32x9_Multiply_tTemp.nOps = (int)result;
  Real32x9_Multiply_tTemp.tZ.vZ = v10;
  qmemcpy(ptDest, &Real32x9_Multiply_tTemp, sizeof(struct real32x9_t));
  return result;
}

// source: b/1/real.c:4129  [anchor-callee]
struct real32x9_t *__cdecl Real32x9_Create(
        struct real32x9_t *ptDest,
        float vAlpha,
        float vBeta,
        float vGamma)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v18; };
    struct { char igi2_o1[4]; float v19; };
    struct { char igi2_o2[8]; struct real32x9_t Real32x9_Multiply_tTemp; };
    struct { char igi2_o3[48]; struct real32x9_t tTempMatrix; };
    char igi2_extent[88];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  long double v4; // st7
  long double v5; // st6
  double v6; // st4
  double v7; // st4
  long double v8; // st3
  long double v9; // st7
  long double v10; // st6
  long double v11; // st5
  double v12; // st4
  double v13; // st4
  double v14; // st4
  long double v15; // st3
  long double v16; // st7
  long double v17; // st3
  float vAlphaa = *(float *)&vBeta; // [esp+60h] [ebp+8h] ARGSLOT
  float vBetaa = *(float *)&vGamma; // [esp+64h] [ebp+Ch] ARGSLOT

  v4 = sin(vGamma);
  ptDest->tX.vZ = 0.0;
  ptDest->tY.vZ = 0.0;
  ptDest->tZ.vX = 0.0;
  ptDest->tZ.vY = 0.0;
  ptDest->tZ.vZ = 1.0;
  ptDest->nOps = 0;
  v5 = cos(vGamma);
  ptDest->tX.vX = v5;
  ptDest->tX.vY = -v4;
  ptDest->tY.vX = v4;
  ptDest->tY.vY = v5;
  vBetaa = sin(vBeta);
  vAlphaa = cos(vBeta);
  v6 = -vBetaa;
  igi2_frame.tTempMatrix.tZ.vX = v6;
  v7 = v6 * 0.0;
  v8 = -v4 * 0.0;
  igi2_frame.Real32x9_Multiply_tTemp.tX.vX = vAlphaa * v5 + v8 + v7;
  igi2_frame.v18 = v5 * 0.0;
  igi2_frame.Real32x9_Multiply_tTemp.tX.vY = igi2_frame.v18 - v4;
  igi2_frame.v19 = vAlphaa * 0.0;
  igi2_frame.Real32x9_Multiply_tTemp.tX.vZ = vBetaa * v5 + igi2_frame.v19 + v8;
  igi2_frame.Real32x9_Multiply_tTemp.tY.vX = vAlphaa * v4 + igi2_frame.v18 + v7;
  igi2_frame.Real32x9_Multiply_tTemp.tY.vY = v4 * 0.0 + v5;
  igi2_frame.Real32x9_Multiply_tTemp.tY.vZ = vBetaa * v4 + igi2_frame.v19 + igi2_frame.v18;
  igi2_frame.Real32x9_Multiply_tTemp.tZ.vX = igi2_frame.v19 + igi2_frame.tTempMatrix.tZ.vX;
  igi2_frame.Real32x9_Multiply_tTemp.tZ.vY = 0.0;
  igi2_frame.Real32x9_Multiply_tTemp.nOps = 1;
  igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ = vBetaa * 0.0 + vAlphaa;
  qmemcpy(ptDest, &igi2_frame.Real32x9_Multiply_tTemp, sizeof(struct real32x9_t));
  v9 = sin(vAlpha);
  v10 = cos(vAlpha);
  v11 = -v9;
  igi2_frame.Real32x9_Multiply_tTemp.tX.vX = (ptDest->tX.vZ + ptDest->tX.vY) * 0.0 + ptDest->tX.vX;
  v12 = ptDest->tX.vX * 0.0;
  igi2_frame.Real32x9_Multiply_tTemp.tX.vY = v10 * ptDest->tX.vY + v9 * ptDest->tX.vZ + v12;
  igi2_frame.Real32x9_Multiply_tTemp.tX.vZ = v10 * ptDest->tX.vZ + -v9 * ptDest->tX.vY + v12;
  igi2_frame.Real32x9_Multiply_tTemp.tY.vX = (ptDest->tY.vY + ptDest->tY.vZ) * 0.0 + ptDest->tY.vX;
  v13 = ptDest->tY.vX * 0.0;
  igi2_frame.Real32x9_Multiply_tTemp.tY.vY = v9 * ptDest->tY.vZ + v10 * ptDest->tY.vY + v13;
  igi2_frame.Real32x9_Multiply_tTemp.tY.vZ = v10 * ptDest->tY.vZ + -v9 * ptDest->tY.vY + v13;
  igi2_frame.Real32x9_Multiply_tTemp.tZ.vX = (ptDest->tZ.vZ + ptDest->tZ.vY) * 0.0 + ptDest->tZ.vX;
  v14 = ptDest->tZ.vX * 0.0;
  v15 = v9;
  v16 = v10 * ptDest->tZ.vY;
  v17 = v15 * ptDest->tZ.vZ;
  igi2_frame.Real32x9_Multiply_tTemp.nOps = ptDest->nOps + 1;
  igi2_frame.Real32x9_Multiply_tTemp.tZ.vY = v16 + v17 + v14;
  igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ = v10 * ptDest->tZ.vZ + v11 * ptDest->tZ.vY + v14;
  qmemcpy(ptDest, &igi2_frame.Real32x9_Multiply_tTemp, sizeof(struct real32x9_t));
  ptDest->nOps = 0;
  return ptDest;
}

// source: b/1/real.c:4159  [anchor-callee]
struct real32x9_t *__cdecl Real32x9_CreateAlpha(struct real32x9_t *ptDest, float vAngle)
{
  long double v2; // st7
  long double v3; // st6

  v2 = sin(vAngle);
  ptDest->tX.vX = 1.0;
  ptDest->tX.vY = 0.0;
  ptDest->tX.vZ = 0.0;
  ptDest->tY.vX = 0.0;
  ptDest->tZ.vX = 0.0;
  ptDest->nOps = 0;
  v3 = cos(vAngle);
  ptDest->tY.vY = v3;
  ptDest->tY.vZ = -v2;
  ptDest->tZ.vY = v2;
  ptDest->tZ.vZ = v3;
  return ptDest;
}

// source: b/1/real.c:4195  [anchor-mhash]
struct real32x9_t *__cdecl Real32x9_CreateBeta(struct real32x9_t *ptDest, float vAngle)
{
  long double v2; // st6
  long double v3; // st5

  ptDest->tX.vY = 0.0;
  ptDest->tY.vX = 0.0;
  ptDest->tY.vY = 1.0;
  ptDest->tY.vZ = 0.0;
  ptDest->tZ.vY = 0.0;
  ptDest->nOps = 0;
  v2 = cos(vAngle);
  ptDest->tX.vX = v2;
  v3 = sin(vAngle);
  ptDest->tX.vZ = v3;
  ptDest->tZ.vX = -v3;
  ptDest->tZ.vZ = v2;
  return ptDest;
}

// source: b/1/real.c:4231  [anchor-callee]
struct real32x9_t *__cdecl Real32x9_CreateGamma(struct real32x9_t *ptDest, float vAngle)
{
  long double v2; // st7
  long double v3; // st6

  v2 = sin(vAngle);
  ptDest->tX.vZ = 0.0;
  ptDest->tY.vZ = 0.0;
  ptDest->tZ.vX = 0.0;
  ptDest->tZ.vY = 0.0;
  ptDest->tZ.vZ = 1.0;
  ptDest->nOps = 0;
  v3 = cos(vAngle);
  ptDest->tX.vX = v3;
  ptDest->tX.vY = -v2;
  ptDest->tY.vX = v2;
  ptDest->tY.vY = v3;
  return ptDest;
}

// source: b/1/real.c:4267  [anchor-mhash]
struct real32x9_t *__cdecl Real32x9_CreateDiagonal(
        struct real32x9_t *ptDest,
        float v11,
        float v22,
        float v33)
{
  ptDest->tX.vX = v11;
  ptDest->tZ.vZ = v33;
  ptDest->tY.vY = v22;
  ptDest->tX.vY = 0.0;
  ptDest->tX.vZ = 0.0;
  ptDest->tY.vX = 0.0;
  ptDest->tY.vZ = 0.0;
  ptDest->tZ.vX = 0.0;
  ptDest->tZ.vY = 0.0;
  ptDest->nOps = 0;
  return ptDest;
}

// source: b/1/real.c:4297  [anchor-strings]
void __cdecl Real32x9_GetAngles(struct real32x9_t *ptSource, float *pvAlpha, float *pvBeta, float *pvGamma)
{
  long double v4; // st7
  double v5; // st6
  double v6; // st6
  double v7; // st7
  double v8; // st7
  double v9; // st7
  long double vX; // st6
  long double v11; // st6
  double v12; // st6
  double v13; // st6
  double v14; // st7
  double v15; // st7
  double v16; // st6
  double vGamma; // [esp+0h] [ebp-10h]
  double vAlpha; // [esp+8h] [ebp-8h]

  v4 = sqrt(ptSource->tY.vX * ptSource->tY.vX + ptSource->tX.vX * ptSource->tX.vX);
  if ( v4 <= 0.0001 )
  {
    v11 = -ptSource->tY.vZ;
    if ( ptSource->tY.vY == 0.0 )
    {
      if ( v11 == 0.0 )
        goto LABEL_5;
      if ( v11 >= 0.0 )
        v13 = 1.0;
      else
        v13 = -1.0;
      v12 = v13 * 1.5707963267948972;
    }
    else
    {
      v12 = atan2(v11, ptSource->tY.vY);
    }
    vAlpha = v12;
    if ( v4 == 0.0 )
    {
      v14 = -ptSource->tZ.vX;
      if ( v14 == 0.0 )
        goto LABEL_5;
      if ( v14 >= 0.0 )
        v15 = 1.0;
      else
        v15 = -1.0;
      v7 = v15 * 1.5707963267948972;
    }
    else
    {
      v7 = atan2(-ptSource->tZ.vX, v4);
    }
    vGamma = 0.0;
    goto LABEL_38;
  }
  if ( ptSource->tZ.vZ == 0.0 )
  {
    if ( ptSource->tZ.vY == 0.0 )
      goto LABEL_5;
    if ( ptSource->tZ.vY >= 0.0 )
      v6 = 1.0;
    else
      v6 = -1.0;
    v5 = v6 * 1.5707963267948972;
  }
  else
  {
    v5 = atan2(ptSource->tZ.vY, ptSource->tZ.vZ);
  }
  vAlpha = v5;
  if ( v4 == 0.0 )
  {
    v8 = -ptSource->tZ.vX;
    if ( v8 == 0.0 )
      goto LABEL_5;
    if ( v8 >= 0.0 )
      v9 = 1.0;
    else
      v9 = -1.0;
    v7 = v9 * 1.5707963267948972;
  }
  else
  {
    v7 = atan2(-ptSource->tZ.vX, v4);
  }
  vX = ptSource->tY.vX;
  if ( ptSource->tX.vX != 0.0 )
  {
    vGamma = atan2(vX, ptSource->tX.vX);
    goto LABEL_38;
  }
  if ( vX == 0.0 )
  {
LABEL_5:
    LDebug_Error("Atan2 undefined in origo");
    abort();
  }
  if ( ptSource->tY.vX >= 0.0 )
    vGamma = 1.0 * 1.5707963267948972;
  else
    vGamma = -1.0 * 1.5707963267948972;
LABEL_38:
  v16 = vAlpha;
  if ( vAlpha < 0.0 )
    v16 = vAlpha + 6.283185307179589;
  if ( v7 < 0.0 )
    v7 = v7 + 6.283185307179589;
  if ( vGamma < 0.0 )
    vGamma = vGamma + 6.283185307179589;
  *pvAlpha = v16;
  *pvBeta = v7;
  *pvGamma = vGamma;
}

// source: b/1/real.c:4383  [anchor-callee]
struct real32x9_t *__cdecl Real32x9_CreateRotationAroundAxis(
        struct real32x9_t *ptDest,
        struct real32x3_t *ptUnitAxis,
        float vRadians)
{
  long double v3; // st7
  long double v4; // st6
  long double v5; // rt0
  long double v6; // st6
  long double v7; // st7
  double v8; // st7
  float vZZ; // [esp+0h] [ebp-30h]
  float vXZ; // [esp+4h] [ebp-2Ch]
  float vYW; // [esp+8h] [ebp-28h]
  float vYZ; // [esp+Ch] [ebp-24h]
  float vXW; // [esp+10h] [ebp-20h]
  float vYY; // [esp+14h] [ebp-1Ch]
  float vXX; // [esp+18h] [ebp-18h]
  float tQuat32; // [esp+1Ch] [ebp-14h]
  float tQuat32_4; // [esp+20h] [ebp-10h]
  float ptDesta = *(float *)&vRadians; // [esp+34h] [ebp+4h] ARGSLOT

  v3 = vRadians * 0.5;
  v4 = sin(v3);
  tQuat32 = v4 * ptUnitAxis->vX;
  tQuat32_4 = v4 * ptUnitAxis->vY;
  v5 = v4 * ptUnitAxis->vZ;
  v6 = cos(v3);
  vXX = tQuat32 * tQuat32 + tQuat32 * tQuat32;
  ptDesta = tQuat32_4 * tQuat32 + tQuat32_4 * tQuat32;
  vXZ = v5 * tQuat32 + v5 * tQuat32;
  vXW = tQuat32 * v6 + tQuat32 * v6;
  vYY = tQuat32_4 * tQuat32_4 + tQuat32_4 * tQuat32_4;
  vYZ = v5 * tQuat32_4 + v5 * tQuat32_4;
  vYW = tQuat32_4 * v6 + tQuat32_4 * v6;
  vZZ = v5 * v5 + v5 * v5;
  v7 = v6 * v5 + v6 * v5;
  ptDest->tX.vX = 1.0 - vYY - vZZ;
  ptDest->tX.vY = ptDesta - v7;
  ptDest->tX.vZ = vYW + vXZ;
  ptDest->tY.vX = v7 + ptDesta;
  v8 = 1.0 - vXX;
  ptDest->tY.vY = v8 - vZZ;
  ptDest->tY.vZ = vYZ - vXW;
  ptDest->nOps = 0;
  ptDest->tZ.vX = vXZ - vYW;
  ptDest->tZ.vY = vYZ + vXW;
  ptDest->tZ.vZ = v8 - vYY;
  return ptDest;
}

// source: b/1/real.c:4417  [anchor-mhash]
void __cdecl Real32x9_FromReal32x3(struct real32x9_t *ptDest, struct real32x3_t *ptSource)
{
  #pragma pack(push, 1)
  union
  {
    struct { float tY; };
    struct { char igi2_o1[8]; float tY_8; };
    struct { char igi2_o2[12]; float v20; };
    struct { char igi2_o3[24]; struct real32x9_t Real32x9_Normalize_tTemp; };
    struct { char igi2_o4[64]; struct real32x9_t tMatrix; };
    char igi2_extent[104];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  long double v2; // st7
  long double v3; // st4
  long double v4; // st6
  long double v5; // st7
  long double v6; // rt1
  long double v7; // st6
  long double v8; // st7
  long double v9; // st6
  long double v10; // st7
  long double v11; // st7
  struct real32x3_t tZ; // 0:^8.12
  struct real32x3_t tTemp_; // 0:^14.12
  struct real32x3_t tYa; // 0:^20.12

  tZ = *ptSource;
  if ( ptSource->vX == 0.0 && tZ.vY == 0.0 )
  {
    v2 = 1.0;
    igi2_frame.tY = 0.0;
    igi2_frame.tY_8 = 0.0;
  }
  else
  {
    v2 = -tZ.vX;
    igi2_frame.tY = ptSource->vY;
    igi2_frame.tY_8 = 0.0;
    if ( tZ.vY != 0.0 || v2 != 0.0 )
    {
      v3 = sqrt(tZ.vY * tZ.vY + v2 * v2);
      igi2_frame.tY = tZ.vY * (1.0 / v3);
      v4 = v2;
      v5 = 1.0 / v3;
      v6 = v4 * v5;
      v7 = v5;
      v2 = v6;
      igi2_frame.tY_8 = v7 * 0.0;
    }
  }
  igi2_frame.tMatrix.tX.vY = igi2_frame.tY;
  igi2_frame.Real32x9_Normalize_tTemp.tX.vY = igi2_frame.tY;
  igi2_frame.tMatrix.tX.vZ = tZ.vX;
  igi2_frame.Real32x9_Normalize_tTemp.tX.vZ = tZ.vX;
  igi2_frame.v20 = tZ.vZ * v2 - igi2_frame.tY_8 * tZ.vY;
  igi2_frame.tMatrix.tX.vX = igi2_frame.v20;
  igi2_frame.Real32x9_Normalize_tTemp.tX.vX = igi2_frame.v20;
  v8 = igi2_frame.tY * tZ.vY - v2 * tZ.vX;
  if ( igi2_frame.v20 != 0.0 || igi2_frame.tY != 0.0 || tZ.vX != 0.0 )
  {
    v9 = 1.0 / sqrt(igi2_frame.v20 * igi2_frame.v20 + igi2_frame.tY * igi2_frame.tY + tZ.vX * tZ.vX);
    igi2_frame.Real32x9_Normalize_tTemp.tX.vX = igi2_frame.v20 * v9;
    igi2_frame.Real32x9_Normalize_tTemp.tX.vY = igi2_frame.Real32x9_Normalize_tTemp.tX.vY * v9;
    igi2_frame.Real32x9_Normalize_tTemp.tX.vZ = igi2_frame.Real32x9_Normalize_tTemp.tX.vZ * v9;
  }
  tTemp_.vX = igi2_frame.tY_8 * tZ.vX - tZ.vZ * igi2_frame.tY;
  tTemp_.vY = -(tZ.vX * v8 - igi2_frame.v20 * tZ.vZ);
  tTemp_.vZ = v8 * igi2_frame.tY - igi2_frame.v20 * igi2_frame.tY_8;
  igi2_frame.Real32x9_Normalize_tTemp.tY = tTemp_;
  tYa.vX = tTemp_.vZ * igi2_frame.Real32x9_Normalize_tTemp.tX.vY - tTemp_.vY * igi2_frame.Real32x9_Normalize_tTemp.tX.vZ;
  tYa.vY = -(tTemp_.vZ * igi2_frame.Real32x9_Normalize_tTemp.tX.vX - tTemp_.vX * igi2_frame.Real32x9_Normalize_tTemp.tX.vZ);
  tYa.vZ = tTemp_.vY * igi2_frame.Real32x9_Normalize_tTemp.tX.vX - tTemp_.vX * igi2_frame.Real32x9_Normalize_tTemp.tX.vY;
  igi2_frame.Real32x9_Normalize_tTemp.tZ = tYa;
  if ( tTemp_.vX != 0.0 || tTemp_.vY != 0.0 || tTemp_.vZ != 0.0 )
  {
    v10 = 1.0 / sqrt(tTemp_.vZ * tTemp_.vZ + tTemp_.vY * tTemp_.vY + tTemp_.vX * tTemp_.vX);
    igi2_frame.Real32x9_Normalize_tTemp.tY.vX = tTemp_.vX * v10;
    igi2_frame.Real32x9_Normalize_tTemp.tY.vY = igi2_frame.Real32x9_Normalize_tTemp.tY.vY * v10;
    igi2_frame.Real32x9_Normalize_tTemp.tY.vZ = igi2_frame.Real32x9_Normalize_tTemp.tY.vZ * v10;
  }
  if ( tYa.vX != 0.0 || tYa.vY != 0.0 || tYa.vZ != 0.0 )
  {
    v11 = 1.0 / sqrt(tYa.vX * tYa.vX + tYa.vY * tYa.vY + tYa.vZ * tYa.vZ);
    igi2_frame.Real32x9_Normalize_tTemp.tZ.vX = tYa.vX * v11;
    igi2_frame.Real32x9_Normalize_tTemp.tZ.vY = igi2_frame.Real32x9_Normalize_tTemp.tZ.vY * v11;
    igi2_frame.Real32x9_Normalize_tTemp.tZ.vZ = igi2_frame.Real32x9_Normalize_tTemp.tZ.vZ * v11;
  }
  qmemcpy(&igi2_frame.tMatrix, &igi2_frame.Real32x9_Normalize_tTemp, sizeof(igi2_frame.tMatrix));
  igi2_frame.tMatrix.nOps = 0;
  qmemcpy(ptDest, &igi2_frame.tMatrix, sizeof(struct real32x9_t));
}

// source: b/1/real.c:4474  [anchor-mhash]
struct real32x9_t *__cdecl Real32x9_InvertSafe(
        struct real32x9_t *ptDest,
        struct real32x9_t *ptSource)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v8; };
    struct { char igi2_o1[4]; float v9; };
    struct { char igi2_o2[8]; float v10; };
    struct { char igi2_o3[12]; float v11; };
    struct { char igi2_o4[16]; float v12; };
    struct { char igi2_o5[20]; struct real32x9_t tTemp; };
    char igi2_extent[64];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v2; // st7
  double v3; // st6
  double v4; // rt0
  double v5; // st6
  double v6; // st5
  struct real32x9_t *result; // eax

  v2 = ptSource->tY.vX * ptSource->tZ.vY;
  igi2_frame.v11 = ptSource->tZ.vX * ptSource->tY.vZ;
  igi2_frame.v8 = ptSource->tZ.vZ * ptSource->tY.vY;
  igi2_frame.v9 = ptSource->tY.vZ * ptSource->tZ.vY;
  igi2_frame.v10 = ptSource->tZ.vZ * ptSource->tY.vX;
  igi2_frame.v12 = ptSource->tZ.vX * ptSource->tY.vY;
  v3 = 1.0
     / (igi2_frame.v8 * ptSource->tX.vX
      + v2 * ptSource->tX.vZ
      + igi2_frame.v11 * ptSource->tX.vY
      - igi2_frame.v9 * ptSource->tX.vX
      - igi2_frame.v10 * ptSource->tX.vY
      - igi2_frame.v12 * ptSource->tX.vZ);
  igi2_frame.tTemp.tX.vX = (igi2_frame.v8 - igi2_frame.v9) * v3;
  igi2_frame.tTemp.tX.vY = -((igi2_frame.v10 - igi2_frame.v11) * v3);
  v4 = v3;
  igi2_frame.tTemp.tX.vZ = (v2 - igi2_frame.v12) * v3;
  igi2_frame.tTemp.tY.vX = -((ptSource->tZ.vZ * ptSource->tX.vY - ptSource->tX.vZ * ptSource->tZ.vY) * v3);
  igi2_frame.tTemp.tY.vY = (ptSource->tZ.vZ * ptSource->tX.vX - ptSource->tZ.vX * ptSource->tX.vZ) * v3;
  igi2_frame.tTemp.tY.vZ = -((ptSource->tX.vX * ptSource->tZ.vY - ptSource->tZ.vX * ptSource->tX.vY) * v3);
  igi2_frame.tTemp.tZ.vX = (ptSource->tY.vZ * ptSource->tX.vY - ptSource->tX.vZ * ptSource->tY.vY) * v3;
  igi2_frame.tTemp.tZ.vY = -((ptSource->tY.vZ * ptSource->tX.vX - ptSource->tY.vX * ptSource->tX.vZ) * v3);
  v5 = ptSource->tY.vY * ptSource->tX.vX;
  v6 = ptSource->tY.vX * ptSource->tX.vY;
  result = (struct real32x9_t *)(ptSource->nOps + 1);
  igi2_frame.tTemp.nOps = (int)result;
  igi2_frame.tTemp.tZ.vZ = (v5 - v6) * v4;
  qmemcpy(ptDest, &igi2_frame.tTemp, sizeof(struct real32x9_t));
  return result;
}

// source: b/1/real.c:4918  [anchor-mhash]
void __cdecl Quat32_SLERP(
        struct Quat32_t *ptDest,
        struct Quat32_t *ptSource0,
        struct Quat32_t *ptSource1,
        float vTime)
{
  double v4; // st7
  double v5; // st7
  double v6; // st7
  long double v7; // st7
  long double v8; // st6
  long double v9; // rt0
  long double v10; // st5
  float vDot; // [esp+0h] [ebp-4h]

  v4 = ptSource0->vX * ptSource1->vX
     + ptSource0->vZ * ptSource1->vZ
     + ptSource0->vY * ptSource1->vY
     + ptSource1->vW * ptSource0->vW;
  vDot = v4;
  if ( v4 <= 0.9999899864196777 )
  {
    if ( vDot >= -0.9999899864196777 )
    {
      if ( vDot >= 0.0 )
      {
        v7 = sqrt(1.0 - vDot) * (((vDot * -0.018729299306869507 + 0.07426100224256516) * vDot - 0.2121143937110901) * vDot + 1.5707287788391113);
        v8 = sin((1.0 - vTime) * v7);
      }
      else
      {
        v7 = sqrt(1.0 - -vDot) * (((-vDot * -0.018729299306869507 + 0.07426100224256516) * -vDot - 0.2121143937110901) * -vDot + 1.5707287788391113);
        v8 = -sin((1.0 - vTime) * v7);
      }
      v9 = sin(v7 * vTime);
      v10 = 1.0 / sin(v7);
      ptDest->vX = (v8 * ptSource0->vX + v9 * ptSource1->vX) * v10;
      ptDest->vY = (v8 * ptSource0->vY + v9 * ptSource1->vY) * v10;
      ptDest->vZ = (v8 * ptSource0->vZ + v9 * ptSource1->vZ) * v10;
      ptDest->vW = (v9 * ptSource1->vW + v8 * ptSource0->vW) * v10;
    }
    else
    {
      v6 = 1.0 - vTime;
      ptDest->vX = v6 * ptSource0->vX - vTime * ptSource1->vX;
      ptDest->vY = v6 * ptSource0->vY - vTime * ptSource1->vY;
      ptDest->vZ = v6 * ptSource0->vZ - vTime * ptSource1->vZ;
      ptDest->vW = v6 * ptSource0->vW - vTime * ptSource1->vW;
    }
  }
  else
  {
    v5 = 1.0 - vTime;
    ptDest->vX = vTime * ptSource1->vX + v5 * ptSource0->vX;
    ptDest->vY = v5 * ptSource0->vY + vTime * ptSource1->vY;
    ptDest->vZ = v5 * ptSource0->vZ + vTime * ptSource1->vZ;
    ptDest->vW = v5 * ptSource0->vW + vTime * ptSource1->vW;
  }
}

// source: b/1/real.c:5009  [anchor-mhash]
float __cdecl Quat32_DotProduct(struct Quat32_t *ptSource0, struct Quat32_t *ptSource1)
{
  return ptSource0->vW * ptSource1->vW
       + ptSource0->vZ * ptSource1->vZ
       + ptSource0->vY * ptSource1->vY
       + ptSource0->vX * ptSource1->vX;
}

// source: b/1/real.c:5030  [anchor-mhash]
char __cdecl Quat32_Equal(struct Quat32_t *ptSource0, struct Quat32_t *ptSource1)
{
  return ptSource0->vX == ptSource1->vX
      && ptSource0->vY == ptSource1->vY
      && ptSource0->vZ == ptSource1->vZ
      && ptSource0->vW == ptSource1->vW;
}

// source: b/1/real.c:5051  [anchor-mhash]
void __cdecl Quat32_Rotate(
        struct Quat32_t *ptDest,
        struct Quat32_t *ptSource,
        float vAlpha,
        float vBeta,
        float vGamma)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v_J; };
    struct { char igi2_o1[4]; float v17; };
    struct { char igi2_o2[8]; float v18; };
    struct { char igi2_o3[12]; float v_F; };
    struct { char igi2_o4[16]; struct Quat32_t tTemp; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v5; // st7
  double v6; // st6
  double v7; // st5
  double v8; // st4
  double v9; // st3
  double v10; // st2
  int nOps; // eax
  double v12; // st7
  int v13; // eax
  double vX; // st6
  long double v15; // st6

  Quat32_Create(&igi2_frame.tTemp, vAlpha, vBeta, vGamma);
  v5 = (ptSource->vY - ptSource->vZ) * (igi2_frame.tTemp.vZ - igi2_frame.tTemp.vY);
  v6 = (ptSource->vZ + ptSource->vY) * (igi2_frame.tTemp.vW - igi2_frame.tTemp.vX);
  v7 = (igi2_frame.tTemp.vY + igi2_frame.tTemp.vZ) * (ptSource->vW - ptSource->vX);
  igi2_frame.v_F = (ptSource->vX + ptSource->vY) * (igi2_frame.tTemp.vX + igi2_frame.tTemp.vZ);
  v8 = (ptSource->vW - ptSource->vZ) * (igi2_frame.tTemp.vW + igi2_frame.tTemp.vY);
  v9 = (ptSource->vZ + ptSource->vW) * (igi2_frame.tTemp.vW - igi2_frame.tTemp.vY);
  v10 = v9 + v8 + igi2_frame.v_F;
  igi2_frame.v_J = ((ptSource->vX - ptSource->vY) * (igi2_frame.tTemp.vZ - igi2_frame.tTemp.vX) + v10) * 0.5;
  ptDest->vX = (ptSource->vX + ptSource->vW) * (igi2_frame.tTemp.vX + igi2_frame.tTemp.vW) + igi2_frame.v_J - v10;
  nOps = igi2_frame.tTemp.nOps;
  igi2_frame.v17 = igi2_frame.v_J + v6 - v9;
  ptDest->vY = igi2_frame.v17;
  igi2_frame.v18 = igi2_frame.v_J + v7 - v8;
  ptDest->vZ = igi2_frame.v18;
  v12 = v5 + igi2_frame.v_J - igi2_frame.v_F;
  ptDest->vW = v12;
  v13 = ptSource->nOps + nOps + 1;
  ptDest->nOps = v13;
  if ( v13 > 1000 )
  {
    vX = ptDest->vX;
    ptDest->nOps = 0;
    v15 = 1.0 / sqrt(vX * vX + v12 * v12 + igi2_frame.v18 * igi2_frame.v18 + igi2_frame.v17 * igi2_frame.v17);
    ptDest->vX = ptDest->vX * v15;
    ptDest->vY = igi2_frame.v17 * v15;
    ptDest->vZ = igi2_frame.v18 * v15;
    ptDest->vW = v12 * v15;
  }
}

// source: b/1/real.c:5075  [anchor-mhash]
struct Quat32_t *__cdecl Quat32_RotateAlpha(
        struct Quat32_t *ptDest,
        struct Quat32_t *ptSource,
        float vAngle)
{
  long double v3; // st7
  long double v4; // rt0
  long double v5; // st6
  long double v6; // st5
  long double v7; // st5
  double v8; // st7
  double v9; // st6
  struct Quat32_t *result; // eax
  double vX; // st5
  long double v12; // st5
  float v_Ha; // [esp+0h] [ebp-18h]
  float v_H; // [esp+0h] [ebp-18h]
  float v_G; // [esp+4h] [ebp-14h]
  float v_F; // [esp+8h] [ebp-10h]
  float v_C; // [esp+Ch] [ebp-Ch]
  float v_D; // [esp+10h] [ebp-8h]
  float v_A; // [esp+14h] [ebp-4h]
  float ptDesta = *(float *)&vAngle; // [esp+1Ch] [ebp+4h] ARGSLOT

  v3 = vAngle * 0.5;
  v4 = sin(v3);
  v5 = cos(v3);
  v_A = (ptSource->vY - ptSource->vZ) * 0.0;
  v_C = (ptSource->vZ + ptSource->vY) * (v5 - v4);
  v_D = (ptSource->vW - ptSource->vX) * 0.0;
  v_F = (ptSource->vY + ptSource->vX) * v4;
  v_G = (ptSource->vW - ptSource->vZ) * v5;
  v6 = (ptSource->vZ + ptSource->vW) * v5;
  v_Ha = v6;
  v7 = v6 + v_G + v_F;
  ptDesta = ((ptSource->vX - ptSource->vY) * -v4 + v7) * 0.5;
  ptDest->vX = (v4 + v5) * (ptSource->vW + ptSource->vX) + ptDesta - v7;
  v8 = ptDesta + v_C - v_Ha;
  ptDest->vY = v8;
  v_H = ptDesta + v_D - v_G;
  ptDest->vZ = v_H;
  v9 = ptDesta + v_A - v_F;
  ptDest->vW = v9;
  result = (struct Quat32_t *)(ptSource->nOps + 1);
  ptDest->nOps = (int)result;
  if ( (int)result > 1000 )
  {
    vX = ptDest->vX;
    ptDest->nOps = 0;
    v12 = 1.0 / sqrt(vX * vX + v9 * v9 + v_H * v_H + v8 * v8);
    ptDest->vX = ptDest->vX * v12;
    ptDest->vY = v8 * v12;
    ptDest->vZ = v_H * v12;
    ptDest->vW = v9 * v12;
  }
  return result;
}

// source: b/1/real.c:5097  [anchor-mhash]
struct Quat32_t *__cdecl Quat32_RotateBeta(
        struct Quat32_t *ptDest,
        struct Quat32_t *ptSource,
        float vAngle)
{
  long double v3; // st7
  long double v4; // rt0
  long double v5; // st7
  long double v6; // st6
  long double v7; // st7
  double v8; // st6
  struct Quat32_t *result; // eax
  double vX; // st5
  long double v11; // st5
  float v_Ga; // [esp+0h] [ebp-28h]
  float v_G; // [esp+0h] [ebp-28h]
  float v_F; // [esp+4h] [ebp-24h]
  float v_C; // [esp+8h] [ebp-20h]
  float v_D; // [esp+Ch] [ebp-1Ch]
  float v_A; // [esp+10h] [ebp-18h]
  float tTemp_12; // [esp+20h] [ebp-8h]
  float ptDesta = *(float *)&vAngle; // [esp+2Ch] [ebp+4h] ARGSLOT

  v3 = vAngle * 0.5;
  v4 = sin(v3);
  tTemp_12 = cos(v3);
  v_A = (ptSource->vY - ptSource->vZ) * -v4;
  v_C = (ptSource->vZ + ptSource->vY) * tTemp_12;
  v_D = (ptSource->vW - ptSource->vX) * v4;
  v_F = (ptSource->vY + ptSource->vX) * 0.0;
  v_Ga = (tTemp_12 + v4) * (ptSource->vW - ptSource->vZ);
  v5 = (ptSource->vZ + ptSource->vW) * (tTemp_12 - v4);
  v6 = v_Ga + v5 + v_F;
  ptDesta = ((ptSource->vX - ptSource->vY) * 0.0 + v6) * 0.5;
  ptDest->vX = (ptSource->vW + ptSource->vX) * tTemp_12 + ptDesta - v6;
  v7 = ptDesta + v_C - v5;
  ptDest->vY = v7;
  v_G = ptDesta + v_D - v_Ga;
  ptDest->vZ = v_G;
  v8 = ptDesta + v_A - v_F;
  ptDest->vW = v8;
  result = (struct Quat32_t *)(ptSource->nOps + 1);
  ptDest->nOps = (int)result;
  if ( (int)result > 1000 )
  {
    vX = ptDest->vX;
    ptDest->nOps = 0;
    v11 = 1.0 / sqrt(vX * vX + v8 * v8 + v_G * v_G + v7 * v7);
    ptDest->vX = ptDest->vX * v11;
    ptDest->vY = v7 * v11;
    ptDest->vZ = v_G * v11;
    ptDest->vW = v8 * v11;
  }
  return result;
}

// source: b/1/real.c:5119  [anchor-mhash]
struct Quat32_t *__cdecl Quat32_RotateGamma(
        struct Quat32_t *ptDest,
        struct Quat32_t *ptSource,
        float vAngle)
{
  long double v3; // st7
  long double v4; // st7
  long double v5; // st6
  long double v6; // st7
  long double v7; // st6
  double v8; // st5
  long double v9; // st4
  long double v10; // st7
  double v11; // st6
  struct Quat32_t *result; // eax
  double vX; // st5
  long double v14; // st5
  float v15; // [esp+0h] [ebp-14h]
  float v16; // [esp+0h] [ebp-14h]
  float v_F; // [esp+4h] [ebp-10h]
  float v_C; // [esp+8h] [ebp-Ch]
  float v_D; // [esp+Ch] [ebp-8h]
  float v_A; // [esp+10h] [ebp-4h]
  float ptDesta = *(float *)&vAngle; // [esp+18h] [ebp+4h] ARGSLOT
  float ptDestb = *(float *)&vAngle; // [esp+18h] [ebp+4h] ARGSLOT
  float ptDestc = *(float *)&vAngle; // [esp+18h] [ebp+4h] ARGSLOT

  v3 = vAngle * 0.5;
  ptDesta = v3;
  v4 = sin(v3);
  v5 = cos(ptDesta);
  v15 = v4;
  v_A = (ptSource->vY - ptSource->vZ) * v15;
  ptDestb = v5;
  v_C = (ptSource->vZ + ptSource->vY) * ptDestb;
  v_D = (ptSource->vW - ptSource->vX) * v4;
  v_F = (ptSource->vY + ptSource->vX) * v4;
  v6 = v5;
  v7 = (ptSource->vW - ptSource->vZ) * v5;
  v8 = (ptSource->vZ + ptSource->vW) * ptDestb;
  v9 = v8 + v7 + v_F;
  ptDestc = ((ptSource->vX - ptSource->vY) * v15 + v9) * 0.5;
  ptDest->vX = (ptSource->vW + ptSource->vX) * v6 + ptDestc - v9;
  v16 = ptDestc + v_C - v8;
  ptDest->vY = v16;
  v10 = ptDestc + v_D - v7;
  ptDest->vZ = v10;
  v11 = ptDestc + v_A - v_F;
  ptDest->vW = v11;
  result = (struct Quat32_t *)(ptSource->nOps + 1);
  ptDest->nOps = (int)result;
  if ( (int)result > 1000 )
  {
    vX = ptDest->vX;
    ptDest->nOps = 0;
    v14 = 1.0 / sqrt(vX * vX + v11 * v11 + v10 * v10 + v16 * v16);
    ptDest->vX = ptDest->vX * v14;
    ptDest->vY = v16 * v14;
    ptDest->vZ = v10 * v14;
    ptDest->vW = v11 * v14;
  }
  return result;
}

// source: b/1/real.c:5141  [anchor-mhash]
struct Quat32_t *__cdecl Quat32_Create(
        struct Quat32_t *ptDest,
        float vAlpha,
        float vBeta,
        float vGamma)
{
  long double v4; // st7
  long double v5; // rt0
  long double v6; // st6
  long double v7; // st5
  long double v8; // st5
  long double v9; // st4
  long double v10; // st7
  float vSinBeta; // [esp+0h] [ebp-Ch]
  float vSinAlphaCosBeta; // [esp+4h] [ebp-8h]
  float vCosAlphaCosBeta; // [esp+8h] [ebp-4h]
  float ptDesta = *(float *)&vAlpha; // [esp+10h] [ebp+4h] ARGSLOT
  float vAlphaa = *(float *)&vBeta; // [esp+14h] [ebp+8h] ARGSLOT
  float vBetaa = *(float *)&vGamma; // [esp+18h] [ebp+Ch] ARGSLOT

  ptDest->nOps = 0;
  v4 = vAlpha * 0.5;
  v5 = sin(v4);
  v6 = cos(v4);
  v7 = vBeta * 0.5;
  vSinBeta = sin(v7);
  v8 = cos(v7);
  v9 = vGamma * 0.5;
  vAlphaa = sin(v9);
  ptDesta = cos(v9);
  vSinAlphaCosBeta = v8 * v5;
  vBetaa = vSinBeta * v6;
  vCosAlphaCosBeta = v8 * v6;
  v10 = v5 * vSinBeta;
  ptDest->vX = vSinAlphaCosBeta * ptDesta - vBetaa * vAlphaa;
  ptDest->vY = vBetaa * ptDesta + vSinAlphaCosBeta * vAlphaa;
  ptDest->vZ = vCosAlphaCosBeta * vAlphaa - v10 * ptDesta;
  ptDest->vW = vCosAlphaCosBeta * ptDesta + v10 * vAlphaa;
  return ptDest;
}

// source: b/1/real.c:5189  [size]
struct Quat32_t *__cdecl Quat32_CreateAlpha(struct Quat32_t *ptDest, float vAlpha)
{
  long double v2; // st7

  v2 = vAlpha * 0.5;
  ptDest->vY = 0.0;
  ptDest->vZ = 0.0;
  ptDest->nOps = 0;
  ptDest->vX = sin(v2);
  ptDest->vW = cos(v2);
  return ptDest;
}

// source: b/1/real.c:5218  [size]
struct Quat32_t *__cdecl Quat32_CreateBeta(struct Quat32_t *ptDest, float vBeta)
{
  long double v2; // st7

  v2 = vBeta * 0.5;
  ptDest->vX = 0.0;
  ptDest->vZ = 0.0;
  ptDest->nOps = 0;
  ptDest->vY = sin(v2);
  ptDest->vW = cos(v2);
  return ptDest;
}

// source: b/1/real.c:5247  [size]
struct Quat32_t *__cdecl Quat32_CreateGamma(struct Quat32_t *ptDest, float vGamma)
{
  long double v2; // st7

  v2 = vGamma * 0.5;
  ptDest->vX = 0.0;
  ptDest->vY = 0.0;
  ptDest->nOps = 0;
  ptDest->vZ = sin(v2);
  ptDest->vW = cos(v2);
  return ptDest;
}

// source: b/1/real.c:5280  [anchor-mhash]
struct Quat32_t *__cdecl Quat32_CreateRotationAroundAxis(
        struct Quat32_t *ptDest,
        struct real32x3_t *ptUnitAxis,
        float vRadians)
{
  long double v3; // st7
  long double v4; // st6
  long double v5; // st6

  v3 = vRadians * 0.5;
  v4 = sin(v3);
  ptDest->vX = v4 * ptUnitAxis->vX;
  ptDest->vY = v4 * ptUnitAxis->vY;
  v5 = v4 * ptUnitAxis->vZ;
  ptDest->nOps = 0;
  ptDest->vZ = v5;
  ptDest->vW = cos(v3);
  return ptDest;
}

// source: b/1/real.c:5308  [anchor-mhash]
void __cdecl Real_Open()
{
  int v0; // eax
  double v1; // st7
  long double v2; // st7
  int v3; // ecx
  float *v4; // eax
  int v5; // esi
  double v6; // st7
  int v7; // edx
  int v8; // esi
  double v9; // st7
  int iCount; // [esp+8h] [ebp-8h]
  int iCounta; // [esp+8h] [ebp-8h]
  double iCountb; // [esp+8h] [ebp-8h]

  v0 = 0;
  iCount = 0;
  do
  {
    v1 = (double)iCount;
    iCount = ++v0;
    v2 = v1 * 0.0015339808305725455;
    flt_84EE0B8[2 * v0] = sin(v2);
    flt_84DE098[2 * v0] = cos(v2);
  }
  while ( v0 < 4096 );
  v3 = 2;
  v4 = nullptr;
  v5 = 512;
  do
  {
    v4 += 16;
    v4[34846753] = Real32_avSin[((_WORD)v3 - 1) & 0xFFF].vX - v4[34846752];
    v4[34830361] = Real32_avCos[((_WORD)v3 - 1) & 0xFFF].vX - v4[34830360];
    v4[34846755] = Real32_avSin[v3 & 0xFFF].vX - v4[34846754];
    v4[34830363] = Real32_avCos[v3 & 0xFFF].vX - v4[34830362];
    v4[34846757] = Real32_avSin[((_WORD)v3 + 1) & 0xFFF].vX - v4[34846756];
    v4[34830365] = Real32_avCos[((_WORD)v3 + 1) & 0xFFF].vX - v4[34830364];
    v4[34846759] = Real32_avSin[((_WORD)v3 + 2) & 0xFFF].vX - v4[34846758];
    v4[34830367] = Real32_avCos[((_WORD)v3 + 2) & 0xFFF].vX - v4[34830366];
    v4[34846761] = Real32_avSin[((_WORD)v3 + 3) & 0xFFF].vX - v4[34846760];
    v4[34830369] = Real32_avCos[((_WORD)v3 + 3) & 0xFFF].vX - v4[34830368];
    v4[34846763] = Real32_avSin[((_WORD)v3 + 4) & 0xFFF].vX - v4[34846762];
    v4[34830371] = Real32_avCos[((_WORD)v3 + 4) & 0xFFF].vX - v4[34830370];
    v4[34846765] = Real32_avSin[((_WORD)v3 + 5) & 0xFFF].vX - v4[34846764];
    v6 = Real32_avCos[((_WORD)v3 + 5) & 0xFFF].vX - v4[34830372];
    v7 = 8 * (((_WORD)v3 + 6) & 0xFFF);
    v3 += 8;
    --v5;
    v4[34830373] = v6;
    v4[34846767] = *(float *)(v7 + 139387072) - v4[34846766];
    v4[34830375] = *(float *)(v7 + 139321504) - v4[34830374];
  }
  while ( v5 );
  v8 = 0;
  iCounta = 0;
  do
  {
    v9 = (double)iCounta * 0.000244140625 - 1.0;
    iCountb = v9;
    if ( v9 >= -1.0 )
    {
      if ( v9 <= 1.0 )
        goto LABEL_11;
      HIDWORD(iCountb) = 1072693248;
    }
    else
    {
      HIDWORD(iCountb) = -1074790400;
    }
    LODWORD(iCountb) = 0;
LABEL_11:
    Real32_avASin[v8++] = asin(iCountb);
    iCounta = v8;
  }
  while ( v8 < 8193 );
}

// source: b/1/real.c:5347  [size]
void __cdecl Real_Close()
{
  ;
}
