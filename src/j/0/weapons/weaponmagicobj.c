/* j/0/weapons/weaponmagicobj.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/weapons/weaponmagicobj.c:49  [anchor-mhash]
char *__cdecl WeaponMagicObj_GetModelName(struct QTask_s *ptWeaponMagicObj)
{
  struct QTask_s *ptParent; // edx
  char *result; // eax
  unsigned __int16 v3; // bx
  unsigned __int16 v4; // bp
  int v5; // edi
  struct QTask_s *v6; // eax
  int v7; // ecx
  int v8; // esi
  unsigned __int16 eQTaskType; // si
  struct QTask_s *ptNext; // edx
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptTail; // eax
  char v13; // cl

  ptParent = ptWeaponMagicObj->ptParent;
  result = "none";
  if ( ptParent )
  {
    v3 = Human_eQTaskType;
    v4 = AnimController_eQTaskType;
    v5 = ModelObj_nDisabledAttachObjects;
    while ( 1 )
    {
      if ( QTask_IsQTaskTypeDerived(ptParent->eQTaskType, v4) )
      {
        v6 = ptParent[1].ptParent;
        if ( v6 )
        {
          v7 = 0;
          if ( *(int *)&v6->eQTaskType > 0 )
          {
            v8 = 0;
            do
            {
              ModelObj_apzDisabledAttachObjects[v5] = (char *)&v6[1].ptNext[v8];
              v6 = ptParent[1].ptParent;
              ++v5;
              ++v7;
              v8 += 2;
            }
            while ( v7 < (int)(*(_DWORD *)&v6->eQTaskType) );
          }
        }
      }
      eQTaskType = ptParent->eQTaskType;
      if ( QTask_IsQTaskTypeDerived(eQTaskType, v3) )
      {
        ptNext = ptParent[33].ptNext;
        ModelObj_nDisabledAttachObjects = v5;
        if ( ptNext )
        {
          ptPrev = ptNext[1].ptPrev;
          if ( ptPrev )
          {
            ptTail = ptPrev->tQTaskChildren.ptTail;
            if ( ptTail )
              return (char *)&ptTail[16].eQTaskType;
          }
        }
        return "none";
      }
      if ( QTask_IsQTaskTypeDerived(eQTaskType, EditBoneObj_eQTaskType) )
        break;
      ptParent = ptParent->ptParent;
      if ( !ptParent )
      {
        ModelObj_nDisabledAttachObjects = v5;
        return "none";
      }
    }
    v13 = (char)ptParent[12].ptNext;
    result = (char *)&ptParent[12];
    ModelObj_nDisabledAttachObjects = v5;
    if ( v13 )
      return result;
    return "none";
  }
  return result;
}

// source: j/0/weapons/weaponmagicobj.c:136  [anchor-mhash]
void __cdecl WeaponMagicObj_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = WeaponMagicObj_GetModelName(ptQTask);
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][RigidMagicObj_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  ModelObj_nDisabledAttachObjects = 0;
}

// source: j/0/weapons/weaponmagicobj.c:157  [anchor-caller]
void __cdecl PrimaryMagicObj_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptParent; // edx
  char *zFixedModel; // esi
  unsigned __int16 v4; // cx
  struct Weapon_s *ptNext; // eax
  struct WeaponTypeItem_s *WeaponTypeItemFromCategory; // eax
  int v7; // ecx

  ptParent = ptQTask->ptParent;
  zFixedModel = "none";
  if ( ptParent )
  {
    v4 = Human_eQTaskType;
    while ( QTask_IsQTaskTypeDerived(ptParent->eQTaskType, v4) == false )
    {
      ptParent = ptParent->ptParent;
      if ( !ptParent )
        goto LABEL_9;
    }
    ptNext = (struct Weapon_s *)ptParent[33].ptNext;
    if ( ptNext )
    {
      WeaponTypeItemFromCategory = Weapon_GetWeaponTypeItemFromCategory(ptNext, WEAPONCATEGORY_PRIMARY);
      if ( WeaponTypeItemFromCategory )
        zFixedModel = WeaponTypeItemFromCategory->ptWeaponType->zFixedModel;
    }
  }
LABEL_9:
  v7 = RigidMagicObj_eQTaskType;
  *(_DWORD *)pxContext = zFixedModel;
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][v7].pfHandler)(ptQTask, pxContext);
}

// source: j/0/weapons/weaponmagicobj.c:214  [anchor-mhash]
void __cdecl WeaponMagicObj_GrenadePinMagicObjEnterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptParent; // edx
  unsigned __int16 v3; // di
  struct QTask_s *v4; // edx
  unsigned __int16 v5; // cx
  struct QTask_s *ptNext; // edx

  ptParent = ptQTask->ptParent;
  v3 = RigidMagicObj_eQTaskType;
  if ( QTask_IsQTaskTypeDerived(ptParent->eQTaskType, RigidMagicObj_eQTaskType) == false )
    goto LABEL_9;
  v4 = ptParent->ptParent;
  if ( !v4 )
    goto LABEL_9;
  v5 = Human_eQTaskType;
  while ( QTask_IsQTaskTypeDerived(v4->eQTaskType, v5) == false )
  {
    v4 = v4->ptParent;
    if ( !v4 )
      goto LABEL_9;
  }
  ptNext = v4[33].ptNext;
  if ( !ptNext || !ptNext[16].tQTaskChildren.ptTail )
LABEL_9:
    ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[MagicObj_eMagicObjEnterEvent][v3].pfHandler)(
      ptQTask,
      pxContext);
}

// source: j/0/weapons/weaponmagicobj.c:260  [anchor-mhash]
void __cdecl WeaponMagicObj_RPGRocketMagicObjEnterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptParent; // edx
  unsigned __int16 v3; // di
  unsigned __int16 v4; // bx
  unsigned __int16 v5; // bp
  unsigned __int16 eQTaskType; // si
  struct QTask_s *ptNext; // eax
  struct WeaponGetFireTypeAmmoContext_s tAmmoContext; // [esp+10h] [ebp-14h] BYREF

  ptParent = ptQTask->ptParent;
  if ( ptParent )
  {
    v3 = MagicObjContainer_eQTaskType;
    v4 = Human_eQTaskType;
    v5 = GunPickup_eQTaskType;
    do
    {
      eQTaskType = ptParent->eQTaskType;
      if ( QTask_IsQTaskTypeDerived(eQTaskType, v3) )
      {
        ptParent = ptParent[1].ptNext;
      }
      else if ( QTask_IsQTaskTypeDerived(eQTaskType, v4) )
      {
        ptNext = ptParent[33].ptNext;
        if ( ptNext )
        {
          Weapon_GetFireTypeAmmoInfoFromWeaponTypeItem(
            (struct Weapon_s *)ptParent[33].ptNext,
            (struct WeaponTypeItem_s *)ptNext[1].ptPrev,
            0,
            &tAmmoContext);
          if ( !tAmmoContext.nAmmoInWeapon )
            return;
          break;
        }
      }
      else
      {
        if ( QTask_IsQTaskTypeDerived(eQTaskType, v5) )
        {
          if ( (int)ptParent[8].ptNext <= 0 )
            return;
          break;
        }
        ptParent = ptParent->ptParent;
      }
    }
    while ( ptParent );
  }
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[MagicObj_eMagicObjEnterEvent][RigidMagicObj_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
}

// source: j/0/weapons/weaponmagicobj.c:322  [anchor-mhash]
void __cdecl WeaponMagicObj_BombBackpackMagicObjEnterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptParent; // esi
  unsigned __int16 v3; // bx
  unsigned __int16 v4; // di
  unsigned __int16 eQTaskType; // dx
  int v6; // eax
  struct GetWeaponObjectContext_t tGetWeaponObjectContext; // [esp+8h] [ebp-Ch] BYREF

  ptParent = ptQTask->ptParent;
  if ( !ptParent )
    return;
  v3 = Human_eQTaskType;
  v4 = MagicObjContainer_eQTaskType;
  while ( 1 )
  {
    eQTaskType = ptParent->eQTaskType;
    if ( QTask_IsQTaskTypeDerived(eQTaskType, v4) )
    {
      ptParent = ptParent[1].ptNext;
      goto LABEL_13;
    }
    if ( QTask_IsQTaskTypeDerived(eQTaskType, v3) == false )
    {
      ptParent = ptParent->ptParent;
      goto LABEL_13;
    }
    if ( ptParent[33].ptNext )
      break;
LABEL_13:
    if ( !ptParent )
      return;
  }
  if ( Weapon_IsWeaponSelectable(ptParent[33].ptNext, "WEAPON_ID_C4BOMB") )
  {
    v6 = ptParent->eQTaskType;
    memset(&tGetWeaponObjectContext, 0, sizeof(tGetWeaponObjectContext));
    ((void (__cdecl *)(struct QTask_s *, struct GetWeaponObjectContext_t *))QTask_aatQTaskFinalEvent[Weapon_eGetWeaponObjectEvent][v6].pfHandler)(
      ptParent,
      &tGetWeaponObjectContext);
    if ( !tGetWeaponObjectContext.ptWeaponObject
      || strcmp(tGetWeaponObjectContext.ptWeaponObject->tModelObj.ptLODVirModel->zFirstVirModelName, "113_01_1") )
    {
      ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[MagicObj_eMagicObjEnterEvent][RigidMagicObj_eQTaskType].pfHandler)(
        ptQTask,
        pxContext);
    }
  }
}

void __cdecl WeaponMagicObj_Refresh(struct QTask_s *a1, struct QTask_s *ptQTask)
{
  struct QTask_s *ptParent; // esi
  unsigned __int16 v3; // di
  unsigned __int16 v4; // bx
  unsigned __int16 eQTaskType; // dx
  int v6; // eax
  _DWORD v7[3]; // [esp+10h] [ebp-Ch] BYREF

  ptParent = a1->ptParent;
  if ( !ptParent )
    goto LABEL_13;
  v3 = MagicObjContainer_eQTaskType;
  v4 = Human_eQTaskType;
  while ( 1 )
  {
    eQTaskType = ptParent->eQTaskType;
    if ( QTask_IsQTaskTypeDerived(eQTaskType, v3) )
    {
      ptParent = ptParent[1].ptNext;
      goto LABEL_12;
    }
    if ( QTask_IsQTaskTypeDerived(eQTaskType, v4) == false )
    {
      ptParent = ptParent->ptParent;
      goto LABEL_12;
    }
    if ( ptParent[33].ptNext )
      break;
LABEL_12:
    if ( !ptParent )
      goto LABEL_13;
  }
  if ( Weapon_IsWeaponSelectable(ptParent[33].ptNext, "WEAPON_ID_C4BOMB") )
  {
    v6 = ptParent->eQTaskType;
    memset(v7, 0, sizeof(v7));
    ((void (__cdecl *)(struct QTask_s *, _DWORD *))QTask_aatQTaskFinalEvent[Weapon_eGetWeaponObjectEvent][v6].pfHandler)(
      ptParent,
      v7);
    if ( !v7[0] || strcmp((char *)(*(_DWORD *)(v7[0] + 116) + 20), "113_01_1") )
    {
      QTask_TriggerQTaskEventParent(a1, ShadowVolume_eGetShadowInfoEvent, ptQTask);
      return;
    }
  }
LABEL_13:
  ptQTask->tQTaskChildren.ptMiddle = nullptr;
}

// source: j/0/weapons/weaponmagicobj.c:423  [anchor-strings]
void __cdecl WeaponMagicObj_Open()
{
  unsigned __int16 v0; // ax
  void *v1; // esi
  _DWORD *v2; // esi
  _DWORD *v3; // esi
  _DWORD *v4; // esi
  _DWORD *v5; // esi
  _DWORD *v6; // esi

  v0 = QTask_NewQTaskType("WeaponMagicObj", 328, RigidMagicObj_eQTaskType, 0, 0);
  v1 = (void *)v0;
  WeaponMagicObj_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 0, WeaponMagicObj_CreateHandler);
  Symbol_Register(
    "TASKTYPE_WEAPONMAGICOBJ",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    v1,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  v2 = Mem_AllocFn(18444, 4);
  v2[1] = 0;
  *v2 = 0;
  v2[4610] = "TASKTYPE_WEAPONMAGICOBJ";
  Wildcard_CreateNFA("TASKTYPE_WEAPONMAGICOBJ", v2 + 2, (char *)v2 + 10248);
  List_AddTail(v2, (int)&MagicObjConfig_tTaskTypeEnumList);
  LOWORD(v2) = QTask_NewQTaskType("PrimaryMagicObj", 328, RigidMagicObj_eQTaskType, 0, 0);
  WeaponMagicObj_ePrimaryMagicObjQTaskType = (unsigned __int16)v2;
  QTask_LinkQTaskEventHandlerFn((unsigned __int16)v2, 0, PrimaryMagicObj_CreateHandler);
  Symbol_Register(
    "TASKTYPE_PRIMARYMAGICOBJ",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)(unsigned __int16)v2,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  v3 = Mem_AllocFn(18444, 4);
  v3[1] = 0;
  *v3 = 0;
  v3[4610] = "TASKTYPE_PRIMARYMAGICOBJ";
  Wildcard_CreateNFA("TASKTYPE_PRIMARYMAGICOBJ", v3 + 2, (char *)v3 + 10248);
  List_AddTail(v3, (int)&MagicObjConfig_tTaskTypeEnumList);
  LOWORD(v3) = QTask_NewQTaskType("GrenadePin", 328, RigidMagicObj_eQTaskType, 0, 0);
  WeaponMagicObj_eGrenadePinQTaskType = (unsigned __int16)v3;
  QTask_LinkQTaskEventHandlerFn(
    (unsigned __int16)v3,
    MagicObj_eMagicObjEnterEvent,
    WeaponMagicObj_GrenadePinMagicObjEnterHandler);
  Symbol_Register(
    "TASKTYPE_GRENADEPIN",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)(unsigned __int16)v3,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  v4 = Mem_AllocFn(18444, 4);
  v4[1] = 0;
  *v4 = 0;
  v4[4610] = "TASKTYPE_GRENADEPIN";
  Wildcard_CreateNFA("TASKTYPE_GRENADEPIN", v4 + 2, (char *)v4 + 10248);
  List_AddTail(v4, (int)&MagicObjConfig_tTaskTypeEnumList);
  LOWORD(v4) = QTask_NewQTaskType("RPGRocket", 328, RigidMagicObj_eQTaskType, 0, 0);
  WeaponMagicObj_eRPGRocketQTaskType = (unsigned __int16)v4;
  QTask_LinkQTaskEventHandlerFn(
    (unsigned __int16)v4,
    MagicObj_eMagicObjEnterEvent,
    WeaponMagicObj_RPGRocketMagicObjEnterHandler);
  Symbol_Register(
    "TASKTYPE_RPGROCKET",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)(unsigned __int16)v4,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  v5 = Mem_AllocFn(18444, 4);
  v5[1] = 0;
  *v5 = 0;
  v5[4610] = "TASKTYPE_RPGROCKET";
  Wildcard_CreateNFA("TASKTYPE_RPGROCKET", v5 + 2, (char *)v5 + 10248);
  List_AddTail(v5, (int)&MagicObjConfig_tTaskTypeEnumList);
  LOWORD(v5) = QTask_NewQTaskType("BombBackpack", 328, RigidMagicObj_eQTaskType, 0, 0);
  WeaponMagicObj_eBombBackpackQTaskType = (unsigned __int16)v5;
  QTask_LinkQTaskEventHandlerFn(
    (unsigned __int16)v5,
    MagicObj_eMagicObjEnterEvent,
    WeaponMagicObj_BombBackpackMagicObjEnterHandler);
  QTask_LinkQTaskEventHandlerFn(
    (unsigned __int16)v5,
    ShadowVolume_eGetShadowInfoEvent,
    (void (__cdecl *)(struct QTask_s *, void *))WeaponMagicObj_Refresh);
  Symbol_Register(
    "TASKTYPE_BOMBBACKPACK",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)(unsigned __int16)v5,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  v6 = Mem_AllocFn(18444, 4);
  v6[1] = 0;
  *v6 = 0;
  v6[4610] = "TASKTYPE_BOMBBACKPACK";
  Wildcard_CreateNFA("TASKTYPE_BOMBBACKPACK", v6 + 2, (char *)v6 + 10248);
  List_AddTail(v6, (int)&MagicObjConfig_tTaskTypeEnumList);
}
