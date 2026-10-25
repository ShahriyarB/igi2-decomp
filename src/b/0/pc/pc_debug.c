/* b/0/pc/pc_debug.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/0/pc/pc_debug.c:44  [size]
void __cdecl Debug_ParseQuietCmd(char *zUnused)
{
  Debug_isQuiet = true;
}

// source: b/0/pc/pc_debug.c:80  [anchor-hash]
__declspec(noreturn) void __cdecl Debug_ExitFunc()
{
  if ( AppContext_tAppContext.isDebugtext )
    Debug_nDummy = MEMORY[0];
  exit__crt0dat(1);
}

// source: b/0/pc/pc_debug.c:105  [size]
void __cdecl Debug_MsgBoxFunc(char *zMessage)
{
  ShowCursor(1);
  MessageBoxA(nullptr, zMessage, AppContext_tAppContext.zApplicationName, 0x10u);
  ShowCursor(0);
}

// source: b/0/pc/pc_debug.c:125  [anchor-hash]
void __cdecl Debug_InitCallbacks()
{
  LDebug_SetAbort((void (__cdecl *)())Debug_ExitFunc);
  LDebug_SetPrint(Debug_MsgBoxFunc);
  AppMain_FindPrefix(AppContext_tAppContext.zCmdLine, "quiet", (void (__cdecl *)(char *))Debug_ParseQuietCmd);
  if ( Debug_isQuiet == false )
  {
    LDebug_SetWarning(Debug_MsgBoxFunc);
    LDebug_SetMessage(Debug_MsgBoxFunc);
  }
}

// source: b/0/pc/pc_debug.c:152  [size]
void __cdecl Debug_Open()
{
  LDebug_Open();
  Debug_InitCallbacks();
}

// source: b/0/pc/pc_debug.c:174  [size]
void __cdecl Debug_Close()
{
  ;
}

// source: b/0/pc/pc_debug.c:197  [size]
void __cdecl Debug_LogStart()
{
  ;
}

// source: b/0/pc/pc_debug.c:209  [size]
void __cdecl Debug_LogEnd()
{
  ;
}
