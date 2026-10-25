/* j/0/computer/computerobjectives.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/computer/computerobjectives.c:102  [anchor-mhash]
void __cdecl ComputerObjectives_ButtonItemActivateCB(
        struct MenuItem_s *ptMenuItem,
        struct MenuItemActivateContext_s *ptMenuItemActivateContext)
{
  char v2; // al
  int v3; // eax
  char *v4; // eax
  int v5; // eax

  if ( ptMenuItem->isActivated && !ptMenuItem->isActive )
    SoundSys_PlaySimpleSoundDefFn("mapcomp_05", 1u, nullptr);
  if ( ptMenuItem->eMenuItem == ptMenuItemActivateContext->eMenuItem )
  {
    v2 = (int)ComputerMenu_ptComputerMenuQTask[1].tQTaskChildren.ptTail & 0x10;
    BYTE1(ptMenuItem[1].tClientRect.vY) = LOBYTE(ptMenuItem[1].tClientRect.vY);
    LOBYTE(ptMenuItem[1].tClientRect.vY) = v2;
    if ( v2 )
    {
      SoundSys_PlaySimpleSoundDefFn("mapcomp_01", 1u, nullptr);
      switch ( ptMenuItem->eMenuItem )
      {
        case 5:
          v3 = 0;
          goto LABEL_15;
        case 6:
          v3 = 1;
          goto LABEL_15;
        case 7:
          v3 = 2;
          goto LABEL_15;
        case 8:
          v3 = 3;
          goto LABEL_15;
        case 9:
          v3 = 4;
          goto LABEL_15;
        case 0xA:
          v3 = 5;
          goto LABEL_15;
        case 0xB:
          v3 = 6;
          goto LABEL_15;
        case 0xC:
          v3 = 7;
LABEL_15:
          if ( DefineComputerObjective_ptQTask )
            v4 = (char *)&DefineComputerObjective_ptQTask[3] + 204 * v3;
          else
            v4 = nullptr;
          v5 = *((_DWORD *)v4 + 8);
          if ( v5 != -1 )
          {
            ComputerMap_ptPositionQTask = Level_GetQTaskFromLevelQTaskID(v5);
            ComputerMenu_ptComputerMenuQTask[1].tQTaskRefList.ptTail = (struct QReference_s *)1;
          }
          break;
        default:
          return;
      }
    }
  }
}

// source: j/0/computer/computerobjectives.c:204  [anchor-strings]
void __cdecl ComputerObjectives_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v3; // ebp
  struct QTask_s *ScreenMenuItems; // eax
  enum GameLanguage_e eLanguage; // esi
  char *LocalizedStringForLanguage; // ebx
  struct QTask_s *ptGameScreenQTask; // ecx
  struct QTask_s *ptHead; // eax
  struct QTask_s *v9; // ecx
  struct QSprite_s *Font; // eax
  struct QSprite_s *v11; // eax
  int v12; // esi
  struct QTask_s **p_ptPrev; // edi
  float zFontName; // [esp+0h] [ebp-2Ch]
  float zString; // [esp+4h] [ebp-28h]
  char *v16; // [esp+8h] [ebp-24h]
  float v17; // [esp+1Ch] [ebp-10h]
  int nHeight; // [esp+20h] [ebp-Ch]
  float v19; // [esp+20h] [ebp-Ch]
  int isDisabled; // [esp+24h] [ebp-8h]
  float isDisableda; // [esp+24h] [ebp-8h]
  float isDisabledb; // [esp+24h] [ebp-8h]
  struct QTask_s *ptParent; // [esp+28h] [ebp-4h]
  struct QTask_s *ptQTaska = *(struct QTask_s * *)&ptQTask; // [esp+30h] [ebp+4h] ARGSLOT
  float ptQTaskb = *(float *)&ptQTask; // [esp+30h] [ebp+4h] ARGSLOT

  v3 = nullptr;
  nHeight = Display_tActiveMode.nHeight;
  isDisabled = Display_tActiveMode.nWidth;
  ScreenMenuItems = ComputerMenu_CreateScreenMenuItems(nullptr, nullptr, ptQTask, COMPUTERMENU_OBJECTIVES);
  eLanguage = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage;
  ptParent = ScreenMenuItems;
  LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage("computer/OBJECTIVES", eLanguage, true);
  ptGameScreenQTask = Game_ptGame->ptGameScreenQTask;
  ptHead = ptGameScreenQTask[1].tQTaskChildren.ptHead;
  if ( ptHead )
    ptQTaska = ptHead->tQTaskChildren.ptHead;
  else
    ptQTaska = nullptr;
  v9 = ptGameScreenQTask[1].tQTaskChildren.ptHead;
  if ( v9 )
    v3 = v9->tQTaskChildren.ptHead;
  v17 = (float)nHeight;
  v19 = (float)isDisabled;
  v16 = Config_GetLocalizedStringForLanguage("computer/OBJECTIVES", eLanguage, true);
  zString = v17 * 0.078125;
  isDisableda = v19 * 0.5;
  Font = MenuManager_GetFont(ptQTaska, (char *)&g_zFontName_1);
  zFontName = isDisableda - (double)Font_GetStringWidth(Font, LocalizedStringForLanguage);
  v11 = MenuManager_GetFont(v3, (char *)&g_zFontName_1);
  ptQTask[1].ptNext = (struct QTask_s *)Text_New(v11, zFontName, zString, v16);
  if ( Computer_isEnabled )
  {
    v12 = 0;
    p_ptPrev = &ptQTask[1].ptPrev;
    do
    {
      isDisabledb = v19 * -34.0;
      ptQTaskb = v17 + v17;
      *p_ptPrev = ComputerButtonItem_New(
                    ptParent,
                    v12 + 5,
                    0,
                    0,
                    0,
                    0,
                    0,
                    isDisabledb,
                    ptQTaskb,
                    0,
                    nullptr,
                    (char *)&g_zInitialValue,
                    &ComputerMenu_tComputerMenuResource.tQSpriteObjective_1,
                    &ComputerMenu_tComputerMenuResource.tQSpriteObjective_2,
                    &ComputerMenu_tComputerMenuResource.tQSpriteObjective_2,
                    ComputerObjectives_ButtonItemActivateCB);
      ++v12;
      ++p_ptPrev;
    }
    while ( v12 < 8 );
  }
}

void __cdecl sub_53AF70(struct QTask_s *a1)
{
  struct QTask_s *ptHead; // ecx
  int v2; // edx
  struct QTask_s *v3; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
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
}

void __cdecl sub_53AFE0(struct QTask_s *a1)
{
  Text_Delete((struct StaticTilemap_s *)a1[1].ptNext);
}

// source: j/0/computer/computerobjectives.c:306  [anchor-strings]
void __cdecl ComputerObjectives_GetStatusStrings(
        char *zCurrentObjective,
        char *zStateString,
        int nLength)
{
  int v3; // ebp
  struct QReference_s *ptTail; // eax
  char *v5; // esi
  bool v6; // zf
  char *LocalizedString; // eax
  int i; // [esp+0h] [ebp-Ch]
  int eLocalTeam; // [esp+4h] [ebp-8h]

  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    v3 = 0;
    if ( HumanPlayer_ptQTask )
    {
      ptTail = HumanPlayer_ptQTask[10].tQTaskRefList.ptTail;
      *zStateString = 0;
      eLocalTeam = (int)ptTail;
      *zCurrentObjective = 0;
      i = 0;
      do
      {
        if ( DefineComputerObjective_ptQTask )
        {
          v5 = (char *)&DefineComputerObjective_ptQTask[3] + v3;
          if ( (struct QTask_s *)((char *)DefineComputerObjective_ptQTask + v3) != (struct QTask_s *)-120
            && (char *)&DefineComputerObjective_ptQTask[3].ptNext
             + strlen((char *)&DefineComputerObjective_ptQTask[3] + v3)
             + 1 != (char *)&DefineComputerObjective_ptQTask[3].ptNext + 1 )
          {
            if ( *(struct QTask_s **)((char *)&DefineComputerObjective_ptQTask[8].ptNext + v3) )
            {
              v6 = eLocalTeam == 1;
            }
            else
            {
              if ( !*(_DWORD *)((char *)&DefineComputerObjective_ptQTask[7].eQTaskType + v3) )
              {
                strncat(zStateString, "[ - ] ", nLength);
                if ( (!v3
                   || DefineComputerObjective_GetObjective(i - 1)->isComplete
                   || DefineComputerObjective_GetObjective(i - 1)->isFailed)
                  && (NetManager_eMode == NETMANAGER_MODE_PLAY || NetManager_eMode == NETMANAGER_MODE_SPAWN) )
                {
                  LocalizedString = Config_GetLocalizedString(v5);
                  strncpy(zCurrentObjective, LocalizedString, nLength);
                }
                goto LABEL_20;
              }
              v6 = eLocalTeam == 0;
            }
            if ( v6 )
              strncat(zStateString, "[IGI] ", nLength);
            else
              strncat(zStateString, "[CON] ", nLength);
          }
        }
LABEL_20:
        v3 += 204;
        ++i;
      }
      while ( v3 < 1632 );
    }
  }
}

// source: j/0/computer/computerobjectives.c:400  [anchor-strings]
void __cdecl ComputerObjectives_DrawHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vX; };
    struct { char igi2_o1[4]; float vY; };
    struct { char igi2_o2[24]; char *v38; };
    struct { char igi2_o3[36]; struct QSprite_s *v39; };
    struct { char igi2_o4[56]; int nX; };
    struct { char igi2_o5[56]; int nXa; };
    struct { char igi2_o6[60]; float **vHeight; };
    struct { char igi2_o7[60]; float vHeighta; };
    struct { char igi2_o8[64]; int vWidth; };
    struct { char igi2_o9[64]; float vWidtha; };
    struct { char igi2_o10[68]; int nHeight; };
    struct { char igi2_o11[68]; int v47; };
    struct { char igi2_o12[80]; int v48; };
    struct { char igi2_o13[84]; char *zResourceName; };
    struct { char igi2_o14[88]; char zText[64]; };
    struct { char igi2_o15[152]; char Buffer[256]; };
    char igi2_extent[408];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptNext; // eax
  double v2; // st7
  int v3; // edx
  double v4; // st7
  struct QTask_s *v5; // ebp
  int v6; // edi
  int v7; // esi
  float *v8; // eax
  double v9; // st6
  double v10; // st5
  char *LocalizedStringForLanguage; // eax
  char *v12; // eax
  enum ComputerMenuColor_e v13; // ebp
  struct QTask_s *ptHead; // eax
  struct QTask_s *v15; // ebx
  struct QSprite_s *Font; // eax
  struct QTask_s *ptGameScreenQTask; // ecx
  struct QTask_s *v18; // eax
  struct QTask_s *v19; // eax
  struct QTask_s *v20; // ecx
  struct QTask_s *v21; // esi
  struct QSprite_s *v22; // eax
  int StringWidth; // eax
  int v24; // esi
  char *v25; // edi
  struct QTask_s *v26; // eax
  struct QTask_s *v27; // eax
  struct QSprite_s *v28; // eax
  int v29; // eax
  struct QTask_s *v30; // ecx
  int v31; // edx
  struct QTask_s *v32; // eax
  int v33; // esi
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v35; // edx

  igi2_frame.nHeight = Display_tActiveMode.nHeight;
  igi2_frame.nXa = Display_tActiveMode.nWidth;
  igi2_frame.vHeighta = (float)Display_tActiveMode.nHeight;
  igi2_frame.vWidtha = (float)Display_tActiveMode.nWidth;
  igi2_frame.vY = igi2_frame.vHeighta * 0.0;
  igi2_frame.vX = igi2_frame.vWidtha * 0.0;
  QSprite_RegisterBlankZ(igi2_frame.vX, igi2_frame.vY, igi2_frame.vWidtha, igi2_frame.vHeighta, 0.0, 0.0, 0.0, 0x40040000u, -1, 542.47998046875);
  ptNext = ptQTask[1].ptNext;
  QTilemap_Register(
    (struct QTilemap_s *)ptNext->ptNext,
    *(float *)&ptNext->ptPrev,
    *(float *)&ptNext->tQTaskChildren.ptHead,
    *(float *)&ptNext->tQTaskRefList.ptHead,
    *(float *)&ptNext->tQTaskRefList.ptMiddle,
    *(float *)&ptNext->tQTaskRefList.ptTail,
    *(float *)&ptNext->tQTaskChildren.ptTail,
    *(float *)&ptNext->tQTaskChildren.ptMiddle,
    *(_DWORD *)&ptNext->eQTaskType | 0x40000000,
    (int)ptNext->ptParent);
  v2 = (double)igi2_frame.nXa;
  v3 = 0;
  if ( Computer_isEnabled )
    v4 = v2 * 0.3125;
  else
    v4 = v2 * 0.153125;
  igi2_frame.nX = (__int64)v4;
  v5 = DefineComputerObjective_ptQTask;
  igi2_frame.vWidth = 0;
  igi2_frame.v48 = 0;
  igi2_frame.vHeight = (float **)&ptQTask[1].ptPrev;
  v6 = (__int64)((double)igi2_frame.nHeight * 0.12083333333333333);
  igi2_frame.v47 = v6;
  do
  {
    if ( !v5 )
      goto LABEL_37;
    v7 = (int)&v5[3] + v3;
    igi2_frame.zResourceName = (char *)v7;
    if ( (struct QTask_s *)((char *)v5 + v3) == (struct QTask_s *)-120 || !strlen((char *)&v5[3] + v3) )
      goto LABEL_37;
    if ( Computer_isEnabled )
    {
      v8 = *igi2_frame.vHeight;
      v9 = (double)igi2_frame.nX - 34.0;
      v8[32] = v9;
      v10 = (double)igi2_frame.v47 + 2.0;
      v8[33] = v10;
      v8[25] = v9;
      v8[26] = v10;
    }
    LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                   "OBJECTIVE",
                                   Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                   true);
    sprintf(igi2_frame.Buffer, "%s %d: ", LocalizedStringForLanguage, igi2_frame.vWidth + 1);
    if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
    {
      if ( !HumanPlayer_ptQTask )
        return;
      if ( !*(_DWORD *)(v7 + 196) )
      {
LABEL_20:
        igi2_frame.v38 = Config_GetLocalizedStringForLanguage(
                "INCOMPLETE",
                Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                true);
        sprintf(igi2_frame.zText, (char *const)&stru_6A4CDC.tDebugConsoleLineList.ptMiddle, igi2_frame.v38);
        goto LABEL_21;
      }
      if ( HumanPlayer_ptQTask[10].tQTaskRefList.ptTail != (struct QReference_s *)NetMission_eAttackingTeam )
      {
LABEL_17:
        v12 = Config_GetLocalizedStringForLanguage(
                "FAILED",
                Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                true);
        goto LABEL_18;
      }
    }
    else
    {
      if ( *(_DWORD *)(v7 + 200) )
        goto LABEL_17;
      if ( !*(_DWORD *)(v7 + 196) )
        goto LABEL_20;
    }
    v12 = Config_GetLocalizedStringForLanguage(
            "COMPLETE",
            Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
            true);
LABEL_18:
    sprintf(igi2_frame.zText, (char *const)&stru_6A4CDC.tDebugConsoleLineList.ptMiddle, v12);
LABEL_21:
    if ( *(_DWORD *)(v7 + 200) )
      v13 = COMPUTERMENU_COLOR_DARK_RED;
    else
      v13 = 2 * (*(_DWORD *)(v7 + 196) == 0) + 2;
    ptHead = Game_ptGame->ptGameScreenQTask[1].tQTaskChildren.ptHead;
    if ( ptHead )
      v15 = ptHead->tQTaskChildren.ptHead;
    else
      v15 = nullptr;
    Font = MenuManager_GetFont(v15, (char *)&g_zFontName_1);
    ComputerObjectives_Print(igi2_frame.nX, v6, 522.47998046875, 400, 120, igi2_frame.Buffer, Font, COMPUTERMENU_COLOR_WHITE);
    ptGameScreenQTask = Game_ptGame->ptGameScreenQTask;
    v18 = ptGameScreenQTask[1].tQTaskChildren.ptHead;
    if ( v18 )
      v19 = v18->tQTaskChildren.ptHead;
    else
      v19 = nullptr;
    v20 = ptGameScreenQTask[1].tQTaskChildren.ptHead;
    if ( v20 )
      v21 = v20->tQTaskChildren.ptHead;
    else
      v21 = nullptr;
    igi2_frame.v39 = MenuManager_GetFont(v19, (char *)&g_zFontName_1);
    v22 = MenuManager_GetFont(v21, (char *)&g_zFontName_1);
    StringWidth = Font_GetStringWidth(v22, igi2_frame.Buffer);
    v24 = ComputerObjectives_Print(igi2_frame.nX + StringWidth, v6, 522.47998046875, 400, 120, igi2_frame.zText, igi2_frame.v39, v13);
    v25 = Config_GetLocalizedStringForLanguage(
            igi2_frame.zResourceName,
            Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
            true);
    v26 = Game_ptGame->ptGameScreenQTask[1].tQTaskChildren.ptHead;
    if ( v26 )
      v27 = v26->tQTaskChildren.ptHead;
    else
      v27 = nullptr;
    v28 = MenuManager_GetFont(v27, (char *)&g_zFontName_0.tQTaskChildren.ptMiddle);
    v29 = ComputerObjectives_Print(igi2_frame.nX, v24, 522.47998046875, 400, 120, v25, v28, COMPUTERMENU_COLOR_GREEN);
    v5 = DefineComputerObjective_ptQTask;
    v3 = igi2_frame.v48;
    v6 = v29 + 8;
    igi2_frame.v47 = v29 + 8;
LABEL_37:
    v3 += 204;
    ++igi2_frame.vWidth;
    ++igi2_frame.vHeight;
    igi2_frame.v48 = v3;
  }
  while ( v3 < 1632 );
  v30 = ptQTask->tQTaskChildren.ptHead;
  if ( v30->ptNext && v30 )
  {
    v31 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( v30->ptNext )
        v32 = v30->ptNext->ptNext != nullptr ? v30->ptNext : nullptr;
      else
        v32 = nullptr;
      v33 = Screen_eDrawQTaskEvent;
      QTask_atProtectedQTaskStack[v31].ptQTask = v32;
      pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[v33][v30->eQTaskType].pfHandler;
      v35 = v31 + 1;
      QTask_nProtectedQTaskStackOffset = v35;
      if ( pfHandler )
      {
        pfHandler(v30);
        v35 = QTask_nProtectedQTaskStackOffset;
      }
      v30 = (struct QTask_s *)dword_849C7DC[v35];
      v31 = v35 - 1;
      QTask_nProtectedQTaskStackOffset = v31;
    }
    while ( v30 );
  }
}

// source: j/0/computer/computerobjectives.c:619  [anchor-hash]
void __cdecl ComputerObjectives_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("ComputerObjectives", 76, BaseQTaskType, 0, 0);
  ComputerObjectives_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 0, ComputerObjectives_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, sub_53AF70);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, sub_53AFE0);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, Screen_eDrawQTaskEvent, ComputerObjectives_DrawHandler);
}

// source: j/0/computer/computerobjectives.c:639  [size]
void __cdecl ComputerObjectives_Close()
{
  QTask_DeleteQTaskType(ComputerObjectives_eQTaskType);
}

// source: j/0/computer/computerobjectives.c:653  [size]
struct QTask_s *__cdecl ComputerObjectives_New(struct QTask_s *ptParent)
{
  return QTask_NewFn(ptParent, ComputerObjectives_eQTaskType, nullptr);
}

// source: j/0/computer/computerobjectives.c:680  [anchor-callee]
int __cdecl ComputerObjectives_Print(
        int nX,
        int nY,
        float vZ,
        int nWidth,
        int nHeight,
        char *zText,
        struct QSprite_s *ptQSprite,
        enum ComputerMenuColor_e eComputerMenuColor)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vR; };
    struct { char igi2_o1[4]; float vG; };
    struct { char igi2_o2[20]; unsigned int v41; };
    struct { char igi2_o3[48]; int nPrintX; };
    struct { char igi2_o4[56]; int nLineWidth; };
    struct { char igi2_o5[60]; int isCompleteText; };
    struct { char igi2_o6[64]; float vX; };
    struct { char igi2_o7[68]; int nWordWidth; };
    struct { char igi2_o8[72]; float ptQTilemap; };
    struct { char igi2_o9[76]; char zWord[256]; };
    struct { char igi2_o10[332]; char zLine[256]; };
    char igi2_extent[588];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QSprite_s *v8; // esi
  struct StaticTilemap_s *v10; // ebp
  unsigned int bQGraphicFlags; // edx
  int v12; // ecx
  char v13; // al
  int StringWidth; // ebx
  unsigned int v16; // edx
  char *v17; // edi
  unsigned int v19; // edx
  char *v20; // edi
  struct QTilemap_s *v22; // edx
  unsigned __int8 *anID; // edi
  unsigned int v24; // edx
  char *v25; // edi
  char v26; // cl
  unsigned __int8 v27; // dl
  struct QTilemap_s *v28; // esi
  int v29; // ecx
  char *v30; // eax
  int v31; // edi
  unsigned int v32; // eax
  float v33; // ecx
  float vA; // edx
  struct QTilemap_s *v35; // ebx
  float vB; // eax
  int v37; // esi

  v8 = ptQSprite;
  igi2_frame.isCompleteText = 0;
  igi2_frame.nPrintX = nX;
  igi2_frame.nLineWidth = nWidth;
  igi2_frame.zLine[0] = 0;
  v10 = Text_New(ptQSprite, 0.0, 0.0, (char *)&g_zInitialValue);
  bQGraphicFlags = v10->bQGraphicFlags;
  v10->vZ = vZ;
  v10->bQGraphicFlags = bQGraphicFlags | 0x40000;
  v10->vR = ComputerMenu_atColor[eComputerMenuColor].vX;
  v10->vG = ComputerMenu_atColor[eComputerMenuColor].vY;
  v10->vB = ComputerMenu_atColor[eComputerMenuColor].vZ;
  while ( 2 )
  {
    v12 = 0;
    igi2_frame.zWord[0] = 0;
    while ( 1 )
    {
      v13 = *zText;
      if ( *zText++ == 0 )
        break;
      if ( v13 == 32 )
      {
        igi2_frame.zWord[v12] = 32;
        igi2_frame.zWord[v12 + 1] = 0;
        goto LABEL_9;
      }
      igi2_frame.zWord[v12++] = v13;
    }
    igi2_frame.zWord[v12] = 0;
    igi2_frame.isCompleteText = 1;
LABEL_9:
    StringWidth = Font_GetStringWidth(v8, igi2_frame.zWord);
    igi2_frame.nWordWidth = StringWidth;
    if ( igi2_frame.nLineWidth <= StringWidth )
    {
      igi2_frame.nPrintX = nX;
      nY += v8->atQAnimframe[v8->nQAnimframes].nHeight;
      igi2_frame.zLine[0] = 0;
      v19 = strlen(igi2_frame.zWord) + 1;
      v20 = &igi2_frame.zWord[255];
      while ( *++v20 )
        ;
      qmemcpy(v20, igi2_frame.zWord, v19);
      igi2_frame.nLineWidth = nWidth - StringWidth;
    }
    else
    {
      v16 = strlen(igi2_frame.zWord) + 1;
      v17 = &igi2_frame.zWord[255];
      while ( *++v17 )
        ;
      qmemcpy(v17, igi2_frame.zWord, v16);
      igi2_frame.nLineWidth -= StringWidth;
    }
    v22 = v10->ptQTilemap;
    memset(v10->ptQTilemap->anGraphicWidth, 0, 2 * v10->ptQTilemap->nHeight);
    anID = v22->anID;
    v24 = v22->nHeight * v22->nWidth;
    memset(anID, 0, 4 * (v24 >> 2));
    v25 = (char *)&anID[4 * (v24 >> 2)];
    v26 = v24;
    v27 = igi2_frame.zWord[0];
    memset(v25, 0, v26 & 3);
    v28 = v10->ptQTilemap;
    v29 = (int)v10->ptQTilemap->ptQSprite->ptQTilemap->anID;
    v30 = igi2_frame.zWord;
    if ( v27 )
    {
      v31 = v10->ptQTilemap->anID - (unsigned __int8 *)igi2_frame.zWord;
      do
      {
        v30[v31] = *(_BYTE *)(v27 + v29);
        v27 = *++v30;
      }
      while ( v27 );
    }
    QTilemap_UpdateGraphicWidth(v28, 0);
    v32 = v10->bQGraphicFlags;
    v33 = v10->vZ;
    vA = v10->vA;
    igi2_frame.ptQTilemap = (float)igi2_frame.nPrintX;
    v35 = v10->ptQTilemap;
    v10->vX = igi2_frame.ptQTilemap;
    igi2_frame.v41 = v32 | 0x40000000;
    vB = v10->vB;
    igi2_frame.vX = (float)nY;
    v10->vY = igi2_frame.vX;
    igi2_frame.vG = v10->vG;
    igi2_frame.vR = v10->vR;
    v10->nPri = -1;
    QTilemap_Register(v35, igi2_frame.ptQTilemap, igi2_frame.vX, igi2_frame.vR, igi2_frame.vG, vB, vA, v33, igi2_frame.v41, -1);
    igi2_frame.nPrintX += igi2_frame.nWordWidth;
    if ( !igi2_frame.isCompleteText )
    {
      v8 = ptQSprite;
      continue;
    }
    break;
  }
  v37 = ptQSprite->atQAnimframe[ptQSprite->nQAnimframes].nHeight + nY;
  Text_Delete(v10);
  return v37;
}

// source: j/0/computer/computerobjectives.c:831  [size]
unsigned __int16 __cdecl ComputerObjectives_GetQTaskType()
{
  return ComputerObjectives_eQTaskType;
}
