/* j/0/menusystem/listbox.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/menusystem/listbox.c:127  [anchor-hash]
void __cdecl ListBox_DeleteEntries(struct ListBox_t *ptListBox)
{
  struct ListBoxItem_t *atListBoxItem; // eax
  int v2; // ecx

  atListBoxItem = ptListBox->atListBoxItem;
  v2 = 128;
  do
  {
    atListBoxItem->zItem[0] = 0;
    atListBoxItem->nItemID = 0;
    ++atListBoxItem;
    --v2;
  }
  while ( v2 );
  *(_DWORD *)&ptListBox[1].atListBoxItem[61].zItem[120] = 0;
  *(_DWORD *)&ptListBox[1].atListBoxItem[61].zItem[124] = 0;
  *(_DWORD *)&ptListBox[1].atListBoxItem[61].zItem[128] = 0;
}

// source: j/0/menusystem/listbox.c:156  [anchor-mhash]
void __cdecl ListBox_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  unsigned __int16 v2; // ax
  struct QReference_s *v3; // eax

  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][MenuWindow_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  v2 = MenuButton_eQTaskType;
  LOBYTE(ptQTask[2].tQTaskChildren.ptMiddle) = 0;
  LOBYTE(ptQTask[3].eQTaskType) = 0;
  ptQTask[838].ptPrev = (struct QTask_s *)100;
  ptQTask[5].tQTaskRefList.ptHead = (struct QReference_s *)QTask_NewFn(nullptr, v2, nullptr);
  v3 = (struct QReference_s *)QTask_NewFn(nullptr, MenuButton_eQTaskType, nullptr);
  ptQTask[5].tQTaskRefList.ptMiddle = v3;
  v3[6].ptNext = nullptr;
  ptQTask[5].tQTaskRefList.ptHead[6].ptNext = nullptr;
  ptQTask[5].tQTaskRefList.ptMiddle[5].pxObject = nullptr;
  ptQTask[5].tQTaskRefList.ptHead[5].pxObject = nullptr;
  ptQTask[837].ptParent = nullptr;
  ListBox_DeleteEntries((struct ListBox_t *)ptQTask);
  ptQTask[840].tQTaskChildren.ptTail = nullptr;
  ptQTask[840].tQTaskRefList.ptHead = nullptr;
  ptQTask[840].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[842].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[842].tQTaskChildren.ptTail = nullptr;
  ptQTask[842].tQTaskRefList.ptHead = nullptr;
  ptQTask[842].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[844].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[844].tQTaskChildren.ptTail = nullptr;
  ptQTask[844].tQTaskRefList.ptHead = nullptr;
  ptQTask[844].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[846].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[846].tQTaskChildren.ptTail = nullptr;
  ptQTask[846].tQTaskRefList.ptHead = nullptr;
  ptQTask[846].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[848].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[838].tQTaskChildren.ptTail = nullptr;
  ptQTask[838].tQTaskRefList.ptHead = nullptr;
  ptQTask[838].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[840].tQTaskChildren.ptMiddle = nullptr;
  LOBYTE(ptQTask[838].tQTaskChildren.ptHead) = 0;
  ptQTask[838].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[1].tQTaskRefList.ptTail = (struct QReference_s *)1;
  ptQTask[1].ptParent = (struct QTask_s *)1;
  BYTE1(ptQTask[838].tQTaskChildren.ptHead) = 1;
}

// source: j/0/menusystem/listbox.c:205  [anchor-mhash]
void __cdecl ListBox_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptMiddle; // eax

  ptMiddle = ptQTask[838].tQTaskChildren.ptMiddle;
  if ( ptMiddle )
  {
    Text_Delete((struct StaticTilemap_s *)ptMiddle);
    ptQTask[838].tQTaskChildren.ptMiddle = nullptr;
  }
  ListBox_DeleteEntries((struct ListBox_t *)ptQTask);
  QTask_Delete((struct QTask_s *)ptQTask[5].tQTaskRefList.ptHead);
  QTask_Delete((struct QTask_s *)ptQTask[5].tQTaskRefList.ptMiddle);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[840].tQTaskChildren.ptTail);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[842].tQTaskChildren.ptTail);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[844].tQTaskChildren.ptTail);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[846].tQTaskChildren.ptTail);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[838].tQTaskChildren.ptTail);
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Level_eRemoveLevelScriptSymbolsEvent][ptQTask->eQTaskType].pfHandler)(ptQTask);
}

// source: j/0/menusystem/listbox.c:244  [anchor-strings]
void __cdecl ListBox_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { char *p_eQTaskType; };
    struct { char igi2_o1[20]; char zResourceName[64]; };
    char igi2_extent[84];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v3; // ebx
  struct QReference_s *ptHead; // ebp
  struct QSprite_s *Font; // edi
  struct QTask_s *ptMiddle; // eax
  struct QTask_s *v7; // eax
  struct QTask_s *v8; // edx
  struct QTask_s *ptPrev; // eax
  int v10; // ecx
  int v11; // eax
  struct QTask_s *ptQTaska = *(struct QTask_s * *)&ptQTask; // [esp+54h] [ebp+4h] ARGSLOT

  v3 = *(struct QTask_s **)&ptQTask[1].eQTaskType;
  ptHead = ptQTask[5].tQTaskRefList.ptHead;
  igi2_frame.p_eQTaskType = (char *)&ptQTask[3].eQTaskType;
  ptQTaska = (struct QTask_s *)ptQTask[5].tQTaskRefList.ptMiddle;
  Font = MenuManager_GetFont(v3, igi2_frame.p_eQTaskType);
  ptMiddle = ptQTask[838].tQTaskChildren.ptMiddle;
  if ( ptMiddle )
  {
    Text_Delete((struct StaticTilemap_s *)ptMiddle);
    ptQTask[838].tQTaskChildren.ptMiddle = nullptr;
  }
  if ( Font )
  {
    v7 = (struct QTask_s *)Text_New(Font, 0.0, 0.0, (char *)&g_zInitialValue);
    ptQTask[838].tQTaskChildren.ptMiddle = v7;
    v7->ptParent = nullptr;
  }
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[840].tQTaskChildren.ptTail, ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[842].tQTaskChildren.ptTail, ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[844].tQTaskChildren.ptTail, ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[846].tQTaskChildren.ptTail, ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[838].tQTaskChildren.ptTail, ptQTask);
  if ( *(_DWORD *)&ptQTask[1].eQTaskType )
  {
    sprintf(igi2_frame.zResourceName, "%s_1.spr", (char *)&ptQTask[2].tQTaskChildren.ptMiddle);
    strcpy((char *)&ptQTask[5].tQTaskRefList.ptHead[7].pxObject, igi2_frame.zResourceName);
    sprintf(igi2_frame.zResourceName, "%s_2.spr", (char *)&ptQTask[2].tQTaskChildren.ptMiddle);
    strcpy((char *)&ptQTask[5].tQTaskRefList.ptMiddle[7].pxObject, igi2_frame.zResourceName);
  }
  ptQTask[5].tQTaskRefList.ptHead[6].ptPrev = *(struct QReference_s **)&ptQTask[1].eQTaskType;
  ptQTask[5].tQTaskRefList.ptMiddle[6].ptPrev = *(struct QReference_s **)&ptQTask[1].eQTaskType;
  ((void (__cdecl *)(struct QReference_s *, void *))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][LOWORD(ptQTask[5].tQTaskRefList.ptHead[3].ptNext)].pfHandler)(
    ptQTask[5].tQTaskRefList.ptHead,
    pxContext);
  ((void (__cdecl *)(struct QReference_s *, void *))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][LOWORD(ptQTask[5].tQTaskRefList.ptMiddle[3].ptNext)].pfHandler)(
    ptQTask[5].tQTaskRefList.ptMiddle,
    pxContext);
  v8 = (struct QTask_s *)((char *)&ptQTaska[1].tQTaskChildren.ptHead->ptPrev
                        + (unsigned int)ptQTask[838].ptPrev
                        + (unsigned int)ptHead[4].ptNext
                        + 2);
  ptPrev = (struct QTask_s *)ptHead[4].ptPrev;
  if ( (int)ptPrev <= (int)ptQTaska[1].tQTaskChildren.ptMiddle )
    ptPrev = ptQTaska[1].tQTaskChildren.ptMiddle;
  v10 = MenuWindow_eQTaskType;
  ptQTask[1].tQTaskChildren.ptMiddle = (struct QTask_s *)&ptPrev->ptPrev;
  v11 = v10 + 511 * ParameterList_eUpdateInternalDataQTaskEvent;
  ptQTask[1].tQTaskChildren.ptHead = v8;
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][v11].pfHandler)(ptQTask, pxContext);
}

// source: j/0/menusystem/listbox.c:334  [size]
void __cdecl ListBox_RunHandler(struct QTask_s *ptQTask)
{
  struct QReference_s *ptMiddle; // ebx
  struct QReference_s *ptHead; // edi
  struct QTask_s *ptParent; // ecx
  struct QTask_s *v4; // eax
  bool v5; // zf
  struct QTask_s *nLastActiveID; // [esp+Ch] [ebp-4h]

  ptMiddle = ptQTask[5].tQTaskRefList.ptMiddle;
  nLastActiveID = ptQTask[838].ptNext;
  ptHead = ptQTask[5].tQTaskRefList.ptHead;
  if ( ptQTask[838].tQTaskChildren.ptTail
    && ptQTask[838].tQTaskRefList.ptHead->ptNext
    && ptQTask[838].tQTaskRefList.ptMiddle )
  {
    BYTE1(ptQTask[838].tQTaskChildren.ptHead) = Expression_EvalInt((struct QExpression_s *)ptQTask[838].tQTaskRefList.ptMiddle) != 0;
  }
  if ( BYTE1(ptQTask[838].tQTaskChildren.ptHead) )
  {
    ((void (__cdecl *)(struct QReference_s *))QTask_aatQTaskFinalEvent[1][LOWORD(ptHead[3].ptNext)].pfHandler)(ptHead);
    ((void (__cdecl *)(struct QReference_s *))QTask_aatQTaskFinalEvent[1][LOWORD(ptMiddle[3].ptNext)].pfHandler)(ptMiddle);
  }
  else
  {
    ptQTask[2].tQTaskChildren.ptHead = nullptr;
  }
  ptParent = ptQTask[837].ptParent;
  if ( ptParent )
  {
    if ( HIBYTE(ptHead[6].pxObject) || (v4 = ptQTask[2].tQTaskChildren.ptHead, v4 == (struct QTask_s *)-1) )
    {
      v5 = (*(_DWORD *)&ptQTask[837].eQTaskType)-- == 0;
      if ( v5 )
        *(_DWORD *)&ptQTask[837].eQTaskType = (char *)ptParent - 1;
    }
    else if ( HIBYTE(ptMiddle[6].pxObject) || v4 == (struct QTask_s *)-2 )
    {
      *(_DWORD *)&ptQTask[837].eQTaskType = (*(_DWORD *)&ptQTask[837].eQTaskType + 1) % (int)ptParent;
    }
    ptQTask[838].ptNext = *(&ptQTask[5].ptParent + 65 * *(_DWORD *)&ptQTask[837].eQTaskType);
  }
  v5 = nLastActiveID == ptQTask[838].ptNext;
  ptQTask[2].tQTaskChildren.ptHead = nullptr;
  if ( !v5 )
  {
    SoundSys_PlaySimpleSoundFn((char *)&g_zFileName.aptSelectableItems[22], 0, nullptr);
    Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[846].tQTaskChildren.ptTail, ptQTask);
  }
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][MenuWindow_eQTaskType].pfHandler)(ptQTask);
}

// source: j/0/menusystem/listbox.c:407  [anchor-caller]
void __cdecl ListBox_DrawHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vAlpha; };
    struct { char igi2_o1[24]; float vColourScale; };
    struct { char igi2_o2[28]; float vFade; };
    struct { char igi2_o3[32]; struct QSprite_s *nXPos; };
    struct { char igi2_o4[32]; int nXPosa; };
    struct { char igi2_o5[40]; __int64 nYPos; };
    struct { char igi2_o6[48]; char zTemp[128]; };
    char igi2_extent[176];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QReference_s *ptHead; // esi
  double v2; // st7
  struct QReference_s *ptMiddle; // edi
  struct QTask_s *ptNext; // eax
  struct QReference_s *v5; // edx
  char *v6; // ecx
  struct QReference_s *v7; // eax
  int v8; // edx
  struct StaticTilemap_s *v9; // esi
  struct QTask_s *ptPrev; // ebx
  char *v11; // edi
  unsigned int v12; // edi
  int p_ptTail; // ebx
  char *v14; // edi
  char *v16; // ebx
  int nHeight; // eax
  int v18; // edx
  __int16 *anGraphicWidth; // ecx
  int v20; // kr04_4
  struct QTask_s *v21; // edx
  int v22; // eax
  int v23; // ecx
  unsigned int bQGraphicFlags; // eax

  ptHead = ptQTask[5].tQTaskRefList.ptHead;
  v2 = (double)(*(_DWORD *)(*(_DWORD *)&ptQTask[1].eQTaskType + 356) - 8) * 0.125;
  ptMiddle = ptQTask[5].tQTaskRefList.ptMiddle;
  if ( v2 <= 0.0 )
    igi2_frame.vFade = 0.0;
  else
    igi2_frame.vFade = v2;
  igi2_frame.vColourScale = 1.0;
  if ( !BYTE1(ptQTask[838].tQTaskChildren.ptHead) )
    igi2_frame.vColourScale = 0.5;
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Screen_eDrawQTaskEvent][MenuWindow_eQTaskType].pfHandler)(ptQTask);
  ptNext = ptQTask[1].ptNext;
  v5 = ptHead[4].ptNext;
  v6 = (char *)&ptQTask[1].ptPrev->ptNext + 2;
  ptHead[3].pxObject = v6;
  ptNext = (struct QTask_s *)((char *)ptNext + 2);
  ptHead[3].ptPrev = (struct QReference_s *)ptNext;
  v7 = (struct QReference_s *)((char *)&ptNext->ptNext + (_DWORD)ptQTask[838].ptPrev + (unsigned int)v5 + 2);
  v8 = Screen_eDrawQTaskEvent;
  ptMiddle[3].pxObject = v6;
  ptMiddle[3].ptPrev = v7;
  ((void (__cdecl *)(struct QReference_s *))QTask_aatQTaskFinalEvent[v8][LOWORD(ptQTask[5].tQTaskRefList.ptHead[3].ptNext)].pfHandler)(ptQTask[5].tQTaskRefList.ptHead);
  ((void (__cdecl *)(struct QReference_s *))QTask_aatQTaskFinalEvent[Screen_eDrawQTaskEvent][LOWORD(ptQTask[5].tQTaskRefList.ptMiddle[3].ptNext)].pfHandler)(ptQTask[5].tQTaskRefList.ptMiddle);
  if ( ptQTask[837].ptParent )
  {
    v9 = (struct StaticTilemap_s *)ptQTask[838].tQTaskChildren.ptMiddle;
    if ( v9 )
    {
      ptPrev = ptQTask[838].ptPrev;
      v11 = (char *)(&ptQTask[5].eQTaskType + 130 * *(_DWORD *)&ptQTask[837].eQTaskType);
      igi2_frame.nXPos = v9->ptQTilemap->ptQSprite;
      if ( Font_GetStringWidth(igi2_frame.nXPos, v11) <= (int)&ptPrev[-1].eQTaskType )
      {
        Text_SetString(v9, v11);
      }
      else
      {
        strcpy(igi2_frame.zTemp, v11);
        v12 = strlen(igi2_frame.zTemp);
        if ( v12 )
        {
          p_ptTail = (int)&ptPrev[-1].tQTaskRefList.ptTail;
          do
          {
            if ( Font_GetStringWidth(igi2_frame.nXPos, igi2_frame.zTemp) <= p_ptTail )
              break;
            igi2_frame.zTemp[--v12] = 0;
          }
          while ( v12 );
        }
        v14 = (char *)&igi2_frame.nYPos + 7;
        while ( *++v14 )
          ;
        strcpy(v14, "...");
        Text_SetString(v9, igi2_frame.zTemp);
      }
      v16 = (char *)&ptQTask[1].ptPrev->ptNext
          + ((int)ptQTask[1].tQTaskChildren.ptMiddle
           - v9->ptQTilemap->nHeight
           * v9->ptQTilemap->ptQSprite->atQAnimframe[v9->ptQTilemap->ptQSprite->nQAnimframes].nHeight)
          / 2
          + 1;
      nHeight = v9->ptQTilemap->nHeight;
      v18 = 0;
      if ( nHeight > 0 )
      {
        anGraphicWidth = v9->ptQTilemap->anGraphicWidth;
        do
        {
          if ( *anGraphicWidth > v18 )
            v18 = *anGraphicWidth;
          ++anGraphicWidth;
          --nHeight;
        }
        while ( nHeight );
      }
      v20 = (int)ptQTask[1].tQTaskChildren.ptHead - v18;
      v21 = ptQTask[1].ptNext;
      v22 = (Display_tActiveMode.nWidth >> 1) + v20 / 2;
      v23 = Display_tActiveMode.nHeight;
      v9->vR = igi2_frame.vColourScale * 51.20000076293945;
      igi2_frame.nXPosa = (int)&v21[-8] + v22;
      bQGraphicFlags = v9->bQGraphicFlags;
      v9->vG = igi2_frame.vColourScale * 76.80000305175781;
      v9->bQGraphicFlags = bQGraphicFlags | 0x80000;
      v9->vB = igi2_frame.vColourScale * 128.0;
      v9->vA = igi2_frame.vFade;
      v9->vX = (float)(int)(__int64)(double)igi2_frame.nXPosa;
      igi2_frame.nYPos = (__int64)(double)(int)&v16[(v23 >> 1) - 240];
      v9->vY = (float)(int)igi2_frame.nYPos;
      Text_Register(v9);
    }
  }
  igi2_frame.vAlpha = igi2_frame.vColourScale * igi2_frame.vFade;
  MenuWindow_DrawBorder((struct MenuWindow_t *)ptQTask, 0.5, igi2_frame.vAlpha, SBYTE1(ptQTask[2].ptPrev));
}

// source: j/0/menusystem/listbox.c:514  [size]
void __cdecl ListBox_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = ListBox_ptParameterList;
}

// source: j/0/menusystem/listbox.c:530  [anchor-mhash]
void __cdecl ListBox_InitDataHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptTail; // ecx
  struct QTask_s *v2; // ecx
  struct QTask_s *v3; // edx
  int v4; // eax
  struct QTask_s **p_ptParent; // ecx
  struct QTask_s *ptHead; // ecx
  int v7; // edx
  struct QTask_s *v8; // eax
  int v9; // esi
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v11; // edx

  ListBox_DeleteEntries((struct ListBox_t *)ptQTask);
  ptTail = ptQTask[840].tQTaskChildren.ptTail;
  ListBox_ptActiveListBox = (struct ListBox_t *)ptQTask;
  if ( ptTail && ptQTask[840].tQTaskRefList.ptHead->ptNext && ptQTask[840].tQTaskRefList.ptMiddle )
    Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[840].tQTaskChildren.ptTail, ptQTask);
  v2 = ptQTask[842].tQTaskChildren.ptTail;
  ListBox_ptActiveListBox = nullptr;
  if ( v2 )
  {
    if ( ptQTask[842].tQTaskRefList.ptHead->ptNext )
    {
      if ( ptQTask[842].tQTaskRefList.ptMiddle )
      {
        v3 = (struct QTask_s *)(__int64)Level_RunLevelExpression(
                                          (struct LevelExpression_s *)&ptQTask[842].tQTaskChildren.ptTail,
                                          ptQTask);
        v4 = 0;
        if ( (int)ptQTask[837].ptParent > 0 )
        {
          p_ptParent = &ptQTask[5].ptParent;
          while ( v3 != *p_ptParent )
          {
            ++v4;
            p_ptParent += 65;
            if ( v4 >= (int)ptQTask[837].ptParent )
              goto LABEL_14;
          }
          *(_DWORD *)&ptQTask[837].eQTaskType = v4;
          ptQTask[838].ptNext = v3;
        }
      }
    }
  }
LABEL_14:
  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v7 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v8 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v8 = nullptr;
      v9 = MenuWindow_eInitDataEvent;
      QTask_atProtectedQTaskStack[v7].ptQTask = v8;
      pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[v9][ptHead->eQTaskType].pfHandler;
      v11 = v7 + 1;
      QTask_nProtectedQTaskStackOffset = v11;
      if ( pfHandler )
      {
        pfHandler(ptHead);
        v11 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v11];
      v7 = v11 - 1;
      QTask_nProtectedQTaskStackOffset = v7;
    }
    while ( ptHead );
  }
}

// source: j/0/menusystem/listbox.c:580  [size]
void __cdecl ListBox_ChangeDataHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // ecx
  int v2; // edx
  struct QTask_s *v3; // eax
  int v4; // esi
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v6; // edx

  if ( ptQTask[844].tQTaskChildren.ptTail
    && ptQTask[844].tQTaskRefList.ptHead->ptNext
    && ptQTask[844].tQTaskRefList.ptMiddle )
  {
    Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[844].tQTaskChildren.ptTail, ptQTask);
  }
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

// source: j/0/menusystem/listbox.c:605  [size]
void __cdecl ListBox_RegisterScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( !LOBYTE(ptQTask[838].tQTaskChildren.ptHead) )
  {
    LOBYTE(ptQTask[838].tQTaskChildren.ptHead) = 1;
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.nActiveID", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int,
      &ptQTask[838],
      4,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
  }
}

// source: j/0/menusystem/listbox.c:637  [size]
void __cdecl ListBox_RemoveScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( LOBYTE(ptQTask[838].tQTaskChildren.ptHead) )
  {
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.nActiveID", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    LOBYTE(ptQTask[838].tQTaskChildren.ptHead) = 0;
  }
}

// source: j/0/menusystem/listbox.c:695  [anchor-callee]
void __cdecl ListBox_AddItem(char *zItemName, int nItemID)
{
  int v2; // ecx
  char *v3; // esi
  struct ListBoxItem_t *v4; // edi
  int v5; // eax
  struct ListBoxItem_t *atListBoxItem; // ecx

  if ( ListBox_ptActiveListBox )
  {
    v2 = *(_DWORD *)&ListBox_ptActiveListBox[1].atListBoxItem[61].zItem[120];
    v3 = &ListBox_ptActiveListBox[1].atListBoxItem[61].zItem[120];
    if ( v2 < 128 )
    {
      v4 = &ListBox_ptActiveListBox->atListBoxItem[v2];
      v5 = 0;
      if ( v2 <= 0 )
      {
LABEL_7:
        v4->nItemID = nItemID;
        _snprintf(v4->zItem, 0x100u, (char *const)&stru_6A4CDC.tDebugConsoleLineList.ptMiddle, zItemName);
        ++*(_DWORD *)v3;
      }
      else
      {
        atListBoxItem = ListBox_ptActiveListBox->atListBoxItem;
        while ( atListBoxItem->nItemID != nItemID )
        {
          ++v5;
          ++atListBoxItem;
          if ( v5 >= (int)(*(_DWORD *)v3) )
            goto LABEL_7;
        }
      }
    }
  }
}

// source: j/0/menusystem/listbox.c:737  [anchor-hash]
void __cdecl ListBox_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // edx

  v0 = QTask_NewQTaskType("ListBox", 33936, MenuWindow_eQTaskType, 0, 0);
  ListBox_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, ListBox_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Screen_eDrawQTaskEvent, ListBox_DrawHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, ListBox_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, ListBox_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))ListBox_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, ListBox_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, MenuWindow_eInitDataEvent, ListBox_InitDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, MenuWindow_eChangeDataEvent, ListBox_ChangeDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eRegisterLevelScriptSymbolsEvent,
    ListBox_RegisterScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Level_eRemoveLevelScriptSymbolsEvent, ListBox_RemoveScriptSymbolsHandler);
  v1 = (struct ParameterList_s *)Mem_AllocFn(172, 4);
  v2 = Level_eParameterTypeString32;
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  v1->nParameters = 0;
  v1->nMaxParameters = 8;
  ListBox_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0x5Cu, v2, "Sprite Resource", 7u, nullptr);
  ParameterList_AddParameter(ListBox_ptParameterList, 0x9Cu, Level_eParameterTypeString32, "Font Resource", 7u, nullptr);
  ParameterList_AddParameter(ListBox_ptParameterList, 0x82F4u, Level_eParameterTypeInt32, "Width", 7u, nullptr);
  ParameterList_AddParameter(
    ListBox_ptParameterList,
    0x8350u,
    Level_eParameterTypeVarString,
    "Collect Items Script",
    7u,
    nullptr);
  ParameterList_AddParameter(
    ListBox_ptParameterList,
    0x83A0u,
    Level_eParameterTypeVarString,
    "Get Data Script",
    7u,
    nullptr);
  ParameterList_AddParameter(
    ListBox_ptParameterList,
    0x83F0u,
    Level_eParameterTypeVarString,
    "Set Data Script",
    7u,
    nullptr);
  ParameterList_AddParameter(
    ListBox_ptParameterList,
    0x8440u,
    Level_eParameterTypeVarString,
    "Modify Data Script",
    7u,
    nullptr);
  ParameterList_AddParameter(
    ListBox_ptParameterList,
    0x8300u,
    Level_eParameterTypeVarString,
    "isEnabled Expression",
    7u,
    nullptr);
}

// source: j/0/menusystem/listbox.c:781  [size]
void __cdecl ListBox_Close()
{
  int v0; // esi

  if ( ListBox_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&ListBox_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(ListBox_eQTaskType);
  ListBox_eQTaskType = 512;
}
