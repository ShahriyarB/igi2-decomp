/* j/0/editvariable.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/editvariable.c:72  [size]
void __cdecl EditVariable_GetSerializeParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = EditVariable_ptSerializeParameterList;
}

// source: j/0/editvariable.c:90  [size]
void __cdecl EditVariable_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[1].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[1].tQTaskRefList.ptTail = nullptr;
  ptQTask[1].ptParent = nullptr;
  ptQTask[3].tQTaskRefList.ptHead = nullptr;
  ptQTask[3].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[3].tQTaskRefList.ptTail = nullptr;
  ptQTask[3].ptParent = nullptr;
  ptQTask[5].tQTaskRefList.ptHead = nullptr;
  ptQTask[5].tQTaskRefList.ptMiddle = nullptr;
  LOBYTE(ptQTask[5].tQTaskRefList.ptTail) = 0;
}

// source: j/0/editvariable.c:132  [anchor-mhash]
void __cdecl EditVariable_RunHandler(struct QTask_s *ptQTask)
{
  if ( ptQTask[1].tQTaskRefList.ptMiddle && ptQTask[1].tQTaskRefList.ptTail->ptNext && ptQTask[1].ptParent )
    ptQTask[5].tQTaskRefList.ptMiddle = (struct QReference_s *)((char *)ptQTask[5].tQTaskRefList.ptMiddle
                                                              + (__int64)Level_RunLevelExpression(
                                                                           (struct LevelExpression_s *)&ptQTask[1].tQTaskRefList.ptMiddle,
                                                                           ptQTask));
  if ( ptQTask[3].tQTaskRefList.ptMiddle && ptQTask[3].tQTaskRefList.ptTail->ptNext )
  {
    if ( ptQTask[3].ptParent )
      ptQTask[5].tQTaskRefList.ptMiddle = (struct QReference_s *)((char *)ptQTask[5].tQTaskRefList.ptMiddle
                                                                - (__int64)Level_RunLevelExpression(
                                                                             (struct LevelExpression_s *)&ptQTask[3].tQTaskRefList.ptMiddle,
                                                                             ptQTask));
  }
}

// source: j/0/editvariable.c:169  [anchor-mhash]
void __cdecl EditVariable_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QReference_s **v1; // ecx
  int v2; // ecx
  struct QReference_s *v3; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax

  v1 = Level_atLevelQTaskID;
  do
  {
    if ( *v1 && (*v1)->pxObject == ptQTask )
      break;
    ++v1;
  }
  while ( (int)v1 < 127904760 );
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
      goto LABEL_13;
  }
  if ( v2 >= 0 )
  {
    pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Level_eRemoveLevelScriptSymbolsEvent][ptQTask->eQTaskType].pfHandler;
    if ( pfHandler )
      pfHandler(ptQTask);
  }
LABEL_13:
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[1].tQTaskRefList.ptMiddle);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[3].tQTaskRefList.ptMiddle);
}

// source: j/0/editvariable.c:206  [size]
void __cdecl EditVariable_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = EditVariable_ptParameterList;
}

// source: j/0/editvariable.c:222  [size]
void __cdecl EditVariable_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[1].tQTaskRefList.ptMiddle, ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[3].tQTaskRefList.ptMiddle, ptQTask);
}

// source: j/0/editvariable.c:258  [size]
void __cdecl EditVariable_RegisterScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( !LOBYTE(ptQTask[5].tQTaskRefList.ptTail) )
  {
    LOBYTE(ptQTask[5].tQTaskRefList.ptTail) = 1;
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.nValue", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int,
      &ptQTask[5].tQTaskRefList.ptMiddle,
      4,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
  }
}

// source: j/0/editvariable.c:290  [size]
void __cdecl EditVariable_RemoveScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( LOBYTE(ptQTask[5].tQTaskRefList.ptTail) )
  {
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.nValue", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    LOBYTE(ptQTask[5].tQTaskRefList.ptTail) = 0;
  }
}

// source: j/0/editvariable.c:326  [anchor-hash]
void __cdecl EditVariable_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // edx
  struct ParameterList_s *v3; // eax
  int v4; // edx

  v0 = QTask_NewQTaskType("EditVariable", 232, EditorRigidObj_eQTaskType, 0, 0);
  EditVariable_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveNoChildrenHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, (void (__cdecl *)(struct QTask_s *, void *))EditVariable_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, EditVariable_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, EditVariable_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))EditVariable_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, EditVariable_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eRegisterLevelScriptSymbolsEvent,
    EditVariable_RegisterScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eRemoveLevelScriptSymbolsEvent,
    EditVariable_RemoveScriptSymbolsHandler);
  v1 = (struct ParameterList_s *)Mem_AllocFn(92, 4);
  v2 = Level_eParameterTypeObjectPos;
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  v1->nParameters = 0;
  v1->nMaxParameters = 4;
  EditVariable_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0x28u, v2, "Position", 7u, nullptr);
  ParameterList_AddParameter(
    EditVariable_ptParameterList,
    0xE0u,
    Level_eParameterTypeInt32,
    "Initial value",
    7u,
    nullptr);
  ParameterList_AddParameter(EditVariable_ptParameterList, 0x40u, Level_eParameterTypeVarString, "Add", 7u, nullptr);
  ParameterList_AddParameter(EditVariable_ptParameterList, 0x90u, Level_eParameterTypeVarString, "Sub", 7u, nullptr);
  QTask_LinkQTaskEventHandlerFn(
    EditVariable_eQTaskType,
    Serialize_eGetSerializeParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))EditVariable_GetSerializeParameterListHandler);
  v3 = (struct ParameterList_s *)Mem_AllocFn(32, 4);
  v4 = Level_eParameterTypeInt32;
  v3->ptParameterListItem = (struct ParameterListItem_s *)&v3[1];
  v3->nParameters = 0;
  v3->nMaxParameters = 1;
  EditVariable_ptSerializeParameterList = v3;
  ParameterList_AddParameter(v3, 0xE0u, v4, "Initial value", 7u, nullptr);
}

// source: j/0/editvariable.c:368  [size]
void __cdecl EditVariable_Close()
{
  int v0; // esi
  int v1; // esi

  if ( EditVariable_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&EditVariable_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  if ( EditVariable_ptSerializeParameterList )
  {
    v1 = *(_DWORD *)((unsigned int)&EditVariable_ptSerializeParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
  QTask_DeleteQTaskType(EditVariable_eQTaskType);
}
