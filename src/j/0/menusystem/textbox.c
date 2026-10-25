/* j/0/menusystem/textbox.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/menusystem/textbox.c:110  [anchor-callee]
int __cdecl TextBox_Print(
        int nX,
        int nY,
        float vZ,
        int nWidth,
        int nHeight,
        char *zText,
        struct QSprite_s *ptQSprite,
        struct StaticTilemap_s *ptText,
        float vAlpha)
{
  #pragma pack(push, 1)
  union
  {
    struct { unsigned int v38; };
    struct { char igi2_o1[4]; int v39; };
    struct { char igi2_o2[32]; int nPrintX; };
    struct { char igi2_o3[36]; int nLineWidth; };
    struct { char igi2_o4[40]; int isCompleteText; };
    struct { char igi2_o5[44]; float vX; };
    struct { char igi2_o6[48]; int nWordWidth; };
    struct { char igi2_o7[52]; float ptQTilemap; };
    struct { char igi2_o8[56]; char zWord[256]; };
    struct { char igi2_o9[312]; char zLine[256]; };
    char igi2_extent[568];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v9; // esi
  unsigned int v10; // eax
  int v11; // ecx
  char v12; // al
  int StringWidth; // eax
  int v15; // edx
  unsigned int v16; // eax
  char *v17; // edi
  int v19; // eax
  char v20; // cl
  struct QTilemap_s *v21; // edx
  unsigned __int8 *anID; // edi
  unsigned int v23; // edx
  unsigned __int8 *v24; // edi
  char v25; // cl
  unsigned __int8 v26; // dl
  struct QTilemap_s *v27; // edi
  unsigned __int8 *v28; // ecx
  char *v29; // eax
  int v30; // esi
  int nPri; // eax
  unsigned int bQGraphicFlags; // ecx
  float v33; // edx
  struct QTilemap_s *v34; // ebx
  float vA; // eax
  float vB; // ecx

  igi2_frame.nPrintX = nX;
  v9 = nWidth;
  v10 = ptText->bQGraphicFlags | 0x80000;
  igi2_frame.isCompleteText = 0;
  igi2_frame.zLine[0] = 0;
  ptText->bQGraphicFlags = v10;
  ptText->vA = vAlpha;
  while ( 2 )
  {
    v11 = 0;
    igi2_frame.zWord[0] = 0;
    while ( 1 )
    {
      v12 = *zText;
      if ( *zText++ == 0 )
        break;
      if ( v12 == 32 )
      {
        igi2_frame.zWord[v11] = 32;
        igi2_frame.zWord[v11 + 1] = 0;
        goto LABEL_9;
      }
      igi2_frame.zWord[v11++] = v12;
    }
    igi2_frame.isCompleteText = 1;
    igi2_frame.zWord[v11] = 0;
LABEL_9:
    StringWidth = Font_GetStringWidth(ptQSprite, igi2_frame.zWord);
    v15 = StringWidth;
    igi2_frame.nWordWidth = StringWidth;
    if ( v9 <= StringWidth )
    {
      igi2_frame.nPrintX = nX;
      nY += ptQSprite->atQAnimframe[ptQSprite->nQAnimframes].nHeight;
      v19 = 0;
      do
      {
        v20 = igi2_frame.zWord[v19];
        igi2_frame.zLine[v19++] = v20;
      }
      while ( v20 );
      igi2_frame.nLineWidth = nWidth - v15;
    }
    else
    {
      igi2_frame.nLineWidth = v9 - StringWidth;
      v16 = strlen(igi2_frame.zWord) + 1;
      v17 = &igi2_frame.zWord[255];
      while ( *++v17 )
        ;
      qmemcpy(v17, igi2_frame.zWord, v16);
    }
    v21 = ptText->ptQTilemap;
    memset(ptText->ptQTilemap->anGraphicWidth, 0, 2 * ptText->ptQTilemap->nHeight);
    anID = v21->anID;
    v23 = v21->nHeight * v21->nWidth;
    memset(anID, 0, 4 * (v23 >> 2));
    v24 = &anID[4 * (v23 >> 2)];
    v25 = v23;
    v26 = igi2_frame.zWord[0];
    memset(v24, 0, v25 & 3);
    v27 = ptText->ptQTilemap;
    v28 = ptText->ptQTilemap->ptQSprite->ptQTilemap->anID;
    v29 = igi2_frame.zWord;
    if ( v26 )
    {
      v30 = ptText->ptQTilemap->anID - (unsigned __int8 *)igi2_frame.zWord;
      do
      {
        v29[v30] = v28[v26];
        v26 = *++v29;
      }
      while ( v26 );
    }
    QTilemap_UpdateGraphicWidth(v27, 0);
    nPri = ptText->nPri;
    bQGraphicFlags = ptText->bQGraphicFlags;
    v33 = ptText->vZ;
    igi2_frame.ptQTilemap = (float)igi2_frame.nPrintX;
    v34 = ptText->ptQTilemap;
    ptText->vX = igi2_frame.ptQTilemap;
    igi2_frame.v39 = nPri;
    vA = ptText->vA;
    igi2_frame.v38 = bQGraphicFlags | 0x40000000;
    igi2_frame.vX = (float)nY;
    vB = ptText->vB;
    ptText->vY = igi2_frame.vX;
    QTilemap_Register(v34, igi2_frame.ptQTilemap, igi2_frame.vX, ptText->vR, ptText->vG, vB, vA, v33, igi2_frame.v38, igi2_frame.v39);
    igi2_frame.nPrintX += igi2_frame.nWordWidth;
    if ( !igi2_frame.isCompleteText )
    {
      v9 = igi2_frame.nLineWidth;
      continue;
    }
    return nY + ptQSprite->atQAnimframe[ptQSprite->nQAnimframes].nHeight;
  }
}

// source: j/0/menusystem/textbox.c:246  [anchor-mhash]
void __cdecl TextBox_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][MenuWindow_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  LOBYTE(ptQTask[2].tQTaskChildren.ptMiddle) = 0;
  *(_DWORD *)&ptQTask[3].eQTaskType = 0;
  ptQTask[4].ptNext = nullptr;
  ptQTask[1].ptNext = (struct QTask_s *)300;
  ptQTask[1].ptPrev = (struct QTask_s *)230;
  ptQTask[215].tQTaskChildren.ptTail = nullptr;
  ptQTask[215].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[1].tQTaskChildren.ptHead = (struct QTask_s *)128;
  ptQTask[1].tQTaskChildren.ptMiddle = (struct QTask_s *)128;
  ptQTask[1].tQTaskRefList.ptTail = (struct QReference_s *)1;
  ptQTask[1].ptParent = (struct QTask_s *)1;
  ptQTask[215].tQTaskRefList.ptHead = nullptr;
  ptQTask[215].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[215].tQTaskRefList.ptTail = nullptr;
  ptQTask[217].tQTaskChildren.ptTail = nullptr;
  ptQTask[217].tQTaskRefList.ptHead = nullptr;
  ptQTask[217].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[217].tQTaskRefList.ptTail = nullptr;
  ptQTask[219].tQTaskChildren.ptTail = nullptr;
}

// source: j/0/menusystem/textbox.c:286  [anchor-mhash]
void __cdecl TextBox_DeleteHandler(struct QTask_s *ptQTask)
{
  struct StaticTilemap_s *v1; // eax

  v1 = *(struct StaticTilemap_s **)&ptQTask[3].eQTaskType;
  if ( v1 )
  {
    Text_Delete(v1);
    *(_DWORD *)&ptQTask[3].eQTaskType = 0;
  }
  ptQTask[215].tQTaskChildren.ptTail = nullptr;
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[215].tQTaskRefList);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[217].tQTaskRefList);
}

// source: j/0/menusystem/textbox.c:315  [anchor-mhash]
void __cdecl TextBox_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct StaticTilemap_s *v2; // eax
  struct QTask_s *v3; // ebx
  struct QTask_s *Font; // eax
  struct StaticTilemap_s *v5; // eax

  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[215].tQTaskRefList, ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[217].tQTaskRefList, ptQTask);
  v2 = *(struct StaticTilemap_s **)&ptQTask[3].eQTaskType;
  if ( v2 )
  {
    Text_Delete(v2);
    *(_DWORD *)&ptQTask[3].eQTaskType = 0;
  }
  v3 = *(struct QTask_s **)&ptQTask[1].eQTaskType;
  if ( v3 )
  {
    Font = (struct QTask_s *)MenuManager_GetFont(v3, (char *)&ptQTask[2].tQTaskChildren.ptMiddle);
    ptQTask[4].ptNext = Font;
    if ( Font )
    {
      v5 = Text_New((struct QSprite_s *)Font, 0.0, 0.0, (char *)&g_zInitialValue);
      *(_DWORD *)&ptQTask[3].eQTaskType = v5;
      v5->nPri = 0;
    }
  }
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][MenuWindow_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
}

// source: j/0/menusystem/textbox.c:363  [anchor-mhash]
void __cdecl TextBox_RunHandler(struct QTask_s *ptQTask)
{
  struct QReference_s *v1; // edx
  struct QTask_s *v2; // eax
  struct QReferenceList_s *p_tQTaskRefList; // ecx

  if ( ptQTask[217].tQTaskRefList.ptHead )
  {
    if ( ptQTask[217].tQTaskRefList.ptMiddle->ptNext )
    {
      if ( ptQTask[217].tQTaskRefList.ptTail )
      {
        v1 = (struct QReference_s *)(__int64)Level_RunLevelExpression(
                                               (struct LevelExpression_s *)&ptQTask[217].tQTaskRefList,
                                               ptQTask);
        v2 = nullptr;
        if ( (int)ptQTask[215].tQTaskChildren.ptTail > 0 )
        {
          p_tQTaskRefList = &ptQTask[10].tQTaskRefList;
          while ( v1 != p_tQTaskRefList->ptHead )
          {
            v2 = (struct QTask_s *)((char *)v2 + 1);
            p_tQTaskRefList += 22;
            if ( (int)v2 >= (int)ptQTask[215].tQTaskChildren.ptTail )
              goto LABEL_10;
          }
          ptQTask[215].tQTaskChildren.ptMiddle = v2;
        }
      }
    }
  }
LABEL_10:
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][MenuWindow_eQTaskType].pfHandler)(ptQTask);
}

// source: j/0/menusystem/textbox.c:403  [anchor-mhash]
void __cdecl TextBox_DrawHandler(struct QTask_s *ptQTask)
{
  double v2; // st7
  struct QTask_s *ptNext; // edx
  struct StaticTilemap_s *v4; // ecx
  char *v5; // eax
  float ptQTaska = *(float *)&ptQTask; // [esp+8h] [ebp+4h] ARGSLOT

  v2 = (double)(*(_DWORD *)(*(_DWORD *)&ptQTask[1].eQTaskType + 356) - 8) * 0.125;
  if ( v2 <= 0.0 )
    ptQTaska = 0.0;
  else
    ptQTaska = v2;
  if ( ptQTask[215].tQTaskChildren.ptTail )
  {
    ptNext = ptQTask[4].ptNext;
    if ( ptNext )
    {
      v4 = *(struct StaticTilemap_s **)&ptQTask[3].eQTaskType;
      if ( v4 )
      {
        v5 = (char *)(&ptQTask[10].tQTaskRefList.ptMiddle)[66 * (int)ptQTask[215].tQTaskChildren.ptMiddle];
        if ( v5 )
          TextBox_Print(
            (int)&ptQTask[1].ptNext[-7] + (Display_tActiveMode.nWidth >> 1) - 36,
            (int)&ptQTask[1].ptPrev[-5] + (Display_tActiveMode.nHeight >> 1) - 36,
            1.0,
            (int)&ptQTask[1].tQTaskChildren.ptHead[-1].ptParent,
            (int)&ptQTask[1].tQTaskChildren.ptMiddle[-1].ptParent,
            v5,
            (struct QSprite_s *)ptNext,
            v4,
            ptQTaska);
      }
    }
  }
  MenuWindow_DrawBorder((struct MenuWindow_t *)ptQTask, 0.5, ptQTaska, 0);
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Screen_eDrawQTaskEvent][MenuWindow_eQTaskType].pfHandler)(ptQTask);
}

// source: j/0/menusystem/textbox.c:447  [size]
void __cdecl TextBox_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = TextBox_ptParameterList;
}

// source: j/0/menusystem/textbox.c:463  [size]
void __cdecl TextBox_InitDataHandler(struct QTask_s *ptQTask)
{
  bool v1; // zf
  struct QTask_s *ptTail; // eax
  int v3; // ebp
  struct QTask_s **p_ptPrev; // esi
  struct QTask_s *ptHead; // ecx
  int v6; // edx
  struct QTask_s *v7; // eax
  int v8; // esi
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v10; // edx

  ptQTask[215].tQTaskChildren.ptMiddle = nullptr;
  v1 = ptQTask[215].tQTaskRefList.ptHead == nullptr;
  TextBox_ptActiveTextBox = (struct TextBox_t *)ptQTask;
  if ( !v1 && ptQTask[215].tQTaskRefList.ptMiddle->ptNext && ptQTask[215].tQTaskRefList.ptTail )
    Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[215].tQTaskRefList, ptQTask);
  ptTail = ptQTask[215].tQTaskChildren.ptTail;
  v3 = 0;
  TextBox_ptActiveTextBox = nullptr;
  p_ptPrev = &ptQTask[4].ptPrev;
  if ( (int)ptTail > 0 )
  {
    do
    {
      p_ptPrev[65] = (struct QTask_s *)Config_GetLocalizedStringForLanguage(
                                         (char *)p_ptPrev,
                                         Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                         true);
      p_ptPrev += 66;
      ++v3;
    }
    while ( v3 < (int)ptQTask[215].tQTaskChildren.ptTail );
  }
  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v6 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v7 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v7 = nullptr;
      v8 = MenuWindow_eInitDataEvent;
      QTask_atProtectedQTaskStack[v6].ptQTask = v7;
      pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[v8][ptHead->eQTaskType].pfHandler;
      v10 = v6 + 1;
      QTask_nProtectedQTaskStackOffset = v10;
      if ( pfHandler )
      {
        pfHandler(ptHead);
        v10 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v10];
      v6 = v10 - 1;
      QTask_nProtectedQTaskStackOffset = v6;
    }
    while ( ptHead );
  }
}

// source: j/0/menusystem/textbox.c:507  [size]
void __cdecl TextBox_ChangeDataHandler(struct QTask_s *ptQTask)
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

// source: j/0/menusystem/textbox.c:525  [anchor-hash]
void __cdecl TextBox_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax

  v0 = QTask_NewQTaskType("TextBox", 8780, MenuWindow_eQTaskType, 0, 0);
  TextBox_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, TextBox_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Screen_eDrawQTaskEvent, TextBox_DrawHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, TextBox_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, MenuWindow_eInitDataEvent, TextBox_InitDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, MenuWindow_eChangeDataEvent, TextBox_ChangeDataHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, TextBox_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))TextBox_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, TextBox_UpdateInternalDataHandler);
  v1 = (struct ParameterList_s *)Mem_AllocFn(112, 4);
  v1->nParameters = 0;
  v1->nMaxParameters = 5;
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  TextBox_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0x5Cu, Level_eParameterTypeString32, "Font Resource", 7u, nullptr);
  ParameterList_AddParameter(TextBox_ptParameterList, 0x30u, Level_eParameterTypeInt32, "Width", 7u, nullptr);
  ParameterList_AddParameter(TextBox_ptParameterList, 0x34u, Level_eParameterTypeInt32, "Height", 7u, nullptr);
  ParameterList_AddParameter(
    TextBox_ptParameterList,
    0x21ACu,
    Level_eParameterTypeVarString,
    "Collect Items",
    7u,
    nullptr);
  ParameterList_AddParameter(
    TextBox_ptParameterList,
    0x21FCu,
    Level_eParameterTypeVarString,
    "Get Active Picture",
    7u,
    nullptr);
}

// source: j/0/menusystem/textbox.c:567  [size]
void __cdecl TextBox_Close()
{
  int v0; // esi

  if ( TextBox_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&TextBox_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(TextBox_eQTaskType);
  TextBox_eQTaskType = 512;
}

// source: j/0/menusystem/textbox.c:588  [anchor-mhash]
char *__cdecl TextBox_AddItem(char *zItemName, int nItemID)
{
  struct TextBox_t *v2; // esi
  struct TextBoxItem_s *v3; // edi
  int v4; // edx
  int *p_nItemID; // ecx
  int v6; // edx
  char v7; // cl

  v2 = TextBox_ptActiveTextBox;
  v3 = &TextBox_ptActiveTextBox->atTextBoxItem[TextBox_ptActiveTextBox->nTextItem];
  v4 = 0;
  if ( TextBox_ptActiveTextBox->nTextItem <= 0 )
  {
LABEL_5:
    TextBox_ptActiveTextBox->atTextBoxItem[TextBox_ptActiveTextBox->nTextItem].nItemID = nItemID;
    v6 = (char *)v3 - zItemName;
    do
    {
      v7 = *zItemName;
      zItemName[v6] = *zItemName;
      ++zItemName;
    }
    while ( v7 );
    ++v2->nTextItem;
  }
  else
  {
    p_nItemID = &TextBox_ptActiveTextBox->atTextBoxItem[0].nItemID;
    while ( *p_nItemID != nItemID )
    {
      ++v4;
      p_nItemID += 66;
      if ( v4 >= TextBox_ptActiveTextBox->nTextItem )
        goto LABEL_5;
    }
  }
  return zItemName;
}
