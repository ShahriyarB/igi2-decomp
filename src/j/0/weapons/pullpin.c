/* j/0/weapons/pullpin.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/weapons/pullpin.c:58  [size]
void __cdecl PullPin_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  LOBYTE(ptQTask[1].ptNext) = 0;
  LOBYTE(ptQTask[1].ptParent) = 0;
  ptQTask[2].tQTaskRefList.ptMiddle = (struct QReference_s *)1082130432;
}

// source: j/0/weapons/pullpin.c:76  [size]
void __cdecl PullPin_DeleteHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: j/0/weapons/pullpin.c:91  [size]
void __cdecl PullPin_RunHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: j/0/weapons/pullpin.c:106  [size]
void __cdecl PullPin_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: j/0/weapons/pullpin.c:124  [size]
void __cdecl PullPin_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = PullPin_ptParameterList;
}

// source: j/0/weapons/pullpin.c:140  [size]
void __cdecl PullPin_CreateWeaponTypeParametersHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *((_DWORD *)pxContext + 2) = QTask_NewFn(*((struct QTask_s **)pxContext + 1), PullPin_eQTaskType, nullptr);
}

// source: j/0/weapons/pullpin.c:159  [size]
void __cdecl PullPin_GetAnimHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // ecx
  int v3; // eax
  int v4; // edi
  struct QHashTable_s *v5; // esi
  unsigned int v6; // eax
  int v7; // eax
  int v8; // esi
  int v9; // eax

  v2 = *((_DWORD *)pxContext + 3);
  v3 = *((_DWORD *)pxContext + 5);
  if ( v2 == 4 )
  {
    v4 = v3 + 40;
    v5 = Hierarchy_ptHashTable;
    v6 = Hierarchy_ptHashTable->tPrivate.pfHashFunction(
           Hierarchy_ptHashTable->tPrivate.nHashTableSize,
           *(void **)pxContext);
    v7 = ((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Hierarchy_ptHashTable->tPrivate.pfFindElement)(v5, v6, (const void *)(*(void **)pxContext));
    v8 = *(_DWORD *)v7;
    v9 = (*(int (__cdecl **)(_DWORD, int))(*(_DWORD *)v7 + 12))(*(_DWORD *)(*(_DWORD *)v7 + 4), v4);
    *((_DWORD *)pxContext + 6) = (*(int (__cdecl **)(int, int, const void *))(v8 + 28))(v8, v9, (const void *)(v4));
  }
  else if ( v2 == 17 )
  {
    *((_DWORD *)pxContext + 6) = Hierarchy_GetAnim(*(unsigned __int8 **)pxContext, (char *)(v3 + 72));
  }
}

// source: j/0/weapons/pullpin.c:195  [size]
void __cdecl PullPin_GetAmmoInfoHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *((_DWORD *)pxContext + 2) = 0;
  *((_DWORD *)pxContext + 3) = 0;
  *((_DWORD *)pxContext + 4) = 1;
  *((_DWORD *)pxContext + 1) = 0;
}

// source: j/0/weapons/pullpin.c:216  [anchor-mhash]
void __cdecl PullPin_WeaponFireHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // ecx
  int v3; // edx

  v2 = *(_DWORD *)pxContext;
  v3 = *((_DWORD *)pxContext + 25);
  *(_DWORD *)(v2 + 656) = 1;
  *(_DWORD *)(v2 + 660) = (__int64)(*(float *)(v3 + 104) * 30.0);
  *((_DWORD *)pxContext + 28) = 0;
  *((_DWORD *)pxContext + 29) = 0;
  *((_DWORD *)pxContext + 32) = 1008981770;
  *((_DWORD *)pxContext + 33) = 1008981770;
  *((_DWORD *)pxContext + 30) = 1036831949;
}

// source: j/0/weapons/pullpin.c:254  [size]
unsigned __int16 __cdecl PullPin_GetQTaskType()
{
  return PullPin_eQTaskType;
}

// source: j/0/weapons/pullpin.c:267  [anchor-hash]
void __cdecl PullPin_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // edx

  v0 = QTask_NewQTaskType("PullPin", 108, FireType_eQTaskType, 0, 0);
  PullPin_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 0, (void (__cdecl *)(struct QTask_s *, void *))PullPin_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, (void (__cdecl *)(struct QTask_s *))PullPin_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, (void (__cdecl *)(struct QTask_s *))PullPin_RunHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eUpdateInternalDataQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))PullPin_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))PullPin_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, WeaponType_eCreateParametersQTaskEvent, PullPin_CreateWeaponTypeParametersHandler);
  QTask_LinkQTaskEventHandlerFn(v0, WeaponType_eGetAnimQTaskEvent, PullPin_GetAnimHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    WeaponType_eGetAmmoInfoQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))PullPin_GetAmmoInfoHandler);
  QTask_LinkQTaskEventHandlerFn(v0, Weapon_eFireQTaskEvent, PullPin_WeaponFireHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  v1 = (struct ParameterList_s *)Mem_AllocFn(72, 4);
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  v2 = Level_eParameterTypeString32;
  v1->nParameters = 0;
  v1->nMaxParameters = 3;
  PullPin_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0x28u, v2, "1st Fire Anim", 7u, nullptr);
  ParameterList_AddParameter(PullPin_ptParameterList, 0x48u, Level_eParameterTypeString32, "3rd Fire Anim", 7u, nullptr);
  ParameterList_AddParameter(
    PullPin_ptParameterList,
    0x68u,
    Level_eParameterTypeReal32,
    "Explode Time (seconds)",
    7u,
    nullptr);
  Symbol_Register(
    "TASKTYPE_PULLPIN",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)PullPin_eQTaskType,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}

// source: j/0/weapons/pullpin.c:305  [size]
void __cdecl PullPin_Close()
{
  int v0; // esi

  if ( PullPin_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&PullPin_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(PullPin_eQTaskType);
}
