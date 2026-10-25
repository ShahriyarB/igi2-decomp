/* j/0/network/client.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/network/client.c:82  [anchor-callee]
void __cdecl Client_ProjectWorldPos(
        struct real32x2_t *ptDest,
        float *pvDist,
        struct Human_s *ptHuman,
        struct real64x3_t *ptPos)
{
  #pragma pack(push, 1)
  union
  {
    struct { int nHeight; };
    struct { char igi2_o1[12]; double v13; };
    struct { char igi2_o2[20]; struct real64x3_t tViewPos; };
    struct { char igi2_o3[44]; struct real32x9_t tViewOrientation; };
    char igi2_extent[84];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  float *ptHumanViewQTask; // ebx
  int nWidth; // eax
  double v7; // st7
  double v8; // st6
  double v9; // st5
  double v10; // st7
  double v11; // st7
  float ptHumana = *(float *)&ptPos; // [esp+74h] [ebp+Ch] ARGSLOT

  ptHumanViewQTask = (float *)ptHuman->ptHumanViewQTask;
  if ( AppContext_tAppContext.isServer )
  {
    nWidth = 640;
    igi2_frame.nHeight = 480;
    ptHumana = 1.0;
  }
  else
  {
    nWidth = Display_tActiveMode.nWidth;
    igi2_frame.nHeight = Display_tActiveMode.nHeight;
    ptHumana = (double)Display_tActiveMode.nHeight * 4.0 / ((double)Display_tActiveMode.nWidth * 3.0);
  }
  qmemcpy(&igi2_frame.tViewPos, ptHumanViewQTask + 102, sizeof(igi2_frame.tViewPos));
  igi2_frame.v13 = (double)(nWidth / 2);
  qmemcpy(&igi2_frame.tViewOrientation, ptHumanViewQTask + 108, sizeof(igi2_frame.tViewOrientation));
  Real32x9_RotateAlpha(&igi2_frame.tViewOrientation, &igi2_frame.tViewOrientation, -1.5707963705062866);
  v7 = ptPos->vX - igi2_frame.tViewPos.vX;
  v8 = ptPos->vY - igi2_frame.tViewPos.vY;
  v9 = ptPos->vZ - igi2_frame.tViewPos.vZ;
  *(float *)&igi2_frame.tViewPos.vX = igi2_frame.tViewOrientation.tZ.vX * v9 + v8 * igi2_frame.tViewOrientation.tY.vX + v7 * igi2_frame.tViewOrientation.tX.vX;
  *((float *)&igi2_frame.tViewPos.vX + 1) = igi2_frame.tViewOrientation.tZ.vY * v9 + v8 * igi2_frame.tViewOrientation.tY.vY + v7 * igi2_frame.tViewOrientation.tX.vY;
  v10 = v9 * igi2_frame.tViewOrientation.tZ.vZ + v8 * igi2_frame.tViewOrientation.tY.vZ + v7 * igi2_frame.tViewOrientation.tX.vZ;
  *pvDist = v10;
  if ( v10 > 0.0 )
  {
    v11 = 1.0 / v10;
    ptDest->vX = *(float *)&igi2_frame.tViewPos.vX * v11 * igi2_frame.v13 / ptHumanViewQTask[162] + igi2_frame.v13;
    ptDest->vY = ptHumana * igi2_frame.v13 * *((float *)&igi2_frame.tViewPos.vX + 1) * v11 / ptHumanViewQTask[162] + (double)(igi2_frame.nHeight / 2);
  }
}

// source: j/0/network/client.c:165  [anchor-callee]
enum bool __cdecl Client_IsClientVisible(
        struct Client_s *ptClient1,
        struct Client_s *ptClient2)
{
  #pragma pack(push, 1)
  union
  {
    struct { int nWidth; };
    struct { char igi2_o1[4]; int nHeight; };
    struct { char igi2_o2[8]; float vDepth; };
    struct { char igi2_o3[12]; struct real32x2_t tScreenPos; };
    char igi2_extent[24];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Human_s *v2; // eax

  v2 = *(struct Human_s **)(ptClient1->tReceiveTimeBuffer.nCounter + 8);
  if ( AppContext_tAppContext.isServer )
  {
    igi2_frame.nWidth = 640;
    igi2_frame.nHeight = 480;
  }
  else
  {
    igi2_frame.nWidth = Display_tActiveMode.nWidth;
    igi2_frame.nHeight = Display_tActiveMode.nHeight;
  }
  Client_ProjectWorldPos(
    &igi2_frame.tScreenPos,
    &igi2_frame.vDepth,
    v2,
    (struct real64x3_t *)(*(_DWORD *)(ptClient2->tReceiveTimeBuffer.nCounter + 8) + 40));
  return igi2_frame.vDepth > 0.0
      && igi2_frame.tScreenPos.vX > 0.0
      && (double)igi2_frame.nWidth > igi2_frame.tScreenPos.vX
      && igi2_frame.tScreenPos.vY > 0.0
      && (double)igi2_frame.nHeight > igi2_frame.tScreenPos.vY;
}

// source: j/0/network/client.c:216  [anchor-callee]
int __cdecl Client_GetClientPriority(
        struct Client_s *ptDestination,
        struct Client_s *ptSource,
        float vThresholdRadius,
        float vThresholdViewDistance)
{
  int v4; // ecx
  int v5; // eax
  double v6; // st7
  double v7; // st6
  long double v8; // st5
  int v10; // ecx
  long double v11; // st6
  double v12; // [esp+8h] [ebp-Ch]

  v4 = *(_DWORD *)(ptDestination->tReceiveTimeBuffer.nCounter + 8);
  v5 = *(_DWORD *)(ptSource->tReceiveTimeBuffer.nCounter + 8);
  if ( !*(_BYTE *)(v5 + 1181) )
    return 0;
  if ( ptDestination->eNetworkIDSpectate == ptSource->eNetworkID )
    return 1;
  if ( !*(_BYTE *)(v4 + 1181) )
    return 0;
  v6 = *(double *)(v5 + 40) - *(double *)(v4 + 40);
  v7 = *(double *)(v5 + 48) - *(double *)(v4 + 48);
  v12 = *(double *)(v5 + 56) - *(double *)(v4 + 56);
  v8 = sqrt(v7 * v7 + v12 * v12 + v6 * v6);
  if ( v8 < vThresholdRadius )
    return 1;
  v10 = *(_DWORD *)(v4 + 1336);
  v11 = vThresholdViewDistance;
  if ( *(_DWORD *)(v10 + 664) )
    v11 = v11 / *(float *)(v10 + 648);
  return v8 < v11 && Client_IsClientVisible(ptDestination, ptSource);
}

// source: j/0/network/client.c:295  [anchor-callee]
int __cdecl Client_GetGlobalPriority(float vThresholdRadius, float vThresholdViewDistance)
{
  struct QTask_s *ptNetManagerQTask; // esi
  struct QTask_s *p_tQTask; // ebx
  struct Client_s *ClientFromNetworkID; // edi
  unsigned __int16 v5; // bp
  struct Client_s *v6; // eax
  int result; // eax
  struct QTask_s *v8; // [esp+10h] [ebp-4h]

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  p_tQTask = nullptr;
  v8 = ptNetManagerQTask;
  ClientFromNetworkID = NetManager_GetClientFromNetworkID((int)ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
  if ( ClientFromNetworkID )
  {
    v5 = Client_eQTaskType;
    while ( 1 )
    {
      v6 = (struct Client_s *)(p_tQTask
                             ? QTask_GetNextSiblingOfType(p_tQTask, v5)
                             : QTask_GetFirstChildOfType(ptNetManagerQTask, v5));
      p_tQTask = &v6->tQTask;
      if ( !v6 )
        break;
      if ( v6 != ClientFromNetworkID )
      {
        result = Client_GetClientPriority(v6, ClientFromNetworkID, vThresholdRadius, vThresholdViewDistance);
        if ( result == 1 )
          return result;
        ptNetManagerQTask = v8;
      }
    }
  }
  return 0;
}

// source: j/0/network/client.c:333  [anchor-mhash]
enum bool __cdecl Client_IsRemoteIdleFor(struct Client_s *ptClient, int nSeconds)
{
  struct HumanRemote_t *v2; // edi

  v2 = *(struct HumanRemote_t **)(ptClient->tReceiveTimeBuffer.nCounter + 8);
  if ( v2->tHuman.tBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.eQTaskType == HumanRemote_eQTaskType )
    return HumanRemote_IsIdleFor(v2, nSeconds);
  else
    return false;
}

// source: j/0/network/client.c:368  [anchor-strings]
void __cdecl Client_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s *ptNetManagerQTask; };
    struct { struct QTask_s *v34; };
    struct { float v35; };
    struct { char igi2_o3[4]; int *v36; };
    struct { char igi2_o4[8]; int v37; };
    struct { char igi2_o5[12]; struct WeaponTypeItem_s *WeaponTypeItemFromWeaponType; };
    struct { char igi2_o6[16]; struct QTask_s *ptTail; };
    struct { char igi2_o7[20]; char zText[256]; };
    char igi2_extent[276];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // edx
  BOOL v3; // eax
  char *v4; // ecx
  char *v5; // ecx
  char *v6; // eax
  char v7; // cl
  DWORD PerformanceCounter; // eax
  struct Flow_t *v9; // edx
  struct QTask_s *v10; // esi
  DWORD TickCount; // eax
  struct Flow_t *v12; // edx
  bool v13; // zf
  struct QTask_s *v14; // esi
  DWORD v15; // eax
  struct Flow_t *v16; // edx
  struct QTask_s *v17; // esi
  DWORD v18; // eax
  BOOL v19; // edx
  DWORD v20; // eax
  struct QTask_s *ptHead; // eax
  struct WeaponType_s *WeaponTypeFromID; // eax
  struct QTask_s *ptNext; // esi
  char *zWeaponScriptID; // edi
  int v25; // edi
  struct WeaponType_s *v26; // eax
  struct QTask_s *v27; // ecx
  double v28; // st7
  double v29; // st7
  struct QTask_s *v30; // eax
  struct QTask_s *v31; // edx
  struct QReference_s *v32; // eax

  igi2_frame.ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  ptQTask[1].ptNext = *((struct QTask_s **)pxContext + 1);
  ptQTask[1].ptPrev = (struct QTask_s *)-1;
  ptQTask[1].tQTaskRefList.ptHead = *((struct QReference_s **)pxContext + 2);
  ptQTask[1].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[1].tQTaskRefList.ptTail = (struct QReference_s *)1;
  LOBYTE(ptQTask[20].eQTaskType) = 0;
  v2 = *((_DWORD *)pxContext + 38);
  *(_DWORD *)&ptQTask[7].eQTaskType = v2;
  ptQTask[15].tQTaskChildren.ptMiddle = nullptr;
  if ( v2 >= 0 )
  {
    if ( v2 > 1000 )
    {
      NetManager_LogMessage("Bandwidth param out of range - clamped to 1000\n");
      *(_DWORD *)&ptQTask[7].eQTaskType = 1000;
    }
  }
  else
  {
    NetManager_LogMessage("Bandwidth param out of range - clamped to 0\n");
    *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  }
  v3 = ptQTask[1].ptNext == nullptr;
  ptQTask[1].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[1].ptParent = (struct QTask_s *)-1;
  *(_DWORD *)&ptQTask[1].eQTaskType = -1;
  ptQTask[1].tQTaskChildren.ptHead = (struct QTask_s *)v3;
  ptQTask[5].tQTaskRefList.ptMiddle = *(struct QReference_s **)pxContext;
  ptQTask[15].tQTaskRefList.ptHead = (struct QReference_s *)-1;
  ptQTask[15].tQTaskChildren.ptHead = (struct QTask_s *)ServerConfig_tServerConfig.nMoneyCap;
  v4 = *((char **)pxContext + 4);
  if ( v4 )
    strcpy((char *)&ptQTask[2], v4);
  else
    LOBYTE(ptQTask[2].ptNext) = 0;
  v5 = *((char **)pxContext + 5);
  if ( v5 )
  {
    strcpy((char *)&ptQTask[3].tQTaskRefList.ptMiddle, v5);
    v6 = (char *)pxContext + 24;
    do
    {
      v7 = *v6;
      v6[(char *)ptQTask - ((_BYTE *)pxContext + 24) + 208] = *v6;
      ++v6;
    }
    while ( v7 );
  }
  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  v9 = Flow_ptFlow;
  ptQTask[5].tQTaskRefList.ptTail = (struct QReference_s *)(PerformanceCounter - Timer_nStartTime);
  v10 = v9->ptNetManagerQTask;
  if ( Timer_isPerformanceCounter )
    TickCount = Timer_GetPerformanceCounter();
  else
    TickCount = GetTickCount();
  v12 = Flow_ptFlow;
  v13 = Timer_isPerformanceCounter == 0;
  ptQTask[5].ptParent = (struct QTask_s *)(TickCount
                                         - Timer_nStartTime
                                         + (char *)v10[6].tQTaskRefList.ptMiddle
                                         - (char *)v10[6].tQTaskRefList.ptTail);
  v14 = v12->ptNetManagerQTask;
  if ( v13 )
    v15 = GetTickCount();
  else
    v15 = Timer_GetPerformanceCounter();
  v16 = Flow_ptFlow;
  v13 = Timer_isPerformanceCounter == 0;
  *(_DWORD *)&ptQTask[5].eQTaskType = v15
                                    - Timer_nStartTime
                                    + (char *)v14[6].tQTaskRefList.ptMiddle
                                    - (char *)v14[6].tQTaskRefList.ptTail;
  v17 = v16->ptNetManagerQTask;
  if ( v13 )
    v18 = GetTickCount();
  else
    v18 = Timer_GetPerformanceCounter();
  ptQTask[6].ptNext = (struct QTask_s *)(v18
                                       - Timer_nStartTime
                                       + (char *)v17[6].tQTaskRefList.ptMiddle
                                       - (char *)v17[6].tQTaskRefList.ptTail);
  ptQTask[6].ptPrev = (struct QTask_s *)-1;
  LOBYTE(ptQTask[8].tQTaskChildren.ptTail) = 0;
  ptQTask[8].tQTaskRefList.ptHead = nullptr;
  ptQTask[8].ptNext = nullptr;
  ptQTask[8].ptPrev = nullptr;
  ptQTask[8].tQTaskChildren.ptHead = nullptr;
  ptQTask[15].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[15].ptParent = nullptr;
  *(_DWORD *)&ptQTask[15].eQTaskType = 0;
  ptQTask[16].ptNext = nullptr;
  v13 = LOBYTE(igi2_frame.ptNetManagerQTask[5].eQTaskType) == 0;
  ptQTask[15].tQTaskChildren.ptTail = (struct QTask_s *)-1;
  v19 = !v13;
  ptQTask[15].ptNext = (struct QTask_s *)-1;
  ptQTask[15].ptPrev = (struct QTask_s *)-1;
  v13 = Timer_isPerformanceCounter == 0;
  ptQTask[15].tQTaskRefList.ptTail = (struct QReference_s *)v19;
  if ( v13 )
    v20 = GetTickCount();
  else
    v20 = Timer_GetPerformanceCounter();
  ptQTask[1].tQTaskChildren.ptTail = (struct QTask_s *)(v20 - Timer_nStartTime);
  memset(&ptQTask[17].tQTaskChildren.ptTail, 0, 0x8Cu);
  Client_CreateHuman((struct Client_s *)ptQTask);
  ptHead = ptQTask[16].tQTaskChildren.ptHead;
  if ( ptHead )
  {
    igi2_frame.v34 = ptHead->tQTaskChildren.ptHead;
    igi2_frame.ptTail = igi2_frame.v34[33].tQTaskChildren.ptTail;
    LOBYTE(igi2_frame.v34[29].tQTaskRefList.ptHead) = *((_BYTE *)pxContext + 12);
    igi2_frame.v36 = (int *)((char *)pxContext + 96);
    igi2_frame.v37 = 13;
    do
    {
      WeaponTypeFromID = WeaponType_GetWeaponTypeFromID(*(igi2_frame.v36 - 13));
      if ( WeaponTypeFromID )
      {
        ptNext = igi2_frame.v34[33].ptNext;
        if ( ptNext )
        {
          zWeaponScriptID = WeaponTypeFromID->zWeaponScriptID;
          igi2_frame.WeaponTypeItemFromWeaponType = Weapon_GetWeaponTypeItemFromWeaponType(
                                           igi2_frame.v34[33].ptNext,
                                           WeaponTypeFromID->zWeaponScriptID);
          Weapon_EnableWeaponType(ptNext, zWeaponScriptID, true);
          if ( igi2_frame.WeaponTypeItemFromWeaponType )
            igi2_frame.WeaponTypeItemFromWeaponType->iActiveFireMode = *igi2_frame.v36;
        }
      }
      v13 = igi2_frame.v37 == 1;
      ++igi2_frame.v36;
      --igi2_frame.v37;
    }
    while ( !v13 );
    v25 = *((_DWORD *)pxContext + 10);
    if ( v25 != -1 )
    {
      v26 = WeaponType_GetWeaponTypeFromID(v25);
      if ( v26 )
      {
        v27 = igi2_frame.v34[33].ptNext;
        if ( v27 )
          Weapon_Activate(v27, v26->zWeaponScriptID, false);
      }
    }
    v28 = *((float *)pxContext + 37);
    igi2_frame.ptTail[16].tQTaskChildren.ptHead = *((struct QTask_s **)pxContext + 37);
    igi2_frame.v35 = tan(0.7853981852531433);
    v29 = v28 - igi2_frame.v35;
    if ( v29 < 0.0 )
      v29 = -v29;
    if ( v29 >= 0.0010000000474974513 )
    {
      igi2_frame.ptTail[16].tQTaskRefList.ptMiddle = (struct QReference_s *)1;
    }
    else
    {
      *(float *)&igi2_frame.ptTail[16].tQTaskChildren.ptHead = igi2_frame.v35;
      igi2_frame.ptTail[16].tQTaskRefList.ptMiddle = nullptr;
      *(float *)&igi2_frame.ptTail[16].tQTaskRefList.ptHead = tan(0.5235987901687622);
    }
  }
  v30 = StatusScreen_ptStatusScreenQTask;
  *((_DWORD *)&StatusScreen_ptStatusScreenQTask[49].tQTaskChildren.ptHead
  + *(_DWORD *)&StatusScreen_ptStatusScreenQTask[48].eQTaskType) = ptQTask;
  ++*(_DWORD *)&v30[48].eQTaskType;
  v31 = ptQTask[1].ptNext;
  ptQTask[16].tQTaskChildren.ptMiddle = (struct QTask_s *)-1;
  ptQTask[16].tQTaskChildren.ptTail = (struct QTask_s *)-1;
  ptQTask[6].tQTaskRefList.ptHead = (struct QReference_s *)v31;
  ptQTask[7].ptNext = nullptr;
  ptQTask[6].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[6].tQTaskRefList.ptTail = nullptr;
  ptQTask[6].ptParent = nullptr;
  *(_DWORD *)&ptQTask[6].eQTaskType = 0;
  ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[7].tQTaskRefList.ptHead = nullptr;
  ptQTask[7].tQTaskChildren.ptHead = nullptr;
  ptQTask[7].ptPrev = nullptr;
  *(float *)&ptQTask[16].tQTaskRefList.ptHead = (double)ServerConfig_tServerConfig.nViewPosRange * 4096.0;
  *(float *)&ptQTask[16].tQTaskRefList.ptMiddle = (double)ServerConfig_tServerConfig.nCloseFireRange * 4096.0;
  ptQTask[16].ptParent = (struct QTask_s *)-1;
  *(_DWORD *)&ptQTask[16].eQTaskType = -1;
  ptQTask[17].ptNext = (struct QTask_s *)-1;
  ptQTask[17].ptPrev = (struct QTask_s *)-1;
  ptQTask[17].tQTaskChildren.ptHead = (struct QTask_s *)-1;
  ptQTask[16].tQTaskRefList.ptTail = nullptr;
  if ( *((_BYTE *)pxContext + 13) )
  {
    Config_SetLocalizedPhrase(igi2_frame.zText, "mp/has_joined_the_game", (char *)&ptQTask[2], nullptr, nullptr);
    if ( StatusScreen_ptStatusScreenQTask )
    {
      v32 = StatusScreen_ptStatusScreenQTask[52].tQTaskRefList.ptTail;
      if ( v32 )
        TextScroller_Add((struct TextScroller_s *)v32, igi2_frame.zText, TEXTSCROLLER_COLOUR_RED);
    }
    NetManager_LogMessage(igi2_frame.zText);
    NetManager_LogMessage("\r\n");
  }
  ptQTask[17].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[16].ptPrev = nullptr;
}

// source: j/0/network/client.c:605  [anchor-strings]
struct Client_s *__cdecl Client_CancelTalk(struct Client_s *ptClient)
{
  int v1; // edi
  struct QTask_s *v2; // edx
  char *LocalizedStringForLanguage; // esi
  struct QReference_s *ptTail; // eax

  if ( ptClient->zTalkString[4] || ptClient->zTalkString[5] )
  {
    v1 = *(_DWORD *)(ptClient->tReceiveTimeBuffer.nCounter + 8);
    v2 = StatusScreen_ptStatusScreenQTask;
    ptClient->zTalkString[4] = 0;
    ptClient->zTalkString[5] = 0;
    *(_DWORD *)&ptClient->zTalkString[8] = 0;
    Text_SetString((struct StaticTilemap_s *)v2[28].tQTaskRefList.ptHead, (char *)&g_zInitialValue);
    Keyboard_tKeyboard.isLocked = 0;
    tKeyboardBuffer.iBufferIndex = 0;
    tKeyboardBuffer.nBuffer = 0;
    Keyboard_tKeyboard.anPreviousKey[1] = 0;
    Keyboard_tKeyboard.anCurrentKey[1] = 0;
    *(_DWORD *)(v1 + 832) = 1065353216;
    *(_DWORD *)(v1 + 580) = 1065353216;
    LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                   "mp/MESSAGE_CANCELED",
                                   Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                   true);
    if ( StatusScreen_ptStatusScreenQTask )
    {
      ptTail = StatusScreen_ptStatusScreenQTask[52].tQTaskRefList.ptTail;
      if ( ptTail )
        TextScroller_Add((struct TextScroller_s *)ptTail, LocalizedStringForLanguage, TEXTSCROLLER_COLOUR_RED);
    }
    NetManager_LogMessage(LocalizedStringForLanguage);
    NetManager_LogMessage("\r\n");
    ptClient = (struct Client_s *)MenuManager_ptQTask;
    if ( MenuManager_ptQTask )
    {
      if ( MenuManager_ptQTask[1].tQTaskChildren.ptMiddle == (struct QTask_s *)20 )
        MenuManager_ptQTask[1].tQTaskChildren.ptMiddle = MenuManager_ptQTask[1].tQTaskChildren.ptHead;
    }
  }
  return ptClient;
}

// source: j/0/network/client.c:648  [size]
void __cdecl Client_CancelLocalTalk()
{
  struct Client_s *ClientFromNetworkID; // eax

  ClientFromNetworkID = NetManager_GetClientFromNetworkID((int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
  if ( ClientFromNetworkID )
    Client_CancelTalk(ClientFromNetworkID);
}

// source: j/0/network/client.c:667  [anchor-strings]
void __cdecl Client_UpdateTalk(struct Client_s *ptClient)
{
  #pragma pack(push, 1)
  union
  {
    struct { char nLetter; };
    struct { char igi2_o1[1]; struct Human_s *ptHuman; };
    struct { char igi2_o2[5]; struct ClientGameMessageChat_s tChatMessage; };
    struct { char igi2_o3[277]; char zText[256]; };
    char igi2_extent[533];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char *LocalizedStringForLanguage; // ebx
  char *v2; // eax
  float *v3; // ecx
  char *v4; // edi
  char AsciiCode; // dl
  signed int v6; // edi
  struct QTask_s *v7; // eax
  signed int v8; // eax
  int v9; // eax
  enum TextScrollerColour_e v10; // ecx
  unsigned int v11; // eax
  char *v12; // edi
  char *v14; // edi
  char *v15; // esi
  char v16; // cl
  char v17; // al

  LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                 "mp/SAY_TEAM",
                                 Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                 true);
  v2 = Config_GetLocalizedStringForLanguage(
         "mp/SAY_ALL",
         Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
         true);
  v3 = *(float **)(ptClient->tReceiveTimeBuffer.nCounter + 8);
  v4 = v2;
  igi2_frame.ptHuman = (struct Human_s *)v3;
  if ( KeyboardBuffer_nSP <= 0 )
  {
    if ( v3[208] != 0.0 && v3[145] == 0.0 )
    {
      ptClient->zTalkString[4] = 1;
      sprintf(&ptClient->zTalkString[12], v2);
      Text_SetString(
        (struct StaticTilemap_s *)StatusScreen_ptStatusScreenQTask[28].tQTaskRefList.ptHead,
        &ptClient->zTalkString[12]);
      StatusScreen_SetTalkColour(1.0, 1.0, 1.0);
      *(_DWORD *)&ptClient->zTalkString[8] = strlen(v4);
      tKeyboardBuffer.iBufferIndex = 0;
      tKeyboardBuffer.nBuffer = 0;
      return;
    }
    if ( v3[209] != 0.0 && v3[146] == 0.0 )
    {
      ptClient->zTalkString[5] = 1;
      sprintf(&ptClient->zTalkString[12], LocalizedStringForLanguage);
      Text_SetString(
        (struct StaticTilemap_s *)StatusScreen_ptStatusScreenQTask[28].tQTaskRefList.ptHead,
        &ptClient->zTalkString[12]);
      StatusScreen_SetTalkColour(1.0, 1.0, 0.0);
      *(_DWORD *)&ptClient->zTalkString[8] = strlen(LocalizedStringForLanguage);
      tKeyboardBuffer.iBufferIndex = 0;
      tKeyboardBuffer.nBuffer = 0;
      return;
    }
    if ( ptClient->zTalkString[4] || ptClient->zTalkString[5] )
    {
      AsciiCode = KeyInterface_GetAsciiCode();
      igi2_frame.nLetter = AsciiCode;
      v6 = strlen(v4);
      Keyboard_tKeyboard.isLocked = 1;
      if ( ptClient->zTalkString[5] )
        v6 = strlen(LocalizedStringForLanguage);
      v7 = MenuManager_ptQTask;
      if ( MenuManager_ptQTask && MenuManager_ptQTask[1].tQTaskChildren.ptMiddle == (struct QTask_s *)3 )
      {
        MenuManager_ptQTask[1].tQTaskChildren.ptHead = (struct QTask_s *)3;
        v7[1].tQTaskChildren.ptMiddle = (struct QTask_s *)20;
      }
      switch ( AsciiCode )
      {
        case -8:
          goto LABEL_18;
        case -7:
          if ( *(_DWORD *)&ptClient->zTalkString[8] == v6 )
          {
LABEL_18:
            Client_CancelTalk(ptClient);
            return;
          }
          break;
        case -5:
          v8 = *(_DWORD *)&ptClient->zTalkString[8];
          if ( v8 == v6 )
            goto LABEL_18;
          if ( v8 > v6 )
            *(_DWORD *)&ptClient->zTalkString[8] = v8 - 1;
          ptClient->zTalkString[*(_DWORD *)&ptClient->zTalkString[8] + 12] = 0;
          break;
        default:
          if ( AsciiCode > 0 )
          {
            ptClient->zTalkString[*(_DWORD *)&ptClient->zTalkString[8] + 12] = AsciiCode;
            ptClient->zTalkString[*(_DWORD *)&ptClient->zTalkString[8] + 13] = 0;
            v9 = *(_DWORD *)&ptClient->zTalkString[8];
            if ( v9 < 191 )
              *(_DWORD *)&ptClient->zTalkString[8] = v9 + 1;
          }
          break;
      }
      if ( Flow_ptFlow->nTicks / 15 % 2 )
      {
        ptClient->zTalkString[*(_DWORD *)&ptClient->zTalkString[8] + 12] = 95;
        ptClient->zTalkString[*(_DWORD *)&ptClient->zTalkString[8] + 13] = 0;
      }
      else
      {
        ptClient->zTalkString[*(_DWORD *)&ptClient->zTalkString[8] + 12] = 0;
      }
      Text_SetString(
        (struct StaticTilemap_s *)StatusScreen_ptStatusScreenQTask[28].tQTaskRefList.ptHead,
        &ptClient->zTalkString[12]);
      if ( igi2_frame.nLetter == -7 )
      {
        ptClient->zTalkString[*(_DWORD *)&ptClient->zTalkString[8] + 12] = 0;
        igi2_frame.tChatMessage.isServerAnnounce = 0;
        sprintf(igi2_frame.zText, "%s: %s\n", ptClient->zPlayerName, &ptClient->zTalkString[v6 + 12]);
        igi2_frame.zText[254] = 0;
        if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
        {
          v10 = TEXTSCROLLER_COLOUR_YELLOW;
          if ( !ptClient->zTalkString[5] )
            v10 = TEXTSCROLLER_COLOUR_WHITE;
          StatusScreen_ShowMessage(igi2_frame.zText, v10);
        }
        igi2_frame.tChatMessage.tBaseMessage.eGameMessage = 1128808788;
        igi2_frame.tChatMessage.tBaseMessage.nLocalTime = NetManager_GetTimer();
        igi2_frame.tChatMessage.zString[0] = 0;
        v11 = strlen(igi2_frame.zText) + 1;
        v12 = (char *)&igi2_frame.tChatMessage.tBaseMessage.nLocalTime + 3;
        while ( *++v12 )
          ;
        qmemcpy(v12, igi2_frame.zText, 4 * (v11 >> 2));
        v15 = &igi2_frame.zText[4 * (v11 >> 2)];
        v14 = &v12[4 * (v11 >> 2)];
        v16 = v11;
        v17 = ptClient->zTalkString[5];
        qmemcpy(v14, v15, v16 & 3);
        if ( v17 )
          igi2_frame.tChatMessage.eTeam = ptClient->eTeam;
        else
          igi2_frame.tChatMessage.eTeam = -1;
        NetManager_SendGameMessage(0, ptClient->eNetworkID, NETWORKQUEUE_GUARANTEED, &igi2_frame.tChatMessage.tBaseMessage, 0x110u);
        ptClient->zTalkString[4] = 0;
        ptClient->zTalkString[5] = 0;
        *(_DWORD *)&ptClient->zTalkString[8] = 0;
        StatusScreen_SetTalkText((char *)&g_zInitialValue);
        Keyboard_tKeyboard.isLocked = 0;
        igi2_frame.ptHuman->avChannel[17] = 1.0;
        igi2_frame.ptHuman->avLastChannel[17] = 1.0;
        if ( MenuManager_ptQTask )
        {
          if ( MenuManager_ptQTask[1].tQTaskChildren.ptMiddle == (struct QTask_s *)20 )
            MenuManager_ptQTask[1].tQTaskChildren.ptMiddle = MenuManager_ptQTask[1].tQTaskChildren.ptHead;
        }
      }
    }
  }
}

// source: j/0/network/client.c:868  [anchor-mhash]
int __cdecl Client_ChangeMoney(struct Client_s *ptClient, int nDeltaMoney)
{
  int nUpdateItemTime; // ecx
  int nMoneyKill; // eax

  nUpdateItemTime = ptClient->nUpdateItemTime;
  nMoneyKill = nUpdateItemTime + nDeltaMoney;
  if ( nMoneyKill >= 0 )
  {
    if ( ServerConfig_tServerConfig.nMoneyKill < nMoneyKill )
      nMoneyKill = ServerConfig_tServerConfig.nMoneyKill;
    ptClient->nUpdateItemTime = nMoneyKill;
    return nUpdateItemTime != nMoneyKill;
  }
  else
  {
    ptClient->nUpdateItemTime = 0;
    return nUpdateItemTime != 0;
  }
}

// source: j/0/network/client.c:898  [anchor-callee]
int __cdecl Client_CostToSpawn(struct Client_s *ptClient)
{
  struct QTask_s *ptNetManagerQTask; // eax
  int v2; // ecx
  int v3; // esi
  int v4; // eax
  enum bool isSpectateFirstPerson; // ebx
  int v6; // edi
  int v7; // eax
  int result; // eax

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  v2 = ptClient->tDownload.nLastLoDown + 1;
  v3 = v2 * (int)ptNetManagerQTask[5].tQTaskChildren.ptMiddle;
  v4 = v2 * (int)ptNetManagerQTask[5].tQTaskChildren.ptHead;
  if ( ptClient->eTeam == NetMission_eDefendingTeam )
    v3 = (__int64)((double)v3 * 0.699999988079071);
  if ( *(_DWORD *)&ptClient->isTalk
    && v3 > 0
    && (isSpectateFirstPerson = ptClient->isSpectateFirstPerson,
        v6 = 1000 * v4,
        v7 = NetManager_GetTimer() - isSpectateFirstPerson,
        v7 <= v6) )
  {
    result = ((v3 - v3 * v7 / v6) % 100 < 50 ? 0 : 0x32) + 100 * ((v3 - v3 * v7 / v6) / 100);
    if ( result < 0 )
      return 0;
  }
  else
  {
    result = 0;
  }
  if ( v3 < result )
    return v3;
  return result;
}

// source: j/0/network/client.c:975  [anchor-strings]
void __cdecl Client_DebugSpawnInfo(char *zText, struct Client_s *ptClient)
{
  struct QTask_s *ptNetManagerQTask; // ebx
  int v3; // ebp
  DWORD PerformanceCounter; // eax
  struct QReference_s *ptMiddle; // esi
  struct QReference_s *ptTail; // ecx
  int v7; // ebx
  int v8; // esi
  int v9; // eax
  char Buffer[256]; // [esp+Ch] [ebp-100h] BYREF

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  v3 = *((_DWORD *)zText + 154);
  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  ptMiddle = ptNetManagerQTask[6].tQTaskRefList.ptMiddle;
  ptTail = ptNetManagerQTask[6].tQTaskRefList.ptTail;
  v7 = *((_DWORD *)zText + 81);
  v8 = PerformanceCounter - Timer_nStartTime + ((char *)ptMiddle - (char *)ptTail) - v3;
  v9 = Client_CostToSpawn((struct Client_s *)zText);
  _snprintf(
    Buffer,
    0xFFu,
    "SpawnInfo: %s: nID=%d, sinceDead=%d, nDeaths=%d, cost=%d\n",
    (char *)ptClient,
    *((_DWORD *)zText + 10),
    v8,
    v7,
    v9);
  NetManager_LogMessage(Buffer);
}

// source: j/0/network/client.c:1011  [anchor-callee]
enum bool __cdecl Client_isSpawnAffordable(struct Client_s *ptClient, int ltcg_esi)
{
  return Client_CostToSpawn((struct Client_s *)ltcg_esi) <= (int)(*(_DWORD *)(ltcg_esi + 608));
}

// source: j/0/network/client.c:1098  [size]
enum bool __cdecl Client_IsDeathSequenceOver(struct Client_s *ptClient)
{
  struct QTask_s *ptNetManagerQTask; // esi
  int v3; // edi
  DWORD PerformanceCounter; // eax
  __int16 v5; // cx
  enum bool result; // eax

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  v3 = *(_DWORD *)(ptClient->tReceiveTimeBuffer.nCounter + 8);
  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  v5 = *(_WORD *)(v3 + 36);
  result = (int)(PerformanceCounter
               - Timer_nStartTime
               + (char *)ptNetManagerQTask[6].tQTaskRefList.ptMiddle
               - ptClient->isSpectateFirstPerson
               - (char *)ptNetManagerQTask[6].tQTaskRefList.ptTail) > 5000;
  if ( v5 == HumanRemote_eQTaskType )
    return (*(_BYTE *)(v3 + 3268) == 0) | result;
  if ( v5 == HumanPlayer_eQTaskType )
    return (*(_BYTE *)(v3 + 3216) == 0) | result;
  return result;
}

// source: j/0/network/client.c:1138  [size~]
void __cdecl Client_UpdateWorldRegister(struct Client_s *ptClient)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct World_s *ptWorld; };
    struct { char igi2_o1[4]; _DWORD v6[3]; };
    char igi2_extent[16];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v1; // esi
  struct QTask_s *v2; // edi
  int v3; // edx
  int v4; // ecx

  v1 = *(_DWORD *)(ptClient->tReceiveTimeBuffer.nCounter + 8);
  v2 = HumanPlayer_ptQTask;
  if ( *(_BYTE *)(v1 + 1180) )
  {
    if ( *(_BYTE *)(v1 + 1181) )
    {
      if ( ptClient->isSpectateFirstPerson != -1 )
      {
        if ( Client_IsDeathSequenceOver(ptClient) )
        {
          v3 = *(unsigned __int16 *)(v1 + 36);
          igi2_frame.ptWorld = Game_ptGame->ptWorld;
          ((void (__cdecl *)(int, struct World_s **))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRemoveQTaskEvent][v3].pfHandler)(
            v1,
            &igi2_frame.ptWorld);
          if ( (struct QTask_s *)v1 == v2 )
            LOBYTE(v2[80].tQTaskChildren.ptTail) = 0;
        }
      }
    }
  }
  if ( !*(_BYTE *)(v1 + 1180) && !*(_BYTE *)(v1 + 1181) )
  {
    igi2_frame.v6[0] = 0;
    igi2_frame.v6[2] = 2;
    v4 = *(unsigned __int16 *)(v1 + 36);
    igi2_frame.v6[1] = Game_ptGame->ptWorld;
    ((void (__cdecl *)(int, _DWORD *))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRegisterQTaskEvent][v4].pfHandler)(
      v1,
      igi2_frame.v6);
    if ( (struct QTask_s *)v1 == v2 )
      LOBYTE(v2[80].tQTaskChildren.ptTail) = 1;
  }
}

// source: j/0/network/client.c:1197  [anchor-callee]
int __cdecl Client_GetAveTimeBetweenUpdates(struct Client_s *ptClient)
{
  int v1; // eax
  struct QReference_s **i; // ecx

  v1 = 0;
  for ( i = &ptClient->ptTimebasedActionSoundQTaskRef; *i != (struct QReference_s *)-1; ++i )
  {
    if ( ++v1 >= 5 )
      return (ptClient->tReceiveTimeBuffer.aReceiveTime[ptClient->tReceiveTimeBuffer.aReceiveTime[4]
                                                      + 4
                                                      + (ptClient->tReceiveTimeBuffer.aReceiveTime[4] - 1 < 0 ? 5 : 0)]
            - *((_DWORD *)&ptClient->ptTimebasedActionSoundQTaskRef + ptClient->tReceiveTimeBuffer.aReceiveTime[4]))
           / 4;
  }
  return -1;
}

// source: j/0/network/client.c:1244  [anchor-strings]
void __cdecl Client_PrintToConsole(struct Client_s *ptClient)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDestination; };
    struct { char igi2_o1[4]; float ptSource; };
    struct { char igi2_o2[24]; int LowDelay; };
    struct { char igi2_o3[28]; int HighDelay; };
    struct { char igi2_o4[32]; int nObjectives; };
    struct { char igi2_o5[36]; int AveTimeBetweenUpdates; };
    struct { char igi2_o6[40]; char v18[8]; };
    char igi2_extent[48];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char v2; // bl
  struct QTask_s *ptMiddle; // esi
  struct Client_s *ClientFromNetworkID; // eax
  int eNetworkID; // edi
  struct Node_s *ptHead; // ecx
  struct Node_s *ptNext; // eax
  struct Client_s *v8; // edx
  int v9; // esi
  int LastReceivedTimeFromNetworkID; // edi
  DWORD PerformanceCounter; // eax
  struct Client_s *ptClienta = *(struct Client_s * *)&ptClient; // [esp+34h] [ebp+4h] ARGSLOT

  if ( Timer_isPerformanceCounter )
    Timer_GetPerformanceCounter();
  else
    GetTickCount();
  igi2_frame.AveTimeBetweenUpdates = Client_GetAveTimeBetweenUpdates(ptClient);
  igi2_frame.nObjectives = ptClient->tStats.nObjectives;
  v2 = 45;
  igi2_frame.HighDelay = Client_GetHighDelay(ptClient);
  igi2_frame.LowDelay = Client_GetLowDelay(ptClient);
  DebugConsole_PushActiveConsole(NetworkInfo_tFrameInfoConsoleID);
  ptMiddle = Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle;
  if ( !ptMiddle && ptClient->eNetworkID )
  {
    ClientFromNetworkID = NetManager_GetClientFromNetworkID(0);
    if ( ClientFromNetworkID )
    {
      igi2_frame.ptSource = (double)ServerConfig_tServerConfig.nCloseFireRange * 4096.0;
      igi2_frame.ptDestination = (double)ServerConfig_tServerConfig.nViewPosRange * 4096.0;
      ptMiddle = nullptr;
      v2 = Client_GetClientPriority(ClientFromNetworkID, ptClient, igi2_frame.ptDestination, igi2_frame.ptSource) != 0 ? 72 : 76;
    }
    else
    {
      v2 = 78;
    }
  }
  eNetworkID = ptClient->eNetworkID;
  if ( (struct QTask_s *)eNetworkID == ptMiddle )
  {
    DebugConsole_printf(
      "L:%c[%d]%s:[posdt= %d ms][b %d %d-%d]\n",
      v2,
      eNetworkID,
      ptClient->zPlayerName,
      igi2_frame.AveTimeBetweenUpdates,
      igi2_frame.nObjectives,
      igi2_frame.HighDelay,
      igi2_frame.LowDelay);
  }
  else
  {
    ptHead = Network_atQueues[0].tList.ptHead;
    strcpy(igi2_frame.v18, "----");
    ptNext = Network_atQueues[0].tList.ptHead->ptNext;
    v8 = nullptr;
    ptClienta = nullptr;
    if ( Network_atQueues[0].tList.ptHead->ptNext )
    {
      do
      {
        if ( ptHead[1].ptNext == (struct Node_s *)eNetworkID )
          v8 = (struct Client_s *)((char *)v8 + 1);
        ptHead = ptNext;
        ptNext = ptNext->ptNext;
      }
      while ( ptNext );
      ptClienta = v8;
    }
    v9 = Network_NumberOfWaitingFromHost(eNetworkID);
    LastReceivedTimeFromNetworkID = NetManager_GetLastReceivedTimeFromNetworkID(eNetworkID);
    if ( Timer_isPerformanceCounter )
      PerformanceCounter = Timer_GetPerformanceCounter();
    else
      PerformanceCounter = GetTickCount();
    DebugConsole_printf(
      "R:%c[%d]%s:[pdt=%3d ms][since=%3d][%s][g_o %d][g_i %d][b %d %d-%d]\n",
      v2,
      ptClient->eNetworkID,
      ptClient->zPlayerName,
      igi2_frame.AveTimeBetweenUpdates,
      PerformanceCounter - Timer_nStartTime - LastReceivedTimeFromNetworkID,
      igi2_frame.v18,
      ptClienta,
      v9,
      igi2_frame.nObjectives,
      igi2_frame.HighDelay,
      igi2_frame.LowDelay);
  }
  DebugConsole_PopActiveConsole();
}

// source: j/0/network/client.c:1379  [anchor-strings]
void __cdecl Client_RunHandler(struct QTask_s *ptQTask)
{
  DWORD PerformanceCounter; // eax
  struct QReference_s *v2; // edi
  struct QTask_s *ptParent; // eax
  struct QReference_s *ptHead; // ecx
  int v5; // eax
  int v6; // edi
  char *v7; // ecx

  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  v2 = (struct QReference_s *)(PerformanceCounter - Timer_nStartTime);
  Client_UpdateWorldRegister((struct Client_s *)ptQTask);
  ptParent = ptQTask[15].ptParent;
  if ( (int)ptParent > 0 )
    ptQTask[15].ptParent = (struct QTask_s *)((char *)ptParent - 1);
  if ( !Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    if ( ptQTask[1].ptNext )
    {
      ptHead = ptQTask[15].tQTaskRefList.ptHead;
      if ( ptHead == (struct QReference_s *)-1 || (char *)v2 - (char *)ptHead > 3000 )
      {
        NetworkGameItem_SendAllGameItemStates((int)ptQTask[1].ptNext);
        ptQTask[15].tQTaskRefList.ptHead = v2;
      }
    }
  }
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle == ptQTask[1].ptNext )
  {
    v5 = Client_CostToSpawn((struct Client_s *)ptQTask);
    v6 = v5;
    if ( v5 > 0 && v5 != dword_834DDA4 )
    {
      v7 = "respawn_01";
      if ( (int)ptQTask[15].tQTaskChildren.ptHead >= v5 )
        v7 = "respawn_02";
      SoundSys_PlaySimpleSoundFn(v7, 0, nullptr);
    }
    dword_834DDA4 = v6;
  }
  Client_PrintToConsole((struct Client_s *)ptQTask);
}

// source: j/0/network/client.c:1452  [size]
struct ClientDR_t *__cdecl Client_GetDR(struct Client_s *ptClient, int eNetworkID)
{
  return ptClient->anDR[eNetworkID + 5];
}

// source: j/0/network/client.c:1476  [anchor-mhash]
struct ClientDR_t *__cdecl Client_GetCreateDR(struct Client_s *ptClient, int eNetworkID)
{
  struct ClientDR_t *result; // eax

  result = ptClient->anDR[eNetworkID + 5];
  if ( !result )
  {
    result = (struct ClientDR_t *)Mem_AllocFn(120, 4);
    ptClient->anDR[eNetworkID + 5] = result;
  }
  return result;
}

// source: j/0/network/client.c:1513  [anchor-strings]
void __cdecl Client_FreeIfExistsDR(struct Client_s *ptClient, int eNetworkID)
{
  struct ClientDR_t *v2; // eax
  int v3; // esi
  char zTemp[256]; // [esp+4h] [ebp-100h] BYREF

  if ( ptClient->anDR[eNetworkID + 5] )
  {
    if ( ptClient->eNetworkID == eNetworkID )
    {
      _snprintf(zTemp, 0xFFu, "Client_FreeDR: Found DR data to self[%d]\n", eNetworkID);
      NetManager_LogMessage(zTemp);
    }
    if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
      NetManager_LogMessage("Client_FreeDR: Found DR data on a client host\n");
    v2 = ptClient->anDR[eNetworkID + 5];
    if ( v2 )
    {
      v3 = *(_DWORD *)((unsigned int)&v2[-1].vAlpha & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v3);
      memset(*(void **)(v3 + 8), 0xCDu, *(_DWORD *)(v3 + 16));
      free((void *)v3);
    }
    ptClient->anDR[eNetworkID + 5] = nullptr;
  }
}

// source: j/0/network/client.c:1557  [anchor-mhash]
struct Client_s *__cdecl Client_UpdateDR(
        struct Client_s *ptDestination,
        struct Client_s *ptSource,
        struct ClientGameMessageUpdateBody_s *ptBody)
{
  int eNetworkID; // esi
  struct Client_s *result; // eax

  eNetworkID = ptSource->eNetworkID;
  result = (struct Client_s *)ptDestination->anDR[eNetworkID + 5];
  if ( !result )
  {
    result = (struct Client_s *)Mem_AllocFn(120, 4);
    ptDestination->anDR[eNetworkID + 5] = (struct ClientDR_t *)result;
  }
  return result;
}

// source: j/0/network/client.c:1584  [size]
enum bool __cdecl Client_IsDRDifference(struct Client_s *ptDestination, struct Client_s *ptSource)
{
  return true;
}

// source: j/0/network/client.c:1605  [anchor-strings]
void __cdecl Client_DeleteHandler(struct QTask_s *ptQTask)
{
  int ptNext; // edi
  struct QTask_s *ptMiddle; // eax
  int v3; // ebx
  struct QTask_s *ptHead; // eax
  struct QTask_s *v5; // ebp
  char Buffer[256]; // [esp+Ch] [ebp-100h] BYREF

  ptNext = (int)ptQTask[1].ptNext;
  _snprintf(Buffer, 0xFFu, "Client_Deletehandler: Removing [%d]%s\n", ptNext, (char *)&ptQTask[2]);
  NetManager_LogMessage(Buffer);
  ptMiddle = ptQTask[17].tQTaskChildren.ptMiddle;
  v3 = 0;
  if ( ptMiddle )
  {
    QReference_Delete((struct QReference_s *)ptMiddle, &QTask_tQTaskRefPool);
    ptQTask[17].tQTaskChildren.ptMiddle = nullptr;
  }
  ptHead = ptQTask[16].tQTaskChildren.ptHead;
  if ( ptHead )
  {
    v5 = ptHead->tQTaskChildren.ptHead;
    StatusScreen_RemoveScoreClient((struct Client_s *)ptQTask);
    if ( v5 )
      QTask_Delete(v5);
    QReference_Delete((struct QReference_s *)ptQTask[16].tQTaskChildren.ptHead, &QTask_tQTaskRefPool);
    ptQTask[16].tQTaskChildren.ptHead = nullptr;
  }
  --BYTE1(Flow_ptFlow->ptNetManagerQTask[3].ptPrev);
  if ( Network_RemoveIDItemFromID(ptNext) )
    _snprintf(Buffer, 0xFFu, "Client_DeleteHandler: Removed from network queues,id=%d\n", ptNext);
  else
    _snprintf(Buffer, 0xFFu, "Client_DeleteHandler: Tried removed but not found in network queues,id=%d\n", ptNext);
  NetManager_LogMessage(Buffer);
  Network_FreeQueuesTo(ptNext);
  if ( !Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    gcd_disconnect_user(ptNext);
    NetManager_LogMessage("Client sent disconnect to CD auth\n");
    if ( ptNext )
      Server_PushFreeNID(ptNext, true);
  }
  Network_nGuaranteedPacketID[ptNext] = 1;
  Network_nLastReceivedGuaranteedPacketID[ptNext] = 0;
  do
    Client_FreeIfExistsDR((struct Client_s *)ptQTask, v3++);
  while ( v3 < 35 );
}

// source: j/0/network/client.c:1689  [anchor-strings]
struct Client_s *__cdecl Client_FillGameMessageUpdate(
        struct Client_s *ptClient,
        struct ClientGameMessageUpdateBody_s *ptBody)
{
  int nCounter; // eax
  struct HumanRemote_t *v4; // eax
  unsigned __int16 eQTaskType; // cx
  struct Client_s *result; // eax

  ptBody->eNetworkID = ptClient->eNetworkID;
  nCounter = ptClient->tReceiveTimeBuffer.nCounter;
  if ( !nCounter )
  {
    LDebug_Error("No human attached to client");
LABEL_7:
    abort();
  }
  v4 = *(struct HumanRemote_t **)(nCounter + 8);
  eQTaskType = v4->tHuman.tBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.eQTaskType;
  if ( eQTaskType == HumanRemote_eQTaskType )
  {
    HumanRemote_FillGameMessageUpdate(v4, ptBody);
    return result;
  }
  if ( eQTaskType != HumanPlayer_eQTaskType )
  {
    LDebug_Error("Unknown human type");
    goto LABEL_7;
  }
  return (struct Client_s *)HumanPlayer_FillGameMessageUpdate((struct HumanPlayer_t *)v4, ptBody);
}

// source: j/0/network/client.c:1739  [anchor-strings]
int __cdecl Client_HandleUpdate(
        struct Client_s *ptClient,
        struct ClientGameMessageUpdateBody_s *ptBody,
        int nLocalTime,
        int nRemoteTime)
{
  struct HumanRemote_t *v4; // esi
  int v5; // edx
  int AveTimeBetweenUpdates; // eax

  if ( nRemoteTime >= ptClient->nLastUpdateReceivedRemote )
  {
    v4 = *(struct HumanRemote_t **)(ptClient->tReceiveTimeBuffer.nCounter + 8);
    v5 = ptClient->tReceiveTimeBuffer.aReceiveTime[4];
    ptClient->nLastUpdateReceivedLocal = nLocalTime;
    ptClient->nLastUpdateReceivedRemote = nRemoteTime;
    *((_DWORD *)&ptClient->ptTimebasedActionSoundQTaskRef + v5) = nLocalTime;
    ptClient->tReceiveTimeBuffer.aReceiveTime[4] = (ptClient->tReceiveTimeBuffer.aReceiveTime[4] + 1) % 5;
    if ( v4->tHuman.tBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.eQTaskType != HumanRemote_eQTaskType )
    {
      LDebug_Error("No human remote attached to remote client");
      abort();
    }
    AveTimeBetweenUpdates = Client_GetAveTimeBetweenUpdates(ptClient);
    if ( AveTimeBetweenUpdates <= 0 )
      AveTimeBetweenUpdates = 90;
    return HumanRemote_HandleUpdate(v4, ptBody, nRemoteTime, AveTimeBetweenUpdates);
  }
  return nLocalTime;
}

// source: j/0/network/client.c:1789  [anchor-strings]
void __cdecl Client_GameMessageActivateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s **v2; // ebx
  unsigned int v3; // eax
  struct QTask_s *ptHead; // ecx
  struct QTask_s *v6; // edx
  struct QReference_s *v7; // eax
  void *pxObject; // edi
  struct QTask_s *ptNext; // eax
  _DWORD *p_ptMiddle; // esi
  struct QTask_s *v11; // eax
  struct QTask_s *v12; // ebp
  struct QTask_s *v13; // eax
  struct QTask_s *v14; // eax
  struct QTask_s *v15; // eax
  struct QTask_s *v16; // eax
  struct QTask_s *v17; // eax
  struct QTask_s *v18; // ebp
  struct QTask_s *v19; // ebp
  struct QTask_s *ptQTaska = *(struct QTask_s * *)&ptQTask; // [esp+14h] [ebp+4h] ARGSLOT

  v2 = *((struct QTask_s ***)pxContext + 3);
  v3 = (unsigned int)v2[5];
  ptHead = ptQTask[16].tQTaskChildren.ptHead;
  v6 = ptHead->tQTaskChildren.ptHead;
  ptQTaska = v6;
  if ( v3 < 0x1000 && (v7 = Level_atLevelQTaskID[v3]) != nullptr )
    pxObject = v7->pxObject;
  else
    pxObject = nullptr;
  ptNext = ptQTask[1].ptNext;
  if ( ptNext == *v2
    || v2[4] == (struct QTask_s *)14 && ptNext == Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    if ( ptHead && v6->eQTaskType == HumanRemote_eQTaskType )
      v6[82].ptPrev = v2[7];
    p_ptMiddle = &ptQTask[17].tQTaskChildren.ptMiddle;
    QTask_DeleteQTaskAndQTaskRefSafe((struct QReference_s **)&ptQTask[17].tQTaskChildren.ptMiddle);
    switch ( (unsigned int)v2[4] )
    {
      case 1u:
        Switch_Pressed((struct QTask_s *)pxObject, (int)v2[6]);
        break;
      case 2u:
        if ( v2[7] == (struct QTask_s *)1 )
        {
          v12 = ptQTask[16].tQTaskChildren.ptHead;
          if ( v12 )
            v13 = v12->tQTaskChildren.ptHead;
          else
            v13 = nullptr;
          *((_BYTE *)pxObject + 939) = 1;
          if ( v13 )
          {
            Door_ToggleOpenDoorEx((struct QTask_s *)pxObject, (struct real64x3_t *)&v13[1]);
          }
          else
          {
            *((_BYTE *)pxObject + 942) ^= 1u;
            *((_BYTE *)pxObject + 941) = 1;
          }
        }
        else
        {
          v14 = SoundSys_NewSoundFn(ptQTaska, (char *)pxObject + 532);
          *p_ptMiddle = QTask_NewQTaskRef(v14);
        }
        break;
      case 4u:
        if ( v2[7] == (struct QTask_s *)1 )
        {
          *((_DWORD *)pxObject + 191) = v2[6];
          *((_DWORD *)pxObject + 188) = 1;
        }
        else
        {
          v15 = SoundSys_NewSoundFn(ptQTaska, (char *)pxObject + 632);
          *p_ptMiddle = QTask_NewQTaskRef(v15);
        }
        break;
      case 8u:
        v18 = ptQTask[16].tQTaskChildren.ptHead;
        if ( v18 )
          v19 = v18->tQTaskChildren.ptHead;
        else
          v19 = nullptr;
        if ( v19->eQTaskType == HumanRemote_eQTaskType )
          v19[82].tQTaskChildren.ptHead = v2[7];
        break;
      case 0xAu:
        if ( v2[7] == (struct QTask_s *)1 )
        {
          *((_DWORD *)pxObject + 207) = v2[6];
          *((_DWORD *)pxObject + 204) = 1;
        }
        else
        {
          v16 = SoundSys_NewSoundFn(ptQTaska, (char *)pxObject + 681);
          *p_ptMiddle = QTask_NewQTaskRef(v16);
        }
        break;
      case 0xBu:
        if ( v2[7] != (struct QTask_s *)1 )
        {
          v17 = SoundSys_NewSoundFn(ptQTaska, "tba_placec4_2");
          *p_ptMiddle = QTask_NewQTaskRef(v17);
        }
        break;
      case 0xEu:
        v11 = v2[6];
        *((_DWORD *)pxObject + 44) = v2[7];
        *((_DWORD *)pxObject + 48) = v11;
        break;
      default:
        return;
    }
  }
}

// source: j/0/network/client.c:1956  [anchor-strings]
void __cdecl Client_GameMessageSettingsHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v3; // edi
  struct QTask_s *ptNext; // eax
  struct QTask_s *v5; // ecx
  int v6; // edi
  struct Human_s *ptHead; // ebx
  int v8; // eax
  int v9; // edx
  int eQTaskType; // edx
  char Buffer[16]; // [esp+8h] [ebp-10h] BYREF
  struct QTask_s *ptQTaska = *(struct QTask_s * *)&ptQTask; // [esp+1Ch] [ebp+4h] ARGSLOT

  v3 = *((_DWORD *)pxContext + 3);
  ptNext = ptQTask[1].ptNext;
  v5 = *(struct QTask_s **)(v3 + 16);
  v6 = v3 + 8;
  if ( ptNext == v5 )
  {
    ptHead = (struct Human_s *)ptQTask[16].tQTaskChildren.ptHead->tQTaskChildren.ptHead;
    if ( ptNext == Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle
      && ptQTask[1].tQTaskRefList.ptHead != *(struct QReference_s **)(v6 + 12) )
    {
      NetManager_SetTeam(*(_DWORD *)(v6 + 12));
      NetManager_ForceSpawnMode();
    }
    v8 = *(_DWORD *)(v6 + 12);
    v9 = *(_DWORD *)(v6 + 16);
    if ( v8 )
    {
      if ( v8 == 1 )
        sprintf(Buffer, "%s%d_1", NetManager_atBadModel[v9].pzModel, *(_DWORD *)(v6 + 20));
    }
    else
    {
      sprintf(Buffer, "%s%d_1", NetManager_atGoodModel[v9].pzModel, *(_DWORD *)(v6 + 20));
    }
    if ( strncmp((char *)&ptQTask[5].tQTaskChildren, Buffer, 0x10u) )
    {
      eQTaskType = ptHead->tBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.eQTaskType;
      ptQTaska = HumanPlayer_ptQTask;
      pxContext = Game_ptGame->ptWorld;
      ((void (__cdecl *)(struct Human_s *, void **))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRemoveQTaskEvent][eQTaskType].pfHandler)(
        ptHead,
        &pxContext);
      if ( ptHead == (struct Human_s *)ptQTaska )
        LOBYTE(ptQTaska[80].tQTaskChildren.ptTail) = 0;
    }
    ptQTask[1].tQTaskRefList.ptHead = *(struct QReference_s **)(v6 + 12);
    ptQTask[1].tQTaskRefList.ptMiddle = *(struct QReference_s **)(v6 + 16);
    Weapon_ClearAllWeapons(ptHead->ptWeaponQTask);
    Weapon_EnableWeaponType(ptHead->ptWeaponQTask, "WEAPON_ID_KNIFE", true);
    if ( ptQTask[1].tQTaskRefList.ptHead == (struct QReference_s *)1 )
      Weapon_EnableWeaponType(ptHead->ptWeaponQTask, "WEAPON_ID_MAKAROV", true);
    else
      Weapon_EnableWeaponType(ptHead->ptWeaponQTask, "WEAPON_ID_GLOCK", true);
    strncpy((char *)&ptQTask[5].tQTaskChildren, Buffer, 0x10u);
    strncpy((char *)&ptQTask[2], (char *)(v6 + 24), 0x40u);
    strncpy(
      (char *)&ptQTask[3].tQTaskRefList.ptMiddle,
      NetManager_atTeams[(int)ptQTask[1].tQTaskRefList.ptHead].pzName,
      0x40u);
    Human_SetTeam(ptHead, (int)ptQTask[1].tQTaskRefList.ptHead, (char *)&ptQTask[5].tQTaskChildren);
  }
}

// source: j/0/network/client.c:2061  [size]
int __cdecl Client_GetModel(struct Client_s *ptClient)
{
  return ptClient->eModel;
}

// source: j/0/network/client.c:2078  [anchor-caller]
void __cdecl Client_GameMessageEquipHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct GunPickupContext_t tContext; };
    struct { char igi2_o1[24]; char zTemp[256]; };
    char igi2_extent[280];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // ebp
  struct QTask_s *v3; // ecx
  struct QTask_s *ptHead; // ebx
  struct QTask_s *ptNext; // eax
  int v6; // ebp
  char v7; // al
  struct QTask_s *ptPrev; // eax
  int v9; // edi
  struct QTask_s *v10; // eax
  struct QTask_s *v11; // esi
  int v12; // eax
  struct WeaponType_s *WeaponTypeFromID; // esi
  struct WeaponType_s *NextEnabledWeaponTypeFromCategory; // eax
  int v15; // ecx
  int v16; // ebp
  struct WeaponType_s *v17; // edi
  struct QTask_s *v18; // eax
  int v19; // eax
  struct QTask_s *v20; // ecx

  v2 = *((_DWORD *)pxContext + 3);
  v3 = *(struct QTask_s **)(v2 + 28);
  ptHead = ptQTask[16].tQTaskChildren.ptHead->tQTaskChildren.ptHead;
  ptNext = ptQTask[1].ptNext;
  v6 = v2 + 8;
  if ( ptNext == v3 )
  {
    _snprintf(
      igi2_frame.zTemp,
      0xFFu,
      "Client_EquipHandler[%d] got pickuptype=%d, pickupid=%d,ammo=%d\n",
      ptNext,
      *(unsigned __int8 *)(v6 + 8),
      *(_DWORD *)(v6 + 12),
      *(_DWORD *)(v6 + 16));
    NetManager_LogMessage(igi2_frame.zTemp);
    v7 = *(_BYTE *)(v6 + 8);
    if ( v7 )
    {
      if ( v7 != 1 )
      {
        LDebug_Error("Unknown pickuptype");
        abort();
      }
      v19 = *(_DWORD *)(v6 + 16);
      v20 = ptQTask[16].tQTaskChildren.ptHead;
      igi2_frame.tContext.nAmmoInClip = *(_DWORD *)(v6 + 12);
      igi2_frame.tContext.anAmmoForFiretype[0] = v19;
      igi2_frame.tContext.anAmmoForFiretype[1] = 1;
      ((void (__cdecl *)(struct QTask_s *, struct GunPickupContext_t *))QTask_aatQTaskFinalEvent[AmmoPickup_eAmmoPickupQTaskEvent][v20->tQTaskChildren.ptHead->eQTaskType].pfHandler)(
        v20->tQTaskChildren.ptHead,
        &igi2_frame.tContext);
    }
    else if ( ptHead != HumanPlayer_ptQTask
           || LOBYTE(ptHead[29].tQTaskRefList.ptHead)
           || (ptPrev = ptHead[33].ptNext[1].ptPrev) == nullptr
           || !ptPrev->tQTaskChildren.ptTail
           || (v9 = *(_DWORD *)(v6 + 12),
               ptPrev->tQTaskChildren.ptTail[3].tQTaskRefList.ptTail == (struct QReference_s *)v9)
           || !strcmp(WeaponType_GetWeaponTypeFromID(v9)->zWeaponScriptID, (char *)&g_zSoundDefPrefix.eQTaskType) )
    {
      WeaponTypeFromID = WeaponType_GetWeaponTypeFromID(*(_DWORD *)(v6 + 12));
      NextEnabledWeaponTypeFromCategory = Weapon_GetNextEnabledWeaponTypeFromCategory(
                                            ptHead[33].ptNext,
                                            WeaponTypeFromID->eWeaponCategory,
                                            nullptr);
      v15 = *(_DWORD *)(v6 + 12);
      v16 = *(_DWORD *)(v6 + 16);
      v17 = NextEnabledWeaponTypeFromCategory;
      igi2_frame.tContext.isExternalAdd = true;
      igi2_frame.tContext.anAmmoForFiretype[1] = 1;
      v18 = ptQTask[16].tQTaskChildren.ptHead;
      igi2_frame.tContext.iWeaponID = v15;
      igi2_frame.tContext.nAmmoInClip = v16;
      igi2_frame.tContext.anAmmoForFiretype[0] = v16;
      ((void (__cdecl *)(struct QTask_s *, struct GunPickupContext_t *))QTask_aatQTaskFinalEvent[GunPickup_eGunPickupQTaskEvent][v18->tQTaskChildren.ptHead->eQTaskType].pfHandler)(
        v18->tQTaskChildren.ptHead,
        &igi2_frame.tContext);
      if ( ptHead == HumanPlayer_ptQTask && v17 && v17 != WeaponTypeFromID )
        Weapon_DisableWeaponType(ptHead[33].ptNext, v17->zWeaponScriptID, true);
    }
    else
    {
      v10 = HumanPlayer_ptQTask;
      HumanPlayer_ptQTask[87].tQTaskRefList.ptMiddle = (struct QReference_s *)1;
      v10[87].ptPrev = *(struct QTask_s **)(v6 + 12);
      v10[87].tQTaskChildren.ptHead = *(struct QTask_s **)(v6 + 16);
      v11 = v10;
      v12 = Script_ParseLineInt32("WEAPON_ID_KNIFE");
      v11[76].ptParent = (struct QTask_s *)WeaponType_GetWeaponTypeFromID(v12)->eID;
      HumanPlayer_SelectWeapon(v11, 1);
    }
  }
}

// source: j/0/network/client.c:2196  [anchor-callee]
void __cdecl Client_UpdateMoneyRemote(struct Client_s *ptClient, char *zMessage)
{
  void *v3; // esi
  int v4; // esi

  v3 = Mem_AllocFn(96, 4);
  *((_DWORD *)v3 + 3) = 10;
  *((_DWORD *)v3 + 11) = 1;
  *((_DWORD *)v3 + 5) = ptClient->nUpdateItemTime;
  strncpy((char *)v3 + 56, zMessage, 0x28u);
  NetManager_SendListCommand((struct NetManagerGameMessageList *)v3, ptClient->eNetworkID);
  v4 = *(_DWORD *)(((int)v3 - 4) & 0xFFFFFFFC);
  --Mem_nCurrentAllocations;
  Node_Remove((_DWORD **)v4);
  memset(*(void **)(v4 + 8), 0xCDu, *(_DWORD *)(v4 + 16));
  free((void *)v4);
}

// source: j/0/network/client.c:2236  [anchor-strings]
void __cdecl Client_GameMessagePickupHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { _DWORD v9[10]; };
    struct { char igi2_o1[40]; char Buffer[256]; };
    char igi2_extent[296];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // edi
  struct QTask_s *v3; // edx
  int v4; // edi
  struct QTask_s *ptHead; // ebx
  struct QTask_s *QTaskFromID; // eax
  int eQTaskType; // edx
  void (__cdecl *pfHandler)(struct QTask_s *, _DWORD *); // eax

  v2 = *((_DWORD *)pxContext + 3);
  v3 = *(struct QTask_s **)(v2 + 24);
  v4 = v2 + 8;
  if ( ptQTask[1].ptNext == v3 )
  {
    ptHead = ptQTask[16].tQTaskChildren.ptHead->tQTaskChildren.ptHead;
    QTaskFromID = NetworkGameItem_GetQTaskFromID(*(_DWORD *)(v4 + 8));
    if ( QTaskFromID )
      *(_DWORD *)&QTaskFromID[12].eQTaskType = 0;
    if ( *(_DWORD *)(v4 + 12) == -1 )
    {
      if ( ptHead == HumanPlayer_ptQTask )
        HumanPlayer_ptQTask[80].tQTaskRefList.ptTail = (struct QReference_s *)3;
    }
    else
    {
      if ( ptHead == HumanPlayer_ptQTask )
        HumanPlayer_ptQTask[80].tQTaskRefList.ptTail = (struct QReference_s *)2;
      if ( QTaskFromID )
      {
        igi2_frame.v9[0] = ptHead;
        GunPickup_Pickup(QTaskFromID, igi2_frame.v9);
      }
      else
      {
        _snprintf(
          igi2_frame.Buffer,
          0xFFu,
          "Warning: Client picked up weapon that did not exist locally, ePickupID=%d",
          *(_DWORD *)(v4 + 12));
        NetManager_LogMessage(igi2_frame.Buffer);
        eQTaskType = ptHead->eQTaskType;
        igi2_frame.v9[3] = *(_DWORD *)(v4 + 12);
        pfHandler = (void (__cdecl *)(struct QTask_s *, _DWORD *))QTask_aatQTaskFinalEvent[GunPickup_eGunPickupQTaskEvent][eQTaskType].pfHandler;
        igi2_frame.v9[5] = 0;
        if ( pfHandler )
          pfHandler(ptHead, igi2_frame.v9);
      }
    }
  }
}

// source: j/0/network/client.c:2339  [anchor-caller]
void __cdecl Client_GameMessageDropHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v9; };
    struct { char igi2_o1[20]; struct real32x9_t ptOrientation; };
    char igi2_extent[60];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // esi
  struct QTask_s *v3; // edx
  int v4; // esi
  struct QTask_s *ptHead; // ebx
  struct WeaponType_s *WeaponTypeFromID; // eax
  float v7; // edx
  struct WeaponType_s *v8; // edi

  v2 = *((_DWORD *)pxContext + 3);
  v3 = *(struct QTask_s **)(v2 + 76);
  v4 = v2 + 8;
  if ( ptQTask[1].ptNext == v3 )
  {
    ptHead = ptQTask[16].tQTaskChildren.ptHead->tQTaskChildren.ptHead;
    WeaponTypeFromID = WeaponType_GetWeaponTypeFromID(*(_DWORD *)(v4 + 48));
    v7 = *(float *)(v4 + 36);
    v8 = WeaponTypeFromID;
    igi2_frame.v9 = *(float *)(v4 + 40);
    GunPickup_iGameItemID = *(_WORD *)(v4 + 52);
    Real32x9_Create(&igi2_frame.ptOrientation, *(float *)(v4 + 32), v7, igi2_frame.v9);
    GunPickup_New(
      v8,
      (struct real64x3_t *)(v4 + 8),
      &igi2_frame.ptOrientation,
      *(float *)(v4 + 44),
      true,
      0,
      *(int **)(v4 + 56),
      v4 + 60);
    Weapon_DisableWeaponType(ptHead[33].ptNext, v8->zWeaponScriptID, true);
  }
}

// source: j/0/network/client.c:2411  [anchor-strings]
void __cdecl Client_GameMessageChatHandler(struct QTask_s *ptQTask, void *pxContext)
{
  char *v2; // edi
  struct QReference_s *v3; // ecx
  struct QReference_s *ptHead; // edx
  char zTemp[256]; // [esp+8h] [ebp-100h] BYREF

  if ( ((int)ptQTask[5].tQTaskRefList.ptMiddle & 1) != 0 )
  {
    if ( *(_BYTE *)(*((_DWORD *)pxContext + 3) + 276) )
    {
      v2 = (char *)(*((_DWORD *)pxContext + 3) + 16);
      StatusScreen_ShowMonitorMessage(v2, TEXTSCROLLER_COLOUR_WHITE);
      if ( ptQTask[1].ptNext )
      {
        _snprintf(zTemp, 0xFFu, "SERVER ANNOUNCE: %s\n", v2);
        zTemp[254] = 0;
        NetManager_LogMessage(zTemp);
      }
    }
    else
    {
      v3 = *(struct QReference_s **)(*((_DWORD *)pxContext + 3) + 272);
      ptHead = ptQTask[1].tQTaskRefList.ptHead;
      if ( v3 == ptHead )
        goto LABEL_8;
      if ( v3 != (struct QReference_s *)-1 )
        return;
      if ( ptHead == (struct QReference_s *)-1 )
LABEL_8:
        StatusScreen_ShowMessage((char *)(*((_DWORD *)pxContext + 3) + 16), TEXTSCROLLER_COLOUR_YELLOW);
      else
        StatusScreen_ShowMessage((char *)(*((_DWORD *)pxContext + 3) + 16), TEXTSCROLLER_COLOUR_WHITE);
    }
  }
}

// source: j/0/network/client.c:2478  [anchor-mhash]
void __cdecl Client_GameMessagePingHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptNetManagerQTask; // esi
  int v3; // edi
  DWORD PerformanceCounter; // eax
  bool v5; // zf
  DWORD TickCount; // eax
  struct QTask_s *ptMiddle; // ecx
  struct ServerGameMessagePong_s tPongGameMessage; // [esp+4h] [ebp-Ch] BYREF

  if ( ((int)ptQTask[5].tQTaskRefList.ptMiddle & 1) != 0 )
  {
    ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
    v3 = *((_DWORD *)pxContext + 3) + 8;
    if ( Timer_isPerformanceCounter )
      PerformanceCounter = Timer_GetPerformanceCounter();
    else
      PerformanceCounter = GetTickCount();
    v5 = Timer_isPerformanceCounter == 0;
    ptQTask[5].ptParent = (struct QTask_s *)(PerformanceCounter
                                           - Timer_nStartTime
                                           + (char *)ptNetManagerQTask[6].tQTaskRefList.ptMiddle
                                           - (char *)ptNetManagerQTask[6].tQTaskRefList.ptTail);
    tPongGameMessage.tBaseMessage.eGameMessage = 1347374663;
    if ( v5 )
      TickCount = GetTickCount();
    else
      TickCount = Timer_GetPerformanceCounter();
    ptMiddle = Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle;
    tPongGameMessage.tBaseMessage.nLocalTime = TickCount - Timer_nStartTime;
    tPongGameMessage.nServerTime = *(_DWORD *)(v3 + 4);
    NetManager_SendGameMessage(0, (int)ptMiddle, NETWORKQUEUE_MEDIUMPRIORITY, &tPongGameMessage.tBaseMessage, 0xCu);
  }
}

// source: j/0/network/client.c:2525  [anchor-strings]
void __cdecl Client_GameMessagePongHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct NetManagerGameMessage_s *v2; // esi
  DWORD PerformanceCounter; // eax
  unsigned int v4; // eax
  char Buffer[256]; // [esp+8h] [ebp-100h] BYREF

  v2 = (struct NetManagerGameMessage_s *)(*((_DWORD *)pxContext + 3) + 8);
  if ( ((int)ptQTask[5].tQTaskRefList.ptMiddle & 1) != 0 && Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    if ( Timer_isPerformanceCounter )
      PerformanceCounter = Timer_GetPerformanceCounter();
    else
      PerformanceCounter = GetTickCount();
    v4 = PerformanceCounter - Timer_nStartTime - v2->nLocalTime;
    if ( v4 >= 0xBB8 )
    {
      _snprintf(Buffer, 0xFFu, "Client_Pong: Skipping round trip value out of range: %d ms\n", v4);
      NetManager_LogMessage(Buffer);
    }
    else
    {
      NetManager_Synchronize(v2, (int)&ptQTask[6].tQTaskRefList);
    }
  }
}

// source: j/0/network/client.c:2564  [anchor-mhash]
void __cdecl Client_GameMessageDamageHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { char *apzSound[3]; };
    struct { char igi2_o1[12]; char azSound[3][32]; };
    char igi2_extent[108];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // esi
  char ptMiddle; // al
  int v4; // esi
  struct QTask_s *ptHead; // eax
  struct QTask_s *v6; // eax
  struct QTask_s *v7; // eax
  struct QTask_s *v8; // edi
  struct QTask_s *v9; // edi

  strcpy(igi2_frame.azSound[0], "player_hit_1");
  *(_QWORD *)&igi2_frame.azSound[0][13] = 0;
  *(_QWORD *)&igi2_frame.azSound[0][21] = 0;
  strcpy(igi2_frame.azSound[1], "player_hit_2");
  *(_WORD *)&igi2_frame.azSound[0][29] = 0;
  *(_QWORD *)&igi2_frame.azSound[1][13] = 0;
  igi2_frame.azSound[0][31] = 0;
  *(_QWORD *)&igi2_frame.azSound[1][21] = 0;
  *(_QWORD *)&igi2_frame.azSound[2][13] = 0;
  *(_WORD *)&igi2_frame.azSound[1][29] = 0;
  strcpy(igi2_frame.azSound[2], "player_hit_3");
  igi2_frame.azSound[1][31] = 0;
  *(_QWORD *)&igi2_frame.azSound[2][21] = 0;
  igi2_frame.apzSound[1] = igi2_frame.azSound[1];
  v2 = *((_DWORD *)pxContext + 3);
  *(_WORD *)&igi2_frame.azSound[2][29] = 0;
  igi2_frame.apzSound[0] = igi2_frame.azSound[0];
  ptMiddle = (char)ptQTask[5].tQTaskRefList.ptMiddle;
  igi2_frame.azSound[2][31] = 0;
  v4 = v2 + 8;
  igi2_frame.apzSound[2] = igi2_frame.azSound[2];
  if ( (ptMiddle & 1) != 0 )
  {
    if ( *(struct QTask_s **)(v4 + 20) == ptQTask[1].ptNext )
    {
      ptHead = ptQTask[16].tQTaskChildren.ptHead;
      if ( ptHead )
      {
        v6 = ptHead->tQTaskChildren.ptHead;
        if ( v6 )
          ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[NetManager_eGameMessageDamageQTaskEvent][v6->eQTaskType].pfHandler)(
            v6,
            pxContext);
      }
    }
    v7 = *(struct QTask_s **)(v4 + 24);
    if ( v7 == ptQTask[1].ptNext && v7 != *(struct QTask_s **)(v4 + 20) )
    {
      v8 = ptQTask[16].tQTaskChildren.ptHead;
      if ( v8 )
      {
        v9 = v8->tQTaskChildren.ptHead;
        if ( v9 )
        {
          Human_HitSound(v9, igi2_frame.apzSound, 3);
          if ( !*(_DWORD *)(v4 + 16) )
            HumanDamage_CreateFleshEnterEffect(
              (struct HumanDamage_t *)&v9[25].tQTaskRefList,
              (struct real32x3_t *)(v4 + 56),
              (struct real64x3_t *)(v4 + 32),
              v9);
        }
      }
    }
  }
}

// source: j/0/network/client.c:2645  [anchor-caller]
void __cdecl Client_GameMessageKillHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { char *zPlayerName; };
    struct { char igi2_o1[28]; int v24; };
    struct { char igi2_o2[32]; struct Client_s *v25; };
    struct { char igi2_o3[36]; struct Human_s *ptHuman; };
    struct { char igi2_o4[40]; struct Client_s *ClientFromNetworkID; };
    struct { char igi2_o5[44]; char Buffer[64]; };
    struct { char igi2_o6[108]; char zText[2]; };
    struct { char igi2_o7[110]; _BYTE v30[253]; };
    char igi2_extent[364];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // eax
  struct QTask_s *v3; // edi
  struct Client_s *v4; // esi
  struct Client_s *v5; // ebx
  struct Human_s *v6; // edx
  int v7; // edi
  int v8; // edi
  char *zName; // eax
  char *v10; // edx
  char v11; // cl
  int v12; // edi
  struct QReference_s *ptTail; // eax
  int eTeam; // eax
  enum TextScrollerColour_e v15; // ecx
  int v16; // edi
  struct Flow_t *v17; // eax
  int v18; // ecx
  float vBoxLength; // ecx
  struct QTask_s *ptNetManagerQTask; // eax
  int eNetworkID; // ecx
  struct QTask_s *v22; // esi

  igi2_frame.ClientFromNetworkID = NetManager_GetClientFromNetworkID((int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
  v2 = *((_DWORD *)pxContext + 3);
  v3 = *(struct QTask_s **)(v2 + 20);
  igi2_frame.v24 = v2 + 8;
  if ( ptQTask[1].ptNext != v3 )
    return;
  v4 = nullptr;
  igi2_frame.v25 = nullptr;
  v5 = NetManager_GetClientFromNetworkID((int)v3);
  v6 = *(struct Human_s **)(v5->tReceiveTimeBuffer.nCounter + 8);
  *(_WORD *)igi2_frame.zText = 0;
  memset(igi2_frame.v30, 0, sizeof(igi2_frame.v30));
  v7 = *(_DWORD *)(igi2_frame.v24 + 8);
  igi2_frame.ptHuman = v6;
  if ( v7 != -1 )
  {
    igi2_frame.v25 = NetManager_GetClientFromNetworkID(v7);
    v4 = igi2_frame.v25;
  }
  v8 = *(_DWORD *)(igi2_frame.v24 + 24);
  if ( v8 == -1 )
  {
    sprintf(igi2_frame.Buffer, byte_69AF88);
  }
  else
  {
    zName = WeaponType_GetWeaponTypeFromID(v8)->zName;
    v10 = (char *)(igi2_frame.Buffer - zName);
    do
    {
      v11 = *zName;
      zName[(_DWORD)v10] = *zName;
      ++zName;
    }
    while ( v11 );
  }
  igi2_frame.ptHuman->tHumanDamage.vDamage = 4.0;
  Human_UpdateDie(igi2_frame.ptHuman);
  Weapon_ClearAllWeapons(igi2_frame.ptHuman->ptWeaponQTask);
  Weapon_EnableWeaponType(igi2_frame.ptHuman->ptWeaponQTask, "WEAPON_ID_KNIFE", true);
  if ( ptQTask[1].tQTaskRefList.ptHead == (struct QReference_s *)1 )
    Weapon_EnableWeaponType(igi2_frame.ptHuman->ptWeaponQTask, "WEAPON_ID_MAKAROV", true);
  else
    Weapon_EnableWeaponType(igi2_frame.ptHuman->ptWeaponQTask, "WEAPON_ID_GLOCK", true);
  if ( (struct QTask_s *)v5->eNetworkID == Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
    Client_CancelTalk((struct Client_s *)ptQTask);
  v12 = igi2_frame.v24;
  if ( *(_BYTE *)(igi2_frame.v24 + 28) )
  {
    Config_SetLocalizedPhrase(igi2_frame.zText, "mp/spawnkilled", v5->zPlayerName, v4->zPlayerName, igi2_frame.Buffer);
    if ( StatusScreen_ptStatusScreenQTask )
    {
      ptTail = StatusScreen_ptStatusScreenQTask[52].tQTaskRefList.ptTail;
      if ( ptTail )
        TextScroller_Add((struct TextScroller_s *)ptTail, igi2_frame.zText, TEXTSCROLLER_COLOUR_LIGHTRED);
    }
    NetManager_LogMessage(igi2_frame.zText);
    NetManager_LogMessage("\r\n");
    goto LABEL_52;
  }
  if ( *(_DWORD *)(igi2_frame.v24 + 8) == *(_DWORD *)(igi2_frame.v24 + 12) )
  {
    if ( *(_DWORD *)(igi2_frame.v24 + 20) == 2 )
    {
      igi2_frame.zPlayerName = v5->zPlayerName;
LABEL_49:
      Config_SetLocalizedPhrase(igi2_frame.zText, "mp/felldeath", igi2_frame.zPlayerName, nullptr, nullptr);
      goto LABEL_50;
    }
    Config_SetLocalizedPhrase(igi2_frame.zText, "mp/suicided", v5->zPlayerName, nullptr, nullptr);
    goto LABEL_50;
  }
  if ( !v4 )
  {
    v16 = *(_DWORD *)(igi2_frame.v24 + 20);
    if ( v16 )
    {
      if ( v16 == 1 )
      {
        Config_SetLocalizedPhrase(igi2_frame.zText, "mp/blown", v5->zPlayerName, nullptr, nullptr);
      }
      else
      {
        if ( v16 != 4 )
        {
          igi2_frame.zPlayerName = v5->zPlayerName;
          goto LABEL_49;
        }
        Config_SetLocalizedPhrase(igi2_frame.zText, "mp/mine", v5->zPlayerName, nullptr, nullptr);
      }
    }
    else
    {
      Config_SetLocalizedPhrase(igi2_frame.zText, "mp/sentrygun", v5->zPlayerName, nullptr, nullptr);
    }
LABEL_50:
    v15 = TEXTSCROLLER_COLOUR_LIGHTRED;
    goto LABEL_51;
  }
  if ( *(_DWORD *)(igi2_frame.v24 + 20) == 1 )
  {
    Config_SetLocalizedPhrase(igi2_frame.zText, "mp/was_blown", v5->zPlayerName, v4->zPlayerName, nullptr);
  }
  else if ( *(_DWORD *)(igi2_frame.v24 + 24) == Script_ParseLineInt32("WEAPON_ID_KNIFE") )
  {
    Config_SetLocalizedPhrase(igi2_frame.zText, "mp/was_stabbed", v5->zPlayerName, v4->zPlayerName, nullptr);
  }
  else if ( *(_DWORD *)(igi2_frame.v24 + 20) == 3 )
  {
    Config_SetLocalizedPhrase(igi2_frame.zText, "mp/was_pummeled_to_death_by", v5->zPlayerName, v4->zPlayerName, igi2_frame.Buffer);
  }
  else
  {
    switch ( *(_DWORD *)(igi2_frame.v24 + 16) )
    {
      case 0:
      case 1:
      case 2:
      case 6:
      case 7:
      case 8:
        Config_SetLocalizedPhrase(igi2_frame.zText, "mp/was_shot_leg", v5->zPlayerName, v4->zPlayerName, igi2_frame.Buffer);
        break;
      case 3:
      case 4:
      case 5:
      case 9:
      case 0xA:
      case 0xB:
        Config_SetLocalizedPhrase(igi2_frame.zText, "mp/was_shot_arm", v5->zPlayerName, v4->zPlayerName, igi2_frame.Buffer);
        break;
      case 0xC:
      case 0xD:
        Config_SetLocalizedPhrase(igi2_frame.zText, "mp/was_shot_chest", v5->zPlayerName, v4->zPlayerName, igi2_frame.Buffer);
        break;
      case 0xE:
        Config_SetLocalizedPhrase(igi2_frame.zText, "mp/was_shot_back", v5->zPlayerName, v4->zPlayerName, igi2_frame.Buffer);
        break;
      case 0xF:
        Config_SetLocalizedPhrase(igi2_frame.zText, "mp/was_shot_groin", v5->zPlayerName, v4->zPlayerName, igi2_frame.Buffer);
        break;
      case 0x10:
        Config_SetLocalizedPhrase(igi2_frame.zText, "mp/was_shot_head", v5->zPlayerName, v4->zPlayerName, igi2_frame.Buffer);
        break;
      default:
        Config_SetLocalizedPhrase(igi2_frame.zText, "mp/maimed", v5->zPlayerName, v4->zPlayerName, igi2_frame.Buffer);
        break;
    }
  }
  eTeam = v5->eTeam;
  if ( v4->eTeam == eTeam || igi2_frame.ClientFromNetworkID && igi2_frame.ClientFromNetworkID->eTeam == eTeam )
    goto LABEL_50;
  v15 = TEXTSCROLLER_COLOUR_LIGHTGREEN;
LABEL_51:
  StatusScreen_ShowMessage(igi2_frame.zText, v15);
  v4 = igi2_frame.v25;
  v12 = igi2_frame.v24;
LABEL_52:
  v17 = Flow_ptFlow;
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    if ( v4 && v4 != v5 || *(_BYTE *)(v12 + 28) )
    {
      if ( v5->eTeam == v4->eTeam )
      {
        v18 = v4->tDownload.nLastLoDown + 1;
        --v4->nPoints;
        v4->tDownload.nLastLoDown = v18;
        LODWORD(v4->tDownload.vBoxLength) = 1;
      }
      else
      {
        ++v4->nPoints;
      }
    }
    vBoxLength = v5->tDownload.vBoxLength;
    ++*(_DWORD *)&v5->isTalk;
    if ( vBoxLength == 0.0 )
      v5->tDownload.nLastLoDown = 0;
    ptNetManagerQTask = v17->ptNetManagerQTask;
    eNetworkID = v5->eNetworkID;
    if ( (struct QTask_s *)eNetworkID == ptNetManagerQTask[6].tQTaskChildren.ptMiddle && v4 )
    {
      if ( (ptNetManagerQTask[5].tQTaskRefList.ptHead == (struct QReference_s *)2 || v5->eTeam == v4->eTeam)
        && (v22 = (struct QTask_s *)v4->eNetworkID, (struct QTask_s *)eNetworkID != v22) )
      {
        ptNetManagerQTask[6].tQTaskChildren.ptTail = v22;
      }
      else
      {
        ptNetManagerQTask[6].tQTaskChildren.ptTail = (struct QTask_s *)-1;
      }
    }
    DebugConsole_printf("\nClient: Set death timer on client %d\n", v5->eNetworkID);
    NetManager_SetDeathTimer(v5);
  }
}

// source: j/0/network/client.c:2869  [anchor-caller]
void __cdecl Client_GameMessageSpawnHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real64x3_t *ptPos; };
    struct { char igi2_o1[4]; struct WeaponType_s *NextEnabledWeaponTypeFromCategory; };
    struct { char igi2_o2[4]; struct HumanPlayer_t *v22; };
    struct { char igi2_o3[8]; int v23; };
    struct { char igi2_o4[12]; struct real64x3_t ptNewSpeed; };
    struct { char igi2_o5[36]; struct real64x3_t ptSpeed; };
    struct { char igi2_o6[60]; struct real64x3_t ptNewPos; };
    struct { char igi2_o7[84]; struct real64x3_t ptOldPos; };
    struct { char igi2_o8[108]; char Buffer[256]; };
    char igi2_extent[364];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // eax
  struct QTask_s *ptHead; // ebx
  struct QTask_s *ptNetManagerQTask; // esi
  struct QTask_s *ptNext; // esi
  struct WeaponType_s *v6; // eax
  char *zWeaponScriptID; // eax
  struct QTask_s *v8; // eax
  struct HumanPlayer_t *v9; // eax
  DWORD PerformanceCounter; // eax
  struct QTaskNodeList_s *p_tQTaskChildren; // ebx
  struct QTask_s *SpawnPointFromID; // eax
  DWORD TickCount; // eax
  struct Spline_s *p_apfExitState; // esi
  int ePrecisionType; // eax
  int vIdealModifiedPrecision_low; // ecx
  int v17; // eax
  struct Spline_s *p_vActualModifiedPrecision; // esi
  int v19; // ecx

  v2 = *((_DWORD *)pxContext + 3);
  igi2_frame.v23 = v2 + 8;
  if ( *(struct QTask_s **)(v2 + 16) == ptQTask[1].ptNext )
  {
    ptHead = ptQTask[16].tQTaskChildren.ptHead->tQTaskChildren.ptHead;
    ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
    ptQTask[15].tQTaskRefList.ptMiddle = nullptr;
    ptQTask[15].ptParent = (struct QTask_s *)(30 * (int)ptNetManagerQTask[6].ptNext);
    ptQTask[15].tQTaskChildren.ptTail = (struct QTask_s *)-1;
    LOBYTE(ptHead[29].tQTaskRefList.ptHead) = 0;
    BYTE2(ptHead[50].ptNext) = 1;
    HIBYTE(ptHead[50].ptNext) = 0;
    *(_DWORD *)&ptHead[47].eQTaskType = 1;
    ptHead[48].ptNext = nullptr;
    ptHead[48].ptPrev = nullptr;
    ptHead[47].ptParent = nullptr;
    ptQTask[16].ptNext = nullptr;
    ptNetManagerQTask[6].tQTaskChildren.ptTail = (struct QTask_s *)-1;
    HumanDamage_ClearDamage((struct HumanDamage_t *)&ptHead[25].tQTaskRefList);
    BoneDynCubeObj_DeInitBloodStains((struct BoneDynCubeObj_s *)ptHead);
    BoneDynCubeObj_InitBloodStains((struct BoneDynCubeObj_s *)ptHead);
    Weapon_EnableWeaponType(ptHead[33].ptNext, "WEAPON_ID_KNIFE", true);
    ptNext = ptHead[33].ptNext;
    igi2_frame.NextEnabledWeaponTypeFromCategory = Weapon_GetNextEnabledWeaponTypeFromCategory(
                                          ptNext,
                                          WEAPONCATEGORY_PRIMARY,
                                          nullptr);
    v6 = Weapon_GetNextEnabledWeaponTypeFromCategory(ptNext, WEAPONCATEGORY_SIDEARM, nullptr);
    if ( !v6 )
    {
      if ( ptQTask[1].tQTaskRefList.ptHead )
        Weapon_EnableWeaponType(ptNext, "WEAPON_ID_MAKAROV", true);
      else
        Weapon_EnableWeaponType(ptNext, "WEAPON_ID_GLOCK", true);
      ptNext = ptHead[33].ptNext;
      v6 = Weapon_GetNextEnabledWeaponTypeFromCategory(ptNext, WEAPONCATEGORY_SIDEARM, nullptr);
    }
    if ( igi2_frame.NextEnabledWeaponTypeFromCategory )
      zWeaponScriptID = igi2_frame.NextEnabledWeaponTypeFromCategory->zWeaponScriptID;
    else
      zWeaponScriptID = v6->zWeaponScriptID;
    Weapon_Activate(ptNext, zWeaponScriptID, true);
    v8 = ptQTask[16].tQTaskChildren.ptHead;
    if ( v8 )
    {
      v9 = (struct HumanPlayer_t *)v8->tQTaskChildren.ptHead;
      igi2_frame.v22 = v9;
      if ( ((int)ptQTask[5].tQTaskRefList.ptMiddle & 1) != 0 )
      {
        HumanPlayer_Spawn(v9, *(_DWORD *)(igi2_frame.v23 + 12));
        _snprintf(igi2_frame.Buffer, 0xFFu, "Client: Local spawned[%d][%s]\n", ptQTask[1].ptNext, (char *)&ptQTask[2]);
        NetManager_LogMessage(igi2_frame.Buffer);
      }
      else
      {
        if ( Timer_isPerformanceCounter )
          PerformanceCounter = Timer_GetPerformanceCounter();
        else
          PerformanceCounter = GetTickCount();
        igi2_frame.ptPos = (struct real64x3_t *)(PerformanceCounter - Timer_nStartTime);
        p_tQTaskChildren = &ptHead[34].tQTaskChildren;
        SpawnPointFromID = SpawnPoint_GetSpawnPointFromID(*(_DWORD *)(igi2_frame.v23 + 12));
        qmemcpy(&igi2_frame.ptNewPos, &SpawnPointFromID[1].tQTaskChildren, sizeof(igi2_frame.ptNewPos));
        if ( p_tQTaskChildren )
          p_tQTaskChildren->ptHead = SpawnPointFromID[1].ptParent;
        if ( Timer_isPerformanceCounter )
          TickCount = Timer_GetPerformanceCounter();
        else
          TickCount = GetTickCount();
        p_apfExitState = (struct Spline_s *)&igi2_frame.v22->tAction.apfExitState;
        LODWORD(igi2_frame.v22->tStateContext.tFlatContext.tLastOrientation.tX.vX) = TickCount - Timer_nStartTime;
        igi2_frame.v22->ePrecisionType = -1;
        ePrecisionType = igi2_frame.v22->ePrecisionType;
        memset(&igi2_frame.ptNewSpeed, 0, sizeof(igi2_frame.ptNewSpeed));
        if ( ePrecisionType <= 0 )
        {
          Spline_Initialize(p_apfExitState, &igi2_frame.ptNewPos, &igi2_frame.ptNewPos, &igi2_frame.ptNewSpeed, &igi2_frame.ptNewSpeed, (int)igi2_frame.ptPos, 100);
        }
        else
        {
          vIdealModifiedPrecision_low = LODWORD(igi2_frame.v22->vIdealModifiedPrecision);
          if ( (int)igi2_frame.ptPos >= vIdealModifiedPrecision_low )
          {
            if ( (int)igi2_frame.ptPos <= ePrecisionType + vIdealModifiedPrecision_low )
              Spline_OnSpline(&igi2_frame.ptOldPos, &igi2_frame.ptSpeed, p_apfExitState, (int)igi2_frame.ptPos);
            else
              Spline_ExtraFromEnd(&igi2_frame.ptOldPos, &igi2_frame.ptSpeed, p_apfExitState, (int)igi2_frame.ptPos);
            Spline_Initialize(p_apfExitState, &igi2_frame.ptOldPos, &igi2_frame.ptNewPos, &igi2_frame.ptSpeed, &igi2_frame.ptNewSpeed, (int)igi2_frame.ptPos, 100);
          }
          else
          {
            Spline_ExtraFromStart(&igi2_frame.ptOldPos, &igi2_frame.ptSpeed, p_apfExitState, (int)igi2_frame.ptPos);
            Spline_Initialize(p_apfExitState, &igi2_frame.ptOldPos, &igi2_frame.ptNewPos, &igi2_frame.ptSpeed, &igi2_frame.ptNewSpeed, (int)igi2_frame.ptPos, 100);
          }
        }
        igi2_frame.v22->avDamageFlash[0] = IGI2_FLOAT_BITS(0xffffffffu);
        v17 = LODWORD(igi2_frame.v22->avDamageFlash[0]);
        p_vActualModifiedPrecision = (struct Spline_s *)&igi2_frame.v22->vActualModifiedPrecision;
        if ( v17 <= 0 )
        {
          Spline_Initialize(
            p_vActualModifiedPrecision,
            &igi2_frame.ptNewSpeed,
            &igi2_frame.ptNewSpeed,
            &igi2_frame.ptNewSpeed,
            &igi2_frame.ptNewSpeed,
            (int)igi2_frame.ptPos,
            100);
        }
        else
        {
          v19 = LODWORD(igi2_frame.v22->avDamageFlash[1]);
          if ( (int)igi2_frame.ptPos >= v19 )
          {
            if ( (int)igi2_frame.ptPos <= v17 + v19 )
              Spline_OnSpline(&igi2_frame.ptNewPos, &igi2_frame.ptSpeed, p_vActualModifiedPrecision, (int)igi2_frame.ptPos);
            else
              Spline_ExtraFromEnd(&igi2_frame.ptNewPos, &igi2_frame.ptSpeed, p_vActualModifiedPrecision, (int)igi2_frame.ptPos);
            Spline_Initialize(
              p_vActualModifiedPrecision,
              &igi2_frame.ptNewPos,
              &igi2_frame.ptNewSpeed,
              &igi2_frame.ptSpeed,
              &igi2_frame.ptNewSpeed,
              (int)igi2_frame.ptPos,
              100);
          }
          else
          {
            Spline_ExtraFromStart(&igi2_frame.ptNewPos, &igi2_frame.ptSpeed, p_vActualModifiedPrecision, (int)igi2_frame.ptPos);
            Spline_Initialize(
              p_vActualModifiedPrecision,
              &igi2_frame.ptNewPos,
              &igi2_frame.ptNewSpeed,
              &igi2_frame.ptSpeed,
              &igi2_frame.ptNewSpeed,
              (int)igi2_frame.ptPos,
              100);
          }
        }
        _snprintf(igi2_frame.Buffer, 0xFFu, "Client: Remote spawned[%d][%s]\n", ptQTask[1].ptNext, (char *)&ptQTask[2]);
        NetManager_LogMessage(igi2_frame.Buffer);
      }
    }
  }
}

void __cdecl sub_5241E0(struct QTask_s *a1, _DWORD *a2)
{
  int v2; // eax
  struct QTask_s *v3; // edx
  int v4; // eax

  v2 = a2[3];
  v3 = *(struct QTask_s **)(v2 + 16);
  v4 = v2 + 8;
  if ( v3 == a1[1].ptNext )
    a1[1].ptPrev = *(struct QTask_s **)(v4 + 12);
}

void __cdecl sub_524200(struct QTask_s *a1, _DWORD *a2)
{
  unsigned int v2; // eax
  struct QReference_s *v3; // eax
  struct QTask_s *pxObject; // eax
  int ptPrev; // esi
  int ptNext; // ebx
  enum bool v7; // edi

  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle
    && (struct QTask_s *)a2[1] == a1[1].ptNext
    && ((int)a1[5].tQTaskRefList.ptMiddle & 1) != 0 )
  {
    v2 = *(_DWORD *)(a2[3] + 16);
    if ( v2 < 0x1000 && (v3 = Level_atLevelQTaskID[v2]) != nullptr )
      pxObject = (struct QTask_s *)v3->pxObject;
    else
      pxObject = nullptr;
    ptPrev = (int)pxObject[5].ptPrev;
    ptNext = (int)pxObject[5].ptNext;
    v7 = *(char *)(a2[3] + 20);
    NetMission_SetObjectiveComplete(pxObject, v7, *(_DWORD *)(a2[3] + 24));
    NetObjective_DisplayCompleteState(ptPrev, v7, ptNext);
  }
}

// source: j/0/network/client.c:3117  [anchor-caller]
void __cdecl Client_GameMessageAuthenticateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zResponse[80]; };
    struct { char igi2_o1[80]; char zCDKey[52]; };
    char igi2_extent[132];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // eax
  int v3; // edi
  struct QTask_s *v4; // eax
  int v5; // eax
  struct Flow_t *v6; // edx

  v2 = *((_DWORD *)pxContext + 3);
  v3 = v2 + 8;
  if ( !*(_DWORD *)v2 )
  {
    if ( *(_BYTE *)(v2 + 104) )
    {
      v4 = *(struct QTask_s **)(v2 + 16);
      if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle == v4 && ptQTask[1].ptNext == v4 )
      {
        GameSpy_GetCDKey(igi2_frame.zCDKey, 50);
        gcd_compute_response(igi2_frame.zCDKey, (char *)(v3 + 12), igi2_frame.zResponse);
        *(_DWORD *)(v3 + 92) = strlen(igi2_frame.zResponse);
        strcpy((char *)(v3 + 12), igi2_frame.zResponse);
        v5 = Timer_Read();
        v6 = Flow_ptFlow;
        *(_DWORD *)(v3 + 4) = v5;
        *(_BYTE *)(v3 + 96) = 0;
        *(_BYTE *)(v3 + 97) = 1;
        NetManager_SendGameMessage(
          0,
          (int)v6->ptNetManagerQTask[6].tQTaskChildren.ptMiddle,
          NETWORKQUEUE_GUARANTEED,
          (struct NetManagerGameMessage_s *)v3,
          0x64u);
      }
    }
  }
}

// source: j/0/network/client.c:3198  [anchor-caller]
void __cdecl Client_GameMessageBombHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { void *v21; };
    struct { char igi2_o1[16]; struct QTask_s *v22; };
    struct { char igi2_o2[20]; struct QTask_s *ptHead; };
    struct { char igi2_o3[24]; struct QTask_s v24; };
    struct { char igi2_o4[80]; _BYTE v25[24]; };
    struct { char igi2_o5[104]; _BYTE v26[40]; };
    struct { char igi2_o6[144]; struct QTask_s *v27; };
    struct { char igi2_o7[148]; float nSpawnMaxCost; };
    struct { char igi2_o8[152]; struct QTask_s *v29; };
    struct { char igi2_o9[156]; struct QTask_s *v30; };
    char igi2_extent[160];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // ebx
  struct QTask_s *v3; // ecx
  _DWORD *v4; // ebx
  unsigned int v5; // eax
  struct QReference_s *v6; // eax
  _DWORD *pxObject; // esi
  unsigned __int16 v8; // dx
  struct QTask_s *FirstChildOfType; // eax
  int v10; // edi
  char *LocalizedStringForLanguage; // eax
  int v12; // ecx
  char *v13; // eax
  struct QTask_s *ptPrev; // ecx
  struct QTask_s *ptMiddle; // edx
  float v16; // ecx
  struct QTask_s *v17; // edx
  struct QTask_s *v18; // eax
  char *v19; // eax
  char v20; // cl

  v2 = *((_DWORD *)pxContext + 3);
  v3 = *(struct QTask_s **)(v2 + 16);
  v4 = (_DWORD *)(v2 + 8);
  if ( v3 == ptQTask[1].ptNext )
  {
    v5 = v4[3];
    if ( v5 < 0x1000 && (v6 = Level_atLevelQTaskID[v5]) != nullptr )
      pxObject = v6->pxObject;
    else
      pxObject = nullptr;
    v8 = NetObjective_eQTaskType;
    FirstChildOfType = QTask_GetFirstChildOfType(&NetMission_ptNetMission->tQTask, NetObjective_eQTaskType);
    if ( FirstChildOfType )
    {
      v10 = NetMission_eCurrentObjective;
      while ( FirstChildOfType[5].ptNext != (struct QTask_s *)v10 )
      {
        FirstChildOfType = QTask_GetNextSiblingOfType(FirstChildOfType, v8);
        if ( !FirstChildOfType )
          goto LABEL_10;
      }
      igi2_frame.v22 = FirstChildOfType;
    }
    else
    {
LABEL_10:
      igi2_frame.v22 = nullptr;
    }
    if ( v4[4] )
    {
      LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                     "mp/BOMB_DISARMED",
                                     Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                     true);
      StatusScreen_ShowCritical(LocalizedStringForLanguage, TEXTSCROLLER_COLOUR_WHITE);
      v12 = pxObject[10];
      pxObject[105] = 1;
      *(_BYTE *)(v12 + 652) = 0;
      *(_DWORD *)(pxObject[10] + 632) = (char *)&MTP_atLODVirModel[11].atBoneVertexRefs[28].atVertexRefs[780].iVertex
                                      + 3;
      QTask_DeleteQTaskAndQTaskRefSafe((struct QReference_s **)(pxObject[10] + 656));
      if ( igi2_frame.v22 )
        igi2_frame.v22[5].tQTaskChildren.ptTail = (struct QTask_s *)v4[2];
    }
    else
    {
      igi2_frame.ptHead = ptQTask[16].tQTaskChildren.ptHead->tQTaskChildren.ptHead;
      v13 = Config_GetLocalizedStringForLanguage(
              "mp/BOMB_PLACED",
              Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
              true);
      StatusScreen_ShowCritical(v13, TEXTSCROLLER_COLOUR_WHITE);
      qmemcpy(igi2_frame.v25, v4 + 14, sizeof(igi2_frame.v25));
      qmemcpy(igi2_frame.v26, v4 + 20, sizeof(igi2_frame.v26));
      if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
      {
        v16 = *((float *)v4 + 31);
        v17 = (struct QTask_s *)v4[32];
        igi2_frame.v27 = (struct QTask_s *)v4[30];
        v18 = (struct QTask_s *)v4[33];
        igi2_frame.nSpawnMaxCost = v16;
        igi2_frame.v29 = v17;
        igi2_frame.v30 = v18;
      }
      else
      {
        ptPrev = C4Bomb_ptQTask[3].ptPrev;
        igi2_frame.v27 = C4Bomb_ptQTask[3].tQTaskChildren.ptHead;
        igi2_frame.nSpawnMaxCost = (float)ServerConfig_tServerConfig.nSpawnMaxCost;
        ptMiddle = C4Bomb_ptQTask[3].tQTaskChildren.ptMiddle;
        igi2_frame.v29 = ptPrev;
        igi2_frame.v30 = ptMiddle;
      }
      v19 = (char *)(v4 + 5);
      do
      {
        v20 = *v19;
        v19[(char *)&igi2_frame.v24.tQTaskRefList - (char *)(v4 + 5)] = *v19;
        ++v19;
      }
      while ( v20 );
      C4BombArea_PlaceBomb(&igi2_frame.v24, igi2_frame.v21);
      if ( igi2_frame.v22 )
        igi2_frame.v22[5].tQTaskChildren.ptTail = (struct QTask_s *)v4[2];
      Weapon_DisableWeaponType(igi2_frame.ptHead[33].ptNext, "WEAPON_ID_C4BOMB", true);
    }
  }
}

// source: j/0/network/client.c:3297  [anchor-caller]
void __cdecl Client_GameMessageWeaponHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // ebx
  char v3; // al
  int v4; // ebx
  BOOL v5; // esi
  struct QTask_s *ptNext; // edi
  struct Node_s *ptHead; // ecx
  struct Node_s *v8; // eax
  struct Flow_t *v9; // ebp
  enum WeaponCategory_e eWeaponCategory; // eax
  struct QTask_s *NextSiblingOfType; // eax
  struct QTask_s *v12; // esi
  unsigned int v13; // eax
  struct QReference_s *v14; // eax
  _WORD *pxObject; // eax
  struct WeaponType_s *WeaponTypeFromID; // eax
  struct QTask_s *v17; // edi
  struct Flow_t *v18; // ebp
  unsigned __int16 v19; // dx
  struct QTask_s *v20; // eax
  __int16 ptPrev; // [esp+10h] [ebp-8h]
  int v22; // [esp+14h] [ebp-4h]
  struct QTask_s *ptQTaska = *(struct QTask_s * *)&ptQTask; // [esp+1Ch] [ebp+4h] ARGSLOT

  v2 = *((_DWORD *)pxContext + 3);
  v3 = *(_BYTE *)(v2 + 24);
  v22 = v2;
  v4 = v2 + 8;
  v5 = 0;
  if ( !v3 && !NetManager_GetClientFromNetworkID(*(_DWORD *)(v4 + 8)) )
    v5 = ptQTask[1].ptNext == QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, Client_eQTaskType)[1].ptNext;
  ptNext = ptQTask[1].ptNext;
  if ( ptNext == *(struct QTask_s **)(v4 + 8) && ptQTask[16].tQTaskChildren.ptHead || v5 )
  {
    ptHead = result_7086a8.ptHead;
    v8 = result_7086a8.ptHead->ptNext;
    if ( result_7086a8.ptHead->ptNext )
    {
      while ( ptHead[1].ptNext != *(struct Node_s **)v4 )
      {
        ptHead = v8;
        v8 = v8->ptNext;
        if ( !v8 )
          goto LABEL_10;
      }
      ptPrev = (__int16)ptHead[1].ptPrev;
    }
    else
    {
LABEL_10:
      ptPrev = 512;
    }
    v9 = Flow_ptFlow;
    if ( ptNext == Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
    {
      switch ( *(_DWORD *)v4 )
      {
        case 0x57534652:
          eWeaponCategory = WeaponType_GetWeaponTypeFromID(*(unsigned __int8 *)(v4 + 20))->eWeaponCategory;
          if ( eWeaponCategory != WEAPONCATEGORY_GRENADE
            && eWeaponCategory != WEAPONCATEGORY_FLASHBANG
            && eWeaponCategory != WEAPONCATEGORY_SMOKEGRENADE
            && eWeaponCategory != WEAPONCATEGORY_PROXIMITYMINE )
          {
            return;
          }
          v9 = Flow_ptFlow;
          break;
        case 0x57535A4D:
          return;
        case 0x57534154:
          if ( !strcmp((char *)(v4 + 20), (char *)&g_zSoundDefPrefix.eQTaskType) )
            return;
          v9 = Flow_ptFlow;
          break;
      }
    }
    if ( *(_BYTE *)(v4 + 16) )
    {
      NextSiblingOfType = nullptr;
      do
      {
        if ( NextSiblingOfType )
          NextSiblingOfType = QTask_GetNextSiblingOfType(NextSiblingOfType, Client_eQTaskType);
        else
          NextSiblingOfType = QTask_GetFirstChildOfType(v9->ptNetManagerQTask, Client_eQTaskType);
      }
      while ( NextSiblingOfType && NextSiblingOfType[1].ptNext != *(struct QTask_s **)(v4 + 8) );
      v12 = NextSiblingOfType[16].tQTaskChildren.ptHead->tQTaskChildren.ptHead[33].ptNext;
      ptQTaska = v12;
    }
    else
    {
      v13 = *(_DWORD *)(v4 + 12);
      if ( v13 < 0x1000 && (v14 = Level_atLevelQTaskID[v13]) != nullptr )
        pxObject = v14->pxObject;
      else
        pxObject = nullptr;
      if ( pxObject[18] != AIStationaryGunHolder_eQTaskType )
        return;
      ptQTaska = *(struct QTask_s **)(*(_DWORD *)(*((_DWORD *)pxObject + 5217) + 8) + 496);
      v12 = ptQTaska;
    }
    if ( !v9->ptNetManagerQTask[6].tQTaskChildren.ptMiddle && *(_DWORD *)v4 == 1465075282 )
    {
      WeaponTypeFromID = WeaponType_GetWeaponTypeFromID(*(unsigned __int8 *)(v4 + 20));
      if ( WeaponTypeFromID )
      {
        if ( WeaponTypeFromID->eWeaponType == WEAPONTYPE_GRENADE )
        {
          v17 = nullptr;
          *(_BYTE *)(v4 + 23) = Grenade_GetNextTaskID();
LABEL_43:
          v18 = Flow_ptFlow;
          v19 = Client_eQTaskType;
          while ( 1 )
          {
            v20 = v17 ? QTask_GetNextSiblingOfType(v17, v19) : QTask_GetFirstChildOfType(v18->ptNetManagerQTask, v19);
            v17 = v20;
            if ( !v20 )
              break;
            if ( ((int)v20[5].tQTaskRefList.ptMiddle & 1) == 0 )
            {
              NetManager_SendGameMessage(
                (int)v20[1].ptNext,
                (int)v18->ptNetManagerQTask[6].tQTaskChildren.ptMiddle,
                NETWORKQUEUE_GUARANTEED,
                (struct NetManagerGameMessage_s *)v4,
                *((_DWORD *)pxContext + 2) - (v4 - v22));
              goto LABEL_43;
            }
          }
          v12 = ptQTaska;
        }
      }
    }
    if ( ptPrev != 512 )
    {
      if ( v12 )
        ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[ptPrev][v12->eQTaskType].pfHandler)(
          v12,
          pxContext);
    }
  }
}

void __cdecl sub_524810(struct QTask_s *a1, _DWORD *a2)
{
  struct QTask_s *ptNetManagerQTask; // ebx
  int v3; // esi
  struct Client_s *ClientFromNetworkID; // eax
  bool v5; // cc

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  if ( ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    v3 = a2[3];
    ClientFromNetworkID = NetManager_GetClientFromNetworkID(*(_DWORD *)v3);
    if ( ((int)a1[5].tQTaskRefList.ptMiddle & 1) != 0 )
    {
      if ( ClientFromNetworkID )
        v5 = (int)(*(_DWORD *)(v3 + 4)) < ClientFromNetworkID->nLastPacketID;
      else
        v5 = (int)(*(_DWORD *)(v3 + 4)) < (int)ptNetManagerQTask[31].tQTaskChildren.ptHead;
      if ( v5 )
        NetManager_LogMessage("Client: UPGR: Dropping old packet\r\n");
      else
        Grenade_HandleUpdatePacket((struct ClientGameMessageUpdateGrenade_s *)(v3 + 8));
    }
  }
}

// source: j/0/network/client.c:3552  [anchor-strings]
void __cdecl Client_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("NetworkClient", 844, BaseQTaskType, 0, 0);
  Client_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 0, Client_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, Client_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, Client_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v1, NetManager_eGameMessageActivateQTaskEvent, Client_GameMessageActivateHandler);
  QTask_LinkQTaskEventHandlerFn(v1, NetManager_eGameMessagePickupQTaskEvent, Client_GameMessagePickupHandler);
  QTask_LinkQTaskEventHandlerFn(v1, NetManager_eGameMessageDropQTaskEvent, Client_GameMessageDropHandler);
  QTask_LinkQTaskEventHandlerFn(v1, NetManager_eGameMessageChatQTaskEvent, Client_GameMessageChatHandler);
  QTask_LinkQTaskEventHandlerFn(v1, NetManager_eGameMessageKillQTaskEvent, Client_GameMessageKillHandler);
  QTask_LinkQTaskEventHandlerFn(v1, NetManager_eGameMessagePingQTaskEvent, Client_GameMessagePingHandler);
  QTask_LinkQTaskEventHandlerFn(v1, NetManager_eGameMessagePongQTaskEvent, Client_GameMessagePongHandler);
  QTask_LinkQTaskEventHandlerFn(v1, NetManager_eGameMessageEquipQTaskEvent, Client_GameMessageEquipHandler);
  QTask_LinkQTaskEventHandlerFn(v1, NetManager_eGameMessageSettingsQTaskEvent, Client_GameMessageSettingsHandler);
  QTask_LinkQTaskEventHandlerFn(v1, NetManager_eGameMessageDamageQTaskEvent, Client_GameMessageDamageHandler);
  QTask_LinkQTaskEventHandlerFn(v1, NetManager_eGameMessageSpawnQTaskEvent, Client_GameMessageSpawnHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    NetManager_eGameMessageSpectateQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))sub_5241E0);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    NetManager_eGameMessageObjectiveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))sub_524200);
  QTask_LinkQTaskEventHandlerFn(v1, NetManager_eGameMessageBombQTaskEvent, Client_GameMessageBombHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    NetManager_eGameMessageGrenadeUpdateQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))sub_524810);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    NetManager_eGameMessageAuthenticateQTaskEvent,
    Client_GameMessageAuthenticateHandler);
  QTask_LinkQTaskEventHandlerFn(v1, Weapon_eFireQTaskEvent, Client_GameMessageWeaponHandler);
  QTask_LinkQTaskEventHandlerFn(v1, Weapon_eReleaseQTaskEvent, Client_GameMessageWeaponHandler);
  QTask_LinkQTaskEventHandlerFn(v1, Weapon_eReloadQTaskEvent, Client_GameMessageWeaponHandler);
  QTask_LinkQTaskEventHandlerFn(v1, Weapon_eZoomQTaskEvent, Client_GameMessageWeaponHandler);
  QTask_LinkQTaskEventHandlerFn(v1, Weapon_eActivateQTaskEvent, Client_GameMessageWeaponHandler);
}

// source: j/0/network/client.c:3598  [size]
void __cdecl Client_Close()
{
  QTask_DeleteQTaskType(Client_eQTaskType);
}

// source: j/0/network/client.c:3612  [anchor-hash]
struct QTask_s *__cdecl Client_New(
        struct QTask_s *ptParentQTask,
        struct ClientCreateContext_s *ptCreateContext)
{
  ++BYTE1(Flow_ptFlow->ptNetManagerQTask[3].ptPrev);
  return QTask_NewFn(ptParentQTask, Client_eQTaskType, ptCreateContext);
}

// source: j/0/network/client.c:3641  [size]
unsigned __int16 __cdecl Client_GetQTaskType()
{
  return Client_eQTaskType;
}

// source: j/0/network/client.c:3656  [anchor-callee]
void __cdecl Client_CreateHuman(struct Client_s *ptClient)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct Human_s *ptHuman; };
    struct { char igi2_o1[4]; struct real64x3_t tPos; };
    char igi2_extent[32];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptNetManagerQTask; // edi
  struct QReference_s *nCounter; // eax
  struct Human_s *v3; // ebp
  struct QTask_s *v4; // eax
  char *zModel; // edx
  int v6; // edi
  char v7; // al
  __int16 v8; // dx
  struct QTask_s *v9; // edi

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  nCounter = (struct QReference_s *)ptClient->tReceiveTimeBuffer.nCounter;
  memset(&igi2_frame.tPos, 0, sizeof(igi2_frame.tPos));
  if ( nCounter )
  {
    QReference_Delete(nCounter, &QTask_tQTaskRefPool);
    ptClient->tReceiveTimeBuffer.nCounter = 0;
  }
  if ( (ptClient->bFlags & 1) != 0 )
  {
    v3 = (struct Human_s *)HumanPlayer_ptQTask;
    if ( HumanPlayer_ptQTask )
    {
      igi2_frame.ptHuman = (struct Human_s *)HumanPlayer_ptQTask;
      zModel = ptClient->zModel;
      v6 = (char *)&HumanPlayer_ptQTask[10].ptParent - ptClient->zModel;
      do
      {
        v7 = *zModel;
        zModel[v6] = *zModel;
        ++zModel;
      }
      while ( v7 );
      Human_SetTeam(v3, ptClient->eTeam, ptClient->zModel);
      v8 = ParameterList_eUpdateInternalDataQTaskEvent;
      igi2_frame.ptHuman->ptClient = ptClient;
      QTask_TriggerQTaskEventRecursively(&v3->tBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask, v8, nullptr);
      ptClient->tReceiveTimeBuffer.nCounter = (int)QTask_NewQTaskRef(&v3->tBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask);
      ptClient->anDR[4] = nullptr;
    }
    else
    {
      v4 = HumanPlayer_New(Level_ptDynamicQTask, &igi2_frame.tPos, 0.0, ptClient->zModel, ptClient->eTeam, ptClient->eNetworkID);
      BYTE2(v4[80].tQTaskRefList.ptMiddle) = ptNetManagerQTask[9].ptPrev;
      v4[33].ptPrev = &ptClient->tQTask;
      ptClient->tReceiveTimeBuffer.nCounter = (int)QTask_NewQTaskRef(v4);
      ptClient->anDR[4] = nullptr;
    }
  }
  else
  {
    v9 = HumanRemote_New(Level_ptDynamicQTask, &igi2_frame.tPos, 0.0, ptClient->zModel, ptClient->eTeam, ptClient->eNetworkID);
    ptClient->tReceiveTimeBuffer.nCounter = (int)QTask_NewQTaskRef(v9);
    v9[33].ptPrev = &ptClient->tQTask;
    ptClient->anDR[4] = nullptr;
  }
}

// source: j/0/network/client.c:3744  [anchor-callee]
int __cdecl Client_GetDeltaSpeedForceUpdate(struct Client_s *ptClient)
{
  int nObjectives; // eax

  nObjectives = ptClient->tStats.nObjectives;
  if ( !nObjectives )
    return 3;
  if ( nObjectives <= 100 )
    return 400;
  if ( nObjectives >= 300 )
    return nObjectives >= 500 ? 50 : 100;
  return 200;
}

// source: j/0/network/client.c:3788  [anchor-callee]
int __cdecl Client_GetHighDelay(struct Client_s *ptClient)
{
  int nObjectives; // eax

  nObjectives = ptClient->tStats.nObjectives;
  if ( !nObjectives )
    return 30;
  if ( nObjectives <= 100 )
    return 150;
  if ( nObjectives <= 150 )
    return 110;
  if ( nObjectives <= 200 )
    return 90;
  if ( nObjectives <= 250 )
    return 80;
  if ( nObjectives <= 300 )
    return 70;
  if ( nObjectives <= 350 )
    return 60;
  if ( nObjectives <= 400 )
    return 50;
  if ( nObjectives > 450 )
    return nObjectives >= 500 ? 30 : 40;
  return 45;
}

// source: j/0/network/client.c:3840  [anchor-callee]
int __cdecl Client_GetLowDelay(struct Client_s *ptClient)
{
  int nObjectives; // eax

  nObjectives = ptClient->tStats.nObjectives;
  if ( !nObjectives )
    return 450;
  if ( nObjectives <= 100 )
    return 1000;
  if ( nObjectives <= 200 )
    return 900;
  if ( nObjectives <= 300 )
    return 800;
  if ( nObjectives > 400 )
    return nObjectives >= 500 ? 550 : 600;
  return 700;
}

// source: j/0/network/client.c:3889  [anchor-hash]
struct ClientMessageCompression_s *__cdecl Client_ClearGameMessageCompression(
        struct ClientMessageCompression_s *ptCompression)
{
  ptCompression->nAlpha = 0;
  ptCompression->nGamma = 0;
  ptCompression->nSpeed = 0;
  ptCompression->nAlphaSpeed = 0;
  ptCompression->nGammaSpeed = 0;
  ptCompression->nTotal = 0;
  return ptCompression;
}

// source: j/0/network/client.c:3910  [anchor-hash]
enum bool __cdecl Client_IsCompressionLossInteresting(
        struct ClientMessageCompression_s *ptCompression)
{
  return ptCompression->nTotal > 0
      && (ptCompression->nSpeed > 0
       || ptCompression->nAlpha > 0
       || ptCompression->nGamma > 0
       || ptCompression->nAlphaSpeed > 0
       || ptCompression->nGammaSpeed > 0);
}

// source: j/0/network/client.c:3932  [anchor-strings]
struct ClientMessageCompression_s *__cdecl Client_CompressionLossDesc(
        struct ClientMessageCompression_s *ptCompression,
        char *zDesc,
        int nLength)
{
  struct ClientMessageCompression_s *result; // eax

  result = (struct ClientMessageCompression_s *)_snprintf(
                                                  zDesc,
                                                  nLength,
                                                  "t[%d]s[%d]a[%d]g[%d]as[%d]gs[%d]",
                                                  ptCompression->nTotal,
                                                  ptCompression->nSpeed,
                                                  ptCompression->nAlpha,
                                                  ptCompression->nGamma,
                                                  ptCompression->nAlphaSpeed,
                                                  ptCompression->nGammaSpeed);
  zDesc[nLength - 1] = 0;
  return result;
}

// source: j/0/network/client.c:3955  [anchor-mhash]
struct ClientMessageCompression_s *__cdecl Client_GetCompressionLoss(
        struct Client_s *ptClient)
{
  int nCounter; // eax
  int v2; // eax
  __int16 v3; // cx

  nCounter = ptClient->tReceiveTimeBuffer.nCounter;
  if ( !nCounter )
    return nullptr;
  v2 = *(_DWORD *)(nCounter + 8);
  v3 = *(_WORD *)(v2 + 36);
  if ( v3 == HumanRemote_eQTaskType )
    return (struct ClientMessageCompression_s *)(v2 + 3296);
  if ( v3 == HumanPlayer_eQTaskType )
    return (struct ClientMessageCompression_s *)(v2 + 3516);
  else
    return nullptr;
}

// source: j/0/network/client.c:3990  [anchor-callee]
void __cdecl Client_CheckCompression(
        struct ClientMessageCompression_s *ptCompression,
        struct real32x3_t *ptSpeed,
        float vAlpha,
        float vAlphaSpeed,
        float vGamma,
        float vGammaSpeed)
{
  double v6; // st7
  double v7; // st7
  double v8; // st7
  double v9; // st7
  double v10; // st7
  double v11; // st7
  double v12; // st7
  float vzDiffa; // [esp+0h] [ebp-10h]
  float vzDiffb; // [esp+0h] [ebp-10h]
  float vzDiffc; // [esp+0h] [ebp-10h]
  float vzDiff; // [esp+0h] [ebp-10h]
  float vxDiff; // [esp+8h] [ebp-8h]
  float vyDiff; // [esp+Ch] [ebp-4h]
  float ptCompressiona = *(float *)&vAlpha; // [esp+14h] [ebp+4h] ARGSLOT
  float vAlphaa = *(float *)&vGamma; // [esp+1Ch] [ebp+Ch] ARGSLOT
  float vAlphaSpeeda = *(float *)&vGammaSpeed; // [esp+20h] [ebp+10h] ARGSLOT

  vzDiffa = ptSpeed->vX;
  v6 = (double)(World_GetScaledUint8FromReal32(ptSpeed->vX, 40960.0) - 127) * 322.5196838378906 - vzDiffa;
  if ( v6 < 0.0 )
    v6 = -v6;
  vxDiff = v6 * 0.000244140625;
  vzDiffb = ptSpeed->vY;
  v7 = (double)(World_GetScaledUint8FromReal32(vzDiffb, 40960.0) - 127) * 322.5196838378906 - vzDiffb;
  if ( v7 < 0.0 )
    v7 = -v7;
  vyDiff = v7 * 0.000244140625;
  vzDiffc = ptSpeed->vZ;
  v8 = (double)(World_GetScaledUint8FromReal32(vzDiffc, 40960.0) - 127) * 322.5196838378906 - vzDiffc;
  if ( v8 < 0.0 )
    v8 = -v8;
  vzDiff = v8 * 0.000244140625;
  v9 = (double)(World_GetScaledUint16FromReal32(vGamma, 3.1415927410125732) - 0x7FFF) * 9.5876726845745e-05 - vGamma;
  if ( v9 < 0.0 )
    v9 = -v9;
  vAlphaa = v9;
  v10 = (double)(World_GetScaledUint8FromReal32(vGammaSpeed, 30.0) - 127) * 0.23622047901153564 - vGammaSpeed;
  if ( v10 < 0.0 )
    v10 = -v10;
  vAlphaSpeeda = v10;
  v11 = (double)(World_GetScaledUint16FromReal32(vAlpha, 1.5707963705062866) - 0x7FFF) * 4.79383634228725e-05 - vAlpha;
  if ( v11 < 0.0 )
    v11 = -v11;
  ptCompressiona = v11;
  v12 = (double)(World_GetScaledUint8FromReal32(vAlphaSpeed, 20.0) - 127) * 0.15748031437397003 - vAlphaSpeed;
  if ( v12 < 0.0 )
    v12 = -v12;
  ++ptCompression->nTotal;
  if ( vxDiff > 0.1 || vyDiff > 0.1 || vzDiff > 0.1 )
    ++ptCompression->nSpeed;
  if ( vAlphaa > 0.03490658476948738 )
    ++ptCompression->nGamma;
  if ( vAlphaSpeeda > 1.0 )
    ++ptCompression->nGammaSpeed;
  if ( ptCompressiona > 0.03490658476948738 )
    ++ptCompression->nAlpha;
  if ( v12 > 1.0 )
    ++ptCompression->nAlphaSpeed;
}

// source: j/0/network/client.c:4068  [anchor-callee]
struct real64x3_t *__cdecl Client_DecompressInput(
        struct ClientGameMessageUpdateBody_s *ptBody,
        struct real64x3_t *ptInPos,
        struct real64x3_t *ptInSpeed,
        float *pvInAlpha,
        float *pvInAlphaSpeed,
        float *pvInGamma,
        float *pvInGammaSpeed)
{
  struct real64x3_t *result; // eax

  ptInPos->vX = (double)ptBody->tPosition.nX;
  ptInPos->vY = (double)ptBody->tPosition.nY;
  ptInPos->vZ = (double)ptBody->tPosition.nZ;
  ptInPos->vX = ptInPos->vX * 0.01;
  ptInPos->vY = ptInPos->vY * 0.01;
  ptInPos->vZ = ptInPos->vZ * 0.01;
  ptInSpeed->vX = (double)(ptBody->vX - 127) * 322.5196838378906;
  ptInSpeed->vY = (double)(ptBody->vY - 127) * 322.5196838378906;
  ptInSpeed->vZ = (double)(ptBody->vZ - 127) * 322.5196838378906;
  ptInPos->vX = ptInPos->vX * 4096.0;
  ptInPos->vY = ptInPos->vY * 4096.0;
  ptInPos->vZ = ptInPos->vZ * 4096.0;
  *pvInAlpha = (double)(ptBody->vAlpha - 0x7FFF) * 4.79383634228725e-05;
  *pvInAlphaSpeed = (double)(ptBody->vAlphaSpeed - 127) * 0.15748031437397003;
  *pvInGamma = (double)(ptBody->vGamma - 0x7FFF) * 9.5876726845745e-05;
  result = (struct real64x3_t *)(ptBody->vGammaSpeed - 127);
  *pvInGammaSpeed = (double)(int)result * 0.23622047901153564;
  return result;
}

// source: j/0/network/client.c:4095  [anchor-callee]
void __cdecl Client_CompressOutput(
        struct ClientGameMessageUpdateBody_s *ptBody,
        struct real32x3_t *ptSpeed,
        float vAlpha,
        float vAlphaSpeed,
        float vGamma,
        float vGammaSpeed)
{
  ptBody->vX = World_GetScaledUint8FromReal32(ptSpeed->vX, 40960.0);
  ptBody->vY = World_GetScaledUint8FromReal32(ptSpeed->vY, 40960.0);
  ptBody->vZ = World_GetScaledUint8FromReal32(ptSpeed->vZ, 40960.0);
  ptBody->vAlpha = World_GetScaledUint16FromReal32(vAlpha, 1.5707963705062866);
  ptBody->vAlphaSpeed = World_GetScaledUint8FromReal32(vAlphaSpeed, 20.0);
  ptBody->vGamma = World_GetScaledUint16FromReal32(vGamma, 3.1415927410125732);
  ptBody->vGammaSpeed = World_GetScaledUint8FromReal32(vGammaSpeed, 30.0);
}

// source: j/0/network/client.c:4120  [size]
void __cdecl Client_CopyOffsetToUpdate(
        struct ClientGameMessageUpdateBody_s *ptUpdate,
        struct ClientGameMessageOffsetBody_s *ptOffset)
{
  ptUpdate->eNetworkID = ptOffset->eNetworkID;
  ptUpdate->vX = ptOffset->vX;
  ptUpdate->vY = ptOffset->vY;
  ptUpdate->vZ = ptOffset->vZ;
  ptUpdate->vAlpha = ptOffset->vAlpha;
  ptUpdate->vGamma = ptOffset->vGamma;
  ptUpdate->vAlphaSpeed = ptOffset->vAlphaSpeed;
  ptUpdate->vGammaSpeed = ptOffset->vGammaSpeed;
  ptUpdate->eAnimState = ptOffset->eAnimState;
  ptUpdate->eUpperBody = ptOffset->eUpperBody;
  ptUpdate->isShowPlayer = ptOffset->isShowPlayer;
}

// source: j/0/network/client.c:4150  [size]
struct ClientGameMessageOffsetBody_s *__cdecl Client_CopyUpdateToOffset(
        struct ClientGameMessageUpdateBody_s *ptUpdate,
        struct ClientGameMessageOffsetBody_s *ptOffset)
{
  ptOffset->eNetworkID = ptUpdate->eNetworkID;
  ptOffset->vX = ptUpdate->vX;
  ptOffset->vY = ptUpdate->vY;
  ptOffset->vZ = ptUpdate->vZ;
  ptOffset->vAlpha = ptUpdate->vAlpha;
  ptOffset->vGamma = ptUpdate->vGamma;
  ptOffset->vAlphaSpeed = ptUpdate->vAlphaSpeed;
  ptOffset->vGammaSpeed = ptUpdate->vGammaSpeed;
  ptOffset->eAnimState = ptUpdate->eAnimState;
  ptOffset->eUpperBody = ptUpdate->eUpperBody;
  ptOffset->isShowPlayer = ptUpdate->isShowPlayer;
  return ptOffset;
}
