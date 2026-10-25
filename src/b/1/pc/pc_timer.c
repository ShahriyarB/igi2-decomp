/* b/1/pc/pc_timer.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/1/pc/pc_timer.c:44  [anchor-strings]
int __cdecl Timer_GetPerformanceCounter()
{
  __int64 time_; // [esp+0h] [ebp-8h] BYREF

  if ( !QueryPerformanceCounter((LARGE_INTEGER *)&time_) )
  {
    LDebug_Error("GetPerformanceCounter called and no performance counter in system");
    abort();
  }
  return 1000 * (time_ / Timer_lpCount) + 1000 * (time_ % Timer_lpCount) / Timer_lpCount;
}

// source: b/1/pc/pc_timer.c:70  [anchor-hash]
void __cdecl Timer_Open()
{
  if ( QueryPerformanceFrequency((LARGE_INTEGER *)&Timer_lpCount) )
  {
    Timer_isPerformanceCounter = 1;
    Timer_nStartTime = Timer_GetPerformanceCounter();
  }
  else
  {
    Timer_isPerformanceCounter = 0;
    Timer_nStartTime = GetTickCount();
  }
}

// source: b/1/pc/pc_timer.c:92  [size]
void __cdecl Timer_Close()
{
  ;
}

// source: b/1/pc/pc_timer.c:104  [anchor-hash]
int __cdecl Timer_Read()
{
  if ( Timer_isPerformanceCounter )
    return Timer_GetPerformanceCounter() - Timer_nStartTime;
  else
    return GetTickCount() - Timer_nStartTime;
}

// source: b/1/pc/pc_timer.c:124  [anchor-mhash]
unsigned __int64 __cdecl GetTick()
{
  return __rdtsc();
}
