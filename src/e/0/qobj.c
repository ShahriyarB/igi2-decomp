/* e/0/qobj.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: e/0/qobj.c:36  [anchor-hash]
void __cdecl QObj_Open()
{
  unsigned __int16 BaseQTaskType; // ax

  QTask_NewSystemQTaskEventFn(0, 5, "Enter");
  QTask_NewSystemQTaskEventFn(0, 6, "Leave");
  QTask_NewSystemQTaskEventFn(0, 7, "SetPosition");
  QTask_NewSystemQTaskEventFn(0, 8, "GetCameraTarget");
  LOWORD(ShadowVolume_vIntensity) = QTask_NewQTaskEventFn(0, "GetObjectBoundingSphere");
  BaseQTaskType = QTask_GetBaseQTaskType();
  LOWORD(ShadowVolume_nShadow) = QTask_NewQTaskType("QObj", 88, BaseQTaskType, 0, 0);
}

// source: e/0/qobj.c:60  [anchor-hash]
void __cdecl QObj_Close()
{
  QTask_DeleteQTaskType(ShadowVolume_nShadow);
  LOWORD(ShadowVolume_nShadow) = 512;
  QTask_DeleteQTaskEvent(8);
  QTask_DeleteQTaskEvent(5);
  QTask_DeleteQTaskEvent(6);
  QTask_DeleteQTaskEvent(7);
  QTask_DeleteQTaskEvent(SLOWORD(ShadowVolume_vIntensity));
}

// source: e/0/qobj.c:86  [size]
__int16 __cdecl QObj_GetGetObjectBoundingSphereQTaskEvent()
{
  return LOWORD(ShadowVolume_vIntensity);
}

// source: e/0/qobj.c:99  [size]
void *__cdecl QObj_SetData(struct QObj_s *ptQObj, void *pxData)
{
  ptQObj->pxQData = pxData;
  return pxData;
}

// source: e/0/qobj.c:112  [size]
void *__cdecl QObj_GetData(struct QObj_s *ptQObj)
{
  return ptQObj->pxQData;
}
