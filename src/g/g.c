/* g/g.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: g/g.c:32  [anchor-hash]
void __cdecl G_Open()
{
  F_Open();
  Idle_eDeactivateQTaskEvent = QTask_NewQTaskEventFn(0, "Deactivate");
  Idle_eActivateQTaskEvent = QTask_NewQTaskEventFn(0, "Activate");
  State_eGetStateQTaskEvent = QTask_NewQTaskEventFn(0, "GetState");
  State_ptRunStateQTaskProfileRegion = nullptr;
  AnimTrigger_Open();
  Compress_aptAlgorithm[0] = &LZ77_tAlgorithm;
  Physics_ptUpdateProfileRegion = nullptr;
}

// source: g/g.c:58  [size]
void __cdecl G_Close()
{
  AnimTrigger_Close();
  QTask_DeleteQTaskEvent(State_eGetStateQTaskEvent);
  QTask_DeleteQTaskEvent(Idle_eActivateQTaskEvent);
  QTask_DeleteQTaskEvent(Idle_eDeactivateQTaskEvent);
  F_Close();
}
