/* j/0/network/spline.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/network/spline.c:40  [anchor-mhash]
double __cdecl Spline_CubicValue(double t, double *aPoly)
{
  return ((t * aPoly[3] + aPoly[2]) * t + aPoly[1]) * t + *aPoly;
}

// source: j/0/network/spline.c:55  [anchor-mhash]
double __cdecl Spline_CubicDValue(double t, double *aPoly)
{
  return (t * aPoly[3] * 3.0 + aPoly[2] + aPoly[2]) * t + aPoly[1];
}

// source: j/0/network/spline.c:69  [size]
struct Spline_s *__cdecl Spline_Disable(struct Spline_s *ptSpline)
{
  ptSpline->a = -1;
  return ptSpline;
}

// source: j/0/network/spline.c:82  [size]
enum bool __cdecl Spline_IsEnabled(struct Spline_s *ptSpline)
{
  return ptSpline->a > 0;
}

// source: j/0/network/spline.c:96  [anchor-callee]
// local variable allocation has failed, the output may be wrong!
double *__cdecl Spline_CreateCubicPolygon(
        double x0,
        double v0,
        double x1,
        double v1,
        int a,
        double *aPoly)
{
  double v6; // st7

  *(_DWORD *)aPoly = HIDWORD(x0);
  v6 = 1.0 / (double)SLODWORD(x0);
  *((_DWORD *)aPoly + 1) = LODWORD(v0);
  *((_QWORD *)aPoly + 1) = __PAIR64__(LODWORD(x1), HIDWORD(v0));
  aPoly[2] = v6 * v6 * *(double *)((char *)&v1 - 4) * 3.0
           - (v6 * v6 * *(double *)((char *)&x0 + 4) * 3.0
            + v6 * *(double *)((char *)&v0 + 4)
            + v6 * *(double *)((char *)&v0 + 4))
           - v6 * *(double *)((char *)&v1 + 4);
  aPoly[3] = *(double *)((char *)&x0 + 4) * (v6 * v6 * v6)
           + *(double *)((char *)&x0 + 4) * (v6 * v6 * v6)
           + v6 * v6 * *(double *)((char *)&v0 + 4)
           - (v6 * v6 * v6 * *(double *)((char *)&v1 - 4)
            + v6 * v6 * v6 * *(double *)((char *)&v1 - 4))
           + v6 * v6 * *(double *)((char *)&v1 + 4);
  return aPoly;
}

// source: j/0/network/spline.c:122  [anchor-mhash]
struct Spline_s *__cdecl Spline_Pos(
        struct Spline_s *ptSpline,
        struct real64x3_t *ptPos,
        int t)
{
  double v3; // st7

  v3 = (double)t;
  ptPos->vX = ((v3 * ptSpline->x[3] + ptSpline->x[2]) * v3 + ptSpline->x[1]) * v3 + ptSpline->x[0];
  ptPos->vY = ((v3 * ptSpline->y[3] + ptSpline->y[2]) * v3 + ptSpline->y[1]) * v3 + ptSpline->y[0];
  ptPos->vZ = ((v3 * ptSpline->z[3] + ptSpline->z[2]) * v3 + ptSpline->z[1]) * v3 + ptSpline->z[0];
  return ptSpline;
}

// source: j/0/network/spline.c:138  [anchor-callee]
void __cdecl Spline_Speed(struct Spline_s *ptSpline, struct real64x3_t *ptSpeed, int t)
{
  double v3; // st7
  double v4; // st7
  int vX_high; // eax
  double v6; // [esp+0h] [ebp-18h]
  double vY; // [esp+8h] [ebp-10h]

  v3 = (double)t;
  ptSpeed->vX = (v3 * ptSpline->x[3] * 3.0 + ptSpline->x[2] + ptSpline->x[2]) * v3 + ptSpline->x[1];
  LODWORD(v6) = LODWORD(ptSpeed->vX);
  ptSpeed->vY = (v3 * ptSpline->y[3] * 3.0 + ptSpline->y[2] + ptSpline->y[2]) * v3 + ptSpline->y[1];
  vY = ptSpeed->vY;
  v4 = v3 * (v3 * ptSpline->z[3] * 3.0 + ptSpline->z[2] + ptSpline->z[2]) + ptSpline->z[1];
  vX_high = HIDWORD(ptSpeed->vX);
  ptSpeed->vZ = v4;
  HIDWORD(v6) = vX_high;
  if ( pow(1.0, -8.0) > sqrt(v4 * v4 + v6 * v6 + vY * vY) )
  {
    ptSpeed->vX = 0.0;
    ptSpeed->vY = 0.0;
    ptSpeed->vZ = 0.0;
  }
}

// source: j/0/network/spline.c:185  [anchor-strings]
int __cdecl Spline_Initialize(
        struct Spline_s *ptSpline,
        struct real64x3_t *ptOldPos,
        struct real64x3_t *ptNewPos,
        struct real64x3_t *ptOldSpeed,
        struct real64x3_t *ptNewSpeed,
        int t0,
        int a)
{
  #pragma pack(push, 1)
  union
  {
    struct { _BYTE v10[32]; };
    struct { _BYTE v11[32]; };
    struct { _BYTE v12[32]; };
    struct { char igi2_o3[48]; char zTemp[256]; };
    char igi2_extent[304];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v7; // esi

  v7 = a;
  if ( a <= 0 )
  {
    _snprintf(igi2_frame.zTemp, 0xFFu, "Spline_Initialize: Emergency fix. a was %d. Set to 1.\n", a);
    NetManager_LogMessage(igi2_frame.zTemp);
    v7 = 1;
  }
  if ( t0 < 0 )
  {
    _snprintf(igi2_frame.zTemp, 0xFFu, "Spline_Initialize: Emergency fix. t0 was %d. Set to 1\n", t0);
    NetManager_LogMessage(igi2_frame.zTemp);
    t0 = 1;
  }
  *(_DWORD *)&igi2_frame.v10[28] = LODWORD(ptNewSpeed->vX);
  *(double *)&igi2_frame.v10[20] = ptNewPos->vX;
  *(double *)&igi2_frame.v10[12] = ptOldSpeed->vX;
  *(double *)&igi2_frame.v10[4] = ptOldPos->vX;
  *(_DWORD *)igi2_frame.v10 = v7;
  Spline_CreateCubicPolygon(
    *(double *)igi2_frame.v10,
    *(double *)&igi2_frame.v10[8],
    *(double *)&igi2_frame.v10[16],
    *(double *)&igi2_frame.v10[24],
    HIDWORD(ptNewSpeed->vX),
    ptSpline->x);
  *(_DWORD *)&igi2_frame.v11[28] = LODWORD(ptNewSpeed->vY);
  *(double *)&igi2_frame.v11[20] = ptNewPos->vY;
  *(double *)&igi2_frame.v11[12] = ptOldSpeed->vY;
  *(double *)&igi2_frame.v11[4] = ptOldPos->vY;
  *(_DWORD *)igi2_frame.v11 = v7;
  Spline_CreateCubicPolygon(
    *(double *)igi2_frame.v11,
    *(double *)&igi2_frame.v11[8],
    *(double *)&igi2_frame.v11[16],
    *(double *)&igi2_frame.v11[24],
    HIDWORD(ptNewSpeed->vY),
    ptSpline->y);
  *(_DWORD *)&igi2_frame.v12[28] = LODWORD(ptNewSpeed->vZ);
  *(double *)&igi2_frame.v12[20] = ptNewPos->vZ;
  *(double *)&igi2_frame.v12[12] = ptOldSpeed->vZ;
  *(double *)&igi2_frame.v12[4] = ptOldPos->vZ;
  *(_DWORD *)igi2_frame.v12 = v7;
  Spline_CreateCubicPolygon(
    *(double *)igi2_frame.v12,
    *(double *)&igi2_frame.v12[8],
    *(double *)&igi2_frame.v12[16],
    *(double *)&igi2_frame.v12[24],
    HIDWORD(ptNewSpeed->vZ),
    ptSpline->z);
  ptSpline->a = v7;
  ptSpline->t0 = t0;
  return t0;
}

// source: j/0/network/spline.c:229  [anchor-callee]
enum SplineRead_e __cdecl Spline_Extend(
        struct Spline_s *ptSpline,
        enum SplineRead_e eRead,
        struct real64x3_t *ptNewPos,
        struct real64x3_t *ptNewSpeed,
        int t0,
        int a)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v9; };
    struct { char igi2_o1[12]; struct real64x3_t tCurrentPos; };
    struct { char igi2_o2[36]; struct real64x3_t tCurrentSpeed; };
    char igi2_extent[60];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  __int32 v6; // eax
  int v7; // eax

  if ( eRead )
  {
    v6 = eRead - 1;
    if ( v6 )
    {
      if ( v6 != 1 )
      {
        LDebug_Error("Unknow spline read type used");
        abort();
      }
      goto LABEL_5;
    }
    igi2_frame.v9 = t0;
LABEL_7:
    Spline_ExtraFromEnd(&igi2_frame.tCurrentPos, &igi2_frame.tCurrentSpeed, ptSpline, igi2_frame.v9);
    return Spline_Initialize(ptSpline, &igi2_frame.tCurrentPos, ptNewPos, &igi2_frame.tCurrentSpeed, ptNewSpeed, t0, a);
  }
  v7 = ptSpline->t0;
  if ( t0 >= v7 )
  {
    igi2_frame.v9 = t0;
    if ( t0 <= ptSpline->a + v7 )
    {
      Spline_OnSpline(&igi2_frame.tCurrentPos, &igi2_frame.tCurrentSpeed, ptSpline, t0);
      return Spline_Initialize(ptSpline, &igi2_frame.tCurrentPos, ptNewPos, &igi2_frame.tCurrentSpeed, ptNewSpeed, t0, a);
    }
    goto LABEL_7;
  }
LABEL_5:
  Spline_ExtraFromStart(&igi2_frame.tCurrentPos, &igi2_frame.tCurrentSpeed, ptSpline, t0);
  return Spline_Initialize(ptSpline, &igi2_frame.tCurrentPos, ptNewPos, &igi2_frame.tCurrentSpeed, ptNewSpeed, t0, a);
}

// source: j/0/network/spline.c:258  [anchor-caller]
int __cdecl Spline_SetPoint(
        struct Spline_s *ptSpline,
        enum SplineRead_e eRead,
        struct real64x3_t *ptNewPos,
        struct real64x3_t *ptNewSpeed,
        int t0,
        int a)
{
  if ( ptSpline->a <= 0 )
    return Spline_Initialize(ptSpline, ptNewPos, ptNewPos, ptNewSpeed, ptNewSpeed, t0, a);
  else
    return Spline_Extend(ptSpline, eRead, ptNewPos, ptNewSpeed, t0, a);
}

// source: j/0/network/spline.c:283  [anchor-callee]
struct Spline_s *__cdecl Spline_ExtraFromStart(
        struct real64x3_t *ptPos,
        struct real64x3_t *ptSpeed,
        struct Spline_s *ptSpline,
        int t)
{
  int v6; // ebp
  double v8; // st7
  struct real64x3_t tTemp; // [esp+10h] [ebp-18h] BYREF
  struct real64x3_t *ptPosa = *(struct real64x3_t * *)&t; // [esp+2Ch] [ebp+4h] ARGSLOT

  ptPosa = (struct real64x3_t *)ptSpline->a;
  v6 = t - ptSpline->t0;
  ptPos->vX = ((ptSpline->x[3] * 0.0 + ptSpline->x[2]) * 0.0 + ptSpline->x[1]) * 0.0 + ptSpline->x[0];
  ptPos->vY = ((ptSpline->y[3] * 0.0 + ptSpline->y[2]) * 0.0 + ptSpline->y[1]) * 0.0 + ptSpline->y[0];
  ptPos->vZ = ((ptSpline->z[3] * 0.0 + ptSpline->z[2]) * 0.0 + ptSpline->z[1]) * 0.0 + ptSpline->z[0];
  Spline_Speed(ptSpline, ptSpeed, 0);
  v8 = (double)(v6 - (int)ptPosa);
  qmemcpy(&tTemp, ptSpeed, sizeof(tTemp));
  tTemp.vY = v8 * tTemp.vY;
  tTemp.vZ = v8 * tTemp.vZ;
  ptPos->vX = tTemp.vX * v8 + ptPos->vX;
  ptPos->vY = tTemp.vY + ptPos->vY;
  ptPos->vZ = tTemp.vZ + ptPos->vZ;
  return (struct Spline_s *)ptPosa;
}

// source: j/0/network/spline.c:311  [anchor-callee]
struct Spline_s *__cdecl Spline_ExtraFromEnd(
        struct real64x3_t *ptPos,
        struct real64x3_t *ptSpeed,
        struct Spline_s *ptSpline,
        int t)
{
  int a; // ecx
  int v6; // ebp
  double v7; // st7
  double v9; // st7
  struct real64x3_t tTemp; // [esp+10h] [ebp-18h] BYREF
  struct real64x3_t *ptPosa = *(struct real64x3_t * *)&t; // [esp+2Ch] [ebp+4h] ARGSLOT

  a = ptSpline->a;
  v6 = t - ptSpline->t0;
  ptPosa = (struct real64x3_t *)a;
  if ( v6 > 5 * a )
    v6 = 5 * a;
  v7 = (double)a;
  ptPos->vX = ((v7 * ptSpline->x[3] + ptSpline->x[2]) * v7 + ptSpline->x[1]) * v7 + ptSpline->x[0];
  ptPos->vY = ((v7 * ptSpline->y[3] + ptSpline->y[2]) * v7 + ptSpline->y[1]) * v7 + ptSpline->y[0];
  ptPos->vZ = ((v7 * ptSpline->z[3] + ptSpline->z[2]) * v7 + ptSpline->z[1]) * v7 + ptSpline->z[0];
  Spline_Speed(ptSpline, ptSpeed, a);
  v9 = (double)(v6 - (int)ptPosa);
  qmemcpy(&tTemp, ptSpeed, sizeof(tTemp));
  tTemp.vY = v9 * tTemp.vY;
  tTemp.vZ = v9 * tTemp.vZ;
  ptPos->vX = tTemp.vX * v9 + ptPos->vX;
  ptPos->vY = tTemp.vY + ptPos->vY;
  ptPos->vZ = tTemp.vZ + ptPos->vZ;
  return (struct Spline_s *)ptPosa;
}

// source: j/0/network/spline.c:354  [anchor-callee]
void __cdecl Spline_OnSpline(
        struct real64x3_t *ptPos,
        struct real64x3_t *ptSpeed,
        struct Spline_s *ptSpline,
        int t)
{
  double v4; // st7
  struct real64x3_t *ptSpeeda = *(struct real64x3_t * *)&t; // [esp+Ch] [ebp+8h] ARGSLOT

  ptSpeeda = (struct real64x3_t *)(t - ptSpline->t0);
  v4 = (double)(int)ptSpeeda;
  ptPos->vX = ((v4 * ptSpline->x[3] + ptSpline->x[2]) * v4 + ptSpline->x[1]) * v4 + ptSpline->x[0];
  ptPos->vY = ((v4 * ptSpline->y[3] + ptSpline->y[2]) * v4 + ptSpline->y[1]) * v4 + ptSpline->y[0];
  ptPos->vZ = ((v4 * ptSpline->z[3] + ptSpline->z[2]) * v4 + ptSpline->z[1]) * v4 + ptSpline->z[0];
  Spline_Speed(ptSpline, ptSpeed, (int)ptSpeeda);
}

// source: j/0/network/spline.c:375  [anchor-callee]
void __cdecl Spline_Auto(
        struct real64x3_t *ptPos,
        struct real64x3_t *ptSpeed,
        struct Spline_s *ptSpline,
        int t)
{
  int t0; // edi

  t0 = ptSpline->t0;
  if ( t >= t0 )
  {
    if ( t <= ptSpline->a + t0 )
      Spline_OnSpline(ptPos, ptSpeed, ptSpline, t);
    else
      Spline_ExtraFromEnd(ptPos, ptSpeed, ptSpline, t);
  }
  else
  {
    Spline_ExtraFromStart(ptPos, ptSpeed, ptSpline, t);
  }
}

// source: j/0/network/spline.c:408  [anchor-refs]
void __cdecl Spline_Read(
        struct Spline_s *ptSpline,
        enum SplineRead_e eRead,
        struct real64x3_t *ptPos,
        struct real64x3_t *ptSpeed,
        int t)
{
  if ( eRead )
  {
    if ( eRead == SPLINE_READ_END )
    {
      Spline_ExtraFromEnd(ptPos, ptSpeed, ptSpline, t);
    }
    else
    {
      if ( eRead != SPLINE_READ_START )
      {
        LDebug_Error("Unknow spline read type used");
        abort();
      }
      Spline_ExtraFromStart(ptPos, ptSpeed, ptSpline, t);
    }
  }
  else
  {
    Spline_Auto(ptPos, ptSpeed, ptSpline, t);
  }
}

// source: j/0/network/spline.c:441  [anchor-refs]
void __cdecl Spline_ReadPosNow(
        struct Spline_s *ptSpline,
        enum SplineRead_e eRead,
        struct real64x3_t *ptPos)
{
  DWORD PerformanceCounter; // eax
  int v5; // eax
  struct real64x3_t tSpeed; // [esp+8h] [ebp-18h] BYREF

  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  v5 = PerformanceCounter - Timer_nStartTime;
  if ( eRead )
  {
    if ( eRead == SPLINE_READ_END )
    {
      Spline_ExtraFromEnd(ptPos, &tSpeed, ptSpline, v5);
    }
    else
    {
      if ( eRead != SPLINE_READ_START )
      {
        LDebug_Error("Unknow spline read type used");
        abort();
      }
      Spline_ExtraFromStart(ptPos, &tSpeed, ptSpline, v5);
    }
  }
  else
  {
    Spline_Auto(ptPos, &tSpeed, ptSpline, v5);
  }
}

// source: j/0/network/spline.c:466  [size]
int __cdecl Spline_GetStartTime(struct Spline_s *ptSpline)
{
  return ptSpline->t0;
}
