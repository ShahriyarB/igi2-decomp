/* h/2/levelscript.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/levelscript.c:60  [size]
void __cdecl LevelScript_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = LevelScript_ptParameterList;
}

// source: h/2/levelscript.c:77  [size]
void __cdecl LevelScript_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: h/2/levelscript.c:89  [size]
void __cdecl LevelScript_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[1].ptPrev = nullptr;
}

// source: h/2/levelscript.c:107  [anchor-mhash]
void __cdecl LevelScript_RunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // eax
  int v2; // edx
  struct QTask_s *v3; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, _DWORD); // ecx
  int v5; // edx
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptNext; // ecx
  struct ScriptRunContext_t tScriptRunContext; // [esp+4h] [ebp-8h] BYREF

  if ( !ptQTask[1].ptPrev )
  {
    ptHead = ptQTask->tQTaskChildren.ptHead;
    ptQTask[1].ptPrev = ptHead->ptNext != nullptr ? ptHead : nullptr;
    if ( ptHead->ptNext )
    {
      if ( ptHead )
      {
        v2 = QTask_nProtectedQTaskStackOffset;
        do
        {
          if ( ptHead->ptNext )
            v3 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
          else
            v3 = nullptr;
          QTask_atProtectedQTaskStack[v2].ptQTask = v3;
          pfHandler = (void (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][ptHead->eQTaskType].pfHandler;
          v5 = v2 + 1;
          QTask_nProtectedQTaskStackOffset = v5;
          if ( pfHandler )
          {
            pfHandler(ptHead, 0);
            v5 = QTask_nProtectedQTaskStackOffset;
          }
          ptHead = (struct QTask_s *)dword_849C7DC[v5];
          v2 = v5 - 1;
          QTask_nProtectedQTaskStackOffset = v2;
        }
        while ( ptHead );
      }
    }
  }
  while ( 1 )
  {
    ptPrev = ptQTask[1].ptPrev;
    tScriptRunContext.iParentID = (int)ptQTask[1].ptNext;
    tScriptRunContext.isContinue = 0;
    if ( !ptPrev )
      break;
    ((void (__cdecl *)(struct QTask_s *, struct ScriptRunContext_t *))QTask_aatQTaskFinalEvent[LevelScript_eRunScriptEvent][ptPrev->eQTaskType].pfHandler)(
      ptPrev,
      &tScriptRunContext);
    if ( !tScriptRunContext.isContinue )
      break;
    ptNext = ptQTask[1].ptPrev->ptNext;
    if ( ptNext )
      ptQTask[1].ptPrev = ptNext->ptNext != nullptr ? ptNext : nullptr;
    else
      ptQTask[1].ptPrev = nullptr;
  }
}

// source: h/2/levelscript.c:153  [anchor-hash]
void __cdecl LevelScript_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // ax
  __int16 v2; // ax
  unsigned __int16 v3; // si
  struct ParameterList_s *v4; // eax
  int v5; // edx

  BaseQTaskType = QTask_GetBaseQTaskType();
  LevelScript_eQTaskType = QTask_NewQTaskType("LevelScript", 48, BaseQTaskType, 0, 0);
  v1 = QTask_GetBaseQTaskType();
  v2 = QTask_NewQTaskEventFn(v1, "RunScript");
  v3 = LevelScript_eQTaskType;
  LevelScript_eRunScriptEvent = v2;
  QTask_LinkQTaskEventHandlerFn(
    LevelScript_eQTaskType,
    0,
    (void (__cdecl *)(struct QTask_s *, void *))LevelScript_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v3, 1, LevelScript_RunHandler);
  QTask_LinkQTaskEventHandlerFn(
    v3,
    ParameterList_eUpdateInternalDataQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))LevelScript_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v3,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))LevelScript_GetParameterListHandler);
  v4 = (struct ParameterList_s *)Mem_AllocFn(52, 4);
  v4->ptParameterListItem = (struct ParameterListItem_s *)&v4[1];
  v5 = Level_eParameterTypeInt32;
  v4->nParameters = 0;
  v4->nMaxParameters = 2;
  LevelScript_ptParameterList = v4;
  ParameterList_AddParameter(v4, 0x28u, v5, "ID", 7u, nullptr);
}

// source: h/2/levelscript.c:184  [anchor-hash]
void __cdecl LevelScript_Close()
{
  int v0; // esi

  QTask_DeleteQTaskEvent(LevelScript_eRunScriptEvent);
  LevelScript_eRunScriptEvent = 512;
  QTask_DeleteQTaskType(LevelScript_eQTaskType);
  if ( LevelScript_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&LevelScript_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
}

// source: h/2/levelscript.c:208  [size]
__int16 __cdecl LevelScript_GetRunScriptEvent()
{
  return LevelScript_eRunScriptEvent;
}
