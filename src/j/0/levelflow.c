/* j/0/levelflow.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/levelflow.c:82  [anchor-mhash]
struct Result_s *__cdecl LevelFlow_SetTimeOfDay(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int ptArgLista; };
    struct { char igi2_o1[8]; struct Result_s Rs; };
    char igi2_extent[32];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( LevelFlow_ptLevelFlow && ptArgList->nArguments > 0 )
  {
    igi2_frame.ptArgLista = Flow_ptFlow->nFrequency;
    LevelFlow_ptLevelFlow->nTimeOfDayTick = (__int64)(Script_EvalArgFloat(ptArgList, 0) * ((double)igi2_frame.ptArgLista * 3600.0));
  }
  igi2_frame.Rs.nResult = 0;
  igi2_frame.Rs.vResult = 0.0;
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/levelflow.c:99  [size]
void __cdecl LevelFlow_GetSerializeParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = LevelFlow_ptSerializeParameterList;
}

// source: j/0/levelflow.c:117  [anchor-mhash]
struct Result_s *__cdecl LevelFlow_GetBreakCutSceneKeyCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+Ch] [ebp-18h] BYREF

  Rs.zResult = (char *)&g_zInitialValue;
  Rs.nResult = Keyboard_tKeyboard.anCurrentKey[1] & 0x80;
  Rs.vResult = (double)Rs.nResult;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/levelflow.c:130  [anchor-mhash]
struct Result_s *__cdecl LevelFlow_LevelFailedCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct Result_s *result; // eax
  double v4[3]; // [esp+Ch] [ebp-18h] BYREF

  LODWORD(v4[2]) = &g_zInitialValue;
  if ( LevelFlow_ptLevelFlow )
  {
    LODWORD(v4[0]) = LevelFlow_ptLevelFlow->isFailed;
    result = retstr;
    v4[1] = (double)SLODWORD(v4[0]);
  }
  else
  {
    LODWORD(v4[0]) = 0;
    v4[1] = 0.0;
    result = retstr;
  }
  qmemcpy(retstr, v4, sizeof(struct Result_s));
  return result;
}

// source: j/0/levelflow.c:145  [size~]
struct Result_s *__cdecl LevelFlow_IsCountryUSACB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  _DWORD v4[6]; // [esp+8h] [ebp-18h] BYREF

  v4[0] = 0;
  v4[2] = 0;
  v4[3] = 0;
  v4[4] = &g_zInitialValue;
  qmemcpy(retstr, v4, sizeof(struct Result_s));
  return retstr;
}

void __cdecl sub_52CA90(struct LevelFlow_s *a1)
{
  LevelFlow_ptLevelFlow = a1;
  Game_RefreshAfterLevelLoad();
  a1->tLevelExpressionComplete.zExpression = nullptr;
  a1->tLevelExpressionComplete.zCompiledExpression = nullptr;
  a1->tLevelExpressionComplete.ptExpression = nullptr;
  a1->tLevelExpressionComplete.nExpressionReference = 0;
  a1->tLevelExpressionFailed.zExpression = nullptr;
  a1->tLevelExpressionFailed.zCompiledExpression = nullptr;
  a1->tLevelExpressionFailed.ptExpression = nullptr;
  a1->tLevelExpressionFailed.nExpressionReference = 0;
  a1->tPos.vX = 0.0;
  a1->tPos.vY = 0.0;
  a1->tPos.vZ = 0.0;
  a1->tOrientation.tX.vY = 0.0;
  a1->tOrientation.tX.vZ = 0.0;
  a1->tOrientation.tY.vX = 0.0;
  a1->tOrientation.tY.vZ = 0.0;
  a1->tOrientation.tZ.vX = 0.0;
  a1->tOrientation.tZ.vY = 0.0;
  a1->tOrientation.nOps = 0;
  a1->isInterfaceTimer = 0;
  a1->vInterfaceCountDownTimer = 0.0;
  a1->isSymbolsCreated = 0;
  a1->isComplete = 0;
  a1->isFailed = 0;
  a1->nTick = 0;
  a1->nTimeOfDayTick = 0;
  a1->isLastFailed = 0;
  a1->tOrientation.tX.vX = 1.0;
  a1->tOrientation.tY.vY = 1.0;
  a1->tOrientation.tZ.vZ = 1.0;
  if ( 2752 * Config_tConfig.iActiveProfile == -7392072 )
    a1->eDifficultySetting = 1;
  else
    a1->eDifficultySetting = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eDifficultyLevel;
}

// source: j/0/levelflow.c:240  [anchor-strings]
void __cdecl LevelFlow_RegisterScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( !LOBYTE(ptQTask[3].tQTaskChildren.ptMiddle) )
  {
    LOBYTE(ptQTask[3].tQTaskChildren.ptMiddle) = 1;
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.isComplete", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      &ptQTask[2].tQTaskRefList.ptMiddle,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.isFailed", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      (char *)&ptQTask[2].tQTaskRefList.ptMiddle + 1,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.nTick", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int,
      &ptQTask[2].eQTaskType,
      4,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.nTimeOfDayTick", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int,
      &ptQTask[2].ptParent,
      4,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.eDifficulty", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int,
      &ptQTask[2].tQTaskRefList.ptTail,
      4,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    Symbol_Register(
      "Key0.isPressed",
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      &LevelFlow_isFixmeKey0,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    Symbol_Register(
      "Key1.isPressed",
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      &LevelFlow_isFixmeKey1,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    Symbol_Register(
      "Key2.isPressed",
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      &LevelFlow_isFixmeKey2,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    Symbol_Register(
      "Key3.isPressed",
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      &LevelFlow_isFixmeKey3,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    Symbol_Register(
      "Key4.isPressed",
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      &LevelFlow_isFixmeKey4,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    Symbol_Register(
      "Key5.isPressed",
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      &LevelFlow_isFixmeKey5,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    Symbol_Register(
      "Key6.isPressed",
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      &LevelFlow_isFixmeKey6,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    Symbol_Register(
      "Key7.isPressed",
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      &LevelFlow_isFixmeKey7,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    Symbol_Register(
      "Key8.isPressed",
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      &LevelFlow_isFixmeKey8,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    Symbol_Register(
      "Key9.isPressed",
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      &LevelFlow_isFixmeKey9,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
  }
}

// source: j/0/levelflow.c:293  [anchor-strings]
void __cdecl LevelFlow_RemoveScriptSymbolsHandler(struct QTask_s *ptQTask)
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
  LOBYTE(ptQTask[3].tQTaskChildren.ptMiddle) = 0;
  sprintf(igi2_frame.zTemp, "%s.isComplete", igi2_frame.zName);
  Symbol_Remove(igi2_frame.zTemp);
  sprintf(igi2_frame.zTemp, "%s.isFailed", igi2_frame.zName);
  Symbol_Remove(igi2_frame.zTemp);
  sprintf(igi2_frame.zTemp, "%s.nTimeOfDayTick", igi2_frame.zName);
  Symbol_Remove(igi2_frame.zTemp);
  sprintf(igi2_frame.zTemp, "%s.nTick", igi2_frame.zName);
  Symbol_Remove(igi2_frame.zTemp);
  sprintf(igi2_frame.zTemp, "%s.eDifficulty", igi2_frame.zName);
  Symbol_Remove(igi2_frame.zTemp);
  Symbol_Remove("Key0.isPressed");
  Symbol_Remove("Key1.isPressed");
  Symbol_Remove("Key2.isPressed");
  Symbol_Remove("Key3.isPressed");
  Symbol_Remove("Key4.isPressed");
  Symbol_Remove("Key5.isPressed");
  Symbol_Remove("Key6.isPressed");
  Symbol_Remove("Key7.isPressed");
  Symbol_Remove("Key8.isPressed");
  Symbol_Remove("Key9.isPressed");
  LOBYTE(ptQTask[3].tQTaskChildren.ptMiddle) = 0;
}

void __cdecl sub_52CED0(struct QTask_s *a1)
{
  int v1; // ecx
  struct QReference_s *v2; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax

  LevelFlow_ptLevelFlow = nullptr;
  Game_RefreshAfterLevelDelete();
  v1 = 0;
  while ( 1 )
  {
    v2 = Level_atLevelQTaskID[v1];
    if ( v2 )
    {
      if ( v2->pxObject == a1 )
        break;
    }
    if ( ++v1 >= 4096 )
      goto LABEL_9;
  }
  if ( v1 >= 0 )
  {
    pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Level_eRemoveLevelScriptSymbolsEvent][a1->eQTaskType].pfHandler;
    if ( pfHandler )
      pfHandler(a1);
  }
LABEL_9:
  Level_DeinitLevelExpression((struct LevelExpression_s *)&a1[3].tQTaskChildren.ptTail);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&a1[5].tQTaskChildren.ptTail);
}

// source: j/0/levelflow.c:396  [size]
void __cdecl LevelFlow_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = LevelFlow_ptParameterList;
}

// source: j/0/levelflow.c:412  [anchor-caller]
void __cdecl LevelFlow_RunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // ecx
  int v2; // edx
  struct QTask_s *v3; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v5; // edx
  char v6; // al
  char v7; // al
  struct QTask_s *ptParent; // edx

  if ( Level_isDynamicQTaskActive || !Level_isDynamicQTaskPaused )
  {
    ptHead = ptQTask->tQTaskChildren.ptHead;
    LOBYTE(ptQTask[7].tQTaskChildren.ptTail) = BYTE1(ptQTask[2].tQTaskRefList.ptMiddle);
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
    if ( ptQTask[3].tQTaskChildren.ptTail )
    {
      if ( ptQTask[3].tQTaskRefList.ptHead->ptNext )
      {
        if ( ptQTask[3].tQTaskRefList.ptMiddle )
        {
          v6 = (__int64)Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[3].tQTaskChildren.ptTail, ptQTask);
          LOBYTE(ptQTask[2].tQTaskRefList.ptMiddle) = v6;
          if ( v6 )
          {
            Game_ptGame->eGameStatus = GAME_GAMESTATUS_COMPLETED;
            Game_CreateMissionScoreScreen();
          }
        }
      }
    }
    if ( ptQTask[5].tQTaskChildren.ptTail )
    {
      if ( ptQTask[5].tQTaskRefList.ptHead->ptNext )
      {
        if ( ptQTask[5].tQTaskRefList.ptMiddle )
        {
          v7 = (__int64)Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[5].tQTaskChildren.ptTail, ptQTask);
          BYTE1(ptQTask[2].tQTaskRefList.ptMiddle) = v7;
          if ( v7 )
            Game_ptGame->eGameStatus = GAME_GAMESTATUS_FAILED;
        }
      }
    }
    if ( BYTE1(ptQTask[2].tQTaskRefList.ptMiddle) )
      LOBYTE(ptQTask[2].tQTaskRefList.ptMiddle) = 0;
    ptParent = ptQTask[2].ptParent;
    ++*(_DWORD *)&ptQTask[2].eQTaskType;
    ptQTask[2].ptParent = (struct QTask_s *)((char *)&ptParent->ptNext + 1);
    LevelFlow_isFixmeKey0 = Keyboard_tKeyboard.anCurrentKey[11] & 0x80;
    LevelFlow_isFixmeKey1 = Keyboard_tKeyboard.anCurrentKey[2] & 0x80;
    LevelFlow_isFixmeKey2 = Keyboard_tKeyboard.anCurrentKey[3] & 0x80;
    LevelFlow_isFixmeKey3 = Keyboard_tKeyboard.anCurrentKey[4] & 0x80;
    LevelFlow_isFixmeKey4 = Keyboard_tKeyboard.anCurrentKey[5] & 0x80;
    LevelFlow_isFixmeKey5 = Keyboard_tKeyboard.anCurrentKey[6] & 0x80;
    LevelFlow_isFixmeKey6 = Keyboard_tKeyboard.anCurrentKey[7] & 0x80;
    LevelFlow_isFixmeKey7 = Keyboard_tKeyboard.anCurrentKey[8] & 0x80;
    LevelFlow_isFixmeKey8 = Keyboard_tKeyboard.anCurrentKey[9] & 0x80;
    LevelFlow_isFixmeKey9 = Keyboard_tKeyboard.anCurrentKey[10] & 0x80;
  }
}

// source: j/0/levelflow.c:479  [size]
void __cdecl LevelFlow_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[3].tQTaskChildren.ptTail, ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[5].tQTaskChildren.ptTail, ptQTask);
}

// source: j/0/levelflow.c:523  [size]
unsigned __int16 __cdecl LevelFlow_GetQTaskType()
{
  return LevelFlow_eQTaskType;
}

// source: j/0/levelflow.c:538  [anchor-hash]
enum bool __cdecl LevelFlow_LevelComplete()
{
  return LevelFlow_ptLevelFlow->isComplete;
}

// source: j/0/levelflow.c:553  [anchor-hash]
enum bool __cdecl LevelFlow_LevelFailed()
{
  if ( LevelFlow_ptLevelFlow )
    return LevelFlow_ptLevelFlow->isFailed;
  else
    return false;
}

// source: j/0/levelflow.c:575  [anchor-mhash]
float __cdecl LevelFlow_GetTime()
{
  return (double)LevelFlow_ptLevelFlow->nTimeOfDayTick / ((double)Flow_ptFlow->nFrequency * 3600.0)
       + LevelFlow_ptLevelFlow->vStartTime;
}

// source: j/0/levelflow.c:627  [anchor-hash]
int __cdecl LevelFlow_GetInterfaceCountDownTimeTicks()
{
  int v0; // eax

  v0 = -LevelFlow_ptLevelFlow->nTick - (__int64)(LevelFlow_ptLevelFlow->vInterfaceCountDownTimer * -30.0);
  return v0 <= 0 ? 0 : v0;
}

// source: j/0/levelflow.c:683  [anchor-hash]
void __cdecl LevelFlow_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  struct ParameterList_s *v2; // eax
  int v3; // edx

  LevelFlow_ptLODVirModel = MTP_GetLODVirModel("306_01_1");
  v0 = QTask_NewQTaskType("LevelFlow", 304, EditorRigidObj_eQTaskType, 0, 0);
  LevelFlow_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, (void (__cdecl *)(struct QTask_s *, void *))sub_52CA90);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, LevelFlow_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, sub_52CED0);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))LevelFlow_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, LevelFlow_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eRegisterLevelScriptSymbolsEvent,
    LevelFlow_RegisterScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Level_eRemoveLevelScriptSymbolsEvent, LevelFlow_RemoveScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 8, nullptr);
  v1 = (struct ParameterList_s *)Mem_AllocFn(152, 4);
  v1->nParameters = 0;
  v1->nMaxParameters = 7;
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  LevelFlow_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0x28u, Level_eParameterTypeObjectPos, "Position", 7u, nullptr);
  ParameterList_AddParameter(LevelFlow_ptParameterList, 0x40u, Level_eParameterTypeReal32x9, "Orientation", 7u, nullptr);
  ParameterList_AddParameter(
    LevelFlow_ptParameterList,
    0x78u,
    Level_eParameterTypeReal32,
    "Start time",
    7u,
    &unk_6B09F8);
  ParameterList_AddParameter(LevelFlow_ptParameterList, 0x88u, Level_eParameterTypeVarString, "Complete", 7u, nullptr);
  ParameterList_AddParameter(LevelFlow_ptParameterList, 0xD8u, Level_eParameterTypeVarString, "Failed", 7u, nullptr);
  ParameterList_AddParameter(
    LevelFlow_ptParameterList,
    0x7Cu,
    Level_eParameterTypebool8,
    &stru_68C1E0.zFilename[240],
    7u,
    nullptr);
  ParameterList_AddParameter(
    LevelFlow_ptParameterList,
    0x80u,
    Level_eParameterTypeReal32,
    &stru_68C1E0.zFilename[220],
    7u,
    nullptr);
  Symbol_Register(
    &stru_68C1E0.zFilename[200],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)LevelFlow_eQTaskType,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &stru_68C1E0.zFilename[168],
    LevelFlow_GetBreakCutSceneKeyCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &stru_68C1E0.zFilename[144],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))LevelFlow_LevelFailedCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &stru_68C1E0.zFilename[120],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))LevelFlow_IsCountryUSACB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &stru_68C1E0.zFilename[96],
    LevelFlow_SetTimeOfDay,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  QTask_LinkQTaskEventHandlerFn(
    LevelFlow_eQTaskType,
    Serialize_eGetSerializeParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))LevelFlow_GetSerializeParameterListHandler);
  v2 = (struct ParameterList_s *)Mem_AllocFn(52, 4);
  v3 = Level_eParameterTypeInt32;
  v2->ptParameterListItem = (struct ParameterListItem_s *)&v2[1];
  v2->nParameters = 0;
  v2->nMaxParameters = 2;
  LevelFlow_ptSerializeParameterList = v2;
  ParameterList_AddParameter(v2, 0x74u, v3, &stru_68C1E0.zFilename[88], 7u, nullptr);
  ParameterList_AddParameter(
    LevelFlow_ptSerializeParameterList,
    0x70u,
    Level_eParameterTypeInt32,
    &stru_68C1E0.zFilename[72],
    7u,
    nullptr);
}

// source: j/0/levelflow.c:743  [size]
void __cdecl LevelFlow_Close()
{
  int v0; // esi
  int v1; // esi

  if ( LevelFlow_ptSerializeParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&LevelFlow_ptSerializeParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  if ( LevelFlow_ptParameterList )
  {
    v1 = *(_DWORD *)((unsigned int)&LevelFlow_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
  QTask_DeleteQTaskType(LevelFlow_eQTaskType);
}
