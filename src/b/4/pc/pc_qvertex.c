/* b/4/pc/pc_qvertex.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/4/pc/pc_qvertex.c:65  [size]
void __cdecl QVertex_HardwareClose()
{
  RenderMode_atRenderModeMethod[QVertex_eStripPrimType].isAllocated = 0;
}
