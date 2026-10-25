/* j/0/weapons/projectilelauncher.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/weapons/projectilelauncher.c:49  [anchor-mhash]
void __cdecl ProjectileLauncher_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[1].tQTaskRefList.ptHead = (struct QReference_s *)1065353216;
  ptQTask[1].tQTaskRefList.ptMiddle = (struct QReference_s *)1065353216;
  ptQTask[1].tQTaskRefList.ptTail = (struct QReference_s *)1065353216;
  LOBYTE(ptQTask[1].ptNext) = 0;
  ptQTask[1].ptPrev = (struct QTask_s *)-1;
  ptQTask[1].tQTaskChildren.ptHead = nullptr;
  ptQTask[1].tQTaskChildren.ptMiddle = (struct QTask_s *)1;
  ptQTask[1].tQTaskChildren.ptTail = (struct QTask_s *)1082130432;
  LOBYTE(ptQTask[1].ptParent) = 0;
  LOBYTE(ptQTask[2].tQTaskRefList.ptMiddle) = 0;
  LOBYTE(ptQTask[3].tQTaskChildren.ptTail) = 0;
  LOBYTE(ptQTask[4].tQTaskChildren.ptHead) = 0;
  LOBYTE(ptQTask[5].ptNext) = 0;
  LOBYTE(ptQTask[5].ptParent) = 0;
  LOBYTE(ptQTask[6].tQTaskRefList.ptMiddle) = 0;
  ptQTask[7].tQTaskChildren.ptTail = (struct QTask_s *)512;
  ptQTask[7].tQTaskRefList.ptHead = (struct QReference_s *)512;
  ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
}

// source: j/0/weapons/projectilelauncher.c:82  [size]
void __cdecl ProjectileLauncher_DeleteHandler(struct QTask_s *ptQTask)
{
  WeaponType_DeleteParameters(&ptQTask[7].tQTaskRefList.ptMiddle);
}

// source: j/0/weapons/projectilelauncher.c:98  [size]
void __cdecl ProjectileLauncher_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = ProjectileLauncher_ptParameterList;
}

// source: j/0/weapons/projectilelauncher.c:116  [size]
void __cdecl ProjectileLauncher_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[1].tQTaskChildren.ptHead = (struct QTask_s *)AmmoType_GetAmmoTypeFromID((int)ptQTask[1].ptPrev);
}

// source: j/0/weapons/projectilelauncher.c:143  [size]
void __cdecl ProjectileLauncher_UpdateTagItemsHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: j/0/weapons/projectilelauncher.c:163  [size]
void __cdecl ProjectileLauncher_UpdaterInternalDataAfterLoadHandler(struct QTask_s *ptQTask)
{
  ptQTask[7].tQTaskRefList.ptMiddle = WeaponType_CreateParameters(
                                        (unsigned __int16)ptQTask[7].tQTaskChildren.ptTail,
                                        ptQTask);
  ptQTask[7].tQTaskRefList.ptHead = (struct QReference_s *)ptQTask[7].tQTaskChildren.ptTail;
}

// source: j/0/weapons/projectilelauncher.c:180  [size]
void __cdecl ProjectileLauncher_CreateWeaponTypeParametersHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v2; // esi

  v2 = QTask_NewFn(*((struct QTask_s **)pxContext + 1), ProjectileLauncher_eQTaskType, nullptr);
  *((_DWORD *)pxContext + 2) = v2;
  v2[7].tQTaskRefList.ptMiddle = WeaponType_CreateParameters((unsigned __int16)v2[7].tQTaskChildren.ptTail, v2);
}

// source: j/0/weapons/projectilelauncher.c:204  [size]
void __cdecl ProjectileLauncher_DeleteWeaponTypeParametersHandler(struct QTask_s *ptQTask, void *pxContext)
{
  WeaponType_DeleteParameters((struct QReference_s **)(*(_DWORD *)pxContext + 304));
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[WeaponType_eDeleteParametersQTaskEvent][FireType_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
}

// source: j/0/weapons/projectilelauncher.c:227  [anchor-strings]
void __cdecl ProjectileLauncher_GetAnimHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // esi
  int v3; // eax
  char *v4; // eax
  int v5; // edi
  struct QHashTable_s *v6; // esi
  unsigned int v7; // eax
  int v8; // eax
  int v9; // esi
  int v10; // eax
  struct WeaponGetFireTypeAmmoContext_s tFireTypeAmmoInfo; // [esp+10h] [ebp-14h] BYREF

  v2 = *((_DWORD *)pxContext + 5);
  Weapon_GetFireTypeAmmoInfoFromWeaponTypeItem(
    *((struct Weapon_s **)pxContext + 1),
    *(struct WeaponTypeItem_s **)(*((_DWORD *)pxContext + 1) + 44),
    *((_DWORD *)pxContext + 4),
    &tFireTypeAmmoInfo);
  v3 = *((_DWORD *)pxContext + 3);
  if ( v3 == 4 )
  {
    if ( tFireTypeAmmoInfo.nAmmoAvailable || (v5 = v2 + 104, !*(_BYTE *)(v2 + 104)) )
      v5 = v2 + 72;
    v6 = Hierarchy_ptHashTable;
    v7 = Hierarchy_ptHashTable->tPrivate.pfHashFunction(
           Hierarchy_ptHashTable->tPrivate.nHashTableSize,
           *(void **)pxContext);
    v8 = ((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Hierarchy_ptHashTable->tPrivate.pfFindElement)(v6, v7, (const void *)(*(void **)pxContext));
    v9 = *(_DWORD *)v8;
    v10 = (*(int (__cdecl **)(_DWORD, int))(*(_DWORD *)v8 + 12))(*(_DWORD *)(*(_DWORD *)v8 + 4), v5);
    *((_DWORD *)pxContext + 6) = (*(int (__cdecl **)(int, int, const void *))(v9 + 28))(v9, v10, (const void *)(v5));
  }
  else
  {
    if ( v3 != 17 )
    {
      LDebug_Error("Unkown WEAPONTYPE_GETANIMTYPE");
      abort();
    }
    if ( tFireTypeAmmoInfo.nAmmoAvailable || (v4 = (char *)(v2 + 168), !*(_BYTE *)(v2 + 168)) )
      v4 = (char *)(v2 + 136);
    *((_DWORD *)pxContext + 6) = Hierarchy_GetAnim(*(unsigned __int8 **)pxContext, v4);
  }
}

// source: j/0/weapons/projectilelauncher.c:276  [size]
void __cdecl ProjectileLauncher_GetAmmoInfoHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *((_DWORD *)pxContext + 2) = 1;
  *((_DWORD *)pxContext + 3) = 1;
  *((_DWORD *)pxContext + 4) = 1;
  *((_DWORD *)pxContext + 1) = *(_DWORD *)(*(_DWORD *)pxContext + 48);
}

// source: j/0/weapons/projectilelauncher.c:301  [anchor-mhash]
void __cdecl ProjectileLauncher_StatusDisplayHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zText[16]; };
    struct { char igi2_o1[16]; struct WeaponTypeGetFireTypeScreenPositionContext_s tPositionContext; };
    char igi2_extent[44];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // ebx
  int v3; // eax
  struct AmmoTypeItem_s *AmmoTypeItemFromAmmoType; // eax
  float *v5; // edi
  float v6; // eax
  int v7; // ecx
  int v8; // esi
  __int16 *v9; // eax
  void *pxContexta = *(void * *)&pxContext; // [esp+44h] [ebp+8h] ARGSLOT

  v2 = **((_DWORD **)pxContext + 1);
  v3 = *(_DWORD *)(*((_DWORD *)pxContext + 6) + 48);
  if ( v3 )
  {
    AmmoTypeItemFromAmmoType = Weapon_GetAmmoTypeItemFromAmmoType(
                                 *(struct QTask_s **)pxContext,
                                 (char *)(v3 + 40));
    if ( AmmoTypeItemFromAmmoType )
    {
      sprintf(igi2_frame.zText, "%4d", AmmoTypeItemFromAmmoType->nAmmoCount);
      Text_SetString(*(struct StaticTilemap_s **)(v2 + 1136), igi2_frame.zText);
      v5 = *(float **)(v2 + 1136);
      v6 = *v5;
      igi2_frame.tPositionContext.tIn.nFireType = *((_DWORD *)pxContext + 2);
      v7 = *(__int16 *)(LODWORD(v6) + 6);
      v8 = 0;
      pxContexta = nullptr;
      if ( v7 > 0 )
      {
        v9 = *(__int16 **)(LODWORD(v6) + 12);
        do
        {
          if ( *v9 > v8 )
            v8 = *v9;
          ++v9;
          --v7;
        }
        while ( v7 );
        pxContexta = (void *)v8;
      }
      igi2_frame.tPositionContext.tIn.vTextWidth = (float)(int)pxContexta;
      WeaponType_GetFireTypeScreenPosition(&igi2_frame.tPositionContext);
      v5[1] = (float)(__int64)igi2_frame.tPositionContext.tOut.vTextXPos;
      *(float *)(*(_DWORD *)(v2 + 1136) + 8) = (float)(__int64)igi2_frame.tPositionContext.tOut.vTextYPos;
      Text_Register(*(struct StaticTilemap_s **)(v2 + 1136));
    }
  }
}

// source: j/0/weapons/projectilelauncher.c:353  [anchor-mhash]
void __cdecl ProjectileLauncher_WeaponFireHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v3; // ebp
  int v4; // edi
  void *pfHandler; // ecx
  struct QTask_s *ptTail; // eax
  struct QTask_s *ptHead; // eax
  struct HumanAI_s *ptParent; // eax
  struct QTask_s *TargetQTask; // eax
  float v10; // eax
  float v11; // edx
  int v12; // eax
  int v13; // edx
  void *v14; // eax
  struct QTask_s *v15; // edx
  struct WeaponType_s *v16; // eax
  struct AmmoType_s *v17; // edx
  struct QTask_s *v18; // eax
  struct QTask_s *v19; // eax
  float v20; // edx
  bool v21; // zf
  double v22; // st7
  struct WeaponCreateProjectileContext_s tCreateContext; // [esp+18h] [ebp-48h] BYREF
  void *pxContexta = *(void * *)&pxContext; // [esp+68h] [ebp+8h] ARGSLOT

  v3 = *(struct QTask_s **)pxContext;
  v4 = *((_DWORD *)pxContext + 25);
  pfHandler = QTask_aatQTaskFinalEvent[Weapon_eCreateProjectileQTaskEvent][*(unsigned __int16 *)(v4 + 296)].pfHandler;
  pxContexta = pfHandler;
  if ( pfHandler && !*(_BYTE *)(v4 + 40) )
  {
    ptTail = v3[2].tQTaskChildren.ptTail;
    if ( ptTail
      && (ptHead = ptTail->tQTaskChildren.ptHead) != nullptr
      && (ptParent = (struct HumanAI_s *)ptHead[48].ptParent) != nullptr )
    {
      TargetQTask = HumanAI_GetTargetQTask(ptParent, true);
      pfHandler = pxContexta;
      tCreateContext.tIn.ptTarget = TargetQTask;
    }
    else
    {
      tCreateContext.tIn.ptTarget = nullptr;
    }
    tCreateContext.tIn.iTaskID = *((_BYTE *)pxContext + 96);
    tCreateContext.tIn.ptOrientation = (struct real32x9_t *)((char *)pxContext + 40);
    tCreateContext.tIn.ptFireOrientation = (struct real32x9_t *)((char *)pxContext + 40);
    v10 = *(float *)(v4 + 60);
    tCreateContext.tIn.ptPos = (struct real64x3_t *)((char *)pxContext + 16);
    v11 = *(float *)(v4 + 64);
    tCreateContext.tIn.vSpeed = v10;
    v12 = *((_DWORD *)pxContext + 23);
    tCreateContext.tIn.vEffectiveRange = v11;
    v13 = *(_DWORD *)(v4 + 304);
    tCreateContext.tIn.nHeldTime = v12;
    v14 = *(void **)(v13 + 8);
    v15 = *((struct QTask_s **)pxContext + 1);
    tCreateContext.tIn.pxProjectileParameters = v14;
    v16 = *((struct WeaponType_s **)pxContext + 26);
    tCreateContext.tIn.ptIgnoreQTask = v15;
    v17 = *(struct AmmoType_s **)(v4 + 48);
    tCreateContext.tIn.ptWeaponQTask = v3;
    tCreateContext.tIn.ptWeaponType = v16;
    tCreateContext.tIn.ptAmmoType = v17;
    v18 = v3[2].tQTaskChildren.ptTail;
    if ( v18 )
      v19 = v18->tQTaskChildren.ptHead;
    else
      v19 = nullptr;
    tCreateContext.tIn.ptHumanOperator = v19;
    tCreateContext.tIn.tParentSpeed.vX = *((float *)pxContext + 20);
    v20 = *((float *)pxContext + 21);
    tCreateContext.tIn.tParentSpeed.vZ = *((float *)pxContext + 22);
    v21 = v3[16].tQTaskChildren.ptTail == nullptr;
    tCreateContext.tIn.tParentSpeed.vY = v20;
    if ( v21 )
      tCreateContext.tIn.nExplodeTime = (__int64)(*(float *)(v4 + 56) * 30.0);
    else
      tCreateContext.tIn.nExplodeTime = (int)v3[16].tQTaskRefList.ptHead;
    ((void (__cdecl *)(_DWORD, struct WeaponCreateProjectileContext_s *))pfHandler)(0, &tCreateContext);
    v3[16].tQTaskChildren.ptTail = nullptr;
    v3[16].tQTaskRefList.ptHead = nullptr;
    *((_DWORD *)pxContext + 28) = 1;
    v22 = (double)*(int *)(v4 + 52);
    *((_DWORD *)pxContext + 30) = 1036831949;
    *((_DWORD *)pxContext + 29) = (__int64)(60.0 / v22 * 30.0);
    *((_DWORD *)pxContext + 32) = 1008981770;
    *((_DWORD *)pxContext + 33) = 1008981770;
    Weapon_PlaySound(*(struct QTask_s **)pxContext, 1, (char *)(v4 + 200), false);
  }
}

// source: j/0/weapons/projectilelauncher.c:459  [anchor-mhash]
void __cdecl ProjectileLauncher_WeaponReleaseHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct WeaponCreateProjectileContext_s tCreateContext; };
    struct { char igi2_o1[80]; void (__cdecl *pxContexta)(_DWORD, struct WeaponCreateProjectileContext_s *); };
    char igi2_extent[72];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // ecx
  int v4; // ebp
  int v5; // edi
  float v6; // edx
  float v7; // eax
  int v8; // ecx
  struct WeaponType_s *v9; // eax
  struct QTask_s *v10; // edx
  struct AmmoType_s *v11; // eax
  float v12; // edx
  float v13; // ecx
  bool v14; // zf

  v2 = 511 * Weapon_eCreateProjectileQTaskEvent;
  v4 = *(_DWORD *)pxContext;
  v5 = *((_DWORD *)pxContext + 24);
  *((_DWORD *)pxContext + 30) = 0;
  *((_DWORD *)pxContext + 31) = 0;
  *((_DWORD *)pxContext + 28) = 0;
  *((_DWORD *)pxContext + 29) = 0;
  igi2_frame.pxContexta = (void (__cdecl *)(_DWORD, struct WeaponCreateProjectileContext_s *))QTask_aatQTaskFinalEvent[0][*(unsigned __int16 *)(v5 + 296) + v2].pfHandler;
  if ( igi2_frame.pxContexta
    && *(_BYTE *)(v5 + 40)
    && Weapon_GetAmmoTypeItemFromAmmoType((struct QTask_s *)v4, (char *)(*(_DWORD *)(v5 + 48) + 40))->nAmmoCount > 0 )
  {
    v6 = *(float *)(v5 + 60);
    igi2_frame.tCreateContext.tIn.ptHumanOperator = *((struct QTask_s **)pxContext + 2);
    igi2_frame.tCreateContext.tIn.ptOrientation = (struct real32x9_t *)((char *)pxContext + 40);
    igi2_frame.tCreateContext.tIn.ptFireOrientation = (struct real32x9_t *)((char *)pxContext + 40);
    v7 = *(float *)(v5 + 64);
    igi2_frame.tCreateContext.tIn.ptPos = (struct real64x3_t *)((char *)pxContext + 16);
    v8 = *((_DWORD *)pxContext + 23);
    igi2_frame.tCreateContext.tIn.vEffectiveRange = v7;
    v9 = *((struct WeaponType_s **)pxContext + 25);
    igi2_frame.tCreateContext.tIn.nHeldTime = v8;
    igi2_frame.tCreateContext.tIn.vSpeed = v6;
    v10 = *((struct QTask_s **)pxContext + 1);
    igi2_frame.tCreateContext.tIn.ptWeaponType = v9;
    v11 = *(struct AmmoType_s **)(v5 + 48);
    igi2_frame.tCreateContext.tIn.ptIgnoreQTask = v10;
    v12 = *((float *)pxContext + 20);
    igi2_frame.tCreateContext.tIn.ptAmmoType = v11;
    v13 = *((float *)pxContext + 22);
    igi2_frame.tCreateContext.tIn.tParentSpeed.vY = *((float *)pxContext + 21);
    v14 = *(_DWORD *)(v4 + 656) == 0;
    igi2_frame.tCreateContext.tIn.pxProjectileParameters = (void *)v5;
    igi2_frame.tCreateContext.tIn.ptWeaponQTask = (struct QTask_s *)v4;
    igi2_frame.tCreateContext.tIn.tParentSpeed.vX = v12;
    igi2_frame.tCreateContext.tIn.tParentSpeed.vZ = v13;
    if ( v14 )
      igi2_frame.tCreateContext.tIn.nExplodeTime = (__int64)(*(float *)(v5 + 56) * 30.0);
    else
      igi2_frame.tCreateContext.tIn.nExplodeTime = *(_DWORD *)(v4 + 660);
    igi2_frame.pxContexta(0, &igi2_frame.tCreateContext);
    *(_DWORD *)(v4 + 656) = 0;
    *(_DWORD *)(v4 + 660) = 0;
    *((_DWORD *)pxContext + 28) = 1;
    *((_DWORD *)pxContext + 29) = (__int64)(60.0 / (double)*(int *)(v5 + 52) * 30.0);
  }
}

// source: j/0/weapons/projectilelauncher.c:545  [size]
unsigned __int16 __cdecl ProjectileLauncher_GetQTaskType()
{
  return ProjectileLauncher_eQTaskType;
}

// source: j/0/weapons/projectilelauncher.c:558  [anchor-hash]
void __cdecl ProjectileLauncher_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // edx

  v0 = QTask_NewQTaskType("ProjectileLauncher", 308, FireType_eQTaskType, 0, 0);
  ProjectileLauncher_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 0, ProjectileLauncher_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, ProjectileLauncher_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eUpdateInternalDataAfterLoadEvent,
    ProjectileLauncher_UpdaterInternalDataAfterLoadHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))ProjectileLauncher_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eUpdateInternalDataQTaskEvent,
    ProjectileLauncher_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    WeaponType_eCreateParametersQTaskEvent,
    ProjectileLauncher_CreateWeaponTypeParametersHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    WeaponType_eDeleteParametersQTaskEvent,
    ProjectileLauncher_DeleteWeaponTypeParametersHandler);
  QTask_LinkQTaskEventHandlerFn(v0, WeaponType_eGetAnimQTaskEvent, ProjectileLauncher_GetAnimHandler);
  QTask_LinkQTaskEventHandlerFn(v0, WeaponType_eGetAmmoInfoQTaskEvent, ProjectileLauncher_GetAmmoInfoHandler);
  QTask_LinkQTaskEventHandlerFn(v0, StatusScreen_eStatusDisplayQTaskEvent, ProjectileLauncher_StatusDisplayHandler);
  QTask_LinkQTaskEventHandlerFn(v0, Weapon_eFireQTaskEvent, ProjectileLauncher_WeaponFireHandler);
  QTask_LinkQTaskEventHandlerFn(v0, Weapon_eReleaseQTaskEvent, ProjectileLauncher_WeaponReleaseHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    TagItem_eUpdateTagItemQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))ProjectileLauncher_UpdateTagItemsHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  v1 = (struct ParameterList_s *)Mem_AllocFn(352, 4);
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  v2 = Level_eParameterTypebool8;
  v1->nParameters = 0;
  v1->nMaxParameters = 17;
  ProjectileLauncher_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0x28u, v2, "Create On Release", 7u, nullptr);
  ParameterList_AddParameter(
    ProjectileLauncher_ptParameterList,
    0x2Cu,
    ParameterEnumList_eParameterTypeInt32,
    "Ammo Type",
    7u,
    &AmmoType_tEnumList);
  ParameterList_AddParameter(
    ProjectileLauncher_ptParameterList,
    0x34u,
    Level_eParameterTypeInt32,
    "Rounds Per Minute",
    7u,
    nullptr);
  ParameterList_AddParameter(
    ProjectileLauncher_ptParameterList,
    0x3Cu,
    Level_eParameterTypeReal32,
    "Speed (m/s)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    ProjectileLauncher_ptParameterList,
    0x40u,
    Level_eParameterTypeReal32,
    "Effective Range (meters)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    ProjectileLauncher_ptParameterList,
    0x44u,
    Level_eParameterTypeReal32,
    "Max Hold Time (seconds)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    ProjectileLauncher_ptParameterList,
    0x38u,
    Level_eParameterTypeReal32,
    "Explode Time (seconds)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    ProjectileLauncher_ptParameterList,
    0x48u,
    Level_eParameterTypeString32,
    "1st Fire Anim",
    7u,
    nullptr);
  ParameterList_AddParameter(
    ProjectileLauncher_ptParameterList,
    0x68u,
    Level_eParameterTypeString32,
    "1st Fire Last Anim",
    7u,
    nullptr);
  ParameterList_AddParameter(
    ProjectileLauncher_ptParameterList,
    0x88u,
    Level_eParameterTypeString32,
    "3rd Fire Anim",
    7u,
    nullptr);
  ParameterList_AddParameter(
    ProjectileLauncher_ptParameterList,
    0xA8u,
    Level_eParameterTypeString32,
    "3rd Fire Last Anim",
    7u,
    nullptr);
  ParameterList_AddParameter(
    ProjectileLauncher_ptParameterList,
    0xC8u,
    Level_eParameterTypeString32,
    "Fire Sound",
    7u,
    nullptr);
  ParameterList_AddParameter(
    ProjectileLauncher_ptParameterList,
    0xE8u,
    Level_eParameterTypeString32,
    "Fire Hold Sound",
    7u,
    nullptr);
  ParameterList_AddParameter(
    ProjectileLauncher_ptParameterList,
    0x108u,
    Level_eParameterTypeString32,
    "Fire Release Sound",
    7u,
    nullptr);
  ParameterList_AddParameter(
    ProjectileLauncher_ptParameterList,
    0x128u,
    ParameterEnumList_eParameterTypeInt32,
    "Projectile QTaskType",
    7u,
    &WeaponType_tTaskTypeEnumList);
  Symbol_Register(
    "TASKTYPE_PROJECTILELAUNCHER",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)ProjectileLauncher_eQTaskType,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}

// source: j/0/weapons/projectilelauncher.c:696  [size]
void __cdecl ProjectileLauncher_Close()
{
  int v0; // esi

  if ( ProjectileLauncher_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&ProjectileLauncher_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(ProjectileLauncher_eQTaskType);
}
