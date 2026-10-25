/* j/0/computer/computermap.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/computer/computermap.c:104  [anchor-mhash]
int __cdecl ComputerMap_LoadBarsCallback(struct QTask_s *ptQTask, int nBar)
{
  int v2; // eax
  int result; // eax

  if ( !nBar )
  {
    ptQTask[4].ptPrev[1].ptNext = (struct QTask_s *)4;
    goto LABEL_6;
  }
  v2 = nBar - 1;
  if ( !v2 )
  {
LABEL_6:
    result = (int)ptQTask[4].ptPrev;
    *(_DWORD *)(result + 40) = 21;
    return result;
  }
  result = v2 - 1;
  if ( !result )
  {
    result = (int)ptQTask[4].ptPrev;
    *(_DWORD *)(result + 40) = 31;
  }
  return result;
}

// source: j/0/computer/computermap.c:145  [size]
struct ComputerMap_s *__cdecl ComputerMap_SetNoise(
        struct ComputerMap_s *ptComputerMap,
        float vNoise,
        int nTime)
{
  ptComputerMap->nNoiseTimer = nTime;
  ptComputerMap->vNoise = vNoise;
  return ptComputerMap;
}

// source: j/0/computer/computermap.c:159  [anchor-mhash]
void __cdecl ComputerMap_SetFOV(struct ComputerMap_s *ptComputerMap, float vFOV)
{
  if ( vFOV != ptComputerMap->vFOV )
    ptComputerMap->vFOV = vFOV;
}

// source: j/0/computer/computermap.c:176  [anchor-hash]
void __cdecl ComputerMap_PlayZoomSound(struct ComputerMap_s *ptComputerMap)
{
  struct Game_s *v1; // eax
  unsigned int v2; // ecx
  int v3; // ecx
  double v4; // st7
  int v5; // ecx
  int v6; // edx
  unsigned int v7; // edx

  v1 = Game_ptGame;
  v2 = (Game_ptGame->tRunRandomState.anRandom[0] >> 7) ^ Game_ptGame->tRunRandomState.anRandom[2];
  Game_ptGame->tRunRandomState.anRandom[2] = v2;
  v3 = v2 ^ v1->tRunRandomState.anRandom[1];
  v1->tRunRandomState.anRandom[1] = v3;
  v4 = (double)(unsigned __int16)(v3 + LOWORD(v1->tRunRandomState.anRandom[0]));
  v1->tRunRandomState.anRandom[0] += v3;
  v5 = (v1->tRunRandomState.anRandom[0] >> 7) ^ v1->tRunRandomState.anRandom[2];
  v6 = v5 ^ v1->tRunRandomState.anRandom[1];
  v1->tRunRandomState.anRandom[2] = v5;
  v1->tRunRandomState.anRandom[1] = v6;
  v7 = v6 + v1->tRunRandomState.anRandom[0];
  v1->tRunRandomState.anRandom[0] = v7;
  ptComputerMap->vNoise = v4 * 0.0000152587890625 * 0.05000000074505806 + 0.949999988079071;
  ptComputerMap->nNoiseTimer = v7 % 0x4B + 15;
  SoundSys_PlaySimpleSoundDefFn("mapcomp_03", 1u, nullptr);
}

// source: j/0/computer/computermap.c:204  [anchor-callee]
char __cdecl ComputerMap_CheckCameraPosAgainstLimit(
        struct ComputerMap_s *ptComputerMap,
        struct real64x3_t *ptPos)
{
  struct QTask_s *v2; // eax
  double v3; // st7
  double v4; // st6
  char result; // al
  double v6; // [esp+0h] [ebp-20h]
  double tDelta_8; // [esp+10h] [ebp-10h]

  if ( DefineComputerLimit_ptQTask )
    v2 = DefineComputerLimit_ptQTask + 1;
  else
    v2 = nullptr;
  result = true;
  if ( v2 )
  {
    v3 = *(float *)&v2->tQTaskRefList.ptMiddle * 0.5 * 4096.0;
    v4 = ptPos->vX - *(double *)&v2->ptNext;
    tDelta_8 = ptPos->vY - *(double *)&v2->tQTaskChildren.ptHead;
    v6 = -v3;
    if ( v4 < v6 || v4 > v3 || tDelta_8 < v6 || tDelta_8 > v3 )
      return false;
  }
  return result;
}

// source: j/0/computer/computermap.c:245  [anchor-callee]
void __cdecl ComputerMap_ClipCameraPosAgainstLimit(struct ComputerMap_s *ptComputerMap)
{
  double *v1; // ecx
  double v2; // st7
  double v3; // st6
  double vSize; // [esp+0h] [ebp-28h]
  double tDelta; // [esp+10h] [ebp-18h]
  double tDelta_16; // [esp+20h] [ebp-8h]

  if ( DefineComputerLimit_ptQTask )
  {
    v1 = (double *)&DefineComputerLimit_ptQTask[1];
    if ( DefineComputerLimit_ptQTask != (struct QTask_s *)-40 )
    {
      vSize = *(float *)&DefineComputerLimit_ptQTask[1].tQTaskRefList.ptMiddle * 0.5 * 4096.0;
      tDelta = ComputerMap_tPos.vX - *v1;
      v2 = ComputerMap_tPos.vY - *(double *)&DefineComputerLimit_ptQTask[1].tQTaskChildren.ptHead;
      tDelta_16 = ComputerMap_tPos.vZ - *(double *)&DefineComputerLimit_ptQTask[1].tQTaskChildren.ptTail;
      v3 = -vSize;
      if ( tDelta < -vSize )
        tDelta = v3;
      if ( tDelta > vSize )
        tDelta = *(float *)&DefineComputerLimit_ptQTask[1].tQTaskRefList.ptMiddle * 0.5 * 4096.0;
      if ( v2 < v3 )
        v2 = -vSize;
      if ( v2 > vSize )
        v2 = vSize;
      ComputerMap_tPos.vX = tDelta + *v1;
      ComputerMap_tPos.vY = v2 + *(double *)&DefineComputerLimit_ptQTask[1].tQTaskChildren.ptHead;
      ComputerMap_tPos.vZ = tDelta_16 + *(double *)&DefineComputerLimit_ptQTask[1].tQTaskChildren.ptTail;
    }
  }
}

// source: j/0/computer/computermap.c:293  [anchor-callee]
struct real64x3_t *__cdecl ComputerMap_SetCameraPosFromWorldPos(
        struct QTask_s *ptQTask,
        struct real64x3_t *ptPos)
{
  double v2; // st6
  float tY; // [esp+0h] [ebp-Ch]
  struct QReference_s *tY_8; // [esp+8h] [ebp-4h]

  v2 = *(float *)&ptQTask[2].tQTaskChildren.ptTail;
  tY_8 = ptQTask[2].tQTaskRefList.ptTail;
  tY = *(float *)&ptQTask[2].ptPrev * -921600.0;
  ComputerMap_tPos.vX = tY + ptPos->vX;
  ComputerMap_tPos.vY = v2 * -921600.0 + ptPos->vY;
  ComputerMap_tPos.vZ = *(float *)&tY_8 * -921600.0 + ptPos->vZ;
  return ptPos;
}

// source: j/0/computer/computermap.c:314  [anchor-callee]
void __cdecl ComputerMap_SetCameraPosRelativeToTerrain(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct World_s *ptWorld; };
    struct { char igi2_o1[32]; double vGetNextZDistance; };
    struct { char igi2_o2[40]; struct QIntersection_s tIntersection; };
    char igi2_extent[160];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  igi2_frame.ptWorld = Game_ptGame->ptWorld;
  igi2_frame.vGetNextZDistance = -1843200.0;
  World_GetNextZ(igi2_frame.ptWorld, &igi2_frame.tIntersection, &ComputerMap_tPos, 1, &igi2_frame.vGetNextZDistance, 512, nullptr, 0x80000000);
  if ( igi2_frame.tIntersection.isHit )
    ComputerMap_SetCameraPosFromWorldPos(ptQTask, &igi2_frame.tIntersection.tPos);
}

// source: j/0/computer/computermap.c:357  [anchor-callee]
void __cdecl ComputerMap_SetCameraPosFromTask(struct QTask_s *ptQTask, struct QTask_s *ptFollowQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v4; };
    struct { char igi2_o1[8]; struct QReference_s *ptTail; };
    struct { char igi2_o2[12]; struct GetCameraTargetInfoContext_s tGetCameraTargetInfoContext; };
    char igi2_extent[104];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int eQTaskType; // eax
  double v3; // st7

  if ( ComputerMap_tLastPos.vX == 0.0 && ComputerMap_tLastPos.vY == 0.0 && ComputerMap_tLastPos.vZ == 0.0
    || ComputerMap_ptPositionQTask )
  {
    eQTaskType = ptFollowQTask->eQTaskType;
    igi2_frame.tGetCameraTargetInfoContext.zName = nullptr;
    ((void (__cdecl *)(struct QTask_s *, struct GetCameraTargetInfoContext_s *))QTask_aatQTaskFinalEvent[8][eQTaskType].pfHandler)(
      ptFollowQTask,
      &igi2_frame.tGetCameraTargetInfoContext);
    igi2_frame.ptTail = ptQTask[2].tQTaskRefList.ptTail;
    v3 = *(float *)&ptQTask[2].tQTaskChildren.ptTail;
    igi2_frame.v4 = *(float *)&ptQTask[2].ptPrev * -921600.0;
    ComputerMap_tPos.vX = igi2_frame.v4 + igi2_frame.tGetCameraTargetInfoContext.tPos.vX;
    ComputerMap_tPos.vY = v3 * -921600.0 + igi2_frame.tGetCameraTargetInfoContext.tPos.vY;
    ComputerMap_tPos.vZ = *(float *)&igi2_frame.ptTail * -921600.0 + igi2_frame.tGetCameraTargetInfoContext.tPos.vZ;
  }
  else
  {
    ComputerMap_SetCameraPosFromWorldPos(ptQTask, &ComputerMap_tLastPos);
  }
}

// source: j/0/computer/computermap.c:389  [anchor-hash]
void __cdecl ComputerMap_DeleteFollowQTaskRef(struct ComputerMap_s *ptComputerMap)
{
  struct QReference_s *ptFollowQTaskRef; // eax

  ptFollowQTaskRef = ptComputerMap->ptFollowQTaskRef;
  if ( ptFollowQTaskRef )
  {
    QReference_Delete(ptFollowQTaskRef, &QTask_tQTaskRefPool);
    ptComputerMap->ptFollowQTaskRef = nullptr;
  }
}

// source: j/0/computer/computermap.c:406  [anchor-callee]
void __cdecl ComputerMap_SetFollowQTaskRef(struct ComputerMap_s *ptComputerMap, struct QTask_s *ptQTask)
{
  int v2; // ecx
  struct QReference_s *ptFollowQTaskRef; // eax
  int eQTaskType; // eax
  void (__cdecl *pfHandler)(struct QTask_s *, struct ComputerMapFollowQTaskContext_s *); // eax
  struct ComputerMapFollowQTaskContext_s tContext; // [esp+1h] [ebp-1h] BYREF

  tContext.isFollow = HIBYTE(v2);
  ptFollowQTaskRef = ptComputerMap->ptFollowQTaskRef;
  if ( ptFollowQTaskRef )
  {
    QReference_Delete(ptFollowQTaskRef, &QTask_tQTaskRefPool);
    ptComputerMap->ptFollowQTaskRef = nullptr;
  }
  eQTaskType = ptQTask->eQTaskType;
  if ( QTask_aatQTaskFinalEvent[8][eQTaskType].pfHandler )
  {
    pfHandler = (void (__cdecl *)(struct QTask_s *, struct ComputerMapFollowQTaskContext_s *))QTask_aatQTaskFinalEvent[ComputerMap_eFollowQTaskEvent][eQTaskType].pfHandler;
    if ( pfHandler )
    {
      pfHandler(ptQTask, &tContext);
      if ( tContext.isFollow )
        ptComputerMap->ptFollowQTaskRef = QTask_NewQTaskRef(ptQTask);
    }
  }
}

// source: j/0/computer/computermap.c:433  [size]
float __cdecl ComputerMap_SetZoomDelta(float vIdealFOV, float vRealFOV)
{
  return (vIdealFOV - vRealFOV) * 0.3333333432674408;
}

// source: j/0/computer/computermap.c:446  [anchor-strings]
void __cdecl ComputerMap_Trace(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char isPlayScrollSound; };
    struct { char igi2_o1[1]; char isCenterCamera; };
    struct { char igi2_o2[2]; enum bool isZoomIn; };
    struct { char igi2_o3[9]; char isTrace; };
    struct { char igi2_o4[10]; enum bool isZoomOut; };
    struct { char igi2_o5[14]; struct real64x3_t tViewVector; };
    struct { char igi2_o6[38]; struct ComputerMenu_t *ptComputerMenu; };
    struct { char igi2_o7[42]; struct QCamera_s *ptQCamera; };
    struct { char igi2_o8[46]; struct real64x3_t bEdgeButton; };
    struct { char igi2_o9[70]; unsigned __int64 tReal64x3_8; };
    struct { char igi2_o10[78]; __int64 tReal64x3_16; };
    struct { char igi2_o11[86]; struct real64x3_t tStop; };
    struct { char igi2_o12[110]; struct QIntersection_s tGetCameraTargetInfoContext; };
    char igi2_extent[230];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct ComputerMenu_t *ptHead; // edx
  struct QTask_s *v2; // edi
  BOOL v3; // ebx
  struct QTask_s *ptParent; // eax
  struct QTask_s *v5; // eax
  struct QTask_s *v6; // eax
  struct QTask_s *v7; // eax
  long double v8; // st7
  struct QTask_s *ptNext; // eax
  struct QTask_s *v10; // eax
  double v11; // st7
  double v12; // st6
  struct QReference_s *ptPrev; // ecx
  long double v14; // st7
  struct QTask_s *v15; // eax
  struct QTask_s *v16; // eax
  struct QTask_s *v17; // eax
  int v18; // edi
  struct QTask_s *v19; // eax
  struct QTask_s *v20; // eax
  struct QReference_s *v21; // eax
  unsigned __int16 *pxObject; // ecx
  int v23; // edx
  struct QTask_s *v24; // ecx
  double v25; // st7
  double v26; // st6
  double v27; // st6
  struct QCamera_s *v28; // eax
  long double v29; // st7
  struct QTask_s *ptTail; // eax
  struct QReference_s *v31; // eax
  struct QReference_s *v32; // eax
  struct QTask_s *v33; // ecx
  bool v34; // c0
  float *p_tQTaskRefList; // ecx
  struct Game_s *v36; // edx
  float *v37; // eax
  double v38; // st7
  struct QTaskList_s *v39; // ebx
  double v40; // st7
  enum bool nTask; // edx
  bool v42; // cc
  struct QTask_s **v43; // ebx
  double v44; // st7
  struct QTask_s *v45; // eax
  double v46; // st6
  double v47; // st5
  double v48; // st4
  double v49; // st3
  enum bool v50; // ebx
  __int32 v51; // ebx
  int v52; // edx
  unsigned int v53; // eax
  int v54; // ebx
  double v55; // st7
  int v56; // edx
  double v57; // st6
  double v58; // st5
  struct QTask_s *v59; // eax
  struct QTask_s *v60; // eax
  struct QTask_s *v61; // eax
  struct QTask_s *v62; // esi
  int v63; // eax

  igi2_frame.tReal64x3_8 = InputPort_atInputPort[0].tInput.bEdgeButton;
  ptHead = (struct ComputerMenu_t *)Game_ptGame->ptGameScreenQTask[1].ptPrev[2].tQTaskChildren.ptHead;
  v2 = ComputerMenu_ptComputerMenuQTask;
  igi2_frame.ptQCamera = (struct QCamera_s *)ComputerMenu_ptComputerMenuQTask;
  igi2_frame.isPlayScrollSound = 0;
  igi2_frame.isTrace = 0;
  igi2_frame.isCenterCamera = 0;
  igi2_frame.ptComputerMenu = ptHead;
  *(float *)&igi2_frame.isZoomIn = 0.0;
  *(float *)&igi2_frame.isZoomOut = 0.0;
  v3 = (Keyboard_tKeyboard.anCurrentKey[157] & 0x80u) != 0 || (Keyboard_tKeyboard.anCurrentKey[29] & 0x80u) != 0;
  igi2_frame.bEdgeButton.vX = 0.0;
  if ( (Keyboard_tKeyboard.anCurrentKey[200] & 0x80u) != 0 && v3 )
  {
    ptParent = ptQTask[3].ptParent;
    if ( ptParent )
    {
      QReference_Delete((struct QReference_s *)ptParent, &QTask_tQTaskRefPool);
      ptQTask[3].ptParent = nullptr;
    }
    HIDWORD(igi2_frame.bEdgeButton.vX) = 1188386133;
    igi2_frame.isPlayScrollSound = 1;
  }
  if ( (Keyboard_tKeyboard.anCurrentKey[208] & 0x80u) != 0 && v3 )
  {
    v5 = ptQTask[3].ptParent;
    if ( v5 )
    {
      QReference_Delete((struct QReference_s *)v5, &QTask_tQTaskRefPool);
      ptQTask[3].ptParent = nullptr;
    }
    igi2_frame.isPlayScrollSound = 1;
    *((float *)&igi2_frame.bEdgeButton.vX + 1) = *((float *)&igi2_frame.bEdgeButton.vX + 1) - 27306.666015625;
  }
  if ( (Keyboard_tKeyboard.anCurrentKey[203] & 0x80u) != 0 && v3 )
  {
    v6 = ptQTask[3].ptParent;
    if ( v6 )
    {
      QReference_Delete((struct QReference_s *)v6, &QTask_tQTaskRefPool);
      ptQTask[3].ptParent = nullptr;
    }
    LODWORD(igi2_frame.bEdgeButton.vX) = -959097515;
    igi2_frame.isPlayScrollSound = 1;
  }
  if ( (Keyboard_tKeyboard.anCurrentKey[205] & 0x80u) != 0 && v3 )
  {
    v7 = ptQTask[3].ptParent;
    if ( v7 )
    {
      QReference_Delete((struct QReference_s *)v7, &QTask_tQTaskRefPool);
      ptQTask[3].ptParent = nullptr;
    }
    igi2_frame.isPlayScrollSound = 1;
    *(float *)&igi2_frame.bEdgeButton.vX = *(float *)&igi2_frame.bEdgeButton.vX + 27306.666015625;
  }
  v8 = pow(*(float *)&ptQTask[3].ptNext, 0.699999988079071);
  *((float *)&igi2_frame.bEdgeButton.vX + 1) = v8 * *((float *)&igi2_frame.bEdgeButton.vX + 1);
  *(float *)&igi2_frame.bEdgeButton.vY = v8 * 0.0;
  ComputerMap_tPos.vX = *(float *)&igi2_frame.bEdgeButton.vX * v8 + ComputerMap_tPos.vX;
  ComputerMap_tPos.vY = *((float *)&igi2_frame.bEdgeButton.vX + 1) + ComputerMap_tPos.vY;
  ComputerMap_tPos.vZ = *(float *)&igi2_frame.bEdgeButton.vY + ComputerMap_tPos.vZ;
  if ( (Mouse_tMouse.bButton & 1) == 0
    || ((ptNext = ComputerMenu_ptComputerMenuQTask[1].ptNext) == nullptr
      ? (v10 = nullptr)
      : (v10 = ptNext->tQTaskChildren.ptHead),
        memset(&igi2_frame.tViewVector, 0, 12),
        MenuItem_Enumerate(
          v10,
          (void (__cdecl *)(struct MenuItem_s *, void *))MenuItem_ActiveMenuItemCallback,
          &igi2_frame.tViewVector),
        HIDWORD(igi2_frame.tViewVector.vX)) )
  {
    LOBYTE(v2[1].tQTaskChildren.ptMiddle) = 0;
  }
  else
  {
    v11 = ComputerMenu_vMouseSpeedX;
    v12 = ComputerMenu_vMouseSpeedY;
    igi2_frame.isPlayScrollSound = 1;
    if ( !LOBYTE(v2[1].tQTaskChildren.ptMiddle) )
    {
      ptPrev = (struct QReference_s *)v2[1].ptPrev;
      LOBYTE(v2[1].tQTaskChildren.ptMiddle) = 1;
      ptQTask[3].tQTaskRefList.ptMiddle = ptPrev;
      ptQTask[3].tQTaskRefList.ptTail = (struct QReference_s *)v2[1].tQTaskChildren.ptHead;
      igi2_frame.isTrace = 1;
    }
    *(float *)&igi2_frame.tViewVector.vX = -v11 * 819200.0;
    *((float *)&igi2_frame.tViewVector.vX + 1) = v12 * 819200.0;
    v14 = pow(*(float *)&ptQTask[3].ptNext, 0.699999988079071);
    *((float *)&igi2_frame.tViewVector.vX + 1) = v14 * *((float *)&igi2_frame.tViewVector.vX + 1);
    *(float *)&igi2_frame.tViewVector.vY = v14 * 0.0;
    ComputerMap_tPos.vX = *(float *)&igi2_frame.tViewVector.vX * v14 + ComputerMap_tPos.vX;
    ComputerMap_tPos.vY = *((float *)&igi2_frame.tViewVector.vX + 1) + ComputerMap_tPos.vY;
    ComputerMap_tPos.vZ = *(float *)&igi2_frame.tViewVector.vY + ComputerMap_tPos.vZ;
    v15 = ptQTask[3].ptParent;
    if ( v15 )
    {
      QReference_Delete((struct QReference_s *)v15, &QTask_tQTaskRefPool);
      ptQTask[3].ptParent = nullptr;
    }
  }
  if ( ((int)ComputerMenu_ptComputerMenuQTask[1].tQTaskRefList.ptHead & 0x10) != 0 )
  {
    v16 = ComputerMenu_ptComputerMenuQTask[1].ptNext;
    v17 = v16 ? v16->tQTaskChildren.ptHead : nullptr;
    memset(&igi2_frame.tViewVector, 0, 12);
    MenuItem_Enumerate(
      v17,
      (void (__cdecl *)(struct MenuItem_s *, void *))MenuItem_ActiveMenuItemCallback,
      &igi2_frame.tViewVector);
    if ( !HIDWORD(igi2_frame.tViewVector.vX) )
    {
      if ( ptQTask[3].tQTaskChildren.ptTail )
      {
        igi2_frame.isZoomIn = true;
        ptQTask[3].tQTaskChildren.ptTail = nullptr;
      }
      else
      {
        ptQTask[3].tQTaskChildren.ptTail = (struct QTask_s *)13;
      }
    }
  }
  v18 = igi2_frame.tReal64x3_8;
  if ( (igi2_frame.tReal64x3_8 & 0x2000000) != 0 )
    igi2_frame.isZoomIn = true;
  if ( ((int)ComputerMenu_ptComputerMenuQTask[1].tQTaskRefList.ptHead & 0x20) != 0 )
  {
    v19 = ComputerMenu_ptComputerMenuQTask[1].ptNext;
    v20 = v19 ? v19->tQTaskChildren.ptHead : nullptr;
    memset(&igi2_frame.tViewVector, 0, 12);
    MenuItem_Enumerate(
      v20,
      (void (__cdecl *)(struct MenuItem_s *, void *))MenuItem_ActiveMenuItemCallback,
      &igi2_frame.tViewVector);
    if ( !HIDWORD(igi2_frame.tViewVector.vX) )
    {
      if ( ptQTask[3].tQTaskRefList.ptHead )
      {
        igi2_frame.isZoomOut = true;
        ptQTask[3].tQTaskRefList.ptHead = nullptr;
      }
      else
      {
        ptQTask[3].tQTaskRefList.ptHead = (struct QReference_s *)13;
      }
    }
  }
  if ( (v18 & 0x4000000) != 0 )
    igi2_frame.isZoomOut = true;
  if ( (Keyboard_tKeyboard.anCurrentKey[199] & 0x80u) != 0
    && (Keyboard_tKeyboard.anPreviousKey[199] & 0x80u) == 0
    && ComputerMap_ptPositionQTask )
  {
    ComputerMap_tLastPos.vX = 0.0;
    ComputerMap_tLastPos.vY = 0.0;
    ComputerMap_tLastPos.vZ = 0.0;
    ComputerMap_SetCameraPosFromTask(ptQTask, ComputerMap_ptPositionQTask);
  }
  v21 = (struct QReference_s *)ptQTask[3].ptParent;
  if ( v21 )
  {
    pxObject = (unsigned __int16 *)v21->pxObject;
    if ( !pxObject )
    {
      QReference_Delete(v21, &QTask_tQTaskRefPool);
      v24 = ComputerMenu_ptComputerMenuQTask;
      ptQTask[3].ptParent = nullptr;
      ComputerMap_tTargetPos.vX = 0.0;
      ComputerMap_tTargetPos.vY = 0.0;
      ComputerMap_tTargetPos.vZ = 0.0;
      goto LABEL_74;
    }
    v23 = pxObject[18];
    igi2_frame.tGetCameraTargetInfoContext.ptEnterMaterial = nullptr;
    ((void (__cdecl *)(unsigned __int16 *, struct QIntersection_s *))QTask_aatQTaskFinalEvent[8][v23].pfHandler)(
      pxObject,
      &igi2_frame.tGetCameraTargetInfoContext);
    qmemcpy(&ComputerMap_tTargetPos, &igi2_frame.tGetCameraTargetInfoContext, sizeof(ComputerMap_tTargetPos));
  }
  v24 = ComputerMenu_ptComputerMenuQTask;
  if ( ComputerMap_tTargetPos.vX != 0.0 || ComputerMap_tTargetPos.vY != 0.0 || ComputerMap_tTargetPos.vZ != 0.0 )
  {
    v25 = ComputerMap_tTargetPos.vX - *(double *)&igi2_frame.ptComputerMenu->ptMenuItemQTask;
    *((float *)&igi2_frame.bEdgeButton.vX + 1) = ComputerMap_tTargetPos.vY - *(double *)&igi2_frame.ptComputerMenu->tMousePos.vY;
    v26 = v25;
    if ( v25 < 0.0 )
      v26 = -v25;
    if ( v26 > 409.6000061035156 )
      goto LABEL_73;
    v27 = *((float *)&igi2_frame.bEdgeButton.vX + 1);
    if ( *((float *)&igi2_frame.bEdgeButton.vX + 1) < 0.0 )
      v27 = -v27;
    if ( v27 > 409.6000061035156 )
    {
LABEL_73:
      ComputerMap_tPos.vX = v25 * 0.3333333432674408 + ComputerMap_tPos.vX;
      ComputerMap_tPos.vY = *((float *)&igi2_frame.bEdgeButton.vX + 1) * 0.3333333432674408 + ComputerMap_tPos.vY;
    }
    else
    {
      ComputerMap_tTargetPos.vX = 0.0;
      ComputerMap_tTargetPos.vY = 0.0;
      ComputerMap_tTargetPos.vZ = 0.0;
    }
  }
LABEL_74:
  if ( (Mouse_tMouse.bButton & 0x100) != 0 && ((int)ptQTask[4].tQTaskChildren.ptMiddle & 0x100) == 0
    || *(float *)&igi2_frame.isZoomIn != 0.0 )
  {
    ptQTask[3].tQTaskRefList.ptMiddle = (struct QReference_s *)v24[1].ptPrev;
    ptQTask[3].tQTaskRefList.ptTail = (struct QReference_s *)v24[1].tQTaskChildren.ptHead;
    igi2_frame.isTrace = 1;
    igi2_frame.isCenterCamera = 1;
    *(float *)&v24[1].ptPrev = (double)Display_tActiveMode.nWidth * 0.5;
    *(float *)&v24[1].tQTaskChildren.ptHead = (double)Display_tActiveMode.nHeight * 0.5;
    if ( (unsigned __int16)ComputerMap_nZoomLevel < 3u )
    {
      ++ComputerMap_nZoomLevel;
      ComputerMap_PlayZoomSound((struct ComputerMap_s *)ptQTask);
    }
  }
  if ( ((Mouse_tMouse.bButton & 0x200) != 0 && ((int)ptQTask[4].tQTaskChildren.ptMiddle & 0x200) == 0
     || *(float *)&igi2_frame.isZoomOut != 0.0)
    && ComputerMap_nZoomLevel )
  {
    --ComputerMap_nZoomLevel;
    ComputerMap_PlayZoomSound((struct ComputerMap_s *)ptQTask);
    v28 = igi2_frame.ptQCamera;
    *((float *)&igi2_frame.ptQCamera->tPos.vX + 1) = (double)Display_tActiveMode.nWidth * 0.5;
    *(float *)&v28->tPos.vY = (double)Display_tActiveMode.nHeight * 0.5;
  }
  v29 = (tan(ComputerMap_avZoomLevel[ComputerMap_nZoomLevel]) - *(float *)&ptQTask[3].ptNext) * 0.3333333432674408
      + *(float *)&ptQTask[3].ptNext;
  if ( v29 != *(float *)&ptQTask[3].ptNext )
    *(float *)&ptQTask[3].ptNext = v29;
  ptTail = ptQTask[3].tQTaskChildren.ptTail;
  if ( (int)ptTail > 0 )
    ptQTask[3].tQTaskChildren.ptTail = (struct QTask_s *)((char *)ptTail - 1);
  v31 = ptQTask[3].tQTaskRefList.ptHead;
  if ( (int)v31 > 0 )
    ptQTask[3].tQTaskRefList.ptHead = (struct QReference_s *)((char *)v31 - 1);
  if ( !igi2_frame.isTrace )
    goto LABEL_129;
  v32 = ptQTask[3].tQTaskRefList.ptTail;
  igi2_frame.isZoomOut = (enum bool)ptQTask[3].tQTaskRefList.ptMiddle;
  v33 = Game_ptGame->ptGameScreenQTask[1].ptPrev;
  v34 = *(float *)&igi2_frame.isZoomOut < (double)*(float *)&v33[1].tQTaskRefList.ptHead;
  p_tQTaskRefList = (float *)&v33[1].tQTaskRefList;
  igi2_frame.isZoomIn = (enum bool)v32;
  if ( v34
    || *(float *)&igi2_frame.isZoomIn < (double)p_tQTaskRefList[1]
    || p_tQTaskRefList[2] + *p_tQTaskRefList <= *(float *)&igi2_frame.isZoomOut
    || p_tQTaskRefList[3] + p_tQTaskRefList[1] <= *(float *)&igi2_frame.isZoomIn )
  {
    goto LABEL_129;
  }
  v36 = Game_ptGame;
  v37 = (float *)Game_ptGame->ptGameScreenQTask[1].ptPrev[2].tQTaskChildren.ptHead;
  *(double *)&igi2_frame.tReal64x3_8 = (double)Display_tActiveMode.nWidth;
  igi2_frame.tViewVector.vX = (*(float *)&igi2_frame.isZoomOut + *(float *)&igi2_frame.isZoomOut - *(double *)&igi2_frame.tReal64x3_8)
                 * v37[16]
                 / *(double *)&igi2_frame.tReal64x3_8;
  v38 = Display_GetAspectRatio() * v37[16];
  igi2_frame.isZoomOut = (enum bool)Mine_ptMineQTaskList;
  v39 = Human_ptQTaskList;
  v40 = v38
      * (*(float *)&igi2_frame.isZoomIn + *(float *)&igi2_frame.isZoomIn - (double)Display_tActiveMode.nHeight)
      / *(double *)&igi2_frame.tReal64x3_8;
  LODWORD(igi2_frame.tReal64x3_8) = SCamera_ptSCameraLensQTaskList;
  igi2_frame.ptQCamera = nullptr;
  igi2_frame.tReal64x3_16 = 0;
  igi2_frame.ptComputerMenu = nullptr;
  qmemcpy(&igi2_frame.bEdgeButton, v37 + 10, sizeof(igi2_frame.bEdgeButton));
  igi2_frame.tStop.vX = v37[1] * v40 + *v37 * igi2_frame.tViewVector.vX + v37[2];
  igi2_frame.tStop.vY = v37[4] * v40 + v37[3] * igi2_frame.tViewVector.vX + v37[5];
  igi2_frame.tStop.vZ = v37[7] * v40 + v37[6] * igi2_frame.tViewVector.vX + v37[8];
  qmemcpy(&igi2_frame.tViewVector, &igi2_frame.tStop, sizeof(igi2_frame.tViewVector));
  Real64x3_Normalize(&igi2_frame.tViewVector);
  igi2_frame.tViewVector.vZ = igi2_frame.tViewVector.vZ * 4096000.0;
  igi2_frame.tStop.vX = igi2_frame.bEdgeButton.vX + igi2_frame.tViewVector.vX * 4096000.0;
  igi2_frame.tStop.vY = igi2_frame.bEdgeButton.vY + igi2_frame.tViewVector.vY * 4096000.0;
  igi2_frame.tStop.vZ = igi2_frame.bEdgeButton.vZ + igi2_frame.tViewVector.vZ;
  World_TraceLines(v36->ptWorld, &igi2_frame.tGetCameraTargetInfoContext, &igi2_frame.bEdgeButton, &igi2_frame.tStop, 1, 512, nullptr, 0xFFFFFFFF);
  qmemcpy(&ComputerMap_tLockPos, &igi2_frame.tGetCameraTargetInfoContext.tPos, sizeof(ComputerMap_tLockPos));
  nTask = v39->nTask;
  v42 = v39->nTask <= 0;
  *(float *)&igi2_frame.isZoomIn = 0.0;
  if ( !v42 )
  {
    v43 = v39->ptQTask;
    v44 = *(float *)&ptQTask[3].ptNext * 167772160.0;
    while ( 1 )
    {
      v45 = *v43;
      v46 = *(double *)&(*v43)[1].tQTaskChildren.ptTail;
      v47 = *(double *)&(*v43)[1].ptNext;
      qmemcpy(&igi2_frame.tViewVector, &igi2_frame.tGetCameraTargetInfoContext.tPos, sizeof(igi2_frame.tViewVector));
      v48 = *(double *)&v45[1].tQTaskChildren.ptHead - igi2_frame.tViewVector.vY;
      v49 = *(double *)&v45[1].tQTaskChildren.ptTail - v46;
      igi2_frame.ptComputerMenu = (struct ComputerMenu_t *)v45;
      if ( v49 * v49 + v48 * v48 + (v47 - igi2_frame.tViewVector.vX) * (v47 - igi2_frame.tViewVector.vX) < v44 )
        break;
      ++v43;
      if ( ++igi2_frame.isZoomIn >= nTask )
        goto LABEL_101;
    }
    igi2_frame.ptQCamera = (struct QCamera_s *)1;
  }
LABEL_101:
  if ( Game_eGameMode == GAME_GAMEMODE_SINGLEPLAYER )
  {
    if ( (Mouse_tMouse.bButton & 1) != 0 )
    {
      v50 = igi2_frame.isZoomOut;
      v42 = (int)(*(_DWORD *)igi2_frame.isZoomOut) <= 0;
      igi2_frame.isZoomOut = *(enum bool *)igi2_frame.isZoomOut;
      *(float *)&igi2_frame.isZoomIn = 0.0;
      if ( !v42 )
      {
        v51 = v50 + 8;
        while ( 1 )
        {
          v52 = *(_DWORD *)v51;
          v53 = *(_DWORD *)(*(_DWORD *)v51 + 56);
          qmemcpy(&igi2_frame.tViewVector, &igi2_frame.tGetCameraTargetInfoContext.tPos, sizeof(igi2_frame.tViewVector));
          *(_QWORD *)&igi2_frame.tViewVector.vZ = __PAIR64__(*(_DWORD *)(v52 + 60), v53);
          if ( *(_BYTE *)(v52 + 646) )
          {
            if ( *(float *)&ptQTask[3].ptNext * 167772160.0 > (*(double *)(v52 + 56) - igi2_frame.tViewVector.vZ)
                                                            * (*(double *)(v52 + 56) - igi2_frame.tViewVector.vZ)
                                                            + (*(double *)(v52 + 48) - igi2_frame.tViewVector.vY)
                                                            * (*(double *)(v52 + 48) - igi2_frame.tViewVector.vY)
                                                            + (*(double *)(v52 + 40) - igi2_frame.tViewVector.vX)
                                                            * (*(double *)(v52 + 40) - igi2_frame.tViewVector.vX) )
              break;
          }
          v51 += 4;
          if ( ++igi2_frame.isZoomIn >= igi2_frame.isZoomOut )
            goto LABEL_111;
        }
        *(_BYTE *)(v52 + 644) = 1;
        *(_DWORD *)(v52 + 632) = 9;
        HIDWORD(igi2_frame.tReal64x3_16) = 1;
      }
    }
    goto LABEL_111;
  }
  if ( Game_eGameMode != GAME_GAMEMODE_MULTIPLAYER )
  {
LABEL_111:
    v42 = (int)(*(_DWORD *)igi2_frame.tReal64x3_8) <= 0;
    igi2_frame.isZoomOut = *(enum bool *)igi2_frame.tReal64x3_8;
    *(float *)&igi2_frame.isZoomIn = 0.0;
    if ( !v42 )
    {
      v54 = igi2_frame.tReal64x3_8 + 8;
      v55 = *(float *)&ptQTask[3].ptNext * 167772160.0;
      while ( 1 )
      {
        v56 = *(_DWORD *)v54;
        v57 = *(double *)(*(_DWORD *)v54 + 56);
        v58 = *(double *)(*(_DWORD *)v54 + 40);
        qmemcpy(&igi2_frame.tViewVector, &igi2_frame.tGetCameraTargetInfoContext.tPos, sizeof(igi2_frame.tViewVector));
        if ( (*(double *)(v56 + 56) - v57) * (*(double *)(v56 + 56) - v57)
           + (*(double *)(v56 + 48) - igi2_frame.tViewVector.vY) * (*(double *)(v56 + 48) - igi2_frame.tViewVector.vY)
           + (v58 - igi2_frame.tViewVector.vX) * (v58 - igi2_frame.tViewVector.vX) < v55 )
          break;
        v54 += 4;
        if ( ++igi2_frame.isZoomIn >= igi2_frame.isZoomOut )
          goto LABEL_117;
      }
      ptQTask[4].tQTaskChildren.ptHead = (struct QTask_s *)v56;
      LODWORD(igi2_frame.tReal64x3_16) = 1;
    }
  }
LABEL_117:
  if ( !igi2_frame.tGetCameraTargetInfoContext.isHit )
    goto LABEL_127;
  if ( !igi2_frame.tReal64x3_16
    && igi2_frame.isCenterCamera
    && ComputerMap_CheckCameraPosAgainstLimit((struct ComputerMap_s *)ptQTask, &igi2_frame.tGetCameraTargetInfoContext.tPos) )
  {
    qmemcpy(&ComputerMap_tTargetPos, &igi2_frame.tGetCameraTargetInfoContext.tPos, sizeof(ComputerMap_tTargetPos));
  }
  if ( igi2_frame.ptQCamera && igi2_frame.isCenterCamera )
  {
    ComputerMap_SetFollowQTaskRef((struct ComputerMap_s *)ptQTask, &igi2_frame.ptComputerMenu->tQTask);
    goto LABEL_129;
  }
  if ( igi2_frame.tGetCameraTargetInfoContext.ptHitObj )
  {
    ComputerMap_SetFollowQTaskRef((struct ComputerMap_s *)ptQTask, &igi2_frame.tGetCameraTargetInfoContext.ptHitObj->tQTask);
  }
  else
  {
LABEL_127:
    v59 = ptQTask[3].ptParent;
    if ( v59 )
    {
      QReference_Delete((struct QReference_s *)v59, &QTask_tQTaskRefPool);
      ptQTask[3].ptParent = nullptr;
    }
  }
LABEL_129:
  if ( igi2_frame.isPlayScrollSound )
  {
    v60 = ptQTask[4].ptNext;
    if ( v60 && v60->tQTaskChildren.ptHead )
    {
      ptQTask[4].tQTaskChildren.ptMiddle = (struct QTask_s *)Mouse_tMouse.bButton;
    }
    else
    {
      v61 = SoundSys_NewSoundFn(Level_ptDynamicQTask, "mapcomp_04");
      v62 = v61;
      if ( v61 )
      {
        v63 = 511 * SoundSys_eSetRelativeToMicrophoneQTaskEvent + v61->eQTaskType;
        igi2_frame.isCenterCamera = 1;
        ((void (__cdecl *)(struct QTask_s *, char *))QTask_aatQTaskFinalEvent[0][v63].pfHandler)(v62, &igi2_frame.isCenterCamera);
        ptQTask[4].ptNext = (struct QTask_s *)QTask_NewQTaskRef(v62);
      }
      ptQTask[4].tQTaskChildren.ptMiddle = (struct QTask_s *)Mouse_tMouse.bButton;
    }
  }
  else
  {
    QTask_DeleteQTaskAndQTaskRefSafe((struct QReference_s **)&ptQTask[4]);
    ptQTask[4].tQTaskChildren.ptMiddle = (struct QTask_s *)Mouse_tMouse.bButton;
  }
}

// source: j/0/computer/computermap.c:968  [anchor-caller]
void __cdecl ComputerMap_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  long double v2; // st7
  struct real32x9_t *v4; // ebx
  struct QCamera_s *p_tQCamera; // edi
  long double v6; // st6
  struct Flow_t *v7; // ecx
  struct LevelFlow_s *v8; // eax
  unsigned __int16 v9; // ax
  struct QTask_s *v10; // eax
  struct QTask_s *ScreenMenuItems; // eax
  struct QTask_s *v12; // edi
  struct QTask_s *v13; // ebx
  struct QTask_s *ptNext; // eax
  float nFrameNumber; // [esp+0h] [ebp-14h]
  float ptQTaska = *(float *)&ptQTask; // [esp+18h] [ebp+4h] ARGSLOT

  v2 = sin(-1.5707963705062866);
  v4 = (struct real32x9_t *)&ptQTask[1];
  p_tQCamera = &Game_ptGame->tQCamera;
  ComputerMap_ptComputerMap = (struct ComputerMap_s *)ptQTask;
  ptQTask[2].ptNext = (struct QTask_s *)1065353216;
  ptQTask[2].ptPrev = nullptr;
  ptQTask[2].tQTaskChildren.ptHead = nullptr;
  ptQTask[2].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[2].tQTaskRefList.ptMiddle = nullptr;
  *(_DWORD *)&ptQTask[2].eQTaskType = 0;
  v6 = cos(-1.5707963705062866);
  *(float *)&ptQTask[2].tQTaskChildren.ptTail = v6;
  *(float *)&ptQTask[2].tQTaskRefList.ptHead = -v2;
  *(float *)&ptQTask[2].tQTaskRefList.ptTail = v2;
  *(float *)&ptQTask[2].ptParent = v6;
  Real32x9_RotateAlpha((struct real32x9_t *)&ptQTask[1], (struct real32x9_t *)&ptQTask[2], -1.5707963705062866);
  if ( ComputerMap_ptPositionQTask )
  {
    ComputerMap_SetCameraPosFromTask(ptQTask, ComputerMap_ptPositionQTask);
    ComputerMap_ptPositionQTask = nullptr;
  }
  v7 = Flow_ptFlow;
  v8 = LevelFlow_ptLevelFlow;
  ptQTaska = tan(ComputerMap_avZoomLevel[ComputerMap_nZoomLevel]);
  *(float *)&ptQTask[3].ptNext = ptQTaska;
  nFrameNumber = (double)v8->nTimeOfDayTick / ((double)v7->nFrequency * 3600.0) + v8->vStartTime;
  QCamera_Set(p_tQCamera, &ComputerMap_tPos, v4, ptQTaska, 1.0, 2000.0, Screen_nFrameNumber, ptQTask, nFrameNumber, 0);
  v9 = ComputerObject_eQTaskType;
  Game_ptGame->ptGameScreenQTask[1].ptPrev[10].tQTaskChildren.ptMiddle = (struct QTask_s *)1;
  ptQTask[3].tQTaskChildren.ptTail = nullptr;
  ptQTask[3].tQTaskRefList.ptHead = nullptr;
  v10 = QTask_NewFn(ptQTask, v9, nullptr);
  v10[1].ptNext = nullptr;
  ptQTask[4].ptPrev = v10;
  ptQTask[3].tQTaskChildren.ptHead = (struct QTask_s *)1065353216;
  ptQTask[3].tQTaskChildren.ptMiddle = (struct QTask_s *)60;
  ScreenMenuItems = ComputerMenu_CreateScreenMenuItems(nullptr, nullptr, ptQTask, COMPUTERMENU_MAP);
  v12 = ComputerMenu_ptComputerMenuQTask + 1;
  v13 = ScreenMenuItems;
  ptNext = ComputerMenu_ptComputerMenuQTask[1].ptNext;
  if ( ptNext )
  {
    QReference_Delete((struct QReference_s *)ptNext, &QTask_tQTaskRefPool);
    v12->ptNext = nullptr;
  }
  if ( v13 )
    v12->ptNext = (struct QTask_s *)QTask_NewQTaskRef(v13);
  ptQTask[3].ptParent = nullptr;
  ptQTask[4].tQTaskChildren.ptHead = nullptr;
  ptQTask[4].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[4].ptNext = nullptr;
}

// source: j/0/computer/computermap.c:1051  [anchor-caller]
void __cdecl ComputerMap_RunHandler(struct QTask_s *ptQTask)
{
  struct QCamera_s *p_tQCamera; // esi
  struct QTask_s *ptHead; // ecx
  int v3; // edx
  struct QTask_s *v4; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v6; // edx
  struct QTask_s *ptMiddle; // eax
  struct QTask_s *v8; // eax
  struct RandomState_s *p_tRunRandomState; // esi
  struct RandomState_s *v10; // eax
  double RandomNumberReal32; // st7
  int v12; // ebx
  int v13; // eax
  unsigned int v14; // ecx
  double v15; // st7
  float nFrameNumber; // [esp+0h] [ebp-14h]
  float nFrameNumbera; // [esp+0h] [ebp-14h]

  p_tQCamera = &Game_ptGame->tQCamera;
  if ( Game_ptGame && LOBYTE(Game_ptGame->pxSpritesResource) )
  {
    nFrameNumber = (double)LevelFlow_ptLevelFlow->nTimeOfDayTick / ((double)Flow_ptFlow->nFrequency * 3600.0)
                 + LevelFlow_ptLevelFlow->vStartTime;
    QCamera_Set(
      &Game_ptGame->tQCamera,
      &ComputerMap_tPos,
      (struct real32x9_t *)&ptQTask[1],
      *(float *)&ptQTask[3].ptNext,
      1.0,
      2000.0,
      Screen_nFrameNumber,
      ptQTask,
      nFrameNumber,
      0);
  }
  else
  {
    ptQTask[4].ptPrev[1].ptNext = (struct QTask_s *)31;
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
        pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][ptHead->eQTaskType].pfHandler;
        v6 = v3 + 1;
        QTask_nProtectedQTaskStackOffset = v6;
        if ( pfHandler )
        {
          pfHandler(ptHead);
          v6 = QTask_nProtectedQTaskStackOffset;
        }
        ptHead = (struct QTask_s *)dword_849C7DC[v6];
        v3 = v6 - 1;
        QTask_nProtectedQTaskStackOffset = v3;
      }
      while ( ptHead );
    }
    ComputerMap_Trace(ptQTask);
    ComputerMap_SetCameraPosRelativeToTerrain(ptQTask);
    ComputerMap_ClipCameraPosAgainstLimit((struct ComputerMap_s *)ptQTask);
    nFrameNumbera = (double)LevelFlow_ptLevelFlow->nTimeOfDayTick / ((double)Flow_ptFlow->nFrequency * 3600.0)
                  + LevelFlow_ptLevelFlow->vStartTime;
    QCamera_Set(
      p_tQCamera,
      &ComputerMap_tPos,
      (struct real32x9_t *)&ptQTask[1],
      *(float *)&ptQTask[3].ptNext,
      1.0,
      2000.0,
      Screen_nFrameNumber,
      ptQTask,
      nFrameNumbera,
      0);
    p_tQCamera->vHeightFactor = 4096.0;
    ptMiddle = ptQTask[3].tQTaskChildren.ptMiddle;
    if ( ptMiddle )
    {
      v8 = (struct QTask_s *)((char *)ptMiddle - 1);
    }
    else
    {
      p_tRunRandomState = &Game_ptGame->tRunRandomState;
      v10 = &Game_ptGame->tRunRandomState;
      ptQTask[3].tQTaskChildren.ptHead = (struct QTask_s *)1036831949;
      RandomNumberReal32 = Random_GetRandomNumberReal32(v10);
      ptQTask[3].tQTaskChildren.ptMiddle = (struct QTask_s *)15;
      *(float *)&ptQTask[3].tQTaskChildren.ptHead = RandomNumberReal32 * 0.4000000059604645
                                                  + *(float *)&ptQTask[3].tQTaskChildren.ptHead;
      v12 = (p_tRunRandomState->anRandom[0] >> 7) ^ p_tRunRandomState->anRandom[2];
      v13 = v12 ^ p_tRunRandomState->anRandom[1];
      v14 = v13 + p_tRunRandomState->anRandom[0];
      p_tRunRandomState->anRandom[1] = v13;
      p_tRunRandomState->anRandom[0] = v14;
      p_tRunRandomState->anRandom[2] = v12;
      v8 = (struct QTask_s *)((char *)ptQTask[3].tQTaskChildren.ptMiddle + v14 % 0x4B);
    }
    v15 = *(float *)&ptQTask[3].tQTaskChildren.ptHead;
    ptQTask[3].tQTaskChildren.ptMiddle = v8;
    *(float *)&ptQTask[3].tQTaskChildren.ptHead = v15 - 0.03333333507180214;
  }
}

// source: j/0/computer/computermap.c:1118  [size~]
void __cdecl ComputerMap_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptPrev; // ebp
  struct QTask_s *ptParent; // eax
  struct Game_s *v3; // eax

  ptPrev = Game_ptGame->ptGameScreenQTask[1].ptPrev;
  QTask_DeleteQTaskAndQTaskRefSafe((struct QReference_s **)&ptQTask[4]);
  qmemcpy(&ComputerMap_tLastPos, &ComputerMap_tPos, sizeof(ComputerMap_tLastPos));
  ptParent = ptQTask[3].ptParent;
  ComputerMap_ptComputerMap = nullptr;
  if ( ptParent )
    QReference_Delete((struct QReference_s *)ptParent, &QTask_tQTaskRefPool);
  if ( ptPrev )
    ptPrev[10].tQTaskChildren.ptMiddle = nullptr;
  v3 = Game_ptGame;
  Game_ptGame->tQCamera.ptSetCameraQTask = nullptr;
  v3->tQCamera.tPos.vX = 0.0;
  v3->tQCamera.tPos.vY = 0.0;
  v3->tQCamera.tPos.vZ = 0.0;
  v3->tQCamera.tMatrix.tX.vY = 0.0;
  v3->tQCamera.tMatrix.tX.vZ = 0.0;
  v3->tQCamera.tMatrix.tY.vX = 0.0;
  v3->tQCamera.tMatrix.tY.vZ = 0.0;
  v3->tQCamera.tMatrix.tZ.vX = 0.0;
  v3->tQCamera.tMatrix.tZ.vY = 0.0;
  v3->tQCamera.tMatrix.nOps = 0;
  v3->tQCamera.nLastFrameNumber = -1082130432;
  v3->tQCamera.tMatrix.tX.vX = 1.0;
  v3->tQCamera.tMatrix.tY.vY = 1.0;
  v3->tQCamera.tMatrix.tZ.vZ = 1.0;
  v3->tQCamera.vHeightFactor = 409.6000061035156;
}

// source: j/0/computer/computermap.c:1159  [anchor-mhash]
void __cdecl ComputerMap_DrawHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vX1; };
    struct { char igi2_o1[8]; float vX3; };
    struct { char igi2_o2[12]; float vY1; };
    struct { char igi2_o3[16]; __int64 vDepth; };
    char igi2_extent[24];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QAnimframe_s *v1; // eax
  double v2; // st7
  double v3; // st6
  struct QTask_s *ptHead; // ecx
  int v5; // edx
  struct QTask_s *v6; // eax
  int v7; // esi
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v9; // edx

  if ( LOBYTE(ComputerMenu_ptComputerMenuQTask[1].tQTaskChildren.ptMiddle) )
    TransContext_ProjectWorldPos2(
      &TransContext_tActiveTransContext,
      (struct real32x2_t *)&ComputerMenu_ptComputerMenuQTask[1].ptPrev,
      (float *)&igi2_frame.vDepth,
      &ComputerMap_tLockPos);
  v1 = &ComputerMenu_tComputerMenuResource.tQSpriteCompass.atQAnimframe[ComputerMenu_tComputerMenuResource.tQSpriteCompass.nQAnimframes];
  v2 = (double)(50 * Display_tActiveMode.nHeight) * 0.0020833334419876337;
  igi2_frame.vDepth = (__int64)((double)(Display_tActiveMode.nHeight * v1->nHeight) * 0.0020833334419876337 + v2);
  igi2_frame.vX3 = (float)(int)igi2_frame.vDepth;
  v3 = (double)(520 * Display_tActiveMode.nWidth) * 0.0015625000232830644;
  igi2_frame.vY1 = (float)(int)(__int64)((double)(Display_tActiveMode.nWidth * v1->nWidth) * 0.0015625000232830644 + v3);
  igi2_frame.vDepth = (__int64)v3;
  *(float *)&igi2_frame.vDepth = (float)(int)(__int64)v3;
  igi2_frame.vX1 = (float)(int)(__int64)v2;
  QSprite_Register4(
    &ComputerMenu_tComputerMenuResource.tQSpriteCompass,
    *(float *)&igi2_frame.vDepth,
    igi2_frame.vX1,
    igi2_frame.vY1,
    igi2_frame.vX1,
    *(float *)&igi2_frame.vDepth,
    igi2_frame.vX3,
    igi2_frame.vY1,
    igi2_frame.vX3,
    128.0,
    128.0,
    128.0,
    0,
    (unsigned int)&MTP_atLODVirModel[48].atBoneVertexRefs[1].atVertexRefs[668],
    0);
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
      v7 = Screen_eDrawQTaskEvent;
      QTask_atProtectedQTaskStack[v5].ptQTask = v6;
      pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[v7][ptHead->eQTaskType].pfHandler;
      v9 = v5 + 1;
      QTask_nProtectedQTaskStackOffset = v9;
      if ( pfHandler )
      {
        pfHandler(ptHead);
        v9 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v9];
      v5 = v9 - 1;
      QTask_nProtectedQTaskStackOffset = v5;
    }
    while ( ptHead );
  }
}

// source: j/0/computer/computermap.c:1216  [size]
struct QTask_s *__cdecl ComputerMap_New(struct QTask_s *ptParent)
{
  return QTask_NewFn(ptParent, ComputerMap_eQTaskType, nullptr);
}

// source: j/0/computer/computermap.c:1236  [size]
struct ComputerMap_s *__cdecl ComputerMap_GetComputerMap()
{
  return ComputerMap_ptComputerMap;
}

// source: j/0/computer/computermap.c:1249  [size]
__int16 __cdecl ComputerMap_GetFollowQTaskEvent()
{
  return ComputerMap_eFollowQTaskEvent;
}

// source: j/0/computer/computermap.c:1262  [size]
unsigned __int16 __cdecl ComputerMap_GetQTaskType()
{
  return ComputerMap_eQTaskType;
}

// source: j/0/computer/computermap.c:1275  [size]
__int16 __cdecl ComputerMap_GetZoomLevel()
{
  return ComputerMap_nZoomLevel;
}

// source: j/0/computer/computermap.c:1288  [size]
void __cdecl ComputerMap_ClearZoomLevel()
{
  ComputerMap_nZoomLevel = 0;
}

// source: j/0/computer/computermap.c:1301  [size]
struct QTask_s *__cdecl ComputerMap_SetPositionTask(struct QTask_s *ptQTask)
{
  ComputerMap_ptPositionQTask = ptQTask;
  return ptQTask;
}

// source: j/0/computer/computermap.c:1314  [anchor-hash]
void __cdecl ComputerMap_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("ComputerMap", 176, BaseQTaskType, 0, 0);
  ComputerMap_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 0, ComputerMap_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, ComputerMap_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, ComputerMap_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, Screen_eDrawQTaskEvent, ComputerMap_DrawHandler);
  ComputerMap_eFollowQTaskEvent = QTask_NewQTaskEventFn(0, "ComputerMapFollowQTask");
  Symbol_Register(
    "Computer_nZoomLevel",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int16,
    &ComputerMap_nZoomLevel,
    2,
    QSCRIPT_SYMBOLCLASS_VARIABLE,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_FINITE);
}

void __cdecl sub_4DE380(int a1, int a2)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v9; };
    struct { char igi2_o1[4]; float v10; };
    struct { char igi2_o2[8]; float v11; };
    struct { char igi2_o3[12]; float v12; };
    struct { char igi2_o4[16]; int v13; };
    struct { char igi2_o5[20]; double v14; };
    struct { char igi2_o6[28]; float v15; };
    struct { char igi2_o7[40]; float v16; };
    struct { char igi2_o8[44]; float v17; };
    struct { char igi2_o9[48]; float v18; };
    struct { char igi2_o10[52]; float v19; };
    struct { char igi2_o11[56]; float v20; };
    struct { char igi2_o12[60]; struct CollisionEvaluateContext_s nNumPoints; };
    struct { char igi2_o13[68]; struct QIntersection_s ptIntersection; };
    struct { char igi2_o14[208]; int v23; };
    struct { char igi2_o15[212]; double v24; };
    char igi2_extent[240];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // ecx
  int v3; // ebp
  float *v4; // edi
  int v5; // esi
  long double v6; // st7
  long double v7; // st6
  double v8; // st7

  v2 = *(_DWORD *)(a2 + 112);
  igi2_frame.v11 = *(float *)(a2 + 284) + 2048.0;
  igi2_frame.v12 = 0.0;
  igi2_frame.v13 = -1068953637;
  igi2_frame.v14 = 0.0;
  if ( v2 )
    igi2_frame.nNumPoints.ptQTask = *(struct QTask_s **)(v2 + 8);
  else
    igi2_frame.nNumPoints.ptQTask = nullptr;
  qmemcpy(&igi2_frame.ptIntersection, (void *)(a2 + 120), 0x18u);
  v3 = a1 != 0 ? 1 : 8;
  v4 = (float *)&unk_6B8158;
  while ( 2 )
  {
    v5 = 0;
    igi2_frame.v10 = *v4;
    igi2_frame.v9 = -1.5707963705062866;
    igi2_frame.v15 = cos(igi2_frame.v10);
    igi2_frame.v20 = sin(igi2_frame.v10);
    do
    {
      v6 = cos(igi2_frame.v9) * igi2_frame.v15;
      v7 = sin(igi2_frame.v9) * igi2_frame.v15;
      igi2_frame.v17 = v6 * *(float *)(a2 + 188) + igi2_frame.v20 * *(float *)(a2 + 196) + v7 * *(float *)(a2 + 192);
      igi2_frame.v18 = v6 * *(float *)(a2 + 200) + igi2_frame.v20 * *(float *)(a2 + 208) + v7 * *(float *)(a2 + 204);
      igi2_frame.v19 = v6 * *(float *)(a2 + 212) + igi2_frame.v20 * *(float *)(a2 + 220) + v7 * *(float *)(a2 + 216);
      igi2_frame.v16 = igi2_frame.v19 * igi2_frame.v11;
      igi2_frame.ptIntersection.tPos.vZ = igi2_frame.v17 * igi2_frame.v11 + *(double *)&igi2_frame.ptIntersection.ptHitObj;
      *(double *)&igi2_frame.ptIntersection.tLocalPos.vX = igi2_frame.v18 * igi2_frame.v11 + igi2_frame.ptIntersection.tPos.vX;
      *(double *)&igi2_frame.ptIntersection.tLocalPos.vZ = igi2_frame.v16 + igi2_frame.ptIntersection.tPos.vY;
      World_TraceLines(
        Game_ptGame->ptWorld,
        (struct QIntersection_s *)&igi2_frame.ptIntersection.tLocalNormal.vY,
        (struct real64x3_t *)&igi2_frame.ptIntersection,
        (struct real64x3_t *)&igi2_frame.ptIntersection.tPos.vZ,
        1,
        GameFunctions_eObjectCollisionEvaluateQTaskEvent,
        &igi2_frame.nNumPoints,
        0xFFFFFFFF);
      if ( !igi2_frame.v23 || *(_WORD *)(LODWORD(igi2_frame.ptIntersection.tLocalNormal.vY) + 36) == Water_eQTaskType && igi2_frame.v10 > 0.0 )
      {
        igi2_frame.v14 = igi2_frame.v11;
        igi2_frame.v12 = igi2_frame.v10;
        igi2_frame.v13 = LODWORD(igi2_frame.v9);
        goto LABEL_16;
      }
      if ( igi2_frame.v24 > igi2_frame.v14 )
      {
        igi2_frame.v12 = igi2_frame.v10;
        igi2_frame.v13 = LODWORD(igi2_frame.v9);
        igi2_frame.v14 = igi2_frame.v24;
      }
      ++v5;
      igi2_frame.v9 = igi2_frame.v9 + 0.7853981852531433;
    }
    while ( v5 < v3 );
    if ( (int)++v4 < 7045496 )
      continue;
    break;
  }
LABEL_16:
  v8 = igi2_frame.v14 - 2048.0;
  *(_DWORD *)(a2 + 276) = igi2_frame.v13;
  *(float *)(a2 + 272) = igi2_frame.v12;
  if ( igi2_frame.v14 - 2048.0 <= 0.0 )
    v8 = 0.0;
  *(float *)(a2 + 280) = v8;
}

int __cdecl sub_4DE620(int result)
{
  long double v1; // st7
  long double v2; // st6
  long double v3; // st5
  long double v4; // rt0
  long double v5; // st5
  long double v6; // st6
  long double v7; // st7
  long double v8; // st6
  double v9; // rtt
  float v10; // [esp+8h] [ebp-18h]
  float v11; // [esp+10h] [ebp-10h]
  float v12; // [esp+14h] [ebp-Ch]
  float v13; // [esp+18h] [ebp-8h]
  float v14; // [esp+1Ch] [ebp-4h]

  v1 = *(float *)(result + 272);
  v2 = *(float *)(result + 276);
  v3 = cos(v1);
  qmemcpy((void *)(result + 40), (void *)(result + 120), 0x18u);
  v10 = cos(v2) * v3;
  v4 = v3;
  v5 = sin(v2);
  v6 = v1;
  v7 = v4 * v5;
  v8 = sin(v6);
  v12 = v8 * *(float *)(result + 196) + v7 * *(float *)(result + 192) + v10 * *(float *)(result + 188);
  v13 = v8 * *(float *)(result + 208) + v7 * *(float *)(result + 204) + v10 * *(float *)(result + 200);
  v14 = v8 * *(float *)(result + 220) + v7 * *(float *)(result + 216) + v10 * *(float *)(result + 212);
  v11 = v14 * *(float *)(result + 280);
  v9 = v13 * *(float *)(result + 280);
  *(double *)(result + 40) = v12 * *(float *)(result + 280) + *(double *)(result + 40);
  *(double *)(result + 48) = v9 + *(double *)(result + 48);
  *(double *)(result + 56) = v11 + *(double *)(result + 56);
  return result;
}

void __cdecl sub_4DE720(int a1)
{
  #pragma pack(push, 1)
  union
  {
    struct { float pvBeta; };
    struct { char igi2_o1[4]; float pvGamma; };
    struct { char igi2_o2[8]; double v9; };
    struct { char igi2_o3[16]; float v10; };
    struct { char igi2_o4[20]; struct real32x3_t ptSource; };
    char igi2_extent[32];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v1; // st7
  double v2; // st6
  double v3; // st5
  double v4; // st6
  long double v5; // st7
  double v6; // st7

  v1 = *(double *)(a1 + 40) - *(double *)(a1 + 120);
  v2 = *(double *)(a1 + 48) - *(double *)(a1 + 128);
  v3 = *(double *)(a1 + 56) - *(double *)(a1 + 136);
  *(float *)&igi2_frame.v9 = v3 * *(float *)(a1 + 212) + v2 * *(float *)(a1 + 200) + v1 * *(float *)(a1 + 188);
  igi2_frame.ptSource.vX = *(float *)&igi2_frame.v9;
  *((float *)&igi2_frame.v9 + 1) = v3 * *(float *)(a1 + 216) + v2 * *(float *)(a1 + 204) + v1 * *(float *)(a1 + 192);
  igi2_frame.ptSource.vY = *((float *)&igi2_frame.v9 + 1);
  igi2_frame.v10 = v3 * *(float *)(a1 + 220) + v2 * *(float *)(a1 + 208) + v1 * *(float *)(a1 + 196);
  igi2_frame.ptSource.vZ = igi2_frame.v10;
  Real32x3_GetAngles(&igi2_frame.ptSource, &igi2_frame.pvBeta, &igi2_frame.pvGamma);
  v4 = igi2_frame.v10 * igi2_frame.v10 + *((float *)&igi2_frame.v9 + 1) * *((float *)&igi2_frame.v9 + 1);
  igi2_frame.v9 = *(float *)&igi2_frame.v9;
  v5 = sqrt(v4 + igi2_frame.v9 * igi2_frame.v9);
  *(float *)(a1 + 280) = v5;
  if ( v5 > *(float *)(a1 + 284) )
    *(_DWORD *)(a1 + 280) = *(_DWORD *)(a1 + 284);
  v6 = -igi2_frame.pvBeta;
  *(float *)(a1 + 276) = igi2_frame.pvGamma;
  *(float *)(a1 + 272) = v6;
}

int __cdecl sub_4DE830(int a1)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v41; };
    struct { float v42; };
    struct { float v43; };
    struct { float v44; };
    struct { float v45; };
    struct { float v46; };
    struct { float v47; };
    struct { char igi2_o7[4]; float v48; };
    struct { char igi2_o8[4]; float v49; };
    struct { char igi2_o9[4]; float v50; };
    struct { char igi2_o10[4]; float v51; };
    struct { char igi2_o11[4]; float v52; };
    struct { char igi2_o12[4]; float v53; };
    struct { char igi2_o13[4]; float v54; };
    struct { char igi2_o14[8]; float v55; };
    struct { char igi2_o15[8]; float v56; };
    struct { char igi2_o16[8]; float v57; };
    struct { char igi2_o17[8]; float v58; };
    struct { char igi2_o18[8]; float v59; };
    struct { char igi2_o19[8]; float v60; };
    struct { char igi2_o20[12]; int v61; };
    struct { char igi2_o21[16]; float v62; };
    struct { char igi2_o22[24]; float v63; };
    struct { char igi2_o23[28]; float v64; };
    struct { char igi2_o24[28]; float v65; };
    struct { char igi2_o25[32]; struct QIntersection_s ptIntersection; };
    struct { char igi2_o26[152]; _BYTE v67[168]; };
    struct { char igi2_o27[320]; struct real64x3_t ptEnd; };
    struct { char igi2_o28[344]; double v69[33]; };
    struct { char igi2_o29[608]; struct QIntersection_s v70; };
    char igi2_extent[2052];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  unsigned int v1; // eax
  double *v2; // ebp
  float *v3; // edx
  double v4; // st6
  double v5; // st7
  double v6; // st7
  double v7; // st7
  double v8; // st7
  double v9; // st6
  double v10; // st7
  _BYTE *v11; // edi
  double v12; // st7
  double v13; // st7
  float v14; // ecx
  double v15; // st7
  double v16; // st6
  double v17; // st5
  int v18; // edx
  double *p_vDistance; // eax
  int v20; // esi
  double v21; // st4
  int v22; // ecx
  int v23; // ecx
  double v24; // st4
  int v25; // ecx
  int v26; // ecx
  double v27; // st4
  int v28; // ecx
  int v29; // ecx
  double v30; // st4
  int v31; // ecx
  int v32; // ecx
  double v33; // st4
  int v34; // ecx
  int v35; // ecx
  double v36; // st4
  int v37; // ecx
  int v38; // ecx
  int result; // eax
  double v40; // st6

  v1 = 0;
  igi2_frame.v61 = 0;
  v2 = (double *)(a1 + 40);
  v3 = (float *)&unk_6B80D4;
  do
  {
    qmemcpy((char *)&igi2_frame.ptIntersection + v1, v2, 0x18u);
    v4 = *(v3 - 2) * 2048.0;
    igi2_frame.v55 = *(v3 - 1) * 2048.0;
    *(double *)((char *)&igi2_frame.ptEnd.vX + v1) = *(v3 - 3) * 2048.0 + *(double *)&igi2_frame.ptIntersection.ptHitObj;
    *(double *)((char *)&igi2_frame.ptEnd.vY + v1) = v4 + igi2_frame.ptIntersection.tPos.vX;
    v5 = igi2_frame.v55 + igi2_frame.ptIntersection.tPos.vY;
    qmemcpy((char *)&igi2_frame.ptIntersection.tPos.vZ + v1, v2, 0x18u);
    *(double *)((char *)&igi2_frame.ptEnd.vZ + v1) = v5;
    igi2_frame.v56 = v3[2] * 2048.0;
    v6 = v3[1] * 2048.0;
    igi2_frame.v69[v1 / 8] = *v3 * 2048.0 + *(double *)&igi2_frame.ptIntersection.ptHitObj;
    igi2_frame.v69[v1 / 8 + 1] = v6 + igi2_frame.ptIntersection.tPos.vX;
    v7 = igi2_frame.v56 + igi2_frame.ptIntersection.tPos.vY;
    qmemcpy((char *)&igi2_frame.ptIntersection.tLocalNormal.vY + v1, v2, 0x18u);
    igi2_frame.v69[v1 / 8 + 2] = v7;
    igi2_frame.v57 = v3[5] * 2048.0;
    v8 = v3[4] * 2048.0;
    igi2_frame.v69[v1 / 8 + 3] = v3[3] * 2048.0 + *(double *)&igi2_frame.ptIntersection.ptHitObj;
    igi2_frame.v69[v1 / 8 + 4] = v8 + igi2_frame.ptIntersection.tPos.vX;
    igi2_frame.v69[v1 / 8 + 5] = igi2_frame.v57 + igi2_frame.ptIntersection.tPos.vY;
    qmemcpy((char *)&igi2_frame.ptIntersection.iFace + v1, v2, 0x18u);
    v9 = v3[7] * 2048.0;
    igi2_frame.v58 = v3[8] * 2048.0;
    igi2_frame.v69[v1 / 8 + 6] = v3[6] * 2048.0 + *(double *)&igi2_frame.ptIntersection.ptHitObj;
    igi2_frame.v69[v1 / 8 + 7] = v9 + igi2_frame.ptIntersection.tPos.vX;
    v10 = igi2_frame.v58 + igi2_frame.ptIntersection.tPos.vY;
    qmemcpy((char *)&igi2_frame.ptIntersection.vDistance + v1, v2, 0x18u);
    igi2_frame.v69[v1 / 8 + 8] = v10;
    v11 = &igi2_frame.v67[v1];
    v1 += 144;
    igi2_frame.v59 = v3[11] * 2048.0;
    v12 = v3[10] * 2048.0;
    *(double *)&igi2_frame.v67[v1 + 120] = v3[9] * 2048.0 + *(double *)&igi2_frame.ptIntersection.ptHitObj;
    *(double *)&igi2_frame.v67[v1 + 128] = v12 + igi2_frame.ptIntersection.tPos.vX;
    v13 = igi2_frame.v59 + igi2_frame.ptIntersection.tPos.vY;
    qmemcpy(v11, v2, 0x18u);
    *(double *)&igi2_frame.v67[v1 + 136] = v13;
    igi2_frame.v41 = v3[12];
    v14 = v3[14];
    igi2_frame.v48 = v3[13];
    v3 += 18;
    igi2_frame.v60 = v14 * 2048.0;
    *(double *)&igi2_frame.v67[v1 + 144] = igi2_frame.v41 * 2048.0 + *(double *)&igi2_frame.ptIntersection.ptHitObj;
    *(double *)&igi2_frame.v67[v1 + 152] = igi2_frame.v48 * 2048.0 + igi2_frame.ptIntersection.tPos.vX;
    *(double *)&igi2_frame.v67[v1 + 160] = igi2_frame.v60 + igi2_frame.ptIntersection.tPos.vY;
  }
  while ( (int)v3 < 7045476 );
  World_TraceLines(
    Game_ptGame->ptWorld,
    &igi2_frame.v70,
    (struct real64x3_t *)&igi2_frame.ptIntersection,
    &igi2_frame.ptEnd,
    12,
    512,
    nullptr,
    0xFFFFFFFF);
  v15 = 0.0;
  v16 = 0.0;
  v17 = 0.0;
  v18 = 0;
  p_vDistance = &igi2_frame.v70.vDistance;
  v20 = 2;
  do
  {
    if ( *((_DWORD *)p_vDistance - 1) )
    {
      v21 = 2048.0 - *p_vDistance;
      v22 = *(_DWORD *)(a1 + 112);
      igi2_frame.v42 = *((float *)p_vDistance - 10) * v21;
      ++v18;
      igi2_frame.v49 = *((float *)p_vDistance - 9) * v21;
      v15 = v15 + igi2_frame.v42;
      v16 = v16 + igi2_frame.v49;
      v17 = v17 + v21 * *((float *)p_vDistance - 8);
      v23 = v22 ? *(_DWORD *)(v22 + 8) : 0;
      if ( *((_DWORD *)p_vDistance - 24) != v23 )
        igi2_frame.v61 = 1;
    }
    if ( *((_DWORD *)p_vDistance + 29) )
    {
      v24 = 2048.0 - p_vDistance[15];
      v25 = *(_DWORD *)(a1 + 112);
      igi2_frame.v43 = *((float *)p_vDistance + 20) * v24;
      ++v18;
      igi2_frame.v50 = *((float *)p_vDistance + 21) * v24;
      v15 = v15 + igi2_frame.v43;
      v16 = v16 + igi2_frame.v50;
      v17 = v17 + v24 * *((float *)p_vDistance + 22);
      v26 = v25 ? *(_DWORD *)(v25 + 8) : 0;
      if ( *((_DWORD *)p_vDistance + 6) != v26 )
        igi2_frame.v61 = 1;
    }
    if ( *((_DWORD *)p_vDistance + 59) )
    {
      v27 = 2048.0 - p_vDistance[30];
      v28 = *(_DWORD *)(a1 + 112);
      igi2_frame.v44 = *((float *)p_vDistance + 50) * v27;
      ++v18;
      igi2_frame.v51 = *((float *)p_vDistance + 51) * v27;
      v15 = v15 + igi2_frame.v44;
      v16 = v16 + igi2_frame.v51;
      v17 = v17 + v27 * *((float *)p_vDistance + 52);
      v29 = v28 ? *(_DWORD *)(v28 + 8) : 0;
      if ( *((_DWORD *)p_vDistance + 36) != v29 )
        igi2_frame.v61 = 1;
    }
    if ( *((_DWORD *)p_vDistance + 89) )
    {
      v30 = 2048.0 - p_vDistance[45];
      v31 = *(_DWORD *)(a1 + 112);
      igi2_frame.v45 = *((float *)p_vDistance + 80) * v30;
      ++v18;
      igi2_frame.v52 = *((float *)p_vDistance + 81) * v30;
      v15 = v15 + igi2_frame.v45;
      v16 = v16 + igi2_frame.v52;
      v17 = v17 + v30 * *((float *)p_vDistance + 82);
      v32 = v31 ? *(_DWORD *)(v31 + 8) : 0;
      if ( *((_DWORD *)p_vDistance + 66) != v32 )
        igi2_frame.v61 = 1;
    }
    if ( *((_DWORD *)p_vDistance + 119) )
    {
      v33 = 2048.0 - p_vDistance[60];
      v34 = *(_DWORD *)(a1 + 112);
      igi2_frame.v46 = *((float *)p_vDistance + 110) * v33;
      ++v18;
      igi2_frame.v53 = *((float *)p_vDistance + 111) * v33;
      v15 = v15 + igi2_frame.v46;
      v16 = v16 + igi2_frame.v53;
      v17 = v17 + v33 * *((float *)p_vDistance + 112);
      v35 = v34 ? *(_DWORD *)(v34 + 8) : 0;
      if ( *((_DWORD *)p_vDistance + 96) != v35 )
        igi2_frame.v61 = 1;
    }
    if ( *((_DWORD *)p_vDistance + 149) )
    {
      v36 = 2048.0 - p_vDistance[75];
      v37 = *(_DWORD *)(a1 + 112);
      igi2_frame.v47 = *((float *)p_vDistance + 140) * v36;
      ++v18;
      igi2_frame.v54 = *((float *)p_vDistance + 141) * v36;
      v15 = v15 + igi2_frame.v47;
      v16 = v16 + igi2_frame.v54;
      v17 = v17 + v36 * *((float *)p_vDistance + 142);
      v38 = v37 ? *(_DWORD *)(v37 + 8) : 0;
      if ( *((_DWORD *)p_vDistance + 126) != v38 )
        igi2_frame.v61 = 1;
    }
    p_vDistance += 90;
    --v20;
  }
  while ( v20 );
  result = igi2_frame.v61;
  igi2_frame.v63 = v16;
  if ( v18 )
  {
    v40 = 1.0 / (double)v18;
    igi2_frame.v62 = v40;
    igi2_frame.v64 = v17;
    igi2_frame.v65 = igi2_frame.v62 * igi2_frame.v64;
    *v2 = v15 * v40 + *v2;
    *(double *)(a1 + 48) = igi2_frame.v62 * igi2_frame.v63 + *(double *)(a1 + 48);
    *(double *)(a1 + 56) = igi2_frame.v65 + *(double *)(a1 + 56);
  }
  return result;
}

int __cdecl sub_4DEE70(double *a1, float *a2, double *a3)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v16; };
    struct { float v17; };
    struct { char igi2_o2[4]; float v18; };
    struct { char igi2_o3[4]; float v19; };
    struct { char igi2_o4[8]; float v20; };
    struct { char igi2_o5[8]; float v21; };
    struct { char igi2_o6[12]; float v22; };
    struct { char igi2_o7[16]; float v23; };
    struct { char igi2_o8[20]; float v24; };
    struct { char igi2_o9[24]; float v25; };
    struct { char igi2_o10[28]; float v26; };
    struct { char igi2_o11[28]; float v27; };
    struct { char igi2_o12[36]; float v28; };
    struct { char igi2_o13[40]; float v29; };
    struct { char igi2_o14[40]; float v30; };
    struct { char igi2_o15[44]; float v31; };
    struct { char igi2_o16[48]; float v32; };
    struct { char igi2_o17[52]; float v33; };
    struct { char igi2_o18[56]; float v34; };
    struct { char igi2_o19[60]; float v35[10]; };
    struct { char igi2_o20[120]; float v36; };
    char igi2_extent[144];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v3; // st7
  double v5; // st6
  long double v6; // st7
  double v7; // st5
  long double v8; // st7
  long double v9; // st5
  long double v10; // st5
  long double v11; // st5
  double v13; // st4
  double v14; // st4
  int v15; // edx

  v3 = *a1 - *a3;
  igi2_frame.v26 = a1[1] - a3[1];
  v5 = a1[2] - a3[2];
  if ( v3 == 0.0 && igi2_frame.v26 == 0.0 )
  {
    igi2_frame.v25 = 0.0;
    igi2_frame.v27 = 1.0;
    v6 = 0.0;
  }
  else
  {
    v7 = v3;
    v8 = 1.0 / sqrt(v3 * v3 + igi2_frame.v26 * igi2_frame.v26 + v5 * v5);
    igi2_frame.v25 = v7 * v8;
    igi2_frame.v27 = igi2_frame.v26 * v8;
    v6 = v5 * v8;
  }
  igi2_frame.v16 = igi2_frame.v27 - 0.0 * v6;
  igi2_frame.v22 = igi2_frame.v16;
  igi2_frame.v18 = -(igi2_frame.v25 - 0.0 * v6);
  igi2_frame.v23 = igi2_frame.v18;
  igi2_frame.v34 = igi2_frame.v25 * 0.0;
  igi2_frame.v29 = igi2_frame.v27 * 0.0;
  igi2_frame.v20 = igi2_frame.v34 - igi2_frame.v29;
  igi2_frame.v24 = igi2_frame.v20;
  if ( igi2_frame.v16 != 0.0 || igi2_frame.v18 != 0.0 || igi2_frame.v20 != 0.0 )
  {
    v9 = 1.0 / sqrt(igi2_frame.v16 * igi2_frame.v16 + igi2_frame.v18 * igi2_frame.v18 + igi2_frame.v20 * igi2_frame.v20);
    igi2_frame.v22 = igi2_frame.v16 * v9;
    igi2_frame.v23 = igi2_frame.v18 * v9;
    igi2_frame.v24 = igi2_frame.v20 * v9;
  }
  igi2_frame.v31 = igi2_frame.v23 * v6 - igi2_frame.v24 * igi2_frame.v27;
  igi2_frame.v17 = igi2_frame.v31;
  igi2_frame.v32 = -(igi2_frame.v22 * v6 - igi2_frame.v24 * igi2_frame.v25);
  igi2_frame.v19 = igi2_frame.v32;
  igi2_frame.v33 = igi2_frame.v22 * igi2_frame.v27 - igi2_frame.v23 * igi2_frame.v25;
  igi2_frame.v21 = igi2_frame.v33;
  if ( igi2_frame.v31 != 0.0 || igi2_frame.v32 != 0.0 || igi2_frame.v33 != 0.0 )
  {
    v10 = 1.0 / sqrt(igi2_frame.v31 * igi2_frame.v31 + igi2_frame.v32 * igi2_frame.v32 + igi2_frame.v33 * igi2_frame.v33);
    igi2_frame.v17 = igi2_frame.v31 * v10;
    igi2_frame.v19 = igi2_frame.v32 * v10;
    igi2_frame.v21 = igi2_frame.v33 * v10;
  }
  a2[7] = v6;
  v11 = sin(-1.5707963705062866);
  *a2 = igi2_frame.v22;
  a2[3] = igi2_frame.v23;
  a2[6] = igi2_frame.v24;
  a2[1] = igi2_frame.v25;
  a2[4] = igi2_frame.v27;
  a2[2] = igi2_frame.v17;
  a2[5] = igi2_frame.v19;
  a2[8] = igi2_frame.v21;
  igi2_frame.v28 = cos(-1.5707963705062866);
  igi2_frame.v36 = -v11;
  igi2_frame.v35[0] = igi2_frame.v17 * 0.0 + igi2_frame.v34 + igi2_frame.v22;
  v13 = igi2_frame.v22 * 0.0;
  igi2_frame.v35[1] = igi2_frame.v28 * igi2_frame.v25 + v11 * igi2_frame.v17 + v13;
  igi2_frame.v35[2] = igi2_frame.v28 * igi2_frame.v17 + igi2_frame.v36 * igi2_frame.v25 + v13;
  igi2_frame.v35[3] = igi2_frame.v19 * 0.0 + igi2_frame.v23 + igi2_frame.v29;
  v14 = igi2_frame.v23 * 0.0;
  igi2_frame.v35[4] = igi2_frame.v28 * igi2_frame.v27 + v11 * igi2_frame.v19 + v14;
  igi2_frame.v35[5] = igi2_frame.v28 * igi2_frame.v19 + igi2_frame.v36 * igi2_frame.v27 + v14;
  v15 = *((_DWORD *)a2 + 9) + 1;
  igi2_frame.v35[6] = igi2_frame.v21 * 0.0 + igi2_frame.v24 + 0.0 * v6;
  LODWORD(igi2_frame.v35[9]) = v15;
  igi2_frame.v30 = igi2_frame.v24 * 0.0;
  igi2_frame.v35[7] = igi2_frame.v28 * v6 + v11 * igi2_frame.v21 + igi2_frame.v30;
  igi2_frame.v35[8] = igi2_frame.v28 * igi2_frame.v21 + igi2_frame.v36 * v6 + igi2_frame.v30;
  qmemcpy(a2, igi2_frame.v35, 0x28u);
  return LODWORD(igi2_frame.v19);
}
