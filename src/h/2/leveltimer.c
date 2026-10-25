/* h/2/leveltimer.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/leveltimer.c:77  [size]
void __cdecl LevelTimer_GetSerializeParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = LevelTimer_ptSerializeParameterList;
}

// source: h/2/leveltimer.c:93  [size]
void __cdecl LevelTimer_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)&ptQTask[2].eQTaskType = 0;
  ptQTask[3].ptNext = nullptr;
  ptQTask[3].ptPrev = nullptr;
  ptQTask[4].ptParent = nullptr;
  *(_DWORD *)&ptQTask[4].eQTaskType = 0;
  ptQTask[5].ptNext = nullptr;
  ptQTask[5].ptPrev = nullptr;
  ptQTask[6].ptParent = nullptr;
  ptQTask[1].ptNext = nullptr;
  ptQTask[1].ptPrev = nullptr;
  ptQTask[1].tQTaskChildren.ptHead = nullptr;
  ptQTask[1].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[1].tQTaskChildren.ptTail = nullptr;
  ptQTask[1].tQTaskRefList.ptHead = nullptr;
  ptQTask[1].tQTaskRefList.ptMiddle = (struct QReference_s *)1065353216;
  ptQTask[1].tQTaskRefList.ptTail = nullptr;
  ptQTask[1].ptParent = nullptr;
  *(_DWORD *)&ptQTask[1].eQTaskType = 0;
  ptQTask[2].ptNext = (struct QTask_s *)1065353216;
  ptQTask[2].ptPrev = nullptr;
  ptQTask[2].tQTaskChildren.ptHead = nullptr;
  ptQTask[2].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[2].tQTaskChildren.ptTail = (struct QTask_s *)1065353216;
  ptQTask[2].tQTaskRefList.ptHead = nullptr;
  LOBYTE(ptQTask[2].ptParent) = 0;
  LOBYTE(ptQTask[2].tQTaskRefList.ptMiddle) = 1;
  ptQTask[2].tQTaskRefList.ptTail = nullptr;
}

// source: h/2/leveltimer.c:140  [size]
void __cdecl LevelTimer_RegisterScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( !LOBYTE(ptQTask[2].ptParent) )
  {
    LOBYTE(ptQTask[2].ptParent) = 1;
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.isRun", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      &ptQTask[2].tQTaskRefList.ptMiddle,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.nTick", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int,
      &ptQTask[2].tQTaskRefList.ptTail,
      4,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
  }
}

// source: h/2/leveltimer.c:173  [anchor-mhash]
void __cdecl LevelTimer_RemoveScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
  LOBYTE(ptQTask[2].ptParent) = 0;
  sprintf(igi2_frame.zTemp, "%s.isRun", igi2_frame.zName);
  Symbol_Remove(igi2_frame.zTemp);
  sprintf(igi2_frame.zTemp, "%s.nTick", igi2_frame.zName);
  Symbol_Remove(igi2_frame.zTemp);
  LOBYTE(ptQTask[2].ptParent) = 0;
}

// source: h/2/leveltimer.c:206  [size]
void __cdecl LevelTimer_DeleteHandler(struct QTask_s *ptQTask)
{
  int v1; // ecx
  struct QReference_s *v2; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax

  v1 = 0;
  while ( 1 )
  {
    v2 = Level_atLevelQTaskID[v1];
    if ( v2 )
    {
      if ( v2->pxObject == ptQTask )
        break;
    }
    if ( ++v1 >= 4096 )
      goto LABEL_9;
  }
  if ( v1 >= 0 )
  {
    pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Level_eRemoveLevelScriptSymbolsEvent][ptQTask->eQTaskType].pfHandler;
    if ( pfHandler )
      pfHandler(ptQTask);
  }
LABEL_9:
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[2].eQTaskType);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[4].eQTaskType);
}

// source: h/2/leveltimer.c:240  [size]
void __cdecl LevelTimer_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = LevelTimer_ptParameterList;
}

// source: h/2/leveltimer.c:256  [anchor-mhash]
void __cdecl LevelTimer_RunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // ecx
  int v2; // edx
  struct QTask_s *v3; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v5; // edx

  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v2 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v3 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v3 = nullptr;
      QTask_atProtectedQTaskStack[v2].ptQTask = v3;
      pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][ptHead->eQTaskType].pfHandler;
      v5 = v2 + 1;
      QTask_nProtectedQTaskStackOffset = v5;
      if ( pfHandler )
      {
        pfHandler(ptHead);
        v5 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v5];
      v2 = v5 - 1;
      QTask_nProtectedQTaskStackOffset = v2;
    }
    while ( ptHead );
  }
  if ( *(_DWORD *)&ptQTask[2].eQTaskType && ptQTask[3].ptNext->ptNext && ptQTask[3].ptPrev )
    LOBYTE(ptQTask[2].tQTaskRefList.ptMiddle) = (__int64)Level_RunLevelExpression(
                                                           (struct LevelExpression_s *)&ptQTask[2].eQTaskType,
                                                           ptQTask);
  if ( *(_DWORD *)&ptQTask[4].eQTaskType
    && ptQTask[5].ptNext->ptNext
    && ptQTask[5].ptPrev
    && Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[4].eQTaskType, ptQTask) != 0.0 )
  {
    ptQTask[2].tQTaskRefList.ptTail = nullptr;
  }
  if ( LOBYTE(ptQTask[2].tQTaskRefList.ptMiddle) )
    ++*(int *)&ptQTask[2].tQTaskRefList.ptTail;
}

// source: h/2/leveltimer.c:291  [anchor-mhash]
void __cdecl LevelTimer_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptHead; // eax
  int v3; // edx
  struct QTask_s *v4; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, _DWORD); // ecx
  int v6; // edx

  if ( !pxContext || !*(_DWORD *)pxContext )
  {
    ptHead = ptQTask->tQTaskChildren.ptHead;
    if ( ptHead->ptNext )
    {
      if ( ptHead )
      {
        v3 = QTask_nProtectedQTaskStackOffset;
        do
        {
          if ( ptHead->ptNext )
            v4 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
          else
            v4 = nullptr;
          QTask_atProtectedQTaskStack[v3].ptQTask = v4;
          pfHandler = (void (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][ptHead->eQTaskType].pfHandler;
          v6 = v3 + 1;
          QTask_nProtectedQTaskStackOffset = v6;
          if ( pfHandler )
          {
            pfHandler(ptHead, 0);
            v6 = QTask_nProtectedQTaskStackOffset;
          }
          ptHead = (struct QTask_s *)dword_849C7DC[v6];
          v3 = v6 - 1;
          QTask_nProtectedQTaskStackOffset = v3;
        }
        while ( ptHead );
      }
    }
  }
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[2].eQTaskType, ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[4].eQTaskType, ptQTask);
}

// source: h/2/leveltimer.c:346  [anchor-strings]
void __cdecl LevelTimer_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // edx
  struct ParameterList_s *v3; // eax
  int v4; // edx

  v0 = QTask_NewQTaskType("LevelTimer", 280, EditorRigidObj_eQTaskType, 0, 0);
  LevelTimer_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, LevelTimer_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, LevelTimer_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, LevelTimer_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))LevelTimer_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, LevelTimer_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eRegisterLevelScriptSymbolsEvent,
    LevelTimer_RegisterScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eRemoveLevelScriptSymbolsEvent,
    LevelTimer_RemoveScriptSymbolsHandler);
  v1 = (struct ParameterList_s *)Mem_AllocFn(112, 4);
  v2 = Level_eParameterTypeObjectPos;
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  v1->nParameters = 0;
  v1->nMaxParameters = 5;
  LevelTimer_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0x28u, v2, "Position", 7u, nullptr);
  ParameterList_AddParameter(
    LevelTimer_ptParameterList,
    0x40u,
    Level_eParameterTypeReal32x9,
    "Orientation",
    7u,
    nullptr);
  ParameterList_AddParameter(LevelTimer_ptParameterList, 0x74u, Level_eParameterTypeVarString, "On", 7u, nullptr);
  ParameterList_AddParameter(LevelTimer_ptParameterList, 0xC4u, Level_eParameterTypeVarString, "Reset", 7u, nullptr);
  ParameterList_AddParameter(LevelTimer_ptParameterList, 0x68u, Level_eParameterTypebool8, "Initial run", 7u, nullptr);
  QTask_LinkQTaskEventHandlerFn(
    LevelTimer_eQTaskType,
    Serialize_eGetSerializeParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))LevelTimer_GetSerializeParameterListHandler);
  v3 = (struct ParameterList_s *)Mem_AllocFn(52, 4);
  v4 = Level_eParameterTypebool8;
  v3->ptParameterListItem = (struct ParameterListItem_s *)&v3[1];
  v3->nParameters = 0;
  v3->nMaxParameters = 2;
  LevelTimer_ptSerializeParameterList = v3;
  ParameterList_AddParameter(v3, 0x68u, v4, "isRun", 7u, nullptr);
  ParameterList_AddParameter(
    LevelTimer_ptSerializeParameterList,
    0x6Cu,
    Level_eParameterTypeInt32,
    "nTick",
    7u,
    nullptr);
  Symbol_Register(
    "TASKTYPE_LEVELTIMER",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)LevelTimer_eQTaskType,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}

// source: h/2/leveltimer.c:394  [size]
void __cdecl LevelTimer_Close()
{
  int v0; // esi
  int v1; // esi

  if ( LevelTimer_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&LevelTimer_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  if ( LevelTimer_ptSerializeParameterList )
  {
    v1 = *(_DWORD *)((unsigned int)&LevelTimer_ptSerializeParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
  QTask_DeleteQTaskType(LevelTimer_eQTaskType);
}

// source: h/2/leveltimer.c:412  [size]
unsigned __int16 __cdecl LevelTimer_GetQTaskType()
{
  return LevelTimer_eQTaskType;
}
