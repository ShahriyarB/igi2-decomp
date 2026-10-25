/* j/0/menusystem/togglebox.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/menusystem/togglebox.c:92  [anchor-mhash]
void __cdecl ToggleBox_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v2; // eax
  int v3; // edx
  struct QTask_s *ptNext; // eax

  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][MenuWindow_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  *(_DWORD *)&ptQTask[3].eQTaskType = QTask_NewFn(nullptr, MenuWindow_eQTaskType, nullptr);
  v2 = QTask_NewFn(nullptr, MenuWindow_eQTaskType, nullptr);
  v3 = *(_DWORD *)&ptQTask[3].eQTaskType;
  ptQTask[4].ptNext = v2;
  *(_DWORD *)(v3 + 76) = *(_DWORD *)&ptQTask[1].eQTaskType;
  *(_DWORD *)&ptQTask[4].ptNext[1].eQTaskType = *(_DWORD *)&ptQTask[1].eQTaskType;
  ptNext = ptQTask[4].ptNext;
  LOBYTE(ptQTask[2].tQTaskChildren.ptMiddle) = 0;
  ptNext[1].ptParent = nullptr;
  *(_DWORD *)(*(_DWORD *)&ptQTask[3].eQTaskType + 72) = 0;
  ptQTask[4].ptNext[1].tQTaskRefList.ptTail = nullptr;
  *(_DWORD *)(*(_DWORD *)&ptQTask[3].eQTaskType + 68) = 0;
  ptQTask[4].ptPrev = nullptr;
  ptQTask[4].tQTaskChildren.ptHead = nullptr;
  ptQTask[1].tQTaskChildren.ptHead = (struct QTask_s *)50;
  ptQTask[1].tQTaskChildren.ptMiddle = (struct QTask_s *)15;
  ptQTask[4].tQTaskChildren.ptMiddle = (struct QTask_s *)1;
  ptQTask[1].tQTaskRefList.ptTail = (struct QReference_s *)1;
  ptQTask[1].ptParent = (struct QTask_s *)1;
  ptQTask[6].tQTaskRefList.ptHead = nullptr;
  ptQTask[6].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[6].tQTaskRefList.ptTail = nullptr;
  ptQTask[8].tQTaskChildren.ptTail = nullptr;
  ptQTask[8].tQTaskRefList.ptHead = nullptr;
  ptQTask[8].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[8].tQTaskRefList.ptTail = nullptr;
  ptQTask[10].tQTaskChildren.ptTail = nullptr;
  ptQTask[10].tQTaskRefList.ptHead = nullptr;
  ptQTask[10].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[10].tQTaskRefList.ptTail = nullptr;
  ptQTask[12].tQTaskChildren.ptTail = nullptr;
  ptQTask[4].tQTaskRefList.ptHead = nullptr;
  ptQTask[4].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[4].tQTaskRefList.ptTail = nullptr;
  ptQTask[6].tQTaskChildren.ptTail = nullptr;
  LOBYTE(ptQTask[4].tQTaskChildren.ptTail) = 0;
  LOBYTE(ptQTask[12].tQTaskRefList.ptHead) = 1;
}

// source: j/0/menusystem/togglebox.c:143  [anchor-mhash]
void __cdecl ToggleBox_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptHead; // eax

  ptPrev = ptQTask[4].ptPrev;
  if ( ptPrev )
    Text_Delete((struct StaticTilemap_s *)ptPrev);
  ptHead = ptQTask[4].tQTaskChildren.ptHead;
  if ( ptHead )
    Text_Delete((struct StaticTilemap_s *)ptHead);
  QTask_Delete(*(struct QTask_s **)&ptQTask[3].eQTaskType);
  QTask_Delete(ptQTask[4].ptNext);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[6].tQTaskRefList);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[8].tQTaskRefList);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[10].tQTaskRefList);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[4].tQTaskRefList);
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Level_eRemoveLevelScriptSymbolsEvent][ptQTask->eQTaskType].pfHandler)(ptQTask);
}

// source: j/0/menusystem/togglebox.c:182  [anchor-strings]
void __cdecl ToggleBox_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QSprite_s *Font; // edi
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptHead; // eax
  char *LocalizedStringForLanguage; // eax
  char *v6; // eax
  struct QTask_s *v7; // eax
  struct QTask_s *v8; // edx

  Font = MenuManager_GetFont(
           *(struct QTask_s **)&ptQTask[1].eQTaskType,
           (char *)&g_zFontName_0.tQTaskChildren.ptMiddle);
  ptPrev = ptQTask[4].ptPrev;
  if ( ptPrev )
    Text_Delete((struct StaticTilemap_s *)ptPrev);
  ptHead = ptQTask[4].tQTaskChildren.ptHead;
  if ( ptHead )
    Text_Delete((struct StaticTilemap_s *)ptHead);
  if ( Font )
  {
    LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                   off_69164C,
                                   Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                   true);
    ptQTask[4].ptPrev = (struct QTask_s *)Text_New(Font, 0.0, 0.0, LocalizedStringForLanguage);
    v6 = Config_GetLocalizedStringForLanguage(
           "No",
           Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
           true);
    v7 = (struct QTask_s *)Text_New(Font, 0.0, 0.0, v6);
    v8 = ptQTask[4].ptPrev;
    ptQTask[4].tQTaskChildren.ptHead = v7;
    v8->ptParent = nullptr;
    ptQTask[4].tQTaskChildren.ptHead->ptParent = nullptr;
  }
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[6].tQTaskRefList, ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[8].tQTaskRefList, ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[10].tQTaskRefList, ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[4].tQTaskRefList, ptQTask);
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][MenuWindow_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
}

// source: j/0/menusystem/togglebox.c:240  [size]
void __cdecl ToggleBox_RunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptNext; // ecx
  struct MenuWindow_t *v2; // ebx
  struct QTask_s *ptHead; // esi
  int v4; // eax
  struct MenuWindow_t *ptOption2; // [esp+10h] [ebp-10h]
  struct QTask_s *nXPos; // [esp+14h] [ebp-Ch]
  struct QTask_s *nYPos; // [esp+18h] [ebp-8h]
  struct QTask_s *nHeight; // [esp+1Ch] [ebp-4h]

  ptNext = ptQTask[4].ptNext;
  v2 = *(struct MenuWindow_t **)&ptQTask[3].eQTaskType;
  ptHead = ptQTask[1].tQTaskChildren.ptHead;
  nXPos = ptQTask[1].ptNext;
  nHeight = ptQTask[1].tQTaskChildren.ptMiddle;
  ptOption2 = (struct MenuWindow_t *)ptNext;
  nYPos = ptQTask[1].ptPrev;
  if ( ptQTask[4].tQTaskRefList.ptHead && ptQTask[4].tQTaskRefList.ptMiddle->ptNext && ptQTask[4].tQTaskRefList.ptTail )
  {
    v4 = Expression_EvalInt((struct QExpression_s *)ptQTask[4].tQTaskRefList.ptTail);
    ptNext = &ptOption2->tQTask;
    LOBYTE(ptQTask[12].tQTaskRefList.ptHead) = v4 != 0;
  }
  v2->nXPos = (int)nXPos;
  v2->nYPos = (int)nYPos;
  v2->nHeight = (int)nHeight;
  v2->nWidth = (int)ptHead >> 1;
  ptNext[1].ptNext = (struct QTask_s *)((char *)nXPos + ((int)ptHead >> 1));
  ptNext[1].ptPrev = nYPos;
  ptNext[1].tQTaskChildren.ptHead = (struct QTask_s *)((char *)ptHead - ((int)ptHead >> 1));
  ptNext[1].tQTaskChildren.ptMiddle = nHeight;
  if ( LOBYTE(ptQTask[12].tQTaskRefList.ptHead) )
  {
    MenuWindow_HitTest(v2, v2->nXPos, v2->nYPos, v2->nWidth, v2->nHeight, nullptr, nullptr);
    MenuWindow_HitTest(
      ptOption2,
      ptOption2->nXPos,
      ptOption2->nYPos,
      ptOption2->nWidth,
      ptOption2->nHeight,
      nullptr,
      nullptr);
    if ( (v2->isClicked || ptQTask[2].tQTaskChildren.ptHead == (struct QTask_s *)-1)
      && !ptQTask[4].tQTaskChildren.ptMiddle )
    {
      SoundSys_PlaySimpleSoundFn((char *)&g_zFileName.aptSelectableItems[22], 0, nullptr);
      ptQTask[4].tQTaskChildren.ptMiddle = (struct QTask_s *)1;
LABEL_14:
      if ( ptQTask[10].tQTaskRefList.ptHead
        && ptQTask[10].tQTaskRefList.ptMiddle->ptNext
        && ptQTask[10].tQTaskRefList.ptTail )
      {
        Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[10].tQTaskRefList, ptQTask);
      }
      goto LABEL_18;
    }
    if ( (ptOption2->isClicked || ptQTask[2].tQTaskChildren.ptHead == (struct QTask_s *)-2)
      && ptQTask[4].tQTaskChildren.ptMiddle )
    {
      SoundSys_PlaySimpleSoundFn((char *)&g_zFileName.aptSelectableItems[22], 0, nullptr);
      ptQTask[4].tQTaskChildren.ptMiddle = nullptr;
      goto LABEL_14;
    }
  }
LABEL_18:
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][MenuWindow_eQTaskType].pfHandler)(ptQTask);
}

// source: j/0/menusystem/togglebox.c:325  [anchor-mhash]
void __cdecl ToggleBox_DrawHandler(struct QTask_s *ptQTask)
{
  struct MenuWindow_t *v2; // edi
  double v3; // st7
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptNext; // ecx
  int ptPrev_high; // eax
  int ptNext_low; // edi
  struct QTask_s *ptMiddle; // ecx
  struct QTask_s *v9; // eax
  int v10; // edx
  int v11; // ebx
  struct QTask_s *v12; // eax
  double v13; // st7
  int v14; // edx
  char v15; // al
  double v16; // st7
  double v17; // st6
  float vX; // [esp+0h] [ebp-48h]
  float vY; // [esp+4h] [ebp-44h]
  float vWidth; // [esp+8h] [ebp-40h]
  float vHeight; // [esp+Ch] [ebp-3Ch]
  float vR; // [esp+10h] [ebp-38h]
  float vG; // [esp+14h] [ebp-34h]
  float vB; // [esp+18h] [ebp-30h]
  float vAlpha; // [esp+24h] [ebp-24h]
  float vFade; // [esp+34h] [ebp-14h]
  char *nY; // [esp+38h] [ebp-10h]
  struct MenuWindow_t *ptActiveOption; // [esp+3Ch] [ebp-Ch]
  float nX0; // [esp+40h] [ebp-8h]
  char *nX1; // [esp+44h] [ebp-4h]
  float ptQTaska = *(float *)&ptQTask; // [esp+4Ch] [ebp+4h] ARGSLOT

  if ( ptQTask[4].tQTaskChildren.ptMiddle )
  {
    v2 = *(struct MenuWindow_t **)&ptQTask[3].eQTaskType;
    ptActiveOption = v2;
  }
  else
  {
    ptActiveOption = (struct MenuWindow_t *)ptQTask[4].ptNext;
    v2 = ptActiveOption;
  }
  v3 = (double)(*(_DWORD *)(*(_DWORD *)&ptQTask[1].eQTaskType + 356) - 8) * 0.125;
  if ( v3 <= 0.0 )
    vFade = 0.0;
  else
    vFade = v3;
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Screen_eDrawQTaskEvent][MenuWindow_eQTaskType].pfHandler)(ptQTask);
  ptQTaska = 1.0;
  if ( !LOBYTE(ptQTask[12].tQTaskRefList.ptHead) )
    ptQTaska = 0.5;
  ptPrev = ptQTask[4].ptPrev;
  if ( ptPrev && ptQTask[4].tQTaskChildren.ptHead )
  {
    ptNext = ptPrev->ptNext;
    nY = (char *)ptQTask[1].ptPrev
       + ((int)ptQTask[1].tQTaskChildren.ptMiddle
        - SHIWORD(ptPrev->ptNext->ptPrev)
        * *((__int16 *)&ptPrev->ptNext->tQTaskChildren.ptHead->tQTaskChildren.ptHead->tQTaskChildren.ptMiddle
          + 18 * LOWORD(ptPrev->ptNext->tQTaskChildren.ptHead->tQTaskRefList.ptHead)
          + 1))
       / 2;
    ptPrev_high = SHIWORD(ptPrev->ptNext->ptPrev);
    ptNext_low = 0;
    if ( ptPrev_high > 0 )
    {
      ptMiddle = ptNext->tQTaskChildren.ptMiddle;
      do
      {
        if ( SLOWORD(ptMiddle->ptNext) > ptNext_low )
          ptNext_low = SLOWORD(ptMiddle->ptNext);
        ptMiddle = (struct QTask_s *)((char *)ptMiddle + 2);
        --ptPrev_high;
      }
      while ( ptPrev_high );
    }
    v9 = ptQTask[4].tQTaskChildren.ptHead->ptNext;
    v10 = SHIWORD(v9->ptPrev);
    v11 = 0;
    if ( v10 > 0 )
    {
      v12 = v9->tQTaskChildren.ptMiddle;
      do
      {
        if ( SLOWORD(v12->ptNext) > v11 )
          v11 = SLOWORD(v12->ptNext);
        v12 = (struct QTask_s *)((char *)v12 + 2);
        --v10;
      }
      while ( v10 );
    }
    v13 = (double)((unsigned int)&ptQTask[1].ptNext[-8]
                 + (int)ptQTask[1].tQTaskChildren.ptHead / 4
                 - ptNext_low / 2
                 + (Display_tActiveMode.nWidth >> 1));
    nX1 = (char *)&ptQTask[1].ptNext[-8]
        + 3 * (int)ptQTask[1].tQTaskChildren.ptHead / 4
        - v11 / 2
        + (Display_tActiveMode.nWidth >> 1);
    v14 = (int)&nY[(Display_tActiveMode.nHeight >> 1) - 240];
    ptQTask[4].ptPrev->tQTaskRefList.ptHead = nullptr;
    ptQTask[4].ptPrev->tQTaskRefList.ptMiddle = nullptr;
    ptQTask[4].ptPrev->tQTaskRefList.ptTail = nullptr;
    *(_DWORD *)&ptQTask[4].ptPrev->eQTaskType |= 0x80000u;
    *(float *)&ptQTask[4].ptPrev->tQTaskChildren.ptTail = vFade;
    *(float *)&ptQTask[4].ptPrev->ptPrev = v13;
    nX0 = (float)v14;
    *(float *)&ptQTask[4].ptPrev->tQTaskChildren.ptHead = nX0;
    Text_Register((struct StaticTilemap_s *)ptQTask[4].ptPrev);
    ptQTask[4].tQTaskChildren.ptHead->tQTaskRefList.ptHead = nullptr;
    ptQTask[4].tQTaskChildren.ptHead->tQTaskRefList.ptMiddle = nullptr;
    ptQTask[4].tQTaskChildren.ptHead->tQTaskRefList.ptTail = nullptr;
    *(_DWORD *)&ptQTask[4].tQTaskChildren.ptHead->eQTaskType |= 0x80000u;
    *(float *)&ptQTask[4].tQTaskChildren.ptHead->tQTaskChildren.ptTail = vFade;
    *(float *)&ptQTask[4].tQTaskChildren.ptHead->ptPrev = (float)(int)nX1;
    *(float *)&ptQTask[4].tQTaskChildren.ptHead->tQTaskChildren.ptHead = nX0;
    Text_Register((struct StaticTilemap_s *)ptQTask[4].tQTaskChildren.ptHead);
    v2 = ptActiveOption;
  }
  v15 = BYTE1(ptQTask[2].ptPrev);
  if ( v15 )
    v16 = 0.8999999761581421;
  else
    v16 = 0.6000000238418579;
  if ( v15 )
    v17 = 0.8999999761581421;
  else
    v17 = 0.4000000059604645;
  vB = ptQTaska * 128.0;
  vG = v16 * ptQTaska * 128.0;
  vR = v17 * ptQTaska * 128.0;
  vHeight = (float)v2->nHeight;
  vWidth = (float)v2->nWidth;
  vY = (float)((Display_tActiveMode.nHeight >> 1) + v2->nYPos - 240);
  vX = (float)((Display_tActiveMode.nWidth >> 1) + v2->nXPos - 320);
  QSprite_RegisterBlankAZ(vX, vY, vWidth, vHeight, vR, vG, vB, vFade, 1.0, 0x80000u, 0);
  vAlpha = ptQTaska * vFade;
  MenuWindow_DrawBorder((struct MenuWindow_t *)ptQTask, 0.5, vAlpha, SBYTE1(ptQTask[2].ptPrev));
}

// source: j/0/menusystem/togglebox.c:398  [size]
void __cdecl ToggleBox_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = ToggleBox_ptParameterList;
}

// source: j/0/menusystem/togglebox.c:414  [size]
void __cdecl ToggleBox_InitDataHandler(struct QTask_s *ptQTask)
{
  char *LocalizedStringForLanguage; // eax
  char *v2; // eax
  struct QTask_s *ptHead; // ecx
  int v4; // edx
  struct QTask_s *v5; // eax
  int v6; // esi
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v8; // edx

  if ( ptQTask[6].tQTaskRefList.ptHead && ptQTask[6].tQTaskRefList.ptMiddle->ptNext && ptQTask[6].tQTaskRefList.ptTail )
    ptQTask[4].tQTaskChildren.ptMiddle = (struct QTask_s *)(Expression_EvalInt((struct QExpression_s *)ptQTask[6].tQTaskRefList.ptTail) != 0);
  LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                 off_69164C,
                                 Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                 true);
  Text_SetString((struct StaticTilemap_s *)ptQTask[4].ptPrev, LocalizedStringForLanguage);
  v2 = Config_GetLocalizedStringForLanguage(
         "No",
         Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
         true);
  Text_SetString((struct StaticTilemap_s *)ptQTask[4].tQTaskChildren.ptHead, v2);
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
      v6 = MenuWindow_eInitDataEvent;
      QTask_atProtectedQTaskStack[v4].ptQTask = v5;
      pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[v6][ptHead->eQTaskType].pfHandler;
      v8 = v4 + 1;
      QTask_nProtectedQTaskStackOffset = v8;
      if ( pfHandler )
      {
        pfHandler(ptHead);
        v8 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v8];
      v4 = v8 - 1;
      QTask_nProtectedQTaskStackOffset = v4;
    }
    while ( ptHead );
  }
}

// source: j/0/menusystem/togglebox.c:442  [anchor-mhash]
void __cdecl ToggleBox_ChangeDataHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // ecx
  int v2; // edx
  struct QTask_s *v3; // eax
  int v4; // esi
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v6; // edx

  if ( ptQTask[8].tQTaskRefList.ptHead && ptQTask[8].tQTaskRefList.ptMiddle->ptNext && ptQTask[8].tQTaskRefList.ptTail )
    Expression_EvalInt((struct QExpression_s *)ptQTask[8].tQTaskRefList.ptTail);
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
      v4 = MenuWindow_eChangeDataEvent;
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

// source: j/0/menusystem/togglebox.c:465  [size]
void __cdecl ToggleBox_RegisterScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( !LOBYTE(ptQTask[4].tQTaskChildren.ptTail) )
  {
    LOBYTE(ptQTask[4].tQTaskChildren.ptTail) = 1;
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.isOn", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int,
      &ptQTask[4].tQTaskChildren.ptMiddle,
      4,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
  }
}

// source: j/0/menusystem/togglebox.c:497  [size]
void __cdecl ToggleBox_RemoveScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( LOBYTE(ptQTask[4].tQTaskChildren.ptTail) )
  {
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.isOn", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    LOBYTE(ptQTask[4].tQTaskChildren.ptTail) = 0;
  }
}

// source: j/0/menusystem/togglebox.c:532  [anchor-hash]
void __cdecl ToggleBox_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // edx

  v0 = QTask_NewQTaskType("ToggleBox", 504, MenuWindow_eQTaskType, 0, 0);
  ToggleBox_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, ToggleBox_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Screen_eDrawQTaskEvent, ToggleBox_DrawHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, ToggleBox_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, ToggleBox_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))ToggleBox_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, ToggleBox_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, MenuWindow_eInitDataEvent, ToggleBox_InitDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, MenuWindow_eChangeDataEvent, ToggleBox_ChangeDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eRegisterLevelScriptSymbolsEvent,
    ToggleBox_RegisterScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Level_eRemoveLevelScriptSymbolsEvent, ToggleBox_RemoveScriptSymbolsHandler);
  v1 = (struct ParameterList_s *)Mem_AllocFn(92, 4);
  v2 = Level_eParameterTypeVarString;
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  v1->nParameters = 0;
  v1->nMaxParameters = 4;
  ToggleBox_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0x104u, v2, "Get Data Script", 7u, nullptr);
  ParameterList_AddParameter(
    ToggleBox_ptParameterList,
    0x154u,
    Level_eParameterTypeVarString,
    "Set Data Script",
    7u,
    nullptr);
  ParameterList_AddParameter(
    ToggleBox_ptParameterList,
    0x1A4u,
    Level_eParameterTypeVarString,
    "Modify Data Script",
    7u,
    nullptr);
  ParameterList_AddParameter(
    ToggleBox_ptParameterList,
    0xB4u,
    Level_eParameterTypeVarString,
    "isEnabled Expression",
    7u,
    nullptr);
}

// source: j/0/menusystem/togglebox.c:572  [size]
void __cdecl ToggleBox_Close()
{
  int v0; // esi

  if ( ToggleBox_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&ToggleBox_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(ToggleBox_eQTaskType);
  ToggleBox_eQTaskType = 512;
}
