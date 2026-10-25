/* j/0/computer/definecomputerlimit.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/computer/definecomputerlimit.c:61  [size]
void __cdecl DefineComputerLimit_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  DefineComputerLimit_ptQTask = ptQTask;
}

// source: j/0/computer/definecomputerlimit.c:78  [size]
void __cdecl DefineComputerLimit_DeleteHandler(struct QTask_s *ptQTask)
{
  DefineComputerLimit_ptQTask = nullptr;
}

// source: j/0/computer/definecomputerlimit.c:95  [size]
void __cdecl DefineComputerLimit_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = DefineComputerLimit_ptParameterList;
}

// source: j/0/computer/definecomputerlimit.c:111  [size]
void __cdecl DefineComputerLimit_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: j/0/computer/definecomputerlimit.c:127  [anchor-hash]
void __cdecl DefineComputerLimit_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si
  struct ParameterList_s *v2; // eax
  int v3; // edx

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("DefineComputerLimit", 72, BaseQTaskType, 0, 0);
  DefineComputerLimit_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(
    v1,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 0, (void (__cdecl *)(struct QTask_s *, void *))DefineComputerLimit_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, (void (__cdecl *)(struct QTask_s *))DefineComputerLimit_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))DefineComputerLimit_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eUpdateInternalDataQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))DefineComputerLimit_UpdateInternalDataHandler);
  v2 = (struct ParameterList_s *)Mem_AllocFn(52, 4);
  v3 = Level_eParameterTypeObjectPos;
  v2->ptParameterListItem = (struct ParameterListItem_s *)&v2[1];
  v2->nParameters = 0;
  v2->nMaxParameters = 2;
  DefineComputerLimit_ptParameterList = v2;
  ParameterList_AddParameter(v2, 0x28u, v3, "Position", 7u, nullptr);
  ParameterList_AddParameter(
    DefineComputerLimit_ptParameterList,
    0x40u,
    Level_eParameterTypeReal32,
    "Quadrant Size (m)",
    7u,
    nullptr);
}

// source: j/0/computer/definecomputerlimit.c:158  [size]
void __cdecl DefineComputerLimit_Close()
{
  int v0; // esi

  QTask_DeleteQTaskType(DefineComputerLimit_eQTaskType);
  if ( DefineComputerLimit_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&DefineComputerLimit_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
}

// source: j/0/computer/definecomputerlimit.c:175  [anchor-hash]
struct ComputerLimit_t *__cdecl DefineComputerLimit_GetLimit()
{
  if ( DefineComputerLimit_ptQTask )
    return (struct ComputerLimit_t *)&DefineComputerLimit_ptQTask[1];
  else
    return nullptr;
}
