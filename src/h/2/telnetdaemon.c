/* h/2/telnetdaemon.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/telnetdaemon.c:47  [size]
void __cdecl TelnetDaemon_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  if ( tMyThreadContext.isRunning == false )
    TelnetHost_CreateListenerThread(&tMyThreadContext);
}

// source: h/2/telnetdaemon.c:63  [size]
void __cdecl TelnetDaemon_DeleteHandler(struct QTask_s *ptQTask)
{
  if ( tMyThreadContext.isRunning )
    TelnetHost_TerminateListenerThread(&tMyThreadContext);
}

// source: h/2/telnetdaemon.c:79  [size]
void __cdecl TelnetDaemon_RunHandler(struct QTask_s *ptQTask)
{
  if ( tMyThreadContext.isRunning )
    TelnetHost_PollListenerThread(&tMyThreadContext);
}

// source: h/2/telnetdaemon.c:95  [size]
void __cdecl TelnetDaemon_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: h/2/telnetdaemon.c:110  [size]
void __cdecl TelnetDaemon_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = TelnetDaemon_ptParameterList;
}

// source: h/2/telnetdaemon.c:128  [size]
unsigned __int16 __cdecl TelnetDaemon_GetQTaskType()
{
  return TelnetDaemon_eQTaskType;
}

// source: h/2/telnetdaemon.c:141  [anchor-hash]
void __cdecl TelnetDaemon_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si
  struct ParameterList_s *v2; // eax

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("TelnetDaemon", 40, BaseQTaskType, 0, 0);
  TelnetDaemon_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 0, TelnetDaemon_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, TelnetDaemon_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, TelnetDaemon_RunHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eUpdateInternalDataQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))TelnetDaemon_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))TelnetDaemon_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  v2 = (struct ParameterList_s *)Mem_AllocFn(32, 4);
  v2->nParameters = 0;
  v2->nMaxParameters = 1;
  v2->ptParameterListItem = (struct ParameterListItem_s *)&v2[1];
  TelnetDaemon_ptParameterList = v2;
}

// source: h/2/telnetdaemon.c:169  [size]
void __cdecl TelnetDaemon_Close()
{
  int v0; // esi

  if ( TelnetDaemon_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&TelnetDaemon_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(TelnetDaemon_eQTaskType);
}
