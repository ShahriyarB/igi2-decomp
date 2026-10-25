/* b/1/networkinfo.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/1/networkinfo.c:39  [size]
int __cdecl NetworkInfo_GetLogConsoleID()
{
  return NetworkInfo_tLogConsoleID;
}

// source: b/1/networkinfo.c:54  [size]
int __cdecl NetworkInfo_GetSendLogConsoleID()
{
  return NetworkInfo_tSendLogConsoleID;
}

// source: b/1/networkinfo.c:69  [size]
int __cdecl NetworkInfo_GetReceiveLogConsoleID()
{
  return NetworkInfo_tReceiveLogConsoleID;
}

// source: b/1/networkinfo.c:85  [size]
int __cdecl NetworkInfo_GetFrameInfoConsoleID()
{
  return NetworkInfo_tFrameInfoConsoleID;
}

// source: b/1/networkinfo.c:98  [size]
void __cdecl NetworkInfo_ClearFrameInfoConsole()
{
  DebugConsole_PushActiveConsole(NetworkInfo_tFrameInfoConsoleID);
  DebugConsole_ClearAll(DebugConsole_ptActiveDebugConsole, false);
  DebugConsole_PopActiveConsole();
}

// source: b/1/networkinfo.c:113  [anchor-hash]
void __cdecl NetworkInfo_Open()
{
  NetworkInfo_tLogConsoleID = DebugConsole_Alloc("NetworkInfo Log", 100);
  NetworkInfo_tSendLogConsoleID = DebugConsole_Alloc("NetworkInfo Send Log", 100);
  NetworkInfo_tReceiveLogConsoleID = DebugConsole_Alloc("NetworkInfo Receive Log", 100);
  NetworkInfo_tFrameInfoConsoleID = DebugConsole_Alloc("NetworkInfo", 100);
}

// source: b/1/networkinfo.c:129  [anchor-hash]
void __cdecl NetworkInfo_Close()
{
  DebugConsole_DeAlloc(NetworkInfo_tLogConsoleID);
  DebugConsole_DeAlloc(NetworkInfo_tSendLogConsoleID);
  DebugConsole_DeAlloc(NetworkInfo_tReceiveLogConsoleID);
  DebugConsole_DeAlloc(NetworkInfo_tFrameInfoConsoleID);
}
