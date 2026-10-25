/* f/2/freecameratask.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: f/2/freecameratask.c:58  [size]
void __cdecl FreeCameraQTask_DeleteHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: f/2/freecameratask.c:73  [size]
void __cdecl FreeCameraQTask_RunHandler(struct QTask_s *ptQTask)
{
  if ( LOBYTE(ptQTask[3].tQTaskRefList.ptTail) )
    QCamera_Set(
      (struct QCamera_s *)ptQTask[3].ptParent,
      (struct real64x3_t *)&ptQTask[2],
      (struct real32x9_t *)&ptQTask[1],
      *(float *)&ptQTask[2].tQTaskRefList.ptMiddle,
      1.0,
      100.0,
      Screen_nFrameNumber,
      nullptr,
      0.0,
      0);
}

// source: f/2/freecameratask.c:110  [anchor-strings]
void __cdecl FreeCameraQTask_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("FreeCamera", 160, BaseQTaskType, 0, 0);
  FreeCameraQTask_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, FreeCameraQTask_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, (void (__cdecl *)(struct QTask_s *))FreeCameraQTask_DeleteHandler);
}

// source: f/2/freecameratask.c:129  [size]
void __cdecl FreeCameraQTask_Close()
{
  QTask_DeleteQTaskType(FreeCameraQTask_eQTaskType);
}

// source: f/2/freecameratask.c:145  [anchor-mhash]
struct QTask_s *__cdecl FreeCameraQTask_New(struct QTask_s *ptParent, struct QCamera_s *ptQCamera)
{
  struct QTask_s *result; // eax

  result = QTask_NewFn(ptParent, FreeCameraQTask_eQTaskType, nullptr);
  result[3].ptParent = (struct QTask_s *)ptQCamera;
  LOBYTE(result[3].tQTaskRefList.ptTail) = 0;
  result[1].ptPrev = nullptr;
  result[1].tQTaskChildren.ptHead = nullptr;
  result[1].tQTaskChildren.ptMiddle = nullptr;
  result[1].tQTaskRefList.ptHead = nullptr;
  result[1].tQTaskRefList.ptMiddle = nullptr;
  result[1].tQTaskRefList.ptTail = nullptr;
  *(_DWORD *)&result[1].eQTaskType = 0;
  result[2].ptNext = nullptr;
  result[2].ptPrev = nullptr;
  result[2].tQTaskChildren.ptHead = nullptr;
  result[2].tQTaskChildren.ptMiddle = nullptr;
  result[2].tQTaskChildren.ptTail = nullptr;
  result[2].tQTaskRefList.ptHead = nullptr;
  result[3].tQTaskRefList.ptMiddle = (struct QReference_s *)1;
  result[1].ptNext = (struct QTask_s *)1065353216;
  result[1].tQTaskChildren.ptTail = (struct QTask_s *)1065353216;
  result[1].ptParent = (struct QTask_s *)1065353216;
  result[2].tQTaskRefList.ptMiddle = (struct QReference_s *)1065353216;
  return result;
}
