/* j/0/flow/conditionalcontainer.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/flow/conditionalcontainer.c:77  [anchor-mhash]
void __cdecl ConditionalContainer_RegisterChildren(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // ecx
  int v2; // edx
  struct QTask_s *v3; // eax
  void (__cdecl *pfHandler)(struct QTask_s *, struct DynCubeObjRegisterObjContext_s *); // eax
  int v5; // edx
  struct DynCubeObjRegisterObjContext_s tRegisterContext; // [esp+0h] [ebp-Ch] BYREF

  tRegisterContext.eDynCubeObjRegisterMethod = DYNCUBEOBJREGISTERMETHOD_RADIUS;
  tRegisterContext.ptWorld = Game_ptGame->ptWorld;
  ptHead = ptQTask->tQTaskChildren.ptHead;
  tRegisterContext.eDynCubeTreeCategory = 2;
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
      pfHandler = (void (__cdecl *)(struct QTask_s *, struct DynCubeObjRegisterObjContext_s *))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRegisterQTaskEvent][ptHead->eQTaskType].pfHandler;
      v5 = v2 + 1;
      QTask_nProtectedQTaskStackOffset = v5;
      if ( pfHandler )
      {
        pfHandler(ptHead, &tRegisterContext);
        v5 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v5];
      v2 = v5 - 1;
      QTask_nProtectedQTaskStackOffset = v2;
    }
    while ( ptHead );
  }
  BYTE2(ptQTask[7].ptPrev) = 1;
}

// source: j/0/flow/conditionalcontainer.c:103  [anchor-mhash]
void __cdecl ConditionalContainer_RemoveChildren(struct QTask_s *ptQTask)
{
  struct World_s *v1; // ecx
  struct QTask_s *ptHead; // ecx
  int v3; // edx
  struct QTask_s *v4; // eax
  void (__cdecl *pfHandler)(struct QTask_s *, struct DynCubeObjRemoveObjContext_s *); // eax
  int v6; // edx
  struct DynCubeObjRemoveObjContext_s tRemoveContext; // [esp+0h] [ebp-4h] BYREF

  tRemoveContext.ptWorld = v1;
  tRemoveContext.ptWorld = Game_ptGame->ptWorld;
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
      pfHandler = (void (__cdecl *)(struct QTask_s *, struct DynCubeObjRemoveObjContext_s *))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRemoveQTaskEvent][ptHead->eQTaskType].pfHandler;
      v6 = v3 + 1;
      QTask_nProtectedQTaskStackOffset = v6;
      if ( pfHandler )
      {
        pfHandler(ptHead, &tRemoveContext);
        v6 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v6];
      v3 = v6 - 1;
      QTask_nProtectedQTaskStackOffset = v3;
    }
    while ( ptHead );
  }
  BYTE2(ptQTask[7].ptPrev) = 0;
}

// source: j/0/flow/conditionalcontainer.c:127  [size]
void __cdecl ConditionalContainer_GetSerializeParameterListHandler(
        struct QTask_s *ptQTask,
        void *pxContext)
{
  *(_DWORD *)pxContext = ConditionalContainer_ptSerializeParameterList;
}

// source: j/0/flow/conditionalcontainer.c:144  [size]
// attributes: thunk
void __cdecl ConditionalContainer_DeSerializeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  Serialize_DeSerializeHandler(ptQTask, pxContext);
}

// source: j/0/flow/conditionalcontainer.c:161  [anchor-mhash]
void __cdecl ConditionalContainer_DeSerializeDoneHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // esi

  v2 = SBYTE2(ptQTask[7].ptPrev);
  ConditionalContainer_RegisterChildren(ptQTask);
  if ( !v2 )
    ConditionalContainer_RemoveChildren(ptQTask);
}

void __cdecl sub_52BF20(struct QTask_s *a1, void *a2)
{
  a1[1].ptPrev = nullptr;
  a1[1].tQTaskChildren.ptHead = nullptr;
  a1[1].tQTaskChildren.ptMiddle = nullptr;
  a1[3].ptNext = nullptr;
  a1[3].ptPrev = nullptr;
  a1[3].tQTaskChildren.ptHead = nullptr;
  a1[3].tQTaskChildren.ptMiddle = nullptr;
  a1[5].ptNext = nullptr;
  a1[5].ptPrev = nullptr;
  a1[5].tQTaskChildren.ptHead = nullptr;
  a1[5].tQTaskChildren.ptMiddle = nullptr;
  a1[7].ptNext = nullptr;
  LOBYTE(a1[7].ptPrev) = 0;
  BYTE2(a1[7].ptPrev) = 1;
  BYTE1(a1[7].ptPrev) = 0;
  LOBYTE(a1[1].ptNext) = 0;
}

// source: j/0/flow/conditionalcontainer.c:209  [anchor-mhash]
void __cdecl ConditionalContainer_RunHandler(struct QTask_s *ptQTask)
{
  int ptPrev_low; // ebx
  char v2; // al
  struct QTask_s *ptHead; // ecx
  int v4; // edx
  struct QTask_s *v5; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v7; // edx
  struct LevelExpression_s *p_ptPrev; // eax
  bool v9; // zf

  ptPrev_low = SLOBYTE(ptQTask[7].ptPrev);
  if ( ptQTask[1].ptPrev && ptQTask[1].tQTaskChildren.ptHead->ptNext && ptQTask[1].tQTaskChildren.ptMiddle )
    LOBYTE(ptQTask[7].ptPrev) = (__int64)Level_RunLevelExpression(
                                           (struct LevelExpression_s *)&ptQTask[1].ptPrev,
                                           ptQTask);
  v2 = BYTE2(ptQTask[7].ptPrev);
  if ( LOBYTE(ptQTask[7].ptPrev) )
  {
    if ( !v2 )
      ConditionalContainer_RegisterChildren(ptQTask);
    ptHead = ptQTask->tQTaskChildren.ptHead;
    if ( ptHead->ptNext && ptHead )
    {
      v4 = QTask_nProtectedQTaskStackOffset;
      do
      {
        if ( ptHead->ptNext )
          v5 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
        else
          v5 = nullptr;
        QTask_atProtectedQTaskStack[v4].ptQTask = v5;
        pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][ptHead->eQTaskType].pfHandler;
        v7 = v4 + 1;
        QTask_nProtectedQTaskStackOffset = v7;
        if ( pfHandler )
        {
          pfHandler(ptHead);
          v7 = QTask_nProtectedQTaskStackOffset;
        }
        ptHead = (struct QTask_s *)dword_849C7DC[v7];
        v4 = v7 - 1;
        QTask_nProtectedQTaskStackOffset = v4;
      }
      while ( ptHead );
    }
  }
  else if ( v2 )
  {
    ConditionalContainer_RemoveChildren(ptQTask);
  }
  if ( LOBYTE(ptQTask[7].ptPrev) )
  {
    if ( ptPrev_low )
      return;
    p_ptPrev = (struct LevelExpression_s *)&ptQTask[3].ptPrev;
    if ( !ptQTask[3].ptPrev )
      return;
    v9 = ptQTask[3].tQTaskChildren.ptHead->ptNext == nullptr;
  }
  else
  {
    if ( !ptPrev_low )
      return;
    p_ptPrev = (struct LevelExpression_s *)&ptQTask[5].ptPrev;
    if ( !ptQTask[5].ptPrev )
      return;
    v9 = ptQTask[5].tQTaskChildren.ptHead->ptNext == nullptr;
  }
  if ( !v9 )
  {
    if ( p_ptPrev->ptExpression )
      Level_RunLevelExpression(p_ptPrev, ptQTask);
  }
}

// source: j/0/flow/conditionalcontainer.c:276  [anchor-mhash]
void __cdecl ConditionalContainer_DeleteHandler(struct QTask_s *ptQTask)
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
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[1].ptPrev);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[3].ptPrev);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[5].ptPrev);
}

// source: j/0/flow/conditionalcontainer.c:301  [size]
void __cdecl ConditionalContainer_MagicObjEnterHandler(struct QTask_s *ptQTask, void *pxContext)
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
      pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[MagicObj_eMagicObjEnterEvent][ptHead->eQTaskType].pfHandler;
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

// source: j/0/flow/conditionalcontainer.c:314  [size]
void __cdecl ConditionalContainer_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = ConditionalContainer_ptParameterList;
}

// source: j/0/flow/conditionalcontainer.c:330  [anchor-mhash]
void __cdecl ConditionalContainer_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[1].ptPrev, ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[3].ptPrev, ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[5].ptPrev, ptQTask);
}

// source: j/0/flow/conditionalcontainer.c:349  [anchor-mhash]
void __cdecl ConditionalContainer_DrawComputerObjectHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptHead; // esi
  __int16 v3; // ax
  struct QTask_s *v4; // ecx
  int v5; // edx
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // ecx

  if ( BYTE2(ptQTask[7].ptPrev) )
  {
    ptHead = ptQTask->tQTaskChildren.ptHead;
    if ( ptHead->ptNext )
    {
      if ( ptHead )
      {
        v3 = ComputerObject_eDrawComputerObjectQTaskEvent;
        do
        {
          if ( ptHead->ptNext )
            v4 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
          else
            v4 = nullptr;
          v5 = QTask_nProtectedQTaskStackOffset;
          QTask_atProtectedQTaskStack[QTask_nProtectedQTaskStackOffset].ptQTask = v4;
          QTask_nProtectedQTaskStackOffset = v5 + 1;
          if ( v3 == 512 )
          {
            v3 = QTask_NewQTaskEventFn(0x200u, "DrawComputerObject");
            ComputerObject_eDrawComputerObjectQTaskEvent = v3;
          }
          pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[v3][ptHead->eQTaskType].pfHandler;
          if ( pfHandler )
          {
            pfHandler(ptHead, pxContext);
            v3 = ComputerObject_eDrawComputerObjectQTaskEvent;
          }
          ptHead = (struct QTask_s *)dword_849C7DC[QTask_nProtectedQTaskStackOffset--];
        }
        while ( ptHead );
      }
    }
  }
}

// source: j/0/flow/conditionalcontainer.c:388  [size]
void __cdecl ConditionalContainer_RegisterScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( !BYTE1(ptQTask[7].ptPrev) )
  {
    BYTE1(ptQTask[7].ptPrev) = 1;
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.isRun", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      &ptQTask[7].ptPrev,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
  }
}

// source: j/0/flow/conditionalcontainer.c:415  [size]
void __cdecl ConditionalContainer_RemoveScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( BYTE1(ptQTask[7].ptPrev) )
  {
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.isRun", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    BYTE1(ptQTask[7].ptPrev) = 0;
  }
}

// source: j/0/flow/conditionalcontainer.c:444  [anchor-mhash]
void __cdecl ConditionalContainer_RegisterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptHead; // eax
  int v3; // edx
  struct QTask_s *v4; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // ecx
  int v6; // edx

  if ( LOBYTE(ptQTask[7].ptPrev) && !BYTE2(ptQTask[7].ptPrev) )
  {
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
    BYTE2(ptQTask[7].ptPrev) = 1;
  }
}

// source: j/0/flow/conditionalcontainer.c:465  [anchor-mhash]
void __cdecl ConditionalContainer_RemoveHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptHead; // eax
  int v3; // edx
  struct QTask_s *v4; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // ecx
  int v6; // edx

  if ( BYTE2(ptQTask[7].ptPrev) )
  {
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
    BYTE2(ptQTask[7].ptPrev) = 0;
  }
  LOBYTE(ptQTask[7].ptPrev) = 0;
}

void __cdecl sub_52C4B0(struct QTask_s *a1)
{
  struct QTask_s *ptHead; // ecx
  int v2; // edx
  struct QTask_s *v3; // eax
  int v4; // esi
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v6; // edx

  ptHead = a1->tQTaskChildren.ptHead;
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

void __cdecl sub_52C530(struct QTask_s *a1)
{
  struct QTask_s *ptHead; // ecx
  int v2; // edx
  struct QTask_s *v3; // eax
  void (__cdecl *pfHandler)(struct QTask_s *, _DWORD); // eax
  int v5; // edx

  ptHead = a1->tQTaskChildren.ptHead;
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
      pfHandler = (void (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[4][ptHead->eQTaskType].pfHandler;
      v5 = v2 + 1;
      QTask_nProtectedQTaskStackOffset = v5;
      if ( pfHandler )
      {
        pfHandler(ptHead, 0);
        v5 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v5];
      v2 = v5 - 1;
      QTask_nProtectedQTaskStackOffset = v2;
    }
    while ( ptHead );
  }
}

// source: j/0/flow/conditionalcontainer.c:529  [anchor-hash]
void __cdecl ConditionalContainer_Open()
{
  unsigned __int16 v0; // si
  __int16 v1; // ax
  struct ParameterList_s *v2; // eax
  int v3; // edx
  unsigned __int16 v4; // si
  struct ParameterList_s *v5; // eax
  int v6; // edx

  v0 = QTask_NewQTaskType("ConditionalContainer", 288, Container_eQTaskType, 0, 0);
  ConditionalContainer_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, (void (__cdecl *)(struct QTask_s *, void *))sub_52BF20);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, ConditionalContainer_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, ConditionalContainer_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v0, MagicObj_eMagicObjEnterEvent, ConditionalContainer_MagicObjEnterHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))ConditionalContainer_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eUpdateInternalDataQTaskEvent,
    ConditionalContainer_UpdateInternalDataHandler);
  v1 = ComputerObject_eDrawComputerObjectQTaskEvent;
  if ( ComputerObject_eDrawComputerObjectQTaskEvent == 512 )
  {
    v1 = QTask_NewQTaskEventFn(0x200u, "DrawComputerObject");
    v0 = ConditionalContainer_eQTaskType;
    ComputerObject_eDrawComputerObjectQTaskEvent = v1;
  }
  QTask_LinkQTaskEventHandlerFn(v0, v1, ConditionalContainer_DrawComputerObjectHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eRegisterLevelScriptSymbolsEvent,
    ConditionalContainer_RegisterScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eRemoveLevelScriptSymbolsEvent,
    ConditionalContainer_RemoveScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerFn(v0, DynCubeObj_eDynCubeObjRemoveQTaskEvent, ConditionalContainer_RemoveHandler);
  QTask_LinkQTaskEventHandlerFn(v0, DynCubeObj_eDynCubeObjRegisterQTaskEvent, ConditionalContainer_RegisterHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Attach_eUpdateAttachmentEvent, sub_52C4B0);
  QTask_LinkQTaskEventHandlerFn(v0, 4, (void (__cdecl *)(struct QTask_s *, void *))sub_52C530);
  v2 = (struct ParameterList_s *)Mem_AllocFn(72, 4);
  v2->ptParameterListItem = (struct ParameterListItem_s *)&v2[1];
  v3 = Level_eParameterTypeVarString;
  v2->nParameters = 0;
  v2->nMaxParameters = 3;
  ConditionalContainer_ptParameterList = v2;
  ParameterList_AddParameter(v2, 0x2Cu, v3, "Condition", 7u, nullptr);
  ParameterList_AddParameter(
    ConditionalContainer_ptParameterList,
    0x7Cu,
    Level_eParameterTypeVarString,
    "Run at start",
    7u,
    nullptr);
  ParameterList_AddParameter(
    ConditionalContainer_ptParameterList,
    0xCCu,
    Level_eParameterTypeVarString,
    "Run at stop",
    7u,
    nullptr);
  v4 = ConditionalContainer_eQTaskType;
  QTask_LinkQTaskEventHandlerFn(
    ConditionalContainer_eQTaskType,
    Serialize_eGetSerializeParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))ConditionalContainer_GetSerializeParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v4, Serialize_eDeSerializeQTaskEvent, ConditionalContainer_DeSerializeHandler);
  QTask_LinkQTaskEventHandlerFn(v4, Serialize_eDeSerializeDoneQTaskEvent, ConditionalContainer_DeSerializeDoneHandler);
  v5 = (struct ParameterList_s *)Mem_AllocFn(52, 4);
  v5->ptParameterListItem = (struct ParameterListItem_s *)&v5[1];
  v6 = Level_eParameterTypebool8;
  v5->nParameters = 0;
  v5->nMaxParameters = 2;
  ConditionalContainer_ptSerializeParameterList = v5;
  ParameterList_AddParameter(v5, 0x11Eu, v6, "isChildrenRegistered", 7u, nullptr);
  ParameterList_AddParameter(
    ConditionalContainer_ptSerializeParameterList,
    0x11Cu,
    Level_eParameterTypebool8,
    "isRun",
    7u,
    nullptr);
}

// source: j/0/flow/conditionalcontainer.c:579  [size]
void __cdecl ConditionalContainer_Close()
{
  int v0; // esi
  int v1; // esi

  QTask_DeleteQTaskType(ConditionalContainer_eQTaskType);
  if ( ConditionalContainer_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&ConditionalContainer_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  if ( ConditionalContainer_ptSerializeParameterList )
  {
    v1 = *(_DWORD *)((unsigned int)&ConditionalContainer_ptSerializeParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
}

// source: j/0/flow/conditionalcontainer.c:597  [size]
unsigned __int16 __cdecl ConditionalContainer_GetQTaskType()
{
  return ConditionalContainer_eQTaskType;
}
