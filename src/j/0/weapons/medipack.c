/* j/0/weapons/medipack.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/weapons/medipack.c:84  [size]
void __cdecl Medipack_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[1].ptNext = (struct QTask_s *)1008981770;
  ptQTask[1].ptPrev = (struct QTask_s *)1;
  ptQTask[1].tQTaskChildren.ptHead = (struct QTask_s *)-1;
  LOBYTE(ptQTask[1].tQTaskChildren.ptMiddle) = 0;
  LOBYTE(ptQTask[2].ptPrev) = 0;
  LOBYTE(ptQTask[2].eQTaskType) = 0;
  LOBYTE(ptQTask[3].tQTaskRefList.ptTail) = 0;
  LOBYTE(ptQTask[4].tQTaskRefList.ptHead) = 0;
  LOBYTE(ptQTask[5].tQTaskChildren.ptMiddle) = 0;
  LOBYTE(ptQTask[6].ptPrev) = 0;
  LOBYTE(ptQTask[6].eQTaskType) = 0;
  LOBYTE(ptQTask[7].tQTaskRefList.ptTail) = 0;
}

// source: j/0/weapons/medipack.c:111  [size]
void __cdecl Medipack_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = Medipack_ptParameterList;
}

// source: j/0/weapons/medipack.c:129  [size]
void __cdecl Medipack_CreateWeaponTypeParametersHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *((_DWORD *)pxContext + 2) = QTask_NewFn(*((struct QTask_s **)pxContext + 1), Medipack_eQTaskType, nullptr);
}

// source: j/0/weapons/medipack.c:148  [anchor-mhash]
void __cdecl Medipack_GetAnimHandler(struct QTask_s *ptQTask, void *pxContext)
{
  char *v2; // eax

  v2 = *((char **)pxContext + 5);
  switch ( *((_DWORD *)pxContext + 3) )
  {
    case 4:
      *((_DWORD *)pxContext + 6) = Hierarchy_GetAnim(*(unsigned __int8 **)pxContext, v2 + 52);
      break;
    case 5:
      *((_DWORD *)pxContext + 6) = Hierarchy_GetAnim(*(unsigned __int8 **)pxContext, v2 + 84);
      break;
    case 6:
      *((_DWORD *)pxContext + 6) = Hierarchy_GetAnim(*(unsigned __int8 **)pxContext, v2 + 116);
      break;
    case 0x11:
      *((_DWORD *)pxContext + 6) = Hierarchy_GetAnim(*(unsigned __int8 **)pxContext, v2 + 148);
      break;
    case 0x12:
      *((_DWORD *)pxContext + 6) = Hierarchy_GetAnim(*(unsigned __int8 **)pxContext, v2 + 180);
      break;
    case 0x13:
      *((_DWORD *)pxContext + 6) = Hierarchy_GetAnim(*(unsigned __int8 **)pxContext, v2 + 212);
      break;
    default:
      return;
  }
}

// source: j/0/weapons/medipack.c:204  [size]
void __cdecl Medipack_GetAmmoInfoHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // eax

  v2 = *(_DWORD *)pxContext;
  *((_DWORD *)pxContext + 2) = 1;
  *((_DWORD *)pxContext + 3) = 1;
  *((_DWORD *)pxContext + 4) = 1;
  *((_DWORD *)pxContext + 1) = AmmoType_GetAmmoTypeFromID(*(_DWORD *)(v2 + 48));
}

// source: j/0/weapons/medipack.c:229  [size]
void __cdecl Medipack_StatusDisplayHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zText[16]; };
    struct { char igi2_o1[16]; struct WeaponTypeGetFireTypeScreenPositionContext_s tPositionContext; };
    char igi2_extent[44];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // ebp
  struct AmmoType_s *AmmoTypeFromID; // eax
  struct AmmoTypeItem_s *AmmoTypeItemFromAmmoType; // eax
  float *v5; // edi
  float v6; // eax
  int v7; // ecx
  int v8; // esi
  __int16 *v9; // eax
  int v10; // eax
  void *pxContexta = *(void * *)&pxContext; // [esp+4Ch] [ebp+8h] ARGSLOT

  v2 = **((_DWORD **)pxContext + 1);
  AmmoTypeFromID = AmmoType_GetAmmoTypeFromID(*(_DWORD *)(*((_DWORD *)pxContext + 6) + 48));
  AmmoTypeItemFromAmmoType = Weapon_GetAmmoTypeItemFromAmmoType(
                               *(struct QTask_s **)pxContext,
                               AmmoTypeFromID->zAmmoTypeScriptID);
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
  v10 = *(_DWORD *)(v2 + 1136);
  QTilemap_Register(
    *(struct QTilemap_s **)v10,
    *(float *)(v10 + 4),
    *(float *)(v10 + 8),
    *(float *)(v10 + 20),
    *(float *)(v10 + 24),
    *(float *)(v10 + 28),
    *(float *)(v10 + 16),
    *(float *)(v10 + 12),
    *(_DWORD *)(v10 + 36) | 0x40000000,
    *(_DWORD *)(v10 + 32));
}

// source: j/0/weapons/medipack.c:285  [anchor-mhash]
void __cdecl Medipack_WeaponFireHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // ebx
  int v3; // esi
  int v4; // edi
  double v5; // st7

  v2 = *((_DWORD *)pxContext + 25);
  v3 = *((_DWORD *)pxContext + 1);
  v4 = 0;
  if ( v3 && QTask_IsQTaskTypeDerived(*(_WORD *)(v3 + 36), Human_eQTaskType) && *(float *)(v3 + 1020) != 0.0 )
  {
    v5 = *(float *)(v3 + 1020) - *(float *)(v2 + 40) * *(float *)(v3 + 1024);
    *(float *)(v3 + 1020) = v5;
    if ( v5 >= 0.0 )
    {
      if ( v5 > *(float *)(v3 + 1024) )
        *(_DWORD *)(v3 + 1020) = *(_DWORD *)(v3 + 1024);
    }
    else
    {
      *(_DWORD *)(v3 + 1020) = 0;
    }
    v4 = 1;
  }
  *((_DWORD *)pxContext + 28) = v4;
  *((_DWORD *)pxContext + 29) = (__int64)(60.0 / (double)*(int *)(v2 + 44) * 30.0);
  if ( v4 <= 0 )
  {
    *((_DWORD *)pxContext + 32) = 0;
    *((_DWORD *)pxContext + 33) = 0;
    *((_DWORD *)pxContext + 30) = 0;
  }
  else
  {
    *((_DWORD *)pxContext + 32) = 1008981770;
    *((_DWORD *)pxContext + 33) = 1008981770;
    *((_DWORD *)pxContext + 30) = 1036831949;
  }
}

// source: j/0/weapons/medipack.c:349  [size]
void __cdecl MediPack_WeaponReleaseHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: j/0/weapons/medipack.c:365  [anchor-hash]
void __cdecl Medipack_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // edx

  v0 = QTask_NewQTaskType("Medipack", 340, FireType_eQTaskType, 0, 0);
  Medipack_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, (void (__cdecl *)(struct QTask_s *, void *))Medipack_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Medipack_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, WeaponType_eCreateParametersQTaskEvent, Medipack_CreateWeaponTypeParametersHandler);
  QTask_LinkQTaskEventHandlerFn(v0, WeaponType_eGetAnimQTaskEvent, Medipack_GetAnimHandler);
  QTask_LinkQTaskEventHandlerFn(v0, WeaponType_eGetAmmoInfoQTaskEvent, Medipack_GetAmmoInfoHandler);
  QTask_LinkQTaskEventHandlerFn(v0, StatusScreen_eStatusDisplayQTaskEvent, Medipack_StatusDisplayHandler);
  QTask_LinkQTaskEventHandlerFn(v0, Weapon_eFireQTaskEvent, Medipack_WeaponFireHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Weapon_eReleaseQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))MediPack_WeaponReleaseHandler);
  v1 = (struct ParameterList_s *)Mem_AllocFn(252, 4);
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  v2 = Level_eParameterTypeReal32;
  v1->nParameters = 0;
  v1->nMaxParameters = 12;
  Medipack_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0x28u, v2, "Factor of human max damage to add for each round", 7u, &unk_6B09D8);
  ParameterList_AddParameter(
    Medipack_ptParameterList,
    0x2Cu,
    Level_eParameterTypeInt32,
    "Rounds Per minute",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Medipack_ptParameterList,
    0x30u,
    ParameterEnumList_eParameterTypeInt32,
    "AmmoType",
    7u,
    &AmmoType_tEnumList);
  ParameterList_AddParameter(
    Medipack_ptParameterList,
    0x34u,
    Level_eParameterTypeString32,
    "1st Fire Anim",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Medipack_ptParameterList,
    0x54u,
    Level_eParameterTypeString32,
    "1st Fire Hold Anim",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Medipack_ptParameterList,
    0x74u,
    Level_eParameterTypeString32,
    "1st Fire Release Anim",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Medipack_ptParameterList,
    0x94u,
    Level_eParameterTypeString32,
    "3rd Fire Anim",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Medipack_ptParameterList,
    0xB4u,
    Level_eParameterTypeString32,
    "3rd Fire Hold Anim",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Medipack_ptParameterList,
    0xD4u,
    Level_eParameterTypeString32,
    "3rd Fire Release Anim",
    7u,
    nullptr);
  ParameterList_AddParameter(Medipack_ptParameterList, 0xF4u, Level_eParameterTypeString32, "Fire Sound", 7u, nullptr);
  ParameterList_AddParameter(Medipack_ptParameterList, 0x114u, Level_eParameterTypeString32, "Hold Sound", 7u, nullptr);
  ParameterList_AddParameter(
    Medipack_ptParameterList,
    0x134u,
    Level_eParameterTypeString32,
    "Release Sound",
    7u,
    nullptr);
  Symbol_Register(
    "TASKTYPE_MEDIPACK",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)Medipack_eQTaskType,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}

// source: j/0/weapons/medipack.c:489  [size]
void __cdecl Medipack_Close()
{
  int v0; // esi

  if ( Medipack_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&Medipack_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(Medipack_eQTaskType);
}

// source: j/0/weapons/medipack.c:506  [size]
unsigned __int16 __cdecl Medipack_GetQTaskType()
{
  return Medipack_eQTaskType;
}
