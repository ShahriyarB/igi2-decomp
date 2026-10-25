/* j/0/menusystem/scrolllistbox.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/menusystem/scrolllistbox.c:131  [anchor-hash]
struct QTask_s *__cdecl ScrollListBox_ForceVisible(struct QTask_s *ptQTask)
{
  struct QTask_s *result; // eax
  struct QTask_s *ptMiddle; // ecx
  struct QTask_s *v4; // ebp
  BOOL v5; // ebx
  struct QTask_s *ptParent; // ecx
  struct QTask_s *v7; // edx
  int v8; // esi
  struct QTask_s *ptPrev; // edx
  int v10; // ecx
  struct QTask_s *v11; // edi

  result = (struct QTask_s *)((int)&ptQTask[1].tQTaskChildren.ptMiddle[-1].eQTaskType
                            / (int)ptQTask[238].tQTaskRefList.ptTail);
  ptMiddle = ptQTask[226].tQTaskChildren.ptMiddle;
  v4 = ptMiddle;
  if ( (int)ptMiddle >= (int)result )
    v4 = result;
  v5 = (int)result < (int)ptMiddle;
  if ( (int)result < (int)ptMiddle && (ptParent = ptQTask[238].ptParent, (v7 = ptParent[16].ptParent) != nullptr) )
    v8 = (__int64)((double)(int)(&v7[-1].isInMemPool + 1) * *(double *)&ptParent[4].tQTaskChildren.ptHead + 0.5);
  else
    v8 = 0;
  ptPrev = ptQTask[228].ptPrev;
  v10 = (int)ptPrev - v8;
  if ( v5 )
  {
    if ( v10 >= 0 )
    {
      if ( v10 < (int)v4 )
        return result;
      if ( v10 > 0 )
        ptPrev = (struct QTask_s *)((char *)ptPrev - (char *)result + 1);
    }
    v11 = ptQTask[238].ptParent;
    result = v11[16].ptParent;
    if ( result )
      *(double *)&v11[4].tQTaskChildren.ptHead = ((double)(int)ptPrev + 0.5) / (double)(int)v11[16].ptParent;
  }
  return result;
}

// source: j/0/menusystem/scrolllistbox.c:164  [anchor-hash]
void __cdecl ScrollListBox_DeleteEntries(struct ScrollListBox_t *ptScrollListBox)
{
  struct ScrollListBoxItem_t *atScrollListBoxItem; // eax
  int v2; // ecx

  atScrollListBoxItem = ptScrollListBox->atScrollListBoxItem;
  v2 = 64;
  do
  {
    atScrollListBoxItem->zItem[0] = 0;
    atScrollListBoxItem->nItemID = 0;
    ++atScrollListBoxItem;
    --v2;
  }
  while ( v2 );
  ptScrollListBox->nEntries = 0;
  ptScrollListBox->nActiveEntry = 0;
  ptScrollListBox->nActiveID = 0;
}

// source: j/0/menusystem/scrolllistbox.c:192  [anchor-mhash]
void __cdecl ScrollListBox_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  unsigned __int16 v2; // ax
  struct QTask_s *v3; // eax
  struct QTask_s *v4; // eax
  void *v5; // [esp-Ch] [ebp-18h]

  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][MenuWindow_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  ptQTask[226].tQTaskChildren.ptMiddle = nullptr;
  ScrollListBox_DeleteEntries((struct ScrollListBox_t *)ptQTask);
  ptQTask[228].tQTaskRefList.ptTail = nullptr;
  ptQTask[228].ptParent = nullptr;
  *(_DWORD *)&ptQTask[228].eQTaskType = 0;
  ptQTask[230].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[230].tQTaskRefList.ptTail = nullptr;
  ptQTask[230].ptParent = nullptr;
  *(_DWORD *)&ptQTask[230].eQTaskType = 0;
  ptQTask[232].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[232].tQTaskRefList.ptTail = nullptr;
  ptQTask[232].ptParent = nullptr;
  *(_DWORD *)&ptQTask[232].eQTaskType = 0;
  ptQTask[234].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[234].tQTaskRefList.ptTail = nullptr;
  ptQTask[234].ptParent = nullptr;
  *(_DWORD *)&ptQTask[234].eQTaskType = 0;
  ptQTask[236].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[236].tQTaskRefList.ptTail = nullptr;
  ptQTask[236].ptParent = nullptr;
  *(_DWORD *)&ptQTask[236].eQTaskType = 0;
  ptQTask[238].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[1].tQTaskRefList.ptTail = (struct QReference_s *)1;
  ptQTask[1].ptParent = (struct QTask_s *)1;
  BYTE2(ptQTask[2].ptPrev) = 1;
  v5 = *(void **)&ptQTask[1].eQTaskType;
  v2 = SlideBar_eQTaskType;
  BYTE1(ptQTask[228].tQTaskRefList.ptHead) = 0;
  ptQTask[228].tQTaskChildren.ptTail = nullptr;
  LOBYTE(ptQTask[226].tQTaskRefList.ptHead) = 0;
  ptQTask[1].tQTaskChildren.ptHead = (struct QTask_s *)100;
  ptQTask[1].tQTaskChildren.ptMiddle = (struct QTask_s *)100;
  ptQTask[228].tQTaskRefList.ptMiddle = nullptr;
  v3 = QTask_NewFn(nullptr, v2, v5);
  strcpy((char *)&v3[2].tQTaskChildren.ptMiddle, "slidevert");
  LOBYTE(v3[4].tQTaskRefList.ptTail) = 0;
  v3[4].tQTaskRefList.ptHead = (struct QReference_s *)50;
  v3[16].ptParent = (struct QTask_s *)3;
  ptQTask[238].ptParent = v3;
  v4 = QTask_NewFn(nullptr, MenuWindow_eQTaskType, *(void **)&ptQTask[1].eQTaskType);
  HIBYTE(ptQTask[228].tQTaskRefList.ptHead) = 0;
  LOBYTE(ptQTask[228].tQTaskRefList.ptHead) = 0;
  *(_DWORD *)&ptQTask[238].eQTaskType = v4;
}

// source: j/0/menusystem/scrolllistbox.c:233  [anchor-mhash]
void __cdecl ScrollListBox_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QReference_s *ptMiddle; // eax

  QTask_Delete(ptQTask[238].ptParent);
  QTask_Delete(*(struct QTask_s **)&ptQTask[238].eQTaskType);
  ptMiddle = ptQTask[228].tQTaskRefList.ptMiddle;
  if ( ptMiddle )
  {
    Text_Delete((struct StaticTilemap_s *)ptMiddle);
    ptQTask[228].tQTaskRefList.ptMiddle = nullptr;
  }
  ScrollListBox_DeleteEntries((struct ScrollListBox_t *)ptQTask);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[228].tQTaskRefList.ptTail);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[230].tQTaskRefList.ptTail);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[232].tQTaskRefList.ptTail);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[234].tQTaskRefList.ptTail);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[236].tQTaskRefList.ptTail);
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Level_eRemoveLevelScriptSymbolsEvent][ptQTask->eQTaskType].pfHandler)(ptQTask);
}

// source: j/0/menusystem/scrolllistbox.c:271  [anchor-mhash]
void __cdecl ScrollListBox_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QSprite_s *Font; // edi
  struct QReference_s *ptMiddle; // eax
  struct QReference_s *v4; // eax
  int v5; // ecx
  struct QTask_s *ptHead; // edx

  Font = MenuManager_GetFont(*(struct QTask_s **)&ptQTask[1].eQTaskType, (char *)&ptQTask[226].tQTaskRefList);
  ptMiddle = ptQTask[228].tQTaskRefList.ptMiddle;
  if ( ptMiddle )
  {
    Text_Delete((struct StaticTilemap_s *)ptMiddle);
    ptQTask[228].tQTaskRefList.ptMiddle = nullptr;
  }
  if ( Font )
  {
    v4 = (struct QReference_s *)Text_New(Font, 0.0, 0.0, "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
    ptQTask[228].tQTaskRefList.ptMiddle = v4;
    v4[2].pxObject = nullptr;
    ptQTask[238].tQTaskRefList.ptTail = (struct QReference_s *)(SHIWORD(ptQTask[228].tQTaskRefList.ptMiddle->ptNext->ptPrev)
                                                              * *(__int16 *)(*((_DWORD *)ptQTask[228].tQTaskRefList.ptMiddle->ptNext->pxObject
                                                                             + 2)
                                                                           + 36
                                                                           * *((unsigned __int16 *)ptQTask[228].tQTaskRefList.ptMiddle->ptNext->pxObject
                                                                             + 10)
                                                                           + 14)
                                                              + 1);
  }
  else
  {
    ptQTask[238].tQTaskRefList.ptTail = (struct QReference_s *)1;
  }
  v5 = *(_DWORD *)&ptQTask[238].eQTaskType;
  ptHead = ptQTask[1].tQTaskChildren.ptHead;
  BYTE2(ptQTask[228].tQTaskRefList.ptHead) = 0;
  *(_DWORD *)(v5 + 48) = ptHead;
  *(_DWORD *)(*(_DWORD *)&ptQTask[238].eQTaskType + 52) = ptQTask[1].tQTaskChildren.ptMiddle;
  *(_DWORD *)(*(_DWORD *)&ptQTask[238].eQTaskType + 40) = ptQTask[1].ptNext;
  *(_DWORD *)(*(_DWORD *)&ptQTask[238].eQTaskType + 44) = ptQTask[1].ptPrev;
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[228].tQTaskRefList.ptTail, ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[230].tQTaskRefList.ptTail, ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[232].tQTaskRefList.ptTail, ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[234].tQTaskRefList.ptTail, ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[236].tQTaskRefList.ptTail, ptQTask);
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][ptQTask[238].ptParent->eQTaskType].pfHandler)(
    ptQTask[238].ptParent,
    pxContext);
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][MenuWindow_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
}

// source: j/0/menusystem/scrolllistbox.c:328  [anchor-caller]
void __cdecl ScrollListBox_RunHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v20; };
    struct { char igi2_o1[4]; struct QTask_s *v21; };
    struct { char igi2_o2[8]; int nHeight; };
    struct { char igi2_o3[12]; int v23; };
    struct { char igi2_o4[16]; struct QTask_s *ptPrev; };
    struct { char igi2_o5[20]; int nWidth[2]; };
    char igi2_extent[28];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v1; // esi
  struct MenuWindow_t *v2; // ebx
  struct QTask_s *ptParent; // eax
  struct QTask_s *v4; // ecx
  struct QTask_s *v5; // eax
  struct Flow_t *v6; // ecx
  struct QTask_s *ptMiddle; // eax
  struct QTask_s *nTicks; // esi
  int i; // edx
  int v10; // eax
  struct QReference_s *v11; // eax
  struct QTask_s *v12; // eax
  struct QTask_s *v13; // eax
  struct QTask_s *v14; // eax
  struct QTask_s *v15; // eax
  bool v16; // cc
  struct QReference_s *v17; // eax
  struct QReference_s *v18; // eax
  struct QTask_s *v19; // eax

  v1 = *(struct QTask_s **)&ptQTask[1].eQTaskType;
  v2 = *(struct MenuWindow_t **)&ptQTask[238].eQTaskType;
  igi2_frame.v21 = v1;
  igi2_frame.v23 = (int)&ptQTask[1].tQTaskChildren.ptMiddle[-1].eQTaskType / (int)ptQTask[238].tQTaskRefList.ptTail;
  igi2_frame.ptPrev = ptQTask[228].ptPrev;
  if ( ptQTask[228].tQTaskChildren.ptTail )
  {
    ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[MenuWindow_eInitDataEvent][ptQTask->eQTaskType].pfHandler)(ptQTask);
    ptQTask[228].tQTaskChildren.ptTail = nullptr;
  }
  if ( BYTE2(ptQTask[228].tQTaskRefList.ptHead)
    && (((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][ptQTask[238].ptParent->eQTaskType].pfHandler)(ptQTask[238].ptParent),
        ptParent = ptQTask[238].ptParent,
        (v4 = ptParent[16].ptParent) != nullptr) )
  {
    *(_QWORD *)igi2_frame.nWidth = (__int64)((double)(int)(&v4[-1].isInMemPool + 1) * *(double *)&ptParent[4].tQTaskChildren.ptHead
                                + 0.5);
    igi2_frame.v20 = igi2_frame.nWidth[0];
  }
  else
  {
    igi2_frame.v20 = 0;
  }
  if ( (int)ptQTask[226].tQTaskChildren.ptMiddle > 0 )
  {
    MenuWindow_HitTest(v2, v2->nXPos, v2->nYPos, v2->nWidth, v2->nHeight, igi2_frame.nWidth, &igi2_frame.nHeight);
    if ( v2->isClicked )
    {
      v5 = (struct QTask_s *)(igi2_frame.v20 + (igi2_frame.nHeight - v2->nYPos) / (int)ptQTask[238].tQTaskRefList.ptTail);
      if ( v5 == ptQTask[228].ptPrev || (int)v5 >= (int)ptQTask[226].tQTaskChildren.ptMiddle )
      {
        ptMiddle = ptQTask[228].tQTaskChildren.ptMiddle;
        nTicks = (struct QTask_s *)Flow_ptFlow->nTicks;
        if ( ptMiddle != (struct QTask_s *)-1 )
        {
          *(_QWORD *)igi2_frame.nWidth = (__int64)((double)Flow_ptFlow->nFrequency * 0.5);
          if ( (char *)nTicks - (char *)ptMiddle < igi2_frame.nWidth[0] )
          {
            if ( Level_LevelExpressionDefined((struct LevelExpression_s *)&ptQTask[234].tQTaskRefList.ptTail) )
              Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[234].tQTaskRefList.ptTail, ptQTask);
          }
        }
        ptQTask[228].tQTaskChildren.ptMiddle = nTicks;
      }
      else
      {
        v6 = Flow_ptFlow;
        ptQTask[228].ptPrev = v5;
        ptQTask[228].tQTaskChildren.ptMiddle = (struct QTask_s *)v6->nTicks;
      }
    }
    v1 = igi2_frame.v21;
  }
  if ( HIBYTE(ptQTask[228].tQTaskRefList.ptHead) )
  {
    for ( i = tKeyboardBuffer.nBuffer; tKeyboardBuffer.nBuffer; i = tKeyboardBuffer.nBuffer )
    {
      v10 = 0;
      if ( i )
      {
        v10 = tKeyboardBuffer.anBuffer[tKeyboardBuffer.iBufferIndex++];
        if ( tKeyboardBuffer.iBufferIndex == 32 )
          tKeyboardBuffer.iBufferIndex = 0;
        tKeyboardBuffer.nBuffer = i - 1;
      }
      LOBYTE(ptQTask[228].tQTaskRefList.ptHead) = 1;
      switch ( v10 )
      {
        case -11:
          v17 = (struct QReference_s *)v1[255].ptParent;
          if ( v17 )
          {
            QReference_Delete(v17, &QTask_tQTaskRefPool);
            v1[255].ptParent = nullptr;
          }
          HIBYTE(ptQTask[228].tQTaskRefList.ptHead) = 0;
          MenuManager_GotoNextTAB(v1);
          break;
        case -8:
          v11 = (struct QReference_s *)v1[255].ptParent;
          if ( v11 )
          {
            QReference_Delete(v11, &QTask_tQTaskRefPool);
            v1[255].ptParent = nullptr;
          }
          HIBYTE(ptQTask[228].tQTaskRefList.ptHead) = 0;
          MenuManager_ExitTAB(v1);
          break;
        case -7:
          if ( ptQTask[234].tQTaskRefList.ptTail && ptQTask[234].ptParent->ptNext && *(_DWORD *)&ptQTask[234].eQTaskType )
            Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[234].tQTaskRefList.ptTail, ptQTask);
          break;
        case -4:
          v14 = ptQTask[228].ptPrev;
          if ( (int)v14 < (int)(&ptQTask[226].tQTaskChildren.ptMiddle[-1].isInMemPool + 1) )
          {
            v15 = (struct QTask_s *)((char *)&v14->ptNext + 1);
            v16 = (int)v15 < igi2_frame.v23 + igi2_frame.v20;
            ptQTask[228].ptPrev = v15;
            if ( !v16 )
              SlideBar_SetIntValue((struct MenuWindow_t *)ptQTask[238].ptParent, igi2_frame.v20 + 1);
          }
          break;
        case -3:
          v12 = ptQTask[228].ptPrev;
          if ( (int)v12 > 0 )
          {
            v13 = (struct QTask_s *)((char *)v12 - 1);
            ptQTask[228].ptPrev = v13;
            if ( (int)v13 < igi2_frame.v20 )
              SlideBar_SetIntValue((struct MenuWindow_t *)ptQTask[238].ptParent, igi2_frame.v20 - 1);
          }
          break;
        default:
          continue;
      }
    }
  }
  if ( HIBYTE(ptQTask[2].ptPrev) )
  {
    if ( !HIBYTE(ptQTask[228].tQTaskRefList.ptHead) )
      LOBYTE(ptQTask[228].tQTaskRefList.ptHead) = 1;
    HIBYTE(ptQTask[228].tQTaskRefList.ptHead) = 1;
    v18 = (struct QReference_s *)v1[255].ptParent;
    if ( v18 )
    {
      QReference_Delete(v18, &QTask_tQTaskRefPool);
      v1[255].ptParent = nullptr;
    }
    v1[255].ptParent = (struct QTask_s *)QTask_NewQTaskRef(ptQTask);
  }
  v19 = ptQTask[228].ptPrev;
  ptQTask[228].tQTaskChildren.ptHead = *(&ptQTask[2].tQTaskChildren.ptMiddle + 35 * (_DWORD)v19);
  if ( igi2_frame.ptPrev != v19 )
  {
    if ( ptQTask[236].tQTaskRefList.ptTail && ptQTask[236].ptParent->ptNext && *(_DWORD *)&ptQTask[236].eQTaskType )
      Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[236].tQTaskRefList.ptTail, ptQTask);
    SoundSys_PlaySimpleSoundFn("menu_sel2", 0, nullptr);
  }
  if ( LOBYTE(ptQTask[228].tQTaskRefList.ptHead) )
  {
    LOBYTE(ptQTask[228].tQTaskRefList.ptHead) = 0;
    ScrollListBox_ForceVisible(ptQTask);
  }
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][MenuWindow_eQTaskType].pfHandler)(ptQTask);
}

// source: j/0/menusystem/scrolllistbox.c:515  [size]
void __cdecl ScrollListBox_DrawHandler(struct QTask_s *ptQTask)
{
  double v2; // st7
  int v3; // eax
  struct QTask_s *ptMiddle; // edx
  int v5; // ebx
  struct QTask_s *ptNext; // ecx
  struct QTask_s *ptParent; // eax
  struct QTask_s *v8; // edx
  int v9; // eax
  struct QTask_s *ptPrev; // ebp
  char *v11; // ebp
  int v12; // edi
  struct QReference_s *v13; // eax
  __int16 *v14; // edx
  struct QReference_s *v15; // ebx
  struct QTilemap_s *v16; // ebp
  unsigned __int8 v17; // cl
  int v18; // eax
  struct QReference_s *v19; // edi
  int v20; // edx
  struct QReference_s *v21; // edx
  float b; // ecx
  struct QReference_s *v23; // eax
  float vX; // [esp+0h] [ebp-58h]
  float vY; // [esp+4h] [ebp-54h]
  float vWidth; // [esp+8h] [ebp-50h]
  float vHeight; // [esp+Ch] [ebp-4Ch]
  float vFade; // [esp+38h] [ebp-20h]
  struct QReference_s **v29; // [esp+3Ch] [ebp-1Ch]
  int nEntry; // [esp+40h] [ebp-18h]
  int nX; // [esp+44h] [ebp-14h]
  int iEntry; // [esp+48h] [ebp-10h]
  struct QReference_s *v33; // [esp+4Ch] [ebp-Ch]
  int nSelected; // [esp+50h] [ebp-8h]
  struct QTask_s *ptQTaska = *(struct QTask_s * *)&ptQTask; // [esp+5Ch] [ebp+4h] ARGSLOT

  v2 = (double)(*(_DWORD *)(*(_DWORD *)&ptQTask[1].eQTaskType + 356) - 8) * 0.125;
  if ( v2 <= 0.0 )
    vFade = 0.0;
  else
    vFade = v2;
  v3 = (int)&ptQTask[1].tQTaskChildren.ptMiddle[-1].eQTaskType / (int)ptQTask[238].tQTaskRefList.ptTail;
  ptMiddle = ptQTask[226].tQTaskChildren.ptMiddle;
  v5 = (int)ptMiddle;
  if ( (int)ptMiddle >= v3 )
    v5 = (int)&ptQTask[1].tQTaskChildren.ptMiddle[-1].eQTaskType / (int)ptQTask[238].tQTaskRefList.ptTail;
  ptNext = ptQTask[1].ptNext;
  nX = (int)&ptNext[-8] + (Display_tActiveMode.nWidth >> 1);
  nEntry = v5;
  ptQTaska = (struct QTask_s *)((char *)ptQTask[1].ptPrev + (Display_tActiveMode.nHeight >> 1) - 238);
  if ( v3 < (int)ptMiddle && (ptParent = ptQTask[238].ptParent, (v8 = ptParent[16].ptParent) != nullptr) )
    v9 = (__int64)((double)(int)(&v8[-1].isInMemPool + 1) * *(double *)&ptParent[4].tQTaskChildren.ptHead + 0.5);
  else
    v9 = 0;
  ptPrev = ptQTask[228].ptPrev;
  *(_DWORD *)(*(_DWORD *)&ptQTask[238].eQTaskType + 40) = ptNext;
  v11 = (char *)ptPrev - v9;
  v12 = 0;
  nSelected = (int)v11;
  *(_DWORD *)(*(_DWORD *)&ptQTask[238].eQTaskType + 44) = ptQTask[1].ptPrev;
  iEntry = 0;
  if ( v5 > 0 )
  {
    v29 = &ptQTask[5].tQTaskRefList.ptMiddle + 35 * v9;
    do
    {
      v13 = ptQTask[228].tQTaskRefList.ptMiddle;
      v33 = v13;
      if ( v13 )
      {
        v14 = (__int16 *)v13->ptNext;
        v15 = *v29;
        memset(v13->ptNext[1].ptNext, 0, 2 * SHIWORD(v13->ptNext->ptPrev));
        memset(v14 + 8, 0, v14[3] * v14[2]);
        v16 = (struct QTilemap_s *)v13->ptNext;
        v17 = (unsigned __int8)v15->ptNext;
        v18 = *((_DWORD *)v13->ptNext->pxObject + 3) + 16;
        v19 = v15;
        if ( LOBYTE(v15->ptNext) )
        {
          v20 = (char *)&v33->ptNext[1].ptPrev - (char *)v15;
          do
          {
            *((_BYTE *)&v19->ptNext + v20) = *(_BYTE *)(v17 + v18);
            v17 = BYTE1(v19->ptNext);
            v19 = (struct QReference_s *)((char *)v19 + 1);
          }
          while ( v17 );
        }
        QTilemap_UpdateGraphicWidth(v16, 0);
        v12 = iEntry;
        v11 = (char *)nSelected;
        *(float *)&ptQTask[228].tQTaskRefList.ptMiddle->ptPrev = (float)(nX + 4);
        *(float *)&ptQTask[228].tQTaskRefList.ptMiddle->pxObject = (float)(int)ptQTaska;
        v21 = ptQTask[228].tQTaskRefList.ptMiddle;
        if ( iEntry == nSelected )
        {
          v21[1].pxObject = (void *)LODWORD(MenuText_atTextColour[4].r);
          ptQTask[228].tQTaskRefList.ptMiddle[2].ptNext = (struct QReference_s *)LODWORD(MenuText_atTextColour[4].g);
          b = MenuText_atTextColour[4].b;
        }
        else
        {
          v21[1].pxObject = (void *)LODWORD(MenuText_atTextColour[2].r);
          ptQTask[228].tQTaskRefList.ptMiddle[2].ptNext = (struct QReference_s *)LODWORD(MenuText_atTextColour[2].g);
          b = MenuText_atTextColour[2].b;
        }
        *(float *)&ptQTask[228].tQTaskRefList.ptMiddle[2].ptPrev = b;
        ptQTask[228].tQTaskRefList.ptMiddle[3].ptNext = (struct QReference_s *)((int)ptQTask[228].tQTaskRefList.ptMiddle[3].ptNext
                                                                              | 0x80000);
        *(float *)&ptQTask[228].tQTaskRefList.ptMiddle[1].ptPrev = vFade;
        v23 = ptQTask[228].tQTaskRefList.ptMiddle;
        QTilemap_Register(
          (struct QTilemap_s *)v23->ptNext,
          *(float *)&v23->ptPrev,
          *(float *)&v23->pxObject,
          *(float *)&v23[1].pxObject,
          *(float *)&v23[2].ptNext,
          *(float *)&v23[2].ptPrev,
          *(float *)&v23[1].ptPrev,
          *(float *)&v23[1].ptNext,
          (int)v23[3].ptNext | 0x40000000,
          (int)v23[2].pxObject);
        v5 = nEntry;
      }
      if ( (char *)v12 == v11 )
      {
        vHeight = (float)(int)ptQTask[238].tQTaskRefList.ptTail;
        vWidth = (double)*(int *)(*(_DWORD *)&ptQTask[238].eQTaskType + 48) - 4.0;
        vY = (float)(int)ptQTaska;
        vX = (double)nX + 2.0;
        QSprite_RegisterBlankA(vX, vY, vWidth, vHeight, 15.359999656677246, 35.84000015258789, 98.55999755859375, vFade, 0x80000u, 0);
      }
      ++v12;
      ptQTaska = (struct QTask_s *)((char *)ptQTaska + (unsigned int)ptQTask[238].tQTaskRefList.ptTail);
      iEntry = v12;
      v29 += 35;
    }
    while ( v12 < v5 );
  }
  if ( BYTE2(ptQTask[228].tQTaskRefList.ptHead) )
    ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Screen_eDrawQTaskEvent][ptQTask[238].ptParent->eQTaskType].pfHandler)(ptQTask[238].ptParent);
  MenuWindow_DrawBorder(
    *(struct MenuWindow_t **)&ptQTask[238].eQTaskType,
    0.5,
    vFade,
    SHIBYTE(ptQTask[228].tQTaskRefList.ptHead));
}

// source: j/0/menusystem/scrolllistbox.c:614  [size]
void __cdecl ScrollListBox_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = ScrollListBox_ptParameterList;
}

// source: j/0/menusystem/scrolllistbox.c:630  [anchor-caller]
void __cdecl ScrollListBox_InitDataHandler(struct QTask_s *ptQTask)
{
  struct QReference_s *ptTail; // ecx
  struct QTask_s *ptMiddle; // eax
  int v3; // ebx
  struct QTask_s **p_ptTail; // edi
  struct QExpression_s *v5; // ebx
  struct QTask_s *v6; // edi
  struct QTask_s *v7; // eax
  struct QTask_s **p_ptMiddle; // ecx
  struct QTask_s *v9; // eax
  int v10; // ebx
  int v11; // edi
  struct MemPoolFreeItem_s *v12; // eax
  struct QTask_s *ptParent; // ecx
  struct QTask_s *v14; // eax
  char *v15; // edx
  struct QTask_s *v16; // ecx
  struct QTask_s *v17; // ebx
  struct QTask_s *ptPrev; // edi
  int v19; // eax
  struct QTask_s *ptHead; // ecx
  int v21; // edx
  struct QTask_s *v22; // eax
  int v23; // edi
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v25; // edx
  struct QTask_s *v26; // ecx
  struct QExpression_s *v27; // ebx
  double nSlideBarWidth; // [esp+10h] [ebp-8h]
  __int64 nSlideBarWidtha; // [esp+10h] [ebp-8h]
  int nSlideBarWidthb; // [esp+10h] [ebp-8h]
  int nSlideBarWidthc; // [esp+10h] [ebp-8h]

  ScrollListBox_DeleteEntries((struct ScrollListBox_t *)ptQTask);
  ptTail = ptQTask[228].tQTaskRefList.ptTail;
  ScrollListBox_ptActiveScrollListBox = (struct ScrollListBox_t *)ptQTask;
  if ( ptTail && ptQTask[228].ptParent->ptNext && *(_DWORD *)&ptQTask[228].eQTaskType )
    Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[228].tQTaskRefList.ptTail, ptQTask);
  ptMiddle = ptQTask[226].tQTaskChildren.ptMiddle;
  v3 = 0;
  ScrollListBox_ptActiveScrollListBox = nullptr;
  if ( (int)ptMiddle > 0 )
  {
    p_ptTail = &ptQTask[2].tQTaskChildren.ptTail;
    do
    {
      if ( p_ptTail[33] )
        p_ptTail[32] = (struct QTask_s *)Config_GetLocalizedStringForLanguage(
                                           (char *)p_ptTail,
                                           Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                           true);
      else
        p_ptTail[32] = (struct QTask_s *)p_ptTail;
      ++v3;
      p_ptTail += 35;
    }
    while ( v3 < (int)ptQTask[226].tQTaskChildren.ptMiddle );
  }
  if ( !ptQTask[230].tQTaskRefList.ptTail || !ptQTask[230].ptParent->ptNext || !*(_DWORD *)&ptQTask[230].eQTaskType )
    goto LABEL_23;
  nSlideBarWidth = 0.0;
  if ( !ptQTask[230].ptParent
    || (Level_ValidateLevelExpression((struct LevelExpression_s *)&ptQTask[230].tQTaskRefList.ptTail),
        !ptQTask[230].ptParent) )
  {
    Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[230].tQTaskRefList.ptTail, ptQTask);
  }
  v5 = *(struct QExpression_s **)&ptQTask[230].eQTaskType;
  if ( v5 )
    nSlideBarWidth = Expression_EvalFloat(v5);
  v6 = ptQTask[226].tQTaskChildren.ptMiddle;
  nSlideBarWidtha = (__int64)nSlideBarWidth;
  v7 = nullptr;
  if ( (int)v6 > 0 )
  {
    p_ptMiddle = &ptQTask[2].tQTaskChildren.ptMiddle;
    while ( (struct QTask_s *)nSlideBarWidtha != *p_ptMiddle )
    {
      v7 = (struct QTask_s *)((char *)v7 + 1);
      p_ptMiddle += 35;
      if ( (int)v7 >= (int)ptQTask[226].tQTaskChildren.ptMiddle )
        goto LABEL_23;
    }
    ptQTask[228].ptPrev = v7;
    ptQTask[228].tQTaskChildren.ptHead = (struct QTask_s *)nSlideBarWidtha;
  }
  else
  {
LABEL_23:
    v6 = ptQTask[226].tQTaskChildren.ptMiddle;
    v9 = nullptr;
    ptQTask[228].ptPrev = nullptr;
    if ( v6 )
      v9 = ptQTask[2].tQTaskChildren.ptMiddle;
    ptQTask[228].tQTaskChildren.ptHead = v9;
  }
  v10 = (int)&ptQTask[1].tQTaskChildren.ptMiddle[-1].eQTaskType / (int)ptQTask[238].tQTaskRefList.ptTail;
  BYTE2(ptQTask[228].tQTaskRefList.ptHead) = v10 < (int)v6;
  if ( v10 >= (int)v6 )
  {
    v19 = 0;
  }
  else
  {
    v11 = *(_DWORD *)&ptQTask[1].eQTaskType;
    v12 = *(struct MemPoolFreeItem_s **)(v11 + 10236);
    ptParent = ptQTask[238].ptParent;
    nSlideBarWidthb = (int)ptParent;
    if ( v12 )
    {
      if ( v12->ptNext )
      {
        v12 = (struct MemPoolFreeItem_s *)Node_Remove(v12);
        ptParent = (struct QTask_s *)nSlideBarWidthb;
      }
      --QTask_tQTaskRefPool.nAllocatedBlocks;
      v12->ptNext = QTask_tQTaskRefPool.tMemPoolFreeList.ptHead;
      QTask_tQTaskRefPool.tMemPoolFreeList.ptHead = v12;
      *(_DWORD *)(v11 + 10236) = 0;
    }
    if ( ptParent )
      *(_DWORD *)(v11 + 10236) = QTask_NewQTaskRef(ptParent);
    v14 = ptQTask[238].ptParent;
    v15 = (char *)ptQTask[226].tQTaskChildren.ptMiddle - v10;
    nSlideBarWidthc = (int)v14[1].tQTaskChildren.ptHead;
    v16 = ptQTask[1].tQTaskChildren.ptMiddle;
    v17 = (struct QTask_s *)((char *)ptQTask[1].ptNext + (unsigned int)ptQTask[1].tQTaskChildren.ptHead
                                                       - nSlideBarWidthc);
    v14[1].ptPrev = ptQTask[1].ptPrev;
    ptPrev = v14[4].ptPrev;
    v14[1].tQTaskChildren.ptMiddle = v16;
    v14[1].ptNext = v17;
    v14[4].tQTaskRefList.ptHead = (struct QReference_s *)((char *)v16
                                                        - (char *)ptPrev[1].tQTaskChildren.ptMiddle
                                                        - (unsigned int)v14[4].ptNext[1].tQTaskChildren.ptMiddle
                                                        - 6);
    v14[16].ptParent = (struct QTask_s *)(v15 + 1);
    v19 = nSlideBarWidthc + 2;
  }
  *(_DWORD *)(*(_DWORD *)&ptQTask[238].eQTaskType + 40) = ptQTask[1].ptNext;
  *(_DWORD *)(*(_DWORD *)&ptQTask[238].eQTaskType + 44) = ptQTask[1].ptPrev;
  *(_DWORD *)(*(_DWORD *)&ptQTask[238].eQTaskType + 52) = ptQTask[1].tQTaskChildren.ptMiddle;
  *(_DWORD *)(*(_DWORD *)&ptQTask[238].eQTaskType + 48) = (char *)ptQTask[1].tQTaskChildren.ptHead - v19;
  ptHead = ptQTask->tQTaskChildren.ptHead;
  HIBYTE(ptQTask[228].tQTaskRefList.ptHead) = 0;
  ptQTask[228].tQTaskChildren.ptMiddle = (struct QTask_s *)-1;
  if ( ptHead->ptNext && ptHead )
  {
    v21 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v22 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v22 = nullptr;
      v23 = MenuWindow_eInitDataEvent;
      QTask_atProtectedQTaskStack[v21].ptQTask = v22;
      pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[v23][ptHead->eQTaskType].pfHandler;
      v25 = v21 + 1;
      QTask_nProtectedQTaskStackOffset = v25;
      if ( pfHandler )
      {
        pfHandler(ptHead);
        v25 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v25];
      v21 = v25 - 1;
      QTask_nProtectedQTaskStackOffset = v21;
    }
    while ( ptHead );
  }
  if ( (int)ptQTask[226].tQTaskChildren.ptMiddle > 0 )
  {
    if ( ptQTask[236].tQTaskRefList.ptTail )
    {
      v26 = ptQTask[236].ptParent;
      if ( LOBYTE(v26->ptNext) )
      {
        if ( *(_DWORD *)&ptQTask[236].eQTaskType )
        {
          if ( !v26
            || (Level_ValidateLevelExpression((struct LevelExpression_s *)&ptQTask[236].tQTaskRefList.ptTail),
                !ptQTask[236].ptParent) )
          {
            Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[236].tQTaskRefList.ptTail, ptQTask);
          }
          v27 = *(struct QExpression_s **)&ptQTask[236].eQTaskType;
          if ( v27 )
            Expression_EvalFloat(v27);
        }
      }
    }
  }
  LOBYTE(ptQTask[228].tQTaskRefList.ptHead) = 1;
}

// source: j/0/menusystem/scrolllistbox.c:750  [size]
void __cdecl ScrollListBox_ChangeDataHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // ecx
  int v2; // edx
  struct QTask_s *v3; // eax
  int v4; // esi
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v6; // edx

  if ( ptQTask[232].tQTaskRefList.ptTail && ptQTask[232].ptParent->ptNext && *(_DWORD *)&ptQTask[232].eQTaskType )
    Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[232].tQTaskRefList.ptTail, ptQTask);
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

// source: j/0/menusystem/scrolllistbox.c:775  [size]
void __cdecl ScrollListBox_RegisterScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( !BYTE1(ptQTask[228].tQTaskRefList.ptHead) )
  {
    BYTE1(ptQTask[228].tQTaskRefList.ptHead) = 1;
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.nActiveID", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int,
      &ptQTask[228].tQTaskChildren,
      4,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.isUpdate", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int,
      &ptQTask[228].tQTaskChildren.ptTail,
      4,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.nActiveEntry", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int,
      &ptQTask[228].ptPrev,
      4,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
  }
}

// source: j/0/menusystem/scrolllistbox.c:810  [size]
void __cdecl ScrollListBox_RemoveScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( BYTE1(ptQTask[228].tQTaskRefList.ptHead) )
  {
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.nActiveID", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.isUpdate", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.nActiveEntry", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    BYTE1(ptQTask[228].tQTaskRefList.ptHead) = 0;
  }
}

// source: j/0/menusystem/scrolllistbox.c:848  [anchor-callee]
void __cdecl ScrollListBox_AddItemEx(char *zItemName, int nItemID, enum bool isTranslated)
{
  int *p_nEntries; // esi
  struct ScrollListBoxItem_t *v4; // edi
  int v5; // ecx
  struct ScrollListBoxItem_t *atScrollListBoxItem; // eax

  p_nEntries = &ScrollListBox_ptActiveScrollListBox->nEntries;
  v4 = &ScrollListBox_ptActiveScrollListBox->atScrollListBoxItem[ScrollListBox_ptActiveScrollListBox->nEntries];
  v5 = 0;
  if ( ScrollListBox_ptActiveScrollListBox->nEntries <= 0 )
  {
LABEL_5:
    v4->nItemID = nItemID;
    strncpy(v4->zItem, zItemName, 0x80u);
    v4->isTranslated = isTranslated;
    ++*p_nEntries;
  }
  else
  {
    atScrollListBoxItem = ScrollListBox_ptActiveScrollListBox->atScrollListBoxItem;
    while ( atScrollListBoxItem->nItemID != nItemID )
    {
      ++v5;
      ++atScrollListBoxItem;
      if ( v5 >= *p_nEntries )
        goto LABEL_5;
    }
  }
}

// source: j/0/menusystem/scrolllistbox.c:903  [anchor-hash]
char *__cdecl ScrollListBox_AddItem(char *zItemName, int nItemID)
{
  char *result; // eax

  ScrollListBox_AddItemEx(zItemName, nItemID, true);
  return result;
}

// source: j/0/menusystem/scrolllistbox.c:919  [anchor-hash]
enum bool __cdecl ScrollListBox_IsFull()
{
  return ScrollListBox_ptActiveScrollListBox->nEntries == 64;
}

// source: j/0/menusystem/scrolllistbox.c:935  [anchor-hash]
void __cdecl ScrollListBox_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // edx

  v0 = QTask_NewQTaskType("ScrollListBox", 9560, MenuWindow_eQTaskType, 0, 0);
  ScrollListBox_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, ScrollListBox_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Screen_eDrawQTaskEvent, ScrollListBox_DrawHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, ScrollListBox_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, ScrollListBox_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))ScrollListBox_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eUpdateInternalDataQTaskEvent,
    ScrollListBox_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, MenuWindow_eInitDataEvent, ScrollListBox_InitDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, MenuWindow_eChangeDataEvent, ScrollListBox_ChangeDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eRegisterLevelScriptSymbolsEvent,
    ScrollListBox_RegisterScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eRemoveLevelScriptSymbolsEvent,
    ScrollListBox_RemoveScriptSymbolsHandler);
  v1 = (struct ParameterList_s *)Mem_AllocFn(172, 4);
  v2 = Level_eParameterTypeString32;
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  v1->nParameters = 0;
  v1->nMaxParameters = 8;
  ScrollListBox_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0x2364u, v2, "Font Resource", 7u, nullptr);
  ParameterList_AddParameter(
    ScrollListBox_ptParameterList,
    0x23BCu,
    Level_eParameterTypeVarString,
    "Collect Items Script",
    7u,
    nullptr);
  ParameterList_AddParameter(
    ScrollListBox_ptParameterList,
    0x240Cu,
    Level_eParameterTypeVarString,
    "Get Data Script",
    7u,
    nullptr);
  ParameterList_AddParameter(
    ScrollListBox_ptParameterList,
    0x245Cu,
    Level_eParameterTypeVarString,
    "Set Data Script",
    7u,
    nullptr);
  ParameterList_AddParameter(ScrollListBox_ptParameterList, 0x30u, Level_eParameterTypeInt32, "Width", 7u, nullptr);
  ParameterList_AddParameter(ScrollListBox_ptParameterList, 0x34u, Level_eParameterTypeInt32, "Height", 7u, nullptr);
  ParameterList_AddParameter(
    ScrollListBox_ptParameterList,
    0x24ACu,
    Level_eParameterTypeVarString,
    "On Select Item",
    7u,
    nullptr);
  ParameterList_AddParameter(
    ScrollListBox_ptParameterList,
    0x24FCu,
    Level_eParameterTypeVarString,
    "On Focus Item",
    7u,
    nullptr);
}

// source: j/0/menusystem/scrolllistbox.c:979  [size]
void __cdecl ScrollListBox_Close()
{
  int v0; // esi

  if ( ScrollListBox_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&ScrollListBox_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(ScrollListBox_eQTaskType);
  ScrollListBox_eQTaskType = 512;
}
