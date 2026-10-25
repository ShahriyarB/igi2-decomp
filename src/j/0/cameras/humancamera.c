/* j/0/cameras/humancamera.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/cameras/humancamera.c:85  [anchor-callee]
void __cdecl HumanCamera_FindFirstAvailableHuman(struct HumanCamera_t *ptHumanCamera)
{
  struct QReference_s *ptHumanQTaskRef; // eax
  int v2; // esi
  struct QTask_s *pxObject; // eax
  struct QReference_s *v4; // eax

  ptHumanQTaskRef = ptHumanCamera->ptHumanQTaskRef;
  if ( ptHumanQTaskRef )
  {
    QReference_Delete(ptHumanQTaskRef, &QTask_tQTaskRefPool);
    ptHumanCamera->ptHumanQTaskRef = nullptr;
  }
  v2 = 0;
  while ( !HumanCamera_atHumanList[v2].isUsed )
  {
    if ( ++v2 >= 128 )
      return;
  }
  pxObject = (struct QTask_s *)HumanCamera_atHumanList[v2].ptHumanQTaskRef->pxObject;
  if ( !pxObject )
  {
    LDebug_Error("ERROR IN HUMANCAMERA HUMANLIST");
    abort();
  }
  v4 = QTask_NewQTaskRef(pxObject);
  ptHumanCamera->nCurrentHuman = v2;
  ptHumanCamera->ptHumanQTaskRef = v4;
}

// source: j/0/cameras/humancamera.c:118  [anchor-mhash]
void __cdecl HumanCamera_CycleListForward(struct HumanCamera_t *ptHumanCamera)
{
  struct QReference_s *ptHumanQTaskRef; // eax
  int v2; // eax
  int v3; // edx
  int v4; // ecx
  int v5; // esi
  struct QTask_s *pxObject; // eax
  struct QReference_s *v7; // eax

  ptHumanQTaskRef = ptHumanCamera->ptHumanQTaskRef;
  if ( ptHumanQTaskRef )
  {
    QReference_Delete(ptHumanQTaskRef, &QTask_tQTaskRefPool);
    ptHumanCamera->ptHumanQTaskRef = nullptr;
  }
  v2 = ptHumanCamera->nCurrentHuman + 1;
  ptHumanCamera->nCurrentHuman = v2;
  v3 = v2;
  v4 = 0;
  while ( 1 )
  {
    v5 = v2 % 128;
    if ( HumanCamera_atHumanList[v2 % 128].isUsed )
      break;
    ++v4;
    ++v2;
    if ( v4 >= 128 )
    {
      ptHumanCamera->nCurrentHuman = v3 - 1;
      return;
    }
  }
  pxObject = (struct QTask_s *)HumanCamera_atHumanList[v5].ptHumanQTaskRef->pxObject;
  if ( !pxObject )
  {
    LDebug_Error("ERROR IN HUMANCAMERA HUMANLIST");
    abort();
  }
  v7 = QTask_NewQTaskRef(pxObject);
  ptHumanCamera->nCurrentHuman = v5;
  ptHumanCamera->ptHumanQTaskRef = v7;
}

// source: j/0/cameras/humancamera.c:159  [anchor-mhash]
void __cdecl HumanCamera_CycleListBackward(struct HumanCamera_t *ptHumanCamera)
{
  struct QReference_s *ptHumanQTaskRef; // eax
  int v2; // esi
  int v3; // eax
  int v4; // edi
  int v5; // edx
  int v6; // ebx
  int v7; // ecx
  struct QTask_s *pxObject; // eax
  struct QReference_s *v9; // eax

  ptHumanQTaskRef = ptHumanCamera->ptHumanQTaskRef;
  v2 = 0;
  if ( ptHumanQTaskRef )
  {
    QReference_Delete(ptHumanQTaskRef, &QTask_tQTaskRefPool);
    ptHumanCamera->ptHumanQTaskRef = nullptr;
  }
  v3 = ptHumanCamera->nCurrentHuman - 1;
  ptHumanCamera->nCurrentHuman = v3;
  v4 = v3 + 128;
  v5 = 8 * v3;
  while ( 1 )
  {
    v6 = v3;
    v7 = v5;
    if ( v3 < 0 )
    {
      v6 = v4;
      v7 = v5 + 1024;
    }
    if ( *(&HumanCamera_atHumanList[0].isUsed + v7) )
      break;
    ++v2;
    v5 -= 8;
    --v3;
    --v4;
    if ( v2 >= 128 )
    {
      ++ptHumanCamera->nCurrentHuman;
      return;
    }
  }
  pxObject = (struct QTask_s *)(*(struct QReference_s **)((char *)&HumanCamera_atHumanList[0].ptHumanQTaskRef + v7))->pxObject;
  if ( !pxObject )
  {
    LDebug_Error("ERROR IN HUMANCAMERA HUMANLIST");
    abort();
  }
  v9 = QTask_NewQTaskRef(pxObject);
  ptHumanCamera->nCurrentHuman = v6;
  ptHumanCamera->ptHumanQTaskRef = v9;
}

// source: j/0/cameras/humancamera.c:207  [size]
void __cdecl HumanCamera_ControlListInput(struct QTask_s *ptQTask)
{
  ;
}

// source: j/0/cameras/humancamera.c:433  [size]
struct QTask_s *__cdecl HumanCamera_FirstPersonInit(struct QTask_s *ptQTask)
{
  ptQTask[7].ptNext = nullptr;
  return ptQTask;
}

// source: j/0/cameras/humancamera.c:450  [size]
void __cdecl HumanCamera_FirstPersonControlInput(struct QTask_s *ptQTask)
{
  ;
}

// source: j/0/cameras/humancamera.c:464  [anchor-callee]
struct QTask_s *__cdecl HumanCamera_FirstPersonSetCamera(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real32x9_t tOrientation; };
    struct { char igi2_o1[40]; struct real32x9_t Real32x9_Multiply_tTemp; };
    char igi2_extent[84];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  long double v1; // st7
  long double v2; // st6
  long double v3; // st5
  double v4; // st4
  double v5; // st4
  long double v6; // st4
  double v7; // st7

  v1 = sin(-1.5707963705062866);
  qmemcpy(&igi2_frame.tOrientation, &ptQTask[3].tQTaskRefList.ptMiddle, sizeof(igi2_frame.tOrientation));
  qmemcpy(&ptQTask[6].tQTaskChildren, &ptQTask[3], 0x18u);
  v2 = cos(-1.5707963705062866);
  v3 = -v1;
  igi2_frame.Real32x9_Multiply_tTemp.tX.vX = (igi2_frame.tOrientation.tX.vZ + igi2_frame.tOrientation.tX.vY) * 0.0 + igi2_frame.tOrientation.tX.vX;
  v4 = igi2_frame.tOrientation.tX.vX * 0.0;
  igi2_frame.Real32x9_Multiply_tTemp.tX.vY = v1 * igi2_frame.tOrientation.tX.vZ + v2 * igi2_frame.tOrientation.tX.vY + v4;
  igi2_frame.Real32x9_Multiply_tTemp.tX.vZ = v2 * igi2_frame.tOrientation.tX.vZ + -v1 * igi2_frame.tOrientation.tX.vY + v4;
  igi2_frame.Real32x9_Multiply_tTemp.tY.vX = (igi2_frame.tOrientation.tY.vZ + igi2_frame.tOrientation.tY.vY) * 0.0 + igi2_frame.tOrientation.tY.vX;
  v5 = igi2_frame.tOrientation.tY.vX * 0.0;
  igi2_frame.Real32x9_Multiply_tTemp.tY.vY = v1 * igi2_frame.tOrientation.tY.vZ + v2 * igi2_frame.tOrientation.tY.vY + v5;
  igi2_frame.Real32x9_Multiply_tTemp.tY.vZ = v2 * igi2_frame.tOrientation.tY.vZ + igi2_frame.tOrientation.tY.vY * -v1 + v5;
  igi2_frame.Real32x9_Multiply_tTemp.tZ.vX = (igi2_frame.tOrientation.tZ.vZ + igi2_frame.tOrientation.tZ.vY) * 0.0 + igi2_frame.tOrientation.tZ.vX;
  v6 = v1;
  v7 = igi2_frame.tOrientation.tZ.vX * 0.0;
  igi2_frame.Real32x9_Multiply_tTemp.nOps = igi2_frame.tOrientation.nOps + 1;
  igi2_frame.Real32x9_Multiply_tTemp.tZ.vY = v6 * igi2_frame.tOrientation.tZ.vZ + v2 * igi2_frame.tOrientation.tZ.vY + v7;
  qmemcpy(&ptQTask[1], &ptQTask[3], 0x18u);
  igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ = v2 * igi2_frame.tOrientation.tZ.vZ + igi2_frame.tOrientation.tZ.vY * v3 + v7;
  qmemcpy(&ptQTask[1].tQTaskRefList.ptMiddle, &igi2_frame.Real32x9_Multiply_tTemp, sizeof(struct QTask_s));
  ptQTask[2].tQTaskRefList.ptMiddle = ptQTask[4].tQTaskRefList.ptMiddle;
  return ptQTask;
}

// source: j/0/cameras/humancamera.c:512  [size]
struct QTask_s *__cdecl HumanCamera_ThirdPersonInit(struct QTask_s *ptQTask)
{
  ptQTask[7].ptNext = (struct QTask_s *)1149239296;
  ptQTask[6].ptParent = nullptr;
  *(_DWORD *)&ptQTask[6].eQTaskType = 0;
  return ptQTask;
}

// source: j/0/cameras/humancamera.c:533  [anchor-callee]
void __cdecl HumanCamera_ThirdPersonControlInput(struct QTask_s *ptQTask)
{
  if ( *(float *)&ptQTask[7].ptNext >= 1024.0 )
  {
    if ( *(float *)&ptQTask[7].ptNext > 409600.0 )
      ptQTask[7].ptNext = (struct QTask_s *)1221066752;
  }
  else
  {
    ptQTask[7].ptNext = (struct QTask_s *)1149239296;
  }
  if ( *(float *)&ptQTask[6].ptParent < -1.5533430576324463 )
    ptQTask[6].ptParent = (struct QTask_s *)-1077488654;
  if ( *(float *)&ptQTask[6].ptParent > 1.5533430576324463 )
    ptQTask[6].ptParent = (struct QTask_s *)1069994994;
}

// source: j/0/cameras/humancamera.c:599  [anchor-callee]
void __cdecl HumanCamera_ThirdPersonSetCamera(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { double a1[3]; };
    struct { char igi2_o1[24]; double v11[3]; };
    struct { char igi2_o2[48]; double a3[3]; };
    struct { char igi2_o3[72]; struct real32x9_t ptDest; };
    char igi2_extent[116];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  long double v1; // st7
  double v2; // st7
  double v3; // st6
  double v4; // st5
  double v5; // st4
  double v6; // st3
  double v7; // st2
  double v8; // st3
  double v9; // st6

  if ( *(float *)&ptQTask[7].ptNext == 0.0 )
  {
    v1 = *(float *)&ptQTask[4].tQTaskRefList.ptMiddle;
    qmemcpy(igi2_frame.a3, &ptQTask[3], sizeof(igi2_frame.a3));
    qmemcpy(&igi2_frame.ptDest, &ptQTask[3].tQTaskRefList.ptMiddle, sizeof(igi2_frame.ptDest));
    qmemcpy(&ptQTask[6].tQTaskChildren, &ptQTask[3], 0x18u);
  }
  else
  {
    Real32x9_Create(&igi2_frame.ptDest, *(float *)&ptQTask[6].ptParent, 0.0, *(float *)&ptQTask[6].eQTaskType);
    v2 = -*(float *)&ptQTask[7].ptNext;
    qmemcpy(igi2_frame.v11, &ptQTask[3], sizeof(igi2_frame.v11));
    v3 = (igi2_frame.ptDest.tX.vZ + igi2_frame.ptDest.tX.vX) * 0.0 + igi2_frame.ptDest.tX.vY * v2;
    qmemcpy(igi2_frame.a1, &ptQTask[6].tQTaskChildren, sizeof(igi2_frame.a1));
    v4 = (igi2_frame.ptDest.tY.vZ + igi2_frame.ptDest.tY.vX) * 0.0 + igi2_frame.ptDest.tY.vY * v2;
    v5 = (igi2_frame.ptDest.tZ.vZ + igi2_frame.ptDest.tZ.vX) * 0.0 + igi2_frame.ptDest.tZ.vY * v2;
    v6 = *(float *)&ptQTask[4].eQTaskType * v5;
    igi2_frame.a1[0] = igi2_frame.v11[0];
    v7 = *(float *)&ptQTask[4].ptParent * v4;
    igi2_frame.a1[1] = igi2_frame.v11[1];
    *(double *)&igi2_frame.ptDest.tX.vX = v6 + v7 + *(float *)&ptQTask[4].tQTaskRefList.ptTail * v3;
    *(double *)&igi2_frame.ptDest.tX.vZ = *(float *)&ptQTask[5].tQTaskChildren.ptHead * v5
                             + *(float *)&ptQTask[5].ptPrev * v4
                             + *(float *)&ptQTask[5].ptNext * v3;
    v8 = *(float *)&ptQTask[5].tQTaskRefList.ptHead * v5
       + *(float *)&ptQTask[5].tQTaskChildren.ptTail * v4
       + *(float *)&ptQTask[5].tQTaskChildren.ptMiddle * v3;
    igi2_frame.a1[2] = igi2_frame.v11[2] * 0.05 + igi2_frame.a1[2] * 0.95;
    v9 = igi2_frame.v11[0] + *(double *)&igi2_frame.ptDest.tX.vX;
    qmemcpy(&ptQTask[6].tQTaskChildren, igi2_frame.a1, 0x18u);
    igi2_frame.a3[0] = v9;
    igi2_frame.a3[1] = igi2_frame.v11[1] + *(double *)&igi2_frame.ptDest.tX.vZ;
    igi2_frame.a3[2] = igi2_frame.a1[2] + v8;
    sub_4DEE70(igi2_frame.a1, &igi2_frame.ptDest.tX.vX, igi2_frame.a3);
    v1 = tan(0.7853981852531433);
  }
  *(float *)&ptQTask[2].tQTaskRefList.ptMiddle = v1;
  qmemcpy(&ptQTask[1], igi2_frame.a3, 0x18u);
  qmemcpy(&ptQTask[1].tQTaskRefList.ptMiddle, &igi2_frame.ptDest, sizeof(struct QTask_s));
}

// source: j/0/cameras/humancamera.c:693  [anchor-callee]
void __cdecl HumanCamera_MovementInit(struct QTask_s *ptQTask)
{
  ptQTask[7].ptNext = (struct QTask_s *)1149239296;
  ptQTask[7].ptPrev = (struct QTask_s *)1176502272;
  ptQTask[6].ptParent = nullptr;
  *(_DWORD *)&ptQTask[6].eQTaskType = 0;
  *(float *)&ptQTask[2].tQTaskRefList.ptMiddle = tan(0.7853981852531433);
  sub_4DE380(0, (int)ptQTask);
}

// source: j/0/cameras/humancamera.c:715  [anchor-callee]
struct QTask_s *__cdecl HumanCamera_MovementControlInput(struct QTask_s *ptQTask)
{
  struct QTask_s *result; // eax
  float v2; // [esp+0h] [ebp-Ch]
  float vDeltaAlpha; // [esp+4h] [ebp-8h]

  vDeltaAlpha = InputPort_atInputPort[0].tInput.vAnalogX * 0.6981317400932312;
  v2 = InputPort_atInputPort[0].tInput.vAnalogY * 0.6981317400932312;
  HumanCamera_UpdateAlphaAndGammaWithCollisions(ptQTask, v2, vDeltaAlpha);
  return result;
}

// source: j/0/cameras/humancamera.c:765  [size~]
void __cdecl HumanCamera_MovementSetCamera(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { int vBeta; };
    struct { float vBetaa; };
    struct { char igi2_o2[24]; float pvBeta; };
    struct { char igi2_o3[28]; struct real32x9_t ptSource; };
    struct { char igi2_o4[68]; int v24; };
    struct { char igi2_o5[72]; int v25; };
    struct { char igi2_o6[76]; double v26; };
    struct { char igi2_o7[84]; struct real64x3_t v27; };
    struct { char igi2_o8[108]; struct real32x9_t ptPos; };
    struct { char igi2_o9[148]; struct real64x3_t v29; };
    char igi2_extent[172];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  DWORD PerformanceCounter; // eax
  struct QTask_s *v2; // ebx
  int v3; // ebp
  struct QTask_s *ptNext; // eax
  DWORD TickCount; // eax
  double vX; // st7
  double v7; // st7
  double i; // st7
  int v9; // eax
  double v10; // st7
  struct Spline_s *p_ptMiddle; // esi
  struct QTask_s *ptPrev; // ecx
  int v13; // ecx
  struct Spline_s *v14; // eax
  DWORD v15; // eax
  int v16; // eax
  struct QTask_s *v17; // ecx
  bool v18; // cc
  struct Spline_s *v19; // eax

  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  v2 = ptQTask;
  v3 = PerformanceCounter - Timer_nStartTime;
  qmemcpy(&igi2_frame.ptPos, &ptQTask[4].tQTaskRefList.ptTail, sizeof(igi2_frame.ptPos));
  Real32x9_GetAngles(&igi2_frame.ptPos, &igi2_frame.ptSource.tX.vX, &igi2_frame.ptSource.tX.vY, &igi2_frame.pvBeta);
  ptNext = ptQTask[10].ptNext;
  igi2_frame.pvBeta = igi2_frame.pvBeta - 3.1415927410125732;
  if ( (int)ptNext <= 0 )
  {
    vX = igi2_frame.ptSource.tX.vX;
    *(float *)&ptQTask[10].tQTaskChildren.ptHead = igi2_frame.pvBeta;
  }
  else
  {
    if ( Timer_isPerformanceCounter )
      TickCount = Timer_GetPerformanceCounter();
    else
      TickCount = GetTickCount();
    Spline_ExtraFromEnd(
      &igi2_frame.v27,
      (struct real64x3_t *)&igi2_frame.ptPos,
      (struct Spline_s *)&ptQTask[7].tQTaskRefList.ptMiddle,
      TickCount - Timer_nStartTime);
    for ( vX = igi2_frame.v27.vZ; vX - igi2_frame.pvBeta < -3.1415927410125732; vX = vX + 6.2831854820251465 )
      ;
    for ( ; vX - igi2_frame.pvBeta > 3.1415927410125732; vX = vX - 6.2831854820251465 )
      ;
    v2 = ptQTask;
  }
  if ( (int)v2[10].ptNext <= 0 || (signed int)(v3 - (unsigned int)v2[10].ptPrev) > 500 )
    goto LABEL_20;
  v7 = vX - igi2_frame.pvBeta;
  if ( v7 < 0.0 )
    v7 = -v7;
  if ( v7 > 0.15707963705062866 )
  {
LABEL_20:
    for ( i = igi2_frame.pvBeta; i - *(float *)&v2[10].tQTaskChildren.ptHead < -3.1415927410125732; i = i + 6.2831854820251465 )
      ;
    for ( ; i - *(float *)&v2[10].tQTaskChildren.ptHead > 3.1415927410125732; i = i - 6.2831854820251465 )
      ;
    v9 = (int)v2[10].ptNext;
    *(double *)&igi2_frame.ptSource.tZ.vX = i;
    v10 = i - *(float *)&v2[10].tQTaskChildren.ptHead;
    p_ptMiddle = (struct Spline_s *)&v2[7].tQTaskRefList.ptMiddle;
    memset(&igi2_frame.ptSource.tX.vZ, 0, 16);
    igi2_frame.v26 = v10 * 0.001;
    igi2_frame.ptSource.tZ.vZ = 0.0;
    igi2_frame.ptSource.nOps = 0;
    igi2_frame.v24 = 0;
    igi2_frame.v25 = 0;
    if ( v9 <= 0 )
    {
      Spline_Initialize(
        p_ptMiddle,
        (struct real64x3_t *)&igi2_frame.ptSource.tX.vZ,
        (struct real64x3_t *)&igi2_frame.ptSource.tX.vZ,
        (struct real64x3_t *)&igi2_frame.ptSource.tZ.vZ,
        (struct real64x3_t *)&igi2_frame.ptSource.tZ.vZ,
        v3,
        500);
    }
    else
    {
      ptPrev = v2[10].ptPrev;
      if ( v3 >= (int)ptPrev )
      {
        v13 = (int)ptPrev + v9;
        v14 = (struct Spline_s *)&v2[7].tQTaskRefList.ptMiddle;
        if ( v3 <= v13 )
          Spline_OnSpline(&igi2_frame.v29, (struct real64x3_t *)&igi2_frame.ptPos, v14, v3);
        else
          Spline_ExtraFromEnd(&igi2_frame.v29, (struct real64x3_t *)&igi2_frame.ptPos, v14, v3);
        Spline_Initialize(
          p_ptMiddle,
          &igi2_frame.v29,
          (struct real64x3_t *)&igi2_frame.ptSource.tX.vZ,
          (struct real64x3_t *)&igi2_frame.ptPos,
          (struct real64x3_t *)&igi2_frame.ptSource.tZ.vZ,
          v3,
          500);
      }
      else
      {
        Spline_ExtraFromStart(&igi2_frame.v29, (struct real64x3_t *)&igi2_frame.ptPos, (struct Spline_s *)&v2[7].tQTaskRefList.ptMiddle, v3);
        Spline_Initialize(
          p_ptMiddle,
          &igi2_frame.v29,
          (struct real64x3_t *)&igi2_frame.ptSource.tX.vZ,
          (struct real64x3_t *)&igi2_frame.ptPos,
          (struct real64x3_t *)&igi2_frame.ptSource.tZ.vZ,
          v3,
          500);
      }
    }
    v2 = ptQTask;
  }
  if ( Timer_isPerformanceCounter )
    v15 = Timer_GetPerformanceCounter();
  else
    v15 = GetTickCount();
  v16 = v15 - Timer_nStartTime;
  v17 = v2[10].ptPrev;
  igi2_frame.vBeta = v16;
  if ( v16 >= (int)v17 )
  {
    v18 = v16 <= (int)((int)v2[10].ptNext + (unsigned int)v17);
    v19 = (struct Spline_s *)&v2[7].tQTaskRefList.ptMiddle;
    if ( v18 )
    {
      Spline_OnSpline(&igi2_frame.v27, (struct real64x3_t *)&igi2_frame.ptPos, v19, igi2_frame.vBeta);
    }
    else
    {
      Spline_ExtraFromEnd(&igi2_frame.v27, (struct real64x3_t *)&igi2_frame.ptPos, v19, igi2_frame.vBeta);
      v2 = ptQTask;
    }
  }
  else
  {
    Spline_ExtraFromStart(&igi2_frame.v27, (struct real64x3_t *)&igi2_frame.ptPos, (struct Spline_s *)&v2[7].tQTaskRefList.ptMiddle, v16);
    v2 = ptQTask;
  }
  igi2_frame.pvBeta = igi2_frame.v27.vZ;
  igi2_frame.vBetaa = igi2_frame.v27.vZ + 3.1415927410125732;
  Real32x9_Create((struct real32x9_t *)&v2[4].tQTaskRefList.ptTail, igi2_frame.ptSource.tX.vX, igi2_frame.ptSource.tX.vY, igi2_frame.vBetaa);
  *(float *)&v2[10].tQTaskChildren.ptHead = igi2_frame.pvBeta;
}

void __cdecl sub_4DFC10(int a1)
{
  int v1; // eax
  int v2; // eax
  double v3; // st7
  double i; // st7
  float vDeltaAlpha; // [esp+4h] [ebp-8h]
  float ptQTask; // [esp+8h] [ebp-4h]

  v1 = *(_DWORD *)(a1 + 112);
  if ( v1 )
    v2 = *(_DWORD *)(v1 + 8);
  else
    v2 = 0;
  ptQTask = InputPort_atInputPort[0].tInput.vAnalogY * 0.6981317400932312;
  if ( v2 && *(_BYTE *)(v2 + 1180) )
  {
    v3 = InputPort_atInputPort[0].tInput.vAnalogX * 0.6981317400932312;
  }
  else
  {
    for ( i = -1.5707963705062866 - *(float *)(a1 + 276); i < -3.1415927410125732; i = i + 6.2831854820251465 )
      ;
    for ( ; i >= 3.1415927410125732; i = i - 6.2831854820251465 )
      ;
    v3 = i * 0.25;
  }
  vDeltaAlpha = v3;
  HumanCamera_MovementSetCamera((struct QTask_s *)a1);
  HumanCamera_UpdateAlphaAndGammaWithCollisions((struct QTask_s *)a1, ptQTask, vDeltaAlpha);
}

// source: j/0/cameras/humancamera.c:936  [anchor-caller]
void __cdecl HumanCamera_SpectateSetFirstCamera(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // ebx

  ptHead = ptQTask[2].ptParent->tQTaskChildren.ptHead;
  if ( ptHead )
  {
    qmemcpy(&ptQTask[1], &ptHead[33].tQTaskChildren.ptTail[10].tQTaskChildren, 0x18u);
    qmemcpy(&ptQTask[1].tQTaskRefList.ptMiddle, &ptHead[33].tQTaskChildren.ptTail[10].ptParent, sizeof(struct QTask_s));
    Real32x9_RotateAlpha(
      (struct real32x9_t *)&ptQTask[1].tQTaskRefList.ptMiddle,
      (struct real32x9_t *)&ptQTask[1].tQTaskRefList.ptMiddle,
      -1.5707963705062866);
    ptQTask[2].tQTaskRefList.ptMiddle = (struct QReference_s *)ptHead[33].tQTaskChildren.ptTail[16].tQTaskChildren.ptHead;
  }
}

// source: j/0/cameras/humancamera.c:1195  [size]
void __cdecl HumanCamera_OverrideInit(struct QTask_s *ptQTask)
{
  ;
}

// source: j/0/cameras/humancamera.c:1209  [size]
void __cdecl HumanCamera_OverrideControlInput(struct QTask_s *ptQTask)
{
  ;
}

// source: j/0/cameras/humancamera.c:1223  [anchor-callee]
struct QTask_s *__cdecl HumanCamera_OverrideSetCamera(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real32x9_t tOrientation; };
    struct { char igi2_o1[40]; struct real32x9_t Real32x9_Multiply_tTemp; };
    char igi2_extent[84];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  long double v1; // st7
  long double v2; // st6
  long double v3; // st5
  double v4; // st4
  double v5; // st4
  long double v6; // st4
  double v7; // st7

  v1 = sin(-1.5707963705062866);
  qmemcpy(&igi2_frame.tOrientation, &ptQTask[3].tQTaskRefList.ptMiddle, sizeof(igi2_frame.tOrientation));
  qmemcpy(&ptQTask[6].tQTaskChildren, &ptQTask[3], 0x18u);
  v2 = cos(-1.5707963705062866);
  v3 = -v1;
  igi2_frame.Real32x9_Multiply_tTemp.tX.vX = (igi2_frame.tOrientation.tX.vZ + igi2_frame.tOrientation.tX.vY) * 0.0 + igi2_frame.tOrientation.tX.vX;
  v4 = igi2_frame.tOrientation.tX.vX * 0.0;
  igi2_frame.Real32x9_Multiply_tTemp.tX.vY = v1 * igi2_frame.tOrientation.tX.vZ + v2 * igi2_frame.tOrientation.tX.vY + v4;
  igi2_frame.Real32x9_Multiply_tTemp.tX.vZ = v2 * igi2_frame.tOrientation.tX.vZ + -v1 * igi2_frame.tOrientation.tX.vY + v4;
  igi2_frame.Real32x9_Multiply_tTemp.tY.vX = (igi2_frame.tOrientation.tY.vZ + igi2_frame.tOrientation.tY.vY) * 0.0 + igi2_frame.tOrientation.tY.vX;
  v5 = igi2_frame.tOrientation.tY.vX * 0.0;
  igi2_frame.Real32x9_Multiply_tTemp.tY.vY = v1 * igi2_frame.tOrientation.tY.vZ + v2 * igi2_frame.tOrientation.tY.vY + v5;
  igi2_frame.Real32x9_Multiply_tTemp.tY.vZ = v2 * igi2_frame.tOrientation.tY.vZ + igi2_frame.tOrientation.tY.vY * -v1 + v5;
  igi2_frame.Real32x9_Multiply_tTemp.tZ.vX = (igi2_frame.tOrientation.tZ.vZ + igi2_frame.tOrientation.tZ.vY) * 0.0 + igi2_frame.tOrientation.tZ.vX;
  v6 = v1;
  v7 = igi2_frame.tOrientation.tZ.vX * 0.0;
  igi2_frame.Real32x9_Multiply_tTemp.nOps = igi2_frame.tOrientation.nOps + 1;
  igi2_frame.Real32x9_Multiply_tTemp.tZ.vY = v6 * igi2_frame.tOrientation.tZ.vZ + v2 * igi2_frame.tOrientation.tZ.vY + v7;
  qmemcpy(&ptQTask[1], &ptQTask[3], 0x18u);
  igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ = v2 * igi2_frame.tOrientation.tZ.vZ + igi2_frame.tOrientation.tZ.vY * v3 + v7;
  qmemcpy(&ptQTask[1].tQTaskRefList.ptMiddle, &igi2_frame.Real32x9_Multiply_tTemp, sizeof(struct QTask_s));
  ptQTask[2].tQTaskRefList.ptMiddle = ptQTask[4].tQTaskRefList.ptMiddle;
  return ptQTask;
}

// source: j/0/cameras/humancamera.c:1272  [anchor-callee]
void __cdecl HumanCamera_DeathCameraInit(struct QTask_s *ptQTask)
{
  ptQTask[7].ptNext = (struct QTask_s *)1149239296;
  ptQTask[7].ptPrev = (struct QTask_s *)1176502272;
  ptQTask[6].ptParent = nullptr;
  *(_DWORD *)&ptQTask[6].eQTaskType = 0;
  ptQTask[7].tQTaskRefList.ptHead = (struct QReference_s *)1;
  *(float *)&ptQTask[2].tQTaskRefList.ptMiddle = tan(0.7853981852531433);
  sub_4DE380(0, (int)ptQTask);
}

// source: j/0/cameras/humancamera.c:1298  [anchor-callee]
void __cdecl HumanCamera_UpdateAlphaAndGammaWithCollisions(
        struct QTask_s *ptQTask,
        float vDeltaAlpha,
        float vDeltaGamma)
{
  double v4; // st7
  double v5; // st6
  int v6; // esi
  double v7; // st7
  double v8; // st7
  double v9; // st7

  if ( vDeltaAlpha >= -0.10471975803375244 )
  {
    if ( vDeltaAlpha > 0.10471975803375244 )
      vDeltaAlpha = 0.10471975803375244;
  }
  else
  {
    vDeltaAlpha = -0.10471975803375244;
  }
  v4 = vDeltaGamma;
  if ( vDeltaGamma >= -0.10471975803375244 )
  {
    if ( v4 > 0.10471975803375244 )
      v4 = 0.10471975803375244;
  }
  else
  {
    v4 = -0.10471975803375244;
  }
  v5 = *(float *)&ptQTask[6].ptParent - vDeltaAlpha;
  *(float *)&ptQTask[6].ptParent = v5;
  if ( v5 >= -1.242674469947815 )
  {
    if ( v5 > 1.5533430576324463 )
      v5 = 1.5533430576324463;
  }
  else
  {
    v5 = -1.242674469947815;
  }
  *(float *)&ptQTask[6].ptParent = v5;
  *(float *)&ptQTask[6].eQTaskType = v4 + *(float *)&ptQTask[6].eQTaskType;
  sub_4DE620((int)ptQTask);
  v6 = sub_4DE830((int)ptQTask);
  sub_4DE720((int)ptQTask);
  sub_4DEE70((double *)&ptQTask[3], (float *)&ptQTask[1].tQTaskRefList.ptMiddle, (double *)&ptQTask[1]);
  if ( !v6 )
  {
    v7 = *(float *)&ptQTask[7].ptNext;
    if ( v7 >= *(float *)&ptQTask[7].ptPrev )
    {
      if ( v7 > *(float *)&ptQTask[7].ptPrev )
      {
        v9 = *(float *)&ptQTask[7].ptNext - 136.53334045410156;
        *(float *)&ptQTask[7].ptNext = v9;
        if ( v9 < *(float *)&ptQTask[7].ptPrev )
          ptQTask[7].ptNext = ptQTask[7].ptPrev;
      }
    }
    else
    {
      v8 = v7 + 136.53334045410156;
      *(float *)&ptQTask[7].ptNext = v8;
      if ( v8 > *(float *)&ptQTask[7].ptPrev )
        ptQTask[7].ptNext = ptQTask[7].ptPrev;
    }
  }
}

// source: j/0/cameras/humancamera.c:1500  [anchor-callee]
void __cdecl HumanCamera_DeathCameraControlInput(struct QTask_s *ptQTask)
{
  struct QTask_s *ptParent; // eax
  struct QTask_s *ptHead; // edx
  struct QReference_s *ptMiddle; // eax
  float v4; // [esp+0h] [ebp-Ch]
  float vDeltaAlpha; // [esp+4h] [ebp-8h]

  ptParent = ptQTask[2].ptParent;
  if ( !ptParent
    || (ptHead = ptParent->tQTaskChildren.ptHead,
        QTask_IsQTaskTypeDerived(ptHead->eQTaskType, HumanPlayer_eQTaskType) == false)
    || (ptMiddle = ptHead[86].tQTaskRefList.ptMiddle) == nullptr
    || !ptMiddle->pxObject
    || ((int)ptQTask[7].tQTaskRefList.ptHead & 1) == 0 )
  {
    vDeltaAlpha = InputPort_atInputPort[0].tInput.vAnalogX * 0.6981317400932312;
    v4 = InputPort_atInputPort[0].tInput.vAnalogY * 0.6981317400932312;
    HumanCamera_UpdateAlphaAndGammaWithCollisions(ptQTask, v4, vDeltaAlpha);
  }
}

void __cdecl sub_4E0120(struct QTaskList_s *ptQTaskList)
{
  ptQTaskList[3].nMaxTask = 0;
  ptQTaskList[3].ptQTask[0] = nullptr;
  ptQTaskList[4].nTask = 0;
  ptQTaskList[4].nMaxTask = 0;
  ptQTaskList[4].ptQTask[0] = nullptr;
  ptQTaskList[5].nTask = 0;
  ptQTaskList[5].nMaxTask = 1065353216;
  ptQTaskList[5].ptQTask[0] = nullptr;
  ptQTaskList[6].nTask = 0;
  ptQTaskList[6].nMaxTask = 0;
  ptQTaskList[6].ptQTask[0] = (struct QTask_s *)1065353216;
  ptQTaskList[7].nTask = 0;
  ptQTaskList[7].nMaxTask = 0;
  ptQTaskList[7].ptQTask[0] = nullptr;
  ptQTaskList[8].nTask = 1065353216;
  ptQTaskList[8].nMaxTask = 0;
  ptQTaskList[9].nMaxTask = 0;
  ptQTaskList[24].ptQTask[0] = nullptr;
  ptQTaskList[20].nTask = 0;
  ptQTaskList[20].ptQTask[0] = nullptr;
  ptQTaskList[21].nTask = 0;
  ptQTaskList[21].nMaxTask = 0;
  ptQTaskList[21].ptQTask[0] = nullptr;
  ptQTaskList[22].nTask = 0;
  ptQTaskList[22].nMaxTask = 0;
  ptQTaskList[22].ptQTask[0] = nullptr;
  ptQTaskList[23].nTask = 0;
  ptQTaskList[23].nMaxTask = 0;
  ptQTaskList[23].ptQTask[0] = nullptr;
  ptQTaskList[24].nTask = 0;
  ptQTaskList[24].nMaxTask = 0;
  ptQTaskList[25].nTask = 0;
  ptQTaskList[34].nMaxTask = 0;
  ptQTaskList[33].nMaxTask = -1;
  ptQTaskList[34].nTask = 0;
  *(float *)ptQTaskList[8].ptQTask = tan(0.7853981852531433);
  QTaskList_Register(Flow_ptDrawInterpolateQTaskList, ptQTaskList);
}

// source: j/0/cameras/humancamera.c:1888  [anchor-caller]
void __cdecl HumanCamera_RunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptParent; // eax
  struct QTask_s *ptHead; // eax
  struct QTask_s *v3; // eax
  BOOL v4; // ebx
  float nFrameNumber; // [esp+0h] [ebp-14h]
  int isFirstPerson; // [esp+10h] [ebp-4h]

  ptParent = ptQTask[2].ptParent;
  isFirstPerson = 0;
  if ( ptParent && (ptHead = ptParent->tQTaskChildren.ptHead) != nullptr )
  {
    ((void (__cdecl *)(struct QTask_s *, struct QTask_s *))QTask_aatQTaskFinalEvent[HumanCamera_eGetHumanCameraInfoQTaskEvent][ptHead->eQTaskType].pfHandler)(
      ptHead,
      &ptQTask[3]);
    v3 = ptQTask[5].ptParent;
    v4 = ptQTask[6].ptNext != v3;
    ptQTask[6].ptNext = v3;
    switch ( (unsigned int)v3 )
    {
      case 1u:
        if ( v4 )
          ptQTask[7].ptNext = nullptr;
        HumanCamera_FirstPersonSetCamera(ptQTask);
        isFirstPerson = 1;
        break;
      case 2u:
        if ( v4 )
        {
          ptQTask[7].ptNext = (struct QTask_s *)1149239296;
          ptQTask[6].ptParent = nullptr;
          *(_DWORD *)&ptQTask[6].eQTaskType = 0;
        }
        HumanCamera_ThirdPersonControlInput(ptQTask);
        HumanCamera_ThirdPersonSetCamera(ptQTask);
        break;
      case 3u:
        if ( v4 )
          HumanCamera_MovementInit(ptQTask);
        HumanCamera_MovementControlInput(ptQTask);
        break;
      case 4u:
        HumanCamera_OverrideSetCamera(ptQTask);
        break;
      case 5u:
        if ( v4 )
          HumanCamera_DeathCameraInit(ptQTask);
        HumanCamera_DeathCameraControlInput(ptQTask);
        ptQTask[7].tQTaskRefList.ptHead = (struct QReference_s *)((int)ptQTask[7].tQTaskRefList.ptHead & ~1u);
        break;
      case 6u:
        HumanCamera_SpectateSetFirstCamera(ptQTask);
        break;
      case 7u:
        if ( v4 )
        {
          HumanCamera_MovementInit(ptQTask);
          ptQTask[10].ptNext = (struct QTask_s *)-1;
        }
        sub_4DFC10((int)ptQTask);
        break;
      default:
        break;
    }
    nFrameNumber = (double)LevelFlow_ptLevelFlow->nTimeOfDayTick / ((double)Flow_ptFlow->nFrequency * 3600.0)
                 + LevelFlow_ptLevelFlow->vStartTime;
    QCamera_Set(
      (struct QCamera_s *)ptQTask[2].tQTaskRefList.ptTail,
      (struct real64x3_t *)&ptQTask[1],
      (struct real32x9_t *)&ptQTask[1].tQTaskRefList.ptMiddle,
      *(float *)&ptQTask[2].tQTaskRefList.ptMiddle,
      1.0,
      300.0,
      Screen_nFrameNumber,
      ptQTask,
      nFrameNumber,
      isFirstPerson);
    Mesh3D_avOverrideFOV[0] = *(float *)&ptQTask[5].tQTaskRefList.ptTail;
  }
  else
  {
    HumanCamera_FindFirstAvailableHuman((struct HumanCamera_t *)ptQTask);
  }
}

void __cdecl sub_4E0390(struct QTask_s *a1)
{
  ((void (__cdecl *)())QTask_aatQTaskFinalEvent[1][a1->eQTaskType].pfHandler)(a1);
}

// source: j/0/cameras/humancamera.c:2095  [anchor-mhash]
void __cdecl HumanCamera_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptParent; // eax
  struct QTask_s *ptTail; // eax

  ptParent = ptQTask[2].ptParent;
  if ( ptParent )
  {
    QReference_Delete((struct QReference_s *)ptParent, &QTask_tQTaskRefPool);
    ptQTask[2].ptParent = nullptr;
  }
  ptTail = ptQTask[7].tQTaskChildren.ptTail;
  if ( ptTail )
  {
    QReference_Delete((struct QReference_s *)ptTail, &QTask_tQTaskRefPool);
    ptQTask[7].tQTaskChildren.ptTail = nullptr;
  }
  QTaskList_Remove(Flow_ptDrawInterpolateQTaskList, ptQTask);
}

// source: j/0/cameras/humancamera.c:2117  [anchor-strings]
void __cdecl HumanCamera_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  __int16 v1; // ax
  unsigned __int16 v2; // si
  char *p_isUsed; // eax

  BaseQTaskType = QTask_GetBaseQTaskType();
  HumanCamera_eQTaskType = QTask_NewQTaskType("HumanCamera", 416, BaseQTaskType, 0, 0);
  v1 = QTask_NewQTaskEventFn(0, "GetHumanCameraInfo");
  v2 = HumanCamera_eQTaskType;
  HumanCamera_eGetHumanCameraInfoQTaskEvent = v1;
  QTask_LinkQTaskEventHandlerFn(HumanCamera_eQTaskType, 0, (void (__cdecl *)(struct QTask_s *, void *))sub_4E0120);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, 1, HumanCamera_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, 2, HumanCamera_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v2,
    Flow_eDrawInterpolateQTaskEvent,
    (void (__cdecl *)(struct QTask_s *))sub_4E0390);
  p_isUsed = &HumanCamera_atHumanList[0].isUsed;
  do
  {
    *(_DWORD *)(p_isUsed - 5) = 0;
    *p_isUsed = 0;
    p_isUsed += 8;
  }
  while ( (int)p_isUsed < 7679669 );
}

// source: j/0/cameras/humancamera.c:2152  [anchor-hash]
char *HumanCamera_Close()
{
  char *result; // eax

  QTask_DeleteQTaskEvent(HumanCamera_eGetHumanCameraInfoQTaskEvent);
  QTask_DeleteQTaskType(HumanCamera_eQTaskType);
  result = &HumanCamera_atHumanList[0].isUsed;
  do
  {
    if ( *result )
    {
      LDebug_Error("HumanCamera humanlist not empty");
      abort();
    }
    result += 8;
  }
  while ( (int)result < 7679669 );
  return result;
}

// source: j/0/cameras/humancamera.c:2183  [size]
__int16 __cdecl HumanCamera_GetGetHumanCameraInfoQTaskEvent()
{
  return HumanCamera_eGetHumanCameraInfoQTaskEvent;
}

// source: j/0/cameras/humancamera.c:2197  [size]
struct QTask_s *__cdecl HumanCamera_New(struct QTask_s *ptParent, struct QCamera_s *ptQCamera)
{
  struct QTask_s *v2; // eax
  struct Flow_t *v3; // ecx
  struct QTask_s *v4; // esi
  struct LevelFlow_s *v5; // eax
  float nFrameNumber; // [esp+0h] [ebp-10h]

  v2 = QTask_NewFn(ptParent, HumanCamera_eQTaskType, nullptr);
  v3 = Flow_ptFlow;
  v4 = v2;
  v5 = LevelFlow_ptLevelFlow;
  v4[2].tQTaskRefList.ptTail = (struct QReference_s *)ptQCamera;
  nFrameNumber = (double)v5->nTimeOfDayTick / ((double)v3->nFrequency * 3600.0) + v5->vStartTime;
  QCamera_Set(
    ptQCamera,
    (struct real64x3_t *)&v4[1],
    (struct real32x9_t *)&v4[1].tQTaskRefList.ptMiddle,
    *(float *)&v4[2].tQTaskRefList.ptMiddle,
    1.0,
    300.0,
    Screen_nFrameNumber,
    v4,
    nFrameNumber,
    0);
  return v4;
}

// source: j/0/cameras/humancamera.c:2238  [anchor-callee]
void __cdecl HumanCamera_SetHumanQTask(struct QTask_s *ptHumanCameraQTask, struct QTask_s *ptHumanQTask)
{
  struct QTask_s *ptParent; // eax
  struct QTask_s *ptTail; // eax
  int v4; // esi
  struct QReference_s *ptHumanQTaskRef; // eax
  struct QTask_s *pxObject; // ebp
  struct QTask_s *v7; // eax

  ptHumanCameraQTask[10].ptNext = (struct QTask_s *)-1;
  ptParent = ptHumanCameraQTask[2].ptParent;
  if ( ptParent )
  {
    QReference_Delete((struct QReference_s *)ptParent, &QTask_tQTaskRefPool);
    ptHumanCameraQTask[2].ptParent = nullptr;
  }
  ptTail = ptHumanCameraQTask[7].tQTaskChildren.ptTail;
  if ( ptTail )
  {
    QReference_Delete((struct QReference_s *)ptTail, &QTask_tQTaskRefPool);
    ptHumanCameraQTask[7].tQTaskChildren.ptTail = nullptr;
  }
  v4 = 0;
  while ( 1 )
  {
    if ( HumanCamera_atHumanList[v4].isUsed )
    {
      ptHumanQTaskRef = HumanCamera_atHumanList[v4].ptHumanQTaskRef;
      pxObject = (struct QTask_s *)ptHumanQTaskRef->pxObject;
      if ( pxObject == ptHumanQTask )
        break;
    }
    if ( ++v4 >= 128 )
    {
      LDebug_Error("ERROR IN HUMANCAMERA HUMANLIST");
      abort();
    }
  }
  ptHumanCameraQTask[2].ptParent = (struct QTask_s *)QTask_NewQTaskRef((struct QTask_s *)ptHumanQTaskRef->pxObject);
  v7 = (struct QTask_s *)QTask_NewQTaskRef(pxObject);
  ptHumanCameraQTask[7].tQTaskChildren.ptHead = (struct QTask_s *)v4;
  ptHumanCameraQTask[7].tQTaskChildren.ptMiddle = (struct QTask_s *)v4;
  ptHumanCameraQTask[7].tQTaskChildren.ptTail = v7;
}

// source: j/0/cameras/humancamera.c:2290  [anchor-mhash]
void __cdecl HumanCamera_RegisterHumanInCameraList(struct QTask_s *ptHumanQTask)
{
  int v1; // esi

  v1 = 0;
  while ( HumanCamera_atHumanList[v1].isUsed )
  {
    if ( ++v1 >= 128 )
      return;
  }
  HumanCamera_atHumanList[v1].ptHumanQTaskRef = QTask_NewQTaskRef(ptHumanQTask);
  HumanCamera_atHumanList[v1].isUsed = 1;
}

// source: j/0/cameras/humancamera.c:2315  [anchor-callee]
void __cdecl HumanCamera_RemoveHumanFromCameraList(struct QTask_s *ptHumanQTask)
{
  int v1; // esi
  struct QTask_s *pxObject; // eax
  struct QReference_s *ptHumanQTaskRef; // eax

  v1 = 0;
  while ( 1 )
  {
    if ( HumanCamera_atHumanList[v1].isUsed )
    {
      pxObject = (struct QTask_s *)HumanCamera_atHumanList[v1].ptHumanQTaskRef->pxObject;
      if ( !pxObject )
      {
        LDebug_Error("ERROR IN HUMANCAMERA HUMANLIST");
        abort();
      }
      if ( pxObject == ptHumanQTask )
        break;
    }
    if ( ++v1 >= 128 )
      return;
  }
  ptHumanQTaskRef = HumanCamera_atHumanList[v1].ptHumanQTaskRef;
  if ( ptHumanQTaskRef )
  {
    QReference_Delete(ptHumanQTaskRef, &QTask_tQTaskRefPool);
    HumanCamera_atHumanList[v1].ptHumanQTaskRef = nullptr;
  }
  HumanCamera_atHumanList[v1].isUsed = 0;
}
