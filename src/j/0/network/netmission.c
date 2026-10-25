/* j/0/network/netmission.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/network/netmission.c:113  [anchor-mhash]
void __cdecl NetObjective_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v2; // edx

  v2 = (struct QTask_s *)NetMission_eObjectiveNumber;
  ptQTask[1].ptNext = nullptr;
  ptQTask[1].ptPrev = nullptr;
  ptQTask[1].tQTaskChildren.ptHead = nullptr;
  *(_DWORD *)&ptQTask[2].eQTaskType = 0;
  ptQTask[3].ptNext = nullptr;
  ptQTask[3].ptPrev = nullptr;
  ptQTask[3].tQTaskChildren.ptHead = nullptr;
  *(_DWORD *)&ptQTask[4].eQTaskType = 0;
  ptQTask[5].ptNext = v2;
  NetMission_eObjectiveNumber = (int)&v2->ptNext + 1;
  ptQTask[5].tQTaskChildren.ptHead = nullptr;
  ptQTask[5].ptPrev = (struct QTask_s *)-1;
  ptQTask[5].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[5].tQTaskRefList.ptHead = nullptr;
  ptQTask[5].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[5].tQTaskRefList.ptTail = nullptr;
  ptQTask[5].ptParent = nullptr;
  *(_DWORD *)&ptQTask[5].eQTaskType = 0;
  ptQTask[5].tQTaskChildren.ptTail = (struct QTask_s *)-1;
  SpawnArea_nGoodIndex = 1;
  SpawnArea_nBadIndex = 1;
}

// source: j/0/network/netmission.c:147  [anchor-mhash]
void __cdecl NetMission_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptNetManagerQTask; // edi
  bool v3; // cc
  enum bool v4; // ecx

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  ptQTask[3].ptParent = nullptr;
  *(_DWORD *)&ptQTask[3].eQTaskType = 0;
  ptQTask[4].ptNext = nullptr;
  ptQTask[5].tQTaskRefList.ptTail = nullptr;
  ptQTask[1].tQTaskChildren.ptTail = nullptr;
  ptQTask[1].tQTaskRefList.ptHead = nullptr;
  ptQTask[1].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[1].tQTaskRefList.ptTail = nullptr;
  ptQTask[1].ptParent = nullptr;
  *(_DWORD *)&ptQTask[1].eQTaskType = 0;
  ptQTask[1].ptNext = nullptr;
  ptQTask[1].ptPrev = nullptr;
  ptQTask[1].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[2].ptNext = nullptr;
  NetMission_eCurrentObjective = 1;
  NetMission_eObjectiveNumber = 1;
  ptQTask[2].tQTaskChildren.ptHead = nullptr;
  ptQTask[2].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[2].tQTaskChildren.ptTail = nullptr;
  ptQTask[2].tQTaskRefList.ptHead = nullptr;
  ptQTask[2].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[2].tQTaskRefList.ptTail = nullptr;
  ptQTask[2].ptParent = (struct QTask_s *)1065353216;
  *(_DWORD *)&ptQTask[2].eQTaskType = 0;
  ptQTask[3].ptNext = nullptr;
  ptQTask[3].ptPrev = nullptr;
  ptQTask[3].tQTaskChildren.ptHead = (struct QTask_s *)1065353216;
  ptQTask[3].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[3].tQTaskChildren.ptTail = nullptr;
  ptQTask[3].tQTaskRefList.ptHead = nullptr;
  ptQTask[3].tQTaskRefList.ptMiddle = (struct QReference_s *)1065353216;
  ptQTask[3].tQTaskRefList.ptTail = nullptr;
  v3 = (int)ptNetManagerQTask[4].ptParent <= 0;
  NetMission_ptNetMission = (struct NetMission_t *)ptQTask;
  if ( v3 )
  {
    NetMission_isWarmUp = false;
  }
  else
  {
    v4 = NetMission_isWarmUp == false;
    NetMission_isWarmUp = v4;
    if ( v4 )
      ptQTask[1].tQTaskChildren.ptHead = (struct QTask_s *)(1000 * (int)ptNetManagerQTask[4].ptParent
                                                          + NetManager_GetTimer());
  }
}

// source: j/0/network/netmission.c:201  [anchor-caller]
void __cdecl NetMission_WarmupChangedFromCommand()
{
  struct QTask_s *ptNetManagerQTask; // esi
  int v1; // [esp-4h] [ebp-8h]

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  if ( !ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    ptNetManagerQTask[4].ptParent = (struct QTask_s *)ServerConfig_tServerConfig.nPloss;
    NetManager_SendScoreUpdate();
    if ( (int)ptNetManagerQTask[4].ptParent <= 0 )
    {
      if ( NetMission_isWarmUp )
        NetManager_InitiateRestart();
    }
    else if ( NetMission_isWarmUp )
    {
      v1 = 1000 * (int)ptNetManagerQTask[4].ptParent + NetManager_GetTimer();
      NetMission_ptNetMission->nWarmupEndTime = v1;
      NetMission_EvaluateWarmUp(v1);
    }
  }
}

// source: j/0/network/netmission.c:250  [anchor-strings]
void __cdecl NetObjective_DisplayCompleteState(
        int eAttackingTeam,
        enum bool isComplete,
        int nNumber)
{
  struct QTask_s *v3; // esi
  int ptTail; // eax
  char zText[200]; // [esp+4h] [ebp-C8h] BYREF

  v3 = StatusScreen_ptStatusScreenQTask;
  strcpy(zText, "-");
  if ( HumanPlayer_ptQTask )
    ptTail = (int)HumanPlayer_ptQTask[10].tQTaskRefList.ptTail;
  else
    ptTail = -1;
  if ( isComplete == false )
  {
    if ( eAttackingTeam )
    {
      if ( eAttackingTeam == 1 )
      {
        if ( ptTail == 1 )
        {
          _snprintf(zText, 0xC8u, "IGI WON OBJECTIVE #%d: YOUR ATTACK FAILED", nNumber);
          v3[49].ptNext = (struct QTask_s *)300;
          return;
        }
        if ( !ptTail )
        {
          _snprintf(zText, 0xC8u, "IGI WON OBJECTIVE #%d: YOUR DEFENCE SUCCEEDED", nNumber);
          goto LABEL_17;
        }
        NetManager_LogMessage("IGI won objective\n");
      }
    }
    else
    {
      if ( !ptTail )
      {
        _snprintf(zText, 0xC8u, "CONSPIRACY WON OBJECTIVE #%d: YOUR ATTACK FAILED", nNumber);
LABEL_17:
        v3[49].ptNext = (struct QTask_s *)300;
        return;
      }
      if ( ptTail == 1 )
      {
        _snprintf(zText, 0xC8u, "CONSPIRACY WON OBJECTIVE #%d: YOUR DEFENCE SUCCEEDED", nNumber);
        v3[49].ptNext = (struct QTask_s *)300;
        return;
      }
      NetManager_LogMessage("Conspiracy won objective\n");
    }
    v3[49].ptNext = (struct QTask_s *)300;
    return;
  }
  if ( eAttackingTeam )
  {
    if ( eAttackingTeam == 1 )
    {
      if ( ptTail == 1 )
      {
        _snprintf(zText, 0xC8u, "CONSPIRACY WON OBJECTIVE #%d: YOUR ATTACK SUCCEEDED", nNumber);
        v3[49].ptNext = (struct QTask_s *)150;
        return;
      }
      if ( !ptTail )
      {
        _snprintf(zText, 0xC8u, "CONSPIRACY WON OBJECTIVE #%d: YOUR DEFENCE FAILED", nNumber);
        goto LABEL_22;
      }
      NetManager_LogMessage("Conspiracy won objective\n");
    }
  }
  else
  {
    if ( !ptTail )
    {
      _snprintf(zText, 0xC8u, "IGI WON OBJECTIVE #%d: YOUR ATTACK SUCCEEDED", nNumber);
LABEL_22:
      v3[49].ptNext = (struct QTask_s *)150;
      return;
    }
    if ( ptTail == 1 )
    {
      _snprintf(zText, 0xC8u, "IGI WON OBJECTIVE #%d: YOUR DEFENCE FAILED", nNumber);
      v3[49].ptNext = (struct QTask_s *)150;
      return;
    }
    NetManager_LogMessage("IGI won objective\n");
  }
  v3[49].ptNext = (struct QTask_s *)150;
}

// source: j/0/network/netmission.c:375  [anchor-caller]
void __cdecl NetObjective_RunHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v16; };
    struct { char igi2_o1[4]; unsigned int v17; };
    struct { char igi2_o2[12]; struct QReference_s *ptTail; };
    struct { char igi2_o3[16]; struct QTask_s *ptParent; };
    struct { char igi2_o4[20]; struct NetManagerGameMessage_s ptGameMessage; };
    struct { char igi2_o5[28]; int v21; };
    struct { char igi2_o6[32]; int v22; };
    struct { char igi2_o7[36]; int v23; };
    struct { char igi2_o8[40]; struct QTask_s *v24; };
    char igi2_extent[44];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptPrev; // ebx
  struct QTask_s *v2; // edi
  int NumberOfTeamClients; // eax
  unsigned int RandomNumberBelowLimit; // eax
  struct QTask_s *v5; // ebx
  unsigned __int16 v6; // dx
  struct QTask_s *v7; // eax
  struct QTask_s *ptHead; // ecx
  struct QTask_s *ptNext; // edi
  struct Client_s *i; // edi
  struct QReference_s *v11; // eax
  struct QTask_s *v12; // edi
  int LevelQTaskIDFromQTask; // eax
  char v14; // dl
  struct QTask_s *v15; // eax

  igi2_frame.ptTail = ptQTask[5].tQTaskRefList.ptTail;
  igi2_frame.ptParent = ptQTask[5].ptParent;
  if ( !Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle
    && ptQTask[5].ptNext == (struct QTask_s *)NetMission_eCurrentObjective )
  {
    if ( ptQTask[5].tQTaskRefList.ptHead )
    {
      if ( !ptQTask[5].tQTaskRefList.ptMiddle )
      {
        ptPrev = ptQTask[5].ptPrev;
        if ( TeamManager_GetNumberOfTeamClients((int)ptPrev) )
        {
          if ( NetMission_isWarmUp == false )
          {
            v2 = nullptr;
            igi2_frame.v16 = 0;
            NumberOfTeamClients = TeamManager_GetNumberOfTeamClients((int)ptPrev);
            RandomNumberBelowLimit = Random_GetRandomNumberBelowLimit(
                                       &Game_ptGame->tRunRandomState,
                                       NumberOfTeamClients);
            v5 = HumanPlayer_ptQTask;
            v6 = Client_eQTaskType;
            igi2_frame.v17 = RandomNumberBelowLimit;
            while ( 1 )
            {
              v7 = v2
                 ? QTask_GetNextSiblingOfType(v2, v6)
                 : QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, v6);
              v2 = v7;
              if ( !v7 )
                break;
              if ( v7[1].tQTaskRefList.ptHead == (struct QReference_s *)ptQTask[5].ptPrev )
              {
                if ( igi2_frame.v16 == igi2_frame.v17 )
                {
                  ptHead = v7[16].tQTaskChildren.ptHead->tQTaskChildren.ptHead;
                  if ( !LOBYTE(ptHead[29].tQTaskRefList.ptHead)
                    && (v5 != ptHead || NetManager_eMode == NETMANAGER_MODE_PLAY) )
                  {
                    ptNext = v7[1].ptNext;
                    if ( ptNext != (struct QTask_s *)-1 )
                    {
                      igi2_frame.ptGameMessage.eGameMessage = 1162958153;
                      igi2_frame.ptGameMessage.nLocalTime = Timer_Read();
                      igi2_frame.v24 = ptNext;
                      LOBYTE(igi2_frame.v21) = 0;
                      igi2_frame.v22 = Script_ParseLineInt32("WEAPON_ID_C4BOMB");
                      igi2_frame.v23 = 2;
                      for ( i = NetManager_GetNextClient(nullptr); i; i = NetManager_GetNextClient(i) )
                        NetManager_SendGameMessage(
                          i->eNetworkID,
                          (int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle,
                          NETWORKQUEUE_GUARANTEED,
                          &igi2_frame.ptGameMessage,
                          0x18u);
                      if ( AppContext_tAppContext.isServer )
                        NetManager_SendGameMessage(
                          0,
                          (int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle,
                          NETWORKQUEUE_GUARANTEED,
                          &igi2_frame.ptGameMessage,
                          0x18u);
                      ptQTask[5].tQTaskRefList.ptMiddle = (struct QReference_s *)1;
                    }
                    break;
                  }
                }
                ++igi2_frame.v16;
              }
            }
          }
        }
      }
    }
    if ( ptQTask[1].ptNext && ptQTask[1].ptPrev->ptNext && ptQTask[1].tQTaskChildren.ptHead )
      ptQTask[5].tQTaskRefList.ptTail = (struct QReference_s *)((int)ptQTask[5].tQTaskRefList.ptTail
                                                              | (char)(__int64)Level_RunLevelExpression(
                                                                                 (struct LevelExpression_s *)&ptQTask[1],
                                                                                 ptQTask));
    if ( ptQTask[3].ptNext && ptQTask[3].ptPrev->ptNext && ptQTask[3].tQTaskChildren.ptHead )
      ptQTask[5].ptParent = (struct QTask_s *)((int)ptQTask[5].ptParent
                                             | (char)(__int64)Level_RunLevelExpression(
                                                                (struct LevelExpression_s *)&ptQTask[3],
                                                                ptQTask));
    v11 = ptQTask[5].tQTaskRefList.ptTail;
    if ( v11 && !igi2_frame.ptTail && !ptQTask[5].ptParent || ptQTask[5].ptParent && !igi2_frame.ptParent && !v11 )
    {
      if ( v11 )
      {
        v12 = ptQTask[5].tQTaskChildren.ptTail;
        if ( NetManager_GetClientFromNetworkID((int)v12) )
          Netshop_AddMoneyToClient((int)v12, ServerConfig_tServerConfig.nMoneyObjectiveTeamWin);
        Netshop_AddMoneyToTeam(ServerConfig_tServerConfig.nMoneyObjectiveTeamLost, (int)ptQTask[5].ptPrev);
        if ( NetMission_eCurrentObjective != 3 )
          RadioCom_AutoTransmit(
            (int)ptQTask[5].ptPrev,
            RADIOCOM_AUTOMATIC_OBJECTIVE,
            -1,
            (int)ptQTask[5].tQTaskChildren.ptTail);
        if ( !ptQTask[5].ptPrev )
          Netshop_AddMoneyToTeam(ServerConfig_tServerConfig.nMoneyMissionWin, 1);
        if ( ptQTask[5].ptPrev == (struct QTask_s *)1 )
          Netshop_AddMoneyToTeam(ServerConfig_tServerConfig.nMoneyMissionWin, 0);
      }
      if ( ptQTask[5].ptParent )
      {
        Netshop_AddMoneyToTeam(ServerConfig_tServerConfig.nMoneyMissionWin, (int)ptQTask[5].ptPrev);
        if ( !ptQTask[5].ptPrev )
        {
          if ( NetMission_eCurrentObjective != 3 )
            RadioCom_AutoTransmit(1, RADIOCOM_AUTOMATIC_OBJECTIVE, -1, (int)ptQTask[5].tQTaskChildren.ptTail);
          Netshop_AddMoneyToTeam(ServerConfig_tServerConfig.nMoneyObjectiveTeamLost, 1);
        }
        if ( ptQTask[5].ptPrev == (struct QTask_s *)1 )
        {
          if ( NetMission_eCurrentObjective != 3 )
            RadioCom_AutoTransmit(0, RADIOCOM_AUTOMATIC_OBJECTIVE, -1, (int)ptQTask[5].tQTaskChildren.ptTail);
          Netshop_AddMoneyToTeam(ServerConfig_tServerConfig.nMoneyObjectiveTeamLost, 0);
        }
      }
      NetMission_SetObjectiveComplete(
        ptQTask,
        (char)ptQTask[5].tQTaskRefList.ptTail,
        (int)ptQTask[5].tQTaskChildren.ptTail);
      NetObjective_DisplayCompleteState(
        (int)ptQTask[5].ptPrev,
        (enum bool)ptQTask[5].tQTaskRefList.ptTail,
        (int)ptQTask[5].ptNext);
      igi2_frame.ptGameMessage.eGameMessage = 1329744468;
      igi2_frame.ptGameMessage.nLocalTime = NetManager_GetTimer();
      LevelQTaskIDFromQTask = Level_GetLevelQTaskIDFromQTask(ptQTask);
      v14 = (char)ptQTask[5].tQTaskRefList.ptTail;
      igi2_frame.v21 = LevelQTaskIDFromQTask;
      v15 = ptQTask[5].tQTaskChildren.ptTail;
      LOBYTE(igi2_frame.v22) = v14;
      igi2_frame.v23 = (int)v15;
      NetManager_SendGameMessage(0, 0, NETWORKQUEUE_GUARANTEED, &igi2_frame.ptGameMessage, 0x14u);
    }
  }
}

// source: j/0/network/netmission.c:575  [anchor-caller]
void __cdecl NetMission_RunHandler(struct QTask_s *ptQTask)
{
  unsigned __int16 v1; // dx
  struct QTask_s *FirstChildOfType; // eax
  int v3; // esi
  struct QTask_s *ptNetManagerQTask; // esi
  struct QTask_s *v5; // ebx
  struct Client_s *ClientFromNetworkID; // edi
  DWORD PerformanceCounter; // eax
  int v8; // ecx
  struct NetMission_t *v9; // eax
  struct Flow_t *v10; // eax
  enum NetManagerMode_e v11; // esi
  char *LocalizedStringForLanguage; // eax
  struct Client_s *v13; // eax
  struct QTask_s *v14; // esi
  char *v15; // eax
  struct QTask_s *ptMiddle; // eax
  struct QTask_s *v17; // eax
  struct Mission_s *NextMap; // eax
  unsigned __int16 v19; // si
  struct QTask_s *NextSiblingOfType; // eax
  int ptPrev; // edi
  struct QTask_s *ptHead; // ebx
  int v23; // eax
  int v24; // edx
  struct QTask_s *v25; // ecx
  int v26; // [esp+Ch] [ebp-Ch]
  int v27; // [esp+Ch] [ebp-Ch]
  BOOL eTeam; // [esp+10h] [ebp-8h]
  struct QTask_s *v29; // [esp+14h] [ebp-4h]

  v1 = NetObjective_eQTaskType;
  FirstChildOfType = QTask_GetFirstChildOfType(&NetMission_ptNetMission->tQTask, NetObjective_eQTaskType);
  if ( FirstChildOfType )
  {
    v3 = NetMission_eCurrentObjective;
    while ( FirstChildOfType[5].ptNext != (struct QTask_s *)v3 )
    {
      FirstChildOfType = QTask_GetNextSiblingOfType(FirstChildOfType, v1);
      if ( !FirstChildOfType )
        goto LABEL_5;
    }
    v29 = FirstChildOfType;
  }
  else
  {
LABEL_5:
    v29 = nullptr;
  }
  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  v5 = ptQTask;
  ClientFromNetworkID = NetManager_GetClientFromNetworkID((int)ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
  if ( !ptQTask[1].tQTaskChildren.ptTail )
  {
    if ( Timer_isPerformanceCounter )
      PerformanceCounter = Timer_GetPerformanceCounter();
    else
      PerformanceCounter = GetTickCount();
    v8 = (int)ptNetManagerQTask[6].tQTaskRefList.ptMiddle
       + 60000 * (int)ptNetManagerQTask[4].tQTaskRefList.ptMiddle
       - (unsigned int)ptNetManagerQTask[6].tQTaskRefList.ptTail
       + PerformanceCounter
       - Timer_nStartTime;
    v9 = NetMission_ptNetMission;
    NetMission_ptNetMission->nMissionEndTime = v8;
    v9->isStarted = true;
  }
  if ( ptQTask[3].ptParent
    && **(_BYTE **)&ptQTask[3].eQTaskType
    && ptQTask[4].ptNext
    && Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[3].ptParent, ptQTask) != 0.0 )
  {
    NetManager_KillClient(ClientFromNetworkID->eNetworkID);
  }
  if ( ptQTask[1].ptPrev
    && NetMission_GetMissionTimer() <= 0
    && !ptQTask[1].tQTaskChildren.ptMiddle
    && !C4BombArea_SoundUpdateParameterListHandler() )
  {
    NetMission_eCurrentObjective = 0;
    v10 = Flow_ptFlow;
    *(_DWORD *)&ptNetManagerQTask[35].eQTaskType = 150;
    if ( !v10->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
      MapControl_ServerRoundComplete();
    ptQTask[1].tQTaskChildren.ptMiddle = (struct QTask_s *)600;
  }
  if ( MapControl_isChangeMapNow() )
  {
    v11 = NETMANAGER_MODE_COMPLETE;
    if ( NetManager_eMode != NETMANAGER_MODE_COMPLETE )
    {
      v26 = 9;
      if ( BYTE2(Flow_ptFlow->ptNetManagerQTask[5].tQTaskChildren.ptTail) && NetManager_ForceChangeTeam() )
      {
        LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                       "mp/FORCE_TEAM_CHANGE",
                                       Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                       true);
        StatusScreen_ShowMessage(LocalizedStringForLanguage, TEXTSCROLLER_COLOUR_WHITE);
        v26 = 1;
        NetManager_nBodySprite = 0;
        NetManager_nFaceSprite = 0;
        NetManager_isModelSelect = true;
        v11 = NETMANAGER_MODE_SELECTSKIN;
      }
      v13 = NetManager_GetClientFromNetworkID((int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
      if ( v13 )
        NetManager_eTeam = v13->eTeam;
      NetManager_eMode = v11;
      v14 = MenuManager_ptQTask;
      LOBYTE(MenuManager_ptQTask[243].eQTaskType) = 1;
      switch ( v26 )
      {
        case 1:
          if ( !LOBYTE(HumanPlayer_ptQTask[29].tQTaskRefList.ptHead) )
          {
            NetManager_KillClient((int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
            v14 = MenuManager_ptQTask;
          }
          v14[1].ptNext = (struct QTask_s *)996;
          v14[1].tQTaskChildren.ptMiddle = nullptr;
          break;
        default:
          break;
      }
    }
  }
  if ( ptQTask[2].ptNext && ClientFromNetworkID && ClientFromNetworkID->eTeam == NetMission_eDefendingTeam )
  {
    QTask_Delete(ptQTask[2].ptNext);
    ptQTask[2].ptNext = nullptr;
  }
  if ( v29
    && ClientFromNetworkID
    && ClientFromNetworkID->eTeam == NetMission_eAttackingTeam
    && *(_DWORD *)&ptQTask[1].eQTaskType
    && !ptQTask[2].ptNext )
  {
    ptQTask[2].ptNext = QTask_NewFn(ptQTask, ComputerHilight_eQTaskType, nullptr);
    v15 = (char *)Mem_AllocFn(255, 4);
    strcpy(v15, ComputerMenu_tComputerMenuResource.azQSpriteHilight[19]);
    ComputerHilight_SetSprite(ptQTask[2].ptNext, v15);
  }
  if ( !Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    ptMiddle = ptQTask[1].tQTaskChildren.ptMiddle;
    if ( (int)ptMiddle <= 0 )
    {
      if ( MapControl_isChangeMapNow() )
      {
        ptQTask[1].tQTaskChildren.ptMiddle = (struct QTask_s *)600;
        ptQTask[1].tQTaskRefList.ptMiddle = (struct QReference_s *)1;
        NetMission_eCurrentObjective = 0;
      }
    }
    else
    {
      v17 = (struct QTask_s *)((char *)ptMiddle - 1);
      ptQTask[1].tQTaskChildren.ptMiddle = v17;
      if ( !v17 )
      {
        if ( MapControl_isChangeMapNow() )
        {
          NextMap = NetManager_GetNextMap();
          NetManager_InitiateChangeMap(NextMap->iID);
        }
        else
        {
          NetManager_InitiateRestart();
        }
        return;
      }
    }
    if ( NetMission_isWarmUp && NetManager_GetTimer() > (int)ptQTask[1].tQTaskChildren.ptHead )
      NetManager_InitiateRestart();
    if ( !NetMission_eCurrentObjective
      && !ptQTask[1].tQTaskRefList.ptHead
      && !ptQTask[1].tQTaskRefList.ptMiddle
      && !ptQTask[1].tQTaskRefList.ptTail )
    {
      v27 = 0;
      v19 = NetObjective_eQTaskType;
      NextSiblingOfType = QTask_GetFirstChildOfType(ptQTask, NetObjective_eQTaskType);
      ptPrev = (int)NextSiblingOfType[5].ptPrev;
      eTeam = ptPrev == 0;
      do
      {
        if ( !NextSiblingOfType[5].tQTaskRefList.ptTail )
          ++v27;
        NextSiblingOfType = QTask_GetNextSiblingOfType(NextSiblingOfType, v19);
      }
      while ( NextSiblingOfType );
      if ( v27 )
      {
        Netshop_AddMoneyToTeam(ServerConfig_tServerConfig.nMapMaxRounds, ptPrev);
        Netshop_AddMoneyToTeam(ServerConfig_tServerConfig.nMoneyMissionLost, eTeam);
        TeamManager_AddScore(1, eTeam);
        ptQTask[1].tQTaskRefList.ptHead = (struct QReference_s *)1;
        RadioCom_AutoTransmit(eTeam, RADIOCOM_AUTOMATIC_MISSION, -1, 0);
      }
      else
      {
        Netshop_AddMoneyToTeam(ServerConfig_tServerConfig.nMoneyMissionLost, ptPrev);
        Netshop_AddMoneyToTeam(ServerConfig_tServerConfig.nMapMaxRounds, eTeam);
        TeamManager_AddScore(1, ptPrev);
        ptQTask[1].tQTaskRefList.ptMiddle = (struct QReference_s *)1;
        RadioCom_AutoTransmit(ptPrev, RADIOCOM_AUTOMATIC_MISSION, -1, 0);
      }
      v5 = ptQTask;
    }
    ptHead = v5->tQTaskChildren.ptHead;
    if ( ptHead->ptNext )
    {
      v23 = (int)ptHead;
      if ( ptHead )
      {
        v24 = QTask_nProtectedQTaskStackOffset;
        do
        {
          if ( *(_DWORD *)v23 )
            v25 = **(_DWORD **)v23 != 0 ? *(struct QTask_s **)v23 : nullptr;
          else
            v25 = nullptr;
          QTask_atProtectedQTaskStack[v24].ptQTask = v25;
          QTask_nProtectedQTaskStackOffset = v24 + 1;
          ((void (__cdecl *)(int))QTask_aatQTaskFinalEvent[1][*(unsigned __int16 *)(v23 + 36)].pfHandler)(v23);
          v23 = dword_849C7DC[QTask_nProtectedQTaskStackOffset];
          v24 = --QTask_nProtectedQTaskStackOffset;
        }
        while ( v23 );
      }
    }
  }
}

// source: j/0/network/netmission.c:795  [anchor-mhash]
void __cdecl NetObjective_DeleteHandler(struct QTask_s *ptQTask)
{
  int v1; // ecx
  struct QReference_s *v2; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax

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
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[1]);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[3]);
}

// source: j/0/network/netmission.c:821  [anchor-mhash]
void __cdecl NetMission_DeleteHandler(struct QTask_s *ptQTask)
{
  int v1; // ecx
  struct QReference_s *v2; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax

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
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[3].ptParent);
  NetMission_ptNetMission = nullptr;
}

// source: j/0/network/netmission.c:847  [size]
void __cdecl NetObjective_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = NetObjective_ptParameterList;
}

// source: j/0/network/netmission.c:863  [size]
void __cdecl NetMission_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = NetMission_ptParameterList;
}

// source: j/0/network/netmission.c:908  [anchor-mhash]
void __cdecl NetObjective_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  if ( ptQTask[5].ptNext == (struct QTask_s *)1 )
  {
    NetMission_eAttackingTeam = (int)ptQTask[5].ptPrev;
    NetMission_eDefendingTeam = NetMission_eAttackingTeam == 0;
  }
  NetMission_ptNetMission->isBombObjective |= (enum bool)ptQTask[5].tQTaskRefList.ptHead;
  if ( !Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[1], ptQTask);
    Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[3], ptQTask);
  }
}

// source: j/0/network/netmission.c:955  [size]
void __cdecl NetMission_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[3].ptParent, ptQTask);
}

// source: j/0/network/netmission.c:972  [size]
void __cdecl NetObjective_RegisterScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( !*(_DWORD *)&ptQTask[5].eQTaskType )
  {
    *(_DWORD *)&ptQTask[5].eQTaskType = 1;
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.isObjectiveComplete", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Bool,
      &ptQTask[5].tQTaskRefList.ptTail,
      4,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.isObjectiveFailed", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Bool,
      &ptQTask[5].ptParent,
      4,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
  }
}

// source: j/0/network/netmission.c:1004  [size]
void __cdecl NetObjective_RemoveScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( *(_DWORD *)&ptQTask[5].eQTaskType )
  {
    *(_DWORD *)&ptQTask[5].eQTaskType = 0;
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.isObjectiveComplete", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.isObjectiveFailed", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
  }
}

// source: j/0/network/netmission.c:1036  [size]
void __cdecl NetMission_RegisterScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( !ptQTask[1].ptParent )
  {
    ptQTask[1].ptParent = (struct QTask_s *)1;
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.isMissionComplete", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Bool,
      &ptQTask[1].tQTaskRefList,
      4,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.isMissionFailed", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Bool,
      &ptQTask[1].tQTaskRefList.ptMiddle,
      4,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
  }
}

// source: j/0/network/netmission.c:1068  [size]
void __cdecl NetMission_RemoveScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( ptQTask[1].ptParent )
  {
    ptQTask[1].ptParent = nullptr;
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.isMissionComplete", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.isMissionFailed", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
  }
}

// source: j/0/network/netmission.c:1100  [anchor-mhash]
struct Result_s *__cdecl NetObjective_NotifyWhoDidItCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // ebx
  struct ArgList_s *v5; // esi
  unsigned __int16 v6; // dx
  struct QTask_s *FirstChildOfType; // eax
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
  if ( v3->isQVM )
  {
    ptArgList = nullptr;
    QVM_EvalArg(&ptArgList, 4, v3, 1, 1);
    v5 = ptArgList;
  }
  else
  {
    v5 = (struct ArgList_s *)Expression_EvalInt(v3->aptExpression[1]);
  }
  v6 = NetObjective_eQTaskType;
  FirstChildOfType = QTask_GetFirstChildOfType(&NetMission_ptNetMission->tQTask, NetObjective_eQTaskType);
  if ( FirstChildOfType )
  {
    while ( (struct ArgList_s *)FirstChildOfType[5].ptNext != v4 )
    {
      FirstChildOfType = QTask_GetNextSiblingOfType(FirstChildOfType, v6);
      if ( !FirstChildOfType )
        goto LABEL_10;
    }
  }
  else
  {
LABEL_10:
    FirstChildOfType = nullptr;
  }
  FirstChildOfType[5].tQTaskChildren.ptTail = (struct QTask_s *)v5;
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/netmission.c:1127  [anchor-hash]
void __cdecl NetMission_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si
  struct ParameterList_s *v2; // eax
  int v3; // edx
  unsigned __int16 v4; // ax
  unsigned __int16 v5; // si
  struct ParameterList_s *v6; // eax
  int v7; // edx

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("Network_Mission", 232, BaseQTaskType, 1, 0);
  NetMission_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(
    v1,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 0, NetMission_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, NetMission_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, NetMission_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))NetMission_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v1, ParameterList_eUpdateInternalDataQTaskEvent, NetMission_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v1,
    Level_eRegisterLevelScriptSymbolsEvent,
    NetMission_RegisterScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v1,
    Level_eRemoveLevelScriptSymbolsEvent,
    NetMission_RemoveScriptSymbolsHandler);
  v2 = (struct ParameterList_s *)Mem_AllocFn(72, 4);
  v3 = Level_eParameterTypeObjectPos;
  v2->ptParameterListItem = (struct ParameterListItem_s *)&v2[1];
  v2->nParameters = 0;
  v2->nMaxParameters = 3;
  NetMission_ptParameterList = v2;
  ParameterList_AddParameter(v2, 0x58u, v3, "Start Camera Position", 7u, nullptr);
  ParameterList_AddParameter(
    NetMission_ptParameterList,
    0x70u,
    Level_eParameterTypeReal32x9,
    "Start Camera Orientation",
    7u,
    nullptr);
  ParameterList_AddParameter(
    NetMission_ptParameterList,
    0x98u,
    Level_eParameterTypeVarString,
    "Mission Violated Expression",
    7u,
    nullptr);
  v4 = QTask_GetBaseQTaskType();
  v5 = QTask_NewQTaskType("Network_Objective", 240, v4, 1, 0);
  NetObjective_eQTaskType = v5;
  QTask_LinkQTaskEventHandlerFn(
    v5,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v5, 0, NetObjective_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v5, 1, NetObjective_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v5, 2, NetObjective_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v5,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))NetObjective_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v5, ParameterList_eUpdateInternalDataQTaskEvent, NetObjective_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v5,
    Level_eRegisterLevelScriptSymbolsEvent,
    NetObjective_RegisterScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v5,
    Level_eRemoveLevelScriptSymbolsEvent,
    NetObjective_RemoveScriptSymbolsHandler);
  v6 = (struct ParameterList_s *)Mem_AllocFn(132, 4);
  v6->ptParameterListItem = (struct ParameterListItem_s *)&v6[1];
  v7 = Level_eParameterTypeVarString;
  v6->nParameters = 0;
  v6->nMaxParameters = 6;
  NetObjective_ptParameterList = v6;
  ParameterList_AddParameter(v6, 0x28u, v7, "Objective Expression", 7u, nullptr);
  ParameterList_AddParameter(
    NetObjective_ptParameterList,
    0x78u,
    Level_eParameterTypeVarString,
    "Objective Failed Expression",
    7u,
    nullptr);
  ParameterList_AddParameter(
    NetObjective_ptParameterList,
    0xC8u,
    Level_eParameterTypeInt32,
    "Order number for objective",
    7u,
    nullptr);
  ParameterList_AddParameter(
    NetObjective_ptParameterList,
    0xCCu,
    Level_eParameterTypeInt32,
    "Team this objective is for",
    7u,
    nullptr);
  ParameterList_AddParameter(
    NetObjective_ptParameterList,
    0xD0u,
    Level_eParameterTypeInt32,
    "Time for objective",
    7u,
    nullptr);
  ParameterList_AddParameter(
    NetObjective_ptParameterList,
    0xDCu,
    Level_eParameterTypebool8,
    "Is the c4 bomb required for this objective",
    7u,
    nullptr);
  Symbol_Register(
    "NetMission_eCurrentObjective",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int,
    &NetMission_eCurrentObjective,
    4,
    QSCRIPT_SYMBOLCLASS_VARIABLE,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_FINITE);
  Symbol_Register(
    "NetObjective_NotifyWhoDidIt",
    NetObjective_NotifyWhoDidItCB,
    nullptr,
    2,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}

// source: j/0/network/netmission.c:1193  [size]
void __cdecl NetMission_Close()
{
  int v0; // esi
  int v1; // esi

  QTask_DeleteQTaskType(NetObjective_eQTaskType);
  QTask_DeleteQTaskType(NetMission_eQTaskType);
  if ( NetObjective_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&NetObjective_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  if ( NetMission_ptParameterList )
  {
    v1 = *(_DWORD *)((unsigned int)&NetMission_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
}

// source: j/0/network/netmission.c:1211  [size]
unsigned __int16 __cdecl NetObjective_GetQTaskType()
{
  return NetObjective_eQTaskType;
}

// source: j/0/network/netmission.c:1224  [size]
unsigned __int16 __cdecl NetMission_GetQTaskType()
{
  return NetMission_eQTaskType;
}

// source: j/0/network/netmission.c:1237  [size]
void __cdecl NetMission_SetObjectiveEndTime(int nTime)
{
  NetMission_ptNetMission->nObjectiveEndTime = nTime;
}

// source: j/0/network/netmission.c:1250  [size]
void __cdecl NetMission_SetMissionEndTime(int nTime)
{
  struct NetMission_t *v1; // eax

  v1 = NetMission_ptNetMission;
  NetMission_ptNetMission->nMissionEndTime = nTime;
  v1->isStarted = true;
}

// source: j/0/network/netmission.c:1264  [anchor-callee]
struct QTask_s *__cdecl NetMission_SetObjectiveComplete(
        struct QTask_s *ptQTask,
        char isComplete,
        int nWhoDidItClientID)
{
  struct Flow_t *v3; // ebx
  struct QTask_s *ptNetManagerQTask; // ebp
  struct Client_s *ClientFromNetworkID; // eax
  struct NetMission_t *v7; // edi
  unsigned __int16 v8; // dx
  struct QTask_s *FirstChildOfType; // eax
  int v10; // esi
  struct QTask_s *result; // eax

  v3 = Flow_ptFlow;
  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  ClientFromNetworkID = NetManager_GetClientFromNetworkID(nWhoDidItClientID);
  if ( isComplete )
    ptQTask[5].tQTaskRefList.ptTail = (struct QReference_s *)1;
  else
    ptQTask[5].ptParent = (struct QTask_s *)1;
  if ( ClientFromNetworkID )
    ++ClientFromNetworkID->nTalkOffset;
  v7 = NetMission_ptNetMission;
  v8 = NetObjective_eQTaskType;
  FirstChildOfType = QTask_GetFirstChildOfType(&NetMission_ptNetMission->tQTask, NetObjective_eQTaskType);
  v10 = NetMission_eCurrentObjective + 1;
  if ( FirstChildOfType[5].ptNext == (struct QTask_s *)(NetMission_eCurrentObjective + 1) )
  {
LABEL_9:
    NetMission_eCurrentObjective = (int)FirstChildOfType[5].ptNext;
    NetMission_eAttackingTeam = (int)FirstChildOfType[5].ptPrev;
    NetMission_eDefendingTeam = NetMission_eAttackingTeam == 0;
    result = QTask_GetFirstChildOfType(FirstChildOfType, SpawnArea_eQTaskType);
    ptNetManagerQTask[8].ptParent = (struct QTask_s *)1;
    SpawnArea_ptActive = result;
  }
  else
  {
    while ( 1 )
    {
      FirstChildOfType = QTask_GetNextSiblingOfType(FirstChildOfType, v8);
      if ( !FirstChildOfType )
        break;
      if ( FirstChildOfType[5].ptNext == (struct QTask_s *)v10 )
        goto LABEL_9;
    }
    NetMission_eCurrentObjective = 0;
    *(_DWORD *)&ptNetManagerQTask[35].eQTaskType = 240;
    v7->nRestartTimer = 600;
    result = v3->ptNetManagerQTask;
    if ( !result[6].tQTaskChildren.ptMiddle )
    {
      result = QTask_GetFirstChildOfType(result, MapControl_eQTaskType);
      ++*(int *)&result[1].tQTaskChildren.ptMiddle;
    }
  }
  return result;
}

// source: j/0/network/netmission.c:1366  [anchor-callee]
int __cdecl NetMission_GetMissionTimer()
{
  struct QTask_s *ptNetManagerQTask; // esi
  DWORD PerformanceCounter; // eax
  struct QTask_s *v2; // esi
  DWORD TickCount; // eax
  int v4; // ecx

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  if ( (int)((int)ptNetManagerQTask[6].tQTaskRefList.ptTail
           + NetMission_ptNetMission->nMissionEndTime
           - (unsigned int)ptNetManagerQTask[6].tQTaskRefList.ptMiddle
           - (PerformanceCounter
            - Timer_nStartTime)) <= 0 )
  {
    v4 = 0;
  }
  else
  {
    v2 = Flow_ptFlow->ptNetManagerQTask;
    if ( Timer_isPerformanceCounter )
      TickCount = Timer_GetPerformanceCounter();
    else
      TickCount = GetTickCount();
    v4 = (int)v2[6].tQTaskRefList.ptTail
       + NetMission_ptNetMission->nMissionEndTime
       - (unsigned int)v2[6].tQTaskRefList.ptMiddle
       - (TickCount
        - Timer_nStartTime);
  }
  return v4 / 1000;
}

// source: j/0/network/netmission.c:1379  [size]
int __cdecl NetMission_GetObjectiveEndTime()
{
  return NetMission_ptNetMission->nObjectiveEndTime;
}

// source: j/0/network/netmission.c:1392  [size]
int __cdecl NetMission_GetMissionEndTime()
{
  return NetMission_ptNetMission->nMissionEndTime;
}

// source: j/0/network/netmission.c:1406  [size]
enum bool __cdecl NetMission_IsMission()
{
  return NetMission_ptNetMission != nullptr;
}

// source: j/0/network/netmission.c:1420  [size]
int __cdecl NetMission_GetCurrentObjective()
{
  return NetMission_eCurrentObjective;
}

// source: j/0/network/netmission.c:1433  [size]
int __cdecl NetMission_SetCurrentObjective(int nNumber)
{
  NetMission_eCurrentObjective = nNumber;
  return nNumber;
}

// source: j/0/network/netmission.c:1446  [size]
int __cdecl NetMission_GetDefendingTeam()
{
  return NetMission_eDefendingTeam;
}

// source: j/0/network/netmission.c:1459  [size]
int __cdecl NetMission_GetAttackingTeam()
{
  return NetMission_eAttackingTeam;
}

// source: j/0/network/netmission.c:1472  [anchor-callee]
void __cdecl NetMission_Restart()
{
  struct QTask_s *v0; // ebp
  unsigned __int16 v1; // dx
  struct QTask_s *v2; // eax
  struct QTask_s *ptHead; // ebx
  struct QTask_s *ptNext; // esi
  struct QTask_s *ptTail; // eax
  struct QTask_s *v6; // ecx
  struct QTask_s *v7; // edi
  struct Client_s *ClientFromNetworkID; // eax
  struct QTask_s *v9; // [esp+14h] [ebp-8h]
  struct QTask_s *ptNetManagerQTask; // [esp+18h] [ebp-4h]

  v9 = HumanPlayer_ptQTask;
  v0 = nullptr;
  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  NetMission_eObjectiveNumber = 1;
  NetMission_eCurrentObjective = 1;
LABEL_2:
  v1 = Client_eQTaskType;
LABEL_3:
  while ( 1 )
  {
    v2 = v0 ? QTask_GetNextSiblingOfType(v0, v1) : QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, v1);
    v0 = v2;
    if ( !v2 )
      break;
    ptHead = v2[16].tQTaskChildren.ptHead->tQTaskChildren.ptHead;
    ptNext = ptHead[33].ptNext;
    ptTail = ptNext[4].tQTaskChildren.ptTail;
    v6 = ptTail->ptNext;
    if ( ptTail->ptNext )
    {
      while ( 1 )
      {
        v7 = ptTail->tQTaskChildren.ptTail;
        if ( v7 )
        {
          if ( LOBYTE(ptTail->tQTaskRefList.ptTail) && v7[16].ptParent == (struct QTask_s *)9 )
            break;
        }
        ptTail = v6;
        v6 = v6->ptNext;
        if ( !v6 )
          goto LABEL_3;
      }
      if ( ptTail->tQTaskChildren.ptTail )
      {
        Weapon_Activate(ptNext, "WEAPON_ID_KNIFE", true);
        Weapon_DisableWeaponType(ptHead[33].ptNext, "WEAPON_ID_C4BOMB", true);
        goto LABEL_2;
      }
    }
  }
  if ( v9 )
  {
    if ( NetMission_isWarmUp )
    {
      ClientFromNetworkID = NetManager_GetClientFromNetworkID((int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
      NetManager_SetTeam(ClientFromNetworkID->eTeam);
      if ( NetManager_eMode != NETMANAGER_MODE_WARMUP )
        return;
    }
    else if ( MapControl_isChangeMapNow() && !BYTE2(ptNetManagerQTask[5].tQTaskChildren.ptTail) )
    {
      NetManager_SetMode(0);
      return;
    }
    NetManager_SetMode(2);
  }
}

// source: j/0/network/netmission.c:1532  [size]
struct NetManagerGameMessageTeamScore_t *__cdecl NetMission_WriteToScoreUpdate(
        struct NetManagerGameMessageTeamScore_t *ptMessage)
{
  struct NetMission_t *v1; // ecx

  v1 = NetMission_ptNetMission;
  ptMessage->nMissionEndTime = NetMission_ptNetMission->nMissionEndTime;
  ptMessage->nWarmupEndTime = v1->nWarmupEndTime;
  ptMessage->nWarmup = ServerConfig_tServerConfig.nPloss;
  ptMessage->nMissionTime = ServerConfig_tServerConfig.nBombTime;
  return ptMessage;
}

// source: j/0/network/netmission.c:1553  [size]
void __cdecl NetMission_ReadFromScoreUpdate(struct NetManagerGameMessageTeamScore_t *ptMessage)
{
  struct QTask_s *ptNetManagerQTask; // edi
  struct NetMission_t *v2; // eax
  int nWarmupEndTime; // [esp-4h] [ebp-8h]

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  v2 = NetMission_ptNetMission;
  NetMission_ptNetMission->nMissionEndTime = ptMessage->nMissionEndTime;
  v2->isStarted = true;
  nWarmupEndTime = ptMessage->nWarmupEndTime;
  v2->nWarmupEndTime = nWarmupEndTime;
  NetMission_EvaluateWarmUp(nWarmupEndTime);
  ptNetManagerQTask[4].ptParent = (struct QTask_s *)ptMessage->nWarmup;
  ptNetManagerQTask[4].tQTaskRefList.ptMiddle = (struct QReference_s *)ptMessage->nMissionTime;
}

// source: j/0/network/netmission.c:1580  [size]
struct NetMission_t *__cdecl NetMission_GetNetMission()
{
  return NetMission_ptNetMission;
}

// source: j/0/network/netmission.c:1596  [anchor-hash]
struct NetObjective_t *__cdecl NetMission_GetObjective(int nObjective)
{
  unsigned __int16 v1; // dx
  struct NetObjective_t *result; // eax

  v1 = NetObjective_eQTaskType;
  result = (struct NetObjective_t *)QTask_GetFirstChildOfType(&NetMission_ptNetMission->tQTask, NetObjective_eQTaskType);
  if ( !result )
    return nullptr;
  while ( result->nNumber != nObjective )
  {
    result = (struct NetObjective_t *)QTask_GetNextSiblingOfType(&result->tQTask, v1);
    if ( !result )
      return nullptr;
  }
  return result;
}

// source: j/0/network/netmission.c:1638  [size]
enum bool __cdecl NetMission_IsWarmUp()
{
  return NetMission_isWarmUp;
}

// source: j/0/network/netmission.c:1653  [size]
int __cdecl NetMission_GetWarmupEndTime()
{
  return NetMission_ptNetMission->nWarmupEndTime;
}

// source: j/0/network/netmission.c:1668  [anchor-callee]
int __cdecl NetMission_GetWarmUpTimer()
{
  struct QTask_s *ptNetManagerQTask; // esi
  DWORD PerformanceCounter; // eax

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  return (int)((int)ptNetManagerQTask[6].tQTaskRefList.ptTail
             + NetMission_ptNetMission->nWarmupEndTime
             - (unsigned int)ptNetManagerQTask[6].tQTaskRefList.ptMiddle
             - (PerformanceCounter
              - Timer_nStartTime))
       / 1000;
}

// source: j/0/network/netmission.c:1683  [anchor-callee]
void __cdecl NetMission_EvaluateWarmUp(int nTime)
{
  struct QTask_s *ptNetManagerQTask; // esi
  DWORD PerformanceCounter; // eax

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  NetMission_isWarmUp = (int)(PerformanceCounter
                            - Timer_nStartTime
                            + (char *)ptNetManagerQTask[6].tQTaskRefList.ptMiddle
                            - (char *)ptNetManagerQTask[6].tQTaskRefList.ptTail) < nTime;
}

// source: j/0/network/netmission.c:1705  [anchor-hash]
void __cdecl NetMission_SetWarmupEndTime(int nTime)
{
  NetMission_ptNetMission->nWarmupEndTime = nTime;
  NetMission_EvaluateWarmUp(nTime);
}

// source: j/0/network/netmission.c:1721  [anchor-mhash]
void __cdecl NetMission_SetWarmup(enum bool isWarmup)
{
  NetMission_isWarmUp = (int)Flow_ptFlow->ptNetManagerQTask[4].ptParent <= 0 ? false : isWarmup;
}

// source: j/0/network/netmission.c:1744  [anchor-hash]
struct QTask_s *__cdecl NetMission_GetComputerHilightTask()
{
  if ( NetMission_ptNetMission )
    return NetMission_ptNetMission->ptBombComputerHighlightQTask;
  else
    return nullptr;
}

// source: j/0/network/netmission.c:1763  [anchor-strings]
char *__cdecl NetMission_SetDesc(size_t a1, char *a2)
{
  char *LocalizedStringForLanguage; // eax
  char *LocalizedString; // eax
  int v6; // edi
  int MissionTimer; // eax
  char *v8; // eax

  if ( !NetMission_ptNetMission )
    return strncpy(a2, "No mission set", a1);
  if ( NetMission_ptNetMission->isStarted == false )
    return strncpy(a2, "Mission not started", a1);
  if ( NetMission_ptNetMission->nMissionEndTime )
  {
    if ( C4BombArea_SoundUpdateParameterListHandler() && NetMission_eCurrentObjective )
    {
      LocalizedString = Config_GetLocalizedString("mp/BOMB_PLACED");
      return strncpy(a2, LocalizedString, a1);
    }
    else if ( NetMission_GetMissionTimer() > 0 && NetMission_eCurrentObjective )
    {
      v6 = NetMission_GetMissionTimer() / 60;
      MissionTimer = NetMission_GetMissionTimer();
      return (char *)_snprintf(a2, 0x40u, "%02d : %02d", v6, MissionTimer % 60);
    }
    else
    {
      v8 = Config_GetLocalizedString("mp/Mission Over");
      return (char *)_snprintf(a2, 0x40u, v8);
    }
  }
  else
  {
    LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                   "mp/WaitingforData",
                                   Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                   true);
    return strncpy(a2, LocalizedStringForLanguage, a1);
  }
}

// source: j/0/network/netmission.c:1841  [size~]
char *__cdecl NetMission_GetWhoDidLastObjective()
{
  size_t v0; // ecx
  char *v1; // edi
  int v3; // esi
  int MissionTimer; // eax

  if ( !NetMission_ptNetMission )
    return strncpy(v1, "LOADING", v0);
  if ( NetMission_ptNetMission->isStarted == false )
    return strncpy(v1, "NOT STARTED", v0);
  if ( !NetMission_ptNetMission->nMissionEndTime )
    return strncpy(v1, "NO DATA", v0);
  if ( NetMission_GetMissionTimer() <= 0 )
    return (char *)_snprintf(v1, 0x40u, "MISSION OVER");
  v3 = NetMission_GetMissionTimer() / 60;
  MissionTimer = NetMission_GetMissionTimer();
  return (char *)_snprintf(v1, 0x40u, "%02d:%02d", v3, MissionTimer % 60);
}

void __cdecl sub_4D8AC0(struct QTask_s *a1)
{
  a1[1].ptNext = nullptr;
  a1[1].ptPrev = nullptr;
  a1[1].tQTaskChildren.ptHead = nullptr;
  *(_DWORD *)&a1[2].eQTaskType = 0;
  LOBYTE(a1[3].ptNext) = 0;
  a1[3].ptParent = (struct QTask_s *)-1;
  *(_DWORD *)&a1[3].eQTaskType = 0;
  a1[4].ptNext = nullptr;
  a1[4].ptPrev = nullptr;
  a1[5].ptParent = nullptr;
  *(_DWORD *)&a1[5].eQTaskType = 0;
  a1[6].ptNext = nullptr;
  a1[6].ptPrev = nullptr;
  a1[7].ptParent = nullptr;
  *(_DWORD *)&a1[7].eQTaskType = 0;
  a1[8].ptNext = nullptr;
  LOBYTE(a1[8].ptPrev) = 0;
  *(_DWORD *)&a1[8].eQTaskType = -1;
  a1[9].ptNext = nullptr;
  a1[9].ptPrev = nullptr;
  a1[9].tQTaskChildren.ptHead = nullptr;
  *(_DWORD *)&a1[10].eQTaskType = 0;
  a1[11].ptNext = nullptr;
  a1[11].ptPrev = nullptr;
  a1[11].tQTaskChildren.ptHead = nullptr;
  *(_DWORD *)&a1[12].eQTaskType = 0;
  a1[13].ptNext = nullptr;
  a1[13].ptPrev = nullptr;
  LOBYTE(a1[13].tQTaskChildren.ptHead) = 0;
  a1[14].ptNext = (struct QTask_s *)-1;
  a1[14].ptPrev = nullptr;
  a1[14].tQTaskChildren.ptHead = nullptr;
  a1[14].tQTaskChildren.ptMiddle = nullptr;
  a1[16].ptNext = nullptr;
  a1[16].ptPrev = nullptr;
  a1[16].tQTaskChildren.ptHead = nullptr;
  a1[16].tQTaskChildren.ptMiddle = nullptr;
  a1[18].ptNext = nullptr;
  a1[18].ptPrev = nullptr;
  a1[18].tQTaskChildren.ptHead = nullptr;
  LOBYTE(a1[18].tQTaskChildren.ptMiddle) = 0;
  a1[19].ptPrev = (struct QTask_s *)-1;
  a1[19].tQTaskChildren.ptHead = nullptr;
  a1[19].tQTaskChildren.ptMiddle = nullptr;
  a1[19].tQTaskChildren.ptTail = nullptr;
  a1[21].ptPrev = nullptr;
  a1[21].tQTaskChildren.ptHead = nullptr;
  a1[21].tQTaskChildren.ptMiddle = nullptr;
  a1[21].tQTaskChildren.ptTail = nullptr;
  a1[23].ptPrev = nullptr;
  a1[23].tQTaskChildren.ptHead = nullptr;
  a1[23].tQTaskChildren.ptMiddle = nullptr;
  LOBYTE(a1[23].tQTaskChildren.ptTail) = 0;
  a1[24].tQTaskChildren.ptHead = (struct QTask_s *)-1;
  a1[24].tQTaskChildren.ptMiddle = nullptr;
  a1[24].tQTaskChildren.ptTail = nullptr;
  a1[24].tQTaskRefList.ptHead = nullptr;
  a1[26].tQTaskChildren.ptHead = nullptr;
  a1[26].tQTaskChildren.ptMiddle = nullptr;
  a1[26].tQTaskChildren.ptTail = nullptr;
  a1[26].tQTaskRefList.ptHead = nullptr;
  a1[28].tQTaskChildren.ptHead = nullptr;
  a1[28].tQTaskChildren.ptMiddle = nullptr;
  a1[28].tQTaskChildren.ptTail = nullptr;
  LOBYTE(a1[28].tQTaskRefList.ptHead) = 0;
  a1[29].tQTaskChildren.ptMiddle = (struct QTask_s *)-1;
  a1[29].tQTaskChildren.ptTail = nullptr;
  a1[29].tQTaskRefList.ptHead = nullptr;
  a1[29].tQTaskRefList.ptMiddle = nullptr;
  a1[31].tQTaskChildren.ptMiddle = nullptr;
  a1[31].tQTaskChildren.ptTail = nullptr;
  a1[31].tQTaskRefList.ptHead = nullptr;
  a1[31].tQTaskRefList.ptMiddle = nullptr;
  a1[33].tQTaskChildren.ptMiddle = nullptr;
  a1[33].tQTaskChildren.ptTail = nullptr;
  a1[33].tQTaskRefList.ptHead = nullptr;
  LOBYTE(a1[33].tQTaskRefList.ptMiddle) = 0;
  a1[34].tQTaskChildren.ptTail = (struct QTask_s *)-1;
  a1[34].tQTaskRefList.ptHead = nullptr;
  a1[34].tQTaskRefList.ptMiddle = nullptr;
  a1[34].tQTaskRefList.ptTail = nullptr;
  a1[36].tQTaskChildren.ptTail = nullptr;
  a1[36].tQTaskRefList.ptHead = nullptr;
  a1[36].tQTaskRefList.ptMiddle = nullptr;
  a1[36].tQTaskRefList.ptTail = nullptr;
  a1[38].tQTaskChildren.ptTail = nullptr;
  a1[38].tQTaskRefList.ptHead = nullptr;
  a1[38].tQTaskRefList.ptMiddle = nullptr;
  LOBYTE(a1[38].tQTaskRefList.ptTail) = 0;
  a1[39].tQTaskRefList.ptHead = (struct QReference_s *)-1;
  a1[39].tQTaskRefList.ptMiddle = nullptr;
  a1[39].tQTaskRefList.ptTail = nullptr;
  a1[39].ptParent = nullptr;
  a1[41].tQTaskRefList.ptHead = nullptr;
  a1[41].tQTaskRefList.ptMiddle = nullptr;
  a1[41].tQTaskRefList.ptTail = nullptr;
  a1[41].ptParent = nullptr;
  a1[43].tQTaskRefList.ptHead = nullptr;
  a1[43].tQTaskRefList.ptMiddle = nullptr;
  a1[43].tQTaskRefList.ptTail = nullptr;
}
