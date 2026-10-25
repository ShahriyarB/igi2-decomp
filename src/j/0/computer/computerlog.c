/* j/0/computer/computerlog.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/computer/computerlog.c:104  [anchor-mhash]
void __cdecl ComputerLog_ButtonItemActivateCB__computerlog(
        struct MenuItem_s *ptMenuItem,
        struct MenuItemActivateContext_s *ptMenuItemActivateContext)
{
  struct ComputerLog_t *v2; // edi
  char v3; // al
  signed int v4; // eax
  int nDisplayLog; // eax

  v2 = ComputerLog_ptComputerLog;
  if ( ptMenuItem->isActivated && !ptMenuItem->isActive )
    SoundSys_PlaySimpleSoundDefFn("mapcomp_05", 1u, nullptr);
  if ( ptMenuItem->eMenuItem == ptMenuItemActivateContext->eMenuItem )
  {
    v3 = (int)ComputerMenu_ptComputerMenuQTask[1].tQTaskChildren.ptTail & 0x10;
    BYTE1(ptMenuItem[1].tClientRect.vY) = LOBYTE(ptMenuItem[1].tClientRect.vY);
    LOBYTE(ptMenuItem[1].tClientRect.vY) = v3;
    if ( v3 )
    {
      SoundSys_PlaySimpleSoundDefFn("mapcomp_01", 1u, nullptr);
      if ( ptMenuItem->eMenuItem == 5 )
      {
        if ( !BYTE1(ptMenuItem[1].tClientRect.vY) )
        {
          nDisplayLog = v2->nDisplayLog;
          if ( nDisplayLog > 0 )
            v2->nDisplayLog = nDisplayLog - 1;
        }
      }
      else if ( ptMenuItem->eMenuItem == 6 && !BYTE1(ptMenuItem[1].tClientRect.vY) )
      {
        v4 = v2->nDisplayLog;
        if ( v4 < (signed int)(ComputerLog_ptQVector->tPrivate.nElements - 15) )
          v2->nDisplayLog = v4 + 1;
      }
    }
  }
}

// source: j/0/computer/computerlog.c:168  [anchor-strings]
void __cdecl ComputerLog_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v3; // ebp
  struct QTask_s *ScreenMenuItems; // eax
  double v5; // st7
  enum GameLanguage_e eLanguage; // ebx
  double v7; // st7
  struct QTask_s *v8; // esi
  struct QTask_s *ptGameScreenQTask; // ecx
  struct QTask_s *ptHead; // eax
  struct QTask_s *v11; // ecx
  struct QSprite_s *Font; // eax
  struct QSprite_s *v13; // eax
  float vY; // [esp+0h] [ebp-44h]
  float v15; // [esp+14h] [ebp-30h]
  float zString; // [esp+18h] [ebp-2Ch]
  char *LocalizedStringForLanguage; // [esp+1Ch] [ebp-28h]
  float v18; // [esp+30h] [ebp-14h]
  float v19; // [esp+30h] [ebp-14h]
  struct QTask_s *nHeight; // [esp+34h] [ebp-10h]
  struct QTask_s *v21; // [esp+34h] [ebp-10h]
  int nDisplayHeighta; // [esp+38h] [ebp-Ch]
  int nDisplayHeight; // [esp+38h] [ebp-Ch]
  char *vArrowYPos; // [esp+3Ch] [ebp-8h]
  float vArrowXPos; // [esp+40h] [ebp-4h]
  float ptQTaska = *(float *)&ptQTask; // [esp+48h] [ebp+4h] ARGSLOT

  v3 = nullptr;
  nHeight = (struct QTask_s *)Display_tActiveMode.nHeight;
  nDisplayHeighta = Display_tActiveMode.nWidth;
  ComputerLog_ptComputerLog = (struct ComputerLog_t *)ptQTask;
  ScreenMenuItems = ComputerMenu_CreateScreenMenuItems(nullptr, nullptr, ptQTask, COMPUTERMENU_LOG);
  v5 = (double)nDisplayHeighta;
  v18 = v5;
  eLanguage = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage;
  vArrowXPos = v5 * 0.14687499403953552;
  v7 = (double)(int)nHeight;
  v8 = ScreenMenuItems;
  *(float *)&nDisplayHeight = v7 * 0.14166666567325592;
  vArrowYPos = Config_GetLocalizedStringForLanguage(
                 (char *)&g_zFontName_1.tQTaskChildren.ptMiddle,
                 eLanguage,
                 true);
  ptGameScreenQTask = Game_ptGame->ptGameScreenQTask;
  ptHead = ptGameScreenQTask[1].tQTaskChildren.ptHead;
  if ( ptHead )
    v21 = ptHead->tQTaskChildren.ptHead;
  else
    v21 = nullptr;
  v11 = ptGameScreenQTask[1].tQTaskChildren.ptHead;
  if ( v11 )
    v3 = v11->tQTaskChildren.ptHead;
  LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                 (char *)&g_zFontName_1.tQTaskChildren.ptMiddle,
                                 eLanguage,
                                 true);
  ptQTaska = v7;
  zString = ptQTaska * 0.078125;
  v19 = v18 * 0.5;
  Font = MenuManager_GetFont(v21, (char *)&g_zFontName_1);
  v15 = v19 - (double)Font_GetStringWidth(Font, vArrowYPos);
  v13 = MenuManager_GetFont(v3, (char *)&g_zFontName_1);
  ptQTask[1].ptPrev = (struct QTask_s *)Text_New(v13, v15, zString, LocalizedStringForLanguage);
  ComputerButtonItem_New(
    v8,
    5,
    0,
    0,
    0,
    0,
    0,
    vArrowXPos,
    *(float *)&nDisplayHeight,
    0,
    nullptr,
    (char *)&g_zInitialValue,
    &ComputerMenu_tComputerMenuResource.tQSpriteArrowUp_1,
    &ComputerMenu_tComputerMenuResource.tQSpriteArrowUp_2,
    &ComputerMenu_tComputerMenuResource.tQSpriteArrowUp_3,
    ComputerLog_ButtonItemActivateCB__computerlog);
  vY = *(float *)&nDisplayHeight + 36.0;
  ComputerButtonItem_New(
    v8,
    6,
    0,
    0,
    0,
    0,
    0,
    vArrowXPos,
    vY,
    0,
    nullptr,
    (char *)&g_zInitialValue,
    &ComputerMenu_tComputerMenuResource.tQSpriteArrowDown_1,
    &ComputerMenu_tComputerMenuResource.tQSpriteArrowDown_2,
    &ComputerMenu_tComputerMenuResource.tQSpriteArrowDown_3,
    ComputerLog_ButtonItemActivateCB__computerlog);
}

// source: j/0/computer/computerlog.c:249  [size]
void __cdecl ComputerLog_RunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // ecx
  int v2; // edx
  struct QTask_s *v3; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v5; // edx

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

// source: j/0/computer/computerlog.c:266  [size]
void __cdecl ComputerLog_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptPrev; // eax

  ptPrev = ptQTask[1].ptPrev;
  ComputerLog_ptComputerLog = nullptr;
  Text_Delete((struct StaticTilemap_s *)ptPrev);
}

// source: j/0/computer/computerlog.c:285  [anchor-caller]
void __cdecl ComputerLog_DrawHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptPrev; // eax
  int v2; // esi
  int i; // edi
  struct QTask_s *ptHead; // eax
  struct QTask_s *v5; // ebx
  struct QSprite_s *Font; // eax
  int v7; // edi
  struct QTask_s *v8; // ecx
  int v9; // edx
  struct QTask_s *v10; // eax
  int v11; // esi
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v13; // edx
  float vX1; // [esp+0h] [ebp-68h]
  float vX2; // [esp+Ch] [ebp-5Ch]
  float vX; // [esp+18h] [ebp-50h]
  float vY; // [esp+1Ch] [ebp-4Ch]
  float vHeight; // [esp+50h] [ebp-18h]
  float vWidth; // [esp+54h] [ebp-14h]
  int nDisplayWidtha; // [esp+58h] [ebp-10h]
  __int64 nDisplayWidth; // [esp+58h] [ebp-10h]
  int nDisplayHeight; // [esp+60h] [ebp-8h]
  float nDisplayHeighta; // [esp+60h] [ebp-8h]

  nDisplayHeight = Display_tActiveMode.nHeight;
  nDisplayWidtha = Display_tActiveMode.nWidth;
  vHeight = (float)Display_tActiveMode.nHeight;
  vWidth = (float)Display_tActiveMode.nWidth;
  vY = vHeight * 0.0;
  vX = vWidth * 0.0;
  QSprite_RegisterBlankZ(vX, vY, vWidth, vHeight, 0.0, 0.0, 0.0, 0x40040000u, -1, 542.47998046875);
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
  v2 = 0;
  nDisplayWidth = (__int64)((double)nDisplayWidtha * 0.228125);
  for ( i = (__int64)((double)nDisplayHeight * 0.12083333333333333);
        v2 < (signed int)ComputerLog_ptQVector->tPrivate.nElements;
        ++v2 )
  {
    if ( v2 >= 15 )
      break;
    ptHead = Game_ptGame->ptGameScreenQTask[1].tQTaskChildren.ptHead;
    v5 = ptHead ? ptHead->tQTaskChildren.ptHead : nullptr;
    Font = MenuManager_GetFont(v5, (char *)&g_zFontName_0);
    v7 = ComputerObjectives_Print(
           nDisplayWidth,
           i,
           522.47998046875,
           400,
           120,
           (char *)ComputerLog_ptQVector->tPrivate.papxElement[ComputerLog_ptQVector->tPrivate.nElements
                                                                   - (unsigned int)ptQTask[1].ptNext
                                                                   - v2
                                                                   - 1],
           Font,
           COMPUTERMENU_COLOR_GREEN)
       + 2;
    nDisplayHeighta = (float)v7;
    vX2 = (float)(nDisplayWidth + 100);
    vX1 = (float)(int)nDisplayWidth;
    QSprite_RegisterLine(
      vX1,
      nDisplayHeighta,
      522.47998046875,
      vX2,
      nDisplayHeighta,
      522.47998046875,
      48.0,
      96.0,
      48.0,
      0.0,
      16.0,
      0.0,
      0.0,
      1.0,
      0x40040000u,
      -1);
    i = v7 + 2;
  }
  v8 = ptQTask->tQTaskChildren.ptHead;
  if ( v8->ptNext && v8 )
  {
    v9 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( v8->ptNext )
        v10 = v8->ptNext->ptNext != nullptr ? v8->ptNext : nullptr;
      else
        v10 = nullptr;
      v11 = Screen_eDrawQTaskEvent;
      QTask_atProtectedQTaskStack[v9].ptQTask = v10;
      pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[v11][v8->eQTaskType].pfHandler;
      v13 = v9 + 1;
      QTask_nProtectedQTaskStackOffset = v13;
      if ( pfHandler )
      {
        pfHandler(v8);
        v13 = QTask_nProtectedQTaskStackOffset;
      }
      v8 = (struct QTask_s *)dword_849C7DC[v13];
      v9 = v13 - 1;
      QTask_nProtectedQTaskStackOffset = v9;
    }
    while ( v8 );
  }
}

// source: j/0/computer/computerlog.c:382  [anchor-hash]
void __cdecl ComputerLog_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si
  void **v2; // esi
  struct QVector_s *v3; // eax

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("ComputerLog", 48, BaseQTaskType, 0, 0);
  ComputerLog_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 0, ComputerLog_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, ComputerLog_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, ComputerLog_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, Screen_eDrawQTaskEvent, ComputerLog_DrawHandler);
  v2 = (void **)Mem_AllocFn(512, 4);
  v3 = (struct QVector_s *)Mem_AllocFn(24, 4);
  v3->tPrivate.papxElement = v2;
  v3->tPrivate.nArraySize = 128;
  v3->tPrivate.nReallocSize = 32;
  v3->tPrivate.nElements = 0;
  v3->tPrivate.isPrivateMem = false;
  v3->tPrivate.isStrictOrder = true;
  ComputerLog_ptQVector = v3;
}

// source: j/0/computer/computerlog.c:404  [anchor-caller]
void __cdecl ComputerLog_Close()
{
  ComputerLog_ClearLog();
  QVector_Delete(ComputerLog_ptQVector);
  QTask_DeleteQTaskType(ComputerLog_eQTaskType);
}

// source: j/0/computer/computerlog.c:421  [size]
struct QTask_s *__cdecl ComputerLog_New(struct QTask_s *ptParent)
{
  return QTask_NewFn(ptParent, ComputerLog_eQTaskType, nullptr);
}

// source: j/0/computer/computerlog.c:441  [anchor-hash]
void __cdecl ComputerLog_ClearLog()
{
  struct QVector_s *v0; // ecx
  unsigned int i; // ebx
  void *v2; // eax
  int v3; // esi

  v0 = ComputerLog_ptQVector;
  for ( i = 0; i < v0->tPrivate.nElements; ++i )
  {
    v2 = v0->tPrivate.papxElement[i];
    if ( v2 )
    {
      v3 = *(_DWORD *)(((int)v2 - 4) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v3);
      memset(*(void **)(v3 + 8), 0xCDu, *(_DWORD *)(v3 + 16));
      free((void *)v3);
      v0 = ComputerLog_ptQVector;
    }
  }
  v0->tPrivate.nElements = 0;
}

// source: j/0/computer/computerlog.c:465  [anchor-mhash]
void __cdecl ComputerLog_RegisterLog(char *zLogMessage)
{
  char *v1; // eax

  v1 = (char *)Mem_AllocFn(strlen(zLogMessage) + 1, 4);
  strcpy(v1, zLogMessage);
  QVector_AddElement(ComputerLog_ptQVector, v1);
}
