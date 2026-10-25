/* j/0/network/networkgameitem.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/network/networkgameitem.c:71  [anchor-callee]
struct NetworkGameItemNode_s *__cdecl NetworkGameItem_GetNode(int iGameItemID)
{
  struct NetworkGameItemNode_s *result; // eax
  int v2; // ecx

  result = (struct NetworkGameItemNode_s *)Flow_ptFlow->ptNetManagerQTask[6].tQTaskRefList.ptHead[4].ptNext;
  v2 = 0;
  while ( result->iGameItemID != iGameItemID )
  {
    ++v2;
    ++result;
    if ( v2 >= 256 )
      return nullptr;
  }
  return result;
}

// source: j/0/network/networkgameitem.c:107  [anchor-mhash]
void __cdecl NetworkGameItem_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v2; // eax
  int v3; // eax
  struct QTask_s *ptHead; // ecx
  int v5; // edi
  struct QTask_s *v6; // ecx
  char *v7; // ecx
  char *v8; // ecx
  char *v9; // ecx
  char *v10; // ecx
  char *v11; // ecx
  char *v12; // ecx

  v2 = (struct QTask_s *)Mem_AllocFn(4096, 4);
  ptQTask[1].tQTaskChildren.ptHead = v2;
  LOWORD(ptQTask[1].ptNext) = 1;
  HIWORD(ptQTask[1].ptNext) = 0;
  memset(v2, 0, 0x1000u);
  v3 = 48;
  do
  {
    ptHead = ptQTask[1].tQTaskChildren.ptHead;
    v5 = v3 - 48;
    *(_WORD *)((char *)&ptHead->ptNext + v5) = 0;
    *(struct QTask_s **)((char *)&ptHead->ptPrev + v5) = nullptr;
    *(struct QTask_s **)((char *)&ptHead->tQTaskChildren.ptMiddle + v5) = (struct QTask_s *)1;
    v6 = ptQTask[1].tQTaskChildren.ptHead;
    *(_WORD *)((char *)&v6->tQTaskChildren.ptTail + v5) = 0;
    *(struct QReference_s **)((char *)&v6->tQTaskRefList.ptHead + v5) = nullptr;
    *(struct QReference_s **)((char *)&v6->tQTaskRefList.ptTail + v5) = (struct QReference_s *)1;
    v7 = (char *)ptQTask[1].tQTaskChildren.ptHead + v3 - 16;
    *(_WORD *)v7 = 0;
    *((_DWORD *)v7 + 1) = 0;
    *((_DWORD *)v7 + 3) = 1;
    v8 = (char *)ptQTask[1].tQTaskChildren.ptHead + v3;
    *(_WORD *)v8 = 0;
    *((_DWORD *)v8 + 1) = 0;
    *((_DWORD *)v8 + 3) = 1;
    v9 = (char *)&ptQTask[1].tQTaskChildren.ptHead->tQTaskChildren.ptTail + v3;
    *(_WORD *)v9 = 0;
    *((_DWORD *)v9 + 1) = 0;
    *((_DWORD *)v9 + 3) = 1;
    v10 = (char *)&ptQTask[1].tQTaskChildren.ptHead->ptParent + v3;
    *(_WORD *)v10 = 0;
    *((_DWORD *)v10 + 1) = 0;
    *((_DWORD *)v10 + 3) = 1;
    v11 = (char *)&ptQTask[1].tQTaskChildren.ptHead[1].tQTaskChildren + v3;
    *(_WORD *)v11 = 0;
    *((_DWORD *)v11 + 1) = 0;
    *((_DWORD *)v11 + 3) = 1;
    v12 = (char *)&ptQTask[1].tQTaskChildren.ptHead[1].tQTaskRefList.ptMiddle + v3;
    v3 += 128;
    *(_WORD *)v12 = 0;
    *((_DWORD *)v12 + 1) = 0;
    *((_DWORD *)v12 + 3) = 1;
  }
  while ( v3 < 4144 );
}

// source: j/0/network/networkgameitem.c:146  [size]
void __cdecl NetworkGameItem_RunHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: j/0/network/networkgameitem.c:160  [size]
void __cdecl NetworkGameItem_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // eax
  int v2; // esi

  ptHead = ptQTask[1].tQTaskChildren.ptHead;
  if ( ptHead )
  {
    v2 = *(_DWORD *)((unsigned int)&ptHead[-1].eQTaskType & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v2);
    memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
    free((void *)v2);
  }
  ptQTask[1].tQTaskChildren.ptHead = nullptr;
}

// source: j/0/network/networkgameitem.c:201  [anchor-caller]
void __cdecl NetworkGameItem_GameMessageGameItemHandler(struct QTask_s *ptQTask, void *pxContext)
{
  unsigned __int16 v2; // si
  unsigned __int16 *v3; // edi
  int i; // ecx
  struct QTask_s *v5; // ebx
  int v6; // edx
  char *v7; // eax
  struct QTask_s *ptHead; // eax
  bool v9; // zf
  int v10; // eax
  struct QTask_s *v11; // eax
  int v12; // eax
  char *v13; // eax
  struct QTask_s *v14; // eax
  int v15; // eax
  struct QTask_s *v16; // eax
  int v17; // eax
  struct QTask_s *v18; // eax
  int v19; // eax
  struct QTask_s *v20; // eax
  int v21; // eax
  unsigned __int16 v22; // ax
  struct QReference_s *ptNext; // esi
  int v24; // ecx
  unsigned __int16 v25; // cx
  unsigned __int16 *pxObject; // eax
  void (__cdecl *pfHandler)(unsigned __int16 *, unsigned __int16 *); // ecx
  int j; // esi
  char *v29; // eax
  int v30; // [esp+10h] [ebp-8h]
  int v31; // [esp+14h] [ebp-4h]

  v2 = Door_eQTaskType;
  v31 = *((_DWORD *)pxContext + 3) + 8;
  v3 = (unsigned __int16 *)(*((_DWORD *)pxContext + 3) + 20);
  for ( i = 48; i < 4144; i += 128 )
  {
    v5 = ptQTask;
    v6 = i - 48;
    v7 = (char *)&ptQTask[1].tQTaskChildren.ptHead[-1] + i - 8;
    if ( *(_WORD *)v7 )
    {
      v5 = ptQTask;
      if ( *(_WORD *)(*(_DWORD *)(*((_DWORD *)v7 + 1) + 8) + 36) != v2 )
        *((_DWORD *)v7 + 3) = 1;
    }
    ptHead = v5[1].tQTaskChildren.ptHead;
    v9 = *(_WORD *)((char *)&ptHead->tQTaskChildren.ptTail + v6) == 0;
    v10 = (int)&ptHead->tQTaskChildren.ptTail + v6;
    if ( !v9 && *(_WORD *)(*(_DWORD *)(*(_DWORD *)(v10 + 4) + 8) + 36) != v2 )
      *(_DWORD *)(v10 + 12) = 1;
    v11 = v5[1].tQTaskChildren.ptHead;
    v9 = *(_WORD *)((char *)v11 + i - 16) == 0;
    v12 = (int)v11 + i - 16;
    if ( !v9 && *(_WORD *)(*(_DWORD *)(*(_DWORD *)(v12 + 4) + 8) + 36) != v2 )
      *(_DWORD *)(v12 + 12) = 1;
    v13 = (char *)v5[1].tQTaskChildren.ptHead + i;
    if ( *(_WORD *)v13 && *(_WORD *)(*(_DWORD *)(*((_DWORD *)v13 + 1) + 8) + 36) != v2 )
      *((_DWORD *)v13 + 3) = 1;
    v14 = v5[1].tQTaskChildren.ptHead;
    v9 = *(_WORD *)((char *)&v14->tQTaskChildren.ptTail + i) == 0;
    v15 = (int)&v14->tQTaskChildren.ptTail + i;
    if ( !v9 && *(_WORD *)(*(_DWORD *)(*(_DWORD *)(v15 + 4) + 8) + 36) != v2 )
      *(_DWORD *)(v15 + 12) = 1;
    v16 = v5[1].tQTaskChildren.ptHead;
    v9 = *(_WORD *)((char *)&v16->ptParent + i) == 0;
    v17 = (int)&v16->ptParent + i;
    if ( !v9 && *(_WORD *)(*(_DWORD *)(*(_DWORD *)(v17 + 4) + 8) + 36) != v2 )
      *(_DWORD *)(v17 + 12) = 1;
    v18 = v5[1].tQTaskChildren.ptHead;
    v9 = *(_WORD *)((char *)&v18[1].tQTaskChildren.ptHead + i) == 0;
    v19 = (int)&v18[1].tQTaskChildren + i;
    if ( !v9 && *(_WORD *)(*(_DWORD *)(*(_DWORD *)(v19 + 4) + 8) + 36) != v2 )
      *(_DWORD *)(v19 + 12) = 1;
    v20 = v5[1].tQTaskChildren.ptHead;
    v9 = *(_WORD *)((char *)&v20[1].tQTaskRefList.ptMiddle + i) == 0;
    v21 = (int)&v20[1].tQTaskRefList.ptMiddle + i;
    if ( !v9 && *(_WORD *)(*(_DWORD *)(*(_DWORD *)(v21 + 4) + 8) + 36) != v2 )
      *(_DWORD *)(v21 + 12) = 1;
  }
  v30 = 0;
  if ( *(_WORD *)(v31 + 8) )
  {
    do
    {
      v22 = *v3;
      ptNext = Flow_ptFlow->ptNetManagerQTask[6].tQTaskRefList.ptHead[4].ptNext;
      v24 = 0;
      while ( LOWORD(ptNext->ptNext) != v22 )
      {
        ++v24;
        ptNext = (struct QReference_s *)((char *)ptNext + 16);
        if ( v24 >= 256 )
          goto LABEL_33;
      }
      if ( !ptNext )
      {
LABEL_33:
        v25 = v3[2];
        if ( v25 == GunPickup_eQTaskType )
        {
          GunPickup_CreateFromItem(v3 + 3, v22);
        }
        else if ( v25 == Mine_eQTaskType )
        {
          Mine_CreateFromItem(v3 + 3, v22);
          v5 = ptQTask;
        }
        else if ( v25 == Bomb_eQTaskType )
        {
          sub_476CC0(v22, (int)(v3 + 3), v3);
          v5 = ptQTask;
        }
        goto LABEL_42;
      }
      pxObject = (unsigned __int16 *)ptNext->ptPrev->pxObject;
      pfHandler = (void (__cdecl *)(unsigned __int16 *, unsigned __int16 *))QTask_aatQTaskFinalEvent[NetworkGameItem_eGameItemUpdateQTaskEvent][pxObject[18]].pfHandler;
      if ( pfHandler )
        pfHandler(pxObject, v3);
      ptNext[1].ptNext = nullptr;
LABEL_42:
      v3 = (unsigned __int16 *)((char *)v3 + v3[1] + 6);
      ++v30;
    }
    while ( v30 < *(unsigned __int16 *)(v31 + 8) );
  }
  for ( j = 0; j < 4096; j += 16 )
  {
    v29 = (char *)v5[1].tQTaskChildren.ptHead + j;
    if ( *(_WORD *)v29 )
    {
      if ( *((_DWORD *)v29 + 3) )
        QTask_Delete(*(struct QTask_s **)(*((_DWORD *)v29 + 1) + 8));
    }
  }
}

// source: j/0/network/networkgameitem.c:329  [anchor-hash]
void __cdecl NetworkGameItem_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  __int16 v1; // ax
  unsigned __int16 v2; // si
  __int16 v3; // di

  BaseQTaskType = QTask_GetBaseQTaskType();
  NetworkGameItem_eQTaskType = QTask_NewQTaskType("NetworkGameItem", 52, BaseQTaskType, 0, 0);
  NetworkGameItem_eGetGameItemDataQTaskEvent = QTask_NewQTaskEventFn(0, "NetworkGI-GetItemData");
  NetworkGameItem_eGameItemUpdateQTaskEvent = QTask_NewQTaskEventFn(0, "NetworkGI-Update");
  v1 = QTask_NewQTaskEventFn(0, "NetworkGM-GameItem");
  v2 = NetworkGameItem_eQTaskType;
  v3 = v1;
  NetworkGameItem_eGameMessageGameItemQTaskEvent = v1;
  QTask_LinkQTaskEventHandlerFn(NetworkGameItem_eQTaskType, 0, NetworkGameItem_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, 1, (void (__cdecl *)(struct QTask_s *))NetworkGameItem_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, 2, NetworkGameItem_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v2, v3, NetworkGameItem_GameMessageGameItemHandler);
  NetManager_RegisterGameMessage((struct Node_s *)0x474D494D, v3, 0);
}

// source: j/0/network/networkgameitem.c:361  [anchor-hash]
void __cdecl NetworkGameItem_Close()
{
  NetManager_RemoveGameMessage(0x474D494Du);
  QTask_DeleteQTaskEvent(NetworkGameItem_eGameMessageGameItemQTaskEvent);
  QTask_DeleteQTaskEvent(NetworkGameItem_eGameItemUpdateQTaskEvent);
  QTask_DeleteQTaskEvent(NetworkGameItem_eGetGameItemDataQTaskEvent);
  QTask_DeleteQTaskType(NetworkGameItem_eQTaskType);
}

// source: j/0/network/networkgameitem.c:383  [size]
struct QTask_s *__cdecl NetworkGameItem_New(struct QTask_s *ptParentQTask)
{
  return QTask_NewFn(ptParentQTask, NetworkGameItem_eQTaskType, nullptr);
}

// source: j/0/network/networkgameitem.c:398  [size]
unsigned __int16 __cdecl NetworkGameItem_GetQTaskType()
{
  return NetworkGameItem_eQTaskType;
}

// source: j/0/network/networkgameitem.c:413  [size]
__int16 __cdecl NetworkGameItem_GetGetGameItemDataQTaskEvent()
{
  return NetworkGameItem_eGetGameItemDataQTaskEvent;
}

// source: j/0/network/networkgameitem.c:428  [size]
__int16 __cdecl NetworkGameItem_GetGameItemUpdateQTaskEvent()
{
  return NetworkGameItem_eGameItemUpdateQTaskEvent;
}

// source: j/0/network/networkgameitem.c:443  [size]
__int16 __cdecl NetworkGameItem_GetGameMessageGameItemQTaskEvent()
{
  return NetworkGameItem_eGameMessageGameItemQTaskEvent;
}

// source: j/0/network/networkgameitem.c:460  [anchor-mhash]
struct QReference_s *NetworkGameItem_GetNextGameItemNode()
{
  struct QReference_s *result; // eax
  int v1; // ecx

  result = Flow_ptFlow->ptNetManagerQTask[6].tQTaskRefList.ptHead[4].ptNext;
  v1 = 0;
  while ( LOWORD(result->ptNext) )
  {
    ++v1;
    result = (struct QReference_s *)((char *)result + 16);
    if ( v1 >= 256 )
    {
      LDebug_Error("Too many game items!");
      abort();
    }
  }
  return result;
}

// source: j/0/network/networkgameitem.c:495  [anchor-mhash]
int __cdecl NetworkGameItem_RegisterGameItem(
        struct QTask_s *ptGameItemQTask,
        unsigned __int16 iDataSize,
        unsigned __int16 iGameItemID)
{
  struct QReference_s *ptHead; // esi
  struct QReference_s *NextGameItemNode; // eax
  struct QReference_s *v5; // edi
  struct QReference_s *v6; // eax

  ptHead = Flow_ptFlow->ptNetManagerQTask[6].tQTaskRefList.ptHead;
  NextGameItemNode = NetworkGameItem_GetNextGameItemNode();
  v5 = NextGameItemNode;
  if ( iGameItemID )
    LOWORD(NextGameItemNode->ptNext) = iGameItemID;
  else
    LOWORD(NextGameItemNode->ptNext) = LOWORD(ptHead[3].ptPrev)++;
  v6 = QTask_NewQTaskRef(ptGameItemQTask);
  LOWORD(v5->pxObject) = iDataSize;
  v5->ptPrev = v6;
  v5[1].ptNext = nullptr;
  ++HIWORD(ptHead[3].ptPrev);
  LOWORD(ptHead[3].pxObject) += iDataSize + 6;
  return LOWORD(v5->ptNext);
}

// source: j/0/network/networkgameitem.c:538  [anchor-mhash]
void __cdecl NetworkGameItem_RemoveGameItem(int iGameItemID)
{
  struct QReference_s *ptHead; // esi
  struct QReference_s *ptNext; // ecx
  struct QReference_s *v3; // edi
  int v4; // eax

  ptHead = Flow_ptFlow->ptNetManagerQTask[6].tQTaskRefList.ptHead;
  ptNext = ptHead[4].ptNext;
  v3 = nullptr;
  v4 = 0;
  while ( LOWORD(ptNext->ptNext) != iGameItemID )
  {
    ++v4;
    ptNext = (struct QReference_s *)((char *)ptNext + 16);
    if ( v4 >= 256 )
      goto LABEL_6;
  }
  v3 = ptNext;
LABEL_6:
  QReference_Delete(v3->ptPrev, &QTask_tQTaskRefPool);
  v3->ptPrev = nullptr;
  LOWORD(v3->ptNext) = 0;
  if ( !--HIWORD(ptHead[3].ptPrev) )
    LOWORD(ptHead[3].ptPrev) = 1;
  LOWORD(ptHead[3].pxObject) += -6 - LOWORD(v3->pxObject);
}

// source: j/0/network/networkgameitem.c:583  [anchor-mhash]
void __cdecl NetworkGameItem_SendAllGameItemStates(int eDestination)
{
  struct QReference_s *ptHead; // edi
  int v2; // ebp
  struct NetManagerGameMessage_s *v3; // ebx
  struct Flow_t *v4; // eax
  struct QTask_s *ptNetManagerQTask; // esi
  DWORD PerformanceCounter; // eax
  struct QReference_s *ptNext; // eax
  __int16 v8; // si
  int v9; // eax
  unsigned __int16 v10; // si
  int v11; // eax
  void (__cdecl *pfHandler)(int, int *); // ecx
  struct Flow_t *v13; // eax
  int v14; // esi
  int *pxItemData; // [esp+10h] [ebp-Ch]
  unsigned __int16 iCount; // [esp+14h] [ebp-8h]
  int v17; // [esp+18h] [ebp-4h]

  ptHead = Flow_ptFlow->ptNetManagerQTask[6].tQTaskRefList.ptHead;
  v2 = 0;
  iCount = 0;
  v3 = (struct NetManagerGameMessage_s *)Mem_AllocFn(LOWORD(ptHead[3].pxObject) + 16, 4);
  v4 = Flow_ptFlow;
  v3->eGameMessage = 1196247373;
  ptNetManagerQTask = v4->ptNetManagerQTask;
  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  v3->nLocalTime = PerformanceCounter
                 - Timer_nStartTime
                 + (char *)ptNetManagerQTask[6].tQTaskRefList.ptMiddle
                 - (char *)ptNetManagerQTask[6].tQTaskRefList.ptTail;
  pxItemData = &v3[1].nLocalTime;
  v17 = 256;
  do
  {
    ptNext = ptHead[4].ptNext;
    v8 = *(_WORD *)((char *)&ptNext->pxObject + v2);
    v9 = *(int *)((char *)&ptNext->ptPrev + v2);
    v10 = v8 + 6;
    if ( v9 )
    {
      v11 = *(_DWORD *)(v9 + 8);
      if ( v11 )
      {
        pfHandler = (void (__cdecl *)(int, int *))QTask_aatQTaskFinalEvent[NetworkGameItem_eGetGameItemDataQTaskEvent][*(unsigned __int16 *)(v11 + 36)].pfHandler;
        if ( pfHandler )
          pfHandler(v11, pxItemData);
        pxItemData = (int *)((char *)pxItemData + v10);
        ++iCount;
      }
    }
    v2 += 16;
    --v17;
  }
  while ( v17 );
  v13 = Flow_ptFlow;
  LOWORD(v3[1].eGameMessage) = iCount;
  NetManager_SendGameMessage(
    eDestination,
    (int)v13->ptNetManagerQTask[6].tQTaskChildren.ptMiddle,
    NETWORKQUEUE_MEDIUMPRIORITY,
    v3,
    LOWORD(ptHead[3].pxObject) + 16);
  v14 = *(_DWORD *)((unsigned int)&v3[-1].nLocalTime & 0xFFFFFFFC);
  --Mem_nCurrentAllocations;
  Node_Remove((_DWORD **)v14);
  memset(*(void **)(v14 + 8), 0xCDu, *(_DWORD *)(v14 + 16));
  free((void *)v14);
}

// source: j/0/network/networkgameitem.c:663  [anchor-callee]
struct QTask_s *__cdecl NetworkGameItem_GetQTaskFromID(int iGameItemID)
{
  struct QReference_s *ptNext; // eax
  int v2; // ecx
  struct QReference_s *ptPrev; // eax

  ptNext = Flow_ptFlow->ptNetManagerQTask[6].tQTaskRefList.ptHead[4].ptNext;
  v2 = 0;
  while ( LOWORD(ptNext->ptNext) != iGameItemID )
  {
    ++v2;
    ptNext = (struct QReference_s *)((char *)ptNext + 16);
    if ( v2 >= 256 )
      return nullptr;
  }
  ptPrev = ptNext->ptPrev;
  if ( !ptPrev )
    return nullptr;
  return (struct QTask_s *)ptPrev->pxObject;
}

// source: j/0/network/networkgameitem.c:711  [anchor-callee]
int __cdecl NetworkGameItem_GetNextGameItemID()
{
  struct QReference_s *ptHead; // eax
  int ptPrev_low; // ecx

  ptHead = Flow_ptFlow->ptNetManagerQTask[6].tQTaskRefList.ptHead;
  ptPrev_low = LOWORD(ptHead[3].ptPrev);
  LOWORD(ptHead[3].ptPrev) = ptPrev_low + 1;
  return (unsigned __int16)ptPrev_low;
}
