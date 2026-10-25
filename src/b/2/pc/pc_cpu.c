/* b/2/pc/pc_cpu.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/2/pc/pc_cpu.c:32  [override: the original runs cpuid inline]
void __cdecl CPU_TestCPU()
{
  unsigned int eflags; // the AC flag (bit 18) toggles only on CPUs that have CPUID
  int regs[4];

  eflags = __readeflags();
  __writeeflags(eflags ^ 0x40000);
  if ( eflags != __readeflags() )
  {
    __cpuid(regs, 1);
    CPU_tCaps.isCPUID = true;
    CPU_tCaps.isMMX = (regs[3] & 0x800000) != 0;    // edx bit 23
    CPU_tCaps.isSSE = (regs[3] & 0x2000000) != 0;   // edx bit 25
    CPU_tCaps.isSSE2 = (regs[3] & 0x4000000) != 0;  // edx bit 26
  }
  else
  {
    CPU_tCaps.isCPUID = false;
    CPU_tCaps.isMMX = false;
    CPU_tCaps.isSSE = false;
    CPU_tCaps.isSSE2 = false;
  }
}

// source: b/2/pc/pc_cpu.c:110  [size]
struct CPU_s *__cdecl CPU_GetCaps()
{
  return &CPU_tCaps;
}
