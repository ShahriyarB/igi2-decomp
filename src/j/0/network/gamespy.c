/* j/0/network/gamespy.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/network/gamespy.c:112  [anchor-strings]
void __cdecl info_callback(char *outbuf, int maxlen, void *userdata)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s *v17; };
    struct { char igi2_o1[4]; char Buffer[200]; };
    struct { char igi2_o2[204]; char a1[256]; };
    char igi2_extent[460];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Node_s *ptHead; // ecx
  struct QTask_s *ptNetManagerQTask; // esi
  struct Node_s *ptNext; // eax
  struct Node_s *v6; // ebx
  unsigned int v7; // eax
  char *v8; // edi
  char *v9; // edi
  char *v10; // esi
  char v11; // cl
  struct QObjectVector_s *v12; // eax
  bool v13; // zf
  unsigned int nAllocated; // eax
  double v15; // st7
  DWORD PerformanceCounter; // eax

  ptHead = Mission_tMissions.ptHead;
  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  ptNext = Mission_tMissions.ptHead->ptNext;
  igi2_frame.v17 = ptNetManagerQTask;
  if ( Mission_tMissions.ptHead->ptNext )
  {
    while ( ptHead[1].ptNext != (struct Node_s *)ptNetManagerQTask[3].ptNext )
    {
      ptHead = ptNext;
      ptNext = ptNext->ptNext;
      if ( !ptNext )
        goto LABEL_4;
    }
    v6 = ptHead;
  }
  else
  {
LABEL_4:
    v6 = nullptr;
  }
  sprintf(igi2_frame.Buffer, "\\hostname\\%s", (char *)&ptNetManagerQTask[1].ptPrev);
  strcat(outbuf, igi2_frame.Buffer);
  sprintf(igi2_frame.Buffer, "\\hostport\\%d", gamedata.hostport);
  strcat(outbuf, igi2_frame.Buffer);
  if ( v6 )
    sprintf(igi2_frame.Buffer, "\\mapname\\%s", &v6[2]);
  else
    sprintf(igi2_frame.Buffer, "\\mapname\\%s", "?No map name");
  strcat(outbuf, igi2_frame.Buffer);
  sprintf(igi2_frame.Buffer, "\\gametype\\%s", gamedata.gametype);
  v7 = strlen(igi2_frame.Buffer) + 1;
  v8 = &outbuf[strlen(outbuf)];
  qmemcpy(v8, igi2_frame.Buffer, 4 * (v7 >> 2));
  v10 = &igi2_frame.Buffer[4 * (v7 >> 2)];
  v9 = &v8[4 * (v7 >> 2)];
  v11 = v7;
  v12 = Network_ptLoadingHosts;
  v13 = Network_ptLoadingHosts == nullptr;
  qmemcpy(v9, v10, v11 & 3);
  if ( v13 )
    nAllocated = 0;
  else
    nAllocated = v12->nAllocated;
  sprintf(igi2_frame.Buffer, "\\numplayers\\%d", nAllocated + SBYTE1(igi2_frame.v17[3].ptPrev));
  strcat(outbuf, igi2_frame.Buffer);
  sprintf(igi2_frame.Buffer, "\\maxplayers\\%d", SBYTE2(igi2_frame.v17[3].ptPrev));
  strcat(outbuf, igi2_frame.Buffer);
  sprintf(igi2_frame.Buffer, "\\gamemode\\%s", &gamedata);
  strcat(outbuf, igi2_frame.Buffer);
  sprintf(igi2_frame.Buffer, "\\bwidth\\%d", ClientConfig_tClientConfig.nBandwidth);
  strcat(outbuf, igi2_frame.Buffer);
  v15 = (double)(int)pValue_84b73b4 * 0.009999999776482582;
  if ( v15 <= 0.009999999776482582 )
    v15 = 0.009999999776482582;
  sprintf(igi2_frame.Buffer, "\\maxout\\%.1f", (double)(int)pValue_84b73b8 * v15);
  strcat(outbuf, igi2_frame.Buffer);
  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  sprintf(
    igi2_frame.Buffer,
    "\\uptime\\%d",
    (int)(PerformanceCounter - Timer_nStartTime - (unsigned int)igi2_frame.v17[9].tQTaskRefList.ptHead) / 60000);
  strcat(outbuf, igi2_frame.Buffer);
  NetMission_GetWhoDidLastObjective();
  sprintf(igi2_frame.Buffer, "\\timeleft\\%s", igi2_frame.a1);
  strcat(outbuf, igi2_frame.Buffer);
  sub_44B380(igi2_frame.a1, 0xFFu);
  sprintf(igi2_frame.Buffer, "\\mapstat\\%s", igi2_frame.a1);
  strcat(outbuf, igi2_frame.Buffer);
}

// source: j/0/network/gamespy.c:180  [anchor-strings]
void __cdecl rules_callback(char *outbuf, int maxlen, void *userdata)
{
  struct QTask_s *ptNetManagerQTask; // ebp
  struct QTask_s *ptNext; // ecx
  double v5; // st7
  char Buffer[80]; // [esp+1Ch] [ebp-50h] BYREF

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  ptNext = ptNetManagerQTask[5].ptNext;
  ptNetManagerQTask = (struct QTask_s *)((char *)ptNetManagerQTask + 44);
  sprintf(Buffer, "\\timelimit\\%d", (int)ptNext / 60000);
  strcat(outbuf, Buffer);
  sprintf(Buffer, "\\autobalance\\%d", BYTE2(ptNetManagerQTask[4].tQTaskChildren.ptMiddle) != 0);
  strcat(outbuf, Buffer);
  sprintf(Buffer, "\\teamdamage\\%d", BYTE1(ptNetManagerQTask[4].tQTaskChildren.ptMiddle) != 0);
  strcat(outbuf, Buffer);
  sprintf(Buffer, "\\sniper\\%d", LOBYTE(ptNetManagerQTask[5].ptNext) != 0);
  strcat(outbuf, Buffer);
  sprintf(Buffer, "\\bombrepos\\%d", (int)ptNetManagerQTask[4].tQTaskRefList.ptTail / 60);
  strcat(outbuf, Buffer);
  sprintf(Buffer, "\\specmode\\%d", ptNetManagerQTask[4].tQTaskChildren.ptTail);
  strcat(outbuf, Buffer);
  sprintf(Buffer, "\\pingmax\\%d", ServerConfig_tServerConfig.nPingMax);
  strcat(outbuf, Buffer);
  sprintf(Buffer, "\\plossmax\\%.1f", (double)ServerConfig_tServerConfig.nPlossMax * 0.10000000149011612);
  strcat(outbuf, Buffer);
  sprintf(Buffer, "\\bwidth\\%d", ClientConfig_tClientConfig.nBandwidth);
  strcat(outbuf, Buffer);
  v5 = (double)(int)pValue_84b73b4 * 0.009999999776482582;
  if ( v5 <= 0.009999999776482582 )
    v5 = 0.009999999776482582;
  sprintf(Buffer, "\\maxout\\%.1f", (double)(int)pValue_84b73b8 * v5);
  strcat(outbuf, Buffer);
  if ( AppContext_tAppContext.isServer )
    sprintf(Buffer, "\\dedicated\\1");
  else
    sprintf(Buffer, "\\dedicated\\0");
  strcat(outbuf, Buffer);
  if ( strlen(ServerConfig_tServerConfig.zServerPassword) )
    sprintf(Buffer, "\\password\\1");
  else
    sprintf(Buffer, "\\password\\0");
  strcat(outbuf, Buffer);
}

// source: j/0/network/gamespy.c:261  [anchor-strings]
void __cdecl players_callback(char *outbuf, int maxlen, void *userdata)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s *v20; };
    struct { char igi2_o1[4]; struct QTask_s **p_ptPrev; };
    struct { char igi2_o2[8]; struct QTask_s *v22; };
    struct { char igi2_o3[12]; struct QTask_s *v23; };
    struct { char igi2_o4[16]; char Buffer[160]; };
    char igi2_extent[176];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v3; // ebp
  unsigned int v4; // eax
  struct Flow_t *v5; // edx
  struct QTask_s *ptNetManagerQTask; // esi
  unsigned __int16 v7; // dx
  struct QTask_s *FirstChildOfType; // eax
  int ptPrev; // edi
  struct QTask_s *v10; // eax
  int ptNext; // eax
  unsigned int v12; // eax
  char *v13; // edi
  struct QTask_s *v14; // eax
  struct QTask_s *v15; // esi
  struct QReference_s *ptMiddle; // ebx
  struct QReference_s *ptHead; // ebp
  char *v18; // edi
  char v19; // al

  v3 = nullptr;
  igi2_frame.p_ptPrev = &Flow_ptFlow->ptNetManagerQTask[1].ptPrev;
  sprintf(igi2_frame.Buffer, "\\team_t%d\\%s\\team_t%d\\%s", 0, "IGI", 1, "CON");
  v4 = strlen(igi2_frame.Buffer) + 1;
  v5 = Flow_ptFlow;
  qmemcpy(&outbuf[strlen(outbuf)], igi2_frame.Buffer, v4);
  ptNetManagerQTask = v5->ptNetManagerQTask;
  v7 = TeamManager_eQTaskType;
  FirstChildOfType = QTask_GetFirstChildOfType(ptNetManagerQTask, TeamManager_eQTaskType);
  if ( FirstChildOfType )
    ptPrev = (int)FirstChildOfType[1].ptPrev;
  else
    ptPrev = -1;
  v10 = QTask_GetFirstChildOfType(ptNetManagerQTask, v7);
  if ( v10 )
    ptNext = (int)v10[1].ptNext;
  else
    ptNext = -1;
  sprintf(igi2_frame.Buffer, "\\score_t%d\\%d\\score_t%d\\%d", 0, ptNext, 1, ptPrev);
  v12 = strlen(igi2_frame.Buffer) + 1;
  v13 = &outbuf[strlen(outbuf)];
  while ( 1 )
  {
    qmemcpy(v13, igi2_frame.Buffer, v12);
    v14 = v3
        ? QTask_GetNextSiblingOfType(v3, Client_eQTaskType)
        : QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, Client_eQTaskType);
    igi2_frame.v22 = v14;
    if ( !v14 )
      break;
    v15 = v14[1].ptNext;
    ptMiddle = v14[6].tQTaskRefList.ptMiddle;
    ptHead = v14[1].tQTaskRefList.ptHead;
    v18 = (char *)&v14[2];
    igi2_frame.v20 = v14[8].ptNext;
    igi2_frame.v23 = v14[8].ptPrev;
    if ( strlen((char *)&v14[2]) > 0x40 )
    {
      v18 = "?BAD NAME";
    }
    else
    {
      for ( ; strchr(v18, 92); *strchr(v18, 92) = 46 )
        ;
    }
    v19 = *((_BYTE *)igi2_frame.p_ptPrev + 81);
    if ( v19 > 14 )
    {
      if ( v19 > 22 )
        sprintf(igi2_frame.Buffer, "\\player_%d\\%s", v15, v18);
      else
        sprintf(igi2_frame.Buffer, "\\player_%d\\%s\\ping_%d\\%d\\team_%d\\%d", v15, v18, v15, ptMiddle, v15, ptHead);
    }
    else
    {
      sprintf(
        igi2_frame.Buffer,
        "\\player_%d\\%s\\frags_%d\\%d\\deaths_%d\\%d\\ping_%d\\%d\\team_%d\\%d",
        v15,
        v18,
        v15,
        igi2_frame.v20,
        v15,
        igi2_frame.v23,
        v15,
        ptMiddle,
        v15,
        ptHead);
    }
    v12 = strlen(igi2_frame.Buffer) + 1;
    v13 = &outbuf[strlen(outbuf)];
    v3 = igi2_frame.v22;
  }
}

// source: j/0/network/gamespy.c:336  [size]
int __cdecl init_game(int nPort)
{
  gamedata.hostport = nPort;
  return nPort;
}

// source: j/0/network/gamespy.c:350  [size]
unsigned __int16 __cdecl GameSpy_GetQTaskType()
{
  return GameSpy_eQTaskType;
}

// source: j/0/network/gamespy.c:364  [size]
struct QTask_s *__cdecl GameSpy_New(
        struct QTask_s *ptParentQTask,
        struct GameSpyCreateContext_s *ptCreateContext)
{
  return QTask_NewFn(ptParentQTask, GameSpy_eQTaskType, ptCreateContext);
}

// source: j/0/network/gamespy.c:383  [anchor-mhash]
void __cdecl GameSpy_RunHandler(struct QTask_s *ptQTask)
{
  struct qr_implementation_s *v1; // esi

  if ( ptQTask[1].ptNext == (struct QTask_s *)1 )
  {
    v1 = current_rec;
    qr_check_send_heartbeat(current_rec);
    qr_check_queries(v1);
  }
  else
  {
    qr_check_queries(current_rec);
  }
  gcd_think();
}

// source: j/0/network/gamespy.c:415  [anchor-hash]
void __cdecl GameSpy_StateChanged()
{
  send_heartbeat(current_rec, 1);
}

// source: j/0/network/gamespy.c:429  [anchor-strings]
void __cdecl GameSpy_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { char secret_key[12]; };
    struct { char igi2_o1[12]; struct WSAData WSAData; };
    char igi2_extent[412];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  unsigned int v2; // esi
  struct QTask_s *v3; // ecx
  int v4; // ebp

  v2 = *(_DWORD *)pxContext;
  qmemcpy(&gamedata, "openplay", 8);
  strcpy(gamedata.gametype, "Team match");
  *(_DWORD *)&gamedata.gamemode[8] = &unk_676E69;
  v3 = *((struct QTask_s **)pxContext + 3);
  strcpy(igi2_frame.secret_key, "j4F9cY");
  ptQTask[1].ptNext = v3;
  WSAStartup(0x101u, &igi2_frame.WSAData);
  init_qrec(
    nullptr,
    0,
    v2,
    v2,
    "projectigi2r",
    igi2_frame.secret_key,
    (void (__cdecl *)(char *, int, void *))qr_basic_callback__,
    info_callback,
    rules_callback,
    players_callback,
    nullptr);
  if ( do_connect(v2, qr_hostname, 27900, &current_rec->hbaddr) )
    NetManager_LogMessage("Error starting Q&R SDK\n");
  gamedata.hostport = *((_DWORD *)pxContext + 1);
  v4 = *((_DWORD *)pxContext + 2);
  *(_DWORD *)&valaddr.sin_family = 2;
  valaddr.sin_addr.S_un.S_addr = 0;
  *(_DWORD *)valaddr.sin_zero = 0;
  Network_pfExternalReceiveHandler = (void (__cdecl *)(char *, int, struct sockaddr *))sub_5D7310;
  Network_ExternalReceiveMarkerI = 92;
  Network_ExternalReceiveMarkerII = 59;
  localport = -1;
  g_sock = stru_6B0500.querysock;
  stru_6B0500.cdkeyprocess = cdkey_process_buf;
  *(_DWORD *)&valaddr.sin_zero[4] = 0;
  valaddr.sin_port = htons(0x74D6u);
  valaddr.sin_addr.S_un.S_addr = stru_6B0500.hbaddr.sin_addr.S_un.S_addr;
  gcd_init_common(v4);
  if ( ptQTask[1].ptNext )
    NetManager_LogMessage("Gamespy (public mode) link created\n");
  else
    NetManager_LogMessage("Gamespy (private mode) link created\n");
}

// source: j/0/network/gamespy.c:502  [anchor-caller]
char *__cdecl GameSpy_CreateCDChallengeResponse(
        char *zKey,
        char *zChallenge,
        char *zResponse)
{
  return gcd_compute_response((char *)zKey, (char *)zChallenge, zResponse);
}

// source: j/0/network/gamespy.c:516  [size]
// attributes: thunk
void __cdecl GameSpy_DisconnectClient(int eNetworkID)
{
  int v1; // eax

  gcd_disconnect_user(v1);
}

// source: j/0/network/gamespy.c:530  [anchor-strings]
void __cdecl GameSpy_GetCDKey(char *zCDKey, int nLength)
{
  #pragma pack(push, 1)
  union
  {
    struct { HKEY phkResult; };
    struct { char igi2_o1[4]; DWORD cbData; };
    char igi2_extent[8];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  igi2_frame.cbData = 50;
  if ( RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\IGI 2 Retail\\CDKey", 0, 1u, &igi2_frame.phkResult)
    || RegQueryValueExA(igi2_frame.phkResult, "CDKey", nullptr, nullptr, (LPBYTE)zCDKey, &igi2_frame.cbData) )
  {
    *zCDKey = 0;
  }
  RegCloseKey(igi2_frame.phkResult);
}

// source: j/0/network/gamespy.c:585  [anchor-strings]
void __cdecl GameSpy_DeleteHandler(struct QTask_s *ptQTask)
{
  struct qr_implementation_s *v1; // esi
  unsigned int hbsock; // eax

  Network_pfExternalReceiveHandler = nullptr;
  Network_ExternalReceiveMarkerI = 92;
  Network_ExternalReceiveMarkerII = 59;
  *(_DWORD *)gamedata.gamemode = 1953069157;
  *(_DWORD *)&gamedata.gamemode[4] = &unk_676E69;
  gcd_disconnect_all();
  closesocket(g_sock);
  g_sock = -1;
  WSACleanup();
  send_heartbeat(current_rec, 2);
  v1 = current_rec;
  if ( current_rec->querysock != -1 && current_rec->qport )
    closesocket(current_rec->querysock);
  hbsock = v1->hbsock;
  if ( hbsock != -1 && hbsock != v1->querysock )
    closesocket(v1->hbsock);
  v1->hbsock = -1;
  v1->querysock = -1;
  v1->lastheartbeat = 0;
  if ( v1 != &stru_6B0500 )
    free(v1);
  WSACleanup();
  NetManager_LogMessage("Gamespy was shut down\n");
}

// source: j/0/network/gamespy.c:610  [size]
void __cdecl GameSpy_Close()
{
  QTask_DeleteQTaskType(GameSpy_eQTaskType);
}

// source: j/0/network/gamespy.c:624  [anchor-strings]
void __cdecl GameSpy_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("GameSpy", 44, BaseQTaskType, 0, 0);
  GameSpy_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 0, GameSpy_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, GameSpy_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, GameSpy_DeleteHandler);
}
