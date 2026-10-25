/* j/0/objects/rotatingobject.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/objects/rotatingobject.c:119  [anchor-mhash]
void __cdecl RotatingObject_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  double v2; // st7
  bool v3; // c0
  bool v4; // c3
  double v5; // st7
  double v6; // st7
  int *v7; // eax
  int v8; // eax
  double v9; // st6
  struct QReference_s *v10; // eax
  float ptDynCubeObj; // [esp+0h] [ebp-18h]

  ModelObj_Init((struct ModelObj_s *)ptQTask, Game_ptGame->ptWorld, nullptr);
  ptQTask[7].tQTaskChildren.ptHead = nullptr;
  ptQTask[7].tQTaskChildren.ptMiddle = (struct QTask_s *)2;
  ptQTask[7].tQTaskRefList.ptHead = nullptr;
  ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[7].tQTaskRefList.ptTail = nullptr;
  ptQTask[7].ptParent = nullptr;
  *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  v2 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  v3 = v2 < *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  v4 = v2 == *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  ptQTask[1].ptNext = nullptr;
  ptQTask[1].ptPrev = nullptr;
  ptQTask[1].tQTaskChildren.ptHead = nullptr;
  ptQTask[1].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[1].tQTaskChildren.ptTail = nullptr;
  ptQTask[1].tQTaskRefList.ptHead = nullptr;
  if ( v3 || v4 )
    v5 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  else
    v5 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  if ( v5 >= *(float *)&ptQTask[6].ptPrev )
  {
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
      v6 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v6 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  }
  else
  {
    v6 = *(float *)&ptQTask[6].ptPrev;
  }
  v7 = *(int **)&ptQTask[2].eQTaskType;
  if ( v7 && (v8 = *v7) != 0 )
    v9 = *(float *)(*(_DWORD *)(*(_DWORD *)(v8 + 12) + 12) + 120);
  else
    v9 = 1.0;
  ptDynCubeObj = v6 * v9;
  World_RegisterDynCubeObjFirstTimeRadius(
    Game_ptGame->ptWorld,
    (struct DynCubeObj_s *)ptQTask,
    (struct real64x3_t *)&ptQTask[1],
    ptDynCubeObj,
    WORLD_DYNCUBETREE_CATEGORY_MOBILE);
  ptQTask[10].ptParent = (struct QTask_s *)1065353216;
  ptQTask[11].tQTaskChildren.ptHead = (struct QTask_s *)1065353216;
  ptQTask[11].tQTaskRefList.ptMiddle = (struct QReference_s *)1065353216;
  ptQTask[11].ptParent = (struct QTask_s *)1065353216;
  ptQTask[12].tQTaskChildren.ptHead = (struct QTask_s *)1065353216;
  ptQTask[12].tQTaskRefList.ptMiddle = (struct QReference_s *)1065353216;
  *(_DWORD *)&ptQTask[10].eQTaskType = 0;
  ptQTask[11].ptNext = nullptr;
  ptQTask[11].ptPrev = nullptr;
  ptQTask[11].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[11].tQTaskChildren.ptTail = nullptr;
  ptQTask[11].tQTaskRefList.ptHead = nullptr;
  ptQTask[11].tQTaskRefList.ptTail = nullptr;
  *(_DWORD *)&ptQTask[11].eQTaskType = 0;
  ptQTask[12].ptNext = nullptr;
  ptQTask[12].ptPrev = nullptr;
  ptQTask[12].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[12].tQTaskChildren.ptTail = nullptr;
  ptQTask[12].tQTaskRefList.ptHead = nullptr;
  ptQTask[12].tQTaskRefList.ptTail = nullptr;
  qmemcpy(&ptQTask[3].ptPrev, &ptQTask[10].ptParent, sizeof(struct QTask_s));
  ptQTask[13].tQTaskChildren.ptTail = nullptr;
  v10 = (struct QReference_s *)Mem_AllocFn(8, 4);
  if ( v10 )
  {
    v10->ptNext = (struct QReference_s *)1;
    v10->ptPrev = nullptr;
  }
  ptQTask[13].tQTaskRefList.ptHead = v10;
  ptQTask[9].tQTaskChildren.ptHead = (struct QTask_s *)1092616192;
  ptQTask[9].tQTaskChildren.ptMiddle = (struct QTask_s *)1092616192;
  ptQTask[9].tQTaskChildren.ptTail = (struct QTask_s *)1092616192;
  LOBYTE(ptQTask[8].ptNext) = 0;
  ptQTask[9].tQTaskRefList.ptHead = (struct QReference_s *)1065353216;
  ptQTask[9].tQTaskRefList.ptMiddle = (struct QReference_s *)1065353216;
  ptQTask[9].tQTaskRefList.ptTail = (struct QReference_s *)1065353216;
  LOBYTE(ptQTask[9].ptParent) = 1;
  ptQTask[13].tQTaskRefList.ptTail = nullptr;
  ptQTask[13].ptParent = nullptr;
  *(_DWORD *)&ptQTask[13].eQTaskType = 0;
  ptQTask[15].tQTaskRefList.ptMiddle = nullptr;
  LOBYTE(ptQTask[13].tQTaskRefList.ptMiddle) = 0;
}

// source: j/0/objects/rotatingobject.c:176  [anchor-mhash]
void __cdecl RotatingObject_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptTail; // eax
  struct QReference_s *ptHead; // eax

  World_RemoveDynCubeObj((struct World_s *)ptQTask[2].ptParent, (struct DynCubeObj_s *)ptQTask);
  ptTail = ptQTask[13].tQTaskChildren.ptTail;
  if ( ptTail )
    QReference_Delete((struct QReference_s *)ptTail, &QTask_tQTaskRefPool);
  ptHead = ptQTask[13].tQTaskRefList.ptHead;
  if ( ptHead )
    SoundSys_DeleteChannelList((struct SoundSysChannelList_t *)ptHead);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[13].tQTaskRefList.ptTail);
}

// source: j/0/objects/rotatingobject.c:211  [anchor-mhash]
void __cdecl RotatingObject_RunHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDest; };
    struct { char igi2_o1[4]; float vAlpha; };
    struct { char igi2_o2[8]; float vBeta; };
    struct { char igi2_o3[24]; float v18; };
    struct { char igi2_o4[28]; float v19; };
    struct { char igi2_o5[36]; struct real32x9_t Real32x9_Multiply_tTemp; };
    char igi2_extent[76];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v1; // st7
  double v2; // st7
  double v3; // st7
  double v4; // st7
  double v5; // st7
  double v6; // st7
  double v7; // st7
  double v8; // st6
  double v9; // st7
  double v10; // st7
  struct real32x9_t *v11; // eax
  double v12; // st7
  struct QReference_s *ptHead; // eax
  struct QReference_s *v14; // ecx

  if ( ptQTask[13].tQTaskRefList.ptTail
    && ptQTask[13].ptParent->ptNext
    && *(_DWORD *)&ptQTask[13].eQTaskType
    && !(unsigned __int8)(__int64)Level_RunLevelExpression(
                                    (struct LevelExpression_s *)&ptQTask[13].tQTaskRefList.ptTail,
                                    ptQTask)
    || LOBYTE(ptQTask[13].tQTaskRefList.ptMiddle) )
  {
    *(_DWORD *)&ptQTask[9].eQTaskType = 0;
    ptQTask[10].ptNext = nullptr;
    ptQTask[10].ptPrev = nullptr;
  }
  if ( *(float *)&ptQTask[10].tQTaskChildren.ptHead != *(float *)&ptQTask[9].eQTaskType )
  {
    if ( *(float *)&ptQTask[10].tQTaskChildren.ptHead >= (double)*(float *)&ptQTask[9].eQTaskType )
    {
      if ( *(float *)&ptQTask[10].tQTaskChildren.ptHead > (double)*(float *)&ptQTask[9].eQTaskType )
      {
        v2 = *(float *)&ptQTask[10].tQTaskChildren.ptHead - *(float *)&ptQTask[9].tQTaskRefList.ptHead * 0.03333333507180214;
        *(float *)&ptQTask[10].tQTaskChildren.ptHead = v2;
        if ( v2 < *(float *)&ptQTask[9].eQTaskType )
          ptQTask[10].tQTaskChildren.ptHead = *(struct QTask_s **)&ptQTask[9].eQTaskType;
      }
    }
    else
    {
      v1 = *(float *)&ptQTask[9].tQTaskRefList.ptHead * 0.03333333507180214 + *(float *)&ptQTask[10].tQTaskChildren.ptHead;
      *(float *)&ptQTask[10].tQTaskChildren.ptHead = v1;
      if ( v1 > *(float *)&ptQTask[9].eQTaskType )
        ptQTask[10].tQTaskChildren.ptHead = *(struct QTask_s **)&ptQTask[9].eQTaskType;
    }
  }
  if ( *(float *)&ptQTask[10].tQTaskChildren.ptMiddle != *(float *)&ptQTask[10].ptNext )
  {
    if ( *(float *)&ptQTask[10].tQTaskChildren.ptMiddle >= (double)*(float *)&ptQTask[10].ptNext )
    {
      if ( *(float *)&ptQTask[10].tQTaskChildren.ptMiddle > (double)*(float *)&ptQTask[10].ptNext )
      {
        v4 = *(float *)&ptQTask[10].tQTaskChildren.ptMiddle - *(float *)&ptQTask[9].tQTaskRefList.ptMiddle * 0.03333333507180214;
        *(float *)&ptQTask[10].tQTaskChildren.ptMiddle = v4;
        if ( v4 < *(float *)&ptQTask[10].ptNext )
          ptQTask[10].tQTaskChildren.ptMiddle = ptQTask[10].ptNext;
      }
    }
    else
    {
      v3 = *(float *)&ptQTask[9].tQTaskRefList.ptMiddle * 0.03333333507180214 + *(float *)&ptQTask[10].tQTaskChildren.ptMiddle;
      *(float *)&ptQTask[10].tQTaskChildren.ptMiddle = v3;
      if ( v3 > *(float *)&ptQTask[10].ptNext )
        ptQTask[10].tQTaskChildren.ptMiddle = ptQTask[10].ptNext;
    }
  }
  if ( *(float *)&ptQTask[10].tQTaskChildren.ptTail != *(float *)&ptQTask[10].ptPrev )
  {
    if ( *(float *)&ptQTask[10].tQTaskChildren.ptTail >= (double)*(float *)&ptQTask[10].ptPrev )
    {
      if ( *(float *)&ptQTask[10].tQTaskChildren.ptTail > (double)*(float *)&ptQTask[10].ptPrev )
      {
        v6 = *(float *)&ptQTask[10].tQTaskChildren.ptTail - *(float *)&ptQTask[9].tQTaskRefList.ptTail * 0.03333333507180214;
        *(float *)&ptQTask[10].tQTaskChildren.ptTail = v6;
        if ( v6 < *(float *)&ptQTask[10].ptPrev )
          ptQTask[10].tQTaskChildren.ptTail = ptQTask[10].ptPrev;
      }
    }
    else
    {
      v5 = *(float *)&ptQTask[9].tQTaskRefList.ptTail * 0.03333333507180214 + *(float *)&ptQTask[10].tQTaskChildren.ptTail;
      *(float *)&ptQTask[10].tQTaskChildren.ptTail = v5;
      if ( v5 > *(float *)&ptQTask[10].ptPrev )
        ptQTask[10].tQTaskChildren.ptTail = ptQTask[10].ptPrev;
    }
  }
  igi2_frame.v18 = *(float *)&ptQTask[10].tQTaskChildren.ptHead * 0.03333333507180214 + *(float *)&ptQTask[10].tQTaskRefList.ptHead;
  *(float *)&ptQTask[10].tQTaskRefList.ptHead = igi2_frame.v18;
  v7 = *(float *)&ptQTask[10].tQTaskChildren.ptMiddle * 0.03333333507180214 + *(float *)&ptQTask[10].tQTaskRefList.ptMiddle;
  *(float *)&ptQTask[10].tQTaskRefList.ptMiddle = v7;
  igi2_frame.v19 = *(float *)&ptQTask[10].tQTaskChildren.ptTail * 0.03333333507180214 + *(float *)&ptQTask[10].tQTaskRefList.ptTail;
  *(float *)&ptQTask[10].tQTaskRefList.ptTail = igi2_frame.v19;
  if ( igi2_frame.v18 >= 360.0 )
  {
    v8 = *(float *)&ptQTask[10].tQTaskRefList.ptHead;
    do
      v8 = v8 - 360.0;
    while ( v8 >= 360.0 );
    *(float *)&ptQTask[10].tQTaskRefList.ptHead = v8;
  }
  if ( v7 >= 360.0 )
  {
    v9 = *(float *)&ptQTask[10].tQTaskRefList.ptMiddle;
    do
      v9 = v9 - 360.0;
    while ( v9 >= 360.0 );
    *(float *)&ptQTask[10].tQTaskRefList.ptMiddle = v9;
  }
  if ( igi2_frame.v19 >= 360.0 )
  {
    v10 = *(float *)&ptQTask[10].tQTaskRefList.ptTail;
    do
      v10 = v10 - 360.0;
    while ( v10 >= 360.0 );
    *(float *)&ptQTask[10].tQTaskRefList.ptTail = v10;
  }
  igi2_frame.vBeta = *(float *)&ptQTask[10].tQTaskRefList.ptTail * 0.01745329238474369;
  igi2_frame.vAlpha = *(float *)&ptQTask[10].tQTaskRefList.ptMiddle * 0.01745329238474369;
  igi2_frame.ptDest = *(float *)&ptQTask[10].tQTaskRefList.ptHead * 0.01745329238474369;
  v11 = Real32x9_Create((struct real32x9_t *)&ptQTask[11].ptParent, igi2_frame.ptDest, igi2_frame.vAlpha, igi2_frame.vBeta);
  igi2_frame.Real32x9_Multiply_tTemp.tX.vX = v11->tX.vX * *(float *)&ptQTask[10].ptParent
                                + *(float *)&ptQTask[11].ptNext * *(float *)&ptQTask[12].tQTaskChildren.ptTail
                                + *(float *)&ptQTask[10].eQTaskType * *(float *)&ptQTask[12].ptPrev;
  igi2_frame.Real32x9_Multiply_tTemp.tX.vY = *(float *)&ptQTask[10].eQTaskType * *(float *)&ptQTask[12].tQTaskChildren.ptHead
                                + *(float *)&ptQTask[11].ptNext * *(float *)&ptQTask[12].tQTaskRefList.ptHead
                                + *(float *)&ptQTask[10].ptParent * *(float *)&ptQTask[11].eQTaskType;
  igi2_frame.Real32x9_Multiply_tTemp.tX.vZ = *(float *)&ptQTask[10].eQTaskType * *(float *)&ptQTask[12].tQTaskChildren.ptMiddle
                                + *(float *)&ptQTask[11].ptNext * *(float *)&ptQTask[12].tQTaskRefList.ptMiddle
                                + *(float *)&ptQTask[10].ptParent * *(float *)&ptQTask[12].ptNext;
  igi2_frame.Real32x9_Multiply_tTemp.tY.vX = *(float *)&ptQTask[11].tQTaskChildren.ptMiddle
                                * *(float *)&ptQTask[12].tQTaskChildren.ptTail
                                + *(float *)&ptQTask[12].ptPrev * *(float *)&ptQTask[11].tQTaskChildren.ptHead
                                + v11->tX.vX * *(float *)&ptQTask[11].ptPrev;
  igi2_frame.Real32x9_Multiply_tTemp.tY.vY = *(float *)&ptQTask[12].tQTaskRefList.ptHead
                                * *(float *)&ptQTask[11].tQTaskChildren.ptMiddle
                                + *(float *)&ptQTask[11].eQTaskType * *(float *)&ptQTask[11].ptPrev
                                + *(float *)&ptQTask[12].tQTaskChildren.ptHead
                                * *(float *)&ptQTask[11].tQTaskChildren.ptHead;
  igi2_frame.Real32x9_Multiply_tTemp.tY.vZ = *(float *)&ptQTask[12].tQTaskRefList.ptMiddle
                                * *(float *)&ptQTask[11].tQTaskChildren.ptMiddle
                                + *(float *)&ptQTask[12].ptNext * *(float *)&ptQTask[11].ptPrev
                                + *(float *)&ptQTask[12].tQTaskChildren.ptMiddle
                                * *(float *)&ptQTask[11].tQTaskChildren.ptHead;
  v12 = *(float *)&ptQTask[11].tQTaskRefList.ptMiddle * *(float *)&ptQTask[12].tQTaskChildren.ptTail
      + *(float *)&ptQTask[11].tQTaskChildren.ptTail * v11->tX.vX
      + *(float *)&ptQTask[11].tQTaskRefList.ptHead * *(float *)&ptQTask[12].ptPrev;
  ptHead = ptQTask[13].tQTaskRefList.ptHead;
  igi2_frame.Real32x9_Multiply_tTemp.nOps = (int)&ptQTask[12].tQTaskRefList.ptTail->ptNext
                               + (unsigned int)ptQTask[11].tQTaskRefList.ptTail
                               + 1;
  igi2_frame.Real32x9_Multiply_tTemp.tZ.vX = v12;
  igi2_frame.Real32x9_Multiply_tTemp.tZ.vY = *(float *)&ptQTask[11].tQTaskRefList.ptHead
                                * *(float *)&ptQTask[12].tQTaskChildren.ptHead
                                + *(float *)&ptQTask[11].tQTaskRefList.ptMiddle
                                * *(float *)&ptQTask[12].tQTaskRefList.ptHead
                                + *(float *)&ptQTask[11].tQTaskChildren.ptTail * *(float *)&ptQTask[11].eQTaskType;
  igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ = *(float *)&ptQTask[11].tQTaskRefList.ptHead
                                * *(float *)&ptQTask[12].tQTaskChildren.ptMiddle
                                + *(float *)&ptQTask[11].tQTaskRefList.ptMiddle
                                * *(float *)&ptQTask[12].tQTaskRefList.ptMiddle
                                + *(float *)&ptQTask[11].tQTaskChildren.ptTail * *(float *)&ptQTask[12].ptNext;
  qmemcpy(&ptQTask[3].ptPrev, &igi2_frame.Real32x9_Multiply_tTemp, sizeof(struct QTask_s));
  if ( ptHead )
  {
    *(float *)&ptHead->ptPrev = *(float *)&ptQTask[10].tQTaskChildren.ptTail
                              / *(float *)&ptQTask[9].tQTaskChildren.ptTail
                              + *(float *)&ptQTask[10].tQTaskChildren.ptMiddle
                              / *(float *)&ptQTask[9].tQTaskChildren.ptMiddle
                              + *(float *)&ptQTask[10].tQTaskChildren.ptHead
                              / *(float *)&ptQTask[9].tQTaskChildren.ptHead;
    v14 = ptQTask[13].tQTaskRefList.ptHead;
    if ( *(float *)&v14->ptPrev < 0.0 )
    {
      v14->ptPrev = nullptr;
      RigidDynCubeObj_UpdateAttachments((struct RigidDynCubeObj_t *)ptQTask);
      return;
    }
    if ( *(float *)&v14->ptPrev > 1.0 )
      v14->ptPrev = (struct QReference_s *)1065353216;
  }
  RigidDynCubeObj_UpdateAttachments((struct RigidDynCubeObj_t *)ptQTask);
}

// source: j/0/objects/rotatingobject.c:307  [anchor-mhash]
void __cdecl RotatingObject_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct LODVirModel_s *LODVirModelExistsFn; // eax
  double v3; // st7
  double v4; // st7
  int *v5; // eax
  int v6; // eax
  double v7; // st6
  struct QTask_s *ptTail; // eax
  struct QTask_s *ptMiddle; // edx
  struct QTask_s *ptHead; // ecx
  struct QTask_s *v11; // eax
  struct QTask_s *v12; // eax
  struct QTask_s *v13; // eax
  __int16 v14; // cx
  float ptDynCubeObj; // [esp+0h] [ebp-14h]

  qmemcpy(&ptQTask[10].ptParent, &ptQTask[3].ptPrev, sizeof(struct QTask_s));
  LODVirModelExistsFn = MTP_GetLODVirModelExistsFn((char *)&ptQTask[8].ptParent);
  if ( LODVirModelExistsFn != *(struct LODVirModel_s **)&ptQTask[2].eQTaskType )
  {
    ModelObj_SetLODVirModel((struct ModelObj_s *)ptQTask, LODVirModelExistsFn, false);
    ptQTask[7].tQTaskRefList.ptHead = nullptr;
    ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
    ptQTask[7].tQTaskRefList.ptTail = nullptr;
    ptQTask[7].ptParent = nullptr;
    *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  }
  if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
    v3 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  else
    v3 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  if ( v3 >= *(float *)&ptQTask[6].ptPrev )
  {
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
      v4 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v4 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  }
  else
  {
    v4 = *(float *)&ptQTask[6].ptPrev;
  }
  v5 = *(int **)&ptQTask[2].eQTaskType;
  if ( v5 && (v6 = *v5) != 0 )
    v7 = *(float *)(*(_DWORD *)(*(_DWORD *)(v6 + 12) + 12) + 120);
  else
    v7 = 1.0;
  ptDynCubeObj = v4 * v7;
  World_MoveDynCubeObjRadius(
    Game_ptGame->ptWorld,
    (struct DynCubeObj_s *)ptQTask,
    (struct real64x3_t *)&ptQTask[12].ptParent,
    ptDynCubeObj);
  ptTail = ptQTask[9].tQTaskChildren.ptTail;
  ptMiddle = ptQTask[9].tQTaskChildren.ptMiddle;
  qmemcpy(&ptQTask[3].ptPrev, &ptQTask[10].ptParent, sizeof(struct QTask_s));
  ptHead = ptQTask[9].tQTaskChildren.ptHead;
  ptQTask[10].ptPrev = ptTail;
  ptQTask[10].tQTaskChildren.ptTail = ptTail;
  v11 = ptQTask[13].tQTaskChildren.ptTail;
  *(_DWORD *)&ptQTask[9].eQTaskType = ptHead;
  ptQTask[10].ptNext = ptMiddle;
  ptQTask[10].tQTaskChildren.ptHead = ptHead;
  ptQTask[10].tQTaskChildren.ptMiddle = ptMiddle;
  ptQTask[10].tQTaskRefList.ptHead = nullptr;
  ptQTask[10].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[10].tQTaskRefList.ptTail = nullptr;
  if ( v11 )
  {
    v12 = v11->tQTaskChildren.ptHead;
    if ( v12 )
      QTask_Delete(v12);
    QReference_Delete((struct QReference_s *)ptQTask[13].tQTaskChildren.ptTail, &QTask_tQTaskRefPool);
    ptQTask[13].tQTaskChildren.ptTail = nullptr;
  }
  v13 = SoundSys_NewSoundFn(ptQTask, (char *)&ptQTask[8]);
  if ( v13 )
    ptQTask[13].tQTaskChildren.ptTail = (struct QTask_s *)QTask_NewQTaskRef(v13);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[13].tQTaskRefList.ptTail, ptQTask);
  RigidDynCubeObj_UpdateAttachments((struct RigidDynCubeObj_t *)ptQTask);
  v14 = Attach_eAttachEvent;
  ptQTask[5].tQTaskChildren.ptTail = (struct QTask_s *)-1;
  ptQTask[5].tQTaskRefList.ptHead = nullptr;
  QTask_TriggerQTaskEventParent(ptQTask, v14, &ptQTask[5].tQTaskChildren.ptTail);
  ModelObj_CalcRelativePosAndOrientation((struct ModelObj_s *)ptQTask);
}

// source: j/0/objects/rotatingobject.c:409  [size]
void __cdecl RotatingObject_WeaponHitHandler(struct QTask_s *ptQTask, void *pxContext)
{
  if ( LOBYTE(ptQTask[9].ptParent) )
    LOBYTE(ptQTask[13].tQTaskRefList.ptMiddle) = 1;
}

// source: j/0/objects/rotatingobject.c:431  [size]
void __cdecl RotatingObject_SoundUpdateParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = ptQTask + 1;
  *((_DWORD *)pxContext + 1) = (char *)ptQTask + 124;
  *((_DWORD *)pxContext + 2) = ptQTask[13].tQTaskRefList.ptHead;
}

// source: j/0/objects/rotatingobject.c:455  [size]
void __cdecl RotatingObject_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = RotatingObject_ptParameterList;
}

// source: j/0/objects/rotatingobject.c:530  [anchor-mhash]
void __cdecl RotatingObject_UpdateAttachmentHandler(struct QTask_s *ptQTask)
{
  double v1; // st7
  double v2; // st7
  char *v3; // eax
  double v4; // st7
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptHead; // eax
  int v7; // edx
  int v8; // eax
  struct QTask_s *v9; // ecx
  int v10; // esi
  void (__cdecl *pfHandler)(int); // ecx
  int v12; // eax
  struct QTask_s *v13; // ecx
  struct QTask_s *v14; // edx
  int v15; // esi
  void (__cdecl *v16)(struct QTask_s *); // edx
  int v17; // eax
  struct real32x9_t Real32x9_Multiply_tTemp; // [esp+4h] [ebp-28h] BYREF

  if ( ptQTask[2].ptParent )
  {
    ModelObj_UpdateAttachment((struct ModelObj_s *)ptQTask);
    v1 = *(float *)&ptQTask[12].tQTaskChildren.ptTail;
    qmemcpy(&ptQTask[10].ptParent, &ptQTask[3].ptPrev, sizeof(struct QTask_s));
    Real32x9_Multiply_tTemp.tX.vX = v1 * *(float *)&ptQTask[11].ptNext
                                  + *(float *)&ptQTask[12].ptPrev * *(float *)&ptQTask[10].eQTaskType
                                  + *(float *)&ptQTask[10].ptParent * *(float *)&ptQTask[11].ptParent;
    v2 = *(float *)&ptQTask[10].ptParent * *(float *)&ptQTask[11].eQTaskType;
    qmemcpy(&ptQTask[12].ptParent, &ptQTask[1], 0x18u);
    Real32x9_Multiply_tTemp.tX.vY = v2
                                  + *(float *)&ptQTask[11].ptNext * *(float *)&ptQTask[12].tQTaskRefList.ptHead
                                  + *(float *)&ptQTask[12].tQTaskChildren.ptHead * *(float *)&ptQTask[10].eQTaskType;
    Real32x9_Multiply_tTemp.tX.vZ = *(float *)&ptQTask[10].ptParent * *(float *)&ptQTask[12].ptNext
                                  + *(float *)&ptQTask[11].ptNext * *(float *)&ptQTask[12].tQTaskRefList.ptMiddle
                                  + *(float *)&ptQTask[12].tQTaskChildren.ptMiddle * *(float *)&ptQTask[10].eQTaskType;
    Real32x9_Multiply_tTemp.tY.vX = *(float *)&ptQTask[12].tQTaskChildren.ptTail
                                  * *(float *)&ptQTask[11].tQTaskChildren.ptMiddle
                                  + *(float *)&ptQTask[12].ptPrev * *(float *)&ptQTask[11].tQTaskChildren.ptHead
                                  + *(float *)&ptQTask[11].ptParent * *(float *)&ptQTask[11].ptPrev;
    Real32x9_Multiply_tTemp.tY.vY = *(float *)&ptQTask[12].tQTaskChildren.ptHead
                                  * *(float *)&ptQTask[11].tQTaskChildren.ptHead
                                  + *(float *)&ptQTask[12].tQTaskRefList.ptHead
                                  * *(float *)&ptQTask[11].tQTaskChildren.ptMiddle
                                  + *(float *)&ptQTask[11].eQTaskType * *(float *)&ptQTask[11].ptPrev;
    Real32x9_Multiply_tTemp.tY.vZ = *(float *)&ptQTask[12].tQTaskChildren.ptMiddle
                                  * *(float *)&ptQTask[11].tQTaskChildren.ptHead
                                  + *(float *)&ptQTask[12].tQTaskRefList.ptMiddle
                                  * *(float *)&ptQTask[11].tQTaskChildren.ptMiddle
                                  + *(float *)&ptQTask[12].ptNext * *(float *)&ptQTask[11].ptPrev;
    v3 = (char *)&ptQTask[12].tQTaskRefList.ptTail->ptNext + (unsigned int)ptQTask[11].tQTaskRefList.ptTail + 1;
    Real32x9_Multiply_tTemp.tZ.vX = *(float *)&ptQTask[12].tQTaskChildren.ptTail
                                  * *(float *)&ptQTask[11].tQTaskRefList.ptMiddle
                                  + *(float *)&ptQTask[12].ptPrev * *(float *)&ptQTask[11].tQTaskRefList.ptHead
                                  + *(float *)&ptQTask[11].tQTaskChildren.ptTail * *(float *)&ptQTask[11].ptParent;
    v4 = *(float *)&ptQTask[11].tQTaskRefList.ptMiddle;
    Real32x9_Multiply_tTemp.nOps = (int)v3;
    ptNext = ptQTask[3].ptNext;
    Real32x9_Multiply_tTemp.tZ.vY = v4 * *(float *)&ptQTask[12].tQTaskRefList.ptHead
                                  + *(float *)&ptQTask[11].tQTaskChildren.ptTail * *(float *)&ptQTask[11].eQTaskType
                                  + *(float *)&ptQTask[12].tQTaskChildren.ptHead
                                  * *(float *)&ptQTask[11].tQTaskRefList.ptHead;
    Real32x9_Multiply_tTemp.tZ.vZ = *(float *)&ptQTask[11].tQTaskRefList.ptMiddle
                                  * *(float *)&ptQTask[12].tQTaskRefList.ptMiddle
                                  + *(float *)&ptQTask[11].tQTaskChildren.ptTail * *(float *)&ptQTask[12].ptNext
                                  + *(float *)&ptQTask[12].tQTaskChildren.ptMiddle
                                  * *(float *)&ptQTask[11].tQTaskRefList.ptHead;
    qmemcpy(&ptQTask[3].ptPrev, &Real32x9_Multiply_tTemp, sizeof(struct QTask_s));
    if ( ptNext && (ptHead = ptNext->tQTaskChildren.ptHead, ptHead->ptNext) && (v7 = (int)ptHead) != 0 )
    {
      v8 = QTask_nProtectedQTaskStackOffset;
      do
      {
        if ( *(_DWORD *)v7 )
          v9 = **(_DWORD **)v7 != 0 ? *(struct QTask_s **)v7 : nullptr;
        else
          v9 = nullptr;
        v10 = Attach_eUpdateAttachmentEvent;
        QTask_atProtectedQTaskStack[v8].ptQTask = v9;
        pfHandler = (void (__cdecl *)(int))QTask_aatQTaskFinalEvent[v10][*(unsigned __int16 *)(v7 + 36)].pfHandler;
        v12 = v8 + 1;
        QTask_nProtectedQTaskStackOffset = v12;
        if ( pfHandler )
        {
          pfHandler(v7);
          v12 = QTask_nProtectedQTaskStackOffset;
        }
        v7 = dword_849C7DC[v12];
        v8 = v12 - 1;
        QTask_nProtectedQTaskStackOffset = v8;
      }
      while ( v7 );
    }
    else
    {
      v8 = QTask_nProtectedQTaskStackOffset;
    }
    v13 = ptQTask->tQTaskChildren.ptHead;
    if ( v13->ptNext && v13 )
    {
      do
      {
        if ( v13->ptNext )
          v14 = v13->ptNext->ptNext != nullptr ? v13->ptNext : nullptr;
        else
          v14 = nullptr;
        v15 = Attach_eUpdateAttachmentEvent;
        QTask_atProtectedQTaskStack[v8].ptQTask = v14;
        v16 = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[v15][v13->eQTaskType].pfHandler;
        v17 = v8 + 1;
        QTask_nProtectedQTaskStackOffset = v17;
        if ( v16 )
        {
          v16(v13);
          v17 = QTask_nProtectedQTaskStackOffset;
        }
        v13 = (struct QTask_s *)dword_849C7DC[v17];
        v8 = v17 - 1;
        QTask_nProtectedQTaskStackOffset = v8;
      }
      while ( v13 );
    }
  }
}

// source: j/0/objects/rotatingobject.c:569  [anchor-strings]
void __cdecl RotatingObject_Open()
{
  unsigned __int16 v0; // si
  __int16 v1; // ax
  struct ParameterList_s *v2; // eax
  int v3; // edx

  v0 = QTask_NewQTaskType("RotatingObject", 632, RigidDynCubeObj_eQTaskType, 0, 0);
  RotatingObject_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 0, RotatingObject_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, RotatingObject_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, RotatingObject_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eUpdateInternalDataQTaskEvent,
    RotatingObject_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    GameFunctions_eWeaponHitQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))RotatingObject_WeaponHitHandler);
  v1 = SoundSys_eUpdateParameterListQTaskEvent;
  if ( SoundSys_eUpdateParameterListQTaskEvent == 512 )
  {
    v1 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.nRealFadeCount);
    v0 = RotatingObject_eQTaskType;
    SoundSys_eUpdateParameterListQTaskEvent = v1;
  }
  QTask_LinkQTaskEventHandlerFn(v0, v1, RotatingObject_SoundUpdateParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))RotatingObject_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Attach_eUpdateAttachmentEvent, RotatingObject_UpdateAttachmentHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  v2 = (struct ParameterList_s *)Mem_AllocFn(252, 4);
  v2->ptParameterListItem = (struct ParameterListItem_s *)&v2[1];
  v3 = Level_eParameterTypeObjectPos;
  v2->nParameters = 0;
  v2->nMaxParameters = 12;
  RotatingObject_ptParameterList = v2;
  ParameterList_AddParameter(v2, 0x200u, v3, "Position", 7u, nullptr);
  ParameterList_AddParameter(
    RotatingObject_ptParameterList,
    0x1B0u,
    Level_eParameterTypeReal32x9,
    "Orientation",
    7u,
    nullptr);
  ParameterList_AddParameter(RotatingObject_ptParameterList, 0x160u, Level_eParameterTypeString16, "Model", 7u, nullptr);
  ParameterList_AddParameter(
    RotatingObject_ptParameterList,
    0x140u,
    Level_eParameterTypeString16,
    "Rotate sound",
    7u,
    nullptr);
  ParameterList_AddParameter(
    RotatingObject_ptParameterList,
    0x170u,
    Level_eParameterTypeDegrees,
    "Degrees per second X-axis",
    7u,
    nullptr);
  ParameterList_AddParameter(
    RotatingObject_ptParameterList,
    0x174u,
    Level_eParameterTypeDegrees,
    "Degrees per second Y-axis",
    7u,
    nullptr);
  ParameterList_AddParameter(
    RotatingObject_ptParameterList,
    0x178u,
    Level_eParameterTypeDegrees,
    "Degrees per second Z-axis",
    7u,
    nullptr);
  ParameterList_AddParameter(
    RotatingObject_ptParameterList,
    0x17Cu,
    Level_eParameterTypeDegrees,
    "Acceleration, degrees per second X-axis",
    7u,
    nullptr);
  ParameterList_AddParameter(
    RotatingObject_ptParameterList,
    0x180u,
    Level_eParameterTypeDegrees,
    "Acceleration, degrees per second Y-axis",
    7u,
    nullptr);
  ParameterList_AddParameter(
    RotatingObject_ptParameterList,
    0x184u,
    Level_eParameterTypeDegrees,
    "Acceleration, degrees per second Z-axis",
    7u,
    nullptr);
  ParameterList_AddParameter(
    RotatingObject_ptParameterList,
    0x188u,
    Level_eParameterTypebool8,
    "Destructable",
    7u,
    nullptr);
  ParameterList_AddParameter(
    RotatingObject_ptParameterList,
    0x224u,
    Level_eParameterTypeVarString,
    "On expression",
    7u,
    nullptr);
}

// source: j/0/objects/rotatingobject.c:619  [size]
void __cdecl RotatingObject_Close()
{
  int v0; // esi

  if ( RotatingObject_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&RotatingObject_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(RotatingObject_eQTaskType);
}
