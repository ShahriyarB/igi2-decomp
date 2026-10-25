/* j/0/network/server.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/network/server.c:90  [anchor-hash]
int __cdecl Server_PopFreeNID()
{
  struct QTask_s *ptPrev; // eax
  int ptNext; // esi

  ptPrev = QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, Server_eQTaskType)[1].ptPrev;
  if ( *(_DWORD *)&ptPrev->eQTaskType )
  {
    ptNext = (int)ptPrev[1].tQTaskChildren.ptHead->ptNext->ptNext;
    QObjectVector_RemoveElement((struct QObjectVector_s *)ptPrev, 0);
    return ptNext;
  }
  else
  {
    NetManager_LogMessage("Server_PopFreeNID failed, no items pooled\n");
    return -1;
  }
}

// source: j/0/network/server.c:136  [anchor-callee]
void __cdecl Server_PushFreeNID(int nID, enum bool isVerbose)
{
  struct QObjectVector_s *ptPrev; // esi
  unsigned int nAllocated; // eax
  int *v4; // ecx

  ptPrev = (struct QObjectVector_s *)QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, Server_eQTaskType)[1].ptPrev;
  if ( ptPrev->nAllocated == ptPrev->nSize )
    QObjectVector_Realloc(ptPrev, ptPrev->nReallocSize);
  nAllocated = ptPrev->nAllocated;
  v4 = (int *)ptPrev->papxElement[nAllocated];
  ptPrev->nAllocated = nAllocated + 1;
  *v4 = nID;
}

// source: j/0/network/server.c:172  [anchor-strings]
void __cdecl Server_InitNIDPool(struct Server_s *ptServer)
{
  struct QObjectVector_s *v1; // esi
  int v2; // edi
  struct QObjectVector_s *ptPrev; // esi
  unsigned int nAllocated; // eax
  _DWORD *v5; // ecx
  char zTemp[256]; // [esp+Ch] [ebp-100h] BYREF

  v1 = (struct QObjectVector_s *)Mem_AllocFn(52, 4);
  v2 = 1;
  v1->isStrictOrder = true;
  v1->nSize = 0;
  v1->nAllocated = 0;
  v1->nReallocSize = 3;
  v1->papxElement = nullptr;
  v1->nElementSize = 8;
  v1->tMemPool.nBlocks = 0;
  v1->tMemPool.nAllocatedBlocks = 0;
  v1->tMemPool.nAlignment = 4;
  v1->tMemPool.nBlockSize = 8;
  v1->tMemPool.nReAllocBlocks = 3;
  v1->tMemPool.tMemPoolFreeList.ptHead = nullptr;
  v1->tMemPool.tMemPoolSegmentList.ptHead = nullptr;
  MemPool_ReAlloc(&v1->tMemPool, 0x23u);
  QObjectVector_Realloc(v1, 0x23u);
  ptServer->ptNIDPool = v1;
  do
  {
    ptPrev = (struct QObjectVector_s *)QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, Server_eQTaskType)[1].ptPrev;
    if ( ptPrev->nAllocated == ptPrev->nSize )
      QObjectVector_Realloc(ptPrev, ptPrev->nReallocSize);
    nAllocated = ptPrev->nAllocated;
    v5 = ptPrev->papxElement[nAllocated];
    ptPrev->nAllocated = nAllocated + 1;
    *v5 = v2++;
  }
  while ( v2 < 35 );
  _snprintf(zTemp, 0xFFu, "Added IDs to the pool, [1]-[%d]\n", 34);
  NetManager_LogMessage(zTemp);
}

// source: j/0/network/server.c:202  [anchor-mhash]
enum bool __cdecl Server_RemoveFromPool(int nID)
{
  struct QObjectVector_s *ptPrev; // eax
  int nAllocated; // edx
  unsigned int v3; // ecx
  void **i; // esi

  ptPrev = (struct QObjectVector_s *)QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, Server_eQTaskType)[1].ptPrev;
  nAllocated = ptPrev->nAllocated;
  v3 = 0;
  if ( nAllocated <= 0 )
    return false;
  for ( i = ptPrev->papxElement; *(_DWORD *)*i != nID; ++i )
  {
    if ( (int)++v3 >= nAllocated )
      return false;
  }
  QObjectVector_RemoveElement(ptPrev, v3);
  return true;
}

// source: j/0/network/server.c:241  [anchor-strings]
void __cdecl Server_ResynchPool()
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s *ptQTask; };
    struct { char igi2_o1[4]; struct QTask_s *FirstChildOfType; };
    struct { char igi2_o2[8]; int v15; };
    struct { char igi2_o3[12]; char Buffer[256]; };
    char igi2_extent[268];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Flow_t *v0; // ebx
  struct QTask_s *ptPrev; // eax
  int i; // edi
  struct QObjectVector_s *v3; // esi
  unsigned int nAllocated; // eax
  int *v5; // ecx
  struct QTask_s *j; // eax
  struct QTask_s *v7; // esi
  struct QTask_s *ptNext; // edi
  struct QObjectVector_s *v9; // eax
  int v10; // edx
  signed int v11; // ecx
  void **papxElement; // esi

  v0 = Flow_ptFlow;
  igi2_frame.FirstChildOfType = QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, Server_eQTaskType);
  ptPrev = igi2_frame.FirstChildOfType[1].ptPrev;
  igi2_frame.v15 = *(_DWORD *)&ptPrev->eQTaskType;
  *(_DWORD *)&ptPrev->eQTaskType = 0;
  for ( i = 1; i < 35; ++i )
  {
    v3 = (struct QObjectVector_s *)QTask_GetFirstChildOfType(v0->ptNetManagerQTask, Server_eQTaskType)[1].ptPrev;
    if ( v3->nAllocated == v3->nSize )
    {
      QObjectVector_Realloc(v3, v3->nReallocSize);
      v0 = Flow_ptFlow;
    }
    nAllocated = v3->nAllocated;
    v5 = (int *)v3->papxElement[nAllocated];
    v3->nAllocated = nAllocated + 1;
    *v5 = i;
  }
  for ( j = QTask_GetFirstChildOfType(v0->ptNetManagerQTask, Client_eQTaskType);
        ;
        j = QTask_GetNextSiblingOfType(v7, Client_eQTaskType) )
  {
    v7 = j;
    igi2_frame.ptQTask = j;
    if ( !j )
      break;
    ptNext = j[1].ptNext;
    if ( ptNext )
    {
      v9 = (struct QObjectVector_s *)QTask_GetFirstChildOfType(v0->ptNetManagerQTask, Server_eQTaskType)[1].ptPrev;
      v10 = v9->nAllocated;
      v11 = 0;
      if ( v10 > 0 )
      {
        papxElement = v9->papxElement;
        while ( *(struct QTask_s **)*papxElement != ptNext )
        {
          ++v11;
          ++papxElement;
          if ( v11 >= v10 )
            goto LABEL_6;
        }
        QObjectVector_RemoveElement(v9, v11);
LABEL_6:
        v7 = igi2_frame.ptQTask;
      }
    }
  }
  _snprintf(
    igi2_frame.Buffer,
    0xFFu,
    "Server_ResynchPool: Retrieved %d ID(s)\n",
    *(_DWORD *)&igi2_frame.FirstChildOfType[1].ptPrev->eQTaskType - igi2_frame.v15);
  NetManager_LogMessage(igi2_frame.Buffer);
}

void __cdecl sub_453540(struct QTask_s *a1, void *a2)
{
  a1[1].tQTaskChildren.ptHead = (struct QTask_s *)-1;
  a1[1].ptPrev = nullptr;
  a1[1].tQTaskChildren.ptMiddle = *((struct QTask_s **)a2 + 5);
  a1[1].tQTaskChildren.ptTail = (struct QTask_s *)-1;
  a1[1].tQTaskRefList.ptHead = *((struct QReference_s **)a2 + 6);
  a1[1].tQTaskRefList.ptMiddle = (struct QReference_s *)-1;
  a1[1].tQTaskRefList.ptTail = nullptr;
  a1[1].ptParent = nullptr;
}

void __cdecl pfQTaskEventNoContext__(struct QTask_s *a1)
{
  QObjectVector_Delete((struct QObjectVector_s *)a1[1].ptPrev);
  a1[1].ptPrev = nullptr;
}

// source: j/0/network/server.c:365  [anchor-mhash]
void __cdecl Server_GameMessagePingHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int *v2; // ebx
  int v3; // ecx
  struct QTask_s *ptNetManagerQTask; // esi
  DWORD PerformanceCounter; // eax
  int v6; // edx
  struct ServerGameMessagePong_s tPongMessage; // [esp+8h] [ebp-Ch] BYREF

  v2 = *((int **)pxContext + 3);
  if ( NetManager_GetClientFromNetworkID(*v2) )
  {
    v3 = v2[3];
    ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
    tPongMessage.tBaseMessage.eGameMessage = 1347374663;
    tPongMessage.tBaseMessage.nLocalTime = v3;
    if ( Timer_isPerformanceCounter )
      PerformanceCounter = Timer_GetPerformanceCounter();
    else
      PerformanceCounter = GetTickCount();
    v6 = *v2;
    tPongMessage.nServerTime = PerformanceCounter
                             - Timer_nStartTime
                             + (char *)ptNetManagerQTask[6].tQTaskRefList.ptMiddle
                             - (char *)ptNetManagerQTask[6].tQTaskRefList.ptTail;
    NetManager_SendGameMessage(v6, 0, NETWORKQUEUE_MEDIUMPRIORITY, &tPongMessage.tBaseMessage, 0xCu);
  }
}

// source: j/0/network/server.c:416  [anchor-hash]
void __cdecl Server_GameMessagePongHandler(struct QTask_s *ptQTask, void *pxContext)
{
  if ( Timer_isPerformanceCounter )
    Timer_GetPerformanceCounter();
  else
    GetTickCount();
}

// source: j/0/network/server.c:457  [size]
void __cdecl Server_GameMessageObjectiveHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct NetManagerGameMessage_s *v2; // edi
  struct QTask_s *v3; // esi
  struct Flow_t *v4; // ebp
  unsigned __int16 v5; // dx
  struct QTask_s *v6; // eax
  int ptNext; // eax

  v2 = *((struct NetManagerGameMessage_s **)pxContext + 3);
  v3 = nullptr;
LABEL_2:
  v4 = Flow_ptFlow;
  v5 = Client_eQTaskType;
  while ( 1 )
  {
    v6 = v3 ? QTask_GetNextSiblingOfType(v3, v5) : QTask_GetFirstChildOfType(v4->ptNetManagerQTask, v5);
    v3 = v6;
    if ( !v6 )
      break;
    ptNext = (int)v6[1].ptNext;
    if ( (struct QTask_s *)ptNext != v4->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
    {
      NetManager_SendGameMessage(ptNext, v2->eGameMessage, NETWORKQUEUE_GUARANTEED, v2 + 1, 0x14u);
      goto LABEL_2;
    }
  }
}

// source: j/0/network/server.c:501  [anchor-callee]
void __cdecl Server_SendChallengeTo(struct Server_s *ptServer, struct Client_s *ptClient)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zChallenge[8]; };
    struct { char igi2_o1[8]; struct ClientGameMessageAuthenticate_s tGameMessage; };
    char igi2_extent[108];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  DWORD PerformanceCounter; // eax
  unsigned int v3; // ecx
  int v4; // esi
  int v5; // edi
  int i; // ebp
  unsigned int v7; // edx
  char v8; // dl
  int v9; // eax
  char v10; // cl
  DWORD TickCount; // eax
  int eNetworkID; // edx

  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  v3 = (PerformanceCounter - Timer_nStartTime) ^ 0xC8FB1A07;
  v4 = ((PerformanceCounter - Timer_nStartTime) << 15) + 971667286;
  v5 = 2146516173 - ((PerformanceCounter - Timer_nStartTime) << 9);
  for ( i = 0; i < 7; ++i )
  {
    v5 ^= v3 >> 7;
    v4 ^= v5;
    v3 += v4;
    v7 = v3 % 0x3E;
    if ( v3 % 0x3E > 9 )
    {
      if ( (unsigned __int8)v7 < 0xAu || (unsigned __int8)v7 > 0x23u )
        v8 = v7 + 61;
      else
        v8 = v7 + 55;
    }
    else
    {
      v8 = v7 + 48;
    }
    igi2_frame.zChallenge[i] = v8;
  }
  Server_tRandomState.anRandom[0] = v3;
  Server_tRandomState.anRandom[1] = v4;
  Server_tRandomState.anRandom[2] = v5;
  igi2_frame.zChallenge[7] = 0;
  igi2_frame.tGameMessage.isChallenge = 1;
  igi2_frame.tGameMessage.isResponse = 0;
  igi2_frame.tGameMessage.nLength = strlen(igi2_frame.zChallenge);
  v9 = 0;
  do
  {
    v10 = igi2_frame.zChallenge[v9];
    igi2_frame.tGameMessage.zText[v9++] = v10;
  }
  while ( v10 );
  strcpy((char *)&ptClient[1].tQTask.tQTaskChildren.ptMiddle, igi2_frame.zChallenge);
  igi2_frame.tGameMessage.eClient = ptClient->eNetworkID;
  igi2_frame.tGameMessage.tBaseMessage.eGameMessage = 1096111176;
  if ( Timer_isPerformanceCounter )
    TickCount = Timer_GetPerformanceCounter();
  else
    TickCount = GetTickCount();
  eNetworkID = ptClient->eNetworkID;
  igi2_frame.tGameMessage.tBaseMessage.nLocalTime = TickCount - Timer_nStartTime;
  NetManager_SendGameMessage(
    eNetworkID,
    (int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle,
    NETWORKQUEUE_GUARANTEED,
    &igi2_frame.tGameMessage.tBaseMessage,
    0x64u);
}

void __cdecl authfn__(int eClientNetworkID, int a2, char *a3)
{
  char *LocalizedStringForLanguage; // eax
  struct QReference_s *ptTail; // eax
  char Buffer[256]; // [esp+Ch] [ebp-100h] BYREF

  _snprintf(Buffer, 0xFFu, "Server_AuthCallBack: %d %d '%s'\n", eClientNetworkID, a2, a3);
  NetManager_LogMessage(Buffer);
  if ( NetManager_GetClientFromNetworkID(eClientNetworkID) )
  {
    LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                   "mp/CD_OK",
                                   Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                   true);
    _snprintf(Buffer, 0xFFu, "[%d] %s", eClientNetworkID, LocalizedStringForLanguage);
    if ( StatusScreen_ptStatusScreenQTask )
    {
      ptTail = StatusScreen_ptStatusScreenQTask[52].tQTaskRefList.ptTail;
      if ( ptTail )
        TextScroller_Add((struct TextScroller_s *)ptTail, Buffer, TEXTSCROLLER_COLOUR_WHITE);
    }
    NetManager_LogMessage(Buffer);
    NetManager_LogMessage("\r\n");
  }
  else
  {
    _snprintf(Buffer, 0xFFu, "Server_AuthCallBack: Got response on non-existant client[%d]\n", eClientNetworkID);
    NetManager_LogMessage(Buffer);
  }
}

void __cdecl sub_453970(struct QTask_s *a1, _DWORD *a2)
{
  int v2; // esi
  char v3; // al
  int v4; // esi
  struct Client_s *ClientFromNetworkID; // eax
  char *p_ptMiddle; // edi
  int eNetworkID; // edx
  unsigned int UserIPByNetworkID; // eax

  v2 = a2[3];
  v3 = *(_BYTE *)(v2 + 105);
  v4 = v2 + 8;
  if ( v3 )
  {
    ClientFromNetworkID = NetManager_GetClientFromNetworkID(*(_DWORD *)(v4 + 8));
    if ( ClientFromNetworkID )
    {
      p_ptMiddle = (char *)&ClientFromNetworkID[1].tQTask.tQTaskChildren.ptMiddle;
      if ( strlen((char *)&ClientFromNetworkID[1].tQTask.tQTaskChildren.ptMiddle) )
      {
        eNetworkID = ClientFromNetworkID->eNetworkID;
        UserIPByNetworkID = Network_GetUserIPByNetworkID(eNetworkID);
        if ( UserIPByNetworkID )
          gcd_authenticate_user(
            eNetworkID,
            UserIPByNetworkID,
            p_ptMiddle,
            (char *)(v4 + 12),
            (void (__cdecl *)(int, int, char *, void *))authfn__,
            nullptr);
      }
    }
  }
}

// source: j/0/network/server.c:679  [size]
void __cdecl Server_GameMessageBombHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // edi
  struct QTask_s *v3; // eax
  struct QTask_s *v4; // esi
  struct Flow_t *v5; // ebp
  unsigned __int16 v6; // dx
  struct QTask_s *v7; // eax
  int ptNext; // eax

  v2 = *((_DWORD *)pxContext + 3);
  v3 = C4Bomb_ptQTask;
  *(_DWORD *)(v2 + 128) = C4Bomb_ptQTask[3].tQTaskChildren.ptHead;
  v4 = nullptr;
  *(float *)(v2 + 132) = (float)ServerConfig_tServerConfig.nSpawnMaxCost;
  *(_DWORD *)(v2 + 140) = v3[3].tQTaskChildren.ptMiddle;
LABEL_2:
  v5 = Flow_ptFlow;
  v6 = Client_eQTaskType;
  while ( 1 )
  {
    v7 = v4 ? QTask_GetNextSiblingOfType(v4, v6) : QTask_GetFirstChildOfType(v5->ptNetManagerQTask, v6);
    v4 = v7;
    if ( !v7 )
      break;
    ptNext = (int)v7[1].ptNext;
    if ( (struct QTask_s *)ptNext != v5->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
    {
      NetManager_SendGameMessage(
        ptNext,
        *(_DWORD *)v2,
        NETWORKQUEUE_GUARANTEED,
        (struct NetManagerGameMessage_s *)(v2 + 8),
        0x88u);
      goto LABEL_2;
    }
  }
}

// source: j/0/network/server.c:733  [anchor-caller]
enum bool __cdecl Server_IsSendHigh(struct Client_s *ptDestination)
{
  DWORD v1; // eax
  DWORD v2; // edx
  enum bool result; // eax

  result = true;
  if ( ptDestination->tReceiveTimeBuffer.aReceiveTime[0] != -1 )
  {
    v1 = Timer_isPerformanceCounter ? Timer_GetPerformanceCounter() : GetTickCount();
    v2 = v1 - Timer_nStartTime;
    if ( (int)(v2 - ptDestination->tReceiveTimeBuffer.aReceiveTime[0]) <= Client_GetHighDelay(ptDestination) )
      return false;
  }
  return result;
}

// source: j/0/network/server.c:742  [layout]
enum bool __cdecl Server_IsSendLow(struct Client_s *ptDestination)
{
  DWORD v1; // eax
  DWORD v2; // edx
  enum bool result; // eax

  result = true;
  if ( ptDestination->tReceiveTimeBuffer.aReceiveTime[1] != -1 )
  {
    v1 = Timer_isPerformanceCounter ? Timer_GetPerformanceCounter() : GetTickCount();
    v2 = v1 - Timer_nStartTime;
    if ( (int)(v2 - ptDestination->tReceiveTimeBuffer.aReceiveTime[1]) <= Client_GetLowDelay(ptDestination) )
      return false;
  }
  return result;
}

// source: j/0/network/server.c:761  [anchor-callee]
void __cdecl Server_GetMinMax(
        struct ClientGameMessageUpdateBatch_s *ptBatch,
        struct int32x3_t *ptMin,
        struct int32x3_t *ptMax)
{
  int v4; // ebx
  struct int32x3_t *v5; // eax
  int v6; // eax
  int nX; // esi
  int nY; // esi
  int nZ; // esi
  int v10; // esi
  int nLocalTime; // esi
  struct ClientGameMessageUpdateBatch_s *ptBatcha = *(struct ClientGameMessageUpdateBatch_s * *)&ptBatch; // [esp+Ch] [ebp+4h] ARGSLOT

  v4 = 0;
  if ( ptBatch->nMessages )
  {
    ptBatcha = (struct ClientGameMessageUpdateBatch_s *)ptBatch->nMessages;
    do
    {
      v5 = (struct int32x3_t *)&ptBatch[2 * v4 + 1];
      if ( v4 )
      {
        nX = ptMin->nX;
        if ( ptMin->nX >= v5->nX )
          nX = v5->nX;
        ptMin->nX = nX;
        nY = ptMin->nY;
        if ( nY >= ptBatch[2 * v4 + 1].tBaseMessage.nLocalTime )
          nY = ptBatch[2 * v4 + 1].tBaseMessage.nLocalTime;
        ptMin->nY = nY;
        nZ = ptMin->nZ;
        if ( nZ >= (int)(*(_DWORD *)&ptBatch[2 * v4 + 1].nMessages) )
          nZ = *(_DWORD *)&ptBatch[2 * v4 + 1].nMessages;
        ptMin->nZ = nZ;
        v10 = ptMax->nX;
        if ( ptMax->nX <= v5->nX )
          v10 = v5->nX;
        ptMax->nX = v10;
        nLocalTime = ptMax->nY;
        if ( nLocalTime <= ptBatch[2 * v4 + 1].tBaseMessage.nLocalTime )
          nLocalTime = ptBatch[2 * v4 + 1].tBaseMessage.nLocalTime;
        ptMax->nY = nLocalTime;
        v6 = *(_DWORD *)&ptBatch[2 * v4 + 1].nMessages;
        if ( ptMax->nZ > v6 )
          v6 = ptMax->nZ;
      }
      else
      {
        *ptMin = *v5;
        ptMax->nX = v5->nX;
        ptMax->nY = ptBatch[1].tBaseMessage.nLocalTime;
        v6 = *(_DWORD *)&ptBatch[1].nMessages;
      }
      ptMax->nZ = v6;
      ++v4;
      ptBatcha = (struct ClientGameMessageUpdateBatch_s *)((char *)ptBatcha - 1);
    }
    while ( ptBatcha );
  }
}

// source: j/0/network/server.c:827  [anchor-callee]
void __cdecl Server_SendOffsetMessage(
        int eDestination,
        struct ClientGameMessageUpdateBatch_s *ptUpdateBatch,
        struct int32x3_t *ptBase,
        int nx,
        int ny,
        int nz)
{
  #pragma pack(push, 1)
  union
  {
    struct { int nMessages; };
    struct { char igi2_o1[8]; unsigned __int8 *v35; };
    struct { char igi2_o2[12]; unsigned int dz; };
    struct { char igi2_o3[20]; unsigned __int8 *tPackMan; };
    struct { char igi2_o4[32]; unsigned __int8 buffer[860]; };
    char igi2_extent[892];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct ClientGameMessageUpdateBatch_s *v6; // edi
  int v7; // esi
  char *p_nMessages; // edi
  unsigned int v9; // ebx
  unsigned int v10; // ebp
  int v11; // eax
  int v12; // edx
  int v13; // esi
  unsigned int *v14; // eax
  int v15; // eax
  int v16; // edx
  int v17; // esi
  unsigned int *v18; // eax
  int v19; // eax
  int v20; // edx
  unsigned int *v21; // eax
  unsigned __int8 v22; // dl
  unsigned __int8 v23; // cl
  unsigned __int8 v24; // dl
  __int16 v25; // cx
  __int16 v26; // dx
  signed __int8 v27; // cl
  unsigned int v28; // edi
  int v29; // edx
  int v30; // ecx
  int v31; // edx
  struct QTask_s *ptNetManagerQTask; // esi
  DWORD PerformanceCounter; // eax

  v6 = ptUpdateBatch;
  v7 = 0;
  igi2_frame.tPackMan = &igi2_frame.buffer[14 * ptUpdateBatch->nMessages + 28];
  if ( !ptUpdateBatch->nMessages )
    goto LABEL_17;
  igi2_frame.v35 = &igi2_frame.buffer[26];
  p_nMessages = &ptUpdateBatch[1].nMessages;
  igi2_frame.nMessages = ptUpdateBatch->nMessages;
  do
  {
    v9 = *((_DWORD *)p_nMessages - 1) - ptBase->nY;
    v10 = *((_DWORD *)p_nMessages - 2) - ptBase->nX;
    igi2_frame.dz = *(_DWORD *)p_nMessages - ptBase->nZ;
    v11 = v7 / 32;
    v12 = v7 % 32;
    v13 = nx + v7;
    v14 = (unsigned int *)&igi2_frame.tPackMan[4 * v11];
    if ( v12 > 0 )
    {
      *v14 |= v10 << v12;
      if ( 32 - v12 >= nx )
        goto LABEL_7;
      ++v14;
      v10 >>= 32 - v12;
    }
    *v14 = v10;
LABEL_7:
    v15 = v13 / 32;
    v16 = v13 % 32;
    v17 = ny + v13;
    v18 = (unsigned int *)&igi2_frame.tPackMan[4 * v15];
    if ( v16 > 0 )
    {
      *v18 |= v9 << v16;
      if ( 32 - v16 >= ny )
        goto LABEL_11;
      ++v18;
      v9 >>= 32 - v16;
    }
    *v18 = v9;
LABEL_11:
    v19 = v17 / 32;
    v20 = v17 % 32;
    v7 = nz + v17;
    v21 = (unsigned int *)&igi2_frame.tPackMan[4 * v19];
    if ( v20 <= 0 )
    {
      *v21 = igi2_frame.dz;
    }
    else
    {
      *v21 |= igi2_frame.dz << v20;
      if ( 32 - v20 < nz )
        v21[1] = igi2_frame.dz >> (32 - v20);
    }
    v22 = p_nMessages[4];
    *(igi2_frame.v35 - 2) = *(p_nMessages - 12);
    v23 = p_nMessages[5];
    *(igi2_frame.v35 - 1) = v22;
    v24 = p_nMessages[6];
    *igi2_frame.v35 = v23;
    v25 = *((_WORD *)p_nMessages + 4);
    igi2_frame.v35[1] = v24;
    v26 = *((_WORD *)p_nMessages + 5);
    *((_WORD *)igi2_frame.v35 + 1) = v25;
    LOBYTE(v25) = p_nMessages[12];
    *((_WORD *)igi2_frame.v35 + 2) = v26;
    LOBYTE(v26) = p_nMessages[13];
    igi2_frame.v35[6] = v25;
    LOBYTE(v25) = p_nMessages[14];
    igi2_frame.v35[7] = v26;
    LOBYTE(v26) = p_nMessages[15];
    igi2_frame.v35[8] = v25;
    LOBYTE(v25) = p_nMessages[16];
    igi2_frame.v35[9] = v26;
    igi2_frame.v35[10] = v25;
    igi2_frame.v35 += 14;
    p_nMessages += 32;
    --igi2_frame.nMessages;
  }
  while ( igi2_frame.nMessages );
  v6 = ptUpdateBatch;
LABEL_17:
  v27 = v6->nMessages;
  v28 = (v7 + 7) / 8 + 14 * (v27 + 2);
  igi2_frame.buffer[10] = ny;
  igi2_frame.buffer[8] = v27;
  igi2_frame.buffer[9] = nx;
  v29 = ptBase->nX;
  igi2_frame.buffer[11] = nz;
  v30 = ptBase->nY;
  *(_DWORD *)&igi2_frame.buffer[12] = v29;
  v31 = ptBase->nZ;
  *(_DWORD *)&igi2_frame.buffer[16] = v30;
  *(_DWORD *)&igi2_frame.buffer[20] = v31;
  *(_DWORD *)igi2_frame.buffer = 1515083088;
  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  *(_DWORD *)&igi2_frame.buffer[4] = PerformanceCounter
                        - Timer_nStartTime
                        + (char *)ptNetManagerQTask[6].tQTaskRefList.ptMiddle
                        - (char *)ptNetManagerQTask[6].tQTaskRefList.ptTail;
  NetManager_SendGameMessage(
    eDestination,
    0,
    NETWORKQUEUE_MEDIUMPRIORITY,
    (struct NetManagerGameMessage_s *)igi2_frame.buffer,
    v28);
}

// source: j/0/network/server.c:935  [anchor-callee]
void __cdecl Server_SendUpdate(struct ClientGameMessageUpdateBatch_s *ptBatch, int eDestination)
{
  char nMessages; // al
  int v4; // esi
  struct Flow_t *v5; // eax
  struct QTask_s *ptNetManagerQTask; // edi
  unsigned int v7; // esi
  DWORD PerformanceCounter; // eax

  nMessages = ptBatch->nMessages;
  if ( nMessages > 0 )
  {
    v4 = nMessages;
    v5 = Flow_ptFlow;
    ptBatch->tBaseMessage.eGameMessage = 1213093200;
    ptNetManagerQTask = v5->ptNetManagerQTask;
    v7 = 32 * v4 + 16;
    if ( Timer_isPerformanceCounter )
      PerformanceCounter = Timer_GetPerformanceCounter();
    else
      PerformanceCounter = GetTickCount();
    ptBatch->tBaseMessage.nLocalTime = PerformanceCounter
                                     - Timer_nStartTime
                                     + (char *)ptNetManagerQTask[6].tQTaskRefList.ptMiddle
                                     - (char *)ptNetManagerQTask[6].tQTaskRefList.ptTail;
    NetManager_SendGameMessage(eDestination, 0, NETWORKQUEUE_MEDIUMPRIORITY, &ptBatch->tBaseMessage, v7);
  }
}

void __cdecl sub_453F30(struct ClientGameMessageUpdateBatch_s *a1, int eDestination)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct int32x3_t ptBase; };
    struct { char igi2_o1[12]; struct int32x3_t ptMax; };
    char igi2_extent[24];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  unsigned int v2; // esi
  int v3; // edi
  unsigned int v4; // edx
  int v5; // eax
  int v6; // ecx

  if ( a1->nMessages <= 1 )
  {
    Server_SendUpdate(a1, eDestination);
  }
  else
  {
    Server_GetMinMax(a1, &igi2_frame.ptBase, &igi2_frame.ptMax);
    v2 = igi2_frame.ptMax.nZ - igi2_frame.ptBase.nZ;
    v3 = 1;
    v4 = igi2_frame.ptMax.nY - igi2_frame.ptBase.nY;
    if ( (unsigned int)(igi2_frame.ptMax.nX - igi2_frame.ptBase.nX) > 1 )
    {
      do
        ++v3;
      while ( (1 << v3) - 1 < (unsigned int)(igi2_frame.ptMax.nX - igi2_frame.ptBase.nX) );
    }
    v5 = 1;
    if ( v4 > 1 )
    {
      do
        ++v5;
      while ( (1 << v5) - 1 < v4 );
    }
    v6 = 1;
    if ( v2 > 1 )
    {
      do
        ++v6;
      while ( (1 << v6) - 1 < v2 );
    }
    Server_SendOffsetMessage(eDestination, a1, &igi2_frame.ptBase, v3, v5, v6);
  }
}

// source: j/0/network/server.c:987  [anchor-caller]
struct Client_s *__cdecl Server_SendToClient(struct Server_s *ptServer, struct Client_s *ptDestination)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v22; };
    struct { char igi2_o1[4]; float ptSource; };
    struct { char igi2_o2[28]; BOOL v24; };
    struct { char igi2_o3[32]; int v25; };
    struct { char igi2_o4[36]; void **v26; };
    struct { char igi2_o5[40]; int v27; };
    struct { char igi2_o6[44]; struct ClientGameMessageUpdateBody_s *ptBody; };
    struct { char igi2_o7[48]; int v29; };
    struct { char igi2_o8[52]; struct QTask_s *ptQTask; };
    struct { char igi2_o9[56]; struct ClientGameMessageUpdateBatch_s a1; };
    struct { char igi2_o10[1096]; struct ClientGameMessageUpdateBatch_s v32; };
    char igi2_extent[2136];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v3; // eax
  void **p_ptBody; // ebx
  DWORD v5; // eax
  DWORD v6; // edx
  DWORD TickCount; // eax
  DWORD v8; // edx
  BOOL v9; // edi
  DWORD PerformanceCounter; // eax
  struct Client_s *result; // eax
  struct Client_s *v12; // eax
  struct Client_s *v13; // edi
  int v14; // eax
  __int16 v15; // cx
  int eNetworkID; // edi
  int ClientPriority; // ebp
  int v18; // ebx
  int v19; // edi
  DWORD v20; // eax
  DWORD v21; // eax

  igi2_frame.ptBody = (struct ClientGameMessageUpdateBody_s *)&igi2_frame.v32.ptBody;
  v3 = ptDestination->tReceiveTimeBuffer.aReceiveTime[0];
  p_ptBody = &igi2_frame.a1.ptBody;
  igi2_frame.ptQTask = nullptr;
  igi2_frame.v26 = &igi2_frame.a1.ptBody;
  igi2_frame.a1.nMessages = 0;
  igi2_frame.v32.nMessages = 0;
  igi2_frame.v24 = true;
  if ( v3 != -1 )
  {
    v5 = Timer_isPerformanceCounter ? Timer_GetPerformanceCounter() : GetTickCount();
    v6 = v5 - Timer_nStartTime;
    if ( (int)(v6 - ptDestination->tReceiveTimeBuffer.aReceiveTime[0]) <= Client_GetHighDelay(ptDestination) )
      igi2_frame.v24 = false;
  }
  if ( ptDestination->tReceiveTimeBuffer.aReceiveTime[1] == -1
    || (!Timer_isPerformanceCounter ? (TickCount = GetTickCount()) : (TickCount = Timer_GetPerformanceCounter()),
        v8 = TickCount - Timer_nStartTime,
        igi2_frame.v25 = 0,
        (int)(v8 - ptDestination->tReceiveTimeBuffer.aReceiveTime[1]) > Client_GetLowDelay(ptDestination)) )
  {
    igi2_frame.v25 = 1;
  }
  v9 = sub_41E250();
  if ( v9 )
  {
    if ( igi2_frame.v24 )
    {
      if ( Timer_isPerformanceCounter )
        PerformanceCounter = Timer_GetPerformanceCounter();
      else
        PerformanceCounter = GetTickCount();
      ptDestination->tReceiveTimeBuffer.aReceiveTime[0] = PerformanceCounter - Timer_nStartTime;
    }
    igi2_frame.v24 = 0;
  }
  else if ( igi2_frame.v24 && igi2_frame.v25 )
  {
    goto LABEL_25;
  }
  igi2_frame.v27 = 0;
  if ( v9 && igi2_frame.v25 )
LABEL_25:
    igi2_frame.v27 = 1;
  if ( igi2_frame.v24 || (result = (struct Client_s *)igi2_frame.v25) != nullptr )
  {
    while ( 1 )
    {
      v12 = (struct Client_s *)(igi2_frame.ptQTask
                              ? QTask_GetNextSiblingOfType(igi2_frame.ptQTask, Client_eQTaskType)
                              : QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, Client_eQTaskType));
      v13 = v12;
      igi2_frame.ptQTask = &v12->tQTask;
      if ( !v12 )
        break;
      if ( v12 != ptDestination )
      {
        v14 = *(_DWORD *)(v12->tReceiveTimeBuffer.nCounter + 8);
        v15 = *(_WORD *)(v14 + 36);
        if ( v15 == HumanRemote_eQTaskType )
        {
          igi2_frame.v29 = *(char *)(v14 + 3268);
        }
        else if ( v15 == HumanPlayer_eQTaskType )
        {
          igi2_frame.v29 = *(char *)(v14 + 3216);
        }
        if ( igi2_frame.v29 )
        {
          if ( igi2_frame.v27 )
          {
            Client_FillGameMessageUpdate(v13, (struct ClientGameMessageUpdateBody_s *)p_ptBody);
            eNetworkID = v13->eNetworkID;
            if ( !ptDestination->anDR[eNetworkID + 5] )
              ptDestination->anDR[eNetworkID + 5] = (struct ClientDR_t *)Mem_AllocFn(120, 4);
            p_ptBody += 8;
            igi2_frame.v26 = p_ptBody;
            ++igi2_frame.a1.nMessages;
          }
          else
          {
            igi2_frame.ptSource = (double)ServerConfig_tServerConfig.nCloseFireRange * 4096.0;
            igi2_frame.v22 = (double)ServerConfig_tServerConfig.nViewPosRange * 4096.0;
            ClientPriority = Client_GetClientPriority(ptDestination, v13, igi2_frame.v22, igi2_frame.ptSource);
            if ( igi2_frame.v24 && ClientPriority == 1 )
            {
              Client_FillGameMessageUpdate(v13, (struct ClientGameMessageUpdateBody_s *)p_ptBody);
              v18 = v13->eNetworkID;
              if ( !ptDestination->anDR[v18 + 5] )
                ptDestination->anDR[v18 + 5] = (struct ClientDR_t *)Mem_AllocFn(120, 4);
              igi2_frame.v26 += 8;
              ++igi2_frame.a1.nMessages;
              p_ptBody = igi2_frame.v26;
            }
            if ( igi2_frame.v25 && !ClientPriority )
            {
              Client_FillGameMessageUpdate(v13, igi2_frame.ptBody);
              v19 = v13->eNetworkID;
              if ( !ptDestination->anDR[v19 + 5] )
                ptDestination->anDR[v19 + 5] = (struct ClientDR_t *)Mem_AllocFn(120, 4);
              ++igi2_frame.ptBody;
              ++igi2_frame.v32.nMessages;
            }
          }
        }
      }
    }
    if ( igi2_frame.v24 )
    {
      sub_453F30(&igi2_frame.a1, ptDestination->eNetworkID);
      if ( Timer_isPerformanceCounter )
        v20 = Timer_GetPerformanceCounter();
      else
        v20 = GetTickCount();
      ptDestination->tReceiveTimeBuffer.aReceiveTime[0] = v20 - Timer_nStartTime;
    }
    result = (struct Client_s *)igi2_frame.v25;
    if ( igi2_frame.v25 )
    {
      result = (struct Client_s *)igi2_frame.v27;
      if ( !igi2_frame.v27 )
      {
        sub_453F30(&igi2_frame.v32, ptDestination->eNetworkID);
        if ( Timer_isPerformanceCounter )
          v21 = Timer_GetPerformanceCounter();
        else
          v21 = GetTickCount();
        result = (struct Client_s *)(v21 - Timer_nStartTime);
        ptDestination->tReceiveTimeBuffer.aReceiveTime[1] = (int)result;
      }
    }
  }
  return result;
}

// source: j/0/network/server.c:1141  [anchor-callee]
void __cdecl Server_SendGameMessageAll(struct Server_s *ptServer)
{
  struct QTask_s *p_tQTask; // esi
  unsigned __int16 v2; // dx
  struct Client_s *v3; // eax

  p_tQTask = nullptr;
  if ( sub_41E250() )
    ++ptServer[1].tQTask.ptNext;
  else
    ++ptServer[1].tQTask.ptPrev;
LABEL_4:
  v2 = Client_eQTaskType;
  while ( 1 )
  {
    v3 = (struct Client_s *)(p_tQTask
                           ? QTask_GetNextSiblingOfType(p_tQTask, v2)
                           : QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, v2));
    p_tQTask = &v3->tQTask;
    if ( !v3 )
      break;
    if ( v3->eNetworkID )
    {
      Server_SendToClient(ptServer, v3);
      goto LABEL_4;
    }
  }
  if ( Timer_isPerformanceCounter )
    ptServer->nLastPosSendRun = Timer_GetPerformanceCounter() - Timer_nStartTime;
  else
    ptServer->nLastPosSendRun = GetTickCount() - Timer_nStartTime;
}

int __cdecl sub_4543F0(int result)
{
  *(_DWORD *)(result + 68) = 0;
  *(_DWORD *)(result + 72) = 0;
  return result;
}

// source: j/0/network/server.c:1176  [anchor-hash]
int __cdecl Server_FreeIfExistsDR(struct Server_s *ptServer, int eNetworkID)
{
  struct QTask_s *v3; // esi
  int result; // eax

  v3 = nullptr;
  while ( 1 )
  {
    result = (int)(v3
                 ? QTask_GetNextSiblingOfType(v3, Client_eQTaskType)
                 : QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, Client_eQTaskType));
    v3 = (struct QTask_s *)result;
    if ( !result )
      break;
    Client_FreeIfExistsDR((struct Client_s *)result, eNetworkID);
  }
  return result;
}

// source: j/0/network/server.c:1202  [size]
void __cdecl Server_ClientGameMessageActivateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct NetManagerGameMessage_s *v2; // edi
  struct QTask_s *v3; // esi
  struct Flow_t *v4; // ebp
  unsigned __int16 v5; // dx
  struct QTask_s *v6; // eax
  int ptNext; // eax

  v2 = *((struct NetManagerGameMessage_s **)pxContext + 3);
  v3 = nullptr;
LABEL_2:
  v4 = Flow_ptFlow;
  v5 = Client_eQTaskType;
  while ( 1 )
  {
    v6 = v3 ? QTask_GetNextSiblingOfType(v3, v5) : QTask_GetFirstChildOfType(v4->ptNetManagerQTask, v5);
    v3 = v6;
    if ( !v6 )
      break;
    ptNext = (int)v6[1].ptNext;
    if ( (struct QTask_s *)ptNext != v4->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
    {
      NetManager_SendGameMessage(ptNext, v2->eGameMessage, NETWORKQUEUE_GUARANTEED, v2 + 1, 0x18u);
      goto LABEL_2;
    }
  }
}

// source: j/0/network/server.c:1247  [anchor-mhash]
void __cdecl Server_ClientGameMessageChatHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v2; // esi
  struct Flow_t *v3; // edi
  unsigned __int16 v4; // dx
  struct QTask_s *v5; // eax
  int ptNext; // eax
  void *pxContexta = *(void * *)&pxContext; // [esp+18h] [ebp+8h] ARGSLOT

  v2 = nullptr;
  pxContexta = *((void **)pxContext + 3);
LABEL_2:
  v3 = Flow_ptFlow;
  v4 = Client_eQTaskType;
  while ( 1 )
  {
    v5 = v2 ? QTask_GetNextSiblingOfType(v2, v4) : QTask_GetFirstChildOfType(v3->ptNetManagerQTask, v4);
    v2 = v5;
    if ( !v5 )
      break;
    ptNext = (int)v5[1].ptNext;
    if ( *(_DWORD *)pxContexta != ptNext && (struct QTask_s *)ptNext != v3->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
    {
      NetManager_SendGameMessage(
        ptNext,
        *(_DWORD *)pxContexta,
        NETWORKQUEUE_GUARANTEED,
        (struct NetManagerGameMessage_s *)pxContexta + 1,
        0x110u);
      goto LABEL_2;
    }
  }
  if ( !NetManager_GetClientFromNetworkID(0) )
    NetManager_LogMessage((char *)pxContexta + 16);
}

// source: j/0/network/server.c:1296  [size]
void __cdecl Server_ClientGameMessageSpawnHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct NetManagerGameMessage_s *v2; // edi
  struct QTask_s *v3; // esi
  struct Flow_t *v4; // ebp
  unsigned __int16 v5; // dx
  struct QTask_s *v6; // eax
  int ptNext; // eax

  v2 = *((struct NetManagerGameMessage_s **)pxContext + 3);
  v3 = nullptr;
LABEL_2:
  v4 = Flow_ptFlow;
  v5 = Client_eQTaskType;
  while ( 1 )
  {
    v6 = v3 ? QTask_GetNextSiblingOfType(v3, v5) : QTask_GetFirstChildOfType(v4->ptNetManagerQTask, v5);
    v3 = v6;
    if ( !v6 )
      break;
    ptNext = (int)v6[1].ptNext;
    if ( (struct QTask_s *)ptNext != v4->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
    {
      NetManager_SendGameMessage(ptNext, v2->eGameMessage, NETWORKQUEUE_GUARANTEED, v2 + 1, 0x10u);
      goto LABEL_2;
    }
  }
}

// source: j/0/network/server.c:1338  [anchor-mhash]
void __cdecl Server_ClientGameMessageSpectateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct NetManagerGameMessage_s *v2; // ebp
  struct QTask_s *v3; // esi
  struct Flow_t *v4; // edi
  unsigned __int16 v5; // dx
  struct QTask_s *v6; // eax
  int ptNext; // eax

  v2 = *((struct NetManagerGameMessage_s **)pxContext + 3);
  v3 = nullptr;
  NetManager_GetClientFromNetworkID(v2[2].eGameMessage)->eNetworkIDSpectate = v2[2].nLocalTime;
LABEL_2:
  v4 = Flow_ptFlow;
  v5 = Client_eQTaskType;
  while ( 1 )
  {
    v6 = v3 ? QTask_GetNextSiblingOfType(v3, v5) : QTask_GetFirstChildOfType(v4->ptNetManagerQTask, v5);
    v3 = v6;
    if ( !v6 )
      break;
    ptNext = (int)v6[1].ptNext;
    if ( (struct QTask_s *)ptNext != v4->ptNetManagerQTask[6].tQTaskChildren.ptMiddle && ptNext != *(_DWORD *)pxContext )
    {
      NetManager_SendGameMessage(ptNext, v2->eGameMessage, NETWORKQUEUE_GUARANTEED, v2 + 1, 0x10u);
      goto LABEL_2;
    }
  }
}

// source: j/0/network/server.c:1385  [anchor-mhash]
void __cdecl Server_ClientGameMessageDamageHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s *v17; };
    struct { char igi2_o1[4]; struct NetManagerGameMessage_s ptGameMessage; };
    struct { char igi2_o2[12]; int v19; };
    struct { char igi2_o3[16]; int v20; };
    struct { char igi2_o4[20]; int v21; };
    struct { char igi2_o5[24]; int v22; };
    struct { char igi2_o6[28]; int v23; };
    struct { char igi2_o7[32]; char v24; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Client_s *ClientFromNetworkID; // eax
  struct Client_s *v4; // edi
  double v5; // st7
  int v6; // esi
  int nLocalTime; // eax
  double v8; // st7
  int Timer; // eax
  int v10; // ecx
  int eNetworkID; // edi
  struct QTask_s *ptNetManagerQTask; // eax
  int ptMiddle; // ecx
  unsigned __int16 v14; // dx
  struct QTask_s *v15; // eax
  int ptNext; // eax
  struct NetManagerGameMessage_s *pxContexta = *(struct NetManagerGameMessage_s * *)&pxContext; // [esp+3Ch] [ebp+8h] ARGSLOT

  pxContexta = *((struct NetManagerGameMessage_s **)pxContext + 3);
  igi2_frame.v17 = nullptr;
  ClientFromNetworkID = NetManager_GetClientFromNetworkID(pxContexta[3].nLocalTime);
  v4 = ClientFromNetworkID;
  if ( NetManager_eMode != NETMANAGER_MODE_WARMUP && *(_DWORD *)pxContext )
  {
    v5 = *(float *)&pxContexta[2].eGameMessage;
    v6 = *(_DWORD *)(ClientFromNetworkID->tReceiveTimeBuffer.nCounter + 8);
    nLocalTime = pxContexta[2].nLocalTime;
    *(_DWORD *)(v6 + 1168) = nLocalTime;
    v8 = v5 * *(float *)(v6 + 8 * nLocalTime + 1036);
    *(float *)(v6 + 8 * nLocalTime + 1032) = v8 + *(float *)(v6 + 8 * nLocalTime + 1032);
    *(float *)(v6 + 1020) = v8 + *(float *)(v6 + 1020);
    Human_UpdateDie((struct Human_s *)v6);
    if ( *(float *)(v6 + 1020) >= (double)*(float *)(v6 + 1024) )
    {
      igi2_frame.ptGameMessage.eGameMessage = 1263094860;
      Timer = NetManager_GetTimer();
      v10 = pxContexta[2].nLocalTime;
      eNetworkID = v4->eNetworkID;
      igi2_frame.ptGameMessage.nLocalTime = Timer;
      ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
      igi2_frame.v21 = v10;
      ptMiddle = (int)ptNetManagerQTask[6].tQTaskChildren.ptMiddle;
      igi2_frame.v24 = 0;
      igi2_frame.v23 = -1;
      igi2_frame.v20 = eNetworkID;
      igi2_frame.v19 = eNetworkID;
      igi2_frame.v22 = 2;
      NetManager_SendGameMessage(0, ptMiddle, NETWORKQUEUE_GUARANTEED, &igi2_frame.ptGameMessage, 0x20u);
    }
LABEL_5:
    v14 = Client_eQTaskType;
    while ( 1 )
    {
      v15 = igi2_frame.v17 ? QTask_GetNextSiblingOfType(igi2_frame.v17, v14) : QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, v14);
      igi2_frame.v17 = v15;
      if ( !v15 )
        break;
      ptNext = (int)v15[1].ptNext;
      if ( ptNext )
      {
        NetManager_SendGameMessage(ptNext, pxContexta->eGameMessage, NETWORKQUEUE_GUARANTEED, pxContexta + 1, 0x48u);
        goto LABEL_5;
      }
    }
  }
}

// source: j/0/network/server.c:1472  [anchor-mhash]
void __cdecl Server_ClientGameMessageKillHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct Client_s *v2; // esi
  struct Client_s *ClientFromNetworkID; // ebx
  int eGameMessage; // edi
  struct Client_s *v5; // eax
  int v6; // edx
  float vBoxLength; // eax
  struct Flow_t *v8; // edi
  struct QTask_s *ptNetManagerQTask; // eax
  unsigned __int16 v10; // dx
  struct QTask_s *v11; // eax
  int ptNext; // eax
  struct QTask_s *v13; // [esp+10h] [ebp-4h]
  struct NetManagerGameMessage_s *pxContexta = *(struct NetManagerGameMessage_s * *)&pxContext; // [esp+1Ch] [ebp+8h] ARGSLOT

  pxContexta = *((struct NetManagerGameMessage_s **)pxContext + 3);
  v2 = nullptr;
  v13 = nullptr;
  ClientFromNetworkID = NetManager_GetClientFromNetworkID(pxContexta[2].nLocalTime);
  if ( NetManager_eMode != NETMANAGER_MODE_WARMUP )
  {
    eGameMessage = pxContexta[2].eGameMessage;
    if ( eGameMessage != -1 )
    {
      v5 = NetManager_GetClientFromNetworkID(eGameMessage);
      v2 = v5;
      if ( v5 )
      {
        if ( v5 != ClientFromNetworkID )
        {
          if ( ClientFromNetworkID->eTeam == v5->eTeam || LOBYTE(pxContexta[4].nLocalTime) )
          {
            v6 = v5->tDownload.nLastLoDown + 1;
            --v5->nPoints;
            v5->tDownload.nLastLoDown = v6;
            LODWORD(v5->tDownload.vBoxLength) = 1;
            Netshop_AddMoneyToClient(pxContexta[2].eGameMessage, ServerConfig_tServerConfig.nMoneyObjectivePlayerWin);
          }
          else
          {
            ++v5->nPoints;
            Netshop_AddMoneyToClient(pxContexta[2].eGameMessage, ServerConfig_tServerConfig.nMoneyTeamKill);
          }
        }
      }
    }
    vBoxLength = ClientFromNetworkID->tDownload.vBoxLength;
    ++*(_DWORD *)&ClientFromNetworkID->isTalk;
    if ( vBoxLength == 0.0 )
      ClientFromNetworkID->tDownload.nLastLoDown = 0;
    NetManager_SetDeathTimer(ClientFromNetworkID);
    if ( ClientFromNetworkID != v2 )
      Netshop_AddMoneyToClient(ClientFromNetworkID->eNetworkID, ServerConfig_tServerConfig.nMoneyCap);
    v8 = Flow_ptFlow;
    ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
    if ( (struct QTask_s *)ClientFromNetworkID->eNetworkID == ptNetManagerQTask[6].tQTaskChildren.ptMiddle && v2 )
    {
      if ( ptNetManagerQTask[5].tQTaskRefList.ptHead == (struct QReference_s *)2
        || ClientFromNetworkID->eTeam == v2->eTeam )
      {
        ptNetManagerQTask[6].tQTaskChildren.ptTail = (struct QTask_s *)v2->eNetworkID;
      }
      else
      {
        ptNetManagerQTask[6].tQTaskChildren.ptTail = (struct QTask_s *)-1;
      }
    }
LABEL_19:
    v10 = Client_eQTaskType;
    while ( 1 )
    {
      v11 = v13 ? QTask_GetNextSiblingOfType(v13, v10) : QTask_GetFirstChildOfType(v8->ptNetManagerQTask, v10);
      v13 = v11;
      if ( !v11 )
        break;
      ptNext = (int)v11[1].ptNext;
      if ( (struct QTask_s *)ptNext != v8->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
      {
        NetManager_SendGameMessage(ptNext, pxContexta->eGameMessage, NETWORKQUEUE_GUARANTEED, pxContexta + 1, 0x20u);
        v8 = Flow_ptFlow;
        goto LABEL_19;
      }
    }
  }
}

// source: j/0/network/server.c:1572  [anchor-mhash]
void __cdecl Server_ClientGameMessageSettingsHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v2; // esi
  struct Flow_t *v3; // edi
  unsigned __int16 v4; // dx
  struct QTask_s *v5; // eax
  int ptNext; // eax
  struct NetManagerGameMessage_s *pxContexta = *(struct NetManagerGameMessage_s * *)&pxContext; // [esp+18h] [ebp+8h] ARGSLOT

  v2 = nullptr;
  pxContexta = *((struct NetManagerGameMessage_s **)pxContext + 3);
LABEL_2:
  v3 = Flow_ptFlow;
  v4 = Client_eQTaskType;
  while ( 1 )
  {
    v5 = v2 ? QTask_GetNextSiblingOfType(v2, v4) : QTask_GetFirstChildOfType(v3->ptNetManagerQTask, v4);
    v2 = v5;
    if ( !v5 )
      break;
    ptNext = (int)v5[1].ptNext;
    if ( pxContexta->eGameMessage != ptNext
      && (struct QTask_s *)ptNext != v3->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
    {
      NetManager_SendGameMessage(ptNext, pxContexta->eGameMessage, NETWORKQUEUE_GUARANTEED, pxContexta + 1, 0x58u);
      goto LABEL_2;
    }
  }
}

// source: j/0/network/server.c:1615  [anchor-caller]
void __cdecl Server_SpamWeaponGameMessageHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // ebp
  struct Client_s *ClientFromNetworkID; // eax
  struct WeaponType_s *v4; // eax
  struct QTask_s *v5; // eax
  struct Client_s *v6; // ebx
  struct WeaponType_s *WeaponTypeFromID; // eax
  enum WeaponCategory_e eWeaponCategory; // ecx
  BOOL v9; // ecx
  enum NetworkQueue_e v10; // eax
  float ptSource; // [esp+8h] [ebp-20h]
  struct Client_s *v12; // [esp+Ch] [ebp-1Ch]
  struct QTask_s *v13; // [esp+10h] [ebp-18h]
  int v14; // [esp+18h] [ebp-10h]
  BOOL v15; // [esp+1Ch] [ebp-Ch]
  float ptDestination; // [esp+20h] [ebp-8h]
  BOOL v17; // [esp+24h] [ebp-4h]

  v2 = *((_DWORD *)pxContext + 3) + 8;
  ptDestination = (double)ServerConfig_tServerConfig.nViewFireRange * 4096.0;
  v13 = nullptr;
  ptSource = (double)ServerConfig_tServerConfig.nSmoothPercent * 4096.0;
  ClientFromNetworkID = NetManager_GetClientFromNetworkID(*(_DWORD *)pxContext);
  v12 = ClientFromNetworkID;
  if ( *(_DWORD *)v2 == 1465075282
    && ClientFromNetworkID
    && (v4 = WeaponType_GetWeaponTypeFromID(*(unsigned __int8 *)(v2 + 20))) != nullptr )
  {
    switch ( v4->eWeaponType )
    {
      case WEAPONTYPE_GUN:
      case WEAPONTYPE_PISTOL:
      case WEAPONTYPE_SHOTGUN:
        ptSource = *((float *)v4->atFireTypes[*(unsigned __int8 *)(v2 + 21)].ptParametersQTaskRef->pxObject + 18)
                 * 4096.0;
        goto LABEL_7;
      case WEAPONTYPE_GRENADE:
        return;
      case WEAPONTYPE_PROXIMITYMINE:
        *(_BYTE *)(v2 + 23) = NetworkGameItem_GetNextGameItemID();
        goto LABEL_7;
      default:
        goto LABEL_7;
    }
  }
  else
  {
LABEL_7:
    while ( 1 )
    {
      v5 = v13
         ? QTask_GetNextSiblingOfType(v13, Client_eQTaskType)
         : QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, Client_eQTaskType);
      v6 = (struct Client_s *)v5;
      v13 = v5;
      if ( !v5 )
        break;
      if ( ((int)v5[5].tQTaskRefList.ptMiddle & 1) == 0 )
      {
        if ( *(_DWORD *)v2 == 1465075282 && v12 )
        {
          WeaponTypeFromID = WeaponType_GetWeaponTypeFromID(*(unsigned __int8 *)(v2 + 20));
          v17 = *(_BYTE *)(v2 + 21) == 1;
          v15 = false;
          if ( v12 == v6 )
          {
            eWeaponCategory = WeaponTypeFromID->eWeaponCategory;
            if ( eWeaponCategory == WEAPONCATEGORY_GRENADE
              || eWeaponCategory == WEAPONCATEGORY_FLASHBANG
              || eWeaponCategory == WEAPONCATEGORY_SMOKEGRENADE
              || eWeaponCategory == WEAPONCATEGORY_PROXIMITYMINE )
            {
              v15 = true;
            }
          }
          if ( WeaponTypeFromID->eWeaponCategory != WEAPONCATEGORY_SIDEARM
            || (v14 = 1, WeaponTypeFromID->anRoundsInSuccession[0] != 1) )
          {
            v14 = 0;
          }
          v9 = v12 != v6
            && (Client_GetClientPriority(v6, v12, ptDestination, ptSource) == 1
             || Client_GetClientPriority(v12, v6, ptDestination, ptSource) == 1);
          if ( v17 || !v14 )
            v10 = NETWORKQUEUE_GUARANTEED;
          else
            v10 = NETWORKQUEUE_MEDIUMPRIORITY;
          if ( v17 || v9 || v15 )
            NetManager_SendGameMessage(
              v6->eNetworkID,
              (int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle,
              v10,
              (struct NetManagerGameMessage_s *)v2,
              *((_DWORD *)pxContext + 2) - 8);
        }
        else
        {
          NetManager_SendGameMessage(
            (int)v5[1].ptNext,
            (int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle,
            NETWORKQUEUE_GUARANTEED,
            (struct NetManagerGameMessage_s *)v2,
            *((_DWORD *)pxContext + 2) - 8);
        }
      }
    }
  }
}

// source: j/0/network/server.c:1726  [anchor-mhash]
void __cdecl Server_SpamGuaranteedServerGameMessageToClientsHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct NetManagerGameMessage_s *v2; // ebx
  struct QTask_s *v3; // edi
  struct Flow_t *v4; // ebp
  unsigned __int16 v5; // dx
  struct QTask_s *v6; // eax

  v2 = (struct NetManagerGameMessage_s *)(*((_DWORD *)pxContext + 3) + 8);
  v3 = nullptr;
LABEL_2:
  v4 = Flow_ptFlow;
  v5 = Client_eQTaskType;
  while ( 1 )
  {
    v6 = v3 ? QTask_GetNextSiblingOfType(v3, v5) : QTask_GetFirstChildOfType(v4->ptNetManagerQTask, v5);
    v3 = v6;
    if ( !v6 )
      break;
    if ( ((int)v6[5].tQTaskRefList.ptMiddle & 1) == 0 )
    {
      NetManager_SendGameMessage(
        (int)v6[1].ptNext,
        (int)v4->ptNetManagerQTask[6].tQTaskChildren.ptMiddle,
        NETWORKQUEUE_GUARANTEED,
        v2,
        *((_DWORD *)pxContext + 2) - 8);
      goto LABEL_2;
    }
  }
}

// source: j/0/network/server.c:1774  [size~]
void __cdecl Server_GameMessageRequestSpawnHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct NetManagerGameMessage_s ptGameMessage; };
    struct { char igi2_o1[8]; int eNetworkID; };
    struct { char igi2_o2[12]; struct QTask_s *ptNext; };
    char igi2_extent[16];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // ebx
  int v3; // edi
  int v4; // ebx
  struct Client_s *ClientFromNetworkID; // eax
  struct Client_s *v6; // esi
  unsigned int v7; // ebx
  struct QReference_s *v8; // ebx
  struct QTask_s *pxObject; // ebx
  int v10; // eax
  struct QTask_s *SpawnPoint; // edi
  int v12; // eax
  int Timer; // eax
  struct QTask_s *ptMiddle; // ecx

  v2 = *((_DWORD *)pxContext + 3);
  v3 = *(_DWORD *)(v2 + 16);
  v4 = v2 + 8;
  ClientFromNetworkID = NetManager_GetClientFromNetworkID(v3);
  v6 = ClientFromNetworkID;
  if ( ClientFromNetworkID )
  {
    v7 = *(_DWORD *)(v4 + 12);
    if ( v7 < 0x1000 && (v8 = Level_atLevelQTaskID[v7]) != nullptr )
      pxObject = (struct QTask_s *)v8->pxObject;
    else
      pxObject = nullptr;
    if ( (struct QTask_s *)ClientFromNetworkID->eTeam == pxObject[6].tQTaskChildren.ptHead )
    {
      if ( Client_CostToSpawn(ClientFromNetworkID) > ClientFromNetworkID->nUpdateItemTime )
      {
        NetManager_LogMessage("Server: Client could not afford spawning\n");
      }
      else
      {
        v10 = Client_CostToSpawn(v6);
        Netshop_AddMoneyToClient(v6->eNetworkID, -v10);
        SpawnPoint = SpawnPoint_GetSpawnPoint(pxObject, 0);
        v12 = SpawnPoint_nUse;
        *(_DWORD *)&SpawnPoint[1].eQTaskType = SpawnPoint_nUse;
        SpawnPoint_nUse = v12 + 1;
        igi2_frame.ptGameMessage.eGameMessage = 1397774158;
        Timer = NetManager_GetTimer();
        igi2_frame.eNetworkID = v6->eNetworkID;
        ptMiddle = Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle;
        igi2_frame.ptGameMessage.nLocalTime = Timer;
        igi2_frame.ptNext = SpawnPoint[1].ptNext;
        NetManager_SendGameMessage(0, (int)ptMiddle, NETWORKQUEUE_GUARANTEED, &igi2_frame.ptGameMessage, 0x10u);
      }
    }
    else
    {
      NetManager_LogMessage("Server: Client tried to spawn in opponents spawn area. BUG or CHEAT\n");
    }
  }
  else
  {
    NetManager_LogMessage("Server_GameMessageRequestSpawnHandler: No client found at input networkID\n");
  }
}

// source: j/0/network/server.c:1862  [anchor-caller]
void __cdecl Server_GameMessageRequestPickupHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct Client_s *ptClient; };
    struct { char igi2_o1[4]; struct Client_s *ptCurrentClient; };
    struct { char igi2_o2[8]; struct ClientGameMessagePickup_s *ptClientGameMessagePickup; };
    struct { char igi2_o3[12]; struct WeaponType_s *ptAddWeaponType; };
    struct { char igi2_o4[16]; struct real64x3_t tPos; };
    struct { char igi2_o5[40]; struct PickupContext_t tPickupContext; };
    char igi2_extent[80];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct NetManagerGameMessage_s *v2; // ebx
  struct Client_s *ClientFromNetworkID; // eax
  struct QTask_s *QTaskFromID; // eax
  struct QTask_s *v5; // esi
  struct QTask_s *v6; // ebx
  struct WeaponType_s *NextEnabledWeaponTypeFromCategory; // edi
  unsigned __int16 v8; // dx
  struct QTask_s *v9; // eax
  int ptNext; // eax

  v2 = (struct NetManagerGameMessage_s *)(*((_DWORD *)pxContext + 3) + 8);
  igi2_frame.ptClientGameMessagePickup = (struct ClientGameMessagePickup_s *)v2;
  igi2_frame.ptCurrentClient = nullptr;
  ClientFromNetworkID = NetManager_GetClientFromNetworkID(*(_DWORD *)pxContext);
  igi2_frame.ptClient = ClientFromNetworkID;
  if ( ClientFromNetworkID )
  {
    qmemcpy(
      &igi2_frame.tPos,
      (void *)(*(_DWORD *)(*(_DWORD *)(ClientFromNetworkID->tReceiveTimeBuffer.nCounter + 8) + 1336) + 408),
      sizeof(igi2_frame.tPos));
    QTaskFromID = NetworkGameItem_GetQTaskFromID(v2[1].eGameMessage);
    v5 = QTaskFromID;
    if ( QTaskFromID && GunPickup_IsAbleToPickup(QTaskFromID, &igi2_frame.tPos, 20480.0, igi2_frame.ptClient->eTeam) )
    {
      v6 = *(struct QTask_s **)(igi2_frame.ptClient->tReceiveTimeBuffer.nCounter + 8);
      igi2_frame.ptAddWeaponType = WeaponType_GetWeaponTypeFromID((int)v5[10].tQTaskChildren.ptTail);
      NextEnabledWeaponTypeFromCategory = Weapon_GetNextEnabledWeaponTypeFromCategory(
                                            v6[33].ptNext,
                                            igi2_frame.ptAddWeaponType->eWeaponCategory,
                                            nullptr);
      igi2_frame.tPickupContext.ptQTask = v6;
      GunPickup_Pickup(v5, &igi2_frame.tPickupContext);
      if ( v6 == HumanPlayer_ptQTask )
        HumanPlayer_ptQTask[80].tQTaskRefList.ptTail = (struct QReference_s *)2;
      igi2_frame.ptClientGameMessagePickup->tBaseMessage.eGameMessage = 1346978635;
LABEL_7:
      v8 = Client_eQTaskType;
      while ( 1 )
      {
        v9 = igi2_frame.ptCurrentClient
           ? QTask_GetNextSiblingOfType(&igi2_frame.ptCurrentClient->tQTask, v8)
           : QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, v8);
        igi2_frame.ptCurrentClient = (struct Client_s *)v9;
        if ( !v9 )
          break;
        ptNext = (int)v9[1].ptNext;
        if ( ptNext )
        {
          NetManager_SendGameMessage(
            ptNext,
            0,
            NETWORKQUEUE_GUARANTEED,
            &igi2_frame.ptClientGameMessagePickup->tBaseMessage,
            0x14u);
          goto LABEL_7;
        }
      }
      if ( NextEnabledWeaponTypeFromCategory )
      {
        if ( NextEnabledWeaponTypeFromCategory != igi2_frame.ptAddWeaponType )
          NetManager_DropWeapon(igi2_frame.ptClient->eNetworkID, NextEnabledWeaponTypeFromCategory->eID);
      }
    }
    else
    {
      v2->eGameMessage = 1346978635;
      v2[1].nLocalTime = -1;
      NetManager_SendGameMessage(igi2_frame.ptClient->eNetworkID, 0, NETWORKQUEUE_GUARANTEED, v2, 0x14u);
    }
  }
}

// source: j/0/network/server.c:1979  [anchor-caller]
void __cdecl Server_GameMessageRequestDropHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // esi

  v2 = *((_DWORD *)pxContext + 3) + 8;
  if ( NetManager_GetClientFromNetworkID(*(_DWORD *)pxContext) )
    NetManager_DropWeapon(*(_DWORD *)(v2 + 68), *(_DWORD *)(v2 + 48));
}

// source: j/0/network/server.c:2024  [anchor-mhash]
struct QTask_s *__cdecl Server_SendAreaActivateMessage(
        struct QTask_s *ptActivateQTask,
        int nActive,
        int nClientID)
{
  struct QTask_s *ptNetManagerQTask; // esi
  struct QTask_s *v5; // edi
  DWORD PerformanceCounter; // eax
  int v7; // eax
  struct QReference_s *v8; // ecx
  unsigned __int16 v9; // dx
  struct QTask_s *result; // eax
  struct QTask_s *ptNext; // eax
  struct ClientGameMessageActivate_s tActivateMessage; // [esp+Ch] [ebp-18h] BYREF

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  v5 = nullptr;
  tActivateMessage.tBaseMessage.eGameMessage = 1094931529;
  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  tActivateMessage.tBaseMessage.nLocalTime = PerformanceCounter
                                           - Timer_nStartTime
                                           + (char *)ptNetManagerQTask[6].tQTaskRefList.ptMiddle
                                           - (char *)ptNetManagerQTask[6].tQTaskRefList.ptTail;
  tActivateMessage.eActivate = 14;
  v7 = 0;
  while ( 1 )
  {
    v8 = Level_atLevelQTaskID[v7];
    if ( v8 )
    {
      if ( v8->pxObject == ptActivateQTask )
        break;
    }
    if ( ++v7 >= 4096 )
    {
      v7 = -1;
      break;
    }
  }
  tActivateMessage.nTaskID = v7;
  tActivateMessage.nWhoDidItClientID = nClientID;
  tActivateMessage.nActivateInfo = nActive;
LABEL_10:
  v9 = Client_eQTaskType;
  while ( 1 )
  {
    result = v5 ? QTask_GetNextSiblingOfType(v5, v9) : QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, v9);
    v5 = result;
    if ( !result )
      return result;
    ptNext = result[1].ptNext;
    if ( ptNext )
    {
      NetManager_SendGameMessage((int)ptNext, 0, NETWORKQUEUE_GUARANTEED, &tActivateMessage.tBaseMessage, 0x18u);
      goto LABEL_10;
    }
  }
}

// source: j/0/network/server.c:2059  [size]
struct QTask_s *__cdecl Server_New(
        struct QTask_s *ptParentQTask,
        struct ServerCreateContext_s *ptCreateContext)
{
  return QTask_NewFn(ptParentQTask, Server_eQTaskType, ptCreateContext);
}

// source: j/0/network/server.c:2076  [size]
unsigned __int16 __cdecl Server_GetQTaskType()
{
  return Server_eQTaskType;
}

// source: j/0/network/server.c:2093  [anchor-callee]
void __cdecl Server_DestroyPlayer(struct Client_s *ptClient, enum NetManagerDestroyPlayerReason_e eReason)
{
  struct QTask_s *ptNetManagerQTask; // esi
  DWORD PerformanceCounter; // eax
  int v4; // ecx
  int eNetworkID; // eax
  struct NetManagerGameMessageDestroyPlayer_s tDestroyGameMessage; // [esp+8h] [ebp-10h] BYREF

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  tDestroyGameMessage.tBaseMessage.eGameMessage = 1145393228;
  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  v4 = PerformanceCounter
     - Timer_nStartTime
     + (char *)ptNetManagerQTask[6].tQTaskRefList.ptMiddle
     - (char *)ptNetManagerQTask[6].tQTaskRefList.ptTail;
  eNetworkID = ptClient->eNetworkID;
  tDestroyGameMessage.tBaseMessage.nLocalTime = v4;
  tDestroyGameMessage.eDestroyReason = eReason;
  tDestroyGameMessage.eClientNetworkID = eNetworkID;
  NetManager_SendGameMessage(0, 0, NETWORKQUEUE_GUARANTEED, &tDestroyGameMessage.tBaseMessage, 0x10u);
}

// source: j/0/network/server.c:2132  [anchor-strings]
enum bool __cdecl Server_IsConnectionActive(struct Client_s *ptClient)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zTime[8]; };
    struct { char igi2_o1[8]; char zIDName[52]; };
    struct { char igi2_o2[60]; char zTemp[256]; };
    char igi2_extent[316];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptNetManagerQTask; // ebx
  DWORD PerformanceCounter; // eax
  int v4; // ecx
  struct QReference_s *ptTail; // eax

  if ( !ptClient->eNetworkID )
    return true;
  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  v4 = 1000 * ServerConfig_tServerConfig.nAutoKick;
  if ( (int)(PerformanceCounter - Timer_nStartTime - ptClient->nLastPacketReceived) <= 1000
                                                                                     * ServerConfig_tServerConfig.nAutoKick
    || (int)(PerformanceCounter - Timer_nStartTime - (unsigned int)ptNetManagerQTask[29].tQTaskChildren.ptHead) >= v4 / 2 )
  {
    return true;
  }
  _snprintf(igi2_frame.zTime, 5u, (char *const)&g_ptNetManager.tReceiveCounters.tCounters[9].nBytes, v4 / 1000);
  _snprintf(igi2_frame.zIDName, 0x32u, "[%d][%s]", ptClient->eNetworkID, ptClient->zPlayerName);
  Config_SetLocalizedPhrase(igi2_frame.zTemp, "mp/NO_INCOMING_DATA_ONSERVER", igi2_frame.zIDName, igi2_frame.zTime, nullptr);
  if ( StatusScreen_ptStatusScreenQTask )
  {
    ptTail = StatusScreen_ptStatusScreenQTask[52].tQTaskRefList.ptTail;
    if ( ptTail )
      TextScroller_Add((struct TextScroller_s *)ptTail, igi2_frame.zTemp, TEXTSCROLLER_COLOUR_RED);
  }
  NetManager_LogMessage(igi2_frame.zTemp);
  NetManager_LogMessage("\r\n");
  return false;
}

// source: j/0/network/server.c:2199  [anchor-caller]
enum bool __cdecl Server_RunDisconnectCheck()
{
  struct QTask_s *ptNetManagerQTask; // edi
  struct QTask_s *p_tQTask; // esi
  DWORD v2; // eax
  struct Client_s *v3; // eax
  struct Client_s *v4; // edi

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  p_tQTask = nullptr;
  if ( ptNetManagerQTask[8].tQTaskRefList.ptMiddle )
  {
    v2 = Timer_isPerformanceCounter ? Timer_GetPerformanceCounter() : GetTickCount();
    if ( (int)(v2 - Timer_nStartTime - (unsigned int)ptNetManagerQTask[9].tQTaskRefList.ptMiddle) > 3000 )
    {
      while ( 1 )
      {
        v3 = (struct Client_s *)(p_tQTask
                               ? QTask_GetNextSiblingOfType(p_tQTask, Client_eQTaskType)
                               : QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, Client_eQTaskType));
        v4 = v3;
        p_tQTask = &v3->tQTask;
        if ( !v3 )
          break;
        if ( Server_IsConnectionActive(v3) == false )
        {
          Server_DestroyPlayer(v4, NETMANAGER_DESTROYPLAYER_REASON_LOST);
          return true;
        }
      }
    }
  }
  return false;
}

// source: j/0/network/server.c:2247  [anchor-strings]
enum bool __cdecl Server_IsConnectionGood(struct Client_s *ptClient, char *zDesc, int nDesc)
{
  #pragma pack(push, 1)
  union
  {
    struct { int nPlossMax; };
    struct { char igi2_o1[4]; int nIdleMax; };
    struct { char igi2_o2[8]; int nGoutMax; };
    struct { char igi2_o3[12]; __int64 v17; };
    struct { char igi2_o4[20]; int nPingMax; };
    struct { char igi2_o5[24]; char Buffer[256]; };
    char igi2_extent[280];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int nReceivedPacks; // eax
  float vPacketLoss; // ebp
  DWORD PerformanceCounter; // eax
  DWORD v8; // esi
  int LastReceivedTimeFromNetworkID; // eax
  struct Node_s *ptHead; // ecx
  int v11; // esi
  struct Node_s *ptNext; // eax
  int i; // ebx

  *zDesc = 0;
  if ( !ptClient->eNetworkID )
  {
    strncat(zDesc, "SERVER_ALWAYS_OK", 0xFFu);
    return true;
  }
  igi2_frame.nPingMax = ServerConfig_tServerConfig.nPingMax;
  igi2_frame.nGoutMax = ServerConfig_tServerConfig.nGoutMax;
  nReceivedPacks = ptClient->tStats.nReceivedPacks;
  igi2_frame.nPlossMax = ServerConfig_tServerConfig.nPlossMax;
  igi2_frame.nIdleMax = ServerConfig_tServerConfig.nIdleMax;
  if ( nReceivedPacks == 3000 || nReceivedPacks == -1 || !nReceivedPacks )
    vPacketLoss = IGI2_FLOAT_BITS(0xffffffffu);
  else
    vPacketLoss = ptClient->tStats.vPacketLoss;
  igi2_frame.v17 = (__int64)(*(float *)&ptClient->tStats.nLostPacks * 10.0 + 0.5);
  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  v8 = PerformanceCounter - Timer_nStartTime;
  LastReceivedTimeFromNetworkID = NetManager_GetLastReceivedTimeFromNetworkID(ptClient->eNetworkID);
  ptHead = Network_atQueues[0].tList.ptHead;
  v11 = v8 - LastReceivedTimeFromNetworkID;
  ptNext = Network_atQueues[0].tList.ptHead->ptNext;
  for ( i = 0; ptNext; ptNext = ptNext->ptNext )
  {
    if ( ptHead[1].ptNext == (struct Node_s *)ptClient->eNetworkID )
      ++i;
    ptHead = ptNext;
  }
  if ( SLODWORD(vPacketLoss) <= igi2_frame.nPingMax && (int)igi2_frame.v17 <= igi2_frame.nPlossMax && v11 <= igi2_frame.nIdleMax && i <= igi2_frame.nGoutMax )
  {
    strncat(zDesc, "OK", 0xFFu);
    return true;
  }
  _snprintf(igi2_frame.Buffer, 0xFFu, "Server_IsConnectionGood: Connection not good[%d]:\n", ptClient->eNetworkID);
  NetManager_LogMessage(igi2_frame.Buffer);
  _snprintf(igi2_frame.Buffer, 0xFFu, "  IDLE : now %dms max %dms\n", v11, igi2_frame.nIdleMax);
  NetManager_LogMessage(igi2_frame.Buffer);
  _snprintf(igi2_frame.Buffer, 0xFFu, "  PING : now %dms max %dms\n", vPacketLoss, igi2_frame.nPingMax);
  NetManager_LogMessage(igi2_frame.Buffer);
  _snprintf(igi2_frame.Buffer, 0xFFu, "  PLOSS: now %d pr1000 max %d pr1000\n", (_DWORD)igi2_frame.v17, igi2_frame.nPlossMax);
  NetManager_LogMessage(igi2_frame.Buffer);
  _snprintf(igi2_frame.Buffer, 0xFFu, "  GOUT : now %d max %d\n", i, igi2_frame.nGoutMax);
  NetManager_LogMessage(igi2_frame.Buffer);
  if ( SLODWORD(vPacketLoss) > igi2_frame.nPingMax )
  {
    _snprintf(zDesc, 0xFFu, "PING: %dms>%dms", vPacketLoss, igi2_frame.nPingMax);
    return false;
  }
  if ( (int)igi2_frame.v17 <= igi2_frame.nPlossMax )
  {
    if ( v11 > igi2_frame.nIdleMax )
    {
      _snprintf(zDesc, 0xFFu, "IDLE: %dms > %dms", v11, igi2_frame.nIdleMax);
      return false;
    }
    if ( i > igi2_frame.nGoutMax )
    {
      _snprintf(zDesc, 0xFFu, "QUEUE: %d > %d", i, igi2_frame.nGoutMax);
      return false;
    }
    strncat(zDesc, "?BAD CONNECTION- UNKNOWN REASON", 0xFFu);
    return false;
  }
  else
  {
    _snprintf(zDesc, 0xFFu, "PLOSS: %.1f%% > %.1f%%", (double)(int)igi2_frame.v17 * 0.10000000149011612, (double)igi2_frame.nPlossMax * 0.10000000149011612);
    return false;
  }
}

// source: j/0/network/server.c:2352  [anchor-strings]
enum bool __cdecl Server_RunBadConnectCheck(struct Server_s *ptServer)
{
  #pragma pack(push, 1)
  union
  {
    struct { char Source[256]; };
    struct { char igi2_o1[256]; char Destination[256]; };
    struct { char igi2_o2[512]; char Buffer[256]; };
    char igi2_extent[768];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptNetManagerQTask; // ebx
  struct QTask_s *v2; // ebp
  int v3; // esi
  DWORD PerformanceCounter; // eax
  struct QTask_s *v5; // eax
  struct QTask_s *v6; // edi
  DWORD v7; // eax

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  v2 = nullptr;
  v3 = 2 * (ptServer->nDisconnectCheckInterval + 500 * ServerConfig_tServerConfig.nAutoKick);
  if ( !ptNetManagerQTask[8].tQTaskRefList.ptMiddle )
    goto LABEL_25;
  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  if ( (int)(PerformanceCounter - Timer_nStartTime - (unsigned int)ptNetManagerQTask[9].tQTaskRefList.ptMiddle) > v3 )
  {
    while ( 1 )
    {
      v5 = v2
         ? QTask_GetNextSiblingOfType(v2, Client_eQTaskType)
         : QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, Client_eQTaskType);
      v6 = v5;
      v2 = v5;
      if ( !v5 )
        break;
      if ( v5[1].ptNext )
      {
        v7 = Timer_isPerformanceCounter ? Timer_GetPerformanceCounter() : GetTickCount();
        if ( (int)(v7 - Timer_nStartTime - (unsigned int)v6[1].tQTaskChildren.ptTail) >= v3 )
        {
          if ( Server_IsConnectionGood((struct Client_s *)v6, igi2_frame.Destination, 255) )
          {
            v6[15].tQTaskChildren.ptMiddle = nullptr;
          }
          else
          {
            ++*(int *)&v6[15].tQTaskChildren.ptMiddle;
            Config_SetLocalizedPhrase(igi2_frame.Source, "mp/SERVER_WARNING", igi2_frame.Destination, nullptr, nullptr);
            NetManager_ServerMessageToClient((struct Client_s *)v6, igi2_frame.Source);
            if ( (int)v6[15].tQTaskChildren.ptMiddle > 1 )
            {
              Server_DestroyPlayer((struct Client_s *)v6, NETMANAGER_DESTROYPLAYER_REASON_LOST);
              return true;
            }
            _snprintf(igi2_frame.Buffer, 0xFFu, "Server reducing bandwidth for [%d]\n", v6[1].ptNext);
            NetManager_LogMessage(igi2_frame.Buffer);
            NetManager_ReduceClientBandwidth(
              (struct NetManager_s *)ptNetManagerQTask,
              (struct Client_s *)v6,
              0.800000011920929,
              200,
              500);
          }
        }
      }
    }
    return false;
  }
  if ( !ptNetManagerQTask[8].tQTaskRefList.ptMiddle )
  {
LABEL_25:
    NetManager_LogMessage("Server_RunBadConnectCheck: No strict regime: Game not started\n");
    return false;
  }
  if ( Timer_isPerformanceCounter )
    Timer_GetPerformanceCounter();
  else
    GetTickCount();
  return false;
}

// source: j/0/network/server.c:2477  [anchor-caller]
void __cdecl Server_RunHandler(struct QTask_s *ptQTask)
{
  DWORD PerformanceCounter; // eax
  DWORD TickCount; // eax
  DWORD v3; // eax

  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  if ( (signed int)(PerformanceCounter - Timer_nStartTime - (unsigned int)ptQTask[1].tQTaskRefList.ptMiddle) > (int)ptQTask[1].tQTaskRefList.ptHead )
  {
    NetManager_CountMapVotes();
    NetManager_CountKickVotes();
    if ( Timer_isPerformanceCounter )
      TickCount = Timer_GetPerformanceCounter();
    else
      TickCount = GetTickCount();
    ptQTask[1].tQTaskRefList.ptMiddle = (struct QReference_s *)(TickCount - Timer_nStartTime);
  }
  if ( Timer_isPerformanceCounter )
    v3 = Timer_GetPerformanceCounter();
  else
    v3 = GetTickCount();
  if ( (signed int)(v3 - Timer_nStartTime - (unsigned int)ptQTask[1].tQTaskChildren.ptTail) > (int)ptQTask[1].tQTaskChildren.ptMiddle )
  {
    if ( Server_RunDisconnectCheck() == false )
      Server_RunBadConnectCheck((struct Server_s *)ptQTask);
    while ( Network_RemoveOneLoadingTimedOut((__int64)((double)ServerConfig_tServerConfig.nAutoKick * 1500.0 + 0.5)) )
      ;
    if ( Timer_isPerformanceCounter )
      ptQTask[1].tQTaskChildren.ptTail = (struct QTask_s *)(Timer_GetPerformanceCounter() - Timer_nStartTime);
    else
      ptQTask[1].tQTaskChildren.ptTail = (struct QTask_s *)(GetTickCount() - Timer_nStartTime);
  }
}

// source: j/0/network/server.c:2533  [anchor-hash]
void __cdecl Server_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si
  DWORD PerformanceCounter; // eax
  DWORD v3; // eax

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("NetworkServer", 76, BaseQTaskType, 0, 0);
  Server_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 0, sub_453540);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, Server_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, pfQTaskEventNoContext__);
  QTask_LinkQTaskEventHandlerFn(v1, NetManager_eGameMessagePingQTaskEvent, Server_GameMessagePingHandler);
  QTask_LinkQTaskEventHandlerFn(v1, NetManager_eGameMessagePongQTaskEvent, Server_GameMessagePongHandler);
  QTask_LinkQTaskEventHandlerFn(v1, NetManager_eGameMessageObjectiveQTaskEvent, Server_GameMessageObjectiveHandler);
  QTask_LinkQTaskEventHandlerFn(v1, NetManager_eGameMessageBombQTaskEvent, Server_GameMessageBombHandler);
  QTask_LinkQTaskEventHandlerFn(v1, NetManager_eGameMessageSpawnQTaskEvent, Server_ClientGameMessageSpawnHandler);
  QTask_LinkQTaskEventHandlerFn(v1, NetManager_eGameMessageSpectateQTaskEvent, Server_ClientGameMessageSpectateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    NetManager_eGameMessageRequestSpawnQTaskEvent,
    Server_GameMessageRequestSpawnHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    NetManager_eGameMessageRequestPickupQTaskEvent,
    Server_GameMessageRequestPickupHandler);
  QTask_LinkQTaskEventHandlerFn(v1, NetManager_eGameMessageRequestDropQTaskEvent, Server_GameMessageRequestDropHandler);
  QTask_LinkQTaskEventHandlerFn(v1, NetManager_eGameMessageActivateQTaskEvent, Server_ClientGameMessageActivateHandler);
  QTask_LinkQTaskEventHandlerFn(v1, NetManager_eGameMessageChatQTaskEvent, Server_ClientGameMessageChatHandler);
  QTask_LinkQTaskEventHandlerFn(v1, NetManager_eGameMessageDamageQTaskEvent, Server_ClientGameMessageDamageHandler);
  QTask_LinkQTaskEventHandlerFn(v1, NetManager_eGameMessageKillQTaskEvent, Server_ClientGameMessageKillHandler);
  QTask_LinkQTaskEventHandlerFn(v1, NetManager_eGameMessageSettingsQTaskEvent, Server_ClientGameMessageSettingsHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    NetManager_eGameMessageAuthenticateQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))sub_453970);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    NetworkGameItem_eGameMessageGameItemQTaskEvent,
    Server_SpamGuaranteedServerGameMessageToClientsHandler);
  QTask_LinkQTaskEventHandlerFn(v1, Weapon_eFireQTaskEvent, Server_SpamWeaponGameMessageHandler);
  QTask_LinkQTaskEventHandlerFn(v1, Weapon_eReleaseQTaskEvent, Server_SpamWeaponGameMessageHandler);
  QTask_LinkQTaskEventHandlerFn(v1, Weapon_eReloadQTaskEvent, Server_SpamWeaponGameMessageHandler);
  QTask_LinkQTaskEventHandlerFn(v1, Weapon_eZoomQTaskEvent, Server_SpamWeaponGameMessageHandler);
  QTask_LinkQTaskEventHandlerFn(v1, Weapon_eActivateQTaskEvent, Server_SpamWeaponGameMessageHandler);
  Server_tRandomState.anRandom[0] = -923067897;
  Server_tRandomState.anRandom[1] = 971667286;
  Server_tRandomState.anRandom[2] = 2146516173;
  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  v3 = PerformanceCounter - Timer_nStartTime;
  Server_tRandomState.anRandom[0] = v3 ^ 0xC8FB1A07;
  Server_tRandomState.anRandom[1] = (v3 << 15) + 971667286;
  Server_tRandomState.anRandom[2] = 2146516173 - (v3 << 9);
}

// source: j/0/network/server.c:2585  [size]
void __cdecl Server_Close()
{
  QTask_DeleteQTaskType(Server_eQTaskType);
}

// source: j/0/network/server.c:2601  [size]
enum bool __cdecl Server_IsSupported()
{
  return true;
}
