/* j/0/network/radiocom.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/network/radiocom.c:73  [size]
struct RadioCom_s *__cdecl RadioCom_GetRadio()
{
  return (struct RadioCom_s *)QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, RadioCom_eQTaskType);
}

// source: j/0/network/radiocom.c:88  [anchor-hash]
void __cdecl RadioCom_SetActiveSlotSelector()
{
  SlotSelector_ptActiveSelector = (struct SlotSelector_s *)QTask_GetFirstChildOfType(
                                                             Flow_ptFlow->ptNetManagerQTask,
                                                             RadioCom_eQTaskType)[1].ptNext;
}

// source: j/0/network/radiocom.c:107  [anchor-strings]
struct Result_s *__cdecl RadioCom_ActivateCB(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  struct SlotSelector_s *ptNext; // ecx
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  DebugConsole_printf("RadioCom_ActivateCB\n");
  ptNext = (struct SlotSelector_s *)QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, RadioCom_eQTaskType)[1].ptNext;
  SlotSelector_ptActiveSelector = ptNext;
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/radiocom.c:125  [anchor-strings]
int __cdecl RadioCom_PlayerLocate(int hostID)
{
  struct Client_s *ClientFromNetworkID; // esi
  int result; // eax
  int nCounter; // esi
  int v5; // esi
  char zTemp[100]; // [esp+8h] [ebp-64h] BYREF

  ClientFromNetworkID = NetManager_GetClientFromNetworkID(hostID);
  if ( ClientFromNetworkID )
  {
    if ( (struct QTask_s *)hostID == Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
    {
      DebugConsole_printf("RadioCom: Transmitted messages from self\n");
    }
    else
    {
      _snprintf(zTemp, 0x64u, "[%d] %s", hostID, ClientFromNetworkID->zPlayerName);
      DebugConsole_printf("RadioCom: Transmitted messages from %s\n", zTemp);
      nCounter = ClientFromNetworkID->tReceiveTimeBuffer.nCounter;
      if ( nCounter )
      {
        v5 = *(_DWORD *)(nCounter + 8);
        if ( v5 )
        {
          *(_DWORD *)(v5 + 3276) = 100;
          *(_DWORD *)(v5 + 3280) = 100;
        }
      }
    }
  }
  else
  {
    DebugConsole_printf("RadioCom: Transmitted messages from unknown player\n");
  }
  return result;
}

// source: j/0/network/radiocom.c:173  [anchor-hash]
enum bool __cdecl RadioCom_IsMessageCritical(int nMessage)
{
  return nMessage == 52
      || nMessage == 53
      || nMessage == 54
      || nMessage == 65
      || nMessage == 62
      || nMessage == 63
      || nMessage == 64;
}

// source: j/0/network/radiocom.c:203  [anchor-strings]
struct Result_s *__cdecl RadioCom_Say(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int nSound; };
    struct { char igi2_o1[4]; char *zLoc; };
    struct { char igi2_o2[8]; int nCat; };
    struct { char igi2_o3[12]; int hostID; };
    struct { char igi2_o4[16]; char zTemp[24]; };
    struct { char igi2_o5[40]; char Buffer[256]; };
    struct { char igi2_o6[296]; char zRef[256]; };
    char igi2_extent[552];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v3; // edi
  int v4; // ebx
  int v5; // esi
  struct Client_s *v6; // esi
  char *zPlayerName; // eax
  struct Client_s *ClientFromNetworkID; // eax
  int v9; // edi
  int v10; // ebx
  char *LocalizedStringForLanguage; // esi
  char *v12; // ecx
  struct Client_s *v13; // eax
  int v14; // eax

  if ( !ptArgList || ptArgList->nArguments != 3 )
  {
    DebugConsole_printf("RadioCom_Say: Invalid parameters\n");
    goto LABEL_35;
  }
  v3 = Script_EvalArgInt(ptArgList, 0);
  igi2_frame.hostID = v3;
  v4 = Script_EvalArgInt(ptArgList, 1);
  v5 = Script_EvalArgInt(ptArgList, 2);
  igi2_frame.nCat = v4 % 10;
  igi2_frame.nSound = v4 / 10;
  _snprintf(igi2_frame.zRef, 0xFFu, "radio/TEXT_%d_%d", v4 / 10, v4 % 10);
  igi2_frame.zLoc = Config_GetLocalizedStringForLanguage(
           igi2_frame.zRef,
           Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
           true);
  if ( v3 != -1 )
  {
    ClientFromNetworkID = NetManager_GetClientFromNetworkID(v3);
    if ( ClientFromNetworkID )
      zPlayerName = ClientFromNetworkID->zPlayerName;
    else
      zPlayerName = "?UNKNOWN";
    goto LABEL_11;
  }
  v6 = NetManager_GetClientFromNetworkID(v5);
  zPlayerName = Config_GetLocalizedStringForLanguage(
                  "mp/MISSION CONTROL",
                  Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                  true);
  if ( !v6 || v4 != 54 && v4 != 64 )
  {
LABEL_11:
    _snprintf(igi2_frame.Buffer, 0xFFu, "%s: %s", zPlayerName, igi2_frame.zLoc);
    goto LABEL_12;
  }
  _snprintf(igi2_frame.Buffer, 0xFFu, "%s: %s (%s)", zPlayerName, igi2_frame.zLoc, v6->zPlayerName);
LABEL_12:
  if ( v4 == 52 || v4 == 53 || v4 == 54 || v4 == 65 || v4 == 62 || v4 == 63 || v4 == 64 )
    StatusScreen_ShowCritical(igi2_frame.Buffer, TEXTSCROLLER_COLOUR_YELLOW);
  else
    StatusScreen_ShowMessage(igi2_frame.Buffer, TEXTSCROLLER_COLOUR_YELLOW);
  v9 = igi2_frame.nCat;
  v10 = igi2_frame.nSound;
  _snprintf(igi2_frame.zRef, 0xFFu, "radio/SOUND_%d_%d", igi2_frame.nSound, igi2_frame.nCat);
  LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                 igi2_frame.zRef,
                                 Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                 false);
  if ( !LocalizedStringForLanguage || scprintf(LocalizedStringForLanguage, "mpr_%d_%d", &igi2_frame.nCat, &igi2_frame.nSound) != 2 )
    goto LABEL_32;
  if ( v10 >= 5 && v9 != 1 )
  {
    v12 = (char *)LocalizedStringForLanguage;
LABEL_31:
    SoundSys_PlaySimpleSoundFn(v12, 0, nullptr);
    goto LABEL_32;
  }
  v13 = NetManager_GetClientFromNetworkID(igi2_frame.hostID);
  if ( v13 )
  {
    v14 = v13->eModel + 1;
    if ( v14 == 1 || v14 == 2 || v14 == 3 )
    {
      _snprintf(igi2_frame.zTemp, 0x14u, "mpr%d_%d_%d", v14, igi2_frame.nCat, igi2_frame.nSound);
      v12 = igi2_frame.zTemp;
      goto LABEL_31;
    }
  }
LABEL_32:
  if ( igi2_frame.hostID != -1 )
    RadioCom_PlayerLocate(igi2_frame.hostID);
LABEL_35:
  *(_DWORD *)igi2_frame.zTemp = 0;
  *(_DWORD *)&igi2_frame.zTemp[8] = 0;
  *(_DWORD *)&igi2_frame.zTemp[12] = 0;
  *(_DWORD *)&igi2_frame.zTemp[16] = &g_zInitialValue;
  qmemcpy(retstr, igi2_frame.zTemp, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/radiocom.c:345  [anchor-strings]
struct Result_s *__cdecl RadioCom_Broadcast(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  int v3; // eax
  struct QTask_s *ptMiddle; // esi
  char Buffer[40]; // [esp+8h] [ebp-28h] BYREF

  if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    DebugConsole_printf("RadioCom_Broadcast: Not on server");
  }
  else if ( ptArgList && ptArgList->nArguments == 1 )
  {
    v3 = Script_EvalArgInt(ptArgList, 0);
    ptMiddle = (struct QTask_s *)NetworkCommand_eEvalNetworkID;
    if ( NetworkCommand_eEvalNetworkID == -1 )
      ptMiddle = Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle;
    _snprintf(Buffer, 0x28u, "RadioCom_Say(%d,%d,0)", ptMiddle, v3);
    NetworkCommand_RemoteEval((char *)ptMiddle, (int)Buffer, NETMANAGER_HOSTSET_GIVEN_TEAM);
  }
  else
  {
    DebugConsole_printf("RadioCom_Broadcast: Invalid parameters\n");
  }
  *(_DWORD *)Buffer = 0;
  *(_DWORD *)&Buffer[8] = 0;
  *(_DWORD *)&Buffer[12] = 0;
  *(_DWORD *)&Buffer[16] = &g_zInitialValue;
  qmemcpy(retstr, Buffer, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/radiocom.c:393  [anchor-mhash]
struct Result_s *__cdecl RadioCom_SayTextCB(
        struct Result_s *retstr,
        void *pxUnUsed,
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
  struct QReference_s *ptTail; // eax

  if ( ptArgList && ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      igi2_frame.zTemp[0] = 0;
      QVM_EvalArg(igi2_frame.zTemp, 255, ptArgList, 0, 3);
    }
    else
    {
      Expression_EvalString(*ptArgList->aptExpression, igi2_frame.zTemp, 255);
    }
    if ( StatusScreen_ptStatusScreenQTask )
    {
      ptTail = StatusScreen_ptStatusScreenQTask[52].tQTaskRefList.ptTail;
      if ( ptTail )
        TextScroller_Add((struct TextScroller_s *)ptTail, igi2_frame.zTemp, TEXTSCROLLER_COLOUR_GREEN);
    }
    NetManager_LogMessage(igi2_frame.zTemp);
    NetManager_LogMessage("\r\n");
  }
  igi2_frame.Rs.nResult = 0;
  igi2_frame.Rs.vResult = 0.0;
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/radiocom.c:417  [size]
unsigned __int16 __cdecl RadioCom_GetQTaskType()
{
  return RadioCom_eQTaskType;
}

// source: j/0/network/radiocom.c:431  [size]
struct QTask_s *__cdecl RadioCom_New(
        struct QTask_s *ptParentQTask,
        struct RadioComCreateContext_s *ptCreateContext)
{
  return QTask_NewFn(ptParentQTask, RadioCom_eQTaskType, ptCreateContext);
}

// source: j/0/network/radiocom.c:452  [size]
void __cdecl RadioCom_RunHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: j/0/network/radiocom.c:467  [anchor-strings]
void __cdecl RadioCom_ItemPicked(
        struct SlotSelector_s *ptSlotSelector,
        struct SlotCategory_s *ptSlotCategory,
        struct SlotItem_s *ptSlotItem,
        int nSlot)
{
  char Buffer[40]; // [esp+0h] [ebp-28h] BYREF

  _snprintf(Buffer, 0x28u, "RadioCom_Broadcast(%d)", ptSlotItem->nItemID);
  NetworkCommand_RemoteEval(nullptr, (int)Buffer, NETMANAGER_HOSTSET_GIVEN_DESTINATION);
}

// source: j/0/network/radiocom.c:485  [size]
enum bool __cdecl RadioCom_isItemEnabled(int nID)
{
  return true;
}

// source: j/0/network/radiocom.c:500  [anchor-strings]
void __cdecl RadioCom_ItemText(int nID, char *zText)
{
  char *LocalizedStringForLanguage; // eax
  char zTemp[256]; // [esp+0h] [ebp-100h] BYREF

  if ( nID < 11 || nID >= 50 )
  {
    strncpy(zText, "?Out of range", 0x3Cu);
  }
  else
  {
    _snprintf(zTemp, 0xFFu, "radio/TEXT_%d_%d", nID / 10, nID % 10);
    LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                   zTemp,
                                   Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                   true);
    strncpy(zText, LocalizedStringForLanguage, 0x3Cu);
  }
}

// source: j/0/network/radiocom.c:534  [anchor-hash]
void __cdecl RadioCom_Fill(struct RadioCom_s *ptRadio)
{
  unsigned __int16 v1; // dx
  int v2; // ebx
  struct SlotSelector_s *v3; // edi
  int v4; // ebp
  int j; // esi
  struct SlotCategory_s *ptActiveCategory; // eax
  struct QTask_s *FirstChildOfType; // eax
  struct SlotCategory_s *v8; // eax
  int i; // [esp+10h] [ebp-4h]

  v1 = SlotCategory_eQTaskType;
  v2 = 11;
  v3 = SlotSelector_ptActiveSelector;
  v4 = 1;
  for ( i = 11; i <= 41; i += 10 )
  {
    for ( j = 80; j < 116; j += 4 )
    {
      ptActiveCategory = v3->ptActiveCategory;
      if ( !ptActiveCategory || ptActiveCategory->nCategory != v4 )
      {
        FirstChildOfType = QTask_GetFirstChildOfType(&v3->tQTask, v1);
        if ( FirstChildOfType )
        {
          while ( FirstChildOfType[1].ptNext != (struct QTask_s *)v4 )
          {
            FirstChildOfType = QTask_GetNextSiblingOfType(FirstChildOfType, v1);
            if ( !FirstChildOfType )
              goto LABEL_10;
          }
          v3->ptActiveCategory = (struct SlotCategory_s *)FirstChildOfType;
        }
      }
LABEL_10:
      v8 = v3->ptActiveCategory;
      if ( v8 )
        *(struct QTask_s **)((char *)&v8->tQTask.ptNext + j) = (struct QTask_s *)v2;
      ++v2;
    }
    v2 = i + 10;
    ++v4;
  }
  v3->ptActiveCategory = nullptr;
}

// source: j/0/network/radiocom.c:563  [anchor-strings]
void __cdecl RadioCom_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct SlotSelector_s *v2; // eax
  struct SlotCreateContext_s tSlotCreateContext; // [esp+8h] [ebp-Ch] BYREF

  tSlotCreateContext.pfItemClicked = RadioCom_ItemPicked;
  tSlotCreateContext.pfItemEnabled = (enum bool (__cdecl *)(int))RadioCom_isItemEnabled;
  tSlotCreateContext.pfItemText = RadioCom_ItemText;
  v2 = (struct SlotSelector_s *)QTask_NewFn(ptQTask, SlotSelector_eQTaskType, &tSlotCreateContext);
  ptQTask[1].ptNext = &v2->tQTask;
  SlotSelector_ptActiveSelector = v2;
  SlotSelector_CreateCategory("radio/PLAYER_RADIO", 1);
  SlotSelector_CreateCategory("radio/GROUP_RADIO", 2);
  SlotSelector_CreateCategory("RADIO-CAT 3", 3);
  SlotSelector_CreateCategory("RADIO-CAT 4", 4);
  SlotSelector_ptActiveSelector->ptActiveCategory = nullptr;
  RadioCom_Fill((struct RadioCom_s *)ptQTask);
}

// source: j/0/network/radiocom.c:614  [anchor-callee]
void __cdecl RadioCom_AutoTransmit(int eTeam, enum RadioCom_Automatic_e eAutomatic, int eSource, int nInfo)
{
  #pragma pack(push, 1)
  union
  {
    struct { char *zEval; };
    struct { char igi2_o1[4]; char Buffer[40]; };
    char igi2_extent[44];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Client_s *AnyClientOnTeam; // esi
  struct Client_s *v5; // eax
  int v6; // edi
  BOOL v7; // esi

  AnyClientOnTeam = NetManager_GetAnyClientOnTeam(eTeam);
  v5 = NetManager_GetAnyClientOnTeam(eTeam == 0);
  if ( AnyClientOnTeam )
  {
    igi2_frame.zEval = (char *)AnyClientOnTeam->eNetworkID;
    v6 = 1;
  }
  else
  {
    v6 = 0;
  }
  v7 = v5 != nullptr;
  if ( eAutomatic )
  {
    if ( eAutomatic == RADIOCOM_AUTOMATIC_OBJECTIVE )
    {
      if ( v6 )
      {
        if ( eTeam )
          _snprintf(igi2_frame.Buffer, 0x28u, "RadioCom_Say(%d,%d,%d)", eSource, 64, nInfo);
        else
          _snprintf(igi2_frame.Buffer, 0x28u, "RadioCom_Say(%d,%d,%d)", eSource, 54, nInfo);
        NetworkCommand_RemoteEval(igi2_frame.zEval, (int)igi2_frame.Buffer, NETMANAGER_HOSTSET_GIVEN_TEAM);
      }
      if ( v7 )
      {
        if ( eTeam )
          _snprintf(igi2_frame.Buffer, 0x28u, "RadioCom_Say(%d,%d,%d)", eSource, 55, nInfo);
        else
          _snprintf(igi2_frame.Buffer, 0x28u, "RadioCom_Say(%d,%d,%d)", eSource, 65, nInfo);
        goto LABEL_26;
      }
    }
    else
    {
      if ( eAutomatic != RADIOCOM_AUTOMATIC_MISSION )
      {
        LDebug_Error("Automatic radio event unknown");
        abort();
      }
      if ( v6 )
      {
        if ( eTeam )
          _snprintf(igi2_frame.Buffer, 0x28u, "RadioCom_Say(%d,%d,0)", eSource, 62);
        else
          _snprintf(igi2_frame.Buffer, 0x28u, "RadioCom_Say(%d,%d,0)", eSource, 52);
        NetworkCommand_RemoteEval(igi2_frame.zEval, (int)igi2_frame.Buffer, NETMANAGER_HOSTSET_GIVEN_TEAM);
      }
      if ( v7 )
      {
        if ( eTeam )
          _snprintf(igi2_frame.Buffer, 0x28u, "RadioCom_Say(%d,%d,0)", eSource, 53);
        else
          _snprintf(igi2_frame.Buffer, 0x28u, "RadioCom_Say(%d,%d,0)", eSource, 63);
LABEL_26:
        if ( v6 )
          NetworkCommand_RemoteEval(igi2_frame.zEval, (int)igi2_frame.Buffer, NETMANAGER_HOSTSET_OTHER_TEAM);
        else
          NetworkCommand_RemoteEval((char *)0xFFFFFFFF, (int)igi2_frame.Buffer, NETMANAGER_HOSTSET_ALL);
      }
    }
  }
  else if ( v6 )
  {
    _snprintf(igi2_frame.Buffer, 0x28u, "RadioCom_Say(%d,%d,0)", eSource, 51);
    NetworkCommand_RemoteEval(igi2_frame.zEval, (int)igi2_frame.Buffer, NETMANAGER_HOSTSET_GIVEN_TEAM);
  }
}

// source: j/0/network/radiocom.c:756  [size]
void __cdecl RadioCom_Close()
{
  QTask_DeleteQTaskType(RadioCom_eQTaskType);
}

// source: j/0/network/radiocom.c:770  [anchor-hash]
void __cdecl RadioCom_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("RadioCom", 44, BaseQTaskType, 0, 0);
  RadioCom_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 0, RadioCom_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, (void (__cdecl *)(struct QTask_s *))RadioCom_RunHandler);
  Symbol_Register(
    "RadioCom_Activate",
    RadioCom_ActivateCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "RadioCom_Broadcast",
    RadioCom_Broadcast,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "RadioCom_Say",
    RadioCom_Say,
    nullptr,
    3,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "RadioCom_SayText",
    RadioCom_SayTextCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}
