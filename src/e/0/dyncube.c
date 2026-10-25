/* e/0/dyncube.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: e/0/dyncube.c:49  [size]
void __cdecl DynCubeObj_RemoveHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptHead; // eax
  int v3; // edx
  struct QTask_s *v4; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // ecx
  int v6; // edx

  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v3 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v4 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v4 = nullptr;
      QTask_atProtectedQTaskStack[v3].ptQTask = v4;
      pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRemoveQTaskEvent][ptHead->eQTaskType].pfHandler;
      v6 = v3 + 1;
      QTask_nProtectedQTaskStackOffset = v6;
      if ( pfHandler )
      {
        pfHandler(ptHead, pxContext);
        v6 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v6];
      v3 = v6 - 1;
      QTask_nProtectedQTaskStackOffset = v3;
    }
    while ( ptHead );
  }
  World_RemoveDynCubeObj(*(struct World_s **)pxContext, (struct DynCubeObj_s *)ptQTask);
}

// source: e/0/dyncube.c:74  [anchor-mhash]
void __cdecl DynCubeObj_RegisterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptHead; // eax
  int v3; // edx
  struct QTask_s *v4; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // ecx
  int v6; // edx

  World_RegisterDynCubeObjFirstTimeRadius(
    *((struct World_s **)pxContext + 1),
    (struct DynCubeObj_s *)ptQTask,
    (struct real64x3_t *)&ptQTask[1],
    *(float *)&ptQTask[1].eQTaskType,
    *((enum DynCubeTreeCategory_enum *)pxContext + 2));
  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v3 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v4 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v4 = nullptr;
      QTask_atProtectedQTaskStack[v3].ptQTask = v4;
      pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRegisterQTaskEvent][ptHead->eQTaskType].pfHandler;
      v6 = v3 + 1;
      QTask_nProtectedQTaskStackOffset = v6;
      if ( pfHandler )
      {
        pfHandler(ptHead, pxContext);
        v6 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v6];
      v3 = v6 - 1;
      QTask_nProtectedQTaskStackOffset = v3;
    }
    while ( ptHead );
  }
}

// source: e/0/dyncube.c:107  [size]
enum bool __cdecl DynCubeObj_IsRegistered(struct DynCubeObj_s *ptDynCubeObj)
{
  return ptDynCubeObj->ptDynCubeObjTreeItem != nullptr;
}

// source: e/0/dyncube.c:122  [size]
void __cdecl DynCubeObj_AssertRemovedBeforeDelete(struct QTask_s *ptQTask)
{
  ;
}

// source: e/0/dyncube.c:141  [size]
__int16 __cdecl DynCubeObj_GetRegisterQTaskEvent()
{
  return DynCubeObj_eDynCubeObjRegisterQTaskEvent;
}

// source: e/0/dyncube.c:156  [size]
__int16 __cdecl DynCubeObj_GetRemoveQTaskEvent()
{
  return DynCubeObj_eDynCubeObjRemoveQTaskEvent;
}

// source: e/0/dyncube.c:171  [size]
__int16 __cdecl DynCube_GetDynCubeObjInGameEvalQTaskEvent()
{
  return DynCube_eDynCubeObjInGameEvalQTaskEvent;
}

// source: e/0/dyncube.c:186  [anchor-hash]
void __cdecl DynCubeObj_Open()
{
  __int16 v0; // ax
  unsigned __int16 v1; // si

  DynCubeObj_eQTaskType = QTask_NewQTaskType("DynCubeObj", 112, ShadowVolume_nShadow, 0, 0);
  DynCube_eDynCubeObjInGameEvalQTaskEvent = QTask_NewQTaskEventFn(0x200u, "DynCubeObjInGameEval");
  DynCubeObj_eDynCubeObjRegisterQTaskEvent = QTask_NewQTaskEventFn(0x200u, "DynCubeObjRegister");
  v0 = QTask_NewQTaskEventFn(0x200u, "DynCubeObjRemove");
  v1 = DynCubeObj_eQTaskType;
  DynCubeObj_eDynCubeObjRemoveQTaskEvent = v0;
  QTask_LinkQTaskEventHandlerFn(DynCubeObj_eQTaskType, v0, DynCubeObj_RemoveHandler);
  QTask_LinkQTaskEventHandlerFn(v1, DynCubeObj_eDynCubeObjRegisterQTaskEvent, DynCubeObj_RegisterHandler);
}

// source: e/0/dyncube.c:214  [size]
void __cdecl DynCubeObj_Close()
{
  QTask_DeleteQTaskEvent(DynCube_eDynCubeObjInGameEvalQTaskEvent);
  QTask_DeleteQTaskEvent(DynCubeObj_eDynCubeObjRegisterQTaskEvent);
  QTask_DeleteQTaskEvent(DynCubeObj_eDynCubeObjRemoveQTaskEvent);
  QTask_DeleteQTaskType(DynCubeObj_eQTaskType);
}
