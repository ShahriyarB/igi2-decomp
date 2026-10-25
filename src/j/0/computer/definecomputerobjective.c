/* j/0/computer/definecomputerobjective.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/computer/definecomputerobjective.c:109  [anchor-mhash]
void __cdecl DefineComputerObjective_RunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s **p_ptPrev; // esi
  int v2; // [esp+10h] [ebp-10h]

  if ( ptQTask[1].ptNext
    && ptQTask[1].ptPrev->ptNext
    && ptQTask[1].tQTaskChildren.ptHead
    && !(unsigned __int8)(__int64)Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[1], ptQTask) )
  {
    DefineComputerObjective_ptInactiveQTask = ptQTask;
  }
  else
  {
    DefineComputerObjective_ptQTask = ptQTask;
    p_ptPrev = &ptQTask[4].ptPrev;
    v2 = 8;
    do
    {
      if ( *(p_ptPrev - 2) && LOBYTE((*(p_ptPrev - 1))->ptNext) && *p_ptPrev )
        p_ptPrev[38] = (struct QTask_s *)(char)(__int64)Level_RunLevelExpression(
                                                          (struct LevelExpression_s *)(p_ptPrev - 2),
                                                          ptQTask);
      else
        p_ptPrev[38] = nullptr;
      if ( p_ptPrev[18] && LOBYTE(p_ptPrev[19]->ptNext) && p_ptPrev[20] )
        p_ptPrev[39] = (struct QTask_s *)(char)(__int64)Level_RunLevelExpression(
                                                          (struct LevelExpression_s *)(p_ptPrev + 18),
                                                          ptQTask);
      else
        p_ptPrev[39] = nullptr;
      p_ptPrev += 51;
      --v2;
    }
    while ( v2 );
  }
}

// source: j/0/computer/definecomputerobjective.c:175  [anchor-mhash]
void __cdecl DefineComputerObjective_DeleteHandler(struct QTask_s *ptQTask)
{
  struct LevelExpression_s *p_eQTaskType; // edi
  int v2; // ebx

  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[1]);
  p_eQTaskType = (struct LevelExpression_s *)&ptQTask[5].eQTaskType;
  v2 = 8;
  do
  {
    Level_DeinitLevelExpression(p_eQTaskType - 1);
    Level_DeinitLevelExpression(p_eQTaskType);
    p_eQTaskType = (struct LevelExpression_s *)((char *)p_eQTaskType + 204);
    --v2;
  }
  while ( v2 );
  DefineComputerObjective_ptQTask = nullptr;
  DefineComputerObjective_ptInactiveQTask = nullptr;
}

// source: j/0/computer/definecomputerobjective.c:210  [size]
void __cdecl DefineComputerObjective_GetParameterListHandler(
        struct QTask_s *ptQTask,
        void *pxContext)
{
  *(_DWORD *)pxContext = DefineComputerObjective_ptParameterList;
}

// source: j/0/computer/definecomputerobjective.c:226  [anchor-mhash]
void __cdecl DefineComputerObjective_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct LevelExpression_s *p_eQTaskType; // esi
  int v3; // ebx

  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[1], ptQTask);
  p_eQTaskType = (struct LevelExpression_s *)&ptQTask[5].eQTaskType;
  v3 = 8;
  do
  {
    Level_CompileLevelExpression(p_eQTaskType - 1, ptQTask);
    Level_CompileLevelExpression(p_eQTaskType, ptQTask);
    p_eQTaskType = (struct LevelExpression_s *)((char *)p_eQTaskType + 204);
    --v3;
  }
  while ( v3 );
}

// source: j/0/computer/definecomputerobjective.c:259  [anchor-hash]
void __cdecl DefineComputerObjective_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si
  struct ParameterList_s *v2; // eax
  int v3; // edx

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("DefineComputerObjective", 1752, BaseQTaskType, 0, 0);
  DefineComputerObjective_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(
    v1,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 0, (void (__cdecl *)(struct QTask_s *, void *))sub_4D8AC0);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, DefineComputerObjective_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, DefineComputerObjective_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))DefineComputerObjective_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eUpdateInternalDataQTaskEvent,
    DefineComputerObjective_UpdateInternalDataHandler);
  v2 = (struct ParameterList_s *)Mem_AllocFn(672, 4);
  v2->ptParameterListItem = (struct ParameterListItem_s *)&v2[1];
  v3 = Level_eParameterTypeVarString;
  v2->nParameters = 0;
  v2->nMaxParameters = 33;
  DefineComputerObjective_ptParameterList = v2;
  ParameterList_AddParameter(v2, 0x28u, v3, "Objectives Valid", 7u, nullptr);
  ParameterList_AddParameter(
    DefineComputerObjective_ptParameterList,
    0x78u,
    Level_eParameterTypeString32,
    "Objective 1 Text Resource",
    7u,
    nullptr);
  ParameterList_AddParameter(
    DefineComputerObjective_ptParameterList,
    0x98u,
    Level_eParameterTypeInt32,
    "Objective 1 Link To Position",
    7u,
    nullptr);
  ParameterList_AddParameter(
    DefineComputerObjective_ptParameterList,
    0x9Cu,
    Level_eParameterTypeVarString,
    "Objective 1 Complete Expression",
    7u,
    nullptr);
  ParameterList_AddParameter(
    DefineComputerObjective_ptParameterList,
    0xECu,
    Level_eParameterTypeVarString,
    "Objective 1 Failed Expression",
    7u,
    nullptr);
  ParameterList_AddParameter(
    DefineComputerObjective_ptParameterList,
    0x144u,
    Level_eParameterTypeString32,
    "Objective 2 Text Resource",
    7u,
    nullptr);
  ParameterList_AddParameter(
    DefineComputerObjective_ptParameterList,
    0x164u,
    Level_eParameterTypeInt32,
    "Objective 2 Link To Position",
    7u,
    nullptr);
  ParameterList_AddParameter(
    DefineComputerObjective_ptParameterList,
    0x168u,
    Level_eParameterTypeVarString,
    "Objective 2 Complete Expression",
    7u,
    nullptr);
  ParameterList_AddParameter(
    DefineComputerObjective_ptParameterList,
    0x1B8u,
    Level_eParameterTypeVarString,
    "Objective 2 Failed Expression",
    7u,
    nullptr);
  ParameterList_AddParameter(
    DefineComputerObjective_ptParameterList,
    0x210u,
    Level_eParameterTypeString32,
    "Objective 3 Text Resource",
    7u,
    nullptr);
  ParameterList_AddParameter(
    DefineComputerObjective_ptParameterList,
    0x230u,
    Level_eParameterTypeInt32,
    "Objective 3 Link To Position",
    7u,
    nullptr);
  ParameterList_AddParameter(
    DefineComputerObjective_ptParameterList,
    0x234u,
    Level_eParameterTypeVarString,
    "Objective 3 Complete Expression",
    7u,
    nullptr);
  ParameterList_AddParameter(
    DefineComputerObjective_ptParameterList,
    0x284u,
    Level_eParameterTypeVarString,
    "Objective 3 Failed Expression",
    7u,
    nullptr);
  ParameterList_AddParameter(
    DefineComputerObjective_ptParameterList,
    0x2DCu,
    Level_eParameterTypeString32,
    "Objective 4 Text Resource",
    7u,
    nullptr);
  ParameterList_AddParameter(
    DefineComputerObjective_ptParameterList,
    0x2FCu,
    Level_eParameterTypeInt32,
    "Objective 4 Link To Position",
    7u,
    nullptr);
  ParameterList_AddParameter(
    DefineComputerObjective_ptParameterList,
    0x300u,
    Level_eParameterTypeVarString,
    "Objective 4 Complete Expression",
    7u,
    nullptr);
  ParameterList_AddParameter(
    DefineComputerObjective_ptParameterList,
    0x350u,
    Level_eParameterTypeVarString,
    "Objective 4 Failed Expression",
    7u,
    nullptr);
  ParameterList_AddParameter(
    DefineComputerObjective_ptParameterList,
    0x3A8u,
    Level_eParameterTypeString32,
    "Objective 5 Text Resource",
    7u,
    nullptr);
  ParameterList_AddParameter(
    DefineComputerObjective_ptParameterList,
    0x3C8u,
    Level_eParameterTypeInt32,
    "Objective 5 Link To Position",
    7u,
    nullptr);
  ParameterList_AddParameter(
    DefineComputerObjective_ptParameterList,
    0x3CCu,
    Level_eParameterTypeVarString,
    "Objective 5 Complete Expression",
    7u,
    nullptr);
  ParameterList_AddParameter(
    DefineComputerObjective_ptParameterList,
    0x41Cu,
    Level_eParameterTypeVarString,
    "Objective 5 Failed Expression",
    7u,
    nullptr);
  ParameterList_AddParameter(
    DefineComputerObjective_ptParameterList,
    0x474u,
    Level_eParameterTypeString32,
    "Objective 6 Text Resource",
    7u,
    nullptr);
  ParameterList_AddParameter(
    DefineComputerObjective_ptParameterList,
    0x494u,
    Level_eParameterTypeInt32,
    "Objective 6 Link To Position",
    7u,
    nullptr);
  ParameterList_AddParameter(
    DefineComputerObjective_ptParameterList,
    0x498u,
    Level_eParameterTypeVarString,
    "Objective 6 Complete Expression",
    7u,
    nullptr);
  ParameterList_AddParameter(
    DefineComputerObjective_ptParameterList,
    0x4E8u,
    Level_eParameterTypeVarString,
    "Objective 6 Failed Expression",
    7u,
    nullptr);
  ParameterList_AddParameter(
    DefineComputerObjective_ptParameterList,
    0x540u,
    Level_eParameterTypeString32,
    "Objective 7 Text Resource",
    7u,
    nullptr);
  ParameterList_AddParameter(
    DefineComputerObjective_ptParameterList,
    0x560u,
    Level_eParameterTypeInt32,
    "Objective 7 Link To Position",
    7u,
    nullptr);
  ParameterList_AddParameter(
    DefineComputerObjective_ptParameterList,
    0x564u,
    Level_eParameterTypeVarString,
    "Objective 7 Complete Expression",
    7u,
    nullptr);
  ParameterList_AddParameter(
    DefineComputerObjective_ptParameterList,
    0x5B4u,
    Level_eParameterTypeVarString,
    "Objective 7 Failed Expression",
    7u,
    nullptr);
  ParameterList_AddParameter(
    DefineComputerObjective_ptParameterList,
    0x60Cu,
    Level_eParameterTypeString32,
    "Objective 8 Text Resource",
    7u,
    nullptr);
  ParameterList_AddParameter(
    DefineComputerObjective_ptParameterList,
    0x62Cu,
    Level_eParameterTypeInt32,
    "Objective 8 Link To Position",
    7u,
    nullptr);
  ParameterList_AddParameter(
    DefineComputerObjective_ptParameterList,
    0x630u,
    Level_eParameterTypeVarString,
    "Objective 8 Complete Expression",
    7u,
    nullptr);
  ParameterList_AddParameter(
    DefineComputerObjective_ptParameterList,
    0x680u,
    Level_eParameterTypeVarString,
    "Objective 8 Failed Expression",
    7u,
    nullptr);
}

// source: j/0/computer/definecomputerobjective.c:330  [size]
void __cdecl DefineComputerObjective_Close()
{
  int v0; // esi

  QTask_DeleteQTaskType(DefineComputerObjective_eQTaskType);
  if ( DefineComputerObjective_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&DefineComputerObjective_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
}

// source: j/0/computer/definecomputerobjective.c:347  [anchor-callee]
struct Objective_t *__cdecl DefineComputerObjective_GetObjective(int iObjective)
{
  if ( DefineComputerObjective_ptQTask )
    return (struct Objective_t *)((char *)&DefineComputerObjective_ptQTask[3] + 204 * iObjective);
  else
    return nullptr;
}

// source: j/0/computer/definecomputerobjective.c:372  [anchor-hash]
struct Objective_t *__cdecl DefineComputerObjective_GetInactiveObjective(
        int iObjective)
{
  if ( DefineComputerObjective_ptInactiveQTask )
    return (struct Objective_t *)((char *)&DefineComputerObjective_ptInactiveQTask[3] + 204 * iObjective);
  else
    return nullptr;
}
