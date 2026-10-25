/* j/0/menusystem/menustatsscreen.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/menusystem/menustatsscreen.c:73  [anchor-mhash]
struct Result_s *__cdecl MenuStatsScreen_SetActiveMissionID(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      ptArgList = nullptr;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
      v4 = ptArgList;
    }
    else
    {
      v4 = (struct ArgList_s *)Expression_EvalInt(*ptArgList->aptExpression);
    }
    MenuStatsScreen_nActiveMissionID = (int)v4;
    MenuStatsScreen_isActiveMissionIDChanged = true;
  }
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/menusystem/menustatsscreen.c:91  [size]
struct Result_s *__cdecl MenuStatsScreen_GetActiveMissionID(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  Rs.nResult = MenuStatsScreen_nActiveMissionID;
  Rs.vResult = (double)MenuStatsScreen_nActiveMissionID;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/menusystem/menustatsscreen.c:104  [size]
void __cdecl MenuStatsScreen_RegisterMissionEntry(
        struct HumanMissionScoreData_s *ptHumanMissionScoreData,
        void *pxContext)
{
  struct Node_s *ptHead; // esi
  struct Node_s *ptPrev; // ecx
  char *LocalizedStringForLanguage; // eax

  ptHead = Mission_tMissionList.ptHead;
  if ( Mission_tMissionList.ptHead->ptNext && Mission_tMissionList.ptHead )
  {
    while ( 1 )
    {
      ptPrev = ptHead[1].ptPrev;
      if ( ptHead[1].ptNext == (struct Node_s *)ptHumanMissionScoreData->iMissionID )
        break;
      ptHead = ptHead->ptNext;
      if ( !ptHead->ptNext || !ptHead )
        return;
    }
    if ( !MenuStatsScreen_nActiveMissionID )
    {
      MenuStatsScreen_nActiveMissionID = (int)ptHead[1].ptNext;
      MenuStatsScreen_isActiveMissionIDChanged = true;
    }
    LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                   (char *)&ptPrev[2],
                                   Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                   true);
    ListBox_AddItem(LocalizedStringForLanguage, (int)ptHead[1].ptNext);
  }
}

// source: j/0/menusystem/menustatsscreen.c:137  [anchor-mhash]
struct Result_s *__cdecl MenuStatsScreen_FillListBox(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { _DWORD v6[2]; };
    struct { char igi2_o1[8]; struct Result_s Rs; };
    char igi2_extent[32];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QHashTable_s *ptMissionStatsHashTable; // eax
  bool v4; // zf

  ptMissionStatsHashTable = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].ptMissionStatsHashTable;
  igi2_frame.v6[0] = MenuStatsScreen_RegisterMissionEntry;
  igi2_frame.v6[1] = 0;
  v4 = ptMissionStatsHashTable->tPrivate.nEntries == 0;
  MenuStatsScreen_nActiveMissionID = 0;
  MenuStatsScreen_isActiveMissionIDChanged = false;
  if ( !v4 )
    ptMissionStatsHashTable->tPrivate.pfMap(
      ptMissionStatsHashTable,
      (void (__cdecl *)(struct QHashTable_s *, void *, void *, void *))Config_EnumerateMissionStatsCallback,
      igi2_frame.v6);
  igi2_frame.Rs.nResult = 0;
  igi2_frame.Rs.vResult = 0.0;
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/menusystem/menustatsscreen.c:153  [anchor-hash]
void __cdecl MenuStatsScreen_DeleteMissionScoreScreen(struct MenuStatsScreen_s *ptMenuStatsScreen)
{
  struct QReference_s *ptMissionScoreScreen; // eax
  struct QTask_s *pxObject; // eax
  struct QReference_s *v3; // eax

  ptMissionScoreScreen = ptMenuStatsScreen->ptMissionScoreScreen;
  if ( ptMissionScoreScreen )
  {
    pxObject = (struct QTask_s *)ptMissionScoreScreen->pxObject;
    if ( pxObject )
      QTask_Delete(pxObject);
  }
  v3 = ptMenuStatsScreen->ptMissionScoreScreen;
  if ( v3 )
  {
    QReference_Delete(v3, &QTask_tQTaskRefPool);
    ptMenuStatsScreen->ptMissionScoreScreen = nullptr;
  }
}

// source: j/0/menusystem/menustatsscreen.c:171  [anchor-strings]
void __cdecl MenuStatsScreen_CreateMissionScoreScreen(struct MenuStatsScreen_s *ptMenuStatsScreen)
{
  struct QReference_s *ptMissionScoreScreen; // eax
  int v2; // ebx
  struct QTask_s *pxObject; // eax
  struct QReference_s *v4; // eax
  struct QHashTable_s *ptMissionStatsHashTable; // esi
  int v6; // eax
  struct HumanMissionScoreData_s *v7; // esi
  struct MissionScoreSettings_s *MissionScoreSettings; // eax
  struct QTask_s *v9; // eax

  ptMissionScoreScreen = ptMenuStatsScreen->ptMissionScoreScreen;
  v2 = MenuStatsScreen_nActiveMissionID;
  if ( ptMissionScoreScreen )
  {
    pxObject = (struct QTask_s *)ptMissionScoreScreen->pxObject;
    if ( pxObject )
      QTask_Delete(pxObject);
  }
  v4 = ptMenuStatsScreen->ptMissionScoreScreen;
  if ( v4 )
  {
    QReference_Delete(v4, &QTask_tQTaskRefPool);
    ptMenuStatsScreen->ptMissionScoreScreen = nullptr;
  }
  sprintf(byte_70CB00, &g_zFileName.atPictureResources[22].zResourceFilename[32], v2);
  ptMissionStatsHashTable = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].ptMissionStatsHashTable;
  v6 = ptMissionStatsHashTable->tPrivate.pfHashFunction(ptMissionStatsHashTable->tPrivate.nHashTableSize, byte_70CB00);
  v7 = (struct HumanMissionScoreData_s *)((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))ptMissionStatsHashTable->tPrivate.pfFindElement)(ptMissionStatsHashTable, v6, (const void *)(byte_70CB00));
  MissionScoreSettings = Config_GetMissionScoreSettings(v2);
  if ( v7 )
  {
    if ( MissionScoreSettings )
    {
      v9 = MissionScoreScreen_New(
             nullptr,
             v7,
             MissionScoreSettings,
             0xFu,
             ptMenuStatsScreen->tMenuWindow.nXPos,
             ptMenuStatsScreen->tMenuWindow.nYPos,
             ptMenuStatsScreen->tMenuWindow.nWidth,
             ptMenuStatsScreen->tMenuWindow.nHeight,
             "LOCAL:common/fonts/font3.fnt",
             ptMenuStatsScreen->zFont);
      ptMenuStatsScreen->ptMissionScoreScreen = QTask_NewQTaskRef(v9);
    }
  }
}

// source: j/0/menusystem/menustatsscreen.c:212  [anchor-strings]
void __cdecl MenuStatsScreen_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][MenuWindow_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  ptQTask[1].tQTaskChildren.ptHead = (struct QTask_s *)100;
  ptQTask[1].tQTaskChildren.ptMiddle = (struct QTask_s *)100;
  ptQTask[1].tQTaskRefList.ptTail = (struct QReference_s *)1;
  ptQTask[1].ptParent = (struct QTask_s *)1;
  ptQTask[3].tQTaskChildren.ptHead = nullptr;
  strcpy((char *)&ptQTask[2].tQTaskChildren.ptTail, "LOCAL:common/fonts/font4.fnt");
}

// source: j/0/menusystem/menustatsscreen.c:236  [anchor-mhash]
void __cdecl MenuStatsScreen_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // eax
  struct QTask_s *v2; // eax
  struct QTask_s *v3; // eax

  ptHead = ptQTask[3].tQTaskChildren.ptHead;
  if ( ptHead )
  {
    v2 = ptHead->tQTaskChildren.ptHead;
    if ( v2 )
      QTask_Delete(v2);
  }
  v3 = ptQTask[3].tQTaskChildren.ptHead;
  if ( v3 )
  {
    QReference_Delete((struct QReference_s *)v3, &QTask_tQTaskRefPool);
    ptQTask[3].tQTaskChildren.ptHead = nullptr;
  }
}

// source: j/0/menusystem/menustatsscreen.c:252  [size]
void __cdecl MenuStatsScreen_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ((void (__cdecl *)())QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][MenuWindow_eQTaskType].pfHandler)(ptQTask, pxContext);
}

// source: j/0/menusystem/menustatsscreen.c:272  [anchor-caller]
void __cdecl MenuStatsScreen_RunHandler(struct QTask_s *ptQTask)
{
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][MenuWindow_eQTaskType].pfHandler)(ptQTask);
  if ( MenuStatsScreen_isActiveMissionIDChanged )
  {
    MenuStatsScreen_isActiveMissionIDChanged = false;
    MenuStatsScreen_CreateMissionScoreScreen((struct MenuStatsScreen_s *)ptQTask);
  }
}

// source: j/0/menusystem/menustatsscreen.c:293  [anchor-mhash]
void __cdecl MenuStatsScreen_DrawHandler(struct QTask_s *ptQTask)
{
  double v2; // st7
  struct QTask_s *ptHead; // eax
  struct QTask_s *v4; // eax
  struct QTask_s *v5; // eax
  int v6; // edx
  struct QTask_s *v7; // ecx
  int eQTaskType; // ecx
  float ptQTaska = *(float *)&ptQTask; // [esp+8h] [ebp+4h] ARGSLOT

  v2 = (double)(*(_DWORD *)(*(_DWORD *)&ptQTask[1].eQTaskType + 356) - 8) * 0.125;
  if ( v2 <= 0.0 )
  {
    ptQTaska = 0.0;
  }
  else
  {
    ptQTaska = v2;
    if ( v2 >= 0.9900000095367432 )
    {
      ptHead = ptQTask[3].tQTaskChildren.ptHead;
      if ( ptHead )
      {
        v4 = ptHead->tQTaskChildren.ptHead;
        if ( v4 )
          ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Screen_eDrawQTaskEvent][v4->eQTaskType].pfHandler)(v4);
      }
    }
  }
  v5 = ptQTask->tQTaskChildren.ptHead;
  if ( v5->ptNext && v5 )
  {
    v6 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( v5->ptNext )
        v7 = v5->ptNext->ptNext != nullptr ? v5->ptNext : nullptr;
      else
        v7 = nullptr;
      QTask_atProtectedQTaskStack[v6].ptQTask = v7;
      eQTaskType = v5->eQTaskType;
      QTask_nProtectedQTaskStackOffset = v6 + 1;
      ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Screen_eDrawQTaskEvent][eQTaskType].pfHandler)(v5);
      v5 = (struct QTask_s *)dword_849C7DC[QTask_nProtectedQTaskStackOffset];
      v6 = --QTask_nProtectedQTaskStackOffset;
    }
    while ( v5 );
  }
  MenuWindow_DrawBorder((struct MenuWindow_t *)ptQTask, 0.5, ptQTaska, 0);
}

// source: j/0/menusystem/menustatsscreen.c:320  [size]
void __cdecl MenuStatsScreen_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = MenuStatsScreen_ptParameterList;
}

// source: j/0/menusystem/menustatsscreen.c:336  [anchor-mhash]
void __cdecl MenuStatsScreen_InitDataHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // eax
  struct QTask_s *v2; // eax
  struct QTask_s *v3; // eax
  struct QTask_s *v4; // ecx
  int v5; // edx
  struct QTask_s *v6; // eax
  int v7; // esi
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v9; // edx

  ptHead = ptQTask[3].tQTaskChildren.ptHead;
  if ( ptHead )
  {
    v2 = ptHead->tQTaskChildren.ptHead;
    if ( v2 )
      QTask_Delete(v2);
  }
  v3 = ptQTask[3].tQTaskChildren.ptHead;
  if ( v3 )
  {
    QReference_Delete((struct QReference_s *)v3, &QTask_tQTaskRefPool);
    ptQTask[3].tQTaskChildren.ptHead = nullptr;
  }
  v4 = ptQTask->tQTaskChildren.ptHead;
  if ( v4->ptNext && v4 )
  {
    v5 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( v4->ptNext )
        v6 = v4->ptNext->ptNext != nullptr ? v4->ptNext : nullptr;
      else
        v6 = nullptr;
      v7 = MenuWindow_eInitDataEvent;
      QTask_atProtectedQTaskStack[v5].ptQTask = v6;
      pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[v7][v4->eQTaskType].pfHandler;
      v9 = v5 + 1;
      QTask_nProtectedQTaskStackOffset = v9;
      if ( pfHandler )
      {
        pfHandler(v4);
        v9 = QTask_nProtectedQTaskStackOffset;
      }
      v4 = (struct QTask_s *)dword_849C7DC[v9];
      v5 = v9 - 1;
      QTask_nProtectedQTaskStackOffset = v5;
    }
    while ( v4 );
  }
}

// source: j/0/menusystem/menustatsscreen.c:355  [size]
unsigned __int16 __cdecl MenuStatsScreen_GetQTaskType()
{
  return MenuStatsScreen_eQTaskType;
}

// source: j/0/menusystem/menustatsscreen.c:370  [anchor-hash]
void __cdecl MenuStatsScreen_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // edx

  v0 = QTask_NewQTaskType("MenuStatsScreen", 132, MenuWindow_eQTaskType, 0, 0);
  MenuStatsScreen_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, MenuStatsScreen_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Screen_eDrawQTaskEvent, MenuStatsScreen_DrawHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, MenuStatsScreen_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, MenuStatsScreen_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))MenuStatsScreen_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eUpdateInternalDataQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))MenuStatsScreen_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, MenuWindow_eInitDataEvent, MenuStatsScreen_InitDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  Symbol_Register(
    "MenuStatsScreen_SetActiveMissionID",
    MenuStatsScreen_SetActiveMissionID,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "MenuStatsScreen_GetActiveMissionID",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))MenuStatsScreen_GetActiveMissionID,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "MenuStatsScreen_FillListBox",
    MenuStatsScreen_FillListBox,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  v1 = (struct ParameterList_s *)Mem_AllocFn(72, 4);
  v2 = Level_eParameterTypeInt32;
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  v1->nParameters = 0;
  v1->nMaxParameters = 3;
  MenuStatsScreen_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0x30u, v2, "Width", 7u, nullptr);
  ParameterList_AddParameter(MenuStatsScreen_ptParameterList, 0x34u, Level_eParameterTypeInt32, "Height", 7u, nullptr);
  ParameterList_AddParameter(MenuStatsScreen_ptParameterList, 0x60u, Level_eParameterTypeString32, "Font", 7u, nullptr);
}

// source: j/0/menusystem/menustatsscreen.c:402  [size]
void __cdecl MenuStatsScreen_Close()
{
  int v0; // esi

  if ( MenuStatsScreen_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&MenuStatsScreen_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(MenuStatsScreen_eQTaskType);
  MenuStatsScreen_eQTaskType = 512;
}
