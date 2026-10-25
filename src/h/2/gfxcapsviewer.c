/* h/2/gfxcapsviewer.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/gfxcapsviewer.c:46  [size]
void __cdecl GFXCapsViewer_PrintQTaskInfoHandler(struct QTask_s *ptQTask, void *pxContext)
{
  RenderMode_tActiveRenderMode.apfRenderModeMethod[Display_eGetGFXCapsMethod](&unk_8341610);
  *(_DWORD *)pxContext = &unk_8341610;
}

// source: h/2/gfxcapsviewer.c:73  [anchor-hash]
void __cdecl GFXCapsViewer_Open()
{
  unsigned __int16 v0; // si

  v0 = QTask_NewQTaskType("GFXCapsViewer", 40, 0x200u, 0, 0);
  GFXCapsViewer_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v0, Level_ePrintQTaskInfoQTaskEvent, GFXCapsViewer_PrintQTaskInfoHandler);
}

// source: h/2/gfxcapsviewer.c:91  [size]
void __cdecl GFXCapsViewer_Close()
{
  QTask_DeleteQTaskType(GFXCapsViewer_eQTaskType);
}
