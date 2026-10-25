/* j/0/humanai/aidetection.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/humanai/aidetection.c:67  [anchor-callee]
char __cdecl AIDetection_IsPositionInsideView(
        struct AIDetectionView_s *ptView,
        struct real64x3_t *ptPosition)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real64x3_t v8; };
    struct { char igi2_o1[36]; float vAlphaDelta; };
    struct { char igi2_o2[40]; double vLength; };
    struct { char igi2_o3[48]; struct real64x3_t Real64x3_RotateInverse_tTemp; };
    char igi2_extent[76];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v2; // st7
  double v3; // st6
  double v4; // st5
  double v5; // st7
  double v6; // st7

  v2 = ptPosition->vX - ptView->tViewPosition.vX;
  v3 = ptPosition->vY - ptView->tViewPosition.vY;
  v4 = ptPosition->vZ - ptView->tViewPosition.vZ;
  igi2_frame.Real64x3_RotateInverse_tTemp.vX = ptView->tViewOrientation.tZ.vX * v4
                                  + ptView->tViewOrientation.tY.vX * v3
                                  + ptView->tViewOrientation.tX.vX * v2;
  igi2_frame.Real64x3_RotateInverse_tTemp.vY = ptView->tViewOrientation.tZ.vY * v4
                                  + ptView->tViewOrientation.tY.vY * v3
                                  + ptView->tViewOrientation.tX.vY * v2;
  igi2_frame.Real64x3_RotateInverse_tTemp.vZ = ptView->tViewOrientation.tZ.vZ * v4
                                  + ptView->tViewOrientation.tY.vZ * v3
                                  + ptView->tViewOrientation.tX.vZ * v2;
  qmemcpy(&igi2_frame.v8, &igi2_frame.Real64x3_RotateInverse_tTemp, sizeof(igi2_frame.v8));
  igi2_frame.vLength = sqrt(
              igi2_frame.Real64x3_RotateInverse_tTemp.vY * igi2_frame.Real64x3_RotateInverse_tTemp.vY
            + igi2_frame.Real64x3_RotateInverse_tTemp.vZ * igi2_frame.Real64x3_RotateInverse_tTemp.vZ
            + igi2_frame.Real64x3_RotateInverse_tTemp.vX * igi2_frame.Real64x3_RotateInverse_tTemp.vX);
  v5 = GameFunctions_CalcAlpha(igi2_frame.v8);
  if ( v5 < 0.0 )
    v5 = -v5;
  igi2_frame.vAlphaDelta = v5;
  qmemcpy(&igi2_frame.v8, &igi2_frame.Real64x3_RotateInverse_tTemp, sizeof(igi2_frame.v8));
  v6 = GameFunctions_CalcGamma(igi2_frame.v8);
  if ( v6 < 0.0 )
    v6 = -v6;
  if ( igi2_frame.vLength <= ptView->vViewConeLength && igi2_frame.vAlphaDelta < ptView->vViewConeAlpha && v6 < ptView->vViewConeGamma )
    return 1;
  return ptView->isSecondaryViewUsed
      && igi2_frame.vLength <= ptView->vSecondaryViewConeLength
      && igi2_frame.vAlphaDelta < ptView->vSecondaryViewConeAlpha
      && v6 < ptView->vSecondaryViewConeGamma;
}

// source: j/0/humanai/aidetection.c:124  [anchor-callee]
char __cdecl AIDetection_CheckTargetVisibility(
        struct QTask_s *ptSourceQTask,
        struct real64x3_t *ptSourcePosition,
        struct QTask_s *ptTargetQTask,
        struct real64x3_t *ptTargetPosition,
        struct QMaterial_t **pptQMaterial)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct LineOfSightOutputContext_s tOutputContext; };
    struct { char igi2_o1[8]; struct AIDetectionLineOfSightContext_s tAIDetectionLineOfSightContext; };
    char igi2_extent[24];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Game_s *v5; // ecx
  __int16 v6; // dx

  v5 = Game_ptGame;
  igi2_frame.tAIDetectionLineOfSightContext.tCollisionEvaluateContext.ptQTask = ptSourceQTask;
  igi2_frame.tAIDetectionLineOfSightContext.ptDetectorTask = ptSourceQTask;
  v6 = AIDetection_eLineOfSightQTaskEvent;
  igi2_frame.tAIDetectionLineOfSightContext.ptDetecteeTask = ptTargetQTask;
  *pptQMaterial = nullptr;
  if ( World_LineOfSight(
         v5->ptWorld,
         ptSourcePosition,
         ptTargetPosition,
         v6,
         &igi2_frame.tAIDetectionLineOfSightContext.tCollisionEvaluateContext,
         Forest_bQTaskGroup | 0x98000000,
         WORLD_DYNCUBETREE_CATEGORY_ALL,
         &igi2_frame.tOutputContext) )
  {
    return 1;
  }
  if ( igi2_frame.tOutputContext.vTransparency >= 0.5 )
  {
    *pptQMaterial = igi2_frame.tOutputContext.ptQMaterial;
    return 1;
  }
  return 0;
}

// source: j/0/humanai/aidetection.c:171  [anchor-hash]
void __cdecl AIDetection_DeleteListItem(struct AIDetectionListItem_s *ptListItem)
{
  QReference_Delete(ptListItem->ptQTaskRef, &QTask_tQTaskRefPool);
  ptListItem->ptQTaskRef = nullptr;
  ptListItem->isUsed = 0;
  Node_Remove(ptListItem);
}

// source: j/0/humanai/aidetection.c:192  [anchor-callee]
struct QTask_s *__cdecl AIDetection_DeleteListItemFromQTask(
        struct AIDetection_s *ptDetection,
        struct QTask_s *ptQTask)
{
  struct QTask_s *result; // eax
  struct QReference_s **i; // ecx
  struct QReference_s **v5; // esi

  result = nullptr;
  for ( i = &ptDetection->atListItems[0].ptQTaskRef; !*((_BYTE *)i + 47) || (*i)->pxObject != ptQTask; i += 26 )
  {
    result = (struct QTask_s *)((char *)result + 1);
    if ( (int)result >= 192 )
      return result;
  }
  v5 = (struct QReference_s **)((char *)ptDetection + 104 * (_DWORD)result);
  QReference_Delete(v5[16], &QTask_tQTaskRefPool);
  v5[16] = nullptr;
  *((_BYTE *)v5 + 111) = 0;
  return (struct QTask_s *)Node_Remove((_DWORD **)v5 + 14);
}

// source: j/0/humanai/aidetection.c:222  [anchor-refs]
int __cdecl AIDetection_GetFirstFreeListItem(int a1, int a2)
{
  int v2; // eax
  _BYTE *i; // ecx

  v2 = 0;
  for ( i = (_BYTE *)(a2 + 111); *i; i += 104 )
  {
    if ( ++v2 >= 192 )
    {
      LDebug_Error("Ran out of listitems in AIDetection");
      abort();
    }
  }
  return 104 * v2 + a2 + 56;
}

// source: j/0/humanai/aidetection.c:248  [anchor-callee]
struct AIDetectionListItem_s *__cdecl AIDetection_GetListItemFromQTask(
        struct AIDetection_s *ptDetection,
        struct QTask_s *ptQTask)
{
  struct AIDetectionListItem_s *result; // eax

  result = ptDetection->tEnemyList.ptHead;
  if ( result->ptNext && result )
  {
    while ( result->ptQTaskRef->pxObject != ptQTask )
    {
      result = result->ptNext;
      if ( !result->ptNext || !result )
        goto LABEL_6;
    }
  }
  else
  {
LABEL_6:
    result = ptDetection->tFriendList.ptHead;
    if ( result->ptNext && result )
    {
      while ( result->ptQTaskRef->pxObject != ptQTask )
      {
        result = result->ptNext;
        if ( !result->ptNext || !result )
          return nullptr;
      }
    }
    else
    {
      return nullptr;
    }
  }
  return result;
}

// source: j/0/humanai/aidetection.c:286  [anchor-callee]
struct AIDetectionListItem_s *__cdecl AIDetection_NewListItem(
        struct AIDetection_s *ptDetection,
        struct AIDetectionList_s *ptAddToList,
        struct QTask_s *ptQTask)
{
  struct AIDetectionListItem_s *result; // eax
  int v5; // ecx
  char *i; // eax
  struct AIDetectionListItem_s *v7; // esi
  struct LevelFlow_s *v8; // eax
  char *aisFullVisible; // eax
  struct QMaterial_t **aptQMaterial; // ecx
  int v11; // edx

  result = ptAddToList->ptHead;
  if ( ptAddToList->ptHead->ptNext && result )
  {
    while ( result->ptQTaskRef->pxObject != ptQTask )
    {
      result = result->ptNext;
      if ( !result->ptNext || !result )
        goto LABEL_6;
    }
  }
  else
  {
LABEL_6:
    v5 = 0;
    for ( i = &ptDetection->atListItems[0].isUsed; *i; i += 104 )
    {
      if ( ++v5 >= 192 )
      {
        LDebug_Error("Ran out of listitems in AIDetection");
        abort();
      }
    }
    v7 = &ptDetection->atListItems[v5];
    v7->ptQTaskRef = QTask_NewQTaskRef(ptQTask);
    v8 = LevelFlow_ptLevelFlow;
    v7->nTicksToConeUpdate = 0;
    v7->nTicksToFullUpdate = 0;
    v7->nDetectionTick = v8->nTick;
    v7->nBecameVisibleTick = v8->nTick;
    LODWORD(v7->vDistance) = 0;
    HIDWORD(v7->vDistance) = 0;
    aisFullVisible = v7->aisFullVisible;
    aptQMaterial = v7->aptQMaterial;
    v11 = 3;
    do
    {
      *(aisFullVisible - 3) = 0;
      *aisFullVisible = 0;
      *aptQMaterial++ = nullptr;
      ++aisFullVisible;
      --v11;
    }
    while ( v11 );
    v7->nCurrentDetectionPosition = 0;
    v7->isHasBeenFullVisible = 0;
    v7->isUsed = 1;
    v7->isCreatedByGunShot = 0;
    v7->isIdentifying = 0;
    v7->isKeepInListAfterLostSight = 0;
    LODWORD(v7->tLastVisiblePosition.vX) = 0;
    HIDWORD(v7->tLastVisiblePosition.vX) = 0;
    LODWORD(v7->tLastVisiblePosition.vY) = 0;
    HIDWORD(v7->tLastVisiblePosition.vY) = 0;
    LODWORD(v7->tLastVisiblePosition.vZ) = 0;
    HIDWORD(v7->tLastVisiblePosition.vZ) = 0;
    v7->ptPrev = nullptr;
    v7->ptNext = nullptr;
    return (struct AIDetectionListItem_s *)List_AddTail(v7, (int)ptAddToList);
  }
  return result;
}

// source: j/0/humanai/aidetection.c:353  [anchor-hash]
void __cdecl AIDetection_Open()
{
  AIDetection_ptRunDetectionProfileRegion = nullptr;
  AIDetection_ptRunDetectionCheckProfileRegion = nullptr;
  AIDetection_ptFindMatchingListItemProfileRegion = nullptr;
  AIDetection_ptDetectionQTaskList = QTaskList_New(192);
  memset32(AIDetection_aeMaskQTaskTypeList, 33554944, 0x10u);
  AIDetection_eLineOfSightQTaskEvent = QTask_NewQTaskEventFn(0, "AIDetection_LineOfSight");
  AIDetection_eGetDetectionInfoQTaskEvent = QTask_NewQTaskEventFn(0, "AIDetection_GetDetectionInfo");
  AIDetection_eGetAIDetectionEvent = QTask_NewQTaskEventFn(0, "AIDetection_eGetAIDetectionEvent");
}

// source: j/0/humanai/aidetection.c:385  [size]
void __cdecl AIDetection_Close()
{
  QTask_DeleteQTaskEvent(AIDetection_eLineOfSightQTaskEvent);
  QTask_DeleteQTaskEvent(AIDetection_eGetDetectionInfoQTaskEvent);
  QTask_DeleteQTaskEvent(AIDetection_eGetAIDetectionEvent);
  QTaskList_Delete(AIDetection_ptDetectionQTaskList);
}

// source: j/0/humanai/aidetection.c:403  [size]
__int16 __cdecl AIDetection_GetLineOfSightQTaskEvent()
{
  return AIDetection_eLineOfSightQTaskEvent;
}

// source: j/0/humanai/aidetection.c:417  [size]
__int16 __cdecl AIDetection_GetGetDetectionInfoQTaskEvent()
{
  return AIDetection_eGetDetectionInfoQTaskEvent;
}

// source: j/0/humanai/aidetection.c:431  [size]
__int16 __cdecl AIDetection_GetGetAIDetectionEvent()
{
  return AIDetection_eGetAIDetectionEvent;
}

// source: j/0/humanai/aidetection.c:445  [anchor-callee]
unsigned int __cdecl AIDetection_AllocateQTaskMask(unsigned __int16 eQTaskType)
{
  int v1; // ecx

  v1 = 0;
  while ( AIDetection_aeMaskQTaskTypeList[v1] != 512 )
  {
    if ( ++v1 >= 32 )
      return 0;
  }
  AIDetection_aeMaskQTaskTypeList[v1] = eQTaskType;
  return 1 << v1;
}

// source: j/0/humanai/aidetection.c:481  [size]
void __cdecl AIDetection_FreeQTaskMask(unsigned __int16 eQTaskType)
{
  AIDetection_aeMaskQTaskTypeList[0] = 512;
}

// source: j/0/humanai/aidetection.c:506  [size]
unsigned int __cdecl AIDetection_GetQTaskMask(unsigned __int16 eQTaskType)
{
  return 1;
}

// source: j/0/humanai/aidetection.c:534  [size]
struct QTask_s *__cdecl AIDetection_AddQTaskToDetectionList(struct QTask_s *ptQTask)
{
  return (struct QTask_s *)QTaskList_Register(AIDetection_ptDetectionQTaskList, (struct QTaskList_s *)ptQTask);
}

// source: j/0/humanai/aidetection.c:549  [size]
void __cdecl AIDetection_RemoveQTaskFromDetectionList(struct QTask_s *ptQTask)
{
  QTaskList_Remove(AIDetection_ptDetectionQTaskList, ptQTask);
}

// source: j/0/humanai/aidetection.c:565  [anchor-mhash]
enum bool __cdecl AIDetection_IsQTaskInDetectionList(struct QTask_s *ptQTask)
{
  int iI; // [esp+4h] [ebp-4h] BYREF

  return QTaskList_IsQTaskRegistered(AIDetection_ptDetectionQTaskList, &iI, ptQTask);
}

// source: j/0/humanai/aidetection.c:583  [anchor-callee]
int __cdecl AIDetection_InitDetection(
        struct AIDetection_s *ptDetection,
        int eTeam,
        unsigned int bTeamCheckMask,
        unsigned int bQTaskCheckMask,
        int nConeUpdateInterval,
        int nVisualUpdateInterval)
{
  int v6; // eax
  int result; // eax
  int v8; // ecx

  ptDetection->eTeam = eTeam;
  ptDetection->bQTaskCheckMask = bQTaskCheckMask;
  v6 = AIDetection_nDisplaceTick;
  ptDetection->nDisplaceTick = AIDetection_nDisplaceTick;
  ptDetection->bFlags = 0;
  ptDetection->bTeamCheckMask = bTeamCheckMask;
  AIDetection_nDisplaceTick = (v6 + 1) % 4;
  ptDetection->nConeUpdateInterval = nConeUpdateInterval / 4;
  ptDetection->nVisualUpdateInterval = nVisualUpdateInterval / 4;
  ptDetection->tEnemyList.ptHead = (struct AIDetectionListItem_s *)&ptDetection->tEnemyList.ptMiddle;
  ptDetection->tEnemyList.ptTail = (struct AIDetectionListItem_s *)&ptDetection->tEnemyList;
  ptDetection->tEnemyList.ptMiddle = nullptr;
  ptDetection->tFriendList.ptHead = (struct AIDetectionListItem_s *)&ptDetection->tFriendList.ptMiddle;
  ptDetection->tFriendList.ptMiddle = nullptr;
  ptDetection->tFriendList.ptTail = (struct AIDetectionListItem_s *)&ptDetection->tFriendList;
  result = (int)&ptDetection->atListItems[0].isUsed;
  v8 = 192;
  do
  {
    *(_BYTE *)result = 0;
    result += 104;
    --v8;
  }
  while ( v8 );
  return result;
}

// source: j/0/humanai/aidetection.c:623  [anchor-callee]
void __cdecl AIDetection_RunDetectionCheck(
        struct AIDetection_s *ptDetection,
        struct AIDetectionListItem_s *ptListItem,
        struct real64x3_t *ptQTaskPosition,
        struct AIDetectionView_s *ptView,
        struct QTask_s *ptSourceQTask)
{
  struct real64x3_t *v6; // ebx
  int v7; // esi
  struct real64x3_t *v8; // edi
  struct AIDetectionView_s *v9; // edx
  int v10; // eax
  int nCurrentDetectionPosition; // eax
  struct real64x3_t *v12; // esi
  char v13; // al
  int nTicksToFullUpdate; // eax
  double v15; // st6
  double v16; // st5
  int bPrevVisible; // [esp+14h] [ebp-4h]
  int ptListItema = *(int *)&ptListItem; // [esp+20h] [ebp+8h] ARGSLOT

  bPrevVisible = ptListItem->isHasBeenFullVisible;
  if ( ptListItem->nTicksToConeUpdate && (ptDetection->bFlags & 2) == 0 )
  {
    v9 = ptView;
    v6 = ptQTaskPosition;
  }
  else
  {
    v6 = ptQTaskPosition;
    v7 = 0;
    v8 = ptQTaskPosition;
    do
    {
      v9 = ptView;
      if ( AIDetection_IsPositionInsideView(ptView, v8) )
      {
        ptListItem->aisConeVisible[v7] = 1;
      }
      else
      {
        ptListItem->aisConeVisible[v7] = 0;
        ptListItem->aisFullVisible[v7] = 0;
      }
      ++v7;
      ++v8;
    }
    while ( v7 < 3 );
    if ( !ptListItem->nTicksToConeUpdate )
      ptListItem->nTicksToConeUpdate = ptDetection->nConeUpdateInterval + 1;
  }
  v10 = 0;
  while ( !ptListItem->aisConeVisible[v10] )
  {
    if ( ++v10 >= 3 )
      goto LABEL_25;
  }
  if ( !ptListItem->nTicksToFullUpdate || (ptDetection->bFlags & 2) != 0 )
  {
    nCurrentDetectionPosition = ptListItem->nCurrentDetectionPosition;
    v12 = &v6[nCurrentDetectionPosition];
    ptListItema = nCurrentDetectionPosition;
    v13 = AIDetection_CheckTargetVisibility(
            ptSourceQTask,
            &v9->tViewPosition,
            (struct QTask_s *)ptListItem->ptQTaskRef->pxObject,
            v12,
            &ptListItem->aptQMaterial[nCurrentDetectionPosition]);
    ptListItem->aisFullVisible[ptListItema] = v13;
    ptListItem->isHasBeenFullVisible |= v13;
    if ( ptListItem->aisFullVisible[ptListItema] )
    {
      ptListItem->isCreatedByGunShot = 0;
      if ( !bPrevVisible )
        ptListItem->nBecameVisibleTick = LevelFlow_ptLevelFlow->nTick;
      qmemcpy(&ptListItem->tLastVisiblePosition, v12, sizeof(ptListItem->tLastVisiblePosition));
    }
    nTicksToFullUpdate = ptListItem->nTicksToFullUpdate;
    v6 = ptQTaskPosition;
    ptListItem->nCurrentDetectionPosition = (ptListItem->nCurrentDetectionPosition + 1) % 3;
    if ( !nTicksToFullUpdate )
      ptListItem->nTicksToFullUpdate = ptDetection->nVisualUpdateInterval + 1;
    v9 = ptView;
  }
  --ptListItem->nTicksToFullUpdate;
LABEL_25:
  --ptListItem->nTicksToConeUpdate;
  v15 = v9->tViewPosition.vY - v6->vY;
  v16 = v9->tViewPosition.vZ - v6->vZ;
  ptListItem->vDistance = sqrt(v16 * v16 + v15 * v15 + (v9->tViewPosition.vX - v6->vX) * (v9->tViewPosition.vX - v6->vX));
}

// source: j/0/humanai/aidetection.c:706  [anchor-callee]
void __cdecl AIDetection_RemoveDeadItems(struct AIDetection_s *ptDetection)
{
  struct AIDetectionListItem_s *ptHead; // esi
  struct MemPoolFreeItem_s *ptQTaskRef; // eax
  struct AIDetectionListItem_s *v3; // esi
  struct MemPoolFreeItem_s *v4; // eax

  ptHead = ptDetection->tEnemyList.ptHead;
  while ( ptHead->ptNext && ptHead )
  {
    ptQTaskRef = (struct MemPoolFreeItem_s *)ptHead->ptQTaskRef;
    if ( ptQTaskRef[2].ptNext )
    {
      ptHead = ptHead->ptNext;
    }
    else
    {
      if ( ptQTaskRef->ptNext )
        ptQTaskRef = (struct MemPoolFreeItem_s *)Node_Remove(ptQTaskRef);
      --QTask_tQTaskRefPool.nAllocatedBlocks;
      ptQTaskRef->ptNext = QTask_tQTaskRefPool.tMemPoolFreeList.ptHead;
      QTask_tQTaskRefPool.tMemPoolFreeList.ptHead = ptQTaskRef;
      ptHead->ptQTaskRef = nullptr;
      ptHead->isUsed = 0;
      Node_Remove(ptHead);
      ptHead = ptDetection->tEnemyList.ptHead;
    }
  }
  v3 = ptDetection->tFriendList.ptHead;
  while ( v3->ptNext && v3 )
  {
    v4 = (struct MemPoolFreeItem_s *)v3->ptQTaskRef;
    if ( v4[2].ptNext )
    {
      v3 = v3->ptNext;
    }
    else
    {
      if ( v4->ptNext )
        v4 = (struct MemPoolFreeItem_s *)Node_Remove(v4);
      --QTask_tQTaskRefPool.nAllocatedBlocks;
      v4->ptNext = QTask_tQTaskRefPool.tMemPoolFreeList.ptHead;
      QTask_tQTaskRefPool.tMemPoolFreeList.ptHead = v4;
      v3->ptQTaskRef = nullptr;
      v3->isUsed = 0;
      Node_Remove(v3);
      v3 = ptDetection->tFriendList.ptHead;
    }
  }
}

// source: j/0/humanai/aidetection.c:754  [anchor-callee]
void __cdecl AIDetection_RunDetection(
        struct AIDetection_s *ptDetection,
        struct AIDetectionView_s *ptView,
        struct QTask_s *ptSourceQTask,
        int eSourceQTaskTeam)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v20; };
    struct { char igi2_o1[4]; int v21; };
    struct { char igi2_o2[8]; float tDelta; };
    struct { char igi2_o3[12]; float tDelta_4; };
    struct { char igi2_o4[20]; float v24; };
    struct { char igi2_o5[24]; float v25; };
    struct { char igi2_o6[32]; struct AIDetectionGetDetectionInfoContext_s tContext; };
    char igi2_extent[124];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int nTask; // ebx
  int nTicks; // esi
  int v6; // esi
  double v7; // st3
  double v8; // st7
  struct AIDetectionListItem_s *ptHead; // eax
  struct QReference_s *ptQTaskRef; // ecx
  unsigned int bTeamCheckMask; // eax
  struct AIDetectionList_s *p_tFriendList; // edi
  bool v13; // zf
  double v14; // st3
  double v15; // st4
  struct AIDetectionListItem_s *ListItemFromQTask; // eax
  char *aisFullVisible; // ecx
  int v18; // edx
  struct AIDetectionListItem_s *v19; // eax

  nTask = AIDetection_ptDetectionQTaskList->nTask;
  nTicks = Flow_ptFlow->nTicks;
  AIDetection_RemoveDeadItems(ptDetection);
  if ( ptDetection->nDisplaceTick == nTicks % 4 && nTask > 0 )
  {
    igi2_frame.v20 = 8;
    igi2_frame.v21 = nTask;
    do
    {
      v6 = *(int *)((char *)&AIDetection_ptDetectionQTaskList->nTask + igi2_frame.v20);
      if ( (struct QTask_s *)v6 != ptSourceQTask )
      {
        igi2_frame.tDelta = *(double *)(v6 + 40) - ptView->tViewPosition.vX;
        igi2_frame.tDelta_4 = *(double *)(v6 + 48) - ptView->tViewPosition.vY;
        v7 = *(double *)(v6 + 56) - ptView->tViewPosition.vZ;
        v8 = sqrt(igi2_frame.tDelta * igi2_frame.tDelta + igi2_frame.tDelta_4 * igi2_frame.tDelta_4 + v7 * v7) + *(float *)(v6 + 76);
        if ( v8 > ptView->vViewConeLength && (!ptView->isSecondaryViewUsed || v8 > ptView->vSecondaryViewConeLength) )
        {
          ptHead = ptDetection->tEnemyList.ptHead;
          if ( !ptHead->ptNext || !ptHead )
            goto LABEL_39;
          while ( 1 )
          {
            ptQTaskRef = ptHead->ptQTaskRef;
            if ( ptQTaskRef )
            {
              if ( ptQTaskRef->pxObject == (void *)v6 )
                break;
            }
            ptHead = ptHead->ptNext;
            if ( !ptHead->ptNext || !ptHead )
              goto LABEL_39;
          }
        }
        ((void (__cdecl *)(int, struct AIDetectionGetDetectionInfoContext_s *))QTask_aatQTaskFinalEvent[AIDetection_eGetDetectionInfoQTaskEvent][*(unsigned __int16 *)(v6 + 36)].pfHandler)(
          v6,
          &igi2_frame.tContext);
        if ( !igi2_frame.tContext.isActive || (igi2_frame.tContext.bQTaskMask & ptDetection->bQTaskCheckMask) == 0 )
          goto LABEL_34;
        bTeamCheckMask = ptDetection->bTeamCheckMask;
        if ( igi2_frame.tContext.eTeam == eSourceQTaskTeam )
        {
          if ( (bTeamCheckMask & 3) == 0 )
            goto LABEL_34;
          if ( igi2_frame.tContext.isAlive )
          {
            if ( (bTeamCheckMask & 1) == 0 )
              goto LABEL_34;
            p_tFriendList = &ptDetection->tFriendList;
          }
          else
          {
            if ( (bTeamCheckMask & 2) == 0 )
              goto LABEL_34;
            p_tFriendList = &ptDetection->tFriendList;
          }
        }
        else
        {
          if ( (bTeamCheckMask & 0xC) == 0
            || (!igi2_frame.tContext.isAlive ? (v13 = (bTeamCheckMask & 8) == 0) : (v13 = (bTeamCheckMask & 4) == 0), v13) )
          {
LABEL_34:
            ListItemFromQTask = AIDetection_GetListItemFromQTask(ptDetection, (struct QTask_s *)v6);
            if ( !ListItemFromQTask )
              goto LABEL_38;
            aisFullVisible = ListItemFromQTask->aisFullVisible;
            v18 = 3;
            do
            {
              *(aisFullVisible - 3) = 0;
              *aisFullVisible++ = 0;
              --v18;
            }
            while ( v18 );
            if ( !ListItemFromQTask->isKeepInListAfterLostSight )
LABEL_38:
              AIDetection_DeleteListItemFromQTask(ptDetection, (struct QTask_s *)v6);
            goto LABEL_39;
          }
          p_tFriendList = &ptDetection->tEnemyList;
        }
        if ( (ptDetection->bFlags & 1) == 0 )
        {
          if ( QTask_IsQTaskTypeDerived(*(_WORD *)(v6 + 36), Human_eQTaskType) )
          {
            igi2_frame.v24 = *(double *)(v6 + 40) - ptView->tViewPosition.vX;
            igi2_frame.v25 = *(double *)(v6 + 48) - ptView->tViewPosition.vY;
            v14 = *(double *)(v6 + 56) - ptView->tViewPosition.vZ;
            v15 = sqrt(igi2_frame.v24 * igi2_frame.v24 + igi2_frame.v25 * igi2_frame.v25 + v14 * v14);
            if ( v15 > *(float *)(v6 + 1984) * ptView->vViewConeLength
              && v15 > *(float *)(v6 + 1984) * ptView->vSecondaryViewConeLength )
            {
              goto LABEL_34;
            }
          }
        }
        v19 = AIDetection_NewListItem(ptDetection, p_tFriendList, (struct QTask_s *)v6);
        AIDetection_RunDetectionCheck(ptDetection, v19, igi2_frame.tContext.atPosition, ptView, ptSourceQTask);
      }
LABEL_39:
      v13 = igi2_frame.v21 == 1;
      igi2_frame.v20 += 4;
      --igi2_frame.v21;
    }
    while ( !v13 );
  }
}

// source: j/0/humanai/aidetection.c:955  [anchor-callee]
void __cdecl AIDetection_ClearDetection(struct AIDetection_s *ptDetection)
{
  struct AIDetectionListItem_s *i; // esi
  struct MemPoolFreeItem_s *ptQTaskRef; // eax
  struct AIDetectionListItem_s *j; // esi
  struct MemPoolFreeItem_s *v4; // eax

  for ( i = ptDetection->tEnemyList.ptHead; i->ptNext && i; i = ptDetection->tEnemyList.ptHead )
  {
    ptQTaskRef = (struct MemPoolFreeItem_s *)i->ptQTaskRef;
    if ( ptQTaskRef->ptNext )
      ptQTaskRef = (struct MemPoolFreeItem_s *)Node_Remove(ptQTaskRef);
    --QTask_tQTaskRefPool.nAllocatedBlocks;
    ptQTaskRef->ptNext = QTask_tQTaskRefPool.tMemPoolFreeList.ptHead;
    QTask_tQTaskRefPool.tMemPoolFreeList.ptHead = ptQTaskRef;
    i->ptQTaskRef = nullptr;
    i->isUsed = 0;
    Node_Remove(i);
  }
  for ( j = ptDetection->tFriendList.ptHead; j->ptNext && j; j = ptDetection->tFriendList.ptHead )
  {
    v4 = (struct MemPoolFreeItem_s *)j->ptQTaskRef;
    if ( v4->ptNext )
      v4 = (struct MemPoolFreeItem_s *)Node_Remove(v4);
    --QTask_tQTaskRefPool.nAllocatedBlocks;
    v4->ptNext = QTask_tQTaskRefPool.tMemPoolFreeList.ptHead;
    QTask_tQTaskRefPool.tMemPoolFreeList.ptHead = v4;
    j->ptQTaskRef = nullptr;
    j->isUsed = 0;
    Node_Remove(j);
  }
}

// source: j/0/humanai/aidetection.c:984  [anchor-callee]
struct AIDetectionListItem_s *__cdecl AIDetection_FindMatchingListItem(
        struct AIDetection_s *ptDetection,
        struct QTask_s *ptQTask)
{
  struct AIDetectionListItem_s *result; // eax
  struct AIDetectionListItem_s *ptNext; // ecx
  struct AIDetectionListItem_s *v4; // ecx

  result = ptDetection->tEnemyList.ptHead;
  ptNext = result->ptNext;
  if ( result->ptNext )
  {
    while ( !result->isUsed || result->ptQTaskRef->pxObject != ptQTask )
    {
      result = ptNext;
      ptNext = ptNext->ptNext;
      if ( !ptNext )
        goto LABEL_5;
    }
  }
  else
  {
LABEL_5:
    result = ptDetection->tFriendList.ptHead;
    v4 = result->ptNext;
    if ( result->ptNext )
    {
      while ( !result->isUsed || result->ptQTaskRef->pxObject != ptQTask )
      {
        result = v4;
        v4 = v4->ptNext;
        if ( !v4 )
          return nullptr;
      }
    }
    else
    {
      return nullptr;
    }
  }
  return result;
}

// source: j/0/humanai/aidetection.c:1029  [size]
enum bool __cdecl AIDetection_IsFullVisible(
        struct AIDetectionListItem_s *ptListItem)
{
  int v1; // eax

  v1 = 0;
  while ( !ptListItem->aisFullVisible[v1] )
  {
    if ( ++v1 >= 3 )
      return false;
  }
  return true;
}

// source: j/0/humanai/aidetection.c:1054  [size]
enum bool __cdecl AIDetection_IsConeVisible(
        struct AIDetectionListItem_s *ptListItem)
{
  int v1; // eax

  v1 = 0;
  while ( !ptListItem->aisConeVisible[v1] )
  {
    if ( ++v1 >= 3 )
      return false;
  }
  return true;
}

// source: j/0/humanai/aidetection.c:1080  [size]
struct QTaskList_s *__cdecl AIDetection_GetDetectionList()
{
  return AIDetection_ptDetectionQTaskList;
}
