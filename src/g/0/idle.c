/* g/0/idle.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: g/0/idle.c:39  [anchor-hash]
void __cdecl Idle_Open()
{
  Idle_eDeactivateQTaskEvent = QTask_NewQTaskEventFn(0, "Deactivate");
  Idle_eActivateQTaskEvent = QTask_NewQTaskEventFn(0, "Activate");
}

// source: g/0/idle.c:58  [size]
void __cdecl Idle_Close()
{
  QTask_DeleteQTaskEvent(Idle_eActivateQTaskEvent);
  QTask_DeleteQTaskEvent(Idle_eDeactivateQTaskEvent);
}

// source: g/0/idle.c:75  [size]
__int16 __cdecl Idle_GetDeactivateQTaskEvent()
{
  return Idle_eDeactivateQTaskEvent;
}

// source: g/0/idle.c:91  [size]
__int16 __cdecl Idle_GetActivateQTaskEvent()
{
  return Idle_eActivateQTaskEvent;
}

// source: g/0/idle.c:107  [size]
struct Idle_t *__cdecl Idle_Init(struct Idle_t *ptIdle, struct QTask_s *ptQTask)
{
  ptIdle->isIdle = 0;
  ptIdle->ptOriginalParent = ptQTask->ptParent;
  ptIdle->nTime = 0;
  return ptIdle;
}

// source: g/0/idle.c:126  [anchor-mhash]
int __cdecl Idle_Deactivate(struct Idle_t *ptIdle, struct QTask_s *ptQTask)
{
  int v2; // eax
  bool v3; // sf
  void (__cdecl *pfHandler)(struct QTask_s *, _DWORD); // eax

  v2 = ptIdle->nTime + 1;
  v3 = ptIdle->nTime - 9 < 0;
  ptIdle->nTime = v2;
  if ( v3 ^ __OFSUB__(v2, 10) | (v2 == 10) )
    return 0;
  pfHandler = (void (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[Idle_eDeactivateQTaskEvent][ptQTask->eQTaskType].pfHandler;
  if ( pfHandler )
    pfHandler(ptQTask, 0);
  ptIdle->isIdle = 1;
  return 1;
}

// source: g/0/idle.c:160  [anchor-mhash]
int __cdecl Idle_Activate(struct Idle_t *ptIdle, struct QTask_s *ptQTask)
{
  bool v2; // zf
  struct QTask_s *ptOriginalParent; // esi

  v2 = ptIdle->isIdle == 0;
  ptIdle->nTime = 0;
  if ( !v2 )
    return 0;
  ptOriginalParent = ptIdle->ptOriginalParent;
  ptIdle->isIdle = 0;
  QTask_ChangeParent(ptQTask, ptOriginalParent);
  return 1;
}

// source: g/0/idle.c:191  [size]
struct QTask_s *__cdecl Idle_ChangeOriginalParent(
        struct Idle_t *ptIdle,
        struct QTask_s *ptNewParent)
{
  ptIdle->ptOriginalParent = ptNewParent;
  return ptNewParent;
}
