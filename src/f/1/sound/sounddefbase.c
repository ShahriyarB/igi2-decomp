/* f/1/sound/sounddefbase.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: f/1/sound/sounddefbase.c:74  [size]
void __cdecl SoundDefBase_DeleteHandler(struct QTask_s *ptQTask)
{
  ;
}

void __cdecl sub_54E730(struct QTaskList_s *ptQTaskList)
{
  if ( !ptQTaskList[3].nMaxTask )
  {
    ptQTaskList[3].nMaxTask = 1;
    QTaskList_Register(SoundSys_ptSoundQTaskList, ptQTaskList);
  }
}

void __cdecl sub_54E750(struct QTask_s *ptQTask)
{
  struct QTaskList_s *v1; // eax

  if ( ptQTask[1].ptNext )
  {
    v1 = SoundSys_ptSoundQTaskList;
    ptQTask[1].ptNext = nullptr;
    QTaskList_Remove(v1, ptQTask);
  }
}

// source: f/1/sound/sounddefbase.c:99  [size]
void __cdecl SoundDefBase_SetFalloffScale(struct QTask_s *ptQTask, float vFalloffScale)
{
  *(float *)&ptQTask[1].ptPrev = vFalloffScale;
}

// source: f/1/sound/sounddefbase.c:117  [size]
unsigned __int16 __cdecl SoundDefBase_GetQTaskType()
{
  return SoundDefBase_eQTaskType;
}

// source: f/1/sound/sounddefbase.c:130  [anchor-hash]
void __cdecl SoundDefBase_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("SoundDefBase", 56, BaseQTaskType, 0, 0);
  SoundDefBase_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 0, (void (__cdecl *)(struct QTask_s *, void *))sub_54E6F0);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, (void (__cdecl *)(struct QTask_s *))SoundDefBase_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    DynCubeObj_eDynCubeObjRemoveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))sub_54E750);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    DynCubeObj_eDynCubeObjRegisterQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))sub_54E730);
}

// source: f/1/sound/sounddefbase.c:159  [size]
void __cdecl SoundDefBase_Close()
{
  QTask_DeleteQTaskType(SoundDefBase_eQTaskType);
}
