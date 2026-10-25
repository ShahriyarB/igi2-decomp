/* b/4/3dpicture.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/4/3dpicture.c:35  [anchor-callee]
void __cdecl Q3DPicture_RegisterSize(
        struct StaticTilemap_s *ptPicture,
        float vX,
        float vY,
        float vWidth,
        float vHeight,
        int nDepth)
{
  struct QTilemap_s *ptQTilemap; // edi
  int nWidth; // eax
  int v8; // ebp
  unsigned __int8 v9; // al
  bool v10; // cc
  float vYStep; // [esp+8h] [ebp-14h]
  int y; // [esp+Ch] [ebp-10h]
  float vXStep; // [esp+14h] [ebp-8h]
  float vX3; // [esp+18h] [ebp-4h]
  float ptPicturea = *(float *)&vX; // [esp+20h] [ebp+4h] ARGSLOT
  float vYa = *(float *)&vWidth; // [esp+28h] [ebp+Ch] ARGSLOT
  int vWidtha = *(int *)&vHeight; // [esp+2Ch] [ebp+10h] ARGSLOT

  ptQTilemap = ptPicture->ptQTilemap;
  nWidth = ptPicture->ptQTilemap->nWidth;
  v8 = 0;
  y = 0;
  vXStep = vWidth / (double)nWidth;
  vYStep = vHeight / (double)ptPicture->ptQTilemap->nHeight;
  if ( ptPicture->ptQTilemap->nHeight > 0 )
  {
    do
    {
      ptPicturea = vX;
      for ( vWidtha = 0; vWidtha < nWidth; ++vWidtha )
      {
        v9 = ptQTilemap->anID[v8];
        if ( v9 )
        {
          vX3 = vYStep + vY;
          vYa = vXStep + ptPicturea;
          QSprite_Register4AZ(
            ptPicture->ptQTilemap->ptQSprite,
            ptPicturea,
            vY,
            vYa,
            vY,
            ptPicturea,
            vX3,
            vYa,
            vX3,
            ptPicture->vR,
            ptPicture->vG,
            ptPicture->vB,
            ptPicture->vZ,
            ptPicture->vA,
            v9 - 1,
            ptPicture->bQGraphicFlags,
            nDepth);
          ptPicturea = vYa;
        }
        nWidth = ptQTilemap->nWidth;
        ++v8;
      }
      v10 = y + 1 < ptQTilemap->nHeight;
      vY = vYStep + vY;
      ++y;
    }
    while ( v10 );
  }
}
