/* j/0/menusystem/menutext.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/menusystem/menutext.c:145  [size]
void __cdecl MenuText_SetPosHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ((void (__cdecl *)())QTask_aatQTaskFinalEvent[MenuWindow_eSetPosEvent][MenuWindow_eQTaskType].pfHandler)(ptQTask, pxContext);
}

// source: j/0/menusystem/menutext.c:175  [size]
void __cdecl MenuTextSelection_SetPosHandler(struct QTask_s *ptQTask, void *pxContext)
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
      pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[MenuWindow_eSetPosEvent][ptHead->eQTaskType].pfHandler;
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

// source: j/0/menusystem/menutext.c:191  [anchor-mhash]
void __cdecl MenuText_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][MenuWindow_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  LOBYTE(ptQTask[2].tQTaskChildren.ptMiddle) = 0;
  LOBYTE(ptQTask[3].eQTaskType) = 0;
  LOBYTE(ptQTask[5].tQTaskRefList.ptHead) = 0;
  ptQTask[7].ptPrev = nullptr;
  ptQTask[15].tQTaskRefList.ptHead = nullptr;
  ptQTask[15].tQTaskChildren.ptMiddle = (struct QTask_s *)-1;
  ptQTask[1].ptNext = (struct QTask_s *)300;
  ptQTask[1].ptPrev = (struct QTask_s *)230;
  ptQTask[1].tQTaskRefList.ptTail = (struct QReference_s *)1;
  ptQTask[1].ptParent = (struct QTask_s *)1;
  ptQTask[7].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[7].tQTaskChildren.ptTail = nullptr;
  ptQTask[7].tQTaskRefList.ptHead = nullptr;
  ptQTask[9].tQTaskChildren.ptHead = nullptr;
  ptQTask[9].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[9].tQTaskChildren.ptTail = nullptr;
  ptQTask[9].tQTaskRefList.ptHead = nullptr;
  ptQTask[11].tQTaskChildren.ptHead = nullptr;
  ptQTask[11].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[11].tQTaskChildren.ptTail = nullptr;
  ptQTask[11].tQTaskRefList.ptHead = nullptr;
  ptQTask[13].tQTaskChildren.ptHead = nullptr;
  ptQTask[13].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[13].tQTaskChildren.ptTail = nullptr;
  ptQTask[13].tQTaskRefList.ptHead = nullptr;
  ptQTask[15].tQTaskChildren.ptHead = nullptr;
  ptQTask[15].tQTaskRefList.ptTail = nullptr;
  ptQTask[15].ptParent = (struct QTask_s *)1;
  ptQTask[15].tQTaskRefList.ptMiddle = (struct QReference_s *)1;
  *(_DWORD *)&ptQTask[15].eQTaskType = 0;
  ptQTask[15].tQTaskChildren.ptTail = nullptr;
}

// source: j/0/menusystem/menutext.c:238  [anchor-mhash]
void __cdecl MenuText_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptPrev; // eax
  int v2; // ecx
  struct QReference_s *v3; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax

  ptPrev = ptQTask[7].ptPrev;
  if ( ptPrev )
  {
    Text_Delete((struct StaticTilemap_s *)ptPrev);
    ptQTask[7].ptPrev = nullptr;
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
      goto LABEL_11;
  }
  if ( v2 >= 0 )
  {
    pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Level_eRemoveLevelScriptSymbolsEvent][ptQTask->eQTaskType].pfHandler;
    if ( pfHandler )
      pfHandler(ptQTask);
  }
LABEL_11:
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[7].tQTaskChildren.ptMiddle);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[9].tQTaskChildren.ptMiddle);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[11].tQTaskChildren.ptMiddle);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[13].tQTaskChildren.ptMiddle);
}

// source: j/0/menusystem/menutext.c:271  [anchor-strings]
void __cdecl MenuText_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v2; // ebx
  struct QSprite_s *Font; // edi
  struct QTask_s *ptPrev; // eax
  char *LocalizedStringForLanguage; // eax
  struct QTask_s *v6; // eax
  struct QTask_s *ptNext_low; // edx
  struct QTask_s *v8; // edi
  int ptPrev_high; // ecx
  struct QTask_s *ptMiddle; // eax
  float nX; // [esp+0h] [ebp-24h]
  float nY; // [esp+4h] [ebp-20h]
  char *v13; // [esp+18h] [ebp-Ch]
  char *v14; // [esp+1Ch] [ebp-8h]
  __int64 v15; // [esp+1Ch] [ebp-8h]

  v2 = *(struct QTask_s **)&ptQTask[1].eQTaskType;
  ptQTask[1].tQTaskChildren.ptHead = nullptr;
  ptQTask[1].tQTaskChildren.ptMiddle = nullptr;
  if ( v2 )
  {
    Font = MenuManager_GetFont(v2, (char *)&ptQTask[3].eQTaskType);
    ptQTask[15].tQTaskRefList.ptHead = (struct QReference_s *)MenuManager_GetSprite(
                                                                *(struct QTask_s **)&ptQTask[1].eQTaskType,
                                                                (char *)&g_zSpriteName_0);
    ptPrev = ptQTask[7].ptPrev;
    if ( ptPrev )
    {
      Text_Delete((struct StaticTilemap_s *)ptPrev);
      ptQTask[7].ptPrev = nullptr;
    }
    if ( Font )
    {
      v14 = (char *)&ptQTask[1].ptNext[-8] + (Display_tActiveMode.nWidth >> 1);
      v13 = (char *)&ptQTask[1].ptPrev[-6] + (Display_tActiveMode.nHeight >> 1);
      LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                     (char *)&ptQTask[2].tQTaskChildren.ptMiddle,
                                     Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                     true);
      nY = (float)(int)v13;
      nX = (float)(int)v14;
      v6 = (struct QTask_s *)Text_New(Font, nX, nY, LocalizedStringForLanguage);
      ptQTask[7].ptPrev = v6;
      ptNext_low = nullptr;
      v6->ptParent = nullptr;
      v8 = ptQTask[7].ptPrev;
      ptPrev_high = SHIWORD(v8->ptNext->ptPrev);
      if ( ptPrev_high > 0 )
      {
        ptMiddle = v8->ptNext->tQTaskChildren.ptMiddle;
        do
        {
          if ( SLOWORD(ptMiddle->ptNext) > (int)ptNext_low )
            ptNext_low = (struct QTask_s *)SLOWORD(ptMiddle->ptNext);
          ptMiddle = (struct QTask_s *)((char *)ptMiddle + 2);
          --ptPrev_high;
        }
        while ( ptPrev_high );
      }
      ptQTask[1].tQTaskChildren.ptHead = ptNext_low;
      ptQTask[1].tQTaskChildren.ptMiddle = (struct QTask_s *)(SHIWORD(v8->ptNext->ptPrev)
                                                            * *((__int16 *)&v8->ptNext->tQTaskChildren.ptHead->tQTaskChildren.ptHead->tQTaskChildren.ptMiddle
                                                              + 18
                                                              * LOWORD(v8->ptNext->tQTaskChildren.ptHead->tQTaskRefList.ptHead)
                                                              + 1));
    }
  }
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[7].tQTaskChildren.ptMiddle, ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[9].tQTaskChildren.ptMiddle, ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[11].tQTaskChildren.ptMiddle, ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[13].tQTaskChildren.ptMiddle, ptQTask);
  if ( ptQTask[7].tQTaskChildren.ptMiddle )
    LOBYTE(ptQTask[2].ptPrev) = 1;
  if ( ptQTask[9].tQTaskChildren.ptMiddle && ptQTask[9].tQTaskChildren.ptTail->ptNext && ptQTask[9].tQTaskRefList.ptHead )
  {
    v15 = (__int64)Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[9].tQTaskChildren.ptMiddle, ptQTask);
    ptQTask[15].tQTaskRefList.ptTail = (struct QReference_s *)v15;
    LOBYTE(ptQTask[2].ptPrev) = v15;
  }
  if ( ptQTask[11].tQTaskChildren.ptMiddle
    && ptQTask[11].tQTaskChildren.ptTail->ptNext
    && ptQTask[11].tQTaskRefList.ptHead )
  {
    ptQTask[15].ptParent = (struct QTask_s *)(__int64)Level_RunLevelExpression(
                                                        (struct LevelExpression_s *)&ptQTask[11].tQTaskChildren.ptMiddle,
                                                        ptQTask);
  }
  if ( ptQTask[13].tQTaskChildren.ptMiddle
    && ptQTask[13].tQTaskChildren.ptTail->ptNext
    && ptQTask[13].tQTaskRefList.ptHead )
  {
    MenuText_ptActiveMenuText = (struct MenuText_t *)ptQTask;
    Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[13].tQTaskChildren.ptMiddle, ptQTask);
    MenuText_ptActiveMenuText = nullptr;
  }
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][MenuWindow_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
}

// source: j/0/menusystem/menutext.c:362  [size]
void __cdecl MenuText_RunHandler(struct QTask_s *ptQTask)
{
  char *p_tQTaskRefList; // ecx
  int v2; // edx
  __int64 v3; // [esp+10h] [ebp-8h]

  if ( ptQTask[11].tQTaskChildren.ptMiddle
    && ptQTask[11].tQTaskChildren.ptTail->ptNext
    && ptQTask[11].tQTaskRefList.ptHead )
  {
    ptQTask[15].ptParent = (struct QTask_s *)(__int64)Level_RunLevelExpression(
                                                        (struct LevelExpression_s *)&ptQTask[11].tQTaskChildren.ptMiddle,
                                                        ptQTask);
  }
  if ( ptQTask[13].tQTaskChildren.ptMiddle
    && ptQTask[13].tQTaskChildren.ptTail->ptNext
    && ptQTask[13].tQTaskRefList.ptHead )
  {
    MenuText_ptActiveMenuText = (struct MenuText_t *)ptQTask;
    Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[13].tQTaskChildren.ptMiddle, ptQTask);
    MenuText_ptActiveMenuText = nullptr;
  }
  if ( ptQTask[9].tQTaskChildren.ptMiddle && ptQTask[9].tQTaskChildren.ptTail->ptNext && ptQTask[9].tQTaskRefList.ptHead )
  {
    v3 = (__int64)Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[9].tQTaskChildren.ptMiddle, ptQTask);
    ptQTask[15].tQTaskRefList.ptTail = (struct QReference_s *)v3;
    LOBYTE(ptQTask[2].ptPrev) = v3;
  }
  if ( ptQTask[7].tQTaskChildren.ptMiddle && ptQTask[15].tQTaskRefList.ptTail )
  {
    MenuWindow_HitTest(
      (struct MenuWindow_t *)ptQTask,
      (int)ptQTask[1].ptNext,
      (int)ptQTask[1].ptPrev,
      (int)ptQTask[1].tQTaskChildren.ptHead,
      (int)ptQTask[1].tQTaskChildren.ptMiddle,
      nullptr,
      nullptr);
    if ( BYTE1(ptQTask[2].ptNext) )
      MenuManager_SetSelectedWindow(*(struct QTask_s **)&ptQTask[1].eQTaskType, ptQTask);
    if ( HIBYTE(ptQTask[2].ptNext)
      || ptQTask[2].tQTaskChildren.ptHead == (struct QTask_s *)-7
      || *(_DWORD *)&ptQTask[15].eQTaskType )
    {
      *(_DWORD *)&ptQTask[15].eQTaskType = 0;
      if ( ptQTask[7].tQTaskChildren.ptMiddle )
      {
        if ( ptQTask[7].tQTaskChildren.ptTail->ptNext && ptQTask[7].tQTaskRefList.ptHead )
        {
          Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[7].tQTaskChildren.ptMiddle, ptQTask);
          p_tQTaskRefList = (char *)&ptQTask[5].tQTaskRefList;
          if ( !LOBYTE(ptQTask[5].tQTaskRefList.ptHead) )
            p_tQTaskRefList = "menu_sel";
          SoundSys_PlaySimpleSoundFn(p_tQTaskRefList, 0, nullptr);
        }
      }
    }
  }
  v2 = MenuWindow_eQTaskType;
  ptQTask[2].tQTaskChildren.ptHead = nullptr;
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][v2].pfHandler)(ptQTask);
}

// source: j/0/menusystem/menutext.c:449  [anchor-mhash]
void __cdecl MenuTextSelection_RunHandler(struct QTask_s *ptQTask)
{
  unsigned __int16 v1; // dx
  struct QTask_s *FirstChildOfType; // eax
  int v3; // esi
  struct QTask_s *ptHead; // eax
  int v5; // edx
  struct QTask_s *v6; // ecx
  int eQTaskType; // ecx

  v1 = MenuText_eQTaskType;
  FirstChildOfType = QTask_GetFirstChildOfType(ptQTask, MenuText_eQTaskType);
  v3 = -1;
  if ( (Keyboard_tKeyboard.anCurrentKey[2] & 0x80u) != 0 && (Keyboard_tKeyboard.anPreviousKey[2] & 0x80) == 0
    || (Keyboard_tKeyboard.anCurrentKey[79] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[79] & 0x80) == 0 )
  {
    v3 = 0;
  }
  if ( (Keyboard_tKeyboard.anCurrentKey[3] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[3] & 0x80) == 0
    || (Keyboard_tKeyboard.anCurrentKey[80] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[80] & 0x80) == 0 )
  {
    v3 = 1;
  }
  if ( (Keyboard_tKeyboard.anCurrentKey[4] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[4] & 0x80) == 0
    || (Keyboard_tKeyboard.anCurrentKey[81] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[81] & 0x80) == 0 )
  {
    v3 = 2;
  }
  if ( (Keyboard_tKeyboard.anCurrentKey[5] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[5] & 0x80) == 0
    || (Keyboard_tKeyboard.anCurrentKey[75] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[75] & 0x80) == 0 )
  {
    v3 = 3;
  }
  if ( (Keyboard_tKeyboard.anCurrentKey[6] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[6] & 0x80) == 0
    || (Keyboard_tKeyboard.anCurrentKey[76] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[76] & 0x80) == 0 )
  {
    v3 = 4;
  }
  if ( (Keyboard_tKeyboard.anCurrentKey[7] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[7] & 0x80) == 0
    || (Keyboard_tKeyboard.anCurrentKey[77] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[77] & 0x80) == 0 )
  {
    v3 = 5;
  }
  if ( (Keyboard_tKeyboard.anCurrentKey[8] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[8] & 0x80) == 0
    || (Keyboard_tKeyboard.anCurrentKey[71] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[71] & 0x80) == 0 )
  {
    v3 = 6;
  }
  if ( (Keyboard_tKeyboard.anCurrentKey[9] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[9] & 0x80) == 0
    || (Keyboard_tKeyboard.anCurrentKey[72] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[72] & 0x80) == 0 )
  {
    v3 = 7;
  }
  if ( (Keyboard_tKeyboard.anCurrentKey[10] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[10] & 0x80) == 0
    || (Keyboard_tKeyboard.anCurrentKey[73] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[73] & 0x80) == 0 )
  {
    v3 = 8;
  }
  if ( ((Keyboard_tKeyboard.anCurrentKey[11] & 0x80) == 0 || (Keyboard_tKeyboard.anPreviousKey[11] & 0x80) != 0)
    && ((Keyboard_tKeyboard.anCurrentKey[82] & 0x80) == 0 || (Keyboard_tKeyboard.anPreviousKey[82] & 0x80) != 0) )
  {
    if ( v3 <= -1 )
      goto LABEL_59;
  }
  else
  {
    v3 = 9;
  }
  if ( FirstChildOfType )
  {
    while ( --v3 >= 0 )
    {
      FirstChildOfType = QTask_GetNextSiblingOfType(FirstChildOfType, v1);
      if ( !FirstChildOfType )
        goto LABEL_59;
    }
    if ( FirstChildOfType[15].tQTaskRefList.ptTail && FirstChildOfType[15].ptParent )
      *(_DWORD *)&FirstChildOfType[15].eQTaskType = 1;
  }
LABEL_59:
  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v5 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v6 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v6 = nullptr;
      QTask_atProtectedQTaskStack[v5].ptQTask = v6;
      eQTaskType = ptHead->eQTaskType;
      QTask_nProtectedQTaskStackOffset = v5 + 1;
      ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][eQTaskType].pfHandler)(ptHead);
      ptHead = (struct QTask_s *)dword_849C7DC[QTask_nProtectedQTaskStackOffset];
      v5 = --QTask_nProtectedQTaskStackOffset;
    }
    while ( ptHead );
  }
}

// source: j/0/menusystem/menutext.c:510  [anchor-mhash]
void __cdecl MenuText_DrawHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptPrev; // ebx
  int v3; // edi
  double v4; // st7
  BOOL v5; // ebp
  int v6; // edi
  BOOL v7; // eax
  double v8; // st7
  int v9; // eax
  double ptHead; // st7
  double ptMiddle; // st6
  float vY4; // [esp+0h] [ebp-30h]
  float vR1; // [esp+4h] [ebp-2Ch]
  float vG1; // [esp+8h] [ebp-28h]
  float vY0; // [esp+24h] [ebp-Ch]
  float v16; // [esp+28h] [ebp-8h]
  float vX1; // [esp+2Ch] [ebp-4h]
  float ptQTaska = *(float *)&ptQTask; // [esp+34h] [ebp+4h] ARGSLOT
  float ptQTaskb = *(float *)&ptQTask; // [esp+34h] [ebp+4h] ARGSLOT

  ptPrev = ptQTask[7].ptPrev;
  v3 = *(_DWORD *)(*(_DWORD *)&ptQTask[1].eQTaskType + 356);
  v4 = (double)(v3 - 8) * 0.125;
  if ( v4 <= 0.0 )
    ptQTaska = 0.0;
  else
    ptQTaska = v4;
  if ( ptQTask[15].ptParent )
  {
    ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Screen_eDrawQTaskEvent][MenuWindow_eQTaskType].pfHandler)(ptQTask);
    if ( ptPrev )
    {
      v5 = v3 == 16 && BYTE1(ptQTask[2].ptPrev);
      v6 = (int)ptQTask[7].tQTaskChildren.ptHead & 3;
      if ( v5 )
      {
        ptPrev->tQTaskRefList = (*(struct QReferenceList_s *)&MenuText_atTextColour[4]);
        v6 = 4;
      }
      else
      {
        *(float *)&ptPrev->tQTaskRefList.ptHead = MenuText_atTextColour[v6].r;
        *(float *)&ptPrev->tQTaskRefList.ptMiddle = MenuText_atTextColour[v6].g;
        *(float *)&ptPrev->tQTaskRefList.ptTail = MenuText_atTextColour[v6].b;
      }
      v7 = !ptQTask[15].tQTaskRefList.ptTail && ptQTask[15].tQTaskRefList.ptMiddle;
      v8 = ptQTaska;
      if ( v7 | (int)ptQTask[7].tQTaskChildren.ptHead & 0x10 )
        v8 = v8 * 0.5;
      v9 = *(_DWORD *)&ptPrev->eQTaskType;
      *(float *)&ptPrev->tQTaskChildren.ptTail = v8;
      *(_DWORD *)&ptPrev->eQTaskType = v9 | 0x80000;
      *(float *)&ptQTask[7].ptPrev->ptPrev = (double)(int)ptQTask[1].ptNext
                                           - 320.0
                                           + (double)(Display_tActiveMode.nWidth >> 1);
      *(float *)&ptQTask[7].ptPrev->tQTaskChildren.ptHead = (double)(Display_tActiveMode.nHeight >> 1)
                                                          + (double)(int)ptQTask[1].ptPrev
                                                          - 240.0;
      Text_Register((struct StaticTilemap_s *)ptQTask[7].ptPrev);
      if ( v5 )
      {
        ptHead = (double)(int)ptQTask[1].tQTaskChildren.ptHead;
        ptQTaskb = (double)((unsigned int)&ptQTask[1].ptNext[-8] + (Display_tActiveMode.nWidth >> 1))
                 - ptHead * 0.4000000059604645;
        ptMiddle = (double)(int)ptQTask[1].tQTaskChildren.ptMiddle;
        vY0 = (double)((unsigned int)&ptQTask[1].ptPrev[-6] + (Display_tActiveMode.nHeight >> 1)) - ptMiddle * 0.20000000298023224;
        vX1 = ptHead * 1.7999999523162842 + ptQTaskb;
        v16 = ptMiddle * 1.399999976158142 + vY0;
        vG1 = MenuText_atTextColour[v6].b * 0.20000000298023224;
        vR1 = MenuText_atTextColour[v6].g * 0.20000000298023224;
        vY4 = MenuText_atTextColour[v6].r * 0.20000000298023224;
        QSprite_Register4(
          (struct QSprite_s *)ptQTask[15].tQTaskRefList.ptHead,
          ptQTaskb,
          vY0,
          vX1,
          vY0,
          ptQTaskb,
          v16,
          vX1,
          v16,
          vY4,
          vR1,
          vG1,
          0,
          8u,
          0);
      }
    }
  }
}

// source: j/0/menusystem/menutext.c:611  [anchor-mhash]
void __cdecl MenuTextSelection_DrawHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // eax
  int v2; // edx
  struct QTask_s *v3; // ecx
  int eQTaskType; // ecx

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
      eQTaskType = ptHead->eQTaskType;
      QTask_nProtectedQTaskStackOffset = v2 + 1;
      ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Screen_eDrawQTaskEvent][eQTaskType].pfHandler)(ptHead);
      ptHead = (struct QTask_s *)dword_849C7DC[QTask_nProtectedQTaskStackOffset];
      v2 = --QTask_nProtectedQTaskStackOffset;
    }
    while ( ptHead );
  }
}

// source: j/0/menusystem/menutext.c:628  [size]
void __cdecl MenuText_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = MenuText_ptParameterList;
}

// source: j/0/menusystem/menutext.c:644  [size]
void __cdecl MenuTextSelection_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = MenuTextSelection_ptParameterList;
}

// source: j/0/menusystem/menutext.c:660  [size]
void __cdecl MenuText_RegisterScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( !ptQTask[15].tQTaskChildren.ptTail )
  {
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.nID", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int,
      &ptQTask[15].tQTaskChildren.ptMiddle,
      4,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    ptQTask[15].tQTaskChildren.ptTail = (struct QTask_s *)1;
  }
}

// source: j/0/menusystem/menutext.c:690  [size]
void __cdecl MenuText_RemoveScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( ptQTask[15].tQTaskChildren.ptTail )
  {
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.nID", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    ptQTask[15].tQTaskChildren.ptTail = nullptr;
  }
}

// source: j/0/menusystem/menutext.c:720  [size]
void __cdecl MenuText_ChangeLanguageHandler(struct QTask_s *ptQTask)
{
  int v1; // eax
  char *LocalizedStringForLanguage; // eax
  struct QTask_s *ptPrev; // ebp
  int ptPrev_high; // ecx
  struct QTask_s *ptNext_low; // edx
  struct QTask_s *ptMiddle; // eax
  struct QTask_s *ptHead; // ecx
  int v8; // edx
  struct QTask_s *v9; // eax
  int v10; // esi
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v12; // edx

  v1 = *(_DWORD *)&ptQTask[1].eQTaskType;
  ptQTask[1].tQTaskChildren.ptHead = nullptr;
  ptQTask[1].tQTaskChildren.ptMiddle = nullptr;
  if ( v1 && ptQTask[7].ptPrev )
  {
    LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                   (char *)&ptQTask[2].tQTaskChildren.ptMiddle,
                                   *(enum GameLanguage_e *)(v1 + 10044),
                                   true);
    Text_SetString((struct StaticTilemap_s *)ptQTask[7].ptPrev, LocalizedStringForLanguage);
    ptPrev = ptQTask[7].ptPrev;
    ptPrev_high = SHIWORD(ptPrev->ptNext->ptPrev);
    ptNext_low = nullptr;
    if ( ptPrev_high > 0 )
    {
      ptMiddle = ptPrev->ptNext->tQTaskChildren.ptMiddle;
      do
      {
        if ( SLOWORD(ptMiddle->ptNext) > (int)ptNext_low )
          ptNext_low = (struct QTask_s *)SLOWORD(ptMiddle->ptNext);
        ptMiddle = (struct QTask_s *)((char *)ptMiddle + 2);
        --ptPrev_high;
      }
      while ( ptPrev_high );
    }
    ptQTask[1].tQTaskChildren.ptHead = ptNext_low;
    ptQTask[1].tQTaskChildren.ptMiddle = (struct QTask_s *)(SHIWORD(ptPrev->ptNext->ptPrev)
                                                          * *((__int16 *)&ptPrev->ptNext->tQTaskChildren.ptHead->tQTaskChildren.ptHead->tQTaskChildren.ptMiddle
                                                            + 18
                                                            * LOWORD(ptPrev->ptNext->tQTaskChildren.ptHead->tQTaskRefList.ptHead)
                                                            + 1));
  }
  if ( ptQTask[13].tQTaskChildren.ptMiddle
    && ptQTask[13].tQTaskChildren.ptTail->ptNext
    && ptQTask[13].tQTaskRefList.ptHead )
  {
    MenuText_ptActiveMenuText = (struct MenuText_t *)ptQTask;
    Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[13].tQTaskChildren.ptMiddle, ptQTask);
    MenuText_ptActiveMenuText = nullptr;
  }
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
      v10 = MenuWindow_eChangeLanguageEvent;
      QTask_atProtectedQTaskStack[v8].ptQTask = v9;
      pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[v10][ptHead->eQTaskType].pfHandler;
      v12 = v8 + 1;
      QTask_nProtectedQTaskStackOffset = v12;
      if ( pfHandler )
      {
        pfHandler(ptHead);
        v12 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v12];
      v8 = v12 - 1;
      QTask_nProtectedQTaskStackOffset = v8;
    }
    while ( ptHead );
  }
}

// source: j/0/menusystem/menutext.c:763  [size]
void __cdecl MenuTextSelection_ChangeLanguageHandler(struct QTask_s *ptQTask)
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
      v4 = MenuWindow_eChangeLanguageEvent;
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

// source: j/0/menusystem/menutext.c:785  [anchor-callee]
char *__cdecl MenuText_SetText(int nID, char *zText)
{
  struct MenuText_t *v2; // edi
  struct StaticTilemap_s *ptQText; // ebx
  int nHeight; // ecx
  int v5; // edx
  __int16 *anGraphicWidth; // eax

  v2 = MenuText_ptActiveMenuText;
  if ( MenuText_ptActiveMenuText )
  {
    Text_SetString(MenuText_ptActiveMenuText->ptQText, zText);
    ptQText = v2->ptQText;
    v2->nID = nID;
    nHeight = ptQText->ptQTilemap->nHeight;
    v5 = 0;
    if ( nHeight > 0 )
    {
      anGraphicWidth = ptQText->ptQTilemap->anGraphicWidth;
      do
      {
        if ( *anGraphicWidth > v5 )
          v5 = *anGraphicWidth;
        ++anGraphicWidth;
        --nHeight;
      }
      while ( nHeight );
    }
    v2->tMenuWindow.nWidth = v5;
    zText = (char *)ptQText->ptQTilemap->nHeight;
    v2->tMenuWindow.nHeight = (_DWORD)zText
                            * ptQText->ptQTilemap->ptQSprite->atQAnimframe[ptQText->ptQTilemap->ptQSprite->nQAnimframes].nHeight;
  }
  return zText;
}

// source: j/0/menusystem/menutext.c:809  [size]
unsigned __int16 __cdecl MenuText_GetQTaskType()
{
  return MenuText_eQTaskType;
}

// source: j/0/menusystem/menutext.c:824  [size]
unsigned __int16 __cdecl MenuTextSelection_GetQTaskType()
{
  return MenuTextSelection_eQTaskType;
}

// source: j/0/menusystem/menutext.c:839  [anchor-hash]
void __cdecl MenuText_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // ax
  __int16 v2; // bx
  unsigned __int16 v3; // si
  unsigned __int16 v4; // di
  int v5; // ebx
  __int16 v6; // bp
  struct ParameterList_s *v7; // eax
  int v8; // edx
  struct ParameterList_s *v9; // eax

  MenuText_eQTaskType = QTask_NewQTaskType("MenuText", 640, MenuWindow_eQTaskType, 0, 0);
  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("MenuTextSelection", 40, BaseQTaskType, 0, 0);
  v2 = Level_eAllowSaveQTaskEvent;
  v3 = MenuText_eQTaskType;
  v4 = v1;
  MenuTextSelection_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(
    MenuText_eQTaskType,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v4, v2, (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v3, 1, MenuText_RunHandler);
  v5 = Screen_eDrawQTaskEvent;
  QTask_LinkQTaskEventHandlerNoContextFn(v3, Screen_eDrawQTaskEvent, MenuText_DrawHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v3, 2, MenuText_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v3, 0, MenuText_CreateHandler);
  v6 = ParameterList_eGetParameterListQTaskEvent;
  QTask_LinkQTaskEventHandlerFn(
    v3,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))MenuText_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v3, ParameterList_eUpdateInternalDataQTaskEvent, MenuText_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v3, MenuWindow_eChangeLanguageEvent, MenuText_ChangeLanguageHandler);
  QTask_LinkQTaskEventHandlerFn(
    v3,
    MenuWindow_eSetPosEvent,
    (void (__cdecl *)(struct QTask_s *, void *))MenuText_SetPosHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v4, 1, MenuTextSelection_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v4, v5, MenuTextSelection_DrawHandler);
  QTask_LinkQTaskEventHandlerFn(
    v4,
    v6,
    (void (__cdecl *)(struct QTask_s *, void *))MenuTextSelection_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v4, MenuWindow_eChangeLanguageEvent, MenuTextSelection_ChangeLanguageHandler);
  QTask_LinkQTaskEventHandlerFn(v4, MenuWindow_eSetPosEvent, MenuTextSelection_SetPosHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v3,
    Level_eRegisterLevelScriptSymbolsEvent,
    MenuText_RegisterScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v3, Level_eRemoveLevelScriptSymbolsEvent, MenuText_RemoveScriptSymbolsHandler);
  v7 = (struct ParameterList_s *)Mem_AllocFn(212, 4);
  v8 = Level_eParameterTypeString32;
  v7->ptParameterListItem = (struct ParameterListItem_s *)&v7[1];
  v7->nParameters = 0;
  v7->nMaxParameters = 10;
  MenuText_ptParameterList = v7;
  ParameterList_AddParameter(v7, 0x5Cu, v8, "Text Resource", 7u, nullptr);
  ParameterList_AddParameter(
    MenuText_ptParameterList,
    0x9Cu,
    Level_eParameterTypeString32,
    "Font Resource",
    7u,
    nullptr);
  ParameterList_AddParameter(MenuText_ptParameterList, 0x120u, Level_eParameterTypeInt32, "ColourIndex", 7u, nullptr);
  ParameterList_AddParameter(MenuText_ptParameterList, 0x44u, Level_eParameterTypeInt32, "AlignmentMode", 7u, nullptr);
  ParameterList_AddParameter(
    MenuText_ptParameterList,
    0x174u,
    Level_eParameterTypeVarString,
    "isEnabled Expression",
    7u,
    nullptr);
  ParameterList_AddParameter(
    MenuText_ptParameterList,
    0x1C4u,
    Level_eParameterTypeVarString,
    "isVisible Expression",
    7u,
    nullptr);
  ParameterList_AddParameter(
    MenuText_ptParameterList,
    0x124u,
    Level_eParameterTypeVarString,
    "On Click Script",
    7u,
    nullptr);
  ParameterList_AddParameter(
    MenuText_ptParameterList,
    0xDCu,
    Level_eParameterTypeString32,
    "Click Sound Resource",
    7u,
    nullptr);
  ParameterList_AddParameter(
    MenuText_ptParameterList,
    0x270u,
    Level_eParameterTypebool8,
    "Is Item Dimmed When Disabled",
    7u,
    nullptr);
  ParameterList_AddParameter(
    MenuText_ptParameterList,
    0x214u,
    Level_eParameterTypeVarString,
    "Collect text Expression",
    7u,
    nullptr);
  v9 = (struct ParameterList_s *)Mem_AllocFn(32, 4);
  v9->nParameters = 0;
  v9->nMaxParameters = 1;
  v9->ptParameterListItem = (struct ParameterListItem_s *)&v9[1];
  MenuTextSelection_ptParameterList = v9;
  Symbol_Register(
    "TEXT_BLACK",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    nullptr,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "TEXT_WHITE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)1,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "TEXT_GREEN",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)2,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "TEXT_ORANGE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)3,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}

// source: j/0/menusystem/menutext.c:904  [anchor-hash]
void __cdecl MenuText_Close()
{
  int v0; // esi
  int v1; // esi

  if ( MenuText_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&MenuText_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  if ( MenuTextSelection_ptParameterList )
  {
    v1 = *(_DWORD *)((unsigned int)&MenuTextSelection_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
  Symbol_Remove("TEXT_BLACK");
  Symbol_Remove("TEXT_WHITE");
  Symbol_Remove("TEXT_GREEN");
  Symbol_Remove("TEXT_ORANGE");
  QTask_DeleteQTaskType(MenuText_eQTaskType);
  QTask_DeleteQTaskType(MenuTextSelection_eQTaskType);
  MenuText_eQTaskType = 512;
  MenuTextSelection_eQTaskType = 512;
}
