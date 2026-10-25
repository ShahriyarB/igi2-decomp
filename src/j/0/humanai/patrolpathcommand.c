/* j/0/humanai/patrolpathcommand.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/humanai/patrolpathcommand.c:64  [anchor-mhash]
void __cdecl PatrolPathCommand_SetQTaskNote(struct QTask_s *ptQTask)
{
  struct QTask_s *ptPrev; // eax
  char zTempString[1024]; // [esp+0h] [ebp-400h] BYREF

  ptPrev = ptQTask[1].ptPrev;
  if ( (unsigned int)ptPrev < 4
    || ptPrev == (struct QTask_s *)5
    || ptPrev == (struct QTask_s *)8
    || ptPrev == (struct QTask_s *)9 )
  {
    sprintf(
      zTempString,
      PatrolPathCommand_azPatrolPathCommandDesc[(int)ptPrev + 1][1],
      ptQTask[1].tQTaskChildren.ptHead);
  }
  else if ( ptPrev == (struct QTask_s *)10 )
  {
    sprintf(zTempString, PatrolPathCommand_azPatrolPathCommandDesc[11][1], ptQTask[1].tQTaskChildren.ptMiddle);
  }
  else if ( ptPrev == (struct QTask_s *)11 )
  {
    sprintf(zTempString, PatrolPathCommand_azPatrolPathCommandDesc[12][1], &ptQTask[3].tQTaskChildren.ptMiddle);
  }
  else
  {
    sprintf(zTempString, PatrolPathCommand_azPatrolPathCommandDesc[(int)ptPrev + 1][0]);
  }
}

// source: j/0/humanai/patrolpathcommand.c:108  [anchor-mhash]
void __cdecl PatrolPathCommand_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[1].ptPrev = (struct QTask_s *)-1;
  ptQTask[1].tQTaskChildren.ptHead = (struct QTask_s *)-1;
  ptQTask[1].ptNext = (struct QTask_s *)-1;
  ptQTask[1].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[1].tQTaskChildren.ptTail = nullptr;
  ptQTask[1].tQTaskRefList.ptHead = nullptr;
  ptQTask[3].tQTaskChildren.ptHead = nullptr;
  LOBYTE(ptQTask[3].tQTaskChildren.ptMiddle) = 0;
}

// source: j/0/humanai/patrolpathcommand.c:129  [size]
void __cdecl PatrolPathCommand_DeleteHandler(struct QTask_s *ptQTask)
{
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[1].tQTaskChildren.ptMiddle);
}

// source: j/0/humanai/patrolpathcommand.c:148  [size]
void __cdecl PatrolPathCommand_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = PatrolPathCommand_ptParameterList;
}

// source: j/0/humanai/patrolpathcommand.c:164  [anchor-mhash]
void __cdecl PatrolPathCommand_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptPrev; // eax

  ptPrev = ptQTask[1].ptPrev;
  if ( (int)ptPrev < -1 || (int)ptPrev >= 12 )
    ptQTask[1].ptPrev = (struct QTask_s *)-1;
  PatrolPathCommand_SetQTaskNote(ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[1].tQTaskChildren.ptMiddle, ptQTask);
}

// source: j/0/humanai/patrolpathcommand.c:199  [anchor-hash]
void __cdecl PatrolPathCommand_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si
  struct ParameterList_s *v2; // eax
  int v3; // edx

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("PatrolPathCommand", 164, BaseQTaskType, 0, 0);
  PatrolPathCommand_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 0, (void (__cdecl *)(struct QTask_s *, void *))PatrolPathCommand_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))PatrolPathCommand_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eUpdateInternalDataQTaskEvent,
    PatrolPathCommand_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, PatrolPathCommand_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  v2 = (struct ParameterList_s *)Mem_AllocFn(112, 4);
  v3 = Level_eParameterTypeInt32;
  v2->ptParameterListItem = (struct ParameterListItem_s *)&v2[1];
  v2->nParameters = 0;
  v2->nMaxParameters = 5;
  PatrolPathCommand_ptParameterList = v2;
  ParameterList_AddParameter(v2, 0x2Cu, v3, "Command", 7u, nullptr);
  ParameterList_AddParameter(
    PatrolPathCommand_ptParameterList,
    0x30u,
    Level_eParameterTypeInt32,
    "Command Parameter",
    7u,
    nullptr);
  ParameterList_AddParameter(
    PatrolPathCommand_ptParameterList,
    0x28u,
    Level_eParameterTypeInt32,
    "eNodeId",
    3u,
    nullptr);
  ParameterList_AddParameter(
    PatrolPathCommand_ptParameterList,
    0x34u,
    Level_eParameterTypeVarString,
    "Command Expression",
    7u,
    nullptr);
  ParameterList_AddParameter(
    PatrolPathCommand_ptParameterList,
    0x84u,
    Level_eParameterTypeString32,
    "Command Text",
    7u,
    nullptr);
}

// source: j/0/humanai/patrolpathcommand.c:236  [size]
void __cdecl PatrolPathCommand_Close()
{
  int v0; // esi

  QTask_DeleteQTaskType(PatrolPathCommand_eQTaskType);
  if ( PatrolPathCommand_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&PatrolPathCommand_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
}

// source: j/0/humanai/patrolpathcommand.c:253  [size]
unsigned __int16 __cdecl PatrolPathCommand_GetQTaskType()
{
  return PatrolPathCommand_eQTaskType;
}

// source: j/0/humanai/patrolpathcommand.c:268  [size]
int __cdecl PatrolPathCommand_GetCommand(struct QTask_s *ptPatrolPathCommandQTask)
{
  return (int)ptPatrolPathCommandQTask[1].ptPrev;
}

// source: j/0/humanai/patrolpathcommand.c:284  [size]
int __cdecl PatrolPathCommand_GetParameter(struct QTask_s *ptPatrolPathCommandQTask)
{
  return (int)ptPatrolPathCommandQTask[1].tQTaskChildren.ptHead;
}

// source: j/0/humanai/patrolpathcommand.c:301  [anchor-callee]
enum bool __cdecl PatrolPathCommand_isExpression(struct QTask_s *ptPatrolPathCommandQTask)
{
  if ( ptPatrolPathCommandQTask[1].tQTaskChildren.ptMiddle
    && ptPatrolPathCommandQTask[1].tQTaskChildren.ptTail->ptNext
    && ptPatrolPathCommandQTask[1].tQTaskRefList.ptHead )
  {
    return (char)(__int64)Level_RunLevelExpression(
                            (struct LevelExpression_s *)&ptPatrolPathCommandQTask[1].tQTaskChildren.ptMiddle,
                            ptPatrolPathCommandQTask);
  }
  else
  {
    return false;
  }
}

// source: j/0/humanai/patrolpathcommand.c:323  [size]
char *__cdecl PatrolPathCommand_GetText(struct QTask_s *ptPatrolPathCommandQTask)
{
  return (char *)&ptPatrolPathCommandQTask[3].tQTaskChildren.ptMiddle;
}
