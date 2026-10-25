/* e/e.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: e/e.c:30  [anchor-caller]
void __cdecl E_Open()
{
  D_Open();
  E3_Open();
}

// source: e/e.c:49  [size]
void __cdecl E_Close()
{
  E3_Close();
  D_Close();
}
