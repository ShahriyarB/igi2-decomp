/* b/4/qtilemap.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/4/qtilemap.c:31  [anchor-caller]
struct QTilemap_s *__cdecl QTilemap_FromROMTilemap(
        struct ROMTilemap *ptROMTilemap,
        struct QSprite_s *ptQSprite)
{
  unsigned int *p_bFlags; // ecx
  struct QTilemap_s *result; // eax
  int v4; // ecx
  int nWidth; // esi
  int v6; // ebp
  __int16 *p_nTileID; // edx
  int y; // [esp+0h] [ebp-4h]

  p_bFlags = &ptQSprite->atQAnimframe[ptQSprite->nQAnimframes].bFlags;
  *p_bFlags |= 0x10000u;
  result = QTilemap_New(ptROMTilemap->nWidth, ptROMTilemap->nHeight, ptQSprite);
  v4 = 0;
  y = 0;
  if ( ptROMTilemap->nHeight > 0 )
  {
    nWidth = ptROMTilemap->nWidth;
    do
    {
      v6 = 0;
      if ( nWidth > 0 )
      {
        p_nTileID = &ptROMTilemap->atTile[v4].nTileID;
        do
        {
          result->anID[v4] = *(_BYTE *)p_nTileID;
          nWidth = ptROMTilemap->nWidth;
          ++v4;
          p_nTileID += 8;
          ++v6;
        }
        while ( v6 < nWidth );
      }
      ++y;
    }
    while ( y < ptROMTilemap->nHeight );
  }
  return result;
}

// source: b/4/qtilemap.c:76  [anchor-callee]
struct QTilemap_s *__cdecl QTilemap_New(int nWidth, int nHeight, struct QSprite_s *ptQSprite)
{
  signed int v3; // ebp
  struct QTilemap_s *v4; // esi
  int i; // eax

  v3 = nHeight * nWidth;
  v4 = (struct QTilemap_s *)Mem_AllocFn(nHeight * nWidth + 19, 4);
  memset(v4, 0, nHeight * nWidth + 19);
  v4->eQTilemapType = (ptQSprite->atQAnimframe[ptQSprite->nQAnimframes].bFlags & 0x10000) == 0;
  v4->nWidth = nWidth;
  v4->nHeight = nHeight;
  v4->ptQSprite = ptQSprite;
  v4->anGraphicWidth = (__int16 *)Mem_AllocFn(2 * nHeight, 4);
  for ( i = 0; i < nHeight; ++i )
    v4->anGraphicWidth[i] = 0;
  if ( v3 > 0 )
    memset(v4->anID, 0, v3);
  return v4;
}

// source: b/4/qtilemap.c:120  [anchor-hash]
void __cdecl QTilemap_Delete(struct QTilemap_s *ptQTilemap)
{
  __int16 *anGraphicWidth; // eax
  int v3; // esi
  int v4; // ecx
  int v5; // esi

  anGraphicWidth = ptQTilemap->anGraphicWidth;
  if ( anGraphicWidth )
  {
    v3 = *(_DWORD *)((unsigned int)(anGraphicWidth - 2) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v3);
    memset(*(void **)(v3 + 8), 0xCDu, *(_DWORD *)(v3 + 16));
    free((void *)v3);
  }
  v4 = Mem_nCurrentAllocations;
  ptQTilemap->anGraphicWidth = nullptr;
  v5 = *(_DWORD *)((unsigned int)ptQTilemap[-1].anID & 0xFFFFFFFC);
  Mem_nCurrentAllocations = v4 - 1;
  Node_Remove((_DWORD **)v5);
  memset(*(void **)(v5 + 8), 0xCDu, *(_DWORD *)(v5 + 16));
  free((void *)v5);
}

// source: b/4/qtilemap.c:142  [size]
struct QTilemap_s *__cdecl QTilemap_SetTile(
        struct QTilemap_s *ptQTilemap,
        int nX,
        int nY,
        unsigned __int8 nID)
{
  char *v4; // ecx

  v4 = (char *)ptQTilemap + nY * ptQTilemap->nWidth;
  v4[nX + 16] = nID;
  return (struct QTilemap_s *)nX;
}

// source: b/4/qtilemap.c:173  [size]
unsigned __int8 __cdecl QTilemap_GetTile(
        struct QTilemap_s *ptQTilemap,
        int nX,
        int nY)
{
  return ptQTilemap->anID[nY * ptQTilemap->nWidth + nX];
}

// source: b/4/qtilemap.c:208  [anchor-mhash]
void __cdecl QTilemap_UpdateGraphicWidth(struct QTilemap_s *ptQTilemap, int nY)
{
  struct QSprite_s *ptQSprite; // eax
  struct QAnimframe_s *atQAnimframe; // edx
  int nWidth; // esi
  int v5; // ecx
  __int16 v6; // bp
  __int16 v7; // dx
  int v8; // eax
  int v9; // edi
  unsigned __int8 v10; // al
  unsigned __int8 *atTileLine; // [esp+Ch] [ebp-8h]
  int nSpace; // [esp+10h] [ebp-4h]

  ptQSprite = ptQTilemap->ptQSprite;
  atQAnimframe = ptQSprite->atQAnimframe;
  nWidth = ptQTilemap->nWidth;
  atTileLine = &ptQTilemap->anID[nY * nWidth];
  v5 = 0;
  v6 = 0;
  if ( ptQTilemap->eQTilemapType )
  {
    if ( ptQTilemap->eQTilemapType != QTILEMAP_TYPE_PROPTEXT )
      return;
    v9 = 0;
    for ( nSpace = atQAnimframe[ptQSprite->nQAnimframes].nSpace; v9 < nWidth; ++v9 )
    {
      v10 = atTileLine[v9];
      if ( v10 )
      {
        v5 += atQAnimframe[v10 - 1].nSpace;
        v6 = v5;
      }
      else
      {
        v5 += nSpace;
      }
    }
    goto LABEL_13;
  }
  v7 = atQAnimframe[ptQSprite->nQAnimframes].nWidth;
  v8 = 0;
  if ( nWidth <= 0 )
  {
LABEL_13:
    ptQTilemap->anGraphicWidth[nY] = v6;
    return;
  }
  do
  {
    LOWORD(v5) = v7 + v5;
    if ( atTileLine[v8] )
      v6 = v5;
    ++v8;
  }
  while ( v8 < nWidth );
  ptQTilemap->anGraphicWidth[nY] = v6;
}

// source: b/4/qtilemap.c:294  [size]
void __cdecl QTilemap_SetString(
        struct QTilemap_s *ptQTilemap,
        char *zText,
        int nX,
        int nY)
{
  int v5; // eax
  char v6; // cl
  unsigned __int8 *v7; // eax

  v5 = nX + nY * ptQTilemap->nWidth;
  v6 = *zText;
  if ( *zText )
  {
    v7 = &ptQTilemap->anID[v5];
    do
    {
      *v7 = v6;
      v6 = zText[1];
      ++v7;
      ++zText;
    }
    while ( v6 );
  }
  QTilemap_UpdateGraphicWidth(ptQTilemap, nY);
}

// source: b/4/qtilemap.c:331  [size]
void __cdecl QTilemap_SetTranslatedString(
        struct QTilemap_s *ptQTilemap,
        char *zText,
        int nX,
        int nY)
{
  int v5; // eax
  unsigned __int8 v6; // cl
  unsigned __int8 *anID; // edx
  unsigned __int8 *v8; // eax

  v5 = nX + nY * ptQTilemap->nWidth;
  v6 = *zText;
  anID = ptQTilemap->ptQSprite->ptQTilemap->anID;
  if ( *zText )
  {
    v8 = &ptQTilemap->anID[v5];
    do
    {
      *v8 = anID[v6];
      v6 = zText[1];
      ++v8;
      ++zText;
    }
    while ( v6 );
  }
  QTilemap_UpdateGraphicWidth(ptQTilemap, nY);
}

// source: b/4/qtilemap.c:375  [size]
void __cdecl QTilemap_ScrollUp(struct QTilemap_s *ptQTilemap, int nLines)
{
  int v2; // ecx
  signed int nWidth; // edx
  unsigned __int8 *anID; // edi
  unsigned __int8 *v6; // eax
  int v7; // esi
  unsigned __int8 *v8; // eax
  int v9; // [esp+8h] [ebp-8h]
  signed int v10; // [esp+Ch] [ebp-4h]
  unsigned __int8 *ptQTilemapa = *(unsigned __int8 * *)&ptQTilemap; // [esp+14h] [ebp+4h] ARGSLOT
  struct QTilemap_s *ptQTilemapb = *(struct QTilemap_s * *)&ptQTilemap; // [esp+14h] [ebp+4h] ARGSLOT

  v2 = nLines;
  nWidth = ptQTilemap->nWidth;
  anID = ptQTilemap->anID;
  v6 = &ptQTilemap->anID[nLines * nWidth];
  ptQTilemapa = ptQTilemap->anID;
  if ( nLines >= 1 )
  {
    v7 = 0;
    if ( ptQTilemap->nHeight - nLines > 0 )
    {
      ptQTilemapb = (struct QTilemap_s *)v6;
      v9 = nLines;
      do
      {
        ptQTilemap->anGraphicWidth[v7] = ptQTilemap->anGraphicWidth[v9];
        if ( nWidth > 0 )
        {
          v8 = anID;
          v10 = nWidth;
          do
          {
            *v8 = v8[(char *)ptQTilemapb - (char *)anID];
            ++v8;
            --v10;
          }
          while ( v10 );
          v2 = nLines;
        }
        ptQTilemapb = (struct QTilemap_s *)((char *)ptQTilemapb + nWidth);
        ++v9;
        anID += nWidth;
        ++v7;
      }
      while ( v7 < ptQTilemap->nHeight - v2 );
      ptQTilemapa = anID;
    }
    for ( ; v7 < ptQTilemap->nHeight; ptQTilemapa = anID )
    {
      ptQTilemap->anGraphicWidth[v7] = 0;
      if ( nWidth > 0 )
      {
        memset(anID, 0, nWidth);
        anID = ptQTilemapa;
      }
      anID += nWidth;
      ++v7;
    }
  }
}

// source: b/4/qtilemap.c:441  [anchor-callee]
void __cdecl QTilemap_Register(
        struct QTilemap_s *ptQTilemap,
        float vX,
        float vY,
        float vR,
        float vG,
        float vB,
        float vA,
        float vZ,
        unsigned int bQGraphicFlags,
        int nDepth)
{
  struct QSprite_s *ptQSprite; // edi
  __int16 *v11; // eax
  int v12; // ecx
  unsigned int v13; // esi
  unsigned __int8 v14; // al
  int v15; // ecx
  unsigned int v16; // esi
  unsigned __int8 v17; // al
  int v18; // esi
  double nSpace; // st7
  bool v20; // cc
  int i; // [esp+Ch] [ebp-20h]
  int ia; // [esp+Ch] [ebp-20h]
  int iX; // [esp+14h] [ebp-18h]
  int iXa; // [esp+14h] [ebp-18h]
  int iY; // [esp+18h] [ebp-14h]
  int iYa; // [esp+18h] [ebp-14h]
  int nWidth; // [esp+1Ch] [ebp-10h]
  int nWidtha; // [esp+1Ch] [ebp-10h]
  int nHeight; // [esp+24h] [ebp-8h]
  float nHeighta; // [esp+24h] [ebp-8h]
  float nHeightb; // [esp+24h] [ebp-8h]
  float v33; // [esp+28h] [ebp-4h]
  float vXa = *(float *)&vY; // [esp+34h] [ebp+8h] ARGSLOT
  float vXb = *(float *)&vY; // [esp+34h] [ebp+8h] ARGSLOT

  ptQSprite = ptQTilemap->ptQSprite;
  v11 = (__int16 *)&ptQSprite->atQAnimframe[ptQSprite->nQAnimframes];
  nWidth = v11[6];
  nHeight = v11[7];
  if ( ptQTilemap->eQTilemapType )
  {
    if ( ptQTilemap->eQTilemapType == QTILEMAP_TYPE_PROPTEXT )
    {
      nWidtha = v11[8];
      v15 = 0;
      iYa = 0;
      ia = 0;
      if ( ptQTilemap->nHeight > 0 )
      {
        v16 = bQGraphicFlags & 0x80;
        nHeightb = (float)nHeight;
        do
        {
          if ( v16 )
          {
            vXb = vX - (double)(ptQTilemap->anGraphicWidth[v15] / 2);
          }
          else if ( (bQGraphicFlags & 0x100) != 0 )
          {
            vXb = vX - (double)ptQTilemap->anGraphicWidth[v15];
          }
          else
          {
            vXb = vX;
          }
          iXa = 0;
          if ( ptQTilemap->nWidth > 0 )
          {
            do
            {
              v17 = ptQTilemap->anID[ia];
              if ( v17 )
              {
                v18 = (unsigned __int8)(v17 - 1);
                QSprite_RegisterAZ(ptQSprite, vXb, vY, vR, vG, vB, vA, vZ, v18, bQGraphicFlags, nDepth);
                v15 = iYa;
                nSpace = (double)ptQSprite->atQAnimframe[v18].nSpace;
              }
              else
              {
                nSpace = (double)nWidtha;
              }
              vXb = nSpace + vXb;
              v20 = iXa + 1 < ptQTilemap->nWidth;
              ++ia;
              ++iXa;
            }
            while ( v20 );
            v16 = bQGraphicFlags & 0x80;
          }
          iYa = ++v15;
          vY = nHeightb + vY;
        }
        while ( v15 < ptQTilemap->nHeight );
      }
    }
  }
  else
  {
    v12 = 0;
    iY = 0;
    i = 0;
    if ( ptQTilemap->nHeight > 0 )
    {
      v13 = bQGraphicFlags & 0x80;
      nHeighta = (float)nHeight;
      do
      {
        if ( v13 )
        {
          vXa = vX - (double)(ptQTilemap->anGraphicWidth[v12] / 2);
        }
        else if ( (bQGraphicFlags & 0x100) != 0 )
        {
          vXa = vX - (double)ptQTilemap->anGraphicWidth[v12];
        }
        else
        {
          vXa = vX;
        }
        iX = 0;
        if ( ptQTilemap->nWidth > 0 )
        {
          do
          {
            v14 = ptQTilemap->anID[i];
            if ( v14 )
            {
              QSprite_RegisterAZ(
                ptQSprite,
                vXa,
                vY,
                vR,
                vG,
                vB,
                vA,
                vZ,
                (unsigned __int8)(v14 - 1),
                bQGraphicFlags,
                nDepth);
              v12 = iY;
            }
            ++i;
            v33 = (float)nWidth;
            vXa = v33 + vXa;
            ++iX;
          }
          while ( iX < ptQTilemap->nWidth );
          v13 = bQGraphicFlags & 0x80;
        }
        iY = ++v12;
        vY = nHeighta + vY;
      }
      while ( v12 < ptQTilemap->nHeight );
    }
  }
}

// source: b/4/qtilemap.c:558  [anchor-mhash]
int __cdecl QTilemap_GetWidth(struct QTilemap_s *ptQTilemap)
{
  int nHeight; // ecx
  int result; // eax
  __int16 *anGraphicWidth; // edx
  int v4; // esi

  nHeight = ptQTilemap->nHeight;
  result = 0;
  if ( nHeight > 0 )
  {
    anGraphicWidth = ptQTilemap->anGraphicWidth;
    v4 = nHeight;
    do
    {
      if ( *anGraphicWidth > result )
        result = *anGraphicWidth;
      ++anGraphicWidth;
      --v4;
    }
    while ( v4 );
  }
  return result;
}

// source: b/4/qtilemap.c:581  [anchor-mhash]
int __cdecl QTilemap_GetHeight(struct QTilemap_s *ptQTilemap)
{
  return ptQTilemap->nHeight * ptQTilemap->ptQSprite->atQAnimframe[ptQTilemap->ptQSprite->nQAnimframes].nHeight;
}

// source: b/4/qtilemap.c:596  [size]
void __cdecl QTilemap_Clear(struct QTilemap_s *ptQTilemap)
{
  memset(ptQTilemap->anGraphicWidth, 0, 2 * ptQTilemap->nHeight);
  memset(ptQTilemap->anID, 0, ptQTilemap->nHeight * ptQTilemap->nWidth);
}
