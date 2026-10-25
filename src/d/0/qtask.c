/* d/0/qtask.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: d/0/qtask.c:537  [size]
int __cdecl QTask_isProtectedQTaskStackEmpty()
{
  return QTask_nProtectedQTaskStackOffset == 0;
}

// source: d/0/qtask.c:1074  [anchor-hash]
unsigned __int16 __cdecl QTask_GetPropertiesStaticFn(unsigned __int16 eQTaskType)
{
  int v1; // eax
  int v2; // edx
  __int16 *v3; // edi
  __int16 v4; // cx
  void *pfHandler; // ebx
  void *v6; // ebx
  __int16 v7; // cx
  void *v8; // ebx
  __int16 v9; // cx
  void *v10; // ebx
  __int16 v11; // cx
  void *v12; // ebx
  __int16 v13; // cx
  void *v14; // ebx
  __int16 v15; // cx
  void *v16; // ebx
  __int16 v17; // cx
  void *v18; // ebx

  v1 = 0;
  v2 = 2;
  v3 = &QTask_aePropertyBitAllocated[1];
  do
  {
    v4 = *(v3 - 1);
    if ( v4 != 512 )
    {
      pfHandler = QTask_aatQTaskFinalEvent[v4][eQTaskType].pfHandler;
      LOWORD(pfHandler) = pfHandler != nullptr;
      v1 |= (_DWORD)pfHandler << (v2 - 2);
    }
    if ( *v3 != 512 )
    {
      v6 = QTask_aatQTaskFinalEvent[*v3][eQTaskType].pfHandler;
      LOWORD(v6) = v6 != nullptr;
      v1 |= (_DWORD)v6 << (v2 - 1);
    }
    v7 = v3[1];
    if ( v7 != 512 )
    {
      v8 = QTask_aatQTaskFinalEvent[v7][eQTaskType].pfHandler;
      LOWORD(v8) = v8 != nullptr;
      v1 |= (_DWORD)v8 << v2;
    }
    v9 = v3[2];
    if ( v9 != 512 )
    {
      v10 = QTask_aatQTaskFinalEvent[v9][eQTaskType].pfHandler;
      LOWORD(v10) = v10 != nullptr;
      v1 |= (_DWORD)v10 << (v2 + 1);
    }
    v11 = v3[3];
    if ( v11 != 512 )
    {
      v12 = QTask_aatQTaskFinalEvent[v11][eQTaskType].pfHandler;
      LOWORD(v12) = v12 != nullptr;
      v1 |= (_DWORD)v12 << (v2 + 2);
    }
    v13 = v3[4];
    if ( v13 != 512 )
    {
      v14 = QTask_aatQTaskFinalEvent[v13][eQTaskType].pfHandler;
      LOWORD(v14) = v14 != nullptr;
      v1 |= (_DWORD)v14 << (v2 + 3);
    }
    v15 = v3[5];
    if ( v15 != 512 )
    {
      v16 = QTask_aatQTaskFinalEvent[v15][eQTaskType].pfHandler;
      LOWORD(v16) = v16 != nullptr;
      v1 |= (_DWORD)v16 << (v2 + 4);
    }
    v17 = v3[6];
    if ( v17 != 512 )
    {
      v18 = QTask_aatQTaskFinalEvent[v17][eQTaskType].pfHandler;
      LOWORD(v18) = v18 != nullptr;
      v1 |= (_DWORD)v18 << (v2 + 5);
    }
    v2 += 8;
    v3 += 8;
  }
  while ( v2 - 2 < 16 );
  return v1 | 0x8000;
}

// source: d/0/qtask.c:1106  [anchor-hash]
void __cdecl QTask_CalculatePropertyBits()
{
  unsigned __int16 v0; // si
  unsigned __int16 *p_bQTaskProperties; // edi

  v0 = 0;
  p_bQTaskProperties = &QTask_atQTaskType[0].bQTaskProperties;
  do
  {
    if ( *((_BYTE *)p_bQTaskProperties - 3) )
      *p_bQTaskProperties = QTask_GetPropertiesStaticFn(v0);
    p_bQTaskProperties += 26;
    ++v0;
  }
  while ( (int)p_bQTaskProperties < 139052504 );
}

// source: d/0/qtask.c:1142  [anchor-callee]
struct QTask_s *__cdecl QTask_CreateNewTask(struct QTask_s *ptParent, unsigned __int16 eQTaskType)
{
  int v3; // edi
  char isUseMemPool; // al
  unsigned int nAllocatedBlocks; // ecx
  struct MemPool_s *p_tMemPool; // esi
  struct QTask_s *result; // eax
  int v8; // ecx
  char *i; // esi
  char eQTaskTypea = *(char *)&eQTaskType; // [esp+18h] [ebp+8h] ARGSLOT

  v3 = eQTaskType;
  isUseMemPool = QTask_atQTaskType[v3].isUseMemPool;
  eQTaskTypea = 0;
  ++QTask_nQTask;
  if ( !isUseMemPool )
    goto LABEL_7;
  nAllocatedBlocks = QTask_atQTaskType[v3].tMemPool.nAllocatedBlocks;
  p_tMemPool = &QTask_atQTaskType[v3].tMemPool;
  if ( QTask_atQTaskType[v3].tMemPool.nBlocks == nAllocatedBlocks )
  {
    eQTaskTypea = 0;
LABEL_7:
    result = (struct QTask_s *)Mem_AllocFn(QTask_atQTaskType[v3].nSize, 4);
    goto LABEL_8;
  }
  eQTaskTypea = 1;
  if ( nAllocatedBlocks == p_tMemPool->nBlocks )
    MemPool_ReAlloc(p_tMemPool, p_tMemPool->nReAllocBlocks);
  ++p_tMemPool->nAllocatedBlocks;
  result = (struct QTask_s *)p_tMemPool->tMemPoolFreeList.ptHead;
  p_tMemPool->tMemPoolFreeList.ptHead = (struct MemPoolFreeItem_s *)result->ptNext;
LABEL_8:
  result->isInMemPool = eQTaskTypea;
  result->ptParent = ptParent;
  result->tQTaskChildren.ptHead = (struct QTask_s *)&result->tQTaskChildren.ptMiddle;
  result->tQTaskChildren.ptMiddle = nullptr;
  result->tQTaskChildren.ptTail = (struct QTask_s *)&result->tQTaskChildren;
  result->eQTaskType = eQTaskType;
  result->tQTaskRefList.ptHead = (struct QReference_s *)&result->tQTaskRefList.ptMiddle;
  result->tQTaskRefList.ptMiddle = nullptr;
  result->ptPrev = nullptr;
  result->ptNext = nullptr;
  result->tQTaskRefList.ptTail = (struct QReference_s *)&result->tQTaskRefList;
  v8 = 0;
  for ( i = (char *)result + QTask_atQTaskType[0].nSize; v8 < QTask_atQTaskType[v3].nSize - QTask_atQTaskType[0].nSize; ++v8 )
    i[v8] = 0;
  return result;
}

// source: d/0/qtask.c:1278  [anchor-hash]
void __cdecl QTask_OpenQTaskType()
{
  struct QTaskType_s *v0; // eax

  v0 = QTask_atQTaskType;
  do
  {
    v0->isUsed = 0;
    v0->zName = nullptr;
    ++v0;
  }
  while ( (int)v0 < 139052460 );
}

// source: d/0/qtask.c:1302  [anchor-callee]
void __cdecl QTask_CloseQTaskType()
{
  ;
}

// source: d/0/qtask.c:1327  [anchor-hash]
void __cdecl QTask_OpenEvent()
{
  char **p_zName; // eax

  p_zName = &QTask_atQTaskEventType[0].zName;
  do
  {
    *((_BYTE *)p_zName - 6) = 0;
    *p_zName = nullptr;
    p_zName += 3;
  }
  while ( (int)p_zName < 7347964 );
}

// source: d/0/qtask.c:1357  [size]
void __cdecl QTask_CloseEvent()
{
  ;
}

// source: d/0/qtask.c:1584  [anchor-callee]
struct QTask_s *__cdecl QTask_NewFn(
        struct QTask_s *ptParent,
        unsigned __int16 eQTaskType,
        void *pxContext)
{
  struct QTask_s *NewTask; // eax
  struct QTask_s *v4; // esi
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // eax

  NewTask = QTask_CreateNewTask(ptParent, eQTaskType);
  v4 = NewTask;
  if ( ptParent )
    List_AddTail(NewTask, (int)&ptParent->tQTaskChildren);
  pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][v4->eQTaskType].pfHandler;
  if ( pfHandler )
    pfHandler(v4, pxContext);
  return v4;
}

// source: d/0/qtask.c:1651  [anchor-caller]
struct QTask_s *__cdecl QTask_NewFirstChildFn(
        struct QTask_s *ptParent,
        unsigned __int16 eQTaskType,
        void *pxContext)
{
  struct QTask_s *NewTask; // eax
  struct QTask_s *v4; // esi
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // eax

  NewTask = QTask_CreateNewTask(ptParent, eQTaskType);
  v4 = NewTask;
  if ( ptParent )
    List_AddHead(NewTask, (int)&ptParent->tQTaskChildren);
  pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][v4->eQTaskType].pfHandler;
  if ( pfHandler )
    pfHandler(v4, pxContext);
  return v4;
}

// source: d/0/qtask.c:1716  [anchor-callee]
void __cdecl QTask_LinkQTaskEventHandlerFn(
        unsigned __int16 eQTaskType,
        __int16 eQTaskEvent,
        void (__cdecl *pfQTaskEvent__)(struct QTask_s *, void *))
{
  int v3; // esi
  int v4; // eax
  bool v5; // zf
  int v6; // edi
  unsigned __int16 *p_eBaseQTaskType; // ebx

  ++QTask_nHandlerTimeStamp;
  v3 = 511 * eQTaskEvent;
  v4 = v3 + eQTaskType;
  v5 = dword_834E210++ == 0;
  QTask_aatQTaskFinalEvent[0][v4].pfHandler = pfQTaskEvent__;
  QTask_aaisHandlerSetDirectly[v4] = v5;
  v6 = 0;
  p_eBaseQTaskType = &QTask_atQTaskType[0].eBaseQTaskType;
  do
  {
    if ( *((_BYTE *)p_eBaseQTaskType + 33) && *p_eBaseQTaskType == eQTaskType && !QTask_aaisHandlerSetDirectly[v3 + v6] )
      QTask_LinkQTaskEventHandlerFn(v6, eQTaskEvent, pfQTaskEvent__);
    p_eBaseQTaskType += 26;
    ++v6;
  }
  while ( (int)p_eBaseQTaskType < 139052468 );
  QTask_CalculatePropertyBits();
  --dword_834E210;
}

// source: d/0/qtask.c:1815  [anchor-callee]
void __cdecl QTask_LinkQTaskEventHandlerNoContextFn(
        unsigned __int16 eQTaskType,
        int eQTaskEventNoContext,
        void (__cdecl *pfQTaskEventNoContext__)(struct QTask_s *))
{
  int v3; // eax
  bool v4; // zf
  int v5; // edi
  unsigned __int16 *p_eBaseQTaskType; // ebx

  ++QTask_nHandlerTimeStamp;
  v3 = 511 * eQTaskEventNoContext + eQTaskType;
  v4 = dword_834E214++ == 0;
  QTask_aatQTaskFinalEvent[0][v3].pfHandler = pfQTaskEventNoContext__;
  QTask_aaisHandlerSetDirectly[v3] = v4;
  v5 = 0;
  p_eBaseQTaskType = &QTask_atQTaskType[0].eBaseQTaskType;
  do
  {
    if ( *((_BYTE *)p_eBaseQTaskType + 33)
      && *p_eBaseQTaskType == eQTaskType
      && !QTask_aaisHandlerSetDirectly[511 * eQTaskEventNoContext + v5] )
    {
      QTask_LinkQTaskEventHandlerNoContextFn(v5, eQTaskEventNoContext, pfQTaskEventNoContext__);
    }
    p_eBaseQTaskType += 26;
    ++v5;
  }
  while ( (int)p_eBaseQTaskType < 139052468 );
  QTask_CalculatePropertyBits();
  --dword_834E214;
}

// source: d/0/qtask.c:2125  [size]
void __cdecl QTask_RegisterQTaskEventCallback(
        void (__cdecl *pfQTaskEventCallback)(struct QTask_s *, int, void *),
        void *pxContext)
{
  ;
}

// source: d/0/qtask.c:2143  [size]
void __cdecl QTask_RemoveQTaskEventCallback(
        void (__cdecl *pfQTaskEventCallback)(struct QTask_s *, int, void *))
{
  ;
}

// source: d/0/qtask.c:2520  [anchor-callee]
struct QTask_s *__cdecl QTask_RemoveFromParent(struct QTask_s *ptQTask)
{
  if ( ptQTask->ptParent )
    return (struct QTask_s *)Node_Remove(ptQTask);
  return ptQTask;
}

// source: d/0/qtask.c:2544  [anchor-hash]
struct QTask_s *__cdecl QTask_UnlinkFromParent(struct QTask_s *ptQTask)
{
  struct QTask_s *result; // eax

  result = QTask_RemoveFromParent(ptQTask);
  result->ptParent = nullptr;
  result->ptPrev = nullptr;
  result->ptNext = nullptr;
  return result;
}

// source: d/0/qtask.c:2561  [anchor-callee]
void __cdecl QTask_Delete(struct QTask_s *ptQTask)
{
  int v1; // ecx
  struct QTask_s *v2; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  struct QTask_s *ptTail; // eax
  struct QTask_s *i; // esi
  void (__cdecl *v6)(struct QTask_s *); // eax
  struct QReference_s *ptHead; // eax
  struct QReference_s *j; // esi
  _DWORD *v9; // eax
  int v10; // eax
  struct MemPoolFreeItem_s *v11; // edx
  int v12; // esi

  if ( ptQTask )
  {
    v1 = 0;
    --QTask_nQTask;
    if ( QTask_nProtectedQTaskStackOffset > 0 )
    {
      while ( QTask_atProtectedQTaskStack[v1].ptQTask != ptQTask )
      {
        if ( ++v1 >= QTask_nProtectedQTaskStackOffset )
          goto LABEL_10;
      }
      if ( ptQTask->ptNext )
        v2 = ptQTask->ptNext->ptNext != nullptr ? ptQTask->ptNext : nullptr;
      else
        v2 = nullptr;
      QTask_atProtectedQTaskStack[v1].ptQTask = v2;
    }
LABEL_10:
    pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[3][ptQTask->eQTaskType].pfHandler;
    if ( pfHandler )
      pfHandler(ptQTask);
    ptTail = ptQTask->tQTaskChildren.ptTail;
    for ( i = ptTail->ptPrev; i; i = i->ptPrev )
    {
      QTask_Delete(ptTail);
      ptTail = i;
    }
    v6 = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[2][ptQTask->eQTaskType].pfHandler;
    if ( v6 )
      v6(ptQTask);
    ptHead = ptQTask->tQTaskRefList.ptHead;
    for ( j = ptHead->ptNext; j; j = j->ptNext )
    {
      v9 = Node_Remove(ptHead);
      List_AddTail(v9, (int)&QTask_tQTaskRefList)[2] = 0;
      ptHead = j;
    }
    QTask_RemoveFromParent(ptQTask);
    if ( ptQTask->isInMemPool )
    {
      v10 = 52 * ptQTask->eQTaskType + 139025900;
      v11 = QTask_atQTaskType[ptQTask->eQTaskType].tMemPool.tMemPoolFreeList.ptHead;
      *(_DWORD *)(v10 + 4) = QTask_atQTaskType[ptQTask->eQTaskType].tMemPool.nAllocatedBlocks - 1;
      ptQTask->ptNext = (struct QTask_s *)v11;
      *(_DWORD *)(v10 + 20) = ptQTask;
    }
    else
    {
      v12 = *(_DWORD *)((unsigned int)&ptQTask[-1].eQTaskType & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v12);
      memset(*(void **)(v12 + 8), 0xCDu, *(_DWORD *)(v12 + 16));
      free((void *)v12);
    }
  }
}

// source: d/0/qtask.c:2670  [anchor-hash]
struct QTask_s *__cdecl QTask_DeleteChildren(struct QTask_s *ptQTask)
{
  struct QTask_s *result; // eax
  struct QTask_s *i; // esi

  result = ptQTask->tQTaskChildren.ptTail;
  for ( i = result->ptPrev; i; i = i->ptPrev )
  {
    QTask_Delete(result);
    result = i;
  }
  return result;
}

// source: d/0/qtask.c:2700  [anchor-callee]
struct QTask_s *__cdecl QTask_ChangeParent(struct QTask_s *ptQTask, struct QTask_s *ptNewParent)
{
  struct QTask_s *v2; // ecx
  struct QTask_s *(__cdecl *pfHandler)(struct QTask_s *, struct QTaskParentChangedContext_s *); // ecx
  struct QTaskParentChangedContext_s tQTaskParentChangedContext; // [esp+0h] [ebp-4h] BYREF

  tQTaskParentChangedContext.ptOldParent = v2;
  if ( ptQTask->ptParent != ptNewParent )
  {
    tQTaskParentChangedContext.ptOldParent = ptQTask->ptParent;
    ptQTask = QTask_RemoveFromParent(ptQTask);
    ptQTask->ptParent = ptNewParent;
    if ( ptNewParent )
      ptQTask = (struct QTask_s *)List_AddTail(ptQTask, (int)&ptNewParent->tQTaskChildren);
    pfHandler = (struct QTask_s *(__cdecl *)(struct QTask_s *, struct QTaskParentChangedContext_s *))QTask_aatQTaskFinalEvent[4][ptQTask->eQTaskType].pfHandler;
    if ( pfHandler )
      return pfHandler(ptQTask, &tQTaskParentChangedContext);
  }
  return ptQTask;
}

// source: d/0/qtask.c:3006  [anchor-callee]
struct QTask_s *__cdecl QTask_TriggerQTaskEventParent(
        struct QTask_s *ptQTask,
        __int16 eQTaskEvent,
        void *pxContext)
{
  struct QTask_s *result; // eax
  int v4; // ecx

  result = ptQTask->ptParent;
  if ( result )
  {
    v4 = eQTaskEvent;
    while ( !QTask_aatQTaskFinalEvent[v4][result->eQTaskType].pfHandler )
    {
      result = result->ptParent;
      if ( !result )
        return result;
    }
    return (struct QTask_s *)((int (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[v4][result->eQTaskType].pfHandler)(
                               result,
                               pxContext);
  }
  return result;
}

// source: d/0/qtask.c:3039  [anchor-mhash]
struct QTask_s *__cdecl QTask_TriggerQTaskEventParentNoContext(
        struct QTask_s *ptQTask,
        int eQTaskEventNoContext)
{
  struct QTask_s *result; // eax
  int v3; // ecx

  result = ptQTask->ptParent;
  if ( result )
  {
    v3 = eQTaskEventNoContext;
    while ( !QTask_aatQTaskFinalEvent[v3][result->eQTaskType].pfHandler )
    {
      result = result->ptParent;
      if ( !result )
        return result;
    }
    return (struct QTask_s *)((int (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[v3][result->eQTaskType].pfHandler)(result);
  }
  return result;
}

// source: d/0/qtask.c:3115  [anchor-callee]
int __cdecl QTask_NewQTaskEventFn(unsigned __int16 eDefinedForQTaskType, char *zName)
{
  int result; // eax
  char *p_isUsed; // ecx
  int v4; // ecx

  result = 32;
  p_isUsed = &QTask_atQTaskEventType[32].isUsed;
  while ( *p_isUsed )
  {
    p_isUsed += 12;
    ++result;
    if ( (int)p_isUsed >= 7347958 )
    {
      LDebug_Error("Unable to allocate event");
      abort();
    }
  }
  v4 = result;
  QTask_atQTaskEventType[v4].isUsed = 1;
  QTask_atQTaskEventType[v4].isContext = 1;
  QTask_atQTaskEventType[v4].eDefinedForQTaskType = eDefinedForQTaskType;
  QTask_atQTaskEventType[v4].zName = zName;
  return result;
}

// source: d/0/qtask.c:3178  [anchor-callee]
int __cdecl QTask_NewQTaskEventNoContextFn(unsigned __int16 eDefinedForQTaskType, char *zName)
{
  int result; // eax
  char *p_isUsed; // ecx
  int v4; // ecx

  result = 32;
  p_isUsed = &QTask_atQTaskEventType[32].isUsed;
  while ( *p_isUsed )
  {
    p_isUsed += 12;
    ++result;
    if ( (int)p_isUsed >= 7347958 )
    {
      LDebug_Error("Unable to allocate event");
      abort();
    }
  }
  v4 = result;
  QTask_atQTaskEventType[v4].eDefinedForQTaskType = eDefinedForQTaskType;
  QTask_atQTaskEventType[v4].isUsed = 1;
  QTask_atQTaskEventType[v4].isContext = 0;
  QTask_atQTaskEventType[v4].zName = zName;
  return result;
}

// source: d/0/qtask.c:3241  [anchor-callee]
void __cdecl QTask_NewSystemQTaskEventFn(
        unsigned __int16 eDefinedForQTaskType,
        __int16 eQTaskEvent,
        char *zName)
{
  int v3; // eax

  v3 = eQTaskEvent;
  QTask_atQTaskEventType[v3].isUsed = 1;
  QTask_atQTaskEventType[v3].isContext = 1;
  QTask_atQTaskEventType[v3].eDefinedForQTaskType = eDefinedForQTaskType;
  QTask_atQTaskEventType[v3].zName = zName;
}

// source: d/0/qtask.c:3292  [anchor-callee]
int __cdecl QTask_NewSystemQTaskEventNoContextFn(
        unsigned __int16 eDefinedForQTaskType,
        int eQTaskEventNoContext,
        char *zName)
{
  int result; // eax

  result = eQTaskEventNoContext;
  QTask_atQTaskEventType[result].isUsed = 1;
  QTask_atQTaskEventType[result].eDefinedForQTaskType = eDefinedForQTaskType;
  QTask_atQTaskEventType[result].isContext = 0;
  QTask_atQTaskEventType[result].zName = zName;
  return result * 12;
}

// source: d/0/qtask.c:3340  [anchor-callee]
void __cdecl QTask_DeleteQTaskEvent(__int16 eQTaskEvent)
{
  QTask_atQTaskEventType[eQTaskEvent].isUsed = 0;
}

// source: d/0/qtask.c:3408  [anchor-callee]
// attributes: thunk
int __cdecl QTask_DeleteQTaskEventNoContext(int eQTaskEventNoContext)
{
  int result; // eax

  QTask_DeleteQTaskEvent(eQTaskEventNoContext);
  return result;
}

// source: d/0/qtask.c:3421  [anchor-callee]
unsigned __int16 __cdecl QTask_GetBaseQTaskType()
{
  return QTask_eBaseQTaskType;
}

// source: d/0/qtask.c:3438  [anchor-strings]
unsigned __int16 __cdecl QTask_NewQTaskType(
        char *zName,
        int nSize,
        unsigned __int16 eBaseQTaskType,
        int nMemPoolItems,
        char isInheritMemPool)
{
  int v6; // ebp
  char *p_isUsed; // eax
  int v8; // edi
  unsigned __int16 v9; // ax
  struct MemPool_s *p_tMemPool; // esi
  int v11; // eax
  _DWORD *v12; // ecx
  _DWORD *v13; // eax
  int v14; // edx
  _DWORD *v15; // eax
  int v16; // ecx

  v6 = 0;
  p_isUsed = &QTask_atQTaskType[0].isUsed;
  while ( *p_isUsed )
  {
    p_isUsed += 52;
    ++v6;
    if ( (int)p_isUsed >= 139052501 )
    {
      LDebug_Error("Unable to allocate task type");
      abort();
    }
  }
  v8 = v6;
  QTask_atQTaskType[v8].zName = zName;
  v9 = eBaseQTaskType;
  QTask_atQTaskType[v8].isUsed = 1;
  QTask_atQTaskType[v8].nSize = nSize;
  QTask_atQTaskType[v8].eBaseQTaskType = eBaseQTaskType;
  if ( eBaseQTaskType == 512 )
    QTask_atQTaskType[v6].bQTaskGroup = 0x20000000;
  else
    QTask_atQTaskType[v6].bQTaskGroup = QTask_atQTaskType[eBaseQTaskType].bQTaskGroup;
  if ( nMemPoolItems )
  {
    p_tMemPool = &QTask_atQTaskType[v8].tMemPool;
    v11 = nSize;
    if ( (unsigned int)nSize <= 4 )
      v11 = 4;
    p_tMemPool->nBlocks = 0;
    p_tMemPool->nAllocatedBlocks = 0;
    p_tMemPool->nAlignment = 4;
    p_tMemPool->nBlockSize = (v11 + 3) & 0xFFFFFFFC;
    p_tMemPool->nReAllocBlocks = 0;
    p_tMemPool->tMemPoolFreeList.ptHead = nullptr;
    p_tMemPool->tMemPoolSegmentList.ptHead = nullptr;
    MemPool_ReAlloc(p_tMemPool, nMemPoolItems);
    v9 = eBaseQTaskType;
    QTask_atQTaskType[v6].isUseMemPool = 1;
  }
  else
  {
    QTask_atQTaskType[v6].isUseMemPool = 0;
  }
  if ( v9 == 512 )
  {
    v15 = (_DWORD *)(4 * v6 + 137981376);
    v16 = 511;
    do
    {
      *v15 = 0;
      v15 += 511;
      --v16;
    }
    while ( v16 );
  }
  else
  {
    v12 = (_DWORD *)(4 * v6 + 137981376);
    v13 = (_DWORD *)(4 * v9 + 137981376);
    v14 = 511;
    do
    {
      *v12 = *v13;
      v13 += 511;
      v12 += 511;
      --v14;
    }
    while ( v14 );
  }
  QTask_CalculatePropertyBits();
  return v6;
}

// source: d/0/qtask.c:3553  [anchor-hash]
void __cdecl QTask_DeleteQTaskType(unsigned __int16 eQTaskType)
{
  int v1; // esi

  v1 = eQTaskType;
  if ( QTask_atQTaskType[v1].isUseMemPool )
    MemPool_DeInit(&QTask_atQTaskType[v1].tMemPool);
  QTask_atQTaskType[v1].isUsed = 0;
}

// source: d/0/qtask.c:3603  [anchor-callee]
int __cdecl QTask_GetNumberOfQTasks()
{
  return QTask_nQTask;
}

// source: d/0/qtask.c:3636  [anchor-hash]
unsigned __int16 __cdecl QTask_GetQTaskType(char *zName)
{
  unsigned __int16 v1; // bp
  char *p_isUsed; // edi

  v1 = 0;
  p_isUsed = &QTask_atQTaskType[0].isUsed;
  while ( !*p_isUsed || strcmp(QTask_GetQTaskTypeName(v1), zName) )
  {
    p_isUsed += 52;
    ++v1;
    if ( (int)p_isUsed >= 139052501 )
    {
      LDebug_Error("QTask type \"%s\" not defined", zName);
      abort();
    }
  }
  return v1;
}

// source: d/0/qtask.c:3685  [anchor-hash]
unsigned __int16 __cdecl QTask_GetQTaskTypeSafe(char *zName)
{
  unsigned __int16 v1; // bp
  char *p_isUsed; // edi

  v1 = 0;
  p_isUsed = &QTask_atQTaskType[0].isUsed;
  while ( !*p_isUsed || strcmp(QTask_GetQTaskTypeName(v1), zName) )
  {
    p_isUsed += 52;
    ++v1;
    if ( (int)p_isUsed >= 139052501 )
      return 512;
  }
  return v1;
}

// source: d/0/qtask.c:3714  [anchor-mhash]
void __cdecl QTask_TriggerQTaskEventDerivedQTaskTypes(
        unsigned __int16 eQTaskType,
        __int16 eQTaskEvent,
        void *pxContext)
{
  unsigned __int16 v3; // si
  int v4; // edi
  char *p_isUsed; // ebx
  void (__cdecl *pfHandler)(_DWORD, void *); // eax

  v3 = 0;
  v4 = 0;
  p_isUsed = &QTask_atQTaskType[0].isUsed;
  do
  {
    if ( *p_isUsed && QTask_IsQTaskTypeDerived(v3, eQTaskType) )
    {
      pfHandler = (void (__cdecl *)(_DWORD, void *))QTask_aatQTaskFinalEvent[eQTaskEvent][v4].pfHandler;
      if ( pfHandler )
        pfHandler(0, pxContext);
    }
    ++v3;
    ++v4;
    p_isUsed += 52;
  }
  while ( v3 < 0x1FFu );
}

// source: d/0/qtask.c:3742  [anchor-mhash]
void __cdecl QTask_TriggerQTaskEventDerivedQTaskTypesNoContext(unsigned __int16 eQTaskType, int eQTaskEvent)
{
  unsigned __int16 v2; // si
  int v3; // edi
  char *p_isUsed; // ebx
  void (__cdecl *pfHandler)(_DWORD); // eax

  v2 = 0;
  v3 = 0;
  p_isUsed = &QTask_atQTaskType[0].isUsed;
  do
  {
    if ( *p_isUsed && QTask_IsQTaskTypeDerived(v2, eQTaskType) )
    {
      pfHandler = (void (__cdecl *)(_DWORD))QTask_aatQTaskFinalEvent[eQTaskEvent][v3].pfHandler;
      if ( pfHandler )
        pfHandler(0);
    }
    ++v2;
    ++v3;
    p_isUsed += 52;
  }
  while ( v2 < 0x1FFu );
}

// source: d/0/qtask.c:3878  [anchor-callee]
char *__cdecl QTask_GetQTaskTypeName(unsigned __int16 eQTaskType)
{
  return QTask_atQTaskType[eQTaskType].zName;
}

// source: d/0/qtask.c:3897  [anchor-hash]
char *__cdecl QTask_GetQTaskEventName(__int16 eQTaskEvent)
{
  return QTask_atQTaskEventType[eQTaskEvent].zName;
}

// source: d/0/qtask.c:3919  [anchor-hash]
char *__cdecl QTask_GetQTaskEventNameNoContext(int eQTaskEventNoContext)
{
  return QTask_atQTaskEventType[eQTaskEventNoContext].zName;
}

// source: d/0/qtask.c:3939  [anchor-mhash]
int __cdecl QTask_EnumerateQTaskTypes(
        void (__cdecl *pfCallback)(struct QTaskEnumerateQTaskTypeContext_s *, void *),
        void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { int nQTaskTypes; };
    struct { char igi2_o1[4]; struct QTaskEnumerateQTaskTypeContext_s tContext; };
    char igi2_extent[16];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  unsigned __int16 v2; // di
  struct QTaskType_s *v3; // esi
  unsigned __int16 eBaseQTaskType; // cx
  int nSize; // edx

  v2 = 0;
  igi2_frame.nQTaskTypes = 0;
  v3 = QTask_atQTaskType;
  do
  {
    if ( v3->isUsed )
    {
      if ( pfCallback )
      {
        eBaseQTaskType = v3->eBaseQTaskType;
        nSize = v3->nSize;
        igi2_frame.tContext.zName = v3->zName;
        igi2_frame.tContext.eBaseQTaskType = eBaseQTaskType;
        igi2_frame.tContext.nSize = nSize;
        igi2_frame.tContext.eQTaskType = v2;
        pfCallback(&igi2_frame.tContext, pxContext);
      }
      ++igi2_frame.nQTaskTypes;
    }
    ++v3;
    ++v2;
  }
  while ( (int)v3 < 139052460 );
  return igi2_frame.nQTaskTypes;
}

// source: d/0/qtask.c:3974  [anchor-mhash]
int __cdecl QTask_EnumerateQTaskEvents(
        void (__cdecl *pfCallback)(struct QTaskEnumerateQTaskEventContext_s *, void *),
        void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { int nQTaskEvents; };
    struct { char igi2_o1[4]; struct QTaskEnumerateQTaskEventContext_s tContext; };
    char igi2_extent[12];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  __int16 v2; // di
  char **p_zName; // esi

  v2 = 0;
  igi2_frame.nQTaskEvents = 0;
  p_zName = &QTask_atQTaskEventType[0].zName;
  do
  {
    if ( *((_BYTE *)p_zName - 6) )
    {
      if ( pfCallback )
      {
        igi2_frame.tContext.zName = *p_zName;
        igi2_frame.tContext.eQTaskEvent = v2;
        pfCallback(&igi2_frame.tContext, pxContext);
      }
      ++igi2_frame.nQTaskEvents;
    }
    p_zName += 3;
    ++v2;
  }
  while ( (int)p_zName < 7347964 );
  return igi2_frame.nQTaskEvents;
}

// source: d/0/qtask.c:4020  [anchor-callee]
void __cdecl QTask_QTaskTypeTriggerQTaskEvent(
        unsigned __int16 eQTaskType,
        __int16 eQTaskEvent,
        void *pxContext)
{
  void (__cdecl *pfHandler)(_DWORD, void *); // eax

  pfHandler = (void (__cdecl *)(_DWORD, void *))QTask_aatQTaskFinalEvent[eQTaskEvent][eQTaskType].pfHandler;
  if ( pfHandler )
    pfHandler(0, pxContext);
}

// source: d/0/qtask.c:4042  [anchor-hash]
int __cdecl QTask_QTaskTypeTriggerQTaskEventNoContext(
        unsigned __int16 eQTaskType,
        int eQTaskEventNoContext)
{
  int result; // eax

  result = (int)QTask_aatQTaskFinalEvent[eQTaskEventNoContext][eQTaskType].pfHandler;
  if ( result )
    return ((int (__cdecl *)(_DWORD))result)(0);
  return result;
}

// source: d/0/qtask.c:4062  [anchor-callee]
struct QTask_s *__cdecl QTask_InsertBeforeQTask(
        struct QTask_s *ptQTaskToInsert,
        struct QTask_s *ptQTask)
{
  struct QTask_s *ptParent; // esi
  struct QTask_s *v3; // edi
  struct QTask_s *v4; // eax
  struct QTask_s *result; // eax
  struct QTask_s *(__cdecl *pfHandler)(struct QTask_s *, struct QTaskParentChangedContext_s *); // ecx
  struct QTaskParentChangedContext_s tQTaskParentChangedContext; // [esp+8h] [ebp-4h] BYREF

  ptParent = ptQTask->ptParent;
  v3 = ptQTaskToInsert->ptParent;
  v4 = QTask_RemoveFromParent(ptQTaskToInsert);
  result = (struct QTask_s *)Node_InsertBefore(v4, (int)ptQTask);
  result->ptParent = ptParent;
  if ( ptParent != v3 )
  {
    pfHandler = (struct QTask_s *(__cdecl *)(struct QTask_s *, struct QTaskParentChangedContext_s *))QTask_aatQTaskFinalEvent[4][result->eQTaskType].pfHandler;
    tQTaskParentChangedContext.ptOldParent = v3;
    if ( pfHandler )
      return pfHandler(result, &tQTaskParentChangedContext);
  }
  return result;
}

// source: d/0/qtask.c:4096  [anchor-caller]
struct QTask_s *__cdecl QTask_InsertAfterQTask(
        struct QTask_s *ptQTaskToInsert,
        struct QTask_s *ptQTask)
{
  struct QTask_s *ptParent; // esi
  struct QTask_s *v3; // edi
  struct QTask_s *v4; // eax
  struct QTask_s *result; // eax
  struct QTask_s *(__cdecl *pfHandler)(struct QTask_s *, struct QTaskParentChangedContext_s *); // ecx
  struct QTaskParentChangedContext_s tQTaskParentChangedContext; // [esp+8h] [ebp-4h] BYREF

  ptParent = ptQTask->ptParent;
  v3 = ptQTaskToInsert->ptParent;
  v4 = QTask_RemoveFromParent(ptQTaskToInsert);
  result = (struct QTask_s *)Node_InsertAfter(v4, (int)ptQTask);
  result->ptParent = ptParent;
  if ( ptParent != v3 )
  {
    pfHandler = (struct QTask_s *(__cdecl *)(struct QTask_s *, struct QTaskParentChangedContext_s *))QTask_aatQTaskFinalEvent[4][result->eQTaskType].pfHandler;
    tQTaskParentChangedContext.ptOldParent = v3;
    if ( pfHandler )
      return pfHandler(result, &tQTaskParentChangedContext);
  }
  return result;
}

// source: d/0/qtask.c:4130  [anchor-hash]
struct QTask_s *__cdecl QTask_GetFirstChildOfType(
        struct QTask_s *ptQTask,
        unsigned __int16 eQTaskType)
{
  struct QTask_s *result; // eax
  struct QTask_s *ptNext; // ecx

  result = ptQTask->tQTaskChildren.ptHead;
  ptNext = result->ptNext;
  if ( !result->ptNext )
    return nullptr;
  while ( result->eQTaskType != eQTaskType )
  {
    result = ptNext;
    ptNext = ptNext->ptNext;
    if ( !ptNext )
      return nullptr;
  }
  return result;
}

// source: d/0/qtask.c:4159  [anchor-hash]
struct QTask_s *__cdecl QTask_GetLastChildOfType(
        struct QTask_s *ptQTask,
        unsigned __int16 eQTaskType)
{
  struct QTask_s *result; // eax
  struct QTask_s *ptPrev; // ecx

  result = ptQTask->tQTaskChildren.ptTail;
  ptPrev = result->ptPrev;
  if ( !ptPrev )
    return nullptr;
  while ( result->eQTaskType != eQTaskType )
  {
    result = ptPrev;
    ptPrev = ptPrev->ptPrev;
    if ( !ptPrev )
      return nullptr;
  }
  return result;
}

// source: d/0/qtask.c:4188  [anchor-hash]
struct QTask_s *__cdecl QTask_GetNextSiblingOfType(
        struct QTask_s *ptQTask,
        unsigned __int16 eQTaskType)
{
  struct QTask_s *result; // eax

  result = ptQTask->ptNext;
  if ( !result || !result->ptNext )
    return nullptr;
  while ( result->eQTaskType != eQTaskType )
  {
    result = result->ptNext;
    if ( !result || !result->ptNext )
      return nullptr;
  }
  return result;
}

// source: d/0/qtask.c:4212  [anchor-hash]
struct QTask_s *__cdecl QTask_GetPrevSiblingOfType(
        struct QTask_s *ptQTask,
        unsigned __int16 eQTaskType)
{
  struct QTask_s *result; // eax

  result = ptQTask->ptPrev;
  if ( !result || !result->ptPrev )
    return nullptr;
  while ( result->eQTaskType != eQTaskType )
  {
    result = result->ptPrev;
    if ( !result || !result->ptPrev )
      return nullptr;
  }
  return result;
}

// source: d/0/qtask.c:4236  [anchor-hash]
struct QTask_s *__cdecl QTask_GetFirstParentOfType(
        struct QTask_s *ptQTask,
        unsigned __int16 eQTaskType)
{
  struct QTask_s *result; // eax

  for ( result = ptQTask->ptParent; result; result = result->ptParent )
  {
    if ( result->eQTaskType == eQTaskType )
      break;
  }
  return result;
}

// source: d/0/qtask.c:4261  [anchor-mhash]
struct QTask_s *__cdecl QTask_GetFirstParentDerivedOfType(
        struct QTask_s *ptQTask,
        unsigned __int16 eQTaskType)
{
  struct QTask_s *i; // edx

  for ( i = ptQTask->ptParent; i; i = i->ptParent )
  {
    if ( QTask_IsQTaskTypeDerived(i->eQTaskType, eQTaskType) )
      break;
  }
  return i;
}

// source: d/0/qtask.c:4287  [anchor-callee]
enum bool __cdecl QTask_IsQTaskTypeDerived(
        unsigned __int16 eQTaskType,
        unsigned __int16 eBaseQTaskType)
{
  while ( eQTaskType != eBaseQTaskType )
  {
    eQTaskType = QTask_atQTaskType[eQTaskType].eBaseQTaskType;
    if ( eQTaskType == 512 )
      return false;
  }
  return true;
}

// source: d/0/qtask.c:4316  [anchor-hash]
void __cdecl QTask_TriggerBaseHandler(
        struct QTask_s *ptQTask,
        unsigned __int16 eQTaskType,
        __int16 eQTaskEvent,
        void *pxContext)
{
  ((void (__cdecl *)())QTask_aatQTaskFinalEvent[eQTaskEvent][QTask_atQTaskType[eQTaskType].eBaseQTaskType].pfHandler)(ptQTask, pxContext);
}

// source: d/0/qtask.c:4334  [anchor-hash]
int __cdecl QTask_TriggerBaseHandlerNoContext(
        struct QTask_s *ptQTask,
        unsigned __int16 eQTaskType,
        int eQTaskEventNoContext)
{
  return ((int (*)(void))QTask_aatQTaskFinalEvent[eQTaskEventNoContext][QTask_atQTaskType[eQTaskType].eBaseQTaskType].pfHandler)();
}

// source: d/0/qtask.c:4352  [anchor-caller]
int __cdecl QTask_AllocatePropertyBit(__int16 eQTaskEvent)
{
  int i; // ebx

  for ( i = 12; QTask_aePropertyBitAllocated[i] != 512; ++i )
    ;
  QTask_aePropertyBitAllocated[i] = eQTaskEvent;
  QTask_anEventBit[eQTaskEvent] = i;
  QTask_CalculatePropertyBits();
  return i;
}

// source: d/0/qtask.c:4382  [anchor-callee]
void __cdecl QTask_AllocateSystemPropertyBit(__int16 eQTaskEvent, int iBit)
{
  QTask_aePropertyBitAllocated[iBit] = eQTaskEvent;
  QTask_anEventBit[eQTaskEvent] = iBit;
  QTask_CalculatePropertyBits();
}

// source: d/0/qtask.c:4403  [anchor-callee]
void __cdecl QTask_FreePropertyBit(__int16 eQTaskEvent)
{
  QTask_aePropertyBitAllocated[QTask_anEventBit[eQTaskEvent]] = 512;
  QTask_anEventBit[eQTaskEvent] = -1;
  QTask_CalculatePropertyBits();
}

// source: d/0/qtask.c:4446  [anchor-callee]
void __cdecl QTask_TriggerQTaskEventRecursively(struct QTask_s *ptQTask, __int16 eQTaskEvent, void *pxContext)
{
  int v3; // eax
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // ecx
  int v5; // eax
  struct QTask_s *ptHead; // ecx
  struct QTask_s *v7; // edx

  v3 = QTask_nProtectedQTaskStackOffset;
  QTask_atProtectedQTaskStack[QTask_nProtectedQTaskStackOffset].ptQTask = ptQTask;
  pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[eQTaskEvent][ptQTask->eQTaskType].pfHandler;
  v5 = v3 + 1;
  QTask_nProtectedQTaskStackOffset = v5;
  if ( pfHandler )
  {
    pfHandler(ptQTask, pxContext);
    v5 = QTask_nProtectedQTaskStackOffset;
  }
  if ( ptQTask == (struct QTask_s *)dword_849C7DC[v5] )
  {
    ptHead = ptQTask->tQTaskChildren.ptHead;
    if ( ptHead->ptNext )
    {
      for ( ; ptHead; v5 = QTask_nProtectedQTaskStackOffset - 1 )
      {
        if ( ptHead->ptNext )
          v7 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
        else
          v7 = nullptr;
        QTask_atProtectedQTaskStack[v5].ptQTask = v7;
        QTask_nProtectedQTaskStackOffset = v5 + 1;
        QTask_TriggerQTaskEventRecursively(ptHead, eQTaskEvent, pxContext);
        ptHead = (struct QTask_s *)dword_849C7DC[QTask_nProtectedQTaskStackOffset];
      }
    }
  }
  QTask_nProtectedQTaskStackOffset = v5 - 1;
}

// override: written as the retail instructions in support/qtask_asm.c (the handlers it calls
// read a second argument the retail stack layout supplies; see that file)

// source: d/0/qtask.c:4620  [anchor-callee]
struct QTask_s *__cdecl QTask_TriggerQTaskEventChildrenRecursively(
        struct QTask_s *ptQTask,
        __int16 eQTaskEvent,
        void *pxContext)
{
  struct QTask_s *ptHead; // esi

  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    do
    {
      QTask_TriggerQTaskEventRecursively(ptHead, eQTaskEvent, pxContext);
      ptHead = ptHead->ptNext;
    }
    while ( ptHead && ptHead->ptNext );
  }
  return ptQTask;
}

// source: d/0/qtask.c:4644  [anchor-callee]
struct QTask_s *__cdecl QTask_TriggerQTaskEventChildrenRecursivelyNoContext(
        struct QTask_s *ptQTask,
        int eQTaskEventNoContext)
{
  struct QTask_s *ptHead; // esi

  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    do
    {
      QTask_TriggerQTaskEventRecursivelyNoContext(ptHead, eQTaskEventNoContext);
      ptHead = ptHead->ptNext;
    }
    while ( ptHead && ptHead->ptNext );
  }
  return ptQTask;
}

// source: d/0/qtask.c:4668  [anchor-mhash]
void __cdecl QTask_TriggerQTaskEventRecursivelySpecificQTaskType(
        struct QTask_s *ptQTask,
        __int16 eQTaskEvent,
        unsigned __int16 eQTaskType,
        void *pxContext)
{
  int v4; // eax
  unsigned __int16 v5; // cx
  int v6; // eax
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // ecx
  struct QTask_s *ptHead; // ecx
  struct QTask_s *v9; // edx

  v4 = QTask_nProtectedQTaskStackOffset;
  QTask_atProtectedQTaskStack[QTask_nProtectedQTaskStackOffset].ptQTask = ptQTask;
  v5 = ptQTask->eQTaskType;
  v6 = v4 + 1;
  QTask_nProtectedQTaskStackOffset = v6;
  if ( v5 == eQTaskType )
  {
    pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[eQTaskEvent][v5].pfHandler;
    if ( pfHandler )
    {
      pfHandler(ptQTask, pxContext);
      v6 = QTask_nProtectedQTaskStackOffset;
    }
  }
  if ( ptQTask == (struct QTask_s *)dword_849C7DC[v6] )
  {
    ptHead = ptQTask->tQTaskChildren.ptHead;
    if ( ptHead->ptNext )
    {
      for ( ; ptHead; v6 = QTask_nProtectedQTaskStackOffset - 1 )
      {
        if ( ptHead->ptNext )
          v9 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
        else
          v9 = nullptr;
        QTask_atProtectedQTaskStack[v6].ptQTask = v9;
        QTask_nProtectedQTaskStackOffset = v6 + 1;
        QTask_TriggerQTaskEventRecursivelySpecificQTaskType(ptHead, eQTaskEvent, eQTaskType, pxContext);
        ptHead = (struct QTask_s *)dword_849C7DC[QTask_nProtectedQTaskStackOffset];
      }
    }
  }
  QTask_nProtectedQTaskStackOffset = v6 - 1;
}

// source: d/0/qtask.c:4748  [anchor-callee]
struct QTask_s *__cdecl QTask_SetAlwaysRunQTask(struct QTask_s *ptQTask)
{
  QTask_ptAlwaysRunQTask = ptQTask;
  return ptQTask;
}

// source: d/0/qtask.c:4761  [size]
struct QTask_s *__cdecl QTask_GetAlwaysRunQTask()
{
  return QTask_ptAlwaysRunQTask;
}

// source: d/0/qtask.c:4836  [anchor-hash]
enum bool __cdecl QTask_QTaskEventHasContext(int iQTaskEvent)
{
  return QTask_atQTaskEventType[iQTaskEvent].isContext;
}

// source: d/0/qtask.c:4852  [size]
void __cdecl QTask_SetProfilingStatus(char isEnableProfiling)
{
  QTask_isEnableProfiling = isEnableProfiling;
}

// source: d/0/qtask.c:4865  [size]
int *__cdecl QTask_GetProfileData(
        int *pnTotalTime,
        int *pnTimesCalled,
        unsigned __int16 eQTaskType,
        __int16 eQTaskEvent)
{
  *pnTotalTime = 0;
  *pnTimesCalled = 0;
  return pnTotalTime;
}

// source: d/0/qtask.c:4888  [size]
void __cdecl QTask_SetProfilingLogCallback(void (__cdecl *pfQTaskLogProfile)(char *))
{
  QTask_pfQTaskLogProfile = pfQTaskLogProfile;
}

// source: d/0/qtask.c:4901  [size]
void __cdecl QTask_ReadTimeFn(unsigned __int16 eQTaskType, __int16 eQTaskEvent)
{
  ;
}

// source: d/0/qtask.c:4925  [size]
void __cdecl QTask_WriteTimeFn()
{
  ;
}

// source: d/0/qtask.c:5010  [anchor-hash]
unsigned int __cdecl QTask_AllocateGroup()
{
  unsigned int result; // eax

  result = 1;
  if ( (QTask_bQTaskGroup & 1) != 0 )
  {
    do
      result *= 2;
    while ( (QTask_bQTaskGroup & result) != 0 );
  }
  QTask_bQTaskGroup |= result;
  return result;
}

// source: d/0/qtask.c:5035  [anchor-callee]
unsigned int __cdecl QTask_AllocateSystemGroup(unsigned int bQTaskGroup)
{
  QTask_bQTaskGroup |= bQTaskGroup;
  return bQTaskGroup;
}

// source: d/0/qtask.c:5050  [anchor-callee]
unsigned int __cdecl QTask_FreeGroup(unsigned int bQTaskGroup)
{
  unsigned int result; // eax

  result = ~bQTaskGroup;
  QTask_bQTaskGroup &= result;
  return result;
}

// source: d/0/qtask.c:5065  [anchor-callee]
unsigned int __cdecl QTask_SetQTaskTypeGroup(
        unsigned __int16 eQTaskType,
        unsigned int bQTaskGroup)
{
  unsigned int result; // eax

  result = bQTaskGroup | 0x20000000;
  QTask_atQTaskType[eQTaskType].bQTaskGroup = result;
  return result;
}

// source: d/0/qtask.c:5220  [anchor-hash]
void __cdecl QTask_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // ax
  unsigned __int16 v2; // ax
  unsigned __int16 v3; // ax
  unsigned __int16 v4; // ax
  struct MemPoolSegment_s *v5; // esi
  int v6; // eax
  struct MemPoolFreeItem_s *ptHead; // edx
  unsigned int i; // ecx
  struct MemPoolFreeItem_s *v9; // eax

  QTask_nProtectedQTaskStackOffset = 0;
  memset(QTask_atProtectedQTaskStack, 0, sizeof(QTask_atProtectedQTaskStack));
  QTask_nNextQTaskID = 0;
  QTask_OpenEvent();
  QTask_OpenQTaskType();
  memset32(QTask_aePropertyBitAllocated, 33554944, 8u);
  memset(QTask_anEventBit, 0xFFu, 0x1FCu);
  *(_WORD *)&QTask_anEventBit[508] = -1;
  QTask_anEventBit[510] = -1;
  QTask_eBaseQTaskType = QTask_NewQTaskType("QTask", 40, 0x200u, 0, 0);
  BaseQTaskType = QTask_GetBaseQTaskType();
  QTask_NewSystemQTaskEventFn(BaseQTaskType, 0, "Create");
  v1 = QTask_GetBaseQTaskType();
  QTask_NewSystemQTaskEventFn(v1, 4, "ParentChanged");
  v2 = QTask_GetBaseQTaskType();
  QTask_NewSystemQTaskEventNoContextFn(v2, 1, (char *)off_6A50D8);
  v3 = QTask_GetBaseQTaskType();
  QTask_NewSystemQTaskEventNoContextFn(v3, 2, "Delete");
  v4 = QTask_GetBaseQTaskType();
  QTask_NewSystemQTaskEventNoContextFn(v4, 3, "PrepareDelete");
  memset(QTask_aatQTaskFinalEvent, 0, sizeof(QTask_aatQTaskFinalEvent));
  QTask_tQTaskRefPool.nBlocks = 0;
  QTask_tQTaskRefPool.nAllocatedBlocks = 0;
  QTask_tQTaskRefPool.nAlignment = 4;
  QTask_tQTaskRefPool.nBlockSize = 12;
  QTask_tQTaskRefPool.nReAllocBlocks = 0;
  QTask_tQTaskRefPool.tMemPoolFreeList.ptHead = nullptr;
  QTask_tQTaskRefPool.tMemPoolSegmentList.ptHead = nullptr;
  v5 = (struct MemPoolSegment_s *)Mem_AllocFn(12, 4);
  v6 = 8064 * QTask_tQTaskRefPool.nBlockSize;
  v5->nByteSize = 8064 * QTask_tQTaskRefPool.nBlockSize;
  v5->pxData = Mem_AllocFn(v6, QTask_tQTaskRefPool.nAlignment);
  v5->ptNext = QTask_tQTaskRefPool.tMemPoolSegmentList.ptHead;
  ptHead = QTask_tQTaskRefPool.tMemPoolFreeList.ptHead;
  QTask_tQTaskRefPool.tMemPoolSegmentList.ptHead = v5;
  QTask_tQTaskRefPool.nBlocks += 8064;
  for ( i = 0; i < 0x1F80; ++i )
  {
    v9 = (struct MemPoolFreeItem_s *)((char *)v5->pxData + i * QTask_tQTaskRefPool.nBlockSize);
    v9->ptNext = ptHead;
    ptHead = v9;
    QTask_tQTaskRefPool.tMemPoolFreeList.ptHead = v9;
  }
  QTask_tQTaskRefList.ptHead = (struct QReference_s *)&QTask_tQTaskRefList.ptMiddle;
  QTask_tQTaskRefList.ptTail = (struct QReference_s *)&QTask_tQTaskRefList;
  QTask_tQTaskRefList.ptMiddle = nullptr;
  Symbol_Register(
    "QTASK_TYPE_UNDEFINED",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0x200,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  QTask_eQTaskNotDeletedQTaskEvent = QTask_NewQTaskEventNoContextFn(0, "QTaskNotDeallocated");
}

// source: d/0/qtask.c:5295  [anchor-hash]
void __cdecl QTask_Close()
{
  MemPool_DeInit(&QTask_tQTaskRefPool);
  QTask_DeleteQTaskEvent(0);
  QTask_DeleteQTaskEvent(1);
  QTask_DeleteQTaskEvent(2);
  QTask_DeleteQTaskEvent(3);
  QTask_DeleteQTaskEvent(4);
  QTask_DeleteQTaskEventNoContext(QTask_eQTaskNotDeletedQTaskEvent);
  QTask_DeleteQTaskType(QTask_eBaseQTaskType);
  QTask_CloseQTaskType();
  QTask_CloseEvent();
}

// source: d/0/qtask.c:5411  [size]
int __cdecl QTask_GetQTaskNotDeallocatedQTaskEvent()
{
  return QTask_eQTaskNotDeletedQTaskEvent;
}

// source: d/0/qtask.c:5439  [anchor-hash]
struct QReference_s *__cdecl QTask_NewQTaskRef(struct QTask_s *ptQTask)
{
  if ( ptQTask )
    return QReference_NewFn(ptQTask, &ptQTask->tQTaskRefList, &QTask_tQTaskRefPool);
  else
    return nullptr;
}

// source: d/0/qtask.c:5459  [anchor-mhash]
struct QReference_s *__cdecl QTask_SetQTaskRef(
        struct QReference_s *ptQTaskRef,
        struct QTask_s *ptQTask)
{
  if ( ptQTaskRef->ptNext )
    ptQTaskRef = (struct QReference_s *)Node_Remove(ptQTaskRef);
  ptQTaskRef->pxObject = ptQTask;
  if ( ptQTask != (struct QTask_s *)-20 )
    return (struct QReference_s *)List_AddTail(ptQTaskRef, (int)&ptQTask->tQTaskRefList);
  return ptQTaskRef;
}

// source: d/0/qtask.c:5476  [anchor-hash]
enum bool __cdecl QTask_IsQTaskTypeValid(int eQTaskType)
{
  if ( (unsigned int)eQTaskType > 0x1FE )
    return false;
  else
    return QTask_atQTaskType[eQTaskType].isUsed;
}

// source: d/0/qtask.c:5498  [anchor-hash]
void __cdecl QTask_DeleteQTaskAndQTaskRefSafe(struct QReference_s **pptQTaskRef)
{
  if ( *pptQTaskRef )
  {
    if ( (*pptQTaskRef)->pxObject )
      QTask_Delete((struct QTask_s *)(*pptQTaskRef)->pxObject);
    if ( *pptQTaskRef )
    {
      QReference_Delete(*pptQTaskRef, &QTask_tQTaskRefPool);
      *pptQTaskRef = nullptr;
    }
  }
}
