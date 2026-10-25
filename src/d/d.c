/* d/d.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: d/d.c:32  [anchor-caller]
void __cdecl D_Open()
{
  B_Open();
  Script_Open();
  QTask_Open();
}

// source: d/d.c:54  [layout]
void __cdecl D_Close()
{
  QTask_Close();
  Symbol_Close();
  B_Close();
}
