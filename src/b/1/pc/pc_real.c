/* b/1/pc/pc_real.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/1/pc/pc_real.c:36  [anchor-hash]
void __cdecl Real_SetFPUStateIEEE()
{
  Real_nTempCW = igi2_fpu_or(0xC00u);
}
