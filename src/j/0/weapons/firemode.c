/* j/0/weapons/firemode.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/weapons/firemode.c:49  [size]
void __cdecl FireMode_CreateWeaponTypeParametersHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *((_DWORD *)pxContext + 2) = QTask_NewFn(*((struct QTask_s **)pxContext + 1), FireMode_eQTaskType, nullptr);
}

// source: j/0/weapons/firemode.c:69  [anchor-mhash]
void __cdecl FireMode_WeaponFireHandler(struct QTask_s *ptQTask, void *pxContext)
{
  BOOL v2; // ecx
  int v3; // edx
  int v4; // eax
  int v5; // eax

  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
    v2 = *((_DWORD *)pxContext + 23) == 0;
  else
    v2 = *(_DWORD *)(*(_DWORD *)pxContext + 56) == 0;
  if ( v2 )
  {
    v3 = *((_DWORD *)pxContext + 26);
    v4 = *(_DWORD *)pxContext;
    ++*(_DWORD *)(*(_DWORD *)(v4 + 44) + 24);
    v5 = *(_DWORD *)(v4 + 44);
    if ( (int)(*(_DWORD *)(v5 + 24)) >= (int)(*(_DWORD *)(v3 + 832)) )
      *(_DWORD *)(v5 + 24) = 0;
  }
}

// source: j/0/weapons/firemode.c:118  [size]
unsigned __int16 __cdecl FireMode_GetQTaskType()
{
  return FireMode_eQTaskType;
}

// source: j/0/weapons/firemode.c:131  [anchor-hash]
void __cdecl FireMode_Open()
{
  unsigned __int16 v0; // si

  v0 = QTask_NewQTaskType("FireMode", 40, FireType_eQTaskType, 0, 0);
  FireMode_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, WeaponType_eCreateParametersQTaskEvent, FireMode_CreateWeaponTypeParametersHandler);
  QTask_LinkQTaskEventHandlerFn(v0, Weapon_eFireQTaskEvent, FireMode_WeaponFireHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  Symbol_Register(
    "TASKTYPE_FIREMODE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)v0,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}

// source: j/0/weapons/firemode.c:153  [size]
void __cdecl FireMode_Close()
{
  QTask_DeleteQTaskType(FireMode_eQTaskType);
}
