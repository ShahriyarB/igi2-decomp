/* h/2/debugconsolewindow.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/debugconsolewindow.c:104  [anchor-hash]
void __cdecl DebugConsoleWindow_ParseCls(int argc, char **argv, void *pxCommandContext)
{
  DebugConsole_ClearAll(DebugConsole_ptActiveDebugConsole, true);
}

// source: h/2/debugconsolewindow.c:119  [anchor-strings]
void __cdecl DebugConsoleWindow_ListCommandParser(int argc, char **argv, void *pxCommandContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct DebugConsoleWindow_s *ptDebugConsoleWindow; };
    struct { char igi2_o1[4]; char zText[512]; };
    char igi2_extent[516];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct DebugConsole_s *ptHead; // edx
  int tConsoleID; // edi
  void (__cdecl *pfDebugConsolePrintCallback)(char *, void *); // ecx
  struct DebugConsole_s *v6; // ebx
  struct DebugConsole_s *ptNext; // eax
  struct DebugConsole_s *v8; // ecx
  struct DebugConsole_s *v9; // eax
  int v10; // ecx
  int v11; // ecx
  char *zName; // esi
  struct DebugConsole_s *v13; // eax
  int v14; // ecx
  void (__cdecl *v15)(char *, void *); // ecx
  struct DebugConsole_s *v16; // ebx
  struct DebugConsole_s *v17; // eax
  struct DebugConsole_s *v18; // ecx

  igi2_frame.ptDebugConsoleWindow = (struct DebugConsoleWindow_s *)DebugConsoleWindow_ptActiveQTask;
  if ( DebugConsoleWindow_ptActiveQTask )
    DebugConsole_PushActiveConsole((int)DebugConsoleWindow_ptActiveQTask[1].ptPrev);
  ptHead = DebugConsole_tConsoleList.ptHead;
  if ( DebugConsole_tConsoleList.ptHead != (struct DebugConsole_s *)&DebugConsole_tConsoleList.ptMiddle )
  {
    tConsoleID = DebugConsole_tConsoleList.ptHead->tConsoleID;
    if ( tConsoleID != -1 )
    {
      strcpy(igi2_frame.zText, "\nID   Channel\n");
      pfDebugConsolePrintCallback = DebugConsole_ptActiveDebugConsole->pfDebugConsolePrintCallback;
      v6 = DebugConsole_ptActiveDebugConsole;
      if ( pfDebugConsolePrintCallback )
      {
        pfDebugConsolePrintCallback(igi2_frame.zText, DebugConsole_ptActiveDebugConsole->pxPrintCallbackContext);
        ptHead = DebugConsole_tConsoleList.ptHead;
      }
      if ( v6->nMaxLines )
      {
        DebugConsole_ParseCString(v6, igi2_frame.zText);
        ptHead = DebugConsole_tConsoleList.ptHead;
      }
      do
      {
        ptNext = ptHead->ptNext;
        v8 = ptHead;
        if ( ptHead->ptNext )
        {
          while ( v8->tConsoleID != tConsoleID )
          {
            v8 = ptNext;
            ptNext = ptNext->ptNext;
            if ( !ptNext )
              goto LABEL_12;
          }
          v9 = v8;
        }
        else
        {
LABEL_12:
          v9 = nullptr;
        }
        v10 = DebugConsole_nStackPointer + 1;
        DebugConsole_atActiveConsoleStack[v10] = tConsoleID;
        v11 = v10 - 1;
        zName = v9->zName;
        DebugConsole_nStackPointer = v11;
        if ( v11 <= 0 )
        {
          DebugConsole_ptActiveDebugConsole = nullptr;
        }
        else
        {
          v13 = ptHead->ptNext;
          if ( ptHead->ptNext )
          {
            v14 = DebugConsole_atActiveConsoleStack[v11];
            while ( ptHead->tConsoleID != v14 )
            {
              ptHead = v13;
              v13 = v13->ptNext;
              if ( !v13 )
                goto LABEL_18;
            }
          }
          else
          {
LABEL_18:
            ptHead = nullptr;
          }
          DebugConsole_ptActiveDebugConsole = ptHead;
        }
        sprintf(igi2_frame.zText, "%-4d %s\n", tConsoleID, zName);
        v15 = DebugConsole_ptActiveDebugConsole->pfDebugConsolePrintCallback;
        v16 = DebugConsole_ptActiveDebugConsole;
        if ( v15 )
          v15(igi2_frame.zText, DebugConsole_ptActiveDebugConsole->pxPrintCallbackContext);
        if ( v16->nMaxLines )
          DebugConsole_ParseCString(v16, igi2_frame.zText);
        ptHead = DebugConsole_tConsoleList.ptHead;
        v17 = DebugConsole_tConsoleList.ptHead->ptNext;
        v18 = DebugConsole_tConsoleList.ptHead;
        if ( DebugConsole_tConsoleList.ptHead->ptNext )
        {
          while ( v18->tConsoleID != tConsoleID )
          {
            v18 = v17;
            v17 = v17->ptNext;
            if ( !v17 )
              goto LABEL_29;
          }
        }
        else
        {
LABEL_29:
          v18 = nullptr;
        }
        if ( !v18->ptNext->ptNext )
          break;
        tConsoleID = v18->ptNext->tConsoleID;
      }
      while ( tConsoleID != -1 );
    }
  }
  if ( igi2_frame.ptDebugConsoleWindow )
    DebugConsole_PopActiveConsole();
}

// source: h/2/debugconsolewindow.c:171  [anchor-hash]
void __cdecl DebugConsoleWindow_ZoomCommandParser(int argc, char **argv, void *pxCommandContext)
{
  _DWORD *pxObject; // eax
  int v4; // edx
  _DWORD *v5; // eax

  if ( DebugConsoleWindow_ptActiveQTask )
  {
    if ( DebugConsoleTask_ptQTaskRef && (pxObject = DebugConsoleTask_ptQTaskRef->pxObject) != nullptr )
      v4 = pxObject[76];
    else
      v4 = 0;
    if ( DebugConsoleTask_ptQTaskRef )
    {
      v5 = DebugConsoleTask_ptQTaskRef->pxObject;
      if ( v5 )
        v5[76] = v4 == 0;
    }
  }
}

// source: h/2/debugconsolewindow.c:190  [anchor-caller]
void __cdecl DebugConsoleWindow_SetConsoleParser(int argc, char **argv, void *pxCommandContext)
{
  struct QTask_s *v3; // ebx
  _DWORD *p_ptPrev; // esi
  int v5; // edi
  void (__cdecl *pfDebugConsolePrintCallback)(char *, void *); // ecx
  struct DebugConsole_s *v7; // ebx

  v3 = DebugConsoleWindow_ptActiveQTask;
  if ( DebugConsoleWindow_ptActiveQTask )
  {
    p_ptPrev = &DebugConsoleWindow_ptActiveQTask[1].ptPrev;
    DebugConsole_PushActiveConsole((int)DebugConsoleWindow_ptActiveQTask[1].ptPrev);
    if ( argc <= 1 )
    {
      pfDebugConsolePrintCallback = DebugConsole_ptActiveDebugConsole->pfDebugConsolePrintCallback;
      v7 = DebugConsole_ptActiveDebugConsole;
      if ( pfDebugConsolePrintCallback )
        pfDebugConsolePrintCallback("Syntax error\n", DebugConsole_ptActiveDebugConsole->pxPrintCallbackContext);
      if ( v7->nMaxLines )
        DebugConsole_ParseCString(v7, "Syntax error\n");
    }
    else
    {
      v5 = atoi(argv[1]);
      if ( DebugConsole_IsConsoleIDValid(v5) )
      {
        *p_ptPrev = v5;
        v3[1].tQTaskRefList.ptHead = (struct QReference_s *)v5;
      }
      else
      {
        DebugConsole_PrintCString("Invalid console ID\n");
      }
    }
    DebugConsole_PopActiveConsole();
  }
}

// source: h/2/debugconsolewindow.c:230  [anchor-mhash]
void __cdecl DebugConsoleWindow_SplitConsoleParser(int argc, char **argv, void *pxCommandContext)
{
  struct QTask_s *v3; // ebx
  struct QTask_s *v4; // edi
  struct QTask_s **p_ptPrev; // esi
  struct QTask_s *v6; // ebp
  struct QTask_s *v7; // esi
  struct QTask_s *v8; // esi
  struct QTask_s *ptPrev; // [esp+4h] [ebp-4h]

  v3 = DebugConsoleWindow_ptActiveQTask;
  if ( DebugConsoleWindow_ptActiveQTask )
  {
    v4 = DebugConsoleWindow_ptActiveQTask;
    p_ptPrev = &DebugConsoleWindow_ptActiveQTask[1].ptPrev;
    v6 = DebugConsoleWindow_ptActiveQTask;
    ptPrev = DebugConsoleWindow_ptActiveQTask[1].ptPrev;
    if ( !strcmp(*argv, "splitv") )
    {
      QTask_NewFn(DebugConsoleWindow_ptActiveQTask, DebugConsoleWindow_eQTaskType, nullptr)[1].ptPrev = ptPrev;
      v7 = *p_ptPrev;
      QTask_NewFn(v4, DebugConsoleWindow_eQTaskType, nullptr)[1].ptPrev = v7;
      v6[1].ptNext = (struct QTask_s *)1;
    }
    else
    {
      QTask_NewFn(DebugConsoleWindow_ptActiveQTask, DebugConsoleWindow_eQTaskType, nullptr)[1].ptPrev = ptPrev;
      v8 = *p_ptPrev;
      QTask_NewFn(v3, DebugConsoleWindow_eQTaskType, nullptr)[1].ptPrev = v8;
      v6[1].ptNext = nullptr;
    }
  }
}

// source: h/2/debugconsolewindow.c:258  [anchor-hash]
void __cdecl DebugConsoleWindow_KillParser(int argc, char **argv, void *pxCommandContext)
{
  struct QTask_s *v3; // esi
  struct QTask_s *ptParent; // edx
  struct QTask_s **p_ptParent; // edi
  struct QTask_s *v6; // esi
  unsigned __int16 v7; // cx
  void (__cdecl *pfDebugConsolePrintCallback)(char *, void *); // ecx
  struct DebugConsole_s *v9; // ebx

  v3 = DebugConsoleWindow_ptActiveQTask;
  if ( DebugConsoleWindow_ptActiveQTask )
  {
    ptParent = DebugConsoleWindow_ptActiveQTask->ptParent;
    p_ptParent = &DebugConsoleWindow_ptActiveQTask->ptParent;
    if ( QTask_IsQTaskTypeDerived(ptParent->eQTaskType, DebugConsoleWindow_eQTaskType) )
    {
      ptParent[1].tQTaskChildren.ptTail = nullptr;
      v6 = (*p_ptParent)->tQTaskChildren.ptHead->ptNext != nullptr ? (*p_ptParent)->tQTaskChildren.ptHead : nullptr;
      DebugConsoleTask_SetActiveWindow(*p_ptParent);
      if ( v6 )
      {
        v7 = DebugConsoleWindow_eQTaskType;
        do
        {
          if ( QTask_IsQTaskTypeDerived((*p_ptParent)->eQTaskType, v7) )
            v6[1].tQTaskChildren.ptHead = (struct QTask_s *)1;
          v6 = v6->ptNext;
        }
        while ( v6 && v6->ptNext );
      }
    }
    else
    {
      DebugConsole_PushActiveConsole((int)v3[1].ptPrev);
      pfDebugConsolePrintCallback = DebugConsole_ptActiveDebugConsole->pfDebugConsolePrintCallback;
      v9 = DebugConsole_ptActiveDebugConsole;
      if ( pfDebugConsolePrintCallback )
        pfDebugConsolePrintCallback(
          "Can't kill root window.\n",
          DebugConsole_ptActiveDebugConsole->pxPrintCallbackContext);
      if ( v9->nMaxLines )
        DebugConsole_ParseCString(v9, "Can't kill root window.\n");
      DebugConsole_PopActiveConsole();
    }
  }
}

// source: h/2/debugconsolewindow.c:307  [anchor-mhash]
void __cdecl DebugConsoleWindow_ChangeSizeParser(int argc, char **argv, void *pxCommandContext)
{
  struct QTask_s *v3; // ebp
  int v4; // ebx
  struct QTask_s *ptParent; // edx
  void (__cdecl *pfDebugConsolePrintCallback)(char *, void *); // ecx
  struct DebugConsole_s *v7; // ebx
  struct DebugConsoleWindow_s *ptDebugConsoleWindow; // [esp+8h] [ebp-4h]

  ptDebugConsoleWindow = (struct DebugConsoleWindow_s *)DebugConsoleWindow_ptActiveQTask;
  v3 = DebugConsoleWindow_ptActiveQTask;
  v4 = 1;
  if ( DebugConsoleWindow_ptActiveQTask )
  {
    if ( !strcmp(*argv, "shrink") )
      v4 = -1;
    if ( argc > 1 )
      v4 *= atoi(argv[1]);
    ptParent = v3->ptParent;
    if ( QTask_IsQTaskTypeDerived(ptParent->eQTaskType, DebugConsoleWindow_eQTaskType) )
    {
      if ( (ptParent->tQTaskChildren.ptHead->ptNext != nullptr ? ptParent->tQTaskChildren.ptHead : nullptr) != v3 )
        v4 = -v4;
      ptParent[1].tQTaskChildren.ptTail = (struct QTask_s *)((char *)ptParent[1].tQTaskChildren.ptTail + v4);
    }
    else
    {
      DebugConsole_PushActiveConsole(ptDebugConsoleWindow->tConsoleID);
      pfDebugConsolePrintCallback = DebugConsole_ptActiveDebugConsole->pfDebugConsolePrintCallback;
      v7 = DebugConsole_ptActiveDebugConsole;
      if ( pfDebugConsolePrintCallback )
        pfDebugConsolePrintCallback(
          "Can't resize root window.\n",
          DebugConsole_ptActiveDebugConsole->pxPrintCallbackContext);
      if ( v7->nMaxLines )
        DebugConsole_ParseCString(v7, "Can't resize root window.\n");
      DebugConsole_PopActiveConsole();
    }
  }
}

// source: h/2/debugconsolewindow.c:366  [anchor-callee]
int __cdecl DebugConsoleWindow_PrintWindow(
        struct DebugConsoleWindow_s *ptWindow,
        enum bool isShowTitle,
        enum bool isActive,
        enum bool isZoomed,
        int nX,
        int nY,
        int nWidth,
        int nHeight,
        char **azWindowText)
{
  #pragma pack(push, 1)
  union
  {
    struct { int nLines; };
    struct { int nLinesa; };
    struct { char igi2_o2[4]; int iLine; };
    struct { char igi2_o3[8]; char zTemp[80]; };
    char igi2_extent[88];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v9; // esi
  unsigned int v10; // eax
  char *v11; // edi
  char *v13; // edi
  char *v15; // edi
  char *v17; // edi
  int i; // ecx
  char v20; // al
  char *v21; // edx
  int v22; // ebp
  int v23; // edi
  char **v24; // edi
  int v25; // esi
  struct DebugConsoleLine_s *Line; // eax
  unsigned int j; // ecx
  int v28; // eax
  char *v29; // ecx
  char **v30; // ecx
  int v31; // edx
  int k; // eax
  int v33; // esi
  int v34; // edx
  struct DebugConsole_s *ptHead; // ecx
  struct DebugConsole_s *ptNext; // eax
  int v37; // edx

  v9 = nHeight;
  if ( nHeight <= 0 )
    return 0;
  DebugConsole_PushActiveConsole(ptWindow->tConsoleID);
  if ( isShowTitle )
  {
    strcpy(igi2_frame.zTemp, "- ");
    v10 = (char *)&DebugConsole_ptActiveDebugConsole->ptNext
        + strlen(DebugConsole_ptActiveDebugConsole->zName)
        + 1
        - (char *)DebugConsole_ptActiveDebugConsole;
    v11 = (char *)&igi2_frame.iLine + 3;
    while ( *++v11 )
      ;
    qmemcpy(v11, DebugConsole_ptActiveDebugConsole->zName, v10);
    if ( isActive )
    {
      v13 = (char *)&igi2_frame.iLine + 3;
      while ( *++v13 )
        ;
      strcpy(v13, " [Active]");
    }
    if ( isZoomed )
    {
      v15 = (char *)&igi2_frame.iLine + 3;
      while ( *++v15 )
        ;
      strcpy(v15, " [Maximised]");
    }
    v17 = (char *)&igi2_frame.iLine + 3;
    while ( *++v17 )
      ;
    strcpy(v17, " -");
    for ( i = 0; i < nWidth; v21[nX] = v20 )
    {
      if ( i >= (int)strlen(igi2_frame.zTemp) )
        v20 = 45;
      else
        v20 = igi2_frame.zTemp[i];
      v21 = &azWindowText[nY][i++];
    }
    ++nY;
    v9 = --nHeight;
  }
  v22 = 0;
  if ( v9 <= 0 )
  {
    v23 = igi2_frame.nLines;
  }
  else
  {
    v23 = DebugConsole_ptActiveDebugConsole->nLines;
    igi2_frame.nLinesa = v23;
    if ( v23 - v9 >= 0 )
    {
      igi2_frame.iLine = DebugConsole_ptActiveDebugConsole->nLines;
      if ( v23 >= v23 - v9 )
        igi2_frame.iLine = v23 - v9;
    }
    else
    {
      igi2_frame.iLine = 0;
    }
    if ( v9 < v23 )
    {
      igi2_frame.nLinesa = v9;
      v23 = v9;
    }
    if ( v23 > 0 )
    {
      v24 = &azWindowText[nY];
      do
      {
        v25 = (int)&(*v24)[nX];
        Line = DebugConsole_GetLine(DebugConsole_ptActiveDebugConsole, v22 + igi2_frame.iLine, false);
        if ( Line && nWidth )
        {
          for ( j = 0; j < Line->tQString.nLength; ++j )
          {
            if ( j >= nWidth )
              break;
            *(_BYTE *)(j + v25) = Line->tQString.tPrivate.patQStringChar[j];
          }
          v28 = j;
        }
        else
        {
          v28 = 0;
        }
        for ( ; v28 < nWidth; v29[nX] = 32 )
          v29 = &(*v24)[v28++];
        ++v22;
        ++v24;
      }
      while ( v22 < igi2_frame.nLinesa );
      v9 = nHeight;
      v23 = igi2_frame.nLinesa;
    }
    if ( v22 < v9 )
    {
      v30 = &(&azWindowText[nY])[v22];
      v31 = v9 - v22;
      do
      {
        for ( k = 0; k < nWidth; (*v30)[v33] = 32 )
        {
          v33 = k + nX;
          ++k;
        }
        ++v30;
        --v31;
      }
      while ( v31 );
    }
  }
  v34 = --DebugConsole_nStackPointer;
  if ( DebugConsole_nStackPointer <= 0 )
  {
    DebugConsole_ptActiveDebugConsole = nullptr;
    return v23;
  }
  else
  {
    ptHead = DebugConsole_tConsoleList.ptHead;
    ptNext = DebugConsole_tConsoleList.ptHead->ptNext;
    if ( DebugConsole_tConsoleList.ptHead->ptNext )
    {
      v37 = DebugConsole_atActiveConsoleStack[v34];
      while ( ptHead->tConsoleID != v37 )
      {
        ptHead = ptNext;
        ptNext = ptNext->ptNext;
        if ( !ptNext )
          goto LABEL_53;
      }
    }
    else
    {
LABEL_53:
      ptHead = nullptr;
    }
    DebugConsole_ptActiveDebugConsole = ptHead;
    return v23;
  }
}

// source: h/2/debugconsolewindow.c:463  [anchor-mhash]
void __cdecl DebugConsoleWindow_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v2; // eax
  bool v3; // zf
  DWORD TickCount; // eax

  ptQTask[2].ptParent = nullptr;
  ptQTask[2].tQTaskRefList.ptHead = nullptr;
  ptQTask[2].tQTaskChildren.ptTail = (struct QTask_s *)64;
  ptQTask[2].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[2].tQTaskRefList.ptTail = nullptr;
  QString_ReAlloc((struct QString_s *)&ptQTask[2].tQTaskChildren.ptTail, 0x80u);
  ptQTask[2].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[2].ptNext = nullptr;
  *(_DWORD *)&ptQTask[1].eQTaskType = 64;
  ptQTask[2].ptPrev = nullptr;
  ptQTask[2].tQTaskChildren.ptHead = nullptr;
  QString_ReAlloc((struct QString_s *)&ptQTask[1].eQTaskType, 0x80u);
  v2 = (struct QTask_s *)DebugConsole_atActiveConsoleStack[DebugConsole_nStackPointer];
  ptQTask[1].ptPrev = v2;
  ptQTask[1].tQTaskRefList.ptHead = (struct QReference_s *)v2;
  v3 = Timer_isPerformanceCounter == 0;
  ptQTask[1].ptNext = nullptr;
  ptQTask[1].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[1].tQTaskChildren.ptTail = nullptr;
  ptQTask[3].ptNext = nullptr;
  ptQTask[1].ptParent = nullptr;
  ptQTask[1].tQTaskRefList.ptTail = nullptr;
  ptQTask[1].tQTaskRefList.ptMiddle = (struct QReference_s *)1;
  ptQTask[1].tQTaskChildren.ptHead = nullptr;
  if ( v3 )
    TickCount = GetTickCount();
  else
    TickCount = Timer_GetPerformanceCounter();
  *(_DWORD *)&ptQTask[2].eQTaskType = TickCount - Timer_nStartTime;
  ptQTask[3].ptPrev = (struct QTask_s *)-1;
}

// source: h/2/debugconsolewindow.c:494  [anchor-mhash]
void __cdecl DebugConsoleWindow_DeleteHandler(struct QTask_s *ptQTask)
{
  QString_DeAlloc((struct QString_s *)&ptQTask[2].tQTaskChildren.ptTail);
  QString_DeAlloc((struct QString_s *)&ptQTask[1].eQTaskType);
}

// source: h/2/debugconsolewindow.c:511  [anchor-caller]
void __cdecl DebugConsoleWindow_HandleConsoleKeystrokeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zTemp[4]; };
    struct { char igi2_o1[4]; char zCommand[128]; };
    char igi2_extent[132];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // ecx
  int v3; // eax
  struct QTask_s *ptNext; // eax
  struct QTask_s *v5; // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *v7; // ecx
  char *HistoryItem; // eax
  char *v9; // esi
  unsigned int v10; // eax
  unsigned int v11; // esi
  char *v12; // eax
  struct QTask_s *v13; // ecx
  char *v14; // eax
  int v15; // eax
  int v16; // eax
  struct QTask_s *v17; // eax
  struct QTask_s *v18; // eax
  struct QTask_s *ptParent; // ecx
  unsigned int v20; // eax
  struct QTask_s *v21; // eax
  struct QTask_s *v22; // eax

  if ( ptQTask[1].tQTaskRefList.ptMiddle )
  {
    v2 = *(_DWORD *)pxContext;
    v3 = (unsigned __int8)BYTE1(*(_DWORD *)pxContext);
    igi2_frame.zTemp[0] = 0;
    igi2_frame.zTemp[1] = 0;
    switch ( v3 )
    {
      case 203:
        ptNext = ptQTask[3].ptNext;
        if ( ptNext )
          ptQTask[3].ptNext = (struct QTask_s *)((char *)ptNext - 1);
        goto LABEL_50;
      case 205:
        v5 = ptQTask[3].ptNext;
        if ( (int)v5 < (int)ptQTask[2].ptParent )
          ptQTask[3].ptNext = (struct QTask_s *)((char *)&v5->ptNext + 1);
        goto LABEL_50;
      case 211:
        if ( ptQTask[2].ptParent )
          QString_DeleteSubstring(
            (struct QString_s *)&ptQTask[2].tQTaskChildren.ptTail,
            (unsigned int)ptQTask[3].ptNext,
            1u);
        goto LABEL_50;
      case 1:
        if ( ptQTask[2].ptParent )
          ptQTask[2].ptParent = nullptr;
        ptQTask[3].ptNext = nullptr;
        ptQTask[3].ptPrev = (struct QTask_s *)-1;
        goto LABEL_50;
      case 200:
        if ( (int)ptQTask[3].ptPrev < 0 )
          ptQTask[3].ptPrev = (struct QTask_s *)DebugConsoleTask_GetNumberOfHistoryItems();
        ptPrev = ptQTask[3].ptPrev;
        if ( (int)ptPrev <= 0 )
          goto LABEL_50;
        v7 = (struct QTask_s *)((char *)ptPrev - 1);
        ptQTask[3].ptPrev = (struct QTask_s *)((char *)ptPrev - 1);
        HistoryItem = DebugConsoleTask_GetHistoryItem((int)(&ptPrev[-1].isInMemPool + 1));
        v9 = HistoryItem + 1;
        v10 = (unsigned int)&HistoryItem[strlen(HistoryItem) + 1];
LABEL_20:
        v11 = v10 - (_DWORD)v9;
        v12 = DebugConsoleTask_GetHistoryItem((int)v7);
        QString_FromCString((struct QString_s *)&ptQTask[2].tQTaskChildren.ptTail, v12, v11);
        ptQTask[3].ptNext = ptQTask[2].ptParent;
        goto LABEL_50;
      case 208:
        v13 = ptQTask[3].ptPrev;
        if ( (int)v13 < 0 || (int)v13 >= DebugConsoleTask_GetNumberOfHistoryItems() - 1 )
          goto LABEL_50;
        v7 = (struct QTask_s *)((char *)&v13->ptNext + 1);
        ptQTask[3].ptPrev = v7;
        v14 = DebugConsoleTask_GetHistoryItem((int)v7);
        v9 = v14 + 1;
        v10 = (unsigned int)&v14[strlen(v14) + 1];
        goto LABEL_20;
    }
    if ( v2 < 256 )
    {
      if ( v2 == 8 )
      {
        v22 = ptQTask[3].ptNext;
        if ( (int)v22 <= 0 )
          goto LABEL_50;
        QString_DeleteSubstring(
          (struct QString_s *)&ptQTask[2].tQTaskChildren.ptTail,
          (unsigned int)(&v22[-1].isInMemPool + 1),
          1u);
        v18 = (struct QTask_s *)((char *)ptQTask[3].ptNext - 1);
        goto LABEL_49;
      }
      if ( v2 == 13 )
      {
        DebugConsole_PushActiveConsole((int)ptQTask[1].ptPrev);
        ptParent = ptQTask[2].ptParent;
        v20 = 0;
        if ( ptParent )
        {
          do
          {
            if ( v20 >= 0x7F )
              break;
            igi2_frame.zCommand[v20] = *((_BYTE *)&ptQTask[2].tQTaskRefList.ptMiddle->ptNext + v20);
            ++v20;
          }
          while ( v20 < (unsigned int)ptParent );
        }
        igi2_frame.zCommand[v20] = 0;
        DebugConsoleWindow_ptActiveQTask = ptQTask;
        DebugConsoleTask_AddHistoryItem(igi2_frame.zCommand);
        DebugConsoleCommand_Parse(igi2_frame.zCommand);
        v21 = ptQTask[2].ptParent;
        DebugConsoleWindow_ptActiveQTask = nullptr;
        if ( v21 )
          ptQTask[2].ptParent = nullptr;
        ptQTask[3].ptNext = nullptr;
        DebugConsole_PopActiveConsole();
        ptQTask[3].ptPrev = (struct QTask_s *)-1;
        goto LABEL_50;
      }
      if ( ptQTask[2].ptParent < (struct QTask_s *)0x7F )
      {
        v15 = _mb_cur_max_6aece0 <= 1 ? pctype_6aecec[v2] & 0x117 : isctype(v2, 279);
        if ( v15
          || (_mb_cur_max_6aece0 <= 1
            ? (v16 = pctype_6aecec[*(_DWORD *)pxContext] & 8)
            : (v16 = isctype(*(_DWORD *)pxContext, 8)),
              v16) )
        {
          igi2_frame.zTemp[0] = *(_BYTE *)pxContext;
          QString_ReAlloc((struct QString_s *)&ptQTask[1].eQTaskType, 1u);
          v17 = nullptr;
          do
          {
            if ( v17 >= ptQTask[2].ptNext )
              break;
            *((_BYTE *)&v17->ptNext + (unsigned int)ptQTask[2].ptPrev) = igi2_frame.zTemp[(_DWORD)v17];
            v17 = (struct QTask_s *)((char *)v17 + 1);
          }
          while ( !v17 );
          ptQTask[2].tQTaskChildren.ptMiddle = v17;
          QString_InsertSubString(
            (struct QString_s *)&ptQTask[2].tQTaskChildren.ptTail,
            (unsigned int)ptQTask[3].ptNext,
            (struct QString_s *)&ptQTask[1].eQTaskType,
            0,
            1u);
          v18 = (struct QTask_s *)((char *)&ptQTask[3].ptNext->ptNext + 1);
LABEL_49:
          ptQTask[3].ptNext = v18;
        }
      }
    }
LABEL_50:
    if ( Timer_isPerformanceCounter )
      *(_DWORD *)&ptQTask[2].eQTaskType = Timer_GetPerformanceCounter() - Timer_nStartTime;
    else
      *(_DWORD *)&ptQTask[2].eQTaskType = GetTickCount() - Timer_nStartTime;
  }
}

// source: h/2/debugconsolewindow.c:635  [anchor-mhash]
void __cdecl DebugConsoleWindow_RunHandler(struct QTask_s *ptQTask)
{
  DWORD PerformanceCounter; // eax
  DWORD TickCount; // eax
  struct QTask_s *ptHead; // eax
  int v4; // edx
  struct QTask_s *v5; // ecx
  int eQTaskType; // ecx

  if ( ptQTask[1].tQTaskChildren.ptHead )
  {
    QTask_Delete(ptQTask);
  }
  else
  {
    if ( Timer_isPerformanceCounter )
      PerformanceCounter = Timer_GetPerformanceCounter();
    else
      PerformanceCounter = GetTickCount();
    if ( (int)(PerformanceCounter - Timer_nStartTime - *(_DWORD *)&ptQTask[2].eQTaskType) > 500 )
    {
      if ( Timer_isPerformanceCounter )
        TickCount = Timer_GetPerformanceCounter();
      else
        TickCount = GetTickCount();
      *(_DWORD *)&ptQTask[2].eQTaskType = TickCount - Timer_nStartTime;
    }
    ptHead = ptQTask->tQTaskChildren.ptHead;
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
        eQTaskType = ptHead->eQTaskType;
        QTask_nProtectedQTaskStackOffset = v4 + 1;
        ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][eQTaskType].pfHandler)(ptHead);
        ptHead = (struct QTask_s *)dword_849C7DC[QTask_nProtectedQTaskStackOffset];
        v4 = --QTask_nProtectedQTaskStackOffset;
      }
      while ( ptHead );
    }
    ptQTask[1].tQTaskRefList.ptTail = (struct QReference_s *)ptQTask[1].ptParent;
  }
}

// source: h/2/debugconsolewindow.c:664  [anchor-caller]
void __cdecl DebugConsoleWindow_DrawConsoleHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s *ptRight; };
    struct { char igi2_o1[4]; struct DrawConsoleContext_s tContext; };
    char igi2_extent[44];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct DebugConsoleWindow_s *v2; // ebp
  int *v3; // ebx
  int isVerticalSplit; // eax
  int v5; // ecx
  int v6; // esi
  int v7; // ecx
  bool v8; // cc
  int v9; // eax
  void *v10; // esi
  enum bool v11; // ecx
  enum bool v12; // eax
  int v13; // edi

  v2 = (struct DebugConsoleWindow_s *)ptQTask;
  if ( DebugConsoleWindow_GetChildWindows(ptQTask, &ptQTask, &igi2_frame.ptRight) == 2 )
  {
    v3 = (int *)pxContext;
    if ( *((_DWORD *)pxContext + 7) )
    {
      ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[DebugConsoleTask_eDrawConsoleQTaskEvent][ptQTask->eQTaskType].pfHandler)(
        ptQTask,
        pxContext);
      ((void (__cdecl *)(struct QTask_s *, int *))QTask_aatQTaskFinalEvent[DebugConsoleTask_eDrawConsoleQTaskEvent][igi2_frame.ptRight->eQTaskType].pfHandler)(
        igi2_frame.ptRight,
        v3);
      return;
    }
    isVerticalSplit = v2->isVerticalSplit;
    v2->isActive = 0;
    qmemcpy(&igi2_frame.tContext, v3, sizeof(igi2_frame.tContext));
    if ( isVerticalSplit )
    {
      v5 = v3[3];
      v6 = v5 / 2 + v2->nSplit;
      if ( v6 >= 0 )
      {
        if ( v5 >= v6 )
          goto LABEL_11;
        v6 = v3[3];
      }
      else
      {
        v6 = 0;
      }
      if ( v5 < v6 )
      {
        igi2_frame.tContext.tDrawWindow.nWidth = v3[3];
LABEL_19:
        ((void (__cdecl *)(struct QTask_s *, struct DrawConsoleContext_s *))QTask_aatQTaskFinalEvent[DebugConsoleTask_eDrawConsoleQTaskEvent][ptQTask->eQTaskType].pfHandler)(
          ptQTask,
          &igi2_frame.tContext);
        if ( v2->isVerticalSplit )
        {
          igi2_frame.tContext.tDrawWindow.nX += igi2_frame.tContext.tDrawWindow.nWidth;
          igi2_frame.tContext.tDrawWindow.nWidth = v3[3] - v6;
        }
        else
        {
          v9 = v3[4] - v6;
          igi2_frame.tContext.tDrawWindow.nY += igi2_frame.tContext.tDrawWindow.nHeight;
          igi2_frame.tContext.tDrawWindow.nHeight = v9;
        }
        ((void (__cdecl *)(struct QTask_s *, struct DrawConsoleContext_s *))QTask_aatQTaskFinalEvent[DebugConsoleTask_eDrawConsoleQTaskEvent][igi2_frame.ptRight->eQTaskType].pfHandler)(
          igi2_frame.ptRight,
          &igi2_frame.tContext);
        return;
      }
LABEL_11:
      igi2_frame.tContext.tDrawWindow.nWidth = v6;
      goto LABEL_19;
    }
    v7 = v3[4];
    v6 = v7 / 2 + v2->nSplit;
    if ( v6 >= 0 )
    {
      v8 = v7 < v6;
      if ( v7 >= v6 )
        goto LABEL_17;
      v6 = v3[4];
    }
    else
    {
      v6 = 0;
    }
    v8 = v7 < v6;
LABEL_17:
    igi2_frame.tContext.tDrawWindow.nHeight = v3[4];
    if ( !v8 )
      igi2_frame.tContext.tDrawWindow.nHeight = v6;
    goto LABEL_19;
  }
  v10 = pxContext;
  v11 = v2 == *((struct DebugConsoleWindow_s **)pxContext + 8) && *((_DWORD *)pxContext + 6);
  v2->isActive = v11;
  v12 = *((_DWORD *)v10 + 7);
  if ( v12 == false || v2 == *((struct DebugConsoleWindow_s **)v10 + 8) )
  {
    v13 = DebugConsoleWindow_PrintWindow(
            v2,
            *((enum bool *)v10 + 5),
            v11,
            v12,
            *((_DWORD *)v10 + 1),
            *((_DWORD *)v10 + 2),
            *((_DWORD *)v10 + 3),
            *((_DWORD *)v10 + 4),
            *(char ***)v10);
    if ( v13 <= 1 )
      v13 = 1;
    if ( v2->isActive )
    {
      **((_DWORD **)v10 + 9) = *((_DWORD *)v10 + 1);
      *(_DWORD *)(*((_DWORD *)v10 + 9) + 4) = *((_DWORD *)v10 + 2);
      *(_DWORD *)(*((_DWORD *)v10 + 9) + 8) = *((_DWORD *)v10 + 3);
      *(_DWORD *)(*((_DWORD *)v10 + 9) + 12) = *((_DWORD *)v10 + 4);
      if ( v2->isCommandLine )
      {
        *(_DWORD *)(*((_DWORD *)v10 + 9) + 16) = Timer_Read() - v2->nCursorTimeStamp < 250;
        *(_DWORD *)(*((_DWORD *)v10 + 9) + 20) = *((_DWORD *)v10 + 1) + v2->nCursorX;
        *(_DWORD *)(*((_DWORD *)v10 + 9) + 24) = v13 + *((_DWORD *)v10 + 2);
      }
    }
    if ( *((_DWORD *)v10 + 4) && v2->isCommandLine && *((_DWORD *)v10 + 5) )
      QString_GetCString(
        &v2->tQString,
        (char *)(*((_DWORD *)v10 + 1) + *(_DWORD *)(*(_DWORD *)v10 + 4 * (v13 + *((_DWORD *)v10 + 2)))),
        *((_DWORD *)v10 + 3));
  }
}

// source: h/2/debugconsolewindow.c:777  [anchor-caller]
void __cdecl DebugConsoleWindow_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptPrev; // ebx
  struct QTask_s *ptHead; // edi
  struct QTask_s *ptNext; // ebx
  struct QTask_s *v5; // ebp
  struct QTask_s *v6; // ebp

  ptPrev = ptQTask[1].ptPrev;
  ptHead = (struct QTask_s *)ptQTask[1].tQTaskRefList.ptHead;
  if ( ptHead != ptPrev )
  {
    if ( DebugConsole_IsConsoleIDValid((int)ptHead) )
      ptQTask[1].ptPrev = ptHead;
    else
      ptQTask[1].tQTaskRefList.ptHead = (struct QReference_s *)ptPrev;
  }
  if ( ptQTask[1].tQTaskChildren.ptMiddle )
  {
    if ( !DebugConsoleWindow_GetChildWindows(ptQTask, nullptr, nullptr) )
    {
      ptNext = ptQTask[1].ptNext;
      v5 = ptQTask[1].ptPrev;
      QTask_NewFn(ptQTask, DebugConsoleWindow_eQTaskType, nullptr)[1].ptPrev = v5;
      v6 = ptQTask[1].ptPrev;
      QTask_NewFn(ptQTask, DebugConsoleWindow_eQTaskType, nullptr)[1].ptPrev = v6;
      ptQTask[1].ptNext = ptNext;
    }
  }
}

// source: h/2/debugconsolewindow.c:807  [size]
void __cdecl DebugConsoleWindow_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = DebugConsoleWindow_ptParameterList;
}

// source: h/2/debugconsolewindow.c:828  [anchor-callee]
int __cdecl DebugConsoleWindow_GetChildWindows(
        struct QTask_s *ptParent,
        struct QTask_s **pptLeftChild,
        struct QTask_s **pptRightChild)
{
  struct QTask_s *ptHead; // edx
  struct QTask_s *v4; // edi
  struct QTask_s *v5; // esi
  unsigned __int16 v6; // cx

  ptHead = ptParent->tQTaskChildren.ptHead;
  v4 = nullptr;
  v5 = nullptr;
  if ( ptHead->ptNext && ptHead )
  {
    v6 = DebugConsoleWindow_eQTaskType;
    while ( 1 )
    {
      while ( QTask_IsQTaskTypeDerived(ptHead->eQTaskType, v6) == false )
        ;
      if ( v5 )
        break;
      v5 = ptHead;
      ptHead = ptHead->ptNext;
      if ( !ptHead || !ptHead->ptNext )
        goto LABEL_10;
    }
    v4 = ptHead;
  }
LABEL_10:
  if ( pptLeftChild )
    *pptLeftChild = v5;
  if ( pptRightChild )
    *pptRightChild = v4;
  return (v5 != nullptr) + (v4 != nullptr);
}

// source: h/2/debugconsolewindow.c:874  [anchor-callee]
struct QTask_s *__cdecl DebugConsoleWindow_FindWindow(struct QTask_s *ptParent, int tConsoleID)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s *ptLeft; };
    struct { char igi2_o1[4]; struct QTask_s *ptRight; };
    char igi2_extent[8];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v2; // esi
  struct QTask_s *result; // eax

  DebugConsoleWindow_GetChildWindows(ptParent, &igi2_frame.ptLeft, &igi2_frame.ptRight);
  v2 = igi2_frame.ptLeft;
  if ( !igi2_frame.ptLeft )
    goto LABEL_6;
  if ( DebugConsoleWindow_GetChildWindows(igi2_frame.ptLeft, nullptr, nullptr) != 2 )
  {
    if ( v2[1].ptPrev == (struct QTask_s *)tConsoleID )
      return v2;
    goto LABEL_6;
  }
  result = DebugConsoleWindow_FindWindow(v2, tConsoleID);
  if ( !result )
  {
LABEL_6:
    v2 = igi2_frame.ptRight;
    if ( !igi2_frame.ptRight )
      return nullptr;
    if ( DebugConsoleWindow_GetChildWindows(igi2_frame.ptRight, nullptr, nullptr) == 2 )
    {
      DebugConsoleWindow_FindWindow(v2, tConsoleID);
      return nullptr;
    }
    if ( v2[1].ptPrev != (struct QTask_s *)tConsoleID )
      return nullptr;
    return v2;
  }
  return result;
}

// source: h/2/debugconsolewindow.c:924  [size]
unsigned __int16 __cdecl DebugConsoleWindow_GetQTaskType()
{
  return DebugConsoleWindow_eQTaskType;
}

// source: h/2/debugconsolewindow.c:939  [size]
struct QTask_s *__cdecl DebugConsoleWindow_New(struct QTask_s *ptParent, int tConsoleID)
{
  struct QTask_s *result; // eax

  result = QTask_NewFn(ptParent, DebugConsoleWindow_eQTaskType, nullptr);
  result[1].ptPrev = (struct QTask_s *)tConsoleID;
  return result;
}

// source: h/2/debugconsolewindow.c:960  [anchor-mhash]
struct QTask_s *__cdecl DebugConsoleWindow_Split(struct QTask_s *ptQTask, enum bool isVerticalSplit)
{
  struct QTask_s *ptPrev; // esi
  struct QTask_s *v4; // esi

  ptPrev = ptQTask[1].ptPrev;
  QTask_NewFn(ptQTask, DebugConsoleWindow_eQTaskType, nullptr)[1].ptPrev = ptPrev;
  v4 = ptQTask[1].ptPrev;
  QTask_NewFn(ptQTask, DebugConsoleWindow_eQTaskType, nullptr)[1].ptPrev = v4;
  ptQTask[1].ptNext = (struct QTask_s *)isVerticalSplit;
  return (struct QTask_s *)isVerticalSplit;
}

// source: h/2/debugconsolewindow.c:982  [size]
int __cdecl DebugConsoleWindow_SetID(struct QTask_s *ptQTask, int tConsoleID)
{
  ptQTask[1].ptPrev = (struct QTask_s *)tConsoleID;
  ptQTask[1].tQTaskRefList.ptHead = (struct QReference_s *)tConsoleID;
  return tConsoleID;
}

// source: h/2/debugconsolewindow.c:1002  [anchor-hash]
void __cdecl DebugConsoleWindow_EnableDebugCommands(enum bool isEnabled)
{
  struct ConsoleCommand_s *CommandInList; // eax
  struct ConsoleCommand_s *v2; // eax
  struct ConsoleCommand_s *v3; // eax
  struct ConsoleCommand_s *v4; // eax
  struct ConsoleCommand_s *v5; // eax
  struct ConsoleCommand_s *v6; // eax
  struct ConsoleCommand_s *v7; // eax
  struct ConsoleCommand_s *v8; // eax

  if ( isEnabled )
  {
    if ( !dword_7DDD404 )
    {
      DebugConsoleCommand_RegisterCommandInList(
        &DebugConsoleCommand_tGlobalCommandList,
        "list",
        (char *)&g_zInitialValue,
        "Display a list of all available channels.",
        DebugConsoleWindow_ListCommandParser,
        nullptr);
      DebugConsoleCommand_RegisterCommandInList(
        &DebugConsoleCommand_tGlobalCommandList,
        "setid",
        "<console ID>",
        "Set console ID for current window.",
        DebugConsoleWindow_SetConsoleParser,
        nullptr);
      DebugConsoleCommand_RegisterCommandInList(
        &DebugConsoleCommand_tGlobalCommandList,
        "splitv",
        (char *)&g_zInitialValue,
        "Split window vertically.",
        DebugConsoleWindow_SplitConsoleParser,
        nullptr);
      DebugConsoleCommand_RegisterCommandInList(
        &DebugConsoleCommand_tGlobalCommandList,
        "split",
        (char *)&g_zInitialValue,
        "Split window horizontally.",
        DebugConsoleWindow_SplitConsoleParser,
        nullptr);
      DebugConsoleCommand_RegisterCommandInList(
        &DebugConsoleCommand_tGlobalCommandList,
        "kill",
        (char *)&g_zInitialValue,
        "Kill current window.",
        DebugConsoleWindow_KillParser,
        nullptr);
      DebugConsoleCommand_RegisterCommandInList(
        &DebugConsoleCommand_tGlobalCommandList,
        "shrink",
        "[number of rows/columns]",
        "Shrink current window.",
        DebugConsoleWindow_ChangeSizeParser,
        nullptr);
      DebugConsoleCommand_RegisterCommandInList(
        &DebugConsoleCommand_tGlobalCommandList,
        "grow",
        "[number of rows/columns]",
        "Grow current window.",
        DebugConsoleWindow_ChangeSizeParser,
        nullptr);
      DebugConsoleCommand_RegisterCommandInList(
        &DebugConsoleCommand_tGlobalCommandList,
        "z",
        (char *)&g_zInitialValue,
        "Maximise/restore current window size.",
        DebugConsoleWindow_ZoomCommandParser,
        nullptr);
      dword_7DDD404 = isEnabled;
      return;
    }
  }
  else if ( dword_7DDD404 )
  {
    CommandInList = DebugConsoleCommand_FindCommandInList(&DebugConsoleCommand_tGlobalCommandList, "list");
    DebugConsoleCommand_RemoveCommand(CommandInList);
    v2 = DebugConsoleCommand_FindCommandInList(&DebugConsoleCommand_tGlobalCommandList, "setid");
    DebugConsoleCommand_RemoveCommand(v2);
    v3 = DebugConsoleCommand_FindCommandInList(&DebugConsoleCommand_tGlobalCommandList, "splitv");
    DebugConsoleCommand_RemoveCommand(v3);
    v4 = DebugConsoleCommand_FindCommandInList(&DebugConsoleCommand_tGlobalCommandList, "split");
    DebugConsoleCommand_RemoveCommand(v4);
    v5 = DebugConsoleCommand_FindCommandInList(&DebugConsoleCommand_tGlobalCommandList, "kill");
    DebugConsoleCommand_RemoveCommand(v5);
    v6 = DebugConsoleCommand_FindCommandInList(&DebugConsoleCommand_tGlobalCommandList, "shrink");
    DebugConsoleCommand_RemoveCommand(v6);
    v7 = DebugConsoleCommand_FindCommandInList(&DebugConsoleCommand_tGlobalCommandList, "grow");
    DebugConsoleCommand_RemoveCommand(v7);
    v8 = DebugConsoleCommand_FindCommandInList(&DebugConsoleCommand_tGlobalCommandList, "z");
    DebugConsoleCommand_RemoveCommand(v8);
  }
  dword_7DDD404 = isEnabled;
}

// source: h/2/debugconsolewindow.c:1040  [anchor-hash]
void __cdecl DebugConsoleWindow_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si
  struct ParameterList_s *v2; // eax
  int v3; // edx

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("DebugConsoleWindow", 128, BaseQTaskType, 0, 0);
  DebugConsoleWindow_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 0, DebugConsoleWindow_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, DebugConsoleWindow_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, DebugConsoleWindow_RunHandler);
  QTask_LinkQTaskEventHandlerFn(v1, DebugConsoleTask_eDrawConsoleQTaskEvent, DebugConsoleWindow_DrawConsoleHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eUpdateInternalDataQTaskEvent,
    DebugConsoleWindow_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))DebugConsoleWindow_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    DebugConsoleTask_eHandleConsoleKeystrokeEvent,
    DebugConsoleWindow_HandleConsoleKeystrokeHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  v2 = (struct ParameterList_s *)Mem_AllocFn(112, 4);
  v3 = Level_eParameterTypeInt32;
  v2->ptParameterListItem = (struct ParameterListItem_s *)&v2[1];
  v2->nParameters = 0;
  v2->nMaxParameters = 5;
  DebugConsoleWindow_ptParameterList = v2;
  ParameterList_AddParameter(v2, 0x3Cu, v3, "Console ID", 7u, nullptr);
  ParameterList_AddParameter(
    DebugConsoleWindow_ptParameterList,
    0x40u,
    Level_eParameterTypebool8,
    "isCommandLine",
    7u,
    nullptr);
  ParameterList_AddParameter(
    DebugConsoleWindow_ptParameterList,
    0x38u,
    Level_eParameterTypeInt32,
    "Split position",
    7u,
    nullptr);
  ParameterList_AddParameter(
    DebugConsoleWindow_ptParameterList,
    0x28u,
    Level_eParameterTypebool8,
    "isVerticalSplit",
    7u,
    nullptr);
  ParameterList_AddParameter(
    DebugConsoleWindow_ptParameterList,
    0x34u,
    Level_eParameterTypePushButton,
    "Split window",
    6u,
    nullptr);
  DebugConsoleCommand_RegisterCommandInList(
    &DebugConsoleCommand_tGlobalCommandList,
    "cls",
    (char *)&g_zInitialValue,
    "Clear window.",
    DebugConsoleWindow_ParseCls,
    nullptr);
}

// source: h/2/debugconsolewindow.c:1077  [anchor-hash]
void __cdecl DebugConsoleWindow_Close()
{
  struct ConsoleCommand_s *CommandInList; // eax
  int v1; // esi

  DebugConsoleWindow_EnableDebugCommands(false);
  CommandInList = DebugConsoleCommand_FindCommandInList(&DebugConsoleCommand_tGlobalCommandList, "cls");
  DebugConsoleCommand_RemoveCommand(CommandInList);
  if ( DebugConsoleWindow_ptParameterList )
  {
    v1 = *(_DWORD *)((unsigned int)&DebugConsoleWindow_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
  QTask_DeleteQTaskType(DebugConsoleWindow_eQTaskType);
}
