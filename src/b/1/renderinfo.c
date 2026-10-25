/* b/1/renderinfo.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/1/renderinfo.c:37  [size]
int __cdecl RenderInfo_GetLogConsoleID()
{
  return RenderInfo_tLogConsoleID;
}

// source: b/1/renderinfo.c:52  [size]
int __cdecl RenderInfo_GetFrameInfoConsoleID()
{
  return RenderInfo_tFrameInfoConsoleID;
}

// source: b/1/renderinfo.c:65  [size]
void __cdecl RenderInfo_ClearFrameInfoConsole()
{
  DebugConsole_PushActiveConsole(RenderInfo_tFrameInfoConsoleID);
  DebugConsole_ClearAll(DebugConsole_ptActiveDebugConsole, false);
  DebugConsole_PopActiveConsole();
}

// source: b/1/renderinfo.c:80  [anchor-strings]
void __cdecl RenderInfo_Open()
{
  RenderInfo_tLogConsoleID = DebugConsole_Alloc("RenderInfo Log", 100);
  RenderInfo_tFrameInfoConsoleID = DebugConsole_Alloc("RenderInfo", 100);
}

// source: b/1/renderinfo.c:94  [size]
void __cdecl RenderInfo_Close()
{
  DebugConsole_DeAlloc(RenderInfo_tLogConsoleID);
  DebugConsole_DeAlloc(RenderInfo_tFrameInfoConsoleID);
}
