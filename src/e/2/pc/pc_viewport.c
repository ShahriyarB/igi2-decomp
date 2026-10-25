/* e/2/pc/pc_viewport.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: e/2/pc/pc_viewport.c:41  [anchor-hash]
int __cdecl Viewport_GetLogZ(float vZ)
{
  if ( SLODWORD(vZ) <= 1065353216 )
    return 0;
  else
    return (unsigned int)(LODWORD(vZ) - 1065353216) >> 20;
}
