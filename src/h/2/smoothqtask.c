/* h/2/smoothqtask.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/smoothqtask.c:86  [anchor-mhash]
void __cdecl SmoothQTask_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[4].tQTaskChildren.ptTail = nullptr;
  ptQTask[4].tQTaskRefList.ptHead = nullptr;
  ptQTask[4].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[6].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[1].tQTaskRefList.ptMiddle = (struct QReference_s *)1065353216;
  ptQTask[2].ptNext = (struct QTask_s *)1065353216;
  ptQTask[2].tQTaskChildren.ptTail = (struct QTask_s *)1065353216;
  ptQTask[1].ptNext = nullptr;
  ptQTask[1].ptPrev = nullptr;
  ptQTask[1].tQTaskChildren.ptHead = nullptr;
  ptQTask[1].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[1].tQTaskChildren.ptTail = nullptr;
  ptQTask[1].tQTaskRefList.ptHead = nullptr;
  ptQTask[1].tQTaskRefList.ptTail = nullptr;
  ptQTask[1].ptParent = nullptr;
  *(_DWORD *)&ptQTask[1].eQTaskType = 0;
  ptQTask[2].ptPrev = nullptr;
  ptQTask[2].tQTaskChildren.ptHead = nullptr;
  ptQTask[2].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[2].tQTaskRefList.ptHead = nullptr;
  LOBYTE(ptQTask[6].tQTaskChildren.ptTail) = 0;
  ptQTask[2].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[2].tQTaskRefList.ptTail = nullptr;
  ptQTask[2].ptParent = nullptr;
  *(_DWORD *)&ptQTask[2].eQTaskType = 0;
  ptQTask[3].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[3].tQTaskRefList.ptTail = nullptr;
  ptQTask[3].tQTaskChildren.ptTail = nullptr;
  ptQTask[3].tQTaskRefList.ptHead = nullptr;
  ptQTask[3].ptNext = nullptr;
  ptQTask[3].ptPrev = nullptr;
  ptQTask[3].tQTaskChildren.ptHead = nullptr;
  ptQTask[3].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[3].ptParent = nullptr;
  *(_DWORD *)&ptQTask[3].eQTaskType = 0;
  ptQTask[4].ptNext = nullptr;
  ptQTask[4].ptPrev = (struct QTask_s *)1072693248;
  ptQTask[4].tQTaskChildren.ptHead = nullptr;
  ptQTask[4].tQTaskChildren.ptMiddle = (struct QTask_s *)1072693248;
}

// source: h/2/smoothqtask.c:143  [anchor-mhash]
void __cdecl SmoothQTask_RegisterScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( !LOBYTE(ptQTask[6].tQTaskChildren.ptTail) )
  {
    LOBYTE(ptQTask[6].tQTaskChildren.ptTail) = 1;
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.vRealValue", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      Script_Float,
      &ptQTask[2].ptParent,
      8,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_FLOAT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.vIdealValue", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      Script_Float,
      &ptQTask[2].ptParent,
      8,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_FLOAT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
  }
}

// source: h/2/smoothqtask.c:176  [anchor-refs]
void __cdecl SmoothQTask_RemoveScriptSymbolsHandler(struct QTask_s *ptQTask)
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
  LOBYTE(ptQTask[6].tQTaskChildren.ptTail) = 0;
  sprintf(igi2_frame.zTemp, "%s.vRealValue", igi2_frame.zName);
  Symbol_Remove(igi2_frame.zTemp);
  sprintf(igi2_frame.zTemp, "%s.vIdealValue", igi2_frame.zName);
  Symbol_Remove(igi2_frame.zTemp);
  LOBYTE(ptQTask[6].tQTaskChildren.ptTail) = 0;
}

// source: h/2/smoothqtask.c:209  [size]
void __cdecl SmoothQTask_DeleteHandler(struct QTask_s *ptQTask)
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
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[4].tQTaskChildren.ptTail);
}

// source: h/2/smoothqtask.c:242  [size]
void __cdecl SmoothQTask_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = SmoothQTask_ptParameterList;
}

// source: h/2/smoothqtask.c:258  [anchor-mhash]
void __cdecl SmoothQTask_RunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // ecx
  int v2; // edx
  struct QTask_s *v3; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v5; // edx
  struct QTask_s *ptPrev; // eax
  double v7; // st7
  struct QReference_s *v8; // edx
  double v9; // st7
  struct QReference_s *ptTail; // ecx
  int v11; // ecx
  struct QTask_s *v12; // eax

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
  if ( ptQTask[4].tQTaskChildren.ptTail && ptQTask[4].tQTaskRefList.ptHead->ptNext && ptQTask[4].tQTaskRefList.ptMiddle )
  {
    *(double *)&ptQTask[2].tQTaskRefList.ptMiddle = Level_RunLevelExpression(
                                                      (struct LevelExpression_s *)&ptQTask[4].tQTaskChildren.ptTail,
                                                      ptQTask);
  }
  else
  {
    ptPrev = ptQTask[3].ptPrev;
    ptQTask[2].tQTaskRefList.ptMiddle = (struct QReference_s *)ptQTask[3].ptNext;
    ptQTask[2].tQTaskRefList.ptTail = (struct QReference_s *)ptPrev;
  }
  if ( *(double *)&ptQTask[2].ptParent >= *(double *)&ptQTask[2].tQTaskRefList.ptMiddle )
  {
    if ( *(double *)&ptQTask[2].ptParent > *(double *)&ptQTask[2].tQTaskRefList.ptMiddle )
    {
      v9 = *(double *)&ptQTask[2].ptParent - *(double *)&ptQTask[3].tQTaskRefList.ptMiddle;
      *(double *)&ptQTask[2].ptParent = v9;
      if ( v9 < *(double *)&ptQTask[2].tQTaskRefList.ptMiddle )
      {
        ptTail = ptQTask[2].tQTaskRefList.ptTail;
        ptQTask[2].ptParent = (struct QTask_s *)ptQTask[2].tQTaskRefList.ptMiddle;
        *(_DWORD *)&ptQTask[2].eQTaskType = ptTail;
      }
    }
  }
  else
  {
    v7 = *(double *)&ptQTask[3].tQTaskChildren.ptTail + *(double *)&ptQTask[2].ptParent;
    *(double *)&ptQTask[2].ptParent = v7;
    if ( v7 > *(double *)&ptQTask[2].tQTaskRefList.ptMiddle )
    {
      v8 = ptQTask[2].tQTaskRefList.ptTail;
      ptQTask[2].ptParent = (struct QTask_s *)ptQTask[2].tQTaskRefList.ptMiddle;
      *(_DWORD *)&ptQTask[2].eQTaskType = v8;
    }
  }
  if ( *(double *)&ptQTask[4].tQTaskChildren.ptHead != 0.0 )
    *(double *)&ptQTask[2].ptParent = (double)(int)(__int64)(*(double *)&ptQTask[2].ptParent
                                                           / *(double *)&ptQTask[4].tQTaskChildren.ptHead)
                                    * *(double *)&ptQTask[4].tQTaskChildren.ptHead;
  if ( *(double *)&ptQTask[2].ptParent >= *(double *)&ptQTask[3].ptParent )
  {
    if ( *(double *)&ptQTask[2].ptParent > *(double *)&ptQTask[4].ptNext )
    {
      v12 = ptQTask[4].ptPrev;
      ptQTask[2].ptParent = ptQTask[4].ptNext;
      *(_DWORD *)&ptQTask[2].eQTaskType = v12;
    }
  }
  else
  {
    v11 = *(_DWORD *)&ptQTask[3].eQTaskType;
    ptQTask[2].ptParent = ptQTask[3].ptParent;
    *(_DWORD *)&ptQTask[2].eQTaskType = v11;
  }
}

// source: h/2/smoothqtask.c:322  [anchor-mhash]
void __cdecl SmoothQTask_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptHead; // eax
  int v3; // edx
  struct QTask_s *v4; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, _DWORD); // ecx
  int v6; // edx
  struct QTask_s *ptMiddle; // ecx

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
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[4].tQTaskChildren.ptTail, ptQTask);
  ptMiddle = ptQTask[3].tQTaskChildren.ptMiddle;
  ptQTask[2].ptParent = ptQTask[3].tQTaskChildren.ptHead;
  *(_DWORD *)&ptQTask[2].eQTaskType = ptMiddle;
}

// source: h/2/smoothqtask.c:379  [anchor-hash]
void __cdecl SmoothQTask_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // edx

  v0 = QTask_NewQTaskType("SmoothQTask", 264, EditorRigidObj_eQTaskType, 0, 0);
  SmoothQTask_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, SmoothQTask_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, SmoothQTask_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, SmoothQTask_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))SmoothQTask_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, SmoothQTask_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eRegisterLevelScriptSymbolsEvent,
    SmoothQTask_RegisterScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eRemoveLevelScriptSymbolsEvent,
    SmoothQTask_RemoveScriptSymbolsHandler);
  v1 = (struct ParameterList_s *)Mem_AllocFn(212, 4);
  v2 = Level_eParameterTypeObjectPos;
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  v1->nParameters = 0;
  v1->nMaxParameters = 10;
  SmoothQTask_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0x28u, v2, "Position", 7u, nullptr);
  ParameterList_AddParameter(
    SmoothQTask_ptParameterList,
    0x40u,
    Level_eParameterTypeReal32x9,
    "Orientation",
    7u,
    nullptr);
  ParameterList_AddParameter(SmoothQTask_ptParameterList, 0xB0u, Level_eParameterTypeVarString, "Value", 7u, nullptr);
  ParameterList_AddParameter(
    SmoothQTask_ptParameterList,
    0x78u,
    Level_eParameterTypeReal64,
    "Initial ideal value",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SmoothQTask_ptParameterList,
    0x80u,
    Level_eParameterTypeReal64,
    "Initial real value",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SmoothQTask_ptParameterList,
    0x88u,
    Level_eParameterTypeReal64,
    "Increment value",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SmoothQTask_ptParameterList,
    0x90u,
    Level_eParameterTypeReal64,
    "Decrement value",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SmoothQTask_ptParameterList,
    0x98u,
    Level_eParameterTypeReal64,
    "Minimum final value",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SmoothQTask_ptParameterList,
    0xA0u,
    Level_eParameterTypeReal64,
    "Maximum final value",
    7u,
    nullptr);
  ParameterList_AddParameter(SmoothQTask_ptParameterList, 0xA8u, Level_eParameterTypeReal64, "Step value", 7u, nullptr);
  Symbol_Register(
    "TASKTYPE_SMOOTHQTASK",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)SmoothQTask_eQTaskType,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}

// source: h/2/smoothqtask.c:425  [size]
void __cdecl SmoothQTask_Close()
{
  int v0; // esi

  if ( SmoothQTask_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&SmoothQTask_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(SmoothQTask_eQTaskType);
}

// source: h/2/smoothqtask.c:442  [size]
unsigned __int16 __cdecl SmoothQTask_GetQTaskType()
{
  return SmoothQTask_eQTaskType;
}
