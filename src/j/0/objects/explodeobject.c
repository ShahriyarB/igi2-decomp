/* j/0/objects/explodeobject.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/objects/explodeobject.c:49  [size]
void __cdecl ExplodeObject_GetSerializeParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = ExplodeObject_ptSerializeParameterList;
}

// source: j/0/objects/explodeobject.c:67  [anchor-mhash]
void __cdecl ExplodeObject_DeSerializeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct LODVirModel_s *LODVirModelExistsFn; // eax

  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[Serialize_eDeSerializeQTaskEvent][SectorInteriorObject_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  if ( LOBYTE(ptQTask[11].tQTaskChildren.ptTail) )
  {
    ExplodeObject_SetExploded(ptQTask);
  }
  else
  {
    LODVirModelExistsFn = MTP_GetLODVirModelExistsFn((char *)&ptQTask[9].tQTaskRefList.ptMiddle);
    if ( LODVirModelExistsFn != *(struct LODVirModel_s **)&ptQTask[2].eQTaskType )
    {
      ModelObj_SetLODVirModel((struct ModelObj_s *)ptQTask, LODVirModelExistsFn, false);
      ptQTask[7].tQTaskRefList.ptHead = nullptr;
      ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
      ptQTask[7].tQTaskRefList.ptTail = nullptr;
      ptQTask[7].ptParent = nullptr;
      *(_DWORD *)&ptQTask[7].eQTaskType = 0;
    }
    ptQTask[7].tQTaskRefList = *(struct QReferenceList_s *)&ptQTask[10].tQTaskChildren.ptTail;
    ptQTask[7].ptParent = (struct QTask_s *)ptQTask[10].tQTaskRefList.ptTail;
    *(_DWORD *)&ptQTask[7].eQTaskType = ptQTask[10].ptParent;
  }
}

// source: j/0/objects/explodeobject.c:106  [anchor-mhash]
void __cdecl ExplodeObject_Explode(struct ExplodeObject_t *ptExplodeObject)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vFullRange; };
    struct { char igi2_o1[4]; float vFallOffRange; };
    struct { char igi2_o2[72]; struct real64x3_t tPos; };
    char igi2_extent[96];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int nFireball; // eax

  ExplodeObject_SetExploded(&ptExplodeObject->tSectorInteriorObject.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask);
  qmemcpy(
    &igi2_frame.tPos,
    &ptExplodeObject->tSectorInteriorObject.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos,
    sizeof(igi2_frame.tPos));
  GameFunctions_GetMagicVertex(
    &igi2_frame.tPos,
    &ptExplodeObject->tSectorInteriorObject.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask,
    0);
  nFireball = ptExplodeObject->nFireball;
  if ( nFireball > 0 )
  {
    igi2_frame.vFallOffRange = ptExplodeObject->vFalloffRadius * 4096.0;
    igi2_frame.vFullRange = ptExplodeObject->vRadius * 4096.0;
    Explosion0_New(
      &igi2_frame.tPos,
      1,
      0,
      ptExplodeObject->vExplosionDamage,
      igi2_frame.vFullRange,
      igi2_frame.vFallOffRange,
      6144.0,
      ptExplodeObject->nFragment,
      nFireball,
      nullptr,
      "1009_01_1",
      ptExplodeObject->zSound,
      20,
      0x402u,
      307200.0,
      nullptr,
      &ptExplodeObject->tSectorInteriorObject.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask,
      EXPLOSIONDAMAGE_LINEAR_FALLOFF);
  }
}

// source: j/0/objects/explodeobject.c:160  [anchor-mhash]
void __cdecl ExplodeObject_EnumerateLightmapVirModelsHandler(struct QTask_s *ptQTask, void *pxContext)
{
  unsigned __int16 v2; // dx
  _DWORD *p_tMyContext; // ebp
  int v4; // eax
  struct QReference_s *v5; // ecx
  int v6; // ebx
  struct LODVirModel_s *LODVirModelExistsFn; // eax
  struct LODVirModel_s *v8; // ecx
  struct QTask_s *ptHead; // edx
  struct QTask_s *ptMiddle; // eax
  struct QTask_s *ptTail; // ecx
  struct QTask_s *ptParent; // edx
  struct EnumerateLightmapVirModelsContext_t tMyContext; // [esp+10h] [ebp-20h] BYREF

  v2 = LightmapInfo_eQTaskType;
  qmemcpy(&tMyContext, pxContext, sizeof(tMyContext));
  p_tMyContext = pxContext;
  if ( !QTask_GetFirstChildOfType(ptQTask, LightmapInfo_eQTaskType)
    || QTask_GetFirstChildOfType(ptQTask, v2) == *(struct QTask_s **)pxContext )
  {
    v4 = 0;
    while ( 1 )
    {
      v5 = Level_atLevelQTaskID[v4];
      if ( v5 )
      {
        if ( v5->pxObject == ptQTask )
          break;
      }
      if ( ++v4 >= 4096 )
      {
        v6 = -1;
        goto LABEL_10;
      }
    }
    v6 = v4;
    if ( v4 != -1 )
    {
      tMyContext.nParentQTaskID = v4;
      tMyContext.nSubQTaskID = 0;
      tMyContext.nModelVariation = 1;
    }
LABEL_10:
    LightmapInfo_AddLightmapVirModelToEnumeration(
      ptQTask,
      *(struct LODVirModel_s **)&ptQTask[2].eQTaskType,
      (struct Mesh3D_LightmapVirModel_t *(*)[5])&ptQTask[10].tQTaskChildren.ptTail,
      &tMyContext);
    if ( v6 != -1 )
      p_tMyContext = &tMyContext;
    ++p_tMyContext[3];
    if ( !strcmp((char *)&ptQTask[10], (char *)&ptQTask[9].tQTaskRefList.ptMiddle) )
    {
      ptHead = (struct QTask_s *)ptQTask[10].tQTaskRefList.ptHead;
      ptMiddle = (struct QTask_s *)ptQTask[10].tQTaskRefList.ptMiddle;
      *(_DWORD *)&ptQTask[10].eQTaskType = ptQTask[10].tQTaskChildren.ptTail;
      ptTail = (struct QTask_s *)ptQTask[10].tQTaskRefList.ptTail;
      ptQTask[11].ptNext = ptHead;
      ptParent = ptQTask[10].ptParent;
      ptQTask[11].ptPrev = ptMiddle;
      ptQTask[11].tQTaskChildren.ptHead = ptTail;
      ptQTask[11].tQTaskChildren.ptMiddle = ptParent;
    }
    else
    {
      if ( v6 != -1 )
      {
        tMyContext.nParentQTaskID = v6;
        tMyContext.nSubQTaskID = 0;
        tMyContext.nModelVariation = 2;
      }
      LODVirModelExistsFn = MTP_GetLODVirModelExistsFn((char *)&ptQTask[10]);
      if ( LODVirModelExistsFn )
        v8 = LODVirModelExistsFn;
      else
        v8 = nullptr;
      LightmapInfo_AddLightmapVirModelToEnumeration(
        ptQTask,
        v8,
        (struct Mesh3D_LightmapVirModel_t *(*)[5])&ptQTask[10].eQTaskType,
        &tMyContext);
    }
    ptQTask[7].tQTaskRefList = *(struct QReferenceList_s *)&ptQTask[10].tQTaskChildren.ptTail;
    ptQTask[7].ptParent = (struct QTask_s *)ptQTask[10].tQTaskRefList.ptTail;
    *(_DWORD *)&ptQTask[7].eQTaskType = ptQTask[10].ptParent;
  }
}

// source: j/0/objects/explodeobject.c:246  [anchor-mhash]
void __cdecl ExplodeObject_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[24]; struct real64x3_t ptPos; };
    char igi2_extent[52];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v2; // st7
  double v3; // st7
  int *v4; // eax
  int v5; // eax
  double v6; // st6
  __int16 v7; // cx

  memset(&igi2_frame.ptPos, 0, sizeof(igi2_frame.ptPos));
  QTaskList_Register(GameFunctions_ptExplosionQTaskList, (struct QTaskList_s *)ptQTask);
  ModelObj_Init((struct ModelObj_s *)ptQTask, World_ptActiveWorld, nullptr);
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
    World_ptActiveWorld,
    (struct DynCubeObj_s *)ptQTask,
    &igi2_frame.ptPos,
    igi2_frame.ptDynCubeObj,
    WORLD_DYNCUBETREE_CATEGORY_MOBILE);
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
  ptQTask[3].ptPrev = (struct QTask_s *)1065353216;
  ptQTask[3].tQTaskRefList.ptHead = (struct QReference_s *)1065353216;
  *(_DWORD *)&ptQTask[3].eQTaskType = 1065353216;
  ptQTask[8].tQTaskRefList.ptMiddle = (struct QReference_s *)1065353216;
  ptQTask[9].ptNext = (struct QTask_s *)1065353216;
  ptQTask[9].tQTaskChildren.ptTail = (struct QTask_s *)1065353216;
  ptQTask[13].ptParent = (struct QTask_s *)1065353216;
  ptQTask[14].tQTaskChildren.ptMiddle = (struct QTask_s *)1065353216;
  ptQTask[14].tQTaskChildren.ptHead = (struct QTask_s *)1065353216;
  ptQTask[14].tQTaskChildren.ptTail = (struct QTask_s *)1065353216;
  ptQTask[3].tQTaskChildren.ptHead = nullptr;
  ptQTask[3].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[3].tQTaskChildren.ptTail = nullptr;
  ptQTask[3].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[3].tQTaskRefList.ptTail = nullptr;
  ptQTask[3].ptParent = nullptr;
  ptQTask[4].ptNext = nullptr;
  ptQTask[8].tQTaskRefList.ptTail = nullptr;
  ptQTask[8].ptParent = nullptr;
  *(_DWORD *)&ptQTask[8].eQTaskType = 0;
  ptQTask[9].ptPrev = nullptr;
  ptQTask[9].tQTaskChildren.ptHead = nullptr;
  ptQTask[9].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[9].tQTaskRefList.ptHead = nullptr;
  LOBYTE(ptQTask[9].tQTaskRefList.ptMiddle) = 0;
  LOBYTE(ptQTask[10].ptNext) = 0;
  LOBYTE(ptQTask[13].tQTaskRefList.ptHead) = 0;
  LOBYTE(ptQTask[11].tQTaskChildren.ptTail) = 0;
  BYTE1(ptQTask[11].tQTaskChildren.ptTail) = 0;
  ptQTask[13].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[14].ptNext = (struct QTask_s *)0x40000000;
  ptQTask[14].ptPrev = (struct QTask_s *)1069547520;
  *(_DWORD *)&ptQTask[13].eQTaskType = -1;
  ptQTask[14].tQTaskRefList.ptHead = (struct QReference_s *)3;
  ptQTask[14].tQTaskRefList.ptMiddle = (struct QReference_s *)3;
  *(_DWORD *)&ptQTask[10].eQTaskType = 0;
  ptQTask[11].ptNext = nullptr;
  ptQTask[11].ptPrev = nullptr;
  ptQTask[11].tQTaskChildren.ptHead = nullptr;
  ptQTask[11].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[10].tQTaskChildren.ptTail = nullptr;
  ptQTask[10].tQTaskRefList.ptHead = nullptr;
  ptQTask[10].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[10].tQTaskRefList.ptTail = nullptr;
  ptQTask[10].ptParent = nullptr;
  v7 = Attach_eAttachEvent;
  ptQTask[11].tQTaskRefList.ptHead = nullptr;
  ptQTask[11].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[11].tQTaskRefList.ptTail = nullptr;
  ptQTask[13].tQTaskChildren.ptTail = nullptr;
  ptQTask[5].tQTaskChildren.ptTail = (struct QTask_s *)-1;
  LOBYTE(ptQTask[14].tQTaskRefList.ptTail) = 0;
  ptQTask[5].tQTaskRefList.ptHead = nullptr;
  QTask_TriggerQTaskEventParent(ptQTask, v7, &ptQTask[5].tQTaskChildren.ptTail);
  ModelObj_CalcRelativePosAndOrientation((struct ModelObj_s *)ptQTask);
}

// source: j/0/objects/explodeobject.c:322  [anchor-mhash]
void __cdecl ExplodeObject_RunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // ecx
  int v2; // edx
  struct QTask_s *v3; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v5; // edx
  int v6; // eax

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
  if ( !LOBYTE(ptQTask[11].tQTaskChildren.ptTail) )
  {
    if ( ptQTask[11].tQTaskRefList.ptHead
      && ptQTask[11].tQTaskRefList.ptMiddle->ptNext
      && ptQTask[11].tQTaskRefList.ptTail )
    {
      LOBYTE(ptQTask[13].tQTaskRefList.ptHead) = (__int64)Level_RunLevelExpression(
                                                            (struct LevelExpression_s *)&ptQTask[11].tQTaskRefList,
                                                            ptQTask);
    }
    if ( !LOBYTE(ptQTask[13].tQTaskRefList.ptHead) && *(_DWORD *)&ptQTask[13].eQTaskType
      || (ExplodeObject_Explode((struct ExplodeObject_t *)ptQTask),
          MTP_GetLODVirModelExistsFn((char *)&ptQTask[10])) )
    {
      v6 = *(_DWORD *)&ptQTask[13].eQTaskType;
      if ( v6 > 0 )
        *(_DWORD *)&ptQTask[13].eQTaskType = v6 - 1;
    }
  }
}

// source: j/0/objects/explodeobject.c:371  [anchor-mhash]
void __cdecl ExplodeObject_DeleteHandler(struct QTask_s *ptQTask)
{
  int v1; // eax
  struct QReference_s *v2; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *); // eax

  if ( *(_DWORD *)&ptQTask[2].eQTaskType )
  {
    ModelObj_SetLODVirModel((struct ModelObj_s *)ptQTask, nullptr, false);
    ptQTask[7].tQTaskRefList.ptHead = nullptr;
    ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
    ptQTask[7].tQTaskRefList.ptTail = nullptr;
    ptQTask[7].ptParent = nullptr;
    *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  }
  QTaskList_Remove(GameFunctions_ptExplosionQTaskList, ptQTask);
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
      goto LABEL_11;
  }
  if ( v1 >= 0 )
  {
    pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Level_eRemoveLevelScriptSymbolsEvent][ptQTask->eQTaskType].pfHandler;
    if ( pfHandler )
      pfHandler(ptQTask);
  }
LABEL_11:
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[11].tQTaskRefList);
  SectorObject_RemoveInteriorDynCubeObj((struct DynCubeObj_s *)ptQTask);
  World_RemoveDynCubeObj((struct World_s *)ptQTask[2].ptParent, (struct DynCubeObj_s *)ptQTask);
}

// source: j/0/objects/explodeobject.c:408  [size]
void __cdecl ExplodeObject_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = ExplodeObject_ptParameterList;
}

// source: j/0/objects/explodeobject.c:424  [anchor-strings]
void __cdecl ExplodeObject_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[24]; struct LODVirModel_s *ptLODVirModel; };
    struct { char igi2_o2[28]; char Buffer[132]; };
    char igi2_extent[160];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char *p_ptMiddle; // edi
  struct LODVirModel_s *v3; // esi
  struct LODVirModel_s *LODVirModelExistsFn; // eax
  double v5; // st7
  double v6; // st7
  int *v7; // eax
  int v8; // eax
  double v9; // st6
  struct QTask_s *ptParent; // esi
  struct QTask_s *v11; // ecx
  struct QTask_s *ptMiddle; // edx
  __int16 v13; // cx

  p_ptMiddle = (char *)&ptQTask[9].tQTaskRefList.ptMiddle;
  v3 = nullptr;
  igi2_frame.ptLODVirModel = MTP_GetLODVirModelExistsFn((char *)&ptQTask[9].tQTaskRefList.ptMiddle);
  if ( !igi2_frame.ptLODVirModel )
    igi2_frame.ptLODVirModel = nullptr;
  LODVirModelExistsFn = MTP_GetLODVirModelExistsFn((char *)&ptQTask[10]);
  if ( LODVirModelExistsFn )
    v3 = LODVirModelExistsFn;
  if ( !igi2_frame.ptLODVirModel && *p_ptMiddle && BYTE1(ptQTask[9].tQTaskRefList.ptMiddle) != 42 )
    sprintf(igi2_frame.Buffer, "Model \"%s\" not available", p_ptMiddle);
  if ( !v3 && LOBYTE(ptQTask[10].ptNext) && BYTE1(ptQTask[10].ptNext) != 42 )
    sprintf(igi2_frame.Buffer, "Model \"%s\" not available", (char *)&ptQTask[10]);
  if ( igi2_frame.ptLODVirModel != *(struct LODVirModel_s **)&ptQTask[2].eQTaskType )
  {
    ModelObj_SetLODVirModel((struct ModelObj_s *)ptQTask, igi2_frame.ptLODVirModel, false);
    ptQTask[7].tQTaskRefList.ptHead = nullptr;
    ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
    ptQTask[7].tQTaskRefList.ptTail = nullptr;
    ptQTask[7].ptParent = nullptr;
    *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  }
  ptQTask[7].tQTaskRefList = *(struct QReferenceList_s *)&ptQTask[10].tQTaskChildren.ptTail;
  ptQTask[7].ptParent = (struct QTask_s *)ptQTask[10].tQTaskRefList.ptTail;
  *(_DWORD *)&ptQTask[7].eQTaskType = ptQTask[10].ptParent;
  if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
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
  igi2_frame.ptDynCubeObj = v6 * v9;
  World_MoveDynCubeObjRadius(
    (struct World_s *)ptQTask[2].ptParent,
    (struct DynCubeObj_s *)ptQTask,
    (struct real64x3_t *)&ptQTask[8],
    igi2_frame.ptDynCubeObj);
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
  RigidDynCubeObj_UpdateAttachments((struct RigidDynCubeObj_t *)ptQTask);
  v11 = ptQTask[13].ptParent;
  ptMiddle = ptQTask[14].tQTaskChildren.ptMiddle;
  LOBYTE(ptQTask[13].tQTaskRefList.ptHead) = 0;
  LOBYTE(ptQTask[11].tQTaskChildren.ptTail) = 0;
  ptQTask[13].tQTaskRefList.ptMiddle = nullptr;
  *(_DWORD *)&ptQTask[13].eQTaskType = -1;
  ptQTask[13].tQTaskRefList.ptTail = (struct QReference_s *)v11;
  ptQTask[14].tQTaskChildren.ptHead = ptMiddle;
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[11].tQTaskRefList, ptQTask);
  v13 = Attach_eAttachEvent;
  ptQTask[5].tQTaskChildren.ptTail = (struct QTask_s *)-1;
  ptQTask[5].tQTaskRefList.ptHead = nullptr;
  QTask_TriggerQTaskEventParent(ptQTask, v13, &ptQTask[5].tQTaskChildren.ptTail);
  ModelObj_CalcRelativePosAndOrientation((struct ModelObj_s *)ptQTask);
}

// source: j/0/objects/explodeobject.c:525  [size~]
void __cdecl ExplodeObject_UpdateInternalDataAfterLoadHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptParent; // esi

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
}

// source: j/0/objects/explodeobject.c:571  [size]
void __cdecl ExplodeObject_UpdateAttachmentHandler(struct QTask_s *ptQTask)
{
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Attach_eUpdateAttachmentEvent][SectorInteriorObject_eQTaskType].pfHandler)(ptQTask);
  qmemcpy(&ptQTask[8].tQTaskRefList.ptMiddle, &ptQTask[3].ptPrev, sizeof(struct QTask_s));
  qmemcpy(&ptQTask[8], &ptQTask[1], 0x18u);
}

// source: j/0/objects/explodeobject.c:593  [anchor-mhash]
void __cdecl ExplodeObject_WeaponHitHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v2; // esi
  float *v3; // edi
  int v4; // ecx
  int v5; // eax
  void (__cdecl *pfHandler)(int, struct QTask_s **); // eax
  double v7; // st7

  v2 = ptQTask;
  if ( !LOBYTE(ptQTask[11].tQTaskChildren.ptTail) && *(float *)&ptQTask[13].tQTaskRefList.ptTail >= 0.0 )
  {
    v3 = (float *)pxContext;
    v4 = *((_DWORD *)pxContext + 5);
    if ( v4 )
    {
      v5 = *((_DWORD *)pxContext + 7);
      if ( v5 )
      {
        if ( *(_BYTE *)(v5 + 177) )
        {
          pfHandler = (void (__cdecl *)(int, struct QTask_s **))QTask_aatQTaskFinalEvent[Human_eHitByYouQTaskEvent][*(unsigned __int16 *)(v4 + 36)].pfHandler;
          if ( pfHandler )
            pfHandler(v4, &ptQTask);
        }
      }
    }
    v7 = v3[1] + *(float *)&v2[13].tQTaskRefList.ptMiddle;
    *(float *)&v2[13].tQTaskRefList.ptMiddle = v7;
    if ( v7 >= *(float *)&v2[13].tQTaskRefList.ptTail )
      *(_DWORD *)&v2[13].eQTaskType = 0;
  }
}

// source: j/0/objects/explodeobject.c:636  [anchor-mhash]
void __cdecl ExplodeObject_ExplosionHitHandler(struct QTask_s *ptQTask, void *pxContext)
{
  double v2; // st7
  double v3; // st7
  int *v4; // eax
  int v5; // eax
  double v6; // st6
  double v7; // st7
  float ptExplosionHitContext; // [esp+0h] [ebp-1Ch]

  if ( !LOBYTE(ptQTask[11].tQTaskChildren.ptTail)
    && ptQTask[2].tQTaskChildren.ptHead
    && *(float *)&ptQTask[13].tQTaskRefList.ptTail >= 0.0 )
  {
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
    v7 = GameFunctions_ResolveExplosionHit(
           (struct ExplosionHitContext_t *)pxContext,
           ptQTask,
           (struct real64x3_t *)&ptQTask[1],
           ptExplosionHitContext,
           true)
       + *(float *)&ptQTask[13].tQTaskRefList.ptMiddle;
    *(float *)&ptQTask[13].tQTaskRefList.ptMiddle = v7;
    if ( v7 >= *(float *)&ptQTask[13].tQTaskRefList.ptTail )
      *(_DWORD *)&ptQTask[13].eQTaskType = (__int64)(*(float *)&ptQTask[14].tQTaskChildren.ptTail * 30.0);
  }
}

// source: j/0/objects/explodeobject.c:676  [size]
void __cdecl ExplodeObject_RegisterScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( !BYTE1(ptQTask[11].tQTaskChildren.ptTail) )
  {
    BYTE1(ptQTask[11].tQTaskChildren.ptTail) = 1;
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.isExploded", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      &ptQTask[11].tQTaskChildren.ptTail,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
  }
}

// source: j/0/objects/explodeobject.c:706  [size]
void __cdecl ExplodeObject_RemoveScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( BYTE1(ptQTask[11].tQTaskChildren.ptTail) )
  {
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.isExploded", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    BYTE1(ptQTask[11].tQTaskChildren.ptTail) = 0;
  }
}

// source: j/0/objects/explodeobject.c:738  [size]
void __cdecl ExplodeObject_SetPositionHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: j/0/objects/explodeobject.c:819  [size]
void __cdecl ExplodeObject_WeaponCollisionEvaluateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_BYTE *)pxContext = ptQTask != *((struct QTask_s **)pxContext + 1)
                     && ptQTask != *((struct QTask_s **)pxContext + 2)
                     && ptQTask != *((struct QTask_s **)pxContext + 3);
}

// source: j/0/objects/explodeobject.c:849  [size]
unsigned __int16 __cdecl ExplodeObject_GetQTaskType()
{
  return ExplodeObject_eQTaskType;
}

// source: j/0/objects/explodeobject.c:864  [size]
struct ParameterList_s *__cdecl ExplodeObject_GetParameterList()
{
  return ExplodeObject_ptParameterList;
}

// source: j/0/objects/explodeobject.c:879  [size]
struct ParameterList_s *__cdecl ExplodeObject_GetSerializeParameterList()
{
  return ExplodeObject_ptSerializeParameterList;
}

// source: j/0/objects/explodeobject.c:903  [anchor-callee]
void __cdecl ExplodeObject_SetParameters(
        struct QTask_s *ptQTask,
        float vMaxDamageScale,
        float vRadius,
        float vFallOffRadius,
        float vExplosionDamageScale,
        float vDelay,
        int nFragment,
        int nFireBall,
        char *zExplosionSound)
{
  int v9; // edx
  char v10; // al

  *(float *)&ptQTask[13].ptParent = vMaxDamageScale;
  *(float *)&ptQTask[14].ptNext = vRadius;
  *(float *)&ptQTask[14].ptPrev = vFallOffRadius;
  *(float *)&ptQTask[14].tQTaskChildren.ptMiddle = vExplosionDamageScale;
  *(float *)&ptQTask[14].tQTaskChildren.ptHead = vExplosionDamageScale;
  *(float *)&ptQTask[14].tQTaskChildren.ptTail = vDelay;
  ptQTask[14].tQTaskRefList.ptHead = (struct QReference_s *)nFragment;
  ptQTask[14].tQTaskRefList.ptMiddle = (struct QReference_s *)nFireBall;
  v9 = (char *)&ptQTask[14].tQTaskRefList.ptTail - zExplosionSound;
  do
  {
    v10 = *zExplosionSound;
    zExplosionSound[v9] = *zExplosionSound;
    ++zExplosionSound;
  }
  while ( v10 );
}

// source: j/0/objects/explodeobject.c:933  [anchor-mhash]
struct QTask_s *__cdecl ExplodeObject_SetExploded(struct QTask_s *ptQTask)
{
  struct QTask_s *result; // eax
  struct QTask_s *ptHead; // ecx
  int v4; // edx
  struct QTask_s *v5; // eax
  int v6; // edi
  int v7; // edx

  result = (struct QTask_s *)MTP_GetLODVirModelExistsFn((char *)&ptQTask[10]);
  if ( result )
  {
    if ( result != *(struct QTask_s **)&ptQTask[2].eQTaskType )
    {
      ModelObj_SetLODVirModel((struct ModelObj_s *)ptQTask, (struct LODVirModel_s *)result, false);
      ptQTask[7].tQTaskRefList.ptHead = nullptr;
      ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
      ptQTask[7].tQTaskRefList.ptTail = nullptr;
      ptQTask[7].ptParent = nullptr;
      *(_DWORD *)&ptQTask[7].eQTaskType = 0;
    }
    ptQTask[7].tQTaskRefList.ptHead = *(struct QReference_s **)&ptQTask[10].eQTaskType;
    ptQTask[7].tQTaskRefList.ptMiddle = (struct QReference_s *)ptQTask[11].ptNext;
    ptQTask[7].tQTaskRefList.ptTail = (struct QReference_s *)ptQTask[11].ptPrev;
    ptQTask[7].ptParent = ptQTask[11].tQTaskChildren.ptHead;
    result = ptQTask[11].tQTaskChildren.ptMiddle;
    *(_DWORD *)&ptQTask[7].eQTaskType = result;
    ptHead = ptQTask->tQTaskChildren.ptHead;
    if ( ptHead->ptNext && ptHead )
    {
      v4 = QTask_nProtectedQTaskStackOffset;
      do
      {
        if ( ptHead->ptNext )
          v5 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
        else
          v5 = nullptr;
        v6 = Mesh3D_eChangeModelQTaskEventNoContext;
        QTask_atProtectedQTaskStack[v4].ptQTask = v5;
        result = (struct QTask_s *)QTask_aatQTaskFinalEvent[v6][ptHead->eQTaskType].pfHandler;
        v7 = v4 + 1;
        QTask_nProtectedQTaskStackOffset = v7;
        if ( result )
        {
          result = (struct QTask_s *)((int (__cdecl *)(struct QTask_s *))result)(ptHead);
          v7 = QTask_nProtectedQTaskStackOffset;
        }
        ptHead = (struct QTask_s *)dword_849C7DC[v7];
        v4 = v7 - 1;
        QTask_nProtectedQTaskStackOffset = v4;
      }
      while ( ptHead );
    }
  }
  LOBYTE(ptQTask[11].tQTaskChildren.ptTail) = 1;
  return result;
}

// source: j/0/objects/explodeobject.c:975  [anchor-strings]
void __cdecl ExplodeObject_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // edx
  unsigned __int16 v3; // si

  v0 = QTask_NewQTaskType("ExplodeObject", 624, SectorInteriorObject_eQTaskType, 0, 0);
  ExplodeObject_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, ExplodeObject_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, ExplodeObject_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, ExplodeObject_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))ExplodeObject_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eUpdateInternalDataQTaskEvent,
    ExplodeObject_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(v0, GameFunctions_eWeaponHitQTaskEvent, ExplodeObject_WeaponHitHandler);
  QTask_LinkQTaskEventHandlerFn(v0, GameFunctions_eExplosionHitQTaskEvent, ExplodeObject_ExplosionHitHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eRegisterLevelScriptSymbolsEvent,
    ExplodeObject_RegisterScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eRemoveLevelScriptSymbolsEvent,
    ExplodeObject_RemoveScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 7, (void (__cdecl *)(struct QTask_s *, void *))ExplodeObject_SetPositionHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Attach_eUpdateAttachmentEvent, ExplodeObject_UpdateAttachmentHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eUpdateInternalDataAfterLoadEvent,
    ExplodeObject_UpdateInternalDataAfterLoadHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    GameFunctions_eWeaponCollisionEvaluateQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))ExplodeObject_WeaponCollisionEvaluateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    LightmapInfo_eEnumerateLightmapVirModelsEvent,
    ExplodeObject_EnumerateLightmapVirModelsHandler);
  dword_751E68 = 0;
  unk_751E6C = 0;
  unk_751E70 = 0;
  unk_751E74 = 1079574528;
  dword_751E58 = 0;
  unk_751E5C = 0;
  unk_751E60 = 0;
  unk_751E64 = 1083129856;
  v1 = (struct ParameterList_s *)Mem_AllocFn(272, 4);
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  v2 = Level_eParameterTypeObjectPos;
  v1->nParameters = 0;
  v1->nMaxParameters = 13;
  ExplodeObject_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0x140u, v2, "Position", 7u, nullptr);
  ParameterList_AddParameter(
    ExplodeObject_ptParameterList,
    0x158u,
    Level_eParameterTypeReal32x9,
    "Orientation",
    7u,
    nullptr);
  ParameterList_AddParameter(ExplodeObject_ptParameterList, 0x180u, Level_eParameterTypeString16, "Model", 7u, nullptr);
  ParameterList_AddParameter(
    ExplodeObject_ptParameterList,
    0x190u,
    Level_eParameterTypeString16,
    "Destroyed model",
    7u,
    nullptr);
  ParameterList_AddParameter(
    ExplodeObject_ptParameterList,
    0x228u,
    Level_eParameterTypeReal32,
    "Damage scale",
    7u,
    &dword_751E68);
  ParameterList_AddParameter(
    ExplodeObject_ptParameterList,
    0x230u,
    Level_eParameterTypeReal32,
    "Explosion radius",
    7u,
    &dword_751E68);
  ParameterList_AddParameter(
    ExplodeObject_ptParameterList,
    0x234u,
    Level_eParameterTypeReal32,
    "Explosion falloff radius",
    7u,
    &dword_751E68);
  ParameterList_AddParameter(
    ExplodeObject_ptParameterList,
    0x23Cu,
    Level_eParameterTypeReal32,
    "Explosion damage scale",
    7u,
    &dword_751E68);
  ParameterList_AddParameter(
    ExplodeObject_ptParameterList,
    0x240u,
    Level_eParameterTypeReal32,
    "Explosion delay",
    7u,
    &dword_751E68);
  ParameterList_AddParameter(
    ExplodeObject_ptParameterList,
    0x244u,
    Level_eParameterTypeInt32,
    "Explosion fragments",
    7u,
    &dword_751E58);
  ParameterList_AddParameter(
    ExplodeObject_ptParameterList,
    0x248u,
    Level_eParameterTypeInt32,
    "Explosion fireballs",
    7u,
    &dword_751E58);
  ParameterList_AddParameter(
    ExplodeObject_ptParameterList,
    0x1CCu,
    Level_eParameterTypeVarString,
    "Explosion expression",
    7u,
    nullptr);
  ParameterList_AddParameter(
    ExplodeObject_ptParameterList,
    0x24Cu,
    Level_eParameterTypeString16,
    "Explosion sound",
    7u,
    nullptr);
  v3 = ExplodeObject_eQTaskType;
  QTask_LinkQTaskEventHandlerFn(
    ExplodeObject_eQTaskType,
    Serialize_eGetSerializeParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))ExplodeObject_GetSerializeParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v3, Serialize_eDeSerializeQTaskEvent, ExplodeObject_DeSerializeHandler);
  ExplodeObject_ptSerializeParameterList = ParameterList_Derive(ModelObjParameters_ptSerializeParameterList, 4);
  ParameterList_AddParameter(
    ExplodeObject_ptSerializeParameterList,
    0x1C8u,
    Level_eParameterTypebool8,
    "isExploded",
    7u,
    nullptr);
  ParameterList_AddParameter(
    ExplodeObject_ptSerializeParameterList,
    0x21Cu,
    Level_eParameterTypebool8,
    "isExplode",
    7u,
    nullptr);
  ParameterList_AddParameter(
    ExplodeObject_ptSerializeParameterList,
    0x220u,
    Level_eParameterTypeReal32,
    "vDamage",
    7u,
    nullptr);
  ParameterList_AddParameter(
    ExplodeObject_ptSerializeParameterList,
    0x22Cu,
    Level_eParameterTypeInt32,
    "nDelay",
    7u,
    nullptr);
}

// source: j/0/objects/explodeobject.c:1056  [size]
void __cdecl ExplodeObject_Close()
{
  int v0; // esi
  int v1; // esi

  if ( ExplodeObject_ptSerializeParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&ExplodeObject_ptSerializeParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  if ( ExplodeObject_ptParameterList )
  {
    v1 = *(_DWORD *)((unsigned int)&ExplodeObject_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
  QTask_DeleteQTaskType(ExplodeObject_eQTaskType);
}
