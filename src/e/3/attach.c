/* e/3/attach.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: e/3/attach.c:43  [size]
__int16 __cdecl Attach_GetAttachEvent()
{
  return Attach_eAttachEvent;
}

// source: e/3/attach.c:58  [size]
int __cdecl Attach_GetUpdateAttachmentEvent()
{
  return Attach_eUpdateAttachmentEvent;
}

// source: e/3/attach.c:74  [anchor-hash]
void __cdecl Attach_Open()
{
  Attach_eAttachEvent = QTask_NewQTaskEventFn(0, "Attach");
  Attach_eUpdateAttachmentEvent = QTask_NewQTaskEventNoContextFn(0, "UpdateAttachment");
}

// source: e/3/attach.c:90  [size]
void __cdecl Attach_Close()
{
  QTask_DeleteQTaskEvent(Attach_eAttachEvent);
  QTask_DeleteQTaskEventNoContext(Attach_eUpdateAttachmentEvent);
}
