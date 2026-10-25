/* j/0/objects/alarmlight.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/objects/alarmlight.c:141  [anchor-mhash]
void __cdecl AlarmLight_ReflectorRegisterLight(
        struct AlarmLightReflector_s *ptAlarmLightReflector,
        int iMagicVertex)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vY4; };
    struct { char igi2_o1[36]; float vZ; };
    struct { char igi2_o2[40]; float vY3; };
    struct { char igi2_o3[44]; struct real32x2_t tSpriteSize; };
    struct { char igi2_o4[52]; struct real32x2_t tScreenPos; };
    struct { char igi2_o5[60]; struct real32x2_t tCorner2; };
    struct { char igi2_o6[68]; struct real32x2_t tCorner1; };
    struct { char igi2_o7[76]; struct real32x2_t tCorner0; };
    struct { char igi2_o8[84]; float v15; };
    struct { char igi2_o9[88]; struct real64x3_t tLightPos; };
    char igi2_extent[116];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptCreator; // esi
  double v3; // st7
  float v4; // ecx
  double v5; // st7
  long double v6; // st7

  ptCreator = ptAlarmLightReflector->tMagicObj.ptCreator;
  GameFunctions_GetMagicVertex(
    &igi2_frame.tLightPos,
    &ptAlarmLightReflector->tMagicObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask,
    iMagicVertex);
  v3 = *(float *)&ptCreator[8].tQTaskRefList.ptTail;
  v4 = *(float *)&ptCreator[9].tQTaskChildren.ptMiddle;
  LODWORD(igi2_frame.tCorner0.vY) = ptCreator[9].ptNext;
  igi2_frame.v15 = v4;
  if ( (TransContext_tActiveTransContext.tPos.vZ - *(double *)&ptCreator[1].tQTaskChildren.ptTail) * v4
     + (TransContext_tActiveTransContext.tPos.vY - *(double *)&ptCreator[1].tQTaskChildren.ptHead) * igi2_frame.tCorner0.vY
     + (TransContext_tActiveTransContext.tPos.vX - *(double *)&ptCreator[1].ptNext) * v3 > 0.0 )
  {
    TransContext_ProjectWorldPos2(&TransContext_tActiveTransContext, &igi2_frame.tScreenPos, &igi2_frame.vZ, &igi2_frame.tLightPos);
    if ( igi2_frame.vZ > 0.0 )
    {
      v5 = 1.0 / igi2_frame.vZ;
      igi2_frame.tSpriteSize.vX = TransContext_tActiveTransContext.vScreenFOVX * v5 * 6144.0;
      igi2_frame.tSpriteSize.vY = TransContext_tActiveTransContext.vScreenFOVY * v5 * 6144.0;
      v6 = fmod(ptAlarmLightReflector->vRotation, 3.1415926535897944) * 0.31830987334251404 - 0.5;
      if ( v6 < 0.0 )
        v6 = -v6;
      igi2_frame.tCorner0.vX = igi2_frame.tScreenPos.vX - igi2_frame.tSpriteSize.vX;
      igi2_frame.tCorner0.vY = igi2_frame.tScreenPos.vY - igi2_frame.tSpriteSize.vY;
      igi2_frame.vY3 = igi2_frame.tScreenPos.vX + igi2_frame.tSpriteSize.vX;
      igi2_frame.tCorner1.vX = igi2_frame.vY3;
      igi2_frame.tScreenPos.vX = igi2_frame.vY3;
      igi2_frame.tCorner1.vY = igi2_frame.tCorner0.vY;
      igi2_frame.tCorner2.vX = igi2_frame.tCorner0.vX;
      igi2_frame.tCorner2.vY = igi2_frame.tScreenPos.vY + igi2_frame.tSpriteSize.vY;
      igi2_frame.tScreenPos.vY = igi2_frame.tCorner2.vY;
      igi2_frame.vY4 = (v6 + v6) * 128.0;
      QSprite_Register4AZ(
        &AlarmLight_ptLightGameSprite->tQSprite,
        igi2_frame.tCorner0.vX,
        igi2_frame.tCorner0.vY,
        igi2_frame.vY3,
        igi2_frame.tCorner0.vY,
        igi2_frame.tCorner0.vX,
        igi2_frame.tCorner2.vY,
        igi2_frame.vY3,
        igi2_frame.tCorner2.vY,
        igi2_frame.vY4,
        0.0,
        0.0,
        0.5,
        igi2_frame.vZ,
        0,
        (unsigned int)&MTP_atLODVirModel[46].atBoneVertexRefs[36].atVertexRefs[235],
        0);
    }
  }
}

// source: j/0/objects/alarmlight.c:241  [anchor-mhash]
void __cdecl AlarmLight_Explode(struct AlarmLight_t *ptAlarmLight)
{
  struct LODVirModel_s *LODVirModelExistsFn; // eax
  struct Mesh3D_LightmapVirModel_t **v3; // esi

  if ( !ptAlarmLight->isDestroyed )
  {
    Explosion0_New(
      &ptAlarmLight->tSectorInteriorObject.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos,
      1,
      0,
      0.05000000074505806,
      4096.0,
      0.0,
      2048.0,
      5,
      2,
      nullptr,
      "1009_01_1",
      ptAlarmLight->azSound[1],
      20,
      0x402u,
      49152.0,
      nullptr,
      nullptr,
      EXPLOSIONDAMAGE_LINEAR_FALLOFF);
    ptAlarmLight->isDestroyed = 1;
    LODVirModelExistsFn = MTP_GetLODVirModelExistsFn(ptAlarmLight->azModel[2]);
    if ( LODVirModelExistsFn != ptAlarmLight->tSectorInteriorObject.tRigidDynCubeObj.tModelObj.ptLODVirModel )
    {
      ModelObj_SetLODVirModel(
        &ptAlarmLight->tSectorInteriorObject.tRigidDynCubeObj.tModelObj,
        LODVirModelExistsFn,
        false);
      v3 = &ptAlarmLight->tSectorInteriorObject.tRigidDynCubeObj.aptLightmapVirModel[1];
      *v3 = nullptr;
      v3[1] = nullptr;
      v3[2] = nullptr;
      v3[3] = nullptr;
      v3[4] = nullptr;
    }
  }
}

// source: j/0/objects/alarmlight.c:288  [size]
void __cdecl AlarmLight_ReflectorCreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][RigidMagicObj_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  ptQTask[8].tQTaskChildren.ptHead = nullptr;
}

// source: j/0/objects/alarmlight.c:321  [anchor-mhash]
void __cdecl AlarmLight_ReflectorRunHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v17; };
    struct { char igi2_o1[4]; float Real32x9_Multiply_tTemp; };
    struct { char igi2_o2[8]; float Real32x9_Multiply_tTemp_4; };
    struct { char igi2_o3[12]; float Real32x9_Multiply_tTemp_8; };
    struct { char igi2_o4[16]; float Real32x9_Multiply_tTemp_12; };
    struct { char igi2_o5[20]; float Real32x9_Multiply_tTemp_16; };
    struct { char igi2_o6[24]; float Real32x9_Multiply_tTemp_20; };
    struct { char igi2_o7[28]; float Real32x9_Multiply_tTemp_24; };
    struct { char igi2_o8[44]; struct real32x9_t tOrientation; };
    char igi2_extent[84];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptNext; // eax
  long double v3; // st7
  long double v4; // rt0
  double v5; // st6
  double v6; // st6
  long double v7; // st7
  char *v8; // ecx
  double v9; // st6
  double v10; // st7
  double v11; // st6
  struct QTask_s *ptHead; // ecx
  int v13; // edx
  struct QTask_s *v14; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v16; // edx
  float ptQTaska = *(float *)&ptQTask; // [esp+64h] [ebp+4h] ARGSLOT

  ptNext = ptQTask[8].ptNext;
  if ( LOBYTE(ptNext[12].tQTaskChildren.ptTail) && !BYTE1(ptNext[12].tQTaskChildren.ptTail) )
  {
    v3 = *(float *)&ptQTask[8].tQTaskChildren.ptHead + 0.10471975803375244;
    *(float *)&ptQTask[8].tQTaskChildren.ptHead = v3;
    v4 = sin(v3);
    ptQTaska = cos(v3);
    igi2_frame.tOrientation.tY.vZ = -v4;
    igi2_frame.Real32x9_Multiply_tTemp = (*(float *)&ptQTask[4].tQTaskChildren.ptHead
                             + *(float *)&ptQTask[4].tQTaskChildren.ptMiddle)
                            * 0.0
                            + *(float *)&ptQTask[4].ptPrev;
    v5 = *(float *)&ptQTask[4].ptPrev * 0.0;
    igi2_frame.Real32x9_Multiply_tTemp_4 = ptQTaska * *(float *)&ptQTask[4].tQTaskChildren.ptHead
                              + v4 * *(float *)&ptQTask[4].tQTaskChildren.ptMiddle
                              + v5;
    igi2_frame.Real32x9_Multiply_tTemp_8 = igi2_frame.tOrientation.tY.vZ * *(float *)&ptQTask[4].tQTaskChildren.ptHead
                              + ptQTaska * *(float *)&ptQTask[4].tQTaskChildren.ptMiddle
                              + v5;
    igi2_frame.Real32x9_Multiply_tTemp_12 = (*(float *)&ptQTask[4].tQTaskRefList.ptMiddle
                                + *(float *)&ptQTask[4].tQTaskRefList.ptHead)
                               * 0.0
                               + *(float *)&ptQTask[4].tQTaskChildren.ptTail;
    v6 = *(float *)&ptQTask[4].tQTaskChildren.ptTail * 0.0;
    igi2_frame.Real32x9_Multiply_tTemp_16 = v4 * *(float *)&ptQTask[4].tQTaskRefList.ptMiddle
                               + ptQTaska * *(float *)&ptQTask[4].tQTaskRefList.ptHead
                               + v6;
    igi2_frame.Real32x9_Multiply_tTemp_20 = ptQTaska * *(float *)&ptQTask[4].tQTaskRefList.ptMiddle
                               + igi2_frame.tOrientation.tY.vZ * *(float *)&ptQTask[4].tQTaskRefList.ptHead
                               + v6;
    igi2_frame.Real32x9_Multiply_tTemp_24 = (*(float *)&ptQTask[4].eQTaskType + *(float *)&ptQTask[4].ptParent) * 0.0
                               + *(float *)&ptQTask[4].tQTaskRefList.ptTail;
    igi2_frame.v17 = *(float *)&ptQTask[4].tQTaskRefList.ptTail * 0.0;
    v7 = ptQTaska * *(float *)&ptQTask[4].ptParent + v4 * *(float *)&ptQTask[4].eQTaskType + igi2_frame.v17;
    v8 = (char *)&ptQTask[5].ptNext->ptNext + 1;
    v9 = igi2_frame.tOrientation.tY.vZ * *(float *)&ptQTask[4].ptParent + ptQTaska * *(float *)&ptQTask[4].eQTaskType + igi2_frame.v17;
    igi2_frame.tOrientation.tX.vX = igi2_frame.Real32x9_Multiply_tTemp * *(float *)&ptNext[3].ptPrev
                       + igi2_frame.Real32x9_Multiply_tTemp_24 * *(float *)&ptNext[3].tQTaskChildren.ptMiddle
                       + igi2_frame.Real32x9_Multiply_tTemp_12 * *(float *)&ptNext[3].tQTaskChildren.ptHead;
    igi2_frame.tOrientation.tX.vY = igi2_frame.Real32x9_Multiply_tTemp_4 * *(float *)&ptNext[3].ptPrev
                       + v7 * *(float *)&ptNext[3].tQTaskChildren.ptMiddle
                       + igi2_frame.Real32x9_Multiply_tTemp_16 * *(float *)&ptNext[3].tQTaskChildren.ptHead;
    igi2_frame.tOrientation.tX.vZ = igi2_frame.Real32x9_Multiply_tTemp_8 * *(float *)&ptNext[3].ptPrev
                       + v9 * *(float *)&ptNext[3].tQTaskChildren.ptMiddle
                       + igi2_frame.Real32x9_Multiply_tTemp_20 * *(float *)&ptNext[3].tQTaskChildren.ptHead;
    igi2_frame.tOrientation.tY.vX = igi2_frame.Real32x9_Multiply_tTemp * *(float *)&ptNext[3].tQTaskChildren.ptTail
                       + igi2_frame.Real32x9_Multiply_tTemp_24 * *(float *)&ptNext[3].tQTaskRefList.ptMiddle
                       + igi2_frame.Real32x9_Multiply_tTemp_12 * *(float *)&ptNext[3].tQTaskRefList.ptHead;
    igi2_frame.tOrientation.tY.vY = igi2_frame.Real32x9_Multiply_tTemp_4 * *(float *)&ptNext[3].tQTaskChildren.ptTail
                       + v7 * *(float *)&ptNext[3].tQTaskRefList.ptMiddle
                       + igi2_frame.Real32x9_Multiply_tTemp_16 * *(float *)&ptNext[3].tQTaskRefList.ptHead;
    igi2_frame.tOrientation.tY.vZ = igi2_frame.Real32x9_Multiply_tTemp_8 * *(float *)&ptNext[3].tQTaskChildren.ptTail
                       + v9 * *(float *)&ptNext[3].tQTaskRefList.ptMiddle
                       + igi2_frame.Real32x9_Multiply_tTemp_20 * *(float *)&ptNext[3].tQTaskRefList.ptHead;
    igi2_frame.tOrientation.tZ.vX = igi2_frame.Real32x9_Multiply_tTemp_24 * *(float *)&ptNext[3].eQTaskType
                       + igi2_frame.Real32x9_Multiply_tTemp_12 * *(float *)&ptNext[3].ptParent
                       + igi2_frame.Real32x9_Multiply_tTemp * *(float *)&ptNext[3].tQTaskRefList.ptTail;
    igi2_frame.tOrientation.tZ.vY = v7 * *(float *)&ptNext[3].eQTaskType
                       + igi2_frame.Real32x9_Multiply_tTemp_16 * *(float *)&ptNext[3].ptParent
                       + igi2_frame.Real32x9_Multiply_tTemp_4 * *(float *)&ptNext[3].tQTaskRefList.ptTail;
    v10 = v9 * *(float *)&ptNext[3].eQTaskType + igi2_frame.Real32x9_Multiply_tTemp_20 * *(float *)&ptNext[3].ptParent;
    v11 = igi2_frame.Real32x9_Multiply_tTemp_8 * *(float *)&ptNext[3].tQTaskRefList.ptTail;
    igi2_frame.tOrientation.nOps = (int)&ptNext[4].ptNext->ptNext + (unsigned int)v8 + 1;
    igi2_frame.tOrientation.tZ.vZ = v10 + v11;
    qmemcpy(&ptQTask[3].ptPrev, &igi2_frame.tOrientation, sizeof(struct QTask_s));
  }
  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v13 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v14 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v14 = nullptr;
      QTask_atProtectedQTaskStack[v13].ptQTask = v14;
      pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][ptHead->eQTaskType].pfHandler;
      v16 = v13 + 1;
      QTask_nProtectedQTaskStackOffset = v16;
      if ( pfHandler )
      {
        pfHandler(ptHead);
        v16 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v16];
      v13 = v16 - 1;
      QTask_nProtectedQTaskStackOffset = v13;
    }
    while ( ptHead );
  }
}

// source: j/0/objects/alarmlight.c:367  [size]
void __cdecl AlarmLight_ReflectorDeleteHandler(struct QTask_s *ptQTask)
{
  World_RemoveDynCubeObj((struct World_s *)ptQTask[2].ptParent, (struct DynCubeObj_s *)ptQTask);
}

// source: j/0/objects/alarmlight.c:384  [anchor-mhash]
void __cdecl AlarmLight_ReflectorEnterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptNext; // eax

  ptNext = ptQTask[8].ptNext;
  if ( !BYTE1(ptNext[12].tQTaskChildren.ptTail) )
  {
    if ( LOBYTE(ptNext[12].tQTaskChildren.ptTail) )
      AlarmLight_ReflectorRegisterLight((struct AlarmLightReflector_s *)ptQTask, 0);
    ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[5][RigidDynCubeObj_eQTaskType].pfHandler)(
      ptQTask,
      pxContext);
  }
}

// source: j/0/objects/alarmlight.c:413  [anchor-mhash]
void __cdecl AlarmLight_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  double v2; // st7
  bool v3; // c0
  bool v4; // c3
  double v5; // st7
  double v6; // st7
  int *v7; // eax
  int v8; // eax
  double v9; // st6
  struct QReference_s **p_ptMiddle; // eax
  int v11; // ecx
  struct QTask_s **p_ptParent; // eax
  int v13; // ecx
  struct QTaskList_s *v14; // eax
  float ptDynCubeObj; // [esp+0h] [ebp-1Ch]

  ModelObj_Init((struct ModelObj_s *)ptQTask, World_ptActiveWorld, nullptr);
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
  ptQTask[8].ptNext = nullptr;
  ptQTask[8].ptPrev = nullptr;
  ptQTask[8].tQTaskChildren.ptHead = nullptr;
  ptQTask[8].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[8].tQTaskChildren.ptTail = nullptr;
  ptQTask[8].tQTaskRefList.ptHead = nullptr;
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
    World_ptActiveWorld,
    (struct DynCubeObj_s *)ptQTask,
    (struct real64x3_t *)&ptQTask[8],
    ptDynCubeObj,
    WORLD_DYNCUBETREE_CATEGORY_STATIONARY);
  if ( ptQTask[7].tQTaskChildren.ptTail )
  {
    ptQTask[2].tQTaskRefList.ptHead = nullptr;
    ptQTask[2].tQTaskRefList.ptMiddle = nullptr;
  }
  else
  {
    SectorObject_RegisterInteriorDynCubeObjSpecificSectorObject(
      (struct World_s *)ptQTask[2].ptParent,
      nullptr,
      (struct DynCubeObj_s *)ptQTask,
      (struct real64x3_t *)&ptQTask[1]);
  }
  ptQTask[8].tQTaskRefList.ptMiddle = (struct QReference_s *)1065353216;
  ptQTask[9].ptNext = (struct QTask_s *)1065353216;
  ptQTask[9].tQTaskChildren.ptTail = (struct QTask_s *)1065353216;
  ptQTask[8].tQTaskRefList.ptTail = nullptr;
  ptQTask[8].ptParent = nullptr;
  *(_DWORD *)&ptQTask[8].eQTaskType = 0;
  ptQTask[9].ptPrev = nullptr;
  ptQTask[9].tQTaskChildren.ptHead = nullptr;
  ptQTask[9].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[9].tQTaskRefList.ptHead = nullptr;
  qmemcpy(&ptQTask[3].ptPrev, &ptQTask[8].tQTaskRefList.ptMiddle, sizeof(struct QTask_s));
  p_ptMiddle = &ptQTask[9].tQTaskRefList.ptMiddle;
  v11 = 3;
  do
  {
    *(_BYTE *)p_ptMiddle = 0;
    p_ptMiddle += 4;
    --v11;
  }
  while ( v11 );
  p_ptParent = &ptQTask[10].ptParent;
  v13 = 2;
  do
  {
    *(_BYTE *)p_ptParent = 0;
    p_ptParent += 8;
    --v13;
  }
  while ( v13 );
  v14 = GameFunctions_ptExplosionQTaskList;
  LOBYTE(ptQTask[12].tQTaskChildren.ptTail) = 0;
  BYTE1(ptQTask[12].tQTaskChildren.ptTail) = 0;
  BYTE2(ptQTask[12].tQTaskChildren.ptTail) = 0;
  ptQTask[12].tQTaskRefList.ptHead = nullptr;
  ptQTask[12].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[12].tQTaskRefList.ptTail = nullptr;
  ptQTask[14].tQTaskChildren.ptTail = nullptr;
  ptQTask[14].tQTaskRefList.ptHead = nullptr;
  QTaskList_Register(v14, (struct QTaskList_s *)ptQTask);
}

// source: j/0/objects/alarmlight.c:482  [anchor-caller]
void __cdecl AlarmLight_RunHandler(struct QTask_s *ptQTask)
{
  char ptTail; // bl
  char v2; // al
  char *p_ptMiddle; // eax
  struct LODVirModel_s *LODVirModelExistsFn; // eax
  struct QTask_s *ptHead; // ecx
  int v6; // edx
  struct QTask_s *v7; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v9; // edx
  struct QTask_s *ptNext; // edi

  ptTail = (char)ptQTask[12].tQTaskChildren.ptTail;
  if ( !ptTail || BYTE1(ptQTask[12].tQTaskChildren.ptTail) )
  {
    if ( ptQTask[14].tQTaskRefList.ptHead )
    {
      QTask_Delete((struct QTask_s *)ptQTask[14].tQTaskRefList.ptHead);
      ptQTask[14].tQTaskRefList.ptHead = nullptr;
    }
  }
  else if ( !ptQTask[14].tQTaskRefList.ptHead )
  {
    ptQTask[14].tQTaskRefList.ptHead = (struct QReference_s *)SoundSys_NewSoundFn(
                                                                ptQTask,
                                                                (char *)&ptQTask[10].ptParent);
  }
  if ( !BYTE1(ptQTask[12].tQTaskChildren.ptTail) )
  {
    if ( ptQTask[12].tQTaskRefList.ptHead
      && ptQTask[12].tQTaskRefList.ptMiddle->ptNext
      && ptQTask[12].tQTaskRefList.ptTail )
    {
      LOBYTE(ptQTask[12].tQTaskChildren.ptTail) = (__int64)Level_RunLevelExpression(
                                                             (struct LevelExpression_s *)&ptQTask[12].tQTaskRefList,
                                                             ptQTask);
    }
    v2 = (char)ptQTask[12].tQTaskChildren.ptTail;
    if ( ptTail )
    {
      if ( v2 )
        goto LABEL_18;
      p_ptMiddle = (char *)&ptQTask[9].tQTaskRefList.ptMiddle;
    }
    else
    {
      if ( !v2 )
        goto LABEL_18;
      p_ptMiddle = (char *)&ptQTask[10];
    }
    LODVirModelExistsFn = MTP_GetLODVirModelExistsFn(p_ptMiddle);
    RigidDynCubeObj_SetLODVirModel((struct RigidDynCubeObj_t *)ptQTask, LODVirModelExistsFn);
LABEL_18:
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
        pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][ptHead->eQTaskType].pfHandler;
        v9 = v6 + 1;
        QTask_nProtectedQTaskStackOffset = v9;
        if ( pfHandler )
        {
          pfHandler(ptHead);
          v9 = QTask_nProtectedQTaskStackOffset;
        }
        ptHead = (struct QTask_s *)dword_849C7DC[v9];
        v6 = v9 - 1;
        QTask_nProtectedQTaskStackOffset = v6;
      }
      while ( ptHead );
    }
    ptNext = ptQTask[3].ptNext;
    if ( ptNext )
      ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][ptNext->eQTaskType].pfHandler)(ptNext);
  }
}

// source: j/0/objects/alarmlight.c:554  [anchor-mhash]
void __cdecl AlarmLight_DeleteHandler(struct QTask_s *ptQTask)
{
  int v1; // eax
  struct QReference_s *v2; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *); // eax

  QTaskList_Remove(GameFunctions_ptExplosionQTaskList, ptQTask);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[12].tQTaskRefList);
  v1 = 0;
  while ( 1 )
  {
    v2 = Level_atLevelQTaskID[v1];
    if ( v2 )
    {
      if ( v2->pxObject == ptQTask )
        break;
    }
    if ( ++v1 >= 4096 )
      goto LABEL_9;
  }
  if ( v1 >= 0 )
  {
    pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Level_eRemoveLevelScriptSymbolsEvent][ptQTask->eQTaskType].pfHandler;
    if ( pfHandler )
      pfHandler(ptQTask);
  }
LABEL_9:
  if ( *(_DWORD *)&ptQTask[2].eQTaskType )
  {
    ModelObj_SetLODVirModel((struct ModelObj_s *)ptQTask, nullptr, false);
    ptQTask[7].tQTaskRefList.ptHead = nullptr;
    ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
    ptQTask[7].tQTaskRefList.ptTail = nullptr;
    ptQTask[7].ptParent = nullptr;
    *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  }
  SectorObject_RemoveInteriorDynCubeObj((struct DynCubeObj_s *)ptQTask);
  World_RemoveDynCubeObj((struct World_s *)ptQTask[2].ptParent, (struct DynCubeObj_s *)ptQTask);
}

// source: j/0/objects/alarmlight.c:590  [size]
void __cdecl AlarmLight_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = AlarmLight_ptParameterList;
}

// source: j/0/objects/alarmlight.c:606  [anchor-mhash]
void __cdecl AlarmLight_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct LODVirModel_s *LODVirModelExistsFn; // eax
  double v3; // st7
  double v4; // st7
  int *v5; // eax
  int v6; // eax
  double v7; // st6
  struct QTask_s *ptParent; // esi
  float ptDynCubeObj; // [esp+0h] [ebp-10h]

  LODVirModelExistsFn = MTP_GetLODVirModelExistsFn((char *)&ptQTask[10]);
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
    (struct World_s *)ptQTask[2].ptParent,
    (struct DynCubeObj_s *)ptQTask,
    (struct real64x3_t *)&ptQTask[8],
    ptDynCubeObj);
  ptParent = ptQTask[2].ptParent;
  SectorObject_RemoveInteriorDynCubeObj((struct DynCubeObj_s *)ptQTask);
  if ( ptQTask[7].tQTaskChildren.ptTail )
  {
    ptQTask[2].tQTaskRefList.ptHead = nullptr;
    ptQTask[2].tQTaskRefList.ptMiddle = nullptr;
  }
  else
  {
    SectorObject_RegisterInteriorDynCubeObjSpecificSectorObject(
      (struct World_s *)ptParent,
      nullptr,
      (struct DynCubeObj_s *)ptQTask,
      (struct real64x3_t *)&ptQTask[1]);
  }
  qmemcpy(&ptQTask[3].ptPrev, &ptQTask[8].tQTaskRefList.ptMiddle, sizeof(struct QTask_s));
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[12].tQTaskRefList, ptQTask);
}

void __cdecl sub_470880(struct AlarmLight_t *a1)
{
  AlarmLight_Explode(a1);
}

// source: j/0/objects/alarmlight.c:670  [anchor-mhash]
void __cdecl AlarmLight_ExplosionHitHandler(struct QTask_s *ptQTask, void *pxContext)
{
  double v2; // st7
  double v3; // st7
  int *v4; // eax
  int v5; // eax
  double v6; // st6
  float ptExplosionHitContext; // [esp+0h] [ebp-Ch]

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
  ptExplosionHitContext = v3 * v6;
  if ( GameFunctions_ResolveExplosionHit(
         (struct ExplosionHitContext_t *)pxContext,
         ptQTask,
         (struct real64x3_t *)&ptQTask[1],
         ptExplosionHitContext,
         true) != 0.0 )
    AlarmLight_Explode((struct AlarmLight_t *)ptQTask);
}

// source: j/0/objects/alarmlight.c:705  [size]
void __cdecl AlarmLight_RegisterScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( !BYTE2(ptQTask[12].tQTaskChildren.ptTail) )
  {
    BYTE2(ptQTask[12].tQTaskChildren.ptTail) = 1;
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.isOn", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      &ptQTask[12].tQTaskChildren.ptTail,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.isDestroyed", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      (char *)&ptQTask[12].tQTaskChildren.ptTail + 1,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
  }
}

// source: j/0/objects/alarmlight.c:738  [size]
void __cdecl AlarmLight_RemoveScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( BYTE2(ptQTask[12].tQTaskChildren.ptTail) )
  {
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    BYTE2(ptQTask[12].tQTaskChildren.ptTail) = 0;
    sprintf(igi2_frame.zTemp, "%s.isOn", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.isDestroyed", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
  }
}

// source: j/0/objects/alarmlight.c:799  [size]
void __cdecl AlarmLight_UpdateAttachmentHandler(struct QTask_s *ptQTask)
{
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Attach_eUpdateAttachmentEvent][SectorInteriorObject_eQTaskType].pfHandler)(ptQTask);
  qmemcpy(&ptQTask[8].tQTaskRefList.ptMiddle, &ptQTask[3].ptPrev, sizeof(struct QTask_s));
  qmemcpy(&ptQTask[8], &ptQTask[1], 0x18u);
}

// source: j/0/objects/alarmlight.c:873  [anchor-strings]
void __cdecl AlarmLight_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // edx
  signed int v3; // esi
  char **v4; // edi
  unsigned int v5; // edi
  char **v6; // esi
  unsigned __int16 v7; // si
  _DWORD *v8; // esi

  v0 = QTask_NewQTaskType("AlarmLight", 584, SectorInteriorObject_eQTaskType, 0, 0);
  AlarmLight_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, AlarmLight_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, AlarmLight_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, AlarmLight_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))AlarmLight_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, AlarmLight_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    GameFunctions_eWeaponHitQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))sub_470880);
  QTask_LinkQTaskEventHandlerFn(v0, GameFunctions_eExplosionHitQTaskEvent, AlarmLight_ExplosionHitHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eRegisterLevelScriptSymbolsEvent,
    AlarmLight_RegisterScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eRemoveLevelScriptSymbolsEvent,
    AlarmLight_RemoveScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Attach_eUpdateAttachmentEvent, AlarmLight_UpdateAttachmentHandler);
  Symbol_Register(
    "TASKTYPE_ALARMLIGHT",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)v0,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  v1 = (struct ParameterList_s *)Mem_AllocFn(172, 4);
  v2 = Level_eParameterTypeObjectPos;
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  v1->nParameters = 0;
  v1->nMaxParameters = 8;
  AlarmLight_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0x140u, v2, "Position", 7u, nullptr);
  ParameterList_AddParameter(
    AlarmLight_ptParameterList,
    0x158u,
    Level_eParameterTypeReal32x9,
    "Orientation",
    7u,
    nullptr);
  ParameterList_AddParameter(
    AlarmLight_ptParameterList,
    0x1F4u,
    Level_eParameterTypeVarString,
    "On expression",
    7u,
    nullptr);
  v3 = 384;
  v4 = AlarmLight_azModelParameterName;
  do
  {
    ParameterList_AddParameter(AlarmLight_ptParameterList, v3, Level_eParameterTypeString16, *v4, 7u, nullptr);
    v3 += 16;
    ++v4;
  }
  while ( v3 < 432 );
  v5 = 432;
  v6 = AlarmLight_azSoundParameterName;
  do
  {
    ParameterList_AddParameter(AlarmLight_ptParameterList, v5, Level_eParameterTypeString16, *v6++, 7u, nullptr);
    v5 += 32;
  }
  while ( (int)v6 < 7050912 );
  v7 = QTask_NewQTaskType("AlarmLightReflector", 336, RigidMagicObj_eQTaskType, 0, 0);
  AlarmLightReflector_eQTaskType = v7;
  QTask_LinkQTaskEventHandlerFn(v7, 0, AlarmLight_ReflectorCreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v7, 1, AlarmLight_ReflectorRunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v7, 2, AlarmLight_ReflectorDeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v7, 5, AlarmLight_ReflectorEnterHandler);
  Symbol_Register(
    "TASKTYPE_ALARMLIGHTREFLECTOR",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)v7,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  v8 = Mem_AllocFn(18444, 4);
  v8[1] = 0;
  *v8 = 0;
  v8[4610] = "TASKTYPE_ALARMLIGHTREFLECTOR";
  Wildcard_CreateNFA("TASKTYPE_ALARMLIGHTREFLECTOR", v8 + 2, (char *)v8 + 10248);
  List_AddTail(v8, (int)&MagicObjConfig_tTaskTypeEnumList);
  AlarmLight_ptLightGameSprite = GameFunctions_RegisterGameSprite("alarmlight.spr");
}

// source: j/0/objects/alarmlight.c:952  [size]
void __cdecl AlarmLight_Close()
{
  int v0; // esi

  if ( AlarmLight_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&AlarmLight_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(AlarmLightReflector_eQTaskType);
  QTask_DeleteQTaskType(AlarmLight_eQTaskType);
}
