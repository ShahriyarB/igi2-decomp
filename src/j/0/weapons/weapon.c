/* j/0/weapons/weapon.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/weapons/weapon.c:91  [anchor-mhash]
int __cdecl Weapon_GetWeaponTypeIndexFromWeaponTypeItem(
        struct Weapon_s *ptWeapon,
        struct WeaponTypeItem_s *ptWeaponTypeItem)
{
  struct WeaponTypeItem_s *ptHead; // edx
  struct WeaponTypeItem_s *ptNext; // ecx
  int result; // eax

  ptHead = (struct WeaponTypeItem_s *)ptWeapon->tPrivate.tActiveWeaponTypes.ptHead;
  ptNext = (struct WeaponTypeItem_s *)ptHead->tNode.ptNext;
  result = 0;
  if ( !ptHead->tNode.ptNext )
    return 0;
  while ( ptWeaponTypeItem != ptHead )
  {
    ptHead = ptNext;
    ptNext = (struct WeaponTypeItem_s *)ptNext->tNode.ptNext;
    ++result;
    if ( !ptNext )
      return 0;
  }
  return result;
}

// source: j/0/weapons/weapon.c:123  [anchor-mhash]
struct WeaponTypeItem_s *__cdecl Weapon_GetWeaponTypeItemFromIndex(
        struct Weapon_s *ptWeapon,
        int iItem)
{
  struct WeaponTypeItem_s *result; // eax
  struct WeaponTypeItem_s *ptNext; // ecx

  result = (struct WeaponTypeItem_s *)ptWeapon->tPrivate.tActiveWeaponTypes.ptHead;
  ptNext = (struct WeaponTypeItem_s *)result->tNode.ptNext;
  if ( !result->tNode.ptNext )
    return nullptr;
  while ( iItem )
  {
    result = ptNext;
    ptNext = (struct WeaponTypeItem_s *)ptNext->tNode.ptNext;
    --iItem;
    if ( !ptNext )
      return nullptr;
  }
  return result;
}

// source: j/0/weapons/weapon.c:148  [size]
void __cdecl Weapon_GetSerializeParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = Weapon_ptSerializeParameterList;
}

// source: j/0/weapons/weapon.c:166  [anchor-mhash]
void __cdecl Weapon_DeSerializeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptTail; // ecx
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptHead; // edx

  Serialize_DeSerializeHandler(ptQTask, pxContext);
  ptTail = ptQTask[4].tQTaskChildren.ptTail;
  ptNext = ptTail->ptNext;
  ptHead = ptQTask[1].tQTaskChildren.ptHead;
  if ( ptTail->ptNext )
  {
    while ( ptHead )
    {
      ptTail = ptNext;
      ptNext = ptNext->ptNext;
      ptHead = (struct QTask_s *)((char *)ptHead - 1);
      if ( !ptNext )
        goto LABEL_4;
    }
  }
  else
  {
LABEL_4:
    ptTail = nullptr;
  }
  ptQTask[1].ptPrev = ptTail;
  ptQTask[1].ptNext = ptTail;
  ptQTask[1].tQTaskRefList.ptMiddle = nullptr;
}

// source: j/0/weapons/weapon.c:184  [size]
void __cdecl Weapon_SerializeListUpdateAmmoItemHandler(struct SerializeListType_s *ptSerializeListType, void *pxItem)
{
  *((_DWORD *)pxItem + 4) = AmmoType_GetAmmoTypeFromID(*((_DWORD *)pxItem + 5));
}

// source: j/0/weapons/weapon.c:200  [size]
void __cdecl Weapon_SerializeListUpdateWeaponItemHandler(struct SerializeListType_s *ptSerializeListType, void *pxItem)
{
  *((_DWORD *)pxItem + 4) = WeaponType_GetWeaponTypeFromID(*((_DWORD *)pxItem + 5));
}

// source: j/0/weapons/weapon.c:216  [anchor-mhash]
struct real32x3_t *__cdecl Weapon_UnPackOrientation(
        struct real32x9_t *ptOrientation,
        struct real32x3_t *ptPacked)
{
  return (struct real32x3_t *)Real32x9_Create(ptOrientation, ptPacked->vX, ptPacked->vY, ptPacked->vZ);
}

// source: j/0/weapons/weapon.c:232  [anchor-mhash]
void __cdecl Weapon_EnumAmmoTypeCB(struct AmmoType_s *ptAmmoType, void *pxContext)
{
  _DWORD *v2; // eax

  v2 = Mem_AllocFn(24, 4);
  v2[1] = 0;
  *v2 = 0;
  v2[2] = 0;
  v2[4] = ptAmmoType;
  v2[3] = -1;
  v2[5] = ptAmmoType->eAmmoTypeID;
  List_AddTail(v2, (int)pxContext + 188);
}

// source: j/0/weapons/weapon.c:267  [anchor-mhash]
void __cdecl Weapon_EnumWeaponTypeCB(struct WeaponType_s *ptWeaponType, void *pxContext)
{
  _DWORD *v2; // eax

  v2 = Mem_AllocFn(32, 4);
  v2[4] = ptWeaponType;
  v2[1] = 0;
  *v2 = 0;
  *((_BYTE *)v2 + 28) = 0;
  v2[5] = ptWeaponType->eID;
  v2[6] = 0;
  *((_BYTE *)v2 + 29) = 0;
  v2[2] = 0;
  v2[3] = 0;
  List_AddTail(v2, (int)pxContext + 176);
}

// source: j/0/weapons/weapon.c:311  [anchor-callee]
unsigned int __cdecl Weapon_SendWeaponEvent(
        struct QTask_s *ptWeaponQTask,
        unsigned int eGameMessage,
        void *ptNetManagerGameMessage,
        int nMessageSize)
{
  unsigned int result; // eax
  struct QTask_s *ptHead; // edi
  struct Client_s *ClientFromHumanQTask; // eax
  enum WeaponCategory_e eWeaponCategory; // eax
  int v9; // edi
  char v10; // al

  result = Game_eGameMode;
  if ( Game_eGameMode == GAME_GAMEMODE_SINGLEPLAYER )
  {
    if ( eGameMessage > 0x5753524C )
    {
      if ( eGameMessage == 1465078355 )
      {
        result = *(_DWORD *)&Weapon_eReleaseQTaskEvent;
      }
      else
      {
        if ( eGameMessage != 1465080397 )
          return result;
        result = *(_DWORD *)&Weapon_eZoomQTaskEvent;
      }
    }
    else
    {
      switch ( eGameMessage )
      {
        case 0x5753524Cu:
          result = *(_DWORD *)&Weapon_eReloadQTaskEvent;
          break;
        case 0x57534154u:
          result = *(_DWORD *)&Weapon_eActivateQTaskEvent;
          break;
        case 0x57534652u:
          result = *(_DWORD *)&Weapon_eFireQTaskEvent;
          break;
        default:
          return result;
      }
    }
    if ( (_WORD)result != 512 )
      return ((unsigned int (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[(__int16)result][ptWeaponQTask->eQTaskType].pfHandler)(
               ptWeaponQTask,
               ptNetManagerGameMessage);
    return result;
  }
  if ( Game_eGameMode != GAME_GAMEMODE_MULTIPLAYER )
  {
    LDebug_Error("Weapon: GameMode (%d) not defined", Game_eGameMode);
    abort();
  }
  *(_DWORD *)ptNetManagerGameMessage = eGameMessage;
  *((_DWORD *)ptNetManagerGameMessage + 1) = NetManager_GetTimer();
  *((_DWORD *)ptNetManagerGameMessage + 3) = ptWeaponQTask[16].tQTaskRefList.ptTail;
  *((_DWORD *)ptNetManagerGameMessage + 2) = -1;
  if ( ptWeaponQTask[2].tQTaskChildren.ptTail )
  {
    *((_BYTE *)ptNetManagerGameMessage + 16) = 1;
    ptHead = ptWeaponQTask[2].tQTaskChildren.ptTail->tQTaskChildren.ptHead;
    if ( ptHead )
    {
      ClientFromHumanQTask = NetManager_GetClientFromHumanQTask(ptHead);
      if ( ClientFromHumanQTask )
        *((_DWORD *)ptNetManagerGameMessage + 2) = ClientFromHumanQTask->eNetworkID;
    }
  }
  else
  {
    *((_BYTE *)ptNetManagerGameMessage + 16) = 0;
    *((_DWORD *)ptNetManagerGameMessage + 2) = 0;
  }
  if ( eGameMessage > 0x5753524C )
  {
    if ( eGameMessage == 1465078355 )
    {
      v10 = *((_BYTE *)ptNetManagerGameMessage + 24);
      if ( v10 == 1
        || !v10
        && WeaponType_GetWeaponTypeFromID(*((_DWORD *)ptNetManagerGameMessage + 5))->anRoundsInSuccession[*((char *)ptNetManagerGameMessage + 25)] == 1 )
      {
        Weapon_SingleReleaseHandler(ptWeaponQTask, ptNetManagerGameMessage);
      }
      else
      {
        NetManager_SendGameMessage(
          0,
          (int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle,
          NETWORKQUEUE_GUARANTEED,
          (struct NetManagerGameMessage_s *)ptNetManagerGameMessage,
          nMessageSize);
        Weapon_SingleReleaseHandler(ptWeaponQTask, ptNetManagerGameMessage);
      }
      return result;
    }
    if ( eGameMessage == 1465080397 )
    {
      Weapon_SingleZoomHandler(ptWeaponQTask, ptNetManagerGameMessage);
      NetManager_SendGameMessage(
        0,
        (int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle,
        NETWORKQUEUE_GUARANTEED,
        (struct NetManagerGameMessage_s *)ptNetManagerGameMessage,
        nMessageSize);
      return result;
    }
    goto LABEL_38;
  }
  if ( eGameMessage == 1465078348 )
    goto LABEL_38;
  if ( eGameMessage == 1465074004 )
  {
    if ( *((_DWORD *)ptNetManagerGameMessage + 3) )
    {
      Weapon_SingleActivateHandler(ptWeaponQTask, ptNetManagerGameMessage);
      return result;
    }
    goto LABEL_38;
  }
  if ( eGameMessage != 1465075282 )
  {
LABEL_38:
    NetManager_SendGameMessage(
      0,
      (int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle,
      NETWORKQUEUE_GUARANTEED,
      (struct NetManagerGameMessage_s *)ptNetManagerGameMessage,
      nMessageSize);
    ptWeaponQTask[1].tQTaskChildren.ptTail = (struct QTask_s *)5;
    return result;
  }
  if ( !*((_DWORD *)&ptWeaponQTask[2].tQTaskRefList.ptMiddle + 7 * *((unsigned __int8 *)ptNetManagerGameMessage + 21)) )
  {
    Weapon_SingleFireHandler(ptWeaponQTask, ptNetManagerGameMessage);
    return result;
  }
  eWeaponCategory = WeaponType_GetWeaponTypeFromID(*((unsigned __int8 *)ptNetManagerGameMessage + 20))->eWeaponCategory;
  if ( eWeaponCategory == WEAPONCATEGORY_GRENADE
    || eWeaponCategory == WEAPONCATEGORY_FLASHBANG
    || eWeaponCategory == WEAPONCATEGORY_SMOKEGRENADE
    || eWeaponCategory == WEAPONCATEGORY_PROXIMITYMINE )
  {
    v9 = 0;
  }
  else
  {
    v9 = 1;
    Weapon_SingleFireHandler(ptWeaponQTask, ptNetManagerGameMessage);
    result = (unsigned int)ptWeaponQTask[1].tQTaskChildren.ptTail;
    if ( result != 1 )
      return result;
  }
  NetManager_SendGameMessage(
    0,
    (int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle,
    NETWORKQUEUE_GUARANTEED,
    (struct NetManagerGameMessage_s *)ptNetManagerGameMessage,
    nMessageSize);
  if ( !v9 )
    ptWeaponQTask[1].tQTaskChildren.ptTail = (struct QTask_s *)5;
  return result;
}

// source: j/0/weapons/weapon.c:537  [anchor-mhash]
void __cdecl Weapon_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s **p_ptParent; // eax
  int v3; // ecx
  struct QTask_s *v4; // edi
  struct QTask_s *v5; // eax
  struct QTask_s *v6; // eax

  ptQTask[1].ptPrev = nullptr;
  ptQTask[1].ptNext = nullptr;
  ptQTask[1].tQTaskChildren.ptHead = nullptr;
  ptQTask[1].tQTaskChildren.ptTail = nullptr;
  ptQTask[1].tQTaskRefList.ptHead = nullptr;
  ptQTask[1].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[16].ptParent = nullptr;
  *(_DWORD *)&ptQTask[16].eQTaskType = 1;
  ptQTask[17].ptNext = nullptr;
  ptQTask[17].ptPrev = nullptr;
  ptQTask[1].ptParent = nullptr;
  ptQTask[16].tQTaskChildren.ptTail = nullptr;
  ptQTask[16].tQTaskRefList.ptHead = nullptr;
  ptQTask[1].tQTaskRefList.ptTail = nullptr;
  ptQTask[2].ptPrev = nullptr;
  ptQTask[2].tQTaskChildren.ptHead = nullptr;
  ptQTask[2].tQTaskChildren.ptMiddle = (struct QTask_s *)-1;
  ptQTask[2].tQTaskChildren.ptTail = nullptr;
  ptQTask[2].tQTaskRefList.ptHead = (struct QReference_s *)1065353216;
  ptQTask[4].tQTaskChildren.ptHead = nullptr;
  ptQTask[4].tQTaskChildren.ptMiddle = nullptr;
  p_ptParent = &ptQTask[2].ptParent;
  v3 = 2;
  do
  {
    *(p_ptParent - 1) = nullptr;
    *p_ptParent = nullptr;
    *(p_ptParent - 2) = nullptr;
    p_ptParent[1] = (struct QTask_s *)-1;
    p_ptParent[2] = (struct QTask_s *)-1;
    p_ptParent[4] = nullptr;
    p_ptParent[3] = nullptr;
    p_ptParent += 7;
    --v3;
  }
  while ( v3 );
  ptQTask[4].tQTaskChildren.ptTail = (struct QTask_s *)((char *)ptQTask + 180);
  ptQTask[4].tQTaskRefList.ptMiddle = (struct QReference_s *)&ptQTask[4].tQTaskChildren.ptTail;
  ptQTask[4].tQTaskRefList.ptHead = nullptr;
  ptQTask[4].tQTaskRefList.ptTail = (struct QReference_s *)&ptQTask[4].ptParent;
  *(_DWORD *)&ptQTask[4].eQTaskType = (char *)ptQTask + 188;
  ptQTask[4].ptParent = nullptr;
  ptQTask[4].ptNext = nullptr;
  ptQTask[4].ptPrev = nullptr;
  AmmoType_EnumerateAmmoTypes(Weapon_EnumAmmoTypeCB, ptQTask);
  WeaponType_EnumerateWeaponTypes(Weapon_EnumWeaponTypeCB, ptQTask);
  v4 = QTask_NewFn(ptQTask, GunShot_eQTaskType, nullptr);
  *(_DWORD *)&v4[2].eQTaskType = QTask_NewQTaskRef(ptQTask);
  ptQTask[5].ptNext = (struct QTask_s *)QTask_NewQTaskRef(v4);
  v5 = QTask_NewFn(nullptr, LaserDot_eQTaskType, nullptr);
  v6 = (struct QTask_s *)QTask_NewQTaskRef(v5);
  ptQTask[5].tQTaskChildren.ptHead = nullptr;
  ptQTask[16].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[16].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[5].ptPrev = v6;
}

// source: j/0/weapons/weapon.c:621  [size]
void __cdecl Weapon_RunHandler(struct QTask_s *ptQTask)
{
  struct QReference_s *v1; // eax

  v1 = QTask_NewQTaskRef(ptQTask);
  QVector_AddElement(RunDelayed_ptRunDelayedQTaskRefVector, v1);
}

// source: j/0/weapons/weapon.c:634  [anchor-strings]
void __cdecl Weapon_RunDelayedHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDestination; };
    struct { char igi2_o1[4]; float ptSource; };
    struct { char igi2_o2[24]; struct real64x3_t ptReal; };
    struct { char igi2_o3[48]; _BYTE pxContext[24]; };
    struct { char igi2_o4[72]; struct int32x3_t ptInt; };
    struct { char igi2_o5[84]; struct real32x9_t v27; };
    struct { char igi2_o6[160]; int v28; };
    char igi2_extent[168];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v1; // ebx
  struct QTask_s *ptParent; // eax
  struct QReference_s *ptHead; // eax
  struct QReference_s *v4; // eax
  struct Flow_t *v5; // edi
  bool v6; // zf
  struct QTask_s *v7; // eax
  struct QTask_s *ptMiddle; // edx
  int v9; // eax
  char nTicks; // cl
  char v11; // dl
  struct QTask_s *v12; // eax
  void (__cdecl *pfHandler)(struct QTask_s *, struct real32x3_t *); // ecx
  struct QTask_s *v14; // eax
  struct QTask_s *ptPrev; // ecx
  struct QTask_s *v16; // ebx
  int v17; // ecx
  int v18; // edx
  struct QTask_s *v19; // eax
  void (__cdecl *v20)(int); // eax
  int v21; // edx

  v1 = ptQTask;
  if ( !ptQTask[1].ptPrev )
    goto LABEL_26;
  ptParent = ptQTask[1].ptParent;
  if ( ptParent )
    ptQTask[1].ptParent = (struct QTask_s *)((char *)ptParent - 1);
  if ( ptQTask[16].tQTaskChildren.ptTail )
  {
    ptHead = ptQTask[16].tQTaskRefList.ptHead;
    if ( (int)ptHead > 0 )
    {
      v4 = (struct QReference_s *)((char *)ptHead - 1);
      ptQTask[16].tQTaskRefList.ptHead = v4;
      if ( v4 )
      {
        if ( !((int)v4 % 30) )
        {
          Weapon_PlaySound(ptQTask, 1, "grenade_tick", false);
          v1 = ptQTask;
        }
      }
      else
      {
        Weapon_Fire(ptQTask, 0);
        ptQTask[2].ptParent = (struct QTask_s *)1;
        ptQTask[1].tQTaskChildren.ptTail = (struct QTask_s *)6;
      }
    }
  }
  v5 = Flow_ptFlow;
  if ( v1[1].tQTaskRefList.ptMiddle )
  {
    v6 = Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER;
    ++*(int *)&v1[16].tQTaskRefList.ptMiddle;
    if ( !v6 )
      goto LABEL_18;
    if ( !v5->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
      goto LABEL_18;
    v7 = v1->ptParent;
    if ( v7->eQTaskType != HumanRemote_eQTaskType )
      goto LABEL_18;
    igi2_frame.ptSource = (double)ServerConfig_tServerConfig.nSmoothPercent * 4096.0;
    igi2_frame.ptDestination = (double)ServerConfig_tServerConfig.nViewFireRange * 4096.0;
    if ( Client_GetClientPriority(
           (struct Client_s *)HumanPlayer_ptQTask[33].ptPrev,
           (struct Client_s *)v7[33].ptPrev,
           igi2_frame.ptDestination,
           igi2_frame.ptSource) == 1
      && !(((int)&v1[16].tQTaskRefList.ptMiddle->ptNext + 2) % 3) )
    {
      goto LABEL_18;
    }
  }
  else
  {
    ptMiddle = v1[1].tQTaskChildren.ptMiddle;
    v1[16].tQTaskRefList.ptMiddle = nullptr;
    if ( *((_DWORD *)&v1[17].ptNext + (_DWORD)ptMiddle) )
    {
LABEL_18:
      v9 = 28 * (int)v1[1].tQTaskChildren.ptMiddle;
      nTicks = v5->nTicks;
      igi2_frame.pxContext[20] = v1[1].ptPrev->tQTaskChildren.ptTail[3].tQTaskRefList.ptTail;
      v11 = *((_BYTE *)&v1[2].eQTaskType + v9);
      v12 = v1->ptParent;
      igi2_frame.pxContext[22] = nTicks - v11;
      igi2_frame.v28 = 1;
      pfHandler = (void (__cdecl *)(struct QTask_s *, struct real32x3_t *))QTask_aatQTaskFinalEvent[Weapon_eGetParentParametersQTaskEvent][v12->eQTaskType].pfHandler;
      igi2_frame.pxContext[21] = 0;
      if ( pfHandler )
        pfHandler(v12, &igi2_frame.v27.tY);
      qmemcpy(&igi2_frame.ptReal, &igi2_frame.v27.tY, sizeof(igi2_frame.ptReal));
      igi2_frame.ptReal.vX = *(double *)&igi2_frame.v27.tY.vX * 0.000244140625;
      igi2_frame.ptReal.vY = igi2_frame.ptReal.vY * 0.000244140625;
      igi2_frame.ptReal.vZ = igi2_frame.ptReal.vZ * 0.000244140625;
      World_SetInt32CentimeterFromReal64Meter(&igi2_frame.ptReal, &igi2_frame.ptInt);
      Real32x9_GetAngles((struct real32x9_t *)&igi2_frame.v27.nOps, &igi2_frame.v27.tX.vX, &igi2_frame.v27.tX.vY, &igi2_frame.v27.tX.vZ);
      Weapon_SingleFireHandler(v1, igi2_frame.pxContext);
      v14 = v1[1].tQTaskChildren.ptMiddle;
      ptPrev = v1[1].ptPrev;
      if ( !*((_DWORD *)&ptPrev->tQTaskChildren.ptHead + (_DWORD)v14)
        || (int)(*((_DWORD *)&v1[3].tQTaskChildren.ptHead + 7 * (_DWORD)v14)) >= *((_DWORD *)&ptPrev->tQTaskChildren.ptTail[17].ptParent
                                                                          + (int)ptPrev->tQTaskRefList.ptMiddle) )
      {
        v1[1].tQTaskRefList.ptMiddle = nullptr;
        *((_DWORD *)&v1[17].ptNext + (_DWORD)v14) = 0;
        *((_DWORD *)&v1->ptNext + 7 * (int)&v1[1].tQTaskChildren.ptMiddle->ptPrev) = 1;
        *((_DWORD *)&v1[3].tQTaskChildren.ptHead + 7 * (int)v1[1].tQTaskChildren.ptMiddle) = 0;
      }
    }
  }
  Weapon_MaintainSoundSequence(v1);
  if ( v1[1].tQTaskChildren.ptTail == (struct QTask_s *)3 && !v1[1].ptParent )
    v1[1].tQTaskChildren.ptTail = nullptr;
LABEL_26:
  v16 = v1->tQTaskChildren.ptHead;
  if ( v16->ptNext )
  {
    v17 = (int)v16;
    if ( v16 )
    {
      v18 = QTask_nProtectedQTaskStackOffset;
      do
      {
        if ( *(_DWORD *)v17 )
          v19 = **(_DWORD **)v17 != 0 ? *(struct QTask_s **)v17 : nullptr;
        else
          v19 = nullptr;
        QTask_atProtectedQTaskStack[v18].ptQTask = v19;
        v20 = (void (__cdecl *)(int))QTask_aatQTaskFinalEvent[1][*(unsigned __int16 *)(v17 + 36)].pfHandler;
        v21 = v18 + 1;
        QTask_nProtectedQTaskStackOffset = v21;
        if ( v20 )
        {
          v20(v17);
          v21 = QTask_nProtectedQTaskStackOffset;
        }
        v17 = dword_849C7DC[v21];
        v18 = v21 - 1;
        QTask_nProtectedQTaskStackOffset = v18;
      }
      while ( v17 );
    }
  }
}

// source: j/0/weapons/weapon.c:772  [anchor-caller]
void __cdecl Weapon_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptParent; // esi
  struct WeaponTypeItem_s *WeaponTypeItemFromWeaponType; // eax
  struct QTask_s *ptTail; // eax
  struct QTask_s *ptHead; // eax
  struct QTask_s *ptMiddle; // eax
  struct QTask_s *v6; // eax
  struct QTask_s *v7; // eax
  struct QTask_s *i; // ebx
  _DWORD **v9; // eax
  int v10; // esi
  struct QReference_s *v11; // eax
  struct QReference_s *j; // ebx
  _DWORD **v13; // eax
  int v14; // esi
  struct QTask_s *ptPrev; // eax
  struct QTask_s *v16; // eax
  struct QTask_s *v17; // eax

  ptParent = ptQTask->ptParent;
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER && !Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    if ( QTask_IsQTaskTypeDerived(ptParent->eQTaskType, HumanRemote_eQTaskType) )
    {
      WeaponTypeItemFromWeaponType = Weapon_GetWeaponTypeItemFromWeaponType(ptQTask, "WEAPON_ID_C4BOMB");
      if ( WeaponTypeItemFromWeaponType->isActive )
        NetManager_DropWeapon((int)ptParent[33].ptPrev[1].ptNext, WeaponTypeItemFromWeaponType->ptWeaponType->eID);
    }
  }
  while ( ptQTask[16].tQTaskChildren.ptMiddle )
    Weapon_DeleteFirstSoundInSoundSequence(ptQTask);
  ptTail = ptQTask[2].tQTaskChildren.ptTail;
  if ( ptTail )
    QReference_Delete((struct QReference_s *)ptTail, &QTask_tQTaskRefPool);
  ptHead = ptQTask[4].tQTaskChildren.ptHead;
  if ( ptHead )
    QReference_Delete((struct QReference_s *)ptHead, &QTask_tQTaskRefPool);
  ptMiddle = ptQTask[4].tQTaskChildren.ptMiddle;
  if ( ptMiddle )
    QReference_Delete((struct QReference_s *)ptMiddle, &QTask_tQTaskRefPool);
  v6 = ptQTask[5].ptNext->tQTaskChildren.ptHead;
  if ( v6 )
  {
    if ( v6[4].ptPrev )
      v6[2].ptParent = (struct QTask_s *)1;
    else
      QTask_Delete(ptQTask[5].ptNext->tQTaskChildren.ptHead);
  }
  QReference_Delete((struct QReference_s *)ptQTask[5].ptNext, &QTask_tQTaskRefPool);
  v7 = ptQTask[4].tQTaskChildren.ptTail;
  for ( i = v7->ptNext; i; i = i->ptNext )
  {
    v9 = Node_Remove(v7);
    if ( v9 )
    {
      v10 = *(_DWORD *)((unsigned int)(v9 - 1) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v10);
      memset(*(void **)(v10 + 8), 0xCDu, *(_DWORD *)(v10 + 16));
      free((void *)v10);
    }
    v7 = i;
  }
  v11 = ptQTask[4].tQTaskRefList.ptTail;
  for ( j = v11->ptNext; j; j = j->ptNext )
  {
    v13 = Node_Remove(v11);
    if ( v13 )
    {
      v14 = *(_DWORD *)((unsigned int)(v13 - 1) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v14);
      memset(*(void **)(v14 + 8), 0xCDu, *(_DWORD *)(v14 + 16));
      free((void *)v14);
    }
    v11 = j;
  }
  ptPrev = ptQTask[5].ptPrev;
  if ( ptPrev )
  {
    v16 = ptPrev->tQTaskChildren.ptHead;
    if ( v16 )
      QTask_Delete(v16);
  }
  v17 = ptQTask[5].ptPrev;
  if ( v17 )
  {
    if ( v17->ptNext )
      v17 = (struct QTask_s *)Node_Remove(v17);
    --QTask_tQTaskRefPool.nAllocatedBlocks;
    v17->ptNext = (struct QTask_s *)QTask_tQTaskRefPool.tMemPoolFreeList.ptHead;
    QTask_tQTaskRefPool.tMemPoolFreeList.ptHead = (struct MemPoolFreeItem_s *)v17;
    ptQTask[5].ptPrev = nullptr;
  }
}

// source: j/0/weapons/weapon.c:863  [anchor-mhash]
void __cdecl Weapon_StatusDisplayHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { enum bool isDrawDot; };
    struct { char igi2_o1[4]; struct WeaponPositionOverlayContext_s tPositionOverlayContext; };
    struct { char igi2_o2[12]; struct WeaponCollisionEvaluateContext_t tWeaponCollisionEvaluateContext; };
    struct { char igi2_o3[32]; struct WeaponDisplayStatusScreenContext_s tContext; };
    struct { char igi2_o4[64]; struct WeaponGetParentParameterContext_s tGetParentInfoContext; };
    struct { char igi2_o5[136]; struct real64x3_t tTrace; };
    struct { char igi2_o6[160]; struct real64x3_t Real64x3_Rotate_tTemp; };
    struct { char igi2_o7[184]; struct real64x3_t tPos1; };
    struct { char igi2_o8[208]; struct real64x3_t tPos0; };
    struct { char igi2_o9[232]; struct QIntersection_s tIntersection; };
    char igi2_extent[352];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v2; // ebx
  struct QTask_s *ptPrev; // eax
  struct QTask_s *v4; // eax
  struct QTask_s *ptParent; // ecx
  int v6; // eax
  bool v7; // zf
  struct QTask_s *v8; // eax
  struct QTask_s *ptHead; // eax
  struct QTask_s *v10; // eax
  void (__cdecl *pfHandler)(struct QTask_s *, struct WeaponGetParentParameterContext_s *); // ecx
  struct QTask_s *v12; // eax
  void (__cdecl *v13)(struct QTask_s *, struct WeaponPositionOverlayContext_s *); // ecx
  struct QTask_s *ptNext; // esi
  struct QTask_s *v15; // eax
  struct QTask_s *ptTail; // eax
  int v17; // edx
  struct QTask_s *v18; // eax
  void (__cdecl *v19)(struct QTask_s *, struct WeaponDisplayStatusScreenContext_s *); // ecx

  v2 = ptQTask;
  ptPrev = ptQTask[1].ptPrev;
  if ( ptPrev )
  {
    igi2_frame.isDrawDot = false;
    if ( BYTE1(ptPrev->tQTaskRefList.ptTail) || BYTE1(ptPrev->tQTaskChildren.ptTail[48].tQTaskChildren.ptTail) )
    {
      if ( LOBYTE(ptPrev->tQTaskChildren.ptTail[48].tQTaskChildren.ptTail) )
      {
        v4 = ptQTask[5].ptPrev;
        if ( v4 )
        {
          if ( v4->tQTaskChildren.ptHead )
          {
            ptParent = ptQTask->ptParent;
            v6 = Weapon_eGetParentParametersQTaskEvent;
            v7 = QTask_aatQTaskFinalEvent[v6][ptParent->eQTaskType].pfHandler == nullptr;
            igi2_frame.tPositionOverlayContext.ptPosition = (struct real64x3_t *)ptParent;
            if ( !v7 )
            {
              igi2_frame.tGetParentInfoContext.isAddInaccuracy = true;
              ((void (__cdecl *)(struct QTask_s *, struct WeaponGetParentParameterContext_s *))QTask_aatQTaskFinalEvent[v6][ptParent->eQTaskType].pfHandler)(
                ptParent,
                &igi2_frame.tGetParentInfoContext);
              igi2_frame.Real64x3_Rotate_tTemp.vX = (igi2_frame.tGetParentInfoContext.tOrientation.tX.vZ
                                        + igi2_frame.tGetParentInfoContext.tOrientation.tX.vX)
                                       * 0.0
                                       + igi2_frame.tGetParentInfoContext.tOrientation.tX.vY;
              igi2_frame.Real64x3_Rotate_tTemp.vY = (igi2_frame.tGetParentInfoContext.tOrientation.tY.vZ
                                        + igi2_frame.tGetParentInfoContext.tOrientation.tY.vX)
                                       * 0.0
                                       + igi2_frame.tGetParentInfoContext.tOrientation.tY.vY;
              igi2_frame.Real64x3_Rotate_tTemp.vZ = (igi2_frame.tGetParentInfoContext.tOrientation.tZ.vZ
                                        + igi2_frame.tGetParentInfoContext.tOrientation.tZ.vX)
                                       * 0.0
                                       + igi2_frame.tGetParentInfoContext.tOrientation.tZ.vY;
              qmemcpy(&igi2_frame.tTrace, &igi2_frame.Real64x3_Rotate_tTemp, sizeof(igi2_frame.tTrace));
              igi2_frame.tTrace.vZ = igi2_frame.tTrace.vZ * 409600.0;
              qmemcpy(&igi2_frame.tPos0, &igi2_frame.tGetParentInfoContext, sizeof(igi2_frame.tPos0));
              igi2_frame.tPos1.vX = igi2_frame.tGetParentInfoContext.tPosition.vX + igi2_frame.Real64x3_Rotate_tTemp.vX * 409600.0;
              igi2_frame.tPos1.vY = igi2_frame.tGetParentInfoContext.tPosition.vY + igi2_frame.tTrace.vY * 409600.0;
              igi2_frame.tPos1.vZ = igi2_frame.tGetParentInfoContext.tPosition.vZ + igi2_frame.tTrace.vZ;
              *(_DWORD *)&igi2_frame.tWeaponCollisionEvaluateContext.tCollisionEvaluateContext.isEvaluate = 0;
              igi2_frame.tWeaponCollisionEvaluateContext.ptIgnore2QTask = nullptr;
              igi2_frame.tWeaponCollisionEvaluateContext.tCollisionEvaluateContext.ptQTask = nullptr;
              igi2_frame.tWeaponCollisionEvaluateContext.ptIgnore1QTask = (struct QTask_s *)igi2_frame.tPositionOverlayContext.ptPosition;
              igi2_frame.tWeaponCollisionEvaluateContext.vHitProbability = 1.0;
              World_TraceLines(
                Game_ptGame->ptWorld,
                &igi2_frame.tIntersection,
                &igi2_frame.tPos0,
                &igi2_frame.tPos1,
                1,
                GameFunctions_eWeaponCollisionEvaluateQTaskEvent,
                &igi2_frame.tWeaponCollisionEvaluateContext.tCollisionEvaluateContext,
                0xFFFFFFFF);
              if ( igi2_frame.tIntersection.isHit )
              {
                LaserDot_SetPosAndNormal(
                  ptQTask[5].ptPrev->tQTaskChildren.ptHead,
                  &igi2_frame.tIntersection.tPos,
                  &igi2_frame.tIntersection.tNormal);
                v2 = ptQTask;
                igi2_frame.isDrawDot = true;
              }
            }
          }
        }
      }
    }
    v8 = v2[5].ptPrev;
    if ( v8 )
    {
      ptHead = v8->tQTaskChildren.ptHead;
      if ( ptHead )
        *(_DWORD *)&ptHead[2].eQTaskType = igi2_frame.isDrawDot;
    }
    if ( v2[4].ptNext == (struct QTask_s *)2 && v2[4].ptPrev )
    {
      v10 = v2->ptParent;
      igi2_frame.tGetParentInfoContext.isAddInaccuracy = false;
      pfHandler = (void (__cdecl *)(struct QTask_s *, struct WeaponGetParentParameterContext_s *))QTask_aatQTaskFinalEvent[Weapon_eGetParentParametersQTaskEvent][v10->eQTaskType].pfHandler;
      if ( !pfHandler )
        return;
      pfHandler(v10, &igi2_frame.tGetParentInfoContext);
      igi2_frame.tPositionOverlayContext.ptOrientation = &igi2_frame.tGetParentInfoContext.tOrientation;
      igi2_frame.tPositionOverlayContext.ptPosition = (struct real64x3_t *)&igi2_frame.tGetParentInfoContext;
      v12 = v2[4].ptPrev;
      v13 = (void (__cdecl *)(struct QTask_s *, struct WeaponPositionOverlayContext_s *))QTask_aatQTaskFinalEvent[Weapon_ePositionOverlayQTaskEvent][v12->eQTaskType].pfHandler;
      if ( v13 )
        v13(v12, &igi2_frame.tPositionOverlayContext);
      ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[StatusScreen_eStatusDisplayQTaskEvent][v2[4].ptPrev->eQTaskType].pfHandler)(
        v2[4].ptPrev,
        pxContext);
    }
  }
  ptNext = v2[1].ptNext;
  if ( ptNext )
  {
    igi2_frame.tContext.tIn.ptStatusDisplayContext = (struct StatusDisplayContext_t *)pxContext;
    v7 = v2[4].ptNext == nullptr;
    igi2_frame.tContext.tIn.ptWeapon = (struct Weapon_s *)v2;
    igi2_frame.tContext.tIn.ptWeaponType = (struct WeaponType_s *)ptNext->tQTaskChildren.ptTail;
    igi2_frame.tContext.tIn.isScopeActive = false;
    igi2_frame.tContext.tIn.iActiveFireMode = (int)ptNext->tQTaskRefList.ptMiddle;
    if ( !v7 )
    {
      v15 = v2[1].ptPrev;
      if ( v15 )
      {
        ptTail = v15->tQTaskChildren.ptTail;
        if ( ptTail )
          igi2_frame.tContext.tIn.isScopeActive = ptTail[33].ptNext == (struct QTask_s *)Zoom_eQTaskType;
      }
    }
    igi2_frame.tContext.tIn.nFireType = -1;
    igi2_frame.tContext.tIn.pxFireTypeParameters = nullptr;
    v2[3].ptPrev = ptNext->tQTaskChildren.ptHead;
    v17 = WeaponType_eDrawIconQTaskEvent;
    v2[3].ptParent = ptNext->tQTaskChildren.ptMiddle;
    v18 = ptNext->tQTaskChildren.ptTail;
    v19 = (void (__cdecl *)(struct QTask_s *, struct WeaponDisplayStatusScreenContext_s *))QTask_aatQTaskFinalEvent[v17][v18->eQTaskType].pfHandler;
    if ( v19 )
      v19(v18, &igi2_frame.tContext);
    ((void (__cdecl *)(struct QTask_s *, struct WeaponDisplayStatusScreenContext_s *))QTask_aatQTaskFinalEvent[StatusScreen_eStatusDisplayQTaskEvent][ptNext->tQTaskChildren.ptTail->eQTaskType].pfHandler)(
      ptNext->tQTaskChildren.ptTail,
      &igi2_frame.tContext);
  }
}

// source: j/0/weapons/weapon.c:1013  [anchor-callee]
void __cdecl Weapon_SingleFireHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s *v28; };
    struct { char igi2_o1[4]; float v29; };
    struct { char igi2_o2[8]; float v30; };
    struct { char igi2_o3[12]; float v31; };
    struct { char igi2_o4[32]; struct QTask_s *v32; };
    struct { char igi2_o5[36]; struct QTask_s **v33; };
    struct { char igi2_o6[40]; char *v34; };
    struct { char igi2_o7[44]; int v35; };
    struct { char igi2_o8[52]; int v36; };
    struct { char igi2_o9[56]; _DWORD v37[2]; };
    struct { char igi2_o10[64]; struct QTask_s *v38; };
    struct { char igi2_o11[72]; struct real64x3_t ptReal; };
    struct { char igi2_o12[96]; struct real32x9_t ptDest; };
    struct { char igi2_o13[136]; struct QTask_s *v41; };
    struct { char igi2_o14[140]; struct QTask_s *v42; };
    struct { char igi2_o15[144]; struct QTask_s *v43; };
    struct { char igi2_o16[148]; int v44; };
    struct { char igi2_o17[152]; char v45; };
    struct { char igi2_o18[156]; struct QTask_s *v46; };
    struct { char igi2_o19[160]; struct WeaponType_s *v47; };
    struct { char igi2_o20[164]; int v48; };
    struct { char igi2_o21[168]; struct QTask_s *v49; };
    struct { char igi2_o22[172]; struct QTask_s *v50; };
    struct { char igi2_o23[176]; float vGammaKickBack; };
    struct { char igi2_o24[180]; float vKickBackDamping; };
    struct { char igi2_o25[184]; struct QTask_s *ptWeaponQTask; };
    struct { char igi2_o26[188]; float vAlphaKickBack; };
    struct { char igi2_o27[192]; struct WeaponTypeGetAmmoInfoContext_s ptContext; };
    char igi2_extent[236];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // ebx
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptTail; // edx
  struct QTask_s *ptNext; // eax
  int v6; // ecx
  struct WeaponType_s *v7; // esi
  int v8; // eax
  int v9; // ecx
  int nRoundsToFire; // ecx
  struct AmmoType_s *ptAmmoType; // eax
  struct QTask_s *v12; // eax
  struct QTask_s *ptParent; // edx
  struct QTask_s *ptHead; // eax
  struct QTask_s **p_ptParent; // eax
  float v16; // ecx
  float v17; // edx
  float v18; // eax
  int v19; // edx
  struct QTask_s *v20; // ecx
  struct QTask_s *v21; // edx
  int v22; // ecx
  int v23; // ebp
  struct QTask_s *v24; // eax
  bool v25; // zf
  struct AmmoType_s *v26; // eax
  struct AmmoTypeItem_s *AmmoTypeItemFromAmmoType; // eax

  v2 = *((unsigned __int8 *)pxContext + 21);
  *((_DWORD *)&ptQTask[2].tQTaskRefList.ptMiddle + 7 * v2) = 0;
  igi2_frame.v34 = (char *)ptQTask + 28 * v2;
  ptPrev = ptQTask[1].ptPrev;
  ptQTask[1].tQTaskChildren.ptMiddle = (struct QTask_s *)v2;
  if ( ptPrev && !v2 && *((int *)&ptPrev->tQTaskChildren.ptTail[17].ptParent + (int)ptPrev->tQTaskRefList.ptMiddle) > 1 )
    ptQTask[1].tQTaskRefList.ptMiddle = (struct QReference_s *)1;
  ptTail = ptQTask[4].tQTaskChildren.ptTail;
  ptNext = ptTail->ptNext;
  v6 = *((unsigned __int8 *)pxContext + 20);
  igi2_frame.v32 = ptTail;
  if ( ptTail->ptNext )
  {
    while ( v6 )
    {
      igi2_frame.v32 = ptNext;
      ptNext = ptNext->ptNext;
      --v6;
      if ( !ptNext )
        return;
      ptTail = igi2_frame.v32;
    }
    if ( ptTail )
    {
      v7 = (struct WeaponType_s *)ptTail->tQTaskChildren.ptTail;
      v8 = 5 * v2 + 325;
      v9 = *((unsigned __int16 *)&v7->tQTask.ptNext + 2 * v8);
      igi2_frame.v33 = &v7->tQTask.ptNext + v8;
      igi2_frame.v36 = v9;
      if ( QTask_IsQTaskTypeValid(v9) )
      {
        if ( QTask_aatQTaskFinalEvent[Weapon_eFireQTaskEvent][v9].pfHandler )
        {
          *((_DWORD *)igi2_frame.v34 + 30) = Flow_ptFlow->nTicks;
          WeaponType_GetAmmoInfo(v7, &igi2_frame.ptContext);
          nRoundsToFire = igi2_frame.ptContext.atAmmoItem[v2].tOut.nRoundsToFire;
          if ( *((_BYTE *)igi2_frame.v33 + 8) )
          {
            ptAmmoType = igi2_frame.ptContext.atAmmoItem[v2].tOut.ptAmmoType;
            if ( ptAmmoType )
            {
              igi2_frame.v35 = igi2_frame.ptContext.atAmmoItem[v2].tOut.nRoundsToFire;
              if ( igi2_frame.v35 > Weapon_GetAmmoTypeItemFromAmmoType(ptQTask, ptAmmoType->zAmmoTypeScriptID)->nAmmoCount )
              {
                ptQTask[1].tQTaskChildren.ptTail = (struct QTask_s *)4;
                return;
              }
LABEL_21:
              if ( ptQTask[1].ptParent && *igi2_frame.v33 != (struct QTask_s *)Zoom_eQTaskType )
              {
                ptQTask[1].tQTaskChildren.ptTail = (struct QTask_s *)3;
                return;
              }
              v12 = ptQTask[2].tQTaskChildren.ptTail;
              ptParent = ptQTask->ptParent;
              igi2_frame.v37[0] = ptQTask;
              igi2_frame.v37[1] = ptParent;
              if ( v12 )
              {
                ptHead = v12->tQTaskChildren.ptHead;
                igi2_frame.v38 = ptHead;
                if ( ptHead )
                {
                  p_ptParent = &ptHead[37].ptParent;
                  igi2_frame.v41 = *p_ptParent;
                  igi2_frame.v42 = p_ptParent[1];
                  igi2_frame.v43 = p_ptParent[2];
                  goto LABEL_29;
                }
              }
              else
              {
                igi2_frame.v38 = nullptr;
              }
              igi2_frame.v41 = nullptr;
              igi2_frame.v42 = nullptr;
              igi2_frame.v43 = nullptr;
LABEL_29:
              World_SetReal64MeterFromInt32Centimeter(&igi2_frame.ptReal, (struct int32x3_t *)pxContext + 2);
              v16 = *((float *)pxContext + 11);
              v17 = *((float *)pxContext + 10);
              v18 = *((float *)pxContext + 9);
              igi2_frame.ptReal.vX = igi2_frame.ptReal.vX * 4096.0;
              igi2_frame.ptReal.vY = igi2_frame.ptReal.vY * 4096.0;
              igi2_frame.ptReal.vZ = igi2_frame.ptReal.vZ * 4096.0;
              Real32x9_Create(&igi2_frame.ptDest, v18, v17, v16);
              v19 = *((unsigned __int8 *)pxContext + 22);
              igi2_frame.v45 = *((_BYTE *)pxContext + 23);
              v20 = igi2_frame.v33[3];
              igi2_frame.v44 = v19;
              v21 = v20->tQTaskChildren.ptHead;
              v22 = *((_DWORD *)pxContext + 1);
              igi2_frame.v46 = v21;
              Human_nFireTimeStamp = v22;
              igi2_frame.v47 = v7;
              igi2_frame.v48 = *((_DWORD *)igi2_frame.v34 + 32);
              igi2_frame.v49 = nullptr;
              igi2_frame.v50 = nullptr;
              igi2_frame.ptWeaponQTask = nullptr;
              igi2_frame.vAlphaKickBack = 0.0;
              igi2_frame.vGammaKickBack = 0.0;
              igi2_frame.vKickBackDamping = 1.0;
              ((void (__cdecl *)(_DWORD, _DWORD *))QTask_aatQTaskFinalEvent[Weapon_eFireQTaskEvent][igi2_frame.v36].pfHandler)(
                0,
                igi2_frame.v37);
              v23 = (int)igi2_frame.v49;
              v24 = igi2_frame.v50;
              v25 = igi2_frame.v49 == nullptr;
              ptQTask[1].tQTaskRefList.ptTail = (struct QReference_s *)((char *)ptQTask[1].tQTaskRefList.ptTail
                                                                      + (unsigned int)igi2_frame.v49);
              if ( !v25 || v24 )
              {
                ptQTask[1].ptParent = v24;
                if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER
                  && ptQTask[1].tQTaskRefList.ptMiddle
                  && Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
                {
                  *(_DWORD *)&ptQTask[16].eQTaskType = 0;
                }
                if ( *((_BYTE *)igi2_frame.v33 + 8) )
                {
                  v26 = igi2_frame.ptContext.atAmmoItem[v2].tOut.ptAmmoType;
                  if ( v26 )
                  {
                    AmmoTypeItemFromAmmoType = Weapon_GetAmmoTypeItemFromAmmoType(ptQTask, v26->zAmmoTypeScriptID);
                    AmmoTypeItemFromAmmoType->nAmmoCount -= v23;
                    Weapon_UpdateOwnersMissionScoreShots(ptQTask, v2, (int)igi2_frame.v49);
                  }
                }
                else
                {
                  *((_DWORD *)&igi2_frame.v32->tQTaskChildren.ptHead + v2) = (int)(*((_DWORD *)&igi2_frame.v32->tQTaskChildren.ptHead + v2) - v23) <= 0
                                                                ? 0
                                                                : *((_DWORD *)&igi2_frame.v32->tQTaskChildren.ptHead + v2) - v23;
                  *((_DWORD *)igi2_frame.v34 + 32) += (int)(v23);
                  Weapon_UpdateOwnersMissionScoreShots(ptQTask, v2, v23);
                }
              }
              igi2_frame.v31 = igi2_frame.vKickBackDamping;
              igi2_frame.v30 = igi2_frame.vGammaKickBack;
              igi2_frame.v29 = igi2_frame.vAlphaKickBack;
              igi2_frame.v28 = igi2_frame.ptWeaponQTask;
              ptQTask[1].tQTaskChildren.ptTail = (struct QTask_s *)1;
              Weapon_SetKickBack(ptQTask, *(float *)&igi2_frame.v28, igi2_frame.v29, igi2_frame.v30, igi2_frame.v31);
              return;
            }
            if ( !nRoundsToFire )
              goto LABEL_21;
          }
          else if ( nRoundsToFire <= (int)(*((_DWORD *)&igi2_frame.v32->tQTaskChildren.ptHead + v2)) )
          {
            goto LABEL_21;
          }
          ptQTask[1].tQTaskChildren.ptTail = (struct QTask_s *)4;
        }
      }
    }
  }
}

// source: j/0/weapons/weapon.c:1211  [anchor-strings]
void __cdecl Weapon_MultiFireHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // esi
  int v3; // ecx
  int v4; // esi
  struct QTask_s *ptPrev; // ebx
  struct QTask_s *ptParent; // edx

  v2 = *((_DWORD *)pxContext + 3);
  v3 = *(unsigned __int8 *)(v2 + 29);
  v4 = v2 + 8;
  *((_DWORD *)&ptQTask[2].tQTaskRefList.ptMiddle + 7 * v3) = 0;
  ptPrev = ptQTask[1].ptPrev;
  if ( ptPrev )
  {
    ptParent = ptQTask->ptParent;
    if ( QTask_IsQTaskTypeDerived(ptParent->eQTaskType, Human_eQTaskType) )
    {
      if ( ptParent[33].tQTaskChildren.ptTail[16].tQTaskRefList.ptMiddle && *(_BYTE *)(v4 + 21) == 1 )
        ptQTask[1].ptParent = nullptr;
      if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER
        && !Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle
        && ptPrev->tQTaskChildren.ptTail[16].ptParent == (struct QTask_s *)4
        && *(_BYTE *)(v4 + 21) != 1 )
      {
        RadioCom_AutoTransmit(
          (int)ptParent[10].tQTaskRefList.ptTail,
          RADIOCOM_AUTOMATIC_GRENADE,
          *(_DWORD *)(v4 + 8),
          0);
      }
    }
    Weapon_SingleFireHandler(ptQTask, (void *)v4);
  }
  else
  {
    NetManager_LogMessage("Weapon: Fire event, but no active weapon\n");
  }
}

// source: j/0/weapons/weapon.c:1280  [anchor-callee]
void __cdecl Weapon_SingleReleaseHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { int *v16; };
    struct { char igi2_o1[4]; void (__cdecl *pfHandler)(_DWORD, struct WeaponReleaseContext_s *); };
    struct { char igi2_o2[8]; struct WeaponTypeFireType_s *ptFireType; };
    struct { char igi2_o3[12]; struct WeaponReleaseContext_s tReleaseContext; };
    struct { char igi2_o4[140]; struct WeaponGetFireTypeAmmoContext_s tAmmoContext; };
    char igi2_extent[160];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // ebx
  struct QTask_s *ptTail; // ebp
  struct QTask_s *ptNext; // eax
  int v5; // ecx
  int v6; // ecx
  float v7; // eax
  struct QTask_s *v8; // eax
  struct QTask_s *ptHead; // edx
  int v10; // ecx
  struct WeaponType_s *v11; // eax
  struct QReference_s *ptParametersQTaskRef; // eax
  int nBulletsFired; // edi
  struct AmmoTypeItem_s *AmmoTypeItemFromAmmoType; // eax
  int v15; // eax

  v2 = *((char *)pxContext + 24);
  if ( !*((_BYTE *)pxContext + 24) )
    ptQTask[1].tQTaskRefList.ptMiddle = (struct QReference_s *)v2;
  ptTail = ptQTask[4].tQTaskChildren.ptTail;
  ptQTask[1].tQTaskChildren.ptMiddle = (struct QTask_s *)v2;
  ptNext = ptTail->ptNext;
  v5 = *((_DWORD *)pxContext + 5);
  if ( ptTail->ptNext )
  {
    while ( v5 )
    {
      ptTail = ptNext;
      ptNext = ptNext->ptNext;
      --v5;
      if ( !ptNext )
        return;
    }
    if ( ptTail )
    {
      v6 = *((unsigned __int16 *)&ptTail->tQTaskChildren.ptTail[32].tQTaskRefList.ptHead + 10 * v2);
      igi2_frame.ptFireType = (struct WeaponTypeFireType_s *)((char *)&ptTail->tQTaskChildren.ptTail[32].tQTaskRefList + 20 * v2);
      if ( QTask_IsQTaskTypeValid(v6) )
      {
        igi2_frame.pfHandler = (void (__cdecl *)(_DWORD, struct WeaponReleaseContext_s *))QTask_aatQTaskFinalEvent[Weapon_eReleaseQTaskEvent][v6].pfHandler;
        if ( igi2_frame.pfHandler )
        {
          if ( ptQTask[1].ptPrev )
          {
            v7 = *((float *)pxContext + 16);
            igi2_frame.tReleaseContext.tIn.nHeldTime = *((_DWORD *)pxContext + 17);
            qmemcpy(&igi2_frame.tReleaseContext.tIn.tPosition, (char *)pxContext + 32, sizeof(igi2_frame.tReleaseContext.tIn.tPosition));
            Real32x9_Create(
              &igi2_frame.tReleaseContext.tIn.tOrientation,
              *((float *)pxContext + 14),
              *((float *)pxContext + 15),
              v7);
            v8 = ptQTask[2].tQTaskChildren.ptTail;
            if ( v8 )
              ptHead = v8->tQTaskChildren.ptHead;
            else
              ptHead = nullptr;
            igi2_frame.v16 = (int *)((char *)&ptQTask[3].tQTaskChildren + 28 * v2);
            v10 = *igi2_frame.v16;
            igi2_frame.tReleaseContext.tIn.ptIgnoreQTask = ptQTask->ptParent;
            v11 = (struct WeaponType_s *)ptTail->tQTaskChildren.ptTail;
            igi2_frame.tReleaseContext.tIn.nRoundsFired = v10;
            igi2_frame.tReleaseContext.tIn.ptWeaponType = v11;
            ptParametersQTaskRef = v11->atFireTypes[v2].ptParametersQTaskRef;
            igi2_frame.tReleaseContext.tIn.ptHumanOperator = ptHead;
            igi2_frame.tReleaseContext.tIn.ptWeaponQTask = ptQTask;
            igi2_frame.tReleaseContext.tIn.pxFireTypeParameters = ptParametersQTaskRef->pxObject;
            memset(&igi2_frame.tReleaseContext.tOut, 0, sizeof(igi2_frame.tReleaseContext.tOut));
            if ( ptHead )
              igi2_frame.tReleaseContext.tIn.tParentSpeed = *(struct real32x3_t *)&ptHead[37].ptParent;
            else
              memset(&igi2_frame.tReleaseContext.tIn.tParentSpeed, 0, sizeof(igi2_frame.tReleaseContext.tIn.tParentSpeed));
            igi2_frame.pfHandler(0, &igi2_frame.tReleaseContext);
            nBulletsFired = igi2_frame.tReleaseContext.tOut.nBulletsFired;
            if ( igi2_frame.tReleaseContext.tOut.nBulletsFired )
            {
              ptQTask[1].ptParent = (struct QTask_s *)igi2_frame.tReleaseContext.tOut.nDelay;
              if ( igi2_frame.ptFireType->isForceReload )
              {
                Weapon_GetFireTypeAmmoInfoFromWeaponTypeItem(
                  (struct Weapon_s *)ptQTask,
                  (struct WeaponTypeItem_s *)ptQTask[1].ptPrev,
                  v2,
                  &igi2_frame.tAmmoContext);
                if ( igi2_frame.tAmmoContext.ptAmmoType )
                {
                  AmmoTypeItemFromAmmoType = Weapon_GetAmmoTypeItemFromAmmoType(
                                               ptQTask,
                                               igi2_frame.tAmmoContext.ptAmmoType->zAmmoTypeScriptID);
                  AmmoTypeItemFromAmmoType->nAmmoCount -= igi2_frame.tReleaseContext.tOut.nBulletsFired;
                  ptQTask[1].tQTaskChildren.ptTail = nullptr;
                  return;
                }
              }
              else
              {
                v15 = *((_DWORD *)&ptTail->tQTaskChildren.ptHead + v2) - nBulletsFired - nBulletsFired;
                *((_DWORD *)&ptTail->tQTaskChildren.ptHead + v2) -= (int)(nBulletsFired);
                *((_DWORD *)&ptTail->tQTaskChildren.ptHead + v2) = v15 <= 0 ? 0 : v15;
                *igi2_frame.v16 += nBulletsFired;
              }
            }
            ptQTask[1].tQTaskChildren.ptTail = nullptr;
          }
        }
      }
    }
  }
}

void __cdecl sub_5284A0(struct QTask_s *ptQTask, _DWORD *pxContext)
{
  *(_DWORD *)&ptQTask[16].eQTaskType = 1;
  Weapon_SingleReleaseHandler(ptQTask, (void *)(pxContext[3] + 8));
}

// source: j/0/weapons/weapon.c:1444  [anchor-mhash]
void __cdecl Weapon_SingleReloadHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v11; };
    struct { char igi2_o1[4]; struct WeaponTypeGetAmmoInfoContext_s tGetAmmoContext; };
    char igi2_extent[44];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptPrev; // ebx
  struct QTask_s *ptTail; // esi
  struct QTaskNodeList_s *p_tQTaskChildren; // edi
  _BYTE *v5; // esi
  struct __anon_1b7c *p_tOut; // ebp
  struct QTaskNodeList_s *v7; // ebx
  struct AmmoTypeItem_s *AmmoTypeItemFromAmmoType; // eax
  int v9; // ecx
  int nAmmoCount; // edx

  ptPrev = ptQTask[1].ptPrev;
  if ( ptPrev )
  {
    ptTail = ptPrev->tQTaskChildren.ptTail;
    ptQTask[1].ptParent = nullptr;
    memset(&igi2_frame.tGetAmmoContext, 0, sizeof(igi2_frame.tGetAmmoContext));
    ((void (__cdecl *)(struct QTask_s *, struct WeaponTypeGetAmmoInfoContext_s *))QTask_aatQTaskFinalEvent[WeaponType_eGetAmmoInfoQTaskEvent][ptTail->eQTaskType].pfHandler)(
      ptTail,
      &igi2_frame.tGetAmmoContext);
    p_tQTaskChildren = &ptPrev->tQTaskChildren;
    v5 = (char *)&ptTail[32].tQTaskRefList.ptTail + 1;
    p_tOut = &igi2_frame.tGetAmmoContext.atAmmoItem[0].tOut;
    v7 = &ptQTask[3].tQTaskChildren;
    igi2_frame.v11 = 2;
    do
    {
      if ( p_tOut->ptAmmoType )
      {
        AmmoTypeItemFromAmmoType = Weapon_GetAmmoTypeItemFromAmmoType(ptQTask, p_tOut->ptAmmoType->zAmmoTypeScriptID);
        v9 = p_tOut->nRoundsPerClip - (unsigned int)p_tQTaskChildren->ptHead;
        v7->ptHead = nullptr;
        if ( !*(v5 - 1) )
        {
          if ( v9 )
          {
            if ( *v5 )
              v9 = 1;
            if ( AmmoTypeItemFromAmmoType )
            {
              if ( !ptQTask[1].tQTaskRefList.ptHead )
              {
                nAmmoCount = AmmoTypeItemFromAmmoType->nAmmoCount;
                if ( v9 > nAmmoCount )
                  v9 = AmmoTypeItemFromAmmoType->nAmmoCount;
                AmmoTypeItemFromAmmoType->nAmmoCount = nAmmoCount - v9;
              }
              if ( v9 )
                p_tQTaskChildren->ptHead = (struct QTask_s *)((char *)p_tQTaskChildren->ptHead + v9);
            }
          }
        }
      }
      p_tQTaskChildren = (struct QTaskNodeList_s *)((char *)p_tQTaskChildren + 4);
      v7 = (struct QTaskNodeList_s *)((char *)v7 + 28);
      p_tOut = (struct __anon_1b7c *)((char *)p_tOut + 20);
      v5 += 20;
      --igi2_frame.v11;
    }
    while ( igi2_frame.v11 );
    if ( ptQTask[1].tQTaskChildren.ptTail == (struct QTask_s *)4 )
      ptQTask[1].tQTaskChildren.ptTail = nullptr;
  }
}

// source: j/0/weapons/weapon.c:1534  [size]
void __cdecl Weapon_MultiReloadHandler(struct QTask_s *ptQTask, void *pxContext)
{
  Weapon_SingleReloadHandler(ptQTask, (void *)(*((_DWORD *)pxContext + 3) + 8));
}

// source: j/0/weapons/weapon.c:1552  [anchor-callee]
void __cdecl Weapon_SingleZoomHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptPrev; // ecx
  struct QTask_s *ptTail; // ecx
  struct QReferenceList_s *p_tQTaskRefList; // esi
  int v5; // edi
  int ptHead_low; // ecx
  void (__cdecl *pfHandler)(_DWORD, struct WeaponZoomContext_s *); // eax
  struct WeaponZoomContext_s tWeaponZoomContext; // [esp+0h] [ebp-10h] BYREF

  ptPrev = ptQTask[1].ptPrev;
  if ( ptPrev )
  {
    ptTail = ptPrev->tQTaskChildren.ptTail;
    tWeaponZoomContext.tIn.ptWeaponQTask = ptQTask;
    tWeaponZoomContext.tIn.ptIgnoreQTask = ptQTask->ptParent;
    tWeaponZoomContext.tIn.isInOut = *((_DWORD *)pxContext + 5);
    p_tQTaskRefList = &ptTail[32].tQTaskRefList;
    v5 = 2;
    do
    {
      ptHead_low = LOWORD(p_tQTaskRefList->ptHead);
      if ( QTask_IsQTaskTypeValid(ptHead_low) )
      {
        tWeaponZoomContext.tIn.pxFireTypeParameters = p_tQTaskRefList[1].ptHead->pxObject;
        pfHandler = (void (__cdecl *)(_DWORD, struct WeaponZoomContext_s *))QTask_aatQTaskFinalEvent[Weapon_eZoomQTaskEvent][ptHead_low].pfHandler;
        if ( pfHandler )
          pfHandler(0, &tWeaponZoomContext);
      }
      p_tQTaskRefList = (struct QReferenceList_s *)((char *)p_tQTaskRefList + 20);
      --v5;
    }
    while ( v5 );
  }
}

// source: j/0/weapons/weapon.c:1612  [size]
void __cdecl Weapon_MultiZoomHandler(struct QTask_s *ptQTask, void *pxContext)
{
  Weapon_SingleZoomHandler(ptQTask, (void *)(*((_DWORD *)pxContext + 3) + 8));
}

// source: j/0/weapons/weapon.c:1630  [anchor-callee]
void __cdecl Weapon_SingleActivateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { enum WeaponOverlayStatus_e v21; };
    struct { char igi2_o1[16]; struct QTask_s *v22; };
    struct { char igi2_o2[20]; struct QTask_s *ptParent; };
    struct { char igi2_o3[24]; _DWORD v24[4]; };
    struct { char igi2_o4[40]; struct WeaponGetFireTypeAmmoContext_s nFireType; };
    char igi2_extent[60];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptPrev; // esi
  struct WeaponTypeItem_s *WeaponTypeItemFromWeaponType; // eax
  struct QTask_s *v4; // edi
  struct WeaponType_s *ptWeaponType; // edx
  struct QTask_s *ptTail; // eax
  int i; // edi
  int v8; // ecx
  void *pfHandler; // eax
  struct QTask_s *v10; // eax
  struct QReference_s *v11; // ecx
  char *p_ptPrev; // eax
  struct QTask_s *v13; // ecx
  struct QTask_s *ptNext; // eax
  struct QTask_s *v15; // edx
  struct QTask_s *v16; // eax
  bool v17; // zf
  int j; // esi
  int v19; // ecx
  void (__cdecl *v20)(_DWORD, void *); // eax

  igi2_frame.ptParent = ptQTask->ptParent;
  ptPrev = ptQTask[1].ptPrev;
  WeaponTypeItemFromWeaponType = Weapon_GetWeaponTypeItemFromWeaponType(ptQTask, (char *)pxContext + 20);
  v4 = (struct QTask_s *)WeaponTypeItemFromWeaponType;
  igi2_frame.v22 = (struct QTask_s *)WeaponTypeItemFromWeaponType;
  if ( WeaponTypeItemFromWeaponType )
  {
    if ( WeaponTypeItemFromWeaponType->isActive )
    {
      if ( ptPrev )
      {
        ptWeaponType = WeaponTypeItemFromWeaponType->ptWeaponType;
        ptTail = ptPrev->tQTaskChildren.ptTail;
        igi2_frame.v24[0] = ptQTask;
        igi2_frame.v24[1] = igi2_frame.ptParent;
        igi2_frame.v24[2] = ptWeaponType;
        igi2_frame.v24[3] = ptTail;
        for ( i = 1300; i < 1340; i += 20 )
        {
          v8 = *(unsigned __int16 *)((char *)&ptPrev->tQTaskChildren.ptTail->ptNext + i);
          if ( QTask_IsQTaskTypeValid(v8) )
          {
            pfHandler = QTask_aatQTaskFinalEvent[Weapon_eDeActivateQTaskEvent][v8].pfHandler;
            if ( pfHandler )
              ((void (__cdecl *)(_DWORD, _DWORD *))pfHandler)(0, igi2_frame.v24);
          }
        }
        Weapon_SetOverlayStatus((struct QTask_s *)v8, igi2_frame.v21, 0, (int)ptQTask);
        v10 = ptPrev->tQTaskChildren.ptTail;
        v11 = v10[16].tQTaskRefList.ptTail;
        if ( v11 == (struct QReference_s *)4
          || v11 == (struct QReference_s *)7
          || !strcmp((char *)&v10[2].ptPrev, "WEAPON_ID_RPG18") )
        {
          Weapon_GetFireTypeAmmoInfoFromWeaponTypeItem(
            (struct Weapon_s *)ptQTask,
            (struct WeaponTypeItem_s *)ptQTask[1].ptPrev,
            0,
            &igi2_frame.nFireType);
          if ( !igi2_frame.nFireType.nAmmoAvailable )
          {
            p_ptPrev = (char *)&ptPrev->tQTaskChildren.ptTail[2].ptPrev;
            if ( strcmp(p_ptPrev, "WEAPON_ID_RPG18") || !ptPrev->tQTaskChildren.ptHead )
              Weapon_DisableWeaponType(ptQTask, p_ptPrev, true);
          }
        }
        v4 = igi2_frame.v22;
      }
      v13 = ptQTask[4].tQTaskChildren.ptTail;
      ptQTask[1].ptPrev = v4;
      ptQTask[1].ptNext = v4;
      ptNext = v13->ptNext;
      v15 = nullptr;
      if ( v13->ptNext )
      {
        while ( v4 != v13 )
        {
          v13 = ptNext;
          ptNext = ptNext->ptNext;
          v15 = (struct QTask_s *)((char *)v15 + 1);
          if ( !ptNext )
            goto LABEL_22;
        }
      }
      else
      {
LABEL_22:
        v15 = nullptr;
      }
      v16 = HumanPlayer_ptQTask;
      v17 = igi2_frame.ptParent == HumanPlayer_ptQTask;
      ptQTask[1].tQTaskChildren.ptHead = v15;
      ptQTask[1].ptParent = nullptr;
      ptQTask[16].tQTaskChildren.ptTail = nullptr;
      ptQTask[16].tQTaskRefList.ptHead = nullptr;
      ptQTask[1].tQTaskRefList.ptTail = nullptr;
      ptQTask[1].tQTaskChildren.ptTail = nullptr;
      if ( v17 )
        v16[80].tQTaskRefList.ptTail = (struct QReference_s *)4;
      for ( j = 1300; j < 1340; j += 20 )
      {
        v19 = *(unsigned __int16 *)((char *)&v4->tQTaskChildren.ptTail->ptNext + j);
        if ( QTask_IsQTaskTypeValid(v19) )
        {
          v20 = (void (__cdecl *)(_DWORD, void *))QTask_aatQTaskFinalEvent[Weapon_eActivateQTaskEvent][v19].pfHandler;
          if ( v20 )
            v20(0, pxContext);
        }
      }
    }
    else
    {
      NetManager_LogMessage("Weapon_SingleActivateHandler: weapontypeitem not active\n");
    }
  }
  else
  {
    NetManager_LogMessage("Weapon_SingleActivateHandler: weapontypeitem not found\n");
  }
}

void __cdecl sub_528890(struct QTask_s *a1, _DWORD *pxContext)
{
  Weapon_SingleActivateHandler(a1, (void *)(pxContext[3] + 8));
}

// source: j/0/weapons/weapon.c:1822  [size]
void __cdecl Weapon_MultiDeActivateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  if ( ptQTask->ptParent == HumanPlayer_ptQTask )
    HumanPlayer_ptQTask[80].tQTaskRefList.ptTail = nullptr;
}

void __cdecl sub_5288D0(struct QTask_s *a1, void *a2)
{
  if ( a1->ptParent == HumanPlayer_ptQTask )
    HumanPlayer_ptQTask[80].tQTaskRefList.ptTail = nullptr;
}

void __cdecl sub_5288F0(struct QTask_s *a1)
{
  struct QTask_s *ptHead; // ecx
  int v2; // edx
  struct QTask_s *v3; // eax
  int v4; // esi
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v6; // edx

  ptHead = a1->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v2 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v3 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v3 = nullptr;
      v4 = Attach_eUpdateAttachmentEvent;
      QTask_atProtectedQTaskStack[v2].ptQTask = v3;
      pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[v4][ptHead->eQTaskType].pfHandler;
      v6 = v2 + 1;
      QTask_nProtectedQTaskStackOffset = v6;
      if ( pfHandler )
      {
        pfHandler(ptHead);
        v6 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v6];
      v2 = v6 - 1;
      QTask_nProtectedQTaskStackOffset = v2;
    }
    while ( ptHead );
  }
}

void __cdecl sub_528970(struct QTask_s *a1, void *a2)
{
  struct QTask_s *ptHead; // eax
  int v3; // edx
  struct QTask_s *v4; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // ecx
  int v6; // edx

  ptHead = a1->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v3 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v4 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v4 = nullptr;
      QTask_atProtectedQTaskStack[v3].ptQTask = v4;
      pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRegisterQTaskEvent][ptHead->eQTaskType].pfHandler;
      v6 = v3 + 1;
      QTask_nProtectedQTaskStackOffset = v6;
      if ( pfHandler )
      {
        pfHandler(ptHead, a2);
        v6 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v6];
      v3 = v6 - 1;
      QTask_nProtectedQTaskStackOffset = v3;
    }
    while ( ptHead );
  }
}

void __cdecl sub_5289F0(struct QTask_s *a1, void *a2)
{
  struct QTask_s *ptHead; // eax
  int v3; // edx
  struct QTask_s *v4; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // ecx
  int v6; // edx

  ptHead = a1->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v3 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v4 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v4 = nullptr;
      QTask_atProtectedQTaskStack[v3].ptQTask = v4;
      pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRemoveQTaskEvent][ptHead->eQTaskType].pfHandler;
      v6 = v3 + 1;
      QTask_nProtectedQTaskStackOffset = v6;
      if ( pfHandler )
      {
        pfHandler(ptHead, a2);
        v6 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v6];
      v3 = v6 - 1;
      QTask_nProtectedQTaskStackOffset = v3;
    }
    while ( ptHead );
  }
}

// source: j/0/weapons/weapon.c:1873  [size]
__int16 __cdecl Weapon_GetFireQTaskEvent()
{
  return Weapon_eFireQTaskEvent;
}

// source: j/0/weapons/weapon.c:1887  [size]
__int16 __cdecl Weapon_GetGetWeaponPrecisionQTaskEvent()
{
  return Weapon_eGetWeaponPrecisionQTaskEvent;
}

// source: j/0/weapons/weapon.c:1901  [size]
__int16 __cdecl Weapon_GetReleaseQTaskEvent()
{
  return Weapon_eReleaseQTaskEvent;
}

// source: j/0/weapons/weapon.c:1915  [size]
__int16 __cdecl Weapon_GetReloadQTaskEvent()
{
  return Weapon_eReloadQTaskEvent;
}

// source: j/0/weapons/weapon.c:1929  [size]
__int16 __cdecl Weapon_GetZoomQTaskEvent()
{
  return Weapon_eZoomQTaskEvent;
}

// source: j/0/weapons/weapon.c:1943  [size]
__int16 __cdecl Weapon_GetActivateQTaskEvent()
{
  return Weapon_eActivateQTaskEvent;
}

// source: j/0/weapons/weapon.c:1957  [size]
__int16 __cdecl Weapon_GetDeActivateQTaskEvent()
{
  return Weapon_eDeActivateQTaskEvent;
}

// source: j/0/weapons/weapon.c:1971  [size]
__int16 __cdecl Weapon_GetGetParentParametersQTaskEvent()
{
  return Weapon_eGetParentParametersQTaskEvent;
}

// source: j/0/weapons/weapon.c:1985  [size]
__int16 __cdecl Weapon_GetCreateProjectileQTaskEvent()
{
  return Weapon_eCreateProjectileQTaskEvent;
}

// source: j/0/weapons/weapon.c:1999  [size]
__int16 __cdecl Weapon_GetPositionOverlayQTaskEvent()
{
  return Weapon_ePositionOverlayQTaskEvent;
}

// source: j/0/weapons/weapon.c:2013  [size]
__int16 __cdecl Weapon_GetGetWeaponObjectQTaskEvent()
{
  return Weapon_eGetWeaponObjectEvent;
}

// source: j/0/weapons/weapon.c:2027  [size]
struct QTask_s *__cdecl Weapon_New(struct QTask_s *ptParentQTask, int iOwnerQTaskID)
{
  struct QTask_s *result; // eax

  result = QTask_NewFn(ptParentQTask, Weapon_eQTaskType, nullptr);
  result[16].tQTaskRefList.ptTail = (struct QReference_s *)iOwnerQTaskID;
  return result;
}

// source: j/0/weapons/weapon.c:2049  [anchor-hash]
void __cdecl Weapon_InitHandlers()
{
  unsigned __int16 v0; // si
  unsigned __int16 v1; // si

  if ( Game_eGameMode )
  {
    if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
    {
      v1 = Weapon_eQTaskType;
      QTask_LinkQTaskEventHandlerFn(Weapon_eQTaskType, Weapon_eFireQTaskEvent, Weapon_MultiFireHandler);
      QTask_LinkQTaskEventHandlerFn(
        v1,
        Weapon_eReleaseQTaskEvent,
        (void (__cdecl *)(struct QTask_s *, void *))sub_5284A0);
      QTask_LinkQTaskEventHandlerFn(v1, Weapon_eReloadQTaskEvent, Weapon_MultiReloadHandler);
      QTask_LinkQTaskEventHandlerFn(v1, Weapon_eZoomQTaskEvent, Weapon_MultiZoomHandler);
      QTask_LinkQTaskEventHandlerFn(
        v1,
        Weapon_eActivateQTaskEvent,
        (void (__cdecl *)(struct QTask_s *, void *))sub_528890);
      QTask_LinkQTaskEventHandlerFn(
        v1,
        Weapon_eDeActivateQTaskEvent,
        (void (__cdecl *)(struct QTask_s *, void *))sub_5288D0);
    }
  }
  else
  {
    v0 = Weapon_eQTaskType;
    QTask_LinkQTaskEventHandlerFn(Weapon_eQTaskType, Weapon_eFireQTaskEvent, Weapon_SingleFireHandler);
    QTask_LinkQTaskEventHandlerFn(v0, Weapon_eReleaseQTaskEvent, Weapon_SingleReleaseHandler);
    QTask_LinkQTaskEventHandlerFn(v0, Weapon_eReloadQTaskEvent, Weapon_SingleReloadHandler);
    QTask_LinkQTaskEventHandlerFn(v0, Weapon_eZoomQTaskEvent, Weapon_SingleZoomHandler);
    QTask_LinkQTaskEventHandlerFn(v0, Weapon_eActivateQTaskEvent, Weapon_SingleActivateHandler);
    QTask_LinkQTaskEventHandlerFn(
      v0,
      Weapon_eDeActivateQTaskEvent,
      (void (__cdecl *)(struct QTask_s *, void *))Weapon_MultiDeActivateHandler);
  }
}

// source: j/0/weapons/weapon.c:2081  [size]
enum bool __cdecl Weapon_SetUnlimitedAmmoStatus(
        struct QTask_s *ptWeaponQTask,
        enum bool isUnlimitedAmmo)
{
  ptWeaponQTask[1].tQTaskRefList.ptHead = (struct QReference_s *)isUnlimitedAmmo;
  return isUnlimitedAmmo;
}

// source: j/0/weapons/weapon.c:2099  [size]
enum bool __cdecl Weapon_GetUnlimitedAmmoStatus(struct QTask_s *ptWeaponQTask)
{
  return (enum bool)ptWeaponQTask[1].tQTaskRefList.ptHead;
}

// source: j/0/weapons/weapon.c:2117  [anchor-callee]
void __cdecl Weapon_ActivateAllWeapons(struct QTask_s *ptWeaponQTask)
{
  struct QTask_s *ptTail; // esi
  struct QTask_s *i; // ebp
  struct QTask_s *v3; // edx
  int v4; // ecx
  int nRoundsPerClip; // edx
  struct QReference_s *v6; // ecx
  struct QReference_s *j; // eax
  struct WeaponTypeGetAmmoInfoContext_s tGetAmmoInfoContext; // [esp+Ch] [ebp-28h] BYREF

  ptTail = ptWeaponQTask[4].tQTaskChildren.ptTail;
  for ( i = ptTail->ptNext; i; i = i->ptNext )
  {
    v3 = ptTail->tQTaskChildren.ptTail;
    memset(&tGetAmmoInfoContext, 0, sizeof(tGetAmmoInfoContext));
    v4 = 511 * WeaponType_eGetAmmoInfoQTaskEvent;
    LOBYTE(ptTail->tQTaskRefList.ptTail) = 1;
    ((void (__cdecl *)(struct QTask_s *, struct WeaponTypeGetAmmoInfoContext_s *))QTask_aatQTaskFinalEvent[0][v3->eQTaskType + v4].pfHandler)(
      v3,
      &tGetAmmoInfoContext);
    nRoundsPerClip = tGetAmmoInfoContext.atAmmoItem[1].tOut.nRoundsPerClip;
    ptTail->tQTaskChildren.ptHead = (struct QTask_s *)tGetAmmoInfoContext.atAmmoItem[0].tOut.nRoundsPerClip;
    ptTail->tQTaskChildren.ptMiddle = (struct QTask_s *)nRoundsPerClip;
    ptTail = i;
  }
  v6 = ptWeaponQTask[4].tQTaskRefList.ptTail;
  for ( j = v6->ptNext; j; j = j->ptNext )
  {
    v6->pxObject = (char *)v6->pxObject + 100;
    v6 = j;
  }
}

// source: j/0/weapons/weapon.c:2170  [anchor-callee]
void __cdecl Weapon_ClearAllWeapons(struct QTask_s *ptWeaponQTask)
{
  struct QTask_s *ptTail; // ecx
  struct QTask_s *i; // eax
  struct QTaskNodeList_s *p_tQTaskChildren; // ecx
  struct QReference_s *v4; // ecx
  struct QReference_s *j; // eax

  ptTail = ptWeaponQTask[4].tQTaskChildren.ptTail;
  ptWeaponQTask[1].ptPrev = nullptr;
  ptWeaponQTask[1].ptNext = nullptr;
  ptWeaponQTask[1].tQTaskChildren.ptHead = nullptr;
  for ( i = ptTail->ptNext; i; i = i->ptNext )
  {
    LOBYTE(ptTail->tQTaskRefList.ptTail) = 0;
    p_tQTaskChildren = &ptTail->tQTaskChildren;
    p_tQTaskChildren->ptHead = nullptr;
    p_tQTaskChildren->ptMiddle = nullptr;
    ptTail = i;
  }
  v4 = ptWeaponQTask[4].tQTaskRefList.ptTail;
  for ( j = v4->ptNext; j; j = j->ptNext )
  {
    v4->pxObject = nullptr;
    v4 = j;
  }
}

// source: j/0/weapons/weapon.c:2221  [size]
enum WeaponStatus_e __cdecl Weapon_SetStatus(
        struct QTask_s *ptWeaponQTask,
        enum WeaponStatus_e eWeaponStatus)
{
  ptWeaponQTask[1].tQTaskChildren.ptTail = (struct QTask_s *)eWeaponStatus;
  return eWeaponStatus;
}

// source: j/0/weapons/weapon.c:2239  [size]
enum WeaponStatus_e __cdecl Weapon_GetStatus(struct QTask_s *ptWeaponQTask)
{
  return (enum WeaponStatus_e)ptWeaponQTask[1].tQTaskChildren.ptTail;
}

// source: j/0/weapons/weapon.c:2257  [anchor-callee]
void __cdecl Weapon_SetKickBack(
        struct QTask_s *ptWeaponQTask,
        float vAlphaKickBack,
        float vGammaKickBack,
        float vKickBackDamping,
        float vCrossHairDamping)
{
  *(float *)&ptWeaponQTask[2].ptPrev = vAlphaKickBack;
  *(float *)&ptWeaponQTask[1].eQTaskType = vKickBackDamping;
  *(float *)&ptWeaponQTask[2].tQTaskChildren.ptHead = vGammaKickBack;
  *(float *)&ptWeaponQTask[2].ptNext = vCrossHairDamping;
  ptWeaponQTask[16].ptParent = (struct QTask_s *)(vAlphaKickBack != 0.0 || vGammaKickBack != 0.0);
}

// source: j/0/weapons/weapon.c:2280  [anchor-mhash]
float *__cdecl Weapon_GetKickBack(
        struct QTask_s *ptWeaponQTask,
        float *pvAlphaKickBack,
        float *pvGammaKickBack,
        float *pvKickBackDamping,
        float *pvCrossHairDamping)
{
  if ( pvAlphaKickBack )
    *pvAlphaKickBack = *(float *)&ptWeaponQTask[2].ptPrev;
  if ( pvGammaKickBack )
  {
    pvAlphaKickBack = (float *)ptWeaponQTask[2].tQTaskChildren.ptHead;
    *(_DWORD *)pvGammaKickBack = pvAlphaKickBack;
  }
  if ( pvKickBackDamping )
    *pvKickBackDamping = *(float *)&ptWeaponQTask[1].eQTaskType;
  if ( pvCrossHairDamping )
  {
    pvAlphaKickBack = (float *)ptWeaponQTask[2].ptNext;
    *(_DWORD *)pvCrossHairDamping = pvAlphaKickBack;
  }
  return pvAlphaKickBack;
}

// source: j/0/weapons/weapon.c:2313  [size]
int __cdecl Weapon_SetTeam(struct QTask_s *ptWeaponQTask, int eTeam)
{
  ptWeaponQTask[2].tQTaskChildren.ptMiddle = (struct QTask_s *)eTeam;
  return eTeam;
}

// source: j/0/weapons/weapon.c:2331  [size]
int __cdecl Weapon_GetTeam(struct QTask_s *ptWeaponQTask)
{
  return (int)ptWeaponQTask[2].tQTaskChildren.ptMiddle;
}

// source: j/0/weapons/weapon.c:2349  [anchor-mhash]
struct QTask_s *__cdecl Weapon_SetHumanOperator(
        struct QTask_s *ptWeaponQTask,
        struct QTask_s *ptHumanQTask)
{
  struct QTask_s *result; // eax
  struct QTask_s *ptNext; // esi
  struct QTask_s *ptHead; // esi
  struct QReference_s *v6; // eax

  result = ptWeaponQTask[2].tQTaskChildren.ptTail;
  if ( result )
    QReference_Delete((struct QReference_s *)result, &QTask_tQTaskRefPool);
  if ( ptHumanQTask )
  {
    result = (struct QTask_s *)QTask_NewQTaskRef(ptHumanQTask);
    ptWeaponQTask[2].tQTaskChildren.ptTail = result;
    ptNext = ptWeaponQTask[5].ptNext;
    if ( ptNext )
    {
      ptHead = ptNext->tQTaskChildren.ptHead;
      if ( ptHead )
      {
        v6 = (struct QReference_s *)ptHead[3].ptNext;
        if ( v6 )
          QReference_Delete(v6, &QTask_tQTaskRefPool);
        result = (struct QTask_s *)QTask_NewQTaskRef(ptHumanQTask);
        ptHead[3].ptNext = result;
      }
    }
  }
  else
  {
    ptWeaponQTask[2].tQTaskChildren.ptTail = nullptr;
  }
  return result;
}

// source: j/0/weapons/weapon.c:2390  [anchor-hash]
struct QTask_s *__cdecl Weapon_GetHumanOperator(struct QTask_s *ptWeaponQTask)
{
  struct QTask_s *ptTail; // eax

  ptTail = ptWeaponQTask[2].tQTaskChildren.ptTail;
  if ( ptTail )
    return ptTail->tQTaskChildren.ptHead;
  else
    return nullptr;
}

// source: j/0/weapons/weapon.c:2413  [anchor-callee]
int __cdecl Weapon_Fire(struct QTask_s *ptWeaponQTask, int nFireType)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct WeaponType_s *ptWeaponType; };
    struct { char igi2_o1[4]; struct real64x3_t ptReal; };
    struct { char igi2_o2[28]; _BYTE ptNetManagerGameMessage[24]; };
    struct { char igi2_o3[52]; struct int32x3_t ptInt; };
    struct { char igi2_o4[64]; struct real32x9_t ptSource; };
    struct { char igi2_o5[140]; int v16; };
    struct { char igi2_o6[148]; struct WeaponTypeGetAmmoInfoContext_s ptContext; };
    char igi2_extent[188];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int result; // eax
  int v4; // edi
  struct Flow_t *v5; // esi
  struct QTask_s **v6; // eax
  struct QTask_s *ptParent; // ecx
  char v8; // bl
  struct QTask_s *v9; // eax
  void (__cdecl *pfHandler)(struct QTask_s *, struct real32x3_t *); // ecx

  result = (int)ptWeaponQTask[1].ptPrev;
  if ( result )
    igi2_frame.ptWeaponType = *(struct WeaponType_s **)(result + 16);
  else
    igi2_frame.ptWeaponType = nullptr;
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER && !*(_DWORD *)&ptWeaponQTask[16].eQTaskType )
  {
    result = (int)HumanPlayer_ptQTask;
    if ( HumanPlayer_ptQTask )
      BYTE1(HumanPlayer_ptQTask[84].ptNext) = 1;
    return result;
  }
  if ( result )
  {
    if ( QTask_aatQTaskFinalEvent[Weapon_eGetParentParametersQTaskEvent][ptWeaponQTask->ptParent->eQTaskType].pfHandler )
    {
      v4 = 4 * (5 * nFireType + 325);
      result = QTask_IsQTaskTypeValid(*(_DWORD *)(*(_DWORD *)(result + 16) + v4));
      if ( result )
      {
        WeaponType_GetAmmoInfo(igi2_frame.ptWeaponType, &igi2_frame.ptContext);
        result = (int)ptWeaponQTask[1].ptPrev;
        if ( !*(_DWORD *)(result + 4 * nFireType + 8) )
        {
          ptWeaponQTask[1].tQTaskChildren.ptTail = (struct QTask_s *)4;
          return result;
        }
        result = igi2_frame.ptWeaponType->anRoundsInSuccession[*(_DWORD *)(result + 24)];
        if ( result )
        {
          if ( ptWeaponQTask[1].ptParent
            && *(struct QTask_s **)((char *)&igi2_frame.ptWeaponType->tQTask.ptNext + v4) != (struct QTask_s *)Zoom_eQTaskType
            || (result == 1 || nFireType == 1) && *((_DWORD *)&ptWeaponQTask[2].tQTaskRefList.ptMiddle + 7 * nFireType) )
          {
            return result;
          }
          if ( (int)(*((_DWORD *)&ptWeaponQTask[3].tQTaskChildren.ptHead + 7 * nFireType)) >= result )
          {
            *((_DWORD *)&ptWeaponQTask[2].tQTaskRefList.ptMiddle + 7 * nFireType) = 0;
            ptWeaponQTask[1].tQTaskChildren.ptTail = (struct QTask_s *)2;
            return result;
          }
        }
        v5 = Flow_ptFlow;
        v6 = &ptWeaponQTask->ptNext + 7 * nFireType;
        if ( !v6[27] )
        {
          ptParent = ptWeaponQTask->ptParent;
          if ( igi2_frame.ptWeaponType->eWeaponType == WEAPONTYPE_GRENADE && ptParent->eQTaskType == HumanPlayer_eQTaskType )
            *(_DWORD *)&ptWeaponQTask[2].eQTaskType = Flow_ptFlow->nTicks - *(_DWORD *)&ptParent[80].eQTaskType;
          else
            v6[29] = (struct QTask_s *)Flow_ptFlow->nTicks;
          v6[26] = (struct QTask_s *)1;
          v6[27] = (struct QTask_s *)1;
        }
        igi2_frame.ptNetManagerGameMessage[20] = ptWeaponQTask[1].ptPrev->tQTaskChildren.ptTail[3].tQTaskRefList.ptTail;
        igi2_frame.ptNetManagerGameMessage[21] = nFireType;
        v8 = *((_BYTE *)v6 + 116);
        v9 = ptWeaponQTask->ptParent;
        igi2_frame.ptNetManagerGameMessage[22] = LOBYTE(v5->nTicks) - v8;
        igi2_frame.v16 = 1;
        pfHandler = (void (__cdecl *)(struct QTask_s *, struct real32x3_t *))QTask_aatQTaskFinalEvent[Weapon_eGetParentParametersQTaskEvent][v9->eQTaskType].pfHandler;
        if ( pfHandler )
          pfHandler(v9, &igi2_frame.ptSource.tY);
        qmemcpy(&igi2_frame.ptReal, &igi2_frame.ptSource.tY, sizeof(igi2_frame.ptReal));
        igi2_frame.ptReal.vX = *(double *)&igi2_frame.ptSource.tY.vX * 0.000244140625;
        igi2_frame.ptReal.vY = igi2_frame.ptReal.vY * 0.000244140625;
        igi2_frame.ptReal.vZ = igi2_frame.ptReal.vZ * 0.000244140625;
        World_SetInt32CentimeterFromReal64Meter(&igi2_frame.ptReal, &igi2_frame.ptInt);
        Real32x9_GetAngles((struct real32x9_t *)&igi2_frame.ptSource.nOps, &igi2_frame.ptSource.tX.vX, &igi2_frame.ptSource.tX.vY, &igi2_frame.ptSource.tX.vZ);
        return Weapon_SendWeaponEvent(ptWeaponQTask, 0x57534652u, igi2_frame.ptNetManagerGameMessage, 48);
      }
    }
  }
  return result;
}

// source: j/0/weapons/weapon.c:2558  [anchor-mhash]
struct QTask_s *__cdecl Weapon_Reload(struct QTask_s *ptWeaponQTask)
{
  struct WeaponNetReloadContext_s tReloadContext; // [esp+4h] [ebp-14h] BYREF

  return (struct QTask_s *)Weapon_SendWeaponEvent(ptWeaponQTask, 0x5753524Cu, &tReloadContext, 20);
}

// source: j/0/weapons/weapon.c:2577  [anchor-caller]
void __cdecl Weapon_Zoom(struct QTask_s *ptWeaponQTask, enum bool isInOut)
{
  int Timer; // eax
  struct QReference_s *ptTail; // ecx
  struct QTask_s *v4; // eax
  struct QTask_s *ptHead; // edi
  struct Client_s *ClientFromHumanQTask; // eax
  struct WeaponNetZoomContext_s tZoomContext; // [esp+4h] [ebp-18h] BYREF

  tZoomContext.isInOut = isInOut;
  if ( Game_eGameMode )
  {
    if ( Game_eGameMode != GAME_GAMEMODE_MULTIPLAYER )
    {
      LDebug_Error("Weapon: GameMode (%d) not defined", Game_eGameMode);
      abort();
    }
    tZoomContext.tBaseGameMessage.tGameMessage.eGameMessage = 1465080397;
    Timer = NetManager_GetTimer();
    ptTail = ptWeaponQTask[16].tQTaskRefList.ptTail;
    tZoomContext.tBaseGameMessage.tGameMessage.nLocalTime = Timer;
    v4 = ptWeaponQTask[2].tQTaskChildren.ptTail;
    tZoomContext.tBaseGameMessage.iOwnerQTaskID = (int)ptTail;
    tZoomContext.tBaseGameMessage.eSource = -1;
    if ( v4 )
    {
      tZoomContext.tBaseGameMessage.isOwnerHuman = 1;
      ptHead = v4->tQTaskChildren.ptHead;
      if ( ptHead )
      {
        ClientFromHumanQTask = NetManager_GetClientFromHumanQTask(ptHead);
        if ( ClientFromHumanQTask )
          tZoomContext.tBaseGameMessage.eSource = ClientFromHumanQTask->eNetworkID;
      }
    }
    else
    {
      tZoomContext.tBaseGameMessage.isOwnerHuman = 0;
      tZoomContext.tBaseGameMessage.eSource = 0;
    }
    Weapon_SingleZoomHandler(ptWeaponQTask, &tZoomContext);
    NetManager_SendGameMessage(
      0,
      (int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle,
      NETWORKQUEUE_GUARANTEED,
      &tZoomContext.tBaseGameMessage.tGameMessage,
      0x18u);
  }
  else if ( Weapon_eZoomQTaskEvent != 512 )
  {
    ((void (__cdecl *)(struct QTask_s *, struct WeaponNetZoomContext_s *))QTask_aatQTaskFinalEvent[Weapon_eZoomQTaskEvent][ptWeaponQTask->eQTaskType].pfHandler)(
      ptWeaponQTask,
      &tZoomContext);
  }
}

// source: j/0/weapons/weapon.c:2597  [anchor-callee]
void __cdecl Weapon_Activate(
        struct QTask_s *ptWeaponQTask,
        char *pzWeaponType,
        enum bool isForceLocal)
{
  int v3; // edx
  char v4; // cl
  int Timer; // eax
  struct QReference_s *ptTail; // ecx
  struct QTask_s *v7; // eax
  struct QTask_s *ptHead; // eax
  struct Client_s *ClientFromHumanQTask; // eax
  struct WeaponNetActivateContext_s tActivateContext; // [esp+0h] [ebp-34h] BYREF

  v3 = tActivateContext.zWeaponTypeScriptID - pzWeaponType;
  do
  {
    v4 = *pzWeaponType;
    pzWeaponType[v3] = *pzWeaponType;
    ++pzWeaponType;
  }
  while ( v4 );
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    if ( isForceLocal )
    {
      tActivateContext.tBaseGameMessage.tGameMessage.eGameMessage = 1465074004;
      tActivateContext.tBaseGameMessage.tGameMessage.nLocalTime = NetManager_GetTimer();
      tActivateContext.tBaseGameMessage.iOwnerQTaskID = -1;
      tActivateContext.tBaseGameMessage.isOwnerHuman = 1;
      tActivateContext.tBaseGameMessage.eSource = -1;
LABEL_6:
      Weapon_SingleActivateHandler(ptWeaponQTask, &tActivateContext);
      return;
    }
LABEL_12:
    tActivateContext.tBaseGameMessage.tGameMessage.eGameMessage = 1465074004;
    Timer = NetManager_GetTimer();
    ptTail = ptWeaponQTask[16].tQTaskRefList.ptTail;
    tActivateContext.tBaseGameMessage.tGameMessage.nLocalTime = Timer;
    v7 = ptWeaponQTask[2].tQTaskChildren.ptTail;
    tActivateContext.tBaseGameMessage.iOwnerQTaskID = (int)ptTail;
    tActivateContext.tBaseGameMessage.eSource = -1;
    if ( v7 )
    {
      tActivateContext.tBaseGameMessage.isOwnerHuman = 1;
      ptHead = v7->tQTaskChildren.ptHead;
      if ( ptHead )
      {
        ClientFromHumanQTask = NetManager_GetClientFromHumanQTask(ptHead);
        if ( ClientFromHumanQTask )
          tActivateContext.tBaseGameMessage.eSource = ClientFromHumanQTask->eNetworkID;
      }
    }
    else
    {
      tActivateContext.tBaseGameMessage.isOwnerHuman = 0;
      tActivateContext.tBaseGameMessage.eSource = 0;
    }
    if ( !tActivateContext.tBaseGameMessage.iOwnerQTaskID )
    {
      NetManager_SendGameMessage(
        0,
        (int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle,
        NETWORKQUEUE_GUARANTEED,
        &tActivateContext.tBaseGameMessage.tGameMessage,
        0x34u);
      ptWeaponQTask[1].tQTaskChildren.ptTail = (struct QTask_s *)5;
      return;
    }
    goto LABEL_6;
  }
  if ( Game_eGameMode )
  {
    if ( Game_eGameMode != GAME_GAMEMODE_MULTIPLAYER )
    {
      LDebug_Error("Weapon: GameMode (%d) not defined", Game_eGameMode);
      abort();
    }
    goto LABEL_12;
  }
  if ( Weapon_eActivateQTaskEvent != 512 )
    ((void (__cdecl *)(struct QTask_s *, struct WeaponNetActivateContext_s *))QTask_aatQTaskFinalEvent[Weapon_eActivateQTaskEvent][ptWeaponQTask->eQTaskType].pfHandler)(
      ptWeaponQTask,
      &tActivateContext);
}

// source: j/0/weapons/weapon.c:2639  [anchor-mhash]
void __cdecl Weapon_UpdateStatus(struct QTask_s *ptWeaponQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct WeaponType_s *ptActiveWeaponType; };
    struct { char igi2_o1[4]; struct WeaponTypeItem_s *ptActiveWeaponTypeItem; };
    struct { char igi2_o2[8]; struct QTask_s **v14; };
    struct { char igi2_o3[12]; char ptNetManagerGameMessage[20]; };
    struct { char igi2_o4[32]; int eID; };
    struct { char igi2_o5[36]; char v17; };
    struct { char igi2_o6[37]; char v18; };
    struct { char igi2_o7[44]; _BYTE v19[24]; };
    struct { char igi2_o8[68]; float pvAlpha; };
    struct { char igi2_o9[72]; float pvBeta; };
    struct { char igi2_o10[76]; float pvGamma; };
    struct { char igi2_o11[80]; int v23; };
    struct { char igi2_o12[88]; struct WeaponGetFireTypeAmmoContext_s tAmmoContext; };
    struct { char igi2_o13[108]; struct WeaponGetParentParameterContext_s tParentContext; };
    char igi2_extent[180];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptPrev; // eax
  int i; // ebx
  struct WeaponTypeItem_s *v3; // esi
  int iActiveFireMode; // edi
  int v5; // eax
  struct QTask_s *ptHead; // ecx
  char v7; // cl
  int nTicks; // ecx
  struct QTask_s *v9; // eax
  struct QTask_s *ptParent; // eax
  void (__cdecl *pfHandler)(struct QTask_s *, struct WeaponGetParentParameterContext_s *); // ecx

  ptPrev = ptWeaponQTask[1].ptPrev;
  igi2_frame.ptActiveWeaponTypeItem = (struct WeaponTypeItem_s *)ptPrev;
  if ( ptPrev )
  {
    igi2_frame.ptActiveWeaponType = (struct WeaponType_s *)ptPrev->tQTaskChildren.ptTail;
    if ( QTask_aatQTaskFinalEvent[Weapon_eGetParentParametersQTaskEvent][ptWeaponQTask->ptParent->eQTaskType].pfHandler )
    {
      for ( i = 0; i < 2; ++i )
      {
        if ( *((_DWORD *)&ptWeaponQTask[2].ptParent + 7 * i) )
        {
          v3 = (struct WeaponTypeItem_s *)ptWeaponQTask[1].ptPrev;
          iActiveFireMode = v3->iActiveFireMode;
          Weapon_GetFireTypeAmmoInfoFromWeaponTypeItem((struct Weapon_s *)ptWeaponQTask, v3, i, &igi2_frame.tAmmoContext);
          if ( i
            || (v5 = v3->ptWeaponType->anRoundsInSuccession[iActiveFireMode], v5 <= 1)
            || (ptHead = ptWeaponQTask[3].tQTaskChildren.ptHead, (int)ptHead <= 0)
            || (int)ptHead >= v5
            || v5 >= igi2_frame.tAmmoContext.nRoundsPerClip )
          {
            *((_DWORD *)&ptWeaponQTask[17].ptNext + i) = 0;
            v7 = igi2_frame.ptActiveWeaponTypeItem->iActiveFireMode;
            igi2_frame.eID = igi2_frame.ptActiveWeaponType->eID;
            igi2_frame.v18 = v7;
            igi2_frame.v17 = i;
            nTicks = Flow_ptFlow->nTicks;
            igi2_frame.v14 = &ptWeaponQTask->ptNext + 7 * i;
            v9 = igi2_frame.v14[29];
            if ( nTicks - (int)v9 >= 0 )
              igi2_frame.v23 = nTicks - (_DWORD)v9;
            else
              igi2_frame.v23 = (int)v9 - nTicks;
            ptParent = ptWeaponQTask->ptParent;
            igi2_frame.tParentContext.isAddInaccuracy = true;
            pfHandler = (void (__cdecl *)(struct QTask_s *, struct WeaponGetParentParameterContext_s *))QTask_aatQTaskFinalEvent[Weapon_eGetParentParametersQTaskEvent][ptParent->eQTaskType].pfHandler;
            if ( pfHandler )
              pfHandler(ptParent, &igi2_frame.tParentContext);
            qmemcpy(igi2_frame.v19, &igi2_frame.tParentContext, sizeof(igi2_frame.v19));
            Real32x9_GetAngles(&igi2_frame.tParentContext.tOrientation, &igi2_frame.pvAlpha, &igi2_frame.pvBeta, &igi2_frame.pvGamma);
            Weapon_SendWeaponEvent(ptWeaponQTask, 0x57535253u, igi2_frame.ptNetManagerGameMessage, 72);
            igi2_frame.v14[27] = nullptr;
            *((_DWORD *)&ptWeaponQTask[2].ptParent + 7 * i) = 0;
            igi2_frame.v14[32] = nullptr;
          }
          else
          {
            ptWeaponQTask[17].ptNext = (struct QTask_s *)1;
            ptWeaponQTask[2].ptParent = nullptr;
          }
        }
      }
    }
  }
}

// source: j/0/weapons/weapon.c:2736  [anchor-hash]
struct QTask_s *__cdecl Weapon_GetGunShotQTask(struct QTask_s *ptWeaponQTask)
{
  struct QTask_s *ptNext; // eax

  ptNext = ptWeaponQTask[5].ptNext;
  if ( ptNext )
    return ptNext->tQTaskChildren.ptHead;
  else
    return nullptr;
}

// source: j/0/weapons/weapon.c:2759  [size]
struct WeaponTypeItem_s *__cdecl Weapon_GetCurrentWeaponTypeItem(
        struct QTask_s *ptWeaponQTask)
{
  return (struct WeaponTypeItem_s *)ptWeaponQTask[1].ptPrev;
}

// source: j/0/weapons/weapon.c:2777  [anchor-hash]
struct WeaponType_s *__cdecl Weapon_GetCurrentWeaponType(struct QTask_s *ptWeaponQTask)
{
  struct WeaponType_s *result; // eax

  result = (struct WeaponType_s *)ptWeaponQTask[1].ptPrev;
  if ( result )
    return (struct WeaponType_s *)result->tQTask.tQTaskChildren.ptTail;
  return result;
}

// source: j/0/weapons/weapon.c:2800  [anchor-callee]
struct WeaponTypeItem_s *__cdecl Weapon_GetWeaponTypeItemFromWeaponType(
        struct QTask_s *ptWeaponQTask,
        char *pzWeaponType)
{
  struct WeaponTypeItem_s *ptTail; // ebp
  struct WeaponTypeItem_s *ptNext; // edi

  ptTail = (struct WeaponTypeItem_s *)ptWeaponQTask[4].tQTaskChildren.ptTail;
  ptNext = (struct WeaponTypeItem_s *)ptTail->tNode.ptNext;
  if ( !ptTail->tNode.ptNext )
    return nullptr;
  while ( strcmp(ptTail->ptWeaponType->zWeaponScriptID, pzWeaponType) )
  {
    ptTail = ptNext;
    ptNext = (struct WeaponTypeItem_s *)ptNext->tNode.ptNext;
    if ( !ptNext )
      return nullptr;
  }
  return ptTail;
}

// source: j/0/weapons/weapon.c:2836  [anchor-strings]
void __cdecl Weapon_ListCarriedWeapons(struct QTask_s *ptWeaponQTask)
{
  struct QTask_s *ptTail; // eax
  struct QTask_s *i; // ebx
  struct QTask_s *v3; // esi
  struct WeaponTypeItem_s *WeaponTypeItemFromWeaponType; // eax
  int v5; // esi
  struct __anon_1b7c *p_tOut; // edi
  struct WeaponTypeGetAmmoInfoContext_s tAmmoInfoContext; // [esp+8h] [ebp-28h] BYREF

  DebugConsole_printf("Weapon_ListCarriedWeapons\n");
  ptTail = ptWeaponQTask[4].tQTaskChildren.ptTail;
  for ( i = ptTail->ptNext; i; i = i->ptNext )
  {
    v3 = ptTail->tQTaskChildren.ptTail;
    WeaponTypeItemFromWeaponType = Weapon_GetWeaponTypeItemFromWeaponType(ptWeaponQTask, (char *)&v3[2].ptPrev);
    if ( WeaponTypeItemFromWeaponType && WeaponTypeItemFromWeaponType->isActive )
    {
      DebugConsole_printf("Carrying: %s\n", (char *)&v3[2].ptPrev);
      memset(&tAmmoInfoContext, 0, sizeof(tAmmoInfoContext));
      ((void (__cdecl *)(struct QTask_s *, struct WeaponTypeGetAmmoInfoContext_s *))QTask_aatQTaskFinalEvent[WeaponType_eGetAmmoInfoQTaskEvent][v3->eQTaskType].pfHandler)(
        v3,
        &tAmmoInfoContext);
      v5 = 0;
      p_tOut = &tAmmoInfoContext.atAmmoItem[0].tOut;
      do
      {
        if ( p_tOut->ptAmmoType )
          DebugConsole_printf("---------Ammo: %s\n", (char *)v5);
        ++v5;
        p_tOut = (struct __anon_1b7c *)((char *)p_tOut + 20);
      }
      while ( v5 < 2 );
    }
    ptTail = i;
  }
}

// source: j/0/weapons/weapon.c:2895  [anchor-callee]
struct AmmoTypeItem_s *__cdecl Weapon_GetAmmoTypeItemFromAmmoType(
        struct QTask_s *ptWeaponQTask,
        char *pzAmmoType)
{
  struct AmmoTypeItem_s *ptTail; // ebp
  struct AmmoTypeItem_s *ptNext; // edi

  ptTail = (struct AmmoTypeItem_s *)ptWeaponQTask[4].tQTaskRefList.ptTail;
  ptNext = (struct AmmoTypeItem_s *)ptTail->tNode.ptNext;
  if ( !ptTail->tNode.ptNext )
    return nullptr;
  while ( strcmp(ptTail->ptAmmoType->zAmmoTypeScriptID, pzAmmoType) )
  {
    ptTail = ptNext;
    ptNext = (struct AmmoTypeItem_s *)ptNext->tNode.ptNext;
    if ( !ptNext )
      return nullptr;
  }
  return ptTail;
}

// source: j/0/weapons/weapon.c:2929  [anchor-callee]
enum bool __cdecl Weapon_IsWeaponSelectable(struct QTask_s *ptWeaponQTask, char *pzWeaponType)
{
  struct WeaponTypeItem_s *WeaponTypeItemFromWeaponType; // eax
  struct WeaponTypeItem_s *v3; // edi
  struct WeaponType_s *ptWeaponType; // esi
  int *anFireTypeAmmoCount; // ebp
  int v7; // ebx
  struct __anon_1b7c *p_tOut; // esi
  struct WeaponTypeFireType_s *i; // edi
  struct AmmoTypeItem_s *AmmoTypeItemFromAmmoType; // eax
  struct WeaponTypeGetAmmoInfoContext_s tGetAmmoInfoContext; // [esp+Ch] [ebp-28h] BYREF

  WeaponTypeItemFromWeaponType = Weapon_GetWeaponTypeItemFromWeaponType(ptWeaponQTask, pzWeaponType);
  v3 = WeaponTypeItemFromWeaponType;
  if ( !WeaponTypeItemFromWeaponType || !WeaponTypeItemFromWeaponType->isActive )
    return false;
  ptWeaponType = WeaponTypeItemFromWeaponType->ptWeaponType;
  if ( !ptWeaponType->isSelectableWhenEmpty )
  {
    WeaponType_GetAmmoInfo(ptWeaponType, &tGetAmmoInfoContext);
    anFireTypeAmmoCount = v3->anFireTypeAmmoCount;
    v7 = 0;
    p_tOut = &tGetAmmoInfoContext.atAmmoItem[0].tOut;
    for ( i = v3->ptWeaponType->atFireTypes; ; ++i )
    {
      if ( i->eQTaskType != 512 )
      {
        if ( !p_tOut->nRoundsToFire )
          break;
        if ( *anFireTypeAmmoCount )
          break;
        if ( p_tOut->ptAmmoType )
        {
          AmmoTypeItemFromAmmoType = Weapon_GetAmmoTypeItemFromAmmoType(
                                       ptWeaponQTask,
                                       p_tOut->ptAmmoType->zAmmoTypeScriptID);
          if ( AmmoTypeItemFromAmmoType )
          {
            if ( AmmoTypeItemFromAmmoType->nAmmoCount )
              break;
          }
        }
      }
      ++v7;
      ++anFireTypeAmmoCount;
      p_tOut = (struct __anon_1b7c *)((char *)p_tOut + 20);
      if ( v7 >= 2 )
        return false;
    }
  }
  return true;
}

// source: j/0/weapons/weapon.c:3009  [size]
struct QTask_s *__cdecl Weapon_GetFireTypeAmmoInfo(
        struct QTask_s *ptWeaponQTask,
        int nFireType,
        struct WeaponGetFireTypeAmmoContext_s *ptAmmoContext)
{
  struct QTask_s *result; // eax

  Weapon_GetFireTypeAmmoInfoFromWeaponTypeItem(
    (struct Weapon_s *)ptWeaponQTask,
    (struct WeaponTypeItem_s *)ptWeaponQTask[1].ptPrev,
    nFireType,
    ptAmmoContext);
  return result;
}

// source: j/0/weapons/weapon.c:3028  [anchor-callee]
void __cdecl Weapon_GetFireTypeAmmoInfoFromWeaponTypeItem(
        struct Weapon_s *ptWeapon,
        struct WeaponTypeItem_s *ptWeaponTypeItem,
        int nFireType,
        struct WeaponGetFireTypeAmmoContext_s *ptAmmoContext)
{
  struct WeaponType_s *ptWeaponType; // edx
  struct AmmoType_s *ptAmmoType; // eax
  struct AmmoTypeItem_s *AmmoTypeItemFromAmmoType; // eax
  int nRoundsPerClip; // ecx
  struct WeaponTypeGetAmmoInfoContext_s tGetAmmoInfoContext; // [esp+4h] [ebp-28h] BYREF

  if ( ptWeaponTypeItem )
  {
    ptWeaponType = ptWeaponTypeItem->ptWeaponType;
    memset(&tGetAmmoInfoContext, 0, sizeof(tGetAmmoInfoContext));
    ((void (__cdecl *)(struct WeaponType_s *, struct WeaponTypeGetAmmoInfoContext_s *))QTask_aatQTaskFinalEvent[WeaponType_eGetAmmoInfoQTaskEvent][ptWeaponType->tQTask.eQTaskType].pfHandler)(
      ptWeaponType,
      &tGetAmmoInfoContext);
    ptAmmoType = tGetAmmoInfoContext.atAmmoItem[nFireType].tOut.ptAmmoType;
    ptAmmoContext->ptAmmoType = ptAmmoType;
    ptAmmoContext->nAmmoInWeapon = ptWeaponTypeItem->anFireTypeAmmoCount[nFireType];
    if ( ptAmmoType
      && (AmmoTypeItemFromAmmoType = Weapon_GetAmmoTypeItemFromAmmoType(
                                       &ptWeapon->tQTask,
                                       ptAmmoType->zAmmoTypeScriptID)) != nullptr )
    {
      ptAmmoContext->nAmmoAvailable = AmmoTypeItemFromAmmoType->nAmmoCount;
    }
    else
    {
      ptAmmoContext->nAmmoAvailable = 0;
    }
    nRoundsPerClip = tGetAmmoInfoContext.atAmmoItem[nFireType].tOut.nRoundsPerClip;
    ptAmmoContext->nBulletsPerRound = tGetAmmoInfoContext.atAmmoItem[nFireType].tOut.nBulletsPerRound;
    ptAmmoContext->nRoundsPerClip = nRoundsPerClip;
  }
}

// source: j/0/weapons/weapon.c:3075  [anchor-strings]
enum WeaponCategory_e __cdecl Weapon_CategoryDescription(
        struct Weapon_s *ptWeapon,
        enum WeaponCategory_e eWeaponCategory,
        char *zText,
        unsigned int STR_MAX)
{
  #pragma pack(push, 1)
  union
  {
    struct { char *p_ptMiddle; };
    struct { char igi2_o1[4]; char *v12; };
    struct { char igi2_o2[24]; struct WeaponGetFireTypeAmmoContext_s nFireType; };
    struct { char igi2_o3[44]; struct WeaponGetFireTypeAmmoContext_s ptAmmoContext; };
    struct { char igi2_o4[64]; char zResourceName[256]; };
    char igi2_extent[320];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct WeaponType_s *NextEnabledWeaponTypeFromCategory; // ebx
  enum WeaponCategory_e result; // eax
  struct WeaponTypeItem_s *WeaponTypeItemFromCategory; // esi
  char *LocalizedStringForLanguage; // edi
  struct AmmoType_s *ptAmmoType; // eax
  int nAmmoAvailable; // eax

  NextEnabledWeaponTypeFromCategory = Weapon_GetNextEnabledWeaponTypeFromCategory(
                                        &ptWeapon->tQTask,
                                        eWeaponCategory,
                                        nullptr);
  if ( !NextEnabledWeaponTypeFromCategory )
    return _snprintf(zText, STR_MAX, " - ");
  WeaponTypeItemFromCategory = Weapon_GetWeaponTypeItemFromCategory(ptWeapon, eWeaponCategory);
  _snprintf(igi2_frame.zResourceName, 0xFFu, "weapons/strings/%s", NextEnabledWeaponTypeFromCategory->zName);
  LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                 igi2_frame.zResourceName,
                                 Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                 true);
  ptAmmoType = nullptr;
  igi2_frame.nFireType.ptAmmoType = nullptr;
  igi2_frame.ptAmmoContext.ptAmmoType = nullptr;
  if ( WeaponTypeItemFromCategory )
  {
    Weapon_GetFireTypeAmmoInfoFromWeaponTypeItem(ptWeapon, WeaponTypeItemFromCategory, 0, &igi2_frame.nFireType);
    Weapon_GetFireTypeAmmoInfoFromWeaponTypeItem(ptWeapon, WeaponTypeItemFromCategory, 1, &igi2_frame.ptAmmoContext);
    ptAmmoType = igi2_frame.nFireType.ptAmmoType;
  }
  switch ( NextEnabledWeaponTypeFromCategory->eWeaponCategory )
  {
    case WEAPONCATEGORY_NONE:
      return (enum WeaponCategory_e)strncpy(zText, "?NO CATEGORY", STR_MAX);
    case WEAPONCATEGORY_KNIFE:
      igi2_frame.v12 = LocalizedStringForLanguage;
      igi2_frame.p_ptMiddle = (char *)&stru_6A4CDC.tDebugConsoleLineList.ptMiddle;
      goto LABEL_19;
    case WEAPONCATEGORY_SIDEARM:
    case WEAPONCATEGORY_PRIMARY:
      if ( !ptAmmoType )
        goto LABEL_20;
      if ( igi2_frame.ptAmmoContext.ptAmmoType )
        return _snprintf(
                 zText,
                 STR_MAX,
                 "%s (%d/%d) (%d)",
                 LocalizedStringForLanguage,
                 igi2_frame.nFireType.nAmmoInWeapon,
                 igi2_frame.nFireType.nAmmoAvailable,
                 igi2_frame.ptAmmoContext.nAmmoAvailable);
      else
        return _snprintf(
                 zText,
                 STR_MAX,
                 "%s (%d/%d)",
                 LocalizedStringForLanguage,
                 igi2_frame.nFireType.nAmmoInWeapon,
                 igi2_frame.nFireType.nAmmoAvailable);
    case WEAPONCATEGORY_GRENADE:
    case WEAPONCATEGORY_PROXIMITYMINE:
    case WEAPONCATEGORY_FLASHBANG:
    case WEAPONCATEGORY_SMOKEGRENADE:
      if ( !ptAmmoType )
        goto LABEL_20;
      nAmmoAvailable = igi2_frame.nFireType.nAmmoAvailable;
      if ( igi2_frame.nFireType.nAmmoAvailable > 0 )
        goto LABEL_17;
      igi2_frame.v12 = " - ";
      igi2_frame.p_ptMiddle = (char *)&stru_6A4CDC.tDebugConsoleLineList.ptMiddle;
      goto LABEL_19;
    case WEAPONCATEGORY_MEDIPACK:
      if ( ptAmmoType )
      {
        nAmmoAvailable = igi2_frame.nFireType.nAmmoAvailable;
        if ( igi2_frame.nFireType.nAmmoAvailable <= 0 )
        {
          igi2_frame.v12 = LocalizedStringForLanguage;
          igi2_frame.p_ptMiddle = "%s -";
LABEL_19:
          result = _snprintf(zText, STR_MAX, igi2_frame.p_ptMiddle, igi2_frame.v12);
        }
        else
        {
LABEL_17:
          result = _snprintf(zText, STR_MAX, "%s (%d)", LocalizedStringForLanguage, nAmmoAvailable);
        }
      }
      else
      {
LABEL_20:
        result = (enum WeaponCategory_e)strncpy(zText, "?NO AMMO TYPE", STR_MAX);
      }
      break;
    case WEAPONCATEGORY_BINOCULARS:
      return _snprintf(
               zText,
               STR_MAX,
               (char *const)&stru_6A4CDC.tDebugConsoleLineList.ptMiddle,
               LocalizedStringForLanguage);
    default:
      return (enum WeaponCategory_e)strncpy(zText, "?UNKNOWN CATEGORY", STR_MAX);
  }
  return result;
}

// source: j/0/weapons/weapon.c:3227  [anchor-callee]
enum bool __cdecl Weapon_IsInInventoryAndFull(
        struct Weapon_s *ptWeapon,
        struct WeaponType_s *ptWeaponType,
        enum bool isAmmoFullForGun,
        int ltcg_arg3)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct WeaponGetFireTypeAmmoContext_s nFireType; };
    struct { char igi2_o1[20]; struct WeaponGetFireTypeAmmoContext_s ptAmmoContext; };
    char igi2_extent[40];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  enum WeaponCategory_e eWeaponCategory; // edi
  struct WeaponType_s *NextEnabledWeaponTypeFromCategory; // ebx
  enum bool v6; // esi
  enum bool result; // eax
  struct WeaponTypeItem_s *WeaponTypeItemFromCategory; // edi
  struct AmmoType_s *ptAmmoType; // eax
  struct AmmoTypeItem_s *AmmoTypeItemFromAmmoType; // edi
  struct AmmoTypeItem_s *v11; // eax
  int nAmmoAvailable; // edi

  eWeaponCategory = ptWeaponType->eWeaponCategory;
  NextEnabledWeaponTypeFromCategory = Weapon_GetNextEnabledWeaponTypeFromCategory(
                                        &ptWeapon->tQTask,
                                        eWeaponCategory,
                                        nullptr);
  v6 = false;
  if ( !NextEnabledWeaponTypeFromCategory )
    return false;
  WeaponTypeItemFromCategory = Weapon_GetWeaponTypeItemFromCategory(ptWeapon, eWeaponCategory);
  ptAmmoType = nullptr;
  igi2_frame.nFireType.ptAmmoType = nullptr;
  igi2_frame.ptAmmoContext.ptAmmoType = nullptr;
  if ( WeaponTypeItemFromCategory )
  {
    Weapon_GetFireTypeAmmoInfoFromWeaponTypeItem(ptWeapon, WeaponTypeItemFromCategory, 0, &igi2_frame.nFireType);
    Weapon_GetFireTypeAmmoInfoFromWeaponTypeItem(ptWeapon, WeaponTypeItemFromCategory, 1, &igi2_frame.ptAmmoContext);
    ptAmmoType = igi2_frame.nFireType.ptAmmoType;
  }
  switch ( NextEnabledWeaponTypeFromCategory->eWeaponCategory )
  {
    case WEAPONCATEGORY_SIDEARM:
    case WEAPONCATEGORY_PRIMARY:
      if ( isAmmoFullForGun == false )
        return ptWeaponType->eID == NextEnabledWeaponTypeFromCategory->eID;
      if ( !ptAmmoType )
        goto LABEL_30;
      if ( !igi2_frame.ptAmmoContext.ptAmmoType )
      {
        nAmmoAvailable = igi2_frame.nFireType.nAmmoAvailable;
        if ( igi2_frame.nFireType.nAmmoAvailable < 0 )
          goto LABEL_30;
        goto LABEL_28;
      }
      AmmoTypeItemFromAmmoType = Weapon_GetAmmoTypeItemFromAmmoType(&ptWeapon->tQTask, ptAmmoType->zAmmoTypeScriptID);
      v11 = Weapon_GetAmmoTypeItemFromAmmoType(&ptWeapon->tQTask, igi2_frame.ptAmmoContext.ptAmmoType->zAmmoTypeScriptID);
      if ( ltcg_arg3 )
      {
        if ( ltcg_arg3 == 1 )
        {
          if ( igi2_frame.ptAmmoContext.nAmmoAvailable < 0 )
            goto LABEL_30;
          return igi2_frame.ptAmmoContext.nAmmoAvailable >= v11->nAmmoLimit;
        }
        else
        {
          if ( igi2_frame.nFireType.nAmmoAvailable < 0
            || igi2_frame.ptAmmoContext.nAmmoAvailable < 0
            || igi2_frame.nFireType.nAmmoAvailable < AmmoTypeItemFromAmmoType->nAmmoLimit
            || igi2_frame.ptAmmoContext.nAmmoAvailable < v11->nAmmoLimit )
          {
            goto LABEL_30;
          }
          return true;
        }
      }
      else
      {
        if ( igi2_frame.nFireType.nAmmoAvailable < 0 )
          goto LABEL_30;
        return igi2_frame.nFireType.nAmmoAvailable >= AmmoTypeItemFromAmmoType->nAmmoLimit;
      }
    case WEAPONCATEGORY_GRENADE:
    case WEAPONCATEGORY_PROXIMITYMINE:
    case WEAPONCATEGORY_FLASHBANG:
    case WEAPONCATEGORY_SMOKEGRENADE:
      if ( !ptAmmoType )
        goto LABEL_30;
      nAmmoAvailable = igi2_frame.nFireType.nAmmoAvailable;
      if ( igi2_frame.nFireType.nAmmoAvailable <= 0 )
        goto LABEL_30;
      goto LABEL_28;
    case WEAPONCATEGORY_MEDIPACK:
      if ( !ptAmmoType )
        goto LABEL_30;
      nAmmoAvailable = igi2_frame.nFireType.nAmmoAvailable;
      if ( igi2_frame.nFireType.nAmmoAvailable <= 0 )
        goto LABEL_30;
LABEL_28:
      result = nAmmoAvailable >= Weapon_GetAmmoTypeItemFromAmmoType(&ptWeapon->tQTask, ptAmmoType->zAmmoTypeScriptID)->nAmmoLimit;
      break;
    case WEAPONCATEGORY_BINOCULARS:
      v6 = ptWeaponType->eID == NextEnabledWeaponTypeFromCategory->eID;
      goto LABEL_30;
    default:
LABEL_30:
      result = v6;
      break;
  }
  return result;
}

// source: j/0/weapons/weapon.c:3373  [anchor-callee]
char *__cdecl Weapon_AddAmmoForWeapon(
        struct QTask_s *ptWeaponQTask,
        char *pzWeaponType,
        int *anAmmoCount)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct WeaponTypeItem_s *ptItem; };
    struct { char igi2_o1[4]; struct WeaponTypeGetAmmoInfoContext_s tGetAmmoInfoContext; };
    char igi2_extent[44];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char *result; // eax
  char *v4; // ebp
  int v5; // edx
  int v7; // edi
  int *v8; // ebp
  int v9; // esi
  int nRoundsPerClip; // eax
  int v11; // ecx
  int v12; // edx
  int v13; // ecx

  result = (char *)Weapon_GetWeaponTypeItemFromWeaponType(ptWeaponQTask, pzWeaponType);
  v4 = result;
  igi2_frame.ptItem = (struct WeaponTypeItem_s *)result;
  if ( result )
  {
    v5 = *((_DWORD *)result + 4);
    memset(&igi2_frame.tGetAmmoInfoContext, 0, sizeof(igi2_frame.tGetAmmoInfoContext));
    ((void (__cdecl *)(int, struct WeaponTypeGetAmmoInfoContext_s *))QTask_aatQTaskFinalEvent[WeaponType_eGetAmmoInfoQTaskEvent][*(unsigned __int16 *)(v5 + 36)].pfHandler)(
      v5,
      &igi2_frame.tGetAmmoInfoContext);
    v7 = 0;
    v8 = (int *)(v4 + 8);
    do
    {
      v9 = *anAmmoCount;
      if ( !*v8 && !igi2_frame.ptItem->ptWeaponType->atFireTypes[v7].isForceReload )
      {
        nRoundsPerClip = igi2_frame.tGetAmmoInfoContext.atAmmoItem[v7].tOut.nRoundsPerClip;
        if ( v9 <= nRoundsPerClip )
        {
          *v8 = v9;
          v9 = 0;
        }
        else
        {
          *v8 = nRoundsPerClip;
          v9 -= nRoundsPerClip;
        }
      }
      result = (char *)igi2_frame.tGetAmmoInfoContext.atAmmoItem[v7].tOut.ptAmmoType;
      if ( result )
      {
        if ( v9 > 0 )
        {
          result = (char *)Weapon_GetAmmoTypeItemFromAmmoType(ptWeaponQTask, result + 40);
          if ( result )
          {
            v11 = v9 + *((_DWORD *)result + 2);
            *((_DWORD *)result + 2) = v11;
            v12 = v11;
            v13 = *((_DWORD *)result + 3);
            if ( v13 != -1 )
            {
              if ( v12 >= 0 )
              {
                if ( v12 > v13 )
                  *((_DWORD *)result + 2) = v13;
              }
              else
              {
                *((_DWORD *)result + 2) = 0;
              }
            }
          }
        }
      }
      ++v7;
      ++anAmmoCount;
      ++v8;
    }
    while ( v7 < 2 );
  }
  return result;
}

// source: j/0/weapons/weapon.c:3434  [anchor-mhash]
char *__cdecl Weapon_SetAmmoForWeapon(
        struct QTask_s *ptWeaponQTask,
        char *pzWeaponType,
        int nAmmoInClip,
        int *anAmmoCount)
{
  char *result; // eax
  char *v6; // esi
  int v7; // edx
  int nRoundsPerClip; // eax
  int v9; // esi
  struct __anon_1b7c *p_tOut; // edi
  int v11; // ecx
  int v12; // edx
  int v13; // ecx
  struct WeaponTypeGetAmmoInfoContext_s tGetAmmoInfoContext; // [esp+Ch] [ebp-28h] BYREF

  result = (char *)Weapon_GetWeaponTypeItemFromWeaponType(ptWeaponQTask, pzWeaponType);
  v6 = result;
  if ( result )
  {
    v7 = *((_DWORD *)result + 4);
    memset(&tGetAmmoInfoContext, 0, sizeof(tGetAmmoInfoContext));
    ((void (__cdecl *)(int, struct WeaponTypeGetAmmoInfoContext_s *))QTask_aatQTaskFinalEvent[WeaponType_eGetAmmoInfoQTaskEvent][*(unsigned __int16 *)(v7 + 36)].pfHandler)(
      v7,
      &tGetAmmoInfoContext);
    nRoundsPerClip = tGetAmmoInfoContext.atAmmoItem[0].tOut.nRoundsPerClip;
    if ( nAmmoInClip < tGetAmmoInfoContext.atAmmoItem[0].tOut.nRoundsPerClip )
      nRoundsPerClip = nAmmoInClip;
    *((_DWORD *)v6 + 2) = nRoundsPerClip;
    *((_DWORD *)v6 + 3) = 1;
    v9 = 0;
    p_tOut = &tGetAmmoInfoContext.atAmmoItem[0].tOut;
    do
    {
      result = (char *)p_tOut->ptAmmoType;
      if ( p_tOut->ptAmmoType )
      {
        result = (char *)Weapon_GetAmmoTypeItemFromAmmoType(ptWeaponQTask, result + 40);
        if ( result )
        {
          v11 = anAmmoCount[v9] + *((_DWORD *)result + 2);
          *((_DWORD *)result + 2) = v11;
          v12 = v11;
          v13 = *((_DWORD *)result + 3);
          if ( v13 != -1 )
          {
            if ( v12 >= 0 )
            {
              if ( v12 > v13 )
                *((_DWORD *)result + 2) = v13;
            }
            else
            {
              *((_DWORD *)result + 2) = 0;
            }
          }
        }
      }
      ++v9;
      p_tOut = (struct __anon_1b7c *)((char *)p_tOut + 20);
    }
    while ( v9 < 2 );
  }
  return result;
}

// source: j/0/weapons/weapon.c:3484  [anchor-callee]
enum bool __cdecl Weapon_EnableWeaponType(
        struct QTask_s *ptWeaponQTask,
        char *pzWeaponType,
        enum bool isAddAmmo)
{
  #pragma pack(push, 1)
  union
  {
    struct { int anAmmoCount[2]; };
    struct { char igi2_o1[8]; struct WeaponTypeGetAmmoInfoContext_s tGetAmmoContext; };
    char igi2_extent[48];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v4; // esi
  struct WeaponTypeItem_s *WeaponTypeItemFromWeaponType; // eax
  struct QTask_s *v6; // ebx
  char isActive; // dl
  enum bool v8; // edi
  struct WeaponType_s *ptWeaponType; // edx
  struct __anon_1b7c *p_tOut; // edi
  struct QTask_s *ptParent; // eax
  struct QTask_s *ptTail; // ecx
  struct QTask_s *ptNext; // eax
  struct QTask_s *v14; // edx
  struct QTask_s *ptWeaponQTaska = *(struct QTask_s * *)&ptWeaponQTask; // [esp+44h] [ebp+4h] ARGSLOT

  v4 = 0;
  WeaponTypeItemFromWeaponType = Weapon_GetWeaponTypeItemFromWeaponType(ptWeaponQTask, pzWeaponType);
  v6 = (struct QTask_s *)WeaponTypeItemFromWeaponType;
  if ( !WeaponTypeItemFromWeaponType )
    return false;
  isActive = WeaponTypeItemFromWeaponType->isActive;
  v8 = isActive == 0;
  ptWeaponQTaska = (struct QTask_s *)v8;
  WeaponTypeItemFromWeaponType->isActive = 1;
  if ( !isActive )
  {
    WeaponTypeItemFromWeaponType->anFireTypeAmmoCount[0] = WeaponTypeItemFromWeaponType->ptWeaponType->atFireTypes[0].isForceReload != 0;
    WeaponTypeItemFromWeaponType->anFireTypeAmmoCount[1] = WeaponTypeItemFromWeaponType->ptWeaponType->atFireTypes[1].isForceReload != 0;
    if ( isAddAmmo )
    {
      ptWeaponType = WeaponTypeItemFromWeaponType->ptWeaponType;
      if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
      {
        memset(&igi2_frame.tGetAmmoContext, 0, sizeof(igi2_frame.tGetAmmoContext));
        ((void (__cdecl *)(struct WeaponType_s *, struct WeaponTypeGetAmmoInfoContext_s *))QTask_aatQTaskFinalEvent[WeaponType_eGetAmmoInfoQTaskEvent][ptWeaponType->tQTask.eQTaskType].pfHandler)(
          ptWeaponType,
          &igi2_frame.tGetAmmoContext);
        p_tOut = &igi2_frame.tGetAmmoContext.atAmmoItem[0].tOut;
        do
        {
          if ( p_tOut->ptAmmoType )
            igi2_frame.anAmmoCount[v4] = p_tOut->nRoundsPerClip
                            + Weapon_GetAmmoTypeItemFromAmmoType(ptWeaponQTask, p_tOut->ptAmmoType->zAmmoTypeScriptID)->nAmmoLimit;
          else
            igi2_frame.anAmmoCount[v4] = 10000;
          ++v4;
          p_tOut = (struct __anon_1b7c *)((char *)p_tOut + 20);
        }
        while ( v4 < 2 );
        v8 = (enum bool)ptWeaponQTaska;
      }
      else
      {
        WeaponType_CalcGunPickupAmmo(igi2_frame.anAmmoCount, ptWeaponType, 1.0);
      }
      Weapon_AddAmmoForWeapon(ptWeaponQTask, pzWeaponType, igi2_frame.anAmmoCount);
    }
  }
  if ( !ptWeaponQTask[1].ptPrev )
  {
    ptParent = v6->tQTaskChildren.ptTail[16].ptParent;
    if ( ptParent != (struct QTask_s *)12 && ptParent != (struct QTask_s *)11 )
    {
      ptTail = ptWeaponQTask[4].tQTaskChildren.ptTail;
      ptWeaponQTask[1].ptPrev = v6;
      ptWeaponQTask[1].ptNext = v6;
      ptNext = ptTail->ptNext;
      v14 = nullptr;
      if ( ptTail->ptNext )
      {
        while ( v6 != ptTail )
        {
          ptTail = ptNext;
          ptNext = ptNext->ptNext;
          v14 = (struct QTask_s *)((char *)v14 + 1);
          if ( !ptNext )
            goto LABEL_19;
        }
      }
      else
      {
LABEL_19:
        v14 = nullptr;
      }
      ptWeaponQTask[1].tQTaskChildren.ptHead = v14;
    }
  }
  return v8;
}

// source: j/0/weapons/weapon.c:3568  [anchor-callee]
char *__cdecl Weapon_DisableWeaponType(
        struct QTask_s *ptWeaponQTask,
        char *pzWeaponType,
        enum bool isRemoveAmmoInPocket)
{
  int v4; // eax
  struct WeaponType_s *WeaponTypeFromID; // ebp
  char *result; // eax
  char *v7; // esi
  struct __anon_1b7c *p_tOut; // edi
  _DWORD *v9; // esi
  int v10; // ebp
  bool v11; // zf
  struct WeaponTypeGetAmmoInfoContext_s tGetAmmoContext; // [esp+Ch] [ebp-28h] BYREF

  v4 = Script_ParseLineInt32(pzWeaponType);
  WeaponTypeFromID = WeaponType_GetWeaponTypeFromID(v4);
  result = (char *)Weapon_GetWeaponTypeItemFromWeaponType(ptWeaponQTask, pzWeaponType);
  v7 = result;
  if ( result && WeaponTypeFromID )
  {
    memset(&tGetAmmoContext, 0, sizeof(tGetAmmoContext));
    ((void (__cdecl *)(struct WeaponType_s *, struct WeaponTypeGetAmmoInfoContext_s *))QTask_aatQTaskFinalEvent[WeaponType_eGetAmmoInfoQTaskEvent][WeaponTypeFromID->tQTask.eQTaskType].pfHandler)(
      WeaponTypeFromID,
      &tGetAmmoContext);
    *((_BYTE *)v7 + 28) = 0;
    p_tOut = &tGetAmmoContext.atAmmoItem[0].tOut;
    v9 = v7 + 8;
    v10 = 2;
    do
    {
      result = (char *)p_tOut->ptAmmoType;
      v11 = p_tOut->ptAmmoType == nullptr;
      *v9 = 0;
      if ( !v11 )
      {
        if ( isRemoveAmmoInPocket )
        {
          result = (char *)Weapon_GetAmmoTypeItemFromAmmoType(ptWeaponQTask, result + 40);
          *((_DWORD *)result + 2) = 0;
        }
      }
      ++v9;
      p_tOut = (struct __anon_1b7c *)((char *)p_tOut + 20);
      --v10;
    }
    while ( v10 );
  }
  return result;
}

// source: j/0/weapons/weapon.c:3619  [anchor-caller]
enum bool __cdecl Weapon_IsWeaponTypeEnabled(
        struct QTask_s *ptWeaponQTask,
        char *pzWeaponType)
{
  struct WeaponTypeItem_s *WeaponTypeItemFromWeaponType; // eax

  WeaponTypeItemFromWeaponType = Weapon_GetWeaponTypeItemFromWeaponType(ptWeaponQTask, pzWeaponType);
  if ( WeaponTypeItemFromWeaponType )
    return WeaponTypeItemFromWeaponType->isActive;
  else
    return false;
}

// source: j/0/weapons/weapon.c:3645  [size]
void __cdecl Weapon_SetWeaponHitProbability(
        struct QTask_s *ptWeaponQTask,
        float vHitProbability)
{
  *(float *)&ptWeaponQTask[2].tQTaskRefList.ptHead = vHitProbability;
}

// source: j/0/weapons/weapon.c:3664  [size]
float __cdecl Weapon_GetWeaponHitProbability(struct QTask_s *ptWeaponQTask)
{
  return *(float *)&ptWeaponQTask[2].tQTaskRefList.ptHead;
}

// source: j/0/weapons/weapon.c:3684  [anchor-callee]
char *__cdecl Weapon_AddAmmoToAmmoType(
        struct QTask_s *ptWeaponQTask,
        char *pzAmmoType,
        int nAmmoCountToAdd)
{
  char *result; // eax
  int v4; // edx
  int v5; // ecx

  result = (char *)Weapon_GetAmmoTypeItemFromAmmoType(ptWeaponQTask, pzAmmoType);
  if ( result )
  {
    v4 = nAmmoCountToAdd + *((_DWORD *)result + 2);
    v5 = *((_DWORD *)result + 3);
    *((_DWORD *)result + 2) = v4;
    if ( v5 != -1 )
    {
      if ( v4 >= 0 )
      {
        if ( v4 > v5 )
          *((_DWORD *)result + 2) = v5;
      }
      else
      {
        *((_DWORD *)result + 2) = 0;
      }
    }
  }
  return result;
}

// source: j/0/weapons/weapon.c:3715  [anchor-mhash]
char *__cdecl Weapon_LimitAmmoType(
        struct QTask_s *ptWeaponQTask,
        char *pzAmmoType,
        int nLimit)
{
  char *result; // eax
  int v4; // ecx

  result = (char *)Weapon_GetAmmoTypeItemFromAmmoType(ptWeaponQTask, pzAmmoType);
  if ( result )
  {
    *((_DWORD *)result + 3) = nLimit;
    if ( nLimit != -1 )
    {
      v4 = *((_DWORD *)result + 2);
      if ( v4 >= 0 )
      {
        if ( v4 > nLimit )
          *((_DWORD *)result + 2) = nLimit;
      }
      else
      {
        *((_DWORD *)result + 2) = 0;
      }
    }
  }
  return result;
}

// source: j/0/weapons/weapon.c:3744  [anchor-callee]
void __cdecl Weapon_SetOverlayStatus(
        struct QTask_s *ptWeaponQTask,
        enum WeaponOverlayStatus_e eStatus,
        int ltcg_ebx,
        int ltcg_edi)
{
  int v4; // eax
  int v5; // esi
  int v6; // eax

  if ( !ltcg_ebx )
  {
    v4 = *(_DWORD *)(ltcg_edi + 96);
    if ( v4 )
    {
      v5 = *(_DWORD *)(v4 + 8);
      if ( v5 )
      {
        v6 = *(_DWORD *)(v5 + 1336);
        *(_DWORD *)(v6 + 664) = 0;
        *(float *)(v6 + 648) = tan(0.7853981852531433);
        *(float *)(v6 + 660) = tan(0.5235987901687622);
      }
    }
    else
    {
      v5 = 0;
    }
    if ( *(_DWORD *)(*(_DWORD *)(v5 + 1320) + 164) )
    {
      QTask_Delete(*(struct QTask_s **)(*(_DWORD *)(v5 + 1320) + 164));
      *(_DWORD *)(*(_DWORD *)(v5 + 1320) + 164) = 0;
    }
  }
  *(_DWORD *)(ltcg_edi + 160) = ltcg_ebx;
}

// source: j/0/weapons/weapon.c:3766  [size]
enum WeaponOverlayStatus_e __cdecl Weapon_GetOverlayStatus(struct QTask_s *ptWeaponQTask)
{
  return (enum WeaponOverlayStatus_e)ptWeaponQTask[4].ptNext;
}

// source: j/0/weapons/weapon.c:3784  [size]
struct QTask_s *__cdecl Weapon_SetOverlayQTask(
        struct QTask_s *ptWeaponQTask,
        struct QTask_s *ptOverlayQTask)
{
  ptWeaponQTask[4].ptPrev = ptOverlayQTask;
  return ptOverlayQTask;
}

// source: j/0/weapons/weapon.c:3802  [size]
struct QTask_s *__cdecl Weapon_GetOverlayQTask(struct QTask_s *ptWeaponQTask)
{
  return ptWeaponQTask[4].ptPrev;
}

// source: j/0/weapons/weapon.c:3820  [size]
void __cdecl Weapon_SetOverlaySprite(struct QTask_s *ptWeaponQTask, char *pzOverlaySprite)
{
  ;
}

// source: j/0/weapons/weapon.c:3836  [size]
void __cdecl Weapon_RemoveOverlaySprite(struct QTask_s *ptWeaponQTask)
{
  ;
}

// source: j/0/weapons/weapon.c:3852  [anchor-callee]
char *__cdecl Weapon_PlaySound(
        struct QTask_s *ptWeaponQTask,
        int nSlot,
        char *pzSound,
        enum bool isLoop)
{
  int v5; // eax
  struct QTask_s *v6; // eax
  struct QTask_s *ptParent; // edx
  char *result; // eax
  struct QTask_s *v9; // edi
  struct QTask_s *ptTail; // eax
  struct QTask_s *ptHead; // eax

  v5 = *((_DWORD *)&ptWeaponQTask[4].tQTaskChildren.ptHead + nSlot);
  if ( v5 )
  {
    v6 = *(struct QTask_s **)(v5 + 8);
    if ( v6 )
      QTask_Delete(v6);
    QReference_Delete(*((struct QReference_s **)&ptWeaponQTask[4].tQTaskChildren.ptHead + nSlot), &QTask_tQTaskRefPool);
    *((_DWORD *)&ptWeaponQTask[4].tQTaskChildren.ptHead + nSlot) = 0;
  }
  ptParent = ptWeaponQTask->ptParent;
  if ( QTask_IsQTaskTypeDerived(ptParent->eQTaskType, HumanPlayer_eQTaskType) )
    result = (char *)SoundSys_NewSoundFn(ptParent[33].tQTaskChildren.ptTail, pzSound);
  else
    result = (char *)SoundSys_NewSoundFn(ptWeaponQTask, pzSound);
  v9 = (struct QTask_s *)result;
  if ( result )
  {
    ptTail = ptWeaponQTask[2].tQTaskChildren.ptTail;
    if ( ptTail )
    {
      ptHead = ptTail->tQTaskChildren.ptHead;
      if ( ptHead )
        ((void (__cdecl *)(struct QTask_s *, struct QTask_s *))QTask_aatQTaskFinalEvent[SoundSys_eSetSectorQTaskEvent][v9->eQTaskType].pfHandler)(
          v9,
          ptHead[74].tQTaskChildren.ptTail);
    }
    result = (char *)QTask_NewQTaskRef(v9);
    *((_DWORD *)&ptWeaponQTask[4].tQTaskChildren.ptHead + nSlot) = result;
  }
  return result;
}

// source: j/0/weapons/weapon.c:3903  [anchor-mhash]
void __cdecl Weapon_StopSound(struct QTask_s *ptWeaponQTask, int nSlot)
{
  int v2; // eax
  struct QTask_s *v3; // eax

  v2 = *((_DWORD *)&ptWeaponQTask[4].tQTaskChildren.ptHead + nSlot);
  if ( v2 )
  {
    v3 = *(struct QTask_s **)(v2 + 8);
    if ( v3 )
      QTask_Delete(v3);
    QReference_Delete(*((struct QReference_s **)&ptWeaponQTask[4].tQTaskChildren.ptHead + nSlot), &QTask_tQTaskRefPool);
    *((_DWORD *)&ptWeaponQTask[4].tQTaskChildren.ptHead + nSlot) = 0;
  }
}

// source: j/0/weapons/weapon.c:3935  [anchor-callee]
struct WeaponType_s *__cdecl Weapon_GetNextEnabledWeaponTypeFromCategory(
        struct QTask_s *ptWeaponQTask,
        enum WeaponCategory_e eWeaponCategory,
        struct WeaponType_s *ptSkipWeaponType)
{
  struct QTask_s *ptTail; // eax
  struct QTask_s *ptNext; // ecx
  struct QTask_s *v6; // edx

  ptTail = ptWeaponQTask[4].tQTaskChildren.ptTail;
  ptNext = ptTail->ptNext;
  if ( !ptTail->ptNext )
    return nullptr;
  while ( 1 )
  {
    v6 = ptTail->tQTaskChildren.ptTail;
    if ( ptSkipWeaponType != (struct WeaponType_s *)v6 )
      break;
    ptSkipWeaponType = nullptr;
LABEL_7:
    ptTail = ptNext;
    ptNext = ptNext->ptNext;
    if ( !ptNext )
      return nullptr;
  }
  if ( ptSkipWeaponType || !LOBYTE(ptTail->tQTaskRefList.ptTail) || v6[16].ptParent != (struct QTask_s *)eWeaponCategory )
    goto LABEL_7;
  return (struct WeaponType_s *)ptTail->tQTaskChildren.ptTail;
}

// source: j/0/weapons/weapon.c:3977  [anchor-callee]
struct WeaponTypeItem_s *__cdecl Weapon_GetWeaponTypeItemFromCategory(
        struct Weapon_s *ptWeapon,
        enum WeaponCategory_e eWeaponCategory)
{
  struct WeaponTypeItem_s *result; // eax
  struct WeaponTypeItem_s *ptNext; // ecx

  result = (struct WeaponTypeItem_s *)ptWeapon->tPrivate.tActiveWeaponTypes.ptHead;
  ptNext = (struct WeaponTypeItem_s *)result->tNode.ptNext;
  if ( !result->tNode.ptNext )
    return nullptr;
  while ( !result->isActive || result->ptWeaponType->eWeaponCategory != eWeaponCategory )
  {
    result = ptNext;
    ptNext = (struct WeaponTypeItem_s *)ptNext->tNode.ptNext;
    if ( !ptNext )
      return nullptr;
  }
  return result;
}

// source: j/0/weapons/weapon.c:4012  [size]
unsigned __int16 __cdecl Weapon_GetQTaskType()
{
  return Weapon_eQTaskType;
}

// source: j/0/weapons/weapon.c:4026  [anchor-mhash]
void __cdecl Weapon_SubtractAmmoFromActiveWeapon(
        struct QTask_s *ptWeaponQTask,
        int nFireType,
        int nAmmo)
{
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptTail; // edx
  struct AmmoTypeItem_s *AmmoTypeItemFromAmmoType; // eax
  struct WeaponTypeGetAmmoInfoContext_s tGetAmmoContext; // [esp+0h] [ebp-28h] BYREF

  ptPrev = ptWeaponQTask[1].ptPrev;
  if ( ptPrev )
  {
    ptTail = ptPrev->tQTaskChildren.ptTail;
    memset(&tGetAmmoContext, 0, sizeof(tGetAmmoContext));
    ((void (__cdecl *)(struct QTask_s *, struct WeaponTypeGetAmmoInfoContext_s *))QTask_aatQTaskFinalEvent[WeaponType_eGetAmmoInfoQTaskEvent][ptTail->eQTaskType].pfHandler)(
      ptTail,
      &tGetAmmoContext);
    AmmoTypeItemFromAmmoType = Weapon_GetAmmoTypeItemFromAmmoType(
                                 ptWeaponQTask,
                                 tGetAmmoContext.atAmmoItem[nFireType].tOut.ptAmmoType->zAmmoTypeScriptID);
    if ( AmmoTypeItemFromAmmoType )
      AmmoTypeItemFromAmmoType->nAmmoCount -= nAmmo;
  }
}

// source: j/0/weapons/weapon.c:4063  [anchor-mhash]
int __cdecl Weapon_GetAmmoAvailableForActiveWeapon(struct QTask_s *ptWeaponQTask, int nFireType)
{
  struct WeaponGetFireTypeAmmoContext_s tContext; // [esp+0h] [ebp-14h] BYREF

  Weapon_GetFireTypeAmmoInfoFromWeaponTypeItem(
    (struct Weapon_s *)ptWeaponQTask,
    (struct WeaponTypeItem_s *)ptWeaponQTask[1].ptPrev,
    nFireType,
    &tContext);
  return tContext.nAmmoAvailable;
}

// source: j/0/weapons/weapon.c:4080  [anchor-hash]
void __cdecl Weapon_StopAllSound(struct QTask_s *ptQTask)
{
  struct QReference_s **p_tQTaskChildren; // esi
  int v2; // edi
  struct QTask_s **p_ptMiddle; // esi
  int v4; // edi
  struct MemPoolFreeItem_s *v5; // eax

  p_tQTaskChildren = (struct QReference_s **)&ptQTask[4].tQTaskChildren;
  v2 = 2;
  do
  {
    if ( *p_tQTaskChildren )
    {
      if ( (*p_tQTaskChildren)->pxObject )
      {
        QTask_Delete((struct QTask_s *)(*p_tQTaskChildren)->pxObject);
        if ( *p_tQTaskChildren )
        {
          QReference_Delete(*p_tQTaskChildren, &QTask_tQTaskRefPool);
          *p_tQTaskChildren = nullptr;
        }
      }
    }
    ++p_tQTaskChildren;
    --v2;
  }
  while ( v2 );
  p_ptMiddle = &ptQTask[5].tQTaskChildren.ptMiddle;
  v4 = 10;
  do
  {
    if ( *p_ptMiddle )
    {
      if ( (*p_ptMiddle)->tQTaskChildren.ptHead )
      {
        QTask_Delete((*p_ptMiddle)->tQTaskChildren.ptHead);
        v5 = (struct MemPoolFreeItem_s *)*p_ptMiddle;
        if ( *p_ptMiddle )
        {
          if ( v5->ptNext )
            v5 = (struct MemPoolFreeItem_s *)Node_Remove(v5);
          --QTask_tQTaskRefPool.nAllocatedBlocks;
          v5->ptNext = QTask_tQTaskRefPool.tMemPoolFreeList.ptHead;
          QTask_tQTaskRefPool.tMemPoolFreeList.ptHead = v5;
          *p_ptMiddle = nullptr;
        }
      }
    }
    p_ptMiddle += 11;
    --v4;
  }
  while ( v4 );
  ptQTask[16].tQTaskChildren.ptMiddle = nullptr;
}

// source: j/0/weapons/weapon.c:4118  [anchor-callee]
float __cdecl Weapon_GetSummedMovementSlowDown(struct Weapon_s *ptWeapon)
{
  double v1; // st7
  struct WeaponTypeItem_s *ptHead; // eax
  struct WeaponType_s *ptWeaponType; // edx

  v1 = 0.0;
  if ( ptWeapon )
  {
    ptHead = (struct WeaponTypeItem_s *)ptWeapon->tPrivate.tActiveWeaponTypes.ptHead;
    if ( ptHead->tNode.ptNext )
    {
      if ( ptHead )
      {
        do
        {
          if ( ptHead->isActive )
          {
            ptWeaponType = ptHead->ptWeaponType;
            if ( ptWeapon->tPrivate.ptActiveWeapon == ptHead )
              v1 = v1 + ptWeaponType->vMovementSpeedModifier;
            else
              v1 = v1 + ptWeaponType->vMovementSpeedModifier * 0.5;
          }
          ptHead = (struct WeaponTypeItem_s *)ptHead->tNode.ptNext;
        }
        while ( ptHead->tNode.ptNext && ptHead );
      }
    }
  }
  return v1;
}

// source: j/0/weapons/weapon.c:4164  [size]
enum bool __cdecl Weapon_IsThermoVisionActive(struct Weapon_s *ptWeapon)
{
  return ptWeapon->tPrivate.isThermoVisionActive;
}

// source: j/0/weapons/weapon.c:4178  [anchor-callee]
char *__cdecl Weapon_AddSoundToSoundSequence(
        struct QTask_s *ptWeaponQTask,
        char *zSoundName,
        float vTimeToPlay)
{
  struct QTask_s *ptMiddle; // ecx
  int v4; // ecx
  float *v5; // esi
  int v6; // edx
  char v7; // cl

  if ( strlen(zSoundName) < 0x20 )
  {
    ptMiddle = ptWeaponQTask[16].tQTaskChildren.ptMiddle;
    if ( (int)ptMiddle < 10 )
    {
      v4 = 44 * (_DWORD)ptMiddle;
      v5 = (float *)((char *)&ptWeaponQTask[5].tQTaskChildren.ptMiddle + v4);
      *v5 = 0.0;
      v6 = (char *)&ptWeaponQTask[5].tQTaskChildren.ptTail + v4 - zSoundName;
      do
      {
        v7 = *zSoundName;
        zSoundName[v6] = *zSoundName;
        ++zSoundName;
      }
      while ( v7 );
      v5[10] = vTimeToPlay;
      ++*(int *)&ptWeaponQTask[16].tQTaskChildren.ptMiddle;
      return (char *)LODWORD(vTimeToPlay);
    }
  }
  return zSoundName;
}

// source: j/0/weapons/weapon.c:4212  [anchor-hash]
struct QTask_s *__cdecl Weapon_DeleteFirstSoundInSoundSequence(struct QTask_s *ptWeaponQTask)
{
  struct QTask_s *ptMiddle; // eax
  struct QTask_s *v3; // ebx
  struct QTask_s *ptHead; // eax
  struct QTask_s *result; // eax
  int v6; // edx

  ptMiddle = ptWeaponQTask[5].tQTaskChildren.ptMiddle;
  v3 = (struct QTask_s *)((char *)ptWeaponQTask + 212);
  if ( ptMiddle )
  {
    ptHead = ptMiddle->tQTaskChildren.ptHead;
    if ( ptHead )
      QTask_Delete(ptHead);
    QReference_Delete((struct QReference_s *)v3->ptNext, &QTask_tQTaskRefPool);
  }
  result = (struct QTask_s *)((char *)v3[11].ptNext - 1);
  v3[11].ptNext = result;
  v6 = 0;
  if ( (int)result > 0 )
  {
    result = v3;
    do
    {
      qmemcpy(result, &result[1].ptPrev, 0x2Cu);
      ++v6;
      result = (struct QTask_s *)((char *)result + 44);
    }
    while ( v6 < (int)v3[11].ptNext );
  }
  return result;
}

// source: j/0/weapons/weapon.c:4255  [anchor-hash]
void __cdecl Weapon_ClearSoundSequence(struct QTask_s *ptWeaponQTask)
{
  while ( ptWeaponQTask[16].tQTaskChildren.ptMiddle )
    Weapon_DeleteFirstSoundInSoundSequence(ptWeaponQTask);
}

// source: j/0/weapons/weapon.c:4278  [anchor-strings]
void __cdecl Weapon_MaintainSoundSequence(struct QTask_s *ptWeaponQTask)
{
  char *p_ptMiddle; // esi
  int v3; // edx
  struct QTask_s *v4; // eax
  struct QTask_s *v5; // edi
  struct QReference_s *v6; // eax
  unsigned __int16 v7; // cx
  char zWarn[256]; // [esp+8h] [ebp-100h] BYREF

  p_ptMiddle = (char *)&ptWeaponQTask[5].tQTaskChildren.ptMiddle;
  if ( ptWeaponQTask[16].tQTaskChildren.ptMiddle )
  {
    while ( *(_DWORD *)p_ptMiddle )
    {
      v3 = *(_DWORD *)(*(_DWORD *)p_ptMiddle + 8);
      if ( !v3
        || *(float *)&ptWeaponQTask[6].tQTaskChildren.ptMiddle > 0.0
        && QTask_IsQTaskTypeDerived(*(_WORD *)(v3 + 36), SoundDefSound_eQTaskType)
        && *(float *)(v3 + 344) > (double)*(float *)&ptWeaponQTask[6].tQTaskChildren.ptMiddle )
      {
        Weapon_DeleteFirstSoundInSoundSequence(ptWeaponQTask);
        if ( ptWeaponQTask[16].tQTaskChildren.ptMiddle )
          continue;
      }
      return;
    }
    v4 = SoundSys_NewSoundFn(ptWeaponQTask, (char *)&ptWeaponQTask[5].tQTaskChildren.ptTail);
    v5 = v4;
    if ( v4 )
    {
      v6 = QTask_NewQTaskRef(v4);
      v7 = SoundDefSound_eQTaskType;
      *(_DWORD *)p_ptMiddle = v6;
      if ( QTask_IsQTaskTypeDerived(v5->eQTaskType, v7) )
      {
        v5[8].tQTaskRefList.ptMiddle = (struct QReference_s *)1023969417;
        LOBYTE(v5[6].eQTaskType) = 0;
      }
    }
    else
    {
      sprintf(zWarn, "Weapon: %s sound not found", p_ptMiddle + 4);
    }
  }
}

// source: j/0/weapons/weapon.c:4359  [anchor-hash]
int __cdecl Weapon_GetActiveFireMode(struct QTask_s *ptWeaponQTask)
{
  struct QTask_s *ptPrev; // eax

  ptPrev = ptWeaponQTask[1].ptPrev;
  if ( ptPrev )
    return (int)ptPrev->tQTaskRefList.ptMiddle;
  else
    return 0;
}

// source: j/0/weapons/weapon.c:4382  [size]
enum bool __cdecl Weapon_IsKickBack(struct QTask_s *ptWeaponQTask)
{
  return (enum bool)ptWeaponQTask[16].ptParent;
}

// source: j/0/weapons/weapon.c:4400  [size]
struct QTask_s *__cdecl Weapon_ResetKickBack(struct QTask_s *ptWeaponQTask)
{
  ptWeaponQTask[16].ptParent = nullptr;
  return ptWeaponQTask;
}

// source: j/0/weapons/weapon.c:4416  [anchor-hash]
char *__cdecl Weapon_SetStatusDisplayWeaponType(
        struct QTask_s *ptQTask,
        char *zWeaponType)
{
  char *result; // eax

  result = (char *)Weapon_GetWeaponTypeItemFromWeaponType(ptQTask, zWeaponType);
  if ( result )
    ptQTask[1].ptNext = (struct QTask_s *)result;
  return result;
}

// source: j/0/weapons/weapon.c:4441  [anchor-hash]
struct WeaponType_s *__cdecl Weapon_GetStatusDisplayWeaponType(struct QTask_s *ptQTask)
{
  struct QTask_s *ptNext; // eax

  ptNext = ptQTask[1].ptNext;
  if ( ptNext )
    return (struct WeaponType_s *)ptNext->tQTaskChildren.ptTail;
  else
    return nullptr;
}

// source: j/0/weapons/weapon.c:4465  [anchor-hash]
enum bool __cdecl Weapon_IsActiveWeaponMissileLauncher(struct QTask_s *ptQTask)
{
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptTail; // eax
  enum bool result; // eax

  ptPrev = ptQTask[1].ptPrev;
  result = false;
  if ( ptPrev )
  {
    ptTail = ptPrev->tQTaskChildren.ptTail;
    if ( ptTail )
    {
      if ( ptTail[32].tQTaskRefList.ptHead == (struct QReference_s *)Gun_eQTaskType
        && *(_DWORD *)&ptTail[32].ptParent->tQTaskChildren.ptHead[2].eQTaskType == Missile_eQTaskType )
      {
        return true;
      }
    }
  }
  return result;
}

// source: j/0/weapons/weapon.c:4509  [anchor-callee]
void __cdecl Weapon_UpdateOwnersMissionScoreShots(
        struct QTask_s *ptQTask,
        int nFireType,
        int nShotsFired)
{
  struct QTask_s *ptTail; // eax
  struct QTask_s *ptPrev; // ecx
  struct QTask_s *ptHead; // edi
  struct WeaponGetFireTypeAmmoContext_s tFireTypeAmmoInfo; // [esp+0h] [ebp-14h] BYREF

  ptTail = ptQTask[2].tQTaskChildren.ptTail;
  if ( ptTail )
  {
    ptPrev = ptQTask[1].ptPrev;
    if ( ptPrev )
    {
      ptHead = ptTail->tQTaskChildren.ptHead;
      if ( ptHead )
      {
        Weapon_GetFireTypeAmmoInfoFromWeaponTypeItem(
          (struct Weapon_s *)ptQTask,
          (struct WeaponTypeItem_s *)ptPrev,
          nFireType,
          &tFireTypeAmmoInfo);
        if ( tFireTypeAmmoInfo.ptAmmoType )
        {
          if ( tFireTypeAmmoInfo.ptAmmoType->isCountsOnAccuracy )
          {
            if ( ptQTask[1].ptPrev->tQTaskChildren.ptTail[16].tQTaskRefList.ptTail <= (struct QReference_s *)2 )
              ptHead[12].ptPrev = (struct QTask_s *)((char *)ptHead[12].ptPrev + nShotsFired);
          }
        }
      }
    }
  }
}

// source: j/0/weapons/weapon.c:4552  [anchor-callee]
void __cdecl Weapon_DisableAllWeaponTypes(struct QTask_s *ptWeaponQTask)
{
  struct QTask_s *ptTail; // eax
  struct QTask_s *i; // esi

  ptTail = ptWeaponQTask[4].tQTaskChildren.ptTail;
  for ( i = ptTail->ptNext; i; i = i->ptNext )
  {
    Weapon_DisableWeaponType(ptWeaponQTask, (char *)&ptTail->tQTaskChildren.ptTail[2].ptPrev, true);
    ptTail = i;
  }
}

// source: j/0/weapons/weapon.c:4580  [anchor-hash]
void __cdecl Weapon_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  __int16 v1; // ax
  unsigned __int16 v2; // si
  unsigned __int16 v3; // si
  struct ParameterList_s *v4; // eax
  struct ParameterList_s *v5; // eax
  struct ParameterList_s *v6; // eax
  int v7; // edx
  int i; // esi
  char *v9; // eax
  struct SerializeListType_s *v10; // [esp-28h] [ebp-30h]

  BaseQTaskType = QTask_GetBaseQTaskType();
  Weapon_eQTaskType = QTask_NewQTaskType("WeaponHandler", 688, BaseQTaskType, 0, 0);
  QTask_LinkQTaskEventHandlerFn(
    Weapon_eQTaskType,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskDontSaveHandler);
  Weapon_eFireQTaskEvent = QTask_NewQTaskEventFn(0, "Weapon_Fire");
  Weapon_eGetWeaponPrecisionQTaskEvent = QTask_NewQTaskEventFn(0, "Weapon_GetPrecision");
  Weapon_eReleaseQTaskEvent = QTask_NewQTaskEventFn(0, "Weapon_Release");
  Weapon_eReloadQTaskEvent = QTask_NewQTaskEventFn(0, "Weapon_Reload");
  Weapon_eZoomQTaskEvent = QTask_NewQTaskEventFn(0, "Weapon_Zoom");
  Weapon_eActivateQTaskEvent = QTask_NewQTaskEventFn(0, "Weapon_Activate");
  Weapon_eDeActivateQTaskEvent = QTask_NewQTaskEventFn(0, "Weapon_DeActivate");
  Weapon_eGetParentParametersQTaskEvent = QTask_NewQTaskEventFn(0, "Weapon_GetParentParameters");
  Weapon_eCreateProjectileQTaskEvent = QTask_NewQTaskEventFn(0, "Weapon_CreateProjectile");
  Weapon_ePositionOverlayQTaskEvent = QTask_NewQTaskEventFn(0, "Weapon_PositionOverlay");
  v1 = QTask_NewQTaskEventFn(0, "GetWeaponObject");
  v2 = Weapon_eQTaskType;
  Weapon_eGetWeaponObjectEvent = v1;
  QTask_LinkQTaskEventHandlerFn(Weapon_eQTaskType, 0, Weapon_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, 1, Weapon_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, RunDelayed_eQTaskEvent, Weapon_RunDelayedHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, 2, Weapon_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v2, StatusScreen_eStatusDisplayQTaskEvent, Weapon_StatusDisplayHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, Attach_eUpdateAttachmentEvent, sub_5288F0);
  QTask_LinkQTaskEventHandlerFn(v2, DynCubeObj_eDynCubeObjRegisterQTaskEvent, sub_528970);
  QTask_LinkQTaskEventHandlerFn(v2, DynCubeObj_eDynCubeObjRemoveQTaskEvent, sub_5289F0);
  NetManager_RegisterGameMessage((struct Node_s *)0x57534652, Weapon_eFireQTaskEvent, 0);
  NetManager_RegisterGameMessage((struct Node_s *)0x57535253, Weapon_eReleaseQTaskEvent, 0);
  NetManager_RegisterGameMessage((struct Node_s *)0x5753524C, Weapon_eReloadQTaskEvent, 0);
  NetManager_RegisterGameMessage((struct Node_s *)0x57535A4D, Weapon_eZoomQTaskEvent, 0);
  NetManager_RegisterGameMessage((struct Node_s *)0x57534154, Weapon_eActivateQTaskEvent, 0);
  v3 = Weapon_eQTaskType;
  QTask_LinkQTaskEventHandlerFn(
    Weapon_eQTaskType,
    Serialize_eGetSerializeParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Weapon_GetSerializeParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v3, Serialize_eDeSerializeQTaskEvent, Weapon_DeSerializeHandler);
  v4 = (struct ParameterList_s *)Mem_AllocFn(72, 4);
  v4->nParameters = 0;
  v4->nMaxParameters = 3;
  v4->ptParameterListItem = (struct ParameterListItem_s *)&v4[1];
  Weapon_ptAmmoSerializeListItemParameterList = v4;
  v5 = (struct ParameterList_s *)Mem_AllocFn(132, 4);
  v5->ptParameterListItem = (struct ParameterListItem_s *)&v5[1];
  v5->nParameters = 0;
  v5->nMaxParameters = 6;
  Weapon_ptWeaponSerializeListItemParameterList = v5;
  Weapon_ptAmmoSerializeListType = SerializeList_NewListType(
                                     "AmmoItem",
                                     Weapon_ptAmmoSerializeListItemParameterList,
                                     0x18u,
                                     nullptr,
                                     nullptr,
                                     Weapon_SerializeListUpdateAmmoItemHandler);
  Weapon_ptWeaponSerializeListType = SerializeList_NewListType(
                                       "WeaponItem",
                                       Weapon_ptWeaponSerializeListItemParameterList,
                                       0x20u,
                                       nullptr,
                                       nullptr,
                                       Weapon_SerializeListUpdateWeaponItemHandler);
  v6 = (struct ParameterList_s *)Mem_AllocFn(72, 4);
  v10 = Weapon_ptAmmoSerializeListType;
  v6->ptParameterListItem = (struct ParameterListItem_s *)&v6[1];
  v7 = SerializeList_eParameterType;
  v6->nParameters = 0;
  v6->nMaxParameters = 3;
  Weapon_ptSerializeParameterList = v6;
  ParameterList_AddParameter(v6, 0xBCu, v7, "AmmoTypeList", 7u, v10);
  ParameterList_AddParameter(
    Weapon_ptSerializeParameterList,
    0xB0u,
    SerializeList_eParameterType,
    "WeaponTypeList",
    7u,
    Weapon_ptWeaponSerializeListType);
  ParameterList_AddParameter(
    Weapon_ptSerializeParameterList,
    0x30u,
    Level_eParameterTypeInt32,
    "iActiveWeapon",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Weapon_ptAmmoSerializeListItemParameterList,
    8u,
    Level_eParameterTypeInt32,
    "AmmoCount",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Weapon_ptAmmoSerializeListItemParameterList,
    0xCu,
    Level_eParameterTypeInt32,
    "AmmoLimit",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Weapon_ptAmmoSerializeListItemParameterList,
    0x14u,
    Level_eParameterTypeInt32,
    "AmmoTypeID",
    7u,
    nullptr);
  for ( i = 0; i < 2; ++i )
  {
    v9 = (char *)Mem_AllocFn(32, 4);
    Weapon_apzFireTypeAmmoCountParameterName[i] = v9;
    sprintf(v9, "FireTypeAmmoCount%d", i);
    ParameterList_AddParameter(
      Weapon_ptWeaponSerializeListItemParameterList,
      (unsigned int)&Weapon_apzFireTypeAmmoCountParameterName[i - 31963518],
      Level_eParameterTypeInt32,
      Weapon_apzFireTypeAmmoCountParameterName[i],
      7u,
      nullptr);
  }
  ParameterList_AddParameter(
    Weapon_ptWeaponSerializeListItemParameterList,
    0x14u,
    Level_eParameterTypeInt32,
    "WeaponTypeID",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Weapon_ptWeaponSerializeListItemParameterList,
    0x18u,
    Level_eParameterTypeInt32,
    "FireMode",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Weapon_ptWeaponSerializeListItemParameterList,
    0x1Cu,
    Level_eParameterTypebool8,
    "isActive",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Weapon_ptWeaponSerializeListItemParameterList,
    0x1Du,
    Level_eParameterTypebool8,
    "isLaserDotOn",
    7u,
    nullptr);
}

// source: j/0/weapons/weapon.c:4660  [anchor-hash]
void __cdecl Weapon_Close()
{
  char **v0; // ebx
  int v1; // esi
  int v2; // esi
  int v3; // esi
  int v4; // esi

  v0 = Weapon_apzFireTypeAmmoCountParameterName;
  do
  {
    if ( *v0 )
    {
      v1 = *(_DWORD *)((unsigned int)(*v0 - 4) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v1);
      memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
      free((void *)v1);
    }
    *v0++ = nullptr;
  }
  while ( (int)v0 < 127854088 );
  if ( Weapon_ptSerializeParameterList )
  {
    v2 = *(_DWORD *)((unsigned int)&Weapon_ptSerializeParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v2);
    memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
    free((void *)v2);
  }
  if ( Weapon_ptAmmoSerializeListItemParameterList )
  {
    v3 = *(_DWORD *)((unsigned int)&Weapon_ptAmmoSerializeListItemParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v3);
    memset(*(void **)(v3 + 8), 0xCDu, *(_DWORD *)(v3 + 16));
    free((void *)v3);
  }
  if ( Weapon_ptWeaponSerializeListItemParameterList )
  {
    v4 = *(_DWORD *)((unsigned int)&Weapon_ptWeaponSerializeListItemParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v4);
    memset(*(void **)(v4 + 8), 0xCDu, *(_DWORD *)(v4 + 16));
    free((void *)v4);
  }
  NetManager_RemoveGameMessage(0x57534652u);
  NetManager_RemoveGameMessage(0x57535253u);
  NetManager_RemoveGameMessage(0x5753524Cu);
  NetManager_RemoveGameMessage(0x57535A4Du);
  NetManager_RemoveGameMessage(0x57534154u);
  QTask_DeleteQTaskEvent(Weapon_eFireQTaskEvent);
  QTask_DeleteQTaskEvent(Weapon_eReleaseQTaskEvent);
  QTask_DeleteQTaskEvent(Weapon_eReloadQTaskEvent);
  QTask_DeleteQTaskEvent(Weapon_eZoomQTaskEvent);
  QTask_DeleteQTaskEvent(Weapon_eActivateQTaskEvent);
  QTask_DeleteQTaskEvent(Weapon_eDeActivateQTaskEvent);
  QTask_DeleteQTaskEvent(Weapon_eGetParentParametersQTaskEvent);
  QTask_DeleteQTaskEvent(Weapon_eCreateProjectileQTaskEvent);
  QTask_DeleteQTaskEvent(Weapon_ePositionOverlayQTaskEvent);
  QTask_DeleteQTaskEvent(Weapon_eGetWeaponPrecisionQTaskEvent);
  QTask_DeleteQTaskEvent(Weapon_eGetWeaponObjectEvent);
  QTask_DeleteQTaskType(Weapon_eQTaskType);
}
