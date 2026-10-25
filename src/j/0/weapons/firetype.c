/* j/0/weapons/firetype.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/weapons/firetype.c:37  [size]
void __cdecl FireType_GetAmmoInfoHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *((_DWORD *)pxContext + 2) = 0;
  *((_DWORD *)pxContext + 3) = 0;
  *((_DWORD *)pxContext + 4) = 1;
  *((_DWORD *)pxContext + 1) = 0;
}

// source: j/0/weapons/firetype.c:58  [anchor-mhash]
void __cdecl FireType_FindChildrenHandler(struct QTask_s *ptQTask)
{
  struct QTask_s **v1; // esi
  struct QTask_s *eQTaskType; // ecx

  v1 = &ptQTask->ptParent->ptParent->ptNext + 5 * ((int)&ptQTask->ptParent[1].ptNext[1].tQTaskRefList.ptMiddle + 1);
  eQTaskType = (struct QTask_s *)ptQTask->eQTaskType;
  *v1 = eQTaskType;
  v1[1] = eQTaskType;
  v1[3] = (struct QTask_s *)QTask_NewQTaskRef(ptQTask);
}

// source: j/0/weapons/firetype.c:73  [size]
unsigned __int16 __cdecl FireType_GetQTaskType()
{
  return FireType_eQTaskType;
}

// source: j/0/weapons/firetype.c:86  [anchor-hash]
void __cdecl FireType_Open()
{
  unsigned __int16 v0; // si

  v0 = QTask_NewQTaskType("FireType", 40, WeaponTypeParameters_eQTaskType, 0, 0);
  FireType_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    WeaponType_eGetAmmoInfoQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))FireType_GetAmmoInfoHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, WeaponType_eFindChildrenQTaskEvent, FireType_FindChildrenHandler);
}

// source: j/0/weapons/firetype.c:102  [size]
void __cdecl FireType_Close()
{
  QTask_DeleteQTaskType(FireType_eQTaskType);
}
