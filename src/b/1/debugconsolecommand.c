/* b/1/debugconsolecommand.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/1/debugconsolecommand.c:105  [anchor-callee]
char *__cdecl DebugConsoleCommand_SplitCommandLine(
        int *pnArgc,
        char ***pArgv,
        char *zCommandLine)
{
  unsigned int v4; // kr00_4
  char *v5; // ebp
  void **v6; // edi
  struct QVector_s *v7; // esi
  char *v8; // edi
  unsigned int nElements; // ebp
  int v10; // ebx
  int v11; // ebp
  char *i; // ecx
  int v13; // esi
  char **argv; // [esp+10h] [ebp-Ch]
  char *zWork; // [esp+14h] [ebp-8h]

  argv = nullptr;
  v4 = strlen(zCommandLine);
  v5 = (char *)Mem_AllocFn(v4 + 1, 4);
  zWork = strcpy(v5, zCommandLine);
  v6 = (void **)Mem_AllocFn(40, 4);
  v7 = (struct QVector_s *)Mem_AllocFn(24, 4);
  v7->tPrivate.nArraySize = 10;
  v7->tPrivate.nReallocSize = 10;
  v7->tPrivate.papxElement = v6;
  v7->tPrivate.nElements = 0;
  v7->tPrivate.isPrivateMem = false;
  v7->tPrivate.isStrictOrder = true;
  v8 = String_Tokenize(v5, " \r\t\n");
  if ( v8 )
  {
    do
    {
      if ( *v8 == 34 && v8[strlen(v8) - 1] == 34 )
      {
        v8[strlen(v8) - 1] = 0;
        ++v8;
      }
      nElements = v7->tPrivate.nElements;
      if ( v7->tPrivate.nElements == v7->tPrivate.nArraySize )
        QVector_Realloc(v7, 1u);
      if ( nElements < v7->tPrivate.nElements - 1 )
        memmove(
          &v7->tPrivate.papxElement[nElements + 1],
          &v7->tPrivate.papxElement[nElements],
          4 * (v7->tPrivate.nElements - nElements));
      ++v7->tPrivate.nElements;
      v7->tPrivate.papxElement[nElements] = (void *)v8;
      v8 = String_Tokenize(nullptr, " \r\t\n");
    }
    while ( v8 );
    v5 = zWork;
  }
  v10 = v7->tPrivate.nElements;
  if ( v7->tPrivate.nElements )
  {
    v11 = 0;
    argv = (char **)Mem_AllocFn(v4 + 1 + 4 * v10, 4);
    for ( i = (char *)&argv[v10]; v11 < v10; i += strlen(i) + 1 )
    {
      argv[v11] = i;
      strcpy(i, (char *)v7->tPrivate.papxElement[v11++]);
    }
    v5 = zWork;
  }
  QVector_Delete(v7);
  if ( v5 )
  {
    v13 = *(_DWORD *)((unsigned int)(v5 - 4) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v13);
    memset(*(void **)(v13 + 8), 0xCDu, *(_DWORD *)(v13 + 16));
    free((void *)v13);
  }
  *pnArgc = v10;
  *pArgv = argv;
  return (char *)pnArgc;
}

// source: b/1/debugconsolecommand.c:173  [anchor-callee]
struct ConsoleCommand_s *__cdecl DebugConsoleCommand_FindCommandInList(
        struct ConsoleCommandList_s *ptCommandList,
        char *zName)
{
  struct ConsoleCommand_s *ptHead; // ebp
  struct ConsoleCommand_s *ptNext; // edi

  ptHead = ptCommandList->ptHead;
  ptNext = ptCommandList->ptHead->ptNext;
  if ( !ptNext )
    return nullptr;
  while ( strcmp(ptHead->zName, zName) )
  {
    ptHead = ptNext;
    ptNext = ptNext->ptNext;
    if ( !ptNext )
      return nullptr;
  }
  return ptHead;
}

// source: b/1/debugconsolecommand.c:206  [anchor-callee]
void __cdecl DebugConsoleCommand_RegisterCommandInList(
        struct ConsoleCommandList_s *ptCommandList,
        char *zName,
        char *zFormat,
        char *zInfo,
        void (__cdecl *pfParser)(int, char **, void *),
        void *pxCommandContext)
{
  char *v6; // edx
  char *v7; // ecx
  char *v8; // ecx

  v6 = (char *)Mem_AllocFn(592, 4);
  memset(v6, 0, 0x250u);
  *((_DWORD *)v6 + 1) = 0;
  *(_DWORD *)v6 = 0;
  strcpy(v6 + 8, zName);
  v7 = zFormat;
  if ( !zFormat )
    v7 = (char *)&g_zInitialValue;
  strcpy(v6 + 72, v7);
  v8 = zInfo;
  if ( !zInfo )
    v8 = (char *)&g_zInitialValue;
  strcpy(v6 + 328, v8);
  *((_DWORD *)v6 + 147) = pfParser;
  *((_DWORD *)v6 + 146) = pxCommandContext;
  List_AddTail(v6, (int)ptCommandList);
}

// source: b/1/debugconsolecommand.c:234  [anchor-callee]
void __cdecl DebugConsoleCommand_RemoveCommand(struct ConsoleCommand_s *ptCommand)
{
  _DWORD **v1; // eax
  int v2; // esi

  v1 = Node_Remove(ptCommand);
  if ( v1 )
  {
    v2 = *(_DWORD *)((unsigned int)(v1 - 1) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v2);
    memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
    free((void *)v2);
  }
}

// source: b/1/debugconsolecommand.c:250  [size]
struct ConsoleCommandListNode_s *__cdecl DebugConsoleCommand_FindList(int tConsoleID)
{
  struct ConsoleCommandListNode_s *result; // eax
  struct ConsoleCommandListNode_s *ptNext; // ecx

  result = DebugConsoleCommand_tConsoleCommandListList.ptHead;
  ptNext = DebugConsoleCommand_tConsoleCommandListList.ptHead->ptNext;
  if ( !DebugConsoleCommand_tConsoleCommandListList.ptHead->ptNext )
    return nullptr;
  while ( result->tConsoleID != tConsoleID )
  {
    result = ptNext;
    ptNext = ptNext->ptNext;
    if ( !ptNext )
      return nullptr;
  }
  return result;
}

// source: b/1/debugconsolecommand.c:274  [anchor-callee]
struct ConsoleCommandListNode_s *__cdecl DebugConsoleCommand_RegisterConsole(int tConsoleID)
{
  _DWORD *v1; // esi

  v1 = Mem_AllocFn(32, 4);
  memset(v1, 0, 0x20u);
  v1[1] = 0;
  *v1 = 0;
  v1[3] = v1 + 4;
  v1[4] = 0;
  v1[5] = v1 + 3;
  v1[2] = tConsoleID;
  v1[7] = 1;
  return (struct ConsoleCommandListNode_s *)List_AddTail(v1, (int)&DebugConsoleCommand_tConsoleCommandListList);
}

// source: b/1/debugconsolecommand.c:297  [size]
void __cdecl DebugConsoleCommand_RemoveConsole(struct ConsoleCommandListNode_s *ptCommandListNode)
{
  _DWORD **v1; // eax
  int v2; // esi

  v1 = Node_Remove(ptCommandListNode);
  if ( v1 )
  {
    v2 = *(_DWORD *)((unsigned int)(v1 - 1) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v2);
    memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
    free((void *)v2);
  }
}

// source: b/1/debugconsolecommand.c:313  [anchor-strings]
void __cdecl DebugConsoleCommand_ParseHelp(int argc, char **argv)
{
  struct ConsoleCommandListNode_s *ptHead; // ecx
  struct ConsoleCommandListNode_s *ptNext; // eax
  struct ConsoleCommandListNode_s *v4; // ebp
  char *v5; // edi
  struct ConsoleCommand_s *CommandInList; // esi
  void (__cdecl *pfDebugConsolePrintCallback)(char *, void *); // ecx
  struct DebugConsole_s *v8; // ebx
  struct DebugConsole_s *v9; // eax
  void (__cdecl *v10)(char *, void *); // ecx
  struct DebugConsole_s *v11; // ebx
  struct ConsoleCommand_s *v12; // ecx
  struct ConsoleCommand_s *i; // edi
  char *zName; // esi
  void (__cdecl *v15)(char *, void *); // ecx
  struct DebugConsole_s *v16; // ebx
  void (__cdecl *v17)(char *, void *); // ecx
  struct DebugConsole_s *v18; // ebx
  struct ConsoleCommand_s *v19; // ecx
  struct ConsoleCommand_s *j; // edi
  char *v21; // esi
  void (__cdecl *v22)(char *, void *); // ecx
  struct DebugConsole_s *v23; // ebx
  void (__cdecl *v24)(char *, void *); // ecx
  struct DebugConsole_s *v25; // ebx
  void (__cdecl *v26)(char *, void *); // ecx
  struct DebugConsole_s *v27; // ebx
  char zString[512]; // [esp+14h] [ebp-200h] BYREF

  ptHead = DebugConsoleCommand_tConsoleCommandListList.ptHead;
  ptNext = DebugConsoleCommand_tConsoleCommandListList.ptHead->ptNext;
  if ( DebugConsoleCommand_tConsoleCommandListList.ptHead->ptNext )
  {
    while ( ptHead->tConsoleID != DebugConsole_atActiveConsoleStack[DebugConsole_nStackPointer] )
    {
      ptHead = ptNext;
      ptNext = ptNext->ptNext;
      if ( !ptNext )
        goto LABEL_4;
    }
    v4 = ptHead;
  }
  else
  {
LABEL_4:
    v4 = DebugConsoleCommand_RegisterConsole(DebugConsole_atActiveConsoleStack[DebugConsole_nStackPointer]);
  }
  if ( argc > 1
    && ((v5 = argv[1], (CommandInList = DebugConsoleCommand_FindCommandInList(&v4->tCommandList, v5)) != nullptr)
     || (CommandInList = DebugConsoleCommand_FindCommandInList(&DebugConsoleCommand_tGlobalCommandList, v5)) != nullptr) )
  {
    sprintf(zString, "\nUsage:\n\n%s %s\n", CommandInList->zName, CommandInList->zFormat);
    pfDebugConsolePrintCallback = DebugConsole_ptActiveDebugConsole->pfDebugConsolePrintCallback;
    v8 = DebugConsole_ptActiveDebugConsole;
    if ( pfDebugConsolePrintCallback )
      pfDebugConsolePrintCallback(zString, DebugConsole_ptActiveDebugConsole->pxPrintCallbackContext);
    if ( v8->nMaxLines )
      DebugConsole_ParseCString(v8, zString);
    if ( strlen(CommandInList->zInfo) )
    {
      DebugConsole_PrintCString((char *)&stru_6A4CDC);
      DebugConsole_PrintCString(CommandInList->zInfo);
      DebugConsole_PrintCString((char *)&stru_6A4CDC);
    }
  }
  else
  {
    v9 = DebugConsole_ptActiveDebugConsole;
    v10 = DebugConsole_ptActiveDebugConsole->pfDebugConsolePrintCallback;
    v11 = DebugConsole_ptActiveDebugConsole;
    if ( v10 )
    {
      v10("\nAvailable commands:\n", DebugConsole_ptActiveDebugConsole->pxPrintCallbackContext);
      v9 = DebugConsole_ptActiveDebugConsole;
    }
    if ( v11->nMaxLines )
    {
      DebugConsole_ParseCString(v11, "\nAvailable commands:\n");
      v9 = DebugConsole_ptActiveDebugConsole;
    }
    v12 = v4->tCommandList.ptHead;
    for ( i = v12->ptNext; i; i = i->ptNext )
    {
      zName = v12->zName;
      v15 = v9->pfDebugConsolePrintCallback;
      v16 = v9;
      if ( v15 )
      {
        v15(zName, v9->pxPrintCallbackContext);
        v9 = DebugConsole_ptActiveDebugConsole;
      }
      if ( v16->nMaxLines )
      {
        DebugConsole_ParseCString(v16, zName);
        v9 = DebugConsole_ptActiveDebugConsole;
      }
      v17 = v9->pfDebugConsolePrintCallback;
      v18 = v9;
      if ( v17 )
      {
        v17((char *)&stru_6A4CDC, v9->pxPrintCallbackContext);
        v9 = DebugConsole_ptActiveDebugConsole;
      }
      if ( v18->nMaxLines )
      {
        DebugConsole_ParseCString(v18, (char *)&stru_6A4CDC);
        v9 = DebugConsole_ptActiveDebugConsole;
      }
      v12 = i;
    }
    v19 = DebugConsoleCommand_tGlobalCommandList.ptHead;
    for ( j = DebugConsoleCommand_tGlobalCommandList.ptHead->ptNext; j; j = j->ptNext )
    {
      v21 = v19->zName;
      v22 = v9->pfDebugConsolePrintCallback;
      v23 = v9;
      if ( v22 )
      {
        v22(v21, v9->pxPrintCallbackContext);
        v9 = DebugConsole_ptActiveDebugConsole;
      }
      if ( v23->nMaxLines )
      {
        DebugConsole_ParseCString(v23, v21);
        v9 = DebugConsole_ptActiveDebugConsole;
      }
      v24 = v9->pfDebugConsolePrintCallback;
      v25 = v9;
      if ( v24 )
      {
        v24((char *)&stru_6A4CDC, v9->pxPrintCallbackContext);
        v9 = DebugConsole_ptActiveDebugConsole;
      }
      if ( v25->nMaxLines )
      {
        DebugConsole_ParseCString(v25, (char *)&stru_6A4CDC);
        v9 = DebugConsole_ptActiveDebugConsole;
      }
      v19 = j;
    }
    v26 = v9->pfDebugConsolePrintCallback;
    v27 = v9;
    if ( v26 )
      v26("\nEnter ? <commandname> for info on a particular command.\n", v9->pxPrintCallbackContext);
    if ( v27->nMaxLines )
      DebugConsole_ParseCString(v27, "\nEnter ? <commandname> for info on a particular command.\n");
  }
}

// source: b/1/debugconsolecommand.c:395  [anchor-caller]
void *__cdecl DebugConsoleCommand_RegisterGlobal(
        char *zName,
        char *zFormat,
        char *zInfo,
        void (__cdecl *pfParser)(int, char **, void *),
        void *pxCommandContext)
{
  void *result; // eax

  DebugConsoleCommand_RegisterCommandInList(
    &DebugConsoleCommand_tGlobalCommandList,
    zName,
    zFormat,
    zInfo,
    pfParser,
    pxCommandContext);
  return result;
}

// source: b/1/debugconsolecommand.c:410  [anchor-caller]
void __cdecl DebugConsoleCommand_RemoveGlobal(char *zName)
{
  struct ConsoleCommand_s *CommandInList; // eax

  CommandInList = DebugConsoleCommand_FindCommandInList(&DebugConsoleCommand_tGlobalCommandList, zName);
  DebugConsoleCommand_RemoveCommand(CommandInList);
}

// source: b/1/debugconsolecommand.c:434  [anchor-callee]
void __cdecl DebugConsoleCommand_Register(
        char *zName,
        char *zFormat,
        char *zInfo,
        void (__cdecl *pfParser)(int, char **, void *),
        void *pxCommandContext)
{
  int v5; // edx
  struct ConsoleCommandListNode_s *ptHead; // ecx
  struct ConsoleCommandListNode_s *ptNext; // eax
  struct ConsoleCommandListNode_s *v8; // eax

  v5 = DebugConsole_atActiveConsoleStack[DebugConsole_nStackPointer];
  if ( v5 != -1 )
  {
    ptHead = DebugConsoleCommand_tConsoleCommandListList.ptHead;
    ptNext = DebugConsoleCommand_tConsoleCommandListList.ptHead->ptNext;
    if ( DebugConsoleCommand_tConsoleCommandListList.ptHead->ptNext )
    {
      while ( ptHead->tConsoleID != v5 )
      {
        ptHead = ptNext;
        ptNext = ptNext->ptNext;
        if ( !ptNext )
          goto LABEL_5;
      }
      v8 = ptHead;
    }
    else
    {
LABEL_5:
      v8 = DebugConsoleCommand_RegisterConsole(v5);
    }
    DebugConsoleCommand_RegisterCommandInList(&v8->tCommandList, zName, zFormat, zInfo, pfParser, pxCommandContext);
  }
}

// source: b/1/debugconsolecommand.c:464  [anchor-callee]
void __cdecl DebugConsoleCommand_Remove(char *zName)
{
  int v1; // edx
  struct ConsoleCommandListNode_s *ptHead; // ecx
  struct ConsoleCommandListNode_s *ptNext; // eax
  struct ConsoleCommand_s *CommandInList; // eax

  v1 = DebugConsole_atActiveConsoleStack[DebugConsole_nStackPointer];
  if ( v1 != -1 )
  {
    ptHead = DebugConsoleCommand_tConsoleCommandListList.ptHead;
    ptNext = DebugConsoleCommand_tConsoleCommandListList.ptHead->ptNext;
    if ( DebugConsoleCommand_tConsoleCommandListList.ptHead->ptNext )
    {
      while ( ptHead->tConsoleID != v1 )
      {
        ptHead = ptNext;
        ptNext = ptNext->ptNext;
        if ( !ptNext )
          goto LABEL_5;
      }
    }
    else
    {
LABEL_5:
      ptHead = nullptr;
    }
    CommandInList = DebugConsoleCommand_FindCommandInList(&ptHead->tCommandList, zName);
    DebugConsoleCommand_RemoveCommand(CommandInList);
  }
}

// source: b/1/debugconsolecommand.c:498  [anchor-callee]
void __cdecl DebugConsoleCommand_Echo(enum bool isOn)
{
  int v1; // edx
  struct ConsoleCommandListNode_s *ptHead; // ecx
  struct ConsoleCommandListNode_s *ptNext; // eax

  v1 = DebugConsole_atActiveConsoleStack[DebugConsole_nStackPointer];
  if ( v1 != -1 )
  {
    ptHead = DebugConsoleCommand_tConsoleCommandListList.ptHead;
    ptNext = DebugConsoleCommand_tConsoleCommandListList.ptHead->ptNext;
    if ( DebugConsoleCommand_tConsoleCommandListList.ptHead->ptNext )
    {
      while ( ptHead->tConsoleID != v1 )
      {
        ptHead = ptNext;
        ptNext = ptNext->ptNext;
        if ( !ptNext )
          goto LABEL_5;
      }
      ptHead->isEcho = isOn;
    }
    else
    {
LABEL_5:
      DebugConsoleCommand_RegisterConsole(DebugConsole_atActiveConsoleStack[DebugConsole_nStackPointer])->isEcho = isOn;
    }
  }
}

// source: b/1/debugconsolecommand.c:528  [anchor-caller]
void __cdecl DebugConsoleCommand_ForbidGlobalCommands(enum bool isForbidGlobalCommands)
{
  int v1; // edx
  struct ConsoleCommandListNode_s *ptHead; // ecx
  struct ConsoleCommandListNode_s *ptNext; // eax

  v1 = DebugConsole_atActiveConsoleStack[DebugConsole_nStackPointer];
  if ( v1 != -1 )
  {
    ptHead = DebugConsoleCommand_tConsoleCommandListList.ptHead;
    ptNext = DebugConsoleCommand_tConsoleCommandListList.ptHead->ptNext;
    if ( DebugConsoleCommand_tConsoleCommandListList.ptHead->ptNext )
    {
      while ( ptHead->tConsoleID != v1 )
      {
        ptHead = ptNext;
        ptNext = ptNext->ptNext;
        if ( !ptNext )
          goto LABEL_5;
      }
      ptHead->isForbidGlobalCommands = isForbidGlobalCommands;
    }
    else
    {
LABEL_5:
      DebugConsoleCommand_RegisterConsole(DebugConsole_atActiveConsoleStack[DebugConsole_nStackPointer])->isForbidGlobalCommands = isForbidGlobalCommands;
    }
  }
}

// source: b/1/debugconsolecommand.c:556  [anchor-callee]
void __cdecl DebugConsoleCommand_Parse(char *zCommandLine)
{
  #pragma pack(push, 1)
  union
  {
    struct { int argc; };
    struct { char igi2_o1[4]; char **argv; };
    struct { char igi2_o2[8]; char zError[192]; };
    char igi2_extent[200];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v1; // esi
  struct ConsoleCommandListNode_s *ptHead; // ecx
  struct ConsoleCommandListNode_s *ptNext; // eax
  struct ConsoleCommandList_s *v4; // edi
  char **v5; // ebp
  char *v6; // esi
  struct ConsoleCommand_s *CommandInList; // ebx
  int v8; // esi

  v1 = DebugConsole_atActiveConsoleStack[DebugConsole_nStackPointer];
  if ( v1 != -1 )
  {
    DebugConsoleCommand_SplitCommandLine(&igi2_frame.argc, &igi2_frame.argv, zCommandLine);
    if ( igi2_frame.argc )
    {
      ptHead = DebugConsoleCommand_tConsoleCommandListList.ptHead;
      ptNext = DebugConsoleCommand_tConsoleCommandListList.ptHead->ptNext;
      if ( DebugConsoleCommand_tConsoleCommandListList.ptHead->ptNext )
      {
        while ( ptHead->tConsoleID != v1 )
        {
          ptHead = ptNext;
          ptNext = ptNext->ptNext;
          if ( !ptNext )
            goto LABEL_6;
        }
        v4 = (struct ConsoleCommandList_s *)ptHead;
      }
      else
      {
LABEL_6:
        v4 = (struct ConsoleCommandList_s *)DebugConsoleCommand_RegisterConsole(v1);
      }
      v5 = igi2_frame.argv;
      v6 = *igi2_frame.argv;
      CommandInList = DebugConsoleCommand_FindCommandInList(v4 + 1, *igi2_frame.argv);
      if ( !CommandInList && !v4[2].ptHead )
        CommandInList = DebugConsoleCommand_FindCommandInList(&DebugConsoleCommand_tGlobalCommandList, v6);
      if ( v4[2].ptMiddle )
      {
        DebugConsole_PrintCString(zCommandLine);
        DebugConsole_PrintCString((char *)&stru_6A4CDC);
      }
      if ( !strcmp(*v5, (char *)&key_694ffc) )
      {
        DebugConsoleCommand_ParseHelp(igi2_frame.argc, v5);
      }
      else if ( CommandInList )
      {
        CommandInList->pfParser(igi2_frame.argc, v5, CommandInList->pxCommandContext);
      }
      else
      {
        sprintf(igi2_frame.zError, "Unknown command: '%s'", *v5);
        DebugConsole_PrintCString(igi2_frame.zError);
        DebugConsole_PrintCString((char *)&stru_6A4CDC);
      }
      v8 = *(_DWORD *)((unsigned int)(v5 - 1) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v8);
      memset(*(void **)(v8 + 8), 0xCDu, *(_DWORD *)(v8 + 16));
      free((void *)v8);
    }
  }
}

// source: b/1/debugconsolecommand.c:632  [anchor-hash]
void __cdecl DebugConsoleCommand_Open()
{
  DebugConsoleCommand_tGlobalCommandList.ptHead = (struct ConsoleCommand_s *)&DebugConsoleCommand_tGlobalCommandList.ptMiddle;
  DebugConsoleCommand_tGlobalCommandList.ptTail = (struct ConsoleCommand_s *)&DebugConsoleCommand_tGlobalCommandList;
  DebugConsoleCommand_tGlobalCommandList.ptMiddle = nullptr;
  DebugConsoleCommand_tConsoleCommandListList.ptHead = (struct ConsoleCommandListNode_s *)&DebugConsoleCommand_tConsoleCommandListList.ptMiddle;
  DebugConsoleCommand_tConsoleCommandListList.ptTail = (struct ConsoleCommandListNode_s *)&DebugConsoleCommand_tConsoleCommandListList;
  DebugConsoleCommand_tConsoleCommandListList.ptMiddle = nullptr;
}

// source: b/1/debugconsolecommand.c:646  [anchor-hash]
void __cdecl DebugConsoleCommand_Close()
{
  struct ConsoleCommandListNode_s *ptHead; // eax
  struct ConsoleCommandListNode_s *i; // ebx
  _DWORD **v2; // eax
  int v3; // esi

  ptHead = DebugConsoleCommand_tConsoleCommandListList.ptHead;
  for ( i = DebugConsoleCommand_tConsoleCommandListList.ptHead->ptNext; i; i = i->ptNext )
  {
    v2 = Node_Remove(ptHead);
    if ( v2 )
    {
      v3 = *(_DWORD *)((unsigned int)(v2 - 1) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v3);
      memset(*(void **)(v3 + 8), 0xCDu, *(_DWORD *)(v3 + 16));
      free((void *)v3);
    }
    ptHead = i;
  }
}
