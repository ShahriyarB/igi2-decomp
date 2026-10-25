/* h/2/rundelayed.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/rundelayed.c:40  [anchor-hash]
struct QTask_s *__cdecl RunDelayed_DelayQTask(struct QTask_s *ptQTask)
{
  struct QReference_s *v1; // eax

  v1 = QTask_NewQTaskRef(ptQTask);
  return (struct QTask_s *)QVector_AddElement(RunDelayed_ptRunDelayedQTaskRefVector, v1);
}

// source: h/2/rundelayed.c:57  [anchor-hash]
void __cdecl RunDelayed_Run()
{
  struct QVector_s *v0; // esi
  unsigned int v1; // ebx
  bool v2; // zf
  struct MemPoolFreeItem_s *v3; // edi
  struct MemPoolFreeItem_s *ptNext; // eax
  int v5; // eax

  v0 = RunDelayed_ptRunDelayedQTaskRefVector;
  v1 = 0;
  v2 = RunDelayed_ptRunDelayedQTaskRefVector->tPrivate.nElements == 0;
  if ( RunDelayed_ptRunDelayedQTaskRefVector->tPrivate.nElements )
  {
    do
    {
      v3 = (struct MemPoolFreeItem_s *)v0->tPrivate.papxElement[v1];
      ptNext = v3[2].ptNext;
      if ( ptNext )
      {
        ((void (__cdecl *)(struct MemPoolFreeItem_s *))QTask_aatQTaskFinalEvent[RunDelayed_eQTaskEvent][LOWORD(ptNext[9].ptNext)].pfHandler)(v3[2].ptNext);
        v0 = RunDelayed_ptRunDelayedQTaskRefVector;
      }
      if ( v3->ptNext )
        Node_Remove(v3);
      --QTask_tQTaskRefPool.nAllocatedBlocks;
      v3->ptNext = QTask_tQTaskRefPool.tMemPoolFreeList.ptHead;
      QTask_tQTaskRefPool.tMemPoolFreeList.ptHead = v3;
      ++v1;
    }
    while ( v1 < v0->tPrivate.nElements );
    v2 = v0->tPrivate.nElements == 0;
  }
  if ( !v2 )
  {
    do
    {
      v5 = v0->tPrivate.nElements - 1;
      v2 = v0->tPrivate.nElements == 1;
      v0->tPrivate.nElements = v5;
      if ( !v2 )
      {
        if ( v0->tPrivate.isStrictOrder )
        {
          memmove(v0->tPrivate.papxElement, v0->tPrivate.papxElement + 1, 4 * v5);
          v0 = RunDelayed_ptRunDelayedQTaskRefVector;
        }
        else
        {
          *v0->tPrivate.papxElement = v0->tPrivate.papxElement[v5];
        }
      }
    }
    while ( v0->tPrivate.nElements );
  }
}

// source: h/2/rundelayed.c:89  [size]
int __cdecl RunDelayed_GetQTaskEvent()
{
  return RunDelayed_eQTaskEvent;
}

// source: h/2/rundelayed.c:102  [anchor-hash]
void __cdecl RunDelayed_Open()
{
  struct QVector_s *v0; // eax

  RunDelayed_eQTaskEvent = QTask_NewQTaskEventNoContextFn(0, "RunDelayed");
  v0 = (struct QVector_s *)Mem_AllocFn(24, 4);
  v0->tPrivate.nArraySize = 0;
  v0->tPrivate.nElements = 0;
  v0->tPrivate.isPrivateMem = false;
  v0->tPrivate.papxElement = nullptr;
  v0->tPrivate.isStrictOrder = false;
  v0->tPrivate.nReallocSize = 32;
  RunDelayed_ptRunDelayedQTaskRefVector = v0;
}

// source: h/2/rundelayed.c:116  [size]
void __cdecl RunDelayed_Close()
{
  QTask_DeleteQTaskEventNoContext(RunDelayed_eQTaskEvent);
  QVector_Delete(RunDelayed_ptRunDelayedQTaskRefVector);
}
