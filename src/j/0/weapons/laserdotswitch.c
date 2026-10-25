/* j/0/weapons/laserdotswitch.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/weapons/laserdotswitch.c:52  [size]
void __cdecl LaserDotSwitch_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[1].ptNext = nullptr;
}

// source: j/0/weapons/laserdotswitch.c:69  [size]
void __cdecl LaserDotSwitch_DeleteHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: j/0/weapons/laserdotswitch.c:86  [size]
void __cdecl LaserDotSwitch_WeaponFireHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: j/0/weapons/laserdotswitch.c:106  [anchor-mhash]
void __cdecl LaserDotSwitch_WeaponReleaseHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_BYTE *)(*(_DWORD *)(*(_DWORD *)pxContext + 44) + 29) = *(_BYTE *)(*(_DWORD *)(*(_DWORD *)pxContext + 44) + 29) == 0;
}

// source: j/0/weapons/laserdotswitch.c:128  [size]
void __cdecl LaserDotSwitch_CreateWeaponTypeParametersHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *((_DWORD *)pxContext + 2) = QTask_NewFn(*((struct QTask_s **)pxContext + 1), LaserDotSwitch_eQTaskType, nullptr);
}

// source: j/0/weapons/laserdotswitch.c:151  [size]
unsigned __int16 __cdecl LaserDotSwitch_GetQTaskType()
{
  return LaserDotSwitch_eQTaskType;
}

// source: j/0/weapons/laserdotswitch.c:164  [anchor-hash]
void __cdecl LaserDotSwitch_Open()
{
  unsigned __int16 v0; // si
  __int16 v1; // si
  unsigned __int16 v2; // di

  v0 = QTask_NewQTaskType("LaserDotSwitch", 44, FireType_eQTaskType, 0, 0);
  LaserDotSwitch_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 0, (void (__cdecl *)(struct QTask_s *, void *))LaserDotSwitch_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Weapon_eFireQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))LaserDotSwitch_WeaponFireHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Weapon_eReleaseQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))LaserDotSwitch_WeaponReleaseHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    WeaponType_eCreateParametersQTaskEvent,
    LaserDotSwitch_CreateWeaponTypeParametersHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, (void (__cdecl *)(struct QTask_s *))LaserDotSwitch_DeleteHandler);
  Symbol_Register(
    "TASKTYPE_LASERDOTSWITCH",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)v0,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  v1 = Level_eAllowSaveQTaskEvent;
  v2 = LaserDotSwitch_eQTaskType;
  QTask_LinkQTaskEventHandlerFn(
    LaserDotSwitch_eQTaskType,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(
    v2,
    v1,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveNoChildrenHandler);
}

// source: j/0/weapons/laserdotswitch.c:193  [size]
void __cdecl LaserDotSwitch_Close()
{
  QTask_DeleteQTaskType(LaserDotSwitch_eQTaskType);
}
