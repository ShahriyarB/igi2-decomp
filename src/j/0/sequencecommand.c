/* j/0/sequencecommand.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/sequencecommand.c:103  [size]
void __cdecl SequenceCommand_GetSerializeParameterListHandler(
        struct QTask_s *ptQTask,
        void *pxContext)
{
  *(_DWORD *)pxContext = SequenceCommand_ptSerializeParameterList;
}

// source: j/0/sequencecommand.c:121  [size]
// attributes: thunk
void __cdecl SequenceCommand_DeSerializeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  Serialize_DeSerializeHandler(ptQTask, pxContext);
}

// source: j/0/sequencecommand.c:137  [anchor-mhash]
void __cdecl SequenceCommand_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[1].ptNext = nullptr;
  ptQTask[1].ptPrev = nullptr;
  ptQTask[1].tQTaskChildren.ptHead = nullptr;
  *(_DWORD *)&ptQTask[2].eQTaskType = 0;
  ptQTask[3].ptNext = nullptr;
  ptQTask[3].ptPrev = nullptr;
  ptQTask[3].tQTaskChildren.ptHead = nullptr;
  *(_DWORD *)&ptQTask[4].eQTaskType = 0;
  ptQTask[5].ptNext = nullptr;
  ptQTask[5].ptPrev = nullptr;
  ptQTask[5].tQTaskChildren.ptHead = nullptr;
  *(_DWORD *)&ptQTask[6].eQTaskType = 0;
  ptQTask[7].ptNext = nullptr;
  ptQTask[7].ptPrev = nullptr;
  ptQTask[7].tQTaskChildren.ptHead = nullptr;
  *(_DWORD *)&ptQTask[8].eQTaskType = 0;
  ptQTask[9].ptNext = nullptr;
  ptQTask[9].ptPrev = nullptr;
}

// source: j/0/sequencecommand.c:160  [anchor-caller]
void __cdecl SequenceCommand_RunSequenceCommandHandler(struct QTask_s *ptQTask)
{
  if ( ptQTask[1].ptNext
    && ptQTask[1].ptPrev->ptNext
    && ptQTask[1].tQTaskChildren.ptHead
    && (unsigned int)(__int64)Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[1], ptQTask) )
  {
    if ( ptQTask[3].ptNext && ptQTask[3].ptPrev->ptNext && ptQTask[3].tQTaskChildren.ptHead )
      Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[3], ptQTask);
    if ( ptQTask[5].ptNext
      && ptQTask[5].ptPrev->ptNext
      && ptQTask[5].tQTaskChildren.ptHead
      && (unsigned int)(__int64)Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[5], ptQTask) )
    {
      if ( Level_LevelExpressionDefined((struct LevelExpression_s *)&ptQTask[7]) )
        Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[7], ptQTask);
    }
  }
}

// source: j/0/sequencecommand.c:203  [anchor-mhash]
void __cdecl SequenceCommand_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptNext; // eax

  ptNext = ptQTask[9].ptNext;
  if ( ptNext )
  {
    QReference_Delete((struct QReference_s *)ptNext, &QTask_tQTaskRefPool);
    ptQTask[9].ptNext = nullptr;
  }
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[1]);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[3]);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[5]);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[7]);
}

// source: j/0/sequencecommand.c:223  [anchor-mhash]
void __cdecl SequenceCommand_RunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptParent; // eax
  struct QTask_s *ptNext; // eax
  struct QTask_s *v3; // eax
  struct QTask_s *v4; // eax
  struct QTask_s *ptHead; // eax
  int v6; // ecx

  ptParent = ptQTask->ptParent;
  if ( ptParent && QTask_GetFirstChildOfType(ptParent, SequenceCommand_eQTaskType) == ptQTask && !ptQTask[9].ptPrev )
  {
    ptNext = ptQTask[9].ptNext;
    if ( !ptNext || !ptNext->tQTaskChildren.ptHead )
    {
      v3 = ptQTask[9].ptNext;
      if ( v3 )
      {
        QReference_Delete((struct QReference_s *)v3, &QTask_tQTaskRefPool);
        ptQTask[9].ptNext = nullptr;
      }
      ptQTask[9].ptNext = (struct QTask_s *)QTask_NewQTaskRef(ptQTask);
    }
    v4 = ptQTask[9].ptNext;
    if ( v4 )
    {
      ptHead = v4->tQTaskChildren.ptHead;
      if ( ptHead )
      {
        v6 = 511 * SequenceCommand_eRunSequenceCommandQTaskEvent + ptHead->eQTaskType;
        SequenceCommand_ptSequenceCommand = (struct SequenceCommand_s *)ptQTask;
        ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[0][v6].pfHandler)(ptHead);
        SequenceCommand_ptSequenceCommand = nullptr;
      }
    }
  }
}

// source: j/0/sequencecommand.c:255  [anchor-mhash]
void __cdecl SequenceCommand_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptNext; // eax

  ptNext = ptQTask[9].ptNext;
  if ( ptNext )
  {
    QReference_Delete((struct QReference_s *)ptNext, &QTask_tQTaskRefPool);
    ptQTask[9].ptNext = nullptr;
  }
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[1], ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[3], ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[5], ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[7], ptQTask);
}

// source: j/0/sequencecommand.c:277  [size]
void __cdecl SequenceCommand_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = SequenceCommand_ptParameterList;
}

// source: j/0/sequencecommand.c:293  [anchor-mhash]
struct Result_s *__cdecl SequenceCommand_SetNextCommandScriptFunction(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct SequenceCommand_s *v3; // esi
  int v4; // eax
  struct QReference_s *v5; // eax
  struct QTask_s *pxObject; // edi
  struct QReference_s *ptQTaskRef; // eax
  struct QReference_s *v8; // eax
  struct QReference_s *v9; // eax
  struct Result_s Rs; // [esp+Ch] [ebp-18h] BYREF

  v3 = SequenceCommand_ptSequenceCommand;
  if ( SequenceCommand_ptSequenceCommand )
  {
    if ( ptArgList->nArguments > 0 )
    {
      v4 = Script_EvalArgInt(ptArgList, 0);
      if ( v4 >= 0 )
      {
        if ( v4 < 4096 )
        {
          v5 = Level_atLevelQTaskID[v4];
          if ( v5 )
          {
            pxObject = (struct QTask_s *)v5->pxObject;
            if ( pxObject )
            {
              if ( QTask_IsQTaskTypeDerived(pxObject->eQTaskType, SequenceCommand_eQTaskType) )
              {
                ptQTaskRef = v3->ptQTaskRef;
                if ( ptQTaskRef )
                {
                  QReference_Delete(ptQTaskRef, &QTask_tQTaskRefPool);
                  v3->ptQTaskRef = nullptr;
                }
LABEL_18:
                v3->ptQTaskRef = QTask_NewQTaskRef(pxObject);
                goto LABEL_19;
              }
            }
          }
        }
        goto LABEL_11;
      }
      if ( v4 != -2 )
      {
LABEL_11:
        v3->isStopped = true;
        goto LABEL_19;
      }
    }
    v8 = v3->ptQTaskRef;
    if ( v8 )
    {
      pxObject = (struct QTask_s *)v8->pxObject;
      if ( pxObject )
        pxObject = QTask_GetNextSiblingOfType((struct QTask_s *)v8->pxObject, SequenceCommand_eQTaskType);
    }
    else
    {
      pxObject = nullptr;
    }
    v9 = v3->ptQTaskRef;
    if ( v9 )
    {
      QReference_Delete(v9, &QTask_tQTaskRefPool);
      v3->ptQTaskRef = nullptr;
    }
    if ( pxObject )
      goto LABEL_18;
  }
LABEL_19:
  Rs.nResult = 0;
  Rs.zResult = (char *)&g_zInitialValue;
  Rs.vResult = 0.0;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/sequencecommand.c:383  [size]
unsigned __int16 __cdecl SequenceCommand_GetQTaskType()
{
  return SequenceCommand_eQTaskType;
}

// source: j/0/sequencecommand.c:396  [size]
int __cdecl SequenceCommand_GetRunSequenceCommandQTaskEvent()
{
  return SequenceCommand_eRunSequenceCommandQTaskEvent;
}

// source: j/0/sequencecommand.c:409  [anchor-hash]
void __cdecl SequenceCommand_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  int v1; // eax
  unsigned __int16 v2; // si
  int v3; // edi
  struct ParameterList_s *v4; // eax
  int v5; // edx
  unsigned __int16 v6; // si
  struct ParameterList_s *v7; // eax
  int v8; // edx

  BaseQTaskType = QTask_GetBaseQTaskType();
  SequenceCommand_eQTaskType = QTask_NewQTaskType("SequenceCommand", 368, BaseQTaskType, 0, 0);
  v1 = QTask_NewQTaskEventNoContextFn(0, "RunSequenceCommand");
  v2 = SequenceCommand_eQTaskType;
  v3 = v1;
  SequenceCommand_eRunSequenceCommandQTaskEvent = v1;
  QTask_LinkQTaskEventHandlerFn(
    SequenceCommand_eQTaskType,
    0,
    (void (__cdecl *)(struct QTask_s *, void *))SequenceCommand_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, 2, SequenceCommand_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, 1, SequenceCommand_RunHandler);
  QTask_LinkQTaskEventHandlerFn(
    v2,
    ParameterList_eUpdateInternalDataQTaskEvent,
    SequenceCommand_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v2,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))SequenceCommand_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, v3, SequenceCommand_RunSequenceCommandHandler);
  QTask_LinkQTaskEventHandlerFn(
    v2,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  v4 = (struct ParameterList_s *)Mem_AllocFn(92, 4);
  v5 = Level_eParameterTypeVarString;
  v4->ptParameterListItem = (struct ParameterListItem_s *)&v4[1];
  v4->nParameters = 0;
  v4->nMaxParameters = 4;
  SequenceCommand_ptParameterList = v4;
  ParameterList_AddParameter(v4, 0x28u, v5, "IsRun Expression", 7u, nullptr);
  ParameterList_AddParameter(
    SequenceCommand_ptParameterList,
    0x78u,
    Level_eParameterTypeVarString,
    "Run Expression",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SequenceCommand_ptParameterList,
    0xC8u,
    Level_eParameterTypeVarString,
    "IsNext Expression",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SequenceCommand_ptParameterList,
    0x118u,
    Level_eParameterTypeVarString,
    "Next Expression",
    7u,
    nullptr);
  Symbol_Register(
    "SEQUENCECOMMAND_NEXT",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0xFFFFFFFE,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "SEQUENCECOMMAND_STOP",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0xFFFFFFFF,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "SequenceCommand_SetCommand",
    SequenceCommand_SetNextCommandScriptFunction,
    nullptr,
    -1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  v6 = SequenceCommand_eQTaskType;
  QTask_LinkQTaskEventHandlerFn(
    SequenceCommand_eQTaskType,
    Serialize_eGetSerializeParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))SequenceCommand_GetSerializeParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v6, Serialize_eDeSerializeQTaskEvent, SequenceCommand_DeSerializeHandler);
  v7 = (struct ParameterList_s *)Mem_AllocFn(52, 4);
  v7->ptParameterListItem = (struct ParameterListItem_s *)&v7[1];
  v8 = Level_eParameterTypebool8;
  v7->nParameters = 0;
  v7->nMaxParameters = 2;
  SequenceCommand_ptSerializeParameterList = v7;
  ParameterList_AddParameter(v7, 0x16Cu, v8, "isExploded", 7u, nullptr);
  ParameterList_AddParameter(
    SequenceCommand_ptSerializeParameterList,
    0x168u,
    SerializeQTaskRef_eParameterType,
    "ptQTaskRef",
    7u,
    nullptr);
}

// source: j/0/sequencecommand.c:459  [anchor-strings]
void __cdecl SequenceCommand_Close()
{
  int v0; // esi
  int v1; // esi

  Symbol_Remove("SequenceCommand_SetCommand");
  if ( SequenceCommand_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&SequenceCommand_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  if ( SequenceCommand_ptSerializeParameterList )
  {
    v1 = *(_DWORD *)((unsigned int)&SequenceCommand_ptSerializeParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
  QTask_DeleteQTaskEventNoContext(SequenceCommand_eRunSequenceCommandQTaskEvent);
  QTask_DeleteQTaskType(SequenceCommand_eQTaskType);
}
