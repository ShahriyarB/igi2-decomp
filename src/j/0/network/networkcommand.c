/* j/0/network/networkcommand.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/network/networkcommand.c:49  [anchor-callee]
void __cdecl NetworkCommand_SetEvalResponse(char *zString)
{
  char v1; // cl
  char v2; // cl

  if ( strlen(zString) )
  {
    if ( strlen(zString) >= 0x28 )
    {
      zString[36] = 46;
      zString[37] = 46;
      zString[38] = 46;
      zString[39] = v2;
    }
    strncpy(NetworkCommand_zEvalResponse, zString, 0x28u);
  }
  else
  {
    NetworkCommand_zEvalResponse[0] = v1;
  }
}

// source: j/0/network/networkcommand.c:79  [size]
char *__cdecl NetworkCommand_GetEvalResponse()
{
  return NetworkCommand_zEvalResponse;
}

// source: j/0/network/networkcommand.c:94  [size]
enum bool __cdecl NetworkCommand_isRemoteEval()
{
  return NetworkCommand_eEvalNetworkID != -1;
}

// source: j/0/network/networkcommand.c:111  [size]
int __cdecl NetworkCommand_GetRemoteEvalNetworkID()
{
  return NetworkCommand_eEvalNetworkID;
}

// source: j/0/network/networkcommand.c:130  [size]
enum bool __cdecl NetworkCommand_isSameAsRemoteEval(int eNetworkID)
{
  return NetworkCommand_eEvalNetworkID == eNetworkID;
}

// source: j/0/network/networkcommand.c:156  [anchor-callee]
enum bool __cdecl NetworkCommand_isRemoteEvalSuper()
{
  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
    return NetworkCommand_eEvalNetworkID == 0;
  if ( NetworkCommand_eEvalNetworkID )
    return NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
  return true;
}

// source: j/0/network/networkcommand.c:197  [anchor-strings]
struct Result_s *__cdecl NetworkCommand_AnnounceInt(struct Result_s *retstr, int nValue, int ltcg_ebx)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct Result_s Rs; };
    struct { char igi2_o1[24]; char zMsg[64]; };
    char igi2_extent[88];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  _snprintf(igi2_frame.zMsg, 0x40u, &g_zMessage_0.zTalkString[40], retstr);
  NetworkCommand_SetEvalResponse(igi2_frame.zMsg);
  igi2_frame.Rs.nResult = (int)retstr;
  igi2_frame.Rs.vResult = (double)(int)retstr;
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy((void *)ltcg_ebx, &igi2_frame.Rs, 0x18u);
  return (struct Result_s *)ltcg_ebx;
}

// source: j/0/network/networkcommand.c:215  [anchor-strings]
struct Result_s *__cdecl NetworkCommand_AnnounceFloat(
        struct Result_s *retstr,
        float vValue,
        int ltcg_ebx)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct Result_s Rs; };
    struct { char igi2_o1[24]; char zMsg[64]; };
    char igi2_extent[88];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  _snprintf(igi2_frame.zMsg, 0x40u, &g_zMessage_0.zTalkString[28], *(float *)&retstr);
  NetworkCommand_SetEvalResponse(igi2_frame.zMsg);
  igi2_frame.Rs.nResult = (__int64)*(float *)&retstr;
  igi2_frame.Rs.vResult = *(float *)&retstr;
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy((void *)ltcg_ebx, &igi2_frame.Rs, 0x18u);
  return (struct Result_s *)ltcg_ebx;
}

// source: j/0/network/networkcommand.c:233  [anchor-strings]
struct Result_s *__cdecl NetworkCommand_AnnounceBool(
        struct Result_s *retstr,
        enum bool isValue,
        int ltcg_ebx)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct Result_s Rs; };
    struct { char igi2_o1[24]; char zMsg[64]; };
    char igi2_extent[88];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( isValue )
  {
    _snprintf(igi2_frame.zMsg, 0x40u, &g_zMessage_0.zTalkString[12]);
    NetworkCommand_SetEvalResponse(igi2_frame.zMsg);
    igi2_frame.Rs.nResult = 1;
    HIDWORD(igi2_frame.Rs.vResult) = 1072693248;
  }
  else
  {
    _snprintf(igi2_frame.zMsg, 0x40u, (char *const)&g_zMessage_0.nTalkOffset);
    NetworkCommand_SetEvalResponse(igi2_frame.zMsg);
    igi2_frame.Rs.nResult = 0;
    HIDWORD(igi2_frame.Rs.vResult) = 0;
  }
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  LODWORD(igi2_frame.Rs.vResult) = 0;
  qmemcpy((void *)ltcg_ebx, &igi2_frame.Rs, 0x18u);
  return (struct Result_s *)ltcg_ebx;
}

// source: j/0/network/networkcommand.c:261  [anchor-caller]
int __cdecl NetworkCommand_BuyItem(int nItemID)
{
  struct NetManagerGameMessageList tGameMessage; // [esp+0h] [ebp-30h] BYREF

  tGameMessage.nA = nItemID;
  tGameMessage.nCommandID = 9;
  tGameMessage.nNumberOfLines = 0;
  return (int)NetManager_SendListCommand(&tGameMessage, 0);
}

// source: j/0/network/networkcommand.c:286  [anchor-callee]
struct NetManagerGameMessageList *__cdecl NetworkCommand_SetupEval(char *zEval)
{
  void *v1; // esi
  struct Flow_t *v2; // eax

  v1 = Mem_AllocFn(96, 4);
  v2 = Flow_ptFlow;
  *((_DWORD *)v1 + 3) = 11;
  *((_DWORD *)v1 + 11) = 1;
  *((_DWORD *)v1 + 4) = v2->ptNetManagerQTask[6].tQTaskChildren.ptMiddle;
  strncpy((char *)v1 + 56, zEval, 0x28u);
  return (struct NetManagerGameMessageList *)v1;
}

// source: j/0/network/networkcommand.c:322  [anchor-callee]
void __cdecl NetworkCommand_RemoteEval(char *zEval, int eGivenDestination, enum NetManagerHostSet_e eSet)
{
  struct NetManagerGameMessageList *v3; // edi
  int v4; // esi

  if ( eGivenDestination && strlen((char *)eGivenDestination) < 0x28 )
  {
    v3 = NetworkCommand_SetupEval((char *)eGivenDestination);
    NetManager_SendListCommandTo(v3, (int)zEval, eSet);
    if ( v3 )
    {
      v4 = *(_DWORD *)((unsigned int)&v3[-1].nNumberOfLines & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v4);
      memset(*(void **)(v4 + 8), 0xCDu, *(_DWORD *)(v4 + 16));
      free((void *)v4);
    }
  }
}

// source: j/0/network/networkcommand.c:348  [anchor-strings]
void __cdecl NetworkCommand_Eval_ProcessRequest(struct NetManagerGameMessageList *ptListMessage)
{
  int isConsole; // ebp
  int nA; // edi
  char *v3; // eax
  struct Flow_t *v4; // edx
  struct NetManagerGameMessageList *v5; // esi
  int v6; // esi
  double v; // [esp+10h] [ebp-Ch] BYREF

  isConsole = ptListMessage->isConsole;
  if ( ptListMessage->isConsole )
  {
    if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
    {
      NetManager_LogMessage(&g_zMessage_0.zTeamName[52]);
    }
    else
    {
      NetManager_LogMessage((char *)&g_zMessage_0.tStats.vPacketLoss);
      Console_SetRemoteConsoleEval(&ptListMessage->tSockAddr);
    }
  }
  NetworkCommand_SetEvalResponse((char *)&g_zInitialValue);
  NetworkCommand_eEvalNetworkID = ptListMessage->nA;
  ScriptDebugger_EvaluateExpression((char *)&ptListMessage[1].eClientNetworkID, &v);
  nA = ptListMessage->nA;
  NetworkCommand_eEvalNetworkID = -1;
  if ( !nA || NetManager_GetClientFromNetworkID(nA) )
  {
    v3 = (char *)Mem_AllocFn(96, 4);
    v4 = Flow_ptFlow;
    v5 = (struct NetManagerGameMessageList *)v3;
    *((_DWORD *)v3 + 11) = 1;
    *((_DWORD *)v3 + 3) = 12;
    *((_DWORD *)v3 + 4) = ptListMessage->nA;
    *((_DWORD *)v3 + 5) = v4->ptNetManagerQTask[6].tQTaskChildren.ptMiddle;
    v3[24] = ptListMessage->isConsole;
    *(struct sockaddr *)(v3 + 26) = ptListMessage->tSockAddr;
    strncpy(v3 + 56, NetworkCommand_zEvalResponse, 0x28u);
    NetManager_SendListCommand(v5, ptListMessage->nA);
    v6 = *(_DWORD *)((unsigned int)&v5[-1].nNumberOfLines & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v6);
    memset(*(void **)(v6 + 8), 0xCDu, *(_DWORD *)(v6 + 16));
    free((void *)v6);
  }
  if ( isConsole )
  {
    if ( !Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
    {
      NetManager_LogMessage(&g_zMessage_0.zPlayerName[52]);
      QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, Consoled_eQTaskType)[1].tQTaskRefList.ptHead = nullptr;
    }
  }
}

// source: j/0/network/networkcommand.c:447  [anchor-strings]
struct NetManagerGameMessageList *__cdecl NetworkCommand_Eval_Response(
        struct NetManagerGameMessageList *ptListMessage)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zIP[28]; };
    struct { char igi2_o1[28]; char zMsg[256]; };
    char igi2_extent[284];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  u_short v2; // ax
  struct NetManagerGameMessageList *result; // eax

  if ( ptListMessage->isConsole )
  {
    v2 = ntohs(*(_WORD *)ptListMessage->tSockAddr.sa_data);
    _snprintf(
      igi2_frame.zIP,
      0x16u,
      "%d.%d.%d.%d:%d",
      (unsigned __int8)ptListMessage->tSockAddr.sa_data[2],
      (unsigned __int8)ptListMessage->tSockAddr.sa_data[3],
      (unsigned __int8)ptListMessage->tSockAddr.sa_data[4],
      (unsigned __int8)ptListMessage->tSockAddr.sa_data[5],
      v2);
    _snprintf(igi2_frame.zMsg, 0xFFu, (char *const)&g_zMessage_0.eTeam, igi2_frame.zIP);
    NetManager_LogMessage(igi2_frame.zMsg);
    Network_SendConsoleMessage(
      (struct sockaddr_in *)&ptListMessage->tSockAddr,
      (char *)&ptListMessage[1].eClientNetworkID);
  }
  DebugConsole_printf((char *)&g_zMessage_0.nCreateTime, &ptListMessage[1].eClientNetworkID);
  return result;
}

// source: j/0/network/networkcommand.c:490  [anchor-strings]
void __cdecl NetworkCommand_Buy_Request(struct NetManagerGameMessageList *ptListMessage)
{
  struct Client_s *ClientFromNetworkID; // edi
  struct QTask_s *FirstChildOfType; // eax
  int ptNext; // edx
  int v4; // ecx
  int nA; // ebx
  struct QTask_s **p_ptPrev; // eax

  ClientFromNetworkID = NetManager_GetClientFromNetworkID(ptListMessage->eClientNetworkID);
  FirstChildOfType = QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, Netshop_eQTaskType);
  ptNext = (int)FirstChildOfType[1].ptNext;
  v4 = 0;
  if ( ptNext <= 0 )
  {
LABEL_5:
    Client_UpdateMoneyRemote(ClientFromNetworkID, (char *)&g_zMessage_0);
  }
  else
  {
    nA = ptListMessage->nA;
    p_ptPrev = &FirstChildOfType[1].ptPrev;
    while ( *p_ptPrev != (struct QTask_s *)nA )
    {
      ++v4;
      p_ptPrev += 14;
      if ( v4 >= ptNext )
        goto LABEL_5;
    }
    if ( Netshop_Buy(nA, &ClientFromNetworkID->nUpdateItemTime, ClientFromNetworkID->eTeam) )
    {
      NetManager_AddEquipment(ClientFromNetworkID->eNetworkID, ptListMessage->nA);
      Client_UpdateMoneyRemote(ClientFromNetworkID, (char *)&g_zMessage_0.isSuperUser);
    }
    else
    {
      Client_UpdateMoneyRemote(ClientFromNetworkID, (char *)&g_zMessage_0.tQTask.tQTaskChildren.ptTail);
    }
  }
}

// source: j/0/network/networkcommand.c:539  [anchor-callee]
void __cdecl NetworkCommand_Account_Response(struct NetManagerGameMessageList *ptListMessage)
{
  NetManager_GetClientFromNetworkID((int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle)->nUpdateItemTime = ptListMessage->nB;
}

// source: j/0/network/networkcommand.c:584  [anchor-hash]
void __cdecl NetworkCommand_Textlist_Response(struct NetManagerGameMessageList *ptListMessage)
{
  struct NetManagerGameMessageList *v1; // edi
  int i; // ebx
  char zTemp[256]; // [esp+0h] [ebp-100h] BYREF

  if ( ptListMessage->nNumberOfLines )
  {
    v1 = ptListMessage + 1;
    if ( ptListMessage->isConsole )
      NetManager_LogMessage("NetworkCommand_Textlist_Response: Received console redirect message\n");
    for ( i = 0; i < ptListMessage->nNumberOfLines; ++i )
    {
      _snprintf(zTemp, 0xFFu, "[%d]  %s\n", v1->tBaseMessage.eGameMessage, (char *)&v1->eClientNetworkID);
      DebugConsole_printf(zTemp);
      if ( ptListMessage->isConsole )
        Network_SendConsoleMessage((struct sockaddr_in *)&ptListMessage->tSockAddr, zTemp);
      ++v1;
    }
  }
  else
  {
    DebugConsole_printf("Textlist: No entries found\n");
  }
}

// source: j/0/network/networkcommand.c:635  [anchor-hash]
void __cdecl NetworkCommand_ParseNetListInput(struct NetManagerGameMessageList *ptListMessage)
{
  int eClientNetworkID; // edi

  DebugConsole_PushActiveConsole(NetworkCommand_tConsoleID);
  eClientNetworkID = ptListMessage->eClientNetworkID;
  if ( !eClientNetworkID || NetManager_GetClientFromNetworkID(eClientNetworkID) )
  {
    switch ( ptListMessage->nCommandID )
    {
      case 2:
        NetworkCommand_Textlist_Response(ptListMessage);
        DebugConsole_PopActiveConsole();
        break;
      case 9:
        NetworkCommand_Buy_Request(ptListMessage);
        DebugConsole_PopActiveConsole();
        break;
      case 0xA:
        NetworkCommand_Account_Response(ptListMessage);
        DebugConsole_PopActiveConsole();
        break;
      case 0xB:
        NetworkCommand_Eval_ProcessRequest(ptListMessage);
        DebugConsole_PopActiveConsole();
        break;
      case 0xC:
        NetworkCommand_Eval_Response(ptListMessage);
        DebugConsole_PopActiveConsole();
        break;
      default:
        LDebug_Error("Unknown command type received, commandID=%d", ptListMessage->nCommandID);
        abort();
    }
  }
  else
  {
    DebugConsole_printf("Networkcommand: Unknown remote: %d. Skipping\n", eClientNetworkID);
    DebugConsole_PopActiveConsole();
  }
}

// source: j/0/network/networkcommand.c:694  [size]
int __cdecl NetworkCommand_GetConsoleID()
{
  return NetworkCommand_tConsoleID;
}

// source: j/0/network/networkcommand.c:710  [anchor-strings]
// write access to memory has been detected, the output may be wrong!
void __cdecl NetworkCommand_ParseEval(int argc, char **argv, void *pxCommandContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { double zEval; };
    struct { char igi2_o1[8]; char Buffer[28]; };
    struct { char igi2_o2[36]; char zFormat[256]; };
    char igi2_extent[292];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v3; // edi
  int v4; // ecx
  struct QTask_s *FirstChildOfType; // eax
  struct QReference_s *ptHead; // ecx
  int v7; // eax
  char *v8; // ebx
  int v9; // ebp
  int v10; // edi
  struct QTask_s *v11; // eax
  unsigned __int8 *p_ptPrev; // esi
  u_short v13; // ax
  char v14; // cl
  char v15; // cl
  struct QTask_s *v16; // eax
  int v17; // esi
  int v18; // edx
  struct DebugConsole_s *v19; // ecx
  struct DebugConsole_s *ptNext; // eax
  int v21; // edx

  v3 = 0;
  DebugConsole_PushActiveConsole(NetworkCommand_tConsoleID);
  v4 = 1;
  if ( argc <= 1 )
    goto LABEL_29;
  do
    v3 += strlen(argv[v4++]);
  while ( v4 < argc );
  if ( v3 <= 0 || v3 + 1 > 255 )
  {
LABEL_29:
    DebugConsole_printf("EVAL PARSE: No expression or expression too long\n");
  }
  else
  {
    FirstChildOfType = QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, Consoled_eQTaskType);
    if ( !FirstChildOfType || (ptHead = FirstChildOfType[1].tQTaskRefList.ptHead, LODWORD(igi2_frame.zEval) = 1, !ptHead) )
      LODWORD(igi2_frame.zEval) = 0;
    v7 = v3 + 3;
    if ( argc > 3 )
      v7 = v3 + argc;
    v8 = (char *)Mem_AllocFn(v7, 4);
    *v8 = 0;
    qmemcpy(&v8[strlen(v8)], argv[1], &argv[1][strlen(argv[1]) + 1] - argv[1]);
    v9 = 2;
    for ( *(_WORD *)&v8[strlen(v8)] = 40; v9 < argc; ++v9 )
    {
      if ( v9 > 2 )
        *(_WORD *)&v8[strlen(v8)] = 44;
      qmemcpy(&v8[strlen(v8)], argv[v9], &argv[v9][strlen(argv[v9]) + 1] - argv[v9]);
    }
    *(_WORD *)&v8[strlen(v8)] = g_zSpriteName_0.tQTaskChildren.ptMiddle;
    if ( !strcmp("lo", *argv) )
    {
      v10 = LODWORD(igi2_frame.zEval);
      if ( LODWORD(igi2_frame.zEval) )
      {
        v11 = QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, Consoled_eQTaskType);
        p_ptPrev = (unsigned __int8 *)&v11[1].ptPrev;
        v13 = ntohs(HIWORD(v11[1].ptPrev));
        _snprintf(igi2_frame.Buffer, 0x16u, "%d.%d.%d.%d:%d", p_ptPrev[4], p_ptPrev[5], p_ptPrev[6], p_ptPrev[7], v13);
        _snprintf(igi2_frame.zFormat, 0xFFu, "NetworkCommand_ParseEval: Local console evaluation from %s:'%s'", igi2_frame.Buffer, v8);
        NetManager_LogMessage(igi2_frame.zFormat);
      }
      LODWORD(igi2_frame.zEval) = (char *)&g_zInitialValue.ptQTilemap
                     + strlen((char *)&g_zInitialValue)
                     + 1
                     - (char *)&unk_685646;
      if ( LODWORD(igi2_frame.zEval) )
      {
        if ( (unsigned int)((char *)&g_zInitialValue.ptQTilemap
                          + strlen((char *)&g_zInitialValue)
                          + 1
                          - (char *)&unk_685646) >= 0x28 )
        {
          unk_685669 = 46;
          unk_68566A = unk_685669;
          unk_68566B = unk_685669;
          unk_68566C = v15;
        }
        strncpy(NetworkCommand_zEvalResponse, (char *)&g_zInitialValue, 0x28u);
      }
      else
      {
        NetworkCommand_zEvalResponse[0] = v14;
      }
      ScriptDebugger_EvaluateExpression(v8, &igi2_frame.zEval);
      if ( v10 )
      {
        _snprintf(igi2_frame.zFormat, 0xFFu, "%s:%s", v8, NetworkCommand_zEvalResponse);
        v16 = QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, Consoled_eQTaskType);
        Network_SendConsoleMessage((struct sockaddr_in *)&v16[1].ptPrev, igi2_frame.zFormat);
      }
      else
      {
        DebugConsole_printf("%s  (%.1f)\n", NetworkCommand_zEvalResponse, igi2_frame.zEval);
      }
    }
    else if ( !strcmp("sv", *argv) )
    {
      NetworkCommand_RemoteEval(nullptr, (int)v8, NETMANAGER_HOSTSET_GIVEN_DESTINATION);
    }
    else
    {
      DebugConsole_printf("NetworkCommand_ParseEval: Could not find command\n");
    }
    v17 = *(_DWORD *)((unsigned int)(v8 - 4) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v17);
    memset(*(void **)(v17 + 8), 0xCDu, *(_DWORD *)(v17 + 16));
    free((void *)v17);
  }
  v18 = --DebugConsole_nStackPointer;
  if ( DebugConsole_nStackPointer <= 0 )
  {
    DebugConsole_ptActiveDebugConsole = nullptr;
  }
  else
  {
    v19 = DebugConsole_tConsoleList.ptHead;
    ptNext = DebugConsole_tConsoleList.ptHead->ptNext;
    if ( DebugConsole_tConsoleList.ptHead->ptNext )
    {
      v21 = DebugConsole_atActiveConsoleStack[v18];
      while ( v19->tConsoleID != v21 )
      {
        v19 = ptNext;
        ptNext = ptNext->ptNext;
        if ( !ptNext )
          goto LABEL_35;
      }
    }
    else
    {
LABEL_35:
      v19 = nullptr;
    }
    DebugConsole_ptActiveDebugConsole = v19;
  }
}

// source: j/0/network/networkcommand.c:842  [anchor-caller]
void __cdecl NetworkCommand_ParseEvalCommandLine(char *zCmd)
{
  #pragma pack(push, 1)
  union
  {
    struct { char **argv; };
    struct { char igi2_o1[4]; int argc; };
    char igi2_extent[8];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char **v1; // esi
  int v2; // esi

  DebugConsoleCommand_SplitCommandLine(&igi2_frame.argc, &igi2_frame.argv, zCmd);
  v1 = igi2_frame.argv;
  NetworkCommand_ParseEval(igi2_frame.argc, igi2_frame.argv, nullptr);
  if ( v1 )
  {
    v2 = *(_DWORD *)((unsigned int)(v1 - 1) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v2);
    memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
    free((void *)v2);
  }
}

// source: j/0/network/networkcommand.c:860  [anchor-hash]
void __cdecl NetworkCommand_Open()
{
  NetworkCommand_tConsoleID = DebugConsole_Alloc("IGI2 Console", 100);
  DebugConsole_PushActiveConsole(NetworkCommand_tConsoleID);
  DebugConsoleCommand_Register(
    "sv",
    "[expression]",
    "Evaluate expression at server.",
    NetworkCommand_ParseEval,
    nullptr);
  DebugConsoleCommand_Register("lo", "[expression]", "Evaluate expression locally.", NetworkCommand_ParseEval, nullptr);
  DebugConsole_PopActiveConsole();
  NetworkCommand_eEvalNetworkID = -1;
  NetworkCommand_SetEvalResponse((char *)&g_zInitialValue);
}

// source: j/0/network/networkcommand.c:882  [size~]
void __cdecl NetworkCommand_Close(int ltcg_arg0)
{
  int v1; // eax
  int v2; // eax

  v1 = *(_DWORD *)(ltcg_arg0 + 368);
  if ( v1 )
  {
    v2 = *(_DWORD *)(v1 + 8);
    if ( v2 )
      *(_DWORD *)(v2 + 248) = 0;
  }
  QTask_Delete((struct QTask_s *)ltcg_arg0);
}
