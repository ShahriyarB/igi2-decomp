/* j/0/network/ase.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/network/ase.c:54  [anchor-hash]
void __cdecl ASEQuery_wantstatus()
{
  struct Node_s *ptHead; // edx
  struct Node_s *ptNext; // eax

  ptHead = Mission_tMissions.ptHead;
  ptNext = Mission_tMissions.ptHead->ptNext;
  if ( Mission_tMissions.ptHead->ptNext )
  {
    while ( ptHead[1].ptNext != (struct Node_s *)Flow_ptFlow->ptNetManagerQTask[3].ptNext )
    {
      ptHead = ptNext;
      ptNext = ptNext->ptNext;
      if ( !ptNext )
        goto LABEL_4;
    }
  }
  else
  {
LABEL_4:
    ptHead = nullptr;
  }
  ASEQuery_status(
    &Flow_ptFlow->ptNetManagerQTask[1].ptPrev,
    "teams",
    &ptHead[2],
    &Flow_ptFlow->ptNetManagerQTask[2].tQTaskRefList.ptTail,
    &ServerConfig_tServerConfig.zServerPassword[strlen(ServerConfig_tServerConfig.zServerPassword) + 1] != &ServerConfig_tServerConfig.zServerPassword[1],
    SBYTE1(Flow_ptFlow->ptNetManagerQTask[3].ptPrev),
    SBYTE2(Flow_ptFlow->ptNetManagerQTask[3].ptPrev));
}

// source: j/0/network/ase.c:100  [anchor-caller]
void __cdecl ASEQuery_wantrules()
{
  struct QTask_s *ptNetManagerQTask; // esi
  struct QTask_s *ptNext; // ecx
  char zTemp[256]; // [esp+4h] [ebp-100h] BYREF

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  ptNext = ptNetManagerQTask[5].ptNext;
  ptNetManagerQTask = (struct QTask_s *)((char *)ptNetManagerQTask + 44);
  _snprintf(zTemp, 0xFFu, (char *const)&g_ptNetManager.tReceiveCounters.tCounters[9].nBytes, ptNext);
  ASEQuery_addrule(&g_zFileName.atSpriteResources[22].zResourceFilename[24], zTemp);
  _snprintf(
    zTemp,
    0xFFu,
    (char *const)&g_ptNetManager.tReceiveCounters.tCounters[9].nBytes,
    BYTE2(ptNetManagerQTask[4].tQTaskChildren.ptMiddle) != 0);
  ASEQuery_addrule(&g_zFileName.atSpriteResources[29].zResourceFilename[48], zTemp);
  _snprintf(
    zTemp,
    0xFFu,
    (char *const)&g_ptNetManager.tReceiveCounters.tCounters[9].nBytes,
    AppContext_tAppContext.isServer != false);
  ASEQuery_addrule("dedicated", zTemp);
  _snprintf(
    zTemp,
    0xFFu,
    (char *const)&g_ptNetManager.tReceiveCounters.tCounters[9].nBytes,
    BYTE1(ptNetManagerQTask[4].tQTaskChildren.ptMiddle) != 0);
  ASEQuery_addrule(&g_zFileName.atSpriteResources[29].zResourceFilename[60], zTemp);
}

// source: j/0/network/ase.c:146  [anchor-strings]
void __cdecl ASEQuery_wantplayers()
{
  #pragma pack(push, 1)
  union
  {
    struct { struct Client_s *ptClient; };
    struct { char igi2_o1[4]; char zTeam[8]; };
    struct { char igi2_o2[12]; char zPing[8]; };
    struct { char igi2_o3[20]; char zFrags[8]; };
    char igi2_extent[28];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *i; // eax
  struct QTask_s *v1; // eax
  struct QTask_s *ptNext; // edi
  struct QReference_s *ptMiddle; // ebp
  char *v4; // esi
  struct QReference_s *ptHead; // eax

  for ( i = nullptr; ; i = &igi2_frame.ptClient->tQTask )
  {
    v1 = i
       ? QTask_GetNextSiblingOfType(i, Client_eQTaskType)
       : QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, Client_eQTaskType);
    igi2_frame.ptClient = (struct Client_s *)v1;
    if ( !v1 )
      break;
    ptNext = v1[8].ptNext;
    ptMiddle = v1[6].tQTaskRefList.ptMiddle;
    v4 = (char *)&v1[2];
    ptHead = v1[1].tQTaskRefList.ptHead;
    if ( ptHead == (struct QReference_s *)-1 )
    {
      strncpy(igi2_frame.zTeam, "NONE", 5u);
    }
    else if ( ptHead )
    {
      if ( ptHead == (struct QReference_s *)1 )
        strncpy(igi2_frame.zTeam, "CON", 5u);
      else
        strncpy(igi2_frame.zTeam, "???", 5u);
    }
    else
    {
      strncpy(igi2_frame.zTeam, "IGI", 5u);
    }
    igi2_frame.zTeam[4] = 0;
    _snprintf(igi2_frame.zFrags, 5u, (char *const)&g_ptNetManager.tReceiveCounters.tCounters[9].nBytes, ptNext);
    _snprintf(igi2_frame.zPing, 5u, (char *const)&g_ptNetManager.tReceiveCounters.tCounters[9].nBytes, ptMiddle);
    igi2_frame.zFrags[4] = 0;
    igi2_frame.zPing[4] = 0;
    if ( strlen(v4) > 0x40 )
    {
      v4 = "?BAD NAME";
    }
    else
    {
      for ( ; strchr(v4, 92); *strchr(v4, 92) = 46 )
        ;
    }
    ASEQuery_addplayer(v4, igi2_frame.zTeam, 0, igi2_frame.zFrags, igi2_frame.zPing, 0);
  }
}

// source: j/0/network/ase.c:221  [size]
unsigned __int16 __cdecl ASE_GetQTaskType()
{
  return ASE_eQTaskType;
}

// source: j/0/network/ase.c:235  [size]
struct QTask_s *__cdecl ASE_New(
        struct QTask_s *ptParentQTask,
        struct ASECreateContext_s *ptCreateContext)
{
  return QTask_NewFn(ptParentQTask, ASE_eQTaskType, ptCreateContext);
}

// source: j/0/network/ase.c:254  [anchor-strings]
void __cdecl ASE_RunHandler(struct QTask_s *ptQTask)
{
  char zTemp[256]; // [esp+0h] [ebp-100h] BYREF

  if ( ptQTask[1].ptNext )
  {
    if ( !ASEQuery_check() )
    {
      _snprintf(zTemp, 0xFFu, "ASEQuery_check() error: '%s'\n", ASEQuery_error);
      NetManager_LogMessage(zTemp);
    }
  }
}

// source: j/0/network/ase.c:282  [size]
void __cdecl ASE_StateChanged()
{
  ;
}

// source: j/0/network/ase.c:296  [anchor-strings]
void __cdecl ASE_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { SOCKET v3; };
    struct { char igi2_o1[20]; struct sockaddr_in tAddress; };
    struct { char igi2_o2[36]; int nLength; };
    struct { char igi2_o3[40]; char zIP[16]; };
    struct { char igi2_o4[56]; char zTemp[256]; };
    char igi2_extent[312];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int Error; // eax

  memset(&igi2_frame.tAddress, 0, 12);
  ptQTask[1].ptNext = nullptr;
  *(_DWORD *)&igi2_frame.tAddress.sin_zero[4] = 0;
  igi2_frame.v3 = *(_DWORD *)pxContext;
  igi2_frame.nLength = 16;
  if ( getsockname(igi2_frame.v3, (struct sockaddr *)&igi2_frame.tAddress, &igi2_frame.nLength) == -1 )
  {
    Error = WSAGetLastError();
    Network_DebugError("ASE_CreateHandler- getsockname\n", Error);
  }
  else
  {
    _snprintf(
      igi2_frame.zIP,
      0x10u,
      "%d.%d.%d.%d",
      igi2_frame.tAddress.sin_addr.S_un.S_un_b.s_b1,
      igi2_frame.tAddress.sin_addr.S_un.S_un_b.s_b2,
      igi2_frame.tAddress.sin_addr.S_un.S_un_b.s_b3,
      igi2_frame.tAddress.sin_addr.S_un.S_un_b.s_b4);
    if ( ASEQuery_initialize(*((_DWORD *)pxContext + 1), 1, igi2_frame.zIP) )
    {
      _snprintf(igi2_frame.zTemp, 0xFFu, "ASE link created at [%s]\n", igi2_frame.zIP);
      ptQTask[1].ptNext = (struct QTask_s *)1;
    }
    else
    {
      _snprintf(igi2_frame.zTemp, 0xFFu, "ASE: Error initializing: '%s' at [%s]\n", ASEQuery_error, igi2_frame.zIP);
    }
    NetManager_LogMessage(igi2_frame.zTemp);
  }
}

// source: j/0/network/ase.c:357  [anchor-strings]
void __cdecl ASE_DeleteHandler(struct QTask_s *ptQTask)
{
  ASEQuery_shutdown();
  ptQTask[1].ptNext = nullptr;
  NetManager_LogMessage("ASE was shut down\n");
}

// source: j/0/network/ase.c:377  [size]
void __cdecl ASE_Close()
{
  QTask_DeleteQTaskType(ASE_eQTaskType);
}

// source: j/0/network/ase.c:391  [anchor-hash]
void __cdecl ASE_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType(dword_68FAE8, 44, BaseQTaskType, 0, 0);
  ASE_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 0, ASE_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, ASE_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, ASE_DeleteHandler);
}
