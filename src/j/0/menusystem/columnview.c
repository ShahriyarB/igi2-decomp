/* j/0/menusystem/columnview.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/menusystem/columnview.c:123  [anchor-hash]
struct QTask_s *__cdecl ColumnView_ForceVisible(struct QTask_s *ptQTask)
{
  struct QTask_s *result; // eax
  int v3; // ecx
  struct QTask_s *v4; // ebp
  BOOL v5; // ebx
  int v6; // ecx
  int v7; // edx
  int v8; // esi
  struct QTask_s *ptMiddle; // edx
  int v10; // ecx
  int v11; // edi

  result = (struct QTask_s *)((int)&ptQTask[1].tQTaskChildren.ptMiddle[-1].eQTaskType / (int)ptQTask[18].ptParent);
  v3 = *(_DWORD *)&ptQTask[2].tQTaskChildren.ptMiddle->eQTaskType;
  v4 = (struct QTask_s *)v3;
  if ( v3 >= (int)result )
    v4 = result;
  v5 = (int)result < v3;
  if ( (int)result < v3 && (v6 = *(_DWORD *)&ptQTask[18].eQTaskType, (v7 = *(_DWORD *)(v6 + 672)) != 0) )
    v8 = (__int64)((double)(v7 - 1) * *(double *)(v6 + 168) + 0.5);
  else
    v8 = 0;
  ptMiddle = ptQTask[4].tQTaskChildren.ptMiddle;
  v10 = (int)ptMiddle - v8;
  if ( v5 )
  {
    if ( v10 >= 0 )
    {
      if ( v10 < (int)v4 )
        return result;
      if ( v10 > 0 )
        ptMiddle = (struct QTask_s *)((char *)ptMiddle - (char *)result + 1);
    }
    v11 = *(_DWORD *)&ptQTask[18].eQTaskType;
    result = *(struct QTask_s **)(v11 + 672);
    if ( result )
      *(double *)(v11 + 168) = ((double)(int)ptMiddle + 0.5) / (double)*(int *)(v11 + 672);
  }
  return result;
}

// source: j/0/menusystem/columnview.c:156  [anchor-mhash]
void __cdecl ColumnView_DeleteEntries(struct ColumnView_s *ptColumnView)
{
  int v1; // ecx
  struct QObjectVector_s *ptEntryIDVector; // eax
  unsigned int nAllocated; // ecx
  unsigned int *p_nAllocated; // eax
  int v5; // esi
  unsigned int v6; // edi
  struct QTask_s *ptHead; // eax
  int nEntryID; // edi
  struct QTask_s *v9; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, struct ColumnViewDeleteEntryContext_s *); // ecx
  int v11; // esi
  struct QObjectVector_s *v12; // eax
  unsigned int v13; // ecx
  struct ColumnViewDeleteEntryContext_s tColumnViewDeleteEntryContext; // [esp+0h] [ebp-4h] BYREF

  tColumnViewDeleteEntryContext.nEntryID = v1;
  ptEntryIDVector = ptColumnView->ptEntryIDVector;
  nAllocated = ptEntryIDVector->nAllocated;
  p_nAllocated = &ptEntryIDVector->nAllocated;
  if ( nAllocated )
  {
    v5 = QTask_nProtectedQTaskStackOffset;
    do
    {
      v6 = *p_nAllocated;
      ptHead = ptColumnView->tMenuWindow.tQTask.tQTaskChildren.ptHead;
      nEntryID = v6 - 1;
      tColumnViewDeleteEntryContext.nEntryID = nEntryID;
      if ( ptHead->ptNext && ptHead )
      {
        do
        {
          if ( ptHead->ptNext )
            v9 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
          else
            v9 = nullptr;
          QTask_atProtectedQTaskStack[v5].ptQTask = v9;
          pfHandler = (void (__cdecl *)(struct QTask_s *, struct ColumnViewDeleteEntryContext_s *))QTask_aatQTaskFinalEvent[ColumnView_eDeleteEntryQTaskEvent][ptHead->eQTaskType].pfHandler;
          v11 = v5 + 1;
          QTask_nProtectedQTaskStackOffset = v11;
          if ( pfHandler )
          {
            pfHandler(ptHead, &tColumnViewDeleteEntryContext);
            nEntryID = tColumnViewDeleteEntryContext.nEntryID;
            v11 = QTask_nProtectedQTaskStackOffset;
          }
          ptHead = (struct QTask_s *)dword_849C7DC[v11];
          v5 = v11 - 1;
          QTask_nProtectedQTaskStackOffset = v5;
        }
        while ( ptHead );
      }
      QObjectVector_RemoveElement(ptColumnView->ptEntryIDVector, nEntryID);
      v12 = ptColumnView->ptEntryIDVector;
      v13 = v12->nAllocated;
      p_nAllocated = &v12->nAllocated;
    }
    while ( v13 );
  }
}

// source: j/0/menusystem/columnview.c:180  [anchor-mhash]
void __cdecl ColumnView_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  unsigned __int16 v2; // ax
  struct QTask_s *v3; // eax
  struct QTask_s *v4; // eax
  void *v5; // [esp-Ch] [ebp-18h]

  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][MenuWindow_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  ptQTask[2].tQTaskChildren.ptTail = nullptr;
  ptQTask[2].tQTaskRefList.ptHead = nullptr;
  ptQTask[4].tQTaskChildren.ptHead = nullptr;
  ptQTask[4].ptParent = nullptr;
  *(_DWORD *)&ptQTask[4].eQTaskType = 0;
  ptQTask[5].ptNext = nullptr;
  ptQTask[6].tQTaskRefList.ptTail = nullptr;
  ptQTask[6].ptParent = nullptr;
  *(_DWORD *)&ptQTask[6].eQTaskType = 0;
  ptQTask[7].ptNext = nullptr;
  ptQTask[8].tQTaskRefList.ptTail = nullptr;
  ptQTask[8].ptParent = nullptr;
  *(_DWORD *)&ptQTask[8].eQTaskType = 0;
  ptQTask[9].ptNext = nullptr;
  ptQTask[10].tQTaskRefList.ptTail = nullptr;
  ptQTask[10].ptParent = nullptr;
  *(_DWORD *)&ptQTask[10].eQTaskType = 0;
  ptQTask[11].ptNext = nullptr;
  ptQTask[12].tQTaskRefList.ptTail = nullptr;
  ptQTask[12].ptParent = nullptr;
  *(_DWORD *)&ptQTask[12].eQTaskType = 0;
  ptQTask[13].ptNext = nullptr;
  ptQTask[14].tQTaskRefList.ptTail = nullptr;
  ptQTask[14].ptParent = nullptr;
  *(_DWORD *)&ptQTask[14].eQTaskType = 0;
  ptQTask[15].ptNext = nullptr;
  ptQTask[16].tQTaskRefList.ptTail = nullptr;
  ptQTask[16].ptParent = nullptr;
  *(_DWORD *)&ptQTask[16].eQTaskType = 0;
  ptQTask[17].ptNext = nullptr;
  ptQTask[18].tQTaskRefList.ptTail = nullptr;
  ptQTask[1].tQTaskChildren.ptHead = (struct QTask_s *)100;
  ptQTask[1].tQTaskChildren.ptMiddle = (struct QTask_s *)100;
  v5 = *(void **)&ptQTask[1].eQTaskType;
  v2 = SlideBar_eQTaskType;
  BYTE1(ptQTask[4].tQTaskRefList.ptTail) = 0;
  ptQTask[4].tQTaskRefList.ptMiddle = nullptr;
  LOBYTE(ptQTask[4].tQTaskRefList.ptTail) = 1;
  LOBYTE(ptQTask[2].tQTaskRefList.ptMiddle) = 0;
  ptQTask[1].tQTaskRefList.ptTail = (struct QReference_s *)1;
  ptQTask[1].ptParent = (struct QTask_s *)1;
  BYTE2(ptQTask[2].ptPrev) = 1;
  v3 = QTask_NewFn(nullptr, v2, v5);
  strcpy((char *)&v3[2].tQTaskChildren.ptMiddle, "slidevert");
  LOBYTE(v3[4].tQTaskRefList.ptTail) = 0;
  v3[4].tQTaskRefList.ptHead = (struct QReference_s *)50;
  v3[16].ptParent = (struct QTask_s *)3;
  *(_DWORD *)&ptQTask[18].eQTaskType = v3;
  ptQTask[19].ptNext = QTask_NewFn(nullptr, MenuWindow_eQTaskType, *(void **)&ptQTask[1].eQTaskType);
  HIBYTE(ptQTask[4].tQTaskRefList.ptTail) = 0;
  v4 = (struct QTask_s *)Mem_AllocFn(52, 4);
  v4->tQTaskRefList.ptTail = (struct QReference_s *)1;
  v4[1].ptNext = nullptr;
  *(_DWORD *)&v4->eQTaskType = 0;
  v4[1].tQTaskChildren.ptHead = nullptr;
  v4->tQTaskChildren.ptHead = nullptr;
  v4->ptPrev = nullptr;
  v4->tQTaskRefList.ptHead = nullptr;
  v4->tQTaskRefList.ptMiddle = nullptr;
  v4[1].ptPrev = (struct QTask_s *)64;
  v4->ptParent = (struct QTask_s *)8;
  v4->ptNext = (struct QTask_s *)4;
  v4->tQTaskChildren.ptTail = (struct QTask_s *)8;
  v4->tQTaskChildren.ptMiddle = (struct QTask_s *)64;
  ptQTask[2].tQTaskChildren.ptMiddle = v4;
}

// source: j/0/menusystem/columnview.c:227  [anchor-mhash]
void __cdecl ColumnView_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QReference_s *ptHead; // eax

  ptHead = ptQTask[2].tQTaskRefList.ptHead;
  if ( ptHead )
  {
    Text_Delete((struct StaticTilemap_s *)ptHead);
    ptQTask[2].tQTaskRefList.ptHead = nullptr;
  }
  QTask_Delete(*(struct QTask_s **)&ptQTask[18].eQTaskType);
  QTask_Delete(ptQTask[19].ptNext);
  ColumnView_DeleteEntries((struct ColumnView_s *)ptQTask);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[4].ptParent);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[6].ptParent);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[8].ptParent);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[10].ptParent);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[12].ptParent);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[14].ptParent);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[16].ptParent);
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Level_eRemoveLevelScriptSymbolsEvent][ptQTask->eQTaskType].pfHandler)(ptQTask);
  QObjectVector_Delete((struct QObjectVector_s *)ptQTask[2].tQTaskChildren.ptMiddle);
}

// source: j/0/menusystem/columnview.c:269  [anchor-mhash]
void __cdecl ColumnView_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QSprite_s *Font; // edi
  struct QReference_s *ptHead; // eax
  struct QReference_s *v4; // eax
  struct QTask_s *ptNext; // ecx
  struct QTask_s *v6; // edx

  Font = MenuManager_GetFont(
           *(struct QTask_s **)&ptQTask[1].eQTaskType,
           (char *)&ptQTask[2].tQTaskRefList.ptMiddle);
  ptHead = ptQTask[2].tQTaskRefList.ptHead;
  if ( ptHead )
  {
    Text_Delete((struct StaticTilemap_s *)ptHead);
    ptQTask[2].tQTaskRefList.ptHead = nullptr;
  }
  if ( Font )
  {
    v4 = (struct QReference_s *)Text_New(Font, 0.0, 0.0, "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
    ptQTask[2].tQTaskRefList.ptHead = v4;
    v4[2].pxObject = nullptr;
    ptQTask[18].ptParent = (struct QTask_s *)(SHIWORD(ptQTask[2].tQTaskRefList.ptHead->ptNext->ptPrev)
                                            * *(__int16 *)(*((_DWORD *)ptQTask[2].tQTaskRefList.ptHead->ptNext->pxObject
                                                           + 2)
                                                         + 36
                                                         * *((unsigned __int16 *)ptQTask[2].tQTaskRefList.ptHead->ptNext->pxObject
                                                           + 10)
                                                         + 14)
                                            + 1);
  }
  else
  {
    ptQTask[18].ptParent = (struct QTask_s *)1;
  }
  ptNext = ptQTask[19].ptNext;
  v6 = ptQTask[1].tQTaskChildren.ptHead;
  BYTE2(ptQTask[4].tQTaskRefList.ptTail) = 0;
  ptNext[1].tQTaskChildren.ptHead = v6;
  ptQTask[19].ptNext[1].tQTaskChildren.ptMiddle = ptQTask[1].tQTaskChildren.ptMiddle;
  ptQTask[19].ptNext[1].ptNext = ptQTask[1].ptNext;
  ptQTask[19].ptNext[1].ptPrev = ptQTask[1].ptPrev;
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[4].ptParent, ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[6].ptParent, ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[8].ptParent, ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[10].ptParent, ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[12].ptParent, ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[14].ptParent, ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[16].ptParent, ptQTask);
  ((void (__cdecl *)(_DWORD, void *))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][*(unsigned __int16 *)(*(_DWORD *)&ptQTask[18].eQTaskType + 36)].pfHandler)(
    *(_DWORD *)&ptQTask[18].eQTaskType,
    pxContext);
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][MenuWindow_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
}

// source: j/0/menusystem/columnview.c:337  [anchor-mhash]
void __cdecl ColumnView_FormatScrollBar(struct ColumnView_s *ptColumnView)
{
  int nHeight; // edi
  int v2; // eax
  struct QObjectVector_s *ptEntryIDVector; // edx
  bool v4; // zf
  struct MenuWindow_t *ptSlideBar; // ecx
  int nWidth; // ebx
  unsigned int nAllocated; // edx
  int v8; // ebp
  int v9; // ebx
  int nYPos; // [esp+Ch] [ebp-4h]

  nHeight = ptColumnView->tMenuWindow.nHeight;
  v2 = (nHeight - 4) / ptColumnView->nFontHeight;
  ptEntryIDVector = ptColumnView->ptEntryIDVector;
  v4 = v2 >= (signed int)ptEntryIDVector->nAllocated;
  ptColumnView->isScrollBar = v2 < (signed int)ptEntryIDVector->nAllocated;
  if ( v4 )
  {
    v9 = 0;
  }
  else
  {
    ptSlideBar = ptColumnView->ptSlideBar;
    nWidth = ptSlideBar->nWidth;
    nAllocated = ptEntryIDVector->nAllocated;
    nYPos = ptColumnView->tMenuWindow.nYPos;
    v8 = ptColumnView->tMenuWindow.nXPos + ptColumnView->tMenuWindow.nWidth;
    ptSlideBar->nHeight = nHeight;
    ptSlideBar->nXPos = v8 - nWidth;
    ptSlideBar->nYPos = nYPos;
    ptSlideBar[1].nKeyPress = nHeight
                            - *(_DWORD *)(ptSlideBar[1].eVertAlignmentMode + 52)
                            - *(_DWORD *)(ptSlideBar[1].eHorAlignmentMode + 52)
                            - 6;
    ptSlideBar[7].tQTask.tQTaskRefList.ptTail = (struct QReference_s *)(nAllocated - v2 + 1);
    v9 = nWidth + 2;
  }
  ptColumnView->ptItemBox->nXPos = ptColumnView->tMenuWindow.nXPos;
  ptColumnView->ptItemBox->nYPos = ptColumnView->tMenuWindow.nYPos;
  ptColumnView->ptItemBox->nHeight = ptColumnView->tMenuWindow.nHeight;
  ptColumnView->ptItemBox->nWidth = ptColumnView->tMenuWindow.nWidth - v9;
}

// source: j/0/menusystem/columnview.c:381  [anchor-caller]
void __cdecl ColumnView_RunHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v23; };
    struct { char igi2_o1[4]; struct QTask_s *v24; };
    struct { char igi2_o2[8]; int nHeight; };
    struct { char igi2_o3[12]; int v26; };
    struct { char igi2_o4[16]; struct QTask_s *ptMiddle; };
    struct { char igi2_o5[20]; int nWidth[2]; };
    char igi2_extent[28];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v1; // eax
  struct MenuWindow_t *ptNext; // ebx
  struct QTask_s *ptParent; // ecx
  int v4; // esi
  bool v5; // zf
  int v6; // eax
  int v7; // ecx
  struct QTask_s *v8; // eax
  struct QReference_s *ptHead; // eax
  struct QReference_s *nTicks; // ebx
  int i; // edx
  int v12; // eax
  struct QReference_s *v13; // eax
  struct QTask_s *v14; // eax
  struct QTask_s *v15; // eax
  int v16; // ecx
  struct QTask_s *v17; // eax
  struct QTask_s *v18; // eax
  bool v19; // cc
  struct QReference_s *v20; // eax
  struct QReference_s *v21; // eax
  struct QTask_s *v22; // eax

  igi2_frame.v24 = *(struct QTask_s **)&ptQTask[1].eQTaskType;
  v1 = (int)&ptQTask[1].tQTaskChildren.ptMiddle[-1].eQTaskType / (int)ptQTask[18].ptParent;
  ptNext = (struct MenuWindow_t *)ptQTask[19].ptNext;
  igi2_frame.ptMiddle = ptQTask[4].tQTaskChildren.ptMiddle;
  ptParent = ptQTask[4].ptParent;
  ColumnView_ptActiveColumnView = (struct ColumnView_s *)ptQTask;
  igi2_frame.v26 = v1;
  if ( ptParent )
  {
    if ( **(_BYTE **)&ptQTask[4].eQTaskType )
    {
      if ( ptQTask[5].ptNext )
      {
        v4 = *(_DWORD *)&ptQTask[2].tQTaskChildren.ptMiddle->eQTaskType;
        Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[4].ptParent, ptQTask);
        if ( *(_DWORD *)&ptQTask[2].tQTaskChildren.ptMiddle->eQTaskType != v4 )
          ColumnView_FormatScrollBar((struct ColumnView_s *)ptQTask);
      }
    }
  }
  v5 = ptQTask[4].tQTaskRefList.ptMiddle == nullptr;
  ColumnView_ptActiveColumnView = nullptr;
  if ( !v5 )
  {
    ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[MenuWindow_eInitDataEvent][ptQTask->eQTaskType].pfHandler)(ptQTask);
    ptQTask[4].tQTaskRefList.ptMiddle = nullptr;
  }
  if ( BYTE2(ptQTask[4].tQTaskRefList.ptTail)
    && (((void (__cdecl *)(_DWORD))QTask_aatQTaskFinalEvent[1][*(unsigned __int16 *)(*(_DWORD *)&ptQTask[18].eQTaskType
                                                                                   + 36)].pfHandler)(*(_DWORD *)&ptQTask[18].eQTaskType),
        v6 = *(_DWORD *)&ptQTask[18].eQTaskType,
        (v7 = *(_DWORD *)(v6 + 672)) != 0) )
  {
    *(_QWORD *)igi2_frame.nWidth = (__int64)((double)(v7 - 1) * *(double *)(v6 + 168) + 0.5);
    igi2_frame.v23 = igi2_frame.nWidth[0];
  }
  else
  {
    igi2_frame.v23 = 0;
  }
  MenuWindow_HitTest(ptNext, ptNext->nXPos, ptNext->nYPos, ptNext->nWidth, ptNext->nHeight, igi2_frame.nWidth, &igi2_frame.nHeight);
  if ( ptNext->isClicked )
  {
    v8 = (struct QTask_s *)(igi2_frame.v23 + (igi2_frame.nHeight - ptNext->nYPos) / (int)ptQTask[18].ptParent);
    if ( (int)v8 < (int)(*(_DWORD *)&ptQTask[2].tQTaskChildren.ptMiddle->eQTaskType) )
    {
      if ( v8 == ptQTask[4].tQTaskChildren.ptMiddle )
      {
        ptHead = ptQTask[4].tQTaskRefList.ptHead;
        nTicks = (struct QReference_s *)Flow_ptFlow->nTicks;
        if ( ptHead != (struct QReference_s *)-1 )
        {
          *(_QWORD *)igi2_frame.nWidth = (__int64)((double)Flow_ptFlow->nFrequency * 0.5);
          if ( (char *)nTicks - (char *)ptHead < igi2_frame.nWidth[0] )
          {
            if ( Level_LevelExpressionDefined((struct LevelExpression_s *)&ptQTask[12].ptParent) )
            {
              if ( Level_LevelExpressionDefined((struct LevelExpression_s *)&ptQTask[16].ptParent) == false
                || (*(_QWORD *)igi2_frame.nWidth = (__int64)Level_RunLevelExpression(
                                                   (struct LevelExpression_s *)&ptQTask[16].ptParent,
                                                   ptQTask),
                    igi2_frame.nWidth[0]) )
              {
                Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[12].ptParent, ptQTask);
              }
              else
              {
                NetManager_LogMessage("Selection DISABLED\n");
              }
            }
          }
        }
        ptQTask[4].tQTaskRefList.ptHead = nTicks;
      }
      else
      {
        ptQTask[4].tQTaskChildren.ptMiddle = v8;
        ptQTask[4].tQTaskRefList.ptHead = (struct QReference_s *)Flow_ptFlow->nTicks;
      }
    }
  }
  if ( HIBYTE(ptQTask[4].tQTaskRefList.ptTail) )
  {
    for ( i = tKeyboardBuffer.nBuffer; tKeyboardBuffer.nBuffer; i = tKeyboardBuffer.nBuffer )
    {
      v12 = 0;
      if ( i )
      {
        v12 = tKeyboardBuffer.anBuffer[tKeyboardBuffer.iBufferIndex++];
        if ( tKeyboardBuffer.iBufferIndex == 32 )
          tKeyboardBuffer.iBufferIndex = 0;
        tKeyboardBuffer.nBuffer = i - 1;
      }
      LOBYTE(ptQTask[4].tQTaskRefList.ptTail) = 1;
      switch ( v12 )
      {
        case -11:
          v20 = (struct QReference_s *)igi2_frame.v24[255].ptParent;
          if ( v20 )
          {
            QReference_Delete(v20, &QTask_tQTaskRefPool);
            igi2_frame.v24[255].ptParent = nullptr;
          }
          HIBYTE(ptQTask[4].tQTaskRefList.ptTail) = 0;
          MenuManager_GotoNextTAB(igi2_frame.v24);
          break;
        case -8:
          v13 = (struct QReference_s *)igi2_frame.v24[255].ptParent;
          if ( v13 )
          {
            QReference_Delete(v13, &QTask_tQTaskRefPool);
            igi2_frame.v24[255].ptParent = nullptr;
          }
          HIBYTE(ptQTask[4].tQTaskRefList.ptTail) = 0;
          MenuManager_ExitTAB(igi2_frame.v24);
          break;
        case -7:
          if ( ptQTask[12].ptParent && **(_BYTE **)&ptQTask[12].eQTaskType && ptQTask[13].ptNext )
          {
            if ( ptQTask[16].ptParent
              && **(_BYTE **)&ptQTask[16].eQTaskType
              && ptQTask[17].ptNext
              && (*(_QWORD *)igi2_frame.nWidth = (__int64)Level_RunLevelExpression(
                                                 (struct LevelExpression_s *)&ptQTask[16].ptParent,
                                                 ptQTask),
                  !igi2_frame.nWidth[0]) )
            {
              NetManager_LogMessage("Selection DISABLED\n");
            }
            else
            {
              Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[12].ptParent, ptQTask);
            }
          }
          break;
        case -4:
          v17 = ptQTask[4].tQTaskChildren.ptMiddle;
          if ( (int)v17 < (int)(*(_DWORD *)&ptQTask[2].tQTaskChildren.ptMiddle->eQTaskType - 1) )
          {
            v18 = (struct QTask_s *)((char *)&v17->ptNext + 1);
            v19 = (int)v18 < igi2_frame.v23 + igi2_frame.v26;
            ptQTask[4].tQTaskChildren.ptMiddle = v18;
            if ( v19 )
              goto LABEL_41;
            v16 = igi2_frame.v23 + 1;
            goto LABEL_40;
          }
          break;
        case -3:
          v14 = ptQTask[4].tQTaskChildren.ptMiddle;
          if ( (int)v14 > 0 )
          {
            v15 = (struct QTask_s *)((char *)v14 - 1);
            ptQTask[4].tQTaskChildren.ptMiddle = v15;
            if ( (int)v15 < igi2_frame.v23 )
            {
              v16 = igi2_frame.v23 - 1;
LABEL_40:
              SlideBar_SetIntValue(*(struct MenuWindow_t **)&ptQTask[18].eQTaskType, v16);
            }
LABEL_41:
            SoundSys_PlaySimpleSoundFn("menu_sel2", 0, nullptr);
          }
          break;
        default:
          continue;
      }
    }
  }
  if ( HIBYTE(ptQTask[2].ptPrev) )
  {
    if ( !HIBYTE(ptQTask[4].tQTaskRefList.ptTail) )
      LOBYTE(ptQTask[4].tQTaskRefList.ptTail) = 1;
    HIBYTE(ptQTask[4].tQTaskRefList.ptTail) = 1;
    v21 = (struct QReference_s *)igi2_frame.v24[255].ptParent;
    if ( v21 )
    {
      QReference_Delete(v21, &QTask_tQTaskRefPool);
      igi2_frame.v24[255].ptParent = nullptr;
    }
    igi2_frame.v24[255].ptParent = (struct QTask_s *)QTask_NewQTaskRef(ptQTask);
  }
  v22 = ptQTask[4].tQTaskChildren.ptMiddle;
  v5 = igi2_frame.ptMiddle == v22;
  ptQTask[4].tQTaskChildren.ptTail = v22;
  if ( !v5 )
  {
    if ( ptQTask[16].ptParent && **(_BYTE **)&ptQTask[16].eQTaskType && ptQTask[17].ptNext )
    {
      *(_QWORD *)igi2_frame.nWidth = (__int64)Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[16].ptParent, ptQTask);
      if ( igi2_frame.nWidth[0] )
        NetManager_LogMessage("Item is ENABLED\n");
      else
        NetManager_LogMessage("Item is DISABLED\n");
    }
    else
    {
      NetManager_LogMessage("No item level expression\n");
    }
    if ( ptQTask[14].ptParent && **(_BYTE **)&ptQTask[14].eQTaskType && ptQTask[15].ptNext )
      Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[14].ptParent, ptQTask);
    if ( !ptQTask[16].ptParent
      || !**(_BYTE **)&ptQTask[16].eQTaskType
      || !ptQTask[17].ptNext
      || (*(_QWORD *)igi2_frame.nWidth = (__int64)Level_RunLevelExpression(
                                         (struct LevelExpression_s *)&ptQTask[16].ptParent,
                                         ptQTask),
          igi2_frame.nWidth[0]) )
    {
      SoundSys_PlaySimpleSoundFn("menu_sel2", 0, nullptr);
    }
  }
  if ( LOBYTE(ptQTask[4].tQTaskRefList.ptTail) )
  {
    LOBYTE(ptQTask[4].tQTaskRefList.ptTail) = 0;
    ColumnView_ForceVisible(ptQTask);
  }
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][MenuWindow_eQTaskType].pfHandler)(ptQTask);
}

// source: j/0/menusystem/columnview.c:638  [anchor-mhash]
void __cdecl ColumnView_DrawHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vX; };
    struct { char igi2_o1[4]; float vY; };
    struct { char igi2_o2[8]; float vWidth; };
    struct { char igi2_o3[12]; float vHeight; };
    struct { char igi2_o4[56]; int nY; };
    struct { char igi2_o5[60]; float vFade; };
    struct { char igi2_o6[72]; int nX; };
    struct { char igi2_o7[76]; struct ColumnViewDrawEntriesContext_s tColumnViewDrawEntriesContext; };
    char igi2_extent[116];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v2; // st7
  int v3; // eax
  struct QTask_s *v4; // edx
  struct QTask_s *ptNext; // ecx
  int v6; // edi
  char *v7; // ebp
  int v8; // eax
  int v9; // edx
  int v10; // eax
  struct QTask_s *ptMiddle; // ebx
  struct QTask_s *v12; // ecx
  int v13; // ebx
  struct QTask_s *v14; // edx
  struct QTask_s *ptParent; // eax
  struct QReference_s *ptHead; // ecx
  struct QTask_s *v17; // eax
  int v18; // edx
  struct QTask_s *v19; // ecx
  int i; // edi
  struct QTask_s *ptQTaska = *(struct QTask_s * *)&ptQTask; // [esp+78h] [ebp+4h] ARGSLOT

  v2 = (double)(*(_DWORD *)(*(_DWORD *)&ptQTask[1].eQTaskType + 356) - 8) * 0.125;
  if ( v2 <= 0.0 )
    v2 = 0.0;
  igi2_frame.vFade = v2;
  v3 = (int)&ptQTask[1].tQTaskChildren.ptMiddle[-1].eQTaskType / (int)ptQTask[18].ptParent;
  v4 = *(struct QTask_s **)&ptQTask[2].tQTaskChildren.ptMiddle->eQTaskType;
  ptQTaska = v4;
  if ( (int)v4 >= v3 )
    ptQTaska = (struct QTask_s *)v3;
  ptNext = ptQTask[1].ptNext;
  v6 = (int)&ptNext[-8] + (Display_tActiveMode.nWidth >> 1);
  v7 = (char *)&ptQTask[1].ptPrev[-5] + (Display_tActiveMode.nHeight >> 1) - 38;
  igi2_frame.nX = v6;
  igi2_frame.nY = (int)v7;
  if ( v3 < (int)v4 && (v8 = *(_DWORD *)&ptQTask[18].eQTaskType, (v9 = *(_DWORD *)(v8 + 672)) != 0) )
    v10 = (__int64)((double)(v9 - 1) * *(double *)(v8 + 168) + 0.5);
  else
    v10 = 0;
  ptMiddle = ptQTask[4].tQTaskChildren.ptMiddle;
  ptQTask[19].ptNext[1].ptNext = ptNext;
  ptQTask[19].ptNext[1].ptPrev = ptQTask[1].ptPrev;
  igi2_frame.tColumnViewDrawEntriesContext.vFade = v2;
  v12 = ptQTask[2].tQTaskChildren.ptMiddle;
  v13 = (int)ptMiddle - v10;
  igi2_frame.tColumnViewDrawEntriesContext.nEntriesToDraw = (int)ptQTaska;
  v14 = ptQTask[1].tQTaskChildren.ptMiddle;
  igi2_frame.tColumnViewDrawEntriesContext.nEntryOffset = v10;
  ptParent = ptQTask[18].ptParent;
  igi2_frame.tColumnViewDrawEntriesContext.ptEntryIDVector = (struct QObjectVector_s *)v12;
  ptHead = ptQTask[2].tQTaskRefList.ptHead;
  igi2_frame.tColumnViewDrawEntriesContext.nFontHeight = (int)ptParent;
  v17 = ptQTask->tQTaskChildren.ptHead;
  igi2_frame.tColumnViewDrawEntriesContext.nX = v6 + 4;
  igi2_frame.tColumnViewDrawEntriesContext.nY = (int)v7;
  igi2_frame.tColumnViewDrawEntriesContext.nSelectedItem = v13;
  igi2_frame.tColumnViewDrawEntriesContext.ptText = (struct StaticTilemap_s *)ptHead;
  igi2_frame.tColumnViewDrawEntriesContext.nWindowHeight = (int)&v14[-1].eQTaskType;
  if ( v17->ptNext && v17 )
  {
    v18 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( v17->ptNext )
        v19 = v17->ptNext->ptNext != nullptr ? v17->ptNext : nullptr;
      else
        v19 = nullptr;
      QTask_atProtectedQTaskStack[v18].ptQTask = v19;
      QTask_nProtectedQTaskStackOffset = v18 + 1;
      ((void (__cdecl *)(struct QTask_s *, struct ColumnViewDrawEntriesContext_s *))QTask_aatQTaskFinalEvent[ColumnView_eDrawEntriesQTaskEvent][v17->eQTaskType].pfHandler)(
        v17,
        &igi2_frame.tColumnViewDrawEntriesContext);
      v17 = (struct QTask_s *)dword_849C7DC[QTask_nProtectedQTaskStackOffset];
      v18 = --QTask_nProtectedQTaskStackOffset;
    }
    while ( v17 );
  }
  for ( i = 0; i < (int)ptQTaska; igi2_frame.nY += (int)ptQTask[18].ptParent )
  {
    if ( i == v13 )
    {
      igi2_frame.vHeight = (float)(int)ptQTask[18].ptParent;
      igi2_frame.vWidth = (double)(int)ptQTask[19].ptNext[1].tQTaskChildren.ptHead - 4.0;
      igi2_frame.vY = (float)igi2_frame.nY;
      igi2_frame.vX = (double)igi2_frame.nX + 2.0;
      QSprite_RegisterBlankA(igi2_frame.vX, igi2_frame.vY, igi2_frame.vWidth, igi2_frame.vHeight, 15.359999656677246, 35.84000015258789, 98.55999755859375, igi2_frame.vFade, 0x80000u, 0);
    }
    ++i;
  }
  if ( BYTE2(ptQTask[4].tQTaskRefList.ptTail) )
    ((void (__cdecl *)(_DWORD))QTask_aatQTaskFinalEvent[Screen_eDrawQTaskEvent][*(unsigned __int16 *)(*(_DWORD *)&ptQTask[18].eQTaskType + 36)].pfHandler)(*(_DWORD *)&ptQTask[18].eQTaskType);
  MenuWindow_DrawBorder((struct MenuWindow_t *)ptQTask[19].ptNext, 0.5, igi2_frame.vFade, SHIBYTE(ptQTask[4].tQTaskRefList.ptTail));
}

// source: j/0/menusystem/columnview.c:725  [size]
void __cdecl ColumnView_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = ColumnView_ptParameterList;
}

// source: j/0/menusystem/columnview.c:741  [anchor-mhash]
void __cdecl ColumnView_InitDataHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptParent; // ecx
  struct QTask_s *v2; // ecx
  int v3; // eax
  int v4; // edi
  struct QReference_s *v5; // eax
  struct QTask_s *v6; // ebp
  struct QTask_s *ptHead; // ecx
  int v8; // edx
  struct QTask_s *v9; // eax
  int v10; // edi
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v12; // edx

  ColumnView_DeleteEntries((struct ColumnView_s *)ptQTask);
  ptParent = ptQTask[6].ptParent;
  ColumnView_ptActiveColumnView = (struct ColumnView_s *)ptQTask;
  if ( ptParent && **(_BYTE **)&ptQTask[6].eQTaskType && ptQTask[7].ptNext )
    Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[6].ptParent, ptQTask);
  v2 = ptQTask[8].ptParent;
  ColumnView_ptActiveColumnView = nullptr;
  if ( v2 && **(_BYTE **)&ptQTask[8].eQTaskType && ptQTask[9].ptNext )
    v3 = (__int64)Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[8].ptParent, ptQTask);
  else
    v3 = -1;
  ptQTask[4].tQTaskChildren.ptMiddle = (struct QTask_s *)v3;
  ptQTask[4].tQTaskChildren.ptTail = (struct QTask_s *)v3;
  ColumnView_FormatScrollBar((struct ColumnView_s *)ptQTask);
  if ( BYTE2(ptQTask[4].tQTaskRefList.ptTail) )
  {
    v4 = *(_DWORD *)&ptQTask[1].eQTaskType;
    v5 = *(struct QReference_s **)(v4 + 10236);
    v6 = *(struct QTask_s **)&ptQTask[18].eQTaskType;
    if ( v5 )
    {
      QReference_Delete(v5, &QTask_tQTaskRefPool);
      *(_DWORD *)(v4 + 10236) = 0;
    }
    if ( v6 )
      *(_DWORD *)(v4 + 10236) = QTask_NewQTaskRef(v6);
  }
  ptHead = ptQTask->tQTaskChildren.ptHead;
  HIBYTE(ptQTask[4].tQTaskRefList.ptTail) = 0;
  ptQTask[4].tQTaskRefList.ptHead = (struct QReference_s *)-1;
  if ( ptHead->ptNext && ptHead )
  {
    v8 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v9 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v9 = nullptr;
      v10 = MenuWindow_eInitDataEvent;
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
  LOBYTE(ptQTask[4].tQTaskRefList.ptTail) = 1;
}

// source: j/0/menusystem/columnview.c:805  [size]
void __cdecl ColumnView_ChangeDataHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // ecx
  int v2; // edx
  struct QTask_s *v3; // eax
  int v4; // esi
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v6; // edx

  if ( ptQTask[10].ptParent && **(_BYTE **)&ptQTask[10].eQTaskType && ptQTask[11].ptNext )
    Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[10].ptParent, ptQTask);
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

// source: j/0/menusystem/columnview.c:830  [anchor-refs]
void __cdecl ColumnView_RegisterScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( !BYTE1(ptQTask[4].tQTaskRefList.ptTail) )
  {
    BYTE1(ptQTask[4].tQTaskRefList.ptTail) = 1;
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.nActiveID", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int,
      &ptQTask[4].tQTaskChildren.ptTail,
      4,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.isUpdate", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int,
      &ptQTask[4].tQTaskRefList.ptMiddle,
      4,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
  }
}

// source: j/0/menusystem/columnview.c:862  [anchor-mhash]
void __cdecl ColumnView_RemoveScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( BYTE1(ptQTask[4].tQTaskRefList.ptTail) )
  {
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.nActiveID", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.isUpdate", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    BYTE1(ptQTask[4].tQTaskRefList.ptTail) = 0;
  }
}

// source: j/0/menusystem/columnview.c:905  [anchor-mhash]
struct Result_s *__cdecl ColumnView_ScriptSortFunction(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct ArgList_s *iColumn; };
    struct { char igi2_o1[4]; struct Result_s Rs; };
    char igi2_extent[28];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // ebx
  struct ArgList_s *v5; // esi
  struct QReference_s *v6; // eax
  struct ColumnView_s *pxObject; // edx

  v3 = ptArgList;
  if ( ptArgList->nArguments == 3 )
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
    if ( v3->isQVM )
    {
      ptArgList = nullptr;
      QVM_EvalArg(&ptArgList, 4, v3, 1, 1);
      igi2_frame.iColumn = ptArgList;
    }
    else
    {
      igi2_frame.iColumn = (struct ArgList_s *)Expression_EvalInt(v3->aptExpression[1]);
    }
    if ( v3->isQVM )
    {
      ptArgList = nullptr;
      QVM_EvalArg(&ptArgList, 4, v3, 2, 1);
      v5 = ptArgList;
    }
    else
    {
      v5 = (struct ArgList_s *)Expression_EvalInt(v3->aptExpression[2]);
    }
    if ( (unsigned int)v4 < 0x1000 )
    {
      v6 = Level_atLevelQTaskID[(_DWORD)v4];
      if ( v6 )
      {
        pxObject = (struct ColumnView_s *)v6->pxObject;
        if ( pxObject )
        {
          if ( QTask_IsQTaskTypeDerived(pxObject->tMenuWindow.tQTask.eQTaskType, ColumnView_eQTaskType) )
          {
            ColumnView_ptActiveColumnView = pxObject;
            ColumnView_SortEntries((int)igi2_frame.iColumn, (int)v5);
          }
        }
      }
    }
  }
  igi2_frame.Rs.nResult = 0;
  igi2_frame.Rs.vResult = 0.0;
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/menusystem/columnview.c:1035  [anchor-hash]
int __cdecl ColumnView_AddEntry()
{
  struct QObjectVector_s *ptEntryIDVector; // esi
  struct QObjectVector_s **p_ptEntryIDVector; // edi
  unsigned int nAllocated; // eax
  _DWORD *v3; // ecx
  int result; // eax

  ptEntryIDVector = ColumnView_ptActiveColumnView->ptEntryIDVector;
  p_ptEntryIDVector = &ColumnView_ptActiveColumnView->ptEntryIDVector;
  if ( ptEntryIDVector->nAllocated == ptEntryIDVector->nSize )
    QObjectVector_Realloc(ColumnView_ptActiveColumnView->ptEntryIDVector, ptEntryIDVector->nReallocSize);
  nAllocated = ptEntryIDVector->nAllocated;
  v3 = ptEntryIDVector->papxElement[nAllocated];
  ptEntryIDVector->nAllocated = nAllocated + 1;
  result = (*p_ptEntryIDVector)->nAllocated - 1;
  *v3 = result;
  return result;
}

// source: j/0/menusystem/columnview.c:1060  [anchor-mhash]
int __cdecl ColumnView_SetEntry(
        int nEntryID,
        char *zItemName,
        int iColumn,
        enum bool isTranslated)
{
  int result; // eax
  struct QTask_s *ptHead; // ecx
  int v6; // edx
  struct QTask_s *v7; // eax
  int v8; // edx
  struct ColumnViewAddEntryContext_s tColumnViewAddItemContext; // [esp+0h] [ebp-1Ch] BYREF

  tColumnViewAddItemContext.iColumn = iColumn;
  tColumnViewAddItemContext.nEntryID = nEntryID;
  result = (int)ColumnView_ptActiveColumnView;
  tColumnViewAddItemContext.zItemName = zItemName;
  tColumnViewAddItemContext.isTranslated = isTranslated;
  tColumnViewAddItemContext.iCurrentColumn = 0;
  tColumnViewAddItemContext.ptMenuManager = ColumnView_ptActiveColumnView->tMenuWindow.ptMenuManager;
  ptHead = ColumnView_ptActiveColumnView->tMenuWindow.tQTask.tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v6 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v7 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v7 = nullptr;
      QTask_atProtectedQTaskStack[v6].ptQTask = v7;
      result = (int)QTask_aatQTaskFinalEvent[ColumnView_eAddEntryQTaskEvent][ptHead->eQTaskType].pfHandler;
      v8 = v6 + 1;
      QTask_nProtectedQTaskStackOffset = v8;
      if ( result )
      {
        result = ((int (__cdecl *)(struct QTask_s *, struct ColumnViewAddEntryContext_s *))result)(
                   ptHead,
                   &tColumnViewAddItemContext);
        v8 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v8];
      v6 = v8 - 1;
      QTask_nProtectedQTaskStackOffset = v6;
    }
    while ( ptHead );
  }
  return result;
}

// source: j/0/menusystem/columnview.c:1090  [anchor-mhash]
int __cdecl ColumnView_SortEntries(int iColumn, int nSortOrder)
{
  int result; // eax
  struct QTask_s *ptHead; // ecx
  int v4; // edx
  struct QTask_s *v5; // eax
  int v6; // edx
  struct ColumnViewSortEntriesContext_s tColumnViewSortEntriesContext; // [esp+0h] [ebp-10h] BYREF

  tColumnViewSortEntriesContext.iColumn = iColumn;
  result = (int)ColumnView_ptActiveColumnView;
  tColumnViewSortEntriesContext.nSortOrder = nSortOrder;
  tColumnViewSortEntriesContext.ptEntryIDVector = ColumnView_ptActiveColumnView->ptEntryIDVector;
  tColumnViewSortEntriesContext.iCurrentColumn = 0;
  ptHead = ColumnView_ptActiveColumnView->tMenuWindow.tQTask.tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v4 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v5 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v5 = nullptr;
      QTask_atProtectedQTaskStack[v4].ptQTask = v5;
      result = (int)QTask_aatQTaskFinalEvent[ColumnView_eSortEntriesQTaskEvent][ptHead->eQTaskType].pfHandler;
      v6 = v4 + 1;
      QTask_nProtectedQTaskStackOffset = v6;
      if ( result )
      {
        result = ((int (__cdecl *)(struct QTask_s *, struct ColumnViewSortEntriesContext_s *))result)(
                   ptHead,
                   &tColumnViewSortEntriesContext);
        v6 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v6];
      v4 = v6 - 1;
      QTask_nProtectedQTaskStackOffset = v4;
    }
    while ( ptHead );
  }
  return result;
}

// source: j/0/menusystem/columnview.c:1115  [size]
__int16 __cdecl ColumnView_GetAddEntryQTaskEvent()
{
  return ColumnView_eAddEntryQTaskEvent;
}

// source: j/0/menusystem/columnview.c:1128  [size]
__int16 __cdecl ColumnView_GetDeleteEntryQTaskEvent()
{
  return ColumnView_eDeleteEntryQTaskEvent;
}

// source: j/0/menusystem/columnview.c:1141  [size]
__int16 __cdecl ColumnView_GetSortEntriesQTaskEvent()
{
  return ColumnView_eSortEntriesQTaskEvent;
}

// source: j/0/menusystem/columnview.c:1154  [size]
__int16 __cdecl ColumnView_GetDrawEntriesQTaskEvent()
{
  return ColumnView_eDrawEntriesQTaskEvent;
}

// source: j/0/menusystem/columnview.c:1167  [anchor-hash]
void __cdecl ColumnView_Clear()
{
  ColumnView_DeleteEntries(ColumnView_ptActiveColumnView);
}

// source: j/0/menusystem/columnview.c:1185  [anchor-hash]
void __cdecl ColumnView_ClearSelection()
{
  struct ColumnView_s *v0; // eax

  v0 = ColumnView_ptActiveColumnView;
  ColumnView_ptActiveColumnView->nActiveEntry = -1;
  v0->nActiveID = -1;
}

// source: j/0/menusystem/columnview.c:1205  [anchor-hash]
enum bool __cdecl ColumnView_IsSelection()
{
  return ColumnView_ptActiveColumnView->nActiveID != -1 && ColumnView_ptActiveColumnView->nActiveEntry != -1;
}

// source: j/0/menusystem/columnview.c:1224  [anchor-hash]
void __cdecl ColumnView_Open()
{
  __int16 v0; // ax
  unsigned __int16 v1; // si
  struct ParameterList_s *v2; // eax
  int v3; // edx

  ColumnView_eQTaskType = QTask_NewQTaskType("ColumnView", 764, MenuWindow_eQTaskType, 0, 0);
  ColumnView_eAddEntryQTaskEvent = QTask_NewQTaskEventFn(0, "ColumnViewAddItem");
  ColumnView_eDeleteEntryQTaskEvent = QTask_NewQTaskEventFn(0, "ColumnViewDeleteEntry");
  ColumnView_eSortEntriesQTaskEvent = QTask_NewQTaskEventFn(0, "ColumnViewSortEntries");
  v0 = QTask_NewQTaskEventFn(0, "ColumnViewDrawEntries");
  v1 = ColumnView_eQTaskType;
  ColumnView_eDrawEntriesQTaskEvent = v0;
  QTask_LinkQTaskEventHandlerFn(
    ColumnView_eQTaskType,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, ColumnView_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, Screen_eDrawQTaskEvent, ColumnView_DrawHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, ColumnView_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 0, ColumnView_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))ColumnView_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v1, ParameterList_eUpdateInternalDataQTaskEvent, ColumnView_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, MenuWindow_eInitDataEvent, ColumnView_InitDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, MenuWindow_eChangeDataEvent, ColumnView_ChangeDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v1,
    Level_eRegisterLevelScriptSymbolsEvent,
    ColumnView_RegisterScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v1,
    Level_eRemoveLevelScriptSymbolsEvent,
    ColumnView_RemoveScriptSymbolsHandler);
  v2 = (struct ParameterList_s *)Mem_AllocFn(212, 4);
  v3 = Level_eParameterTypeString32;
  v2->ptParameterListItem = (struct ParameterListItem_s *)&v2[1];
  v2->nParameters = 0;
  v2->nMaxParameters = 10;
  ColumnView_ptParameterList = v2;
  ParameterList_AddParameter(v2, 0x68u, v3, "Font Resource", 7u, nullptr);
  ParameterList_AddParameter(
    ColumnView_ptParameterList,
    0x110u,
    Level_eParameterTypeVarString,
    "Collect Items Script",
    7u,
    nullptr);
  ParameterList_AddParameter(
    ColumnView_ptParameterList,
    0x160u,
    Level_eParameterTypeVarString,
    "Get Data Script",
    7u,
    nullptr);
  ParameterList_AddParameter(
    ColumnView_ptParameterList,
    0x1B0u,
    Level_eParameterTypeVarString,
    "Set Data Script",
    7u,
    nullptr);
  ParameterList_AddParameter(ColumnView_ptParameterList, 0x30u, Level_eParameterTypeInt32, "Width", 7u, nullptr);
  ParameterList_AddParameter(ColumnView_ptParameterList, 0x34u, Level_eParameterTypeInt32, "Height", 7u, nullptr);
  ParameterList_AddParameter(
    ColumnView_ptParameterList,
    0x200u,
    Level_eParameterTypeVarString,
    "On Select Item",
    7u,
    nullptr);
  ParameterList_AddParameter(ColumnView_ptParameterList, 0xC0u, Level_eParameterTypeVarString, "On Run", 7u, nullptr);
  ParameterList_AddParameter(ColumnView_ptParameterList, 0x250u, Level_eParameterTypeVarString, "On Focus", 7u, nullptr);
  ParameterList_AddParameter(
    ColumnView_ptParameterList,
    0x2A0u,
    Level_eParameterTypeVarString,
    "Is Enabled",
    7u,
    nullptr);
  Symbol_Register(
    "ColumnView_Sort",
    ColumnView_ScriptSortFunction,
    nullptr,
    3,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}

// source: j/0/menusystem/columnview.c:1279  [anchor-hash]
void __cdecl ColumnView_Close()
{
  int v0; // esi

  Symbol_Remove("ColumnView_Sort");
  QTask_DeleteQTaskEvent(ColumnView_eAddEntryQTaskEvent);
  QTask_DeleteQTaskEvent(ColumnView_eDeleteEntryQTaskEvent);
  QTask_DeleteQTaskEvent(ColumnView_eSortEntriesQTaskEvent);
  QTask_DeleteQTaskEvent(ColumnView_eDrawEntriesQTaskEvent);
  if ( ColumnView_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&ColumnView_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(ColumnView_eQTaskType);
  ColumnView_eQTaskType = 512;
}
