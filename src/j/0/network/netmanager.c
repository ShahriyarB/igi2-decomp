/* j/0/network/netmanager.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/network/netmanager.c:444  [anchor-strings]
void __cdecl NetManager_LogClients()
{
  #pragma pack(push, 1)
  union
  {
    struct { int v28; };
    struct { char igi2_o1[4]; int v29; };
    struct { char igi2_o2[8]; float v30; };
    struct { char igi2_o3[12]; struct QReference_s *ptMiddle; };
    struct { char igi2_o4[16]; int v32; };
    struct { char igi2_o5[20]; struct QTask_s *v33; };
    struct { char igi2_o6[28]; DWORD v34; };
    struct { char igi2_o7[32]; int v35; };
    struct { char igi2_o8[36]; char zString[24]; };
    struct { char igi2_o9[60]; char Buffer[256]; };
    struct { char igi2_o10[316]; char v38[104]; };
    char igi2_extent[420];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  unsigned __int16 v0; // dx
  struct Flow_t *v1; // edi
  struct QTask_s *ptNetManagerQTask; // ebx
  struct QTask_s *v3; // eax
  int i; // esi
  struct QTask_s *v5; // ebp
  struct QTask_s *NextSiblingOfType; // eax
  int ptNext; // edi
  int LastReceivedTimeFromNetworkID; // esi
  DWORD PerformanceCounter; // eax
  struct Node_s *ptHead; // ecx
  struct Node_s *v11; // eax
  int v12; // edx
  DWORD v13; // eax
  int v14; // edx
  struct QTask_s *v15; // eax
  struct QTask_s *v16; // esi
  unsigned __int16 eQTaskType; // ax
  _DWORD *p_ptTail; // esi
  char v19; // bl
  int v20; // ecx
  int v21; // eax
  struct Node_s *v22; // eax
  struct Node_s *v23; // ecx
  int v24; // edi
  struct Node_s *v25; // edx
  int v26; // edx
  struct Node_s *j; // ecx

  v0 = Client_eQTaskType;
  v1 = Flow_ptFlow;
  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  v3 = nullptr;
  igi2_frame.v33 = ptNetManagerQTask;
  for ( i = 0; ; ++i )
  {
    v3 = v3 ? QTask_GetNextSiblingOfType(v3, v0) : QTask_GetFirstChildOfType(ptNetManagerQTask, v0);
    if ( !v3 )
      break;
  }
  if ( i >= 1 )
  {
    NetManager_LogMessage((char *)&stru_6A4CDC);
    NetManager_LogMessage("--Players\n");
    v5 = nullptr;
    while ( 1 )
    {
      v1 = Flow_ptFlow;
      if ( v5 )
        NextSiblingOfType = QTask_GetNextSiblingOfType(v5, Client_eQTaskType);
      else
        NextSiblingOfType = QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, Client_eQTaskType);
      v5 = NextSiblingOfType;
      if ( !NextSiblingOfType )
      {
        ptNetManagerQTask = igi2_frame.v33;
        goto LABEL_40;
      }
      ptNext = (int)NextSiblingOfType[1].ptNext;
      igi2_frame.ptMiddle = NextSiblingOfType[6].tQTaskRefList.ptMiddle;
      igi2_frame.v30 = *(float *)&NextSiblingOfType[7].ptNext;
      LastReceivedTimeFromNetworkID = NetManager_GetLastReceivedTimeFromNetworkID(ptNext);
      if ( Timer_isPerformanceCounter )
        PerformanceCounter = Timer_GetPerformanceCounter();
      else
        PerformanceCounter = GetTickCount();
      ptHead = Network_atQueues[0].tList.ptHead;
      igi2_frame.v34 = PerformanceCounter - Timer_nStartTime - LastReceivedTimeFromNetworkID;
      v11 = Network_atQueues[0].tList.ptHead->ptNext;
      v12 = 0;
      igi2_frame.v28 = 0;
      if ( Network_atQueues[0].tList.ptHead->ptNext )
      {
        do
        {
          if ( ptHead[1].ptNext == (struct Node_s *)v5[1].ptNext )
            ++v12;
          ptHead = v11;
          v11 = v11->ptNext;
        }
        while ( v11 );
        igi2_frame.v28 = v12;
      }
      igi2_frame.v32 = Network_NumberOfWaitingFromHost((int)v5[1].ptNext);
      v13 = Timer_isPerformanceCounter ? Timer_GetPerformanceCounter() : GetTickCount();
      v14 = (unsigned __int64)(1172812403LL * (int)(v13 - Timer_nStartTime - (unsigned int)v5[1].tQTaskChildren.ptTail)) >> 32;
      v15 = v5[16].tQTaskChildren.ptHead;
      igi2_frame.v29 = ((unsigned int)v14 >> 31) + (v14 >> 14);
      igi2_frame.v35 = *(_DWORD *)&v5[7].eQTaskType;
      if ( !v15 )
        break;
      v16 = v15->tQTaskChildren.ptHead;
      eQTaskType = v16->eQTaskType;
      if ( eQTaskType == HumanRemote_eQTaskType )
      {
        p_ptTail = &v16[82].tQTaskChildren.ptTail;
      }
      else
      {
        if ( eQTaskType != HumanPlayer_eQTaskType )
          break;
        p_ptTail = &v16[87].eQTaskType;
      }
LABEL_30:
      v19 = v5[1].tQTaskChildren.ptHead == nullptr ? 32 : 42;
      Network_GetHostnameByNetworkID(igi2_frame.zString, 22, ptNext);
      _snprintf(igi2_frame.Buffer, 0xFFu, "[%d]%c%s[%s]\n", ptNext, v19, (char *)&v5[2], igi2_frame.zString);
      NetManager_LogMessage(igi2_frame.Buffer);
      _snprintf(
        igi2_frame.Buffer,
        0xFFu,
        "   [%03d][%2.1f][%d]m [%d]msIdle gout[%d] gin[%d] b[%d]\n",
        igi2_frame.ptMiddle,
        igi2_frame.v30,
        igi2_frame.v29,
        igi2_frame.v34,
        igi2_frame.v28,
        igi2_frame.v32,
        igi2_frame.v35);
      NetManager_LogMessage(igi2_frame.Buffer);
      if ( p_ptTail )
      {
        v20 = p_ptTail[5];
        if ( v20 > 0
          && ((int)*p_ptTail > 0
           || (int)p_ptTail[1] > 0
           || (int)p_ptTail[2] > 0
           || (int)p_ptTail[3] > 0
           || (int)p_ptTail[4] > 0) )
        {
          _snprintf(
            igi2_frame.v38,
            0x64u,
            "t[%d]s[%d]a[%d]g[%d]as[%d]gs[%d]",
            v20,
            *p_ptTail,
            p_ptTail[1],
            p_ptTail[2],
            p_ptTail[3],
            p_ptTail[4]);
          igi2_frame.v38[99] = 0;
          _snprintf(igi2_frame.Buffer, 0xFFu, "   %s\n", igi2_frame.v38);
          NetManager_LogMessage(igi2_frame.Buffer);
        }
        p_ptTail[1] = 0;
        p_ptTail[2] = 0;
        *p_ptTail = 0;
        p_ptTail[3] = 0;
        p_ptTail[4] = 0;
        p_ptTail[5] = 0;
      }
    }
    p_ptTail = nullptr;
    goto LABEL_30;
  }
LABEL_40:
  if ( (ptNetManagerQTask[6].tQTaskChildren.ptHead || ptNetManagerQTask[1].ptNext)
    && v1->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    if ( Network_NumberOfWaitingFromHost(0) > 0 )
    {
      v21 = Network_NumberOfWaitingFromHost(0);
      _snprintf(igi2_frame.Buffer, 0xFFu, "Inbound g-queue from server non-null: %d\n", v21);
      NetManager_LogMessage(igi2_frame.Buffer);
    }
    v22 = Network_atQueues[0].tList.ptHead->ptNext;
    v23 = Network_atQueues[0].tList.ptHead->ptNext;
    v24 = 0;
    v25 = Network_atQueues[0].tList.ptHead;
    if ( Network_atQueues[0].tList.ptHead->ptNext )
    {
      do
      {
        if ( !v25[1].ptNext )
          ++v24;
        v25 = v23;
        v23 = v23->ptNext;
      }
      while ( v23 );
      if ( v24 > 0 )
      {
        v26 = 0;
        for ( j = Network_atQueues[0].tList.ptHead; v22; v22 = v22->ptNext )
        {
          if ( !j[1].ptNext )
            ++v26;
          j = v22;
        }
        _snprintf(igi2_frame.Buffer, 0xFFu, "Outbound q-queue to server non-null: %d\n", v26);
        NetManager_LogMessage(igi2_frame.Buffer);
      }
    }
  }
}

// source: j/0/network/netmanager.c:602  [size]
enum bool __cdecl NetManager_IsBuffering()
{
  return *((_DWORD *)&Flow_ptFlow->ptNetManagerQTask[31].tQTaskChildren.ptTail
         + (int)Flow_ptFlow->ptNetManagerQTask[32].tQTaskChildren.ptTail);
}

// source: j/0/network/netmanager.c:631  [size]
void __cdecl NetManager_PushBufferingState(enum bool isBuffering, char *zDesc)
{
  struct QTask_s *ptNetManagerQTask; // eax
  int v3; // ecx

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  v3 = (int)&ptNetManagerQTask[32].tQTaskChildren.ptTail->ptNext + 1;
  ptNetManagerQTask[32].tQTaskChildren.ptTail = (struct QTask_s *)v3;
  *((_DWORD *)&ptNetManagerQTask[31].tQTaskChildren.ptTail + v3) = isBuffering;
}

// source: j/0/network/netmanager.c:658  [size]
void __cdecl NetManager_PopBufferingState(char *zDesc)
{
  --Flow_ptFlow->ptNetManagerQTask[32].tQTaskChildren.ptTail;
}

// source: j/0/network/netmanager.c:683  [size]
enum bool __cdecl NetManager_IsBufferStateEmpty()
{
  return Flow_ptFlow->ptNetManagerQTask[32].tQTaskChildren.ptTail == (struct QTask_s *)-1;
}

// source: j/0/network/netmanager.c:702  [anchor-strings]
void __cdecl NetManager_LogBufferState(char *zDesc)
{
  struct QTask_s *ptNetManagerQTask; // eax
  struct QTask_s *ptTail; // edx
  char zTemp[256]; // [esp+4h] [ebp-100h] BYREF

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  ptTail = ptNetManagerQTask[32].tQTaskChildren.ptTail;
  if ( *((_DWORD *)&ptNetManagerQTask[31].tQTaskChildren.ptTail + (_DWORD)ptTail) )
    _snprintf(zTemp, 0xFFu, "[%s]: Buffering state TRUE. [l=%d]\n", zDesc, ptTail);
  else
    _snprintf(zTemp, 0xFFu, "[%s]: Buffering state FALSE. [l=%d]\n", zDesc, ptNetManagerQTask[32].tQTaskChildren.ptTail);
  NetManager_LogMessage(zTemp);
}

// source: j/0/network/netmanager.c:734  [anchor-strings]
void __cdecl NetManager_ClearBuffer()
{
  struct QTask_s *ptMiddle; // eax
  char *v1; // ecx
  char Buffer[256]; // [esp+0h] [ebp-100h] BYREF

  ptMiddle = Flow_ptFlow->ptNetManagerQTask[31].tQTaskChildren.ptMiddle;
  v1 = *(char **)&ptMiddle->eQTaskType;
  *(_DWORD *)&ptMiddle->eQTaskType = 0;
  if ( (int)v1 > 0 )
  {
    _snprintf(Buffer, 0xFFu, "ClearBuffer: Deleted %s packet(s) in receive buffer\n", v1);
    NetManager_LogMessage(Buffer);
  }
}

// source: j/0/network/netmanager.c:863  [anchor-mhash]
void __cdecl NetManager_CreateGameSpy()
{
  struct QTask_s *ptNetManagerQTask; // edi
  struct GameSpyCreateContext_s tCreateContext; // [esp+4h] [ebp-10h] BYREF

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  tCreateContext.socket = Network_UDPSocket;
  if ( AppContext_tAppContext.nPort <= 0 )
    tCreateContext.nPort = ServerConfig_tServerConfig.nPort;
  else
    tCreateContext.nPort = AppContext_tAppContext.nPort;
  tCreateContext.nCDProductID = 703;
  tCreateContext.eMode = ServerConfig_tServerConfig.isAutoBalance != false;
  QTask_NewFn(ptNetManagerQTask, GameSpy_eQTaskType, &tCreateContext);
}

// source: j/0/network/netmanager.c:903  [anchor-mhash]
void __cdecl NetManager_CreateASE()
{
  struct QTask_s *ptNetManagerQTask; // edi
  struct ASECreateContext_s tCreateContext; // [esp+4h] [ebp-8h] BYREF

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  tCreateContext.socket = Network_UDPSocket;
  if ( AppContext_tAppContext.nPort <= 0 )
    tCreateContext.nPort = ServerConfig_tServerConfig.nPort;
  else
    tCreateContext.nPort = AppContext_tAppContext.nPort;
  QTask_NewFn(ptNetManagerQTask, ASE_eQTaskType, &tCreateContext);
}

// source: j/0/network/netmanager.c:933  [anchor-mhash]
void __cdecl NetManager_StartConsoleListener()
{
  struct QTask_s *ptNetManagerQTask; // edi
  struct ConsoledCreateContext_s tCreateContext; // [esp+4h] [ebp-8h] BYREF

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  tCreateContext.nClearIdleInterval = 20000;
  tCreateContext.nMaxIdleTime = 300000;
  QTask_NewFn(ptNetManagerQTask, Consoled_eQTaskType, &tCreateContext);
}

// source: j/0/network/netmanager.c:965  [anchor-hash]
enum bool __cdecl NetManager_IsServerFullIncludingLoading()
{
  return SBYTE1(Flow_ptFlow->ptNetManagerQTask[3].ptPrev)
       + SBYTE2(Flow_ptFlow->ptNetManagerQTask[3].tQTaskChildren.ptHead) >= SBYTE2(Flow_ptFlow->ptNetManagerQTask[3].ptPrev);
}

// source: j/0/network/netmanager.c:988  [anchor-callee]
void __cdecl NetManager_UpdateServerSettings()
{
  struct QTask_s *ptNetManagerQTask; // esi
  struct QObjectVector_s *v1; // eax
  bool v2; // zf
  unsigned int nAllocated; // eax
  struct Flow_t *v4; // edi
  struct QTask_s *v5; // eax
  struct NetMission_t *v6; // ebp
  int v7; // ecx
  struct QReference_s *v8; // eax
  unsigned __int16 v9; // dx
  struct QTask_s *FirstChildOfType; // eax
  struct QTask_s *ptNext; // eax
  struct QTask_s *v12; // eax
  struct QTask_s *ptPrev; // eax
  unsigned __int16 v14; // dx
  int v15; // edi
  _DWORD *p_ptHead; // ebx
  struct QTask_s *NextSiblingOfType; // eax
  int v18; // eax
  struct QReferenceList_s *p_tQTaskRefList; // ecx

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  strncpy((char *)&ptNetManagerQTask[2].tQTaskRefList.ptTail, g_zPlayer1, 0xAu);
  HIBYTE(ptNetManagerQTask[2].eQTaskType) = 0;
  ptNetManagerQTask[5].tQTaskChildren.ptMiddle = (struct QTask_s *)ServerConfig_tServerConfig.nSpawnTimeToFree;
  ptNetManagerQTask[5].tQTaskChildren.ptHead = (struct QTask_s *)ServerConfig_tServerConfig.nSpawnSafeTime;
  LOBYTE(ptNetManagerQTask[5].tQTaskChildren.ptTail) = 1;
  BYTE1(ptNetManagerQTask[5].tQTaskChildren.ptTail) = ServerConfig_tServerConfig.isPublic;
  BYTE2(ptNetManagerQTask[5].tQTaskChildren.ptTail) = ServerConfig_tServerConfig.nWarmup;
  BYTE2(ptNetManagerQTask[3].ptPrev) = ServerConfig_tServerConfig.nSpectateMode;
  ptNetManagerQTask[5].tQTaskRefList.ptHead = (struct QReference_s *)ServerConfig_tServerConfig.nMoneyStart;
  ptNetManagerQTask[5].tQTaskRefList.ptTail = (struct QReference_s *)LODWORD(ServerConfig_tServerConfig.vSendDiffSpeed);
  ptNetManagerQTask[5].ptParent = (struct QTask_s *)ServerConfig_tServerConfig.nBombReposTime;
  LOBYTE(ptNetManagerQTask[5].eQTaskType) = ServerConfig_tServerConfig.isForceFirstSpec;
  LOBYTE(ptNetManagerQTask[3].ptPrev) = &ServerConfig_tServerConfig.zServerPassword[strlen(ServerConfig_tServerConfig.zServerPassword)
                                                                                  + 1] != &ServerConfig_tServerConfig.zServerPassword[1];
  strncpy((char *)&ptNetManagerQTask[1].ptPrev, ServerConfig_tServerConfig.zServerName, 0x40u);
  HIBYTE(ptNetManagerQTask[2].tQTaskRefList.ptMiddle) = 0;
  ptNetManagerQTask[4].tQTaskRefList.ptMiddle = (struct QReference_s *)ServerConfig_tServerConfig.nBombTime;
  ptNetManagerQTask[4].ptParent = (struct QTask_s *)ServerConfig_tServerConfig.nPloss;
  ptNetManagerQTask[6].ptNext = (struct QTask_s *)ServerConfig_tServerConfig.nTimeOut;
  v1 = Network_ptLoadingHosts;
  v2 = Network_ptLoadingHosts == nullptr;
  LOBYTE(ptNetManagerQTask[6].ptPrev) = ServerConfig_tServerConfig.isAllowSniperRifles;
  if ( v2 )
    LOBYTE(nAllocated) = 0;
  else
    nAllocated = v1->nAllocated;
  v4 = Flow_ptFlow;
  BYTE2(ptNetManagerQTask[3].tQTaskChildren.ptHead) = nAllocated;
  v5 = v4->ptNetManagerQTask;
  if ( v5 && v5[8].tQTaskRefList.ptMiddle )
  {
    HIBYTE(ptNetManagerQTask[3].ptPrev) = NetMission_eCurrentObjective;
    v6 = NetMission_ptNetMission;
    ptNetManagerQTask[4].tQTaskChildren.ptTail = (struct QTask_s *)NetMission_ptNetMission->nObjectiveEndTime;
    ptNetManagerQTask[4].tQTaskRefList.ptHead = (struct QReference_s *)v6->nMissionEndTime;
    ptNetManagerQTask[4].tQTaskRefList.ptTail = (struct QReference_s *)v6->nWarmupEndTime;
    v7 = 0;
    while ( 1 )
    {
      v8 = Level_atLevelQTaskID[v7];
      if ( v8 )
      {
        if ( v8->pxObject == SpawnArea_ptActive )
          break;
      }
      if ( ++v7 >= 4096 )
      {
        v7 = -1;
        break;
      }
    }
    v9 = TeamManager_eQTaskType;
    ptNetManagerQTask[5].ptPrev = (struct QTask_s *)v7;
    FirstChildOfType = QTask_GetFirstChildOfType(v4->ptNetManagerQTask, v9);
    if ( FirstChildOfType )
      ptNext = FirstChildOfType[1].ptNext;
    else
      LOBYTE(ptNext) = -1;
    LOBYTE(ptNetManagerQTask[3].tQTaskChildren.ptHead) = (_BYTE)ptNext;
    v12 = QTask_GetFirstChildOfType(v4->ptNetManagerQTask, v9);
    if ( v12 )
      ptPrev = v12[1].ptPrev;
    else
      LOBYTE(ptPrev) = -1;
    v14 = NetObjective_eQTaskType;
    BYTE1(ptNetManagerQTask[3].tQTaskChildren.ptHead) = (_BYTE)ptPrev;
    v15 = 0;
    p_ptHead = &ptNetManagerQTask[3].tQTaskRefList.ptHead;
    while ( 1 )
    {
      NextSiblingOfType = QTask_GetFirstChildOfType(&v6->tQTask, v14);
      if ( NextSiblingOfType )
      {
        while ( NextSiblingOfType[5].ptNext != (struct QTask_s *)(v15 + 1) )
        {
          NextSiblingOfType = QTask_GetNextSiblingOfType(NextSiblingOfType, v14);
          if ( !NextSiblingOfType )
            goto LABEL_29;
        }
        if ( NextSiblingOfType[5].tQTaskRefList.ptTail )
        {
          *((_BYTE *)&ptNetManagerQTask[3].tQTaskChildren.ptHead + v15 + 3) = NextSiblingOfType[5].ptPrev;
        }
        else if ( NextSiblingOfType[5].ptParent )
        {
          *((_BYTE *)&ptNetManagerQTask[3].tQTaskChildren.ptHead + v15 + 3) = NextSiblingOfType[5].ptPrev == nullptr;
        }
        else
        {
          *((_BYTE *)&ptNetManagerQTask[3].tQTaskChildren.ptHead + v15 + 3) = -1;
        }
        *p_ptHead = NextSiblingOfType[5].tQTaskChildren.ptTail;
      }
LABEL_29:
      ++v15;
      ++p_ptHead;
      if ( v15 >= 8 )
        break;
      v6 = NetMission_ptNetMission;
    }
  }
  else
  {
    HIBYTE(ptNetManagerQTask[3].ptPrev) = -1;
    ptNetManagerQTask[4].tQTaskChildren.ptTail = (struct QTask_s *)-1;
    ptNetManagerQTask[4].tQTaskRefList.ptHead = (struct QReference_s *)-1;
    ptNetManagerQTask[4].tQTaskRefList.ptTail = (struct QReference_s *)-1;
    ptNetManagerQTask[5].ptPrev = (struct QTask_s *)-1;
    LOBYTE(ptNetManagerQTask[3].tQTaskChildren.ptHead) = -1;
    BYTE1(ptNetManagerQTask[3].tQTaskChildren.ptHead) = -1;
    v18 = 0;
    p_tQTaskRefList = &ptNetManagerQTask[3].tQTaskRefList;
    do
    {
      *((_BYTE *)&ptNetManagerQTask[3].tQTaskChildren.ptHead + v18 + 3) = -1;
      p_tQTaskRefList->ptHead = (struct QReference_s *)-1;
      ++v18;
      p_tQTaskRefList = (struct QReferenceList_s *)((char *)p_tQTaskRefList + 4);
    }
    while ( v18 < 8 );
  }
  if ( Timer_isPerformanceCounter )
    ptNetManagerQTask[5].tQTaskRefList.ptMiddle = (struct QReference_s *)(Timer_GetPerformanceCounter()
                                                                        - Timer_nStartTime);
  else
    ptNetManagerQTask[5].tQTaskRefList.ptMiddle = (struct QReference_s *)(GetTickCount() - Timer_nStartTime);
}

// source: j/0/network/netmanager.c:1101  [size]
void __cdecl NetManager_SetLocalPingCB(void (__cdecl *pfLocalPing)(int, int, int, int))
{
  Flow_ptFlow->ptNetManagerQTask[36].ptNext = (struct QTask_s *)pfLocalPing;
}

void __cdecl sub_417370(int a1, _DWORD *a2)
{
  int v2; // eax
  int v3; // eax
  int v4; // edx
  struct QReference_s *ptTail; // eax
  char Buffer[256]; // [esp+0h] [ebp-100h] BYREF

  if ( HumanPlayer_ptQTask && !LOBYTE(HumanPlayer_ptQTask[29].tQTaskRefList.ptHead) )
  {
    v2 = a1;
    if ( a1 <= -1000 )
      v2 = -1000;
    a2[a2[74] + 75] = v2;
    a2[74] = (a2[74] + 1) % 5;
    v3 = a2[75] + a2[76] + a2[77] + a2[78] + a2[79];
    if ( v3 > 1500 )
      goto LABEL_9;
    v4 = a1;
    if ( a1 < 0 )
      v4 = -a1;
    if ( v4 > 5000 )
    {
LABEL_9:
      _snprintf(Buffer, 0xFFu, "Speedhack detected! TimeDiff: %d ms - TotalTimeDiff: %d ms\n", a1, v3);
      if ( StatusScreen_ptStatusScreenQTask )
      {
        ptTail = StatusScreen_ptStatusScreenQTask[52].tQTaskRefList.ptTail;
        if ( ptTail )
          TextScroller_Add((struct TextScroller_s *)ptTail, Buffer, TEXTSCROLLER_COLOUR_GREEN);
      }
      NetManager_LogMessage(Buffer);
      NetManager_LogMessage("\r\n");
      a2[92] = 1;
    }
  }
}

// source: j/0/network/netmanager.c:1120  [anchor-strings]
void __cdecl NetManager_Synchronize(struct NetManagerGameMessage_s *ptGameMessage, int ltcg_arg1)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v32; };
    struct { char igi2_o1[4]; int v33; };
    struct { char igi2_o2[8]; int v34; };
    struct { char igi2_o3[12]; struct QTask_s *a2; };
    struct { char igi2_o4[16]; int v36; };
    struct { char igi2_o5[20]; int v37; };
    struct { char igi2_o6[24]; char Buffer[256]; };
    char igi2_extent[280];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // esi
  DWORD PerformanceCounter; // eax
  int v4; // ebp
  _DWORD **v5; // eax
  int v6; // ebx
  _DWORD *v7; // eax
  struct Node_s *ptHead; // ecx
  struct Node_s *ptNext; // edi
  int v10; // edx
  bool v11; // cc
  struct QTask_s *ptNetManagerQTask; // esi
  DWORD TickCount; // eax
  struct QTask_s *v14; // ebp
  struct QReference_s *v15; // esi
  DWORD v16; // eax
  struct Flow_t *v17; // edx
  int v18; // edi
  bool v19; // zf
  struct QTask_s *v20; // ebx
  DWORD v21; // eax
  DWORD v22; // eax
  struct Flow_t *v23; // edx
  struct QTask_s *v24; // esi
  DWORD v25; // eax
  DWORD v26; // eax
  int v27; // ecx
  bool v28; // sf
  int v29; // ecx
  int v30; // eax
  struct QTask_s *v31; // eax

  v2 = 0;
  igi2_frame.a2 = Flow_ptFlow->ptNetManagerQTask;
  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  v4 = PerformanceCounter - Timer_nStartTime - ptGameMessage->nLocalTime;
  igi2_frame.v32 = -1;
  igi2_frame.v34 = -1;
  igi2_frame.v33 = -1;
  v5 = (_DWORD **)(12 * NetManager_nPingIndex + 7374536);
  igi2_frame.v37 = v4;
  v6 = v4 / 2;
  igi2_frame.v36 = 0;
  *(_DWORD *)(ltcg_arg1 + 4) = v4;
  v7 = Node_Remove(v5);
  ptHead = NetManager_tPingList.ptHead;
  v7[2] = v4;
  ptNext = ptHead->ptNext;
  if ( ptHead->ptNext )
  {
    while ( 1 )
    {
      if ( !v2 )
      {
        if ( (int)ptHead[1].ptNext > (int)(v7[2]) )
        {
          v7 = Node_InsertBefore(v7, (int)ptHead);
LABEL_10:
          v2 = 1;
          goto LABEL_11;
        }
        if ( !ptHead->ptNext->ptNext )
        {
          v7 = Node_InsertAfter(v7, (int)ptHead);
          goto LABEL_10;
        }
      }
LABEL_11:
      v10 = ++igi2_frame.v36;
      if ( igi2_frame.v36 == 6 )
      {
        igi2_frame.v32 = (int)ptHead[1].ptNext;
      }
      else if ( v10 == 16 )
      {
        igi2_frame.v34 = (int)ptHead[1].ptNext;
      }
      else if ( v10 == 25 )
      {
        igi2_frame.v33 = (int)ptHead[1].ptNext;
      }
      if ( igi2_frame.v32 < 0 || igi2_frame.v34 < 0 || igi2_frame.v33 < 0 || !v2 )
      {
        ptHead = ptNext;
        ptNext = ptNext->ptNext;
        if ( ptNext )
          continue;
      }
      break;
    }
  }
  NetManager_nPingIndex = (NetManager_nPingIndex + 1) % 32;
  if ( igi2_frame.v33 <= 0 )
    v11 = v4 < 500;
  else
    v11 = v4 < igi2_frame.v33;
  if ( v11 )
  {
    ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
    if ( Timer_isPerformanceCounter )
      TickCount = Timer_GetPerformanceCounter();
    else
      TickCount = GetTickCount();
    sub_417370(
      TickCount
    - Timer_nStartTime
    + (char *)ptNetManagerQTask[6].tQTaskRefList.ptMiddle
    - (char *)ptNetManagerQTask[6].tQTaskRefList.ptTail
    - ptGameMessage[1].eGameMessage
    - v6,
      igi2_frame.a2);
  }
  if ( v4 <= igi2_frame.v32 || (unsigned int)igi2_frame.v32 >= 0xBB8 )
  {
    v14 = Flow_ptFlow->ptNetManagerQTask;
    v15 = (struct QReference_s *)(v6 + ptGameMessage[1].eGameMessage);
    if ( Timer_isPerformanceCounter )
      v16 = Timer_GetPerformanceCounter();
    else
      v16 = GetTickCount();
    v17 = Flow_ptFlow;
    v18 = v16 - Timer_nStartTime + ((char *)v14[6].tQTaskRefList.ptMiddle - (char *)v14[6].tQTaskRefList.ptTail);
    v19 = Timer_isPerformanceCounter == 0;
    *(_DWORD *)&igi2_frame.a2[6].eQTaskType = v6;
    v20 = v17->ptNetManagerQTask;
    if ( v19 )
      v21 = GetTickCount();
    else
      v21 = Timer_GetPerformanceCounter();
    v19 = Timer_isPerformanceCounter == 0;
    igi2_frame.a2[7].ptNext = (struct QTask_s *)(v21
                                    - Timer_nStartTime
                                    + (char *)v20[6].tQTaskRefList.ptMiddle
                                    - (char *)v20[6].tQTaskRefList.ptTail
                                    - (_DWORD)v15);
    igi2_frame.a2[6].tQTaskRefList.ptMiddle = v15;
    if ( v19 )
      v22 = GetTickCount();
    else
      v22 = Timer_GetPerformanceCounter();
    v23 = Flow_ptFlow;
    igi2_frame.a2[6].tQTaskRefList.ptTail = (struct QReference_s *)(v22 - Timer_nStartTime);
    v24 = v23->ptNetManagerQTask;
    if ( Timer_isPerformanceCounter )
      v25 = Timer_GetPerformanceCounter();
    else
      v25 = GetTickCount();
    v26 = v25 - Timer_nStartTime;
    v27 = (char *)v24[6].tQTaskRefList.ptMiddle - (char *)v24[6].tQTaskRefList.ptTail - v18;
    v28 = (int)(v26 + v27) < 0;
    v29 = v26 + v27;
    v30 = v29;
    if ( v28 )
      v30 = -v29;
    if ( v30 > 10 )
    {
      _snprintf(igi2_frame.Buffer, 0xFFu, "Time synch changed > 10ms: %d ms\n", v29);
      NetManager_LogMessage(igi2_frame.Buffer);
    }
    v4 = igi2_frame.v37;
  }
  v31 = igi2_frame.a2[36].ptNext;
  if ( v31 )
    ((void (__cdecl *)(int, int, int, int))v31)(igi2_frame.v32, igi2_frame.v34, igi2_frame.v33, v4);
  *(_DWORD *)(ltcg_arg1 + 8) = igi2_frame.v32;
  *(_DWORD *)(ltcg_arg1 + 12) = igi2_frame.v34;
  *(_DWORD *)(ltcg_arg1 + 16) = igi2_frame.v33;
}

// source: j/0/network/netmanager.c:1302  [anchor-mhash]
struct Result_s *__cdecl NetManager_GetRandomCB(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  int v3; // eax
  int v4; // edx
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  if ( ptArgList && ptArgList->nArguments == 1 )
  {
    v3 = Script_EvalArgInt(ptArgList, 0);
    if ( v3 > 0 )
    {
      if ( v3 == 1 )
        v4 = 1;
      else
        v4 = NetManager_nRandomInt % v3 + 1;
    }
    else
    {
      v4 = -1;
    }
    Rs.nResult = v4;
    Rs.vResult = (double)v4;
  }
  else
  {
    Rs.nResult = 0;
    Rs.vResult = 0.0;
  }
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/netmanager.c:1338  [anchor-callee]
void __cdecl NetManager_EnumMissionsCB(struct Mission_s *ptMission)
{
  _DWORD *v1; // eax
  struct Node_s *ptHead; // ecx
  struct Node_s *ptNext; // edx

  v1 = Mem_AllocFn(16, 4);
  v1[1] = 0;
  *v1 = 0;
  v1[2] = ptMission->iID;
  v1[3] = ptMission;
  ptHead = NetManager_tMapList.ptHead;
  if ( NetManager_tMapList.ptHead == (struct Node_s *)&NetManager_tMapList.ptMiddle
    || (ptNext = NetManager_tMapList.ptHead->ptNext) == nullptr )
  {
LABEL_2:
    List_AddTail(v1, (int)&NetManager_tMapList);
  }
  else
  {
    while ( (int)ptHead[1].ptNext <= (int)(v1[2]) )
    {
      ptHead = ptNext;
      ptNext = ptNext->ptNext;
      if ( !ptNext )
        goto LABEL_2;
    }
    Node_InsertBefore(v1, (int)ptHead);
  }
}

// source: j/0/network/netmanager.c:1363  [size]
struct Result_s *__cdecl NetManager_ListAvailableItemsCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct Node_s *ptHead; // eax
  struct Node_s *i; // esi
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  ptHead = NetManager_tMapList.ptHead;
  for ( i = NetManager_tMapList.ptHead->ptNext; i; i = i->ptNext )
  {
    ScrollListBox_AddItemEx((char *)&ptHead[1].ptPrev[2], (int)ptHead[1].ptNext, false);
    ptHead = i;
  }
  Rs.nResult = 1;
  Rs.vResult = 1.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/netmanager.c:1391  [size]
struct Result_s *__cdecl NetManager_ListActiveItemsCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct Node_s *ptHead; // eax
  struct Node_s *i; // esi
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  ptHead = NetManager_tActiveMapList.ptHead;
  for ( i = NetManager_tActiveMapList.ptHead->ptNext; i; i = i->ptNext )
  {
    ScrollListBox_AddItemEx((char *)&ptHead[1].ptPrev[2], (int)ptHead[1].ptNext, false);
    ptHead = i;
  }
  Rs.nResult = 1;
  Rs.vResult = 1.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/netmanager.c:1416  [size]
struct Result_s *__cdecl NetManager_GetActiveMapCount(
        struct Result_s *retstr,
        void *pxUnused,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int n; };
    struct { char igi2_o1[4]; struct Result_s Rs; };
    char igi2_extent[28];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Node_s *ptNext; // eax
  int v4; // ecx

  ptNext = NetManager_tActiveMapList.ptHead->ptNext;
  v4 = 0;
  igi2_frame.n = 0;
  if ( NetManager_tActiveMapList.ptHead->ptNext )
  {
    do
    {
      ptNext = ptNext->ptNext;
      ++v4;
    }
    while ( ptNext );
    igi2_frame.n = v4;
  }
  igi2_frame.Rs.nResult = v4;
  igi2_frame.Rs.vResult = (double)igi2_frame.n;
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/netmanager.c:1442  [anchor-mhash]
struct Result_s *__cdecl NetManager_MoveItemToActiveListCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // esi
  _DWORD *v5; // eax
  struct Node_s *ptHead; // edx
  struct Node_s *ptNext; // ecx
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->isQVM )
  {
    ptArgList = nullptr;
    QVM_EvalArg(&ptArgList, 4, v3, 1, 1);
    v4 = ptArgList;
  }
  else
  {
    v4 = (struct ArgList_s *)Expression_EvalInt(ptArgList->aptExpression[1]);
  }
  v5 = Mem_AllocFn(16, 4);
  v5[1] = 0;
  *v5 = 0;
  v5[2] = v4;
  ptHead = Mission_tMissions.ptHead;
  ptNext = Mission_tMissions.ptHead->ptNext;
  if ( Mission_tMissions.ptHead->ptNext )
  {
    while ( (struct ArgList_s *)ptHead[1].ptNext != v4 )
    {
      ptHead = ptNext;
      ptNext = ptNext->ptNext;
      if ( !ptNext )
        goto LABEL_7;
    }
  }
  else
  {
LABEL_7:
    ptHead = nullptr;
  }
  v5[3] = ptHead;
  List_AddTail(v5, (int)&NetManager_tActiveMapList);
  Rs.nResult = 2;
  Rs.vResult = 2.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/netmanager.c:1471  [anchor-mhash]
struct Result_s *__cdecl NetManager_MoveItemToAvailableListCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // ebp
  struct Node_s *ptHead; // eax
  struct Node_s *i; // ebx
  int v7; // esi
  struct Result_s Rs; // [esp+10h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->isQVM )
  {
    ptArgList = nullptr;
    QVM_EvalArg(&ptArgList, 4, v3, 1, 1);
    v4 = ptArgList;
  }
  else
  {
    v4 = (struct ArgList_s *)Expression_EvalInt(ptArgList->aptExpression[1]);
  }
  ptHead = NetManager_tActiveMapList.ptHead;
  for ( i = NetManager_tActiveMapList.ptHead->ptNext; i; i = i->ptNext )
  {
    if ( (struct ArgList_s *)ptHead[1].ptNext == v4 )
    {
      v7 = *(_DWORD *)((unsigned int)(Node_Remove(ptHead) - 1) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v7);
      memset(*(void **)(v7 + 8), 0xCDu, *(_DWORD *)(v7 + 16));
      free((void *)v7);
    }
    ptHead = i;
  }
  Rs.nResult = 2;
  Rs.vResult = 2.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/netmanager.c:1504  [anchor-mhash]
struct Result_s *__cdecl NetManager_ClearActiveListCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct Node_s *ptHead; // eax
  struct Node_s *i; // ebx
  _DWORD **v5; // eax
  int v6; // esi
  struct Result_s Rs; // [esp+Ch] [ebp-18h] BYREF

  ptHead = NetManager_tActiveMapList.ptHead;
  for ( i = NetManager_tActiveMapList.ptHead->ptNext; i; i = i->ptNext )
  {
    v5 = Node_Remove(ptHead);
    if ( v5 )
    {
      v6 = *(_DWORD *)((unsigned int)(v5 - 1) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v6);
      memset(*(void **)(v6 + 8), 0xCDu, *(_DWORD *)(v6 + 16));
      free((void *)v6);
    }
    ptHead = i;
  }
  Rs.nResult = 1;
  Rs.vResult = 1.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/netmanager.c:1531  [anchor-caller]
struct Result_s *__cdecl NetManager_MoveActiveListItemUpCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // ebx
  struct Node_s *ptHead; // eax
  struct Node_s *i; // esi
  int ptPrev; // edi
  _DWORD *v8; // eax
  struct Result_s Rs; // [esp+Ch] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->isQVM )
  {
    ptArgList = nullptr;
    QVM_EvalArg(&ptArgList, 4, v3, 1, 1);
    v4 = ptArgList;
  }
  else
  {
    v4 = (struct ArgList_s *)Expression_EvalInt(ptArgList->aptExpression[1]);
  }
  ptHead = NetManager_tActiveMapList.ptHead;
  for ( i = NetManager_tActiveMapList.ptHead->ptNext; i; i = i->ptNext )
  {
    if ( (struct ArgList_s *)ptHead[1].ptNext == v4 )
    {
      ptPrev = (int)ptHead->ptPrev;
      if ( *(_DWORD *)(ptPrev + 4) )
      {
        if ( ptPrev )
        {
          v8 = Node_Remove(ptHead);
          Node_InsertBefore(v8, ptPrev);
        }
      }
    }
    ptHead = i;
  }
  Rs.nResult = 2;
  Rs.vResult = 2.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/netmanager.c:1570  [anchor-caller]
struct Result_s *__cdecl NetManager_MoveActiveListItemDownCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // ebx
  struct Node_s *ptHead; // eax
  struct Node_s *i; // esi
  struct Node_s *ptNext; // edi
  _DWORD *v8; // eax
  struct Result_s Rs; // [esp+Ch] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->isQVM )
  {
    ptArgList = nullptr;
    QVM_EvalArg(&ptArgList, 4, v3, 1, 1);
    v4 = ptArgList;
  }
  else
  {
    v4 = (struct ArgList_s *)Expression_EvalInt(ptArgList->aptExpression[1]);
  }
  ptHead = NetManager_tActiveMapList.ptHead;
  for ( i = NetManager_tActiveMapList.ptHead->ptNext; i; i = i->ptNext )
  {
    if ( (struct ArgList_s *)ptHead[1].ptNext == v4 )
    {
      ptNext = ptHead->ptNext;
      if ( ptHead->ptNext->ptNext )
      {
        if ( ptNext )
        {
          v8 = Node_Remove(ptHead);
          Node_InsertAfter(v8, (int)ptNext);
        }
      }
    }
    ptHead = i;
  }
  Rs.nResult = 2;
  Rs.vResult = 2.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/netmanager.c:1608  [size]
struct Result_s *__cdecl NetManager_GetNumberOfMissionsInActiveListCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int iC; };
    struct { char igi2_o1[4]; struct Result_s Rs; };
    char igi2_extent[28];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Node_s *ptNext; // eax
  int v4; // ecx

  ptNext = NetManager_tActiveMapList.ptHead->ptNext;
  v4 = 0;
  igi2_frame.iC = 0;
  if ( NetManager_tActiveMapList.ptHead->ptNext )
  {
    do
    {
      ptNext = ptNext->ptNext;
      ++v4;
    }
    while ( ptNext );
    igi2_frame.iC = v4;
  }
  igi2_frame.Rs.nResult = v4;
  igi2_frame.Rs.vResult = (double)igi2_frame.iC;
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/netmanager.c:1632  [anchor-strings]
void __cdecl NetManager_ZUpdateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { unsigned int nBitsToUnpack; };
    struct { char igi2_o1[4]; unsigned int v22; };
    struct { char igi2_o2[8]; unsigned int v23; };
    struct { char igi2_o3[12]; struct QTask_s *v24; };
    struct { char igi2_o4[16]; struct PackMan_t ptPackMan; };
    struct { char igi2_o5[28]; struct ClientGameMessageUpdateBody_s ptBody; };
    char igi2_extent[60];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char *v2; // esi
  unsigned int v3; // edx
  char *v4; // eax
  unsigned int v5; // ecx
  char *v6; // esi
  unsigned __int8 *v7; // ebx
  struct QTask_s *v8; // ebp
  unsigned int v9; // edi
  int v10; // edx
  struct QTask_s *ptNetManagerQTask; // edi
  struct QTask_s *v12; // eax
  struct Client_s *v13; // ebp
  unsigned __int8 v14; // dl
  unsigned __int8 v15; // cl
  __int16 v16; // ax
  __int16 v17; // dx
  unsigned __int8 v18; // cl
  unsigned __int8 v19; // cl
  DWORD PerformanceCounter; // eax
  char *pxContexta = *(char * *)&pxContext; // [esp+48h] [ebp+8h] ARGSLOT

  v2 = *((char **)pxContext + 3);
  v3 = v2[18];
  v4 = (char *)v2[16];
  v5 = v2[17];
  v6 = v2 + 8;
  igi2_frame.v22 = v3;
  igi2_frame.nBitsToUnpack = v5;
  igi2_frame.v23 = v6[11];
  igi2_frame.ptPackMan.buffer = (unsigned int *)&v6[14 * (_DWORD)(v4 + 2)];
  igi2_frame.ptPackMan.nNextBitWrite = 0;
  igi2_frame.ptPackMan.nNextBitRead = 0;
  if ( v4 )
  {
    v7 = (unsigned __int8 *)(v6 + 24);
    pxContexta = v4;
    do
    {
      v8 = (struct QTask_s *)*v7;
      igi2_frame.v24 = v8;
      v9 = PackMan_Unpack(&igi2_frame.ptPackMan, igi2_frame.nBitsToUnpack);
      v10 = PackMan_Unpack(&igi2_frame.ptPackMan, igi2_frame.v22) + *((_DWORD *)v6 + 4);
      igi2_frame.ptBody.tPosition.nX = v9 + *((_DWORD *)v6 + 3);
      igi2_frame.ptBody.tPosition.nY = v10;
      igi2_frame.ptBody.tPosition.nZ = *((_DWORD *)v6 + 5) + PackMan_Unpack(&igi2_frame.ptPackMan, igi2_frame.v23);
      ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
      if ( v8 == ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
      {
        NetManager_LogMessage("Received pos Zupdate to local player\n");
      }
      else
      {
        v12 = nullptr;
        while ( 1 )
        {
          v12 = v12
              ? QTask_GetNextSiblingOfType(v12, Client_eQTaskType)
              : QTask_GetFirstChildOfType(ptNetManagerQTask, Client_eQTaskType);
          v13 = (struct Client_s *)v12;
          if ( !v12 )
            break;
          if ( v12[1].ptNext == igi2_frame.v24 )
          {
            v14 = v7[1];
            v15 = v7[3];
            igi2_frame.ptBody.eNetworkID = *v7;
            igi2_frame.ptBody.vY = v7[2];
            v16 = *((_WORD *)v7 + 3);
            igi2_frame.ptBody.vX = v14;
            v17 = *((_WORD *)v7 + 2);
            igi2_frame.ptBody.vGamma = v16;
            LOBYTE(v16) = v7[10];
            igi2_frame.ptBody.vZ = v15;
            v18 = v7[8];
            igi2_frame.ptBody.vAlpha = v17;
            LOBYTE(v17) = v7[9];
            igi2_frame.ptBody.eAnimState = v16;
            igi2_frame.ptBody.vAlphaSpeed = v18;
            v19 = v7[11];
            igi2_frame.ptBody.vGammaSpeed = v17;
            LOBYTE(v17) = v7[12];
            igi2_frame.ptBody.eUpperBody = v19;
            igi2_frame.ptBody.isShowPlayer = v17;
            if ( Timer_isPerformanceCounter )
              PerformanceCounter = Timer_GetPerformanceCounter();
            else
              PerformanceCounter = GetTickCount();
            Client_HandleUpdate(
              v13,
              &igi2_frame.ptBody,
              PerformanceCounter
            - Timer_nStartTime
            + (char *)ptNetManagerQTask[6].tQTaskRefList.ptMiddle
            - (char *)ptNetManagerQTask[6].tQTaskRefList.ptTail,
              *((_DWORD *)v6 + 1));
            break;
          }
        }
      }
      v7 += 14;
      --pxContexta;
    }
    while ( pxContexta );
  }
}

// source: j/0/network/netmanager.c:1766  [anchor-strings]
void __cdecl NetManager_ClientGameMessageUpdateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v12; };
    struct { char igi2_o1[4]; int v13; };
    struct { char igi2_o2[8]; char Buffer[256]; };
    char igi2_extent[264];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // ebp
  int v3; // eax
  int v4; // ebp
  struct ClientGameMessageUpdateBody_s *v5; // ebp
  struct QTask_s *eNetworkID; // ebx
  struct QTask_s *ptNetManagerQTask; // edi
  unsigned __int16 v8; // dx
  struct QTask_s *NextSiblingOfType; // eax
  struct Client_s *v10; // esi
  DWORD PerformanceCounter; // eax

  v2 = *((_DWORD *)pxContext + 3);
  v3 = *(char *)(v2 + 16);
  v4 = v2 + 8;
  igi2_frame.v13 = v4;
  if ( v3 )
  {
    v5 = (struct ClientGameMessageUpdateBody_s *)(v4 + 12);
    igi2_frame.v12 = v3;
    do
    {
      eNetworkID = (struct QTask_s *)v5->eNetworkID;
      ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
      if ( eNetworkID == ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
      {
        NetManager_LogMessage("Received pos update to local player");
      }
      else
      {
        v8 = Client_eQTaskType;
        NextSiblingOfType = nullptr;
        do
        {
          if ( NextSiblingOfType )
            NextSiblingOfType = QTask_GetNextSiblingOfType(NextSiblingOfType, v8);
          else
            NextSiblingOfType = QTask_GetFirstChildOfType(ptNetManagerQTask, v8);
          v10 = (struct Client_s *)NextSiblingOfType;
          if ( !NextSiblingOfType )
          {
            _snprintf(igi2_frame.Buffer, 0xFFu, "Received pos update from server on unknown player[%d]\n", eNetworkID);
            NetManager_LogMessage(igi2_frame.Buffer);
            goto LABEL_16;
          }
        }
        while ( NextSiblingOfType[1].ptNext != eNetworkID );
        if ( Timer_isPerformanceCounter )
          PerformanceCounter = Timer_GetPerformanceCounter();
        else
          PerformanceCounter = GetTickCount();
        Client_HandleUpdate(
          v10,
          v5,
          PerformanceCounter
        - Timer_nStartTime
        + (char *)ptNetManagerQTask[6].tQTaskRefList.ptMiddle
        - (char *)ptNetManagerQTask[6].tQTaskRefList.ptTail,
          *(_DWORD *)(igi2_frame.v13 + 4));
      }
LABEL_16:
      ++v5;
      --igi2_frame.v12;
    }
    while ( igi2_frame.v12 );
  }
}

// source: j/0/network/netmanager.c:1868  [anchor-strings]
struct NetManager_s *__cdecl NetManager_RunServerAlways(struct NetManager_s *ptNetManager)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct Server_s *ptServer; };
    struct { char igi2_o1[4]; char zTemp[256]; };
    char igi2_extent[260];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *FirstChildOfType; // ebx
  struct QTask_s *v3; // ebp
  struct QTask_s *v4; // edi
  int v5; // eax
  struct QTask_s *v6; // esi
  DWORD PerformanceCounter; // eax
  struct NetManager_s *result; // eax

  FirstChildOfType = QTask_GetFirstChildOfType(&ptNetManager->tQTask, GameSpy_eQTaskType);
  v3 = QTask_GetFirstChildOfType(&ptNetManager->tQTask, ASE_eQTaskType);
  v4 = QTask_GetFirstChildOfType(&ptNetManager->tQTask, Consoled_eQTaskType);
  igi2_frame.ptServer = (struct Server_s *)QTask_GetFirstChildOfType(&ptNetManager->tQTask, Server_eQTaskType);
  v5 = Network_RunServer(ptNetManager->pxServerInterface);
  if ( v5 > 60 )
  {
    _snprintf(igi2_frame.zTemp, 0xFFu, "High input: %d packets\n", v5);
    NetManager_LogMessage(igi2_frame.zTemp);
  }
  if ( FirstChildOfType )
    ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][FirstChildOfType->eQTaskType].pfHandler)(FirstChildOfType);
  if ( v3 )
    ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][v3->eQTaskType].pfHandler)(v3);
  if ( v4 )
    ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][v4->eQTaskType].pfHandler)(v4);
  if ( !*((_DWORD *)&Flow_ptFlow->ptNetManagerQTask[31].tQTaskChildren.ptTail
        + (int)Flow_ptFlow->ptNetManagerQTask[32].tQTaskChildren.ptTail)
    && !*(_DWORD *)&ptNetManager[1].tServerGameSettings.zServerName[12] )
  {
    Server_SendGameMessageAll(igi2_frame.ptServer);
  }
  v6 = QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, MapControl_eQTaskType);
  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  result = (struct NetManager_s *)(PerformanceCounter - Timer_nStartTime);
  if ( (char *)result - (char *)v6[1].tQTaskRefList.ptMiddle > (int)v6[1].tQTaskRefList.ptHead )
  {
    v6[1].tQTaskRefList.ptMiddle = (struct QReference_s *)result;
    NetManager_SendScoreUpdate();
  }
  return result;
}

// source: j/0/network/netmanager.c:1938  [anchor-strings]
enum bool __cdecl NetManager_IsSelectedSessionNonFull()
{
  int v0; // ecx
  int v1; // eax
  char zTemp[256]; // [esp+4h] [ebp-100h] BYREF

  v0 = byte_704B1D[240 * NetManager_nSelectedSession];
  v1 = byte_704B1D[240 * NetManager_nSelectedSession + 5];
  if ( v1 + v0 < byte_704B1D[240 * NetManager_nSelectedSession + 1] )
    return true;
  _snprintf(zTemp, 0xFFu, "Server full:(%d+%d/%d)\n", v1, v0, byte_704B1D[240 * NetManager_nSelectedSession + 1]);
  NetManager_LogMessage(zTemp);
  return false;
}

// source: j/0/network/netmanager.c:1980  [anchor-mhash]
enum bool __cdecl NetManager_IsSelectedSessionNonProtected()
{
  return byte_704B1C[240 * NetManager_nSelectedSession] == 0;
}

// source: j/0/network/netmanager.c:2002  [anchor-strings]
enum bool __cdecl NetManager_IsSelectedSessionCompatible()
{
  char *v0; // esi
  char zTemp[256]; // [esp+4h] [ebp-100h] BYREF

  v0 = (char *)(240 * NetManager_nSelectedSession + 7359244);
  if ( !strncmp(v0, g_zPlayer1, 0xAu) )
  {
    _snprintf(zTemp, 0xFFu, "Compatible versions: '%s'\n", v0);
    NetManager_LogMessage(zTemp);
    return true;
  }
  else
  {
    _snprintf(zTemp, 0xFFu, "Incompatible versions. Local '%s'. Server '%s'\n", g_zPlayer1, v0);
    NetManager_LogMessage(zTemp);
    return false;
  }
}

// source: j/0/network/netmanager.c:2038  [size]
char *__cdecl NetManager_GetSelectedSessionVersion()
{
  return (char *)(240 * NetManager_nSelectedSession + 7359244);
}

// source: j/0/network/netmanager.c:2063  [anchor-strings]
enum bool __cdecl NetManager_FindSession(char *zString, int nPort, int nTimeOut)
{
  #pragma pack(push, 1)
  union
  {
    struct { enum bool isAnswered; };
    struct { char igi2_o1[4]; unsigned __int8 zIpAddress[4]; };
    struct { char igi2_o2[8]; int nAdapter; };
    struct { char igi2_o3[12]; struct Node_s *ptTemp; };
    struct { char igi2_o4[16]; int zTemp[4]; };
    struct { char igi2_o5[32]; char zStr[256]; };
    struct { char igi2_o6[288]; char zAdapter[256]; };
    char igi2_extent[544];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  DWORD PerformanceCounter; // eax
  struct Node_s *ptHead; // edi
  struct Node_s *ptNext; // eax
  bool v7; // zf
  void *Server; // esi
  DWORD TickCount; // eax
  DWORD v10; // ebp
  char *v11; // eax
  DWORD v12; // eax
  int v13; // edi
  struct Node_s *v14; // eax
  DWORD v15; // eax

  scprintf(zString, "%d.%d.%d.%d", igi2_frame.zTemp, &igi2_frame.zTemp[1], &igi2_frame.zTemp[2], &igi2_frame.zTemp[3]);
  igi2_frame.zIpAddress[1] = igi2_frame.zTemp[1];
  igi2_frame.zIpAddress[2] = igi2_frame.zTemp[2];
  igi2_frame.zIpAddress[0] = igi2_frame.zTemp[0];
  igi2_frame.nAdapter = 0;
  igi2_frame.isAnswered = false;
  igi2_frame.zIpAddress[3] = igi2_frame.zTemp[3];
  _snprintf(igi2_frame.zStr, 0xFFu, "Requesting %s:%d for server info...\n", zString, nPort);
  NetManager_LogMessage(igi2_frame.zStr);
  NetManager_tSessionList.ptTail = (struct Node_s *)&NetManager_tSessionList;
  NetManager_ptEnumerateGamesDestinationList = &NetManager_tSessionList;
  NetManager_nSelectedSession = -1;
  NetManager_iCurrentSession = 0;
  NetManager_tSessionList.ptHead = (struct Node_s *)&NetManager_tSessionList.ptMiddle;
  NetManager_tSessionList.ptMiddle = nullptr;
  NetManager_tSortedSessionList.ptHead = (struct Node_s *)&NetManager_tSortedSessionList.ptMiddle;
  NetManager_tSortedSessionList.ptTail = (struct Node_s *)&NetManager_tSortedSessionList;
  NetManager_tSortedSessionList.ptMiddle = nullptr;
  if ( !Flow_nSuspendRefCount )
  {
    if ( Timer_isPerformanceCounter )
      PerformanceCounter = Timer_GetPerformanceCounter();
    else
      PerformanceCounter = GetTickCount();
    Flow_nSuspendTime = PerformanceCounter - Timer_nStartTime;
  }
  ptHead = Network_tAdapterList.ptHead;
  ptNext = Network_tAdapterList.ptHead->ptNext;
  v7 = Network_tAdapterList.ptHead->ptNext == nullptr;
  ++Flow_nSuspendRefCount;
  igi2_frame.ptTemp = ptNext;
  if ( v7 )
  {
LABEL_27:
    NetManager_LogMessage("Client got no response from server\n");
  }
  else
  {
    while ( 1 )
    {
      Server = Network_FindServer(
                 (struct NetworkAdapterItem_s *)ptHead,
                 pfHandler__,
                 igi2_frame.zIpAddress,
                 nPort,
                 ServerConfig_tServerConfig.nMaxPlayers);
      if ( Timer_isPerformanceCounter )
        TickCount = Timer_GetPerformanceCounter();
      else
        TickCount = GetTickCount();
      v10 = TickCount - Timer_nStartTime;
      igi2_frame.isAnswered = false;
      if ( LOWORD(ptHead[1].ptNext) == 2 )
      {
        v11 = inet_ntoa((*(struct in_addr *)&ptHead[1].ptPrev->ptNext));
        _snprintf(igi2_frame.zAdapter, 0xFFu, "Trying local network interface [%d]: %s...\n", igi2_frame.nAdapter, v11);
        NetManager_LogMessage(igi2_frame.zAdapter);
      }
      else
      {
        NetManager_LogMessage("NetManager_FindSession: Socket of unknown type\n");
      }
LABEL_13:
      if ( Timer_isPerformanceCounter )
        v12 = Timer_GetPerformanceCounter();
      else
        v12 = GetTickCount();
      if ( (int)(v12 - Timer_nStartTime - v10) < nTimeOut )
      {
        Network_SendRequestInfo(Server);
        Sleep(0x64u);
        v13 = 0;
        while ( Network_RunEnumeration(Server) == false )
        {
          Sleep(0x14u);
          if ( ++v13 >= 30 )
          {
            Sleep(0xBB8u);
            goto LABEL_13;
          }
        }
        igi2_frame.isAnswered = true;
      }
      Network_StopEnumeration(Server);
      if ( igi2_frame.isAnswered )
        break;
      NetManager_LogMessage("Giving up on interface, closing socket\n");
      if ( Network_UDPSocket == -1 )
      {
        NetManager_LogMessage("Network_CloseUDPSocket: Socket was invalid\n");
      }
      else
      {
        closesocket(Network_UDPSocket);
        NetManager_LogMessage("Network_CloseUDPSocket: Socket closed\n");
      }
      Sleep(0xBB8u);
      ptHead = igi2_frame.ptTemp;
      v14 = igi2_frame.ptTemp->ptNext;
      v7 = igi2_frame.ptTemp->ptNext == nullptr;
      ++igi2_frame.nAdapter;
      igi2_frame.ptTemp = v14;
      if ( v7 )
        goto LABEL_27;
    }
    NetManager_LogMessage("Client got response from server\n");
  }
  if ( !--Flow_nSuspendRefCount )
  {
    if ( Timer_isPerformanceCounter )
      v15 = Timer_GetPerformanceCounter();
    else
      v15 = GetTickCount();
    Flow_ptFlow->nSkipTime += v15 - Timer_nStartTime - Flow_nSuspendTime;
    Flow_nSuspendTime = 0;
  }
  NetManager_ptEnumerateGamesDestinationList = nullptr;
  NetManager_iCurrentSession = 0;
  NetManager_nSelectedSession = 0;
  return igi2_frame.isAnswered;
}

// source: j/0/network/netmanager.c:2214  [anchor-strings]
void __cdecl NetManager_CopySelectedServerSettings()
{
  int *ptNetManagerQTask; // ebx
  int v1; // eax
  DWORD PerformanceCounter; // eax

  ptNetManagerQTask = (int *)Flow_ptFlow->ptNetManagerQTask;
  v1 = Timer_isPerformanceCounter;
  qmemcpy(ptNetManagerQTask + 11, (void *)(240 * NetManager_nSelectedSession + 7359180), 0xCCu);
  ptNetManagerQTask[66] = ptNetManagerQTask[56] + 150;
  if ( v1 )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  ptNetManagerQTask[67] = PerformanceCounter - Timer_nStartTime;
  NetManager_LogMessage("Initial clock synchronization\n");
  NetMission_EvaluateWarmUp(ptNetManagerQTask[47]);
}

// source: j/0/network/netmanager.c:2241  [anchor-mhash]
struct Result_s *__cdecl NetManager_FillTeamsCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  char **p_pzName; // esi
  struct Result_s Rs; // [esp+Ch] [ebp-18h] BYREF

  p_pzName = &NetManager_atTeams[0].pzName;
  do
  {
    ListBox_AddItem(*p_pzName, (int)*(p_pzName - 1));
    p_pzName += 2;
  }
  while ( (int)p_pzName < 7061368 );
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/netmanager.c:2262  [anchor-mhash]
struct Result_s *__cdecl NetManager_SetNameCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct Result_s Rs; };
    struct { char igi2_o1[24]; char zName[256]; };
    char igi2_extent[280];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Client_s *ClientFromNetworkID; // esi
  struct QTask_s *ptNetManagerQTask; // edi

  ClientFromNetworkID = NetManager_GetClientFromNetworkID((int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
  if ( ptArgList->isQVM )
  {
    igi2_frame.zName[0] = 0;
    QVM_EvalArg(igi2_frame.zName, 255, ptArgList, 0, 3);
  }
  else
  {
    Expression_EvalString(*ptArgList->aptExpression, igi2_frame.zName, 255);
  }
  if ( ClientFromNetworkID )
  {
    ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
    strncpy(ClientFromNetworkID->zPlayerName, igi2_frame.zName, 0x40u);
    *(_DWORD *)&ptNetManagerQTask[8].eQTaskType = 1;
  }
  strncpy(ClientConfig_tClientConfig.zPlayerName, igi2_frame.zName, 0x40u);
  igi2_frame.Rs.nResult = 0;
  igi2_frame.Rs.vResult = 0.0;
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/netmanager.c:2298  [size]
struct Result_s *__cdecl NetManager_GetNameCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct ClientConfig_s *v3; // eax
  int v4; // edx
  char v5; // cl
  struct Result_s Rs; // [esp+0h] [ebp-18h] BYREF

  v3 = &ClientConfig_tClientConfig;
  v4 = InputBox_ptActiveInputBox->zInputString - (char *)&ClientConfig_tClientConfig;
  do
  {
    v5 = v3->zPlayerName[0];
    v3->zPlayerName[v4] = v3->zPlayerName[0];
    v3 = (struct ClientConfig_s *)((char *)v3 + 1);
  }
  while ( v5 );
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/netmanager.c:2316  [anchor-strings]
struct Result_s *__cdecl NetManager_RequestTeamChangeCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct Result_s Rs; };
    struct { char igi2_o1[24]; char zTemp[256]; };
    char igi2_extent[280];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  unsigned int v3; // eax
  int v4; // esi

  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    if ( ptArgList )
    {
      if ( ptArgList->nArguments == 1 )
      {
        v3 = Script_EvalArgInt(ptArgList, 0);
        v4 = v3;
        if ( v3 < 2 || v3 == -1 )
        {
          _snprintf(igi2_frame.zTemp, 0xFFu, "NetManager_RequestTeamChangedCB: Called with valid arg=%d\n", v3);
          NetManager_LogMessage(igi2_frame.zTemp);
          NetManager_eRequestedTeam = v4;
        }
      }
    }
  }
  igi2_frame.Rs.nResult = 0;
  igi2_frame.Rs.vResult = 0.0;
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/netmanager.c:2348  [anchor-caller]
struct Result_s *__cdecl NetManager_SetTeamCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->isQVM )
  {
    ptArgList = nullptr;
    QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
    v4 = ptArgList;
  }
  else
  {
    v4 = (struct ArgList_s *)Expression_EvalInt(*ptArgList->aptExpression);
  }
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    NetManager_SetTeam((int)v4);
    NetManager_isModelSelect = true;
  }
  NetManager_nBodySprite = 0;
  NetManager_nFaceSprite = 0;
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/netmanager.c:2382  [size]
struct Result_s *__cdecl NetManager_GetTeamCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  Rs.nResult = NetManager_eTeam;
  Rs.vResult = (double)NetManager_eTeam;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/netmanager.c:2400  [anchor-mhash]
struct Result_s *__cdecl NetManager_SetModelCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // esi
  struct Client_s *ClientFromNetworkID; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->isQVM )
  {
    ptArgList = nullptr;
    QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
    v4 = ptArgList;
  }
  else
  {
    v4 = (struct ArgList_s *)Expression_EvalInt(*ptArgList->aptExpression);
  }
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    ClientFromNetworkID = NetManager_GetClientFromNetworkID((int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
    if ( ClientFromNetworkID )
    {
      ClientFromNetworkID->eModel = (int)v4;
      NetManager_eModel = (int)v4;
      NetManager_isModelSelect = false;
    }
  }
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/netmanager.c:2439  [anchor-strings]
struct Result_s *__cdecl NetManager_SetFaceCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // ebx
  struct QTask_s *ptMiddle; // edi
  struct Client_s *ClientFromNetworkID; // eax
  struct Client_s *v7; // esi
  int eTeam; // eax
  struct Human_s *v9; // ebp
  struct Result_s Rs; // [esp+Ch] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->isQVM )
  {
    ptArgList = nullptr;
    QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
    v4 = ptArgList;
  }
  else
  {
    v4 = (struct ArgList_s *)Expression_EvalInt(*ptArgList->aptExpression);
  }
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    ptMiddle = Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle;
    ptArgList = (struct ArgList_s *)Flow_ptFlow->ptNetManagerQTask;
    ClientFromNetworkID = NetManager_GetClientFromNetworkID((int)ptMiddle);
    v7 = ClientFromNetworkID;
    if ( ClientFromNetworkID )
    {
      eTeam = ClientFromNetworkID->eTeam;
      if ( eTeam != -1 )
      {
        v9 = *(struct Human_s **)(v7->tReceiveTimeBuffer.nCounter + 8);
        v7->eFace = (int)v4;
        NetManager_eFace = (int)v4;
        if ( eTeam == 1 )
          sprintf(v7->zModel, "%s%d_1", NetManager_atBadModel[NetManager_eModel].pzModel, v4);
        else
          sprintf(v7->zModel, "%s%d_1", NetManager_atGoodModel[NetManager_eModel].pzModel, v4);
        Human_SetTeam(v9, v7->eTeam, v7->zModel);
        ptArgList[29].aptExpression = (struct QExpression_s **)1;
      }
    }
  }
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/netmanager.c:2497  [anchor-strings]
struct Result_s *__cdecl NetManager_CollectBodyPicsCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct Result_s Rs; };
    struct { char igi2_o1[24]; char zFilename[256]; };
    char igi2_extent[280];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v3; // esi
  struct Client_s *ClientFromNetworkID; // eax
  int eTeam; // eax
  int v6; // eax
  int v7; // esi
  char *pzModel; // edx

  v3 = 0;
  ClientFromNetworkID = NetManager_GetClientFromNetworkID((int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
  if ( ClientFromNetworkID )
  {
    eTeam = ClientFromNetworkID->eTeam;
    if ( !eTeam )
      v3 = 3;
    if ( eTeam == 1 )
      v3 = 3;
    v6 = NetManager_nBodySprite;
    if ( NetManager_nBodySprite >= v3 )
    {
      v6 = 0;
      NetManager_nFaceSprite = 0;
    }
    v7 = v6;
    pzModel = NetManager_atGoodModel[v6].pzModel;
    NetManager_nBodySprite = v6 + 1;
    sprintf(igi2_frame.zFilename, "%s1_1%s", pzModel, "body.spr");
    PictureBox_AddItem(igi2_frame.zFilename, 0);
    sprintf(igi2_frame.zFilename, "%s1_1%s", NetManager_atBadModel[v7].pzModel, "body.spr");
    PictureBox_AddItem(igi2_frame.zFilename, 1);
  }
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  igi2_frame.Rs.vResult = 0.0;
  igi2_frame.Rs.nResult = 0;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/netmanager.c:2555  [anchor-strings]
struct Result_s *__cdecl NetManager_CollectFacePicsCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct Result_s Rs; };
    struct { char igi2_o1[24]; char zFilename[256]; };
    char igi2_extent[280];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v3; // ebp
  int i; // ebx
  int j; // ebx
  struct PictureBox_s *v6; // ecx
  int nPicture; // eax
  struct PictureBoxItem_s *v8; // esi
  int v9; // edx
  int v10; // edi
  int *p_nItemID; // eax
  char *v12; // eax
  int v13; // esi
  char v14; // dl

  v3 = ++NetManager_nFaceSprite;
  for ( i = 0; i < 3; ++i )
  {
    sprintf(igi2_frame.zFilename, "%s1_1%s%02d%s", NetManager_atGoodModel[i].pzModel, "face", v3, ".spr");
    PictureBox_AddItem(igi2_frame.zFilename, i);
  }
  for ( j = 0; j < 3; ++j )
  {
    sprintf(igi2_frame.zFilename, "%s1_1%s%02d%s", NetManager_atBadModel[j].pzModel, "face", v3, ".spr");
    v6 = PictureBox_ptActivePictureBox;
    nPicture = PictureBox_ptActivePictureBox->nPicture;
    v8 = &PictureBox_ptActivePictureBox->atPictureBoxItem[nPicture];
    v9 = 0;
    v10 = j + 3;
    if ( nPicture <= 0 )
    {
LABEL_8:
      v8->nItemID = v10;
      v12 = igi2_frame.zFilename;
      v13 = (char *)v8 - igi2_frame.zFilename;
      do
      {
        v14 = *v12;
        v12[v13] = *v12;
        ++v12;
      }
      while ( v14 );
      ++v6->nPicture;
    }
    else
    {
      p_nItemID = &PictureBox_ptActivePictureBox->atPictureBoxItem[0].nItemID;
      while ( *p_nItemID != v10 )
      {
        ++v9;
        p_nItemID += 18;
        if ( v9 >= PictureBox_ptActivePictureBox->nPicture )
          goto LABEL_8;
      }
    }
  }
  igi2_frame.Rs.nResult = 0;
  igi2_frame.Rs.vResult = 0.0;
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/netmanager.c:2586  [anchor-mhash]
struct Result_s *__cdecl NetManager_GetActiveBodyCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // esi
  struct Client_s *ClientFromNetworkID; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->isQVM )
  {
    ptArgList = nullptr;
    QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
    v4 = ptArgList;
  }
  else
  {
    v4 = (struct ArgList_s *)Expression_EvalInt(*ptArgList->aptExpression);
  }
  ClientFromNetworkID = NetManager_GetClientFromNetworkID((int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
  if ( !ClientFromNetworkID )
  {
    NetManager_LogMessage("NetManager_GetActiveBody called with no local client.\n");
LABEL_9:
    Rs.vResult = -1.0;
    Rs.nResult = -1;
    goto LABEL_10;
  }
  if ( NetManager_isModelSelect == false && v4 != (struct ArgList_s *)NetManager_eModel )
    goto LABEL_9;
  ptArgList = (struct ArgList_s *)ClientFromNetworkID->eTeam;
  Rs.nResult = (int)ptArgList;
  Rs.vResult = (double)(int)ptArgList;
LABEL_10:
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/netmanager.c:2623  [anchor-mhash]
struct Result_s *__cdecl NetManager_GetActiveFaceCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct Client_s *ClientFromNetworkID; // eax
  bool v4; // zf
  struct Result_s *result; // eax
  struct Result_s Rs; // [esp+Ch] [ebp-18h] BYREF

  ClientFromNetworkID = NetManager_GetClientFromNetworkID((int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
  if ( !ClientFromNetworkID )
  {
    NetManager_LogMessage("NetManager_GetActiveBody called with no local client.\n");
    goto LABEL_8;
  }
  if ( NetManager_isModelSelect )
  {
LABEL_8:
    Rs.zResult = (char *)&g_zInitialValue;
    Rs.vResult = -1.0;
    Rs.nResult = -1;
    qmemcpy(retstr, &Rs, sizeof(struct Result_s));
    return retstr;
  }
  v4 = ClientFromNetworkID->eTeam == 0;
  Rs.zResult = (char *)&g_zInitialValue;
  if ( v4 )
  {
    result = retstr;
    Rs.vResult = (double)NetManager_eModel;
    Rs.nResult = NetManager_eModel;
  }
  else
  {
    Rs.nResult = NetManager_eModel + 3;
    result = retstr;
    Rs.vResult = (double)(NetManager_eModel + 3);
  }
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return result;
}

// source: j/0/network/netmanager.c:2665  [size]
struct Result_s *__cdecl NetManager_IsModelSelectCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  Rs.nResult = NetManager_isModelSelect;
  Rs.vResult = (double)(int)NetManager_isModelSelect;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/netmanager.c:2678  [anchor-strings]
__declspec(noreturn) void NetManager_SessionLostCB()
{
  LDebug_Error("Session lost");
  abort();
}

// source: j/0/network/netmanager.c:2694  [anchor-hash]
struct NetManagerCounterSet_s *__cdecl NetManager_ClearPacketCounter(
        struct NetManagerCounterSet_s *ptCounterSet)
{
  struct NetManagerCounterSet_s *result; // eax
  int v2; // ecx

  result = (struct NetManagerCounterSet_s *)ptCounterSet->tCounters;
  v2 = 30;
  do
  {
    *(_DWORD *)&result->zName[4] = 0;
    *(_DWORD *)&result->zName[8] = 0;
    *(_DWORD *)result->zName = -1;
    result = (struct NetManagerCounterSet_s *)((char *)result + 12);
    --v2;
  }
  while ( v2 );
  return result;
}

// source: j/0/network/netmanager.c:2730  [anchor-caller]
void __cdecl NetManager_RunCountPacket(struct NetManagerCounterSet_s *ptCounterSet)
{
  DWORD PerformanceCounter; // eax
  struct NetManagerPacketCounter_s *tCounters; // eax
  int v3; // ecx

  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  if ( (signed int)(PerformanceCounter - Timer_nStartTime - ptCounterSet->nStartTime) > ptCounterSet->nPeriod )
  {
    NetManager_PrintCounter(ptCounterSet, (void (*)(char *, ...))NetManager_LogMessage);
    tCounters = ptCounterSet->tCounters;
    v3 = 30;
    do
    {
      tCounters->nCounter = 0;
      tCounters->nBytes = 0;
      tCounters->eGameMessage = -1;
      ++tCounters;
      --v3;
    }
    while ( v3 );
    if ( Timer_isPerformanceCounter )
      ptCounterSet->nStartTime = Timer_GetPerformanceCounter() - Timer_nStartTime;
    else
      ptCounterSet->nStartTime = GetTickCount() - Timer_nStartTime;
  }
}

// source: j/0/network/netmanager.c:2753  [anchor-strings]
int __cdecl NetManager_CountPacket(int a1, int a2, int a3)
{
  int result; // eax
  int v4; // edx
  int v5; // ecx

  result = a1 + 28;
  v4 = 0;
  while ( 1 )
  {
    if ( *(_DWORD *)result == a3 )
    {
      v5 = *(_DWORD *)(result + 8);
      ++*(_DWORD *)(result + 4);
      *(_DWORD *)(result + 8) = a2 + v5;
      return result;
    }
    if ( *(_DWORD *)result == -1 )
      break;
    result += 12;
    if ( ++v4 >= 30 )
    {
      LDebug_Error("No room for packet type in counters");
      abort();
    }
  }
  *(_DWORD *)(result + 4) = 1;
  *(_DWORD *)result = a3;
  *(_DWORD *)(result + 8) = a2;
  return result;
}

// source: j/0/network/netmanager.c:2802  [anchor-strings]
char *__cdecl NetManager_GetMinModem(float bps)
{
  char *result; // eax
  double v2; // st7
  float bpsa = *(float *)&bps; // [esp+4h] [ebp+4h] ARGSLOT

  if ( bps < 0.10000000149011612 )
    return "NO DATA  ";
  if ( bps < 300.0 )
    return "300 BAUD ";
  if ( bps < 9600.0 )
    return "9600 BAUD";
  if ( bps < 14400.0 )
    return "14.4k    ";
  if ( bps < 28800.0 )
    return "28.8k    ";
  if ( bps < 64000.0 )
    return "ISDN     ";
  if ( bps < 128000.0 )
    return "2xISDN   ";
  v2 = bps * 0.0009765625;
  bpsa = v2;
  if ( v2 < 256.0 )
    return "256k     ";
  if ( bpsa < 384.0 )
    return "384k     ";
  if ( bpsa < 512.0 )
    return "512k     ";
  if ( bpsa < 640.0 )
    return "640k     ";
  if ( bpsa < 768.0 )
    return "768k     ";
  if ( bpsa < 1024.0 )
    return "1Mb      ";
  if ( bpsa < 2048.0 )
    return "2Mb      ";
  result = "10Mb     ";
  if ( bpsa >= 10240.0 )
    return ">10Mb";
  return result;
}

// source: j/0/network/netmanager.c:2833  [anchor-hash]
struct Mission_s *__cdecl NetManager_GetCurrentMap()
{
  struct Mission_s *result; // eax
  struct Node_s *ptNext; // ecx

  result = (struct Mission_s *)Mission_tMissions.ptHead;
  ptNext = Mission_tMissions.ptHead->ptNext;
  if ( !Mission_tMissions.ptHead->ptNext )
    return nullptr;
  while ( result->iID != Game_iMissionID )
  {
    result = (struct Mission_s *)ptNext;
    ptNext = ptNext->ptNext;
    if ( !ptNext )
      return nullptr;
  }
  return result;
}

// source: j/0/network/netmanager.c:2860  [anchor-hash]
struct Mission_s *__cdecl NetManager_GetNextMap()
{
  struct Node_s *ptHead; // ecx
  struct Node_s *ptNext; // eax
  struct Node_s *v2; // edi
  struct Node_s *v3; // ecx
  struct Node_s *v4; // eax
  struct Node_s *v5; // esi
  struct Node_s *v6; // edx
  struct Node_s *v7; // edi
  struct Node_s *v8; // eax

  ptHead = Mission_tMissions.ptHead;
  ptNext = Mission_tMissions.ptHead->ptNext;
  if ( Mission_tMissions.ptHead->ptNext )
  {
    while ( ptHead[1].ptNext != (struct Node_s *)Game_iMissionID )
    {
      ptHead = ptNext;
      ptNext = ptNext->ptNext;
      if ( !ptNext )
        goto LABEL_4;
    }
    v2 = ptHead;
  }
  else
  {
LABEL_4:
    v2 = nullptr;
  }
  v3 = NetManager_tActiveMapList.ptHead;
  v4 = NetManager_tActiveMapList.ptHead->ptNext;
  v5 = nullptr;
  v6 = nullptr;
  if ( !NetManager_tActiveMapList.ptHead->ptNext )
    return (struct Mission_s *)v5[1].ptPrev;
  v7 = v2[1].ptNext;
  do
  {
    if ( !v5 )
      v5 = v3;
    if ( v3[1].ptNext == v7 )
      v6 = v3;
    v3 = v4;
    v4 = v4->ptNext;
  }
  while ( v4 );
  if ( v6 && (v8 = v6->ptNext, v6->ptNext->ptNext) && v8 )
    return (struct Mission_s *)v8[1].ptPrev;
  else
    return (struct Mission_s *)v5[1].ptPrev;
}

// source: j/0/network/netmanager.c:2930  [anchor-mhash]
enum bool __cdecl NetManager_isMapActive(int nMapID)
{
  struct Node_s *ptHead; // ecx
  struct Node_s *ptNext; // eax

  ptHead = NetManager_tActiveMapList.ptHead;
  ptNext = NetManager_tActiveMapList.ptHead->ptNext;
  if ( !NetManager_tActiveMapList.ptHead->ptNext )
    return false;
  while ( ptHead[1].ptNext != (struct Node_s *)nMapID )
  {
    ptHead = ptNext;
    ptNext = ptNext->ptNext;
    if ( !ptNext )
      return false;
  }
  return true;
}

// source: j/0/network/netmanager.c:2970  [anchor-hash]
enum bool __cdecl NetManager_SetMapActive(int iID)
{
  struct Node_s *ptHead; // ecx
  struct Node_s *ptNext; // eax
  struct Node_s *v3; // ecx
  struct Node_s *v4; // eax
  _DWORD *v6; // eax
  struct Node_s *v7; // edx
  struct Node_s *v8; // ecx

  ptHead = NetManager_tActiveMapList.ptHead;
  ptNext = NetManager_tActiveMapList.ptHead->ptNext;
  if ( NetManager_tActiveMapList.ptHead->ptNext )
  {
    while ( ptHead[1].ptNext != (struct Node_s *)iID )
    {
      ptHead = ptNext;
      ptNext = ptNext->ptNext;
      if ( !ptNext )
        goto LABEL_4;
    }
    return false;
  }
LABEL_4:
  v3 = Mission_tMissions.ptHead;
  v4 = Mission_tMissions.ptHead->ptNext;
  if ( !Mission_tMissions.ptHead->ptNext )
    return false;
  while ( v3[1].ptNext != (struct Node_s *)iID )
  {
    v3 = v4;
    v4 = v4->ptNext;
    if ( !v4 )
      return false;
  }
  v6 = Mem_AllocFn(16, 4);
  v6[1] = 0;
  *v6 = 0;
  v6[2] = iID;
  v7 = Mission_tMissions.ptHead;
  v8 = Mission_tMissions.ptHead->ptNext;
  if ( Mission_tMissions.ptHead->ptNext )
  {
    while ( v7[1].ptNext != (struct Node_s *)iID )
    {
      v7 = v8;
      v8 = v8->ptNext;
      if ( !v8 )
        goto LABEL_11;
    }
  }
  else
  {
LABEL_11:
    v7 = nullptr;
  }
  v6[3] = v7;
  List_AddTail(v6, (int)&NetManager_tActiveMapList);
  return true;
}

// source: j/0/network/netmanager.c:3009  [anchor-hash]
enum bool __cdecl NetManager_SetMapInactive(int iID)
{
  struct Node_s *ptNext; // ecx
  struct Node_s *v3; // eax
  struct Node_s *ptHead; // edx
  struct Node_s *v6; // eax
  int v7; // esi

  ptNext = NetManager_tActiveMapList.ptHead->ptNext;
  v3 = NetManager_tActiveMapList.ptHead->ptNext;
  ptHead = NetManager_tActiveMapList.ptHead;
  if ( !NetManager_tActiveMapList.ptHead->ptNext )
    return false;
  while ( ptHead[1].ptNext != (struct Node_s *)iID )
  {
    ptHead = v3;
    v3 = v3->ptNext;
    if ( !v3 )
      return false;
  }
  v6 = NetManager_tActiveMapList.ptHead;
  if ( !ptNext )
    return false;
  while ( v6[1].ptNext != (struct Node_s *)iID )
  {
    v6 = ptNext;
    ptNext = ptNext->ptNext;
    if ( !ptNext )
      return false;
  }
  v7 = *(_DWORD *)((unsigned int)(Node_Remove(v6) - 1) & 0xFFFFFFFC);
  --Mem_nCurrentAllocations;
  Node_Remove((_DWORD **)v7);
  memset(*(void **)(v7 + 8), 0xCDu, *(_DWORD *)(v7 + 16));
  free((void *)v7);
  return true;
}

// source: j/0/network/netmanager.c:3053  [anchor-strings]
struct Result_s *__cdecl NetManager_SetMapActiveCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  int v3; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
  {
    if ( ptArgList && ptArgList->nArguments == 1 )
    {
      v3 = Script_EvalArgInt(ptArgList, 0);
      if ( NetManager_SetMapActive(v3) )
        NetworkCommand_SetEvalResponse("Map added to list");
      else
        NetworkCommand_SetEvalResponse("Map already active or does not exist");
    }
    else
    {
      DebugConsole_printf("NetManager_SetMapActiveCB: Invalid parameters\n");
    }
  }
  else
  {
    NetworkCommand_SetEvalResponse("Available to local only");
  }
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/netmanager.c:3094  [anchor-strings]
struct Result_s *__cdecl NetManager_SetMapInActiveCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  int v3; // eax
  struct Result_s Rs; // [esp+0h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
  {
    if ( ptArgList && ptArgList->nArguments == 1 )
    {
      v3 = Script_EvalArgInt(ptArgList, 0);
      if ( NetManager_SetMapInactive(v3) )
        NetworkCommand_SetEvalResponse("Map removed from list");
      else
        NetworkCommand_SetEvalResponse("Map already inactive");
    }
    else
    {
      DebugConsole_printf("NetManager_SetMapInActiveCB: Invalid parameters\n");
    }
  }
  else
  {
    NetworkCommand_SetEvalResponse("Available to local only");
  }
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/netmanager.c:3135  [anchor-mhash]
void __cdecl NetManager_WriteActiveMaps(struct File_s *ptFile, char *zProperty)
{
  struct Node_s *ptHead; // eax
  struct Node_s *i; // esi
  unsigned int v4; // eax
  char zBuffer[256]; // [esp+4h] [ebp-100h] BYREF

  ptHead = NetManager_tActiveMapList.ptHead;
  for ( i = NetManager_tActiveMapList.ptHead->ptNext; i; i = i->ptNext )
  {
    v4 = sprintf(zBuffer, "lo %s %d\r\n", zProperty, ptHead[1].ptNext);
    File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, zBuffer, v4);
    ptHead = i;
  }
}

// source: j/0/network/netmanager.c:3169  [anchor-strings]
void __cdecl NetManager_PrintCounter(struct NetManagerCounterSet_s *ptCounterSet, void (*pfPrint)(char *, ...))
{
  #pragma pack(push, 1)
  union
  {
    struct { int nTotalBytes; };
    struct { float nTotalBytesa; };
    struct { char igi2_o2[4]; float nTotalCount; };
    struct { char igi2_o3[8]; int nTimePassed; };
    struct { char igi2_o4[12]; char zTemp[256]; };
    char igi2_extent[268];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  DWORD PerformanceCounter; // eax
  int v3; // ebx
  int v4; // edi
  struct NetManagerPacketCounter_s *tCounters; // esi
  int nCounter; // eax
  double v7; // st7
  double v8; // st6
  double v9; // st5
  char *MinModem; // eax

  _snprintf(igi2_frame.zTemp, 0xFFu, "-----%s-----\r\n", ptCounterSet->zName);
  pfPrint(igi2_frame.zTemp);
  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  igi2_frame.nTimePassed = PerformanceCounter - Timer_nStartTime - ptCounterSet->nStartTime;
  if ( igi2_frame.nTimePassed > 0 )
  {
    v3 = 0;
    v4 = 0;
    tCounters = ptCounterSet->tCounters;
    igi2_frame.nTotalBytes = 30;
    do
    {
      nCounter = tCounters->nCounter;
      if ( nCounter > 0 )
      {
        _snprintf(
          igi2_frame.zTemp,
          0xFFu,
          "[%c%c%c%c] count=%4d, #bytes=%6d\r\n",
          SHIBYTE(tCounters->eGameMessage),
          SBYTE2(tCounters->eGameMessage),
          SBYTE1(tCounters->eGameMessage),
          SLOBYTE(tCounters->eGameMessage),
          nCounter,
          tCounters->nBytes);
        pfPrint(igi2_frame.zTemp);
        v4 += tCounters->nCounter;
        v3 += tCounters->nBytes;
      }
      ++tCounters;
      --igi2_frame.nTotalBytes;
    }
    while ( igi2_frame.nTotalBytes );
    if ( v4 <= 0 )
    {
      _snprintf(igi2_frame.zTemp, 0xFFu, "NO DATA IN COUNTERS\r\n");
      pfPrint(igi2_frame.zTemp);
    }
    else
    {
      v7 = (double)v3;
      v8 = (double)igi2_frame.nTimePassed;
      igi2_frame.nTotalBytesa = v7 * 8000.0 / v8;
      v9 = (double)v4;
      igi2_frame.nTotalCount = v9;
      _snprintf(
        igi2_frame.zTemp,
        0xFFu,
        "MESSAGES  [#%d] [ave.size %3.1f ] [%3.1f /sec]\r\n",
        v4,
        v7 / igi2_frame.nTotalCount,
        v9 * 1000.0 / v8);
      pfPrint(igi2_frame.zTemp);
      MinModem = NetManager_GetMinModem(igi2_frame.nTotalBytesa);
      _snprintf(
        igi2_frame.zTemp,
        0xFFu,
        "DATA      [#Bytes %d] [%s] [%.1f kbits/sec] [%.1f Bps]\r\n",
        v3,
        MinModem,
        igi2_frame.nTotalBytesa * 0.0010000000474974513,
        igi2_frame.nTotalBytesa * 0.125);
      pfPrint(igi2_frame.zTemp);
    }
    _snprintf(
      igi2_frame.zTemp,
      0xFFu,
      "Period: %3.0f s. Time to reset: (%2.0f/100)\r\n",
      (double)ptCounterSet->nPeriod * 0.0010000000474974513,
      (double)igi2_frame.nTimePassed * 100.0 / (double)ptCounterSet->nPeriod);
    pfPrint(igi2_frame.zTemp);
  }
  _snprintf(igi2_frame.zTemp, 0xFFu, "\r\n");
  pfPrint(igi2_frame.zTemp);
}

// source: j/0/network/netmanager.c:3263  [anchor-callee]
enum bool __cdecl NetManager_CheckNonGuaranteed(
        int nPacketID,
        int nLastPacketID,
        struct NetManager_s *ptNetManager,
        struct Client_s *ptLocalClient)
{
  int v5; // ecx

  if ( nLastPacketID == -1 )
    return true;
  if ( nPacketID == nLastPacketID + 1 )
    return true;
  if ( nPacketID - 1 > nLastPacketID )
  {
    if ( ptLocalClient )
      ptLocalClient->tStats.nReceivedExpiredPacks += nPacketID - nLastPacketID - 1;
    ptNetManager->aBufferState[2] += nPacketID - nLastPacketID - 1;
    return true;
  }
  if ( nPacketID >= nLastPacketID )
  {
    if ( ptLocalClient )
      ++ptLocalClient->tStats.nSentBytes;
    ++ptNetManager->aBufferState[3];
    return false;
  }
  else
  {
    if ( ptLocalClient )
    {
      v5 = ptLocalClient->tStats.nReceivedExpiredPacks - 1;
      ++ptLocalClient->tStats.nReceivedBytes;
      ptLocalClient->tStats.nReceivedExpiredPacks = v5 <= 0 ? 0 : v5;
    }
    ++ptNetManager->aBufferState[4];
    return true;
  }
}

// source: j/0/network/netmanager.c:3329  [anchor-strings]
void __cdecl NetManager_TriggerReceiveHandlers(struct NetManagerPacket_t *ptPacket, int nSize)
{
  struct QTask_s *ptNetManagerQTask; // esi
  struct Node_s *ptHead; // edi
  struct Node_s *ptNext; // eax
  void (__cdecl *pfHandler)(struct QTask_s *, struct NetManagerPacketReceiveContext_s *); // eax
  int v6; // ecx
  int v7; // edx
  struct QTask_s *v8; // eax
  void (__cdecl *v9)(int, struct NetManagerPacketReceiveContext_s *); // eax
  int v10; // edx
  struct NetManagerPacketReceiveContext_s tContext; // [esp+Ch] [ebp-10h] BYREF

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  ptHead = result_7086a8.ptHead;
  ptNext = result_7086a8.ptHead->ptNext;
  if ( result_7086a8.ptHead->ptNext )
  {
    while ( ptHead[1].ptNext != *(struct Node_s **)ptPacket->anPacketData )
    {
      ptHead = ptNext;
      ptNext = ptNext->ptNext;
      if ( !ptNext )
        goto LABEL_4;
    }
    tContext.eFrom = ptPacket->tInfo.eSource;
    tContext.eTo = (int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle;
    tContext.nDataSize = nSize;
    tContext.ptPacket = ptPacket;
    pfHandler = (void (__cdecl *)(struct QTask_s *, struct NetManagerPacketReceiveContext_s *))QTask_aatQTaskFinalEvent[SLOWORD(ptHead[1].ptPrev)][ptNetManagerQTask->eQTaskType].pfHandler;
    if ( pfHandler )
      pfHandler(ptNetManagerQTask, &tContext);
    v6 = (int)ptNetManagerQTask->tQTaskChildren.ptHead;
    if ( *(_DWORD *)v6 && v6 )
    {
      v7 = QTask_nProtectedQTaskStackOffset;
      do
      {
        if ( *(_DWORD *)v6 )
          v8 = **(_DWORD **)v6 != 0 ? *(struct QTask_s **)v6 : nullptr;
        else
          v8 = nullptr;
        QTask_atProtectedQTaskStack[v7].ptQTask = v8;
        v9 = (void (__cdecl *)(int, struct NetManagerPacketReceiveContext_s *))QTask_aatQTaskFinalEvent[SLOWORD(ptHead[1].ptPrev)][*(unsigned __int16 *)(v6 + 36)].pfHandler;
        v10 = v7 + 1;
        QTask_nProtectedQTaskStackOffset = v10;
        if ( v9 )
        {
          v9(v6, &tContext);
          v10 = QTask_nProtectedQTaskStackOffset;
        }
        v6 = dword_849C7DC[v10];
        v7 = v10 - 1;
        QTask_nProtectedQTaskStackOffset = v7;
      }
      while ( v6 );
    }
  }
  else
  {
LABEL_4:
    NetManager_LogMessage("Unknown message type received\n");
  }
}

// source: j/0/network/netmanager.c:3376  [anchor-callee]
enum bool __cdecl NetManager_IsShouldBufferPacket(int eLocal, unsigned int eMessage, enum bool isGuaranteed)
{
  struct QTask_s *ptNetManagerQTask; // esi
  char zType[8]; // [esp+4h] [ebp-8h] BYREF

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  _snprintf(zType, 5u, "%c%c%c%c", (int)eMessage >> 24, SBYTE2(eMessage), SBYTE1(eMessage), (char)eMessage);
  return isGuaranteed || ptNetManagerQTask[36].ptPrev;
}

// source: j/0/network/netmanager.c:3415  [anchor-callee]
enum bool __cdecl NetManager_IsShouldAlwaysTrigger(
        int eLocal,
        unsigned int eMessage,
        enum bool isGuaranteed)
{
  char zType[8]; // [esp+8h] [ebp-8h] BYREF

  if ( isGuaranteed || !Flow_ptFlow->ptNetManagerQTask[36].ptPrev )
    return false;
  _snprintf(zType, 5u, "%c%c%c%c", (int)eMessage >> 24, SBYTE2(eMessage), SBYTE1(eMessage), (char)eMessage);
  return !strcmp(zType, "HNUP")
      || !strcmp(zType, "ZNUP")
      || !strcmp(zType, "PING")
      || !strcmp(zType, "PONG")
      || !strcmp(zType, "STAT")
      || strcmp(zType, "UPGR") == 0;
}

// source: j/0/network/netmanager.c:3480  [anchor-caller]
void __cdecl NetManager_TriggerReceiveQueue()
{
  struct QObjectVector_s *ptMiddle; // ebx
  void **papxElement; // edx
  int v2; // ebp
  struct NetManagerPacket_t tPacket; // [esp+10h] [ebp-2000h] BYREF

  ptMiddle = (struct QObjectVector_s *)Flow_ptFlow->ptNetManagerQTask[31].tQTaskChildren.ptMiddle;
  while ( ptMiddle->nAllocated )
  {
    if ( *((_DWORD *)&Flow_ptFlow->ptNetManagerQTask[31].tQTaskChildren.ptTail
         + (int)Flow_ptFlow->ptNetManagerQTask[32].tQTaskChildren.ptTail) )
      break;
    papxElement = (void **)ptMiddle->papxElement;
    v2 = *((_DWORD *)*papxElement + 2048);
    qmemcpy(&tPacket, *papxElement, sizeof(tPacket));
    QObjectVector_RemoveElement(ptMiddle, 0);
    NetManager_TriggerReceiveHandlers(&tPacket, v2);
    NetManager_RegisterInput(tPacket.tInfo.eSource);
  }
}

// source: j/0/network/netmanager.c:3534  [anchor-strings]
struct NetworkMessageContext_s *__cdecl NetManager_HandleReceivedPacket(
        struct NetworkMessageContext_s *ptContext,
        enum bool isGuaranteed)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct NetManagerPacket_t *ptPacket; };
    struct { char igi2_o1[4]; struct QTask_s *v15; };
    struct { char igi2_o2[8]; struct Client_s *ptLocalClient; };
    struct { char igi2_o3[12]; struct QObjectVector_s *ptQObjectVector; };
    struct { char igi2_o4[16]; char Buffer[8]; };
    struct { char igi2_o5[24]; char zFormat[256]; };
    char igi2_extent[280];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct NetManagerPacket_t *pxNetworkPacketContents; // ebx
  struct QTask_s *ptNetManagerQTask; // ebp
  int eSource; // esi
  struct Client_s *ClientFromNetworkID; // edi
  int nPacketID; // ecx
  struct NetworkMessageContext_s *result; // eax
  int v8; // edx
  struct Flow_t *v9; // ecx
  int v10; // edx
  struct QTask_s *v11; // eax
  unsigned int nAllocated; // eax
  struct NetManagerPacket_t *v13; // edx

  pxNetworkPacketContents = (struct NetManagerPacket_t *)ptContext->pxNetworkPacketContents;
  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  igi2_frame.ptQObjectVector = (struct QObjectVector_s *)ptNetManagerQTask[31].tQTaskChildren.ptMiddle;
  igi2_frame.ptPacket = (struct NetManagerPacket_t *)ptContext->nPacketContentsSize;
  NetManager_CountPacket(
    (int)&ptNetManagerQTask[9].tQTaskRefList.ptTail,
    (int)&igi2_frame.ptPacket->anPacketData[44],
    *(_DWORD *)pxNetworkPacketContents->anPacketData);
  igi2_frame.ptLocalClient = NetManager_GetClientFromNetworkID((int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
  _snprintf(
    igi2_frame.Buffer,
    5u,
    "%c%c%c%c",
    (char)HIBYTE(*(_DWORD *)pxNetworkPacketContents->anPacketData),
    (char)BYTE2(*(_DWORD *)pxNetworkPacketContents->anPacketData),
    (char)BYTE1(*(_DWORD *)pxNetworkPacketContents->anPacketData),
    (char)*(_DWORD *)pxNetworkPacketContents->anPacketData);
  eSource = pxNetworkPacketContents->tInfo.eSource;
  ClientFromNetworkID = NetManager_GetClientFromNetworkID(pxNetworkPacketContents->tInfo.eSource);
  if ( !ClientFromNetworkID && eSource )
  {
    _snprintf(igi2_frame.zFormat, 0xFFu, "Received [%s] from unknown source[%d]\n", igi2_frame.Buffer, eSource);
    NetManager_LogMessage(igi2_frame.zFormat);
  }
  if ( isGuaranteed == false )
  {
    nPacketID = pxNetworkPacketContents->tInfo.nPacketID;
    igi2_frame.v15 = (struct QTask_s *)nPacketID;
    if ( ClientFromNetworkID )
    {
      result = (struct NetworkMessageContext_s *)NetManager_CheckNonGuaranteed(
                                                   nPacketID,
                                                   ClientFromNetworkID->nLastPacketID,
                                                   (struct NetManager_s *)ptNetManagerQTask,
                                                   igi2_frame.ptLocalClient);
      if ( !result )
        return result;
      if ( (int)igi2_frame.v15 > ClientFromNetworkID->nLastPacketID )
        ClientFromNetworkID->nLastPacketID = (int)igi2_frame.v15;
    }
    else if ( pxNetworkPacketContents->tInfo.eSource )
    {
      _snprintf(
        igi2_frame.zFormat,
        0xFFu,
        "Received non-guaranteed message[%s] from unknown client: %d\n",
        igi2_frame.Buffer,
        pxNetworkPacketContents->tInfo.eSource);
      NetManager_LogMessage(igi2_frame.zFormat);
    }
    else
    {
      result = (struct NetworkMessageContext_s *)NetManager_CheckNonGuaranteed(
                                                   nPacketID,
                                                   (int)ptNetManagerQTask[31].tQTaskChildren.ptHead,
                                                   (struct NetManager_s *)ptNetManagerQTask,
                                                   igi2_frame.ptLocalClient);
      if ( !result )
        return result;
      if ( (int)igi2_frame.v15 > (int)ptNetManagerQTask[31].tQTaskChildren.ptHead )
        ptNetManagerQTask[31].tQTaskChildren.ptHead = igi2_frame.v15;
    }
  }
  if ( igi2_frame.ptLocalClient )
  {
    v8 = (int)&igi2_frame.ptPacket->anPacketData[igi2_frame.ptLocalClient->tStats.nDeaths + 44];
    ++igi2_frame.ptLocalClient->tStats.nReceivedOutOfOrderPacks;
    igi2_frame.ptLocalClient->tStats.nDeaths = v8;
  }
  v9 = Flow_ptFlow;
  v10 = (int)&igi2_frame.ptPacket->anPacketData[(unsigned int)ptNetManagerQTask[30].tQTaskRefList.ptMiddle + 44];
  ++*(int *)&ptNetManagerQTask[30].ptNext;
  ptNetManagerQTask[30].tQTaskRefList.ptMiddle = (struct QReference_s *)v10;
  v11 = v9->ptNetManagerQTask;
  if ( (*((_DWORD *)&v11[31].tQTaskChildren.ptTail + (int)v11[32].tQTaskChildren.ptTail) || igi2_frame.ptQObjectVector->nAllocated)
    && NetManager_IsShouldAlwaysTrigger(
         (int)v11[6].tQTaskChildren.ptMiddle,
         *(_DWORD *)pxNetworkPacketContents->anPacketData,
         isGuaranteed) == false )
  {
    if ( NetManager_IsShouldBufferPacket(
           (int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle,
           *(_DWORD *)pxNetworkPacketContents->anPacketData,
           isGuaranteed) )
    {
      if ( igi2_frame.ptQObjectVector->nAllocated == igi2_frame.ptQObjectVector->nSize )
        QObjectVector_Realloc(igi2_frame.ptQObjectVector, igi2_frame.ptQObjectVector->nReallocSize);
      nAllocated = igi2_frame.ptQObjectVector->nAllocated;
      v13 = (struct NetManagerPacket_t *)igi2_frame.ptQObjectVector->papxElement[nAllocated];
      igi2_frame.ptQObjectVector->nAllocated = nAllocated + 1;
      qmemcpy(v13, pxNetworkPacketContents, sizeof(struct NetManagerPacket_t));
      v13[1].tInfo.eSource = (int)igi2_frame.ptPacket;
    }
  }
  else
  {
    NetManager_TriggerReceiveHandlers(pxNetworkPacketContents, (int)igi2_frame.ptPacket);
  }
  NetManager_TriggerReceiveQueue();
  return result;
}

// source: j/0/network/netmanager.c:3714  [anchor-strings]
enum bool __cdecl NetManager_IsClientMapCorrect(
        enum NetworkMessage_e eNetworkMessage,
        struct NetworkMessageContext_s *ptContext)
{
  struct QTask_s *ptNetManagerQTask; // esi
  _DWORD *pxNetworkPacketContents; // edi
  char zTemp[256]; // [esp+8h] [ebp-100h] BYREF

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  pxNetworkPacketContents = ptContext->pxNetworkPacketContents;
  _snprintf(
    zTemp,
    0xFFu,
    "IsClientMapCorrect: Client %d Server %d\n",
    *pxNetworkPacketContents,
    ptNetManagerQTask[3].ptNext);
  NetManager_LogMessage(zTemp);
  return ptNetManagerQTask[3].ptNext == (struct QTask_s *)*pxNetworkPacketContents;
}

// source: j/0/network/netmanager.c:3757  [anchor-strings]
enum bool __cdecl NetManager_IsPasswordCorrect(
        enum NetworkMessage_e eNetworkMessage,
        struct NetworkMessageContext_s *ptContext)
{
  if ( !ServerConfig_tServerConfig.zServerPassword[0] )
    return true;
  if ( !strncmp(ServerConfig_tServerConfig.zServerPassword, (char *)ptContext->pxNetworkPacketContents + 4, 8u) )
  {
    NetManager_LogMessage("IsPasswordCorrect: Identical to 8 chars: OK\n");
    return true;
  }
  NetManager_LogMessage((char *)&g_ptClient.anDR[33]);
  return false;
}

// source: j/0/network/netmanager.c:3815  [anchor-hash]
enum bool __cdecl NetManager_IsConnectionJustSetup(struct sockaddr_in *ptSocket)
{
  struct NetworkIDListItem_s *IDItemFromAddr; // eax
  int eID; // eax

  IDItemFromAddr = Network_GetIDItemFromAddr(ptSocket);
  if ( !IDItemFromAddr )
    return false;
  eID = IDItemFromAddr->eID;
  return eID != -1 && NetManager_GetClientFromNetworkID(eID) == nullptr;
}

// source: j/0/network/netmanager.c:3857  [anchor-hash]
enum bool __cdecl NetManager_IsSocketInUse(struct sockaddr_in *ptSocket)
{
  struct NetworkIDListItem_s *IDItemFromAddr; // eax
  int eID; // eax
  char zTemp[256]; // [esp+0h] [ebp-100h] BYREF

  IDItemFromAddr = Network_GetIDItemFromAddr(ptSocket);
  if ( !IDItemFromAddr )
    return false;
  eID = IDItemFromAddr->eID;
  if ( eID == -1 )
    return false;
  _snprintf(zTemp, 0xFFu, (char *const)&g_ptClient.anDR[15], eID);
  NetManager_LogMessage(zTemp);
  return true;
}

// source: j/0/network/netmanager.c:3890  [anchor-strings]
int __cdecl NetManager_ServerHandler(
        void *pxHandlerContext,
        enum NetworkMessage_e eNetworkMessage,
        struct NetworkMessageContext_s *ptContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { unsigned __int8 nIP[4]; };
    struct { char igi2_o1[4]; struct sockaddr_in ptSocket; };
    struct { char igi2_o2[60]; char zText[256]; };
    struct { char igi2_o3[316]; char zFormat[256]; };
    char igi2_extent[572];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int result; // eax

  switch ( eNetworkMessage )
  {
    case NETWORKMESSAGE_SERVER_CONNECTIONREQUEST:
      Network_SetSocketData(&ptContext->tSockAddr, igi2_frame.nIP, &igi2_frame.ptSocket.sin_family);
      _snprintf(
        (char *const)&igi2_frame.ptSocket.sin_addr,
        0x32u,
        (char *const)&g_ptClient.anDR[9],
        igi2_frame.nIP[0],
        igi2_frame.nIP[1],
        igi2_frame.nIP[2],
        igi2_frame.nIP[3],
        igi2_frame.ptSocket.sin_family);
      if ( NetManager_IsConnectionJustSetup(&ptContext->tSockAddr) )
      {
        _snprintf(igi2_frame.zFormat, 0xFFu, (char *const)g_ptClient.anDR, &igi2_frame.ptSocket.sin_addr);
        NetManager_LogMessage(igi2_frame.zFormat);
        result = 7;
      }
      else if ( NetManager_IsSocketInUse(&ptContext->tSockAddr) )
      {
        Config_SetLocalizedPhrase(
          igi2_frame.zText,
          (char *)&g_ptClient.tReceiveTimeBuffer.aReceiveTime[1],
          (char *)&igi2_frame.ptSocket.sin_addr,
          nullptr,
          nullptr);
        StatusScreen_ShowMessage(igi2_frame.zText, TEXTSCROLLER_COLOUR_WHITE);
        result = 6;
      }
      else
      {
        if ( NetManager_IsPasswordCorrect(NETWORKMESSAGE_SERVER_CONNECTIONREQUEST, ptContext) == false )
        {
          Config_SetLocalizedPhrase(
            igi2_frame.zText,
            (char *)&g_ptClient.tDownload.nLastLoDown,
            (char *)&igi2_frame.ptSocket.sin_addr,
            nullptr,
            nullptr);
          StatusScreen_ShowMessage(igi2_frame.zText, TEXTSCROLLER_COLOUR_WHITE);
          goto LABEL_8;
        }
        if ( Network_IsBanned(igi2_frame.nIP) )
        {
          Config_SetLocalizedPhrase(
            igi2_frame.zText,
            (char *)&g_ptClient.isSpectateFirstPerson,
            (char *)&igi2_frame.ptSocket.sin_addr,
            nullptr,
            nullptr);
          StatusScreen_ShowMessage(igi2_frame.zText, TEXTSCROLLER_COLOUR_WHITE);
          result = 2;
        }
        else if ( SBYTE1(Flow_ptFlow->ptNetManagerQTask[3].ptPrev) < SBYTE2(Flow_ptFlow->ptNetManagerQTask[3].ptPrev) )
        {
          if ( NetManager_IsClientMapCorrect(NETWORKMESSAGE_SERVER_CONNECTIONREQUEST, ptContext) )
          {
            Config_SetLocalizedPhrase(
              igi2_frame.zText,
              &g_ptClient.zTalkString[228],
              (char *)&igi2_frame.ptSocket.sin_addr,
              nullptr,
              nullptr);
            StatusScreen_ShowMessage(igi2_frame.zText, TEXTSCROLLER_COLOUR_WHITE);
            result = 0;
          }
          else
          {
            Config_SetLocalizedPhrase(
              igi2_frame.zText,
              &g_ptClient.zTalkString[248],
              (char *)&igi2_frame.ptSocket.sin_addr,
              nullptr,
              nullptr);
            StatusScreen_ShowMessage(igi2_frame.zText, TEXTSCROLLER_COLOUR_WHITE);
            result = 4;
          }
        }
        else
        {
          Config_SetLocalizedPhrase(
            igi2_frame.zText,
            (char *)&g_ptClient.nWarnConnection,
            (char *)&igi2_frame.ptSocket.sin_addr,
            nullptr,
            nullptr);
          StatusScreen_ShowMessage(igi2_frame.zText, TEXTSCROLLER_COLOUR_WHITE);
          result = 3;
        }
      }
      break;
    case NETWORKMESSAGE_SERVER_INFOREQUEST:
LABEL_8:
      result = 1;
      break;
    case NETWORKMESSAGE_RECEIVEDDATA:
      NetManager_HandleReceivedPacket(ptContext, false);
      result = 0;
      break;
    case NETWORKMESSAGE_RECEIVEDGUARANTEEDDATA:
      NetManager_HandleReceivedPacket(ptContext, true);
      goto LABEL_18;
    default:
LABEL_18:
      result = 0;
      break;
  }
  return result;
}

// source: j/0/network/netmanager.c:3990  [anchor-strings]
int __cdecl NetManager_ClientHandler(
        void *pxHandlerContext,
        enum NetworkMessage_e eNetworkMessage,
        struct NetworkMessageContext_s *ptContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s *ptTail; };
    struct { char igi2_o1[4]; int v19; };
    struct { char igi2_o2[8]; float v20; };
    struct { char igi2_o3[12]; struct QTask_s *v21; };
    struct { char igi2_o4[16]; struct QTask_s ptParent; };
    struct { char igi2_o5[56]; int v23; };
    struct { char igi2_o6[60]; _DWORD v24[28]; };
    struct { char igi2_o7[172]; struct NetManagerGameMessage_s ptGameMessage; };
    struct { char igi2_o8[180]; int v26; };
    struct { char igi2_o9[184]; int v27; };
    struct { char igi2_o10[196]; int v28; };
    struct { char igi2_o11[200]; _DWORD v29[27]; };
    struct { char igi2_o12[308]; char v30; };
    struct { char igi2_o13[309]; char v31; };
    struct { char igi2_o14[312]; int nBandwidth; };
    struct { char igi2_o15[316]; char Destination[64]; };
    struct { char igi2_o16[380]; char Buffer[16]; };
    struct { char igi2_o17[396]; char zFormat[256]; };
    char igi2_extent[652];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptNetManagerQTask; // edi
  void *pxNetworkPacketContents; // ebp
  int FairTeam; // esi
  char *pzName; // ecx
  int i; // eax
  struct QTask_s *v8; // edi
  struct QTask_s *v9; // edi
  struct QTask_s *ptHead; // esi
  struct QTask_s *ptPrev; // eax
  enum WeaponCategory_e v12; // edi
  struct QTask_s *ptNext; // esi
  struct WeaponType_s *NextEnabledWeaponTypeFromCategory; // eax
  struct WeaponType_s *v15; // ebx
  struct WeaponTypeItem_s *WeaponTypeItemFromWeaponType; // eax

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  switch ( eNetworkMessage )
  {
    case NETWORKMESSAGE_CLIENT_CONNECTIONSUCCESS:
      if ( ptNetManagerQTask[6].tQTaskChildren.ptMiddle != (struct QTask_s *)-1 )
      {
        _snprintf(
          igi2_frame.zFormat,
          0xFFu,
          &g_ptClient.zTalkString[84],
          Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
        return 0;
      }
      pxNetworkPacketContents = ptContext->pxNetworkPacketContents;
      FairTeam = TeamManager_GetFairTeam(-1);
      Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle = *((struct QTask_s **)pxNetworkPacketContents + 2);
      igi2_frame.v19 = FairTeam;
      ptNetManagerQTask[6].tQTaskRefList.ptMiddle = (struct QReference_s *)(*((_DWORD *)pxNetworkPacketContents + 1)
                                                                          + 150);
      ptNetManagerQTask[6].tQTaskRefList.ptTail = (struct QReference_s *)Timer_Read();
      pzName = NetManager_atTeams[FairTeam].pzName;
      igi2_frame.ptParent.ptPrev = *((struct QTask_s **)pxNetworkPacketContents + 2);
      igi2_frame.ptParent.tQTaskRefList.ptHead = (struct QReference_s *)pzName;
      igi2_frame.ptParent.ptNext = (struct QTask_s *)1;
      LOWORD(igi2_frame.ptParent.tQTaskChildren.ptMiddle) = 1;
      igi2_frame.ptParent.tQTaskChildren.ptTail = (struct QTask_s *)&ClientConfig_tClientConfig;
      igi2_frame.ptParent.tQTaskChildren.ptHead = (struct QTask_s *)FairTeam;
      igi2_frame.v23 = -1;
      igi2_frame.v24[27] = ClientConfig_tClientConfig.nBandwidth;
      for ( i = 0; i < 13; ++i )
      {
        igi2_frame.v24[i] = -1;
        igi2_frame.v24[i + 13] = 0;
      }
      igi2_frame.v20 = tan(0.7853981852531433);
      *(float *)&igi2_frame.v24[26] = igi2_frame.v20;
      NetManager_GetTeamModelName(
        (char *)&igi2_frame.ptParent.tQTaskRefList.ptMiddle,
        FairTeam,
        NetManager_eModel,
        NetManager_eFace);
      v8 = Flow_ptFlow->ptNetManagerQTask;
      ++BYTE1(v8[3].ptPrev);
      v9 = QTask_NewFn(v8, Client_eQTaskType, &igi2_frame.ptParent);
      NetManager_SetTeam(FairTeam);
      NetManager_SetLocalBandwidth(ClientConfig_tClientConfig.nBandwidth);
      if ( !v9 )
      {
        NetManager_LogMessage(&g_ptClient.zTalkString[160]);
        return 0;
      }
      ptHead = v9[16].tQTaskChildren.ptHead->tQTaskChildren.ptHead;
      ptPrev = ptHead[33].ptNext[1].ptPrev;
      igi2_frame.v21 = ptHead;
      if ( ptPrev )
        igi2_frame.ptTail = ptPrev->tQTaskChildren.ptTail;
      else
        igi2_frame.ptTail = nullptr;
      _snprintf(igi2_frame.zFormat, 0xFFu, &g_ptClient.zTalkString[192], v9[1].ptNext);
      NetManager_LogMessage(igi2_frame.zFormat);
      igi2_frame.ptGameMessage.eGameMessage = 1129467980;
      igi2_frame.ptGameMessage.nLocalTime = NetManager_GetTimer();
      igi2_frame.nBandwidth = ClientConfig_tClientConfig.nBandwidth;
      igi2_frame.v26 = *((_DWORD *)pxNetworkPacketContents + 2);
      igi2_frame.v27 = igi2_frame.v19;
      v12 = WEAPONCATEGORY_NONE;
      break;
    case NETWORKMESSAGE_CLIENT_CONNECTIONFAILED:
      NetManager_LogMessage(&g_ptClient.zTalkString[12]);
      return 0;
    case NETWORKMESSAGE_CLIENT_SERVERINFO:
      NetManager_LogMessage((char *)&g_ptClient.tStats.nLostPacks);
      return 0;
    case NETWORKMESSAGE_LOSTCONNECTION:
      NetManager_LogMessage(&g_ptClient.zModel[12]);
      return 0;
    case NETWORKMESSAGE_RECEIVEDDATA:
      if ( ptNetManagerQTask[6].tQTaskChildren.ptMiddle == (struct QTask_s *)-1 )
        return 0;
      NetManager_HandleReceivedPacket(ptContext, false);
      return 0;
    case NETWORKMESSAGE_RECEIVEDGUARANTEEDDATA:
      if ( ptNetManagerQTask[6].tQTaskChildren.ptMiddle == (struct QTask_s *)-1 )
        return 0;
      NetManager_HandleReceivedPacket(ptContext, true);
      return 0;
    default:
      NetManager_LogMessage(&g_ptClient.zTeamName[32]);
      return 0;
  }
  while ( 1 )
  {
    ptNext = ptHead[33].ptNext;
    NextEnabledWeaponTypeFromCategory = Weapon_GetNextEnabledWeaponTypeFromCategory(ptNext, v12, nullptr);
    v15 = NextEnabledWeaponTypeFromCategory;
    if ( NextEnabledWeaponTypeFromCategory )
    {
      WeaponTypeItemFromWeaponType = Weapon_GetWeaponTypeItemFromWeaponType(
                                       ptNext,
                                       NextEnabledWeaponTypeFromCategory->zWeaponScriptID);
      igi2_frame.v29[v12] = v15->eID;
      if ( WeaponTypeItemFromWeaponType )
      {
        igi2_frame.v29[v12 + 13] = WeaponTypeItemFromWeaponType->iActiveFireMode;
        goto LABEL_16;
      }
    }
    else
    {
      igi2_frame.v29[v12] = -1;
    }
    igi2_frame.v29[v12 + 13] = 0;
LABEL_16:
    if ( ++v12 >= WEAPONCATEGORIES )
      break;
    ptHead = igi2_frame.v21;
  }
  if ( igi2_frame.ptTail )
    igi2_frame.v28 = (int)igi2_frame.ptTail[3].tQTaskRefList.ptTail;
  else
    igi2_frame.v28 = -1;
  *(float *)&igi2_frame.v29[26] = igi2_frame.v20;
  if ( igi2_frame.v19 )
  {
    if ( igi2_frame.v19 == 1 )
      sprintf(igi2_frame.Buffer, "%s%d_1", NetManager_atBadModel[NetManager_eModel].pzModel, NetManager_eFace);
  }
  else
  {
    sprintf(igi2_frame.Buffer, "%s%d_1", NetManager_atGoodModel[NetManager_eModel].pzModel, NetManager_eFace);
  }
  strncpy(igi2_frame.Destination, ClientConfig_tClientConfig.zPlayerName, 0x40u);
  igi2_frame.v30 = 1;
  igi2_frame.v31 = 1;
  NetManager_SendGameMessage(
    0,
    (int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle,
    NETWORKQUEUE_GUARANTEED,
    &igi2_frame.ptGameMessage,
    0xE0u);
  return 0;
}

int __cdecl pfHandler__(void *a1, enum NetworkMessage_e a2, struct NetworkMessageContext_s *a3)
{
  int v3; // eax
  _WORD *pxNetworkPacketContents; // ecx
  int v5; // ebx
  struct List_s *v6; // ecx

  v3 = NetManager_iCurrentSession;
  pxNetworkPacketContents = a3->pxNetworkPacketContents;
  if ( NetManager_iCurrentSession < 64 )
  {
    v5 = 240 * NetManager_iCurrentSession++ + 7359144;
    *((struct sockaddr_in *)&unk_704ABC + 15 * v3) = a3->tSockAddr;
    if ( *pxNetworkPacketContents == 204 )
    {
      qmemcpy((void *)(v5 + 36), pxNetworkPacketContents + 1, 0xCCu);
      v6 = NetManager_ptEnumerateGamesDestinationList;
      *(_DWORD *)(v5 + 4) = 0;
      *(_DWORD *)v5 = 0;
      List_AddTail((_DWORD *)v5, (int)v6);
      return 0;
    }
    NetManager_LogMessage(&g_ptClient.zPlayerName[24]);
    strncpy((char *)(v5 + 100), &g_ptClient.zPlayerName[12], 0xAu);
    *(_BYTE *)(v5 + 36) = 0;
  }
  return 0;
}

// source: j/0/network/netmanager.c:4325  [anchor-mhash]
void __cdecl NetManager_ClearRunTimers()
{
  struct QTask_s *ptNetManagerQTask; // edx

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  ptNetManagerQTask[29].ptPrev = (struct QTask_s *)-1;
  ptNetManagerQTask[29].tQTaskChildren.ptHead = (struct QTask_s *)-1;
  memset(&ptNetManagerQTask[32].tQTaskRefList, 0xFFu, 0x78u);
  ptNetManagerQTask[35].tQTaskRefList.ptHead = nullptr;
}

// source: j/0/network/netmanager.c:4356  [anchor-callee]
float __cdecl NetManager_GetAverageRunDelta()
{
  struct QTask_s *ptNetManagerQTask; // eax
  struct QReference_s *ptHead; // ecx
  int v2; // edx
  struct QTask_s *ptTail; // eax

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  ptHead = ptNetManagerQTask[35].tQTaskRefList.ptHead;
  v2 = *((_DWORD *)&ptNetManagerQTask[32].tQTaskRefList.ptHead + (_DWORD)ptHead);
  if ( ptHead )
    ptTail = *(&ptNetManagerQTask[32].tQTaskChildren.ptTail + (_DWORD)ptHead);
  else
    ptTail = ptNetManagerQTask[35].tQTaskChildren.ptTail;
  if ( ptTail == (struct QTask_s *)-1 || v2 == -1 )
    return -1.0;
  else
    return (double)((int)ptTail - v2) * 0.03448275849223137;
}

// source: j/0/network/netmanager.c:4395  [anchor-strings]
void __cdecl NetManager_LogTimeAndVersion()
{
  #pragma pack(push, 1)
  union
  {
    struct { int ltime; };
    struct { char igi2_o1[4]; char zTemp[256]; };
    char igi2_extent[260];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct tm *v0; // eax
  char *v1; // eax

  time(&igi2_frame.ltime);
  v0 = gmtime(&igi2_frame.ltime);
  v1 = asctime(v0);
  _snprintf(igi2_frame.zTemp, 0xFFu, (char *const)&g_ptClient.eVotedKickID, g_zPlayer1, v1);
  NetManager_LogMessage(igi2_frame.zTemp);
}

// source: j/0/network/netmanager.c:4424  [anchor-callee]
enum bool __cdecl NetManager_IsLocalRoundPlayedFor(struct NetManager_s *ptNetManager, int nPlayTime)
{
  DWORD PerformanceCounter; // eax

  if ( !*(_DWORD *)&ptNetManager->tReceiveCounters.zName[4] )
    return false;
  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  return (int)(PerformanceCounter - Timer_nStartTime - ptNetManager->tReceiveCounters.tCounters[1].nCounter) > nPlayTime;
}

// source: j/0/network/netmanager.c:4447  [anchor-strings]
void __cdecl NetManager_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v2; // edi
  struct QObjectVector_s *v3; // esi
  int v4; // eax
  DWORD PerformanceCounter; // eax
  unsigned __int16 v6; // ax
  struct QTask_s **p_ptTail; // eax
  int v8; // ecx
  struct QTask_s **p_ptPrev; // eax
  int v10; // ecx
  unsigned __int16 v11; // ax
  _DWORD *v12; // eax
  int v13; // ebp
  struct Node_s *ptHead; // edx
  struct Node_s *ptNext; // ecx
  int v16; // eax
  struct QReferenceList_s *p_tQTaskRefList; // ecx
  unsigned __int16 v18; // ax

  v2 = ptQTask;
  ptQTask[36].ptPrev = nullptr;
  NetManager_LogTimeAndVersion();
  Network_StartSockLib();
  v3 = (struct QObjectVector_s *)Mem_AllocFn(52, 4);
  v3->nSize = 0;
  v3->nAllocated = 0;
  v3->papxElement = nullptr;
  v3->tMemPool.nBlocks = 0;
  v3->tMemPool.nAllocatedBlocks = 0;
  v3->tMemPool.tMemPoolFreeList.ptHead = nullptr;
  v3->tMemPool.tMemPoolSegmentList.ptHead = nullptr;
  v3->isStrictOrder = true;
  v3->nReallocSize = 3;
  v3->nElementSize = 8200;
  v3->tMemPool.nAlignment = 4;
  v3->tMemPool.nBlockSize = 8200;
  v3->tMemPool.nReAllocBlocks = 3;
  MemPool_ReAlloc(&v3->tMemPool, 0xAu);
  QObjectVector_Realloc(v3, 0xAu);
  v4 = Timer_isPerformanceCounter;
  v2[31].tQTaskChildren.ptMiddle = (struct QTask_s *)v3;
  v2[36].ptNext = nullptr;
  v2[6].tQTaskChildren.ptMiddle = (struct QTask_s *)-1;
  v2[6].tQTaskChildren.ptTail = (struct QTask_s *)-1;
  v2[32].tQTaskChildren.ptTail = (struct QTask_s *)-1;
  if ( v4 )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  v2[9].tQTaskChildren.ptMiddle = (struct QTask_s *)(PerformanceCounter - Timer_nStartTime);
  v6 = MapControl_eQTaskType;
  v2[8].tQTaskRefList.ptMiddle = nullptr;
  v2[9].tQTaskRefList.ptMiddle = (struct QReference_s *)-1;
  QTask_NewFn(v2, v6, &ptQTask);
  Network_ClearNetworkStats();
  p_ptTail = &v2[10].tQTaskChildren.ptTail;
  v8 = 30;
  do
  {
    p_ptTail[1] = nullptr;
    p_ptTail[2] = nullptr;
    *p_ptTail = (struct QTask_s *)-1;
    p_ptTail += 3;
    --v8;
  }
  while ( v8 );
  strncpy((char *)&v2[9].tQTaskRefList.ptTail, (char *)&g_ptClient.eModel, 0x14u);
  v2[10].tQTaskChildren.ptMiddle = (struct QTask_s *)100000;
  v2[10].tQTaskChildren.ptHead = nullptr;
  v2[31].ptPrev = nullptr;
  v2[35].tQTaskRefList.ptTail = nullptr;
  v2[35].ptParent = nullptr;
  *(_DWORD *)&v2[35].eQTaskType = 0;
  v2[8].tQTaskRefList.ptHead = nullptr;
  v2[7].tQTaskChildren.ptHead = nullptr;
  v2[7].tQTaskChildren.ptMiddle = nullptr;
  p_ptPrev = &v2[20].ptPrev;
  v10 = 30;
  do
  {
    p_ptPrev[1] = nullptr;
    p_ptPrev[2] = nullptr;
    *p_ptPrev = (struct QTask_s *)-1;
    p_ptPrev += 3;
    --v10;
  }
  while ( v10 );
  strncpy((char *)&v2[19].tQTaskChildren.ptTail, (char *)&g_ptClient.nCreateTime, 0x14u);
  v11 = NetworkGameItem_eQTaskType;
  v2[20].ptNext = (struct QTask_s *)100000;
  *(_DWORD *)&v2[19].eQTaskType = 0;
  v2[6].tQTaskRefList.ptHead = (struct QReference_s *)QTask_NewFn(v2, v11, nullptr);
  v2[1].ptNext = nullptr;
  v2[6].tQTaskChildren.ptHead = nullptr;
  BYTE1(v2[3].ptPrev) = 0;
  BYTE2(v2[3].tQTaskChildren.ptHead) = 0;
  v2[31].tQTaskChildren.ptHead = (struct QTask_s *)-1;
  if ( AppContext_tAppContext.isDrawingDisabled || AppContext_tAppContext.isServer )
  {
    v12 = Mem_AllocFn(16, 4);
    v13 = Game_iMissionID;
    v12[1] = 0;
    *v12 = 0;
    v12[2] = v13;
    ptHead = Mission_tMissions.ptHead;
    ptNext = Mission_tMissions.ptHead->ptNext;
    if ( Mission_tMissions.ptHead->ptNext )
    {
      while ( ptHead[1].ptNext != (struct Node_s *)v13 )
      {
        ptHead = ptNext;
        ptNext = ptNext->ptNext;
        if ( !ptNext )
          goto LABEL_13;
      }
    }
    else
    {
LABEL_13:
      ptHead = nullptr;
    }
    v12[3] = ptHead;
    List_AddTail(v12, (int)&NetManager_tActiveMapList);
  }
  QTask_NewFn(v2, RadioCom_eQTaskType, &ptQTask);
  QTask_NewFn(v2, Netshop_eQTaskType, &ptQTask);
  QTask_NewFn(v2, TeamManager_eQTaskType, &ptQTask);
  v2[8].ptParent = nullptr;
  v2[8].tQTaskRefList.ptTail = nullptr;
  *(_DWORD *)&v2[8].eQTaskType = 0;
  v2[9].ptNext = (struct QTask_s *)1;
  v2[9].tQTaskChildren.ptTail = nullptr;
  v2[9].tQTaskRefList.ptHead = (struct QReference_s *)-1;
  v2[31].tQTaskChildren.ptHead = (struct QTask_s *)-1;
  v2[9].ptPrev = nullptr;
  v16 = 0;
  p_tQTaskRefList = &v2[3].tQTaskRefList;
  do
  {
    *((_BYTE *)&v2[3].tQTaskChildren.ptHead + v16 + 3) = -1;
    p_tQTaskRefList->ptHead = (struct QReference_s *)-1;
    ++v16;
    p_tQTaskRefList = (struct QReferenceList_s *)((char *)p_tQTaskRefList + 4);
  }
  while ( v16 < 8 );
  v2[35].tQTaskRefList.ptMiddle = nullptr;
  v2[36].tQTaskChildren.ptHead = nullptr;
  v2[7].tQTaskRefList.ptHead = nullptr;
  v2[7].tQTaskRefList.ptMiddle = nullptr;
  v2[7].tQTaskRefList.ptTail = nullptr;
  v2[7].ptParent = nullptr;
  *(_DWORD *)&v2[7].eQTaskType = 0;
  v18 = SpyBrowser_eQTaskType;
  v2[7].tQTaskChildren.ptTail = nullptr;
  QTask_NewFn(v2, v18, nullptr);
  QTaskList_Register(Flow_ptDrawInterpolateQTaskList, (struct QTaskList_s *)v2);
}

// source: j/0/network/netmanager.c:4570  [anchor-hash]
int __cdecl NetManager_GetServerPort()
{
  int result; // eax

  result = AppContext_tAppContext.nPort;
  if ( AppContext_tAppContext.nPort <= 0 )
    return ServerConfig_tServerConfig.nPort;
  return result;
}

// source: j/0/network/netmanager.c:4593  [size]
enum bool __cdecl NetManager_isConnected()
{
  return (enum bool)Flow_ptFlow->ptNetManagerQTask[9].tQTaskChildren.ptTail;
}

// source: j/0/network/netmanager.c:4612  [anchor-callee]
void __cdecl NetManager_DistributeStats()
{
  unsigned int v0; // esi
  DWORD PerformanceCounter; // eax
  struct NetManagerGameMessage_s *v2; // eax
  struct Flow_t *v3; // edx
  struct NetManagerGameMessage_s *v4; // ebx
  bool v5; // zf
  struct QTask_s *ptNetManagerQTask; // edi
  DWORD TickCount; // eax
  unsigned __int16 v8; // dx
  int *i; // ebp
  struct QTask_s *v10; // eax
  struct QTask_s *v11; // esi
  struct QTask_s *v12; // eax
  int v13; // esi
  struct QTask_s *v14; // [esp+10h] [ebp-Ch]
  struct QTask_s *ptQTask; // [esp+14h] [ebp-8h]
  enum NetworkQueue_e eQueue; // [esp+18h] [ebp-4h]

  v0 = SBYTE1(Flow_ptFlow->ptNetManagerQTask[3].ptPrev);
  ptQTask = nullptr;
  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  v14 = (struct QTask_s *)(PerformanceCounter - Timer_nStartTime);
  eQueue = 72 * v0 + 12;
  v2 = (struct NetManagerGameMessage_s *)Mem_AllocFn(eQueue, 4);
  v3 = Flow_ptFlow;
  v4 = v2;
  v5 = Timer_isPerformanceCounter == 0;
  v2->eGameMessage = 1398030676;
  ptNetManagerQTask = v3->ptNetManagerQTask;
  if ( v5 )
    TickCount = GetTickCount();
  else
    TickCount = Timer_GetPerformanceCounter();
  v8 = Client_eQTaskType;
  v4->nLocalTime = TickCount
                 - Timer_nStartTime
                 + (char *)ptNetManagerQTask[6].tQTaskRefList.ptMiddle
                 - (char *)ptNetManagerQTask[6].tQTaskRefList.ptTail;
  v4[1].eGameMessage = v0;
  for ( i = &v4[1].nLocalTime; ; i += 18 )
  {
    v10 = ptQTask
        ? QTask_GetNextSiblingOfType(ptQTask, v8)
        : QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, v8);
    ptQTask = v10;
    if ( !v10 )
      break;
    qmemcpy(i, &v10[6].tQTaskRefList, 0x48u);
  }
  v11 = nullptr;
  while ( 1 )
  {
    v12 = v11 ? QTask_GetNextSiblingOfType(v11, v8) : QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, v8);
    v11 = v12;
    if ( !v12 )
      break;
    if ( (char *)v14 - (char *)v12[15].ptPrev > 8000 )
    {
      NetManager_SendGameMessage((int)v12[1].ptNext, 0, NETWORKQUEUE_MEDIUMPRIORITY, v4, eQueue);
      v8 = Client_eQTaskType;
      v11[15].ptPrev = v14;
    }
  }
  v13 = *(_DWORD *)((unsigned int)&v4[-1].nLocalTime & 0xFFFFFFFC);
  --Mem_nCurrentAllocations;
  Node_Remove((_DWORD **)v13);
  memset(*(void **)(v13 + 8), 0xCDu, *(_DWORD *)(v13 + 16));
  free((void *)v13);
}

// source: j/0/network/netmanager.c:4676  [anchor-callee]
void __cdecl NetManager_UpdateStats(struct NetManager_s *ptNetManager)
{
  struct Client_s *ClientFromNetworkID; // edi
  struct NetManagerGameMessage_s *v2; // eax
  struct Flow_t *v3; // edx
  struct NetManagerGameMessage_s *v4; // ebx
  bool v5; // zf
  struct QTask_s *ptNetManagerQTask; // esi
  DWORD TickCount; // eax
  struct Flow_t *v8; // edx
  int v9; // esi

  ClientFromNetworkID = NetManager_GetClientFromNetworkID((int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
  if ( ClientFromNetworkID )
  {
    v2 = (struct NetManagerGameMessage_s *)Mem_AllocFn(84, 4);
    v3 = Flow_ptFlow;
    v4 = v2;
    v5 = Timer_isPerformanceCounter == 0;
    v2->eGameMessage = 1398030676;
    ptNetManagerQTask = v3->ptNetManagerQTask;
    if ( v5 )
      TickCount = GetTickCount();
    else
      TickCount = Timer_GetPerformanceCounter();
    v8 = Flow_ptFlow;
    v4->nLocalTime = TickCount
                   - Timer_nStartTime
                   + (char *)ptNetManagerQTask[6].tQTaskRefList.ptMiddle
                   - (char *)ptNetManagerQTask[6].tQTaskRefList.ptTail;
    v4[1].eGameMessage = 1;
    qmemcpy(&v4[1].nLocalTime, &ClientFromNetworkID->tStats, 0x48u);
    NetManager_SendGameMessage(
      0,
      (int)v8->ptNetManagerQTask[6].tQTaskChildren.ptMiddle,
      NETWORKQUEUE_MEDIUMPRIORITY,
      v4,
      0x54u);
    v9 = *(_DWORD *)((unsigned int)&v4[-1].nLocalTime & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v9);
    memset(*(void **)(v9 + 8), 0xCDu, *(_DWORD *)(v9 + 16));
    free((void *)v9);
  }
}

// source: j/0/network/netmanager.c:4717  [anchor-callee]
void __cdecl NetManager_UpdateSpawnCamera()
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[20]; struct real32x9_t tOrientation; };
    struct { char igi2_o2[60]; struct real32x9_t tOffset; };
    struct { char igi2_o3[100]; struct real32x9_t Real32x9_Multiply_tTemp; };
    struct { char igi2_o4[140]; struct real64x3_t tPos; };
    char igi2_extent[164];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v0; // ebx
  struct QTask_s *v1; // ebp
  double v2; // st7
  double v3; // st7
  double v4; // st7
  struct QReference_s *ptHumanCameraQTaskRef; // eax
  struct QTask_s *pxObject; // eax
  struct QTask_s *ptTail; // eax
  struct QTask_s *v8; // eax

  v0 = HumanPlayer_ptQTask;
  v1 = HumanPlayer_ptQTask;
  if ( HumanPlayer_ptQTask && SpawnArea_ptActive )
  {
    v2 = InputPort_atInputPort[0].tInput.vAnalogY * 0.5;
    qmemcpy(&igi2_frame.tOrientation, &SpawnArea_ptActive[4].tQTaskChildren.ptTail, sizeof(igi2_frame.tOrientation));
    if ( Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tInputOptions.isInvertMouse )
      v3 = NetManager_vSpawnCamOffsetAlpha - v2;
    else
      v3 = v2 + NetManager_vSpawnCamOffsetAlpha;
    if ( v3 >= -0.9424778819084167 )
    {
      if ( v3 <= 0.9424778819084167 )
        NetManager_vSpawnCamOffsetAlpha = v3;
      else
        NetManager_vSpawnCamOffsetAlpha = 0.9424778819084167;
    }
    else
    {
      NetManager_vSpawnCamOffsetAlpha = -0.9424778819084167;
    }
    v4 = NetManager_vSpawnCamOffsetGamma - InputPort_atInputPort[0].tInput.vAnalogX * 0.5;
    if ( v4 >= -0.9424778819084167 )
    {
      if ( v4 <= 0.9424778819084167 )
        NetManager_vSpawnCamOffsetGamma = v4;
      else
        NetManager_vSpawnCamOffsetGamma = 0.9424778819084167;
    }
    else
    {
      NetManager_vSpawnCamOffsetGamma = -0.9424778819084167;
    }
    qmemcpy(&igi2_frame.tPos, &SpawnArea_ptActive[2].ptParent, sizeof(igi2_frame.tPos));
    Real32x9_Create(&igi2_frame.tOffset, NetManager_vSpawnCamOffsetAlpha, 0.0, 0.0);
    igi2_frame.Real32x9_Multiply_tTemp.tX.vX = igi2_frame.tOffset.tZ.vX * igi2_frame.tOrientation.tX.vZ
                                  + igi2_frame.tOffset.tY.vX * igi2_frame.tOrientation.tX.vY
                                  + igi2_frame.tOffset.tX.vX * igi2_frame.tOrientation.tX.vX;
    igi2_frame.Real32x9_Multiply_tTemp.tX.vY = igi2_frame.tOffset.tZ.vY * igi2_frame.tOrientation.tX.vZ
                                  + igi2_frame.tOffset.tY.vY * igi2_frame.tOrientation.tX.vY
                                  + igi2_frame.tOffset.tX.vY * igi2_frame.tOrientation.tX.vX;
    igi2_frame.Real32x9_Multiply_tTemp.tX.vZ = igi2_frame.tOffset.tZ.vZ * igi2_frame.tOrientation.tX.vZ
                                  + igi2_frame.tOffset.tY.vZ * igi2_frame.tOrientation.tX.vY
                                  + igi2_frame.tOffset.tX.vZ * igi2_frame.tOrientation.tX.vX;
    igi2_frame.Real32x9_Multiply_tTemp.tY.vX = igi2_frame.tOrientation.tY.vZ * igi2_frame.tOffset.tZ.vX
                                  + igi2_frame.tOrientation.tY.vY * igi2_frame.tOffset.tY.vX
                                  + igi2_frame.tOrientation.tY.vX * igi2_frame.tOffset.tX.vX;
    igi2_frame.Real32x9_Multiply_tTemp.tY.vY = igi2_frame.tOrientation.tY.vZ * igi2_frame.tOffset.tZ.vY
                                  + igi2_frame.tOrientation.tY.vY * igi2_frame.tOffset.tY.vY
                                  + igi2_frame.tOrientation.tY.vX * igi2_frame.tOffset.tX.vY;
    igi2_frame.Real32x9_Multiply_tTemp.tY.vZ = igi2_frame.tOrientation.tY.vZ * igi2_frame.tOffset.tZ.vZ
                                  + igi2_frame.tOrientation.tY.vY * igi2_frame.tOffset.tY.vZ
                                  + igi2_frame.tOrientation.tY.vX * igi2_frame.tOffset.tX.vZ;
    igi2_frame.Real32x9_Multiply_tTemp.tZ.vX = igi2_frame.tOrientation.tZ.vZ * igi2_frame.tOffset.tZ.vX
                                  + igi2_frame.tOrientation.tZ.vY * igi2_frame.tOffset.tY.vX
                                  + igi2_frame.tOrientation.tZ.vX * igi2_frame.tOffset.tX.vX;
    igi2_frame.Real32x9_Multiply_tTemp.nOps = igi2_frame.tOffset.nOps + igi2_frame.tOrientation.nOps + 1;
    igi2_frame.Real32x9_Multiply_tTemp.tZ.vY = igi2_frame.tOrientation.tZ.vZ * igi2_frame.tOffset.tZ.vY
                                  + igi2_frame.tOrientation.tZ.vY * igi2_frame.tOffset.tY.vY
                                  + igi2_frame.tOrientation.tZ.vX * igi2_frame.tOffset.tX.vY;
    igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ = igi2_frame.tOrientation.tZ.vZ * igi2_frame.tOffset.tZ.vZ
                                  + igi2_frame.tOrientation.tZ.vY * igi2_frame.tOffset.tY.vZ
                                  + igi2_frame.tOrientation.tZ.vX * igi2_frame.tOffset.tX.vZ;
    qmemcpy(&igi2_frame.tOrientation, &igi2_frame.Real32x9_Multiply_tTemp, sizeof(igi2_frame.tOrientation));
    Real32x9_Rotate(&igi2_frame.tOrientation, &igi2_frame.tOrientation, 0.0, 0.0, NetManager_vSpawnCamOffsetGamma);
    ptHumanCameraQTaskRef = Game_ptGame->ptHumanCameraQTaskRef;
    if ( ptHumanCameraQTaskRef )
      pxObject = (struct QTask_s *)ptHumanCameraQTaskRef->pxObject;
    else
      pxObject = nullptr;
    HumanCamera_SetHumanQTask(pxObject, v0);
    ptTail = v0[33].tQTaskChildren.ptTail;
    BYTE2(ptTail[12].tQTaskRefList.ptTail) = 1;
    qmemcpy(&ptTail[12].ptParent, &igi2_frame.tPos, 0x18u);
    qmemcpy(&ptTail[13].tQTaskChildren.ptTail, &igi2_frame.tOrientation, sizeof(struct QTask_s));
    v8 = v0[33].tQTaskChildren.ptTail;
    v8[16].tQTaskRefList.ptMiddle = nullptr;
    *(float *)&v8[16].tQTaskChildren.ptHead = tan(0.7853981852531433);
    *(float *)&v8[16].tQTaskRefList.ptHead = tan(0.5235987901687622);
    LOBYTE(v8) = v0[80].tQTaskChildren.ptTail;
    v1[33].tQTaskRefList.ptHead = (struct QReference_s *)4;
    if ( !(_BYTE)v8 )
    {
      igi2_frame.ptDynCubeObj = BoneDynCubeObj_GetRadius((struct BoneDynCubeObj_s *)v0);
      World_MoveDynCubeObjRadius(Game_ptGame->ptWorld, (struct DynCubeObj_s *)v0, &igi2_frame.tPos, igi2_frame.ptDynCubeObj);
    }
  }
}

// source: j/0/network/netmanager.c:4782  [anchor-callee]
struct QTask_s *__cdecl NetManager_GetNextObjectiveSpawn(
        struct NetManager_s *ptNetManager,
        struct Client_s *ptLocalClient,
        struct NetObjective_t *ptCurrentSpawnObjective,
        enum bool isReverse)
{
  int nNumber; // eax
  int v5; // esi
  struct NetObjective_t *v6; // eax
  struct NetObjective_t *v8; // eax
  struct NetObjective_t *Objective; // eax
  struct NetObjective_t *v10; // eax
  struct NetObjective_t *v11; // eax
  struct NetObjective_t *v12; // eax

  nNumber = ptCurrentSpawnObjective->nNumber;
  v5 = NetMission_eCurrentObjective;
  if ( nNumber >= NetMission_eCurrentObjective
    && ptLocalClient->eTeam != NetMission_eDefendingTeam
    && isReverse == false )
  {
    goto LABEL_4;
  }
  if ( nNumber == 1 )
  {
    if ( isReverse == false )
    {
      Objective = NetMission_GetObjective(2);
      return QTask_GetFirstChildOfType(&Objective->tQTask, SpawnArea_eQTaskType);
    }
    if ( ptLocalClient->eTeam == NetMission_eDefendingTeam )
    {
      v8 = NetMission_GetObjective(3);
      return QTask_GetLastChildOfType(&v8->tQTask, SpawnArea_eQTaskType);
    }
    goto LABEL_15;
  }
  if ( nNumber == 3 )
  {
    if ( isReverse == false )
    {
LABEL_4:
      v6 = NetMission_GetObjective(1);
      return QTask_GetFirstChildOfType(&v6->tQTask, SpawnArea_eQTaskType);
    }
    v10 = NetMission_GetObjective(2);
    return QTask_GetLastChildOfType(&v10->tQTask, SpawnArea_eQTaskType);
  }
  else
  {
    if ( isReverse )
    {
      v5 = nNumber - 1;
LABEL_15:
      v11 = NetMission_GetObjective(v5);
      return QTask_GetLastChildOfType(&v11->tQTask, SpawnArea_eQTaskType);
    }
    v12 = NetMission_GetObjective(nNumber + 1);
    return QTask_GetFirstChildOfType(&v12->tQTask, SpawnArea_eQTaskType);
  }
}

// source: j/0/network/netmanager.c:4841  [anchor-strings]
void __cdecl NetManager_UpdateSpawn(struct NetManager_s *ptNetManager, unsigned __int64 nInputPort)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct NetManagerGameMessage_s ptGameMessage; };
    struct { char igi2_o1[8]; struct QTask_s *ptMiddle; };
    struct { char igi2_o2[12]; int LevelQTaskIDFromQTask; };
    char igi2_extent[16];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Client_s *ClientFromNetworkID; // edi
  int v3; // edx
  enum bool v4; // ebx
  int v5; // esi
  struct QTask_s *PrevSiblingOfType; // eax
  struct NetObjective_t *ptParent; // esi
  char *LocalizedString; // eax

  ClientFromNetworkID = NetManager_GetClientFromNetworkID((int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
  v3 = 0;
  v4 = false;
  if ( (!MenuManager_ptQTask || MenuManager_ptQTask[1].tQTaskChildren.ptMiddle == (struct QTask_s *)10)
    && HumanPlayer_ptQTask
    && ClientFromNetworkID
    && LOBYTE(HumanPlayer_ptQTask[29].tQTaskRefList.ptHead) )
  {
    v5 = nInputPort;
    if ( (nInputPort & 0x800) != 0 || *(_DWORD *)&ptNetManager->tReceiveCounters.zName[12] )
    {
      v3 = 1;
      v4 = false;
    }
    if ( (nInputPort & 0x400) != 0 )
    {
      v4 = true;
    }
    else if ( !v3 )
    {
LABEL_28:
      NetManager_UpdateSpawnCamera();
      if ( (v5 & 0x80000) != 0 && !ClientFromNetworkID->ePrevActiveMenu )
      {
        if ( Client_isSpawnAffordable(nullptr, (int)ClientFromNetworkID) )
        {
          igi2_frame.ptGameMessage.eGameMessage = 1381061463;
          igi2_frame.ptGameMessage.nLocalTime = NetManager_GetTimer();
          igi2_frame.ptMiddle = Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle;
          igi2_frame.LevelQTaskIDFromQTask = Level_GetLevelQTaskIDFromQTask(SpawnArea_ptActive);
          NetManager_SendGameMessage(0, (int)igi2_frame.ptMiddle, NETWORKQUEUE_GUARANTEED, &igi2_frame.ptGameMessage, 0x10u);
          ClientFromNetworkID->ePrevActiveMenu = 1;
          HumanPlayerInput_SetFreezeFire();
          ptNetManager->isGameStarted = 0;
          ptNetManager->isSynchronized = 0;
          ptNetManager->isForceSpawnMode = 0;
          ptNetManager->isUpdateSettings = 0;
          ptNetManager->isFirstRound = 0;
          ptNetManager->nClientConnectWarn = 0;
        }
        else
        {
          LocalizedString = Config_GetLocalizedString((char *)&g_ptClient.tQTask.ptParent);
          StatusScreen_ShowMessage(LocalizedString, TEXTSCROLLER_COLOUR_RED);
          Client_DebugSpawnInfo((char *)ClientFromNetworkID, (struct Client_s *)&g_ptClient);
        }
      }
      return;
    }
    PrevSiblingOfType = SpawnArea_ptActive;
    ptParent = (struct NetObjective_t *)SpawnArea_ptActive->ptParent;
    if ( *(_DWORD *)&ptNetManager->tReceiveCounters.zName[12]
      && SpawnArea_ptActive[6].tQTaskChildren.ptHead == (struct QTask_s *)ClientFromNetworkID->eTeam )
    {
      *(_DWORD *)&ptNetManager->tReceiveCounters.zName[12] = 0;
    }
    else if ( v4 )
    {
      PrevSiblingOfType = QTask_GetPrevSiblingOfType(SpawnArea_ptActive, SpawnArea_eQTaskType);
    }
    else
    {
      PrevSiblingOfType = QTask_GetNextSiblingOfType(SpawnArea_ptActive, SpawnArea_eQTaskType);
    }
    if ( !PrevSiblingOfType )
    {
      PrevSiblingOfType = NetManager_GetNextObjectiveSpawn(ptNetManager, ClientFromNetworkID, ptParent, v4);
      ptParent = (struct NetObjective_t *)PrevSiblingOfType->ptParent;
    }
    while ( PrevSiblingOfType[6].tQTaskChildren.ptHead != (struct QTask_s *)ClientFromNetworkID->eTeam )
    {
      if ( v4 )
        PrevSiblingOfType = QTask_GetPrevSiblingOfType(PrevSiblingOfType, SpawnArea_eQTaskType);
      else
        PrevSiblingOfType = QTask_GetNextSiblingOfType(PrevSiblingOfType, SpawnArea_eQTaskType);
      if ( !PrevSiblingOfType )
      {
        PrevSiblingOfType = NetManager_GetNextObjectiveSpawn(ptNetManager, ClientFromNetworkID, ptParent, v4);
        ptParent = (struct NetObjective_t *)PrevSiblingOfType->ptParent;
      }
    }
    v5 = nInputPort;
    SpawnArea_ptActive = PrevSiblingOfType;
    goto LABEL_28;
  }
}

// source: j/0/network/netmanager.c:5000  [anchor-strings]
void __cdecl NetManager_UpdateSettings(struct NetManager_s *ptNetManager)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct NetManagerGameMessage_s ptGameMessage; };
    struct { char igi2_o1[8]; struct QTask_s *v11; };
    struct { char igi2_o2[12]; int eTeam; };
    struct { char igi2_o3[16]; int v13; };
    struct { char igi2_o4[20]; int v14; };
    struct { char igi2_o5[24]; char Destination[64]; };
    char igi2_extent[88];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Client_s *ClientFromNetworkID; // eax
  struct Client_s *v2; // ebx
  struct Human_s *v3; // edi
  char *pzModel; // ecx
  enum NetManagerMode_e v5; // ebp
  char *LocalizedStringForLanguage; // eax
  struct Client_s *v7; // eax
  struct QTask_s *v8; // esi
  struct QTask_s *ptMiddle; // eax

  if ( *(_DWORD *)&ptNetManager->tReceiveCounters.zName[16] )
  {
    ClientFromNetworkID = NetManager_GetClientFromNetworkID((int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
    v2 = ClientFromNetworkID;
    if ( ClientFromNetworkID )
    {
      v3 = *(struct Human_s **)(ClientFromNetworkID->tReceiveTimeBuffer.nCounter + 8);
      strcpy(ClientFromNetworkID->zTeamName, NetManager_atTeams[ClientFromNetworkID->eTeam].pzName);
      if ( v2->eTeam == 1 )
        pzModel = NetManager_atBadModel[NetManager_eModel].pzModel;
      else
        pzModel = NetManager_atGoodModel[NetManager_eModel].pzModel;
      sprintf(v2->zModel, "%s%d_1", pzModel, NetManager_eFace);
      Human_SetTeam(v3, v2->eTeam, v2->zModel);
      if ( NetManager_eMode == NETMANAGER_MODE_PLAY )
      {
        v5 = NETMANAGER_MODE_SPAWN;
        if ( BYTE2(Flow_ptFlow->ptNetManagerQTask[5].tQTaskChildren.ptTail) && NetManager_ForceChangeTeam() )
        {
          LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                         "mp/FORCE_TEAM_CHANGE",
                                         Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                         true);
          StatusScreen_ShowMessage(LocalizedStringForLanguage, TEXTSCROLLER_COLOUR_WHITE);
          v5 = NETMANAGER_MODE_SELECTSKIN;
          NetManager_nBodySprite = 0;
          NetManager_nFaceSprite = 0;
          NetManager_isModelSelect = true;
        }
        v7 = NetManager_GetClientFromNetworkID((int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
        if ( v7 )
          NetManager_eTeam = v7->eTeam;
        NetManager_eMode = v5;
        v8 = MenuManager_ptQTask;
        LOBYTE(MenuManager_ptQTask[243].eQTaskType) = 1;
        switch ( v5 )
        {
          case NETMANAGER_MODE_SELECTSKIN:
            if ( !LOBYTE(HumanPlayer_ptQTask[29].tQTaskRefList.ptHead) )
            {
              NetManager_KillClient((int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
              v8 = MenuManager_ptQTask;
            }
            v8[1].ptNext = (struct QTask_s *)996;
            v8[1].tQTaskChildren.ptMiddle = nullptr;
            break;
          case NETMANAGER_MODE_SPAWN:
            LOBYTE(v8[243].eQTaskType) = 0;
            NetManager_ForceSpawnMode();
            break;
        }
      }
      Weapon_ClearAllWeapons(v3->ptWeaponQTask);
      Weapon_EnableWeaponType(v3->ptWeaponQTask, "WEAPON_ID_KNIFE", true);
      if ( v2->eTeam == 1 )
        Weapon_EnableWeaponType(v3->ptWeaponQTask, "WEAPON_ID_MAKAROV", true);
      else
        Weapon_EnableWeaponType(v3->ptWeaponQTask, "WEAPON_ID_GLOCK", true);
      igi2_frame.ptGameMessage.eGameMessage = 1397052500;
      igi2_frame.ptGameMessage.nLocalTime = NetManager_GetTimer();
      ptMiddle = Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle;
      igi2_frame.eTeam = v2->eTeam;
      igi2_frame.v11 = ptMiddle;
      igi2_frame.v13 = NetManager_eModel;
      igi2_frame.v14 = NetManager_eFace;
      strncpy(igi2_frame.Destination, v2->zPlayerName, 0x40u);
      NetManager_SendGameMessage(
        0,
        (int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle,
        NETWORKQUEUE_GUARANTEED,
        &igi2_frame.ptGameMessage,
        0x58u);
    }
    *(_DWORD *)&ptNetManager->tReceiveCounters.zName[16] = 0;
  }
}

// source: j/0/network/netmanager.c:5100  [anchor-strings]
struct Client_s *__cdecl NetManager_FindNextSpectateClientTarget(
        struct Client_s *ptClientTarget,
        enum bool isReverse)
{
  struct Flow_t *v2; // ebp
  struct QTask_s *ptNetManagerQTask; // ebx
  struct Client_s *v4; // esi
  unsigned __int16 v5; // di
  struct Client_s *v6; // eax
  struct QTask_s *v7; // eax
  struct Client_s *v8; // eax
  int v9; // eax
  unsigned int nSpectateMode; // [esp+10h] [ebp-8h]
  struct Client_s *ptLocalClient; // [esp+14h] [ebp-4h]

  v2 = Flow_ptFlow;
  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  v4 = ptClientTarget;
  ptLocalClient = NetManager_GetClientFromNetworkID((int)ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
  nSpectateMode = (unsigned int)ptNetManagerQTask[5].tQTaskRefList.ptHead;
  if ( nSpectateMode > 2 )
  {
    NetManager_LogMessage("Bad spectate mode, set to NO spectating\n");
    v2 = Flow_ptFlow;
    nSpectateMode = 0;
  }
  v5 = Client_eQTaskType;
  while ( 1 )
  {
    if ( isReverse )
      v6 = (struct Client_s *)(v4
                             ? QTask_GetPrevSiblingOfType(&v4->tQTask, v5)
                             : QTask_GetLastChildOfType(v2->ptNetManagerQTask, v5));
    else
      v6 = (struct Client_s *)(v4
                             ? QTask_GetNextSiblingOfType(&v4->tQTask, v5)
                             : QTask_GetFirstChildOfType(v2->ptNetManagerQTask, v5));
    v4 = v6;
    if ( v6 == ptClientTarget )
      break;
    if ( !v6 )
    {
      v7 = v2->ptNetManagerQTask;
      v8 = (struct Client_s *)(isReverse ? QTask_GetLastChildOfType(v7, v5) : QTask_GetFirstChildOfType(v7, v5));
      v4 = v8;
      if ( v8 == ptClientTarget )
        break;
    }
    v9 = *(_DWORD *)(v4->tReceiveTimeBuffer.nCounter + 8);
    if ( v9
      && !*(_BYTE *)(v9 + 1180)
      && (struct QTask_s *)v9 != HumanPlayer_ptQTask
      && nSpectateMode
      && (nSpectateMode == 1 ? v4->eTeam == ptLocalClient->eTeam : nSpectateMode == 2) )
    {
      return v4;
    }
  }
  return ptClientTarget;
}

// source: j/0/network/netmanager.c:5217  [anchor-caller]
void __cdecl NetManager_UpdateSpectating(struct NetManager_s *ptNetManager, unsigned __int64 nInputPort)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[4]; enum WeaponOverlayStatus_e v23; };
    struct { char igi2_o2[24]; struct Client_s *NextSpectateClientTarget; };
    struct { char igi2_o3[28]; int v25; };
    struct { char igi2_o4[32]; struct Client_s *v26; };
    struct { char igi2_o5[36]; int v27; };
    struct { char igi2_o6[44]; struct real64x3_t ptNewPos; };
    struct { char igi2_o7[68]; _BYTE v29[40]; };
    char igi2_extent[108];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Client_s *ClientFromNetworkID; // ebx
  struct Client_s *v3; // eax
  struct QTask_s *v4; // ebp
  struct Client_s *v5; // edi
  int v6; // ebx
  _DWORD *v7; // eax
  struct QTask_s *ptNext; // edi
  int v9; // eax
  int v10; // eax
  int v11; // ecx
  void *v12; // ecx
  struct QTask_s *v13; // ecx
  struct QReference_s *ptHead; // eax
  struct QReference_s *ptHumanCameraQTaskRef; // eax
  struct QTask_s *pxObject; // edi
  struct Game_s *v17; // eax
  struct QReference_s *v18; // eax
  struct QTask_s *v19; // eax
  struct QTask_s *ptTail; // eax
  struct QTask_s *v21; // eax

  ClientFromNetworkID = NetManager_GetClientFromNetworkID(ptNetManager->eSpectateNetworkID);
  igi2_frame.NextSpectateClientTarget = ClientFromNetworkID;
  v3 = NetManager_GetClientFromNetworkID((int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
  v4 = HumanPlayer_ptQTask;
  v5 = v3;
  igi2_frame.v26 = v3;
  igi2_frame.v25 = 0;
  if ( HumanPlayer_ptQTask && LOBYTE(HumanPlayer_ptQTask[29].tQTaskRefList.ptHead)
    || NetManager_eMode == NETMANAGER_MODE_COMPLETE )
  {
    if ( !ClientFromNetworkID || (nInputPort & 0x800) != 0 )
    {
      igi2_frame.NextSpectateClientTarget = NetManager_FindNextSpectateClientTarget(ClientFromNetworkID, false);
      igi2_frame.v25 = 1;
      ClientFromNetworkID = igi2_frame.NextSpectateClientTarget;
    }
    if ( (nInputPort & 0x400) != 0 )
    {
      igi2_frame.NextSpectateClientTarget = NetManager_FindNextSpectateClientTarget(ClientFromNetworkID, true);
      igi2_frame.v25 = 1;
      ClientFromNetworkID = igi2_frame.NextSpectateClientTarget;
    }
    if ( (nInputPort & 0x20000) != 0 && !ptNetManager->tServerGameSettings.isForceFirstSpec )
    {
      igi2_frame.v25 = 1;
      v5->ptHumanQTaskRef = (struct QReference_s *)(v5->ptHumanQTaskRef == nullptr);
    }
    if ( ClientFromNetworkID && NetManager_eMode == NETMANAGER_MODE_SPECTATE )
    {
      v6 = *(_DWORD *)(ClientFromNetworkID->tReceiveTimeBuffer.nCounter + 8);
      igi2_frame.v27 = *(_DWORD *)(v6 + 1336);
      if ( *(_BYTE *)(v6 + 1180) && NetManager_GetTimer() - igi2_frame.NextSpectateClientTarget->isSpectateFirstPerson > 4000 )
      {
        ptNetManager->eSpectateNetworkID = -1;
        return;
      }
      qmemcpy(&igi2_frame.ptNewPos, (void *)(v6 + 40), sizeof(igi2_frame.ptNewPos));
      qmemcpy(igi2_frame.v29, (void *)(v6 + 124), sizeof(igi2_frame.v29));
      if ( igi2_frame.v26->ptHumanQTaskRef && *(_DWORD *)(igi2_frame.v27 + 664) )
      {
        v7 = *(_DWORD **)(*(_DWORD *)(v6 + 1320) + 44);
        if ( v7 )
          v7 = (_DWORD *)v7[4];
        ptNext = v4[33].ptNext;
        if ( !ptNext[4].ptPrev && v7 && v7[330] == Zoom_eQTaskType )
        {
          v9 = v7[333];
          if ( v9 )
            v10 = *(_DWORD *)(v9 + 8);
          else
            v10 = 0;
          v11 = *(_DWORD *)(v10 + 116);
          if ( v11 )
            v12 = *(void **)(v11 + 8);
          else
            v12 = nullptr;
          v4[33].ptNext[4].ptPrev = QTask_NewFn(ptNext, *(_WORD *)(v10 + 108), v12);
          v4[33].ptNext[4].ptNext = (struct QTask_s *)2;
        }
      }
      else if ( v4[33].ptNext[4].ptPrev )
      {
        QTask_Delete(v4[33].ptNext[4].ptPrev);
        v13 = v4[33].ptNext;
        v13[4].ptPrev = nullptr;
        Weapon_SetOverlayStatus(v13, igi2_frame.v23, 0, (int)v4[33].ptNext);
      }
      ptNetManager->eSpectateNetworkID = igi2_frame.NextSpectateClientTarget->eNetworkID;
      BYTE2(v4[33].tQTaskChildren.ptTail[12].tQTaskRefList.ptTail) = 0;
      if ( igi2_frame.v25
        || (ptHead = v4[33].tQTaskRefList.ptHead, ptHead != (struct QReference_s *)6)
        && ptHead != (struct QReference_s *)7 )
      {
        ptHumanCameraQTaskRef = Game_ptGame->ptHumanCameraQTaskRef;
        if ( ptHumanCameraQTaskRef )
          pxObject = (struct QTask_s *)ptHumanCameraQTaskRef->pxObject;
        else
          pxObject = nullptr;
        HumanCamera_SetHumanQTask(pxObject, (struct QTask_s *)v6);
        if ( igi2_frame.v26->ptHumanQTaskRef )
        {
          v4[33].tQTaskRefList.ptHead = (struct QReference_s *)6;
          *(_DWORD *)(v6 + 1340) = 6;
        }
        else
        {
          v4[33].tQTaskRefList.ptHead = (struct QReference_s *)7;
          *(_DWORD *)(v6 + 1340) = 7;
        }
      }
    }
    else
    {
      if ( !NetMission_ptNetMission )
      {
        LDebug_Error("NetMission not initialized, can't get start camera pos");
        abort();
      }
      qmemcpy(&igi2_frame.ptNewPos, &NetMission_ptNetMission->tStartCamPos, sizeof(igi2_frame.ptNewPos));
      v17 = Game_ptGame;
      qmemcpy(igi2_frame.v29, &NetMission_ptNetMission->tStartCamOrientation, sizeof(igi2_frame.v29));
      ptNetManager->eSpectateNetworkID = -1;
      v18 = v17->ptHumanCameraQTaskRef;
      if ( v18 )
        v19 = (struct QTask_s *)v18->pxObject;
      else
        v19 = nullptr;
      HumanCamera_SetHumanQTask(v19, v4);
      ptTail = v4[33].tQTaskChildren.ptTail;
      qmemcpy(&ptTail[12].ptParent, &igi2_frame.ptNewPos, 0x18u);
      BYTE2(ptTail[12].tQTaskRefList.ptTail) = 1;
      qmemcpy(&ptTail[13].tQTaskChildren.ptTail, igi2_frame.v29, sizeof(struct QTask_s));
      v21 = v4[33].tQTaskChildren.ptTail;
      v21[16].tQTaskRefList.ptMiddle = nullptr;
      *(float *)&v21[16].tQTaskChildren.ptHead = tan(0.7853981852531433);
      *(float *)&v21[16].tQTaskRefList.ptHead = tan(0.5235987901687622);
      v4[33].tQTaskRefList.ptHead = (struct QReference_s *)4;
    }
    if ( !LOBYTE(v4[80].tQTaskChildren.ptTail) )
    {
      igi2_frame.ptDynCubeObj = sqrt(
                       *(float *)&v4[7].tQTaskChildren.ptTail * *(float *)&v4[7].tQTaskChildren.ptTail
                     + *(float *)&v4[7].tQTaskRefList.ptHead * *(float *)&v4[7].tQTaskRefList.ptHead
                     + *(float *)&v4[7].tQTaskRefList.ptMiddle * *(float *)&v4[7].tQTaskRefList.ptMiddle)
                   + *(float *)&v4[8].ptNext;
      World_MoveDynCubeObjRadius(Game_ptGame->ptWorld, (struct DynCubeObj_s *)v4, &igi2_frame.ptNewPos, igi2_frame.ptDynCubeObj);
      qmemcpy(&v4[3].ptPrev, igi2_frame.v29, sizeof(struct QTask_s));
    }
  }
}

// source: j/0/network/netmanager.c:5390  [anchor-strings]
enum bool __cdecl NetManager_WaitUntilState(
        enum bool isWaitFor,
        int nSeconds,
        float vPeriod,
        int nTimeoutSeconds)
{
  struct QTask_s *ptNetManagerQTask; // esi
  struct QTask_s *ptMiddle; // edi
  DWORD PerformanceCounter; // eax
  DWORD TickCount; // eax
  char Buffer[256]; // [esp+18h] [ebp-100h] BYREF

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  ptMiddle = ptNetManagerQTask[9].tQTaskChildren.ptMiddle;
  if ( QTask_GetFirstChildOfType(ptNetManagerQTask, MapControl_eQTaskType)[1].ptParent != (struct QTask_s *)isWaitFor )
  {
    do
    {
      if ( Timer_isPerformanceCounter )
        PerformanceCounter = Timer_GetPerformanceCounter();
      else
        PerformanceCounter = GetTickCount();
      if ( (int)(PerformanceCounter - Timer_nStartTime - (unsigned int)ptNetManagerQTask[9].tQTaskChildren.ptMiddle) >= 1000 * nTimeoutSeconds )
        break;
      NetManager_BlockRunNetwork(nSeconds, vPeriod);
      if ( (int)ptNetManagerQTask[9].tQTaskChildren.ptMiddle <= (int)ptMiddle )
      {
        if ( Timer_isPerformanceCounter )
          TickCount = Timer_GetPerformanceCounter();
        else
          TickCount = GetTickCount();
        _snprintf(
          Buffer,
          0xFFu,
          "WaitUntilState: Since received is %.1f seconds...\n",
          (double)(int)(TickCount - Timer_nStartTime - (unsigned int)ptNetManagerQTask[9].tQTaskChildren.ptMiddle)
        * 0.0010000000474974513);
        NetManager_LogMessage(Buffer);
      }
      ptMiddle = ptNetManagerQTask[9].tQTaskChildren.ptMiddle;
    }
    while ( QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, MapControl_eQTaskType)[1].ptParent != (struct QTask_s *)isWaitFor );
  }
  return QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, MapControl_eQTaskType)[1].ptParent == (struct QTask_s *)isWaitFor;
}

// source: j/0/network/netmanager.c:5440  [anchor-strings]
void __cdecl NetManager_ChangeLocalMap(int nMap)
{
  struct QTask_s *ptNetManagerQTask; // ebp
  struct Client_s *ClientFromNetworkID; // eax
  struct QTask_s *v3; // eax
  struct QTask_s *v4; // ecx
  unsigned int v5; // ecx
  bool v6; // sf
  int v7; // eax
  struct QTask_s *v8; // eax
  char *v9; // ecx
  struct Flow_t *v10; // eax
  struct QTask_s *ptMiddle; // edx

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  if ( !ptNetManagerQTask[6].tQTaskChildren.ptMiddle
    || (NetManager_LogMessage("Waiting for server to start loading map...\n"),
        NetManager_WaitUntilState(true, 2, 0.15000000596046448, 50)) )
  {
    ClientFromNetworkID = NetManager_GetClientFromNetworkID((int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
    if ( ClientFromNetworkID )
      Client_CancelTalk(ClientFromNetworkID);
    v3 = Flow_ptFlow->ptNetManagerQTask;
    v4 = (struct QTask_s *)((char *)&v3[32].tQTaskChildren.ptTail->ptNext + 1);
    v3[32].tQTaskChildren.ptTail = v4;
    *((_DWORD *)&v3[31].tQTaskChildren.ptTail + (_DWORD)v4) = 1;
    Game_MPRunNetwork((char *)v4);
    NetMission_Restart();
    v5 = (NetManager_tRandomState.anRandom[0] >> 7) ^ NetManager_tRandomState.anRandom[2];
    v6 = (int)((v5 ^ NetManager_tRandomState.anRandom[1]) + NetManager_tRandomState.anRandom[0]) < 0;
    v7 = (v5 ^ NetManager_tRandomState.anRandom[1]) + NetManager_tRandomState.anRandom[0];
    NetManager_tRandomState.anRandom[2] = v5;
    NetManager_tRandomState.anRandom[1] ^= v5;
    NetManager_tRandomState.anRandom[0] = v7;
    NetManager_nRandomInt = v7;
    if ( v6 )
      NetManager_nRandomInt = -v7;
    Game_MPRunNetwork((char *)v5);
    v8 = Flow_ptFlow->ptNetManagerQTask;
    v8[6].tQTaskChildren.ptTail = (struct QTask_s *)-1;
    *(_DWORD *)&v8[35].eQTaskType = 0;
    NetManager_iSpawnPointID = 0;
    NetManager_iSpawnAreaID = 0;
    Game_iMissionID = nMap;
    Game_MPRunNetwork(v9);
    v10 = Flow_ptFlow;
    ptMiddle = Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle;
    NetManager_nSelectedSession = -1;
    if ( !ptMiddle )
      ptNetManagerQTask[3].ptNext = (struct QTask_s *)nMap;
    Game_ptGame->eGameStatus = GAME_GAMESTATUS_COMPLETED;
    --v10->ptNetManagerQTask[32].tQTaskChildren.ptTail;
  }
  else
  {
    NetManager_LogMessage("NetManager_ChangeLocalMap: Server did not send map finished, exiting game...\n");
    NetManager_LeaveGame();
    NetManager_Quit();
  }
}

// source: j/0/network/netmanager.c:5520  [anchor-hash]
void __cdecl NetManager_ClearClientSessionLists()
{
  NetManager_tSessionList.ptHead = (struct Node_s *)&NetManager_tSessionList.ptMiddle;
  NetManager_tSessionList.ptTail = (struct Node_s *)&NetManager_tSessionList;
  NetManager_tSessionList.ptMiddle = nullptr;
  NetManager_tSortedSessionList.ptHead = (struct Node_s *)&NetManager_tSortedSessionList.ptMiddle;
  NetManager_tSortedSessionList.ptTail = (struct Node_s *)&NetManager_tSortedSessionList;
  NetManager_tSortedSessionList.ptMiddle = nullptr;
  NetManager_nSelectedSession = -1;
  NetManager_iCurrentSession = 0;
}

// source: j/0/network/netmanager.c:5548  [anchor-callee]
void __cdecl NetManager_StopNetwork(struct NetManager_s *ptNetManager)
{
  struct QTask_s *FirstChildOfType; // ebx
  struct QTask_s *v2; // ebp
  void *pxServerInterface; // ebx
  struct Node_s *ptHead; // eax
  struct Node_s *i; // ebx
  _DWORD **v6; // eax
  int v7; // ebp
  int v8; // eax
  int *anObjectiveWhoDidIt; // ecx
  struct QTask_s *ptQTask; // [esp+4h] [ebp-8h]
  struct QTask_s *v11; // [esp+8h] [ebp-4h]

  if ( ptNetManager->pxClientInterface )
  {
    Network_StopNetwork(ptNetManager->pxClientInterface);
    Network_nLastConnectionResponse = 8;
    ptNetManager->pxClientInterface = nullptr;
    ptNetManager->tReceiveCounters.tCounters[0].nBytes = 0;
    ptNetManager->tReceiveCounters.tCounters[1].eGameMessage = -1;
  }
  if ( ptNetManager->pxServerInterface )
  {
    FirstChildOfType = QTask_GetFirstChildOfType(&ptNetManager->tQTask, GameSpy_eQTaskType);
    v2 = QTask_GetFirstChildOfType(&ptNetManager->tQTask, ASE_eQTaskType);
    ptQTask = QTask_GetFirstChildOfType(&ptNetManager->tQTask, Consoled_eQTaskType);
    v11 = QTask_GetFirstChildOfType(&ptNetManager->tQTask, Server_eQTaskType);
    if ( FirstChildOfType )
      QTask_Delete(FirstChildOfType);
    if ( v2 )
      QTask_Delete(v2);
    if ( ptQTask )
      QTask_Delete(ptQTask);
    if ( v11 )
      QTask_Delete(v11);
    pxServerInterface = ptNetManager->pxServerInterface;
    QObjectVector_Delete(Network_ptLoadingHosts);
    Network_ptLoadingHosts = nullptr;
    Network_StopNetwork(pxServerInterface);
    ptNetManager->pxServerInterface = nullptr;
    ptNetManager->tReceiveCounters.tCounters[0].nBytes = 0;
    ptNetManager->tReceiveCounters.tCounters[1].eGameMessage = -1;
  }
  ptNetManager->eLocalNetworkID = -1;
  ptNetManager->eSpectateNetworkID = -1;
  ptHead = NetManager_tClientPacketIDs.ptHead;
  for ( i = NetManager_tClientPacketIDs.ptHead->ptNext; i; i = i->ptNext )
  {
    v6 = Node_Remove(ptHead);
    if ( v6 )
    {
      --Mem_nCurrentAllocations;
      v7 = *(_DWORD *)((unsigned int)(v6 - 1) & 0xFFFFFFFC);
      Node_Remove((_DWORD **)v7);
      memset(*(void **)(v7 + 8), 0xCDu, *(_DWORD *)(v7 + 16));
      free((void *)v7);
    }
    ptHead = i;
  }
  ptNetManager->tReceiveCounters.tCounters[3].nCounter = 0;
  ptNetManager->anRunTimer[1] = 0;
  ptNetManager[1].pxServerInterface = nullptr;
  *(_DWORD *)ptNetManager[1].tServerGameSettings.zServerName = 0;
  ptNetManager->tSendCounters.tCounters[3].nBytes = 100000;
  ptNetManager->tSendCounters.tCounters[3].nCounter = 0;
  ptNetManager->tServerGameSettings.nNumPlayers = 0;
  ptNetManager->tServerGameSettings.nNumLoadingPlayers = 0;
  *(_DWORD *)&ptNetManager->tReceiveCounters.zName[12] = 0;
  *(_DWORD *)&ptNetManager->tReceiveCounters.zName[8] = 0;
  *(_DWORD *)&ptNetManager->tReceiveCounters.zName[16] = 0;
  ptNetManager->tReceiveCounters.nStartTime = 1;
  ptNetManager->tReceiveCounters.tCounters[0].nBytes = 0;
  ptNetManager->tReceiveCounters.tCounters[1].eGameMessage = -1;
  ptNetManager->anRunTimer[2] = -1;
  ptNetManager->tReceiveCounters.nPeriod = 0;
  v8 = 0;
  anObjectiveWhoDidIt = ptNetManager->tServerGameSettings.anObjectiveWhoDidIt;
  do
  {
    ptNetManager->tServerGameSettings.anObjectiveWinTeam[v8] = -1;
    *anObjectiveWhoDidIt = -1;
    ++v8;
    ++anObjectiveWhoDidIt;
  }
  while ( v8 < 8 );
  *(_DWORD *)&ptNetManager[1].tQTask.eQTaskType = 0;
}

// source: j/0/network/netmanager.c:5666  [anchor-strings]
void __cdecl NetManager_Quit()
{
  struct QTask_s *ptNetManagerQTask; // esi
  DWORD PerformanceCounter; // eax
  struct QTask_s *FirstChildOfType; // edx
  struct QTask_s *NextSiblingOfType; // edi
  struct Flow_t *v4; // eax
  unsigned __int16 v5; // dx
  struct QTask_s *ptNext; // edx
  BOOL v7; // edi

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  ptNetManagerQTask[9].tQTaskChildren.ptMiddle = (struct QTask_s *)(PerformanceCounter - Timer_nStartTime);
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    NetManager_tSessionList.ptHead = (struct Node_s *)&NetManager_tSessionList.ptMiddle;
    NetManager_tSessionList.ptTail = (struct Node_s *)&NetManager_tSessionList;
    NetManager_tSessionList.ptMiddle = nullptr;
    NetManager_tSortedSessionList.ptHead = (struct Node_s *)&NetManager_tSortedSessionList.ptMiddle;
    NetManager_tSortedSessionList.ptTail = (struct Node_s *)&NetManager_tSortedSessionList;
    NetManager_tSortedSessionList.ptMiddle = nullptr;
    NetManager_nSelectedSession = -1;
    NetManager_iCurrentSession = 0;
  }
  if ( Flow_ptFlow->ptNetManagerQTask[32].tQTaskChildren.ptTail != (struct QTask_s *)-1 )
    NetManager_LogMessage("NetManager_Quit: Buffer state not empty\n");
  FirstChildOfType = QTask_GetFirstChildOfType(ptNetManagerQTask, Client_eQTaskType);
  if ( FirstChildOfType )
  {
    do
    {
      NextSiblingOfType = QTask_GetNextSiblingOfType(FirstChildOfType, Client_eQTaskType);
      QTask_Delete(FirstChildOfType);
      FirstChildOfType = NextSiblingOfType;
    }
    while ( NextSiblingOfType );
  }
  v4 = Flow_ptFlow;
  v5 = Netshop_eQTaskType;
  ptNetManagerQTask[8].ptParent = nullptr;
  ptNetManagerQTask[8].tQTaskRefList.ptTail = nullptr;
  *(_DWORD *)&ptNetManagerQTask[8].eQTaskType = 0;
  ptNetManagerQTask[9].ptNext = (struct QTask_s *)1;
  ptNetManagerQTask[9].tQTaskChildren.ptTail = nullptr;
  ptNetManagerQTask[9].tQTaskRefList.ptHead = (struct QReference_s *)-1;
  ptNetManagerQTask[31].tQTaskChildren.ptHead = (struct QTask_s *)-1;
  QTask_GetFirstChildOfType(v4->ptNetManagerQTask, v5)[1].ptNext = nullptr;
  NetManager_ClearBuffer();
  ptNext = ptNetManagerQTask[1].ptNext;
  NetManager_eRequestedTeam = -1;
  v7 = ptNext != nullptr;
  NetManager_StopNetwork((struct NetManager_s *)ptNetManagerQTask);
  if ( Game_eGameMode == GAME_GAMEMODE_SINGLEPLAYER || AppContext_tAppContext.isEditorState )
    Flow_ptFlow->eRequestedEvent = v7 + 6;
  else
    Flow_ptFlow->eRequestedEvent = 1;
}

// source: j/0/network/netmanager.c:5754  [anchor-caller]
void __cdecl NetManager_AbortInit()
{
  struct QTask_s *ptNetManagerQTask; // esi

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  ptNetManagerQTask[8].ptParent = nullptr;
  ptNetManagerQTask[8].tQTaskRefList.ptTail = nullptr;
  *(_DWORD *)&ptNetManagerQTask[8].eQTaskType = 0;
  ptNetManagerQTask[9].tQTaskChildren.ptTail = nullptr;
  ptNetManagerQTask[9].ptNext = (struct QTask_s *)1;
  ptNetManagerQTask[9].tQTaskRefList.ptHead = (struct QReference_s *)-1;
  ptNetManagerQTask[31].tQTaskChildren.ptHead = (struct QTask_s *)-1;
  NetManager_ClearBuffer();
  NetManager_StopNetwork((struct NetManager_s *)ptNetManagerQTask);
}

// source: j/0/network/netmanager.c:5779  [anchor-strings]
void __cdecl NetManager_LeaveGame()
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s *ptMiddle; };
    struct { char igi2_o1[20]; struct NetManagerGameMessage_s ptGameMessage; };
    struct { char igi2_o2[28]; struct QTask_s *v15; };
    struct { char igi2_o3[32]; char v16; };
    struct { char igi2_o4[36]; char Buffer[260]; };
    char igi2_extent[296];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct NetManagerCounterSet_s *ptNetManagerQTask; // edi
  struct QTask_s *p_tQTask; // esi
  unsigned __int16 v2; // dx
  struct Client_s *v3; // eax
  struct QTask_s *v4; // esi
  DWORD PerformanceCounter; // eax
  struct Flow_t *v6; // ebx
  int v7; // ebp
  struct QTask_s *v8; // esi
  struct QTask_s *v9; // edi
  unsigned __int16 v10; // dx
  struct QTask_s *v11; // eax
  int v12; // ecx

  ptNetManagerQTask = (struct NetManagerCounterSet_s *)Flow_ptFlow->ptNetManagerQTask;
  if ( ptNetManagerQTask->tCounters[18].nCounter || ptNetManagerQTask->tCounters[1].eGameMessage )
  {
    NetManager_LogMessage((char *)&stru_6A4CDC);
    NetManager_LogClients();
    NetManager_LogMessage((char *)&stru_6A4CDC);
    NetManager_PrintCounter(ptNetManagerQTask + 1, (void (*)(char *, ...))NetManager_LogMessage);
    NetManager_LogMessage((char *)&stru_6A4CDC);
    NetManager_PrintCounter(ptNetManagerQTask + 2, (void (*)(char *, ...))NetManager_LogMessage);
    NetManager_LogMessage((char *)&stru_6A4CDC);
    Network_PrintNetworkStats((void (*)(char *, ...))NetManager_LogMessage);
    if ( ptNetManagerQTask->tCounters[1].eGameMessage )
    {
      p_tQTask = nullptr;
      NetManager_LogMessage("Server removing all players...\n");
LABEL_5:
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
          Server_DestroyPlayer(v3, NETMANAGER_DESTROYPLAYER_REASON_SHUTDOWN);
          goto LABEL_5;
        }
      }
      NetManager_BlockRunNetwork(2, 0.20000000298023224);
    }
  }
  if ( ptNetManagerQTask->tCounters[18].nCounter || ptNetManagerQTask->tCounters[1].eGameMessage )
  {
    v4 = Flow_ptFlow->ptNetManagerQTask;
    igi2_frame.ptGameMessage.eGameMessage = 1145393228;
    if ( Timer_isPerformanceCounter )
      PerformanceCounter = Timer_GetPerformanceCounter();
    else
      PerformanceCounter = GetTickCount();
    igi2_frame.ptMiddle = Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle;
    igi2_frame.ptGameMessage.nLocalTime = PerformanceCounter
                             - Timer_nStartTime
                             + (char *)v4[6].tQTaskRefList.ptMiddle
                             - (char *)v4[6].tQTaskRefList.ptTail;
    igi2_frame.v15 = igi2_frame.ptMiddle;
    igi2_frame.v16 = 1;
    _snprintf(igi2_frame.Buffer, 0xFFu, "LeaveGame: Signaling that self[%d] is leaving game\n", igi2_frame.ptMiddle);
    NetManager_LogMessage(igi2_frame.Buffer);
    NetManager_SendGameMessage(
      0,
      (int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle,
      NETWORKQUEUE_GUARANTEED,
      &igi2_frame.ptGameMessage,
      0x10u);
    v6 = Flow_ptFlow;
    if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
    {
      v7 = 5;
LABEL_21:
      v8 = v6->ptNetManagerQTask;
      v9 = v8[6].tQTaskChildren.ptMiddle;
      v10 = Client_eQTaskType;
      v11 = nullptr;
      while ( 1 )
      {
        v11 = v11 ? QTask_GetNextSiblingOfType(v11, v10) : QTask_GetFirstChildOfType(v8, v10);
        if ( !v11 )
          break;
        if ( v11[1].ptNext == v9 )
        {
          v12 = v7--;
          if ( v12 <= 0 )
            break;
          NetManager_BlockRunNetwork(1, 0.20000000298023224);
          v6 = Flow_ptFlow;
          goto LABEL_21;
        }
      }
      if ( NetManager_GetClientFromNetworkID((int)v6->ptNetManagerQTask[6].tQTaskChildren.ptMiddle) )
        NetManager_LogMessage("LeaveGame: Server did not respond to client destroy message, quitting anyway\n");
      else
        NetManager_LogMessage("LeaveGame: Server responded to client destroy message\n");
    }
    NetManager_ClearBuffer();
  }
  else
  {
    NetManager_LogMessage("LeaveGame: No net running, no player to destroy\n");
  }
}

// source: j/0/network/netmanager.c:5876  [anchor-strings]
struct NetManager_s *__cdecl NetManager_KickIdle(struct NetManager_s *ptNetManager)
{
  int nAutoKick; // ebx
  struct Client_s *v2; // edi
  unsigned __int16 v3; // dx
  int v4; // esi
  DWORD PerformanceCounter; // eax
  DWORD v6; // eax
  char zTemp[256]; // [esp+8h] [ebp-100h] BYREF

  nAutoKick = ptNetManager->tServerGameSettings.nAutoKick;
  v2 = nullptr;
  if ( nAutoKick > 0 )
  {
    if ( nAutoKick < 30 )
      nAutoKick = 30;
LABEL_4:
    v3 = Client_eQTaskType;
    while ( 1 )
    {
      ptNetManager = (struct NetManager_s *)(v2
                                           ? QTask_GetNextSiblingOfType(&v2->tQTask, v3)
                                           : QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, v3));
      v2 = (struct Client_s *)ptNetManager;
      if ( !ptNetManager )
        break;
      v4 = *(_DWORD *)(ptNetManager->tReceiveCounters.tCounters[23].nCounter + 8);
      if ( *(_WORD *)(v4 + 36) == HumanRemote_eQTaskType )
      {
        if ( Timer_isPerformanceCounter )
          PerformanceCounter = Timer_GetPerformanceCounter();
        else
          PerformanceCounter = GetTickCount();
        v6 = PerformanceCounter - Timer_nStartTime;
        if ( !*(_BYTE *)(v4 + 1180) && *(_BYTE *)(v4 + 1181) && (int)(v6 - *(_DWORD *)(v4 + 3292)) > 1000 * nAutoKick )
        {
          _snprintf(zTemp, 0xFFu, "NetManager: Idle Client[%d]\n", v2->eNetworkID);
          NetManager_LogMessage(zTemp);
          Server_DestroyPlayer(v2, NETMANAGER_DESTROYPLAYER_REASON_IDLING);
          return ptNetManager;
        }
        goto LABEL_4;
      }
    }
  }
  return ptNetManager;
}

// source: j/0/network/netmanager.c:5923  [anchor-strings]
void __cdecl NetManager_DropWeapon(int eClientNetworkID, int eWeaponID)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s *v25; };
    struct { char igi2_o1[16]; float vBeta; };
    struct { char igi2_o2[20]; int v27; };
    struct { char igi2_o3[24]; struct real32x9_t *ptDest; };
    struct { char igi2_o4[28]; float vAlpha; };
    struct { char igi2_o5[32]; struct real32x9_t *ptOrientation; };
    struct { char igi2_o6[36]; char *pzWeaponType; };
    struct { char igi2_o7[40]; struct QTask_s *ptQTask; };
    struct { char igi2_o8[44]; struct real64x3_t v33; };
    struct { char igi2_o9[68]; struct NetManagerGameMessage_s ptGameMessage; };
    struct { char igi2_o10[76]; _BYTE v35[24]; };
    struct { char igi2_o11[100]; struct real32x9_t *v36; };
    struct { char igi2_o12[104]; float v37; };
    struct { char igi2_o13[108]; float v38; };
    struct { char igi2_o14[112]; struct real32x9_t *v39; };
    struct { char igi2_o15[116]; int v40; };
    struct { char igi2_o16[120]; int v41; };
    struct { char igi2_o17[124]; int v42; };
    struct { char igi2_o18[128]; _DWORD v43[3]; };
    struct { char igi2_o19[140]; struct real32x9_t ptPos; };
    struct { char igi2_o20[180]; char Buffer[256]; };
    char igi2_extent[436];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // esi
  struct WeaponType_s *WeaponTypeFromID; // ebx
  double v4; // st7
  double *v5; // esi
  int v6; // esi
  struct Game_s *v7; // eax
  unsigned int v8; // ecx
  unsigned int v9; // edi
  unsigned int v10; // edx
  int v11; // ecx
  unsigned int v12; // edx
  int v13; // ecx
  unsigned int v14; // edx
  struct QTask_s *v15; // esi
  DWORD PerformanceCounter; // eax
  int ptMiddle_low; // edx
  int v18; // edi
  struct WeaponTypeItem_s *WeaponTypeItemFromWeaponType; // eax
  int v20; // esi
  float *p_vY; // ebx
  unsigned __int16 v22; // dx
  struct QTask_s *v23; // eax
  int ptNext; // eax

  igi2_frame.ptQTask = nullptr;
  v2 = *(_DWORD *)(NetManager_GetClientFromNetworkID(eClientNetworkID)->tReceiveTimeBuffer.nCounter + 8);
  igi2_frame.v27 = v2;
  WeaponTypeFromID = WeaponType_GetWeaponTypeFromID(eWeaponID);
  igi2_frame.v25 = *(struct QTask_s **)(v2 + 1320);
  igi2_frame.pzWeaponType = WeaponTypeFromID->zWeaponScriptID;
  if ( Weapon_IsWeaponSelectable(igi2_frame.v25, WeaponTypeFromID->zWeaponScriptID) )
  {
    if ( QTask_IsQTaskTypeDerived(*(_WORD *)(v2 + 36), HumanRemote_eQTaskType) )
    {
      v4 = *(double *)(v2 + 3208);
      v5 = (double *)(v2 + 3192);
      if ( sqrt(*v5 * *v5 + v5[1] * v5[1] + v4 * v4) < 0.10000000149011612 )
        NetManager_LogMessage((char *)&g_ptNetManager.anRunTimer[7]);
      qmemcpy(&igi2_frame.v33, v5, sizeof(igi2_frame.v33));
      v6 = igi2_frame.v27;
      *(float *)&igi2_frame.ptDest = *(double *)(igi2_frame.v27 + 3216);
      igi2_frame.vAlpha = *(double *)(igi2_frame.v27 + 3224);
      igi2_frame.vBeta = *(double *)(igi2_frame.v27 + 3232);
      Real32x9_Create(&igi2_frame.ptPos, *(float *)&igi2_frame.ptDest, igi2_frame.vAlpha, igi2_frame.vBeta);
    }
    else
    {
      qmemcpy(&igi2_frame.v33, (void *)(v2 + 40), sizeof(igi2_frame.v33));
      qmemcpy(&igi2_frame.ptPos, (void *)(igi2_frame.v27 + 124), sizeof(igi2_frame.ptPos));
      Real32x9_GetAngles(&igi2_frame.ptPos, (float *)&igi2_frame.ptDest, &igi2_frame.vAlpha, &igi2_frame.vBeta);
      v6 = igi2_frame.v27;
    }
    v7 = Game_ptGame;
    v8 = Game_ptGame->tRunRandomState.anRandom[2];
    v9 = Game_ptGame->tRunRandomState.anRandom[1];
    v10 = Game_ptGame->tRunRandomState.anRandom[0] >> 7;
    igi2_frame.v33.vZ = igi2_frame.v33.vZ + 4096.0;
    v11 = v10 ^ v8;
    v12 = Game_ptGame->tRunRandomState.anRandom[0];
    Game_ptGame->tRunRandomState.anRandom[2] = v11;
    v13 = v11 ^ v9;
    v14 = v13 + v12;
    v7->tRunRandomState.anRandom[1] = v13;
    v7->tRunRandomState.anRandom[0] = v14;
    *(float *)&igi2_frame.ptOrientation = (double)(unsigned __int16)v14 * 0.0000152587890625 * 1.5707963705062866 + igi2_frame.vBeta - 0.7853981852531433;
    v15 = GunPickup_NewFromWeapon(
            *(struct QTask_s **)(v6 + 1320),
            WeaponTypeFromID,
            &igi2_frame.v33,
            &igi2_frame.ptPos,
            *(float *)&igi2_frame.ptOrientation,
            true);
    igi2_frame.ptGameMessage.eGameMessage = 1146244944;
    if ( Timer_isPerformanceCounter )
      PerformanceCounter = Timer_GetPerformanceCounter();
    else
      PerformanceCounter = GetTickCount();
    ptMiddle_low = LOWORD(v15[11].tQTaskChildren.ptMiddle);
    igi2_frame.v43[2] = eClientNetworkID;
    igi2_frame.ptGameMessage.nLocalTime = PerformanceCounter - Timer_nStartTime;
    igi2_frame.v41 = ptMiddle_low;
    qmemcpy(igi2_frame.v35, &igi2_frame.v33, sizeof(igi2_frame.v35));
    igi2_frame.v36 = igi2_frame.ptDest;
    igi2_frame.v37 = igi2_frame.vAlpha;
    igi2_frame.v38 = igi2_frame.vBeta;
    igi2_frame.v39 = igi2_frame.ptOrientation;
    igi2_frame.v40 = eWeaponID;
    if ( WeaponTypeFromID )
    {
      v18 = igi2_frame.v27;
      WeaponTypeItemFromWeaponType = Weapon_GetWeaponTypeItemFromWeaponType(
                                       *(struct QTask_s **)(igi2_frame.v27 + 1320),
                                       igi2_frame.pzWeaponType);
      if ( WeaponTypeItemFromWeaponType )
      {
        igi2_frame.v42 = WeaponTypeItemFromWeaponType->anFireTypeAmmoCount[0];
        WeaponType_GetAmmoInfo(WeaponTypeFromID, (struct WeaponTypeGetAmmoInfoContext_s *)&igi2_frame.ptPos);
        v20 = 0;
        p_vY = &igi2_frame.ptPos.tX.vY;
        do
        {
          if ( *(_DWORD *)p_vY )
            igi2_frame.v43[v20] = Weapon_GetAmmoTypeItemFromAmmoType(
                         *(struct QTask_s **)(v18 + 1320),
                         (char *)(*(_DWORD *)p_vY + 40))->nAmmoCount;
          else
            igi2_frame.v43[v20] = 0;
          ++v20;
          p_vY += 5;
        }
        while ( v20 < 2 );
      }
      Weapon_DisableWeaponType(*(struct QTask_s **)(v18 + 1320), igi2_frame.pzWeaponType, true);
    }
LABEL_20:
    v22 = Client_eQTaskType;
    while ( 1 )
    {
      v23 = igi2_frame.ptQTask
          ? QTask_GetNextSiblingOfType(igi2_frame.ptQTask, v22)
          : QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, v22);
      igi2_frame.ptQTask = v23;
      if ( !v23 )
        break;
      ptNext = (int)v23[1].ptNext;
      if ( ptNext )
      {
        NetManager_SendGameMessage(ptNext, 0, NETWORKQUEUE_GUARANTEED, &igi2_frame.ptGameMessage, 0x48u);
        goto LABEL_20;
      }
    }
  }
  else
  {
    _snprintf(
      igi2_frame.Buffer,
      0xFFu,
      (char *const)&g_ptNetManager.anRunTimer[19],
      eClientNetworkID,
      WeaponTypeFromID->zWeaponScriptID);
    NetManager_LogMessage(igi2_frame.Buffer);
  }
}

// source: j/0/network/netmanager.c:6103  [anchor-callee]
void __cdecl NetManager_RequestDropWeapon()
{
  #pragma pack(push, 1)
  union
  {
    struct { struct NetManagerGameMessage_s ptGameMessage; };
    struct { char igi2_o1[8]; struct ClientGameMessageDrop_s tGameMessageDrop; };
    char igi2_extent[76];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptTail; // edi
  struct QTask_s *ptNetManagerQTask; // esi
  DWORD PerformanceCounter; // eax
  struct QReference_s *ptMiddle; // edx
  struct QReference_s *v5; // ebx
  int v6; // esi
  struct QTask_s *v7; // ecx

  ptPrev = HumanPlayer_ptQTask[33].ptNext[1].ptPrev;
  if ( ptPrev )
    ptTail = ptPrev->tQTaskChildren.ptTail;
  else
    ptTail = nullptr;
  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  igi2_frame.ptGameMessage.eGameMessage = 1381057618;
  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  ptMiddle = ptNetManagerQTask[6].tQTaskRefList.ptMiddle;
  v5 = ptNetManagerQTask[6].tQTaskRefList.ptTail;
  v6 = (int)ptTail[3].tQTaskRefList.ptTail;
  v7 = Flow_ptFlow->ptNetManagerQTask;
  igi2_frame.ptGameMessage.nLocalTime = PerformanceCounter - Timer_nStartTime + ((char *)ptMiddle - (char *)v5);
  *(&igi2_frame.tGameMessageDrop.eNetworkReceivingClientID + 1) = (int)v7[6].tQTaskChildren.ptMiddle;
  igi2_frame.tGameMessageDrop.iNewGameItemID = v6;
  if ( v6 != Script_ParseLineInt32("WEAPON_ID_KNIFE") )
    NetManager_SendGameMessage(
      0,
      (int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle,
      NETWORKQUEUE_GUARANTEED,
      &igi2_frame.ptGameMessage,
      0x48u);
}

// source: j/0/network/netmanager.c:6143  [anchor-callee]
void __cdecl NetManager_RunClientPing(struct NetManager_s *ptNetManager)
{
  DWORD PerformanceCounter; // eax
  int v2; // esi
  DWORD TickCount; // eax
  struct QTask_s *ptMiddle; // ecx
  struct ServerGameMessagePing_s tGameMessage; // [esp+8h] [ebp-8h] BYREF

  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  v2 = PerformanceCounter - Timer_nStartTime;
  if ( (int)(PerformanceCounter - Timer_nStartTime - ptNetManager->nLastPingTime) > 3000 )
  {
    tGameMessage.tBaseMessage.eGameMessage = 1346981447;
    if ( Timer_isPerformanceCounter )
      TickCount = Timer_GetPerformanceCounter();
    else
      TickCount = GetTickCount();
    ptMiddle = Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle;
    tGameMessage.tBaseMessage.nLocalTime = TickCount - Timer_nStartTime;
    NetManager_SendGameMessage(0, (int)ptMiddle, NETWORKQUEUE_MEDIUMPRIORITY, &tGameMessage.tBaseMessage, 8u);
    ptNetManager->nLastPingTime = v2;
  }
}

// source: j/0/network/netmanager.c:6182  [anchor-strings]
void __cdecl NetManager_RunAlways(struct NetManager_s *ptNetManager, char *zCaller)
{
  DWORD PerformanceCounter; // eax
  int nBandwidth; // ecx
  DWORD TickCount; // eax
  int v5; // eax
  struct QTask_s *ptNetManagerQTask; // ecx
  struct QTask_s *ptParent; // eax
  struct QReference_s *v8; // esi
  DWORD v9; // eax
  DWORD v10; // eax
  DWORD v11; // eax
  void *pxClientInterface; // esi
  char zTemp[256]; // [esp+8h] [ebp-100h] BYREF

  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  nBandwidth = ptNetManager->tStatsPrTick.nBandwidth;
  if ( nBandwidth == PerformanceCounter - Timer_nStartTime )
    return;
  if ( nBandwidth != -1 )
  {
    if ( Timer_isPerformanceCounter )
      TickCount = Timer_GetPerformanceCounter();
    else
      TickCount = GetTickCount();
    v5 = TickCount - Timer_nStartTime - ptNetManager->tStatsPrTick.nBandwidth;
    ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
    if ( *((_DWORD *)&ptNetManagerQTask[31].tQTaskChildren.ptTail + (int)ptNetManagerQTask[32].tQTaskChildren.ptTail)
      && v5 > 1000 )
    {
      _snprintf(zTemp, 0xFFu, (char *const)&g_ptNetManager.nBufferStateIndex, 1000, v5);
LABEL_15:
      NetManager_LogMessage(zTemp);
      goto LABEL_16;
    }
    if ( !*((_DWORD *)&ptNetManagerQTask[31].tQTaskChildren.ptTail + (int)ptNetManagerQTask[32].tQTaskChildren.ptTail)
      && v5 > 200 )
    {
      _snprintf(zTemp, 0xFFu, (char *const)&g_ptNetManager.aBufferState[3], 200, v5);
      goto LABEL_15;
    }
  }
LABEL_16:
  if ( ptNetManager->tStatsPrTick.nBandwidth != -1 )
  {
    ptParent = ptNetManager[1].tQTask.ptParent;
    v8 = ptParent
       ? (struct QReference_s *)ptNetManager->anRunTimer[(_DWORD)ptParent + 14]
       : ptNetManager[1].tQTask.tQTaskRefList.ptTail;
    v9 = Timer_isPerformanceCounter ? Timer_GetPerformanceCounter() : GetTickCount();
    if ( (int)(v9 - Timer_nStartTime - (_DWORD)v8) > 20 )
    {
      if ( Timer_isPerformanceCounter )
        v10 = Timer_GetPerformanceCounter();
      else
        v10 = GetTickCount();
      ptNetManager->anRunTimer[(int)ptNetManager[1].tQTask.ptParent + 15] = v10 - Timer_nStartTime;
      ptNetManager[1].tQTask.ptParent = (struct QTask_s *)(((int)&ptNetManager[1].tQTask.ptParent->ptNext + 1) % 30);
    }
  }
  if ( Timer_isPerformanceCounter )
    v11 = Timer_GetPerformanceCounter();
  else
    v11 = GetTickCount();
  ptNetManager->tStatsPrTick.nBandwidth = v11 - Timer_nStartTime;
  if ( ptNetManager->pxServerInterface )
    NetManager_RunServerAlways(ptNetManager);
  pxClientInterface = ptNetManager->pxClientInterface;
  if ( pxClientInterface )
    Network_RunClient(pxClientInterface);
  if ( ptNetManager->pxClientInterface || ptNetManager->pxServerInterface )
  {
    NetManager_TriggerReceiveQueue();
    Network_HandleSendQueues();
  }
}

// source: j/0/network/netmanager.c:6278  [anchor-mhash]
enum bool __cdecl NetManager_IsNetworkConnected()
{
  return Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptHead->ptNext == (struct QTask_s *)2;
}

// source: j/0/network/netmanager.c:6299  [anchor-strings]
enum bool __cdecl NetManager_BlockClientConnect(int nSeconds, int nSleepMilliseconds)
{
  #pragma pack(push, 1)
  union
  {
    struct { int nStartTimer; };
    struct { char igi2_o1[4]; char zTemp[256]; };
    char igi2_extent[260];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptNetManagerQTask; // esi
  int v3; // ebx
  int v4; // edi
  DWORD v5; // eax

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  if ( Timer_isPerformanceCounter )
  {
    v3 = Timer_GetPerformanceCounter() - Timer_nStartTime;
    igi2_frame.nStartTimer = v3;
  }
  else
  {
    igi2_frame.nStartTimer = GetTickCount() - Timer_nStartTime;
    v3 = igi2_frame.nStartTimer;
  }
  v4 = 0;
  while ( 1 )
  {
    v5 = Timer_isPerformanceCounter ? Timer_GetPerformanceCounter() : GetTickCount();
    if ( (int)(v5 - Timer_nStartTime - v3) >= 1000 * nSeconds
      || ptNetManagerQTask[6].tQTaskChildren.ptHead->ptNext != (struct QTask_s *)1 )
    {
      break;
    }
    _snprintf(igi2_frame.zTemp, 0xFFu, (char *const)&g_ptNetManager.tStatsPrTick.nSentBytes, ++v4);
    NetManager_LogMessage(igi2_frame.zTemp);
    Network_PostLoadServerContact(
      ptNetManagerQTask[6].tQTaskChildren.ptHead,
      ClientConfig_tClientConfig.zPlayerPassword);
    if ( ptNetManagerQTask[6].tQTaskChildren.ptHead->ptNext != (struct QTask_s *)1 )
    {
      NetManager_LogMessage((char *)&g_ptNetManager.nLastAlwaysRun);
      return ptNetManagerQTask[6].tQTaskChildren.ptHead->ptNext != (struct QTask_s *)1;
    }
    NetManager_LogMessage((char *)&g_ptNetManager.tSendCounters.tCounters[25]);
    Sleep(nSleepMilliseconds);
    v3 = igi2_frame.nStartTimer;
  }
  return ptNetManagerQTask[6].tQTaskChildren.ptHead->ptNext != (struct QTask_s *)1;
}

// source: j/0/network/netmanager.c:6350  [anchor-strings]
void __cdecl NetManager_BlockRunNetwork(int nSeconds, float vPeriod)
{
  struct QTask_s *ptNetManagerQTask; // edi
  DWORD PerformanceCounter; // eax
  DWORD v4; // ebp
  DWORD v5; // eax
  char *v6; // ecx

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  v4 = PerformanceCounter - Timer_nStartTime;
  while ( 1 )
  {
    v5 = Timer_isPerformanceCounter ? Timer_GetPerformanceCounter() : GetTickCount();
    if ( (int)(v5 - Timer_nStartTime - v4) >= 1000 * nSeconds )
      break;
    ptNetManagerQTask[36].ptPrev = nullptr;
    NetManager_RunAlways((struct NetManager_s *)ptNetManagerQTask, v6);
    Sleep((__int64)(vPeriod * 1000.0));
  }
}

// source: j/0/network/netmanager.c:6376  [anchor-strings]
enum bool __cdecl NetManager_PrintFPS(char *zText)
{
  DWORD PerformanceCounter; // eax
  DWORD TickCount; // eax
  int v3; // eax

  if ( Flow_ptFlow->nTicksDrawn < dword_7086C0 )
  {
    dword_7086C0 = Flow_ptFlow->nTicksDrawn;
    if ( Timer_isPerformanceCounter )
      PerformanceCounter = Timer_GetPerformanceCounter();
    else
      PerformanceCounter = GetTickCount();
    dword_7086C4 = PerformanceCounter - Timer_nStartTime;
  }
  if ( Flow_ptFlow->nTicksDrawn - dword_7086C0 < 30 )
    return false;
  if ( Timer_isPerformanceCounter )
    TickCount = Timer_GetPerformanceCounter();
  else
    TickCount = GetTickCount();
  v3 = TickCount - Timer_nStartTime;
  if ( v3 != dword_7086C4 )
    flt_704A98 = 30.0 / ((double)(v3 - dword_7086C4) * 0.0010000000474974513);
  dword_7086C4 = v3;
  dword_7086C0 = Flow_ptFlow->nTicksDrawn;
  sprintf(zText, (char *const)&g_ptNetManager.tSendCounters.tCounters[22].nCounter, flt_704A98);
  return true;
}

// source: j/0/network/netmanager.c:6436  [anchor-strings]
void __cdecl NetManager_KeyPressedHandler(unsigned __int64 nInputPort)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct NetManager_s *ptNetManager; };
    struct { char igi2_o1[4]; struct Client_s *ptClient; };
    struct { char igi2_o2[8]; struct NetManagerGameMessage_s ptGameMessage; };
    struct { char igi2_o3[16]; struct QTask_s *v41; };
    struct { char igi2_o4[20]; int v42; };
    char igi2_extent[28];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Client_s *ClientFromNetworkID; // eax
  struct QTask_s *v2; // esi
  enum NetManagerMode_e v3; // eax
  enum NetManagerMode_e v4; // ebp
  char *LocalizedStringForLanguage; // eax
  struct Client_s *v6; // eax
  enum NetManagerMode_e v7; // ebp
  char *v8; // eax
  struct Client_s *v9; // eax
  struct SlotCategory_s *ptActiveCategory; // eax
  enum NetManagerMode_e v11; // ebp
  char *v12; // eax
  struct Client_s *v13; // eax
  struct QTask_s *ptMiddle; // edi
  struct QTask_s *v15; // eax
  bool v16; // zf
  enum NetManagerMode_e v17; // ebp
  char *v18; // eax
  struct Client_s *v19; // eax
  struct QTask_s *v20; // esi
  enum NetManagerMode_e v21; // ebp
  char *v22; // eax
  struct Client_s *v23; // eax
  struct QTask_s *v24; // eax
  struct NetManager_s *v25; // edi
  int v26; // eax
  int v27; // eax
  enum NetManagerMode_e v28; // ebp
  char *v29; // eax
  struct Client_s *v30; // eax
  struct QTask_s *v31; // esi
  struct QTask_s *ptNetManagerQTask; // esi
  DWORD PerformanceCounter; // eax
  int v34; // ecx
  struct QTask_s *v35; // eax
  int eSpectateNetworkID; // edx
  int nDeathTimer; // eax

  igi2_frame.ptNetManager = (struct NetManager_s *)Flow_ptFlow->ptNetManagerQTask;
  ClientFromNetworkID = NetManager_GetClientFromNetworkID(igi2_frame.ptNetManager->eLocalNetworkID);
  v2 = MenuManager_ptQTask;
  igi2_frame.ptClient = ClientFromNetworkID;
  if ( MenuManager_ptQTask && MenuManager_ptQTask[1].tQTaskChildren.ptMiddle != (struct QTask_s *)10 )
  {
    if ( Game_eGameMode != GAME_GAMEMODE_MULTIPLAYER )
      goto LABEL_116;
    v3 = NetManager_eMode;
  }
  else if ( Game_eGameMode != GAME_GAMEMODE_MULTIPLAYER
         || (v3 = NetManager_eMode, NetManager_eMode == NETMANAGER_MODE_PLAY)
         || NetManager_eMode == NETMANAGER_MODE_WARMUP )
  {
    if ( Netshop_isOpenToLocal() && (nInputPort & 0x8000000000000LL) != 0 )
    {
      if ( Netshop_isAmmoEnabled(1) )
        Netshop_AmmoPicked(nullptr, nullptr, nullptr, 1);
      v2 = MenuManager_ptQTask;
    }
    if ( Netshop_isOpenToLocal() && (nInputPort & 0x10000000000000LL) != 0 )
    {
      if ( Netshop_isAmmoEnabled(2) )
        Netshop_AmmoPicked(nullptr, nullptr, nullptr, 2);
      v2 = MenuManager_ptQTask;
    }
    if ( Netshop_isOpenToLocal() && (nInputPort & 0x20000000000LL) != 0 )
    {
      if ( v2 )
        HIBYTE(v2[243].eQTaskType) = 1;
      NetManager_SetMode(3);
      v2 = MenuManager_ptQTask;
    }
    if ( (nInputPort & 0x20000000) != 0 )
    {
      if ( v2 )
        HIBYTE(v2[243].eQTaskType) = 1;
      SlotSelector_ptActiveSelector = (struct SlotSelector_s *)QTask_GetFirstChildOfType(
                                                                 Flow_ptFlow->ptNetManagerQTask,
                                                                 RadioCom_eQTaskType)[1].ptNext;
      SlotSelector_SetActiveCategory(1);
      v4 = NETMANAGER_MODE_RADIO;
      if ( BYTE2(Flow_ptFlow->ptNetManagerQTask[5].tQTaskChildren.ptTail) )
      {
        if ( NetManager_ForceChangeTeam() )
        {
          v4 = NETMANAGER_MODE_SELECTSKIN;
          LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                         "mp/FORCE_TEAM_CHANGE",
                                         Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                         true);
          StatusScreen_ShowMessage(LocalizedStringForLanguage, TEXTSCROLLER_COLOUR_WHITE);
          NetManager_nBodySprite = 0;
          NetManager_nFaceSprite = 0;
          NetManager_isModelSelect = true;
        }
        v2 = MenuManager_ptQTask;
      }
      v6 = NetManager_GetClientFromNetworkID((int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
      if ( v6 )
        NetManager_eTeam = v6->eTeam;
      NetManager_eMode = v4;
      LOBYTE(v2[243].eQTaskType) = 1;
      switch ( v4 )
      {
        case NETMANAGER_MODE_SELECTSKIN:
          if ( !LOBYTE(HumanPlayer_ptQTask[29].tQTaskRefList.ptHead) )
          {
            NetManager_KillClient((int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
            v2 = MenuManager_ptQTask;
          }
          v2[1].ptNext = (struct QTask_s *)996;
          v2[1].tQTaskChildren.ptMiddle = nullptr;
          break;
        case NETMANAGER_MODE_RADIO:
          LOBYTE(v2[243].eQTaskType) = 0;
          v2[1].ptNext = (struct QTask_s *)908;
          v2[1].tQTaskChildren.ptMiddle = (struct QTask_s *)2;
          break;
      }
    }
    if ( (nInputPort & 0x20000000000000LL) != 0 )
    {
      if ( v2 )
        HIBYTE(v2[243].eQTaskType) = 1;
      SlotSelector_ptActiveSelector = (struct SlotSelector_s *)QTask_GetFirstChildOfType(
                                                                 Flow_ptFlow->ptNetManagerQTask,
                                                                 RadioCom_eQTaskType)[1].ptNext;
      SlotSelector_SetActiveCategory(2);
      v7 = NETMANAGER_MODE_RADIO;
      if ( BYTE2(Flow_ptFlow->ptNetManagerQTask[5].tQTaskChildren.ptTail) )
      {
        if ( NetManager_ForceChangeTeam() )
        {
          v7 = NETMANAGER_MODE_SELECTSKIN;
          v8 = Config_GetLocalizedStringForLanguage(
                 "mp/FORCE_TEAM_CHANGE",
                 Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                 true);
          StatusScreen_ShowMessage(v8, TEXTSCROLLER_COLOUR_WHITE);
          NetManager_nBodySprite = 0;
          NetManager_nFaceSprite = 0;
          NetManager_isModelSelect = true;
        }
        v2 = MenuManager_ptQTask;
      }
      v9 = NetManager_GetClientFromNetworkID((int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
      if ( v9 )
        NetManager_eTeam = v9->eTeam;
      NetManager_eMode = v7;
      LOBYTE(v2[243].eQTaskType) = 1;
      switch ( v7 )
      {
        case NETMANAGER_MODE_SELECTSKIN:
          if ( !LOBYTE(HumanPlayer_ptQTask[29].tQTaskRefList.ptHead) )
          {
            NetManager_KillClient((int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
            v2 = MenuManager_ptQTask;
          }
          v2[1].ptNext = (struct QTask_s *)996;
          v2[1].tQTaskChildren.ptMiddle = nullptr;
          break;
        case NETMANAGER_MODE_RADIO:
          LOBYTE(v2[243].eQTaskType) = 0;
          v2[1].ptNext = (struct QTask_s *)908;
          v2[1].tQTaskChildren.ptMiddle = (struct QTask_s *)2;
          break;
      }
    }
    if ( (nInputPort & 0x800000000000LL) != 0 )
      NetManager_SetMode(0);
    goto LABEL_116;
  }
  if ( v3 == NETMANAGER_MODE_RADIO )
  {
    if ( (nInputPort & 0x20000000) != 0 )
    {
      RadioCom_SetActiveSlotSelector();
      if ( !SlotSelector_ptActiveSelector
        || (ptActiveCategory = SlotSelector_ptActiveSelector->ptActiveCategory) == nullptr
        || ptActiveCategory->nCategory != 1 )
      {
        SlotSelector_SetActiveCategory(1);
        goto LABEL_116;
      }
      MenuManager_LeaveMenues(908, 10, false);
      v11 = NETMANAGER_MODE_PLAY;
      if ( BYTE2(Flow_ptFlow->ptNetManagerQTask[5].tQTaskChildren.ptTail) && NetManager_ForceChangeTeam() )
      {
        v11 = NETMANAGER_MODE_SELECTSKIN;
        v12 = Config_GetLocalizedStringForLanguage(
                "mp/FORCE_TEAM_CHANGE",
                Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                true);
        StatusScreen_ShowMessage(v12, TEXTSCROLLER_COLOUR_WHITE);
        NetManager_nBodySprite = 0;
        NetManager_nFaceSprite = 0;
        NetManager_isModelSelect = true;
      }
      if ( NetMission_isWarmUp && v11 == NETMANAGER_MODE_PLAY )
      {
        NetManager_eMode = NETMANAGER_MODE_WARMUP;
      }
      else
      {
        v13 = NetManager_GetClientFromNetworkID((int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
        if ( v13 )
          NetManager_eTeam = v13->eTeam;
        NetManager_eMode = v11;
      }
      v2 = MenuManager_ptQTask;
      LOBYTE(MenuManager_ptQTask[243].eQTaskType) = 1;
      switch ( v11 )
      {
        case NETMANAGER_MODE_SELECTSKIN:
          if ( LOBYTE(HumanPlayer_ptQTask[29].tQTaskRefList.ptHead) )
            goto LABEL_104;
          ptMiddle = Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle;
          break;
        case NETMANAGER_MODE_PLAY:
          goto LABEL_70;
      }
LABEL_103:
      NetManager_KillClient((int)ptMiddle);
      v2 = MenuManager_ptQTask;
LABEL_104:
      v2[1].ptNext = (struct QTask_s *)996;
      v2[1].tQTaskChildren.ptMiddle = nullptr;
    }
    else
    {
      if ( (nInputPort & 0x20000000000000LL) == 0 )
        goto LABEL_116;
      RadioCom_SetActiveSlotSelector();
      if ( SlotSelector_GetActiveCategoryIfAny() != 2 )
      {
        SlotSelector_SetActiveCategory(2);
        goto LABEL_116;
      }
      MenuManager_LeaveMenues(908, 10, false);
      v17 = NETMANAGER_MODE_PLAY;
      if ( BYTE2(Flow_ptFlow->ptNetManagerQTask[5].tQTaskChildren.ptTail) && NetManager_ForceChangeTeam() )
      {
        v17 = NETMANAGER_MODE_SELECTSKIN;
        v18 = Config_GetLocalizedStringForLanguage(
                "mp/FORCE_TEAM_CHANGE",
                Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                true);
        StatusScreen_ShowMessage(v18, TEXTSCROLLER_COLOUR_WHITE);
        NetManager_nBodySprite = 0;
        NetManager_nFaceSprite = 0;
        NetManager_isModelSelect = true;
      }
      if ( NetMission_isWarmUp && v17 == NETMANAGER_MODE_PLAY )
      {
        NetManager_eMode = NETMANAGER_MODE_WARMUP;
      }
      else
      {
        v19 = NetManager_GetClientFromNetworkID((int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
        if ( v19 )
          NetManager_eTeam = v19->eTeam;
        NetManager_eMode = v17;
      }
      v2 = MenuManager_ptQTask;
      LOBYTE(MenuManager_ptQTask[243].eQTaskType) = 1;
      switch ( v17 )
      {
        case NETMANAGER_MODE_SELECTSKIN:
          if ( LOBYTE(HumanPlayer_ptQTask[29].tQTaskRefList.ptHead) )
            goto LABEL_104;
          ptMiddle = Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle;
          goto LABEL_103;
        case NETMANAGER_MODE_PLAY:
LABEL_70:
          v15 = HumanPlayer_ptQTask;
          v16 = HumanPlayer_ptQTask == nullptr;
          LOBYTE(v2[243].eQTaskType) = 0;
          if ( !v16 && LOBYTE(v15[29].tQTaskRefList.ptHead) )
          {
            NetManager_SetMode(2);
            v2 = MenuManager_ptQTask;
          }
          break;
      }
    }
    if ( Game_eGameMode != GAME_GAMEMODE_MULTIPLAYER )
      goto LABEL_116;
  }
  if ( NetManager_eMode == NETMANAGER_MODE_SHOP && (nInputPort & 0x20000000000LL) != 0 )
  {
    if ( v2 )
      HIBYTE(v2[243].eQTaskType) = 1;
    MenuManager_LeaveMenues(907, 10, false);
    v20 = MenuManager_ptQTask;
    if ( MenuManager_ptQTask )
      HIBYTE(MenuManager_ptQTask[243].eQTaskType) = 0;
    v21 = NETMANAGER_MODE_PLAY;
    if ( BYTE2(Flow_ptFlow->ptNetManagerQTask[5].tQTaskChildren.ptTail) )
    {
      if ( NetManager_ForceChangeTeam() )
      {
        v21 = NETMANAGER_MODE_SELECTSKIN;
        v22 = Config_GetLocalizedStringForLanguage(
                "mp/FORCE_TEAM_CHANGE",
                Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                true);
        StatusScreen_ShowMessage(v22, TEXTSCROLLER_COLOUR_WHITE);
        NetManager_nBodySprite = 0;
        NetManager_nFaceSprite = 0;
        NetManager_isModelSelect = true;
      }
      v20 = MenuManager_ptQTask;
    }
    if ( NetMission_isWarmUp && v21 == NETMANAGER_MODE_PLAY )
    {
      NetManager_eMode = NETMANAGER_MODE_WARMUP;
    }
    else
    {
      v23 = NetManager_GetClientFromNetworkID((int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
      if ( v23 )
        NetManager_eTeam = v23->eTeam;
      NetManager_eMode = v21;
    }
    LOBYTE(v20[243].eQTaskType) = 1;
    switch ( v21 )
    {
      case NETMANAGER_MODE_SELECTSKIN:
        if ( !LOBYTE(HumanPlayer_ptQTask[29].tQTaskRefList.ptHead) )
        {
          NetManager_KillClient((int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
          v20 = MenuManager_ptQTask;
        }
        v20[1].ptNext = (struct QTask_s *)996;
        v20[1].tQTaskChildren.ptMiddle = nullptr;
        break;
      case NETMANAGER_MODE_PLAY:
        v24 = HumanPlayer_ptQTask;
        v16 = HumanPlayer_ptQTask == nullptr;
        LOBYTE(v20[243].eQTaskType) = 0;
        if ( !v16 && LOBYTE(v24[29].tQTaskRefList.ptHead) )
          NetManager_SetMode(2);
        break;
    }
  }
LABEL_116:
  Client_UpdateTalk(igi2_frame.ptClient);
  v25 = igi2_frame.ptNetManager;
  if ( NetManager_eMode == NETMANAGER_MODE_SPAWN )
    NetManager_UpdateSpawn(igi2_frame.ptNetManager, nInputPort);
  v26 = *(_DWORD *)&igi2_frame.ptNetManager[1].tServerGameSettings.zServerName[4];
  if ( v26 <= 0 || (v27 = v26 - 1, (*(_DWORD *)&igi2_frame.ptNetManager[1].tServerGameSettings.zServerName[4] = v27) != 0) )
  {
    v31 = MenuManager_ptQTask;
  }
  else
  {
    v28 = NETMANAGER_MODE_COMPLETE;
    if ( BYTE2(Flow_ptFlow->ptNetManagerQTask[5].tQTaskChildren.ptTail) && NetManager_ForceChangeTeam() )
    {
      v29 = Config_GetLocalizedStringForLanguage(
              "mp/FORCE_TEAM_CHANGE",
              Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
              true);
      StatusScreen_ShowMessage(v29, TEXTSCROLLER_COLOUR_WHITE);
      v28 = NETMANAGER_MODE_SELECTSKIN;
      NetManager_nBodySprite = 0;
      NetManager_nFaceSprite = 0;
      NetManager_isModelSelect = true;
    }
    v30 = NetManager_GetClientFromNetworkID((int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
    if ( v30 )
      NetManager_eTeam = v30->eTeam;
    v25 = igi2_frame.ptNetManager;
    NetManager_eMode = v28;
    v31 = MenuManager_ptQTask;
    LOBYTE(MenuManager_ptQTask[243].eQTaskType) = 1;
    switch ( v28 )
    {
      case NETMANAGER_MODE_SELECTSKIN:
        if ( !LOBYTE(HumanPlayer_ptQTask[29].tQTaskRefList.ptHead) )
        {
          NetManager_KillClient((int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
          v31 = MenuManager_ptQTask;
          v25 = igi2_frame.ptNetManager;
        }
        v31[1].ptNext = (struct QTask_s *)996;
        v31[1].tQTaskChildren.ptMiddle = nullptr;
        break;
      default:
        break;
    }
  }
  if ( NetManager_eMode == NETMANAGER_MODE_SPECTATE
    || NetManager_eMode == NETMANAGER_MODE_WELCOME
    || NetManager_eMode == NETMANAGER_MODE_COMPLETE
    || (unsigned int)NetManager_eMode <= NETMANAGER_MODE_SELECTSKIN )
  {
    NetManager_UpdateSpectating(v25, nInputPort);
    v31 = MenuManager_ptQTask;
  }
  if ( igi2_frame.ptClient->eNetworkIDSpectate != v25->eSpectateNetworkID )
  {
    ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
    igi2_frame.ptGameMessage.eGameMessage = 1397769539;
    if ( Timer_isPerformanceCounter )
      PerformanceCounter = Timer_GetPerformanceCounter();
    else
      PerformanceCounter = GetTickCount();
    v34 = PerformanceCounter
        - Timer_nStartTime
        + (char *)ptNetManagerQTask[6].tQTaskRefList.ptMiddle
        - (char *)ptNetManagerQTask[6].tQTaskRefList.ptTail;
    v35 = Flow_ptFlow->ptNetManagerQTask;
    eSpectateNetworkID = v25->eSpectateNetworkID;
    igi2_frame.ptGameMessage.nLocalTime = v34;
    igi2_frame.v41 = v35[6].tQTaskChildren.ptMiddle;
    igi2_frame.v42 = eSpectateNetworkID;
    NetManager_SendGameMessage(0, (int)igi2_frame.v41, NETWORKQUEUE_GUARANTEED, &igi2_frame.ptGameMessage, 0x10u);
    v31 = MenuManager_ptQTask;
    igi2_frame.ptClient->eNetworkIDSpectate = v25->eSpectateNetworkID;
  }
  if ( NetManager_eMode == NETMANAGER_MODE_DEAD )
  {
    nDeathTimer = v25->nDeathTimer;
    v25->nDeathTimer = nDeathTimer + 1;
    if ( nDeathTimer >= 150 && (!v31 || v31[1].tQTaskChildren.ptMiddle == (struct QTask_s *)10) )
    {
      NetManager_SetMode(2);
      v25->nDeathTimer = 0;
    }
  }
}

// source: j/0/network/netmanager.c:6624  [anchor-hash]
int __cdecl NetManager_RetrieveUnusedNetworkIDs(struct NetManager_s *ptNetManager, int nSeconds)
{
  DWORD PerformanceCounter; // eax
  int result; // eax
  int v5; // ebx
  int i; // edi
  struct QObjectVector_s *ptPrev; // esi
  unsigned int nAllocated; // eax
  int *v9; // ecx

  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  result = PerformanceCounter - Timer_nStartTime - 1000 * nSeconds;
  v5 = result;
  if ( result > 0 )
  {
    for ( i = 1; i < 35; ++i )
    {
      result = (int)NetManager_GetClientFromNetworkID(i);
      if ( !result )
      {
        result = Network_IsItemIDExisitingAndIsCreatedBefore(i, v5);
        if ( result )
        {
          Network_RemoveIDItemFromID(i);
          ptPrev = (struct QObjectVector_s *)QTask_GetFirstChildOfType(
                                               Flow_ptFlow->ptNetManagerQTask,
                                               Server_eQTaskType)[1].ptPrev;
          if ( ptPrev->nAllocated == ptPrev->nSize )
            QObjectVector_Realloc(ptPrev, ptPrev->nReallocSize);
          nAllocated = ptPrev->nAllocated;
          v9 = (int *)ptPrev->papxElement[nAllocated];
          result = nAllocated + 1;
          ptPrev->nAllocated = result;
          *v9 = i;
        }
      }
    }
  }
  return result;
}

// source: j/0/network/netmanager.c:6680  [anchor-callee]
void __cdecl NetManager_AdjustLocalBandwidth(int nPercentage)
{
  struct QTask_s *ptNetManagerQTask; // eax
  struct Client_s *ClientFromNetworkID; // eax
  int v3; // ebx

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  if ( ptNetManagerQTask )
  {
    ClientFromNetworkID = NetManager_GetClientFromNetworkID((int)ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
    if ( ClientFromNetworkID )
    {
      if ( ClientFromNetworkID->eNetworkID )
      {
        v3 = (__int64)((double)(nPercentage * ClientFromNetworkID->tStats.nObjectives) * 0.009999999776482582 + 0.5)
           + ClientFromNetworkID->tStats.nObjectives;
        if ( v3 > 0 )
        {
          if ( v3 > 1000 )
            v3 = 1000;
          NetManager_SetLocalBandwidth(v3);
        }
        else
        {
          NetManager_SetLocalBandwidth(1);
        }
      }
    }
  }
}

// source: j/0/network/netmanager.c:6725  [anchor-strings]
void __cdecl NetManager_SetRemoteBandwidth(struct Client_s *ptRemote, int nBandwidth)
{
  char Buffer[40]; // [esp+0h] [ebp-28h] BYREF

  if ( ptRemote->eNetworkID )
  {
    _snprintf(Buffer, 0x28u, (char *const)&g_ptNetManager.tSendCounters.tCounters[19], nBandwidth);
    NetworkCommand_RemoteEval((char *)ptRemote->eNetworkID, (int)Buffer, NETMANAGER_HOSTSET_GIVEN_DESTINATION);
  }
}

// source: j/0/network/netmanager.c:6756  [anchor-strings]
void __cdecl NetManager_ReduceClientBandwidth(
        struct NetManager_s *ptNetManager,
        struct Client_s *ptClient,
        float vFactor,
        int nMin,
        int nMax)
{
  #pragma pack(push, 1)
  union
  {
    struct { char eSet[40]; };
    struct { char igi2_o1[40]; char Buffer[256]; };
    char igi2_extent[296];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int nObjectives; // eax
  int v6; // esi

  nObjectives = ptClient->tStats.nObjectives;
  if ( nObjectives > nMin )
  {
    v6 = (__int64)((double)ptClient->tStats.nObjectives * vFactor + 0.5);
    if ( v6 > nMax )
      v6 = nMax;
    if ( v6 < nMin )
      v6 = nMin;
    _snprintf(
      igi2_frame.Buffer,
      0xFFu,
      (char *const)&g_ptNetManager.tSendCounters.tCounters[16],
      ptClient->eNetworkID,
      nObjectives,
      v6);
    NetManager_LogMessage(igi2_frame.Buffer);
    if ( ptClient->eNetworkID )
    {
      _snprintf(igi2_frame.eSet, 0x28u, (char *const)&g_ptNetManager.tSendCounters.tCounters[19], v6);
      NetworkCommand_RemoteEval((char *)ptClient->eNetworkID, (int)igi2_frame.eSet, NETMANAGER_HOSTSET_GIVEN_DESTINATION);
    }
  }
}

// source: j/0/network/netmanager.c:6809  [anchor-caller]
void __cdecl NetManager_ReduceClientBandwidths(struct NetManager_s *ptNetManager, float vFactor, int nMin, int nMax)
{
  struct QTask_s *p_tQTask; // esi
  unsigned __int16 v5; // dx
  struct Client_s *v6; // eax

  p_tQTask = nullptr;
LABEL_2:
  v5 = Client_eQTaskType;
  while ( 1 )
  {
    v6 = (struct Client_s *)(p_tQTask
                           ? QTask_GetNextSiblingOfType(p_tQTask, v5)
                           : QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, v5));
    p_tQTask = &v6->tQTask;
    if ( !v6 )
      break;
    if ( v6->eNetworkID )
    {
      NetManager_ReduceClientBandwidth(ptNetManager, v6, vFactor, nMin, nMax);
      goto LABEL_2;
    }
  }
}

struct QTask_s *__cdecl sub_41DF20(int a1)
{
  #pragma pack(push, 1)
  union
  {
    struct { char eSet[40]; };
    struct { char igi2_o1[40]; char Buffer[256]; };
    char igi2_extent[296];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v1; // esi
  struct QTask_s *result; // eax
  struct QTask_s *ptNext; // ecx
  int v4; // eax

  v1 = nullptr;
  while ( 1 )
  {
    result = v1
           ? QTask_GetNextSiblingOfType(v1, Client_eQTaskType)
           : QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, Client_eQTaskType);
    v1 = result;
    if ( !result )
      break;
    ptNext = result[1].ptNext;
    if ( ptNext )
    {
      v4 = *(_DWORD *)&result[7].eQTaskType;
      if ( v4 > a1 )
      {
        _snprintf(
          igi2_frame.Buffer,
          0xFFu,
          (char *const)&g_ptNetManager.tSendCounters.tCounters[12].nCounter,
          ptNext,
          v4,
          a1);
        NetManager_LogMessage(igi2_frame.Buffer);
        if ( v1[1].ptNext )
        {
          _snprintf(igi2_frame.eSet, 0x28u, (char *const)&g_ptNetManager.tSendCounters.tCounters[19], a1);
          NetworkCommand_RemoteEval((char *)v1[1].ptNext, (int)igi2_frame.eSet, NETMANAGER_HOSTSET_GIVEN_DESTINATION);
        }
      }
    }
  }
  return result;
}

// source: j/0/network/netmanager.c:6842  [anchor-strings]
void __cdecl NetManager_TrafficControl(struct NetManager_s *ptNetManager)
{
  enum bool v1; // ebx
  struct QTask_s *FirstChildOfType; // edi
  int ptTail; // [esp+4h] [ebp-8h]
  int v4; // [esp+8h] [ebp-4h]

  v1 = Network_IsManySendErrors(50, 1.0);
  if ( ptNetManager->pxServerInterface )
  {
    FirstChildOfType = QTask_GetFirstChildOfType(&ptNetManager->tQTask, Server_eQTaskType);
    ptTail = (int)FirstChildOfType[1].tQTaskRefList.ptTail;
    v4 = (int)FirstChildOfType[1].ptParent + ptTail;
    if ( v4 >= 100 && (double)ptTail * 100.0 / (double)v4 > 20.0 )
    {
      NetManager_LogMessage((char *)&g_ptNetManager.tSendCounters.tCounters[8]);
      NetManager_ReduceClientBandwidths(ptNetManager, 0.8999999761581421, 100, 500);
    }
    FirstChildOfType[1].tQTaskRefList.ptTail = nullptr;
    FirstChildOfType[1].ptParent = nullptr;
  }
  if ( v1 )
  {
    if ( ptNetManager->pxServerInterface )
    {
      NetManager_ReduceClientBandwidths(ptNetManager, 0.8999999761581421, 200, 500);
      NetManager_LogMessage((char *)&g_ptNetManager.tSendCounters.tCounters[5]);
    }
    else
    {
      if ( ptNetManager->pxClientInterface )
        NetManager_AdjustLocalBandwidth(-10);
      NetManager_LogMessage((char *)&g_ptNetManager.tSendCounters.tCounters[5]);
    }
  }
}

// source: j/0/network/netmanager.c:6890  [anchor-strings]
struct Result_s *__cdecl NetManager_ReduceBandwidthsCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vFactor; };
    struct { char igi2_o1[4]; struct Result_s Rs; };
    struct { char igi2_o2[28]; char zTemp[256]; };
    char igi2_extent[284];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v3; // ecx
  double v4; // st7
  struct NetManager_s *ptNetManagerQTask; // esi

  if ( NetworkCommand_eEvalNetworkID != -1 || Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    NetworkCommand_SetEvalResponse((char *)&g_ptNetManager.tSendCounters.tCounters[3]);
  }
  else if ( ptArgList && ptArgList->nArguments == 1 )
  {
    v3 = Script_EvalArgInt(ptArgList, 0);
    v4 = (double)v3 * 0.10000000149011612;
    igi2_frame.vFactor = v4;
    if ( v4 <= 0.0 || igi2_frame.vFactor >= 1.0 )
    {
      _snprintf(igi2_frame.zTemp, 0xFFu, (char *const)&g_ptNetManager.tReceiveCounters.tCounters[25].nBytes, v3);
      NetManager_LogMessage(igi2_frame.zTemp);
    }
    else
    {
      ptNetManagerQTask = (struct NetManager_s *)Flow_ptFlow->ptNetManagerQTask;
      _snprintf(igi2_frame.zTemp, 0xFFu, &g_ptNetManager.tSendCounters.zName[4], igi2_frame.vFactor);
      NetManager_LogMessage(igi2_frame.zTemp);
      NetManager_ReduceClientBandwidths(ptNetManagerQTask, igi2_frame.vFactor, 200, 700);
    }
  }
  igi2_frame.Rs.nResult = 0;
  igi2_frame.Rs.vResult = 0.0;
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

BOOL sub_41E250()
{
  struct QTask_s *ptNetManagerQTask; // ecx
  double v1; // st7

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  if ( !ptNetManagerQTask || !ptNetManagerQTask[1].ptNext )
    return 0;
  v1 = (double)(int)pValue_84b73b4 * 0.009999999776482582;
  if ( v1 <= 0.009999999776482582 )
    v1 = 0.009999999776482582;
  return *(float *)&ptNetManagerQTask[36].tQTaskChildren.ptHead > (double)(int)pValue_84b73b8 * v1;
}

// source: j/0/network/netmanager.c:6943  [anchor-strings]
void __cdecl NetManager_RunPeriodically(struct NetManager_s *ptNetManager)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vThresholdRadius; };
    struct { char igi2_o1[4]; float vThresholdRadius_4; };
    struct { char igi2_o2[28]; char zEnd[4]; };
    struct { char igi2_o3[32]; char v36; };
    struct { char igi2_o4[36]; char zFormatText[4]; };
    struct { char igi2_o5[40]; char v38; };
    struct { char igi2_o6[44]; DWORD v39; };
    struct { char igi2_o7[48]; char Buffer[256]; };
    char igi2_extent[304];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  DWORD PerformanceCounter; // eax
  char *v2; // ebx
  bool v3; // zf
  bool v4; // sf
  unsigned int v5; // eax
  int *v6; // edi
  struct Flow_t *v7; // edx
  struct QTask_s *v8; // eax
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptHead; // eax
  int v11; // edx
  struct QTask_s *v12; // ecx
  int eQTaskType; // ecx
  struct QTask_s *ptNetManagerQTask; // esi
  DWORD TickCount; // eax
  int v16; // eax
  struct Node_s *v17; // ecx
  struct Node_s *v18; // eax
  int i; // edx
  double AverageRunDelta; // st7
  int GlobalPriority; // eax
  DWORD v22; // eax
  DWORD v23; // eax
  char *LocalizedString; // eax
  int nIdleMax; // ebx
  struct Client_s *ClientFromNetworkID; // eax
  int v27; // edi
  DWORD v28; // edi
  BOOL v29; // esi
  DWORD v30; // ecx
  bool v31; // cc
  BOOL v32; // eax

  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  v2 = (char *)(PerformanceCounter - Timer_nStartTime);
  v3 = ptNetManager->tReceiveCounters.tCounters[0].eGameMessage == 0;
  igi2_frame.v39 = PerformanceCounter - Timer_nStartTime;
  if ( !v3 )
  {
    ptNetManager->tReceiveCounters.tCounters[0].eGameMessage = 0;
    NetManager_LeaveGame();
LABEL_6:
    NetManager_Quit();
    return;
  }
  *(float *)&ptNetManager[1].tServerGameSettings.zServerName[16] = sub_447A40(500);
  sub_447CF0(500);
  *(_DWORD *)igi2_frame.zEnd = &v2[-ptNetManager->anRunTimer[1]];
  if ( (double)*(int *)igi2_frame.zEnd > 33.33333206176758 )
  {
    v5 = (StatusScreen_nCurrentClientStat + 1) & 0x800000FF;
    v4 = StatusScreen_nCurrentClientStat + 1 < 0;
    v6 = (int *)(72 * StatusScreen_nCurrentClientStat + 7652952);
    ptNetManager->anRunTimer[1] = (int)v2;
    qmemcpy(v6, &ptNetManager->tStatsPrTick.nKills, 0x48u);
    if ( v4 )
      v5 = (((_BYTE)v5 - 1) | 0xFFFFFF00) + 1;
    StatusScreen_nCurrentClientStat = v5;
    memset(&ptNetManager->tStatsPrTick.nKills, 0, 0x48u);
  }
  if ( v2 - (char *)ptNetManager[1].pxServerInterface > 10000 )
  {
    v7 = Flow_ptFlow;
    *(_DWORD *)&ptNetManager[1].tQTask.eQTaskType = 0;
    ptNetManager[1].pxServerInterface = v2;
    if ( !v7->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
    {
      NetManager_KickIdle(ptNetManager);
      if ( ptNetManager->pxServerInterface )
        sub_41DF20(ClientConfig_tClientConfig.nBandwidth);
    }
    if ( !Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
      NetManager_RetrieveUnusedNetworkIDs((struct NetManager_s *)Flow_ptFlow, 180);
  }
  if ( (int)&v2[-*(_DWORD *)ptNetManager[1].tServerGameSettings.zServerName] > 30000 )
  {
    NetManager_LogClients();
    *(_DWORD *)ptNetManager[1].tServerGameSettings.zServerName = v2;
  }
  if ( (int)&v2[-ptNetManager->nTrafficControlTimer] > 25000 )
  {
    Network_PrintNetworkStats((void (*)(char *, ...))NetManager_LogMessage);
    if ( NetManager_IsLocalRoundPlayedFor(ptNetManager, 20000) )
      NetManager_TrafficControl(ptNetManager);
    ptNetManager->nTrafficControlTimer = (int)v2;
    Network_ClearNetworkStats();
  }
  DebugConsole_PushActiveConsole(NetworkInfo_tFrameInfoConsoleID);
  DebugConsole_ClearAll(DebugConsole_ptActiveDebugConsole, false);
  DebugConsole_PopActiveConsole();
  if ( *(_DWORD *)&ptNetManager->tReceiveCounters.zName[4] )
  {
    v8 = MenuManager_ptQTask;
    if ( ptNetManager->tReceiveCounters.nStartTime && NetManager_eMode == NETMANAGER_MODE_SELECTTEAM )
    {
      MenuManager_ptQTask[1].ptNext = (struct QTask_s *)995;
      v8[1].tQTaskChildren.ptMiddle = nullptr;
      ptNetManager->tReceiveCounters.nStartTime = 0;
    }
    if ( !v8
      || v8[1].tQTaskChildren.ptMiddle == (struct QTask_s *)10
      || (ptNext = v8[1].ptNext, ptNext != (struct QTask_s *)900) && ptNext != (struct QTask_s *)906 )
    {
      NetManager_UpdateSettings(ptNetManager);
    }
  }
  ptHead = ptNetManager->tQTask.tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v11 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v12 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v12 = nullptr;
      QTask_atProtectedQTaskStack[v11].ptQTask = v12;
      eQTaskType = ptHead->eQTaskType;
      QTask_nProtectedQTaskStackOffset = v11 + 1;
      ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][eQTaskType].pfHandler)(ptHead);
      ptHead = (struct QTask_s *)dword_849C7DC[QTask_nProtectedQTaskStackOffset];
      v11 = --QTask_nProtectedQTaskStackOffset;
    }
    while ( ptHead );
  }
  DebugConsole_PushActiveConsole(NetworkInfo_tFrameInfoConsoleID);
  DebugConsole_printf((char *)&stru_6A4CDC);
  NetManager_PrintCounter(
    (struct NetManagerCounterSet_s *)&ptNetManager->tReceiveCounters.tCounters[1].nBytes,
    DebugConsole_printf);
  DebugConsole_printf((char *)&stru_6A4CDC);
  NetManager_PrintCounter(
    (struct NetManagerCounterSet_s *)&ptNetManager->tSendCounters.tCounters[1].nBytes,
    DebugConsole_printf);
  DebugConsole_printf((char *)&stru_6A4CDC);
  Network_PrintPacketLoss();
  DebugConsole_printf((char *)&stru_6A4CDC);
  Network_PrintNetworkStats(DebugConsole_printf);
  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  if ( Timer_isPerformanceCounter )
    TickCount = Timer_GetPerformanceCounter();
  else
    TickCount = GetTickCount();
  DebugConsole_printf(
    (char *)&g_ptNetManager.tReceiveCounters.tCounters[22].nCounter,
    ptNetManager->tReceiveCounters.tCounters[0].nCounter,
    TickCount
  - Timer_nStartTime
  + (char *)ptNetManagerQTask[6].tQTaskRefList.ptMiddle
  - (char *)ptNetManagerQTask[6].tQTaskRefList.ptTail);
  if ( (ptNetManager->pxClientInterface || ptNetManager->pxServerInterface)
    && Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    v16 = Network_NumberOfWaitingFromHost(0);
    DebugConsole_printf((char *)&g_ptNetManager.tReceiveCounters.tCounters[19].nCounter, v16);
    v17 = Network_atQueues[0].tList.ptHead;
    v18 = Network_atQueues[0].tList.ptHead->ptNext;
    for ( i = 0; v18; v18 = v18->ptNext )
    {
      if ( !v17[1].ptNext )
        ++i;
      v17 = v18;
    }
    DebugConsole_printf((char *)&g_ptNetManager.tReceiveCounters.tCounters[16].nBytes, i);
  }
  AverageRunDelta = NetManager_GetAverageRunDelta();
  if ( AverageRunDelta >= 0.0 )
    DebugConsole_printf((char *)&g_ptNetManager.tReceiveCounters.tCounters[13].nCounter, AverageRunDelta);
  igi2_frame.vThresholdRadius_4 = (double)ServerConfig_tServerConfig.nCloseFireRange * 4096.0;
  igi2_frame.vThresholdRadius = (double)ServerConfig_tServerConfig.nViewPosRange * 4096.0;
  GlobalPriority = Client_GetGlobalPriority(igi2_frame.vThresholdRadius, igi2_frame.vThresholdRadius_4);
  DebugConsole_printf(
    (char *)&g_ptNetManager.tReceiveCounters.tCounters[11].nCounter,
    GlobalPriority != 1 ? 76 : 72);
  DebugConsole_PopActiveConsole();
  NetManager_RunCountPacket((struct NetManagerCounterSet_s *)&ptNetManager->tReceiveCounters.tCounters[1].nBytes);
  NetManager_RunCountPacket((struct NetManagerCounterSet_s *)&ptNetManager->tSendCounters.tCounters[1].nBytes);
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    v22 = Timer_isPerformanceCounter ? Timer_GetPerformanceCounter() : GetTickCount();
    if ( (int)(v22 - Timer_nStartTime - ptNetManager->nClientConnectCheckTimer) > 2000 )
    {
      v23 = Timer_isPerformanceCounter ? Timer_GetPerformanceCounter() : GetTickCount();
      ptNetManager->nClientConnectCheckTimer = v23 - Timer_nStartTime;
      if ( ptNetManager->pxClientInterface )
      {
        if ( Network_nReceivedQUIT == 1 )
        {
          LocalizedString = Config_GetLocalizedString((char *)&g_ptNetManager.tReceiveCounters.tCounters[10]);
          _snprintf(igi2_frame.Buffer, 0xFFu, (char *const)&stru_6A4CDC.tDebugConsoleLineList.ptMiddle, LocalizedString);
          StatusScreen_ShowMessage(igi2_frame.Buffer, TEXTSCROLLER_COLOUR_RED);
        }
        if ( ptNetManager->pxClientInterface )
        {
          nIdleMax = ServerConfig_tServerConfig.nIdleMax;
          ClientFromNetworkID = NetManager_GetClientFromNetworkID((int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
          v27 = 1000 * ServerConfig_tServerConfig.nAutoKick;
          *(_DWORD *)igi2_frame.zEnd = ClientFromNetworkID;
          if ( NetManager_IsLocalRoundPlayedFor(ptNetManager, 20000) )
          {
            v28 = igi2_frame.v39;
            v29 = (int)(igi2_frame.v39 - ptNetManager->tReceiveCounters.tCounters[0].nCounter) > nIdleMax
               && (int)(igi2_frame.v39 - ptNetManager->tStatsPrTick.nBandwidth) < 2 * nIdleMax;
            _snprintf(
              igi2_frame.zFormatText,
              5u,
              (char *const)&g_ptNetManager.tReceiveCounters.tCounters[9].nBytes,
              nIdleMax / 1000);
            igi2_frame.v38 = 0;
            if ( v29 )
            {
              _snprintf(
                igi2_frame.Buffer,
                0xFFu,
                (char *const)&g_ptNetManager.tReceiveCounters.tCounters[4].nCounter,
                nIdleMax,
                v28 - ptNetManager->tReceiveCounters.tCounters[0].nCounter,
                *(_DWORD *)ptNetManager->tReceiveCounters.zName);
              ++*(_DWORD *)ptNetManager->tReceiveCounters.zName;
              NetManager_LogMessage(igi2_frame.Buffer);
              Config_SetLocalizedPhrase(
                igi2_frame.Buffer,
                (char *)&g_ptNetManager.tReceiveCounters.tCounters[2].nCounter,
                igi2_frame.zFormatText,
                nullptr,
                nullptr);
              StatusScreen_ShowMonitorMessage(igi2_frame.Buffer, TEXTSCROLLER_COLOUR_WHITE);
              if ( *(int *)ptNetManager->tReceiveCounters.zName < 2 )
                v29 = 0;
            }
            else
            {
              *(_DWORD *)ptNetManager->tReceiveCounters.zName = 0;
            }
          }
          else
          {
            v30 = igi2_frame.v39;
            v29 = 0;
            v31 = (int)(igi2_frame.v39 - ptNetManager->tReceiveCounters.tCounters[0].nCounter) <= v27;
            *(_DWORD *)ptNetManager->tReceiveCounters.zName = 0;
            if ( !v31 )
              v29 = (int)(v30 - ptNetManager->tStatsPrTick.nBandwidth) < v27 / 2;
            _snprintf(
              igi2_frame.zFormatText,
              5u,
              (char *const)&g_ptNetManager.tReceiveCounters.tCounters[9].nBytes,
              v27 / 1000);
            igi2_frame.v38 = 0;
          }
          v32 = *(_DWORD *)igi2_frame.zEnd && Network_nReceivedQUIT >= 3;
          if ( v29 )
          {
            if ( !v32 )
            {
LABEL_93:
              Config_SetLocalizedPhrase(
                igi2_frame.Buffer,
                (char *)&g_ptNetManager.nRoundStartTime,
                igi2_frame.zFormatText,
                nullptr,
                nullptr);
              goto LABEL_94;
            }
          }
          else if ( *(_DWORD *)igi2_frame.zEnd )
          {
            if ( !v32 )
              goto LABEL_83;
          }
          else if ( !v32 )
          {
            _snprintf(
              igi2_frame.zEnd,
              5u,
              (char *const)&g_ptNetManager.isConnected,
              Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
            igi2_frame.v36 = 0;
            Config_SetLocalizedPhrase(igi2_frame.Buffer, (char *)&g_ptNetManager.isWeaponsCarryOver, igi2_frame.zEnd, nullptr, nullptr);
LABEL_94:
            StatusScreen_ShowMonitorMessage(igi2_frame.Buffer, TEXTSCROLLER_COLOUR_WHITE);
            NetManager_LeaveGame();
            goto LABEL_6;
          }
          NetManager_LogMessage(&g_ptNetManager.tReceiveCounters.zName[16]);
          goto LABEL_93;
        }
      }
    }
  }
LABEL_83:
  if ( ptNetManager->pxServerInterface )
    NetManager_DistributeStats();
  if ( ptNetManager->pxClientInterface )
  {
    NetManager_RunClientPing(ptNetManager);
    if ( !(Flow_ptFlow->nTicks % 60) )
      NetManager_UpdateStats(ptNetManager);
  }
}

// source: j/0/network/netmanager.c:7245  [anchor-callee]
int __cdecl NetManager_GetLastReceivedTimeFromNetworkID(int eNetworkID)
{
  struct QTask_s *ptNetManagerQTask; // ecx
  struct QTask_s *ptMiddle; // eax
  struct Client_s *ClientFromNetworkID; // eax

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  ptMiddle = ptNetManagerQTask[6].tQTaskChildren.ptMiddle;
  if ( ptMiddle == (struct QTask_s *)eNetworkID )
  {
    if ( Timer_isPerformanceCounter )
      return Timer_GetPerformanceCounter() - Timer_nStartTime;
    else
      return GetTickCount() - Timer_nStartTime;
  }
  else if ( ptMiddle )
  {
    return (int)ptNetManagerQTask[9].tQTaskChildren.ptMiddle;
  }
  else
  {
    ClientFromNetworkID = NetManager_GetClientFromNetworkID(eNetworkID);
    if ( ClientFromNetworkID )
    {
      return ClientFromNetworkID->nLastPacketReceived;
    }
    else if ( Timer_isPerformanceCounter )
    {
      return Timer_GetPerformanceCounter() - Timer_nStartTime - 1010;
    }
    else
    {
      return GetTickCount() - Timer_nStartTime - 1010;
    }
  }
}

// source: j/0/network/netmanager.c:7336  [anchor-callee]
int __cdecl NetManager_GetResendDelay(int nTimesSent, int eDestination)
{
  int v2; // ebx
  DWORD PerformanceCounter; // eax
  DWORD v6; // esi
  struct QTask_s *ptNetManagerQTask; // ecx
  struct QTask_s *ptMiddle; // esi
  struct Client_s *ClientFromNetworkID; // eax
  int nPing; // eax
  int v11; // eax
  int v12; // ebx
  long double v13; // st7
  int v14; // [esp+8h] [ebp-Ch]

  v2 = nTimesSent;
  if ( nTimesSent <= 8 )
  {
    if ( !nTimesSent )
      return 0;
  }
  else
  {
    v2 = 8;
  }
  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  v6 = PerformanceCounter - Timer_nStartTime;
  if ( (int)(v6 - NetManager_GetLastReceivedTimeFromNetworkID(eDestination)) >= 1000 )
    return (__int64)(pow(2.0, (double)(v2 - 1)) * 1000.0);
  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  ptMiddle = ptNetManagerQTask[6].tQTaskChildren.ptMiddle;
  if ( ptMiddle )
    eDestination = (int)ptNetManagerQTask[6].tQTaskChildren.ptMiddle;
  ClientFromNetworkID = NetManager_GetClientFromNetworkID(eDestination);
  if ( ClientFromNetworkID )
    nPing = ClientFromNetworkID->tStats.nPing;
  else
    nPing = -1;
  v11 = 2 * nPing;
  v14 = v11;
  if ( v11 >= 100 )
  {
    if ( v11 > 1000 )
      v14 = 1000;
  }
  else
  {
    v14 = 100;
  }
  v12 = v2 - 1;
  if ( ptMiddle )
    v13 = pow(1.7, (double)v12);
  else
    v13 = pow(1.1, (double)v12);
  return (__int64)(v13 * (double)v14);
}

// source: j/0/network/netmanager.c:7393  [anchor-strings]
void __cdecl NetManager_RunHandler(struct QTask_s *ptQTask)
{
  struct SpyBrowser_s *FirstChildOfType; // eax
  DWORD PerformanceCounter; // eax
  char *v3; // ecx
  struct QTask_s *v4; // esi
  char *v5; // ecx

  FirstChildOfType = (struct SpyBrowser_s *)QTask_GetFirstChildOfType(ptQTask, SpyBrowser_eQTaskType);
  SpyBrowser_ThinkList(FirstChildOfType);
  if ( Game_eGameMode )
  {
    if ( Timer_isPerformanceCounter )
      PerformanceCounter = Timer_GetPerformanceCounter();
    else
      PerformanceCounter = GetTickCount();
    v4 = (struct QTask_s *)(PerformanceCounter - Timer_nStartTime);
    ptQTask[36].ptPrev = nullptr;
    NetManager_RunAlways((struct NetManager_s *)ptQTask, v3);
    if ( !*((_DWORD *)&Flow_ptFlow->ptNetManagerQTask[31].tQTaskChildren.ptTail
          + (int)Flow_ptFlow->ptNetManagerQTask[32].tQTaskChildren.ptTail)
      && (char *)v4 - (char *)ptQTask[29].ptPrev >= 16 )
    {
      ptQTask[29].ptPrev = v4;
      NetManager_RunPeriodically((struct NetManager_s *)ptQTask);
      ptQTask[36].ptPrev = nullptr;
      NetManager_RunAlways((struct NetManager_s *)ptQTask, v5);
    }
  }
}

// source: j/0/network/netmanager.c:7444  [anchor-hash]
void __cdecl NetManager_DrawInterpolateHandler(struct QTask_s *ptQTask)
{
  if ( NetManager_eMode == NETMANAGER_MODE_SPAWN )
    NetManager_UpdateSpawnCamera();
}

// source: j/0/network/netmanager.c:7468  [anchor-callee]
void __cdecl NetManager_SendScoreUpdate()
{
  struct QTask_s *v0; // edi
  struct Flow_t *v1; // esi
  unsigned __int16 v2; // dx
  struct QTask_s *v3; // eax
  struct QTask_s *ptNetManagerQTask; // esi
  DWORD PerformanceCounter; // eax
  struct QReference_s *ptTail; // ebx
  struct QReference_s *ptMiddle; // ecx
  struct QTask_s *v8; // esi
  unsigned __int16 v9; // dx
  struct QTask_s *FirstChildOfType; // eax
  int ptPrev; // eax
  struct QTask_s *v12; // eax
  int ptNext; // eax
  struct QTask_s *v14; // eax
  int v15; // ecx
  int v16; // edx
  int nWarmupEndTime; // edx
  struct NetManagerGameMessageTeamScore_t tGameMessage; // [esp+Ch] [ebp-30h] BYREF

  v0 = nullptr;
LABEL_2:
  v1 = Flow_ptFlow;
  v2 = Client_eQTaskType;
  while ( 1 )
  {
    v3 = v0 ? QTask_GetNextSiblingOfType(v0, v2) : QTask_GetFirstChildOfType(v1->ptNetManagerQTask, v2);
    v0 = v3;
    if ( !v3 )
      break;
    if ( v3[1].ptNext )
    {
      ptNetManagerQTask = v1->ptNetManagerQTask;
      tGameMessage.tBaseMessage.eGameMessage = 1414742866;
      if ( Timer_isPerformanceCounter )
        PerformanceCounter = Timer_GetPerformanceCounter();
      else
        PerformanceCounter = GetTickCount();
      ptTail = ptNetManagerQTask[6].tQTaskRefList.ptTail;
      ptMiddle = ptNetManagerQTask[6].tQTaskRefList.ptMiddle;
      v8 = Flow_ptFlow->ptNetManagerQTask;
      v9 = TeamManager_eQTaskType;
      tGameMessage.tBaseMessage.nLocalTime = PerformanceCounter - Timer_nStartTime + ((char *)ptMiddle - (char *)ptTail);
      FirstChildOfType = QTask_GetFirstChildOfType(v8, TeamManager_eQTaskType);
      if ( FirstChildOfType )
        ptPrev = (int)FirstChildOfType[1].ptPrev;
      else
        ptPrev = -1;
      tGameMessage.nBadScore = ptPrev;
      v12 = QTask_GetFirstChildOfType(v8, v9);
      if ( v12 )
        ptNext = (int)v12[1].ptNext;
      else
        ptNext = -1;
      tGameMessage.nGoodScore = ptNext;
      v14 = QTask_GetFirstChildOfType(v8, MapControl_eQTaskType);
      v15 = (int)v14[1].tQTaskChildren.ptTail;
      v16 = (int)v14[1].tQTaskChildren.ptMiddle;
      tGameMessage.isLoading = (char)v14[1].ptParent;
      tGameMessage.nMapEndTime = v15;
      tGameMessage.nRound = v16;
      if ( NetMission_ptNetMission )
      {
        nWarmupEndTime = NetMission_ptNetMission->nWarmupEndTime;
        tGameMessage.nMissionEndTime = NetMission_ptNetMission->nMissionEndTime;
        tGameMessage.nWarmupEndTime = nWarmupEndTime;
        tGameMessage.nWarmup = ServerConfig_tServerConfig.nPloss;
        tGameMessage.nMissionTime = ServerConfig_tServerConfig.nBombTime;
      }
      else
      {
        tGameMessage.nMissionEndTime = -1;
        tGameMessage.nWarmupEndTime = -1;
      }
      NetManager_SendGameMessage((int)v0[1].ptNext, 0, NETWORKQUEUE_GUARANTEED, &tGameMessage.tBaseMessage, 0x30u);
      goto LABEL_2;
    }
  }
}

// source: j/0/network/netmanager.c:7523  [anchor-strings]
int __cdecl NetManager_AddEquipment(int eClientNetworkID, int nItemID)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct Netshop_Item_s *ptNetshopItem; };
    struct { char igi2_o1[4]; struct Client_s *ptCurrentClient; };
    struct { char igi2_o2[8]; struct ClientGameMessageEquip_s tGameMessage; };
    struct { char igi2_o3[32]; char zTemp[256]; };
    char igi2_extent[288];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *FirstChildOfType; // eax
  int ptNext; // edx
  int v5; // ecx
  struct QTask_s **p_ptPrev; // eax
  int v7; // ebp
  struct WeaponType_s *WeaponTypeFromID; // eax
  struct QTask_s *v9; // ebx
  struct WeaponType_s *v10; // esi
  struct WeaponType_s *NextEnabledWeaponTypeFromCategory; // edi
  struct QTask_s *ptNetManagerQTask; // esi
  DWORD PerformanceCounter; // eax
  unsigned __int8 ePickupType; // cl
  int ePickupID; // edx
  int nPickupAmount; // eax
  struct QTask_s *v17; // eax
  int result; // eax

  igi2_frame.ptCurrentClient = nullptr;
  _snprintf(
    igi2_frame.zTemp,
    0xFFu,
    (char *const)&g_ptNetManager.tServerGameSettings.nSpawnSafeTime,
    nItemID,
    eClientNetworkID);
  NetManager_LogMessage(igi2_frame.zTemp);
  FirstChildOfType = QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, Netshop_eQTaskType);
  ptNext = (int)FirstChildOfType[1].ptNext;
  v5 = 0;
  if ( ptNext <= 0 )
  {
LABEL_5:
    igi2_frame.ptNetshopItem = nullptr;
  }
  else
  {
    p_ptPrev = &FirstChildOfType[1].ptPrev;
    while ( *p_ptPrev != (struct QTask_s *)nItemID )
    {
      ++v5;
      p_ptPrev += 14;
      if ( v5 >= ptNext )
        goto LABEL_5;
    }
    igi2_frame.ptNetshopItem = (struct Netshop_Item_s *)p_ptPrev;
  }
  v7 = *(_DWORD *)(NetManager_GetClientFromNetworkID(eClientNetworkID)->tReceiveTimeBuffer.nCounter + 8);
  if ( !igi2_frame.ptNetshopItem->ePickupType )
  {
    WeaponTypeFromID = WeaponType_GetWeaponTypeFromID(nItemID);
    v9 = *(struct QTask_s **)(v7 + 1320);
    v10 = WeaponTypeFromID;
    NextEnabledWeaponTypeFromCategory = Weapon_GetNextEnabledWeaponTypeFromCategory(
                                          v9,
                                          WeaponTypeFromID->eWeaponCategory,
                                          nullptr);
    if ( *(_BYTE *)(v7 + 1180) )
    {
      if ( NextEnabledWeaponTypeFromCategory && NextEnabledWeaponTypeFromCategory != v10 )
        Weapon_DisableWeaponType(v9, NextEnabledWeaponTypeFromCategory->zWeaponScriptID, true);
    }
    else if ( Weapon_GetWeaponTypeItemFromWeaponType(v9, v10->zWeaponScriptID)->isActive )
    {
      NetManager_DropWeapon(eClientNetworkID, NextEnabledWeaponTypeFromCategory->eID);
    }
  }
  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  igi2_frame.tGameMessage.tBaseMessage.eGameMessage = 1162958153;
  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  igi2_frame.tGameMessage.tBaseMessage.nLocalTime = PerformanceCounter
                                       - Timer_nStartTime
                                       + (char *)ptNetManagerQTask[6].tQTaskRefList.ptMiddle
                                       - (char *)ptNetManagerQTask[6].tQTaskRefList.ptTail;
  ePickupType = igi2_frame.ptNetshopItem->ePickupType;
  igi2_frame.tGameMessage.eNetworkReceivingClientID = eClientNetworkID;
  ePickupID = igi2_frame.ptNetshopItem->ePickupID;
  nPickupAmount = igi2_frame.ptNetshopItem->nPickupAmount;
  igi2_frame.tGameMessage.ePickupType = ePickupType;
  igi2_frame.tGameMessage.ePickupID = ePickupID;
  igi2_frame.tGameMessage.nPickupAmount = nPickupAmount;
  if ( nPickupAmount <= 0 )
    igi2_frame.tGameMessage.nPickupAmount = 10000;
  while ( 1 )
  {
    v17 = igi2_frame.ptCurrentClient
        ? QTask_GetNextSiblingOfType(&igi2_frame.ptCurrentClient->tQTask, Client_eQTaskType)
        : QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, Client_eQTaskType);
    igi2_frame.ptCurrentClient = (struct Client_s *)v17;
    if ( !v17 )
      break;
    NetManager_SendGameMessage((int)v17[1].ptNext, 0, NETWORKQUEUE_GUARANTEED, &igi2_frame.tGameMessage.tBaseMessage, 0x18u);
  }
  result = AppContext_tAppContext.isServer;
  if ( AppContext_tAppContext.isServer )
    NetManager_SendGameMessage(0, 0, NETWORKQUEUE_GUARANTEED, &igi2_frame.tGameMessage.tBaseMessage, 0x18u);
  return result;
}

// source: j/0/network/netmanager.c:7643  [anchor-strings]
struct NetManagerGameMessageList *__cdecl NetManager_SendListCommand(
        struct NetManagerGameMessageList *ptGameMessage,
        int eDestination)
{
  struct Flow_t *v3; // eax
  struct NetManagerGameMessageList *result; // eax
  struct QTask_s *ptNetManagerQTask; // esi
  DWORD PerformanceCounter; // eax
  int v7; // edx
  struct Flow_t *v8; // eax

  v3 = Flow_ptFlow;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle == (struct QTask_s *)-1 )
  {
    DebugConsole_printf((char *)&g_ptNetManager.tServerGameSettings.nWarmupEndTime);
  }
  else
  {
    ptGameMessage->tBaseMessage.eGameMessage = 1279873876;
    ptNetManagerQTask = v3->ptNetManagerQTask;
    if ( Timer_isPerformanceCounter )
      PerformanceCounter = Timer_GetPerformanceCounter();
    else
      PerformanceCounter = GetTickCount();
    v7 = PerformanceCounter
       - Timer_nStartTime
       + (char *)ptNetManagerQTask[6].tQTaskRefList.ptMiddle
       - (char *)ptNetManagerQTask[6].tQTaskRefList.ptTail;
    v8 = Flow_ptFlow;
    ptGameMessage->tBaseMessage.nLocalTime = v7;
    ptGameMessage->eClientNetworkID = (int)v8->ptNetManagerQTask[6].tQTaskChildren.ptMiddle;
    Consoled_ConfigListMessage(ptGameMessage);
    NetManager_SendGameMessage(
      eDestination,
      (int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle,
      NETWORKQUEUE_GUARANTEED,
      &ptGameMessage->tBaseMessage,
      48 * (ptGameMessage->nNumberOfLines + 1));
  }
  return result;
}

// source: j/0/network/netmanager.c:7678  [anchor-callee]
void __cdecl NetManager_SendListCommandToMonitors(struct NetManagerGameMessageList *ptGameMessage)
{
  struct QTask_s *v1; // esi
  unsigned __int16 v2; // dx
  struct QTask_s *v3; // eax

  v1 = nullptr;
LABEL_2:
  v2 = Client_eQTaskType;
  while ( 1 )
  {
    v3 = v1 ? QTask_GetNextSiblingOfType(v1, v2) : QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, v2);
    v1 = v3;
    if ( !v3 )
      break;
    if ( v3[1].tQTaskChildren.ptMiddle )
    {
      NetManager_SendListCommand(ptGameMessage, (int)v3[1].ptNext);
      goto LABEL_2;
    }
  }
}

// source: j/0/network/netmanager.c:7706  [anchor-callee]
void __cdecl NetManager_SendListCommandTo(
        struct NetManagerGameMessageList *ptGameMessage,
        int eGivenDestination,
        enum NetManagerHostSet_e eSet)
{
  int eTeam; // ebx
  struct QTask_s *v4; // edi
  unsigned __int16 v5; // dx
  struct QTask_s *v6; // eax
  struct QTask_s *ptNext; // ecx
  bool v8; // zf
  int eGivenTeam; // [esp+8h] [ebp-4h]

  switch ( eSet )
  {
    case NETMANAGER_HOSTSET_MONITORS:
      NetManager_SendListCommandToMonitors(ptGameMessage);
      return;
    case NETMANAGER_HOSTSET_GIVEN_TEAM:
    case NETMANAGER_HOSTSET_OTHER_TEAM:
      eTeam = NetManager_GetClientFromNetworkID(eGivenDestination)->eTeam;
      break;
    case NETMANAGER_HOSTSET_GIVEN_DESTINATION:
      NetManager_SendListCommand(ptGameMessage, eGivenDestination);
      return;
    default:
      eTeam = eGivenTeam;
      break;
  }
  v4 = nullptr;
LABEL_10:
  v5 = Client_eQTaskType;
  while ( 1 )
  {
    v6 = v4 ? QTask_GetNextSiblingOfType(v4, v5) : QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, v5);
    v4 = v6;
    if ( !v6 )
      break;
    ptNext = v6[1].ptNext;
    if ( eSet != NETMANAGER_HOSTSET_ALL_EXCEPT_GIVEN && eSet != NETMANAGER_HOSTSET_ALL_EXCEPT_GIVEN_AND_SERVER )
      goto LABEL_20;
    if ( ptNext != (struct QTask_s *)eGivenDestination )
    {
      if ( eSet == NETMANAGER_HOSTSET_ALL_EXCEPT_GIVEN_AND_SERVER )
      {
        v8 = ptNext == nullptr;
        goto LABEL_25;
      }
LABEL_20:
      if ( eSet == NETMANAGER_HOSTSET_GIVEN_TEAM )
      {
        if ( v6[1].tQTaskRefList.ptHead == (struct QReference_s *)eTeam )
          goto LABEL_22;
      }
      else
      {
        if ( eSet != NETMANAGER_HOSTSET_OTHER_TEAM )
          goto LABEL_22;
        v8 = v6[1].tQTaskRefList.ptHead == (struct QReference_s *)eTeam;
LABEL_25:
        if ( !v8 )
        {
LABEL_22:
          NetManager_SendListCommand(ptGameMessage, (int)v6[1].ptNext);
          goto LABEL_10;
        }
      }
    }
  }
  if ( !NetManager_GetClientFromNetworkID(0)
    && (eSet != NETMANAGER_HOSTSET_ALL_EXCEPT_GIVEN && eSet != NETMANAGER_HOSTSET_ALL_EXCEPT_GIVEN_AND_SERVER
     || eGivenDestination && eSet != NETMANAGER_HOSTSET_ALL_EXCEPT_GIVEN_AND_SERVER)
    && eSet != NETMANAGER_HOSTSET_GIVEN_TEAM
    && eSet != NETMANAGER_HOSTSET_OTHER_TEAM )
  {
    NetManager_SendListCommand(ptGameMessage, 0);
  }
}

// source: j/0/network/netmanager.c:7811  [anchor-callee]
void __cdecl NetManager_ServerMessageToClient(struct Client_s *ptClient, char *zText)
{
  struct QTask_s *ptNetManagerQTask; // esi
  DWORD PerformanceCounter; // eax
  struct ClientGameMessageChat_s tChatMessage; // [esp+8h] [ebp-110h] BYREF

  tChatMessage.isServerAnnounce = 1;
  tChatMessage.tBaseMessage.eGameMessage = 1128808788;
  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  tChatMessage.tBaseMessage.nLocalTime = PerformanceCounter
                                       - Timer_nStartTime
                                       + (char *)ptNetManagerQTask[6].tQTaskRefList.ptMiddle
                                       - (char *)ptNetManagerQTask[6].tQTaskRefList.ptTail;
  tChatMessage.eTeam = -1;
  tChatMessage.zString[0] = 0;
  strncpy(tChatMessage.zString, zText, 0xFFu);
  NetManager_SendGameMessage(ptClient->eNetworkID, 0, NETWORKQUEUE_GUARANTEED, &tChatMessage.tBaseMessage, 0x110u);
}

// source: j/0/network/netmanager.c:7845  [anchor-callee]
char *__cdecl NetManager_ServerMessage(char *zText, enum bool isToAll)
{
  struct QTask_s *v3; // esi
  char *result; // eax

  v3 = nullptr;
  while ( 1 )
  {
    result = (char *)(v3
                    ? QTask_GetNextSiblingOfType(v3, Client_eQTaskType)
                    : QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, Client_eQTaskType));
    v3 = (struct QTask_s *)result;
    if ( !result )
      break;
    if ( *((_DWORD *)result + 10) )
    {
      if ( isToAll || *((_DWORD *)result + 13) )
        NetManager_ServerMessageToClient((struct Client_s *)result, zText);
    }
    else if ( isToAll )
    {
      StatusScreen_ShowMonitorMessage(zText, TEXTSCROLLER_COLOUR_WHITE);
    }
  }
  return result;
}

// source: j/0/network/netmanager.c:7879  [anchor-callee]
void __cdecl NetManager_ServerAnnounce(char *zText)
{
  struct QTask_s *ptNetManagerQTask; // esi

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  if ( (int)ptNetManagerQTask[35].tQTaskRefList.ptMiddle <= 30 )
  {
    NetManager_ServerMessage(zText, false);
    ++*(int *)&ptNetManagerQTask[35].tQTaskRefList.ptMiddle;
  }
}

// source: j/0/network/netmanager.c:7899  [anchor-strings]
struct Result_s *__cdecl NetManager_AnnounceCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct Result_s Rs; };
    struct { char igi2_o1[24]; char zTemp[256]; };
    char igi2_extent[280];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char *p_nRound; // edx

  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle || NetworkCommand_eEvalNetworkID != -1 )
  {
    p_nRound = (char *)&g_ptNetManager.tServerGameSettings.anObjectiveWhoDidIt[1];
    goto LABEL_9;
  }
  if ( !ptArgList || ptArgList->nArguments != 1 )
  {
    p_nRound = &g_ptNetManager.tServerGameSettings.nRound;
LABEL_9:
    NetworkCommand_SetEvalResponse(p_nRound);
    goto LABEL_10;
  }
  memset(igi2_frame.zTemp, 0, 255);
  Script_EvalArgString(ptArgList, 0, igi2_frame.zTemp, 40);
  if ( strlen(igi2_frame.zTemp) )
    NetManager_ServerMessage(igi2_frame.zTemp, true);
LABEL_10:
  igi2_frame.Rs.nResult = 1;
  igi2_frame.Rs.vResult = 1.0;
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/netmanager.c:7936  [anchor-strings]
void __cdecl NetManager_DeleteHandler(struct QTask_s *ptQTask)
{
  int Error; // eax
  struct QTaskList_s *v2; // eax

  NetManager_StopNetwork((struct NetManager_s *)ptQTask);
  if ( WSACleanup() == -1 )
  {
    Error = WSAGetLastError();
    Network_DebugError("Network_CloseSockLib():", Error);
  }
  else
  {
    NetManager_LogMessage("Winsock closed and cleaned up\n");
  }
  QObjectVector_Delete((struct QObjectVector_s *)ptQTask[31].tQTaskChildren.ptMiddle);
  v2 = Flow_ptDrawInterpolateQTaskList;
  ptQTask[31].tQTaskChildren.ptMiddle = nullptr;
  QTaskList_Remove(v2, ptQTask);
}

// source: j/0/network/netmanager.c:7974  [size]
void __cdecl NetManager_TeamScoreHandler(struct QTask_s *ptQTask, void *pxContext)
{
  unsigned __int16 v2; // dx
  struct Flow_t *v3; // edi
  int v4; // esi
  struct QTask_s *FirstChildOfType; // eax
  struct NetMission_t *v6; // eax
  struct QTask_s *ptNetManagerQTask; // edi
  int v8; // [esp-4h] [ebp-Ch]

  v2 = TeamManager_eQTaskType;
  v3 = Flow_ptFlow;
  v4 = *((_DWORD *)pxContext + 3) + 8;
  QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, TeamManager_eQTaskType)[1].ptNext = *(struct QTask_s **)(v4 + 8);
  QTask_GetFirstChildOfType(v3->ptNetManagerQTask, v2)[1].ptPrev = *(struct QTask_s **)(v4 + 12);
  FirstChildOfType = QTask_GetFirstChildOfType(v3->ptNetManagerQTask, MapControl_eQTaskType);
  FirstChildOfType[1].tQTaskChildren.ptTail = *(struct QTask_s **)(v4 + 20);
  FirstChildOfType[1].tQTaskChildren.ptMiddle = *(struct QTask_s **)(v4 + 16);
  FirstChildOfType[1].tQTaskRefList.ptTail = (struct QReference_s *)1;
  FirstChildOfType[1].ptParent = (struct QTask_s *)*(char *)(v4 + 44);
  v6 = NetMission_ptNetMission;
  ptNetManagerQTask = v3->ptNetManagerQTask;
  NetMission_ptNetMission->nMissionEndTime = *(_DWORD *)(v4 + 28);
  v6->isStarted = true;
  v8 = *(_DWORD *)(v4 + 32);
  v6->nWarmupEndTime = v8;
  NetMission_EvaluateWarmUp(v8);
  ptNetManagerQTask[4].ptParent = *(struct QTask_s **)(v4 + 36);
  ptNetManagerQTask[4].tQTaskRefList.ptMiddle = *(struct QReference_s **)(v4 + 40);
}

// source: j/0/network/netmanager.c:8007  [size]
void __cdecl NetManager_ListCommandHandler(struct QTask_s *ptQTask, void *pxContext)
{
  NetworkCommand_ParseNetListInput((struct NetManagerGameMessageList *)(*((_DWORD *)pxContext + 3) + 8));
}

// source: j/0/network/netmanager.c:8036  [anchor-strings]
void __cdecl NetManager_CreatePlayerHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s *eNetworkID; };
    struct { char igi2_o1[20]; struct QTask_s *ptTail; };
    struct { char igi2_o2[24]; struct QTask_s *v53; };
    struct { char igi2_o3[28]; struct QTask_s *v54; };
    struct { char igi2_o4[32]; struct NetManagerGameMessage_s Buffer; };
    struct { char igi2_o5[40]; struct QTask_s *ptNext; };
    struct { char igi2_o6[44]; _DWORD v57[61]; };
    struct { char igi2_o7[288]; struct QTask_s ptParent; };
    struct { char igi2_o8[328]; int v59; };
    struct { char igi2_o9[332]; _DWORD v60[28]; };
    struct { char igi2_o10[444]; struct NetManagerGameMessage_s v61; };
    struct { char igi2_o11[452]; int v62; };
    struct { char igi2_o12[456]; int v63; };
    struct { char igi2_o13[460]; int v64; };
    struct { char igi2_o14[464]; int v65; };
    struct { char igi2_o15[468]; struct NetManagerGameMessage_s ptGameMessage; };
    char igi2_extent[532];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // ebp
  int v3; // esi
  int v4; // ebp
  int FairTeam; // esi
  BOOL v6; // ebx
  struct Client_s *ClientFromNetworkID; // eax
  struct QTask_s *ptNetManagerQTask; // edx
  struct QTask_s *v9; // esi
  struct Flow_t *v10; // edi
  unsigned __int16 v11; // dx
  struct QTask_s *v12; // eax
  struct QTask_s *v13; // eax
  struct QTask_s *NextSiblingOfType; // eax
  struct QTask_s *v15; // esi
  struct QTask_s *ptHead; // ebx
  struct QTask_s *ptPrev; // eax
  struct QTask_s *v18; // edi
  DWORD PerformanceCounter; // eax
  int v20; // ecx
  int v21; // eax
  struct QReference_s *v22; // ecx
  struct QTask_s *v23; // eax
  char v24; // cl
  struct QTaskNodeList_s *p_tQTaskChildren; // eax
  char v26; // cl
  unsigned __int8 v27; // dl
  struct QTask_s *v28; // ebx
  enum WeaponCategory_e v29; // edi
  struct WeaponType_s *NextEnabledWeaponTypeFromCategory; // eax
  struct WeaponType_s *v31; // esi
  struct WeaponTypeItem_s *WeaponTypeItemFromWeaponType; // eax
  struct QTask_s *ptMiddle; // ecx
  struct QTask_s *v34; // esi
  DWORD TickCount; // eax
  int v36; // ecx
  struct QTask_s *v37; // eax
  int v38; // ecx
  struct QTask_s **v39; // eax
  struct QTask_s *v40; // edi
  unsigned __int16 v41; // ax
  struct Client_s *v42; // edi
  struct Flow_t *v43; // eax
  struct QTask_s *v44; // ecx
  struct QTask_s *v45; // esi
  DWORD v46; // eax
  int v47; // ecx
  int v48; // edx
  int v49; // eax
  struct Server_s *FirstChildOfType; // eax

  v2 = *((_DWORD *)pxContext + 3);
  v3 = *(_DWORD *)(v2 + 20);
  v4 = v2 + 8;
  FairTeam = TeamManager_GetFairTeam(v3);
  v6 = FairTeam == *(_DWORD *)(v4 + 12);
  ClientFromNetworkID = NetManager_GetClientFromNetworkID(*(_DWORD *)(v4 + 8));
  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  if ( ClientFromNetworkID )
  {
    igi2_frame.eNetworkID = (struct QTask_s *)ClientFromNetworkID->eNetworkID;
    if ( igi2_frame.eNetworkID == ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
      _snprintf((char *const)&igi2_frame.Buffer, 0xFFu, &g_ptNetManager.tServerGameSettings.zServerName[56], igi2_frame.eNetworkID);
    else
      _snprintf((char *const)&igi2_frame.Buffer, 0xFFu, &g_ptNetManager.tServerGameSettings.zServerName[12], igi2_frame.eNetworkID);
    NetManager_LogMessage((char *)&igi2_frame.Buffer);
    return;
  }
  if ( !ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    *(_DWORD *)(v4 + 4) = NetManager_GetTimer();
    if ( !v6 )
    {
      *(_DWORD *)(v4 + 12) = FairTeam;
      NetManager_GetTeamModelName((char *)(v4 + 208), FairTeam, 0, 1);
    }
    MapControl_WriteState((struct NetManagerGameSettings_s *)&ptQTask[1].ptPrev);
    v9 = nullptr;
LABEL_10:
    v10 = Flow_ptFlow;
    v11 = Client_eQTaskType;
    while ( 1 )
    {
      v12 = v9 ? QTask_GetNextSiblingOfType(v9, v11) : QTask_GetFirstChildOfType(v10->ptNetManagerQTask, v11);
      v9 = v12;
      if ( !v12 )
        break;
      if ( ((int)v12[5].tQTaskRefList.ptMiddle & 1) == 0 )
      {
        NetManager_SendGameMessage(
          (int)v12[1].ptNext,
          (int)v10->ptNetManagerQTask[6].tQTaskChildren.ptMiddle,
          NETWORKQUEUE_GUARANTEED,
          (struct NetManagerGameMessage_s *)v4,
          0xE0u);
        goto LABEL_10;
      }
    }
    v13 = nullptr;
LABEL_18:
    if ( v13 )
      NextSiblingOfType = QTask_GetNextSiblingOfType(v13, v11);
    else
      NextSiblingOfType = QTask_GetFirstChildOfType(v10->ptNetManagerQTask, v11);
    v15 = NextSiblingOfType;
    igi2_frame.v53 = NextSiblingOfType;
    if ( NextSiblingOfType )
    {
      ptHead = NextSiblingOfType[16].tQTaskChildren.ptHead->tQTaskChildren.ptHead;
      ptPrev = ptHead[33].ptNext[1].ptPrev;
      if ( ptPrev )
        igi2_frame.ptTail = ptPrev->tQTaskChildren.ptTail;
      else
        igi2_frame.ptTail = nullptr;
      v18 = v10->ptNetManagerQTask;
      igi2_frame.v54 = ptHead[33].tQTaskChildren.ptTail;
      igi2_frame.Buffer.eGameMessage = 1129467980;
      if ( Timer_isPerformanceCounter )
        PerformanceCounter = Timer_GetPerformanceCounter();
      else
        PerformanceCounter = GetTickCount();
      v20 = PerformanceCounter
          - Timer_nStartTime
          + (char *)v18[6].tQTaskRefList.ptMiddle
          - (char *)v18[6].tQTaskRefList.ptTail;
      v21 = *(_DWORD *)&v15[7].eQTaskType;
      igi2_frame.ptNext = v15[1].ptNext;
      igi2_frame.Buffer.nLocalTime = v20;
      v22 = v15[1].tQTaskRefList.ptHead;
      igi2_frame.v57[32] = v21;
      v23 = v15 + 2;
      igi2_frame.v57[0] = v22;
      do
      {
        v24 = (char)v23->ptNext;
        *((_BYTE *)&v23->ptNext + ((char *)&igi2_frame.v57[33] - (char *)&v15[2])) = v23->ptNext;
        v23 = (struct QTask_s *)((char *)v23 + 1);
      }
      while ( v24 );
      p_tQTaskChildren = &v15[5].tQTaskChildren;
      do
      {
        v26 = (char)p_tQTaskChildren->ptHead;
        *((_BYTE *)&p_tQTaskChildren->ptHead + ((char *)&igi2_frame.v57[49] - (char *)&v15[5].tQTaskChildren)) = p_tQTaskChildren->ptHead;
        p_tQTaskChildren = (struct QTaskNodeList_s *)((char *)p_tQTaskChildren + 1);
      }
      while ( v26 );
      v27 = (unsigned __int8)ptHead[29].tQTaskRefList.ptHead;
      v28 = ptHead[33].ptNext;
      LOWORD(igi2_frame.v57[31]) = v27;
      v29 = WEAPONCATEGORY_NONE;
      while ( 1 )
      {
        NextEnabledWeaponTypeFromCategory = Weapon_GetNextEnabledWeaponTypeFromCategory(v28, v29, nullptr);
        v31 = NextEnabledWeaponTypeFromCategory;
        if ( !NextEnabledWeaponTypeFromCategory )
          break;
        WeaponTypeItemFromWeaponType = Weapon_GetWeaponTypeItemFromWeaponType(
                                         v28,
                                         NextEnabledWeaponTypeFromCategory->zWeaponScriptID);
        igi2_frame.v57[v29 + 4] = v31->eID;
        if ( !WeaponTypeItemFromWeaponType )
          goto LABEL_37;
        igi2_frame.v57[v29 + 17] = WeaponTypeItemFromWeaponType->iActiveFireMode;
LABEL_38:
        if ( ++v29 >= WEAPONCATEGORIES )
        {
          if ( igi2_frame.ptTail )
            igi2_frame.v57[3] = igi2_frame.ptTail[3].tQTaskRefList.ptTail;
          else
            igi2_frame.v57[3] = -1;
          ptMiddle = Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle;
          igi2_frame.v57[30] = igi2_frame.v54[16].tQTaskChildren.ptHead;
          NetManager_SendGameMessage(*(_DWORD *)(v4 + 8), (int)ptMiddle, NETWORKQUEUE_GUARANTEED, &igi2_frame.Buffer, 0xE0u);
          v10 = Flow_ptFlow;
          v11 = Client_eQTaskType;
          v13 = igi2_frame.v53;
          goto LABEL_18;
        }
      }
      igi2_frame.v57[v29 + 4] = -1;
LABEL_37:
      igi2_frame.v57[v29 + 17] = 0;
      goto LABEL_38;
    }
    NetManager_UpdateServerSettings();
    v34 = Flow_ptFlow->ptNetManagerQTask;
    igi2_frame.Buffer.eGameMessage = 1229867348;
    if ( Timer_isPerformanceCounter )
      TickCount = Timer_GetPerformanceCounter();
    else
      TickCount = GetTickCount();
    v36 = TickCount - Timer_nStartTime + ((char *)v34[6].tQTaskRefList.ptMiddle - (char *)v34[6].tQTaskRefList.ptTail);
    v37 = Flow_ptFlow->ptNetManagerQTask;
    igi2_frame.Buffer.nLocalTime = v36;
    qmemcpy(igi2_frame.v57, &ptQTask[1].ptPrev, 0xCCu);
    NetManager_SendGameMessage(
      *(_DWORD *)(v4 + 8),
      (int)v37[6].tQTaskChildren.ptMiddle,
      NETWORKQUEUE_GUARANTEED,
      &igi2_frame.Buffer,
      0xD8u);
  }
  igi2_frame.ptParent.ptPrev = *(struct QTask_s **)(v4 + 8);
  igi2_frame.ptParent.ptNext = nullptr;
  igi2_frame.ptParent.tQTaskChildren.ptHead = *(struct QTask_s **)(v4 + 12);
  strncpy((char *)&igi2_frame.ptParent.tQTaskRefList.ptMiddle, (char *)(v4 + 208), 0x10u);
  igi2_frame.ptParent.tQTaskChildren.ptTail = (struct QTask_s *)(v4 + 144);
  igi2_frame.ptParent.tQTaskRefList.ptHead = (struct QReference_s *)NetManager_atTeams[*(_DWORD *)(v4 + 12)].pzName;
  LOBYTE(igi2_frame.ptParent.tQTaskChildren.ptMiddle) = *(_BYTE *)(v4 + 136);
  igi2_frame.v59 = *(_DWORD *)(v4 + 24);
  igi2_frame.v60[26] = *(_DWORD *)(v4 + 132);
  BYTE1(igi2_frame.ptParent.tQTaskChildren.ptMiddle) = *(_BYTE *)(v4 + 137);
  igi2_frame.v60[27] = *(_DWORD *)(v4 + 140);
  v38 = 0;
  v39 = (struct QTask_s **)(v4 + 80);
  do
  {
    igi2_frame.v60[v38] = *(v39 - 13);
    *(struct QTask_s **)((char *)v39 + (_DWORD)&igi2_frame.ptParent.tQTaskChildren.ptTail - v4) = *v39;
    ++v38;
    ++v39;
  }
  while ( v38 < 13 );
  v40 = Flow_ptFlow->ptNetManagerQTask;
  v41 = Client_eQTaskType;
  ++BYTE1(v40[3].ptPrev);
  v42 = (struct Client_s *)QTask_NewFn(v40, v41, &igi2_frame.ptParent);
  _snprintf(
    (char *const)&igi2_frame.Buffer,
    0xFFu,
    (char *const)&g_ptNetManager.tQTask.tQTaskRefList.ptMiddle,
    igi2_frame.ptParent.ptPrev,
    igi2_frame.ptParent.tQTaskChildren.ptTail);
  NetManager_LogMessage((char *)&igi2_frame.Buffer);
  v43 = Flow_ptFlow;
  v44 = Flow_ptFlow->ptNetManagerQTask;
  if ( !v44[6].tQTaskChildren.ptMiddle )
  {
    igi2_frame.v61.eGameMessage = 1397052500;
    v45 = v44;
    if ( Timer_isPerformanceCounter )
      v46 = Timer_GetPerformanceCounter();
    else
      v46 = GetTickCount();
    v47 = *(_DWORD *)(v4 + 12);
    v48 = v46 - Timer_nStartTime + ((char *)v45[6].tQTaskRefList.ptMiddle - (char *)v45[6].tQTaskRefList.ptTail);
    v49 = *(_DWORD *)(v4 + 8);
    igi2_frame.v61.nLocalTime = v48;
    igi2_frame.v62 = v49;
    igi2_frame.v63 = v47;
    igi2_frame.v64 = 0;
    igi2_frame.v65 = 1;
    strncpy((char *)&igi2_frame.ptGameMessage, (char *)(v4 + 144), 0x40u);
    NetManager_SendGameMessage(
      *(_DWORD *)(v4 + 8),
      (int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle,
      NETWORKQUEUE_GUARANTEED,
      &igi2_frame.v61,
      0x58u);
    v43 = Flow_ptFlow;
  }
  if ( !v43->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    FirstChildOfType = (struct Server_s *)QTask_GetFirstChildOfType(ptQTask, Server_eQTaskType);
    Server_SendChallengeTo(FirstChildOfType, v42);
  }
}

// source: j/0/network/netmanager.c:8288  [anchor-mhash]
void __cdecl NetManager_ClearVotes(int eNetworkID)
{
  unsigned __int16 v1; // dx
  struct Flow_t *v2; // esi
  struct QTask_s *v3; // eax

  v1 = Client_eQTaskType;
  v2 = Flow_ptFlow;
  v3 = nullptr;
  while ( 1 )
  {
    v3 = v3 ? QTask_GetNextSiblingOfType(v3, v1) : QTask_GetFirstChildOfType(v2->ptNetManagerQTask, v1);
    if ( !v3 )
      break;
    if ( v3[1].ptParent == (struct QTask_s *)eNetworkID )
      v3[1].ptParent = (struct QTask_s *)-1;
  }
}

// source: j/0/network/netmanager.c:8312  [anchor-caller]
void __cdecl NetManager_DestroyPlayerHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { int eClientNetworkID; };
    struct { char igi2_o1[4]; int v22; };
    struct { char igi2_o2[8]; char Buffer[104]; };
    struct { char igi2_o3[112]; char zText[256]; };
    char igi2_extent[368];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // ebx
  int v3; // ecx
  struct Flow_t *v4; // esi
  struct NetManagerGameMessage_s *v5; // ebx
  int eGameMessage; // edi
  struct Server_s *FirstChildOfType; // eax
  struct QTask_s *ptNetManagerQTask; // esi
  struct QTask_s *v9; // edi
  DWORD PerformanceCounter; // eax
  char *v11; // edx
  struct QTask_s *NextSiblingOfType; // eax
  char *v13; // ecx
  int ptNext; // eax
  char *v15; // ecx
  struct Client_s *ClientFromNetworkID; // eax
  struct QTask_s *p_tQTask; // esi
  char *v18; // ecx
  char *LocalizedString; // eax
  struct QReference_s *ptTail; // eax

  v2 = *((_DWORD *)pxContext + 3);
  v3 = *(unsigned __int8 *)(v2 + 20);
  v4 = Flow_ptFlow;
  v5 = (struct NetManagerGameMessage_s *)(v2 + 8);
  eGameMessage = v5[1].eGameMessage;
  igi2_frame.eClientNetworkID = eGameMessage;
  igi2_frame.v22 = v3;
  if ( !Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    FirstChildOfType = (struct Server_s *)QTask_GetFirstChildOfType(ptQTask, Server_eQTaskType);
    Server_FreeIfExistsDR(FirstChildOfType, eGameMessage);
    v4 = Flow_ptFlow;
  }
  if ( !v4->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
    NetManager_ClearVotes(eGameMessage);
  ptNetManagerQTask = v4->ptNetManagerQTask;
  if ( !ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    v9 = nullptr;
    if ( Timer_isPerformanceCounter )
      PerformanceCounter = Timer_GetPerformanceCounter();
    else
      PerformanceCounter = GetTickCount();
    v5->nLocalTime = PerformanceCounter
                   - Timer_nStartTime
                   + (char *)ptNetManagerQTask[6].tQTaskRefList.ptMiddle
                   - (char *)ptNetManagerQTask[6].tQTaskRefList.ptTail;
LABEL_10:
    v11 = *(char **)&Client_eQTaskType;
    while ( 1 )
    {
      if ( v9 )
      {
        v13 = v11;
        NextSiblingOfType = QTask_GetNextSiblingOfType(v9, (unsigned __int16)v11);
      }
      else
      {
        NextSiblingOfType = QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, (unsigned __int16)v11);
      }
      v9 = NextSiblingOfType;
      if ( !NextSiblingOfType )
        break;
      ptNext = (int)NextSiblingOfType[1].ptNext;
      if ( ptNext )
      {
        NetManager_SendGameMessage(ptNext, 0, NETWORKQUEUE_GUARANTEED, v5, 0x10u);
        goto LABEL_10;
      }
    }
    ptQTask[36].ptPrev = nullptr;
    NetManager_RunAlways((struct NetManager_s *)ptQTask, v13);
    NetManager_RunAlways((struct NetManager_s *)ptQTask, v15);
    eGameMessage = igi2_frame.eClientNetworkID;
  }
  ClientFromNetworkID = NetManager_GetClientFromNetworkID(eGameMessage);
  p_tQTask = &ClientFromNetworkID->tQTask;
  if ( ClientFromNetworkID )
  {
    _snprintf(igi2_frame.Buffer, 0x64u, "[%d][%s]", igi2_frame.eClientNetworkID, ClientFromNetworkID->zPlayerName);
    switch ( igi2_frame.v22 )
    {
      case 0:
        v18 = "mp/kicked";
        goto LABEL_27;
      case 1:
        Config_SetLocalizedPhrase(igi2_frame.zText, "mp/left", igi2_frame.Buffer, nullptr, nullptr);
        goto LABEL_28;
      case 2:
        Config_SetLocalizedPhrase(igi2_frame.zText, (char *)&g_ptNetManager.isWeaponsCarryOver, igi2_frame.Buffer, nullptr, nullptr);
        goto LABEL_28;
      case 3:
        v18 = "mp/shutdown";
        goto LABEL_27;
      case 4:
        Config_SetLocalizedPhrase(igi2_frame.zText, (char *)&g_ptCounterSet.tCounters[29], igi2_frame.Buffer, nullptr, nullptr);
        goto LABEL_28;
      case 5:
        LocalizedString = Config_GetLocalizedString((char *)&g_ptCounterSet.tCounters[28]);
        _snprintf(igi2_frame.zText, 0xFFu, (char *const)&g_ptCounterSet.tCounters[27].nCounter, igi2_frame.Buffer, LocalizedString);
        goto LABEL_28;
      default:
        v18 = (char *)&g_ptCounterSet.tCounters[26];
LABEL_27:
        Config_SetLocalizedPhrase(igi2_frame.zText, v18, igi2_frame.Buffer, nullptr, nullptr);
LABEL_28:
        if ( StatusScreen_ptStatusScreenQTask )
        {
          ptTail = StatusScreen_ptStatusScreenQTask[52].tQTaskRefList.ptTail;
          if ( ptTail )
            TextScroller_Add((struct TextScroller_s *)ptTail, igi2_frame.zText, TEXTSCROLLER_COLOUR_RED);
        }
        NetManager_LogMessage(igi2_frame.zText);
        NetManager_LogMessage("\r\n");
        QTask_Delete(p_tQTask);
        break;
    }
  }
  else
  {
    _snprintf(igi2_frame.zText, 0xFFu, (char *const)&g_ptCounterSet.tCounters[21], igi2_frame.eClientNetworkID);
    NetManager_LogMessage(igi2_frame.zText);
  }
}

// source: j/0/network/netmanager.c:8434  [anchor-caller]
void __cdecl NetManager_InitGameSettingsHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptNetManagerQTask; // eax
  struct QTask_s *FirstChildOfType; // esi
  struct NetMission_t *v4; // eax
  unsigned __int16 v5; // dx
  int v6; // esi
  struct QReferenceList_s *p_tQTaskRefList; // ebx
  struct QTask_s *NextSiblingOfType; // eax
  char v9; // cl
  struct Flow_t *v10; // esi
  unsigned __int16 v11; // dx
  struct QTask_s *ptHead_low; // edi
  struct QTask_s *v13; // edi
  struct QTask_s *ptPrev; // ebp
  struct QReference_s *v15; // ebp
  struct QTask_s *pxObject; // eax
  struct QTask_s *v17; // edx
  struct QTask_s *v18; // eax
  bool v19; // zf
  int *v20; // esi
  struct QTask_s *ptNext; // eax
  struct QTask_s *v22; // eax
  struct QTask_s *v23; // ecx
  struct QReference_s *ptTail; // [esp-4h] [ebp-14h]
  enum WeaponOverlayStatus_e v25; // [esp+0h] [ebp-10h]

  qmemcpy(&ptQTask[1].ptPrev, (void *)(*((_DWORD *)pxContext + 3) + 20), 0xCCu);
  MapControl_ReadState((struct NetManagerGameSettings_s *)&ptQTask[1].ptPrev);
  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  if ( LOBYTE(ptQTask[5].tQTaskChildren.ptTail) )
  {
    FirstChildOfType = QTask_GetFirstChildOfType(ptNetManagerQTask, Netshop_eQTaskType);
    FirstChildOfType[169].tQTaskChildren.ptHead = (struct QTask_s *)1;
  }
  else
  {
    FirstChildOfType = QTask_GetFirstChildOfType(ptNetManagerQTask, Netshop_eQTaskType);
    FirstChildOfType[169].tQTaskChildren.ptHead = nullptr;
  }
  WeaponType_EnumerateWeaponTypes(Netshop_HandleWeaponType, FirstChildOfType);
  AmmoType_EnumerateAmmoTypes(Netshop_HandleAmmoType, FirstChildOfType);
  Netshop_FillSlots((struct Netshop_s *)FirstChildOfType);
  v4 = NetMission_ptNetMission;
  NetMission_eCurrentObjective = SHIBYTE(ptQTask[3].ptPrev);
  NetMission_ptNetMission->nMissionEndTime = (int)ptQTask[4].tQTaskRefList.ptHead;
  v4->isStarted = true;
  ptTail = ptQTask[4].tQTaskRefList.ptTail;
  v4->nWarmupEndTime = (int)ptTail;
  NetMission_EvaluateWarmUp((int)ptTail);
  v5 = NetObjective_eQTaskType;
  v6 = 0;
  p_tQTaskRefList = &ptQTask[3].tQTaskRefList;
  do
  {
    NextSiblingOfType = QTask_GetFirstChildOfType(&NetMission_ptNetMission->tQTask, v5);
    if ( NextSiblingOfType )
    {
      while ( NextSiblingOfType[5].ptNext != (struct QTask_s *)(v6 + 1) )
      {
        NextSiblingOfType = QTask_GetNextSiblingOfType(NextSiblingOfType, v5);
        if ( !NextSiblingOfType )
          goto LABEL_14;
      }
      v9 = *((_BYTE *)&ptQTask[3].tQTaskChildren.ptHead + v6 + 3);
      if ( v9 != -1 )
      {
        if ( (struct QTask_s *)v9 == NextSiblingOfType[5].ptPrev )
          NextSiblingOfType[5].tQTaskRefList.ptTail = (struct QReference_s *)1;
        else
          NextSiblingOfType[5].ptParent = (struct QTask_s *)1;
      }
      NextSiblingOfType[5].tQTaskChildren.ptTail = (struct QTask_s *)p_tQTaskRefList->ptHead;
    }
LABEL_14:
    ++v6;
    p_tQTaskRefList = (struct QReferenceList_s *)((char *)p_tQTaskRefList + 4);
  }
  while ( v6 < 8 );
  v10 = Flow_ptFlow;
  v11 = TeamManager_eQTaskType;
  ptHead_low = (struct QTask_s *)SLOBYTE(ptQTask[3].tQTaskChildren.ptHead);
  QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, TeamManager_eQTaskType)[1].ptNext = ptHead_low;
  v13 = (struct QTask_s *)SBYTE1(ptQTask[3].tQTaskChildren.ptHead);
  QTask_GetFirstChildOfType(v10->ptNetManagerQTask, v11)[1].ptPrev = v13;
  ptPrev = ptQTask[5].ptPrev;
  if ( (unsigned int)ptPrev < 0x1000 && (v15 = Level_atLevelQTaskID[(_DWORD)ptPrev]) != nullptr )
    pxObject = (struct QTask_s *)v15->pxObject;
  else
    pxObject = nullptr;
  v17 = v10->ptNetManagerQTask;
  SpawnArea_ptActive = pxObject;
  v18 = HumanPlayer_ptQTask;
  v19 = HumanPlayer_ptQTask == nullptr;
  v17[8].ptParent = (struct QTask_s *)1;
  if ( !v19 )
  {
    v20 = (int *)&v18[33];
    ptNext = v18[33].ptNext;
    if ( ptNext )
    {
      v22 = ptNext[4].ptPrev;
      if ( v22 )
      {
        QTask_Delete(v22);
        *(_DWORD *)(*v20 + 164) = 0;
        Weapon_SetOverlayStatus(v23, v25, 0, *v20);
      }
    }
  }
}

// source: j/0/network/netmanager.c:8518  [anchor-mhash]
void __cdecl NetManager_StatsHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // edi
  int v3; // eax
  struct QTask_s **v4; // edi
  unsigned __int16 v5; // dx
  struct Flow_t *v6; // ebx
  struct QTask_s **v7; // esi
  struct QTask_s *v8; // eax
  int v9; // [esp+8h] [ebp-Ch]
  int v10; // [esp+Ch] [ebp-8h]
  int v11; // [esp+10h] [ebp-4h]
  struct QTask_s **pxContexta = *(struct QTask_s ** *)&pxContext; // [esp+1Ch] [ebp+8h] ARGSLOT

  v2 = *((_DWORD *)pxContext + 3);
  v3 = *(_DWORD *)(v2 + 16);
  v4 = (struct QTask_s **)(v2 + 8);
  pxContexta = v4;
  v9 = 0;
  if ( v3 > 0 )
  {
    v5 = Client_eQTaskType;
    v6 = Flow_ptFlow;
    v7 = v4 + 3;
    do
    {
      v8 = nullptr;
      while ( 1 )
      {
        v8 = v8 ? QTask_GetNextSiblingOfType(v8, v5) : QTask_GetFirstChildOfType(v6->ptNetManagerQTask, v5);
        if ( !v8 )
          break;
        if ( v8[1].ptNext == *v7 )
        {
          if ( ((int)v8[5].tQTaskRefList.ptMiddle & 1) != 0 )
          {
            v11 = (int)v8[7].tQTaskChildren.ptMiddle
                + (unsigned int)v8[7].tQTaskRefList.ptHead
                + (unsigned int)v8[7].tQTaskRefList.ptMiddle
                + (unsigned int)v8[7].tQTaskChildren.ptHead;
            v4 = pxContexta;
            v10 = (int)v8[7].tQTaskChildren.ptMiddle
                + (unsigned int)v8[7].tQTaskRefList.ptHead
                + (unsigned int)v8[7].tQTaskRefList.ptMiddle;
            if ( v11 > 200 )
            {
              v8[7].tQTaskChildren.ptTail = nullptr;
              v8[7].tQTaskChildren.ptMiddle = nullptr;
              v8[7].tQTaskRefList.ptMiddle = nullptr;
              v8[7].tQTaskRefList.ptHead = nullptr;
              v8[7].ptParent = nullptr;
              v8[7].tQTaskChildren.ptHead = nullptr;
              v8[7].tQTaskRefList.ptTail = nullptr;
              v8[7].ptPrev = nullptr;
              *(float *)&v8[7].ptNext = (double)v10 * 100.0 / (double)v11;
            }
          }
          else
          {
            v8[6].tQTaskRefList.ptTail = (struct QReference_s *)v7[2];
            v8[6].ptParent = v7[3];
            *(_DWORD *)&v8[6].eQTaskType = v7[4];
            *(_DWORD *)&v8[7].eQTaskType = v7[14];
            v8[7].tQTaskChildren.ptTail = v7[9];
            v8[7].tQTaskChildren.ptMiddle = v7[8];
            v8[6].tQTaskRefList.ptMiddle = (struct QReference_s *)v7[1];
            v8[7].ptParent = v7[13];
            v8[7].tQTaskRefList.ptMiddle = (struct QReference_s *)v7[11];
            v8[7].tQTaskRefList.ptHead = (struct QReference_s *)v7[10];
            v8[7].tQTaskChildren.ptHead = v7[7];
            v8[7].tQTaskRefList.ptTail = (struct QReference_s *)v7[12];
            v8[7].ptPrev = v7[6];
            v8[7].ptNext = v7[5];
          }
          if ( v6->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
          {
            v8[8].ptPrev = v7[16];
            v8[8].ptNext = v7[15];
            v8[8].tQTaskChildren.ptHead = v7[17];
          }
          break;
        }
      }
      v7 += 18;
      ++v9;
    }
    while ( v9 < (int)v4[2] );
  }
}

// source: j/0/network/netmanager.c:8630  [size]
unsigned __int16 __cdecl NetManager_GetQTaskType()
{
  return NetManager_eQTaskType;
}

// source: j/0/network/netmanager.c:8645  [size]
__int16 __cdecl NetManager_GetGameMessageCreatePlayerQTaskEvent()
{
  return NetManager_eGameMessageCreatePlayerQTaskEvent;
}

// source: j/0/network/netmanager.c:8660  [size]
__int16 __cdecl NetManager_GetGameMessageDestroyPlayerQTaskEvent()
{
  return NetManager_eGameMessageDestroyPlayerQTaskEvent;
}

// source: j/0/network/netmanager.c:8675  [size]
__int16 __cdecl NetManager_GetGameMessageInitGameSettingsQTaskEvent()
{
  return NetManager_eGameMessageInitGameSettingsQTaskEvent;
}

// source: j/0/network/netmanager.c:8690  [size]
__int16 __cdecl NetManager_GetGameMessageStatasQTaskEvent()
{
  return NetManager_eGameMessageStatsQTaskEvent;
}

// source: j/0/network/netmanager.c:8705  [size]
__int16 __cdecl NetManager_GetGameMessageListQTaskEvent()
{
  return NetManager_eGameMessageListQTaskEvent;
}

// source: j/0/network/netmanager.c:8720  [size]
__int16 __cdecl NetManager_GetGameMessagePingQTaskEvent()
{
  return NetManager_eGameMessagePingQTaskEvent;
}

// source: j/0/network/netmanager.c:8735  [size]
__int16 __cdecl NetManager_GetGameMessagePongQTaskEvent()
{
  return NetManager_eGameMessagePongQTaskEvent;
}

// source: j/0/network/netmanager.c:8750  [size]
__int16 __cdecl NetManager_GetGameMessageDamageQTaskEvent()
{
  return NetManager_eGameMessageDamageQTaskEvent;
}

// source: j/0/network/netmanager.c:8765  [size]
__int16 __cdecl NetManager_GetGameMessageSpawnQTaskEvent()
{
  return NetManager_eGameMessageSpawnQTaskEvent;
}

// source: j/0/network/netmanager.c:8780  [size]
__int16 __cdecl NetManager_GetGameMessageSpectateQTaskEvent()
{
  return NetManager_eGameMessageSpectateQTaskEvent;
}

// source: j/0/network/netmanager.c:8795  [size]
__int16 __cdecl NetManager_GetGameMessageRequestSpawnQTaskEvent()
{
  return NetManager_eGameMessageRequestSpawnQTaskEvent;
}

// source: j/0/network/netmanager.c:8810  [size]
__int16 __cdecl NetManager_GetGameMessageObjectiveQTaskEvent()
{
  return NetManager_eGameMessageObjectiveQTaskEvent;
}

// source: j/0/network/netmanager.c:8825  [size]
__int16 __cdecl NetManager_GetGameMessageBombQTaskEvent()
{
  return NetManager_eGameMessageBombQTaskEvent;
}

// source: j/0/network/netmanager.c:8840  [size]
__int16 __cdecl NetManager_GetGameMessageAuthenticateQTaskEvent()
{
  return NetManager_eGameMessageAuthenticateQTaskEvent;
}

// source: j/0/network/netmanager.c:8855  [size]
__int16 __cdecl NetManager_GetGameMessageGrenadeUpdateQTaskEvent()
{
  return NetManager_eGameMessageGrenadeUpdateQTaskEvent;
}

// source: j/0/network/netmanager.c:8870  [size]
__int16 __cdecl NetManager_GetGameMessagePickupQTaskEvent()
{
  return NetManager_eGameMessagePickupQTaskEvent;
}

// source: j/0/network/netmanager.c:8885  [size]
__int16 __cdecl NetManager_GetGameMessageRequestPickupQTaskEvent()
{
  return NetManager_eGameMessageRequestPickupQTaskEvent;
}

// source: j/0/network/netmanager.c:8900  [size]
__int16 __cdecl NetManager_GetGameMessageDropQTaskEvent()
{
  return NetManager_eGameMessageDropQTaskEvent;
}

// source: j/0/network/netmanager.c:8915  [size]
__int16 __cdecl NetManager_GetGameMessageRequestDropQTaskEvent()
{
  return NetManager_eGameMessageRequestDropQTaskEvent;
}

// source: j/0/network/netmanager.c:8930  [size]
__int16 __cdecl NetManager_GetGameMessageEquipQTaskEvent()
{
  return NetManager_eGameMessageEquipQTaskEvent;
}

// source: j/0/network/netmanager.c:8945  [size]
__int16 __cdecl NetManager_GetGameMessageTeamScoreQTaskEvent()
{
  return NetManager_eGameMessageTeamScoreQTaskEvent;
}

// source: j/0/network/netmanager.c:8960  [size]
__int16 __cdecl NetManager_GetGameMessageUpdateQTaskEvent()
{
  return NetManager_eGameMessageUpdateQTaskEvent;
}

// source: j/0/network/netmanager.c:8975  [size]
__int16 __cdecl NetManager_GetGameMessageActivateQTaskEvent()
{
  return NetManager_eGameMessageActivateQTaskEvent;
}

// source: j/0/network/netmanager.c:8990  [size]
__int16 __cdecl NetManager_GetGameMessageChatQTaskEvent()
{
  return NetManager_eGameMessageChatQTaskEvent;
}

// source: j/0/network/netmanager.c:9005  [size]
__int16 __cdecl NetManager_GetGameMessageKillQTaskEvent()
{
  return NetManager_eGameMessageKillQTaskEvent;
}

// source: j/0/network/netmanager.c:9019  [size]
__int16 __cdecl NetManager_GetGameMessageSettingsQTaskEvent()
{
  return NetManager_eGameMessageSettingsQTaskEvent;
}

// source: j/0/network/netmanager.c:9055  [size]
int __cdecl NetManager_GetSpawnMaxCost()
{
  return (int)Flow_ptFlow->ptNetManagerQTask[5].tQTaskChildren.ptHead;
}

// source: j/0/network/netmanager.c:9072  [anchor-mhash]
int __cdecl NetManager_GetMissionID()
{
  if ( NetManager_nSelectedSession == -1 )
    return (int)Flow_ptFlow->ptNetManagerQTask[3].ptNext;
  else
    return dword_704B18[60 * NetManager_nSelectedSession];
}

// source: j/0/network/netmanager.c:9099  [anchor-mhash]
struct Result_s *__cdecl NetManager_isSessionSelectedCB(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  struct Result_s *result; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  result = retstr;
  Rs.zResult = (char *)&g_zInitialValue;
  LODWORD(Rs.vResult) = 0;
  if ( NetManager_nSelectedSession == -1 )
  {
    Rs.nResult = 0;
    HIDWORD(Rs.vResult) = 0;
  }
  else
  {
    Rs.nResult = 1;
    HIDWORD(Rs.vResult) = 1072693248;
  }
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return result;
}

// source: j/0/network/netmanager.c:9122  [anchor-caller]
void __cdecl NetManager_StartServerClient()
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s ptParent; };
    struct { char igi2_o1[40]; int v8; };
    struct { char igi2_o2[44]; _DWORD v9[28]; };
    char igi2_extent[156];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Flow_t *v0; // esi
  struct QTask_s *ptNetManagerQTask; // ebp
  int FairTeam; // esi
  int i; // eax
  struct QTask_s *v4; // edi
  struct QTask_s *v5; // eax
  struct QTask_s *FirstChildOfType; // edi

  v0 = Flow_ptFlow;
  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  if ( AppContext_tAppContext.isServer == false )
  {
    FairTeam = TeamManager_GetFairTeam(-1);
    igi2_frame.ptParent.tQTaskRefList.ptHead = (struct QReference_s *)NetManager_atTeams[FairTeam].pzName;
    igi2_frame.ptParent.ptPrev = nullptr;
    igi2_frame.ptParent.ptNext = (struct QTask_s *)1;
    igi2_frame.ptParent.tQTaskChildren.ptTail = (struct QTask_s *)&ClientConfig_tClientConfig;
    igi2_frame.ptParent.tQTaskChildren.ptHead = (struct QTask_s *)FairTeam;
    LOWORD(igi2_frame.ptParent.tQTaskChildren.ptMiddle) = 1;
    igi2_frame.v8 = -1;
    igi2_frame.v9[27] = 0;
    for ( i = 0; i < 13; ++i )
    {
      igi2_frame.v9[i] = -1;
      igi2_frame.v9[i + 13] = 0;
    }
    if ( FairTeam == 1 )
      sprintf(
        (char *const)&igi2_frame.ptParent.tQTaskRefList.ptMiddle,
        "%s%d_1",
        NetManager_atBadModel[NetManager_eModel].pzModel,
        NetManager_eFace);
    else
      sprintf(
        (char *const)&igi2_frame.ptParent.tQTaskRefList.ptMiddle,
        "%s%d_1",
        NetManager_atGoodModel[NetManager_eModel].pzModel,
        NetManager_eFace);
    *(float *)&igi2_frame.v9[26] = tan(0.7853981852531433);
    v4 = Flow_ptFlow->ptNetManagerQTask;
    ++BYTE1(v4[3].ptPrev);
    QTask_NewFn(v4, Client_eQTaskType, &igi2_frame.ptParent);
    NetManager_SetLocalBandwidth(0);
    NetManager_SetTeam(FairTeam);
    v0 = Flow_ptFlow;
  }
  v5 = v0->ptNetManagerQTask;
  if ( LOBYTE(ptNetManagerQTask[5].tQTaskChildren.ptTail) )
  {
    FirstChildOfType = QTask_GetFirstChildOfType(v5, Netshop_eQTaskType);
    FirstChildOfType[169].tQTaskChildren.ptHead = (struct QTask_s *)1;
  }
  else
  {
    FirstChildOfType = QTask_GetFirstChildOfType(v5, Netshop_eQTaskType);
    FirstChildOfType[169].tQTaskChildren.ptHead = nullptr;
  }
  WeaponType_EnumerateWeaponTypes(Netshop_HandleWeaponType, FirstChildOfType);
  AmmoType_EnumerateAmmoTypes(Netshop_HandleAmmoType, FirstChildOfType);
  Netshop_FillSlots((struct Netshop_s *)FirstChildOfType);
}

// source: j/0/network/netmanager.c:9218  [anchor-caller]
void __cdecl NetManager_InitSessionData()
{
  struct QTask_s *ptNetManagerQTask; // esi
  struct QTask_s *FirstChildOfType; // eax

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  if ( NetManager_tActiveMapList.ptHead->ptNext )
    ptNetManagerQTask[3].ptNext = (struct QTask_s *)NetManager_tActiveMapList.ptHead[1].ptNext;
  NetManager_UpdateServerSettings();
  MapControl_LoadServerConfig(&ServerConfig_tServerConfig);
  FirstChildOfType = QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, MapControl_eQTaskType);
  BYTE1(ptNetManagerQTask[4].tQTaskChildren.ptMiddle) = FirstChildOfType[1].ptNext;
  ptNetManagerQTask[5].ptNext = FirstChildOfType[1].ptPrev;
  BYTE2(ptNetManagerQTask[4].tQTaskChildren.ptMiddle) = FirstChildOfType[1].tQTaskChildren.ptHead;
  LOBYTE(ptNetManagerQTask[4].tQTaskChildren.ptMiddle) = FirstChildOfType[1].tQTaskChildren.ptMiddle;
  *(_DWORD *)&ptNetManagerQTask[4].eQTaskType = FirstChildOfType[1].tQTaskChildren.ptTail;
}

// source: j/0/network/netmanager.c:9256  [anchor-hash]
int __cdecl NetManager_GetFirstActiveMap()
{
  if ( NetManager_tActiveMapList.ptHead->ptNext )
    return (int)NetManager_tActiveMapList.ptHead[1].ptNext;
  else
    return -1;
}

// source: j/0/network/netmanager.c:9288  [anchor-strings]
void __cdecl NetManager_SetupNetworkPartForServer(int nPort)
{
  #pragma pack(push, 1)
  union
  {
    struct { char *v12; };
    struct { char igi2_o1[24]; struct NetworkServerContext_s ptServerContext; };
    struct { char igi2_o2[44]; int v14; };
    struct { char igi2_o3[48]; int v15; };
    struct { char igi2_o4[56]; char Buffer[256]; };
    char igi2_extent[312];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptNetManagerQTask; // ebx
  int v2; // esi
  int nClientPort; // ebp
  struct Node_s *ptHead; // eax
  struct Node_s *ptNext; // esi
  int v6; // edi
  struct QTask_s *started; // eax
  struct Flow_t *v8; // eax
  struct Server_s *v9; // eax
  bool v10; // zf
  DWORD TickCount; // eax

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  v2 = List_Length(&Network_tAdapterList);
  if ( v2 <= 1 )
  {
    nClientPort = 0;
  }
  else
  {
    nClientPort = ServerConfig_tServerConfig.nClientPort;
    _snprintf(igi2_frame.Buffer, 0xFFu, (char *const)&g_ptCounterSet.tCounters[17], ServerConfig_tServerConfig.nClientPort);
    NetManager_LogMessage(igi2_frame.Buffer);
    if ( nClientPort >= v2 || nClientPort < 0 )
    {
      NetManager_LogMessage((char *)&g_ptCounterSet.tCounters[11].nCounter);
      nClientPort = v2 - 1;
    }
  }
  ptHead = Network_tAdapterList.ptHead;
  ptNext = Network_tAdapterList.ptHead->ptNext;
  v6 = 0;
  if ( Network_tAdapterList.ptHead->ptNext )
  {
    while ( 1 )
    {
      igi2_frame.ptServerContext.ptAdapter = (struct NetworkAdapterItem_s *)ptHead;
      igi2_frame.v12 = inet_ntoa((*(struct in_addr *)&ptHead[1].ptPrev->ptNext));
      if ( v6 == nClientPort )
        break;
      _snprintf(igi2_frame.Buffer, 0xFFu, (char *const)&g_ptCounterSet.tCounters[5], v6, igi2_frame.v12);
      NetManager_LogMessage(igi2_frame.Buffer);
      ptHead = ptNext;
      ptNext = ptNext->ptNext;
      ++v6;
      if ( !ptNext )
        goto LABEL_11;
    }
    _snprintf(igi2_frame.Buffer, 0xFFu, (char *const)&g_ptCounterSet.tCounters[8].nCounter, v6, igi2_frame.v12);
    NetManager_LogMessage(igi2_frame.Buffer);
  }
LABEL_11:
  igi2_frame.ptServerContext.nPort = nPort;
  igi2_frame.ptServerContext.pxApplicationData = &ptNetManagerQTask[1].ptPrev;
  igi2_frame.ptServerContext.nApplicationDataSize = 204;
  started = (struct QTask_s *)Network_StartServer(&igi2_frame.ptServerContext, NetManager_ServerHandler, nullptr);
  ptNetManagerQTask[1].ptNext = started;
  if ( started )
  {
    v8 = Flow_ptFlow;
    Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle = nullptr;
    ptNetManagerQTask[4].tQTaskRefList.ptMiddle = (struct QReference_s *)ServerConfig_tServerConfig.nBombTime;
    ptNetManagerQTask[4].ptParent = (struct QTask_s *)ServerConfig_tServerConfig.nPloss;
    igi2_frame.v14 = 5000;
    igi2_frame.v15 = 6000;
    v9 = (struct Server_s *)QTask_NewFn(v8->ptNetManagerQTask, Server_eQTaskType, &igi2_frame.ptServerContext);
    Server_InitNIDPool(v9);
    v10 = Timer_isPerformanceCounter == 0;
    ptNetManagerQTask[9].tQTaskChildren.ptTail = (struct QTask_s *)1;
    if ( v10 )
      TickCount = GetTickCount();
    else
      TickCount = Timer_GetPerformanceCounter();
    ptNetManagerQTask[9].tQTaskRefList.ptHead = (struct QReference_s *)(TickCount - Timer_nStartTime);
  }
  else
  {
    ptNetManagerQTask[9].tQTaskChildren.ptTail = nullptr;
    ptNetManagerQTask[9].tQTaskRefList.ptHead = (struct QReference_s *)-1;
  }
}

// source: j/0/network/netmanager.c:9364  [anchor-mhash]
void __cdecl NetManager_InitData()
{
  struct QTask_s *ptNetManagerQTask; // eax
  struct NetManagerPingNode_t *v1; // eax

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  ptNetManagerQTask[6].tQTaskRefList.ptMiddle = nullptr;
  ptNetManagerQTask[6].tQTaskRefList.ptTail = nullptr;
  ptNetManagerQTask[6].ptParent = nullptr;
  ptNetManagerQTask[8].tQTaskRefList.ptTail = nullptr;
  NetManager_nSelectedSession = -1;
  NetManager_nPingIndex = 0;
  NetManager_tPingList.ptHead = (struct Node_s *)&NetManager_tPingList.ptMiddle;
  NetManager_tPingList.ptTail = (struct Node_s *)&NetManager_tPingList;
  NetManager_tPingList.ptMiddle = nullptr;
  v1 = NetManager_atPingNode;
  do
  {
    v1->tNode.ptPrev = nullptr;
    v1->tNode.ptNext = nullptr;
    v1->nPingTime = 3000;
    v1 = (struct NetManagerPingNode_t *)(List_AddTail(v1, (int)&NetManager_tPingList) + 3);
  }
  while ( (int)v1 < 7374920 );
}

// source: j/0/network/netmanager.c:9411  [anchor-caller]
void __cdecl NetManager_SetupLocalClientNetwork()
{
  struct NetworkAdapterItem_s *ptHead; // ecx
  struct QTask_s *ptNetManagerQTask; // esi
  struct Node_s *i; // eax
  ULONG v3; // eax
  int v4; // edx
  int v5; // eax
  struct QTask_s *started; // eax
  bool v7; // zf
  struct NetworkClientContext_s tNetworkClient; // [esp+4h] [ebp-14h] BYREF

  ptHead = (struct NetworkAdapterItem_s *)Network_tAdapterList.ptHead;
  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  for ( i = Network_tAdapterList.ptHead->ptNext; i; i = i->ptNext )
  {
    tNetworkClient.ptAdapter = ptHead;
    ptHead = (struct NetworkAdapterItem_s *)i;
  }
  v3 = *((_DWORD *)&unk_704AC0 + 60 * NetManager_nSelectedSession);
  *(_DWORD *)&tNetworkClient.tSockAddr.sin_family = *((_DWORD *)&unk_704ABC + 60 * NetManager_nSelectedSession);
  v4 = *((_DWORD *)&unk_704AC4 + 60 * NetManager_nSelectedSession);
  tNetworkClient.tSockAddr.sin_addr.S_un.S_addr = v3;
  v5 = *((_DWORD *)&unk_704AC8 + 60 * NetManager_nSelectedSession);
  *(_DWORD *)tNetworkClient.tSockAddr.sin_zero = v4;
  *(_DWORD *)&tNetworkClient.tSockAddr.sin_zero[4] = v5;
  started = (struct QTask_s *)Network_StartClient(&tNetworkClient, NetManager_ClientHandler, nullptr);
  ptNetManagerQTask[6].tQTaskChildren.ptHead = started;
  if ( started )
  {
    v7 = Timer_isPerformanceCounter == 0;
    ptNetManagerQTask[9].tQTaskChildren.ptTail = (struct QTask_s *)1;
    if ( v7 )
      ptNetManagerQTask[9].tQTaskChildren.ptMiddle = (struct QTask_s *)(GetTickCount() - Timer_nStartTime);
    else
      ptNetManagerQTask[9].tQTaskChildren.ptMiddle = (struct QTask_s *)(Timer_GetPerformanceCounter() - Timer_nStartTime);
  }
  else
  {
    ptNetManagerQTask[9].tQTaskChildren.ptTail = nullptr;
  }
}

// source: j/0/network/netmanager.c:9462  [anchor-mhash]
void __cdecl NetManager_InitCommonSettings()
{
  struct QTask_s *ptNetManagerQTask; // eax

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  ptNetManagerQTask[6].tQTaskChildren.ptTail = (struct QTask_s *)-1;
  *(_DWORD *)&ptNetManagerQTask[35].eQTaskType = 0;
  NetManager_iSpawnPointID = 0;
  NetManager_iSpawnAreaID = 0;
}

// source: j/0/network/netmanager.c:9485  [anchor-strings]
_DWORD *__cdecl NetManager_RegisterGameMessage(
        struct Node_s *a1,
        __int16 eGameMessageID,
        int eQTaskEvent)
{
  struct Node_s *ptHead; // ecx
  struct Node_s *i; // eax
  _DWORD *v5; // eax
  _DWORD *result; // eax

  ptHead = result_7086a8.ptHead;
  for ( i = result_7086a8.ptHead->ptNext; i; i = i->ptNext )
  {
    if ( ptHead[1].ptNext == a1 )
    {
      LDebug_Error((char *)&g_ptCounterSet.tCounters[2].nCounter);
      abort();
    }
    ptHead = i;
  }
  v5 = Mem_AllocFn(20, 4);
  v5[1] = 0;
  *v5 = 0;
  result = List_AddTail(v5, (int)&result_7086a8);
  result[2] = a1;
  *((_WORD *)result + 6) = eGameMessageID;
  result[4] = eQTaskEvent;
  return result;
}

// source: j/0/network/netmanager.c:9526  [anchor-callee]
void __cdecl NetManager_RemoveGameMessage(unsigned int eGameMessageID)
{
  struct Node_s *ptHead; // eax
  struct Node_s *ptNext; // ecx
  int v3; // esi

  ptHead = result_7086a8.ptHead;
  ptNext = result_7086a8.ptHead->ptNext;
  if ( result_7086a8.ptHead->ptNext )
  {
    while ( ptHead[1].ptNext != (struct Node_s *)eGameMessageID )
    {
      ptHead = ptNext;
      ptNext = ptNext->ptNext;
      if ( !ptNext )
        return;
    }
    v3 = *(_DWORD *)((unsigned int)(Node_Remove(ptHead) - 1) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v3);
    memset(*(void **)(v3 + 8), 0xCDu, *(_DWORD *)(v3 + 16));
    free((void *)v3);
  }
}

// source: j/0/network/netmanager.c:9557  [anchor-mhash]
__int16 __cdecl NetManager_GetGameMessageQTaskEvent(unsigned int eGameMessageID)
{
  struct Node_s *ptHead; // ecx
  struct Node_s *ptNext; // eax

  ptHead = result_7086a8.ptHead;
  ptNext = result_7086a8.ptHead->ptNext;
  if ( !result_7086a8.ptHead->ptNext )
    return 512;
  while ( ptHead[1].ptNext != (struct Node_s *)eGameMessageID )
  {
    ptHead = ptNext;
    ptNext = ptNext->ptNext;
    if ( !ptNext )
      return 512;
  }
  return (__int16)ptHead[1].ptPrev;
}

// source: j/0/network/netmanager.c:9588  [anchor-callee]
int __cdecl NetManager_GetNewPacketID(int eDestination, int eSource)
{
  struct Node_s *ptHead; // ecx
  struct Node_s *ptNext; // eax
  _DWORD *v4; // eax
  int result; // eax

  ptHead = NetManager_tClientPacketIDs.ptHead;
  ptNext = NetManager_tClientPacketIDs.ptHead->ptNext;
  if ( NetManager_tClientPacketIDs.ptHead->ptNext )
  {
    while ( ptHead[1].ptPrev != (struct Node_s *)eDestination || ptHead[1].ptNext != (struct Node_s *)eSource )
    {
      ptHead = ptNext;
      ptNext = ptNext->ptNext;
      if ( !ptNext )
        goto LABEL_5;
    }
    result = (int)&ptHead[2].ptNext->ptNext + 1;
    ptHead[2].ptNext = (struct Node_s *)result;
  }
  else
  {
LABEL_5:
    v4 = Mem_AllocFn(20, 4);
    v4[1] = 0;
    *v4 = 0;
    v4[3] = eDestination;
    v4[2] = eSource;
    v4[4] = 0;
    return List_AddTail(v4, (int)&NetManager_tClientPacketIDs)[4];
  }
  return result;
}

// source: j/0/network/netmanager.c:9633  [anchor-strings]
void __cdecl NetManager_SendGameMessage(
        int eDestination,
        int eSource,
        enum NetworkQueue_e eQueue,
        struct NetManagerGameMessage_s *ptGameMessage,
        unsigned int nSize)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s *v18; };
    struct { char igi2_o1[4]; struct Client_s *v19; };
    struct { char igi2_o2[8]; unsigned __int8 pnData[4]; };
    struct { char igi2_o3[12]; int v21; };
    struct { char igi2_o4[16]; _DWORD v22[2046]; };
    char igi2_extent[8200];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptNetManagerQTask; // esi
  struct Client_s *ClientFromNetworkID; // eax
  unsigned int v8; // ecx
  int NewPacketID; // eax
  int nKills; // edi
  int v11; // edi
  char v12; // dl
  unsigned int v13; // ecx
  _DWORD *v14; // edi
  unsigned int *v15; // esi
  int v16; // edx
  int *p_nCounter; // eax

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  igi2_frame.v18 = ptNetManagerQTask;
  ClientFromNetworkID = NetManager_GetClientFromNetworkID(eSource);
  v8 = nSize;
  igi2_frame.v19 = ClientFromNetworkID;
  *(_DWORD *)igi2_frame.pnData = eSource;
  igi2_frame.v21 = -1;
  if ( eQueue )
  {
    NewPacketID = NetManager_GetNewPacketID(eDestination, eSource);
    v8 = nSize;
    igi2_frame.v21 = NewPacketID;
    ClientFromNetworkID = igi2_frame.v19;
  }
  if ( ClientFromNetworkID )
  {
    nKills = ClientFromNetworkID->tStats.nKills;
    ++ClientFromNetworkID->tStats.nDuplicatePacks;
    ClientFromNetworkID->tStats.nKills = v8 + 60 + nKills;
  }
  v11 = *(_DWORD *)&ptNetManagerQTask[29].eQTaskType;
  ptNetManagerQTask[30].tQTaskRefList.ptHead = (struct QReference_s *)((char *)ptNetManagerQTask[30].tQTaskRefList.ptHead
                                                                     + v8
                                                                     + 60);
  v12 = v8;
  *(_DWORD *)&ptNetManagerQTask[29].eQTaskType = v11 + 1;
  v13 = v8 >> 2;
  qmemcpy(igi2_frame.v22, ptGameMessage, 4 * v13);
  v15 = &ptGameMessage->eGameMessage + v13;
  v14 = &igi2_frame.v22[v13];
  LOBYTE(v13) = v12;
  v16 = NetworkInfo_tSendLogConsoleID;
  qmemcpy(v14, v15, v13 & 3);
  DebugConsole_PushActiveConsole(v16);
  p_nCounter = &g_ptCounterSet.tCounters[1].nCounter;
  if ( eQueue )
    p_nCounter = (int *)&g_zInitialValue;
  DebugConsole_printf(
    g_ptCounterSet.zName,
    Flow_ptFlow->nTicks,
    SHIBYTE(ptGameMessage->eGameMessage),
    SBYTE2(ptGameMessage->eGameMessage),
    SBYTE1(ptGameMessage->eGameMessage),
    SLOBYTE(ptGameMessage->eGameMessage),
    eDestination,
    nSize + 60,
    p_nCounter);
  DebugConsole_PopActiveConsole();
  NetManager_CountPacket((int)&igi2_frame.v18[19].tQTaskChildren.ptTail, nSize + 60, ptGameMessage->eGameMessage);
  Network_AddPacketToQueue(eDestination, eQueue, igi2_frame.pnData, nSize + 8);
  Network_HandleSendQueues();
}

// source: j/0/network/netmanager.c:9720  [size]
void __cdecl NetManager_SetLocalNetworkID(int eLocalID)
{
  Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle = (struct QTask_s *)eLocalID;
}

// source: j/0/network/netmanager.c:9738  [size]
int __cdecl NetManager_GetLocalNetworkID()
{
  return (int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle;
}

// source: j/0/network/netmanager.c:9756  [anchor-callee]
struct Client_s *__cdecl NetManager_GetNextClient(struct Client_s *ptCurrentClient)
{
  if ( ptCurrentClient )
    return (struct Client_s *)QTask_GetNextSiblingOfType(&ptCurrentClient->tQTask, Client_eQTaskType);
  else
    return (struct Client_s *)QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, Client_eQTaskType);
}

// source: j/0/network/netmanager.c:9785  [anchor-hash]
struct Client_s *__cdecl NetManager_GetPrevClient(struct Client_s *ptCurrentClient)
{
  if ( ptCurrentClient )
    return (struct Client_s *)QTask_GetPrevSiblingOfType(&ptCurrentClient->tQTask, Client_eQTaskType);
  else
    return (struct Client_s *)QTask_GetLastChildOfType(Flow_ptFlow->ptNetManagerQTask, Client_eQTaskType);
}

// source: j/0/network/netmanager.c:9814  [anchor-callee]
struct Client_s *__cdecl NetManager_GetClientFromNetworkID(int eClientNetworkID)
{
  unsigned __int16 v1; // dx
  struct Flow_t *v2; // esi
  struct Client_s *result; // eax

  v1 = Client_eQTaskType;
  v2 = Flow_ptFlow;
  result = nullptr;
  while ( 1 )
  {
    result = (struct Client_s *)(result
                               ? QTask_GetNextSiblingOfType(&result->tQTask, v1)
                               : QTask_GetFirstChildOfType(v2->ptNetManagerQTask, v1));
    if ( !result )
      break;
    if ( result->eNetworkID == eClientNetworkID )
      return result;
  }
  return nullptr;
}

// source: j/0/network/netmanager.c:9842  [anchor-hash]
enum bool __cdecl NetManager_isClientKnown(int eClientNetworkID)
{
  return NetManager_GetClientFromNetworkID(eClientNetworkID) != nullptr;
}

// source: j/0/network/netmanager.c:9855  [anchor-callee]
struct Client_s *__cdecl NetManager_GetClientFromHumanQTask(struct QTask_s *ptQTask)
{
  unsigned __int16 v1; // dx
  struct Flow_t *v2; // esi
  struct Client_s *result; // eax
  int nCounter; // ecx

  v1 = Client_eQTaskType;
  v2 = Flow_ptFlow;
  result = nullptr;
  do
  {
    if ( result )
      result = (struct Client_s *)QTask_GetNextSiblingOfType(&result->tQTask, v1);
    else
      result = (struct Client_s *)QTask_GetFirstChildOfType(v2->ptNetManagerQTask, v1);
    if ( !result )
    {
      LDebug_Error("Matching client not found");
      abort();
    }
    nCounter = result->tReceiveTimeBuffer.nCounter;
  }
  while ( !nCounter || *(struct QTask_s **)(nCounter + 8) != ptQTask );
  return result;
}

// source: j/0/network/netmanager.c:9885  [anchor-refs]
int __cdecl NetManager_GetClientNetworkIDFromHumanQTask(struct QTask_s *ptQTask)
{
  unsigned __int16 v1; // dx
  struct Flow_t *v2; // esi
  struct QTask_s *NextSiblingOfType; // eax
  struct QTask_s *ptHead; // ecx

  v1 = Client_eQTaskType;
  v2 = Flow_ptFlow;
  NextSiblingOfType = nullptr;
  do
  {
    if ( NextSiblingOfType )
      NextSiblingOfType = QTask_GetNextSiblingOfType(NextSiblingOfType, v1);
    else
      NextSiblingOfType = QTask_GetFirstChildOfType(v2->ptNetManagerQTask, v1);
    if ( !NextSiblingOfType )
    {
      LDebug_Error("Matching client not found");
      abort();
    }
    ptHead = NextSiblingOfType[16].tQTaskChildren.ptHead;
  }
  while ( !ptHead || ptHead->tQTaskChildren.ptHead != ptQTask );
  return (int)NextSiblingOfType[1].ptNext;
}

// source: j/0/network/netmanager.c:9914  [size]
struct QTask_s *__cdecl NetManager_GetGameItemServerQTask()
{
  return (struct QTask_s *)Flow_ptFlow->ptNetManagerQTask[6].tQTaskRefList.ptHead;
}

// source: j/0/network/netmanager.c:9932  [size]
int __cdecl NetManager_GetSpawnPointID()
{
  return NetManager_iSpawnPointID++;
}

// source: j/0/network/netmanager.c:9945  [size]
int __cdecl NetManager_GetSpawnAreaID()
{
  return NetManager_iSpawnAreaID++;
}

// source: j/0/network/netmanager.c:9958  [size]
struct NetManagerGameSettings_s *__cdecl NetManager_GetActiveSettngs()
{
  return (struct NetManagerGameSettings_s *)&Flow_ptFlow->ptNetManagerQTask[1].ptPrev;
}

// source: j/0/network/netmanager.c:9974  [anchor-callee]
void __cdecl NetManager_ForceSpawnMode()
{
  enum WeaponOverlayStatus_e v0; // edi
  struct QTask_s *v1; // eax
  bool v2; // zf
  int *v3; // esi
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *v6; // ecx

  v1 = HumanPlayer_ptQTask;
  v2 = HumanPlayer_ptQTask == nullptr;
  Flow_ptFlow->ptNetManagerQTask[8].ptParent = (struct QTask_s *)1;
  if ( !v2 )
  {
    v3 = (int *)&v1[33];
    ptNext = v1[33].ptNext;
    if ( ptNext )
    {
      ptPrev = ptNext[4].ptPrev;
      if ( ptPrev )
      {
        QTask_Delete(ptPrev);
        *(_DWORD *)(*v3 + 164) = 0;
        Weapon_SetOverlayStatus(v6, v0, 0, *v3);
      }
    }
  }
}

// source: j/0/network/netmanager.c:10017  [anchor-callee]
int __cdecl NetManager_GetTimer()
{
  struct QTask_s *ptNetManagerQTask; // esi
  DWORD PerformanceCounter; // eax

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  return PerformanceCounter
       - Timer_nStartTime
       + (char *)ptNetManagerQTask[6].tQTaskRefList.ptMiddle
       - (char *)ptNetManagerQTask[6].tQTaskRefList.ptTail;
}

// source: j/0/network/netmanager.c:10035  [size]
char *__cdecl NetManager_GetTeamName(int eTeam)
{
  return NetManager_atTeams[eTeam].pzName;
}

// source: j/0/network/netmanager.c:10048  [anchor-callee]
int __cdecl NetManager_GetTeamModelName(
        char *pzModel,
        int eTeam,
        int eModel,
        int eFace)
{
  if ( !eTeam )
    return sprintf(pzModel, "%s%d_1", NetManager_atGoodModel[eModel].pzModel, eFace);
  if ( eTeam == 1 )
    return sprintf(pzModel, "%s%d_1", NetManager_atBadModel[eModel].pzModel, eFace);
  return eFace;
}

// source: j/0/network/netmanager.c:10075  [anchor-callee]
struct Client_s *__cdecl NetManager_GetAnyClientOnTeam(int eTeam)
{
  unsigned __int16 v1; // dx
  struct Flow_t *v2; // esi
  struct Client_s *result; // eax

  v1 = Client_eQTaskType;
  v2 = Flow_ptFlow;
  result = nullptr;
  while ( 1 )
  {
    result = (struct Client_s *)(result
                               ? QTask_GetNextSiblingOfType(&result->tQTask, v1)
                               : QTask_GetFirstChildOfType(v2->ptNetManagerQTask, v1));
    if ( !result )
      break;
    if ( result->eTeam == eTeam )
      return result;
  }
  return nullptr;
}

// source: j/0/network/netmanager.c:10106  [anchor-strings]
void __cdecl NetManager_SetTeam(int eTeam)
{
  struct Client_s *ClientFromNetworkID; // ecx
  unsigned __int16 v2; // di
  unsigned __int16 v3; // si
  int v4; // ebx
  struct QTask_s *FirstChildOfType; // eax
  struct QTask_s *NextSiblingOfType; // eax
  bool v7; // zf
  struct Client_s *v8; // [esp+8h] [ebp-4h]

  ClientFromNetworkID = NetManager_GetClientFromNetworkID((int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
  v8 = ClientFromNetworkID;
  if ( ClientFromNetworkID )
  {
    if ( NetMission_eCurrentObjective > 0 )
    {
      v2 = NetObjective_eQTaskType;
      v3 = SpawnArea_eQTaskType;
      v4 = NetMission_eCurrentObjective;
      do
      {
LABEL_5:
        FirstChildOfType = QTask_GetFirstChildOfType(&NetMission_ptNetMission->tQTask, v2);
        if ( FirstChildOfType )
        {
          while ( FirstChildOfType[5].ptNext != (struct QTask_s *)v4 )
          {
            FirstChildOfType = QTask_GetNextSiblingOfType(FirstChildOfType, v2);
            if ( !FirstChildOfType )
              goto LABEL_8;
          }
        }
        else
        {
LABEL_8:
          FirstChildOfType = nullptr;
        }
        NextSiblingOfType = QTask_GetFirstChildOfType(FirstChildOfType, v3);
        --v4;
      }
      while ( !NextSiblingOfType );
      while ( NextSiblingOfType[6].tQTaskChildren.ptHead != (struct QTask_s *)eTeam )
      {
        NextSiblingOfType = QTask_GetNextSiblingOfType(NextSiblingOfType, v3);
        if ( !NextSiblingOfType )
          goto LABEL_5;
      }
      ClientFromNetworkID = v8;
      SpawnArea_ptActive = NextSiblingOfType;
    }
    v7 = NetManager_eMode == NETMANAGER_MODE_WARMUP;
    ClientFromNetworkID->eTeam = eTeam;
    if ( !v7 )
      NetManager_eTeam = eTeam;
  }
  else
  {
    NetManager_LogMessage("NetManager_SetTeam: Local client is null\n");
  }
}

// source: j/0/network/netmanager.c:10159  [size]
int __cdecl NetManager_GetMode()
{
  return NetManager_eMode;
}

// source: j/0/network/netmanager.c:10174  [anchor-mhash]
void __cdecl NetManager_SetDeathTimer(struct Client_s *ptClient)
{
  struct QTask_s *ptNetManagerQTask; // esi
  DWORD PerformanceCounter; // eax

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  ptClient->isSpectateFirstPerson = PerformanceCounter
                                  - Timer_nStartTime
                                  + (char *)ptNetManagerQTask[6].tQTaskRefList.ptMiddle
                                  - (char *)ptNetManagerQTask[6].tQTaskRefList.ptTail;
}

// source: j/0/network/netmanager.c:10197  [anchor-strings]
enum bool __cdecl NetManager_ForceChangeTeam()
{
  char Buffer[256]; // [esp+0h] [ebp-100h] BYREF

  if ( !BYTE2(Flow_ptFlow->ptNetManagerQTask[5].tQTaskChildren.ptTail)
    || NetManager_eRequestedTeam == -1
    || NetManager_eRequestedTeam == NetManager_eTeam )
  {
    return false;
  }
  _snprintf(
    Buffer,
    0xFFu,
    "NetManager_ForceChangeTeam: Changing team from %d to %d\n",
    NetManager_eTeam,
    NetManager_eRequestedTeam);
  NetManager_LogMessage(Buffer);
  NetManager_SetTeam(NetManager_eRequestedTeam);
  NetManager_eRequestedTeam = -1;
  return true;
}

// source: j/0/network/netmanager.c:10245  [anchor-callee]
void __cdecl NetManager_SetMode(int eMode)
{
  enum NetManagerMode_e v1; // ebp
  enum bool v2; // eax
  char *LocalizedStringForLanguage; // eax
  struct Client_s *ClientFromNetworkID; // eax
  struct QTask_s *v5; // esi
  struct QTask_s *v6; // eax
  bool v7; // zf

  v1 = eMode;
  if ( BYTE2(Flow_ptFlow->ptNetManagerQTask[5].tQTaskChildren.ptTail) && eMode != 10 )
  {
    v2 = NetManager_ForceChangeTeam();
    if ( !eMode )
    {
      if ( v2 == false )
      {
LABEL_8:
        v1 = NETMANAGER_MODE_SELECTSKIN;
        NetManager_nBodySprite = 0;
        NetManager_nFaceSprite = 0;
        NetManager_isModelSelect = true;
        goto LABEL_9;
      }
LABEL_7:
      LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                     "mp/FORCE_TEAM_CHANGE",
                                     Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                     true);
      StatusScreen_ShowMessage(LocalizedStringForLanguage, TEXTSCROLLER_COLOUR_WHITE);
      goto LABEL_8;
    }
    if ( v2 )
      goto LABEL_7;
  }
LABEL_9:
  if ( NetMission_isWarmUp && v1 == NETMANAGER_MODE_PLAY )
  {
    NetManager_eMode = NETMANAGER_MODE_WARMUP;
  }
  else
  {
    ClientFromNetworkID = NetManager_GetClientFromNetworkID((int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
    if ( ClientFromNetworkID )
      NetManager_eTeam = ClientFromNetworkID->eTeam;
    NetManager_eMode = v1;
  }
  v5 = MenuManager_ptQTask;
  LOBYTE(MenuManager_ptQTask[243].eQTaskType) = 1;
  switch ( v1 )
  {
    case NETMANAGER_MODE_SELECTTEAM:
      v5[1].ptNext = (struct QTask_s *)995;
      v5[1].tQTaskChildren.ptMiddle = nullptr;
      break;
    case NETMANAGER_MODE_SELECTSKIN:
      if ( !LOBYTE(HumanPlayer_ptQTask[29].tQTaskRefList.ptHead) )
      {
        NetManager_KillClient((int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
        v5 = MenuManager_ptQTask;
      }
      v5[1].ptNext = (struct QTask_s *)996;
      v5[1].tQTaskChildren.ptMiddle = nullptr;
      break;
    case NETMANAGER_MODE_SPECTATE:
      v5[1].ptNext = (struct QTask_s *)984;
      v5[1].tQTaskChildren.ptMiddle = nullptr;
      break;
    case NETMANAGER_MODE_SHOP:
      Netshop_SetActiveSlotSelector();
      SlotSelector_ptActiveSelector->ptActiveCategory = nullptr;
      v5[1].ptNext = (struct QTask_s *)907;
      v5[1].tQTaskChildren.ptMiddle = (struct QTask_s *)2;
      break;
    case NETMANAGER_MODE_RADIO:
      LOBYTE(v5[243].eQTaskType) = 0;
      v5[1].ptNext = (struct QTask_s *)908;
      v5[1].tQTaskChildren.ptMiddle = (struct QTask_s *)2;
      break;
    case NETMANAGER_MODE_SPAWN:
      LOBYTE(v5[243].eQTaskType) = 0;
      NetManager_ForceSpawnMode();
      break;
    case NETMANAGER_MODE_WARMUP:
    case NETMANAGER_MODE_PLAY:
      v6 = HumanPlayer_ptQTask;
      v7 = HumanPlayer_ptQTask == nullptr;
      LOBYTE(v5[243].eQTaskType) = 0;
      if ( !v7 && LOBYTE(v6[29].tQTaskRefList.ptHead) )
        NetManager_SetMode(2);
      if ( v1 == NETMANAGER_MODE_WARMUP )
        NetManager_eTeam = -1;
      break;
    default:
      return;
  }
}

// source: j/0/network/netmanager.c:10388  [anchor-mhash]
struct Result_s *__cdecl NetManager_SetModeCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->isQVM )
  {
    ptArgList = nullptr;
    QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
    v4 = ptArgList;
  }
  else
  {
    v4 = (struct ArgList_s *)Expression_EvalInt(*ptArgList->aptExpression);
  }
  NetManager_SetMode((int)v4);
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/netmanager.c:10407  [anchor-mhash]
struct Result_s *__cdecl NetManager_isModeCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // eax
  bool v5; // zf
  struct Result_s *result; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->isQVM )
  {
    ptArgList = nullptr;
    QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
    v4 = ptArgList;
  }
  else
  {
    v4 = (struct ArgList_s *)Expression_EvalInt(*ptArgList->aptExpression);
  }
  v5 = NetManager_eMode == (_DWORD)v4;
  result = retstr;
  Rs.zResult = (char *)&g_zInitialValue;
  LODWORD(Rs.vResult) = 0;
  if ( v5 )
  {
    Rs.nResult = 1;
    HIDWORD(Rs.vResult) = 1072693248;
  }
  else
  {
    Rs.nResult = 0;
    HIDWORD(Rs.vResult) = 0;
  }
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return result;
}

// source: j/0/network/netmanager.c:10432  [anchor-hash]
void __cdecl NetManager_ResurrectHumans()
{
  struct QTask_s *p_tQTask; // edi
  struct Client_s *v1; // eax

  p_tQTask = nullptr;
  while ( 1 )
  {
    v1 = (struct Client_s *)(p_tQTask
                           ? QTask_GetNextSiblingOfType(p_tQTask, Client_eQTaskType)
                           : QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, Client_eQTaskType));
    p_tQTask = &v1->tQTask;
    if ( !v1 )
      break;
    Client_CreateHuman(v1);
  }
}

// source: j/0/network/netmanager.c:10459  [anchor-mhash]
void __cdecl NetManager_FillScoreboard()
{
  unsigned __int16 v0; // dx
  struct QTask_s *v1; // esi
  struct Flow_t *v2; // edi
  struct QTask_s *i; // eax

  v0 = Client_eQTaskType;
  v1 = StatusScreen_ptStatusScreenQTask;
  v2 = Flow_ptFlow;
  for ( i = nullptr; ; *((_DWORD *)&v1[49].tQTaskChildren.ptHead + (*(_DWORD *)&v1[48].eQTaskType)++) = i )
  {
    i = i ? QTask_GetNextSiblingOfType(i, v0) : QTask_GetFirstChildOfType(v2->ptNetManagerQTask, v0);
    if ( !i )
      break;
  }
}

// source: j/0/network/netmanager.c:10487  [anchor-strings]
struct Result_s *__cdecl NetManager_ListSocketsCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct Result_s Rs; };
    struct { char igi2_o1[24]; char zIP[256]; };
    char igi2_extent[280];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v3; // ebx
  struct QTask_s *v4; // eax
  int ptNext; // esi

  v3 = nullptr;
  while ( 1 )
  {
    v4 = v3
       ? QTask_GetNextSiblingOfType(v3, Client_eQTaskType)
       : QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, Client_eQTaskType);
    v3 = v4;
    if ( !v4 )
      break;
    ptNext = (int)v4[1].ptNext;
    Network_GetHostnameByNetworkID(igi2_frame.zIP, 255, ptNext);
    DebugConsole_printf("[%d]: %s\n", ptNext, igi2_frame.zIP);
  }
  igi2_frame.Rs.nResult = 0;
  igi2_frame.Rs.vResult = 0.0;
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/netmanager.c:10518  [anchor-strings]
void __cdecl NetManager_LocalRestartMap()
{
  struct QTask_s *ptNetManagerQTask; // esi
  struct QTask_s *v1; // eax
  struct Client_s *ClientFromNetworkID; // eax
  struct QTask_s *v3; // eax
  struct QTask_s *v4; // ecx
  unsigned int v5; // ecx
  bool v6; // sf
  int v7; // eax
  struct QTask_s *v8; // eax
  enum NetManagerMode_e v9; // edi
  char *v10; // ecx
  char *v11; // ecx
  char *v12; // ecx
  struct Flow_t *v13; // ebp
  enum NetManagerMode_e v14; // esi
  char *LocalizedStringForLanguage; // eax
  struct Client_s *v16; // eax
  struct QTask_s *v17; // esi
  int v18; // [esp+10h] [ebp-4h]

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  if ( ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    NetManager_LogMessage("Waiting for server to start loading...\n");
    if ( NetManager_WaitUntilState(true, 2, 0.15000000596046448, 50) == false )
    {
LABEL_3:
      NetManager_LogMessage("NetManager_LocalRestartMap: Server did not send map finished, exiting game...\n");
      NetManager_LeaveGame();
      NetManager_Quit();
      return;
    }
    if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
    {
      v1 = Flow_ptFlow->ptNetManagerQTask;
      v1[8].tQTaskRefList.ptMiddle = nullptr;
      v1[9].tQTaskRefList.ptMiddle = (struct QReference_s *)-1;
      NetManager_LogMessage((char *)&stru_6A1E00.tServerGameSettings.nMissionTime);
    }
  }
  ClientFromNetworkID = NetManager_GetClientFromNetworkID((int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
  if ( ClientFromNetworkID )
    Client_CancelTalk(ClientFromNetworkID);
  v3 = Flow_ptFlow->ptNetManagerQTask;
  v4 = (struct QTask_s *)((char *)&v3[32].tQTaskChildren.ptTail->ptNext + 1);
  v3[32].tQTaskChildren.ptTail = v4;
  *((_DWORD *)&v3[31].tQTaskChildren.ptTail + (_DWORD)v4) = 1;
  Game_MPRunNetwork((char *)v4);
  NetMission_Restart();
  v5 = (NetManager_tRandomState.anRandom[0] >> 7) ^ NetManager_tRandomState.anRandom[2];
  v6 = (int)((v5 ^ NetManager_tRandomState.anRandom[1]) + NetManager_tRandomState.anRandom[0]) < 0;
  v7 = (v5 ^ NetManager_tRandomState.anRandom[1]) + NetManager_tRandomState.anRandom[0];
  NetManager_tRandomState.anRandom[2] = v5;
  NetManager_tRandomState.anRandom[1] ^= v5;
  NetManager_tRandomState.anRandom[0] = v7;
  NetManager_nRandomInt = v7;
  if ( v6 )
    NetManager_nRandomInt = -v7;
  Game_MPRunNetwork((char *)v5);
  v8 = Flow_ptFlow->ptNetManagerQTask;
  v9 = NetManager_eMode;
  v8[6].tQTaskChildren.ptTail = (struct QTask_s *)-1;
  *(_DWORD *)&v8[35].eQTaskType = 0;
  NetManager_iSpawnPointID = 0;
  NetManager_iSpawnAreaID = 0;
  ptNetManagerQTask[9].ptPrev = (struct QTask_s *)1;
  Game_Restart();
  Game_MPRunNetwork(v10);
  NetManager_ResurrectHumans();
  Game_MPRunNetwork(v11);
  Game_LoadCarryOverMP(Game_iMissionID);
  ptNetManagerQTask[9].ptPrev = nullptr;
  Game_MPRunNetwork(v12);
  v13 = Flow_ptFlow;
  --Flow_ptFlow->ptNetManagerQTask[32].tQTaskChildren.ptTail;
  if ( v13->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    NetManager_LogMessage("Waiting for server to finish loading...\n");
    if ( NetManager_WaitUntilState(false, 2, 0.15000000596046448, 50) == false )
      goto LABEL_3;
    NetManager_SetStartGameStatus(true);
    v13 = Flow_ptFlow;
  }
  if ( (unsigned int)v9 < NETMANAGER_MODE_SPECTATE
    || v9 == NETMANAGER_MODE_SHOP
    || v9 == NETMANAGER_MODE_SPECTATE
    || v9 == NETMANAGER_MODE_WELCOME )
  {
    NetManager_SetMode(v9);
  }
  else
  {
    v14 = NETMANAGER_MODE_SPAWN;
    v18 = 5;
    if ( BYTE2(v13->ptNetManagerQTask[5].tQTaskChildren.ptTail) )
    {
      if ( NetManager_ForceChangeTeam() )
      {
        LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                       "mp/FORCE_TEAM_CHANGE",
                                       Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                       true);
        StatusScreen_ShowMessage(LocalizedStringForLanguage, TEXTSCROLLER_COLOUR_WHITE);
        v18 = 1;
        NetManager_nBodySprite = 0;
        NetManager_nFaceSprite = 0;
        NetManager_isModelSelect = true;
        v14 = NETMANAGER_MODE_SELECTSKIN;
      }
      v13 = Flow_ptFlow;
    }
    v16 = NetManager_GetClientFromNetworkID((int)v13->ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
    if ( v16 )
      NetManager_eTeam = v16->eTeam;
    NetManager_eMode = v14;
    v17 = MenuManager_ptQTask;
    LOBYTE(MenuManager_ptQTask[243].eQTaskType) = 1;
    switch ( v18 )
    {
      case 1:
        if ( !LOBYTE(HumanPlayer_ptQTask[29].tQTaskRefList.ptHead) )
        {
          NetManager_KillClient((int)v13->ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
          v17 = MenuManager_ptQTask;
        }
        v17[1].ptNext = (struct QTask_s *)996;
        v17[1].tQTaskChildren.ptMiddle = nullptr;
        break;
      case 5:
        LOBYTE(v17[243].eQTaskType) = 0;
        NetManager_ForceSpawnMode();
        break;
    }
  }
}

// source: j/0/network/netmanager.c:10650  [anchor-strings]
void __cdecl NetManager_InitiateRestart()
{
  struct QTask_s *ptNetManagerQTask; // eax
  bool v1; // zf
  struct QTask_s *v2; // esi
  DWORD TickCount; // eax
  char Buffer[44]; // [esp+10h] [ebp-2Ch] BYREF

  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
    ptNetManagerQTask[8].tQTaskRefList.ptMiddle = nullptr;
    ptNetManagerQTask[9].tQTaskRefList.ptMiddle = (struct QReference_s *)-1;
    NetManager_LogMessage((char *)&stru_6A1E00.tServerGameSettings.nMissionTime);
  }
  QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, MapControl_eQTaskType)[1].ptParent = (struct QTask_s *)1;
  NetManager_LogMessage("MapControl_SetLoading(): set toTRUE\n");
  NetManager_SendScoreUpdate();
  TeamManager_Rebalance();
  _snprintf(Buffer, 0x28u, "NetManager_RestartMap()");
  NetworkCommand_RemoteEval(nullptr, (int)Buffer, NETMANAGER_HOSTSET_ALL_EXCEPT_GIVEN);
  NetManager_LocalRestartMap();
  NetManager_UpdateServerSettings();
  QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, MapControl_eQTaskType)[1].ptParent = nullptr;
  NetManager_LogMessage("MapControl_SetLoading(): set to FALSE\n");
  NetManager_SendScoreUpdate();
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    v1 = Timer_isPerformanceCounter == 0;
    v2 = Flow_ptFlow->ptNetManagerQTask;
    v2[8].tQTaskRefList.ptMiddle = (struct QReference_s *)1;
    if ( v1 )
      TickCount = GetTickCount();
    else
      TickCount = Timer_GetPerformanceCounter();
    v2[9].tQTaskRefList.ptMiddle = (struct QReference_s *)(TickCount - Timer_nStartTime);
    NetManager_SetLocalBandwidth(ClientConfig_tClientConfig.nBandwidth);
    NetManager_LogMessage((char *)&stru_6A1E00.tServerGameSettings.nSpawnAreaTaskID);
  }
}

// source: j/0/network/netmanager.c:10685  [anchor-strings]
void __cdecl NetManager_InitiateChangeMap(int nMap)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s *v15; };
    struct { char igi2_o1[4]; char Buffer[40]; };
    char igi2_extent[44];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v1; // eax
  struct Flow_t *v2; // ebx
  unsigned __int16 v3; // dx
  struct QTask_s *v4; // eax
  struct QTask_s *v5; // edi
  struct QTask_s *ptNext; // esi
  struct Client_s *v7; // eax
  int nUpdateItemTime; // edx
  int nMoneyCap; // ecx
  bool v10; // zf
  char *zTeamName; // ecx
  struct QTask_s *ptNetManagerQTask; // eax
  struct QTask_s *v13; // eax
  int v14; // edx

  v1 = nullptr;
  while ( 1 )
  {
    v2 = Flow_ptFlow;
    v3 = Client_eQTaskType;
    v4 = v1
       ? QTask_GetNextSiblingOfType(v1, Client_eQTaskType)
       : QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, Client_eQTaskType);
    v5 = v4;
    igi2_frame.v15 = v4;
    if ( !v4 )
      break;
    ptNext = v4[1].ptNext;
    v7 = nullptr;
    while ( 1 )
    {
      v7 = (struct Client_s *)(v7
                             ? QTask_GetNextSiblingOfType(&v7->tQTask, v3)
                             : QTask_GetFirstChildOfType(v2->ptNetManagerQTask, v3));
      if ( !v7 )
        break;
      if ( (struct QTask_s *)v7->eNetworkID == ptNext )
        goto LABEL_14;
    }
    v7 = nullptr;
LABEL_14:
    nUpdateItemTime = v7->nUpdateItemTime;
    nMoneyCap = ServerConfig_tServerConfig.nMoneyCap;
    if ( ServerConfig_tServerConfig.nMoneyCap >= 0 )
    {
      if ( ServerConfig_tServerConfig.nMoneyKill < ServerConfig_tServerConfig.nMoneyCap )
        nMoneyCap = ServerConfig_tServerConfig.nMoneyKill;
    }
    else
    {
      nMoneyCap = 0;
    }
    v7->nUpdateItemTime = nMoneyCap;
    v10 = nUpdateItemTime == nMoneyCap;
    zTeamName = &g_zMessage.zTeamName[24];
    if ( v10 )
      zTeamName = g_zMessage.zTeamName;
    Client_UpdateMoneyRemote(v7, zTeamName);
    v1 = igi2_frame.v15;
    v5[8].ptNext = nullptr;
    v5[8].ptPrev = nullptr;
    v5[8].tQTaskChildren.ptHead = nullptr;
  }
  QTask_GetFirstChildOfType(v2->ptNetManagerQTask, MapControl_eQTaskType)[1].ptParent = (struct QTask_s *)1;
  NetManager_LogMessage("MapControl_SetLoading(): set toTRUE\n");
  NetManager_SendScoreUpdate();
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
    ptNetManagerQTask[8].tQTaskRefList.ptMiddle = nullptr;
    ptNetManagerQTask[9].tQTaskRefList.ptMiddle = (struct QReference_s *)-1;
    NetManager_LogMessage((char *)&stru_6A1E00.tServerGameSettings.nMissionTime);
  }
  TeamManager_Rebalance();
  _snprintf(igi2_frame.Buffer, 0x28u, "NetManager_GotoMap(%d)", nMap);
  NetworkCommand_RemoteEval(nullptr, (int)igi2_frame.Buffer, NETMANAGER_HOSTSET_ALL_EXCEPT_GIVEN);
  NetManager_ChangeLocalMap(nMap);
  v13 = Flow_ptFlow->ptNetManagerQTask;
  v14 = (int)&v13[32].tQTaskChildren.ptTail->ptNext + 1;
  v13[32].tQTaskChildren.ptTail = (struct QTask_s *)v14;
  *((_DWORD *)&v13[31].tQTaskChildren.ptTail + v14) = 1;
  NetMission_Restart();
  --Flow_ptFlow->ptNetManagerQTask[32].tQTaskChildren.ptTail;
}

// source: j/0/network/netmanager.c:10758  [anchor-strings]
struct Result_s *__cdecl NetManager_RestartmapCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct QTask_s *ptMiddle; // esi
  __int32 isSuperUser; // eax
  char *v5; // edx
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_10;
  ptMiddle = Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle;
  if ( ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_7;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
LABEL_10:
    v5 = "Not remote or not authorized";
    goto LABEL_11;
  }
LABEL_7:
  if ( ptMiddle )
  {
    NetManager_LocalRestartMap();
    v5 = "Restartmap received";
LABEL_11:
    NetworkCommand_SetEvalResponse(v5);
    goto LABEL_12;
  }
  NetManager_InitiateRestart();
LABEL_12:
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/netmanager.c:10785  [anchor-strings]
void __cdecl NetManager_GotoMap(int nMap)
{
  struct QTask_s *ptMiddle; // esi
  __int32 isSuperUser; // eax

  if ( NetworkCommand_eEvalNetworkID == -1 )
  {
    DebugConsole_printf("Must be called using 'sv'\n");
    return;
  }
  ptMiddle = Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle;
  if ( ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_9;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    NetworkCommand_SetEvalResponse("Not authorized to change map");
    return;
  }
LABEL_9:
  if ( ptMiddle )
  {
    NetManager_ChangeLocalMap(nMap);
    NetworkCommand_SetEvalResponse("Restartmap received");
  }
  else
  {
    NetManager_InitiateChangeMap(nMap);
  }
  NetMission_isWarmUp = false;
}

// source: j/0/network/netmanager.c:10820  [anchor-hash]
void __cdecl NetManager_GotoNext()
{
  struct Mission_s *NextMap; // esi

  NextMap = NetManager_GetNextMap();
  DebugConsole_printf("Next map is id=%d\n", NextMap->iID);
  NetManager_GotoMap(NextMap->iID);
}

// source: j/0/network/netmanager.c:10839  [anchor-strings]
struct Result_s *__cdecl NetManager_GotoNextCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct Mission_s *NextMap; // esi
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  NextMap = NetManager_GetNextMap();
  DebugConsole_printf("Next map is id=%d\n", NextMap->iID);
  NetManager_GotoMap(NextMap->iID);
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/netmanager.c:10853  [anchor-strings]
struct Result_s *__cdecl NetManager_GotoMapCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  int v3; // eax
  struct Node_s *ptHead; // edx
  struct Node_s *ptNext; // ecx
  _DWORD v7[6]; // [esp+8h] [ebp-18h] BYREF

  if ( ptArgList && ptArgList->nArguments == 1 )
  {
    v3 = Script_EvalArgInt(ptArgList, 0);
    ptHead = Mission_tMissions.ptHead;
    ptNext = Mission_tMissions.ptHead->ptNext;
    if ( Mission_tMissions.ptHead->ptNext )
    {
      while ( ptHead[1].ptNext != (struct Node_s *)v3 )
      {
        ptHead = ptNext;
        ptNext = ptNext->ptNext;
        if ( !ptNext )
          goto LABEL_6;
      }
      NetManager_GotoMap(v3);
    }
    else
    {
LABEL_6:
      DebugConsole_printf("NetManager_GotoMap: Invalid map number\n");
    }
  }
  else
  {
    DebugConsole_printf("NetManager_GotoMap: Invalid parameters\n");
  }
  v7[0] = 0;
  v7[2] = 0;
  v7[3] = 0;
  v7[4] = &g_zInitialValue;
  qmemcpy(retstr, v7, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/netmanager.c:10882  [anchor-strings]
struct Result_s *__cdecl NetManager_SetBandwidthFromRemoteCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct Result_s Rs; };
    struct { char igi2_o1[24]; char zTemp[256]; };
    char igi2_extent[280];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptMiddle; // esi
  __int32 isSuperUser; // eax
  char *v5; // edx
  unsigned int v6; // eax
  int v7; // ebx

  if ( NetworkCommand_eEvalNetworkID == -1 )
    goto LABEL_15;
  ptMiddle = Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle;
  if ( ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_7;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
LABEL_15:
    v5 = "RBw: Not remote or not auth.";
    goto LABEL_16;
  }
LABEL_7:
  if ( !ptMiddle )
  {
    v5 = "RBw: No effect on server";
LABEL_16:
    NetworkCommand_SetEvalResponse(v5);
    goto LABEL_17;
  }
  if ( ptArgList && ptArgList->nArguments == 1 )
  {
    v6 = Script_EvalArgInt(ptArgList, 0);
    v7 = v6;
    if ( v6 > 0x3E8 )
    {
      _snprintf(igi2_frame.zTemp, 0xFFu, "SetBandwidthFromRemoteCB: Server requesting net usage set to bad value: %d\n", v6);
      NetManager_LogMessage(igi2_frame.zTemp);
    }
    else
    {
      _snprintf(igi2_frame.zTemp, 0xFFu, "SetBandwidthFromRemoteCB: Server requesting bandwidth change to %d\n", v6);
      NetManager_LogMessage(igi2_frame.zTemp);
      NetManager_SetLocalBandwidth(v7);
    }
  }
  else
  {
    DebugConsole_printf("SetBandwidthFromRemoteCB: Invalid parameters\n");
  }
LABEL_17:
  igi2_frame.Rs.nResult = 0;
  igi2_frame.Rs.vResult = 0.0;
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/netmanager.c:10930  [anchor-strings]
struct Result_s *__cdecl NetManager_RemoteBandwidthCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct Result_s Rs; };
    struct { char igi2_o1[24]; char zTemp[256]; };
    char igi2_extent[280];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v3; // edi
  unsigned int v4; // ebx
  struct Client_s *ClientFromNetworkID; // eax
  struct Client_s *v6; // esi

  if ( NetworkCommand_eEvalNetworkID != -1 || Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    NetworkCommand_SetEvalResponse((char *)&g_ptNetManager.tSendCounters.tCounters[3]);
  }
  else if ( ptArgList && ptArgList->nArguments == 2 )
  {
    v3 = Script_EvalArgInt(ptArgList, 0);
    v4 = Script_EvalArgInt(ptArgList, 1);
    ClientFromNetworkID = NetManager_GetClientFromNetworkID(v3);
    v6 = ClientFromNetworkID;
    if ( ClientFromNetworkID && ClientFromNetworkID->eNetworkID && v4 <= 0x3E8 )
    {
      _snprintf(igi2_frame.zTemp, 0xFFu, "NetManager_RemoteBandwidthCB called with good params [%d]: b=%d\n", v3, v4);
      NetManager_LogMessage(igi2_frame.zTemp);
      NetManager_SetRemoteBandwidth(v6, v4);
    }
    else
    {
      _snprintf(igi2_frame.zTemp, 0xFFu, "NetManager_RemoteBandwidthCB called with bad params [%d]: b=%d\n", v3, v4);
      NetManager_LogMessage(igi2_frame.zTemp);
    }
  }
  else
  {
    NetManager_LogMessage("NetManager_RemoteBandwidthCB called with bad parameters\n");
  }
  igi2_frame.Rs.nResult = 0;
  igi2_frame.Rs.vResult = 0.0;
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/netmanager.c:10985  [anchor-hash]
int __cdecl NetManager_GetKickMin()
{
  int result; // eax

  result = (__int64)((double)SBYTE1(Flow_ptFlow->ptNetManagerQTask[3].ptPrev) * 0.4000000059604645 + 0.5);
  if ( result < 2 )
    return 2;
  return result;
}

// source: j/0/network/netmanager.c:11032  [anchor-strings]
void __cdecl NetManager_CountKickVotes()
{
  #pragma pack(push, 1)
  union
  {
    struct { _DWORD v11[32]; };
    struct { char igi2_o1[128]; enum NetManagerHostSet_e v12[32]; };
    struct { char igi2_o2[256]; char eSet[40]; };
    struct { char igi2_o3[296]; char Buffer[256]; };
    char igi2_extent[552];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  unsigned __int16 v0; // dx
  int v1; // ebx
  struct QTask_s *i; // eax
  struct QTask_s *ptParent; // esi
  int v4; // ecx
  enum NetManagerHostSet_e v5; // eax
  int v6; // ebx
  int j; // ecx
  struct Flow_t *v8; // esi
  int v9; // ecx
  struct QTask_s *v10; // eax

  v0 = Client_eQTaskType;
  memset(igi2_frame.v11, 0xFFu, sizeof(igi2_frame.v11));
  memset(igi2_frame.v12, 0, sizeof(igi2_frame.v12));
  v1 = 0;
  for ( i = QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, Client_eQTaskType);
        i;
        i = QTask_GetNextSiblingOfType(i, v0) )
  {
    ptParent = i[1].ptParent;
    if ( ptParent != (struct QTask_s *)-1 )
    {
      ++v1;
      v4 = 0;
      while ( 1 )
      {
        if ( igi2_frame.v11[v4] == -1 )
          igi2_frame.v11[v4] = ptParent;
        if ( (struct QTask_s *)igi2_frame.v11[v4] == ptParent )
          break;
        if ( ++v4 >= 32 )
        {
          NetManager_LogMessage("NetManager_CountKickVotes: Bug: Failed to register vote. Exiting votecount.\n");
          return;
        }
      }
      ++igi2_frame.v12[v4];
    }
  }
  if ( v1 >= 1 )
  {
    v5 = NETMANAGER_HOSTSET_GIVEN_DESTINATION;
    v6 = -1;
    for ( j = 0; j < 32; j += 8 )
    {
      if ( igi2_frame.v11[j] == -1 )
        break;
      if ( igi2_frame.v12[j] > v5 )
      {
        v5 = igi2_frame.v12[j];
        v6 = igi2_frame.v11[j];
      }
      if ( igi2_frame.v11[j + 1] == -1 )
        break;
      if ( igi2_frame.v12[j + 1] > v5 )
      {
        v5 = igi2_frame.v12[j + 1];
        v6 = igi2_frame.v11[j + 1];
      }
      if ( igi2_frame.v11[j + 2] == -1 )
        break;
      if ( igi2_frame.v12[j + 2] > v5 )
      {
        v5 = igi2_frame.v12[j + 2];
        v6 = igi2_frame.v11[j + 2];
      }
      if ( igi2_frame.v11[j + 3] == -1 )
        break;
      if ( igi2_frame.v12[j + 3] > v5 )
      {
        v5 = igi2_frame.v12[j + 3];
        v6 = igi2_frame.v11[j + 3];
      }
      if ( igi2_frame.v11[j + 4] == -1 )
        break;
      if ( igi2_frame.v12[j + 4] > v5 )
      {
        v5 = igi2_frame.v12[j + 4];
        v6 = igi2_frame.v11[j + 4];
      }
      if ( igi2_frame.v11[j + 5] == -1 )
        break;
      if ( igi2_frame.v12[j + 5] > v5 )
      {
        v5 = igi2_frame.v12[j + 5];
        v6 = igi2_frame.v11[j + 5];
      }
      if ( igi2_frame.v11[j + 6] == -1 )
        break;
      if ( igi2_frame.v12[j + 6] > v5 )
      {
        v5 = igi2_frame.v12[j + 6];
        v6 = igi2_frame.v11[j + 6];
      }
      if ( igi2_frame.v11[j + 7] == -1 )
        break;
      if ( igi2_frame.v12[j + 7] > v5 )
      {
        v5 = igi2_frame.v12[j + 7];
        v6 = igi2_frame.v11[j + 7];
      }
    }
    if ( v5 == NETMANAGER_HOSTSET_GIVEN_DESTINATION || v6 == -1 )
    {
      NetManager_LogMessage("NetManager_CountKickVotes: Bug: Failed to count votes. Exiting votecount.\n");
    }
    else
    {
      v8 = Flow_ptFlow;
      v9 = (__int64)((double)SBYTE1(Flow_ptFlow->ptNetManagerQTask[3].ptPrev) * 0.4000000059604645 + 0.5);
      if ( v9 < 2 )
        v9 = 2;
      if ( v5 >= v9 )
      {
        v10 = nullptr;
        while ( 1 )
        {
          v10 = v10 ? QTask_GetNextSiblingOfType(v10, v0) : QTask_GetFirstChildOfType(v8->ptNetManagerQTask, v0);
          if ( !v10 )
            break;
          if ( v10[1].ptParent == (struct QTask_s *)v6 )
            v10[1].ptParent = (struct QTask_s *)-1;
        }
        _snprintf(igi2_frame.Buffer, 0xFFu, "SERVER KICKING PLAYER [%d] AFTER COUNTING VOTES\n", v6);
        NetManager_LogMessage(igi2_frame.Buffer);
        _snprintf(igi2_frame.eSet, 0x28u, "NetManager_KickPlayer(%d)", v6);
        NetworkCommand_RemoteEval(nullptr, (int)igi2_frame.eSet, NETMANAGER_HOSTSET_GIVEN_DESTINATION);
      }
    }
  }
}

// source: j/0/network/netmanager.c:11173  [anchor-callee]
int __cdecl NetManager_GetVoteCount(int eNetworkID)
{
  unsigned __int16 v1; // dx
  struct Flow_t *v2; // esi
  struct QTask_s *v3; // eax
  int v4; // edi

  v1 = Client_eQTaskType;
  v2 = Flow_ptFlow;
  v3 = nullptr;
  v4 = 0;
  while ( 1 )
  {
    v3 = v3 ? QTask_GetNextSiblingOfType(v3, v1) : QTask_GetFirstChildOfType(v2->ptNetManagerQTask, v1);
    if ( !v3 )
      break;
    if ( v3[1].ptParent == (struct QTask_s *)eNetworkID )
      ++v4;
  }
  return v4;
}

// source: j/0/network/netmanager.c:11203  [anchor-strings]
void __cdecl NetManager_CountMapVotes()
{
  #pragma pack(push, 1)
  union
  {
    struct { _DWORD v10[32]; };
    struct { char igi2_o1[128]; enum NetManagerHostSet_e v11[32]; };
    struct { char igi2_o2[256]; char eSet[40]; };
    struct { char igi2_o3[296]; char Buffer[256]; };
    char igi2_extent[552];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  unsigned __int16 v0; // dx
  int v1; // ebx
  struct QTask_s *i; // eax
  int v3; // esi
  int v4; // ecx
  int v5; // edi
  enum NetManagerHostSet_e v6; // eax
  int j; // ecx
  struct Node_s *ptHead; // edx
  struct Node_s *ptNext; // ecx

  v0 = Client_eQTaskType;
  memset(igi2_frame.v10, 0xFFu, sizeof(igi2_frame.v10));
  memset(igi2_frame.v11, 0, sizeof(igi2_frame.v11));
  v1 = 0;
  for ( i = QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, Client_eQTaskType);
        i;
        i = QTask_GetNextSiblingOfType(i, v0) )
  {
    v3 = *(_DWORD *)&i[1].eQTaskType;
    if ( v3 != -1 )
    {
      ++v1;
      v4 = 0;
      while ( 1 )
      {
        if ( igi2_frame.v10[v4] == -1 )
          igi2_frame.v10[v4] = v3;
        if ( igi2_frame.v10[v4] == v3 )
          break;
        if ( ++v4 >= 32 )
        {
          NetManager_LogMessage("NetManager_CountMapVotesCB: Bug: Failed to register vote. Exiting votecount.\n");
          return;
        }
      }
      ++igi2_frame.v11[v4];
    }
  }
  if ( v1 >= 1 )
  {
    v5 = -1;
    v6 = NETMANAGER_HOSTSET_GIVEN_DESTINATION;
    for ( j = 0; j < 32; j += 8 )
    {
      if ( igi2_frame.v10[j] == -1 )
        break;
      if ( igi2_frame.v11[j] > v6 )
      {
        v6 = igi2_frame.v11[j];
        v5 = igi2_frame.v10[j];
      }
      if ( igi2_frame.v10[j + 1] == -1 )
        break;
      if ( igi2_frame.v11[j + 1] > v6 )
      {
        v6 = igi2_frame.v11[j + 1];
        v5 = igi2_frame.v10[j + 1];
      }
      if ( igi2_frame.v10[j + 2] == -1 )
        break;
      if ( igi2_frame.v11[j + 2] > v6 )
      {
        v6 = igi2_frame.v11[j + 2];
        v5 = igi2_frame.v10[j + 2];
      }
      if ( igi2_frame.v10[j + 3] == -1 )
        break;
      if ( igi2_frame.v11[j + 3] > v6 )
      {
        v6 = igi2_frame.v11[j + 3];
        v5 = igi2_frame.v10[j + 3];
      }
      if ( igi2_frame.v10[j + 4] == -1 )
        break;
      if ( igi2_frame.v11[j + 4] > v6 )
      {
        v6 = igi2_frame.v11[j + 4];
        v5 = igi2_frame.v10[j + 4];
      }
      if ( igi2_frame.v10[j + 5] == -1 )
        break;
      if ( igi2_frame.v11[j + 5] > v6 )
      {
        v6 = igi2_frame.v11[j + 5];
        v5 = igi2_frame.v10[j + 5];
      }
      if ( igi2_frame.v10[j + 6] == -1 )
        break;
      if ( igi2_frame.v11[j + 6] > v6 )
      {
        v6 = igi2_frame.v11[j + 6];
        v5 = igi2_frame.v10[j + 6];
      }
      if ( igi2_frame.v10[j + 7] == -1 )
        break;
      if ( igi2_frame.v11[j + 7] > v6 )
      {
        v6 = igi2_frame.v11[j + 7];
        v5 = igi2_frame.v10[j + 7];
      }
    }
    if ( v6 == NETMANAGER_HOSTSET_GIVEN_DESTINATION || v5 == -1 )
    {
      NetManager_LogMessage("NetManager_CountMapVotesCB: Bug: Failed to count votes. Exiting votecount.\n");
    }
    else
    {
      ptHead = Mission_tMissions.ptHead;
      ptNext = Mission_tMissions.ptHead->ptNext;
      if ( Mission_tMissions.ptHead->ptNext )
      {
        while ( ptHead[1].ptNext != (struct Node_s *)Game_iMissionID )
        {
          ptHead = ptNext;
          ptNext = ptNext->ptNext;
          if ( !ptNext )
            goto LABEL_44;
        }
      }
      else
      {
LABEL_44:
        ptHead = nullptr;
      }
      if ( ptHead[1].ptNext != (struct Node_s *)v5 && v6 >= NETMANAGER_HOSTSET_ALL_EXCEPT_GIVEN )
      {
        _snprintf(igi2_frame.Buffer, 0xFFu, "SERVER CHANGING MAP TO [%d] AFTER COUNTING VOTES\n", v5);
        NetManager_LogMessage(igi2_frame.Buffer);
        _snprintf(igi2_frame.eSet, 0x28u, "NetManager_GotoMap(%d)", v5);
        NetworkCommand_RemoteEval(nullptr, (int)igi2_frame.eSet, NETMANAGER_HOSTSET_GIVEN_DESTINATION);
      }
    }
  }
}

// source: j/0/network/netmanager.c:11349  [anchor-strings]
void __cdecl NetManager_VoteMap(int nMap)
{
  struct Node_s *ptHead; // ecx
  struct Node_s *ptNext; // eax
  struct Client_s *ClientFromNetworkID; // eax
  int eNetworkID; // [esp-4h] [ebp-8h]

  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle || NetworkCommand_eEvalNetworkID == -1 )
  {
    DebugConsole_printf("NetManager_VoteMap: Not on server or not using remote eval\n");
  }
  else
  {
    ptHead = Mission_tMissions.ptHead;
    ptNext = Mission_tMissions.ptHead->ptNext;
    if ( Mission_tMissions.ptHead->ptNext )
    {
      while ( ptHead[1].ptNext != (struct Node_s *)nMap )
      {
        ptHead = ptNext;
        ptNext = ptNext->ptNext;
        if ( !ptNext )
          return;
      }
      ClientFromNetworkID = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID);
      eNetworkID = ClientFromNetworkID->eNetworkID;
      ClientFromNetworkID->nVotedMap = nMap;
      DebugConsole_printf("NetManager_VoteMap: Placed vote for map [%d] for client %d\n", nMap, eNetworkID);
    }
  }
}

// source: j/0/network/netmanager.c:11379  [anchor-strings]
struct Result_s *__cdecl NetManager_VoteMapCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  int v3; // esi
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  if ( ptArgList && ptArgList->nArguments == 1 )
  {
    v3 = Script_EvalArgInt(ptArgList, 0);
    DebugConsole_printf("NetManager_VoteMapCB(%d)\n", v3);
    NetManager_VoteMap(v3);
  }
  else
  {
    DebugConsole_printf("NetManager_VoteMap: Invalid parameters\n");
  }
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/netmanager.c:11403  [anchor-strings]
struct Result_s *__cdecl NetManager_VoteNextCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct Mission_s *NextMap; // esi
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  NextMap = NetManager_GetNextMap();
  DebugConsole_printf("Placing vote for map=%d\n", NextMap->iID);
  NetManager_VoteMap(NextMap->iID);
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/netmanager.c:11427  [anchor-strings]
struct Result_s *__cdecl NetManager_ShowVotesCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v13; };
    struct { char igi2_o1[4]; struct QTask_s *ptParent; };
    struct { char igi2_o2[24]; char zTemp[40]; };
    char igi2_extent[64];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptNetManagerQTask; // edi
  unsigned __int16 v4; // dx
  struct QTask_s *v5; // eax
  int i; // esi
  struct NetManagerGameMessageList *v7; // edi
  struct NetManagerGameMessageList *v8; // esi
  struct QTask_s *v9; // ebx
  struct QTask_s *v10; // eax
  int v11; // esi

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  if ( ptNetManagerQTask[6].tQTaskChildren.ptMiddle || NetworkCommand_eEvalNetworkID == -1 )
  {
    strncpy(igi2_frame.zTemp, "Not on server or not remote eval", 0x28u);
  }
  else
  {
    v4 = Client_eQTaskType;
    v5 = nullptr;
    for ( i = 0; ; ++i )
    {
      v5 = v5 ? QTask_GetNextSiblingOfType(v5, v4) : QTask_GetFirstChildOfType(ptNetManagerQTask, v4);
      if ( !v5 )
        break;
    }
    if ( i >= 1 )
    {
      strncpy(igi2_frame.zTemp, "Showing votes", 0x28u);
      v7 = (struct NetManagerGameMessageList *)Mem_AllocFn(16 * (3 * i + 3), 4);
      v7->nNumberOfLines = i;
      v7->nCommandID = 2;
      v8 = v7 + 1;
      v9 = nullptr;
      while ( 1 )
      {
        v10 = v9
            ? QTask_GetNextSiblingOfType(v9, Client_eQTaskType)
            : QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, Client_eQTaskType);
        v9 = v10;
        if ( !v10 )
          break;
        igi2_frame.ptParent = v10[1].ptParent;
        igi2_frame.v13 = *(_DWORD *)&v10[1].eQTaskType;
        v8->tBaseMessage.eGameMessage = (unsigned int)v10[1].ptNext;
        _snprintf((char *const)&v8->eClientNetworkID, 0x28u, "[%s][%d][%d]", (char *)&v10[2], igi2_frame.v13, igi2_frame.ptParent);
        ++v8;
      }
      NetManager_SendListCommand(v7, NetworkCommand_eEvalNetworkID);
      v11 = *(_DWORD *)((unsigned int)&v7[-1].nNumberOfLines & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v11);
      memset(*(void **)(v11 + 8), 0xCDu, *(_DWORD *)(v11 + 16));
      free((void *)v11);
    }
    else
    {
      strncpy(igi2_frame.zTemp, "No players found", 0x28u);
    }
  }
  NetworkCommand_SetEvalResponse(igi2_frame.zTemp);
  *(_DWORD *)igi2_frame.zTemp = 0;
  *(_DWORD *)&igi2_frame.zTemp[8] = 0;
  *(_DWORD *)&igi2_frame.zTemp[12] = 0;
  *(_DWORD *)&igi2_frame.zTemp[16] = &g_zInitialValue;
  qmemcpy(retstr, igi2_frame.zTemp, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/netmanager.c:11506  [anchor-strings]
struct Result_s *__cdecl NetManager_FingerCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v25; };
    struct { char igi2_o1[4]; DWORD v26; };
    struct { char igi2_o2[8]; char *Buffer; };
    struct { char igi2_o3[16]; int nBandwidth; };
    struct { char igi2_o4[20]; int gIn; };
    struct { char igi2_o5[24]; int dReceive; };
    struct { char igi2_o6[28]; int nTimeOnline; };
    struct { char igi2_o7[32]; int nPing; };
    struct { char igi2_o8[36]; struct NetManagerGameMessageList *ptGameMessage; };
    struct { char igi2_o9[40]; struct Client_s *ptCurrentClient; };
    struct { char igi2_o10[44]; char zIP[24]; };
    struct { char igi2_o11[68]; char zTemp[40]; };
    char igi2_extent[108];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptNetManagerQTask; // edi
  unsigned __int16 v4; // dx
  struct QTask_s *v5; // eax
  int i; // esi
  struct NetManagerGameMessageList *v7; // edi
  int v8; // ecx
  struct NetManagerGameMessageList *v9; // esi
  struct QTask_s *p_tQTask; // eax
  struct QTask_s *v11; // eax
  struct QTask_s *v12; // ebp
  int ptNext; // edi
  DWORD PerformanceCounter; // eax
  int v15; // edx
  struct Node_s *ptHead; // ecx
  struct Node_s *v17; // eax
  int v18; // edx
  int v19; // ebx
  DWORD TickCount; // eax
  char v21; // bl
  struct NetManagerGameMessageList *v22; // esi
  int v23; // esi

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  if ( ptNetManagerQTask[6].tQTaskChildren.ptMiddle || NetworkCommand_eEvalNetworkID == -1 )
  {
    strncpy(igi2_frame.zTemp, "Not on server or not remote eval", 0x28u);
  }
  else
  {
    v4 = Client_eQTaskType;
    v5 = nullptr;
    for ( i = 0; ; ++i )
    {
      v5 = v5 ? QTask_GetNextSiblingOfType(v5, v4) : QTask_GetFirstChildOfType(ptNetManagerQTask, v4);
      if ( !v5 )
        break;
    }
    if ( i >= 1 )
    {
      strncpy(igi2_frame.zTemp, "Player status", 0x28u);
      v7 = (struct NetManagerGameMessageList *)Mem_AllocFn(96 * i + 48, 4);
      v8 = 2 * i;
      v9 = v7 + 1;
      igi2_frame.ptGameMessage = v7;
      v7->nNumberOfLines = v8;
      v7->nCommandID = 2;
      p_tQTask = nullptr;
      for ( igi2_frame.Buffer = (char *)&v7[1].eClientNetworkID; ; igi2_frame.Buffer += 96 )
      {
        v11 = p_tQTask
            ? QTask_GetNextSiblingOfType(p_tQTask, Client_eQTaskType)
            : QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, Client_eQTaskType);
        v12 = v11;
        igi2_frame.ptCurrentClient = (struct Client_s *)v11;
        if ( !v11 )
          break;
        ptNext = (int)v11[1].ptNext;
        igi2_frame.nPing = (int)v11[6].tQTaskRefList.ptMiddle;
        if ( Timer_isPerformanceCounter )
          PerformanceCounter = Timer_GetPerformanceCounter();
        else
          PerformanceCounter = GetTickCount();
        v15 = (int)(PerformanceCounter - Timer_nStartTime - (unsigned int)v12[1].tQTaskChildren.ptTail) / 60000;
        ptHead = Network_atQueues[0].tList.ptHead;
        v17 = Network_atQueues[0].tList.ptHead->ptNext;
        igi2_frame.nTimeOnline = v15;
        v18 = 0;
        igi2_frame.v25 = 0;
        if ( Network_atQueues[0].tList.ptHead->ptNext )
        {
          do
          {
            if ( ptHead[1].ptNext == (struct Node_s *)v12[1].ptNext )
              ++v18;
            ptHead = v17;
            v17 = v17->ptNext;
          }
          while ( v17 );
          igi2_frame.v25 = v18;
        }
        v19 = (int)v12[1].ptNext;
        igi2_frame.gIn = Network_NumberOfWaitingFromHost(v19);
        igi2_frame.dReceive = NetManager_GetLastReceivedTimeFromNetworkID(v19);
        if ( Timer_isPerformanceCounter )
          TickCount = Timer_GetPerformanceCounter();
        else
          TickCount = GetTickCount();
        igi2_frame.nBandwidth = *(_DWORD *)&v12[7].eQTaskType;
        igi2_frame.v26 = TickCount - Timer_nStartTime;
        v21 = v12[1].tQTaskChildren.ptHead == nullptr ? 32 : 42;
        Network_GetHostnameByNetworkID(igi2_frame.zIP, 22, ptNext);
        v9->tBaseMessage.eGameMessage = ptNext;
        _snprintf(
          igi2_frame.Buffer,
          0x28u,
          "%c%s-drec%d-gout%d-gin%d-b%d",
          v21,
          (char *)&v12[2],
          igi2_frame.v26 - igi2_frame.dReceive,
          igi2_frame.v25,
          igi2_frame.gIn,
          igi2_frame.nBandwidth);
        HIBYTE(v9->nNumberOfLines) = 0;
        v22 = v9 + 1;
        v22->tBaseMessage.eGameMessage = ptNext;
        _snprintf(igi2_frame.Buffer + 48, 0x28u, "  %s-%03d-%dm", igi2_frame.zIP, igi2_frame.nPing, igi2_frame.nTimeOnline);
        v7 = igi2_frame.ptGameMessage;
        p_tQTask = &igi2_frame.ptCurrentClient->tQTask;
        HIBYTE(v22->nNumberOfLines) = 0;
        v9 = v22 + 1;
      }
      NetManager_SendListCommand(v7, NetworkCommand_eEvalNetworkID);
      v23 = *(_DWORD *)((unsigned int)&v7[-1].nNumberOfLines & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v23);
      memset(*(void **)(v23 + 8), 0xCDu, *(_DWORD *)(v23 + 16));
      free((void *)v23);
    }
    else
    {
      strncpy(igi2_frame.zTemp, "No players found", 0x28u);
    }
  }
  NetworkCommand_SetEvalResponse(igi2_frame.zTemp);
  *(_DWORD *)igi2_frame.zIP = 0;
  *(_DWORD *)&igi2_frame.zIP[8] = 0;
  *(_DWORD *)&igi2_frame.zIP[12] = 0;
  *(_DWORD *)&igi2_frame.zIP[16] = &g_zInitialValue;
  qmemcpy(retstr, igi2_frame.zIP, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/netmanager.c:11630  [anchor-strings]
struct Result_s *__cdecl NetManager_RConCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct Client_s *ClientFromNetworkID; // eax
  struct Client_s *v4; // esi
  char zTemp[40]; // [esp+8h] [ebp-28h] BYREF

  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle || NetworkCommand_eEvalNetworkID == -1 )
  {
    strncpy(zTemp, "Not on server or not remote eval", 0x28u);
  }
  else if ( ptArgList && ptArgList->nArguments == 1 )
  {
    Script_EvalArgString(ptArgList, 0, zTemp, 40);
    if ( !strncmp(zTemp, ServerConfig_tServerConfig.zRConPassword, 8u) )
    {
      ClientFromNetworkID = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID);
      v4 = ClientFromNetworkID;
      if ( ClientFromNetworkID )
      {
        if ( ClientFromNetworkID->isSuperUser )
        {
          NetworkCommand_SetEvalResponse("Already rcon authenticated");
        }
        else
        {
          NetworkCommand_SetEvalResponse("rcon OK");
          v4->isSuperUser = true;
        }
      }
      else
      {
        NetworkCommand_SetEvalResponse("Player not found");
      }
    }
    else
    {
      NetworkCommand_SetEvalResponse("Wrong password");
    }
  }
  else
  {
    NetworkCommand_SetEvalResponse("No password supplied");
  }
  *(_DWORD *)zTemp = 1;
  *(_DWORD *)&zTemp[8] = 0;
  *(_DWORD *)&zTemp[12] = 1072693248;
  *(_DWORD *)&zTemp[16] = &g_zInitialValue;
  qmemcpy(retstr, zTemp, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/netmanager.c:11696  [anchor-strings]
struct Result_s *__cdecl NetManager_ListMapsCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct NetManagerGameMessageList *ptGameMessage; };
    struct { char igi2_o1[4]; char zTemp[40]; };
    char igi2_extent[44];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v3; // esi
  char *v4; // eax
  struct NetManagerGameMessageList *v5; // ebx
  struct Node_s *ptHead; // ecx
  struct Node_s *ptNext; // esi
  struct Node_s **v8; // ebp
  char *v9; // edi
  struct Node_s *v10; // edx
  struct Node_s *v11; // eax
  int v12; // esi
  char v13; // cl
  char v14; // cl

  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle || NetworkCommand_eEvalNetworkID == -1 )
  {
    strncpy(igi2_frame.zTemp, "Not on server or not remote eval", 0x28u);
  }
  else
  {
    v3 = List_Length(&NetManager_tMapList);
    strncpy(igi2_frame.zTemp, "NetManager_ListMapsCB called", 0x28u);
    v4 = (char *)Mem_AllocFn(16 * (3 * v3 + 3), 4);
    v5 = (struct NetManagerGameMessageList *)v4;
    *((_DWORD *)v4 + 11) = v3;
    *((_DWORD *)v4 + 3) = 2;
    ptHead = NetManager_tMapList.ptHead;
    ptNext = NetManager_tMapList.ptHead->ptNext;
    igi2_frame.ptGameMessage = (struct NetManagerGameMessageList *)v4;
    v8 = (struct Node_s **)(v4 + 48);
    if ( NetManager_tMapList.ptHead->ptNext )
    {
      v9 = v4 + 56;
      do
      {
        *v8 = ptHead[1].ptNext;
        v10 = NetManager_tActiveMapList.ptHead;
        v11 = NetManager_tActiveMapList.ptHead->ptNext;
        if ( NetManager_tActiveMapList.ptHead->ptNext )
        {
          while ( v10[1].ptNext != ptHead[1].ptNext )
          {
            v10 = v11;
            v11 = v11->ptNext;
            if ( !v11 )
            {
              v5 = igi2_frame.ptGameMessage;
              goto LABEL_9;
            }
          }
          _snprintf(v9, 0x28u, "%20s [ACTIVE]", (char *)&ptHead[1].ptPrev[2]);
          v5 = igi2_frame.ptGameMessage;
        }
        else
        {
LABEL_9:
          _snprintf(v9, 0x28u, "%20s", (char *)&ptHead[1].ptPrev[2]);
        }
        ptHead = ptNext;
        ptNext = ptNext->ptNext;
        v8 += 12;
        v9 += 48;
      }
      while ( ptNext );
    }
    NetManager_SendListCommand(v5, NetworkCommand_eEvalNetworkID);
    v12 = *(_DWORD *)((unsigned int)&v5[-1].nNumberOfLines & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v12);
    memset(*(void **)(v12 + 8), 0xCDu, *(_DWORD *)(v12 + 16));
    free((void *)v12);
  }
  if ( &igi2_frame.zTemp[strlen(igi2_frame.zTemp) + 1] == &igi2_frame.zTemp[1] )
  {
    NetworkCommand_zEvalResponse[0] = v13;
  }
  else
  {
    if ( (unsigned int)(&igi2_frame.zTemp[strlen(igi2_frame.zTemp) + 1] - &igi2_frame.zTemp[1]) >= 0x28 )
    {
      memset(&igi2_frame.zTemp[36], 46, 3);
      igi2_frame.zTemp[39] = v14;
    }
    strncpy(NetworkCommand_zEvalResponse, igi2_frame.zTemp, 0x28u);
  }
  *(_DWORD *)igi2_frame.zTemp = 0;
  *(_DWORD *)&igi2_frame.zTemp[8] = 0;
  *(_DWORD *)&igi2_frame.zTemp[12] = 0;
  *(_DWORD *)&igi2_frame.zTemp[16] = &g_zInitialValue;
  qmemcpy(retstr, igi2_frame.zTemp, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/netmanager.c:11776  [anchor-strings]
struct Result_s *__cdecl NetManager_MonitorCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  int v3; // edi
  char *v4; // edx
  __int32 isSuperUser; // eax
  struct Client_s *ClientFromNetworkID; // eax
  enum bool isMonitoring; // edx
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = NetworkCommand_eEvalNetworkID;
  if ( NetworkCommand_eEvalNetworkID == -1 )
  {
    v4 = "Must be called with rcon.\n";
    goto LABEL_16;
  }
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    isSuperUser = NetworkCommand_eEvalNetworkID == 0;
  }
  else
  {
    if ( !NetworkCommand_eEvalNetworkID )
      goto LABEL_10;
    isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  }
  if ( !isSuperUser )
  {
    v4 = "Not authorized.\n";
    goto LABEL_16;
  }
  if ( !v3 )
  {
LABEL_10:
    v4 = "Not effective when called from server\n";
    goto LABEL_16;
  }
  ClientFromNetworkID = NetManager_GetClientFromNetworkID(v3);
  if ( ClientFromNetworkID )
  {
    isMonitoring = ClientFromNetworkID->isMonitoring;
    ClientFromNetworkID->isMonitoring = isMonitoring == false;
    if ( isMonitoring )
      v4 = "Monitoring OFF\n";
    else
      v4 = "Monitoring ON\n";
  }
  else
  {
    v4 = "Player not found\n";
  }
LABEL_16:
  NetworkCommand_SetEvalResponse(v4);
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/netmanager.c:11819  [size]
int __cdecl NetManager_GetPacketLoss()
{
  return ServerConfig_tServerConfig.isLocalWeapon;
}

// source: j/0/network/netmanager.c:11833  [anchor-caller]
struct Result_s *__cdecl NetManager_ChallengeCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct Client_s *v7; };
    struct { char igi2_o1[12]; struct Result_s Rs; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v3; // eax
  struct Client_s *ClientFromNetworkID; // eax
  struct Server_s *FirstChildOfType; // eax

  if ( !Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    if ( ptArgList )
    {
      if ( ptArgList->nArguments == 1 )
      {
        v3 = Script_EvalArgInt(ptArgList, 0);
        ClientFromNetworkID = NetManager_GetClientFromNetworkID(v3);
        if ( ClientFromNetworkID )
        {
          igi2_frame.v7 = ClientFromNetworkID;
          FirstChildOfType = (struct Server_s *)QTask_GetFirstChildOfType(
                                                  Flow_ptFlow->ptNetManagerQTask,
                                                  Server_eQTaskType);
          Server_SendChallengeTo(FirstChildOfType, igi2_frame.v7);
        }
      }
    }
  }
  igi2_frame.Rs.nResult = 0;
  igi2_frame.Rs.vResult = 0.0;
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/netmanager.c:11866  [anchor-strings]
struct Result_s *__cdecl NetManager_KickPlayerCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { char *v14; };
    struct { char igi2_o1[4]; int v15; };
    struct { char igi2_o2[24]; char zResponse[40]; };
    char igi2_extent[64];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v3; // esi
  int v4; // eax
  int v5; // ebx
  int v6; // ebp
  struct Client_s *ClientFromNetworkID; // esi
  struct Client_s *v8; // eax
  struct Client_s *v9; // edi
  char *zPlayerName; // ecx
  int eNetworkID; // esi
  int v12; // eax

  memset(&igi2_frame.zResponse[18], 0, 22);
  strcpy(igi2_frame.zResponse, "KICK: NO RESPONSE");
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle
    || (v3 = NetworkCommand_eEvalNetworkID, NetworkCommand_eEvalNetworkID == -1) )
  {
    DebugConsole_printf("NetManager_KickPlayer: Not on server or not using remote eval\n");
    goto LABEL_21;
  }
  if ( NetworkCommand_isRemoteEvalSuper() == false )
  {
    _snprintf(igi2_frame.zResponse, 0x28u, "kick: Not allowed to kick. id=%d\n", v3);
    NetworkCommand_SetEvalResponse(igi2_frame.zResponse);
LABEL_21:
    *(_DWORD *)igi2_frame.zResponse = 0;
    goto LABEL_22;
  }
  if ( !ptArgList || ptArgList->nArguments != 1 )
  {
    igi2_frame.v15 = 0;
    igi2_frame.v14 = "kick: Inv. params recv. host[%d]\n";
    goto LABEL_18;
  }
  v4 = Script_EvalArgInt(ptArgList, 0);
  v5 = NetworkCommand_eEvalNetworkID;
  v6 = v4;
  ClientFromNetworkID = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID);
  v8 = NetManager_GetClientFromNetworkID(v6);
  v9 = v8;
  if ( ClientFromNetworkID )
  {
    zPlayerName = ClientFromNetworkID->zPlayerName;
    eNetworkID = ClientFromNetworkID->eNetworkID;
LABEL_11:
    if ( !v8 )
    {
      _snprintf(igi2_frame.zResponse, 0x28u, "kick: No such player, id=%d\n", v6);
LABEL_19:
      NetworkCommand_SetEvalResponse(igi2_frame.zResponse);
      *(_DWORD *)igi2_frame.zResponse = 0;
      goto LABEL_22;
    }
    v12 = v8->eNetworkID;
    if ( v12 )
    {
      _snprintf(igi2_frame.zResponse, 0x28u, "[%d][%s] KICKS [%d][%s]\n", eNetworkID, zPlayerName, v12, v9->zPlayerName);
      Server_DestroyPlayer(v9, NETMANAGER_DESTROYPLAYER_REASON_KICKED);
      goto LABEL_19;
    }
    igi2_frame.v15 = v6;
    igi2_frame.v14 = "kick: Cannot kick server player,id=%d\n";
LABEL_18:
    _snprintf(igi2_frame.zResponse, 0x28u, igi2_frame.v14, igi2_frame.v15);
    goto LABEL_19;
  }
  if ( !v5 )
  {
    zPlayerName = "SERVER";
    eNetworkID = 0;
    goto LABEL_11;
  }
  NetManager_LogMessage("Kick message received from unknown host. Skipping\n");
  *(_DWORD *)igi2_frame.zResponse = 0;
LABEL_22:
  *(_DWORD *)&igi2_frame.zResponse[16] = &g_zInitialValue;
  *(_DWORD *)&igi2_frame.zResponse[12] = 0;
  *(_DWORD *)&igi2_frame.zResponse[8] = 0;
  qmemcpy(retstr, igi2_frame.zResponse, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/netmanager.c:11958  [anchor-strings]
struct Result_s *__cdecl NetManager_VoteKickCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  int v3; // ebx
  struct Client_s *ClientFromNetworkID; // esi
  struct Client_s *v5; // eax
  int eNetworkID; // ebx
  int VoteCount; // esi
  int KickMin; // eax
  struct Result_s Rs; // [esp+Ch] [ebp-28h] BYREF

  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle || NetworkCommand_eEvalNetworkID == -1 )
  {
    DebugConsole_printf("NetManager_VoteKick: Not on server or not using remote eval\n");
  }
  else if ( ptArgList && ptArgList->nArguments == 1 )
  {
    v3 = Script_EvalArgInt(ptArgList, 0);
    ClientFromNetworkID = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID);
    v5 = NetManager_GetClientFromNetworkID(v3);
    if ( ClientFromNetworkID )
    {
      if ( v5 )
      {
        ClientFromNetworkID->eVotedKickID = v5->eNetworkID;
        eNetworkID = v5->eNetworkID;
        VoteCount = NetManager_GetVoteCount(eNetworkID);
        KickMin = NetManager_GetKickMin();
        if ( VoteCount >= KickMin )
          _snprintf((char *const)&Rs, 0x28u, "[%d] about to be kicked", eNetworkID);
        else
          _snprintf(
            (char *const)&Rs,
            0x28u,
            "%d vote(s) on [%d]: %d more needed",
            VoteCount,
            eNetworkID,
            KickMin - VoteCount);
        NetworkCommand_SetEvalResponse((char *)&Rs);
      }
      else
      {
        _snprintf((char *const)&Rs, 0x28u, "Vote: No such player:[%d]", v3);
        NetworkCommand_SetEvalResponse((char *)&Rs);
      }
    }
    else
    {
      NetManager_LogMessage("Vote messsage received by unknown player\n");
    }
  }
  else
  {
    _snprintf((char *const)&Rs, 0x28u, "To vote: 'sv votekick [ID]'");
    NetworkCommand_SetEvalResponse((char *)&Rs);
  }
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/netmanager.c:12052  [anchor-callee]
void __cdecl NetManager_KillClient(int eNetworkID)
{
  struct QTask_s *ptNetManagerQTask; // esi
  DWORD PerformanceCounter; // eax
  int v3; // ecx
  struct QTask_s *v4; // eax
  int ptMiddle; // ecx
  struct ServerGameMessageKill_s tKillMessage; // [esp+8h] [ebp-20h] BYREF

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  tKillMessage.tBaseMessage.eGameMessage = 1263094860;
  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  v3 = PerformanceCounter
     - Timer_nStartTime
     + (char *)ptNetManagerQTask[6].tQTaskRefList.ptMiddle
     - (char *)ptNetManagerQTask[6].tQTaskRefList.ptTail;
  v4 = Flow_ptFlow->ptNetManagerQTask;
  tKillMessage.tBaseMessage.nLocalTime = v3;
  ptMiddle = (int)v4[6].tQTaskChildren.ptMiddle;
  tKillMessage.eDamageType = 0;
  tKillMessage.isSpawnKill = 0;
  tKillMessage.eKillerNetworkID = eNetworkID;
  tKillMessage.eVictimNetworkID = eNetworkID;
  tKillMessage.eDamagePart = 13;
  tKillMessage.eWeaponID = -1;
  NetManager_SendGameMessage(0, ptMiddle, NETWORKQUEUE_GUARANTEED, &tKillMessage.tBaseMessage, 0x20u);
}

// source: j/0/network/netmanager.c:12081  [anchor-strings]
struct Result_s *__cdecl NetManager_KillSelfCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  int v3; // edi
  char zTemp[40]; // [esp+8h] [ebp-28h] BYREF

  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle
    || (v3 = NetworkCommand_eEvalNetworkID, NetworkCommand_eEvalNetworkID == -1) )
  {
    DebugConsole_printf("NetManager_VoteMap: Not on server or not using remote eval\n");
  }
  else
  {
    strncpy(zTemp, "Executed", 0x28u);
    NetworkCommand_SetEvalResponse(zTemp);
    NetManager_KillClient(v3);
    DebugConsole_printf("Player with network id %d suicided\n", v3);
  }
  *(_DWORD *)zTemp = 0;
  *(_DWORD *)&zTemp[8] = 0;
  *(_DWORD *)&zTemp[12] = 0;
  *(_DWORD *)&zTemp[16] = &g_zInitialValue;
  qmemcpy(retstr, zTemp, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/netmanager.c:12111  [anchor-strings]
struct Result_s *__cdecl NetManager_BanPlayerCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  char *p_Rs; // edx
  int v4; // ebx
  struct Client_s *ClientFromNetworkID; // esi
  struct Client_s *v6; // eax
  struct Client_s *v7; // edi
  struct Result_s Rs; // [esp+8h] [ebp-28h] BYREF

  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle || NetworkCommand_eEvalNetworkID == -1 )
  {
    p_Rs = "Ban: Not on server or not using remote eval";
  }
  else if ( NetworkCommand_isRemoteEvalSuper() )
  {
    if ( ptArgList && ptArgList->nArguments == 1 )
    {
      v4 = Script_EvalArgInt(ptArgList, 0);
      ClientFromNetworkID = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID);
      v6 = NetManager_GetClientFromNetworkID(v4);
      v7 = v6;
      if ( ClientFromNetworkID )
      {
        if ( v6 )
        {
          if ( Network_BanPlayer(v6->eNetworkID) )
            _snprintf(
              (char *const)&Rs,
              0x28u,
              "Ban: [%d][%s] bans [%d][%s]",
              ClientFromNetworkID->eNetworkID,
              ClientFromNetworkID->zPlayerName,
              v7->eNetworkID,
              v7->zPlayerName);
          else
            _snprintf((char *const)&Rs, 0x28u, "Ban: Already banned or non-existing");
          p_Rs = (char *)&Rs;
        }
        else
        {
          p_Rs = "Ban: No such player";
        }
      }
      else
      {
        p_Rs = "Ban: Banner gone";
      }
    }
    else
    {
      p_Rs = "Ban:Invalid parameters";
    }
  }
  else
  {
    p_Rs = "Ban: Not allowed to ban";
  }
  NetworkCommand_SetEvalResponse(p_Rs);
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/netmanager.c:12179  [anchor-strings]
struct Result_s *__cdecl NetManager_UnbanPlayerCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct Result_s Rs; };
    struct { char igi2_o1[24]; char zTemp[256]; };
    char igi2_extent[280];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v3; // esi
  char *v4; // edx
  int v5; // esi

  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle
    || (v3 = NetworkCommand_eEvalNetworkID, NetworkCommand_eEvalNetworkID == -1) )
  {
    v4 = "unban: Not on server or not using remote eval";
  }
  else if ( NetworkCommand_isRemoteEvalSuper() )
  {
    if ( ptArgList && ptArgList->nArguments == 1 )
    {
      v5 = Script_EvalArgInt(ptArgList, 0);
      if ( NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID) )
      {
        if ( v5 < 0 )
        {
          v4 = "unban: Bad index given";
        }
        else if ( Network_UnbanPlayer(v5) )
        {
          v4 = "unban: Address unbanned";
        }
        else
        {
          v4 = "unban: No such address";
        }
      }
      else
      {
        v4 = "unban: Lost unbanning client. Dropped unban";
      }
    }
    else
    {
      v4 = "unban: Invalid parameters";
    }
  }
  else
  {
    _snprintf(igi2_frame.zTemp, 0xFFu, "unban: Not allowed to unban player. UserID=%d", v3);
    v4 = igi2_frame.zTemp;
  }
  NetworkCommand_SetEvalResponse(v4);
  igi2_frame.Rs.nResult = 0;
  igi2_frame.Rs.vResult = 0.0;
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/netmanager.c:12247  [anchor-strings]
struct Result_s *__cdecl NetManager_ListBanCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  int v3; // esi
  struct NetManagerGameMessageList *v4; // ebx
  unsigned __int8 *ptHead; // eax
  struct Node_s *ptNext; // esi
  unsigned int v7; // ebp
  struct NetManagerGameMessageList *i; // edi
  int v9; // esi
  char v10; // cl
  char v11; // cl
  char zTemp[40]; // [esp+Ch] [ebp-28h] BYREF

  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle || NetworkCommand_eEvalNetworkID == -1 )
  {
    strncpy(zTemp, "NetManager_ListBanCB(): Not on server or not remote eval", 0x28u);
  }
  else
  {
    v3 = List_Length(&Network_tBannedList);
    _snprintf(zTemp, 0x28u, "%d address(es) banned", v3);
    v4 = (struct NetManagerGameMessageList *)Mem_AllocFn(16 * (3 * v3 + 3), 4);
    v4->nNumberOfLines = v3;
    v4->nCommandID = 2;
    ptHead = (unsigned __int8 *)Network_tBannedList.ptHead;
    ptNext = Network_tBannedList.ptHead->ptNext;
    v7 = 0;
    for ( i = v4 + 1; ptNext; ++v7 )
    {
      i->tBaseMessage.eGameMessage = v7;
      _snprintf((char *const)&i->eClientNetworkID, 0x28u, "%u.%u.%u.%u", ptHead[8], ptHead[9], ptHead[10], ptHead[11]);
      ++i;
      ptHead = (unsigned __int8 *)ptNext;
      ptNext = ptNext->ptNext;
    }
    NetManager_SendListCommand(v4, NetworkCommand_eEvalNetworkID);
    v9 = *(_DWORD *)((unsigned int)&v4[-1].nNumberOfLines & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v9);
    memset(*(void **)(v9 + 8), 0xCDu, *(_DWORD *)(v9 + 16));
    free((void *)v9);
  }
  if ( &zTemp[strlen(zTemp) + 1] == &zTemp[1] )
  {
    NetworkCommand_zEvalResponse[0] = v10;
  }
  else
  {
    if ( (unsigned int)(&zTemp[strlen(zTemp) + 1] - &zTemp[1]) >= 0x28 )
    {
      memset(&zTemp[36], 46, 3);
      zTemp[39] = v11;
    }
    strncpy(NetworkCommand_zEvalResponse, zTemp, 0x28u);
  }
  *(_DWORD *)zTemp = 0;
  *(_DWORD *)&zTemp[8] = 0;
  *(_DWORD *)&zTemp[12] = 0;
  *(_DWORD *)&zTemp[16] = &g_zInitialValue;
  qmemcpy(retstr, zTemp, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/netmanager.c:12326  [size]
struct Result_s *__cdecl NetManager_SetActiveSessionCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->isQVM )
  {
    ptArgList = nullptr;
    QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
    v4 = ptArgList;
  }
  else
  {
    v4 = (struct ArgList_s *)Expression_EvalInt(*ptArgList->aptExpression);
  }
  NetManager_nSelectedSession = (int)v4;
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/netmanager.c:12344  [size]
struct Result_s *__cdecl NetManager_GetActiveSessionCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  Rs.nResult = NetManager_nSelectedSession;
  Rs.vResult = (double)NetManager_nSelectedSession;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/netmanager.c:12358  [anchor-caller]
void __cdecl NetManager_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  __int16 v1; // ax
  unsigned __int16 v2; // si
  struct Mission_s *ptHead; // eax
  struct Node_s *i; // esi

  BaseQTaskType = QTask_GetBaseQTaskType();
  NetManager_eQTaskType = QTask_NewQTaskType("NetManager", 1452, BaseQTaskType, 0, 0);
  NetManager_eGameMessageCreatePlayerQTaskEvent = QTask_NewQTaskEventFn(0, "NetManager-GMCreatePlayer");
  NetManager_eGameMessageDestroyPlayerQTaskEvent = QTask_NewQTaskEventFn(0, "NetManager-GMDestroyPlayer");
  NetManager_eGameMessageInitGameSettingsQTaskEvent = QTask_NewQTaskEventFn(0, "NetManager-GMInitGameSettings");
  NetManager_eGameMessageUpdateQTaskEvent = QTask_NewQTaskEventFn(0, "NetManager-GMUpdate");
  NetManager_eGameMessageZUpdateQTaskEvent = QTask_NewQTaskEventFn(0, "NetManager_GMZUpdate");
  NetManager_eGameMessageDamageQTaskEvent = QTask_NewQTaskEventFn(0, "NetManager-GMDamage");
  NetManager_eGameMessageKillQTaskEvent = QTask_NewQTaskEventFn(0, "NetManager-GMKill");
  NetManager_eGameMessageSpawnQTaskEvent = QTask_NewQTaskEventFn(0, "NetManager-GMSpawn");
  NetManager_eGameMessageRequestSpawnQTaskEvent = QTask_NewQTaskEventFn(0, "NetManager-GMRequestSpawn");
  NetManager_eGameMessageSpectateQTaskEvent = QTask_NewQTaskEventFn(0, "NetManager-GMSpectate");
  NetManager_eGameMessagePickupQTaskEvent = QTask_NewQTaskEventFn(0, "NetManager-GMPickup");
  NetManager_eGameMessageRequestPickupQTaskEvent = QTask_NewQTaskEventFn(0, "NetManager-GMRequestPickup");
  NetManager_eGameMessageDropQTaskEvent = QTask_NewQTaskEventFn(0, "NetManager-GMDrop");
  NetManager_eGameMessageRequestDropQTaskEvent = QTask_NewQTaskEventFn(0, "NetManager-GMRequestDrop");
  NetManager_eGameMessageActivateQTaskEvent = QTask_NewQTaskEventFn(0, "NetManager-GMActivate");
  NetManager_eGameMessageObjectiveQTaskEvent = QTask_NewQTaskEventFn(0, "NetManager-GMObjective");
  NetManager_eGameMessageEquipQTaskEvent = QTask_NewQTaskEventFn(0, "NetManager-GMEquip");
  NetManager_eGameMessageTeamScoreQTaskEvent = QTask_NewQTaskEventFn(0, "NetManager-GMTeamScore");
  NetManager_eGameMessageChatQTaskEvent = QTask_NewQTaskEventFn(0, "NetManager-GMChat");
  NetManager_eGameMessageSettingsQTaskEvent = QTask_NewQTaskEventFn(0, "NetManager-GMSettings");
  NetManager_eGameMessageStatsQTaskEvent = QTask_NewQTaskEventFn(0, "NetManager-GMStats");
  NetManager_eGameMessagePingQTaskEvent = QTask_NewQTaskEventFn(0, "NetManager-GMPing");
  NetManager_eGameMessagePongQTaskEvent = QTask_NewQTaskEventFn(0, "NetManager-GMPong");
  NetManager_eGameMessageListQTaskEvent = QTask_NewQTaskEventFn(0, "NetManager-GMList");
  NetManager_eGameMessageBombQTaskEvent = QTask_NewQTaskEventFn(0, "NetManager-GMBomb");
  NetManager_eGameMessageGrenadeUpdateQTaskEvent = QTask_NewQTaskEventFn(0, "NetManager-GMGrenadeUpdate");
  v1 = QTask_NewQTaskEventFn(0, "NetManager-GMAuthenticate");
  v2 = NetManager_eQTaskType;
  NetManager_eGameMessageAuthenticateQTaskEvent = v1;
  QTask_LinkQTaskEventHandlerFn(NetManager_eQTaskType, 0, NetManager_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, 1, NetManager_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, 2, NetManager_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v2, NetManager_eGameMessageUpdateQTaskEvent, NetManager_ClientGameMessageUpdateHandler);
  QTask_LinkQTaskEventHandlerFn(v2, NetManager_eGameMessageZUpdateQTaskEvent, NetManager_ZUpdateHandler);
  QTask_LinkQTaskEventHandlerFn(v2, NetManager_eGameMessageCreatePlayerQTaskEvent, NetManager_CreatePlayerHandler);
  QTask_LinkQTaskEventHandlerFn(v2, NetManager_eGameMessageDestroyPlayerQTaskEvent, NetManager_DestroyPlayerHandler);
  QTask_LinkQTaskEventHandlerFn(
    v2,
    NetManager_eGameMessageInitGameSettingsQTaskEvent,
    NetManager_InitGameSettingsHandler);
  QTask_LinkQTaskEventHandlerFn(v2, NetManager_eGameMessageStatsQTaskEvent, NetManager_StatsHandler);
  QTask_LinkQTaskEventHandlerFn(v2, NetManager_eGameMessageListQTaskEvent, NetManager_ListCommandHandler);
  QTask_LinkQTaskEventHandlerFn(v2, NetManager_eGameMessageTeamScoreQTaskEvent, NetManager_TeamScoreHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, Flow_eDrawInterpolateQTaskEvent, NetManager_DrawInterpolateHandler);
  Symbol_Register(
    "NetManager_eTeam",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int,
    &NetManager_eTeam,
    4,
    QSCRIPT_SYMBOLCLASS_VARIABLE,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_FINITE);
  NetManager_tMapList.ptHead = (struct Node_s *)&NetManager_tMapList.ptMiddle;
  NetManager_tMapList.ptTail = (struct Node_s *)&NetManager_tMapList;
  NetManager_tMapList.ptMiddle = nullptr;
  NetManager_tActiveMapList.ptHead = (struct Node_s *)&NetManager_tActiveMapList.ptMiddle;
  NetManager_tActiveMapList.ptTail = (struct Node_s *)&NetManager_tActiveMapList;
  NetManager_tActiveMapList.ptMiddle = nullptr;
  result_7086a8.ptHead = (struct Node_s *)&result_7086a8.ptMiddle;
  result_7086a8.ptTail = (struct Node_s *)&result_7086a8;
  result_7086a8.ptMiddle = nullptr;
  NetManager_tClientPacketIDs.ptHead = (struct Node_s *)&NetManager_tClientPacketIDs.ptMiddle;
  NetManager_tClientPacketIDs.ptTail = (struct Node_s *)&NetManager_tClientPacketIDs;
  NetManager_tClientPacketIDs.ptMiddle = nullptr;
  NetManager_tSessionList.ptHead = (struct Node_s *)&NetManager_tSessionList.ptMiddle;
  NetManager_tSessionList.ptTail = (struct Node_s *)&NetManager_tSessionList;
  NetManager_tSessionList.ptMiddle = nullptr;
  NetManager_tSortedSessionList.ptHead = (struct Node_s *)&NetManager_tSortedSessionList.ptMiddle;
  NetManager_tSortedSessionList.ptTail = (struct Node_s *)&NetManager_tSortedSessionList;
  NetManager_tSortedSessionList.ptMiddle = nullptr;
  NetManager_nSelectedSession = -1;
  NetManager_iCurrentSession = 0;
  NetManager_RegisterGameMessage((struct Node_s *)0x4352504C, NetManager_eGameMessageCreatePlayerQTaskEvent, 0);
  NetManager_RegisterGameMessage((struct Node_s *)0x4445504C, NetManager_eGameMessageDestroyPlayerQTaskEvent, 0);
  NetManager_RegisterGameMessage((struct Node_s *)0x494E4954, NetManager_eGameMessageInitGameSettingsQTaskEvent, 0);
  NetManager_RegisterGameMessage((struct Node_s *)0x484E5550, NetManager_eGameMessageUpdateQTaskEvent, 0);
  NetManager_RegisterGameMessage((struct Node_s *)0x5A4E5550, NetManager_eGameMessageZUpdateQTaskEvent, 0);
  NetManager_RegisterGameMessage((struct Node_s *)0x44414D47, NetManager_eGameMessageDamageQTaskEvent, 0);
  NetManager_RegisterGameMessage((struct Node_s *)0x4B494C4C, NetManager_eGameMessageKillQTaskEvent, 0);
  NetManager_RegisterGameMessage((struct Node_s *)0x5350574E, NetManager_eGameMessageSpawnQTaskEvent, 0);
  NetManager_RegisterGameMessage((struct Node_s *)0x53504543, NetManager_eGameMessageSpectateQTaskEvent, 0);
  NetManager_RegisterGameMessage((struct Node_s *)0x52515357, NetManager_eGameMessageRequestSpawnQTaskEvent, 0);
  NetManager_RegisterGameMessage((struct Node_s *)0x5049434B, NetManager_eGameMessagePickupQTaskEvent, 0);
  NetManager_RegisterGameMessage((struct Node_s *)0x52515055, NetManager_eGameMessageRequestPickupQTaskEvent, 0);
  NetManager_RegisterGameMessage((struct Node_s *)0x44524F50, NetManager_eGameMessageDropQTaskEvent, 0);
  NetManager_RegisterGameMessage((struct Node_s *)0x52514452, NetManager_eGameMessageRequestDropQTaskEvent, 0);
  NetManager_RegisterGameMessage((struct Node_s *)0x41435449, NetManager_eGameMessageActivateQTaskEvent, 0);
  NetManager_RegisterGameMessage((struct Node_s *)0x4F424A54, NetManager_eGameMessageObjectiveQTaskEvent, 0);
  NetManager_RegisterGameMessage((struct Node_s *)0x45515549, NetManager_eGameMessageEquipQTaskEvent, 0);
  NetManager_RegisterGameMessage((struct Node_s *)0x54534352, NetManager_eGameMessageTeamScoreQTaskEvent, 0);
  NetManager_RegisterGameMessage((struct Node_s *)0x43484154, NetManager_eGameMessageChatQTaskEvent, 0);
  NetManager_RegisterGameMessage((struct Node_s *)0x53455454, NetManager_eGameMessageSettingsQTaskEvent, 0);
  NetManager_RegisterGameMessage((struct Node_s *)0x53544154, NetManager_eGameMessageStatsQTaskEvent, 0);
  NetManager_RegisterGameMessage((struct Node_s *)0x50494E47, NetManager_eGameMessagePingQTaskEvent, 0);
  NetManager_RegisterGameMessage((struct Node_s *)0x504F4E47, NetManager_eGameMessagePongQTaskEvent, 0);
  NetManager_RegisterGameMessage((struct Node_s *)0x4C495354, NetManager_eGameMessageListQTaskEvent, 0);
  NetManager_RegisterGameMessage((struct Node_s *)0x424F4D42, NetManager_eGameMessageBombQTaskEvent, 0);
  NetManager_RegisterGameMessage((struct Node_s *)0x55504752, NetManager_eGameMessageGrenadeUpdateQTaskEvent, 0);
  NetManager_RegisterGameMessage((struct Node_s *)0x41555448, NetManager_eGameMessageAuthenticateQTaskEvent, 0);
  Symbol_Register(
    "NetManager_ListAvailableItems",
    NetManager_ListAvailableItemsCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "NetManager_ListActiveItems",
    NetManager_ListActiveItemsCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "NetManager_GetActiveMapCount",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))NetManager_GetActiveMapCount,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "NetManager_MoveItemToActiveList",
    NetManager_MoveItemToActiveListCB,
    nullptr,
    2,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "NetManager_MoveItemToAvailableList",
    NetManager_MoveItemToAvailableListCB,
    nullptr,
    2,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "NetManager_ClearActiveList",
    NetManager_ClearActiveListCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "NetManager_MoveActiveListItemUp",
    NetManager_MoveActiveListItemUpCB,
    nullptr,
    2,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "NetManager_MoveActiveListItemDown",
    NetManager_MoveActiveListItemDownCB,
    nullptr,
    2,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "NetManager_GetNumberOfMissionsInActiveList",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))NetManager_GetNumberOfMissionsInActiveListCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "NetManager_isSessionSelected",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))NetManager_isSessionSelectedCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "NetManager_SetName",
    NetManager_SetNameCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "NetManager_GetName",
    NetManager_GetNameCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "NetManager_FillTeams",
    NetManager_FillTeamsCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "NetManager_SetTeam",
    NetManager_SetTeamCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "NetManager_GetTeam",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))NetManager_GetTeamCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "NetManager_RequestTeamChange",
    NetManager_RequestTeamChangeCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "NetManager_SetModel",
    NetManager_SetModelCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "NetManager_SetFace",
    NetManager_SetFaceCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "NetManager_IsModelSelect",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))NetManager_IsModelSelectCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "NetManager_SetMode",
    NetManager_SetModeCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&stru_6A1E00.pfLocalPing,
    NetManager_isModeCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&stru_6A1E00.anRunTimer[28],
    NetManager_CollectBodyPicsCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&stru_6A1E00.anRunTimer[21],
    NetManager_CollectFacePicsCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&stru_6A1E00.anRunTimer[14],
    NetManager_GetActiveBodyCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&stru_6A1E00.anRunTimer[7],
    NetManager_GetActiveFaceCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&stru_6A1E00.anRunTimer[2],
    NetManager_GotoNextCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&stru_6A1E00.nBufferStateIndex,
    NetManager_GotoNextCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&stru_6A1E00.aBufferState[5],
    NetManager_GotoMapCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&stru_6A1E00.aBufferState[3],
    NetManager_GotoMapCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&stru_6A1E00.tStatsPrTick.nKills,
    NetManager_SetBandwidthFromRemoteCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&stru_6A1E00.tStatsPrTick.nSentBytes,
    NetManager_RemoteBandwidthCB,
    nullptr,
    2,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&stru_6A1E00.tStatsPrTick.nReceivedOutOfOrderPacks,
    NetManager_ReduceBandwidthsCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&stru_6A1E00.tStatsPrTick.nPing,
    NetManager_SetMapActiveCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&stru_6A1E00.nLastRun,
    NetManager_SetMapActiveCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&stru_6A1E00.tSendCounters.tCounters[27].nBytes,
    NetManager_SetMapInActiveCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&stru_6A1E00.tSendCounters.tCounters[26].nCounter,
    NetManager_SetMapInActiveCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&stru_6A1E00.tSendCounters.tCounters[24].nBytes,
    NetManager_VoteMapCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&stru_6A1E00.tSendCounters.tCounters[24],
    NetManager_VoteMapCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&stru_6A1E00.tSendCounters.tCounters[22].nCounter,
    NetManager_VoteNextCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&stru_6A1E00.tSendCounters.tCounters[21].nCounter,
    NetManager_VoteNextCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&stru_6A1E00.tSendCounters.tCounters[19].nBytes,
    NetManager_ListMapsCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&stru_6A1E00.tSendCounters.tCounters[18].nBytes,
    NetManager_ListMapsCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&stru_6A1E00.tSendCounters.tCounters[16].nBytes,
    NetManager_RestartmapCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&stru_6A1E00.tSendCounters.tCounters[15].nBytes,
    NetManager_RestartmapCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&stru_6A1E00.tSendCounters.tCounters[13].nBytes,
    NetManager_KickPlayerCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&stru_6A1E00.tSendCounters.tCounters[13],
    NetManager_KickPlayerCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&stru_6A1E00.tSendCounters.tCounters[12],
    NetManager_ChallengeCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&stru_6A1E00.tSendCounters.tCounters[10].nCounter,
    NetManager_VoteKickCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&stru_6A1E00.tSendCounters.tCounters[9].nCounter,
    NetManager_VoteKickCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&stru_6A1E00.tSendCounters.tCounters[7].nCounter,
    NetManager_BanPlayerCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&stru_6A1E00.tSendCounters.tCounters[7],
    NetManager_BanPlayerCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&stru_6A1E00.tSendCounters.tCounters[5],
    NetManager_UnbanPlayerCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&stru_6A1E00.tSendCounters.tCounters[4].nCounter,
    NetManager_UnbanPlayerCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&stru_6A1E00.tSendCounters.tCounters[2].nBytes,
    NetManager_ListBanCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&stru_6A1E00.tSendCounters.tCounters[2],
    NetManager_ListBanCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&stru_6A1E00.tSendCounters.tCounters[1].nCounter,
    NetManager_KillSelfCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&stru_6A1E00.tSendCounters.tCounters[0].nBytes,
    NetManager_RConCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &stru_6A1E00.tSendCounters.zName[16],
    NetManager_MonitorCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &stru_6A1E00.tSendCounters.zName[8],
    NetManager_MonitorCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&stru_6A1E00.tReceiveCounters.tCounters[28].nBytes,
    NetManager_ShowVotesCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&stru_6A1E00.tReceiveCounters.tCounters[27].nBytes,
    NetManager_ShowVotesCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&stru_6A1E00.tReceiveCounters.tCounters[27],
    NetManager_FingerCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&stru_6A1E00.tReceiveCounters.tCounters[26],
    NetManager_AnnounceCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&stru_6A1E00.tReceiveCounters.tCounters[24],
    NetManager_GetRandomCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&stru_6A1E00.tReceiveCounters.tCounters[22],
    NetManager_ListSocketsCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&stru_6A1E00.tReceiveCounters.tCounters[20],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int32,
    &NetManager_nRandomInt,
    4,
    QSCRIPT_SYMBOLCLASS_VARIABLE,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&stru_6A1E00.tReceiveCounters.tCounters[17].nBytes,
    NetManager_SetActiveSessionCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&stru_6A1E00.tReceiveCounters.tCounters[15].nCounter,
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))NetManager_GetActiveSessionCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&stru_6A1E00.tReceiveCounters.tCounters[13],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    nullptr,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&stru_6A1E00.tReceiveCounters.tCounters[10].nBytes,
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)1,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&stru_6A1E00.tReceiveCounters.tCounters[8].nCounter,
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)2,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&stru_6A1E00.tReceiveCounters.tCounters[6].nCounter,
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)3,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&stru_6A1E00.tReceiveCounters.tCounters[4].nCounter,
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)5,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&stru_6A1E00.tReceiveCounters.tCounters[2].nCounter,
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)7,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&stru_6A1E00.tReceiveCounters.tCounters[0].nCounter,
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)8,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  ptHead = (struct Mission_s *)Mission_tMissions.ptHead;
  for ( i = Mission_tMissions.ptHead->ptNext; i; i = i->ptNext )
  {
    if ( ptHead->eGameModeID == 1297435732 )
      NetManager_EnumMissionsCB(ptHead);
    ptHead = (struct Mission_s *)i;
  }
  NetManager_ptMultiplayerLogFile = File_New(&stru_6A1E00.tReceiveCounters.zName[8], "w");
  NetManager_ptMultiplayerMonitorFile = File_New((char *)&stru_6A1E00.nLastReceiveTime, "w");
  NetManager_tRandomState.anRandom[2] = 471633611;
  NetManager_tRandomState.anRandom[1] = -630294115;
  NetManager_tRandomState.anRandom[0] = -1405584205;
  NetManager_nRandomInt = 1405584205;
}

// source: j/0/network/netmanager.c:12610  [anchor-hash]
void __cdecl NetManager_Close()
{
  struct Node_s *ptHead; // eax
  struct Node_s *i; // ebx
  _DWORD **v2; // eax
  int v3; // esi
  struct Node_s *v4; // eax
  struct Node_s *j; // ebx
  _DWORD **v6; // eax
  int v7; // esi
  struct Node_s *k; // eax
  struct Node_s *v9; // eax
  struct Node_s *m; // ebx
  _DWORD **v11; // eax
  int v12; // esi

  Symbol_Remove("NetManager_ListAvailableItems");
  Symbol_Remove("NetManager_ListActiveItems");
  Symbol_Remove("NetManager_MoveItemToActiveList");
  Symbol_Remove("NetManager_MoveItemToAvailableList");
  Symbol_Remove("NetManager_ClearActiveList");
  Symbol_Remove("NetManager_MoveActiveListItemUp");
  Symbol_Remove("NetManager_MoveActiveListItemDown");
  Symbol_Remove("NetManager_GetNumberOfMissionsInActiveList");
  Symbol_Remove((char *)&stru_6A1E00.tReceiveCounters.tCounters[22]);
  Symbol_Remove((char *)&stru_6A1E00.tReceiveCounters.tCounters[24]);
  Symbol_Remove("NetManager_FillTeams");
  Symbol_Remove("NetManager_SetTeam");
  Symbol_Remove("NetManager_GetTeam");
  Symbol_Remove("NetManager_RequestTeamChange");
  Symbol_Remove("NetManager_SetModel");
  Symbol_Remove("NetManager_IsModelSelect");
  Symbol_Remove("NetManager_SetMode");
  Symbol_Remove((char *)&stru_6A1E00.anRunTimer[2]);
  Symbol_Remove((char *)&stru_6A1E00.nBufferStateIndex);
  Symbol_Remove((char *)&stru_6A1E00.aBufferState[5]);
  Symbol_Remove((char *)&stru_6A1E00.aBufferState[3]);
  Symbol_Remove((char *)&stru_6A1E00.tStatsPrTick.nKills);
  Symbol_Remove((char *)&stru_6A1E00.tStatsPrTick.nSentBytes);
  Symbol_Remove((char *)&stru_6A1E00.tStatsPrTick.nReceivedOutOfOrderPacks);
  Symbol_Remove((char *)&stru_6A1E00.tStatsPrTick.nPing);
  Symbol_Remove((char *)&stru_6A1E00.nLastRun);
  Symbol_Remove((char *)&stru_6A1E00.tSendCounters.tCounters[27].nBytes);
  Symbol_Remove((char *)&stru_6A1E00.tSendCounters.tCounters[26].nCounter);
  Symbol_Remove((char *)&stru_6A1E00.tSendCounters.tCounters[24].nBytes);
  Symbol_Remove((char *)&stru_6A1E00.tSendCounters.tCounters[24]);
  Symbol_Remove((char *)&stru_6A1E00.tSendCounters.tCounters[22].nCounter);
  Symbol_Remove((char *)&stru_6A1E00.tSendCounters.tCounters[21].nCounter);
  Symbol_Remove((char *)&stru_6A1E00.tSendCounters.tCounters[19].nBytes);
  Symbol_Remove((char *)&stru_6A1E00.tSendCounters.tCounters[18].nBytes);
  Symbol_Remove((char *)&stru_6A1E00.tSendCounters.tCounters[13].nBytes);
  Symbol_Remove((char *)&stru_6A1E00.tSendCounters.tCounters[13]);
  Symbol_Remove((char *)&stru_6A1E00.tSendCounters.tCounters[12]);
  Symbol_Remove((char *)&stru_6A1E00.tSendCounters.tCounters[10].nCounter);
  Symbol_Remove((char *)&stru_6A1E00.tSendCounters.tCounters[9].nCounter);
  Symbol_Remove((char *)&stru_6A1E00.tSendCounters.tCounters[7].nCounter);
  Symbol_Remove((char *)&stru_6A1E00.tSendCounters.tCounters[7]);
  Symbol_Remove((char *)&stru_6A1E00.tSendCounters.tCounters[5]);
  Symbol_Remove((char *)&stru_6A1E00.tSendCounters.tCounters[4].nCounter);
  Symbol_Remove((char *)&stru_6A1E00.tSendCounters.tCounters[2].nBytes);
  Symbol_Remove((char *)&stru_6A1E00.tSendCounters.tCounters[2]);
  Symbol_Remove(&stru_6A1E00.tSendCounters.zName[16]);
  Symbol_Remove(&stru_6A1E00.tSendCounters.zName[8]);
  Symbol_Remove((char *)&stru_6A1E00.tSendCounters.tCounters[16].nBytes);
  Symbol_Remove((char *)&stru_6A1E00.tSendCounters.tCounters[15].nBytes);
  Symbol_Remove((char *)&stru_6A1E00.tReceiveCounters.tCounters[17].nBytes);
  Symbol_Remove((char *)&stru_6A1E00.tReceiveCounters.tCounters[15].nCounter);
  Symbol_Remove((char *)&stru_6A1E00.tReceiveCounters.tCounters[26]);
  NetManager_RemoveGameMessage(0x4352504Cu);
  NetManager_RemoveGameMessage(0x4445504Cu);
  NetManager_RemoveGameMessage(0x494E4954u);
  NetManager_RemoveGameMessage(0x484E5550u);
  NetManager_RemoveGameMessage(0x5A4E5550u);
  NetManager_RemoveGameMessage(0x44414D47u);
  NetManager_RemoveGameMessage(0x4B494C4Cu);
  NetManager_RemoveGameMessage(0x5350574Eu);
  NetManager_RemoveGameMessage(0x53504543u);
  NetManager_RemoveGameMessage(0x52515357u);
  NetManager_RemoveGameMessage(0x5049434Bu);
  NetManager_RemoveGameMessage(0x52515055u);
  NetManager_RemoveGameMessage(0x44524F50u);
  NetManager_RemoveGameMessage(0x52514452u);
  NetManager_RemoveGameMessage(0x41435449u);
  NetManager_RemoveGameMessage(0x4F424A54u);
  NetManager_RemoveGameMessage(0x45515549u);
  NetManager_RemoveGameMessage(0x54534352u);
  NetManager_RemoveGameMessage(0x43484154u);
  NetManager_RemoveGameMessage(0x53455454u);
  NetManager_RemoveGameMessage(0x53544154u);
  NetManager_RemoveGameMessage(0x4C495354u);
  NetManager_RemoveGameMessage(0x50494E47u);
  NetManager_RemoveGameMessage(0x504F4E47u);
  NetManager_RemoveGameMessage(0x424F4D42u);
  NetManager_RemoveGameMessage(0x55504752u);
  NetManager_RemoveGameMessage(0x41555448u);
  QTask_DeleteQTaskEvent(NetManager_eGameMessageCreatePlayerQTaskEvent);
  QTask_DeleteQTaskEvent(NetManager_eGameMessageDestroyPlayerQTaskEvent);
  QTask_DeleteQTaskEvent(NetManager_eGameMessageInitGameSettingsQTaskEvent);
  QTask_DeleteQTaskEvent(NetManager_eGameMessageUpdateQTaskEvent);
  QTask_DeleteQTaskEvent(NetManager_eGameMessageZUpdateQTaskEvent);
  QTask_DeleteQTaskEvent(NetManager_eGameMessageDamageQTaskEvent);
  QTask_DeleteQTaskEvent(NetManager_eGameMessageKillQTaskEvent);
  QTask_DeleteQTaskEvent(NetManager_eGameMessageSpawnQTaskEvent);
  QTask_DeleteQTaskEvent(NetManager_eGameMessageSpectateQTaskEvent);
  QTask_DeleteQTaskEvent(NetManager_eGameMessageRequestSpawnQTaskEvent);
  QTask_DeleteQTaskEvent(NetManager_eGameMessagePickupQTaskEvent);
  QTask_DeleteQTaskEvent(NetManager_eGameMessageRequestPickupQTaskEvent);
  QTask_DeleteQTaskEvent(NetManager_eGameMessageDropQTaskEvent);
  QTask_DeleteQTaskEvent(NetManager_eGameMessageRequestDropQTaskEvent);
  QTask_DeleteQTaskEvent(NetManager_eGameMessageActivateQTaskEvent);
  QTask_DeleteQTaskEvent(NetManager_eGameMessageObjectiveQTaskEvent);
  QTask_DeleteQTaskEvent(NetManager_eGameMessageEquipQTaskEvent);
  QTask_DeleteQTaskEvent(NetManager_eGameMessageTeamScoreQTaskEvent);
  QTask_DeleteQTaskEvent(NetManager_eGameMessageChatQTaskEvent);
  QTask_DeleteQTaskEvent(NetManager_eGameMessageSettingsQTaskEvent);
  QTask_DeleteQTaskEvent(NetManager_eGameMessageStatsQTaskEvent);
  QTask_DeleteQTaskEvent(NetManager_eGameMessagePingQTaskEvent);
  QTask_DeleteQTaskEvent(NetManager_eGameMessagePongQTaskEvent);
  QTask_DeleteQTaskEvent(NetManager_eGameMessageListQTaskEvent);
  QTask_DeleteQTaskEvent(NetManager_eGameMessageBombQTaskEvent);
  QTask_DeleteQTaskEvent(NetManager_eGameMessageGrenadeUpdateQTaskEvent);
  QTask_DeleteQTaskEvent(NetManager_eGameMessageAuthenticateQTaskEvent);
  QTask_DeleteQTaskType(NetManager_eQTaskType);
  ptHead = NetManager_tMapList.ptHead;
  for ( i = NetManager_tMapList.ptHead->ptNext; i; i = i->ptNext )
  {
    v2 = Node_Remove(ptHead);
    if ( v2 )
    {
      v3 = *(_DWORD *)((unsigned int)(v2 - 1) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v3);
      memset(*(void **)(v3 + 8), 0xCDu, *(_DWORD *)(v3 + 16));
      free((void *)v3);
    }
    ptHead = i;
  }
  v4 = NetManager_tActiveMapList.ptHead;
  for ( j = NetManager_tActiveMapList.ptHead->ptNext; j; j = j->ptNext )
  {
    v6 = Node_Remove(v4);
    if ( v6 )
    {
      v7 = *(_DWORD *)((unsigned int)(v6 - 1) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v7);
      memset(*(void **)(v7 + 8), 0xCDu, *(_DWORD *)(v7 + 16));
      free((void *)v7);
    }
    v4 = j;
  }
  for ( k = result_7086a8.ptHead->ptNext; k; k = k->ptNext )
    ;
  v9 = NetManager_tClientPacketIDs.ptHead;
  for ( m = NetManager_tClientPacketIDs.ptHead->ptNext; m; m = m->ptNext )
  {
    v11 = Node_Remove(v9);
    if ( v11 )
    {
      v12 = *(_DWORD *)((unsigned int)(v11 - 1) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v12);
      memset(*(void **)(v12 + 8), 0xCDu, *(_DWORD *)(v12 + 16));
      free((void *)v12);
    }
    v9 = m;
  }
  if ( NetManager_ptMultiplayerLogFile == &File_tDummyAsyncFile )
    File_tDummyAsyncFile.isAsync = false;
  else
    File_atDevice[NetManager_ptMultiplayerLogFile->eDeviceID].pfDelete(
      NetManager_ptMultiplayerLogFile->eDeviceID,
      NetManager_ptMultiplayerLogFile);
  if ( NetManager_ptMultiplayerMonitorFile == &File_tDummyAsyncFile )
    File_tDummyAsyncFile.isAsync = false;
  else
    File_atDevice[NetManager_ptMultiplayerMonitorFile->eDeviceID].pfDelete(
      NetManager_ptMultiplayerMonitorFile->eDeviceID,
      NetManager_ptMultiplayerMonitorFile);
}

// source: j/0/network/netmanager.c:12801  [size]
void __cdecl NetManager_LoadSprites()
{
  ;
}

// source: j/0/network/netmanager.c:12844  [size]
void __cdecl NetManager_DeAllocSprites()
{
  ;
}

// source: j/0/network/netmanager.c:12880  [anchor-hash]
char *__cdecl NetManager_LogMonitorMessage(char *zFormat)
{
  File_printf(NetManager_ptMultiplayerMonitorFile, zFormat);
  return (char *)File_atDevice[NetManager_ptMultiplayerMonitorFile->eDeviceID].pfSync(
                         NetManager_ptMultiplayerMonitorFile->eDeviceID,
                         NetManager_ptMultiplayerMonitorFile,
                         FILE_SYNC_FLUSH);
}

// source: j/0/network/netmanager.c:12898  [anchor-strings]
void __cdecl NetManager_LogMessage(char *zFormat)
{
  #pragma pack(push, 1)
  union
  {
    struct { int ltime; };
    struct { char igi2_o1[4]; char zEval[256]; };
    struct { char igi2_o2[260]; char zTemp[312]; };
    char igi2_extent[572];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct tm *v1; // eax
  struct QTask_s *ptNetManagerQTask; // ecx
  int ptMiddle; // eax
  struct QTask_s *v4; // esi

  time(&igi2_frame.ltime);
  v1 = gmtime(&igi2_frame.ltime);
  _snprintf(igi2_frame.zTemp, 0x131u, (char *const)&stru_6A1E00.isSynchronized, v1->tm_hour, v1->tm_min, v1->tm_sec, zFormat);
  File_printf(NetManager_ptMultiplayerLogFile, igi2_frame.zTemp);
  File_atDevice[NetManager_ptMultiplayerLogFile->eDeviceID].pfSync(
    NetManager_ptMultiplayerLogFile->eDeviceID,
    NetManager_ptMultiplayerLogFile,
    FILE_SYNC_FLUSH);
  if ( Flow_ptFlow )
  {
    ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
    if ( ptNetManagerQTask )
    {
      if ( !ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
      {
        ptMiddle = (int)ptNetManagerQTask[35].tQTaskRefList.ptMiddle;
        if ( ptMiddle >= 30 )
        {
          if ( ptMiddle == 30 )
          {
            strncpy(igi2_frame.zEval, (char *)&stru_6A1E00.tServerGameSettings.nSpawnSafeTime, 0xFFu);
            NetManager_ServerAnnounce(igi2_frame.zEval);
          }
        }
        else
        {
          _snprintf(igi2_frame.zEval, 0xFFu, (char *const)&stru_6A1E00.nTrafficControlTimer, zFormat);
          v4 = Flow_ptFlow->ptNetManagerQTask;
          if ( (int)v4[35].tQTaskRefList.ptMiddle <= 30 )
          {
            NetManager_ServerMessage(igi2_frame.zEval, false);
            ++*(int *)&v4[35].tQTaskRefList.ptMiddle;
          }
        }
      }
    }
  }
}

// source: j/0/network/netmanager.c:12950  [anchor-strings]
// positive sp value has been detected, the output may be wrong!
void __cdecl NetManager_LogTextAndTime(
        struct NetManager_s *ptNetManager,
        char *zText,
        int ltcg_eax,
        int ltcg_edi)
{
  int PerformanceCounter; // eax
  int v5; // esi
  int v6; // eax
  char v7[256]; // [esp-100h] [ebp-100h] BYREF

  if ( ltcg_eax == 6758812 )
    PerformanceCounter = ((int (*)(void))ltcg_edi)();
  else
    PerformanceCounter = Timer_GetPerformanceCounter();
  v5 = PerformanceCounter - Timer_nStartTime - ptNetManager->tStatsPrTick.nBandwidth;
  if ( Timer_isPerformanceCounter )
    v6 = Timer_GetPerformanceCounter();
  else
    v6 = ((int (*)(void))ltcg_edi)();
  _snprintf(
    v7,
    0xFFu,
    (char *const)&stru_6A1E00.tServerGameSettings.nServerTime,
    zText,
    v6 - Timer_nStartTime,
    v5);
  NetManager_LogMessage(v7);
}

// source: j/0/network/netmanager.c:12976  [anchor-callee]
void __cdecl NetManager_RegisterInput(int eNetworkID)
{
  struct QTask_s *ptNetManagerQTask; // ebx
  struct Client_s *ClientFromNetworkID; // esi
  DWORD PerformanceCounter; // eax

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  ClientFromNetworkID = NetManager_GetClientFromNetworkID(eNetworkID);
  if ( ClientFromNetworkID )
  {
    if ( Timer_isPerformanceCounter )
      PerformanceCounter = Timer_GetPerformanceCounter();
    else
      PerformanceCounter = GetTickCount();
    ClientFromNetworkID->nLastPacketReceived = PerformanceCounter - Timer_nStartTime;
  }
  if ( Timer_isPerformanceCounter )
    ptNetManagerQTask[9].tQTaskChildren.ptMiddle = (struct QTask_s *)(Timer_GetPerformanceCounter() - Timer_nStartTime);
  else
    ptNetManagerQTask[9].tQTaskChildren.ptMiddle = (struct QTask_s *)(GetTickCount() - Timer_nStartTime);
}

// source: j/0/network/netmanager.c:13025  [anchor-mhash]
void __cdecl NetManager_ResetAllInput()
{
  struct QTask_s *ptNetManagerQTask; // esi
  struct QTask_s *v1; // edi
  DWORD PerformanceCounter; // eax
  unsigned __int16 v3; // dx
  struct Flow_t *v4; // ecx
  struct QTask_s *v5; // eax
  struct QTask_s *v6; // esi
  DWORD TickCount; // eax

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  v1 = nullptr;
  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  v3 = Client_eQTaskType;
  v4 = Flow_ptFlow;
  ptNetManagerQTask[9].tQTaskChildren.ptMiddle = (struct QTask_s *)(PerformanceCounter - Timer_nStartTime);
  if ( QTask_GetFirstChildOfType(v4->ptNetManagerQTask, v3) )
  {
    while ( 1 )
    {
      v5 = v1 ? QTask_GetNextSiblingOfType(v1, v3) : QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, v3);
      v6 = v5;
      v1 = v5;
      if ( !v5 )
        break;
      if ( Timer_isPerformanceCounter )
        TickCount = Timer_GetPerformanceCounter();
      else
        TickCount = GetTickCount();
      v3 = Client_eQTaskType;
      v6[5].tQTaskRefList.ptTail = (struct QReference_s *)(TickCount - Timer_nStartTime);
    }
  }
}

// source: j/0/network/netmanager.c:13057  [anchor-callee]
enum bool __cdecl NetManager_IsShouldSendServerInfo()
{
  enum bool result; // eax

  result = (enum bool)Flow_ptFlow->ptNetManagerQTask;
  if ( result )
    return *(_DWORD *)(result + 344);
  return result;
}

// source: j/0/network/netmanager.c:13080  [anchor-strings]
enum bool __cdecl NetManager_SetStartGameStatus(enum bool isStarted)
{
  struct QTask_s *ptNetManagerQTask; // esi
  DWORD PerformanceCounter; // eax

  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
    ptNetManagerQTask[8].tQTaskRefList.ptMiddle = (struct QReference_s *)isStarted;
    if ( isStarted )
    {
      if ( Timer_isPerformanceCounter )
        PerformanceCounter = Timer_GetPerformanceCounter();
      else
        PerformanceCounter = GetTickCount();
      ptNetManagerQTask[9].tQTaskRefList.ptMiddle = (struct QReference_s *)(PerformanceCounter - Timer_nStartTime);
      NetManager_SetLocalBandwidth(ClientConfig_tClientConfig.nBandwidth);
      NetManager_LogMessage((char *)&stru_6A1E00.tServerGameSettings.nSpawnAreaTaskID);
    }
    else
    {
      ptNetManagerQTask[9].tQTaskRefList.ptMiddle = (struct QReference_s *)-1;
      NetManager_LogMessage((char *)&stru_6A1E00.tServerGameSettings.nMissionTime);
    }
  }
  return isStarted;
}

// source: j/0/network/netmanager.c:13122  [anchor-strings]
void __cdecl NetManager_SetLocalBandwidth(int nBandwidth)
{
  struct QTask_s *ptNetManagerQTask; // eax
  struct Client_s *ClientFromNetworkID; // eax
  struct Client_s *v3; // esi
  char zTemp[256]; // [esp+0h] [ebp-100h] BYREF

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  if ( ptNetManagerQTask )
  {
    ClientFromNetworkID = NetManager_GetClientFromNetworkID((int)ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
    v3 = ClientFromNetworkID;
    if ( ClientFromNetworkID )
    {
      if ( ClientFromNetworkID->eNetworkID )
      {
        _snprintf(
          zTemp,
          0xFFu,
          &stru_6A1E00.tServerGameSettings.isPasswordProtected,
          ClientFromNetworkID->tStats.nObjectives,
          nBandwidth);
        NetManager_LogMessage(zTemp);
        v3->tStats.nObjectives = nBandwidth;
      }
      else
      {
        NetManager_LogMessage(&stru_6A1E00.tServerGameSettings.zServerName[24]);
        v3->tStats.nObjectives = 0;
      }
    }
  }
}

// source: j/0/network/netmanager.c:13170  [anchor-strings]
void __cdecl NetManager_RunNetworkInterrupt()
{
  struct QTask_s *ptNetManagerQTask; // edi
  struct QTask_s *ptTail; // edx
  struct QTask_s *v2; // edx
  struct Flow_t *v3; // eax

  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
    ptTail = ptNetManagerQTask[32].tQTaskChildren.ptTail;
    if ( !*((_DWORD *)&ptNetManagerQTask[31].tQTaskChildren.ptTail + (_DWORD)ptTail) )
    {
      v2 = (struct QTask_s *)((char *)&ptTail->ptNext + 1);
      ptNetManagerQTask[32].tQTaskChildren.ptTail = v2;
      *((_DWORD *)&ptNetManagerQTask[31].tQTaskChildren.ptTail + (_DWORD)v2) = 1;
      ptNetManagerQTask[36].ptPrev = (struct QTask_s *)1;
      NetManager_RunAlways((struct NetManager_s *)ptNetManagerQTask, (char *)1);
      v3 = Flow_ptFlow;
      ptNetManagerQTask[36].ptPrev = nullptr;
      --v3->ptNetManagerQTask[32].tQTaskChildren.ptTail;
    }
  }
}

// source: j/0/network/netmanager.c:13191  [anchor-strings]
struct NetworkMessageContext_s *__cdecl NetManager_PrintPacketNumber(
        struct NetworkMessageContext_s *ptContext,
        enum bool isSend)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v5; };
    struct { char igi2_o1[4]; char zLastPacketType[12]; };
    struct { char igi2_o2[16]; char zText[256]; };
    char igi2_extent[272];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  _DWORD *pxNetworkPacketContents; // ecx
  int v3; // eax
  struct NetworkMessageContext_s *result; // eax

  pxNetworkPacketContents = ptContext->pxNetworkPacketContents;
  v3 = pxNetworkPacketContents[2];
  igi2_frame.zLastPacketType[3] = v3;
  v3 >>= 8;
  igi2_frame.zLastPacketType[2] = v3;
  igi2_frame.zLastPacketType[0] = (unsigned __int16)(v3 >> 8) >> 8;
  igi2_frame.zLastPacketType[1] = BYTE1(v3);
  igi2_frame.zLastPacketType[4] = 0;
  igi2_frame.v5 = pxNetworkPacketContents[1];
  if ( isSend )
    sprintf(igi2_frame.zText, "SOCKETSEND: %s - %d\n", igi2_frame.zLastPacketType, igi2_frame.v5);
  else
    sprintf(igi2_frame.zText, "SOCKETRECEIVE: %s - %d\n", igi2_frame.zLastPacketType, igi2_frame.v5);
  NetManager_LogMessage(igi2_frame.zText);
  return result;
}

// source: j/0/network/netmanager.c:13237  [size]
enum bool __cdecl NetManager_IsServerSupported()
{
  return true;
}

// source: j/0/network/netmanager.c:13250  [size]
float __cdecl NetManager_GetSpawnCamOffsetGamma()
{
  return NetManager_vSpawnCamOffsetGamma;
}
