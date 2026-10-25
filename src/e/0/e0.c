/* e/0/e0.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: e/0/e0.c:28  [anchor-hash]
void __cdecl E0_Open()
{
  QObj_Open();
  QCamera_eFirstPersonQTaskEvent = QTask_NewQTaskEventFn(0, "FirstPerson");
  QCamera_ptFirstPersonQTaskList = QTaskList_New(256);
  DynCubeObj_Open();
  Lightsource_Open();
  Display_RegisterCallback((void (__cdecl *)())Clipping_StartFrameCallback, &Display_ptStartFrameCallback);
}
