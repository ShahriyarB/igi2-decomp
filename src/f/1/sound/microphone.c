/* f/1/sound/microphone.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: f/1/sound/microphone.c:80  [size]
void __cdecl Microphone_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[3].tQTaskChildren.ptTail = nullptr;
  ptQTask[3].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[3].ptParent = nullptr;
}

// source: f/1/sound/microphone.c:98  [size]
void __cdecl Microphone_RunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptParent; // eax
  double *v2; // eax
  double *ptMiddle; // eax
  struct QReference_s *ptHead; // esi
  double *v5; // esi
  struct QTask_s **ptTail; // eax
  struct QTaskList_s *v7; // eax
  int v8; // esi
  int v9; // edi
  struct QTask_s *v10; // ebx
  struct QTask_s *v11; // ecx
  int v12; // edx
  struct QTask_s *v13; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v15; // edx
  struct MicrophoneTriggerContext_t tMicContext; // [esp+10h] [ebp-8h] BYREF

  if ( !ptQTask[3].tQTaskChildren.ptTail )
  {
    ptParent = ptQTask[3].ptParent;
    if ( ptParent && (v2 = (double *)ptParent->tQTaskChildren.ptHead) != nullptr )
    {
      *(double *)&ptQTask[2].tQTaskRefList.ptMiddle = v2[5] - *(double *)&ptQTask[2].ptNext;
      *(double *)&ptQTask[2].ptParent = v2[6] - *(double *)&ptQTask[2].tQTaskChildren.ptHead;
      *(double *)&ptQTask[3].ptNext = v2[7] - *(double *)&ptQTask[2].tQTaskChildren.ptTail;
      qmemcpy(&ptQTask[1], (char *)v2 + 124, sizeof(struct QTask_s));
      qmemcpy(&ptQTask[2], v2 + 5, 0x18u);
    }
    else
    {
      ptMiddle = (double *)ptQTask[3].tQTaskRefList.ptMiddle;
      ptHead = ptQTask[3].tQTaskRefList.ptHead;
      *(double *)&ptQTask[2].tQTaskRefList.ptMiddle = *ptMiddle - *(double *)&ptQTask[2].ptNext;
      *(double *)&ptQTask[2].ptParent = ptMiddle[1] - *(double *)&ptQTask[2].tQTaskChildren.ptHead;
      *(double *)&ptQTask[3].ptNext = ptMiddle[2] - *(double *)&ptQTask[2].tQTaskChildren.ptTail;
      qmemcpy(&ptQTask[1], ptHead, sizeof(struct QTask_s));
      v5 = ptMiddle;
      ptTail = (struct QTask_s **)ptQTask[3].tQTaskRefList.ptTail;
      qmemcpy(&ptQTask[2], v5, 0x18u);
      ptQTask[3].tQTaskChildren.ptMiddle = *ptTail;
    }
  }
  v7 = SoundSys_ptSoundQTaskList;
  qmemcpy(&Sound_tMMicrophoneOrientation, &ptQTask[1], sizeof(Sound_tMMicrophoneOrientation));
  qmemcpy(&Sound_tMicrophonePos, &ptQTask[2], sizeof(Sound_tMicrophonePos));
  qmemcpy(&Sound_tMicrophoneSpeed, &ptQTask[2].tQTaskRefList.ptMiddle, sizeof(Sound_tMicrophoneSpeed));
  tMicContext.ptMicrophoneQTask = ptQTask;
  tMicContext.isGameRunning = 1;
  v8 = 0;
  if ( SoundSys_ptSoundQTaskList->nTask > 0 )
  {
    v9 = 8;
    do
    {
      ((void (__cdecl *)(_DWORD, struct MicrophoneTriggerContext_t *))QTask_aatQTaskFinalEvent[Microphone_eTriggerEvent][*(unsigned __int16 *)(*(int *)((char *)&v7->nTask + v9) + 36)].pfHandler)(
        *(int *)((char *)&v7->nTask + v9),
        &tMicContext);
      v7 = SoundSys_ptSoundQTaskList;
      ++v8;
      v9 += 4;
    }
    while ( v8 < SoundSys_ptSoundQTaskList->nTask );
  }
  v10 = ptQTask->tQTaskChildren.ptHead;
  if ( v10->ptNext )
  {
    v11 = ptQTask->tQTaskChildren.ptHead;
    if ( v10 )
    {
      v12 = QTask_nProtectedQTaskStackOffset;
      do
      {
        if ( v11->ptNext )
          v13 = v11->ptNext->ptNext != nullptr ? v11->ptNext : nullptr;
        else
          v13 = nullptr;
        QTask_atProtectedQTaskStack[v12].ptQTask = v13;
        pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][v11->eQTaskType].pfHandler;
        v15 = v12 + 1;
        QTask_nProtectedQTaskStackOffset = v15;
        if ( pfHandler )
        {
          pfHandler(v11);
          v15 = QTask_nProtectedQTaskStackOffset;
        }
        v11 = (struct QTask_s *)dword_849C7DC[v15];
        v12 = v15 - 1;
        QTask_nProtectedQTaskStackOffset = v12;
      }
      while ( v11 );
    }
  }
}

// source: f/1/sound/microphone.c:147  [anchor-mhash]
void __cdecl Microphone_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptParent; // eax

  ptParent = ptQTask[3].ptParent;
  if ( ptParent )
  {
    QReference_Delete((struct QReference_s *)ptParent, &QTask_tQTaskRefPool);
    ptQTask[3].ptParent = nullptr;
  }
}

// source: f/1/sound/microphone.c:167  [anchor-mhash]
struct QTask_s *__cdecl Microphone_New(
        struct QTask_s *ptQTask,
        struct World_s *ptWorld,
        struct real64x3_t *ptPos,
        struct real32x9_t *ptOrientation,
        int *pisInside)
{
  struct QTask_s *result; // eax

  result = QTask_NewFn(ptQTask, Microphone_eQTaskType, nullptr);
  result[1].ptNext = (struct QTask_s *)1065353216;
  result[1].tQTaskChildren.ptTail = (struct QTask_s *)1065353216;
  result[1].ptParent = (struct QTask_s *)1065353216;
  result[3].tQTaskChildren.ptHead = (struct QTask_s *)ptWorld;
  result[3].tQTaskRefList.ptTail = (struct QReference_s *)pisInside;
  result[1].ptPrev = nullptr;
  result[1].tQTaskChildren.ptHead = nullptr;
  result[1].tQTaskChildren.ptMiddle = nullptr;
  result[1].tQTaskRefList.ptHead = nullptr;
  result[1].tQTaskRefList.ptMiddle = nullptr;
  result[1].tQTaskRefList.ptTail = nullptr;
  *(_DWORD *)&result[1].eQTaskType = 0;
  result[3].tQTaskRefList.ptMiddle = (struct QReference_s *)ptPos;
  result[3].tQTaskRefList.ptHead = (struct QReference_s *)ptOrientation;
  return result;
}

// source: f/1/sound/microphone.c:195  [anchor-hash]
void __cdecl Microphone_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  __int16 v1; // ax
  unsigned __int16 v2; // si

  BaseQTaskType = QTask_GetBaseQTaskType();
  Microphone_eQTaskType = QTask_NewQTaskType("SoundSysMicrophone", 160, BaseQTaskType, 0, 0);
  v1 = QTask_NewQTaskEventFn(0, "MicrophoneTrigger");
  v2 = Microphone_eQTaskType;
  Microphone_eTriggerEvent = v1;
  QTask_LinkQTaskEventHandlerFn(
    Microphone_eQTaskType,
    0,
    (void (__cdecl *)(struct QTask_s *, void *))Microphone_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, 1, Microphone_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, 2, Microphone_DeleteHandler);
}

// source: f/1/sound/microphone.c:217  [size]
void __cdecl Microphone_Close()
{
  QTask_DeleteQTaskEvent(Microphone_eTriggerEvent);
  QTask_DeleteQTaskType(Microphone_eQTaskType);
}

// source: f/1/sound/microphone.c:234  [size]
unsigned __int16 __cdecl Microphone_GetQTaskType()
{
  return Microphone_eQTaskType;
}

// source: f/1/sound/microphone.c:247  [size]
__int16 __cdecl Microphone_GetTriggerQTaskEvent()
{
  return Microphone_eTriggerEvent;
}

// source: f/1/sound/microphone.c:261  [size]
struct real64x3_t *__cdecl Microphone_GetPos(struct QTask_s *ptQTask)
{
  return (struct real64x3_t *)&ptQTask[2];
}

// source: f/1/sound/microphone.c:274  [size]
enum bool __cdecl Microphone_IsInside(struct QTask_s *ptQTask)
{
  return (enum bool)ptQTask[3].tQTaskChildren.ptMiddle;
}

// source: f/1/sound/microphone.c:287  [size]
enum bool __cdecl Microphone_ForbidUpdates(
        struct QTask_s *ptQTask,
        enum bool isForbidUpdates)
{
  ptQTask[3].tQTaskChildren.ptTail = (struct QTask_s *)isForbidUpdates;
  return isForbidUpdates;
}

// source: f/1/sound/microphone.c:306  [size]
enum bool __cdecl Microphone_IsForbidUpdates(struct QTask_s *ptQTask)
{
  return (enum bool)ptQTask[3].tQTaskChildren.ptTail;
}

// source: f/1/sound/microphone.c:324  [size]
void __cdecl Microphone_Lock(struct QTask_s *ptQTask, struct QTask_s *ptModelObj)
{
  struct QTask_s *ptParent; // eax

  ptParent = ptQTask[3].ptParent;
  if ( ptParent )
  {
    QReference_Delete((struct QReference_s *)ptParent, &QTask_tQTaskRefPool);
    ptQTask[3].ptParent = nullptr;
  }
  if ( ptModelObj )
    ptQTask[3].ptParent = (struct QTask_s *)QTask_NewQTaskRef(ptModelObj);
}

// source: f/1/sound/microphone.c:347  [anchor-hash]
struct QTask_s *__cdecl Microphone_GetLockedTarget(struct QTask_s *ptQTask)
{
  struct QTask_s *ptParent; // eax

  ptParent = ptQTask[3].ptParent;
  if ( ptParent )
    return ptParent->tQTaskChildren.ptHead;
  else
    return nullptr;
}

// source: f/1/sound/microphone.c:366  [anchor-hash]
struct QTask_s *__cdecl Microphone_GetSector(struct QTask_s *ptQTask)
{
  return (struct QTask_s *)ptQTask[3].tQTaskRefList.ptTail->ptNext;
}
