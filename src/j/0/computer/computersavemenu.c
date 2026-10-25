/* j/0/computer/computersavemenu.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/computer/computersavemenu.c:195  [size]
int __cdecl ComputerSaveMenu_GetMenuItemIDForSlot(int iSaveSlot)
{
  return iSaveSlot + 10;
}

// source: j/0/computer/computersavemenu.c:208  [anchor-mhash]
void __cdecl ComputerSaveMenu_UploadItemActivateCB(
        struct MenuItem_s *ptMenuItem,
        struct MenuItemActivateContext_s *ptMenuItemActivateContext)
{
  struct QTask_s *v2; // edi

  v2 = ComputerSaveMenu_ptQTask;
  if ( ptMenuItem->isActivated && !ptMenuItem->isActive )
    SoundSys_PlaySimpleSoundDefFn("mapcomp_05", 1u, nullptr);
  if ( ((int)ComputerMenu_ptComputerMenuQTask[1].tQTaskRefList.ptHead & 0x10) != 0
    && ptMenuItemActivateContext->eMenuItem == ptMenuItem->eMenuItem
    && *(float *)&v2[2].tQTaskChildren.ptMiddle > 0.0 )
  {
    SoundSys_PlaySimpleSoundDefFn("mapcomp_01", 1u, nullptr);
    *(_DWORD *)&v2[1].eQTaskType = 2;
  }
  if ( ((int)ComputerMenu_ptComputerMenuQTask[1].tQTaskRefList.ptHead & 0x10) != 0
    && ptMenuItemActivateContext->eMenuItem == ptMenuItem->eMenuItem
    && *(float *)&v2[2].tQTaskChildren.ptMiddle <= 0.0 )
  {
    SoundSys_PlaySimpleSoundDefFn("mapcomp_06", 1u, nullptr);
  }
}

// source: j/0/computer/computersavemenu.c:240  [size]
void __cdecl ComputerSaveMenu_DownloadItemActivateCB(
        struct MenuItem_s *ptMenuItem,
        struct MenuItemActivateContext_s *ptMenuItemActivateContext)
{
  struct QTask_s *v2; // edi

  v2 = ComputerSaveMenu_ptQTask;
  if ( ptMenuItem->isActivated && !ptMenuItem->isActive )
    SoundSys_PlaySimpleSoundDefFn("mapcomp_05", 1u, nullptr);
  if ( ((int)ComputerMenu_ptComputerMenuQTask[1].tQTaskRefList.ptHead & 0x10) != 0
    && ptMenuItemActivateContext->eMenuItem == ptMenuItem->eMenuItem )
  {
    SoundSys_PlaySimpleSoundDefFn("mapcomp_01", 1u, nullptr);
    *(_DWORD *)&v2[1].eQTaskType = 3;
  }
}

// source: j/0/computer/computersavemenu.c:264  [size]
void __cdecl ComputerSaveMenu_CancelItemActivateCB(
        struct MenuItem_s *ptMenuItem,
        struct MenuItemActivateContext_s *ptMenuItemActivateContext)
{
  struct QTask_s *v2; // edi

  v2 = ComputerSaveMenu_ptQTask;
  if ( ptMenuItem->isActivated && !ptMenuItem->isActive )
    SoundSys_PlaySimpleSoundDefFn("mapcomp_05", 1u, nullptr);
  if ( ((int)ComputerMenu_ptComputerMenuQTask[1].tQTaskRefList.ptHead & 0x10) != 0
    && ptMenuItemActivateContext->eMenuItem == ptMenuItem->eMenuItem )
  {
    SoundSys_PlaySimpleSoundDefFn("mapcomp_02", 1u, nullptr);
    *(_DWORD *)&v2[1].eQTaskType = 1;
  }
}

// source: j/0/computer/computersavemenu.c:288  [size]
void __cdecl ComputerSaveMenu_YesItemActivateCB(
        struct MenuItem_s *ptMenuItem,
        struct MenuItemActivateContext_s *ptMenuItemActivateContext)
{
  struct QTask_s *v2; // edi

  v2 = ComputerSaveMenu_ptQTask;
  if ( ptMenuItem->isActivated && !ptMenuItem->isActive )
    SoundSys_PlaySimpleSoundDefFn("mapcomp_05", 1u, nullptr);
  if ( ((int)ComputerMenu_ptComputerMenuQTask[1].tQTaskRefList.ptHead & 0x10) != 0
    && ptMenuItemActivateContext->eMenuItem == ptMenuItem->eMenuItem )
  {
    SoundSys_PlaySimpleSoundDefFn("mapcomp_01", 1u, nullptr);
    *(_DWORD *)&v2[1].eQTaskType = 5;
  }
}

// source: j/0/computer/computersavemenu.c:312  [size]
void __cdecl ComputerSaveMenu_NoItemActivateCB(
        struct MenuItem_s *ptMenuItem,
        struct MenuItemActivateContext_s *ptMenuItemActivateContext)
{
  struct QTask_s *v2; // edi

  v2 = ComputerSaveMenu_ptQTask;
  if ( ptMenuItem->isActivated && !ptMenuItem->isActive )
    SoundSys_PlaySimpleSoundDefFn("mapcomp_05", 1u, nullptr);
  if ( ((int)ComputerMenu_ptComputerMenuQTask[1].tQTaskRefList.ptHead & 0x10) != 0
    && ptMenuItemActivateContext->eMenuItem == ptMenuItem->eMenuItem )
  {
    SoundSys_PlaySimpleSoundDefFn("mapcomp_02", 1u, nullptr);
    *(_DWORD *)&v2[1].eQTaskType = 2;
  }
}

// source: j/0/computer/computersavemenu.c:336  [size]
void __cdecl ComputerSaveMenu_SlotItemActivateCB(
        struct MenuItem_s *ptMenuItem,
        struct MenuItemActivateContext_s *ptMenuItemActivateContext)
{
  struct QTask_s *v2; // edi
  _DWORD *pxObject; // ecx
  int v4; // eax
  bool v5; // zf
  struct QReference_s *v6; // eax

  v2 = ComputerSaveMenu_ptQTask;
  if ( ptMenuItem->isActivated && !ptMenuItem->isActive )
    SoundSys_PlaySimpleSoundDefFn("mapcomp_05", 1u, nullptr);
  if ( ((int)ComputerMenu_ptComputerMenuQTask[1].tQTaskRefList.ptHead & 0x10) != 0
    && ptMenuItemActivateContext->eMenuItem == ptMenuItem->eMenuItem )
  {
    if ( HumanPlayer_ptQTask )
      QTask_GetFirstChildOfType(HumanPlayer_ptQTask, HumanPlayerInput_eQTaskType)[23].tQTaskChildren.ptTail = (struct QTask_s *)1;
    if ( v2[1].ptParent == (struct QTask_s *)2 )
    {
      SoundSys_PlaySimpleSoundDefFn("mapcomp_01", 1u, nullptr);
      v2[2].tQTaskChildren.ptHead = (struct QTask_s *)ptMenuItem[1].eMenuItem;
      *(_DWORD *)&v2[1].eQTaskType = (LODWORD(ptMenuItem[4].tClientRect.vHalfWidth) != 0) + 4;
    }
    if ( v2[1].ptParent == (struct QTask_s *)3 )
    {
      if ( !LODWORD(ptMenuItem[4].tClientRect.vHalfWidth) )
      {
        SoundSys_PlaySimpleSoundDefFn("mapcomp_01", 1u, nullptr);
        if ( Level_atLevelQTaskID[0] )
          pxObject = Level_atLevelQTaskID[0]->pxObject;
        else
          pxObject = nullptr;
        v4 = ptMenuItem[1].eMenuItem + 1;
        v5 = Game_eGameMode == GAME_GAMEMODE_SINGLEPLAYER;
        pxObject[852] = v4;
        pxObject[854] = !v5 ? 0 : v4;
        v6 = Level_atLevelQTaskID[0];
        if ( Level_atLevelQTaskID[0] )
          v6 = (struct QReference_s *)Level_atLevelQTaskID[0]->pxObject;
        HIBYTE(v6[268].pxObject) = 1;
      }
      if ( v2[1].ptParent == (struct QTask_s *)3 )
      {
        if ( LODWORD(ptMenuItem[4].tClientRect.vHalfWidth) )
          SoundSys_PlaySimpleSoundDefFn("mapcomp_06", 1u, nullptr);
      }
    }
  }
}

// source: j/0/computer/computersavemenu.c:385  [anchor-mhash]
void __cdecl ComputerSaveMenu_SaveSlotDrawHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptMiddle; // eax
  int v2; // eax
  struct QTask_s *ptHead; // eax
  struct QReference_s *ptTail; // eax

  if ( !BYTE2(ptQTask[2].ptPrev) || LOBYTE(ptQTask[2].ptPrev) )
    ptMiddle = ptQTask[3].tQTaskChildren.ptMiddle;
  else
    ptMiddle = ptQTask[3].tQTaskChildren.ptTail;
  v2 = (int)ptMiddle;
  ptQTask[3].tQTaskChildren.ptHead->tQTaskRefList.ptHead = (struct QReference_s *)LODWORD(ComputerMenu_atColor[v2].vX);
  ptQTask[3].tQTaskChildren.ptHead->tQTaskRefList.ptMiddle = (struct QReference_s *)LODWORD(ComputerMenu_atColor[v2].vY);
  ptQTask[3].tQTaskChildren.ptHead->tQTaskRefList.ptTail = (struct QReference_s *)LODWORD(ComputerMenu_atColor[v2].vZ);
  ptQTask[10].tQTaskRefList.ptTail[1].pxObject = (void *)LODWORD(ComputerMenu_atColor[v2].vX);
  ptQTask[10].tQTaskRefList.ptTail[2].ptNext = (struct QReference_s *)LODWORD(ComputerMenu_atColor[v2].vY);
  ptQTask[10].tQTaskRefList.ptTail[2].ptPrev = (struct QReference_s *)LODWORD(ComputerMenu_atColor[v2].vZ);
  ptHead = ptQTask[3].tQTaskChildren.ptHead;
  QTilemap_Register(
    (struct QTilemap_s *)ptHead->ptNext,
    *(float *)&ptHead->ptPrev,
    *(float *)&ptHead->tQTaskChildren.ptHead,
    *(float *)&ptHead->tQTaskRefList.ptHead,
    *(float *)&ptHead->tQTaskRefList.ptMiddle,
    *(float *)&ptHead->tQTaskRefList.ptTail,
    *(float *)&ptHead->tQTaskChildren.ptTail,
    *(float *)&ptHead->tQTaskChildren.ptMiddle,
    *(_DWORD *)&ptHead->eQTaskType | 0x40000000,
    (int)ptHead->ptParent);
  ptTail = ptQTask[10].tQTaskRefList.ptTail;
  QTilemap_Register(
    (struct QTilemap_s *)ptTail->ptNext,
    *(float *)&ptTail->ptPrev,
    *(float *)&ptTail->pxObject,
    *(float *)&ptTail[1].pxObject,
    *(float *)&ptTail[2].ptNext,
    *(float *)&ptTail[2].ptPrev,
    *(float *)&ptTail[1].ptPrev,
    *(float *)&ptTail[1].ptNext,
    (int)ptTail[3].ptNext | 0x40000000,
    (int)ptTail[2].pxObject);
}

// source: j/0/computer/computersavemenu.c:419  [anchor-callee]
float *__cdecl ComputerSaveMenu_CalcSlotCoordinates(
        float *pvX,
        float *pvY,
        int iSaveSlot)
{
  double nHeight; // st7

  nHeight = (double)Display_tActiveMode.nHeight;
  *pvX = (double)Display_tActiveMode.nWidth * 0.15625;
  *pvY = ((double)iSaveSlot * 0.0729166641831398 + 0.25) * nHeight;
  return pvX;
}

// source: j/0/computer/computersavemenu.c:437  [anchor-caller]
struct SaveSlot_s *__cdecl ComputerSaveMenu_NewSaveSlot(
        struct ComputerSaveMenu_s *ptComputerSaveMenu,
        int iSaveSlot,
        enum bool isEnabled)
{
  #pragma pack(push, 1)
  union
  {
    struct { char *v17; };
    struct { char igi2_o1[28]; int eMenuItem; };
    struct { char igi2_o2[32]; int ptQTask; };
    struct { char igi2_o3[36]; char *zFontName; };
    struct { char igi2_o4[40]; int eLinkDown; };
    struct { char igi2_o5[44]; int eLinkLeft; };
    struct { char igi2_o6[48]; struct SaveGame_s ptSaveGame; };
    struct { char igi2_o7[64]; char zBuffer[256]; };
    struct { char igi2_o8[320]; char Buffer[1024]; };
    char igi2_extent[1344];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v3; // ebp
  struct Game_s *v4; // edx
  struct QTask_s *ptHead; // eax
  struct QTask_s *v6; // eax
  struct Game_s *v7; // eax
  struct QTask_s *v8; // eax
  struct QSprite_s *Font; // eax
  int v10; // esi
  int v11; // edi
  struct QTask_s *v12; // eax
  struct QTask_s *v13; // ebx
  struct QSprite_s *v14; // eax
  float *v15; // eax

  v3 = QTask_NewFn(ptComputerSaveMenu->ptMenuItemQTask, ComputerSaveMenu_eSaveSlotQTaskType, nullptr);
  sprintf(
    (char *const)&v3[4],
    (char *const)&g_ptParentQTask.tQTaskRefList,
    Config_tConfig.iActiveProfile,
    Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eDifficultyLevel,
    Game_iMissionID,
    iSaveSlot);
  if ( Game_GetSaveGameTimeDateString(&igi2_frame.ptSaveGame, igi2_frame.zBuffer, 0x100u, (char *)&v3[4]) )
  {
    Game_GetSaveGameInfoString(igi2_frame.Buffer, 0x400u, &igi2_frame.ptSaveGame);
    v4 = Game_ptGame;
    v3[10].tQTaskRefList.ptMiddle = nullptr;
    ptHead = v4->ptGameScreenQTask[1].tQTaskChildren.ptHead;
    igi2_frame.zFontName = igi2_frame.Buffer;
    if ( ptHead )
      v6 = ptHead->tQTaskChildren.ptHead;
    else
      v6 = nullptr;
    igi2_frame.v17 = igi2_frame.zBuffer;
  }
  else
  {
    igi2_frame.zFontName = (char *)Config_GetLocalizedStringForLanguage(
                          "computer/Unused",
                          Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                          true);
    v7 = Game_ptGame;
    v3[10].tQTaskRefList.ptMiddle = (struct QReference_s *)1;
    v8 = v7->ptGameScreenQTask[1].tQTaskChildren.ptHead;
    if ( v8 )
      v6 = v8->tQTaskChildren.ptHead;
    else
      v6 = nullptr;
    igi2_frame.v17 = (char *)&g_zInitialValue;
  }
  Font = MenuManager_GetFont(v6, (char *)&g_zFontName_0.tQTaskChildren.ptMiddle);
  v3[10].tQTaskRefList.ptTail = (struct QReference_s *)Text_New(Font, 0.0, 0.0, igi2_frame.v17);
  *(_DWORD *)&v3[3].eQTaskType = iSaveSlot;
  v10 = 7;
  *(float *)&igi2_frame.eLinkDown = (double)Display_tActiveMode.nWidth * 0.15625;
  *(float *)&igi2_frame.eLinkLeft = ((double)iSaveSlot * 0.0729166641831398 + 0.25) * (double)Display_tActiveMode.nHeight;
  if ( iSaveSlot == 4 )
  {
    igi2_frame.eMenuItem = 7;
  }
  else
  {
    igi2_frame.eMenuItem = iSaveSlot + 11;
    if ( !iSaveSlot )
    {
      v10 = 7;
      igi2_frame.ptQTask = 7;
LABEL_16:
      v11 = iSaveSlot + 11;
      if ( !iSaveSlot )
        goto LABEL_18;
      goto LABEL_17;
    }
  }
  igi2_frame.ptQTask = iSaveSlot + 9;
  if ( iSaveSlot != 4 )
    goto LABEL_16;
  v11 = 7;
LABEL_17:
  v10 = iSaveSlot + 9;
LABEL_18:
  v12 = Game_ptGame->ptGameScreenQTask[1].tQTaskChildren.ptHead;
  if ( v12 )
    v13 = v12->tQTaskChildren.ptHead;
  else
    v13 = nullptr;
  v14 = MenuManager_GetFont(v13, (char *)&g_zFontName_0.tQTaskChildren.ptMiddle);
  ComputerTextItem_Init(
    v3,
    iSaveSlot + 10,
    v10,
    v11,
    igi2_frame.ptQTask,
    igi2_frame.eMenuItem,
    (enum bool)(isEnabled == false),
    *(float *)&igi2_frame.eLinkDown,
    *(float *)&igi2_frame.eLinkLeft,
    v14,
    igi2_frame.zFontName,
    COMPUTERMENU_COLOR_GREEN,
    COMPUTERMENU_COLOR_LIGHT_GREEN,
    ComputerSaveMenu_SlotItemActivateCB);
  *(float *)&v3[10].tQTaskRefList.ptTail->ptPrev = (float)(__int64)*(float *)&v3[3].tQTaskChildren.ptHead->ptPrev;
  v15 = (float *)v3[3].tQTaskChildren.ptHead;
  *(float *)&v3[10].tQTaskRefList.ptTail->pxObject = (float)(int)(__int64)((double)(*(__int16 *)(*(_DWORD *)v15 + 6)
                                                                                  * *(__int16 *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)v15 + 8) + 8)
                                                                                               + 36
                                                                                               * *(unsigned __int16 *)(*(_DWORD *)(*(_DWORD *)v15 + 8) + 20)
                                                                                               + 14))
                                                                         + v15[2]);
  return (struct SaveSlot_s *)v3;
}

// source: j/0/computer/computersavemenu.c:526  [size]
void __cdecl ComputerSaveMenu_SaveSlotDeleteHandler(struct QTask_s *ptQTask)
{
  Text_Delete((struct StaticTilemap_s *)ptQTask[10].tQTaskRefList.ptTail);
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[2][ComputerTextItem_eQTaskType].pfHandler)(ptQTask);
}

// source: j/0/computer/computersavemenu.c:543  [anchor-strings]
void __cdecl ComputerSaveMenu_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  double nHeight; // st7
  struct QTask_s *ScreenMenuItems; // eax
  struct Game_s *v5; // edx
  struct QTask_s *ptHead; // eax
  struct QTask_s *v7; // ebx
  struct QSprite_s *Font; // eax
  struct StaticTilemap_s *v9; // eax
  int v10; // edx
  struct QTask_s *v11; // edi
  __int16 *anGraphicWidth; // ecx
  struct Game_s *v13; // ecx
  struct QTask_s *v14; // eax
  struct QTask_s *v15; // ebx
  struct QSprite_s *v16; // eax
  struct StaticTilemap_s *v17; // eax
  struct Game_s *v18; // eax
  struct QTask_s *v19; // eax
  struct QTask_s *v20; // ebx
  struct QSprite_s *v21; // eax
  struct StaticTilemap_s *v22; // eax
  struct Game_s *v23; // eax
  struct QTask_s *v24; // eax
  struct QTask_s *v25; // eax
  struct QSprite_s *v26; // eax
  struct StaticTilemap_s *v27; // eax
  struct QTask_s *pxObject; // eax
  double BatteryLevel; // st7
  struct QTask_s *v30; // eax
  struct QTask_s *v31; // ebx
  struct QSprite_s *v32; // eax
  struct StaticTilemap_s *v33; // eax
  float vZ; // edx
  struct QTask_s *v35; // eax
  struct QTask_s *v36; // ebx
  struct QSprite_s *v37; // eax
  struct StaticTilemap_s *v38; // eax
  float *ptMiddle; // ebx
  int v40; // ecx
  struct QTask_s *v41; // edi
  __int16 *v42; // edx
  float *v43; // eax
  struct QTask_s *v44; // eax
  struct QTask_s *v45; // eax
  struct QSprite_s *v46; // eax
  struct StaticTilemap_s *v47; // eax
  float *v48; // eax
  struct QTask_s *v49; // eax
  struct QTask_s *v50; // eax
  struct QSprite_s *v51; // eax
  struct StaticTilemap_s *v52; // eax
  char *LocalizedStringForLanguage; // [esp-8h] [ebp-28h]
  char *v54; // [esp-8h] [ebp-28h]
  char *v55; // [esp-8h] [ebp-28h]
  char *v56; // [esp-8h] [ebp-28h]
  float v57; // [esp+8h] [ebp-18h]
  float nWidth; // [esp+Ch] [ebp-14h]
  float v59; // [esp+10h] [ebp-10h]
  struct QTask_s *ptQTaska = *(struct QTask_s * *)&ptQTask; // [esp+24h] [ebp+4h] ARGSLOT
  struct QTask_s *ptQTaskb = *(struct QTask_s * *)&ptQTask; // [esp+24h] [ebp+4h] ARGSLOT

  nWidth = (float)Display_tActiveMode.nWidth;
  nHeight = (double)Display_tActiveMode.nHeight;
  ptQTask[2].ptNext = nullptr;
  v57 = nHeight;
  ComputerSaveMenu_ptQTask = ptQTask;
  ptQTask[2].ptPrev = nullptr;
  ScreenMenuItems = ComputerMenu_CreateScreenMenuItems(
                      (struct MenuItem_s **)&ptQTask[2],
                      (struct MenuItem_s **)&ptQTask[2].ptPrev,
                      ptQTask,
                      COMPUTERMENU_SAVE);
  v5 = Game_ptGame;
  ptQTask[1].ptNext = ScreenMenuItems;
  ptQTask[1].ptParent = nullptr;
  *(_DWORD *)&ptQTask[1].eQTaskType = 1;
  ptHead = v5->ptGameScreenQTask[1].tQTaskChildren.ptHead;
  if ( ptHead )
    v7 = ptHead->tQTaskChildren.ptHead;
  else
    v7 = nullptr;
  LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                 "computer/IGI HQ",
                                 Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                 true);
  Font = MenuManager_GetFont(v7, (char *)&g_zFontName_1);
  v9 = Text_New(Font, 0.0, 0.0, LocalizedStringForLanguage);
  ptQTask[1].tQTaskRefList.ptTail = (struct QReference_s *)v9;
  v10 = v9->ptQTilemap->nHeight;
  v11 = nullptr;
  ptQTaska = nullptr;
  if ( v10 > 0 )
  {
    anGraphicWidth = v9->ptQTilemap->anGraphicWidth;
    do
    {
      if ( *anGraphicWidth > (int)v11 )
        v11 = (struct QTask_s *)*anGraphicWidth;
      ++anGraphicWidth;
      --v10;
    }
    while ( v10 );
    ptQTaska = v11;
  }
  v13 = Game_ptGame;
  v9->vX = (float)(int)(__int64)((nWidth - (double)(int)ptQTaska) * 0.5);
  *(float *)&ptQTask[1].tQTaskRefList.ptTail->pxObject = (float)(int)(__int64)(v57 * 0.1041666641831398);
  v14 = v13->ptGameScreenQTask[1].tQTaskChildren.ptHead;
  if ( v14 )
    v15 = v14->tQTaskChildren.ptHead;
  else
    v15 = nullptr;
  v16 = MenuManager_GetFont(v15, (char *)&g_zFontName_1);
  v17 = Text_New(v16, 0.0, 0.0, (char *)&g_zInitialValue);
  ptQTask[1].tQTaskRefList.ptMiddle = (struct QReference_s *)v17;
  v59 = (float)(int)(__int64)(nWidth * 0.15625);
  v17->vX = v59;
  v18 = Game_ptGame;
  *(float *)&ptQTask[1].tQTaskRefList.ptMiddle->pxObject = (float)(int)(__int64)(v57 * 0.1875);
  v19 = v18->ptGameScreenQTask[1].tQTaskChildren.ptHead;
  if ( v19 )
    v20 = v19->tQTaskChildren.ptHead;
  else
    v20 = nullptr;
  v54 = Config_GetLocalizedStringForLanguage(
          (char *)&stru_690604.atTexInfo,
          Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
          true);
  v21 = MenuManager_GetFont(v20, (char *)&g_zFontName_0.tQTaskChildren.ptMiddle);
  v22 = Text_New(v21, 0.0, 0.0, v54);
  ptQTask[1].tQTaskChildren.ptTail = (struct QTask_s *)v22;
  v22->vR = ComputerMenu_atColor[0].vX;
  ptQTask[1].tQTaskChildren.ptTail->tQTaskRefList.ptMiddle = (struct QReference_s *)LODWORD(ComputerMenu_atColor[0].vY);
  v23 = Game_ptGame;
  ptQTask[1].tQTaskChildren.ptTail->tQTaskRefList.ptTail = (struct QReference_s *)LODWORD(ComputerMenu_atColor[0].vZ);
  v24 = v23->ptGameScreenQTask[1].tQTaskChildren.ptHead;
  if ( v24 )
    v25 = v24->tQTaskChildren.ptHead;
  else
    v25 = nullptr;
  v26 = MenuManager_GetFont(v25, (char *)&g_zFontName_0.tQTaskChildren.ptMiddle);
  v27 = Text_New(v26, 0.0, 0.0, (char *)&stru_690604);
  ptQTask[1].tQTaskRefList.ptHead = (struct QReference_s *)v27;
  v27->vR = ComputerMenu_atColor[1].vX;
  ptQTask[1].tQTaskRefList.ptHead[2].ptNext = (struct QReference_s *)LODWORD(ComputerMenu_atColor[1].vY);
  ptQTask[1].tQTaskRefList.ptHead[2].ptPrev = (struct QReference_s *)LODWORD(ComputerMenu_atColor[1].vZ);
  pxObject = (struct QTask_s *)Level_atLevelQTaskID[0];
  if ( Level_atLevelQTaskID[0] )
    pxObject = (struct QTask_s *)Level_atLevelQTaskID[0]->pxObject;
  BatteryLevel = HumanPlayer_GetBatteryLevel(pxObject);
  *(float *)&ptQTask[2].tQTaskChildren.ptMiddle = BatteryLevel;
  if ( BatteryLevel == 0.0 )
  {
    v35 = Game_ptGame->ptGameScreenQTask[1].tQTaskChildren.ptHead;
    if ( v35 )
      v36 = v35->tQTaskChildren.ptHead;
    else
      v36 = nullptr;
    v56 = Config_GetLocalizedStringForLanguage(
            "computer/BATTERY LOW",
            Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
            true);
    v37 = MenuManager_GetFont(v36, (char *)&g_zFontName_0.tQTaskChildren.ptMiddle);
    v38 = Text_New(v37, 0.0, 0.0, v56);
    ptQTask[1].tQTaskChildren.ptMiddle = (struct QTask_s *)v38;
    v38->vR = ComputerMenu_atColor[0].vX;
    ptQTask[1].tQTaskChildren.ptMiddle->tQTaskRefList.ptMiddle = (struct QReference_s *)LODWORD(ComputerMenu_atColor[0].vY);
    vZ = ComputerMenu_atColor[0].vZ;
  }
  else
  {
    v30 = Game_ptGame->ptGameScreenQTask[1].tQTaskChildren.ptHead;
    if ( v30 )
      v31 = v30->tQTaskChildren.ptHead;
    else
      v31 = nullptr;
    v55 = Config_GetLocalizedStringForLanguage(
            "computer/Battery Level",
            Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
            true);
    v32 = MenuManager_GetFont(v31, (char *)&g_zFontName_0.tQTaskChildren.ptMiddle);
    v33 = Text_New(v32, 0.0, 0.0, v55);
    ptQTask[1].tQTaskChildren.ptMiddle = (struct QTask_s *)v33;
    v33->vR = ComputerMenu_atColor[1].vX;
    ptQTask[1].tQTaskChildren.ptMiddle->tQTaskRefList.ptMiddle = (struct QReference_s *)LODWORD(ComputerMenu_atColor[1].vY);
    vZ = ComputerMenu_atColor[1].vZ;
  }
  *(float *)&ptQTask[1].tQTaskChildren.ptMiddle->tQTaskRefList.ptTail = vZ;
  ptMiddle = (float *)ptQTask[1].tQTaskChildren.ptMiddle;
  v40 = *(__int16 *)(*(_DWORD *)ptMiddle + 6);
  v41 = nullptr;
  ptQTaskb = nullptr;
  if ( v40 > 0 )
  {
    v42 = *(__int16 **)(*(_DWORD *)ptMiddle + 12);
    do
    {
      if ( *v42 > (int)v41 )
        v41 = (struct QTask_s *)*v42;
      ++v42;
      --v40;
    }
    while ( v40 );
    ptQTaskb = v41;
  }
  ptMiddle[1] = (float)(int)(__int64)(nWidth * 0.78125 - (double)(int)ptQTaskb);
  v43 = (float *)ptQTask[1].tQTaskChildren.ptMiddle;
  v43[2] = (float)(int)(__int64)(v57 * 0.6458333134651184
                               + 64.0
                               - (double)(*(__int16 *)(*(_DWORD *)v43 + 6)
                                        * *(__int16 *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)v43 + 8) + 8)
                                                     + 36 * *(unsigned __int16 *)(*(_DWORD *)(*(_DWORD *)v43 + 8) + 20)
                                                     + 14)));
  v44 = Game_ptGame->ptGameScreenQTask[1].tQTaskChildren.ptHead;
  if ( v44 )
    v45 = v44->tQTaskChildren.ptHead;
  else
    v45 = nullptr;
  v46 = MenuManager_GetFont(v45, (char *)&g_zFontName_0.tQTaskChildren.ptMiddle);
  v47 = Text_New(v46, 0.0, 0.0, (char *)&g_zInitialValue);
  ptQTask[1].tQTaskChildren.ptHead = (struct QTask_s *)v47;
  v47->vR = ComputerMenu_atColor[1].vX;
  ptQTask[1].tQTaskChildren.ptHead->tQTaskRefList.ptMiddle = (struct QReference_s *)LODWORD(ComputerMenu_atColor[1].vY);
  ptQTask[1].tQTaskChildren.ptHead->tQTaskRefList.ptTail = (struct QReference_s *)LODWORD(ComputerMenu_atColor[1].vZ);
  *(float *)&ptQTask[1].tQTaskChildren.ptHead->ptPrev = v59;
  v48 = (float *)ptQTask[1].tQTaskChildren.ptHead;
  v48[2] = (float)(int)(__int64)(v57 * 0.7916666865348816
                               - (double)(*(__int16 *)(*(_DWORD *)v48 + 6)
                                        * *(__int16 *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)v48 + 8) + 8)
                                                     + 36 * *(unsigned __int16 *)(*(_DWORD *)(*(_DWORD *)v48 + 8) + 20)
                                                     + 14))
                               - 2.0);
  v49 = Game_ptGame->ptGameScreenQTask[1].tQTaskChildren.ptHead;
  if ( v49 )
    v50 = v49->tQTaskChildren.ptHead;
  else
    v50 = nullptr;
  v51 = MenuManager_GetFont(v50, (char *)&g_zFontName_0.tQTaskChildren.ptMiddle);
  v52 = Text_New(v51, 0.0, 0.0, (char *)&g_zInitialValue);
  ptQTask[1].ptPrev = (struct QTask_s *)v52;
  v52->vR = ComputerMenu_atColor[3].vX;
  ptQTask[1].ptPrev->tQTaskRefList.ptMiddle = (struct QReference_s *)LODWORD(ComputerMenu_atColor[3].vY);
  ptQTask[1].ptPrev->tQTaskRefList.ptTail = (struct QReference_s *)LODWORD(ComputerMenu_atColor[3].vZ);
}

void __cdecl sub_4E8350(struct QTask_s *a1)
{
  Text_Delete((struct StaticTilemap_s *)a1[1].tQTaskRefList.ptTail);
  Text_Delete((struct StaticTilemap_s *)a1[1].tQTaskChildren.ptTail);
  Text_Delete((struct StaticTilemap_s *)a1[1].tQTaskRefList.ptMiddle);
  Text_Delete((struct StaticTilemap_s *)a1[1].tQTaskRefList.ptHead);
  Text_Delete((struct StaticTilemap_s *)a1[1].tQTaskChildren.ptMiddle);
  Text_Delete((struct StaticTilemap_s *)a1[1].tQTaskChildren.ptHead);
  Text_Delete((struct StaticTilemap_s *)a1[1].ptPrev);
  ComputerSaveMenu_ptQTask = nullptr;
}

// source: j/0/computer/computersavemenu.c:689  [anchor-strings]
void __cdecl ComputerSaveMenu_RunHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vY; };
    struct { float vYa; };
    struct { char igi2_o2[8]; char *v76; };
    struct { char igi2_o3[8]; char *v77; };
    struct { char igi2_o4[8]; char *v78; };
    struct { char igi2_o5[8]; char *v79; };
    struct { char igi2_o6[20]; char *v80; };
    struct { char igi2_o7[20]; char *v81; };
    struct { char igi2_o8[20]; char *v82; };
    struct { char igi2_o9[40]; enum bool isDisabled; };
    struct { char igi2_o10[44]; float nHeight; };
    struct { char igi2_o11[48]; enum bool vX; };
    struct { char igi2_o12[52]; int eLinkLeft[2]; };
    struct { char igi2_o13[60]; __int64 v87; };
    struct { char igi2_o14[68]; enum bool v88; };
    struct { char igi2_o15[72]; int eLinkDown; };
    struct { char igi2_o16[76]; _DWORD v90[7]; };
    struct { char igi2_o17[104]; char Buffer[512]; };
    char igi2_extent[616];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptHead; // ecx
  struct QTask_s *ptNext; // eax
  int v3; // edx
  struct QTask_s *v4; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v6; // edx
  char *LocalizedStringForLanguage; // eax
  float *v8; // ebx
  int v9; // eax
  int v10; // ecx
  enum bool v11; // esi
  __int16 *v12; // eax
  struct QTask_s *ptPrev; // edx
  struct QTask_s *v14; // edx
  double v15; // st7
  struct QReference_s *v16; // eax
  _DWORD *pxObject; // ecx
  char *v18; // eax
  BOOL v19; // edx
  _BYTE *v20; // eax
  struct QTask_s *v21; // eax
  struct QTask_s *v22; // eax
  struct QTask_s *v23; // eax
  char *LocalizedString; // eax
  _DWORD *v25; // eax
  int v26; // edx
  struct QTask_s *v27; // eax
  struct QSprite_s *v28; // eax
  struct QTask_s *v29; // eax
  struct QSprite_s *v30; // eax
  struct QTask_s *v31; // eax
  struct QSprite_s *v32; // eax
  struct QTask_s *v33; // eax
  struct QSprite_s *v34; // eax
  struct QTask_s *v35; // eax
  struct QSprite_s *v36; // eax
  struct QTask_s *v37; // eax
  struct QSprite_s *v38; // eax
  float v39; // esi
  double v40; // st7
  struct QReference_s *v41; // edx
  struct QReference_s *v42; // ecx
  struct QTask_s *v43; // eax
  struct QSprite_s *v44; // eax
  struct QTask_s *ptTail; // ecx
  struct QTask_s *v46; // eax
  struct QTask_s *v47; // eax
  struct QTask_s *v48; // eax
  enum bool v49; // edi
  struct QTask_s *v50; // esi
  struct QTask_s *ScreenMenuItems; // eax
  struct QTask_s *v52; // edx
  enum bool ptMiddle; // eax
  struct QReference_s *v54; // edi
  struct QTask_s *v55; // eax
  struct QSprite_s *v56; // eax
  int v57; // esi
  struct QTask_s *v58; // eax
  struct QSprite_s *v59; // eax
  struct QTask_s *v60; // eax
  struct QTask_s *v61; // ecx
  enum GameLanguage_e eLanguage; // eax
  struct QTask_s *v63; // ebx
  char *v64; // esi
  struct QSprite_s *Font; // ebx
  struct QTask_s *v66; // eax
  char *v67; // eax
  int i; // esi
  struct SaveSlot_s *v69; // eax
  struct QReference_s *v70; // eax
  char *v71; // edx
  struct QTask_s *v72; // ebp
  int v73; // eax

  ptHead = ptQTask->tQTaskChildren.ptHead;
  *(float *)&igi2_frame.v88 = (float)Display_tActiveMode.nWidth;
  ptNext = ptHead->ptNext;
  igi2_frame.nHeight = (float)Display_tActiveMode.nHeight;
  if ( ptNext && ptHead )
  {
    v3 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v4 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v4 = nullptr;
      QTask_atProtectedQTaskStack[v3].ptQTask = v4;
      pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][ptHead->eQTaskType].pfHandler;
      v6 = v3 + 1;
      QTask_nProtectedQTaskStackOffset = v6;
      if ( pfHandler )
      {
        pfHandler(ptHead);
        v6 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v6];
      v3 = v6 - 1;
      QTask_nProtectedQTaskStackOffset = v3;
    }
    while ( ptHead );
  }
  if ( ptQTask[1].ptParent == (struct QTask_s *)5 )
  {
    LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                   "computer/Uploading",
                                   Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                   true);
    sprintf(igi2_frame.Buffer, "%s:", LocalizedStringForLanguage);
    Text_SetString((struct StaticTilemap_s *)ptQTask[1].tQTaskChildren.ptHead, igi2_frame.Buffer);
    *(_QWORD *)igi2_frame.eLinkLeft = (__int64)(*(float *)&ptQTask[2].tQTaskChildren.ptTail * 100.0);
    sprintf(igi2_frame.Buffer, "%d%%", igi2_frame.eLinkLeft[0]);
    Text_SetString((struct StaticTilemap_s *)ptQTask[1].ptPrev, igi2_frame.Buffer);
    v8 = (float *)ptQTask[1].tQTaskChildren.ptHead;
    v9 = *(_DWORD *)v8;
    v10 = *(__int16 *)(*(_DWORD *)v8 + 6);
    *(float *)&v11 = 0.0;
    *(float *)&igi2_frame.isDisabled = 0.0;
    if ( v10 > 0 )
    {
      v12 = *(__int16 **)(v9 + 12);
      do
      {
        if ( *v12 > v11 )
          v11 = *v12;
        ++v12;
        --v10;
      }
      while ( v10 );
      igi2_frame.isDisabled = v11;
    }
    ptPrev = ptQTask[1].ptPrev;
    *(_QWORD *)igi2_frame.eLinkLeft = (__int64)((double)(int)igi2_frame.isDisabled + v8[1]);
    igi2_frame.vX = (enum bool)igi2_frame.eLinkLeft[0];
    *(float *)&ptPrev->ptPrev = (float)igi2_frame.eLinkLeft[0];
    v14 = ptQTask[1].ptPrev;
    *(_QWORD *)igi2_frame.eLinkLeft = (__int64)*(float *)&ptQTask[1].tQTaskChildren.ptHead->tQTaskChildren.ptHead;
    igi2_frame.vX = (enum bool)igi2_frame.eLinkLeft[0];
    *(float *)&v14->tQTaskChildren.ptHead = (float)igi2_frame.eLinkLeft[0];
    v15 = *(float *)&ptQTask[2].tQTaskChildren.ptTail + 0.009999999776482582;
    *(float *)&ptQTask[2].tQTaskChildren.ptTail = v15;
    if ( v15 >= 1.0 )
    {
      ptQTask[2].tQTaskChildren.ptTail = (struct QTask_s *)1065353216;
      *(_DWORD *)&ptQTask[1].eQTaskType = 6;
    }
  }
  if ( ptQTask[1].ptParent == (struct QTask_s *)6 )
  {
    v16 = ptQTask[2].tQTaskRefList.ptHead;
    if ( (int)v16 <= 0 )
    {
      if ( Level_atLevelQTaskID[0] )
        pxObject = Level_atLevelQTaskID[0]->pxObject;
      else
        pxObject = nullptr;
      v18 = (char *)&ptQTask[2].tQTaskChildren.ptHead->ptNext + 1;
      v19 = Game_eGameMode != GAME_GAMEMODE_SINGLEPLAYER;
      pxObject[853] = v18;
      pxObject[854] = v19 ? nullptr : v18;
      if ( Level_atLevelQTaskID[0] )
        v20 = Level_atLevelQTaskID[0]->pxObject;
      else
        v20 = nullptr;
      v20[3227] = 1;
    }
    else
    {
      ptQTask[2].tQTaskRefList.ptHead = (struct QReference_s *)((char *)v16 - 1);
    }
  }
  if ( *(_DWORD *)&ptQTask[1].eQTaskType )
  {
    v21 = ComputerMenu_ptComputerMenuQTask;
    ComputerMenu_ptComputerMenuQTask[1].tQTaskRefList.ptHead = nullptr;
    v21[1].tQTaskRefList.ptMiddle = nullptr;
    v22 = ptQTask[1].ptNext;
    *(float *)&igi2_frame.vX = 0.0;
    QTask_DeleteChildren(v22);
    v23 = *(struct QTask_s **)&ptQTask[1].eQTaskType;
    ptQTask[1].ptParent = v23;
    *(_DWORD *)&ptQTask[1].eQTaskType = 0;
    if ( v23 == (struct QTask_s *)2 || v23 == (struct QTask_s *)3 )
    {
      v61 = Game_ptGame->ptGameScreenQTask[1].tQTaskChildren.ptHead;
      eLanguage = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage;
      *(float *)&igi2_frame.eLinkDown = (double)Display_tActiveMode.nWidth * 0.15625;
      *(float *)igi2_frame.eLinkLeft = (double)Display_tActiveMode.nHeight * 0.6145833134651184;
      if ( v61 )
        v63 = v61->tQTaskChildren.ptHead;
      else
        v63 = nullptr;
      v64 = Config_GetLocalizedStringForLanguage("computer/Cancel", eLanguage, true);
      Font = MenuManager_GetFont(v63, (char *)&g_zFontName_1);
      v66 = QTask_NewFn(ptQTask[1].ptNext, ComputerTextItem_eQTaskType, nullptr);
      ComputerTextItem_Init(
        v66,
        7,
        14,
        10,
        14,
        10,
        false,
        *(float *)&igi2_frame.eLinkDown,
        *(float *)igi2_frame.eLinkLeft,
        Font,
        v64,
        COMPUTERMENU_COLOR_GREEN,
        COMPUTERMENU_COLOR_LIGHT_GREEN,
        ComputerSaveMenu_CancelItemActivateCB);
      if ( ptQTask[1].ptParent == (struct QTask_s *)2 )
        v67 = Config_GetLocalizedStringForLanguage(
                "computer/Upload mission data to IGI H.Q",
                Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                true);
      else
        v67 = Config_GetLocalizedStringForLanguage(
                "computer/Download mission data from IGI H.Q",
                Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                true);
      Text_SetString((struct StaticTilemap_s *)ptQTask[1].tQTaskRefList.ptMiddle, v67);
      for ( i = 0; i < 5; ++i )
      {
        v69 = ComputerSaveMenu_NewSaveSlot((struct ComputerSaveMenu_s *)ptQTask, i, true);
        if ( *(float *)&igi2_frame.vX == 0.0 && ptQTask[1].ptParent == (struct QTask_s *)2 && v69->isFree )
        {
          ptQTask[2].tQTaskChildren.ptHead = (struct QTask_s *)i;
          *(_DWORD *)&ptQTask[1].eQTaskType = 5;
          igi2_frame.vX = true;
        }
      }
      v70 = Level_atLevelQTaskID[0];
      if ( Level_atLevelQTaskID[0] )
        v70 = (struct QReference_s *)Level_atLevelQTaskID[0]->pxObject;
      v71 = (char *)v70[284].pxObject;
      v72 = ptQTask[1].ptNext;
      memset(igi2_frame.v90, 0, sizeof(igi2_frame.v90));
      v73 = 511 * MenuItem_eActivateQTaskEvent + v72->eQTaskType;
      if ( v71 )
        igi2_frame.v90[0] = v71 + 9;
      else
        igi2_frame.v90[0] = 7;
      ((void (__cdecl *)(struct QTask_s *, _DWORD *))QTask_aatQTaskFinalEvent[0][v73].pfHandler)(v72, igi2_frame.v90);
    }
    else if ( v23 == (struct QTask_s *)5 )
    {
      ptQTask[2].tQTaskChildren.ptTail = nullptr;
    }
    else if ( v23 == (struct QTask_s *)6 )
    {
      LocalizedString = Config_GetLocalizedString("computer/Complete");
      sprintf(igi2_frame.Buffer, (char *const)&stru_6A4CDC.tDebugConsoleLineList.ptMiddle, LocalizedString);
      Text_SetString((struct StaticTilemap_s *)ptQTask[1].ptPrev, igi2_frame.Buffer);
      ptQTask[2].tQTaskRefList.ptHead = (struct QReference_s *)30;
      if ( Level_atLevelQTaskID[0] )
        v25 = Level_atLevelQTaskID[0]->pxObject;
      else
        v25 = nullptr;
      v26 = v25[805] + 1;
      v25[851] = (char *)&ptQTask[2].tQTaskChildren.ptHead->ptNext + 1;
      v25[805] = v26;
      if ( Level_atLevelQTaskID[0] )
        *(float *)&ptQTask[2].tQTaskChildren.ptMiddle = HumanPlayer_GetBatteryLevel((struct QTask_s *)Level_atLevelQTaskID[0]->pxObject);
      else
        *(float *)&ptQTask[2].tQTaskChildren.ptMiddle = HumanPlayer_GetBatteryLevel(nullptr);
    }
    else if ( v23 == (struct QTask_s *)4 )
    {
      ComputerSaveMenu_CalcSlotCoordinates((float *)&igi2_frame.isDisabled, (float *)&igi2_frame.vX, (int)ptQTask[2].tQTaskChildren.ptHead);
      igi2_frame.v80 = Config_GetLocalizedString("computer/Yes");
      v27 = sub_40A180();
      v28 = MenuManager_GetFont(v27, (char *)&g_zFontName_0.tQTaskChildren.ptMiddle);
      igi2_frame.nHeight = COERCE_FLOAT(Font_GetStringWidth(v28, igi2_frame.v80));
      *(float *)&igi2_frame.eLinkDown = (float)SLODWORD(igi2_frame.nHeight);
      igi2_frame.v81 = Config_GetLocalizedString("computer/No");
      v29 = sub_40A180();
      v30 = MenuManager_GetFont(v29, (char *)&g_zFontName_0.tQTaskChildren.ptMiddle);
      igi2_frame.nHeight = COERCE_FLOAT(Font_GetStringWidth(v30, igi2_frame.v81));
      *(float *)&igi2_frame.isDisabled = (float)SLODWORD(igi2_frame.nHeight);
      v31 = sub_40A180();
      v32 = MenuManager_GetFont(v31, (char *)&g_zFontName_0.tQTaskChildren.ptMiddle);
      igi2_frame.nHeight = COERCE_FLOAT(Font_GetStringWidth(v32, (char *)&stru_690604));
      *(float *)&igi2_frame.v87 = (float)SLODWORD(igi2_frame.nHeight);
      igi2_frame.v82 = Config_GetLocalizedString((char *)&stru_690604.atTexInfo);
      v33 = sub_40A180();
      v34 = MenuManager_GetFont(v33, (char *)&g_zFontName_0.tQTaskChildren.ptMiddle);
      igi2_frame.nHeight = COERCE_FLOAT(Font_GetStringWidth(v34, igi2_frame.v82));
      *(float *)igi2_frame.eLinkLeft = (float)SLODWORD(igi2_frame.nHeight);
      v35 = sub_40A180();
      v36 = MenuManager_GetFont(v35, (char *)&g_zFontName_0.tQTaskChildren.ptMiddle);
      igi2_frame.nHeight = (float)Font_GetStringWidth(v36, (char *)&Delimiter);
      *(float *)&igi2_frame.isDisabled = *(float *)&igi2_frame.v88 * 0.875 - *(float *)&igi2_frame.isDisabled;
      igi2_frame.v76 = Config_GetLocalizedString("computer/No");
      v37 = sub_40A180();
      v38 = MenuManager_GetFont(v37, (char *)&g_zFontName_0.tQTaskChildren.ptMiddle);
      v39 = *(float *)&igi2_frame.vX;
      ComputerTextItem_New(
        ptQTask[1].ptNext,
        9,
        8,
        8,
        8,
        8,
        false,
        *(float *)&igi2_frame.isDisabled,
        *(float *)&igi2_frame.vX,
        v38,
        igi2_frame.v76,
        COMPUTERMENU_COLOR_GREEN,
        COMPUTERMENU_COLOR_LIGHT_GREEN,
        ComputerSaveMenu_NoItemActivateCB);
      v40 = *(float *)&igi2_frame.isDisabled - *(float *)&igi2_frame.v87;
      v41 = ptQTask[1].tQTaskRefList.ptHead;
      igi2_frame.v87 = (__int64)v40;
      LODWORD(igi2_frame.v87) = (__int64)v40;
      *(float *)&v41->ptPrev = (float)(int)igi2_frame.v87;
      v42 = ptQTask[1].tQTaskRefList.ptHead;
      igi2_frame.v87 = (__int64)*(float *)&igi2_frame.vX;
      *(float *)&igi2_frame.v87 = (float)(int)igi2_frame.v87;
      v42->pxObject = (void *)igi2_frame.v87;
      *(float *)&igi2_frame.isDisabled = v40 - *(float *)&igi2_frame.eLinkDown;
      igi2_frame.v77 = Config_GetLocalizedString("computer/Yes");
      v43 = sub_40A180();
      v44 = MenuManager_GetFont(v43, (char *)&g_zFontName_0.tQTaskChildren.ptMiddle);
      ComputerTextItem_New(
        ptQTask[1].ptNext,
        8,
        9,
        9,
        9,
        9,
        false,
        *(float *)&igi2_frame.isDisabled,
        v39,
        v44,
        igi2_frame.v77,
        COMPUTERMENU_COLOR_GREEN,
        COMPUTERMENU_COLOR_LIGHT_GREEN,
        ComputerSaveMenu_YesItemActivateCB);
      ptTail = ptQTask[1].tQTaskChildren.ptTail;
      *(_QWORD *)igi2_frame.eLinkLeft = (__int64)(*(float *)&igi2_frame.isDisabled - *(float *)igi2_frame.eLinkLeft - igi2_frame.nHeight);
      v46 = (struct QTask_s *)igi2_frame.v87;
      *(float *)&ptTail->ptPrev = (float)igi2_frame.eLinkLeft[0];
      ptQTask[1].tQTaskChildren.ptTail->tQTaskChildren.ptHead = v46;
      ComputerSaveMenu_NewSaveSlot(
        (struct ComputerSaveMenu_s *)ptQTask,
        (int)ptQTask[2].tQTaskChildren.ptHead,
        false);
      v47 = ComputerMenu_ptComputerMenuQTask;
      ComputerMenu_ptComputerMenuQTask[1].tQTaskRefList.ptHead = nullptr;
      v47[1].tQTaskRefList.ptMiddle = nullptr;
      MenuItem_Activate(ptQTask[1].ptNext, 8);
    }
    else
    {
      if ( Level_atLevelQTaskID[0] )
        v48 = (struct QTask_s *)Level_atLevelQTaskID[0]->pxObject;
      else
        v48 = nullptr;
      v49 = HumanPlayer_IsSaveAllowed(v48);
      v50 = ptQTask + 2;
      igi2_frame.eLinkLeft[0] = v49;
      ScreenMenuItems = ComputerMenu_CreateScreenMenuItems(
                          (struct MenuItem_s **)&ptQTask[2],
                          (struct MenuItem_s **)&ptQTask[2].ptPrev,
                          ptQTask,
                          COMPUTERMENU_SAVE);
      v52 = ptQTask[2].ptPrev;
      ptQTask[1].ptNext = ScreenMenuItems;
      v52[1].ptParent = (struct QTask_s *)6;
      ptQTask[2].ptPrev[2].ptNext = (struct QTask_s *)6;
      v50->ptNext[1].tQTaskRefList.ptTail = (struct QReference_s *)(6 - (v49 != false));
      *(_DWORD *)&v50->ptNext[1].eQTaskType = v50->ptNext[1].tQTaskRefList.ptTail;
      if ( v49 )
        ptMiddle = 5;
      else
        ptMiddle = (enum bool)v50->ptNext[1].tQTaskRefList.ptMiddle;
      igi2_frame.vX = ptMiddle;
      igi2_frame.isDisabled = ptMiddle;
      v54 = ptQTask[2].ptPrev[1].tQTaskRefList.ptMiddle;
      *(float *)&igi2_frame.v88 = *(float *)&igi2_frame.v88 * 0.15625;
      igi2_frame.v78 = Config_GetLocalizedString("computer/Download mission data from IGI H.Q");
      v55 = sub_40A180();
      v56 = MenuManager_GetFont(v55, (char *)&g_zFontName_1);
      igi2_frame.vY = igi2_frame.nHeight * 0.1875;
      ComputerTextItem_New(
        ptQTask[1].ptNext,
        6,
        (int)v54,
        igi2_frame.isDisabled,
        (int)v54,
        igi2_frame.vX,
        false,
        *(float *)&igi2_frame.v88,
        igi2_frame.vY,
        v56,
        igi2_frame.v78,
        COMPUTERMENU_COLOR_GREEN,
        COMPUTERMENU_COLOR_LIGHT_GREEN,
        ComputerSaveMenu_DownloadItemActivateCB);
      if ( igi2_frame.eLinkLeft[0] )
      {
        v57 = (int)v50->ptNext[1].tQTaskRefList.ptMiddle;
        igi2_frame.v79 = Config_GetLocalizedString("computer/Upload mission data to IGI H.Q");
        v58 = sub_40A180();
        v59 = MenuManager_GetFont(v58, (char *)&g_zFontName_1);
        igi2_frame.vYa = igi2_frame.nHeight * 0.22291666269302368;
        ComputerTextItem_New(
          ptQTask[1].ptNext,
          5,
          6,
          v57,
          6,
          v57,
          false,
          *(float *)&igi2_frame.v88,
          igi2_frame.vYa,
          v59,
          igi2_frame.v79,
          COMPUTERMENU_COLOR_GREEN,
          COMPUTERMENU_COLOR_LIGHT_GREEN,
          ComputerSaveMenu_UploadItemActivateCB);
      }
      Text_SetString((struct StaticTilemap_s *)ptQTask[1].tQTaskRefList.ptMiddle, (char *)&g_zInitialValue);
      v60 = ComputerMenu_ptComputerMenuQTask;
      ComputerMenu_ptComputerMenuQTask[1].tQTaskRefList.ptHead = nullptr;
      v60[1].tQTaskRefList.ptMiddle = nullptr;
      MenuItem_Activate(ptQTask[1].ptNext, 5);
    }
  }
}

// source: j/0/computer/computersavemenu.c:938  [anchor-mhash]
void __cdecl ComputerSaveMenu_DrawHandler(struct QTask_s *ptQTask)
{
  struct QReference_s *ptTail; // eax
  struct QReference_s *ptMiddle; // eax
  struct QTask_s *v4; // eax
  struct QTask_s *v5; // eax
  struct QReference_s *ptHead; // eax
  float v7; // edi
  double v8; // st7
  struct QTask_s *ptParent; // eax
  struct QTask_s *v10; // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *v12; // ecx
  int v13; // edx
  struct QTask_s *v14; // eax
  int v15; // esi
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v17; // edx
  float nDepth; // [esp+0h] [ebp-74h]
  float nDeptha; // [esp+0h] [ebp-74h]
  float v20; // [esp+4h] [ebp-70h]
  float vHeight; // [esp+8h] [ebp-6Ch]
  float vHeighta; // [esp+8h] [ebp-6Ch]
  float v23; // [esp+Ch] [ebp-68h]
  float vX; // [esp+30h] [ebp-44h]
  float vY; // [esp+34h] [ebp-40h]
  float vWidth; // [esp+64h] [ebp-10h]
  int nDisplayWidth; // [esp+68h] [ebp-Ch]
  float nDisplayWidtha; // [esp+68h] [ebp-Ch]
  float nDisplayWidthb; // [esp+68h] [ebp-Ch]
  int nDisplayHeight; // [esp+6Ch] [ebp-8h]
  float nDisplayHeighta; // [esp+6Ch] [ebp-8h]
  float nDisplayHeightb; // [esp+6Ch] [ebp-8h]
  float vX3; // [esp+70h] [ebp-4h]
  float vX3a; // [esp+70h] [ebp-4h]
  float ptQTaska = *(float *)&ptQTask; // [esp+78h] [ebp+4h] ARGSLOT

  nDisplayHeight = Display_tActiveMode.nHeight;
  nDisplayWidth = Display_tActiveMode.nWidth;
  ptTail = ptQTask[1].tQTaskRefList.ptTail;
  QTilemap_Register(
    (struct QTilemap_s *)ptTail->ptNext,
    *(float *)&ptTail->ptPrev,
    *(float *)&ptTail->pxObject,
    *(float *)&ptTail[1].pxObject,
    *(float *)&ptTail[2].ptNext,
    *(float *)&ptTail[2].ptPrev,
    *(float *)&ptTail[1].ptPrev,
    *(float *)&ptTail[1].ptNext,
    (int)ptTail[3].ptNext | 0x40000000,
    (int)ptTail[2].pxObject);
  ptMiddle = ptQTask[1].tQTaskRefList.ptMiddle;
  QTilemap_Register(
    (struct QTilemap_s *)ptMiddle->ptNext,
    *(float *)&ptMiddle->ptPrev,
    *(float *)&ptMiddle->pxObject,
    *(float *)&ptMiddle[1].pxObject,
    *(float *)&ptMiddle[2].ptNext,
    *(float *)&ptMiddle[2].ptPrev,
    *(float *)&ptMiddle[1].ptPrev,
    *(float *)&ptMiddle[1].ptNext,
    (int)ptMiddle[3].ptNext | 0x40000000,
    (int)ptMiddle[2].pxObject);
  v4 = ptQTask[1].tQTaskChildren.ptMiddle;
  QTilemap_Register(
    (struct QTilemap_s *)v4->ptNext,
    *(float *)&v4->ptPrev,
    *(float *)&v4->tQTaskChildren.ptHead,
    *(float *)&v4->tQTaskRefList.ptHead,
    *(float *)&v4->tQTaskRefList.ptMiddle,
    *(float *)&v4->tQTaskRefList.ptTail,
    *(float *)&v4->tQTaskChildren.ptTail,
    *(float *)&v4->tQTaskChildren.ptMiddle,
    *(_DWORD *)&v4->eQTaskType | 0x40000000,
    (int)v4->ptParent);
  if ( ptQTask[1].ptParent == (struct QTask_s *)4 )
  {
    v5 = ptQTask[1].tQTaskChildren.ptTail;
    QTilemap_Register(
      (struct QTilemap_s *)v5->ptNext,
      *(float *)&v5->ptPrev,
      *(float *)&v5->tQTaskChildren.ptHead,
      *(float *)&v5->tQTaskRefList.ptHead,
      *(float *)&v5->tQTaskRefList.ptMiddle,
      *(float *)&v5->tQTaskRefList.ptTail,
      *(float *)&v5->tQTaskChildren.ptTail,
      *(float *)&v5->tQTaskChildren.ptMiddle,
      *(_DWORD *)&v5->eQTaskType | 0x40000000,
      (int)v5->ptParent);
    ptHead = ptQTask[1].tQTaskRefList.ptHead;
    QTilemap_Register(
      (struct QTilemap_s *)ptHead->ptNext,
      *(float *)&ptHead->ptPrev,
      *(float *)&ptHead->pxObject,
      *(float *)&ptHead[1].pxObject,
      *(float *)&ptHead[2].ptNext,
      *(float *)&ptHead[2].ptPrev,
      *(float *)&ptHead[1].ptPrev,
      *(float *)&ptHead[1].ptNext,
      (int)ptHead[3].ptNext | 0x40000000,
      (int)ptHead[2].pxObject);
  }
  ptQTaska = (float)nDisplayHeight;
  vWidth = (float)nDisplayWidth;
  vY = ptQTaska * 0.0;
  vX = vWidth * 0.0;
  QSprite_RegisterBlankZ(vX, vY, vWidth, ptQTaska, 0.0, 0.0, 0.0, 0x40040000u, -1, 542.47998046875);
  nDisplayHeighta = *(float *)&ptQTask[2].tQTaskChildren.ptMiddle * 128.0;
  nDisplayWidtha = vWidth * 0.78125;
  v7 = nDisplayWidtha;
  vHeight = *(float *)&ptQTask[2].tQTaskChildren.ptMiddle * 64.0;
  nDepth = (1.0 - *(float *)&ptQTask[2].tQTaskChildren.ptMiddle) * 64.0 + ptQTaska * 0.6458333134651184;
  QSprite_RegisterBlank4RGBAZ(
    nDisplayWidtha,
    nDepth,
    64.0,
    vHeight,
    128.0,
    128.0,
    0.0,
    128.0,
    128.0,
    0.0,
    128.0,
    nDisplayHeighta,
    0.0,
    128.0,
    nDisplayHeighta,
    0.0,
    1.0,
    1.0,
    1.0,
    1.0,
    1.0,
    0,
    -1);
  v8 = ptQTaska * 0.6458333134651184;
  nDisplayHeightb = v8;
  vX3 = v8 + 64.0;
  nDisplayWidthb = nDisplayWidtha + 64.0;
  QSprite_Register4AZ(
    &ComputerMenu_tComputerMenuResource.tQSpriteBattery,
    v7,
    nDisplayHeightb,
    nDisplayWidthb,
    nDisplayHeightb,
    v7,
    vX3,
    nDisplayWidthb,
    vX3,
    ComputerMenu_atColor[1].vX,
    ComputerMenu_atColor[1].vY,
    ComputerMenu_atColor[1].vZ,
    1.0,
    1.0,
    0,
    0,
    -1);
  ptParent = ptQTask[1].ptParent;
  if ( ptParent == (struct QTask_s *)5 || ptParent == (struct QTask_s *)6 )
  {
    vX3a = *(float *)&ptQTask[2].tQTaskChildren.ptTail * 128.0;
    v23 = ptQTaska * 0.01666666753590107;
    vHeighta = *(float *)&ptQTask[2].tQTaskChildren.ptTail * 0.65625 * vWidth;
    v20 = ptQTaska * 0.7916666865348816;
    nDeptha = vWidth * 0.15625;
    QSprite_RegisterBlank4RGBAZ(
      nDeptha,
      v20,
      vHeighta,
      v23,
      0.0,
      vX3a,
      128.0,
      0.0,
      128.0,
      128.0,
      0.0,
      vX3a,
      128.0,
      0.0,
      128.0,
      128.0,
      1.0,
      1.0,
      1.0,
      1.0,
      1.0,
      0,
      -1);
    v10 = ptQTask[1].tQTaskChildren.ptHead;
    QTilemap_Register(
      (struct QTilemap_s *)v10->ptNext,
      *(float *)&v10->ptPrev,
      *(float *)&v10->tQTaskChildren.ptHead,
      *(float *)&v10->tQTaskRefList.ptHead,
      *(float *)&v10->tQTaskRefList.ptMiddle,
      *(float *)&v10->tQTaskRefList.ptTail,
      *(float *)&v10->tQTaskChildren.ptTail,
      *(float *)&v10->tQTaskChildren.ptMiddle,
      *(_DWORD *)&v10->eQTaskType | 0x40000000,
      (int)v10->ptParent);
    ptPrev = ptQTask[1].ptPrev;
    QTilemap_Register(
      (struct QTilemap_s *)ptPrev->ptNext,
      *(float *)&ptPrev->ptPrev,
      *(float *)&ptPrev->tQTaskChildren.ptHead,
      *(float *)&ptPrev->tQTaskRefList.ptHead,
      *(float *)&ptPrev->tQTaskRefList.ptMiddle,
      *(float *)&ptPrev->tQTaskRefList.ptTail,
      *(float *)&ptPrev->tQTaskChildren.ptTail,
      *(float *)&ptPrev->tQTaskChildren.ptMiddle,
      *(_DWORD *)&ptPrev->eQTaskType | 0x40000000,
      (int)ptPrev->ptParent);
  }
  v12 = ptQTask->tQTaskChildren.ptHead;
  if ( v12->ptNext && v12 )
  {
    v13 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( v12->ptNext )
        v14 = v12->ptNext->ptNext != nullptr ? v12->ptNext : nullptr;
      else
        v14 = nullptr;
      v15 = Screen_eDrawQTaskEvent;
      QTask_atProtectedQTaskStack[v13].ptQTask = v14;
      pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[v15][v12->eQTaskType].pfHandler;
      v17 = v13 + 1;
      QTask_nProtectedQTaskStackOffset = v17;
      if ( pfHandler )
      {
        pfHandler(v12);
        v17 = QTask_nProtectedQTaskStackOffset;
      }
      v12 = (struct QTask_s *)dword_849C7DC[v17];
      v13 = v17 - 1;
      QTask_nProtectedQTaskStackOffset = v13;
    }
    while ( v12 );
  }
}

// source: j/0/computer/computersavemenu.c:1050  [size]
unsigned __int16 __cdecl ComputerSaveMenu_GetQTaskType()
{
  return ComputerSaveMenu_eQTaskType;
}

// source: j/0/computer/computersavemenu.c:1063  [size]
struct QTask_s *__cdecl ComputerSaveMenu_New(struct QTask_s *ptParent)
{
  return QTask_NewFn(ptParent, ComputerSaveMenu_eQTaskType, nullptr);
}

// source: j/0/computer/computersavemenu.c:1076  [anchor-hash]
void __cdecl ComputerSaveMenu_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si
  unsigned __int16 v2; // si

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("ComputerSaveMenu", 104, BaseQTaskType, 0, 0);
  ComputerSaveMenu_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 0, ComputerSaveMenu_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, sub_4E8350);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, ComputerSaveMenu_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, Screen_eDrawQTaskEvent, ComputerSaveMenu_DrawHandler);
  v2 = QTask_NewQTaskType("SaveSlot", 432, ComputerTextItem_eQTaskType, 0, 0);
  ComputerSaveMenu_eSaveSlotQTaskType = v2;
  QTask_LinkQTaskEventHandlerNoContextFn(v2, 2, ComputerSaveMenu_SaveSlotDeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, Screen_eDrawQTaskEvent, ComputerSaveMenu_SaveSlotDrawHandler);
}

// source: j/0/computer/computersavemenu.c:1097  [size]
void __cdecl ComputerSaveMenu_Close()
{
  QTask_DeleteQTaskType(ComputerSaveMenu_eQTaskType);
  QTask_DeleteQTaskType(ComputerSaveMenu_eSaveSlotQTaskType);
}
