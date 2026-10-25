/* e/2/viewport.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: e/2/viewport.c:44  [anchor-mhash]
void __cdecl Viewport_AllocID(int *pnID)
{
  int v1; // eax

  v1 = 0;
  if ( Viewport_aisIDUsed[0] )
  {
    while ( Viewport_aisIDUsed[++v1] )
      ;
  }
  Viewport_aisIDUsed[v1] = 1;
  *pnID = v1;
}

// source: e/2/viewport.c:70  [size]
int __cdecl Viewport_SetActiveID(int nID)
{
  Viewport_nActiveID = nID;
  return nID;
}

// source: e/2/viewport.c:87  [size]
int __cdecl Viewport_GetActiveID()
{
  return Viewport_nActiveID;
}

// source: e/2/viewport.c:103  [size]
int __cdecl Viewport_FreeID(int nID)
{
  Viewport_aisIDUsed[nID] = 0;
  return nID;
}

// source: e/2/viewport.c:123  [size]
void __cdecl Viewport_Init()
{
  ;
}

// source: e/2/viewport.c:138  [size]
void __cdecl Viewport_DeInit()
{
  ;
}

// source: e/2/viewport.c:153  [size]
void __cdecl Viewport_Open()
{
  ;
}

// source: e/2/viewport.c:168  [size]
void __cdecl Viewport_Close()
{
  ;
}
