/* e/0/qcamera.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: e/0/qcamera.c:44  [anchor-hash]
void __cdecl QCamera_Open()
{
  QCamera_eFirstPersonQTaskEvent = QTask_NewQTaskEventFn(0, "FirstPerson");
  QCamera_ptFirstPersonQTaskList = QTaskList_New(256);
}

// source: e/0/qcamera.c:63  [size]
void __cdecl QCamera_Close()
{
  QTask_DeleteQTaskEvent(QCamera_eFirstPersonQTaskEvent);
  QTaskList_Delete(QCamera_ptFirstPersonQTaskList);
}

// source: e/0/qcamera.c:80  [size]
__int16 __cdecl QCamera_GetFirstPersonQTaskEvent()
{
  return QCamera_eFirstPersonQTaskEvent;
}

// source: e/0/qcamera.c:94  [size]
struct QTaskList_s *__cdecl QCamera_GetFirstPersonQTaskList()
{
  return QCamera_ptFirstPersonQTaskList;
}

// source: e/0/qcamera.c:120  [anchor-callee]
void __cdecl QCamera_Set(
        struct QCamera_s *ptQCamera,
        struct real64x3_t *ptPos,
        struct real32x9_t *ptOrientation,
        float vFOVX,
        float vHeightFactor,
        float vPriority,
        int nFrameNumber,
        struct QTask_s *ptSetCameraQTask,
        float vTime,
        int isFirstPerson)
{
  int nTimesSet; // ecx
  int v11; // eax
  int v12; // ecx
  struct QTaskList_s *v13; // eax
  int v14; // esi
  int v15; // edi

  nTimesSet = ptQCamera->nTimesSet;
  ++ptQCamera->ptSetCameraQTask;
  if ( nFrameNumber > nTimesSet )
  {
    ptQCamera->nTimesSet = nFrameNumber;
    ptQCamera->nLastFrameNumber = -1082130432;
  }
  if ( vPriority >= (double)*(float *)&ptQCamera->nLastFrameNumber )
  {
    qmemcpy(&ptQCamera->tPos, ptPos, sizeof(ptQCamera->tPos));
    qmemcpy(ptQCamera, ptOrientation, 0x28u);
    ptQCamera->vFOVX = vFOVX;
    LODWORD(ptQCamera->vTime) = ptSetCameraQTask;
    v11 = LODWORD(vPriority);
    ptQCamera->vPriority = vHeightFactor;
    v12 = LODWORD(vTime);
    ptQCamera->nLastFrameNumber = v11;
    v13 = QCamera_ptFirstPersonQTaskList;
    ptQCamera->isFirstPerson = v12;
    LODWORD(ptQCamera[1].tMatrix.tX.vX) = isFirstPerson;
    vPriority = *(float *)&isFirstPerson;
    v14 = 0;
    if ( v13->nTask > 0 )
    {
      v15 = 8;
      do
      {
        ((void (__cdecl *)(_DWORD, float *))QTask_aatQTaskFinalEvent[QCamera_eFirstPersonQTaskEvent][*(unsigned __int16 *)(*(int *)((char *)&v13->nTask + v15) + 36)].pfHandler)(
          *(int *)((char *)&v13->nTask + v15),
          &vPriority);
        v13 = QCamera_ptFirstPersonQTaskList;
        ++v14;
        v15 += 4;
      }
      while ( v14 < QCamera_ptFirstPersonQTaskList->nTask );
    }
  }
}

// source: e/0/qcamera.c:184  [size~]
struct QCamera_s *__cdecl QCamera_Clear(struct QCamera_s *ptQCamera)
{
  ptQCamera->ptSetCameraQTask = nullptr;
  ptQCamera->nLastFrameNumber = -1082130432;
  ptQCamera->tPos.vX = 0.0;
  ptQCamera->tPos.vY = 0.0;
  ptQCamera->tPos.vZ = 0.0;
  ptQCamera->tMatrix.tX.vX = 1.0;
  ptQCamera->tMatrix.tX.vY = 0.0;
  ptQCamera->tMatrix.tX.vZ = 0.0;
  ptQCamera->tMatrix.tY.vX = 0.0;
  ptQCamera->tMatrix.tY.vY = 1.0;
  ptQCamera->tMatrix.tY.vZ = 0.0;
  ptQCamera->tMatrix.tZ.vX = 0.0;
  ptQCamera->tMatrix.tZ.vY = 0.0;
  ptQCamera->tMatrix.tZ.vZ = 1.0;
  ptQCamera->tMatrix.nOps = 0;
  ptQCamera->vHeightFactor = 409.6000061035156;
  return ptQCamera;
}

// source: e/0/qcamera.c:209  [size~]
struct QCamera_s *__cdecl QCamera_Init(struct QCamera_s *ptQCamera)
{
  ptQCamera->ptSetCameraQTask = nullptr;
  ptQCamera->nLastFrameNumber = -1082130432;
  ptQCamera->tPos.vX = 0.0;
  ptQCamera->tPos.vY = 0.0;
  ptQCamera->tPos.vZ = 0.0;
  ptQCamera->tMatrix.tX.vX = 1.0;
  ptQCamera->tMatrix.tX.vY = 0.0;
  ptQCamera->tMatrix.tX.vZ = 0.0;
  ptQCamera->tMatrix.tY.vX = 0.0;
  ptQCamera->tMatrix.tY.vY = 1.0;
  ptQCamera->tMatrix.tY.vZ = 0.0;
  ptQCamera->tMatrix.tZ.vX = 0.0;
  ptQCamera->tMatrix.tZ.vY = 0.0;
  ptQCamera->tMatrix.tZ.vZ = 1.0;
  ptQCamera->tMatrix.nOps = 0;
  ptQCamera->vHeightFactor = 409.6000061035156;
  return ptQCamera;
}
