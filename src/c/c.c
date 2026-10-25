/* c/c.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: c/c.c:28  [anchor-caller]
void __cdecl C_Open()
{
  B_Open();
  Script_Open();
}

// source: c/c.c:47  [size]
void __cdecl C_Close()
{
  Symbol_Close();
  B_Close();
}
