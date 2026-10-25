/* j/0/objects/building.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/objects/building.c:64  [anchor-mhash]
void __cdecl Building_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  __int16 v2; // cx
  struct real64x3_t tNull; // [esp+10h] [ebp-18h] BYREF

  memset(&tNull, 0, sizeof(tNull));
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][SectorObject_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  World_RegisterDynCubeObjFirstTimeRadius(
    Game_ptGame->ptWorld,
    (struct DynCubeObj_s *)ptQTask,
    &tNull,
    1.0,
    WORLD_DYNCUBETREE_CATEGORY_SECTOROBJECTS);
  v2 = Attach_eAttachEvent;
  ptQTask[5].tQTaskChildren.ptTail = (struct QTask_s *)-1;
  ptQTask[5].tQTaskRefList.ptHead = nullptr;
  QTask_TriggerQTaskEventParent(ptQTask, v2, &ptQTask[5].tQTaskChildren.ptTail);
  ModelObj_CalcRelativePosAndOrientation((struct ModelObj_s *)ptQTask);
  LOBYTE(ptQTask[13].ptNext) = 0;
  ptQTask[12].ptPrev = nullptr;
  ptQTask[12].tQTaskChildren.ptHead = nullptr;
  ptQTask[12].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[12].tQTaskRefList.ptHead = nullptr;
  ptQTask[12].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[12].tQTaskRefList.ptTail = nullptr;
  *(_DWORD *)&ptQTask[12].eQTaskType = 0;
  ptQTask[13].tQTaskChildren.ptTail = nullptr;
  ptQTask[13].tQTaskRefList.ptHead = nullptr;
  ptQTask[13].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[13].tQTaskRefList.ptTail = nullptr;
  ptQTask[13].ptParent = nullptr;
  *(_DWORD *)&ptQTask[13].eQTaskType = 0;
  ptQTask[12].ptNext = (struct QTask_s *)1065353216;
  ptQTask[12].tQTaskChildren.ptTail = (struct QTask_s *)1065353216;
  ptQTask[12].ptParent = (struct QTask_s *)1065353216;
}

// source: j/0/objects/building.c:102  [size]
void __cdecl Building_DeleteHandler(struct QTask_s *ptQTask)
{
  World_RemoveDynCubeObj((struct World_s *)ptQTask[2].ptParent, (struct DynCubeObj_s *)ptQTask);
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[2][SectorObject_eQTaskType].pfHandler)(ptQTask);
}

// source: j/0/objects/building.c:122  [size]
void __cdecl Building_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = Building_ptParameterList;
}

// source: j/0/objects/building.c:138  [anchor-mhash]
void __cdecl Building_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct LODVirModel_s *LODVirModelExistsFn; // eax
  double v3; // st7
  double v4; // st7
  int *v5; // eax
  int v6; // eax
  double v7; // st6
  __int16 v8; // cx
  float ptDynCubeObj; // [esp+0h] [ebp-10h]

  LODVirModelExistsFn = MTP_GetLODVirModelExistsFn((char *)&ptQTask[13]);
  SectorObject_SetModel((struct SectorObject_s *)ptQTask, LODVirModelExistsFn);
  if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
    v3 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  else
    v3 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  if ( v3 >= *(float *)&ptQTask[6].ptPrev )
  {
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
      v4 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v4 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  }
  else
  {
    v4 = *(float *)&ptQTask[6].ptPrev;
  }
  v5 = *(int **)&ptQTask[2].eQTaskType;
  if ( v5 && (v6 = *v5) != 0 )
    v7 = *(float *)(*(_DWORD *)(*(_DWORD *)(v6 + 12) + 12) + 120);
  else
    v7 = 1.0;
  ptDynCubeObj = v4 * v7;
  World_MoveDynCubeObjRadius(
    Game_ptGame->ptWorld,
    (struct DynCubeObj_s *)ptQTask,
    (struct real64x3_t *)&ptQTask[13].tQTaskChildren.ptTail,
    ptDynCubeObj);
  qmemcpy(&ptQTask[3].ptPrev, &ptQTask[12], sizeof(struct QTask_s));
  v8 = Attach_eAttachEvent;
  ptQTask[5].tQTaskChildren.ptTail = (struct QTask_s *)-1;
  ptQTask[5].tQTaskRefList.ptHead = nullptr;
  QTask_TriggerQTaskEventParent(ptQTask, v8, &ptQTask[5].tQTaskChildren.ptTail);
  ModelObj_CalcRelativePosAndOrientation((struct ModelObj_s *)ptQTask);
  SectorObject_UpdateAttachObjects((struct SectorObject_s *)ptQTask);
}

// source: j/0/objects/building.c:187  [anchor-mhash]
void __cdecl Building_UpdateInternalDataAfterLoadHandler(struct QTask_s *ptQTask)
{
  sub_5C5600(
    *(_DWORD *)&ptQTask[2].eQTaskType,
    (int *)&ptQTask[10].ptParent,
    (int)&ptQTask[1],
    (float *)&ptQTask[3].ptPrev);
}

// source: j/0/objects/building.c:233  [size]
void __cdecl Building_UpdateAttachmentHandler(struct QTask_s *ptQTask)
{
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Attach_eUpdateAttachmentEvent][SectorObject_eQTaskType].pfHandler)(ptQTask);
  qmemcpy(&ptQTask[12], &ptQTask[3].ptPrev, sizeof(struct QTask_s));
  qmemcpy(&ptQTask[13].tQTaskChildren.ptTail, &ptQTask[1], 0x18u);
}

// source: j/0/objects/building.c:288  [anchor-mhash]
void __cdecl Building_RegisterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  double v2; // st7
  double v3; // st7
  int *v4; // eax
  int v5; // eax
  double v6; // st6
  struct QTask_s *ptHead; // eax
  int v8; // edx
  struct QTask_s *v9; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // ecx
  int v11; // edx
  float ptDynCubeObj; // [esp+0h] [ebp-14h]

  if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
    v2 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  else
    v2 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  if ( v2 >= *(float *)&ptQTask[6].ptPrev )
  {
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
      v3 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v3 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  }
  else
  {
    v3 = *(float *)&ptQTask[6].ptPrev;
  }
  v4 = *(int **)&ptQTask[2].eQTaskType;
  if ( v4 && (v5 = *v4) != 0 )
    v6 = *(float *)(*(_DWORD *)(*(_DWORD *)(v5 + 12) + 12) + 120);
  else
    v6 = 1.0;
  ptDynCubeObj = v3 * v6;
  World_RegisterDynCubeObjFirstTimeRadius(
    *((struct World_s **)pxContext + 1),
    (struct DynCubeObj_s *)ptQTask,
    (struct real64x3_t *)&ptQTask[13].tQTaskChildren.ptTail,
    ptDynCubeObj,
    WORLD_DYNCUBETREE_CATEGORY_SECTOROBJECTS);
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRegisterQTaskEvent][SectorObject_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v8 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v9 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v9 = nullptr;
      QTask_atProtectedQTaskStack[v8].ptQTask = v9;
      pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRegisterQTaskEvent][ptHead->eQTaskType].pfHandler;
      v11 = v8 + 1;
      QTask_nProtectedQTaskStackOffset = v11;
      if ( pfHandler )
      {
        pfHandler(ptHead, pxContext);
        v11 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v11];
      v8 = v11 - 1;
      QTask_nProtectedQTaskStackOffset = v8;
    }
    while ( ptHead );
  }
}

// source: j/0/objects/building.c:325  [anchor-mhash]
void __cdecl Building_RemoveHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptHead; // eax
  int v3; // edx
  struct QTask_s *v4; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // ecx
  int v6; // edx

  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v3 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v4 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v4 = nullptr;
      QTask_atProtectedQTaskStack[v3].ptQTask = v4;
      pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRemoveQTaskEvent][ptHead->eQTaskType].pfHandler;
      v6 = v3 + 1;
      QTask_nProtectedQTaskStackOffset = v6;
      if ( pfHandler )
      {
        pfHandler(ptHead, pxContext);
        v6 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v6];
      v3 = v6 - 1;
      QTask_nProtectedQTaskStackOffset = v3;
    }
    while ( ptHead );
  }
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRemoveQTaskEvent][SectorObject_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  World_RemoveDynCubeObj(*(struct World_s **)pxContext, (struct DynCubeObj_s *)ptQTask);
}

// source: j/0/objects/building.c:362  [anchor-strings]
void __cdecl Building_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // edx

  v0 = QTask_NewQTaskType("Building", 560, SectorObject_eQTaskType, 0, 0);
  Building_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, Building_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, Building_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Building_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, Building_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eUpdateInternalDataAfterLoadEvent,
    Building_UpdateInternalDataAfterLoadHandler);
  QTask_LinkQTaskEventHandlerFn(v0, GameFunctions_eGetNextZEvaluateQTaskEvent, GameFunctions_GetNextZEvaluateHandler);
  QTask_LinkQTaskEventHandlerFn(v0, DynCubeObj_eDynCubeObjRemoveQTaskEvent, Building_RemoveHandler);
  QTask_LinkQTaskEventHandlerFn(v0, DynCubeObj_eDynCubeObjRegisterQTaskEvent, Building_RegisterHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Attach_eUpdateAttachmentEvent, Building_UpdateAttachmentHandler);
  v1 = (struct ParameterList_s *)Mem_AllocFn(92, 4);
  v2 = Level_eParameterTypeObjectPos;
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  v1->nParameters = 0;
  v1->nMaxParameters = 4;
  Building_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0x218u, v2, "Position", 7u, nullptr);
  ParameterList_AddParameter(Building_ptParameterList, 0x1E0u, Level_eParameterTypeReal32x9, "Orientation", 7u, nullptr);
  ParameterList_AddParameter(Building_ptParameterList, 0x208u, Level_eParameterTypeString16, "Model", 7u, nullptr);
  ParameterList_AddParameter(Building_ptParameterList, 0x194u, Level_eParameterTypeRGB, "Inside ambient", 1u, nullptr);
  Symbol_Register(
    "TASKTYPE_BUILDING",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)Building_eQTaskType,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}

// source: j/0/objects/building.c:405  [size]
void __cdecl Building_Close()
{
  int v0; // esi

  if ( Building_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&Building_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(Building_eQTaskType);
}
