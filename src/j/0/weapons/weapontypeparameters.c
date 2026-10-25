/* j/0/weapons/weapontypeparameters.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/weapons/weapontypeparameters.c:68  [size]
void __cdecl WeaponTypeParameters_DeleteWeaponTypeParametersHandler(struct QTask_s *ptQTask, void *pxContext)
{
  QTask_Delete(*(struct QTask_s **)pxContext);
}

// source: j/0/weapons/weapontypeparameters.c:88  [size]
unsigned __int16 __cdecl WeaponTypeParameters_GetQTaskType()
{
  return WeaponTypeParameters_eQTaskType;
}

// source: j/0/weapons/weapontypeparameters.c:101  [anchor-hash]
void __cdecl WeaponTypeParameters_Open()
{
  unsigned __int16 BaseQTaskType; // ax

  BaseQTaskType = QTask_GetBaseQTaskType();
  WeaponTypeParameters_eQTaskType = QTask_NewQTaskType("WeaponTypeParameters", 40, BaseQTaskType, 0, 0);
  QTask_LinkQTaskEventHandlerFn(
    WeaponTypeParameters_eQTaskType,
    WeaponType_eDeleteParametersQTaskEvent,
    WeaponTypeParameters_DeleteWeaponTypeParametersHandler);
}

// source: j/0/weapons/weapontypeparameters.c:118  [size]
void __cdecl WeaponTypeParameters_Close()
{
  QTask_DeleteQTaskType(WeaponTypeParameters_eQTaskType);
}
