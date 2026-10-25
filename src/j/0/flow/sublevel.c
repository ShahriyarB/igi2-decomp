/* j/0/flow/sublevel.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/flow/sublevel.c:59  [size]
void __cdecl SubLevel_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  LOBYTE(ptQTask[1].ptNext) = 0;
}

// source: j/0/flow/sublevel.c:76  [size]
void __cdecl SubLevel_RunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // ecx
  int v2; // edx
  struct QTask_s *v3; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v5; // edx

  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v2 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v3 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v3 = nullptr;
      QTask_atProtectedQTaskStack[v2].ptQTask = v3;
      pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][ptHead->eQTaskType].pfHandler;
      v5 = v2 + 1;
      QTask_nProtectedQTaskStackOffset = v5;
      if ( pfHandler )
      {
        pfHandler(ptHead);
        v5 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v5];
      v2 = v5 - 1;
      QTask_nProtectedQTaskStackOffset = v2;
    }
    while ( ptHead );
  }
}

// source: j/0/flow/sublevel.c:90  [size]
void __cdecl SubLevel_MagicObjEnterHandler(struct QTask_s *ptQTask, void *pxContext)
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
      pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[MagicObj_eMagicObjEnterEvent][ptHead->eQTaskType].pfHandler;
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
}

// source: j/0/flow/sublevel.c:127  [size]
void __cdecl SubLevel_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = SubLevel_ptParameterList;
}

// source: j/0/flow/sublevel.c:143  [anchor-mhash]
void __cdecl SubLevel_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct File_s *v2; // eax
  struct Script_s *v3; // esi

  QTask_DeleteChildren(ptQTask);
  if ( LOBYTE(ptQTask[1].ptNext) )
  {
    v2 = File_New((char *)&ptQTask[1], "r");
    if ( v2 )
    {
      if ( v2 == &File_tDummyAsyncFile )
        File_tDummyAsyncFile.isAsync = false;
      else
        File_atDevice[v2->eDeviceID].pfDelete(v2->eDeviceID, v2);
      v3 = Script_New((char *)&ptQTask[1]);
      if ( v3 )
      {
        Script_SetSymbolContext("Task_New", ptQTask);
        Script_Execute(v3);
        Script_Delete(v3);
      }
    }
  }
}

// source: j/0/flow/sublevel.c:196  [anchor-hash]
void __cdecl SubLevel_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si
  struct ParameterList_s *v2; // eax
  int v3; // edx

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("SubLevel", 296, BaseQTaskType, 0, 0);
  SubLevel_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(
    v1,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveNoChildrenHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 0, (void (__cdecl *)(struct QTask_s *, void *))SubLevel_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, SubLevel_RunHandler);
  QTask_LinkQTaskEventHandlerFn(v1, MagicObj_eMagicObjEnterEvent, SubLevel_MagicObjEnterHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))SubLevel_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v1, ParameterList_eUpdateInternalDataQTaskEvent, SubLevel_UpdateInternalDataHandler);
  v2 = (struct ParameterList_s *)Mem_AllocFn(32, 4);
  v3 = Level_eParameterTypeString256;
  v2->ptParameterListItem = (struct ParameterListItem_s *)&v2[1];
  v2->nParameters = 0;
  v2->nMaxParameters = 1;
  SubLevel_ptParameterList = v2;
  ParameterList_AddParameter(v2, 0x28u, v3, "Sublevel filename", 7u, nullptr);
}

// source: j/0/flow/sublevel.c:231  [size]
void __cdecl SubLevel_Close()
{
  int v0; // esi

  QTask_DeleteQTaskType(SubLevel_eQTaskType);
  if ( SubLevel_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&SubLevel_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
}

// source: j/0/flow/sublevel.c:248  [size]
unsigned __int16 __cdecl SubLevel_GetQTaskType()
{
  return SubLevel_eQTaskType;
}
