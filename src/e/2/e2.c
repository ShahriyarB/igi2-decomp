/* e/2/e2.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: e/2/e2.c:28  [anchor-hash]
void __cdecl E2_Open()
{
  E1_Open();
  CubeOcclusion_Open();
  QCube_Open();
  Hazinglayers_Open();
}

// source: e/2/e2.c:52  [anchor-caller]
void __cdecl E2_Close()
{
  struct DisplayCallbackChain_s *v0; // eax
  struct DisplayCallbackChain_s *v1; // ecx
  int v2; // eax

  QTask_DeleteQTaskType(Hazinglayers_eQTaskType);
  QCube_Close();
  QTask_DeleteQTaskEvent(CubeOcclusion_eOcclusionDrawQTaskEvent);
  CubeOcclusion_eOcclusionDrawQTaskEvent = 512;
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
