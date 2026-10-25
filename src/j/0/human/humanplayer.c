/* j/0/human/humanplayer.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/human/humanplayer.c:488  [size]
void __cdecl CDAPFN0506_X_HumanPlayer_InitStateActivateDoor()
{
  if ( !CDAPFN0506_HumanPlayer_InitStateActivateDoor.Version )
    CDAPFN0506_X_HumanPlayer_InitStateActivateDoor();
  if ( !CDAPFN0506_CDAPFN0506_X_HumanPlayer_InitStateActivateDoor.Version )
    ((void (*)(void))CDAPFN0506_CDAPFN0506_X_HumanPlayer_InitStateActivateDoor.FunctionAddress)();
}

// source: j/0/human/humanplayer.c:491  [size]
void __cdecl CDAPFN0506_X_HumanPlayer_InitStateActivateCabinet()
{
  if ( !CDAPFN0506_HumanPlayer_InitStateActivateCabinet.Version )
    CDAPFN0506_X_HumanPlayer_InitStateActivateCabinet();
  if ( !CDAPFN0506_CDAPFN0506_X_HumanPlayer_InitStateActivateCabinet.Version )
    ((void (*)(void))CDAPFN0506_CDAPFN0506_X_HumanPlayer_InitStateActivateCabinet.FunctionAddress)();
}

// source: j/0/human/humanplayer.c:494  [size]
void __cdecl CDAPFN0506_X_HumanPlayer_InitStateActivateTerminal()
{
  if ( !CDAPFN0506_HumanPlayer_InitStateActivateTerminal.Version )
    CDAPFN0506_X_HumanPlayer_InitStateActivateTerminal();
  if ( !CDAPFN0506_CDAPFN0506_X_HumanPlayer_InitStateActivateTerminal.Version )
    ((void (*)(void))CDAPFN0506_CDAPFN0506_X_HumanPlayer_InitStateActivateTerminal.FunctionAddress)();
}

// source: j/0/human/humanplayer.c:497  [size]
void __cdecl CDAPFN0506_X_HumanPlayer_InitStateActivateStationaryGun()
{
  if ( !CDAPFN0506_HumanPlayer_InitStateActivateStationaryGun.Version )
    CDAPFN0506_X_HumanPlayer_InitStateActivateStationaryGun();
  if ( !CDAPFN0506_CDAPFN0506_X_HumanPlayer_InitStateActivateStationaryGun.Version )
    ((void (*)(void))CDAPFN0506_CDAPFN0506_X_HumanPlayer_InitStateActivateStationaryGun.FunctionAddress)();
}

// source: j/0/human/humanplayer.c:500  [size]
void __cdecl CDAPFN0506_X_HumanPlayer_InitStateActivateGenericTBA()
{
  if ( !CDAPFN0506_HumanPlayer_InitStateActivateGenericTBA.Version )
    CDAPFN0506_X_HumanPlayer_InitStateActivateGenericTBA();
  if ( !CDAPFN0506_CDAPFN0506_X_HumanPlayer_InitStateActivateGenericTBA.Version )
    ((void (*)(void))CDAPFN0506_CDAPFN0506_X_HumanPlayer_InitStateActivateGenericTBA.FunctionAddress)();
}

// source: j/0/human/humanplayer.c:503  [size]
void __cdecl CDAPFN0506_X_HumanPlayer_InitStateActivateC4BombTBA()
{
  if ( !CDAPFN0506_HumanPlayer_InitStateActivateC4BombTBA.Version )
    CDAPFN0506_X_HumanPlayer_InitStateActivateC4BombTBA();
  if ( !CDAPFN0506_CDAPFN0506_X_HumanPlayer_InitStateActivateC4BombTBA.Version )
    ((void (*)(void))CDAPFN0506_CDAPFN0506_X_HumanPlayer_InitStateActivateC4BombTBA.FunctionAddress)();
}

// source: j/0/human/humanplayer.c:506  [size]
void __cdecl CDAPFN0506_X_HumanPlayer_InitStateActivatePlaceExplosiveTBA()
{
  if ( !CDAPFN0506_HumanPlayer_InitStateActivatePlaceExplosiveTBA.Version )
    CDAPFN0506_X_HumanPlayer_InitStateActivatePlaceExplosiveTBA();
  if ( !CDAPFN0506_CDAPFN0506_X_HumanPlayer_InitStateActivatePlaceExplosiveTBA.Version )
    ((void (*)(void))CDAPFN0506_CDAPFN0506_X_HumanPlayer_InitStateActivatePlaceExplosiveTBA.FunctionAddress)();
}

// source: j/0/human/humanplayer.c:509  [size]
void __cdecl CDAPFN0506_X_HumanPlayer_InitStateSilentKill()
{
  if ( !CDAPFN0506_HumanPlayer_InitStateSilentKill.Version )
    CDAPFN0506_X_HumanPlayer_InitStateSilentKill();
  if ( !CDAPFN0506_CDAPFN0506_X_HumanPlayer_InitStateSilentKill.Version )
    ((void (*)(void))CDAPFN0506_CDAPFN0506_X_HumanPlayer_InitStateSilentKill.FunctionAddress)();
}

// source: j/0/human/humanplayer.c:1330  [anchor-caller]
int __cdecl HumanPlayer_GetAnimStateFromAnimName(struct QTask_s *ptQTask, char *zAnimName)
{
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptPrev; // eax
  struct WeaponType_s *ptTail; // esi
  struct QTask_s *WeaponTypeAnimPtr; // eax
  unsigned __int8 *v6; // edx
  enum WeaponTypeAnim_e WeaponTypeAnimFromName; // ecx
  int result; // eax
  char *ptQTaska; // [esp+8h] [ebp+4h]

  ptNext = ptQTask[33].ptNext;
  if ( !ptNext )
    return 2;
  ptPrev = ptNext[1].ptPrev;
  if ( !ptPrev )
    return 2;
  ptTail = (struct WeaponType_s *)ptPrev->tQTaskChildren.ptTail;
  if ( !ptTail )
    return 2;
  WeaponTypeAnimPtr = Human_GetWeaponTypeAnimPtr(ptQTask);
  if ( !WeaponTypeAnimPtr )
    return 2;
  v6 = *(unsigned __int8 **)&WeaponTypeAnimPtr[24].eQTaskType;
  if ( !v6 )
    return 2;
  WeaponTypeAnimFromName = WeaponType_GetWeaponTypeAnimFromName(ptTail, v6, ptQTaska);
  result = 0;
  while ( HumanPlayer_atStateAnimData[result].iWeaponTypeAnim != WeaponTypeAnimFromName )
  {
    if ( ++result >= 109 )
      return 2;
  }
  return result;
}

// source: j/0/human/humanplayer.c:1385  [anchor-mhash]
void __cdecl HumanPlayer_AreaActivateCB(struct AreaActivateContext_s *ptContext)
{
  enum GameMode_e v1; // ebx
  struct Flow_t *v2; // ebp
  struct QTask_s *ptAreaActivateQTask; // edx
  _WORD *pxObject; // edi
  struct Client_s *ClientFromHumanQTask; // eax
  int nHitCount; // eax
  struct real64x3_t ptPos; // [esp+10h] [ebp-18h] BYREF
  struct QTask_s *ptContexta = *(struct QTask_s * *)&ptContext; // [esp+2Ch] [ebp+4h] ARGSLOT

  v1 = Game_eGameMode;
  v2 = Flow_ptFlow;
  ptAreaActivateQTask = ptContext->ptAreaActivateQTask;
  ptContexta = ptContext->ptAreaActivateQTask[4].tQTaskChildren.ptTail;
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER && Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    HIBYTE(ptAreaActivateQTask[4].tQTaskRefList.ptTail) = 1;
    return;
  }
  if ( !Level_atLevelQTaskID[0]
    || (pxObject = Level_atLevelQTaskID[0]->pxObject) == nullptr
    || QTask_IsQTaskTypeDerived(pxObject[18], HumanPlayer_eQTaskType) == false
    || (sub_580CA0((int)pxObject, &ptPos.vX), !AreaActivateQTask_IsInsideArea(ptAreaActivateQTask, &ptPos)) )
  {
LABEL_14:
    if ( v1 != GAME_GAMEMODE_MULTIPLAYER )
      return;
    goto LABEL_15;
  }
  if ( v1 != GAME_GAMEMODE_MULTIPLAYER )
  {
LABEL_13:
    ++ptContext->nHitCount;
    goto LABEL_14;
  }
  if ( !v2->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    ClientFromHumanQTask = NetManager_GetClientFromHumanQTask(HumanPlayer_ptQTask);
    if ( ClientFromHumanQTask )
      ptContext->nClientID = ClientFromHumanQTask->eNetworkID;
    v1 = Game_eGameMode;
    v2 = Flow_ptFlow;
    goto LABEL_13;
  }
LABEL_15:
  if ( !v2->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    nHitCount = ptContext->nHitCount;
    if ( (struct QTask_s *)nHitCount != ptContexta )
      Server_SendAreaActivateMessage(ptContext->ptAreaActivateQTask, nHitCount, ptContext->nClientID);
  }
}

// source: j/0/human/humanplayer.c:1508  [anchor-refs]
struct WeaponType_s *__cdecl HumanPlayer_GetPrimaryWeaponType()
{
  void *pxObject; // edx
  struct WeaponType_s *result; // eax
  int v2; // eax

  if ( !Level_atLevelQTaskID[0]
    || (pxObject = Level_atLevelQTaskID[0]->pxObject) == nullptr
    || QTask_IsQTaskTypeDerived(*((_WORD *)pxObject + 18), Human_eQTaskType) == false
    || (result = Weapon_GetNextEnabledWeaponTypeFromCategory(
                   *((struct QTask_s **)pxObject + 330),
                   WEAPONCATEGORY_PRIMARY,
                   nullptr)) == nullptr )
  {
    v2 = Script_ParseLineInt32("WEAPON_ID_KNIFE");
    return WeaponType_GetWeaponTypeFromID(v2);
  }
  return result;
}

// source: j/0/human/humanplayer.c:1542  [size]
struct Result_s *__cdecl HumanPlayer_GetPrimaryWeaponModel(
        struct Result_s *retstr,
        void *pxUnused,
        struct ArgList_s *ptArgList)
{
  struct WeaponType_s *PrimaryWeaponType; // eax
  struct Result_s *result; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  PrimaryWeaponType = HumanPlayer_GetPrimaryWeaponType();
  Rs.vResult = 0.0;
  Rs.nResult = 0;
  if ( PrimaryWeaponType )
  {
    Rs.zResult = PrimaryWeaponType->zFixedModel;
    result = retstr;
  }
  else
  {
    result = retstr;
    Rs.zResult = (char *)&g_zInitialValue;
  }
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return result;
}

// source: j/0/human/humanplayer.c:1566  [size]
struct Result_s *__cdecl HumanPlayer_GetPrimaryWeaponID(
        struct Result_s *retstr,
        void *pxUnused,
        struct ArgList_s *ptArgList)
{
  struct WeaponType_s *PrimaryWeaponType; // eax
  struct Result_s *result; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  PrimaryWeaponType = HumanPlayer_GetPrimaryWeaponType();
  Rs.vResult = 0.0;
  Rs.nResult = 0;
  if ( PrimaryWeaponType )
  {
    Rs.zResult = PrimaryWeaponType->zWeaponScriptID;
    result = retstr;
  }
  else
  {
    result = retstr;
    Rs.zResult = (char *)&g_zInitialValue;
  }
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return result;
}

// source: j/0/human/humanplayer.c:1587  [anchor-callee]
enum bool __cdecl HumanPlayer_IsActivateComputer(struct QTask_s *ptQTask)
{
  double v1; // st7

  if ( Game_eGameMode )
  {
    if ( *(float *)&ptQTask[22].tQTaskRefList.ptMiddle != 0.0 && *(float *)&ptQTask[16].tQTaskChildren.ptMiddle == 0.0
      || *(float *)&ptQTask[23].tQTaskRefList.ptHead != 0.0 && *(float *)&ptQTask[17].tQTaskChildren.ptHead == 0.0 )
    {
      return true;
    }
    if ( *(float *)&ptQTask[23].tQTaskRefList.ptMiddle == 0.0 )
      return false;
    v1 = *(float *)&ptQTask[17].tQTaskChildren.ptMiddle;
    goto LABEL_16;
  }
  if ( *(float *)&ptQTask[22].tQTaskRefList.ptMiddle != 0.0 && *(float *)&ptQTask[16].tQTaskChildren.ptMiddle == 0.0
    || *(float *)&ptQTask[23].tQTaskRefList.ptHead != 0.0 && *(float *)&ptQTask[17].tQTaskChildren.ptHead == 0.0
    || *(float *)&ptQTask[23].tQTaskRefList.ptMiddle != 0.0 && *(float *)&ptQTask[17].tQTaskChildren.ptMiddle == 0.0 )
  {
    return true;
  }
  if ( *(float *)&ptQTask[23].tQTaskRefList.ptTail != 0.0 )
  {
    v1 = *(float *)&ptQTask[17].tQTaskChildren.ptTail;
LABEL_16:
    if ( v1 == 0.0 )
      return true;
  }
  return false;
}

// source: j/0/human/humanplayer.c:1623  [anchor-callee]
void __cdecl HumanPlayer_SendActivateMessage(
        struct QTask_s *ptActivateQTask,
        int eHumanActivate,
        int nActivateInfo)
{
  struct QTask_s *ptNetManagerQTask; // esi
  DWORD PerformanceCounter; // eax
  int v5; // eax
  struct QReference_s *v6; // ecx
  struct ClientGameMessageActivate_s tActivateMessage; // [esp+8h] [ebp-18h] BYREF

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  tActivateMessage.tBaseMessage.eGameMessage = 1094931529;
  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  tActivateMessage.tBaseMessage.nLocalTime = PerformanceCounter
                                           - Timer_nStartTime
                                           + (char *)ptNetManagerQTask[6].tQTaskRefList.ptMiddle
                                           - (char *)ptNetManagerQTask[6].tQTaskRefList.ptTail;
  tActivateMessage.eActivate = eHumanActivate;
  v5 = 0;
  while ( 1 )
  {
    v6 = Level_atLevelQTaskID[v5];
    if ( v6 )
    {
      if ( v6->pxObject == ptActivateQTask )
        break;
    }
    if ( ++v5 >= 4096 )
    {
      v5 = -1;
      break;
    }
  }
  tActivateMessage.nTaskID = v5;
  tActivateMessage.nWhoDidItClientID = (int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle;
  tActivateMessage.nActivateInfo = nActivateInfo;
  NetManager_SendGameMessage(
    0,
    tActivateMessage.nWhoDidItClientID,
    NETWORKQUEUE_GUARANTEED,
    &tActivateMessage.tBaseMessage,
    0x18u);
}

// source: j/0/human/humanplayer.c:1650  [anchor-callee]
void __cdecl HumanPlayer_ActivateComputer(struct QTask_s *ptQTask)
{
  double v1; // st7
  struct QTask_s *ptTail; // eax
  void (__cdecl *v3)(struct QReference_s **, struct QTask_s *); // eax
  struct QReference_s *v4; // eax
  struct QTask_s *pxObject; // eax

  if ( *(float *)&ptQTask[23].tQTaskRefList.ptTail == 0.0 || Game_eGameMode )
  {
    if ( *(float *)&ptQTask[23].tQTaskRefList.ptMiddle == 0.0 )
    {
      v1 = *(float *)&ptQTask[23].tQTaskRefList.ptHead;
      Computer_eStartupMode = 3;
      if ( v1 == 0.0 )
        Computer_eStartupMode = 1;
    }
    else
    {
      Computer_eStartupMode = 2;
    }
  }
  else
  {
    Computer_eStartupMode = 4;
  }
  ptTail = ptQTask[33].tQTaskChildren.ptTail;
  ptTail[16].tQTaskRefList.ptMiddle = nullptr;
  *(float *)&ptTail[16].tQTaskChildren.ptHead = tan(0.7853981852531433);
  *(float *)&ptTail[16].tQTaskRefList.ptHead = tan(0.5235987901687622);
  v3 = *((void (__cdecl **)(struct QReference_s **, struct QTask_s *))&ptQTask[74].ptParent->ptNext
       + (int)ptQTask[75].ptPrev);
  if ( v3 )
    v3(&ptQTask[74].tQTaskRefList.ptMiddle, ptQTask);
  v4 = ptQTask[74].tQTaskRefList.ptTail;
  ptQTask[75].ptNext = ptQTask[75].ptPrev;
  ptQTask[75].ptPrev = (struct QTask_s *)8;
  pxObject = (struct QTask_s *)v4[2].pxObject;
  ptQTask[75].tQTaskChildren.ptHead = pxObject;
  ((void (__cdecl *)(struct QReference_s **, struct QTask_s *))pxObject)(&ptQTask[74].tQTaskRefList.ptMiddle, ptQTask);
}

// source: j/0/human/humanplayer.c:1699  [size]
void __cdecl HumanPlayer_DeleteSoundTasks(struct QTask_s *ptQTask)
{
  QTask_DeleteQTaskAndQTaskRefSafe(&ptQTask[85].tQTaskRefList.ptMiddle);
  QTask_DeleteQTaskAndQTaskRefSafe(&ptQTask[85].tQTaskRefList.ptHead);
}

// source: j/0/human/humanplayer.c:1716  [size]
void __cdecl HumanPlayer_GetSerializeParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = HumanPlayer_ptSerializeParameterList;
}

// source: j/0/human/humanplayer.c:1737  [anchor-mhash]
void __cdecl HumanPlayer_DeSerializeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v2; // ecx
  struct QReference_s *ptHead; // eax
  struct QTask_s *pxObject; // edx
  struct QReference_s *v5; // eax
  int v6; // eax
  struct QTask_s *ptTail; // eax
  struct GameTexture_s *v8; // ecx
  struct QTask_s *ptNext; // edx
  struct QTask_s *v10; // eax
  struct QTask_s *v11; // eax
  struct QTask_s *ptPrev; // eax
  struct WeaponType_s *PrimaryWeaponType; // eax
  enum WeaponCategory_e eWeaponCategory; // ecx
  struct QTask_s *v15; // eax
  struct QTask_s *v16; // edx
  struct QTask_s *v17; // eax
  int v18; // ecx
  struct QTask_s *v19; // eax
  void (__cdecl *v20)(struct QReference_s **, struct QTask_s *); // eax
  struct QReference_s *v21; // ecx
  struct QTask_s *v22; // eax
  void (__cdecl *v23)(struct QReference_s **, struct QTask_s *); // eax
  struct QReference_s *v24; // eax
  struct QTask_s *v25; // eax
  void (__cdecl *v26)(struct QReference_s **, struct QTask_s *); // eax
  struct QReference_s *v27; // ecx
  struct QTask_s *v28; // eax
  void (__cdecl *v29)(struct QReference_s **, struct QTask_s *); // eax
  struct QReference_s *v30; // edx
  struct QTask_s *v31; // eax
  enum WeaponOverlayStatus_e v32; // [esp+0h] [ebp-10h]

  ptHead = ptQTask[46].tQTaskRefList.ptHead;
  if ( ptHead )
  {
    pxObject = (struct QTask_s *)ptHead->pxObject;
    if ( pxObject )
    {
      v2 = *(struct QTask_s **)&StationaryGun_eQTaskType;
      if ( QTask_IsQTaskTypeDerived(pxObject->eQTaskType, StationaryGun_eQTaskType) )
      {
        pxObject[14].tQTaskRefList.ptHead = (struct QReference_s *)ptQTask;
        StationaryGun_Deactivate(pxObject);
      }
    }
  }
  Weapon_SetOverlayStatus(v2, v32, 0, (int)ptQTask[33].ptNext);
  v5 = ptQTask[46].tQTaskRefList.ptHead;
  ptQTask[86].tQTaskRefList.ptHead = nullptr;
  if ( v5 )
  {
    QReference_Delete(v5, &QTask_tQTaskRefPool);
    ptQTask[46].tQTaskRefList.ptHead = nullptr;
  }
  v6 = Human_eQTaskType + 511 * Serialize_eDeSerializeQTaskEvent;
  ptQTask[44].tQTaskRefList.ptTail = nullptr;
  ptQTask[48].ptNext = nullptr;
  *(_DWORD *)&ptQTask[47].eQTaskType = 1;
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][v6].pfHandler)(ptQTask, pxContext);
  ptTail = ptQTask[33].tQTaskChildren.ptTail;
  v8 = Human_ptShadow;
  HIBYTE(ptQTask[80].tQTaskRefList.ptMiddle) = 0;
  LOBYTE(ptTail[12].tQTaskRefList.ptTail) = 0;
  ptNext = ptQTask[47].ptNext;
  LOBYTE(ptQTask[34].tQTaskChildren.ptMiddle) = 0;
  ptQTask[86].tQTaskChildren.ptHead = nullptr;
  ptQTask[86].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[86].tQTaskChildren.ptTail = nullptr;
  ptQTask[37].ptParent = nullptr;
  *(_DWORD *)&ptQTask[37].eQTaskType = 0;
  ptQTask[38].ptNext = nullptr;
  ptQTask[39].ptNext = nullptr;
  ptQTask[39].ptPrev = nullptr;
  ptQTask[39].tQTaskChildren.ptHead = nullptr;
  HIBYTE(ptQTask[50].ptNext) = 0;
  ptNext[3].tQTaskChildren.ptMiddle = (struct QTask_s *)&v8->tTexInfo;
  BoneDynCubeObj_DeInitBloodStains((struct BoneDynCubeObj_s *)ptQTask);
  BoneDynCubeObj_InitBloodStains((struct BoneDynCubeObj_s *)ptQTask);
  v10 = ptQTask[33].ptNext;
  if ( v10[1].tQTaskChildren.ptTail )
  {
    v10[2].ptParent = (struct QTask_s *)1;
    v10[1].tQTaskChildren.ptTail = nullptr;
    v11 = ptQTask[33].ptNext;
    v11[3].tQTaskRefList.ptHead = (struct QReference_s *)1;
    v11[1].tQTaskChildren.ptTail = nullptr;
  }
  Weapon_StopAllSound(ptQTask[33].ptNext);
  QTask_DeleteQTaskAndQTaskRefSafe(&ptQTask[85].tQTaskRefList.ptMiddle);
  QTask_DeleteQTaskAndQTaskRefSafe(&ptQTask[85].tQTaskRefList.ptHead);
  ptPrev = ptQTask[33].ptNext[1].ptPrev;
  if ( ptPrev )
  {
    PrimaryWeaponType = (struct WeaponType_s *)ptPrev->tQTaskChildren.ptTail;
    if ( PrimaryWeaponType )
    {
      eWeaponCategory = PrimaryWeaponType->eWeaponCategory;
      if ( eWeaponCategory == WEAPONCATEGORY_BINOCULARS || eWeaponCategory == WEAPONCATEGORY_THERMOCHEMICAL )
        PrimaryWeaponType = HumanPlayer_GetPrimaryWeaponType();
      Weapon_Activate(ptQTask[33].ptNext, PrimaryWeaponType->zWeaponScriptID, false);
      ptQTask[77].tQTaskRefList.ptTail = nullptr;
    }
  }
  v15 = ptQTask[33].ptNext[5].ptNext;
  if ( v15 && v15->tQTaskChildren.ptHead )
  {
    v16 = v15->tQTaskChildren.ptHead;
    v17 = v16 + 6;
    v18 = 15;
    do
    {
      v17->ptNext = nullptr;
      v17 = (struct QTask_s *)((char *)v17 + 72);
      --v18;
    }
    while ( v18 );
    v16[4].ptPrev = nullptr;
  }
  v19 = ActionMenuScreen_ptQTask;
  ptQTask[50].tQTaskChildren.ptHead = nullptr;
  ptQTask[50].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[50].tQTaskChildren.ptTail = nullptr;
  BYTE2(ptQTask[50].ptNext) = 0;
  ActionMenuScreen_ClearHistory(v19);
  v20 = *((void (__cdecl **)(struct QReference_s **, struct QTask_s *))&ptQTask[74].ptParent->ptNext
        + (int)ptQTask[75].ptPrev);
  if ( v20 )
    v20(&ptQTask[74].tQTaskRefList.ptMiddle, ptQTask);
  v21 = ptQTask[74].tQTaskRefList.ptTail;
  ptQTask[75].ptNext = ptQTask[75].ptPrev;
  ptQTask[75].ptPrev = (struct QTask_s *)1;
  v22 = (struct QTask_s *)v21->ptPrev;
  ptQTask[75].tQTaskChildren.ptHead = v22;
  ((void (__cdecl *)(struct QReference_s **, struct QTask_s *))v22)(&ptQTask[74].tQTaskRefList.ptMiddle, ptQTask);
  if ( *(_DWORD *)&ptQTask[32].eQTaskType == 1 )
  {
    v29 = *((void (__cdecl **)(struct QReference_s **, struct QTask_s *))&ptQTask[30].ptParent->ptNext
          + (int)ptQTask[31].ptPrev);
    if ( v29 )
      v29(&ptQTask[30].tQTaskRefList.ptMiddle, ptQTask);
    v30 = ptQTask[30].tQTaskRefList.ptTail;
    ptQTask[31].ptNext = ptQTask[31].ptPrev;
    ptQTask[31].ptPrev = (struct QTask_s *)23;
    v31 = (struct QTask_s *)v30[7].pxObject;
    ptQTask[31].tQTaskChildren.ptHead = v31;
    ((void (__cdecl *)(struct QReference_s **, struct QTask_s *))v31)(&ptQTask[30].tQTaskRefList.ptMiddle, ptQTask);
  }
  else if ( *(_DWORD *)&ptQTask[32].eQTaskType == 2 )
  {
    v26 = *((void (__cdecl **)(struct QReference_s **, struct QTask_s *))&ptQTask[30].ptParent->ptNext
          + (int)ptQTask[31].ptPrev);
    if ( v26 )
      v26(&ptQTask[30].tQTaskRefList.ptMiddle, ptQTask);
    v27 = ptQTask[30].tQTaskRefList.ptTail;
    ptQTask[31].ptNext = ptQTask[31].ptPrev;
    ptQTask[31].ptPrev = (struct QTask_s *)75;
    v28 = (struct QTask_s *)v27[25].ptNext;
    ptQTask[31].tQTaskChildren.ptHead = v28;
    ((void (__cdecl *)(struct QReference_s **, struct QTask_s *))v28)(&ptQTask[30].tQTaskRefList.ptMiddle, ptQTask);
  }
  else
  {
    v23 = *((void (__cdecl **)(struct QReference_s **, struct QTask_s *))&ptQTask[30].ptParent->ptNext
          + (int)ptQTask[31].ptPrev);
    if ( v23 )
      v23(&ptQTask[30].tQTaskRefList.ptMiddle, ptQTask);
    v24 = ptQTask[30].tQTaskRefList.ptTail;
    ptQTask[31].ptNext = ptQTask[31].ptPrev;
    ptQTask[31].ptPrev = nullptr;
    v25 = (struct QTask_s *)v24->ptNext;
    ptQTask[31].tQTaskChildren.ptHead = v25;
    ((void (__cdecl *)(struct QReference_s **, struct QTask_s *))v25)(&ptQTask[30].tQTaskRefList.ptMiddle, ptQTask);
  }
}

// source: j/0/human/humanplayer.c:1831  [anchor-mhash]
void __cdecl HumanPlayer_SerializeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  Serialize_SerializeChild(ptQTask, ptQTask[33].ptNext, pxContext);
  Serialize_SerializeChild(ptQTask, ptQTask[33].tQTaskChildren.ptTail, pxContext);
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[Serialize_eSerializeQTaskEvent][Human_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
}

// source: j/0/human/humanplayer.c:1852  [anchor-mhash]
struct Result_s *__cdecl HumanPlayer_DefineWeaponCycleCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  int v3; // esi
  struct ArgList_s *v4; // edi
  struct ArgList_s *v5; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = 0;
  v4 = ptArgList;
  for ( HumanPlayer_tWeaponCycle.nID = 0; v3 < v4->nArguments; ++HumanPlayer_tWeaponCycle.nID )
  {
    if ( v4->isQVM )
    {
      ptArgList = nullptr;
      QVM_EvalArg(&ptArgList, 4, v4, v3, 1);
      v5 = ptArgList;
    }
    else
    {
      v5 = (struct ArgList_s *)Expression_EvalInt(v4->aptExpression[v3]);
    }
    HumanPlayer_tWeaponCycle.anID[HumanPlayer_tWeaponCycle.nID] = (int)v5;
    ++v3;
  }
  Rs.nResult = 1;
  Rs.vResult = 1.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/human/humanplayer.c:1884  [anchor-strings]
struct Result_s *__cdecl HumanPlayer_DisableAllWeapons(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  void *pxObject; // ebx
  struct Result_s Rs; // [esp+10h] [ebp-18h] BYREF

  if ( Level_atLevelQTaskID[0] )
  {
    pxObject = Level_atLevelQTaskID[0]->pxObject;
    if ( pxObject )
    {
      if ( QTask_IsQTaskTypeDerived(*((_WORD *)pxObject + 18), HumanPlayer_eQTaskType) )
      {
        Weapon_DisableAllWeaponTypes(*((struct QTask_s **)pxObject + 330));
        Weapon_EnableWeaponType(*((struct QTask_s **)pxObject + 330), "WEAPON_ID_KNIFE", false);
        Weapon_Activate(*((struct QTask_s **)pxObject + 330), "WEAPON_ID_KNIFE", false);
        *((_DWORD *)pxObject + 777) = 0;
      }
    }
  }
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/human/humanplayer.c:1914  [anchor-mhash]
struct Result_s *__cdecl HumanPlayer_EnableWeapon(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  void *pxObject; // esi
  char zWeaponID[32]; // [esp+8h] [ebp-20h] BYREF

  if ( Level_atLevelQTaskID[0] )
  {
    pxObject = Level_atLevelQTaskID[0]->pxObject;
    if ( pxObject )
    {
      if ( QTask_IsQTaskTypeDerived(*((_WORD *)pxObject + 18), HumanPlayer_eQTaskType) && ptArgList->nArguments > 0 )
      {
        if ( ptArgList->isQVM )
        {
          zWeaponID[0] = 0;
          QVM_EvalArg(zWeaponID, 32, ptArgList, 0, 3);
        }
        else
        {
          Expression_EvalString(*ptArgList->aptExpression, zWeaponID, 32);
        }
        Weapon_EnableWeaponType(*((struct QTask_s **)pxObject + 330), zWeaponID, true);
      }
    }
  }
  *(_DWORD *)zWeaponID = 0;
  *(_DWORD *)&zWeaponID[8] = 0;
  *(_DWORD *)&zWeaponID[12] = 0;
  *(_DWORD *)&zWeaponID[16] = &g_zInitialValue;
  qmemcpy(retstr, zWeaponID, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/human/humanplayer.c:1942  [anchor-mhash]
struct Result_s *__cdecl HumanPlayer_DefineAmmoLimitCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v10; };
    struct { char igi2_o1[4]; struct Result_s Rs; };
    char igi2_extent[28];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct ArgList_s *v3; // edi
  int i; // esi
  struct ArgList_s **v5; // ebx
  struct ArgList_s *v6; // eax
  int v7; // esi
  int v8; // eax

  v3 = ptArgList;
  HumanPlayer_tAmmoLimit.nAmmoLimit = 0;
  for ( i = 0; i < v3->nArguments; ++HumanPlayer_tAmmoLimit.nAmmoLimit )
  {
    v5 = (struct ArgList_s **)(8 * HumanPlayer_tAmmoLimit.nAmmoLimit + 7676524);
    if ( v3->isQVM )
    {
      ptArgList = nullptr;
      QVM_EvalArg(&ptArgList, 4, v3, i, 1);
      v6 = ptArgList;
    }
    else
    {
      v6 = (struct ArgList_s *)Expression_EvalInt(v3->aptExpression[i]);
    }
    *v5 = v6;
    v7 = i + 1;
    if ( v3->isQVM )
    {
      igi2_frame.v10 = 0;
      QVM_EvalArg(&igi2_frame.v10, 4, v3, v7, 1);
      v8 = igi2_frame.v10;
    }
    else
    {
      v8 = Expression_EvalInt(v3->aptExpression[v7]);
    }
    v5[1] = (struct ArgList_s *)v8;
    i = v7 + 1;
  }
  igi2_frame.Rs.nResult = 1;
  igi2_frame.Rs.vResult = 1.0;
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/human/humanplayer.c:1979  [anchor-hash]
void __cdecl HumanPlayer_InitStateTable()
{
  memset(HumanPlayer_apfExitState, 0, sizeof(HumanPlayer_apfExitState));
  HumanPlayer_apfState[19] = HumanPlayer_InitStateSwim;
  HumanPlayer_apfState[20] = HumanPlayer_InitStateSwim;
  HumanPlayer_apfState[21] = HumanPlayer_InitStateSwim;
  HumanPlayer_apfState[0] = HumanPlayer_InitStateStand;
  HumanPlayer_apfState[1] = HumanPlayer_InitStateStandTurn;
  HumanPlayer_apfState[2] = nullptr;
  HumanPlayer_apfState[3] = HumanPlayer_InitStateRunForward;
  HumanPlayer_apfState[4] = HumanPlayer_InitStateRunForwardRight;
  HumanPlayer_apfState[5] = HumanPlayer_InitStateRunForwardLeft;
  HumanPlayer_apfState[6] = HumanPlayer_InitStateRunBackward;
  HumanPlayer_apfState[7] = HumanPlayer_InitStateRunBackwardRight;
  HumanPlayer_apfState[8] = HumanPlayer_InitStateRunBackwardLeft;
  HumanPlayer_apfState[9] = HumanPlayer_InitStateRunRight;
  HumanPlayer_apfState[10] = HumanPlayer_InitStateRunLeft;
  HumanPlayer_apfState[11] = HumanPlayer_InitStateWalkForward;
  HumanPlayer_apfState[12] = HumanPlayer_InitStateWalkForwardRight;
  HumanPlayer_apfState[13] = HumanPlayer_InitStateWalkForwardLeft;
  HumanPlayer_apfState[14] = HumanPlayer_InitStateWalkBackward;
  HumanPlayer_apfState[15] = HumanPlayer_InitStateWalkBackwardRight;
  HumanPlayer_apfState[16] = HumanPlayer_InitStateWalkBackwardLeft;
  HumanPlayer_apfState[17] = HumanPlayer_InitStateWalkRight;
  HumanPlayer_apfState[18] = HumanPlayer_InitStateWalkLeft;
  HumanPlayer_apfState[22] = HumanPlayer_InitStateDie;
  HumanPlayer_apfState[23] = HumanPlayer_InitStateCrouch;
  HumanPlayer_apfState[24] = HumanPlayer_InitStateCrouchTurn;
  HumanPlayer_apfState[25] = nullptr;
  HumanPlayer_apfState[26] = HumanPlayer_InitStateCrouchWalkForward;
  HumanPlayer_apfState[27] = HumanPlayer_InitStateCrouchWalkForwardRight;
  HumanPlayer_apfState[28] = HumanPlayer_InitStateCrouchWalkForwardLeft;
  HumanPlayer_apfState[29] = HumanPlayer_InitStateCrouchWalkBackward;
  HumanPlayer_apfState[30] = HumanPlayer_InitStateCrouchWalkBackwardRight;
  HumanPlayer_apfState[31] = HumanPlayer_InitStateCrouchWalkBackwardLeft;
  HumanPlayer_apfState[32] = HumanPlayer_InitStateCrouchWalkRight;
  HumanPlayer_apfState[33] = HumanPlayer_InitStateCrouchWalkLeft;
  HumanPlayer_apfState[34] = nullptr;
  HumanPlayer_apfState[35] = nullptr;
  HumanPlayer_apfState[36] = HumanPlayer_InitStateJump;
  HumanPlayer_apfExitState[36] = (void (__cdecl *)(struct State_s *, struct QTask_s *))sub_4B6130;
  HumanPlayer_apfState[37] = HumanPlayer_InitStateFall;
  HumanPlayer_apfState[38] = HumanPlayer_InitStateActivateDoor;
  HumanPlayer_apfState[39] = HumanPlayer_InitStateActivateCabinet;
  HumanPlayer_apfState[40] = HumanPlayer_InitStateActivateTerminal;
  HumanPlayer_apfState[41] = HumanPlayer_InitStateActivateStationaryGun;
  HumanPlayer_apfState[42] = HumanPlayer_InitStateActivateGenericTBA;
  HumanPlayer_apfState[43] = HumanPlayer_InitStateActivateC4BombTBA;
  HumanPlayer_apfState[44] = HumanPlayer_InitStateActivatePlaceExplosiveTBA;
  HumanPlayer_apfState[45] = HumanPlayer_InitStateClimbLadder;
  HumanPlayer_apfState[46] = HumanPlayer_InitStateClimbLadderGetOnTop;
  HumanPlayer_apfState[47] = HumanPlayer_InitStateClimbLadderGetOffTop;
  HumanPlayer_apfState[48] = HumanPlayer_InitStateClimbLadderSlideDown;
  HumanPlayer_apfState[49] = HumanPlayer_InitStateClimbFence;
  HumanPlayer_apfState[50] = HumanPlayer_InitStateClimbWire;
  HumanPlayer_apfState[51] = HumanPlayer_InitStateSlideWire;
  HumanPlayer_apfState[52] = HumanPlayer_InitStatePeek;
  HumanPlayer_apfState[53] = HumanPlayer_InitStateComputer;
  HumanPlayer_apfState[54] = HumanPlayer_InitStateHit;
  HumanPlayer_apfState[55] = HumanPlayer_InitStateDie;
  HumanPlayer_apfState[56] = HumanPlayer_InitStateNetworkWait;
  HumanPlayer_apfState[57] = HumanPlayer_InitStateFly;
  HumanPlayer_apfState[58] = nullptr;
  HumanPlayer_apfState[59] = nullptr;
  HumanPlayer_apfState[60] = nullptr;
  HumanPlayer_apfState[61] = nullptr;
  HumanPlayer_apfState[62] = nullptr;
  HumanPlayer_apfState[63] = nullptr;
  HumanPlayer_apfState[64] = nullptr;
  HumanPlayer_apfState[65] = nullptr;
  HumanPlayer_apfState[66] = nullptr;
  HumanPlayer_apfState[67] = nullptr;
  HumanPlayer_apfState[68] = nullptr;
  HumanPlayer_apfState[69] = nullptr;
  HumanPlayer_apfState[70] = nullptr;
  HumanPlayer_apfState[71] = nullptr;
  HumanPlayer_apfState[72] = nullptr;
  HumanPlayer_apfState[73] = nullptr;
  HumanPlayer_apfState[74] = nullptr;
  HumanPlayer_apfState[75] = HumanPlayer_InitStateFlat;
  HumanPlayer_apfState[76] = nullptr;
  HumanPlayer_apfState[77] = nullptr;
  HumanPlayer_apfState[78] = nullptr;
  HumanPlayer_apfState[79] = nullptr;
  HumanPlayer_apfState[80] = HumanPlayer_InitStateFlatCrawl;
  HumanPlayer_apfExitState[80] = HumanPlayer_ExitStateFlatCrawl;
  HumanPlayer_apfState[81] = nullptr;
  HumanPlayer_apfState[83] = nullptr;
  HumanPlayer_apfState[84] = nullptr;
  HumanPlayer_apfState[85] = nullptr;
  HumanPlayer_apfState[86] = nullptr;
  HumanPlayer_apfState[87] = nullptr;
  HumanPlayer_apfState[88] = nullptr;
  HumanPlayer_apfState[89] = nullptr;
  HumanPlayer_apfState[90] = nullptr;
  HumanPlayer_apfState[91] = nullptr;
  HumanPlayer_apfState[92] = nullptr;
  HumanPlayer_apfState[93] = nullptr;
  HumanPlayer_apfState[94] = nullptr;
  HumanPlayer_apfState[95] = nullptr;
  HumanPlayer_apfState[96] = nullptr;
  HumanPlayer_apfState[97] = nullptr;
  HumanPlayer_apfState[98] = nullptr;
  HumanPlayer_apfState[99] = nullptr;
  HumanPlayer_apfState[100] = nullptr;
  HumanPlayer_apfState[101] = nullptr;
  HumanPlayer_apfState[102] = nullptr;
  HumanPlayer_apfState[103] = nullptr;
  HumanPlayer_apfState[104] = nullptr;
  HumanPlayer_apfState[105] = nullptr;
  HumanPlayer_apfState[106] = nullptr;
  HumanPlayer_apfState[107] = nullptr;
  HumanPlayer_apfState[108] = HumanPlayer_InitStateSilentKill;
  HumanPlayer_atStateAnimData[0].iWeaponTypeAnim = 60;
  HumanPlayer_atStateAnimData[1].iWeaponTypeAnim = 1;
  HumanPlayer_atStateAnimData[2].iWeaponTypeAnim = 61;
  HumanPlayer_atStateAnimData[3].iWeaponTypeAnim = 5;
  HumanPlayer_atStateAnimData[4].iWeaponTypeAnim = 9;
  HumanPlayer_atStateAnimData[5].iWeaponTypeAnim = 8;
  HumanPlayer_atStateAnimData[6].iWeaponTypeAnim = 10;
  HumanPlayer_atStateAnimData[7].iWeaponTypeAnim = 12;
  HumanPlayer_atStateAnimData[8].iWeaponTypeAnim = 11;
  HumanPlayer_atStateAnimData[9].iWeaponTypeAnim = 7;
  HumanPlayer_atStateAnimData[10].iWeaponTypeAnim = 6;
  HumanPlayer_atStateAnimData[11].iWeaponTypeAnim = 13;
  HumanPlayer_atStateAnimData[12].iWeaponTypeAnim = 17;
  HumanPlayer_atStateAnimData[13].iWeaponTypeAnim = 16;
  HumanPlayer_atStateAnimData[14].iWeaponTypeAnim = 18;
  HumanPlayer_atStateAnimData[15].iWeaponTypeAnim = 20;
  HumanPlayer_atStateAnimData[16].iWeaponTypeAnim = 19;
  HumanPlayer_atStateAnimData[17].iWeaponTypeAnim = 15;
  HumanPlayer_atStateAnimData[18].iWeaponTypeAnim = 14;
  HumanPlayer_atStateAnimData[19].iWeaponTypeAnim = 229;
  HumanPlayer_atStateAnimData[20].iWeaponTypeAnim = 230;
  HumanPlayer_atStateAnimData[21].iWeaponTypeAnim = 231;
  HumanPlayer_atStateAnimData[22].iWeaponTypeAnim = 232;
  HumanPlayer_atStateAnimData[23].iWeaponTypeAnim = 100;
  HumanPlayer_atStateAnimData[24].iWeaponTypeAnim = 119;
  HumanPlayer_atStateAnimData[25].iWeaponTypeAnim = 101;
  HumanPlayer_atStateAnimData[26].iWeaponTypeAnim = 102;
  HumanPlayer_atStateAnimData[27].iWeaponTypeAnim = 106;
  HumanPlayer_atStateAnimData[28].iWeaponTypeAnim = 105;
  HumanPlayer_atStateAnimData[29].iWeaponTypeAnim = 107;
  HumanPlayer_atStateAnimData[30].iWeaponTypeAnim = 109;
  HumanPlayer_atStateAnimData[31].iWeaponTypeAnim = 108;
  HumanPlayer_atStateAnimData[32].iWeaponTypeAnim = 104;
  HumanPlayer_atStateAnimData[33].iWeaponTypeAnim = 103;
  HumanPlayer_atStateAnimData[34].iWeaponTypeAnim = 100;
  HumanPlayer_atStateAnimData[35].iWeaponTypeAnim = 193;
  HumanPlayer_atStateAnimData[36].iWeaponTypeAnim = 52;
  HumanPlayer_atStateAnimData[37].iWeaponTypeAnim = 0;
  HumanPlayer_atStateAnimData[38].iWeaponTypeAnim = 0;
  HumanPlayer_atStateAnimData[39].iWeaponTypeAnim = 0;
  HumanPlayer_atStateAnimData[40].iWeaponTypeAnim = 0;
  HumanPlayer_atStateAnimData[41].iWeaponTypeAnim = 21;
  HumanPlayer_atStateAnimData[42].iWeaponTypeAnim = 0;
  HumanPlayer_atStateAnimData[53].iWeaponTypeAnim = 100;
  HumanPlayer_atStateAnimData[43].iWeaponTypeAnim = 0;
  HumanPlayer_atStateAnimData[44].iWeaponTypeAnim = 0;
  HumanPlayer_atStateAnimData[45].iWeaponTypeAnim = 136;
  HumanPlayer_atStateAnimData[46].iWeaponTypeAnim = 137;
  HumanPlayer_atStateAnimData[47].iWeaponTypeAnim = 138;
  HumanPlayer_atStateAnimData[48].iWeaponTypeAnim = 139;
  HumanPlayer_atStateAnimData[49].iWeaponTypeAnim = 140;
  HumanPlayer_atStateAnimData[50].iWeaponTypeAnim = 141;
  HumanPlayer_atStateAnimData[51].iWeaponTypeAnim = 142;
  HumanPlayer_atStateAnimData[52].iWeaponTypeAnim = 0;
  HumanPlayer_atStateAnimData[54].iWeaponTypeAnim = 143;
  HumanPlayer_atStateAnimData[55].iWeaponTypeAnim = 215;
  HumanPlayer_atStateAnimData[56].iWeaponTypeAnim = 0;
  HumanPlayer_atStateAnimData[57].iWeaponTypeAnim = 0;
  HumanPlayer_atStateAnimData[59].iWeaponTypeAnim = 215;
  HumanPlayer_atStateAnimData[60].iWeaponTypeAnim = 215;
  HumanPlayer_atStateAnimData[58].iWeaponTypeAnim = 170;
  HumanPlayer_atStateAnimData[61].iWeaponTypeAnim = 176;
  HumanPlayer_atStateAnimData[63].iWeaponTypeAnim = 167;
  HumanPlayer_atStateAnimData[62].iWeaponTypeAnim = 173;
  HumanPlayer_atStateAnimData[64].iWeaponTypeAnim = 164;
  HumanPlayer_atStateAnimData[65].iWeaponTypeAnim = 215;
  HumanPlayer_atStateAnimData[66].iWeaponTypeAnim = 215;
  HumanPlayer_atStateAnimData[67].iWeaponTypeAnim = 215;
  HumanPlayer_atStateAnimData[68].iWeaponTypeAnim = 117;
  HumanPlayer_atStateAnimData[69].iWeaponTypeAnim = 54;
  HumanPlayer_atStateAnimData[70].iWeaponTypeAnim = 55;
  HumanPlayer_atStateAnimData[71].iWeaponTypeAnim = 57;
  HumanPlayer_atStateAnimData[72].iWeaponTypeAnim = 56;
  HumanPlayer_atStateAnimData[73].iWeaponTypeAnim = 58;
  HumanPlayer_atStateAnimData[74].iWeaponTypeAnim = 21;
  HumanPlayer_atStateAnimData[75].iWeaponTypeAnim = 120;
  HumanPlayer_atStateAnimData[76].iWeaponTypeAnim = 121;
  HumanPlayer_atStateAnimData[77].iWeaponTypeAnim = 122;
  HumanPlayer_atStateAnimData[78].iWeaponTypeAnim = 123;
  HumanPlayer_atStateAnimData[79].iWeaponTypeAnim = 124;
  HumanPlayer_atStateAnimData[80].iWeaponTypeAnim = 128;
  HumanPlayer_atStateAnimData[81].iWeaponTypeAnim = 126;
  HumanPlayer_atStateAnimData[82].iWeaponTypeAnim = 187;
  HumanPlayer_atStateAnimData[83].iWeaponTypeAnim = 78;
  HumanPlayer_atStateAnimData[84].iWeaponTypeAnim = 79;
  HumanPlayer_atStateAnimData[85].iWeaponTypeAnim = 80;
  HumanPlayer_atStateAnimData[86].iWeaponTypeAnim = 81;
  HumanPlayer_atStateAnimData[87].iWeaponTypeAnim = 233;
  HumanPlayer_atStateAnimData[88].iWeaponTypeAnim = 234;
  HumanPlayer_atStateAnimData[89].iWeaponTypeAnim = 60;
  HumanPlayer_atStateAnimData[90].iWeaponTypeAnim = 235;
  HumanPlayer_atStateAnimData[91].iWeaponTypeAnim = 236;
  HumanPlayer_atStateAnimData[92].iWeaponTypeAnim = 215;
  HumanPlayer_atStateAnimData[93].iWeaponTypeAnim = 216;
  HumanPlayer_atStateAnimData[94].iWeaponTypeAnim = 217;
  HumanPlayer_atStateAnimData[95].iWeaponTypeAnim = 218;
  HumanPlayer_atStateAnimData[96].iWeaponTypeAnim = 219;
  HumanPlayer_atStateAnimData[97].iWeaponTypeAnim = 220;
  HumanPlayer_atStateAnimData[98].iWeaponTypeAnim = 209;
  HumanPlayer_atStateAnimData[99].iWeaponTypeAnim = 210;
  HumanPlayer_atStateAnimData[100].iWeaponTypeAnim = 199;
  HumanPlayer_atStateAnimData[101].iWeaponTypeAnim = 200;
  HumanPlayer_atStateAnimData[102].iWeaponTypeAnim = 201;
  HumanPlayer_atStateAnimData[103].iWeaponTypeAnim = 202;
  HumanPlayer_atStateAnimData[104].iWeaponTypeAnim = 203;
  HumanPlayer_atStateAnimData[105].iWeaponTypeAnim = 204;
  HumanPlayer_atStateAnimData[106].iWeaponTypeAnim = 228;
  HumanPlayer_atStateAnimData[107].iWeaponTypeAnim = 237;
  HumanPlayer_atStateAnimData[108].iWeaponTypeAnim = 0;
}

// source: j/0/human/humanplayer.c:2226  [size]
// attributes: thunk
void __cdecl HumanPlayer_SendAIEvent(struct HumanAIEventContext_t *ptHumanAIEventContext)
{
  HumanAI_SendEvent(ptHumanAIEventContext);
}

// source: j/0/human/humanplayer.c:2242  [anchor-caller]
void __cdecl HumanPlayer_SendWalkEvent(struct QTask_s *ptHumanQTask, enum bool isRun)
{
  struct QReference_s *ptMiddle; // eax
  double v3; // st7
  char *p_ptPrev; // eax
  struct QTask_s *SoundDef; // eax
  struct QTask_s *v6; // edx
  struct QTask_s *ptTail; // ecx
  struct QReference_s *v8; // eax
  struct HumanAIEventContext_t tEventContext; // [esp+4h] [ebp-44h] BYREF

  ptMiddle = ptHumanQTask[42].tQTaskRefList.ptMiddle;
  v3 = 20480.0;
  if ( ptMiddle )
  {
    if ( isRun )
      p_ptPrev = (char *)&ptMiddle[28].ptPrev;
    else
      p_ptPrev = (char *)&ptMiddle[7];
    SoundDef = SoundSys_GetSoundDef(p_ptPrev);
    v6 = SoundDef;
    if ( SoundDef && QTask_IsQTaskTypeDerived(SoundDef->eQTaskType, SoundDefSound_eQTaskType) )
      v3 = *(float *)&v6[6].tQTaskRefList.ptTail * 3072.0;
    else
      v3 = (float)20480.0;
  }
  ptTail = ptHumanQTask[33].tQTaskChildren.ptTail;
  tEventContext.vRadius = v3;
  v8 = ptHumanQTask[10].tQTaskRefList.ptTail;
  tEventContext.eEvent = 9;
  tEventContext.eTeam = (int)v8;
  tEventContext.bFlags = 1090;
  tEventContext.ptPosition = (struct real64x3_t *)&ptTail[10].tQTaskChildren;
  tEventContext.ptReferenceQTask = ptHumanQTask;
  tEventContext.ptHumanOriginatorQTask = ptHumanQTask;
  HumanAI_SendEvent(&tEventContext);
}

// source: j/0/human/humanplayer.c:2290  [anchor-callee]
void __cdecl HumanPlayer_SetWeaponPrecision(
        struct QTask_s *ptHumanQTask,
        enum HumanPlayerPrecisionType_e ePrecisionType)
{
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptTail; // edx
  struct QTask_s *ptHead; // eax
  double v5; // st7

  ptPrev = ptHumanQTask[33].ptNext[1].ptPrev;
  if ( ptPrev && (ptTail = ptPrev->tQTaskChildren.ptTail) != nullptr )
  {
    ptHumanQTask[77].tQTaskChildren.ptHead = (struct QTask_s *)ePrecisionType;
    switch ( ePrecisionType )
    {
      case HUMANPLAYER_PRECISIONTYPE_RUNNING:
        ptHead = ptTail[21].ptPrev;
        goto LABEL_14;
      case HUMANPLAYER_PRECISIONTYPE_WALKING:
        ptHead = ptTail[21].tQTaskChildren.ptHead;
        goto LABEL_14;
      case HUMANPLAYER_PRECISIONTYPE_CROUCHING:
        ptHead = ptTail[21].tQTaskChildren.ptMiddle;
        goto LABEL_14;
      case HUMANPLAYER_PRECISIONTYPE_CROUCHWALKING:
        ptHead = ptTail[21].tQTaskChildren.ptTail;
        goto LABEL_14;
      case HUMANPLAYER_PRECISIONTYPE_LYINGFLAT:
        ptHead = (struct QTask_s *)ptTail[21].tQTaskRefList.ptHead;
        goto LABEL_14;
      case HUMANPLAYER_PRECISIONTYPE_CRAWLING:
        ptHead = (struct QTask_s *)ptTail[21].tQTaskRefList.ptMiddle;
        goto LABEL_14;
      case HUMANPLAYER_PRECISIONTYPE_JUMPING:
        *(float *)&ptHumanQTask[77].tQTaskChildren.ptMiddle = *(float *)&ptTail[21].tQTaskRefList.ptTail
                                                            + *(float *)&ptTail[21].ptPrev;
        goto LABEL_15;
      case HUMANPLAYER_PRECISIONTYPE_CROUCHJUMPING:
        *(float *)&ptHumanQTask[77].tQTaskChildren.ptMiddle = *(float *)&ptTail[21].tQTaskRefList.ptTail
                                                            + *(float *)&ptTail[21].tQTaskChildren.ptTail
                                                            + *(float *)&ptTail[21].ptPrev;
        goto LABEL_15;
      default:
        ptHead = ptTail[21].ptNext;
LABEL_14:
        ptHumanQTask[77].tQTaskChildren.ptMiddle = ptHead;
LABEL_15:
        v5 = *(float *)&ptHumanQTask[43].ptParent;
        if ( v5 < 0.0 )
          v5 = -v5;
        *(float *)&ptHumanQTask[77].tQTaskChildren.ptMiddle = v5 * *(float *)&ptTail[21].ptParent * 3.0
                                                            + *(float *)&ptHumanQTask[77].tQTaskChildren.ptMiddle;
        break;
    }
  }
  else
  {
    ptHumanQTask[77].tQTaskChildren.ptHead = nullptr;
    ptHumanQTask[77].tQTaskChildren.ptMiddle = nullptr;
  }
}

// source: j/0/human/humanplayer.c:2374  [anchor-callee]
struct QTask_s *__cdecl Human_SendDoorAIEvent(struct QTask_s *ptDoorQTask, struct QTask_s *ptHumanQTask)
{
  struct QTask_s *result; // eax
  struct HumanAIEventContext_t tContext; // [esp+8h] [ebp-40h] BYREF

  tContext.eTeam = (int)ptHumanQTask[10].tQTaskRefList.ptTail;
  tContext.eEvent = 11;
  tContext.bFlags = 1090;
  tContext.vRadius = 20480.0;
  tContext.ptPosition = (struct real64x3_t *)&ptHumanQTask[1];
  tContext.ptReferenceQTask = ptDoorQTask;
  tContext.ptHumanOriginatorQTask = ptHumanQTask;
  HumanAI_SendEvent(&tContext);
  return result;
}

// source: j/0/human/humanplayer.c:2403  [anchor-mhash]
void __cdecl HumanPlayer_DrawActionItemHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v3; // ecx
  int v4; // eax
  int v5; // eax
  struct WeaponType_s *WeaponTypeFromID; // eax
  struct QSprite_s *p_tWeaponPickupSprite; // esi
  int v8; // eax
  struct ActionMenuDrawContext_s tTempContext; // [esp+Ch] [ebp-18h] BYREF
  int pxContexta = *(int *)&pxContext; // [esp+2Ch] [ebp+8h] ARGSLOT

  qmemcpy(&tTempContext, pxContext, sizeof(tTempContext));
  v3 = *(_DWORD *)pxContext;
  tTempContext.ptOverlaySprite = (struct QSprite_s *)&StatusScreen_ptStatusScreenQTask[21].ptPrev;
  v4 = *(_DWORD *)(v3 + 4);
  if ( v4 )
  {
    v5 = *(_DWORD *)(v4 + 8);
    if ( v5 )
    {
      WeaponTypeFromID = WeaponType_GetWeaponTypeFromID(*(_DWORD *)(v5 + 416));
      if ( WeaponTypeFromID->isWeaponPickupSpriteLoaded )
      {
        p_tWeaponPickupSprite = &WeaponTypeFromID->tWeaponPickupSprite;
        ActionMenuScreen_DrawActionItem(ActionMenuScreen_ptQTask, &WeaponTypeFromID->tWeaponPickupSprite, pxContext);
        pxContexta = p_tWeaponPickupSprite->atQAnimframe[p_tWeaponPickupSprite->nQAnimframes].nHeight;
        *((_DWORD *)pxContext + 5) += (int)(10);
        tTempContext.vY = (double)pxContexta + tTempContext.vY + 10.0;
      }
    }
  }
  v8 = *(_DWORD *)(*(_DWORD *)pxContext + 12);
  if ( v8 )
  {
    if ( *(_DWORD *)(v8 + 1924) )
    {
      ActionMenuScreen_DrawActionItem(ActionMenuScreen_ptQTask, (struct QSprite_s *)(v8 + 1880), &tTempContext);
      *((_DWORD *)pxContext + 5) += (int)(tTempContext.tReturn.nHeight);
    }
  }
}

// source: j/0/human/humanplayer.c:2463  [anchor-caller]
void __cdecl HumanPlayer_RegisterWeaponPickupActionItem(
        struct QTask_s *ptQTask,
        struct QTask_s *ptMyGunPickup,
        struct QTask_s *ptMyDropWeaponType)
{
  struct QTask_s *v3; // edx
  int i; // esi
  int v5; // eax
  int v6; // ebx
  struct QTask_s *v7; // edi
  struct WeaponType_s *WeaponTypeFromID; // ebp

  v3 = ActionMenuScreen_ptQTask;
  for ( i = 0; i < 120; i += 20 )
  {
    if ( i >= 0 && *((_BYTE *)&v3[1].tQTaskChildren.ptTail + i + 2) && *((_BYTE *)&v3[1].tQTaskChildren.ptTail + i + 1) )
    {
      v5 = *(int *)((char *)&v3[1].ptPrev + i);
      v6 = v5 ? *(_DWORD *)(v5 + 8) : 0;
      v7 = *(struct QTask_s **)((char *)&v3[1].tQTaskChildren.ptMiddle + i);
      if ( QTask_IsQTaskTypeDerived(*(_WORD *)(v6 + 36), GunPickup_eQTaskType) )
      {
        if ( v7 && v7 == ptMyDropWeaponType )
        {
          WeaponTypeFromID = WeaponType_GetWeaponTypeFromID((int)ptMyGunPickup[10].tQTaskChildren.ptTail);
          if ( WeaponType_GetWeaponTypeFromID(*(_DWORD *)(v6 + 416)) == WeaponTypeFromID )
            return;
          v3 = ActionMenuScreen_ptQTask;
        }
      }
    }
  }
  ActionMenuScreen_RegisterActionItem(v3, ptMyGunPickup, ptQTask, ptMyDropWeaponType);
}

// source: j/0/human/humanplayer.c:2507  [anchor-caller]
void __cdecl HumanPlayer_Pickup(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { int pvBeta; };
    struct { char igi2_o1[4]; int v21; };
    struct { char igi2_o2[8]; struct WeaponType_s *pvAlpha; };
    struct { char igi2_o3[12]; float ptSource[11]; };
    struct { char igi2_o4[56]; int v24; };
    struct { char igi2_o5[60]; int v25; };
    struct { char igi2_o6[64]; struct QTask_s ptHumanQTask; };
    struct { char igi2_o7[104]; struct real32x9_t ptPos; };
    char igi2_extent[144];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTaskNodeList_s *p_tQTaskChildren; // esi
  float v2; // ebx
  unsigned __int16 v3; // ax
  int v4; // edi
  struct WeaponType_s *WeaponTypeFromID; // eax
  struct WeaponType_s *NextEnabledWeaponTypeFromCategory; // esi
  struct WeaponType_s *v7; // eax
  double v8; // st7
  int v9; // eax
  int v10; // eax
  struct WeaponType_s *v11; // eax
  struct WeaponTypeItem_s *WeaponTypeItemFromWeaponType; // eax
  struct QTask_s *ptTail; // eax
  struct WeaponType_s *v14; // eax
  struct QTask_s *ptPrev; // ebx
  enum bool v16; // edi
  double RandomNumberReal32; // st7
  struct QTask_s *v18; // eax
  bool v19; // cc

  if ( LOBYTE(ptQTask[29].tQTaskRefList.ptHead) )
    return;
  p_tQTaskChildren = &ptQTask[33].tQTaskChildren.ptTail[10].tQTaskChildren;
  LODWORD(igi2_frame.ptSource[3]) = ptQTask;
  qmemcpy(&igi2_frame.ptSource[5], p_tQTaskChildren, 0x18u);
  igi2_frame.ptSource[0] = *(float *)&GameFunctions_ptPickupQTaskList->nTask;
  igi2_frame.ptSource[1] = 0.0;
  if ( SLODWORD(igi2_frame.ptSource[0]) <= 0 )
    return;
  igi2_frame.pvBeta = 8;
  while ( 1 )
  {
    igi2_frame.v25 = 0;
    igi2_frame.v24 = 1;
    v2 = *(float *)((char *)&GameFunctions_ptPickupQTaskList->nTask + igi2_frame.pvBeta);
    v3 = *(_WORD *)(LODWORD(v2) + 36);
    igi2_frame.ptSource[2] = v2;
    if ( QTask_IsQTaskTypeDerived(v3, GunPickup_eQTaskType) == false )
    {
      igi2_frame.v24 = 1;
      ((void (__cdecl *)(_DWORD, float *))QTask_aatQTaskFinalEvent[GameFunctions_ePickupQTaskEvent][*(unsigned __int16 *)(LODWORD(v2) + 36)].pfHandler)(
        LODWORD(v2),
        &igi2_frame.ptSource[3]);
      goto LABEL_38;
    }
    if ( ptQTask[75].ptPrev == (struct QTask_s *)6 || ptQTask[86].tQTaskRefList.ptHead )
      goto LABEL_38;
    igi2_frame.v24 = 0;
    v4 = *(_DWORD *)(LODWORD(v2) + 416);
    igi2_frame.v21 = 0;
    WeaponTypeFromID = WeaponType_GetWeaponTypeFromID(v4);
    NextEnabledWeaponTypeFromCategory = Weapon_GetNextEnabledWeaponTypeFromCategory(
                                          ptQTask[33].ptNext,
                                          WeaponTypeFromID->eWeaponCategory,
                                          nullptr);
    v7 = WeaponType_GetWeaponTypeFromID(*(_DWORD *)(LODWORD(v2) + 416));
    v8 = *(float *)&ptQTask[20].ptNext;
    igi2_frame.pvAlpha = v7;
    if ( v8 != 0.0 && *(float *)&ptQTask[13].tQTaskRefList.ptTail == 0.0 )
    {
      if ( !NextEnabledWeaponTypeFromCategory )
        goto LABEL_24;
      while ( 1 )
      {
        if ( ActionMenuScreen_ptQTask[4].tQTaskChildren.ptHead && !ActionMenuScreen_ptQTask[4].ptNext )
        {
          v9 = *((_DWORD *)&ActionMenuScreen_ptQTask[1].ptPrev
               + 5 * (int)ActionMenuScreen_ptQTask[4].tQTaskChildren.ptTail);
          v10 = v9 ? *(_DWORD *)(v9 + 8) : 0;
          if ( LODWORD(v2) == v10
            && NextEnabledWeaponTypeFromCategory == *((struct WeaponType_s **)&ActionMenuScreen_ptQTask[1].tQTaskChildren.ptMiddle
                                                    + 5 * (int)ActionMenuScreen_ptQTask[4].tQTaskChildren.ptTail) )
          {
            break;
          }
        }
        v11 = WeaponType_GetWeaponTypeFromID(*(_DWORD *)(LODWORD(v2) + 416));
        NextEnabledWeaponTypeFromCategory = Weapon_GetNextEnabledWeaponTypeFromCategory(
                                              ptQTask[33].ptNext,
                                              v11->eWeaponCategory,
                                              NextEnabledWeaponTypeFromCategory);
        if ( !NextEnabledWeaponTypeFromCategory )
          goto LABEL_24;
      }
LABEL_23:
      igi2_frame.v24 = 1;
      igi2_frame.v21 = 1;
      goto LABEL_24;
    }
    WeaponTypeItemFromWeaponType = Weapon_GetWeaponTypeItemFromWeaponType(ptQTask[33].ptNext, v7->zWeaponScriptID);
    if ( WeaponTypeItemFromWeaponType && WeaponTypeItemFromWeaponType->isActive )
    {
      igi2_frame.v24 = 1;
      NextEnabledWeaponTypeFromCategory = nullptr;
      goto LABEL_24;
    }
    if ( !NextEnabledWeaponTypeFromCategory )
      goto LABEL_23;
LABEL_24:
    ((void (__cdecl *)(_DWORD, float *))QTask_aatQTaskFinalEvent[GameFunctions_ePickupQTaskEvent][*(unsigned __int16 *)(LODWORD(v2) + 36)].pfHandler)(
      LODWORD(v2),
      &igi2_frame.ptSource[3]);
    if ( !igi2_frame.v21 )
    {
      if ( igi2_frame.v25 )
      {
        ptTail = ptQTask[46].tQTaskChildren.ptTail;
        if ( !ptTail || !ptTail->tQTaskChildren.ptHead )
        {
          for ( ;
                NextEnabledWeaponTypeFromCategory;
                NextEnabledWeaponTypeFromCategory = Weapon_GetNextEnabledWeaponTypeFromCategory(
                                                      ptQTask[33].ptNext,
                                                      v14->eWeaponCategory,
                                                      NextEnabledWeaponTypeFromCategory) )
          {
            HumanPlayer_RegisterWeaponPickupActionItem(
              ptQTask,
              (struct QTask_s *)LODWORD(v2),
              &NextEnabledWeaponTypeFromCategory->tQTask);
            v14 = WeaponType_GetWeaponTypeFromID(*(_DWORD *)(LODWORD(v2) + 416));
          }
        }
      }
      goto LABEL_38;
    }
    if ( igi2_frame.v25 && NextEnabledWeaponTypeFromCategory )
      break;
LABEL_38:
    v19 = (int)(++LODWORD(igi2_frame.ptSource[1])) < SLODWORD(igi2_frame.ptSource[0]);
    igi2_frame.pvBeta += 4;
    if ( !v19 )
      return;
  }
  if ( Game_eGameMode == GAME_GAMEMODE_SINGLEPLAYER )
  {
    memset(&igi2_frame.ptHumanQTask, 0, sizeof(igi2_frame.ptHumanQTask));
    ((void (__cdecl *)(struct WeaponType_s *, struct QTask_s *))QTask_aatQTaskFinalEvent[WeaponType_eGetAmmoInfoQTaskEvent][igi2_frame.pvAlpha->tQTask.eQTaskType].pfHandler)(
      igi2_frame.pvAlpha,
      &igi2_frame.ptHumanQTask);
    ptPrev = igi2_frame.ptHumanQTask.ptPrev;
    memset(&igi2_frame.ptPos, 0, sizeof(igi2_frame.ptPos));
    ((void (__cdecl *)(struct WeaponType_s *, struct real32x9_t *))QTask_aatQTaskFinalEvent[WeaponType_eGetAmmoInfoQTaskEvent][NextEnabledWeaponTypeFromCategory->tQTask.eQTaskType].pfHandler)(
      NextEnabledWeaponTypeFromCategory,
      &igi2_frame.ptPos);
    v16 = ptPrev != (struct QTask_s *)LODWORD(igi2_frame.ptPos.tX.vY);
    HumanAnim_GetWeaponPositionAndOrientation(ptQTask, (struct real64x3_t *)&igi2_frame.ptHumanQTask, &igi2_frame.ptPos);
    sub_580CA0((int)ptQTask, (double *)&igi2_frame.ptHumanQTask);
    *(double *)&igi2_frame.ptHumanQTask.tQTaskChildren.ptTail = *(double *)&igi2_frame.ptHumanQTask.tQTaskChildren.ptTail + 1228.800048828125;
    Real32x9_GetAngles((struct real32x9_t *)&ptQTask[3].ptPrev, igi2_frame.ptSource, (float *)&igi2_frame.pvAlpha, (float *)&igi2_frame.pvBeta);
    RandomNumberReal32 = Random_GetRandomNumberReal32(&Game_ptGame->tRunRandomState);
    *(float *)&igi2_frame.pvBeta = RandomNumberReal32 * 1.5707963705062866 + *(float *)&igi2_frame.pvBeta - 0.7853981852531433;
    GunPickup_NewFromWeapon(
      ptQTask[33].ptNext,
      NextEnabledWeaponTypeFromCategory,
      (struct real64x3_t *)&igi2_frame.ptHumanQTask,
      &igi2_frame.ptPos,
      *(float *)&igi2_frame.pvBeta,
      v16);
    Weapon_DisableWeaponType(ptQTask[33].ptNext, NextEnabledWeaponTypeFromCategory->zWeaponScriptID, v16);
    v2 = igi2_frame.ptSource[2];
  }
  v18 = ptQTask[33].ptNext[1].ptPrev;
  if ( v18 )
    v18 = v18->tQTaskChildren.ptTail;
  if ( v18 == (struct QTask_s *)NextEnabledWeaponTypeFromCategory )
    ptQTask[76].ptParent = *(struct QTask_s **)(LODWORD(v2) + 416);
}

// source: j/0/human/humanplayer.c:2659  [anchor-strings]
void __cdecl HumanPlayer_InAirControl(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char *v18; };
    struct { char igi2_o1[24]; float vDamage; };
    struct { char igi2_o2[24]; float vDamagea; };
    struct { char igi2_o3[28]; float tSpeed; };
    struct { char igi2_o4[28]; float tSpeeda; };
    struct { char igi2_o5[32]; float tSpeed_4; };
    struct { char igi2_o6[40]; float v24; };
    struct { char igi2_o7[44]; float tGroundSpeed; };
    struct { char igi2_o8[48]; float tGroundSpeed_4; };
    struct { char igi2_o9[52]; double tGroundSpeed_8; };
    struct { char igi2_o10[60]; double tGroundSpeed_16; };
    struct { char igi2_o11[68]; struct real64x3_t tPlatformPos; };
    struct { char igi2_o12[100]; struct HumanAIEventContext_t tContext; };
    struct { char igi2_o13[164]; struct ServerGameMessageDamage_s tDamageMessage; };
    char igi2_extent[236];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v1; // st7
  double vInAirControlSpeed; // st6
  double v3; // st6
  double v4; // st5
  bool v5; // zf
  double v6; // st7
  double v7; // st6
  struct QReference_s *ptMiddle; // eax
  _WORD *pxObject; // edx
  double v10; // st7
  double v11; // st6
  struct QTask_s *ptTail; // eax
  double v13; // st7
  struct Client_s *ClientFromHumanQTask; // esi
  int Timer; // eax
  int eNetworkID; // ecx
  struct QReference_s *v17; // ecx

  v1 = *(float *)&ptQTask[38].tQTaskChildren.ptMiddle - 84.74169158935547;
  igi2_frame.tSpeed = 0.0;
  *(float *)&ptQTask[38].tQTaskChildren.ptMiddle = v1;
  vInAirControlSpeed = 0.0;
  if ( *(float *)&ptQTask[19].tQTaskChildren.ptMiddle != 0.0 )
    igi2_frame.tSpeed = -HumanPlayer_tGeneral.vInAirControlSpeed;
  if ( *(float *)&ptQTask[19].tQTaskChildren.ptTail != 0.0 )
    igi2_frame.tSpeed = HumanPlayer_tGeneral.vInAirControlSpeed + igi2_frame.tSpeed;
  if ( *(float *)&ptQTask[19].tQTaskRefList.ptHead != 0.0 )
    vInAirControlSpeed = HumanPlayer_tGeneral.vInAirControlSpeed;
  if ( *(float *)&ptQTask[19].tQTaskRefList.ptMiddle != 0.0 )
    vInAirControlSpeed = vInAirControlSpeed - HumanPlayer_tGeneral.vInAirControlSpeed;
  igi2_frame.tGroundSpeed = vInAirControlSpeed * *(float *)&ptQTask[3].tQTaskChildren.ptHead
               + igi2_frame.tSpeed * *(float *)&ptQTask[3].ptPrev
               + *(float *)&ptQTask[3].tQTaskChildren.ptMiddle * 0.0;
  igi2_frame.tGroundSpeed_4 = vInAirControlSpeed * *(float *)&ptQTask[3].tQTaskRefList.ptHead
                 + igi2_frame.tSpeed * *(float *)&ptQTask[3].tQTaskChildren.ptTail
                 + *(float *)&ptQTask[3].tQTaskRefList.ptMiddle * 0.0;
  v3 = vInAirControlSpeed * *(float *)&ptQTask[3].ptParent
     + igi2_frame.tSpeed * *(float *)&ptQTask[3].tQTaskRefList.ptTail
     + *(float *)&ptQTask[3].eQTaskType * 0.0;
  igi2_frame.vDamage = igi2_frame.tGroundSpeed + *(float *)&ptQTask[38].ptPrev;
  v4 = igi2_frame.tGroundSpeed_4 + *(float *)&ptQTask[38].tQTaskChildren.ptHead;
  *(float *)&ptQTask[38].ptPrev = igi2_frame.vDamage;
  v5 = (ptQTask[30].eQTaskType & 2) == 0;
  igi2_frame.v24 = v4;
  v6 = v1 + v3;
  *(float *)&ptQTask[38].tQTaskChildren.ptHead = igi2_frame.v24;
  *(float *)&ptQTask[38].tQTaskChildren.ptMiddle = v6;
  if ( v5 )
  {
    ptQTask[87].tQTaskRefList.ptTail = (struct QReference_s *)SLOBYTE(ptQTask[74].ptPrev);
  }
  else
  {
    v7 = 0.0;
    igi2_frame.tGroundSpeed_8 = 0.0;
    igi2_frame.tGroundSpeed_16 = 0.0;
    if ( HIBYTE(ptQTask[74].ptPrev) )
    {
      ptMiddle = ptQTask[44].tQTaskRefList.ptMiddle;
      if ( ptMiddle )
      {
        pxObject = ptMiddle->pxObject;
        if ( pxObject )
        {
          if ( QTask_IsQTaskTypeDerived(pxObject[18], RigidDynCubeObj_eQTaskType) )
          {
            qmemcpy(&igi2_frame.tPlatformPos, pxObject + 20, sizeof(igi2_frame.tPlatformPos));
            v7 = igi2_frame.tPlatformPos.vX - *(double *)&ptQTask[70].tQTaskRefList.ptMiddle;
            igi2_frame.tGroundSpeed_8 = igi2_frame.tPlatformPos.vY - *(double *)&ptQTask[70].ptParent;
            igi2_frame.tGroundSpeed_16 = igi2_frame.tPlatformPos.vZ - *(double *)&ptQTask[71].ptNext;
          }
        }
      }
    }
    if ( ptQTask[87].tQTaskRefList.ptTail )
    {
      if ( v6 < 0.0 )
        v6 = -v6;
    }
    else
    {
      igi2_frame.tSpeeda = igi2_frame.vDamage - v7;
      igi2_frame.tSpeed_4 = igi2_frame.v24 - igi2_frame.tGroundSpeed_8;
      v6 = sqrt(igi2_frame.tSpeeda * igi2_frame.tSpeeda + igi2_frame.tSpeed_4 * igi2_frame.tSpeed_4 + (v6 - igi2_frame.tGroundSpeed_16) * (v6 - igi2_frame.tGroundSpeed_16));
    }
    v10 = v6 * 0.000244140625 * 30.0;
    v11 = 0.125 * v10;
    if ( 0.125 * v10 >= 0.0 )
    {
      if ( v11 > 1.0 )
        v11 = 1.0;
    }
    else
    {
      v11 = 0.0;
    }
    ptTail = ptQTask[33].tQTaskChildren.ptTail;
    *(float *)&ptTail[15].tQTaskChildren.ptTail = v11 * -1024.0;
    ptTail[15].tQTaskRefList.ptHead = nullptr;
    igi2_frame.tContext.vRadius = 16384.0;
    v13 = v10 - 16.5;
    if ( v13 > 0.0 )
    {
      ptQTask[29].tQTaskChildren.ptHead = (struct QTask_s *)13;
      igi2_frame.vDamagea = v13 * 0.07000000029802322 * *(float *)&ptQTask[25].tQTaskRefList.ptMiddle;
      if ( !LOBYTE(ptQTask[29].tQTaskRefList.ptHead) && NetManager_eMode != NETMANAGER_MODE_WARMUP )
      {
        if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
        {
          ClientFromHumanQTask = NetManager_GetClientFromHumanQTask(ptQTask);
          igi2_frame.tDamageMessage.tBaseMessage.eGameMessage = 1145130311;
          Timer = NetManager_GetTimer();
          eNetworkID = ClientFromHumanQTask->eNetworkID;
          igi2_frame.tDamageMessage.eDamageType = 2;
          igi2_frame.tDamageMessage.tBaseMessage.nLocalTime = Timer;
          igi2_frame.tDamageMessage.vDamage = igi2_frame.vDamagea;
          igi2_frame.tDamageMessage.eDamagePart = 16;
          igi2_frame.tDamageMessage.iVictimID = eNetworkID;
          igi2_frame.tDamageMessage.iKillerID = eNetworkID;
          NetManager_SendGameMessage(0, eNetworkID, NETWORKQUEUE_GUARANTEED, &igi2_frame.tDamageMessage.tBaseMessage, 0x48u);
        }
        else
        {
          *(float *)&ptQTask[28].tQTaskChildren.ptTail = igi2_frame.vDamagea + *(float *)&ptQTask[28].tQTaskChildren.ptTail;
          *(float *)&ptQTask[25].tQTaskRefList.ptHead = igi2_frame.vDamagea + *(float *)&ptQTask[25].tQTaskRefList.ptHead;
        }
      }
      if ( igi2_frame.vDamagea != 0.0 )
      {
        if ( *(float *)&ptQTask[25].tQTaskRefList.ptMiddle * 0.10000000149011612 <= igi2_frame.vDamagea )
        {
          if ( *(float *)&ptQTask[25].tQTaskRefList.ptMiddle * 0.20000000298023224 <= igi2_frame.vDamagea )
            igi2_frame.v18 = "player_fall_3";
          else
            igi2_frame.v18 = "player_fall_2";
          sprintf((char *const)&igi2_frame.tPlatformPos, igi2_frame.v18);
        }
        else
        {
          sprintf((char *const)&igi2_frame.tPlatformPos, "player_fall_1");
        }
        SoundSys_NewSoundFn(ptQTask[33].tQTaskChildren.ptTail, (char *)&igi2_frame.tPlatformPos);
        igi2_frame.tContext.vRadius = 16384.0;
      }
    }
    v17 = ptQTask[10].tQTaskRefList.ptTail;
    igi2_frame.tContext.eEvent = 10;
    igi2_frame.tContext.eTeam = (int)v17;
    igi2_frame.tContext.bFlags = 1090;
    igi2_frame.tContext.ptPosition = (struct real64x3_t *)&ptQTask[1];
    igi2_frame.tContext.ptReferenceQTask = ptQTask;
    igi2_frame.tContext.ptHumanOriginatorQTask = ptQTask;
    HumanAI_SendEvent(&igi2_frame.tContext);
  }
}

// source: j/0/human/humanplayer.c:2887  [anchor-mhash]
char *__cdecl HumanPlayer_PlaySound(char *zSound)
{
  if ( zSound )
  {
    if ( HumanPlayer_ptQTask )
      return (char *)SoundSys_NewSoundFn(HumanPlayer_ptQTask[33].tQTaskChildren.ptTail, zSound);
  }
  return zSound;
}

// source: j/0/human/humanplayer.c:2911  [anchor-caller]
enum bool __cdecl HumanPlayer_IsWeaponSelectable(
        struct QTask_s *ptWeaponQTask,
        struct WeaponType_s *ptWeaponType)
{
  return Weapon_IsWeaponSelectable(ptWeaponQTask, ptWeaponType->zWeaponScriptID);
}

// source: j/0/human/humanplayer.c:2924  [anchor-mhash]
void __cdecl HumanPlayer_SelectWeaponFromCategory(struct QTask_s *ptQTask)
{
  enum WeaponCategory_e v1; // ebp
  struct QTask_s *ptNext; // ebx
  struct QTask_s *v3; // eax
  struct WeaponType_s *ptTail; // esi
  enum WeaponCategory_e eWeaponCategory; // edi
  __int32 v6; // edi
  struct WeaponType_s *NextEnabledWeaponTypeFromCategory; // eax
  int nRetry; // [esp+4h] [ebp-4h]

  v1 = WEAPONCATEGORY_NONE;
  if ( *(float *)&ptQTask[21].tQTaskRefList.ptTail != 0.0 )
    v1 = *(float *)&ptQTask[15].tQTaskChildren.ptTail == 0.0;
  if ( *(float *)&ptQTask[21].ptParent != 0.0 && *(float *)&ptQTask[15].tQTaskRefList.ptHead == 0.0 )
    v1 = WEAPONCATEGORY_SIDEARM;
  if ( *(float *)&ptQTask[21].eQTaskType != 0.0 && *(float *)&ptQTask[15].tQTaskRefList.ptMiddle == 0.0 )
    v1 = WEAPONCATEGORY_PRIMARY;
  if ( *(float *)&ptQTask[22].ptNext != 0.0 && *(float *)&ptQTask[15].tQTaskRefList.ptTail == 0.0 )
    v1 = WEAPONCATEGORY_GRENADE;
  if ( *(float *)&ptQTask[22].ptPrev != 0.0 && *(float *)&ptQTask[15].ptParent == 0.0 )
    v1 = WEAPONCATEGORY_C4;
  if ( *(float *)&ptQTask[22].tQTaskChildren.ptHead != 0.0 && *(float *)&ptQTask[15].eQTaskType == 0.0 )
    v1 = WEAPONCATEGORY_PROXIMITYMINE;
  if ( *(float *)&ptQTask[22].tQTaskChildren.ptMiddle != 0.0 && *(float *)&ptQTask[16].ptNext == 0.0 )
    v1 = WEAPONCATEGORY_LASERDESIGNATOR;
  if ( *(float *)&ptQTask[22].tQTaskRefList.ptHead == 0.0 || *(float *)&ptQTask[16].tQTaskChildren.ptHead != 0.0 )
  {
    if ( v1 == WEAPONCATEGORY_NONE )
      return;
  }
  else
  {
    v1 = WEAPONCATEGORY_MEDIPACK;
  }
  ptNext = ptQTask[33].ptNext;
  v3 = ptNext[1].ptNext;
  if ( !v3 )
    goto LABEL_39;
  ptTail = (struct WeaponType_s *)v3->tQTaskChildren.ptTail;
  if ( ptTail )
  {
    if ( v1 == WEAPONCATEGORY_GRENADE )
    {
      eWeaponCategory = ptTail->eWeaponCategory;
      nRetry = 2;
      while ( 1 )
      {
        v6 = eWeaponCategory - 4;
        if ( v6 )
          eWeaponCategory = v6 == 2 ? WEAPONCATEGORY_SMOKEGRENADE : WEAPONCATEGORY_GRENADE;
        else
          eWeaponCategory = WEAPONCATEGORY_FLASHBANG;
        if ( Weapon_GetNextEnabledWeaponTypeFromCategory(ptNext, eWeaponCategory, nullptr) )
          break;
        if ( nRetry-- == 0 )
          goto LABEL_38;
      }
      v1 = eWeaponCategory;
    }
LABEL_38:
    if ( ptTail->eWeaponCategory != v1 )
LABEL_39:
      ptTail = nullptr;
  }
  NextEnabledWeaponTypeFromCategory = Weapon_GetNextEnabledWeaponTypeFromCategory(ptNext, v1, ptTail);
  if ( NextEnabledWeaponTypeFromCategory
    || (NextEnabledWeaponTypeFromCategory = Weapon_GetNextEnabledWeaponTypeFromCategory(ptNext, v1, nullptr)) != nullptr )
  {
    *(float *)&ptQTask[20].tQTaskChildren.ptTail = (float)NextEnabledWeaponTypeFromCategory->eID;
  }
}

// source: j/0/human/humanplayer.c:3039  [anchor-callee]
void __cdecl HumanPlayer_SelectWeapon(struct QTask_s *ptQTask, int isForceCycle)
{
  enum WeaponOverlayStatus_e v2; // edi
  struct QTask_s *ptNext; // eax
  struct QTask_s *v4; // eax
  struct QTask_s *ptTail; // eax
  int ptPrev; // ebp
  struct WeaponType_s *WeaponTypeFromID; // eax
  int i; // eax
  struct QReference_s *ptHead; // eax
  struct QTask_s *v10; // eax
  struct QTask_s *v11; // edx
  int nID; // ebx
  int v13; // ecx
  bool v14; // zf
  struct QReference_s *v15; // eax
  struct QReference_s *v16; // edi
  int v17; // edi
  struct WeaponType_s *v18; // eax
  struct QTask_s *v19; // ecx
  struct QTask_s *v20; // edi
  enum WeaponOverlayStatus_e v21; // [esp-8h] [ebp-1Ch]
  int v22; // [esp+4h] [ebp-10h]
  int v23; // [esp+8h] [ebp-Ch]

  ptNext = ptQTask[33].ptNext;
  v23 = -1;
  v22 = 0;
  if ( !ptNext )
    return;
  v4 = ptNext[1].ptNext;
  if ( v4 )
  {
    ptTail = v4->tQTaskChildren.ptTail;
    if ( ptTail )
      v23 = (int)ptTail[3].tQTaskRefList.ptTail;
  }
  v21 = v2;
  ptPrev = (__int64)*(float *)&ptQTask[20].tQTaskChildren.ptTail;
  WeaponTypeFromID = WeaponType_GetWeaponTypeFromID(ptPrev);
  if ( WeaponTypeFromID )
  {
    if ( Weapon_IsWeaponSelectable(ptQTask[33].ptNext, WeaponTypeFromID->zWeaponScriptID) == false )
    {
      ptPrev = -1;
      goto LABEL_12;
    }
    for ( i = 0; i < HumanPlayer_tWeaponCycle.nID; ++i )
    {
      if ( HumanPlayer_tWeaponCycle.anID[i] == ptPrev )
        ptQTask[76].tQTaskRefList.ptTail = (struct QReference_s *)i;
    }
  }
  if ( ptPrev != -1 )
    goto LABEL_42;
LABEL_12:
  if ( ptQTask[76].tQTaskRefList.ptTail == (struct QReference_s *)-1
    || isForceCycle
    || *(float *)&ptQTask[21].tQTaskRefList.ptHead != 0.0 && *(float *)&ptQTask[15].tQTaskChildren.ptHead == 0.0 )
  {
    v22 = 1;
  }
  if ( *(float *)&ptQTask[21].tQTaskRefList.ptMiddle != 0.0 && *(float *)&ptQTask[15].tQTaskChildren.ptMiddle == 0.0 )
    --v22;
  if ( !v22 )
    goto LABEL_42;
  ptHead = ptQTask[86].tQTaskRefList.ptHead;
  if ( !ptHead )
  {
    v10 = ptQTask[33].ptNext[1].ptNext;
    if ( v10 && (v11 = v10->tQTaskChildren.ptTail) != nullptr )
    {
      ptQTask[76].tQTaskRefList.ptTail = nullptr;
      nID = HumanPlayer_tWeaponCycle.nID;
      v13 = 0;
      v14 = HumanPlayer_tWeaponCycle.nID == 0;
      if ( HumanPlayer_tWeaponCycle.nID <= 0 )
        goto LABEL_32;
      do
      {
        v15 = ptQTask[76].tQTaskRefList.ptTail;
        if ( (struct QReference_s *)HumanPlayer_tWeaponCycle.anID[(_DWORD)v15] == v11[3].tQTaskRefList.ptTail )
          break;
        ptQTask[76].tQTaskRefList.ptTail = (struct QReference_s *)((char *)&v15->ptNext + 1);
        nID = HumanPlayer_tWeaponCycle.nID;
        ++v13;
      }
      while ( v13 < HumanPlayer_tWeaponCycle.nID );
    }
    else
    {
      nID = HumanPlayer_tWeaponCycle.nID;
    }
    v14 = nID == 0;
LABEL_32:
    if ( !v14 )
    {
      while ( 1 )
      {
        v16 = (struct QReference_s *)((char *)ptQTask[76].tQTaskRefList.ptTail + v22);
        ptQTask[76].tQTaskRefList.ptTail = v16;
        --nID;
        if ( (int)v16 < HumanPlayer_tWeaponCycle.nID )
        {
          if ( (int)v16 < 0 )
            ptQTask[76].tQTaskRefList.ptTail = (struct QReference_s *)(HumanPlayer_tWeaponCycle.nID - 1);
        }
        else
        {
          ptQTask[76].tQTaskRefList.ptTail = nullptr;
        }
        v17 = HumanPlayer_tWeaponCycle.anID[(int)ptQTask[76].tQTaskRefList.ptTail];
        v18 = WeaponType_GetWeaponTypeFromID(v17);
        if ( v18 )
        {
          if ( Weapon_IsWeaponSelectable(ptQTask[33].ptNext, v18->zWeaponScriptID) )
            break;
        }
        if ( !nID )
          goto LABEL_42;
      }
      ptPrev = v17;
    }
    goto LABEL_42;
  }
  ptPrev = (int)ptHead[12].ptPrev;
  ptQTask[86].tQTaskRefList.ptHead = nullptr;
LABEL_42:
  if ( ptPrev != v23 )
  {
    if ( WeaponType_GetWeaponTypeFromID(ptPrev) )
    {
      v20 = ptQTask[33].ptNext;
      ptQTask[76].ptParent = (struct QTask_s *)ptPrev;
      ptQTask[86].tQTaskRefList.ptHead = nullptr;
      Weapon_SetOverlayStatus(v19, v21, 0, (int)v20);
    }
  }
}

// source: j/0/human/humanplayer.c:3229  [anchor-mhash]
void __cdecl HumanPlayer_UpdateDamageFlash(struct QTask_s *ptQTask)
{
  float *p_ptParent; // ecx
  int v2; // edx
  double v3; // st7

  p_ptParent = (float *)&ptQTask[79].ptParent;
  v2 = 4;
  do
  {
    if ( *p_ptParent != 0.0 )
    {
      v3 = *p_ptParent - 0.02222222276031971;
      *p_ptParent = v3;
      if ( v3 < 0.0 )
        *p_ptParent = 0.0;
    }
    ++p_ptParent;
    --v2;
  }
  while ( v2 );
}

// source: j/0/human/humanplayer.c:3260  [anchor-mhash]
void __cdecl HumanPlayer_UpdateFlashBangFlash(struct QTask_s *ptQTask)
{
  double v1; // st7
  double v2; // st7

  if ( *(float *)&ptQTask[80].tQTaskChildren.ptHead != 0.0 )
  {
    v1 = *(float *)&ptQTask[80].tQTaskChildren.ptHead;
    if ( v1 <= 1.0 )
      v2 = v1 - 0.008333333767950535;
    else
      v2 = v1 - 0.01666666753590107;
    *(float *)&ptQTask[80].tQTaskChildren.ptHead = v2;
    if ( *(float *)&ptQTask[80].tQTaskChildren.ptHead < 0.0 )
      ptQTask[80].tQTaskChildren.ptHead = nullptr;
  }
}

// source: j/0/human/humanplayer.c:3292  [size]
void __cdecl HumanPlayer_UpdateElectricDamage(struct QTask_s *ptQTask)
{
  struct QTask_s *ptMiddle; // eax

  ptMiddle = ptQTask[80].tQTaskChildren.ptMiddle;
  if ( ptMiddle )
    ptQTask[80].tQTaskChildren.ptMiddle = (struct QTask_s *)((char *)ptMiddle - 1);
}

// source: j/0/human/humanplayer.c:3312  [size]
struct QTask_s *__cdecl HumanPlayer_LockAction(struct QTask_s *ptQTask)
{
  LOBYTE(ptQTask[76].tQTaskRefList.ptMiddle) = 1;
  return ptQTask;
}

// source: j/0/human/humanplayer.c:3328  [size]
struct QTask_s *__cdecl HumanPlayer_UnlockAction(struct QTask_s *ptQTask)
{
  LOBYTE(ptQTask[76].tQTaskRefList.ptMiddle) = 0;
  return ptQTask;
}

// source: j/0/human/humanplayer.c:3344  [size]
struct QTask_s *__cdecl HumanPlayer_DisableProgressBar(struct QTask_s *ptQTask)
{
  LOBYTE(ptQTask[78].ptPrev) = 0;
  return ptQTask;
}

// source: j/0/human/humanplayer.c:3360  [size]
struct QTask_s *__cdecl HumanPlayer_EnableProgressBar(struct QTask_s *ptQTask)
{
  LOBYTE(ptQTask[78].ptPrev) = 1;
  return ptQTask;
}

// source: j/0/human/humanplayer.c:3376  [anchor-caller]
void __cdecl HumanPlayer_InitActivate(struct QTask_s *ptQTask, int eHumanActivate)
{
  struct QTask_s *ptTail; // eax
  struct QReference_s **p_ptMiddle; // esi
  struct QTask_s *ptHead; // edi
  struct QReference_s *v5; // eax
  void (__cdecl *v6)(struct QReference_s **, struct QTask_s *); // eax
  struct QReference_s *v7; // eax
  struct QTask_s *v8; // eax
  struct QReference_s *v9; // eax
  struct QTask_s *pxObject; // edi
  struct QReference_s *v11; // eax
  struct QReference_s *v12; // eax
  struct QTask_s *v13; // ecx
  void (__cdecl *v14)(struct QReference_s **, struct QTask_s *); // eax
  struct QReference_s *v15; // ecx
  struct QTask_s *v16; // eax
  void (__cdecl *v17)(struct QReference_s **, struct QTask_s *); // eax
  struct QReference_s *v18; // edx
  struct QTask_s *v19; // eax
  void (__cdecl *v20)(struct QReference_s **, struct QTask_s *); // eax
  struct QReference_s *v21; // eax
  struct QTask_s *ptNext; // eax
  void (__cdecl *v23)(struct QReference_s **, struct QTask_s *); // eax
  struct QReference_s *v24; // ecx
  struct QTask_s *ptPrev; // eax
  void (__cdecl *v26)(struct QReference_s **, struct QTask_s *); // eax
  struct QReference_s *v27; // edx
  struct QTask_s *v28; // eax
  void (__cdecl *v29)(struct QReference_s **, struct QTask_s *); // eax
  struct QReference_s *v30; // eax
  struct QTask_s *v31; // eax
  void (__cdecl *v32)(struct QReference_s **, struct QTask_s *); // eax
  struct QReference_s *v33; // ecx
  struct QTask_s *v34; // eax
  struct QTask_s *v35; // esi
  struct QReference_s *v36; // eax
  void *v37; // edi

  ptTail = ptQTask[46].tQTaskChildren.ptTail;
  p_ptMiddle = &ptQTask[30].tQTaskRefList.ptMiddle;
  if ( ptTail )
    ptHead = ptTail->tQTaskChildren.ptHead;
  else
    ptHead = nullptr;
  v5 = ptQTask[46].tQTaskRefList.ptHead;
  if ( v5 )
  {
    QReference_Delete(v5, &QTask_tQTaskRefPool);
    ptQTask[46].tQTaskRefList.ptHead = nullptr;
  }
  if ( ptHead )
    ptQTask[46].tQTaskRefList.ptHead = QTask_NewQTaskRef(ptHead);
  LOBYTE(ptQTask[46].tQTaskRefList.ptMiddle) = 1;
  ptQTask[46].tQTaskRefList.ptTail = nullptr;
  switch ( eHumanActivate )
  {
    case 1:
      v9 = ptQTask[46].tQTaskRefList.ptHead;
      pxObject = nullptr;
      if ( v9 )
        pxObject = (struct QTask_s *)v9->pxObject;
      if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
      {
        if ( *(float *)&ptQTask[13].tQTaskRefList.ptTail == 0.0 )
          HumanPlayer_SendActivateMessage(pxObject, 1, 1);
      }
      else
      {
        Switch_Pressed(pxObject, 0);
      }
      goto LABEL_18;
    case 2:
      v12 = ptQTask[46].tQTaskRefList.ptHead;
      v13 = nullptr;
      if ( v12 )
        v13 = (struct QTask_s *)v12->pxObject;
      if ( BYTE2(v13[23].tQTaskChildren.ptMiddle) )
      {
        if ( Door_IsPickable(v13) )
        {
          v14 = *((void (__cdecl **)(struct QReference_s **, struct QTask_s *))&ptQTask[30].ptParent->ptNext
                + (int)ptQTask[31].ptPrev);
          if ( v14 )
            v14(p_ptMiddle, ptQTask);
          v15 = ptQTask[30].tQTaskRefList.ptTail;
          ptQTask[31].ptNext = ptQTask[31].ptPrev;
          ptQTask[31].ptPrev = (struct QTask_s *)38;
          v16 = (struct QTask_s *)v15[12].pxObject;
          ptQTask[31].tQTaskChildren.ptHead = v16;
          ((void (__cdecl *)(struct QReference_s **, struct QTask_s *))v16)(p_ptMiddle, ptQTask);
        }
      }
      else
      {
        if ( *(float *)&ptQTask[13].tQTaskRefList.ptTail == 0.0 )
        {
          if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
          {
            if ( !Door_GetDoorStatus(v13) || Door_GetDoorStatus(v13) == 1 )
              HumanPlayer_SendActivateMessage(v13, 2, 1);
          }
          else
          {
            Door_ToggleOpenDoorEx(v13, (struct real64x3_t *)&ptQTask[1]);
            Human_SendDoorAIEvent(v13, ptQTask);
          }
        }
LABEL_18:
        v11 = ptQTask[46].tQTaskRefList.ptHead;
LABEL_19:
        LOBYTE(ptQTask[46].tQTaskRefList.ptMiddle) = 0;
        BYTE1(ptQTask[46].tQTaskRefList.ptMiddle) = 1;
        if ( v11 )
        {
          QReference_Delete(v11, &QTask_tQTaskRefPool);
          ptQTask[46].tQTaskRefList.ptHead = nullptr;
        }
      }
      break;
    case 3:
      if ( *(float *)&ptQTask[13].tQTaskRefList.ptTail != 0.0 )
        goto LABEL_18;
      v20 = *((void (__cdecl **)(struct QReference_s **, struct QTask_s *))&ptQTask[30].ptParent->ptNext
            + (int)ptQTask[31].ptPrev);
      if ( v20 )
        v20(p_ptMiddle, ptQTask);
      v21 = ptQTask[30].tQTaskRefList.ptTail;
      ptQTask[31].ptNext = ptQTask[31].ptPrev;
      ptQTask[31].ptPrev = (struct QTask_s *)39;
      ptNext = (struct QTask_s *)v21[13].ptNext;
      ptQTask[31].tQTaskChildren.ptHead = ptNext;
      ((void (__cdecl *)(struct QReference_s **, struct QTask_s *))ptNext)(p_ptMiddle, ptQTask);
      break;
    case 4:
      if ( *(float *)&ptQTask[13].tQTaskRefList.ptTail != 0.0 )
        goto LABEL_18;
      v23 = *((void (__cdecl **)(struct QReference_s **, struct QTask_s *))&ptQTask[30].ptParent->ptNext
            + (int)ptQTask[31].ptPrev);
      if ( v23 )
        v23(p_ptMiddle, ptQTask);
      v24 = ptQTask[30].tQTaskRefList.ptTail;
      ptQTask[31].ptNext = ptQTask[31].ptPrev;
      ptQTask[31].ptPrev = (struct QTask_s *)40;
      ptPrev = (struct QTask_s *)v24[13].ptPrev;
      ptQTask[31].tQTaskChildren.ptHead = ptPrev;
      ((void (__cdecl *)(struct QReference_s **, struct QTask_s *))ptPrev)(p_ptMiddle, ptQTask);
      break;
    case 5:
      if ( *(float *)&ptQTask[13].tQTaskRefList.ptTail != 0.0 )
        goto LABEL_18;
      v17 = *((void (__cdecl **)(struct QReference_s **, struct QTask_s *))&ptQTask[30].ptParent->ptNext
            + (int)ptQTask[31].ptPrev);
      if ( v17 )
        v17(p_ptMiddle, ptQTask);
      v18 = ptQTask[30].tQTaskRefList.ptTail;
      ptQTask[31].ptNext = ptQTask[31].ptPrev;
      ptQTask[31].ptPrev = (struct QTask_s *)41;
      v19 = (struct QTask_s *)v18[13].pxObject;
      ptQTask[31].tQTaskChildren.ptHead = v19;
      ((void (__cdecl *)(struct QReference_s **, struct QTask_s *))v19)(p_ptMiddle, ptQTask);
      break;
    case 7:
      v11 = ptQTask[46].tQTaskRefList.ptHead;
      if ( *(float *)&ptQTask[13].tQTaskRefList.ptTail != 0.0 )
        goto LABEL_19;
      v35 = nullptr;
      if ( v11 )
        v35 = (struct QTask_s *)v11->pxObject;
      if ( Wire_IsSliding(v35) )
        LOBYTE(ptQTask[79].tQTaskChildren.ptHead) = 1;
      else
        HIBYTE(ptQTask[78].ptParent) = 1;
      break;
    case 8:
      if ( *(float *)&ptQTask[13].tQTaskRefList.ptTail != 0.0 )
        goto LABEL_18;
      if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
      {
        v36 = ptQTask[46].tQTaskRefList.ptHead;
        v37 = nullptr;
        if ( v36 )
          v37 = v36->pxObject;
        HumanPlayer_SendActivateMessage((struct QTask_s *)v37, 8, *((_DWORD *)v37 + 83));
      }
      LOBYTE(ptQTask[78].tQTaskChildren.ptTail) = 1;
      break;
    case 9:
      if ( *(float *)&ptQTask[13].tQTaskRefList.ptTail != 0.0 )
        goto LABEL_18;
      LOBYTE(ptQTask[78].ptParent) = 1;
      break;
    case 10:
      if ( *(float *)&ptQTask[13].tQTaskRefList.ptTail != 0.0 )
        goto LABEL_18;
      v26 = *((void (__cdecl **)(struct QReference_s **, struct QTask_s *))&ptQTask[30].ptParent->ptNext
            + (int)ptQTask[31].ptPrev);
      if ( v26 )
        v26(p_ptMiddle, ptQTask);
      v27 = ptQTask[30].tQTaskRefList.ptTail;
      ptQTask[31].ptNext = ptQTask[31].ptPrev;
      ptQTask[31].ptPrev = (struct QTask_s *)42;
      v28 = (struct QTask_s *)v27[14].ptNext;
      ptQTask[31].tQTaskChildren.ptHead = v28;
      ((void (__cdecl *)(struct QReference_s **, struct QTask_s *))v28)(p_ptMiddle, ptQTask);
      break;
    case 11:
      v29 = *((void (__cdecl **)(struct QReference_s **, struct QTask_s *))&ptQTask[30].ptParent->ptNext
            + (int)ptQTask[31].ptPrev);
      if ( v29 )
        v29(p_ptMiddle, ptQTask);
      v30 = ptQTask[30].tQTaskRefList.ptTail;
      ptQTask[31].ptNext = ptQTask[31].ptPrev;
      ptQTask[31].ptPrev = (struct QTask_s *)43;
      v31 = (struct QTask_s *)v30[14].ptPrev;
      ptQTask[31].tQTaskChildren.ptHead = v31;
      ((void (__cdecl *)(struct QReference_s **, struct QTask_s *))v31)(p_ptMiddle, ptQTask);
      return;
    case 12:
      if ( *(float *)&ptQTask[13].tQTaskRefList.ptTail != 0.0 )
        goto LABEL_18;
      v32 = *((void (__cdecl **)(struct QReference_s **, struct QTask_s *))&ptQTask[30].ptParent->ptNext
            + (int)ptQTask[31].ptPrev);
      if ( v32 )
        v32(p_ptMiddle, ptQTask);
      v33 = ptQTask[30].tQTaskRefList.ptTail;
      ptQTask[31].ptNext = ptQTask[31].ptPrev;
      ptQTask[31].ptPrev = (struct QTask_s *)44;
      v34 = (struct QTask_s *)v33[14].pxObject;
      ptQTask[31].tQTaskChildren.ptHead = v34;
      ((void (__cdecl *)(struct QReference_s **, struct QTask_s *))v34)(p_ptMiddle, ptQTask);
      break;
    case 13:
      v6 = *((void (__cdecl **)(struct QReference_s **, struct QTask_s *))&ptQTask[30].ptParent->ptNext
           + (int)ptQTask[31].ptPrev);
      if ( v6 )
        v6(p_ptMiddle, ptQTask);
      v7 = ptQTask[30].tQTaskRefList.ptTail;
      ptQTask[31].ptNext = ptQTask[31].ptPrev;
      ptQTask[31].ptPrev = (struct QTask_s *)108;
      v8 = (struct QTask_s *)v7[36].ptNext;
      ptQTask[31].tQTaskChildren.ptHead = v8;
      ((void (__cdecl *)(struct QReference_s **, struct QTask_s *))v8)(p_ptMiddle, ptQTask);
      return;
    default:
      return;
  }
}

// source: j/0/human/humanplayer.c:3600  [anchor-mhash]
void __cdecl HumanPlayer_ClimbLadder(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s *pxObject; };
    struct { char igi2_o1[4]; float pvAlpha; };
    struct { char igi2_o2[8]; _BYTE ptSource[56]; };
    struct { char igi2_o3[64]; struct real64x3_t ptPos; };
    char igi2_extent[88];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v1; // ebp
  struct QReference_s *ptHead; // ecx
  struct QTask_s *v3; // edi
  bool v4; // zf
  double vZ; // st6
  char ptMiddle; // al
  struct QTask_s *v7; // edi
  double v8; // st6
  struct QTask_s *ptTail; // ecx
  struct QTask_s *v10; // eax
  void (__cdecl *v11)(struct QReference_s **, struct QTask_s *); // eax
  struct QReference_s *v12; // ecx
  struct QTask_s *ptPrev; // eax
  void (__cdecl *v14)(struct QReference_s **, struct QTask_s *); // eax
  struct QReference_s *v15; // eax
  struct QTask_s *v16; // edx
  int v17; // eax
  void (__cdecl *v18)(struct QReference_s **, struct QTask_s *); // eax
  struct QReference_s *v19; // eax

  v1 = ptQTask;
  ptHead = ptQTask[46].tQTaskRefList.ptHead;
  v3 = nullptr;
  igi2_frame.pxObject = nullptr;
  if ( ptHead )
  {
    igi2_frame.pxObject = (struct QTask_s *)ptHead->pxObject;
    v3 = igi2_frame.pxObject;
  }
  if ( LOBYTE(ptQTask[78].tQTaskChildren.ptTail) )
  {
    v4 = HIBYTE(ptQTask[78].tQTaskChildren.ptTail) == 0;
    ptQTask[38].ptPrev = nullptr;
    v1[38].tQTaskChildren.ptHead = nullptr;
    v1[38].tQTaskChildren.ptMiddle = nullptr;
    v1[38].tQTaskChildren.ptTail = nullptr;
    v1[38].tQTaskRefList.ptHead = nullptr;
    v1[38].tQTaskRefList.ptMiddle = nullptr;
    v1[37].tQTaskChildren.ptHead = nullptr;
    v1[37].tQTaskChildren.ptMiddle = nullptr;
    v1[37].tQTaskChildren.ptTail = nullptr;
    if ( !v4 )
    {
      *(_QWORD *)&igi2_frame.ptSource[8] = 0;
      *(_DWORD *)&igi2_frame.ptSource[16] = 1065353216;
      GameFunctions_GetMagicVertex((struct real64x3_t *)&igi2_frame.ptSource[32], v3, 3);
      Human_PopPosition(v1, (struct real64x3_t *)&igi2_frame.ptSource[32]);
      v1[86].tQTaskChildren.ptHead = nullptr;
      v1[86].tQTaskChildren.ptMiddle = nullptr;
      v1[86].tQTaskChildren.ptTail = nullptr;
      Real32x9_GetAngles((struct real32x9_t *)&v3[3].ptPrev, (float *)igi2_frame.ptSource, &igi2_frame.pvAlpha, (float *)&ptQTask);
      *(float *)&ptQTask = *(float *)&ptQTask + 3.1415927410125732;
      Human_PopOrientation(v1, *(float *)&ptQTask);
      v1[78].tQTaskRefList.ptMiddle = (struct QReference_s *)((char *)&v3[8].tQTaskChildren.ptHead[-1].ptParent + 2);
      Human_MoveFree(v1, -9830.400390625, (struct real32x3_t *)&igi2_frame.ptSource[8], true);
      goto LABEL_19;
    }
    qmemcpy(&igi2_frame.ptSource[32], &v1[1], 0x18u);
    GameFunctions_GetMagicVertex(&igi2_frame.ptPos, igi2_frame.pxObject, 3);
    GameFunctions_GetMagicVertex((struct real64x3_t *)&igi2_frame.ptSource[8], igi2_frame.pxObject, 2);
    if ( *(double *)&igi2_frame.ptSource[24] <= *(double *)&igi2_frame.ptSource[48] )
    {
      if ( igi2_frame.ptPos.vZ >= *(double *)&igi2_frame.ptSource[48] )
        vZ = *(double *)&igi2_frame.ptSource[48];
      else
        vZ = igi2_frame.ptPos.vZ;
    }
    else
    {
      vZ = *(double *)&igi2_frame.ptSource[24];
    }
    *(_QWORD *)igi2_frame.ptSource = (__int64)((vZ - *(double *)&igi2_frame.ptSource[24]) * 0.0008138020509957453);
    ptMiddle = (char)v1[80].tQTaskRefList.ptMiddle;
    v7 = *(struct QTask_s **)igi2_frame.ptSource;
    ptQTask = *(struct QTask_s **)igi2_frame.ptSource;
    if ( ptMiddle )
    {
      v7 = (struct QTask_s *)(*(_DWORD *)igi2_frame.ptSource + 1);
      ptQTask = (struct QTask_s *)(*(_DWORD *)igi2_frame.ptSource + 1);
    }
    if ( (int)v7 >= 0 )
    {
      if ( (int)&igi2_frame.pxObject[8].tQTaskChildren.ptHead[-1].ptParent + 2 >= (int)v7 )
      {
LABEL_18:
        v8 = (double)(int)ptQTask / (double)(int)igi2_frame.pxObject[8].tQTaskChildren.ptHead;
        *(double *)&igi2_frame.ptSource[32] = (igi2_frame.ptPos.vX - *(double *)&igi2_frame.ptSource[8]) * v8 + *(double *)&igi2_frame.ptSource[8];
        *(double *)&igi2_frame.ptSource[40] = (igi2_frame.ptPos.vY - *(double *)&igi2_frame.ptSource[16]) * v8 + *(double *)&igi2_frame.ptSource[16];
        *(double *)&igi2_frame.ptSource[48] = (igi2_frame.ptPos.vZ - *(double *)&igi2_frame.ptSource[24]) * v8 + *(double *)&igi2_frame.ptSource[24];
        Human_PopPosition(v1, (struct real64x3_t *)&igi2_frame.ptSource[32]);
        v1[86].tQTaskChildren.ptHead = nullptr;
        v1[86].tQTaskChildren.ptMiddle = nullptr;
        v1[86].tQTaskChildren.ptTail = nullptr;
        Real32x9_GetAngles((struct real32x9_t *)&igi2_frame.pxObject[3].ptPrev, (float *)igi2_frame.ptSource, &igi2_frame.pvAlpha, (float *)&ptQTask);
        *(float *)&ptQTask = *(float *)&ptQTask + 3.1415927410125732;
        Human_PopOrientation(v1, *(float *)&ptQTask);
        v1[78].tQTaskRefList.ptMiddle = (struct QReference_s *)v7;
        v3 = igi2_frame.pxObject;
LABEL_19:
        ptTail = v1[33].tQTaskChildren.ptTail;
        v1[38].ptPrev = nullptr;
        v1[38].tQTaskChildren.ptHead = nullptr;
        v1[38].tQTaskChildren.ptMiddle = nullptr;
        v1[38].tQTaskChildren.ptTail = nullptr;
        v1[38].tQTaskRefList.ptHead = nullptr;
        v1[38].tQTaskRefList.ptMiddle = nullptr;
        v1[37].tQTaskChildren.ptHead = nullptr;
        v1[37].tQTaskChildren.ptMiddle = nullptr;
        v1[37].tQTaskChildren.ptTail = nullptr;
        LOBYTE(v1[78].tQTaskChildren.ptTail) = 0;
        BYTE1(v1[78].tQTaskChildren.ptTail) = 1;
        LOBYTE(v1[46].tQTaskRefList.ptMiddle) = 1;
        LOBYTE(v1[34].tQTaskChildren.ptMiddle) = 1;
        LOBYTE(ptTail[12].tQTaskRefList.ptTail) = 1;
        v10 = v1[33].tQTaskChildren.ptTail;
        *(_DWORD *)&v10[11].eQTaskType = 0;
        v10[12].ptNext = nullptr;
        v10[12].ptPrev = nullptr;
        v10[12].tQTaskRefList.ptHead = nullptr;
        v10[12].tQTaskChildren.ptHead = nullptr;
        v10[12].tQTaskChildren.ptMiddle = nullptr;
        v10[12].tQTaskChildren.ptTail = nullptr;
        v10[12].tQTaskRefList.ptMiddle = nullptr;
        LOBYTE(v1[40].tQTaskChildren.ptMiddle) = 1;
        v1[48].ptNext = (struct QTask_s *)1;
        *(_DWORD *)&v1[47].eQTaskType = 0;
        Human_SnapFromGround(v1);
        BYTE1(v1[36].tQTaskChildren.ptTail) = 1;
        v1[33].tQTaskRefList.ptHead = (struct QReference_s *)3;
        LOBYTE(v1[76].tQTaskRefList.ptMiddle) = 1;
        v1[78].tQTaskRefList.ptHead = (struct QReference_s *)v3[8].tQTaskChildren.ptHead;
        Human_AttachToTask(v1, v3, (struct real64x3_t *)&v1[1], (struct real32x9_t *)&v1[3].ptPrev);
        if ( HIBYTE(v1[78].tQTaskChildren.ptTail) )
        {
          v11 = *((void (__cdecl **)(struct QReference_s **, struct QTask_s *))&v1[30].ptParent->ptNext
                + (int)v1[31].ptPrev);
          if ( v11 )
            v11(&v1[30].tQTaskRefList.ptMiddle, v1);
          v12 = v1[30].tQTaskRefList.ptTail;
          v1[31].ptNext = v1[31].ptPrev;
          v1[31].ptPrev = (struct QTask_s *)46;
          ptPrev = (struct QTask_s *)v12[15].ptPrev;
        }
        else
        {
          v14 = *((void (__cdecl **)(struct QReference_s **, struct QTask_s *))&v1[30].ptParent->ptNext
                + (int)v1[31].ptPrev);
          if ( v14 )
            v14(&v1[30].tQTaskRefList.ptMiddle, v1);
          v15 = v1[30].tQTaskRefList.ptTail;
          v1[31].ptNext = v1[31].ptPrev;
          v1[31].ptPrev = (struct QTask_s *)45;
          ptPrev = (struct QTask_s *)v15[15].ptNext;
        }
LABEL_31:
        v1[31].tQTaskChildren.ptHead = ptPrev;
        ((void (__cdecl *)(struct QReference_s **, struct QTask_s *))ptPrev)(&v1[30].tQTaskRefList.ptMiddle, v1);
        return;
      }
      v7 = (struct QTask_s *)((char *)igi2_frame.pxObject[8].tQTaskChildren.ptHead - 6);
    }
    else
    {
      v7 = nullptr;
    }
    ptQTask = v7;
    goto LABEL_18;
  }
  if ( BYTE2(ptQTask[78].tQTaskChildren.ptTail) )
  {
    v16 = ptQTask[33].tQTaskChildren.ptTail;
    BYTE2(ptQTask[78].tQTaskChildren.ptTail) = 0;
    BYTE1(v1[78].tQTaskChildren.ptTail) = 0;
    LOBYTE(v1[46].tQTaskRefList.ptMiddle) = 0;
    BYTE1(v1[46].tQTaskRefList.ptMiddle) = 1;
    LOBYTE(v1[34].tQTaskChildren.ptMiddle) = 0;
    LOBYTE(v16[12].tQTaskRefList.ptTail) = 0;
    v1[48].ptNext = nullptr;
    *(_DWORD *)&v1[47].eQTaskType = 1;
    LOBYTE(v1[40].tQTaskChildren.ptMiddle) = 0;
    BYTE1(v1[36].tQTaskChildren.ptTail) = 0;
    v1[33].tQTaskRefList.ptHead = (struct QReference_s *)1;
    LOBYTE(v1[76].tQTaskRefList.ptMiddle) = 0;
    HumanAnim_SetAnimationAndTimeFromState(v1, 0, 0, 0.0);
    v17 = *(_DWORD *)&v1[30].eQTaskType;
    v1[44].tQTaskRefList.ptTail = nullptr;
    v1[48].ptNext = nullptr;
    *(_DWORD *)&v1[47].eQTaskType = 1;
    if ( (v17 & 0x20000) != 0 )
    {
      v18 = *((void (__cdecl **)(struct QReference_s **, struct QTask_s *))&v1[30].ptParent->ptNext + (int)v1[31].ptPrev);
      if ( v18 )
        v18(&v1[30].tQTaskRefList.ptMiddle, v1);
      v19 = v1[30].tQTaskRefList.ptTail;
      v1[31].ptNext = v1[31].ptPrev;
      v1[31].ptPrev = (struct QTask_s *)55;
      ptPrev = (struct QTask_s *)v19[18].ptPrev;
      goto LABEL_31;
    }
  }
}

// source: j/0/human/humanplayer.c:3800  [anchor-mhash]
void __cdecl HumanPlayer_ClimbFence(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vGamma; };
    struct { char igi2_o1[4]; float vGammaOffset; };
    struct { char igi2_o2[8]; float vBeta; };
    struct { char igi2_o3[12]; float vAlpha; };
    struct { char igi2_o4[16]; struct real64x3_t tPos; };
    struct { char igi2_o5[40]; struct real64x3_t Real64x3_Rotate_tTemp; };
    struct { char igi2_o6[64]; struct HumanAIEventContext_t tContext; };
    char igi2_extent[128];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QReference_s *ptHead; // eax
  double *pxObject; // edx
  double v3; // st7
  double v4; // st7
  struct real32x9_t *v5; // ecx
  struct QTask_s *ptTail; // eax
  void (__cdecl *v7)(struct QReference_s **, struct QTask_s *); // eax
  struct QReference_s *v8; // ecx
  struct QTask_s *ptPrev; // eax
  struct QReference_s *v10; // eax
  void (__cdecl *v11)(struct QReference_s **, struct QTask_s *); // eax
  struct QReference_s *v12; // ecx
  struct QReference_s *v13; // edx

  ptHead = ptQTask[46].tQTaskRefList.ptHead;
  pxObject = nullptr;
  if ( ptHead )
    pxObject = (double *)ptHead->pxObject;
  if ( LOBYTE(ptQTask[78].ptParent) )
  {
    v3 = *(double *)&ptQTask[1].ptNext - pxObject[5];
    LODWORD(igi2_frame.vGamma) = (char *)pxObject + 124;
    igi2_frame.vGammaOffset = 0.0;
    igi2_frame.tPos.vX = v3;
    igi2_frame.tPos.vY = *(double *)&ptQTask[1].tQTaskChildren.ptHead - pxObject[6];
    igi2_frame.tPos.vZ = *(double *)&ptQTask[1].tQTaskChildren.ptTail - pxObject[7];
    v4 = *((float *)pxObject + 34) * igi2_frame.tPos.vY + *((float *)pxObject + 37) * igi2_frame.tPos.vZ + *((float *)pxObject + 31) * v3;
    if ( *((float *)pxObject + 35) * igi2_frame.tPos.vY + *((float *)pxObject + 38) * igi2_frame.tPos.vZ + *((float *)pxObject + 32) * igi2_frame.tPos.vX >= 0.0 )
      igi2_frame.vGammaOffset = 3.1415927410125732;
    igi2_frame.Real64x3_Rotate_tTemp.vX = (*((float *)pxObject + 33) + *((float *)pxObject + 32)) * 0.0
                             + *((float *)pxObject + 31) * v4;
    igi2_frame.Real64x3_Rotate_tTemp.vY = (*((float *)pxObject + 36) + *((float *)pxObject + 35)) * 0.0
                             + *((float *)pxObject + 34) * v4;
    igi2_frame.Real64x3_Rotate_tTemp.vZ = (*((float *)pxObject + 39) + *((float *)pxObject + 38)) * 0.0
                             + *((float *)pxObject + 37) * v4;
    qmemcpy(&igi2_frame.tPos, &igi2_frame.Real64x3_Rotate_tTemp, sizeof(igi2_frame.tPos));
    igi2_frame.tPos.vX = igi2_frame.Real64x3_Rotate_tTemp.vX + pxObject[5];
    igi2_frame.tPos.vY = igi2_frame.tPos.vY + pxObject[6];
    igi2_frame.tPos.vZ = igi2_frame.tPos.vZ + pxObject[7];
    Human_PopPosition(ptQTask, &igi2_frame.tPos);
    v5 = (struct real32x9_t *)LODWORD(igi2_frame.vGamma);
    ptQTask[86].tQTaskChildren.ptHead = nullptr;
    ptQTask[86].tQTaskChildren.ptMiddle = nullptr;
    ptQTask[86].tQTaskChildren.ptTail = nullptr;
    Real32x9_GetAngles(v5, &igi2_frame.vAlpha, &igi2_frame.vBeta, &igi2_frame.vGamma);
    igi2_frame.vGamma = igi2_frame.vGamma + igi2_frame.vGammaOffset;
    Human_PopOrientation(ptQTask, igi2_frame.vGamma);
    ptQTask[38].ptPrev = nullptr;
    ptQTask[38].tQTaskChildren.ptHead = nullptr;
    ptQTask[38].tQTaskChildren.ptMiddle = nullptr;
    ptQTask[38].tQTaskChildren.ptTail = nullptr;
    ptQTask[38].tQTaskRefList.ptHead = nullptr;
    ptQTask[38].tQTaskRefList.ptMiddle = nullptr;
    ptQTask[37].tQTaskChildren.ptHead = nullptr;
    ptQTask[37].tQTaskChildren.ptMiddle = nullptr;
    ptQTask[37].tQTaskChildren.ptTail = nullptr;
    LOBYTE(ptQTask[78].ptParent) = 0;
    BYTE1(ptQTask[78].ptParent) = 1;
    LOBYTE(ptQTask[46].tQTaskRefList.ptMiddle) = 1;
    LOBYTE(ptQTask[34].tQTaskChildren.ptMiddle) = 1;
    ptTail = ptQTask[33].tQTaskChildren.ptTail;
    *(_DWORD *)&ptTail[11].eQTaskType = 0;
    ptTail[12].ptNext = nullptr;
    ptTail[12].ptPrev = nullptr;
    ptTail[12].tQTaskRefList.ptHead = nullptr;
    ptTail[12].tQTaskChildren.ptHead = nullptr;
    ptTail[12].tQTaskChildren.ptMiddle = nullptr;
    ptTail[12].tQTaskChildren.ptTail = nullptr;
    ptTail[12].tQTaskRefList.ptMiddle = nullptr;
    LOBYTE(ptQTask[33].tQTaskChildren.ptTail[12].tQTaskRefList.ptTail) = 1;
    LOBYTE(ptQTask[40].tQTaskChildren.ptMiddle) = 1;
    ptQTask[48].ptNext = (struct QTask_s *)1;
    *(_DWORD *)&ptQTask[47].eQTaskType = 0;
    Human_SnapFromGround(ptQTask);
    BYTE1(ptQTask[36].tQTaskChildren.ptTail) = 1;
    ptQTask[33].tQTaskRefList.ptHead = (struct QReference_s *)3;
    LOBYTE(ptQTask[76].tQTaskRefList.ptMiddle) = 1;
    v7 = *((void (__cdecl **)(struct QReference_s **, struct QTask_s *))&ptQTask[30].ptParent->ptNext
         + (int)ptQTask[31].ptPrev);
    if ( v7 )
      v7(&ptQTask[30].tQTaskRefList.ptMiddle, ptQTask);
    v8 = ptQTask[30].tQTaskRefList.ptTail;
    ptQTask[31].ptNext = ptQTask[31].ptPrev;
    ptQTask[31].ptPrev = (struct QTask_s *)49;
    ptPrev = (struct QTask_s *)v8[16].ptPrev;
LABEL_9:
    ptQTask[31].tQTaskChildren.ptHead = ptPrev;
    ((void (__cdecl *)(struct QReference_s **, struct QTask_s *))ptPrev)(&ptQTask[30].tQTaskRefList.ptMiddle, ptQTask);
    return;
  }
  if ( BYTE2(ptQTask[78].ptParent) )
  {
    BYTE2(ptQTask[78].ptParent) = 0;
    BYTE1(ptQTask[78].ptParent) = 0;
    LOBYTE(ptQTask[46].tQTaskRefList.ptMiddle) = 0;
    BYTE1(ptQTask[46].tQTaskRefList.ptMiddle) = 1;
    LOBYTE(ptQTask[34].tQTaskChildren.ptMiddle) = 0;
    LOBYTE(ptQTask[33].tQTaskChildren.ptTail[12].tQTaskRefList.ptTail) = 0;
    *(_DWORD *)&ptQTask[47].eQTaskType = 1;
    ptQTask[33].tQTaskRefList.ptHead = (struct QReference_s *)1;
    v10 = ptQTask[46].tQTaskRefList.ptHead;
    ptQTask[48].ptNext = nullptr;
    LOBYTE(ptQTask[40].tQTaskChildren.ptMiddle) = 0;
    BYTE1(ptQTask[36].tQTaskChildren.ptTail) = 0;
    LOBYTE(ptQTask[76].tQTaskRefList.ptMiddle) = 0;
    if ( v10 )
    {
      QReference_Delete(v10, &QTask_tQTaskRefPool);
      ptQTask[46].tQTaskRefList.ptHead = nullptr;
    }
    HumanAnim_SetAnimationAndTimeFromState(ptQTask, 0, 0, 0.0);
    if ( (*(_DWORD *)&ptQTask[30].eQTaskType & 0x20000) != 0 )
    {
      v11 = *((void (__cdecl **)(struct QReference_s **, struct QTask_s *))&ptQTask[30].ptParent->ptNext
            + (int)ptQTask[31].ptPrev);
      if ( v11 )
        v11(&ptQTask[30].tQTaskRefList.ptMiddle, ptQTask);
      v12 = ptQTask[30].tQTaskRefList.ptTail;
      ptQTask[31].ptNext = ptQTask[31].ptPrev;
      ptQTask[31].ptPrev = (struct QTask_s *)55;
      ptPrev = (struct QTask_s *)v12[18].ptPrev;
      goto LABEL_9;
    }
  }
  else
  {
    v13 = ptQTask[10].tQTaskRefList.ptTail;
    igi2_frame.tContext.eEvent = 12;
    igi2_frame.tContext.eTeam = (int)v13;
    igi2_frame.tContext.bFlags = 1090;
    igi2_frame.tContext.vRadius = 20480.0;
    igi2_frame.tContext.ptPosition = (struct real64x3_t *)&ptQTask[1];
    igi2_frame.tContext.ptReferenceQTask = ptQTask;
    igi2_frame.tContext.ptHumanOriginatorQTask = ptQTask;
    HumanAI_SendEvent(&igi2_frame.tContext);
  }
}

// source: j/0/human/humanplayer.c:3994  [anchor-mhash]
void __cdecl HumanPlayer_ClimbWire(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vGamma; };
    struct { char igi2_o1[4]; struct real32x9_t tOrientation; };
    struct { char igi2_o2[44]; struct real64x3_t Real64x3_RotateInverse_tTemp; };
    struct { char igi2_o3[68]; struct real64x3_t tPos; };
    struct { char igi2_o4[96]; struct real32x3_t tMagicPos0; };
    struct { char igi2_o5[108]; struct real64x3_t tDelta; };
    struct { char igi2_o6[132]; float vBeta; };
    struct { char igi2_o7[136]; float vAlpha; };
    char igi2_extent[140];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QReference_s *ptHead; // eax
  struct QTask_s *pxObject; // ebx
  double v3; // st7
  double v4; // st5
  double v5; // st7
  double v6; // st7
  struct QTask_s *ptTail; // eax
  void (__cdecl *v8)(struct QReference_s **, struct QTask_s *); // eax
  struct QReference_s *v9; // eax
  struct QTask_s *ptPrev; // eax
  bool v11; // dl
  void (__cdecl *v12)(struct QReference_s **, struct QTask_s *); // eax
  struct QReference_s *v13; // ecx
  void (__cdecl *v14)(struct QReference_s **, struct QTask_s *); // eax
  struct QReference_s *v15; // eax

  ptHead = ptQTask[46].tQTaskRefList.ptHead;
  pxObject = nullptr;
  if ( ptHead )
    pxObject = (struct QTask_s *)ptHead->pxObject;
  if ( HIBYTE(ptQTask[78].ptParent) )
  {
    Wire_GetOrientation(&igi2_frame.tOrientation, pxObject);
    v3 = *(double *)&ptQTask[1].ptNext - *(double *)&pxObject[1].ptNext;
    igi2_frame.tDelta.vY = *(double *)&ptQTask[1].tQTaskChildren.ptHead - *(double *)&pxObject[1].tQTaskChildren.ptHead;
    v4 = *(double *)&ptQTask[1].tQTaskChildren.ptTail - *(double *)&pxObject[1].tQTaskChildren.ptTail;
    igi2_frame.Real64x3_RotateInverse_tTemp.vX = igi2_frame.tOrientation.tZ.vX * v4 + igi2_frame.tOrientation.tY.vX * igi2_frame.tDelta.vY + igi2_frame.tOrientation.tX.vX * v3;
    igi2_frame.Real64x3_RotateInverse_tTemp.vY = igi2_frame.tOrientation.tZ.vY * v4 + igi2_frame.tOrientation.tY.vY * igi2_frame.tDelta.vY + igi2_frame.tOrientation.tX.vY * v3;
    igi2_frame.Real64x3_RotateInverse_tTemp.vZ = igi2_frame.tOrientation.tZ.vZ * v4 + igi2_frame.tOrientation.tY.vZ * igi2_frame.tDelta.vY + igi2_frame.tOrientation.tX.vZ * v3;
    qmemcpy(&igi2_frame.tDelta, &igi2_frame.Real64x3_RotateInverse_tTemp, sizeof(igi2_frame.tDelta));
    GameFunctions_GetMagicVertexLocal(&igi2_frame.tMagicPos0, pxObject, 0);
    GameFunctions_GetMagicVertexLocal((struct real32x3_t *)&igi2_frame.tPos, pxObject, 1);
    v5 = igi2_frame.tMagicPos0.vY + 3072.0;
    if ( v5 <= igi2_frame.Real64x3_RotateInverse_tTemp.vY )
    {
      v6 = *((float *)&igi2_frame.tPos.vX + 1) - 3072.0;
      if ( v6 < igi2_frame.Real64x3_RotateInverse_tTemp.vY )
        igi2_frame.tDelta.vY = v6;
    }
    else
    {
      igi2_frame.tDelta.vY = v5;
    }
    igi2_frame.Real64x3_RotateInverse_tTemp.vX = (igi2_frame.tOrientation.tX.vZ + igi2_frame.tOrientation.tX.vX) * 0.0 + igi2_frame.tOrientation.tX.vY * igi2_frame.tDelta.vY;
    igi2_frame.Real64x3_RotateInverse_tTemp.vY = (igi2_frame.tOrientation.tY.vZ + igi2_frame.tOrientation.tY.vX) * 0.0 + igi2_frame.tOrientation.tY.vY * igi2_frame.tDelta.vY;
    igi2_frame.Real64x3_RotateInverse_tTemp.vZ = (igi2_frame.tOrientation.tZ.vZ + igi2_frame.tOrientation.tZ.vX) * 0.0 + igi2_frame.tOrientation.tZ.vY * igi2_frame.tDelta.vY;
    qmemcpy(&igi2_frame.tPos, &igi2_frame.Real64x3_RotateInverse_tTemp, sizeof(igi2_frame.tPos));
    igi2_frame.tPos.vX = igi2_frame.Real64x3_RotateInverse_tTemp.vX + *(double *)&pxObject[1].ptNext;
    igi2_frame.tPos.vY = igi2_frame.tPos.vY + *(double *)&pxObject[1].tQTaskChildren.ptHead;
    igi2_frame.tPos.vZ = igi2_frame.tPos.vZ + *(double *)&pxObject[1].tQTaskChildren.ptTail;
    Human_PopPosition(ptQTask, &igi2_frame.tPos);
    ptQTask[86].tQTaskChildren.ptHead = nullptr;
    ptQTask[86].tQTaskChildren.ptMiddle = nullptr;
    ptQTask[86].tQTaskChildren.ptTail = nullptr;
    ptQTask[38].ptPrev = nullptr;
    ptQTask[38].tQTaskChildren.ptHead = nullptr;
    ptQTask[38].tQTaskChildren.ptMiddle = nullptr;
    ptQTask[38].tQTaskChildren.ptTail = nullptr;
    ptQTask[38].tQTaskRefList.ptHead = nullptr;
    ptQTask[38].tQTaskRefList.ptMiddle = nullptr;
    ptQTask[37].tQTaskChildren.ptHead = nullptr;
    ptQTask[37].tQTaskChildren.ptMiddle = nullptr;
    ptQTask[37].tQTaskChildren.ptTail = nullptr;
    Real32x9_GetAngles(&igi2_frame.tOrientation, &igi2_frame.vAlpha, &igi2_frame.vBeta, &igi2_frame.vGamma);
    if ( igi2_frame.tDelta.vY > 0.0 )
      igi2_frame.vGamma = igi2_frame.vGamma + 3.1415927410125732;
    Human_PopOrientation(ptQTask, igi2_frame.vGamma);
    HIBYTE(ptQTask[78].ptParent) = 0;
    LOBYTE(ptQTask[78].eQTaskType) = 1;
    LOBYTE(ptQTask[46].tQTaskRefList.ptMiddle) = 1;
    LOBYTE(ptQTask[34].tQTaskChildren.ptMiddle) = 1;
    LOBYTE(ptQTask[33].tQTaskChildren.ptTail[12].tQTaskRefList.ptTail) = 1;
    LOBYTE(ptQTask[40].tQTaskChildren.ptMiddle) = 1;
    Human_SnapFromGround(ptQTask);
    ptTail = ptQTask[33].tQTaskChildren.ptTail;
    *(_DWORD *)&ptTail[11].eQTaskType = 0;
    ptTail[12].ptNext = nullptr;
    ptTail[12].ptPrev = nullptr;
    ptTail[12].tQTaskRefList.ptHead = nullptr;
    ptTail[12].tQTaskChildren.ptHead = nullptr;
    ptTail[12].tQTaskChildren.ptMiddle = nullptr;
    ptTail[12].tQTaskChildren.ptTail = nullptr;
    ptTail[12].tQTaskRefList.ptMiddle = nullptr;
    BYTE1(ptQTask[36].tQTaskChildren.ptTail) = 1;
    ptQTask[33].tQTaskRefList.ptHead = (struct QReference_s *)3;
    LOBYTE(ptQTask[76].tQTaskRefList.ptMiddle) = 1;
    ptQTask[48].ptNext = (struct QTask_s *)1;
    *(_DWORD *)&ptQTask[47].eQTaskType = 0;
    v8 = *((void (__cdecl **)(struct QReference_s **, struct QTask_s *))&ptQTask[30].ptParent->ptNext
         + (int)ptQTask[31].ptPrev);
    if ( v8 )
      v8(&ptQTask[30].tQTaskRefList.ptMiddle, ptQTask);
    v9 = ptQTask[30].tQTaskRefList.ptTail;
    ptQTask[31].ptNext = ptQTask[31].ptPrev;
    ptQTask[31].ptPrev = (struct QTask_s *)50;
    ptPrev = (struct QTask_s *)v9[16].pxObject;
LABEL_28:
    ptQTask[31].tQTaskChildren.ptHead = ptPrev;
    ((void (__cdecl *)(struct QReference_s **, struct QTask_s *))ptPrev)(&ptQTask[30].tQTaskRefList.ptMiddle, ptQTask);
    return;
  }
  Wire_GetOrientation(&igi2_frame.tOrientation, pxObject);
  igi2_frame.Real64x3_RotateInverse_tTemp.vY = igi2_frame.tOrientation.tZ.vY
                                  * (*(double *)&ptQTask[1].tQTaskChildren.ptTail
                                   - *(double *)&pxObject[1].tQTaskChildren.ptTail)
                                  + igi2_frame.tOrientation.tY.vY
                                  * (*(double *)&ptQTask[1].tQTaskChildren.ptHead
                                   - *(double *)&pxObject[1].tQTaskChildren.ptHead)
                                  + igi2_frame.tOrientation.tX.vY
                                  * (*(double *)&ptQTask[1].ptNext - *(double *)&pxObject[1].ptNext);
  GameFunctions_GetMagicVertexLocal(&igi2_frame.tMagicPos0, pxObject, 0);
  GameFunctions_GetMagicVertexLocal((struct real32x3_t *)&igi2_frame.tPos, pxObject, 1);
  v11 = igi2_frame.tMagicPos0.vY + 3072.0 > igi2_frame.Real64x3_RotateInverse_tTemp.vY
     || *((float *)&igi2_frame.tPos.vX + 1) - 3072.0 < igi2_frame.Real64x3_RotateInverse_tTemp.vY;
  if ( *(float *)&ptQTask[20].ptNext != 0.0 && *(float *)&ptQTask[13].tQTaskRefList.ptTail == 0.0
    || v11
    || (*(_DWORD *)&ptQTask[30].eQTaskType & 0x20000) != 0 )
  {
    LOBYTE(ptQTask[78].eQTaskType) = 0;
    LOBYTE(ptQTask[46].tQTaskRefList.ptMiddle) = 0;
    BYTE1(ptQTask[46].tQTaskRefList.ptMiddle) = 1;
    LOBYTE(ptQTask[34].tQTaskChildren.ptMiddle) = 0;
    LOBYTE(ptQTask[33].tQTaskChildren.ptTail[12].tQTaskRefList.ptTail) = 0;
    LOBYTE(ptQTask[40].tQTaskChildren.ptMiddle) = 0;
    BYTE1(ptQTask[36].tQTaskChildren.ptTail) = 0;
    ptQTask[33].tQTaskRefList.ptHead = (struct QReference_s *)1;
    LOBYTE(ptQTask[76].tQTaskRefList.ptMiddle) = 0;
    ptQTask[48].ptNext = nullptr;
    *(_DWORD *)&ptQTask[47].eQTaskType = 1;
    LOBYTE(pxObject[9].tQTaskRefList.ptMiddle) = 0;
    if ( (*(_DWORD *)&ptQTask[30].eQTaskType & 0x20000) != 0 )
    {
      v12 = *((void (__cdecl **)(struct QReference_s **, struct QTask_s *))&ptQTask[30].ptParent->ptNext
            + (int)ptQTask[31].ptPrev);
      if ( v12 )
        v12(&ptQTask[30].tQTaskRefList.ptMiddle, ptQTask);
      v13 = ptQTask[30].tQTaskRefList.ptTail;
      ptQTask[31].ptNext = ptQTask[31].ptPrev;
      ptQTask[31].ptPrev = (struct QTask_s *)55;
      ptPrev = (struct QTask_s *)v13[18].ptPrev;
    }
    else
    {
      v14 = *((void (__cdecl **)(struct QReference_s **, struct QTask_s *))&ptQTask[30].ptParent->ptNext
            + (int)ptQTask[31].ptPrev);
      if ( v14 )
        v14(&ptQTask[30].tQTaskRefList.ptMiddle, ptQTask);
      v15 = ptQTask[30].tQTaskRefList.ptTail;
      ptQTask[31].ptNext = ptQTask[31].ptPrev;
      ptQTask[31].ptPrev = (struct QTask_s *)37;
      ptPrev = (struct QTask_s *)v15[12].ptPrev;
    }
    goto LABEL_28;
  }
}

// source: j/0/human/humanplayer.c:4209  [anchor-mhash]
void __cdecl HumanPlayer_SlideWire(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v20; };
    struct { char igi2_o1[28]; float pvBeta; };
    struct { char igi2_o2[32]; struct QTask_s *pxObject; };
    struct { char igi2_o3[36]; struct real64x3_t ptPos; };
    struct { char igi2_o4[60]; struct real64x3_t v24; };
    struct { char igi2_o5[84]; struct real32x9_t ptOrientation; };
    struct { char igi2_o6[124]; struct real64x3_t v26; };
    struct { char igi2_o7[152]; float v27; };
    struct { char igi2_o8[156]; double v28[3]; };
    struct { char igi2_o9[184]; float pvAlpha; };
    char igi2_extent[188];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QReference_s *ptHead; // eax
  struct QTask_s *v2; // ebx
  double v3; // st7
  double v4; // st5
  double v5; // st7
  struct QTask_s *v6; // esi
  double v7; // st7
  double v8; // st6
  double vY; // st2
  long double v10; // st3
  struct QTask_s *ptTail; // eax
  struct QTask_s *v12; // eax
  void (__cdecl *v13)(struct QReference_s **, struct QTask_s *); // eax
  struct QReference_s *v14; // ecx
  struct QTask_s *ptNext; // eax
  bool v16; // cl
  void (__cdecl *v17)(struct QReference_s **, struct QTask_s *); // eax
  struct QReference_s *v18; // eax
  struct QReference_s *v19; // eax

  ptHead = ptQTask[46].tQTaskRefList.ptHead;
  v2 = nullptr;
  igi2_frame.pxObject = nullptr;
  if ( ptHead )
  {
    igi2_frame.pxObject = (struct QTask_s *)ptHead->pxObject;
    v2 = igi2_frame.pxObject;
  }
  if ( LOBYTE(ptQTask[79].tQTaskChildren.ptHead) )
  {
    Wire_GetOrientation(&igi2_frame.ptOrientation, v2);
    v3 = *(double *)&ptQTask[1].ptNext - *(double *)&v2[1].ptNext;
    igi2_frame.v28[1] = *(double *)&ptQTask[1].tQTaskChildren.ptHead - *(double *)&v2[1].tQTaskChildren.ptHead;
    v4 = *(double *)&ptQTask[1].tQTaskChildren.ptTail - *(double *)&v2[1].tQTaskChildren.ptTail;
    igi2_frame.v24.vX = igi2_frame.ptOrientation.tZ.vX * v4 + igi2_frame.ptOrientation.tY.vX * igi2_frame.v28[1] + igi2_frame.ptOrientation.tX.vX * v3;
    igi2_frame.v24.vY = igi2_frame.ptOrientation.tZ.vY * v4 + igi2_frame.ptOrientation.tY.vY * igi2_frame.v28[1] + igi2_frame.ptOrientation.tX.vY * v3;
    igi2_frame.v24.vZ = igi2_frame.ptOrientation.tZ.vZ * v4 + igi2_frame.ptOrientation.tY.vZ * igi2_frame.v28[1] + igi2_frame.ptOrientation.tX.vZ * v3;
    qmemcpy(igi2_frame.v28, &igi2_frame.v24, sizeof(igi2_frame.v28));
    GameFunctions_GetMagicVertexLocal((struct real32x3_t *)&igi2_frame.v26, v2, 0);
    GameFunctions_GetMagicVertexLocal((struct real32x3_t *)&igi2_frame.ptPos, v2, 1);
    v5 = *((float *)&igi2_frame.v26.vX + 1) + 3072.0;
    if ( v5 <= igi2_frame.v24.vY )
    {
      v5 = *((float *)&igi2_frame.ptPos.vX + 1) - 3072.0;
      if ( v5 >= igi2_frame.v24.vY )
        v5 = igi2_frame.v28[1];
    }
    igi2_frame.v24.vX = igi2_frame.ptOrientation.tX.vZ * *(float *)&igi2_frame.v26.vY
           + igi2_frame.ptOrientation.tX.vX * *(float *)&igi2_frame.v26.vX
           + igi2_frame.ptOrientation.tX.vY * v5;
    igi2_frame.v24.vY = igi2_frame.ptOrientation.tY.vZ * *(float *)&igi2_frame.v26.vY
           + igi2_frame.ptOrientation.tY.vX * *(float *)&igi2_frame.v26.vX
           + igi2_frame.ptOrientation.tY.vY * v5;
    igi2_frame.v24.vZ = igi2_frame.ptOrientation.tZ.vZ * *(float *)&igi2_frame.v26.vY
           + igi2_frame.ptOrientation.tZ.vX * *(float *)&igi2_frame.v26.vX
           + igi2_frame.ptOrientation.tZ.vY * v5;
    qmemcpy(&igi2_frame.ptPos, &igi2_frame.v24, sizeof(igi2_frame.ptPos));
    igi2_frame.ptPos.vX = igi2_frame.v24.vX + *(double *)&v2[1].ptNext;
    igi2_frame.ptPos.vY = igi2_frame.ptPos.vY + *(double *)&v2[1].tQTaskChildren.ptHead;
    igi2_frame.ptPos.vZ = igi2_frame.ptPos.vZ + *(double *)&v2[1].tQTaskChildren.ptTail - 3072.0;
    Human_PopPosition(ptQTask, &igi2_frame.ptPos);
    ptQTask[86].tQTaskChildren.ptHead = nullptr;
    ptQTask[86].tQTaskChildren.ptMiddle = nullptr;
    ptQTask[86].tQTaskChildren.ptTail = nullptr;
    Real32x9_GetAngles(&igi2_frame.ptOrientation, &igi2_frame.v27, &igi2_frame.pvAlpha, &igi2_frame.pvBeta);
    v6 = igi2_frame.pxObject;
    GameFunctions_GetMagicVertex(&igi2_frame.v26, igi2_frame.pxObject, 0);
    GameFunctions_GetMagicVertex(&igi2_frame.v24, v6, 1);
    v7 = igi2_frame.v24.vX - igi2_frame.v26.vX;
    igi2_frame.ptPos.vY = igi2_frame.v24.vY - igi2_frame.v26.vY;
    v8 = igi2_frame.v24.vZ - igi2_frame.v26.vZ;
    if ( igi2_frame.v24.vZ - igi2_frame.v26.vZ > 0.0 )
    {
      v7 = -v7;
      igi2_frame.ptPos.vY = -igi2_frame.ptPos.vY;
      v8 = -v8;
      igi2_frame.pvBeta = igi2_frame.pvBeta + 3.1415927410125732;
    }
    igi2_frame.v20 = igi2_frame.pvBeta;
    vY = igi2_frame.ptPos.vY;
    ptQTask[79].tQTaskRefList.ptMiddle = nullptr;
    v10 = 1.0 / sqrt(v7 * v7 + vY * vY + v8 * v8);
    igi2_frame.ptPos.vX = v10 * v7;
    igi2_frame.ptPos.vY = igi2_frame.ptPos.vY * v10;
    *(float *)&ptQTask[79].tQTaskChildren.ptMiddle = igi2_frame.ptPos.vX;
    *(float *)&ptQTask[79].tQTaskChildren.ptTail = igi2_frame.ptPos.vY;
    *(float *)&ptQTask[79].tQTaskRefList.ptHead = v10 * v8;
    Human_PopOrientation(ptQTask, igi2_frame.v20);
    LOBYTE(ptQTask[79].tQTaskChildren.ptHead) = 0;
    BYTE1(ptQTask[79].tQTaskChildren.ptHead) = 1;
    LOBYTE(ptQTask[46].tQTaskRefList.ptMiddle) = 1;
    LOBYTE(ptQTask[34].tQTaskChildren.ptMiddle) = 1;
    LOBYTE(ptQTask[33].tQTaskChildren.ptTail[12].tQTaskRefList.ptTail) = 1;
    ptTail = ptQTask[33].tQTaskChildren.ptTail;
    *(_DWORD *)&ptTail[11].eQTaskType = 0;
    ptTail[12].ptNext = nullptr;
    ptTail[12].ptPrev = nullptr;
    ptTail[12].tQTaskRefList.ptHead = nullptr;
    ptTail[12].tQTaskChildren.ptHead = nullptr;
    ptTail[12].tQTaskChildren.ptMiddle = nullptr;
    ptTail[12].tQTaskChildren.ptTail = nullptr;
    ptTail[12].tQTaskRefList.ptMiddle = nullptr;
    LOBYTE(ptQTask[40].tQTaskChildren.ptMiddle) = 1;
    BYTE1(ptQTask[36].tQTaskChildren.ptTail) = 1;
    Human_SnapFromGround(ptQTask);
    ptQTask[33].tQTaskRefList.ptHead = (struct QReference_s *)3;
    LOBYTE(ptQTask[76].tQTaskRefList.ptMiddle) = 1;
    QTask_DeleteQTaskAndQTaskRefSafe(&ptQTask[85].tQTaskRefList.ptHead);
    v12 = SoundSys_NewSoundFn(ptQTask[33].tQTaskChildren.ptTail, "wire_slide_1");
    ptQTask[85].tQTaskRefList.ptHead = QTask_NewQTaskRef(v12);
    ptQTask[48].ptNext = (struct QTask_s *)1;
    *(_DWORD *)&ptQTask[47].eQTaskType = 0;
    v13 = *((void (__cdecl **)(struct QReference_s **, struct QTask_s *))&ptQTask[30].ptParent->ptNext
          + (int)ptQTask[31].ptPrev);
    if ( v13 )
      v13(&ptQTask[30].tQTaskRefList.ptMiddle, ptQTask);
    v14 = ptQTask[30].tQTaskRefList.ptTail;
    ptQTask[31].ptNext = ptQTask[31].ptPrev;
    ptQTask[31].ptPrev = (struct QTask_s *)51;
    ptNext = (struct QTask_s *)v14[17].ptNext;
LABEL_27:
    ptQTask[31].tQTaskChildren.ptHead = ptNext;
    ((void (__cdecl *)(struct QReference_s **, struct QTask_s *))ptNext)(&ptQTask[30].tQTaskRefList.ptMiddle, ptQTask);
    return;
  }
  Wire_GetOrientation(&igi2_frame.ptOrientation, v2);
  igi2_frame.v28[1] = igi2_frame.ptOrientation.tZ.vY
         * (*(double *)&ptQTask[1].tQTaskChildren.ptTail - *(double *)&v2[1].tQTaskChildren.ptTail)
         + igi2_frame.ptOrientation.tY.vY
         * (*(double *)&ptQTask[1].tQTaskChildren.ptHead - *(double *)&v2[1].tQTaskChildren.ptHead)
         + igi2_frame.ptOrientation.tX.vY * (*(double *)&ptQTask[1].ptNext - *(double *)&v2[1].ptNext);
  GameFunctions_GetMagicVertexLocal((struct real32x3_t *)&igi2_frame.v26, v2, 0);
  GameFunctions_GetMagicVertexLocal((struct real32x3_t *)&igi2_frame.ptPos, v2, 1);
  v16 = *((float *)&igi2_frame.v26.vX + 1) + 3072.0 > igi2_frame.v28[1] || *((float *)&igi2_frame.ptPos.vX + 1) - 3072.0 < igi2_frame.v28[1];
  if ( *(float *)&ptQTask[20].ptNext != 0.0 && *(float *)&ptQTask[13].tQTaskRefList.ptTail == 0.0
    || v16
    || (*(_DWORD *)&ptQTask[30].eQTaskType & 0x20000) != 0 )
  {
    BYTE1(ptQTask[79].tQTaskChildren.ptHead) = 0;
    LOBYTE(ptQTask[46].tQTaskRefList.ptMiddle) = 0;
    BYTE1(ptQTask[46].tQTaskRefList.ptMiddle) = 1;
    LOBYTE(ptQTask[34].tQTaskChildren.ptMiddle) = 0;
    LOBYTE(ptQTask[33].tQTaskChildren.ptTail[12].tQTaskRefList.ptTail) = 0;
    LOBYTE(ptQTask[40].tQTaskChildren.ptMiddle) = 0;
    BYTE1(ptQTask[36].tQTaskChildren.ptTail) = 0;
    ptQTask[33].tQTaskRefList.ptHead = (struct QReference_s *)1;
    LOBYTE(ptQTask[76].tQTaskRefList.ptMiddle) = 0;
    QTask_DeleteQTaskAndQTaskRefSafe(&ptQTask[85].tQTaskRefList.ptMiddle);
    QTask_DeleteQTaskAndQTaskRefSafe(&ptQTask[85].tQTaskRefList.ptHead);
    ptQTask[48].ptNext = nullptr;
    *(_DWORD *)&ptQTask[47].eQTaskType = 1;
    LOBYTE(v2[9].tQTaskRefList.ptMiddle) = 0;
    v17 = *((void (__cdecl **)(struct QReference_s **, struct QTask_s *))&ptQTask[30].ptParent->ptNext
          + (int)ptQTask[31].ptPrev);
    if ( (*(_DWORD *)&ptQTask[30].eQTaskType & 0x20000) != 0 )
    {
      if ( v17 )
        v17(&ptQTask[30].tQTaskRefList.ptMiddle, ptQTask);
      v18 = ptQTask[30].tQTaskRefList.ptTail;
      ptQTask[31].ptNext = ptQTask[31].ptPrev;
      ptQTask[31].ptPrev = (struct QTask_s *)55;
      ptNext = (struct QTask_s *)v18[18].ptPrev;
    }
    else
    {
      if ( v17 )
        v17(&ptQTask[30].tQTaskRefList.ptMiddle, ptQTask);
      v19 = ptQTask[30].tQTaskRefList.ptTail;
      ptQTask[31].ptNext = ptQTask[31].ptPrev;
      ptQTask[31].ptPrev = (struct QTask_s *)37;
      ptNext = (struct QTask_s *)v19[12].ptPrev;
    }
    goto LABEL_27;
  }
}

// source: j/0/human/humanplayer.c:4454  [anchor-caller]
void __cdecl HumanPlayer_Update(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float pvBeta; };
    struct { char igi2_o1[4]; float pvGamma; };
    struct { char igi2_o2[8]; _BYTE v32[40]; };
    struct { char igi2_o3[48]; _DWORD v33[10]; };
    struct { char igi2_o4[88]; struct real32x3_t ptSpeed; };
    struct { char igi2_o5[100]; struct real64x3_t ptPos0; };
    struct { char igi2_o6[124]; float v36; };
    struct { char igi2_o7[128]; float v37; };
    struct { char igi2_o8[132]; float v38; };
    struct { char igi2_o9[136]; int v39; };
    struct { char igi2_o10[140]; struct real64x3_t ptPos; };
    struct { char igi2_o11[168]; struct QReference_s **p_ptMiddle; };
    char igi2_extent[200];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v1; // eax
  struct QTask_s *ptPrev; // eax
  int *p_ptTail; // esi
  struct QTask_s *v4; // eax
  struct QReference_s *v5; // ecx
  unsigned int v6; // ecx
  bool v7; // al
  struct QReference_s *ptMiddle; // eax
  void *pxObject; // eax
  struct QTask_s *v10; // eax
  struct QTask_s *ptTail; // eax
  double v13; // st7
  double v14; // st6
  DWORD PerformanceCounter; // eax
  DWORD TickCount; // eax
  double v17; // st7
  double v18; // st7
  struct QTask_s *v19; // eax
  struct QReference_s *v20; // eax
  _WORD *v21; // eax
  struct QTask_s *v23; // eax
  struct QReference_s *ptHumanCameraQTaskRef; // eax
  _DWORD *v26; // eax
  double i; // st7
  float *v28; // eax
  DWORD v29; // eax

  igi2_frame.p_ptMiddle = &ptQTask[30].tQTaskRefList.ptMiddle;
  v1 = *(_DWORD *)&ptQTask[30].eQTaskType;
  if ( (v1 & 2) == 0 || (v1 & 0x10000) != 0 )
  {
    ptQTask[84].ptPrev = (struct QTask_s *)15;
    LOBYTE(ptQTask[50].ptPrev) &= ~8u;
  }
  else
  {
    ptPrev = ptQTask[84].ptPrev;
    if ( ptPrev )
    {
      LOBYTE(ptQTask[50].ptPrev) &= ~8u;
      ptQTask[84].ptPrev = (struct QTask_s *)((char *)ptPrev - 1);
    }
  }
  Human_UpdateDie((struct Human_s *)ptQTask);
  Human_UpdateActivate(ptQTask);
  HumanPlayer_SelectWeaponFromCategory(ptQTask);
  if ( !Computer_ptComputerQTask
    || *(float *)&ptQTask[21].tQTaskRefList.ptHead == 0.0 && *(float *)&ptQTask[21].tQTaskRefList.ptMiddle == 0.0 )
  {
    HumanPlayer_SelectWeapon(ptQTask, 0);
  }
  if ( BYTE1(ptQTask[80].tQTaskChildren.ptTail) )
    ptQTask[20].ptNext = nullptr;
  p_ptTail = (int *)&ptQTask[51].tQTaskRefList.ptTail;
  if ( Water_IsUnderWater(
         (float *)&ptQTask[51].tQTaskRefList.ptMiddle,
         (struct real64x3_t *)&ptQTask[1],
         (int *)&ptQTask[51].tQTaskRefList.ptTail) )
  {
    v4 = ptQTask[31].ptPrev;
    if ( v4 == (struct QTask_s *)21 || v4 == (struct QTask_s *)1 )
    {
      Water_PlayerMovementEffect((struct real64x3_t *)&ptQTask[1], *p_ptTail, false);
    }
    else if ( v4 )
    {
      Water_PlayerMovementEffect(
        (struct real64x3_t *)&ptQTask[1],
        *p_ptTail,
        (enum bool)(BYTE1(ptQTask[50].ptNext) != 0));
    }
  }
  else
  {
    ptQTask[51].tQTaskRefList.ptMiddle = nullptr;
  }
  if ( *(float *)&ptQTask[51].tQTaskRefList.ptMiddle >= 819.2000122070312 )
    LOBYTE(ptQTask[50].ptPrev) &= ~4u;
  if ( *(float *)&ptQTask[51].tQTaskRefList.ptMiddle >= 3276.800048828125 )
    LOBYTE(ptQTask[50].ptPrev) &= 0xF9u;
  v5 = igi2_frame.p_ptMiddle[3];
  if ( *(float *)&ptQTask[51].tQTaskRefList.ptMiddle < 5734.39990234375 )
    v6 = (unsigned int)v5 & 0xFF7FFFFF;
  else
    v6 = (unsigned int)v5 | 0x800000;
  igi2_frame.p_ptMiddle[3] = (struct QReference_s *)v6;
  v7 = !ptQTask[44].tQTaskRefList.ptTail && !LOBYTE(ptQTask[80].tQTaskRefList.ptMiddle);
  LOBYTE(ptQTask[50].ptNext) = v7;
  ptMiddle = ptQTask[44].tQTaskRefList.ptMiddle;
  if ( ptMiddle )
    pxObject = ptMiddle->pxObject;
  else
    pxObject = nullptr;
  if ( pxObject && *(float *)&ptQTask[42].tQTaskChildren.ptHead < 0.6427900195121765 )
  {
    ptQTask[19].tQTaskRefList.ptHead = nullptr;
    ptQTask[19].tQTaskRefList.ptMiddle = nullptr;
  }
  v10 = ptQTask[33].ptNext[1].ptPrev;
  if ( v10 )
    ptTail = v10->tQTaskChildren.ptTail;
  else
    ptTail = nullptr;
  if ( ptTail
    && ptTail[32].tQTaskRefList.ptHead == (struct QReference_s *)Gun_eQTaskType
    && *(_DWORD *)&ptTail[32].ptParent->tQTaskChildren.ptHead[2].eQTaskType == Missile_eQTaskType )
  {
    LOBYTE(ptQTask[50].ptPrev) &= ~4u;
  }
  if ( *(float *)&ptQTask[22].tQTaskRefList.ptMiddle != 0.0
    || *(float *)&ptQTask[23].tQTaskRefList.ptHead != 0.0
    || *(float *)&ptQTask[23].tQTaskRefList.ptMiddle != 0.0
    || *(float *)&ptQTask[23].tQTaskRefList.ptTail != 0.0 )
  {
    ptQTask[19].tQTaskRefList.ptTail = nullptr;
  }
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    State_Run((struct State_s *)&ptQTask[30].tQTaskRefList.ptMiddle, ptQTask);
    State_Run((struct State_s *)&ptQTask[74].tQTaskRefList.ptMiddle, ptQTask);
  }
  else
  {
    State_Run((struct State_s *)&ptQTask[30].tQTaskRefList.ptMiddle, ptQTask);
    State_Run((struct State_s *)&ptQTask[74].tQTaskRefList.ptMiddle, ptQTask);
  }
  if ( *(float *)&ptQTask[21].tQTaskChildren.ptTail != 0.0 && *(float *)&ptQTask[15].ptPrev == 0.0 )
    BYTE1(ptQTask[76].tQTaskRefList.ptMiddle) ^= 1u;
  if ( *(int *)&ptQTask[32].eQTaskType >= 1 )
    BYTE1(ptQTask[50].ptNext) = 0;
  if ( LOBYTE(ptQTask[78].tQTaskChildren.ptTail) || BYTE1(ptQTask[78].tQTaskChildren.ptTail) )
    HumanPlayer_ClimbLadder(ptQTask);
  if ( LOBYTE(ptQTask[78].ptParent) || BYTE1(ptQTask[78].ptParent) )
    HumanPlayer_ClimbFence(ptQTask);
  if ( HIBYTE(ptQTask[78].ptParent) || LOBYTE(ptQTask[78].eQTaskType) )
    HumanPlayer_ClimbWire(ptQTask);
  if ( LOBYTE(ptQTask[79].tQTaskChildren.ptHead) || BYTE1(ptQTask[79].tQTaskChildren.ptHead) )
    HumanPlayer_SlideWire(ptQTask);
  igi2_frame.p_ptMiddle[3] = (struct QReference_s *)((unsigned int)igi2_frame.p_ptMiddle[3] & 0xFFFEFFFF);
  Human_UpdateBody(ptQTask);
  HumanView_UpdateView(ptQTask[33].tQTaskChildren.ptTail, ptQTask);
  HumanPlayer_CheckViewCollision((struct HumanPlayer_t *)ptQTask);
  if ( !BYTE1(ptQTask[36].tQTaskChildren.ptTail) )
  {
    *(float *)&ptQTask[36].ptPrev = HumanPlayer_tGeneral.vDeltaTranslationScale * *(float *)&ptQTask[36].ptPrev;
    *(float *)&ptQTask[36].tQTaskChildren.ptHead = HumanPlayer_tGeneral.vDeltaTranslationScale
                                                 * *(float *)&ptQTask[36].tQTaskChildren.ptHead;
    *(float *)&ptQTask[36].tQTaskChildren.ptMiddle = HumanPlayer_tGeneral.vDeltaTranslationScale
                                                   * *(float *)&ptQTask[36].tQTaskChildren.ptMiddle;
  }
  if ( LOBYTE(ptQTask[29].tQTaskRefList.ptHead) && LOBYTE(ptQTask[80].tQTaskRefList.ptMiddle) )
  {
    v13 = *(float *)&ptQTask[51].tQTaskRefList.ptMiddle - 5734.39990234375;
    v14 = v13;
    if ( v13 < 0.0 )
      v14 = -v13;
    if ( v14 > 4.096 )
    {
      ptQTask[38].ptPrev = nullptr;
      ptQTask[38].tQTaskChildren.ptHead = nullptr;
      ptQTask[38].tQTaskChildren.ptMiddle = nullptr;
      ptQTask[38].tQTaskChildren.ptTail = nullptr;
      ptQTask[38].tQTaskRefList.ptHead = nullptr;
      ptQTask[38].tQTaskRefList.ptMiddle = nullptr;
      qmemcpy(&igi2_frame.ptPos, &ptQTask[1], sizeof(igi2_frame.ptPos));
      igi2_frame.ptPos.vZ = v13 + igi2_frame.ptPos.vZ;
      Human_PopPosition(ptQTask, &igi2_frame.ptPos);
      ptQTask[86].tQTaskChildren.ptHead = nullptr;
      ptQTask[86].tQTaskChildren.ptMiddle = nullptr;
      ptQTask[86].tQTaskChildren.ptTail = nullptr;
    }
  }
  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  if ( (int)(PerformanceCounter - Timer_nStartTime - 600000) >= 0 )
  {
    if ( Timer_isPerformanceCounter )
      TickCount = Timer_GetPerformanceCounter();
    else
      TickCount = GetTickCount();
    igi2_frame.v39 = TickCount - Timer_nStartTime - 600000;
  }
  else
  {
    igi2_frame.v39 = 0;
  }
  v17 = (double)igi2_frame.v39 * 0.0000008333333333333333;
  if ( v17 >= 1.0 )
    v17 = 1.0;
  v18 = (DEGRADE_PlayerMovementSpeed - 1.0) * v17 + 1.0;
  igi2_frame.v38 = v18 * *(float *)&ptQTask[86].tQTaskChildren.ptHead;
  *(float *)&ptQTask[86].tQTaskChildren.ptHead = igi2_frame.v38;
  igi2_frame.v37 = v18 * *(float *)&ptQTask[86].tQTaskChildren.ptMiddle;
  *(float *)&ptQTask[86].tQTaskChildren.ptMiddle = igi2_frame.v37;
  igi2_frame.v36 = v18 * *(float *)&ptQTask[86].tQTaskChildren.ptTail;
  *(float *)&ptQTask[86].tQTaskChildren.ptTail = igi2_frame.v36;
  v19 = ptQTask[31].ptPrev;
  if ( v19 != (struct QTask_s *)57 && v19 != (struct QTask_s *)56 )
  {
    if ( ptQTask[44].tQTaskRefList.ptTail )
    {
      qmemcpy(&igi2_frame.ptPos0, &ptQTask[1], sizeof(igi2_frame.ptPos0));
      Human_GroundCollision(ptQTask, &igi2_frame.ptPos0, &igi2_frame.ptPos0, &igi2_frame.ptSpeed, (unsigned int *)&ptQTask[30].eQTaskType, 819.2000122070312);
      Human_Attach(ptQTask);
    }
    else if ( (ptQTask[30].eQTaskType & 2) == 0 || LOBYTE(ptQTask[29].tQTaskRefList.ptHead) )
    {
      ptQTask[86].tQTaskChildren.ptHead = nullptr;
      ptQTask[86].tQTaskChildren.ptMiddle = nullptr;
      ptQTask[86].tQTaskChildren.ptTail = nullptr;
      Human_Move(ptQTask);
    }
    else
    {
      *(float *)&ptQTask[36].ptPrev = igi2_frame.v38 + *(float *)&ptQTask[36].ptPrev;
      *(float *)&ptQTask[36].tQTaskChildren.ptHead = igi2_frame.v37 + *(float *)&ptQTask[36].tQTaskChildren.ptHead;
      *(float *)&ptQTask[36].tQTaskChildren.ptMiddle = igi2_frame.v36 + *(float *)&ptQTask[36].tQTaskChildren.ptMiddle;
      Human_Move(ptQTask);
    }
  }
  if ( *(_DWORD *)&ptQTask[32].eQTaskType == 2 )
  {
    v20 = ptQTask[44].tQTaskRefList.ptMiddle;
    v21 = v20 ? v20->pxObject : nullptr;
    if ( !v21 || v21[18] != Train_eQTaskType )
    {
      Human_InterpolateZAxisToAveragedGroundNormal(ptQTask);
      Human_UpdatePlatformPos(ptQTask, false, true);
      ModelObj_UpdateAttachments((struct ModelObj_s *)ptQTask);
    }
  }
  AnimController_Step(
    (struct AnimController_t *)ptQTask[34].tQTaskChildren.ptTail,
    (int)ptQTask[34].tQTaskChildren.ptTail[1].tQTaskRefList.ptMiddle
  + (unsigned int)ptQTask[34].tQTaskChildren.ptTail[1].tQTaskRefList.ptTail);
  HumanView_UpdateBody(ptQTask[33].tQTaskChildren.ptTail, ptQTask, true);
  if ( LOBYTE(ptQTask[84].ptNext) )
  {
    Weapon_Fire(ptQTask[33].ptNext, (int)ptQTask[77].ptPrev);
    LOBYTE(ptQTask[84].ptNext) = 0;
    ptQTask[83].ptParent = nullptr;
  }
  Weapon_UpdateStatus(ptQTask[33].ptNext);
  Human_Notify(ptQTask);
  HumanPlayer_Pickup(ptQTask);
  HumanPlayer_UpdateDamageFlash(ptQTask);
  HumanPlayer_UpdateFlashBangFlash(ptQTask);
  v23 = ptQTask[80].tQTaskChildren.ptMiddle;
  if ( v23 )
    ptQTask[80].tQTaskChildren.ptMiddle = (struct QTask_s *)((char *)v23 - 1);
  if ( LOBYTE(ptQTask[83].eQTaskType) )
  {
    ptHumanCameraQTaskRef = Game_ptGame->ptHumanCameraQTaskRef;
    if ( ptHumanCameraQTaskRef ? ptHumanCameraQTaskRef->pxObject : nullptr )
    {
      v26 = ptHumanCameraQTaskRef ? ptHumanCameraQTaskRef->pxObject : nullptr;
      igi2_frame.v33[0] = v26[16];
      igi2_frame.v33[1] = v26[19];
      igi2_frame.v33[2] = v26[22];
      igi2_frame.v33[3] = v26[17];
      igi2_frame.v33[4] = v26[20];
      igi2_frame.v33[5] = v26[23];
      igi2_frame.v33[6] = v26[18];
      igi2_frame.v33[7] = v26[21];
      igi2_frame.v33[8] = v26[24];
      igi2_frame.v33[9] = v26[25];
      qmemcpy(igi2_frame.v32, igi2_frame.v33, sizeof(igi2_frame.v32));
      Real32x3_GetAngles((struct real32x3_t *)&igi2_frame.v32[24], &igi2_frame.pvBeta, &igi2_frame.pvGamma);
      for ( i = igi2_frame.pvGamma; i < 0.0; i = i + 6.2831854820251465 )
        ;
    }
  }
  v28 = (float *)ptQTask[33].tQTaskChildren.ptTail;
  v28[121] = -v28[121] * v28[118] + v28[121];
  v28[124] = -v28[124] * v28[118] + v28[124];
  if ( Timer_isPerformanceCounter )
    v29 = Timer_GetPerformanceCounter();
  else
    v29 = GetTickCount();
  ptQTask[51].ptParent = (struct QTask_s *)(v29 - Timer_nStartTime);
}

// source: j/0/human/humanplayer.c:4855  [anchor-callee]
struct real64x3_t *__cdecl HumanPlayer_ExtrapolatePos(
        struct Human_s *ptHuman,
        struct real64x3_t *ptPos)
{
  DWORD PerformanceCounter; // eax
  int v4; // eax
  double v5; // st5
  double v6; // st7
  DWORD TickCount; // eax
  struct real64x3_t *result; // eax
  float nTimeDiff; // [esp+Ch] [ebp-20h]
  double tSpeed_16; // [esp+20h] [ebp-Ch]

  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  v4 = PerformanceCounter - Timer_nStartTime - LODWORD(ptHuman->atOldPos[0].vX);
  if ( (ptHuman->tState.bSignal & 4) != 0 || HIBYTE(ptHuman->ptCoughRef) && BYTE2(ptHuman->ptCoughRef) || v4 <= 0 )
  {
    qmemcpy(ptPos, &ptHuman->tBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos, sizeof(struct real64x3_t));
  }
  else
  {
    tSpeed_16 = ptHuman->tWorldSpeed.vZ;
    v5 = (double)v4 * 0.029999999329447746;
    nTimeDiff = v5;
    v6 = nTimeDiff * ptHuman->tWorldSpeed.vY;
    ptPos->vX = v5 * ptHuman->tWorldSpeed.vX + ptHuman->tBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vX;
    ptPos->vY = v6 + ptHuman->tBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vY;
    ptPos->vZ = nTimeDiff * tSpeed_16 + ptHuman->tBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vZ;
  }
  if ( Timer_isPerformanceCounter )
    TickCount = Timer_GetPerformanceCounter();
  else
    TickCount = GetTickCount();
  result = (struct real64x3_t *)(TickCount - Timer_nStartTime);
  LODWORD(ptHuman->atOldPos[0].vX) = result;
  return result;
}

// source: j/0/human/humanplayer.c:4912  [anchor-caller]
void __cdecl HumanPlayer_StateSignalHandler(struct State_s *ptState, struct QTask_s *ptQTask)
{
  unsigned int v2; // ebp
  unsigned int v3; // ebp
  struct QTask_s *ptNext; // edx
  struct QTask_s *v5; // eax
  struct QTask_s *v6; // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptTail; // eax
  struct QTask_s *v9; // eax
  struct QTask_s *v10; // ecx
  struct QTask_s *v11; // ecx
  struct QTask_s *v12; // eax
  struct QTask_s *v13; // eax
  struct QTask_s *v14; // ecx

  v2 = ptState->bSignal & 0xC0F7001E;
  if ( *(float *)&ptQTask[19].ptPrev != 0.0 )
    v2 |= 0x8000000u;
  if ( ((int)ptQTask[34].tQTaskChildren.ptTail[1].ptPrev & 4) != 0 )
    v2 |= 1u;
  if ( BYTE1(ptQTask[76].tQTaskRefList.ptMiddle) == (*(float *)&ptQTask[23].ptPrev != 0.0) )
  {
    BYTE1(ptQTask[50].ptNext) = 1;
    v3 = v2 & 0xFFFBFFFF;
  }
  else
  {
    BYTE1(ptQTask[50].ptNext) = 0;
    v3 = v2 | 0x40000;
  }
  if ( *(float *)&ptQTask[19].tQTaskChildren.ptMiddle != 0.0 )
  {
    v3 |= 0x20u;
    ptQTask[83].ptParent = nullptr;
  }
  if ( *(float *)&ptQTask[19].tQTaskChildren.ptTail != 0.0 )
  {
    v3 |= 0x40u;
    ptQTask[83].ptParent = nullptr;
  }
  if ( *(float *)&ptQTask[19].tQTaskRefList.ptHead != 0.0 )
  {
    v3 |= 0x80u;
    ptQTask[83].ptParent = nullptr;
  }
  if ( *(float *)&ptQTask[19].tQTaskRefList.ptMiddle != 0.0 )
  {
    v3 |= 0x100u;
    ptQTask[83].ptParent = nullptr;
  }
  ptNext = ptQTask[33].ptNext;
  if ( *(float *)&ptQTask[19].tQTaskRefList.ptTail == 0.0 )
  {
    if ( ptNext )
    {
      ptPrev = ptNext[1].ptPrev;
      if ( ptPrev )
      {
        ptTail = ptPrev->tQTaskChildren.ptTail;
        if ( ptTail )
        {
          if ( ptTail[16].ptParent == (struct QTask_s *)10 && Human_IsZoomFireModeActive((struct Human_s *)ptQTask) )
            Weapon_Fire(ptNext, 1);
        }
      }
    }
  }
  else
  {
    if ( ptNext )
    {
      v5 = ptNext[1].ptPrev;
      if ( v5 )
      {
        v6 = v5->tQTaskChildren.ptTail;
        if ( v6 )
        {
          if ( v6[16].ptParent == (struct QTask_s *)10 )
          {
            if ( Human_IsZoomFireModeActive((struct Human_s *)ptQTask) == false )
              Weapon_Fire(ptNext, 1);
            ptQTask[33].ptNext[1].ptParent = nullptr;
          }
        }
      }
    }
    v3 |= 0x200u;
  }
  if ( *(float *)&ptQTask[19].ptParent != 0.0 )
  {
    v9 = ptQTask[33].ptNext;
    v10 = v9[1].ptPrev;
    if ( v10 )
      v11 = v10->tQTaskChildren.ptTail;
    else
      v11 = nullptr;
    if ( v9
      && (v12 = v9[1].ptPrev) != nullptr
      && (v13 = v12->tQTaskChildren.ptTail) != nullptr
      && v13[16].ptParent == (struct QTask_s *)10 )
    {
      ptQTask[19].ptParent = nullptr;
    }
    else
    {
      v3 |= 0x400u;
    }
    if ( v11
      && v11[33].ptNext == (struct QTask_s *)Zoom_eQTaskType
      && HumanPlayer_IsZoomedModeAllowed(ptQTask) == false )
    {
      ptQTask[19].ptParent = nullptr;
    }
    else
    {
      v3 |= 0x400u;
    }
  }
  if ( *(float *)&ptQTask[19].eQTaskType != 0.0 )
  {
    v3 |= 0x800u;
    ptQTask[83].ptParent = nullptr;
  }
  if ( *(float *)&ptQTask[20].ptNext != 0.0 )
  {
    v3 |= 0x1000u;
    ptQTask[83].ptParent = nullptr;
  }
  if ( *(float *)&ptQTask[23].ptNext != 0.0 && *(float *)&ptQTask[16].tQTaskRefList.ptTail == 0.0 )
  {
    v3 |= 0x2000000u;
    ptQTask[83].ptParent = nullptr;
  }
  if ( *(float *)&ptQTask[22].eQTaskType != 0.0 && *(float *)&ptQTask[16].tQTaskRefList.ptMiddle == 0.0 )
  {
    v3 |= 0x1000000u;
    ptQTask[83].ptParent = nullptr;
  }
  if ( *(float *)&ptQTask[24].ptNext != 0.0 && *(float *)&ptQTask[17].tQTaskRefList.ptTail == 0.0 )
  {
    if ( *(_DWORD *)&ptQTask[32].eQTaskType == 2 )
      v3 |= 0x10000000u;
    else
      v3 |= 0x20000000u;
    ptQTask[83].ptParent = nullptr;
  }
  if ( *(float *)&ptQTask[23].ptPrev != 0.0 )
    v3 |= 0x4000000u;
  if ( *(float *)&ptQTask[20].ptPrev == 0.0 )
  {
    if ( *(float *)&ptQTask[13].ptParent == 0.0 )
      goto LABEL_69;
  }
  else
  {
    v3 |= 0x2000u;
    if ( *(float *)&ptQTask[13].ptParent != 0.0 )
      goto LABEL_69;
  }
  ptQTask[83].ptParent = nullptr;
LABEL_69:
  if ( *(float *)&ptQTask[20].tQTaskChildren.ptHead != 0.0 )
  {
    v3 |= 0x4000u;
    ptQTask[83].ptParent = nullptr;
  }
  if ( *(float *)&ptQTask[21].tQTaskRefList.ptHead != 0.0 )
  {
    v3 |= 0x80000u;
    ptQTask[83].ptParent = nullptr;
  }
  v14 = ActionMenuScreen_ptQTask;
  if ( *(float *)&ptQTask[20].tQTaskRefList.ptHead != 0.0 && *(float *)&ptQTask[14].tQTaskChildren.ptHead == 0.0 )
    ActionMenuScreen_ptQTask[4].ptPrev = (struct QTask_s *)1;
  if ( *(float *)&ptQTask[20].tQTaskRefList.ptMiddle != 0.0 && *(float *)&ptQTask[14].tQTaskChildren.ptMiddle == 0.0 )
    v14[4].ptPrev = (struct QTask_s *)-1;
  if ( *(float *)&ptQTask[20].tQTaskRefList.ptHead != 0.0 && *(float *)&ptQTask[14].tQTaskChildren.ptHead == 0.0 )
  {
    Weapon_Zoom(ptQTask[33].ptNext, true);
    ptQTask[83].ptParent = nullptr;
  }
  if ( *(float *)&ptQTask[20].tQTaskRefList.ptMiddle == 0.0 )
  {
    ptState->bSignal = v3;
  }
  else
  {
    if ( *(float *)&ptQTask[14].tQTaskChildren.ptMiddle == 0.0 )
    {
      Weapon_Zoom(ptQTask[33].ptNext, false);
      ptQTask[83].ptParent = nullptr;
    }
    ptState->bSignal = v3;
  }
}

// source: j/0/human/humanplayer.c:5136  [anchor-mhash]
void __cdecl HumanPlayer_InitStateStand(struct State_s *ptState, struct QTask_s *ptQTask)
{
  struct QTask_s *ptTail; // eax
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *v5; // ecx
  double v6; // st7
  double v7; // st6

  ptTail = ptQTask[33].tQTaskChildren.ptTail;
  ptTail[14].tQTaskRefList.ptTail = nullptr;
  ptTail[14].ptParent = nullptr;
  *(_DWORD *)&ptTail[14].eQTaskType = 0;
  ptTail[14].tQTaskChildren.ptTail = nullptr;
  ptTail[14].tQTaskRefList.ptHead = nullptr;
  ptTail[14].tQTaskRefList.ptMiddle = nullptr;
  *(_DWORD *)&ptQTask[32].eQTaskType = 0;
  HumanAnim_SetAnimationAndTimeFromState(ptQTask, 2, 0, 0.20000000298023224);
  ptNext = ptQTask[33].ptNext;
  ptQTask[77].ptParent = (struct QTask_s *)1;
  ptPrev = ptNext[1].ptPrev;
  if ( ptPrev && (v5 = ptPrev->tQTaskChildren.ptTail) != nullptr )
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    v6 = *(float *)&v5[21].ptNext;
    ptQTask[77].tQTaskChildren.ptMiddle = v5[21].ptNext;
    v7 = *(float *)&ptQTask[43].ptParent;
    if ( v7 < 0.0 )
      v7 = -v7;
    *(float *)&ptQTask[77].tQTaskChildren.ptMiddle = v7 * *(float *)&v5[21].ptParent * 3.0 + v6;
    ptState->pfState = HumanPlayer_RunStateStand;
  }
  else
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    ptQTask[77].tQTaskChildren.ptMiddle = nullptr;
    ptState->pfState = HumanPlayer_RunStateStand;
  }
}

// source: j/0/human/humanplayer.c:5167  [anchor-mhash]
void __cdecl HumanPlayer_RunStateStand(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { int bSignal; };
    struct { char igi2_o1[4]; unsigned int v58; };
    struct { char igi2_o2[8]; struct real32x3_t tReal32x3; };
    struct { char igi2_o3[20]; struct real64x3_t tReal64x3; };
    char igi2_extent[44];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v2; // esi
  unsigned int v3; // ecx
  void (__cdecl *v4)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v6)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v7)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v8)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v9)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v10)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v11)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v12)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v13)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v14)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v15)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v16)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v17)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v18)(struct State_s *, struct QTask_s *); // eax
  char ptPrev; // al
  void (__cdecl *v20)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v21)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v22)(struct State_s *, struct QTask_s *); // eax
  bool v23; // zf
  void (__cdecl *v24)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v25)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v26)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v27)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v28)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v29)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v30)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v31)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v32)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v33)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v34)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v35)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v36)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v37)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v38)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v39)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v40)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v41)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v42)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v43)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v44)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v45)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v46)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v47)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v48)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v49)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v50)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v51)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v52)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v53)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v54)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v55)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v56)(struct State_s *, struct QTask_s *); // eax

  v2 = ptQTask;
  igi2_frame.v58 = ptState->bSignal;
  HumanPlayer_MoveOnGround((struct HumanPlayer_t *)ptQTask, 0.0, 118.76579284667969, 0.0, 118.76579284667969);
  v3 = igi2_frame.v58;
  if ( (igi2_frame.v58 & 0x20000) != 0 )
  {
    v4 = ptState->apfExitState[ptState->nState];
    if ( v4 )
      v4(ptState, ptQTask);
    apfState = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 55;
    v6 = apfState[55];
    ptState->pfState = v6;
    v6(ptState, ptQTask);
    return;
  }
  if ( (igi2_frame.v58 & 0x800000) != 0 )
  {
    v7 = ptState->apfExitState[ptState->nState];
    if ( v7 )
      v7(ptState, ptQTask);
    v8 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 21;
    v9 = v8[21];
    ptState->pfState = v9;
    v9(ptState, ptQTask);
    return;
  }
  if ( (igi2_frame.v58 & 2) == 0 )
  {
    v10 = ptState->apfExitState[ptState->nState];
    if ( v10 )
      v10(ptState, ptQTask);
    v11 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 37;
    v12 = v11[37];
    ptState->pfState = v12;
    v12(ptState, ptQTask);
    return;
  }
  if ( (igi2_frame.v58 & 0x10000) != 0 )
  {
    v13 = ptState->apfExitState[ptState->nState];
    if ( v13 )
      v13(ptState, ptQTask);
    v14 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 54;
    v15 = v14[54];
    ptState->pfState = v15;
    v15(ptState, ptQTask);
    return;
  }
  if ( (igi2_frame.v58 & 0x1000000) != 0 )
  {
    ptQTask[83].tQTaskRefList.ptHead = nullptr;
    v16 = ptState->apfExitState[ptState->nState];
    if ( v16 )
      v16(ptState, ptQTask);
    v17 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 23;
    v18 = v17[23];
    ptState->pfState = v18;
    v18(ptState, ptQTask);
    return;
  }
  if ( (igi2_frame.v58 & 0x2000) != 0 || (ptPrev = (char)ptQTask[50].ptPrev, (ptPrev & 1) == 0) )
  {
    ptPrev = (char)ptQTask[50].ptPrev;
    if ( (ptPrev & 2) != 0 )
    {
      ptQTask[83].tQTaskRefList.ptHead = (struct QReference_s *)1;
      v20 = ptState->apfExitState[ptState->nState];
      if ( v20 )
        v20(ptState, ptQTask);
      v21 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 23;
      v22 = v21[23];
      ptState->pfState = v22;
      v22(ptState, ptQTask);
      return;
    }
  }
  if ( (igi2_frame.v58 & 0x20000000) != 0 && (ptPrev & 4) != 0 )
  {
    igi2_frame.bSignal = 0;
    qmemcpy(&igi2_frame.tReal64x3, &ptQTask[1], sizeof(igi2_frame.tReal64x3));
    *(_DWORD *)&ptQTask[32].eQTaskType = 2;
    Human_ObjectCollision(ptQTask, &igi2_frame.tReal64x3, &igi2_frame.tReal64x3, &igi2_frame.tReal32x3, (unsigned int *)&igi2_frame.bSignal);
    v23 = (igi2_frame.bSignal & 4) == 0;
    *(_DWORD *)&ptQTask[32].eQTaskType = 0;
    if ( v23 )
    {
      v24 = ptState->apfExitState[ptState->nState];
      if ( v24 )
        v24(ptState, ptQTask);
      v25 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 75;
      v26 = v25[75];
      ptState->pfState = v26;
      v26(ptState, ptQTask);
      return;
    }
    v3 = igi2_frame.v58;
    v2 = ptQTask;
  }
  if ( (ptState->bSignal & 0x40000) != 0 )
  {
    if ( (v3 & 0x80u) != 0 )
    {
      v27 = ptState->apfExitState[ptState->nState];
      if ( v27 )
        v27(ptState, v2);
      v28 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 11;
      v29 = v28[11];
      ptState->pfState = v29;
      v29(ptState, v2);
      return;
    }
    if ( (v3 & 0x100) != 0 )
    {
      v30 = ptState->apfExitState[ptState->nState];
      if ( v30 )
        v30(ptState, v2);
      v31 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 14;
      v32 = v31[14];
      ptState->pfState = v32;
      v32(ptState, v2);
      return;
    }
    if ( (v3 & 0x40) != 0 )
    {
      v33 = ptState->apfExitState[ptState->nState];
      if ( v33 )
        v33(ptState, v2);
      v34 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 17;
      v35 = v34[17];
      ptState->pfState = v35;
      v35(ptState, v2);
      return;
    }
    if ( (v3 & 0x20) != 0 )
    {
      v36 = ptState->apfExitState[ptState->nState];
      if ( v36 )
        v36(ptState, v2);
      v37 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 18;
      v38 = v37[18];
      ptState->pfState = v38;
      v38(ptState, v2);
      return;
    }
    goto LABEL_67;
  }
  if ( (v3 & 0x80u) == 0 )
  {
    if ( (v3 & 0x100) != 0 )
    {
      v42 = ptState->apfExitState[ptState->nState];
      if ( v42 )
        v42(ptState, v2);
      v43 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 6;
      v44 = v43[6];
      ptState->pfState = v44;
      v44(ptState, v2);
    }
    else if ( (v3 & 0x40) != 0 )
    {
      v45 = ptState->apfExitState[ptState->nState];
      if ( v45 )
        v45(ptState, v2);
      v46 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 9;
      v47 = v46[9];
      ptState->pfState = v47;
      v47(ptState, v2);
    }
    else
    {
      if ( (v3 & 0x20) == 0 )
      {
LABEL_67:
        if ( *(float *)&v2[20].tQTaskChildren.ptHead != 0.0
          && *(float *)&v2[13].eQTaskType == 0.0
          && ((int)v2[50].ptPrev & 8) != 0 )
        {
          v51 = ptState->apfExitState[ptState->nState];
          if ( v51 )
            v51(ptState, v2);
          v52 = ptState->apfState;
          ptState->nPreviousState = ptState->nState;
          ptState->nState = 36;
          v53 = v52[36];
          ptState->pfState = v53;
          v53(ptState, v2);
        }
        else if ( (v3 & 0x8000000) != 0 )
        {
          v54 = ptState->apfExitState[ptState->nState];
          if ( v54 )
            v54(ptState, v2);
          v55 = ptState->apfState;
          ptState->nPreviousState = ptState->nState;
          ptState->nState = 1;
          v56 = v55[1];
          ptState->pfState = v56;
          v56(ptState, v2);
        }
        return;
      }
      v48 = ptState->apfExitState[ptState->nState];
      if ( v48 )
        v48(ptState, v2);
      v49 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 10;
      v50 = v49[10];
      ptState->pfState = v50;
      v50(ptState, v2);
    }
  }
  else
  {
    v39 = ptState->apfExitState[ptState->nState];
    if ( v39 )
      v39(ptState, v2);
    v40 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 3;
    v41 = v40[3];
    ptState->pfState = v41;
    v41(ptState, v2);
  }
}

// source: j/0/human/humanplayer.c:5263  [anchor-mhash]
void __cdecl HumanPlayer_InitStateStandTurn(struct State_s *ptState, struct QTask_s *ptQTask)
{
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptTail; // ecx
  double v4; // st7
  double v5; // st6

  ptQTask[81].tQTaskChildren.ptMiddle = nullptr;
  *(_DWORD *)&ptQTask[32].eQTaskType = 0;
  HumanAnim_SetAnimationAndTimeFromState(ptQTask, 1, 0, 0.20000000298023224);
  ptQTask[77].ptParent = (struct QTask_s *)1;
  ptQTask[34].tQTaskChildren.ptTail[1].ptPrev = (struct QTask_s *)((int)ptQTask[34].tQTaskChildren.ptTail[1].ptPrev | 1);
  ptPrev = ptQTask[33].ptNext[1].ptPrev;
  if ( ptPrev && (ptTail = ptPrev->tQTaskChildren.ptTail) != nullptr )
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    v4 = *(float *)&ptTail[21].ptNext;
    ptQTask[77].tQTaskChildren.ptMiddle = ptTail[21].ptNext;
    v5 = *(float *)&ptQTask[43].ptParent;
    if ( v5 < 0.0 )
      v5 = -v5;
    *(float *)&ptQTask[77].tQTaskChildren.ptMiddle = v5 * *(float *)&ptTail[21].ptParent * 3.0 + v4;
    ptState->pfState = HumanPlayer_RunStateStandTurn;
  }
  else
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    ptQTask[77].tQTaskChildren.ptMiddle = nullptr;
    ptState->pfState = HumanPlayer_RunStateStandTurn;
  }
}

// source: j/0/human/humanplayer.c:5295  [anchor-mhash]
void __cdecl HumanPlayer_RunStateStandTurn(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { int bSignal; };
    struct { char igi2_o1[4]; unsigned int v58; };
    struct { char igi2_o2[8]; struct real32x3_t tReal32x3; };
    struct { char igi2_o3[20]; struct real64x3_t tReal64x3; };
    char igi2_extent[44];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v2; // esi
  unsigned int v3; // ecx
  void (__cdecl *v4)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v6)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v7)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v8)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v9)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v10)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v11)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v12)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v13)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v14)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v15)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v16)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v17)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v18)(struct State_s *, struct QTask_s *); // eax
  char ptPrev; // al
  void (__cdecl *v20)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v21)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v22)(struct State_s *, struct QTask_s *); // eax
  bool v23; // zf
  void (__cdecl *v24)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v25)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v26)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v27)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v28)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v29)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v30)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v31)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v32)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v33)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v34)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v35)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v36)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v37)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v38)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v39)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v40)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v41)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v42)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v43)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v44)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v45)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v46)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v47)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v48)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v49)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v50)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v51)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v52)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v53)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v54)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v55)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v56)(struct State_s *, struct QTask_s *); // eax

  v2 = ptQTask;
  igi2_frame.v58 = ptState->bSignal;
  HumanPlayer_MoveOnGround((struct HumanPlayer_t *)ptQTask, 0.0, 118.76579284667969, 0.0, 118.76579284667969);
  v3 = igi2_frame.v58;
  if ( (igi2_frame.v58 & 0x20000) != 0 )
  {
    v4 = ptState->apfExitState[ptState->nState];
    if ( v4 )
      v4(ptState, ptQTask);
    apfState = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 55;
    v6 = apfState[55];
    ptState->pfState = v6;
    v6(ptState, ptQTask);
    return;
  }
  if ( (igi2_frame.v58 & 0x800000) != 0 )
  {
    v7 = ptState->apfExitState[ptState->nState];
    if ( v7 )
      v7(ptState, ptQTask);
    v8 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 21;
    v9 = v8[21];
    ptState->pfState = v9;
    v9(ptState, ptQTask);
    return;
  }
  if ( (igi2_frame.v58 & 2) == 0 )
  {
    v10 = ptState->apfExitState[ptState->nState];
    if ( v10 )
      v10(ptState, ptQTask);
    v11 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 37;
    v12 = v11[37];
    ptState->pfState = v12;
    v12(ptState, ptQTask);
    return;
  }
  if ( (igi2_frame.v58 & 0x10000) != 0 )
  {
    v13 = ptState->apfExitState[ptState->nState];
    if ( v13 )
      v13(ptState, ptQTask);
    v14 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 54;
    v15 = v14[54];
    ptState->pfState = v15;
    v15(ptState, ptQTask);
    return;
  }
  if ( (igi2_frame.v58 & 0x1000000) != 0 )
  {
    ptQTask[83].tQTaskRefList.ptHead = nullptr;
    v16 = ptState->apfExitState[ptState->nState];
    if ( v16 )
      v16(ptState, ptQTask);
    v17 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 23;
    v18 = v17[23];
    ptState->pfState = v18;
    v18(ptState, ptQTask);
    return;
  }
  if ( (igi2_frame.v58 & 0x2000) != 0 || (ptPrev = (char)ptQTask[50].ptPrev, (ptPrev & 1) == 0) )
  {
    ptPrev = (char)ptQTask[50].ptPrev;
    if ( (ptPrev & 2) != 0 )
    {
      ptQTask[83].tQTaskRefList.ptHead = (struct QReference_s *)1;
      v20 = ptState->apfExitState[ptState->nState];
      if ( v20 )
        v20(ptState, ptQTask);
      v21 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 23;
      v22 = v21[23];
      ptState->pfState = v22;
      v22(ptState, ptQTask);
      return;
    }
  }
  if ( (igi2_frame.v58 & 0x20000000) != 0 && (ptPrev & 4) != 0 )
  {
    igi2_frame.bSignal = 0;
    qmemcpy(&igi2_frame.tReal64x3, &ptQTask[1], sizeof(igi2_frame.tReal64x3));
    *(_DWORD *)&ptQTask[32].eQTaskType = 2;
    Human_ObjectCollision(ptQTask, &igi2_frame.tReal64x3, &igi2_frame.tReal64x3, &igi2_frame.tReal32x3, (unsigned int *)&igi2_frame.bSignal);
    v23 = (igi2_frame.bSignal & 4) == 0;
    *(_DWORD *)&ptQTask[32].eQTaskType = 0;
    if ( v23 )
    {
      v24 = ptState->apfExitState[ptState->nState];
      if ( v24 )
        v24(ptState, ptQTask);
      v25 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 75;
      v26 = v25[75];
      ptState->pfState = v26;
      v26(ptState, ptQTask);
      return;
    }
    v3 = igi2_frame.v58;
    v2 = ptQTask;
  }
  if ( (ptState->bSignal & 0x40000) != 0 )
  {
    if ( (v3 & 0x80u) != 0 )
    {
      v27 = ptState->apfExitState[ptState->nState];
      if ( v27 )
        v27(ptState, v2);
      v28 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 11;
      v29 = v28[11];
      ptState->pfState = v29;
      v29(ptState, v2);
      return;
    }
    if ( (v3 & 0x100) != 0 )
    {
      v30 = ptState->apfExitState[ptState->nState];
      if ( v30 )
        v30(ptState, v2);
      v31 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 14;
      v32 = v31[14];
      ptState->pfState = v32;
      v32(ptState, v2);
      return;
    }
    if ( (v3 & 0x40) != 0 )
    {
      v33 = ptState->apfExitState[ptState->nState];
      if ( v33 )
        v33(ptState, v2);
      v34 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 17;
      v35 = v34[17];
      ptState->pfState = v35;
      v35(ptState, v2);
      return;
    }
    if ( (v3 & 0x20) != 0 )
    {
      v36 = ptState->apfExitState[ptState->nState];
      if ( v36 )
        v36(ptState, v2);
      v37 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 18;
      v38 = v37[18];
      ptState->pfState = v38;
      v38(ptState, v2);
      return;
    }
    goto LABEL_67;
  }
  if ( (v3 & 0x80u) == 0 )
  {
    if ( (v3 & 0x100) != 0 )
    {
      v42 = ptState->apfExitState[ptState->nState];
      if ( v42 )
        v42(ptState, v2);
      v43 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 6;
      v44 = v43[6];
      ptState->pfState = v44;
      v44(ptState, v2);
    }
    else if ( (v3 & 0x40) != 0 )
    {
      v45 = ptState->apfExitState[ptState->nState];
      if ( v45 )
        v45(ptState, v2);
      v46 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 9;
      v47 = v46[9];
      ptState->pfState = v47;
      v47(ptState, v2);
    }
    else
    {
      if ( (v3 & 0x20) == 0 )
      {
LABEL_67:
        if ( *(float *)&v2[20].tQTaskChildren.ptHead != 0.0
          && *(float *)&v2[13].eQTaskType == 0.0
          && ((int)v2[50].ptPrev & 8) != 0 )
        {
          v51 = ptState->apfExitState[ptState->nState];
          if ( v51 )
            v51(ptState, v2);
          v52 = ptState->apfState;
          ptState->nPreviousState = ptState->nState;
          ptState->nState = 36;
          v53 = v52[36];
          ptState->pfState = v53;
          v53(ptState, v2);
        }
        else
        {
          if ( (v3 & 1) != 0 )
            v2[81].tQTaskChildren.ptMiddle = (struct QTask_s *)1;
          if ( v2[81].tQTaskChildren.ptMiddle && (v3 & 0x8000000) == 0 )
          {
            v54 = ptState->apfExitState[ptState->nState];
            if ( v54 )
              v54(ptState, v2);
            v55 = ptState->apfState;
            ptState->nPreviousState = ptState->nState;
            ptState->nState = 0;
            v56 = *v55;
            ptState->pfState = *v55;
            v56(ptState, v2);
          }
        }
        return;
      }
      v48 = ptState->apfExitState[ptState->nState];
      if ( v48 )
        v48(ptState, v2);
      v49 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 10;
      v50 = v49[10];
      ptState->pfState = v50;
      v50(ptState, v2);
    }
  }
  else
  {
    v39 = ptState->apfExitState[ptState->nState];
    if ( v39 )
      v39(ptState, v2);
    v40 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 3;
    v41 = v40[3];
    ptState->pfState = v41;
    v41(ptState, v2);
  }
}

// source: j/0/human/humanplayer.c:5399  [size~]
void __cdecl HumanPlayer_InitStateRunForward(struct State_s *ptState, struct QTask_s *ptQTask)
{
  int v2; // edx
  int nPreviousState; // ecx
  struct QTask_s *ptTail; // eax
  struct QTask_s *ptParent; // ecx
  double v6; // st7
  struct QTask_s *v7; // eax
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *v10; // ecx
  double v11; // st7
  double v12; // st6
  int v13; // [esp+10h] [ebp-8h]

  v2 = 0;
  *(_DWORD *)&ptQTask[32].eQTaskType = 0;
  nPreviousState = ptState->nPreviousState;
  switch ( nPreviousState )
  {
    case 4:
    case 5:
    case 11:
    case 26:
      ptTail = ptQTask[34].tQTaskChildren.ptTail;
      ptParent = ptTail[1].ptParent;
      if ( ptParent )
        v6 = (double)(int)ptTail[1].tQTaskRefList.ptMiddle / (double)(int)ptParent->tQTaskChildren.ptTail;
      else
        v6 = 0.0;
      v7 = ptTail[1].ptParent;
      if ( v7 )
        v13 = (int)v7->tQTaskChildren.ptTail;
      else
        v13 = 0;
      v2 = (__int64)((double)v13 * v6);
      goto LABEL_9;
    default:
      if ( nPreviousState == 36 )
        HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, 0, 0.0);
      else
LABEL_9:
        HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, v2, 0.20000000298023224);
      ptNext = ptQTask[33].ptNext;
      ptQTask[77].ptParent = (struct QTask_s *)3;
      ptPrev = ptNext[1].ptPrev;
      if ( ptPrev && (v10 = ptPrev->tQTaskChildren.ptTail) != nullptr )
      {
        ptQTask[77].tQTaskChildren.ptHead = (struct QTask_s *)1;
        v11 = *(float *)&v10[21].ptPrev;
        ptQTask[77].tQTaskChildren.ptMiddle = v10[21].ptPrev;
        v12 = *(float *)&ptQTask[43].ptParent;
        if ( v12 < 0.0 )
          v12 = -v12;
        *(float *)&ptQTask[77].tQTaskChildren.ptMiddle = v12 * *(float *)&v10[21].ptParent * 3.0 + v11;
        ptState->pfState = HumanPlayer_RunStateRunForward;
      }
      else
      {
        ptQTask[77].tQTaskChildren.ptHead = nullptr;
        ptQTask[77].tQTaskChildren.ptMiddle = nullptr;
        ptState->pfState = HumanPlayer_RunStateRunForward;
      }
      return;
  }
}

// source: j/0/human/humanplayer.c:5447  [anchor-mhash]
void __cdecl HumanPlayer_RunStateRunForward(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptHumanPlayer; };
    struct { char igi2_o1[36]; struct real32x3_t tReal32x3; };
    struct { char igi2_o2[48]; struct real64x3_t tReal64x3; };
    char igi2_extent[76];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v2; // ebp
  unsigned int bSignal; // ecx
  void (__cdecl *v4)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v6)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v7)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v8)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v9)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v10)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v11)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v12)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v13)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v14)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v15)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v16)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v17)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v18)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v19)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v20)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v21)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v22)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v23)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v24)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v25)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v26)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v27)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v28)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v29)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v30)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v31)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v32)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v33)(struct State_s *, struct QTask_s *); // eax
  char ptPrev; // al
  void (__cdecl *v35)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v36)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v37)(struct State_s *, struct QTask_s *); // eax
  bool v38; // zf
  void (__cdecl *v39)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v40)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v41)(struct State_s *, struct QTask_s *); // eax

  v2 = ptQTask;
  Human_RunningControl(ptQTask, HUMANPLAYER_RUNFORWARD_ANIMTIMESCALE);
  igi2_frame.ptHumanPlayer = *(float *)&v2[81].ptNext * 890.743408203125;
  HumanPlayer_MoveOnGround((struct HumanPlayer_t *)v2, igi2_frame.ptHumanPlayer, 118.76579284667969, 0.0, 63.62453079223633);
  bSignal = ptState->bSignal;
  if ( (bSignal & 0x800000) != 0 )
  {
    v4 = ptState->apfExitState[ptState->nState];
    if ( v4 )
      v4(ptState, v2);
    apfState = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 21;
    v6 = apfState[21];
    ptState->pfState = v6;
    v6(ptState, v2);
  }
  else if ( (bSignal & 2) != 0 )
  {
    if ( (bSignal & 0x20000) != 0 )
    {
      v10 = ptState->apfExitState[ptState->nState];
      if ( v10 )
        v10(ptState, v2);
      v11 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 55;
      v12 = v11[55];
      ptState->pfState = v12;
      v12(ptState, v2);
    }
    else if ( (bSignal & 0x10000) != 0 )
    {
      v13 = ptState->apfExitState[ptState->nState];
      if ( v13 )
        v13(ptState, v2);
      v14 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 54;
      v15 = v14[54];
      ptState->pfState = v15;
      v15(ptState, v2);
    }
    else if ( (bSignal & 0x40000) != 0 )
    {
      v16 = ptState->apfExitState[ptState->nState];
      if ( v16 )
        v16(ptState, v2);
      v17 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 11;
      v18 = v17[11];
      ptState->pfState = v18;
      v18(ptState, v2);
    }
    else if ( *(float *)&v2[20].tQTaskChildren.ptHead != 0.0
           && *(float *)&v2[13].eQTaskType == 0.0
           && ((int)v2[50].ptPrev & 8) != 0 )
    {
      v19 = ptState->apfExitState[ptState->nState];
      if ( v19 )
        v19(ptState, v2);
      v20 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 36;
      v21 = v20[36];
      ptState->pfState = v21;
      v21(ptState, v2);
    }
    else if ( (bSignal & 0x40) != 0 )
    {
      v22 = ptState->apfExitState[ptState->nState];
      if ( v22 )
        v22(ptState, v2);
      v23 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 4;
      v24 = v23[4];
      ptState->pfState = v24;
      v24(ptState, v2);
    }
    else if ( (bSignal & 0x20) != 0 )
    {
      v25 = ptState->apfExitState[ptState->nState];
      if ( v25 )
        v25(ptState, v2);
      v26 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 5;
      v27 = v26[5];
      ptState->pfState = v27;
      v27(ptState, v2);
    }
    else if ( (bSignal & 0x80u) != 0 )
    {
      if ( (bSignal & 0x1000000) != 0 )
      {
        v2[83].tQTaskRefList.ptHead = nullptr;
        v31 = ptState->apfExitState[ptState->nState];
        if ( v31 )
          v31(ptState, v2);
        v32 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 23;
        v33 = v32[23];
        ptState->pfState = v33;
        v33(ptState, v2);
      }
      else if ( ((bSignal & 0x2000) != 0 || (ptPrev = (char)v2[50].ptPrev, (ptPrev & 1) == 0))
             && (ptPrev = (char)v2[50].ptPrev, (ptPrev & 2) != 0) )
      {
        v2[83].tQTaskRefList.ptHead = (struct QReference_s *)1;
        v35 = ptState->apfExitState[ptState->nState];
        if ( v35 )
          v35(ptState, v2);
        v36 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 23;
        v37 = v36[23];
        ptState->pfState = v37;
        v37(ptState, v2);
      }
      else if ( (bSignal & 0x20000000) != 0
             && (ptPrev & 4) != 0
             && (ptQTask = nullptr,
                 qmemcpy(&igi2_frame.tReal64x3, &v2[1], sizeof(igi2_frame.tReal64x3)),
                 *(_DWORD *)&v2[32].eQTaskType = 2,
                 Human_ObjectCollision(v2, &igi2_frame.tReal64x3, &igi2_frame.tReal64x3, &igi2_frame.tReal32x3, (unsigned int *)&ptQTask),
                 v38 = ((unsigned __int8)ptQTask & 4) == 0,
                 *(_DWORD *)&v2[32].eQTaskType = 0,
                 v38) )
      {
        v39 = ptState->apfExitState[ptState->nState];
        if ( v39 )
          v39(ptState, v2);
        v40 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 75;
        v41 = v40[75];
        ptState->pfState = v41;
        v41(ptState, v2);
      }
      else
      {
        HumanPlayer_SendWalkEvent(v2, true);
      }
    }
    else
    {
      v28 = ptState->apfExitState[ptState->nState];
      if ( v28 )
        v28(ptState, v2);
      v29 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 0;
      v30 = *v29;
      ptState->pfState = v30;
      v30(ptState, v2);
    }
  }
  else
  {
    v7 = ptState->apfExitState[ptState->nState];
    if ( v7 )
      v7(ptState, v2);
    v8 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 37;
    v9 = v8[37];
    ptState->pfState = v9;
    v9(ptState, v2);
  }
}

// source: j/0/human/humanplayer.c:5532  [size]
void __cdecl HumanPlayer_InitStateRunForwardRight(struct State_s *ptState, struct QTask_s *ptQTask)
{
  int nPreviousState; // eax
  struct QTask_s *ptTail; // eax
  struct QTask_s *ptParent; // ecx
  double v5; // st7
  struct QTask_s *v6; // eax
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *v9; // ecx
  double v10; // st7
  double v11; // st6
  int v12; // [esp+10h] [ebp-8h]

  *(_DWORD *)&ptQTask[32].eQTaskType = 0;
  nPreviousState = ptState->nPreviousState;
  if ( nPreviousState == 3 || nPreviousState == 12 || nPreviousState == 27 )
  {
    ptTail = ptQTask[34].tQTaskChildren.ptTail;
    ptParent = ptTail[1].ptParent;
    if ( ptParent )
      v5 = (double)(int)ptTail[1].tQTaskRefList.ptMiddle / (double)(int)ptParent->tQTaskChildren.ptTail;
    else
      v5 = 0.0;
    v6 = ptTail[1].ptParent;
    if ( v6 )
      v12 = (int)v6->tQTaskChildren.ptTail;
    else
      v12 = 0;
    HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, (__int64)((double)v12 * v5), 0.20000000298023224);
  }
  else
  {
    HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, 0, 0.20000000298023224);
  }
  ptNext = ptQTask[33].ptNext;
  ptQTask[77].ptParent = (struct QTask_s *)3;
  ptPrev = ptNext[1].ptPrev;
  if ( ptPrev && (v9 = ptPrev->tQTaskChildren.ptTail) != nullptr )
  {
    ptQTask[77].tQTaskChildren.ptHead = (struct QTask_s *)1;
    v10 = *(float *)&v9[21].ptPrev;
    ptQTask[77].tQTaskChildren.ptMiddle = v9[21].ptPrev;
    v11 = *(float *)&ptQTask[43].ptParent;
    if ( v11 < 0.0 )
      v11 = -v11;
    *(float *)&ptQTask[77].tQTaskChildren.ptMiddle = v11 * *(float *)&v9[21].ptParent * 3.0 + v10;
    ptState->pfState = HumanPlayer_RunStateRunForwardRight;
  }
  else
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    ptQTask[77].tQTaskChildren.ptMiddle = nullptr;
    ptState->pfState = HumanPlayer_RunStateRunForwardRight;
  }
}

// source: j/0/human/humanplayer.c:5572  [size]
void __cdecl HumanPlayer_RunStateRunForwardRight(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptHumanPlayer; };
    struct { char igi2_o1[8]; float vMaxYDelta; };
    struct { char igi2_o2[36]; struct real32x3_t tReal32x3; };
    struct { char igi2_o3[48]; struct real64x3_t tReal64x3; };
    char igi2_extent[76];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v2; // ebp
  unsigned int bSignal; // ecx
  void (__cdecl *v4)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v6)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v7)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v8)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v9)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v10)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v11)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v12)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v13)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v14)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v15)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v16)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v17)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v18)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v19)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v20)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v21)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v22)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v23)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v24)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v25)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v26)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v27)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v28)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v29)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v30)(struct State_s *, struct QTask_s *); // eax
  char ptPrev; // al
  void (__cdecl *v32)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v33)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v34)(struct State_s *, struct QTask_s *); // eax
  bool v35; // zf
  void (__cdecl *v36)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v37)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v38)(struct State_s *, struct QTask_s *); // eax

  v2 = ptQTask;
  Human_RunningControl(ptQTask, HUMANPLAYER_RUNFORWARDRIGHT_ANIMTIMESCALE);
  igi2_frame.vMaxYDelta = *(float *)&v2[81].ptNext * 477.1839904785156;
  igi2_frame.ptHumanPlayer = *(float *)&v2[81].ptNext * 890.743408203125;
  HumanPlayer_MoveOnGround((struct HumanPlayer_t *)v2, igi2_frame.ptHumanPlayer, 118.76579284667969, igi2_frame.vMaxYDelta, 63.62453079223633);
  bSignal = ptState->bSignal;
  if ( (bSignal & 0x800000) != 0 )
  {
    v4 = ptState->apfExitState[ptState->nState];
    if ( v4 )
      v4(ptState, v2);
    apfState = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 21;
    v6 = apfState[21];
    ptState->pfState = v6;
    v6(ptState, v2);
  }
  else if ( (bSignal & 2) != 0 )
  {
    if ( (bSignal & 0x20000) != 0 )
    {
      v10 = ptState->apfExitState[ptState->nState];
      if ( v10 )
        v10(ptState, v2);
      v11 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 55;
      v12 = v11[55];
      ptState->pfState = v12;
      v12(ptState, v2);
    }
    else if ( (bSignal & 0x10000) != 0 )
    {
      v13 = ptState->apfExitState[ptState->nState];
      if ( v13 )
        v13(ptState, v2);
      v14 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 54;
      v15 = v14[54];
      ptState->pfState = v15;
      v15(ptState, v2);
    }
    else if ( (bSignal & 0x40000) != 0 )
    {
      v16 = ptState->apfExitState[ptState->nState];
      if ( v16 )
        v16(ptState, v2);
      v17 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 12;
      v18 = v17[12];
      ptState->pfState = v18;
      v18(ptState, v2);
    }
    else if ( *(float *)&v2[20].tQTaskChildren.ptHead != 0.0
           && *(float *)&v2[13].eQTaskType == 0.0
           && ((int)v2[50].ptPrev & 8) != 0 )
    {
      v19 = ptState->apfExitState[ptState->nState];
      if ( v19 )
        v19(ptState, v2);
      v20 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 36;
      v21 = v20[36];
      ptState->pfState = v21;
      v21(ptState, v2);
    }
    else if ( (bSignal & 0x80u) != 0 )
    {
      if ( (bSignal & 0x40) != 0 )
      {
        if ( (bSignal & 0x1000000) != 0 )
        {
          v2[83].tQTaskRefList.ptHead = nullptr;
          v28 = ptState->apfExitState[ptState->nState];
          if ( v28 )
            v28(ptState, v2);
          v29 = ptState->apfState;
          ptState->nPreviousState = ptState->nState;
          ptState->nState = 23;
          v30 = v29[23];
          ptState->pfState = v30;
          v30(ptState, v2);
        }
        else if ( ((bSignal & 0x2000) != 0 || (ptPrev = (char)v2[50].ptPrev, (ptPrev & 1) == 0))
               && (ptPrev = (char)v2[50].ptPrev, (ptPrev & 2) != 0) )
        {
          v2[83].tQTaskRefList.ptHead = (struct QReference_s *)1;
          v32 = ptState->apfExitState[ptState->nState];
          if ( v32 )
            v32(ptState, v2);
          v33 = ptState->apfState;
          ptState->nPreviousState = ptState->nState;
          ptState->nState = 23;
          v34 = v33[23];
          ptState->pfState = v34;
          v34(ptState, v2);
        }
        else if ( (bSignal & 0x20000000) != 0
               && (ptPrev & 4) != 0
               && (qmemcpy(&igi2_frame.tReal64x3, &v2[1], sizeof(igi2_frame.tReal64x3)),
                   ptQTask = nullptr,
                   *(_DWORD *)&v2[32].eQTaskType = 2,
                   Human_ObjectCollision(v2, &igi2_frame.tReal64x3, &igi2_frame.tReal64x3, &igi2_frame.tReal32x3, (unsigned int *)&ptQTask),
                   v35 = ((unsigned __int8)ptQTask & 4) == 0,
                   *(_DWORD *)&v2[32].eQTaskType = 0,
                   v35) )
        {
          v36 = ptState->apfExitState[ptState->nState];
          if ( v36 )
            v36(ptState, v2);
          v37 = ptState->apfState;
          ptState->nPreviousState = ptState->nState;
          ptState->nState = 75;
          v38 = v37[75];
          ptState->pfState = v38;
          v38(ptState, v2);
        }
        else
        {
          HumanPlayer_SendWalkEvent(v2, true);
        }
      }
      else
      {
        v25 = ptState->apfExitState[ptState->nState];
        if ( v25 )
          v25(ptState, v2);
        v26 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 3;
        v27 = v26[3];
        ptState->pfState = v27;
        v27(ptState, v2);
      }
    }
    else
    {
      v22 = ptState->apfExitState[ptState->nState];
      if ( v22 )
        v22(ptState, v2);
      v23 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 9;
      v24 = v23[9];
      ptState->pfState = v24;
      v24(ptState, v2);
    }
  }
  else
  {
    v7 = ptState->apfExitState[ptState->nState];
    if ( v7 )
      v7(ptState, v2);
    v8 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 37;
    v9 = v8[37];
    ptState->pfState = v9;
    v9(ptState, v2);
  }
}

// source: j/0/human/humanplayer.c:5655  [size]
void __cdecl HumanPlayer_InitStateRunForwardLeft(struct State_s *ptState, struct QTask_s *ptQTask)
{
  int nPreviousState; // eax
  struct QTask_s *ptTail; // eax
  struct QTask_s *ptParent; // ecx
  double v5; // st7
  struct QTask_s *v6; // eax
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *v9; // ecx
  double v10; // st7
  double v11; // st6
  int v12; // [esp+10h] [ebp-8h]

  *(_DWORD *)&ptQTask[32].eQTaskType = 0;
  nPreviousState = ptState->nPreviousState;
  if ( nPreviousState == 3 || nPreviousState == 13 || nPreviousState == 28 )
  {
    ptTail = ptQTask[34].tQTaskChildren.ptTail;
    ptParent = ptTail[1].ptParent;
    if ( ptParent )
      v5 = (double)(int)ptTail[1].tQTaskRefList.ptMiddle / (double)(int)ptParent->tQTaskChildren.ptTail;
    else
      v5 = 0.0;
    v6 = ptTail[1].ptParent;
    if ( v6 )
      v12 = (int)v6->tQTaskChildren.ptTail;
    else
      v12 = 0;
    HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, (__int64)((double)v12 * v5), 0.20000000298023224);
  }
  else
  {
    HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, 0, 0.20000000298023224);
  }
  ptNext = ptQTask[33].ptNext;
  ptQTask[77].ptParent = (struct QTask_s *)3;
  ptPrev = ptNext[1].ptPrev;
  if ( ptPrev && (v9 = ptPrev->tQTaskChildren.ptTail) != nullptr )
  {
    ptQTask[77].tQTaskChildren.ptHead = (struct QTask_s *)1;
    v10 = *(float *)&v9[21].ptPrev;
    ptQTask[77].tQTaskChildren.ptMiddle = v9[21].ptPrev;
    v11 = *(float *)&ptQTask[43].ptParent;
    if ( v11 < 0.0 )
      v11 = -v11;
    *(float *)&ptQTask[77].tQTaskChildren.ptMiddle = v11 * *(float *)&v9[21].ptParent * 3.0 + v10;
    ptState->pfState = HumanPlayer_RunStateRunForwardLeft;
  }
  else
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    ptQTask[77].tQTaskChildren.ptMiddle = nullptr;
    ptState->pfState = HumanPlayer_RunStateRunForwardLeft;
  }
}

// source: j/0/human/humanplayer.c:5695  [size]
void __cdecl HumanPlayer_RunStateRunForwardLeft(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptHumanPlayer; };
    struct { char igi2_o1[8]; float vMaxYDelta; };
    struct { char igi2_o2[36]; struct real32x3_t tReal32x3; };
    struct { char igi2_o3[48]; struct real64x3_t tReal64x3; };
    char igi2_extent[76];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v2; // ebp
  unsigned int bSignal; // ecx
  void (__cdecl *v4)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v6)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v7)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v8)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v9)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v10)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v11)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v12)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v13)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v14)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v15)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v16)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v17)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v18)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v19)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v20)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v21)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v22)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v23)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v24)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v25)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v26)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v27)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v28)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v29)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v30)(struct State_s *, struct QTask_s *); // eax
  char ptPrev; // al
  void (__cdecl *v32)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v33)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v34)(struct State_s *, struct QTask_s *); // eax
  bool v35; // zf
  void (__cdecl *v36)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v37)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v38)(struct State_s *, struct QTask_s *); // eax

  v2 = ptQTask;
  Human_RunningControl(ptQTask, HUMANPLAYER_RUNFORWARDLEFT_ANIMTIMESCALE);
  igi2_frame.vMaxYDelta = *(float *)&v2[81].ptNext * -477.1839904785156;
  igi2_frame.ptHumanPlayer = *(float *)&v2[81].ptNext * 890.743408203125;
  HumanPlayer_MoveOnGround((struct HumanPlayer_t *)v2, igi2_frame.ptHumanPlayer, 118.76579284667969, igi2_frame.vMaxYDelta, 63.62453079223633);
  bSignal = ptState->bSignal;
  if ( (bSignal & 0x800000) != 0 )
  {
    v4 = ptState->apfExitState[ptState->nState];
    if ( v4 )
      v4(ptState, v2);
    apfState = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 21;
    v6 = apfState[21];
    ptState->pfState = v6;
    v6(ptState, v2);
  }
  else if ( (bSignal & 2) != 0 )
  {
    if ( (bSignal & 0x20000) != 0 )
    {
      v10 = ptState->apfExitState[ptState->nState];
      if ( v10 )
        v10(ptState, v2);
      v11 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 55;
      v12 = v11[55];
      ptState->pfState = v12;
      v12(ptState, v2);
    }
    else if ( (bSignal & 0x10000) != 0 )
    {
      v13 = ptState->apfExitState[ptState->nState];
      if ( v13 )
        v13(ptState, v2);
      v14 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 54;
      v15 = v14[54];
      ptState->pfState = v15;
      v15(ptState, v2);
    }
    else if ( (bSignal & 0x40000) != 0 )
    {
      v16 = ptState->apfExitState[ptState->nState];
      if ( v16 )
        v16(ptState, v2);
      v17 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 13;
      v18 = v17[13];
      ptState->pfState = v18;
      v18(ptState, v2);
    }
    else if ( *(float *)&v2[20].tQTaskChildren.ptHead != 0.0
           && *(float *)&v2[13].eQTaskType == 0.0
           && ((int)v2[50].ptPrev & 8) != 0 )
    {
      v19 = ptState->apfExitState[ptState->nState];
      if ( v19 )
        v19(ptState, v2);
      v20 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 36;
      v21 = v20[36];
      ptState->pfState = v21;
      v21(ptState, v2);
    }
    else if ( (bSignal & 0x80u) != 0 )
    {
      if ( (bSignal & 0x20) != 0 )
      {
        if ( (bSignal & 0x1000000) != 0 )
        {
          v2[83].tQTaskRefList.ptHead = nullptr;
          v28 = ptState->apfExitState[ptState->nState];
          if ( v28 )
            v28(ptState, v2);
          v29 = ptState->apfState;
          ptState->nPreviousState = ptState->nState;
          ptState->nState = 23;
          v30 = v29[23];
          ptState->pfState = v30;
          v30(ptState, v2);
        }
        else if ( ((bSignal & 0x2000) != 0 || (ptPrev = (char)v2[50].ptPrev, (ptPrev & 1) == 0))
               && (ptPrev = (char)v2[50].ptPrev, (ptPrev & 2) != 0) )
        {
          v2[83].tQTaskRefList.ptHead = (struct QReference_s *)1;
          v32 = ptState->apfExitState[ptState->nState];
          if ( v32 )
            v32(ptState, v2);
          v33 = ptState->apfState;
          ptState->nPreviousState = ptState->nState;
          ptState->nState = 23;
          v34 = v33[23];
          ptState->pfState = v34;
          v34(ptState, v2);
        }
        else if ( (bSignal & 0x20000000) != 0
               && (ptPrev & 4) != 0
               && (qmemcpy(&igi2_frame.tReal64x3, &v2[1], sizeof(igi2_frame.tReal64x3)),
                   ptQTask = nullptr,
                   *(_DWORD *)&v2[32].eQTaskType = 2,
                   Human_ObjectCollision(v2, &igi2_frame.tReal64x3, &igi2_frame.tReal64x3, &igi2_frame.tReal32x3, (unsigned int *)&ptQTask),
                   v35 = ((unsigned __int8)ptQTask & 4) == 0,
                   *(_DWORD *)&v2[32].eQTaskType = 0,
                   v35) )
        {
          v36 = ptState->apfExitState[ptState->nState];
          if ( v36 )
            v36(ptState, v2);
          v37 = ptState->apfState;
          ptState->nPreviousState = ptState->nState;
          ptState->nState = 75;
          v38 = v37[75];
          ptState->pfState = v38;
          v38(ptState, v2);
        }
        else
        {
          HumanPlayer_SendWalkEvent(v2, true);
        }
      }
      else
      {
        v25 = ptState->apfExitState[ptState->nState];
        if ( v25 )
          v25(ptState, v2);
        v26 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 3;
        v27 = v26[3];
        ptState->pfState = v27;
        v27(ptState, v2);
      }
    }
    else
    {
      v22 = ptState->apfExitState[ptState->nState];
      if ( v22 )
        v22(ptState, v2);
      v23 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 10;
      v24 = v23[10];
      ptState->pfState = v24;
      v24(ptState, v2);
    }
  }
  else
  {
    v7 = ptState->apfExitState[ptState->nState];
    if ( v7 )
      v7(ptState, v2);
    v8 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 37;
    v9 = v8[37];
    ptState->pfState = v9;
    v9(ptState, v2);
  }
}

// source: j/0/human/humanplayer.c:5777  [size~]
void __cdecl HumanPlayer_InitStateRunBackward(struct State_s *ptState, struct QTask_s *ptQTask)
{
  int v2; // edx
  int nPreviousState; // ecx
  struct QTask_s *ptTail; // eax
  struct QTask_s *ptParent; // ecx
  double v6; // st7
  struct QTask_s *v7; // eax
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *v10; // ecx
  double v11; // st7
  double v12; // st6
  int v13; // [esp+10h] [ebp-8h]

  v2 = 0;
  *(_DWORD *)&ptQTask[32].eQTaskType = 0;
  nPreviousState = ptState->nPreviousState;
  switch ( nPreviousState )
  {
    case 7:
    case 8:
    case 14:
    case 29:
      ptTail = ptQTask[34].tQTaskChildren.ptTail;
      ptParent = ptTail[1].ptParent;
      if ( ptParent )
        v6 = (double)(int)ptTail[1].tQTaskRefList.ptMiddle / (double)(int)ptParent->tQTaskChildren.ptTail;
      else
        v6 = 0.0;
      v7 = ptTail[1].ptParent;
      if ( v7 )
        v13 = (int)v7->tQTaskChildren.ptTail;
      else
        v13 = 0;
      v2 = (__int64)((double)v13 * v6);
      goto LABEL_9;
    default:
      if ( nPreviousState == 36 )
        HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, 0, 0.0);
      else
LABEL_9:
        HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, v2, 0.20000000298023224);
      ptNext = ptQTask[33].ptNext;
      ptQTask[77].ptParent = (struct QTask_s *)3;
      ptPrev = ptNext[1].ptPrev;
      if ( ptPrev && (v10 = ptPrev->tQTaskChildren.ptTail) != nullptr )
      {
        ptQTask[77].tQTaskChildren.ptHead = (struct QTask_s *)1;
        v11 = *(float *)&v10[21].ptPrev;
        ptQTask[77].tQTaskChildren.ptMiddle = v10[21].ptPrev;
        v12 = *(float *)&ptQTask[43].ptParent;
        if ( v12 < 0.0 )
          v12 = -v12;
        *(float *)&ptQTask[77].tQTaskChildren.ptMiddle = v12 * *(float *)&v10[21].ptParent * 3.0 + v11;
        ptState->pfState = HumanPlayer_RunStateRunBackward;
      }
      else
      {
        ptQTask[77].tQTaskChildren.ptHead = nullptr;
        ptQTask[77].tQTaskChildren.ptMiddle = nullptr;
        ptState->pfState = HumanPlayer_RunStateRunBackward;
      }
      return;
  }
}

// source: j/0/human/humanplayer.c:5825  [anchor-mhash]
void __cdecl HumanPlayer_RunStateRunBackward(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptHumanPlayer; };
    struct { char igi2_o1[36]; struct real32x3_t tReal32x3; };
    struct { char igi2_o2[48]; struct real64x3_t tReal64x3; };
    char igi2_extent[76];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v2; // ebx
  unsigned int bSignal; // ecx
  void (__cdecl *v4)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v6)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v7)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v8)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v9)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v10)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v11)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v12)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v13)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v14)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v15)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v16)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v17)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v18)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v19)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v20)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v21)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v22)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v23)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v24)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v25)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v26)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v27)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v28)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v29)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v30)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v31)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v32)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v33)(struct State_s *, struct QTask_s *); // eax
  char ptPrev; // al
  void (__cdecl *v35)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v36)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v37)(struct State_s *, struct QTask_s *); // eax
  bool v38; // zf
  void (__cdecl *v39)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v40)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v41)(struct State_s *, struct QTask_s *); // eax

  v2 = ptQTask;
  Human_RunningControl(ptQTask, HUMANPLAYER_RUNBACKWARD_ANIMTIMESCALE);
  igi2_frame.ptHumanPlayer = *(float *)&v2[81].ptNext * -681.9840087890625;
  HumanPlayer_MoveOnGround((struct HumanPlayer_t *)v2, igi2_frame.ptHumanPlayer, 90.93119812011719, 0.0, 63.62453079223633);
  bSignal = ptState->bSignal;
  if ( (bSignal & 0x800000) != 0 )
  {
    v4 = ptState->apfExitState[ptState->nState];
    if ( v4 )
      v4(ptState, v2);
    apfState = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 21;
    v6 = apfState[21];
    ptState->pfState = v6;
    v6(ptState, v2);
  }
  else if ( (bSignal & 2) != 0 )
  {
    if ( (bSignal & 0x20000) != 0 )
    {
      v10 = ptState->apfExitState[ptState->nState];
      if ( v10 )
        v10(ptState, v2);
      v11 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 55;
      v12 = v11[55];
      ptState->pfState = v12;
      v12(ptState, v2);
    }
    else if ( (bSignal & 0x10000) != 0 )
    {
      v13 = ptState->apfExitState[ptState->nState];
      if ( v13 )
        v13(ptState, v2);
      v14 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 54;
      v15 = v14[54];
      ptState->pfState = v15;
      v15(ptState, v2);
    }
    else if ( (bSignal & 0x40000) != 0 )
    {
      v16 = ptState->apfExitState[ptState->nState];
      if ( v16 )
        v16(ptState, v2);
      v17 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 14;
      v18 = v17[14];
      ptState->pfState = v18;
      v18(ptState, v2);
    }
    else if ( *(float *)&v2[20].tQTaskChildren.ptHead != 0.0
           && *(float *)&v2[13].eQTaskType == 0.0
           && ((int)v2[50].ptPrev & 8) != 0 )
    {
      v19 = ptState->apfExitState[ptState->nState];
      if ( v19 )
        v19(ptState, v2);
      v20 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 36;
      v21 = v20[36];
      ptState->pfState = v21;
      v21(ptState, v2);
    }
    else if ( (bSignal & 0x40) != 0 )
    {
      v22 = ptState->apfExitState[ptState->nState];
      if ( v22 )
        v22(ptState, v2);
      v23 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 7;
      v24 = v23[7];
      ptState->pfState = v24;
      v24(ptState, v2);
    }
    else if ( (bSignal & 0x20) != 0 )
    {
      v25 = ptState->apfExitState[ptState->nState];
      if ( v25 )
        v25(ptState, v2);
      v26 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 8;
      v27 = v26[8];
      ptState->pfState = v27;
      v27(ptState, v2);
    }
    else if ( (bSignal & 0x100) != 0 )
    {
      if ( (bSignal & 0x1000000) != 0 )
      {
        v2[83].tQTaskRefList.ptHead = nullptr;
        v31 = ptState->apfExitState[ptState->nState];
        if ( v31 )
          v31(ptState, v2);
        v32 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 23;
        v33 = v32[23];
        ptState->pfState = v33;
        v33(ptState, v2);
      }
      else if ( ((bSignal & 0x2000) != 0 || (ptPrev = (char)v2[50].ptPrev, (ptPrev & 1) == 0))
             && (ptPrev = (char)v2[50].ptPrev, (ptPrev & 2) != 0) )
      {
        v2[83].tQTaskRefList.ptHead = (struct QReference_s *)1;
        v35 = ptState->apfExitState[ptState->nState];
        if ( v35 )
          v35(ptState, v2);
        v36 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 23;
        v37 = v36[23];
        ptState->pfState = v37;
        v37(ptState, v2);
      }
      else if ( (bSignal & 0x20000000) != 0
             && (ptPrev & 4) != 0
             && (ptQTask = nullptr,
                 qmemcpy(&igi2_frame.tReal64x3, &v2[1], sizeof(igi2_frame.tReal64x3)),
                 *(_DWORD *)&v2[32].eQTaskType = 2,
                 Human_ObjectCollision(v2, &igi2_frame.tReal64x3, &igi2_frame.tReal64x3, &igi2_frame.tReal32x3, (unsigned int *)&ptQTask),
                 v38 = ((unsigned __int8)ptQTask & 4) == 0,
                 *(_DWORD *)&v2[32].eQTaskType = 0,
                 v38) )
      {
        v39 = ptState->apfExitState[ptState->nState];
        if ( v39 )
          v39(ptState, v2);
        v40 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 75;
        v41 = v40[75];
        ptState->pfState = v41;
        v41(ptState, v2);
      }
      else
      {
        HumanPlayer_SendWalkEvent(v2, true);
      }
    }
    else
    {
      v28 = ptState->apfExitState[ptState->nState];
      if ( v28 )
        v28(ptState, v2);
      v29 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 0;
      v30 = *v29;
      ptState->pfState = v30;
      v30(ptState, v2);
    }
  }
  else
  {
    v7 = ptState->apfExitState[ptState->nState];
    if ( v7 )
      v7(ptState, v2);
    v8 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 37;
    v9 = v8[37];
    ptState->pfState = v9;
    v9(ptState, v2);
  }
}

// source: j/0/human/humanplayer.c:5909  [size]
void __cdecl HumanPlayer_InitStateRunBackwardRight(struct State_s *ptState, struct QTask_s *ptQTask)
{
  int nPreviousState; // eax
  struct QTask_s *ptTail; // eax
  struct QTask_s *ptParent; // ecx
  double v5; // st7
  struct QTask_s *v6; // eax
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *v9; // ecx
  double v10; // st7
  double v11; // st6
  int v12; // [esp+10h] [ebp-8h]

  *(_DWORD *)&ptQTask[32].eQTaskType = 0;
  nPreviousState = ptState->nPreviousState;
  if ( nPreviousState == 6 || nPreviousState == 15 || nPreviousState == 30 )
  {
    ptTail = ptQTask[34].tQTaskChildren.ptTail;
    ptParent = ptTail[1].ptParent;
    if ( ptParent )
      v5 = (double)(int)ptTail[1].tQTaskRefList.ptMiddle / (double)(int)ptParent->tQTaskChildren.ptTail;
    else
      v5 = 0.0;
    v6 = ptTail[1].ptParent;
    if ( v6 )
      v12 = (int)v6->tQTaskChildren.ptTail;
    else
      v12 = 0;
    HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, (__int64)((double)v12 * v5), 0.20000000298023224);
  }
  else
  {
    HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, 0, 0.20000000298023224);
  }
  ptNext = ptQTask[33].ptNext;
  ptQTask[77].ptParent = (struct QTask_s *)3;
  ptPrev = ptNext[1].ptPrev;
  if ( ptPrev && (v9 = ptPrev->tQTaskChildren.ptTail) != nullptr )
  {
    ptQTask[77].tQTaskChildren.ptHead = (struct QTask_s *)1;
    v10 = *(float *)&v9[21].ptPrev;
    ptQTask[77].tQTaskChildren.ptMiddle = v9[21].ptPrev;
    v11 = *(float *)&ptQTask[43].ptParent;
    if ( v11 < 0.0 )
      v11 = -v11;
    *(float *)&ptQTask[77].tQTaskChildren.ptMiddle = v11 * *(float *)&v9[21].ptParent * 3.0 + v10;
    ptState->pfState = HumanPlayer_RunStateRunBackwardRight;
  }
  else
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    ptQTask[77].tQTaskChildren.ptMiddle = nullptr;
    ptState->pfState = HumanPlayer_RunStateRunBackwardRight;
  }
}

// source: j/0/human/humanplayer.c:5949  [size]
void __cdecl HumanPlayer_RunStateRunBackwardRight(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptHumanPlayer; };
    struct { char igi2_o1[8]; float vMaxYDelta; };
    struct { char igi2_o2[36]; struct real32x3_t tReal32x3; };
    struct { char igi2_o3[48]; struct real64x3_t tReal64x3; };
    char igi2_extent[76];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v2; // ebp
  unsigned int bSignal; // ecx
  void (__cdecl *v4)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v6)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v7)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v8)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v9)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v10)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v11)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v12)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v13)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v14)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v15)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v16)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v17)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v18)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v19)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v20)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v21)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v22)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v23)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v24)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v25)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v26)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v27)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v28)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v29)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v30)(struct State_s *, struct QTask_s *); // eax
  char ptPrev; // al
  void (__cdecl *v32)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v33)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v34)(struct State_s *, struct QTask_s *); // eax
  bool v35; // zf
  void (__cdecl *v36)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v37)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v38)(struct State_s *, struct QTask_s *); // eax

  v2 = ptQTask;
  Human_RunningControl(ptQTask, HUMANPLAYER_RUNBACKWARDRIGHT_ANIMTIMESCALE);
  igi2_frame.vMaxYDelta = *(float *)&v2[81].ptNext * 477.1839904785156;
  igi2_frame.ptHumanPlayer = *(float *)&v2[81].ptNext * -681.9840087890625;
  HumanPlayer_MoveOnGround((struct HumanPlayer_t *)v2, igi2_frame.ptHumanPlayer, 90.93119812011719, igi2_frame.vMaxYDelta, 63.62453079223633);
  bSignal = ptState->bSignal;
  if ( (bSignal & 0x800000) != 0 )
  {
    v4 = ptState->apfExitState[ptState->nState];
    if ( v4 )
      v4(ptState, v2);
    apfState = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 21;
    v6 = apfState[21];
    ptState->pfState = v6;
    v6(ptState, v2);
  }
  else if ( (bSignal & 2) != 0 )
  {
    if ( (bSignal & 0x20000) != 0 )
    {
      v10 = ptState->apfExitState[ptState->nState];
      if ( v10 )
        v10(ptState, v2);
      v11 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 55;
      v12 = v11[55];
      ptState->pfState = v12;
      v12(ptState, v2);
    }
    else if ( (bSignal & 0x10000) != 0 )
    {
      v13 = ptState->apfExitState[ptState->nState];
      if ( v13 )
        v13(ptState, v2);
      v14 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 54;
      v15 = v14[54];
      ptState->pfState = v15;
      v15(ptState, v2);
    }
    else if ( (bSignal & 0x40000) != 0 )
    {
      v16 = ptState->apfExitState[ptState->nState];
      if ( v16 )
        v16(ptState, v2);
      v17 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 15;
      v18 = v17[15];
      ptState->pfState = v18;
      v18(ptState, v2);
    }
    else if ( *(float *)&v2[20].tQTaskChildren.ptHead != 0.0
           && *(float *)&v2[13].eQTaskType == 0.0
           && ((int)v2[50].ptPrev & 8) != 0 )
    {
      v19 = ptState->apfExitState[ptState->nState];
      if ( v19 )
        v19(ptState, v2);
      v20 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 36;
      v21 = v20[36];
      ptState->pfState = v21;
      v21(ptState, v2);
    }
    else if ( (bSignal & 0x100) != 0 )
    {
      if ( (bSignal & 0x40) != 0 )
      {
        if ( (bSignal & 0x1000000) != 0 )
        {
          v2[83].tQTaskRefList.ptHead = nullptr;
          v28 = ptState->apfExitState[ptState->nState];
          if ( v28 )
            v28(ptState, v2);
          v29 = ptState->apfState;
          ptState->nPreviousState = ptState->nState;
          ptState->nState = 23;
          v30 = v29[23];
          ptState->pfState = v30;
          v30(ptState, v2);
        }
        else if ( ((bSignal & 0x2000) != 0 || (ptPrev = (char)v2[50].ptPrev, (ptPrev & 1) == 0))
               && (ptPrev = (char)v2[50].ptPrev, (ptPrev & 2) != 0) )
        {
          v2[83].tQTaskRefList.ptHead = (struct QReference_s *)1;
          v32 = ptState->apfExitState[ptState->nState];
          if ( v32 )
            v32(ptState, v2);
          v33 = ptState->apfState;
          ptState->nPreviousState = ptState->nState;
          ptState->nState = 23;
          v34 = v33[23];
          ptState->pfState = v34;
          v34(ptState, v2);
        }
        else if ( (bSignal & 0x20000000) != 0
               && (ptPrev & 4) != 0
               && (qmemcpy(&igi2_frame.tReal64x3, &v2[1], sizeof(igi2_frame.tReal64x3)),
                   ptQTask = nullptr,
                   *(_DWORD *)&v2[32].eQTaskType = 2,
                   Human_ObjectCollision(v2, &igi2_frame.tReal64x3, &igi2_frame.tReal64x3, &igi2_frame.tReal32x3, (unsigned int *)&ptQTask),
                   v35 = ((unsigned __int8)ptQTask & 4) == 0,
                   *(_DWORD *)&v2[32].eQTaskType = 0,
                   v35) )
        {
          v36 = ptState->apfExitState[ptState->nState];
          if ( v36 )
            v36(ptState, v2);
          v37 = ptState->apfState;
          ptState->nPreviousState = ptState->nState;
          ptState->nState = 75;
          v38 = v37[75];
          ptState->pfState = v38;
          v38(ptState, v2);
        }
        else
        {
          HumanPlayer_SendWalkEvent(v2, true);
        }
      }
      else
      {
        v25 = ptState->apfExitState[ptState->nState];
        if ( v25 )
          v25(ptState, v2);
        v26 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 6;
        v27 = v26[6];
        ptState->pfState = v27;
        v27(ptState, v2);
      }
    }
    else
    {
      v22 = ptState->apfExitState[ptState->nState];
      if ( v22 )
        v22(ptState, v2);
      v23 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 9;
      v24 = v23[9];
      ptState->pfState = v24;
      v24(ptState, v2);
    }
  }
  else
  {
    v7 = ptState->apfExitState[ptState->nState];
    if ( v7 )
      v7(ptState, v2);
    v8 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 37;
    v9 = v8[37];
    ptState->pfState = v9;
    v9(ptState, v2);
  }
}

// source: j/0/human/humanplayer.c:6031  [size]
void __cdecl HumanPlayer_InitStateRunBackwardLeft(struct State_s *ptState, struct QTask_s *ptQTask)
{
  int nPreviousState; // eax
  struct QTask_s *ptTail; // eax
  struct QTask_s *ptParent; // ecx
  double v5; // st7
  struct QTask_s *v6; // eax
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *v9; // ecx
  double v10; // st7
  double v11; // st6
  int v12; // [esp+10h] [ebp-8h]

  *(_DWORD *)&ptQTask[32].eQTaskType = 0;
  nPreviousState = ptState->nPreviousState;
  if ( nPreviousState == 6 || nPreviousState == 16 || nPreviousState == 31 )
  {
    ptTail = ptQTask[34].tQTaskChildren.ptTail;
    ptParent = ptTail[1].ptParent;
    if ( ptParent )
      v5 = (double)(int)ptTail[1].tQTaskRefList.ptMiddle / (double)(int)ptParent->tQTaskChildren.ptTail;
    else
      v5 = 0.0;
    v6 = ptTail[1].ptParent;
    if ( v6 )
      v12 = (int)v6->tQTaskChildren.ptTail;
    else
      v12 = 0;
    HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, (__int64)((double)v12 * v5), 0.20000000298023224);
  }
  else
  {
    HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, 0, 0.20000000298023224);
  }
  ptNext = ptQTask[33].ptNext;
  ptQTask[77].ptParent = (struct QTask_s *)3;
  ptPrev = ptNext[1].ptPrev;
  if ( ptPrev && (v9 = ptPrev->tQTaskChildren.ptTail) != nullptr )
  {
    ptQTask[77].tQTaskChildren.ptHead = (struct QTask_s *)1;
    v10 = *(float *)&v9[21].ptPrev;
    ptQTask[77].tQTaskChildren.ptMiddle = v9[21].ptPrev;
    v11 = *(float *)&ptQTask[43].ptParent;
    if ( v11 < 0.0 )
      v11 = -v11;
    *(float *)&ptQTask[77].tQTaskChildren.ptMiddle = v11 * *(float *)&v9[21].ptParent * 3.0 + v10;
    ptState->pfState = HumanPlayer_RunStateRunBackwardLeft;
  }
  else
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    ptQTask[77].tQTaskChildren.ptMiddle = nullptr;
    ptState->pfState = HumanPlayer_RunStateRunBackwardLeft;
  }
}

// source: j/0/human/humanplayer.c:6071  [size]
void __cdecl HumanPlayer_RunStateRunBackwardLeft(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptHumanPlayer; };
    struct { char igi2_o1[8]; float vMaxYDelta; };
    struct { char igi2_o2[36]; struct real32x3_t tReal32x3; };
    struct { char igi2_o3[48]; struct real64x3_t tReal64x3; };
    char igi2_extent[76];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v2; // ebp
  unsigned int bSignal; // ecx
  void (__cdecl *v4)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v6)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v7)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v8)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v9)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v10)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v11)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v12)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v13)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v14)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v15)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v16)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v17)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v18)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v19)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v20)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v21)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v22)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v23)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v24)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v25)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v26)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v27)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v28)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v29)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v30)(struct State_s *, struct QTask_s *); // eax
  char ptPrev; // al
  void (__cdecl *v32)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v33)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v34)(struct State_s *, struct QTask_s *); // eax
  bool v35; // zf
  void (__cdecl *v36)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v37)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v38)(struct State_s *, struct QTask_s *); // eax

  v2 = ptQTask;
  Human_RunningControl(ptQTask, HUMANPLAYER_RUNBACKWARDLEFT_ANIMTIMESCALE);
  igi2_frame.vMaxYDelta = *(float *)&v2[81].ptNext * -477.1839904785156;
  igi2_frame.ptHumanPlayer = *(float *)&v2[81].ptNext * -681.9840087890625;
  HumanPlayer_MoveOnGround((struct HumanPlayer_t *)v2, igi2_frame.ptHumanPlayer, 90.93119812011719, igi2_frame.vMaxYDelta, 63.62453079223633);
  bSignal = ptState->bSignal;
  if ( (bSignal & 0x800000) != 0 )
  {
    v4 = ptState->apfExitState[ptState->nState];
    if ( v4 )
      v4(ptState, v2);
    apfState = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 21;
    v6 = apfState[21];
    ptState->pfState = v6;
    v6(ptState, v2);
  }
  else if ( (bSignal & 2) != 0 )
  {
    if ( (bSignal & 0x20000) != 0 )
    {
      v10 = ptState->apfExitState[ptState->nState];
      if ( v10 )
        v10(ptState, v2);
      v11 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 55;
      v12 = v11[55];
      ptState->pfState = v12;
      v12(ptState, v2);
    }
    else if ( (bSignal & 0x10000) != 0 )
    {
      v13 = ptState->apfExitState[ptState->nState];
      if ( v13 )
        v13(ptState, v2);
      v14 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 54;
      v15 = v14[54];
      ptState->pfState = v15;
      v15(ptState, v2);
    }
    else if ( (bSignal & 0x40000) != 0 )
    {
      v16 = ptState->apfExitState[ptState->nState];
      if ( v16 )
        v16(ptState, v2);
      v17 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 16;
      v18 = v17[16];
      ptState->pfState = v18;
      v18(ptState, v2);
    }
    else if ( *(float *)&v2[20].tQTaskChildren.ptHead != 0.0
           && *(float *)&v2[13].eQTaskType == 0.0
           && ((int)v2[50].ptPrev & 8) != 0 )
    {
      v19 = ptState->apfExitState[ptState->nState];
      if ( v19 )
        v19(ptState, v2);
      v20 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 36;
      v21 = v20[36];
      ptState->pfState = v21;
      v21(ptState, v2);
    }
    else if ( (bSignal & 0x100) != 0 )
    {
      if ( (bSignal & 0x20) != 0 )
      {
        if ( (bSignal & 0x1000000) != 0 )
        {
          v2[83].tQTaskRefList.ptHead = nullptr;
          v28 = ptState->apfExitState[ptState->nState];
          if ( v28 )
            v28(ptState, v2);
          v29 = ptState->apfState;
          ptState->nPreviousState = ptState->nState;
          ptState->nState = 23;
          v30 = v29[23];
          ptState->pfState = v30;
          v30(ptState, v2);
        }
        else if ( ((bSignal & 0x2000) != 0 || (ptPrev = (char)v2[50].ptPrev, (ptPrev & 1) == 0))
               && (ptPrev = (char)v2[50].ptPrev, (ptPrev & 2) != 0) )
        {
          v2[83].tQTaskRefList.ptHead = (struct QReference_s *)1;
          v32 = ptState->apfExitState[ptState->nState];
          if ( v32 )
            v32(ptState, v2);
          v33 = ptState->apfState;
          ptState->nPreviousState = ptState->nState;
          ptState->nState = 23;
          v34 = v33[23];
          ptState->pfState = v34;
          v34(ptState, v2);
        }
        else if ( (bSignal & 0x20000000) != 0
               && (ptPrev & 4) != 0
               && (qmemcpy(&igi2_frame.tReal64x3, &v2[1], sizeof(igi2_frame.tReal64x3)),
                   ptQTask = nullptr,
                   *(_DWORD *)&v2[32].eQTaskType = 2,
                   Human_ObjectCollision(v2, &igi2_frame.tReal64x3, &igi2_frame.tReal64x3, &igi2_frame.tReal32x3, (unsigned int *)&ptQTask),
                   v35 = ((unsigned __int8)ptQTask & 4) == 0,
                   *(_DWORD *)&v2[32].eQTaskType = 0,
                   v35) )
        {
          v36 = ptState->apfExitState[ptState->nState];
          if ( v36 )
            v36(ptState, v2);
          v37 = ptState->apfState;
          ptState->nPreviousState = ptState->nState;
          ptState->nState = 75;
          v38 = v37[75];
          ptState->pfState = v38;
          v38(ptState, v2);
        }
        else
        {
          HumanPlayer_SendWalkEvent(v2, true);
        }
      }
      else
      {
        v25 = ptState->apfExitState[ptState->nState];
        if ( v25 )
          v25(ptState, v2);
        v26 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 6;
        v27 = v26[6];
        ptState->pfState = v27;
        v27(ptState, v2);
      }
    }
    else
    {
      v22 = ptState->apfExitState[ptState->nState];
      if ( v22 )
        v22(ptState, v2);
      v23 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 10;
      v24 = v23[10];
      ptState->pfState = v24;
      v24(ptState, v2);
    }
  }
  else
  {
    v7 = ptState->apfExitState[ptState->nState];
    if ( v7 )
      v7(ptState, v2);
    v8 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 37;
    v9 = v8[37];
    ptState->pfState = v9;
    v9(ptState, v2);
  }
}

// source: j/0/human/humanplayer.c:6153  [size]
void __cdecl HumanPlayer_InitStateRunRight(struct State_s *ptState, struct QTask_s *ptQTask)
{
  int nPreviousState; // eax
  struct QTask_s *ptTail; // eax
  struct QTask_s *ptParent; // ecx
  double v5; // st7
  struct QTask_s *v6; // eax
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *v9; // ecx
  double v10; // st7
  double v11; // st6
  float v12; // [esp-4h] [ebp-1Ch]
  int v13; // [esp+10h] [ebp-8h]

  *(_DWORD *)&ptQTask[32].eQTaskType = 0;
  nPreviousState = ptState->nPreviousState;
  if ( nPreviousState == 17 || nPreviousState == 32 )
  {
    ptTail = ptQTask[34].tQTaskChildren.ptTail;
    ptParent = ptTail[1].ptParent;
    if ( ptParent )
      v5 = (double)(int)ptTail[1].tQTaskRefList.ptMiddle / (double)(int)ptParent->tQTaskChildren.ptTail;
    else
      v5 = 0.0;
    v6 = ptTail[1].ptParent;
    if ( v6 )
      v13 = (int)v6->tQTaskChildren.ptTail;
    else
      v13 = 0;
    HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, (__int64)((double)v13 * v5), 0.20000000298023224);
  }
  else
  {
    if ( nPreviousState == 36 )
      v12 = 0.0;
    else
      v12 = 0.20000000298023224;
    HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, 0, v12);
  }
  ptNext = ptQTask[33].ptNext;
  ptQTask[77].ptParent = (struct QTask_s *)3;
  ptPrev = ptNext[1].ptPrev;
  if ( ptPrev && (v9 = ptPrev->tQTaskChildren.ptTail) != nullptr )
  {
    ptQTask[77].tQTaskChildren.ptHead = (struct QTask_s *)1;
    v10 = *(float *)&v9[21].ptPrev;
    ptQTask[77].tQTaskChildren.ptMiddle = v9[21].ptPrev;
    v11 = *(float *)&ptQTask[43].ptParent;
    if ( v11 < 0.0 )
      v11 = -v11;
    *(float *)&ptQTask[77].tQTaskChildren.ptMiddle = v11 * *(float *)&v9[21].ptParent * 3.0 + v10;
    ptState->pfState = HumanPlayer_RunStateRunRight;
  }
  else
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    ptQTask[77].tQTaskChildren.ptMiddle = nullptr;
    ptState->pfState = HumanPlayer_RunStateRunRight;
  }
}

// source: j/0/human/humanplayer.c:6198  [anchor-mhash]
void __cdecl HumanPlayer_RunStateRunRight(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vMaxYDelta; };
    struct { char igi2_o1[28]; struct real32x3_t tReal32x3; };
    struct { char igi2_o2[40]; struct real64x3_t tReal64x3; };
    char igi2_extent[68];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v2; // ebp
  unsigned int bSignal; // ecx
  void (__cdecl *v4)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v6)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v7)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v8)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v9)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v10)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v11)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v12)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v13)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v14)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v15)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v16)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v17)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v18)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v19)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v20)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v21)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v22)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v23)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v24)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v25)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v26)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v27)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v28)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v29)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v30)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v31)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v32)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v33)(struct State_s *, struct QTask_s *); // eax
  char ptPrev; // al
  void (__cdecl *v35)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v36)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v37)(struct State_s *, struct QTask_s *); // eax
  bool v38; // zf
  void (__cdecl *v39)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v40)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v41)(struct State_s *, struct QTask_s *); // eax

  v2 = ptQTask;
  Human_RunningControl(ptQTask, HUMANPLAYER_RUNRIGHT_ANIMTIMESCALE);
  igi2_frame.vMaxYDelta = *(float *)&v2[81].ptNext * 477.1839904785156;
  HumanPlayer_MoveOnGround((struct HumanPlayer_t *)v2, 0.0, 118.76579284667969, igi2_frame.vMaxYDelta, 63.62453079223633);
  bSignal = ptState->bSignal;
  if ( (bSignal & 0x800000) != 0 )
  {
    v4 = ptState->apfExitState[ptState->nState];
    if ( v4 )
      v4(ptState, v2);
    apfState = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 21;
    v6 = apfState[21];
    ptState->pfState = v6;
    v6(ptState, v2);
  }
  else if ( (bSignal & 2) != 0 )
  {
    if ( (bSignal & 0x20000) != 0 )
    {
      v10 = ptState->apfExitState[ptState->nState];
      if ( v10 )
        v10(ptState, v2);
      v11 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 55;
      v12 = v11[55];
      ptState->pfState = v12;
      v12(ptState, v2);
    }
    else if ( (bSignal & 0x10000) != 0 )
    {
      v13 = ptState->apfExitState[ptState->nState];
      if ( v13 )
        v13(ptState, v2);
      v14 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 54;
      v15 = v14[54];
      ptState->pfState = v15;
      v15(ptState, v2);
    }
    else if ( (bSignal & 0x40000) != 0 )
    {
      v16 = ptState->apfExitState[ptState->nState];
      if ( v16 )
        v16(ptState, v2);
      v17 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 17;
      v18 = v17[17];
      ptState->pfState = v18;
      v18(ptState, v2);
    }
    else if ( *(float *)&v2[20].tQTaskChildren.ptHead != 0.0
           && *(float *)&v2[13].eQTaskType == 0.0
           && ((int)v2[50].ptPrev & 8) != 0 )
    {
      v19 = ptState->apfExitState[ptState->nState];
      if ( v19 )
        v19(ptState, v2);
      v20 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 36;
      v21 = v20[36];
      ptState->pfState = v21;
      v21(ptState, v2);
    }
    else if ( (bSignal & 0x40) != 0 )
    {
      if ( (bSignal & 0x80u) == 0 )
      {
        if ( (bSignal & 0x100) != 0 )
        {
          v28 = ptState->apfExitState[ptState->nState];
          if ( v28 )
            v28(ptState, v2);
          v29 = ptState->apfState;
          ptState->nPreviousState = ptState->nState;
          ptState->nState = 7;
          v30 = v29[7];
          ptState->pfState = v30;
          v30(ptState, v2);
        }
        else if ( (bSignal & 0x1000000) != 0 )
        {
          v2[83].tQTaskRefList.ptHead = nullptr;
          v31 = ptState->apfExitState[ptState->nState];
          if ( v31 )
            v31(ptState, v2);
          v32 = ptState->apfState;
          ptState->nPreviousState = ptState->nState;
          ptState->nState = 23;
          v33 = v32[23];
          ptState->pfState = v33;
          v33(ptState, v2);
        }
        else if ( ((bSignal & 0x2000) != 0 || (ptPrev = (char)v2[50].ptPrev, (ptPrev & 1) == 0))
               && (ptPrev = (char)v2[50].ptPrev, (ptPrev & 2) != 0) )
        {
          v2[83].tQTaskRefList.ptHead = (struct QReference_s *)1;
          v35 = ptState->apfExitState[ptState->nState];
          if ( v35 )
            v35(ptState, v2);
          v36 = ptState->apfState;
          ptState->nPreviousState = ptState->nState;
          ptState->nState = 23;
          v37 = v36[23];
          ptState->pfState = v37;
          v37(ptState, v2);
        }
        else if ( (bSignal & 0x20000000) != 0
               && (ptPrev & 4) != 0
               && (ptQTask = nullptr,
                   qmemcpy(&igi2_frame.tReal64x3, &v2[1], sizeof(igi2_frame.tReal64x3)),
                   *(_DWORD *)&v2[32].eQTaskType = 2,
                   Human_ObjectCollision(v2, &igi2_frame.tReal64x3, &igi2_frame.tReal64x3, &igi2_frame.tReal32x3, (unsigned int *)&ptQTask),
                   v38 = ((unsigned __int8)ptQTask & 4) == 0,
                   *(_DWORD *)&v2[32].eQTaskType = 0,
                   v38) )
        {
          v39 = ptState->apfExitState[ptState->nState];
          if ( v39 )
            v39(ptState, v2);
          v40 = ptState->apfState;
          ptState->nPreviousState = ptState->nState;
          ptState->nState = 75;
          v41 = v40[75];
          ptState->pfState = v41;
          v41(ptState, v2);
        }
        else
        {
          HumanPlayer_SendWalkEvent(v2, true);
        }
      }
      else
      {
        v25 = ptState->apfExitState[ptState->nState];
        if ( v25 )
          v25(ptState, v2);
        v26 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 4;
        v27 = v26[4];
        ptState->pfState = v27;
        v27(ptState, v2);
      }
    }
    else
    {
      v22 = ptState->apfExitState[ptState->nState];
      if ( v22 )
        v22(ptState, v2);
      v23 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 0;
      v24 = *v23;
      ptState->pfState = *v23;
      v24(ptState, v2);
    }
  }
  else
  {
    v7 = ptState->apfExitState[ptState->nState];
    if ( v7 )
      v7(ptState, v2);
    v8 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 37;
    v9 = v8[37];
    ptState->pfState = v9;
    v9(ptState, v2);
  }
}

// source: j/0/human/humanplayer.c:6281  [size]
void __cdecl HumanPlayer_InitStateRunLeft(struct State_s *ptState, struct QTask_s *ptQTask)
{
  int nPreviousState; // eax
  struct QTask_s *ptTail; // eax
  struct QTask_s *ptParent; // ecx
  double v5; // st7
  struct QTask_s *v6; // eax
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *v9; // ecx
  double v10; // st7
  double v11; // st6
  float v12; // [esp-4h] [ebp-1Ch]
  int v13; // [esp+10h] [ebp-8h]

  *(_DWORD *)&ptQTask[32].eQTaskType = 0;
  nPreviousState = ptState->nPreviousState;
  if ( nPreviousState == 18 || nPreviousState == 33 )
  {
    ptTail = ptQTask[34].tQTaskChildren.ptTail;
    ptParent = ptTail[1].ptParent;
    if ( ptParent )
      v5 = (double)(int)ptTail[1].tQTaskRefList.ptMiddle / (double)(int)ptParent->tQTaskChildren.ptTail;
    else
      v5 = 0.0;
    v6 = ptTail[1].ptParent;
    if ( v6 )
      v13 = (int)v6->tQTaskChildren.ptTail;
    else
      v13 = 0;
    HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, (__int64)((double)v13 * v5), 0.20000000298023224);
  }
  else
  {
    if ( nPreviousState == 36 )
      v12 = 0.0;
    else
      v12 = 0.20000000298023224;
    HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, 0, v12);
  }
  ptNext = ptQTask[33].ptNext;
  ptQTask[77].ptParent = (struct QTask_s *)3;
  ptPrev = ptNext[1].ptPrev;
  if ( ptPrev && (v9 = ptPrev->tQTaskChildren.ptTail) != nullptr )
  {
    ptQTask[77].tQTaskChildren.ptHead = (struct QTask_s *)1;
    v10 = *(float *)&v9[21].ptPrev;
    ptQTask[77].tQTaskChildren.ptMiddle = v9[21].ptPrev;
    v11 = *(float *)&ptQTask[43].ptParent;
    if ( v11 < 0.0 )
      v11 = -v11;
    *(float *)&ptQTask[77].tQTaskChildren.ptMiddle = v11 * *(float *)&v9[21].ptParent * 3.0 + v10;
    ptState->pfState = HumanPlayer_RunStateRunLeft;
  }
  else
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    ptQTask[77].tQTaskChildren.ptMiddle = nullptr;
    ptState->pfState = HumanPlayer_RunStateRunLeft;
  }
}

// source: j/0/human/humanplayer.c:6326  [anchor-mhash]
void __cdecl HumanPlayer_RunStateRunLeft(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vMaxYDelta; };
    struct { char igi2_o1[28]; struct real32x3_t tReal32x3; };
    struct { char igi2_o2[40]; struct real64x3_t tReal64x3; };
    char igi2_extent[68];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v2; // ebx
  unsigned int bSignal; // ecx
  void (__cdecl *v4)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v6)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v7)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v8)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v9)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v10)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v11)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v12)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v13)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v14)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v15)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v16)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v17)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v18)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v19)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v20)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v21)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v22)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v23)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v24)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v25)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v26)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v27)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v28)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v29)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v30)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v31)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v32)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v33)(struct State_s *, struct QTask_s *); // eax
  char ptPrev; // al
  void (__cdecl *v35)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v36)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v37)(struct State_s *, struct QTask_s *); // eax
  bool v38; // zf
  void (__cdecl *v39)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v40)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v41)(struct State_s *, struct QTask_s *); // eax

  v2 = ptQTask;
  Human_RunningControl(ptQTask, HUMANPLAYER_RUNLEFT_ANIMTIMESCALE);
  igi2_frame.vMaxYDelta = *(float *)&v2[81].ptNext * -477.1839904785156;
  HumanPlayer_MoveOnGround((struct HumanPlayer_t *)v2, 0.0, 118.76579284667969, igi2_frame.vMaxYDelta, 63.62453079223633);
  bSignal = ptState->bSignal;
  if ( (bSignal & 0x800000) != 0 )
  {
    v4 = ptState->apfExitState[ptState->nState];
    if ( v4 )
      v4(ptState, v2);
    apfState = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 21;
    v6 = apfState[21];
    ptState->pfState = v6;
    v6(ptState, v2);
  }
  else if ( (bSignal & 2) != 0 )
  {
    if ( (bSignal & 0x20000) != 0 )
    {
      v10 = ptState->apfExitState[ptState->nState];
      if ( v10 )
        v10(ptState, v2);
      v11 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 55;
      v12 = v11[55];
      ptState->pfState = v12;
      v12(ptState, v2);
    }
    else if ( (bSignal & 0x10000) != 0 )
    {
      v13 = ptState->apfExitState[ptState->nState];
      if ( v13 )
        v13(ptState, v2);
      v14 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 54;
      v15 = v14[54];
      ptState->pfState = v15;
      v15(ptState, v2);
    }
    else if ( (bSignal & 0x40000) != 0 )
    {
      v16 = ptState->apfExitState[ptState->nState];
      if ( v16 )
        v16(ptState, v2);
      v17 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 18;
      v18 = v17[18];
      ptState->pfState = v18;
      v18(ptState, v2);
    }
    else if ( *(float *)&v2[20].tQTaskChildren.ptHead != 0.0
           && *(float *)&v2[13].eQTaskType == 0.0
           && ((int)v2[50].ptPrev & 8) != 0 )
    {
      v19 = ptState->apfExitState[ptState->nState];
      if ( v19 )
        v19(ptState, v2);
      v20 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 36;
      v21 = v20[36];
      ptState->pfState = v21;
      v21(ptState, v2);
    }
    else if ( (bSignal & 0x20) != 0 )
    {
      if ( (bSignal & 0x80u) == 0 )
      {
        if ( (bSignal & 0x100) != 0 )
        {
          v28 = ptState->apfExitState[ptState->nState];
          if ( v28 )
            v28(ptState, v2);
          v29 = ptState->apfState;
          ptState->nPreviousState = ptState->nState;
          ptState->nState = 8;
          v30 = v29[8];
          ptState->pfState = v30;
          v30(ptState, v2);
        }
        else if ( (bSignal & 0x1000000) != 0 )
        {
          v2[83].tQTaskRefList.ptHead = nullptr;
          v31 = ptState->apfExitState[ptState->nState];
          if ( v31 )
            v31(ptState, v2);
          v32 = ptState->apfState;
          ptState->nPreviousState = ptState->nState;
          ptState->nState = 23;
          v33 = v32[23];
          ptState->pfState = v33;
          v33(ptState, v2);
        }
        else if ( ((bSignal & 0x2000) != 0 || (ptPrev = (char)v2[50].ptPrev, (ptPrev & 1) == 0))
               && (ptPrev = (char)v2[50].ptPrev, (ptPrev & 2) != 0) )
        {
          v2[83].tQTaskRefList.ptHead = (struct QReference_s *)1;
          v35 = ptState->apfExitState[ptState->nState];
          if ( v35 )
            v35(ptState, v2);
          v36 = ptState->apfState;
          ptState->nPreviousState = ptState->nState;
          ptState->nState = 23;
          v37 = v36[23];
          ptState->pfState = v37;
          v37(ptState, v2);
        }
        else if ( (bSignal & 0x20000000) != 0
               && (ptPrev & 4) != 0
               && (ptQTask = nullptr,
                   qmemcpy(&igi2_frame.tReal64x3, &v2[1], sizeof(igi2_frame.tReal64x3)),
                   *(_DWORD *)&v2[32].eQTaskType = 2,
                   Human_ObjectCollision(v2, &igi2_frame.tReal64x3, &igi2_frame.tReal64x3, &igi2_frame.tReal32x3, (unsigned int *)&ptQTask),
                   v38 = ((unsigned __int8)ptQTask & 4) == 0,
                   *(_DWORD *)&v2[32].eQTaskType = 0,
                   v38) )
        {
          v39 = ptState->apfExitState[ptState->nState];
          if ( v39 )
            v39(ptState, v2);
          v40 = ptState->apfState;
          ptState->nPreviousState = ptState->nState;
          ptState->nState = 75;
          v41 = v40[75];
          ptState->pfState = v41;
          v41(ptState, v2);
        }
        else
        {
          HumanPlayer_SendWalkEvent(v2, true);
        }
      }
      else
      {
        v25 = ptState->apfExitState[ptState->nState];
        if ( v25 )
          v25(ptState, v2);
        v26 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 5;
        v27 = v26[5];
        ptState->pfState = v27;
        v27(ptState, v2);
      }
    }
    else
    {
      v22 = ptState->apfExitState[ptState->nState];
      if ( v22 )
        v22(ptState, v2);
      v23 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 0;
      v24 = *v23;
      ptState->pfState = *v23;
      v24(ptState, v2);
    }
  }
  else
  {
    v7 = ptState->apfExitState[ptState->nState];
    if ( v7 )
      v7(ptState, v2);
    v8 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 37;
    v9 = v8[37];
    ptState->pfState = v9;
    v9(ptState, v2);
  }
}

// source: j/0/human/humanplayer.c:6409  [size~]
void __cdecl HumanPlayer_InitStateWalkForward(struct State_s *ptState, struct QTask_s *ptQTask)
{
  int v2; // edx
  struct QTask_s *ptTail; // eax
  struct QTask_s *ptParent; // ecx
  double v5; // st7
  struct QTask_s *v6; // eax
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *v9; // ecx
  double v10; // st7
  double v11; // st6
  int v12; // [esp+10h] [ebp-8h]

  v2 = 0;
  *(_DWORD *)&ptQTask[32].eQTaskType = 0;
  switch ( ptState->nPreviousState )
  {
    case 3:
    case 0xC:
    case 0xD:
    case 0x1A:
      ptTail = ptQTask[34].tQTaskChildren.ptTail;
      ptParent = ptTail[1].ptParent;
      if ( ptParent )
        v5 = (double)(int)ptTail[1].tQTaskRefList.ptMiddle / (double)(int)ptParent->tQTaskChildren.ptTail;
      else
        v5 = 0.0;
      v6 = ptTail[1].ptParent;
      if ( v6 )
        v12 = (int)v6->tQTaskChildren.ptTail;
      else
        v12 = 0;
      v2 = (__int64)((double)v12 * v5);
      break;
    default:
      break;
  }
  HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, v2, 0.20000000298023224);
  ptNext = ptQTask[33].ptNext;
  ptQTask[77].ptParent = (struct QTask_s *)2;
  ptPrev = ptNext[1].ptPrev;
  if ( ptPrev && (v9 = ptPrev->tQTaskChildren.ptTail) != nullptr )
  {
    ptQTask[77].tQTaskChildren.ptHead = (struct QTask_s *)2;
    v10 = *(float *)&v9[21].tQTaskChildren.ptHead;
    ptQTask[77].tQTaskChildren.ptMiddle = v9[21].tQTaskChildren.ptHead;
    v11 = *(float *)&ptQTask[43].ptParent;
    if ( v11 < 0.0 )
      v11 = -v11;
    *(float *)&ptQTask[77].tQTaskChildren.ptMiddle = v11 * *(float *)&v9[21].ptParent * 3.0 + v10;
    ptState->pfState = HumanPlayer_RunStateWalkForward;
  }
  else
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    ptQTask[77].tQTaskChildren.ptMiddle = nullptr;
    ptState->pfState = HumanPlayer_RunStateWalkForward;
  }
}

// source: j/0/human/humanplayer.c:6450  [anchor-mhash]
void __cdecl HumanPlayer_RunStateWalkForward(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptHumanPlayer; };
    struct { char igi2_o1[36]; struct real32x3_t tReal32x3; };
    struct { char igi2_o2[48]; struct real64x3_t tReal64x3; };
    char igi2_extent[76];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v2; // ebp
  unsigned int bSignal; // ecx
  void (__cdecl *v4)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v6)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v7)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v8)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v9)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v10)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v11)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v12)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v13)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v14)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v15)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v16)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v17)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v18)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v19)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v20)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v21)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v22)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v23)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v24)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v25)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v26)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v27)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v28)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v29)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v30)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v31)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v32)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v33)(struct State_s *, struct QTask_s *); // eax
  char ptPrev; // al
  void (__cdecl *v35)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v36)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v37)(struct State_s *, struct QTask_s *); // eax
  bool v38; // zf
  void (__cdecl *v39)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v40)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v41)(struct State_s *, struct QTask_s *); // eax

  v2 = ptQTask;
  igi2_frame.ptHumanPlayer = *(float *)&ptQTask[81].ptNext * 442.3680114746094;
  HumanPlayer_MoveOnGround((struct HumanPlayer_t *)ptQTask, igi2_frame.ptHumanPlayer, 58.98240280151367, 0.0, 63.62453079223633);
  bSignal = ptState->bSignal;
  if ( (bSignal & 0x800000) != 0 )
  {
    v4 = ptState->apfExitState[ptState->nState];
    if ( v4 )
      v4(ptState, v2);
    apfState = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 21;
    v6 = apfState[21];
    ptState->pfState = v6;
    v6(ptState, v2);
  }
  else if ( (bSignal & 2) != 0 )
  {
    if ( (bSignal & 0x20000) != 0 )
    {
      v10 = ptState->apfExitState[ptState->nState];
      if ( v10 )
        v10(ptState, v2);
      v11 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 55;
      v12 = v11[55];
      ptState->pfState = v12;
      v12(ptState, v2);
    }
    else if ( (bSignal & 0x10000) != 0 )
    {
      v13 = ptState->apfExitState[ptState->nState];
      if ( v13 )
        v13(ptState, v2);
      v14 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 54;
      v15 = v14[54];
      ptState->pfState = v15;
      v15(ptState, v2);
    }
    else if ( (bSignal & 0x40000) != 0 )
    {
      if ( *(float *)&v2[20].tQTaskChildren.ptHead != 0.0
        && *(float *)&v2[13].eQTaskType == 0.0
        && ((int)v2[50].ptPrev & 8) != 0 )
      {
        v19 = ptState->apfExitState[ptState->nState];
        if ( v19 )
          v19(ptState, v2);
        v20 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 36;
        v21 = v20[36];
        ptState->pfState = v21;
        v21(ptState, v2);
      }
      else if ( (bSignal & 0x40) != 0 )
      {
        v22 = ptState->apfExitState[ptState->nState];
        if ( v22 )
          v22(ptState, v2);
        v23 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 12;
        v24 = v23[12];
        ptState->pfState = v24;
        v24(ptState, v2);
      }
      else if ( (bSignal & 0x20) != 0 )
      {
        v25 = ptState->apfExitState[ptState->nState];
        if ( v25 )
          v25(ptState, v2);
        v26 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 13;
        v27 = v26[13];
        ptState->pfState = v27;
        v27(ptState, v2);
      }
      else if ( (bSignal & 0x80u) != 0 )
      {
        if ( (bSignal & 0x1000000) != 0 )
        {
          v2[83].tQTaskRefList.ptHead = nullptr;
          v31 = ptState->apfExitState[ptState->nState];
          if ( v31 )
            v31(ptState, v2);
          v32 = ptState->apfState;
          ptState->nPreviousState = ptState->nState;
          ptState->nState = 23;
          v33 = v32[23];
          ptState->pfState = v33;
          v33(ptState, v2);
        }
        else if ( ((bSignal & 0x2000) != 0 || (ptPrev = (char)v2[50].ptPrev, (ptPrev & 1) == 0))
               && (ptPrev = (char)v2[50].ptPrev, (ptPrev & 2) != 0) )
        {
          v2[83].tQTaskRefList.ptHead = (struct QReference_s *)1;
          v35 = ptState->apfExitState[ptState->nState];
          if ( v35 )
            v35(ptState, v2);
          v36 = ptState->apfState;
          ptState->nPreviousState = ptState->nState;
          ptState->nState = 23;
          v37 = v36[23];
          ptState->pfState = v37;
          v37(ptState, v2);
        }
        else if ( (bSignal & 0x20000000) != 0
               && (ptPrev & 4) != 0
               && (ptQTask = nullptr,
                   qmemcpy(&igi2_frame.tReal64x3, &v2[1], sizeof(igi2_frame.tReal64x3)),
                   *(_DWORD *)&v2[32].eQTaskType = 2,
                   Human_ObjectCollision(v2, &igi2_frame.tReal64x3, &igi2_frame.tReal64x3, &igi2_frame.tReal32x3, (unsigned int *)&ptQTask),
                   v38 = ((unsigned __int8)ptQTask & 4) == 0,
                   *(_DWORD *)&v2[32].eQTaskType = 0,
                   v38) )
        {
          v39 = ptState->apfExitState[ptState->nState];
          if ( v39 )
            v39(ptState, v2);
          v40 = ptState->apfState;
          ptState->nPreviousState = ptState->nState;
          ptState->nState = 75;
          v41 = v40[75];
          ptState->pfState = v41;
          v41(ptState, v2);
        }
        else
        {
          HumanPlayer_SendWalkEvent(v2, false);
        }
      }
      else
      {
        v28 = ptState->apfExitState[ptState->nState];
        if ( v28 )
          v28(ptState, v2);
        v29 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 0;
        v30 = *v29;
        ptState->pfState = *v29;
        v30(ptState, v2);
      }
    }
    else
    {
      v16 = ptState->apfExitState[ptState->nState];
      if ( v16 )
        v16(ptState, v2);
      v17 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 3;
      v18 = v17[3];
      ptState->pfState = v18;
      v18(ptState, v2);
    }
  }
  else
  {
    v7 = ptState->apfExitState[ptState->nState];
    if ( v7 )
      v7(ptState, v2);
    v8 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 37;
    v9 = v8[37];
    ptState->pfState = v9;
    v9(ptState, v2);
  }
}

// source: j/0/human/humanplayer.c:6530  [size]
void __cdecl HumanPlayer_InitStateWalkForwardRight(struct State_s *ptState, struct QTask_s *ptQTask)
{
  int nPreviousState; // eax
  struct QTask_s *ptTail; // eax
  struct QTask_s *ptParent; // ecx
  double v5; // st7
  struct QTask_s *v6; // eax
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *v9; // ecx
  double v10; // st7
  double v11; // st6
  int v12; // [esp+10h] [ebp-8h]

  *(_DWORD *)&ptQTask[32].eQTaskType = 0;
  nPreviousState = ptState->nPreviousState;
  if ( nPreviousState == 4 || nPreviousState == 11 || nPreviousState == 27 )
  {
    ptTail = ptQTask[34].tQTaskChildren.ptTail;
    ptParent = ptTail[1].ptParent;
    if ( ptParent )
      v5 = (double)(int)ptTail[1].tQTaskRefList.ptMiddle / (double)(int)ptParent->tQTaskChildren.ptTail;
    else
      v5 = 0.0;
    v6 = ptTail[1].ptParent;
    if ( v6 )
      v12 = (int)v6->tQTaskChildren.ptTail;
    else
      v12 = 0;
    HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, (__int64)((double)v12 * v5), 0.20000000298023224);
  }
  else
  {
    HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, 0, 0.20000000298023224);
  }
  ptNext = ptQTask[33].ptNext;
  ptQTask[77].ptParent = (struct QTask_s *)2;
  ptPrev = ptNext[1].ptPrev;
  if ( ptPrev && (v9 = ptPrev->tQTaskChildren.ptTail) != nullptr )
  {
    ptQTask[77].tQTaskChildren.ptHead = (struct QTask_s *)2;
    v10 = *(float *)&v9[21].tQTaskChildren.ptHead;
    ptQTask[77].tQTaskChildren.ptMiddle = v9[21].tQTaskChildren.ptHead;
    v11 = *(float *)&ptQTask[43].ptParent;
    if ( v11 < 0.0 )
      v11 = -v11;
    *(float *)&ptQTask[77].tQTaskChildren.ptMiddle = v11 * *(float *)&v9[21].ptParent * 3.0 + v10;
    ptState->pfState = HumanPlayer_RunStateWalkForwardRight;
  }
  else
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    ptQTask[77].tQTaskChildren.ptMiddle = nullptr;
    ptState->pfState = HumanPlayer_RunStateWalkForwardRight;
  }
}

// source: j/0/human/humanplayer.c:6570  [size]
void __cdecl HumanPlayer_RunStateWalkForwardRight(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptHumanPlayer; };
    struct { char igi2_o1[8]; float vMaxYDelta; };
    struct { char igi2_o2[36]; struct real32x3_t tReal32x3; };
    struct { char igi2_o3[48]; struct real64x3_t tReal64x3; };
    char igi2_extent[76];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v2; // ebp
  unsigned int bSignal; // ecx
  void (__cdecl *v4)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v6)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v7)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v8)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v9)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v10)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v11)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v12)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v13)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v14)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v15)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v16)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v17)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v18)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v19)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v20)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v21)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v22)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v23)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v24)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v25)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v26)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v27)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v28)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v29)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v30)(struct State_s *, struct QTask_s *); // eax
  char ptPrev; // al
  void (__cdecl *v32)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v33)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v34)(struct State_s *, struct QTask_s *); // eax
  bool v35; // zf
  void (__cdecl *v36)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v37)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v38)(struct State_s *, struct QTask_s *); // eax

  v2 = ptQTask;
  igi2_frame.vMaxYDelta = *(float *)&ptQTask[81].ptNext * 477.1839904785156;
  igi2_frame.ptHumanPlayer = *(float *)&ptQTask[81].ptNext * 442.3680114746094;
  HumanPlayer_MoveOnGround((struct HumanPlayer_t *)ptQTask, igi2_frame.ptHumanPlayer, 58.98240280151367, igi2_frame.vMaxYDelta, 63.62453079223633);
  bSignal = ptState->bSignal;
  if ( (bSignal & 0x800000) != 0 )
  {
    v4 = ptState->apfExitState[ptState->nState];
    if ( v4 )
      v4(ptState, v2);
    apfState = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 21;
    v6 = apfState[21];
    ptState->pfState = v6;
    v6(ptState, v2);
  }
  else if ( (bSignal & 2) != 0 )
  {
    if ( (bSignal & 0x20000) != 0 )
    {
      v10 = ptState->apfExitState[ptState->nState];
      if ( v10 )
        v10(ptState, v2);
      v11 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 55;
      v12 = v11[55];
      ptState->pfState = v12;
      v12(ptState, v2);
    }
    else if ( (bSignal & 0x10000) != 0 )
    {
      v13 = ptState->apfExitState[ptState->nState];
      if ( v13 )
        v13(ptState, v2);
      v14 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 54;
      v15 = v14[54];
      ptState->pfState = v15;
      v15(ptState, v2);
    }
    else if ( (bSignal & 0x40000) != 0 )
    {
      if ( *(float *)&v2[20].tQTaskChildren.ptHead != 0.0
        && *(float *)&v2[13].eQTaskType == 0.0
        && ((int)v2[50].ptPrev & 8) != 0 )
      {
        v19 = ptState->apfExitState[ptState->nState];
        if ( v19 )
          v19(ptState, v2);
        v20 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 36;
        v21 = v20[36];
        ptState->pfState = v21;
        v21(ptState, v2);
      }
      else if ( (bSignal & 0x80u) != 0 )
      {
        if ( (bSignal & 0x40) != 0 )
        {
          if ( (bSignal & 0x1000000) != 0 )
          {
            v2[83].tQTaskRefList.ptHead = nullptr;
            v28 = ptState->apfExitState[ptState->nState];
            if ( v28 )
              v28(ptState, v2);
            v29 = ptState->apfState;
            ptState->nPreviousState = ptState->nState;
            ptState->nState = 23;
            v30 = v29[23];
            ptState->pfState = v30;
            v30(ptState, v2);
          }
          else if ( ((bSignal & 0x2000) != 0 || (ptPrev = (char)v2[50].ptPrev, (ptPrev & 1) == 0))
                 && (ptPrev = (char)v2[50].ptPrev, (ptPrev & 2) != 0) )
          {
            v2[83].tQTaskRefList.ptHead = (struct QReference_s *)1;
            v32 = ptState->apfExitState[ptState->nState];
            if ( v32 )
              v32(ptState, v2);
            v33 = ptState->apfState;
            ptState->nPreviousState = ptState->nState;
            ptState->nState = 23;
            v34 = v33[23];
            ptState->pfState = v34;
            v34(ptState, v2);
          }
          else if ( (bSignal & 0x20000000) != 0
                 && (ptPrev & 4) != 0
                 && (qmemcpy(&igi2_frame.tReal64x3, &v2[1], sizeof(igi2_frame.tReal64x3)),
                     ptQTask = nullptr,
                     *(_DWORD *)&v2[32].eQTaskType = 2,
                     Human_ObjectCollision(v2, &igi2_frame.tReal64x3, &igi2_frame.tReal64x3, &igi2_frame.tReal32x3, (unsigned int *)&ptQTask),
                     v35 = ((unsigned __int8)ptQTask & 4) == 0,
                     *(_DWORD *)&v2[32].eQTaskType = 0,
                     v35) )
          {
            v36 = ptState->apfExitState[ptState->nState];
            if ( v36 )
              v36(ptState, v2);
            v37 = ptState->apfState;
            ptState->nPreviousState = ptState->nState;
            ptState->nState = 75;
            v38 = v37[75];
            ptState->pfState = v38;
            v38(ptState, v2);
          }
          else
          {
            HumanPlayer_SendWalkEvent(v2, false);
          }
        }
        else
        {
          v25 = ptState->apfExitState[ptState->nState];
          if ( v25 )
            v25(ptState, v2);
          v26 = ptState->apfState;
          ptState->nPreviousState = ptState->nState;
          ptState->nState = 11;
          v27 = v26[11];
          ptState->pfState = v27;
          v27(ptState, v2);
        }
      }
      else
      {
        v22 = ptState->apfExitState[ptState->nState];
        if ( v22 )
          v22(ptState, v2);
        v23 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 17;
        v24 = v23[17];
        ptState->pfState = v24;
        v24(ptState, v2);
      }
    }
    else
    {
      v16 = ptState->apfExitState[ptState->nState];
      if ( v16 )
        v16(ptState, v2);
      v17 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 4;
      v18 = v17[4];
      ptState->pfState = v18;
      v18(ptState, v2);
    }
  }
  else
  {
    v7 = ptState->apfExitState[ptState->nState];
    if ( v7 )
      v7(ptState, v2);
    v8 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 37;
    v9 = v8[37];
    ptState->pfState = v9;
    v9(ptState, v2);
  }
}

// source: j/0/human/humanplayer.c:6649  [size]
void __cdecl HumanPlayer_InitStateWalkForwardLeft(struct State_s *ptState, struct QTask_s *ptQTask)
{
  int nPreviousState; // eax
  struct QTask_s *ptTail; // eax
  struct QTask_s *ptParent; // ecx
  double v5; // st7
  struct QTask_s *v6; // eax
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *v9; // ecx
  double v10; // st7
  double v11; // st6
  int v12; // [esp+10h] [ebp-8h]

  *(_DWORD *)&ptQTask[32].eQTaskType = 0;
  nPreviousState = ptState->nPreviousState;
  if ( nPreviousState == 5 || nPreviousState == 11 || nPreviousState == 28 )
  {
    ptTail = ptQTask[34].tQTaskChildren.ptTail;
    ptParent = ptTail[1].ptParent;
    if ( ptParent )
      v5 = (double)(int)ptTail[1].tQTaskRefList.ptMiddle / (double)(int)ptParent->tQTaskChildren.ptTail;
    else
      v5 = 0.0;
    v6 = ptTail[1].ptParent;
    if ( v6 )
      v12 = (int)v6->tQTaskChildren.ptTail;
    else
      v12 = 0;
    HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, (__int64)((double)v12 * v5), 0.20000000298023224);
  }
  else
  {
    HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, 0, 0.20000000298023224);
  }
  ptNext = ptQTask[33].ptNext;
  ptQTask[77].ptParent = (struct QTask_s *)2;
  ptPrev = ptNext[1].ptPrev;
  if ( ptPrev && (v9 = ptPrev->tQTaskChildren.ptTail) != nullptr )
  {
    ptQTask[77].tQTaskChildren.ptHead = (struct QTask_s *)2;
    v10 = *(float *)&v9[21].tQTaskChildren.ptHead;
    ptQTask[77].tQTaskChildren.ptMiddle = v9[21].tQTaskChildren.ptHead;
    v11 = *(float *)&ptQTask[43].ptParent;
    if ( v11 < 0.0 )
      v11 = -v11;
    *(float *)&ptQTask[77].tQTaskChildren.ptMiddle = v11 * *(float *)&v9[21].ptParent * 3.0 + v10;
    ptState->pfState = HumanPlayer_RunStateWalkForwardLeft;
  }
  else
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    ptQTask[77].tQTaskChildren.ptMiddle = nullptr;
    ptState->pfState = HumanPlayer_RunStateWalkForwardLeft;
  }
}

// source: j/0/human/humanplayer.c:6689  [size]
void __cdecl HumanPlayer_RunStateWalkForwardLeft(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptHumanPlayer; };
    struct { char igi2_o1[8]; float vMaxYDelta; };
    struct { char igi2_o2[36]; struct real32x3_t tReal32x3; };
    struct { char igi2_o3[48]; struct real64x3_t tReal64x3; };
    char igi2_extent[76];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v2; // ebp
  unsigned int bSignal; // ecx
  void (__cdecl *v4)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v6)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v7)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v8)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v9)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v10)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v11)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v12)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v13)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v14)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v15)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v16)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v17)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v18)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v19)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v20)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v21)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v22)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v23)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v24)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v25)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v26)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v27)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v28)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v29)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v30)(struct State_s *, struct QTask_s *); // eax
  char ptPrev; // al
  void (__cdecl *v32)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v33)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v34)(struct State_s *, struct QTask_s *); // eax
  bool v35; // zf
  void (__cdecl *v36)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v37)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v38)(struct State_s *, struct QTask_s *); // eax

  v2 = ptQTask;
  igi2_frame.vMaxYDelta = *(float *)&ptQTask[81].ptNext * -477.1839904785156;
  igi2_frame.ptHumanPlayer = *(float *)&ptQTask[81].ptNext * 442.3680114746094;
  HumanPlayer_MoveOnGround((struct HumanPlayer_t *)ptQTask, igi2_frame.ptHumanPlayer, 58.98240280151367, igi2_frame.vMaxYDelta, 63.62453079223633);
  bSignal = ptState->bSignal;
  if ( (bSignal & 0x800000) != 0 )
  {
    v4 = ptState->apfExitState[ptState->nState];
    if ( v4 )
      v4(ptState, v2);
    apfState = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 21;
    v6 = apfState[21];
    ptState->pfState = v6;
    v6(ptState, v2);
  }
  else if ( (bSignal & 2) != 0 )
  {
    if ( (bSignal & 0x20000) != 0 )
    {
      v10 = ptState->apfExitState[ptState->nState];
      if ( v10 )
        v10(ptState, v2);
      v11 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 55;
      v12 = v11[55];
      ptState->pfState = v12;
      v12(ptState, v2);
    }
    else if ( (bSignal & 0x10000) != 0 )
    {
      v13 = ptState->apfExitState[ptState->nState];
      if ( v13 )
        v13(ptState, v2);
      v14 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 54;
      v15 = v14[54];
      ptState->pfState = v15;
      v15(ptState, v2);
    }
    else if ( (bSignal & 0x40000) != 0 )
    {
      if ( *(float *)&v2[20].tQTaskChildren.ptHead != 0.0
        && *(float *)&v2[13].eQTaskType == 0.0
        && ((int)v2[50].ptPrev & 8) != 0 )
      {
        v19 = ptState->apfExitState[ptState->nState];
        if ( v19 )
          v19(ptState, v2);
        v20 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 36;
        v21 = v20[36];
        ptState->pfState = v21;
        v21(ptState, v2);
      }
      else if ( (bSignal & 0x80u) != 0 )
      {
        if ( (bSignal & 0x20) != 0 )
        {
          if ( (bSignal & 0x1000000) != 0 )
          {
            v2[83].tQTaskRefList.ptHead = nullptr;
            v28 = ptState->apfExitState[ptState->nState];
            if ( v28 )
              v28(ptState, v2);
            v29 = ptState->apfState;
            ptState->nPreviousState = ptState->nState;
            ptState->nState = 23;
            v30 = v29[23];
            ptState->pfState = v30;
            v30(ptState, v2);
          }
          else if ( ((bSignal & 0x2000) != 0 || (ptPrev = (char)v2[50].ptPrev, (ptPrev & 1) == 0))
                 && (ptPrev = (char)v2[50].ptPrev, (ptPrev & 2) != 0) )
          {
            v2[83].tQTaskRefList.ptHead = (struct QReference_s *)1;
            v32 = ptState->apfExitState[ptState->nState];
            if ( v32 )
              v32(ptState, v2);
            v33 = ptState->apfState;
            ptState->nPreviousState = ptState->nState;
            ptState->nState = 23;
            v34 = v33[23];
            ptState->pfState = v34;
            v34(ptState, v2);
          }
          else if ( (bSignal & 0x20000000) != 0
                 && (ptPrev & 4) != 0
                 && (qmemcpy(&igi2_frame.tReal64x3, &v2[1], sizeof(igi2_frame.tReal64x3)),
                     ptQTask = nullptr,
                     *(_DWORD *)&v2[32].eQTaskType = 2,
                     Human_ObjectCollision(v2, &igi2_frame.tReal64x3, &igi2_frame.tReal64x3, &igi2_frame.tReal32x3, (unsigned int *)&ptQTask),
                     v35 = ((unsigned __int8)ptQTask & 4) == 0,
                     *(_DWORD *)&v2[32].eQTaskType = 0,
                     v35) )
          {
            v36 = ptState->apfExitState[ptState->nState];
            if ( v36 )
              v36(ptState, v2);
            v37 = ptState->apfState;
            ptState->nPreviousState = ptState->nState;
            ptState->nState = 75;
            v38 = v37[75];
            ptState->pfState = v38;
            v38(ptState, v2);
          }
          else
          {
            HumanPlayer_SendWalkEvent(v2, false);
          }
        }
        else
        {
          v25 = ptState->apfExitState[ptState->nState];
          if ( v25 )
            v25(ptState, v2);
          v26 = ptState->apfState;
          ptState->nPreviousState = ptState->nState;
          ptState->nState = 11;
          v27 = v26[11];
          ptState->pfState = v27;
          v27(ptState, v2);
        }
      }
      else
      {
        v22 = ptState->apfExitState[ptState->nState];
        if ( v22 )
          v22(ptState, v2);
        v23 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 18;
        v24 = v23[18];
        ptState->pfState = v24;
        v24(ptState, v2);
      }
    }
    else
    {
      v16 = ptState->apfExitState[ptState->nState];
      if ( v16 )
        v16(ptState, v2);
      v17 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 5;
      v18 = v17[5];
      ptState->pfState = v18;
      v18(ptState, v2);
    }
  }
  else
  {
    v7 = ptState->apfExitState[ptState->nState];
    if ( v7 )
      v7(ptState, v2);
    v8 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 37;
    v9 = v8[37];
    ptState->pfState = v9;
    v9(ptState, v2);
  }
}

// source: j/0/human/humanplayer.c:6768  [size~]
void __cdecl HumanPlayer_InitStateWalkBackward(struct State_s *ptState, struct QTask_s *ptQTask)
{
  int v2; // edx
  struct QTask_s *ptTail; // eax
  struct QTask_s *ptParent; // ecx
  double v5; // st7
  struct QTask_s *v6; // eax
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *v9; // ecx
  double v10; // st7
  double v11; // st6
  int v12; // [esp+10h] [ebp-8h]

  v2 = 0;
  *(_DWORD *)&ptQTask[32].eQTaskType = 0;
  switch ( ptState->nPreviousState )
  {
    case 6:
    case 0xF:
    case 0x10:
    case 0x1D:
      ptTail = ptQTask[34].tQTaskChildren.ptTail;
      ptParent = ptTail[1].ptParent;
      if ( ptParent )
        v5 = (double)(int)ptTail[1].tQTaskRefList.ptMiddle / (double)(int)ptParent->tQTaskChildren.ptTail;
      else
        v5 = 0.0;
      v6 = ptTail[1].ptParent;
      if ( v6 )
        v12 = (int)v6->tQTaskChildren.ptTail;
      else
        v12 = 0;
      v2 = (__int64)((double)v12 * v5);
      break;
    default:
      break;
  }
  HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, v2, 0.20000000298023224);
  ptNext = ptQTask[33].ptNext;
  ptQTask[77].ptParent = (struct QTask_s *)2;
  ptPrev = ptNext[1].ptPrev;
  if ( ptPrev && (v9 = ptPrev->tQTaskChildren.ptTail) != nullptr )
  {
    ptQTask[77].tQTaskChildren.ptHead = (struct QTask_s *)2;
    v10 = *(float *)&v9[21].tQTaskChildren.ptHead;
    ptQTask[77].tQTaskChildren.ptMiddle = v9[21].tQTaskChildren.ptHead;
    v11 = *(float *)&ptQTask[43].ptParent;
    if ( v11 < 0.0 )
      v11 = -v11;
    *(float *)&ptQTask[77].tQTaskChildren.ptMiddle = v11 * *(float *)&v9[21].ptParent * 3.0 + v10;
    ptState->pfState = HumanPlayer_RunStateWalkBackward;
  }
  else
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    ptQTask[77].tQTaskChildren.ptMiddle = nullptr;
    ptState->pfState = HumanPlayer_RunStateWalkBackward;
  }
}

// source: j/0/human/humanplayer.c:6809  [anchor-mhash]
void __cdecl HumanPlayer_RunStateWalkBackward(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptHumanPlayer; };
    struct { char igi2_o1[36]; struct real32x3_t tReal32x3; };
    struct { char igi2_o2[48]; struct real64x3_t tReal64x3; };
    char igi2_extent[76];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v2; // ebp
  unsigned int bSignal; // ecx
  void (__cdecl *v4)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v6)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v7)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v8)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v9)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v10)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v11)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v12)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v13)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v14)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v15)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v16)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v17)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v18)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v19)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v20)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v21)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v22)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v23)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v24)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v25)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v26)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v27)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v28)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v29)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v30)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v31)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v32)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v33)(struct State_s *, struct QTask_s *); // eax
  char ptPrev; // al
  void (__cdecl *v35)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v36)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v37)(struct State_s *, struct QTask_s *); // eax
  bool v38; // zf
  void (__cdecl *v39)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v40)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v41)(struct State_s *, struct QTask_s *); // eax

  v2 = ptQTask;
  igi2_frame.ptHumanPlayer = *(float *)&ptQTask[81].ptNext * -442.3680114746094;
  HumanPlayer_MoveOnGround((struct HumanPlayer_t *)ptQTask, igi2_frame.ptHumanPlayer, 58.98240280151367, 0.0, 63.62453079223633);
  bSignal = ptState->bSignal;
  if ( (bSignal & 0x800000) != 0 )
  {
    v4 = ptState->apfExitState[ptState->nState];
    if ( v4 )
      v4(ptState, v2);
    apfState = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 21;
    v6 = apfState[21];
    ptState->pfState = v6;
    v6(ptState, v2);
  }
  else if ( (bSignal & 2) != 0 )
  {
    if ( (bSignal & 0x20000) != 0 )
    {
      v10 = ptState->apfExitState[ptState->nState];
      if ( v10 )
        v10(ptState, v2);
      v11 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 55;
      v12 = v11[55];
      ptState->pfState = v12;
      v12(ptState, v2);
    }
    else if ( (bSignal & 0x10000) != 0 )
    {
      v13 = ptState->apfExitState[ptState->nState];
      if ( v13 )
        v13(ptState, v2);
      v14 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 54;
      v15 = v14[54];
      ptState->pfState = v15;
      v15(ptState, v2);
    }
    else if ( (bSignal & 0x40000) != 0 )
    {
      if ( *(float *)&v2[20].tQTaskChildren.ptHead != 0.0
        && *(float *)&v2[13].eQTaskType == 0.0
        && ((int)v2[50].ptPrev & 8) != 0 )
      {
        v19 = ptState->apfExitState[ptState->nState];
        if ( v19 )
          v19(ptState, v2);
        v20 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 36;
        v21 = v20[36];
        ptState->pfState = v21;
        v21(ptState, v2);
      }
      else if ( (bSignal & 0x40) != 0 )
      {
        v22 = ptState->apfExitState[ptState->nState];
        if ( v22 )
          v22(ptState, v2);
        v23 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 15;
        v24 = v23[15];
        ptState->pfState = v24;
        v24(ptState, v2);
      }
      else if ( (bSignal & 0x20) != 0 )
      {
        v25 = ptState->apfExitState[ptState->nState];
        if ( v25 )
          v25(ptState, v2);
        v26 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 16;
        v27 = v26[16];
        ptState->pfState = v27;
        v27(ptState, v2);
      }
      else if ( (bSignal & 0x100) != 0 )
      {
        if ( (bSignal & 0x1000000) != 0 )
        {
          v2[83].tQTaskRefList.ptHead = nullptr;
          v31 = ptState->apfExitState[ptState->nState];
          if ( v31 )
            v31(ptState, v2);
          v32 = ptState->apfState;
          ptState->nPreviousState = ptState->nState;
          ptState->nState = 23;
          v33 = v32[23];
          ptState->pfState = v33;
          v33(ptState, v2);
        }
        else if ( ((bSignal & 0x2000) != 0 || (ptPrev = (char)v2[50].ptPrev, (ptPrev & 1) == 0))
               && (ptPrev = (char)v2[50].ptPrev, (ptPrev & 2) != 0) )
        {
          v2[83].tQTaskRefList.ptHead = (struct QReference_s *)1;
          v35 = ptState->apfExitState[ptState->nState];
          if ( v35 )
            v35(ptState, v2);
          v36 = ptState->apfState;
          ptState->nPreviousState = ptState->nState;
          ptState->nState = 23;
          v37 = v36[23];
          ptState->pfState = v37;
          v37(ptState, v2);
        }
        else if ( (bSignal & 0x20000000) != 0
               && (ptPrev & 4) != 0
               && (ptQTask = nullptr,
                   qmemcpy(&igi2_frame.tReal64x3, &v2[1], sizeof(igi2_frame.tReal64x3)),
                   *(_DWORD *)&v2[32].eQTaskType = 2,
                   Human_ObjectCollision(v2, &igi2_frame.tReal64x3, &igi2_frame.tReal64x3, &igi2_frame.tReal32x3, (unsigned int *)&ptQTask),
                   v38 = ((unsigned __int8)ptQTask & 4) == 0,
                   *(_DWORD *)&v2[32].eQTaskType = 0,
                   v38) )
        {
          v39 = ptState->apfExitState[ptState->nState];
          if ( v39 )
            v39(ptState, v2);
          v40 = ptState->apfState;
          ptState->nPreviousState = ptState->nState;
          ptState->nState = 75;
          v41 = v40[75];
          ptState->pfState = v41;
          v41(ptState, v2);
        }
        else
        {
          HumanPlayer_SendWalkEvent(v2, false);
        }
      }
      else
      {
        v28 = ptState->apfExitState[ptState->nState];
        if ( v28 )
          v28(ptState, v2);
        v29 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 0;
        v30 = *v29;
        ptState->pfState = *v29;
        v30(ptState, v2);
      }
    }
    else
    {
      v16 = ptState->apfExitState[ptState->nState];
      if ( v16 )
        v16(ptState, v2);
      v17 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 6;
      v18 = v17[6];
      ptState->pfState = v18;
      v18(ptState, v2);
    }
  }
  else
  {
    v7 = ptState->apfExitState[ptState->nState];
    if ( v7 )
      v7(ptState, v2);
    v8 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 37;
    v9 = v8[37];
    ptState->pfState = v9;
    v9(ptState, v2);
  }
}

// source: j/0/human/humanplayer.c:6889  [size]
void __cdecl HumanPlayer_InitStateWalkBackwardRight(struct State_s *ptState, struct QTask_s *ptQTask)
{
  int nPreviousState; // eax
  struct QTask_s *ptTail; // eax
  struct QTask_s *ptParent; // ecx
  double v5; // st7
  struct QTask_s *v6; // eax
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *v9; // ecx
  double v10; // st7
  double v11; // st6
  int v12; // [esp+10h] [ebp-8h]

  *(_DWORD *)&ptQTask[32].eQTaskType = 0;
  nPreviousState = ptState->nPreviousState;
  if ( nPreviousState == 7 || nPreviousState == 14 || nPreviousState == 30 )
  {
    ptTail = ptQTask[34].tQTaskChildren.ptTail;
    ptParent = ptTail[1].ptParent;
    if ( ptParent )
      v5 = (double)(int)ptTail[1].tQTaskRefList.ptMiddle / (double)(int)ptParent->tQTaskChildren.ptTail;
    else
      v5 = 0.0;
    v6 = ptTail[1].ptParent;
    if ( v6 )
      v12 = (int)v6->tQTaskChildren.ptTail;
    else
      v12 = 0;
    HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, (__int64)((double)v12 * v5), 0.20000000298023224);
  }
  else
  {
    HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, 0, 0.20000000298023224);
  }
  ptNext = ptQTask[33].ptNext;
  ptQTask[77].ptParent = (struct QTask_s *)2;
  ptPrev = ptNext[1].ptPrev;
  if ( ptPrev && (v9 = ptPrev->tQTaskChildren.ptTail) != nullptr )
  {
    ptQTask[77].tQTaskChildren.ptHead = (struct QTask_s *)2;
    v10 = *(float *)&v9[21].tQTaskChildren.ptHead;
    ptQTask[77].tQTaskChildren.ptMiddle = v9[21].tQTaskChildren.ptHead;
    v11 = *(float *)&ptQTask[43].ptParent;
    if ( v11 < 0.0 )
      v11 = -v11;
    *(float *)&ptQTask[77].tQTaskChildren.ptMiddle = v11 * *(float *)&v9[21].ptParent * 3.0 + v10;
    ptState->pfState = HumanPlayer_RunStateWalkBackwardRight;
  }
  else
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    ptQTask[77].tQTaskChildren.ptMiddle = nullptr;
    ptState->pfState = HumanPlayer_RunStateWalkBackwardRight;
  }
}

// source: j/0/human/humanplayer.c:6929  [size]
void __cdecl HumanPlayer_RunStateWalkBackwardRight(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptHumanPlayer; };
    struct { char igi2_o1[8]; float vMaxYDelta; };
    struct { char igi2_o2[36]; struct real32x3_t tReal32x3; };
    struct { char igi2_o3[48]; struct real64x3_t tReal64x3; };
    char igi2_extent[76];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v2; // ebp
  unsigned int bSignal; // ecx
  void (__cdecl *v4)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v6)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v7)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v8)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v9)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v10)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v11)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v12)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v13)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v14)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v15)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v16)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v17)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v18)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v19)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v20)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v21)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v22)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v23)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v24)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v25)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v26)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v27)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v28)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v29)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v30)(struct State_s *, struct QTask_s *); // eax
  char ptPrev; // al
  void (__cdecl *v32)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v33)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v34)(struct State_s *, struct QTask_s *); // eax
  bool v35; // zf
  void (__cdecl *v36)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v37)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v38)(struct State_s *, struct QTask_s *); // eax

  v2 = ptQTask;
  igi2_frame.vMaxYDelta = *(float *)&ptQTask[81].ptNext * 477.1839904785156;
  igi2_frame.ptHumanPlayer = *(float *)&ptQTask[81].ptNext * -442.3680114746094;
  HumanPlayer_MoveOnGround((struct HumanPlayer_t *)ptQTask, igi2_frame.ptHumanPlayer, 58.98240280151367, igi2_frame.vMaxYDelta, 63.62453079223633);
  bSignal = ptState->bSignal;
  if ( (bSignal & 0x800000) != 0 )
  {
    v4 = ptState->apfExitState[ptState->nState];
    if ( v4 )
      v4(ptState, v2);
    apfState = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 21;
    v6 = apfState[21];
    ptState->pfState = v6;
    v6(ptState, v2);
  }
  else if ( (bSignal & 2) != 0 )
  {
    if ( (bSignal & 0x20000) != 0 )
    {
      v10 = ptState->apfExitState[ptState->nState];
      if ( v10 )
        v10(ptState, v2);
      v11 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 55;
      v12 = v11[55];
      ptState->pfState = v12;
      v12(ptState, v2);
    }
    else if ( (bSignal & 0x10000) != 0 )
    {
      v13 = ptState->apfExitState[ptState->nState];
      if ( v13 )
        v13(ptState, v2);
      v14 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 54;
      v15 = v14[54];
      ptState->pfState = v15;
      v15(ptState, v2);
    }
    else if ( (bSignal & 0x40000) != 0 )
    {
      if ( *(float *)&v2[20].tQTaskChildren.ptHead != 0.0
        && *(float *)&v2[13].eQTaskType == 0.0
        && ((int)v2[50].ptPrev & 8) != 0 )
      {
        v19 = ptState->apfExitState[ptState->nState];
        if ( v19 )
          v19(ptState, v2);
        v20 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 36;
        v21 = v20[36];
        ptState->pfState = v21;
        v21(ptState, v2);
      }
      else if ( (bSignal & 0x100) != 0 )
      {
        if ( (bSignal & 0x40) != 0 )
        {
          if ( (bSignal & 0x1000000) != 0 )
          {
            v2[83].tQTaskRefList.ptHead = nullptr;
            v28 = ptState->apfExitState[ptState->nState];
            if ( v28 )
              v28(ptState, v2);
            v29 = ptState->apfState;
            ptState->nPreviousState = ptState->nState;
            ptState->nState = 23;
            v30 = v29[23];
            ptState->pfState = v30;
            v30(ptState, v2);
          }
          else if ( ((bSignal & 0x2000) != 0 || (ptPrev = (char)v2[50].ptPrev, (ptPrev & 1) == 0))
                 && (ptPrev = (char)v2[50].ptPrev, (ptPrev & 2) != 0) )
          {
            v2[83].tQTaskRefList.ptHead = (struct QReference_s *)1;
            v32 = ptState->apfExitState[ptState->nState];
            if ( v32 )
              v32(ptState, v2);
            v33 = ptState->apfState;
            ptState->nPreviousState = ptState->nState;
            ptState->nState = 23;
            v34 = v33[23];
            ptState->pfState = v34;
            v34(ptState, v2);
          }
          else if ( (bSignal & 0x20000000) != 0
                 && (ptPrev & 4) != 0
                 && (qmemcpy(&igi2_frame.tReal64x3, &v2[1], sizeof(igi2_frame.tReal64x3)),
                     ptQTask = nullptr,
                     *(_DWORD *)&v2[32].eQTaskType = 2,
                     Human_ObjectCollision(v2, &igi2_frame.tReal64x3, &igi2_frame.tReal64x3, &igi2_frame.tReal32x3, (unsigned int *)&ptQTask),
                     v35 = ((unsigned __int8)ptQTask & 4) == 0,
                     *(_DWORD *)&v2[32].eQTaskType = 0,
                     v35) )
          {
            v36 = ptState->apfExitState[ptState->nState];
            if ( v36 )
              v36(ptState, v2);
            v37 = ptState->apfState;
            ptState->nPreviousState = ptState->nState;
            ptState->nState = 75;
            v38 = v37[75];
            ptState->pfState = v38;
            v38(ptState, v2);
          }
          else
          {
            HumanPlayer_SendWalkEvent(v2, false);
          }
        }
        else
        {
          v25 = ptState->apfExitState[ptState->nState];
          if ( v25 )
            v25(ptState, v2);
          v26 = ptState->apfState;
          ptState->nPreviousState = ptState->nState;
          ptState->nState = 14;
          v27 = v26[14];
          ptState->pfState = v27;
          v27(ptState, v2);
        }
      }
      else
      {
        v22 = ptState->apfExitState[ptState->nState];
        if ( v22 )
          v22(ptState, v2);
        v23 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 17;
        v24 = v23[17];
        ptState->pfState = v24;
        v24(ptState, v2);
      }
    }
    else
    {
      v16 = ptState->apfExitState[ptState->nState];
      if ( v16 )
        v16(ptState, v2);
      v17 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 7;
      v18 = v17[7];
      ptState->pfState = v18;
      v18(ptState, v2);
    }
  }
  else
  {
    v7 = ptState->apfExitState[ptState->nState];
    if ( v7 )
      v7(ptState, v2);
    v8 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 37;
    v9 = v8[37];
    ptState->pfState = v9;
    v9(ptState, v2);
  }
}

// source: j/0/human/humanplayer.c:7009  [size]
void __cdecl HumanPlayer_InitStateWalkBackwardLeft(struct State_s *ptState, struct QTask_s *ptQTask)
{
  int nPreviousState; // eax
  struct QTask_s *ptTail; // eax
  struct QTask_s *ptParent; // ecx
  double v5; // st7
  struct QTask_s *v6; // eax
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *v9; // ecx
  double v10; // st7
  double v11; // st6
  int v12; // [esp+10h] [ebp-8h]

  *(_DWORD *)&ptQTask[32].eQTaskType = 0;
  nPreviousState = ptState->nPreviousState;
  if ( nPreviousState == 8 || nPreviousState == 14 || nPreviousState == 31 )
  {
    ptTail = ptQTask[34].tQTaskChildren.ptTail;
    ptParent = ptTail[1].ptParent;
    if ( ptParent )
      v5 = (double)(int)ptTail[1].tQTaskRefList.ptMiddle / (double)(int)ptParent->tQTaskChildren.ptTail;
    else
      v5 = 0.0;
    v6 = ptTail[1].ptParent;
    if ( v6 )
      v12 = (int)v6->tQTaskChildren.ptTail;
    else
      v12 = 0;
    HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, (__int64)((double)v12 * v5), 0.20000000298023224);
  }
  else
  {
    HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, 0, 0.20000000298023224);
  }
  ptNext = ptQTask[33].ptNext;
  ptQTask[77].ptParent = (struct QTask_s *)2;
  ptPrev = ptNext[1].ptPrev;
  if ( ptPrev && (v9 = ptPrev->tQTaskChildren.ptTail) != nullptr )
  {
    ptQTask[77].tQTaskChildren.ptHead = (struct QTask_s *)2;
    v10 = *(float *)&v9[21].tQTaskChildren.ptHead;
    ptQTask[77].tQTaskChildren.ptMiddle = v9[21].tQTaskChildren.ptHead;
    v11 = *(float *)&ptQTask[43].ptParent;
    if ( v11 < 0.0 )
      v11 = -v11;
    *(float *)&ptQTask[77].tQTaskChildren.ptMiddle = v11 * *(float *)&v9[21].ptParent * 3.0 + v10;
    ptState->pfState = HumanPlayer_RunStateWalkBackwardLeft;
  }
  else
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    ptQTask[77].tQTaskChildren.ptMiddle = nullptr;
    ptState->pfState = HumanPlayer_RunStateWalkBackwardLeft;
  }
}

// source: j/0/human/humanplayer.c:7049  [size]
void __cdecl HumanPlayer_RunStateWalkBackwardLeft(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptHumanPlayer; };
    struct { char igi2_o1[8]; float vMaxYDelta; };
    struct { char igi2_o2[36]; struct real32x3_t tReal32x3; };
    struct { char igi2_o3[48]; struct real64x3_t tReal64x3; };
    char igi2_extent[76];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v2; // ebp
  unsigned int bSignal; // ecx
  void (__cdecl *v4)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v6)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v7)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v8)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v9)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v10)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v11)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v12)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v13)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v14)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v15)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v16)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v17)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v18)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v19)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v20)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v21)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v22)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v23)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v24)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v25)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v26)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v27)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v28)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v29)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v30)(struct State_s *, struct QTask_s *); // eax
  char ptPrev; // al
  void (__cdecl *v32)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v33)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v34)(struct State_s *, struct QTask_s *); // eax
  bool v35; // zf
  void (__cdecl *v36)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v37)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v38)(struct State_s *, struct QTask_s *); // eax

  v2 = ptQTask;
  igi2_frame.vMaxYDelta = *(float *)&ptQTask[81].ptNext * -477.1839904785156;
  igi2_frame.ptHumanPlayer = *(float *)&ptQTask[81].ptNext * -442.3680114746094;
  HumanPlayer_MoveOnGround((struct HumanPlayer_t *)ptQTask, igi2_frame.ptHumanPlayer, 58.98240280151367, igi2_frame.vMaxYDelta, 63.62453079223633);
  bSignal = ptState->bSignal;
  if ( (bSignal & 0x800000) != 0 )
  {
    v4 = ptState->apfExitState[ptState->nState];
    if ( v4 )
      v4(ptState, v2);
    apfState = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 21;
    v6 = apfState[21];
    ptState->pfState = v6;
    v6(ptState, v2);
  }
  else if ( (bSignal & 2) != 0 )
  {
    if ( (bSignal & 0x20000) != 0 )
    {
      v10 = ptState->apfExitState[ptState->nState];
      if ( v10 )
        v10(ptState, v2);
      v11 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 55;
      v12 = v11[55];
      ptState->pfState = v12;
      v12(ptState, v2);
    }
    else if ( (bSignal & 0x10000) != 0 )
    {
      v13 = ptState->apfExitState[ptState->nState];
      if ( v13 )
        v13(ptState, v2);
      v14 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 54;
      v15 = v14[54];
      ptState->pfState = v15;
      v15(ptState, v2);
    }
    else if ( (bSignal & 0x40000) != 0 )
    {
      if ( *(float *)&v2[20].tQTaskChildren.ptHead != 0.0
        && *(float *)&v2[13].eQTaskType == 0.0
        && ((int)v2[50].ptPrev & 8) != 0 )
      {
        v19 = ptState->apfExitState[ptState->nState];
        if ( v19 )
          v19(ptState, v2);
        v20 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 36;
        v21 = v20[36];
        ptState->pfState = v21;
        v21(ptState, v2);
      }
      else if ( (bSignal & 0x100) != 0 )
      {
        if ( (bSignal & 0x20) != 0 )
        {
          if ( (bSignal & 0x1000000) != 0 )
          {
            v2[83].tQTaskRefList.ptHead = nullptr;
            v28 = ptState->apfExitState[ptState->nState];
            if ( v28 )
              v28(ptState, v2);
            v29 = ptState->apfState;
            ptState->nPreviousState = ptState->nState;
            ptState->nState = 23;
            v30 = v29[23];
            ptState->pfState = v30;
            v30(ptState, v2);
          }
          else if ( ((bSignal & 0x2000) != 0 || (ptPrev = (char)v2[50].ptPrev, (ptPrev & 1) == 0))
                 && (ptPrev = (char)v2[50].ptPrev, (ptPrev & 2) != 0) )
          {
            v2[83].tQTaskRefList.ptHead = (struct QReference_s *)1;
            v32 = ptState->apfExitState[ptState->nState];
            if ( v32 )
              v32(ptState, v2);
            v33 = ptState->apfState;
            ptState->nPreviousState = ptState->nState;
            ptState->nState = 23;
            v34 = v33[23];
            ptState->pfState = v34;
            v34(ptState, v2);
          }
          else if ( (bSignal & 0x20000000) != 0
                 && (ptPrev & 4) != 0
                 && (qmemcpy(&igi2_frame.tReal64x3, &v2[1], sizeof(igi2_frame.tReal64x3)),
                     ptQTask = nullptr,
                     *(_DWORD *)&v2[32].eQTaskType = 2,
                     Human_ObjectCollision(v2, &igi2_frame.tReal64x3, &igi2_frame.tReal64x3, &igi2_frame.tReal32x3, (unsigned int *)&ptQTask),
                     v35 = ((unsigned __int8)ptQTask & 4) == 0,
                     *(_DWORD *)&v2[32].eQTaskType = 0,
                     v35) )
          {
            v36 = ptState->apfExitState[ptState->nState];
            if ( v36 )
              v36(ptState, v2);
            v37 = ptState->apfState;
            ptState->nPreviousState = ptState->nState;
            ptState->nState = 75;
            v38 = v37[75];
            ptState->pfState = v38;
            v38(ptState, v2);
          }
          else
          {
            HumanPlayer_SendWalkEvent(v2, false);
          }
        }
        else
        {
          v25 = ptState->apfExitState[ptState->nState];
          if ( v25 )
            v25(ptState, v2);
          v26 = ptState->apfState;
          ptState->nPreviousState = ptState->nState;
          ptState->nState = 14;
          v27 = v26[14];
          ptState->pfState = v27;
          v27(ptState, v2);
        }
      }
      else
      {
        v22 = ptState->apfExitState[ptState->nState];
        if ( v22 )
          v22(ptState, v2);
        v23 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 17;
        v24 = v23[17];
        ptState->pfState = v24;
        v24(ptState, v2);
      }
    }
    else
    {
      v16 = ptState->apfExitState[ptState->nState];
      if ( v16 )
        v16(ptState, v2);
      v17 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 8;
      v18 = v17[8];
      ptState->pfState = v18;
      v18(ptState, v2);
    }
  }
  else
  {
    v7 = ptState->apfExitState[ptState->nState];
    if ( v7 )
      v7(ptState, v2);
    v8 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 37;
    v9 = v8[37];
    ptState->pfState = v9;
    v9(ptState, v2);
  }
}

// source: j/0/human/humanplayer.c:7128  [size]
void __cdecl HumanPlayer_InitStateWalkRight(struct State_s *ptState, struct QTask_s *ptQTask)
{
  struct QTask_s *ptTail; // eax
  struct QTask_s *ptParent; // ecx
  double v4; // st7
  struct QTask_s *v5; // eax
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *v8; // ecx
  double v9; // st7
  double v10; // st6
  int v11; // [esp+10h] [ebp-8h]

  *(_DWORD *)&ptQTask[32].eQTaskType = 0;
  if ( ptState->nPreviousState == 32 )
  {
    ptTail = ptQTask[34].tQTaskChildren.ptTail;
    ptParent = ptTail[1].ptParent;
    if ( ptParent )
      v4 = (double)(int)ptTail[1].tQTaskRefList.ptMiddle / (double)(int)ptParent->tQTaskChildren.ptTail;
    else
      v4 = 0.0;
    v5 = ptTail[1].ptParent;
    if ( v5 )
      v11 = (int)v5->tQTaskChildren.ptTail;
    else
      v11 = 0;
    HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, (__int64)((double)v11 * v4), 0.20000000298023224);
  }
  else
  {
    HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, 0, 0.20000000298023224);
  }
  ptNext = ptQTask[33].ptNext;
  ptQTask[77].ptParent = (struct QTask_s *)2;
  ptPrev = ptNext[1].ptPrev;
  if ( ptPrev && (v8 = ptPrev->tQTaskChildren.ptTail) != nullptr )
  {
    ptQTask[77].tQTaskChildren.ptHead = (struct QTask_s *)2;
    v9 = *(float *)&v8[21].tQTaskChildren.ptHead;
    ptQTask[77].tQTaskChildren.ptMiddle = v8[21].tQTaskChildren.ptHead;
    v10 = *(float *)&ptQTask[43].ptParent;
    if ( v10 < 0.0 )
      v10 = -v10;
    *(float *)&ptQTask[77].tQTaskChildren.ptMiddle = v10 * *(float *)&v8[21].ptParent * 3.0 + v9;
    ptState->pfState = HumanPlayer_RunStateWalkRight;
  }
  else
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    ptQTask[77].tQTaskChildren.ptMiddle = nullptr;
    ptState->pfState = HumanPlayer_RunStateWalkRight;
  }
}

// source: j/0/human/humanplayer.c:7166  [size]
void __cdecl HumanPlayer_RunStateWalkRight(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vMaxYDelta; };
    struct { char igi2_o1[28]; struct real32x3_t tReal32x3; };
    struct { char igi2_o2[40]; struct real64x3_t tReal64x3; };
    char igi2_extent[68];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v2; // ebp
  unsigned int bSignal; // ecx
  void (__cdecl *v4)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v6)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v7)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v8)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v9)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v10)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v11)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v12)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v13)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v14)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v15)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v16)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v17)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v18)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v19)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v20)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v21)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v22)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v23)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v24)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v25)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v26)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v27)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v28)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v29)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v30)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v31)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v32)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v33)(struct State_s *, struct QTask_s *); // eax
  char ptPrev; // al
  void (__cdecl *v35)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v36)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v37)(struct State_s *, struct QTask_s *); // eax
  bool v38; // zf
  void (__cdecl *v39)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v40)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v41)(struct State_s *, struct QTask_s *); // eax

  v2 = ptQTask;
  igi2_frame.vMaxYDelta = *(float *)&ptQTask[81].ptNext * 477.1839904785156;
  HumanPlayer_MoveOnGround((struct HumanPlayer_t *)ptQTask, 0.0, 58.98240280151367, igi2_frame.vMaxYDelta, 63.62453079223633);
  bSignal = ptState->bSignal;
  if ( (bSignal & 0x800000) != 0 )
  {
    v4 = ptState->apfExitState[ptState->nState];
    if ( v4 )
      v4(ptState, v2);
    apfState = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 21;
    v6 = apfState[21];
    ptState->pfState = v6;
    v6(ptState, v2);
  }
  else if ( (bSignal & 2) != 0 )
  {
    if ( (bSignal & 0x20000) != 0 )
    {
      v10 = ptState->apfExitState[ptState->nState];
      if ( v10 )
        v10(ptState, v2);
      v11 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 55;
      v12 = v11[55];
      ptState->pfState = v12;
      v12(ptState, v2);
    }
    else if ( (bSignal & 0x10000) != 0 )
    {
      v13 = ptState->apfExitState[ptState->nState];
      if ( v13 )
        v13(ptState, v2);
      v14 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 54;
      v15 = v14[54];
      ptState->pfState = v15;
      v15(ptState, v2);
    }
    else if ( (bSignal & 0x40000) != 0 )
    {
      if ( *(float *)&v2[20].tQTaskChildren.ptHead != 0.0
        && *(float *)&v2[13].eQTaskType == 0.0
        && ((int)v2[50].ptPrev & 8) != 0 )
      {
        v19 = ptState->apfExitState[ptState->nState];
        if ( v19 )
          v19(ptState, v2);
        v20 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 36;
        v21 = v20[36];
        ptState->pfState = v21;
        v21(ptState, v2);
      }
      else if ( (bSignal & 0x40) != 0 )
      {
        if ( (bSignal & 0x80u) == 0 )
        {
          if ( (bSignal & 0x100) != 0 )
          {
            v28 = ptState->apfExitState[ptState->nState];
            if ( v28 )
              v28(ptState, v2);
            v29 = ptState->apfState;
            ptState->nPreviousState = ptState->nState;
            ptState->nState = 15;
            v30 = v29[15];
            ptState->pfState = v30;
            v30(ptState, v2);
          }
          else if ( (bSignal & 0x1000000) != 0 )
          {
            v2[83].tQTaskRefList.ptHead = nullptr;
            v31 = ptState->apfExitState[ptState->nState];
            if ( v31 )
              v31(ptState, v2);
            v32 = ptState->apfState;
            ptState->nPreviousState = ptState->nState;
            ptState->nState = 23;
            v33 = v32[23];
            ptState->pfState = v33;
            v33(ptState, v2);
          }
          else if ( ((bSignal & 0x2000) != 0 || (ptPrev = (char)v2[50].ptPrev, (ptPrev & 1) == 0))
                 && (ptPrev = (char)v2[50].ptPrev, (ptPrev & 2) != 0) )
          {
            v2[83].tQTaskRefList.ptHead = (struct QReference_s *)1;
            v35 = ptState->apfExitState[ptState->nState];
            if ( v35 )
              v35(ptState, v2);
            v36 = ptState->apfState;
            ptState->nPreviousState = ptState->nState;
            ptState->nState = 23;
            v37 = v36[23];
            ptState->pfState = v37;
            v37(ptState, v2);
          }
          else if ( (bSignal & 0x20000000) != 0
                 && (ptPrev & 4) != 0
                 && (ptQTask = nullptr,
                     qmemcpy(&igi2_frame.tReal64x3, &v2[1], sizeof(igi2_frame.tReal64x3)),
                     *(_DWORD *)&v2[32].eQTaskType = 2,
                     Human_ObjectCollision(v2, &igi2_frame.tReal64x3, &igi2_frame.tReal64x3, &igi2_frame.tReal32x3, (unsigned int *)&ptQTask),
                     v38 = ((unsigned __int8)ptQTask & 4) == 0,
                     *(_DWORD *)&v2[32].eQTaskType = 0,
                     v38) )
          {
            v39 = ptState->apfExitState[ptState->nState];
            if ( v39 )
              v39(ptState, v2);
            v40 = ptState->apfState;
            ptState->nPreviousState = ptState->nState;
            ptState->nState = 75;
            v41 = v40[75];
            ptState->pfState = v41;
            v41(ptState, v2);
          }
          else
          {
            HumanPlayer_SendWalkEvent(v2, false);
          }
        }
        else
        {
          v25 = ptState->apfExitState[ptState->nState];
          if ( v25 )
            v25(ptState, v2);
          v26 = ptState->apfState;
          ptState->nPreviousState = ptState->nState;
          ptState->nState = 12;
          v27 = v26[12];
          ptState->pfState = v27;
          v27(ptState, v2);
        }
      }
      else
      {
        v22 = ptState->apfExitState[ptState->nState];
        if ( v22 )
          v22(ptState, v2);
        v23 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 0;
        v24 = *v23;
        ptState->pfState = v24;
        v24(ptState, v2);
      }
    }
    else
    {
      v16 = ptState->apfExitState[ptState->nState];
      if ( v16 )
        v16(ptState, v2);
      v17 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 9;
      v18 = v17[9];
      ptState->pfState = v18;
      v18(ptState, v2);
    }
  }
  else
  {
    v7 = ptState->apfExitState[ptState->nState];
    if ( v7 )
      v7(ptState, v2);
    v8 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 37;
    v9 = v8[37];
    ptState->pfState = v9;
    v9(ptState, v2);
  }
}

// source: j/0/human/humanplayer.c:7246  [size]
void __cdecl HumanPlayer_InitStateWalkLeft(struct State_s *ptState, struct QTask_s *ptQTask)
{
  struct QTask_s *ptTail; // eax
  struct QTask_s *ptParent; // ecx
  double v4; // st7
  struct QTask_s *v5; // eax
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *v8; // ecx
  double v9; // st7
  double v10; // st6
  int v11; // [esp+10h] [ebp-8h]

  *(_DWORD *)&ptQTask[32].eQTaskType = 0;
  if ( ptState->nPreviousState == 33 )
  {
    ptTail = ptQTask[34].tQTaskChildren.ptTail;
    ptParent = ptTail[1].ptParent;
    if ( ptParent )
      v4 = (double)(int)ptTail[1].tQTaskRefList.ptMiddle / (double)(int)ptParent->tQTaskChildren.ptTail;
    else
      v4 = 0.0;
    v5 = ptTail[1].ptParent;
    if ( v5 )
      v11 = (int)v5->tQTaskChildren.ptTail;
    else
      v11 = 0;
    HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, (__int64)((double)v11 * v4), 0.20000000298023224);
  }
  else
  {
    HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, 0, 0.20000000298023224);
  }
  ptNext = ptQTask[33].ptNext;
  ptQTask[77].ptParent = (struct QTask_s *)2;
  ptPrev = ptNext[1].ptPrev;
  if ( ptPrev && (v8 = ptPrev->tQTaskChildren.ptTail) != nullptr )
  {
    ptQTask[77].tQTaskChildren.ptHead = (struct QTask_s *)2;
    v9 = *(float *)&v8[21].tQTaskChildren.ptHead;
    ptQTask[77].tQTaskChildren.ptMiddle = v8[21].tQTaskChildren.ptHead;
    v10 = *(float *)&ptQTask[43].ptParent;
    if ( v10 < 0.0 )
      v10 = -v10;
    *(float *)&ptQTask[77].tQTaskChildren.ptMiddle = v10 * *(float *)&v8[21].ptParent * 3.0 + v9;
    ptState->pfState = HumanPlayer_RunStateWalkLeft;
  }
  else
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    ptQTask[77].tQTaskChildren.ptMiddle = nullptr;
    ptState->pfState = HumanPlayer_RunStateWalkLeft;
  }
}

// source: j/0/human/humanplayer.c:7284  [size]
void __cdecl HumanPlayer_RunStateWalkLeft(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vMaxYDelta; };
    struct { char igi2_o1[28]; struct real32x3_t tReal32x3; };
    struct { char igi2_o2[40]; struct real64x3_t tReal64x3; };
    char igi2_extent[68];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v2; // ebp
  unsigned int bSignal; // ecx
  void (__cdecl *v4)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v6)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v7)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v8)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v9)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v10)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v11)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v12)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v13)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v14)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v15)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v16)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v17)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v18)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v19)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v20)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v21)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v22)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v23)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v24)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v25)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v26)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v27)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v28)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v29)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v30)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v31)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v32)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v33)(struct State_s *, struct QTask_s *); // eax
  char ptPrev; // al
  void (__cdecl *v35)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v36)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v37)(struct State_s *, struct QTask_s *); // eax
  bool v38; // zf
  void (__cdecl *v39)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v40)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v41)(struct State_s *, struct QTask_s *); // eax

  v2 = ptQTask;
  igi2_frame.vMaxYDelta = *(float *)&ptQTask[81].ptNext * -477.1839904785156;
  HumanPlayer_MoveOnGround((struct HumanPlayer_t *)ptQTask, 0.0, 58.98240280151367, igi2_frame.vMaxYDelta, 63.62453079223633);
  bSignal = ptState->bSignal;
  if ( (bSignal & 0x800000) != 0 )
  {
    v4 = ptState->apfExitState[ptState->nState];
    if ( v4 )
      v4(ptState, v2);
    apfState = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 21;
    v6 = apfState[21];
    ptState->pfState = v6;
    v6(ptState, v2);
  }
  else if ( (bSignal & 2) != 0 )
  {
    if ( (bSignal & 0x20000) != 0 )
    {
      v10 = ptState->apfExitState[ptState->nState];
      if ( v10 )
        v10(ptState, v2);
      v11 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 55;
      v12 = v11[55];
      ptState->pfState = v12;
      v12(ptState, v2);
    }
    else if ( (bSignal & 0x10000) != 0 )
    {
      v13 = ptState->apfExitState[ptState->nState];
      if ( v13 )
        v13(ptState, v2);
      v14 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 54;
      v15 = v14[54];
      ptState->pfState = v15;
      v15(ptState, v2);
    }
    else if ( (bSignal & 0x40000) != 0 )
    {
      if ( *(float *)&v2[20].tQTaskChildren.ptHead != 0.0
        && *(float *)&v2[13].eQTaskType == 0.0
        && ((int)v2[50].ptPrev & 8) != 0 )
      {
        v19 = ptState->apfExitState[ptState->nState];
        if ( v19 )
          v19(ptState, v2);
        v20 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 36;
        v21 = v20[36];
        ptState->pfState = v21;
        v21(ptState, v2);
      }
      else if ( (bSignal & 0x20) != 0 )
      {
        if ( (bSignal & 0x80u) == 0 )
        {
          if ( (bSignal & 0x100) != 0 )
          {
            v28 = ptState->apfExitState[ptState->nState];
            if ( v28 )
              v28(ptState, v2);
            v29 = ptState->apfState;
            ptState->nPreviousState = ptState->nState;
            ptState->nState = 16;
            v30 = v29[16];
            ptState->pfState = v30;
            v30(ptState, v2);
          }
          else if ( (bSignal & 0x1000000) != 0 )
          {
            v2[83].tQTaskRefList.ptHead = nullptr;
            v31 = ptState->apfExitState[ptState->nState];
            if ( v31 )
              v31(ptState, v2);
            v32 = ptState->apfState;
            ptState->nPreviousState = ptState->nState;
            ptState->nState = 23;
            v33 = v32[23];
            ptState->pfState = v33;
            v33(ptState, v2);
          }
          else if ( ((bSignal & 0x2000) != 0 || (ptPrev = (char)v2[50].ptPrev, (ptPrev & 1) == 0))
                 && (ptPrev = (char)v2[50].ptPrev, (ptPrev & 2) != 0) )
          {
            v2[83].tQTaskRefList.ptHead = (struct QReference_s *)1;
            v35 = ptState->apfExitState[ptState->nState];
            if ( v35 )
              v35(ptState, v2);
            v36 = ptState->apfState;
            ptState->nPreviousState = ptState->nState;
            ptState->nState = 23;
            v37 = v36[23];
            ptState->pfState = v37;
            v37(ptState, v2);
          }
          else if ( (bSignal & 0x20000000) != 0
                 && (ptPrev & 4) != 0
                 && (ptQTask = nullptr,
                     qmemcpy(&igi2_frame.tReal64x3, &v2[1], sizeof(igi2_frame.tReal64x3)),
                     *(_DWORD *)&v2[32].eQTaskType = 2,
                     Human_ObjectCollision(v2, &igi2_frame.tReal64x3, &igi2_frame.tReal64x3, &igi2_frame.tReal32x3, (unsigned int *)&ptQTask),
                     v38 = ((unsigned __int8)ptQTask & 4) == 0,
                     *(_DWORD *)&v2[32].eQTaskType = 0,
                     v38) )
          {
            v39 = ptState->apfExitState[ptState->nState];
            if ( v39 )
              v39(ptState, v2);
            v40 = ptState->apfState;
            ptState->nPreviousState = ptState->nState;
            ptState->nState = 75;
            v41 = v40[75];
            ptState->pfState = v41;
            v41(ptState, v2);
          }
          else
          {
            HumanPlayer_SendWalkEvent(v2, false);
          }
        }
        else
        {
          v25 = ptState->apfExitState[ptState->nState];
          if ( v25 )
            v25(ptState, v2);
          v26 = ptState->apfState;
          ptState->nPreviousState = ptState->nState;
          ptState->nState = 13;
          v27 = v26[13];
          ptState->pfState = v27;
          v27(ptState, v2);
        }
      }
      else
      {
        v22 = ptState->apfExitState[ptState->nState];
        if ( v22 )
          v22(ptState, v2);
        v23 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 0;
        v24 = *v23;
        ptState->pfState = v24;
        v24(ptState, v2);
      }
    }
    else
    {
      v16 = ptState->apfExitState[ptState->nState];
      if ( v16 )
        v16(ptState, v2);
      v17 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 10;
      v18 = v17[10];
      ptState->pfState = v18;
      v18(ptState, v2);
    }
  }
  else
  {
    v7 = ptState->apfExitState[ptState->nState];
    if ( v7 )
      v7(ptState, v2);
    v8 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 37;
    v9 = v8[37];
    ptState->pfState = v9;
    v9(ptState, v2);
  }
}

// source: j/0/human/humanplayer.c:7364  [anchor-mhash]
void __cdecl HumanPlayer_InitStateCrouch(struct State_s *ptState, struct QTask_s *ptQTask)
{
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptTail; // ecx
  double v5; // st7
  double v6; // st6

  if ( *(_DWORD *)&ptQTask[32].eQTaskType == 2 )
    HumanPlayer_LeaveZoomAlternateFireMode(ptQTask);
  *(_DWORD *)&ptQTask[32].eQTaskType = 1;
  HumanAnim_SetAnimationAndTimeFromState(ptQTask, 25, 0, 0.20000000298023224);
  ptNext = ptQTask[33].ptNext;
  ptQTask[77].ptParent = (struct QTask_s *)4;
  ptPrev = ptNext[1].ptPrev;
  if ( ptPrev && (ptTail = ptPrev->tQTaskChildren.ptTail) != nullptr )
  {
    ptQTask[77].tQTaskChildren.ptHead = (struct QTask_s *)3;
    v5 = *(float *)&ptTail[21].tQTaskChildren.ptMiddle;
    ptQTask[77].tQTaskChildren.ptMiddle = ptTail[21].tQTaskChildren.ptMiddle;
    v6 = *(float *)&ptQTask[43].ptParent;
    if ( v6 < 0.0 )
      v6 = -v6;
    *(float *)&ptQTask[77].tQTaskChildren.ptMiddle = v6 * *(float *)&ptTail[21].ptParent * 3.0 + v5;
    ptState->pfState = HumanPlayer_RunStateCrouch;
  }
  else
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    ptQTask[77].tQTaskChildren.ptMiddle = nullptr;
    ptState->pfState = HumanPlayer_RunStateCrouch;
  }
}

// source: j/0/human/humanplayer.c:7405  [anchor-mhash]
void __cdecl HumanPlayer_CrouchStateCheckWaterDepth(struct State_s *ptState, struct QTask_s *ptQTask)
{
  void (__cdecl *v2)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v4)(struct State_s *, struct QTask_s *); // eax

  if ( *(float *)&ptQTask[51].tQTaskRefList.ptMiddle >= 3276.800048828125 )
  {
    v2 = ptState->apfExitState[ptState->nState];
    if ( v2 )
      v2(ptState, ptQTask);
    apfState = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 0;
    v4 = *apfState;
    ptState->pfState = v4;
    v4(ptState, ptQTask);
  }
}

// source: j/0/human/humanplayer.c:7419  [anchor-mhash]
void __cdecl HumanPlayer_RunStateCrouch(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { unsigned int bSignal; };
    struct { char igi2_o1[4]; struct real32x3_t tReal32x3; };
    struct { char igi2_o2[16]; struct real64x3_t tReal64x3; };
    char igi2_extent[44];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v2; // ebx
  struct State_s *v3; // ebp
  unsigned int v4; // ecx
  void (__cdecl *v5)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v7)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v8)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v9)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v10)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v11)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v12)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v13)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v14)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v15)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v16)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v17)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v18)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v19)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v20)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v21)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v22)(struct State_s *, struct QTask_s *); // eax
  bool v23; // zf
  void (__cdecl *v24)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v25)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v26)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v27)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v28)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v29)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v30)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v31)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v32)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v33)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v34)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v35)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v36)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v37)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v38)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v39)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v40)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v41)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v42)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v43)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v44)(struct State_s *, struct QTask_s *); // eax

  v2 = ptQTask;
  v3 = ptState;
  igi2_frame.bSignal = ptState->bSignal;
  HumanPlayer_MoveOnGround((struct HumanPlayer_t *)ptQTask, 0.0, 118.76579284667969, 0.0, 118.76579284667969);
  v4 = igi2_frame.bSignal;
  if ( (igi2_frame.bSignal & 0x800000) != 0 )
  {
    v5 = v3->apfExitState[v3->nState];
    if ( v5 )
      v5(v3, v2);
    apfState = v3->apfState;
    v3->nPreviousState = v3->nState;
    v3->nState = 21;
    v7 = apfState[21];
    v3->pfState = v7;
    v7(v3, v2);
    return;
  }
  if ( (igi2_frame.bSignal & 2) == 0 )
  {
    v8 = v3->apfExitState[v3->nState];
    if ( v8 )
      v8(v3, v2);
    v9 = v3->apfState;
    v3->nPreviousState = v3->nState;
    v3->nState = 37;
    v10 = v9[37];
    v3->pfState = v10;
    v10(v3, v2);
    return;
  }
  if ( (igi2_frame.bSignal & 0x20000) != 0 )
  {
    v11 = v3->apfExitState[v3->nState];
    if ( v11 )
      v11(v3, v2);
    v12 = v3->apfState;
    v3->nPreviousState = v3->nState;
    v3->nState = 55;
    v13 = v12[55];
    v3->pfState = v13;
    v13(v3, v2);
    return;
  }
  if ( (igi2_frame.bSignal & 0x10000) != 0 )
  {
    v14 = v3->apfExitState[v3->nState];
    if ( v14 )
      v14(v3, v2);
    v15 = v3->apfState;
    v3->nPreviousState = v3->nState;
    v3->nState = 54;
    v16 = v15[54];
    v3->pfState = v16;
    v16(v3, v2);
    return;
  }
  if ( v2[83].tQTaskRefList.ptHead && (igi2_frame.bSignal & 0x2000) == 0 && ((int)v2[50].ptPrev & 1) != 0 )
  {
    v17 = v3->apfExitState[v3->nState];
    if ( v17 )
      v17(v3, v2);
    v18 = v3->apfState;
    v3->nPreviousState = v3->nState;
    v3->nState = 0;
    v19 = *v18;
    v3->pfState = *v18;
    v19(v3, v2);
    return;
  }
  if ( (igi2_frame.bSignal & 0x12000000) != 0 && ((int)v2[50].ptPrev & 1) != 0 )
  {
    v20 = v3->apfExitState[v3->nState];
    if ( v20 )
      v20(v3, v2);
    v21 = v3->apfState;
    v3->nPreviousState = v3->nState;
    v3->nState = 0;
    v22 = *v21;
    v3->pfState = v22;
    v22(v3, v2);
    return;
  }
  if ( (igi2_frame.bSignal & 0x21000000) != 0 && ((int)v2[50].ptPrev & 4) != 0 )
  {
    ptState = nullptr;
    qmemcpy(&igi2_frame.tReal64x3, &v2[1], sizeof(igi2_frame.tReal64x3));
    *(_DWORD *)&v2[32].eQTaskType = 2;
    Human_ObjectCollision(v2, &igi2_frame.tReal64x3, &igi2_frame.tReal64x3, &igi2_frame.tReal32x3, (unsigned int *)&ptState);
    v23 = ((unsigned __int8)ptState & 4) == 0;
    *(_DWORD *)&v2[32].eQTaskType = 1;
    if ( v23 )
    {
      v24 = v3->apfExitState[v3->nState];
      if ( v24 )
        v24(v3, v2);
      v25 = v3->apfState;
      v3->nPreviousState = v3->nState;
      v3->nState = 75;
      v26 = v25[75];
      v3->pfState = v26;
      v26(v3, v2);
      return;
    }
    v4 = igi2_frame.bSignal;
  }
  if ( *(float *)&v2[20].tQTaskChildren.ptHead != 0.0
    && *(float *)&v2[13].eQTaskType == 0.0
    && ((int)v2[50].ptPrev & 8) != 0 )
  {
    v27 = v3->apfExitState[v3->nState];
    if ( v27 )
      v27(v3, v2);
    v28 = v3->apfState;
    v3->nPreviousState = v3->nState;
    v3->nState = 36;
    v29 = v28[36];
    v3->pfState = v29;
    v29(v3, v2);
  }
  else if ( (v4 & 0x40) != 0 )
  {
    v30 = v3->apfExitState[v3->nState];
    if ( v30 )
      v30(v3, v2);
    v31 = v3->apfState;
    v3->nPreviousState = v3->nState;
    v3->nState = 32;
    v32 = v31[32];
    v3->pfState = v32;
    v32(v3, v2);
  }
  else if ( (v4 & 0x20) != 0 )
  {
    v33 = v3->apfExitState[v3->nState];
    if ( v33 )
      v33(v3, v2);
    v34 = v3->apfState;
    v3->nPreviousState = v3->nState;
    v3->nState = 33;
    v35 = v34[33];
    v3->pfState = v35;
    v35(v3, v2);
  }
  else if ( (v4 & 0x80u) == 0 )
  {
    if ( (v4 & 0x100) != 0 )
    {
      v39 = v3->apfExitState[v3->nState];
      if ( v39 )
        v39(v3, v2);
      v40 = v3->apfState;
      v3->nPreviousState = v3->nState;
      v3->nState = 29;
      v41 = v40[29];
      v3->pfState = v41;
      v41(v3, v2);
    }
    else if ( (v4 & 0x8000000) != 0 )
    {
      v42 = v3->apfExitState[v3->nState];
      if ( v42 )
        v42(v3, v2);
      v43 = v3->apfState;
      v3->nPreviousState = v3->nState;
      v3->nState = 24;
      v44 = v43[24];
      v3->pfState = v44;
      v44(v3, v2);
    }
    else
    {
      HumanPlayer_CrouchStateCheckWaterDepth(v3, v2);
    }
  }
  else
  {
    v36 = v3->apfExitState[v3->nState];
    if ( v36 )
      v36(v3, v2);
    v37 = v3->apfState;
    v3->nPreviousState = v3->nState;
    v3->nState = 26;
    v38 = v37[26];
    v3->pfState = v38;
    v38(v3, v2);
  }
}

// source: j/0/human/humanplayer.c:7505  [anchor-mhash]
void __cdecl HumanPlayer_InitStateCrouchTurn(struct State_s *ptState, struct QTask_s *ptQTask)
{
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptTail; // ecx
  double v5; // st7
  double v6; // st6

  if ( *(_DWORD *)&ptQTask[32].eQTaskType == 2 )
    HumanPlayer_LeaveZoomAlternateFireMode(ptQTask);
  *(_DWORD *)&ptQTask[32].eQTaskType = 1;
  ptQTask[83].tQTaskRefList.ptMiddle = nullptr;
  HumanAnim_SetAnimationAndTimeFromState(ptQTask, 24, 0, 0.20000000298023224);
  ptNext = ptQTask[33].ptNext;
  ptQTask[77].ptParent = (struct QTask_s *)4;
  ptPrev = ptNext[1].ptPrev;
  if ( ptPrev && (ptTail = ptPrev->tQTaskChildren.ptTail) != nullptr )
  {
    ptQTask[77].tQTaskChildren.ptHead = (struct QTask_s *)3;
    v5 = *(float *)&ptTail[21].tQTaskChildren.ptMiddle;
    ptQTask[77].tQTaskChildren.ptMiddle = ptTail[21].tQTaskChildren.ptMiddle;
    v6 = *(float *)&ptQTask[43].ptParent;
    if ( v6 < 0.0 )
      v6 = -v6;
    *(float *)&ptQTask[77].tQTaskChildren.ptMiddle = v6 * *(float *)&ptTail[21].ptParent * 3.0 + v5;
    ptState->pfState = HumanPlayer_RunStateCrouchTurn;
  }
  else
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    ptQTask[77].tQTaskChildren.ptMiddle = nullptr;
    ptState->pfState = HumanPlayer_RunStateCrouchTurn;
  }
}

// source: j/0/human/humanplayer.c:7539  [anchor-mhash]
void __cdecl HumanPlayer_RunStateCrouchTurn(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { unsigned int bSignal; };
    struct { char igi2_o1[4]; struct real32x3_t tReal32x3; };
    struct { char igi2_o2[16]; struct real64x3_t tReal64x3; };
    char igi2_extent[44];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v2; // ebx
  struct State_s *v3; // ebp
  unsigned int v4; // ecx
  void (__cdecl *v5)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v7)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v8)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v9)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v10)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v11)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v12)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v13)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v14)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v15)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v16)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v17)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v18)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v19)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v20)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v21)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v22)(struct State_s *, struct QTask_s *); // eax
  bool v23; // zf
  void (__cdecl *v24)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v25)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v26)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v27)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v28)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v29)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v30)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v31)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v32)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v33)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v34)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v35)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v36)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v37)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v38)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v39)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v40)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v41)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v42)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v43)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v44)(struct State_s *, struct QTask_s *); // eax

  v2 = ptQTask;
  v3 = ptState;
  igi2_frame.bSignal = ptState->bSignal;
  HumanPlayer_MoveOnGround((struct HumanPlayer_t *)ptQTask, 0.0, 118.76579284667969, 0.0, 118.76579284667969);
  v4 = igi2_frame.bSignal;
  if ( (igi2_frame.bSignal & 0x800000) != 0 )
  {
    v5 = v3->apfExitState[v3->nState];
    if ( v5 )
      v5(v3, v2);
    apfState = v3->apfState;
    v3->nPreviousState = v3->nState;
    v3->nState = 21;
    v7 = apfState[21];
    v3->pfState = v7;
    v7(v3, v2);
    return;
  }
  if ( (igi2_frame.bSignal & 2) == 0 )
  {
    v8 = v3->apfExitState[v3->nState];
    if ( v8 )
      v8(v3, v2);
    v9 = v3->apfState;
    v3->nPreviousState = v3->nState;
    v3->nState = 37;
    v10 = v9[37];
    v3->pfState = v10;
    v10(v3, v2);
    return;
  }
  if ( (igi2_frame.bSignal & 0x20000) != 0 )
  {
    v11 = v3->apfExitState[v3->nState];
    if ( v11 )
      v11(v3, v2);
    v12 = v3->apfState;
    v3->nPreviousState = v3->nState;
    v3->nState = 55;
    v13 = v12[55];
    v3->pfState = v13;
    v13(v3, v2);
    return;
  }
  if ( (igi2_frame.bSignal & 0x10000) != 0 )
  {
    v14 = v3->apfExitState[v3->nState];
    if ( v14 )
      v14(v3, v2);
    v15 = v3->apfState;
    v3->nPreviousState = v3->nState;
    v3->nState = 54;
    v16 = v15[54];
    v3->pfState = v16;
    v16(v3, v2);
    return;
  }
  if ( v2[83].tQTaskRefList.ptHead && (igi2_frame.bSignal & 0x2000) == 0 && ((int)v2[50].ptPrev & 1) != 0 )
  {
    v17 = v3->apfExitState[v3->nState];
    if ( v17 )
      v17(v3, v2);
    v18 = v3->apfState;
    v3->nPreviousState = v3->nState;
    v3->nState = 0;
    v19 = *v18;
    v3->pfState = *v18;
    v19(v3, v2);
    return;
  }
  if ( (igi2_frame.bSignal & 0x12000000) != 0 && ((int)v2[50].ptPrev & 1) != 0 )
  {
    v20 = v3->apfExitState[v3->nState];
    if ( v20 )
      v20(v3, v2);
    v21 = v3->apfState;
    v3->nPreviousState = v3->nState;
    v3->nState = 0;
    v22 = *v21;
    v3->pfState = v22;
    v22(v3, v2);
    return;
  }
  if ( (igi2_frame.bSignal & 0x21000000) != 0 && ((int)v2[50].ptPrev & 4) != 0 )
  {
    ptState = nullptr;
    qmemcpy(&igi2_frame.tReal64x3, &v2[1], sizeof(igi2_frame.tReal64x3));
    *(_DWORD *)&v2[32].eQTaskType = 2;
    Human_ObjectCollision(v2, &igi2_frame.tReal64x3, &igi2_frame.tReal64x3, &igi2_frame.tReal32x3, (unsigned int *)&ptState);
    v23 = ((unsigned __int8)ptState & 4) == 0;
    *(_DWORD *)&v2[32].eQTaskType = 1;
    if ( v23 )
    {
      v24 = v3->apfExitState[v3->nState];
      if ( v24 )
        v24(v3, v2);
      v25 = v3->apfState;
      v3->nPreviousState = v3->nState;
      v3->nState = 75;
      v26 = v25[75];
      v3->pfState = v26;
      v26(v3, v2);
      return;
    }
    v4 = igi2_frame.bSignal;
  }
  if ( *(float *)&v2[20].tQTaskChildren.ptHead != 0.0
    && *(float *)&v2[13].eQTaskType == 0.0
    && ((int)v2[50].ptPrev & 8) != 0 )
  {
    v27 = v3->apfExitState[v3->nState];
    if ( v27 )
      v27(v3, v2);
    v28 = v3->apfState;
    v3->nPreviousState = v3->nState;
    v3->nState = 36;
    v29 = v28[36];
    v3->pfState = v29;
    v29(v3, v2);
  }
  else if ( (v4 & 0x40) != 0 )
  {
    v30 = v3->apfExitState[v3->nState];
    if ( v30 )
      v30(v3, v2);
    v31 = v3->apfState;
    v3->nPreviousState = v3->nState;
    v3->nState = 32;
    v32 = v31[32];
    v3->pfState = v32;
    v32(v3, v2);
  }
  else if ( (v4 & 0x20) != 0 )
  {
    v33 = v3->apfExitState[v3->nState];
    if ( v33 )
      v33(v3, v2);
    v34 = v3->apfState;
    v3->nPreviousState = v3->nState;
    v3->nState = 33;
    v35 = v34[33];
    v3->pfState = v35;
    v35(v3, v2);
  }
  else if ( (v4 & 0x80u) == 0 )
  {
    if ( (v4 & 0x100) != 0 )
    {
      v39 = v3->apfExitState[v3->nState];
      if ( v39 )
        v39(v3, v2);
      v40 = v3->apfState;
      v3->nPreviousState = v3->nState;
      v3->nState = 29;
      v41 = v40[29];
      v3->pfState = v41;
      v41(v3, v2);
    }
    else if ( (v4 & 0x8000000) != 0 || !v2[83].tQTaskRefList.ptMiddle )
    {
      if ( (v4 & 1) != 0 )
        v2[83].tQTaskRefList.ptMiddle = (struct QReference_s *)1;
      HumanPlayer_CrouchStateCheckWaterDepth(v3, v2);
    }
    else
    {
      v42 = v3->apfExitState[v3->nState];
      if ( v42 )
        v42(v3, v2);
      v43 = v3->apfState;
      v3->nPreviousState = v3->nState;
      v3->nState = 23;
      v44 = v43[23];
      v3->pfState = v44;
      v44(v3, v2);
    }
  }
  else
  {
    v36 = v3->apfExitState[v3->nState];
    if ( v36 )
      v36(v3, v2);
    v37 = v3->apfState;
    v3->nPreviousState = v3->nState;
    v3->nState = 26;
    v38 = v37[26];
    v3->pfState = v38;
    v38(v3, v2);
  }
}

// source: j/0/human/humanplayer.c:7633  [size]
void __cdecl HumanPlayer_InitStateCrouchWalkForward(struct State_s *ptState, struct QTask_s *ptQTask)
{
  struct QTask_s *ptTail; // eax
  struct QTask_s *ptParent; // ecx
  double v4; // st7
  struct QTask_s *v5; // eax
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *v8; // ecx
  double v9; // st7
  double v10; // st6
  int v11; // [esp+10h] [ebp-8h]

  *(_DWORD *)&ptQTask[32].eQTaskType = 1;
  if ( ptState->nPreviousState == 3 )
  {
    ptTail = ptQTask[34].tQTaskChildren.ptTail;
    ptParent = ptTail[1].ptParent;
    if ( ptParent )
      v4 = (double)(int)ptTail[1].tQTaskRefList.ptMiddle / (double)(int)ptParent->tQTaskChildren.ptTail;
    else
      v4 = 0.0;
    v5 = ptTail[1].ptParent;
    if ( v5 )
      v11 = (int)v5->tQTaskChildren.ptTail;
    else
      v11 = 0;
    HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, (__int64)((double)v11 * v4), 0.20000000298023224);
  }
  else
  {
    HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, 0, 0.20000000298023224);
  }
  ptNext = ptQTask[33].ptNext;
  ptQTask[77].ptParent = (struct QTask_s *)5;
  ptPrev = ptNext[1].ptPrev;
  if ( ptPrev && (v8 = ptPrev->tQTaskChildren.ptTail) != nullptr )
  {
    ptQTask[77].tQTaskChildren.ptHead = (struct QTask_s *)4;
    v9 = *(float *)&v8[21].tQTaskChildren.ptTail;
    ptQTask[77].tQTaskChildren.ptMiddle = v8[21].tQTaskChildren.ptTail;
    v10 = *(float *)&ptQTask[43].ptParent;
    if ( v10 < 0.0 )
      v10 = -v10;
    *(float *)&ptQTask[77].tQTaskChildren.ptMiddle = v10 * *(float *)&v8[21].ptParent * 3.0 + v9;
    ptState->pfState = HumanPlayer_RunStateCrouchWalkForward;
  }
  else
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    ptQTask[77].tQTaskChildren.ptMiddle = nullptr;
    ptState->pfState = HumanPlayer_RunStateCrouchWalkForward;
  }
}

// source: j/0/human/humanplayer.c:7671  [anchor-mhash]
void __cdecl HumanPlayer_RunStateCrouchWalkForward(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptHumanPlayer; };
    struct { char igi2_o1[36]; struct real32x3_t tReal32x3; };
    struct { char igi2_o2[48]; struct real64x3_t tReal64x3; };
    char igi2_extent[76];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v2; // ebx
  char v4; // cl
  void (__cdecl *v5)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v7)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v8)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v9)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v10)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v11)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v12)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v13)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v14)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v15)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v16)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v17)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v18)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v19)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v20)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v21)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v22)(struct State_s *, struct QTask_s *); // eax
  bool v23; // zf
  void (__cdecl *v24)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v25)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v26)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v27)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v28)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v29)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v30)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v31)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v32)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v33)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v34)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v35)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v36)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v37)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v38)(struct State_s *, struct QTask_s *); // eax
  unsigned int ptStatea = *(unsigned int *)&ptState; // [esp+50h] [ebp+4h] ARGSLOT

  v2 = ptQTask;
  igi2_frame.ptHumanPlayer = *(float *)&ptQTask[81].ptNext * 221.86666870117188;
  HumanPlayer_MoveOnGround((struct HumanPlayer_t *)ptQTask, igi2_frame.ptHumanPlayer, 44.37333297729492, 0.0, 44.37333297729492);
  ptStatea = ptState->bSignal;
  v4 = ptStatea;
  if ( (ptStatea & 0x800000) != 0 )
  {
    v5 = ptState->apfExitState[ptState->nState];
    if ( v5 )
      v5(ptState, v2);
    apfState = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 21;
    v7 = apfState[21];
    ptState->pfState = v7;
    v7(ptState, v2);
    return;
  }
  if ( (ptStatea & 2) == 0 )
  {
    v8 = ptState->apfExitState[ptState->nState];
    if ( v8 )
      v8(ptState, v2);
    v9 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 37;
    v10 = v9[37];
    ptState->pfState = v10;
    v10(ptState, v2);
    return;
  }
  if ( (ptStatea & 0x20000) != 0 )
  {
    v11 = ptState->apfExitState[ptState->nState];
    if ( v11 )
      v11(ptState, v2);
    v12 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 55;
    v13 = v12[55];
    ptState->pfState = v13;
    v13(ptState, v2);
    return;
  }
  if ( (ptStatea & 0x10000) != 0 )
  {
    v14 = ptState->apfExitState[ptState->nState];
    if ( v14 )
      v14(ptState, v2);
    v15 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 54;
    v16 = v15[54];
    ptState->pfState = v16;
    v16(ptState, v2);
    return;
  }
  if ( v2[83].tQTaskRefList.ptHead && (ptStatea & 0x2000) == 0 && ((int)v2[50].ptPrev & 1) != 0 )
  {
    v17 = ptState->apfExitState[ptState->nState];
    if ( v17 )
      v17(ptState, v2);
    v18 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 0;
    v19 = *v18;
    ptState->pfState = *v18;
    v19(ptState, v2);
    return;
  }
  if ( (ptStatea & 0x12000000) != 0 && ((int)v2[50].ptPrev & 1) != 0 )
  {
    v20 = ptState->apfExitState[ptState->nState];
    if ( v20 )
      v20(ptState, v2);
    v21 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 0;
    v22 = *v21;
    ptState->pfState = *v21;
    v22(ptState, v2);
    return;
  }
  if ( (ptStatea & 0x21000000) != 0 && ((int)v2[50].ptPrev & 4) != 0 )
  {
    ptQTask = nullptr;
    qmemcpy(&igi2_frame.tReal64x3, &v2[1], sizeof(igi2_frame.tReal64x3));
    *(_DWORD *)&v2[32].eQTaskType = 2;
    Human_ObjectCollision(v2, &igi2_frame.tReal64x3, &igi2_frame.tReal64x3, &igi2_frame.tReal32x3, (unsigned int *)&ptQTask);
    v23 = ((unsigned __int8)ptQTask & 4) == 0;
    *(_DWORD *)&v2[32].eQTaskType = 1;
    if ( v23 )
    {
      v24 = ptState->apfExitState[ptState->nState];
      if ( v24 )
        v24(ptState, v2);
      v25 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 75;
      v26 = v25[75];
      ptState->pfState = v26;
      v26(ptState, v2);
      return;
    }
    v4 = ptStatea;
  }
  if ( *(float *)&v2[20].tQTaskChildren.ptHead != 0.0
    && *(float *)&v2[13].eQTaskType == 0.0
    && ((int)v2[50].ptPrev & 8) != 0 )
  {
    v27 = ptState->apfExitState[ptState->nState];
    if ( v27 )
      v27(ptState, v2);
    v28 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 36;
    v29 = v28[36];
    ptState->pfState = v29;
    v29(ptState, v2);
  }
  else if ( (v4 & 0x40) != 0 )
  {
    v30 = ptState->apfExitState[ptState->nState];
    if ( v30 )
      v30(ptState, v2);
    v31 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 27;
    v32 = v31[27];
    ptState->pfState = v32;
    v32(ptState, v2);
  }
  else if ( (v4 & 0x20) != 0 )
  {
    v33 = ptState->apfExitState[ptState->nState];
    if ( v33 )
      v33(ptState, v2);
    v34 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 28;
    v35 = v34[28];
    ptState->pfState = v35;
    v35(ptState, v2);
  }
  else if ( v4 < 0 )
  {
    HumanPlayer_CrouchStateCheckWaterDepth(ptState, v2);
  }
  else
  {
    v36 = ptState->apfExitState[ptState->nState];
    if ( v36 )
      v36(ptState, v2);
    v37 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 23;
    v38 = v37[23];
    ptState->pfState = v38;
    v38(ptState, v2);
  }
}

// source: j/0/human/humanplayer.c:7751  [size]
void __cdecl HumanPlayer_InitStateCrouchWalkForwardRight(struct State_s *ptState, struct QTask_s *ptQTask)
{
  int nPreviousState; // eax
  struct QTask_s *ptTail; // eax
  struct QTask_s *ptParent; // ecx
  double v5; // st7
  struct QTask_s *v6; // eax
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *v9; // ecx
  double v10; // st7
  double v11; // st6
  int v12; // [esp+10h] [ebp-8h]

  *(_DWORD *)&ptQTask[32].eQTaskType = 1;
  nPreviousState = ptState->nPreviousState;
  if ( nPreviousState == 4 || nPreviousState == 26 || nPreviousState == 32 )
  {
    ptTail = ptQTask[34].tQTaskChildren.ptTail;
    ptParent = ptTail[1].ptParent;
    if ( ptParent )
      v5 = (double)(int)ptTail[1].tQTaskRefList.ptMiddle / (double)(int)ptParent->tQTaskChildren.ptTail;
    else
      v5 = 0.0;
    v6 = ptTail[1].ptParent;
    if ( v6 )
      v12 = (int)v6->tQTaskChildren.ptTail;
    else
      v12 = 0;
    HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, (__int64)((double)v12 * v5), 0.20000000298023224);
  }
  else
  {
    HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, 0, 0.20000000298023224);
  }
  ptNext = ptQTask[33].ptNext;
  ptQTask[77].ptParent = (struct QTask_s *)5;
  ptPrev = ptNext[1].ptPrev;
  if ( ptPrev && (v9 = ptPrev->tQTaskChildren.ptTail) != nullptr )
  {
    ptQTask[77].tQTaskChildren.ptHead = (struct QTask_s *)4;
    v10 = *(float *)&v9[21].tQTaskChildren.ptTail;
    ptQTask[77].tQTaskChildren.ptMiddle = v9[21].tQTaskChildren.ptTail;
    v11 = *(float *)&ptQTask[43].ptParent;
    if ( v11 < 0.0 )
      v11 = -v11;
    *(float *)&ptQTask[77].tQTaskChildren.ptMiddle = v11 * *(float *)&v9[21].ptParent * 3.0 + v10;
    ptState->pfState = HumanPlayer_RunStateCrouchWalkForwardRight;
  }
  else
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    ptQTask[77].tQTaskChildren.ptMiddle = nullptr;
    ptState->pfState = HumanPlayer_RunStateCrouchWalkForwardRight;
  }
}

// source: j/0/human/humanplayer.c:7791  [anchor-mhash]
void __cdecl HumanPlayer_RunStateCrouchWalkForwardRight(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real32x3_t tReal32x3; };
    struct { char igi2_o1[12]; struct real64x3_t tReal64x3; };
    char igi2_extent[40];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v2; // ebx
  char v4; // cl
  void (__cdecl *v5)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v7)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v8)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v9)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v10)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v11)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v12)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v13)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v14)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v15)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v16)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v17)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v18)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v19)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v20)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v21)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v22)(struct State_s *, struct QTask_s *); // eax
  bool v23; // zf
  void (__cdecl *v24)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v25)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v26)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v27)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v28)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v29)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v30)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v31)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v32)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v33)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v34)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v35)(struct State_s *, struct QTask_s *); // eax
  unsigned int ptStatea = *(unsigned int *)&ptState; // [esp+40h] [ebp+4h] ARGSLOT

  v2 = ptQTask;
  *(float *)&ptQTask = *(float *)&ptQTask[81].ptNext * 221.86666870117188;
  HumanPlayer_MoveOnGround((struct HumanPlayer_t *)v2, *(float *)&ptQTask, 44.37333297729492, *(float *)&ptQTask, 44.37333297729492);
  ptStatea = ptState->bSignal;
  v4 = ptStatea;
  if ( (ptStatea & 0x800000) != 0 )
  {
    v5 = ptState->apfExitState[ptState->nState];
    if ( v5 )
      v5(ptState, v2);
    apfState = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 21;
    v7 = apfState[21];
    ptState->pfState = v7;
    v7(ptState, v2);
    return;
  }
  if ( (ptStatea & 2) == 0 )
  {
    v8 = ptState->apfExitState[ptState->nState];
    if ( v8 )
      v8(ptState, v2);
    v9 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 37;
    v10 = v9[37];
    ptState->pfState = v10;
    v10(ptState, v2);
    return;
  }
  if ( (ptStatea & 0x20000) != 0 )
  {
    v11 = ptState->apfExitState[ptState->nState];
    if ( v11 )
      v11(ptState, v2);
    v12 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 55;
    v13 = v12[55];
    ptState->pfState = v13;
    v13(ptState, v2);
    return;
  }
  if ( (ptStatea & 0x10000) != 0 )
  {
    v14 = ptState->apfExitState[ptState->nState];
    if ( v14 )
      v14(ptState, v2);
    v15 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 54;
    v16 = v15[54];
    ptState->pfState = v16;
    v16(ptState, v2);
    return;
  }
  if ( v2[83].tQTaskRefList.ptHead && (ptStatea & 0x2000) == 0 && ((int)v2[50].ptPrev & 1) != 0 )
  {
    v17 = ptState->apfExitState[ptState->nState];
    if ( v17 )
      v17(ptState, v2);
    v18 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 0;
    v19 = *v18;
    ptState->pfState = *v18;
    v19(ptState, v2);
    return;
  }
  if ( (ptStatea & 0x12000000) != 0 && ((int)v2[50].ptPrev & 1) != 0 )
  {
    v20 = ptState->apfExitState[ptState->nState];
    if ( v20 )
      v20(ptState, v2);
    v21 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 0;
    v22 = *v21;
    ptState->pfState = *v21;
    v22(ptState, v2);
    return;
  }
  if ( (ptStatea & 0x21000000) != 0 && ((int)v2[50].ptPrev & 4) != 0 )
  {
    *(float *)&ptQTask = 0.0;
    qmemcpy(&igi2_frame.tReal64x3, &v2[1], sizeof(igi2_frame.tReal64x3));
    *(_DWORD *)&v2[32].eQTaskType = 2;
    Human_ObjectCollision(v2, &igi2_frame.tReal64x3, &igi2_frame.tReal64x3, &igi2_frame.tReal32x3, (unsigned int *)&ptQTask);
    v23 = ((unsigned __int8)ptQTask & 4) == 0;
    *(_DWORD *)&v2[32].eQTaskType = 1;
    if ( v23 )
    {
      v24 = ptState->apfExitState[ptState->nState];
      if ( v24 )
        v24(ptState, v2);
      v25 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 75;
      v26 = v25[75];
      ptState->pfState = v26;
      v26(ptState, v2);
      return;
    }
    v4 = ptStatea;
  }
  if ( *(float *)&v2[20].tQTaskChildren.ptHead != 0.0
    && *(float *)&v2[13].eQTaskType == 0.0
    && ((int)v2[50].ptPrev & 8) != 0 )
  {
    v27 = ptState->apfExitState[ptState->nState];
    if ( v27 )
      v27(ptState, v2);
    v28 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 36;
    v29 = v28[36];
    ptState->pfState = v29;
    v29(ptState, v2);
  }
  else if ( (v4 & 0x40) != 0 )
  {
    if ( v4 < 0 )
    {
      HumanPlayer_CrouchStateCheckWaterDepth(ptState, v2);
    }
    else
    {
      v33 = ptState->apfExitState[ptState->nState];
      if ( v33 )
        v33(ptState, v2);
      v34 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 32;
      v35 = v34[32];
      ptState->pfState = v35;
      v35(ptState, v2);
    }
  }
  else
  {
    v30 = ptState->apfExitState[ptState->nState];
    if ( v30 )
      v30(ptState, v2);
    v31 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 26;
    v32 = v31[26];
    ptState->pfState = v32;
    v32(ptState, v2);
  }
}

// source: j/0/human/humanplayer.c:7870  [size]
void __cdecl HumanPlayer_InitStateCrouchWalkForwardLeft(struct State_s *ptState, struct QTask_s *ptQTask)
{
  int nPreviousState; // eax
  struct QTask_s *ptTail; // eax
  struct QTask_s *ptParent; // ecx
  double v5; // st7
  struct QTask_s *v6; // eax
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *v9; // ecx
  double v10; // st7
  double v11; // st6
  int v12; // [esp+10h] [ebp-8h]

  *(_DWORD *)&ptQTask[32].eQTaskType = 1;
  nPreviousState = ptState->nPreviousState;
  if ( nPreviousState == 5 || nPreviousState == 26 || nPreviousState == 33 )
  {
    ptTail = ptQTask[34].tQTaskChildren.ptTail;
    ptParent = ptTail[1].ptParent;
    if ( ptParent )
      v5 = (double)(int)ptTail[1].tQTaskRefList.ptMiddle / (double)(int)ptParent->tQTaskChildren.ptTail;
    else
      v5 = 0.0;
    v6 = ptTail[1].ptParent;
    if ( v6 )
      v12 = (int)v6->tQTaskChildren.ptTail;
    else
      v12 = 0;
    HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, (__int64)((double)v12 * v5), 0.20000000298023224);
  }
  else
  {
    HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, 0, 0.20000000298023224);
  }
  ptNext = ptQTask[33].ptNext;
  ptQTask[77].ptParent = (struct QTask_s *)5;
  ptPrev = ptNext[1].ptPrev;
  if ( ptPrev && (v9 = ptPrev->tQTaskChildren.ptTail) != nullptr )
  {
    ptQTask[77].tQTaskChildren.ptHead = (struct QTask_s *)4;
    v10 = *(float *)&v9[21].tQTaskChildren.ptTail;
    ptQTask[77].tQTaskChildren.ptMiddle = v9[21].tQTaskChildren.ptTail;
    v11 = *(float *)&ptQTask[43].ptParent;
    if ( v11 < 0.0 )
      v11 = -v11;
    *(float *)&ptQTask[77].tQTaskChildren.ptMiddle = v11 * *(float *)&v9[21].ptParent * 3.0 + v10;
    ptState->pfState = HumanPlayer_RunStateCrouchWalkForwardLeft;
  }
  else
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    ptQTask[77].tQTaskChildren.ptMiddle = nullptr;
    ptState->pfState = HumanPlayer_RunStateCrouchWalkForwardLeft;
  }
}

// source: j/0/human/humanplayer.c:7910  [anchor-mhash]
void __cdecl HumanPlayer_RunStateCrouchWalkForwardLeft(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptHumanPlayer; };
    struct { char igi2_o1[8]; float vMaxYDelta; };
    struct { char igi2_o2[36]; struct real32x3_t tReal32x3; };
    struct { char igi2_o3[48]; struct real64x3_t tReal64x3; };
    char igi2_extent[76];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v2; // ebx
  char v4; // cl
  void (__cdecl *v5)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v7)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v8)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v9)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v10)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v11)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v12)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v13)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v14)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v15)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v16)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v17)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v18)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v19)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v20)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v21)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v22)(struct State_s *, struct QTask_s *); // eax
  bool v23; // zf
  void (__cdecl *v24)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v25)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v26)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v27)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v28)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v29)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v30)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v31)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v32)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v33)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v34)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v35)(struct State_s *, struct QTask_s *); // eax
  unsigned int ptStatea = *(unsigned int *)&ptState; // [esp+50h] [ebp+4h] ARGSLOT

  v2 = ptQTask;
  igi2_frame.vMaxYDelta = *(float *)&ptQTask[81].ptNext * -221.86666870117188;
  igi2_frame.ptHumanPlayer = *(float *)&ptQTask[81].ptNext * 221.86666870117188;
  HumanPlayer_MoveOnGround((struct HumanPlayer_t *)ptQTask, igi2_frame.ptHumanPlayer, 44.37333297729492, igi2_frame.vMaxYDelta, 44.37333297729492);
  ptStatea = ptState->bSignal;
  v4 = ptStatea;
  if ( (ptStatea & 0x800000) != 0 )
  {
    v5 = ptState->apfExitState[ptState->nState];
    if ( v5 )
      v5(ptState, v2);
    apfState = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 21;
    v7 = apfState[21];
    ptState->pfState = v7;
    v7(ptState, v2);
    return;
  }
  if ( (ptStatea & 2) == 0 )
  {
    v8 = ptState->apfExitState[ptState->nState];
    if ( v8 )
      v8(ptState, v2);
    v9 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 37;
    v10 = v9[37];
    ptState->pfState = v10;
    v10(ptState, v2);
    return;
  }
  if ( (ptStatea & 0x20000) != 0 )
  {
    v11 = ptState->apfExitState[ptState->nState];
    if ( v11 )
      v11(ptState, v2);
    v12 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 55;
    v13 = v12[55];
    ptState->pfState = v13;
    v13(ptState, v2);
    return;
  }
  if ( (ptStatea & 0x10000) != 0 )
  {
    v14 = ptState->apfExitState[ptState->nState];
    if ( v14 )
      v14(ptState, v2);
    v15 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 54;
    v16 = v15[54];
    ptState->pfState = v16;
    v16(ptState, v2);
    return;
  }
  if ( v2[83].tQTaskRefList.ptHead && (ptStatea & 0x2000) == 0 && ((int)v2[50].ptPrev & 1) != 0 )
  {
    v17 = ptState->apfExitState[ptState->nState];
    if ( v17 )
      v17(ptState, v2);
    v18 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 0;
    v19 = *v18;
    ptState->pfState = *v18;
    v19(ptState, v2);
    return;
  }
  if ( (ptStatea & 0x12000000) != 0 && ((int)v2[50].ptPrev & 1) != 0 )
  {
    v20 = ptState->apfExitState[ptState->nState];
    if ( v20 )
      v20(ptState, v2);
    v21 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 0;
    v22 = *v21;
    ptState->pfState = *v21;
    v22(ptState, v2);
    return;
  }
  if ( (ptStatea & 0x21000000) != 0 && ((int)v2[50].ptPrev & 4) != 0 )
  {
    ptQTask = nullptr;
    qmemcpy(&igi2_frame.tReal64x3, &v2[1], sizeof(igi2_frame.tReal64x3));
    *(_DWORD *)&v2[32].eQTaskType = 2;
    Human_ObjectCollision(v2, &igi2_frame.tReal64x3, &igi2_frame.tReal64x3, &igi2_frame.tReal32x3, (unsigned int *)&ptQTask);
    v23 = ((unsigned __int8)ptQTask & 4) == 0;
    *(_DWORD *)&v2[32].eQTaskType = 1;
    if ( v23 )
    {
      v24 = ptState->apfExitState[ptState->nState];
      if ( v24 )
        v24(ptState, v2);
      v25 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 75;
      v26 = v25[75];
      ptState->pfState = v26;
      v26(ptState, v2);
      return;
    }
    v4 = ptStatea;
  }
  if ( *(float *)&v2[20].tQTaskChildren.ptHead != 0.0
    && *(float *)&v2[13].eQTaskType == 0.0
    && ((int)v2[50].ptPrev & 8) != 0 )
  {
    v27 = ptState->apfExitState[ptState->nState];
    if ( v27 )
      v27(ptState, v2);
    v28 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 36;
    v29 = v28[36];
    ptState->pfState = v29;
    v29(ptState, v2);
  }
  else if ( (v4 & 0x20) != 0 )
  {
    if ( v4 < 0 )
    {
      HumanPlayer_CrouchStateCheckWaterDepth(ptState, v2);
    }
    else
    {
      v33 = ptState->apfExitState[ptState->nState];
      if ( v33 )
        v33(ptState, v2);
      v34 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 33;
      v35 = v34[33];
      ptState->pfState = v35;
      v35(ptState, v2);
    }
  }
  else
  {
    v30 = ptState->apfExitState[ptState->nState];
    if ( v30 )
      v30(ptState, v2);
    v31 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 26;
    v32 = v31[26];
    ptState->pfState = v32;
    v32(ptState, v2);
  }
}

// source: j/0/human/humanplayer.c:7989  [size]
void __cdecl HumanPlayer_InitStateCrouchWalkBackward(struct State_s *ptState, struct QTask_s *ptQTask)
{
  struct QTask_s *ptTail; // eax
  struct QTask_s *ptParent; // ecx
  double v4; // st7
  struct QTask_s *v5; // eax
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *v8; // ecx
  double v9; // st7
  double v10; // st6
  int v11; // [esp+10h] [ebp-8h]

  *(_DWORD *)&ptQTask[32].eQTaskType = 1;
  if ( ptState->nPreviousState == 14 )
  {
    ptTail = ptQTask[34].tQTaskChildren.ptTail;
    ptParent = ptTail[1].ptParent;
    if ( ptParent )
      v4 = (double)(int)ptTail[1].tQTaskRefList.ptMiddle / (double)(int)ptParent->tQTaskChildren.ptTail;
    else
      v4 = 0.0;
    v5 = ptTail[1].ptParent;
    if ( v5 )
      v11 = (int)v5->tQTaskChildren.ptTail;
    else
      v11 = 0;
    HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, (__int64)((double)v11 * v4), 0.20000000298023224);
  }
  else
  {
    HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, 0, 0.20000000298023224);
  }
  ptNext = ptQTask[33].ptNext;
  ptQTask[77].ptParent = (struct QTask_s *)5;
  ptPrev = ptNext[1].ptPrev;
  if ( ptPrev && (v8 = ptPrev->tQTaskChildren.ptTail) != nullptr )
  {
    ptQTask[77].tQTaskChildren.ptHead = (struct QTask_s *)4;
    v9 = *(float *)&v8[21].tQTaskChildren.ptTail;
    ptQTask[77].tQTaskChildren.ptMiddle = v8[21].tQTaskChildren.ptTail;
    v10 = *(float *)&ptQTask[43].ptParent;
    if ( v10 < 0.0 )
      v10 = -v10;
    *(float *)&ptQTask[77].tQTaskChildren.ptMiddle = v10 * *(float *)&v8[21].ptParent * 3.0 + v9;
    ptState->pfState = HumanPlayer_RunStateCrouchWalkBackward;
  }
  else
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    ptQTask[77].tQTaskChildren.ptMiddle = nullptr;
    ptState->pfState = HumanPlayer_RunStateCrouchWalkBackward;
  }
}

// source: j/0/human/humanplayer.c:8027  [anchor-mhash]
void __cdecl HumanPlayer_RunStateCrouchWalkBackward(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptHumanPlayer; };
    struct { char igi2_o1[36]; struct real32x3_t tReal32x3; };
    struct { char igi2_o2[48]; struct real64x3_t tReal64x3; };
    char igi2_extent[76];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v2; // ebx
  __int16 v4; // cx
  void (__cdecl *v5)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v7)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v8)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v9)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v10)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v11)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v12)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v13)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v14)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v15)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v16)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v17)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v18)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v19)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v20)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v21)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v22)(struct State_s *, struct QTask_s *); // eax
  bool v23; // zf
  void (__cdecl *v24)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v25)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v26)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v27)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v28)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v29)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v30)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v31)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v32)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v33)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v34)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v35)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v36)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v37)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v38)(struct State_s *, struct QTask_s *); // eax
  unsigned int ptStatea = *(unsigned int *)&ptState; // [esp+50h] [ebp+4h] ARGSLOT

  v2 = ptQTask;
  igi2_frame.ptHumanPlayer = *(float *)&ptQTask[81].ptNext * -221.86666870117188;
  HumanPlayer_MoveOnGround((struct HumanPlayer_t *)ptQTask, igi2_frame.ptHumanPlayer, 44.37333297729492, 0.0, 44.37333297729492);
  ptStatea = ptState->bSignal;
  v4 = ptStatea;
  if ( (ptStatea & 0x800000) != 0 )
  {
    v5 = ptState->apfExitState[ptState->nState];
    if ( v5 )
      v5(ptState, v2);
    apfState = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 21;
    v7 = apfState[21];
    ptState->pfState = v7;
    v7(ptState, v2);
    return;
  }
  if ( (ptStatea & 2) == 0 )
  {
    v8 = ptState->apfExitState[ptState->nState];
    if ( v8 )
      v8(ptState, v2);
    v9 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 37;
    v10 = v9[37];
    ptState->pfState = v10;
    v10(ptState, v2);
    return;
  }
  if ( (ptStatea & 0x20000) != 0 )
  {
    v11 = ptState->apfExitState[ptState->nState];
    if ( v11 )
      v11(ptState, v2);
    v12 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 55;
    v13 = v12[55];
    ptState->pfState = v13;
    v13(ptState, v2);
    return;
  }
  if ( (ptStatea & 0x10000) != 0 )
  {
    v14 = ptState->apfExitState[ptState->nState];
    if ( v14 )
      v14(ptState, v2);
    v15 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 54;
    v16 = v15[54];
    ptState->pfState = v16;
    v16(ptState, v2);
    return;
  }
  if ( v2[83].tQTaskRefList.ptHead && (ptStatea & 0x2000) == 0 && ((int)v2[50].ptPrev & 1) != 0 )
  {
    v17 = ptState->apfExitState[ptState->nState];
    if ( v17 )
      v17(ptState, v2);
    v18 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 0;
    v19 = *v18;
    ptState->pfState = *v18;
    v19(ptState, v2);
    return;
  }
  if ( (ptStatea & 0x12000000) != 0 && ((int)v2[50].ptPrev & 1) != 0 )
  {
    v20 = ptState->apfExitState[ptState->nState];
    if ( v20 )
      v20(ptState, v2);
    v21 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 0;
    v22 = *v21;
    ptState->pfState = *v21;
    v22(ptState, v2);
    return;
  }
  if ( (ptStatea & 0x21000000) != 0 && ((int)v2[50].ptPrev & 4) != 0 )
  {
    ptQTask = nullptr;
    qmemcpy(&igi2_frame.tReal64x3, &v2[1], sizeof(igi2_frame.tReal64x3));
    *(_DWORD *)&v2[32].eQTaskType = 2;
    Human_ObjectCollision(v2, &igi2_frame.tReal64x3, &igi2_frame.tReal64x3, &igi2_frame.tReal32x3, (unsigned int *)&ptQTask);
    v23 = ((unsigned __int8)ptQTask & 4) == 0;
    *(_DWORD *)&v2[32].eQTaskType = 1;
    if ( v23 )
    {
      v24 = ptState->apfExitState[ptState->nState];
      if ( v24 )
        v24(ptState, v2);
      v25 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 75;
      v26 = v25[75];
      ptState->pfState = v26;
      v26(ptState, v2);
      return;
    }
    v4 = ptStatea;
  }
  if ( *(float *)&v2[20].tQTaskChildren.ptHead != 0.0
    && *(float *)&v2[13].eQTaskType == 0.0
    && ((int)v2[50].ptPrev & 8) != 0 )
  {
    v27 = ptState->apfExitState[ptState->nState];
    if ( v27 )
      v27(ptState, v2);
    v28 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 36;
    v29 = v28[36];
    ptState->pfState = v29;
    v29(ptState, v2);
  }
  else if ( (v4 & 0x40) != 0 )
  {
    v30 = ptState->apfExitState[ptState->nState];
    if ( v30 )
      v30(ptState, v2);
    v31 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 30;
    v32 = v31[30];
    ptState->pfState = v32;
    v32(ptState, v2);
  }
  else if ( (v4 & 0x20) != 0 )
  {
    v33 = ptState->apfExitState[ptState->nState];
    if ( v33 )
      v33(ptState, v2);
    v34 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 31;
    v35 = v34[31];
    ptState->pfState = v35;
    v35(ptState, v2);
  }
  else if ( (v4 & 0x100) != 0 )
  {
    HumanPlayer_CrouchStateCheckWaterDepth(ptState, v2);
  }
  else
  {
    v36 = ptState->apfExitState[ptState->nState];
    if ( v36 )
      v36(ptState, v2);
    v37 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 23;
    v38 = v37[23];
    ptState->pfState = v38;
    v38(ptState, v2);
  }
}

// source: j/0/human/humanplayer.c:8106  [size]
void __cdecl HumanPlayer_InitStateCrouchWalkBackwardRight(struct State_s *ptState, struct QTask_s *ptQTask)
{
  int nPreviousState; // eax
  struct QTask_s *ptTail; // eax
  struct QTask_s *ptParent; // ecx
  double v5; // st7
  struct QTask_s *v6; // eax
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *v9; // ecx
  double v10; // st7
  double v11; // st6
  int v12; // [esp+10h] [ebp-8h]

  *(_DWORD *)&ptQTask[32].eQTaskType = 1;
  nPreviousState = ptState->nPreviousState;
  if ( nPreviousState == 7 || nPreviousState == 15 || nPreviousState == 29 )
  {
    ptTail = ptQTask[34].tQTaskChildren.ptTail;
    ptParent = ptTail[1].ptParent;
    if ( ptParent )
      v5 = (double)(int)ptTail[1].tQTaskRefList.ptMiddle / (double)(int)ptParent->tQTaskChildren.ptTail;
    else
      v5 = 0.0;
    v6 = ptTail[1].ptParent;
    if ( v6 )
      v12 = (int)v6->tQTaskChildren.ptTail;
    else
      v12 = 0;
    HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, (__int64)((double)v12 * v5), 0.20000000298023224);
  }
  else
  {
    HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, 0, 0.20000000298023224);
  }
  ptNext = ptQTask[33].ptNext;
  ptQTask[77].ptParent = (struct QTask_s *)5;
  ptPrev = ptNext[1].ptPrev;
  if ( ptPrev && (v9 = ptPrev->tQTaskChildren.ptTail) != nullptr )
  {
    ptQTask[77].tQTaskChildren.ptHead = (struct QTask_s *)4;
    v10 = *(float *)&v9[21].tQTaskChildren.ptTail;
    ptQTask[77].tQTaskChildren.ptMiddle = v9[21].tQTaskChildren.ptTail;
    v11 = *(float *)&ptQTask[43].ptParent;
    if ( v11 < 0.0 )
      v11 = -v11;
    *(float *)&ptQTask[77].tQTaskChildren.ptMiddle = v11 * *(float *)&v9[21].ptParent * 3.0 + v10;
    ptState->pfState = HumanPlayer_RunStateCrouchWalkBackwardRight;
  }
  else
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    ptQTask[77].tQTaskChildren.ptMiddle = nullptr;
    ptState->pfState = HumanPlayer_RunStateCrouchWalkBackwardRight;
  }
}

// source: j/0/human/humanplayer.c:8146  [anchor-mhash]
void __cdecl HumanPlayer_RunStateCrouchWalkBackwardRight(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptHumanPlayer; };
    struct { char igi2_o1[8]; float vMaxYDelta; };
    struct { char igi2_o2[36]; struct real32x3_t tReal32x3; };
    struct { char igi2_o3[48]; struct real64x3_t tReal64x3; };
    char igi2_extent[76];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v2; // ebx
  __int16 v4; // cx
  void (__cdecl *v5)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v7)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v8)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v9)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v10)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v11)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v12)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v13)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v14)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v15)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v16)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v17)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v18)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v19)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v20)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v21)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v22)(struct State_s *, struct QTask_s *); // eax
  bool v23; // zf
  void (__cdecl *v24)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v25)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v26)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v27)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v28)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v29)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v30)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v31)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v32)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v33)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v34)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v35)(struct State_s *, struct QTask_s *); // eax
  unsigned int ptStatea = *(unsigned int *)&ptState; // [esp+50h] [ebp+4h] ARGSLOT

  v2 = ptQTask;
  igi2_frame.vMaxYDelta = *(float *)&ptQTask[81].ptNext * 221.86666870117188;
  igi2_frame.ptHumanPlayer = *(float *)&ptQTask[81].ptNext * -221.86666870117188;
  HumanPlayer_MoveOnGround((struct HumanPlayer_t *)ptQTask, igi2_frame.ptHumanPlayer, 44.37333297729492, igi2_frame.vMaxYDelta, 44.37333297729492);
  ptStatea = ptState->bSignal;
  v4 = ptStatea;
  if ( (ptStatea & 0x800000) != 0 )
  {
    v5 = ptState->apfExitState[ptState->nState];
    if ( v5 )
      v5(ptState, v2);
    apfState = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 21;
    v7 = apfState[21];
    ptState->pfState = v7;
    v7(ptState, v2);
    return;
  }
  if ( (ptStatea & 2) == 0 )
  {
    v8 = ptState->apfExitState[ptState->nState];
    if ( v8 )
      v8(ptState, v2);
    v9 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 37;
    v10 = v9[37];
    ptState->pfState = v10;
    v10(ptState, v2);
    return;
  }
  if ( (ptStatea & 0x20000) != 0 )
  {
    v11 = ptState->apfExitState[ptState->nState];
    if ( v11 )
      v11(ptState, v2);
    v12 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 55;
    v13 = v12[55];
    ptState->pfState = v13;
    v13(ptState, v2);
    return;
  }
  if ( (ptStatea & 0x10000) != 0 )
  {
    v14 = ptState->apfExitState[ptState->nState];
    if ( v14 )
      v14(ptState, v2);
    v15 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 54;
    v16 = v15[54];
    ptState->pfState = v16;
    v16(ptState, v2);
    return;
  }
  if ( v2[83].tQTaskRefList.ptHead && (ptStatea & 0x2000) == 0 && ((int)v2[50].ptPrev & 1) != 0 )
  {
    v17 = ptState->apfExitState[ptState->nState];
    if ( v17 )
      v17(ptState, v2);
    v18 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 0;
    v19 = *v18;
    ptState->pfState = *v18;
    v19(ptState, v2);
    return;
  }
  if ( (ptStatea & 0x12000000) != 0 && ((int)v2[50].ptPrev & 1) != 0 )
  {
    v20 = ptState->apfExitState[ptState->nState];
    if ( v20 )
      v20(ptState, v2);
    v21 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 0;
    v22 = *v21;
    ptState->pfState = *v21;
    v22(ptState, v2);
    return;
  }
  if ( (ptStatea & 0x21000000) != 0 && ((int)v2[50].ptPrev & 4) != 0 )
  {
    ptQTask = nullptr;
    qmemcpy(&igi2_frame.tReal64x3, &v2[1], sizeof(igi2_frame.tReal64x3));
    *(_DWORD *)&v2[32].eQTaskType = 2;
    Human_ObjectCollision(v2, &igi2_frame.tReal64x3, &igi2_frame.tReal64x3, &igi2_frame.tReal32x3, (unsigned int *)&ptQTask);
    v23 = ((unsigned __int8)ptQTask & 4) == 0;
    *(_DWORD *)&v2[32].eQTaskType = 1;
    if ( v23 )
    {
      v24 = ptState->apfExitState[ptState->nState];
      if ( v24 )
        v24(ptState, v2);
      v25 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 75;
      v26 = v25[75];
      ptState->pfState = v26;
      v26(ptState, v2);
      return;
    }
    v4 = ptStatea;
  }
  if ( *(float *)&v2[20].tQTaskChildren.ptHead != 0.0
    && *(float *)&v2[13].eQTaskType == 0.0
    && ((int)v2[50].ptPrev & 8) != 0 )
  {
    v27 = ptState->apfExitState[ptState->nState];
    if ( v27 )
      v27(ptState, v2);
    v28 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 36;
    v29 = v28[36];
    ptState->pfState = v29;
    v29(ptState, v2);
  }
  else if ( (v4 & 0x100) != 0 )
  {
    if ( (v4 & 0x40) != 0 )
    {
      HumanPlayer_CrouchStateCheckWaterDepth(ptState, v2);
    }
    else
    {
      v33 = ptState->apfExitState[ptState->nState];
      if ( v33 )
        v33(ptState, v2);
      v34 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 29;
      v35 = v34[29];
      ptState->pfState = v35;
      v35(ptState, v2);
    }
  }
  else
  {
    v30 = ptState->apfExitState[ptState->nState];
    if ( v30 )
      v30(ptState, v2);
    v31 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 32;
    v32 = v31[32];
    ptState->pfState = v32;
    v32(ptState, v2);
  }
}

// source: j/0/human/humanplayer.c:8225  [size]
void __cdecl HumanPlayer_InitStateCrouchWalkBackwardLeft(struct State_s *ptState, struct QTask_s *ptQTask)
{
  int nPreviousState; // eax
  struct QTask_s *ptTail; // eax
  struct QTask_s *ptParent; // ecx
  double v5; // st7
  struct QTask_s *v6; // eax
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *v9; // ecx
  double v10; // st7
  double v11; // st6
  int v12; // [esp+10h] [ebp-8h]

  *(_DWORD *)&ptQTask[32].eQTaskType = 1;
  nPreviousState = ptState->nPreviousState;
  if ( nPreviousState == 8 || nPreviousState == 16 || nPreviousState == 29 )
  {
    ptTail = ptQTask[34].tQTaskChildren.ptTail;
    ptParent = ptTail[1].ptParent;
    if ( ptParent )
      v5 = (double)(int)ptTail[1].tQTaskRefList.ptMiddle / (double)(int)ptParent->tQTaskChildren.ptTail;
    else
      v5 = 0.0;
    v6 = ptTail[1].ptParent;
    if ( v6 )
      v12 = (int)v6->tQTaskChildren.ptTail;
    else
      v12 = 0;
    HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, (__int64)((double)v12 * v5), 0.20000000298023224);
  }
  else
  {
    HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, 0, 0.20000000298023224);
  }
  ptNext = ptQTask[33].ptNext;
  ptQTask[77].ptParent = (struct QTask_s *)5;
  ptPrev = ptNext[1].ptPrev;
  if ( ptPrev && (v9 = ptPrev->tQTaskChildren.ptTail) != nullptr )
  {
    ptQTask[77].tQTaskChildren.ptHead = (struct QTask_s *)4;
    v10 = *(float *)&v9[21].tQTaskChildren.ptTail;
    ptQTask[77].tQTaskChildren.ptMiddle = v9[21].tQTaskChildren.ptTail;
    v11 = *(float *)&ptQTask[43].ptParent;
    if ( v11 < 0.0 )
      v11 = -v11;
    *(float *)&ptQTask[77].tQTaskChildren.ptMiddle = v11 * *(float *)&v9[21].ptParent * 3.0 + v10;
    ptState->pfState = HumanPlayer_RunStateCrouchWalkBackwardLeft;
  }
  else
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    ptQTask[77].tQTaskChildren.ptMiddle = nullptr;
    ptState->pfState = HumanPlayer_RunStateCrouchWalkBackwardLeft;
  }
}

// source: j/0/human/humanplayer.c:8265  [anchor-mhash]
void __cdecl HumanPlayer_RunStateCrouchWalkBackwardLeft(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real32x3_t tReal32x3; };
    struct { char igi2_o1[12]; struct real64x3_t tReal64x3; };
    char igi2_extent[40];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v2; // ebx
  __int16 v4; // cx
  void (__cdecl *v5)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v7)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v8)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v9)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v10)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v11)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v12)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v13)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v14)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v15)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v16)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v17)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v18)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v19)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v20)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v21)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v22)(struct State_s *, struct QTask_s *); // eax
  bool v23; // zf
  void (__cdecl *v24)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v25)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v26)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v27)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v28)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v29)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v30)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v31)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v32)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v33)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v34)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v35)(struct State_s *, struct QTask_s *); // eax
  unsigned int ptStatea = *(unsigned int *)&ptState; // [esp+40h] [ebp+4h] ARGSLOT

  v2 = ptQTask;
  *(float *)&ptQTask = *(float *)&ptQTask[81].ptNext * -221.86666870117188;
  HumanPlayer_MoveOnGround((struct HumanPlayer_t *)v2, *(float *)&ptQTask, 44.37333297729492, *(float *)&ptQTask, 44.37333297729492);
  ptStatea = ptState->bSignal;
  v4 = ptStatea;
  if ( (ptStatea & 0x800000) != 0 )
  {
    v5 = ptState->apfExitState[ptState->nState];
    if ( v5 )
      v5(ptState, v2);
    apfState = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 21;
    v7 = apfState[21];
    ptState->pfState = v7;
    v7(ptState, v2);
    return;
  }
  if ( (ptStatea & 2) == 0 )
  {
    v8 = ptState->apfExitState[ptState->nState];
    if ( v8 )
      v8(ptState, v2);
    v9 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 37;
    v10 = v9[37];
    ptState->pfState = v10;
    v10(ptState, v2);
    return;
  }
  if ( (ptStatea & 0x20000) != 0 )
  {
    v11 = ptState->apfExitState[ptState->nState];
    if ( v11 )
      v11(ptState, v2);
    v12 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 55;
    v13 = v12[55];
    ptState->pfState = v13;
    v13(ptState, v2);
    return;
  }
  if ( (ptStatea & 0x10000) != 0 )
  {
    v14 = ptState->apfExitState[ptState->nState];
    if ( v14 )
      v14(ptState, v2);
    v15 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 54;
    v16 = v15[54];
    ptState->pfState = v16;
    v16(ptState, v2);
    return;
  }
  if ( v2[83].tQTaskRefList.ptHead && (ptStatea & 0x2000) == 0 && ((int)v2[50].ptPrev & 1) != 0 )
  {
    v17 = ptState->apfExitState[ptState->nState];
    if ( v17 )
      v17(ptState, v2);
    v18 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 0;
    v19 = *v18;
    ptState->pfState = *v18;
    v19(ptState, v2);
    return;
  }
  if ( (ptStatea & 0x12000000) != 0 && ((int)v2[50].ptPrev & 1) != 0 )
  {
    v20 = ptState->apfExitState[ptState->nState];
    if ( v20 )
      v20(ptState, v2);
    v21 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 0;
    v22 = *v21;
    ptState->pfState = *v21;
    v22(ptState, v2);
    return;
  }
  if ( (ptStatea & 0x21000000) != 0 && ((int)v2[50].ptPrev & 4) != 0 )
  {
    *(float *)&ptQTask = 0.0;
    qmemcpy(&igi2_frame.tReal64x3, &v2[1], sizeof(igi2_frame.tReal64x3));
    *(_DWORD *)&v2[32].eQTaskType = 2;
    Human_ObjectCollision(v2, &igi2_frame.tReal64x3, &igi2_frame.tReal64x3, &igi2_frame.tReal32x3, (unsigned int *)&ptQTask);
    v23 = ((unsigned __int8)ptQTask & 4) == 0;
    *(_DWORD *)&v2[32].eQTaskType = 1;
    if ( v23 )
    {
      v24 = ptState->apfExitState[ptState->nState];
      if ( v24 )
        v24(ptState, v2);
      v25 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 75;
      v26 = v25[75];
      ptState->pfState = v26;
      v26(ptState, v2);
      return;
    }
    v4 = ptStatea;
  }
  if ( *(float *)&v2[20].tQTaskChildren.ptHead != 0.0
    && *(float *)&v2[13].eQTaskType == 0.0
    && ((int)v2[50].ptPrev & 8) != 0 )
  {
    v27 = ptState->apfExitState[ptState->nState];
    if ( v27 )
      v27(ptState, v2);
    v28 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 36;
    v29 = v28[36];
    ptState->pfState = v29;
    v29(ptState, v2);
  }
  else if ( (v4 & 0x100) != 0 )
  {
    if ( (v4 & 0x20) != 0 )
    {
      HumanPlayer_CrouchStateCheckWaterDepth(ptState, v2);
    }
    else
    {
      v33 = ptState->apfExitState[ptState->nState];
      if ( v33 )
        v33(ptState, v2);
      v34 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 29;
      v35 = v34[29];
      ptState->pfState = v35;
      v35(ptState, v2);
    }
  }
  else
  {
    v30 = ptState->apfExitState[ptState->nState];
    if ( v30 )
      v30(ptState, v2);
    v31 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 33;
    v32 = v31[33];
    ptState->pfState = v32;
    v32(ptState, v2);
  }
}

// source: j/0/human/humanplayer.c:8344  [size]
void __cdecl HumanPlayer_InitStateCrouchWalkRight(struct State_s *ptState, struct QTask_s *ptQTask)
{
  struct QTask_s *ptTail; // eax
  struct QTask_s *ptParent; // ecx
  double v4; // st7
  struct QTask_s *v5; // eax
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *v8; // ecx
  double v9; // st7
  double v10; // st6
  int v11; // [esp+10h] [ebp-8h]

  *(_DWORD *)&ptQTask[32].eQTaskType = 1;
  if ( ptState->nPreviousState == 9 )
  {
    ptTail = ptQTask[34].tQTaskChildren.ptTail;
    ptParent = ptTail[1].ptParent;
    if ( ptParent )
      v4 = (double)(int)ptTail[1].tQTaskRefList.ptMiddle / (double)(int)ptParent->tQTaskChildren.ptTail;
    else
      v4 = 0.0;
    v5 = ptTail[1].ptParent;
    if ( v5 )
      v11 = (int)v5->tQTaskChildren.ptTail;
    else
      v11 = 0;
    HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, (__int64)((double)v11 * v4), 0.20000000298023224);
  }
  else
  {
    HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, 0, 0.20000000298023224);
  }
  ptNext = ptQTask[33].ptNext;
  ptQTask[77].ptParent = (struct QTask_s *)5;
  ptPrev = ptNext[1].ptPrev;
  if ( ptPrev && (v8 = ptPrev->tQTaskChildren.ptTail) != nullptr )
  {
    ptQTask[77].tQTaskChildren.ptHead = (struct QTask_s *)4;
    v9 = *(float *)&v8[21].tQTaskChildren.ptTail;
    ptQTask[77].tQTaskChildren.ptMiddle = v8[21].tQTaskChildren.ptTail;
    v10 = *(float *)&ptQTask[43].ptParent;
    if ( v10 < 0.0 )
      v10 = -v10;
    *(float *)&ptQTask[77].tQTaskChildren.ptMiddle = v10 * *(float *)&v8[21].ptParent * 3.0 + v9;
    ptState->pfState = HumanPlayer_RunStateCrouchWalkRight;
  }
  else
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    ptQTask[77].tQTaskChildren.ptMiddle = nullptr;
    ptState->pfState = HumanPlayer_RunStateCrouchWalkRight;
  }
}

// source: j/0/human/humanplayer.c:8382  [size]
void __cdecl HumanPlayer_RunStateCrouchWalkRight(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vMaxYDelta; };
    struct { char igi2_o1[28]; struct real32x3_t tReal32x3; };
    struct { char igi2_o2[40]; struct real64x3_t tReal64x3; };
    char igi2_extent[68];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v2; // ebx
  __int16 v4; // cx
  void (__cdecl *v5)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v7)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v8)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v9)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v10)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v11)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v12)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v13)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v14)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v15)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v16)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v17)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v18)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v19)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v20)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v21)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v22)(struct State_s *, struct QTask_s *); // eax
  bool v23; // zf
  void (__cdecl *v24)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v25)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v26)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v27)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v28)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v29)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v30)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v31)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v32)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v33)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v34)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v35)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v36)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v37)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v38)(struct State_s *, struct QTask_s *); // eax
  unsigned int ptStatea = *(unsigned int *)&ptState; // [esp+48h] [ebp+4h] ARGSLOT

  v2 = ptQTask;
  igi2_frame.vMaxYDelta = *(float *)&ptQTask[81].ptNext * 221.86666870117188;
  HumanPlayer_MoveOnGround((struct HumanPlayer_t *)ptQTask, 0.0, 44.37333297729492, igi2_frame.vMaxYDelta, 44.37333297729492);
  ptStatea = ptState->bSignal;
  v4 = ptStatea;
  if ( (ptStatea & 0x800000) != 0 )
  {
    v5 = ptState->apfExitState[ptState->nState];
    if ( v5 )
      v5(ptState, v2);
    apfState = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 21;
    v7 = apfState[21];
    ptState->pfState = v7;
    v7(ptState, v2);
    return;
  }
  if ( (ptStatea & 2) == 0 )
  {
    v8 = ptState->apfExitState[ptState->nState];
    if ( v8 )
      v8(ptState, v2);
    v9 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 37;
    v10 = v9[37];
    ptState->pfState = v10;
    v10(ptState, v2);
    return;
  }
  if ( (ptStatea & 0x20000) != 0 )
  {
    v11 = ptState->apfExitState[ptState->nState];
    if ( v11 )
      v11(ptState, v2);
    v12 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 55;
    v13 = v12[55];
    ptState->pfState = v13;
    v13(ptState, v2);
    return;
  }
  if ( (ptStatea & 0x10000) != 0 )
  {
    v14 = ptState->apfExitState[ptState->nState];
    if ( v14 )
      v14(ptState, v2);
    v15 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 54;
    v16 = v15[54];
    ptState->pfState = v16;
    v16(ptState, v2);
    return;
  }
  if ( v2[83].tQTaskRefList.ptHead && (ptStatea & 0x2000) == 0 && ((int)v2[50].ptPrev & 1) != 0 )
  {
    v17 = ptState->apfExitState[ptState->nState];
    if ( v17 )
      v17(ptState, v2);
    v18 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 0;
    v19 = *v18;
    ptState->pfState = *v18;
    v19(ptState, v2);
    return;
  }
  if ( (ptStatea & 0x12000000) != 0 && ((int)v2[50].ptPrev & 1) != 0 )
  {
    v20 = ptState->apfExitState[ptState->nState];
    if ( v20 )
      v20(ptState, v2);
    v21 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 0;
    v22 = *v21;
    ptState->pfState = *v21;
    v22(ptState, v2);
    return;
  }
  if ( (ptStatea & 0x21000000) != 0 && ((int)v2[50].ptPrev & 4) != 0 )
  {
    ptQTask = nullptr;
    qmemcpy(&igi2_frame.tReal64x3, &v2[1], sizeof(igi2_frame.tReal64x3));
    *(_DWORD *)&v2[32].eQTaskType = 2;
    Human_ObjectCollision(v2, &igi2_frame.tReal64x3, &igi2_frame.tReal64x3, &igi2_frame.tReal32x3, (unsigned int *)&ptQTask);
    v23 = ((unsigned __int8)ptQTask & 4) == 0;
    *(_DWORD *)&v2[32].eQTaskType = 1;
    if ( v23 )
    {
      v24 = ptState->apfExitState[ptState->nState];
      if ( v24 )
        v24(ptState, v2);
      v25 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 75;
      v26 = v25[75];
      ptState->pfState = v26;
      v26(ptState, v2);
      return;
    }
    v4 = ptStatea;
  }
  if ( *(float *)&v2[20].tQTaskChildren.ptHead != 0.0
    && *(float *)&v2[13].eQTaskType == 0.0
    && ((int)v2[50].ptPrev & 8) != 0 )
  {
    v27 = ptState->apfExitState[ptState->nState];
    if ( v27 )
      v27(ptState, v2);
    v28 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 36;
    v29 = v28[36];
    ptState->pfState = v29;
    v29(ptState, v2);
  }
  else if ( (v4 & 0x40) != 0 )
  {
    if ( (v4 & 0x80u) == 0 )
    {
      if ( (v4 & 0x100) != 0 )
      {
        v36 = ptState->apfExitState[ptState->nState];
        if ( v36 )
          v36(ptState, v2);
        v37 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 30;
        v38 = v37[30];
        ptState->pfState = v38;
        v38(ptState, v2);
      }
      else
      {
        HumanPlayer_CrouchStateCheckWaterDepth(ptState, v2);
      }
    }
    else
    {
      v33 = ptState->apfExitState[ptState->nState];
      if ( v33 )
        v33(ptState, v2);
      v34 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 27;
      v35 = v34[27];
      ptState->pfState = v35;
      v35(ptState, v2);
    }
  }
  else
  {
    v30 = ptState->apfExitState[ptState->nState];
    if ( v30 )
      v30(ptState, v2);
    v31 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 23;
    v32 = v31[23];
    ptState->pfState = v32;
    v32(ptState, v2);
  }
}

// source: j/0/human/humanplayer.c:8462  [size]
void __cdecl HumanPlayer_InitStateCrouchWalkLeft(struct State_s *ptState, struct QTask_s *ptQTask)
{
  struct QTask_s *ptTail; // eax
  struct QTask_s *ptParent; // ecx
  double v4; // st7
  struct QTask_s *v5; // eax
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *v8; // ecx
  double v9; // st7
  double v10; // st6
  int v11; // [esp+10h] [ebp-8h]

  *(_DWORD *)&ptQTask[32].eQTaskType = 1;
  if ( ptState->nPreviousState == 10 )
  {
    ptTail = ptQTask[34].tQTaskChildren.ptTail;
    ptParent = ptTail[1].ptParent;
    if ( ptParent )
      v4 = (double)(int)ptTail[1].tQTaskRefList.ptMiddle / (double)(int)ptParent->tQTaskChildren.ptTail;
    else
      v4 = 0.0;
    v5 = ptTail[1].ptParent;
    if ( v5 )
      v11 = (int)v5->tQTaskChildren.ptTail;
    else
      v11 = 0;
    HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, (__int64)((double)v11 * v4), 0.20000000298023224);
  }
  else
  {
    HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, 0, 0.20000000298023224);
  }
  ptNext = ptQTask[33].ptNext;
  ptQTask[77].ptParent = (struct QTask_s *)5;
  ptPrev = ptNext[1].ptPrev;
  if ( ptPrev && (v8 = ptPrev->tQTaskChildren.ptTail) != nullptr )
  {
    ptQTask[77].tQTaskChildren.ptHead = (struct QTask_s *)4;
    v9 = *(float *)&v8[21].tQTaskChildren.ptTail;
    ptQTask[77].tQTaskChildren.ptMiddle = v8[21].tQTaskChildren.ptTail;
    v10 = *(float *)&ptQTask[43].ptParent;
    if ( v10 < 0.0 )
      v10 = -v10;
    *(float *)&ptQTask[77].tQTaskChildren.ptMiddle = v10 * *(float *)&v8[21].ptParent * 3.0 + v9;
    ptState->pfState = HumanPlayer_RunStateCrouchWalkLeft;
  }
  else
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    ptQTask[77].tQTaskChildren.ptMiddle = nullptr;
    ptState->pfState = HumanPlayer_RunStateCrouchWalkLeft;
  }
}

// source: j/0/human/humanplayer.c:8500  [size]
void __cdecl HumanPlayer_RunStateCrouchWalkLeft(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vMaxYDelta; };
    struct { char igi2_o1[28]; struct real32x3_t tReal32x3; };
    struct { char igi2_o2[40]; struct real64x3_t tReal64x3; };
    char igi2_extent[68];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v2; // ebx
  __int16 v4; // cx
  void (__cdecl *v5)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v7)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v8)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v9)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v10)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v11)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v12)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v13)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v14)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v15)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v16)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v17)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v18)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v19)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v20)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v21)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v22)(struct State_s *, struct QTask_s *); // eax
  bool v23; // zf
  void (__cdecl *v24)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v25)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v26)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v27)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v28)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v29)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v30)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v31)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v32)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v33)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v34)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v35)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v36)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v37)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v38)(struct State_s *, struct QTask_s *); // eax
  unsigned int ptStatea = *(unsigned int *)&ptState; // [esp+48h] [ebp+4h] ARGSLOT

  v2 = ptQTask;
  igi2_frame.vMaxYDelta = *(float *)&ptQTask[81].ptNext * -221.86666870117188;
  HumanPlayer_MoveOnGround((struct HumanPlayer_t *)ptQTask, 0.0, 44.37333297729492, igi2_frame.vMaxYDelta, 44.37333297729492);
  ptStatea = ptState->bSignal;
  v4 = ptStatea;
  if ( (ptStatea & 0x800000) != 0 )
  {
    v5 = ptState->apfExitState[ptState->nState];
    if ( v5 )
      v5(ptState, v2);
    apfState = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 21;
    v7 = apfState[21];
    ptState->pfState = v7;
    v7(ptState, v2);
    return;
  }
  if ( (ptStatea & 2) == 0 )
  {
    v8 = ptState->apfExitState[ptState->nState];
    if ( v8 )
      v8(ptState, v2);
    v9 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 37;
    v10 = v9[37];
    ptState->pfState = v10;
    v10(ptState, v2);
    return;
  }
  if ( (ptStatea & 0x20000) != 0 )
  {
    v11 = ptState->apfExitState[ptState->nState];
    if ( v11 )
      v11(ptState, v2);
    v12 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 55;
    v13 = v12[55];
    ptState->pfState = v13;
    v13(ptState, v2);
    return;
  }
  if ( (ptStatea & 0x10000) != 0 )
  {
    v14 = ptState->apfExitState[ptState->nState];
    if ( v14 )
      v14(ptState, v2);
    v15 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 54;
    v16 = v15[54];
    ptState->pfState = v16;
    v16(ptState, v2);
    return;
  }
  if ( v2[83].tQTaskRefList.ptHead && (ptStatea & 0x2000) == 0 && ((int)v2[50].ptPrev & 1) != 0 )
  {
    v17 = ptState->apfExitState[ptState->nState];
    if ( v17 )
      v17(ptState, v2);
    v18 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 0;
    v19 = *v18;
    ptState->pfState = *v18;
    v19(ptState, v2);
    return;
  }
  if ( (ptStatea & 0x12000000) != 0 && ((int)v2[50].ptPrev & 1) != 0 )
  {
    v20 = ptState->apfExitState[ptState->nState];
    if ( v20 )
      v20(ptState, v2);
    v21 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 0;
    v22 = *v21;
    ptState->pfState = *v21;
    v22(ptState, v2);
    return;
  }
  if ( (ptStatea & 0x21000000) != 0 && ((int)v2[50].ptPrev & 4) != 0 )
  {
    ptQTask = nullptr;
    qmemcpy(&igi2_frame.tReal64x3, &v2[1], sizeof(igi2_frame.tReal64x3));
    *(_DWORD *)&v2[32].eQTaskType = 2;
    Human_ObjectCollision(v2, &igi2_frame.tReal64x3, &igi2_frame.tReal64x3, &igi2_frame.tReal32x3, (unsigned int *)&ptQTask);
    v23 = ((unsigned __int8)ptQTask & 4) == 0;
    *(_DWORD *)&v2[32].eQTaskType = 1;
    if ( v23 )
    {
      v24 = ptState->apfExitState[ptState->nState];
      if ( v24 )
        v24(ptState, v2);
      v25 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 75;
      v26 = v25[75];
      ptState->pfState = v26;
      v26(ptState, v2);
      return;
    }
    v4 = ptStatea;
  }
  if ( *(float *)&v2[20].tQTaskChildren.ptHead != 0.0
    && *(float *)&v2[13].eQTaskType == 0.0
    && ((int)v2[50].ptPrev & 8) != 0 )
  {
    v27 = ptState->apfExitState[ptState->nState];
    if ( v27 )
      v27(ptState, v2);
    v28 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 36;
    v29 = v28[36];
    ptState->pfState = v29;
    v29(ptState, v2);
  }
  else if ( (v4 & 0x20) != 0 )
  {
    if ( (v4 & 0x80u) == 0 )
    {
      if ( (v4 & 0x100) != 0 )
      {
        v36 = ptState->apfExitState[ptState->nState];
        if ( v36 )
          v36(ptState, v2);
        v37 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 31;
        v38 = v37[31];
        ptState->pfState = v38;
        v38(ptState, v2);
      }
      else
      {
        HumanPlayer_CrouchStateCheckWaterDepth(ptState, v2);
      }
    }
    else
    {
      v33 = ptState->apfExitState[ptState->nState];
      if ( v33 )
        v33(ptState, v2);
      v34 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 28;
      v35 = v34[28];
      ptState->pfState = v35;
      v35(ptState, v2);
    }
  }
  else
  {
    v30 = ptState->apfExitState[ptState->nState];
    if ( v30 )
      v30(ptState, v2);
    v31 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 23;
    v32 = v31[23];
    ptState->pfState = v32;
    v32(ptState, v2);
  }
}

// source: j/0/human/humanplayer.c:8581  [anchor-refs]
void __cdecl HumanPlayer_InitStateJump(struct State_s *ptState, struct QTask_s *ptQTask)
{
  struct QReference_s *ptMiddle; // eax
  _WORD *pxObject; // eax
  void (__cdecl *v4)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v6)(struct State_s *, struct QTask_s *); // eax
  struct QTask_s *ptPrev; // eax
  float *ptTail; // ecx
  double v9; // st7
  double v10; // st6
  struct QTask_s *v11; // eax
  struct QTask_s *v12; // ecx
  double v13; // st7
  struct QReference_s *v14; // eax
  float tSpeed_8; // [esp+14h] [ebp-4h]

  ptMiddle = ptQTask[44].tQTaskRefList.ptMiddle;
  ptQTask[83].tQTaskRefList.ptTail = nullptr;
  if ( ptMiddle )
  {
    pxObject = ptMiddle->pxObject;
    if ( pxObject )
    {
      if ( pxObject[18] == Elevator_eQTaskType )
      {
        v4 = ptState->apfExitState[ptState->nState];
        if ( v4 )
          v4(ptState, ptQTask);
        apfState = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 0;
        v6 = *apfState;
        ptState->pfState = *apfState;
        v6(ptState, ptQTask);
        return;
      }
    }
  }
  if ( *(_DWORD *)&ptQTask[32].eQTaskType == 1 )
  {
    HumanAnim_SetAnimationAndTimeFromState(ptQTask, 68, 0, 0.20000000298023224);
    ptPrev = ptQTask[33].ptNext[1].ptPrev;
    if ( !ptPrev || (ptTail = (float *)ptPrev->tQTaskChildren.ptTail) == nullptr )
    {
      ptQTask[77].tQTaskChildren.ptHead = nullptr;
      ptQTask[77].tQTaskChildren.ptMiddle = nullptr;
      goto LABEL_19;
    }
    ptQTask[77].tQTaskChildren.ptHead = (struct QTask_s *)8;
    v9 = ptTail[217] + ptTail[214] + ptTail[211];
    *(float *)&ptQTask[77].tQTaskChildren.ptMiddle = v9;
    v10 = *(float *)&ptQTask[43].ptParent;
    if ( v10 < 0.0 )
      v10 = -v10;
  }
  else
  {
    HumanAnim_SetAnimationAndTimeFromState(ptQTask, 36, 0, 0.20000000298023224);
    v11 = ptQTask[33].ptNext[1].ptPrev;
    if ( !v11 || (ptTail = (float *)v11->tQTaskChildren.ptTail) == nullptr )
    {
      ptQTask[77].tQTaskChildren.ptHead = nullptr;
      ptQTask[77].tQTaskChildren.ptMiddle = nullptr;
      goto LABEL_19;
    }
    ptQTask[77].tQTaskChildren.ptHead = (struct QTask_s *)7;
    v9 = ptTail[217] + ptTail[211];
    *(float *)&ptQTask[77].tQTaskChildren.ptMiddle = v9;
    v10 = *(float *)&ptQTask[43].ptParent;
    if ( v10 < 0.0 )
      v10 = -v10;
  }
  *(float *)&ptQTask[77].tQTaskChildren.ptMiddle = v10 * ptTail[218] * 3.0 + v9;
LABEL_19:
  SoundSys_NewSoundFn(ptQTask[33].tQTaskChildren.ptTail, "jump_1");
  v12 = *(struct QTask_s **)&ptQTask[37].eQTaskType;
  v13 = HumanPlayer_tGeneral.vUpwardJumpSpeed + *(float *)&ptQTask[38].ptNext;
  ptQTask[38].ptPrev = ptQTask[37].ptParent;
  ptQTask[38].tQTaskChildren.ptHead = v12;
  tSpeed_8 = v13;
  *(float *)&ptQTask[38].tQTaskChildren.ptMiddle = tSpeed_8;
  v14 = ptQTask[44].tQTaskRefList.ptMiddle;
  *(_DWORD *)&ptQTask[30].eQTaskType &= ~2u;
  if ( v14 && v14->pxObject )
  {
    QReference_Delete(v14, &QTask_tQTaskRefPool);
    ptQTask[44].tQTaskRefList.ptMiddle = nullptr;
    HIBYTE(ptQTask[74].ptPrev) = 0;
  }
  *(_DWORD *)&ptQTask[42].eQTaskType = 0;
  ptQTask[49].tQTaskRefList.ptTail = nullptr;
  ptState->pfState = HumanPlayer_RunStateJump;
}

_DWORD *__cdecl sub_4B6130(int a1, _DWORD *a2)
{
  a2[381] = 0;
  a2[382] = 0;
  a2[383] = 0;
  a2[384] = 0;
  a2[385] = 0;
  a2[386] = 0;
  a2[497] = 1145883853;
  return a2;
}

// source: j/0/human/humanplayer.c:8647  [anchor-mhash]
void __cdecl HumanPlayer_RunStateJump(struct State_s *ptState, struct QTask_s *ptQTask)
{
  unsigned int bSignal; // ebx
  struct QTask_s *ptPrev; // eax
  float *ptTail; // ecx
  double v5; // st7
  double v6; // st7
  double v7; // st6
  void (__cdecl *v8)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v10)(struct State_s *, struct QTask_s *); // eax
  struct QReference_s *ptMiddle; // eax
  void (__cdecl *v12)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v13)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v14)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v15)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v16)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v17)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v18)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v19)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v20)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v21)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v22)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v23)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v24)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v25)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v26)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v27)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v28)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v29)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v30)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v31)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v32)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v33)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v34)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v35)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v36)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v37)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v38)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v39)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v40)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v41)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v42)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v43)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v44)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v45)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v46)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v47)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v48)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v49)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v50)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v51)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v52)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v53)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v54)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v55)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v56)(struct State_s *, struct QTask_s *); // eax

  HumanPlayer_InAirControl(ptQTask);
  bSignal = ptState->bSignal;
  if ( *(float *)&ptQTask[38].tQTaskChildren.ptMiddle <= 0.0 )
    ptQTask[49].tQTaskRefList.ptTail = (struct QReference_s *)1145883853;
  ptPrev = ptQTask[33].ptNext[1].ptPrev;
  if ( (bSignal & 0x2000) != 0 )
  {
    if ( !ptPrev || (ptTail = (float *)ptPrev->tQTaskChildren.ptTail) == nullptr )
    {
      ptQTask[77].tQTaskChildren.ptHead = nullptr;
      ptQTask[77].tQTaskChildren.ptMiddle = nullptr;
      goto LABEL_15;
    }
    ptQTask[77].tQTaskChildren.ptHead = (struct QTask_s *)8;
    v5 = ptTail[217] + ptTail[214];
  }
  else
  {
    if ( !ptPrev || (ptTail = (float *)ptPrev->tQTaskChildren.ptTail) == nullptr )
    {
      ptQTask[77].tQTaskChildren.ptHead = nullptr;
      ptQTask[77].tQTaskChildren.ptMiddle = nullptr;
      goto LABEL_15;
    }
    ptQTask[77].tQTaskChildren.ptHead = (struct QTask_s *)7;
    v5 = ptTail[217];
  }
  v6 = v5 + ptTail[211];
  *(float *)&ptQTask[77].tQTaskChildren.ptMiddle = v6;
  v7 = *(float *)&ptQTask[43].ptParent;
  if ( v7 < 0.0 )
    v7 = -v7;
  *(float *)&ptQTask[77].tQTaskChildren.ptMiddle = v7 * ptTail[218] * 3.0 + v6;
LABEL_15:
  if ( (bSignal & 0x800000) != 0 )
  {
    SoundSys_NewSoundFn(ptQTask[33].tQTaskChildren.ptTail, "water_land_02");
    v8 = ptState->apfExitState[ptState->nState];
    if ( v8 )
      v8(ptState, ptQTask);
    apfState = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 21;
    v10 = apfState[21];
    ptState->pfState = v10;
    v10(ptState, ptQTask);
    return;
  }
  if ( (bSignal & 2) == 0 )
    return;
  if ( Water_IsUnderWater(
         (float *)&ptQTask[51].tQTaskRefList.ptMiddle,
         (struct real64x3_t *)&ptQTask[1],
         (int *)&ptQTask[51].tQTaskRefList.ptTail) )
  {
    SoundSys_NewSoundFn(ptQTask[33].tQTaskChildren.ptTail, "water_land_01");
  }
  else
  {
    ptMiddle = ptQTask[42].tQTaskRefList.ptMiddle;
    if ( ptMiddle )
      SoundSys_NewSoundFn(ptQTask[33].tQTaskChildren.ptTail, (char *)&ptMiddle[49].pxObject);
  }
  if ( *(float *)&ptQTask[25].tQTaskRefList.ptHead >= (double)*(float *)&ptQTask[25].tQTaskRefList.ptMiddle )
  {
    Human_UpdateDie((struct Human_s *)ptQTask);
    v54 = ptState->apfExitState[ptState->nState];
    if ( v54 )
      v54(ptState, ptQTask);
    v55 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 55;
    v56 = v55[55];
    ptState->pfState = v56;
    v56(ptState, ptQTask);
  }
  else
  {
    if ( *(_DWORD *)&ptQTask[32].eQTaskType == 1 )
    {
      if ( (bSignal & 0x80u) == 0 )
      {
        if ( (bSignal & 0x100) != 0 )
        {
          v15 = ptState->apfExitState[ptState->nState];
          if ( v15 )
            v15(ptState, ptQTask);
          v16 = ptState->apfState;
          ptState->nPreviousState = ptState->nState;
          ptState->nState = 29;
          v17 = v16[29];
          ptState->pfState = v17;
          v17(ptState, ptQTask);
        }
        else if ( (bSignal & 0x40) != 0 )
        {
          v18 = ptState->apfExitState[ptState->nState];
          if ( v18 )
            v18(ptState, ptQTask);
          v19 = ptState->apfState;
          ptState->nPreviousState = ptState->nState;
          ptState->nState = 32;
          v20 = v19[32];
          ptState->pfState = v20;
          v20(ptState, ptQTask);
        }
        else if ( (bSignal & 0x20) != 0 )
        {
          v21 = ptState->apfExitState[ptState->nState];
          if ( v21 )
            v21(ptState, ptQTask);
          v22 = ptState->apfState;
          ptState->nPreviousState = ptState->nState;
          ptState->nState = 33;
          v23 = v22[33];
          ptState->pfState = v23;
          v23(ptState, ptQTask);
        }
        else
        {
          v24 = ptState->apfExitState[ptState->nState];
          if ( v24 )
            v24(ptState, ptQTask);
          v25 = ptState->apfState;
          ptState->nPreviousState = ptState->nState;
          ptState->nState = 23;
          v26 = v25[23];
          ptState->pfState = v26;
          v26(ptState, ptQTask);
        }
      }
      else
      {
        v12 = ptState->apfExitState[ptState->nState];
        if ( v12 )
          v12(ptState, ptQTask);
        v13 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 26;
        v14 = v13[26];
        ptState->pfState = v14;
        v14(ptState, ptQTask);
      }
      return;
    }
    if ( (ptState->bSignal & 0x40000) != 0 )
    {
      if ( (bSignal & 0x80u) != 0 )
      {
        v27 = ptState->apfExitState[ptState->nState];
        if ( v27 )
          v27(ptState, ptQTask);
        v28 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 11;
        v29 = v28[11];
        ptState->pfState = v29;
        v29(ptState, ptQTask);
        return;
      }
      if ( (bSignal & 0x100) != 0 )
      {
        v30 = ptState->apfExitState[ptState->nState];
        if ( v30 )
          v30(ptState, ptQTask);
        v31 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 14;
        v32 = v31[14];
        ptState->pfState = v32;
        v32(ptState, ptQTask);
        return;
      }
      if ( (bSignal & 0x40) != 0 )
      {
        v33 = ptState->apfExitState[ptState->nState];
        if ( v33 )
          v33(ptState, ptQTask);
        v34 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 17;
        v35 = v34[17];
        ptState->pfState = v35;
        v35(ptState, ptQTask);
        return;
      }
      if ( (bSignal & 0x20) != 0 )
      {
        v36 = ptState->apfExitState[ptState->nState];
        if ( v36 )
          v36(ptState, ptQTask);
        v37 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 18;
        v38 = v37[18];
        ptState->pfState = v38;
        v38(ptState, ptQTask);
        return;
      }
      goto LABEL_78;
    }
    if ( (bSignal & 0x80u) == 0 )
    {
      if ( (bSignal & 0x100) != 0 )
      {
        v42 = ptState->apfExitState[ptState->nState];
        if ( v42 )
          v42(ptState, ptQTask);
        v43 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 6;
        v44 = v43[6];
        ptState->pfState = v44;
        v44(ptState, ptQTask);
      }
      else if ( (bSignal & 0x40) != 0 )
      {
        v45 = ptState->apfExitState[ptState->nState];
        if ( v45 )
          v45(ptState, ptQTask);
        v46 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 9;
        v47 = v46[9];
        ptState->pfState = v47;
        v47(ptState, ptQTask);
      }
      else
      {
        if ( (bSignal & 0x20) == 0 )
        {
LABEL_78:
          v51 = ptState->apfExitState[ptState->nState];
          if ( v51 )
            v51(ptState, ptQTask);
          v52 = ptState->apfState;
          ptState->nPreviousState = ptState->nState;
          ptState->nState = 0;
          v53 = *v52;
          ptState->pfState = *v52;
          v53(ptState, ptQTask);
          return;
        }
        v48 = ptState->apfExitState[ptState->nState];
        if ( v48 )
          v48(ptState, ptQTask);
        v49 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 10;
        v50 = v49[10];
        ptState->pfState = v50;
        v50(ptState, ptQTask);
      }
    }
    else
    {
      v39 = ptState->apfExitState[ptState->nState];
      if ( v39 )
        v39(ptState, ptQTask);
      v40 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 3;
      v41 = v40[3];
      ptState->pfState = v41;
      v41(ptState, ptQTask);
    }
  }
}

// source: j/0/human/humanplayer.c:8762  [anchor-mhash]
void __cdecl HumanPlayer_InitStateFall(struct State_s *ptState, struct QTask_s *ptQTask)
{
  int v2; // eax
  int v3; // eax
  int v4; // ebx
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptTail; // ecx
  double v8; // st7
  double v9; // st6

  v2 = *(_DWORD *)&ptQTask[32].eQTaskType;
  if ( !v2 )
  {
    v4 = 0;
    goto LABEL_7;
  }
  v3 = v2 - 1;
  if ( !v3 )
  {
    v4 = 23;
    goto LABEL_7;
  }
  if ( v3 == 1 )
  {
    v4 = 75;
LABEL_7:
    HumanAnim_SetAnimationAndTimeFromState(ptQTask, v4, 0, 0.0);
  }
  ptQTask[38].ptPrev = ptQTask[37].ptParent;
  ptNext = ptQTask[38].ptNext;
  ptQTask[38].tQTaskChildren.ptHead = *(struct QTask_s **)&ptQTask[37].eQTaskType;
  ptQTask[38].tQTaskChildren.ptMiddle = ptNext;
  ptPrev = ptQTask[33].ptNext[1].ptPrev;
  if ( ptPrev && (ptTail = ptPrev->tQTaskChildren.ptTail) != nullptr )
  {
    ptQTask[77].tQTaskChildren.ptHead = (struct QTask_s *)1;
    v8 = *(float *)&ptTail[21].ptPrev;
    ptQTask[77].tQTaskChildren.ptMiddle = ptTail[21].ptPrev;
    v9 = *(float *)&ptQTask[43].ptParent;
    if ( v9 < 0.0 )
      v9 = -v9;
    *(float *)&ptQTask[77].tQTaskChildren.ptMiddle = v9 * *(float *)&ptTail[21].ptParent * 3.0 + v8;
    ptState->pfState = HumanPlayer_RunStateFall;
  }
  else
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    ptQTask[77].tQTaskChildren.ptMiddle = nullptr;
    ptState->pfState = HumanPlayer_RunStateFall;
  }
}

// source: j/0/human/humanplayer.c:8795  [anchor-mhash]
void __cdecl HumanPlayer_RunStateFall(struct State_s *ptState, struct QTask_s *ptQTask)
{
  unsigned int bSignal; // eax
  void (__cdecl *v3)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v5)(struct State_s *, struct QTask_s *); // eax
  struct QReference_s *ptMiddle; // eax
  double v7; // st7
  bool v8; // c0
  int v9; // eax
  int v10; // eax
  void (__cdecl *v11)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v12)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v13)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v14)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v15)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v16)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v17)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v18)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v19)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v20)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v21)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v22)(struct State_s *, struct QTask_s *); // eax

  HumanPlayer_InAirControl(ptQTask);
  bSignal = ptState->bSignal;
  if ( (bSignal & 0x800000) != 0 )
  {
    SoundSys_NewSoundFn(ptQTask[33].tQTaskChildren.ptTail, "water_land_02");
    v3 = ptState->apfExitState[ptState->nState];
    if ( v3 )
      v3(ptState, ptQTask);
    apfState = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 21;
    v5 = apfState[21];
    ptState->pfState = v5;
    v5(ptState, ptQTask);
  }
  else if ( (bSignal & 2) != 0 )
  {
    if ( Water_IsUnderWater(
           (float *)&ptQTask[51].tQTaskRefList.ptMiddle,
           (struct real64x3_t *)&ptQTask[1],
           (int *)&ptQTask[51].tQTaskRefList.ptTail) )
    {
      SoundSys_NewSoundFn(ptQTask[33].tQTaskChildren.ptTail, "water_land_01");
    }
    else
    {
      ptMiddle = ptQTask[42].tQTaskRefList.ptMiddle;
      if ( ptMiddle )
        SoundSys_NewSoundFn(ptQTask[33].tQTaskChildren.ptTail, (char *)&ptMiddle[49].pxObject);
    }
    v7 = *(float *)&ptQTask[25].tQTaskRefList.ptHead;
    ptQTask[38].ptPrev = nullptr;
    v8 = v7 < *(float *)&ptQTask[25].tQTaskRefList.ptMiddle;
    ptQTask[38].tQTaskChildren.ptHead = nullptr;
    ptQTask[38].tQTaskChildren.ptMiddle = nullptr;
    ptQTask[38].tQTaskChildren.ptTail = nullptr;
    ptQTask[38].tQTaskRefList.ptHead = nullptr;
    ptQTask[38].tQTaskRefList.ptMiddle = nullptr;
    if ( v8 )
    {
      v9 = *(_DWORD *)&ptQTask[32].eQTaskType;
      if ( v9 )
      {
        v10 = v9 - 1;
        if ( v10 )
        {
          if ( v10 == 1 )
          {
            v11 = ptState->apfExitState[ptState->nState];
            if ( v11 )
              v11(ptState, ptQTask);
            v12 = ptState->apfState;
            ptState->nPreviousState = ptState->nState;
            ptState->nState = 75;
            v13 = v12[75];
            ptState->pfState = v13;
            v13(ptState, ptQTask);
          }
        }
        else
        {
          v14 = ptState->apfExitState[ptState->nState];
          if ( v14 )
            v14(ptState, ptQTask);
          v15 = ptState->apfState;
          ptState->nPreviousState = ptState->nState;
          ptState->nState = 23;
          v16 = v15[23];
          ptState->pfState = v16;
          v16(ptState, ptQTask);
        }
      }
      else
      {
        v17 = ptState->apfExitState[ptState->nState];
        if ( v17 )
          v17(ptState, ptQTask);
        v18 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 0;
        v19 = *v18;
        ptState->pfState = *v18;
        v19(ptState, ptQTask);
      }
    }
    else
    {
      Human_UpdateDie((struct Human_s *)ptQTask);
      v20 = ptState->apfExitState[ptState->nState];
      if ( v20 )
        v20(ptState, ptQTask);
      v21 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 55;
      v22 = v21[55];
      ptState->pfState = v22;
      v22(ptState, ptQTask);
    }
  }
}

// source: j/0/human/humanplayer.c:8868  [anchor-callee]
void __cdecl HumanPlayer_SetWeaponTypeAnim(
        struct QTask_s *ptQTask,
        enum WeaponTypeGetAnimType_e eAnimType,
        int nTimeFrame,
        enum bool isReverse)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vTimeScale; };
    struct { char igi2_o1[8]; struct WeaponTypeGetAnimContext_s tGetAnimContext; };
    char igi2_extent[40];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptPrev; // ecx
  int v5; // ebp
  struct QTask_s *ptTail; // edi
  struct QTask_s *v7; // ecx
  unsigned __int8 *v8; // edx

  ptPrev = ptQTask[33].ptNext[1].ptPrev;
  v5 = nTimeFrame;
  ptTail = ptQTask[33].tQTaskChildren.ptTail;
  if ( ptPrev )
  {
    v7 = ptPrev->tQTaskChildren.ptTail;
    if ( v7 )
    {
      v8 = (unsigned __int8 *)ptTail[7].tQTaskRefList.ptTail;
      igi2_frame.tGetAnimContext.tIn.ptWeapon = ptQTask[33].ptNext;
      igi2_frame.tGetAnimContext.tIn.ptHierarchy = v8;
      igi2_frame.tGetAnimContext.tIn.eAnimType = eAnimType;
      igi2_frame.tGetAnimContext.tIn.nFireType = (int)ptQTask[77].ptPrev;
      igi2_frame.tGetAnimContext.tIn.ptWeaponType = nullptr;
      igi2_frame.tGetAnimContext.tOut.ptAnim = nullptr;
      ((void (__cdecl *)(struct QTask_s *, struct WeaponTypeGetAnimContext_s *))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][v7->eQTaskType].pfHandler)(
        v7,
        &igi2_frame.tGetAnimContext);
      igi2_frame.vTimeScale = igi2_frame.tGetAnimContext.tOut.vTimeScale;
      if ( igi2_frame.tGetAnimContext.tOut.ptAnim )
      {
        if ( isReverse )
          igi2_frame.vTimeScale = igi2_frame.tGetAnimContext.tOut.vTimeScale * -1.0;
        if ( igi2_frame.vTimeScale < 0.0 )
          v5 = igi2_frame.tGetAnimContext.tOut.ptAnim->nTotalTime - nTimeFrame;
        AnimController_SetAnimationAndTime(
          (struct AnimController_t *)ptTail[16].tQTaskRefList.ptTail,
          igi2_frame.tGetAnimContext.tOut.ptAnim,
          v5);
        ptTail[16].tQTaskRefList.ptTail[5].pxObject = (void *)(__int64)((double)AnimController_nTicksPerFrame
                                                                      * igi2_frame.vTimeScale);
        *(_DWORD *)&ptQTask[74].eQTaskType &= ~1u;
      }
      else
      {
        ptTail[16].tQTaskRefList.ptTail[3].pxObject = (void *)((int)ptTail[16].tQTaskRefList.ptTail[3].pxObject | 4);
        *(_DWORD *)&ptQTask[74].eQTaskType |= 1u;
      }
    }
  }
}

// source: j/0/human/humanplayer.c:8943  [anchor-mhash]
void __cdecl HumanPlayer_SwimUpdateActivate(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float pxContext; };
    struct { char igi2_o1[4]; struct EvaluateActivateContext_t tEvaluateActivateContext; };
    char igi2_extent[144];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptTail; // eax
  double v2; // st6
  double v3; // st5
  double v4; // st4
  struct QTask_s *v5; // eax
  struct QTask_s *ptBestQTask; // esi

  ptTail = ptQTask[33].tQTaskChildren.ptTail;
  v2 = *(float *)&ptQTask[7].tQTaskRefList.ptHead;
  v3 = *(float *)&ptQTask[7].tQTaskChildren.ptTail;
  v4 = *(float *)&ptQTask[7].tQTaskRefList.ptMiddle;
  igi2_frame.tEvaluateActivateContext.ptQTask = ptQTask;
  qmemcpy(&igi2_frame.tEvaluateActivateContext.tViewPos, &ptTail[10].tQTaskChildren, sizeof(igi2_frame.tEvaluateActivateContext.tViewPos));
  qmemcpy(
    &igi2_frame.tEvaluateActivateContext.tViewOrientation,
    &ptTail[10].ptParent,
    sizeof(igi2_frame.tEvaluateActivateContext.tViewOrientation));
  qmemcpy(
    &igi2_frame.tEvaluateActivateContext.tObjectOrientation,
    &ptQTask[3].ptPrev,
    sizeof(igi2_frame.tEvaluateActivateContext.tObjectOrientation));
  igi2_frame.tEvaluateActivateContext.vBestAlpha = 3.1415927410125732;
  igi2_frame.tEvaluateActivateContext.vBestGamma = 3.1415927410125732;
  igi2_frame.tEvaluateActivateContext.vBestLength = 8192.0;
  igi2_frame.tEvaluateActivateContext.ptBestQTask = nullptr;
  igi2_frame.pxContext = sqrt(v4 * v4 + v3 * v3 + v2 * v2) + *(float *)&ptQTask[8].ptNext;
  World_TriggerQTaskEventSphereSpecificTree(
    Game_ptGame->ptWorld,
    GameFunctions_eEvaluateActivateQTaskEvent,
    &igi2_frame.tEvaluateActivateContext,
    (struct real64x3_t *)&ptQTask[1],
    igi2_frame.pxContext,
    0xFFFFFFFF,
    WORLD_DYNCUBETREE_STATIONARY);
  v5 = ptQTask[46].tQTaskChildren.ptTail;
  ptBestQTask = igi2_frame.tEvaluateActivateContext.ptBestQTask;
  if ( v5 )
  {
    QReference_Delete((struct QReference_s *)v5, &QTask_tQTaskRefPool);
    ptQTask[46].tQTaskChildren.ptTail = nullptr;
  }
  if ( ptBestQTask )
    ptQTask[46].tQTaskChildren.ptTail = (struct QTask_s *)QTask_NewQTaskRef(ptBestQTask);
}

// source: j/0/human/humanplayer.c:8984  [anchor-mhash]
void __cdecl HumanPlayer_RunStateTreadWater(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real64x3_t tPos; };
    struct { char igi2_o1[24]; struct AnimHeader_s *ptAnim; };
    struct { char igi2_o2[28]; float v40; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v3; // st7
  struct State_s *v4; // ebx
  unsigned int bSignal; // ecx
  double v6; // st6
  struct QTask_s *ptTail; // eax
  struct QReference_s *ptHead; // eax
  int v9; // eax
  int v10; // esi
  struct QReference_s *v11; // edx
  struct QTask_s *v12; // eax
  struct QTask_s *v13; // ecx
  struct QTask_s *v14; // ecx
  struct QTask_s *v15; // eax
  void (__cdecl *v16)(struct QTask_s *, struct real64x3_t *); // ecx
  struct QTask_s *v17; // eax
  struct QReference_s *v18; // edx
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptPrev; // ecx
  struct QTask_s *v21; // ecx
  struct QTask_s *v22; // eax
  void (__cdecl *pfHandler)(struct QTask_s *, struct real64x3_t *); // ecx
  struct QTask_s *v24; // eax
  void (__cdecl *v25)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v27)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v28)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v29)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v30)(struct State_s *, struct QTask_s *); // eax
  int v31; // ecx
  void (__cdecl *v32)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v33)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v34)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v35)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v36)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v37)(struct State_s *, struct QTask_s *); // eax
  struct QTask_s *ptQTaska = *(struct QTask_s * *)&ptQTask; // [esp+44h] [ebp+8h] ARGSLOT

  HumanPlayer_SwimUpdateActivate(ptQTask);
  v3 = *(float *)&ptQTask[51].tQTaskRefList.ptMiddle - 5734.39990234375;
  v4 = ptState;
  bSignal = ptState->bSignal;
  ptQTaska = (struct QTask_s *)bSignal;
  v6 = v3;
  if ( v3 < 0.0 )
    v6 = -v3;
  if ( v6 > 4.096 )
  {
    qmemcpy(&igi2_frame.tPos, &ptQTask[1], sizeof(igi2_frame.tPos));
    igi2_frame.tPos.vZ = v3 + igi2_frame.tPos.vZ;
    Human_PopPosition(ptQTask, &igi2_frame.tPos);
    bSignal = (unsigned int)ptQTaska;
    ptQTask[86].tQTaskChildren.ptHead = nullptr;
    ptQTask[86].tQTaskChildren.ptMiddle = nullptr;
    ptQTask[86].tQTaskChildren.ptTail = nullptr;
  }
  if ( *(float *)&ptQTask[51].tQTaskRefList.ptMiddle < 5734.39990234375 && (bSignal & 2) != 0 )
  {
    ptTail = ptQTask[33].tQTaskChildren.ptTail;
    *(_DWORD *)&ptTail[14].eQTaskType = 0;
    ptTail[14].tQTaskRefList.ptMiddle = nullptr;
    ptHead = ptQTask[86].tQTaskRefList.ptHead;
    if ( ptHead )
    {
      Weapon_Activate(ptQTask[33].ptNext, (char *)&ptHead[7], false);
      ptQTask[86].tQTaskRefList.ptHead = nullptr;
    }
    v9 = *(_DWORD *)&ptQTask[32].eQTaskType;
    ptQTask[77].tQTaskRefList.ptTail = (struct QReference_s *)12;
    ptQTask[87].tQTaskChildren.ptMiddle = (struct QTask_s *)1;
    v10 = v9 == 2 ? 90 : 87;
    if ( v9 == 2 )
    {
      HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
      if ( v10 != 90 )
      {
        HumanAnim_SetAnimationAndTimeFromState(ptQTask, v10, 0, 0.0);
        v4 = ptState;
        goto LABEL_29;
      }
      v18 = ptQTask[7].tQTaskRefList.ptTail;
      LODWORD(igi2_frame.tPos.vZ) = ptQTask[77].ptPrev;
      ptNext = ptQTask[33].ptNext;
      ptQTask[35].tQTaskRefList.ptHead = (struct QReference_s *)90;
      *(_QWORD *)&igi2_frame.tPos.vX = __PAIR64__((unsigned int)ptNext, (unsigned int)v18);
      *(_QWORD *)&igi2_frame.tPos.vY = 0x1A00000000LL;
      igi2_frame.ptAnim = nullptr;
      ptPrev = ptNext[1].ptPrev;
      if ( ptPrev )
        v21 = ptPrev->tQTaskChildren.ptTail;
      else
        v21 = nullptr;
      v22 = ptNext[1].ptPrev;
      pfHandler = (void (__cdecl *)(struct QTask_s *, struct real64x3_t *))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][v21->eQTaskType].pfHandler;
      if ( v22 )
        v24 = v22->tQTaskChildren.ptTail;
      else
        v24 = nullptr;
      pfHandler(v24, &igi2_frame.tPos);
      if ( igi2_frame.ptAnim )
        goto LABEL_17;
    }
    else
    {
      v11 = ptQTask[7].tQTaskRefList.ptTail;
      LODWORD(igi2_frame.tPos.vZ) = ptQTask[77].ptPrev;
      v12 = ptQTask[33].ptNext;
      ptQTask[35].tQTaskRefList.ptHead = (struct QReference_s *)87;
      *(_QWORD *)&igi2_frame.tPos.vX = __PAIR64__((unsigned int)v12, (unsigned int)v11);
      *(_QWORD *)&igi2_frame.tPos.vY = 0xF00000000LL;
      igi2_frame.ptAnim = nullptr;
      v13 = v12[1].ptPrev;
      if ( v13 )
        v14 = v13->tQTaskChildren.ptTail;
      else
        v14 = nullptr;
      v15 = v12[1].ptPrev;
      v16 = (void (__cdecl *)(struct QTask_s *, struct real64x3_t *))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][v14->eQTaskType].pfHandler;
      if ( v15 )
        v17 = v15->tQTaskChildren.ptTail;
      else
        v17 = nullptr;
      v16(v17, &igi2_frame.tPos);
      if ( igi2_frame.ptAnim )
      {
LABEL_17:
        HumanAnim_SetUpperBodyAnimationFromHeader(ptQTask, igi2_frame.ptAnim, igi2_frame.ptAnim->nTotalTime, 0.0);
        ptQTask[34].tQTaskRefList.ptHead[5].pxObject = (void *)(__int64)(-igi2_frame.v40 * (double)AnimController_nTicksPerFrame);
LABEL_29:
        HumanPlayer_SetWeaponTypeAnim(ptQTask, WEAPONTYPE_GETANIMTYPE_1STACTIVATE, 0, true);
        ptQTask[75].tQTaskChildren.ptHead = (struct QTask_s *)sub_4C2030;
        LOBYTE(ptQTask[80].tQTaskRefList.ptMiddle) = 0;
        LOBYTE(ptQTask[76].tQTaskRefList.ptMiddle) = 0;
        v25 = v4->apfExitState[v4->nState];
        if ( v25 )
          v25(v4, ptQTask);
        apfState = v4->apfState;
        v4->nPreviousState = v4->nState;
        v4->nState = 0;
        v27 = *apfState;
        v4->pfState = *apfState;
        v27(v4, ptQTask);
        return;
      }
    }
    HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
    goto LABEL_29;
  }
  if ( (bSignal & 0x20000) != 0 )
  {
    LOBYTE(ptQTask[76].tQTaskRefList.ptMiddle) = 0;
    v28 = ptState->apfExitState[ptState->nState];
    if ( v28 )
      v28(ptState, ptQTask);
    v29 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 55;
    v30 = v29[55];
    ptState->pfState = v30;
    v30(ptState, ptQTask);
  }
  else
  {
    v31 = bSignal & 0x180;
    if ( v31 == 128 )
    {
      v32 = ptState->apfExitState[ptState->nState];
      if ( v32 )
        v32(ptState, ptQTask);
      v33 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 19;
      v34 = v33[19];
      ptState->pfState = v34;
      v34(ptState, ptQTask);
    }
    else if ( v31 == 256 )
    {
      v35 = ptState->apfExitState[ptState->nState];
      if ( v35 )
        v35(ptState, ptQTask);
      v36 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 20;
      v37 = v36[20];
      ptState->pfState = v37;
      v37(ptState, ptQTask);
    }
  }
}

// source: j/0/human/humanplayer.c:9061  [anchor-caller]
void __cdecl HumanPlayer_InitStateSwim(struct State_s *ptState, struct QTask_s *ptQTask)
{
  struct QTask_s *v2; // esi
  struct QTask_s *ptTail; // eax
  struct QTask_s *ptNext; // eax
  struct QTask_s *v5; // eax
  struct QTask_s *v6; // ebx
  struct QTask_s *v7; // eax
  struct QTask_s *ptHead; // edi
  struct QTask_s *v9; // eax
  struct State_s *v10; // edi
  int nPreviousState; // eax
  struct QReference_s *ptMiddle; // eax
  unsigned int v13; // edx

  v2 = ptQTask;
  ptTail = ptQTask[33].tQTaskChildren.ptTail;
  *(_DWORD *)&ptTail[14].eQTaskType = 0;
  ptTail[14].tQTaskRefList.ptMiddle = (struct QReference_s *)1157627904;
  ptNext = ptQTask[33].ptNext;
  if ( ptNext[1].tQTaskChildren.ptTail )
  {
    ptNext[2].ptParent = (struct QTask_s *)1;
    ptNext[1].tQTaskChildren.ptTail = nullptr;
    v5 = ptQTask[33].ptNext;
    v5[3].tQTaskRefList.ptHead = (struct QReference_s *)1;
    v5[1].tQTaskChildren.ptTail = nullptr;
  }
  Weapon_StopAllSound(ptQTask[33].ptNext);
  v6 = ptQTask[33].ptNext;
  v7 = v6[2].tQTaskChildren.ptTail;
  if ( v7 )
  {
    ptHead = v7->tQTaskChildren.ptHead;
    if ( ptHead )
    {
      v9 = ptHead[33].tQTaskChildren.ptTail;
      v9[16].tQTaskRefList.ptMiddle = nullptr;
      *(float *)&v9[16].tQTaskChildren.ptHead = tan(0.7853981852531433);
      *(float *)&v9[16].tQTaskRefList.ptHead = tan(0.5235987901687622);
    }
  }
  else
  {
    ptHead = nullptr;
  }
  if ( ptHead[33].ptNext[4].ptPrev )
  {
    QTask_Delete(ptHead[33].ptNext[4].ptPrev);
    ptHead[33].ptNext[4].ptPrev = nullptr;
  }
  v6[4].ptNext = nullptr;
  HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, 0, 0.20000000298023224);
  v10 = ptState;
  nPreviousState = ptState->nPreviousState;
  if ( nPreviousState != 19 && nPreviousState != 21 && nPreviousState != 20 )
  {
    ptQTask[75].tQTaskChildren.ptHead = (struct QTask_s *)HumanPlayer_RunActionLock;
    HumanPlayer_SetWeaponTypeAnim(ptQTask, WEAPONTYPE_GETANIMTYPE_1STACTIVATE, 0, false);
    v2 = ptQTask;
  }
  ptMiddle = v2[44].tQTaskRefList.ptMiddle;
  v13 = *(_DWORD *)&v2[30].eQTaskType & 0xFFFFFFFD;
  v2[38].ptPrev = nullptr;
  v2[38].tQTaskChildren.ptHead = nullptr;
  v2[38].tQTaskChildren.ptMiddle = nullptr;
  *(_DWORD *)&v2[30].eQTaskType = v13;
  if ( ptMiddle && ptMiddle->pxObject )
  {
    QReference_Delete(ptMiddle, &QTask_tQTaskRefPool);
    v2[44].tQTaskRefList.ptMiddle = nullptr;
    HIBYTE(v2[74].ptPrev) = 0;
  }
  *(_DWORD *)&v2[42].eQTaskType = 0;
  LOBYTE(v2[76].tQTaskRefList.ptMiddle) = 1;
  LOBYTE(v2[80].tQTaskRefList.ptMiddle) = 1;
  v2[77].tQTaskRefList.ptTail = nullptr;
  v2[77].ptParent = nullptr;
  if ( v2[34].tQTaskRefList.ptHead )
  {
    AnimBlender_Blend(
      (struct AnimBlender_t *)v2[35].tQTaskChildren.ptHead,
      (struct AnimControllerBase_t *)v2[35].ptPrev,
      (struct AnimControllerBase_t *)v2[35].ptNext,
      1920);
    v10 = ptState;
    ptQTask[34].tQTaskRefList.ptHead = nullptr;
    v2 = ptQTask;
  }
  if ( v10->nState == 21 )
  {
    v10->pfState = HumanPlayer_RunStateTreadWater;
    Water_PlayerMovementEffect(
      (struct real64x3_t *)&v2[1],
      (int)v2[51].tQTaskRefList.ptTail,
      (enum bool)(BYTE1(v2[50].ptNext) != 0));
  }
  else
  {
    v10->bSignal |= 0x100000u;
    v10->pfState = HumanPlayer_RunStateSwim;
  }
}

// source: j/0/human/humanplayer.c:9126  [anchor-mhash]
void __cdecl HumanPlayer_RunStateSwim(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real64x3_t tPos; };
    struct { char igi2_o1[24]; struct AnimHeader_s *ptAnim; };
    struct { char igi2_o2[28]; float v44; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct State_s *v3; // ebx
  double v4; // st7
  double v5; // st6
  __int16 v6; // cx
  struct QTask_s *ptTail; // eax
  struct QReference_s *ptHead; // eax
  int v9; // eax
  int v10; // esi
  struct QReference_s *v11; // edx
  struct QTask_s *v12; // eax
  struct QTask_s *v13; // ecx
  struct QTask_s *v14; // ecx
  struct QTask_s *v15; // eax
  void (__cdecl *v16)(struct QTask_s *, struct real64x3_t *); // ecx
  struct QTask_s *v17; // eax
  struct QReference_s *v18; // edx
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptPrev; // ecx
  struct QTask_s *v21; // ecx
  struct QTask_s *v22; // eax
  void (__cdecl *pfHandler)(struct QTask_s *, struct real64x3_t *); // ecx
  struct QTask_s *v24; // eax
  void (__cdecl *v25)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v27)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v28)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v29)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v30)(struct State_s *, struct QTask_s *); // eax
  int nState; // eax
  int v32; // ecx
  void (__cdecl *v33)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v34)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v35)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v36)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v37)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v38)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v39)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v40)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v41)(struct State_s *, struct QTask_s *); // eax
  unsigned int ptQTaska = *(unsigned int *)&ptQTask; // [esp+44h] [ebp+8h] ARGSLOT

  HumanPlayer_SwimUpdateActivate(ptQTask);
  v3 = ptState;
  ptQTaska = ptState->bSignal;
  if ( (ptQTaska & 0x100000) != 0 )
  {
    *(_DWORD *)&ptQTask[30].eQTaskType &= ~0x100000u;
    Human_CreateSwimStrokeSound(ptQTask);
  }
  v4 = *(float *)&ptQTask[51].tQTaskRefList.ptMiddle - 5734.39990234375;
  v5 = v4;
  if ( v4 < 0.0 )
    v5 = -v4;
  if ( v5 > 4.096 )
  {
    qmemcpy(&igi2_frame.tPos, &ptQTask[1], sizeof(igi2_frame.tPos));
    igi2_frame.tPos.vZ = v4 + igi2_frame.tPos.vZ;
    Human_PopPosition(ptQTask, &igi2_frame.tPos);
    ptQTask[86].tQTaskChildren.ptHead = nullptr;
    ptQTask[86].tQTaskChildren.ptMiddle = nullptr;
    ptQTask[86].tQTaskChildren.ptTail = nullptr;
  }
  v6 = ptQTaska & 0x1E0;
  if ( (ptQTaska & 0x80u) != 0 )
  {
    Human_MoveOnGround(ptQTask, 163.8400115966797, 0.0);
LABEL_11:
    v6 = ptQTaska & 0x1E0;
    goto LABEL_12;
  }
  if ( (v6 & 0x100) != 0 )
  {
    Human_MoveOnGround(ptQTask, 81.92000579833984, 3.1415927410125732);
    goto LABEL_11;
  }
LABEL_12:
  if ( *(float *)&ptQTask[51].tQTaskRefList.ptMiddle < 5734.39990234375 && (ptQTaska & 2) != 0 )
  {
    ptTail = ptQTask[33].tQTaskChildren.ptTail;
    *(_DWORD *)&ptTail[14].eQTaskType = 0;
    ptTail[14].tQTaskRefList.ptMiddle = nullptr;
    ptHead = ptQTask[86].tQTaskRefList.ptHead;
    if ( ptHead )
    {
      Weapon_Activate(ptQTask[33].ptNext, (char *)&ptHead[7], false);
      ptQTask[86].tQTaskRefList.ptHead = nullptr;
    }
    v9 = *(_DWORD *)&ptQTask[32].eQTaskType;
    ptQTask[77].tQTaskRefList.ptTail = (struct QReference_s *)12;
    ptQTask[87].tQTaskChildren.ptMiddle = (struct QTask_s *)1;
    v10 = v9 == 2 ? 90 : 87;
    if ( v9 == 2 )
    {
      HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
      if ( v10 != 90 )
      {
        HumanAnim_SetAnimationAndTimeFromState(ptQTask, v10, 0, 0.0);
        v3 = ptState;
        goto LABEL_36;
      }
      v18 = ptQTask[7].tQTaskRefList.ptTail;
      LODWORD(igi2_frame.tPos.vZ) = ptQTask[77].ptPrev;
      ptNext = ptQTask[33].ptNext;
      ptQTask[35].tQTaskRefList.ptHead = (struct QReference_s *)90;
      *(_QWORD *)&igi2_frame.tPos.vX = __PAIR64__((unsigned int)ptNext, (unsigned int)v18);
      *(_QWORD *)&igi2_frame.tPos.vY = 0x1A00000000LL;
      igi2_frame.ptAnim = nullptr;
      ptPrev = ptNext[1].ptPrev;
      if ( ptPrev )
        v21 = ptPrev->tQTaskChildren.ptTail;
      else
        v21 = nullptr;
      v22 = ptNext[1].ptPrev;
      pfHandler = (void (__cdecl *)(struct QTask_s *, struct real64x3_t *))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][v21->eQTaskType].pfHandler;
      if ( v22 )
        v24 = v22->tQTaskChildren.ptTail;
      else
        v24 = nullptr;
      pfHandler(v24, &igi2_frame.tPos);
      if ( igi2_frame.ptAnim )
        goto LABEL_24;
    }
    else
    {
      v11 = ptQTask[7].tQTaskRefList.ptTail;
      LODWORD(igi2_frame.tPos.vZ) = ptQTask[77].ptPrev;
      v12 = ptQTask[33].ptNext;
      ptQTask[35].tQTaskRefList.ptHead = (struct QReference_s *)87;
      *(_QWORD *)&igi2_frame.tPos.vX = __PAIR64__((unsigned int)v12, (unsigned int)v11);
      *(_QWORD *)&igi2_frame.tPos.vY = 0xF00000000LL;
      igi2_frame.ptAnim = nullptr;
      v13 = v12[1].ptPrev;
      if ( v13 )
        v14 = v13->tQTaskChildren.ptTail;
      else
        v14 = nullptr;
      v15 = v12[1].ptPrev;
      v16 = (void (__cdecl *)(struct QTask_s *, struct real64x3_t *))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][v14->eQTaskType].pfHandler;
      if ( v15 )
        v17 = v15->tQTaskChildren.ptTail;
      else
        v17 = nullptr;
      v16(v17, &igi2_frame.tPos);
      if ( igi2_frame.ptAnim )
      {
LABEL_24:
        HumanAnim_SetUpperBodyAnimationFromHeader(ptQTask, igi2_frame.ptAnim, igi2_frame.ptAnim->nTotalTime, 0.0);
        ptQTask[34].tQTaskRefList.ptHead[5].pxObject = (void *)(__int64)(-igi2_frame.v44 * (double)AnimController_nTicksPerFrame);
LABEL_36:
        HumanPlayer_SetWeaponTypeAnim(ptQTask, WEAPONTYPE_GETANIMTYPE_1STACTIVATE, 0, true);
        ptQTask[75].tQTaskChildren.ptHead = (struct QTask_s *)sub_4C2030;
        LOBYTE(ptQTask[80].tQTaskRefList.ptMiddle) = 0;
        LOBYTE(ptQTask[76].tQTaskRefList.ptMiddle) = 0;
        v25 = v3->apfExitState[v3->nState];
        if ( v25 )
          v25(v3, ptQTask);
        apfState = v3->apfState;
        v3->nPreviousState = v3->nState;
        v3->nState = 0;
        v27 = *apfState;
        v3->pfState = *apfState;
        v27(v3, ptQTask);
        return;
      }
    }
    HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
    goto LABEL_36;
  }
  if ( (ptQTaska & 0x20000) != 0 )
  {
    LOBYTE(ptQTask[76].tQTaskRefList.ptMiddle) = 0;
    v28 = ptState->apfExitState[ptState->nState];
    if ( v28 )
      v28(ptState, ptQTask);
    v29 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 55;
    v30 = v29[55];
    ptState->pfState = v30;
    v30(ptState, ptQTask);
  }
  else
  {
    nState = ptState->nState;
    v32 = v6 & 0x180;
    if ( nState == 19 && v32 == 256 )
    {
      v33 = ptState->apfExitState[19];
      if ( v33 )
        v33(ptState, ptQTask);
      v34 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 20;
      v35 = v34[20];
      ptState->pfState = v35;
      v35(ptState, ptQTask);
    }
    else if ( nState == 20 && v32 == 128 )
    {
      v36 = ptState->apfExitState[20];
      if ( v36 )
        v36(ptState, ptQTask);
      v37 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 19;
      v38 = v37[19];
      ptState->pfState = v38;
      v38(ptState, ptQTask);
    }
    else if ( !v32 )
    {
      v39 = ptState->apfExitState[nState];
      if ( v39 )
        v39(ptState, ptQTask);
      v40 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 21;
      v41 = v40[21];
      ptState->pfState = v41;
      v41(ptState, ptQTask);
    }
  }
}

// source: j/0/human/humanplayer.c:9221  [anchor-caller]
void __cdecl HumanPlayer_InitStateActivateDoor(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s *ptActivateQTask; };
    struct { char igi2_o1[4]; float vGamma; };
    struct { char igi2_o2[8]; float vBeta; };
    struct { char igi2_o3[12]; __int64 vAlpha; };
    struct { char igi2_o4[20]; struct real64x3_t tPos; };
    struct { char igi2_o5[44]; struct real64x3_t Real64x3_Rotate_tTemp; };
    struct { char igi2_o6[68]; struct real32x9_t tOrientation; };
    char igi2_extent[108];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QReference_s *ptHead; // eax
  struct QTask_s *v3; // edi
  struct QTask_s *ptTail; // eax
  struct QTask_s *v5; // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *v7; // ecx
  double v8; // st7
  double v9; // st6

  ptHead = ptQTask[46].tQTaskRefList.ptHead;
  igi2_frame.ptActivateQTask = nullptr;
  if ( ptHead )
    igi2_frame.ptActivateQTask = (struct QTask_s *)ptHead->pxObject;
  ptQTask[81].ptPrev = *(struct QTask_s **)&ptQTask[32].eQTaskType;
  *(_DWORD *)&ptQTask[32].eQTaskType = 0;
  ptQTask[77].tQTaskRefList.ptTail = nullptr;
  ptQTask[77].ptParent = nullptr;
  HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.4000000059604645);
  HumanAnim_SetAnimationAndTimeFromState(ptQTask, 69, 0, 0.0);
  AnimController_Step(
    (struct AnimController_t *)ptQTask[34].tQTaskChildren.ptTail,
    (int)ptQTask[34].tQTaskChildren.ptTail[1].tQTaskRefList.ptMiddle
  + (unsigned int)ptQTask[34].tQTaskChildren.ptTail[1].tQTaskRefList.ptTail);
  qmemcpy(&igi2_frame.tOrientation, &igi2_frame.ptActivateQTask[3].ptPrev, sizeof(igi2_frame.tOrientation));
  GameFunctions_GetMagicVertex(&igi2_frame.tPos, igi2_frame.ptActivateQTask, 0);
  v3 = ptQTask;
  if ( igi2_frame.tOrientation.tZ.vY * (*(double *)&ptQTask[1].tQTaskChildren.ptTail - igi2_frame.tPos.vZ)
     + igi2_frame.tOrientation.tY.vY * (*(double *)&ptQTask[1].tQTaskChildren.ptHead - igi2_frame.tPos.vY)
     + igi2_frame.tOrientation.tX.vY * (*(double *)&ptQTask[1].ptNext - igi2_frame.tPos.vX) < 0.0 )
    Real32x9_RotateGamma(&igi2_frame.tOrientation, &igi2_frame.tOrientation, 3.1415927410125732);
  igi2_frame.Real64x3_Rotate_tTemp.vZ = (igi2_frame.tOrientation.tZ.vZ + igi2_frame.tOrientation.tZ.vX) * 0.0 + igi2_frame.tOrientation.tZ.vY * 3481.6;
  igi2_frame.tPos.vX = (igi2_frame.tOrientation.tX.vZ + igi2_frame.tOrientation.tX.vX) * 0.0 + igi2_frame.tOrientation.tX.vY * 3481.6 + igi2_frame.tPos.vX;
  igi2_frame.tPos.vY = (igi2_frame.tOrientation.tY.vZ + igi2_frame.tOrientation.tY.vX) * 0.0 + igi2_frame.tOrientation.tY.vY * 3481.6 + igi2_frame.tPos.vY;
  igi2_frame.tPos.vZ = igi2_frame.Real64x3_Rotate_tTemp.vZ + igi2_frame.tPos.vZ;
  Human_PopPosition(ptQTask, &igi2_frame.tPos);
  ptQTask[86].tQTaskChildren.ptHead = nullptr;
  ptQTask[86].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[86].tQTaskChildren.ptTail = nullptr;
  Human_SnapToGround(ptQTask);
  Real32x9_GetAngles(&igi2_frame.tOrientation, (float *)&igi2_frame.vAlpha, &igi2_frame.vBeta, &igi2_frame.vGamma);
  igi2_frame.vGamma = igi2_frame.vGamma + 3.1415927410125732;
  Human_PopOrientation(ptQTask, igi2_frame.vGamma);
  igi2_frame.vAlpha = (__int64)(*(float *)&igi2_frame.ptActivateQTask[20].tQTaskRefList.ptHead * 30.0);
  ptTail = ptQTask[33].tQTaskChildren.ptTail;
  *(_QWORD *)&ptQTask[77].eQTaskType = (unsigned int)igi2_frame.vAlpha;
  ptQTask[33].tQTaskRefList.ptHead = (struct QReference_s *)3;
  LOBYTE(ptQTask[78].ptPrev) = 1;
  BYTE1(ptQTask[36].tQTaskChildren.ptTail) = 1;
  *(_DWORD *)&ptTail[11].eQTaskType = 0;
  ptTail[12].ptNext = nullptr;
  ptTail[12].ptPrev = nullptr;
  ptTail[12].tQTaskRefList.ptHead = nullptr;
  ptTail[12].tQTaskChildren.ptHead = nullptr;
  ptTail[12].tQTaskChildren.ptMiddle = nullptr;
  ptTail[12].tQTaskChildren.ptTail = nullptr;
  ptTail[12].tQTaskRefList.ptMiddle = nullptr;
  LOBYTE(ptQTask[33].tQTaskChildren.ptTail[12].tQTaskRefList.ptTail) = 1;
  LOBYTE(ptQTask[34].tQTaskChildren.ptMiddle) = 1;
  LOBYTE(ptQTask[76].tQTaskRefList.ptMiddle) = 1;
  if ( HIBYTE(igi2_frame.ptActivateQTask[23].tQTaskChildren.ptMiddle)
    && *(float *)&igi2_frame.ptActivateQTask[10].tQTaskChildren.ptTail > 0.6000000238418579
    || Door_GetDoorStatus(igi2_frame.ptActivateQTask) == 1 )
  {
    QTask_DeleteQTaskAndQTaskRefSafe(&ptQTask[85].tQTaskRefList.ptMiddle);
    v5 = SoundSys_NewSoundFn(
           ptQTask[33].tQTaskChildren.ptTail,
           (char *)&igi2_frame.ptActivateQTask[13].tQTaskChildren.ptMiddle);
    ptQTask[85].tQTaskRefList.ptMiddle = QTask_NewQTaskRef(v5);
    if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
    {
      HumanPlayer_SendActivateMessage(igi2_frame.ptActivateQTask, 2, 0);
      v3 = ptQTask;
    }
  }
  ptPrev = v3[33].ptNext[1].ptPrev;
  if ( ptPrev && (v7 = ptPrev->tQTaskChildren.ptTail) != nullptr )
  {
    v3[77].tQTaskChildren.ptHead = nullptr;
    v8 = *(float *)&v7[21].ptNext;
    v3[77].tQTaskChildren.ptMiddle = v7[21].ptNext;
    v9 = *(float *)&v3[43].ptParent;
    if ( v9 < 0.0 )
      v9 = -v9;
    *(float *)&v3[77].tQTaskChildren.ptMiddle = v9 * *(float *)&v7[21].ptParent * 3.0 + v8;
  }
  else
  {
    v3[77].tQTaskChildren.ptHead = nullptr;
    v3[77].tQTaskChildren.ptMiddle = nullptr;
  }
  v3[84].tQTaskChildren.ptMiddle = (struct QTask_s *)20;
  ptState->pfState = HumanPlayer_RunStateActivateDoor;
  if ( !CDAPFN0506_HumanPlayer_InitStateActivateDoor.Version )
    ((void (*)(void))CDAPFN0506_HumanPlayer_InitStateActivateDoor.FunctionAddress)();
}

// source: j/0/human/humanplayer.c:9349  [anchor-strings]
void __cdecl HumanPlayer_RunStateActivateDoor(struct State_s *ptState, struct QTask_s *ptQTask)
{
  struct QReference_s *ptHead; // eax
  struct QTask_s *pxObject; // edi
  struct QTask_s *ptMiddle; // eax
  unsigned int bSignal; // eax
  struct QTask_s *ptNext; // ecx
  struct QTask_s *v10; // eax
  struct QReference_s *v11; // eax
  void (__cdecl *v12)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v14)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v15)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v16)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v17)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v18)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v19)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v20)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v21)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v22)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v23)(struct State_s *, struct QTask_s *); // eax
  unsigned int ptStatea = *(unsigned int *)&ptState; // [esp+18h] [ebp+4h] ARGSLOT
  bool ptQTaska = *(bool *)&ptQTask; // [esp+1Ch] [ebp+8h] ARGSLOT

  ptHead = ptQTask[46].tQTaskRefList.ptHead;
  pxObject = nullptr;
  if ( ptHead )
    pxObject = (struct QTask_s *)ptHead->pxObject;
  ptQTaska = 0;
  HumanPlayer_MoveOnGround((struct HumanPlayer_t *)ptQTask, 0.0, 118.76579284667969, 0.0, 118.76579284667969);
  ActionMenuScreen_ptQTask[4].ptNext = (struct QTask_s *)10;
  ptMiddle = ptQTask[84].tQTaskChildren.ptMiddle;
  if ( ptMiddle )
    ptQTask[84].tQTaskChildren.ptMiddle = (struct QTask_s *)((char *)ptMiddle - 1);
  else
    ptQTaska = *(float *)&ptQTask[20].ptNext == 0.0;
  bSignal = ptState->bSignal;
  if ( (bSignal & 0x20000) != 0 )
    ptQTaska = 1;
  if ( (bSignal & 0x10000) != 0 )
    ptQTaska = 1;
  ptNext = ptQTask[78].ptNext;
  v10 = *(struct QTask_s **)&ptQTask[77].eQTaskType;
  if ( (int)ptNext < (int)v10 )
    ptQTask[78].ptNext = (struct QTask_s *)((char *)&ptNext->ptNext + 1);
  ptStatea = ptState->bSignal;
  if ( ptQTask[78].ptNext == v10 )
  {
    if ( !ptQTaska )
    {
      if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
      {
        if ( !Door_GetDoorStatus(pxObject) || Door_GetDoorStatus(pxObject) == 1 )
          HumanPlayer_SendActivateMessage(pxObject, 2, 1);
      }
      else
      {
        HIBYTE(pxObject[23].tQTaskChildren.ptTail) = 1;
        Door_ToggleOpenDoorEx(pxObject, (struct real64x3_t *)&ptQTask[1]);
      }
      Human_SendDoorAIEvent(pxObject, ptQTask);
      SoundSys_NewSoundFn(ptQTask[33].tQTaskChildren.ptTail, "pickloop_end");
      goto LABEL_16;
    }
  }
  else if ( !ptQTaska )
  {
    return;
  }
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
    HumanPlayer_SendActivateMessage(pxObject, 0, 0);
LABEL_16:
  LOBYTE(ptQTask[33].tQTaskChildren.ptTail[12].tQTaskRefList.ptTail) = 0;
  v11 = ptQTask[46].tQTaskRefList.ptHead;
  LOBYTE(ptQTask[34].tQTaskChildren.ptMiddle) = 0;
  LOBYTE(ptQTask[46].tQTaskRefList.ptMiddle) = 0;
  BYTE1(ptQTask[46].tQTaskRefList.ptMiddle) = 1;
  LOBYTE(ptQTask[76].tQTaskRefList.ptMiddle) = 0;
  if ( v11 )
  {
    QReference_Delete(v11, &QTask_tQTaskRefPool);
    ptQTask[46].tQTaskRefList.ptHead = nullptr;
  }
  ptQTask[33].tQTaskRefList.ptHead = (struct QReference_s *)1;
  BYTE1(ptQTask[36].tQTaskChildren.ptTail) = 0;
  LOBYTE(ptQTask[78].ptPrev) = 0;
  QTask_DeleteQTaskAndQTaskRefSafe(&ptQTask[85].tQTaskRefList.ptMiddle);
  QTask_DeleteQTaskAndQTaskRefSafe(&ptQTask[85].tQTaskRefList.ptHead);
  if ( (ptStatea & 0x10000) != 0 )
  {
    v12 = ptState->apfExitState[ptState->nState];
    if ( v12 )
      v12(ptState, ptQTask);
    apfState = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 54;
    v14 = apfState[54];
    ptState->pfState = v14;
    v14(ptState, ptQTask);
  }
  else if ( ptQTask[81].ptPrev == (struct QTask_s *)1 )
  {
    v21 = ptState->apfExitState[ptState->nState];
    if ( v21 )
      v21(ptState, ptQTask);
    v22 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 23;
    v23 = v22[23];
    ptState->pfState = v23;
    v23(ptState, ptQTask);
  }
  else if ( ptQTask[81].ptPrev == (struct QTask_s *)2 )
  {
    v18 = ptState->apfExitState[ptState->nState];
    if ( v18 )
      v18(ptState, ptQTask);
    v19 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 75;
    v20 = v19[75];
    ptState->pfState = v20;
    v20(ptState, ptQTask);
  }
  else
  {
    v15 = ptState->apfExitState[ptState->nState];
    if ( v15 )
      v15(ptState, ptQTask);
    v16 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 0;
    v17 = *v16;
    ptState->pfState = *v16;
    v17(ptState, ptQTask);
  }
}

// source: j/0/human/humanplayer.c:9493  [anchor-strings]
void __cdecl HumanPlayer_InitStateActivateCabinet(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s *pxObject; };
    struct { char igi2_o1[4]; float vGamma; };
    struct { char igi2_o2[8]; float vBeta; };
    struct { char igi2_o3[12]; __int64 vAlpha; };
    struct { char igi2_o4[20]; struct real64x3_t tPos; };
    struct { char igi2_o5[44]; struct real64x3_t Real64x3_Rotate_tTemp; };
    struct { char igi2_o6[68]; struct real32x9_t tOrientation; };
    char igi2_extent[108];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QReference_s *ptHead; // eax
  struct QTask_s *v3; // eax
  struct QTask_s *ptTail; // eax
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *v7; // ecx
  double v8; // st7
  double v9; // st6

  ptHead = ptQTask[46].tQTaskRefList.ptHead;
  igi2_frame.pxObject = nullptr;
  if ( ptHead )
    igi2_frame.pxObject = (struct QTask_s *)ptHead->pxObject;
  ptQTask[81].ptPrev = *(struct QTask_s **)&ptQTask[32].eQTaskType;
  *(_DWORD *)&ptQTask[32].eQTaskType = 0;
  ptQTask[77].tQTaskRefList.ptTail = nullptr;
  ptQTask[77].ptParent = nullptr;
  HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.4000000059604645);
  HumanAnim_SetAnimationAndTimeFromState(ptQTask, 70, 0, 0.0);
  ptQTask[78].tQTaskChildren.ptMiddle = nullptr;
  AnimController_Step(
    (struct AnimController_t *)ptQTask[34].tQTaskChildren.ptTail,
    (int)ptQTask[34].tQTaskChildren.ptTail[1].tQTaskRefList.ptMiddle
  + (unsigned int)ptQTask[34].tQTaskChildren.ptTail[1].tQTaskRefList.ptTail);
  qmemcpy(&igi2_frame.tOrientation, &igi2_frame.pxObject[3].ptPrev, sizeof(igi2_frame.tOrientation));
  GameFunctions_GetMagicVertex(&igi2_frame.tPos, igi2_frame.pxObject, 0);
  igi2_frame.Real64x3_Rotate_tTemp.vZ = (igi2_frame.tOrientation.tZ.vZ + igi2_frame.tOrientation.tZ.vX) * 0.0 + igi2_frame.tOrientation.tZ.vY * 3481.6;
  igi2_frame.tPos.vX = igi2_frame.tPos.vX + (igi2_frame.tOrientation.tX.vZ + igi2_frame.tOrientation.tX.vX) * 0.0 + igi2_frame.tOrientation.tX.vY * 3481.6;
  igi2_frame.tPos.vY = igi2_frame.tPos.vY + (igi2_frame.tOrientation.tY.vZ + igi2_frame.tOrientation.tY.vX) * 0.0 + igi2_frame.tOrientation.tY.vY * 3481.6;
  igi2_frame.tPos.vZ = igi2_frame.tPos.vZ + igi2_frame.Real64x3_Rotate_tTemp.vZ;
  Human_PopPosition(ptQTask, &igi2_frame.tPos);
  ptQTask[86].tQTaskChildren.ptHead = nullptr;
  ptQTask[86].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[86].tQTaskChildren.ptTail = nullptr;
  Human_SnapToGround(ptQTask);
  Real32x9_GetAngles(&igi2_frame.tOrientation, (float *)&igi2_frame.vAlpha, &igi2_frame.vBeta, &igi2_frame.vGamma);
  igi2_frame.vGamma = igi2_frame.vGamma + 3.1415927410125732;
  Human_PopOrientation(ptQTask, igi2_frame.vGamma);
  LOBYTE(ptQTask[76].tQTaskRefList.ptMiddle) = 1;
  QTask_DeleteQTaskAndQTaskRefSafe(&ptQTask[85].tQTaskRefList.ptMiddle);
  v3 = SoundSys_NewSoundFn(ptQTask[33].tQTaskChildren.ptTail, "tba_searchcab");
  ptQTask[85].tQTaskRefList.ptMiddle = QTask_NewQTaskRef(v3);
  igi2_frame.vAlpha = (__int64)(*(float *)&igi2_frame.pxObject[10].ptNext * 30.0);
  ptTail = ptQTask[33].tQTaskChildren.ptTail;
  *(_QWORD *)&ptQTask[77].eQTaskType = (unsigned int)igi2_frame.vAlpha;
  ptQTask[33].tQTaskRefList.ptHead = (struct QReference_s *)3;
  LOBYTE(ptQTask[78].ptPrev) = 1;
  BYTE1(ptQTask[36].tQTaskChildren.ptTail) = 1;
  *(_DWORD *)&ptTail[11].eQTaskType = 0;
  ptTail[12].ptNext = nullptr;
  ptTail[12].ptPrev = nullptr;
  ptTail[12].tQTaskRefList.ptHead = nullptr;
  ptTail[12].tQTaskChildren.ptHead = nullptr;
  ptTail[12].tQTaskChildren.ptMiddle = nullptr;
  ptTail[12].tQTaskChildren.ptTail = nullptr;
  ptTail[12].tQTaskRefList.ptMiddle = nullptr;
  LOBYTE(ptQTask[33].tQTaskChildren.ptTail[12].tQTaskRefList.ptTail) = 1;
  ptNext = ptQTask[33].ptNext;
  LOBYTE(ptQTask[34].tQTaskChildren.ptMiddle) = 1;
  ptPrev = ptNext[1].ptPrev;
  if ( ptPrev && (v7 = ptPrev->tQTaskChildren.ptTail) != nullptr )
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    v8 = *(float *)&v7[21].ptNext;
    ptQTask[77].tQTaskChildren.ptMiddle = v7[21].ptNext;
    v9 = *(float *)&ptQTask[43].ptParent;
    if ( v9 < 0.0 )
      v9 = -v9;
    *(float *)&ptQTask[77].tQTaskChildren.ptMiddle = v9 * *(float *)&v7[21].ptParent * 3.0 + v8;
  }
  else
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    ptQTask[77].tQTaskChildren.ptMiddle = nullptr;
  }
  ptQTask[84].tQTaskChildren.ptMiddle = (struct QTask_s *)20;
  ptState->pfState = HumanPlayer_RunStateActivateCabinet;
  if ( !CDAPFN0506_HumanPlayer_InitStateActivateCabinet.Version )
    ((void (*)(void))CDAPFN0506_HumanPlayer_InitStateActivateCabinet.FunctionAddress)();
}

// source: j/0/human/humanplayer.c:9597  [anchor-mhash]
void __cdecl HumanPlayer_RunStateActivateCabinet(struct State_s *ptState, struct QTask_s *ptQTask)
{
  struct QReference_s *ptHead; // eax
  char *pxObject; // esi
  struct QTask_s *ptMiddle; // eax
  struct QTask_s *ptNext; // eax
  struct QTask_s *v9; // eax
  struct QTask_s *ptTail; // eax
  struct QTask_s *v11; // eax
  struct QReference_s *ptPrev; // ecx
  struct QTask_s *v13; // eax
  unsigned int bSignal; // eax
  struct QTask_s *v15; // eax
  unsigned int v16; // ecx
  struct QTask_s *v17; // eax
  struct QReference_s *v18; // eax
  void (__cdecl *v19)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v21)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v22)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v23)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v24)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v25)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v26)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v27)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v28)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v29)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v30)(struct State_s *, struct QTask_s *); // eax
  unsigned int ptStatea = *(unsigned int *)&ptState; // [esp+18h] [ebp+4h] ARGSLOT
  char ptQTaska = *(char *)&ptQTask; // [esp+1Ch] [ebp+8h] ARGSLOT

  ptHead = ptQTask[46].tQTaskRefList.ptHead;
  pxObject = nullptr;
  if ( ptHead )
    pxObject = (char *)ptHead->pxObject;
  ptQTaska = 0;
  HumanPlayer_MoveOnGround((struct HumanPlayer_t *)ptQTask, 0.0, 118.76579284667969, 0.0, 118.76579284667969);
  ptMiddle = ptQTask[78].tQTaskChildren.ptMiddle;
  if ( ptMiddle )
  {
    if ( ptMiddle == (struct QTask_s *)1 )
    {
      if ( (ptNext = ptQTask[33].ptNext) != nullptr
        && (v9 = ptNext[1].ptPrev) != nullptr
        && (ptTail = v9->tQTaskChildren.ptTail) != nullptr
        && (ptQTask[7].tQTaskRefList.ptTail != *(struct QReference_s **)&ptTail[48].tQTaskChildren.ptHead[24].eQTaskType
          ? (v11 = ptTail[48].tQTaskChildren.ptMiddle)
          : (v11 = ptTail[48].tQTaskChildren.ptHead),
            v11) )
      {
        ptPrev = v11[6].tQTaskRefList.ptMiddle[1].ptPrev;
      }
      else
      {
        ptPrev = nullptr;
      }
      if ( (int)ptQTask[78].ptNext > (int)(*(_DWORD *)&ptQTask[77].eQTaskType - 30 * ((int)ptPrev / 4800)) )
      {
        HumanAnim_SetAnimationAndTimeFromState(ptQTask, 72, 0, 0.20000000298023224);
        ptQTask[78].tQTaskChildren.ptMiddle = (struct QTask_s *)2;
      }
    }
  }
  else if ( (ptState->bSignal & 1) != 0 )
  {
    HumanAnim_SetAnimationAndTimeFromState(ptQTask, 71, 0, 0.0);
    ptQTask[78].tQTaskChildren.ptMiddle = (struct QTask_s *)1;
  }
  ActionMenuScreen_ptQTask[4].ptNext = (struct QTask_s *)10;
  v13 = ptQTask[84].tQTaskChildren.ptMiddle;
  if ( v13 )
  {
    ptQTask[84].tQTaskChildren.ptMiddle = (struct QTask_s *)((char *)v13 - 1);
  }
  else if ( *(float *)&ptQTask[20].ptNext == 0.0 )
  {
    ptQTaska = 1;
  }
  bSignal = ptState->bSignal;
  if ( (bSignal & 0x20000) != 0 )
    ptQTaska = 1;
  if ( (bSignal & 0x10000) != 0 )
    ptQTaska = 1;
  v15 = ptQTask[78].ptNext;
  if ( (int)v15 < (int)(*(_DWORD *)&ptQTask[77].eQTaskType) )
    ptQTask[78].ptNext = (struct QTask_s *)((char *)&v15->ptNext + 1);
  ptStatea = ptState->bSignal;
  v16 = ptStatea;
  if ( (ptStatea & 0x200000) != 0 )
  {
    *(_DWORD *)&ptQTask[30].eQTaskType &= ~0x200000u;
    *(_WORD *)(pxObject + 407) = 1;
    pxObject[406] = 1;
  }
  if ( (ptStatea & 0x400000) != 0 )
  {
    *(_DWORD *)&ptQTask[30].eQTaskType &= ~0x400000u;
    pxObject[408] = 1;
    *((_WORD *)pxObject + 203) = 1;
  }
  if ( ptQTask[78].ptNext == *(struct QTask_s **)&ptQTask[77].eQTaskType )
  {
    if ( !ptQTaska )
    {
      pxObject[416] = 1;
      goto LABEL_35;
    }
  }
  else if ( !ptQTaska )
  {
    return;
  }
  pxObject[405] = 1;
  pxObject[406] = 1;
  QTask_DeleteQTaskAndQTaskRefSafe(&ptQTask[85].tQTaskRefList.ptMiddle);
  v16 = ptStatea;
LABEL_35:
  v17 = ptQTask[33].tQTaskChildren.ptTail;
  LOBYTE(ptQTask[76].tQTaskRefList.ptMiddle) = 0;
  LOBYTE(v17[12].tQTaskRefList.ptTail) = 0;
  v18 = ptQTask[46].tQTaskRefList.ptHead;
  LOBYTE(ptQTask[34].tQTaskChildren.ptMiddle) = 0;
  LOBYTE(ptQTask[46].tQTaskRefList.ptMiddle) = 0;
  BYTE1(ptQTask[46].tQTaskRefList.ptMiddle) = 1;
  if ( v18 )
  {
    QReference_Delete(v18, &QTask_tQTaskRefPool);
    v16 = ptStatea;
    ptQTask[46].tQTaskRefList.ptHead = nullptr;
  }
  ptQTask[33].tQTaskRefList.ptHead = (struct QReference_s *)1;
  LOBYTE(ptQTask[78].ptPrev) = 0;
  BYTE1(ptQTask[36].tQTaskChildren.ptTail) = 0;
  if ( (v16 & 0x10000) != 0 )
  {
    v19 = ptState->apfExitState[ptState->nState];
    if ( v19 )
      v19(ptState, ptQTask);
    apfState = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 54;
    v21 = apfState[54];
    ptState->pfState = v21;
    v21(ptState, ptQTask);
  }
  else if ( ptQTask[81].ptPrev == (struct QTask_s *)1 )
  {
    v28 = ptState->apfExitState[ptState->nState];
    if ( v28 )
      v28(ptState, ptQTask);
    v29 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 23;
    v30 = v29[23];
    ptState->pfState = v30;
    v30(ptState, ptQTask);
  }
  else if ( ptQTask[81].ptPrev == (struct QTask_s *)2 )
  {
    v25 = ptState->apfExitState[ptState->nState];
    if ( v25 )
      v25(ptState, ptQTask);
    v26 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 75;
    v27 = v26[75];
    ptState->pfState = v27;
    v27(ptState, ptQTask);
  }
  else
  {
    v22 = ptState->apfExitState[ptState->nState];
    if ( v22 )
      v22(ptState, ptQTask);
    v23 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 0;
    v24 = *v23;
    ptState->pfState = *v23;
    v24(ptState, ptQTask);
  }
}

// source: j/0/human/humanplayer.c:9785  [anchor-caller]
void __cdecl HumanPlayer_InitStateActivateTerminal(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s *ptActivateQTask; };
    struct { char igi2_o1[4]; float vGamma; };
    struct { char igi2_o2[8]; float vBeta; };
    struct { char igi2_o3[12]; __int64 vAlpha; };
    struct { char igi2_o4[20]; struct real64x3_t tPos; };
    struct { char igi2_o5[44]; struct real64x3_t Real64x3_Rotate_tTemp; };
    struct { char igi2_o6[68]; struct real32x9_t tOrientation; };
    char igi2_extent[108];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QReference_s *ptHead; // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptTail; // ecx
  double v5; // st7
  double v6; // st6
  struct QTask_s *v7; // edi
  struct QReference_s *ptMiddle; // eax
  struct QTask_s *v9; // eax
  struct QTask_s *v10; // eax

  ptHead = ptQTask[46].tQTaskRefList.ptHead;
  igi2_frame.ptActivateQTask = nullptr;
  if ( ptHead )
    igi2_frame.ptActivateQTask = (struct QTask_s *)ptHead->pxObject;
  ptQTask[81].ptPrev = *(struct QTask_s **)&ptQTask[32].eQTaskType;
  *(_DWORD *)&ptQTask[32].eQTaskType = 0;
  ptQTask[77].tQTaskRefList.ptTail = nullptr;
  ptQTask[77].ptParent = nullptr;
  HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.4000000059604645);
  ptPrev = ptQTask[33].ptNext[1].ptPrev;
  if ( ptPrev && (ptTail = ptPrev->tQTaskChildren.ptTail) != nullptr )
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    v5 = *(float *)&ptTail[21].ptNext;
    ptQTask[77].tQTaskChildren.ptMiddle = ptTail[21].ptNext;
    v6 = *(float *)&ptQTask[43].ptParent;
    if ( v6 < 0.0 )
      v6 = -v6;
    *(float *)&ptQTask[77].tQTaskChildren.ptMiddle = v6 * *(float *)&ptTail[21].ptParent * 3.0 + v5;
  }
  else
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    ptQTask[77].tQTaskChildren.ptMiddle = nullptr;
  }
  HumanAnim_SetAnimationAndTimeFromState(ptQTask, 73, 0, 0.0);
  AnimController_Step(
    (struct AnimController_t *)ptQTask[34].tQTaskChildren.ptTail,
    (int)ptQTask[34].tQTaskChildren.ptTail[1].tQTaskRefList.ptMiddle
  + (unsigned int)ptQTask[34].tQTaskChildren.ptTail[1].tQTaskRefList.ptTail);
  qmemcpy(&igi2_frame.tOrientation, &igi2_frame.ptActivateQTask[3].ptPrev, sizeof(igi2_frame.tOrientation));
  GameFunctions_GetMagicVertex(&igi2_frame.tPos, igi2_frame.ptActivateQTask, 1);
  v7 = ptQTask;
  igi2_frame.Real64x3_Rotate_tTemp.vZ = (igi2_frame.tOrientation.tZ.vZ + igi2_frame.tOrientation.tZ.vX) * 0.0 + igi2_frame.tOrientation.tZ.vY * 2764.8;
  igi2_frame.tPos.vX = igi2_frame.tPos.vX + (igi2_frame.tOrientation.tX.vZ + igi2_frame.tOrientation.tX.vX) * 0.0 + igi2_frame.tOrientation.tX.vY * 2764.8;
  igi2_frame.tPos.vY = igi2_frame.tPos.vY + (igi2_frame.tOrientation.tY.vZ + igi2_frame.tOrientation.tY.vX) * 0.0 + igi2_frame.tOrientation.tY.vY * 2764.8;
  igi2_frame.tPos.vZ = igi2_frame.tPos.vZ + igi2_frame.Real64x3_Rotate_tTemp.vZ;
  Human_PopPosition(ptQTask, &igi2_frame.tPos);
  ptQTask[86].tQTaskChildren.ptHead = nullptr;
  ptQTask[86].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[86].tQTaskChildren.ptTail = nullptr;
  Human_SnapToGround(ptQTask);
  ptMiddle = ptQTask[44].tQTaskRefList.ptMiddle;
  if ( ptMiddle && ptMiddle->pxObject )
  {
    QReference_Delete(ptMiddle, &QTask_tQTaskRefPool);
    ptQTask[44].tQTaskRefList.ptMiddle = nullptr;
    HIBYTE(ptQTask[74].ptPrev) = 0;
  }
  Real32x9_GetAngles(&igi2_frame.tOrientation, (float *)&igi2_frame.vAlpha, &igi2_frame.vBeta, &igi2_frame.vGamma);
  igi2_frame.vGamma = igi2_frame.vGamma + 3.1415927410125732;
  Human_PopOrientation(ptQTask, igi2_frame.vGamma);
  LOBYTE(ptQTask[76].tQTaskRefList.ptMiddle) = 1;
  igi2_frame.vAlpha = (__int64)(*(float *)&igi2_frame.ptActivateQTask[15].tQTaskRefList.ptTail * 30.0);
  *(_DWORD *)&ptQTask[77].eQTaskType = igi2_frame.vAlpha;
  v9 = ptQTask[33].tQTaskChildren.ptTail;
  ptQTask[78].ptNext = nullptr;
  ptQTask[33].tQTaskRefList.ptHead = (struct QReference_s *)3;
  LOBYTE(ptQTask[78].ptPrev) = 1;
  BYTE1(ptQTask[36].tQTaskChildren.ptTail) = 1;
  *(_DWORD *)&v9[11].eQTaskType = 0;
  v9[12].ptNext = nullptr;
  v9[12].ptPrev = nullptr;
  v9[12].tQTaskRefList.ptHead = nullptr;
  v9[12].tQTaskChildren.ptHead = nullptr;
  v9[12].tQTaskChildren.ptMiddle = nullptr;
  v9[12].tQTaskChildren.ptTail = nullptr;
  v9[12].tQTaskRefList.ptMiddle = nullptr;
  LOBYTE(ptQTask[33].tQTaskChildren.ptTail[12].tQTaskRefList.ptTail) = 1;
  LOBYTE(ptQTask[34].tQTaskChildren.ptMiddle) = 1;
  QTask_DeleteQTaskAndQTaskRefSafe(&ptQTask[85].tQTaskRefList.ptMiddle);
  v10 = SoundSys_NewSoundFn(ptQTask[33].tQTaskChildren.ptTail, (char *)&igi2_frame.ptActivateQTask[15].ptParent);
  ptQTask[85].tQTaskRefList.ptMiddle = QTask_NewQTaskRef(v10);
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    HumanPlayer_SendActivateMessage(igi2_frame.ptActivateQTask, 4, 0);
    v7 = ptQTask;
  }
  v7[84].tQTaskChildren.ptMiddle = (struct QTask_s *)20;
  ptState->pfState = HumanPlayer_RunStateActivateTerminal;
  if ( !CDAPFN0506_HumanPlayer_InitStateActivateTerminal.Version )
    ((void (*)(void))CDAPFN0506_HumanPlayer_InitStateActivateTerminal.FunctionAddress)();
}

// source: j/0/human/humanplayer.c:9893  [anchor-strings]
void __cdecl HumanPlayer_RunStateActivateTerminal(struct State_s *ptState, struct QTask_s *ptQTask)
{
  struct QReference_s *ptHead; // eax
  struct QTask_s *pxObject; // edi
  struct QTask_s *ptMiddle; // eax
  unsigned int bSignal; // eax
  struct QTask_s *ptNext; // ecx
  struct QTask_s *v10; // eax
  struct QTask_s *ptTail; // eax
  struct QReference_s *v12; // eax
  void (__cdecl *v13)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v15)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v16)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v17)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v18)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v19)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v20)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v21)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v22)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v23)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v24)(struct State_s *, struct QTask_s *); // eax
  unsigned int ptStatea = *(unsigned int *)&ptState; // [esp+14h] [ebp+4h] ARGSLOT
  bool ptQTaska = *(bool *)&ptQTask; // [esp+18h] [ebp+8h] ARGSLOT

  ptHead = ptQTask[46].tQTaskRefList.ptHead;
  pxObject = nullptr;
  if ( ptHead )
    pxObject = (struct QTask_s *)ptHead->pxObject;
  ptQTaska = 0;
  HumanPlayer_MoveOnGround((struct HumanPlayer_t *)ptQTask, 0.0, 118.76579284667969, 0.0, 118.76579284667969);
  ActionMenuScreen_ptQTask[4].ptNext = (struct QTask_s *)10;
  ptMiddle = ptQTask[84].tQTaskChildren.ptMiddle;
  if ( ptMiddle )
    ptQTask[84].tQTaskChildren.ptMiddle = (struct QTask_s *)((char *)ptMiddle - 1);
  else
    ptQTaska = *(float *)&ptQTask[20].ptNext == 0.0;
  bSignal = ptState->bSignal;
  if ( (bSignal & 0x20000) != 0 )
    ptQTaska = 1;
  if ( (bSignal & 0x10000) != 0 )
    ptQTaska = 1;
  ptNext = ptQTask[78].ptNext;
  v10 = *(struct QTask_s **)&ptQTask[77].eQTaskType;
  if ( (int)ptNext < (int)v10 )
    ptQTask[78].ptNext = (struct QTask_s *)((char *)&ptNext->ptNext + 1);
  ptStatea = ptState->bSignal;
  if ( ptQTask[78].ptNext != v10 )
  {
    if ( !ptQTaska )
      return;
    goto LABEL_14;
  }
  if ( ptQTaska )
  {
LABEL_14:
    if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
      HumanPlayer_SendActivateMessage(pxObject, 0, 0);
    goto LABEL_16;
  }
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    HumanPlayer_SendActivateMessage(pxObject, 4, 1);
  }
  else
  {
    pxObject[18].ptParent = (struct QTask_s *)1;
    pxObject[19].ptPrev = nullptr;
  }
  SoundSys_NewSoundFn(ptQTask[33].tQTaskChildren.ptTail, "typecomp_end");
LABEL_16:
  ptTail = ptQTask[33].tQTaskChildren.ptTail;
  LOBYTE(ptQTask[76].tQTaskRefList.ptMiddle) = 0;
  LOBYTE(ptTail[12].tQTaskRefList.ptTail) = 0;
  v12 = ptQTask[46].tQTaskRefList.ptHead;
  LOBYTE(ptQTask[34].tQTaskChildren.ptMiddle) = 0;
  LOBYTE(ptQTask[46].tQTaskRefList.ptMiddle) = 0;
  BYTE1(ptQTask[46].tQTaskRefList.ptMiddle) = 1;
  if ( v12 )
  {
    QReference_Delete(v12, &QTask_tQTaskRefPool);
    ptQTask[46].tQTaskRefList.ptHead = nullptr;
  }
  ptQTask[33].tQTaskRefList.ptHead = (struct QReference_s *)1;
  LOBYTE(ptQTask[78].ptPrev) = 0;
  BYTE1(ptQTask[36].tQTaskChildren.ptTail) = 0;
  QTask_DeleteQTaskAndQTaskRefSafe(&ptQTask[85].tQTaskRefList.ptMiddle);
  QTask_DeleteQTaskAndQTaskRefSafe(&ptQTask[85].tQTaskRefList.ptHead);
  if ( (ptStatea & 0x10000) != 0 )
  {
    v13 = ptState->apfExitState[ptState->nState];
    if ( v13 )
      v13(ptState, ptQTask);
    apfState = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 54;
    v15 = apfState[54];
    ptState->pfState = v15;
    v15(ptState, ptQTask);
  }
  else if ( ptQTask[81].ptPrev == (struct QTask_s *)1 )
  {
    v22 = ptState->apfExitState[ptState->nState];
    if ( v22 )
      v22(ptState, ptQTask);
    v23 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 23;
    v24 = v23[23];
    ptState->pfState = v24;
    v24(ptState, ptQTask);
  }
  else if ( ptQTask[81].ptPrev == (struct QTask_s *)2 )
  {
    v19 = ptState->apfExitState[ptState->nState];
    if ( v19 )
      v19(ptState, ptQTask);
    v20 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 75;
    v21 = v20[75];
    ptState->pfState = v21;
    v21(ptState, ptQTask);
  }
  else
  {
    v16 = ptState->apfExitState[ptState->nState];
    if ( v16 )
      v16(ptState, ptQTask);
    v17 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 0;
    v18 = *v17;
    ptState->pfState = *v17;
    v18(ptState, ptQTask);
  }
}

// source: j/0/human/humanplayer.c:10025  [anchor-caller]
void __cdecl HumanPlayer_InitStateActivateStationaryGun(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s *ptAttachQTask; };
    struct { char igi2_o1[4]; float vGamma; };
    struct { char igi2_o2[8]; float vBeta; };
    struct { char igi2_o3[12]; float vAlpha; };
    struct { char igi2_o4[16]; struct real64x3_t tPos; };
    struct { char igi2_o5[40]; struct real64x3_t Real64x3_Rotate_tTemp; };
    struct { char igi2_o6[64]; struct real32x9_t tOrientation; };
    char igi2_extent[104];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QReference_s *ptHead; // ecx
  struct QTask_s *v3; // edx
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptTail; // ecx
  double v6; // st7
  double v7; // st6
  struct QTask_s *v8; // eax

  ptHead = ptQTask[46].tQTaskRefList.ptHead;
  v3 = nullptr;
  igi2_frame.ptAttachQTask = nullptr;
  if ( ptHead )
  {
    igi2_frame.ptAttachQTask = (struct QTask_s *)ptHead->pxObject;
    v3 = igi2_frame.ptAttachQTask;
  }
  ptQTask[81].ptPrev = *(struct QTask_s **)&ptQTask[32].eQTaskType;
  *(_DWORD *)&ptQTask[32].eQTaskType = 0;
  qmemcpy(&igi2_frame.tOrientation, &v3[3].ptPrev, sizeof(igi2_frame.tOrientation));
  GameFunctions_GetMagicVertex(&igi2_frame.tPos, v3, 0);
  igi2_frame.Real64x3_Rotate_tTemp.vZ = igi2_frame.tOrientation.tZ.vZ * -6348.8 - igi2_frame.tOrientation.tZ.vY * 204.8 + igi2_frame.tOrientation.tZ.vX * 0.0;
  igi2_frame.tPos.vX = igi2_frame.tPos.vX + igi2_frame.tOrientation.tX.vZ * -6348.8 - igi2_frame.tOrientation.tX.vY * 204.8 + igi2_frame.tOrientation.tX.vX * 0.0;
  igi2_frame.tPos.vY = igi2_frame.tPos.vY + igi2_frame.tOrientation.tY.vZ * -6348.8 - igi2_frame.tOrientation.tY.vY * 204.8 + igi2_frame.tOrientation.tY.vX * 0.0;
  igi2_frame.tPos.vZ = igi2_frame.tPos.vZ + igi2_frame.Real64x3_Rotate_tTemp.vZ;
  Human_PopPosition(ptQTask, &igi2_frame.tPos);
  ptQTask[86].tQTaskChildren.ptHead = nullptr;
  ptQTask[86].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[86].tQTaskChildren.ptTail = nullptr;
  Real32x9_GetAngles(&igi2_frame.tOrientation, &igi2_frame.vAlpha, &igi2_frame.vBeta, &igi2_frame.vGamma);
  Human_PopOrientation(ptQTask, igi2_frame.vGamma);
  ptQTask[77].tQTaskRefList.ptTail = nullptr;
  ptQTask[77].ptParent = nullptr;
  HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.4000000059604645);
  ptPrev = ptQTask[33].ptNext[1].ptPrev;
  if ( ptPrev && (ptTail = ptPrev->tQTaskChildren.ptTail) != nullptr )
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    v6 = *(float *)&ptTail[21].ptNext;
    ptQTask[77].tQTaskChildren.ptMiddle = ptTail[21].ptNext;
    v7 = *(float *)&ptQTask[43].ptParent;
    if ( v7 < 0.0 )
      v7 = -v7;
    *(float *)&ptQTask[77].tQTaskChildren.ptMiddle = v7 * *(float *)&ptTail[21].ptParent * 3.0 + v6;
  }
  else
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    ptQTask[77].tQTaskChildren.ptMiddle = nullptr;
  }
  LOBYTE(ptQTask[76].tQTaskRefList.ptMiddle) = 1;
  HumanAnim_SetAnimationAndTimeFromState(ptQTask, 74, 0, 0.0);
  v8 = ptQTask[33].tQTaskChildren.ptTail;
  *(_DWORD *)&v8[11].eQTaskType = 0;
  v8[12].ptNext = nullptr;
  v8[12].ptPrev = nullptr;
  v8[12].tQTaskRefList.ptHead = nullptr;
  v8[12].tQTaskChildren.ptHead = nullptr;
  v8[12].tQTaskChildren.ptMiddle = nullptr;
  v8[12].tQTaskChildren.ptTail = nullptr;
  v8[12].tQTaskRefList.ptMiddle = nullptr;
  LOBYTE(ptQTask[33].tQTaskChildren.ptTail[12].tQTaskRefList.ptTail) = 1;
  LOBYTE(ptQTask[34].tQTaskChildren.ptMiddle) = 1;
  Human_AttachToTask(ptQTask, igi2_frame.ptAttachQTask, &igi2_frame.tPos, &igi2_frame.tOrientation);
  BYTE1(ptQTask[36].tQTaskChildren.ptTail) = 1;
  LOBYTE(ptQTask[33].tQTaskChildren.ptHead) = 0;
  ptState->pfState = HumanPlayer_RunStateActivateStationaryGun;
  if ( !CDAPFN0506_HumanPlayer_InitStateActivateStationaryGun.Version )
    ((void (*)(void))CDAPFN0506_HumanPlayer_InitStateActivateStationaryGun.FunctionAddress)();
}

// source: j/0/human/humanplayer.c:10110  [anchor-caller]
void __cdecl HumanPlayer_RunStateActivateStationaryGun(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s *pxObject; };
    struct { char igi2_o1[4]; struct real32x3_t ptUnitVector; };
    char igi2_extent[16];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QReference_s *ptHead; // eax
  enum bool v3; // ebp
  struct QReference_s *ptMiddle; // eax
  struct QReference_s *v5; // eax
  void (__cdecl *v6)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v7)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v8)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v9)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v10)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v11)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v12)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v14)(struct State_s *, struct QTask_s *); // eax

  ptHead = ptQTask[46].tQTaskRefList.ptHead;
  igi2_frame.pxObject = nullptr;
  if ( ptHead )
    igi2_frame.pxObject = (struct QTask_s *)ptHead->pxObject;
  v3 = false;
  HumanPlayer_MoveOnGround((struct HumanPlayer_t *)ptQTask, 0.0, 118.76579284667969, 0.0, 118.76579284667969);
  ActionMenuScreen_ptQTask[4].ptNext = (struct QTask_s *)10;
  if ( (*(_DWORD *)&ptQTask[30].eQTaskType & 0x1000) != 0 )
    v3 = *(float *)&ptQTask[13].tQTaskRefList.ptTail == 0.0;
  if ( (ptState->bSignal & 0x20000) != 0 )
    v3 = true;
  if ( HumanPlayer_IsActivateComputer(ptQTask) || v3 )
  {
    igi2_frame.ptUnitVector.vX = 0.0;
    igi2_frame.ptUnitVector.vY = 1.0;
    igi2_frame.ptUnitVector.vZ = 0.0;
    Human_MoveFree(ptQTask, -4096.0, &igi2_frame.ptUnitVector, v3);
    ptMiddle = ptQTask[44].tQTaskRefList.ptMiddle;
    if ( ptMiddle )
    {
      if ( ptMiddle->pxObject )
      {
        QReference_Delete(ptMiddle, &QTask_tQTaskRefPool);
        ptQTask[44].tQTaskRefList.ptMiddle = nullptr;
        HIBYTE(ptQTask[74].ptPrev) = 0;
      }
    }
  }
  if ( HumanPlayer_IsActivateComputer(ptQTask) )
    HumanPlayer_ActivateComputer(ptQTask);
  if ( v3 )
  {
    LOBYTE(ptQTask[33].tQTaskChildren.ptHead) = 1;
    LOBYTE(ptQTask[76].tQTaskRefList.ptMiddle) = 0;
    LOBYTE(ptQTask[33].tQTaskChildren.ptTail[12].tQTaskRefList.ptTail) = 0;
    LOBYTE(ptQTask[34].tQTaskChildren.ptMiddle) = 0;
    StationaryGun_Deactivate(igi2_frame.pxObject);
    v5 = ptQTask[46].tQTaskRefList.ptHead;
    LOBYTE(ptQTask[46].tQTaskRefList.ptMiddle) = 0;
    BYTE1(ptQTask[46].tQTaskRefList.ptMiddle) = 1;
    if ( v5 )
    {
      QReference_Delete(v5, &QTask_tQTaskRefPool);
      ptQTask[46].tQTaskRefList.ptHead = nullptr;
    }
    ptQTask[44].tQTaskRefList.ptTail = nullptr;
    ptQTask[48].ptNext = nullptr;
    *(_DWORD *)&ptQTask[47].eQTaskType = 1;
    BYTE1(ptQTask[36].tQTaskChildren.ptTail) = 0;
    if ( ptQTask[81].ptPrev == (struct QTask_s *)1 )
    {
      v12 = ptState->apfExitState[ptState->nState];
      if ( v12 )
        v12(ptState, ptQTask);
      apfState = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 23;
      v14 = apfState[23];
      ptState->pfState = v14;
      v14(ptState, ptQTask);
    }
    else if ( ptQTask[81].ptPrev == (struct QTask_s *)2 )
    {
      v9 = ptState->apfExitState[ptState->nState];
      if ( v9 )
        v9(ptState, ptQTask);
      v10 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 75;
      v11 = v10[75];
      ptState->pfState = v11;
      v11(ptState, ptQTask);
    }
    else
    {
      v6 = ptState->apfExitState[ptState->nState];
      if ( v6 )
        v6(ptState, ptQTask);
      v7 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 0;
      v8 = *v7;
      ptState->pfState = v8;
      v8(ptState, ptQTask);
    }
  }
}

// source: j/0/human/humanplayer.c:10205  [anchor-caller]
void __cdecl HumanPlayer_InitStateActivateGenericTBA(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s *ptActivateQTask; };
    struct { char igi2_o1[4]; float vGamma; };
    struct { char igi2_o2[8]; float vBeta; };
    struct { char igi2_o3[12]; __int64 vAlpha; };
    struct { char igi2_o4[20]; struct real64x3_t tPos; };
    struct { char igi2_o5[44]; struct real64x3_t Real64x3_Rotate_tTemp; };
    struct { char igi2_o6[68]; struct real32x9_t tOrientation; };
    char igi2_extent[108];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QReference_s *ptHead; // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptTail; // ecx
  double v5; // st7
  double v6; // st6
  struct QHashTable_s *v7; // edi
  unsigned int v8; // eax
  int v9; // eax
  int v10; // edi
  int v11; // eax
  struct AnimHeader_s *v12; // eax
  char *v13; // ecx
  struct QTask_s *v14; // edi
  struct QReference_s *ptMiddle; // eax
  struct QTask_s *v16; // eax
  struct QTask_s *v17; // eax

  ptHead = ptQTask[46].tQTaskRefList.ptHead;
  igi2_frame.ptActivateQTask = nullptr;
  if ( ptHead )
    igi2_frame.ptActivateQTask = (struct QTask_s *)ptHead->pxObject;
  ptQTask[81].ptPrev = *(struct QTask_s **)&ptQTask[32].eQTaskType;
  *(_DWORD *)&ptQTask[32].eQTaskType = 0;
  ptQTask[77].tQTaskRefList.ptTail = nullptr;
  ptQTask[77].ptParent = nullptr;
  HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.4000000059604645);
  ptPrev = ptQTask[33].ptNext[1].ptPrev;
  if ( ptPrev && (ptTail = ptPrev->tQTaskChildren.ptTail) != nullptr )
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    v5 = *(float *)&ptTail[21].ptNext;
    ptQTask[77].tQTaskChildren.ptMiddle = ptTail[21].ptNext;
    v6 = *(float *)&ptQTask[43].ptParent;
    if ( v6 < 0.0 )
      v6 = -v6;
    *(float *)&ptQTask[77].tQTaskChildren.ptMiddle = v6 * *(float *)&ptTail[21].ptParent * 3.0 + v5;
  }
  else
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    ptQTask[77].tQTaskChildren.ptMiddle = nullptr;
  }
  v7 = Hierarchy_ptHashTable;
  v8 = Hierarchy_ptHashTable->tPrivate.pfHashFunction(
         Hierarchy_ptHashTable->tPrivate.nHashTableSize,
         ptQTask[7].tQTaskRefList.ptTail);
  v9 = ((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Hierarchy_ptHashTable->tPrivate.pfFindElement)(v7, v8, (const void *)(ptQTask[7].tQTaskRefList.ptTail));
  v10 = *(_DWORD *)v9;
  v11 = (*(int (__cdecl **)(_DWORD, int))(*(_DWORD *)v9 + 12))(
          *(_DWORD *)(*(_DWORD *)v9 + 4),
          (int)&igi2_frame.ptActivateQTask[16].tQTaskChildren.ptHead + 1);
  v12 = (struct AnimHeader_s *)(*(int (__cdecl **)(int, int, const void *))(v10 + 28))(v10, v11, (const void *)((int)&igi2_frame.ptActivateQTask[16].tQTaskChildren.ptHead + 1));
  HumanAnim_SetAnimation(ptQTask, v12, 0, 0.0);
  ptQTask[35].tQTaskChildren.ptTail = (struct QTask_s *)HumanPlayer_GetAnimStateFromAnimName(ptQTask, v13);
  AnimController_Step(
    (struct AnimController_t *)ptQTask[34].tQTaskChildren.ptTail,
    (int)ptQTask[34].tQTaskChildren.ptTail[1].tQTaskRefList.ptMiddle
  + (unsigned int)ptQTask[34].tQTaskChildren.ptTail[1].tQTaskRefList.ptTail);
  qmemcpy(&igi2_frame.tOrientation, &igi2_frame.ptActivateQTask[3].ptPrev, sizeof(igi2_frame.tOrientation));
  GameFunctions_GetMagicVertex(&igi2_frame.tPos, igi2_frame.ptActivateQTask, 1);
  igi2_frame.Real64x3_Rotate_tTemp.vZ = (igi2_frame.tOrientation.tZ.vZ + igi2_frame.tOrientation.tZ.vX) * 0.0 + igi2_frame.tOrientation.tZ.vY * 3481.6;
  igi2_frame.tPos.vX = igi2_frame.tPos.vX + (igi2_frame.tOrientation.tX.vZ + igi2_frame.tOrientation.tX.vX) * 0.0 + igi2_frame.tOrientation.tX.vY * 3481.6;
  igi2_frame.tPos.vY = igi2_frame.tPos.vY + (igi2_frame.tOrientation.tY.vZ + igi2_frame.tOrientation.tY.vX) * 0.0 + igi2_frame.tOrientation.tY.vY * 3481.6;
  v14 = ptQTask;
  igi2_frame.tPos.vZ = igi2_frame.tPos.vZ + igi2_frame.Real64x3_Rotate_tTemp.vZ;
  Human_PopPosition(ptQTask, &igi2_frame.tPos);
  ptQTask[86].tQTaskChildren.ptHead = nullptr;
  ptQTask[86].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[86].tQTaskChildren.ptTail = nullptr;
  Human_SnapToGround(ptQTask);
  ptMiddle = ptQTask[44].tQTaskRefList.ptMiddle;
  if ( ptMiddle && ptMiddle->pxObject )
  {
    QReference_Delete(ptMiddle, &QTask_tQTaskRefPool);
    ptQTask[44].tQTaskRefList.ptMiddle = nullptr;
    HIBYTE(ptQTask[74].ptPrev) = 0;
  }
  Real32x9_GetAngles(&igi2_frame.tOrientation, (float *)&igi2_frame.vAlpha, &igi2_frame.vBeta, &igi2_frame.vGamma);
  igi2_frame.vGamma = igi2_frame.vGamma + 3.1415927410125732;
  Human_PopOrientation(ptQTask, igi2_frame.vGamma);
  LOBYTE(ptQTask[76].tQTaskRefList.ptMiddle) = 1;
  igi2_frame.vAlpha = (__int64)(*(float *)&igi2_frame.ptActivateQTask[17].eQTaskType * 30.0);
  *(_DWORD *)&ptQTask[77].eQTaskType = igi2_frame.vAlpha;
  v16 = ptQTask[33].tQTaskChildren.ptTail;
  ptQTask[78].ptNext = nullptr;
  ptQTask[33].tQTaskRefList.ptHead = (struct QReference_s *)3;
  LOBYTE(ptQTask[78].ptPrev) = 1;
  BYTE1(ptQTask[36].tQTaskChildren.ptTail) = 1;
  *(_DWORD *)&v16[11].eQTaskType = 0;
  v16[12].ptNext = nullptr;
  v16[12].ptPrev = nullptr;
  v16[12].tQTaskRefList.ptHead = nullptr;
  v16[12].tQTaskChildren.ptHead = nullptr;
  v16[12].tQTaskChildren.ptMiddle = nullptr;
  v16[12].tQTaskChildren.ptTail = nullptr;
  v16[12].tQTaskRefList.ptMiddle = nullptr;
  LOBYTE(ptQTask[33].tQTaskChildren.ptTail[12].tQTaskRefList.ptTail) = 1;
  LOBYTE(ptQTask[34].tQTaskChildren.ptMiddle) = 1;
  QTask_DeleteQTaskAndQTaskRefSafe(&ptQTask[85].tQTaskRefList.ptMiddle);
  v17 = SoundSys_NewSoundFn(ptQTask[33].tQTaskChildren.ptTail, (char *)&igi2_frame.ptActivateQTask[17].ptNext + 1);
  ptQTask[85].tQTaskRefList.ptMiddle = QTask_NewQTaskRef(v17);
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    HumanPlayer_SendActivateMessage(igi2_frame.ptActivateQTask, 10, 0);
    v14 = ptQTask;
  }
  v14[84].tQTaskChildren.ptMiddle = (struct QTask_s *)20;
  ptState->pfState = HumanPlayer_RunStateActivateGenericTBA;
  if ( !CDAPFN0506_HumanPlayer_InitStateActivateGenericTBA.Version )
    ((void (*)(void))CDAPFN0506_HumanPlayer_InitStateActivateGenericTBA.FunctionAddress)();
}

// source: j/0/human/humanplayer.c:10326  [anchor-strings]
void __cdecl HumanPlayer_InitStateActivateC4BombTBA(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s *ptActivateQTask; };
    struct { char igi2_o1[4]; float pvBeta; };
    struct { char igi2_o2[8]; float pvAlpha; };
    struct { char igi2_o3[12]; float ptSource; };
    struct { char igi2_o4[16]; struct real64x3_t ptSource_4; };
    struct { char igi2_o5[48]; double ptSource_36; };
    struct { char igi2_o6[64]; struct real32x9_t v22; };
    char igi2_extent[104];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v2; // ebx
  struct QReference_s *ptHead; // eax
  struct QTask_s *v4; // esi
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptTail; // ecx
  double v7; // st7
  double v8; // st6
  struct QTask_s *v9; // eax
  struct QReference_s *ptMiddle; // ecx
  double v11; // st7
  struct QReference_s *v12; // ecx
  struct QReference_s *v13; // eax
  struct QTask_s *v14; // eax
  struct QTask_s *v15; // eax

  v2 = ptQTask;
  ptHead = ptQTask[46].tQTaskRefList.ptHead;
  v4 = nullptr;
  igi2_frame.ptActivateQTask = nullptr;
  if ( ptHead )
  {
    igi2_frame.ptActivateQTask = (struct QTask_s *)ptHead->pxObject;
    v4 = igi2_frame.ptActivateQTask;
  }
  ptPrev = ptQTask[33].ptNext[1].ptPrev;
  if ( ptPrev && (ptTail = ptPrev->tQTaskChildren.ptTail) != nullptr )
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    v7 = *(float *)&ptTail[21].ptNext;
    ptQTask[77].tQTaskChildren.ptMiddle = ptTail[21].ptNext;
    v8 = *(float *)&ptQTask[43].ptParent;
    if ( v8 < 0.0 )
      v8 = -v8;
    *(float *)&ptQTask[77].tQTaskChildren.ptMiddle = v8 * *(float *)&ptTail[21].ptParent * 3.0 + v7;
  }
  else
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    ptQTask[77].tQTaskChildren.ptMiddle = nullptr;
  }
  ptQTask[81].ptPrev = *(struct QTask_s **)&ptQTask[32].eQTaskType;
  *(_DWORD *)&ptQTask[32].eQTaskType = 0;
  if ( v4[1].ptNext && !v4[10].tQTaskRefList.ptHead && !v4[10].tQTaskChildren.ptTail )
  {
    *(_DWORD *)&ptQTask[32].eQTaskType = 0;
    ptQTask[77].tQTaskRefList.ptTail = nullptr;
    ptQTask[77].ptParent = nullptr;
    HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.4000000059604645);
    HumanAnim_SetAnimationAndTimeFromState(ptQTask, 107, 0, 0.0);
    v4 = igi2_frame.ptActivateQTask;
    v2 = ptQTask;
  }
  AnimController_Step(
    (struct AnimController_t *)v2[34].tQTaskChildren.ptTail,
    (int)v2[34].tQTaskChildren.ptTail[1].tQTaskRefList.ptMiddle
  + (unsigned int)v2[34].tQTaskChildren.ptTail[1].tQTaskRefList.ptTail);
  v9 = igi2_frame.ptActivateQTask;
  qmemcpy(&igi2_frame.ptSource_4, &v4[6], sizeof(igi2_frame.ptSource_4));
  qmemcpy(&igi2_frame.v22, &igi2_frame.ptActivateQTask[6].tQTaskRefList.ptMiddle, sizeof(igi2_frame.v22));
  ptMiddle = igi2_frame.ptActivateQTask[10].tQTaskRefList.ptMiddle;
  igi2_frame.ptActivateQTask[10].ptNext = (struct QTask_s *)1;
  if ( ptMiddle )
  {
    if ( !igi2_frame.ptActivateQTask[1].ptNext
      || igi2_frame.ptActivateQTask[10].tQTaskRefList.ptHead
      || igi2_frame.ptActivateQTask[10].tQTaskChildren.ptTail )
    {
      v11 = 3481.6;
    }
    else
    {
      v11 = -3481.6;
    }
    v12 = v2[1].tQTaskRefList.ptHead;
    LODWORD(igi2_frame.ptSource_4.vZ) = v2[1].tQTaskChildren.ptTail;
    HIDWORD(igi2_frame.ptSource_4.vZ) = v12;
    igi2_frame.ptSource_36 = (igi2_frame.v22.tY.vZ + igi2_frame.v22.tY.vX) * 0.0 + igi2_frame.v22.tY.vY * v11;
    igi2_frame.ptSource_4.vX = igi2_frame.ptSource_4.vX + (igi2_frame.v22.tX.vZ + igi2_frame.v22.tX.vX) * 0.0 + igi2_frame.v22.tX.vY * v11;
    igi2_frame.ptSource_4.vY = igi2_frame.ptSource_4.vY + igi2_frame.ptSource_36;
    Human_PopPosition(v2, &igi2_frame.ptSource_4);
    v2[86].tQTaskChildren.ptHead = nullptr;
    v2[86].tQTaskChildren.ptMiddle = nullptr;
    v2[86].tQTaskChildren.ptTail = nullptr;
    Human_SnapToGround(v2);
    v13 = ptQTask[44].tQTaskRefList.ptMiddle;
    if ( v13 && v13->pxObject )
    {
      QReference_Delete(v13, &QTask_tQTaskRefPool);
      ptQTask[44].tQTaskRefList.ptMiddle = nullptr;
      HIBYTE(ptQTask[74].ptPrev) = 0;
    }
    Real32x9_GetAngles(&igi2_frame.v22, &igi2_frame.ptSource, &igi2_frame.pvAlpha, &igi2_frame.pvBeta);
    if ( !igi2_frame.ptActivateQTask[1].ptNext
      || igi2_frame.ptActivateQTask[10].tQTaskRefList.ptHead
      || igi2_frame.ptActivateQTask[10].tQTaskChildren.ptTail )
    {
      igi2_frame.pvBeta = igi2_frame.pvBeta + 3.1415927410125732;
    }
    Human_PopOrientation(ptQTask, igi2_frame.pvBeta);
    v2 = ptQTask;
    v9 = igi2_frame.ptActivateQTask;
  }
  if ( !v9[1].ptNext || v9[10].tQTaskRefList.ptHead || v9[10].tQTaskChildren.ptTail )
    *(_DWORD *)&v2[77].eQTaskType = 142;
  else
    *(_DWORD *)&v2[77].eQTaskType = 600;
  v2[78].ptNext = nullptr;
  if ( v9[1].ptNext && !v9[10].tQTaskRefList.ptHead && !v9[10].tQTaskChildren.ptTail )
    v2[33].tQTaskRefList.ptHead = (struct QReference_s *)3;
  v14 = v2[33].tQTaskChildren.ptTail;
  LOBYTE(v2[78].ptPrev) = 1;
  BYTE1(v2[36].tQTaskChildren.ptTail) = 1;
  *(_DWORD *)&v14[11].eQTaskType = 0;
  v14[12].ptNext = nullptr;
  v14[12].ptPrev = nullptr;
  v14[12].tQTaskRefList.ptHead = nullptr;
  v14[12].tQTaskChildren.ptHead = nullptr;
  v14[12].tQTaskChildren.ptMiddle = nullptr;
  v14[12].tQTaskChildren.ptTail = nullptr;
  v14[12].tQTaskRefList.ptMiddle = nullptr;
  LOBYTE(v2[33].tQTaskChildren.ptTail[12].tQTaskRefList.ptTail) = 1;
  LOBYTE(v2[34].tQTaskChildren.ptMiddle) = 1;
  QTask_DeleteQTaskAndQTaskRefSafe(&v2[85].tQTaskRefList.ptMiddle);
  if ( !igi2_frame.ptActivateQTask[1].ptNext
    || igi2_frame.ptActivateQTask[10].tQTaskRefList.ptHead
    || igi2_frame.ptActivateQTask[10].tQTaskChildren.ptTail )
  {
    v15 = SoundSys_NewSoundFn(v2[33].tQTaskChildren.ptTail, "tba_placec4");
  }
  else
  {
    v15 = SoundSys_NewSoundFn(v2[33].tQTaskChildren.ptTail, "tba_c4defuse");
  }
  v2[85].tQTaskRefList.ptMiddle = QTask_NewQTaskRef(v15);
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
    HumanPlayer_SendActivateMessage(igi2_frame.ptActivateQTask, 11, 0);
  v2[84].tQTaskChildren.ptMiddle = (struct QTask_s *)20;
  ptState->pfState = HumanPlayer_RunStateActivateC4BombTBA;
  if ( !CDAPFN0506_HumanPlayer_InitStateActivateC4BombTBA.Version )
    ((void (*)(void))CDAPFN0506_HumanPlayer_InitStateActivateC4BombTBA.FunctionAddress)();
}

// source: j/0/human/humanplayer.c:10464  [anchor-caller]
void __cdecl HumanPlayer_RunStateActivateC4BombTBA(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { int p_ptMiddle; };
    struct { char igi2_o1[4]; int v51; };
    struct { char igi2_o2[27]; char v52; };
    struct { char igi2_o3[28]; struct QTask_s *ptActivateQTask; };
    struct { char igi2_o4[32]; int eSource[3]; };
    struct { char igi2_o5[44]; struct QReference_s *v55; };
    struct { char igi2_o6[48]; struct QTask_s *v56; };
    struct { char igi2_o7[52]; int v57; };
    struct { char igi2_o8[56]; int v58; };
    struct { char igi2_o9[60]; struct QTask_s *v59; };
    struct { char igi2_o10[68]; struct AnimHeader_s *ptAnim; };
    struct { char igi2_o11[72]; float v61; };
    struct { char igi2_o12[76]; unsigned int v62; };
    struct { char igi2_o13[80]; struct NetManagerGameMessage_s ptGameMessage; };
    struct { char igi2_o14[88]; struct QTask_s *v64; };
    struct { char igi2_o15[92]; int LevelQTaskIDFromQTask; };
    struct { char igi2_o16[96]; int v66; };
    struct { char igi2_o17[100]; _BYTE v67[36]; };
    struct { char igi2_o18[136]; double v68[3]; };
    struct { char igi2_o19[160]; struct real32x9_t ptDest; };
    struct { char igi2_o20[200]; struct QReference_s *v70; };
    struct { char igi2_o21[204]; struct QReference_s *v71; };
    struct { char igi2_o22[208]; struct QTask_s *v72; };
    struct { char igi2_o23[212]; int v73; };
    struct { char igi2_o24[228]; float v74; };
    char igi2_extent[236];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QReference_s *ptHead; // eax
  struct QTask_s *pxObject; // edi
  struct QTask_s *ptMiddle; // eax
  double v5; // st7
  struct State_s *v6; // ebx
  unsigned int bSignal; // eax
  struct QTask_s *ptNext; // ecx
  struct QTask_s *v9; // eax
  struct QTask_s *v10; // eax
  struct QTask_s *v11; // ebx
  struct QTask_s **p_ptPrev; // eax
  char v13; // cl
  struct QReference_s *v14; // edx
  struct QTask_s *ptParent; // eax
  int v16; // ecx
  struct QTask_s *v17; // esi
  struct WeaponType_s *NextEnabledWeaponTypeFromCategory; // eax
  char *zWeaponScriptID; // edi
  int v20; // eax
  int v21; // esi
  struct QReference_s *v22; // edx
  struct QTask_s *v23; // eax
  struct QTask_s *v24; // ecx
  struct QTask_s *v25; // ecx
  struct QTask_s *v26; // eax
  void (__cdecl *v27)(struct QTask_s *, struct QReference_s **); // ecx
  struct QTask_s *v28; // eax
  struct QReference_s *v29; // ecx
  struct QReference_s *v30; // edx
  struct QTask_s *v31; // eax
  struct QTask_s *v32; // ecx
  struct QTask_s *v33; // ecx
  struct QTask_s *v34; // eax
  void (__cdecl *pfHandler)(struct QTask_s *, struct QReference_s **); // ecx
  struct QTask_s *v36; // eax
  struct QReference_s *v37; // eax
  void (__cdecl *v38)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v40)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v41)(struct QReference_s **, struct QTask_s *); // eax
  struct QReference_s *ptTail; // eax
  struct QTask_s *ptPrev; // eax
  void (__cdecl *v44)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v45)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v46)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v47)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v48)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v49)(struct State_s *, struct QTask_s *); // ecx

  ptHead = ptQTask[46].tQTaskRefList.ptHead;
  pxObject = nullptr;
  igi2_frame.ptActivateQTask = nullptr;
  if ( ptHead )
  {
    pxObject = (struct QTask_s *)ptHead->pxObject;
    igi2_frame.ptActivateQTask = pxObject;
  }
  igi2_frame.v52 = 0;
  HumanPlayer_MoveOnGround((struct HumanPlayer_t *)ptQTask, 0.0, 118.76579284667969, 0.0, 118.76579284667969);
  ActionMenuScreen_ptQTask[4].ptNext = (struct QTask_s *)10;
  if ( !pxObject[1].ptNext || pxObject[10].tQTaskRefList.ptHead || pxObject[10].tQTaskChildren.ptTail )
  {
    if ( *(float *)&ptQTask[20].ptNext != 0.0 )
      goto LABEL_13;
    v5 = *(float *)&ptQTask[19].tQTaskRefList.ptTail;
  }
  else
  {
    ptMiddle = ptQTask[84].tQTaskChildren.ptMiddle;
    if ( ptMiddle )
    {
      ptQTask[84].tQTaskChildren.ptMiddle = (struct QTask_s *)((char *)ptMiddle - 1);
      goto LABEL_13;
    }
    v5 = *(float *)&ptQTask[20].ptNext;
  }
  if ( v5 == 0.0 )
    igi2_frame.v52 = 1;
LABEL_13:
  v6 = ptState;
  bSignal = ptState->bSignal;
  if ( (bSignal & 0x20000) != 0 )
    igi2_frame.v52 = 1;
  if ( (bSignal & 0x10000) != 0 )
    igi2_frame.v52 = 1;
  ptNext = ptQTask[78].ptNext;
  v9 = *(struct QTask_s **)&ptQTask[77].eQTaskType;
  if ( (int)ptNext < (int)v9 )
    ptQTask[78].ptNext = (struct QTask_s *)((char *)&ptNext->ptNext + 1);
  igi2_frame.v62 = ptState->bSignal;
  if ( ptQTask[78].ptNext == v9 || igi2_frame.v52 )
  {
    if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
      HumanPlayer_SendActivateMessage(pxObject, 0, 0);
    if ( igi2_frame.v52 )
    {
      if ( pxObject[1].ptNext )
      {
        if ( !pxObject[10].tQTaskRefList.ptHead && !pxObject[10].tQTaskChildren.ptTail )
          HumanPlayer_SendActivateMessage(pxObject, 11, 1);
        ptQTask[77].ptParent = (struct QTask_s *)1;
      }
      else
      {
        pxObject[10].ptNext = nullptr;
        ptQTask[77].ptParent = (struct QTask_s *)1;
      }
      goto LABEL_67;
    }
    if ( Game_eGameMode != GAME_GAMEMODE_MULTIPLAYER )
    {
LABEL_67:
      LOBYTE(ptQTask[33].tQTaskChildren.ptTail[12].tQTaskRefList.ptTail) = 0;
      v37 = ptQTask[46].tQTaskRefList.ptHead;
      LOBYTE(ptQTask[34].tQTaskChildren.ptMiddle) = 0;
      LOBYTE(ptQTask[46].tQTaskRefList.ptMiddle) = 0;
      BYTE1(ptQTask[46].tQTaskRefList.ptMiddle) = 1;
      if ( v37 )
      {
        QReference_Delete(v37, &QTask_tQTaskRefPool);
        ptQTask[46].tQTaskRefList.ptHead = nullptr;
      }
      if ( pxObject[1].ptNext && !pxObject[10].tQTaskRefList.ptHead && !pxObject[10].tQTaskChildren.ptTail )
        ptQTask[33].tQTaskRefList.ptHead = (struct QReference_s *)1;
      LOBYTE(ptQTask[78].ptPrev) = 0;
      BYTE1(ptQTask[36].tQTaskChildren.ptTail) = 0;
      QTask_DeleteQTaskAndQTaskRefSafe(&ptQTask[85].tQTaskRefList.ptMiddle);
      QTask_DeleteQTaskAndQTaskRefSafe(&ptQTask[85].tQTaskRefList.ptHead);
      if ( (igi2_frame.v62 & 0x10000) != 0 )
      {
        v38 = v6->apfExitState[v6->nState];
        if ( v38 )
          v38(v6, ptQTask);
        apfState = v6->apfState;
        v6->nPreviousState = v6->nState;
        v6->nState = 54;
        v40 = apfState[54];
      }
      else
      {
        v41 = *((void (__cdecl **)(struct QReference_s **, struct QTask_s *))&ptQTask[74].ptParent->ptNext
              + (int)ptQTask[75].ptPrev);
        if ( v41 )
          v41(&ptQTask[74].tQTaskRefList.ptMiddle, ptQTask);
        ptTail = ptQTask[74].tQTaskRefList.ptTail;
        ptQTask[75].ptNext = ptQTask[75].ptPrev;
        ptQTask[75].ptPrev = (struct QTask_s *)1;
        ptPrev = (struct QTask_s *)ptTail->ptPrev;
        igi2_frame.v51 = (int)ptQTask;
        igi2_frame.p_ptMiddle = (int)&ptQTask[74].tQTaskRefList.ptMiddle;
        ptQTask[75].tQTaskChildren.ptHead = ptPrev;
        ((void (__cdecl *)(int, int))ptPrev)(igi2_frame.p_ptMiddle, igi2_frame.v51);
        if ( ptQTask[81].ptPrev == (struct QTask_s *)1 )
        {
          v48 = v6->apfExitState[v6->nState];
          if ( v48 )
            v48(v6, ptQTask);
          v49 = v6->apfState;
          v6->nPreviousState = v6->nState;
          v6->nState = 23;
          v40 = v49[23];
        }
        else if ( ptQTask[81].ptPrev == (struct QTask_s *)2 )
        {
          v46 = v6->apfExitState[v6->nState];
          if ( v46 )
            v46(v6, ptQTask);
          v47 = v6->apfState;
          v6->nPreviousState = v6->nState;
          v6->nState = 75;
          v40 = v47[75];
        }
        else
        {
          v44 = v6->apfExitState[v6->nState];
          if ( v44 )
            v44(v6, ptQTask);
          v45 = v6->apfState;
          v6->nPreviousState = v6->nState;
          v6->nState = 0;
          v40 = *v45;
        }
      }
      igi2_frame.v51 = (int)ptQTask;
      igi2_frame.p_ptMiddle = (int)v6;
      v6->pfState = v40;
      v40((struct State_s *)igi2_frame.p_ptMiddle, (struct QTask_s *)igi2_frame.v51);
      return;
    }
    v10 = Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle;
    igi2_frame.ptGameMessage.nLocalTime = Flow_ptFlow->nTicks;
    igi2_frame.ptGameMessage.eGameMessage = 1112493378;
    igi2_frame.eSource[0] = (int)v10;
    igi2_frame.v64 = v10;
    igi2_frame.LevelQTaskIDFromQTask = Level_GetLevelQTaskIDFromQTask(pxObject);
    if ( !pxObject[1].ptNext || pxObject[10].tQTaskRefList.ptHead || pxObject[10].tQTaskChildren.ptTail )
    {
      v11 = igi2_frame.ptActivateQTask;
      igi2_frame.v66 = 0;
      qmemcpy(igi2_frame.v68, &igi2_frame.ptActivateQTask[6], sizeof(igi2_frame.v68));
      qmemcpy(&igi2_frame.ptDest, &igi2_frame.ptActivateQTask[6].tQTaskRefList.ptMiddle, sizeof(igi2_frame.ptDest));
      Real32x9_RotateGamma(&igi2_frame.ptDest, &igi2_frame.ptDest, 3.1415927410125732);
      p_ptPrev = &igi2_frame.ptActivateQTask[5].ptPrev;
      igi2_frame.v74 = igi2_frame.ptDest.tZ.vY * -1228.800048828125;
      igi2_frame.v68[0] = igi2_frame.ptDest.tX.vY * -1228.800048828125 + igi2_frame.v68[0];
      igi2_frame.v68[1] = igi2_frame.ptDest.tY.vY * -1228.800048828125 + igi2_frame.v68[1];
      igi2_frame.v68[2] = igi2_frame.v74 + igi2_frame.v68[2];
      do
      {
        v13 = *(_BYTE *)p_ptPrev;
        *((_BYTE *)p_ptPrev + ((char *)(igi2_frame.v67) - (char *)(&v11[5].ptPrev))) = *(_BYTE *)p_ptPrev;
        p_ptPrev = (struct QTask_s **)((char *)p_ptPrev + 1);
      }
      while ( v13 );
      v14 = v11[7].tQTaskRefList.ptTail;
      ptParent = v11[7].ptParent;
      igi2_frame.v70 = v11[7].tQTaskRefList.ptMiddle;
      v16 = *(_DWORD *)&v11[7].eQTaskType;
      igi2_frame.v71 = v14;
      igi2_frame.v72 = ptParent;
      igi2_frame.v73 = v16;
    }
    else
    {
      igi2_frame.v66 = 1;
    }
    NetManager_SendGameMessage(0, igi2_frame.eSource[0], NETWORKQUEUE_GUARANTEED, &igi2_frame.ptGameMessage, 0x88u);
    if ( !igi2_frame.ptActivateQTask[1].ptNext
      || igi2_frame.ptActivateQTask[10].tQTaskRefList.ptHead
      || igi2_frame.ptActivateQTask[10].tQTaskChildren.ptTail )
    {
      igi2_frame.v51 = 1;
      igi2_frame.p_ptMiddle = 11;
    }
    else
    {
      igi2_frame.v51 = 0;
      igi2_frame.p_ptMiddle = 0;
    }
    HumanPlayer_SendActivateMessage(igi2_frame.ptActivateQTask, igi2_frame.p_ptMiddle, igi2_frame.v51);
    Weapon_DisableWeaponType(ptQTask[33].ptNext, "WEAPON_ID_C4BOMB", true);
    v17 = ptQTask[33].ptNext;
    NextEnabledWeaponTypeFromCategory = Weapon_GetNextEnabledWeaponTypeFromCategory(
                                          v17,
                                          WEAPONCATEGORY_PRIMARY,
                                          nullptr);
    if ( !NextEnabledWeaponTypeFromCategory )
    {
      NextEnabledWeaponTypeFromCategory = Weapon_GetNextEnabledWeaponTypeFromCategory(
                                            v17,
                                            WEAPONCATEGORY_SIDEARM,
                                            nullptr);
      if ( !NextEnabledWeaponTypeFromCategory )
        NextEnabledWeaponTypeFromCategory = Weapon_GetNextEnabledWeaponTypeFromCategory(
                                              v17,
                                              WEAPONCATEGORY_KNIFE,
                                              nullptr);
    }
    zWeaponScriptID = NextEnabledWeaponTypeFromCategory->zWeaponScriptID;
    Weapon_Activate(v17, NextEnabledWeaponTypeFromCategory->zWeaponScriptID, true);
    Weapon_Activate(ptQTask[33].ptNext, zWeaponScriptID, false);
    v20 = *(_DWORD *)&ptQTask[32].eQTaskType;
    ptQTask[77].tQTaskRefList.ptTail = (struct QReference_s *)12;
    ptQTask[87].tQTaskChildren.ptMiddle = (struct QTask_s *)1;
    v21 = v20 == 2 ? 90 : 87;
    if ( v20 == 2 )
    {
      HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
      if ( v21 != 90 )
      {
        HumanAnim_SetAnimationAndTimeFromState(ptQTask, v21, 0, 0.0);
        goto LABEL_66;
      }
      v30 = ptQTask[7].tQTaskRefList.ptTail;
      igi2_frame.v59 = ptQTask[77].ptPrev;
      v31 = ptQTask[33].ptNext;
      ptQTask[35].tQTaskRefList.ptHead = (struct QReference_s *)90;
      igi2_frame.v55 = v30;
      igi2_frame.v58 = 26;
      igi2_frame.v56 = v31;
      igi2_frame.v57 = 0;
      igi2_frame.ptAnim = nullptr;
      v32 = v31[1].ptPrev;
      if ( v32 )
        v33 = v32->tQTaskChildren.ptTail;
      else
        v33 = nullptr;
      v34 = v31[1].ptPrev;
      pfHandler = (void (__cdecl *)(struct QTask_s *, struct QReference_s **))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][v33->eQTaskType].pfHandler;
      if ( v34 )
        v36 = v34->tQTaskChildren.ptTail;
      else
        v36 = nullptr;
      pfHandler(v36, &igi2_frame.v55);
      igi2_frame.v51 = 0;
      if ( igi2_frame.ptAnim )
        goto LABEL_54;
    }
    else
    {
      v22 = ptQTask[7].tQTaskRefList.ptTail;
      igi2_frame.v59 = ptQTask[77].ptPrev;
      v23 = ptQTask[33].ptNext;
      ptQTask[35].tQTaskRefList.ptHead = (struct QReference_s *)87;
      igi2_frame.v55 = v22;
      igi2_frame.v58 = 15;
      igi2_frame.v56 = v23;
      igi2_frame.v57 = 0;
      igi2_frame.ptAnim = nullptr;
      v24 = v23[1].ptPrev;
      if ( v24 )
        v25 = v24->tQTaskChildren.ptTail;
      else
        v25 = nullptr;
      v26 = v23[1].ptPrev;
      v27 = (void (__cdecl *)(struct QTask_s *, struct QReference_s **))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][v25->eQTaskType].pfHandler;
      if ( v26 )
        v28 = v26->tQTaskChildren.ptTail;
      else
        v28 = nullptr;
      v27(v28, &igi2_frame.v55);
      igi2_frame.v51 = 0;
      if ( igi2_frame.ptAnim )
      {
LABEL_54:
        HumanAnim_SetUpperBodyAnimationFromHeader(ptQTask, igi2_frame.ptAnim, igi2_frame.ptAnim->nTotalTime, *(float *)&igi2_frame.v51);
        v29 = ptQTask[34].tQTaskRefList.ptHead;
        *(_QWORD *)igi2_frame.eSource = (__int64)(-igi2_frame.v61 * (double)AnimController_nTicksPerFrame);
        v29[5].pxObject = (void *)igi2_frame.eSource[0];
LABEL_66:
        HumanPlayer_SetWeaponTypeAnim(ptQTask, WEAPONTYPE_GETANIMTYPE_1STACTIVATE, 0, true);
        v6 = ptState;
        pxObject = igi2_frame.ptActivateQTask;
        goto LABEL_67;
      }
    }
    HumanAnim_ClearUpperBodyAnimation(ptQTask, *(float *)&igi2_frame.v51);
    goto LABEL_66;
  }
}

// source: j/0/human/humanplayer.c:10691  [anchor-caller]
void __cdecl HumanPlayer_InitStateActivatePlaceExplosiveTBA(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s *ptActivateQTask; };
    struct { char igi2_o1[4]; struct real32x3_t tDir; };
    struct { char igi2_o2[16]; float vGamma; };
    struct { char igi2_o3[20]; struct real64x3_t tDirection; };
    struct { char igi2_o4[44]; struct real64x3_t tPos; };
    struct { char igi2_o5[68]; __int64 vBeta; };
    struct { char igi2_o6[76]; struct real64x3_t tStartPos; };
    struct { char igi2_o7[100]; struct ObjectCollisionEvaluateContext_t tObjectCollisionEvaluateContext; };
    struct { char igi2_o8[108]; struct real64x3_t tEndPos; };
    struct { char igi2_o9[132]; struct QIntersection_s tQObjIntersection; };
    char igi2_extent[252];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QReference_s *ptHead; // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptTail; // ecx
  double v5; // st7
  double v6; // st6
  struct QHashTable_s *v7; // ebx
  unsigned int v8; // eax
  int v9; // eax
  int v10; // ebx
  int v11; // eax
  struct AnimHeader_s *v12; // eax
  long double v13; // st7
  unsigned int v14; // eax
  struct QReference_s *v15; // eax
  char *pxObject; // ebx
  float v17; // esi
  struct QTask_s *v18; // edi
  long double v19; // st7
  struct QReference_s *ptMiddle; // eax
  struct QTask_s *v21; // eax
  struct QTask_s *v22; // eax

  ptHead = ptQTask[46].tQTaskRefList.ptHead;
  igi2_frame.ptActivateQTask = nullptr;
  if ( ptHead )
    igi2_frame.ptActivateQTask = (struct QTask_s *)ptHead->pxObject;
  ptQTask[81].ptPrev = *(struct QTask_s **)&ptQTask[32].eQTaskType;
  *(_DWORD *)&ptQTask[32].eQTaskType = 0;
  ptQTask[77].tQTaskRefList.ptTail = nullptr;
  ptQTask[77].ptParent = nullptr;
  HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.4000000059604645);
  ptPrev = ptQTask[33].ptNext[1].ptPrev;
  if ( ptPrev && (ptTail = ptPrev->tQTaskChildren.ptTail) != nullptr )
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    v5 = *(float *)&ptTail[21].ptNext;
    ptQTask[77].tQTaskChildren.ptMiddle = ptTail[21].ptNext;
    v6 = *(float *)&ptQTask[43].ptParent;
    if ( v6 < 0.0 )
      v6 = -v6;
    *(float *)&ptQTask[77].tQTaskChildren.ptMiddle = v6 * *(float *)&ptTail[21].ptParent * 3.0 + v5;
  }
  else
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    ptQTask[77].tQTaskChildren.ptMiddle = nullptr;
  }
  v7 = Hierarchy_ptHashTable;
  v8 = Hierarchy_ptHashTable->tPrivate.pfHashFunction(
         Hierarchy_ptHashTable->tPrivate.nHashTableSize,
         ptQTask[7].tQTaskRefList.ptTail);
  v9 = ((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Hierarchy_ptHashTable->tPrivate.pfFindElement)(v7, v8, (const void *)(ptQTask[7].tQTaskRefList.ptTail));
  v10 = *(_DWORD *)v9;
  v11 = (*(int (__cdecl **)(_DWORD, int))(*(_DWORD *)v9 + 12))(
          *(_DWORD *)(*(_DWORD *)v9 + 4),
          (int)&igi2_frame.ptActivateQTask[16].tQTaskChildren.ptHead + 1);
  v12 = (struct AnimHeader_s *)(*(int (__cdecl **)(int, int, const void *))(v10 + 28))(v10, v11, (const void *)((int)&igi2_frame.ptActivateQTask[16].tQTaskChildren.ptHead + 1));
  HumanAnim_SetAnimation(ptQTask, v12, 0, 0.0);
  AnimController_Step(
    (struct AnimController_t *)ptQTask[34].tQTaskChildren.ptTail,
    (int)ptQTask[34].tQTaskChildren.ptTail[1].tQTaskRefList.ptMiddle
  + (unsigned int)ptQTask[34].tQTaskChildren.ptTail[1].tQTaskRefList.ptTail);
  GameFunctions_GetMagicVertex(&igi2_frame.tPos, igi2_frame.ptActivateQTask, 1);
  igi2_frame.tObjectCollisionEvaluateContext.tCollisionEvaluateContext.ptQTask = ptQTask;
  qmemcpy(&igi2_frame.tStartPos, &ptQTask[33].tQTaskChildren.ptTail[10].tQTaskChildren, sizeof(igi2_frame.tStartPos));
  igi2_frame.tDirection.vX = igi2_frame.tPos.vX - igi2_frame.tStartPos.vX;
  igi2_frame.tDirection.vY = igi2_frame.tPos.vY - igi2_frame.tStartPos.vY;
  igi2_frame.tDirection.vZ = igi2_frame.tPos.vZ - igi2_frame.tStartPos.vZ;
  qmemcpy(&igi2_frame.tEndPos, &igi2_frame.tPos, sizeof(igi2_frame.tEndPos));
  igi2_frame.tDir.vX = igi2_frame.tDirection.vX;
  igi2_frame.tDir.vY = igi2_frame.tDirection.vY;
  igi2_frame.tDir.vZ = igi2_frame.tDirection.vZ;
  qmemcpy(&igi2_frame.tPos, &igi2_frame.tStartPos, sizeof(igi2_frame.tPos));
  World_TraceLines(
    Game_ptGame->ptWorld,
    &igi2_frame.tQObjIntersection,
    &igi2_frame.tStartPos,
    &igi2_frame.tEndPos,
    1,
    GameFunctions_eObjectCollisionEvaluateQTaskEvent,
    &igi2_frame.tObjectCollisionEvaluateContext.tCollisionEvaluateContext,
    0xFFFFFFFF);
  if ( igi2_frame.tQObjIntersection.isHit && igi2_frame.tQObjIntersection.ptEnterMaterial )
  {
    qmemcpy(&igi2_frame.tPos, &igi2_frame.tQObjIntersection.tPos, sizeof(igi2_frame.tPos));
    igi2_frame.tDir = igi2_frame.tQObjIntersection.tNormal;
  }
  if ( igi2_frame.tDir.vX != 0.0 || igi2_frame.tDir.vY != 0.0 || igi2_frame.tDir.vZ != 0.0 )
  {
    v13 = 1.0 / sqrt(igi2_frame.tDir.vX * igi2_frame.tDir.vX + igi2_frame.tDir.vY * igi2_frame.tDir.vY + igi2_frame.tDir.vZ * igi2_frame.tDir.vZ);
    igi2_frame.tDir.vX = igi2_frame.tDir.vX * v13;
    igi2_frame.tDir.vY = igi2_frame.tDir.vY * v13;
    igi2_frame.tDir.vZ = igi2_frame.tDir.vZ * v13;
  }
  Real32x3_GetAngles(&igi2_frame.tDir, (float *)&igi2_frame.vBeta, &igi2_frame.vGamma);
  v14 = *(_DWORD *)&igi2_frame.ptActivateQTask[20].eQTaskType;
  igi2_frame.vGamma = igi2_frame.vGamma + 1.5707963705062866;
  if ( v14 < 0x1000
    && (v15 = Level_atLevelQTaskID[v14]) != nullptr
    && (pxObject = (char *)v15->pxObject) != nullptr
    && QTask_IsQTaskTypeDerived(*((_WORD *)pxObject + 18), EditRigidObj_eQTaskType) )
  {
    qmemcpy(pxObject + 320, &igi2_frame.tPos, 0x18u);
    v17 = igi2_frame.vGamma;
    Real32x9_Create((struct real32x9_t *)(pxObject + 344), 1.5707963705062866, 0.0, igi2_frame.vGamma);
    Real32x9_Create((struct real32x9_t *)(pxObject + 124), 1.5707963705062866, 0.0, v17);
  }
  else
  {
    v17 = igi2_frame.vGamma;
  }
  v18 = ptQTask;
  v19 = 1.0 / sqrt(igi2_frame.tDirection.vY * igi2_frame.tDirection.vY + igi2_frame.tDirection.vZ * igi2_frame.tDirection.vZ + igi2_frame.tDirection.vX * igi2_frame.tDirection.vX);
  igi2_frame.tDirection.vY = v19 * igi2_frame.tDirection.vY;
  igi2_frame.tDirection.vZ = v19 * igi2_frame.tDirection.vZ;
  igi2_frame.tDirection.vZ = igi2_frame.tDirection.vZ * 2048.0;
  igi2_frame.tPos.vX = igi2_frame.tPos.vX - igi2_frame.tDirection.vX * v19 * 2048.0;
  igi2_frame.tPos.vY = igi2_frame.tPos.vY - igi2_frame.tDirection.vY * 2048.0;
  igi2_frame.tPos.vZ = igi2_frame.tPos.vZ - igi2_frame.tDirection.vZ;
  Human_PopPosition(ptQTask, &igi2_frame.tPos);
  ptQTask[86].tQTaskChildren.ptHead = nullptr;
  ptQTask[86].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[86].tQTaskChildren.ptTail = nullptr;
  Human_SnapToGround(ptQTask);
  ptMiddle = ptQTask[44].tQTaskRefList.ptMiddle;
  if ( ptMiddle && ptMiddle->pxObject )
  {
    QReference_Delete(ptMiddle, &QTask_tQTaskRefPool);
    ptQTask[44].tQTaskRefList.ptMiddle = nullptr;
    HIBYTE(ptQTask[74].ptPrev) = 0;
  }
  Human_PopOrientation(ptQTask, v17);
  LOBYTE(ptQTask[76].tQTaskRefList.ptMiddle) = 1;
  igi2_frame.vBeta = (__int64)(*(float *)&igi2_frame.ptActivateQTask[17].eQTaskType * 30.0);
  v21 = ptQTask[33].tQTaskChildren.ptTail;
  *(_QWORD *)&ptQTask[77].eQTaskType = (unsigned int)igi2_frame.vBeta;
  ptQTask[33].tQTaskRefList.ptHead = (struct QReference_s *)3;
  LOBYTE(ptQTask[78].ptPrev) = 1;
  BYTE1(ptQTask[36].tQTaskChildren.ptTail) = 1;
  *(_DWORD *)&v21[11].eQTaskType = 0;
  v21[12].ptNext = nullptr;
  v21[12].ptPrev = nullptr;
  v21[12].tQTaskRefList.ptHead = nullptr;
  v21[12].tQTaskChildren.ptHead = nullptr;
  v21[12].tQTaskChildren.ptMiddle = nullptr;
  v21[12].tQTaskChildren.ptTail = nullptr;
  v21[12].tQTaskRefList.ptMiddle = nullptr;
  LOBYTE(ptQTask[33].tQTaskChildren.ptTail[12].tQTaskRefList.ptTail) = 1;
  LOBYTE(ptQTask[34].tQTaskChildren.ptMiddle) = 1;
  QTask_DeleteQTaskAndQTaskRefSafe(&ptQTask[85].tQTaskRefList.ptMiddle);
  v22 = SoundSys_NewSoundFn(ptQTask[33].tQTaskChildren.ptTail, (char *)&igi2_frame.ptActivateQTask[17].ptNext + 1);
  ptQTask[85].tQTaskRefList.ptMiddle = QTask_NewQTaskRef(v22);
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    HumanPlayer_SendActivateMessage(igi2_frame.ptActivateQTask, 10, 0);
    v18 = ptQTask;
  }
  v18[84].tQTaskChildren.ptMiddle = (struct QTask_s *)20;
  ptState->pfState = HumanPlayer_RunStateActivateGenericTBA;
  if ( !CDAPFN0506_HumanPlayer_InitStateActivatePlaceExplosiveTBA.Version )
    ((void (*)(void))CDAPFN0506_HumanPlayer_InitStateActivatePlaceExplosiveTBA.FunctionAddress)();
}

// source: j/0/human/humanplayer.c:10856  [anchor-mhash]
void __cdecl HumanPlayer_RunStateActivateGenericTBA(struct State_s *ptState, struct QTask_s *ptQTask)
{
  struct QReference_s *ptHead; // eax
  struct QTask_s *pxObject; // edi
  struct QTask_s *ptMiddle; // eax
  unsigned int bSignal; // eax
  struct QTask_s *ptNext; // ecx
  struct QTask_s *v10; // eax
  struct QTask_s *ptTail; // edx
  struct QReference_s *v12; // eax
  void (__cdecl *v13)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v15)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v16)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v17)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v18)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v19)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v20)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v21)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v22)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v23)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v24)(struct State_s *, struct QTask_s *); // eax
  unsigned int ptStatea = *(unsigned int *)&ptState; // [esp+14h] [ebp+4h] ARGSLOT
  bool ptQTaska = *(bool *)&ptQTask; // [esp+18h] [ebp+8h] ARGSLOT

  ptHead = ptQTask[46].tQTaskRefList.ptHead;
  pxObject = nullptr;
  if ( ptHead )
    pxObject = (struct QTask_s *)ptHead->pxObject;
  ptQTaska = 0;
  HumanPlayer_MoveOnGround((struct HumanPlayer_t *)ptQTask, 0.0, 118.76579284667969, 0.0, 118.76579284667969);
  ActionMenuScreen_ptQTask[4].ptNext = (struct QTask_s *)10;
  ptMiddle = ptQTask[84].tQTaskChildren.ptMiddle;
  if ( ptMiddle )
    ptQTask[84].tQTaskChildren.ptMiddle = (struct QTask_s *)((char *)ptMiddle - 1);
  else
    ptQTaska = *(float *)&ptQTask[20].ptNext == 0.0;
  bSignal = ptState->bSignal;
  if ( (bSignal & 0x20000) != 0 )
    ptQTaska = 1;
  if ( (bSignal & 0x10000) != 0 )
    ptQTaska = 1;
  ptNext = ptQTask[78].ptNext;
  v10 = *(struct QTask_s **)&ptQTask[77].eQTaskType;
  if ( (int)ptNext < (int)v10 )
    ptQTask[78].ptNext = (struct QTask_s *)((char *)&ptNext->ptNext + 1);
  ptStatea = ptState->bSignal;
  if ( ptQTask[78].ptNext != v10 )
  {
    if ( !ptQTaska )
      return;
    goto LABEL_14;
  }
  if ( ptQTaska )
  {
LABEL_14:
    if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
      HumanPlayer_SendActivateMessage(pxObject, 0, 0);
    goto LABEL_16;
  }
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    HumanPlayer_SendActivateMessage(pxObject, 10, 1);
  }
  else
  {
    pxObject[20].tQTaskChildren.ptTail = (struct QTask_s *)1;
    pxObject[20].tQTaskRefList.ptTail = nullptr;
  }
LABEL_16:
  ptTail = ptQTask[33].tQTaskChildren.ptTail;
  LOBYTE(ptQTask[76].tQTaskRefList.ptMiddle) = 0;
  LOBYTE(ptTail[12].tQTaskRefList.ptTail) = 0;
  v12 = ptQTask[46].tQTaskRefList.ptHead;
  LOBYTE(ptQTask[34].tQTaskChildren.ptMiddle) = 0;
  LOBYTE(ptQTask[46].tQTaskRefList.ptMiddle) = 0;
  BYTE1(ptQTask[46].tQTaskRefList.ptMiddle) = 1;
  if ( v12 )
  {
    QReference_Delete(v12, &QTask_tQTaskRefPool);
    ptQTask[46].tQTaskRefList.ptHead = nullptr;
  }
  ptQTask[33].tQTaskRefList.ptHead = (struct QReference_s *)1;
  LOBYTE(ptQTask[78].ptPrev) = 0;
  BYTE1(ptQTask[36].tQTaskChildren.ptTail) = 0;
  QTask_DeleteQTaskAndQTaskRefSafe(&ptQTask[85].tQTaskRefList.ptMiddle);
  QTask_DeleteQTaskAndQTaskRefSafe(&ptQTask[85].tQTaskRefList.ptHead);
  if ( (ptStatea & 0x10000) != 0 )
  {
    v13 = ptState->apfExitState[ptState->nState];
    if ( v13 )
      v13(ptState, ptQTask);
    apfState = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 54;
    v15 = apfState[54];
    ptState->pfState = v15;
    v15(ptState, ptQTask);
  }
  else if ( ptQTask[81].ptPrev == (struct QTask_s *)1 )
  {
    v22 = ptState->apfExitState[ptState->nState];
    if ( v22 )
      v22(ptState, ptQTask);
    v23 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 23;
    v24 = v23[23];
    ptState->pfState = v24;
    v24(ptState, ptQTask);
  }
  else if ( ptQTask[81].ptPrev == (struct QTask_s *)2 )
  {
    v19 = ptState->apfExitState[ptState->nState];
    if ( v19 )
      v19(ptState, ptQTask);
    v20 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 75;
    v21 = v20[75];
    ptState->pfState = v21;
    v21(ptState, ptQTask);
  }
  else
  {
    v16 = ptState->apfExitState[ptState->nState];
    if ( v16 )
      v16(ptState, ptQTask);
    v17 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 0;
    v18 = *v17;
    ptState->pfState = *v17;
    v18(ptState, ptQTask);
  }
}

// source: j/0/human/humanplayer.c:11001  [anchor-strings]
void __cdecl HumanPlayer_InitStateSilentKill(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct HumanKilledByYouContext_s tHumanKilledByYouContext; };
    struct { char igi2_o1[4]; struct AnimHeader_s *ptSilentKillAnim; };
    char igi2_extent[8];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QReference_s *ptHead; // eax
  struct QTask_s *pxObject; // esi
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptTail; // ecx
  double v6; // st7
  double v7; // st6
  struct QHashTable_s *v8; // ebx
  unsigned int v9; // eax
  int v10; // eax
  int v11; // ebx
  int v12; // eax
  void (__cdecl *v13)(struct QReference_s **, struct QTask_s *); // eax
  struct QReference_s *v14; // eax
  struct QTask_s *v15; // eax
  void (__cdecl *pfHandler)(struct QTask_s *, struct HumanKilledByYouContext_s *); // eax
  struct AnimHeader_s *v17; // edx
  unsigned int v18; // edx
  struct QTask_s *v19; // eax

  ptHead = ptQTask[46].tQTaskRefList.ptHead;
  pxObject = nullptr;
  if ( ptHead )
    pxObject = (struct QTask_s *)ptHead->pxObject;
  ptQTask[81].ptPrev = *(struct QTask_s **)&ptQTask[32].eQTaskType;
  *(_DWORD *)&ptQTask[32].eQTaskType = 0;
  ptQTask[77].tQTaskRefList.ptTail = nullptr;
  ptQTask[77].ptParent = nullptr;
  HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.4000000059604645);
  ptPrev = ptQTask[33].ptNext[1].ptPrev;
  if ( ptPrev && (ptTail = ptPrev->tQTaskChildren.ptTail) != nullptr )
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    v6 = *(float *)&ptTail[21].ptNext;
    ptQTask[77].tQTaskChildren.ptMiddle = ptTail[21].ptNext;
    v7 = *(float *)&ptQTask[43].ptParent;
    if ( v7 < 0.0 )
      v7 = -v7;
    *(float *)&ptQTask[77].tQTaskChildren.ptMiddle = v7 * *(float *)&ptTail[21].ptParent * 3.0 + v6;
  }
  else
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    ptQTask[77].tQTaskChildren.ptMiddle = nullptr;
  }
  v8 = Hierarchy_ptHashTable;
  v9 = Hierarchy_ptHashTable->tPrivate.pfHashFunction(
         Hierarchy_ptHashTable->tPrivate.nHashTableSize,
         ptQTask[7].tQTaskRefList.ptTail);
  v10 = ((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Hierarchy_ptHashTable->tPrivate.pfFindElement)(v8, v9, (const void *)(ptQTask[7].tQTaskRefList.ptTail));
  v11 = *(_DWORD *)v10;
  v12 = (*(int (__cdecl **)(_DWORD, char *))(*(_DWORD *)v10 + 12))(
          *(_DWORD *)(*(_DWORD *)v10 + 4),
          "tba_silent_kill_jones");
  igi2_frame.ptSilentKillAnim = (struct AnimHeader_s *)(*(int (__cdecl **)(int, int, const void *))(v11 + 28))(v11, v12, (const void *)("tba_silent_kill_jones"));
  HumanAnim_SetAnimation(ptQTask, igi2_frame.ptSilentKillAnim, 0, 0.0);
  v13 = *((void (__cdecl **)(struct QReference_s **, struct QTask_s *))&pxObject[30].ptParent->ptNext
        + (int)pxObject[31].ptPrev);
  if ( v13 )
    v13(&pxObject[30].tQTaskRefList.ptMiddle, ptQTask);
  v14 = pxObject[30].tQTaskRefList.ptTail;
  pxObject[31].ptNext = pxObject[31].ptPrev;
  pxObject[31].ptPrev = (struct QTask_s *)40;
  v15 = (struct QTask_s *)v14[13].ptPrev;
  pxObject[31].tQTaskChildren.ptHead = v15;
  ((void (__cdecl *)(struct QReference_s **, struct QTask_s *))v15)(&pxObject[30].tQTaskRefList.ptMiddle, pxObject);
  Human_PopOrientation(pxObject, *(float *)&ptQTask[34].ptPrev);
  Human_PopPosition(pxObject, (struct real64x3_t *)&ptQTask[1]);
  pfHandler = (void (__cdecl *)(struct QTask_s *, struct HumanKilledByYouContext_s *))QTask_aatQTaskFinalEvent[Human_eKilledByYouQTaskEvent][ptQTask->eQTaskType].pfHandler;
  igi2_frame.tHumanKilledByYouContext.ptSenderQTask = pxObject;
  if ( pfHandler )
    pfHandler(ptQTask, &igi2_frame.tHumanKilledByYouContext);
  v17 = igi2_frame.ptSilentKillAnim;
  LOBYTE(ptQTask[76].tQTaskRefList.ptMiddle) = 1;
  v18 = (int)((unsigned __int64)(1717986919LL * v17->nTotalTime) >> 32) >> 6;
  ptQTask[78].ptNext = nullptr;
  ptQTask[33].tQTaskRefList.ptHead = (struct QReference_s *)3;
  LOBYTE(ptQTask[78].ptPrev) = 1;
  BYTE1(ptQTask[36].tQTaskChildren.ptTail) = 1;
  v19 = ptQTask[33].tQTaskChildren.ptTail;
  *(_DWORD *)&ptQTask[77].eQTaskType = (v18 >> 31) + v18;
  *(_DWORD *)&v19[11].eQTaskType = 0;
  v19[12].ptNext = nullptr;
  v19[12].ptPrev = nullptr;
  v19[12].tQTaskRefList.ptHead = nullptr;
  v19[12].tQTaskChildren.ptHead = nullptr;
  v19[12].tQTaskChildren.ptMiddle = nullptr;
  v19[12].tQTaskChildren.ptTail = nullptr;
  v19[12].tQTaskRefList.ptMiddle = nullptr;
  LOBYTE(ptQTask[33].tQTaskChildren.ptTail[12].tQTaskRefList.ptTail) = 1;
  HumanPlayer_MoveOnGround((struct HumanPlayer_t *)ptQTask, 0.0, 1781.48681640625, 0.0, 1781.48681640625);
  LOBYTE(ptQTask[34].tQTaskChildren.ptMiddle) = 1;
  ptState->pfState = HumanPlayer_RunStateSilentKill;
  if ( !CDAPFN0506_HumanPlayer_InitStateSilentKill.Version )
    ((void (*)(void))CDAPFN0506_HumanPlayer_InitStateSilentKill.FunctionAddress)();
}

// source: j/0/human/humanplayer.c:11082  [anchor-mhash]
void __cdecl HumanPlayer_RunStateSilentKill(struct State_s *ptState, struct QTask_s *ptQTask)
{
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptTail; // ecx
  struct QReference_s *ptHead; // eax
  void (__cdecl *v6)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v8)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v9)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v10)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v11)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v12)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v13)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v14)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v15)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v16)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v17)(struct State_s *, struct QTask_s *); // eax
  unsigned int ptQTaska = *(unsigned int *)&ptQTask; // [esp+10h] [ebp+8h] ARGSLOT

  ActionMenuScreen_ptQTask[4].ptNext = (struct QTask_s *)10;
  ptNext = ptQTask[78].ptNext;
  if ( (int)ptNext < (int)(*(_DWORD *)&ptQTask[77].eQTaskType) )
    ptQTask[78].ptNext = (struct QTask_s *)((char *)&ptNext->ptNext + 1);
  ptQTaska = ptState->bSignal;
  if ( (ptQTaska & 1) != 0 )
  {
    ptTail = ptQTask[33].tQTaskChildren.ptTail;
    LOBYTE(ptQTask[76].tQTaskRefList.ptMiddle) = 0;
    LOBYTE(ptTail[12].tQTaskRefList.ptTail) = 0;
    ptHead = ptQTask[46].tQTaskRefList.ptHead;
    LOBYTE(ptQTask[34].tQTaskChildren.ptMiddle) = 0;
    LOBYTE(ptQTask[46].tQTaskRefList.ptMiddle) = 0;
    BYTE1(ptQTask[46].tQTaskRefList.ptMiddle) = 1;
    if ( ptHead )
    {
      QReference_Delete(ptHead, &QTask_tQTaskRefPool);
      ptQTask[46].tQTaskRefList.ptHead = nullptr;
    }
    ptQTask[33].tQTaskRefList.ptHead = (struct QReference_s *)1;
    LOBYTE(ptQTask[78].ptPrev) = 0;
    BYTE1(ptQTask[36].tQTaskChildren.ptTail) = 0;
    QTask_DeleteQTaskAndQTaskRefSafe(&ptQTask[85].tQTaskRefList.ptMiddle);
    QTask_DeleteQTaskAndQTaskRefSafe(&ptQTask[85].tQTaskRefList.ptHead);
    if ( (ptQTaska & 0x10000) != 0 )
    {
      v6 = ptState->apfExitState[ptState->nState];
      if ( v6 )
        v6(ptState, ptQTask);
      apfState = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 54;
      v8 = apfState[54];
      ptState->pfState = v8;
      v8(ptState, ptQTask);
    }
    else if ( ptQTask[81].ptPrev == (struct QTask_s *)1 )
    {
      v15 = ptState->apfExitState[ptState->nState];
      if ( v15 )
        v15(ptState, ptQTask);
      v16 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 23;
      v17 = v16[23];
      ptState->pfState = v17;
      v17(ptState, ptQTask);
    }
    else if ( ptQTask[81].ptPrev == (struct QTask_s *)2 )
    {
      v12 = ptState->apfExitState[ptState->nState];
      if ( v12 )
        v12(ptState, ptQTask);
      v13 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 75;
      v14 = v13[75];
      ptState->pfState = v14;
      v14(ptState, ptQTask);
    }
    else
    {
      v9 = ptState->apfExitState[ptState->nState];
      if ( v9 )
        v9(ptState, ptQTask);
      v10 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 0;
      v11 = *v10;
      ptState->pfState = v11;
      v11(ptState, ptQTask);
    }
  }
}

// source: j/0/human/humanplayer.c:11168  [anchor-mhash]
void __cdecl HumanPlayer_Climb(struct HumanPlayer_t *ptHumanPlayer, enum bool isDown, float vSteps)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptQTask; };
    struct { char igi2_o1[16]; struct real32x3_t tMove; };
    char igi2_extent[28];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct AnimHeader_s *ptAnim; // eax
  int nTotalTime; // eax
  double v5; // st7

  ptAnim = ptHumanPlayer->tHuman.tHumanAnim.ptActiveMainController->ptAnim;
  igi2_frame.tMove.vX = 0.0;
  igi2_frame.tMove.vY = 0.0;
  igi2_frame.tMove.vZ = 1.0;
  if ( ptAnim )
    nTotalTime = ptAnim->nTotalTime;
  else
    nTotalTime = 0;
  if ( isDown )
    v5 = -0.30000001192092896;
  else
    v5 = 0.30000001192092896;
  igi2_frame.ptQTask = v5 * vSteps * 4096.0 / (double)(30 * nTotalTime / 4800);
  Human_MoveFree(&ptHumanPlayer->tHuman.tBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask, igi2_frame.ptQTask, &igi2_frame.tMove, false);
}

// source: j/0/human/humanplayer.c:11189  [anchor-mhash]
void __cdecl HumanPlayer_InitStateClimbLadder(struct State_s *ptState, struct QTask_s *ptQTask)
{
  struct QTask_s *ptTail; // eax
  struct QTask_s *v3; // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *v5; // ecx
  double v6; // st7
  double v7; // st6
  double v8; // st7

  ptTail = ptQTask[33].tQTaskChildren.ptTail;
  *(_DWORD *)&ptTail[14].eQTaskType = 0;
  ptTail[14].tQTaskRefList.ptMiddle = nullptr;
  v3 = *(struct QTask_s **)&ptQTask[32].eQTaskType;
  LOBYTE(ptQTask[80].tQTaskRefList.ptMiddle) = 0;
  ptQTask[81].ptPrev = v3;
  *(_DWORD *)&ptQTask[32].eQTaskType = 0;
  HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, 0, 0.0);
  ptQTask[77].tQTaskRefList.ptTail = nullptr;
  ptQTask[77].ptParent = nullptr;
  HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.4000000059604645);
  ptPrev = ptQTask[33].ptNext[1].ptPrev;
  if ( ptPrev && (v5 = ptPrev->tQTaskChildren.ptTail) != nullptr )
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    v6 = *(float *)&v5[21].ptNext;
    ptQTask[77].tQTaskChildren.ptMiddle = v5[21].ptNext;
    v7 = *(float *)&ptQTask[43].ptParent;
    if ( v7 < 0.0 )
      v7 = -v7;
    *(float *)&ptQTask[77].tQTaskChildren.ptMiddle = v7 * *(float *)&v5[21].ptParent * 3.0 + v6;
  }
  else
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    ptQTask[77].tQTaskChildren.ptMiddle = nullptr;
  }
  v8 = (double)AnimController_nTicksPerFrame;
  ptQTask[78].tQTaskRefList.ptTail = nullptr;
  ptQTask[34].tQTaskChildren.ptTail[1].tQTaskRefList.ptTail = (struct QReference_s *)(__int64)(v8 * 0.0);
  ptState->pfState = HumanPlayer_RunStateClimbLadder;
}

// source: j/0/human/humanplayer.c:11231  [anchor-mhash]
void __cdecl HumanPlayer_RunStateClimbLadder(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real32x3_t ptUnitVector; };
    struct { char igi2_o1[16]; struct HumanAIEventContext_t ptEventContext; };
    char igi2_extent[84];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  unsigned int v3; // ebx
  double v4; // st7
  struct QReference_s *ptTail; // eax
  void (__cdecl *v6)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v8)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v9)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v10)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v11)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v12)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v13)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v14)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v15)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v16)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v17)(struct State_s *, struct QTask_s *); // eax
  struct QReference_s *v18; // eax
  double v19; // st7
  double v20; // st7
  void (__cdecl *v21)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v22)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v23)(struct State_s *, struct QTask_s *); // eax
  struct QReference_s *ptMiddle; // eax
  void (__cdecl *v25)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v26)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v27)(struct State_s *, struct QTask_s *); // eax
  unsigned int ptStatea = *(unsigned int *)&ptState; // [esp+68h] [ebp+4h] ARGSLOT
  float ptStateb = *(float *)&ptState; // [esp+68h] [ebp+4h] ARGSLOT
  float ptStatec = *(float *)&ptState; // [esp+68h] [ebp+4h] ARGSLOT

  ptStatea = ptState->bSignal;
  v3 = ptStatea;
  HumanPlayer_MoveOnGround((struct HumanPlayer_t *)ptQTask, 0.0, 118.76579284667969, 0.0, 118.76579284667969);
  if ( (ptStatea & 0x100000) != 0 )
  {
    v4 = (double)AnimController_nTicksPerFrame;
    *(_DWORD *)&ptQTask[30].eQTaskType &= ~0x100000u;
    *(_QWORD *)&igi2_frame.ptUnitVector.vX = (__int64)(v4 * 0.0);
    ptQTask[34].tQTaskChildren.ptTail[1].tQTaskRefList.ptTail = (struct QReference_s *)LODWORD(igi2_frame.ptUnitVector.vX);
    ptQTask[78].tQTaskRefList.ptMiddle = (struct QReference_s *)((char *)ptQTask[78].tQTaskRefList.ptMiddle
                                                               + (unsigned int)ptQTask[78].tQTaskRefList.ptTail);
    ptQTask[78].tQTaskRefList.ptTail = nullptr;
    Human_MakeLadderFootstepSound(ptQTask);
  }
  else if ( (ptStatea & 0x180) != 0 && (ptStatea & 0x40000) == 0 )
  {
    ptTail = ptQTask[10].tQTaskRefList.ptTail;
    igi2_frame.ptEventContext.eEvent = 13;
    igi2_frame.ptEventContext.eTeam = (int)ptTail;
    igi2_frame.ptEventContext.bFlags = 1090;
    igi2_frame.ptEventContext.vRadius = 81920.0;
    igi2_frame.ptEventContext.ptPosition = (struct real64x3_t *)&ptQTask[1];
    igi2_frame.ptEventContext.ptReferenceQTask = ptQTask;
    igi2_frame.ptEventContext.ptHumanOriginatorQTask = ptQTask;
    HumanAI_SendEvent(&igi2_frame.ptEventContext);
    v3 = ptStatea;
  }
  if ( ptQTask[78].tQTaskRefList.ptTail )
    goto LABEL_27;
  if ( (v3 & 0x80u) != 0 )
  {
    if ( ptQTask[78].tQTaskRefList.ptMiddle == (struct QReference_s *)((char *)ptQTask[78].tQTaskRefList.ptHead - 6) )
    {
      v6 = ptState->apfExitState[ptState->nState];
      if ( v6 )
        v6(ptState, ptQTask);
      apfState = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 47;
      v8 = apfState[47];
      ptState->pfState = v8;
      v8(ptState, ptQTask);
      return;
    }
    ptQTask[78].tQTaskRefList.ptTail = (struct QReference_s *)1;
    goto LABEL_27;
  }
  if ( (v3 & 0x100) == 0 )
  {
LABEL_27:
    v18 = ptQTask[78].tQTaskRefList.ptTail;
    if ( v18 )
    {
      if ( (int)v18 <= 0 )
      {
        if ( (v3 & 0x40000) != 0 )
          v20 = -1.0;
        else
          v20 = -1.75;
        ptStatec = 2.0;
        *(_QWORD *)&igi2_frame.ptUnitVector.vX = (__int64)((double)AnimController_nTicksPerFrame * v20);
        ptQTask[34].tQTaskChildren.ptTail[1].tQTaskRefList.ptTail = (struct QReference_s *)LODWORD(igi2_frame.ptUnitVector.vX);
        if ( (v3 & 0x40000) == 0 )
          ptStatec = 3.5;
        HumanPlayer_Climb((struct HumanPlayer_t *)ptQTask, true, ptStatec);
      }
      else
      {
        if ( (v3 & 0x40000) != 0 )
          v19 = 1.0;
        else
          v19 = 1.75;
        ptStateb = 2.0;
        *(_QWORD *)&igi2_frame.ptUnitVector.vX = (__int64)((double)AnimController_nTicksPerFrame * v19);
        ptQTask[34].tQTaskChildren.ptTail[1].tQTaskRefList.ptTail = (struct QReference_s *)LODWORD(igi2_frame.ptUnitVector.vX);
        if ( (v3 & 0x40000) == 0 )
          ptStateb = 3.5;
        HumanPlayer_Climb((struct HumanPlayer_t *)ptQTask, false, ptStateb);
      }
    }
    if ( *(float *)&ptQTask[20].ptNext == 0.0 || *(float *)&ptQTask[13].tQTaskRefList.ptTail != 0.0 )
    {
      if ( (v3 & 0x20000) != 0 )
        BYTE2(ptQTask[78].tQTaskChildren.ptTail) = 1;
      if ( (v3 & 0x800000) != 0 )
      {
        igi2_frame.ptUnitVector.vX = 0.0;
        igi2_frame.ptUnitVector.vY = 1.0;
        igi2_frame.ptUnitVector.vZ = 0.0;
        BYTE2(ptQTask[78].tQTaskChildren.ptTail) = 1;
        Human_MoveFree(ptQTask, -2048.0, &igi2_frame.ptUnitVector, true);
        ptMiddle = ptQTask[44].tQTaskRefList.ptMiddle;
        if ( ptMiddle && ptMiddle->pxObject )
        {
          QReference_Delete(ptMiddle, &QTask_tQTaskRefPool);
          ptQTask[44].tQTaskRefList.ptMiddle = nullptr;
          HIBYTE(ptQTask[74].ptPrev) = 0;
        }
        SoundSys_NewSoundFn(ptQTask[33].tQTaskChildren.ptTail, "water_land_02");
        v25 = ptState->apfExitState[ptState->nState];
        if ( v25 )
          v25(ptState, ptQTask);
        v26 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 21;
        v27 = v26[21];
        ptState->pfState = v27;
        v27(ptState, ptQTask);
      }
    }
    else
    {
      v21 = ptState->apfExitState[ptState->nState];
      if ( v21 )
        v21(ptState, ptQTask);
      v22 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 48;
      v23 = v22[48];
      ptState->pfState = v23;
      v23(ptState, ptQTask);
    }
    return;
  }
  if ( ptQTask[78].tQTaskRefList.ptMiddle )
  {
    ptQTask[78].tQTaskRefList.ptTail = (struct QReference_s *)-1;
    goto LABEL_27;
  }
  igi2_frame.ptUnitVector.vX = 0.0;
  igi2_frame.ptUnitVector.vY = 1.0;
  igi2_frame.ptUnitVector.vZ = 0.0;
  BYTE2(ptQTask[78].tQTaskChildren.ptTail) = 1;
  Human_MoveFree(ptQTask, -2048.0, &igi2_frame.ptUnitVector, true);
  Human_UpdatePosition(ptQTask);
  if ( ptQTask[81].ptPrev == (struct QTask_s *)1 )
  {
    v15 = ptState->apfExitState[ptState->nState];
    if ( v15 )
      v15(ptState, ptQTask);
    v16 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 23;
    v17 = v16[23];
    ptState->pfState = v17;
    v17(ptState, ptQTask);
  }
  else if ( ptQTask[81].ptPrev == (struct QTask_s *)2 )
  {
    v12 = ptState->apfExitState[ptState->nState];
    if ( v12 )
      v12(ptState, ptQTask);
    v13 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 75;
    v14 = v13[75];
    ptState->pfState = v14;
    v14(ptState, ptQTask);
  }
  else
  {
    v9 = ptState->apfExitState[ptState->nState];
    if ( v9 )
      v9(ptState, ptQTask);
    v10 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 0;
    v11 = *v10;
    ptState->pfState = *v10;
    v11(ptState, ptQTask);
  }
}

// source: j/0/human/humanplayer.c:11381  [anchor-mhash]
void __cdecl HumanPlayer_InitStateClimbLadderGetOnTop(struct State_s *ptState, struct QTask_s *ptQTask)
{
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptTail; // ecx
  double v4; // st7
  double v5; // st6

  HumanAnim_SetAnimationAtEndFromState(ptQTask, ptState->nState, 0.0);
  ptQTask[34].tQTaskChildren.ptTail[1].tQTaskRefList.ptTail = (struct QReference_s *)(__int64)((double)AnimController_nTicksPerFrame
                                                                                             * -1.0);
  ptQTask[77].tQTaskRefList.ptTail = nullptr;
  ptQTask[77].ptParent = nullptr;
  HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.4000000059604645);
  ptPrev = ptQTask[33].ptNext[1].ptPrev;
  if ( ptPrev && (ptTail = ptPrev->tQTaskChildren.ptTail) != nullptr )
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    v4 = *(float *)&ptTail[21].ptNext;
    ptQTask[77].tQTaskChildren.ptMiddle = ptTail[21].ptNext;
    v5 = *(float *)&ptQTask[43].ptParent;
    if ( v5 < 0.0 )
      v5 = -v5;
    *(float *)&ptQTask[77].tQTaskChildren.ptMiddle = v5 * *(float *)&ptTail[21].ptParent * 3.0 + v4;
    ptState->pfState = HumanPlayer_RunStateClimbLadderGetOnTop;
  }
  else
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    ptQTask[77].tQTaskChildren.ptMiddle = nullptr;
    ptState->pfState = HumanPlayer_RunStateClimbLadderGetOnTop;
  }
}

// source: j/0/human/humanplayer.c:11404  [anchor-mhash]
void __cdecl HumanPlayer_RunStateClimbLadderGetOnTop(struct State_s *ptState, struct QTask_s *ptQTask)
{
  unsigned int bSignal; // ebx
  double v3; // st7
  void (__cdecl *v4)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v6)(struct State_s *, struct QTask_s *); // eax
  struct real32x3_t tMove; // [esp+10h] [ebp-14h] BYREF

  bSignal = ptState->bSignal;
  if ( (bSignal & 0x40000) != 0 )
    v3 = -1.0;
  else
    v3 = -2.0;
  *(_QWORD *)&tMove.vX = (__int64)((double)AnimController_nTicksPerFrame * v3);
  ptQTask[34].tQTaskChildren.ptTail[1].tQTaskRefList.ptTail = (struct QReference_s *)LODWORD(tMove.vX);
  if ( (bSignal & 0x100000) != 0 )
  {
    *(_DWORD *)&ptQTask[30].eQTaskType &= ~0x100000u;
    Human_MakeLadderFootstepSound(ptQTask);
  }
  if ( (bSignal & 1) != 0 )
  {
    tMove.vX = 0.0;
    tMove.vY = 0.0;
    tMove.vZ = 1.0;
    Human_MoveFree(ptQTask, 2457.60009765625, &tMove, false);
    v4 = ptState->apfExitState[ptState->nState];
    if ( v4 )
      v4(ptState, ptQTask);
    apfState = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 45;
    v6 = apfState[45];
    ptState->pfState = v6;
    v6(ptState, ptQTask);
  }
  else if ( (bSignal & 0x20000) != 0 )
  {
    BYTE2(ptQTask[78].tQTaskChildren.ptTail) = 1;
  }
}

// source: j/0/human/humanplayer.c:11454  [anchor-mhash]
void __cdecl HumanPlayer_InitStateClimbLadderGetOffTop(struct State_s *ptState, struct QTask_s *ptQTask)
{
  int nState; // ebx
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptTail; // ecx
  double v5; // st7
  double v6; // st6
  struct real32x3_t ptUnitVector; // [esp+Ch] [ebp-Ch] BYREF

  nState = ptState->nState;
  ptUnitVector.vX = 0.0;
  ptUnitVector.vY = 0.0;
  ptUnitVector.vZ = 1.0;
  HumanAnim_SetAnimationAndTimeFromState(ptQTask, nState, 0, 0.0);
  ptQTask[77].tQTaskRefList.ptTail = nullptr;
  ptQTask[77].ptParent = nullptr;
  HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.4000000059604645);
  ptPrev = ptQTask[33].ptNext[1].ptPrev;
  if ( ptPrev && (ptTail = ptPrev->tQTaskChildren.ptTail) != nullptr )
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    v5 = *(float *)&ptTail[21].ptNext;
    ptQTask[77].tQTaskChildren.ptMiddle = ptTail[21].ptNext;
    v6 = *(float *)&ptQTask[43].ptParent;
    if ( v6 < 0.0 )
      v6 = -v6;
    *(float *)&ptQTask[77].tQTaskChildren.ptMiddle = v6 * *(float *)&ptTail[21].ptParent * 3.0 + v5;
  }
  else
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    ptQTask[77].tQTaskChildren.ptMiddle = nullptr;
  }
  Human_MoveFree(ptQTask, -2457.60009765625, &ptUnitVector, false);
  ptState->pfState = HumanPlayer_RunStateClimbLadderGetOffTop;
}

// source: j/0/human/humanplayer.c:11482  [anchor-mhash]
void __cdecl HumanPlayer_RunStateClimbLadderGetOffTop(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float Real32x3_Rotate_tTemp_8; };
    struct { char igi2_o1[8]; struct real64x3_t tPos; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  unsigned int bSignal; // ebx
  double v3; // st7
  double v4; // st7
  double v5; // st6
  double v6; // rt0
  char *v7; // eax
  void (__cdecl *v8)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v9)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v10)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v11)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v13)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v14)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v15)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v16)(struct State_s *, struct QTask_s *); // eax

  bSignal = ptState->bSignal;
  if ( (bSignal & 0x40000) != 0 )
    v3 = 1.0;
  else
    v3 = 2.0;
  ptQTask[34].tQTaskChildren.ptTail[1].tQTaskRefList.ptTail = (struct QReference_s *)(__int64)((double)AnimController_nTicksPerFrame
                                                                                             * v3);
  if ( (bSignal & 0x100000) != 0 )
  {
    *(_DWORD *)&ptQTask[30].eQTaskType &= ~0x100000u;
    Human_MakeLadderFootstepSound(ptQTask);
  }
  if ( (bSignal & 1) != 0 )
  {
    v4 = *(float *)&ptQTask[3].tQTaskChildren.ptMiddle * 8192.0;
    v5 = *(float *)&ptQTask[3].tQTaskChildren.ptHead;
    BYTE2(ptQTask[78].tQTaskChildren.ptTail) = 1;
    igi2_frame.Real32x3_Rotate_tTemp_8 = *(float *)&ptQTask[3].eQTaskType * 8192.0
                            + *(float *)&ptQTask[3].ptParent * 6144.0
                            + *(float *)&ptQTask[3].tQTaskRefList.ptTail * 0.0;
    v6 = *(float *)&ptQTask[3].tQTaskRefList.ptMiddle * 8192.0
       + *(float *)&ptQTask[3].tQTaskRefList.ptHead * 6144.0
       + *(float *)&ptQTask[3].tQTaskChildren.ptTail * 0.0;
    igi2_frame.tPos.vX = v4 + v5 * 6144.0 + *(float *)&ptQTask[3].ptPrev * 0.0 + *(double *)&ptQTask[1].ptNext;
    igi2_frame.tPos.vY = v6 + *(double *)&ptQTask[1].tQTaskChildren.ptHead;
    igi2_frame.tPos.vZ = igi2_frame.Real32x3_Rotate_tTemp_8 + *(double *)&ptQTask[1].tQTaskChildren.ptTail;
    Human_PopPosition(ptQTask, &igi2_frame.tPos);
    v7 = &ptQTask[81].ptPrev[-1].isInMemPool + 1;
    ptQTask[86].tQTaskChildren.ptHead = nullptr;
    ptQTask[86].tQTaskChildren.ptMiddle = nullptr;
    ptQTask[86].tQTaskChildren.ptTail = nullptr;
    if ( v7 )
    {
      if ( v7 == (char *)1 )
      {
        v11 = ptState->apfExitState[ptState->nState];
        if ( v11 )
          v11(ptState, ptQTask);
        apfState = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 75;
        v13 = apfState[75];
        ptState->pfState = v13;
        v13(ptState, ptQTask);
      }
      else
      {
        v8 = ptState->apfExitState[ptState->nState];
        if ( v8 )
          v8(ptState, ptQTask);
        v9 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 0;
        v10 = *v9;
        ptState->pfState = v10;
        v10(ptState, ptQTask);
      }
    }
    else
    {
      v14 = ptState->apfExitState[ptState->nState];
      if ( v14 )
        v14(ptState, ptQTask);
      v15 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 23;
      v16 = v15[23];
      ptState->pfState = v16;
      v16(ptState, ptQTask);
    }
  }
  else if ( (bSignal & 0x20000) != 0 )
  {
    BYTE2(ptQTask[78].tQTaskChildren.ptTail) = 1;
  }
}

// source: j/0/human/humanplayer.c:11553  [anchor-mhash]
void __cdecl HumanPlayer_InitStateClimbLadderSlideDown(struct State_s *ptState, struct QTask_s *ptQTask)
{
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptTail; // ecx
  double v4; // st7
  double v5; // st6
  struct QTask_s *v6; // eax

  *(_DWORD *)&ptQTask[32].eQTaskType = 0;
  HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, 0, 0.0);
  ptQTask[77].tQTaskRefList.ptTail = nullptr;
  ptQTask[77].ptParent = nullptr;
  HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.4000000059604645);
  ptPrev = ptQTask[33].ptNext[1].ptPrev;
  if ( ptPrev && (ptTail = ptPrev->tQTaskChildren.ptTail) != nullptr )
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    v4 = *(float *)&ptTail[21].ptNext;
    ptQTask[77].tQTaskChildren.ptMiddle = ptTail[21].ptNext;
    v5 = *(float *)&ptQTask[43].ptParent;
    if ( v5 < 0.0 )
      v5 = -v5;
    *(float *)&ptQTask[77].tQTaskChildren.ptMiddle = v5 * *(float *)&ptTail[21].ptParent * 3.0 + v4;
  }
  else
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    ptQTask[77].tQTaskChildren.ptMiddle = nullptr;
  }
  LOBYTE(ptQTask[40].tQTaskChildren.ptMiddle) = 1;
  QTask_DeleteQTaskAndQTaskRefSafe(&ptQTask[85].tQTaskRefList.ptHead);
  v6 = SoundSys_NewSoundFn(ptQTask[33].tQTaskChildren.ptTail, "wire_slide_1");
  ptQTask[85].tQTaskRefList.ptHead = QTask_NewQTaskRef(v6);
  ptState->pfState = HumanPlayer_RunStateClimbLadderSlideDown;
}

// source: j/0/human/humanplayer.c:11588  [anchor-mhash]
void __cdecl HumanPlayer_RunStateClimbLadderSlideDown(struct State_s *ptState, struct QTask_s *ptQTask)
{
  struct QReference_s *ptHead; // eax
  struct RigidDynCubeObj_t *pxObject; // ecx
  double v5; // st7
  unsigned int bSignal; // edx
  BOOL v7; // ecx
  struct QReference_s *ptMiddle; // eax
  void (__cdecl *v9)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v11)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v12)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v13)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v14)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v15)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v16)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v17)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v18)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v19)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v20)(struct State_s *, struct QTask_s *); // eax
  struct real64x3_t ptPos; // [esp+10h] [ebp-1Ch] BYREF
  unsigned int ptQTaska = *(unsigned int *)&ptQTask; // [esp+34h] [ebp+8h] ARGSLOT

  ptHead = ptQTask[46].tQTaskRefList.ptHead;
  pxObject = nullptr;
  if ( ptHead )
    pxObject = (struct RigidDynCubeObj_t *)ptHead->pxObject;
  ActionMenuScreen_ptQTask[4].ptNext = (struct QTask_s *)10;
  RigidDynCubeObj_GetMagicVertexPos(pxObject, 0, &ptPos);
  *(float *)&ptQTask[38].ptPrev = *(float *)&ptQTask[38].ptPrev * 0.9900000095367432;
  *(float *)&ptQTask[38].tQTaskChildren.ptHead = *(float *)&ptQTask[38].tQTaskChildren.ptHead * 0.9900000095367432;
  v5 = (*(float *)&ptQTask[38].tQTaskChildren.ptMiddle - 44.600887298583984) * 0.9900000095367432;
  *(float *)&ptQTask[38].tQTaskChildren.ptMiddle = v5;
  bSignal = ptState->bSignal;
  ptQTaska = bSignal;
  v7 = *(double *)&ptQTask[43].tQTaskRefList.ptMiddle > -4096.0 && -v5 > *(double *)&ptQTask[43].tQTaskRefList.ptMiddle;
  if ( *(double *)&ptQTask[1].tQTaskChildren.ptTail - ptPos.vZ < 4096.0
    && (LOBYTE(ptQTask[40].tQTaskChildren.ptMiddle) = 0, v7)
    || (bSignal & 0x800000) != 0 )
  {
    ptPos.vX = 0.0078125;
    LODWORD(ptPos.vY) = 0;
    Human_MoveFree(ptQTask, -2048.0, (struct real32x3_t *)&ptPos, true);
    ptMiddle = ptQTask[44].tQTaskRefList.ptMiddle;
    if ( ptMiddle && ptMiddle->pxObject )
    {
      QReference_Delete(ptMiddle, &QTask_tQTaskRefPool);
      ptQTask[44].tQTaskRefList.ptMiddle = nullptr;
      HIBYTE(ptQTask[74].ptPrev) = 0;
    }
    ptQTask[38].ptPrev = nullptr;
    ptQTask[38].tQTaskChildren.ptHead = nullptr;
    ptQTask[38].tQTaskChildren.ptMiddle = nullptr;
    ptQTask[38].tQTaskChildren.ptTail = nullptr;
    ptQTask[38].tQTaskRefList.ptHead = nullptr;
    ptQTask[38].tQTaskRefList.ptMiddle = nullptr;
    QTask_DeleteQTaskAndQTaskRefSafe(&ptQTask[85].tQTaskRefList.ptMiddle);
    QTask_DeleteQTaskAndQTaskRefSafe(&ptQTask[85].tQTaskRefList.ptHead);
    LOBYTE(ptQTask[40].tQTaskChildren.ptMiddle) = 0;
    BYTE2(ptQTask[78].tQTaskChildren.ptTail) = 1;
    if ( (ptQTaska & 0x800000) != 0 )
    {
      SoundSys_NewSoundFn(ptQTask[33].tQTaskChildren.ptTail, "water_land_02");
      v9 = ptState->apfExitState[ptState->nState];
      if ( v9 )
        v9(ptState, ptQTask);
      apfState = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 21;
      v11 = apfState[21];
      ptState->pfState = v11;
      v11(ptState, ptQTask);
    }
    else if ( ptQTask[81].ptPrev == (struct QTask_s *)1 )
    {
      v18 = ptState->apfExitState[ptState->nState];
      if ( v18 )
        v18(ptState, ptQTask);
      v19 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 23;
      v20 = v19[23];
      ptState->pfState = v20;
      v20(ptState, ptQTask);
    }
    else if ( ptQTask[81].ptPrev == (struct QTask_s *)2 )
    {
      v15 = ptState->apfExitState[ptState->nState];
      if ( v15 )
        v15(ptState, ptQTask);
      v16 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 75;
      v17 = v16[75];
      ptState->pfState = v17;
      v17(ptState, ptQTask);
    }
    else
    {
      v12 = ptState->apfExitState[ptState->nState];
      if ( v12 )
        v12(ptState, ptQTask);
      v13 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 0;
      v14 = *v13;
      ptState->pfState = v14;
      v14(ptState, ptQTask);
    }
  }
}

// source: j/0/human/humanplayer.c:11680  [anchor-strings]
void __cdecl HumanPlayer_InitStateClimbFence(struct State_s *ptState, struct QTask_s *ptQTask)
{
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptTail; // ecx
  double v4; // st7
  double v5; // st6
  struct QTask_s *v6; // [esp-4h] [ebp-14h]

  ptQTask[81].ptPrev = *(struct QTask_s **)&ptQTask[32].eQTaskType;
  *(_DWORD *)&ptQTask[32].eQTaskType = 0;
  HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, 0, 0.0);
  ptQTask[77].tQTaskRefList.ptTail = nullptr;
  ptQTask[77].ptParent = nullptr;
  HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.4000000059604645);
  ptPrev = ptQTask[33].ptNext[1].ptPrev;
  if ( ptPrev && (ptTail = ptPrev->tQTaskChildren.ptTail) != nullptr )
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    v4 = *(float *)&ptTail[21].ptNext;
    ptQTask[77].tQTaskChildren.ptMiddle = ptTail[21].ptNext;
    v5 = *(float *)&ptQTask[43].ptParent;
    if ( v5 < 0.0 )
      v5 = -v5;
    *(float *)&ptQTask[77].tQTaskChildren.ptMiddle = v5 * *(float *)&ptTail[21].ptParent * 3.0 + v4;
  }
  else
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    ptQTask[77].tQTaskChildren.ptMiddle = nullptr;
  }
  v6 = ptQTask[33].tQTaskChildren.ptTail;
  *(_DWORD *)&ptQTask[77].eQTaskType = 180;
  ptQTask[78].ptNext = nullptr;
  SoundSys_NewSoundFn(v6, "tba_fenceclimb");
  ptState->pfState = HumanPlayer_RunStateClimbFence;
}

// source: j/0/human/humanplayer.c:11715  [anchor-mhash]
void __cdecl HumanPlayer_RunStateClimbFence(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float Real32x3_Rotate_tTemp_8; };
    struct { char igi2_o1[4]; struct real64x3_t tPos; };
    char igi2_extent[32];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptNext; // eax
  unsigned int bSignal; // eax
  double v4; // st7
  double v5; // st6
  double v6; // rt0
  struct QTask_s *ptPrev; // ecx
  void (__cdecl *v8)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v10)(struct State_s *, struct QTask_s *); // eax

  HumanPlayer_MoveOnGround((struct HumanPlayer_t *)ptQTask, 0.0, 118.76579284667969, 0.0, 118.76579284667969);
  ptNext = ptQTask[78].ptNext;
  if ( (int)ptNext < (int)(*(_DWORD *)&ptQTask[77].eQTaskType) )
    ptQTask[78].ptNext = (struct QTask_s *)((char *)&ptNext->ptNext + 1);
  bSignal = ptState->bSignal;
  if ( (bSignal & 1) != 0 )
  {
    v4 = *(float *)&ptQTask[3].tQTaskChildren.ptMiddle * 8192.0;
    v5 = *(float *)&ptQTask[3].tQTaskChildren.ptHead;
    BYTE2(ptQTask[78].ptParent) = 1;
    igi2_frame.Real32x3_Rotate_tTemp_8 = *(float *)&ptQTask[3].eQTaskType * 8192.0
                            + *(float *)&ptQTask[3].ptParent * 6144.0
                            + *(float *)&ptQTask[3].tQTaskRefList.ptTail * 0.0;
    v6 = *(float *)&ptQTask[3].tQTaskRefList.ptMiddle * 8192.0
       + *(float *)&ptQTask[3].tQTaskRefList.ptHead * 6144.0
       + *(float *)&ptQTask[3].tQTaskChildren.ptTail * 0.0;
    igi2_frame.tPos.vX = v4 + v5 * 6144.0 + *(float *)&ptQTask[3].ptPrev * 0.0 + *(double *)&ptQTask[1].ptNext;
    igi2_frame.tPos.vY = v6 + *(double *)&ptQTask[1].tQTaskChildren.ptHead;
    igi2_frame.tPos.vZ = igi2_frame.Real32x3_Rotate_tTemp_8 + *(double *)&ptQTask[1].tQTaskChildren.ptTail;
    Human_PopPosition(ptQTask, &igi2_frame.tPos);
    ptPrev = ptQTask[81].ptPrev;
    ptQTask[86].tQTaskChildren.ptHead = nullptr;
    ptQTask[86].tQTaskChildren.ptMiddle = nullptr;
    ptQTask[86].tQTaskChildren.ptTail = nullptr;
    *(_DWORD *)&ptQTask[32].eQTaskType = ptPrev;
    v8 = ptState->apfExitState[ptState->nState];
    if ( v8 )
      v8(ptState, ptQTask);
    apfState = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 37;
    v10 = apfState[37];
    ptState->pfState = v10;
    v10(ptState, ptQTask);
  }
  else if ( (bSignal & 0x20000) != 0 )
  {
    BYTE2(ptQTask[78].ptParent) = 1;
  }
}

// source: j/0/human/humanplayer.c:11773  [anchor-mhash]
void __cdecl HumanPlayer_InitStateClimbWire(struct State_s *ptState, struct QTask_s *ptQTask)
{
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptTail; // ecx
  double v4; // st7
  double v5; // st6

  *(_DWORD *)&ptQTask[32].eQTaskType = 0;
  HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, 0, 0.0);
  ptQTask[77].tQTaskRefList.ptTail = nullptr;
  ptQTask[77].ptParent = nullptr;
  HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.4000000059604645);
  ptPrev = ptQTask[33].ptNext[1].ptPrev;
  if ( ptPrev && (ptTail = ptPrev->tQTaskChildren.ptTail) != nullptr )
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    v4 = *(float *)&ptTail[21].ptNext;
    ptQTask[77].tQTaskChildren.ptMiddle = ptTail[21].ptNext;
    v5 = *(float *)&ptQTask[43].ptParent;
    if ( v5 < 0.0 )
      v5 = -v5;
    *(float *)&ptQTask[77].tQTaskChildren.ptMiddle = v5 * *(float *)&ptTail[21].ptParent * 3.0 + v4;
    ptQTask[79].ptNext = (struct QTask_s *)-1;
    ptState->pfState = HumanPlayer_RunStateClimbWire;
  }
  else
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    ptQTask[77].tQTaskChildren.ptMiddle = nullptr;
    ptQTask[79].ptNext = (struct QTask_s *)-1;
    ptState->pfState = HumanPlayer_RunStateClimbWire;
  }
}

// source: j/0/human/humanplayer.c:11804  [anchor-mhash]
void __cdecl HumanPlayer_RunStateClimbWire(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v8; };
    struct { char igi2_o1[16]; struct real32x3_t tMove; };
    struct { char igi2_o2[32]; char zSound[36]; };
    char igi2_extent[68];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  unsigned int bSignal; // eax
  double v3; // st7
  double v4; // st7
  double v5; // st7
  struct QTask_s *ptPrev; // eax
  int v7; // ecx
  struct QReference_s *ptStatea = *(struct QReference_s * *)&ptState; // [esp+48h] [ebp+4h] ARGSLOT

  bSignal = ptState->bSignal;
  if ( (bSignal & 0x100000) != 0 )
  {
    v3 = (double)AnimController_nTicksPerFrame;
    *(_DWORD *)&ptQTask[30].eQTaskType &= ~0x100000u;
    *(_QWORD *)&igi2_frame.tMove.vX = (__int64)(v3 * 0.0);
    ptQTask[34].tQTaskChildren.ptTail[1].tQTaskRefList.ptTail = (struct QReference_s *)LODWORD(igi2_frame.tMove.vX);
    ptQTask[78].tQTaskRefList.ptTail = nullptr;
  }
  if ( !ptQTask[78].tQTaskRefList.ptTail )
  {
    if ( (bSignal & 0x80u) != 0 )
    {
      v4 = (double)AnimController_nTicksPerFrame;
      ptQTask[78].tQTaskRefList.ptTail = (struct QReference_s *)1;
      *(_QWORD *)&igi2_frame.tMove.vX = (__int64)v4;
      ptQTask[34].tQTaskChildren.ptTail[1].tQTaskRefList.ptTail = (struct QReference_s *)(__int64)v4;
    }
    if ( (bSignal & 0x100) != 0 )
    {
      v5 = (double)AnimController_nTicksPerFrame;
      ptQTask[78].tQTaskRefList.ptTail = (struct QReference_s *)-1;
      *(_QWORD *)&igi2_frame.tMove.vX = (__int64)(v5 * -1.0);
      ptQTask[34].tQTaskChildren.ptTail[1].tQTaskRefList.ptTail = (struct QReference_s *)LODWORD(igi2_frame.tMove.vX);
    }
    if ( ptQTask[78].tQTaskRefList.ptTail )
    {
      ptPrev = ptQTask[79].ptPrev;
      v7 = HumanPlayer_anClimbWireSoundSequence[(_DWORD)ptPrev];
      ptQTask[79].ptPrev = (struct QTask_s *)(((_BYTE)ptPrev - 1) & 1);
      sprintf(igi2_frame.zSound, "wire_drag_%d", v7 + 1);
      SoundSys_NewSoundFn(ptQTask[33].tQTaskChildren.ptTail, igi2_frame.zSound);
    }
  }
  ptStatea = ptQTask[78].tQTaskRefList.ptTail;
  if ( ptStatea )
  {
    igi2_frame.tMove.vX = 0.0;
    igi2_frame.tMove.vY = 1.0;
    igi2_frame.v8 = (double)(int)ptStatea * 221.86666870117188;
    igi2_frame.tMove.vZ = 0.0;
    Human_MoveFree(ptQTask, igi2_frame.v8, &igi2_frame.tMove, true);
  }
}

// source: j/0/human/humanplayer.c:11897  [anchor-mhash]
void __cdecl HumanPlayer_InitStateSlideWire(struct State_s *ptState, struct QTask_s *ptQTask)
{
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptTail; // ecx
  double v4; // st7
  double v5; // st6

  *(_DWORD *)&ptQTask[32].eQTaskType = 0;
  HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, 0, 0.0);
  ptQTask[77].tQTaskRefList.ptTail = nullptr;
  ptQTask[77].ptParent = nullptr;
  HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.4000000059604645);
  ptPrev = ptQTask[33].ptNext[1].ptPrev;
  if ( ptPrev && (ptTail = ptPrev->tQTaskChildren.ptTail) != nullptr )
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    v4 = *(float *)&ptTail[21].ptNext;
    ptQTask[77].tQTaskChildren.ptMiddle = ptTail[21].ptNext;
    v5 = *(float *)&ptQTask[43].ptParent;
    if ( v5 < 0.0 )
      v5 = -v5;
    *(float *)&ptQTask[77].tQTaskChildren.ptMiddle = v5 * *(float *)&ptTail[21].ptParent * 3.0 + v4;
  }
  else
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    ptQTask[77].tQTaskChildren.ptMiddle = nullptr;
  }
  ptQTask[38].ptPrev = nullptr;
  ptQTask[38].tQTaskChildren.ptHead = nullptr;
  ptQTask[38].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[38].tQTaskChildren.ptTail = nullptr;
  ptQTask[38].tQTaskRefList.ptHead = nullptr;
  ptQTask[38].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[37].tQTaskChildren.ptHead = nullptr;
  ptQTask[37].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[37].tQTaskChildren.ptTail = nullptr;
  ptState->pfState = HumanPlayer_RunStateSlideWire;
}

// source: j/0/human/humanplayer.c:11927  [anchor-mhash]
void __cdecl HumanPlayer_RunStateSlideWire(struct State_s *ptState, struct QTask_s *ptQTask)
{
  double v2; // st7
  double v3; // st6
  double v4; // st7
  struct QTask_s *ptHead; // edx
  double v6; // st6

  v2 = -*(float *)&ptQTask[79].tQTaskRefList.ptHead * 88.30976104736328;
  v3 = *(float *)&ptQTask[79].tQTaskRefList.ptMiddle * 0.9900000095367432;
  ptQTask[38].ptPrev = ptQTask[79].tQTaskChildren.ptMiddle;
  v4 = v2 + v3;
  ptHead = (struct QTask_s *)ptQTask[79].tQTaskRefList.ptHead;
  ptQTask[38].tQTaskChildren.ptHead = ptQTask[79].tQTaskChildren.ptTail;
  *(float *)&ptQTask[79].tQTaskRefList.ptMiddle = v4;
  ptQTask[38].tQTaskChildren.ptMiddle = ptHead;
  v6 = v4 * *(float *)&ptQTask[38].ptPrev;
  LOBYTE(ptQTask[74].ptPrev) = 1;
  *(float *)&ptQTask[38].ptPrev = v6;
  *(float *)&ptQTask[38].tQTaskChildren.ptHead = v4 * *(float *)&ptQTask[38].tQTaskChildren.ptHead;
  *(float *)&ptQTask[38].tQTaskChildren.ptMiddle = v4 * *(float *)&ptQTask[38].tQTaskChildren.ptMiddle;
}

// source: j/0/human/humanplayer.c:11968  [anchor-mhash]
void __cdecl HumanPlayer_InitStatePeek(struct State_s *ptState, struct QTask_s *ptQTask)
{
  int nState; // ebx
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptTail; // ecx
  double v5; // st7
  double v6; // st6

  if ( *(_DWORD *)&ptQTask[32].eQTaskType == 1 )
  {
    nState = 23;
  }
  else if ( *(_DWORD *)&ptQTask[32].eQTaskType == 2 )
  {
    nState = 75;
  }
  else
  {
    nState = ptState->nState;
  }
  HumanAnim_SetAnimationAndTimeFromState(ptQTask, nState, 0, 0.20000000298023224);
  ptPrev = ptQTask[33].ptNext[1].ptPrev;
  if ( ptPrev && (ptTail = ptPrev->tQTaskChildren.ptTail) != nullptr )
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    v5 = *(float *)&ptTail[21].ptNext;
    ptQTask[77].tQTaskChildren.ptMiddle = ptTail[21].ptNext;
    v6 = *(float *)&ptQTask[43].ptParent;
    if ( v6 < 0.0 )
      v6 = -v6;
    *(float *)&ptQTask[77].tQTaskChildren.ptMiddle = v6 * *(float *)&ptTail[21].ptParent * 3.0 + v5;
    ptState->pfState = HumanPlayer_RunStatePeek;
  }
  else
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    ptQTask[77].tQTaskChildren.ptMiddle = nullptr;
    ptState->pfState = HumanPlayer_RunStatePeek;
  }
}

// source: j/0/human/humanplayer.c:11995  [anchor-caller]
void __cdecl HumanPlayer_RunStatePeek(struct State_s *ptState, struct QTask_s *ptQTask)
{
  float *ptTail; // edi
  int v4; // ecx
  double vPeekOffsetX; // st7
  int v6; // eax
  int v7; // ecx
  double v8; // st7
  double vPeekOffsetZ; // st7
  double v10; // st7
  double v11; // st7
  float ptQTaska = *(float *)&ptQTask; // [esp+14h] [ebp+8h] ARGSLOT

  ptTail = (float *)ptQTask[33].tQTaskChildren.ptTail;
  HumanPlayer_MoveOnGround((struct HumanPlayer_t *)ptQTask, 0.0, 118.76579284667969, 0.0, 118.76579284667969);
  HumanPlayer_CheckBinoculars(ptQTask, true);
  v4 = 2752 * Config_tConfig.iActiveProfile + 7392072;
  if ( *(float *)&ptQTask[19].ptPrev != 0.0 )
  {
    ptTail[147] = HumanPlayer_tGeneral.vPeekOffsetX / (double)HumanPlayer_tGeneral.nPeekTime;
    vPeekOffsetX = -HumanPlayer_tGeneral.vPeekOffsetX;
    ptQTaska = *(float *)&ptQTask[19].ptPrev * 15000.0 + ptTail[144];
    if ( vPeekOffsetX <= ptQTaska )
    {
      if ( HumanPlayer_tGeneral.vPeekOffsetX >= (double)ptQTaska )
        vPeekOffsetX = ptQTaska;
      else
        vPeekOffsetX = HumanPlayer_tGeneral.vPeekOffsetX;
    }
    ptTail[144] = vPeekOffsetX;
  }
  v6 = *(_DWORD *)&ptQTask[32].eQTaskType;
  if ( (v6 == 1 || v6 == 2) && *(float *)&ptQTask[19].tQTaskChildren.ptHead != 0.0 )
  {
    ptTail[149] = HumanPlayer_tGeneral.vPeekOffsetZ / (double)HumanPlayer_tGeneral.nPeekTime;
    v7 = *(_DWORD *)(v4 + 2692);
    if ( v7 )
      v8 = 1.0;
    else
      v8 = -1.0;
    if ( v8 * *(float *)&ptQTask[19].tQTaskChildren.ptHead * 15000.0 + ptTail[146] >= 0.0 )
    {
      if ( v7 )
        v10 = 1.0;
      else
        v10 = -1.0;
      if ( v10 * *(float *)&ptQTask[19].tQTaskChildren.ptHead * 15000.0 + ptTail[146] <= HumanPlayer_tGeneral.vPeekOffsetZ )
      {
        if ( v7 )
          v11 = 1.0;
        else
          v11 = -1.0;
        vPeekOffsetZ = v11 * *(float *)&ptQTask[19].tQTaskChildren.ptHead * 15000.0 + ptTail[146];
      }
      else
      {
        vPeekOffsetZ = HumanPlayer_tGeneral.vPeekOffsetZ;
      }
    }
    else
    {
      vPeekOffsetZ = 0.0;
    }
    ptTail[146] = vPeekOffsetZ;
  }
  ptQTask[19].ptPrev = nullptr;
  ptQTask[19].tQTaskChildren.ptHead = nullptr;
}

// source: j/0/human/humanplayer.c:12114  [anchor-mhash]
void __cdecl HumanPlayer_InitStateComputer(struct State_s *ptState, struct QTask_s *ptQTask)
{
  struct QReference_s *ptHead; // eax
  struct QTask_s *pxObject; // edx
  struct QReference_s *ptMicrophoneQTaskRef; // eax
  struct QTask_s *ptTail; // esi
  void *v6; // ebx
  struct QReference_s *v7; // eax
  int v8; // ebx
  struct QTask_s *ptPrev; // eax
  struct QTask_s *v10; // ecx
  double v11; // st7
  double v12; // st6

  ptHead = ptQTask[46].tQTaskRefList.ptHead;
  if ( ptHead )
  {
    pxObject = (struct QTask_s *)ptHead->pxObject;
    if ( pxObject )
    {
      if ( QTask_IsQTaskTypeDerived(pxObject->eQTaskType, StationaryGun_eQTaskType) )
        StationaryGun_Pause(pxObject);
    }
  }
  ptMicrophoneQTaskRef = Game_ptGame->ptMicrophoneQTaskRef;
  ptTail = ptQTask[33].tQTaskChildren.ptTail;
  if ( ptMicrophoneQTaskRef )
  {
    v6 = ptMicrophoneQTaskRef->pxObject;
    if ( v6 )
    {
      v7 = *((struct QReference_s **)v6 + 38);
      if ( v7 )
      {
        QReference_Delete(v7, &QTask_tQTaskRefPool);
        *((_DWORD *)v6 + 38) = 0;
      }
      if ( ptTail )
        *((_DWORD *)v6 + 38) = QTask_NewQTaskRef(ptTail);
    }
  }
  if ( *(_DWORD *)&ptQTask[32].eQTaskType == 1 )
  {
    v8 = 23;
    goto LABEL_16;
  }
  if ( *(_DWORD *)&ptQTask[32].eQTaskType != 2 )
  {
    v8 = 0;
LABEL_16:
    HumanAnim_SetAnimationAndTimeFromState(ptQTask, v8, 0, 0.20000000298023224);
    ptQTask[77].ptParent = (struct QTask_s *)4;
    goto LABEL_17;
  }
  HumanAnim_SetAnimationAndTimeFromState(ptQTask, 75, 0, 0.20000000298023224);
LABEL_17:
  ptPrev = ptQTask[33].ptNext[1].ptPrev;
  if ( ptPrev && (v10 = ptPrev->tQTaskChildren.ptTail) != nullptr )
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    v11 = *(float *)&v10[21].ptNext;
    ptQTask[77].tQTaskChildren.ptMiddle = v10[21].ptNext;
    v12 = *(float *)&ptQTask[43].ptParent;
    if ( v12 < 0.0 )
      v12 = -v12;
    *(float *)&ptQTask[77].tQTaskChildren.ptMiddle = v12 * *(float *)&v10[21].ptParent * 3.0 + v11;
  }
  else
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    ptQTask[77].tQTaskChildren.ptMiddle = nullptr;
  }
  LOBYTE(ptQTask[33].tQTaskChildren.ptTail[12].tQTaskRefList.ptTail) = 1;
  LOBYTE(ptQTask[34].tQTaskChildren.ptMiddle) = 1;
  QTask_NewFn(ptQTask, Computer_eQTaskType, nullptr);
  ptState->pfState = HumanPlayer_RunStateComputer;
}

// source: j/0/human/humanplayer.c:12166  [anchor-caller]
void __cdecl HumanPlayer_RunStateComputer(struct State_s *ptState, struct QTask_s *ptQTask)
{
  unsigned int bSignal; // edx
  int v5; // eax
  int v6; // eax
  struct WeaponType_s *WeaponTypeFromID; // eax
  double v8; // st7
  struct WeaponType_s *v9; // edi
  struct QTask_s *ptTail; // edx
  struct QTask_s *ptPrev; // eax
  BOOL v12; // ecx
  struct QTask_s *v13; // ecx
  struct QReference_s *ptHead; // eax
  struct QTask_s *ptNext; // eax
  struct QTask_s *v16; // ecx
  struct QTask_s *v17; // ecx
  struct WeaponType_s *v18; // ecx
  struct QTask_s *v19; // eax
  struct QTask_s *v20; // eax
  struct QReference_s *ptMicrophoneQTaskRef; // eax
  void *pxObject; // edi
  struct QReference_s *v23; // eax
  void (__cdecl *v24)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v26)(struct State_s *, struct QTask_s *); // eax
  struct QReference_s *v27; // ecx
  _DWORD *v28; // eax
  void (__cdecl *v29)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v30)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v31)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v32)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v33)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v34)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v35)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v36)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v37)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v38)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v39)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v40)(struct State_s *, struct QTask_s *); // eax
  enum WeaponOverlayStatus_e v41; // [esp+0h] [ebp-14h]
  unsigned int v42; // [esp+10h] [ebp-4h]
  struct WeaponType_s *ptStatea = *(struct WeaponType_s * *)&ptState; // [esp+18h] [ebp+4h] ARGSLOT
  struct QTask_s *ptQTaska = *(struct QTask_s * *)&ptQTask; // [esp+1Ch] [ebp+8h] ARGSLOT

  HumanPlayer_MoveOnGround((struct HumanPlayer_t *)ptQTask, 0.0, 118.76579284667969, 0.0, 118.76579284667969);
  bSignal = ptState->bSignal;
  v42 = bSignal;
  if ( HumanPlayer_IsActivateComputer(ptQTask)
    || *(float *)&ptQTask[22].ptParent != 0.0
    || *(float *)&ptQTask[23].tQTaskChildren.ptTail != 0.0
    || *(float *)&ptQTask[21].tQTaskRefList.ptTail != 0.0
    || *(float *)&ptQTask[21].ptParent != 0.0
    || *(float *)&ptQTask[21].eQTaskType != 0.0
    || *(float *)&ptQTask[22].ptNext != 0.0
    || *(float *)&ptQTask[22].ptPrev != 0.0
    || *(float *)&ptQTask[22].tQTaskChildren.ptHead != 0.0
    || *(float *)&ptQTask[22].tQTaskChildren.ptMiddle != 0.0
    || *(float *)&ptQTask[22].tQTaskChildren.ptTail != 0.0
    || *(float *)&ptQTask[22].tQTaskRefList.ptHead != 0.0
    || *(float *)&ptQTask[21].tQTaskRefList.ptHead != 0.0
    || *(float *)&ptQTask[21].tQTaskRefList.ptMiddle != 0.0
    || HIBYTE(ptQTask[80].tQTaskRefList.ptMiddle)
    || (bSignal & 0x30000) != 0 )
  {
    v5 = Script_ParseLineInt32((char *)&g_zSoundDefPrefix.eQTaskType);
    ptStatea = WeaponType_GetWeaponTypeFromID(v5);
    v6 = Script_ParseLineInt32((char *)&g_zSoundDefPrefix.tQTaskChildren.ptTail);
    WeaponTypeFromID = WeaponType_GetWeaponTypeFromID(v6);
    v8 = *(float *)&ptQTask[22].tQTaskRefList.ptMiddle;
    v9 = WeaponTypeFromID;
    ptQTaska = &WeaponTypeFromID->tQTask;
    ptQTask[21].tQTaskRefList.ptHead = nullptr;
    ptQTask[21].tQTaskRefList.ptMiddle = nullptr;
    if ( v8 == 0.0 || HumanPlayer_IsActivateComputer(ptQTask) == false )
    {
      if ( *(float *)&ptQTask[23].tQTaskRefList.ptHead == 0.0 || HumanPlayer_IsActivateComputer(ptQTask) == false )
      {
        if ( *(float *)&ptQTask[23].tQTaskRefList.ptTail == 0.0 || HumanPlayer_IsActivateComputer(ptQTask) == false )
        {
          if ( *(float *)&ptQTask[23].tQTaskRefList.ptMiddle != 0.0
            && HumanPlayer_IsActivateComputer(ptQTask)
            && ComputerMenu_eActiveMenu != COMPUTERMENU_OBJECTIVES )
          {
            ComputerMenu_ptComputerMenuQTask[1].tQTaskRefList.ptTail = (struct QReference_s *)2;
            return;
          }
        }
        else if ( ComputerMenu_eActiveMenu != COMPUTERMENU_SAVE )
        {
          ComputerMenu_ptComputerMenuQTask[1].tQTaskRefList.ptTail = (struct QReference_s *)4;
          return;
        }
      }
      else if ( ComputerMenu_eActiveMenu != COMPUTERMENU_LOG )
      {
        ComputerMenu_ptComputerMenuQTask[1].tQTaskRefList.ptTail = (struct QReference_s *)3;
        return;
      }
    }
    else if ( ComputerMenu_eActiveMenu != COMPUTERMENU_MAP )
    {
      if ( Computer_isEnabled )
      {
        ComputerMenu_ptComputerMenuQTask[1].tQTaskRefList.ptTail = (struct QReference_s *)1;
        return;
      }
      if ( ComputerMenu_eActiveMenu != COMPUTERMENU_OBJECTIVES )
        return;
    }
    ptTail = ptQTask[33].tQTaskChildren.ptTail;
    HIBYTE(ptQTask[80].tQTaskRefList.ptMiddle) = 0;
    LOBYTE(ptTail[12].tQTaskRefList.ptTail) = 0;
    ptPrev = ptQTask[85].ptPrev;
    LOBYTE(ptQTask[34].tQTaskChildren.ptMiddle) = 0;
    if ( ptPrev )
    {
      v12 = Game_eGameMode != GAME_GAMEMODE_SINGLEPLAYER;
      ptQTask[85].tQTaskChildren.ptMiddle = ptPrev;
      ptQTask[85].ptPrev = nullptr;
      ptQTask[85].tQTaskChildren.ptTail = v12 ? nullptr : ptPrev;
    }
    QTask_Delete(Computer_ptComputerQTask);
    ptHead = ptQTask[86].tQTaskRefList.ptHead;
    Computer_ptComputerQTask = nullptr;
    ptQTask[38].tQTaskChildren.ptTail = nullptr;
    ptQTask[38].tQTaskRefList.ptHead = nullptr;
    ptQTask[38].tQTaskRefList.ptMiddle = nullptr;
    if ( ptHead )
    {
      Weapon_SetOverlayStatus(v13, v41, 0, (int)ptQTask[33].ptNext);
      Weapon_Fire(ptQTask[33].ptNext, 0);
      ptNext = ptQTask[33].ptNext;
      v9 = (struct WeaponType_s *)ptQTaska;
      ptNext[2].ptParent = (struct QTask_s *)1;
      ptNext[1].tQTaskChildren.ptTail = nullptr;
    }
    if ( ptStatea )
    {
      if ( v9 )
      {
        v16 = ptQTask[33].ptNext;
        if ( v16 )
        {
          if ( *(float *)&ptQTask[22].ptParent != 0.0 )
          {
            v17 = v16[1].ptPrev;
            v18 = v17 ? (struct WeaponType_s *)v17->tQTaskChildren.ptTail : nullptr;
            if ( v18 != ptStatea )
              HumanPlayer_CheckBinoculars(ptQTask, false);
          }
          if ( *(float *)&ptQTask[23].tQTaskChildren.ptTail != 0.0 )
          {
            v19 = ptQTask[33].ptNext[1].ptPrev;
            v20 = v19 ? v19->tQTaskChildren.ptTail : nullptr;
            if ( v20 != (struct QTask_s *)v9 )
              HumanPlayer_CheckBinoculars(ptQTask, false);
          }
        }
      }
    }
    ptMicrophoneQTaskRef = Game_ptGame->ptMicrophoneQTaskRef;
    if ( ptMicrophoneQTaskRef )
    {
      pxObject = ptMicrophoneQTaskRef->pxObject;
      if ( pxObject )
      {
        v23 = *((struct QReference_s **)pxObject + 38);
        if ( v23 )
        {
          QReference_Delete(v23, &QTask_tQTaskRefPool);
          *((_DWORD *)pxObject + 38) = 0;
        }
      }
    }
    if ( (v42 & 0x20000) != 0 )
    {
      v24 = ptState->apfExitState[ptState->nState];
      if ( v24 )
        v24(ptState, ptQTask);
      apfState = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 55;
      v26 = apfState[55];
      ptState->pfState = v26;
      v26(ptState, ptQTask);
    }
    else if ( ptState->nPreviousState == 41 )
    {
      v27 = ptQTask[46].tQTaskRefList.ptHead;
      v28 = nullptr;
      if ( v27 )
        v28 = v27->pxObject;
      v28[145] = ptQTask;
      v29 = ptState->apfExitState[ptState->nState];
      if ( v29 )
        v29(ptState, ptQTask);
      v30 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 41;
      v31 = v30[41];
      ptState->pfState = v31;
      v31(ptState, ptQTask);
    }
    else if ( *(_DWORD *)&ptQTask[32].eQTaskType == 1 )
    {
      v38 = ptState->apfExitState[ptState->nState];
      if ( v38 )
        v38(ptState, ptQTask);
      v39 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 23;
      v40 = v39[23];
      ptState->pfState = v40;
      v40(ptState, ptQTask);
    }
    else if ( *(_DWORD *)&ptQTask[32].eQTaskType == 2 )
    {
      v35 = ptState->apfExitState[ptState->nState];
      if ( v35 )
        v35(ptState, ptQTask);
      v36 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 75;
      v37 = v36[75];
      ptState->pfState = v37;
      v37(ptState, ptQTask);
    }
    else
    {
      v32 = ptState->apfExitState[ptState->nState];
      if ( v32 )
        v32(ptState, ptQTask);
      v33 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 0;
      v34 = *v33;
      ptState->pfState = *v33;
      v34(ptState, ptQTask);
    }
  }
}

// source: j/0/human/humanplayer.c:12306  [anchor-mhash]
void __cdecl HumanPlayer_InitStateHit(struct State_s *ptState, struct QTask_s *ptQTask)
{
  struct Game_s *v2; // eax
  unsigned int v3; // ebx
  unsigned int v4; // esi
  int v5; // edx
  int v6; // edx
  int v7; // ebx
  struct QTask_s *ptTail; // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *v10; // ecx
  double v11; // st7
  double v12; // st6

  v2 = Game_ptGame;
  v3 = (Game_ptGame->tRunRandomState.anRandom[0] >> 7)
     ^ Game_ptGame->tRunRandomState.anRandom[2]
     ^ Game_ptGame->tRunRandomState.anRandom[1];
  v4 = v3 + Game_ptGame->tRunRandomState.anRandom[0];
  Game_ptGame->tRunRandomState.anRandom[2] ^= Game_ptGame->tRunRandomState.anRandom[0] >> 7;
  v2->tRunRandomState.anRandom[0] = v4;
  v2->tRunRandomState.anRandom[1] = v3;
  v5 = *(_DWORD *)&ptQTask[32].eQTaskType;
  if ( v5 )
  {
    v6 = v5 - 1;
    if ( v6 )
    {
      if ( v6 != 1 )
        goto LABEL_8;
      v7 = 81;
    }
    else
    {
      v7 = 34;
    }
  }
  else
  {
    v7 = *((_DWORD *)&ptQTask[25].tQTaskRefList.ptTail[5 * (int)ptQTask[29].tQTaskChildren.ptHead].pxObject + v4 % 3);
  }
  HumanAnim_SetAnimationAndTimeFromState(ptQTask, v7, 0, 0.20000000298023224);
LABEL_8:
  ptTail = ptQTask[34].tQTaskChildren.ptTail;
  if ( ptTail )
    ptQTask[34].tQTaskChildren.ptTail[1].tQTaskRefList.ptTail = (struct QReference_s *)(__int64)((double)(int)ptTail[1].ptParent->tQTaskChildren.ptTail
                                                                                               * 0.00020833333837799728
                                                                                               * (double)AnimController_nTicksPerFrame
                                                                                               * 4.0);
  ptQTask[77].tQTaskRefList.ptTail = nullptr;
  ptQTask[77].ptParent = nullptr;
  HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.4000000059604645);
  ptPrev = ptQTask[33].ptNext[1].ptPrev;
  if ( ptPrev && (v10 = ptPrev->tQTaskChildren.ptTail) != nullptr )
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    v11 = *(float *)&v10[21].ptNext;
    ptQTask[77].tQTaskChildren.ptMiddle = v10[21].ptNext;
    v12 = *(float *)&ptQTask[43].ptParent;
    if ( v12 < 0.0 )
      v12 = -v12;
    *(float *)&ptQTask[77].tQTaskChildren.ptMiddle = v12 * *(float *)&v10[21].ptParent * 3.0 + v11;
    ptState->pfState = HumanPlayer_RunStateHit;
  }
  else
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    ptQTask[77].tQTaskChildren.ptMiddle = nullptr;
    ptState->pfState = HumanPlayer_RunStateHit;
  }
}

// source: j/0/human/humanplayer.c:12385  [anchor-mhash]
void __cdecl HumanPlayer_RunStateHit(struct State_s *ptState, struct QTask_s *ptQTask)
{
  unsigned int bSignal; // ebx
  void (__cdecl *v3)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v5)(struct State_s *, struct QTask_s *); // eax
  int v6; // eax
  int v7; // eax
  void (__cdecl *v8)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v9)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v10)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v11)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v12)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v13)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v14)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v15)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v16)(struct State_s *, struct QTask_s *); // eax

  bSignal = ptState->bSignal;
  HumanPlayer_MoveOnGround((struct HumanPlayer_t *)ptQTask, 0.0, 14.845724105834961, 0.0, 14.845724105834961);
  if ( (bSignal & 0x20000) != 0 )
  {
    v3 = ptState->apfExitState[ptState->nState];
    if ( v3 )
      v3(ptState, ptQTask);
    apfState = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 55;
    v5 = apfState[55];
    ptState->pfState = v5;
    v5(ptState, ptQTask);
  }
  else if ( (bSignal & 1) != 0 )
  {
    v6 = *(_DWORD *)&ptQTask[32].eQTaskType;
    if ( v6 )
    {
      v7 = v6 - 1;
      if ( v7 )
      {
        if ( v7 == 1 )
        {
          v8 = ptState->apfExitState[ptState->nState];
          if ( v8 )
            v8(ptState, ptQTask);
          v9 = ptState->apfState;
          ptState->nPreviousState = ptState->nState;
          ptState->nState = 75;
          v10 = v9[75];
          ptState->pfState = v10;
          v10(ptState, ptQTask);
        }
      }
      else
      {
        v11 = ptState->apfExitState[ptState->nState];
        if ( v11 )
          v11(ptState, ptQTask);
        v12 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 23;
        v13 = v12[23];
        ptState->pfState = v13;
        v13(ptState, ptQTask);
      }
    }
    else
    {
      v14 = ptState->apfExitState[ptState->nState];
      if ( v14 )
        v14(ptState, ptQTask);
      v15 = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 0;
      v16 = *v15;
      ptState->pfState = v16;
      v16(ptState, ptQTask);
    }
  }
}

// source: j/0/human/humanplayer.c:12432  [anchor-strings]
void __cdecl HumanPlayer_InitStateDie(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { enum WeaponOverlayStatus_e v19; };
    struct { char igi2_o1[16]; _DWORD v20[6]; };
    struct { char igi2_o2[40]; _DWORD v21[8]; };
    char igi2_extent[72];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v2; // ecx
  struct QTask_s *ptNext; // edi
  int nPreviousState; // eax
  int v5; // eax
  int v6; // eax
  unsigned int RandomNumberBelowLimit; // eax
  unsigned int v8; // eax
  int v9; // ebx
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptTail; // ecx
  double v12; // st7
  double v13; // st6
  struct QTask_s *v14; // edx
  struct QTask_s *v15; // eax
  struct QTask_s *v16; // eax
  struct QTask_s *ptParent; // edx
  struct QTask_s *v18; // eax

  ptNext = ptQTask[33].ptNext;
  igi2_frame.v21[0] = 92;
  igi2_frame.v21[1] = 93;
  igi2_frame.v21[2] = 94;
  igi2_frame.v21[3] = 95;
  igi2_frame.v21[4] = 96;
  igi2_frame.v21[5] = 97;
  igi2_frame.v21[6] = 98;
  igi2_frame.v21[7] = 99;
  igi2_frame.v20[0] = 100;
  igi2_frame.v20[1] = 101;
  igi2_frame.v20[2] = 102;
  igi2_frame.v20[3] = 103;
  igi2_frame.v20[4] = 104;
  igi2_frame.v20[5] = 105;
  Weapon_SetOverlayStatus(v2, igi2_frame.v19, 0, (int)ptNext);
  nPreviousState = ptState->nPreviousState;
  if ( nPreviousState == 19 || nPreviousState == 21 )
  {
    v9 = 22;
    goto LABEL_13;
  }
  if ( nPreviousState == 37 || nPreviousState == 36 )
  {
    v9 = 106;
LABEL_13:
    HumanAnim_SetAnimationAndTimeFromState(ptQTask, v9, 0, 0.20000000298023224);
    goto LABEL_14;
  }
  v5 = *(_DWORD *)&ptQTask[32].eQTaskType;
  if ( v5 )
  {
    v6 = v5 - 1;
    if ( v6 )
    {
      if ( v6 == 1 )
        HumanAnim_SetAnimationAndTimeFromState(ptQTask, 82, 0, 0.20000000298023224);
    }
    else
    {
      RandomNumberBelowLimit = Random_GetRandomNumberBelowLimit(&Game_ptGame->tRunRandomState, 6);
      HumanAnim_SetAnimationAndTimeFromState(ptQTask, igi2_frame.v20[RandomNumberBelowLimit], 0, 0.20000000298023224);
    }
  }
  else
  {
    v8 = Random_GetRandomNumberBelowLimit(&Game_ptGame->tRunRandomState, 8);
    HumanAnim_SetAnimationAndTimeFromState(ptQTask, igi2_frame.v21[v8], 0, 0.20000000298023224);
  }
LABEL_14:
  *(_DWORD *)&ptQTask[32].eQTaskType = 0;
  ptQTask[77].tQTaskRefList.ptTail = nullptr;
  ptQTask[77].ptParent = nullptr;
  HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.4000000059604645);
  ptPrev = ptQTask[33].ptNext[1].ptPrev;
  if ( ptPrev && (ptTail = ptPrev->tQTaskChildren.ptTail) != nullptr )
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    v12 = *(float *)&ptTail[21].ptNext;
    ptQTask[77].tQTaskChildren.ptMiddle = ptTail[21].ptNext;
    v13 = *(float *)&ptQTask[43].ptParent;
    if ( v13 < 0.0 )
      v13 = -v13;
    *(float *)&ptQTask[77].tQTaskChildren.ptMiddle = v13 * *(float *)&ptTail[21].ptParent * 3.0 + v12;
  }
  else
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    ptQTask[77].tQTaskChildren.ptMiddle = nullptr;
  }
  v14 = ptQTask[33].tQTaskChildren.ptTail;
  LOBYTE(ptQTask[36].tQTaskRefList.ptMiddle) = 0;
  LOBYTE(ptQTask[76].tQTaskRefList.ptMiddle) = 1;
  ptQTask[33].tQTaskRefList.ptHead = (struct QReference_s *)5;
  LOBYTE(v14[12].tQTaskRefList.ptTail) = 1;
  v15 = ptQTask[33].ptNext;
  LOBYTE(ptQTask[34].tQTaskChildren.ptMiddle) = 1;
  v15[2].ptParent = (struct QTask_s *)1;
  v15[1].tQTaskChildren.ptTail = nullptr;
  v16 = ptQTask[33].ptNext;
  v16[3].tQTaskRefList.ptHead = (struct QReference_s *)1;
  v16[1].tQTaskChildren.ptTail = nullptr;
  Human_PlayDeathSound(ptQTask, (char *)&g_zSoundDefPrefix, 3);
  ptParent = ptQTask[38].ptParent;
  v18 = *(struct QTask_s **)&ptQTask[38].eQTaskType;
  ptQTask[38].ptPrev = (struct QTask_s *)ptQTask[38].tQTaskRefList.ptTail;
  ptQTask[38].tQTaskChildren.ptHead = ptParent;
  ptQTask[38].tQTaskChildren.ptMiddle = v18;
  ptState->pfState = HumanPlayer_RunStateDie;
}

// source: j/0/human/humanplayer.c:12578  [anchor-mhash]
void __cdecl HumanPlayer_RunStateDie(struct State_s *ptState, struct QTask_s *ptQTask)
{
  unsigned int bSignal; // ebx
  int nPreviousState; // ecx

  bSignal = ptState->bSignal;
  if ( (bSignal & 1) != 0 )
    LOBYTE(ptQTask[32].tQTaskRefList.ptTail) = 1;
  nPreviousState = ptState->nPreviousState;
  if ( nPreviousState == 19 || nPreviousState == 21 )
  {
    if ( (bSignal & 1) == 0 )
      return;
  }
  else
  {
    HumanPlayer_InAirControl(ptQTask);
    if ( (bSignal & 2) == 0 && !BYTE2(ptQTask[50].ptNext) )
      return;
    ptQTask[38].ptPrev = nullptr;
    ptQTask[38].tQTaskChildren.ptHead = nullptr;
    ptQTask[38].tQTaskChildren.ptMiddle = nullptr;
    ptQTask[38].tQTaskChildren.ptTail = nullptr;
    ptQTask[38].tQTaskRefList.ptHead = nullptr;
    ptQTask[38].tQTaskRefList.ptMiddle = nullptr;
  }
  if ( Game_eGameMode == GAME_GAMEMODE_SINGLEPLAYER )
    Weapon_ClearAllWeapons(ptQTask[33].ptNext);
  ptState->pfState = HumanPlayer_RunStateDie2;
}

// source: j/0/human/humanplayer.c:12629  [anchor-caller]
void __cdecl HumanPlayer_RunStateDie2(struct State_s *ptState, struct QTask_s *ptQTask)
{
  struct QTask_s *v2; // esi
  enum NetManagerMode_e v3; // ebp
  char *LocalizedStringForLanguage; // eax
  struct Client_s *ClientFromNetworkID; // eax

  if ( (ptState->bSignal & 1) != 0 )
    LOBYTE(ptQTask[32].tQTaskRefList.ptTail) = 1;
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    v2 = MenuManager_ptQTask;
    if ( MenuManager_ptQTask && MenuManager_ptQTask[1].tQTaskChildren.ptMiddle != (struct QTask_s *)10
      || NetManager_eMode == NETMANAGER_MODE_COMPLETE )
    {
LABEL_17:
      ptState->pfState = HumanPlayer_RunStateNetworkWait;
    }
    else
    {
      v3 = NETMANAGER_MODE_DEAD;
      if ( BYTE2(Flow_ptFlow->ptNetManagerQTask[5].tQTaskChildren.ptTail) )
      {
        if ( NetManager_ForceChangeTeam() )
        {
          LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                         "mp/FORCE_TEAM_CHANGE",
                                         Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                         true);
          StatusScreen_ShowMessage(LocalizedStringForLanguage, TEXTSCROLLER_COLOUR_WHITE);
          v3 = NETMANAGER_MODE_SELECTSKIN;
          NetManager_nBodySprite = 0;
          NetManager_nFaceSprite = 0;
          NetManager_isModelSelect = true;
        }
        v2 = MenuManager_ptQTask;
      }
      ClientFromNetworkID = NetManager_GetClientFromNetworkID((int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
      if ( ClientFromNetworkID )
        NetManager_eTeam = ClientFromNetworkID->eTeam;
      NetManager_eMode = v3;
      LOBYTE(v2[243].eQTaskType) = 1;
      switch ( v3 )
      {
        case NETMANAGER_MODE_SELECTSKIN:
          if ( !LOBYTE(HumanPlayer_ptQTask[29].tQTaskRefList.ptHead) )
          {
            NetManager_KillClient((int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
            v2 = MenuManager_ptQTask;
          }
          v2[1].ptNext = (struct QTask_s *)996;
          v2[1].tQTaskChildren.ptMiddle = nullptr;
          ptState->pfState = HumanPlayer_RunStateNetworkWait;
          break;
        default:
          goto LABEL_17;
      }
    }
  }
}

// source: j/0/human/humanplayer.c:12667  [anchor-mhash]
void __cdecl HumanPlayer_InitStateNetworkWait(struct State_s *ptState, struct QTask_s *ptQTask)
{
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptTail; // ecx
  double v4; // st7
  double v5; // st6

  *(_DWORD *)&ptQTask[32].eQTaskType = 0;
  HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, 0, 0.20000000298023224);
  ptQTask[77].tQTaskRefList.ptTail = nullptr;
  ptQTask[77].ptParent = nullptr;
  HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.4000000059604645);
  ptPrev = ptQTask[33].ptNext[1].ptPrev;
  if ( ptPrev && (ptTail = ptPrev->tQTaskChildren.ptTail) != nullptr )
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    v4 = *(float *)&ptTail[21].ptNext;
    ptQTask[77].tQTaskChildren.ptMiddle = ptTail[21].ptNext;
    v5 = *(float *)&ptQTask[43].ptParent;
    if ( v5 < 0.0 )
      v5 = -v5;
    *(float *)&ptQTask[77].tQTaskChildren.ptMiddle = v5 * *(float *)&ptTail[21].ptParent * 3.0 + v4;
    ptState->pfState = HumanPlayer_RunStateNetworkWait;
  }
  else
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    ptQTask[77].tQTaskChildren.ptMiddle = nullptr;
    ptState->pfState = HumanPlayer_RunStateNetworkWait;
  }
}

// source: j/0/human/humanplayer.c:12689  [anchor-mhash]
void __cdecl HumanPlayer_RunStateNetworkWait(struct State_s *ptState, struct QTask_s *ptQTask)
{
  int bEdgeButton; // ecx
  struct QTask_s *ptNetManagerQTask; // esi

  bEdgeButton = InputPort_atInputPort[0].tInput.bEdgeButton;
  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  if ( (InputPort_atInputPort[0].tInput.bEdgeButton & 0x80000) != 0 )
  {
    if ( NetManager_eMode == NETMANAGER_MODE_DEAD )
    {
      if ( (int)ptNetManagerQTask[7].ptPrev <= 60
        || MenuManager_ptQTask && MenuManager_ptQTask[1].tQTaskChildren.ptMiddle != (struct QTask_s *)10 )
      {
        return;
      }
      NetManager_SetMode(2);
      ptNetManagerQTask[7].ptPrev = nullptr;
      goto LABEL_11;
    }
    if ( NetManager_eMode == NETMANAGER_MODE_WELCOME )
    {
      if ( MenuManager_ptQTask && MenuManager_ptQTask[1].tQTaskChildren.ptMiddle != (struct QTask_s *)10 )
        return;
      NetManager_SetMode(0);
LABEL_11:
      bEdgeButton = InputPort_atInputPort[0].tInput.bEdgeButton;
    }
  }
  if ( NetManager_eMode == NETMANAGER_MODE_SPAWN && ((bEdgeButton & 0x100000) != 0 || NetMission_eCurrentObjective <= 0) )
    NetManager_SetMode(2);
}

// source: j/0/human/humanplayer.c:12765  [anchor-mhash]
void __cdecl HumanPlayer_InitStateFly(struct State_s *ptState, struct QTask_s *ptQTask)
{
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptTail; // ecx
  double v4; // st7
  double v5; // st6
  struct QReference_s *ptMiddle; // eax
  unsigned int v7; // edx

  *(_DWORD *)&ptQTask[32].eQTaskType = 0;
  HumanAnim_SetAnimationAndTimeFromState(ptQTask, ptState->nState, 0, 0.20000000298023224);
  ptPrev = ptQTask[33].ptNext[1].ptPrev;
  if ( ptPrev && (ptTail = ptPrev->tQTaskChildren.ptTail) != nullptr )
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    v4 = *(float *)&ptTail[21].ptNext;
    ptQTask[77].tQTaskChildren.ptMiddle = ptTail[21].ptNext;
    v5 = *(float *)&ptQTask[43].ptParent;
    if ( v5 < 0.0 )
      v5 = -v5;
    *(float *)&ptQTask[77].tQTaskChildren.ptMiddle = v5 * *(float *)&ptTail[21].ptParent * 3.0 + v4;
  }
  else
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    ptQTask[77].tQTaskChildren.ptMiddle = nullptr;
  }
  ptMiddle = ptQTask[44].tQTaskRefList.ptMiddle;
  v7 = *(_DWORD *)&ptQTask[30].eQTaskType & 0xFFFFFFFD;
  ptQTask[38].ptPrev = nullptr;
  ptQTask[38].tQTaskChildren.ptHead = nullptr;
  ptQTask[38].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[38].tQTaskChildren.ptTail = nullptr;
  ptQTask[38].tQTaskRefList.ptHead = nullptr;
  ptQTask[38].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[37].tQTaskChildren.ptHead = nullptr;
  ptQTask[37].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[37].tQTaskChildren.ptTail = nullptr;
  *(_DWORD *)&ptQTask[30].eQTaskType = v7;
  if ( ptMiddle && ptMiddle->pxObject )
  {
    QReference_Delete(ptMiddle, &QTask_tQTaskRefPool);
    ptQTask[44].tQTaskRefList.ptMiddle = nullptr;
    HIBYTE(ptQTask[74].ptPrev) = 0;
  }
  *(_DWORD *)&ptQTask[42].eQTaskType = 0;
  ptState->pfState = HumanPlayer_RunStateFly;
}

// source: j/0/human/humanplayer.c:12795  [anchor-mhash]
void __cdecl HumanPlayer_RunStateFly(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[16]; float tDirection_4; };
    struct { char igi2_o2[20]; float tDirection_8; };
    struct { char igi2_o3[20]; float tDirection_8a; };
    struct { char igi2_o4[24]; struct real64x3_t tPos; };
    struct { char igi2_o5[48]; struct real32x9_t tOrientation; };
    char igi2_extent[88];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double vY; // st7
  unsigned int bSignal; // eax
  double v5; // st6
  double v6; // st5
  long double v7; // st7
  long double v8; // rt1
  long double v9; // st5
  double v10; // st6
  struct World_s *ptWorld; // ecx
  float ptQTaska = *(float *)&ptQTask; // [esp+60h] [ebp+8h] ARGSLOT

  vY = 0.0;
  bSignal = ptState->bSignal;
  qmemcpy(&igi2_frame.tOrientation, &ptQTask[33].tQTaskChildren.ptTail[10].ptParent, sizeof(igi2_frame.tOrientation));
  igi2_frame.tDirection_4 = 0.0;
  igi2_frame.tDirection_8 = 0.0;
  if ( (bSignal & 0x80u) != 0 )
  {
    vY = igi2_frame.tOrientation.tX.vY;
    igi2_frame.tDirection_4 = igi2_frame.tOrientation.tY.vY;
    igi2_frame.tDirection_8 = igi2_frame.tOrientation.tZ.vY;
  }
  if ( (bSignal & 0x100) != 0 )
  {
    *((float *)&igi2_frame.tPos.vX + 1) = -igi2_frame.tOrientation.tY.vY;
    *(float *)&igi2_frame.tPos.vY = -igi2_frame.tOrientation.tZ.vY;
    vY = vY - igi2_frame.tOrientation.tX.vY;
    igi2_frame.tDirection_4 = *((float *)&igi2_frame.tPos.vX + 1) + igi2_frame.tDirection_4;
    igi2_frame.tDirection_8 = *(float *)&igi2_frame.tPos.vY + igi2_frame.tDirection_8;
  }
  if ( (bSignal & 0x40) != 0 )
  {
    vY = vY + igi2_frame.tOrientation.tX.vX;
    igi2_frame.tDirection_4 = igi2_frame.tOrientation.tY.vX + igi2_frame.tDirection_4;
    igi2_frame.tDirection_8 = igi2_frame.tOrientation.tZ.vX + igi2_frame.tDirection_8;
  }
  if ( (bSignal & 0x20) != 0 )
  {
    *((float *)&igi2_frame.tPos.vX + 1) = -igi2_frame.tOrientation.tY.vX;
    *(float *)&igi2_frame.tPos.vY = -igi2_frame.tOrientation.tZ.vX;
    vY = vY - igi2_frame.tOrientation.tX.vX;
    igi2_frame.tDirection_4 = *((float *)&igi2_frame.tPos.vX + 1) + igi2_frame.tDirection_4;
    igi2_frame.tDirection_8 = *(float *)&igi2_frame.tPos.vY + igi2_frame.tDirection_8;
  }
  if ( (bSignal & 0x7000) != 0 )
    v5 = 10.0;
  else
    v5 = 1.0;
  if ( vY != 0.0 || igi2_frame.tDirection_4 != 0.0 || igi2_frame.tDirection_8 != 0.0 )
  {
    qmemcpy(&igi2_frame.tPos, &ptQTask[1], sizeof(igi2_frame.tPos));
    if ( vY != 0.0 || igi2_frame.tDirection_4 != 0.0 || igi2_frame.tDirection_8 != 0.0 )
    {
      v6 = vY;
      v7 = 1.0 / sqrt(vY * vY + igi2_frame.tDirection_4 * igi2_frame.tDirection_4 + igi2_frame.tDirection_8 * igi2_frame.tDirection_8);
      v8 = v6 * v7;
      v9 = v7;
      vY = v8;
      igi2_frame.tDirection_4 = igi2_frame.tDirection_4 * v9;
      igi2_frame.tDirection_8 = igi2_frame.tDirection_8 * v9;
    }
    v10 = v5 * 1638.4;
    ptWorld = Game_ptGame->ptWorld;
    ptQTaska = v10;
    igi2_frame.tDirection_8a = ptQTaska * igi2_frame.tDirection_8;
    igi2_frame.tPos.vX = vY * v10 + igi2_frame.tPos.vX;
    igi2_frame.tPos.vY = ptQTaska * igi2_frame.tDirection_4 + igi2_frame.tPos.vY;
    igi2_frame.tPos.vZ = igi2_frame.tDirection_8a + igi2_frame.tPos.vZ;
    igi2_frame.ptDynCubeObj = sqrt(
                     *(float *)&ptQTask[7].tQTaskChildren.ptTail * *(float *)&ptQTask[7].tQTaskChildren.ptTail
                   + *(float *)&ptQTask[7].tQTaskRefList.ptHead * *(float *)&ptQTask[7].tQTaskRefList.ptHead
                   + *(float *)&ptQTask[7].tQTaskRefList.ptMiddle * *(float *)&ptQTask[7].tQTaskRefList.ptMiddle)
                 + *(float *)&ptQTask[8].ptNext;
    World_MoveDynCubeObjRadius(ptWorld, (struct DynCubeObj_s *)ptQTask, &igi2_frame.tPos, igi2_frame.ptDynCubeObj);
  }
}

// source: j/0/human/humanplayer.c:12902  [anchor-mhash]
void __cdecl HumanPlayer_InitStateFlat(struct State_s *ptState, struct QTask_s *ptQTask)
{
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptTail; // ecx
  double v4; // st7
  double v5; // st6

  if ( *(_DWORD *)&ptQTask[32].eQTaskType != 2 )
    HumanPlayer_LeaveZoomAlternateFireMode(ptQTask);
  *(_DWORD *)&ptQTask[32].eQTaskType = 2;
  HumanAnim_SetAnimationAndTimeFromState(ptQTask, 75, 0, 0.20000000298023224);
  ptQTask[77].tQTaskRefList.ptTail = nullptr;
  ptQTask[77].ptParent = nullptr;
  HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.4000000059604645);
  ptPrev = ptQTask[33].ptNext[1].ptPrev;
  if ( ptPrev && (ptTail = ptPrev->tQTaskChildren.ptTail) != nullptr )
  {
    ptQTask[77].tQTaskChildren.ptHead = (struct QTask_s *)5;
    v4 = *(float *)&ptTail[21].tQTaskRefList.ptHead;
    ptQTask[77].tQTaskChildren.ptMiddle = (struct QTask_s *)ptTail[21].tQTaskRefList.ptHead;
    v5 = *(float *)&ptQTask[43].ptParent;
    if ( v5 < 0.0 )
      v5 = -v5;
    *(float *)&ptQTask[77].tQTaskChildren.ptMiddle = v5 * *(float *)&ptTail[21].ptParent * 3.0 + v4;
  }
  else
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    ptQTask[77].tQTaskChildren.ptMiddle = nullptr;
  }
  qmemcpy(&ptQTask[82].tQTaskRefList, &ptQTask[3].ptPrev, sizeof(struct QTask_s));
  HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
  ptQTask[49].tQTaskRefList.ptTail = (struct QReference_s *)1157627904;
  ptState->pfState = HumanPlayer_RunStateFlat;
}

// source: j/0/human/humanplayer.c:12937  [anchor-mhash]
void __cdecl HumanPlayer_RunStateFlat(struct State_s *ptState, struct QTask_s *ptQTask)
{
  unsigned int bSignal; // ebx
  int v3; // ebx
  char ptPrev; // al
  void (__cdecl *v5)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v7)(struct State_s *, struct QTask_s *); // ebx

  bSignal = ptState->bSignal;
  HumanPlayer_MoveOnGround((struct HumanPlayer_t *)ptQTask, 0.0, 890.743408203125, 0.0, 890.743408203125);
  if ( (bSignal & 2) == 0 )
  {
    v3 = 37;
    goto LABEL_17;
  }
  ptPrev = (char)ptQTask[50].ptPrev;
  if ( (ptPrev & 4) == 0 )
  {
    if ( (ptPrev & 2) != 0 )
    {
      ptQTask[83].tQTaskRefList.ptHead = nullptr;
      v3 = 23;
      goto LABEL_17;
    }
LABEL_8:
    v3 = 0;
    goto LABEL_17;
  }
  if ( (bSignal & 0x10000000) != 0 && (ptPrev & 1) != 0 )
    goto LABEL_8;
  if ( (bSignal & 0x2000000) != 0 && (ptPrev & 2) != 0 )
  {
    ptQTask[83].tQTaskRefList.ptHead = nullptr;
    v3 = 23;
  }
  else if ( (bSignal & 0x20000) != 0 )
  {
    v3 = 55;
  }
  else
  {
    if ( (bSignal & 0x80001E0) == 0 || ptQTask[75].ptPrev != (struct QTask_s *)1 )
      return;
    v3 = 80;
  }
LABEL_17:
  ptQTask[49].tQTaskRefList.ptTail = (struct QReference_s *)1145883853;
  v5 = ptState->apfExitState[ptState->nState];
  if ( v5 )
    v5(ptState, ptQTask);
  apfState = ptState->apfState;
  ptState->nPreviousState = ptState->nState;
  ptState->nState = v3;
  v7 = apfState[v3];
  ptState->pfState = v7;
  v7(ptState, ptQTask);
}

// source: j/0/human/humanplayer.c:13018  [anchor-mhash]
void __cdecl HumanPlayer_InitStateFlatCrawl(struct State_s *ptState, struct QTask_s *ptQTask)
{
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptTail; // ecx
  double v4; // st7
  double v5; // st6

  *(_DWORD *)&ptQTask[32].eQTaskType = 2;
  HumanAnim_SetAnimationAndTimeFromState(ptQTask, 80, 0, 0.20000000298023224);
  ptPrev = ptQTask[33].ptNext[1].ptPrev;
  if ( ptPrev && (ptTail = ptPrev->tQTaskChildren.ptTail) != nullptr )
  {
    ptQTask[77].tQTaskChildren.ptHead = (struct QTask_s *)5;
    v4 = *(float *)&ptTail[21].tQTaskRefList.ptHead;
    ptQTask[77].tQTaskChildren.ptMiddle = (struct QTask_s *)ptTail[21].tQTaskRefList.ptHead;
    v5 = *(float *)&ptQTask[43].ptParent;
    if ( v5 < 0.0 )
      v5 = -v5;
    *(float *)&ptQTask[77].tQTaskChildren.ptMiddle = v5 * *(float *)&ptTail[21].ptParent * 3.0 + v4;
  }
  else
  {
    ptQTask[77].tQTaskChildren.ptHead = nullptr;
    ptQTask[77].tQTaskChildren.ptMiddle = nullptr;
  }
  ptQTask[82].tQTaskChildren.ptTail = nullptr;
  ptQTask[49].tQTaskRefList.ptTail = (struct QReference_s *)1157627904;
  ptState->pfState = HumanPlayer_RunStateFlatCrawl;
}

// source: j/0/human/humanplayer.c:13046  [anchor-strings]
void __cdecl HumanPlayer_RunStateFlatCrawl(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptHumanPlayer; };
    struct { char igi2_o1[8]; float vMaxYDelta; };
    struct { char igi2_o2[32]; int iSwitchToState; };
    struct { char igi2_o3[36]; struct QTask_s *ptCrawlSound; };
    struct { char igi2_o4[40]; struct real32x2_t avXYSpeed[16]; };
    char igi2_extent[168];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  unsigned int bSignal; // ebx
  struct QTask_s *ptTail; // eax
  struct QReference_s **p_ptTail; // esi
  struct QTask_s *ptHead; // eax
  struct QTask_s *ptPrev; // eax
  float *v7; // ecx
  double v8; // st7
  double v9; // st6
  char v10; // al
  int v11; // eax
  int v12; // ecx
  int v13; // ebx
  struct QTask_s *v14; // eax
  void (__cdecl *v15)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v16)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v17)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v18)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // eax

  bSignal = ptState->bSignal;
  ptTail = ptQTask[82].tQTaskChildren.ptTail;
  p_ptTail = (struct QReference_s **)&ptQTask[82].tQTaskChildren.ptTail;
  igi2_frame.iSwitchToState = -1;
  if ( ptTail )
  {
    ptHead = ptTail->tQTaskChildren.ptHead;
    igi2_frame.ptCrawlSound = ptHead;
    if ( ptHead )
      ((void (__cdecl *)(struct QTask_s *, struct QTask_s *))QTask_aatQTaskFinalEvent[SoundSys_eSetPositionQTaskEvent][ptHead->eQTaskType].pfHandler)(
        ptHead,
        &ptQTask[1]);
  }
  else
  {
    igi2_frame.ptCrawlSound = nullptr;
  }
  ptPrev = ptQTask[33].ptNext[1].ptPrev;
  if ( (bSignal & 0x1E0) != 0 )
  {
    if ( !ptPrev || (v7 = (float *)ptPrev->tQTaskChildren.ptTail) == nullptr )
    {
      ptQTask[77].tQTaskChildren.ptHead = nullptr;
      ptQTask[77].tQTaskChildren.ptMiddle = nullptr;
      goto LABEL_17;
    }
    ptQTask[77].tQTaskChildren.ptHead = (struct QTask_s *)6;
    v8 = v7[216];
  }
  else
  {
    if ( !ptPrev || (v7 = (float *)ptPrev->tQTaskChildren.ptTail) == nullptr )
    {
      ptQTask[77].tQTaskChildren.ptHead = nullptr;
      ptQTask[77].tQTaskChildren.ptMiddle = nullptr;
      goto LABEL_17;
    }
    ptQTask[77].tQTaskChildren.ptHead = (struct QTask_s *)5;
    v8 = v7[215];
  }
  *(float *)&ptQTask[77].tQTaskChildren.ptMiddle = v8;
  v9 = *(float *)&ptQTask[43].ptParent;
  if ( v9 < 0.0 )
    v9 = -v9;
  *(float *)&ptQTask[77].tQTaskChildren.ptMiddle = v9 * v7[218] * 3.0 + v8;
LABEL_17:
  if ( (bSignal & 0x20000) != 0 )
  {
    igi2_frame.iSwitchToState = 55;
    goto LABEL_43;
  }
  if ( (bSignal & 2) == 0 )
  {
    igi2_frame.iSwitchToState = 37;
    goto LABEL_43;
  }
  v10 = (char)ptQTask[50].ptPrev;
  if ( ((v10 == 0) & 4) != 0 )
  {
    if ( (v10 & 2) != 0 )
    {
      igi2_frame.iSwitchToState = 23;
      ptQTask[83].tQTaskRefList.ptHead = nullptr;
      goto LABEL_43;
    }
LABEL_29:
    igi2_frame.iSwitchToState = 0;
    goto LABEL_43;
  }
  if ( (bSignal & 0x2000000) != 0 && (v10 & 2) != 0 )
  {
    ptQTask[83].tQTaskRefList.ptHead = nullptr;
    igi2_frame.iSwitchToState = 23;
    goto LABEL_43;
  }
  if ( (bSignal & 0x10000000) != 0 && (v10 & 1) != 0 )
    goto LABEL_29;
  if ( (bSignal & 0xA00) != 0 )
  {
    igi2_frame.iSwitchToState = 75;
  }
  else if ( (bSignal & 0x80001E0) != 0 )
  {
    v11 = ((bSignal >> 5) & 1) + 2 * ((bSignal >> 6) & 1);
    v12 = ((bSignal >> 8) & 1) + 2 * ((bSignal >> 7) & 1);
    igi2_frame.avXYSpeed[0].vX = 0.0;
    igi2_frame.avXYSpeed[0].vY = 0.0;
    igi2_frame.avXYSpeed[1].vX = -136.53334045410156;
    igi2_frame.avXYSpeed[1].vY = 0.0;
    igi2_frame.avXYSpeed[2].vX = 136.53334045410156;
    igi2_frame.avXYSpeed[2].vY = 0.0;
    memset(&igi2_frame.avXYSpeed[3], 0, 12);
    igi2_frame.avXYSpeed[4].vY = -136.53334045410156;
    igi2_frame.avXYSpeed[5].vX = -136.53334045410156;
    igi2_frame.avXYSpeed[5].vY = -136.53334045410156;
    igi2_frame.avXYSpeed[6].vX = 136.53334045410156;
    igi2_frame.avXYSpeed[6].vY = -136.53334045410156;
    memset(&igi2_frame.avXYSpeed[7], 0, 12);
    igi2_frame.avXYSpeed[8].vY = 136.53334045410156;
    igi2_frame.avXYSpeed[9].vX = -136.53334045410156;
    igi2_frame.avXYSpeed[9].vY = 136.53334045410156;
    igi2_frame.avXYSpeed[10].vX = 136.53334045410156;
    igi2_frame.avXYSpeed[10].vY = 136.53334045410156;
    memset(&igi2_frame.avXYSpeed[11], 0, 40);
    v13 = v11 + 4 * v12;
    if ( v11 || v12 )
    {
      if ( !igi2_frame.ptCrawlSound )
      {
        if ( *p_ptTail )
        {
          QReference_Delete(*p_ptTail, &QTask_tQTaskRefPool);
          *p_ptTail = nullptr;
        }
        v14 = SoundSys_NewSoundFn(ptQTask[33].tQTaskChildren.ptTail, "crawl_loop");
        *p_ptTail = QTask_NewQTaskRef(v14);
      }
    }
    else if ( igi2_frame.ptCrawlSound )
    {
      QTask_DeleteQTaskAndQTaskRefSafe(p_ptTail);
    }
    igi2_frame.vMaxYDelta = igi2_frame.avXYSpeed[v13].vX * *(float *)&ptQTask[81].ptNext;
    igi2_frame.ptHumanPlayer = igi2_frame.avXYSpeed[v13].vY * *(float *)&ptQTask[81].ptNext;
    HumanPlayer_MoveOnGround((struct HumanPlayer_t *)ptQTask, igi2_frame.ptHumanPlayer, 27.30666732788086, igi2_frame.vMaxYDelta, 27.30666732788086);
  }
  else
  {
    igi2_frame.iSwitchToState = 75;
  }
LABEL_43:
  if ( *(float *)&ptQTask[51].tQTaskRefList.ptMiddle < 819.2000122070312 )
  {
    if ( igi2_frame.iSwitchToState == -1 )
      return;
    v18 = ptState->apfExitState[ptState->nState];
    if ( v18 )
      v18(ptState, ptQTask);
    apfState = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = igi2_frame.iSwitchToState;
    v17 = apfState[igi2_frame.iSwitchToState];
  }
  else
  {
    v15 = ptState->apfExitState[ptState->nState];
    if ( v15 )
      v15(ptState, ptQTask);
    v16 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 0;
    v17 = *v16;
  }
  ptState->pfState = v17;
  v17(ptState, ptQTask);
}

// source: j/0/human/humanplayer.c:13196  [size]
void __cdecl HumanPlayer_ExitStateFlatCrawl(struct State_s *ptState, struct QTask_s *ptQTask)
{
  ptQTask[49].tQTaskRefList.ptTail = (struct QReference_s *)1145883853;
  QTask_DeleteQTaskAndQTaskRefSafe((struct QReference_s **)&ptQTask[82].tQTaskChildren.ptTail);
}

// source: j/0/human/humanplayer.c:13215  [anchor-mhash]
void __cdecl HumanPlayer_ActionSignalHandler(struct State_s *ptState, struct QTask_s *ptQTask)
{
  unsigned int v2; // edx
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptTail; // esi

  v2 = ptState->bSignal & 0xC8F7001E;
  if ( ((int)ptQTask[33].tQTaskChildren.ptTail[16].tQTaskRefList.ptTail[3].pxObject & 4) != 0 )
    v2 |= 1u;
  if ( *(float *)&ptQTask[19].tQTaskChildren.ptMiddle != 0.0 )
    v2 |= 0x20u;
  if ( *(float *)&ptQTask[19].tQTaskChildren.ptTail != 0.0 )
    v2 |= 0x40u;
  if ( *(float *)&ptQTask[19].tQTaskRefList.ptHead != 0.0 )
    v2 |= 0x80u;
  if ( *(float *)&ptQTask[19].tQTaskRefList.ptMiddle != 0.0 )
    v2 |= 0x100u;
  if ( *(float *)&ptQTask[19].tQTaskRefList.ptTail != 0.0 )
    v2 |= 0x200u;
  if ( *(float *)&ptQTask[19].ptParent != 0.0 )
  {
    ptNext = ptQTask[33].ptNext;
    if ( ptNext
      && (ptPrev = ptNext[1].ptPrev) != nullptr
      && (ptTail = ptPrev->tQTaskChildren.ptTail) != nullptr
      && ptTail[16].ptParent == (struct QTask_s *)10 )
    {
      ptQTask[19].ptParent = nullptr;
    }
    else
    {
      v2 |= 0x400u;
      ptQTask[83].ptParent = nullptr;
    }
  }
  if ( *(float *)&ptQTask[19].eQTaskType != 0.0 )
    v2 |= 0x800u;
  if ( *(float *)&ptQTask[20].ptNext != 0.0 )
    v2 |= 0x1000u;
  if ( *(float *)&ptQTask[23].ptNext != 0.0 && *(float *)&ptQTask[16].tQTaskRefList.ptTail == 0.0 )
    v2 |= 0x2000000u;
  if ( *(float *)&ptQTask[22].eQTaskType != 0.0 && *(float *)&ptQTask[16].tQTaskRefList.ptMiddle == 0.0 )
    v2 |= 0x1000000u;
  if ( *(float *)&ptQTask[24].ptNext != 0.0 && *(float *)&ptQTask[17].tQTaskRefList.ptTail == 0.0 )
  {
    if ( *(_DWORD *)&ptQTask[32].eQTaskType == 2 )
      v2 |= 0x10000000u;
    else
      v2 |= 0x20000000u;
  }
  if ( *(float *)&ptQTask[23].ptPrev != 0.0 )
    v2 |= 0x4000000u;
  if ( *(float *)&ptQTask[20].ptPrev != 0.0 )
    v2 |= 0x2000u;
  if ( *(float *)&ptQTask[20].tQTaskChildren.ptHead != 0.0 )
    v2 |= 0x4000u;
  if ( *(float *)&ptQTask[20].tQTaskChildren.ptMiddle != 0.0 )
    v2 |= 0x8000u;
  if ( *(float *)&ptQTask[21].tQTaskRefList.ptHead != 0.0 )
    v2 |= 0x80000u;
  ptState->bSignal = v2;
}

// source: j/0/human/humanplayer.c:13351  [size]
void __cdecl HumanPlayer_InitActionLock(struct State_s *ptState, struct QTask_s *ptQTask)
{
  ptQTask[77].tQTaskRefList.ptTail = nullptr;
  ptQTask[77].ptParent = nullptr;
  HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.4000000059604645);
  ptState->pfState = HumanPlayer_RunActionLock;
}

// source: j/0/human/humanplayer.c:13364  [anchor-caller]
void __cdecl HumanPlayer_RunActionLock(struct State_s *ptState, struct QTask_s *ptQTask)
{
  struct QTask_s *v2; // edi
  void (__cdecl *v3)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v5)(struct State_s *, struct QTask_s *); // eax
  struct QTask_s *ptTail; // esi
  struct QTask_s *ptHead; // edx

  v2 = ptQTask;
  if ( LOBYTE(ptQTask[76].tQTaskRefList.ptMiddle) )
  {
    if ( LOBYTE(ptQTask[80].tQTaskRefList.ptMiddle) )
    {
      ptTail = ptQTask[46].tQTaskChildren.ptTail;
      if ( ptTail )
      {
        ptHead = ptTail->tQTaskChildren.ptHead;
        if ( ptHead )
        {
          if ( *(float *)&ptQTask[20].ptNext != 0.0
            && ActionMenuScreen_IsFirstActionItem(ActionMenuScreen_ptQTask, ptHead, nullptr) )
          {
            ptQTask = nullptr;
            ((void (__cdecl *)(struct QTask_s *, struct QTask_s **))QTask_aatQTaskFinalEvent[GameFunctions_eGetActivateQTaskEvent][ptTail->tQTaskChildren.ptHead->eQTaskType].pfHandler)(
              ptTail->tQTaskChildren.ptHead,
              &ptQTask);
            HumanView_DisableZoomMode(v2[33].tQTaskChildren.ptTail);
            HumanPlayer_InitActivate(v2, (int)ptQTask);
          }
        }
      }
    }
  }
  else
  {
    v3 = ptState->apfExitState[ptState->nState];
    if ( v3 )
      v3(ptState, ptQTask);
    apfState = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 1;
    v5 = apfState[1];
    ptState->pfState = v5;
    v5(ptState, v2);
  }
}

// source: j/0/human/humanplayer.c:13414  [anchor-mhash]
void __cdecl HumanPlayer_InitActionIdle(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QReference_s *v19; };
    struct { char igi2_o1[4]; struct QTask_s *v20; };
    struct { char igi2_o2[8]; int v21; };
    struct { char igi2_o3[12]; struct QTask_s *v22; };
    struct { char igi2_o4[16]; struct QTask_s *v23; };
    struct { char igi2_o5[24]; struct AnimHeader_s *ptAnim; };
    struct { char igi2_o6[28]; float v25; };
    char igi2_extent[32];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // eax
  int v3; // ebx
  struct QTask_s *v4; // edx
  struct QTask_s *v5; // eax
  struct QTask_s *v6; // ecx
  struct QTask_s *v7; // ecx
  struct QTask_s *v8; // eax
  void (__cdecl *v9)(struct QTask_s *, struct QReference_s **); // ecx
  struct QTask_s *v10; // eax
  struct QTask_s *ptPrev; // ecx
  struct QReference_s *ptTail; // edx
  struct QTask_s *ptNext; // eax
  struct QTask_s *v14; // ecx
  struct QTask_s *v15; // ecx
  struct QTask_s *v16; // eax
  void (__cdecl *pfHandler)(struct QTask_s *, struct QReference_s **); // ecx
  struct QTask_s *v18; // eax

  ptQTask[77].tQTaskRefList.ptTail = (struct QReference_s *)1;
  ptQTask[87].tQTaskChildren.ptMiddle = (struct QTask_s *)1;
  v2 = *(_DWORD *)&ptQTask[32].eQTaskType;
  v3 = v2 != 2 ? 0 : 0x4B;
  if ( v2 == 2 )
  {
    HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
    if ( v3 == 77 || v3 == 78 || v3 == 79 )
    {
      ptPrev = ptQTask[77].ptPrev;
      ptTail = ptQTask[7].tQTaskRefList.ptTail;
      igi2_frame.v22 = ptQTask;
      ptNext = ptQTask[33].ptNext;
      igi2_frame.v19 = ptTail;
      igi2_frame.v23 = ptPrev;
      igi2_frame.v20 = ptNext;
      igi2_frame.v21 = 0;
      igi2_frame.ptAnim = nullptr;
      v14 = ptNext[1].ptPrev;
      if ( v14 )
        v15 = v14->tQTaskChildren.ptTail;
      else
        v15 = nullptr;
      v16 = ptNext[1].ptPrev;
      pfHandler = (void (__cdecl *)(struct QTask_s *, struct QReference_s **))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][v15->eQTaskType].pfHandler;
      if ( v16 )
        v18 = v16->tQTaskChildren.ptTail;
      else
        v18 = nullptr;
      pfHandler(v18, &igi2_frame.v19);
      if ( igi2_frame.ptAnim )
      {
        HumanAnim_SetAnimation(ptQTask, igi2_frame.ptAnim, 0, 0.0);
        ptQTask[34].tQTaskChildren.ptTail[1].tQTaskRefList.ptTail = (struct QReference_s *)(__int64)((double)AnimController_nTicksPerFrame * igi2_frame.v25);
      }
    }
    else if ( v3 == 90 || v3 == 91 )
    {
      v4 = ptQTask[77].ptPrev;
      igi2_frame.v19 = ptQTask[7].tQTaskRefList.ptTail;
      v5 = ptQTask[33].ptNext;
      igi2_frame.v22 = ptQTask;
      igi2_frame.v23 = v4;
      igi2_frame.v20 = v5;
      igi2_frame.v21 = 0;
      igi2_frame.ptAnim = nullptr;
      v6 = v5[1].ptPrev;
      if ( v6 )
        v7 = v6->tQTaskChildren.ptTail;
      else
        v7 = nullptr;
      v8 = v5[1].ptPrev;
      v9 = (void (__cdecl *)(struct QTask_s *, struct QReference_s **))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][v7->eQTaskType].pfHandler;
      if ( v8 )
        v10 = v8->tQTaskChildren.ptTail;
      else
        v10 = nullptr;
      v9(v10, &igi2_frame.v19);
      if ( igi2_frame.ptAnim )
      {
        HumanAnim_SetUpperBodyAnimationFromHeader(ptQTask, igi2_frame.ptAnim, 0, 0.0);
        ptQTask[34].tQTaskRefList.ptHead[5].pxObject = (void *)(__int64)((double)AnimController_nTicksPerFrame * igi2_frame.v25);
      }
      else
      {
        HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
      }
    }
    else
    {
      HumanAnim_SetAnimationAndTimeFromState(ptQTask, v3, 0, 0.0);
    }
  }
  else
  {
    HumanAnim_SetUpperBodyAnimationAndTimeFromState(ptQTask, v3, 0, 0.0);
  }
  HumanPlayer_SetWeaponTypeAnim(ptQTask, WEAPONTYPE_GETANIMTYPE_1STSTAND, 0, false);
  ptState->pfState = HumanPlayer_RunActionIdle;
}

// source: j/0/human/humanplayer.c:13429  [anchor-caller]
void __cdecl HumanPlayer_CheckBinoculars(struct QTask_s *ptQTask, enum bool isForceChangeWeapon)
{
  #pragma pack(push, 1)
  union
  {
    struct { enum WeaponOverlayStatus_e v29; };
    struct { char igi2_o1[20]; struct QReference_s *v30; };
    struct { char igi2_o2[40]; struct QReference_s *v31; };
    struct { char igi2_o3[44]; _DWORD v32[13]; };
    struct { char igi2_o4[96]; char v33[12]; };
    struct { char igi2_o5[108]; char *v34; };
    struct { char igi2_o6[112]; char v35; };
    struct { char igi2_o7[120]; _BYTE v36[52]; };
    char igi2_extent[8308];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptNext; // eax
  int v3; // eax
  struct WeaponType_s *WeaponTypeFromID; // esi
  int v5; // eax
  struct WeaponType_s *v6; // edi
  struct QTask_s *ptPrev; // ecx
  struct QReference_s *ptHead; // eax
  struct QTask_s *v9; // edi
  struct QTask_s *v10; // eax
  int v11; // eax
  int v12; // esi
  struct QReference_s *v13; // edx
  struct QTask_s *v14; // eax
  struct QTask_s *v15; // ecx
  struct QTask_s *v16; // ecx
  struct QTask_s *v17; // eax
  void (__cdecl *v18)(struct QTask_s *, _DWORD *); // ecx
  struct QTask_s *v19; // eax
  struct QReference_s *ptTail; // edx
  struct QTask_s *v21; // eax
  struct QTask_s *v22; // ecx
  struct QTask_s *v23; // ecx
  struct QTask_s *v24; // eax
  void (__cdecl *pfHandler)(struct QTask_s *, _DWORD *); // ecx
  struct QTask_s *v26; // eax
  struct QTask_s *v27; // eax
  struct QTask_s *v28; // esi

  if ( ptQTask[33].ptNext && Weapon_IsWeaponSelectable(ptQTask[33].ptNext, (char *)&g_zSoundDefPrefix.eQTaskType) )
  {
    ptNext = ptQTask[33].ptNext[1].ptNext;
    igi2_frame.v30 = ptNext ? (struct QReference_s *)ptNext->tQTaskChildren.ptTail : nullptr;
    if ( *(float *)&ptQTask[22].ptParent != 0.0 && *(float *)&ptQTask[16].tQTaskRefList.ptHead == 0.0
      || *(float *)&ptQTask[23].tQTaskChildren.ptTail != 0.0 && *(float *)&ptQTask[17].ptPrev == 0.0 )
    {
      v3 = Script_ParseLineInt32((char *)&g_zSoundDefPrefix.eQTaskType);
      WeaponTypeFromID = WeaponType_GetWeaponTypeFromID(v3);
      igi2_frame.v31 = (struct QReference_s *)WeaponTypeFromID;
      v5 = Script_ParseLineInt32((char *)&g_zSoundDefPrefix.tQTaskChildren.ptTail);
      v6 = WeaponType_GetWeaponTypeFromID(v5);
      if ( v6 )
      {
        if ( WeaponTypeFromID )
        {
          ptPrev = (struct QTask_s *)igi2_frame.v30;
          if ( WeaponTypeFromID == (struct WeaponType_s *)igi2_frame.v30 && *(float *)&ptQTask[22].ptParent != 0.0
            || v6 == (struct WeaponType_s *)igi2_frame.v30 && *(float *)&ptQTask[23].tQTaskChildren.ptTail != 0.0 )
          {
            ptHead = ptQTask[86].tQTaskRefList.ptHead;
            if ( ptHead )
            {
              if ( isForceChangeWeapon )
              {
                Weapon_Activate(ptQTask[33].ptNext, (char *)&ptHead[7], false);
              }
              else
              {
                ptPrev = (struct QTask_s *)ptHead[12].ptPrev;
                ptQTask[76].ptParent = ptPrev;
              }
            }
            v9 = ptQTask[33].ptNext;
            ptQTask[86].tQTaskRefList.ptHead = nullptr;
            Weapon_SetOverlayStatus(ptPrev, igi2_frame.v29, 0, (int)v9);
LABEL_48:
            HumanPlayer_SetWeaponPrecision(ptQTask, (enum HumanPlayerPrecisionType_e)ptQTask[77].tQTaskChildren.ptHead);
            return;
          }
          if ( *(float *)&ptQTask[22].ptParent == 0.0 )
          {
            v28 = ptQTask[33].ptNext;
            isInfraEnabled = 1;
            Weapon_Activate(v28, v6->zWeaponScriptID, false);
LABEL_44:
            if ( igi2_frame.v30 != igi2_frame.v31 && igi2_frame.v30 != (struct QReference_s *)v6 )
              ptQTask[86].tQTaskRefList.ptHead = igi2_frame.v30;
            Weapon_Fire(ptQTask[33].ptNext, 0);
            v27 = ptQTask[33].ptNext;
            v27[2].ptParent = (struct QTask_s *)1;
            v27[1].tQTaskChildren.ptTail = nullptr;
            goto LABEL_48;
          }
          Weapon_Activate(ptQTask[33].ptNext, WeaponTypeFromID->zWeaponScriptID, false);
          if ( Game_eGameMode != GAME_GAMEMODE_MULTIPLAYER )
            goto LABEL_44;
          strcpy((char *)&igi2_frame.v32[5], WeaponTypeFromID->zWeaponScriptID);
          v10 = ptQTask[33].ptNext;
          igi2_frame.v34 = &igi2_frame.v35;
          qmemcpy(igi2_frame.v36, igi2_frame.v32, sizeof(igi2_frame.v36));
          ((void (__cdecl *)(struct QTask_s *, char *))QTask_aatQTaskFinalEvent[Weapon_eActivateQTaskEvent][v10->eQTaskType].pfHandler)(
            v10,
            igi2_frame.v33);
          v11 = *(_DWORD *)&ptQTask[32].eQTaskType;
          ptQTask[77].tQTaskRefList.ptTail = (struct QReference_s *)12;
          ptQTask[87].tQTaskChildren.ptMiddle = (struct QTask_s *)1;
          v12 = v11 == 2 ? 90 : 87;
          if ( v11 == 2 )
          {
            HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
            if ( v12 != 90 )
            {
              HumanAnim_SetAnimationAndTimeFromState(ptQTask, v12, 0, 0.0);
              goto LABEL_43;
            }
            ptTail = ptQTask[7].tQTaskRefList.ptTail;
            igi2_frame.v32[4] = ptQTask[77].ptPrev;
            v21 = ptQTask[33].ptNext;
            ptQTask[35].tQTaskRefList.ptHead = (struct QReference_s *)90;
            igi2_frame.v32[0] = ptTail;
            igi2_frame.v32[3] = 26;
            igi2_frame.v32[1] = v21;
            igi2_frame.v32[2] = 0;
            igi2_frame.v32[6] = 0;
            v22 = v21[1].ptPrev;
            if ( v22 )
              v23 = v22->tQTaskChildren.ptTail;
            else
              v23 = nullptr;
            v24 = v21[1].ptPrev;
            pfHandler = (void (__cdecl *)(struct QTask_s *, _DWORD *))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][v23->eQTaskType].pfHandler;
            if ( v24 )
              v26 = v24->tQTaskChildren.ptTail;
            else
              v26 = nullptr;
            pfHandler(v26, igi2_frame.v32);
            if ( igi2_frame.v32[6] )
              goto LABEL_31;
          }
          else
          {
            v13 = ptQTask[7].tQTaskRefList.ptTail;
            igi2_frame.v32[4] = ptQTask[77].ptPrev;
            v14 = ptQTask[33].ptNext;
            ptQTask[35].tQTaskRefList.ptHead = (struct QReference_s *)87;
            igi2_frame.v32[0] = v13;
            igi2_frame.v32[3] = 15;
            igi2_frame.v32[1] = v14;
            igi2_frame.v32[2] = 0;
            igi2_frame.v32[6] = 0;
            v15 = v14[1].ptPrev;
            if ( v15 )
              v16 = v15->tQTaskChildren.ptTail;
            else
              v16 = nullptr;
            v17 = v14[1].ptPrev;
            v18 = (void (__cdecl *)(struct QTask_s *, _DWORD *))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][v16->eQTaskType].pfHandler;
            if ( v17 )
              v19 = v17->tQTaskChildren.ptTail;
            else
              v19 = nullptr;
            v18(v19, igi2_frame.v32);
            if ( igi2_frame.v32[6] )
            {
LABEL_31:
              HumanAnim_SetUpperBodyAnimationFromHeader(
                ptQTask,
                (struct AnimHeader_s *)igi2_frame.v32[6],
                *(_DWORD *)(igi2_frame.v32[6] + 16),
                0.0);
              ptQTask[34].tQTaskRefList.ptHead[5].pxObject = (void *)(__int64)(-*(float *)&igi2_frame.v32[7]
                                                                             * (double)AnimController_nTicksPerFrame);
LABEL_43:
              HumanPlayer_SetWeaponTypeAnim(ptQTask, WEAPONTYPE_GETANIMTYPE_1STACTIVATE, 0, true);
              goto LABEL_44;
            }
          }
          HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
          goto LABEL_43;
        }
      }
    }
  }
}

// source: j/0/human/humanplayer.c:13524  [anchor-caller]
void __cdecl HumanPlayer_RunActionIdle(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { int eHumanActivate; };
    struct { char igi2_o1[4]; unsigned int bSignal; };
    struct { char igi2_o2[8]; struct WeaponGetFireTypeAmmoContext_s nFireType; };
    char igi2_extent[28];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v2; // ebx
  struct QReference_s *ptTail; // ecx
  struct QTask_s *ptParent; // eax
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptPrev; // eax
  struct State_s *v7; // esi
  char ptMiddle; // al
  struct QTask_s *v9; // eax
  void (__cdecl *v10)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v12)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v13)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v14)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v15)(struct State_s *, struct QTask_s *); // eax
  int v16; // edi
  BOOL v17; // eax
  struct QTask_s *v18; // edi
  void (__cdecl *v19)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v20)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v21)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v22)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v23)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v24)(struct State_s *, struct QTask_s *); // eax
  struct QTask_s *v25; // ecx
  struct QTask_s *v26; // eax
  void (__cdecl *v27)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v28)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v29)(struct State_s *, struct QTask_s *); // eax
  int v30; // eax
  void (__cdecl *v31)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v32)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v33)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v34)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v35)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v36)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v37)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v38)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v39)(struct State_s *, struct QTask_s *); // eax
  struct QTask_s *v40; // esi
  struct QTask_s *EvaluateActivateTask; // eax
  struct QTask_s *v42; // esi
  struct QTask_s *v43; // eax
  struct WeaponType_s *v44; // edi
  struct WeaponType_s *NextEnabledWeaponTypeFromCategory; // eax

  v2 = ptQTask;
  ptTail = ptQTask[77].tQTaskRefList.ptTail;
  ptParent = ptQTask[77].ptParent;
  igi2_frame.eHumanActivate = 0;
  if ( ptTail != (struct QReference_s *)ptParent )
  {
    if ( ptTail == (struct QReference_s *)4 && ptParent == (struct QTask_s *)5
      || ptTail == (struct QReference_s *)5 && ptParent == (struct QTask_s *)4 )
    {
      ptQTask[77].tQTaskRefList.ptTail = (struct QReference_s *)ptParent;
    }
    else
    {
      HumanPlayer_SetUpperBody(ptQTask, (int)ptParent);
    }
  }
  ptNext = ptQTask[33].ptNext;
  if ( ptNext )
  {
    ptPrev = ptNext[1].ptPrev;
    if ( ptPrev )
      igi2_frame.eHumanActivate = (int)ptPrev->tQTaskChildren.ptTail;
    else
      igi2_frame.eHumanActivate = 0;
  }
  HumanPlayer_SetWeaponPrecision(ptQTask, (enum HumanPlayerPrecisionType_e)ptQTask[77].tQTaskChildren.ptHead);
  v7 = ptState;
  ptMiddle = (char)ptQTask[76].tQTaskRefList.ptMiddle;
  igi2_frame.bSignal = ptState->bSignal;
  if ( ptMiddle )
  {
    v9 = ptQTask[33].tQTaskChildren.ptTail;
    v9[16].tQTaskRefList.ptMiddle = nullptr;
    *(float *)&v9[16].tQTaskChildren.ptHead = tan(0.7853981852531433);
    *(float *)&v9[16].tQTaskRefList.ptHead = tan(0.5235987901687622);
    v10 = ptState->apfExitState[ptState->nState];
    if ( v10 )
      v10(ptState, ptQTask);
    apfState = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 0;
    v12 = *apfState;
    ptState->pfState = *apfState;
    v12(ptState, ptQTask);
    return;
  }
  if ( igi2_frame.eHumanActivate )
  {
    if ( *(_DWORD *)(igi2_frame.eHumanActivate + 668) == 7 || !strcmp((char *)(igi2_frame.eHumanActivate + 84), "WEAPON_ID_RPG18") )
    {
      Weapon_GetFireTypeAmmoInfoFromWeaponTypeItem(
        (struct Weapon_s *)ptQTask[33].ptNext,
        (struct WeaponTypeItem_s *)ptQTask[33].ptNext[1].ptPrev,
        0,
        &igi2_frame.nFireType);
      if ( !igi2_frame.nFireType.nAmmoAvailable
        && (strcmp((char *)(igi2_frame.eHumanActivate + 84), "WEAPON_ID_RPG18")
         || !ptQTask[33].ptNext[1].ptPrev->tQTaskChildren.ptHead)
        || ptQTask[33].ptNext[1].tQTaskChildren.ptTail == (struct QTask_s *)6 )
      {
        HumanPlayer_SelectWeapon(ptQTask, 1);
      }
      v2 = ptQTask;
    }
    v7 = ptState;
  }
  HumanPlayer_CheckBinoculars(v2, false);
  if ( *(float *)&v2[20].tQTaskChildren.ptMiddle != 0.0 && (v2[30].eQTaskType & 2) != 0 )
  {
    if ( !v2[86].tQTaskRefList.ptHead )
      HumanView_DisableZoomMode(v2[33].tQTaskChildren.ptTail);
    v13 = v7->apfExitState[v7->nState];
    if ( v13 )
      v13(v7, v2);
    v14 = v7->apfState;
    v7->nPreviousState = v7->nState;
    v7->nState = 7;
    v15 = v14[7];
    v7->pfState = v15;
    v15(v7, v2);
    return;
  }
  if ( HumanPlayer_IsActivateComputer(v2) && (v2[30].eQTaskType & 2) != 0 )
    HumanPlayer_ActivateComputer(v2);
  if ( !v2[86].tQTaskRefList.ptHead )
  {
    if ( !igi2_frame.eHumanActivate )
    {
LABEL_80:
      if ( v2[76].ptParent == (struct QTask_s *)-1 )
      {
        v40 = v2[46].tQTaskChildren.ptTail;
        if ( v40 )
        {
          if ( v40->tQTaskChildren.ptHead )
          {
            if ( *(float *)&v2[20].ptNext != 0.0 )
            {
              EvaluateActivateTask = Human_GetEvaluateActivateTask(v2);
              if ( ActionMenuScreen_IsFirstActionItem(ActionMenuScreen_ptQTask, EvaluateActivateTask, nullptr) )
              {
                igi2_frame.eHumanActivate = 0;
                ((void (__cdecl *)(struct QTask_s *, int *))QTask_aatQTaskFinalEvent[GameFunctions_eGetActivateQTaskEvent][v40->tQTaskChildren.ptHead->eQTaskType].pfHandler)(
                  v40->tQTaskChildren.ptHead,
                  &igi2_frame.eHumanActivate);
                HumanView_DisableZoomMode(v2[33].tQTaskChildren.ptTail);
                HumanPlayer_InitActivate(v2, igi2_frame.eHumanActivate);
              }
            }
          }
        }
        if ( *(float *)&v2[20].tQTaskRefList.ptTail != 0.0 && *(float *)&v2[14].tQTaskChildren.ptTail == 0.0 )
        {
          v42 = v2[33].ptNext;
          v43 = v42[1].ptPrev;
          v44 = v43 ? (struct WeaponType_s *)v43->tQTaskChildren.ptTail : nullptr;
          if ( v44->isDropWeaponInSinglePlayer
            && Weapon_GetWeaponTypeItemFromWeaponType(v2[33].ptNext, v44->zWeaponScriptID)->isActive )
          {
            v2[86].ptParent = &v44->tQTask;
            v2[87].tQTaskRefList.ptHead = (struct QReference_s *)1;
            NextEnabledWeaponTypeFromCategory = Weapon_GetNextEnabledWeaponTypeFromCategory(
                                                  v42,
                                                  v44->eWeaponCategory,
                                                  v44);
            if ( NextEnabledWeaponTypeFromCategory )
            {
              v2[76].ptParent = (struct QTask_s *)NextEnabledWeaponTypeFromCategory->eID;
              HumanPlayer_SelectWeapon(v2, 0);
            }
            else
            {
              HumanPlayer_SelectWeapon(v2, 1);
            }
          }
        }
        v2[87].ptParent = nullptr;
      }
      else
      {
        HumanView_DisableZoomMode(v2[33].tQTaskChildren.ptTail);
        v37 = ptState->apfExitState[ptState->nState];
        if ( v37 )
          v37(ptState, v2);
        v38 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 6;
        v39 = v38[6];
        ptState->pfState = v39;
        v39(ptState, v2);
      }
      return;
    }
    v16 = Script_ParseLineInt32("WEAPON_ID_C4BOMB");
    if ( *(_DWORD *)(igi2_frame.eHumanActivate + 148) == WeaponType_GetWeaponTypeFromID(v16)->eID
      && v2[87].ptParent
      && *(float *)&v2[20].ptNext > 0.0 )
    {
      v2[19].tQTaskRefList.ptTail = (struct QReference_s *)1065353216;
    }
    if ( *(float *)&v2[19].tQTaskRefList.ptTail == 0.0 && *(float *)&v2[19].ptParent == 0.0 )
    {
LABEL_72:
      if ( (igi2_frame.bSignal & 0x800) != 0 )
      {
        Weapon_GetFireTypeAmmoInfoFromWeaponTypeItem(
          (struct Weapon_s *)v2[33].ptNext,
          (struct WeaponTypeItem_s *)v2[33].ptNext[1].ptPrev,
          0,
          &igi2_frame.nFireType);
        if ( igi2_frame.nFireType.nAmmoInWeapon != igi2_frame.nFireType.nRoundsPerClip
          && (igi2_frame.nFireType.nAmmoAvailable || *(&ptQTask[83].isInMemPool + 1)) )
        {
          v34 = ptState->apfExitState[ptState->nState];
          if ( v34 )
            v34(ptState, ptQTask);
          v35 = ptState->apfState;
          ptState->nPreviousState = ptState->nState;
          ptState->nState = 5;
          v36 = v35[5];
          ptState->pfState = v36;
          v36(ptState, ptQTask);
          return;
        }
        v2 = ptQTask;
      }
      goto LABEL_80;
    }
    v17 = *(float *)&v2[19].ptParent != 0.0;
    v2[77].ptPrev = (struct QTask_s *)v17;
    Weapon_GetFireTypeAmmoInfoFromWeaponTypeItem(
      (struct Weapon_s *)v2[33].ptNext,
      (struct WeaponTypeItem_s *)v2[33].ptNext[1].ptPrev,
      v17,
      &igi2_frame.nFireType);
    if ( !igi2_frame.nFireType.ptAmmoType || igi2_frame.nFireType.nAmmoInWeapon )
    {
      v18 = ptQTask;
    }
    else
    {
      v18 = ptQTask;
      if ( ptQTask[33].ptNext[1].tQTaskChildren.ptTail != (struct QTask_s *)5 )
      {
        if ( igi2_frame.nFireType.nAmmoAvailable || *(&ptQTask[83].isInMemPool + 1) )
        {
          v22 = ptState->apfExitState[ptState->nState];
          if ( v22 )
            v22(ptState, ptQTask);
          v23 = ptState->apfState;
          ptState->nPreviousState = ptState->nState;
          ptState->nState = 5;
          v24 = v23[5];
          ptState->pfState = v24;
          v24(ptState, ptQTask);
        }
        else
        {
          v19 = ptState->apfExitState[ptState->nState];
          if ( v19 )
            v19(ptState, ptQTask);
          v20 = ptState->apfState;
          ptState->nPreviousState = ptState->nState;
          ptState->nState = 9;
          v21 = v20[9];
          ptState->pfState = v21;
          v21(ptState, ptQTask);
        }
        return;
      }
    }
    v25 = v18[33].ptNext;
    v26 = v25[1].ptPrev;
    if ( v26 )
      v26 = v26->tQTaskChildren.ptTail;
    if ( *((_DWORD *)&v26->ptNext + 5 * ((int)&v18[77].ptPrev[1].tQTaskRefList.ptMiddle + 1)) == 512 )
      goto LABEL_71;
    if ( *(_DWORD *)(igi2_frame.eHumanActivate + 668) == 4 )
    {
      if ( !v25[1].ptParent && (*(float *)&ptQTask[19].tQTaskRefList.ptTail != 0.0 || !v25[16].tQTaskChildren.ptTail) )
      {
        v27 = ptState->apfExitState[ptState->nState];
        if ( v27 )
          v27(ptState, ptQTask);
        v28 = ptState->apfState;
        ptState->nPreviousState = ptState->nState;
        ptState->nState = 10;
        v29 = v28[10];
        ptState->pfState = v29;
        v29(ptState, ptQTask);
        return;
      }
      goto LABEL_71;
    }
    v30 = *(_DWORD *)(igi2_frame.eHumanActivate + 672);
    if ( v30 == 12 || v30 == 11 )
    {
LABEL_71:
      v2 = ptQTask;
      goto LABEL_72;
    }
    v31 = ptState->apfExitState[ptState->nState];
    if ( v31 )
      v31(ptState, ptQTask);
    v32 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 2;
    v33 = v32[2];
    ptState->pfState = v33;
    v33(ptState, ptQTask);
  }
}

// source: j/0/human/humanplayer.c:13790  [anchor-mhash]
struct Result_s *__cdecl HumanPlayer_LockActivateScriptFunction(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  char v4; // al
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments > 0 )
  {
    if ( ptArgList->isQVM )
    {
      ptArgList = nullptr;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
      v4 = (char)ptArgList;
    }
    else
    {
      v4 = Expression_EvalInt(*ptArgList->aptExpression);
    }
    *((_BYTE *)pxContext + 3217) = v4;
  }
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/human/humanplayer.c:13823  [anchor-caller]
struct Result_s *__cdecl HumanPlayer_ActivateScriptFunction(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct ArgList_s *v11; };
    struct { char igi2_o1[28]; struct Result_s Rs; };
    char igi2_extent[52];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // eax
  struct QReference_s *v5; // eax
  struct QTask_s *pxObject; // edi
  int v7; // edx
  int v8; // edx
  int v9; // eax

  v3 = ptArgList;
  if ( ptArgList->nArguments > 0 )
  {
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
    if ( (unsigned int)v4 < 0x1000 )
    {
      v5 = Level_atLevelQTaskID[(_DWORD)v4];
      if ( v5 )
      {
        pxObject = (struct QTask_s *)v5->pxObject;
        if ( pxObject )
        {
          if ( QTask_aatQTaskFinalEvent[GameFunctions_eGetActivateQTaskEvent][pxObject->eQTaskType].pfHandler )
          {
            Human_SetEvaluateActivateTask((struct QTask_s *)pxContext, pxObject);
            v7 = 511 * GameFunctions_eGetActivateQTaskEvent;
            *((_BYTE *)pxContext + 1864) = 1;
            v8 = pxObject->eQTaskType + v7;
            ptArgList = nullptr;
            ((void (__cdecl *)(struct QTask_s *, struct ArgList_s **))QTask_aatQTaskFinalEvent[0][v8].pfHandler)(
              pxObject,
              &ptArgList);
            v9 = *((_DWORD *)pxContext + 334);
            *(_DWORD *)(v9 + 664) = 0;
            *(float *)(v9 + 648) = tan(0.7853981852531433);
            *(float *)(v9 + 660) = tan(0.5235987901687622);
            igi2_frame.v11 = ptArgList;
            *((_DWORD *)pxContext + 137) = 0;
            HumanPlayer_InitActivate((struct QTask_s *)pxContext, (int)igi2_frame.v11);
          }
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

// source: j/0/human/humanplayer.c:13881  [anchor-mhash]
void __cdecl HumanPlayer_Kickback(struct QTask_s *ptQTask)
{
  struct QTask_s *ptNext; // eax
  double v2; // st7
  float *ptTail; // edx
  double v4; // st6
  float vGamma; // [esp+8h] [ebp-4h]

  ptNext = ptQTask[33].ptNext;
  v2 = *(float *)&ptNext[2].ptPrev;
  ptTail = (float *)ptQTask[33].tQTaskChildren.ptTail;
  v4 = *(float *)&ptNext[1].eQTaskType;
  vGamma = *(float *)&ptNext[2].tQTaskChildren.ptHead;
  if ( ptQTask != (struct QTask_s *)-3368 )
    ptQTask[84].tQTaskChildren.ptHead = ptNext[2].ptNext;
  *(float *)&ptQTask[77].tQTaskRefList.ptMiddle = (v2 + vGamma) * 0.4000000059604645
                                                + *(float *)&ptQTask[77].tQTaskRefList.ptMiddle;
  ptTail[121] = v2 * 0.01745329238474369 + ptTail[121];
  ptTail[124] = vGamma * 0.01745329238474369 + ptTail[124];
  ptTail[118] = v4;
}

// source: j/0/human/humanplayer.c:13916  [anchor-callee]
void __cdecl HumanPlayer_HandleBreathViewOffset(struct QTask_s *ptQTask)
{
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptTail; // eax
  float *ptHead; // esi
  struct QReference_s *ptMiddle; // eax
  struct QReference_s *v6; // edi
  int v7; // eax
  double v8; // st7
  int v9; // eax
  long double v10; // st7
  double v11; // st6
  int v12; // esi
  int v13; // eax
  bool v14; // sf
  double v15; // st6
  struct QTask_s *v16; // [esp+8h] [ebp-4h]

  ptNext = ptQTask[33].ptNext;
  if ( !ptNext )
    goto LABEL_10;
  if ( !ptNext[4].ptNext )
    goto LABEL_10;
  ptPrev = ptNext[1].ptPrev;
  if ( !ptPrev )
    goto LABEL_10;
  ptTail = ptPrev->tQTaskChildren.ptTail;
  if ( !ptTail )
    goto LABEL_10;
  if ( ptTail[32].tQTaskRefList.ptHead == (struct QReference_s *)Zoom_eQTaskType )
  {
    ptHead = (float *)ptTail[32].ptParent->tQTaskChildren.ptHead;
  }
  else
  {
    if ( ptTail[33].ptNext != (struct QTask_s *)Zoom_eQTaskType )
      goto LABEL_10;
    ptHead = (float *)ptTail[33].tQTaskChildren.ptMiddle->tQTaskChildren.ptHead;
  }
  if ( !ptHead )
  {
LABEL_10:
    ptMiddle = ptQTask[88].tQTaskRefList.ptMiddle;
    ptQTask[88].tQTaskRefList.ptHead = nullptr;
    if ( (int)ptMiddle <= 0 )
      ptQTask[88].tQTaskRefList.ptMiddle = nullptr;
    else
      ptQTask[88].tQTaskRefList.ptMiddle = (struct QReference_s *)((char *)ptMiddle - 2);
    return;
  }
  v16 = ptQTask[33].tQTaskChildren.ptTail;
  if ( !v16 )
    return;
  v6 = ptQTask[88].tQTaskRefList.ptHead;
  v7 = *(_DWORD *)&ptQTask[32].eQTaskType;
  v8 = (double)((int)v6 % 120) * 0.008333333767950535;
  if ( !v7 )
  {
    v10 = cos(v8 * 6.2831854820251465);
    v11 = ptHead[15];
    goto LABEL_20;
  }
  v9 = v7 - 1;
  if ( !v9 )
  {
    v10 = cos(v8 * 6.2831854820251465);
    v11 = ptHead[16];
    goto LABEL_20;
  }
  if ( v9 == 1 )
  {
    v10 = cos(v8 * 6.2831854820251465);
    v11 = ptHead[17];
LABEL_20:
    v8 = v10 * (v11 * 0.01745329238474369);
  }
  v12 = (int)&ptQTask[88].tQTaskRefList.ptMiddle->ptNext + 1;
  v13 = v12;
  v14 = (int)&ptQTask[88].tQTaskRefList.ptMiddle[-5].ptNext + 1 < 0;
  ptQTask[88].tQTaskRefList.ptMiddle = (struct QReference_s *)v12;
  if ( v14 ^ __OFSUB__(v12, 60) | (v12 == 60) )
  {
    v15 = 0.0;
  }
  else
  {
    if ( v12 >= 300 )
      v13 = 300;
    ptQTask[88].tQTaskRefList.ptMiddle = (struct QReference_s *)v13;
    v15 = (double)(v13 - 60) * 0.004166666883975267;
    if ( v15 <= 0.0 )
      v15 = 0.0;
    ptQTask[88].tQTaskRefList.ptHead = (struct QReference_s *)((char *)&v6->ptNext + 1);
  }
  *(float *)&v16[12].tQTaskRefList.ptHead = v15 * v8;
}

// source: j/0/human/humanplayer.c:14012  [anchor-strings]
void __cdecl HumanPlayer_RunActionThrowGrenade(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v36; };
    struct { char igi2_o1[4]; unsigned int bSignal; };
    struct { char igi2_o2[16]; struct WeaponGetFireTypeAmmoContext_s nFireType; };
    struct { char igi2_o3[40]; struct AnimHeader_s *ptAnim; };
    struct { char igi2_o4[44]; float v40; };
    char igi2_extent[48];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v2; // esi
  struct QTask_s *ptTail; // ebx
  struct State_s *v4; // edi
  struct QTask_s *ptParent; // eax
  struct QTask_s *ptNext; // eax
  struct QTask_s *v7; // ecx
  void *v8; // eax
  struct QReference_s *v9; // ecx
  struct QTask_s *v10; // edx
  unsigned int v11; // eax
  struct QReference_s *ptHead; // ecx
  struct WeaponType_s *WeaponTypeFromID; // eax
  struct QTask_s *v14; // edi
  struct QTask_s *v15; // esi
  int v16; // eax
  int v17; // esi
  struct QReference_s *v18; // edx
  struct QTask_s *v19; // eax
  struct QTask_s *v20; // ecx
  struct QTask_s *v21; // ecx
  struct QTask_s *v22; // eax
  void (__cdecl *v23)(struct QTask_s *, struct WeaponGetFireTypeAmmoContext_s *); // ecx
  struct QTask_s *v24; // eax
  struct QReference_s *v25; // edx
  struct QTask_s *v26; // eax
  struct QTask_s *ptPrev; // ecx
  struct QTask_s *v28; // ecx
  struct QTask_s *v29; // eax
  void (__cdecl *pfHandler)(struct QTask_s *, struct WeaponGetFireTypeAmmoContext_s *); // ecx
  struct QTask_s *v31; // eax
  struct QTask_s *v32; // eax
  void (__cdecl *v33)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v35)(struct State_s *, struct QTask_s *); // eax

  v2 = ptQTask;
  ptTail = ptQTask[33].tQTaskChildren.ptTail;
  v4 = ptState;
  igi2_frame.bSignal = ptState->bSignal;
  ptParent = ptQTask[80].ptParent;
  igi2_frame.v36 = 0;
  ptQTask[80].ptParent = (struct QTask_s *)((char *)&ptParent->ptNext + 1);
  if ( ptParent == (struct QTask_s *)7 )
  {
    Weapon_Fire(ptQTask[33].ptNext, 1);
    ptNext = ptQTask[33].ptNext;
    ptNext[3].tQTaskRefList.ptHead = (struct QReference_s *)1;
    ptNext[1].tQTaskChildren.ptTail = nullptr;
    ptQTask[77].ptPrev = nullptr;
  }
  if ( (igi2_frame.bSignal & 0x100000) != 0 )
  {
    v7 = HumanPlayer_ptQTask;
    if ( !*(_DWORD *)&ptQTask[80].eQTaskType && HumanPlayer_ptQTask )
    {
      SoundSys_NewSoundFn(HumanPlayer_ptQTask[33].tQTaskChildren.ptTail, "grenade_handle");
      v7 = HumanPlayer_ptQTask;
    }
    if ( *(float *)&ptQTask[19].tQTaskRefList.ptTail == 0.0 )
    {
      if ( v7 )
        SoundSys_NewSoundFn(v7[33].tQTaskChildren.ptTail, "grenade_throw");
      v11 = (__int64)(double)AnimController_nTicksPerFrame;
      ptTail[16].tQTaskRefList.ptTail[5].pxObject = (void *)v11;
      ptHead = ptQTask[34].tQTaskRefList.ptHead;
      if ( ptHead )
        ptHead[5].pxObject = (void *)v11;
      *(_DWORD *)&ptQTask[74].eQTaskType &= ~0x100000u;
    }
    else
    {
      v8 = (void *)(__int64)((double)AnimController_nTicksPerFrame * 0.0);
      ptTail[16].tQTaskRefList.ptTail[5].pxObject = v8;
      v9 = ptQTask[34].tQTaskRefList.ptHead;
      if ( v9 )
        v9[5].pxObject = v8;
      v10 = ptQTask[33].ptNext;
      ++*(_DWORD *)&ptQTask[80].eQTaskType;
      if ( v10[1].tQTaskChildren.ptTail == (struct QTask_s *)6 )
        igi2_frame.v36 = 1;
    }
  }
  if ( (int)ptTail[16].tQTaskRefList.ptTail[5].ptPrev > 6400
    && (Weapon_GetFireTypeAmmoInfoFromWeaponTypeItem(
          (struct Weapon_s *)ptQTask[33].ptNext,
          (struct WeaponTypeItem_s *)ptQTask[33].ptNext[1].ptPrev,
          0,
          &igi2_frame.nFireType),
        !igi2_frame.nFireType.nAmmoAvailable)
    || igi2_frame.v36 )
  {
    *(_DWORD *)&ptQTask[74].eQTaskType &= ~0x100000u;
    HumanPlayer_SelectWeapon(ptQTask, 1);
    WeaponTypeFromID = WeaponType_GetWeaponTypeFromID((int)ptQTask[76].ptParent);
    v14 = ptQTask;
    v15 = ptQTask[33].ptNext;
    ptQTask[76].ptParent = (struct QTask_s *)-1;
    Weapon_Activate(v15, WeaponTypeFromID->zWeaponScriptID, false);
    v16 = *(_DWORD *)&ptQTask[32].eQTaskType;
    ptQTask[77].tQTaskRefList.ptTail = (struct QReference_s *)12;
    ptQTask[87].tQTaskChildren.ptMiddle = (struct QTask_s *)1;
    v17 = v16 == 2 ? 90 : 87;
    if ( v16 == 2 )
    {
      HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
      if ( v17 != 90 )
      {
        HumanAnim_SetAnimationAndTimeFromState(ptQTask, v17, 0, 0.0);
        v14 = ptQTask;
        goto LABEL_40;
      }
      v25 = ptQTask[7].tQTaskRefList.ptTail;
      igi2_frame.nFireType.nRoundsPerClip = (int)ptQTask[77].ptPrev;
      v26 = ptQTask[33].ptNext;
      ptQTask[35].tQTaskRefList.ptHead = (struct QReference_s *)90;
      igi2_frame.nFireType.ptAmmoType = (struct AmmoType_s *)v25;
      igi2_frame.nFireType.nBulletsPerRound = 26;
      igi2_frame.nFireType.nAmmoInWeapon = (int)v26;
      igi2_frame.nFireType.nAmmoAvailable = 0;
      igi2_frame.ptAnim = nullptr;
      ptPrev = v26[1].ptPrev;
      if ( ptPrev )
        v28 = ptPrev->tQTaskChildren.ptTail;
      else
        v28 = nullptr;
      v29 = v26[1].ptPrev;
      pfHandler = (void (__cdecl *)(struct QTask_s *, struct WeaponGetFireTypeAmmoContext_s *))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][v28->eQTaskType].pfHandler;
      if ( v29 )
        v31 = v29->tQTaskChildren.ptTail;
      else
        v31 = nullptr;
      pfHandler(v31, &igi2_frame.nFireType);
      if ( igi2_frame.ptAnim )
        goto LABEL_28;
    }
    else
    {
      v18 = ptQTask[7].tQTaskRefList.ptTail;
      igi2_frame.nFireType.nRoundsPerClip = (int)ptQTask[77].ptPrev;
      v19 = ptQTask[33].ptNext;
      ptQTask[35].tQTaskRefList.ptHead = (struct QReference_s *)87;
      igi2_frame.nFireType.ptAmmoType = (struct AmmoType_s *)v18;
      igi2_frame.nFireType.nBulletsPerRound = 15;
      igi2_frame.nFireType.nAmmoInWeapon = (int)v19;
      igi2_frame.nFireType.nAmmoAvailable = 0;
      igi2_frame.ptAnim = nullptr;
      v20 = v19[1].ptPrev;
      if ( v20 )
        v21 = v20->tQTaskChildren.ptTail;
      else
        v21 = nullptr;
      v22 = v19[1].ptPrev;
      v23 = (void (__cdecl *)(struct QTask_s *, struct WeaponGetFireTypeAmmoContext_s *))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][v21->eQTaskType].pfHandler;
      if ( v22 )
        v24 = v22->tQTaskChildren.ptTail;
      else
        v24 = nullptr;
      v23(v24, &igi2_frame.nFireType);
      if ( igi2_frame.ptAnim )
      {
LABEL_28:
        HumanAnim_SetUpperBodyAnimationFromHeader(ptQTask, igi2_frame.ptAnim, igi2_frame.ptAnim->nTotalTime, 0.0);
        ptQTask[34].tQTaskRefList.ptHead[5].pxObject = (void *)(__int64)(-igi2_frame.v40 * (double)AnimController_nTicksPerFrame);
LABEL_40:
        HumanPlayer_SetWeaponTypeAnim(v14, WEAPONTYPE_GETANIMTYPE_1STACTIVATE, 0, true);
        HumanPlayer_SetWeaponPrecision(v14, (enum HumanPlayerPrecisionType_e)v14[77].tQTaskChildren.ptHead);
        v2 = ptQTask;
        ptState->pfState = (void (__cdecl *)(struct State_s *, struct QTask_s *))sub_4C2030;
        v4 = ptState;
        goto LABEL_41;
      }
    }
    HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
    goto LABEL_40;
  }
LABEL_41:
  if ( (igi2_frame.bSignal & 1) != 0 )
  {
    v32 = v2[33].ptNext;
    v32[2].ptParent = (struct QTask_s *)1;
    v32[1].tQTaskChildren.ptTail = nullptr;
    v33 = v4->apfExitState[v4->nState];
    if ( v33 )
      v33(v4, v2);
    apfState = v4->apfState;
    v4->nPreviousState = v4->nState;
    v4->nState = 1;
    v35 = apfState[1];
    v4->pfState = v35;
    v35(v4, v2);
  }
}

void __cdecl sub_4BF1E0(_DWORD *a1, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct AnimHeader_s *v29; };
    struct { char igi2_o1[32]; struct QReference_s *v30; };
    struct { char igi2_o2[36]; struct QTask_s *v31; };
    struct { char igi2_o3[40]; int v32; };
    struct { char igi2_o4[44]; int v33; };
    struct { char igi2_o5[48]; struct QTask_s *v34; };
    struct { char igi2_o6[56]; struct AnimHeader_s *ptAnim; };
    struct { char igi2_o7[60]; float v36; };
    char igi2_extent[64];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  void (__cdecl *v2)(_DWORD *, struct QTask_s *); // eax
  int v3; // eax
  void (__cdecl *v4)(_DWORD *, struct QTask_s *); // eax
  struct QTask_s *ptPrev; // ecx
  int v6; // eax
  int v7; // ebx
  struct QTask_s *v8; // eax
  struct QTask_s *v9; // ecx
  struct QTask_s *v10; // ecx
  struct QTask_s *v11; // eax
  void (__cdecl *v12)(struct QTask_s *, struct QReference_s **); // ecx
  struct QTask_s *v13; // eax
  struct QTask_s *v14; // edx
  struct QTask_s *v15; // eax
  struct QTask_s *v16; // ecx
  struct QTask_s *v17; // ecx
  struct QTask_s *v18; // eax
  void (__cdecl *v19)(struct QTask_s *, struct QReference_s **); // ecx
  struct QTask_s *v20; // eax
  struct QTask_s *v21; // ecx
  struct QReference_s *ptTail; // edx
  struct QTask_s *ptNext; // eax
  struct QTask_s *v24; // ecx
  struct QTask_s *v25; // ecx
  struct QTask_s *v26; // eax
  void (__cdecl *pfHandler)(struct QTask_s *, struct QReference_s **); // ecx
  struct QTask_s *v28; // eax

  if ( *(_DWORD *)&ptQTask[32].eQTaskType != 2 )
  {
    *(_DWORD *)&ptQTask[80].eQTaskType = 0;
    ptQTask[80].ptParent = nullptr;
    ptQTask[77].ptPrev = nullptr;
    ptPrev = ptQTask[77].ptPrev;
    v6 = *(_DWORD *)&ptQTask[32].eQTaskType;
    ptQTask[77].tQTaskRefList.ptTail = (struct QReference_s *)7;
    ptQTask[87].tQTaskChildren.ptMiddle = (struct QTask_s *)1;
    v7 = v6 == 2 ? 76 : 83;
    if ( v6 == 2 )
    {
      HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
      if ( v7 == 77 || v7 == 78 || v7 == 79 )
      {
        v21 = ptQTask[77].ptPrev;
        ptTail = ptQTask[7].tQTaskRefList.ptTail;
        igi2_frame.v33 = (int)ptQTask;
        ptNext = ptQTask[33].ptNext;
        igi2_frame.v30 = ptTail;
        igi2_frame.v34 = v21;
        igi2_frame.v31 = ptNext;
        igi2_frame.v32 = 0;
        igi2_frame.ptAnim = nullptr;
        v24 = ptNext[1].ptPrev;
        if ( v24 )
          v25 = v24->tQTaskChildren.ptTail;
        else
          v25 = nullptr;
        v26 = ptNext[1].ptPrev;
        pfHandler = (void (__cdecl *)(struct QTask_s *, struct QReference_s **))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][v25->eQTaskType].pfHandler;
        if ( v26 )
          v28 = v26->tQTaskChildren.ptTail;
        else
          v28 = nullptr;
        pfHandler(v28, &igi2_frame.v30);
        if ( igi2_frame.ptAnim )
        {
          HumanAnim_SetAnimation(ptQTask, igi2_frame.ptAnim, 0, 0.0);
          ptQTask[34].tQTaskChildren.ptTail[1].tQTaskRefList.ptTail = (struct QReference_s *)(__int64)((double)AnimController_nTicksPerFrame * igi2_frame.v36);
        }
        goto LABEL_39;
      }
      if ( v7 != 90 && v7 != 91 )
      {
        HumanAnim_SetAnimationAndTimeFromState(ptQTask, v7, 0, 0.0);
        goto LABEL_39;
      }
      v14 = ptQTask[77].ptPrev;
      igi2_frame.v30 = ptQTask[7].tQTaskRefList.ptTail;
      v15 = ptQTask[33].ptNext;
      igi2_frame.v33 = (int)ptQTask;
      igi2_frame.v34 = v14;
      igi2_frame.v31 = v15;
      igi2_frame.v32 = 0;
      igi2_frame.ptAnim = nullptr;
      v16 = v15[1].ptPrev;
      if ( v16 )
        v17 = v16->tQTaskChildren.ptTail;
      else
        v17 = nullptr;
      v18 = v15[1].ptPrev;
      v19 = (void (__cdecl *)(struct QTask_s *, struct QReference_s **))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][v17->eQTaskType].pfHandler;
      if ( v18 )
        v20 = v18->tQTaskChildren.ptTail;
      else
        v20 = nullptr;
      v19(v20, &igi2_frame.v30);
      if ( igi2_frame.ptAnim )
      {
        HumanAnim_SetUpperBodyAnimationFromHeader(ptQTask, igi2_frame.ptAnim, 0, 0.0);
        ptQTask[34].tQTaskRefList.ptHead[5].pxObject = (void *)(__int64)((double)AnimController_nTicksPerFrame * igi2_frame.v36);
        goto LABEL_39;
      }
    }
    else
    {
      if ( !ptPrev )
      {
        HumanAnim_SetUpperBodyAnimationAndTimeFromState(ptQTask, v7, 0, 0.0);
        goto LABEL_39;
      }
      igi2_frame.v30 = ptQTask[7].tQTaskRefList.ptTail;
      v8 = ptQTask[33].ptNext;
      igi2_frame.v33 = 17;
      igi2_frame.v34 = ptPrev;
      igi2_frame.v31 = v8;
      igi2_frame.v32 = 0;
      igi2_frame.ptAnim = nullptr;
      v9 = v8[1].ptPrev;
      if ( v9 )
        v10 = v9->tQTaskChildren.ptTail;
      else
        v10 = nullptr;
      v11 = v8[1].ptPrev;
      v12 = (void (__cdecl *)(struct QTask_s *, struct QReference_s **))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][v10->eQTaskType].pfHandler;
      if ( v11 )
        v13 = v11->tQTaskChildren.ptTail;
      else
        v13 = nullptr;
      v12(v13, &igi2_frame.v30);
      if ( igi2_frame.ptAnim )
      {
        igi2_frame.v29 = igi2_frame.ptAnim;
        ptQTask[35].tQTaskRefList.ptHead = (struct QReference_s *)83;
        HumanAnim_SetUpperBodyAnimationFromHeader(ptQTask, igi2_frame.v29, 0, 0.0);
LABEL_39:
        HumanPlayer_SetWeaponTypeAnim(ptQTask, WEAPONTYPE_GETANIMTYPE_1STFIRE, 0, false);
        a1[6] = HumanPlayer_RunActionThrowGrenade;
        return;
      }
    }
    HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
    goto LABEL_39;
  }
  v2 = *(void (__cdecl **)(_DWORD *, struct QTask_s *))(a1[2] + 4 * a1[5]);
  if ( v2 )
    v2(a1, ptQTask);
  v3 = a1[1];
  a1[4] = a1[5];
  a1[5] = 1;
  v4 = *(void (__cdecl **)(_DWORD *, struct QTask_s *))(v3 + 4);
  a1[6] = v4;
  v4(a1, ptQTask);
}

int __cdecl sub_4BF4E0(int a1, int a2)
{
  *(_BYTE *)(a2 + 3361) = 1;
  *(_DWORD *)(a1 + 24) = sub_4BF510;
  return sub_4BF510((_DWORD *)a1, (struct QTask_s *)a2);
}

int __cdecl sub_4BF510(_DWORD *a1, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct AnimHeader_s *v72; };
    struct { struct AnimHeader_s *v73; };
    struct { char igi2_o2[20]; int v74; };
    struct { char igi2_o3[24]; int eAnimType; };
    struct { char igi2_o4[40]; struct WeaponGetFireTypeAmmoContext_s nFireType; };
    struct { char igi2_o5[64]; struct AnimHeader_s *ptAnim; };
    struct { char igi2_o6[68]; float v78; };
    char igi2_extent[72];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Weapon_s *ptNext; // eax
  struct QTask_s *ptPrev; // ebx
  _DWORD *v4; // esi
  void (__cdecl *v5)(_DWORD *, struct QTask_s *); // eax
  int (__cdecl **v6)(_DWORD *, struct QTask_s *); // ecx
  int (__cdecl *v7)(_DWORD *, struct QTask_s *); // eax
  int result; // eax
  struct QTask_s *v9; // eax
  struct RandomState_s *p_tRunRandomState; // eax
  double RandomNumberReal32; // st7
  int v12; // eax
  struct QTask_s *v13; // ecx
  int v14; // esi
  struct QTask_s *v15; // eax
  struct QTask_s *v16; // ecx
  struct QTask_s *v17; // ecx
  struct QTask_s *v18; // eax
  void (__cdecl *v19)(struct QTask_s *, struct WeaponGetFireTypeAmmoContext_s *); // ecx
  struct QTask_s *v20; // eax
  struct QTask_s *v21; // edx
  struct QTask_s *v22; // eax
  struct QTask_s *v23; // ecx
  struct QTask_s *v24; // ecx
  struct QTask_s *v25; // eax
  void (__cdecl *v26)(struct QTask_s *, struct WeaponGetFireTypeAmmoContext_s *); // ecx
  struct QTask_s *v27; // eax
  struct QTask_s *v28; // ecx
  struct QReference_s *ptTail; // edx
  struct QTask_s *v30; // eax
  struct QTask_s *v31; // ecx
  struct QTask_s *v32; // ecx
  struct QTask_s *v33; // eax
  void (__cdecl *pfHandler)(struct QTask_s *, struct WeaponGetFireTypeAmmoContext_s *); // ecx
  struct QTask_s *v35; // eax
  void (__cdecl *v36)(_DWORD *, struct QTask_s *); // eax
  int v37; // eax
  int (__cdecl *v38)(_DWORD *, struct QTask_s *); // eax
  struct QTask_s *v39; // eax
  struct QTask_s *v40; // ecx
  struct QTask_s *v41; // edx
  bool v42; // zf
  void (__cdecl *v43)(_DWORD *, struct QTask_s *); // eax
  int v44; // edx
  int (__cdecl *v45)(_DWORD *, struct QTask_s *); // eax
  struct RandomState_s *v46; // eax
  double v47; // st7
  int v48; // eax
  struct QTask_s *v49; // ecx
  int v50; // esi
  struct QTask_s *v51; // eax
  struct QTask_s *v52; // ecx
  struct QTask_s *v53; // ecx
  struct QTask_s *v54; // eax
  void (__cdecl *v55)(struct QTask_s *, struct WeaponGetFireTypeAmmoContext_s *); // ecx
  struct QTask_s *v56; // eax
  struct QTask_s *v57; // edx
  struct QTask_s *v58; // eax
  struct QTask_s *v59; // ecx
  struct QTask_s *v60; // ecx
  struct QTask_s *v61; // eax
  void (__cdecl *v62)(struct QTask_s *, struct WeaponGetFireTypeAmmoContext_s *); // ecx
  struct QTask_s *v63; // eax
  struct QTask_s *v64; // ecx
  struct QReference_s *v65; // edx
  struct QTask_s *v66; // eax
  struct QTask_s *v67; // ecx
  struct QTask_s *v68; // ecx
  struct QTask_s *v69; // eax
  void (__cdecl *v70)(struct QTask_s *, struct WeaponGetFireTypeAmmoContext_s *); // ecx
  struct QTask_s *v71; // eax

  ptNext = (struct Weapon_s *)ptQTask[33].ptNext;
  ptPrev = ptQTask[77].ptPrev;
  ptQTask[83].ptParent = nullptr;
  Weapon_GetFireTypeAmmoInfoFromWeaponTypeItem(ptNext, ptNext->tPrivate.ptActiveWeapon, (int)ptPrev, &igi2_frame.nFireType);
  v4 = a1;
  igi2_frame.eAnimType = a1[3];
  if ( LOBYTE(ptQTask[76].tQTaskRefList.ptMiddle) )
  {
    v5 = *(void (__cdecl **)(_DWORD *, struct QTask_s *))(a1[2] + 4 * a1[5]);
    if ( v5 )
      v5(a1, ptQTask);
    v6 = (int (__cdecl **)(_DWORD *, struct QTask_s *))a1[1];
    a1[4] = a1[5];
    a1[5] = 0;
    v7 = *v6;
    a1[6] = *v6;
    return v7(a1, ptQTask);
  }
  if ( *((float *)&ptQTask[19].ptPrev + HumanPlayer_anFireTypeChannel[(int)ptQTask[77].ptPrev]) == 0.0
    && !BYTE1(ptQTask[84].ptNext) )
  {
    v9 = ptQTask[33].ptNext;
    if ( v9[1].tQTaskChildren.ptTail != (struct QTask_s *)5 )
    {
      LOBYTE(ptQTask[84].ptNext) = 0;
      if ( !v9[16].ptParent )
      {
LABEL_44:
        v36 = *(void (__cdecl **)(_DWORD *, struct QTask_s *))(v4[2] + 4 * v4[5]);
        if ( v36 )
          v36(v4, ptQTask);
        v37 = v4[1];
        v4[4] = v4[5];
        v4[5] = 4;
        v38 = *(int (__cdecl **)(_DWORD *, struct QTask_s *))(v37 + 16);
        v4[6] = v38;
        return v38(v4, ptQTask);
      }
      HumanPlayer_Kickback(ptQTask);
      ptQTask[33].ptNext[16].ptParent = nullptr;
      p_tRunRandomState = &Game_ptGame->tRunRandomState;
      ptQTask[77].tQTaskRefList.ptTail = (struct QReference_s *)6;
      ptQTask[87].tQTaskChildren.ptMiddle = (struct QTask_s *)1;
      RandomNumberReal32 = Random_GetRandomNumberReal32(p_tRunRandomState);
      v12 = *(_DWORD *)&ptQTask[32].eQTaskType;
      v13 = ptQTask[77].ptPrev;
      v14 = v12 == 2 ? 76 : 83;
      if ( v12 == 2 )
      {
        HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
        if ( v14 == 77 || v14 == 78 || v14 == 79 )
        {
          v28 = ptQTask[77].ptPrev;
          ptTail = ptQTask[7].tQTaskRefList.ptTail;
          igi2_frame.nFireType.nBulletsPerRound = (__int64)(RandomNumberReal32 * 0.17499999701976776 * 4800.0);
          v30 = ptQTask[33].ptNext;
          igi2_frame.nFireType.ptAmmoType = (struct AmmoType_s *)ptTail;
          igi2_frame.nFireType.nRoundsPerClip = (int)v28;
          igi2_frame.nFireType.nAmmoInWeapon = (int)v30;
          igi2_frame.nFireType.nAmmoAvailable = 0;
          igi2_frame.ptAnim = nullptr;
          v31 = v30[1].ptPrev;
          if ( v31 )
            v32 = v31->tQTaskChildren.ptTail;
          else
            v32 = nullptr;
          v33 = v30[1].ptPrev;
          pfHandler = (void (__cdecl *)(struct QTask_s *, struct WeaponGetFireTypeAmmoContext_s *))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][v32->eQTaskType].pfHandler;
          if ( v33 )
            v35 = v33->tQTaskChildren.ptTail;
          else
            v35 = nullptr;
          pfHandler(v35, &igi2_frame.nFireType);
          if ( igi2_frame.ptAnim )
          {
            HumanAnim_SetAnimation(ptQTask, igi2_frame.ptAnim, 0, 0.0);
            ptQTask[34].tQTaskChildren.ptTail[1].tQTaskRefList.ptTail = (struct QReference_s *)(__int64)((double)AnimController_nTicksPerFrame * igi2_frame.v78);
          }
          goto LABEL_43;
        }
        if ( v14 != 90 && v14 != 91 )
        {
          HumanAnim_SetAnimationAndTimeFromState(ptQTask, v14, 0, 0.0);
          goto LABEL_43;
        }
        v21 = ptQTask[77].ptPrev;
        igi2_frame.nFireType.ptAmmoType = (struct AmmoType_s *)ptQTask[7].tQTaskRefList.ptTail;
        v22 = ptQTask[33].ptNext;
        igi2_frame.nFireType.nBulletsPerRound = (__int64)(RandomNumberReal32 * 0.17499999701976776 * 4800.0);
        igi2_frame.nFireType.nRoundsPerClip = (int)v21;
        igi2_frame.nFireType.nAmmoInWeapon = (int)v22;
        igi2_frame.nFireType.nAmmoAvailable = 0;
        igi2_frame.ptAnim = nullptr;
        v23 = v22[1].ptPrev;
        if ( v23 )
          v24 = v23->tQTaskChildren.ptTail;
        else
          v24 = nullptr;
        v25 = v22[1].ptPrev;
        v26 = (void (__cdecl *)(struct QTask_s *, struct WeaponGetFireTypeAmmoContext_s *))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][v24->eQTaskType].pfHandler;
        if ( v25 )
          v27 = v25->tQTaskChildren.ptTail;
        else
          v27 = nullptr;
        v26(v27, &igi2_frame.nFireType);
        if ( igi2_frame.ptAnim )
        {
          HumanAnim_SetUpperBodyAnimationFromHeader(ptQTask, igi2_frame.ptAnim, 0, 0.0);
          ptQTask[34].tQTaskRefList.ptHead[5].pxObject = (void *)(__int64)((double)AnimController_nTicksPerFrame * igi2_frame.v78);
          goto LABEL_43;
        }
      }
      else
      {
        if ( !v13 )
        {
          HumanAnim_SetUpperBodyAnimationAndTimeFromState(ptQTask, v12 == 2 ? 76 : 83, 0, 0.0);
          goto LABEL_43;
        }
        igi2_frame.nFireType.ptAmmoType = (struct AmmoType_s *)ptQTask[7].tQTaskRefList.ptTail;
        v15 = ptQTask[33].ptNext;
        igi2_frame.nFireType.nBulletsPerRound = 17;
        igi2_frame.nFireType.nRoundsPerClip = (int)v13;
        igi2_frame.nFireType.nAmmoInWeapon = (int)v15;
        igi2_frame.nFireType.nAmmoAvailable = 0;
        igi2_frame.ptAnim = nullptr;
        v16 = v15[1].ptPrev;
        if ( v16 )
          v17 = v16->tQTaskChildren.ptTail;
        else
          v17 = nullptr;
        v18 = v15[1].ptPrev;
        v19 = (void (__cdecl *)(struct QTask_s *, struct WeaponGetFireTypeAmmoContext_s *))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][v17->eQTaskType].pfHandler;
        if ( v18 )
          v20 = v18->tQTaskChildren.ptTail;
        else
          v20 = nullptr;
        v19(v20, &igi2_frame.nFireType);
        if ( igi2_frame.ptAnim )
        {
          igi2_frame.v72 = igi2_frame.ptAnim;
          ptQTask[35].tQTaskRefList.ptHead = (struct QReference_s *)83;
          HumanAnim_SetUpperBodyAnimationFromHeader(ptQTask, igi2_frame.v72, 0, 0.0);
LABEL_43:
          HumanPlayer_SetWeaponTypeAnim(
            ptQTask,
            WEAPONTYPE_GETANIMTYPE_1STFIRE,
            (__int64)(RandomNumberReal32 * 0.17499999701976776 * 4800.0),
            false);
          v4 = a1;
          goto LABEL_44;
        }
      }
      HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
      goto LABEL_43;
    }
  }
  v39 = ptQTask[33].ptNext;
  v40 = v39[1].ptPrev;
  v41 = v39[1].tQTaskChildren.ptTail;
  if ( v40 )
    igi2_frame.v74 = (int)v40->tQTaskChildren.ptTail;
  else
    igi2_frame.v74 = 0;
  if ( v41 == (struct QTask_s *)1 )
  {
    if ( !v39[16].ptParent )
      goto LABEL_94;
    HumanPlayer_Kickback(ptQTask);
    ptQTask[33].ptNext[16].ptParent = nullptr;
    v46 = &Game_ptGame->tRunRandomState;
    ptQTask[77].tQTaskRefList.ptTail = (struct QReference_s *)6;
    ptQTask[87].tQTaskChildren.ptMiddle = (struct QTask_s *)1;
    v47 = Random_GetRandomNumberReal32(v46);
    v48 = *(_DWORD *)&ptQTask[32].eQTaskType;
    v49 = ptQTask[77].ptPrev;
    v50 = v48 == 2 ? 76 : 83;
    if ( v48 == 2 )
    {
      HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
      if ( v50 == 77 || v50 == 78 || v50 == 79 )
      {
        v64 = ptQTask[77].ptPrev;
        v65 = ptQTask[7].tQTaskRefList.ptTail;
        igi2_frame.nFireType.nBulletsPerRound = (__int64)(v47 * 0.17499999701976776 * 4800.0);
        v66 = ptQTask[33].ptNext;
        igi2_frame.nFireType.ptAmmoType = (struct AmmoType_s *)v65;
        igi2_frame.nFireType.nRoundsPerClip = (int)v64;
        igi2_frame.nFireType.nAmmoInWeapon = (int)v66;
        igi2_frame.nFireType.nAmmoAvailable = 0;
        igi2_frame.ptAnim = nullptr;
        v67 = v66[1].ptPrev;
        if ( v67 )
          v68 = v67->tQTaskChildren.ptTail;
        else
          v68 = nullptr;
        v69 = v66[1].ptPrev;
        v70 = (void (__cdecl *)(struct QTask_s *, struct WeaponGetFireTypeAmmoContext_s *))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][v68->eQTaskType].pfHandler;
        if ( v69 )
          v71 = v69->tQTaskChildren.ptTail;
        else
          v71 = nullptr;
        v70(v71, &igi2_frame.nFireType);
        if ( igi2_frame.ptAnim )
        {
          HumanAnim_SetAnimation(ptQTask, igi2_frame.ptAnim, 0, 0.0);
          ptQTask[34].tQTaskChildren.ptTail[1].tQTaskRefList.ptTail = (struct QReference_s *)(__int64)((double)AnimController_nTicksPerFrame * igi2_frame.v78);
        }
        goto LABEL_93;
      }
      if ( v50 != 90 && v50 != 91 )
      {
        HumanAnim_SetAnimationAndTimeFromState(ptQTask, v50, 0, 0.0);
        goto LABEL_93;
      }
      v57 = ptQTask[77].ptPrev;
      igi2_frame.nFireType.ptAmmoType = (struct AmmoType_s *)ptQTask[7].tQTaskRefList.ptTail;
      v58 = ptQTask[33].ptNext;
      igi2_frame.nFireType.nBulletsPerRound = (__int64)(v47 * 0.17499999701976776 * 4800.0);
      igi2_frame.nFireType.nRoundsPerClip = (int)v57;
      igi2_frame.nFireType.nAmmoInWeapon = (int)v58;
      igi2_frame.nFireType.nAmmoAvailable = 0;
      igi2_frame.ptAnim = nullptr;
      v59 = v58[1].ptPrev;
      if ( v59 )
        v60 = v59->tQTaskChildren.ptTail;
      else
        v60 = nullptr;
      v61 = v58[1].ptPrev;
      v62 = (void (__cdecl *)(struct QTask_s *, struct WeaponGetFireTypeAmmoContext_s *))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][v60->eQTaskType].pfHandler;
      if ( v61 )
        v63 = v61->tQTaskChildren.ptTail;
      else
        v63 = nullptr;
      v62(v63, &igi2_frame.nFireType);
      if ( igi2_frame.ptAnim )
      {
        HumanAnim_SetUpperBodyAnimationFromHeader(ptQTask, igi2_frame.ptAnim, 0, 0.0);
        ptQTask[34].tQTaskRefList.ptHead[5].pxObject = (void *)(__int64)((double)AnimController_nTicksPerFrame * igi2_frame.v78);
        goto LABEL_93;
      }
    }
    else
    {
      if ( !v49 )
      {
        HumanAnim_SetUpperBodyAnimationAndTimeFromState(ptQTask, v48 == 2 ? 76 : 83, 0, 0.0);
        goto LABEL_93;
      }
      igi2_frame.nFireType.ptAmmoType = (struct AmmoType_s *)ptQTask[7].tQTaskRefList.ptTail;
      v51 = ptQTask[33].ptNext;
      igi2_frame.nFireType.nBulletsPerRound = 17;
      igi2_frame.nFireType.nRoundsPerClip = (int)v49;
      igi2_frame.nFireType.nAmmoInWeapon = (int)v51;
      igi2_frame.nFireType.nAmmoAvailable = 0;
      igi2_frame.ptAnim = nullptr;
      v52 = v51[1].ptPrev;
      if ( v52 )
        v53 = v52->tQTaskChildren.ptTail;
      else
        v53 = nullptr;
      v54 = v51[1].ptPrev;
      v55 = (void (__cdecl *)(struct QTask_s *, struct WeaponGetFireTypeAmmoContext_s *))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][v53->eQTaskType].pfHandler;
      if ( v54 )
        v56 = v54->tQTaskChildren.ptTail;
      else
        v56 = nullptr;
      v55(v56, &igi2_frame.nFireType);
      if ( igi2_frame.ptAnim )
      {
        igi2_frame.v73 = igi2_frame.ptAnim;
        ptQTask[35].tQTaskRefList.ptHead = (struct QReference_s *)83;
        HumanAnim_SetUpperBodyAnimationFromHeader(ptQTask, igi2_frame.v73, 0, 0.0);
LABEL_93:
        HumanPlayer_SetWeaponTypeAnim(
          ptQTask,
          WEAPONTYPE_GETANIMTYPE_1STFIRE,
          (__int64)(v47 * 0.17499999701976776 * 4800.0),
          false);
        goto LABEL_94;
      }
    }
    HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
    goto LABEL_93;
  }
  if ( v41 != (struct QTask_s *)4 )
    goto LABEL_94;
  v42 = *(&ptQTask[83].isInMemPool + 1) == 0;
  BYTE1(ptQTask[84].ptNext) = 0;
  if ( !v42 )
  {
    Weapon_Reload(v39);
    HumanPlayer_SendHandleWeaponAIEvent(ptQTask, 20480.0);
    goto LABEL_94;
  }
  *((_DWORD *)&v39->ptNext + 7 * (int)&ptQTask[77].ptPrev->ptPrev) = 1;
  v39[1].tQTaskChildren.ptTail = nullptr;
  if ( (igi2_frame.eAnimType & 1) == 0 )
  {
LABEL_94:
    result = igi2_frame.v74;
    if ( *(_DWORD *)(igi2_frame.v74 + 20 * ((int)&ptQTask[77].ptPrev[1].tQTaskRefList.ptMiddle + 1)) != 512
      && (BYTE1(ptQTask[84].ptNext) || *(_DWORD *)(igi2_frame.v74 + 672) == 10) )
    {
      LOBYTE(ptQTask[84].ptNext) = 1;
    }
    BYTE1(ptQTask[84].ptNext) = 0;
    return result;
  }
  v43 = *(void (__cdecl **)(_DWORD *, struct QTask_s *))(a1[2] + 4 * a1[5]);
  if ( v43 )
    v43(a1, ptQTask);
  v44 = a1[1];
  a1[4] = a1[5];
  a1[5] = 9;
  v45 = *(int (__cdecl **)(_DWORD *, struct QTask_s *))(v44 + 36);
  a1[6] = v45;
  return v45(a1, ptQTask);
}

// source: j/0/human/humanplayer.c:14282  [size]
void __cdecl HumanPlayer_InitActionFire(struct State_s *ptState, struct QTask_s *ptQTask)
{
  ptState->pfState = (void (__cdecl *)(struct State_s *, struct QTask_s *))HumanPlayer_RunActionFire;
}

// source: j/0/human/humanplayer.c:14292  [size]
void __cdecl HumanPlayer_RunActionFire(struct State_s *ptState, struct QTask_s *ptQTask)
{
  ;
}

// source: j/0/human/humanplayer.c:14305  [anchor-mhash]
void __cdecl HumanPlayer_InitActionFireRelease(struct State_s *ptState, struct QTask_s *ptQTask)
{
  struct QTask_s *ptNext; // eax

  ptNext = ptQTask[33].ptNext;
  *((_DWORD *)&ptNext->ptNext + 7 * (int)&ptQTask[77].ptPrev->ptPrev) = 1;
  ptNext[1].tQTaskChildren.ptTail = nullptr;
  ptState->pfState = HumanPlayer_RunActionFireRelease;
}

// source: j/0/human/humanplayer.c:14321  [anchor-mhash]
void __cdecl HumanPlayer_RunActionFireRelease(struct State_s *ptState, struct QTask_s *ptQTask)
{
  void (__cdecl *v2)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v4)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v5)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v6)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v7)(struct State_s *, struct QTask_s *); // eax

  if ( (ptState->bSignal & 1) != 0 )
  {
    v2 = ptState->apfExitState[ptState->nState];
    if ( v2 )
      v2(ptState, ptQTask);
    apfState = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 1;
    v4 = apfState[1];
    ptState->pfState = v4;
    v4(ptState, ptQTask);
  }
  else if ( *(float *)&ptQTask[19].tQTaskRefList.ptTail != 0.0 || *(float *)&ptQTask[19].ptParent != 0.0 )
  {
    ptQTask[77].ptPrev = (struct QTask_s *)(*(float *)&ptQTask[19].ptParent != 0.0);
    v5 = ptState->apfExitState[ptState->nState];
    if ( v5 )
      v5(ptState, ptQTask);
    v6 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 2;
    v7 = v6[2];
    ptState->pfState = v7;
    v7(ptState, ptQTask);
  }
}

// source: j/0/human/humanplayer.c:14361  [anchor-strings]
void __cdecl HumanPlayer_InitActionFireEmpty(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QReference_s *v19; };
    struct { char igi2_o1[4]; struct QTask_s *v20; };
    struct { char igi2_o2[8]; int v21; };
    struct { char igi2_o3[12]; struct QTask_s *v22; };
    struct { char igi2_o4[16]; struct QTask_s *v23; };
    struct { char igi2_o5[24]; struct AnimHeader_s *ptAnim; };
    struct { char igi2_o6[28]; float v25; };
    char igi2_extent[32];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // eax
  int v3; // ebx
  struct QTask_s *v4; // edx
  struct QTask_s *v5; // eax
  struct QTask_s *v6; // ecx
  struct QTask_s *v7; // ecx
  struct QTask_s *v8; // eax
  void (__cdecl *v9)(struct QTask_s *, struct QReference_s **); // ecx
  struct QTask_s *v10; // eax
  struct QTask_s *ptPrev; // ecx
  struct QReference_s *ptTail; // edx
  struct QTask_s *ptNext; // eax
  struct QTask_s *v14; // ecx
  struct QTask_s *v15; // ecx
  struct QTask_s *v16; // eax
  void (__cdecl *pfHandler)(struct QTask_s *, struct QReference_s **); // ecx
  struct QTask_s *v18; // eax

  ptQTask[77].tQTaskRefList.ptTail = (struct QReference_s *)1;
  ptQTask[87].tQTaskChildren.ptMiddle = (struct QTask_s *)1;
  v2 = *(_DWORD *)&ptQTask[32].eQTaskType;
  v3 = v2 != 2 ? 0 : 0x4B;
  if ( v2 == 2 )
  {
    HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
    if ( v3 == 77 || v3 == 78 || v3 == 79 )
    {
      ptPrev = ptQTask[77].ptPrev;
      ptTail = ptQTask[7].tQTaskRefList.ptTail;
      igi2_frame.v22 = ptQTask;
      ptNext = ptQTask[33].ptNext;
      igi2_frame.v19 = ptTail;
      igi2_frame.v23 = ptPrev;
      igi2_frame.v20 = ptNext;
      igi2_frame.v21 = 0;
      igi2_frame.ptAnim = nullptr;
      v14 = ptNext[1].ptPrev;
      if ( v14 )
        v15 = v14->tQTaskChildren.ptTail;
      else
        v15 = nullptr;
      v16 = ptNext[1].ptPrev;
      pfHandler = (void (__cdecl *)(struct QTask_s *, struct QReference_s **))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][v15->eQTaskType].pfHandler;
      if ( v16 )
        v18 = v16->tQTaskChildren.ptTail;
      else
        v18 = nullptr;
      pfHandler(v18, &igi2_frame.v19);
      if ( igi2_frame.ptAnim )
      {
        HumanAnim_SetAnimation(ptQTask, igi2_frame.ptAnim, 0, 0.0);
        ptQTask[34].tQTaskChildren.ptTail[1].tQTaskRefList.ptTail = (struct QReference_s *)(__int64)((double)AnimController_nTicksPerFrame * igi2_frame.v25);
      }
    }
    else if ( v3 == 90 || v3 == 91 )
    {
      v4 = ptQTask[77].ptPrev;
      igi2_frame.v19 = ptQTask[7].tQTaskRefList.ptTail;
      v5 = ptQTask[33].ptNext;
      igi2_frame.v22 = ptQTask;
      igi2_frame.v23 = v4;
      igi2_frame.v20 = v5;
      igi2_frame.v21 = 0;
      igi2_frame.ptAnim = nullptr;
      v6 = v5[1].ptPrev;
      if ( v6 )
        v7 = v6->tQTaskChildren.ptTail;
      else
        v7 = nullptr;
      v8 = v5[1].ptPrev;
      v9 = (void (__cdecl *)(struct QTask_s *, struct QReference_s **))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][v7->eQTaskType].pfHandler;
      if ( v8 )
        v10 = v8->tQTaskChildren.ptTail;
      else
        v10 = nullptr;
      v9(v10, &igi2_frame.v19);
      if ( igi2_frame.ptAnim )
      {
        HumanAnim_SetUpperBodyAnimationFromHeader(ptQTask, igi2_frame.ptAnim, 0, 0.0);
        ptQTask[34].tQTaskRefList.ptHead[5].pxObject = (void *)(__int64)((double)AnimController_nTicksPerFrame * igi2_frame.v25);
      }
      else
      {
        HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
      }
    }
    else
    {
      HumanAnim_SetAnimationAndTimeFromState(ptQTask, v3, 0, 0.0);
    }
  }
  else
  {
    HumanAnim_SetUpperBodyAnimationAndTimeFromState(ptQTask, v3, 0, 0.0);
  }
  HumanPlayer_SetWeaponTypeAnim(ptQTask, WEAPONTYPE_GETANIMTYPE_1STSTAND, 0, false);
  SoundSys_NewSoundFn(ptQTask[33].tQTaskChildren.ptTail, "guns_dry_1");
  ptState->pfState = HumanPlayer_RunActionFireEmpty;
}

// source: j/0/human/humanplayer.c:14380  [anchor-mhash]
void __cdecl HumanPlayer_RunActionFireEmpty(struct State_s *ptState, struct QTask_s *ptQTask)
{
  void (__cdecl *v2)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v4)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v5)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v6)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v7)(struct State_s *, struct QTask_s *); // eax

  if ( LOBYTE(ptQTask[76].tQTaskRefList.ptMiddle) )
  {
    v2 = ptState->apfExitState[ptState->nState];
    if ( v2 )
      v2(ptState, ptQTask);
    apfState = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 0;
    v4 = *apfState;
    ptState->pfState = v4;
    v4(ptState, ptQTask);
  }
  else if ( *((float *)&ptQTask[19].ptPrev + HumanPlayer_anFireTypeChannel[(int)ptQTask[77].ptPrev]) == 0.0 )
  {
    v5 = ptState->apfExitState[ptState->nState];
    if ( v5 )
      v5(ptState, ptQTask);
    v6 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 1;
    v7 = v6[1];
    ptState->pfState = v7;
    v7(ptState, ptQTask);
  }
}

// source: j/0/human/humanplayer.c:14408  [anchor-mhash]
enum bool __cdecl HumanPlayer_IsWeaponAnimDefined(
        struct HumanPlayer_t *ptHumanPlayer,
        enum WeaponTypeGetAnimType_e eAnimType)
{
  struct QTask_s *ptWeaponQTask; // edx
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptTail; // eax
  unsigned __int8 *v5; // esi
  int vIdealModifiedPrecision_low; // ecx
  struct WeaponTypeGetAnimContext_s tGetAnimContext; // [esp+4h] [ebp-20h] BYREF

  ptWeaponQTask = ptHumanPlayer->tHuman.ptWeaponQTask;
  ptPrev = ptWeaponQTask[1].ptPrev;
  if ( !ptPrev )
    return false;
  ptTail = ptPrev->tQTaskChildren.ptTail;
  if ( !ptTail )
    return false;
  v5 = (unsigned __int8 *)ptHumanPlayer->tHuman.ptHumanViewQTask[7].tQTaskRefList.ptTail;
  vIdealModifiedPrecision_low = LODWORD(ptHumanPlayer->vIdealModifiedPrecision);
  tGetAnimContext.tIn.ptWeapon = ptWeaponQTask;
  tGetAnimContext.tIn.ptHierarchy = v5;
  tGetAnimContext.tIn.nFireType = vIdealModifiedPrecision_low;
  tGetAnimContext.tIn.eAnimType = eAnimType;
  tGetAnimContext.tIn.ptWeaponType = nullptr;
  tGetAnimContext.tOut.ptAnim = nullptr;
  ((void (__cdecl *)(struct QTask_s *, struct WeaponTypeGetAnimContext_s *))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][ptTail->eQTaskType].pfHandler)(
    ptTail,
    &tGetAnimContext);
  return tGetAnimContext.tOut.ptAnim != nullptr;
}

// source: j/0/human/humanplayer.c:14448  [anchor-mhash]
void __cdecl HumanPlayer_InitActionReload(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QReference_s *ptTail; };
    struct { char igi2_o1[4]; struct QTask_s *v29; };
    struct { char igi2_o2[8]; int v30; };
    struct { char igi2_o3[12]; int v31; };
    struct { char igi2_o4[16]; struct QTask_s *v32; };
    struct { char igi2_o5[24]; struct AnimHeader_s *ptAnim; };
    struct { char igi2_o6[28]; float v34; };
    char igi2_extent[32];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // eax
  int v3; // ebx
  struct QTask_s *ptPrev; // ecx
  struct QTask_s *ptNext; // eax
  struct QTask_s *v6; // ecx
  struct QTask_s *v7; // ecx
  struct QTask_s *v8; // eax
  void (__cdecl *pfHandler)(struct QTask_s *, struct QReference_s **); // ecx
  struct QTask_s *v10; // eax
  _DWORD *p_ptNext; // ecx
  int v12; // eax
  struct QTask_s *v13; // ecx
  struct QReference_s *v14; // edx
  struct QTask_s *v15; // eax
  struct QTask_s *v16; // ecx
  struct QTask_s *v17; // ecx
  struct QTask_s *v18; // eax
  void (__cdecl *v19)(struct QTask_s *, struct QReference_s **); // ecx
  struct QTask_s *v20; // eax
  struct QReference_s *v21; // edx
  struct QTask_s *v22; // eax
  struct QTask_s *v23; // ecx
  struct QTask_s *v24; // ecx
  struct QTask_s *v25; // eax
  void (__cdecl *v26)(struct QTask_s *, struct QReference_s **); // ecx
  struct QTask_s *v27; // eax

  ptQTask[77].ptPrev = nullptr;
  v2 = *(_DWORD *)&ptQTask[32].eQTaskType;
  ptQTask[77].tQTaskRefList.ptTail = (struct QReference_s *)8;
  ptQTask[87].tQTaskChildren.ptMiddle = (struct QTask_s *)1;
  v3 = v2 == 2 ? 77 : 84;
  if ( v2 != 2 )
  {
    ptPrev = ptQTask[77].ptPrev;
    igi2_frame.ptTail = ptQTask[7].tQTaskRefList.ptTail;
    ptNext = ptQTask[33].ptNext;
    ptQTask[35].tQTaskRefList.ptHead = (struct QReference_s *)84;
    igi2_frame.v31 = 20;
    igi2_frame.v32 = ptPrev;
    igi2_frame.v29 = ptNext;
    igi2_frame.v30 = 0;
    igi2_frame.ptAnim = nullptr;
    v6 = ptNext[1].ptPrev;
    if ( v6 )
      v7 = v6->tQTaskChildren.ptTail;
    else
      v7 = nullptr;
    v8 = ptNext[1].ptPrev;
    pfHandler = (void (__cdecl *)(struct QTask_s *, struct QReference_s **))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][v7->eQTaskType].pfHandler;
    if ( v8 )
      v10 = v8->tQTaskChildren.ptTail;
    else
      v10 = nullptr;
    pfHandler(v10, &igi2_frame.ptTail);
    if ( igi2_frame.ptAnim )
    {
LABEL_9:
      HumanAnim_SetUpperBodyAnimationFromHeader(ptQTask, igi2_frame.ptAnim, 0, 0.0);
      p_ptNext = &ptQTask[34].tQTaskRefList.ptHead->ptNext;
      v12 = (__int64)((double)AnimController_nTicksPerFrame * igi2_frame.v34);
LABEL_33:
      p_ptNext[17] = v12;
      goto LABEL_34;
    }
LABEL_10:
    HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
    goto LABEL_34;
  }
  HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
  if ( v3 != 77 && v3 != 78 && v3 != 79 )
  {
    if ( v3 != 90 && v3 != 91 )
    {
      HumanAnim_SetAnimationAndTimeFromState(ptQTask, v3, 0, 0.0);
      goto LABEL_34;
    }
    v13 = ptQTask[77].ptPrev;
    v14 = ptQTask[7].tQTaskRefList.ptTail;
    igi2_frame.v31 = (int)ptQTask;
    v15 = ptQTask[33].ptNext;
    igi2_frame.ptTail = v14;
    igi2_frame.v32 = v13;
    igi2_frame.v29 = v15;
    igi2_frame.v30 = 0;
    igi2_frame.ptAnim = nullptr;
    v16 = v15[1].ptPrev;
    if ( v16 )
      v17 = v16->tQTaskChildren.ptTail;
    else
      v17 = nullptr;
    v18 = v15[1].ptPrev;
    v19 = (void (__cdecl *)(struct QTask_s *, struct QReference_s **))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][v17->eQTaskType].pfHandler;
    if ( v18 )
      v20 = v18->tQTaskChildren.ptTail;
    else
      v20 = nullptr;
    v19(v20, &igi2_frame.ptTail);
    if ( igi2_frame.ptAnim )
      goto LABEL_9;
    goto LABEL_10;
  }
  v21 = ptQTask[7].tQTaskRefList.ptTail;
  igi2_frame.v32 = ptQTask[77].ptPrev;
  v22 = ptQTask[33].ptNext;
  ptQTask[35].tQTaskChildren.ptTail = (struct QTask_s *)77;
  igi2_frame.ptTail = v21;
  igi2_frame.v31 = 23;
  igi2_frame.v29 = v22;
  igi2_frame.v30 = 0;
  igi2_frame.ptAnim = nullptr;
  v23 = v22[1].ptPrev;
  if ( v23 )
    v24 = v23->tQTaskChildren.ptTail;
  else
    v24 = nullptr;
  v25 = v22[1].ptPrev;
  v26 = (void (__cdecl *)(struct QTask_s *, struct QReference_s **))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][v24->eQTaskType].pfHandler;
  if ( v25 )
    v27 = v25->tQTaskChildren.ptTail;
  else
    v27 = nullptr;
  v26(v27, &igi2_frame.ptTail);
  if ( igi2_frame.ptAnim )
  {
    HumanAnim_SetAnimation(ptQTask, igi2_frame.ptAnim, 0, 0.0);
    p_ptNext = &ptQTask[34].tQTaskChildren.ptTail->ptNext;
    v12 = (__int64)((double)AnimController_nTicksPerFrame * igi2_frame.v34);
    goto LABEL_33;
  }
LABEL_34:
  HumanPlayer_SetWeaponTypeAnim(ptQTask, WEAPONTYPE_GETANIMTYPE_1STRELOADSTART, 0, false);
  ptState->pfState = HumanPlayer_RunActionReload;
}

// source: j/0/human/humanplayer.c:14464  [anchor-mhash]
void __cdecl HumanPlayer_RunActionReload(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v70; };
    struct { char igi2_o1[8]; struct WeaponGetFireTypeAmmoContext_s nFireType; };
    struct { char igi2_o2[32]; struct AnimHeader_s *ptAnim; };
    struct { char igi2_o3[36]; float v73; };
    char igi2_extent[40];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptTail; // eax
  unsigned int bSignal; // ecx
  struct QTask_s *v5; // eax
  void (__cdecl *v6)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v8)(struct State_s *, struct QTask_s *); // eax
  bool v9; // zf
  struct Weapon_s *ptNext; // eax
  int v11; // eax
  int v12; // ebx
  struct QReference_s *v13; // ecx
  struct QTask_s *v14; // eax
  struct QTask_s *v15; // edx
  struct QTask_s *v16; // ecx
  struct QTask_s *v17; // ecx
  struct QTask_s *v18; // eax
  void (__cdecl *v19)(struct QTask_s *, struct WeaponGetFireTypeAmmoContext_s *); // ecx
  struct QTask_s *v20; // eax
  _DWORD *p_ptNext; // ecx
  int v22; // eax
  struct QTask_s *v23; // ecx
  struct QReference_s *v24; // edx
  struct QTask_s *v25; // eax
  struct QTask_s *v26; // ecx
  struct QTask_s *v27; // ecx
  struct QTask_s *v28; // eax
  void (__cdecl *v29)(struct QTask_s *, struct WeaponGetFireTypeAmmoContext_s *); // ecx
  struct QTask_s *v30; // eax
  struct QReference_s *v31; // edx
  struct QTask_s *v32; // eax
  struct QTask_s *v33; // ecx
  struct QTask_s *v34; // ecx
  struct QTask_s *v35; // eax
  void (__cdecl *pfHandler)(struct QTask_s *, struct WeaponGetFireTypeAmmoContext_s *); // ecx
  struct QTask_s *v37; // eax
  int v38; // eax
  int v39; // ebx
  struct QTask_s *v40; // ecx
  struct QTask_s *v41; // eax
  struct QTask_s *v42; // ecx
  struct QTask_s *v43; // ecx
  struct QTask_s *v44; // eax
  void (__cdecl *v45)(struct QTask_s *, struct WeaponGetFireTypeAmmoContext_s *); // ecx
  struct QTask_s *v46; // eax
  _DWORD *v47; // ecx
  int v48; // eax
  struct QTask_s *v49; // ecx
  struct QReference_s *v50; // edx
  struct QTask_s *v51; // eax
  struct QTask_s *v52; // ecx
  struct QTask_s *v53; // ecx
  struct QTask_s *v54; // eax
  void (__cdecl *v55)(struct QTask_s *, struct WeaponGetFireTypeAmmoContext_s *); // ecx
  struct QTask_s *v56; // eax
  struct QReference_s *v57; // edx
  struct QTask_s *v58; // eax
  struct QTask_s *v59; // ecx
  struct QTask_s *v60; // ecx
  struct QTask_s *v61; // eax
  void (__cdecl *v62)(struct QTask_s *, struct WeaponGetFireTypeAmmoContext_s *); // ecx
  struct QTask_s *v63; // eax
  void (__cdecl *v64)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v65)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v66)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v67)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **v68)(struct State_s *, struct QTask_s *); // ecx
  void (__cdecl *v69)(struct State_s *, struct QTask_s *); // eax

  ptPrev = ptQTask[33].ptNext[1].ptPrev;
  if ( ptPrev )
    ptTail = ptPrev->tQTaskChildren.ptTail;
  else
    ptTail = nullptr;
  bSignal = ptState->bSignal;
  igi2_frame.v70 = bSignal;
  ptQTask[83].ptParent = nullptr;
  if ( ptTail )
  {
    if ( ptQTask[76].ptParent != (struct QTask_s *)-1 )
    {
      v5 = ptQTask[33].tQTaskChildren.ptTail;
      v5[16].tQTaskRefList.ptMiddle = nullptr;
      *(float *)&v5[16].tQTaskChildren.ptHead = tan(0.7853981852531433);
      *(float *)&v5[16].tQTaskRefList.ptHead = tan(0.5235987901687622);
      v6 = ptState->apfExitState[ptState->nState];
      if ( v6 )
        v6(ptState, ptQTask);
      apfState = ptState->apfState;
      ptState->nPreviousState = ptState->nState;
      ptState->nState = 6;
      v8 = apfState[6];
      ptState->pfState = v8;
      v8(ptState, ptQTask);
      return;
    }
    if ( (bSignal & 1) == 0 )
      return;
    v9 = HumanPlayer_IsWeaponAnimDefined((struct HumanPlayer_t *)ptQTask, WEAPONTYPE_GETANIMTYPE_1STRELOADLOOP) == false;
    ptNext = (struct Weapon_s *)ptQTask[33].ptNext;
    if ( !v9 )
    {
      Weapon_GetFireTypeAmmoInfoFromWeaponTypeItem(ptNext, ptNext->tPrivate.ptActiveWeapon, 0, &igi2_frame.nFireType);
      if ( (igi2_frame.v70 & 0x200) == 0 && igi2_frame.nFireType.nAmmoInWeapon != igi2_frame.nFireType.nRoundsPerClip - 1 )
      {
        v11 = *(_DWORD *)&ptQTask[32].eQTaskType;
        ptQTask[77].tQTaskRefList.ptTail = (struct QReference_s *)9;
        ptQTask[87].tQTaskChildren.ptMiddle = (struct QTask_s *)1;
        v12 = v11 == 2 ? 78 : 85;
        if ( v11 == 2 )
        {
          HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
          if ( v12 == 77 || v12 == 78 || v12 == 79 )
          {
            v31 = ptQTask[7].tQTaskRefList.ptTail;
            igi2_frame.nFireType.nRoundsPerClip = (int)ptQTask[77].ptPrev;
            v32 = ptQTask[33].ptNext;
            ptQTask[35].tQTaskChildren.ptTail = (struct QTask_s *)78;
            igi2_frame.nFireType.ptAmmoType = (struct AmmoType_s *)v31;
            igi2_frame.nFireType.nBulletsPerRound = 24;
            igi2_frame.nFireType.nAmmoInWeapon = (int)v32;
            igi2_frame.nFireType.nAmmoAvailable = 0;
            igi2_frame.ptAnim = nullptr;
            v33 = v32[1].ptPrev;
            if ( v33 )
              v34 = v33->tQTaskChildren.ptTail;
            else
              v34 = nullptr;
            v35 = v32[1].ptPrev;
            pfHandler = (void (__cdecl *)(struct QTask_s *, struct WeaponGetFireTypeAmmoContext_s *))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][v34->eQTaskType].pfHandler;
            if ( v35 )
              v37 = v35->tQTaskChildren.ptTail;
            else
              v37 = nullptr;
            pfHandler(v37, &igi2_frame.nFireType);
            if ( !igi2_frame.ptAnim )
              goto LABEL_46;
            HumanAnim_SetAnimation(ptQTask, igi2_frame.ptAnim, 0, 0.0);
            p_ptNext = &ptQTask[34].tQTaskChildren.ptTail->ptNext;
            v22 = (__int64)((double)AnimController_nTicksPerFrame * igi2_frame.v73);
            goto LABEL_45;
          }
          if ( v12 != 90 && v12 != 91 )
          {
            HumanAnim_SetAnimationAndTimeFromState(ptQTask, v12, 0, 0.0);
            goto LABEL_46;
          }
          v23 = ptQTask[77].ptPrev;
          v24 = ptQTask[7].tQTaskRefList.ptTail;
          igi2_frame.nFireType.nBulletsPerRound = igi2_frame.v70;
          v25 = ptQTask[33].ptNext;
          igi2_frame.nFireType.ptAmmoType = (struct AmmoType_s *)v24;
          igi2_frame.nFireType.nRoundsPerClip = (int)v23;
          igi2_frame.nFireType.nAmmoInWeapon = (int)v25;
          igi2_frame.nFireType.nAmmoAvailable = 0;
          igi2_frame.ptAnim = nullptr;
          v26 = v25[1].ptPrev;
          if ( v26 )
            v27 = v26->tQTaskChildren.ptTail;
          else
            v27 = nullptr;
          v28 = v25[1].ptPrev;
          v29 = (void (__cdecl *)(struct QTask_s *, struct WeaponGetFireTypeAmmoContext_s *))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][v27->eQTaskType].pfHandler;
          if ( v28 )
            v30 = v28->tQTaskChildren.ptTail;
          else
            v30 = nullptr;
          v29(v30, &igi2_frame.nFireType);
          if ( igi2_frame.ptAnim )
            goto LABEL_21;
        }
        else
        {
          v13 = ptQTask[7].tQTaskRefList.ptTail;
          v14 = ptQTask[33].ptNext;
          v15 = ptQTask[77].ptPrev;
          ptQTask[35].tQTaskRefList.ptHead = (struct QReference_s *)85;
          igi2_frame.nFireType.ptAmmoType = (struct AmmoType_s *)v13;
          igi2_frame.nFireType.nBulletsPerRound = 21;
          igi2_frame.nFireType.nRoundsPerClip = (int)v15;
          igi2_frame.nFireType.nAmmoInWeapon = (int)v14;
          igi2_frame.nFireType.nAmmoAvailable = 0;
          igi2_frame.ptAnim = nullptr;
          v16 = v14[1].ptPrev;
          if ( v16 )
            v17 = v16->tQTaskChildren.ptTail;
          else
            v17 = nullptr;
          v18 = v14[1].ptPrev;
          v19 = (void (__cdecl *)(struct QTask_s *, struct WeaponGetFireTypeAmmoContext_s *))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][v17->eQTaskType].pfHandler;
          if ( v18 )
            v20 = v18->tQTaskChildren.ptTail;
          else
            v20 = nullptr;
          v19(v20, &igi2_frame.nFireType);
          if ( igi2_frame.ptAnim )
          {
LABEL_21:
            HumanAnim_SetUpperBodyAnimationFromHeader(ptQTask, igi2_frame.ptAnim, 0, 0.0);
            p_ptNext = &ptQTask[34].tQTaskRefList.ptHead->ptNext;
            v22 = (__int64)((double)AnimController_nTicksPerFrame * igi2_frame.v73);
LABEL_45:
            p_ptNext[17] = v22;
            goto LABEL_46;
          }
        }
        HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
LABEL_46:
        HumanPlayer_SetWeaponTypeAnim(ptQTask, WEAPONTYPE_GETANIMTYPE_1STRELOADLOOP, 0, false);
        ptState->pfState = HumanPlayer_RunActionReloadLoop;
LABEL_81:
        Weapon_Reload(ptQTask[33].ptNext);
        HumanPlayer_SendHandleWeaponAIEvent(ptQTask, 20480.0);
        return;
      }
      v38 = *(_DWORD *)&ptQTask[32].eQTaskType;
      ptQTask[77].tQTaskRefList.ptTail = (struct QReference_s *)10;
      ptQTask[87].tQTaskChildren.ptMiddle = (struct QTask_s *)1;
      v39 = v38 == 2 ? 79 : 86;
      if ( v38 == 2 )
      {
        HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
        if ( v39 == 77 || v39 == 78 || v39 == 79 )
        {
          v57 = ptQTask[7].tQTaskRefList.ptTail;
          igi2_frame.nFireType.nRoundsPerClip = (int)ptQTask[77].ptPrev;
          v58 = ptQTask[33].ptNext;
          ptQTask[35].tQTaskChildren.ptTail = (struct QTask_s *)79;
          igi2_frame.nFireType.ptAmmoType = (struct AmmoType_s *)v57;
          igi2_frame.nFireType.nBulletsPerRound = 25;
          igi2_frame.nFireType.nAmmoInWeapon = (int)v58;
          igi2_frame.nFireType.nAmmoAvailable = 0;
          igi2_frame.ptAnim = nullptr;
          v59 = v58[1].ptPrev;
          if ( v59 )
            v60 = v59->tQTaskChildren.ptTail;
          else
            v60 = nullptr;
          v61 = v58[1].ptPrev;
          v62 = (void (__cdecl *)(struct QTask_s *, struct WeaponGetFireTypeAmmoContext_s *))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][v60->eQTaskType].pfHandler;
          if ( v61 )
            v63 = v61->tQTaskChildren.ptTail;
          else
            v63 = nullptr;
          v62(v63, &igi2_frame.nFireType);
          if ( !igi2_frame.ptAnim )
            goto LABEL_80;
          HumanAnim_SetAnimation(ptQTask, igi2_frame.ptAnim, 0, 0.0);
          v47 = &ptQTask[34].tQTaskChildren.ptTail->ptNext;
          v48 = (__int64)((double)AnimController_nTicksPerFrame * igi2_frame.v73);
          goto LABEL_79;
        }
        if ( v39 != 90 && v39 != 91 )
        {
          HumanAnim_SetAnimationAndTimeFromState(ptQTask, v39, 0, 0.0);
          goto LABEL_80;
        }
        v49 = ptQTask[77].ptPrev;
        v50 = ptQTask[7].tQTaskRefList.ptTail;
        igi2_frame.nFireType.nBulletsPerRound = igi2_frame.v70;
        v51 = ptQTask[33].ptNext;
        igi2_frame.nFireType.ptAmmoType = (struct AmmoType_s *)v50;
        igi2_frame.nFireType.nRoundsPerClip = (int)v49;
        igi2_frame.nFireType.nAmmoInWeapon = (int)v51;
        igi2_frame.nFireType.nAmmoAvailable = 0;
        igi2_frame.ptAnim = nullptr;
        v52 = v51[1].ptPrev;
        if ( v52 )
          v53 = v52->tQTaskChildren.ptTail;
        else
          v53 = nullptr;
        v54 = v51[1].ptPrev;
        v55 = (void (__cdecl *)(struct QTask_s *, struct WeaponGetFireTypeAmmoContext_s *))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][v53->eQTaskType].pfHandler;
        if ( v54 )
          v56 = v54->tQTaskChildren.ptTail;
        else
          v56 = nullptr;
        v55(v56, &igi2_frame.nFireType);
        if ( igi2_frame.ptAnim )
          goto LABEL_55;
      }
      else
      {
        v40 = ptQTask[77].ptPrev;
        igi2_frame.nFireType.ptAmmoType = (struct AmmoType_s *)ptQTask[7].tQTaskRefList.ptTail;
        v41 = ptQTask[33].ptNext;
        ptQTask[35].tQTaskRefList.ptHead = (struct QReference_s *)86;
        igi2_frame.nFireType.nBulletsPerRound = 22;
        igi2_frame.nFireType.nRoundsPerClip = (int)v40;
        igi2_frame.nFireType.nAmmoInWeapon = (int)v41;
        igi2_frame.nFireType.nAmmoAvailable = 0;
        igi2_frame.ptAnim = nullptr;
        v42 = v41[1].ptPrev;
        if ( v42 )
          v43 = v42->tQTaskChildren.ptTail;
        else
          v43 = nullptr;
        v44 = v41[1].ptPrev;
        v45 = (void (__cdecl *)(struct QTask_s *, struct WeaponGetFireTypeAmmoContext_s *))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][v43->eQTaskType].pfHandler;
        if ( v44 )
          v46 = v44->tQTaskChildren.ptTail;
        else
          v46 = nullptr;
        v45(v46, &igi2_frame.nFireType);
        if ( igi2_frame.ptAnim )
        {
LABEL_55:
          HumanAnim_SetUpperBodyAnimationFromHeader(ptQTask, igi2_frame.ptAnim, 0, 0.0);
          v47 = &ptQTask[34].tQTaskRefList.ptHead->ptNext;
          v48 = (__int64)((double)AnimController_nTicksPerFrame * igi2_frame.v73);
LABEL_79:
          v47[17] = v48;
          goto LABEL_80;
        }
      }
      HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
LABEL_80:
      HumanPlayer_SetWeaponTypeAnim(ptQTask, WEAPONTYPE_GETANIMTYPE_1STRELOADEND, 0, false);
      ptState->pfState = HumanPlayer_RunActionReloadEnd;
      goto LABEL_81;
    }
    Weapon_Reload(&ptNext->tQTask);
    HumanPlayer_SendHandleWeaponAIEvent(ptQTask, 20480.0);
    v64 = ptState->apfExitState[ptState->nState];
    if ( v64 )
      v64(ptState, ptQTask);
    v65 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 1;
    v66 = v65[1];
    ptState->pfState = v66;
    v66(ptState, ptQTask);
  }
  else
  {
    v67 = ptState->apfExitState[ptState->nState];
    if ( v67 )
      v67(ptState, ptQTask);
    v68 = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 1;
    v69 = v68[1];
    ptState->pfState = v69;
    v69(ptState, ptQTask);
  }
}

// source: j/0/human/humanplayer.c:14528  [anchor-mhash]
void __cdecl HumanPlayer_RunActionReloadLoop(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { unsigned int bSignal; };
    struct { char igi2_o1[12]; struct WeaponGetFireTypeAmmoContext_s nFireType; };
    struct { char igi2_o2[36]; struct AnimHeader_s *ptAnim; };
    struct { char igi2_o3[40]; float v112; };
    char igi2_extent[48];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct State_s *v2; // ebx
  int v3; // eax
  int v4; // eax
  int v5; // ebx
  struct QReference_s *v6; // ecx
  struct QTask_s *v7; // eax
  struct QTask_s *v8; // edx
  struct QTask_s *v9; // ecx
  struct QTask_s *v10; // ecx
  struct QTask_s *v11; // eax
  void (__cdecl *v12)(struct QTask_s *, struct WeaponGetFireTypeAmmoContext_s *); // ecx
  struct QTask_s *v13; // eax
  _DWORD *p_ptNext; // ecx
  int v15; // eax
  struct QTask_s *v16; // ecx
  struct QReference_s *v17; // edx
  struct QTask_s *v18; // eax
  struct QTask_s *v19; // ecx
  struct QTask_s *v20; // ecx
  struct QTask_s *v21; // eax
  void (__cdecl *v22)(struct QTask_s *, struct WeaponGetFireTypeAmmoContext_s *); // ecx
  struct QTask_s *v23; // eax
  struct QReference_s *ptTail; // edx
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptPrev; // ecx
  struct QTask_s *v27; // ecx
  struct QTask_s *v28; // eax
  void (__cdecl *pfHandler)(struct QTask_s *, struct WeaponGetFireTypeAmmoContext_s *); // ecx
  struct QTask_s *v30; // eax
  struct QTask_s *v31; // eax
  void (__cdecl *v32)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v34)(struct State_s *, struct QTask_s *); // eax
  int v35; // eax
  int v36; // ebx
  struct QTask_s *v37; // ecx
  struct QTask_s *v38; // eax
  struct QTask_s *v39; // ecx
  struct QTask_s *v40; // ecx
  struct QTask_s *v41; // eax
  void (__cdecl *v42)(struct QTask_s *, struct WeaponGetFireTypeAmmoContext_s *); // ecx
  struct QTask_s *v43; // eax
  struct QTask_s *v44; // ecx
  struct QReference_s *v45; // edx
  struct QTask_s *v46; // eax
  struct QTask_s *v47; // ecx
  struct QTask_s *v48; // ecx
  struct QTask_s *v49; // eax
  void (__cdecl *v50)(struct QTask_s *, struct WeaponGetFireTypeAmmoContext_s *); // ecx
  struct QTask_s *v51; // eax
  struct QReference_s *v52; // edx
  struct QTask_s *v53; // eax
  struct QTask_s *v54; // ecx
  struct QTask_s *v55; // ecx
  struct QTask_s *v56; // eax
  void (__cdecl *v57)(struct QTask_s *, struct WeaponGetFireTypeAmmoContext_s *); // ecx
  struct QTask_s *v58; // eax
  struct AnimHeader_s *v59; // eax
  int v60; // eax
  int v61; // ebx
  struct QReference_s *v62; // edx
  struct QTask_s *v63; // eax
  struct QTask_s *v64; // ecx
  struct QTask_s *v65; // ecx
  struct QTask_s *v66; // eax
  void (__cdecl *v67)(struct QTask_s *, struct WeaponGetFireTypeAmmoContext_s *); // ecx
  struct QTask_s *v68; // eax
  struct QTask_s *v69; // ecx
  struct QReference_s *v70; // edx
  struct QTask_s *v71; // eax
  struct QTask_s *v72; // ecx
  struct QTask_s *v73; // ecx
  struct QTask_s *v74; // eax
  void (__cdecl *v75)(struct QTask_s *, struct WeaponGetFireTypeAmmoContext_s *); // ecx
  struct QTask_s *v76; // eax
  struct QReference_s *v77; // edx
  struct QTask_s *v78; // eax
  struct QTask_s *v79; // ecx
  struct QTask_s *v80; // ecx
  struct QTask_s *v81; // eax
  void (__cdecl *v82)(struct QTask_s *, struct WeaponGetFireTypeAmmoContext_s *); // ecx
  struct QTask_s *v83; // eax
  int v84; // eax
  struct QReference_s *v85; // edx
  struct QTask_s *v86; // eax
  struct QTask_s *v87; // ecx
  struct QTask_s *v88; // ecx
  struct QTask_s *v89; // eax
  void (__cdecl *v90)(struct QTask_s *, struct WeaponGetFireTypeAmmoContext_s *); // ecx
  struct QTask_s *v91; // eax
  struct QTask_s *v92; // ecx
  struct QReference_s *v93; // edx
  struct QTask_s *v94; // eax
  struct QTask_s *v95; // ecx
  struct QTask_s *v96; // ecx
  struct QTask_s *v97; // eax
  void (__cdecl *v98)(struct QTask_s *, struct WeaponGetFireTypeAmmoContext_s *); // ecx
  struct QTask_s *v99; // eax
  _DWORD *v100; // ecx
  int v101; // eax
  struct QReference_s *v102; // edx
  struct QTask_s *v103; // eax
  struct QTask_s *v104; // ecx
  struct QTask_s *v105; // ecx
  struct QTask_s *v106; // eax
  void (__cdecl *v107)(struct QTask_s *, struct WeaponGetFireTypeAmmoContext_s *); // ecx
  struct QTask_s *v108; // eax

  v2 = ptState;
  igi2_frame.bSignal = ptState->bSignal;
  v3 = *(_DWORD *)&ptQTask[30].eQTaskType;
  ptQTask[83].ptParent = nullptr;
  if ( (v3 & 0x20000) != 0 )
  {
    v4 = *(_DWORD *)&ptQTask[32].eQTaskType;
    ptQTask[77].tQTaskRefList.ptTail = (struct QReference_s *)10;
    ptQTask[87].tQTaskChildren.ptMiddle = (struct QTask_s *)1;
    v5 = v4 == 2 ? 79 : 86;
    if ( v4 == 2 )
    {
      HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
      if ( v5 == 77 || v5 == 78 || v5 == 79 )
      {
        ptTail = ptQTask[7].tQTaskRefList.ptTail;
        igi2_frame.nFireType.nRoundsPerClip = (int)ptQTask[77].ptPrev;
        ptNext = ptQTask[33].ptNext;
        ptQTask[35].tQTaskChildren.ptTail = (struct QTask_s *)79;
        igi2_frame.nFireType.ptAmmoType = (struct AmmoType_s *)ptTail;
        igi2_frame.nFireType.nBulletsPerRound = 25;
        igi2_frame.nFireType.nAmmoInWeapon = (int)ptNext;
        igi2_frame.nFireType.nAmmoAvailable = 0;
        igi2_frame.ptAnim = nullptr;
        ptPrev = ptNext[1].ptPrev;
        if ( ptPrev )
          v27 = ptPrev->tQTaskChildren.ptTail;
        else
          v27 = nullptr;
        v28 = ptNext[1].ptPrev;
        pfHandler = (void (__cdecl *)(struct QTask_s *, struct WeaponGetFireTypeAmmoContext_s *))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][v27->eQTaskType].pfHandler;
        if ( v28 )
          v30 = v28->tQTaskChildren.ptTail;
        else
          v30 = nullptr;
        pfHandler(v30, &igi2_frame.nFireType);
        if ( !igi2_frame.ptAnim )
          goto LABEL_35;
        HumanAnim_SetAnimation(ptQTask, igi2_frame.ptAnim, 0, 0.0);
        p_ptNext = &ptQTask[34].tQTaskChildren.ptTail->ptNext;
        v15 = (__int64)((double)AnimController_nTicksPerFrame * igi2_frame.v112);
        goto LABEL_34;
      }
      if ( v5 != 90 && v5 != 91 )
      {
        HumanAnim_SetAnimationAndTimeFromState(ptQTask, v5, 0, 0.0);
        goto LABEL_35;
      }
      v16 = ptQTask[77].ptPrev;
      v17 = ptQTask[7].tQTaskRefList.ptTail;
      igi2_frame.nFireType.nBulletsPerRound = (int)ptState;
      v18 = ptQTask[33].ptNext;
      igi2_frame.nFireType.ptAmmoType = (struct AmmoType_s *)v17;
      igi2_frame.nFireType.nRoundsPerClip = (int)v16;
      igi2_frame.nFireType.nAmmoInWeapon = (int)v18;
      igi2_frame.nFireType.nAmmoAvailable = 0;
      igi2_frame.ptAnim = nullptr;
      v19 = v18[1].ptPrev;
      if ( v19 )
        v20 = v19->tQTaskChildren.ptTail;
      else
        v20 = nullptr;
      v21 = v18[1].ptPrev;
      v22 = (void (__cdecl *)(struct QTask_s *, struct WeaponGetFireTypeAmmoContext_s *))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][v20->eQTaskType].pfHandler;
      if ( v21 )
        v23 = v21->tQTaskChildren.ptTail;
      else
        v23 = nullptr;
      v22(v23, &igi2_frame.nFireType);
      if ( igi2_frame.ptAnim )
        goto LABEL_10;
    }
    else
    {
      v6 = ptQTask[7].tQTaskRefList.ptTail;
      v7 = ptQTask[33].ptNext;
      v8 = ptQTask[77].ptPrev;
      ptQTask[35].tQTaskRefList.ptHead = (struct QReference_s *)86;
      igi2_frame.nFireType.ptAmmoType = (struct AmmoType_s *)v6;
      igi2_frame.nFireType.nBulletsPerRound = 22;
      igi2_frame.nFireType.nRoundsPerClip = (int)v8;
      igi2_frame.nFireType.nAmmoInWeapon = (int)v7;
      igi2_frame.nFireType.nAmmoAvailable = 0;
      igi2_frame.ptAnim = nullptr;
      v9 = v7[1].ptPrev;
      if ( v9 )
        v10 = v9->tQTaskChildren.ptTail;
      else
        v10 = nullptr;
      v11 = v7[1].ptPrev;
      v12 = (void (__cdecl *)(struct QTask_s *, struct WeaponGetFireTypeAmmoContext_s *))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][v10->eQTaskType].pfHandler;
      if ( v11 )
        v13 = v11->tQTaskChildren.ptTail;
      else
        v13 = nullptr;
      v12(v13, &igi2_frame.nFireType);
      if ( igi2_frame.ptAnim )
      {
LABEL_10:
        HumanAnim_SetUpperBodyAnimationFromHeader(ptQTask, igi2_frame.ptAnim, 0, 0.0);
        p_ptNext = &ptQTask[34].tQTaskRefList.ptHead->ptNext;
        v15 = (__int64)((double)AnimController_nTicksPerFrame * igi2_frame.v112);
LABEL_34:
        p_ptNext[17] = v15;
        goto LABEL_35;
      }
    }
    HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
LABEL_35:
    HumanPlayer_SetWeaponTypeAnim(ptQTask, WEAPONTYPE_GETANIMTYPE_1STRELOADEND, 0, false);
    ptState->pfState = HumanPlayer_RunActionReloadEnd;
    v2 = ptState;
  }
  if ( ptQTask[76].ptParent == (struct QTask_s *)-1 )
  {
    if ( (igi2_frame.bSignal & 1) == 0 )
      return;
    Weapon_GetFireTypeAmmoInfoFromWeaponTypeItem(
      (struct Weapon_s *)ptQTask[33].ptNext,
      (struct WeaponTypeItem_s *)ptQTask[33].ptNext[1].ptPrev,
      0,
      &igi2_frame.nFireType);
    if ( (igi2_frame.bSignal & 0x200) != 0 )
    {
      v35 = *(_DWORD *)&ptQTask[32].eQTaskType;
      ptQTask[77].tQTaskRefList.ptTail = (struct QReference_s *)10;
      ptQTask[87].tQTaskChildren.ptMiddle = (struct QTask_s *)1;
      v36 = v35 == 2 ? 79 : 86;
      if ( v35 != 2 )
      {
        v37 = ptQTask[77].ptPrev;
        igi2_frame.nFireType.ptAmmoType = (struct AmmoType_s *)ptQTask[7].tQTaskRefList.ptTail;
        v38 = ptQTask[33].ptNext;
        ptQTask[35].tQTaskRefList.ptHead = (struct QReference_s *)86;
        igi2_frame.nFireType.nBulletsPerRound = 22;
        igi2_frame.nFireType.nRoundsPerClip = (int)v37;
        igi2_frame.nFireType.nAmmoInWeapon = (int)v38;
        igi2_frame.nFireType.nAmmoAvailable = 0;
        igi2_frame.ptAnim = nullptr;
        v39 = v38[1].ptPrev;
        if ( v39 )
          v40 = v39->tQTaskChildren.ptTail;
        else
          v40 = nullptr;
        v41 = v38[1].ptPrev;
        v42 = (void (__cdecl *)(struct QTask_s *, struct WeaponGetFireTypeAmmoContext_s *))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][v40->eQTaskType].pfHandler;
        if ( v41 )
          v43 = v41->tQTaskChildren.ptTail;
        else
          v43 = nullptr;
        v42(v43, &igi2_frame.nFireType);
        if ( !igi2_frame.ptAnim )
        {
LABEL_50:
          HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
LABEL_139:
          HumanPlayer_SetWeaponTypeAnim(ptQTask, WEAPONTYPE_GETANIMTYPE_1STRELOADEND, 0, false);
          ptState->pfState = HumanPlayer_RunActionReloadEnd;
          goto LABEL_140;
        }
        goto LABEL_129;
      }
      HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
      if ( v36 != 77 && v36 != 78 && v36 != 79 )
      {
        if ( v36 != 90 && v36 != 91 )
        {
LABEL_56:
          HumanAnim_SetAnimationAndTimeFromState(ptQTask, v36, 0, 0.0);
          goto LABEL_139;
        }
        v44 = ptQTask[77].ptPrev;
        v45 = ptQTask[7].tQTaskRefList.ptTail;
        igi2_frame.nFireType.nBulletsPerRound = (int)ptState;
        v46 = ptQTask[33].ptNext;
        igi2_frame.nFireType.ptAmmoType = (struct AmmoType_s *)v45;
        igi2_frame.nFireType.nRoundsPerClip = (int)v44;
        igi2_frame.nFireType.nAmmoInWeapon = (int)v46;
        igi2_frame.nFireType.nAmmoAvailable = 0;
        igi2_frame.ptAnim = nullptr;
        v47 = v46[1].ptPrev;
        if ( v47 )
          v48 = v47->tQTaskChildren.ptTail;
        else
          v48 = nullptr;
        v49 = v46[1].ptPrev;
        v50 = (void (__cdecl *)(struct QTask_s *, struct WeaponGetFireTypeAmmoContext_s *))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][v48->eQTaskType].pfHandler;
        if ( v49 )
          v51 = v49->tQTaskChildren.ptTail;
        else
          v51 = nullptr;
        v50(v51, &igi2_frame.nFireType);
        if ( !igi2_frame.ptAnim )
          goto LABEL_50;
LABEL_129:
        HumanAnim_SetUpperBodyAnimationFromHeader(ptQTask, igi2_frame.ptAnim, 0, 0.0);
        v100 = &ptQTask[34].tQTaskRefList.ptHead->ptNext;
        v101 = (__int64)((double)AnimController_nTicksPerFrame * igi2_frame.v112);
LABEL_138:
        v100[17] = v101;
        goto LABEL_139;
      }
      v52 = ptQTask[7].tQTaskRefList.ptTail;
      igi2_frame.nFireType.nRoundsPerClip = (int)ptQTask[77].ptPrev;
      v53 = ptQTask[33].ptNext;
      ptQTask[35].tQTaskChildren.ptTail = (struct QTask_s *)79;
      igi2_frame.nFireType.ptAmmoType = (struct AmmoType_s *)v52;
      igi2_frame.nFireType.nBulletsPerRound = 25;
      igi2_frame.nFireType.nAmmoInWeapon = (int)v53;
      igi2_frame.nFireType.nAmmoAvailable = 0;
      igi2_frame.ptAnim = nullptr;
      v54 = v53[1].ptPrev;
      if ( v54 )
        v55 = v54->tQTaskChildren.ptTail;
      else
        v55 = nullptr;
      v56 = v53[1].ptPrev;
      v57 = (void (__cdecl *)(struct QTask_s *, struct WeaponGetFireTypeAmmoContext_s *))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][v55->eQTaskType].pfHandler;
      if ( v56 )
        v58 = v56->tQTaskChildren.ptTail;
      else
        v58 = nullptr;
      v57(v58, &igi2_frame.nFireType);
      v59 = igi2_frame.ptAnim;
      if ( !igi2_frame.ptAnim )
        goto LABEL_139;
      goto LABEL_137;
    }
    if ( igi2_frame.nFireType.nAmmoAvailable <= 1 || igi2_frame.nFireType.nAmmoInWeapon == igi2_frame.nFireType.nRoundsPerClip - 1 )
    {
      ptQTask[87].tQTaskChildren.ptMiddle = (struct QTask_s *)1;
      v84 = *(_DWORD *)&ptQTask[32].eQTaskType;
      ptQTask[77].tQTaskRefList.ptTail = (struct QReference_s *)10;
      v36 = v84 == 2 ? 79 : 86;
      if ( v84 != 2 )
      {
        v85 = ptQTask[7].tQTaskRefList.ptTail;
        igi2_frame.nFireType.nRoundsPerClip = (int)ptQTask[77].ptPrev;
        v86 = ptQTask[33].ptNext;
        ptQTask[35].tQTaskRefList.ptHead = (struct QReference_s *)86;
        igi2_frame.nFireType.ptAmmoType = (struct AmmoType_s *)v85;
        igi2_frame.nFireType.nBulletsPerRound = 22;
        igi2_frame.nFireType.nAmmoInWeapon = (int)v86;
        igi2_frame.nFireType.nAmmoAvailable = 0;
        igi2_frame.ptAnim = nullptr;
        v87 = v86[1].ptPrev;
        if ( v87 )
          v88 = v87->tQTaskChildren.ptTail;
        else
          v88 = nullptr;
        v89 = v86[1].ptPrev;
        v90 = (void (__cdecl *)(struct QTask_s *, struct WeaponGetFireTypeAmmoContext_s *))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][v88->eQTaskType].pfHandler;
        if ( v89 )
          v91 = v89->tQTaskChildren.ptTail;
        else
          v91 = nullptr;
        v90(v91, &igi2_frame.nFireType);
        if ( !igi2_frame.ptAnim )
          goto LABEL_50;
        goto LABEL_129;
      }
      HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
      if ( v36 != 77 && v36 != 78 && v36 != 79 )
      {
        if ( v36 != 90 && v36 != 91 )
          goto LABEL_56;
        v92 = ptQTask[77].ptPrev;
        v93 = ptQTask[7].tQTaskRefList.ptTail;
        igi2_frame.nFireType.nBulletsPerRound = (int)ptState;
        v94 = ptQTask[33].ptNext;
        igi2_frame.nFireType.ptAmmoType = (struct AmmoType_s *)v93;
        igi2_frame.nFireType.nRoundsPerClip = (int)v92;
        igi2_frame.nFireType.nAmmoInWeapon = (int)v94;
        igi2_frame.nFireType.nAmmoAvailable = 0;
        igi2_frame.ptAnim = nullptr;
        v95 = v94[1].ptPrev;
        if ( v95 )
          v96 = v95->tQTaskChildren.ptTail;
        else
          v96 = nullptr;
        v97 = v94[1].ptPrev;
        v98 = (void (__cdecl *)(struct QTask_s *, struct WeaponGetFireTypeAmmoContext_s *))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][v96->eQTaskType].pfHandler;
        if ( v97 )
          v99 = v97->tQTaskChildren.ptTail;
        else
          v99 = nullptr;
        v98(v99, &igi2_frame.nFireType);
        if ( !igi2_frame.ptAnim )
          goto LABEL_50;
        goto LABEL_129;
      }
      v102 = ptQTask[7].tQTaskRefList.ptTail;
      igi2_frame.nFireType.nRoundsPerClip = (int)ptQTask[77].ptPrev;
      v103 = ptQTask[33].ptNext;
      ptQTask[35].tQTaskChildren.ptTail = (struct QTask_s *)79;
      igi2_frame.nFireType.ptAmmoType = (struct AmmoType_s *)v102;
      igi2_frame.nFireType.nBulletsPerRound = 25;
      igi2_frame.nFireType.nAmmoInWeapon = (int)v103;
      igi2_frame.nFireType.nAmmoAvailable = 0;
      igi2_frame.ptAnim = nullptr;
      v104 = v103[1].ptPrev;
      if ( v104 )
        v105 = v104->tQTaskChildren.ptTail;
      else
        v105 = nullptr;
      v106 = v103[1].ptPrev;
      v107 = (void (__cdecl *)(struct QTask_s *, struct WeaponGetFireTypeAmmoContext_s *))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][v105->eQTaskType].pfHandler;
      if ( v106 )
        v108 = v106->tQTaskChildren.ptTail;
      else
        v108 = nullptr;
      v107(v108, &igi2_frame.nFireType);
      v59 = igi2_frame.ptAnim;
      if ( !igi2_frame.ptAnim )
        goto LABEL_139;
LABEL_137:
      HumanAnim_SetAnimation(ptQTask, v59, 0, 0.0);
      v101 = (__int64)((double)AnimController_nTicksPerFrame * igi2_frame.v112);
      v100 = &ptQTask[34].tQTaskChildren.ptTail->ptNext;
      goto LABEL_138;
    }
    ptQTask[87].tQTaskChildren.ptMiddle = (struct QTask_s *)1;
    v60 = *(_DWORD *)&ptQTask[32].eQTaskType;
    ptQTask[77].tQTaskRefList.ptTail = (struct QReference_s *)9;
    v61 = v60 == 2 ? 78 : 85;
    if ( v60 == 2 )
    {
      HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
      if ( v61 == 77 || v61 == 78 || v61 == 79 )
      {
        v77 = ptQTask[7].tQTaskRefList.ptTail;
        igi2_frame.nFireType.nRoundsPerClip = (int)ptQTask[77].ptPrev;
        v78 = ptQTask[33].ptNext;
        ptQTask[35].tQTaskChildren.ptTail = (struct QTask_s *)78;
        igi2_frame.nFireType.ptAmmoType = (struct AmmoType_s *)v77;
        igi2_frame.nFireType.nBulletsPerRound = 24;
        igi2_frame.nFireType.nAmmoInWeapon = (int)v78;
        igi2_frame.nFireType.nAmmoAvailable = 0;
        igi2_frame.ptAnim = nullptr;
        v79 = v78[1].ptPrev;
        if ( v79 )
          v80 = v79->tQTaskChildren.ptTail;
        else
          v80 = nullptr;
        v81 = v78[1].ptPrev;
        v82 = (void (__cdecl *)(struct QTask_s *, struct WeaponGetFireTypeAmmoContext_s *))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][v80->eQTaskType].pfHandler;
        if ( v81 )
          v83 = v81->tQTaskChildren.ptTail;
        else
          v83 = nullptr;
        v82(v83, &igi2_frame.nFireType);
        if ( igi2_frame.ptAnim )
        {
          HumanAnim_SetAnimation(ptQTask, igi2_frame.ptAnim, 0, 0.0);
          ptQTask[34].tQTaskChildren.ptTail[1].tQTaskRefList.ptTail = (struct QReference_s *)(__int64)((double)AnimController_nTicksPerFrame * igi2_frame.v112);
        }
        HumanPlayer_SetWeaponTypeAnim(ptQTask, WEAPONTYPE_GETANIMTYPE_1STRELOADLOOP, 0, false);
        goto LABEL_140;
      }
      if ( v61 != 90 && v61 != 91 )
      {
        HumanAnim_SetAnimationAndTimeFromState(ptQTask, v61, 0, 0.0);
        HumanPlayer_SetWeaponTypeAnim(ptQTask, WEAPONTYPE_GETANIMTYPE_1STRELOADLOOP, 0, false);
        goto LABEL_140;
      }
      v69 = ptQTask[77].ptPrev;
      v70 = ptQTask[7].tQTaskRefList.ptTail;
      igi2_frame.nFireType.nBulletsPerRound = (int)ptState;
      v71 = ptQTask[33].ptNext;
      igi2_frame.nFireType.ptAmmoType = (struct AmmoType_s *)v70;
      igi2_frame.nFireType.nRoundsPerClip = (int)v69;
      igi2_frame.nFireType.nAmmoInWeapon = (int)v71;
      igi2_frame.nFireType.nAmmoAvailable = 0;
      igi2_frame.ptAnim = nullptr;
      v72 = v71[1].ptPrev;
      if ( v72 )
        v73 = v72->tQTaskChildren.ptTail;
      else
        v73 = nullptr;
      v74 = v71[1].ptPrev;
      v75 = (void (__cdecl *)(struct QTask_s *, struct WeaponGetFireTypeAmmoContext_s *))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][v73->eQTaskType].pfHandler;
      if ( v74 )
        v76 = v74->tQTaskChildren.ptTail;
      else
        v76 = nullptr;
      v75(v76, &igi2_frame.nFireType);
      if ( igi2_frame.ptAnim )
        goto LABEL_83;
    }
    else
    {
      v62 = ptQTask[7].tQTaskRefList.ptTail;
      igi2_frame.nFireType.nRoundsPerClip = (int)ptQTask[77].ptPrev;
      v63 = ptQTask[33].ptNext;
      ptQTask[35].tQTaskRefList.ptHead = (struct QReference_s *)85;
      igi2_frame.nFireType.ptAmmoType = (struct AmmoType_s *)v62;
      igi2_frame.nFireType.nBulletsPerRound = 21;
      igi2_frame.nFireType.nAmmoInWeapon = (int)v63;
      igi2_frame.nFireType.nAmmoAvailable = 0;
      igi2_frame.ptAnim = nullptr;
      v64 = v63[1].ptPrev;
      if ( v64 )
        v65 = v64->tQTaskChildren.ptTail;
      else
        v65 = nullptr;
      v66 = v63[1].ptPrev;
      v67 = (void (__cdecl *)(struct QTask_s *, struct WeaponGetFireTypeAmmoContext_s *))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][v65->eQTaskType].pfHandler;
      if ( v66 )
        v68 = v66->tQTaskChildren.ptTail;
      else
        v68 = nullptr;
      v67(v68, &igi2_frame.nFireType);
      if ( igi2_frame.ptAnim )
      {
LABEL_83:
        HumanAnim_SetUpperBodyAnimationFromHeader(ptQTask, igi2_frame.ptAnim, 0, 0.0);
        ptQTask[34].tQTaskRefList.ptHead[5].pxObject = (void *)(__int64)((double)AnimController_nTicksPerFrame * igi2_frame.v112);
        HumanPlayer_SetWeaponTypeAnim(ptQTask, WEAPONTYPE_GETANIMTYPE_1STRELOADLOOP, 0, false);
LABEL_140:
        Weapon_SendWeaponEvent(ptQTask[33].ptNext, 0x5753524Cu, &igi2_frame.nFireType, 20);
        HumanPlayer_SendHandleWeaponAIEvent(ptQTask, 20480.0);
        return;
      }
    }
    HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
    HumanPlayer_SetWeaponTypeAnim(ptQTask, WEAPONTYPE_GETANIMTYPE_1STRELOADLOOP, 0, false);
    goto LABEL_140;
  }
  v31 = ptQTask[33].tQTaskChildren.ptTail;
  v31[16].tQTaskRefList.ptMiddle = nullptr;
  *(float *)&v31[16].tQTaskChildren.ptHead = tan(0.7853981852531433);
  *(float *)&v31[16].tQTaskRefList.ptHead = tan(0.5235987901687622);
  v32 = v2->apfExitState[v2->nState];
  if ( v32 )
    v32(v2, ptQTask);
  apfState = v2->apfState;
  v2->nPreviousState = v2->nState;
  v2->nState = 6;
  v34 = apfState[6];
  v2->pfState = v34;
  v34(v2, ptQTask);
}

// source: j/0/human/humanplayer.c:14586  [anchor-mhash]
void __cdecl HumanPlayer_RunActionReloadEnd(struct State_s *ptState, struct QTask_s *ptQTask)
{
  unsigned int bSignal; // eax
  void (__cdecl *v3)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v5)(struct State_s *, struct QTask_s *); // eax

  bSignal = ptState->bSignal;
  ptQTask[83].ptParent = nullptr;
  if ( (bSignal & 1) != 0 )
  {
    v3 = ptState->apfExitState[ptState->nState];
    if ( v3 )
      v3(ptState, ptQTask);
    apfState = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 1;
    v5 = apfState[1];
    ptState->pfState = v5;
    v5(ptState, ptQTask);
  }
}

// source: j/0/human/humanplayer.c:14612  [anchor-mhash]
void __cdecl HumanPlayer_InitActionChangeWeapon(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QReference_s *v23; };
    struct { char igi2_o1[4]; struct QTask_s *v24; };
    struct { char igi2_o2[8]; int v25; };
    struct { char igi2_o3[12]; int v26; };
    struct { char igi2_o4[16]; struct QTask_s *v27; };
    struct { char igi2_o5[24]; struct AnimHeader_s *ptAnim; };
    struct { char igi2_o6[28]; float v29; };
    struct { char igi2_o7[32]; char azChangeSound[4][32]; };
    char igi2_extent[160];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Game_s *v2; // eax
  unsigned int v3; // edx
  unsigned int v4; // edi
  unsigned int v5; // esi
  struct QTask_s *ptPrev; // ecx
  int v7; // eax
  int v8; // edi
  struct QReference_s *v9; // edx
  struct QTask_s *v10; // eax
  struct QTask_s *v11; // ecx
  struct QTask_s *v12; // ecx
  struct QTask_s *v13; // eax
  void (__cdecl *v14)(struct QTask_s *, struct QReference_s **); // ecx
  struct QTask_s *v15; // eax
  struct QReference_s *ptTail; // edx
  struct QTask_s *ptNext; // eax
  struct QTask_s *v18; // ecx
  struct QTask_s *v19; // ecx
  struct QTask_s *v20; // eax
  void (__cdecl *pfHandler)(struct QTask_s *, struct QReference_s **); // ecx
  struct QTask_s *v22; // eax

  strcpy(igi2_frame.azChangeSound[0], "changeweapon_01");
  *(_QWORD *)&igi2_frame.azChangeSound[0][20] = 0;
  *(_DWORD *)&igi2_frame.azChangeSound[0][16] = 0;
  *(_DWORD *)&igi2_frame.azChangeSound[0][28] = 0;
  strcpy(igi2_frame.azChangeSound[1], "changeweapon_02");
  strcpy(igi2_frame.azChangeSound[2], "changeweapon_03");
  *(_QWORD *)&igi2_frame.azChangeSound[1][16] = 0;
  *(_QWORD *)&igi2_frame.azChangeSound[1][24] = 0;
  *(_QWORD *)&igi2_frame.azChangeSound[2][16] = 0;
  *(_QWORD *)&igi2_frame.azChangeSound[2][24] = 0;
  strcpy(igi2_frame.azChangeSound[3], "changeweapon_04");
  *(_QWORD *)&igi2_frame.azChangeSound[3][20] = 0;
  *(_DWORD *)&igi2_frame.azChangeSound[3][16] = 0;
  v2 = Game_ptGame;
  *(_DWORD *)&igi2_frame.azChangeSound[3][28] = 0;
  v3 = Game_ptGame->tRunRandomState.anRandom[0] >> 7;
  v4 = v3 ^ Game_ptGame->tRunRandomState.anRandom[2] ^ Game_ptGame->tRunRandomState.anRandom[1];
  v5 = v4 + Game_ptGame->tRunRandomState.anRandom[0];
  Game_ptGame->tRunRandomState.anRandom[2] ^= v3;
  v2->tRunRandomState.anRandom[0] = v5;
  v2->tRunRandomState.anRandom[1] = v4;
  ptPrev = ptQTask[33].ptNext[1].ptPrev;
  if ( ptPrev && LOBYTE(ptPrev->tQTaskRefList.ptTail) )
  {
    SoundSys_NewSoundFn(ptQTask[33].tQTaskChildren.ptTail, igi2_frame.azChangeSound[v5 & 3]);
    v7 = *(_DWORD *)&ptQTask[32].eQTaskType;
    ptQTask[77].tQTaskRefList.ptTail = (struct QReference_s *)11;
    ptQTask[87].tQTaskChildren.ptMiddle = (struct QTask_s *)1;
    v8 = v7 == 2 ? 91 : 88;
    if ( v7 == 2 )
    {
      HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
      if ( v8 != 91 )
      {
        HumanAnim_SetAnimationAndTimeFromState(ptQTask, v8, 0, 0.0);
        goto LABEL_23;
      }
      ptTail = ptQTask[7].tQTaskRefList.ptTail;
      igi2_frame.v27 = ptQTask[77].ptPrev;
      ptNext = ptQTask[33].ptNext;
      ptQTask[35].tQTaskRefList.ptHead = (struct QReference_s *)91;
      igi2_frame.v23 = ptTail;
      igi2_frame.v26 = 27;
      igi2_frame.v24 = ptNext;
      igi2_frame.v25 = 0;
      igi2_frame.ptAnim = nullptr;
      v18 = ptNext[1].ptPrev;
      if ( v18 )
        v19 = v18->tQTaskChildren.ptTail;
      else
        v19 = nullptr;
      v20 = ptNext[1].ptPrev;
      pfHandler = (void (__cdecl *)(struct QTask_s *, struct QReference_s **))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][v19->eQTaskType].pfHandler;
      if ( v20 )
        v22 = v20->tQTaskChildren.ptTail;
      else
        v22 = nullptr;
      pfHandler(v22, &igi2_frame.v23);
      if ( igi2_frame.ptAnim )
        goto LABEL_11;
    }
    else
    {
      v9 = ptQTask[7].tQTaskRefList.ptTail;
      igi2_frame.v27 = ptQTask[77].ptPrev;
      v10 = ptQTask[33].ptNext;
      ptQTask[35].tQTaskRefList.ptHead = (struct QReference_s *)88;
      igi2_frame.v23 = v9;
      igi2_frame.v26 = 16;
      igi2_frame.v24 = v10;
      igi2_frame.v25 = 0;
      igi2_frame.ptAnim = nullptr;
      v11 = v10[1].ptPrev;
      if ( v11 )
        v12 = v11->tQTaskChildren.ptTail;
      else
        v12 = nullptr;
      v13 = v10[1].ptPrev;
      v14 = (void (__cdecl *)(struct QTask_s *, struct QReference_s **))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][v12->eQTaskType].pfHandler;
      if ( v13 )
        v15 = v13->tQTaskChildren.ptTail;
      else
        v15 = nullptr;
      v14(v15, &igi2_frame.v23);
      if ( igi2_frame.ptAnim )
      {
LABEL_11:
        HumanAnim_SetUpperBodyAnimationFromHeader(ptQTask, igi2_frame.ptAnim, 0, 0.0);
        ptQTask[34].tQTaskRefList.ptHead[5].pxObject = (void *)(__int64)((double)AnimController_nTicksPerFrame * igi2_frame.v29);
LABEL_23:
        HumanPlayer_SetWeaponTypeAnim(ptQTask, WEAPONTYPE_GETANIMTYPE_1STACTIVATE, 0, false);
        goto LABEL_24;
      }
    }
    HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
    goto LABEL_23;
  }
LABEL_24:
  LOBYTE(ptQTask[33].tQTaskChildren.ptHead) = 0;
  ptQTask[80].tQTaskRefList.ptTail = nullptr;
  HumanPlayer_SendHandleWeaponAIEvent(ptQTask, 20480.0);
  ptState->pfState = HumanPlayer_RunActionChangeWeapon;
}

// source: j/0/human/humanplayer.c:14649  [anchor-caller]
void __cdecl HumanPlayer_RunActionChangeWeapon(struct State_s *ptState, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float pvBeta; };
    struct { char igi2_o1[4]; float pvAlpha; };
    struct { char igi2_o2[8]; struct real32x9_t ptSource; };
    struct { char igi2_o3[48]; struct real32x9_t ptPos; };
    struct { char igi2_o4[96]; int v45; };
    struct { char igi2_o5[116]; struct QTask_s *v46; };
    char igi2_extent[124];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptPrev; // eax
  struct WeaponType_s *WeaponTypeFromID; // edi
  bool v4; // zf
  double RandomNumberReal32; // st7
  struct WeaponType_s *ptParent; // ebx
  struct QTask_s *QTaskFromID; // eax
  struct QTask_s *v8; // esi
  int Timer; // eax
  float v10; // edx
  struct QTask_s *ptNext; // eax
  struct WeaponType_s *v12; // eax
  struct WeaponType_s *NextEnabledWeaponTypeFromCategory; // esi
  int v14; // eax
  struct QTask_s *ptMiddle; // ecx
  int eID; // eax
  struct QTask_s *ptHead; // eax
  int eQTaskType; // eax
  struct QTask_s *v19; // edi
  struct QReference_s *ptTail; // eax
  struct QTask_s *v21; // esi
  struct QTask_s *v22; // eax
  struct QTask_s *v23; // eax
  struct WeaponTypeItem_s *WeaponTypeItemFromWeaponType; // eax
  int v25; // eax
  int v26; // esi
  struct QReference_s *v27; // edx
  struct QTask_s *v28; // eax
  struct QTask_s *v29; // ecx
  struct QTask_s *v30; // ecx
  struct QTask_s *v31; // eax
  void (__cdecl *v32)(struct QTask_s *, float *); // ecx
  struct QTask_s *v33; // eax
  struct QReference_s *v34; // edx
  struct QTask_s *v35; // eax
  struct QTask_s *v36; // ecx
  struct QTask_s *v37; // ecx
  struct QTask_s *v38; // eax
  void (__cdecl *pfHandler)(struct QTask_s *, float *); // ecx
  struct QTask_s *v40; // eax

  ptPrev = ptQTask[33].ptNext[1].ptPrev;
  if ( (ptState->bSignal & 1) != 0 || ptPrev && !LOBYTE(ptPrev->tQTaskRefList.ptTail) )
  {
    WeaponTypeFromID = WeaponType_GetWeaponTypeFromID((int)ptQTask[76].ptParent);
    if ( WeaponTypeFromID && ptQTask[33].ptNext && !ptQTask[80].tQTaskRefList.ptTail )
    {
      v4 = ptQTask[87].tQTaskRefList.ptHead == nullptr;
      ptQTask[80].tQTaskRefList.ptTail = (struct QReference_s *)1;
      if ( !v4 )
      {
        if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
        {
          NetManager_RequestDropWeapon();
        }
        else
        {
          HumanAnim_GetWeaponPositionAndOrientation(ptQTask, (struct real64x3_t *)&igi2_frame.ptSource.tX.vZ, &igi2_frame.ptPos);
          sub_580CA0((int)ptQTask, (double *)&igi2_frame.ptSource.tX.vZ);
          *(double *)&igi2_frame.ptSource.tZ.vX = *(double *)&igi2_frame.ptSource.tZ.vX + 1228.800048828125;
          Real32x9_GetAngles((struct real32x9_t *)&ptQTask[3].ptPrev, &igi2_frame.ptSource.tX.vX, &igi2_frame.pvAlpha, &igi2_frame.pvBeta);
          RandomNumberReal32 = Random_GetRandomNumberReal32(&Game_ptGame->tRunRandomState);
          ptParent = (struct WeaponType_s *)ptQTask[86].ptParent;
          igi2_frame.pvBeta = RandomNumberReal32 * 1.5707963705062866 + igi2_frame.pvBeta - 0.7853981852531433;
          GunPickup_NewFromWeapon(
            ptQTask[33].ptNext,
            ptParent,
            (struct real64x3_t *)&igi2_frame.ptSource.tX.vZ,
            &igi2_frame.ptPos,
            igi2_frame.pvBeta,
            true);
          Weapon_DisableWeaponType(ptQTask[33].ptNext, (char *)&ptQTask[86].ptParent[2].ptPrev, true);
          ptQTask[86].ptParent = nullptr;
        }
        ptQTask[87].tQTaskRefList.ptHead = nullptr;
      }
      if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER && ptQTask[87].tQTaskChildren.ptTail )
      {
        QTaskFromID = NetworkGameItem_GetQTaskFromID(*(_DWORD *)&ptQTask[86].eQTaskType);
        v8 = QTaskFromID;
        if ( QTaskFromID && !*(_DWORD *)&QTaskFromID[12].eQTaskType )
        {
          igi2_frame.ptSource.tX.vZ = 224748978176.0;
          Timer = NetManager_GetTimer();
          v10 = *(float *)&ptQTask[86].eQTaskType;
          LODWORD(igi2_frame.ptSource.tY.vX) = Timer;
          ptNext = ptQTask[87].ptNext;
          LODWORD(igi2_frame.ptSource.tZ.vX) = Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle;
          igi2_frame.ptSource.tY.vY = v10;
          LODWORD(igi2_frame.ptSource.tY.vZ) = ptNext;
          NetManager_SendGameMessage(
            0,
            SLODWORD(igi2_frame.ptSource.tZ.vX),
            NETWORKQUEUE_GUARANTEED,
            (struct NetManagerGameMessage_s *)&igi2_frame.ptSource.tX.vZ,
            0x14u);
          ptQTask[87].tQTaskChildren.ptTail = nullptr;
          *(_DWORD *)&v8[12].eQTaskType = 1;
        }
      }
      else
      {
        ptQTask[80].tQTaskRefList.ptTail = (struct QReference_s *)2;
      }
    }
    if ( ptQTask[80].tQTaskRefList.ptTail == (struct QReference_s *)2 )
    {
      if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER && ptQTask[87].tQTaskRefList.ptMiddle )
      {
        v12 = WeaponType_GetWeaponTypeFromID((int)ptQTask[87].ptPrev);
        NextEnabledWeaponTypeFromCategory = Weapon_GetNextEnabledWeaponTypeFromCategory(
                                              ptQTask[33].ptNext,
                                              v12->eWeaponCategory,
                                              nullptr);
        if ( NextEnabledWeaponTypeFromCategory )
        {
          igi2_frame.ptPos.tX.vX = 224698597376.0;
          v14 = NetManager_GetTimer();
          ptMiddle = Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle;
          LODWORD(igi2_frame.ptPos.tX.vY) = v14;
          eID = NextEnabledWeaponTypeFromCategory->eID;
          igi2_frame.v46 = ptMiddle;
          igi2_frame.v45 = eID;
          NetManager_SendGameMessage(
            0,
            (int)ptMiddle,
            NETWORKQUEUE_GUARANTEED,
            (struct NetManagerGameMessage_s *)&igi2_frame.ptPos,
            0x48u);
        }
        ptHead = ptQTask[87].tQTaskChildren.ptHead;
        LODWORD(igi2_frame.ptSource.tY.vZ) = ptQTask[87].ptPrev;
        LODWORD(igi2_frame.ptSource.tZ.vY) = 1;
        LODWORD(igi2_frame.ptSource.tX.vZ) = ptHead;
        LODWORD(igi2_frame.ptSource.tY.vX) = ptHead;
        eQTaskType = ptQTask->eQTaskType;
        LODWORD(igi2_frame.ptSource.tY.vY) = 1;
        ((void (__cdecl *)(struct QTask_s *, float *))QTask_aatQTaskFinalEvent[GunPickup_eGunPickupQTaskEvent][eQTaskType].pfHandler)(
          ptQTask,
          &igi2_frame.ptSource.tX.vZ);
        v19 = ptQTask[87].ptPrev;
        ptQTask[87].tQTaskRefList.ptMiddle = nullptr;
        WeaponTypeFromID = WeaponType_GetWeaponTypeFromID((int)v19);
        ptQTask[76].ptParent = ptQTask[87].ptPrev;
      }
      Weapon_Activate(ptQTask[33].ptNext, WeaponTypeFromID->zWeaponScriptID, false);
    }
    ptTail = ptQTask[80].tQTaskRefList.ptTail;
    if ( ptTail == (struct QReference_s *)4 || ptTail == (struct QReference_s *)3 )
    {
      if ( ptTail == (struct QReference_s *)3 )
      {
        v21 = ptQTask[33].ptNext;
        v22 = v21[1].ptPrev;
        if ( v22 )
        {
          v23 = v22->tQTaskChildren.ptTail;
          if ( v23 )
          {
            WeaponTypeItemFromWeaponType = Weapon_GetWeaponTypeItemFromWeaponType(
                                             ptQTask[33].ptNext,
                                             (char *)&v23[2].ptPrev);
            if ( WeaponTypeItemFromWeaponType )
              v21[1].ptNext = (struct QTask_s *)WeaponTypeItemFromWeaponType;
          }
        }
      }
      ptQTask[80].tQTaskRefList.ptTail = nullptr;
      ptQTask[76].ptParent = (struct QTask_s *)-1;
      v25 = *(_DWORD *)&ptQTask[32].eQTaskType;
      ptQTask[77].tQTaskRefList.ptTail = (struct QReference_s *)12;
      ptQTask[87].tQTaskChildren.ptMiddle = (struct QTask_s *)1;
      v26 = v25 == 2 ? 90 : 87;
      if ( v25 == 2 )
      {
        HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
        if ( v26 != 90 )
        {
          HumanAnim_SetAnimationAndTimeFromState(ptQTask, v26, 0, 0.0);
          goto LABEL_52;
        }
        v34 = ptQTask[7].tQTaskRefList.ptTail;
        LODWORD(igi2_frame.ptSource.tZ.vX) = ptQTask[77].ptPrev;
        v35 = ptQTask[33].ptNext;
        ptQTask[35].tQTaskRefList.ptHead = (struct QReference_s *)90;
        LODWORD(igi2_frame.ptSource.tX.vZ) = v34;
        LODWORD(igi2_frame.ptSource.tY.vZ) = 26;
        LODWORD(igi2_frame.ptSource.tY.vX) = v35;
        igi2_frame.ptSource.tY.vY = 0.0;
        igi2_frame.ptSource.tZ.vZ = 0.0;
        v36 = v35[1].ptPrev;
        if ( v36 )
          v37 = v36->tQTaskChildren.ptTail;
        else
          v37 = nullptr;
        v38 = v35[1].ptPrev;
        pfHandler = (void (__cdecl *)(struct QTask_s *, float *))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][v37->eQTaskType].pfHandler;
        if ( v38 )
          v40 = v38->tQTaskChildren.ptTail;
        else
          v40 = nullptr;
        pfHandler(v40, &igi2_frame.ptSource.tX.vZ);
        if ( LODWORD(igi2_frame.ptSource.tZ.vZ) )
          goto LABEL_40;
      }
      else
      {
        v27 = ptQTask[7].tQTaskRefList.ptTail;
        LODWORD(igi2_frame.ptSource.tZ.vX) = ptQTask[77].ptPrev;
        v28 = ptQTask[33].ptNext;
        ptQTask[35].tQTaskRefList.ptHead = (struct QReference_s *)87;
        LODWORD(igi2_frame.ptSource.tX.vZ) = v27;
        LODWORD(igi2_frame.ptSource.tY.vZ) = 15;
        LODWORD(igi2_frame.ptSource.tY.vX) = v28;
        igi2_frame.ptSource.tY.vY = 0.0;
        igi2_frame.ptSource.tZ.vZ = 0.0;
        v29 = v28[1].ptPrev;
        if ( v29 )
          v30 = v29->tQTaskChildren.ptTail;
        else
          v30 = nullptr;
        v31 = v28[1].ptPrev;
        v32 = (void (__cdecl *)(struct QTask_s *, float *))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][v30->eQTaskType].pfHandler;
        if ( v31 )
          v33 = v31->tQTaskChildren.ptTail;
        else
          v33 = nullptr;
        v32(v33, &igi2_frame.ptSource.tX.vZ);
        if ( LODWORD(igi2_frame.ptSource.tZ.vZ) )
        {
LABEL_40:
          HumanAnim_SetUpperBodyAnimationFromHeader(
            ptQTask,
            (struct AnimHeader_s *)LODWORD(igi2_frame.ptSource.tZ.vZ),
            *(_DWORD *)(LODWORD(igi2_frame.ptSource.tZ.vZ) + 16),
            0.0);
          *(_QWORD *)&igi2_frame.ptSource.tX.vX = (__int64)(-*(float *)&igi2_frame.ptSource.nOps * (double)AnimController_nTicksPerFrame);
          ptQTask[34].tQTaskRefList.ptHead[5].pxObject = (void *)LODWORD(igi2_frame.ptSource.tX.vX);
LABEL_52:
          HumanPlayer_SetWeaponTypeAnim(ptQTask, WEAPONTYPE_GETANIMTYPE_1STACTIVATE, 0, true);
          HumanPlayer_SetWeaponPrecision(ptQTask, (enum HumanPlayerPrecisionType_e)ptQTask[77].tQTaskChildren.ptHead);
          ptState->pfState = (void (__cdecl *)(struct State_s *, struct QTask_s *))sub_4C2030;
          return;
        }
      }
      HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
      goto LABEL_52;
    }
  }
}

void __cdecl sub_4C2030(int a1, int a2)
{
  void (__cdecl *v2)(int, int); // eax
  int v3; // eax
  void (__cdecl *v4)(int, int); // eax

  if ( (*(_BYTE *)(a1 + 12) & 1) != 0 )
  {
    *(_BYTE *)(a2 + 1328) = 1;
    v2 = *(void (__cdecl **)(int, int))(*(_DWORD *)(a1 + 8) + 4 * *(_DWORD *)(a1 + 20));
    if ( v2 )
      v2(a1, a2);
    v3 = *(_DWORD *)(a1 + 4);
    *(_DWORD *)(a1 + 16) = *(_DWORD *)(a1 + 20);
    *(_DWORD *)(a1 + 20) = 1;
    v4 = *(void (__cdecl **)(int, int))(v3 + 4);
    *(_DWORD *)(a1 + 24) = v4;
    v4(a1, a2);
  }
}

// source: j/0/human/humanplayer.c:14860  [anchor-mhash]
void __cdecl HumanPlayer_InitActionPeek(struct State_s *ptState, struct QTask_s *ptQTask)
{
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptParent; // ecx
  void (__cdecl *v4)(struct QReference_s **, struct QTask_s *); // eax
  struct QReference_s *ptTail; // ecx
  struct QTask_s *v6; // eax
  struct QTask_s *v7; // eax

  ptPrev = ptQTask[31].ptPrev;
  ptParent = ptQTask[30].ptParent;
  LOBYTE(ptQTask[46].tQTaskRefList.ptMiddle) = 1;
  v4 = *((void (__cdecl **)(struct QReference_s **, struct QTask_s *))&ptParent->ptNext + (_DWORD)ptPrev);
  if ( v4 )
    v4(&ptQTask[30].tQTaskRefList.ptMiddle, ptQTask);
  ptTail = ptQTask[30].tQTaskRefList.ptTail;
  ptQTask[31].ptNext = ptQTask[31].ptPrev;
  ptQTask[31].ptPrev = (struct QTask_s *)52;
  v6 = (struct QTask_s *)ptTail[17].ptPrev;
  ptQTask[31].tQTaskChildren.ptHead = v6;
  ((void (__cdecl *)(struct QReference_s **, struct QTask_s *))v6)(&ptQTask[30].tQTaskRefList.ptMiddle, ptQTask);
  v7 = ptQTask[33].tQTaskChildren.ptTail;
  v7[15].tQTaskRefList.ptTail = (struct QReference_s *)-1088659030;
  v7[16].ptNext = (struct QTask_s *)-1095583549;
  v7[15].ptParent = (struct QTask_s *)1030638510;
  v7[16].ptPrev = (struct QTask_s *)1023945535;
  LOBYTE(ptQTask[34].tQTaskChildren.ptMiddle) = 1;
  ptState->pfState = HumanPlayer_RunActionPeek;
}

// source: j/0/human/humanplayer.c:14885  [anchor-mhash]
void __cdecl HumanPlayer_RunActionPeek(struct State_s *ptState, struct QTask_s *ptQTask)
{
  struct QTask_s *ptTail; // ecx
  struct QTask_s *ptParent; // ecx
  void (__cdecl *v4)(struct QReference_s **, struct QTask_s *); // eax
  struct QReference_s *v5; // ecx
  struct QTask_s *pxObject; // eax
  struct QReference_s *v7; // ecx
  void (__cdecl *v8)(struct QReference_s **, struct QTask_s *); // eax
  struct QReference_s *v9; // ecx
  struct QTask_s *v10; // eax
  void (__cdecl *v11)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v13)(struct State_s *, struct QTask_s *); // eax

  ptTail = ptQTask[33].tQTaskChildren.ptTail;
  if ( *(float *)&ptQTask[20].tQTaskChildren.ptMiddle == 0.0 || (ptState->bSignal & 0x20000) != 0 )
  {
    BYTE1(ptQTask[46].tQTaskRefList.ptMiddle) = 1;
    LOBYTE(ptQTask[34].tQTaskChildren.ptMiddle) = 0;
    LOBYTE(ptQTask[46].tQTaskRefList.ptMiddle) = 0;
    ptTail[14].tQTaskChildren.ptTail = nullptr;
    ptTail[14].tQTaskRefList.ptHead = nullptr;
    ptTail[14].tQTaskRefList.ptMiddle = nullptr;
    ptParent = ptQTask[30].ptParent;
    if ( *(_DWORD *)&ptQTask[32].eQTaskType == 1 )
    {
      v8 = *((void (__cdecl **)(struct QReference_s **, struct QTask_s *))&ptParent->ptNext + (int)ptQTask[31].ptPrev);
      if ( v8 )
        v8(&ptQTask[30].tQTaskRefList.ptMiddle, ptQTask);
      v9 = ptQTask[30].tQTaskRefList.ptTail;
      ptQTask[31].ptNext = ptQTask[31].ptPrev;
      ptQTask[31].ptPrev = (struct QTask_s *)23;
      pxObject = (struct QTask_s *)v9[7].pxObject;
    }
    else
    {
      v4 = *((void (__cdecl **)(struct QReference_s **, struct QTask_s *))&ptParent->ptNext + (int)ptQTask[31].ptPrev);
      if ( *(_DWORD *)&ptQTask[32].eQTaskType == 2 )
      {
        if ( v4 )
          v4(&ptQTask[30].tQTaskRefList.ptMiddle, ptQTask);
        v7 = ptQTask[30].tQTaskRefList.ptTail;
        ptQTask[31].ptNext = ptQTask[31].ptPrev;
        ptQTask[31].ptPrev = (struct QTask_s *)75;
        pxObject = (struct QTask_s *)v7[25].ptNext;
      }
      else
      {
        if ( v4 )
          v4(&ptQTask[30].tQTaskRefList.ptMiddle, ptQTask);
        v5 = ptQTask[30].tQTaskRefList.ptTail;
        ptQTask[31].ptNext = ptQTask[31].ptPrev;
        ptQTask[31].ptPrev = nullptr;
        pxObject = (struct QTask_s *)v5->ptNext;
      }
    }
    ptQTask[31].tQTaskChildren.ptHead = pxObject;
    ((void (__cdecl *)(struct QReference_s **, struct QTask_s *))pxObject)(&ptQTask[30].tQTaskRefList.ptMiddle, ptQTask);
    v10 = ptQTask[33].tQTaskChildren.ptTail;
    v10[15].tQTaskRefList.ptTail = nullptr;
    v10[16].ptNext = nullptr;
    v10[15].ptParent = (struct QTask_s *)1030638510;
    v10[16].ptPrev = (struct QTask_s *)1023945535;
    v11 = ptState->apfExitState[ptState->nState];
    if ( v11 )
      v11(ptState, ptQTask);
    apfState = ptState->apfState;
    ptState->nPreviousState = ptState->nState;
    ptState->nState = 1;
    v13 = apfState[1];
    ptState->pfState = v13;
    v13(ptState, ptQTask);
  }
}

// source: j/0/human/humanplayer.c:14946  [anchor-mhash]
void __cdecl HumanPlayer_InitActionComputer(struct State_s *ptState, struct QTask_s *ptQTask)
{
  void (__cdecl *v2)(struct QReference_s **, struct QTask_s *); // eax
  struct QReference_s *ptTail; // eax
  struct QTask_s *pxObject; // eax

  v2 = *((void (__cdecl **)(struct QReference_s **, struct QTask_s *))&ptQTask[30].ptParent->ptNext
       + (int)ptQTask[31].ptPrev);
  if ( v2 )
    v2(&ptQTask[30].tQTaskRefList.ptMiddle, ptQTask);
  ptTail = ptQTask[30].tQTaskRefList.ptTail;
  ptQTask[31].ptNext = ptQTask[31].ptPrev;
  ptQTask[31].ptPrev = (struct QTask_s *)53;
  pxObject = (struct QTask_s *)ptTail[17].pxObject;
  ptQTask[31].tQTaskChildren.ptHead = pxObject;
  ((void (__cdecl *)(struct QReference_s **, struct QTask_s *))pxObject)(&ptQTask[30].tQTaskRefList.ptMiddle, ptQTask);
  LOBYTE(ptQTask[33].tQTaskChildren.ptHead) = 0;
  ptState->pfState = (void (__cdecl *)(struct State_s *, struct QTask_s *))sub_4C2310;
}

void __cdecl sub_4C2310(_DWORD *a1, int a2)
{
  void (__cdecl *v2)(_DWORD *, int); // eax
  int v3; // eax
  void (__cdecl *v4)(_DWORD *, int); // eax

  if ( *(_DWORD *)(a2 + 1244) != 53 )
  {
    *(_BYTE *)(a2 + 1328) = 1;
    v2 = *(void (__cdecl **)(_DWORD *, int))(a1[2] + 4 * a1[5]);
    if ( v2 )
      v2(a1, a2);
    v3 = a1[1];
    a1[4] = a1[5];
    a1[5] = 1;
    v4 = *(void (__cdecl **)(_DWORD *, int))(v3 + 4);
    a1[6] = v4;
    v4(a1, a2);
  }
}

void __cdecl sub_4C2360(struct QTask_s *a1, _DWORD *a2)
{
  int v2; // esi
  __int16 v3; // dx
  int v4; // eax
  int v5; // ecx
  int v6; // ecx

  v2 = *a2;
  v3 = *(_WORD *)(*a2 + 36);
  if ( v3 == HumanPlayer_eQTaskType )
  {
    v6 = a2[2];
    switch ( v6 )
    {
      case 0:
        *(_DWORD *)(v2 + 1236) |= 0x200000u;
        break;
      case 1:
        *(_DWORD *)(v2 + 1236) |= 0x400000u;
        break;
      case 3:
        return;
      case 8:
        *(_DWORD *)(v2 + 1236) |= 0x100000u;
        break;
      default:
        LDebug_Error("Unknown animtrigger for humanplayer: %d", v6);
        abort();
    }
  }
  else
  {
    v4 = *(_DWORD *)(v2 + 32);
    if ( *(_WORD *)(v4 + 36) == HumanPlayer_eQTaskType )
    {
      v5 = a2[2];
      if ( v5 == 3 )
      {
        *(_BYTE *)(v4 + 3360) = 1;
      }
      else if ( v5 == 8 )
      {
        *(_DWORD *)(v4 + 2996) |= 0x100000u;
      }
    }
    else if ( a2[2] == 8 && v3 == HumanRemote_eQTaskType && v2 )
    {
      if ( *(_BYTE *)(v2 + 3269) )
        Human_CreateSwimStrokeSound((struct QTask_s *)*a2);
      else
        Human_MakeLadderFootstepSound((struct QTask_s *)v2);
    }
  }
}

// source: j/0/human/humanplayer.c:15083  [anchor-strings]
void __cdecl HumanPlayer_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[24]; struct real64x3_t ptPos; };
    char igi2_extent[52];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  bool v2; // zf
  struct QReferenceList_s *p_tQTaskRefList; // esi
  struct QTask_s *v4; // ecx
  double vMaxDamageScale; // st7

  memset(&igi2_frame.ptPos, 0, sizeof(igi2_frame.ptPos));
  if ( !Level_atLevelQTaskID[0] || !Level_atLevelQTaskID[0]->pxObject )
    Level_DefineQTaskID(0, ptQTask);
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][Human_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  if ( HumanPlayer_ptQTask )
  {
    LOBYTE(ptQTask[46].eQTaskType) = 1;
  }
  else
  {
    v2 = Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER;
    HumanPlayer_ptQTask = ptQTask;
    BYTE1(ptQTask[40].tQTaskChildren.ptMiddle) = 1;
    BYTE2(ptQTask[40].tQTaskChildren.ptMiddle) = 1;
    HIBYTE(ptQTask[40].tQTaskChildren.ptMiddle) = 1;
    LOBYTE(ptQTask[40].tQTaskChildren.ptTail) = 1;
    ptQTask[36].tQTaskRefList.ptTail = nullptr;
    ptQTask[36].ptParent = nullptr;
    *(_DWORD *)&ptQTask[36].eQTaskType = 0;
    ptQTask[37].ptNext = nullptr;
    ptQTask[37].ptPrev = nullptr;
    if ( !v2 )
    {
      igi2_frame.ptDynCubeObj = sqrt(
                       *(float *)&ptQTask[7].tQTaskRefList.ptHead * *(float *)&ptQTask[7].tQTaskRefList.ptHead
                     + *(float *)&ptQTask[7].tQTaskRefList.ptMiddle * *(float *)&ptQTask[7].tQTaskRefList.ptMiddle
                     + *(float *)&ptQTask[7].tQTaskChildren.ptTail * *(float *)&ptQTask[7].tQTaskChildren.ptTail)
                   + *(float *)&ptQTask[8].ptNext;
      World_RegisterDynCubeObjFirstTimeRadius(
        Game_ptGame->ptWorld,
        (struct DynCubeObj_s *)ptQTask,
        &igi2_frame.ptPos,
        igi2_frame.ptDynCubeObj,
        WORLD_DYNCUBETREE_CATEGORY_MOBILE);
    }
    v2 = Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER;
    ptQTask[77].tQTaskRefList.ptHead = nullptr;
    ptQTask[77].tQTaskRefList.ptMiddle = nullptr;
    ptQTask[77].tQTaskChildren.ptMiddle = nullptr;
    ptQTask[77].tQTaskChildren.ptTail = nullptr;
    ptQTask[84].tQTaskRefList.ptTail = (struct QReference_s *)1056964608;
    ptQTask[84].ptParent = (struct QTask_s *)1008981770;
    *(_DWORD *)&ptQTask[84].eQTaskType = 1065353216;
    LOBYTE(ptQTask[85].ptNext) = 0;
    ptQTask[88].ptNext = nullptr;
    ptQTask[88].ptPrev = nullptr;
    *(_DWORD *)&ptQTask[87].eQTaskType = 0;
    ptQTask[88].tQTaskChildren.ptHead = nullptr;
    ptQTask[88].tQTaskChildren.ptMiddle = nullptr;
    ptQTask[88].tQTaskChildren.ptTail = nullptr;
    if ( v2 )
    {
      LOBYTE(ptQTask[80].tQTaskChildren.ptTail) = 0;
      ptQTask[30].tQTaskRefList.ptMiddle = (struct QReference_s *)HumanPlayer_StateSignalHandler;
      ptQTask[30].tQTaskRefList.ptTail = (struct QReference_s *)HumanPlayer_apfState;
      ptQTask[30].ptParent = (struct QTask_s *)HumanPlayer_apfExitState;
      *(_DWORD *)&ptQTask[30].eQTaskType = 0;
      ptQTask[31].ptNext = (struct QTask_s *)-1;
      ptQTask[31].ptPrev = (struct QTask_s *)56;
      ptQTask[31].tQTaskChildren.ptHead = (struct QTask_s *)HumanPlayer_apfState[56];
      ptQTask[31].tQTaskChildren.ptMiddle = (struct QTask_s *)2;
      ptQTask[31].tQTaskChildren.ptTail = (struct QTask_s *)-1;
      ptQTask[31].tQTaskRefList.ptHead = (struct QReference_s *)HumanPlayer_atSequence;
      memset(&ptQTask[31].tQTaskRefList.ptMiddle, 0, sizeof(struct QTask_s));
      p_tQTaskRefList = &ptQTask[25].tQTaskRefList;
      ptQTask[25].tQTaskRefList.ptMiddle = (struct QReference_s *)LODWORD(HumanPlayer_tGeneral.vMaxDamageScale);
      ptQTask[25].tQTaskRefList.ptTail = (struct QReference_s *)HumanPlayer_atDamagePartDataMultiplayer;
      HumanDamage_ClearDamage((struct HumanDamage_t *)&ptQTask[25].tQTaskRefList);
      ptQTask[29].tQTaskChildren.ptHead = (struct QTask_s *)-1;
    }
    else
    {
      ptQTask[31].ptNext = (struct QTask_s *)-1;
      ptQTask[30].tQTaskRefList.ptMiddle = (struct QReference_s *)HumanPlayer_StateSignalHandler;
      ptQTask[30].tQTaskRefList.ptTail = (struct QReference_s *)HumanPlayer_apfState;
      ptQTask[30].ptParent = (struct QTask_s *)HumanPlayer_apfExitState;
      *(_DWORD *)&ptQTask[30].eQTaskType = 0;
      ptQTask[31].ptPrev = nullptr;
      v4 = (struct QTask_s *)HumanPlayer_apfState[0];
      ptQTask[31].tQTaskChildren.ptTail = (struct QTask_s *)-1;
      ptQTask[31].tQTaskChildren.ptHead = v4;
      ptQTask[31].tQTaskChildren.ptMiddle = (struct QTask_s *)2;
      ptQTask[31].tQTaskRefList.ptHead = (struct QReference_s *)HumanPlayer_atSequence;
      memset(&ptQTask[31].tQTaskRefList.ptMiddle, 0, sizeof(struct QTask_s));
      LOBYTE(ptQTask[80].tQTaskChildren.ptTail) = 1;
      vMaxDamageScale = HumanPlayer_tGeneral.vMaxDamageScale;
      if ( Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eDifficultyLevel == GAMEDIFFICULTY_2 )
      {
        vMaxDamageScale = HumanPlayer_tGeneral.vMaxDamageScale * 0.699999988079071;
      }
      else if ( Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eDifficultyLevel == GAMEDIFFICULTY_3 )
      {
        vMaxDamageScale = HumanPlayer_tGeneral.vMaxDamageScale * 0.4000000059604645;
      }
      p_tQTaskRefList = &ptQTask[25].tQTaskRefList;
      *(float *)&ptQTask[25].tQTaskRefList.ptMiddle = vMaxDamageScale;
      ptQTask[25].tQTaskRefList.ptTail = (struct QReference_s *)HumanPlayer_atDamagePartData;
      HumanDamage_ClearDamage((struct HumanDamage_t *)&ptQTask[25].tQTaskRefList);
      ptQTask[29].tQTaskChildren.ptHead = (struct QTask_s *)-1;
    }
    p_tQTaskRefList[12].ptTail = nullptr;
    p_tQTaskRefList[13].ptHead = nullptr;
    ptQTask[32].tQTaskRefList.ptMiddle = (struct QReference_s *)HumanPlayer_atStateAnimData;
    ptQTask[74].tQTaskRefList.ptMiddle = (struct QReference_s *)HumanPlayer_ActionSignalHandler;
    ptQTask[74].tQTaskRefList.ptTail = (struct QReference_s *)HumanPlayer_apfAction;
    ptQTask[74].ptParent = (struct QTask_s *)HumanPlayer_apfExitAction;
    *(_DWORD *)&ptQTask[74].eQTaskType = 0;
    ptQTask[75].ptNext = (struct QTask_s *)-1;
    ptQTask[75].ptPrev = (struct QTask_s *)1;
    ptQTask[75].tQTaskChildren.ptHead = (struct QTask_s *)HumanPlayer_apfAction[1];
    ptQTask[75].tQTaskChildren.ptMiddle = nullptr;
    ptQTask[75].tQTaskChildren.ptTail = (struct QTask_s *)-1;
    ptQTask[75].tQTaskRefList.ptHead = nullptr;
    memset(&ptQTask[75].tQTaskRefList.ptMiddle, 0, sizeof(struct QTask_s));
    v2 = Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER;
    LOBYTE(ptQTask[76].tQTaskRefList.ptMiddle) = 0;
    BYTE1(ptQTask[76].tQTaskRefList.ptMiddle) = 0;
    ptQTask[76].tQTaskRefList.ptTail = nullptr;
    ptQTask[76].ptParent = (struct QTask_s *)-1;
    *(_DWORD *)&ptQTask[76].eQTaskType = -1;
    ptQTask[77].ptNext = nullptr;
    ptQTask[77].tQTaskRefList.ptTail = nullptr;
    ptQTask[77].ptParent = nullptr;
    LOBYTE(ptQTask[78].ptPrev) = 0;
    LOBYTE(ptQTask[78].tQTaskChildren.ptTail) = 0;
    BYTE1(ptQTask[78].tQTaskChildren.ptTail) = 0;
    BYTE2(ptQTask[78].tQTaskChildren.ptTail) = 0;
    LOBYTE(ptQTask[78].ptParent) = 0;
    BYTE1(ptQTask[78].ptParent) = 0;
    BYTE2(ptQTask[78].ptParent) = 0;
    HIBYTE(ptQTask[78].ptParent) = 0;
    LOBYTE(ptQTask[78].eQTaskType) = 0;
    ptQTask[79].ptPrev = nullptr;
    LOBYTE(ptQTask[79].tQTaskChildren.ptHead) = 0;
    BYTE1(ptQTask[79].tQTaskChildren.ptHead) = 0;
    ptQTask[79].ptParent = nullptr;
    *(_DWORD *)&ptQTask[79].eQTaskType = 0;
    ptQTask[80].ptNext = nullptr;
    ptQTask[80].ptPrev = nullptr;
    ptQTask[80].tQTaskChildren.ptHead = nullptr;
    ptQTask[80].tQTaskChildren.ptMiddle = nullptr;
    ptQTask[86].tQTaskRefList.ptHead = nullptr;
    ptQTask[86].tQTaskRefList.ptMiddle = nullptr;
    BYTE1(ptQTask[80].tQTaskChildren.ptTail) = 0;
    if ( v2 )
      LOBYTE(ptQTask[29].tQTaskRefList.ptHead) = 1;
    Symbol_Register(
      "HumanPlayer_Activate",
      HumanPlayer_ActivateScriptFunction,
      ptQTask,
      1,
      QSCRIPT_SYMBOLCLASS_FUNCTION,
      QSCRIPT_SYMBOLTYPE_VOID,
      QSCRIPT_SYMBOLLIFESPAN_INFINITE);
    Symbol_Register(
      "HumanPlayer_LockActivate",
      HumanPlayer_LockActivateScriptFunction,
      ptQTask,
      1,
      QSCRIPT_SYMBOLCLASS_FUNCTION,
      QSCRIPT_SYMBOLTYPE_VOID,
      QSCRIPT_SYMBOLLIFESPAN_INFINITE);
    v2 = Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER;
    BYTE1(ptQTask[80].tQTaskRefList.ptMiddle) = 0;
    LOBYTE(ptQTask[80].tQTaskRefList.ptMiddle) = 0;
    ptQTask[80].ptParent = nullptr;
    *(_DWORD *)&ptQTask[80].eQTaskType = 0;
    BYTE2(ptQTask[80].tQTaskRefList.ptMiddle) = 0;
    ptQTask[81].ptNext = nullptr;
    if ( v2 )
      Weapon_EnableWeaponType(ptQTask[33].ptNext, "WEAPON_ID_KNIFE", true);
    v2 = Game_eGameMode == GAME_GAMEMODE_SINGLEPLAYER;
    HIBYTE(ptQTask[80].tQTaskRefList.ptMiddle) = 0;
    ptQTask[80].tQTaskRefList.ptHead = nullptr;
    ptQTask[85].tQTaskChildren.ptMiddle = nullptr;
    ptQTask[85].tQTaskChildren.ptHead = nullptr;
    ptQTask[85].tQTaskChildren.ptTail = nullptr;
    ptQTask[85].ptPrev = nullptr;
    ptQTask[84].ptPrev = nullptr;
    if ( v2 && Game_FindNewestSaveGame((int *)&ptQTask[85].tQTaskChildren.ptTail) )
      ++*(int *)&ptQTask[85].tQTaskChildren.ptTail;
    v2 = Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER;
    ptQTask[80].tQTaskRefList.ptTail = nullptr;
    BYTE1(ptQTask[84].ptNext) = 0;
    LOBYTE(ptQTask[84].ptNext) = 0;
    ptQTask[83].ptParent = nullptr;
    ptQTask[83].isInMemPool = 0;
    ptQTask[83].eQTaskType = 0;
    BYTE1(ptQTask[80].tQTaskRefList.ptMiddle) = 0;
    ptQTask[84].tQTaskChildren.ptTail = nullptr;
    ptQTask[84].tQTaskRefList.ptHead = nullptr;
    ptQTask[84].tQTaskRefList.ptMiddle = nullptr;
    if ( v2 )
    {
      ptQTask[85].tQTaskRefList.ptTail = (struct QReference_s *)-1;
      ptQTask[85].ptParent = nullptr;
      ptQTask[86].ptNext = nullptr;
      *(_DWORD *)&ptQTask[85].eQTaskType = 0;
      ptQTask[86].ptPrev = nullptr;
    }
    ptQTask[86].tQTaskChildren.ptHead = nullptr;
    ptQTask[86].tQTaskChildren.ptMiddle = nullptr;
    ptQTask[86].tQTaskChildren.ptTail = nullptr;
    ptQTask[84].tQTaskChildren.ptHead = (struct QTask_s *)1065353216;
    ptQTask[84].tQTaskChildren.ptMiddle = nullptr;
    ptQTask[86].tQTaskRefList.ptTail = nullptr;
    ptQTask[86].ptParent = nullptr;
    ptQTask[87].tQTaskRefList.ptHead = nullptr;
    ptQTask[87].tQTaskRefList.ptTail = nullptr;
    ptQTask[87].ptParent = nullptr;
    ptQTask[87].tQTaskChildren.ptTail = nullptr;
    ptQTask[87].tQTaskRefList.ptMiddle = nullptr;
    ptQTask[87].tQTaskChildren.ptMiddle = nullptr;
    ptQTask[88].tQTaskRefList.ptHead = nullptr;
    ptQTask[88].tQTaskRefList.ptMiddle = nullptr;
    ptQTask[88].tQTaskRefList.ptTail = nullptr;
    ptQTask[88].ptParent = nullptr;
    *(_DWORD *)&ptQTask[88].eQTaskType = 0;
    ptQTask[90].tQTaskRefList.ptMiddle = nullptr;
  }
}

// source: j/0/human/humanplayer.c:15370  [anchor-mhash]
void __cdecl HumanPlayer_SmokeDamageHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v3; };
    struct { char igi2_o1[8]; struct real32x3_t tReal32x3; };
    char igi2_extent[24];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v2; // st3

  igi2_frame.tReal32x3.vX = *(double *)&ptQTask[1].ptNext - *(double *)pxContext;
  igi2_frame.tReal32x3.vY = *(double *)&ptQTask[1].tQTaskChildren.ptHead - *((double *)pxContext + 1);
  v2 = *(double *)&ptQTask[1].tQTaskChildren.ptTail - *((double *)pxContext + 2);
  if ( sqrt(igi2_frame.tReal32x3.vX * igi2_frame.tReal32x3.vX + igi2_frame.tReal32x3.vY * igi2_frame.tReal32x3.vY + v2 * v2) <= *((float *)pxContext + 7) )
  {
    igi2_frame.v3 = *((float *)pxContext + 6);
    memset(&igi2_frame.tReal32x3, 0, sizeof(igi2_frame.tReal32x3));
    HumanPlayer_HandleDamage((struct HumanPlayer_t *)ptQTask, HUMANDAMAGE_PART_HEAD, igi2_frame.v3, &igi2_frame.tReal32x3);
  }
}

// source: j/0/human/humanplayer.c:15398  [anchor-callee]
void __cdecl HumanPlayer_SampleRotation(struct HumanPlayer_t *ptHumanPlayer)
{
  DWORD PerformanceCounter; // eax
  float v2; // eax
  double v3; // st7
  double vIdealGamma; // st6

  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  LODWORD(v2) = PerformanceCounter - Timer_nStartTime;
  if ( (int)(LODWORD(v2) - LODWORD(ptHumanPlayer->tRotationTracker.vPrevGamma)) > 3 )
  {
    v3 = *(float *)&ptHumanPlayer->tHuman.ptHumanViewQTask[11].eQTaskType;
    vIdealGamma = ptHumanPlayer->tHuman.vIdealGamma;
    ptHumanPlayer->tRotationTracker.vPrevGamma = v2;
    ptHumanPlayer->tGroundMovementSpeed.vX = (v3 - ptHumanPlayer->tRotationTracker.vAlphaSpeed) * 30.0;
    ptHumanPlayer->tGroundMovementSpeed.vY = (vIdealGamma - ptHumanPlayer->tRotationTracker.vGammaSpeed) * 30.0;
    ptHumanPlayer->tRotationTracker.vAlphaSpeed = v3;
    ptHumanPlayer->tRotationTracker.vGammaSpeed = vIdealGamma;
  }
}

// source: j/0/human/humanplayer.c:15448  [anchor-callee]
void __cdecl HumanPlayer_UpdateVisibilityFactor(struct QTask_s *ptQTask)
{
  double v1; // st7
  double v2; // st7
  double v3; // st7
  float v4; // [esp+0h] [ebp-4h]

  if ( ptQTask[49].tQTaskChildren.ptTail )
  {
    ptQTask[49].tQTaskRefList.ptMiddle = (struct QReference_s *)1065353216;
  }
  else
  {
    v1 = *(float *)&ptQTask[49].ptParent * 0.5;
    if ( v1 >= 0.0 )
    {
      if ( v1 <= 1.0 )
        v4 = v1;
      else
        v4 = 1.0;
    }
    else
    {
      v4 = 0.0;
    }
    *(float *)&ptQTask[49].tQTaskRefList.ptMiddle = pow(v4, *(float *)&ptQTask[84].tQTaskRefList.ptTail);
  }
  if ( *(_DWORD *)&ptQTask[32].eQTaskType == 1 )
  {
    v2 = *(float *)&ptQTask[49].tQTaskRefList.ptMiddle * 0.800000011920929;
  }
  else
  {
    if ( *(_DWORD *)&ptQTask[32].eQTaskType != 2 )
      goto LABEL_14;
    v2 = *(float *)&ptQTask[49].tQTaskRefList.ptMiddle * 0.6000000238418579;
  }
  *(float *)&ptQTask[49].tQTaskRefList.ptMiddle = v2;
LABEL_14:
  switch ( (unsigned int)ptQTask[31].ptPrev )
  {
    case 1u:
    case 0x18u:
    case 0x50u:
      v3 = *(float *)&ptQTask[49].tQTaskRefList.ptMiddle + 0.05000000074505806;
      goto LABEL_18;
    case 3u:
    case 4u:
    case 5u:
    case 6u:
    case 7u:
    case 8u:
    case 9u:
    case 0xAu:
      v3 = *(float *)&ptQTask[49].tQTaskRefList.ptMiddle + 0.15000000596046448;
      goto LABEL_18;
    case 0xBu:
    case 0xCu:
    case 0xDu:
    case 0xEu:
    case 0xFu:
    case 0x10u:
    case 0x11u:
    case 0x12u:
    case 0x1Au:
    case 0x1Bu:
    case 0x1Cu:
    case 0x1Du:
    case 0x1Eu:
    case 0x1Fu:
    case 0x20u:
    case 0x21u:
      v3 = *(float *)&ptQTask[49].tQTaskRefList.ptMiddle + 0.10000000149011612;
LABEL_18:
      *(float *)&ptQTask[49].tQTaskRefList.ptMiddle = v3;
      break;
    default:
      break;
  }
  if ( *(float *)&ptQTask[84].ptParent <= (double)*(float *)&ptQTask[49].tQTaskRefList.ptMiddle )
  {
    if ( *(float *)&ptQTask[84].eQTaskType >= (double)*(float *)&ptQTask[49].tQTaskRefList.ptMiddle )
      ptQTask[49].tQTaskRefList.ptMiddle = ptQTask[49].tQTaskRefList.ptMiddle;
    else
      ptQTask[49].tQTaskRefList.ptMiddle = *(struct QReference_s **)&ptQTask[84].eQTaskType;
  }
  else
  {
    ptQTask[49].tQTaskRefList.ptMiddle = (struct QReference_s *)ptQTask[84].ptParent;
  }
}

// source: j/0/human/humanplayer.c:15550  [anchor-mhash]
enum bool __cdecl HumanPlayer_IsZoomedModeAllowed(struct QTask_s *ptQTask)
{
  enum bool v1; // edx
  struct QTask_s *ptPrev; // ecx

  v1 = false;
  switch ( (unsigned int)ptQTask[31].ptPrev )
  {
    case 0u:
    case 1u:
    case 0xBu:
    case 0xCu:
    case 0xDu:
    case 0xEu:
    case 0xFu:
    case 0x10u:
    case 0x11u:
    case 0x12u:
    case 0x17u:
    case 0x18u:
    case 0x1Au:
    case 0x1Bu:
    case 0x1Cu:
    case 0x1Du:
    case 0x1Eu:
    case 0x1Fu:
    case 0x20u:
    case 0x21u:
    case 0x4Bu:
      goto LABEL_6;
    case 0x50u:
      if ( *(float *)&ptQTask[19].tQTaskChildren.ptMiddle == 0.0
        && *(float *)&ptQTask[19].tQTaskChildren.ptTail == 0.0
        && *(float *)&ptQTask[19].tQTaskRefList.ptHead == 0.0
        && *(float *)&ptQTask[19].tQTaskRefList.ptMiddle == 0.0 )
      {
LABEL_6:
        v1 = true;
      }
      break;
    default:
      break;
  }
  ptPrev = ptQTask[75].ptPrev;
  if ( (int)ptPrev > 0 && ((int)ptPrev <= 4 || ptPrev == (struct QTask_s *)9) )
    return v1;
  else
    return false;
}

// source: j/0/human/humanplayer.c:15624  [anchor-hash]
void __cdecl HumanPlayer_CheckZoomedModeAvailability(struct QTask_s *ptQTask)
{
  if ( HumanPlayer_IsZoomedModeAllowed(ptQTask) == false )
    HumanPlayer_LeaveZoomAlternateFireMode(ptQTask);
}

// source: j/0/human/humanplayer.c:15643  [anchor-callee]
struct HumanPlayer_t *__cdecl HumanPlayer_MaintainCollisionZOffset(
        struct HumanPlayer_t *ptHumanPlayer)
{
  int ePose; // ecx
  struct QReference_s *ptGroundQTaskRef; // ecx
  _WORD *pxObject; // ecx

  ePose = ptHumanPlayer->tHuman.ePose;
  if ( ePose >= 0 )
  {
    if ( ePose <= 1 )
    {
      if ( (ptHumanPlayer->tHuman.tState.bSignal & 0x2000) != 0 && ptHumanPlayer->tHuman.tState.nState == 36 )
      {
        ptHumanPlayer->tHuman.vCollisionZOffset = 2048.0;
        ptHumanPlayer->tHuman.vGroundCheckZOffset = 6144.0;
        return ptHumanPlayer;
      }
      ptHumanPlayer->tHuman.vCollisionZOffset = 0.0;
    }
    else
    {
      if ( ePose != 2 )
        return ptHumanPlayer;
      ptGroundQTaskRef = ptHumanPlayer->tHuman.ptGroundQTaskRef;
      ptHumanPlayer->tHuman.vCollisionZOffset = 0.0;
      if ( !ptGroundQTaskRef || (pxObject = ptGroundQTaskRef->pxObject) == nullptr || pxObject[18] != Train_eQTaskType )
      {
        ptHumanPlayer->tHuman.vGroundCheckZOffset = 1228.800048828125;
        return ptHumanPlayer;
      }
    }
    ptHumanPlayer->tHuman.vGroundCheckZOffset = 4096.0;
  }
  return ptHumanPlayer;
}

// source: j/0/human/humanplayer.c:15696  [size]
void __cdecl HumanPlayer_RunHandler(struct QTask_s *ptQTask)
{
  struct QReference_s *v1; // eax

  v1 = QTask_NewQTaskRef(ptQTask);
  QVector_AddElement(RunDelayed_ptRunDelayedQTaskRefVector, v1);
}

// source: j/0/human/humanplayer.c:15709  [anchor-strings]
void __cdecl HumanPlayer_RunDelayedHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { __int16 eQTaskEvent[2]; };
    struct { char igi2_o1[4]; int v47; };
    struct { char igi2_o2[8]; struct QTask_s *v48; };
    struct { char igi2_o3[12]; int v49; };
    char igi2_extent[56];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  _DWORD *v2; // eax
  struct Client_s *ClientFromHumanQTask; // ebp
  int v4; // edi
  struct QTask_s *Window; // eax
  struct QReference_s *v6; // edi
  _DWORD *pxObject; // eax
  _DWORD *v8; // eax
  _DWORD *v9; // eax
  unsigned int ActivePlayerRemappedButton; // eax
  _DWORD *v11; // edi
  struct QTask_s *v12; // edi
  struct QTask_s *ptMiddle; // eax
  struct Weapon_s *ptNext; // ecx
  double SummedMovementSlowDown; // st7
  double v16; // st7
  struct QTask_s *ptPrev; // eax
  struct WeaponTypeItem_s *ptActiveWeapon; // eax
  BOOL v19; // eax
  double v20; // st7
  struct QTask_s *ptHead; // eax
  struct QTask_s *ptTail; // edi
  struct Game_s *v23; // ecx
  struct QReference_s *ptMicrophoneQTaskRef; // eax
  void *v25; // edi
  struct QReference_s *v26; // eax
  struct QTask_s *v27; // eax
  struct QTask_s *v28; // eax
  struct QTask_s *v29; // edi
  struct Game_s *v30; // edx
  struct QReference_s *v31; // eax
  void *v32; // edi
  struct QReference_s *v33; // eax
  char v34; // al
  bool v35; // zf
  char *v36; // eax
  bool v37; // al
  char *v38; // eax
  bool v39; // al
  char *v40; // eax
  int v41; // eax
  struct QTask_s *ptParent; // ecx
  struct QTask_s *v43; // eax
  struct QTask_s *v44; // eax
  int v45; // ecx
  struct QTask_s *ptQTaska = *(struct QTask_s * *)&ptQTask; // [esp+54h] [ebp+4h] ARGSLOT

  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER
    && (!DebugConsoleTask_ptQTaskRef || (v2 = DebugConsoleTask_ptQTaskRef->pxObject) == nullptr || !v2[81]) )
  {
    ClientFromHumanQTask = NetManager_GetClientFromHumanQTask(ptQTask);
    ptQTaska = StatusScreen_ptStatusScreenQTask;
    if ( (Keyboard_tKeyboard.anAlwaysCurrentKey[Config_GetActivePlayerRemappedButton(0x2000000000000uLL)] & 0x80u) == 0
      || dword_834DF34 )
    {
      v12 = MenuManager_ptQTask;
    }
    else
    {
      v4 = NetworkCommand_tConsoleID;
      Window = DebugConsoleTask_FindWindow(NetworkCommand_tConsoleID);
      if ( Window )
        DebugConsoleTask_SetActiveWindow(Window);
      else
        DebugConsoleTask_SplitWindow(false, v4);
      v6 = DebugConsoleTask_ptQTaskRef;
      if ( DebugConsoleTask_ptQTaskRef )
      {
        pxObject = DebugConsoleTask_ptQTaskRef->pxObject;
        if ( pxObject )
        {
          pxObject[80] = 1;
          v6 = DebugConsoleTask_ptQTaskRef;
        }
        if ( v6 )
        {
          v8 = v6->pxObject;
          if ( v8 )
          {
            v8[81] = 1;
            v6 = DebugConsoleTask_ptQTaskRef;
          }
          if ( v6 )
          {
            v9 = v6->pxObject;
            if ( v9 )
            {
              v9[76] = 1;
              v6 = DebugConsoleTask_ptQTaskRef;
            }
          }
        }
      }
      ActivePlayerRemappedButton = Config_GetActivePlayerRemappedButton(0x2000000000000uLL);
      if ( v6 )
      {
        v11 = v6->pxObject;
        if ( v11 )
          v11[155] = ActivePlayerRemappedButton;
      }
      v12 = MenuManager_ptQTask;
      if ( MenuManager_ptQTask )
      {
        ptMiddle = MenuManager_ptQTask[1].tQTaskChildren.ptMiddle;
        if ( ptMiddle != (struct QTask_s *)20 )
        {
          MenuManager_ptQTask[1].tQTaskChildren.ptHead = ptMiddle;
          v12[1].tQTaskChildren.ptMiddle = (struct QTask_s *)20;
        }
      }
      tKeyboardBuffer.isFreezeEscape = 1;
      dword_834DF34 = 1;
    }
    if ( (Keyboard_tKeyboard.anAlwaysCurrentKey[Config_GetActivePlayerRemappedButton(0x2000000000000uLL)] & 0x80u) == 0 )
      dword_834DF34 = 0;
    if ( !ClientFromHumanQTask->zTalkString[4]
      && !ClientFromHumanQTask->zTalkString[5]
      && !ptQTaska[53].ptParent
      && v12
      && v12[1].tQTaskChildren.ptMiddle == (struct QTask_s *)20 )
    {
      v12[1].tQTaskChildren.ptMiddle = v12[1].tQTaskChildren.ptHead;
    }
  }
  if ( BYTE1(ptQTask[29].tQTaskRefList.ptHead) )
  {
    HumanPlayer_HandleBreathViewOffset(ptQTask);
    if ( ptQTask[2].tQTaskChildren.ptHead && !Computer_ptComputerQTask )
      Flow_ptFlow->isDrawInterpolateEnabled = 1;
    ptNext = (struct Weapon_s *)ptQTask[33].ptNext;
    if ( Weapon_GetSummedMovementSlowDown(ptNext) >= 0.5 )
      SummedMovementSlowDown = 0.5;
    else
      SummedMovementSlowDown = Weapon_GetSummedMovementSlowDown(ptNext);
    v16 = 1.0 - SummedMovementSlowDown;
    ptPrev = ptQTask[84].ptPrev;
    *(float *)&ptQTask[81].ptNext = v16;
    if ( ptPrev )
      *(float *)&ptQTask[81].ptNext = v16 * 0.5;
    ptQTask[49].tQTaskRefList.ptMiddle = (struct QReference_s *)1065353216;
    ptActiveWeapon = ptNext->tPrivate.ptActiveWeapon;
    v19 = ptActiveWeapon
       && ptActiveWeapon->ptWeaponType
       && ptActiveWeapon->ptWeaponType->eWeaponType == WEAPONTYPE_SPECIAL;
    v20 = *(float *)&ptQTask[77].tQTaskChildren.ptMiddle;
    isInfraEnabled = v19;
    *(float *)&ptQTask[77].tQTaskChildren.ptTail = (v20 - *(float *)&ptQTask[77].tQTaskChildren.ptTail) * 0.699999988079071
                                                 + *(float *)&ptQTask[77].tQTaskChildren.ptTail;
    *(float *)&ptQTask[77].tQTaskRefList.ptMiddle = (*(float *)&ptQTask[77].tQTaskRefList.ptHead
                                                   - *(float *)&ptQTask[77].tQTaskRefList.ptMiddle)
                                                  * *(float *)&ptQTask[84].tQTaskChildren.ptHead
                                                  + *(float *)&ptQTask[77].tQTaskRefList.ptMiddle;
    HumanPlayer_UpdateVisibilityFactor(ptQTask);
    ptHead = ptQTask[85].tQTaskChildren.ptHead;
    if ( ptHead )
    {
      ptTail = ptQTask[12].tQTaskChildren.ptTail;
      if ( Game_LoadFromSlot((int)(&ptHead[-1].isInMemPool + 1)) )
      {
        v23 = Game_ptGame;
        ptQTask[12].tQTaskChildren.ptTail = (struct QTask_s *)((char *)&ptTail->ptNext + 1);
        ptMicrophoneQTaskRef = v23->ptMicrophoneQTaskRef;
        if ( ptMicrophoneQTaskRef )
        {
          v25 = ptMicrophoneQTaskRef->pxObject;
          if ( v25 )
          {
            v26 = *((struct QReference_s **)v25 + 38);
            if ( v26 )
            {
              QReference_Delete(v26, &QTask_tQTaskRefPool);
              *((_DWORD *)v25 + 38) = 0;
            }
          }
        }
      }
      ptQTask[85].tQTaskChildren.ptHead = nullptr;
    }
    v27 = ptQTask[85].tQTaskChildren.ptMiddle;
    if ( v27 )
    {
      Game_SaveToSlot((int)(&v27[-1].isInMemPool + 1));
      ptQTask[85].ptPrev = nullptr;
      ptQTask[85].tQTaskChildren.ptMiddle = nullptr;
    }
    v28 = ptQTask[85].tQTaskChildren.ptTail;
    if ( v28 )
    {
      v29 = ptQTask[12].tQTaskChildren.ptTail;
      if ( (InputPort_atInputPort[0].tInput.bEdgeButton & 0x40000000000LL) != 0 )
      {
        if ( Game_LoadFromSlot((int)(&v28[-1].isInMemPool + 1)) )
        {
          v30 = Game_ptGame;
          ptQTask[12].tQTaskChildren.ptTail = (struct QTask_s *)((char *)&v29->ptNext + 1);
          v31 = v30->ptMicrophoneQTaskRef;
          if ( v31 )
          {
            v32 = v31->pxObject;
            if ( v32 )
            {
              v33 = *((struct QReference_s **)v32 + 38);
              if ( v33 )
              {
                QReference_Delete(v33, &QTask_tQTaskRefPool);
                *((_DWORD *)v32 + 38) = 0;
              }
            }
          }
        }
      }
    }
    if ( *(float *)&ptQTask[24].tQTaskChildren.ptHead != 0.0 )
    {
      v34 = ptQTask[83].isInMemPool == 0;
      ptQTask[83].isInMemPool = v34;
      v35 = v34 == 0;
      v36 = (char *)&g_zInitialValue;
      if ( v35 )
        v36 = "not ";
      DebugConsole_printf("HumanPlayer %sinvincible.\n", v36);
    }
    if ( *(float *)&ptQTask[24].ptPrev != 0.0 )
    {
      v37 = HIBYTE(ptQTask[83].eQTaskType) == 0;
      HIBYTE(ptQTask[83].eQTaskType) = v37;
      v35 = !v37;
      v38 = "in";
      if ( v35 )
        v38 = (char *)&g_zInitialValue;
      DebugConsole_printf("HumanPlayer %svisible.\n", v38);
    }
    if ( *(float *)&ptQTask[24].tQTaskRefList.ptHead != 0.0 )
      LOBYTE(ptQTask[83].eQTaskType) ^= 1u;
    if ( *(float *)&ptQTask[24].tQTaskRefList.ptMiddle != 0.0 && ptQTask[33].ptNext )
      Weapon_ActivateAllWeapons(ptQTask[33].ptNext);
    if ( *(float *)&ptQTask[24].tQTaskChildren.ptMiddle != 0.0 )
    {
      v39 = *(&ptQTask[83].isInMemPool + 1) == 0;
      *(&ptQTask[83].isInMemPool + 1) = v39;
      v35 = !v39;
      v40 = "un";
      if ( v35 )
        v40 = (char *)&g_zInitialValue;
      DebugConsole_printf("HumanPlayer %slimited ammo.\n", v40);
      ptQTask[33].ptNext[1].tQTaskRefList.ptHead = (struct QReference_s *)*(&ptQTask[83].isInMemPool + 1);
    }
    if ( *(float *)&ptQTask[24].tQTaskChildren.ptTail != 0.0 )
    {
      DebugConsole_printf("HumanPlayer committed suicide.\n");
      *(_DWORD *)&ptQTask[30].eQTaskType |= 0x20000u;
      ptQTask[29].tQTaskChildren.ptHead = (struct QTask_s *)16;
      Human_UpdateDie((struct Human_s *)ptQTask);
    }
    if ( *(float *)&ptQTask[23].ptParent != 0.0 && *(float *)&ptQTask[17].tQTaskRefList.ptHead == 0.0 )
      Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.isHideInventory = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.isHideInventory == 0;
    if ( HumanPlayer_IsZoomedModeAllowed(ptQTask) == false )
      HumanPlayer_LeaveZoomAlternateFireMode(ptQTask);
    v41 = 100
        - (__int64)(*(float *)&ptQTask[25].tQTaskRefList.ptHead / *(float *)&ptQTask[25].tQTaskRefList.ptMiddle * 100.0);
    if ( v41 >= 0 )
    {
      if ( v41 > 100 )
        v41 = 100;
    }
    else
    {
      v41 = 0;
    }
    ptParent = ptQTask[83].ptParent;
    ptQTask[12].tQTaskRefList.ptTail = (struct QReference_s *)v41;
    ptQTask[83].ptParent = (struct QTask_s *)((char *)&ptParent->ptNext + 1);
    HumanPlayer_MaintainRunningSound((struct HumanPlayer_t *)ptQTask);
    HumanPlayer_MaintainFatigue((struct HumanPlayer_t *)ptQTask);
    HumanPlayer_MaintainCollisionZOffset((struct HumanPlayer_t *)ptQTask);
    if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
      HumanPlayer_SampleRotation((struct HumanPlayer_t *)ptQTask);
  }
  if ( !LOBYTE(ptQTask[46].tQTaskRefList.ptMiddle) )
  {
    v43 = ptQTask[46].tQTaskChildren.ptTail;
    if ( v43 )
    {
      v44 = v43->tQTaskChildren.ptHead;
      if ( v44 )
        ActionMenuScreen_RegisterActionItem(ActionMenuScreen_ptQTask, v44, nullptr, nullptr);
    }
  }
  ActionMenuScreen_Update(ActionMenuScreen_ptQTask);
  *(_DWORD *)igi2_frame.eQTaskEvent = ptQTask + 1;
  igi2_frame.v48 = nullptr;
  igi2_frame.v49 = 0;
  igi2_frame.v47 = 1;
  World_TriggerQTaskEventXyzSpecificTree(
    World_ptActiveWorld,
    QCube_eGetSectorQTaskEvent,
    igi2_frame.eQTaskEvent,
    (struct real64x3_t *)&ptQTask[1],
    0xFFFFFFFF,
    WORLD_DYNCUBETREE_STATIONARY);
  v45 = Human_eQTaskType;
  ptQTask[74].tQTaskChildren.ptTail = igi2_frame.v48;
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][v45].pfHandler)(ptQTask);
}

void __cdecl sub_4C3490(struct DynCubeObj_s *a1)
{
  struct QReference_s *ptSector; // eax
  struct World_s *ptWorld; // eax

  Symbol_Remove("HumanPlayer_Activate");
  Symbol_Remove("HumanPlayer_LockActivate");
  ptSector = (struct QReference_s *)a1[30].ptSector;
  if ( ptSector )
  {
    QReference_Delete(ptSector, &QTask_tQTaskRefPool);
    a1[30].ptSector = nullptr;
  }
  QTask_DeleteQTaskAndQTaskRefSafe(&a1[30].tQObj.tQTask.tQTaskRefList.ptHead);
  QTask_DeleteQTaskAndQTaskRefSafe(&a1[30].tQObj.tQTask.tQTaskRefList.ptMiddle);
  QTask_DeleteQTaskAndQTaskRefSafe((struct QReference_s **)&a1[30].iRenderGroup);
  QTask_DeleteQTaskAndQTaskRefSafe((struct QReference_s **)&a1[30].tQObj.vRangeX);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&a1[31].tQObj.vRealRadius);
  ptWorld = Game_ptGame->ptWorld;
  HumanPlayer_ptQTask = nullptr;
  World_RemoveDynCubeObj(ptWorld, a1);
  ((void (__cdecl *)(struct DynCubeObj_s *))QTask_aatQTaskFinalEvent[2][Human_eQTaskType].pfHandler)(a1);
  ActionMenuScreen_ClearHistory(ActionMenuScreen_ptQTask);
}

// source: j/0/human/humanplayer.c:16036  [anchor-mhash]
void __cdecl HumanPlayer_EnterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  if ( LOBYTE(ptQTask[80].tQTaskChildren.ptTail) )
    ((void (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[5][Human_eQTaskType].pfHandler)(ptQTask, 0);
}

// source: j/0/human/humanplayer.c:16062  [size]
void __cdecl HumanPlayer_ShouldersCallback(
        struct BoneDynCubeObj_s *ptBoneDynCubeObj,
        struct Bone_s *ptParent,
        struct Bone_s *ptBone)
{
  double v3; // st7
  double v4; // st6
  long double v5; // st7
  long double v6; // rt0
  long double v7; // st6
  long double v8; // st5
  long double v9; // st4
  int v10; // ecx
  bool v11; // sf
  double v12; // st7
  double v13; // st6
  double vY; // st5
  long double v15; // st3
  float v_G; // [esp+0h] [ebp-10h]
  float v_F; // [esp+4h] [ebp-Ch]
  float v_D; // [esp+8h] [ebp-8h]
  float v_A; // [esp+Ch] [ebp-4h]
  float ptBoneDynCubeObja = *(float *)&ptBoneDynCubeObj; // [esp+14h] [ebp+4h] ARGSLOT

  if ( !LOBYTE(ptBoneDynCubeObj[2].avMorphWeights[14]) )
  {
    v3 = *(float *)(LODWORD(ptBoneDynCubeObj[3].tModelObj.tOrientation.tY.vX) + 504);
    if ( v3 >= 0.0 )
      v4 = 0.24705882370471954;
    else
      v4 = 0.17777778208255768;
    v5 = v3 * v4 * 0.5;
    v6 = sin(v5);
    v7 = cos(v5);
    v_A = (ptBone->tOrientation.vY - ptBone->tOrientation.vZ) * 0.0;
    v_D = (ptBone->tOrientation.vW - ptBone->tOrientation.vX) * 0.0;
    v_F = (ptBone->tOrientation.vY + ptBone->tOrientation.vX) * v6;
    v_G = (ptBone->tOrientation.vW - ptBone->tOrientation.vZ) * v7;
    v8 = (ptBone->tOrientation.vZ + ptBone->tOrientation.vW) * v7;
    v9 = v_G + v8 + v_F;
    ptBoneDynCubeObja = ((ptBone->tOrientation.vX - ptBone->tOrientation.vY) * -v6 + v9) * 0.5;
    ptBone->tOrientation.vX = (v6 + v7) * (ptBone->tOrientation.vX + ptBone->tOrientation.vW) + ptBoneDynCubeObja - v9;
    ptBone->tOrientation.vY = (ptBone->tOrientation.vZ + ptBone->tOrientation.vY) * (v7 - v6) + ptBoneDynCubeObja - v8;
    v10 = ptBone->tOrientation.nOps + 1;
    v11 = ptBone->tOrientation.nOps - 999 < 0;
    ptBone->tOrientation.nOps = v10;
    v12 = ptBoneDynCubeObja + v_D - v_G;
    ptBone->tOrientation.vZ = v12;
    v13 = ptBoneDynCubeObja + v_A - v_F;
    ptBone->tOrientation.vW = v13;
    if ( !(v11 ^ __OFSUB__(v10, 1000) | (v10 == 1000)) )
    {
      vY = ptBone->tOrientation.vY;
      ptBone->tOrientation.nOps = 0;
      v15 = 1.0 / sqrt(v13 * v13 + v12 * v12 + ptBone->tOrientation.vX * ptBone->tOrientation.vX + vY * vY);
      ptBone->tOrientation.vX = ptBone->tOrientation.vX * v15;
      ptBone->tOrientation.vY = ptBone->tOrientation.vY * v15;
      ptBone->tOrientation.vZ = v12 * v15;
      ptBone->tOrientation.vW = v13 * v15;
    }
  }
}

// source: j/0/human/humanplayer.c:16103  [size]
void __cdecl HumanPlayer_UpperBackCallback(
        struct BoneDynCubeObj_s *ptBoneDynCubeObj,
        struct Bone_s *ptParent,
        struct Bone_s *ptBone)
{
  double v3; // st7
  double v4; // st6
  long double v5; // st7
  long double v6; // rt0
  long double v7; // st6
  long double v8; // st5
  long double v9; // st4
  int v10; // ecx
  bool v11; // sf
  double v12; // st7
  double v13; // st6
  double vY; // st5
  long double v15; // st3
  float v_G; // [esp+0h] [ebp-10h]
  float v_F; // [esp+4h] [ebp-Ch]
  float v_D; // [esp+8h] [ebp-8h]
  float v_A; // [esp+Ch] [ebp-4h]
  float ptBoneDynCubeObja = *(float *)&ptBoneDynCubeObj; // [esp+14h] [ebp+4h] ARGSLOT

  if ( !LOBYTE(ptBoneDynCubeObj[2].avMorphWeights[14]) )
  {
    v3 = *(float *)(LODWORD(ptBoneDynCubeObj[3].tModelObj.tOrientation.tY.vX) + 504);
    if ( v3 >= 0.0 )
      v4 = 0.33529412746429443;
    else
      v4 = 0.31111112236976624;
    v5 = v3 * v4 * 0.5;
    v6 = sin(v5);
    v7 = cos(v5);
    v_A = (ptBone->tOrientation.vY - ptBone->tOrientation.vZ) * 0.0;
    v_D = (ptBone->tOrientation.vW - ptBone->tOrientation.vX) * 0.0;
    v_F = (ptBone->tOrientation.vY + ptBone->tOrientation.vX) * v6;
    v_G = (ptBone->tOrientation.vW - ptBone->tOrientation.vZ) * v7;
    v8 = (ptBone->tOrientation.vZ + ptBone->tOrientation.vW) * v7;
    v9 = v_G + v8 + v_F;
    ptBoneDynCubeObja = ((ptBone->tOrientation.vX - ptBone->tOrientation.vY) * -v6 + v9) * 0.5;
    ptBone->tOrientation.vX = (v6 + v7) * (ptBone->tOrientation.vX + ptBone->tOrientation.vW) + ptBoneDynCubeObja - v9;
    ptBone->tOrientation.vY = (ptBone->tOrientation.vZ + ptBone->tOrientation.vY) * (v7 - v6) + ptBoneDynCubeObja - v8;
    v10 = ptBone->tOrientation.nOps + 1;
    v11 = ptBone->tOrientation.nOps - 999 < 0;
    ptBone->tOrientation.nOps = v10;
    v12 = ptBoneDynCubeObja + v_D - v_G;
    ptBone->tOrientation.vZ = v12;
    v13 = ptBoneDynCubeObja + v_A - v_F;
    ptBone->tOrientation.vW = v13;
    if ( !(v11 ^ __OFSUB__(v10, 1000) | (v10 == 1000)) )
    {
      vY = ptBone->tOrientation.vY;
      ptBone->tOrientation.nOps = 0;
      v15 = 1.0 / sqrt(v13 * v13 + v12 * v12 + ptBone->tOrientation.vX * ptBone->tOrientation.vX + vY * vY);
      ptBone->tOrientation.vX = ptBone->tOrientation.vX * v15;
      ptBone->tOrientation.vY = ptBone->tOrientation.vY * v15;
      ptBone->tOrientation.vZ = v12 * v15;
      ptBone->tOrientation.vW = v13 * v15;
    }
  }
}

// source: j/0/human/humanplayer.c:16144  [anchor-mhash]
void __cdecl HumanPlayer_LowerBackCallback(
        struct BoneDynCubeObj_s *ptBoneDynCubeObj,
        struct Bone_s *ptParent,
        struct Bone_s *ptBone)
{
  float vY; // eax
  double v5; // st7
  double v6; // st6
  int v7; // eax
  double v8; // st5
  double v9; // st4
  int v10; // edx
  double v11; // st7
  double v12; // st6
  double v13; // st5
  long double v14; // rt1
  double v15; // st6
  double v16; // st7
  int v17; // eax
  double vX; // st6
  long double v19; // st6
  int iBone; // eax
  double v21; // st7
  double v22; // st7
  double v23; // st6
  long double v24; // st7
  long double v25; // rt0
  long double v26; // st6
  long double v27; // st5
  long double v28; // st4
  int v29; // eax
  bool v30; // sf
  double v31; // st7
  double v32; // st6
  double v33; // st5
  long double v34; // st3
  float v_Ia; // [esp+8h] [ebp-30h]
  float v_I; // [esp+8h] [ebp-30h]
  float v_H; // [esp+Ch] [ebp-2Ch]
  float v_Ha; // [esp+Ch] [ebp-2Ch]
  float v_G; // [esp+10h] [ebp-28h]
  float v_Ga; // [esp+10h] [ebp-28h]
  float v_Gb; // [esp+10h] [ebp-28h]
  float v_F; // [esp+14h] [ebp-24h]
  float v_Fa; // [esp+14h] [ebp-24h]
  float v_Fb; // [esp+14h] [ebp-24h]
  float v_C; // [esp+18h] [ebp-20h]
  float v_Ca; // [esp+18h] [ebp-20h]
  float v_D; // [esp+1Ch] [ebp-1Ch]
  float v_Da; // [esp+1Ch] [ebp-1Ch]
  float v_Db; // [esp+1Ch] [ebp-1Ch]
  float v_A; // [esp+20h] [ebp-18h]
  float v_Aa; // [esp+20h] [ebp-18h]
  float v_Ab; // [esp+20h] [ebp-18h]
  float tQuat_12a; // [esp+30h] [ebp-8h]
  float tQuat_12; // [esp+30h] [ebp-8h]
  float ptBoneDynCubeObjb = *(float *)&ptBoneDynCubeObj; // [esp+3Ch] [ebp+4h] ARGSLOT
  float ptBoneDynCubeObjc = *(float *)&ptBoneDynCubeObj; // [esp+3Ch] [ebp+4h] ARGSLOT
  float ptBoneDynCubeObja = *(float *)&ptBoneDynCubeObj; // [esp+3Ch] [ebp+4h] ARGSLOT
  float ptBoneDynCubeObjd = *(float *)&ptBoneDynCubeObj; // [esp+3Ch] [ebp+4h] ARGSLOT

  if ( !LOBYTE(ptBoneDynCubeObj[2].avMorphWeights[14]) )
  {
    vY = ptBoneDynCubeObj[3].tModelObj.tRelativeOrientation.tY.vY;
    if ( vY != 0.0 )
    {
      v5 = -ptParent->tOrientation.vX;
      tQuat_12a = ptParent->tOrientation.vW;
      v6 = -ptParent->tOrientation.vY;
      v7 = **(_DWORD **)(LODWORD(vY) + 80);
      v8 = -ptParent->tOrientation.vZ;
      v_A = (ptBone->tOrientation.vY - ptBone->tOrientation.vZ) * (v8 - v6);
      v_C = (ptBone->tOrientation.vZ + ptBone->tOrientation.vY) * (tQuat_12a - v5);
      v_D = (ptBone->tOrientation.vW - ptBone->tOrientation.vX) * (v6 - ptParent->tOrientation.vZ);
      v_F = (ptBone->tOrientation.vX + ptBone->tOrientation.vY) * (v5 - ptParent->tOrientation.vZ);
      v_G = (ptBone->tOrientation.vW - ptBone->tOrientation.vZ) * (tQuat_12a - ptParent->tOrientation.vY);
      v9 = (ptBone->tOrientation.vZ + ptBone->tOrientation.vW) * (tQuat_12a - v6);
      v_H = v9;
      v_Ia = v9 + v_G + v_F;
      ptBoneDynCubeObjb = ((ptBone->tOrientation.vX - ptBone->tOrientation.vY) * (v8 - v5) + v_Ia) * 0.5;
      v10 = ptParent->tOrientation.nOps + ptBone->tOrientation.nOps + 1;
      v11 = (ptBone->tOrientation.vX + ptBone->tOrientation.vW) * (tQuat_12a - ptParent->tOrientation.vX)
          + ptBoneDynCubeObjb
          - v_Ia;
      v12 = ptBoneDynCubeObjb + v_C - v_H;
      v13 = ptBoneDynCubeObjb + v_D - v_G;
      tQuat_12 = ptBoneDynCubeObjb + v_A - v_F;
      if ( v10 > 1000 )
      {
        v10 = 0;
        v14 = 1.0 / sqrt(tQuat_12 * tQuat_12 + v13 * v13 + v12 * v12 + v11 * v11);
        v11 = v11 * v14;
        v12 = v12 * v14;
        v13 = v13 * v14;
        tQuat_12 = tQuat_12 * v14;
      }
      v_Ca = (*(float *)(v7 + 20) - *(float *)(v7 + 16)) * (v12 - v13);
      v_Aa = (*(float *)(v7 + 24) - *(float *)(v7 + 12)) * (v13 + v12);
      v_Da = (*(float *)(v7 + 16) + *(float *)(v7 + 20)) * (tQuat_12 - v11);
      v_Ha = (v12 + v11) * (*(float *)(v7 + 20) + *(float *)(v7 + 12));
      v_Ga = (*(float *)(v7 + 24) + *(float *)(v7 + 16)) * (tQuat_12 - v13);
      v_Fa = (*(float *)(v7 + 24) - *(float *)(v7 + 16)) * (tQuat_12 + v13);
      ptBoneDynCubeObjc = v_Fa + v_Ga + v_Ha;
      v15 = ((v11 - v12) * (*(float *)(v7 + 20) - *(float *)(v7 + 12)) + ptBoneDynCubeObjc) * 0.5;
      ptBone->tOrientation.vX = (*(float *)(v7 + 24) + *(float *)(v7 + 12)) * (tQuat_12 + v11) + v15 - ptBoneDynCubeObjc;
      ptBoneDynCubeObja = v_Aa + v15 - v_Fa;
      ptBone->tOrientation.vY = ptBoneDynCubeObja;
      v_I = v_Da + v15 - v_Ga;
      ptBone->tOrientation.vZ = v_I;
      v16 = v15 + v_Ca - v_Ha;
      ptBone->tOrientation.vW = v16;
      v17 = *(_DWORD *)(v7 + 28) + v10 + 1;
      ptBone->tOrientation.nOps = v17;
      if ( v17 > 1000 )
      {
        vX = ptBone->tOrientation.vX;
        ptBone->tOrientation.nOps = 0;
        v19 = 1.0 / sqrt(v16 * v16 + v_I * v_I + ptBoneDynCubeObja * ptBoneDynCubeObja + vX * vX);
        ptBone->tOrientation.vX = ptBone->tOrientation.vX * v19;
        ptBone->tOrientation.vY = ptBoneDynCubeObja * v19;
        ptBone->tOrientation.vZ = v_I * v19;
        ptBone->tOrientation.vW = v16 * v19;
      }
    }
    iBone = ptBoneDynCubeObj[3].tModelObj.tAttachContext.iBone;
    if ( iBone == 83 || !iBone )
      v21 = *(float *)(LODWORD(ptBoneDynCubeObj[3].tModelObj.tOrientation.tY.vX) + 476);
    else
      v21 = 0.0;
    *(float *)(LODWORD(ptBoneDynCubeObj[3].tModelObj.tOrientation.tY.vX) + 504) = (v21
                                                                                 - *(float *)(LODWORD(ptBoneDynCubeObj[3].tModelObj.tOrientation.tY.vX)
                                                                                            + 504))
                                                                                * 0.20000000298023224
                                                                                + *(float *)(LODWORD(ptBoneDynCubeObj[3].tModelObj.tOrientation.tY.vX)
                                                                                           + 504);
    v22 = *(float *)(LODWORD(ptBoneDynCubeObj[3].tModelObj.tOrientation.tY.vX) + 504);
    if ( v22 >= 0.0 )
      v23 = 0.3235294222831726;
    else
      v23 = 0.5;
    v24 = v22 * v23 * 0.5;
    v25 = sin(v24);
    v26 = cos(v24);
    v_Db = (ptBone->tOrientation.vY - ptBone->tOrientation.vZ) * 0.0;
    v_Ab = (ptBone->tOrientation.vW - ptBone->tOrientation.vX) * 0.0;
    v_Gb = (ptBone->tOrientation.vX + ptBone->tOrientation.vY) * v25;
    v_Fb = (ptBone->tOrientation.vW - ptBone->tOrientation.vZ) * v26;
    v27 = (ptBone->tOrientation.vZ + ptBone->tOrientation.vW) * v26;
    v28 = v_Fb + v27 + v_Gb;
    ptBoneDynCubeObjd = ((ptBone->tOrientation.vX - ptBone->tOrientation.vY) * -v25 + v28) * 0.5;
    ptBone->tOrientation.vX = (ptBone->tOrientation.vX + ptBone->tOrientation.vW) * (v26 + v25)
                            + ptBoneDynCubeObjd
                            - v28;
    ptBone->tOrientation.vY = (ptBone->tOrientation.vZ + ptBone->tOrientation.vY) * (v26 - v25)
                            + ptBoneDynCubeObjd
                            - v27;
    v29 = ptBone->tOrientation.nOps + 1;
    v30 = ptBone->tOrientation.nOps - 999 < 0;
    v31 = ptBoneDynCubeObjd + v_Ab - v_Fb;
    ptBone->tOrientation.nOps = v29;
    ptBone->tOrientation.vZ = v31;
    v32 = ptBoneDynCubeObjd + v_Db - v_Gb;
    ptBone->tOrientation.vW = v32;
    if ( !(v30 ^ __OFSUB__(v29, 1000) | (v29 == 1000)) )
    {
      v33 = ptBone->tOrientation.vY;
      ptBone->tOrientation.nOps = 0;
      v34 = 1.0 / sqrt(v32 * v32 + v31 * v31 + ptBone->tOrientation.vX * ptBone->tOrientation.vX + v33 * v33);
      ptBone->tOrientation.vX = ptBone->tOrientation.vX * v34;
      ptBone->tOrientation.vY = ptBone->tOrientation.vY * v34;
      ptBone->tOrientation.vZ = v31 * v34;
      ptBone->tOrientation.vW = v32 * v34;
    }
  }
}

// source: j/0/human/humanplayer.c:16215  [size]
void __cdecl HumanPlayer_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = HumanPlayer_ptParameterList;
}

// source: j/0/human/humanplayer.c:16231  [anchor-caller]
void __cdecl HumanPlayer_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptTail; // edi
  __int16 v3; // cx
  double v4; // st7
  int v5; // eax

  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][Human_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  ptTail = ptQTask[33].tQTaskChildren.ptTail;
  v3 = Attach_eAttachEvent;
  LOBYTE(ptTail[10].ptNext) = 1;
  BYTE1(ptTail[10].ptNext) = 1;
  ptTail[5].tQTaskChildren.ptTail = (struct QTask_s *)-1;
  ptTail[7].ptPrev = nullptr;
  ptTail[5].tQTaskRefList.ptHead = nullptr;
  QTask_TriggerQTaskEventParent(ptTail, v3, &ptTail[5].tQTaskChildren.ptTail);
  ModelObj_CalcRelativePosAndOrientation((struct ModelObj_s *)ptTail);
  Shadow_New(
    ptQTask[33].tQTaskChildren.ptTail,
    (struct real64x3_t *)&ptQTask[47].tQTaskChildren,
    (enum bool *)&ptQTask[47].eQTaskType,
    (enum bool *)&ptQTask[48].tQTaskChildren,
    (float *)&ptQTask[48].tQTaskChildren.ptTail,
    (struct real32x3_t *)&ptQTask[48].tQTaskRefList,
    40960.0,
    1843.199951171875,
    &Human_ptShadow->tTexInfo);
  if ( LOBYTE(ptQTask[85].ptNext) )
  {
    ptQTask[84].tQTaskRefList.ptTail = (struct QReference_s *)1056964608;
    ptQTask[84].ptParent = (struct QTask_s *)1008981770;
    *(_DWORD *)&ptQTask[84].eQTaskType = 1065353216;
  }
  if ( *(float *)&ptQTask[84].eQTaskType <= (double)*(float *)&ptQTask[84].ptParent )
    v4 = *(float *)&ptQTask[84].ptParent;
  else
    v4 = *(float *)&ptQTask[84].eQTaskType;
  v5 = *(_DWORD *)&ptQTask[2].eQTaskType;
  *(float *)&ptQTask[84].eQTaskType = v4;
  if ( v5 )
  {
    *(_DWORD *)(80 * (int)ptQTask[36].ptNext + *(_DWORD *)&ptQTask[7].eQTaskType + 76) = HumanPlayer_ShouldersCallback;
    *(_DWORD *)(80 * *(_DWORD *)&ptQTask[35].eQTaskType + *(_DWORD *)&ptQTask[7].eQTaskType + 76) = HumanPlayer_UpperBackCallback;
    *(_DWORD *)(80 * (int)ptQTask[35].ptParent + *(_DWORD *)&ptQTask[7].eQTaskType + 76) = HumanPlayer_LowerBackCallback;
  }
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[88].tQTaskRefList.ptTail, ptQTask);
}

void __cdecl sub_4C3E30(struct QTask_s *a1)
{
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptHead; // eax

  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Human_eUpdateInternalDataAfterCarryoverQTaskEvent][Human_eQTaskType].pfHandler)(a1);
  ptNext = a1[33].ptNext[5].ptNext;
  if ( ptNext )
  {
    ptHead = ptNext->tQTaskChildren.ptHead;
    if ( ptHead )
    {
      ptHead[4].tQTaskChildren.ptMiddle = (struct QTask_s *)((int)ptHead[4].tQTaskChildren.ptMiddle | 4);
      *(_DWORD *)&ptHead[3].eQTaskType = 50;
    }
  }
}

void __cdecl sub_4C3E80(struct QTask_s *a1)
{
  int v1; // edx
  int v2; // ecx

  if ( Computer_ptComputerQTask )
  {
    QTask_Delete(Computer_ptComputerQTask);
    Computer_ptComputerQTask = nullptr;
  }
  if ( BYTE1(a1[29].tQTaskRefList.ptHead) )
  {
    v1 = BoneDynCubeObj_eQTaskType;
    v2 = 511 * DynCubeObj_eDynCubeObjRemoveQTaskEvent;
    BYTE1(a1[29].tQTaskRefList.ptHead) = 0;
    ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[0][v1 + v2].pfHandler)(a1);
  }
}

// source: j/0/human/humanplayer.c:16350  [anchor-caller]
void __cdecl HumanPlayer_HumanUpdateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  if ( !LOBYTE(ptQTask[25].tQTaskChildren.ptTail) )
  {
    qmemcpy(&ptQTask[12].ptParent, &ptQTask[19].ptPrev, 0xFCu);
    qmemcpy(&ptQTask[19].ptPrev, *(void **)pxContext, 0xFCu);
  }
  HumanPlayer_Update(ptQTask);
}

// source: j/0/human/humanplayer.c:16395  [anchor-mhash]
void __cdecl HumanPlayer_HandleDamage(
        struct HumanPlayer_t *ptHumanPlayer,
        enum DamagePart_e eDamagePart,
        float vHitDamage,
        struct real32x3_t *ptDamageDirection)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v32; };
    struct { int v33; };
    struct { char igi2_o2[4]; char *apzSound[3]; };
    struct { char igi2_o3[16]; char azSound[3][32]; };
    char igi2_extent[112];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v5; // st7
  char isDead; // al
  struct RandomState_s *p_tRunRandomState; // ecx
  unsigned int v8; // eax
  unsigned int v9; // edx
  unsigned int v10; // edx
  double v11; // st7
  struct QTask_s *ptHumanViewQTask; // eax
  double v13; // st7
  int v14; // edx
  int v15; // edx
  unsigned int v16; // edx
  float *v17; // eax
  double v18; // st6
  double v19; // st5
  double v20; // st4
  double v21; // st5
  double v22; // st4
  double v23; // st5
  double v24; // st4
  double v25; // st5
  double v26; // st4
  float vY; // ecx
  float vZ; // edx
  long double v29; // st7
  long double v30; // st3
  double v31; // st6

  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER && NetManager_eMode == NETMANAGER_MODE_WARMUP )
    return;
  ptHumanPlayer->tHuman.tHumanDamage.eDamagePart = eDamagePart;
  v5 = vHitDamage * ptHumanPlayer->tHuman.tHumanDamage.atDamagePart[eDamagePart].vDamageMultiplier;
  ptHumanPlayer->tHuman.tHumanDamage.atDamagePart[eDamagePart].vDamage = v5
                                                                       + ptHumanPlayer->tHuman.tHumanDamage.atDamagePart[eDamagePart].vDamage;
  ptHumanPlayer->tHuman.tHumanDamage.vDamage = v5 + ptHumanPlayer->tHuman.tHumanDamage.vDamage;
  isDead = ptHumanPlayer->tHuman.isDead;
  ptHumanPlayer->tHuman.tState.bSignal |= 0x10000u;
  if ( !isDead )
  {
    strcpy(igi2_frame.azSound[0], "player_hit_1");
    strcpy(igi2_frame.azSound[1], "player_hit_2");
    *(_QWORD *)&igi2_frame.azSound[0][13] = 0;
    *(_QWORD *)&igi2_frame.azSound[1][13] = 0;
    *(_QWORD *)&igi2_frame.azSound[0][21] = 0;
    *(_QWORD *)&igi2_frame.azSound[1][21] = 0;
    *(_WORD *)&igi2_frame.azSound[0][29] = 0;
    *(_QWORD *)&igi2_frame.azSound[2][13] = 0;
    igi2_frame.azSound[0][31] = 0;
    *(_WORD *)&igi2_frame.azSound[1][29] = 0;
    igi2_frame.azSound[1][31] = 0;
    *(_QWORD *)&igi2_frame.azSound[2][21] = 0;
    strcpy(igi2_frame.azSound[2], "player_hit_3");
    *(_WORD *)&igi2_frame.azSound[2][29] = 0;
    igi2_frame.apzSound[0] = igi2_frame.azSound[0];
    igi2_frame.azSound[2][31] = 0;
    igi2_frame.apzSound[1] = igi2_frame.azSound[1];
    igi2_frame.apzSound[2] = igi2_frame.azSound[2];
    Human_HitSound(&ptHumanPlayer->tHuman.tBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask, igi2_frame.apzSound, 3);
  }
  p_tRunRandomState = &Game_ptGame->tRunRandomState;
  v8 = (Game_ptGame->tRunRandomState.anRandom[0] >> 7) ^ Game_ptGame->tRunRandomState.anRandom[2];
  v9 = v8 ^ Game_ptGame->tRunRandomState.anRandom[1];
  Game_ptGame->tRunRandomState.anRandom[2] = v8;
  p_tRunRandomState->anRandom[1] = v9;
  v10 = v9 + p_tRunRandomState->anRandom[0];
  p_tRunRandomState->anRandom[0] = v10;
  v11 = (double)(unsigned __int16)v10 * 0.0000152587890625;
  if ( v11 >= 0.25 )
  {
    if ( v11 > 1.0 )
      v11 = 1.0;
  }
  else
  {
    v11 = 0.25;
  }
  ptHumanViewQTask = ptHumanPlayer->tHuman.ptHumanViewQTask;
  ptHumanViewQTask[15].ptNext = (struct QTask_s *)1065353216;
  ptHumanViewQTask[15].tQTaskChildren.ptMiddle = (struct QTask_s *)1032358025;
  *(float *)&ptHumanViewQTask[15].ptPrev = 204.8000030517578 * v11;
  *(float *)&ptHumanViewQTask[15].tQTaskChildren.ptHead = v11 * 0.013089969754219055;
  if ( ptDamageDirection->vX == 0.0 && ptDamageDirection->vY == 0.0 && ptDamageDirection->vZ == 0.0 )
  {
    v13 = (Random_GetRandomNumberReal32(p_tRunRandomState) + 1.0) * 0.4;
LABEL_13:
    ptHumanPlayer->avDamageFlash[2] = v13;
    ptHumanPlayer->avDamageFlash[3] = v13;
    ptHumanPlayer->vFlashBangFlash = v13;
LABEL_43:
    *(float *)&ptHumanPlayer->nElectricDamageTimeOut = v13;
    goto LABEL_44;
  }
  v14 = (p_tRunRandomState->anRandom[0] >> 7) ^ p_tRunRandomState->anRandom[2];
  p_tRunRandomState->anRandom[2] = v14;
  v15 = v14 ^ p_tRunRandomState->anRandom[1];
  p_tRunRandomState->anRandom[1] = v15;
  v16 = v15 + p_tRunRandomState->anRandom[0];
  p_tRunRandomState->anRandom[0] = v16;
  v17 = (float *)ptHumanPlayer->tHuman.ptHumanViewQTask;
  v13 = ((double)(unsigned __int16)v16 * 0.0000152587890625 + 1.0) * 0.4;
  *(float *)igi2_frame.apzSound = v17[114] * ptDamageDirection->vZ
                     + v17[111] * ptDamageDirection->vY
                     + v17[108] * ptDamageDirection->vX;
  *(float *)&igi2_frame.apzSound[1] = v17[115] * ptDamageDirection->vZ
                         + v17[112] * ptDamageDirection->vY
                         + v17[109] * ptDamageDirection->vX;
  v18 = v17[116] * ptDamageDirection->vZ + v17[113] * ptDamageDirection->vY + v17[110] * ptDamageDirection->vX;
  v19 = *(float *)igi2_frame.apzSound;
  if ( *(float *)igi2_frame.apzSound < 0.0 )
    v19 = -v19;
  v20 = *(float *)&igi2_frame.apzSound[1];
  if ( *(float *)&igi2_frame.apzSound[1] < 0.0 )
    v20 = -v20;
  if ( v19 > v20 )
  {
    v21 = *(float *)igi2_frame.apzSound;
    if ( *(float *)igi2_frame.apzSound < 0.0 )
      v21 = -v21;
    v22 = v18;
    if ( v18 < 0.0 )
      v22 = -v18;
    if ( v21 > v22 )
    {
      if ( *(float *)igi2_frame.apzSound <= 0.0 )
      {
        ptHumanPlayer->avDamageFlash[2] = 0.25 * v13;
        ptHumanPlayer->avDamageFlash[3] = 0.25 * v13;
      }
      else
      {
        ptHumanPlayer->avDamageFlash[2] = v13;
        ptHumanPlayer->avDamageFlash[3] = v13;
        v13 = v13 * 0.25;
      }
      ptHumanPlayer->vFlashBangFlash = v13;
      goto LABEL_43;
    }
  }
  v23 = *(float *)&igi2_frame.apzSound[1];
  if ( *(float *)&igi2_frame.apzSound[1] < 0.0 )
    v23 = -v23;
  v24 = *(float *)igi2_frame.apzSound;
  if ( *(float *)igi2_frame.apzSound < 0.0 )
    v24 = -v24;
  if ( v23 < v24 )
    goto LABEL_40;
  v25 = *(float *)&igi2_frame.apzSound[1];
  if ( *(float *)&igi2_frame.apzSound[1] < 0.0 )
    v25 = -v25;
  v26 = v18;
  if ( v18 < 0.0 )
    v26 = -v18;
  if ( v25 < v26 )
  {
LABEL_40:
    if ( v18 <= 0.0 )
    {
      ptHumanPlayer->avDamageFlash[2] = v13;
      ptHumanPlayer->avDamageFlash[3] = 0.25 * v13;
      ptHumanPlayer->vFlashBangFlash = 0.25 * v13;
      goto LABEL_43;
    }
    *(float *)&igi2_frame.v33 = 0.25 * v13;
    ptHumanPlayer->avDamageFlash[2] = *(float *)&igi2_frame.v33;
    ptHumanPlayer->nElectricDamageTimeOut = igi2_frame.v33;
    ptHumanPlayer->avDamageFlash[3] = v13;
    ptHumanPlayer->vFlashBangFlash = v13;
  }
  else
  {
    if ( *(float *)&igi2_frame.apzSound[1] <= 0.0 )
      goto LABEL_13;
    *(float *)&igi2_frame.v32 = 0.25 * v13;
    ptHumanPlayer->avDamageFlash[2] = *(float *)&igi2_frame.v32;
    ptHumanPlayer->nElectricDamageTimeOut = igi2_frame.v32;
    ptHumanPlayer->avDamageFlash[3] = v13;
    ptHumanPlayer->vFlashBangFlash = v13;
  }
LABEL_44:
  if ( !ptHumanPlayer->tHuman.isDisableDeltaTranslationScale
    && (ptDamageDirection->vX != 0.0 || ptDamageDirection->vY != 0.0 || ptDamageDirection->vZ != 0.0) )
  {
    vY = ptDamageDirection->vY;
    vZ = ptDamageDirection->vZ;
    igi2_frame.apzSound[0] = (char *)LODWORD(ptDamageDirection->vX);
    v29 = *(float *)igi2_frame.apzSound;
    igi2_frame.apzSound[1] = (char *)LODWORD(vY);
    igi2_frame.apzSound[2] = (char *)LODWORD(vZ);
    if ( *(float *)igi2_frame.apzSound != 0.0 || *(float *)&igi2_frame.apzSound[1] != 0.0 || *(float *)&igi2_frame.apzSound[2] != 0.0 )
    {
      v30 = sqrt(
              v29 * v29
            + *(float *)&igi2_frame.apzSound[1] * *(float *)&igi2_frame.apzSound[1]
            + *(float *)&igi2_frame.apzSound[2] * *(float *)&igi2_frame.apzSound[2]);
      v29 = *(float *)igi2_frame.apzSound * (1.0 / v30);
      *(float *)&igi2_frame.apzSound[1] = *(float *)&igi2_frame.apzSound[1] * (1.0 / v30);
    }
    v31 = *(float *)&igi2_frame.apzSound[1];
    ptHumanPlayer->tHuman.tImpactSpeed.vZ = ptHumanPlayer->tHuman.tImpactSpeed.vZ;
    ptHumanPlayer->tHuman.tImpactSpeed.vX = v29 * 163.08148193359375 + ptHumanPlayer->tHuman.tImpactSpeed.vX;
    ptHumanPlayer->tHuman.tImpactSpeed.vY = v31 * 163.08148193359375 + ptHumanPlayer->tHuman.tImpactSpeed.vY;
  }
}

// source: j/0/human/humanplayer.c:16559  [anchor-mhash]
void __cdecl HumanPlayer_WeaponHitHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct NetManagerGameMessage_s ptGameMessage; };
    struct { char igi2_o1[8]; int v18; };
    struct { char igi2_o2[12]; enum DamagePart_e v19; };
    struct { char igi2_o3[16]; int v20; };
    struct { char igi2_o4[20]; int eNetworkID; };
    struct { char igi2_o5[24]; int ClientNetworkIDFromHumanQTask; };
    struct { char igi2_o6[32]; _BYTE v23[24]; };
    struct { char igi2_o7[56]; int v24; };
    struct { char igi2_o8[60]; int v25; };
    struct { char igi2_o9[64]; int v26; };
    char igi2_extent[76];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v4; // edi
  struct Client_s *ClientFromHumanQTask; // eax
  int Timer; // eax
  int v7; // edx
  enum DamagePart_e DamagePartFromWeaponHit; // eax
  struct QTask_s *v9; // edi
  int v10; // eax
  void *v11; // esi
  int v12; // edx
  enum GameDifficulty_e eDifficultyLevel; // eax
  double v14; // st7
  enum DamagePart_e v15; // eax
  struct QTask_s *v16; // edx
  float ptQTaska = *(float *)&ptQTask; // [esp+60h] [ebp+4h] ARGSLOT
  struct QTask_s *ptQTaskb = *(struct QTask_s * *)&ptQTask; // [esp+60h] [ebp+4h] ARGSLOT
  struct Client_s *pxContexta = *(struct Client_s * *)&pxContext; // [esp+64h] [ebp+8h] ARGSLOT
  struct real32x3_t *pxContextb = *(struct real32x3_t * *)&pxContext; // [esp+64h] [ebp+8h] ARGSLOT

  ptQTaska = *((float *)pxContext + 1);
  if ( !BYTE1(ptQTask[29].tQTaskRefList.ptHead) )
    return;
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER
    || (HumanPlayer_LeaveZoomAlternateFireMode(ptQTask), Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER) )
  {
    ptQTaskb = nullptr;
    pxContexta = NetManager_GetClientFromHumanQTask(ptQTask);
    if ( !Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
    {
      if ( BYTE1(ptQTask[29].tQTaskRefList.ptHead) )
      {
        v4 = *((struct QTask_s **)pxContext + 5);
        if ( QTask_IsQTaskTypeDerived(v4->eQTaskType, Human_eQTaskType) == false
          || (ClientFromHumanQTask = NetManager_GetClientFromHumanQTask(v4),
              (ptQTaskb = &ClientFromHumanQTask->tQTask) == nullptr)
          || ClientFromHumanQTask->eTeam != pxContexta->eTeam
          || ServerConfig_tServerConfig.isPublic )
        {
          HumanDamage_CreateFleshEnterEffect(
            (struct HumanDamage_t *)&ptQTask[25].tQTaskRefList,
            (struct real32x3_t *)((char *)pxContext + 8),
            (struct real64x3_t *)(*(_DWORD *)pxContext + 8),
            ptQTask);
          igi2_frame.ptGameMessage.eGameMessage = 1145130311;
          Timer = NetManager_GetTimer();
          v7 = *((_DWORD *)pxContext + 1);
          igi2_frame.ptGameMessage.nLocalTime = Timer;
          igi2_frame.v18 = v7;
          DamagePartFromWeaponHit = HumanDamage_GetDamagePartFromWeaponHit(
                                      (struct HumanDamage_t *)&ptQTask[25].tQTaskRefList,
                                      (struct BoneDynCubeObj_s *)ptQTask,
                                      (struct WeaponHitContext_t *)pxContext);
          v9 = *((struct QTask_s **)pxContext + 5);
          igi2_frame.v19 = DamagePartFromWeaponHit;
          LOWORD(DamagePartFromWeaponHit) = v9->eQTaskType;
          igi2_frame.eNetworkID = pxContexta->eNetworkID;
          if ( QTask_IsQTaskTypeDerived(DamagePartFromWeaponHit, Human_eQTaskType) )
            igi2_frame.ClientNetworkIDFromHumanQTask = NetManager_GetClientNetworkIDFromHumanQTask(v9);
          else
            igi2_frame.ClientNetworkIDFromHumanQTask = -1;
          v10 = *((_DWORD *)pxContext + 2);
          v11 = (void *)(*(_DWORD *)pxContext + 8);
          igi2_frame.v20 = *((_DWORD *)pxContext + 7) != 0 ? 0 : 3;
          v12 = *((_DWORD *)pxContext + 4);
          qmemcpy(igi2_frame.v23, v11, sizeof(igi2_frame.v23));
          igi2_frame.v25 = *((_DWORD *)pxContext + 3);
          igi2_frame.v24 = v10;
          igi2_frame.v26 = v12;
          NetManager_SendGameMessage(0, 0, NETWORKQUEUE_GUARANTEED, &igi2_frame.ptGameMessage, 0x48u);
          if ( QTask_IsQTaskTypeDerived(*(_WORD *)(*((_DWORD *)pxContext + 5) + 36), Human_eQTaskType) )
            NetManager_SendGameMessage((int)ptQTaskb[1].ptNext, 0, NETWORKQUEUE_GUARANTEED, &igi2_frame.ptGameMessage, 0x48u);
        }
      }
    }
    return;
  }
  if ( 2752 * Config_tConfig.iActiveProfile == -7392072 )
    return;
  eDifficultyLevel = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eDifficultyLevel;
  if ( eDifficultyLevel )
  {
    if ( eDifficultyLevel != GAMEDIFFICULTY_3 )
      goto LABEL_21;
    v14 = ptQTaska * 1.25;
  }
  else
  {
    v14 = ptQTaska * 0.75;
  }
  ptQTaska = v14;
LABEL_21:
  pxContextb = (struct real32x3_t *)((char *)pxContext + 8);
  v15 = HumanDamage_GetDamagePartFromWeaponHit(
          (struct HumanDamage_t *)&ptQTask[25].tQTaskRefList,
          (struct BoneDynCubeObj_s *)ptQTask,
          (struct WeaponHitContext_t *)pxContext);
  HumanPlayer_HandleDamage((struct HumanPlayer_t *)ptQTask, v15, ptQTaska, (struct real32x3_t *)((char *)pxContext + 8));
  if ( *(float *)&ptQTask[25].tQTaskRefList.ptHead >= (double)*(float *)&ptQTask[25].tQTaskRefList.ptMiddle
    && !ptQTask[86].tQTaskRefList.ptMiddle )
  {
    v16 = *((struct QTask_s **)pxContext + 5);
    if ( v16 )
    {
      if ( QTask_IsQTaskTypeDerived(v16->eQTaskType, ShadowVolume_nShadow) )
        ptQTask[86].tQTaskRefList.ptMiddle = QTask_NewQTaskRef(v16);
    }
  }
  HumanDamage_CreateFleshEnterEffect(
    (struct HumanDamage_t *)&ptQTask[25].tQTaskRefList,
    pxContextb,
    (struct real64x3_t *)(*(_DWORD *)pxContext + 8),
    ptQTask);
}

// source: j/0/human/humanplayer.c:16736  [anchor-mhash]
void __cdecl HumanPlayer_ExplosionHitHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptExplosionHitContext; };
    struct { char igi2_o1[24]; double v17[3]; };
    struct { char igi2_o2[48]; _BYTE v18[29]; };
    struct { char igi2_o3[77]; __int16 v19; };
    struct { char igi2_o4[79]; char v20; };
    struct { char igi2_o5[80]; _BYTE v21[29]; };
    struct { char igi2_o6[109]; __int16 v22; };
    struct { char igi2_o7[111]; char v23; };
    struct { char igi2_o8[112]; _BYTE v24[29]; };
    struct { char igi2_o9[141]; __int16 v25; };
    struct { char igi2_o10[143]; char v26; };
    char igi2_extent[148];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v2; // st7
  struct Client_s *ClientFromHumanQTask; // ebx
  struct QTask_s *v4; // edi
  int Timer; // eax
  struct QTask_s *v6; // edi
  int eNetworkID; // eax
  unsigned __int16 v8; // si
  struct QTask_s *ptTail; // edx
  double *v10; // eax
  double v11; // st6
  double v12; // st5
  long double v13; // st6
  long double v14; // st6
  struct RandomState_s *p_tRunRandomState; // esi

  if ( !BYTE1(ptQTask[29].tQTaskRefList.ptHead) )
    return;
  ptQTask[29].tQTaskChildren.ptHead = (struct QTask_s *)13;
  igi2_frame.ptExplosionHitContext = (sqrt(
                             *(float *)&ptQTask[7].tQTaskChildren.ptTail * *(float *)&ptQTask[7].tQTaskChildren.ptTail
                           + *(float *)&ptQTask[7].tQTaskRefList.ptHead * *(float *)&ptQTask[7].tQTaskRefList.ptHead
                           + *(float *)&ptQTask[7].tQTaskRefList.ptMiddle * *(float *)&ptQTask[7].tQTaskRefList.ptMiddle)
                         + *(float *)&ptQTask[8].ptNext)
                        * 0.3333333432674408;
  v2 = GameFunctions_ResolveExplosionHit(
         (struct ExplosionHitContext_t *)pxContext,
         ptQTask,
         (struct real64x3_t *)&ptQTask[1],
         igi2_frame.ptExplosionHitContext,
         true);
  *(float *)igi2_frame.v17 = v2;
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER && v2 > 0.0 )
  {
    ClientFromHumanQTask = NetManager_GetClientFromHumanQTask(ptQTask);
    if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
      return;
    v4 = *((struct QTask_s **)pxContext + 1);
    if ( v4 && QTask_IsQTaskTypeDerived(v4->eQTaskType, Human_eQTaskType) )
      NetManager_GetClientFromHumanQTask(v4);
    *(_DWORD *)igi2_frame.v18 = 1145130311;
    Timer = NetManager_GetTimer();
    v6 = *((struct QTask_s **)pxContext + 1);
    *(_DWORD *)&igi2_frame.v18[4] = Timer;
    eNetworkID = ClientFromHumanQTask->eNetworkID;
    *(_DWORD *)&igi2_frame.v18[8] = LODWORD(igi2_frame.v17[0]);
    *(_DWORD *)&igi2_frame.v18[12] = 13;
    *(_DWORD *)&igi2_frame.v18[20] = eNetworkID;
    if ( v6 && QTask_IsQTaskTypeDerived(v6->eQTaskType, Human_eQTaskType) )
      *(_DWORD *)&igi2_frame.v18[24] = NetManager_GetClientNetworkIDFromHumanQTask(v6);
    else
      *(_DWORD *)&igi2_frame.v18[24] = -1;
    v8 = *((_WORD *)pxContext + 4);
    if ( QTask_IsQTaskTypeDerived(v8, Mine_eQTaskType) )
      *(_DWORD *)&igi2_frame.v18[16] = 4;
    else
      *(_DWORD *)&igi2_frame.v18[16] = QTask_IsQTaskTypeDerived(v8, MineField_eQTaskType) != false ? 5 : 1;
    NetManager_SendGameMessage(0, 0, NETWORKQUEUE_GUARANTEED, (struct NetManagerGameMessage_s *)igi2_frame.v18, 0x48u);
    v2 = *(float *)igi2_frame.v17;
  }
  else
  {
    if ( 2752 * Config_tConfig.iActiveProfile == -7392072 )
      return;
    if ( v2 != 0.0 )
    {
      v2 = v2 * *(float *)&ptQTask[28].tQTaskRefList.ptHead;
      if ( Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eDifficultyLevel )
      {
        if ( Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eDifficultyLevel == GAMEDIFFICULTY_3 )
          v2 = v2 * 1.25;
      }
      else
      {
        v2 = v2 * 0.75;
      }
      *(float *)&ptQTask[28].tQTaskChildren.ptTail = v2 + *(float *)&ptQTask[28].tQTaskChildren.ptTail;
      *(float *)&ptQTask[25].tQTaskRefList.ptHead = v2 + *(float *)&ptQTask[25].tQTaskRefList.ptHead;
    }
  }
  ptTail = ptQTask[33].tQTaskChildren.ptTail;
  qmemcpy(igi2_frame.v17, &ptTail[10].tQTaskChildren, sizeof(igi2_frame.v17));
  v10 = *((double **)pxContext + 3);
  v11 = igi2_frame.v17[0] - *v10;
  v12 = igi2_frame.v17[1] - v10[1];
  igi2_frame.v17[0] = igi2_frame.v17[2] - v10[2];
  v13 = sqrt(v12 * v12 + igi2_frame.v17[0] * igi2_frame.v17[0] + v11 * v11) - *((float *)pxContext + 5) * 3.0;
  if ( v13 >= 0.0 )
  {
    v14 = 1.0 - v13 / (*((float *)pxContext + 5) * 6.0);
    if ( v14 <= 0.0 )
      goto LABEL_27;
  }
  else
  {
    v14 = 1.0;
  }
  LODWORD(igi2_frame.v17[0]) = *((_DWORD *)pxContext + 7);
  ptTail[15].ptNext = (struct QTask_s *)1065353216;
  *(float *)&ptTail[15].ptPrev = 204.8000030517578 * v14;
  *(float *)&ptTail[15].tQTaskChildren.ptHead = v14 * 0.013089969754219055;
  *(float *)&ptTail[15].tQTaskChildren.ptMiddle = 1.0 / (double)SLODWORD(igi2_frame.v17[0]);
LABEL_27:
  if ( v2 != 0.0 )
  {
    if ( !LOBYTE(ptQTask[29].tQTaskRefList.ptHead) )
    {
      strcpy(igi2_frame.v18, "gv_69_03");
      memset(&igi2_frame.v18[9], 0, 20);
      strcpy(igi2_frame.v21, "gv_70_03");
      strcpy(igi2_frame.v24, "gv_71_03");
      memset(&igi2_frame.v21[9], 0, 20);
      memset(&igi2_frame.v24[9], 0, 20);
      igi2_frame.v19 = 0;
      igi2_frame.v20 = 0;
      igi2_frame.v22 = 0;
      igi2_frame.v23 = 0;
      igi2_frame.v25 = 0;
      LODWORD(igi2_frame.v17[0]) = igi2_frame.v18;
      igi2_frame.v26 = 0;
      HIDWORD(igi2_frame.v17[0]) = igi2_frame.v21;
      LODWORD(igi2_frame.v17[1]) = igi2_frame.v24;
      Human_HitSound(ptQTask, (char **)igi2_frame.v17, 3);
    }
    p_tRunRandomState = &Game_ptGame->tRunRandomState;
    *(float *)&ptQTask[79].ptParent = (Random_GetRandomNumberReal32(&Game_ptGame->tRunRandomState) + 1.0) * 0.4;
    *(float *)&ptQTask[79].eQTaskType = (Random_GetRandomNumberReal32(p_tRunRandomState) + 1.0) * 0.4;
    *(float *)&ptQTask[80].ptNext = (Random_GetRandomNumberReal32(p_tRunRandomState) + 1.0) * 0.4;
    *(float *)&ptQTask[80].ptPrev = (Random_GetRandomNumberReal32(p_tRunRandomState) + 1.0) * 0.4;
  }
}

void __cdecl sub_4C4BF0(struct QTask_s *a1, void *a2)
{
  ((void (__cdecl *)())QTask_aatQTaskFinalEvent[GunPickup_eGunPickupQTaskEvent][Human_eQTaskType].pfHandler)(a1, a2);
}

// source: j/0/human/humanplayer.c:17019  [anchor-strings]
void __cdecl HumanPlayer_CloseCombatDamageHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real64x3_t tDelta; };
    struct { char igi2_o1[24]; char azSound[3][32]; };
    struct { char igi2_o2[120]; struct real64x3_t Real64x3_Rotate_tTemp; };
    char igi2_extent[148];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int *v2; // ecx
  double *v3; // eax
  int v4; // eax
  int v5; // ecx
  double v6; // st7
  struct Game_s *v7; // eax
  unsigned int v8; // ecx
  unsigned int v9; // esi
  unsigned int v10; // edx
  struct RandomState_s *p_tRunRandomState; // esi
  double RandomNumberReal32; // st7
  struct QTask_s *ptTail; // eax

  if ( BYTE1(ptQTask[29].tQTaskRefList.ptHead)
    && (Game_eGameMode == GAME_GAMEMODE_SINGLEPLAYER || Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle) )
  {
    v2 = (int *)(2752 * Config_tConfig.iActiveProfile + 7392072);
    if ( 2752 * Config_tConfig.iActiveProfile != -7392072 )
    {
      v3 = *((double **)pxContext + 1);
      igi2_frame.Real64x3_Rotate_tTemp.vX = (*(float *)&ptQTask[3].tQTaskChildren.ptMiddle + *(float *)&ptQTask[3].ptPrev) * 0.0
                               + *(float *)&ptQTask[3].tQTaskChildren.ptHead * 4096.0;
      igi2_frame.Real64x3_Rotate_tTemp.vY = (*(float *)&ptQTask[3].tQTaskRefList.ptMiddle
                                + *(float *)&ptQTask[3].tQTaskChildren.ptTail)
                               * 0.0
                               + *(float *)&ptQTask[3].tQTaskRefList.ptHead * 4096.0;
      igi2_frame.Real64x3_Rotate_tTemp.vZ = (*(float *)&ptQTask[3].eQTaskType + *(float *)&ptQTask[3].tQTaskRefList.ptTail) * 0.0
                               + *(float *)&ptQTask[3].ptParent * 4096.0;
      igi2_frame.tDelta.vX = *(double *)&ptQTask[1].ptNext - v3[5];
      igi2_frame.tDelta.vY = *(double *)&ptQTask[1].tQTaskChildren.ptHead - v3[6];
      igi2_frame.tDelta.vZ = *(double *)&ptQTask[1].tQTaskChildren.ptTail - v3[7];
      Real64x3_Normalize(&igi2_frame.tDelta);
      v4 = 14;
      if ( igi2_frame.tDelta.vZ * igi2_frame.Real64x3_Rotate_tTemp.vZ
         + igi2_frame.tDelta.vY * igi2_frame.Real64x3_Rotate_tTemp.vY
         + igi2_frame.tDelta.vX * igi2_frame.Real64x3_Rotate_tTemp.vX < 0.0 )
        v4 = 13;
      ptQTask[29].tQTaskChildren.ptHead = (struct QTask_s *)v4;
      v5 = *v2;
      v6 = *((float *)&ptQTask[25].eQTaskType + 2 * v4) * *(float *)pxContext;
      if ( v5 )
      {
        if ( v5 == 2 )
          v6 = v6 * 1.25;
      }
      else
      {
        v6 = v6 * 0.75;
      }
      *((float *)&ptQTask[25].ptParent + 2 * v4) = v6 + *((float *)&ptQTask[25].ptParent + 2 * v4);
      *(float *)&ptQTask[25].tQTaskRefList.ptHead = v6 + *(float *)&ptQTask[25].tQTaskRefList.ptHead;
      if ( !LOBYTE(ptQTask[29].tQTaskRefList.ptHead) )
      {
        strcpy(igi2_frame.azSound[0], "gv_69_03");
        *(_QWORD *)&igi2_frame.azSound[0][9] = 0;
        strcpy(igi2_frame.azSound[1], "gv_70_03");
        *(_QWORD *)&igi2_frame.azSound[0][17] = 0;
        strcpy(igi2_frame.azSound[2], "gv_71_03");
        *(_QWORD *)&igi2_frame.azSound[1][9] = 0;
        *(_DWORD *)&igi2_frame.azSound[0][25] = 0;
        *(_QWORD *)&igi2_frame.azSound[2][9] = 0;
        *(_WORD *)&igi2_frame.azSound[0][29] = 0;
        *(_QWORD *)&igi2_frame.azSound[1][17] = 0;
        igi2_frame.azSound[0][31] = 0;
        *(_QWORD *)&igi2_frame.azSound[2][17] = 0;
        *(_DWORD *)&igi2_frame.azSound[1][25] = 0;
        *(_WORD *)&igi2_frame.azSound[1][29] = 0;
        *(_DWORD *)&igi2_frame.azSound[2][25] = 0;
        igi2_frame.azSound[1][31] = 0;
        *(_WORD *)&igi2_frame.azSound[2][29] = 0;
        LODWORD(igi2_frame.tDelta.vX) = igi2_frame.azSound;
        igi2_frame.azSound[2][31] = 0;
        HIDWORD(igi2_frame.tDelta.vX) = igi2_frame.azSound[1];
        LODWORD(igi2_frame.tDelta.vY) = igi2_frame.azSound[2];
        Human_HitSound(ptQTask, (char **)&igi2_frame.tDelta, 3);
        v7 = Game_ptGame;
        v8 = (Game_ptGame->tRunRandomState.anRandom[0] >> 7) ^ Game_ptGame->tRunRandomState.anRandom[2];
        v9 = v8 ^ Game_ptGame->tRunRandomState.anRandom[1];
        Game_ptGame->tRunRandomState.anRandom[2] = v8;
        v10 = v9 + v7->tRunRandomState.anRandom[0];
        LOBYTE(v8) = v9 + LOBYTE(v7->tRunRandomState.anRandom[0]);
        v7->tRunRandomState.anRandom[1] = v9;
        v7->tRunRandomState.anRandom[0] = v10;
        if ( (v8 & 1) != 0 )
          SoundSys_NewSoundFn(ptQTask[33].tQTaskChildren.ptTail, "punched_01");
        else
          SoundSys_NewSoundFn(ptQTask[33].tQTaskChildren.ptTail, "punched_02");
      }
      p_tRunRandomState = &Game_ptGame->tRunRandomState;
      RandomNumberReal32 = Random_GetRandomNumberReal32(&Game_ptGame->tRunRandomState);
      if ( RandomNumberReal32 >= 0.25 )
      {
        if ( RandomNumberReal32 > 1.0 )
          RandomNumberReal32 = 1.0;
      }
      else
      {
        RandomNumberReal32 = 0.25;
      }
      ptTail = ptQTask[33].tQTaskChildren.ptTail;
      ptTail[15].ptNext = (struct QTask_s *)1065353216;
      ptTail[15].tQTaskChildren.ptMiddle = (struct QTask_s *)1032358025;
      *(float *)&ptTail[15].ptPrev = 204.8000030517578 * RandomNumberReal32;
      *(float *)&ptTail[15].tQTaskChildren.ptHead = RandomNumberReal32 * 0.013089969754219055;
      *(float *)&ptQTask[79].ptParent = (Random_GetRandomNumberReal32(p_tRunRandomState) + 1.0) * 0.4;
      *(float *)&ptQTask[79].eQTaskType = (Random_GetRandomNumberReal32(p_tRunRandomState) + 1.0) * 0.4;
      *(float *)&ptQTask[80].ptNext = (Random_GetRandomNumberReal32(p_tRunRandomState) + 1.0) * 0.4;
      *(float *)&ptQTask[80].ptPrev = (Random_GetRandomNumberReal32(p_tRunRandomState) + 1.0) * 0.4;
    }
  }
}

// source: j/0/human/humanplayer.c:17203  [anchor-strings]
void __cdecl HumanPlayer_ElectricDamageHandler(struct QTask_s *ptQTask, void *pxContext)
{
  double vElectricFenceDamageScale; // st7
  double v3; // st7
  struct RandomState_s *p_tRunRandomState; // edi
  struct QTask_s *ptTail; // eax

  if ( BYTE1(ptQTask[29].tQTaskRefList.ptHead)
    && (Game_eGameMode == GAME_GAMEMODE_SINGLEPLAYER || Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle)
    && !ptQTask[80].tQTaskChildren.ptMiddle )
  {
    ptQTask[29].tQTaskChildren.ptHead = (struct QTask_s *)13;
    vElectricFenceDamageScale = HumanPlayer_tGeneral.vElectricFenceDamageScale;
    ptQTask[80].tQTaskChildren.ptMiddle = (struct QTask_s *)45;
    v3 = vElectricFenceDamageScale * *(float *)&ptQTask[28].tQTaskRefList.ptHead;
    p_tRunRandomState = &Game_ptGame->tRunRandomState;
    *(float *)&ptQTask[28].tQTaskChildren.ptTail = v3 + *(float *)&ptQTask[28].tQTaskChildren.ptTail;
    *(float *)&ptQTask[25].tQTaskRefList.ptHead = v3 + *(float *)&ptQTask[25].tQTaskRefList.ptHead;
    ptTail = ptQTask[33].tQTaskChildren.ptTail;
    ptTail[15].ptNext = (struct QTask_s *)1065353216;
    ptTail[15].ptPrev = (struct QTask_s *)1129106637;
    ptTail[15].tQTaskChildren.ptHead = (struct QTask_s *)1012299600;
    ptTail[15].tQTaskChildren.ptMiddle = (struct QTask_s *)1018563425;
    *(float *)&ptQTask[79].ptParent = (Random_GetRandomNumberReal32(p_tRunRandomState) + 1.0) * 0.4;
    *(float *)&ptQTask[79].eQTaskType = (Random_GetRandomNumberReal32(p_tRunRandomState) + 1.0) * 0.4;
    *(float *)&ptQTask[80].ptNext = (Random_GetRandomNumberReal32(p_tRunRandomState) + 1.0) * 0.4;
    *(float *)&ptQTask[80].ptPrev = (Random_GetRandomNumberReal32(p_tRunRandomState) + 1.0) * 0.4;
    if ( *(float *)&ptQTask[25].tQTaskRefList.ptHead < (double)*(float *)&ptQTask[25].tQTaskRefList.ptMiddle )
      SoundSys_NewSoundFn(ptQTask[33].tQTaskChildren.ptTail, "elfence_spark1");
  }
}

// source: j/0/human/humanplayer.c:17324  [anchor-mhash]
void __cdecl HumanPlayer_FlashBangHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { double vLen; };
    struct { double vLena; };
    struct { char igi2_o2[12]; struct LineOfSightOutputContext_s tLineOfSightContext; };
    struct { char igi2_o3[24]; struct AIDetectionLineOfSightContext_s tAIDetectionLineOfSightContext; };
    struct { char igi2_o4[40]; struct real64x3_t tPos; };
    struct { char igi2_o5[64]; struct real64x3_t tFlashBangPos; };
    char igi2_extent[92];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double *v3; // esi
  double v4; // st7
  double v5; // st6
  double v6; // st5
  double v7; // st7
  double v8; // st7
  float ptQTaska = *(float *)&ptQTask; // [esp+70h] [ebp+4h] ARGSLOT

  if ( BYTE1(ptQTask[29].tQTaskRefList.ptHead) )
  {
    qmemcpy(&igi2_frame.tPos, &ptQTask[33].tQTaskChildren.ptTail[10].tQTaskChildren, sizeof(igi2_frame.tPos));
    v3 = *(double **)pxContext;
    igi2_frame.vLena = *(double *)(*(_DWORD *)pxContext + 16) - igi2_frame.tPos.vZ;
    igi2_frame.vLen = sqrt(
             (*(double *)(*(_DWORD *)pxContext + 8) - igi2_frame.tPos.vY) * (*(double *)(*(_DWORD *)pxContext + 8) - igi2_frame.tPos.vY)
           + igi2_frame.vLena * igi2_frame.vLena
           + (*(double *)*(_DWORD *)pxContext - igi2_frame.tPos.vX) * (*(double *)*(_DWORD *)pxContext - igi2_frame.tPos.vX));
    if ( igi2_frame.vLen < *((float *)pxContext + 1) )
    {
      v4 = *v3 - *(double *)&ptQTask[1].ptNext;
      v5 = v3[1] - *(double *)&ptQTask[1].tQTaskChildren.ptHead;
      v6 = v3[2] - *(double *)&ptQTask[1].tQTaskChildren.ptTail;
      igi2_frame.tLineOfSightContext.vTransparency = v6 * *(float *)&ptQTask[3].tQTaskRefList.ptTail
                                        + v5 * *(float *)&ptQTask[3].tQTaskChildren.ptTail
                                        + v4 * *(float *)&ptQTask[3].ptPrev;
      *(float *)&igi2_frame.tLineOfSightContext.ptQMaterial = v6 * *(float *)&ptQTask[3].ptParent
                                                 + v5 * *(float *)&ptQTask[3].tQTaskRefList.ptHead
                                                 + v4 * *(float *)&ptQTask[3].tQTaskChildren.ptHead;
      v7 = v6 * *(float *)&ptQTask[3].eQTaskType
         + v5 * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle
         + v4 * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle;
      if ( *(float *)&igi2_frame.tLineOfSightContext.ptQMaterial > 0.0 )
      {
        qmemcpy(&igi2_frame.tFlashBangPos, v3, sizeof(igi2_frame.tFlashBangPos));
        igi2_frame.tAIDetectionLineOfSightContext.tCollisionEvaluateContext.ptQTask = ptQTask;
        igi2_frame.tAIDetectionLineOfSightContext.ptDetectorTask = ptQTask;
        igi2_frame.tAIDetectionLineOfSightContext.ptDetecteeTask = ptQTask;
        ptQTaska = 1.0
                 / sqrt(
                     igi2_frame.tLineOfSightContext.vTransparency * igi2_frame.tLineOfSightContext.vTransparency
                   + *(float *)&igi2_frame.tLineOfSightContext.ptQMaterial * *(float *)&igi2_frame.tLineOfSightContext.ptQMaterial
                   + v7 * v7)
                 * *(float *)&igi2_frame.tLineOfSightContext.ptQMaterial
                 * 5.0;
        igi2_frame.tFlashBangPos.vZ = igi2_frame.tFlashBangPos.vZ + 409.6000061035156;
        if ( World_LineOfSight(
               Game_ptGame->ptWorld,
               &igi2_frame.tFlashBangPos,
               &igi2_frame.tPos,
               AIDetection_eLineOfSightQTaskEvent,
               &igi2_frame.tAIDetectionLineOfSightContext.tCollisionEvaluateContext,
               0xFFFFFFFF,
               WORLD_DYNCUBETREE_CATEGORY_ALL,
               &igi2_frame.tLineOfSightContext) )
        {
          v8 = 1.0 - igi2_frame.vLen / *((float *)pxContext + 1);
          if ( v8 < 0.0 )
            v8 = -v8;
          *(float *)&ptQTask[80].tQTaskChildren.ptHead = ptQTaska * v8;
        }
      }
    }
  }
}

// source: j/0/human/humanplayer.c:17428  [anchor-caller]
void __cdecl HumanPlayer_NetworkDamageHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real32x3_t ptDamageDirection; };
    struct { char igi2_o1[12]; struct NetManagerGameMessage_s ptGameMessage; };
    struct { char igi2_o2[20]; int v21; };
    struct { char igi2_o3[24]; int eNetworkID; };
    struct { char igi2_o4[28]; int v23; };
    struct { char igi2_o5[32]; int v24; };
    struct { char igi2_o6[36]; int v25; };
    struct { char igi2_o7[40]; char v26; };
    char igi2_extent[48];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v2; // edi
  char v3; // al
  int v4; // eax
  enum NetManagerMode_e v5; // ebp
  char *LocalizedStringForLanguage; // eax
  struct Client_s *ClientFromNetworkID; // eax
  struct QTask_s *v8; // esi
  struct Client_s *ClientFromHumanQTask; // eax
  int v10; // edi
  struct Client_s *v11; // esi
  int v12; // eax
  int Timer; // eax
  int v14; // edx
  int v15; // ecx
  struct Human_s *v16; // eax
  int v17; // edx
  bool v18; // cc
  _DWORD *pxContexta = *(_DWORD * *)&pxContext; // [esp+4Ch] [ebp+8h] ARGSLOT

  v2 = ptQTask;
  v3 = BYTE1(ptQTask[29].tQTaskRefList.ptHead);
  memset(&igi2_frame.ptDamageDirection, 0, sizeof(igi2_frame.ptDamageDirection));
  if ( v3 )
  {
    if ( !LOBYTE(ptQTask[29].tQTaskRefList.ptHead) )
    {
      HumanPlayer_LeaveZoomAlternateFireMode(ptQTask);
      v4 = *((_DWORD *)pxContext + 3);
      pxContexta = (_DWORD *)(v4 + 8);
      HumanPlayer_HandleDamage(
        (struct HumanPlayer_t *)ptQTask,
        *(enum DamagePart_e *)(v4 + 20),
        *(float *)(v4 + 16),
        &igi2_frame.ptDamageDirection);
      Human_UpdateDie((struct Human_s *)ptQTask);
      if ( *(float *)&ptQTask[25].tQTaskRefList.ptHead >= (double)*(float *)&ptQTask[25].tQTaskRefList.ptMiddle )
      {
        if ( NetManager_eMode != NETMANAGER_MODE_COMPLETE )
        {
          v5 = NETMANAGER_MODE_DEAD;
          if ( BYTE2(Flow_ptFlow->ptNetManagerQTask[5].tQTaskChildren.ptTail) && NetManager_ForceChangeTeam() )
          {
            v5 = NETMANAGER_MODE_SELECTSKIN;
            LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                           "mp/FORCE_TEAM_CHANGE",
                                           Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                           true);
            StatusScreen_ShowMessage(LocalizedStringForLanguage, TEXTSCROLLER_COLOUR_WHITE);
            NetManager_nBodySprite = 0;
            NetManager_nFaceSprite = 0;
            NetManager_isModelSelect = true;
          }
          ClientFromNetworkID = NetManager_GetClientFromNetworkID((int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
          if ( ClientFromNetworkID )
            NetManager_eTeam = ClientFromNetworkID->eTeam;
          v2 = ptQTask;
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
                v2 = ptQTask;
              }
              v8[1].ptNext = (struct QTask_s *)996;
              v8[1].tQTaskChildren.ptMiddle = nullptr;
              break;
            default:
              break;
          }
        }
        if ( !Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
        {
          ClientFromHumanQTask = NetManager_GetClientFromHumanQTask(v2);
          v10 = pxContexta[6];
          v11 = ClientFromHumanQTask;
          if ( v10 == -1 )
          {
            igi2_frame.v25 = -1;
          }
          else
          {
            v12 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(NetManager_GetClientFromNetworkID(v10)->tReceiveTimeBuffer.nCounter
                                                    + 8)
                                        + 1320)
                            + 44);
            if ( v12 )
              igi2_frame.v25 = *(_DWORD *)(*(_DWORD *)(v12 + 16) + 148);
            else
              igi2_frame.v25 = MEMORY[0x94];
          }
          igi2_frame.ptGameMessage.eGameMessage = 1263094860;
          Timer = NetManager_GetTimer();
          v14 = pxContexta[6];
          v15 = pxContexta[3];
          igi2_frame.ptGameMessage.nLocalTime = Timer;
          igi2_frame.eNetworkID = v11->eNetworkID;
          v16 = *(struct Human_s **)(v11->tReceiveTimeBuffer.nCounter + 8);
          igi2_frame.v21 = v14;
          v17 = pxContexta[4];
          igi2_frame.v23 = v15;
          igi2_frame.v24 = v17;
          if ( Human_isInsideSpawnArea(v16) == false || (v18 = v11->tDownload.nLastHiDown <= 0, igi2_frame.v26 = 1, v18) )
            igi2_frame.v26 = 0;
          NetManager_SendGameMessage(
            0,
            (int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle,
            NETWORKQUEUE_GUARANTEED,
            &igi2_frame.ptGameMessage,
            0x20u);
        }
      }
    }
  }
}

// source: j/0/human/humanplayer.c:17527  [anchor-strings]
int __cdecl HumanPlayer_Spawn(struct HumanPlayer_t *ptHumanPlayer, int nSpawnPoint)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[20]; struct real64x3_t ptNewPos; };
    char igi2_extent[44];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Game_s *v2; // edx
  unsigned int bSignal; // eax
  struct QReference_s *ptHumanCameraQTaskRef; // eax
  struct QTask_s *pxObject; // eax
  struct QReference_s *ptDropWeaponType; // eax
  struct Node_s *ptHead; // ecx
  struct Node_s *ptNext; // eax
  struct Node_s *v11; // ecx
  struct Node_s *v12; // edx
  struct QReference_s *ptGroundQTaskRef; // eax
  DWORD PerformanceCounter; // eax
  enum NetManagerMode_e v15; // esi
  char *LocalizedStringForLanguage; // eax
  struct Client_s *ClientFromNetworkID; // eax
  struct QTask_s *v18; // edi
  struct QTask_s *ptMiddle; // edi
  char *v20; // eax
  struct Client_s *v21; // eax
  struct QTask_s *v22; // eax
  bool v23; // zf
  void (__cdecl *v24)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl *v26)(struct State_s *, struct QTask_s *); // eax
  unsigned int ptHumanPlayera = *(unsigned int *)&ptHumanPlayer; // [esp+30h] [ebp+4h] ARGSLOT

  v2 = Game_ptGame;
  bSignal = ptHumanPlayer->tHuman.tState.bSignal;
  BYTE2(ptHumanPlayer->tHuman.ptHumanViewQTask[12].tQTaskRefList.ptTail) = 0;
  ptHumanPlayera = bSignal;
  ptHumanPlayer->tHuman.eHumanCameraMode = 1;
  ptHumanCameraQTaskRef = v2->ptHumanCameraQTaskRef;
  if ( ptHumanCameraQTaskRef )
    pxObject = (struct QTask_s *)ptHumanCameraQTaskRef->pxObject;
  else
    pxObject = nullptr;
  HumanCamera_SetHumanQTask(pxObject, &ptHumanPlayer->tHuman.tBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask);
  ptDropWeaponType = (struct QReference_s *)ptHumanPlayer->ptDropWeaponType;
  ptHumanPlayer->tHuman.tSpeed.vX = 0.0;
  ptHumanPlayer->tHuman.tSpeed.vY = 0.0;
  ptHumanPlayer->tHuman.tSpeed.vZ = 0.0;
  ptHumanPlayer->tHuman.tImpactSpeed.vX = 0.0;
  ptHumanPlayer->tHuman.tImpactSpeed.vY = 0.0;
  ptHumanPlayer->tHuman.tImpactSpeed.vZ = 0.0;
  ptHumanPlayer->tHuman.tSlidingSpeed.vX = 0.0;
  ptHumanPlayer->tHuman.tSlidingSpeed.vY = 0.0;
  ptHumanPlayer->tHuman.tSlidingSpeed.vZ = 0.0;
  ptHumanPlayer->tHuman.tTotalSpeed.vX = 0.0;
  ptHumanPlayer->tHuman.tTotalSpeed.vY = 0.0;
  ptHumanPlayer->tHuman.tTotalSpeed.vZ = 0.0;
  ptHumanPlayer->tHuman.tAccumulatedSpeed.vX = 0.0;
  ptHumanPlayer->tHuman.tAccumulatedSpeed.vY = 0.0;
  ptHumanPlayer->tHuman.tAccumulatedSpeed.vZ = 0.0;
  ptHumanPlayer->tHuman.tWorldSpeed.vX = 0.0;
  ptHumanPlayer->tHuman.tWorldSpeed.vY = 0.0;
  ptHumanPlayer->tHuman.tWorldSpeed.vZ = 0.0;
  ptHumanPlayer->tHuman.tBoneCollisionData.tDeltaMovement.vY = 0.0;
  ptHumanPlayer->tHuman.tBoneCollisionData.tDeltaMovement.vZ = 0.0;
  ptHumanPlayer->tHuman.tDeathDirection.vX = 0.0;
  ptHumanPlayer->tHuman.tDeltaTranslation.vX = 0.0;
  ptHumanPlayer->tHuman.tDeltaTranslation.vY = 0.0;
  ptHumanPlayer->tHuman.tDeltaTranslation.vZ = 0.0;
  ptHumanPlayer->tHuman.isObjectCollision = 1;
  *(&ptHumanPlayer->tHuman.bAllowedStance + 2) = 0;
  ptHumanPlayer->tHuman.isDeathAnimationDone = 0;
  LOBYTE(ptHumanPlayer->nGrenadeTickTime) = 0;
  if ( ptDropWeaponType )
  {
    QReference_Delete(ptDropWeaponType, &QTask_tQTaskRefPool);
    ptHumanPlayer->ptDropWeaponType = nullptr;
  }
  ptHumanPlayer->tHuman.isRotateUpperBody = 1;
  LOBYTE(ptHumanPlayer->nChangeWeaponID) = 0;
  LOBYTE(ptHumanPlayer->tHuman.ptHumanViewQTask[12].tQTaskRefList.ptTail) = 0;
  ptHumanPlayer->tHuman.isLockOrientation = 0;
  ptHumanPlayer->nWeaponCategory = 0;
  ptHumanPlayer->nWeaponCategoryID = -1;
  ptHead = SpawnPoint_tSpawnPointList.ptHead;
  ptNext = SpawnPoint_tSpawnPointList.ptHead->ptNext;
  if ( SpawnPoint_tSpawnPointList.ptHead->ptNext )
  {
    while ( 1 )
    {
      v11 = ptHead[1].ptNext;
      if ( v11[5].ptNext == (struct Node_s *)nSpawnPoint )
        break;
      ptHead = ptNext;
      ptNext = ptNext->ptNext;
      if ( !ptNext )
        goto LABEL_9;
    }
    v12 = v11;
  }
  else
  {
LABEL_9:
    v12 = nullptr;
  }
  qmemcpy(&igi2_frame.ptNewPos, &v12[6], sizeof(igi2_frame.ptNewPos));
  if ( ptHumanPlayer != (struct HumanPlayer_t *)-1368 )
    LODWORD(ptHumanPlayer->tHuman.vIdealGamma) = v12[9].ptNext;
  igi2_frame.ptDynCubeObj = sqrt(
                   ptHumanPlayer->tHuman.tBoneDynCubeObj.tRootTranslation.vX
                 * ptHumanPlayer->tHuman.tBoneDynCubeObj.tRootTranslation.vX
                 + ptHumanPlayer->tHuman.tBoneDynCubeObj.tRootTranslation.vY
                 * ptHumanPlayer->tHuman.tBoneDynCubeObj.tRootTranslation.vY
                 + ptHumanPlayer->tHuman.tBoneDynCubeObj.tRootTranslation.vZ
                 * ptHumanPlayer->tHuman.tBoneDynCubeObj.tRootTranslation.vZ)
               + ptHumanPlayer->tHuman.tBoneDynCubeObj.vRadius;
  World_MoveDynCubeObjRadius(
    Game_ptGame->ptWorld,
    &ptHumanPlayer->tHuman.tBoneDynCubeObj.tModelObj.tDynCubeObj,
    &igi2_frame.ptNewPos,
    igi2_frame.ptDynCubeObj);
  ptGroundQTaskRef = ptHumanPlayer->tHuman.ptGroundQTaskRef;
  if ( ptGroundQTaskRef && ptGroundQTaskRef->pxObject )
  {
    QReference_Delete(ptGroundQTaskRef, &QTask_tQTaskRefPool);
    ptHumanPlayer->tHuman.ptGroundQTaskRef = nullptr;
    HIBYTE(ptHumanPlayer->tHuman.ptCoughRef) = 0;
  }
  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  LODWORD(ptHumanPlayer->tHuman.atOldPos[0].vX) = PerformanceCounter - Timer_nStartTime;
  if ( NetMission_isWarmUp )
  {
    v15 = NETMANAGER_MODE_WARMUP;
    if ( BYTE2(Flow_ptFlow->ptNetManagerQTask[5].tQTaskChildren.ptTail) && NetManager_ForceChangeTeam() )
    {
      LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                     "mp/FORCE_TEAM_CHANGE",
                                     Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                     true);
      StatusScreen_ShowMessage(LocalizedStringForLanguage, TEXTSCROLLER_COLOUR_WHITE);
      v15 = NETMANAGER_MODE_SELECTSKIN;
      NetManager_nBodySprite = 0;
      NetManager_nFaceSprite = 0;
      NetManager_isModelSelect = true;
    }
    ClientFromNetworkID = NetManager_GetClientFromNetworkID((int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
    if ( ClientFromNetworkID )
      NetManager_eTeam = ClientFromNetworkID->eTeam;
    NetManager_eMode = v15;
    v18 = MenuManager_ptQTask;
    LOBYTE(MenuManager_ptQTask[243].eQTaskType) = 1;
    switch ( v15 )
    {
      case NETMANAGER_MODE_SELECTSKIN:
        if ( LOBYTE(HumanPlayer_ptQTask[29].tQTaskRefList.ptHead) )
          goto LABEL_29;
        ptMiddle = Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle;
        break;
      case NETMANAGER_MODE_WARMUP:
        goto LABEL_42;
    }
LABEL_28:
    NetManager_KillClient((int)ptMiddle);
    v18 = MenuManager_ptQTask;
LABEL_29:
    v18[1].ptNext = (struct QTask_s *)996;
    v18[1].tQTaskChildren.ptMiddle = nullptr;
  }
  else
  {
    v15 = NETMANAGER_MODE_PLAY;
    if ( !BYTE2(Flow_ptFlow->ptNetManagerQTask[5].tQTaskChildren.ptTail) )
      goto LABEL_36;
    if ( NetManager_ForceChangeTeam() )
    {
      v20 = Config_GetLocalizedStringForLanguage(
              "mp/FORCE_TEAM_CHANGE",
              Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
              true);
      StatusScreen_ShowMessage(v20, TEXTSCROLLER_COLOUR_WHITE);
      v15 = NETMANAGER_MODE_SELECTSKIN;
      NetManager_nBodySprite = 0;
      NetManager_nFaceSprite = 0;
      NetManager_isModelSelect = true;
    }
    if ( NetMission_isWarmUp && v15 == NETMANAGER_MODE_PLAY )
    {
      NetManager_eMode = NETMANAGER_MODE_WARMUP;
    }
    else
    {
LABEL_36:
      v21 = NetManager_GetClientFromNetworkID((int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
      if ( v21 )
        NetManager_eTeam = v21->eTeam;
      NetManager_eMode = v15;
    }
    v18 = MenuManager_ptQTask;
    LOBYTE(MenuManager_ptQTask[243].eQTaskType) = 1;
    switch ( v15 )
    {
      case NETMANAGER_MODE_SELECTSKIN:
        if ( LOBYTE(HumanPlayer_ptQTask[29].tQTaskRefList.ptHead) )
          goto LABEL_29;
        ptMiddle = Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle;
        goto LABEL_28;
      case NETMANAGER_MODE_PLAY:
LABEL_42:
        v22 = HumanPlayer_ptQTask;
        v23 = HumanPlayer_ptQTask == nullptr;
        LOBYTE(v18[243].eQTaskType) = 0;
        if ( !v23 && LOBYTE(v22[29].tQTaskRefList.ptHead) )
          NetManager_SetMode(2);
        if ( v15 == NETMANAGER_MODE_WARMUP )
          NetManager_eTeam = -1;
        break;
    }
  }
  ptHumanPlayer->tHuman.tState.bSignal = ptHumanPlayera & 0xFFFDFDFF;
  ptHumanPlayer->nGrenadeHeldTime = 0;
  ptHumanPlayer->ptRunningEquipmentSoundQTaskRef = nullptr;
  v24 = ptHumanPlayer->tHuman.tState.apfExitState[ptHumanPlayer->tHuman.tState.nState];
  if ( v24 )
    v24(&ptHumanPlayer->tHuman.tState, &ptHumanPlayer->tHuman.tBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask);
  apfState = ptHumanPlayer->tHuman.tState.apfState;
  ptHumanPlayer->tHuman.tState.nPreviousState = ptHumanPlayer->tHuman.tState.nState;
  ptHumanPlayer->tHuman.tState.nState = 0;
  v26 = *apfState;
  ptHumanPlayer->tHuman.tState.pfState = v26;
  return ((int (__cdecl *)(struct State_s *, struct HumanPlayer_t *))v26)(&ptHumanPlayer->tHuman.tState, ptHumanPlayer);
}

// source: j/0/human/humanplayer.c:17640  [anchor-mhash]
void __cdecl HumanPlayer_GetWeaponPrecisionHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptTail; // ecx
  DWORD PerformanceCounter; // eax
  DWORD TickCount; // eax
  double v5; // st7
  struct QTask_s *ptQTaska = *(struct QTask_s * *)&ptQTask; // [esp+Ch] [ebp+4h] ARGSLOT

  ptTail = ptQTask[33].tQTaskChildren.ptTail;
  *(float *)pxContext = *(float *)&ptQTask[77].tQTaskRefList.ptMiddle + *(float *)&ptQTask[77].tQTaskChildren.ptTail;
  *((_DWORD *)pxContext + 1) = ptTail[16].tQTaskChildren.ptHead;
  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  if ( (int)(PerformanceCounter - Timer_nStartTime - 600000) >= 0 )
  {
    if ( Timer_isPerformanceCounter )
      TickCount = Timer_GetPerformanceCounter();
    else
      TickCount = GetTickCount();
    ptQTaska = (struct QTask_s *)(TickCount - Timer_nStartTime - 600000);
  }
  else
  {
    ptQTaska = nullptr;
  }
  v5 = (double)(int)ptQTaska * 0.0000008333333333333333;
  if ( v5 >= 1.0 )
    v5 = 1.0;
  *(float *)pxContext = ((DEGRADE_PlayerAccuracy - 1.0) * v5 + 1.0) * *(float *)pxContext;
}

// source: j/0/human/humanplayer.c:17673  [anchor-callee]
void __cdecl HumanPlayer_DrawDamageFlash(struct HumanPlayer_t *ptHumanPlayer)
{
  struct QReference_s *ptHumanCameraQTaskRef; // eax
  _DWORD *pxObject; // eax
  float vWidth; // [esp+0h] [ebp-5Ch]
  float vHeight; // [esp+4h] [ebp-58h]

  ptHumanCameraQTaskRef = Game_ptGame->ptHumanCameraQTaskRef;
  if ( ptHumanCameraQTaskRef )
    pxObject = ptHumanCameraQTaskRef->pxObject;
  else
    pxObject = nullptr;
  if ( pxObject[60] == 1
    && (ptHumanPlayer->avDamageFlash[2] != 0.0
     || ptHumanPlayer->avDamageFlash[3] != 0.0
     || ptHumanPlayer->vFlashBangFlash != 0.0
     || *(float *)&ptHumanPlayer->nElectricDamageTimeOut != 0.0) )
  {
    vHeight = (float)Display_tActiveMode.nHeight;
    vWidth = (float)Display_tActiveMode.nWidth;
    QSprite_RegisterBlank4RGBAZ(
      0.0,
      0.0,
      vWidth,
      vHeight,
      255.0,
      0.0,
      0.0,
      255.0,
      0.0,
      0.0,
      255.0,
      0.0,
      0.0,
      255.0,
      0.0,
      0.0,
      ptHumanPlayer->avDamageFlash[2],
      *(float *)&ptHumanPlayer->nElectricDamageTimeOut,
      ptHumanPlayer->avDamageFlash[3],
      ptHumanPlayer->vFlashBangFlash,
      0.0,
      0x80000u,
      3);
  }
}

// source: j/0/human/humanplayer.c:17722  [anchor-callee]
void __cdecl HumanPlayer_DrawFlashbangEffect(struct HumanPlayer_t *ptHumanPlayer, int nPriority)
{
  struct QReference_s *ptHumanCameraQTaskRef; // eax
  _DWORD *pxObject; // eax
  float vWidth; // [esp+0h] [ebp-2Ch]
  float vHeight; // [esp+4h] [ebp-28h]
  float vAlpha; // [esp+20h] [ebp-Ch]

  ptHumanCameraQTaskRef = Game_ptGame->ptHumanCameraQTaskRef;
  if ( ptHumanCameraQTaskRef )
    pxObject = ptHumanCameraQTaskRef->pxObject;
  else
    pxObject = nullptr;
  if ( pxObject[60] == 1 && *(float *)&ptHumanPlayer->isDisplayPlayer != 0.0 )
  {
    vAlpha = *(float *)&ptHumanPlayer->isDisplayPlayer;
    if ( vAlpha >= 0.0 )
    {
      if ( vAlpha > 0.9900000095367432 )
        vAlpha = 0.9900000095367432;
    }
    else
    {
      vAlpha = 0.0;
    }
    vHeight = (float)Display_tActiveMode.nHeight;
    vWidth = (float)Display_tActiveMode.nWidth;
    QSprite_RegisterBlankA(0.0, 0.0, vWidth, vHeight, 255.0, 255.0, 255.0, vAlpha, 0x80000u, nPriority);
  }
}

// source: j/0/human/humanplayer.c:17770  [anchor-strings]
void __cdecl HumanPlayer_StatusDisplayHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v80; };
    struct { char igi2_o1[4]; float v81; };
    struct { char igi2_o2[8]; float vV4; };
    struct { char igi2_o3[8]; float vV4a; };
    struct { char igi2_o4[8]; float vV4b; };
    struct { char igi2_o5[8]; float vV4c; };
    struct { char igi2_o6[8]; float vV4d; };
    struct { char igi2_o7[12]; float vR1; };
    struct { char igi2_o8[12]; float vR1a; };
    struct { char igi2_o9[12]; float vR1b; };
    struct { char igi2_o10[12]; float vR1c; };
    struct { char igi2_o11[12]; float vR1d; };
    struct { char igi2_o12[12]; float vR1e; };
    struct { char igi2_o13[12]; float vR1f; };
    struct { char igi2_o14[16]; float vG1; };
    struct { char igi2_o15[16]; float vG1a; };
    struct { char igi2_o16[16]; float vG1b; };
    struct { char igi2_o17[16]; float vG1c; };
    struct { char igi2_o18[20]; float vY; };
    struct { char igi2_o19[24]; float vR; };
    struct { char igi2_o20[28]; float vG; };
    struct { char igi2_o21[56]; int vX1; };
    struct { char igi2_o22[56]; float vX1a; };
    struct { char igi2_o23[56]; int vX1b; };
    struct { char igi2_o24[56]; float vX1c; };
    struct { char igi2_o25[56]; float vX1d; };
    struct { char igi2_o26[60]; int vU1; };
    struct { char igi2_o27[60]; int vU1a; };
    struct { char igi2_o28[60]; int vU1b; };
    struct { char igi2_o29[60]; int vU1c; };
    struct { char igi2_o30[60]; struct WeaponType_s *vU1d; };
    struct { char igi2_o31[60]; float vU1e; };
    struct { char igi2_o32[60]; float vU1f; };
    struct { char igi2_o33[64]; float v113; };
    struct { char igi2_o34[64]; float v114; };
    struct { char igi2_o35[64]; float v115; };
    struct { char igi2_o36[68]; float vX; };
    struct { char igi2_o37[68]; unsigned int vXa; };
    struct { char igi2_o38[68]; float vXb; };
    struct { char igi2_o39[68]; int vXc; };
    struct { char igi2_o40[72]; float v120; };
    struct { char igi2_o41[72]; float v121; };
    struct { char igi2_o42[72]; struct QSprite_s *v122; };
    struct { char igi2_o43[72]; float v123; };
    struct { char igi2_o44[76]; int vY1; };
    struct { char igi2_o45[76]; int vY1a; };
    struct { char igi2_o46[76]; float vY1b; };
    struct { char igi2_o47[76]; float vY1c; };
    struct { char igi2_o48[76]; float vY1d; };
    struct { char igi2_o49[84]; float v129; };
    struct { char igi2_o50[84]; int v130; };
    struct { char igi2_o51[88]; float ptQSprite; };
    struct { char igi2_o52[88]; float ptQSpritea; };
    struct { char igi2_o53[88]; int ptQSpriteb; };
    struct { char igi2_o54[88]; int ptQSpritec; };
    struct { char igi2_o55[92]; _DWORD *pxObject; };
    struct { char igi2_o56[92]; int v136; };
    struct { char igi2_o57[96]; struct WeaponType_s *vX3; };
    struct { char igi2_o58[96]; float vX3a; };
    struct { char igi2_o59[96]; float vX3b; };
    struct { char igi2_o60[96]; float vX3c; };
    struct { char igi2_o61[100]; float vHeight; };
    struct { char igi2_o62[100]; float vHeighta; };
    struct { char igi2_o63[104]; _BYTE v143[20]; };
    struct { char igi2_o64[124]; int nWidth; };
    struct { char igi2_o65[128]; struct WeaponGetFireTypeAmmoContext_s nFireType; };
    struct { char igi2_o66[148]; struct WeaponGetFireTypeAmmoContext_s ptAmmoContext; };
    struct { char igi2_o67[168]; int v147; };
    struct { char igi2_o68[172]; int v148; };
    struct { char igi2_o69[176]; int v149; };
    struct { char igi2_o70[180]; int v150; };
    struct { char igi2_o71[184]; int v151; };
    struct { char igi2_o72[188]; int v152; };
    struct { char igi2_o73[192]; int v153; };
    struct { char igi2_o74[196]; int v154; };
    struct { char igi2_o75[200]; int nHeight; };
    struct { char igi2_o76[204]; int v156; };
    struct { char igi2_o77[208]; int v157; };
    struct { char igi2_o78[212]; int v158; };
    struct { char igi2_o79[216]; int v159; };
    struct { char igi2_o80[220]; struct StaticTilemap_s *ptQText; };
    struct { char igi2_o81[224]; _DWORD v161[5]; };
    struct { char igi2_o82[244]; _DWORD v162[40]; };
    struct { char igi2_o83[404]; char Buffer[32]; };
    struct { char igi2_o84[436]; char zResourceName[260]; };
    char igi2_extent[696];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // ebp
  struct QReference_s *ptHumanCameraQTaskRef; // eax
  struct QTask_s *v4; // ebx
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptParent; // edi
  struct WeaponType_s *WeaponTypeFromID; // eax
  struct QTask_s *v8; // esi
  struct WeaponTypeItem_s *WeaponTypeItemFromWeaponType; // eax
  struct QTask_s *v10; // esi
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptHead; // eax
  BOOL v13; // ecx
  struct QTask_s *v14; // edx
  int v15; // eax
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // eax
  enum NetManagerMode_e v17; // esi
  double v18; // st7
  int v19; // ecx
  double v20; // st4
  double v21; // st7
  double v22; // st7
  struct QTask_s *v23; // eax
  double v24; // st7
  double v25; // st6
  double v26; // st5
  double v27; // st7
  double v28; // st6
  float *v29; // edx
  int v30; // ecx
  int v31; // esi
  __int16 *v32; // eax
  float *v33; // ecx
  int v34; // esi
  float *v35; // edx
  int v36; // ecx
  __int16 *v37; // eax
  float *v38; // ecx
  struct QSprite_s *v39; // ecx
  struct QReference_s *ptTail; // eax
  void (__cdecl *v41)(struct QReference_s *, void *); // ecx
  struct QTask_s *v42; // edx
  struct QTask_s *v43; // eax
  unsigned int v44; // edi
  struct QTask_s *v45; // eax
  int v46; // ebx
  struct QTask_s *v47; // eax
  int v48; // eax
  int *v49; // ecx
  int v50; // ecx
  int *v51; // eax
  _DWORD *v52; // edx
  _DWORD *v53; // ebx
  unsigned int v54; // ecx
  int v55; // ebx
  struct Weapon_s *v56; // edx
  struct WeaponTypeItem_s *v57; // esi
  struct WeaponTypeItem_s *v58; // eax
  int v59; // eax
  struct WeaponType_s *ptWeaponType; // edi
  float *v61; // edi
  int v62; // ecx
  int v63; // esi
  __int16 *v64; // edx
  float *v65; // eax
  int v66; // eax
  int v67; // eax
  char *zName; // edi
  char *LocalizedStringForLanguage; // esi
  __int16 **v70; // eax
  __int16 *v71; // edx
  void *v72; // edi
  unsigned int v73; // ebx
  struct QTilemap_s *v74; // ebx
  unsigned __int8 v75; // cl
  int v76; // eax
  int v77; // edi
  int v78; // eax
  struct QSprite_s *v79; // eax

  v2 = *(_DWORD *)pxContext;
  ptHumanCameraQTaskRef = Game_ptGame->ptHumanCameraQTaskRef;
  if ( ptHumanCameraQTaskRef )
    igi2_frame.pxObject = ptHumanCameraQTaskRef->pxObject;
  else
    igi2_frame.pxObject = nullptr;
  v4 = ptQTask;
  igi2_frame.nWidth = Display_tActiveMode.nWidth;
  ptNext = ptQTask[33].ptNext;
  igi2_frame.nHeight = Display_tActiveMode.nHeight;
  if ( ptNext )
  {
    ptParent = ptQTask[76].ptParent;
    if ( ptParent != (struct QTask_s *)-1 )
    {
      WeaponTypeFromID = WeaponType_GetWeaponTypeFromID((int)ptParent);
      if ( WeaponTypeFromID )
      {
        v8 = ptQTask[33].ptNext;
        WeaponTypeItemFromWeaponType = Weapon_GetWeaponTypeItemFromWeaponType(v8, WeaponTypeFromID->zWeaponScriptID);
        if ( WeaponTypeItemFromWeaponType )
          v8[1].ptNext = (struct QTask_s *)WeaponTypeItemFromWeaponType;
      }
    }
  }
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[StatusScreen_eStatusDisplayQTaskEvent][Human_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  v10 = ptQTask[33].ptNext;
  if ( v10 )
  {
    ptPrev = v10[5].ptPrev;
    if ( ptPrev )
    {
      ptHead = ptPrev->tQTaskChildren.ptHead;
      if ( ptHead )
      {
        v13 = igi2_frame.pxObject[60] == 1;
        if ( ptQTask[75].ptPrev == (struct QTask_s *)5 )
          v13 = 0;
        v14 = ptQTask[31].ptPrev;
        if ( v14 == (struct QTask_s *)19 || v14 == (struct QTask_s *)20 || v14 == (struct QTask_s *)21 )
          v13 = 0;
        ptHead[2].ptParent = (struct QTask_s *)v13;
      }
    }
  }
  if ( v10 )
  {
    if ( LOBYTE(ptQTask[50].ptNext) )
    {
      v15 = igi2_frame.pxObject[60];
      if ( v15 == 1 || v15 == 6 )
      {
        if ( v10[4].ptNext == (struct QTask_s *)2 )
          HumanPlayer_DrawFlashbangEffect((struct HumanPlayer_t *)ptQTask, 1);
        pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[StatusScreen_eStatusDisplayQTaskEvent][v10->eQTaskType].pfHandler;
        if ( pfHandler )
          pfHandler(v10, pxContext);
        if ( v10[4].ptNext == (struct QTask_s *)2 )
          return;
      }
    }
  }
  if ( Game_eGameMode == GAME_GAMEMODE_SINGLEPLAYER )
    goto LABEL_34;
  v17 = NetManager_eMode;
  if ( NetManager_eMode == NETMANAGER_MODE_PLAY || NetManager_eMode == NETMANAGER_MODE_RADIO )
    goto LABEL_34;
  if ( NetManager_eMode == NETMANAGER_MODE_SHOP && !LOBYTE(ptQTask[29].tQTaskRefList.ptHead) )
  {
    v4 = ptQTask;
LABEL_34:
    v18 = 1.0 - *(float *)&v4[25].tQTaskRefList.ptHead / *(float *)&v4[25].tQTaskRefList.ptMiddle;
    igi2_frame.v129 = v18;
    if ( v18 < 0.0 )
      igi2_frame.v129 = 0.0;
    v19 = *(_DWORD *)(v2 + 276);
    igi2_frame.ptQSprite = 40.0 - (double)*(__int16 *)(v19 + 36 * *(unsigned __int16 *)(v2 + 288) + 12) * 0.5;
    igi2_frame.vX = (double)Display_tActiveMode.nHeight
       - 50.0
       - (double)*(__int16 *)(v19 + 36 * *(unsigned __int16 *)(v2 + 288) + 14) * 0.5;
    QSprite_Register((struct QSprite_s *)(v2 + 268), igi2_frame.ptQSprite, igi2_frame.vX, 51.20000076293945, 76.80000305175781, 128.0, 0, 0, 3);
    if ( igi2_frame.v129 != 0.0 )
    {
      v20 = (double)Display_tActiveMode.nHeight - 50.0 - 2.0;
      igi2_frame.v120 = 38.0 - (double)*(__int16 *)(*(_DWORD *)(v2 + 300) + 36 * *(unsigned __int16 *)(v2 + 312) + 12) * 0.5;
      igi2_frame.vY1b = (double)*(__int16 *)(*(_DWORD *)(v2 + 300) + 36 * *(unsigned __int16 *)(v2 + 312) + 12) * 0.5 + 38.0;
      igi2_frame.vX3a = (double)*(__int16 *)(*(_DWORD *)(v2 + 300) + 36 * *(unsigned __int16 *)(v2 + 312) + 14) * 0.5 + v20;
      igi2_frame.vU1e = 1.0 - igi2_frame.v129;
      igi2_frame.vX1a = v20
           - (double)*(__int16 *)(*(_DWORD *)(v2 + 300) + 36 * *(unsigned __int16 *)(v2 + 312) + 14) * 0.5
           + (double)*(__int16 *)(*(_DWORD *)(v2 + 300) + 36 * *(unsigned __int16 *)(v2 + 312) + 14) * igi2_frame.vU1e;
      igi2_frame.vG1 = (igi2_frame.v129 * 0.699999988079071 + 0.20000000298023224) * 128.0;
      igi2_frame.vR1 = (igi2_frame.v129 * 0.2200000137090683 + 0.20000000298023224) * 128.0;
      igi2_frame.vV4 = (0.800000011920929 - igi2_frame.v129 * 0.5199999809265137) * 128.0;
      QSprite_Register4AZUV(
        (struct QSprite_s *)(v2 + 292),
        igi2_frame.v120,
        igi2_frame.vX1a,
        igi2_frame.vY1b,
        igi2_frame.vX1a,
        igi2_frame.v120,
        igi2_frame.vX3a,
        igi2_frame.vY1b,
        igi2_frame.vX3a,
        0.0,
        igi2_frame.vU1e,
        1.0,
        igi2_frame.vU1e,
        0.0,
        1.0,
        1.0,
        1.0,
        igi2_frame.vV4,
        igi2_frame.vR1,
        igi2_frame.vG1,
        1.0,
        0.0,
        0,
        0x80000u,
        3);
    }
    v21 = *(float *)&ptQTask[49].tQTaskRefList.ptMiddle - 0.5;
    if ( v21 >= 0.0 )
    {
      if ( v21 > 0.5 )
        v21 = 0.5;
    }
    else
    {
      v21 = 0.0;
    }
    v22 = v21 + v21;
    v23 = ptQTask[12].ptNext;
    igi2_frame.vX1b = *(__int16 *)(*(_DWORD *)(v2 + 276) + 36 * *(unsigned __int16 *)(v2 + 288) + 12);
    *(float *)igi2_frame.v143 = (v22 + 1.0) * 0.4000000059604645;
    *(float *)&igi2_frame.v143[4] = 0.6000000238418579 - 0.40000003576278687 * v22;
    *(float *)&igi2_frame.v143[8] = 1.0 - v22 * 0.800000011920929;
    igi2_frame.v114 = (double)igi2_frame.vX1b + igi2_frame.ptQSprite + 5.0;
    if ( v23 )
      v24 = 0.5;
    else
      v24 = 1.0;
    if ( v23 )
      v25 = 0.4000000059604645;
    else
      v25 = 0.6000000238418579;
    if ( v23 )
      v26 = 0.800000011920929;
    else
      v26 = 0.4000000059604645;
    igi2_frame.vG = v24 * 128.0;
    igi2_frame.vR = v25 * 128.0;
    igi2_frame.vY = v26 * 128.0;
    igi2_frame.vR1a = igi2_frame.v114 + 10.0;
    QSprite_Register((struct QSprite_s *)(v2 + 364), igi2_frame.vR1a, igi2_frame.vX, igi2_frame.vY, igi2_frame.vR, igi2_frame.vG, 0, 0, 3);
    igi2_frame.v121 = igi2_frame.vX + 10.0;
    QSprite_Register((struct QSprite_s *)(v2 + 316), igi2_frame.v114, igi2_frame.v121, 51.20000076293945, 76.80000305175781, 128.0, 0, 0, 3);
    v27 = igi2_frame.v114 + 7.0;
    igi2_frame.v113 = v27;
    v28 = (double)*(__int16 *)(*(_DWORD *)(v2 + 348) + 36 * *(unsigned __int16 *)(v2 + 360) + 14);
    igi2_frame.vU1f = 1.0 - *(float *)&ptQTask[49].tQTaskRefList.ptMiddle;
    igi2_frame.ptQSpritea = igi2_frame.v121 + v28;
    igi2_frame.vX1c = (double)*(__int16 *)(*(_DWORD *)(v2 + 348) + 36 * *(unsigned __int16 *)(v2 + 360) + 12) + igi2_frame.v113;
    igi2_frame.vX3b = igi2_frame.vU1f * v28 + igi2_frame.v121;
    igi2_frame.vG1a = *(float *)&igi2_frame.v143[8] * 128.0;
    igi2_frame.vR1b = *(float *)&igi2_frame.v143[4] * 128.0;
    igi2_frame.vV4a = *(float *)igi2_frame.v143 * 128.0;
    QSprite_Register4AZUV(
      (struct QSprite_s *)(v2 + 340),
      igi2_frame.v113,
      igi2_frame.vX3b,
      igi2_frame.vX1c,
      igi2_frame.vX3b,
      igi2_frame.v113,
      igi2_frame.ptQSpritea,
      igi2_frame.vX1c,
      igi2_frame.ptQSpritea,
      0.0,
      igi2_frame.vU1f,
      1.0,
      igi2_frame.vU1f,
      0.0,
      1.0,
      1.0,
      1.0,
      igi2_frame.vV4a,
      igi2_frame.vR1b,
      igi2_frame.vG1a,
      1.0,
      0.0,
      0,
      0,
      3);
    v29 = *(float **)(v2 + 1120);
    v30 = *(__int16 *)(*(_DWORD *)v29 + 6);
    v31 = 0;
    igi2_frame.vU1 = 0;
    if ( v30 > 0 )
    {
      v32 = *(__int16 **)(*(_DWORD *)v29 + 12);
      do
      {
        if ( *v32 > v31 )
          v31 = *v32;
        ++v32;
        --v30;
      }
      while ( v30 );
      igi2_frame.vU1 = v31;
    }
    *(_QWORD *)igi2_frame.v143 = (__int64)(igi2_frame.v113 - (double)igi2_frame.vU1 - 7.0);
    v29[1] = (float)*(int *)igi2_frame.v143;
    v33 = *(float **)(v2 + 1120);
    v34 = 0;
    igi2_frame.vU1a = 0;
    *(_QWORD *)igi2_frame.v143 = (__int64)(igi2_frame.v121
                              - (double)(*(__int16 *)(*(_DWORD *)v33 + 6)
                                       * *(__int16 *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)v33 + 8) + 8)
                                                    + 36 * *(unsigned __int16 *)(*(_DWORD *)(*(_DWORD *)v33 + 8) + 20)
                                                    + 14)
                                       / 2));
    v33[2] = (float)*(int *)igi2_frame.v143;
    *(_DWORD *)(*(_DWORD *)(v2 + 1120) + 32) = 3;
    v35 = *(float **)(v2 + 1124);
    v36 = *(__int16 *)(*(_DWORD *)v35 + 6);
    if ( v36 > 0 )
    {
      v37 = *(__int16 **)(*(_DWORD *)v35 + 12);
      do
      {
        if ( *v37 > v34 )
          v34 = *v37;
        ++v37;
        --v36;
      }
      while ( v36 );
      igi2_frame.vU1a = v34;
    }
    *(_QWORD *)igi2_frame.v143 = (__int64)(igi2_frame.v113 - (double)igi2_frame.vU1a - 7.0);
    v35[1] = (float)*(int *)igi2_frame.v143;
    v38 = *(float **)(v2 + 1124);
    *(_QWORD *)igi2_frame.v143 = (__int64)(igi2_frame.ptQSpritea
                              - (double)(*(__int16 *)(*(_DWORD *)v38 + 6)
                                       * *(__int16 *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)v38 + 8) + 8)
                                                    + 36 * *(unsigned __int16 *)(*(_DWORD *)(*(_DWORD *)v38 + 8) + 20)
                                                    + 14)
                                       / 2));
    v38[2] = (float)*(int *)igi2_frame.v143;
    *(_DWORD *)(*(_DWORD *)(v2 + 1124) + 32) = 3;
    if ( ptQTask[31].ptPrev == (struct QTask_s *)57 )
    {
      v39 = (struct QSprite_s *)(v2 + 148);
    }
    else if ( *(_DWORD *)&ptQTask[32].eQTaskType == 1 )
    {
      v39 = (struct QSprite_s *)(v2 + 124);
    }
    else if ( *(_DWORD *)&ptQTask[32].eQTaskType == 2 )
    {
      v39 = (struct QSprite_s *)(v2 + 172);
    }
    else if ( BYTE1(ptQTask[50].ptNext) )
    {
      v39 = (struct QSprite_s *)(v2 + 196);
    }
    else
    {
      v39 = (struct QSprite_s *)(v2 + 220);
    }
    igi2_frame.vG1b = (double)Display_tActiveMode.nHeight - 50.0 + 29.0 - (double)v39->atQAnimframe[v39->nQAnimframes].nHeight;
    igi2_frame.vY1c = v27 + 4.0;
    QSprite_Register(v39, igi2_frame.vY1c, igi2_frame.vG1b, 51.20000076293945, 76.80000305175781, 128.0, 0, 0, 3);
    if ( igi2_frame.pxObject[60] == 1 )
      ActionMenuScreen_Draw(ActionMenuScreen_ptQTask);
    v17 = NetManager_eMode;
  }
  if ( igi2_frame.pxObject[60] == 4 )
  {
    ptTail = ptQTask[44].tQTaskRefList.ptTail;
    if ( ptTail )
    {
      v41 = (void (__cdecl *)(struct QReference_s *, void *))QTask_aatQTaskFinalEvent[StatusScreen_eStatusDisplayQTaskEvent][LOWORD(ptTail[3].ptNext)].pfHandler;
      if ( v41 )
      {
        v41(ptTail, pxContext);
        v17 = NetManager_eMode;
      }
    }
  }
  v42 = ptQTask[33].ptNext;
  if ( v42 && v42[4].ptNext == (struct QTask_s *)2 )
  {
    HumanPlayer_DrawFlashbangEffect((struct HumanPlayer_t *)ptQTask, 1);
    return;
  }
  if ( (Game_eGameMode == GAME_GAMEMODE_SINGLEPLAYER
     || v17 == NETMANAGER_MODE_PLAY
     || v17 == NETMANAGER_MODE_RADIO
     || v17 == NETMANAGER_MODE_SHOP && !LOBYTE(ptQTask[29].tQTaskRefList.ptHead))
    && !Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.isHideInventory )
  {
    if ( v42 )
    {
      v43 = v42[1].ptNext;
      if ( v43 )
      {
        if ( v43->tQTaskChildren.ptTail )
        {
          v44 = 0;
          igi2_frame.v162[3] = 64;
          igi2_frame.v162[8] = 64;
          igi2_frame.v162[13] = 64;
          igi2_frame.v162[18] = 64;
          igi2_frame.v162[23] = 64;
          igi2_frame.v162[28] = 64;
          igi2_frame.v162[33] = 64;
          igi2_frame.v162[38] = 64;
          v45 = v42[1].ptNext;
          v46 = 4;
          igi2_frame.v162[9] = "4";
          igi2_frame.v162[14] = "4";
          igi2_frame.v162[19] = "4";
          igi2_frame.v156 = 3;
          igi2_frame.v157 = 1;
          igi2_frame.v158 = 0;
          igi2_frame.v159 = 120;
          igi2_frame.ptQText = (struct StaticTilemap_s *)"1";
          igi2_frame.v161[0] = 2;
          igi2_frame.v161[1] = 1;
          igi2_frame.v161[2] = 0;
          igi2_frame.v161[3] = 72;
          igi2_frame.v161[4] = "2";
          igi2_frame.v162[0] = 1;
          igi2_frame.v162[1] = 0;
          igi2_frame.v162[2] = 0;
          igi2_frame.v162[4] = "3";
          igi2_frame.v162[5] = 4;
          igi2_frame.v162[6] = 1;
          igi2_frame.v162[7] = 1;
          igi2_frame.v162[10] = 6;
          igi2_frame.v162[11] = 1;
          igi2_frame.v162[12] = 1;
          igi2_frame.v162[15] = 7;
          igi2_frame.v162[16] = 1;
          igi2_frame.v162[17] = 1;
          igi2_frame.v162[20] = 9;
          igi2_frame.v162[21] = 0;
          igi2_frame.v162[22] = 0;
          igi2_frame.v162[24] = "5";
          igi2_frame.v162[25] = 5;
          igi2_frame.v162[26] = 1;
          igi2_frame.v162[27] = 1;
          igi2_frame.v162[29] = "6";
          igi2_frame.v162[30] = 10;
          igi2_frame.v162[31] = 0;
          igi2_frame.v162[32] = 0;
          igi2_frame.v162[34] = "7";
          igi2_frame.v162[35] = 8;
          igi2_frame.v162[36] = 1;
          igi2_frame.v162[37] = 1;
          igi2_frame.v162[39] = "9";
          igi2_frame.ptQSpriteb = 5;
          igi2_frame.vU1b = 4;
          igi2_frame.vX1 = 0;
          igi2_frame.v136 = 1;
          igi2_frame.vY1 = 1;
          if ( v45 )
            v47 = v45->tQTaskChildren.ptTail;
          else
            v47 = nullptr;
          igi2_frame.vX3 = (struct WeaponType_s *)v47;
          v48 = (int)v47[16].ptParent;
          if ( v48 == 4 || v48 == 6 || v48 == 7 )
          {
            v46 = v48;
            igi2_frame.vU1b = v48;
          }
          v49 = &igi2_frame.v156;
          do
          {
            if ( *v49 == 4 )
              break;
            if ( *v49 == 6 )
              break;
            ++v44;
            v49 += 5;
          }
          while ( v44 < 0xA );
          v50 = 5 * v44;
          v51 = &igi2_frame.v156 + 5 * v44;
          igi2_frame.v122 = (struct QSprite_s *)v44;
          if ( *v51 != v46 )
          {
            v52 = &igi2_frame.v161[v50];
            v53 = &igi2_frame.v162[v50];
            do
            {
              qmemcpy(igi2_frame.v143, v51, sizeof(igi2_frame.v143));
              qmemcpy(v51, v52, 0x14u);
              qmemcpy(v52, v53, 0x14u);
              qmemcpy(v53, igi2_frame.v143, 0x14u);
            }
            while ( *v51 != igi2_frame.vU1b );
          }
          v54 = 0;
          v55 = 0;
          igi2_frame.vXa = 0;
          igi2_frame.v130 = 0;
          igi2_frame.vU1c = 20 * igi2_frame.nWidth;
          while ( 1 )
          {
            if ( (struct QSprite_s *)v54 != igi2_frame.v122
              && (struct QSprite_s *)v54 != (struct QSprite_s *)((char *)&igi2_frame.v122->ptPalInfo + 1)
              && (struct QSprite_s *)v54 != (struct QSprite_s *)((char *)&igi2_frame.v122->ptPalInfo + 2) )
            {
              igi2_frame.v136 = 1;
            }
            v56 = (struct Weapon_s *)ptQTask[33].ptNext;
            v57 = (struct WeaponTypeItem_s *)v56->tPrivate.tActiveWeaponTypes.ptHead;
            v58 = (struct WeaponTypeItem_s *)v57->tNode.ptNext;
            if ( !v57->tNode.ptNext )
              goto LABEL_154;
            while ( !v57->isActive || v57->ptWeaponType->eWeaponCategory != *(int *)((char *)&igi2_frame.v156 + v55) )
            {
              v57 = v58;
              v58 = (struct WeaponTypeItem_s *)v58->tNode.ptNext;
              if ( !v58 )
                goto LABEL_154;
            }
            v59 = igi2_frame.v136;
            if ( igi2_frame.v136 && !igi2_frame.vY1 )
              igi2_frame.ptQSpriteb += *(int *)((char *)&igi2_frame.v159 + igi2_frame.vU1c) + 1;
            ptWeaponType = v57->ptWeaponType;
            igi2_frame.vU1d = ptWeaponType;
            *(float *)igi2_frame.v143 = (float)igi2_frame.ptQSpriteb;
            igi2_frame.vHeight = *(float *)igi2_frame.v143;
            if ( igi2_frame.v136 )
              igi2_frame.v113 = 5.0;
            if ( *(int *)((char *)&igi2_frame.v157 + v55) && igi2_frame.v136 )
            {
              Weapon_GetFireTypeAmmoInfoFromWeaponTypeItem(v56, v57, 0, &igi2_frame.nFireType);
              Weapon_GetFireTypeAmmoInfoFromWeaponTypeItem(
                (struct Weapon_s *)ptQTask[33].ptNext,
                v57,
                1,
                &igi2_frame.ptAmmoContext);
              if ( !strcmp(v57->ptWeaponType->zWeaponScriptID, "WEAPON_ID_M16A2") )
                sprintf(
                  igi2_frame.Buffer,
                  "%d/%d",
                  igi2_frame.nFireType.nAmmoAvailable + igi2_frame.nFireType.nAmmoInWeapon,
                  igi2_frame.ptAmmoContext.nAmmoAvailable);
              else
                sprintf(
                  igi2_frame.Buffer,
                  (char *const)&g_ptNetManager.tReceiveCounters.tCounters[9].nBytes,
                  igi2_frame.nFireType.nAmmoAvailable + (*(int *)((char *)&igi2_frame.v158 + igi2_frame.v130) != 0 ? 0 : igi2_frame.nFireType.nAmmoInWeapon));
              Text_SetString(*(struct StaticTilemap_s **)(v2 + 1116), igi2_frame.Buffer);
              v61 = *(float **)(v2 + 1116);
              v62 = *(__int16 *)(*(_DWORD *)v61 + 6);
              v63 = 0;
              igi2_frame.vY1a = 0;
              if ( v62 > 0 )
              {
                v64 = *(__int16 **)(*(_DWORD *)v61 + 12);
                do
                {
                  if ( *v64 > v63 )
                    v63 = *v64;
                  ++v64;
                  --v62;
                }
                while ( v62 );
                igi2_frame.vY1a = v63;
              }
              v61[1] = (float)(int)(__int64)((double)*(int *)((char *)&igi2_frame.v159 + igi2_frame.v130) + igi2_frame.vHeight - (double)igi2_frame.vY1a - 1.0);
              v65 = *(float **)(v2 + 1116);
              v65[2] = (float)(int)(__int64)(igi2_frame.v113
                                           + 56.0
                                           - 1.0
                                           - (double)(*(__int16 *)(*(_DWORD *)v65 + 6)
                                                    * *(__int16 *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)v65 + 8) + 8)
                                                                 + 36
                                                                 * *(unsigned __int16 *)(*(_DWORD *)(*(_DWORD *)v65 + 8)
                                                                                       + 20)
                                                                 + 14)));
              v66 = *(_DWORD *)(v2 + 1116);
              QTilemap_Register(
                *(struct QTilemap_s **)v66,
                *(float *)(v66 + 4),
                *(float *)(v66 + 8),
                *(float *)(v66 + 20),
                *(float *)(v66 + 24),
                *(float *)(v66 + 28),
                *(float *)(v66 + 16),
                *(float *)(v66 + 12),
                *(_DWORD *)(v66 + 36) | 0x40000000,
                *(_DWORD *)(v66 + 32));
              ptWeaponType = igi2_frame.vU1d;
              v55 = igi2_frame.v130;
              v59 = igi2_frame.v136;
            }
            if ( ptWeaponType->isWeaponSpriteLoaded == false )
              goto LABEL_135;
            if ( v59 )
              break;
LABEL_137:
            zName = ptWeaponType->zName;
            sprintf(igi2_frame.zResourceName, "weapons/strings/short/%s", zName);
            LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                           igi2_frame.zResourceName,
                                           Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                           false);
            if ( !LocalizedStringForLanguage )
            {
              sprintf(igi2_frame.zResourceName, "weapons/strings/%s", zName);
              LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                             igi2_frame.zResourceName,
                                             Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                             false);
              if ( !LocalizedStringForLanguage )
                LocalizedStringForLanguage = zName;
            }
            v70 = *(__int16 ***)(v2 + 1112);
            v71 = *v70;
            v72 = *((void **)*v70 + 3);
            v73 = 2 * (*v70)[3];
            *(_DWORD *)igi2_frame.v143 = v70;
            memset(v72, 0, v73);
            memset(v71 + 8, 0, v71[3] * v71[2]);
            v74 = **(struct QTilemap_s ***)igi2_frame.v143;
            v75 = *LocalizedStringForLanguage;
            v76 = *(_DWORD *)(*(_DWORD *)(**(_DWORD **)igi2_frame.v143 + 8) + 12) + 16;
            if ( *LocalizedStringForLanguage )
            {
              v77 = **(_DWORD **)igi2_frame.v143 + 16 - (_DWORD)LocalizedStringForLanguage;
              do
              {
                LocalizedStringForLanguage[v77] = *(_BYTE *)(v75 + v76);
                v75 = *++LocalizedStringForLanguage;
              }
              while ( v75 );
            }
            QTilemap_UpdateGraphicWidth(v74, 0);
            *(_QWORD *)igi2_frame.v143 = (__int64)(igi2_frame.vHeight + 1.0);
            *(float *)(*(_DWORD *)(v2 + 1112) + 4) = (float)*(int *)igi2_frame.v143;
            *(_QWORD *)igi2_frame.v143 = (__int64)(igi2_frame.v113 + 1.0);
            *(float *)(*(_DWORD *)(v2 + 1112) + 8) = (float)*(int *)igi2_frame.v143;
            *(_DWORD *)(*(_DWORD *)(v2 + 1112) + 32) = 3;
            if ( igi2_frame.vU1d == igi2_frame.vX3 )
            {
              *(_DWORD *)(*(_DWORD *)(v2 + 1112) + 20) = 1122395750;
              *(_DWORD *)(*(_DWORD *)(v2 + 1112) + 24) = 1122395750;
            }
            else
            {
              *(_DWORD *)(*(_DWORD *)(v2 + 1112) + 20) = 1112329421;
              *(_DWORD *)(*(_DWORD *)(v2 + 1112) + 24) = 1117362586;
            }
            *(_DWORD *)(*(_DWORD *)(v2 + 1112) + 28) = 1124073472;
            v78 = *(_DWORD *)(v2 + 1112);
            QTilemap_Register(
              *(struct QTilemap_s **)v78,
              *(float *)(v78 + 4),
              *(float *)(v78 + 8),
              *(float *)(v78 + 20),
              *(float *)(v78 + 24),
              *(float *)(v78 + 28),
              *(float *)(v78 + 16),
              *(float *)(v78 + 12),
              *(_DWORD *)(v78 + 36) | 0x40000000,
              *(_DWORD *)(v78 + 32));
            *(_DWORD *)igi2_frame.v143 = *(__int16 *)(**(_DWORD **)(v2 + 1112) + 6)
                            * *(__int16 *)(*(_DWORD *)(*(_DWORD *)(**(_DWORD **)(v2 + 1112) + 8) + 8)
                                         + 36 * *(unsigned __int16 *)(*(_DWORD *)(**(_DWORD **)(v2 + 1112) + 8) + 20)
                                         + 14);
            igi2_frame.vR1e = (float)*(int *)igi2_frame.v143;
            igi2_frame.vV4c = (float)*(int *)((char *)&igi2_frame.v159 + igi2_frame.v130);
            QSprite_RegisterBlankA(igi2_frame.vHeight, igi2_frame.v113, igi2_frame.vV4c, igi2_frame.vR1e, 0.0, 0.0, 0.0, 0.5, 0x80000u, 5);
            *(_DWORD *)igi2_frame.v143 = *(__int16 *)(**(_DWORD **)(v2 + 1112) + 6)
                            * *(__int16 *)(*(_DWORD *)(*(_DWORD *)(**(_DWORD **)(v2 + 1112) + 8) + 8)
                                         + 36 * *(unsigned __int16 *)(*(_DWORD *)(**(_DWORD **)(v2 + 1112) + 8) + 20)
                                         + 14);
            v79 = (struct QSprite_s *)(igi2_frame.vXa + 1);
            igi2_frame.v113 = (double)*(int *)igi2_frame.v143 + igi2_frame.v113 + 1.0;
            if ( (struct QSprite_s *)(igi2_frame.vXa + 1) == igi2_frame.v122
              || v79 == (struct QSprite_s *)((char *)&igi2_frame.v122->ptPalInfo + 1)
              || v79 == (struct QSprite_s *)((char *)&igi2_frame.v122->ptPalInfo + 2) )
            {
              if ( igi2_frame.vX1 )
                igi2_frame.v136 = 0;
              igi2_frame.vX1 = 1;
            }
            else
            {
              igi2_frame.v136 = 1;
            }
            igi2_frame.vY1 = 0;
            igi2_frame.vU1c = igi2_frame.v130;
            v54 = igi2_frame.vXa;
            v55 = igi2_frame.v130;
LABEL_154:
            ++v54;
            v55 += 20;
            igi2_frame.vXa = v54;
            igi2_frame.v130 = v55;
            if ( v54 >= 0xA )
              goto LABEL_155;
          }
          igi2_frame.vG1c = (double)(*(__int16 *)(**(_DWORD **)(v2 + 1116) + 6)
                        * *(__int16 *)(*(_DWORD *)(*(_DWORD *)(**(_DWORD **)(v2 + 1116) + 8) + 8)
                                     + 36 * *(unsigned __int16 *)(*(_DWORD *)(**(_DWORD **)(v2 + 1116) + 8) + 20)
                                     + 14))
               + igi2_frame.v113;
          igi2_frame.vR1c = (double)*(int *)((char *)&igi2_frame.v159 + v55) * 0.5
               + igi2_frame.vHeight
               - (double)ptWeaponType->tWeaponSprite.atQAnimframe[ptWeaponType->tWeaponSprite.nQAnimframes].nWidth * 0.5;
          QSprite_Register(&ptWeaponType->tWeaponSprite, igi2_frame.vR1c, igi2_frame.vG1c, 128.0, 128.0, 128.0, 0, 0, 3);
          v59 = igi2_frame.v136;
LABEL_135:
          if ( v59 )
          {
            Text_SetString(*(struct StaticTilemap_s **)(v2 + 1116), *(char **)((char *)&igi2_frame.v161[-1] + igi2_frame.v130));
            *(float *)(*(_DWORD *)(v2 + 1116) + 4) = (float)(int)(__int64)(igi2_frame.vHeight + 1.0);
            *(float *)(*(_DWORD *)(v2 + 1116) + 8) = (float)(int)(__int64)(igi2_frame.v113 + 1.0);
            *(_DWORD *)(*(_DWORD *)(v2 + 1116) + 32) = 3;
            v67 = *(_DWORD *)(v2 + 1116);
            QTilemap_Register(
              *(struct QTilemap_s **)v67,
              *(float *)(v67 + 4),
              *(float *)(v67 + 8),
              *(float *)(v67 + 20),
              *(float *)(v67 + 24),
              *(float *)(v67 + 28),
              *(float *)(v67 + 16),
              *(float *)(v67 + 12),
              *(_DWORD *)(v67 + 36) | 0x40000000,
              *(_DWORD *)(v67 + 32));
            igi2_frame.v115 = igi2_frame.v113 + 56.0;
            igi2_frame.vR1d = igi2_frame.v115 - 5.0;
            igi2_frame.vV4b = (float)*(int *)((char *)&igi2_frame.v159 + igi2_frame.v130);
            QSprite_RegisterBlankA(*(float *)igi2_frame.v143, 5.0, igi2_frame.vV4b, igi2_frame.vR1d, 0.0, 0.0, 0.0, 0.5, 0x80000u, 5);
            ptWeaponType = igi2_frame.vU1d;
            igi2_frame.v113 = igi2_frame.v115 + 1.0;
          }
          goto LABEL_137;
        }
      }
    }
  }
LABEL_155:
  if ( LOBYTE(ptQTask[78].ptPrev) )
  {
    igi2_frame.vXb = (float)igi2_frame.nHeight;
    igi2_frame.v123 = (float)igi2_frame.nWidth;
    igi2_frame.vR1f = igi2_frame.vXb * 0.010416666977107525;
    igi2_frame.vV4d = (double)(int)ptQTask[78].ptNext / (double)*(int *)&ptQTask[77].eQTaskType * igi2_frame.v123 * 0.3687500059604645;
    igi2_frame.v81 = igi2_frame.vXb * 0.8374999761581421;
    igi2_frame.v80 = igi2_frame.v123 * 0.31562501192092896;
    QSprite_RegisterBlankA(igi2_frame.v80, igi2_frame.v81, igi2_frame.vV4d, igi2_frame.vR1f, 128.0, 128.0, 128.0, 1.0, 0, 3);
    igi2_frame.vHeighta = igi2_frame.vXb * 0.01875000074505806;
    igi2_frame.vY1d = igi2_frame.v123 * 0.375;
    igi2_frame.vX3c = igi2_frame.vXb * 0.8333333134651184;
    igi2_frame.vX1d = igi2_frame.v123 * 0.3125;
    QSprite_RegisterBlankA(igi2_frame.vX1d, igi2_frame.vX3c, igi2_frame.vY1d, igi2_frame.vHeighta, 25.600000381469727, 64.0, 128.0, 0.5, 0x80000u, 3);
    igi2_frame.ptAmmoContext.nAmmoInWeapon = 1057132380;
    igi2_frame.ptAmmoContext.nAmmoAvailable = 1059145646;
    igi2_frame.ptAmmoContext.nBulletsPerRound = 1065017672;
    igi2_frame.ptAmmoContext.ptAmmoType = (struct AmmoType_s *)1065353216;
    igi2_frame.nFireType.nBulletsPerRound = 0;
    igi2_frame.nFireType.nRoundsPerClip = 0;
    *(float *)&igi2_frame.ptQSpritec = igi2_frame.vY1d + igi2_frame.vX1d;
    igi2_frame.nFireType.nAmmoAvailable = 981668463;
    igi2_frame.v152 = 1057132380;
    igi2_frame.v153 = 1059145646;
    igi2_frame.v154 = 1065017672;
    igi2_frame.v151 = 1065353216;
    *(float *)&igi2_frame.vXc = igi2_frame.vHeighta + igi2_frame.vX3c;
    igi2_frame.v149 = 0;
    *(float *)&igi2_frame.nFireType.ptAmmoType = igi2_frame.vX1d;
    *(float *)&igi2_frame.nFireType.nAmmoInWeapon = igi2_frame.vX3c;
    igi2_frame.v150 = 0;
    igi2_frame.ptAmmoContext.nRoundsPerClip = igi2_frame.ptQSpritec;
    igi2_frame.v148 = 981668463;
    *(_DWORD *)igi2_frame.v143 = 1;
    *(float *)&igi2_frame.v147 = igi2_frame.vX3c;
    *(_DWORD *)&igi2_frame.v143[8] = 3;
    *(_DWORD *)&igi2_frame.v143[12] = 2;
    *(_DWORD *)&igi2_frame.v143[16] = &igi2_frame.nFireType;
    *(_DWORD *)&igi2_frame.v143[4] = 0;
    RenderMode_tActiveRenderMode.apfRenderModeMethod[QVertex_eRegisterQVertexStripMethod](igi2_frame.v143);
    *(float *)&igi2_frame.nFireType.ptAmmoType = igi2_frame.vX1d;
    igi2_frame.nFireType.nAmmoInWeapon = igi2_frame.vXc;
    igi2_frame.ptAmmoContext.nRoundsPerClip = igi2_frame.ptQSpritec;
    igi2_frame.v147 = igi2_frame.vXc;
    RenderMode_tActiveRenderMode.apfRenderModeMethod[QVertex_eRegisterQVertexStripMethod](igi2_frame.v143);
    *(float *)&igi2_frame.nFireType.nAmmoInWeapon = igi2_frame.vX3c;
    *(float *)&igi2_frame.nFireType.ptAmmoType = igi2_frame.vX1d;
    *(float *)&igi2_frame.ptAmmoContext.nRoundsPerClip = igi2_frame.vX1d;
    igi2_frame.v147 = igi2_frame.vXc;
    RenderMode_tActiveRenderMode.apfRenderModeMethod[QVertex_eRegisterQVertexStripMethod](igi2_frame.v143);
    igi2_frame.nFireType.ptAmmoType = (struct AmmoType_s *)igi2_frame.ptQSpritec;
    *(float *)&igi2_frame.v147 = *(float *)&igi2_frame.vXc + 1.0;
    *(float *)&igi2_frame.nFireType.nAmmoInWeapon = igi2_frame.vX3c;
    igi2_frame.ptAmmoContext.nRoundsPerClip = igi2_frame.ptQSpritec;
    RenderMode_tActiveRenderMode.apfRenderModeMethod[QVertex_eRegisterQVertexStripMethod](igi2_frame.v143);
  }
  HumanPlayer_DrawDamageFlash((struct HumanPlayer_t *)ptQTask);
  HumanPlayer_DrawFlashbangEffect((struct HumanPlayer_t *)ptQTask, 3);
}

// source: j/0/human/humanplayer.c:18536  [anchor-mhash]
void __cdecl HumanPlayer_DrawComputerObjectHandler(struct QTask_s *ptQTask, void *pxContext)
{
  long double v2; // st7

  *((_DWORD *)pxContext + 3) = ptQTask + 1;
  *((_DWORD *)pxContext + 4) = (char *)ptQTask + 124;
  v2 = sqrt(
         *(float *)&ptQTask[7].tQTaskChildren.ptTail * *(float *)&ptQTask[7].tQTaskChildren.ptTail
       + *(float *)&ptQTask[7].tQTaskRefList.ptHead * *(float *)&ptQTask[7].tQTaskRefList.ptHead
       + *(float *)&ptQTask[7].tQTaskRefList.ptMiddle * *(float *)&ptQTask[7].tQTaskRefList.ptMiddle)
     + *(float *)&ptQTask[8].ptNext;
  *((_DWORD *)pxContext + 7) = 1;
  *((_DWORD *)pxContext + 8) = 2;
  *((float *)pxContext + 5) = v2;
  ComputerObject_DrawMarker((struct DrawComputerObjectContext_s *)pxContext);
}

// source: j/0/human/humanplayer.c:18563  [anchor-mhash]
void __cdecl HumanPlayer_WeaponGetParentParametersHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDest; };
    struct { char igi2_o1[4]; float vAlpha; };
    struct { char igi2_o2[28]; float vPrecision; };
    struct { char igi2_o3[32]; float vT1; };
    struct { char igi2_o4[36]; struct real32x9_t tNewOrientation; };
    struct { char igi2_o5[76]; struct real32x9_t Real32x9_Multiply_tTemp; };
    char igi2_extent[120];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptTail; // eax
  float *v4; // ebx
  struct QTask_s **p_ptTail; // esi
  bool v6; // zf
  DWORD TickCount; // eax
  DWORD PerformanceCounter; // eax
  double v9; // st7
  struct RandomState_s *p_tRunRandomState; // esi
  DWORD v11; // eax
  DWORD v12; // eax
  double v13; // st7
  double v14; // st7
  float ptQTaska = *(float *)&ptQTask; // [esp+7Ch] [ebp+4h] ARGSLOT
  void *pxContexta = *(void * *)&pxContext; // [esp+80h] [ebp+8h] ARGSLOT
  void *pxContextb = *(void * *)&pxContext; // [esp+80h] [ebp+8h] ARGSLOT

  ptTail = ptQTask[33].tQTaskChildren.ptTail;
  v4 = (float *)((char *)pxContext + 24);
  if ( BYTE2(ptTail[12].tQTaskRefList.ptTail) )
  {
    qmemcpy(pxContext, &ptTail[12].ptParent, 0x18u);
    p_ptTail = &ptTail[13].tQTaskChildren.ptTail;
  }
  else
  {
    qmemcpy(pxContext, &ptTail[10].tQTaskChildren, 0x18u);
    p_ptTail = &ptQTask[33].tQTaskChildren.ptTail[10].ptParent;
  }
  v6 = Timer_isPerformanceCounter == 0;
  qmemcpy(v4, p_ptTail, 0x28u);
  if ( v6 )
    TickCount = GetTickCount();
  else
    TickCount = Timer_GetPerformanceCounter();
  if ( (int)(TickCount - Timer_nStartTime - 600000) >= 0 )
  {
    if ( Timer_isPerformanceCounter )
      PerformanceCounter = Timer_GetPerformanceCounter();
    else
      PerformanceCounter = GetTickCount();
    pxContexta = (void *)(PerformanceCounter - Timer_nStartTime - 600000);
  }
  else
  {
    pxContexta = nullptr;
  }
  v9 = (double)(int)pxContexta * 0.0000008333333333333333;
  if ( v9 >= 1.0 )
    v9 = 1.0;
  if ( *((_DWORD *)pxContext + 16)
    && ((DEGRADE_PlayerPerfectShotTimer - 1.0) * v9 + 1.0) * 60.0 > (double)(int)ptQTask[83].ptParent )
  {
    p_tRunRandomState = &Game_ptGame->tRunRandomState;
    igi2_frame.vPrecision = *(float *)&ptQTask[77].tQTaskRefList.ptMiddle + *(float *)&ptQTask[77].tQTaskChildren.ptTail;
    igi2_frame.vT1 = Random_GetRandomNumberReal32(&Game_ptGame->tRunRandomState);
    ptQTaska = Random_GetRandomNumberReal32(p_tRunRandomState);
    if ( Timer_isPerformanceCounter )
      v11 = Timer_GetPerformanceCounter();
    else
      v11 = GetTickCount();
    if ( (int)(v11 - Timer_nStartTime - 600000) >= 0 )
    {
      if ( Timer_isPerformanceCounter )
        v12 = Timer_GetPerformanceCounter();
      else
        v12 = GetTickCount();
      pxContextb = (void *)(v12 - Timer_nStartTime - 600000);
    }
    else
    {
      pxContextb = nullptr;
    }
    v13 = (double)(int)pxContextb * 0.0000008333333333333333;
    if ( v13 >= 1.0 )
      v13 = 1.0;
    igi2_frame.vAlpha = ptQTaska * 6.2831854820251465;
    igi2_frame.ptDest = ((DEGRADE_PlayerAccuracy - 1.0) * v13 + 1.0) * igi2_frame.vPrecision * 0.01745329238474369 * igi2_frame.vT1;
    Real32x9_Create(&igi2_frame.tNewOrientation, igi2_frame.ptDest, igi2_frame.vAlpha, 0.0);
    igi2_frame.Real32x9_Multiply_tTemp.tX.vX = igi2_frame.tNewOrientation.tX.vX * *v4
                                  + igi2_frame.tNewOrientation.tZ.vX * *((float *)pxContext + 8)
                                  + igi2_frame.tNewOrientation.tY.vX * *((float *)pxContext + 7);
    igi2_frame.Real32x9_Multiply_tTemp.tX.vY = igi2_frame.tNewOrientation.tX.vY * *v4
                                  + igi2_frame.tNewOrientation.tZ.vY * *((float *)pxContext + 8)
                                  + igi2_frame.tNewOrientation.tY.vY * *((float *)pxContext + 7);
    igi2_frame.Real32x9_Multiply_tTemp.tX.vZ = igi2_frame.tNewOrientation.tX.vZ * *v4
                                  + igi2_frame.tNewOrientation.tZ.vZ * *((float *)pxContext + 8)
                                  + igi2_frame.tNewOrientation.tY.vZ * *((float *)pxContext + 7);
    igi2_frame.Real32x9_Multiply_tTemp.tY.vX = igi2_frame.tNewOrientation.tZ.vX * *((float *)pxContext + 11)
                                  + igi2_frame.tNewOrientation.tX.vX * *((float *)pxContext + 9)
                                  + igi2_frame.tNewOrientation.tY.vX * *((float *)pxContext + 10);
    igi2_frame.Real32x9_Multiply_tTemp.tY.vY = igi2_frame.tNewOrientation.tZ.vY * *((float *)pxContext + 11)
                                  + igi2_frame.tNewOrientation.tX.vY * *((float *)pxContext + 9)
                                  + igi2_frame.tNewOrientation.tY.vY * *((float *)pxContext + 10);
    igi2_frame.Real32x9_Multiply_tTemp.tY.vZ = igi2_frame.tNewOrientation.tZ.vZ * *((float *)pxContext + 11)
                                  + igi2_frame.tNewOrientation.tX.vZ * *((float *)pxContext + 9)
                                  + igi2_frame.tNewOrientation.tY.vZ * *((float *)pxContext + 10);
    v14 = igi2_frame.tNewOrientation.tY.vX * *((float *)pxContext + 13) + igi2_frame.tNewOrientation.tZ.vX * *((float *)pxContext + 14);
    igi2_frame.Real32x9_Multiply_tTemp.nOps = *((_DWORD *)pxContext + 15) + igi2_frame.tNewOrientation.nOps + 1;
    igi2_frame.Real32x9_Multiply_tTemp.tZ.vX = v14 + igi2_frame.tNewOrientation.tX.vX * *((float *)pxContext + 12);
    igi2_frame.Real32x9_Multiply_tTemp.tZ.vY = igi2_frame.tNewOrientation.tY.vY * *((float *)pxContext + 13)
                                  + igi2_frame.tNewOrientation.tZ.vY * *((float *)pxContext + 14)
                                  + igi2_frame.tNewOrientation.tX.vY * *((float *)pxContext + 12);
    igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ = igi2_frame.tNewOrientation.tY.vZ * *((float *)pxContext + 13)
                                  + igi2_frame.tNewOrientation.tZ.vZ * *((float *)pxContext + 14)
                                  + igi2_frame.tNewOrientation.tX.vZ * *((float *)pxContext + 12);
    qmemcpy(v4, &igi2_frame.Real32x9_Multiply_tTemp, 0x28u);
  }
}

// source: j/0/human/humanplayer.c:18630  [size]
unsigned __int16 __cdecl HumanPlayer_GetQTaskType()
{
  return HumanPlayer_eQTaskType;
}

// source: j/0/human/humanplayer.c:18644  [anchor-mhash]
void __cdecl HumanPlayer_UpdateParameters(struct HumanPlayerConfigItem_t *ptHumanPlayerConfigItem)
{
  struct DamagePartData_t *v1; // eax
  float *avDamagePartMultiplier; // ecx
  struct DamagePartData_t *v3; // eax
  float *avDamagePartMultiplierMultiplayer; // ecx

  HumanPlayer_tGeneral.vDeltaTranslationScale = ptHumanPlayerConfigItem->vDeltaTranslationScale;
  HumanPlayer_tGeneral.vForwardJumpSpeed = ptHumanPlayerConfigItem->vForwardJumpSpeed * 4096000.0 * 9.259259059035685e-06;
  HumanPlayer_tGeneral.vUpwardJumpSpeed = ptHumanPlayerConfigItem->vUpwardJumpSpeed * 4096000.0 * 9.259259059035685e-06;
  HumanPlayer_tGeneral.vInAirControlSpeed = ptHumanPlayerConfigItem->vInAirControlSpeed * 4096000.0 * 9.259259059035685e-06;
  HumanPlayer_tGeneral.vPeekOffsetX = ptHumanPlayerConfigItem->vPeekOffsetX * 4096.0;
  HumanPlayer_tGeneral.vPeekOffsetZ = ptHumanPlayerConfigItem->vPeekOffsetZ * 4096.0;
  HumanPlayer_tGeneral.nPeekTime = (__int64)(ptHumanPlayerConfigItem->vPeekTime * 30.0);
  HumanPlayer_tGeneral.vMaxDamageScale = ptHumanPlayerConfigItem->vMaxDamageScale;
  HumanPlayer_tGeneral.vElectricFenceDamageScale = ptHumanPlayerConfigItem->vElectricFenceDamageScale;
  v1 = HumanPlayer_atDamagePartData;
  avDamagePartMultiplier = ptHumanPlayerConfigItem->avDamagePartMultiplier;
  do
  {
    v1->vDamageMultiplier = *avDamagePartMultiplier;
    ++v1;
    ++avDamagePartMultiplier;
  }
  while ( (int)v1 < 7049348 );
  v3 = HumanPlayer_atDamagePartDataMultiplayer;
  avDamagePartMultiplierMultiplayer = ptHumanPlayerConfigItem->avDamagePartMultiplierMultiplayer;
  do
  {
    v3->vDamageMultiplier = *avDamagePartMultiplierMultiplayer;
    ++v3;
    ++avDamagePartMultiplierMultiplayer;
  }
  while ( (int)v3 < 7050372 );
  HumanPlayer_tGeneral.vThrowingBaseVelocity = ptHumanPlayerConfigItem->vThrowingBaseVelocity;
}

// source: j/0/human/humanplayer.c:18704  [anchor-callee]
int __cdecl HumanPlayer_SetUpperBody(struct QTask_s *ptQTask, int eUpperBody)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s *v50; };
    struct { char igi2_o1[4]; struct AnimHeader_s *v51; };
    struct { char igi2_o2[4]; struct AnimHeader_s *v52; };
    struct { char igi2_o3[28]; enum WeaponTypeGetAnimType_e v53; };
    struct { char igi2_o4[32]; enum bool nTimeFrame; };
    struct { char igi2_o5[36]; enum WeaponTypeGetAnimType_e eAnimType[2]; };
    struct { char igi2_o6[52]; struct QReference_s *v56; };
    struct { char igi2_o7[56]; struct QTask_s *v57; };
    struct { char igi2_o8[60]; int v58; };
    struct { char igi2_o9[64]; int v59; };
    struct { char igi2_o10[68]; struct QTask_s *v60; };
    struct { char igi2_o11[76]; struct AnimHeader_s *ptAnim; };
    struct { char igi2_o12[80]; float v62; };
    char igi2_extent[88];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  BOOL v4; // edx
  int result; // eax
  int v6; // eax
  int v7; // ebx
  struct QTask_s *v8; // eax
  struct QTask_s *v9; // edx
  struct QTask_s *v10; // ecx
  struct QTask_s *v11; // ecx
  struct QTask_s *v12; // eax
  void (__cdecl *v13)(struct QTask_s *, struct QReference_s **); // ecx
  struct QTask_s *v14; // eax
  int v15; // eax
  struct QReference_s *v16; // ecx
  struct QTask_s *v17; // edx
  struct QTask_s *v18; // eax
  struct QTask_s *v19; // ecx
  struct QTask_s *v20; // ecx
  struct QTask_s *v21; // eax
  void (__cdecl *v22)(struct QTask_s *, struct QReference_s **); // ecx
  struct QTask_s *v23; // eax
  int v24; // eax
  struct QReference_s *v25; // ecx
  struct QTask_s *v26; // edx
  struct QTask_s *v27; // eax
  struct QTask_s *v28; // ecx
  struct QTask_s *v29; // ecx
  struct QTask_s *v30; // eax
  void (__cdecl *v31)(struct QTask_s *, struct QReference_s **); // ecx
  struct QTask_s *v32; // eax
  int v33; // eax
  struct QReference_s *v34; // edx
  struct QTask_s *v35; // eax
  struct QTask_s *v36; // ecx
  struct QTask_s *v37; // ecx
  struct QTask_s *v38; // eax
  void (__cdecl *v39)(struct QTask_s *, struct QReference_s **); // ecx
  struct QTask_s *v40; // eax
  int v41; // eax
  struct QReference_s *ptTail; // ecx
  struct QTask_s *ptPrev; // edx
  struct QTask_s *ptNext; // eax
  struct QTask_s *v45; // ecx
  struct QTask_s *v46; // ecx
  struct QTask_s *v47; // eax
  void (__cdecl *pfHandler)(struct QTask_s *, struct QReference_s **); // ecx
  struct QTask_s *v49; // eax

  v4 = 0;
  igi2_frame.eAnimType[0] = WEAPONTYPE_GETANIMTYPE_1STSTAND;
  igi2_frame.nTimeFrame = false;
  ptQTask[77].tQTaskRefList.ptTail = (struct QReference_s *)eUpperBody;
  if ( !eUpperBody )
  {
    ptQTask[77].ptParent = nullptr;
    HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.4000000059604645);
    return result;
  }
  v6 = *(_DWORD *)&ptQTask[32].eQTaskType;
  ptQTask[87].tQTaskChildren.ptMiddle = (struct QTask_s *)1;
  v7 = v6 != 2 ? 0 : 0x4B;
  switch ( eUpperBody )
  {
    case 1:
    case 4:
    case 5:
      igi2_frame.v53 = WEAPONTYPE_GETANIMTYPE_1STSTAND;
      break;
    case 2:
    case 3:
      igi2_frame.v53 = WEAPONTYPE_GETANIMTYPE_1STMOVE;
      break;
    case 6:
      *(_QWORD *)igi2_frame.eAnimType = (__int64)(Random_GetRandomNumberReal32(&Game_ptGame->tRunRandomState) * 0.17499999701976776 * 4800.0);
      goto LABEL_7;
    case 7:
LABEL_7:
      v6 = *(_DWORD *)&ptQTask[32].eQTaskType;
      v4 = ptQTask[77].ptPrev != nullptr;
      igi2_frame.v53 = WEAPONTYPE_GETANIMTYPE_1STFIRE;
      v7 = v6 == 2 ? 76 : 83;
      break;
    case 8:
      igi2_frame.v53 = WEAPONTYPE_GETANIMTYPE_1STRELOADSTART;
      v7 = v6 == 2 ? 77 : 84;
      break;
    case 9:
      igi2_frame.v53 = WEAPONTYPE_GETANIMTYPE_1STRELOADLOOP;
      v7 = v6 == 2 ? 78 : 85;
      break;
    case 10:
      igi2_frame.v53 = WEAPONTYPE_GETANIMTYPE_1STRELOADEND;
      v7 = v6 == 2 ? 79 : 86;
      break;
    case 11:
      v7 = v6 == 2 ? 91 : 88;
      goto LABEL_13;
    case 12:
      igi2_frame.nTimeFrame = true;
      v7 = v6 == 2 ? 90 : 87;
LABEL_13:
      igi2_frame.v53 = WEAPONTYPE_GETANIMTYPE_1STACTIVATE;
      break;
    default:
      break;
  }
  if ( v6 == 2 )
  {
    HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
    if ( v7 == 77 || v7 == 78 || v7 == 79 )
    {
      switch ( eUpperBody )
      {
        case 8:
          v41 = 23;
          ptQTask[35].tQTaskChildren.ptTail = (struct QTask_s *)77;
          break;
        case 9:
          v41 = 24;
          ptQTask[35].tQTaskChildren.ptTail = (struct QTask_s *)78;
          break;
        case 10:
          v41 = 25;
          ptQTask[35].tQTaskChildren.ptTail = (struct QTask_s *)79;
          break;
        default:
          v41 = igi2_frame.eAnimType[0];
          break;
      }
      ptTail = ptQTask[7].tQTaskRefList.ptTail;
      ptPrev = ptQTask[77].ptPrev;
      igi2_frame.v59 = v41;
      ptNext = ptQTask[33].ptNext;
      igi2_frame.v56 = ptTail;
      igi2_frame.v60 = ptPrev;
      igi2_frame.v57 = ptNext;
      igi2_frame.v58 = 0;
      igi2_frame.ptAnim = nullptr;
      v45 = ptNext[1].ptPrev;
      if ( v45 )
        v46 = v45->tQTaskChildren.ptTail;
      else
        v46 = nullptr;
      v47 = ptNext[1].ptPrev;
      pfHandler = (void (__cdecl *)(struct QTask_s *, struct QReference_s **))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][v46->eQTaskType].pfHandler;
      if ( v47 )
        v49 = v47->tQTaskChildren.ptTail;
      else
        v49 = nullptr;
      pfHandler(v49, &igi2_frame.v56);
      if ( igi2_frame.ptAnim )
      {
        HumanAnim_SetAnimation(ptQTask, igi2_frame.ptAnim, 0, 0.0);
        ptQTask[34].tQTaskChildren.ptTail[1].tQTaskRefList.ptTail = (struct QReference_s *)(__int64)((double)AnimController_nTicksPerFrame * igi2_frame.v62);
      }
      goto LABEL_92;
    }
    if ( v7 != 90 && v7 != 91 )
    {
      HumanAnim_SetAnimationAndTimeFromState(ptQTask, v7, 0, 0.0);
      goto LABEL_92;
    }
    if ( eUpperBody == 11 )
    {
      v33 = 27;
      ptQTask[35].tQTaskRefList.ptHead = (struct QReference_s *)91;
    }
    else if ( eUpperBody == 12 )
    {
      v33 = 26;
      ptQTask[35].tQTaskRefList.ptHead = (struct QReference_s *)90;
    }
    else
    {
      v33 = igi2_frame.eAnimType[0];
    }
    v34 = ptQTask[7].tQTaskRefList.ptTail;
    igi2_frame.v59 = v33;
    igi2_frame.v60 = ptQTask[77].ptPrev;
    v35 = ptQTask[33].ptNext;
    igi2_frame.v56 = v34;
    igi2_frame.v57 = v35;
    igi2_frame.v58 = 0;
    igi2_frame.ptAnim = nullptr;
    v36 = v35[1].ptPrev;
    if ( v36 )
      v37 = v36->tQTaskChildren.ptTail;
    else
      v37 = nullptr;
    v38 = v35[1].ptPrev;
    v39 = (void (__cdecl *)(struct QTask_s *, struct QReference_s **))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][v37->eQTaskType].pfHandler;
    if ( v38 )
      v40 = v38->tQTaskChildren.ptTail;
    else
      v40 = nullptr;
    v39(v40, &igi2_frame.v56);
    if ( igi2_frame.ptAnim )
    {
      igi2_frame.v52 = igi2_frame.ptAnim;
      igi2_frame.v50 = ptQTask;
      if ( eUpperBody == 12 )
        goto LABEL_41;
      goto LABEL_42;
    }
LABEL_76:
    HumanAnim_ClearUpperBodyAnimation(ptQTask, 0.0);
    goto LABEL_92;
  }
  if ( !v4 )
  {
    if ( eUpperBody == 8 || eUpperBody == 9 || eUpperBody == 10 )
    {
      if ( eUpperBody == 8 )
      {
        v24 = 20;
        ptQTask[35].tQTaskRefList.ptHead = (struct QReference_s *)84;
      }
      else if ( eUpperBody == 9 )
      {
        v24 = 21;
        ptQTask[35].tQTaskRefList.ptHead = (struct QReference_s *)85;
      }
      else
      {
        v24 = 22;
        ptQTask[35].tQTaskRefList.ptHead = (struct QReference_s *)86;
      }
      v25 = ptQTask[7].tQTaskRefList.ptTail;
      v26 = ptQTask[77].ptPrev;
      igi2_frame.v59 = v24;
      v27 = ptQTask[33].ptNext;
      igi2_frame.v56 = v25;
      igi2_frame.v60 = v26;
      igi2_frame.v57 = v27;
      igi2_frame.v58 = 0;
      igi2_frame.ptAnim = nullptr;
      v28 = v27[1].ptPrev;
      if ( v28 )
        v29 = v28->tQTaskChildren.ptTail;
      else
        v29 = nullptr;
      v30 = v27[1].ptPrev;
      v31 = (void (__cdecl *)(struct QTask_s *, struct QReference_s **))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][v29->eQTaskType].pfHandler;
      if ( v30 )
        v32 = v30->tQTaskChildren.ptTail;
      else
        v32 = nullptr;
      v31(v32, &igi2_frame.v56);
      if ( igi2_frame.ptAnim )
      {
        HumanAnim_SetUpperBodyAnimationFromHeader(ptQTask, igi2_frame.ptAnim, 0, 0.0);
        ptQTask[34].tQTaskRefList.ptHead[5].pxObject = (void *)(__int64)((double)AnimController_nTicksPerFrame * igi2_frame.v62);
        goto LABEL_92;
      }
    }
    else
    {
      if ( eUpperBody != 11 && eUpperBody != 12 )
      {
        HumanAnim_SetUpperBodyAnimationAndTimeFromState(ptQTask, v7, 0, 0.0);
        goto LABEL_92;
      }
      if ( eUpperBody == 11 )
      {
        v15 = 16;
        ptQTask[35].tQTaskRefList.ptHead = (struct QReference_s *)88;
      }
      else
      {
        v15 = 15;
        ptQTask[35].tQTaskRefList.ptHead = (struct QReference_s *)87;
      }
      v16 = ptQTask[7].tQTaskRefList.ptTail;
      v17 = ptQTask[77].ptPrev;
      igi2_frame.v59 = v15;
      v18 = ptQTask[33].ptNext;
      igi2_frame.v56 = v16;
      igi2_frame.v60 = v17;
      igi2_frame.v57 = v18;
      igi2_frame.v58 = 0;
      igi2_frame.ptAnim = nullptr;
      v19 = v18[1].ptPrev;
      if ( v19 )
        v20 = v19->tQTaskChildren.ptTail;
      else
        v20 = nullptr;
      v21 = v18[1].ptPrev;
      v22 = (void (__cdecl *)(struct QTask_s *, struct QReference_s **))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][v20->eQTaskType].pfHandler;
      if ( v21 )
        v23 = v21->tQTaskChildren.ptTail;
      else
        v23 = nullptr;
      v22(v23, &igi2_frame.v56);
      if ( igi2_frame.ptAnim )
      {
        igi2_frame.v52 = igi2_frame.ptAnim;
        igi2_frame.v50 = ptQTask;
        if ( eUpperBody == 12 )
        {
LABEL_41:
          HumanAnim_SetUpperBodyAnimationFromHeader(ptQTask, igi2_frame.ptAnim, igi2_frame.ptAnim->nTotalTime, 0.0);
          ptQTask[34].tQTaskRefList.ptHead[5].pxObject = (void *)(__int64)(-igi2_frame.v62 * (double)AnimController_nTicksPerFrame);
          goto LABEL_92;
        }
LABEL_42:
        HumanAnim_SetUpperBodyAnimationFromHeader(igi2_frame.v50, igi2_frame.v52, 0, 0.0);
        ptQTask[34].tQTaskRefList.ptHead[5].pxObject = (void *)(__int64)((double)AnimController_nTicksPerFrame * igi2_frame.v62);
        goto LABEL_92;
      }
    }
    goto LABEL_76;
  }
  v8 = ptQTask[33].ptNext;
  v9 = ptQTask[77].ptPrev;
  igi2_frame.v56 = ptQTask[7].tQTaskRefList.ptTail;
  igi2_frame.v59 = 17;
  igi2_frame.v60 = v9;
  igi2_frame.v57 = v8;
  igi2_frame.v58 = 0;
  igi2_frame.ptAnim = nullptr;
  v10 = v8[1].ptPrev;
  if ( v10 )
    v11 = v10->tQTaskChildren.ptTail;
  else
    v11 = nullptr;
  v12 = v8[1].ptPrev;
  v13 = (void (__cdecl *)(struct QTask_s *, struct QReference_s **))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][v11->eQTaskType].pfHandler;
  if ( v12 )
    v14 = v12->tQTaskChildren.ptTail;
  else
    v14 = nullptr;
  v13(v14, &igi2_frame.v56);
  if ( !igi2_frame.ptAnim )
    goto LABEL_76;
  igi2_frame.v51 = igi2_frame.ptAnim;
  ptQTask[35].tQTaskRefList.ptHead = (struct QReference_s *)83;
  HumanAnim_SetUpperBodyAnimationFromHeader(ptQTask, igi2_frame.v51, 0, 0.0);
LABEL_92:
  HumanPlayer_SetWeaponTypeAnim(ptQTask, igi2_frame.v53, igi2_frame.eAnimType[0], igi2_frame.nTimeFrame);
  return result;
}

// source: j/0/human/humanplayer.c:19068  [size]
int __cdecl HumanPlayer_RequestUpperBody(struct QTask_s *ptQTask, int eUpperBody)
{
  ptQTask[77].ptParent = (struct QTask_s *)eUpperBody;
  return eUpperBody;
}

// source: j/0/human/humanplayer.c:19086  [size]
float __cdecl HumanPlayer_GetDeltaTranslationScale()
{
  return HumanPlayer_tGeneral.vDeltaTranslationScale;
}

// source: j/0/human/humanplayer.c:19099  [anchor-callee]
struct QTask_s *__cdecl HumanPlayer_New(
        struct QTask_s *ptParent,
        struct real64x3_t *ptPosition,
        float vGamma,
        char *zModel,
        int eTeam,
        int eNetworkID)
{
  struct QTask_s *v6; // eax
  struct QTask_s *v7; // ebx
  struct QTask_s **p_ptParent; // edx
  char *v9; // eax
  int v10; // edx
  char v11; // cl
  unsigned __int16 v12; // ax

  v6 = QTask_NewFn(ptParent, HumanPlayer_eQTaskType, &eNetworkID);
  v7 = v6;
  if ( !v6 )
    return nullptr;
  p_ptParent = &v6[10].ptParent;
  qmemcpy(&v6[10], ptPosition, 0x18u);
  v9 = zModel;
  v10 = (char *)p_ptParent - zModel;
  do
  {
    v11 = *v9;
    v9[v10] = *v9;
    ++v9;
  }
  while ( v11 );
  v12 = HumanPlayerInput_eQTaskType;
  *(float *)&v7[10].tQTaskRefList.ptMiddle = vGamma;
  v7[10].tQTaskRefList.ptTail = (struct QReference_s *)eTeam;
  QTask_NewFn(v7, v12, nullptr);
  QTask_TriggerQTaskEventRecursively(v7, ParameterList_eUpdateInternalDataQTaskEvent, nullptr);
  return v7;
}

// source: j/0/human/humanplayer.c:19147  [size]
enum bool __cdecl HumanPlayer_IsInvisible()
{
  return false;
}

// source: j/0/human/humanplayer.c:19166  [size]
enum bool __cdecl HumanPlayer_IsInvincible()
{
  return false;
}

// source: j/0/human/humanplayer.c:19190  [anchor-mhash]
enum bool __cdecl HumanPlayer_isInPlayOutsideSpawnArea()
{
  return HumanPlayer_ptQTask
      && LOBYTE(HumanPlayer_ptQTask[80].tQTaskChildren.ptTail)
      && SpawnArea_isInsideAnyActiveSpawnAreaForTeam(
           (int)HumanPlayer_ptQTask[10].tQTaskRefList.ptTail,
           (struct real64x3_t *)&HumanPlayer_ptQTask[1]) == false;
}

// source: j/0/human/humanplayer.c:19225  [size]
enum bool __cdecl HumanPlayer_isInPlay()
{
  return HumanPlayer_ptQTask && LOBYTE(HumanPlayer_ptQTask[80].tQTaskChildren.ptTail);
}

// source: j/0/human/humanplayer.c:19242  [anchor-mhash]
struct Result_s *__cdecl HumanPlayer_isDeadCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  if ( !HumanPlayer_ptQTask || LOBYTE(HumanPlayer_ptQTask[29].tQTaskRefList.ptHead) )
  {
    Rs.nResult = 1;
    HIDWORD(Rs.vResult) = 1072693248;
  }
  else
  {
    Rs.nResult = 0;
    HIDWORD(Rs.vResult) = 0;
  }
  Rs.zResult = (char *)&g_zInitialValue;
  LODWORD(Rs.vResult) = 0;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/human/humanplayer.c:19267  [anchor-mhash]
struct Result_s *__cdecl HumanPlayer_isInPlayCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  if ( HumanPlayer_ptQTask && LOBYTE(HumanPlayer_ptQTask[80].tQTaskChildren.ptTail) )
  {
    Rs.nResult = 1;
    HIDWORD(Rs.vResult) = 1072693248;
  }
  else
  {
    Rs.nResult = 0;
    HIDWORD(Rs.vResult) = 0;
  }
  Rs.zResult = (char *)&g_zInitialValue;
  LODWORD(Rs.vResult) = 0;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/human/humanplayer.c:19288  [size]
int __cdecl HumanPlayer_GetLogConsoleID()
{
  return HumanPlayer_tLogConsoleID;
}

// source: j/0/human/humanplayer.c:19301  [size]
int __cdecl HumanPlayer_GetConsoleID()
{
  return HumanPlayer_tConsoleID;
}

// source: j/0/human/humanplayer.c:19317  [anchor-strings]
struct Result_s *__cdecl HumanPlayer_PrintUpdateStatsCB(
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
  struct QTask_s *FirstChildOfType; // eax

  FirstChildOfType = QTask_GetFirstChildOfType(HumanPlayer_ptQTask, HumanPlayerInput_eQTaskType);
  _snprintf(
    igi2_frame.zTemp,
    0xFFu,
    "#time-sends=%d, #diff-sends=%d",
    FirstChildOfType[23].tQTaskRefList.ptHead,
    FirstChildOfType[23].tQTaskRefList.ptMiddle);
  NetworkCommand_SetEvalResponse(igi2_frame.zTemp);
  igi2_frame.Rs.nResult = 0;
  igi2_frame.Rs.vResult = 0.0;
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/human/humanplayer.c:19358  [anchor-strings]
void __cdecl HumanPlayer_Open()
{
  unsigned __int16 v0; // si
  __int16 v1; // ax
  __int16 v2; // ax
  __int16 v3; // ax
  unsigned __int16 v4; // si

  v0 = QTask_NewQTaskType("HumanPlayer", 3632, Human_eQTaskType, 0, 0);
  HumanPlayer_eQTaskType = v0;
  QTask_SetQTaskTypeGroup(v0, 1u);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, HumanPlayer_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, nullptr);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, HumanPlayer_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, RunDelayed_eQTaskEvent, HumanPlayer_RunDelayedHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, (void (__cdecl *)(struct QTask_s *))sub_4C3490);
  QTask_LinkQTaskEventHandlerFn(v0, 5, (void (__cdecl *)(struct QTask_s *, void *))HumanPlayer_EnterHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))HumanPlayer_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, HumanPlayer_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    DynCubeObj_eDynCubeObjRemoveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))sub_4C3E80);
  v1 = Human_eHumanUpdateQTaskEvent;
  if ( Human_eHumanUpdateQTaskEvent == 512 )
  {
    v1 = QTask_NewQTaskEventFn(0, "HumanUpdate");
    v0 = HumanPlayer_eQTaskType;
    Human_eHumanUpdateQTaskEvent = v1;
  }
  QTask_LinkQTaskEventHandlerFn(v0, v1, HumanPlayer_HumanUpdateHandler);
  QTask_LinkQTaskEventHandlerFn(v0, GameFunctions_eWeaponHitQTaskEvent, HumanPlayer_WeaponHitHandler);
  QTask_LinkQTaskEventHandlerFn(v0, GameFunctions_eExplosionHitQTaskEvent, HumanPlayer_ExplosionHitHandler);
  QTask_LinkQTaskEventHandlerFn(v0, Human_eCloseCombatDamageQTaskEvent, HumanPlayer_CloseCombatDamageHandler);
  QTask_LinkQTaskEventHandlerFn(v0, GameFunctions_eElectricDamageQTaskEvent, HumanPlayer_ElectricDamageHandler);
  QTask_LinkQTaskEventHandlerFn(v0, FlashBang_eFlashBangQTaskEvent, HumanPlayer_FlashBangHandler);
  QTask_LinkQTaskEventHandlerFn(v0, NetManager_eGameMessageDamageQTaskEvent, HumanPlayer_NetworkDamageHandler);
  QTask_LinkQTaskEventHandlerFn(v0, StatusScreen_eStatusDisplayQTaskEvent, HumanPlayer_StatusDisplayHandler);
  v2 = ComputerObject_eDrawComputerObjectQTaskEvent;
  if ( ComputerObject_eDrawComputerObjectQTaskEvent == 512 )
  {
    v2 = QTask_NewQTaskEventFn(0x200u, "DrawComputerObject");
    v0 = HumanPlayer_eQTaskType;
    ComputerObject_eDrawComputerObjectQTaskEvent = v2;
  }
  QTask_LinkQTaskEventHandlerFn(v0, v2, HumanPlayer_DrawComputerObjectHandler);
  QTask_LinkQTaskEventHandlerFn(v0, Weapon_eGetParentParametersQTaskEvent, HumanPlayer_WeaponGetParentParametersHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    AnimTrigger_eTriggerAnimTriggerQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))sub_4C2360);
  QTask_LinkQTaskEventHandlerFn(v0, ActionMenuScreen_eDrawActionItemQTaskEvent, HumanPlayer_DrawActionItemHandler);
  QTask_LinkQTaskEventHandlerFn(v0, Weapon_eGetWeaponPrecisionQTaskEvent, HumanPlayer_GetWeaponPrecisionHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    GunPickup_eGunPickupQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))sub_4C4BF0);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Human_eUpdateInternalDataAfterCarryoverQTaskEvent, nullptr);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Level_eUpdateInternalDataAfterLoadEvent, sub_4C3E30);
  v3 = Smoke_eSmokeDamageEvent;
  if ( Smoke_eSmokeDamageEvent == 512 )
  {
    v3 = QTask_NewQTaskEventFn(0, "SmokeDamage");
    v0 = HumanPlayer_eQTaskType;
    Smoke_eSmokeDamageEvent = v3;
  }
  QTask_LinkQTaskEventHandlerFn(v0, v3, HumanPlayer_SmokeDamageHandler);
  HumanPlayer_ptParameterList = ParameterList_Derive(Human_ptParameterList, 7);
  ParameterList_AddParameter(
    HumanPlayer_ptParameterList,
    0x1C0u,
    Level_eParameterTypeString16,
    "1st Person Model",
    7u,
    nullptr);
  ParameterList_AddParameterMinMax(
    HumanPlayer_ptParameterList,
    0xD3Cu,
    Level_eParameterTypeReal32,
    "Visibility Gamma",
    7u,
    0.01,
    2.0);
  ParameterList_AddParameterMinMax(
    HumanPlayer_ptParameterList,
    0xD40u,
    Level_eParameterTypeReal32,
    "Visibility Minimum",
    7u,
    0.01,
    1.0);
  ParameterList_AddParameterMinMax(
    HumanPlayer_ptParameterList,
    0xD44u,
    Level_eParameterTypeReal32,
    "Visibility Maximum",
    7u,
    0.01,
    1.0);
  ParameterList_AddParameter(
    HumanPlayer_ptParameterList,
    0xD48u,
    Level_eParameterTypePushButton,
    "Reset Visibility Parameters",
    6u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptParameterList,
    0xC9Au,
    Level_eParameterTypebool8,
    "Carry over weapons from previous mission",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptParameterList,
    0xDDCu,
    Level_eParameterTypeVarString,
    "DisableSpottedIncrease",
    7u,
    nullptr);
  Symbol_Register(
    "DefineHumanPlayerWeaponCycle",
    HumanPlayer_DefineWeaponCycleCB,
    nullptr,
    -1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "DefineHumanPlayerAmmoLimit",
    HumanPlayer_DefineAmmoLimitCB,
    nullptr,
    -1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "HumanPlayer_isInPlay",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))HumanPlayer_isInPlayCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "HumanPlayer_isDead",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))HumanPlayer_isDeadCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "HumanPlayer_DisableAllWeapons",
    HumanPlayer_DisableAllWeapons,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "HumanPlayer_EnableWeapon",
    HumanPlayer_EnableWeapon,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "updatestats",
    HumanPlayer_PrintUpdateStatsCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  v4 = HumanPlayer_eQTaskType;
  QTask_LinkQTaskEventHandlerFn(
    HumanPlayer_eQTaskType,
    Serialize_eGetSerializeParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))HumanPlayer_GetSerializeParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v4, Serialize_eDeSerializeQTaskEvent, HumanPlayer_DeSerializeHandler);
  QTask_LinkQTaskEventHandlerFn(v4, Serialize_eSerializeQTaskEvent, HumanPlayer_SerializeHandler);
  HumanPlayer_ptSerializeParameterList = ParameterList_Derive(Human_ptSerializeParameterList, 72);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xBA8u,
    SerializeStruct_eParameterType,
    "Action",
    7u,
    Human_ptSerializeStateParameterList);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xBF8u,
    Level_eParameterTypebool8,
    "isLockAction",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xBF9u,
    Level_eParameterTypebool8,
    "isWalk",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xBFCu,
    Level_eParameterTypeInt32,
    "nWeaponCycle",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xC00u,
    Level_eParameterTypeInt32,
    "nChangeWeaponID",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xC04u,
    Level_eParameterTypeInt32,
    "nWeaponCategory",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xC0Cu,
    Level_eParameterTypeInt32,
    "nFireType",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xC10u,
    Level_eParameterTypeInt32,
    "ePrecisionType",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xC1Cu,
    Level_eParameterTypeReal32,
    "vIdealWeaponPrecision",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xC20u,
    Level_eParameterTypeReal32,
    "vActualWeaponPrecision",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xC14u,
    Level_eParameterTypeReal32,
    "vIdealModifiedPrecision",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xC18u,
    Level_eParameterTypeReal32,
    "vActualModifiedPrecision",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xC24u,
    Level_eParameterTypeInt32,
    "eCurrentUpperBody",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xC28u,
    Level_eParameterTypeInt32,
    "eRequestedUpperBody",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xC2Cu,
    Level_eParameterTypeInt32,
    "nHumanPlayerActivateTime",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xC30u,
    Level_eParameterTypeInt32,
    "nHumanPlayerActivateTimer",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xC34u,
    Level_eParameterTypebool8,
    "isProgressBar",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xC38u,
    Level_eParameterTypeInt32,
    "nHumanPlayerHealTimer",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xC3Cu,
    Level_eParameterTypeInt32,
    "nCabinetAnim",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xC40u,
    Level_eParameterTypebool8,
    "isInitClimbLadder",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xC41u,
    Level_eParameterTypebool8,
    "isClimbLadder",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xC42u,
    Level_eParameterTypebool8,
    "isDeInitClimbLadder",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xC43u,
    Level_eParameterTypebool8,
    "isLadderActivateTop",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xC44u,
    Level_eParameterTypeInt32,
    "nSteps",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xC48u,
    Level_eParameterTypeInt32,
    "nCurrentStep",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xC4Cu,
    Level_eParameterTypeInt32,
    "nStepChange",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xC50u,
    Level_eParameterTypebool8,
    "isInitClimbFence",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xC51u,
    Level_eParameterTypebool8,
    "isClimbFence",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xC52u,
    Level_eParameterTypebool8,
    "isDeInitClimbFence",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xC53u,
    Level_eParameterTypebool8,
    "isInitClimbWire",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xC54u,
    Level_eParameterTypebool8,
    "isClimbWire",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xC58u,
    Level_eParameterTypeInt32,
    "nWireTimeFrame",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xC5Cu,
    Level_eParameterTypeInt32,
    "nClimbWireSoundSequence",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xC60u,
    Level_eParameterTypebool8,
    "isInitSlideWire",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xC61u,
    Level_eParameterTypebool8,
    "isSlideWire",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xC64u,
    Level_eParameterTypeReal32x3,
    "tSlideWireDirection",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xC70u,
    Level_eParameterTypeReal32,
    "vSlideWireSpeed",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xC74u,
    Level_eParameterTypebool8,
    "isInitPeek",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xC75u,
    Level_eParameterTypebool8,
    "isPeek",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xC78u,
    Level_eParameterTypeReal32,
    "avDamageFlash0",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xC7Cu,
    Level_eParameterTypeReal32,
    "avDamageFlash1",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xC80u,
    Level_eParameterTypeReal32,
    "avDamageFlash2",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xC84u,
    Level_eParameterTypeReal32,
    "avDamageFlash3",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xC88u,
    Level_eParameterTypeReal32,
    "vFlashBangFlash",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xC8Cu,
    Level_eParameterTypeInt32,
    "nElectricDamageTimeOut",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xC90u,
    Level_eParameterTypebool8,
    "isDisplayPlayer",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xC91u,
    Level_eParameterTypebool8,
    "isPlayerActivateLocked",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xC94u,
    Level_eParameterTypeInt32,
    "nSavesUsed",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xC98u,
    Level_eParameterTypebool8,
    "isSwimming",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xC99u,
    Level_eParameterTypebool8,
    "isUnderWater",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xC9Au,
    Level_eParameterTypebool8,
    "isWeaponsCarryOver",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xC9Bu,
    Level_eParameterTypebool8,
    "isQuitComputer",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xC9Cu,
    Level_eParameterTypeInt32,
    "eWeaponStatus",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xCA0u,
    Level_eParameterTypeInt32,
    "nGrenadeTickTime",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xCA4u,
    Level_eParameterTypeInt32,
    "nGrenadeHeldTime",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xCA8u,
    Level_eParameterTypeReal32,
    "vMovementSpeedScale",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xCACu,
    SerializeArray_eParameterType,
    "tStateContext",
    7u,
    (void *)0x68);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xD14u,
    Level_eParameterTypeInt32,
    "nSpeedHack",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xD18u,
    Level_eParameterTypeInt32,
    "nPerfectShotTimer",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xD1Cu,
    Level_eParameterTypebool8,
    "isPrintPlayerPosition",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xD1Du,
    Level_eParameterTypebool8,
    "isInvisible",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xD1Eu,
    Level_eParameterTypebool8,
    "isInvincible",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xD1Fu,
    Level_eParameterTypebool8,
    "isUnlimitedAmmo",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xD20u,
    Level_eParameterTypebool8,
    "isFire",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xD21u,
    Level_eParameterTypebool8,
    "isFirstFire",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xD24u,
    Level_eParameterTypeInt32,
    "nJumpWaitTimer",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xD28u,
    Level_eParameterTypeReal32,
    "vCrossHairDamping",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayer_ptSerializeParameterList,
    0xD2Cu,
    Level_eParameterTypeInt32,
    "nTBATimeout",
    7u,
    nullptr);
  Symbol_Register(
    "TASKTYPE_HUMANPLAYER",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)HumanPlayer_eQTaskType,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  HumanPlayer_tConsoleID = DebugConsole_Alloc("HumanPlayer", 100);
  HumanPlayer_tLogConsoleID = DebugConsole_Alloc((char *)&g_zMessage_0.anDR[33], 100);
  HumanPlayer_InitStateTable();
  Symbol_Register(
    (char *)&g_zMessage_0.anDR[24],
    HumanPlayer_GetPrimaryWeaponModel,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&g_zMessage_0.anDR[16],
    HumanPlayer_GetPrimaryWeaponID,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  HumanPlayer_bAreaActivateCriteria = AreaActivateQTask_RegisterCriteria(
                                        (char *)&g_zMessage_0.anDR[10],
                                        HumanPlayer_AreaActivateCB);
}

// source: j/0/human/humanplayer.c:19522  [anchor-hash]
void __cdecl HumanPlayer_Close()
{
  int v0; // ecx
  int i; // eax
  int v2; // eax
  int v3; // esi
  int v4; // esi

  v0 = HumanPlayer_bAreaActivateCriteria;
  for ( i = 0; (v0 & 1) == 0; ++i )
    v0 >>= 1;
  v2 = i;
  AreaActivate_atCriteria[v2].isUsed = 0;
  Symbol_Remove(AreaActivate_atCriteria[v2].zName);
  DebugConsole_DeAlloc(HumanPlayer_tConsoleID);
  DebugConsole_DeAlloc(HumanPlayer_tLogConsoleID);
  if ( HumanPlayer_ptParameterList )
  {
    v3 = *(_DWORD *)((unsigned int)&HumanPlayer_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v3);
    memset(*(void **)(v3 + 8), 0xCDu, *(_DWORD *)(v3 + 16));
    free((void *)v3);
  }
  if ( HumanPlayer_ptSerializeParameterList )
  {
    v4 = *(_DWORD *)((unsigned int)&HumanPlayer_ptSerializeParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v4);
    memset(*(void **)(v4 + 8), 0xCDu, *(_DWORD *)(v4 + 16));
    free((void *)v4);
  }
  QTask_DeleteQTaskType(HumanPlayer_eQTaskType);
}

// source: j/0/human/humanplayer.c:19548  [size]
struct QTask_s *__cdecl HumanPlayer_GetQTask()
{
  return HumanPlayer_ptQTask;
}

// source: j/0/human/humanplayer.c:19561  [size]
struct StateAnimData_t *__cdecl HumanPlayer_GetStateAnimData()
{
  return HumanPlayer_atStateAnimData;
}

// source: j/0/human/humanplayer.c:19574  [size]
struct DamagePartData_t *__cdecl HumanPlayer_GetDamagePartDataMultiplayer()
{
  return HumanPlayer_atDamagePartDataMultiplayer;
}

// source: j/0/human/humanplayer.c:19588  [anchor-callee]
void __cdecl HumanPlayer_LeaveZoomAlternateFireMode(struct QTask_s *ptQTask)
{
  struct QTask_s *v1; // ecx
  struct QTask_s *ptNext; // esi
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptTail; // edi
  struct QTask_s *v5; // eax
  enum WeaponOverlayStatus_e v6; // [esp+0h] [ebp-10h]

  ptNext = ptQTask[33].ptNext;
  if ( ptNext )
  {
    if ( ptNext[4].ptNext )
    {
      ptPrev = ptNext[1].ptPrev;
      if ( ptPrev )
      {
        ptTail = ptPrev->tQTaskChildren.ptTail;
        if ( ptTail )
        {
          if ( ptTail[33].ptNext == (struct QTask_s *)Zoom_eQTaskType )
          {
            if ( Game_eGameMode == GAME_GAMEMODE_SINGLEPLAYER
              || ptTail[3].tQTaskRefList.ptTail == (struct QReference_s *)Script_ParseLineInt32((char *)&g_zSoundDefPrefix.eQTaskType) )
            {
              Weapon_SetOverlayStatus(v1, v6, 0, (int)ptQTask[33].ptNext);
            }
            else
            {
              ptNext[1].ptParent = nullptr;
              Weapon_Fire(ptNext, 1);
              v5 = ptQTask[33].ptNext;
              v5[3].tQTaskRefList.ptHead = (struct QReference_s *)1;
              v5[1].tQTaskChildren.ptTail = nullptr;
            }
          }
        }
      }
    }
  }
}

// source: j/0/human/humanplayer.c:19629  [anchor-mhash]
struct QTask_s *__cdecl HumanPlayer_SetQuickLoadSlot(struct QTask_s *ptQTask, int iSlot)
{
  if ( Game_eGameMode )
    ptQTask[85].tQTaskChildren.ptTail = nullptr;
  else
    ptQTask[85].tQTaskChildren.ptTail = (struct QTask_s *)(iSlot + 1);
  return ptQTask;
}

// source: j/0/human/humanplayer.c:19654  [size]
int __cdecl HumanPlayer_FinishSaveToSlot(struct QTask_s *ptQTask, int iSlot)
{
  int result; // eax
  BOOL v3; // edx

  result = iSlot + 1;
  v3 = Game_eGameMode != GAME_GAMEMODE_SINGLEPLAYER;
  ptQTask[85].tQTaskChildren.ptMiddle = (struct QTask_s *)result;
  ptQTask[85].tQTaskChildren.ptTail = v3 ? nullptr : (struct QTask_s *)result;
  return result;
}

// source: j/0/human/humanplayer.c:19673  [size]
struct QTask_s *__cdecl HumanPlayer_BeginSaveToSlot(
        struct QTask_s *ptQTask,
        int iSlot)
{
  ptQTask[85].ptPrev = (struct QTask_s *)(iSlot + 1);
  ++*(int *)&ptQTask[80].tQTaskRefList.ptHead;
  return ptQTask;
}

// source: j/0/human/humanplayer.c:19692  [size]
int __cdecl HumanPlayer_LoadFromSlot(struct QTask_s *ptQTask, int iSlot)
{
  int result; // eax
  BOOL v3; // edx

  result = iSlot + 1;
  v3 = Game_eGameMode != GAME_GAMEMODE_SINGLEPLAYER;
  ptQTask[85].tQTaskChildren.ptHead = (struct QTask_s *)result;
  ptQTask[85].tQTaskChildren.ptTail = v3 ? nullptr : (struct QTask_s *)result;
  return result;
}

// source: j/0/human/humanplayer.c:19711  [size]
struct QTask_s *__cdecl HumanPlayer_QuitComputer(struct QTask_s *ptQTask)
{
  HIBYTE(ptQTask[80].tQTaskRefList.ptMiddle) = 1;
  return ptQTask;
}

// source: j/0/human/humanplayer.c:19732  [anchor-callee]
float __cdecl HumanPlayer_GetBatteryLevel(struct QTask_s *ptQTask)
{
  double v1; // st7
  enum GameDifficulty_e eDifficultyLevel; // eax
  __int32 v3; // eax
  double v4; // st7

  v1 = 5.0;
  if ( 2752 * Config_tConfig.iActiveProfile != -7392072 )
  {
    eDifficultyLevel = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eDifficultyLevel;
    if ( eDifficultyLevel )
    {
      v3 = eDifficultyLevel - 1;
      if ( v3 )
      {
        if ( v3 == 1 )
          return 0.0;
      }
      else
      {
        v1 = 3.0;
      }
    }
    else
    {
      v1 = 5.0;
    }
  }
  v4 = (v1 - (double)(int)ptQTask[80].tQTaskRefList.ptHead) / v1;
  if ( v4 < 0.0 )
    return 0.0;
  return v4;
}

// source: j/0/human/humanplayer.c:19773  [anchor-mhash]
enum bool __cdecl HumanPlayer_GetQuickLoadSlot(
        struct QTask_s *ptQTask,
        int *piSlot)
{
  struct QTask_s *ptTail; // eax

  ptTail = ptQTask[85].tQTaskChildren.ptTail;
  if ( !ptTail )
    return false;
  *piSlot = (int)(&ptTail[-1].isInMemPool + 1);
  return true;
}

// source: j/0/human/humanplayer.c:19798  [anchor-callee]
enum bool __cdecl HumanPlayer_IsSaveAllowed(struct QTask_s *ptQTask)
{
  return !BYTE1(ptQTask[80].tQTaskChildren.ptTail)
      && !LOBYTE(ptQTask[76].tQTaskRefList.ptMiddle)
      && Game_eGameMode == GAME_GAMEMODE_SINGLEPLAYER;
}

// source: j/0/human/humanplayer.c:19821  [anchor-callee]
struct HumanPlayer_t *__cdecl HumanPlayer_FillGameMessageUpdate(
        struct HumanPlayer_t *ptHumanPlayer,
        struct ClientGameMessageUpdateBody_s *ptGameMessage)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vOutAlpha; };
    struct { char igi2_o1[8]; float vOutGamma; };
    struct { char igi2_o2[12]; struct real64x3_t tPos; };
    char igi2_extent[40];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptHumanViewQTask; // edi
  float vY; // edx
  float vZ; // eax
  float v6; // ecx
  double i; // st7
  float vX; // edx
  float v9; // edi
  struct HumanPlayer_t *result; // eax

  ptHumanViewQTask = ptHumanPlayer->tHuman.ptHumanViewQTask;
  HumanPlayer_ExtrapolatePos(&ptHumanPlayer->tHuman, &igi2_frame.tPos);
  igi2_frame.tPos.vX = igi2_frame.tPos.vX * 0.000244140625;
  igi2_frame.tPos.vY = igi2_frame.tPos.vY * 0.000244140625;
  igi2_frame.tPos.vZ = igi2_frame.tPos.vZ * 0.000244140625;
  World_SetInt32CentimeterFromReal64Meter(&igi2_frame.tPos, &ptGameMessage->tPosition);
  vY = ptHumanPlayer->tHuman.tWorldSpeed.vY;
  vZ = ptHumanPlayer->tHuman.tWorldSpeed.vZ;
  *(float *)&igi2_frame.tPos.vX = ptHumanPlayer->tHuman.tWorldSpeed.vX;
  v6 = *(float *)&ptHumanViewQTask[11].eQTaskType;
  *(float *)&igi2_frame.tPos.vX = *(float *)&igi2_frame.tPos.vX * 30.0;
  igi2_frame.vOutAlpha = v6;
  *((float *)&igi2_frame.tPos.vX + 1) = vY * 30.0;
  *(float *)&igi2_frame.tPos.vY = vZ * 30.0;
  for ( i = ptHumanPlayer->tHuman.vIdealGamma; i < 0.0; i = i + 6.2831854820251465 )
    ;
  for ( ; i > 6.283185307179589; i = i - 6.2831854820251465 )
    ;
  vX = ptHumanPlayer->tGroundMovementSpeed.vX;
  igi2_frame.vOutGamma = i - 3.1415927410125732;
  v9 = ptHumanPlayer->tGroundMovementSpeed.vY;
  ptGameMessage->eAnimState = ptHumanPlayer->tHuman.tHumanAnim.iStateLastUsedToSetMainAnimation;
  ptGameMessage->eUpperBody = ptHumanPlayer->nActivateTime;
  ptGameMessage->isShowPlayer = ptHumanPlayer->isSwimming;
  Client_CheckCompression(
    (struct ClientMessageCompression_s *)&ptHumanPlayer->tCompressionState.nGamma,
    (struct real32x3_t *)&igi2_frame.tPos,
    v6,
    vX,
    igi2_frame.vOutGamma,
    v9);
  Client_CompressOutput(ptGameMessage, (struct real32x3_t *)&igi2_frame.tPos, igi2_frame.vOutAlpha, vX, igi2_frame.vOutGamma, v9);
  return result;
}

// source: j/0/human/humanplayer.c:19915  [anchor-callee]
void __cdecl HumanPlayer_MoveOnGround(
        struct HumanPlayer_t *ptHumanPlayer,
        float vLocalYTargetSpeed,
        float vMaxYDelta,
        float vLocalXTargetSpeed,
        float vMaxXDelta)
{
  double v5; // st7
  double v6; // st6
  double v7; // st7
  double v8; // st6
  double v9; // st5
  double v10; // st6
  double v11; // st7
  double v12; // st6
  float Real32x3_RotateInverse_tTemp; // [esp+0h] [ebp-18h]
  float Real32x3_RotateInverse_tTempa; // [esp+0h] [ebp-18h]
  float Real32x3_RotateInverse_tTemp_4; // [esp+4h] [ebp-14h]
  float Real32x3_RotateInverse_tTemp_4a; // [esp+4h] [ebp-14h]
  float Real32x3_RotateInverse_tTemp_8; // [esp+8h] [ebp-10h]
  float ptHumanPlayera = *(float *)&vLocalYTargetSpeed; // [esp+1Ch] [ebp+4h] ARGSLOT
  float vLocalYTargetSpeeda = *(float *)&vMaxYDelta; // [esp+20h] [ebp+8h] ARGSLOT

  Real32x3_RotateInverse_tTemp = *(float *)&ptHumanPlayer->ptPrevWeaponType
                               * ptHumanPlayer->tHuman.tBoneDynCubeObj.tModelObj.tOrientation.tY.vX
                               + ptHumanPlayer->tGroundMovementSpeed.vZ
                               * ptHumanPlayer->tHuman.tBoneDynCubeObj.tModelObj.tOrientation.tX.vX
                               + ptHumanPlayer->tHuman.tBoneDynCubeObj.tModelObj.tOrientation.tZ.vX
                               * *(float *)&ptHumanPlayer->ptKillerQTaskRef;
  Real32x3_RotateInverse_tTemp_4 = ptHumanPlayer->tGroundMovementSpeed.vZ
                                 * ptHumanPlayer->tHuman.tBoneDynCubeObj.tModelObj.tOrientation.tX.vY
                                 + ptHumanPlayer->tHuman.tBoneDynCubeObj.tModelObj.tOrientation.tZ.vY
                                 * *(float *)&ptHumanPlayer->ptKillerQTaskRef
                                 + *(float *)&ptHumanPlayer->ptPrevWeaponType
                                 * ptHumanPlayer->tHuman.tBoneDynCubeObj.tModelObj.tOrientation.tY.vY;
  v5 = vLocalYTargetSpeed - Real32x3_RotateInverse_tTemp_4;
  v6 = -vMaxYDelta;
  if ( v6 <= v5 )
  {
    if ( vMaxYDelta < v5 )
      v5 = vMaxYDelta;
  }
  else
  {
    ptHumanPlayera = v6;
    v5 = ptHumanPlayera;
  }
  v7 = v5 + Real32x3_RotateInverse_tTemp_4;
  v8 = vLocalXTargetSpeed - Real32x3_RotateInverse_tTemp;
  v9 = -vMaxXDelta;
  if ( v9 <= v8 )
  {
    if ( vMaxXDelta < v8 )
      v8 = vMaxXDelta;
  }
  else
  {
    vLocalYTargetSpeeda = v9;
    v8 = vLocalYTargetSpeeda;
  }
  v10 = v8 + Real32x3_RotateInverse_tTemp;
  Real32x3_RotateInverse_tTempa = v10 * ptHumanPlayer->tHuman.tBoneDynCubeObj.tModelObj.tOrientation.tX.vX
                                + v7 * ptHumanPlayer->tHuman.tBoneDynCubeObj.tModelObj.tOrientation.tX.vY
                                + ptHumanPlayer->tHuman.tBoneDynCubeObj.tModelObj.tOrientation.tX.vZ * 0.0;
  Real32x3_RotateInverse_tTemp_4a = v7 * ptHumanPlayer->tHuman.tBoneDynCubeObj.tModelObj.tOrientation.tY.vY
                                  + v10 * ptHumanPlayer->tHuman.tBoneDynCubeObj.tModelObj.tOrientation.tY.vX
                                  + ptHumanPlayer->tHuman.tBoneDynCubeObj.tModelObj.tOrientation.tY.vZ * 0.0;
  v11 = v10 * ptHumanPlayer->tHuman.tBoneDynCubeObj.tModelObj.tOrientation.tZ.vX
      + v7 * ptHumanPlayer->tHuman.tBoneDynCubeObj.tModelObj.tOrientation.tZ.vY;
  v12 = ptHumanPlayer->tHuman.tBoneDynCubeObj.tModelObj.tOrientation.tZ.vZ * 0.0;
  ptHumanPlayer->tGroundMovementSpeed.vZ = Real32x3_RotateInverse_tTempa;
  *(float *)&ptHumanPlayer->ptPrevWeaponType = Real32x3_RotateInverse_tTemp_4a;
  Real32x3_RotateInverse_tTemp_8 = v11 + v12;
  *(float *)&ptHumanPlayer->ptKillerQTaskRef = Real32x3_RotateInverse_tTemp_8;
}

// source: j/0/human/humanplayer.c:19946  [anchor-strings]
struct HumanPlayer_t *__cdecl HumanPlayer_MaintainRunningSound(struct HumanPlayer_t *ptHumanPlayer)
{
  int nState; // eax
  struct HumanPlayer_t *result; // eax
  struct QReference_s *iPickupGameItemID; // eax

  nState = ptHumanPlayer->tHuman.tState.nState;
  if ( nState < 3 || nState > 10 )
  {
    QTask_DeleteQTaskAndQTaskRefSafe((struct QReference_s **)&ptHumanPlayer->iPickupGameItemID);
  }
  else
  {
    result = (struct HumanPlayer_t *)ptHumanPlayer->iPickupGameItemID;
    if ( !result || !result->tHuman.tBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.tQTaskChildren.ptHead )
    {
      iPickupGameItemID = (struct QReference_s *)ptHumanPlayer->iPickupGameItemID;
      if ( iPickupGameItemID )
      {
        QReference_Delete(iPickupGameItemID, &QTask_tQTaskRefPool);
        ptHumanPlayer->iPickupGameItemID = 0;
      }
      result = (struct HumanPlayer_t *)SoundSys_NewSoundFn(
                                         ptHumanPlayer->tHuman.ptHumanViewQTask,
                                         (char *)&g_zMessage_0.anDR[6]);
      if ( result )
      {
        result = (struct HumanPlayer_t *)QTask_NewQTaskRef(&result->tHuman.tBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask);
        ptHumanPlayer->iPickupGameItemID = (int)result;
      }
    }
  }
  return result;
}

// source: j/0/human/humanplayer.c:19998  [anchor-strings]
void __cdecl HumanPlayer_MaintainFatigue(struct HumanPlayer_t *ptHumanPlayer)
{
  int nState; // eax
  double v2; // st7
  float vVisibilityGamma; // eax
  struct QTask_s *v4; // esi
  double v5; // st7
  struct QTask_s *v6; // eax
  float vVolume; // [esp+0h] [ebp-4h]
  float vVolumea; // [esp+0h] [ebp-4h]

  nState = ptHumanPlayer->tHuman.tState.nState;
  if ( nState < 3 || nState > 10 )
    v2 = -*(float *)&ptHumanPlayer->ptFatigueStopLoopRef;
  else
    v2 = 1.0 - *(float *)&ptHumanPlayer->ptFatigueStopLoopRef;
  if ( v2 >= -0.006666666828095913 )
  {
    if ( v2 > 0.0016666667070239782 )
      v2 = 0.0016666667070239782;
  }
  else
  {
    v2 = -0.006666666828095913;
  }
  vVolume = v2 + *(float *)&ptHumanPlayer->ptFatigueStopLoopRef;
  *(float *)&ptHumanPlayer->ptFatigueStopLoopRef = vVolume;
  if ( v2 < 0.0 )
  {
    if ( LODWORD(ptHumanPlayer->vVisibilityGamma) )
    {
      QTask_DeleteQTaskAndQTaskRefSafe((struct QReference_s **)&ptHumanPlayer->vVisibilityGamma);
      v6 = SoundSys_NewSoundFn(
             ptHumanPlayer->tHuman.ptHumanViewQTask,
             (char *)&g_zMessage_0.tReceiveTimeBuffer.aReceiveTime[4]);
      if ( v6 )
        LODWORD(ptHumanPlayer->vVisibilityMin) = QTask_NewQTaskRef(v6);
    }
  }
  else
  {
    vVisibilityGamma = ptHumanPlayer->vVisibilityGamma;
    if ( vVisibilityGamma == 0.0 )
      v4 = nullptr;
    else
      v4 = *(struct QTask_s **)(LODWORD(vVisibilityGamma) + 8);
    v5 = (vVolume - 0.699999988079071) * 3.3333332538604736;
    if ( v5 >= 0.0 )
    {
      if ( v4
        || (QTask_DeleteQTaskAndQTaskRefSafe((struct QReference_s **)&ptHumanPlayer->vVisibilityMin),
            v4 = SoundSys_NewSoundFn(ptHumanPlayer->tHuman.ptHumanViewQTask, (char *)&g_zMessage_0.anDR[2]),
            LODWORD(ptHumanPlayer->vVisibilityGamma) = QTask_NewQTaskRef(v4),
            v4) )
      {
        vVolumea = v5;
        SoundSys_SetSoundVolumes(v4, vVolumea, 1.0);
      }
    }
    else
    {
      QTask_DeleteQTaskAndQTaskRefSafe((struct QReference_s **)&ptHumanPlayer->vVisibilityGamma);
    }
  }
}

// source: j/0/human/humanplayer.c:20087  [size]
int __cdecl HumanPlayer_GetNumberOfAmmoLimits()
{
  return HumanPlayer_tAmmoLimit.nAmmoLimit;
}

// source: j/0/human/humanplayer.c:20100  [size]
int __cdecl HumanPlayer_GetAmmoLimitID(int iAmmoLimit)
{
  return HumanPlayer_tAmmoLimit.atAmmoLimit[iAmmoLimit].nAmmoID;
}

// source: j/0/human/humanplayer.c:20113  [size]
int __cdecl HumanPlayer_GetMaxAmmoLimit(int iAmmoLimit)
{
  return HumanPlayer_tAmmoLimit.atAmmoLimit[iAmmoLimit].nMaxAmmo;
}

// source: j/0/human/humanplayer.c:20127  [size]
void __cdecl HumanPlayer_CheckViewCollision(struct HumanPlayer_t *ptHumanPlayer)
{
  #pragma pack(push, 1)
  union
  {
    struct { float x; };
    struct { float xa; };
    struct { char igi2_o2[20]; float vReal32; };
    struct { char igi2_o3[20]; float vReal32a; };
    struct { char igi2_o4[20]; float vReal32b; };
    struct { char igi2_o5[24]; float tDirection; };
    struct { char igi2_o6[28]; float tDirection_4; };
    struct { char igi2_o7[32]; float tDirection_8; };
    struct { char igi2_o8[32]; float tDirection_8a; };
    struct { char igi2_o9[36]; double avDist[3]; };
    struct { char igi2_o10[60]; struct ObjectCollisionEvaluateContext_t tObjectCollisionEvaluateContext; };
    struct { char igi2_o11[68]; struct real64x3_t atStart[2]; };
    struct { char igi2_o12[116]; struct QIntersection_s atIntersection[2]; };
    char igi2_extent[360];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptHumanViewQTask; // ebp
  double vY; // st7
  double v3; // st6
  long double v4; // st7
  double v5; // st7
  double v6; // st6
  double v7; // st5
  double v8; // st4
  double v9; // st7
  double v10; // rt2
  double v11; // st4
  double v12; // st7
  double v13; // st7
  struct QTask_s *ptNext; // eax
  double v15; // st7
  double v16; // st6
  double v17; // st5
  double v18; // st4
  double v19; // st7
  double v20; // rt2
  double v21; // st4
  double v22; // st7
  double v23; // st7
  double v24; // st7

  ptHumanViewQTask = ptHumanPlayer->tHuman.ptHumanViewQTask;
  if ( ptHumanPlayer->tHuman.ePose == 2 )
  {
    igi2_frame.tDirection_8a = ptHumanPlayer->tHuman.tBoneDynCubeObj.tModelObj.tOrientation.tZ.vY;
    vY = ptHumanPlayer->tHuman.tBoneDynCubeObj.tModelObj.tOrientation.tY.vY;
    v3 = ptHumanPlayer->tHuman.tBoneDynCubeObj.tModelObj.tOrientation.tX.vY * 2048.0;
    qmemcpy(igi2_frame.atStart, &ptHumanViewQTask[10].tQTaskChildren, 0x18u);
    igi2_frame.tDirection = v3;
    igi2_frame.tDirection_4 = vY * 2048.0;
    igi2_frame.tDirection_8 = igi2_frame.tDirection_8a * 2048.0;
    igi2_frame.atStart[0].vX = igi2_frame.tDirection + igi2_frame.atStart[0].vX;
    igi2_frame.tObjectCollisionEvaluateContext.tCollisionEvaluateContext.ptQTask = &ptHumanPlayer->tHuman.tBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask;
    igi2_frame.avDist[0] = -4096.0;
    igi2_frame.avDist[1] = 4096.0;
    igi2_frame.atStart[0].vY = igi2_frame.tDirection_4 + igi2_frame.atStart[0].vY;
    igi2_frame.atStart[0].vZ = igi2_frame.tDirection_8 + igi2_frame.atStart[0].vZ;
    qmemcpy(&igi2_frame.atStart[1], igi2_frame.atStart, sizeof(struct real64x3_t));
    World_GetNextZ(
      Game_ptGame->ptWorld,
      igi2_frame.atIntersection,
      igi2_frame.atStart,
      2,
      igi2_frame.avDist,
      GameFunctions_eObjectCollisionEvaluateQTaskEvent,
      &igi2_frame.tObjectCollisionEvaluateContext.tCollisionEvaluateContext,
      Forest_bQTaskGroup | 0x98000000);
    if ( igi2_frame.tDirection != 0.0 || igi2_frame.tDirection_4 != 0.0 || igi2_frame.tDirection_8 != 0.0 )
    {
      v4 = 1.0 / sqrt(igi2_frame.tDirection * igi2_frame.tDirection + igi2_frame.tDirection_4 * igi2_frame.tDirection_4 + igi2_frame.tDirection_8 * igi2_frame.tDirection_8);
      igi2_frame.tDirection = igi2_frame.tDirection * v4;
      igi2_frame.tDirection_4 = igi2_frame.tDirection_4 * v4;
      igi2_frame.tDirection_8 = igi2_frame.tDirection_8 * v4;
    }
    if ( igi2_frame.atIntersection[0].isHit && igi2_frame.atIntersection[0].tNormal.vZ > 0.0 )
    {
      qmemcpy(igi2_frame.avDist, &ptHumanPlayer->tHuman.ptHumanViewQTask[10].tQTaskChildren, sizeof(igi2_frame.avDist));
      v5 = igi2_frame.atIntersection[0].tPos.vX - igi2_frame.avDist[0];
      v6 = igi2_frame.atIntersection[0].tPos.vY - igi2_frame.avDist[1];
      v7 = igi2_frame.atIntersection[0].tPos.vZ - igi2_frame.avDist[2];
      if ( igi2_frame.atIntersection[0].tPos.vX - igi2_frame.avDist[0] != 0.0 || v6 != 0.0 || v7 != 0.0 )
      {
        igi2_frame.vReal32a = sqrt(v5 * v5 + v6 * v6 + v7 * v7);
        v8 = v5;
        v9 = 1.0 / igi2_frame.vReal32a;
        v10 = v8 * v9;
        v11 = v9;
        v5 = v10;
        v6 = v6 * v11;
        v7 = v7 * v11;
      }
      igi2_frame.x = v7 * igi2_frame.tDirection_8 + v6 * igi2_frame.tDirection_4 + v5 * igi2_frame.tDirection;
      v12 = -Real32_Acos(igi2_frame.x);
      if ( v12 >= *(float *)&ptHumanViewQTask[12].ptNext )
      {
        *(float *)&ptHumanViewQTask[12].ptNext = v12;
        if ( ptHumanPlayer->tHuman.avChannel[1] >= 0.0 )
          v13 = ptHumanPlayer->tHuman.avChannel[1];
        else
          v13 = 0.0;
        ptHumanPlayer->tHuman.avChannel[1] = v13;
        ptNext = ptHumanViewQTask[12].ptNext;
        ptHumanViewQTask[12].ptPrev = nullptr;
        *(_DWORD *)&ptHumanViewQTask[11].eQTaskType = ptNext;
        HumanView_UpdateView(
          ptHumanPlayer->tHuman.ptHumanViewQTask,
          &ptHumanPlayer->tHuman.tBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask);
      }
    }
    if ( igi2_frame.atIntersection[1].isHit )
    {
      qmemcpy(igi2_frame.avDist, &ptHumanPlayer->tHuman.ptHumanViewQTask[10].tQTaskChildren, sizeof(igi2_frame.avDist));
      v15 = igi2_frame.atIntersection[1].tPos.vX - igi2_frame.avDist[0];
      v16 = igi2_frame.atIntersection[1].tPos.vY - igi2_frame.avDist[1];
      v17 = igi2_frame.atIntersection[1].tPos.vZ - igi2_frame.avDist[2];
      if ( igi2_frame.atIntersection[1].tPos.vX - igi2_frame.avDist[0] != 0.0 || v16 != 0.0 || v17 != 0.0 )
      {
        igi2_frame.vReal32b = sqrt(v15 * v15 + v16 * v16 + v17 * v17);
        v18 = v15;
        v19 = 1.0 / igi2_frame.vReal32b;
        v20 = v18 * v19;
        v21 = v19;
        v15 = v20;
        v16 = v16 * v21;
        v17 = v17 * v21;
      }
      igi2_frame.xa = v17 * igi2_frame.tDirection_8 + v16 * igi2_frame.tDirection_4 + v15 * igi2_frame.tDirection;
      igi2_frame.vReal32 = Real32_Acos(igi2_frame.xa);
      if ( igi2_frame.atIntersection[1].tNormal.vZ < 0.0 && *(float *)&ptHumanViewQTask[12].ptNext >= (double)igi2_frame.vReal32 )
      {
        *(float *)&ptHumanViewQTask[12].ptNext = igi2_frame.vReal32;
        if ( ptHumanPlayer->tHuman.avChannel[1] <= 0.0 )
          v22 = ptHumanPlayer->tHuman.avChannel[1];
        else
          v22 = 0.0;
        ptHumanPlayer->tHuman.avChannel[1] = v22;
        *(_DWORD *)&ptHumanViewQTask[11].eQTaskType = ptHumanViewQTask[12].ptNext;
LABEL_37:
        ptHumanViewQTask[12].ptPrev = nullptr;
        HumanView_UpdateView(
          ptHumanPlayer->tHuman.ptHumanViewQTask,
          &ptHumanPlayer->tHuman.tBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask);
        return;
      }
      if ( igi2_frame.atIntersection[1].tNormal.vZ > 0.0 && *(float *)&ptHumanViewQTask[12].ptNext < (double)igi2_frame.vReal32 )
      {
        if ( *(float *)&ptHumanViewQTask[12].ptNext <= (double)igi2_frame.vReal32 )
          v23 = igi2_frame.vReal32;
        else
          v23 = *(float *)&ptHumanViewQTask[12].ptNext;
        *(float *)&ptHumanViewQTask[12].ptNext = v23;
        if ( ptHumanPlayer->tHuman.avChannel[1] >= 0.0 )
          v24 = ptHumanPlayer->tHuman.avChannel[1];
        else
          v24 = 0.0;
        ptHumanPlayer->tHuman.avChannel[1] = v24;
        *(_DWORD *)&ptHumanViewQTask[11].eQTaskType = ptHumanViewQTask[12].ptNext;
        goto LABEL_37;
      }
    }
  }
}

// source: j/0/human/humanplayer.c:20245  [anchor-callee]
struct QTask_s *__cdecl HumanPlayer_GoToDefaultState(struct QTask_s *ptQTask)
{
  struct QTask_s *ptTail; // eax
  struct QReference_s *ptHead; // eax
  void (__cdecl *v4)(struct QReference_s **, struct QTask_s *); // eax
  struct QReference_s *v5; // eax
  struct QTask_s *ptNext; // eax
  void (__cdecl *v7)(struct QReference_s **, struct QTask_s *); // eax
  struct QReference_s *v8; // eax
  struct QTask_s *ptPrev; // eax

  ptTail = ptQTask[33].tQTaskChildren.ptTail;
  LOBYTE(ptQTask[76].tQTaskRefList.ptMiddle) = 0;
  LOBYTE(ptTail[12].tQTaskRefList.ptTail) = 0;
  ptHead = ptQTask[46].tQTaskRefList.ptHead;
  LOBYTE(ptQTask[34].tQTaskChildren.ptMiddle) = 0;
  LOBYTE(ptQTask[46].tQTaskRefList.ptMiddle) = 0;
  BYTE1(ptQTask[46].tQTaskRefList.ptMiddle) = 1;
  if ( ptHead )
  {
    QReference_Delete(ptHead, &QTask_tQTaskRefPool);
    ptQTask[46].tQTaskRefList.ptHead = nullptr;
  }
  ptQTask[33].tQTaskRefList.ptHead = (struct QReference_s *)1;
  LOBYTE(ptQTask[78].ptPrev) = 0;
  BYTE1(ptQTask[36].tQTaskChildren.ptTail) = 0;
  QTask_DeleteQTaskAndQTaskRefSafe(&ptQTask[85].tQTaskRefList.ptMiddle);
  QTask_DeleteQTaskAndQTaskRefSafe(&ptQTask[85].tQTaskRefList.ptHead);
  v4 = *((void (__cdecl **)(struct QReference_s **, struct QTask_s *))&ptQTask[30].ptParent->ptNext
       + (int)ptQTask[31].ptPrev);
  if ( v4 )
    v4(&ptQTask[30].tQTaskRefList.ptMiddle, ptQTask);
  v5 = ptQTask[30].tQTaskRefList.ptTail;
  ptQTask[31].ptNext = ptQTask[31].ptPrev;
  ptQTask[31].ptPrev = nullptr;
  ptNext = (struct QTask_s *)v5->ptNext;
  ptQTask[31].tQTaskChildren.ptHead = ptNext;
  ((void (__cdecl *)(struct QReference_s **, struct QTask_s *))ptNext)(&ptQTask[30].tQTaskRefList.ptMiddle, ptQTask);
  v7 = *((void (__cdecl **)(struct QReference_s **, struct QTask_s *))&ptQTask[74].ptParent->ptNext
       + (int)ptQTask[75].ptPrev);
  if ( v7 )
    v7(&ptQTask[74].tQTaskRefList.ptMiddle, ptQTask);
  v8 = ptQTask[74].tQTaskRefList.ptTail;
  ptQTask[75].ptNext = ptQTask[75].ptPrev;
  ptQTask[75].ptPrev = (struct QTask_s *)1;
  ptPrev = (struct QTask_s *)v8->ptPrev;
  ptQTask[75].tQTaskChildren.ptHead = ptPrev;
  return ((struct QTask_s *(__cdecl *)(struct QReference_s **, struct QTask_s *))ptPrev)(
           &ptQTask[74].tQTaskRefList.ptMiddle,
           ptQTask);
}

// source: j/0/human/humanplayer.c:20280  [anchor-mhash]
struct QTask_s *__cdecl HumanPlayer_SendHandleWeaponAIEvent(struct QTask_s *ptQTask, float vRadius)
{
  struct QReference_s *ptTail; // ecx
  struct QTask_s *result; // eax
  struct HumanAIEventContext_t tContext; // [esp+8h] [ebp-40h] BYREF

  ptTail = ptQTask[10].tQTaskRefList.ptTail;
  tContext.ptHumanOriginatorQTask = ptQTask;
  tContext.bFlags = 1090;
  tContext.eEvent = 44;
  tContext.eTeam = (int)ptTail;
  tContext.ptPosition = (struct real64x3_t *)&ptQTask[1];
  memset(&tContext.tDirection, 0, 16);
  tContext.vRadius = vRadius;
  HumanAI_SendEvent(&tContext);
  return result;
}

void __cdecl sub_4C9E00(int a1)
{
  if ( !*(_DWORD *)(a1 + 3548)
    || !**(_BYTE **)(a1 + 3552)
    || !*(_DWORD *)(a1 + 3556)
    || Level_RunLevelExpression((struct LevelExpression_s *)(a1 + 3548), (struct QTask_s *)a1) == 0.0 )
  {
    ++*(_DWORD *)(a1 + 480);
  }
}
