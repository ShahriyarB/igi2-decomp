/* j/0/network/netshop.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/network/netshop.c:59  [size]
unsigned __int16 __cdecl Netshop_GetQTaskType()
{
  return Netshop_eQTaskType;
}

// source: j/0/network/netshop.c:75  [size]
struct Netshop_s *__cdecl Netshop_GetShop()
{
  return (struct Netshop_s *)QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, Netshop_eQTaskType);
}

// source: j/0/network/netshop.c:90  [anchor-hash]
void __cdecl Netshop_SetActiveSlotSelector()
{
  SlotSelector_ptActiveSelector = (struct SlotSelector_s *)QTask_GetFirstChildOfType(
                                                             Flow_ptFlow->ptNetManagerQTask,
                                                             Netshop_eQTaskType)[169].ptPrev;
}

// source: j/0/network/netshop.c:110  [anchor-strings]
struct Result_s *__cdecl Netshop_ActivateCB(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  struct SlotSelector_s *ptPrev; // ecx
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  DebugConsole_printf(&g_zMessage.zTalkString[148]);
  ptPrev = (struct SlotSelector_s *)QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, Netshop_eQTaskType)[169].ptPrev;
  SlotSelector_ptActiveSelector = ptPrev;
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/netshop.c:128  [size~]
int __cdecl Netshop_IsAvailable(int nItemID)
{
  struct QTask_s *FirstChildOfType; // eax
  int ptNext; // edx
  int v4; // ecx
  struct QTask_s **i; // eax
  struct WeaponType_s *WeaponTypeFromID; // eax

  FirstChildOfType = QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, Netshop_eQTaskType);
  ptNext = (int)FirstChildOfType[1].ptNext;
  v4 = 0;
  if ( ptNext <= 0 )
    return 0;
  for ( i = &FirstChildOfType[1].ptPrev; *i != (struct QTask_s *)nItemID; i += 14 )
  {
    if ( ++v4 >= ptNext )
      return 0;
  }
  if ( *((_BYTE *)i + 40) )
    return 0;
  WeaponTypeFromID = WeaponType_GetWeaponTypeFromID(nItemID);
  return WeaponTypeFromID && WeaponTypeFromID->nShopCategory == 4;
}

// source: j/0/network/netshop.c:276  [anchor-callee]
enum bool __cdecl Netshop_IsAmmoFull(int nID, enum bool isAmmoFullForGun, int ltcg_arg1)
{
  struct QTask_s *FirstChildOfType; // eax
  int ptNext; // edx
  int v6; // ecx
  struct QTask_s **p_ptPrev; // eax
  struct WeaponType_s *WeaponTypeFromID; // eax

  FirstChildOfType = QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, Netshop_eQTaskType);
  ptNext = (int)FirstChildOfType[1].ptNext;
  v6 = 0;
  if ( ptNext <= 0 )
  {
LABEL_5:
    p_ptPrev = nullptr;
  }
  else
  {
    p_ptPrev = &FirstChildOfType[1].ptPrev;
    while ( *p_ptPrev != (struct QTask_s *)nID )
    {
      ++v6;
      p_ptPrev += 14;
      if ( v6 >= ptNext )
        goto LABEL_5;
    }
  }
  if ( *((_BYTE *)p_ptPrev + 40) )
    return false;
  WeaponTypeFromID = WeaponType_GetWeaponTypeFromID(nID);
  if ( !WeaponTypeFromID )
    return false;
  else
    return Weapon_IsInInventoryAndFull(
             (struct Weapon_s *)HumanPlayer_ptQTask[33].ptNext,
             WeaponTypeFromID,
             isAmmoFullForGun,
             ltcg_arg1);
}

int __cdecl sub_45E5A0(int nItemID)
{
  struct QTask_s *ptNetManagerQTask; // eax
  enum bool ptPrev_low; // eax

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  if ( ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
    ptPrev_low = SLOBYTE(ptNetManagerQTask[6].ptPrev);
  else
    ptPrev_low = ServerConfig_tServerConfig.isAllowSniperRifles;
  if ( ptPrev_low )
    return 0;
  else
    return Netshop_IsAvailable(nItemID);
}

// source: j/0/network/netshop.c:318  [anchor-caller]
enum bool __cdecl Netshop_isItemEnabled(int nID)
{
  struct Client_s *ClientFromNetworkID; // ebp
  int eTeam; // ebx
  struct Netshop_Item_s *Item; // edi
  enum bool v5; // ebx
  int v6; // eax
  int nCost; // esi
  int v8; // [esp+8h] [ebp-8h]
  int ptHead_low; // [esp+Ch] [ebp-4h]

  ClientFromNetworkID = NetManager_GetClientFromNetworkID((int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
  if ( !ClientFromNetworkID || !HumanPlayer_ptQTask )
    return false;
  eTeam = ClientFromNetworkID->eTeam;
  Item = Netshop_GetItem(nID);
  if ( !Item )
    return false;
  ptHead_low = SLOBYTE(HumanPlayer_ptQTask[29].tQTaskRefList.ptHead);
  if ( eTeam )
  {
    if ( eTeam != 1 || !Item->isBadBuyable )
      goto LABEL_7;
  }
  else if ( !Item->isGoodBuyable )
  {
LABEL_7:
    v8 = 0;
    goto LABEL_8;
  }
  v8 = 1;
LABEL_8:
  v5 = Netshop_IsAmmoFull(nID, false, -1);
  v6 = sub_45E5A0(nID);
  nCost = Item->nCost;
  if ( ptHead_low )
  {
    if ( v6 || ClientFromNetworkID->nUpdateItemTime < nCost || !v8 || v5 )
      return false;
  }
  else if ( v6 || ClientFromNetworkID->nUpdateItemTime < nCost || !v8 )
  {
    return false;
  }
  return true;
}

// source: j/0/network/netshop.c:392  [anchor-callee]
struct WeaponType_s *__cdecl Netshop_GetWeaponForAmmoSlot(int nSlot, int *nFireType)
{
  struct QTask_s *ptNext; // eax
  struct WeaponType_s *result; // eax

  if ( !HumanPlayer_ptQTask )
    return nullptr;
  ptNext = HumanPlayer_ptQTask[33].ptNext;
  switch ( nSlot )
  {
    case 1:
      result = Weapon_GetNextEnabledWeaponTypeFromCategory(ptNext, WEAPONCATEGORY_PRIMARY, nullptr);
      *nFireType = 0;
      break;
    case 2:
      result = Weapon_GetNextEnabledWeaponTypeFromCategory(ptNext, WEAPONCATEGORY_SIDEARM, nullptr);
      *nFireType = 0;
      break;
    case 3:
      result = Weapon_GetNextEnabledWeaponTypeFromCategory(ptNext, WEAPONCATEGORY_PRIMARY, nullptr);
      *nFireType = 1;
      break;
    case 4:
      result = Weapon_GetNextEnabledWeaponTypeFromCategory(ptNext, WEAPONCATEGORY_MEDIPACK, nullptr);
      *nFireType = 0;
      break;
    default:
      *nFireType = -1;
      result = nullptr;
      break;
  }
  return result;
}

// source: j/0/network/netshop.c:457  [anchor-callee]
struct Netshop_Item_s *__cdecl Netshop_GetFromAmmoID(int nAmmoID)
{
  struct QTask_s *FirstChildOfType; // eax
  int ptNext; // esi
  int v3; // edx
  struct QTaskNodeList_s *i; // ecx
  struct Netshop_Item_s *result; // eax

  FirstChildOfType = QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, Netshop_eQTaskType);
  ptNext = (int)FirstChildOfType[1].ptNext;
  v3 = 0;
  if ( ptNext <= 0 )
    return nullptr;
  for ( i = &FirstChildOfType[2].tQTaskChildren; ; i = (struct QTaskNodeList_s *)((char *)i + 56) )
  {
    result = (struct Netshop_Item_s *)&i[-4].ptMiddle;
    if ( LOBYTE(i[-1].ptTail) == 1 && i->ptHead == (struct QTask_s *)nAmmoID )
      break;
    if ( ++v3 >= ptNext )
      return nullptr;
  }
  return result;
}

// source: j/0/network/netshop.c:491  [anchor-callee]
void __cdecl Netshop_AddMoneyToClient(int eNetworkID, int nMoney)
{
  struct Client_s *ClientFromNetworkID; // eax
  int nUpdateItemTime; // edx
  int nMoneyKill; // ecx
  bool v5; // zf
  char *v6; // ecx

  ClientFromNetworkID = NetManager_GetClientFromNetworkID(eNetworkID);
  nUpdateItemTime = ClientFromNetworkID->nUpdateItemTime;
  nMoneyKill = nUpdateItemTime + nMoney;
  if ( nUpdateItemTime + nMoney >= 0 )
  {
    if ( ServerConfig_tServerConfig.nMoneyKill < nMoneyKill )
      nMoneyKill = ServerConfig_tServerConfig.nMoneyKill;
  }
  else
  {
    nMoneyKill = 0;
  }
  ClientFromNetworkID->nUpdateItemTime = nMoneyKill;
  v5 = nUpdateItemTime == nMoneyKill;
  v6 = &g_zMessage.zModel[8];
  if ( v5 )
    v6 = &g_zMessage.zTeamName[48];
  Client_UpdateMoneyRemote(ClientFromNetworkID, v6);
}

// source: j/0/network/netshop.c:525  [anchor-strings]
int __cdecl Netshop_SetMoneyAtClient(int eNetworkID, int nMoney)
{
  struct Client_s *ClientFromNetworkID; // eax
  int nMoneyKill; // edx
  bool v5; // zf
  char *zTeamName; // ecx
  int result; // eax

  ClientFromNetworkID = NetManager_GetClientFromNetworkID(eNetworkID);
  nMoneyKill = nMoney;
  if ( nMoney >= 0 )
  {
    if ( ServerConfig_tServerConfig.nMoneyKill < nMoney )
      nMoneyKill = ServerConfig_tServerConfig.nMoneyKill;
  }
  else
  {
    nMoneyKill = 0;
  }
  v5 = ClientFromNetworkID->nUpdateItemTime == nMoneyKill;
  ClientFromNetworkID->nUpdateItemTime = nMoneyKill;
  zTeamName = &g_zMessage.zTeamName[24];
  if ( v5 )
    zTeamName = g_zMessage.zTeamName;
  Client_UpdateMoneyRemote(ClientFromNetworkID, zTeamName);
  return result;
}

// source: j/0/network/netshop.c:559  [anchor-caller]
int __cdecl Netshop_ResetMoneyAtClient(int eNetworkID)
{
  struct Client_s *ClientFromNetworkID; // ecx
  int result; // eax

  ClientFromNetworkID = NetManager_GetClientFromNetworkID(eNetworkID);
  result = ServerConfig_tServerConfig.nMoneyCap;
  if ( ClientFromNetworkID->nUpdateItemTime < ServerConfig_tServerConfig.nMoneyCap )
    return Netshop_SetMoneyAtClient(eNetworkID, ServerConfig_tServerConfig.nMoneyCap);
  return result;
}

// source: j/0/network/netshop.c:586  [anchor-caller]
void __cdecl Netshop_AddMoneyToTeam(int nMoney, int eTeam)
{
  struct QTask_s *v2; // ebx
  struct Flow_t *v3; // edi
  unsigned __int16 v4; // dx
  struct QTask_s *v5; // eax
  struct QTask_s *ptNext; // esi
  struct Client_s *v7; // eax
  int nUpdateItemTime; // edx
  int nMoneyKill; // ecx
  bool v10; // zf
  char *v11; // ecx

  v2 = nullptr;
LABEL_2:
  v3 = Flow_ptFlow;
  v4 = Client_eQTaskType;
  while ( 1 )
  {
    v5 = v2 ? QTask_GetNextSiblingOfType(v2, v4) : QTask_GetFirstChildOfType(v3->ptNetManagerQTask, v4);
    v2 = v5;
    if ( !v5 )
      break;
    if ( v5[1].tQTaskRefList.ptHead == (struct QReference_s *)eTeam )
    {
      ptNext = v5[1].ptNext;
      v7 = nullptr;
      while ( 1 )
      {
        v7 = (struct Client_s *)(v7
                               ? QTask_GetNextSiblingOfType(&v7->tQTask, v4)
                               : QTask_GetFirstChildOfType(v3->ptNetManagerQTask, v4));
        if ( !v7 )
          break;
        if ( (struct QTask_s *)v7->eNetworkID == ptNext )
          goto LABEL_16;
      }
      v7 = nullptr;
LABEL_16:
      nUpdateItemTime = v7->nUpdateItemTime;
      nMoneyKill = nUpdateItemTime + nMoney;
      if ( nUpdateItemTime + nMoney >= 0 )
      {
        if ( ServerConfig_tServerConfig.nMoneyKill < nMoneyKill )
          nMoneyKill = ServerConfig_tServerConfig.nMoneyKill;
      }
      else
      {
        nMoneyKill = 0;
      }
      v7->nUpdateItemTime = nMoneyKill;
      v10 = nUpdateItemTime == nMoneyKill;
      v11 = &g_zMessage.zModel[8];
      if ( v10 )
        v11 = &g_zMessage.zTeamName[48];
      Client_UpdateMoneyRemote(v7, v11);
      goto LABEL_2;
    }
  }
}

// source: j/0/network/netshop.c:618  [anchor-callee]
void __cdecl Netshop_AddMoneyAll(int nMoney)
{
  struct QTask_s *v1; // ebx
  struct Flow_t *v2; // edi
  unsigned __int16 v3; // dx
  struct QTask_s *v4; // eax
  struct QTask_s *ptNext; // esi
  struct Client_s *v6; // eax
  int nUpdateItemTime; // edx
  int nMoneyKill; // ecx
  bool v9; // zf
  char *v10; // ecx

  v1 = nullptr;
  while ( 1 )
  {
    v2 = Flow_ptFlow;
    v3 = Client_eQTaskType;
    v4 = v1
       ? QTask_GetNextSiblingOfType(v1, Client_eQTaskType)
       : QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, Client_eQTaskType);
    v1 = v4;
    if ( !v4 )
      break;
    ptNext = v4[1].ptNext;
    v6 = nullptr;
    while ( 1 )
    {
      v6 = (struct Client_s *)(v6
                             ? QTask_GetNextSiblingOfType(&v6->tQTask, v3)
                             : QTask_GetFirstChildOfType(v2->ptNetManagerQTask, v3));
      if ( !v6 )
        break;
      if ( (struct QTask_s *)v6->eNetworkID == ptNext )
        goto LABEL_14;
    }
    v6 = nullptr;
LABEL_14:
    nUpdateItemTime = v6->nUpdateItemTime;
    nMoneyKill = nUpdateItemTime + nMoney;
    if ( nUpdateItemTime + nMoney >= 0 )
    {
      if ( ServerConfig_tServerConfig.nMoneyKill < nMoneyKill )
        nMoneyKill = ServerConfig_tServerConfig.nMoneyKill;
    }
    else
    {
      nMoneyKill = 0;
    }
    v6->nUpdateItemTime = nMoneyKill;
    v9 = nUpdateItemTime == nMoneyKill;
    v10 = &g_zMessage.zModel[8];
    if ( v9 )
      v10 = &g_zMessage.zTeamName[48];
    Client_UpdateMoneyRemote(v6, v10);
  }
}

// source: j/0/network/netshop.c:648  [anchor-strings]
struct Result_s *__cdecl Netshop_AddMoneyAllCB(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  __int32 isSuperUser; // eax
  int v4; // esi
  char zTemp[40]; // [esp+8h] [ebp-28h] BYREF

  if ( NetworkCommand_eEvalNetworkID != -1 )
  {
    if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
    {
      isSuperUser = NetworkCommand_eEvalNetworkID == 0;
    }
    else
    {
      if ( !NetworkCommand_eEvalNetworkID )
        goto LABEL_8;
      isSuperUser = NetManager_GetClientFromNetworkID(NetworkCommand_eEvalNetworkID)->isSuperUser;
    }
    if ( !isSuperUser )
    {
      _snprintf(zTemp, 0x28u, &g_zFileName.atSpriteResources[18].zResourceFilename[28]);
      goto LABEL_12;
    }
  }
LABEL_8:
  if ( ptArgList && ptArgList->nArguments == 1 )
  {
    v4 = Script_EvalArgInt(ptArgList, 0);
    Netshop_AddMoneyAll(v4);
    _snprintf(zTemp, 0x28u, &g_zMessage.zPlayerName[36], v4);
  }
  else
  {
    _snprintf(zTemp, 0x28u, &g_zMessage.zPlayerName[8]);
  }
LABEL_12:
  NetworkCommand_SetEvalResponse(zTemp);
  *(_DWORD *)zTemp = 0;
  *(_DWORD *)&zTemp[8] = 0;
  *(_DWORD *)&zTemp[12] = 0;
  *(_DWORD *)&zTemp[16] = &g_zInitialValue;
  qmemcpy(retstr, zTemp, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/netshop.c:684  [anchor-strings]
struct Result_s *__cdecl Netshop_ListMoneyAllCB(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  struct QTask_s *ptNetManagerQTask; // edi
  unsigned __int16 v4; // dx
  struct QTask_s *v5; // eax
  int i; // esi
  struct NetManagerGameMessageList *v7; // ebx
  struct NetManagerGameMessageList *v8; // edi
  struct QTask_s *v9; // esi
  struct QTask_s *v10; // eax
  char zTemp[40]; // [esp+8h] [ebp-28h] BYREF

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  if ( ptNetManagerQTask[6].tQTaskChildren.ptMiddle || NetworkCommand_eEvalNetworkID == -1 )
  {
    strncpy(zTemp, "Not on server or not remote eval", 0x28u);
  }
  else if ( NetworkCommand_isRemoteEvalSuper() )
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
      strncpy(zTemp, (char *)&g_zMessage.eFace, 0x28u);
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
        _snprintf(
          (char *const)&v8->eClientNetworkID,
          0x28u,
          (char *const)&g_zMessage.eTeam,
          &v10[2],
          v10[15].tQTaskChildren.ptHead);
        v8->tBaseMessage.eGameMessage = (unsigned int)v9[1].ptNext;
        ++v8;
      }
      NetManager_SendListCommand(v7, NetworkCommand_eEvalNetworkID);
      Mem_DeAllocFn(v7);
    }
    else
    {
      strncpy(zTemp, "No players found", 0x28u);
    }
  }
  else
  {
    strncpy(zTemp, &g_zFileName.atSpriteResources[18].zResourceFilename[28], 0x28u);
  }
  NetworkCommand_SetEvalResponse(zTemp);
  *(_DWORD *)zTemp = 0;
  *(_DWORD *)&zTemp[8] = 0;
  *(_DWORD *)&zTemp[12] = 0;
  *(_DWORD *)&zTemp[16] = &g_zInitialValue;
  qmemcpy(retstr, zTemp, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/netshop.c:764  [anchor-callee]
enum bool __cdecl Netshop_isOpenToLocal()
{
  return !HumanPlayer_ptQTask
      || !LOBYTE(HumanPlayer_ptQTask[80].tQTaskChildren.ptTail)
      || SpawnArea_isInsideAnyActiveSpawnAreaForTeam(
           (int)HumanPlayer_ptQTask[10].tQTaskRefList.ptTail,
           (struct real64x3_t *)&HumanPlayer_ptQTask[1]) != false;
}

// source: j/0/network/netshop.c:782  [anchor-mhash]
struct Result_s *__cdecl Netshop_isOpenToLocalCB(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  BOOL v3; // eax
  struct Result_s Rs; // [esp+Ch] [ebp-18h] BYREF

  v3 = HumanPlayer_ptQTask
    && LOBYTE(HumanPlayer_ptQTask[80].tQTaskChildren.ptTail)
    && SpawnArea_isInsideAnyActiveSpawnAreaForTeam(
         (int)HumanPlayer_ptQTask[10].tQTaskRefList.ptTail,
         (struct real64x3_t *)&HumanPlayer_ptQTask[1]) == false;
  Rs.zResult = (char *)&g_zInitialValue;
  Rs.nResult = !v3;
  Rs.vResult = (double)Rs.nResult;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/netshop.c:800  [anchor-strings]
int __cdecl Netshop_ItemClicked(int nID)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct NetManagerGameMessageList ptGameMessage; };
    struct { char igi2_o1[48]; char Buffer[256]; };
    char igi2_extent[304];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Client_s *ClientFromNetworkID; // esi
  int v3; // eax
  int result; // eax

  if ( nID < 0 )
  {
    NetManager_LogMessage("Netshop: Bad item ID. Purchase canceled\n");
  }
  else
  {
    ClientFromNetworkID = NetManager_GetClientFromNetworkID((int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
    v3 = Netshop_Buy(nID, &ClientFromNetworkID->nUpdateItemTime, ClientFromNetworkID->eTeam);
    if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
    {
      _snprintf(igi2_frame.Buffer, 0xFFu, "Netshop: Sending buy request, nItemnID=%d\n", nID);
      NetManager_LogMessage(igi2_frame.Buffer);
      igi2_frame.ptGameMessage.nCommandID = 9;
      igi2_frame.ptGameMessage.nNumberOfLines = 0;
      igi2_frame.ptGameMessage.nA = nID;
      return (int)NetManager_SendListCommand(&igi2_frame.ptGameMessage, 0);
    }
    else if ( v3 )
    {
      NetManager_AddEquipment(0, nID);
      Client_UpdateMoneyRemote(ClientFromNetworkID, (char *)&g_zMessage.tQTask.tQTaskRefList.ptMiddle);
    }
    else
    {
      Client_UpdateMoneyRemote(ClientFromNetworkID, (char *)&g_zMessage);
    }
  }
  return result;
}

// source: j/0/network/netshop.c:861  [anchor-strings]
void __cdecl Netshop_ItemPicked(
        struct SlotSelector_s *ptSlotSelector,
        struct SlotCategory_s *ptSlotCategory,
        struct SlotItem_s *ptSlotItem,
        int nSlot)
{
  char zTemp[256]; // [esp+4h] [ebp-100h] BYREF

  _snprintf(
    zTemp,
    0xFFu,
    "Netshop_ItemPicked(): cat=%d,slot=%d,id=%d\n",
    ptSlotCategory->nCategory,
    nSlot,
    ptSlotItem->nItemID);
  NetManager_LogMessage(zTemp);
  Netshop_ItemClicked(ptSlotItem->nItemID);
}

// source: j/0/network/netshop.c:891  [anchor-strings]
void __cdecl Netshop_AmmoPicked(
        struct SlotSelector_s *ptSlotSelector,
        struct SlotCategory_s *ptSlotCategory,
        struct SlotItem_s *ptSlotItem,
        int nSlot)
{
  #pragma pack(push, 1)
  union
  {
    struct { int nFireType; };
    struct { char igi2_o1[4]; char zTemp[256]; };
    char igi2_extent[260];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct WeaponType_s *WeaponForAmmoSlot; // eax
  struct AmmoType_s *AmmoTypeForWeaponFire; // eax
  struct Netshop_Item_s *v6; // eax

  igi2_frame.nFireType = 0;
  WeaponForAmmoSlot = Netshop_GetWeaponForAmmoSlot(nSlot, &igi2_frame.nFireType);
  if ( WeaponForAmmoSlot )
  {
    AmmoTypeForWeaponFire = WeaponType_GetAmmoTypeForWeaponFire(WeaponForAmmoSlot, igi2_frame.nFireType);
    if ( AmmoTypeForWeaponFire )
    {
      v6 = Netshop_GetFromAmmoID(AmmoTypeForWeaponFire->eAmmoTypeID);
      if ( v6 )
        Netshop_ItemClicked(v6->nItemID);
      else
        NetManager_LogMessage("Netshop: No item found for ammo\n");
    }
    else
    {
      NetManager_LogMessage("Netshop: No ammo found for weapon fire\n");
    }
  }
  else
  {
    _snprintf(igi2_frame.zTemp, 0xFFu, "Netshop: No weapon or ammo found. AmmoPicked nSlot=%d\n", nSlot);
    NetManager_LogMessage(igi2_frame.zTemp);
  }
}

// source: j/0/network/netshop.c:938  [anchor-strings]
void __cdecl Netshop_ItemText(int nID, char *zText)
{
  struct QTask_s *FirstChildOfType; // eax
  int ptNext; // edx
  int v4; // ecx
  struct QTask_s **p_ptPrev; // esi
  char *LocalizedStringForLanguage; // eax
  char Buffer[256]; // [esp+8h] [ebp-100h] BYREF

  FirstChildOfType = QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, Netshop_eQTaskType);
  ptNext = (int)FirstChildOfType[1].ptNext;
  v4 = 0;
  if ( ptNext <= 0 )
  {
LABEL_5:
    strncpy(zText, "(Netshop: No item)", 0x3Cu);
  }
  else
  {
    p_ptPrev = &FirstChildOfType[1].ptPrev;
    while ( *p_ptPrev != (struct QTask_s *)nID )
    {
      ++v4;
      p_ptPrev += 14;
      if ( v4 >= ptNext )
        goto LABEL_5;
    }
    _snprintf(Buffer, 0xFFu, "weapons/strings/%s", (char *)p_ptPrev + 4);
    LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                   Buffer,
                                   Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                   false);
    if ( LocalizedStringForLanguage )
      _snprintf(zText, 0x3Cu, "$%d: %s", p_ptPrev[9], LocalizedStringForLanguage);
    else
      _snprintf(zText, 0x3Cu, "$%d: %s", p_ptPrev[9], (char *)p_ptPrev + 4);
  }
}

// source: j/0/network/netshop.c:963  [anchor-strings]
struct Result_s *__cdecl Netshop_InventoryCB(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { _DWORD v8[6]; };
    struct { char igi2_o1[24]; char Destination[60]; };
    char igi2_extent[84];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v3; // esi
  struct ArgList_s *v4; // edi
  struct ArgList_s *v5; // eax
  struct Weapon_s *ptNext; // ecx

  v3 = HumanPlayer_ptQTask;
  v4 = ptArgList;
  if ( ptArgList->isQVM )
  {
    ptArgList = nullptr;
    QVM_EvalArg(&ptArgList, 4, v4, 1, 1);
    v5 = ptArgList;
  }
  else
  {
    v5 = (struct ArgList_s *)Expression_EvalInt(ptArgList->aptExpression[1]);
  }
  if ( v3 )
  {
    ptNext = (struct Weapon_s *)v3[33].ptNext;
    if ( ptNext )
    {
      if ( (unsigned int)v5 > 0xC )
        strncpy(igi2_frame.Destination, "?OUT OF RANGE", 0x3Cu);
      else
        Weapon_CategoryDescription(ptNext, (enum WeaponCategory_e)v5, igi2_frame.Destination, 0x3Cu);
      MenuText_SetText(-1, igi2_frame.Destination);
    }
    else
    {
      strncpy(igi2_frame.Destination, "?NO WEAPON FOUND", 0x3Cu);
    }
  }
  else
  {
    strncpy(igi2_frame.Destination, "?NO PLAYER FOUND", 0x3Cu);
  }
  igi2_frame.v8[0] = 0;
  igi2_frame.v8[2] = 0;
  igi2_frame.v8[3] = 0;
  igi2_frame.v8[4] = &g_zInitialValue;
  qmemcpy(retstr, igi2_frame.v8, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/netshop.c:1012  [anchor-strings]
void __cdecl Netshop_AmmoText(int nID, char *zText)
{
  struct WeaponType_s *WeaponForAmmoSlot; // eax
  struct WeaponType_s *v3; // ebx
  struct AmmoType_s *AmmoTypeForWeaponFire; // eax
  struct AmmoType_s *v5; // esi
  char *LocalizedStringForLanguage; // ebx
  struct Netshop_Item_s *v7; // eax
  int nPickupAmount; // ecx
  int nFireType; // [esp+0h] [ebp-4h] BYREF

  nFireType = 0;
  WeaponForAmmoSlot = Netshop_GetWeaponForAmmoSlot(nID, &nFireType);
  v3 = WeaponForAmmoSlot;
  if ( WeaponForAmmoSlot )
  {
    AmmoTypeForWeaponFire = WeaponType_GetAmmoTypeForWeaponFire(WeaponForAmmoSlot, nFireType);
    v5 = AmmoTypeForWeaponFire;
    if ( AmmoTypeForWeaponFire )
    {
      nFireType = strlen(AmmoTypeForWeaponFire->zAmmoTypeScriptID);
      if ( nFireType )
        LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                       v5->zShopNameResource,
                                       Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                       true);
      else
        LocalizedStringForLanguage = v3->zName;
      v7 = Netshop_GetFromAmmoID(v5->eAmmoTypeID);
      nPickupAmount = v7->nPickupAmount;
      if ( nPickupAmount <= 0 )
        _snprintf(zText, 0x3Cu, "$%4d: %s", v7->nCost, LocalizedStringForLanguage);
      else
        _snprintf(zText, 0x3Cu, "$%4d: %s (%d)", v7->nCost, LocalizedStringForLanguage, nPickupAmount);
    }
    else
    {
      strncpy(zText, " - ", 0x3Cu);
    }
  }
  else
  {
    _snprintf(zText, 0x3Cu, " - ");
  }
}

// source: j/0/network/netshop.c:1076  [anchor-callee]
enum bool __cdecl Netshop_isAmmoEnabled(int nID)
{
  struct Client_s *ClientFromNetworkID; // ebp
  struct WeaponType_s *WeaponForAmmoSlot; // eax
  struct WeaponType_s *v3; // ebx
  enum bool v4; // esi
  struct AmmoType_s *AmmoTypeForWeaponFire; // eax
  struct Netshop_Item_s *v6; // eax
  BOOL v7; // edi
  enum bool v8; // eax
  enum bool result; // eax
  enum bool isAmmoFullForGun; // [esp+10h] [ebp-4h] BYREF

  ClientFromNetworkID = NetManager_GetClientFromNetworkID((int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
  isAmmoFullForGun = -1;
  WeaponForAmmoSlot = Netshop_GetWeaponForAmmoSlot(nID, (int *)&isAmmoFullForGun);
  v3 = WeaponForAmmoSlot;
  result = false;
  if ( WeaponForAmmoSlot )
  {
    if ( ClientFromNetworkID )
    {
      v4 = isAmmoFullForGun;
      AmmoTypeForWeaponFire = WeaponType_GetAmmoTypeForWeaponFire(WeaponForAmmoSlot, isAmmoFullForGun);
      if ( AmmoTypeForWeaponFire )
      {
        v6 = Netshop_GetFromAmmoID(AmmoTypeForWeaponFire->eAmmoTypeID);
        if ( v6 )
        {
          v7 = ClientFromNetworkID->nUpdateItemTime >= v6->nCost;
          v8 = Netshop_IsAmmoFull(v3->eID, true, v4);
          if ( v7 )
          {
            if ( v8 == false )
              return true;
          }
        }
      }
    }
  }
  return result;
}

// source: j/0/network/netshop.c:1124  [size]
struct QTask_s *__cdecl Netshop_New(
        struct QTask_s *ptParentQTask,
        struct NetshopCreateContext_s *ptCreateContext)
{
  return QTask_NewFn(ptParentQTask, Netshop_eQTaskType, ptCreateContext);
}

// source: j/0/network/netshop.c:1154  [anchor-callee]
int __cdecl Netshop_Buy(int nItemID, int *ptAccount, int eTeam)
{
  unsigned __int16 v3; // dx
  struct QTask_s *ptNetManagerQTask; // edi
  struct QTask_s *FirstChildOfType; // eax
  int ptNext; // ecx
  int v7; // esi
  struct QTask_s **i; // eax
  struct QTask_s *v10; // eax
  int v11; // edx
  int v12; // ecx
  struct QTask_s **p_ptPrev; // eax
  struct QTask_s **v14; // esi
  char v15; // al
  enum bool isAllowSniperRifles; // eax
  int v17; // ecx

  v3 = Netshop_eQTaskType;
  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  FirstChildOfType = QTask_GetFirstChildOfType(ptNetManagerQTask, Netshop_eQTaskType);
  ptNext = (int)FirstChildOfType[1].ptNext;
  v7 = 0;
  if ( ptNext <= 0 )
    return 0;
  for ( i = &FirstChildOfType[1].ptPrev; *i != (struct QTask_s *)nItemID; i += 14 )
  {
    if ( ++v7 >= ptNext )
      return 0;
  }
  v10 = QTask_GetFirstChildOfType(ptNetManagerQTask, v3);
  v11 = (int)v10[1].ptNext;
  v12 = 0;
  if ( v11 <= 0 )
  {
LABEL_10:
    v14 = nullptr;
  }
  else
  {
    p_ptPrev = &v10[1].ptPrev;
    while ( *p_ptPrev != (struct QTask_s *)nItemID )
    {
      ++v12;
      p_ptPrev += 14;
      if ( v12 >= v11 )
        goto LABEL_10;
    }
    v14 = p_ptPrev;
  }
  if ( eTeam )
  {
    if ( eTeam == 1 )
    {
      v15 = *((_BYTE *)v14 + 53);
      goto LABEL_16;
    }
    return 0;
  }
  v15 = *((_BYTE *)v14 + 52);
LABEL_16:
  if ( !v15 )
    return 0;
  isAllowSniperRifles = ServerConfig_tServerConfig.isAllowSniperRifles;
  if ( ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
    isAllowSniperRifles = SLOBYTE(ptNetManagerQTask[6].ptPrev);
  if ( isAllowSniperRifles == false && Netshop_IsAvailable(nItemID) )
    return 0;
  v17 = (int)v14[9];
  if ( *ptAccount < v17 )
    return 0;
  *ptAccount -= v17;
  return 1;
}

// source: j/0/network/netshop.c:1243  [anchor-hash]
struct Netshop_Item_s *__cdecl Netshop_GetItem(int nItemID)
{
  struct QTask_s *FirstChildOfType; // eax
  int ptNext; // edx
  int v3; // ecx
  struct Netshop_Item_s *result; // eax

  FirstChildOfType = QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, Netshop_eQTaskType);
  ptNext = (int)FirstChildOfType[1].ptNext;
  v3 = 0;
  if ( ptNext <= 0 )
    return nullptr;
  for ( result = (struct Netshop_Item_s *)&FirstChildOfType[1].ptPrev; result->nItemID != nItemID; ++result )
  {
    if ( ++v3 >= ptNext )
      return nullptr;
  }
  return result;
}

// source: j/0/network/netshop.c:1273  [anchor-hash]
int __cdecl Netshop_NumberOfItems()
{
  return (int)QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, Netshop_eQTaskType)[1].ptNext;
}

// source: j/0/network/netshop.c:1292  [anchor-hash]
struct QTask_s *__cdecl Netshop_Add(int a1)
{
  struct QTask_s *result; // eax
  struct QTask_s *ptNext; // ecx
  struct QTask_s **v3; // edx
  char *v4; // ecx
  char v5; // bl

  result = QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, Netshop_eQTaskType);
  ptNext = result[1].ptNext;
  if ( (int)ptNext >= 120 )
  {
    LDebug_Error("Shop is full");
    abort();
  }
  v3 = &result[1].ptPrev + 14 * (_DWORD)ptNext;
  *((_DWORD *)&result[2].ptNext + 14 * (_DWORD)ptNext) = *(_DWORD *)(a1 + 36);
  v4 = (char *)(a1 + 4);
  do
  {
    v5 = *v4;
    v4[(_DWORD)v3 - a1] = *v4;
    ++v4;
  }
  while ( v5 );
  *((_BYTE *)v3 + 40) = *(_BYTE *)(a1 + 40);
  v3[11] = *(struct QTask_s **)(a1 + 44);
  v3[12] = *(struct QTask_s **)(a1 + 48);
  *v3 = *(struct QTask_s **)a1;
  *((_BYTE *)v3 + 52) = *(_BYTE *)(a1 + 52);
  *((_BYTE *)v3 + 53) = *(_BYTE *)(a1 + 53);
  ++*(int *)&result[1].ptNext;
  return result;
}

// source: j/0/network/netshop.c:1338  [anchor-mhash]
void __cdecl Netshop_HandleWeaponType(struct WeaponType_s *ptWeaponType, void *pxContext)
{
  int nCost; // edx
  int v3; // edx
  char isBadGuysBuyable; // cl
  struct Netshop_Item_s tNetshopItem; // [esp+4h] [ebp-38h] BYREF

  strncpy(tNetshopItem.zName, ptWeaponType->zName, 0x20u);
  nCost = ptWeaponType->nCost;
  tNetshopItem.ePickupID = ptWeaponType->eID;
  tNetshopItem.nCost = nCost;
  tNetshopItem.nItemID = *((_DWORD *)pxContext + 10);
  v3 = *((_DWORD *)pxContext + 1692);
  tNetshopItem.ePickupType = 0;
  tNetshopItem.nPickupAmount = 0;
  if ( v3 || ptWeaponType->eWeaponCategory != WEAPONCATEGORY_MEDIPACK )
  {
    isBadGuysBuyable = ptWeaponType->isBadGuysBuyable;
    tNetshopItem.isGoodBuyable = ptWeaponType->isGoodGuysBuyable;
    tNetshopItem.isBadBuyable = isBadGuysBuyable;
    Netshop_Add((int)&tNetshopItem);
  }
  else
  {
    tNetshopItem.isGoodBuyable = 0;
    tNetshopItem.isBadBuyable = 0;
    Netshop_Add((int)&tNetshopItem);
  }
}

// source: j/0/network/netshop.c:1383  [anchor-strings]
void __cdecl Netshop_FillSlots(struct Netshop_s *ptNetshop)
{
  int *p_ePickupID; // ebx
  struct WeaponType_s *WeaponTypeFromID; // eax
  int nShopCategory; // edi
  int nSlot; // ebp
  int v5; // esi
  struct SlotCategory_s *ptActiveCategory; // eax
  struct SlotSelector_s *v7; // eax
  struct SlotSelector_s *v8; // esi
  unsigned __int16 v9; // dx
  int v10; // ebp
  int i; // edi
  struct SlotCategory_s *v12; // eax
  struct QTask_s *FirstChildOfType; // eax
  struct SlotCategory_s *v14; // eax
  int v15; // [esp+10h] [ebp-4h]

  SlotSelector_ptActiveSelector = (struct SlotSelector_s *)QTask_GetFirstChildOfType(
                                                             &ptNetshop->tQTask,
                                                             SlotSelector_eQTaskType);
  SlotSelector_CreateCategory("SIDEARMS", 1);
  SlotSelector_CreateCategory("SMGs", 2);
  SlotSelector_CreateCategory("ASSAULT RIFLES", 3);
  SlotSelector_CreateCategory("SNIPER RIFLES", 4);
  SlotSelector_CreateCategory("SHOTGUNS", 5);
  SlotSelector_CreateCategory("HEAVY WEAPONS", 6);
  SlotSelector_CreateCategory("GRENADES", 7);
  SlotSelector_CreateCategory("OTHER", 8);
  v15 = 0;
  if ( ptNetshop->nNumberOfItems > 0 )
  {
    p_ePickupID = &ptNetshop->aItems[0].ePickupID;
    do
    {
      if ( !*((_BYTE *)p_ePickupID - 4) )
      {
        WeaponTypeFromID = WeaponType_GetWeaponTypeFromID(*p_ePickupID);
        if ( !WeaponTypeFromID )
        {
          LDebug_Error("Weapon not recognized");
          abort();
        }
        nShopCategory = WeaponTypeFromID->nShopCategory;
        nSlot = WeaponTypeFromID->nSlot;
        if ( nShopCategory >= 1 && nShopCategory <= 9 && nSlot >= 1 && nSlot <= 9 )
        {
          v5 = *(p_ePickupID - 11);
          SlotSelector_SetActiveCategory(nShopCategory);
          ptActiveCategory = SlotSelector_ptActiveSelector->ptActiveCategory;
          if ( ptActiveCategory )
            ptActiveCategory->aItems[nSlot].nItemID = v5;
        }
      }
      p_ePickupID += 14;
      ++v15;
    }
    while ( v15 < ptNetshop->nNumberOfItems );
  }
  v7 = SlotSelector_ptActiveSelector;
  SlotSelector_ptActiveSelector->pfItemClicked = Netshop_AmmoPicked;
  v7->pfItemEnabled = Netshop_isAmmoEnabled;
  v7->pfItemText = Netshop_AmmoText;
  SlotSelector_CreateCategory("AMMO", 9);
  v8 = SlotSelector_ptActiveSelector;
  v9 = SlotCategory_eQTaskType;
  v10 = 1;
  for ( i = 80; i <= 92; i += 4 )
  {
    v12 = v8->ptActiveCategory;
    if ( !v12 || v12->nCategory != 9 )
    {
      FirstChildOfType = QTask_GetFirstChildOfType(&v8->tQTask, v9);
      if ( FirstChildOfType )
      {
        while ( FirstChildOfType[1].ptNext != (struct QTask_s *)9 )
        {
          FirstChildOfType = QTask_GetNextSiblingOfType(FirstChildOfType, v9);
          if ( !FirstChildOfType )
            goto LABEL_21;
        }
        v8->ptActiveCategory = (struct SlotCategory_s *)FirstChildOfType;
      }
    }
LABEL_21:
    v14 = v8->ptActiveCategory;
    if ( v14 )
      *(struct QTask_s **)((char *)&v14->tQTask.ptNext + i) = (struct QTask_s *)v10;
    ++v10;
  }
  v8->ptActiveCategory = nullptr;
}

// source: j/0/network/netshop.c:1469  [anchor-mhash]
void __cdecl Netshop_HandleAmmoType(struct AmmoType_s *ptAmmoType, void *pxContext)
{
  int eAmmoTypeID; // ecx
  int nShopAmount; // edx
  int v4; // edx
  struct Netshop_Item_s tNetshopItem; // [esp+4h] [ebp-38h] BYREF

  strncpy(tNetshopItem.zName, ptAmmoType->zAmmoTypeScriptID, 0x20u);
  eAmmoTypeID = ptAmmoType->eAmmoTypeID;
  tNetshopItem.nCost = ptAmmoType->nCost;
  nShopAmount = ptAmmoType->nShopAmount;
  tNetshopItem.ePickupID = eAmmoTypeID;
  tNetshopItem.nPickupAmount = nShopAmount;
  v4 = *((_DWORD *)pxContext + 10);
  tNetshopItem.ePickupType = 1;
  tNetshopItem.nItemID = v4;
  tNetshopItem.isBadBuyable = 1;
  tNetshopItem.isGoodBuyable = 1;
  Netshop_Add((int)&tNetshopItem);
}

// source: j/0/network/netshop.c:1514  [anchor-mhash]
void __cdecl Netshop_FillShop(int ltcg_arg0)
{
  struct QTask_s *FirstChildOfType; // esi

  FirstChildOfType = QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, Netshop_eQTaskType);
  FirstChildOfType[169].tQTaskChildren.ptHead = (struct QTask_s *)(ltcg_arg0 == 0);
  WeaponType_EnumerateWeaponTypes(Netshop_HandleWeaponType, FirstChildOfType);
  AmmoType_EnumerateAmmoTypes(Netshop_HandleAmmoType, FirstChildOfType);
  Netshop_FillSlots((struct Netshop_s *)FirstChildOfType);
}

// source: j/0/network/netshop.c:1563  [anchor-mhash]
void __cdecl Netshop_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct SlotSelector_s *v2; // eax
  struct SlotCreateContext_s tSlotCreateContext; // [esp+4h] [ebp-Ch] BYREF

  tSlotCreateContext.pfItemClicked = Netshop_ItemPicked;
  tSlotCreateContext.pfItemEnabled = Netshop_isItemEnabled;
  tSlotCreateContext.pfItemText = Netshop_ItemText;
  v2 = (struct SlotSelector_s *)QTask_NewFn(ptQTask, SlotSelector_eQTaskType, &tSlotCreateContext);
  ptQTask[169].ptPrev = &v2->tQTask;
  ptQTask[169].tQTaskChildren.ptHead = (struct QTask_s *)1;
  SlotSelector_ptActiveSelector = v2;
}

// source: j/0/network/netshop.c:1596  [size]
void __cdecl Netshop_RunHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: j/0/network/netshop.c:1609  [anchor-hash]
void __cdecl Netshop_Close()
{
  QTask_DeleteQTaskType(Netshop_eQTaskType);
  Symbol_Remove("Netshop_SetInventoryText");
  Symbol_Remove("Netshop_Activate");
  Symbol_Remove("Netshop_isOpen");
  Symbol_Remove("Netshop_AddMoneyAll");
  Symbol_Remove("addmoney");
  Symbol_Remove("Netshop_AMMOSLOT_SIDEARM");
  Symbol_Remove("Netshop_AMMOSLOT_PRIMARY_I");
  Symbol_Remove("Netshop_AMMOSLOT_PRIMARY_II");
  Symbol_Remove("Netshop_AMMOSLOT_MEDIPACK");
}

// source: j/0/network/netshop.c:1634  [anchor-hash]
void __cdecl Netshop_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("Netshop", 6772, BaseQTaskType, 0, 0);
  Netshop_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 0, Netshop_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, (void (__cdecl *)(struct QTask_s *))Netshop_RunHandler);
  Symbol_Register(
    "Netshop_SetInventoryText",
    Netshop_InventoryCB,
    nullptr,
    2,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "Netshop_Activate",
    Netshop_ActivateCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "Netshop_isOpen",
    Netshop_isOpenToLocalCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "Netshop_AddMoneyAll",
    Netshop_AddMoneyAllCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "addmoney",
    Netshop_AddMoneyAllCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "accounts",
    Netshop_ListMoneyAllCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "Netshop_AMMOSLOT_SIDEARM",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)2,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "Netshop_AMMOSLOT_PRIMARY_I",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)1,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "Netshop_AMMOSLOT_PRIMARY_II",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)3,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "Netshop_AMMOSLOT_MEDIPACK",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)4,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}
