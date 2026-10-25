/* j/0/objects/soundgenerator.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/objects/soundgenerator.c:67  [anchor-hash]
void __cdecl SoundGenerator_StopSound(struct QTask_s *ptQTask)
{
  int v1; // eax
  struct QTask_s *v2; // eax
  struct QReference_s *v3; // eax

  v1 = *(_DWORD *)&ptQTask[1].eQTaskType;
  if ( v1 )
  {
    v2 = *(struct QTask_s **)(v1 + 8);
    if ( v2 )
      QTask_Delete(v2);
  }
  v3 = *(struct QReference_s **)&ptQTask[1].eQTaskType;
  if ( v3 )
  {
    QReference_Delete(v3, &QTask_tQTaskRefPool);
    *(_DWORD *)&ptQTask[1].eQTaskType = 0;
  }
  LOBYTE(ptQTask[1].ptParent) = 0;
}

// source: j/0/objects/soundgenerator.c:92  [anchor-hash]
void __cdecl SoundGenerator_PlaySound(struct QTask_s *ptQTask)
{
  int v1; // eax
  struct QTask_s *v2; // eax
  struct QReference_s *v3; // eax
  struct QTask_s *v4; // eax

  v1 = *(_DWORD *)&ptQTask[1].eQTaskType;
  if ( v1 )
  {
    v2 = *(struct QTask_s **)(v1 + 8);
    if ( v2 )
      QTask_Delete(v2);
  }
  v3 = *(struct QReference_s **)&ptQTask[1].eQTaskType;
  if ( v3 )
  {
    QReference_Delete(v3, &QTask_tQTaskRefPool);
    *(_DWORD *)&ptQTask[1].eQTaskType = 0;
  }
  LOBYTE(ptQTask[1].ptParent) = 0;
  if ( strlen((char *)&ptQTask[1]) )
  {
    v4 = SoundSys_NewSoundFn(ptQTask, (char *)&ptQTask[1]);
    if ( v4 )
    {
      *(_DWORD *)&ptQTask[1].eQTaskType = QTask_NewQTaskRef(v4);
      LOBYTE(ptQTask[1].ptParent) = 1;
    }
  }
}

// source: j/0/objects/soundgenerator.c:120  [size]
void __cdecl SoundGenerator_GetSerializeParameterListHandler(
        struct QTask_s *ptQTask,
        void *pxContext)
{
  *(_DWORD *)pxContext = SoundGenerator_ptSerializeParameterList;
}

// source: j/0/objects/soundgenerator.c:136  [anchor-mhash]
void __cdecl SoundGenerator_SerializeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  char ptParent; // bl
  int v3; // eax

  ptParent = (char)ptQTask[1].ptParent;
  if ( ptParent )
  {
    v3 = *(_DWORD *)&ptQTask[1].eQTaskType;
    if ( !v3 || !*(_DWORD *)(v3 + 8) )
      LOBYTE(ptQTask[1].ptParent) = 0;
  }
  Serialize_SerializeHandler(ptQTask, pxContext);
  LOBYTE(ptQTask[1].ptParent) = ptParent;
}

// source: j/0/objects/soundgenerator.c:161  [anchor-mhash]
void __cdecl SoundGenerator_DeSerializeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  QTask_DeleteQTaskAndQTaskRefSafe((struct QReference_s **)&ptQTask[1].eQTaskType);
  Serialize_DeSerializeHandler(ptQTask, pxContext);
  if ( LOBYTE(ptQTask[1].ptParent) )
    SoundGenerator_PlaySound(ptQTask);
}

// source: j/0/objects/soundgenerator.c:186  [anchor-mhash]
struct Result_s *__cdecl SoundGenerator_PlaySoundScriptFunction(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  if ( ptArgList->nArguments > 0
    && pxContext
    && QTask_IsQTaskTypeDerived(*((_WORD *)pxContext + 18), SoundGenerator_eQTaskType) )
  {
    if ( ptArgList->isQVM )
    {
      *((_BYTE *)pxContext + 40) = 0;
      QVM_EvalArg((char *)pxContext + 40, 32, ptArgList, 0, 3);
    }
    else
    {
      Expression_EvalString(*ptArgList->aptExpression, (char *)pxContext + 40, 32);
    }
    SoundGenerator_PlaySound((struct QTask_s *)pxContext);
  }
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/objects/soundgenerator.c:214  [anchor-caller]
struct Result_s *__cdecl SoundGenerator_StopSoundScriptFunction(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  if ( pxContext && QTask_IsQTaskTypeDerived(*((_WORD *)pxContext + 18), SoundGenerator_eQTaskType) )
    SoundGenerator_StopSound((struct QTask_s *)pxContext);
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/objects/soundgenerator.c:234  [size]
void __cdecl SoundGenerator_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  LOBYTE(ptQTask[1].ptNext) = 0;
  LOBYTE(ptQTask[1].ptParent) = 0;
  *(_DWORD *)&ptQTask[1].eQTaskType = 0;
  ptQTask[2].ptNext = nullptr;
}

// source: j/0/objects/soundgenerator.c:253  [size]
void __cdecl SoundGenerator_RegisterScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( !ptQTask[2].ptNext )
  {
    ptQTask[2].ptNext = (struct QTask_s *)1;
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.isPlaying", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      &ptQTask[1].ptParent,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
  }
}

// source: j/0/objects/soundgenerator.c:280  [size]
void __cdecl SoundGenerator_RemoveScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( ptQTask[2].ptNext )
  {
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.isPlaying", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    ptQTask[2].ptNext = nullptr;
  }
}

// source: j/0/objects/soundgenerator.c:309  [anchor-mhash]
void __cdecl SoundGenerator_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QReference_s *v1; // eax
  int v2; // ecx
  struct QReference_s *v3; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax

  v1 = *(struct QReference_s **)&ptQTask[1].eQTaskType;
  if ( v1 )
  {
    QReference_Delete(v1, &QTask_tQTaskRefPool);
    *(_DWORD *)&ptQTask[1].eQTaskType = 0;
  }
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
  if ( v2 >= 0 )
  {
    pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Level_eRemoveLevelScriptSymbolsEvent][ptQTask->eQTaskType].pfHandler;
    if ( pfHandler )
      pfHandler(ptQTask);
  }
}

// source: j/0/objects/soundgenerator.c:330  [anchor-strings]
void __cdecl SoundGenerator_RunHandler(struct QTask_s *ptQTask)
{
  struct QHashTable_s *v1; // esi
  unsigned int v2; // eax
  int v3; // eax
  struct QHashTable_s *v4; // esi
  unsigned int v5; // eax
  int v6; // eax
  struct QTask_s *ptHead; // ecx
  int v8; // edx
  struct QTask_s *v9; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v11; // edx
  struct QHashTable_s *v12; // esi
  unsigned int v13; // eax
  int v14; // eax
  struct QHashTable_s *v15; // esi
  unsigned int v16; // eax
  int v17; // eax

  v1 = Symbol_ptSymbolHashTable;
  v2 = Symbol_ptSymbolHashTable->tPrivate.pfHashFunction(
         Symbol_ptSymbolHashTable->tPrivate.nHashTableSize,
         "SoundGenerator_PlaySound");
  v3 = ((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Symbol_ptSymbolHashTable->tPrivate.pfFindElement)(v1, v2, (const void *)("SoundGenerator_PlaySound"));
  if ( !v3 || !*(_DWORD *)(v3 + 20) )
  {
    LDebug_Error("Script_SetSymbolContext(): Symbol not found: %s", "SoundGenerator_PlaySound");
LABEL_20:
    abort();
  }
  *(_DWORD *)(v3 + 24) = ptQTask;
  v4 = Symbol_ptSymbolHashTable;
  v5 = Symbol_ptSymbolHashTable->tPrivate.pfHashFunction(
         Symbol_ptSymbolHashTable->tPrivate.nHashTableSize,
         "SoundGenerator_StopSound");
  v6 = ((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Symbol_ptSymbolHashTable->tPrivate.pfFindElement)(v4, v5, (const void *)("SoundGenerator_StopSound"));
  if ( !v6 || !*(_DWORD *)(v6 + 20) )
    goto LABEL_19;
  *(_DWORD *)(v6 + 24) = ptQTask;
  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v8 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v9 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v9 = nullptr;
      QTask_atProtectedQTaskStack[v8].ptQTask = v9;
      pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][ptHead->eQTaskType].pfHandler;
      v11 = v8 + 1;
      QTask_nProtectedQTaskStackOffset = v11;
      if ( pfHandler )
      {
        pfHandler(ptHead);
        v11 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v11];
      v8 = v11 - 1;
      QTask_nProtectedQTaskStackOffset = v8;
    }
    while ( ptHead );
  }
  v12 = Symbol_ptSymbolHashTable;
  v13 = Symbol_ptSymbolHashTable->tPrivate.pfHashFunction(
          Symbol_ptSymbolHashTable->tPrivate.nHashTableSize,
          "SoundGenerator_PlaySound");
  v14 = ((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Symbol_ptSymbolHashTable->tPrivate.pfFindElement)(v12, v13, (const void *)("SoundGenerator_PlaySound"));
  if ( !v14 || !*(_DWORD *)(v14 + 20) )
  {
    LDebug_Error("Script_SetSymbolContext(): Symbol not found: %s", "SoundGenerator_PlaySound");
    goto LABEL_20;
  }
  *(_DWORD *)(v14 + 24) = 0;
  v15 = Symbol_ptSymbolHashTable;
  v16 = Symbol_ptSymbolHashTable->tPrivate.pfHashFunction(
          Symbol_ptSymbolHashTable->tPrivate.nHashTableSize,
          "SoundGenerator_StopSound");
  v17 = ((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Symbol_ptSymbolHashTable->tPrivate.pfFindElement)(v15, v16, (const void *)("SoundGenerator_StopSound"));
  if ( !v17 || !*(_DWORD *)(v17 + 20) )
  {
LABEL_19:
    LDebug_Error("Script_SetSymbolContext(): Symbol not found: %s", "SoundGenerator_StopSound");
    goto LABEL_20;
  }
  *(_DWORD *)(v17 + 24) = 0;
}

// source: j/0/objects/soundgenerator.c:350  [anchor-mhash]
void __cdecl SoundGenerator_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // eax
  struct QTask_s *v3; // eax
  struct QReference_s *v4; // eax

  v2 = *(_DWORD *)&ptQTask[1].eQTaskType;
  if ( v2 )
  {
    v3 = *(struct QTask_s **)(v2 + 8);
    if ( v3 )
      QTask_Delete(v3);
  }
  v4 = *(struct QReference_s **)&ptQTask[1].eQTaskType;
  if ( v4 )
  {
    QReference_Delete(v4, &QTask_tQTaskRefPool);
    *(_DWORD *)&ptQTask[1].eQTaskType = 0;
  }
  LOBYTE(ptQTask[1].ptParent) = 0;
}

// source: j/0/objects/soundgenerator.c:366  [size]
void __cdecl SoundGenerator_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = SoundGenerator_ptParameterList;
}

// source: j/0/objects/soundgenerator.c:382  [size]
void __cdecl SoundGenerator_UpdateAttachmentHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // ecx
  int v2; // edx
  struct QTask_s *v3; // eax
  int v4; // esi
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v6; // edx

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
      v4 = Attach_eUpdateAttachmentEvent;
      QTask_atProtectedQTaskStack[v2].ptQTask = v3;
      pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[v4][ptHead->eQTaskType].pfHandler;
      v6 = v2 + 1;
      QTask_nProtectedQTaskStackOffset = v6;
      if ( pfHandler )
      {
        pfHandler(ptHead);
        v6 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v6];
      v2 = v6 - 1;
      QTask_nProtectedQTaskStackOffset = v2;
    }
    while ( ptHead );
  }
}

// source: j/0/objects/soundgenerator.c:395  [anchor-mhash]
void __cdecl SoundGenerator_RegisterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v2; // eax

  if ( LOBYTE(ptQTask[1].ptParent) && strlen((char *)&ptQTask[1]) )
  {
    v2 = SoundSys_NewSoundFn(ptQTask, (char *)&ptQTask[1]);
    if ( v2 )
    {
      *(_DWORD *)&ptQTask[1].eQTaskType = QTask_NewQTaskRef(v2);
      LOBYTE(ptQTask[1].ptParent) = 1;
    }
  }
}

// source: j/0/objects/soundgenerator.c:422  [size]
void __cdecl SoundGenerator_RemoveHandler(struct QTask_s *ptQTask, void *pxContext)
{
  QTask_DeleteQTaskAndQTaskRefSafe((struct QReference_s **)&ptQTask[1].eQTaskType);
}

// source: j/0/objects/soundgenerator.c:440  [size]
unsigned __int16 __cdecl SoundGenerator_GetQTaskType()
{
  return SoundGenerator_eQTaskType;
}

// source: j/0/objects/soundgenerator.c:453  [anchor-hash]
void __cdecl SoundGenerator_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si
  struct ParameterList_s *v2; // eax
  unsigned __int16 v3; // si
  struct ParameterList_s *v4; // eax
  int v5; // edx

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("SoundGenerator", 84, BaseQTaskType, 0, 0);
  SoundGenerator_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 0, (void (__cdecl *)(struct QTask_s *, void *))SoundGenerator_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eUpdateInternalDataQTaskEvent,
    SoundGenerator_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))SoundGenerator_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v1, DynCubeObj_eDynCubeObjRegisterQTaskEvent, SoundGenerator_RegisterHandler);
  QTask_LinkQTaskEventHandlerFn(v1, DynCubeObj_eDynCubeObjRemoveQTaskEvent, SoundGenerator_RemoveHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, Attach_eUpdateAttachmentEvent, SoundGenerator_UpdateAttachmentHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, SoundGenerator_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, SoundGenerator_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v1,
    Level_eRegisterLevelScriptSymbolsEvent,
    SoundGenerator_RegisterScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v1,
    Level_eRemoveLevelScriptSymbolsEvent,
    SoundGenerator_RemoveScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  v2 = (struct ParameterList_s *)Mem_AllocFn(32, 4);
  v2->nParameters = 0;
  v2->nMaxParameters = 1;
  v2->ptParameterListItem = (struct ParameterListItem_s *)&v2[1];
  SoundGenerator_ptParameterList = v2;
  Symbol_Register(
    "SoundGenerator_StopSound",
    SoundGenerator_StopSoundScriptFunction,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "SoundGenerator_PlaySound",
    SoundGenerator_PlaySoundScriptFunction,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  v3 = SoundGenerator_eQTaskType;
  QTask_LinkQTaskEventHandlerFn(
    SoundGenerator_eQTaskType,
    Serialize_eGetSerializeParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))SoundGenerator_GetSerializeParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v3, Serialize_eSerializeQTaskEvent, SoundGenerator_SerializeHandler);
  QTask_LinkQTaskEventHandlerFn(v3, Serialize_eDeSerializeQTaskEvent, SoundGenerator_DeSerializeHandler);
  v4 = (struct ParameterList_s *)Mem_AllocFn(52, 4);
  v5 = Level_eParameterTypeString32;
  v4->ptParameterListItem = (struct ParameterListItem_s *)&v4[1];
  v4->nParameters = 0;
  v4->nMaxParameters = 2;
  SoundGenerator_ptSerializeParameterList = v4;
  ParameterList_AddParameter(v4, 0x28u, v5, "zSound", 7u, nullptr);
  ParameterList_AddParameter(
    SoundGenerator_ptSerializeParameterList,
    0x48u,
    Level_eParameterTypebool8,
    "isPlaying",
    7u,
    nullptr);
}

// source: j/0/objects/soundgenerator.c:499  [anchor-hash]
void __cdecl SoundGenerator_Close()
{
  int v0; // esi
  int v1; // esi

  Symbol_Remove("SoundGenerator_StopSound");
  Symbol_Remove("SoundGenerator_PlaySound");
  if ( SoundGenerator_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&SoundGenerator_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  if ( SoundGenerator_ptSerializeParameterList )
  {
    v1 = *(_DWORD *)((unsigned int)&SoundGenerator_ptSerializeParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
  QTask_DeleteQTaskType(SoundGenerator_eQTaskType);
}
