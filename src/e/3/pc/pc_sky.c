/* e/3/pc/pc_sky.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: e/3/pc/pc_sky.c:50  [size]
struct real32x3_t *__cdecl Sky_SetColor(struct real32x3_t *ptColor)
{
  float vX; // ecx
  float vY; // edx
  struct real32x3_t *result; // eax

  vX = ptColor->vX;
  vY = ptColor->vY;
  result = (struct real32x3_t *)LODWORD(ptColor->vZ);
  Sky_tColor.vX = vX;
  Sky_tColor.vY = vY;
  LODWORD(Sky_tColor.vZ) = result;
  return result;
}

// source: e/3/pc/pc_sky.c:68  [anchor-hash]
void __cdecl Sky_Open()
{
  Sky_ptLODVirModel = MTP_GetLODVirModel(off_68698C);
}

// source: e/3/pc/pc_sky.c:85  [size]
void __cdecl Sky_Close()
{
  ;
}

// source: e/3/pc/pc_sky.c:101  [size]
void __cdecl Sky_Draw(float vZDisplacement, float vGamma)
{
  ;
}
