/* e/1/callqueue.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: e/1/callqueue.c:50  [anchor-hash]
struct CallQueue_t *__cdecl CallQueue_Init(struct CallQueue_t *ptQueue)
{
  ptQueue->pptLast = &ptQueue->ptFirst;
  ptQueue->ptFirst = nullptr;
  return ptQueue;
}

// source: e/1/callqueue.c:66  [anchor-callee]
void __cdecl CallQueue_QueueEvent(
        struct CallQueue_t *ptQueue,
        struct QTask_s *ptQTask,
        __int16 eQTaskEvent,
        void *pxContext)
{
  struct CallQueueItem_s *v4; // eax

  v4 = CallQueue_ptFirstFreeItem;
  CallQueue_ptFirstFreeItem = CallQueue_ptFirstFreeItem->ptNext;
  v4->ptQTask = ptQTask;
  v4->uEvent.eQTaskEvent = eQTaskEvent;
  v4->isNoContext = false;
  v4->pxContext = pxContext;
  v4->ptNext = nullptr;
  *ptQueue->pptLast = v4;
  ptQueue->pptLast = &v4->ptNext;
}

// source: e/1/callqueue.c:98  [anchor-mhash]
void __cdecl CallQueue_QueueEventNoContext(
        struct CallQueue_t *ptQueue,
        struct QTask_s *ptQTask,
        int eQTaskEvent)
{
  struct CallQueueItem_s *v3; // eax

  v3 = CallQueue_ptFirstFreeItem;
  CallQueue_ptFirstFreeItem = CallQueue_ptFirstFreeItem->ptNext;
  v3->ptQTask = ptQTask;
  v3->uEvent.eQTaskEventNoContext = eQTaskEvent;
  v3->isNoContext = true;
  v3->pxContext = nullptr;
  v3->ptNext = nullptr;
  *ptQueue->pptLast = v3;
  ptQueue->pptLast = &v3->ptNext;
}

// source: e/1/callqueue.c:130  [anchor-mhash]
void __cdecl CallQueue_PushEvent(
        struct CallQueue_t *ptQueue,
        struct QTask_s *ptQTask,
        __int16 eQTaskEvent,
        void *pxContext)
{
  struct CallQueueItem_s *v4; // eax
  struct CallQueueItem_s *ptFirst; // ecx

  v4 = CallQueue_ptFirstFreeItem;
  CallQueue_ptFirstFreeItem = CallQueue_ptFirstFreeItem->ptNext;
  v4->ptQTask = ptQTask;
  v4->uEvent.eQTaskEvent = eQTaskEvent;
  v4->isNoContext = false;
  v4->pxContext = pxContext;
  ptFirst = ptQueue->ptFirst;
  if ( !ptQueue->ptFirst )
    ptQueue->pptLast = &v4->ptNext;
  v4->ptNext = ptFirst;
  ptQueue->ptFirst = v4;
}

// source: e/1/callqueue.c:165  [anchor-mhash]
void __cdecl CallQueue_PushEventNoContext(
        struct CallQueue_t *ptQueue,
        struct QTask_s *ptQTask,
        int eQTaskEvent)
{
  struct CallQueueItem_s *v3; // eax
  struct CallQueueItem_s *ptFirst; // ecx

  v3 = CallQueue_ptFirstFreeItem;
  CallQueue_ptFirstFreeItem = CallQueue_ptFirstFreeItem->ptNext;
  v3->ptQTask = ptQTask;
  v3->uEvent.eQTaskEventNoContext = eQTaskEvent;
  v3->isNoContext = true;
  v3->pxContext = nullptr;
  ptFirst = ptQueue->ptFirst;
  if ( !ptQueue->ptFirst )
    ptQueue->pptLast = &v3->ptNext;
  v3->ptNext = ptFirst;
  ptQueue->ptFirst = v3;
}

// source: e/1/callqueue.c:201  [anchor-callee]
void __cdecl CallQueue_CallHandlers(struct CallQueue_t *ptQueue)
{
  struct CallQueueItem_s *ptFirst; // esi
  struct QTask_s *ptQTask; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // ecx
  void (__cdecl *v4)(struct QTask_s *, void *); // ecx
  struct CallQueueItem_s *ptNext; // eax
  bool v6; // zf

  ptFirst = ptQueue->ptFirst;
  if ( ptQueue->ptFirst )
  {
    do
    {
      ptQTask = ptFirst->ptQTask;
      if ( ptFirst->isNoContext )
      {
        pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[ptFirst->uEvent.eQTaskEventNoContext][ptQTask->eQTaskType].pfHandler;
        if ( pfHandler )
          pfHandler(ptFirst->ptQTask);
      }
      else
      {
        v4 = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[ptFirst->uEvent.eQTaskEvent][ptQTask->eQTaskType].pfHandler;
        if ( v4 )
          v4(ptQTask, ptFirst->pxContext);
      }
      ptNext = ptFirst->ptNext;
      v6 = ptFirst->ptNext == nullptr;
      ptFirst->ptNext = CallQueue_ptFirstFreeItem;
      CallQueue_ptFirstFreeItem = ptFirst;
      ptFirst = ptNext;
    }
    while ( !v6 );
  }
  ptQueue->pptLast = &ptQueue->ptFirst;
  ptQueue->ptFirst = nullptr;
}

// override: written as the retail instructions in support/qtask_asm.c (the handlers it calls
// read a second argument the retail stack layout supplies; see that file)

// source: e/1/callqueue.c:293  [anchor-hash]
void __cdecl CallQueue_Empty(struct CallQueue_t *ptQueue)
{
  struct CallQueueItem_s *ptFirst; // eax
  struct CallQueueItem_s *v2; // edx
  struct CallQueueItem_s *ptNext; // ecx
  bool v4; // zf

  ptFirst = ptQueue->ptFirst;
  if ( ptQueue->ptFirst )
  {
    v2 = CallQueue_ptFirstFreeItem;
    do
    {
      ptNext = ptFirst->ptNext;
      v4 = ptFirst->ptNext == nullptr;
      ptFirst->ptNext = v2;
      v2 = ptFirst;
      CallQueue_ptFirstFreeItem = ptFirst;
      ptFirst = ptNext;
    }
    while ( !v4 );
  }
  ptQueue->pptLast = &ptQueue->ptFirst;
  ptQueue->ptFirst = nullptr;
}

// source: e/1/callqueue.c:322  [anchor-hash]
void __cdecl CallQueue_Open()
{
  struct CallQueueItem_s *v0; // eax

  v0 = CallQueue_atCallQueueItem;
  do
  {
    v0->ptNext = v0 + 1;
    ++v0;
  }
  while ( (int)v0 < 128876752 );
  CallQueue_atCallQueueItem[7999].ptNext = nullptr;
  CallQueue_ptFirstFreeItem = CallQueue_atCallQueueItem;
}

// source: e/1/callqueue.c:344  [size]
void __cdecl CallQueue_Close()
{
  ;
}
