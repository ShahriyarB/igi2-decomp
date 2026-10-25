/* e/1/e1.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: e/1/e1.c:28  [anchor-hash]
void __cdecl E1_Open()
{
  struct CallQueueItem_s *v0; // eax

  QObj_Open();
  QCamera_eFirstPersonQTaskEvent = QTask_NewQTaskEventFn(0, "FirstPerson");
  QCamera_ptFirstPersonQTaskList = QTaskList_New(256);
  DynCubeObj_Open();
  Lightsource_Open();
  Display_RegisterCallback((void (__cdecl *)())Clipping_StartFrameCallback, &Display_ptStartFrameCallback);
  v0 = CallQueue_atCallQueueItem;
  do
  {
    v0->ptNext = v0 + 1;
    ++v0;
  }
  while ( (int)v0 < 128876752 );
  CallQueue_atCallQueueItem[7999].ptNext = nullptr;
  CallQueue_ptFirstFreeItem = CallQueue_atCallQueueItem;
  World_Open();
}

// source: e/1/e1.c:46  [anchor-caller]
void __cdecl E1_Close()
{
  struct DisplayCallbackChain_s *v0; // eax
  struct DisplayCallbackChain_s *v1; // ecx
  int v2; // eax

  World_Close();
  v0 = Display_ptStartFrameCallback;
  v1 = nullptr;
  if ( Display_ptStartFrameCallback )
  {
    while ( (void (__cdecl *)())v0->pfCallback != Clipping_StartFrameCallback )
    {
      v1 = v0;
      v0 = v0->ptNext;
      if ( !v0 )
        goto LABEL_8;
    }
    if ( v1 )
      v1->ptNext = v0->ptNext;
    else
      Display_ptStartFrameCallback = v0->ptNext;
  }
LABEL_8:
  v2 = Lightsource_eRemoveLightsourceRenderModeMethod;
  RenderMode_atRenderModeMethod[Lightsource_eAddLightsourceRenderModeMethod].isAllocated = 0;
  RenderMode_atRenderModeMethod[v2].isAllocated = 0;
  QTask_DeleteQTaskEvent(DynCube_eDynCubeObjInGameEvalQTaskEvent);
  QTask_DeleteQTaskEvent(DynCubeObj_eDynCubeObjRegisterQTaskEvent);
  QTask_DeleteQTaskEvent(DynCubeObj_eDynCubeObjRemoveQTaskEvent);
  QTask_DeleteQTaskType(DynCubeObj_eQTaskType);
  QTask_DeleteQTaskEvent(QCamera_eFirstPersonQTaskEvent);
  QTaskList_Delete(QCamera_ptFirstPersonQTaskList);
  QTask_DeleteQTaskType(ShadowVolume_nShadow);
  LOWORD(ShadowVolume_nShadow) = 512;
  QTask_DeleteQTaskEvent(8);
  QTask_DeleteQTaskEvent(5);
  QTask_DeleteQTaskEvent(6);
  QTask_DeleteQTaskEvent(7);
  QTask_DeleteQTaskEvent(SLOWORD(ShadowVolume_vIntensity));
}
