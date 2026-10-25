/* j/0/menusystem/menuframe.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/menusystem/menuframe.c:79  [anchor-mhash]
int __cdecl MenuFrame_DrawHorizontalBorder(
        struct MenuFrame_t *ptMenuFrame,
        int nXPos,
        int nYPos,
        int nTotalWidth,
        int iLeftSprite,
        int iMiddleSprite,
        int iRightSprite,
        int isBottom)
{
  int v8; // ebp
  int nWidth; // ebx
  int nHeight; // edi
  struct QSprite_s *v11; // eax
  struct QAnimframe_s *atQAnimframe; // edx
  struct QSprite_s *v13; // eax
  struct QAnimframe_s *v14; // edx
  struct QSprite_s *v15; // eax
  int v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // ebx
  float ptQSprite; // [esp+0h] [ebp-2Ch]
  float ptQSpritea; // [esp+0h] [ebp-2Ch]
  float ptQSpriteb; // [esp+0h] [ebp-2Ch]
  float vX; // [esp+4h] [ebp-28h]
  float vXa; // [esp+4h] [ebp-28h]
  int nRightWidth; // [esp+28h] [ebp-4h]
  float iRightSpritea = *(float *)&isBottom; // [esp+48h] [ebp+1Ch] ARGSLOT

  v8 = 0;
  nWidth = 0;
  nHeight = 0;
  nRightWidth = 0;
  if ( ptMenuFrame->aptBorderSprites[0] )
  {
    v11 = ptMenuFrame->aptBorderSprites[iLeftSprite];
    atQAnimframe = v11->atQAnimframe;
    nWidth = atQAnimframe[v11->nQAnimframes].nWidth;
    nHeight = atQAnimframe[v11->nQAnimframes].nHeight;
  }
  if ( ptMenuFrame->aptBorderSprites[1] )
  {
    v13 = ptMenuFrame->aptBorderSprites[iMiddleSprite];
    v14 = v13->atQAnimframe;
    v8 = v14[v13->nQAnimframes].nWidth;
    if ( nHeight <= v14[v13->nQAnimframes].nHeight )
      nHeight = v13->atQAnimframe[v13->nQAnimframes].nHeight;
  }
  if ( ptMenuFrame->aptBorderSprites[2] )
  {
    v15 = ptMenuFrame->aptBorderSprites[iRightSprite];
    nRightWidth = v15->atQAnimframe[v15->nQAnimframes].nWidth;
    if ( nHeight <= v15->atQAnimframe[v15->nQAnimframes].nHeight )
      nHeight = v15->atQAnimframe[v15->nQAnimframes].nHeight;
  }
  if ( isBottom )
    nYPos -= nHeight;
  if ( nWidth )
  {
    vX = (float)nYPos;
    ptQSprite = (float)nXPos;
    QSprite_Register(ptMenuFrame->aptBorderSprites[iLeftSprite], ptQSprite, vX, 128.0, 128.0, 128.0, 0, 0, 0);
    nXPos += nWidth;
    v16 = nTotalWidth - nWidth;
  }
  else
  {
    v16 = nTotalWidth;
  }
  v17 = v16 - nRightWidth;
  if ( v8 )
  {
    v18 = v17 / v8;
    if ( v18 > 0 )
    {
      v19 = v18;
      do
      {
        ptQSpritea = (float)nXPos;
        iRightSpritea = (float)nYPos;
        QSprite_Register(
          ptMenuFrame->aptBorderSprites[iMiddleSprite],
          ptQSpritea,
          iRightSpritea,
          128.0,
          128.0,
          128.0,
          0,
          0,
          0);
        --v19;
        nXPos += v8;
      }
      while ( v19 );
    }
  }
  else
  {
    nXPos += v17;
  }
  if ( nRightWidth )
  {
    vXa = (float)nYPos;
    ptQSpriteb = (float)nXPos;
    QSprite_Register(ptMenuFrame->aptBorderSprites[iRightSprite], ptQSpriteb, vXa, 128.0, 128.0, 128.0, 0, 0, 0);
  }
  return nHeight;
}

// source: j/0/menusystem/menuframe.c:176  [anchor-mhash]
void __cdecl MenuFrame_DrawVerticalBorder(
        struct MenuFrame_t *ptMenuFrame,
        int nXPos,
        int nYPos,
        int nTotalHeight,
        int iSprite,
        int isRight)
{
  struct QSprite_s *v7; // ecx
  int nHeight; // esi
  int v9; // edi
  float vX; // [esp+0h] [ebp-28h]
  float iSpritea = *(float *)&iSprite; // [esp+3Ch] [ebp+14h] ARGSLOT

  v7 = ptMenuFrame->aptBorderSprites[iSprite];
  if ( v7 )
  {
    nHeight = v7->atQAnimframe[v7->nQAnimframes].nHeight;
    if ( isRight )
      nXPos -= v7->atQAnimframe[v7->nQAnimframes].nWidth;
    if ( nTotalHeight / nHeight > 0 )
    {
      v9 = nTotalHeight / nHeight;
      do
      {
        vX = (float)nYPos;
        iSpritea = (float)nXPos;
        QSprite_Register(ptMenuFrame->aptBorderSprites[iSprite], iSpritea, vX, 128.0, 128.0, 128.0, 0, 0, -1);
        --v9;
        nYPos += nHeight;
      }
      while ( v9 );
    }
  }
}

// source: j/0/menusystem/menuframe.c:215  [anchor-mhash]
void __cdecl MenuFrame_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][MenuWindow_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  memset(&ptQTask[3].eQTaskType, 0, 0x20u);
  LOBYTE(ptQTask[2].tQTaskChildren.ptMiddle) = 0;
  ptQTask[1].ptNext = (struct QTask_s *)220;
  ptQTask[1].ptPrev = (struct QTask_s *)220;
  ptQTask[1].tQTaskChildren.ptHead = (struct QTask_s *)200;
  ptQTask[1].tQTaskChildren.ptMiddle = (struct QTask_s *)40;
}

// source: j/0/menusystem/menuframe.c:250  [size]
void __cdecl MenuFrame_DeleteHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: j/0/menusystem/menuframe.c:265  [anchor-strings]
void __cdecl MenuFrame_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // eax
  _DWORD *p_eQTaskType; // edi
  int v4; // esi
  char zResourceName[64]; // [esp+4h] [ebp-40h] BYREF

  if ( *(_DWORD *)&ptQTask[1].eQTaskType )
  {
    v2 = 0;
    p_eQTaskType = &ptQTask[3].eQTaskType;
    do
    {
      v4 = v2 + 1;
      sprintf(zResourceName, "%s_%d.spr", (char *)&ptQTask[2].tQTaskChildren.ptMiddle, v2 + 1);
      *p_eQTaskType = MenuManager_GetSprite(*(struct QTask_s **)&ptQTask[1].eQTaskType, zResourceName);
      v2 = v4;
      ++p_eQTaskType;
    }
    while ( v4 < 8 );
  }
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][MenuWindow_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
}

// source: j/0/menusystem/menuframe.c:304  [anchor-mhash]
void __cdecl MenuFrame_DrawHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptMiddle; // ebp
  char *v3; // ebx
  char *v4; // edi
  int v5; // ebp
  int v6; // edi
  int nTopBorderHeight; // [esp+10h] [ebp-4h]
  struct QTask_s *ptQTaska = *(struct QTask_s * *)&ptQTask; // [esp+18h] [ebp+4h] ARGSLOT

  ptMiddle = ptQTask[1].tQTaskChildren.ptMiddle;
  v3 = (char *)&ptQTask[1].ptNext[-8] + (Display_tActiveMode.nWidth >> 1);
  v4 = (char *)&ptQTask[1].ptPrev[-6] + (Display_tActiveMode.nHeight >> 1);
  ptQTaska = ptQTask[1].tQTaskChildren.ptHead;
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Screen_eDrawQTaskEvent][MenuWindow_eQTaskType].pfHandler)(ptQTask);
  nTopBorderHeight = MenuFrame_DrawHorizontalBorder(
                       (struct MenuFrame_t *)ptQTask,
                       (int)v3,
                       (int)v4,
                       (int)ptQTaska,
                       0,
                       1,
                       2,
                       0);
  v5 = (int)ptMiddle
     - nTopBorderHeight
     - MenuFrame_DrawHorizontalBorder(
         (struct MenuFrame_t *)ptQTask,
         (int)v3,
         (int)ptMiddle + (_DWORD)v4,
         (int)ptQTaska,
         6,
         5,
         4,
         1);
  v6 = (int)&v4[nTopBorderHeight];
  MenuFrame_DrawVerticalBorder((struct MenuFrame_t *)ptQTask, (int)v3, v6, v5, 7, 0);
  MenuFrame_DrawVerticalBorder((struct MenuFrame_t *)ptQTask, (int)ptQTaska + (_DWORD)v3, v6, v5, 3, 1);
}

// source: j/0/menusystem/menuframe.c:360  [size]
void __cdecl MenuFrame_RunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // edx
  unsigned __int16 v2; // cx

  if ( !LOBYTE(ptQTask[2].ptPrev) )
    goto LABEL_13;
  MenuWindow_HitTest(
    (struct MenuWindow_t *)ptQTask,
    (int)ptQTask[1].ptNext,
    (int)ptQTask[1].ptPrev,
    (int)ptQTask[1].tQTaskChildren.ptHead,
    (int)ptQTask[1].tQTaskChildren.ptMiddle,
    nullptr,
    nullptr);
  if ( BYTE1(ptQTask[2].ptNext) && !LOBYTE(ptQTask[2].ptNext) )
    MenuManager_SetSelectedWindow(*(struct QTask_s **)&ptQTask[1].eQTaskType, ptQTask);
  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v2 = MenuWindow_eQTaskType;
    do
    {
      if ( QTask_IsQTaskTypeDerived(ptHead->eQTaskType, v2) )
      {
        ptHead[2].tQTaskChildren.ptHead = ptQTask[2].tQTaskChildren.ptHead;
        BYTE1(ptHead[2].ptPrev) = BYTE1(ptQTask[2].ptPrev);
      }
      ptHead = ptHead->ptNext;
    }
    while ( ptHead && ptHead->ptNext );
  }
  else
  {
LABEL_13:
    v2 = MenuWindow_eQTaskType;
  }
  ptQTask[2].tQTaskChildren.ptHead = nullptr;
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][v2].pfHandler)(ptQTask);
}

// source: j/0/menusystem/menuframe.c:423  [size]
void __cdecl MenuFrame_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = MenuFrame_ptParameterList;
}

// source: j/0/menusystem/menuframe.c:441  [anchor-hash]
void __cdecl MenuFrame_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // edx

  dword_750F68 = 0;
  unk_750F6C = 0;
  unk_750F70 = 0;
  unk_750F74 = 1082392576;
  v0 = QTask_NewQTaskType("MenuFrame", 188, MenuWindow_eQTaskType, 0, 0);
  MenuFrame_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, MenuFrame_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Screen_eDrawQTaskEvent, MenuFrame_DrawHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, (void (__cdecl *)(struct QTask_s *))MenuFrame_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, MenuFrame_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))MenuFrame_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, MenuFrame_UpdateInternalDataHandler);
  v1 = (struct ParameterList_s *)Mem_AllocFn(212, 4);
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  v2 = Level_eParameterTypeString32;
  v1->nParameters = 0;
  v1->nMaxParameters = 10;
  MenuFrame_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0x5Cu, v2, "Sprite Resource", 7u, nullptr);
  ParameterList_AddParameter(MenuFrame_ptParameterList, 0x28u, Level_eParameterTypeInt32, "X-Pos", 7u, &dword_750F68);
  ParameterList_AddParameter(MenuFrame_ptParameterList, 0x2Cu, Level_eParameterTypeInt32, "Y-Pos", 7u, &dword_750F68);
  ParameterList_AddParameter(MenuFrame_ptParameterList, 0x30u, Level_eParameterTypeInt32, "Width", 7u, &dword_750F68);
  ParameterList_AddParameter(MenuFrame_ptParameterList, 0x34u, Level_eParameterTypeInt32, "Height", 7u, &dword_750F68);
  ParameterList_AddParameter(MenuFrame_ptParameterList, 0x40u, Level_eParameterTypeInt32, "LineUpMode", 7u, nullptr);
  ParameterList_AddParameter(MenuFrame_ptParameterList, 0x44u, Level_eParameterTypeInt32, "AlignmentMode", 7u, nullptr);
  ParameterList_AddParameter(MenuFrame_ptParameterList, 0x38u, Level_eParameterTypeInt16, "X-Spacing", 7u, nullptr);
  ParameterList_AddParameter(MenuFrame_ptParameterList, 0x3Cu, Level_eParameterTypeInt16, "Y-Spacing", 7u, nullptr);
  ParameterList_AddParameter(MenuFrame_ptParameterList, 0x54u, Level_eParameterTypebool8, "Is Selectable", 7u, nullptr);
}

// source: j/0/menusystem/menuframe.c:493  [size]
void __cdecl MenuFrame_Close()
{
  int v0; // esi

  if ( MenuFrame_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&MenuFrame_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(MenuFrame_eQTaskType);
  MenuFrame_eQTaskType = 512;
}
