/* j/0/objects/cabinet.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/objects/cabinet.c:134  [size]
void __cdecl Cabinet_GetSerializeParameterlistHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = Cabinet_ptSerializeParameterList;
}

// source: j/0/objects/cabinet.c:150  [anchor-mhash]
void __cdecl Cabinet_DeSerializeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[Serialize_eDeSerializeQTaskEvent][SectorInteriorObject_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  if ( HIBYTE(ptQTask[10].ptPrev) )
  {
    LOBYTE(ptQTask[10].ptPrev) = 1;
    BYTE2(ptQTask[10].ptPrev) = 1;
  }
  if ( LOBYTE(ptQTask[10].tQTaskChildren.ptHead) )
  {
    BYTE1(ptQTask[10].ptPrev) = 1;
    BYTE2(ptQTask[10].ptPrev) = 1;
  }
}

// source: j/0/objects/cabinet.c:176  [anchor-refs]
void __cdecl Drawer_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct LODVirModel_s *LODVirModelExistsFn; // esi
  double v3; // st7
  double v4; // st7
  int *v5; // eax
  int v6; // eax
  double v7; // st6
  float ptDynCubeObj; // [esp+0h] [ebp-18h]

  LODVirModelExistsFn = MTP_GetLODVirModelExistsFn(*(char **)pxContext);
  if ( !LODVirModelExistsFn )
  {
    LDebug_Error("VirModel \"%s\" not available", *(char **)pxContext);
    abort();
  }
  ModelObj_Init((struct ModelObj_s *)ptQTask, *((struct World_s **)pxContext + 1), nullptr);
  ptQTask[7].tQTaskChildren.ptHead = nullptr;
  ptQTask[7].tQTaskChildren.ptMiddle = (struct QTask_s *)2;
  ptQTask[7].tQTaskRefList.ptHead = nullptr;
  ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[7].tQTaskRefList.ptTail = nullptr;
  ptQTask[7].ptParent = nullptr;
  *(_DWORD *)&ptQTask[7].eQTaskType = 0;
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
  World_RegisterDynCubeObjFirstTimeRadius(
    *((struct World_s **)pxContext + 1),
    (struct DynCubeObj_s *)ptQTask,
    (struct real64x3_t *)((char *)pxContext + 8),
    ptDynCubeObj,
    WORLD_DYNCUBETREE_CATEGORY_STATIONARY);
  qmemcpy(&ptQTask[3].ptPrev, (char *)pxContext + 44, sizeof(struct QTask_s));
  ptQTask[8].ptNext = *((struct QTask_s **)pxContext + 31);
  qmemcpy(&ptQTask[8].tQTaskChildren, (char *)pxContext + 8, 0x18u);
  ptQTask[8].ptParent = nullptr;
  *(_DWORD *)&ptQTask[8].eQTaskType = 0;
  ptQTask[9].ptNext = nullptr;
  ModelObj_AttachToParent((struct ModelObj_s *)ptQTask, (struct MagicObjCreateContext_s *)pxContext);
}

// source: j/0/objects/cabinet.c:238  [anchor-mhash]
void __cdecl Drawer_UpdateAttachmentHandler(struct QTask_s *ptQTask)
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

  if ( ptQTask[2].ptParent && ptQTask[5].tQTaskRefList.ptMiddle )
  {
    ModelObj_UpdateAttachment((struct ModelObj_s *)ptQTask);
    ptNext = ptQTask[3].ptNext;
    qmemcpy(&ptQTask[8].tQTaskChildren, &ptQTask[1], 0x18u);
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
  }
}

// source: j/0/objects/cabinet.c:271  [size]
void __cdecl Drawer_RunHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[16]; float Real32x3_Rotate_tTemp_8; };
    struct { char igi2_o2[20]; struct real64x3_t tPos; };
    char igi2_extent[44];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptNext; // ecx
  double v2; // st7
  double v3; // st7
  double v4; // st6
  double v5; // st7
  double v6; // st7
  int *v7; // eax
  int v8; // eax
  double v9; // st6

  ptNext = ptQTask[8].ptNext;
  if ( HIBYTE(ptNext[10].ptPrev) )
  {
    v2 = *(float *)&ptQTask[8].eQTaskType + 671088.625;
    *(float *)&ptQTask[8].eQTaskType = v2;
    if ( v2 > 819.2000122070312 )
    {
      *(_DWORD *)&ptQTask[8].eQTaskType = 1145883853;
      BYTE2(ptNext[10].ptPrev) = 0;
    }
  }
  if ( LOBYTE(ptNext[10].tQTaskChildren.ptHead) )
  {
    v3 = *(float *)&ptQTask[8].eQTaskType - 671088.625;
    *(float *)&ptQTask[8].eQTaskType = v3;
    if ( v3 < 0.0 )
    {
      *(_DWORD *)&ptQTask[8].eQTaskType = 0;
      BYTE2(ptNext[10].ptPrev) = 0;
    }
  }
  if ( BYTE1(ptNext[10].ptPrev) )
  {
    *(_DWORD *)&ptQTask[8].eQTaskType = 0;
    BYTE1(ptNext[10].ptPrev) = 0;
    BYTE2(ptNext[10].ptPrev) = 0;
  }
  if ( LOBYTE(ptNext[10].ptPrev) )
  {
    *(_DWORD *)&ptQTask[8].eQTaskType = 1145883853;
    LOBYTE(ptNext[10].ptPrev) = 0;
    BYTE2(ptNext[10].ptPrev) = 0;
  }
  v4 = *(float *)&ptQTask[3].tQTaskRefList.ptHead * *(float *)&ptQTask[8].eQTaskType
     + *(float *)&ptQTask[3].tQTaskRefList.ptMiddle * *(float *)&ptQTask[9].ptNext
     + *(float *)&ptQTask[3].tQTaskChildren.ptTail * *(float *)&ptQTask[8].ptParent;
  igi2_frame.Real32x3_Rotate_tTemp_8 = *(float *)&ptQTask[3].ptParent * *(float *)&ptQTask[8].eQTaskType
                          + *(float *)&ptQTask[3].eQTaskType * *(float *)&ptQTask[9].ptNext
                          + *(float *)&ptQTask[3].tQTaskRefList.ptTail * *(float *)&ptQTask[8].ptParent;
  igi2_frame.tPos.vX = *(float *)&ptQTask[3].tQTaskChildren.ptHead * *(float *)&ptQTask[8].eQTaskType
          + *(float *)&ptQTask[3].tQTaskChildren.ptMiddle * *(float *)&ptQTask[9].ptNext
          + *(float *)&ptQTask[3].ptPrev * *(float *)&ptQTask[8].ptParent
          + *(double *)&ptQTask[8].tQTaskChildren.ptHead;
  igi2_frame.tPos.vY = v4 + *(double *)&ptQTask[8].tQTaskChildren.ptTail;
  igi2_frame.tPos.vZ = igi2_frame.Real32x3_Rotate_tTemp_8 + *(double *)&ptQTask[8].tQTaskRefList.ptMiddle;
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
  World_MoveDynCubeObjRadius(Game_ptGame->ptWorld, (struct DynCubeObj_s *)ptQTask, &igi2_frame.tPos, igi2_frame.ptDynCubeObj);
}

// source: j/0/objects/cabinet.c:347  [anchor-mhash]
void __cdecl Drawer_DeleteHandler(struct QTask_s *ptQTask)
{
  if ( *(_DWORD *)&ptQTask[2].eQTaskType )
  {
    ModelObj_SetLODVirModel((struct ModelObj_s *)ptQTask, nullptr, false);
    ptQTask[7].tQTaskRefList.ptHead = nullptr;
    ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
    ptQTask[7].tQTaskRefList.ptTail = nullptr;
    ptQTask[7].ptParent = nullptr;
    *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  }
  World_RemoveDynCubeObj((struct World_s *)ptQTask[2].ptParent, (struct DynCubeObj_s *)ptQTask);
}

// source: j/0/objects/cabinet.c:367  [anchor-mhash]
void __cdecl Cabinet_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
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

  memset(&igi2_frame.ptPos, 0, sizeof(igi2_frame.ptPos));
  QTaskList_Register(GameFunctions_ptActivateQTaskList, (struct QTaskList_s *)ptQTask);
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
  ptQTask[8].ptNext = nullptr;
  ptQTask[8].ptPrev = nullptr;
  ptQTask[8].tQTaskChildren.ptHead = nullptr;
  ptQTask[8].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[8].tQTaskChildren.ptTail = nullptr;
  ptQTask[8].tQTaskRefList.ptHead = nullptr;
  ptQTask[8].tQTaskRefList.ptMiddle = nullptr;
  LOBYTE(ptQTask[8].tQTaskRefList.ptTail) = 0;
  strcpy((char *)&ptQTask[9].ptPrev, "tba_searchcab");
  HIBYTE(ptQTask[10].ptPrev) = 0;
  LOBYTE(ptQTask[10].tQTaskChildren.ptHead) = 0;
  BYTE1(ptQTask[10].tQTaskChildren.ptHead) = 0;
  BYTE2(ptQTask[10].tQTaskChildren.ptHead) = 0;
  ptQTask[10].tQTaskChildren.ptMiddle = nullptr;
  LOBYTE(ptQTask[10].tQTaskChildren.ptTail) = 0;
  LOBYTE(ptQTask[9].eQTaskType) = 0;
  BYTE2(ptQTask[10].ptPrev) = 0;
  BYTE1(ptQTask[10].ptPrev) = 0;
  LOBYTE(ptQTask[10].ptPrev) = 0;
  ptQTask[10].ptNext = (struct QTask_s *)1077936128;
}

void __cdecl sub_457A80(struct QTask_s *a1)
{
  struct QTask_s *ptHead; // ecx
  int v2; // edx
  struct QTask_s *v3; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v5; // edx
  struct QTask_s *ptNext; // eax

  ptHead = a1->tQTaskChildren.ptHead;
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
  ptNext = a1[3].ptNext;
  if ( ptNext && BYTE2(a1[10].ptPrev) )
    ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][ptNext->eQTaskType].pfHandler)(a1[3].ptNext);
  if ( LevelFlow_ptLevelFlow->nTick > (int)&a1[10].tQTaskChildren.ptMiddle->ptNext + 2 )
    BYTE1(a1[10].tQTaskChildren.ptHead) = 0;
  BYTE2(a1[10].tQTaskChildren.ptHead) = BYTE1(a1[10].tQTaskChildren.ptHead);
}

// source: j/0/objects/cabinet.c:449  [anchor-mhash]
void __cdecl Cabinet_DeleteHandler(struct QTask_s *ptQTask)
{
  int v1; // eax
  struct QReference_s *v2; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *); // eax

  QTaskList_Remove(GameFunctions_ptActivateQTaskList, ptQTask);
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

// source: j/0/objects/cabinet.c:483  [size]
void __cdecl Cabinet_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = Cabinet_ptParameterList;
}

// source: j/0/objects/cabinet.c:499  [anchor-mhash]
void __cdecl Cabinet_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct LODVirModel_s *LODVirModelExistsFn; // eax
  double v4; // st7
  double v5; // st7
  int *v6; // eax
  int v7; // eax
  double v8; // st6
  struct QTask_s *ptParent; // ebx
  long double v10; // st7
  long double v11; // st6
  __int16 v12; // cx
  float ptDynCubeObj; // [esp+0h] [ebp-18h]
  struct QTask_s *ptQTaska = *(struct QTask_s * *)&ptQTask; // [esp+1Ch] [ebp+4h] ARGSLOT

  LODVirModelExistsFn = MTP_GetLODVirModelExistsFn((char *)&ptQTask[8].tQTaskRefList.ptTail);
  if ( !LODVirModelExistsFn )
    LODVirModelExistsFn = nullptr;
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
  ptQTaska = (struct QTask_s *)ptQTask[8].tQTaskRefList.ptMiddle;
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
  RigidDynCubeObj_UpdateAttachments((struct RigidDynCubeObj_t *)ptQTask);
  v12 = Attach_eAttachEvent;
  ptQTask[5].tQTaskChildren.ptTail = (struct QTask_s *)-1;
  ptQTask[5].tQTaskRefList.ptHead = nullptr;
  QTask_TriggerQTaskEventParent(ptQTask, v12, &ptQTask[5].tQTaskChildren.ptTail);
  ModelObj_CalcRelativePosAndOrientation((struct ModelObj_s *)ptQTask);
}

// source: j/0/objects/cabinet.c:547  [anchor-mhash]
void __cdecl Cabinet_EvaluateActivateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { double tDelta; };
    struct { char igi2_o1[8]; double tDelta_8; };
    struct { char igi2_o2[16]; double tDelta_16; };
    struct { char igi2_o3[24]; struct real64x3_t tPos; };
    char igi2_extent[52];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v3; // st7

  GameFunctions_GetMagicVertex(&igi2_frame.tPos, ptQTask, 0);
  igi2_frame.tDelta = *((double *)pxContext + 1) - igi2_frame.tPos.vX;
  igi2_frame.tDelta_8 = *((double *)pxContext + 2) - igi2_frame.tPos.vY;
  igi2_frame.tDelta_16 = *((double *)pxContext + 3) - igi2_frame.tPos.vZ;
  v3 = *(float *)&ptQTask[3].tQTaskRefList.ptTail * igi2_frame.tDelta_16
     + *(float *)&ptQTask[3].tQTaskChildren.ptTail * igi2_frame.tDelta_8
     + *(float *)&ptQTask[3].ptPrev * igi2_frame.tDelta;
  if ( *(float *)&ptQTask[3].ptParent * igi2_frame.tDelta_16
     + *(float *)&ptQTask[3].tQTaskRefList.ptHead * igi2_frame.tDelta_8
     + *(float *)&ptQTask[3].tQTaskChildren.ptHead * igi2_frame.tDelta > 0.0 )
  {
    if ( v3 < 0.0 )
      v3 = -v3;
    if ( v3 < 3072.0 )
      GameFunctions_ResolveEvaluateActivate((struct EvaluateActivateContext_t *)pxContext, ptQTask, &igi2_frame.tPos);
  }
}

// source: j/0/objects/cabinet.c:587  [size]
void __cdecl Cabinet_GetActivateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = 3;
}

// source: j/0/objects/cabinet.c:604  [size]
void __cdecl Cabinet_ActivateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct LevelFlow_s *v2; // ecx

  v2 = LevelFlow_ptLevelFlow;
  BYTE1(ptQTask[10].tQTaskChildren.ptHead) = 1;
  ptQTask[10].tQTaskChildren.ptMiddle = (struct QTask_s *)v2->nTick;
}

// source: j/0/objects/cabinet.c:640  [size]
void __cdecl Cabinet_WeaponHitHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: j/0/objects/cabinet.c:657  [anchor-refs]
void __cdecl Cabinet_RegisterScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( !LOBYTE(ptQTask[9].eQTaskType) )
  {
    LOBYTE(ptQTask[9].eQTaskType) = 1;
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.isInUse", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      (char *)&ptQTask[10].tQTaskChildren.ptHead + 1,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.isLastInUse", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      (char *)&ptQTask[10].tQTaskChildren.ptHead + 2,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.isSearched", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      &ptQTask[10].tQTaskChildren.ptTail,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
  }
}

// source: j/0/objects/cabinet.c:693  [anchor-mhash]
void __cdecl Cabinet_RemoveScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( LOBYTE(ptQTask[9].eQTaskType) )
  {
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    LOBYTE(ptQTask[9].eQTaskType) = 0;
    sprintf(igi2_frame.zTemp, "%s.isInUse", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.isLastInUse", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.isSearched", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
  }
}

// source: j/0/objects/cabinet.c:762  [size]
struct real64x3_t *__cdecl Cabinet_GetActivatePosAndOrientation(
        struct QTask_s *ptQTask,
        struct real64x3_t *ptPos,
        struct real32x9_t *ptOrientation)
{
  qmemcpy(ptOrientation, &ptQTask[3].ptPrev, sizeof(struct real32x9_t));
  return GameFunctions_GetMagicVertex(ptPos, ptQTask, 0);
}

// source: j/0/objects/cabinet.c:785  [size]
float __cdecl Cabinet_GetActivateTime(struct QTask_s *ptQTask)
{
  return *(float *)&ptQTask[10].ptNext;
}

// source: j/0/objects/cabinet.c:801  [size]
struct QTask_s *__cdecl Cabinet_Searched(struct QTask_s *ptQTask)
{
  LOBYTE(ptQTask[10].tQTaskChildren.ptTail) = 1;
  return ptQTask;
}

// source: j/0/objects/cabinet.c:818  [size]
struct QTask_s *__cdecl Cabinet_ShutDrawer(struct QTask_s *ptQTask)
{
  BYTE1(ptQTask[10].ptPrev) = 1;
  BYTE2(ptQTask[10].ptPrev) = 1;
  return ptQTask;
}

// source: j/0/objects/cabinet.c:839  [size]
struct QTask_s *__cdecl Cabinet_OpenDrawer(struct QTask_s *ptQTask)
{
  HIBYTE(ptQTask[10].ptPrev) = 1;
  LOBYTE(ptQTask[10].tQTaskChildren.ptHead) = 0;
  BYTE2(ptQTask[10].ptPrev) = 1;
  return ptQTask;
}

// source: j/0/objects/cabinet.c:861  [size]
struct QTask_s *__cdecl Cabinet_CloseDrawer(struct QTask_s *ptQTask)
{
  LOBYTE(ptQTask[10].tQTaskChildren.ptHead) = 1;
  HIBYTE(ptQTask[10].ptPrev) = 0;
  BYTE2(ptQTask[10].ptPrev) = 1;
  return ptQTask;
}

// source: j/0/objects/cabinet.c:883  [size]
char *__cdecl Cabinet_GetActivateSound(struct QTask_s *ptQTask)
{
  return (char *)&ptQTask[9].ptPrev;
}

// source: j/0/objects/cabinet.c:902  [size]
unsigned __int16 __cdecl Cabinet_GetQTaskType()
{
  return Cabinet_eQTaskType;
}

// source: j/0/objects/cabinet.c:915  [anchor-strings]
void __cdecl Cabinet_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // edx
  unsigned __int16 v3; // si
  _DWORD *v4; // esi

  v0 = QTask_NewQTaskType("Cabinet", 424, SectorInteriorObject_eQTaskType, 0, 0);
  Cabinet_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, Cabinet_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, sub_457A80);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, Cabinet_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Cabinet_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, Cabinet_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(v0, GameFunctions_eEvaluateActivateQTaskEvent, Cabinet_EvaluateActivateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    GameFunctions_eGetActivateQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Cabinet_GetActivateHandler);
  QTask_LinkQTaskEventHandlerFn(v0, GameFunctions_eActivateQTaskEvent, Cabinet_ActivateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    GameFunctions_eWeaponHitQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Cabinet_WeaponHitHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eRegisterLevelScriptSymbolsEvent,
    Cabinet_RegisterScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Level_eRemoveLevelScriptSymbolsEvent, Cabinet_RemoveScriptSymbolsHandler);
  v1 = (struct ParameterList_s *)Mem_AllocFn(112, 4);
  v2 = Level_eParameterTypeObjectPos;
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  v1->nParameters = 0;
  v1->nMaxParameters = 5;
  Cabinet_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0x140u, v2, "Position", 7u, nullptr);
  ParameterList_AddParameter(Cabinet_ptParameterList, 0x158u, Level_eParameterTypeAngle, "Orientation", 7u, nullptr);
  ParameterList_AddParameter(Cabinet_ptParameterList, 0x15Cu, Level_eParameterTypeString16, "Model", 7u, nullptr);
  ParameterList_AddParameter(
    Cabinet_ptParameterList,
    0x190u,
    Level_eParameterTypeReal32,
    "Search Time (s)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Cabinet_ptParameterList,
    0x16Cu,
    Level_eParameterTypeString32,
    "Activate Sound",
    7u,
    nullptr);
  v3 = QTask_NewQTaskType("Drawer", 368, RigidMagicObj_eQTaskType, 0, 0);
  Drawer_eQTaskType = v3;
  QTask_LinkQTaskEventHandlerFn(v3, 0, Drawer_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v3, 1, Drawer_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v3, 2, Drawer_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v3, Attach_eUpdateAttachmentEvent, Drawer_UpdateAttachmentHandler);
  Symbol_Register(
    "TASKTYPE_DRAWER",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)v3,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  v4 = Mem_AllocFn(18444, 4);
  v4[1] = 0;
  *v4 = 0;
  v4[4610] = "TASKTYPE_DRAWER";
  Wildcard_CreateNFA("TASKTYPE_DRAWER", v4 + 2, (char *)v4 + 10248);
  List_AddTail(v4, (int)&MagicObjConfig_tTaskTypeEnumList);
  LOWORD(v4) = Cabinet_eQTaskType;
  QTask_LinkQTaskEventHandlerFn(
    Cabinet_eQTaskType,
    Serialize_eGetSerializeParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Cabinet_GetSerializeParameterlistHandler);
  QTask_LinkQTaskEventHandlerFn((unsigned __int16)v4, Serialize_eDeSerializeQTaskEvent, Cabinet_DeSerializeHandler);
  Cabinet_ptSerializeParameterList = ParameterList_Derive(ModelObjParameters_ptSerializeParameterList, 6);
  ParameterList_AddParameter(
    Cabinet_ptSerializeParameterList,
    0x197u,
    Level_eParameterTypebool8,
    "isOpenDrawer",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Cabinet_ptSerializeParameterList,
    0x198u,
    Level_eParameterTypebool8,
    "isCloseDrawer",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Cabinet_ptSerializeParameterList,
    0x199u,
    Level_eParameterTypebool8,
    "isInUse",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Cabinet_ptSerializeParameterList,
    0x19Au,
    Level_eParameterTypebool8,
    "isLastInUse",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Cabinet_ptSerializeParameterList,
    0x19Cu,
    Level_eParameterTypeInt32,
    "nLastInUseTick",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Cabinet_ptSerializeParameterList,
    0x1A0u,
    Level_eParameterTypebool8,
    (char *)&g_ptPos.vY + 4,
    7u,
    nullptr);
}

// source: j/0/objects/cabinet.c:991  [size]
void __cdecl Cabinet_Close()
{
  int v0; // esi
  int v1; // esi

  if ( Cabinet_ptSerializeParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&Cabinet_ptSerializeParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  if ( Cabinet_ptParameterList )
  {
    v1 = *(_DWORD *)((unsigned int)&Cabinet_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
  QTask_DeleteQTaskType(Drawer_eQTaskType);
  QTask_DeleteQTaskType(Cabinet_eQTaskType);
}
