/* j/0/objects/generator.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/objects/generator.c:88  [anchor-mhash]
void __cdecl Generator_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][ExplodeObject_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  ptQTask[15].tQTaskRefList.ptMiddle = nullptr;
  LOBYTE(ptQTask[15].tQTaskRefList.ptTail) = 0;
  BYTE1(ptQTask[15].tQTaskRefList.ptTail) = 0;
  ptQTask[15].ptParent = nullptr;
  *(_DWORD *)&ptQTask[15].eQTaskType = 0;
  ptQTask[16].ptNext = nullptr;
  ptQTask[17].tQTaskRefList.ptTail = nullptr;
  LOBYTE(ptQTask[17].ptParent) = 0;
  LOBYTE(ptQTask[18].tQTaskChildren.ptHead) = 0;
  ptQTask[18].tQTaskRefList.ptMiddle = (struct QReference_s *)1092616192;
  LOBYTE(ptQTask[18].tQTaskRefList.ptTail) = 1;
  ptQTask[18].ptParent = (struct QTask_s *)-1;
}

// source: j/0/objects/generator.c:128  [anchor-mhash]
void __cdecl Generator_RunHandler(struct QTask_s *ptQTask)
{
  int ptTail_low; // ebx
  struct QTask_s *ptParent; // eax
  struct QTask_s *v3; // eax

  ptTail_low = SLOBYTE(ptQTask[15].tQTaskRefList.ptTail);
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][ExplodeObject_eQTaskType].pfHandler)(ptQTask);
  if ( LOBYTE(ptQTask[11].tQTaskChildren.ptTail) )
  {
    LOBYTE(ptQTask[15].tQTaskRefList.ptTail) = 0;
  }
  else if ( ptQTask[15].ptParent && **(_BYTE **)&ptQTask[15].eQTaskType && ptQTask[16].ptNext )
  {
    LOBYTE(ptQTask[15].tQTaskRefList.ptTail) = (__int64)Level_RunLevelExpression(
                                                          (struct LevelExpression_s *)&ptQTask[15].ptParent,
                                                          ptQTask);
  }
  if ( LOBYTE(ptQTask[18].tQTaskRefList.ptTail) )
  {
    if ( !LOBYTE(ptQTask[15].tQTaskRefList.ptTail) && ptQTask[18].ptParent == (struct QTask_s *)-1 )
      ptQTask[18].ptParent = (struct QTask_s *)(__int64)(*(float *)&ptQTask[18].tQTaskRefList.ptMiddle * 30.0);
    ptParent = ptQTask[18].ptParent;
    if ( (int)ptParent <= 0 )
      LOBYTE(ptQTask[15].tQTaskRefList.ptTail) = 1;
    else
      ptQTask[18].ptParent = (struct QTask_s *)((char *)ptParent - 1);
  }
  if ( LOBYTE(ptQTask[15].tQTaskRefList.ptTail) )
  {
    if ( !ptQTask[15].tQTaskRefList.ptMiddle )
    {
      if ( LOBYTE(ptQTask[17].ptParent) )
      {
        v3 = SoundSys_NewSoundFn(ptQTask, (char *)&ptQTask[17].ptParent);
        ptQTask[15].tQTaskRefList.ptMiddle = QTask_NewQTaskRef(v3);
      }
    }
  }
  else
  {
    QTask_DeleteQTaskAndQTaskRefSafe(&ptQTask[15].tQTaskRefList.ptMiddle);
    if ( ptTail_low )
      SoundSys_NewSoundFn(ptQTask, (char *)&ptQTask[18].tQTaskChildren);
  }
}

// source: j/0/objects/generator.c:215  [anchor-mhash]
void __cdecl Generator_DeleteHandler(struct QTask_s *ptQTask)
{
  if ( *(_DWORD *)&ptQTask[2].eQTaskType )
  {
    ModelObj_SetLODVirModel((struct ModelObj_s *)ptQTask, nullptr, false);
    ptQTask[7].tQTaskRefList.ptHead = nullptr;
    ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
    ptQTask[7].tQTaskRefList.ptTail = nullptr;
    ptQTask[7].ptParent = nullptr;
    *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  }
  QTask_DeleteQTaskAndQTaskRefSafe(&ptQTask[15].tQTaskRefList.ptMiddle);
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[2][ExplodeObject_eQTaskType].pfHandler)(ptQTask);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[15].ptParent);
}

// source: j/0/objects/generator.c:244  [size]
void __cdecl Generator_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = Generator_ptParameterList;
}

// source: j/0/objects/generator.c:260  [size]
void __cdecl Generator_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][ExplodeObject_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[15].ptParent, ptQTask);
}

// source: j/0/objects/generator.c:284  [anchor-mhash]
void __cdecl Generator_RegisterScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v1; // eax

  if ( !BYTE1(ptQTask[15].tQTaskRefList.ptTail) )
  {
    v1 = ExplodeObject_eQTaskType + 511 * Level_eRegisterLevelScriptSymbolsEvent;
    BYTE1(ptQTask[15].tQTaskRefList.ptTail) = 1;
    ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[0][v1].pfHandler)(ptQTask);
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.isOn", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      &ptQTask[15].tQTaskRefList.ptTail,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.nBackupTimer", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int,
      &ptQTask[18].ptParent,
      4,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
  }
}

// source: j/0/objects/generator.c:323  [anchor-mhash]
void __cdecl Generator_RemoveScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( BYTE1(ptQTask[15].tQTaskRefList.ptTail) )
  {
    ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Level_eRemoveLevelScriptSymbolsEvent][ExplodeObject_eQTaskType].pfHandler)(ptQTask);
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.isOn", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.nBackupTimer", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    BYTE1(ptQTask[15].tQTaskRefList.ptTail) = 0;
  }
}

// source: j/0/objects/generator.c:366  [anchor-mhash]
void __cdecl Generator_Open()
{
  unsigned __int16 v0; // si

  v0 = QTask_NewQTaskType("Generator", 760, ExplodeObject_eQTaskType, 0, 0);
  Generator_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, Generator_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, Generator_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, Generator_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Generator_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, Generator_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eRegisterLevelScriptSymbolsEvent,
    Generator_RegisterScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Level_eRemoveLevelScriptSymbolsEvent, Generator_RemoveScriptSymbolsHandler);
  Generator_ptParameterList = ParameterList_Derive(ExplodeObject_ptParameterList, 5);
  ParameterList_AddParameter(Generator_ptParameterList, 0x2C8u, Level_eParameterTypeString16, "Run sound", 7u, nullptr);
  ParameterList_AddParameter(
    Generator_ptParameterList,
    0x2D8u,
    Level_eParameterTypeString16,
    "Shutdown sound",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Generator_ptParameterList,
    0x278u,
    Level_eParameterTypeVarString,
    "On expression",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Generator_ptParameterList,
    0x2ECu,
    Level_eParameterTypebool8,
    "Use backup timer",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Generator_ptParameterList,
    0x2E8u,
    Level_eParameterTypeReal32,
    "Seconds until power backup",
    7u,
    nullptr);
}

// source: j/0/objects/generator.c:410  [size]
void __cdecl Generator_Close()
{
  int v0; // esi

  if ( Generator_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&Generator_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(Generator_eQTaskType);
}
