/* j/0/weapons/aistationarygunholder.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/weapons/aistationarygunholder.c:60  [anchor-mhash]
void __cdecl AIStationaryGunHolder_DeSerializeDoneHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QReference_s *ptTail; // eax
  unsigned __int16 *pxObject; // eax

  ptTail = ptQTask[521].tQTaskRefList.ptTail;
  if ( ptTail )
  {
    pxObject = (unsigned __int16 *)ptTail->pxObject;
    if ( pxObject )
      ((void (__cdecl *)(unsigned __int16 *, void *))QTask_aatQTaskFinalEvent[Serialize_eDeSerializeDoneQTaskEvent][pxObject[18]].pfHandler)(
        pxObject,
        pxContext);
  }
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[Serialize_eDeSerializeDoneQTaskEvent][SectorInteriorObject_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
}

// source: j/0/weapons/aistationarygunholder.c:80  [size]
void __cdecl AIStationaryGunHolder_GetGunParametersHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = (char *)ptQTask + 20740;
}

// source: j/0/weapons/aistationarygunholder.c:100  [anchor-mhash]
void __cdecl AIStationaryGunHolder_UpdateAttachmentHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptNext; // eax
  int ptHead; // edx
  int v3; // eax
  struct QTask_s *v4; // ecx
  int v5; // esi
  void (__cdecl *pfHandler)(int); // ecx
  int v7; // eax
  struct QTask_s *v8; // ecx
  struct QTask_s *v9; // edx
  int v10; // esi
  void (__cdecl *v11)(struct QTask_s *); // edx
  int v12; // eax

  if ( ptQTask[2].ptParent )
  {
    ModelObj_UpdateAttachment((struct ModelObj_s *)ptQTask);
    ptNext = ptQTask[3].ptNext;
    if ( ptNext && (ptHead = (int)ptNext->tQTaskChildren.ptHead, *(_DWORD *)ptHead) && ptHead )
    {
      v3 = QTask_nProtectedQTaskStackOffset;
      do
      {
        if ( *(_DWORD *)ptHead )
          v4 = **(_DWORD **)ptHead != 0 ? *(struct QTask_s **)ptHead : nullptr;
        else
          v4 = nullptr;
        v5 = Attach_eUpdateAttachmentEvent;
        QTask_atProtectedQTaskStack[v3].ptQTask = v4;
        pfHandler = (void (__cdecl *)(int))QTask_aatQTaskFinalEvent[v5][*(unsigned __int16 *)(ptHead + 36)].pfHandler;
        v7 = v3 + 1;
        QTask_nProtectedQTaskStackOffset = v7;
        if ( pfHandler )
        {
          pfHandler(ptHead);
          v7 = QTask_nProtectedQTaskStackOffset;
        }
        ptHead = dword_849C7DC[v7];
        v3 = v7 - 1;
        QTask_nProtectedQTaskStackOffset = v3;
      }
      while ( ptHead );
    }
    else
    {
      v3 = QTask_nProtectedQTaskStackOffset;
    }
    v8 = ptQTask->tQTaskChildren.ptHead;
    if ( v8->ptNext && v8 )
    {
      do
      {
        if ( v8->ptNext )
          v9 = v8->ptNext->ptNext != nullptr ? v8->ptNext : nullptr;
        else
          v9 = nullptr;
        v10 = Attach_eUpdateAttachmentEvent;
        QTask_atProtectedQTaskStack[v3].ptQTask = v9;
        v11 = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[v10][v8->eQTaskType].pfHandler;
        v12 = v3 + 1;
        QTask_nProtectedQTaskStackOffset = v12;
        if ( v11 )
        {
          v11(v8);
          v12 = QTask_nProtectedQTaskStackOffset;
        }
        v8 = (struct QTask_s *)dword_849C7DC[v12];
        v3 = v12 - 1;
        QTask_nProtectedQTaskStackOffset = v3;
      }
      while ( v8 );
    }
    qmemcpy(&ptQTask[512].tQTaskChildren, &ptQTask[3].ptPrev, sizeof(struct QTask_s));
    qmemcpy(&ptQTask[511].tQTaskRefList.ptMiddle, &ptQTask[1], 0x18u);
  }
}

// source: j/0/weapons/aistationarygunholder.c:138  [anchor-mhash]
void __cdecl AIStationaryGunHolder_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  double v2; // st7
  bool v3; // c0
  bool v4; // c3
  double v5; // st7
  double v6; // st7
  int *v7; // eax
  int v8; // eax
  double v9; // st6
  __int16 v10; // cx
  float ptDynCubeObj; // [esp+0h] [ebp-1Ch]

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
  ptQTask[511].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[511].tQTaskRefList.ptTail = nullptr;
  ptQTask[511].ptParent = nullptr;
  *(_DWORD *)&ptQTask[511].eQTaskType = 0;
  ptQTask[512].ptNext = nullptr;
  ptQTask[512].ptPrev = nullptr;
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
    (struct real64x3_t *)&ptQTask[511].tQTaskRefList.ptMiddle,
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
  ptQTask[512].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[512].tQTaskChildren.ptTail = nullptr;
  ptQTask[512].tQTaskRefList.ptHead = nullptr;
  ptQTask[512].tQTaskRefList.ptTail = nullptr;
  ptQTask[512].ptParent = nullptr;
  *(_DWORD *)&ptQTask[512].eQTaskType = 0;
  ptQTask[513].ptPrev = nullptr;
  ptQTask[512].tQTaskChildren.ptHead = (struct QTask_s *)1065353216;
  ptQTask[512].tQTaskRefList.ptMiddle = (struct QReference_s *)1065353216;
  ptQTask[513].ptNext = (struct QTask_s *)1065353216;
  ptQTask[514].tQTaskChildren.ptHead = (struct QTask_s *)1092616192;
  LOBYTE(ptQTask[513].tQTaskChildren.ptHead) = 0;
  ptQTask[518].tQTaskChildren.ptMiddle = (struct QTask_s *)1;
  ptQTask[514].ptNext = (struct QTask_s *)1106247680;
  ptQTask[514].ptPrev = (struct QTask_s *)1106247680;
  qmemcpy(&ptQTask[3].ptPrev, &ptQTask[512].tQTaskChildren, sizeof(struct QTask_s));
  v10 = Attach_eAttachEvent;
  ptQTask[514].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[514].tQTaskChildren.ptTail = nullptr;
  ptQTask[514].tQTaskRefList.ptHead = nullptr;
  ptQTask[516].tQTaskChildren.ptHead = nullptr;
  ptQTask[516].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[516].tQTaskChildren.ptTail = nullptr;
  ptQTask[516].tQTaskRefList.ptHead = nullptr;
  ptQTask[518].tQTaskChildren.ptHead = nullptr;
  ptQTask[5].tQTaskChildren.ptTail = (struct QTask_s *)-1;
  LOBYTE(ptQTask[518].tQTaskChildren.ptTail) = 0;
  ptQTask[5].tQTaskRefList.ptHead = nullptr;
  QTask_TriggerQTaskEventParent(ptQTask, v10, &ptQTask[5].tQTaskChildren.ptTail);
  ModelObj_CalcRelativePosAndOrientation((struct ModelObj_s *)ptQTask);
  ptQTask[519].tQTaskRefList.ptMiddle = (struct QReference_s *)10000;
  ptQTask[521].tQTaskRefList.ptHead = (struct QReference_s *)1148846080;
  ptQTask[519].tQTaskRefList.ptTail = (struct QReference_s *)1135869952;
  ptQTask[519].ptParent = (struct QTask_s *)1135869952;
  ptQTask[519].tQTaskRefList.ptHead = (struct QReference_s *)1135869952;
  ptQTask[519].tQTaskChildren.ptMiddle = (struct QTask_s *)-1028390912;
  ptQTask[519].tQTaskChildren.ptTail = (struct QTask_s *)-1028390912;
  strcpy((char *)&ptQTask[518].tQTaskRefList, "700_02_1");
  LOBYTE(ptQTask[519].eQTaskType) = 0;
  ptQTask[521].tQTaskRefList.ptMiddle = (struct QReference_s *)1050253722;
  strcpy((char *)&ptQTask[520].tQTaskRefList.ptTail, "WEAPON_ID_M2HB");
  ptQTask[521].tQTaskRefList.ptTail = nullptr;
}

// source: j/0/weapons/aistationarygunholder.c:204  [anchor-mhash]
void __cdecl AIStationaryGunHolder_RunHandler(struct QTask_s *ptQTask)
{
  char ptTail; // bl
  struct QReference_s *v2; // ecx
  struct AIDetectionView_s *v3; // eax
  char *pxObject; // esi
  struct QTask_s *v5; // edx
  struct QTask_s **p_ptPrev; // esi
  struct QTask_s *ptHead; // ecx
  int v8; // edx
  struct QTask_s *v9; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v11; // edx
  struct QTask_s *ptNext; // ebp

  ptTail = (char)ptQTask[518].tQTaskChildren.ptTail;
  if ( ptQTask[516].tQTaskChildren.ptMiddle
    && ptQTask[516].tQTaskChildren.ptTail->ptNext
    && ptQTask[516].tQTaskRefList.ptHead )
  {
    ptQTask[518].tQTaskChildren.ptMiddle = (struct QTask_s *)(__int64)Level_RunLevelExpression(
                                                                        (struct LevelExpression_s *)&ptQTask[516].tQTaskChildren.ptMiddle,
                                                                        ptQTask);
  }
  if ( ptQTask[514].tQTaskChildren.ptMiddle
    && ptQTask[514].tQTaskChildren.ptTail->ptNext
    && ptQTask[514].tQTaskRefList.ptHead )
  {
    LOBYTE(ptQTask[518].tQTaskChildren.ptTail) = (__int64)Level_RunLevelExpression(
                                                            (struct LevelExpression_s *)&ptQTask[514].tQTaskChildren.ptMiddle,
                                                            ptQTask);
  }
  if ( LOBYTE(ptQTask[518].tQTaskChildren.ptTail) )
  {
    v2 = ptQTask[521].tQTaskRefList.ptTail;
    v3 = (struct AIDetectionView_s *)&ptQTask[8];
    if ( v2 && (pxObject = (char *)v2->pxObject) != nullptr )
    {
      v5 = *((struct QTask_s **)pxObject + 125);
      if ( v5 )
        GameFunctions_GetMagicVertex((struct real64x3_t *)&ptQTask[8], v5, 2);
      else
        qmemcpy(v3, pxObject + 392, 0x18u);
      p_ptPrev = (struct QTask_s **)(pxObject + 416);
      v3 = (struct AIDetectionView_s *)&ptQTask[8];
    }
    else
    {
      qmemcpy(v3, &ptQTask[1], 0x18u);
      p_ptPrev = &ptQTask[3].ptPrev;
    }
    qmemcpy(&v3->tViewOrientation, p_ptPrev, sizeof(v3->tViewOrientation));
    v3->isSecondaryViewUsed = 0;
    AIDetection_RunDetection(
      (struct AIDetection_s *)&ptQTask[11],
      v3,
      ptQTask,
      (int)ptQTask[518].tQTaskChildren.ptMiddle);
  }
  else if ( ptTail )
  {
    AIDetection_ClearDetection((struct AIDetection_s *)&ptQTask[11]);
    AIDetection_InitDetection((struct AIDetection_s *)&ptQTask[11], 1, 4u, Human_bAIDetectionQTaskMask, 4, 8);
  }
  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v8 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v9 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v9 = nullptr;
      QTask_atProtectedQTaskStack[v8].ptQTask = v9;
      pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][ptHead->eQTaskType].pfHandler;
      v11 = v8 + 1;
      QTask_nProtectedQTaskStackOffset = v11;
      if ( pfHandler )
      {
        pfHandler(ptHead);
        v11 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v11];
      v8 = v11 - 1;
      QTask_nProtectedQTaskStackOffset = v8;
    }
    while ( ptHead );
  }
  ptNext = ptQTask[3].ptNext;
  if ( ptNext )
    ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][ptNext->eQTaskType].pfHandler)(ptNext);
}

// source: j/0/weapons/aistationarygunholder.c:286  [anchor-mhash]
void __cdecl AIStationaryGunHolder_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QReference_s *ptTail; // eax

  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[514].tQTaskChildren.ptMiddle);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[516].tQTaskChildren.ptMiddle);
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
  AIDetection_ClearDetection((struct AIDetection_s *)&ptQTask[11]);
  ptTail = ptQTask[521].tQTaskRefList.ptTail;
  if ( ptTail )
    QReference_Delete(ptTail, &QTask_tQTaskRefPool);
}

// source: j/0/weapons/aistationarygunholder.c:323  [anchor-mhash]
void __cdecl AIStationaryGunHolder_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct LODVirModel_s *LODVirModelExistsFn; // eax
  double v3; // st7
  double v4; // st7
  int *v5; // eax
  int v6; // eax
  double v7; // st6
  struct QTask_s *ptParent; // esi
  unsigned int v9; // ecx
  __int16 v10; // cx
  struct QTask_s *ptNext; // ebx
  int ptHead; // eax
  int v13; // edx
  struct QTask_s *v14; // ecx
  void (__cdecl *pfHandler)(int, void *); // ecx
  int v16; // edx
  float ptDynCubeObj; // [esp+0h] [ebp-10h]

  LODVirModelExistsFn = MTP_GetLODVirModelExistsFn((char *)&ptQTask[513].tQTaskChildren);
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
    (struct real64x3_t *)&ptQTask[511].tQTaskRefList.ptMiddle,
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
  qmemcpy(&ptQTask[3].ptPrev, &ptQTask[512].tQTaskChildren, sizeof(struct QTask_s));
  RigidDynCubeObj_UpdateAttachments((struct RigidDynCubeObj_t *)ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[514].tQTaskChildren.ptMiddle, ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[516].tQTaskChildren.ptMiddle, ptQTask);
  v9 = Human_bAIDetectionQTaskMask;
  *(double *)&ptQTask[9].tQTaskRefList.ptMiddle = *(float *)&ptQTask[514].ptNext * 0.01745329238474369;
  *(double *)&ptQTask[9].ptParent = *(float *)&ptQTask[514].ptPrev * 0.01745329238474369;
  *(double *)&ptQTask[10].ptNext = *(float *)&ptQTask[514].tQTaskChildren.ptHead * 4096.0;
  AIDetection_InitDetection((struct AIDetection_s *)&ptQTask[11], 1, 4u, v9, 4, 8);
  v10 = Attach_eAttachEvent;
  ptQTask[5].tQTaskChildren.ptTail = (struct QTask_s *)-1;
  ptQTask[5].tQTaskRefList.ptHead = nullptr;
  QTask_TriggerQTaskEventParent(ptQTask, v10, &ptQTask[5].tQTaskChildren.ptTail);
  ModelObj_CalcRelativePosAndOrientation((struct ModelObj_s *)ptQTask);
  ptNext = ptQTask[3].ptNext;
  if ( ptNext )
  {
    ptHead = (int)ptNext->tQTaskChildren.ptHead;
    if ( *(_DWORD *)ptHead )
    {
      if ( ptHead )
      {
        v13 = QTask_nProtectedQTaskStackOffset;
        do
        {
          if ( *(_DWORD *)ptHead )
            v14 = **(_DWORD **)ptHead != 0 ? *(struct QTask_s **)ptHead : nullptr;
          else
            v14 = nullptr;
          QTask_atProtectedQTaskStack[v13].ptQTask = v14;
          pfHandler = (void (__cdecl *)(int, void *))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][*(unsigned __int16 *)(ptHead + 36)].pfHandler;
          v16 = v13 + 1;
          QTask_nProtectedQTaskStackOffset = v16;
          if ( pfHandler )
          {
            pfHandler(ptHead, pxContext);
            v16 = QTask_nProtectedQTaskStackOffset;
          }
          ptHead = dword_849C7DC[v16];
          v13 = v16 - 1;
          QTask_nProtectedQTaskStackOffset = v13;
        }
        while ( ptHead );
      }
    }
  }
}

// source: j/0/weapons/aistationarygunholder.c:395  [anchor-mhash]
void __cdecl AIStationaryGunHolder_UpdateInternalDataAfterLoadHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptParent; // esi
  struct QTask_s *ptNext; // eax
  struct QTask_s *FirstChildOfType; // eax

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
  ptNext = ptQTask[3].ptNext;
  if ( ptNext )
  {
    FirstChildOfType = QTask_GetFirstChildOfType(ptNext, AIStationaryGun_eQTaskType);
    if ( FirstChildOfType )
      ptQTask[521].tQTaskRefList.ptTail = QTask_NewQTaskRef(FirstChildOfType);
  }
}

// source: j/0/weapons/aistationarygunholder.c:457  [size]
void __cdecl AIStationaryGunHolder_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = AIStationaryGunHolder_ptParameterList;
}

// source: j/0/weapons/aistationarygunholder.c:473  [size]
void __cdecl AIStationaryGunHolder_GetAIDetectionHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = ptQTask + 11;
  *((_DWORD *)pxContext + 1) = ptQTask + 8;
}

// source: j/0/weapons/aistationarygunholder.c:493  [size]
void __cdecl AIStationaryGunHolder_AILineOfSightHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_BYTE *)pxContext = *((struct QTask_s **)pxContext + 2) != ptQTask && *((struct QTask_s **)pxContext + 3) != ptQTask;
}

// source: j/0/weapons/aistationarygunholder.c:521  [anchor-mhash]
void __cdecl AIStationaryGunHolder_DrawComputerObjectHandler(struct QTask_s *ptQTask, void *pxContext)
{
  double v2; // st7
  double v3; // st7
  int *v4; // ecx
  int v5; // ecx
  double v6; // st6

  *((_DWORD *)pxContext + 3) = ptQTask + 1;
  *((_DWORD *)pxContext + 4) = (char *)ptQTask + 124;
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
  *((_DWORD *)pxContext + 6) = &ComputerMenu_tComputerMenuResource.atQSpriteHilight[16];
  *((float *)pxContext + 5) = v3 * v6;
  ComputerObject_DrawSprite((struct DrawComputerObjectContext_s *)pxContext);
  *((_DWORD *)pxContext + 6) = 0;
}

// source: j/0/weapons/aistationarygunholder.c:555  [anchor-caller]
void __cdecl AIStationaryGunHolder_Open()
{
  unsigned __int16 v0; // si
  __int16 v1; // ax
  __int16 v2; // ax
  struct ParameterList_s *v3; // eax
  int v4; // edx

  v0 = QTask_NewQTaskType("AIStationaryGunHolder", 20872, SectorInteriorObject_eQTaskType, 0, 0);
  AIStationaryGunHolder_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, AIStationaryGunHolder_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eUpdateInternalDataQTaskEvent,
    AIStationaryGunHolder_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))AIStationaryGunHolder_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, AIDetection_eGetAIDetectionEvent, AIStationaryGunHolder_GetAIDetectionHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    AIDetection_eLineOfSightQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))AIStationaryGunHolder_AILineOfSightHandler);
  v1 = ComputerObject_eDrawComputerObjectQTaskEvent;
  if ( ComputerObject_eDrawComputerObjectQTaskEvent == 512 )
  {
    v1 = QTask_NewQTaskEventFn(0x200u, "DrawComputerObject");
    v0 = AIStationaryGunHolder_eQTaskType;
    ComputerObject_eDrawComputerObjectQTaskEvent = v1;
  }
  QTask_LinkQTaskEventHandlerFn(v0, v1, AIStationaryGunHolder_DrawComputerObjectHandler);
  v2 = AIStationaryGun_eGetGunParametersEvent;
  if ( AIStationaryGun_eGetGunParametersEvent == 512 )
  {
    v2 = QTask_NewQTaskEventFn(0, "AIStationaryGunGetGunParams");
    v0 = AIStationaryGunHolder_eQTaskType;
    AIStationaryGun_eGetGunParametersEvent = v2;
  }
  QTask_LinkQTaskEventHandlerFn(
    v0,
    v2,
    (void (__cdecl *)(struct QTask_s *, void *))AIStationaryGunHolder_GetGunParametersHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, AIStationaryGunHolder_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, AIStationaryGunHolder_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Attach_eUpdateAttachmentEvent,
    AIStationaryGunHolder_UpdateAttachmentHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eUpdateInternalDataAfterLoadEvent,
    AIStationaryGunHolder_UpdateInternalDataAfterLoadHandler);
  QTask_LinkQTaskEventHandlerFn(v0, Serialize_eDeSerializeDoneQTaskEvent, AIStationaryGunHolder_DeSerializeDoneHandler);
  dword_79EE5B0 = 0;
  dword_79EE5B4 = 0;
  dword_79EE5B8 = 0;
  dword_79EE5BC = 1082081280;
  dword_79EE5C0 = 0;
  dword_79EE5C4 = -1065975808;
  dword_79EE5C8 = 0;
  dword_79EE5CC = 1081507840;
  v3 = (struct ParameterList_s *)Mem_AllocFn(392, 4);
  v4 = Level_eParameterTypeObjectPos;
  v3->ptParameterListItem = (struct ParameterListItem_s *)&v3[1];
  v3->nParameters = 0;
  v3->nMaxParameters = 19;
  AIStationaryGunHolder_ptParameterList = v3;
  ParameterList_AddParameter(v3, 0x4FF0u, v4, "Position", 7u, nullptr);
  ParameterList_AddParameter(
    AIStationaryGunHolder_ptParameterList,
    0x5008u,
    Level_eParameterTypeReal32x9,
    "Orientation",
    7u,
    nullptr);
  ParameterList_AddParameter(
    AIStationaryGunHolder_ptParameterList,
    0x5030u,
    Level_eParameterTypeString32,
    "Holder model",
    7u,
    nullptr);
  ParameterList_AddParameter(
    AIStationaryGunHolder_ptParameterList,
    0x5050u,
    Level_eParameterTypeDegrees,
    "Viewcone Alpha",
    7u,
    nullptr);
  ParameterList_AddParameter(
    AIStationaryGunHolder_ptParameterList,
    0x5054u,
    Level_eParameterTypeDegrees,
    "Viewcone Gamma",
    7u,
    nullptr);
  ParameterList_AddParameter(
    AIStationaryGunHolder_ptParameterList,
    0x5058u,
    Level_eParameterTypeReal32,
    "Viewcone Length",
    7u,
    &dword_79EE5B0);
  ParameterList_AddParameter(
    AIStationaryGunHolder_ptParameterList,
    0x505Cu,
    Level_eParameterTypeVarString,
    "On expression",
    7u,
    nullptr);
  ParameterList_AddParameter(
    AIStationaryGunHolder_ptParameterList,
    0x50ACu,
    Level_eParameterTypeVarString,
    "Team expression",
    7u,
    nullptr);
  ParameterList_AddParameter(
    AIStationaryGunHolder_ptParameterList,
    0x5104u,
    Level_eParameterTypeString32,
    "Barrel model",
    7u,
    nullptr);
  ParameterList_AddParameter(
    AIStationaryGunHolder_ptParameterList,
    0x513Cu,
    Level_eParameterTypeString32,
    "Rotationsound",
    7u,
    nullptr);
  ParameterList_AddParameter(
    AIStationaryGunHolder_ptParameterList,
    0x5128u,
    Level_eParameterTypeReal32,
    "Min Alpha (deg)",
    7u,
    &dword_79EE5C0);
  ParameterList_AddParameter(
    AIStationaryGunHolder_ptParameterList,
    0x5124u,
    Level_eParameterTypeReal32,
    "Max Alpha (deg)",
    7u,
    &dword_79EE5C0);
  ParameterList_AddParameter(
    AIStationaryGunHolder_ptParameterList,
    0x512Cu,
    Level_eParameterTypeReal32,
    "Max Gamma (deg)",
    7u,
    &dword_79EE5C0);
  ParameterList_AddParameter(
    AIStationaryGunHolder_ptParameterList,
    0x5130u,
    Level_eParameterTypeInt32,
    (char *)&g_zMessage.anDR[24],
    7u,
    &dword_79EE5B0);
  ParameterList_AddParameter(
    AIStationaryGunHolder_ptParameterList,
    0x5134u,
    Level_eParameterTypeReal32,
    "Alpha speed (deg/sec)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    AIStationaryGunHolder_ptParameterList,
    0x5138u,
    Level_eParameterTypeReal32,
    "Gamma speed (deg/sec)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    AIStationaryGunHolder_ptParameterList,
    0x517Cu,
    Level_eParameterTypeReal32,
    "Beta speed (deg/sec)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    AIStationaryGunHolder_ptParameterList,
    0x5180u,
    Level_eParameterTypeReal32,
    "Accuracy (0..1)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    AIStationaryGunHolder_ptParameterList,
    0x515Cu,
    Level_eParameterTypeString32,
    "WeaponID",
    7u,
    nullptr);
  AIStationaryGunHolder_ptQTaskList = QTaskList_New(16);
}

// source: j/0/weapons/aistationarygunholder.c:641  [size]
void __cdecl AIStationaryGunHolder_Close()
{
  int v0; // esi

  if ( AIStationaryGunHolder_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&AIStationaryGunHolder_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(AIStationaryGunHolder_eQTaskType);
  QTaskList_Delete(AIStationaryGunHolder_ptQTaskList);
}

// source: j/0/weapons/aistationarygunholder.c:661  [size]
unsigned __int16 __cdecl AIStationaryGunHolder_GetQTaskType()
{
  return AIStationaryGunHolder_eQTaskType;
}

// source: j/0/weapons/aistationarygunholder.c:675  [size]
struct QTaskList_s *__cdecl AIStationaryGunHolder_GetQTaskList()
{
  return AIStationaryGunHolder_ptQTaskList;
}
