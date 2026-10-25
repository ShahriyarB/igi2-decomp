/* j/0/effects/environmentsound.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/effects/environmentsound.c:101  [anchor-mhash]
void __cdecl EnvironmentSound_Ecco(struct EnvironmentSound_s *ptEnvironmentSound)
{
  #pragma pack(push, 1)
  union
  {
    struct { float tTemp_; };
    struct { char igi2_o1[4]; float tTemp__4; };
    struct { char igi2_o2[8]; float tTemp__8; };
    struct { char igi2_o3[28]; float tRight_8; };
    struct { char igi2_o4[32]; struct ObjectCollisionEvaluateContext_t tObjectCollisionEvaluateContext; };
    struct { char igi2_o5[40]; struct real64x3_t atStart[2]; };
    struct { char igi2_o6[88]; struct real64x3_t atStop[2]; };
    struct { char igi2_o7[136]; struct QIntersection_s atIntersection[2]; };
    char igi2_extent[376];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v1; // st7
  double v2; // st7
  double v3; // st7
  double v4; // st7
  double v5; // st7
  double v6; // st7
  double v7; // st7
  double v8; // st7
  double vZ; // st7
  double v10; // st6
  double v11; // st5
  struct QTask_s *pxObject; // ecx
  struct QReference_s *v13; // eax
  int v14; // edx
  double *p_vDistance; // esi
  int v16; // eax
  int v17; // ecx
  double v18; // st7
  double v19; // st7

  v1 = ptEnvironmentSound->avEccoLeft[0] - 0.011111111380159855;
  if ( v1 <= 0.0 )
    v1 = 0.0;
  ptEnvironmentSound->avEccoLeft[0] = v1;
  v2 = ptEnvironmentSound->avEccoRight[0] - 0.011111111380159855;
  if ( v2 <= 0.0 )
    v2 = 0.0;
  ptEnvironmentSound->avEccoRight[0] = v2;
  v3 = ptEnvironmentSound->avEccoLeft[1] - 0.011111111380159855;
  if ( v3 <= 0.0 )
    v3 = 0.0;
  ptEnvironmentSound->avEccoLeft[1] = v3;
  v4 = ptEnvironmentSound->avEccoRight[1] - 0.011111111380159855;
  if ( v4 <= 0.0 )
    v4 = 0.0;
  ptEnvironmentSound->avEccoRight[1] = v4;
  v5 = ptEnvironmentSound->avEccoLeft[2] - 0.011111111380159855;
  if ( v5 <= 0.0 )
    v5 = 0.0;
  ptEnvironmentSound->avEccoLeft[2] = v5;
  v6 = ptEnvironmentSound->avEccoRight[2] - 0.011111111380159855;
  if ( v6 <= 0.0 )
    v6 = 0.0;
  ptEnvironmentSound->avEccoRight[2] = v6;
  v7 = ptEnvironmentSound->avEccoLeft[3] - 0.011111111380159855;
  if ( v7 <= 0.0 )
    v7 = 0.0;
  ptEnvironmentSound->avEccoLeft[3] = v7;
  v8 = ptEnvironmentSound->avEccoRight[3] - 0.011111111380159855;
  if ( v8 <= 0.0 )
    v8 = 0.0;
  ptEnvironmentSound->avEccoRight[3] = v8;
  vZ = EnvironmentSound_ptCamera->tMatrix.tX.vZ;
  v10 = EnvironmentSound_ptCamera->tMatrix.tY.vZ;
  v11 = EnvironmentSound_ptCamera->tMatrix.tZ.vZ * 0.0;
  igi2_frame.tTemp_ = v11 - v10;
  igi2_frame.tTemp__4 = -(v11 - vZ);
  igi2_frame.tTemp__8 = v10 * 0.0 - vZ * 0.0;
  qmemcpy(igi2_frame.atStart, &EnvironmentSound_ptCamera->tPos, 0x18u);
  igi2_frame.tRight_8 = -igi2_frame.tTemp__8;
  igi2_frame.atStop[0].vX = -igi2_frame.tTemp_ * 40960.0 + igi2_frame.atStart[0].vX;
  igi2_frame.atStop[0].vY = -igi2_frame.tTemp__4 * 40960.0 + igi2_frame.atStart[0].vY;
  igi2_frame.atStop[0].vZ = igi2_frame.tRight_8 * 40960.0 + igi2_frame.atStart[0].vZ;
  qmemcpy(&igi2_frame.atStart[1], &EnvironmentSound_ptCamera->tPos, sizeof(struct real64x3_t));
  igi2_frame.atStop[1].vX = igi2_frame.tTemp_ * 40960.0 + igi2_frame.atStart[1].vX;
  pxObject = nullptr;
  igi2_frame.atStop[1].vY = igi2_frame.tTemp__4 * 40960.0 + igi2_frame.atStart[1].vY;
  igi2_frame.atStop[1].vZ = igi2_frame.tTemp__8 * 40960.0 + igi2_frame.atStart[1].vZ;
  v13 = Game_ptGame->aptPlayerQTaskRef[2];
  if ( v13 )
    pxObject = (struct QTask_s *)v13->pxObject;
  igi2_frame.tObjectCollisionEvaluateContext.tCollisionEvaluateContext.ptQTask = pxObject;
  World_TraceLines(
    Game_ptGame->ptWorld,
    igi2_frame.atIntersection,
    igi2_frame.atStart,
    igi2_frame.atStop,
    2,
    GameFunctions_eObjectCollisionEvaluateQTaskEvent,
    &igi2_frame.tObjectCollisionEvaluateContext.tCollisionEvaluateContext,
    0x20000000u);
  v14 = 0;
  p_vDistance = &igi2_frame.atIntersection[0].vDistance;
  do
  {
    if ( *((_DWORD *)p_vDistance - 1) && *p_vDistance < 40960.0 )
    {
      v16 = (__int64)(*p_vDistance * 0.000244140625);
      if ( v16 > 1 )
      {
        if ( v16 > 2 )
          v17 = (v16 > 4) + 2;
        else
          v17 = 1;
      }
      else
      {
        v17 = 0;
      }
      if ( (v14 & 1) != 0 )
      {
        v18 = ptEnvironmentSound->avEccoLeft[v17] + 1.0;
        if ( v18 >= 1.0 )
          v18 = 1.0;
        ptEnvironmentSound->avEccoLeft[v17] = v18;
      }
      else
      {
        v19 = ptEnvironmentSound->avEccoRight[v17] + 1.0;
        if ( v19 >= 1.0 )
          v19 = 1.0;
        ptEnvironmentSound->avEccoRight[v17] = v19;
      }
    }
    ++v14;
    p_vDistance += 15;
  }
  while ( v14 < 2 );
}

// source: j/0/effects/environmentsound.c:405  [anchor-mhash]
void __cdecl EnvironmentSound_Init(struct EnvironmentSound_s *ptEnvironmentSound)
{
  struct QTask_s *v1; // eax
  struct QTask_s *v2; // ebx
  struct QReference_s *v3; // eax
  int v4; // ecx
  int eQTaskType; // edx
  float *avEccoRight; // eax
  int v7; // ecx
  _DWORD v8[2]; // [esp+8h] [ebp-8h] BYREF

  ptEnvironmentSound->vAmbientRainVolume = 0.0;
  QTask_DeleteQTaskAndQTaskRefSafe(&ptEnvironmentSound->ptAmbientRainSound);
  v1 = SoundSys_NewSoundFn(&ptEnvironmentSound->tQTask, ptEnvironmentSound->azAmbientRainSound);
  v2 = v1;
  if ( v1 )
  {
    v3 = QTask_NewQTaskRef(v1);
    v4 = 511 * SoundSys_eSetVolumeQTaskEvent;
    ptEnvironmentSound->ptAmbientRainSound = v3;
    eQTaskType = v2->eQTaskType;
    v8[1] = LODWORD(ptEnvironmentSound->vAmbientRainVolume);
    v8[0] = -1082130432;
    ((void (__cdecl *)(struct QTask_s *, _DWORD *))QTask_aatQTaskFinalEvent[0][eQTaskType + v4].pfHandler)(v2, v8);
  }
  avEccoRight = ptEnvironmentSound->avEccoRight;
  v7 = 4;
  do
  {
    *(avEccoRight - 4) = 0.0;
    *avEccoRight++ = 0.0;
    --v7;
  }
  while ( v7 );
}

// source: j/0/effects/environmentsound.c:445  [anchor-mhash]
void __cdecl EnvironmentSound_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  LOBYTE(ptQTask[1].ptNext) = 0;
  BYTE1(ptQTask[1].ptNext) = 0;
  BYTE2(ptQTask[1].ptNext) = 0;
  HIBYTE(ptQTask[1].ptNext) = 0;
  strcpy((char *)&ptQTask[1].ptPrev, "rain_2");
  ptQTask[1].tQTaskRefList.ptMiddle = nullptr;
  EnvironmentSound_Init((struct EnvironmentSound_s *)ptQTask);
}

// source: j/0/effects/environmentsound.c:473  [anchor-mhash]
void __cdecl EnvironmentSound_RunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // ecx
  int v2; // edx
  struct QTask_s *v3; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v5; // edx

  if ( LOBYTE(ptQTask[1].ptNext) )
    EnvironmentSound_Ecco((struct EnvironmentSound_s *)ptQTask);
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

// source: j/0/effects/environmentsound.c:517  [size]
void __cdecl EnvironmentSound_DeleteHandler(struct QTask_s *ptQTask)
{
  QTask_DeleteQTaskAndQTaskRefSafe(&ptQTask[1].tQTaskRefList.ptMiddle);
}

// source: j/0/effects/environmentsound.c:533  [size]
void __cdecl EnvironmentSound_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = EnvironmentSound_ptParameterList;
}

// source: j/0/effects/environmentsound.c:549  [anchor-caller]
void __cdecl EnvironmentSound_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  EnvironmentSound_Init((struct EnvironmentSound_s *)ptQTask);
}

// source: j/0/effects/environmentsound.c:567  [anchor-hash]
void __cdecl EnvironmentSound_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si
  struct ParameterList_s *v2; // eax
  int v3; // edx

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("EnvironmentSound", 100, BaseQTaskType, 0, 0);
  EnvironmentSound_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(
    v1,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveNoChildrenHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 0, EnvironmentSound_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, EnvironmentSound_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, EnvironmentSound_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))EnvironmentSound_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eUpdateInternalDataQTaskEvent,
    EnvironmentSound_UpdateInternalDataHandler);
  v2 = (struct ParameterList_s *)Mem_AllocFn(112, 4);
  v2->ptParameterListItem = (struct ParameterListItem_s *)&v2[1];
  v3 = Level_eParameterTypebool8;
  v2->nParameters = 0;
  v2->nMaxParameters = 5;
  EnvironmentSound_ptParameterList = v2;
  ParameterList_AddParameter(v2, 0x28u, v3, "Ecco on", 7u, nullptr);
  ParameterList_AddParameter(EnvironmentSound_ptParameterList, 0x29u, Level_eParameterTypebool8, "Rain on", 7u, nullptr);
  ParameterList_AddParameter(EnvironmentSound_ptParameterList, 0x2Au, Level_eParameterTypebool8, "Sea on", 7u, nullptr);
  ParameterList_AddParameter(EnvironmentSound_ptParameterList, 0x2Bu, Level_eParameterTypebool8, "Wind on", 7u, nullptr);
  ParameterList_AddParameter(
    EnvironmentSound_ptParameterList,
    0x2Cu,
    Level_eParameterTypeString16,
    "Ambient rain sound",
    7u,
    nullptr);
}

// source: j/0/effects/environmentsound.c:604  [size]
void __cdecl EnvironmentSound_Close()
{
  int v0; // esi

  if ( EnvironmentSound_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&EnvironmentSound_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(EnvironmentSound_eQTaskType);
}

// source: j/0/effects/environmentsound.c:621  [size]
unsigned __int16 __cdecl EnvironmentSound_GetQTaskType()
{
  return EnvironmentSound_eQTaskType;
}

// source: j/0/effects/environmentsound.c:635  [size]
struct QCamera_s *__cdecl EnvironmentSound_SetCamera(struct QCamera_s *ptQCamera)
{
  EnvironmentSound_ptCamera = ptQCamera;
  return ptQCamera;
}

void __cdecl qr_basic_callback__(char *Buffer, size_t BufferCount)
{
  _snprintf(
    Buffer,
    BufferCount,
    "\\gamename\\%s\\gamever\\%s\\location\\%d",
    "projectigi2r",
    g_zPlayer1,
    gamedata.locationid);
}
