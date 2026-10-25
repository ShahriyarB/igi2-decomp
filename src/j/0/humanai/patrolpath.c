/* j/0/humanai/patrolpath.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/humanai/patrolpath.c:67  [size]
struct PatrolPath_t *__cdecl PatrolPath_GetPatrolPathFromNode(struct Node_s *ptNode)
{
  return (struct PatrolPath_t *)&ptNode[-14];
}

// source: j/0/humanai/patrolpath.c:193  [anchor-hash]
void __cdecl PatrolPath_RegisterCommands()
{
  int i; // esi

  for ( i = 0; i < 13; ++i )
    Symbol_Register(
      PatrolPath_azCommandNames[i],
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
      (void *)(i - 1),
      4,
      QSCRIPT_SYMBOLCLASS_CONSTANT,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}

// source: j/0/humanai/patrolpath.c:213  [anchor-hash]
int __cdecl PatrolPath_GetPatrolPathLength(struct PatrolPath_t *ptPatrolPath)
{
  struct QTask_s *v1; // ecx
  int result; // eax

  v1 = ptPatrolPath->tDynCubeObj.tQObj.tQTask.tQTaskChildren.ptHead->ptNext != nullptr
     ? ptPatrolPath->tDynCubeObj.tQObj.tQTask.tQTaskChildren.ptHead
     : nullptr;
  result = 0;
  if ( v1 )
  {
    do
    {
      v1 = v1->ptNext;
      ++result;
    }
    while ( v1 && v1->ptNext );
  }
  return result;
}

// source: j/0/humanai/patrolpath.c:241  [anchor-mhash]
struct PatrolPath_t *__cdecl PatrolPath_GetPatrolPathQTaskFromID(int nID)
{
  struct Node_s *ptHead; // eax
  struct Node_s *ptNext; // ecx
  struct Node_s *v3; // esi
  struct PatrolPath_t *result; // eax

  ptHead = PatrolPath_tPatrolPathList.ptHead;
  ptNext = PatrolPath_tPatrolPathList.ptHead->ptNext;
  if ( !PatrolPath_tPatrolPathList.ptHead->ptNext )
    return nullptr;
  while ( 1 )
  {
    v3 = ptHead[1].ptNext;
    result = (struct PatrolPath_t *)&ptHead[-14];
    if ( v3 == (struct Node_s *)nID )
      break;
    ptHead = ptNext;
    ptNext = ptNext->ptNext;
    if ( !ptNext )
      return nullptr;
  }
  return result;
}

// source: j/0/humanai/patrolpath.c:270  [anchor-callee]
struct QTask_s *__cdecl PatrolPath_ScanToOffset(
        struct PatrolPathControl_t *ptPatrolPathControl,
        int nOffset)
{
  struct QTask_s *result; // eax
  int i; // edx

  result = ptPatrolPathControl->ptPatrolPathQTask->tQTaskChildren.ptHead->ptNext != nullptr
         ? ptPatrolPathControl->ptPatrolPathQTask->tQTaskChildren.ptHead
         : nullptr;
  for ( i = 0; result; ++i )
  {
    if ( i >= nOffset )
      break;
    if ( result[1].ptPrev == (struct QTask_s *)6 )
      ptPatrolPathControl->ptLastEndCommandQTask = result;
    result = result->ptNext ? (result->ptNext->ptNext != nullptr ? result->ptNext : nullptr) : nullptr;
  }
  return result;
}

// source: j/0/humanai/patrolpath.c:588  [anchor-mhash]
void __cdecl PatrolPath_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[3].ptNext = (struct QTask_s *)-1;
  LOBYTE(ptQTask[3].tQTaskChildren.ptHead) = 0;
  memset(&ptQTask[1], 0, 0x48u);
  ptQTask[2].tQTaskRefList.ptTail = (struct QReference_s *)5;
  *(_DWORD *)&ptQTask[2].eQTaskType = 0;
  ptQTask[2].ptParent = nullptr;
}

// source: j/0/humanai/patrolpath.c:622  [size]
void __cdecl PatrolPath_DeleteHandler(struct QTask_s *ptQTask)
{
  if ( LOBYTE(ptQTask[3].tQTaskChildren.ptHead) )
    Node_Remove((_DWORD **)&ptQTask[2].ptParent);
}

// source: j/0/humanai/patrolpath.c:650  [size]
void __cdecl PatrolPath_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = PatrolPath_ptParameterList;
}

// source: j/0/humanai/patrolpath.c:666  [anchor-mhash]
void __cdecl PatrolPath_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // esi
  struct QReference_s *v3; // eax
  _DWORD **v4; // eax

  v2 = 0;
  while ( 1 )
  {
    v3 = Level_atLevelQTaskID[v2];
    if ( v3 )
    {
      if ( v3->pxObject == ptQTask )
        break;
    }
    if ( ++v2 >= 4096 )
      return;
  }
  if ( v2 != -1 )
  {
    if ( LOBYTE(ptQTask[3].tQTaskChildren.ptHead) )
    {
      v4 = Node_Remove((_DWORD **)&ptQTask[2].ptParent);
      *(_DWORD *)&ptQTask[2].eQTaskType = 0;
      *v4 = nullptr;
    }
    ptQTask[3].ptNext = (struct QTask_s *)v2;
    List_AddTail(&ptQTask[2].ptParent, (int)&PatrolPath_tPatrolPathList);
    LOBYTE(ptQTask[3].tQTaskChildren.ptHead) = 1;
  }
}

// source: j/0/humanai/patrolpath.c:701  [anchor-mhash]
void __cdecl PatrolPath_UpdateInternalDataAfterLoadHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *v1; // eax
  struct QTask_s *v2; // ecx

  v1 = ptQTask->tQTaskChildren.ptHead->ptNext != nullptr ? ptQTask->tQTaskChildren.ptHead : nullptr;
  v2 = nullptr;
  if ( v1 )
  {
    do
    {
      v1 = v1->ptNext;
      v2 = (struct QTask_s *)((char *)v2 + 1);
    }
    while ( v1 && v1->ptNext );
  }
  ptQTask[3].ptPrev = v2;
}

// source: j/0/humanai/patrolpath.c:746  [anchor-hash]
void __cdecl PatrolPath_Open()
{
  unsigned __int16 v0; // si

  PatrolPath_tPatrolPathList.ptHead = (struct Node_s *)&PatrolPath_tPatrolPathList.ptMiddle;
  PatrolPath_tPatrolPathList.ptTail = (struct Node_s *)&PatrolPath_tPatrolPathList;
  PatrolPath_tPatrolPathList.ptMiddle = nullptr;
  v0 = QTask_NewQTaskType("PatrolPath", 136, DynCubeObj_eQTaskType, 0, 0);
  PatrolPath_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 0, PatrolPath_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, PatrolPath_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v0, DynCubeObj_eDynCubeObjRegisterQTaskEvent, nullptr);
  QTask_LinkQTaskEventHandlerFn(v0, DynCubeObj_eDynCubeObjRemoveQTaskEvent, nullptr);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))PatrolPath_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, PatrolPath_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eUpdateInternalDataAfterLoadEvent,
    PatrolPath_UpdateInternalDataAfterLoadHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  PatrolPath_ptParameterList = nullptr;
  PatrolPath_RegisterCommands();
}

// source: j/0/humanai/patrolpath.c:795  [size]
void __cdecl PatrolPath_Close()
{
  QTask_DeleteQTaskType(PatrolPath_eQTaskType);
}

// source: j/0/humanai/patrolpath.c:815  [size]
unsigned __int16 __cdecl PatrolPath_GetQTaskType()
{
  return PatrolPath_eQTaskType;
}

// source: j/0/humanai/patrolpath.c:832  [size]
struct QTask_s *__cdecl PatrolPath_GetCurrentCommand(
        struct PatrolPathControl_t *ptPatrolPathControl)
{
  return ptPatrolPathControl->ptCurrentCommandQTask;
}

// source: j/0/humanai/patrolpath.c:850  [anchor-mhash]
struct QTask_s *__cdecl PatrolPath_GetNextCommand(
        struct PatrolPathControl_t *ptPatrolPathControl)
{
  struct QTask_s *result; // eax

  result = ptPatrolPathControl->ptCurrentCommandQTask->ptNext;
  if ( !result || !result->ptNext )
  {
    result = ptPatrolPathControl->ptLastEndCommandQTask;
    if ( !result )
      return ptPatrolPathControl->ptPatrolPathQTask->tQTaskChildren.ptHead->ptNext != nullptr
           ? ptPatrolPathControl->ptPatrolPathQTask->tQTaskChildren.ptHead
           : nullptr;
  }
  return result;
}

// source: j/0/humanai/patrolpath.c:887  [anchor-strings]
_DWORD *__cdecl PatrolPath_StepPatrolPathForward(int a1, _DWORD **a2)
{
  _DWORD *result; // eax
  _DWORD *v3; // ecx

  result = (_DWORD *)*a2[1];
  if ( result && *result
    || (result = a2[2]) != nullptr
    || (result = *(_DWORD *)(*a2)[2] != 0 ? (_DWORD *)(*a2)[2] : nullptr) != nullptr )
  {
    if ( result[11] == 6 )
    {
      if ( result == a2[2] )
        return nullptr;
      a2[1] = result;
      a2[2] = result;
      v3 = (_DWORD *)*result;
      if ( !*result || !*v3 || v3 == result )
        return nullptr;
      result = (_DWORD *)*result;
      if ( v3[11] == 6 )
      {
        LDebug_Error("END command following END command");
        abort();
      }
    }
    a2[1] = result;
  }
  return result;
}

// source: j/0/humanai/patrolpath.c:960  [anchor-callee]
struct PatrolPathControl_t *__cdecl PatrolPath_InitPatrolPath(
        struct PatrolPathControl_t *ptPatrolPathControl,
        int nPatrolPathQTaskID,
        int nOffset)
{
  struct Node_s *ptHead; // ecx
  struct PatrolPathControl_t *result; // eax
  struct Node_s *ptNext; // edi
  struct QTask_s *v7; // ecx

  ptHead = PatrolPath_tPatrolPathList.ptHead;
  result = (struct PatrolPathControl_t *)PatrolPath_tPatrolPathList.ptHead->ptNext;
  if ( !PatrolPath_tPatrolPathList.ptHead->ptNext )
    goto LABEL_4;
  while ( 1 )
  {
    ptNext = ptHead[1].ptNext;
    v7 = (struct QTask_s *)&ptHead[-14];
    if ( ptNext == (struct Node_s *)nPatrolPathQTaskID )
      break;
    ptHead = (struct Node_s *)result;
    result = (struct PatrolPathControl_t *)result->ptPatrolPathQTask;
    if ( !result )
      goto LABEL_4;
  }
  result = (struct PatrolPathControl_t *)v7[3].ptPrev;
  if ( (int)result > 0 )
  {
    ptPatrolPathControl->ptPatrolPathQTask = v7;
    ptPatrolPathControl->ptLastEndCommandQTask = nullptr;
    ptPatrolPathControl->isWalk = 1;
    ptPatrolPathControl->isCrouch = 0;
    ptPatrolPathControl->nUserModify = -1;
    ptPatrolPathControl->nPatrolPathQTaskID = -1;
    ptPatrolPathControl->nCurrentCommandQTaskID = -1;
    ptPatrolPathControl->nLastEndCommandQTaskID = -1;
    result = (struct PatrolPathControl_t *)PatrolPath_ScanToOffset(ptPatrolPathControl, nOffset);
    ptPatrolPathControl->ptCurrentCommandQTask = (struct QTask_s *)result;
    if ( *(_DWORD *)&result[1].isCrouch == 6 )
    {
      result = (struct PatrolPathControl_t *)result->ptPatrolPathQTask;
      if ( !result || !result->ptPatrolPathQTask )
      {
        result = (struct PatrolPathControl_t *)ptPatrolPathControl->ptLastEndCommandQTask;
        if ( !result )
          result = ptPatrolPathControl->ptPatrolPathQTask->tQTaskChildren.ptHead->ptNext != nullptr
                 ? (struct PatrolPathControl_t *)ptPatrolPathControl->ptPatrolPathQTask->tQTaskChildren.ptHead
                 : nullptr;
      }
      ptPatrolPathControl->ptCurrentCommandQTask = (struct QTask_s *)result;
    }
  }
  else
  {
LABEL_4:
    ptPatrolPathControl->ptPatrolPathQTask = nullptr;
  }
  return result;
}
