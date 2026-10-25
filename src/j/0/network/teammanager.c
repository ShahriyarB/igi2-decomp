/* j/0/network/teammanager.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/network/teammanager.c:45  [size]
struct QTask_s *__cdecl TeamManager_New(
        struct QTask_s *ptParentQTask,
        struct TeamManagerCreateContext_s *ptCreateContext)
{
  return QTask_NewFn(ptParentQTask, TeamManager_eQTaskType, ptCreateContext);
}

// source: j/0/network/teammanager.c:67  [size]
unsigned __int16 __cdecl TeamManager_GetQTaskType()
{
  return TeamManager_eQTaskType;
}

// source: j/0/network/teammanager.c:84  [size]
struct TeamManager_s *__cdecl TeamManager_GetTeamManager()
{
  return (struct TeamManager_s *)QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, TeamManager_eQTaskType);
}

// source: j/0/network/teammanager.c:97  [size]
void __cdecl TeamManager_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[1].ptPrev = nullptr;
  ptQTask[1].ptNext = nullptr;
  ptQTask[1].tQTaskChildren.ptHead = nullptr;
}

// source: j/0/network/teammanager.c:119  [size]
void __cdecl TeamManager_RunHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: j/0/network/teammanager.c:135  [anchor-hash]
void __cdecl TeamManager_ClearScore()
{
  struct QTask_s *FirstChildOfType; // eax

  FirstChildOfType = QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, TeamManager_eQTaskType);
  FirstChildOfType[1].ptPrev = nullptr;
  FirstChildOfType[1].ptNext = nullptr;
}

// source: j/0/network/teammanager.c:159  [anchor-mhash]
void __cdecl TeamManager_AddScore(int nScore, int eTeam)
{
  struct QTask_s *FirstChildOfType; // eax
  struct QTask_s *ptPrev; // edi
  struct QTask_s *ptNext; // edx

  FirstChildOfType = QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, TeamManager_eQTaskType);
  ptPrev = FirstChildOfType[1].ptPrev;
  ptNext = FirstChildOfType[1].ptNext;
  if ( eTeam == 1 )
  {
    FirstChildOfType[1].ptPrev = (struct QTask_s *)((char *)ptPrev + nScore);
    if ( (int)ptPrev + nScore < 0 )
      FirstChildOfType[1].ptPrev = nullptr;
  }
  else
  {
    FirstChildOfType[1].ptNext = (struct QTask_s *)((char *)ptNext + nScore);
    if ( (int)ptNext + nScore < 0 )
      FirstChildOfType[1].ptNext = nullptr;
  }
  if ( FirstChildOfType[1].ptNext != ptNext || FirstChildOfType[1].ptPrev != ptPrev )
    NetManager_SendScoreUpdate();
}

// source: j/0/network/teammanager.c:208  [anchor-mhash]
int __cdecl TeamManager_GetScore(int eTeam)
{
  struct QTask_s *FirstChildOfType; // eax

  FirstChildOfType = QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, TeamManager_eQTaskType);
  if ( !FirstChildOfType )
    return -1;
  if ( eTeam == 1 )
    return (int)FirstChildOfType[1].ptPrev;
  return (int)FirstChildOfType[1].ptNext;
}

// source: j/0/network/teammanager.c:243  [anchor-hash]
int __cdecl TeamManager_GetMaxScore()
{
  unsigned __int16 v0; // dx
  struct QTask_s *ptNetManagerQTask; // esi
  struct QTask_s *FirstChildOfType; // eax
  int ptNext; // edi
  struct QTask_s *v4; // eax
  int result; // eax

  v0 = TeamManager_eQTaskType;
  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  FirstChildOfType = QTask_GetFirstChildOfType(ptNetManagerQTask, TeamManager_eQTaskType);
  if ( FirstChildOfType )
    ptNext = (int)FirstChildOfType[1].ptNext;
  else
    ptNext = -1;
  v4 = QTask_GetFirstChildOfType(ptNetManagerQTask, v0);
  if ( v4 )
    result = (int)v4[1].ptPrev;
  else
    result = -1;
  if ( result <= ptNext )
    return ptNext;
  return result;
}

// source: j/0/network/teammanager.c:268  [anchor-mhash]
void __cdecl TeamManager_SetScore(int eTeam, int nScore)
{
  struct QTask_s *FirstChildOfType; // eax

  FirstChildOfType = QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, TeamManager_eQTaskType);
  if ( eTeam == 1 )
    FirstChildOfType[1].ptPrev = (struct QTask_s *)nScore;
  else
    FirstChildOfType[1].ptNext = (struct QTask_s *)nScore;
}

// source: j/0/network/teammanager.c:293  [anchor-strings]
void __cdecl TeamManager_CountPlayers(int *nGoodCounter, int *nBadCounter)
{
  struct QTask_s *v2; // esi
  unsigned __int16 v3; // dx
  struct QTask_s *v4; // eax
  struct QReference_s *ptHead; // ecx
  char zTemp[256]; // [esp+4h] [ebp-100h] BYREF

  v2 = nullptr;
  *nGoodCounter = 0;
  *nBadCounter = 0;
LABEL_2:
  v3 = Client_eQTaskType;
  while ( 1 )
  {
    v4 = v2 ? QTask_GetNextSiblingOfType(v2, v3) : QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, v3);
    v2 = v4;
    if ( !v4 )
      break;
    ptHead = v4[1].tQTaskRefList.ptHead;
    if ( ptHead == (struct QReference_s *)-1 )
    {
      _snprintf(zTemp, 0xFFu, "GetFairTeam: Player on TEAM_NONE, player name=%s\n", (char *)&v4[2]);
      NetManager_LogMessage(zTemp);
      goto LABEL_2;
    }
    if ( ptHead )
    {
      if ( ptHead != (struct QReference_s *)1 )
      {
        _snprintf(
          zTemp,
          0xFFu,
          "Unknown team, teamID=%d, player name=%s",
          v4[1].tQTaskRefList.ptHead,
          (char *)&v4[2]);
        LDebug_Error(zTemp);
        abort();
      }
      ++*nBadCounter;
    }
    else
    {
      ++*nGoodCounter;
    }
  }
}

// source: j/0/network/teammanager.c:344  [anchor-strings]
int __cdecl TeamManager_GetFairTeam(int eTeam)
{
  #pragma pack(push, 1)
  union
  {
    struct { int nGoodCounter; };
    struct { char igi2_o1[4]; int nBadCounter; };
    char igi2_extent[8];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  unsigned int v2; // ecx

  igi2_frame.nGoodCounter = 0;
  igi2_frame.nBadCounter = 0;
  TeamManager_CountPlayers(&igi2_frame.nGoodCounter, &igi2_frame.nBadCounter);
  if ( igi2_frame.nBadCounter >= igi2_frame.nGoodCounter )
  {
    if ( igi2_frame.nBadCounter <= igi2_frame.nGoodCounter )
    {
      if ( eTeam == -1 )
      {
        NetManager_LogMessage("TeamManager: Selecting RANDOM TEAM (was balanced)\n");
        v2 = (TeamManager_tRandomState.anRandom[0] >> 7) ^ TeamManager_tRandomState.anRandom[2];
        TeamManager_tRandomState.anRandom[0] += v2 ^ TeamManager_tRandomState.anRandom[1];
        TeamManager_tRandomState.anRandom[2] = v2;
        TeamManager_tRandomState.anRandom[1] ^= v2;
        return TeamManager_tRandomState.anRandom[0] & 1;
      }
      else
      {
        NetManager_LogMessage("TeamManager: Selecting INPUT TEAM (was balanced\n");
        return eTeam;
      }
    }
    else
    {
      NetManager_LogMessage("TeamManager: Selecting GOOD to balance\n");
      return 0;
    }
  }
  else
  {
    NetManager_LogMessage("TeamManager: Selecting BAD to balance\n");
    return 1;
  }
}

// source: j/0/network/teammanager.c:404  [anchor-strings]
void __cdecl TeamManager_SendChangeTeamRequest(int eNetworkID, int eTeam)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zEval[40]; };
    struct { char igi2_o1[40]; char zTemp[256]; };
    char igi2_extent[296];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  _snprintf(igi2_frame.zEval, 0x28u, "NetManager_RequestTeamChange(%d)", eTeam);
  NetworkCommand_RemoteEval((char *)eNetworkID, (int)igi2_frame.zEval, NETMANAGER_HOSTSET_GIVEN_DESTINATION);
  _snprintf(igi2_frame.zTemp, 0xFFu, "NetManager_RequestTeamChange: Requesting [%d] to team %d", eNetworkID, eTeam);
  NetManager_LogMessage(igi2_frame.zTemp);
}

// source: j/0/network/teammanager.c:437  [anchor-strings]
void __cdecl TeamManager_Rebalance()
{
  #pragma pack(push, 1)
  union
  {
    struct { int nBadCounter; };
    struct { char igi2_o1[4]; int nGoodCounter; };
    struct { char igi2_o2[8]; char Buffer[40]; };
    struct { char igi2_o3[48]; char zFormat[256]; };
    char igi2_extent[304];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v0; // esi
  int v1; // eax
  int v2; // ebx
  struct QTask_s *v3; // ebp
  BOOL v4; // edi
  unsigned __int16 v5; // dx
  struct QTask_s *v6; // eax
  char *ptNext; // esi

  if ( BYTE2(Flow_ptFlow->ptNetManagerQTask[5].tQTaskChildren.ptTail) )
  {
    igi2_frame.nGoodCounter = 0;
    igi2_frame.nBadCounter = 0;
    TeamManager_CountPlayers(&igi2_frame.nGoodCounter, &igi2_frame.nBadCounter);
    v0 = igi2_frame.nBadCounter;
    v1 = igi2_frame.nGoodCounter - igi2_frame.nBadCounter;
    if ( igi2_frame.nGoodCounter - igi2_frame.nBadCounter < 0 )
      v1 = igi2_frame.nBadCounter - igi2_frame.nGoodCounter;
    if ( v1 > 1 )
    {
      v2 = 0;
      igi2_frame.nBadCounter = v1 / 2;
      v3 = nullptr;
      v4 = igi2_frame.nGoodCounter > v0;
LABEL_8:
      v5 = Client_eQTaskType;
      while ( 1 )
      {
        v6 = v3 ? QTask_GetNextSiblingOfType(v3, v5) : QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, v5);
        v3 = v6;
        if ( !v6 || v2 >= igi2_frame.nBadCounter )
          break;
        if ( v6[1].tQTaskRefList.ptHead != (struct QReference_s *)v4 )
        {
          ptNext = (char *)v6[1].ptNext;
          _snprintf(igi2_frame.Buffer, 0x28u, "NetManager_RequestTeamChange(%d)", v4);
          NetworkCommand_RemoteEval(ptNext, (int)igi2_frame.Buffer, NETMANAGER_HOSTSET_GIVEN_DESTINATION);
          _snprintf(igi2_frame.zFormat, 0xFFu, "NetManager_RequestTeamChange: Requesting [%d] to team %d", ptNext, v4);
          NetManager_LogMessage(igi2_frame.zFormat);
          ++v2;
          goto LABEL_8;
        }
      }
    }
    else
    {
      NetManager_LogMessage("TeamManager_Rebalance: Teams are balanced\n");
    }
  }
}

// source: j/0/network/teammanager.c:506  [anchor-strings]
void __cdecl TeamManager_ListTeamsForClients()
{
  struct QTask_s *v0; // esi
  struct QTask_s *v1; // eax

  v0 = nullptr;
  DebugConsole_printf("TeamManager: List of clientIDs and teams[T2]\n");
  while ( 1 )
  {
    v1 = v0
       ? QTask_GetNextSiblingOfType(v0, Client_eQTaskType)
       : QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, Client_eQTaskType);
    v0 = v1;
    if ( !v1 )
      break;
    DebugConsole_printf(
      " Player '%s' [id=%d] is on team %d\n",
      (char *)&v1[2],
      v1[1].ptNext,
      v1[1].tQTaskRefList.ptHead);
  }
}

// source: j/0/network/teammanager.c:537  [anchor-callee]
int __cdecl TeamManager_GetNumberOfTeamClients(int eTeam)
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
    if ( v3[1].tQTaskRefList.ptHead == (struct QReference_s *)eTeam )
      ++v4;
  }
  return v4;
}

// source: j/0/network/teammanager.c:569  [size]
void __cdecl TeamManager_Close()
{
  QTask_DeleteQTaskType(TeamManager_eQTaskType);
}

// source: j/0/network/teammanager.c:583  [anchor-hash]
void __cdecl TeamManager_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si
  DWORD PerformanceCounter; // eax
  DWORD v3; // eax

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("TeamManager", 52, BaseQTaskType, 0, 0);
  TeamManager_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 0, (void (__cdecl *)(struct QTask_s *, void *))TeamManager_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, (void (__cdecl *)(struct QTask_s *))TeamManager_RunHandler);
  TeamManager_tRandomState.anRandom[0] = -923067897;
  TeamManager_tRandomState.anRandom[1] = 971667286;
  TeamManager_tRandomState.anRandom[2] = 2146516173;
  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  v3 = PerformanceCounter - Timer_nStartTime;
  TeamManager_tRandomState.anRandom[0] = v3 ^ 0xC8FB1A07;
  TeamManager_tRandomState.anRandom[1] = (v3 << 15) + 971667286;
  TeamManager_tRandomState.anRandom[2] = 2146516173 - (v3 << 9);
}

void __cdecl pfQTaskEvent__(struct QTask_s *a1)
{
  char *v1; // eax
  bool v2; // zf
  int v3; // edx
  char v4; // cl

  LOBYTE(a1[1].ptNext) = 0;
  a1[1].tQTaskChildren.ptMiddle = nullptr;
  a1[1].tQTaskChildren.ptHead = nullptr;
  a1[1].ptPrev = (struct QTask_s *)1024;
  v1 = MagicObjConfigContainer_zFilename;
  v2 = MagicObjConfigContainer_zFilename == nullptr;
  LOBYTE(a1[1].tQTaskChildren.ptTail) = 0;
  if ( !v2 )
  {
    v3 = (char *)&a1[1].tQTaskChildren.ptTail - v1;
    do
    {
      v4 = *v1;
      v1[v3] = *v1;
      ++v1;
    }
    while ( v4 );
  }
}
