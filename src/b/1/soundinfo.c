/* b/1/soundinfo.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/1/soundinfo.c:37  [size]
int __cdecl SoundInfo_GetLogConsoleID()
{
  return SoundInfo_tLogConsoleID;
}

// source: b/1/soundinfo.c:52  [size]
int __cdecl SoundInfo_GetFrameInfoConsoleID()
{
  return SoundInfo_tFrameInfoConsoleID;
}

// source: b/1/soundinfo.c:65  [size]
void __cdecl SoundInfo_ClearFrameInfoConsole()
{
  DebugConsole_PushActiveConsole(SoundInfo_tFrameInfoConsoleID);
  DebugConsole_ClearAll(DebugConsole_ptActiveDebugConsole, false);
  DebugConsole_PopActiveConsole();
}

// source: b/1/soundinfo.c:80  [anchor-strings]
void __cdecl SoundInfo_Open()
{
  SoundInfo_tLogConsoleID = DebugConsole_Alloc("SoundInfo Log", 100);
  SoundInfo_tFrameInfoConsoleID = DebugConsole_Alloc("SoundInfo", 100);
}

// source: b/1/soundinfo.c:94  [size]
void __cdecl SoundInfo_Close()
{
  DebugConsole_DeAlloc(SoundInfo_tLogConsoleID);
  DebugConsole_DeAlloc(SoundInfo_tFrameInfoConsoleID);
}
