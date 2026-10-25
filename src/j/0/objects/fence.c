/* j/0/objects/fence.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/objects/fence.c:48  [anchor-mhash]
void __cdecl Fence_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[24]; struct real64x3_t tNull; };
    char igi2_extent[52];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v2; // st7
  double v3; // st7
  int *v4; // eax
  int v5; // eax
  double v6; // st6
  __int16 v7; // cx

  memset(&igi2_frame.tNull, 0, sizeof(igi2_frame.tNull));
  QTaskList_Register(GameFunctions_ptActivateQTaskList, (struct QTaskList_s *)ptQTask);
  QTaskList_Register(GameFunctions_ptNotifyQTaskList, (struct QTaskList_s *)ptQTask);
  ModelObj_Init((struct ModelObj_s *)ptQTask, Game_ptGame->ptWorld, nullptr);
  ptQTask[7].tQTaskChildren.ptHead = nullptr;
  ptQTask[7].tQTaskChildren.ptMiddle = (struct QTask_s *)2;
  ptQTask[7].tQTaskRefList.ptHead = nullptr;
  ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[7].tQTaskRefList.ptTail = nullptr;
  ptQTask[7].ptParent = nullptr;
  *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
    v2 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  else
    v2 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  if ( v2 >= *(float *)&ptQTask[6].ptPrev )
  {
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
      v3 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v3 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  }
  else
  {
    v3 = *(float *)&ptQTask[6].ptPrev;
  }
  v4 = *(int **)&ptQTask[2].eQTaskType;
  if ( v4 && (v5 = *v4) != 0 )
    v6 = *(float *)(*(_DWORD *)(*(_DWORD *)(v5 + 12) + 12) + 120);
  else
    v6 = 1.0;
  igi2_frame.ptDynCubeObj = v3 * v6;
  World_RegisterDynCubeObjFirstTimeRadius(
    Game_ptGame->ptWorld,
    (struct DynCubeObj_s *)ptQTask,
    &igi2_frame.tNull,
    igi2_frame.ptDynCubeObj,
    WORLD_DYNCUBETREE_CATEGORY_STATIONARY);
  v7 = Attach_eAttachEvent;
  ptQTask[5].tQTaskChildren.ptTail = (struct QTask_s *)-1;
  ptQTask[8].ptNext = nullptr;
  ptQTask[8].ptPrev = nullptr;
  ptQTask[8].tQTaskChildren.ptHead = nullptr;
  ptQTask[8].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[8].tQTaskChildren.ptTail = nullptr;
  ptQTask[8].tQTaskRefList.ptHead = nullptr;
  ptQTask[8].tQTaskRefList.ptMiddle = nullptr;
  LOBYTE(ptQTask[8].tQTaskRefList.ptTail) = 0;
  LOBYTE(ptQTask[9].ptPrev) = 0;
  BYTE1(ptQTask[9].ptPrev) = 1;
  ptQTask[5].tQTaskRefList.ptHead = nullptr;
  QTask_TriggerQTaskEventParent(ptQTask, v7, &ptQTask[5].tQTaskChildren.ptTail);
  ModelObj_CalcRelativePosAndOrientation((struct ModelObj_s *)ptQTask);
  ptQTask[9].tQTaskChildren.ptHead = nullptr;
  ptQTask[9].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[9].tQTaskChildren.ptTail = nullptr;
  ptQTask[11].ptPrev = nullptr;
  ptQTask[11].tQTaskChildren.ptHead = nullptr;
}

// source: j/0/objects/fence.c:102  [anchor-strings]
void __cdecl Fence_RunHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real32x3_t tMagicPos1; };
    struct { char igi2_o1[16]; struct real64x3_t tSize; };
    struct { char igi2_o2[40]; struct real64x3_t tPos; };
    struct { char igi2_o3[64]; struct real64x3_t Real64x3_Rotate_tTemp; };
    char igi2_extent[88];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v1; // st7
  double v2; // st6
  double v3; // st5
  struct QTask_s *ptHead; // eax
  struct QTask_s *v5; // eax
  void (__cdecl *pfHandler)(struct QTask_s *, _DWORD); // ecx
  struct QTask_s *v7; // ecx
  int v8; // edx
  struct QTask_s *v9; // eax
  void (__cdecl *v10)(struct QTask_s *); // eax
  int v11; // edx

  if ( ptQTask[9].tQTaskChildren.ptHead
    && ptQTask[9].tQTaskChildren.ptMiddle->ptNext
    && ptQTask[9].tQTaskChildren.ptTail )
  {
    *(_QWORD *)&igi2_frame.tMagicPos1.vX = (__int64)Level_RunLevelExpression(
                                           (struct LevelExpression_s *)&ptQTask[9].tQTaskChildren,
                                           ptQTask);
    LOBYTE(ptQTask[9].ptPrev) = LOBYTE(igi2_frame.tMagicPos1.vX);
  }
  else
  {
    LOBYTE(ptQTask[9].ptPrev) = 0;
  }
  if ( ptQTask[11].tQTaskChildren.ptHead )
  {
    if ( !LOBYTE(ptQTask[9].ptPrev) )
    {
      QTask_Delete(ptQTask[11].tQTaskChildren.ptHead);
      ptQTask[11].tQTaskChildren.ptHead = nullptr;
    }
  }
  else if ( LOBYTE(ptQTask[9].ptPrev) )
  {
    ptQTask[11].tQTaskChildren.ptHead = QTask_NewFn(ptQTask, AmbientArea_eQTaskType, nullptr);
    GameFunctions_GetMagicVertexLocal((struct real32x3_t *)&igi2_frame.tSize, ptQTask, 0);
    GameFunctions_GetMagicVertexLocal(&igi2_frame.tMagicPos1, ptQTask, 1);
    v1 = (igi2_frame.tMagicPos1.vX + *(float *)&igi2_frame.tSize.vX) * 0.5;
    v2 = *(float *)&ptQTask[3].ptPrev;
    v3 = *(float *)&ptQTask[3].tQTaskChildren.ptMiddle * 8192.0;
    igi2_frame.tSize.vY = 1.75;
    igi2_frame.tSize.vZ = 2.0;
    igi2_frame.Real64x3_Rotate_tTemp.vX = v2 * v1 + v3 + *(float *)&ptQTask[3].tQTaskChildren.ptHead * 0.0;
    igi2_frame.Real64x3_Rotate_tTemp.vY = *(float *)&ptQTask[3].tQTaskChildren.ptTail * v1
                             + *(float *)&ptQTask[3].tQTaskRefList.ptMiddle * 8192.0
                             + *(float *)&ptQTask[3].tQTaskRefList.ptHead * 0.0;
    igi2_frame.Real64x3_Rotate_tTemp.vZ = *(float *)&ptQTask[3].tQTaskRefList.ptTail * v1
                             + *(float *)&ptQTask[3].eQTaskType * 8192.0
                             + *(float *)&ptQTask[3].ptParent * 0.0;
    qmemcpy(&igi2_frame.tPos, &igi2_frame.Real64x3_Rotate_tTemp, sizeof(igi2_frame.tPos));
    igi2_frame.tPos.vX = igi2_frame.Real64x3_Rotate_tTemp.vX + *(double *)&ptQTask[1].ptNext;
    igi2_frame.tPos.vY = igi2_frame.tPos.vY + *(double *)&ptQTask[1].tQTaskChildren.ptHead;
    ptHead = ptQTask[11].tQTaskChildren.ptHead;
    igi2_frame.tPos.vZ = igi2_frame.tPos.vZ + *(double *)&ptQTask[1].tQTaskChildren.ptTail;
    igi2_frame.tSize.vX = (igi2_frame.tMagicPos1.vX - *(float *)&igi2_frame.tSize.vX) * 0.0001220703125 + 1.5;
    AmbientArea_SetParameters(ptHead, &igi2_frame.tPos, (struct real32x9_t *)&ptQTask[3].ptPrev, &igi2_frame.tSize, 10.0, "elfence_loop");
    v5 = ptQTask[11].tQTaskChildren.ptHead;
    pfHandler = (void (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][v5->eQTaskType].pfHandler;
    if ( pfHandler )
      pfHandler(v5, 0);
  }
  v7 = ptQTask->tQTaskChildren.ptHead;
  if ( v7->ptNext && v7 )
  {
    v8 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( v7->ptNext )
        v9 = v7->ptNext->ptNext != nullptr ? v7->ptNext : nullptr;
      else
        v9 = nullptr;
      QTask_atProtectedQTaskStack[v8].ptQTask = v9;
      v10 = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][v7->eQTaskType].pfHandler;
      v11 = v8 + 1;
      QTask_nProtectedQTaskStackOffset = v11;
      if ( v10 )
      {
        v10(v7);
        v11 = QTask_nProtectedQTaskStackOffset;
      }
      v7 = (struct QTask_s *)dword_849C7DC[v11];
      v8 = v11 - 1;
      QTask_nProtectedQTaskStackOffset = v8;
    }
    while ( v7 );
  }
}

// source: j/0/objects/fence.c:190  [anchor-mhash]
void __cdecl Fence_DeleteHandler(struct QTask_s *ptQTask)
{
  QTaskList_Remove(GameFunctions_ptActivateQTaskList, ptQTask);
  QTaskList_Remove(GameFunctions_ptNotifyQTaskList, ptQTask);
  World_RemoveDynCubeObj(Game_ptGame->ptWorld, (struct DynCubeObj_s *)ptQTask);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[9].tQTaskChildren);
}

// source: j/0/objects/fence.c:219  [size]
void __cdecl Fence_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = Fence_ptParameterList;
}

// source: j/0/objects/fence.c:235  [anchor-mhash]
void __cdecl Fence_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct LODVirModel_s *LODVirModelExistsFn; // eax
  double v4; // st7
  double v5; // st7
  int *v6; // eax
  int v7; // eax
  double v8; // st6
  __int16 v9; // cx
  long double v10; // st7
  long double v11; // st6
  float ptDynCubeObj; // [esp+0h] [ebp-10h]
  struct QTask_s *ptQTaska = *(struct QTask_s * *)&ptQTask; // [esp+14h] [ebp+4h] ARGSLOT

  LODVirModelExistsFn = MTP_GetLODVirModelExistsFn((char *)&ptQTask[8].tQTaskRefList.ptTail);
  if ( LODVirModelExistsFn && LODVirModelExistsFn != *(struct LODVirModel_s **)&ptQTask[2].eQTaskType )
  {
    ModelObj_SetLODVirModel((struct ModelObj_s *)ptQTask, LODVirModelExistsFn, false);
    ptQTask[7].tQTaskRefList.ptHead = nullptr;
    ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
    ptQTask[7].tQTaskRefList.ptTail = nullptr;
    ptQTask[7].ptParent = nullptr;
    *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  }
  if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
    v4 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  else
    v4 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  if ( v4 >= *(float *)&ptQTask[6].ptPrev )
  {
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
      v5 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v5 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  }
  else
  {
    v5 = *(float *)&ptQTask[6].ptPrev;
  }
  v6 = *(int **)&ptQTask[2].eQTaskType;
  if ( v6 && (v7 = *v6) != 0 )
    v8 = *(float *)(*(_DWORD *)(*(_DWORD *)(v7 + 12) + 12) + 120);
  else
    v8 = 1.0;
  ptDynCubeObj = v5 * v8;
  World_MoveDynCubeObjRadius(
    Game_ptGame->ptWorld,
    (struct DynCubeObj_s *)ptQTask,
    (struct real64x3_t *)&ptQTask[8],
    ptDynCubeObj);
  ptQTaska = (struct QTask_s *)ptQTask[8].tQTaskRefList.ptMiddle;
  v9 = Attach_eAttachEvent;
  v10 = sin(*(float *)&ptQTaska);
  ptQTask[3].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[3].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[3].tQTaskRefList.ptTail = nullptr;
  ptQTask[3].ptParent = nullptr;
  *(_DWORD *)&ptQTask[3].eQTaskType = 1065353216;
  ptQTask[4].ptNext = nullptr;
  v11 = cos(*(float *)&ptQTaska);
  *(float *)&ptQTask[3].ptPrev = v11;
  *(float *)&ptQTask[3].tQTaskChildren.ptHead = -v10;
  *(float *)&ptQTask[3].tQTaskChildren.ptTail = v10;
  *(float *)&ptQTask[3].tQTaskRefList.ptHead = v11;
  ptQTask[5].tQTaskChildren.ptTail = (struct QTask_s *)-1;
  ptQTask[5].tQTaskRefList.ptHead = nullptr;
  QTask_TriggerQTaskEventParent(ptQTask, v9, &ptQTask[5].tQTaskChildren.ptTail);
  ModelObj_CalcRelativePosAndOrientation((struct ModelObj_s *)ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[9].tQTaskChildren, ptQTask);
}

// source: j/0/objects/fence.c:310  [size]
void __cdecl Fence_UpdateAttachmentHandler(struct QTask_s *ptQTask)
{
  float v1; // ecx
  struct QTask_s *v2; // edi
  long double v3; // st7
  long double v4; // st6
  float vAlpha; // [esp+0h] [ebp-4h] BYREF

  vAlpha = v1;
  v2 = ptQTask;
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Attach_eUpdateAttachmentEvent][RigidDynCubeObj_eQTaskType].pfHandler)(ptQTask);
  Real32x9_GetAngles(
    (struct real32x9_t *)&v2[3].ptPrev,
    &vAlpha,
    (float *)&ptQTask,
    (float *)&v2[8].tQTaskRefList.ptMiddle);
  ptQTask = (struct QTask_s *)v2[8].tQTaskRefList.ptMiddle;
  v3 = sin(*(float *)&ptQTask);
  v2[3].tQTaskChildren.ptMiddle = nullptr;
  v2[3].tQTaskRefList.ptMiddle = nullptr;
  v2[3].tQTaskRefList.ptTail = nullptr;
  v2[3].ptParent = nullptr;
  *(_DWORD *)&v2[3].eQTaskType = 1065353216;
  v2[4].ptNext = nullptr;
  v4 = cos(*(float *)&ptQTask);
  *(float *)&v2[3].ptPrev = v4;
  *(float *)&v2[3].tQTaskChildren.ptHead = -v3;
  *(float *)&v2[3].tQTaskChildren.ptTail = v3;
  *(float *)&v2[3].tQTaskRefList.ptHead = v4;
  qmemcpy(&v2[8], &v2[1], 0x18u);
}

// source: j/0/objects/fence.c:336  [anchor-mhash]
void __cdecl Fence_NotifyHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real32x3_t tMagicPos0; };
    struct { char igi2_o1[12]; struct real32x3_t tMagicPos1; };
    struct { char igi2_o2[24]; struct real64x3_t Real64x3_RotateInverse_tTemp; };
    char igi2_extent[52];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // edi
  double v3; // st7
  double v4; // st6
  double v5; // st5
  double vY; // st7
  void (__cdecl *pfHandler)(int, _DWORD); // eax

  v2 = *(_DWORD *)pxContext;
  if ( LOBYTE(ptQTask[9].ptPrev) )
  {
    v3 = *((double *)pxContext + 1) - *(double *)&ptQTask[1].ptNext;
    v4 = *((double *)pxContext + 2) - *(double *)&ptQTask[1].tQTaskChildren.ptHead;
    v5 = *((double *)pxContext + 3) - *(double *)&ptQTask[1].tQTaskChildren.ptTail;
    igi2_frame.Real64x3_RotateInverse_tTemp.vX = *(float *)&ptQTask[3].tQTaskRefList.ptTail * v5
                                    + *(float *)&ptQTask[3].tQTaskChildren.ptTail * v4
                                    + *(float *)&ptQTask[3].ptPrev * v3;
    igi2_frame.Real64x3_RotateInverse_tTemp.vY = *(float *)&ptQTask[3].ptParent * v5
                                    + *(float *)&ptQTask[3].tQTaskRefList.ptHead * v4
                                    + *(float *)&ptQTask[3].tQTaskChildren.ptHead * v3;
    igi2_frame.Real64x3_RotateInverse_tTemp.vZ = *(float *)&ptQTask[3].eQTaskType * v5
                                    + *(float *)&ptQTask[3].tQTaskRefList.ptMiddle * v4
                                    + *(float *)&ptQTask[3].tQTaskChildren.ptMiddle * v3;
    GameFunctions_GetMagicVertexLocal(&igi2_frame.tMagicPos0, ptQTask, 0);
    GameFunctions_GetMagicVertexLocal(&igi2_frame.tMagicPos1, ptQTask, 1);
    if ( igi2_frame.tMagicPos0.vX - 2457.60009765625 < igi2_frame.Real64x3_RotateInverse_tTemp.vX
      && igi2_frame.tMagicPos1.vX + 2457.60009765625 > igi2_frame.Real64x3_RotateInverse_tTemp.vX )
    {
      vY = igi2_frame.Real64x3_RotateInverse_tTemp.vY;
      if ( igi2_frame.Real64x3_RotateInverse_tTemp.vY < 0.0 )
        vY = -igi2_frame.Real64x3_RotateInverse_tTemp.vY;
      if ( vY < 2457.60009765625
        && igi2_frame.Real64x3_RotateInverse_tTemp.vZ < 12288.0
        && igi2_frame.Real64x3_RotateInverse_tTemp.vZ > -4096.0 )
      {
        pfHandler = (void (__cdecl *)(int, _DWORD))QTask_aatQTaskFinalEvent[GameFunctions_eElectricDamageQTaskEvent][*(unsigned __int16 *)(v2 + 36)].pfHandler;
        if ( pfHandler )
          pfHandler(v2, 0);
      }
    }
  }
}

// source: j/0/objects/fence.c:397  [anchor-mhash]
void __cdecl Fence_EvaluateActivateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real32x3_t tMagicPos1; };
    struct { char igi2_o1[12]; struct real32x3_t tMagicPos0; };
    struct { char igi2_o2[24]; struct real64x3_t Real64x3_RotateInverse_tTemp; };
    char igi2_extent[52];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v2; // st7
  double v3; // st6
  double v4; // st5
  double vY; // st7
  float v6; // ecx
  float v7; // edx
  struct QReference_s *ptHead; // ecx
  struct QTask_s *ptParent; // edx

  if ( !LOBYTE(ptQTask[9].ptPrev) && BYTE1(ptQTask[9].ptPrev) )
  {
    v2 = *((double *)pxContext + 1) - *(double *)&ptQTask[1].ptNext;
    v3 = *((double *)pxContext + 2) - *(double *)&ptQTask[1].tQTaskChildren.ptHead;
    v4 = *((double *)pxContext + 3) - *(double *)&ptQTask[1].tQTaskChildren.ptTail;
    igi2_frame.Real64x3_RotateInverse_tTemp.vX = *(float *)&ptQTask[3].tQTaskRefList.ptTail * v4
                                    + *(float *)&ptQTask[3].tQTaskChildren.ptTail * v3
                                    + *(float *)&ptQTask[3].ptPrev * v2;
    igi2_frame.Real64x3_RotateInverse_tTemp.vY = *(float *)&ptQTask[3].ptParent * v4
                                    + *(float *)&ptQTask[3].tQTaskChildren.ptHead * v2
                                    + *(float *)&ptQTask[3].tQTaskRefList.ptHead * v3;
    GameFunctions_GetMagicVertexLocal(&igi2_frame.tMagicPos0, ptQTask, 0);
    GameFunctions_GetMagicVertexLocal(&igi2_frame.tMagicPos1, ptQTask, 1);
    vY = igi2_frame.Real64x3_RotateInverse_tTemp.vY;
    if ( igi2_frame.Real64x3_RotateInverse_tTemp.vY < 0.0 )
      vY = -igi2_frame.Real64x3_RotateInverse_tTemp.vY;
    if ( vY < *((double *)pxContext + 15)
      && igi2_frame.tMagicPos0.vX < igi2_frame.Real64x3_RotateInverse_tTemp.vX
      && igi2_frame.tMagicPos1.vX > igi2_frame.Real64x3_RotateInverse_tTemp.vX )
    {
      v6 = *((float *)pxContext + 12);
      v7 = *((float *)pxContext + 15);
      igi2_frame.tMagicPos0.vX = *((float *)pxContext + 9);
      LODWORD(igi2_frame.tMagicPos1.vX) = ptQTask[3].tQTaskChildren.ptHead;
      igi2_frame.tMagicPos0.vY = v6;
      ptHead = ptQTask[3].tQTaskRefList.ptHead;
      igi2_frame.tMagicPos0.vZ = v7;
      ptParent = ptQTask[3].ptParent;
      LODWORD(igi2_frame.tMagicPos1.vY) = ptHead;
      LODWORD(igi2_frame.tMagicPos1.vZ) = ptParent;
      if ( igi2_frame.Real64x3_RotateInverse_tTemp.vY > 0.0 )
      {
        igi2_frame.tMagicPos1.vX = -igi2_frame.tMagicPos1.vX;
        igi2_frame.tMagicPos1.vY = -igi2_frame.tMagicPos1.vY;
        igi2_frame.tMagicPos1.vZ = -igi2_frame.tMagicPos1.vZ;
      }
      if ( Real32x3_Angle(&igi2_frame.tMagicPos0, &igi2_frame.tMagicPos1) < 1.0471975803375244 )
      {
        *((_DWORD *)pxContext + 28) = 0;
        *((_DWORD *)pxContext + 29) = 0;
        *((_DWORD *)pxContext + 32) = ptQTask;
      }
    }
  }
}

// source: j/0/objects/fence.c:487  [size]
void __cdecl Fence_GetActivateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = 9;
}

// source: j/0/objects/fence.c:504  [size]
void __cdecl Fence_ActivateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: j/0/objects/fence.c:582  [size]
float __cdecl Fence_GetActivateTime()
{
  return 6.0;
}

// source: j/0/objects/fence.c:595  [size]
unsigned __int16 __cdecl Fence_GetQTaskType()
{
  return Fence_eQTaskType;
}

// source: j/0/objects/fence.c:608  [anchor-strings]
void __cdecl Fence_Open()
{
  unsigned __int16 v0; // si
  __int16 v1; // ax
  struct ParameterList_s *v2; // eax
  int v3; // edx

  v0 = QTask_NewQTaskType("Fence", 456, RigidDynCubeObj_eQTaskType, 0, 0);
  Fence_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, Fence_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, Fence_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, Fence_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Fence_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, Fence_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(v0, GameFunctions_eNotifyQTaskEvent, Fence_NotifyHandler);
  QTask_LinkQTaskEventHandlerFn(v0, GameFunctions_eEvaluateActivateQTaskEvent, Fence_EvaluateActivateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    GameFunctions_eGetActivateQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Fence_GetActivateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    GameFunctions_eActivateQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Fence_ActivateHandler);
  v1 = ComputerObject_eDrawComputerObjectQTaskEvent;
  if ( ComputerObject_eDrawComputerObjectQTaskEvent == 512 )
  {
    v1 = QTask_NewQTaskEventFn(0x200u, "DrawComputerObject");
    v0 = Fence_eQTaskType;
    ComputerObject_eDrawComputerObjectQTaskEvent = v1;
  }
  QTask_LinkQTaskEventHandlerFn(v0, v1, nullptr);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Attach_eUpdateAttachmentEvent, Fence_UpdateAttachmentHandler);
  v2 = (struct ParameterList_s *)Mem_AllocFn(112, 4);
  v2->ptParameterListItem = (struct ParameterListItem_s *)&v2[1];
  v3 = Level_eParameterTypeObjectPos;
  v2->nParameters = 0;
  v2->nMaxParameters = 5;
  Fence_ptParameterList = v2;
  ParameterList_AddParameter(v2, 0x140u, v3, "Position", 7u, nullptr);
  ParameterList_AddParameter(Fence_ptParameterList, 0x158u, Level_eParameterTypeAngle, "Gamma", 7u, nullptr);
  ParameterList_AddParameter(Fence_ptParameterList, 0x15Cu, Level_eParameterTypeString16, "Model", 7u, nullptr);
  ParameterList_AddParameter(Fence_ptParameterList, 0x16Du, Level_eParameterTypebool8, "Climbable", 7u, nullptr);
  ParameterList_AddParameter(
    Fence_ptParameterList,
    0x170u,
    Level_eParameterTypeVarString,
    "Electric Expression",
    7u,
    nullptr);
  Symbol_Register(
    "TASKTYPE_FENCE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)Fence_eQTaskType,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}

// source: j/0/objects/fence.c:660  [size]
void __cdecl Fence_Close()
{
  int v0; // esi

  QTask_DeleteQTaskType(Fence_eQTaskType);
  if ( Fence_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&Fence_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
}
