/* f/2/debugtext.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: f/2/debugtext.c:650  [size]
void __cdecl DebugText_print(char *zString)
{
  ;
}

// source: f/2/debugtext.c:667  [size]
void __cdecl DebugText_SetCursor(int nX, int nY)
{
  ;
}

// source: f/2/debugtext.c:687  [size]
void __cdecl DebugText_Clear()
{
  ;
}

// source: f/2/debugtext.c:707  [size]
void __cdecl DebugText_Show(enum bool isDisplayed)
{
  ;
}

// source: f/2/debugtext.c:724  [size]
void DebugText_printf(char *zFormat, ...)
{
  ;
}

// source: f/2/debugtext.c:749  [size]
void __cdecl DebugText_vprintf(char *zFormat, char *pArgList)
{
  ;
}

// source: f/2/debugtext.c:769  [size]
void __cdecl DebugText_Enable(enum bool isEnabled)
{
  ;
}

// source: f/2/debugtext.c:786  [size]
enum bool __cdecl DebugText_IsEnabled()
{
  return false;
}

// source: f/2/debugtext.c:803  [size]
struct QTask_s *__cdecl DebugText_New(struct QTask_s *ptParent, enum bool isRenderContext)
{
  return nullptr;
}

// source: f/2/debugtext.c:840  [anchor-hash]
void __cdecl DebugText_Open()
{
  Resource_Register("LOCAL:debug.fnt", nullptr, DebugText_anFont, 0x507Cu, 3u, nullptr);
}

// source: f/2/debugtext.c:882  [size]
void __cdecl DebugText_Close()
{
  ;
}
