/* j/0/pickups/addammo.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/pickups/addammo.c:64  [size]
void __cdecl AddAmmo_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[1].ptNext = nullptr;
  LOBYTE(ptQTask[1].ptPrev) = 0;
  ptQTask[1].eQTaskType = 0;
}

// source: j/0/pickups/addammo.c:85  [anchor-mhash]
void __cdecl AddAmmo_RunHandler(struct QTask_s *ptQTask)
{
  if ( QTask_IsQTaskTypeDerived(ptQTask->ptParent->eQTaskType, Human_eQTaskType) )
    AmmoType_GetAmmoTypeFromID((int)ptQTask[1].ptNext);
  QTask_Delete(ptQTask);
}

// source: j/0/pickups/addammo.c:124  [size]
void __cdecl AddAmmo_DeleteHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: j/0/pickups/addammo.c:138  [size]
void __cdecl AddAmmo_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = AddAmmo_ptParameterList;
}

// source: j/0/pickups/addammo.c:154  [size]
void __cdecl AddAmmo_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[1].ptNext = (struct QTask_s *)Script_ParseLineInt32((char *)&ptQTask[1].ptPrev);
}

// source: j/0/pickups/addammo.c:179  [anchor-hash]
void __cdecl AddAmmo_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si
  struct ParameterList_s *v2; // eax
  int v3; // edx

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("AddAmmo", 80, BaseQTaskType, 0, 0);
  AddAmmo_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(
    v1,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveNoChildrenHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 0, (void (__cdecl *)(struct QTask_s *, void *))AddAmmo_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, AddAmmo_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, (void (__cdecl *)(struct QTask_s *))AddAmmo_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))AddAmmo_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v1, ParameterList_eUpdateInternalDataQTaskEvent, AddAmmo_UpdateInternalDataHandler);
  v2 = (struct ParameterList_s *)Mem_AllocFn(52, 4);
  v2->ptParameterListItem = (struct ParameterListItem_s *)&v2[1];
  v3 = ParameterEnumList_eParameterTypeString32;
  v2->nParameters = 0;
  v2->nMaxParameters = 2;
  AddAmmo_ptParameterList = v2;
  ParameterList_AddParameter(v2, 0x2Cu, v3, "ID", 7u, &AmmoType_tEnumList);
  ParameterList_AddParameter(
    AddAmmo_ptParameterList,
    0x4Cu,
    Level_eParameterTypeInt16,
    (char *)&g_zMessage.anDR[24],
    7u,
    nullptr);
}

// source: j/0/pickups/addammo.c:209  [size]
void __cdecl AddAmmo_Close()
{
  int v0; // esi

  if ( AddAmmo_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&AddAmmo_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(AddAmmo_eQTaskType);
}
