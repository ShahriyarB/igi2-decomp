/* j/0/weapons/thermosight.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/weapons/thermosight.c:53  [size]
void __cdecl ThermoSight_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ((void (__cdecl *)())QTask_aatQTaskFinalEvent[0][Zoom_eQTaskType].pfHandler)(ptQTask, pxContext);
}

// source: j/0/weapons/thermosight.c:72  [size]
void __cdecl ThermoSight_DeleteHandler(struct QTask_s *ptQTask)
{
  ((void (__cdecl *)())QTask_aatQTaskFinalEvent[2][Zoom_eQTaskType].pfHandler)(ptQTask);
}

// source: j/0/weapons/thermosight.c:90  [size]
void __cdecl ThermoSight_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = ThermoSight_ptParameterList;
}

// source: j/0/weapons/thermosight.c:111  [size]
void __cdecl ThermoSight_CreateWeaponTypeParametersHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *((_DWORD *)pxContext + 2) = QTask_NewFn(*((struct QTask_s **)pxContext + 1), ThermoSight_eQTaskType, nullptr);
}

// source: j/0/weapons/thermosight.c:130  [anchor-mhash]
void __cdecl ThermoSight_WeaponFireHandler(struct QTask_s *ptQTask, void *pxContext)
{
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // eax
  int v3; // eax

  pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[Weapon_eFireQTaskEvent][Zoom_eQTaskType].pfHandler;
  if ( pfHandler )
    pfHandler(ptQTask, pxContext);
  v3 = *(_DWORD *)pxContext;
  if ( *(_DWORD *)(*(_DWORD *)pxContext + 160) )
  {
    isInfraEnabled = 1;
    *(_DWORD *)(v3 + 208) = 1;
  }
  else
  {
    isInfraEnabled = 0;
    *(_DWORD *)(v3 + 208) = 0;
  }
}

// source: j/0/weapons/thermosight.c:163  [anchor-mhash]
void __cdecl ThermoSight_WeaponDeactivateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v2; // ecx
  int v3; // edi
  enum WeaponOverlayStatus_e v4; // [esp+0h] [ebp-Ch]

  v2 = (struct QTask_s *)(Zoom_eQTaskType + 511 * Weapon_eReleaseQTaskEvent);
  if ( QTask_aatQTaskFinalEvent[0][(_DWORD)v2].pfHandler )
    ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[Weapon_eDeActivateQTaskEvent][Zoom_eQTaskType].pfHandler)(
      ptQTask,
      pxContext);
  v3 = *(_DWORD *)pxContext;
  isInfraEnabled = 0;
  Weapon_SetOverlayStatus(v2, v4, 0, v3);
}

// source: j/0/weapons/thermosight.c:189  [size]
unsigned __int16 __cdecl ThermoSight_GetQTaskType()
{
  return ThermoSight_eQTaskType;
}

// source: j/0/weapons/thermosight.c:202  [anchor-hash]
void __cdecl ThermoSight_Open()
{
  unsigned __int16 v0; // si
  __int16 v1; // di
  __int16 v2; // si
  unsigned __int16 v3; // di
  int nMaxParameters; // [esp+Ch] [ebp-4h] BYREF

  v0 = QTask_NewQTaskType("ThermoSight", 120, Zoom_eQTaskType, 0, 0);
  ThermoSight_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 0, (void (__cdecl *)(struct QTask_s *, void *))ThermoSight_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    WeaponType_eCreateParametersQTaskEvent,
    ThermoSight_CreateWeaponTypeParametersHandler);
  v1 = ParameterList_eGetParameterListQTaskEvent;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))ThermoSight_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, Weapon_eFireQTaskEvent, ThermoSight_WeaponFireHandler);
  QTask_LinkQTaskEventHandlerFn(v0, Weapon_eDeActivateQTaskEvent, ThermoSight_WeaponDeactivateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, (void (__cdecl *)(struct QTask_s *))ThermoSight_DeleteHandler);
  nMaxParameters = 0;
  ((void (__cdecl *)(_DWORD, int *))QTask_aatQTaskFinalEvent[v1][Zoom_eQTaskType].pfHandler)(0, &nMaxParameters);
  ThermoSight_ptParameterList = ParameterList_Derive((struct ParameterList_s *)nMaxParameters, 0);
  Symbol_Register(
    "TASKTYPE_THERMOSIGHT",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)ThermoSight_eQTaskType,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  v2 = Level_eAllowSaveQTaskEvent;
  v3 = ThermoSight_eQTaskType;
  QTask_LinkQTaskEventHandlerFn(
    ThermoSight_eQTaskType,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(
    v3,
    v2,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveNoChildrenHandler);
}

// source: j/0/weapons/thermosight.c:233  [anchor-hash]
void __cdecl ThermoSight_Close()
{
  int v0; // esi

  if ( ThermoSight_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&ThermoSight_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  ThermoSight_ptParameterList = nullptr;
  QTask_DeleteQTaskType(ThermoSight_eQTaskType);
}
