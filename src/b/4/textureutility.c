/* b/4/textureutility.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/4/textureutility.c:50  [size]
void __cdecl TextureUtility_UpdateGammaLookup(struct TextureFilterContext_s *ptTextureFilterContext)
{
  int v1; // esi
  int i; // [esp+0h] [ebp-Ch]
  double v3; // [esp+4h] [ebp-8h]

  if ( ptTextureFilterContext->vGamma != TextureUtility_vGamma )
  {
    if ( ptTextureFilterContext->vGamma <= 9.999999747378752e-05 )
      TextureUtility_vGamma = 9.999999747378752e-05;
    else
      TextureUtility_vGamma = ptTextureFilterContext->vGamma;
    v1 = 0;
    i = 0;
    v3 = 1.0 / TextureUtility_vGamma;
    do
    {
      flt_834CFA4[++v1] = pow((double)i * 0.00390625, v3) * 256.0;
      i = v1;
    }
    while ( v1 < 256 );
  }
}

// source: b/4/textureutility.c:106  [size]
int __cdecl TextureUtility_ShrinkToHalf8(void *pxDestination, void *pxSource, int nWidth, int nHeight)
{
  int result; // eax
  int v7; // esi
  int v8; // edx
  char *v9; // esi
  char *v10; // eax
  unsigned __int8 *v11; // ecx
  bool v12; // zf
  int pxSourcea = *(int *)&pxSource; // [esp+10h] [ebp+8h] ARGSLOT

  result = nHeight - (nHeight >> 31);
  if ( nHeight / 2 > 0 )
  {
    v7 = nWidth;
    result = nWidth / 2;
    pxSourcea = nHeight / 2;
    do
    {
      v8 = 0;
      if ( result > 0 )
      {
        v9 = (char *)pxSource + v7;
        v10 = (char *)((_BYTE *)pxSource - v9);
        v11 = (unsigned __int8 *)(v9 + 1);
        while ( 1 )
        {
          *((_BYTE *)pxDestination + v8) = (v11[(_DWORD)v10]
                                          + *(v11 - 1)
                                          + *v11
                                          + (unsigned int)*((unsigned __int8 *)pxSource + 2 * v8)
                                          + 2) >> 2;
          result = nWidth / 2;
          ++v8;
          v11 += 2;
          if ( v8 >= nWidth / 2 )
            break;
          v10 = (char *)((_BYTE *)pxSource - v9);
        }
        v7 = nWidth;
      }
      pxSource = (char *)pxSource + 2 * v7;
      v12 = pxSourcea == 1;
      pxDestination = (char *)pxDestination + result;
      --pxSourcea;
    }
    while ( !v12 );
  }
  return result;
}

// source: b/4/textureutility.c:177  [size]
int __cdecl TextureUtility_ShrinkToHalf32HighQuality(
        void *pxDestination,
        void *pxSource,
        int nWidth,
        int nHeight)
{
  int v4; // edi
  int v5; // edx
  int v6; // esi
  unsigned int *v7; // ebx
  char *v8; // edx
  int v9; // esi
  unsigned int v10; // edi
  unsigned int v11; // ecx
  unsigned int v12; // edx
  double v13; // st7
  double v14; // st7
  double v15; // st6
  bool v16; // zf
  float v17; // [esp+10h] [ebp-40h]
  float v18; // [esp+14h] [ebp-3Ch]
  float v19; // [esp+18h] [ebp-38h]
  float v20; // [esp+1Ch] [ebp-34h]
  char *v21; // [esp+20h] [ebp-30h]
  float vG; // [esp+24h] [ebp-2Ch]
  float vR; // [esp+28h] [ebp-28h]
  unsigned int *pnDestOffs; // [esp+2Ch] [ebp-24h]
  unsigned int *v25; // [esp+30h] [ebp-20h]
  int v26; // [esp+34h] [ebp-1Ch]
  int v27; // [esp+38h] [ebp-18h]
  int nNewWidth; // [esp+40h] [ebp-10h]
  int v29; // [esp+44h] [ebp-Ch]

  v4 = nWidth >> 1;
  v5 = nHeight >> 1;
  nNewWidth = nWidth >> 1;
  if ( v5 > 0 )
  {
    v6 = 8 * nWidth;
    nWidth = (int)pxSource + 4 * nWidth;
    v29 = v6;
    v21 = (char *)pxSource;
    v26 = nWidth;
    v27 = v5;
    do
    {
      v7 = (unsigned int *)v21;
      v8 = (char *)pxDestination + 4 * v4;
      pnDestOffs = (unsigned int *)pxDestination;
      v25 = (unsigned int *)v8;
      if ( pxDestination < v8 )
      {
        while ( 1 )
        {
          v9 = *(_DWORD *)nWidth;
          v10 = *(_DWORD *)(nWidth + 4);
          v11 = *v7;
          v12 = v7[1];
          v7 += 2;
          v20 = (double)HIBYTE(v10) * 0.003921568859368563;
          v19 = (double)HIBYTE(*(_DWORD *)nWidth) * 0.003921568859368563;
          v18 = (double)HIBYTE(v12) * 0.003921568859368563;
          v13 = (double)HIBYTE(v11) * 0.003921568859368563;
          v17 = v13;
          v14 = v13 + v18 + v19 + v20;
          if ( v14 <= 0.0 )
          {
            v15 = 0.0;
            vG = 0.0;
            vR = 0.0;
          }
          else
          {
            vR = ((double)(unsigned __int8)v11 * v17
                + (double)(unsigned __int8)v12 * v18
                + (double)(unsigned __int8)v9 * v19
                + (double)(unsigned __int8)v10 * v20)
               * (1.0
                / v14)
               + 0.5;
            vG = ((double)BYTE1(v11) * v17
                + (double)BYTE1(v12) * v18
                + (double)BYTE1(v9) * v19
                + (double)BYTE1(v10) * v20)
               * (1.0
                / v14)
               + 0.5;
            v15 = 1.0
                / v14
                * ((double)BYTE2(v11) * v17
                 + (double)BYTE2(v12) * v18
                 + (double)BYTE2(v9) * v19
                 + (double)BYTE2(v10) * v20)
                + 0.5;
          }
          *pnDestOffs++ = (__int64)vR
                        | (((__int64)vG
                          | (((unsigned int)(__int64)v15 | ((unsigned int)(__int64)(v14 * 63.75 + 0.5) << 8)) << 8)) << 8);
          if ( pnDestOffs >= v25 )
            break;
          nWidth += 8;
        }
        v4 = nNewWidth;
        v6 = v29;
        v8 = (char *)v25;
      }
      v21 += v6;
      pxDestination = v8;
      nWidth = v6 + v26;
      v16 = v27 == 1;
      v26 += v6;
      --v27;
    }
    while ( !v16 );
  }
  return nWidth;
}

// source: b/4/textureutility.c:277  [size]
int __cdecl TextureUtility_ShrinkToHalf32(
        void *pxDestination,
        void *pxSource,
        int nWidth,
        int nHeight)
{
  int v4; // ebx
  int v5; // ecx
  int v6; // esi
  unsigned int *v7; // edi
  unsigned int *v8; // eax
  char *v9; // ecx
  unsigned int v10; // ecx
  unsigned int v11; // esi
  unsigned int v12; // edx
  unsigned int *v13; // edi
  unsigned int v14; // eax
  int v15; // edi
  int v16; // ebx
  int v17; // ebp
  unsigned int v18; // eax
  bool v19; // zf
  unsigned int *v20; // [esp+8h] [ebp-24h]
  unsigned int *pnDestOffs; // [esp+Ch] [ebp-20h]
  unsigned int *v22; // [esp+10h] [ebp-1Ch]
  int v23; // [esp+14h] [ebp-18h]
  unsigned int *pnSourceOffs0; // [esp+18h] [ebp-14h]
  unsigned int *pnSourceOffs1; // [esp+1Ch] [ebp-10h]
  unsigned int *v26; // [esp+20h] [ebp-Ch]
  int nNewWidth; // [esp+24h] [ebp-8h]
  int v28; // [esp+28h] [ebp-4h]

  v4 = nWidth >> 1;
  v5 = nHeight >> 1;
  nNewWidth = nWidth >> 1;
  if ( v5 > 0 )
  {
    v20 = (unsigned int *)pxSource;
    v6 = 8 * nWidth;
    v7 = (unsigned int *)((char *)pxSource + 4 * nWidth);
    v28 = 8 * nWidth;
    v22 = v7;
    v23 = v5;
    do
    {
      v8 = v20;
      v9 = (char *)pxDestination + 4 * v4;
      pnDestOffs = (unsigned int *)pxDestination;
      v26 = (unsigned int *)v9;
      if ( pxDestination < v9 )
      {
        while ( 1 )
        {
          v10 = *v8;
          v11 = *v7;
          v12 = v8[1];
          v13 = v7 + 2;
          pnSourceOffs0 = v8 + 2;
          v14 = *(v13 - 1);
          pnSourceOffs1 = v13;
          v15 = ((v10 & 0xFF00) + (v12 & 0xFF00) + (v11 & 0xFF00) + (v14 & 0xFF00) + 512) & 0x3FC00
              | ((v12 & 0xFF0000) + (v11 & 0xFF0000) + (v14 & 0xFF0000) + (v10 & 0xFF0000) + 0x20000) & 0x3FC0000;
          v16 = (unsigned __int8)v12 + (unsigned __int8)v11 + (unsigned __int8)v14;
          v17 = (unsigned __int8)v10;
          v18 = (unsigned int)&MTP_atLODVirModel[3].atBoneVertexRefs[26].atVertexRefs[479]
              + ((v12 >> 2) & 0x3FC00000)
              + ((v11 >> 2) & 0x3FC00000)
              + ((v14 >> 2) & 0x3FC00000)
              + ((v10 >> 2) & 0x3FC00000);
          v9 = (char *)v26;
          *pnDestOffs++ = v18 & 0xFF000000 | (((v16 + v17 + 2) | (unsigned int)v15) >> 2);
          if ( pnDestOffs >= v26 )
            break;
          v8 = pnSourceOffs0;
          v7 = pnSourceOffs1;
        }
        v4 = nNewWidth;
        v6 = v28;
      }
      v20 = (unsigned int *)((char *)v20 + v6);
      v7 = (unsigned int *)((char *)v22 + v6);
      nWidth = v23 - 1;
      v19 = v23 == 1;
      pxDestination = v9;
      v22 = (unsigned int *)((char *)v22 + v6);
      --v23;
    }
    while ( !v19 );
  }
  return nWidth;
}

// source: b/4/textureutility.c:435  [size]
int __cdecl TextureUtility_ShrinkToHalfHeight32(
        void *pxDestination,
        void *pxSource,
        int nWidth,
        int nHeight)
{
  int v4; // edi
  int result; // eax
  int v7; // ecx
  int v8; // edx
  char *v9; // esi
  _BYTE *v10; // ecx
  int v11; // edx
  unsigned __int8 *v12; // eax
  int v13; // esi
  int v14; // edi
  int v15; // ebx
  bool v16; // zf
  char *v17; // [esp+8h] [ebp-34h]
  int v18; // [esp+Ch] [ebp-30h]
  char *v19; // [esp+10h] [ebp-2Ch]
  int v20; // [esp+14h] [ebp-28h]
  int v21; // [esp+18h] [ebp-24h]
  int v22; // [esp+1Ch] [ebp-20h]
  int v23; // [esp+20h] [ebp-1Ch]
  int v24; // [esp+24h] [ebp-18h]
  int anG; // [esp+2Ch] [ebp-10h]
  int anG_4; // [esp+30h] [ebp-Ch]
  int anB; // [esp+34h] [ebp-8h]
  char *pxDestinationa = *(char * *)&pxDestination; // [esp+40h] [ebp+4h] ARGSLOT

  v4 = nWidth;
  result = nHeight / 2;
  v7 = 4 * nWidth;
  if ( result > 0 )
  {
    v17 = (char *)pxDestination + 2;
    pxDestinationa = (char *)pxSource + 3;
    v22 = -1 - v7;
    v23 = -2 - v7;
    v8 = 8 * nWidth;
    v9 = (char *)pxSource + v7 + 3;
    v19 = v9;
    v24 = -3 - v7;
    v20 = result;
    do
    {
      if ( v4 > 0 )
      {
        v10 = v17;
        v11 = pxDestinationa - v9;
        v12 = (unsigned __int8 *)v9;
        v21 = pxDestinationa - v9;
        v18 = v4;
        while ( 1 )
        {
          v13 = v12[v11];
          v14 = *v12;
          anG = v12[v23];
          anG_4 = *(v12 - 2);
          anB = v12[v24];
          v15 = *(v12 - 3);
          *v10 = (*(v12 - 1) + (unsigned int)v12[v22] + 1) >> 1;
          *(v10 - 1) = (unsigned int)(anG_4 + anG + 1) >> 1;
          *(v10 - 2) = (unsigned int)(v15 + anB + 1) >> 1;
          v10[1] = (unsigned int)(v14 + v13 + 1) >> 1;
          v12 += 4;
          v10 += 4;
          if ( !--v18 )
            break;
          v11 = v21;
        }
        v4 = nWidth;
        v8 = 8 * nWidth;
        v9 = v19;
      }
      v9 += v8;
      result = v20 - 1;
      v16 = v20 == 1;
      v19 = v9;
      pxDestinationa += v8;
      v17 += 4 * v4;
      --v20;
    }
    while ( !v16 );
  }
  return result;
}

// source: b/4/textureutility.c:525  [size]
int __cdecl TextureUtility_ShrinkToHalfWidth32(
        void *pxDestination,
        void *pxSource,
        int nWidth,
        int nHeight)
{
  bool v5; // cc
  int v6; // ecx
  int v7; // ebx
  char *v8; // edi
  _BYTE *v9; // esi
  char *v10; // edx
  unsigned __int8 *v11; // ecx
  unsigned int v12; // ebx
  int v13; // edi
  bool v14; // zf
  char *v15; // [esp+4h] [ebp-40h]
  char *v16; // [esp+8h] [ebp-3Ch]
  int v17; // [esp+Ch] [ebp-38h]
  int nPitch; // [esp+24h] [ebp-20h]
  int v19; // [esp+28h] [ebp-1Ch]
  int anG_4; // [esp+30h] [ebp-14h]
  int anB; // [esp+34h] [ebp-10h]
  int anB_4; // [esp+38h] [ebp-Ch]
  char *pxDestinationa = *(char * *)&pxDestination; // [esp+48h] [ebp+4h] ARGSLOT
  char *pxSourcea = *(char * *)&pxSource; // [esp+4Ch] [ebp+8h] ARGSLOT

  v5 = nHeight <= 0;
  v6 = 4 * nWidth;
  nPitch = 4 * nWidth;
  if ( !v5 )
  {
    v7 = nWidth / 2;
    nWidth = v6 / 2;
    v8 = (char *)pxSource + 2;
    v15 = (char *)v7;
    v19 = v6 / 2;
    pxDestinationa = (char *)pxDestination + 2;
    v16 = (char *)pxSource + 2;
    v17 = nHeight;
    do
    {
      if ( v7 > 0 )
      {
        v9 = pxDestinationa;
        v10 = v8 - 1;
        v11 = (unsigned __int8 *)(v8 + 4);
        pxSourcea = v15;
        do
        {
          anG_4 = *(v11 - 1);
          anB = (unsigned __int8)*(v10 - 1);
          anB_4 = *(v11 - 2);
          v12 = (unsigned __int8)v10[2] + v11[1] + 1;
          v13 = (unsigned __int8)*v10;
          *v9 = (*v11 + (unsigned int)*(v11 - 4) + 1) >> 1;
          *(v9 - 1) = (unsigned int)(anG_4 + v13 + 1) >> 1;
          *(v9 - 2) = (unsigned int)(anB_4 + anB + 1) >> 1;
          v9[1] = v12 >> 1;
          v11 += 8;
          v10 += 8;
          v9 += 4;
          --pxSourcea;
        }
        while ( pxSourcea );
        v7 = (int)v15;
        v6 = nPitch;
        nWidth = v19;
        v8 = v16;
      }
      v8 += v6;
      v14 = v17 == 1;
      v16 = v8;
      pxDestinationa += nWidth;
      --v17;
    }
    while ( !v14 );
  }
  return nWidth;
}

// source: b/4/textureutility.c:617  [size]
void __cdecl TextureUtility_ConvertARGB1555ToARGB8888(
        void *pxDestination,
        int nDestinationWidth,
        int nDestinationHeight,
        void *pxSource,
        int nSourceWidth,
        int nSourceHeight,
        struct tuRect_s *ptClippingRect)
{
  int nX; // esi
  int nY; // eax
  int v9; // ecx
  char *v10; // eax
  int v11; // ecx
  char *v12; // esi
  char *v13; // ebp
  int v14; // edi
  unsigned __int16 v15; // cx
  char v16; // al
  char v17; // bl
  char v18; // dl
  char v19; // cl
  bool v20; // cc
  int nWidth; // [esp+10h] [ebp-Ch]
  int nHeight; // [esp+14h] [ebp-8h]
  int v23; // [esp+18h] [ebp-4h]
  char *pxDestinationa = *(char * *)&pxDestination; // [esp+20h] [ebp+4h] ARGSLOT
  char *pxSourcea = *(char * *)&pxSource; // [esp+2Ch] [ebp+10h] ARGSLOT

  if ( ptClippingRect )
  {
    nX = ptClippingRect->nX;
    nY = ptClippingRect->nY;
    nWidth = ptClippingRect->nWidth;
    if ( nWidth >= nSourceWidth - ptClippingRect->nX )
      nWidth = nSourceWidth - ptClippingRect->nX;
    v9 = ptClippingRect->nHeight;
    if ( v9 >= nSourceHeight - nY )
      nHeight = nSourceHeight - nY;
    else
      nHeight = v9;
  }
  else
  {
    nX = 0;
    nY = 0;
    nWidth = nSourceWidth;
    nHeight = nSourceHeight;
  }
  v10 = (char *)pxSource + 2 * nX + 2 * nSourceWidth * nY;
  pxSourcea = nullptr;
  if ( nDestinationHeight > 0 )
  {
    v11 = nDestinationWidth;
    v12 = (char *)pxDestination + 2;
    v23 = 2 * nSourceWidth;
    v13 = v10;
    pxDestinationa = (char *)pxDestination + 2;
    do
    {
      v14 = 0;
      if ( v11 > 0 )
      {
        do
        {
          if ( v14 >= nWidth || (int)pxSourcea >= nHeight )
          {
            v19 = 0;
            v18 = 0;
            v17 = 0;
            v16 = 0;
          }
          else
          {
            v15 = *(_WORD *)&v13[2 * v14];
            v16 = -((v15 & 0x8000) != 0);
            v17 = (v15 >> 7) & 0xF8;
            v18 = (v15 >> 2) & 0xF8;
            v19 = 8 * (v15 & 0x1F);
          }
          v12[1] = v16;
          *v12 = v17;
          *(v12 - 1) = v18;
          *(v12 - 2) = v19;
          ++v14;
          v12 += 4;
        }
        while ( v14 < nDestinationWidth );
        v11 = nDestinationWidth;
      }
      v12 = &pxDestinationa[4 * v11];
      v13 += v23;
      v20 = (int)++pxSourcea < nDestinationHeight;
      pxDestinationa = v12;
    }
    while ( v20 );
  }
}

// source: b/4/textureutility.c:711  [size]
void __cdecl TextureUtility_ConvertRGB565ToARGB8888(
        void *pxDestination,
        int nDestinationWidth,
        int nDestinationHeight,
        void *pxSource,
        int nSourceWidth,
        int nSourceHeight,
        struct tuRect_s *ptClippingRect)
{
  int nX; // esi
  int nY; // eax
  int v9; // ecx
  char *v10; // eax
  int v11; // ecx
  char *v12; // esi
  char *v13; // ebp
  int v14; // edi
  unsigned __int16 v15; // ax
  char v16; // bl
  char v17; // dl
  char v18; // cl
  char v19; // al
  bool v20; // cc
  int nWidth; // [esp+10h] [ebp-Ch]
  int nHeight; // [esp+14h] [ebp-8h]
  int v23; // [esp+18h] [ebp-4h]
  char *pxDestinationa = *(char * *)&pxDestination; // [esp+20h] [ebp+4h] ARGSLOT
  char *pxSourcea = *(char * *)&pxSource; // [esp+2Ch] [ebp+10h] ARGSLOT

  if ( ptClippingRect )
  {
    nX = ptClippingRect->nX;
    nY = ptClippingRect->nY;
    nWidth = ptClippingRect->nWidth;
    if ( nWidth >= nSourceWidth - ptClippingRect->nX )
      nWidth = nSourceWidth - ptClippingRect->nX;
    v9 = ptClippingRect->nHeight;
    if ( v9 >= nSourceHeight - nY )
      nHeight = nSourceHeight - nY;
    else
      nHeight = v9;
  }
  else
  {
    nX = 0;
    nY = 0;
    nWidth = nSourceWidth;
    nHeight = nSourceHeight;
  }
  v10 = (char *)pxSource + 2 * nX + 2 * nSourceWidth * nY;
  pxSourcea = nullptr;
  if ( nDestinationHeight > 0 )
  {
    v11 = nDestinationWidth;
    v12 = (char *)pxDestination + 2;
    v23 = 2 * nSourceWidth;
    v13 = v10;
    pxDestinationa = (char *)pxDestination + 2;
    do
    {
      v14 = 0;
      if ( v11 > 0 )
      {
        do
        {
          if ( v14 >= nWidth || (int)pxSourcea >= nHeight )
          {
            v19 = 0;
            v18 = 0;
            v17 = 0;
            v16 = 0;
          }
          else
          {
            v15 = *(_WORD *)&v13[2 * v14];
            v16 = -1;
            v17 = HIBYTE(v15) & 0xF8;
            v18 = (v15 >> 3) & 0xFC;
            v19 = 8 * (v15 & 0x1F);
          }
          *(v12 - 2) = v19;
          v12[1] = v16;
          *v12 = v17;
          *(v12 - 1) = v18;
          ++v14;
          v12 += 4;
        }
        while ( v14 < nDestinationWidth );
        v11 = nDestinationWidth;
      }
      v12 = &pxDestinationa[4 * v11];
      v13 += v23;
      v20 = (int)++pxSourcea < nDestinationHeight;
      pxDestinationa = v12;
    }
    while ( v20 );
  }
}

// source: b/4/textureutility.c:805  [size]
void __cdecl TextureUtility_ConvertARGB8888ToARGB1555(
        void *pxDestination,
        int nDestinationWidth,
        int nDestinationHeight,
        int isDithered,
        void *pxSource,
        int nSourceWidth,
        int nSourceHeight,
        struct tuRect_s *ptClippingRect)
{
  int nX; // esi
  int nY; // eax
  int v10; // ecx
  char *v11; // eax
  int v13; // ecx
  char *v14; // esi
  int v15; // edi
  int v16; // ebp
  __int16 v17; // cx
  __int16 v18; // dx
  __int16 v19; // ax
  bool v20; // cc
  int nWidth; // [esp+10h] [ebp-Ch]
  int nHeight; // [esp+14h] [ebp-8h]
  int v23; // [esp+18h] [ebp-4h]
  char *pxDestinationa = *(char * *)&pxDestination; // [esp+20h] [ebp+4h] ARGSLOT
  char *pxSourcea = *(char * *)&pxSource; // [esp+30h] [ebp+14h] ARGSLOT

  if ( ptClippingRect )
  {
    nX = ptClippingRect->nX;
    nY = ptClippingRect->nY;
    nWidth = ptClippingRect->nWidth;
    if ( nWidth >= nSourceWidth - ptClippingRect->nX )
      nWidth = nSourceWidth - ptClippingRect->nX;
    v10 = ptClippingRect->nHeight;
    if ( v10 >= nSourceHeight - nY )
      nHeight = nSourceHeight - nY;
    else
      nHeight = v10;
  }
  else
  {
    nX = 0;
    nY = 0;
    nWidth = nSourceWidth;
    nHeight = nSourceHeight;
  }
  v11 = (char *)pxSource + 4 * nX + 4 * nSourceWidth * nY;
  pxSourcea = nullptr;
  if ( nDestinationHeight > 0 )
  {
    v13 = nDestinationWidth;
    v14 = v11 + 2;
    v23 = 4 * nSourceWidth;
    pxDestinationa = v11 + 2;
    do
    {
      v15 = 0;
      if ( v13 > 0 )
      {
        do
        {
          if ( v15 >= nWidth || (int)pxSourcea >= nHeight )
          {
            v19 = 0;
            v17 = 0;
            v18 = 0;
            LOWORD(v16) = 0;
          }
          else
          {
            v16 = v14[1] != 0 ? 0x8000 : 0;
            v17 = 4 * (*(v14 - 1) & 0xF8);
            v18 = (*v14 & 0xF8) << 7;
            v19 = (unsigned __int8)*(v14 - 2) >> 3;
          }
          *((_WORD *)pxDestination + v15++) = v16 | v18 | v17 | v19;
          v14 += 4;
        }
        while ( v15 < nDestinationWidth );
        v13 = nDestinationWidth;
      }
      pxDestination = (char *)pxDestination + 2 * v13;
      v14 = &pxDestinationa[v23];
      v20 = (int)++pxSourcea < nDestinationHeight;
      pxDestinationa += v23;
    }
    while ( v20 );
  }
}

// source: b/4/textureutility.c:896  [size]
int __cdecl TextureUtility_ConvertARGB8888ToRGB565(
        void *pxDestination,
        int nDestinationWidth,
        int nDestinationHeight,
        int isDithered,
        void *pxSource,
        int nSourceWidth,
        int nSourceHeight,
        struct tuRect_s *ptClippingRect)
{
  int nX; // esi
  int nY; // eax
  int v11; // ecx
  int result; // eax
  char *v14; // esi
  int i; // edx
  __int16 v16; // di
  __int16 v17; // cx
  __int16 v18; // ax
  bool v19; // cc
  int nWidth; // [esp+10h] [ebp-Ch]
  int nHeight; // [esp+14h] [ebp-8h]
  int v22; // [esp+18h] [ebp-4h]
  char *pxDestinationa = *(char * *)&pxDestination; // [esp+20h] [ebp+4h] ARGSLOT
  char *pxSourcea = *(char * *)&pxSource; // [esp+30h] [ebp+14h] ARGSLOT

  if ( ptClippingRect )
  {
    nX = ptClippingRect->nX;
    nY = ptClippingRect->nY;
    nWidth = ptClippingRect->nWidth;
    if ( nWidth >= nSourceWidth - ptClippingRect->nX )
      nWidth = nSourceWidth - ptClippingRect->nX;
    v11 = ptClippingRect->nHeight;
    if ( v11 >= nSourceHeight - nY )
      nHeight = nSourceHeight - nY;
    else
      nHeight = v11;
  }
  else
  {
    nX = 0;
    nY = 0;
    nWidth = nSourceWidth;
    nHeight = nSourceHeight;
  }
  result = (int)pxSource + 4 * nX + 4 * nSourceWidth * nY;
  pxSourcea = nullptr;
  if ( nDestinationHeight > 0 )
  {
    v14 = (char *)(result + 1);
    v22 = 4 * nSourceWidth;
    pxDestinationa = (char *)(result + 1);
    do
    {
      for ( i = 0; i < nDestinationWidth; v14 += 4 )
      {
        if ( i >= nWidth || (int)pxSourcea >= nHeight )
        {
          v18 = 0;
          v17 = 0;
          v16 = 0;
        }
        else
        {
          v16 = *(_WORD *)v14 & 0xF800;
          v17 = 8 * (*v14 & 0xF8);
          v18 = (unsigned __int8)*(v14 - 1) >> 3;
        }
        *((_WORD *)pxDestination + i++) = v16 | v17 | v18;
      }
      pxDestination = (char *)pxDestination + 2 * nDestinationWidth;
      result = nDestinationHeight;
      v14 = &pxDestinationa[v22];
      v19 = (int)++pxSourcea < nDestinationHeight;
      pxDestinationa += v22;
    }
    while ( v19 );
  }
  return result;
}

// source: b/4/textureutility.c:985  [size]
int __cdecl TextureUtility_ConvertARGB8888ToARGB4444(
        void *pxDestination,
        int nDestinationWidth,
        int nDestinationHeight,
        int isDithered,
        void *pxSource,
        int nSourceWidth,
        int nSourceHeight,
        struct tuRect_s *ptClippingRect)
{
  int nX; // esi
  int nY; // eax
  int v11; // ecx
  int result; // eax
  int v14; // ecx
  char *v15; // edx
  int v16; // ebp
  int v17; // eax
  __int16 v18; // cx
  __int16 v19; // di
  __int16 v20; // si
  __int16 v21; // cx
  __int16 v22; // ax
  bool v23; // cc
  int nWidth; // [esp+10h] [ebp-Ch]
  int nHeight; // [esp+14h] [ebp-8h]
  int v26; // [esp+18h] [ebp-4h]
  char *pxDestinationa = *(char * *)&pxDestination; // [esp+20h] [ebp+4h] ARGSLOT
  char *pxSourcea = *(char * *)&pxSource; // [esp+30h] [ebp+14h] ARGSLOT

  if ( ptClippingRect )
  {
    nX = ptClippingRect->nX;
    nY = ptClippingRect->nY;
    nWidth = ptClippingRect->nWidth;
    if ( nWidth >= nSourceWidth - ptClippingRect->nX )
      nWidth = nSourceWidth - ptClippingRect->nX;
    v11 = ptClippingRect->nHeight;
    if ( v11 >= nSourceHeight - nY )
      nHeight = nSourceHeight - nY;
    else
      nHeight = v11;
  }
  else
  {
    nX = 0;
    nY = 0;
    nWidth = nSourceWidth;
    nHeight = nSourceHeight;
  }
  result = (int)pxSource + 4 * nX + 4 * nSourceWidth * nY;
  pxSourcea = nullptr;
  if ( nDestinationHeight > 0 )
  {
    v14 = nDestinationWidth;
    v26 = 4 * nSourceWidth;
    v15 = (char *)(result + 3);
    pxDestinationa = (char *)(result + 3);
    do
    {
      v16 = 0;
      if ( v14 > 0 )
      {
        do
        {
          if ( v16 >= nWidth || (int)pxSourcea >= nHeight )
          {
            v22 = 0;
            v20 = 0;
            v21 = 0;
            v19 = 0;
          }
          else
          {
            v17 = (unsigned __int8)*v15 + 15;
            if ( v17 >= 255 )
              LOBYTE(v17) = -1;
            LOBYTE(v18) = 0;
            HIBYTE(v18) = v17 & 0xF0;
            v19 = v18;
            v20 = *(v15 - 2) & 0xF0;
            v21 = 16 * (*(v15 - 1) & 0xF0);
            v22 = (unsigned __int8)*(v15 - 3) >> 4;
          }
          *((_WORD *)pxDestination + v16++) = v19 | v21 | v20 | v22;
          v15 += 4;
        }
        while ( v16 < nDestinationWidth );
        v14 = nDestinationWidth;
      }
      pxDestination = (char *)pxDestination + 2 * v14;
      result = nDestinationHeight;
      v15 = &pxDestinationa[v26];
      v23 = (int)++pxSourcea < nDestinationHeight;
      pxDestinationa += v26;
    }
    while ( v23 );
  }
  return result;
}

// source: b/4/textureutility.c:1074  [size]
void __cdecl TextureUtility_Fit32bitTexture(
        void *pxDestination,
        int nDestinationWidth,
        int nDestinationHeight,
        void *pxSource,
        int nSourceWidth,
        int nSourceHeight,
        struct tuRect_s *ptClippingRect)
{
  int nX; // esi
  int nY; // eax
  int v9; // ecx
  char *v10; // eax
  int v11; // ebx
  char *v13; // esi
  int v14; // edx
  _DWORD *v15; // eax
  int v16; // esi
  int v17; // ecx
  int nWidth; // [esp+10h] [ebp-Ch]
  int nHeight; // [esp+14h] [ebp-8h]
  int v20; // [esp+18h] [ebp-4h]
  char *pxSourcea = *(char * *)&pxSource; // [esp+2Ch] [ebp+10h] ARGSLOT

  if ( ptClippingRect )
  {
    nX = ptClippingRect->nX;
    nY = ptClippingRect->nY;
    nWidth = ptClippingRect->nWidth;
    if ( nWidth >= nSourceWidth - ptClippingRect->nX )
      nWidth = nSourceWidth - ptClippingRect->nX;
    v9 = ptClippingRect->nHeight;
    if ( v9 >= nSourceHeight - nY )
      nHeight = nSourceHeight - nY;
    else
      nHeight = v9;
  }
  else
  {
    nX = 0;
    nY = 0;
    nWidth = nSourceWidth;
    nHeight = nSourceHeight;
  }
  v10 = (char *)pxSource + 16 * nX + 16 * nSourceWidth * nY;
  v11 = 0;
  if ( nDestinationHeight > 0 )
  {
    v13 = v10;
    v20 = 4 * nSourceWidth;
    pxSourcea = v10;
    do
    {
      v14 = 0;
      if ( nDestinationWidth > 0 )
      {
        v15 = pxDestination;
        v16 = v13 - (_BYTE *)pxDestination;
        do
        {
          if ( v14 >= nWidth || v11 >= nHeight )
            v17 = 0;
          else
            v17 = *(_DWORD *)((char *)v15 + v16);
          *v15 = v17;
          ++v14;
          ++v15;
        }
        while ( v14 < nDestinationWidth );
      }
      pxDestination = (char *)pxDestination + 4 * nDestinationWidth;
      ++v11;
      v13 = &pxSourcea[v20];
      pxSourcea += v20;
    }
    while ( v11 < nDestinationHeight );
  }
}

// source: b/4/textureutility.c:1152  [size]
void __cdecl TextureUtility_Fit16bitTexture(
        void *pxDestination,
        int nDestinationWidth,
        int nDestinationHeight,
        void *pxSource,
        int nSourceWidth,
        int nSourceHeight,
        struct tuRect_s *ptClippingRect)
{
  int nX; // esi
  int nY; // eax
  int v9; // ecx
  char *v10; // eax
  int v11; // ebx
  char *v13; // esi
  int v14; // edx
  _WORD *v15; // eax
  int v16; // esi
  __int16 v17; // cx
  int nWidth; // [esp+10h] [ebp-Ch]
  int nHeight; // [esp+14h] [ebp-8h]
  int v20; // [esp+18h] [ebp-4h]
  char *pxSourcea = *(char * *)&pxSource; // [esp+2Ch] [ebp+10h] ARGSLOT

  if ( ptClippingRect )
  {
    nX = ptClippingRect->nX;
    nY = ptClippingRect->nY;
    nWidth = ptClippingRect->nWidth;
    if ( nWidth >= nSourceWidth - ptClippingRect->nX )
      nWidth = nSourceWidth - ptClippingRect->nX;
    v9 = ptClippingRect->nHeight;
    if ( v9 >= nSourceHeight - nY )
      nHeight = nSourceHeight - nY;
    else
      nHeight = v9;
  }
  else
  {
    nX = 0;
    nY = 0;
    nWidth = nSourceWidth;
    nHeight = nSourceHeight;
  }
  v10 = (char *)pxSource + 2 * nX + 2 * nSourceWidth * nY;
  v11 = 0;
  if ( nDestinationHeight > 0 )
  {
    v13 = v10;
    v20 = 2 * nSourceWidth;
    pxSourcea = v10;
    do
    {
      v14 = 0;
      if ( nDestinationWidth > 0 )
      {
        v15 = pxDestination;
        v16 = v13 - (_BYTE *)pxDestination;
        do
        {
          if ( v14 >= nWidth || v11 >= nHeight )
            v17 = 0;
          else
            v17 = *(_WORD *)((char *)v15 + v16);
          *v15 = v17;
          ++v14;
          ++v15;
        }
        while ( v14 < nDestinationWidth );
      }
      pxDestination = (char *)pxDestination + 2 * nDestinationWidth;
      ++v11;
      v13 = &pxSourcea[v20];
      pxSourcea += v20;
    }
    while ( v11 < nDestinationHeight );
  }
}

// source: b/4/textureutility.c:1229  [size]
int __cdecl TextureUtility_Fit8bitTexture(
        void *pxDestination,
        int nDestinationWidth,
        int nDestinationHeight,
        void *pxSource,
        int nSourceWidth,
        int nSourceHeight,
        struct tuRect_s *ptClippingRect)
{
  int nX; // edx
  int nY; // eax
  int v10; // ecx
  int v11; // ebx
  int result; // eax
  int v13; // esi
  int v15; // edi
  int v16; // eax
  int v17; // edi
  char v18; // cl
  int nWidth; // [esp+10h] [ebp-8h]
  int nHeight; // [esp+14h] [ebp-4h]
  int nSourceWidtha = *(int *)&nSourceWidth; // [esp+2Ch] [ebp+14h] ARGSLOT

  if ( ptClippingRect )
  {
    nX = ptClippingRect->nX;
    nY = ptClippingRect->nY;
    nWidth = ptClippingRect->nWidth;
    if ( nWidth >= nSourceWidth - ptClippingRect->nX )
      nWidth = nSourceWidth - ptClippingRect->nX;
    v10 = ptClippingRect->nHeight;
    v11 = nSourceWidth;
    nSourceHeight -= nY;
    if ( v10 < nSourceHeight )
    {
      nHeight = v10;
      goto LABEL_8;
    }
  }
  else
  {
    v11 = nSourceWidth;
    nX = 0;
    nY = 0;
    nWidth = nSourceWidth;
  }
  nHeight = nSourceHeight;
LABEL_8:
  result = (int)pxSource + nX + v11 * nY;
  v13 = 0;
  if ( nDestinationHeight > 0 )
  {
    v15 = result;
    nSourceWidtha = result;
    do
    {
      v16 = 0;
      if ( nDestinationWidth > 0 )
      {
        v17 = v15 - (_DWORD)pxDestination;
        do
        {
          if ( v16 >= nWidth || v13 >= nHeight )
            v18 = 0;
          else
            v18 = *((_BYTE *)pxDestination + v17 + v16);
          *((_BYTE *)pxDestination + v16++) = v18;
        }
        while ( v16 < nDestinationWidth );
      }
      result = nDestinationHeight;
      ++v13;
      v15 = v11 + nSourceWidtha;
      pxDestination = (char *)pxDestination + nDestinationWidth;
      nSourceWidtha += v11;
    }
    while ( v13 < nDestinationHeight );
  }
  return result;
}

// source: b/4/textureutility.c:1336  [size]
void __cdecl TextureUtility_FitInterleavedARGB8888(
        void *pxDestinationA,
        void *pxDestinationR,
        void *pxDestinationG,
        void *pxDestinationB,
        int nDestinationWidth,
        int nDestinationHeight,
        int nDestinationModuloA,
        int nDestinationModuloR,
        int nDestinationModuloG,
        int nDestinationModuloB,
        void *pxSourceA,
        void *pxSourceR,
        void *pxSourceG,
        void *pxSourceB,
        int nSourceWidth,
        int nSourceHeight,
        int nSourceModuloA,
        int nSourceModuloR,
        int nSourceModuloG,
        int nSourceModuloB,
        struct tuRect_s *ptClippingRect)
{
  int v21; // edx
  int nX; // esi
  int v23; // eax
  int v24; // ebx
  int v25; // ecx
  int v26; // eax
  char *v27; // ebp
  unsigned __int8 *v28; // ebx
  unsigned __int8 *v29; // ecx
  int v30; // eax
  int v31; // esi
  int v32; // edx
  _BYTE *v33; // edi
  _BYTE *v34; // esi
  _BYTE *v35; // edx
  _BYTE *v36; // ecx
  bool v37; // cc
  int nHeight; // [esp+10h] [ebp-34h]
  unsigned __int8 *anSourceG; // [esp+14h] [ebp-30h]
  unsigned __int8 *anSourceB; // [esp+18h] [ebp-2Ch]
  int nY; // [esp+1Ch] [ebp-28h]
  unsigned __int8 *anSourceR; // [esp+20h] [ebp-24h]
  int v43; // [esp+24h] [ebp-20h]
  int v44; // [esp+28h] [ebp-1Ch]
  int v45; // [esp+2Ch] [ebp-18h]
  int v46; // [esp+30h] [ebp-14h]
  int v47; // [esp+40h] [ebp-4h]
  _BYTE *pxSourceAa = *(_BYTE * *)&pxSourceA; // [esp+70h] [ebp+2Ch] ARGSLOT
  unsigned __int8 *pxSourceRa = *(unsigned __int8 * *)&pxSourceR; // [esp+74h] [ebp+30h] ARGSLOT
  unsigned __int8 *pxSourceGa = *(unsigned __int8 * *)&pxSourceG; // [esp+78h] [ebp+34h] ARGSLOT
  unsigned __int8 *pxSourceBa = *(unsigned __int8 * *)&pxSourceB; // [esp+7Ch] [ebp+38h] ARGSLOT
  struct tuRect_s *ptClippingRecta = *(struct tuRect_s * *)&ptClippingRect; // [esp+98h] [ebp+54h] ARGSLOT

  v21 = nSourceWidth;
  if ( ptClippingRect )
  {
    nX = ptClippingRect->nX;
    v23 = ptClippingRect->nY;
    v24 = nSourceWidth - ptClippingRect->nX;
    nSourceWidth = ptClippingRect->nWidth;
    if ( nSourceWidth >= v24 )
      nSourceWidth = v24;
    v25 = ptClippingRect->nHeight;
    if ( v25 >= nSourceHeight - v23 )
    {
      nHeight = nSourceHeight - v23;
      goto LABEL_8;
    }
  }
  else
  {
    v25 = nSourceHeight;
    nX = 0;
    v23 = 0;
  }
  nHeight = v25;
LABEL_8:
  v26 = nX + v21 * v23;
  v27 = (char *)pxSourceA + nSourceModuloA * v26;
  v28 = (unsigned __int8 *)pxSourceR + nSourceModuloR * v26;
  v29 = (unsigned __int8 *)pxSourceG + nSourceModuloG * v26;
  anSourceB = (unsigned __int8 *)pxSourceB + nSourceModuloB * v26;
  anSourceR = v28;
  anSourceG = v29;
  nY = 0;
  if ( nDestinationHeight > 0 )
  {
    v30 = nSourceModuloA * v21;
    v45 = nSourceModuloR * v21;
    v46 = nSourceModuloB * v21;
    v31 = nSourceModuloG * v21;
    v32 = nDestinationWidth;
    v47 = nDestinationModuloB * nDestinationWidth;
    v33 = pxDestinationB;
    v43 = v30;
    v44 = v31;
    while ( 1 )
    {
      ptClippingRecta = nullptr;
      if ( v32 > 0 )
      {
        v34 = pxDestinationG;
        v35 = pxDestinationR;
        v36 = pxDestinationA;
        pxSourceBa = anSourceB;
        pxSourceGa = anSourceG;
        pxSourceRa = v28;
        pxSourceAa = v27;
        do
        {
          if ( (int)ptClippingRecta >= nSourceWidth || nY >= nHeight )
          {
            *v36 = 0;
            *v35 = 0;
            *v34 = 0;
            *v33 = 0;
          }
          else
          {
            *v36 = *pxSourceAa;
            *v35 = *pxSourceRa;
            *v34 = *pxSourceGa;
            *v33 = *pxSourceBa;
          }
          ptClippingRecta = (struct tuRect_s *)((char *)ptClippingRecta + 1);
          pxSourceAa += nSourceModuloA;
          pxSourceRa += nSourceModuloR;
          pxSourceGa += nSourceModuloG;
          pxSourceBa += nSourceModuloB;
          v36 += nDestinationModuloA;
          v35 += nDestinationModuloR;
          v34 += nDestinationModuloG;
          v33 += nDestinationModuloB;
        }
        while ( (int)ptClippingRecta < nDestinationWidth );
        v28 = anSourceR;
        v30 = v43;
        v31 = v44;
        v29 = anSourceG;
      }
      v28 += v45;
      anSourceB += v46;
      pxDestinationA = (char *)pxDestinationA + nDestinationModuloA * nDestinationWidth;
      pxDestinationR = (char *)pxDestinationR + nDestinationModuloR * nDestinationWidth;
      pxDestinationG = (char *)pxDestinationG + nDestinationModuloG * nDestinationWidth;
      v33 = (char *)pxDestinationB + v47;
      v29 += v31;
      v27 += v30;
      v37 = nY + 1 < nDestinationHeight;
      anSourceR = v28;
      anSourceG = v29;
      pxDestinationB = (char *)pxDestinationB + v47;
      ++nY;
      if ( !v37 )
        break;
      v32 = nDestinationWidth;
    }
  }
}

// source: b/4/textureutility.c:1427  [size]
void *__cdecl TextureUtility_ConvertARGB8888ToRGB888WithAlpha8(
        void *pxDestinationA,
        void *pxDestinationRGB,
        int nDestinationWidth,
        int nDestinationHeight,
        void *pxSource,
        int nSourceWidth,
        int nSourceHeight,
        struct tuRect_s *ptClippingRect)
{
  void *result; // eax

  TextureUtility_FitInterleavedARGB8888(
    pxDestinationA,
    pxDestinationRGB,
    (char *)pxDestinationRGB + 1,
    (char *)pxDestinationRGB + 2,
    nDestinationWidth,
    nDestinationHeight,
    1,
    3,
    3,
    3,
    (char *)pxSource + 3,
    (char *)pxSource + 2,
    (char *)pxSource + 1,
    pxSource,
    nSourceWidth,
    nSourceHeight,
    4,
    4,
    4,
    4,
    ptClippingRect);
  return result;
}

// source: b/4/textureutility.c:1472  [size]
void *__cdecl TextureUtility_FitRGB888WithAlpha8(
        void *pxDestinationA,
        void *pxDestinationRGB,
        int nDestinationWidth,
        int nDestinationHeight,
        void *pxSourceA,
        void *pxSourceRGB,
        int nSourceWidth,
        int nSourceHeight,
        struct tuRect_s *ptClippingRect)
{
  void *result; // eax

  TextureUtility_FitInterleavedARGB8888(
    pxDestinationA,
    pxDestinationRGB,
    (char *)pxDestinationRGB + 1,
    (char *)pxDestinationRGB + 2,
    nDestinationWidth,
    nDestinationHeight,
    1,
    3,
    3,
    3,
    pxSourceA,
    pxSourceRGB,
    (char *)pxSourceRGB + 1,
    (char *)pxSourceRGB + 2,
    nSourceWidth,
    nSourceHeight,
    1,
    3,
    3,
    3,
    ptClippingRect);
  return result;
}

// source: b/4/textureutility.c:1520  [size]
int __cdecl TextureUtility_ConvertARGB88ToARGB8888(
        void *pxDestination,
        int nDestinationWidth,
        int nDestinationHeight,
        void *pxSourceAlpha,
        void *pxSourceBitmap,
        void *pxSourcePalette,
        int nSourceWidth,
        int nSourceHeight,
        struct tuRect_s *ptClippingRect)
{
  int v9; // ebx
  int nX; // edx
  int nY; // eax
  int v13; // ecx
  void *v14; // ecx
  unsigned __int8 *v15; // esi
  char *v16; // edi
  int result; // eax
  int v18; // edx
  int v19; // ebp
  _BYTE *v20; // eax
  _BYTE *v21; // ecx
  int v22; // esi
  char v23; // dl
  int nWidth; // [esp+10h] [ebp-Ch]
  int nHeight; // [esp+14h] [ebp-8h]
  unsigned __int8 *anSourceAlpha; // [esp+18h] [ebp-4h]
  void *pxDestinationa = *(void * *)&pxDestination; // [esp+20h] [ebp+4h] ARGSLOT

  v9 = nSourceWidth;
  if ( ptClippingRect )
  {
    nX = ptClippingRect->nX;
    nY = ptClippingRect->nY;
    nWidth = ptClippingRect->nWidth;
    if ( nWidth >= nSourceWidth - ptClippingRect->nX )
      nWidth = nSourceWidth - ptClippingRect->nX;
    v13 = ptClippingRect->nHeight;
    nSourceHeight -= nY;
    if ( v13 < nSourceHeight )
    {
      nHeight = v13;
      goto LABEL_8;
    }
  }
  else
  {
    nX = 0;
    nY = 0;
    nWidth = nSourceWidth;
  }
  nHeight = nSourceHeight;
LABEL_8:
  v14 = pxSourceAlpha;
  if ( pxSourceAlpha )
  {
    v15 = (unsigned __int8 *)pxSourceAlpha + nX + nSourceWidth * nY;
    anSourceAlpha = v15;
  }
  else
  {
    v15 = anSourceAlpha;
  }
  v16 = (char *)pxSourceBitmap + nX + nSourceWidth * nY;
  result = nDestinationHeight;
  v18 = 0;
  for ( pxDestinationa = nullptr; v18 < nDestinationHeight; pxDestinationa = (void *)v18 )
  {
    v19 = 0;
    if ( nDestinationWidth > 0 )
    {
      v20 = (char *)pxDestination + 3;
      v21 = v16;
      v22 = v15 - (unsigned __int8 *)v16;
      do
      {
        if ( v19 >= nWidth || v18 >= nHeight )
        {
          *v20 = 0;
          *(v20 - 1) = 0;
          *(v20 - 2) = 0;
          *(v20 - 3) = 0;
        }
        else
        {
          if ( pxSourceAlpha )
            v23 = v21[v22];
          else
            v23 = (*v21 == 0) - 1;
          *v20 = v23;
          *(v20 - 1) = *((_BYTE *)pxSourcePalette + 4 * (unsigned __int8)*v21 + 2);
          *(v20 - 2) = *((_BYTE *)pxSourcePalette + 4 * (unsigned __int8)*v21 + 1);
          *(v20 - 3) = *((_BYTE *)pxSourcePalette + 4 * (unsigned __int8)*v21);
          v18 = (int)pxDestinationa;
        }
        ++v19;
        ++v21;
        v20 += 4;
      }
      while ( v19 < nDestinationWidth );
      v15 = anSourceAlpha;
      v9 = nSourceWidth;
      v14 = pxSourceAlpha;
    }
    if ( v14 )
    {
      v15 += v9;
      anSourceAlpha = v15;
    }
    result = nDestinationHeight;
    v16 += v9;
    ++v18;
    pxDestination = (char *)pxDestination + 4 * nDestinationWidth;
  }
  return result;
}

// source: b/4/textureutility.c:1610  [size]
void __cdecl TextureUtility_FilterARGB8888(
        void *pxDestination,
        void *pxSource,
        int nWidth,
        int nHeight,
        struct TextureFilterContext_s *ptTextureFilterContext)
{
  int v7; // ebx
  int v8; // eax
  char *v9; // eax
  char *v10; // edx
  unsigned __int8 *v11; // ecx
  double v12; // st7
  float vR; // [esp+10h] [ebp-18h]
  float vG; // [esp+18h] [ebp-10h]
  int v15; // [esp+20h] [ebp-8h]
  int v16; // [esp+24h] [ebp-4h]

  TextureUtility_UpdateGammaLookup(ptTextureFilterContext);
  if ( nHeight > 0 )
  {
    v7 = nWidth;
    v8 = (_BYTE *)pxDestination - (_BYTE *)pxSource;
    v16 = (_BYTE *)pxDestination - (_BYTE *)pxSource;
    v15 = nHeight;
    do
    {
      if ( v7 > 0 )
      {
        v9 = (char *)pxSource + v8;
        v10 = v9 + 2;
        v11 = (unsigned __int8 *)pxSource + 1;
        do
        {
          vR = TextureUtility_avGammaLookup[v11[1]] * 0.003921568859368563 * ptTextureFilterContext->tScale.vX
             + ptTextureFilterContext->tAmbientColour.vX;
          vG = TextureUtility_avGammaLookup[*v11] * 0.003921568859368563 * ptTextureFilterContext->tScale.vY
             + ptTextureFilterContext->tAmbientColour.vY;
          v12 = TextureUtility_avGammaLookup[*(v11 - 1)] * 0.003921568859368563 * ptTextureFilterContext->tScale.vZ
              + ptTextureFilterContext->tAmbientColour.vZ;
          if ( vR >= 0.0 )
          {
            if ( vR > 1.0 )
              vR = 1.0;
          }
          else
          {
            vR = 0.0;
          }
          if ( vG >= 0.0 )
          {
            if ( vG > 1.0 )
              vG = 1.0;
          }
          else
          {
            vG = 0.0;
          }
          if ( v12 >= 0.0 )
          {
            if ( v12 > 1.0 )
              v12 = 1.0;
          }
          else
          {
            v12 = 0.0;
          }
          v10[1] = v11[2];
          v11 += 4;
          v10 += 4;
          --v7;
          *(v10 - 4) = (__int64)(vR * 255.0);
          v11[v9 - (_BYTE *)pxSource - 4] = (__int64)(vG * 255.0);
          *(v10 - 6) = (__int64)(255.0 * v12);
        }
        while ( v7 );
        v7 = nWidth;
        v8 = v16;
      }
      pxSource = (char *)pxSource + 4 * v7;
      --v15;
    }
    while ( v15 );
  }
}

// source: b/4/textureutility.c:1671  [size]
void __cdecl TextureUtility_ValidateMacros()
{
  ;
}
