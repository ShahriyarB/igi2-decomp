/* j/0/objects/radio.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/objects/radio.c:82  [anchor-mhash]
void __cdecl Radio_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  unsigned __int16 *p_eQTaskType; // eax
  int v3; // edx

  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][ExplodeObject_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  ptQTask[15].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[15].tQTaskRefList.ptTail = nullptr;
  LOBYTE(ptQTask[15].ptParent) = 0;
  BYTE1(ptQTask[15].ptParent) = 0;
  *(_DWORD *)&ptQTask[15].eQTaskType = 0;
  ptQTask[16].ptNext = nullptr;
  ptQTask[16].ptPrev = nullptr;
  ptQTask[17].ptParent = nullptr;
  p_eQTaskType = &ptQTask[17].eQTaskType;
  v3 = 4;
  do
  {
    *(_BYTE *)p_eQTaskType = 0;
    p_eQTaskType += 8;
    --v3;
  }
  while ( v3 );
  LOBYTE(ptQTask[19].tQTaskRefList.ptHead) = 0;
}

// source: j/0/objects/radio.c:125  [anchor-mhash]
void __cdecl Radio_RunHandler(struct QTask_s *ptQTask)
{
  int ptParent_low; // ebp
  struct QReference_s *ptMiddle; // eax
  struct QReference_s *ptTail; // eax
  struct Game_s *v4; // eax
  unsigned int v5; // edx
  unsigned int v6; // esi
  unsigned int v7; // edx
  struct QTask_s *v8; // esi
  struct Game_s *v9; // eax
  unsigned int v10; // ebp
  unsigned int v11; // ecx
  unsigned int v12; // edx
  int v13; // ebp
  unsigned int v14; // edx
  struct QTask_s *v15; // eax

  ptParent_low = SLOBYTE(ptQTask[15].ptParent);
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][ExplodeObject_eQTaskType].pfHandler)(ptQTask);
  if ( LOBYTE(ptQTask[11].tQTaskChildren.ptTail) )
  {
    LOBYTE(ptQTask[15].ptParent) = 0;
  }
  else if ( *(_DWORD *)&ptQTask[15].eQTaskType && ptQTask[16].ptNext->ptNext && ptQTask[16].ptPrev )
  {
    LOBYTE(ptQTask[15].ptParent) = (__int64)Level_RunLevelExpression(
                                              (struct LevelExpression_s *)&ptQTask[15].eQTaskType,
                                              ptQTask);
  }
  if ( LOBYTE(ptQTask[15].ptParent) )
  {
    ptMiddle = ptQTask[15].tQTaskRefList.ptMiddle;
    if ( ptMiddle )
    {
      if ( ptMiddle->pxObject )
        return;
      QReference_Delete(ptMiddle, &QTask_tQTaskRefPool);
      ptQTask[15].tQTaskRefList.ptMiddle = nullptr;
    }
    ptTail = ptQTask[15].tQTaskRefList.ptTail;
    if ( ptTail )
    {
      ptQTask[15].tQTaskRefList.ptTail = (struct QReference_s *)((char *)ptTail - 1);
    }
    else
    {
      v4 = Game_ptGame;
      v5 = Game_ptGame->tRunRandomState.anRandom[0];
      v6 = (v5 >> 7) ^ Game_ptGame->tRunRandomState.anRandom[2] ^ Game_ptGame->tRunRandomState.anRandom[1];
      Game_ptGame->tRunRandomState.anRandom[2] ^= v5 >> 7;
      v4->tRunRandomState.anRandom[1] = v6;
      v7 = v6 + v5;
      v4->tRunRandomState.anRandom[0] = v7;
      v8 = SoundSys_NewSoundFn(ptQTask, (char *)&ptQTask[17].eQTaskType + 16 * (v7 & 3));
      v9 = Game_ptGame;
      v10 = Game_ptGame->tRunRandomState.anRandom[1];
      v11 = (Game_ptGame->tRunRandomState.anRandom[0] >> 7) ^ Game_ptGame->tRunRandomState.anRandom[2];
      v12 = Game_ptGame->tRunRandomState.anRandom[0];
      Game_ptGame->tRunRandomState.anRandom[2] = v11;
      v13 = v11 ^ v10;
      v14 = v13 + v12;
      v9->tRunRandomState.anRandom[0] = v14;
      v9->tRunRandomState.anRandom[1] = v13;
      ptQTask[15].tQTaskRefList.ptTail = (struct QReference_s *)(v14 % 0x96 + 150);
      if ( v8 )
      {
        ptQTask[15].tQTaskRefList.ptMiddle = QTask_NewQTaskRef(v8);
        SoundSys_SetSoundPosition(v8, (struct real64x3_t *)&ptQTask[1]);
      }
    }
  }
  else
  {
    QTask_DeleteQTaskAndQTaskRefSafe(&ptQTask[15].tQTaskRefList.ptMiddle);
    if ( ptParent_low )
    {
      v15 = SoundSys_NewSoundFn(ptQTask, (char *)&ptQTask[19].tQTaskRefList);
      if ( v15 )
        ((void (__cdecl *)(struct QTask_s *, struct QTask_s *))QTask_aatQTaskFinalEvent[SoundSys_eSetPositionQTaskEvent][v15->eQTaskType].pfHandler)(
          v15,
          &ptQTask[1]);
    }
  }
}

// source: j/0/objects/radio.c:233  [anchor-mhash]
void __cdecl Radio_DeleteHandler(struct QTask_s *ptQTask)
{
  QTask_DeleteQTaskAndQTaskRefSafe(&ptQTask[15].tQTaskRefList.ptMiddle);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[15].eQTaskType);
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[2][ExplodeObject_eQTaskType].pfHandler)(ptQTask);
}

// source: j/0/objects/radio.c:259  [size]
void __cdecl Radio_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = Radio_ptParameterList;
}

// source: j/0/objects/radio.c:275  [anchor-mhash]
void __cdecl Radio_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][ExplodeObject_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  LOBYTE(ptQTask[15].ptParent) = 0;
  ptQTask[15].tQTaskRefList.ptTail = nullptr;
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[15].eQTaskType, ptQTask);
}

// source: j/0/objects/radio.c:303  [size]
void __cdecl Radio_RegisterScriptSymbolsHandler(struct QTask_s *ptQTask)
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

  if ( !BYTE1(ptQTask[15].ptParent) )
  {
    v1 = ExplodeObject_eQTaskType + 511 * Level_eRegisterLevelScriptSymbolsEvent;
    BYTE1(ptQTask[15].ptParent) = 1;
    ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[0][v1].pfHandler)(ptQTask);
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.isOn", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      &ptQTask[15].ptParent,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
  }
}

// source: j/0/objects/radio.c:339  [anchor-mhash]
void __cdecl Radio_RemoveScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( BYTE1(ptQTask[15].ptParent) )
  {
    ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Level_eRemoveLevelScriptSymbolsEvent][ExplodeObject_eQTaskType].pfHandler)(ptQTask);
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.isOn", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    BYTE1(ptQTask[15].ptParent) = 0;
  }
}

// source: j/0/objects/radio.c:379  [anchor-strings]
void __cdecl Radio_Open()
{
  unsigned __int16 v0; // si
  int v1; // edi
  unsigned int v2; // ebx
  char *v3; // esi

  v0 = QTask_NewQTaskType("Radio", 800, ExplodeObject_eQTaskType, 0, 0);
  Radio_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, Radio_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, Radio_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, Radio_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Radio_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, Radio_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Level_eRegisterLevelScriptSymbolsEvent, Radio_RegisterScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Level_eRemoveLevelScriptSymbolsEvent, Radio_RemoveScriptSymbolsHandler);
  Radio_ptParameterList = ParameterList_Derive(ExplodeObject_ptParameterList, 6);
  v1 = 0;
  v2 = 716;
  v3 = unk_74C58C;
  do
  {
    sprintf(v3, "Radio sound %d", v1);
    ParameterList_AddParameter(Radio_ptParameterList, v2, Level_eParameterTypeString16, v3, 7u, nullptr);
    v3 += 15;
    ++v1;
    v2 += 16;
  }
  while ( (int)v3 < 7652808 );
  ParameterList_AddParameter(Radio_ptParameterList, 0x30Cu, Level_eParameterTypeString16, "Shutdown sound", 7u, nullptr);
  ParameterList_AddParameter(Radio_ptParameterList, 0x27Cu, Level_eParameterTypeVarString, "On expression", 7u, nullptr);
}

// source: j/0/objects/radio.c:433  [size]
void __cdecl Radio_Close()
{
  int v0; // esi

  if ( Radio_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&Radio_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(Radio_eQTaskType);
}
