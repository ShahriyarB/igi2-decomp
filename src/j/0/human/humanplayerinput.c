/* j/0/human/humanplayerinput.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/human/humanplayerinput.c:74  [anchor-callee]
void __cdecl HumanPlayerInput_ReadChannels(struct HumanPlayerInput_t *ptHumanPlayerInput, float *pvChannel)
{
  int v2; // ebp
  unsigned __int64 bCurrentButton; // kr00_8
  int v4; // ebp
  enum NetManagerMode_e v5; // eax
  double v6; // st7
  unsigned int v7; // edx
  double v8; // st7
  double v9; // st7
  double v10; // st7
  double v11; // st7
  double v12; // st7
  double v13; // st7
  double v14; // st7
  double v15; // st7
  double v16; // st7
  double v17; // st7
  double v18; // st7
  double v19; // st7
  double v20; // st7
  double v21; // st7
  double v22; // st7
  double v23; // st7
  double v24; // st7
  double v25; // st7
  double v26; // st7
  double v27; // st7
  double v28; // st7
  double v29; // st7
  double v30; // st7
  double v31; // st7
  double v32; // st7
  double v33; // st7
  double v34; // st7
  double v35; // st7
  double v36; // st7
  double v37; // st7
  double v38; // st7
  double v39; // st7
  double v40; // st7
  double v41; // st7
  double v42; // st7
  double v43; // st7
  double v44; // st7
  double v45; // st7
  double v46; // st7
  double v47; // st7
  double v48; // st7
  double v49; // st7
  double v50; // st7
  enum GameMode_e v51; // eax
  struct Client_s *ClientFromNetworkID; // eax
  float v53; // [esp+Ch] [ebp-14h]
  unsigned __int64 bEdgeButton; // [esp+18h] [ebp-8h]

  v2 = 2752 * Config_tConfig.iActiveProfile;
  memset(pvChannel, 0, 0xFCu);
  bCurrentButton = InputPort_atInputPort[0].tInput.bCurrentButton;
  v4 = v2 + 7392072;
  bEdgeButton = InputPort_atInputPort[0].tInput.bEdgeButton;
  if ( Game_eGameMode != GAME_GAMEMODE_MULTIPLAYER )
    goto LABEL_20;
  if ( MenuManager_ptQTask && MenuManager_ptQTask[1].tQTaskChildren.ptMiddle != (struct QTask_s *)10 )
  {
    v5 = NetManager_eMode;
    goto LABEL_10;
  }
  v5 = NetManager_eMode;
  if ( NetManager_eMode != NETMANAGER_MODE_PLAY && NetManager_eMode != NETMANAGER_MODE_WARMUP )
  {
LABEL_10:
    if ( v5 != NETMANAGER_MODE_RADIO )
    {
      if ( (InputPort_atInputPort[0].tInput.bCurrentButton & 0x40000000) != 0 )
        v6 = 1.0;
      else
        v6 = 0.0;
      v7 = InputPort_atInputPort[0].tInput.bCurrentButton & 0x80000000;
      pvChannel[17] = v6;
      if ( v7 )
        v8 = 1.0;
      else
        v8 = 0.0;
      pvChannel[18] = v8;
      if ( (bCurrentButton & 0x2000000000000LL) != 0 )
        pvChannel[48] = 1.0;
      else
        pvChannel[48] = 0.0;
      return;
    }
    goto LABEL_7;
  }
  if ( NetManager_eMode == NETMANAGER_MODE_RADIO )
  {
LABEL_7:
    if ( Keyboard_IsNumberActive() )
    {
      NetManager_LogMessage("HumanplayerInput_ReadChannels: Radio and num active\n");
      return;
    }
  }
LABEL_20:
  *pvChannel = InputPort_atInputPort[0].tInput.vAnalogX;
  if ( *(_DWORD *)(v4 + 2692) )
    v9 = -1.0;
  else
    v9 = 1.0;
  pvChannel[1] = v9 * InputPort_atInputPort[0].tInput.vAnalogY;
  if ( (bCurrentButton & 1) != 0 )
    v10 = 1.0;
  else
    v10 = 0.0;
  pvChannel[2] = v10;
  if ( (bCurrentButton & 2) != 0 )
    v11 = 1.0;
  else
    v11 = 0.0;
  pvChannel[3] = v11;
  if ( (bCurrentButton & 4) != 0 )
    v12 = 1.0;
  else
    v12 = 0.0;
  pvChannel[4] = v12;
  if ( (bCurrentButton & 8) != 0 )
    v13 = 1.0;
  else
    v13 = 0.0;
  pvChannel[5] = v13;
  if ( *(float *)(v4 + 2696) >= 0.05000000074505806 )
  {
    if ( *(float *)(v4 + 2696) <= 1.0 )
      v14 = *(float *)(v4 + 2696);
    else
      v14 = 1.0;
  }
  else
  {
    v14 = 0.05000000074505806;
  }
  v53 = v14 * *pvChannel;
  *pvChannel = v53;
  pvChannel[1] = v14 * pvChannel[1];
  if ( (bCurrentButton & 0x100) != 0 )
    *pvChannel = v53 - 0.05000000074505806;
  if ( (bCurrentButton & 0x200) != 0 )
    *pvChannel = *pvChannel + 0.05000000074505806;
  if ( (bCurrentButton & 0x80000) != 0 )
    v15 = 1.0;
  else
    v15 = 0.0;
  pvChannel[6] = v15;
  if ( (bCurrentButton & 0x100000) != 0 )
    v16 = 1.0;
  else
    v16 = 0.0;
  pvChannel[7] = v16;
  if ( (bCurrentButton & 0x40000) != 0 )
    v17 = 1.0;
  else
    v17 = 0.0;
  pvChannel[8] = v17;
  if ( (bCurrentButton & 0x20000) != 0 )
    v18 = 1.0;
  else
    v18 = 0.0;
  pvChannel[9] = v18;
  if ( (bCurrentButton & 0x400) != 0 )
    v19 = 1.0;
  else
    v19 = 0.0;
  pvChannel[10] = v19;
  if ( (bCurrentButton & 0x1000) != 0 )
    v20 = 1.0;
  else
    v20 = 0.0;
  pvChannel[39] = v20;
  if ( (bCurrentButton & 0x2000) != 0 )
    v21 = 1.0;
  else
    v21 = 0.0;
  pvChannel[38] = v21;
  if ( (bCurrentButton & 0x40000000000000LL) != 0 )
    v22 = 1.0;
  else
    v22 = 0.0;
  pvChannel[49] = v22;
  if ( (bCurrentButton & 0x8000) != 0 )
    v23 = 1.0;
  else
    v23 = 0.0;
  pvChannel[40] = v23;
  if ( (bCurrentButton & 0x800) != 0 )
    v24 = 1.0;
  else
    v24 = 0.0;
  pvChannel[11] = v24;
  if ( (bCurrentButton & 0x10000) != 0 )
    v25 = 1.0;
  else
    v25 = 0.0;
  pvChannel[12] = v25;
  pvChannel[13] = -1.0;
  if ( (bCurrentButton & 0x2000000) != 0 )
    v26 = 1.0;
  else
    v26 = 0.0;
  pvChannel[14] = v26;
  if ( (bCurrentButton & 0x4000000) != 0 )
    v27 = 1.0;
  else
    v27 = 0.0;
  pvChannel[15] = v27;
  if ( (bCurrentButton & 0x800000) != 0 )
    v28 = 1.0;
  else
    v28 = 0.0;
  pvChannel[16] = v28;
  if ( (bCurrentButton & 0x40000000) != 0 )
    v29 = 1.0;
  else
    v29 = 0.0;
  pvChannel[17] = v29;
  if ( (bCurrentButton & 0x80000000) == 0LL )
    v30 = 0.0;
  else
    v30 = 1.0;
  pvChannel[18] = v30;
  if ( (bCurrentButton & 0x4000) != 0 )
    v31 = 1.0;
  else
    v31 = 0.0;
  pvChannel[23] = v31;
  if ( (bCurrentButton & 0x200000) != 0 )
    v32 = 1.0;
  else
    v32 = 0.0;
  pvChannel[24] = v32;
  if ( (bCurrentButton & 0x400000) != 0 )
    v33 = 1.0;
  else
    v33 = 0.0;
  pvChannel[25] = v33;
  if ( (bEdgeButton & 0x100000000LL) != 0 )
    v34 = 1.0;
  else
    v34 = 0.0;
  pvChannel[26] = v34;
  if ( (bEdgeButton & 0x200000000LL) != 0 )
    v35 = 1.0;
  else
    v35 = 0.0;
  pvChannel[27] = v35;
  if ( (bEdgeButton & 0x400000000LL) != 0 )
    v36 = 1.0;
  else
    v36 = 0.0;
  pvChannel[28] = v36;
  if ( (bEdgeButton & 0x800000000LL) != 0 )
    v37 = 1.0;
  else
    v37 = 0.0;
  pvChannel[29] = v37;
  if ( (bEdgeButton & 0x1000000000LL) != 0 )
    v38 = 1.0;
  else
    v38 = 0.0;
  pvChannel[30] = v38;
  if ( (bEdgeButton & 0x2000000000LL) != 0 )
    v39 = 1.0;
  else
    v39 = 0.0;
  pvChannel[31] = v39;
  if ( (bEdgeButton & 0x4000000000LL) != 0 )
    v40 = 1.0;
  else
    v40 = 0.0;
  pvChannel[32] = v40;
  if ( (bEdgeButton & 0x8000000000LL) != 0 )
    v41 = 1.0;
  else
    v41 = 0.0;
  pvChannel[33] = v41;
  if ( (bEdgeButton & 0x10000000000LL) != 0 )
    v42 = 1.0;
  else
    v42 = 0.0;
  pvChannel[34] = v42;
  if ( (bEdgeButton & 0x4000000000000LL) != 0 )
    v43 = 1.0;
  else
    v43 = 0.0;
  pvChannel[47] = v43;
  if ( (bCurrentButton & 0x1000000) != 0 )
    v44 = 1.0;
  else
    v44 = 0.0;
  pvChannel[37] = v44;
  if ( (bCurrentButton & 0x8000000) != 0 )
    v45 = 1.0;
  else
    v45 = 0.0;
  pvChannel[43] = v45;
  if ( (bCurrentButton & 0x2000000000000LL) != 0 )
    v46 = 1.0;
  else
    v46 = 0.0;
  pvChannel[48] = v46;
  if ( (bCurrentButton & 0x10000000) != 0 )
    v47 = 1.0;
  else
    v47 = 0.0;
  pvChannel[35] = v47;
  if ( (bCurrentButton & 0x100000000000LL) != 0 )
    v48 = 1.0;
  else
    v48 = 0.0;
  pvChannel[44] = v48;
  if ( (bCurrentButton & 0x200000000000LL) != 0 )
    v49 = 1.0;
  else
    v49 = 0.0;
  pvChannel[45] = v49;
  if ( (bCurrentButton & 0x400000000000LL) != 0 )
    v50 = 1.0;
  else
    v50 = 0.0;
  v51 = Game_eGameMode;
  pvChannel[46] = v50;
  pvChannel[19] = 0.0;
  pvChannel[20] = 0.0;
  pvChannel[21] = 0.0;
  pvChannel[22] = 0.0;
  pvChannel[36] = 0.0;
  pvChannel[51] = 0.0;
  pvChannel[50] = 0.0;
  pvChannel[54] = 0.0;
  pvChannel[55] = 0.0;
  pvChannel[52] = 0.0;
  pvChannel[53] = 0.0;
  if ( v51 == GAME_GAMEMODE_MULTIPLAYER )
  {
    ClientFromNetworkID = NetManager_GetClientFromNetworkID((int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
    pvChannel[43] = 0.0;
    if ( ClientFromNetworkID->zTalkString[4] || ClientFromNetworkID->zTalkString[5] )
    {
      pvChannel[2] = (float)(Keyboard_tKeyboard.anAlwaysCurrentKey[203] & 0x80);
      pvChannel[3] = (float)(Keyboard_tKeyboard.anAlwaysCurrentKey[205] & 0x80);
      pvChannel[4] = (float)(Keyboard_tKeyboard.anAlwaysCurrentKey[200] & 0x80);
      pvChannel[5] = (float)(Keyboard_tKeyboard.anAlwaysCurrentKey[208] & 0x80);
    }
    if ( NetManager_eMode == NETMANAGER_MODE_WARMUP )
    {
      pvChannel[6] = 0.0;
      pvChannel[7] = 0.0;
    }
  }
  if ( ptHumanPlayerInput->isFreezeFire )
  {
    if ( pvChannel[6] == 0.0 )
      ptHumanPlayerInput->isFreezeFire = false;
    else
      pvChannel[6] = 0.0;
  }
}

// source: j/0/human/humanplayerinput.c:271  [anchor-callee]
void __cdecl HumanPlayerInput_SendClientInformation(struct QTask_s *ptQTask)
{
  struct QTask_s *ptParent; // esi
  struct Client_s *ClientFromNetworkID; // edi
  int GlobalPriority; // ebx
  DWORD PerformanceCounter; // eax
  int v6; // edx
  double v7; // st7
  char *v8; // ebx
  int Timer; // eax
  struct Flow_t *v10; // edx
  struct Flow_t *v11; // ecx
  int v12; // esi
  DWORD TickCount; // eax
  float vThresholdRadius; // [esp+0h] [ebp-28h]
  float vThresholdViewDistance; // [esp+4h] [ebp-24h]
  float tSpeedDiff; // [esp+1Ch] [ebp-Ch]
  float tSpeedDiff_4; // [esp+20h] [ebp-8h]
  struct QTask_s *ptQTaska = *(struct QTask_s * *)&ptQTask; // [esp+2Ch] [ebp+4h] ARGSLOT

  ptParent = ptQTask->ptParent;
  ClientFromNetworkID = NetManager_GetClientFromNetworkID((int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
  if ( !LOBYTE(ptParent[80].tQTaskChildren.ptTail) )
    return;
  if ( ptQTask[10].ptNext == (struct QTask_s *)-1 )
    goto LABEL_14;
  vThresholdViewDistance = (double)ServerConfig_tServerConfig.nCloseFireRange * 4096.0;
  vThresholdRadius = (double)ServerConfig_tServerConfig.nViewPosRange * 4096.0;
  GlobalPriority = Client_GetGlobalPriority(vThresholdRadius, vThresholdViewDistance);
  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  v6 = PerformanceCounter - Timer_nStartTime - (unsigned int)ptQTask[10].ptNext;
  if ( v6 > 0 && (GlobalPriority || v6 >= Client_GetLowDelay(ClientFromNetworkID)) )
  {
    if ( v6 >= Client_GetHighDelay(ClientFromNetworkID) )
    {
      ++*(int *)&ptQTask[23].tQTaskRefList.ptHead;
    }
    else
    {
      ptQTaska = (struct QTask_s *)Client_GetDeltaSpeedForceUpdate(ClientFromNetworkID);
      tSpeedDiff = *(float *)&ptParent[39].ptNext - *(float *)&ptQTask[22].eQTaskType;
      tSpeedDiff_4 = *(float *)&ptParent[39].ptPrev - *(float *)&ptQTask[23].ptNext;
      v7 = *(float *)&ptParent[39].tQTaskChildren.ptHead - *(float *)&ptQTask[23].ptPrev;
      *(_DWORD *)&ptQTask[22].eQTaskType = ptParent[39].ptNext;
      ptQTask[23].ptNext = ptParent[39].ptPrev;
      ptQTask[23].ptPrev = ptParent[39].tQTaskChildren.ptHead;
      if ( (double)(int)ptQTaska > sqrt(tSpeedDiff * tSpeedDiff + tSpeedDiff_4 * tSpeedDiff_4 + v7 * v7)
        && !ptParent[87].tQTaskChildren.ptMiddle )
      {
        return;
      }
      ptParent[87].tQTaskChildren.ptMiddle = nullptr;
      ++*(int *)&ptQTask[23].tQTaskRefList.ptMiddle;
    }
LABEL_14:
    v8 = (char *)Mem_AllocFn(48, 4);
    v8[8] = 1;
    *(_DWORD *)v8 = 1213093200;
    Timer = NetManager_GetTimer();
    v10 = Flow_ptFlow;
    *((_DWORD *)v8 + 1) = Timer;
    v8[12] = (char)v10->ptNetManagerQTask[6].tQTaskChildren.ptMiddle;
    HumanPlayer_FillGameMessageUpdate(
      (struct HumanPlayer_t *)ptParent,
      (struct ClientGameMessageUpdateBody_s *)(v8 + 12));
    *(_DWORD *)&ptQTask[22].eQTaskType = ptParent[39].ptNext;
    ptQTask[23].ptNext = ptParent[39].ptPrev;
    v11 = Flow_ptFlow;
    ptQTask[23].ptPrev = ptParent[39].tQTaskChildren.ptHead;
    NetManager_SendGameMessage(
      0,
      (int)v11->ptNetManagerQTask[6].tQTaskChildren.ptMiddle,
      NETWORKQUEUE_MEDIUMPRIORITY,
      (struct NetManagerGameMessage_s *)v8,
      0x30u);
    v12 = *(_DWORD *)((unsigned int)(v8 - 4) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v12);
    memset(*(void **)(v12 + 8), 0xCDu, *(_DWORD *)(v12 + 16));
    free((void *)v12);
    if ( Timer_isPerformanceCounter )
      TickCount = Timer_GetPerformanceCounter();
    else
      TickCount = GetTickCount();
    ptQTask[10].ptNext = (struct QTask_s *)(TickCount - Timer_nStartTime);
  }
}

// source: j/0/human/humanplayerinput.c:414  [anchor-strings]
void __cdecl HumanPlayerInput_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v2; // edi
  struct QTask_s *ptParent; // edx
  char *p_tQTaskRefList; // ebp
  int v5; // eax
  struct QReference_s *v6; // ecx
  int v7; // esi
  enum bool v8; // eax
  struct QTask_s *v9; // eax
  struct QTask_s *v10; // ecx
  struct QTask_s *v11; // esi
  unsigned int v12; // eax
  FILE *v13; // eax
  struct QTask_s *ptPrev; // ecx
  struct QTask_s *v15; // eax

  v2 = ptQTask;
  ptParent = ptQTask->ptParent;
  p_tQTaskRefList = (char *)&ptQTask[16].tQTaskRefList;
  ptQTask[5].tQTaskRefList.ptTail = nullptr;
  *(_DWORD *)&v2[5].eQTaskType = 0;
  v2[5].ptParent = nullptr;
  v2[5].tQTaskRefList.ptMiddle = nullptr;
  v2[5].tQTaskChildren.ptTail = nullptr;
  v2[5].tQTaskRefList.ptHead = nullptr;
  *p_tQTaskRefList = 0;
  LOBYTE(v2[10].ptPrev) = 0;
  v2[23].tQTaskChildren.ptMiddle = nullptr;
  v2[23].tQTaskChildren.ptHead = nullptr;
  v2[23].tQTaskChildren.ptTail = nullptr;
  v2[23].tQTaskRefList.ptMiddle = nullptr;
  v2[23].tQTaskRefList.ptHead = nullptr;
  *(_DWORD *)&v2[22].eQTaskType = 0;
  v2[23].ptNext = nullptr;
  v2[23].ptPrev = nullptr;
  v5 = 0;
  while ( 1 )
  {
    v6 = Level_atLevelQTaskID[v5];
    if ( v6 )
    {
      if ( v6->pxObject == ptParent )
        break;
    }
    if ( ++v5 >= 4096 )
    {
      v7 = -1;
      goto LABEL_6;
    }
  }
  v7 = v5;
LABEL_6:
  if ( HumanPlayerInput_isPlayback && v7 >= 0 )
  {
    sprintf(p_tQTaskRefList, "%s_Human%d_Mission%d.bin", HumanPlayerInput_zPlaybackFilename, v7, Game_iMissionID);
    if ( Resource_IsLoadedInternal(p_tQTaskRefList, nullptr) )
      v8 = true;
    else
      v8 = File_Exists(p_tQTaskRefList);
    v2[23].tQTaskChildren.ptMiddle = (struct QTask_s *)v8;
  }
  if ( HumanPlayerInput_isRecord && v7 >= 0 )
  {
    sprintf(
      (char *const)&v2[10].ptPrev,
      "%s_Human%d_Mission%d.bin",
      HumanPlayerInput_zRecordFilename,
      v7,
      Game_iMissionID);
    v2[23].tQTaskChildren.ptHead = (struct QTask_s *)1;
  }
  if ( v2[23].tQTaskChildren.ptMiddle )
  {
    v9 = (struct QTask_s *)Resource_Load(p_tQTaskRefList, (unsigned int *)&ptQTask);
    v10 = ptQTask;
    v11 = v9;
    v12 = (unsigned int)((((unsigned int)ptQTask
                         * (unsigned __int64)((unsigned int)&MTP_atLODVirModel[302].atBoneVertexRefs[2].atVertexRefs[540].iVertex
                                            + 1)) >> 32)
                       + ((unsigned int)((unsigned int)ptQTask
                                       - (((unsigned int)ptQTask
                                         * (unsigned __int64)((unsigned int)&MTP_atLODVirModel[302].atBoneVertexRefs[2].atVertexRefs[540].iVertex
                                                            + 1)) >> 32)) >> 1)) >> 7;
    v2[5].tQTaskRefList.ptMiddle = (struct QReference_s *)v12;
    v2[5].tQTaskChildren.ptTail = v11;
    if ( (struct QTask_s *)(252 * v12) != v10 )
    {
      Resource_Flush(v11);
      v2[5].tQTaskChildren.ptTail = nullptr;
      v2[5].tQTaskRefList.ptMiddle = nullptr;
    }
  }
  if ( v2[23].tQTaskChildren.ptHead )
    v2[5].tQTaskRefList.ptHead = (struct QReference_s *)Mem_AllocFn(
                                                          (int)&MTP_atLODVirModel[6].atBoneVertexRefs[47].atVertexRefs[102],
                                                          4);
  v2[10].ptNext = (struct QTask_s *)-1;
  v2[6].ptNext = nullptr;
  v2[6].ptPrev = nullptr;
  v2[6].tQTaskChildren.ptHead = nullptr;
  *(_DWORD *)&v2[7].eQTaskType = 0;
  v2[8].ptNext = nullptr;
  v2[8].ptPrev = nullptr;
  v2[8].tQTaskChildren.ptHead = nullptr;
  *(_DWORD *)&v2[9].eQTaskType = 0;
  if ( v2[23].tQTaskChildren.ptHead )
  {
    v13 = fopen((char *)&v2[10].ptPrev, "wb");
    if ( v13 )
      fclose(v13);
  }
  ptPrev = v2->ptPrev;
  if ( ptPrev && ptPrev->ptPrev )
  {
    while ( 1 )
    {
      v15 = ptPrev->ptPrev;
      if ( !v15 || !v15->ptPrev )
        break;
      ptPrev = ptPrev->ptPrev;
    }
    QTask_InsertBeforeQTask(v2, ptPrev);
  }
}

// source: j/0/human/humanplayerinput.c:517  [anchor-caller]
void __cdecl HumanPlayerInput_RunHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QReference_s *pxBuffer; };
    struct { char igi2_o1[8]; __int64 tHumanUpdateContext; };
    struct { char igi2_o2[16]; float avChannel[64]; };
    char igi2_extent[272];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptParent; // edi
  struct QReference_s *ptMiddle; // ecx
  struct QReference_s *ptTail; // eax
  FILE *v4; // eax
  FILE *v5; // esi
  struct QTask_s *v6; // eax
  __int16 v7; // ax
  void (__cdecl *pfHandler)(struct QTask_s *, __int64 *); // eax

  ptParent = ptQTask->ptParent;
  if ( ptQTask[23].tQTaskChildren.ptMiddle
    && (ptMiddle = ptQTask[5].tQTaskRefList.ptMiddle) != nullptr
    && (ptTail = ptQTask[5].tQTaskRefList.ptTail, ptTail < ptMiddle) )
  {
    qmemcpy(igi2_frame.avChannel, (char *)ptQTask[5].tQTaskChildren.ptTail + 252 * (_DWORD)ptTail, 0xFCu);
    ptQTask[5].tQTaskRefList.ptTail = (struct QReference_s *)((char *)&ptTail->ptNext + 1);
  }
  else
  {
    HumanPlayerInput_ReadChannels((struct HumanPlayerInput_t *)ptQTask, igi2_frame.avChannel);
  }
  if ( ptQTask[23].tQTaskChildren.ptHead && ptQTask[5].ptParent < (struct QTask_s *)0x8CA0 )
  {
    igi2_frame.pxBuffer = &ptQTask[5].tQTaskRefList.ptHead[21 * *(_DWORD *)&ptQTask[5].eQTaskType];
    qmemcpy(igi2_frame.pxBuffer, igi2_frame.avChannel, 0xFCu);
    v4 = fopen((char *)&ptQTask[10].ptPrev, "ab");
    v5 = v4;
    if ( v4 )
    {
      fwrite(igi2_frame.pxBuffer, 0xFCu, 1u, v4);
      fclose(v5);
    }
    v6 = (struct QTask_s *)((char *)&ptQTask[5].ptParent->ptNext + 1);
    ++*(_DWORD *)&ptQTask[5].eQTaskType;
    ptQTask[5].ptParent = v6;
  }
  if ( ptQTask[8].ptNext
    && ptQTask[8].ptPrev->ptNext
    && ptQTask[8].tQTaskChildren.ptHead
    && (unsigned int)(__int64)Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[8], ptQTask) )
  {
    igi2_frame.avChannel[35] = 0.0;
    memset(&igi2_frame.avChannel[44], 0, 12);
  }
  if ( ptQTask[6].ptNext && ptQTask[6].ptPrev->ptNext && ptQTask[6].tQTaskChildren.ptHead )
  {
    igi2_frame.tHumanUpdateContext = (__int64)Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[6], ptQTask);
    Computer_isEnabled = igi2_frame.tHumanUpdateContext;
  }
  else
  {
    Computer_isEnabled = 1;
  }
  LODWORD(igi2_frame.tHumanUpdateContext) = igi2_frame.avChannel;
  v7 = Human_eHumanUpdateQTaskEvent;
  if ( Human_eHumanUpdateQTaskEvent == 512 )
  {
    v7 = QTask_NewQTaskEventFn(0, "HumanUpdate");
    Human_eHumanUpdateQTaskEvent = v7;
  }
  pfHandler = (void (__cdecl *)(struct QTask_s *, __int64 *))QTask_aatQTaskFinalEvent[v7][ptParent->eQTaskType].pfHandler;
  if ( pfHandler )
    pfHandler(ptParent, &igi2_frame.tHumanUpdateContext);
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    if ( NetManager_eMode == NETMANAGER_MODE_PLAY
      || NetManager_eMode == NETMANAGER_MODE_WARMUP
      || NetManager_eMode == NETMANAGER_MODE_DEAD
      || NetManager_eMode == NETMANAGER_MODE_SHOP && !LOBYTE(ptParent[29].tQTaskRefList.ptHead)
      || !BYTE2(ptParent[50].ptNext) )
    {
      if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
        HumanPlayerInput_SendClientInformation(ptQTask);
    }
    NetManager_KeyPressedHandler(InputPort_atInputPort[0].tInput.bEdgeButton);
  }
}

// source: j/0/human/humanplayerinput.c:650  [anchor-mhash]
void __cdecl HumanPlayerInput_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptTail; // edx
  struct QReference_s *ptHead; // eax
  int v3; // esi

  ptTail = ptQTask[5].tQTaskChildren.ptTail;
  if ( ptTail )
    Resource_Flush(ptTail);
  ptHead = ptQTask[5].tQTaskRefList.ptHead;
  if ( ptHead )
  {
    v3 = *(_DWORD *)((unsigned int)&ptHead[-1].pxObject & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v3);
    memset(*(void **)(v3 + 8), 0xCDu, *(_DWORD *)(v3 + 16));
    free((void *)v3);
    ptQTask[5].tQTaskRefList.ptHead = nullptr;
  }
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[6]);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[8]);
}

// source: j/0/human/humanplayerinput.c:693  [size]
void __cdecl HumanPlayerInput_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = HumanPlayerInput_ptParameterList;
}

// source: j/0/human/humanplayerinput.c:709  [size]
void __cdecl HumanPlayerInput_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[6], ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[8], ptQTask);
}

// source: j/0/human/humanplayerinput.c:727  [size]
void __cdecl HumanPlayerInput_ParseRecordCmdLineArgs(char *zArg)
{
  char *v1; // eax
  char v2; // cl

  v1 = zArg;
  if ( strlen(zArg) )
  {
    HumanPlayerInput_isRecord = true;
    do
    {
      v2 = *v1;
      v1[HumanPlayerInput_zRecordFilename - zArg] = *v1;
      ++v1;
    }
    while ( v2 );
  }
}

// source: j/0/human/humanplayerinput.c:744  [size]
void __cdecl HumanPlayerInput_ParsePlaybackCmdLineArgs(char *zArg)
{
  char *v1; // eax
  char v2; // cl

  v1 = zArg;
  if ( strlen(zArg) )
  {
    HumanPlayerInput_isPlayback = true;
    do
    {
      v2 = *v1;
      v1[HumanPlayerInput_zPlaybackFilename - zArg] = *v1;
      ++v1;
    }
    while ( v2 );
  }
}

// source: j/0/human/humanplayerinput.c:763  [size]
unsigned __int16 __cdecl HumanPlayerInput_GetQTaskType()
{
  return HumanPlayerInput_eQTaskType;
}

// source: j/0/human/humanplayerinput.c:778  [anchor-hash]
void __cdecl HumanPlayerInput_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si
  struct ParameterList_s *v2; // eax
  int v3; // edx

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("HumanPlayerInput", 952, BaseQTaskType, 0, 0);
  HumanPlayerInput_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(
    v1,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveNoChildrenHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 0, HumanPlayerInput_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, HumanPlayerInput_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, HumanPlayerInput_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))HumanPlayerInput_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eUpdateInternalDataQTaskEvent,
    HumanPlayerInput_UpdateInternalDataHandler);
  v2 = (struct ParameterList_s *)Mem_AllocFn(52, 4);
  v2->ptParameterListItem = (struct ParameterListItem_s *)&v2[1];
  v3 = Level_eParameterTypeVarString;
  v2->nParameters = 0;
  v2->nMaxParameters = 2;
  HumanPlayerInput_ptParameterList = v2;
  ParameterList_AddParameter(v2, 0xF0u, v3, "Mapcomputer on expression", 7u, nullptr);
  ParameterList_AddParameter(
    HumanPlayerInput_ptParameterList,
    0x140u,
    Level_eParameterTypeVarString,
    "Mapcomputer unavailable expression",
    7u,
    nullptr);
  AppMain_FindPrefix(AppContext_tAppContext.zCmdLine, "Record:", HumanPlayerInput_ParseRecordCmdLineArgs);
  AppMain_FindPrefix(AppContext_tAppContext.zCmdLine, "Playback:", HumanPlayerInput_ParsePlaybackCmdLineArgs);
}

// source: j/0/human/humanplayerinput.c:814  [size]
void __cdecl HumanPlayerInput_Close()
{
  int v0; // esi

  if ( HumanPlayerInput_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&HumanPlayerInput_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(HumanPlayerInput_eQTaskType);
}

// source: j/0/human/humanplayerinput.c:832  [anchor-hash]
void __cdecl HumanPlayerInput_SetFreezeFire()
{
  if ( HumanPlayer_ptQTask )
    QTask_GetFirstChildOfType(HumanPlayer_ptQTask, HumanPlayerInput_eQTaskType)[23].tQTaskChildren.ptTail = (struct QTask_s *)1;
}
