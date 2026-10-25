/* f/2/camtask.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: f/2/camtask.c:33  [anchor-strings]
void __cdecl CamQTask_Open()
{
  unsigned __int16 BaseQTaskType; // ax

  BaseQTaskType = QTask_GetBaseQTaskType();
  CamQTask_eQTaskType = QTask_NewQTaskType("CamTask", 152, BaseQTaskType, 0, 0);
}

// source: f/2/camtask.c:50  [size]
void __cdecl CamQTask_Close()
{
  QTask_DeleteQTaskType(CamQTask_eQTaskType);
}

// source: f/2/camtask.c:66  [size]
unsigned __int16 __cdecl CamQTask_GetQTaskType()
{
  return CamQTask_eQTaskType;
}
