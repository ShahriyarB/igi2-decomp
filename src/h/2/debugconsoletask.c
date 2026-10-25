/* h/2/debugconsoletask.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/debugconsoletask.c:158  [anchor-mhash]
void __cdecl DebugConsoleTask_DeAllocateResources(struct DebugConsoleTask_s *ptDebugConsoleTask)
{
  int i; // ebx
  struct StaticTilemap_s *v2; // esi
  int v3; // esi
  char *v4; // eax
  int v5; // esi
  struct StaticTilemap_s **aptText; // eax
  int v7; // ebx
  char **azWindowText; // eax
  int v9; // ebx

  if ( ptDebugConsoleTask->aptText )
  {
    for ( i = 0; i < ptDebugConsoleTask->nLines; ++i )
    {
      v2 = ptDebugConsoleTask->aptText[i];
      QTilemap_Delete(v2->ptQTilemap);
      v3 = *(_DWORD *)((unsigned int)&v2[-1].bQGraphicFlags & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v3);
      memset(*(void **)(v3 + 8), 0xCDu, *(_DWORD *)(v3 + 16));
      free((void *)v3);
      v4 = ptDebugConsoleTask->azWindowText[i];
      if ( v4 )
      {
        v5 = *(_DWORD *)((unsigned int)(v4 - 4) & 0xFFFFFFFC);
        --Mem_nCurrentAllocations;
        Node_Remove((_DWORD **)v5);
        memset(*(void **)(v5 + 8), 0xCDu, *(_DWORD *)(v5 + 16));
        free((void *)v5);
      }
      ptDebugConsoleTask->azWindowText[i] = nullptr;
    }
    aptText = ptDebugConsoleTask->aptText;
    if ( aptText )
    {
      --Mem_nCurrentAllocations;
      v7 = *(_DWORD *)((unsigned int)(aptText - 1) & 0xFFFFFFFC);
      Node_Remove((_DWORD **)v7);
      memset(*(void **)(v7 + 8), 0xCDu, *(_DWORD *)(v7 + 16));
      free((void *)v7);
    }
    azWindowText = ptDebugConsoleTask->azWindowText;
    ptDebugConsoleTask->aptText = nullptr;
    if ( azWindowText )
    {
      --Mem_nCurrentAllocations;
      v9 = *(_DWORD *)((unsigned int)(azWindowText - 1) & 0xFFFFFFFC);
      Node_Remove((_DWORD **)v9);
      memset(*(void **)(v9 + 8), 0xCDu, *(_DWORD *)(v9 + 16));
      free((void *)v9);
    }
    ptDebugConsoleTask->azWindowText = nullptr;
  }
  if ( ptDebugConsoleTask->isRenderContext )
  {
    RenderContext_DeAlloc(&ptDebugConsoleTask->tRenderContext);
    ptDebugConsoleTask->isRenderContext = false;
  }
  ptDebugConsoleTask->nLines = 0;
  ptDebugConsoleTask->nColumns = 0;
}

// source: h/2/debugconsoletask.c:198  [size]
void __cdecl DebugConsoleTask_AllocateResources(struct DebugConsoleTask_s *ptDebugConsoleTask)
{
  struct QSprite_s *v1; // edx
  int StringWidth; // eax
  struct StaticTilemap_s **v3; // eax
  int v4; // ecx
  int i; // ebx
  int v6; // eax
  int nY; // [esp+0h] [ebp-28h]
  float nYa; // [esp+0h] [ebp-28h]
  float tMax; // [esp+18h] [ebp-10h]
  float tMax_4; // [esp+1Ch] [ebp-Ch]

  v1 = DebugConsoleTask_ptFont;
  if ( DebugConsoleTask_ptFont && AppContext_tAppContext.isMainMenu == false )
  {
    tMax = (float)Display_tActiveMode.nWidth;
    tMax_4 = (float)Display_tActiveMode.nHeight;
    ptDebugConsoleTask->nLines = (__int64)(tMax_4
                                         / (double)DebugConsoleTask_ptFont->atQAnimframe[DebugConsoleTask_ptFont->nQAnimframes].nHeight);
    StringWidth = Font_GetStringWidth(v1, (char *)&Delimiter);
    nY = 4 * ptDebugConsoleTask->nLines;
    ptDebugConsoleTask->nColumns = (__int64)(tMax / (double)StringWidth);
    v3 = (struct StaticTilemap_s **)Mem_AllocFn(nY, 4);
    v4 = 4 * ptDebugConsoleTask->nLines;
    ptDebugConsoleTask->aptText = v3;
    ptDebugConsoleTask->azWindowText = (char **)Mem_AllocFn(v4, 4);
    for ( i = 0; i < ptDebugConsoleTask->nLines; ++i )
    {
      nYa = (float)(i * DebugConsoleTask_ptFont->atQAnimframe[DebugConsoleTask_ptFont->nQAnimframes].nHeight);
      ptDebugConsoleTask->aptText[i] = Text_New(DebugConsoleTask_ptFont, 0.0, nYa, (char *)&g_zInitialValue);
      ptDebugConsoleTask->azWindowText[i] = (char *)Mem_AllocFn(ptDebugConsoleTask->nColumns + 1, 4);
      memset(ptDebugConsoleTask->azWindowText[i], 0x20u, ptDebugConsoleTask->nColumns);
      ptDebugConsoleTask->azWindowText[i][ptDebugConsoleTask->nColumns] = 0;
    }
    RenderContext_Alloc(&ptDebugConsoleTask->tRenderContext, 1);
    ptDebugConsoleTask->tRenderContext.tDisplayAreaMin.vX = 0.0;
    ptDebugConsoleTask->tRenderContext.tDisplayAreaMax.vY = tMax_4;
    v6 = RenderContext_nActiveRenderContextTimeStamp;
    ptDebugConsoleTask->tRenderContext.tDisplayAreaMin.vY = 0.0;
    ptDebugConsoleTask->tRenderContext.tDisplayAreaMax.vX = tMax;
    ptDebugConsoleTask->isRenderContext = true;
    RenderContext_nActiveRenderContextTimeStamp = v6 + 1;
  }
}

// source: h/2/debugconsoletask.c:251  [anchor-strings]
void __cdecl DebugConsoleTask_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v4; };
    struct { char igi2_o1[20]; char zName[64]; };
    char igi2_extent[84];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  bool v2; // zf
  DWORD TickCount; // eax

  DebugConsoleTask_ptQTaskRef = QTask_NewQTaskRef(ptQTask);
  igi2_frame.v4 = DebugConsoleTask_nID++;
  sprintf(igi2_frame.zName, "Debug console %d", igi2_frame.v4);
  strcpy((char *)&ptQTask[1], "LOCAL:debug.fnt");
  if ( Resource_IsLoadedInternal((char *)&ptQTask[1], nullptr) || File_Exists((char *)&ptQTask[1]) )
    DebugConsoleTask_ptFont = FontManager_LoadFont((char *)&ptQTask[1]);
  ptQTask[10].ptParent = (struct QTask_s *)1065353216;
  *(_DWORD *)&ptQTask[10].eQTaskType = 1065353216;
  ptQTask[11].ptNext = (struct QTask_s *)1065353216;
  ptQTask[11].tQTaskChildren.ptTail = (struct QTask_s *)1056964608;
  ptQTask[11].tQTaskRefList.ptHead = (struct QReference_s *)1061158912;
  ptQTask[11].tQTaskRefList.ptMiddle = (struct QReference_s *)1063339950;
  ptQTask[11].ptPrev = nullptr;
  ptQTask[11].tQTaskChildren.ptHead = nullptr;
  ptQTask[11].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[11].tQTaskRefList.ptTail = (struct QReference_s *)1056964608;
  ptQTask[10].tQTaskChildren.ptTail = nullptr;
  ptQTask[10].tQTaskRefList.ptHead = nullptr;
  ptQTask[10].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[7].tQTaskRefList.ptTail = nullptr;
  ptQTask[8].ptPrev = nullptr;
  ptQTask[8].ptNext = nullptr;
  ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[10].tQTaskRefList.ptTail = (struct QReference_s *)DebugConsole_Alloc(igi2_frame.zName, 100);
  v2 = Timer_isPerformanceCounter == 0;
  ptQTask[11].ptParent = nullptr;
  ptQTask[10].tQTaskChildren.ptHead = nullptr;
  ptQTask[7].ptParent = nullptr;
  *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  *(_DWORD *)&ptQTask[11].eQTaskType = 0;
  if ( v2 )
    TickCount = GetTickCount();
  else
    TickCount = Timer_GetPerformanceCounter();
  ptQTask[12].ptNext = (struct QTask_s *)(TickCount - Timer_nStartTime);
  ptQTask[12].ptPrev = (struct QTask_s *)1077936128;
  ptQTask[10].ptPrev = nullptr;
  ptQTask[15].tQTaskChildren.ptTail = nullptr;
  ptQTask[7].tQTaskRefList.ptHead = nullptr;
  ptQTask[7].tQTaskChildren.ptTail = nullptr;
  ptQTask[15].tQTaskRefList.ptHead = (struct QReference_s *)1;
  memset(&ptQTask[12].tQTaskChildren, 0, 0x80u);
  if ( DebugConsoleTask_isCreateRootWindow )
  {
    QTask_NewFn(ptQTask, DebugConsoleWindow_eQTaskType, nullptr);
    DebugConsoleTask_isCreateRootWindow = false;
  }
}

// source: h/2/debugconsoletask.c:345  [anchor-mhash]
void __cdecl DebugConsoleTask_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptParent; // eax
  int v2; // ecx
  struct QTaskNodeList_s *p_tQTaskChildren; // ebx
  int v4; // esi
  int ptQTaska = *(int *)&ptQTask; // [esp+10h] [ebp+4h] ARGSLOT

  if ( DebugConsoleTask_ptFont )
  {
    FontManager_DeleteFont(DebugConsoleTask_ptFont);
    DebugConsoleTask_ptFont = nullptr;
  }
  DebugConsoleTask_DeAllocateResources((struct DebugConsoleTask_s *)ptQTask);
  DebugConsole_DeAlloc((int)ptQTask[10].tQTaskRefList.ptTail);
  ptParent = ptQTask[11].ptParent;
  if ( ptParent )
  {
    QReference_Delete((struct QReference_s *)ptParent, &QTask_tQTaskRefPool);
    ptQTask[11].ptParent = nullptr;
  }
  if ( DebugConsoleTask_ptQTaskRef )
  {
    QReference_Delete(DebugConsoleTask_ptQTaskRef, &QTask_tQTaskRefPool);
    DebugConsoleTask_ptQTaskRef = nullptr;
  }
  v2 = *(_DWORD *)&ptQTask[11].eQTaskType;
  if ( v2 )
    KeyboardBuffer_Release(v2);
  p_tQTaskChildren = &ptQTask[12].tQTaskChildren;
  ptQTaska = 32;
  do
  {
    if ( p_tQTaskChildren->ptHead )
    {
      v4 = *(_DWORD *)((int)&p_tQTaskChildren->ptHead[-1].eQTaskType & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v4);
      memset(*(void **)(v4 + 8), 0xCDu, *(_DWORD *)(v4 + 16));
      free((void *)v4);
      p_tQTaskChildren->ptHead = nullptr;
    }
    p_tQTaskChildren = (struct QTaskNodeList_s *)((char *)p_tQTaskChildren + 4);
    --ptQTaska;
  }
  while ( ptQTaska );
}

// source: h/2/debugconsoletask.c:383  [anchor-hash]
void __cdecl DebugConsoleTask_SetActiveWindow(struct QTask_s *ptWindow)
{
  _DWORD *pxObject; // esi
  struct QReference_s *v2; // eax

  if ( DebugConsoleTask_ptQTaskRef )
    pxObject = DebugConsoleTask_ptQTaskRef->pxObject;
  else
    pxObject = nullptr;
  v2 = (struct QReference_s *)pxObject[118];
  if ( v2 )
  {
    QReference_Delete(v2, &QTask_tQTaskRefPool);
    pxObject[118] = 0;
  }
  if ( ptWindow )
  {
    pxObject[118] = QTask_NewQTaskRef(ptWindow);
    pxObject[102] = 1;
    pxObject[76] = 0;
  }
}

// source: h/2/debugconsoletask.c:410  [anchor-mhash]
struct QTask_s *__cdecl DebugConsoleTask_FindFirstWindow(
        struct QTask_s *ptParent,
        enum bool isRight)
{
  struct QTask_s *v2; // edi
  struct QTask_s **v3; // esi
  struct QTask_s **v4; // ebx
  struct QTask_s *ptThis; // [esp+Ch] [ebp-4h] BYREF

  v2 = ptParent;
  v3 = isRight != false ? &ptThis : nullptr;
  v4 = isRight != false ? nullptr : &ptThis;
  if ( DebugConsoleWindow_GetChildWindows(ptParent, v4, v3) == 2 )
  {
    do
      v2 = ptThis;
    while ( DebugConsoleWindow_GetChildWindows(ptThis, v4, v3) == 2 );
  }
  return v2;
}

// source: h/2/debugconsoletask.c:432  [anchor-mhash]
struct QTask_s *__cdecl DebugConsoleTask_FindNextWindow(struct QTask_s *ptParent, enum bool isPrev)
{
  struct QTask_s *v2; // edi
  struct QTask_s *v3; // esi
  int v4; // ecx
  bool v5; // zf
  struct QTask_s *v6; // ecx
  struct QTask_s *result; // eax
  struct QTask_s *ptRight; // [esp+Ch] [ebp-4h] BYREF

  v2 = ptParent;
  v3 = ptParent->ptParent;
  if ( !v3
    || QTask_IsQTaskTypeDerived(v3->eQTaskType, DebugConsoleWindow_eQTaskType) == false
    || DebugConsoleWindow_GetChildWindows(v3, &ptParent, &ptRight) != 2 )
  {
    return v2;
  }
  v4 = 0;
  if ( isPrev )
    v5 = v2 == ptRight;
  else
    v5 = v2 == ptParent;
  LOBYTE(v4) = v5;
  if ( !v4 )
  {
    result = DebugConsoleTask_FindNextWindow(v3, isPrev);
    if ( result != v3 )
      return result;
    return v2;
  }
  v6 = ptParent;
  if ( isPrev == false )
    v6 = ptRight;
  return DebugConsoleTask_FindFirstWindow(v6, isPrev);
}

// source: h/2/debugconsoletask.c:476  [anchor-caller]
void __cdecl DebugConsoleTask_RunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *v1; // edi
  struct QTask_s *ptPrev; // eax
  int ptHead; // eax
  int v4; // edx
  struct QTask_s *v5; // ecx
  int v6; // ecx
  int v7; // eax
  struct QTask_s *ptParent; // eax
  struct QTask_s *v9; // ebp
  struct QTask_s *i; // esi
  int v11; // ecx
  bool v12; // zf
  struct QTask_s *v13; // eax
  int j; // eax
  int v15; // ecx
  struct QTask_s *v16; // ebp
  BOOL v17; // eax
  BOOL v18; // esi
  struct QTask_s *NextWindow; // eax
  struct QTask_s *v20; // eax

  v1 = ptQTask;
  if ( ptQTask[7].tQTaskRefList.ptHead )
  {
    Keyboard_tKeyboard.isLocked = 0;
    Keyboard_Update();
    if ( (Keyboard_tKeyboard.anCurrentKey[1] & 0x80u) == 0 )
    {
      v1[7].tQTaskRefList.ptHead = nullptr;
    }
    else
    {
      Keyboard_tKeyboard.isLocked = 1;
      Keyboard_Update();
    }
  }
  ptPrev = v1[10].ptPrev;
  if ( ptPrev )
    v1[10].ptPrev = (struct QTask_s *)((char *)ptPrev - 1);
  if ( v1[8].ptNext || v1[8].ptPrev )
  {
    ptHead = (int)v1->tQTaskChildren.ptHead;
    if ( *(_DWORD *)ptHead && ptHead )
    {
      v4 = QTask_nProtectedQTaskStackOffset;
      do
      {
        if ( *(_DWORD *)ptHead )
          v5 = **(_DWORD **)ptHead != 0 ? *(struct QTask_s **)ptHead : nullptr;
        else
          v5 = nullptr;
        QTask_atProtectedQTaskStack[v4].ptQTask = v5;
        v6 = *(unsigned __int16 *)(ptHead + 36);
        QTask_nProtectedQTaskStackOffset = v4 + 1;
        ((void (__cdecl *)(int))QTask_aatQTaskFinalEvent[1][v6].pfHandler)(ptHead);
        ptHead = dword_849C7DC[QTask_nProtectedQTaskStackOffset];
        v4 = --QTask_nProtectedQTaskStackOffset;
      }
      while ( ptHead );
    }
    if ( v1[8].ptPrev && !*(_DWORD *)&v1[11].eQTaskType )
    {
      v7 = KeyboardBuffer_nSP + 1;
      Keyboard_tKeyboard.isLocked = 1;
      KeyboardBuffer_anStack[v7] = v7;
      KeyboardBuffer_tKeyboardBuffer.nKeysInBuffer = 0;
      KeyboardBuffer_nSP = v7;
      *(_DWORD *)&v1[11].eQTaskType = v7;
    }
    ptParent = v1[11].ptParent;
    if ( ptParent && (v9 = ptParent->tQTaskChildren.ptHead) != nullptr )
    {
      if ( DebugConsoleWindow_GetChildWindows(v9, &ptQTask, nullptr) != 2 )
        goto LABEL_31;
      do
        i = ptQTask;
      while ( DebugConsoleWindow_GetChildWindows(ptQTask, &ptQTask, nullptr) == 2 );
      if ( i == v9 )
      {
LABEL_31:
        if ( v1[8].ptPrev )
          goto LABEL_35;
        goto LABEL_32;
      }
    }
    else
    {
      ptQTask = nullptr;
      if ( DebugConsoleWindow_GetChildWindows(v1, &ptQTask, nullptr) )
      {
        for ( i = ptQTask; DebugConsoleWindow_GetChildWindows(ptQTask, &ptQTask, nullptr) == 2; i = ptQTask )
          ;
      }
      else
      {
        i = ptQTask;
      }
    }
    DebugConsoleTask_SetActiveWindow(i);
    goto LABEL_31;
  }
LABEL_32:
  v11 = *(_DWORD *)&v1[11].eQTaskType;
  if ( v11 )
  {
    KeyboardBuffer_Release(v11);
    v12 = v1[7].tQTaskRefList.ptHead == nullptr;
    *(_DWORD *)&v1[11].eQTaskType = 0;
    if ( !v12 )
      Keyboard_tKeyboard.isLocked = 1;
  }
LABEL_35:
  if ( *(_DWORD *)&v1[11].eQTaskType )
  {
    v13 = v1[11].ptParent;
    if ( v13 )
    {
      if ( v13->tQTaskChildren.ptHead )
      {
        for ( j = KeyboardBuffer_GetChar(*(_DWORD *)&v1[11].eQTaskType);
              j;
              j = KeyboardBuffer_GetChar(*(_DWORD *)&v1[11].eQTaskType) )
        {
          v15 = BYTE1(j);
          if ( BYTE1(j) == 1 || (struct QReference_s *)BYTE1(j) == v1[15].tQTaskRefList.ptHead )
          {
            v1[8].ptPrev = nullptr;
            v1[8].ptNext = nullptr;
            v1[10].ptPrev = (struct QTask_s *)5;
            v1[7].tQTaskRefList.ptHead = (struct QReference_s *)1;
            DebugConsoleWindow_EnableDebugCommands(false);
          }
          else if ( (j & 0x40000) != 0 )
          {
            v16 = v1[11].ptParent->tQTaskChildren.ptHead;
            v17 = BYTE1(j) == 208 || BYTE1(j) == 205;
            v18 = v15 == 200 || v15 == 203;
            if ( v17 )
            {
              NextWindow = DebugConsoleTask_FindNextWindow(v16, false);
              DebugConsoleTask_SetActiveWindow(NextWindow);
            }
            if ( v18 )
            {
              v20 = DebugConsoleTask_FindNextWindow(v16, true);
              DebugConsoleTask_SetActiveWindow(v20);
            }
          }
          else
          {
            ptQTask = (struct QTask_s *)j;
            ((void (__cdecl *)(struct QTask_s *, struct QTask_s **))QTask_aatQTaskFinalEvent[DebugConsoleTask_eHandleConsoleKeystrokeEvent][v1[11].ptParent->tQTaskChildren.ptHead->eQTaskType].pfHandler)(
              v1[11].ptParent->tQTaskChildren.ptHead,
              &ptQTask);
          }
        }
      }
    }
  }
}

// source: h/2/debugconsoletask.c:638  [size~]
void __cdecl DebugConsoleTask_DrawHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vX; };
    struct { char igi2_o1[4]; float vY; };
    struct { char igi2_o2[4]; float vYa; };
    struct { char igi2_o3[8]; float vWidth; };
    struct { char igi2_o4[8]; float vWidtha; };
    struct { char igi2_o5[12]; float vHeight; };
    struct { char igi2_o6[16]; float vR; };
    struct { char igi2_o7[16]; float vRa; };
    struct { char igi2_o8[20]; float vG; };
    struct { char igi2_o9[20]; float vGa; };
    struct { char igi2_o10[24]; float vB; };
    struct { char igi2_o11[24]; float vBa; };
    struct { char igi2_o12[28]; float v37; };
    struct { char igi2_o13[56]; struct QTask_s *pptLeftChild; };
    struct { char igi2_o14[60]; float v39; };
    struct { char igi2_o15[64]; _DWORD v40[7]; };
    struct { char igi2_o16[92]; _DWORD v41[10]; };
    char igi2_extent[132];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char *pxObject; // ebp
  int v2; // edx
  int v3; // ecx
  int v4; // eax
  int v5; // ecx
  bool v6; // zf
  int v7; // eax
  int i; // edi
  struct QSprite_s *v9; // esi
  int StringWidth; // eax
  struct QAnimframe_s *atQAnimframe; // ecx
  int nHeight; // edx
  int v13; // esi
  double v14; // st7
  double v15; // st6
  double v16; // st5
  double v17; // st7
  double v18; // st7
  double v19; // st7
  int v20; // eax
  double v21; // st7
  double v22; // st6
  double v23; // st5
  DWORD PerformanceCounter; // eax

  if ( DebugConsoleTask_ptQTaskRef )
  {
    pxObject = (char *)DebugConsoleTask_ptQTaskRef->pxObject;
    if ( pxObject )
    {
      if ( *((_DWORD *)pxObject + 80) || *((_DWORD *)pxObject + 81) )
      {
        ScriptDebugger_UpdateWatchConsole();
        if ( *((_DWORD *)pxObject + 104)
          && DebugConsoleWindow_GetChildWindows((struct QTask_s *)pxObject, &igi2_frame.pptLeftChild, nullptr) )
        {
          if ( *((_DWORD *)pxObject + 81) )
            *((_DWORD *)pxObject + 120) = Timer_Read();
          v2 = *((_DWORD *)pxObject + 106);
          memset(igi2_frame.v41, 0, sizeof(igi2_frame.v41));
          memset(igi2_frame.v40, 0, sizeof(igi2_frame.v40));
          v3 = *((_DWORD *)pxObject + 104);
          igi2_frame.v41[3] = *((_DWORD *)pxObject + 103);
          v4 = *((_DWORD *)pxObject + 81);
          igi2_frame.v41[4] = v3;
          v5 = *((_DWORD *)pxObject + 76);
          igi2_frame.v41[1] = 0;
          igi2_frame.v41[2] = 0;
          igi2_frame.v41[0] = v2;
          igi2_frame.v41[6] = v4;
          igi2_frame.v41[7] = v5;
          igi2_frame.v39 = COERCE_FLOAT(Timer_Read());
          if ( *((float *)pxObject + 121) * 1000.0 + (double)*((int *)pxObject + 120) <= (double)SLODWORD(igi2_frame.v39)
            || (v6 = *((_DWORD *)pxObject + 74) == 0, igi2_frame.v41[5] = 1, !v6) )
          {
            igi2_frame.v41[5] = 0;
          }
          v7 = *((_DWORD *)pxObject + 118);
          if ( v7 )
            igi2_frame.v41[8] = *(_DWORD *)(v7 + 8);
          else
            igi2_frame.v41[8] = 0;
          igi2_frame.v41[9] = igi2_frame.v40;
          ((void (__cdecl *)(struct QTask_s *, _DWORD *))QTask_aatQTaskFinalEvent[DebugConsoleTask_eDrawConsoleQTaskEvent][igi2_frame.pptLeftChild->eQTaskType].pfHandler)(
            igi2_frame.pptLeftChild,
            igi2_frame.v41);
          for ( i = 0; i < (int)(*((_DWORD *)pxObject + 104)); ++i )
            Text_SetString(
              *(struct StaticTilemap_s **)(*((_DWORD *)pxObject + 105) + 4 * i),
              *(char **)(*((_DWORD *)pxObject + 106) + 4 * i));
          if ( *((_DWORD *)pxObject + 105) )
          {
            v9 = DebugConsoleTask_ptFont;
            StringWidth = Font_GetStringWidth(DebugConsoleTask_ptFont, (char *)&Delimiter);
            atQAnimframe = v9->atQAnimframe;
            igi2_frame.v39 = *(float *)&StringWidth;
            nHeight = atQAnimframe[v9->nQAnimframes].nHeight;
            igi2_frame.v39 = (float)StringWidth;
            qmemcpy(&RenderContext_tActiveRenderContext, pxObject + 328, sizeof(RenderContext_tActiveRenderContext));
            v13 = 0;
            ++RenderContext_nActiveRenderContextTimeStamp;
            *(float *)&igi2_frame.pptLeftChild = (float)nHeight;
            *((_DWORD *)pxObject + 83) = 0;
            *((_DWORD *)pxObject + 82) = 0;
            List_AddTail((_DWORD *)pxObject + 82, (int)&RenderContext_tDrawList);
            if ( igi2_frame.v40[2] && igi2_frame.v40[3] && *((_DWORD *)pxObject + 102) && *((_DWORD *)pxObject + 81) )
            {
              if ( *((float *)pxObject + 110) <= 1.0 )
                v14 = *((float *)pxObject + 110);
              else
                v14 = 1.0;
              if ( *((float *)pxObject + 109) <= 1.0 )
                v15 = *((float *)pxObject + 109);
              else
                v15 = 1.0;
              if ( *((float *)pxObject + 108) <= 1.0 )
                v16 = *((float *)pxObject + 108);
              else
                v16 = 1.0;
              igi2_frame.vB = v14 * 128.0;
              igi2_frame.vG = v15 * 128.0;
              igi2_frame.vR = v16 * 128.0;
              igi2_frame.vHeight = (double)(int)igi2_frame.v40[3] * *(float *)&igi2_frame.pptLeftChild;
              igi2_frame.vWidth = (double)(int)igi2_frame.v40[2] * igi2_frame.v39;
              igi2_frame.vY = (double)(int)igi2_frame.v40[1] * *(float *)&igi2_frame.pptLeftChild;
              igi2_frame.vX = (double)(int)igi2_frame.v40[0] * igi2_frame.v39;
              QSprite_RegisterBlankA(igi2_frame.vX, igi2_frame.vY, igi2_frame.vWidth, igi2_frame.vHeight, igi2_frame.vR, igi2_frame.vG, igi2_frame.vB, *((float *)pxObject + 117), 0x80000u, -1);
            }
            if ( *((int *)pxObject + 104) > 0 )
            {
              do
              {
                if ( *((float *)pxObject + 114) <= 1.0 )
                  v17 = *((float *)pxObject + 114);
                else
                  v17 = 1.0;
                *(float *)(*(_DWORD *)(*((_DWORD *)pxObject + 105) + 4 * v13) + 20) = v17 * 128.0;
                if ( *((float *)pxObject + 115) <= 1.0 )
                  v18 = *((float *)pxObject + 115);
                else
                  v18 = 1.0;
                *(float *)(*(_DWORD *)(*((_DWORD *)pxObject + 105) + 4 * v13) + 24) = v18 * 128.0;
                if ( *((float *)pxObject + 116) <= 1.0 )
                  v19 = *((float *)pxObject + 116);
                else
                  v19 = 1.0;
                *(float *)(*(_DWORD *)(*((_DWORD *)pxObject + 105) + 4 * v13) + 28) = v19 * 128.0;
                *(_DWORD *)(*(_DWORD *)(*((_DWORD *)pxObject + 105) + 4 * v13) + 32) = -1;
                v20 = *(_DWORD *)(*((_DWORD *)pxObject + 105) + 4 * v13);
                QTilemap_Register(
                  *(struct QTilemap_s **)v20,
                  *(float *)(v20 + 4),
                  *(float *)(v20 + 8),
                  *(float *)(v20 + 20),
                  *(float *)(v20 + 24),
                  *(float *)(v20 + 28),
                  *(float *)(v20 + 16),
                  *(float *)(v20 + 12),
                  *(_DWORD *)(v20 + 36) | 0x40000000,
                  *(_DWORD *)(v20 + 32));
                ++v13;
              }
              while ( v13 < (int)(*((_DWORD *)pxObject + 104)) );
            }
            if ( igi2_frame.v40[4] )
            {
              if ( *((float *)pxObject + 113) <= 1.0 )
                v21 = *((float *)pxObject + 113);
              else
                v21 = 1.0;
              if ( *((float *)pxObject + 112) <= 1.0 )
                v22 = *((float *)pxObject + 112);
              else
                v22 = 1.0;
              if ( *((float *)pxObject + 111) <= 1.0 )
                v23 = *((float *)pxObject + 111);
              else
                v23 = 1.0;
              igi2_frame.v37 = v21 * 128.0;
              igi2_frame.vBa = v22 * 128.0;
              igi2_frame.vGa = v23 * 128.0;
              igi2_frame.vRa = *(float *)&igi2_frame.pptLeftChild + 1.0;
              igi2_frame.vWidtha = (double)(int)igi2_frame.v40[6] * *(float *)&igi2_frame.pptLeftChild;
              igi2_frame.vYa = (double)(int)igi2_frame.v40[5] * igi2_frame.v39;
              QSprite_RegisterBlank(igi2_frame.vYa, igi2_frame.vWidtha, 2.0, igi2_frame.vRa, igi2_frame.vGa, igi2_frame.vBa, igi2_frame.v37, 0, -1);
            }
            RenderContext_RenderAll();
          }
        }
      }
      else
      {
        if ( Timer_isPerformanceCounter )
          PerformanceCounter = Timer_GetPerformanceCounter();
        else
          PerformanceCounter = GetTickCount();
        *((_DWORD *)pxObject + 120) = PerformanceCounter - Timer_nStartTime;
      }
    }
  }
}

void __cdecl sub_557460(struct DebugConsoleTask_s *ptDebugConsoleTask)
{
  DebugConsoleTask_DeAllocateResources(ptDebugConsoleTask);
  DebugConsoleTask_AllocateResources(ptDebugConsoleTask);
  if ( ptDebugConsoleTask->isSaveNow )
    Level_SaveQTask("debugconsole.qsc", &ptDebugConsoleTask->tQTask, true, false);
}

// source: h/2/debugconsoletask.c:793  [size]
void __cdecl DebugConsoleTask_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = DebugConsoleTask_ptParameterList;
}

// source: h/2/debugconsoletask.c:809  [anchor-mhash]
void __cdecl DebugConsoleTask_PrepareDeleteHandler(struct QTask_s *ptQTask)
{
  if ( ptQTask[7].ptParent )
    Level_SaveQTask("debugconsole.qsc", ptQTask, true, false);
}

// source: h/2/debugconsoletask.c:824  [anchor-mhash]
struct QTask_s *__cdecl DebugConsoleTask_SaveQTask(struct QTask_s *ptQTask, enum bool isForceSave)
{
  if ( ptQTask[7].ptParent || isForceSave )
    return (struct QTask_s *)Level_SaveQTask("debugconsole.qsc", ptQTask, true, false);
  return ptQTask;
}

// source: h/2/debugconsoletask.c:846  [size]
void __cdecl DebugConsoleTask_Zoom(enum bool isZoom)
{
  _DWORD *pxObject; // eax

  if ( DebugConsoleTask_ptQTaskRef )
  {
    pxObject = DebugConsoleTask_ptQTaskRef->pxObject;
    if ( pxObject )
      pxObject[76] = isZoom;
  }
}

// source: h/2/debugconsoletask.c:869  [anchor-hash]
enum bool __cdecl DebugConsoleTask_IsZoom()
{
  void *pxObject; // eax

  if ( DebugConsoleTask_ptQTaskRef && (pxObject = DebugConsoleTask_ptQTaskRef->pxObject) != nullptr )
    return *((_DWORD *)pxObject + 76);
  else
    return false;
}

// source: h/2/debugconsoletask.c:894  [anchor-callee]
void __cdecl DebugConsoleTask_SplitWindow(enum bool isVertical, int tNewConsoleID)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s *ptWindow; };
    struct { char igi2_o1[4]; struct QTask_s *ptRight; };
    char igi2_extent[8];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *pxObject; // esi
  struct QTask_s *ptParent; // eax
  struct QTask_s *i; // edi
  struct QTask_s *ptPrev; // esi
  struct QTask_s *v6; // esi
  struct QTask_s *v7; // ebx
  struct QTask_s *v8; // ebx

  if ( DebugConsoleTask_ptQTaskRef )
  {
    pxObject = (struct QTask_s *)DebugConsoleTask_ptQTaskRef->pxObject;
    if ( pxObject )
    {
      ptParent = pxObject[11].ptParent;
      if ( ptParent )
      {
        igi2_frame.ptWindow = ptParent->tQTaskChildren.ptHead;
        i = igi2_frame.ptWindow;
        if ( igi2_frame.ptWindow )
        {
LABEL_12:
          ptPrev = i[1].ptPrev;
          QTask_NewFn(i, DebugConsoleWindow_eQTaskType, nullptr)[1].ptPrev = ptPrev;
          v6 = i[1].ptPrev;
          QTask_NewFn(i, DebugConsoleWindow_eQTaskType, nullptr)[1].ptPrev = v6;
          i[1].ptNext = (struct QTask_s *)isVertical;
          DebugConsoleWindow_GetChildWindows(i, &igi2_frame.ptWindow, &igi2_frame.ptRight);
          v7 = igi2_frame.ptWindow;
          DebugConsoleTask_SetActiveWindow(igi2_frame.ptWindow);
          v7[1].ptPrev = (struct QTask_s *)tNewConsoleID;
          v7[1].tQTaskRefList.ptHead = (struct QReference_s *)tNewConsoleID;
          return;
        }
      }
      else
      {
        igi2_frame.ptWindow = nullptr;
      }
      if ( DebugConsoleWindow_GetChildWindows(pxObject, &igi2_frame.ptWindow, nullptr) )
      {
        for ( i = igi2_frame.ptWindow; DebugConsoleWindow_GetChildWindows(igi2_frame.ptWindow, &igi2_frame.ptWindow, nullptr) == 2; i = igi2_frame.ptWindow )
          ;
      }
      else
      {
        i = igi2_frame.ptWindow;
      }
      if ( i )
        goto LABEL_12;
      v8 = QTask_NewFn(pxObject, DebugConsoleWindow_eQTaskType, nullptr);
      DebugConsoleTask_SetActiveWindow(v8);
      v8[1].ptPrev = (struct QTask_s *)tNewConsoleID;
      v8[1].tQTaskRefList.ptHead = (struct QReference_s *)tNewConsoleID;
    }
  }
}

// source: h/2/debugconsoletask.c:949  [anchor-callee]
struct QTask_s *__cdecl DebugConsoleTask_FindWindow(int tConsoleID)
{
  struct QTask_s *pxObject; // eax

  if ( DebugConsoleTask_ptQTaskRef && (pxObject = (struct QTask_s *)DebugConsoleTask_ptQTaskRef->pxObject) != nullptr )
    return DebugConsoleWindow_FindWindow(pxObject, tConsoleID);
  else
    return nullptr;
}

// source: h/2/debugconsoletask.c:972  [anchor-hash]
enum bool __cdecl DebugConsoleTask_IsVisible()
{
  void *pxObject; // eax

  if ( DebugConsoleTask_ptQTaskRef && (pxObject = DebugConsoleTask_ptQTaskRef->pxObject) != nullptr )
    return *((_DWORD *)pxObject + 80);
  else
    return false;
}

// source: h/2/debugconsoletask.c:995  [size]
void __cdecl DebugConsoleTask_SetVisible(enum bool isVisible)
{
  _DWORD *pxObject; // eax

  if ( DebugConsoleTask_ptQTaskRef )
  {
    pxObject = DebugConsoleTask_ptQTaskRef->pxObject;
    if ( pxObject )
      pxObject[80] = isVisible;
  }
}

// source: h/2/debugconsoletask.c:1018  [anchor-hash]
enum bool __cdecl DebugConsoleTask_IsActive()
{
  void *pxObject; // eax

  if ( DebugConsoleTask_ptQTaskRef && (pxObject = DebugConsoleTask_ptQTaskRef->pxObject) != nullptr )
    return *((_DWORD *)pxObject + 81);
  else
    return false;
}

// source: h/2/debugconsoletask.c:1041  [size]
void __cdecl DebugConsoleTask_SetActive(enum bool isActive)
{
  _DWORD *pxObject; // eax

  if ( DebugConsoleTask_ptQTaskRef )
  {
    pxObject = DebugConsoleTask_ptQTaskRef->pxObject;
    if ( pxObject )
      pxObject[81] = isActive;
  }
}

// source: h/2/debugconsoletask.c:1063  [size]
void __cdecl DebugConsoleTask_HideTitle(enum bool isHideTitle)
{
  _DWORD *pxObject; // eax

  if ( DebugConsoleTask_ptQTaskRef )
  {
    pxObject = DebugConsoleTask_ptQTaskRef->pxObject;
    if ( pxObject )
      pxObject[74] = isHideTitle;
  }
}

// source: h/2/debugconsoletask.c:1085  [anchor-caller]
struct QTask_s *__cdecl DebugConsoleTask_LoadQTask(struct QTask_s *ptParent)
{
  struct QTask_s *QTask; // esi

  if ( Resource_IsLoadedInternal("debugconsole.qsc", nullptr) == false
    && File_Exists("debugconsole.qsc") == false
    || (QTask = Level_LoadQTask(ptParent, "debugconsole.qsc", false)) == nullptr )
  {
    DebugConsoleTask_isCreateRootWindow = true;
    QTask = QTask_NewFn(ptParent, DebugConsoleTask_eQTaskType, nullptr);
  }
  QTask_TriggerQTaskEventRecursively(QTask, ParameterList_eUpdateInternalDataQTaskEvent, nullptr);
  return QTask;
}

// source: h/2/debugconsoletask.c:1114  [anchor-hash]
void __cdecl DebugConsoleTask_Unload()
{
  struct QReference_s *v0; // eax

  v0 = DebugConsoleTask_ptQTaskRef;
  if ( DebugConsoleTask_ptQTaskRef )
  {
    if ( DebugConsoleTask_ptQTaskRef->pxObject )
    {
      QTask_Delete((struct QTask_s *)DebugConsoleTask_ptQTaskRef->pxObject);
      v0 = DebugConsoleTask_ptQTaskRef;
    }
    if ( v0 )
    {
      QReference_Delete(v0, &QTask_tQTaskRefPool);
      DebugConsoleTask_ptQTaskRef = nullptr;
    }
  }
}

// source: h/2/debugconsoletask.c:1131  [size]
unsigned __int16 __cdecl DebugConsoleTask_GetQTaskType()
{
  return DebugConsoleTask_eQTaskType;
}

// source: h/2/debugconsoletask.c:1144  [size]
__int16 __cdecl DebugConsoleTask_GetDrawConsoleQTaskEvent()
{
  return DebugConsoleTask_eDrawConsoleQTaskEvent;
}

// source: h/2/debugconsoletask.c:1157  [size]
__int16 __cdecl DebugConsoleTask_GetHandleConsoleKeystrokeQTaskEvent()
{
  return DebugConsoleTask_eHandleConsoleKeystrokeEvent;
}

// source: h/2/debugconsoletask.c:1170  [size]
struct QSprite_s *__cdecl DebugConsoleTask_GetFont()
{
  return DebugConsoleTask_ptFont;
}

// source: h/2/debugconsoletask.c:1183  [anchor-hash]
int __cdecl DebugConsoleTask_GetNumberOfHistoryItems()
{
  _DWORD *pxObject; // eax

  if ( DebugConsoleTask_ptQTaskRef && (pxObject = DebugConsoleTask_ptQTaskRef->pxObject) != nullptr )
    return pxObject[154];
  else
    return 0;
}

// source: h/2/debugconsoletask.c:1203  [anchor-callee]
char *__cdecl DebugConsoleTask_GetHistoryItem(int iItem)
{
  _DWORD *pxObject; // eax

  if ( DebugConsoleTask_ptQTaskRef
    && (pxObject = DebugConsoleTask_ptQTaskRef->pxObject) != nullptr
    && iItem < (int)(pxObject[154]) )
  {
    return (char *)pxObject[iItem + 122];
  }
  else
  {
    return (char *)&g_zInitialValue;
  }
}

// source: h/2/debugconsoletask.c:1227  [anchor-callee]
void __cdecl DebugConsoleTask_AddHistoryItem(char *zCommand)
{
  _DWORD *pxObject; // ebp
  signed int v2; // edi
  signed int v3; // esi
  int i; // ebx
  int v5; // eax
  int v6; // edi
  char **v7; // edx
  int v8; // eax
  int v9; // eax
  _DWORD *v10; // ebx
  int v11; // esi
  int v12; // ecx
  _DWORD *j; // eax

  if ( DebugConsoleTask_ptQTaskRef )
  {
    pxObject = DebugConsoleTask_ptQTaskRef->pxObject;
    if ( pxObject )
    {
      v2 = strlen(zCommand);
      v3 = 0;
      for ( i = 0; v3 < v2; ++v3 )
      {
        if ( _mb_cur_max_6aece0 <= 1 )
          v5 = pctype_6aecec[zCommand[v3]] & 8;
        else
          v5 = isctype(zCommand[v3], 8);
        if ( v5 )
          ++i;
      }
      if ( i != v2 )
      {
        v6 = 0;
        if ( (int)pxObject[154] <= 0 )
        {
LABEL_15:
          v8 = pxObject[154];
          if ( v8 == 31 )
          {
            v9 = pxObject[122];
            v10 = pxObject + 122;
            if ( v9 )
            {
              v11 = *(_DWORD *)((v9 - 4) & 0xFFFFFFFC);
              --Mem_nCurrentAllocations;
              Node_Remove((_DWORD **)v11);
              memset(*(void **)(v11 + 8), 0xCDu, *(_DWORD *)(v11 + 16));
              free((void *)v11);
            }
            *v10 = 0;
            qmemcpy(v10, pxObject + 123, 0x7Cu);
          }
          else
          {
            pxObject[154] = v8 + 1;
          }
          pxObject[pxObject[154] + 121] = Mem_AllocFn(strlen(zCommand) + 1, 4);
          strcpy((char *)pxObject[pxObject[154] + 121], zCommand);
        }
        else
        {
          v7 = (char **)(pxObject + 122);
          while ( strcmp(*v7, zCommand) )
          {
            ++v6;
            ++v7;
            if ( v6 >= (int)(pxObject[154]) )
              goto LABEL_15;
          }
          v12 = pxObject[v6 + 122];
          for ( j = &pxObject[v6 + 122]; v6 < (int)(pxObject[154] - 1); ++j )
          {
            *j = j[1];
            ++v6;
          }
          pxObject[pxObject[154] + 121] = v12;
        }
      }
    }
  }
}

// source: h/2/debugconsoletask.c:1292  [size]
void __cdecl DebugConsoleTask_SetExitKey(int nKey)
{
  _DWORD *pxObject; // eax

  if ( DebugConsoleTask_ptQTaskRef )
  {
    pxObject = DebugConsoleTask_ptQTaskRef->pxObject;
    if ( pxObject )
      pxObject[155] = nKey;
  }
}

// source: h/2/debugconsoletask.c:1311  [anchor-hash]
void __cdecl DebugConsoleTask_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  __int16 v1; // ax
  unsigned __int16 v2; // si
  struct ParameterList_s *v3; // eax
  int v4; // edx

  BaseQTaskType = QTask_GetBaseQTaskType();
  DebugConsoleTask_eQTaskType = QTask_NewQTaskType("DebugConsoleTask", 624, BaseQTaskType, 0, 0);
  DebugConsoleTask_eDrawConsoleQTaskEvent = QTask_NewQTaskEventFn(0, "DrawConsoleWindow");
  v1 = QTask_NewQTaskEventFn(0, "HandleConsoleKeystroke");
  v2 = DebugConsoleTask_eQTaskType;
  DebugConsoleTask_eHandleConsoleKeystrokeEvent = v1;
  QTask_LinkQTaskEventHandlerFn(DebugConsoleTask_eQTaskType, 0, DebugConsoleTask_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, 2, DebugConsoleTask_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, 1, DebugConsoleTask_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, 3, DebugConsoleTask_PrepareDeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v2,
    ParameterList_eUpdateInternalDataQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))sub_557460);
  QTask_LinkQTaskEventHandlerFn(
    v2,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))DebugConsoleTask_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v2,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  v3 = (struct ParameterList_s *)Mem_AllocFn(872, 4);
  v3->nParameters = 0;
  v3->nMaxParameters = 43;
  v4 = Level_eParameterTypebool8;
  v3->ptParameterListItem = (struct ParameterListItem_s *)&v3[1];
  DebugConsoleTask_ptParameterList = v3;
  ParameterList_AddParameter(v3, 0x140u, v4, "Visible", 7u, nullptr);
  ParameterList_AddParameter(
    DebugConsoleTask_ptParameterList,
    0x144u,
    Level_eParameterTypebool8,
    "Console active",
    7u,
    nullptr);
  ParameterList_AddParameter(
    DebugConsoleTask_ptParameterList,
    0x138u,
    Level_eParameterTypebool8,
    "AutoSave",
    7u,
    nullptr);
  ParameterList_AddParameter(
    DebugConsoleTask_ptParameterList,
    0x13Cu,
    Level_eParameterTypePushButton,
    "Save",
    6u,
    nullptr);
  ParameterList_AddParameter(
    DebugConsoleTask_ptParameterList,
    0x28u,
    Level_eParameterTypeString256,
    "Font name",
    7u,
    nullptr);
  ParameterList_AddParameter(
    DebugConsoleTask_ptParameterList,
    0x1C8u,
    Level_eParameterTypeRGB,
    "Font colour",
    7u,
    nullptr);
  ParameterList_AddParameter(
    DebugConsoleTask_ptParameterList,
    0x1B0u,
    Level_eParameterTypeRGB,
    "Background colour",
    7u,
    nullptr);
  ParameterList_AddParameter(
    DebugConsoleTask_ptParameterList,
    0x1BCu,
    Level_eParameterTypeRGB,
    "Cursor colour",
    7u,
    nullptr);
  ParameterList_AddParameterMinMax(
    DebugConsoleTask_ptParameterList,
    0x1D4u,
    Level_eParameterTypeReal32,
    "Background alpha",
    7u,
    0.0,
    1.0);
  ParameterList_AddParameterMinMax(
    DebugConsoleTask_ptParameterList,
    0x1E4u,
    Level_eParameterTypeReal32,
    "Titlebar lifetime",
    7u,
    0.0,
    10.0);
  ParameterList_AddParameter(
    DebugConsoleTask_ptParameterList,
    0x268u,
    Level_eParameterTypeInt32,
    "Command History Items",
    1u,
    nullptr);
  ParameterList_AddParameterArray(
    DebugConsoleTask_ptParameterList,
    0x1E8u,
    Level_eParameterTypeVarString,
    "Command History",
    1u,
    nullptr,
    4u,
    0x20u);
  Display_RegisterCallback((void (__cdecl *)())DebugConsoleTask_DrawHandler, &Display_ptEndFrameCallback);
}

// source: h/2/debugconsoletask.c:1359  [anchor-hash]
void __cdecl DebugConsoleTask_Close()
{
  struct DisplayCallbackChain_s *v0; // eax
  struct DisplayCallbackChain_s *v1; // ecx
  int v2; // esi

  v0 = Display_ptEndFrameCallback;
  v1 = nullptr;
  if ( Display_ptEndFrameCallback )
  {
    while ( (void (__cdecl *)(struct QTask_s *))v0->pfCallback != DebugConsoleTask_DrawHandler )
    {
      v1 = v0;
      v0 = v0->ptNext;
      if ( !v0 )
        goto LABEL_8;
    }
    if ( v1 )
      v1->ptNext = v0->ptNext;
    else
      Display_ptEndFrameCallback = v0->ptNext;
  }
LABEL_8:
  if ( DebugConsoleTask_ptParameterList )
  {
    v2 = *(_DWORD *)((unsigned int)&DebugConsoleTask_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v2);
    memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
    free((void *)v2);
  }
  QTask_DeleteQTaskEvent(DebugConsoleTask_eDrawConsoleQTaskEvent);
  QTask_DeleteQTaskEvent(DebugConsoleTask_eHandleConsoleKeystrokeEvent);
  QTask_DeleteQTaskType(DebugConsoleTask_eQTaskType);
}
