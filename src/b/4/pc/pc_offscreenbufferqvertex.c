/* b/4/pc/pc_offscreenbufferqvertex.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/4/pc/pc_offscreenbufferqvertex.c:79  [anchor-strings]
void __cdecl OffscreenBufferQVertex_RegisterStrip(struct QVertexStripContext_s *ptStripContext)
{
  struct RenderPrimitive_s *p_ptRenderPrimitive; // eax
  struct TexInfo_s *v2; // esi
  bool v3; // zf
  struct PalInfo *v4; // ebx
  int nDepth; // edx
  struct RenderPrimitive_s *v6; // ecx
  struct RenderPrimitive_s ptRenderPrimitive; // [esp+0h] [ebp-8Ch] BYREF

  if ( ptStripContext->nStripLength != 2 )
  {
    LDebug_Error("Strip length not supported.");
    abort();
  }
  if ( ptStripContext->nDepth < 0 )
  {
    p_ptRenderPrimitive = &ptRenderPrimitive;
LABEL_7:
    v2 = QVertex_ptActiveTexture;
    v3 = QVertex_ptActiveTexture == nullptr;
    p_ptRenderPrimitive->ePrimType = QVertex_eStripPrimType;
    v4 = QVertex_ptActivePalette;
    LODWORD(p_ptRenderPrimitive[5].vZ) = ptStripContext->bFlags;
    if ( v3 )
    {
      HIWORD(p_ptRenderPrimitive[6].ptNext) = 0;
    }
    else
    {
      qmemcpy(&p_ptRenderPrimitive[1], v2, 0x2Cu);
      HIWORD(p_ptRenderPrimitive[6].ptNext) = 1;
    }
    if ( v4 )
    {
      LODWORD(p_ptRenderPrimitive[4].vZ) = v4->eRenderMode;
      p_ptRenderPrimitive[5].ptNext = (struct RenderPrimitive_s *)v4->nPalette;
      p_ptRenderPrimitive[5].ePrimType = (int)v4->pxPalette;
      LOWORD(p_ptRenderPrimitive[6].ptNext) = 1;
    }
    else
    {
      LOWORD(p_ptRenderPrimitive[6].ptNext) = 0;
    }
    p_ptRenderPrimitive[6].ePrimType = LODWORD(ptStripContext->atQVertex->vU);
    p_ptRenderPrimitive[6].vZ = ptStripContext->atQVertex->vV;
    p_ptRenderPrimitive[9].ptNext = (struct RenderPrimitive_s *)LODWORD(ptStripContext->atQVertex[1].vU);
    p_ptRenderPrimitive[9].ePrimType = LODWORD(ptStripContext->atQVertex[1].vV);
    p_ptRenderPrimitive[7].ptNext = (struct RenderPrimitive_s *)LODWORD(ptStripContext->atQVertex->vX);
    p_ptRenderPrimitive[7].ePrimType = LODWORD(ptStripContext->atQVertex->vY);
    p_ptRenderPrimitive[8].ptNext = (struct RenderPrimitive_s *)LODWORD(ptStripContext->atQVertex->vR);
    p_ptRenderPrimitive[8].ePrimType = LODWORD(ptStripContext->atQVertex->vG);
    p_ptRenderPrimitive[8].vZ = ptStripContext->atQVertex->vB;
    p_ptRenderPrimitive[9].vZ = ptStripContext->atQVertex->vX;
    p_ptRenderPrimitive[10].ptNext = (struct RenderPrimitive_s *)LODWORD(ptStripContext->atQVertex->vY);
    if ( (LODWORD(p_ptRenderPrimitive[5].vZ) & 0x80000) != 0 )
      p_ptRenderPrimitive[7].vZ = ptStripContext->atQVertex->vA;
    else
      p_ptRenderPrimitive[7].vZ = 1.0;
    nDepth = ptStripContext->nDepth;
    if ( nDepth >= 0 )
    {
      v6 = &RenderContext_tActiveRenderContext.ptRenderPrimitive_[nDepth];
      p_ptRenderPrimitive->ptNext = v6->ptNext;
      v6->ptNext = p_ptRenderPrimitive;
    }
    else
    {
      Primitive_Draw(p_ptRenderPrimitive);
    }
    return;
  }
  p_ptRenderPrimitive = (struct RenderPrimitive_s *)Primitive_ptNextFreePrimitive;
  Primitive_ptNextFreePrimitive = (char *)Primitive_ptNextFreePrimitive + 140;
  if ( (char *)Primitive_ptNextFreePrimitive - Primitive_asPrimitive[0] <= (char *)Primitive_nMaxPrimitiveUsage
    || (Primitive_nMaxPrimitiveUsage = (unsigned int)Primitive_ptNextFreePrimitive - Primitive_asPrimitive[0],
        (char *)Primitive_ptNextFreePrimitive - Primitive_asPrimitive[0] <= (char *)dword_6B9E3C) )
  {
    if ( p_ptRenderPrimitive )
      goto LABEL_7;
  }
}

// source: b/4/pc/pc_offscreenbufferqvertex.c:179  [anchor-mhash]
void __cdecl OffscreenBufferQVertex_RenderNoTexture(struct OffscreenBufferStrip_s *ptPrim)
{
  struct OffscreenBufferStrip_s *v1; // esi
  signed int y; // eax
  char *v3; // edx
  int v4; // ecx
  double a; // st7
  int v6; // edi
  int v7; // ecx
  signed int v8; // edi
  unsigned int v9; // eax
  int v10; // ebx
  int v11; // edi
  int v12; // esi
  unsigned int v13; // eax
  int v14; // eax
  bool v15; // cc
  float vOMA; // [esp+Ch] [ebp-3Ch]
  int vY; // [esp+10h] [ebp-38h]
  int nStartX; // [esp+14h] [ebp-34h]
  signed int vX; // [esp+18h] [ebp-30h]
  int v20; // [esp+1Ch] [ebp-2Ch]
  int nY; // [esp+20h] [ebp-28h]
  int v22; // [esp+24h] [ebp-24h]
  int nClipYEnd; // [esp+28h] [ebp-20h]
  int nClipXEnd; // [esp+2Ch] [ebp-1Ch]
  unsigned int nSR; // [esp+38h] [ebp-10h]
  unsigned int nSG; // [esp+3Ch] [ebp-Ch]
  __int64 nSB; // [esp+40h] [ebp-8h]

  v1 = ptPrim;
  if ( OffscreenBuffer_tActiveOffscreenBuffer.pxBuffer )
  {
    y = (__int64)ptPrim->v1.y;
    v3 = (char *)OffscreenBuffer_tActiveOffscreenBuffer.pxBuffer
       + 4 * (__int64)ptPrim->v1.x
       + 4 * y * OffscreenBuffer_tActiveOffscreenBuffer.nWidth;
    nStartX = (__int64)ptPrim->v1.x;
    vX = (__int64)OffscreenBuffer_tActiveClippingRect.vX;
    vY = (__int64)OffscreenBuffer_tActiveClippingRect.vY;
    nClipXEnd = vX + (__int64)OffscreenBuffer_tActiveClippingRect.vWidth;
    nClipYEnd = vY + (__int64)OffscreenBuffer_tActiveClippingRect.vHeight;
    if ( nStartX < nClipXEnd
      && y < (int)(vY + (__int64)OffscreenBuffer_tActiveClippingRect.vHeight)
      && (int)(nStartX + (__int64)ptPrim->v2.x) >= vX )
    {
      v4 = (__int64)ptPrim->v2.y;
      if ( v4 + y >= vY )
      {
        a = ptPrim->v1.a;
        nY = 0;
        vOMA = 1.0 - a;
        nSR = (__int64)(a * ptPrim->v1.r * 255.0);
        nSG = (__int64)(a * ptPrim->v1.g * 255.0);
        nSB = (__int64)(a * ptPrim->v1.b * 255.0);
        if ( v4 > 0 )
        {
          v6 = (__int64)ptPrim->v1.y;
          v22 = v6;
          do
          {
            if ( v6 >= vY && v6 < nClipYEnd )
            {
              v7 = 0;
              if ( v1->v2.x > 0.0 )
              {
                v8 = nStartX;
                v20 = nStartX;
                do
                {
                  if ( v8 >= vX && v8 < nClipXEnd )
                  {
                    v9 = nSR + (__int64)((double)(unsigned __int8)v3[4 * v7 + 2] * vOMA);
                    v10 = (__int64)((double)(unsigned __int8)*(_DWORD *)&v3[4 * v7] * vOMA);
                    if ( v9 > 0xFF )
                      LOBYTE(v9) = -1;
                    v11 = 255;
                    if ( nSG + (unsigned int)(__int64)((double)(unsigned __int8)v3[4 * v7 + 1] * vOMA) <= 0xFF )
                      v11 = nSG + (__int64)((double)(unsigned __int8)v3[4 * v7 + 1] * vOMA);
                    v12 = v10 + nSB;
                    if ( (unsigned int)(v10 + nSB) > 0xFF )
                      v12 = 255;
                    v13 = v11 | ((v9 | 0xFFFFFF00) << 8);
                    v8 = v20;
                    v14 = v12 | (v13 << 8);
                    v1 = ptPrim;
                    *(_DWORD *)&v3[4 * v7] = v14;
                  }
                  ++v7;
                  v20 = ++v8;
                }
                while ( (double)v7 < v1->v2.x );
                v6 = v22;
              }
            }
            v3 += 4 * OffscreenBuffer_tActiveOffscreenBuffer.nWidth;
            ++v6;
            v15 = ++nY < (__int64)v1->v2.y;
            v22 = v6;
          }
          while ( v15 );
        }
      }
    }
  }
}

// source: b/4/pc/pc_offscreenbufferqvertex.c:257  [anchor-strings]
void __cdecl OffscreenBufferQVertex_RenderTextured(struct OffscreenBufferStrip_s *ptPrim)
{
  double v1; // st7
  double v2; // st6
  int v3; // edx
  int v4; // eax
  int y; // esi
  _WORD *pxPalette; // edx
  int v7; // eax
  int v8; // ebx
  unsigned __int8 *v9; // esi
  int v10; // edi
  int v11; // eax
  int v12; // eax
  int v13; // eax
  bool v14; // cc
  char *v15; // ebx
  int v16; // esi
  int v17; // edx
  char *v18; // edi
  double v19; // st7
  double v20; // st7
  double v21; // st6
  double v22; // st5
  double v23; // st7
  int v24; // edx
  double v25; // st7
  double v26; // st7
  bool v27; // zf
  int v28; // eax
  int v29; // edi
  int v30; // esi
  unsigned int v31; // edx
  unsigned int v32; // eax
  int v33; // edx
  unsigned int v34; // edx
  unsigned int v35; // eax
  int v36; // edx
  unsigned int v37; // edx
  unsigned int v38; // eax
  int v39; // edx
  unsigned int v40; // edx
  unsigned int v41; // eax
  int v42; // edx
  int v43; // ebx
  unsigned int v44; // edx
  unsigned __int16 *v45; // esi
  unsigned int v46; // eax
  int v47; // eax
  int vX; // [esp+10h] [ebp-48h]
  int nClipXEnd; // [esp+14h] [ebp-44h]
  unsigned int *anBuffer; // [esp+18h] [ebp-40h]
  float anBuffera; // [esp+18h] [ebp-40h]
  int isRealColour; // [esp+1Ch] [ebp-3Ch]
  int isRealColoura; // [esp+1Ch] [ebp-3Ch]
  unsigned __int16 *anData; // [esp+20h] [ebp-38h]
  unsigned __int16 *anDataa; // [esp+20h] [ebp-38h]
  int vAlpha; // [esp+24h] [ebp-34h]
  float vAlphaa; // [esp+24h] [ebp-34h]
  float vAlphab; // [esp+24h] [ebp-34h]
  unsigned int *vAlphac; // [esp+24h] [ebp-34h]
  int nStartU; // [esp+28h] [ebp-30h]
  int nStartUa; // [esp+28h] [ebp-30h]
  int nWidth; // [esp+2Ch] [ebp-2Ch]
  unsigned __int8 *nWidtha; // [esp+2Ch] [ebp-2Ch]
  int vY; // [esp+30h] [ebp-28h]
  int nStartX; // [esp+34h] [ebp-24h]
  int nClipYEnd; // [esp+38h] [ebp-20h]
  int nY; // [esp+3Ch] [ebp-1Ch]
  char *nYa; // [esp+3Ch] [ebp-1Ch]
  int nYb; // [esp+3Ch] [ebp-1Ch]
  int nX; // [esp+40h] [ebp-18h]
  int nXa; // [esp+40h] [ebp-18h]
  int nXb; // [esp+40h] [ebp-18h]
  int nXc; // [esp+40h] [ebp-18h]
  unsigned __int16 *nXd; // [esp+40h] [ebp-18h]
  float vSG; // [esp+44h] [ebp-14h]
  int vSGa; // [esp+44h] [ebp-14h]
  int vSGb; // [esp+44h] [ebp-14h]
  float vB; // [esp+48h] [ebp-10h]

  if ( OffscreenBuffer_tActiveOffscreenBuffer.pxBuffer )
  {
    vAlpha = ptPrim->tTexInfo.nHeight;
    v1 = (double)ptPrim->tTexInfo.nWidth;
    nStartU = (__int64)(v1 * ptPrim->v1.u);
    v2 = (double)vAlpha;
    *(float *)&nX = v2;
    v3 = (__int64)(v2 * ptPrim->v1.v);
    nWidth = (__int64)(v1 * ptPrim->v2.u) - nStartU;
    v4 = (__int64)(*(float *)&nX * ptPrim->v2.v) - v3;
    y = (__int64)ptPrim->v1.y;
    nStartX = (__int64)ptPrim->v1.x;
    anBuffer = (unsigned int *)((char *)OffscreenBuffer_tActiveOffscreenBuffer.pxBuffer
                              + 4 * nStartX
                              + 4 * y * OffscreenBuffer_tActiveOffscreenBuffer.nWidth);
    vX = (__int64)OffscreenBuffer_tActiveClippingRect.vX;
    vY = (__int64)OffscreenBuffer_tActiveClippingRect.vY;
    nClipXEnd = vX + (__int64)OffscreenBuffer_tActiveClippingRect.vWidth;
    nClipYEnd = vY + (__int64)OffscreenBuffer_tActiveClippingRect.vHeight;
    if ( nStartX < nClipXEnd && y < nClipYEnd && nWidth + nStartX >= vX && y + v4 >= vY )
    {
      if ( LODWORD(ptPrim->v1.r) != 1065353216
        || LODWORD(ptPrim->v1.g) != 1065353216
        || (isRealColour = 1, LODWORD(ptPrim->v1.b) != 1065353216) )
      {
        isRealColour = 0;
      }
      if ( ptPrim->isPalette )
      {
        pxPalette = ptPrim->tPalInfo.pxPalette;
        nWidtha = (unsigned __int8 *)ptPrim->tTexInfo.pxData;
        nStartUa = (int)pxPalette;
        nY = 0;
        if ( vAlpha > 0 )
        {
          v7 = ptPrim->tTexInfo.nWidth;
          nXa = (__int64)ptPrim->v1.y;
          do
          {
            if ( y >= vY && y < nClipYEnd )
            {
              v8 = 0;
              if ( v7 > 0 )
              {
                v9 = nWidtha;
                v10 = nStartX - (_DWORD)nWidtha;
                do
                {
                  if ( (int)&v9[v10] >= vX && (int)&v9[v10] < nClipXEnd )
                  {
                    v11 = *v9;
                    if ( isRealColour )
                    {
                      v12 = (unsigned __int16)pxPalette[v11];
                    }
                    else
                    {
                      v13 = (__int64)((double)(pxPalette[v11] & 0x1F) * ptPrim->v1.b)
                          | ((((unsigned int)(__int64)((double)(pxPalette[v11] >> 11) * ptPrim->v1.r) << 9)
                            | (unsigned int)(__int64)((double)(((unsigned __int16)pxPalette[v11] >> 5) & 0x3F)
                                                    * ptPrim->v1.g)) << 7);
                      pxPalette = (_WORD *)nStartUa;
                      v12 = 8 * v13;
                    }
                    anBuffer[v8] = v12 | 0xFF000000;
                    v10 = nStartX - (_DWORD)nWidtha;
                  }
                  v7 = ptPrim->tTexInfo.nWidth;
                  ++v8;
                  ++v9;
                }
                while ( v8 < v7 );
                y = nXa;
              }
            }
            anBuffer += OffscreenBuffer_tActiveOffscreenBuffer.nWidth;
            nWidtha += ptPrim->tTexInfo.nPitch;
            ++y;
            v14 = ++nY < ptPrim->tTexInfo.nHeight;
            nXa = y;
          }
          while ( v14 );
        }
      }
      else if ( ptPrim->tTexInfo.nType == 2 )
      {
        anDataa = (unsigned __int16 *)((char *)ptPrim->tTexInfo.pxData
                                     + 2 * ((unsigned int)(v3 * ptPrim->tTexInfo.nPitch) >> 1));
        if ( v4 > 0 )
        {
          nYb = (__int64)ptPrim->v1.y;
          vSGb = (__int64)(*(float *)&nX * ptPrim->v2.v) - v3;
          do
          {
            if ( nYb >= vY && nYb < nClipYEnd )
            {
              v28 = nWidth;
              v29 = 0;
              nXc = 0;
              if ( nWidth >= 4 )
              {
                vAlphac = anBuffer + 2;
                nXd = &anDataa[nStartU];
                v30 = nStartX + 1;
                do
                {
                  HIWORD(v31) = HIWORD(vX);
                  if ( v30 - 1 >= vX && v30 - 1 < nClipXEnd )
                  {
                    LOWORD(v31) = *nXd;
                    if ( (HIBYTE(*nXd) & 0x80u) != 0 )
                    {
                      if ( isRealColour )
                      {
                        v32 = 8 * (v31 & 0x3E0 | (8 * (v31 & 0x7C00)));
                        v33 = v31 & 0x1F;
                      }
                      else
                      {
                        v32 = (((unsigned int)(__int64)((double)((v31 >> 10) & 0x1F) * ptPrim->v1.r) << 8)
                             | (unsigned int)(__int64)((double)((v31 >> 5) & 0x1F) * ptPrim->v1.g)) << 8;
                        v33 = (__int64)((double)(v31 & 0x1F) * ptPrim->v1.b);
                      }
                      *(vAlphac - 2) = (8 * (v33 | v32)) | 0xFF000000;
                    }
                  }
                  if ( v30 >= vX && v30 < nClipXEnd )
                  {
                    HIWORD(v34) = HIWORD(anDataa);
                    LOWORD(v34) = anDataa[v29 + 1 + nStartU];
                    if ( (v34 & 0x8000) != 0 )
                    {
                      if ( isRealColour )
                      {
                        v35 = 8 * (v34 & 0x3E0 | (8 * (v34 & 0x7C00)));
                        v36 = v34 & 0x1F;
                      }
                      else
                      {
                        v35 = (((unsigned int)(__int64)((double)((v34 >> 10) & 0x1F) * ptPrim->v1.r) << 8)
                             | (unsigned int)(__int64)((double)((v34 >> 5) & 0x1F) * ptPrim->v1.g)) << 8;
                        v36 = (__int64)((double)(v34 & 0x1F) * ptPrim->v1.b);
                      }
                      *(vAlphac - 1) = (8 * (v36 | v35)) | 0xFF000000;
                    }
                  }
                  if ( v30 + 1 >= vX && v30 + 1 < nClipXEnd )
                  {
                    HIWORD(v37) = HIWORD(anDataa);
                    LOWORD(v37) = anDataa[v29 + 2 + nStartU];
                    if ( (v37 & 0x8000) != 0 )
                    {
                      if ( isRealColour )
                      {
                        v38 = 8 * (v37 & 0x3E0 | (8 * (v37 & 0x7C00)));
                        v39 = v37 & 0x1F;
                      }
                      else
                      {
                        v38 = (((unsigned int)(__int64)((double)((v37 >> 10) & 0x1F) * ptPrim->v1.r) << 8)
                             | (unsigned int)(__int64)((double)((v37 >> 5) & 0x1F) * ptPrim->v1.g)) << 8;
                        v39 = (__int64)((double)(v37 & 0x1F) * ptPrim->v1.b);
                      }
                      *vAlphac = (8 * (v39 | v38)) | 0xFF000000;
                    }
                  }
                  if ( v30 + 2 >= vX && v30 + 2 < nClipXEnd )
                  {
                    HIWORD(v40) = HIWORD(anDataa);
                    LOWORD(v40) = anDataa[v29 + 3 + nStartU];
                    if ( (v40 & 0x8000) != 0 )
                    {
                      if ( isRealColour )
                      {
                        v41 = 8 * (v40 & 0x3E0 | (8 * (v40 & 0x7C00)));
                        v42 = v40 & 0x1F;
                      }
                      else
                      {
                        v41 = (((unsigned int)(__int64)((double)((v40 >> 10) & 0x1F) * ptPrim->v1.r) << 8)
                             | (unsigned int)(__int64)((double)((v40 >> 5) & 0x1F) * ptPrim->v1.g)) << 8;
                        v42 = (__int64)((double)(v40 & 0x1F) * ptPrim->v1.b);
                      }
                      vAlphac[1] = (8 * (v42 | v41)) | 0xFF000000;
                    }
                  }
                  vAlphac += 4;
                  v30 += 4;
                  v28 = nWidth;
                  v29 += 4;
                  nXd += 4;
                }
                while ( 2 - nStartX + v30 < nWidth );
                nXc = v29;
              }
              if ( v29 < v28 )
              {
                v43 = v29 + nStartX;
                HIWORD(v44) = HIWORD(anDataa);
                v45 = &anDataa[v29 + nStartU];
                do
                {
                  if ( v43 >= vX && v43 < nClipXEnd )
                  {
                    LOWORD(v44) = *v45;
                    if ( (HIBYTE(*v45) & 0x80u) != 0 )
                    {
                      if ( isRealColour )
                      {
                        v46 = 8 * (v44 & 0x3E0 | (8 * (v44 & 0x7C00)));
                        v44 &= 0x1Fu;
                      }
                      else
                      {
                        v46 = (((unsigned int)(__int64)((double)((v44 >> 10) & 0x1F) * ptPrim->v1.r) << 8)
                             | (unsigned int)(__int64)((double)((v44 >> 5) & 0x1F) * ptPrim->v1.g)) << 8;
                        v44 = (__int64)((double)(v44 & 0x1F) * ptPrim->v1.b);
                      }
                      v29 = nXc;
                      v47 = v44 | v46;
                      HIWORD(v44) = HIWORD(anBuffer);
                      anBuffer[nXc] = (8 * v47) | 0xFF000000;
                    }
                  }
                  ++v29;
                  ++v45;
                  ++v43;
                  nXc = v29;
                }
                while ( v29 < nWidth );
              }
            }
            anBuffer += OffscreenBuffer_tActiveOffscreenBuffer.nWidth;
            anDataa += (unsigned int)ptPrim->tTexInfo.nPitch >> 1;
            v27 = vSGb == 1;
            ++nYb;
            --vSGb;
          }
          while ( !v27 );
        }
      }
      else
      {
        if ( ptPrim->tTexInfo.nType != 3 )
        {
          LDebug_Error("OffscreenBufferSprite_RenderSprite() : Texture type not supported.");
          abort();
        }
        nYa = (char *)ptPrim->tTexInfo.pxData + 4 * ((unsigned int)(v3 * ptPrim->tTexInfo.nPitch) >> 2);
        if ( v4 > 0 )
        {
          v15 = (char *)OffscreenBuffer_tActiveOffscreenBuffer.pxBuffer
              + 4 * nStartX
              + 4 * y * OffscreenBuffer_tActiveOffscreenBuffer.nWidth;
          anData = (unsigned __int16 *)(__int64)ptPrim->v1.y;
          isRealColoura = (__int64)(*(float *)&nX * ptPrim->v2.v) - v3;
          do
          {
            if ( (int)anData >= vY && (int)anData < nClipYEnd )
            {
              v16 = 0;
              if ( nWidth > 0 )
              {
                v17 = nStartX;
                nXb = nStartX;
                v18 = &nYa[4 * nStartU + 2];
                do
                {
                  if ( v17 >= vX && v17 < nClipXEnd )
                  {
                    v19 = (double)(unsigned __int8)v18[1] * 0.003921568859368563;
                    vAlphaa = v19;
                    if ( v19 != 0.0 )
                    {
                      v20 = 1.0 - vAlphaa;
                      v21 = (double)(unsigned __int8)*v18 * ptPrim->v1.r * vAlphaa * 0.003921568859368563;
                      anBuffera = (double)(unsigned __int8)*(v18 - 1) * ptPrim->v1.g * vAlphaa * 0.003921568859368563;
                      vB = (double)(unsigned __int8)*(_DWORD *)(v18 - 2) * ptPrim->v1.b * vAlphaa * 0.003921568859368563;
                      vSG = (double)(unsigned __int8)v15[4 * v16 + 1] * v20 * 0.003921568859368563;
                      vAlphab = (double)(unsigned __int8)*(_DWORD *)&v15[4 * v16] * v20 * 0.003921568859368563;
                      v22 = (double)(unsigned __int8)v15[4 * v16 + 2] * v20 * 0.003921568859368563 + v21;
                      v23 = v22;
                      if ( v22 >= 0.0 )
                      {
                        if ( v22 > 1.0 )
                          v23 = 1.0;
                      }
                      else
                      {
                        v23 = 0.0;
                      }
                      v24 = (__int64)(255.0 * v23);
                      v25 = vSG + anBuffera;
                      if ( v25 >= 0.0 )
                      {
                        if ( v25 > 1.0 )
                          v25 = 1.0;
                      }
                      else
                      {
                        v25 = 0.0;
                      }
                      vSGa = (__int64)(255.0 * v25);
                      v26 = vAlphab + vB;
                      if ( v26 >= 0.0 )
                      {
                        if ( v26 > 1.0 )
                          v26 = 1.0;
                      }
                      else
                      {
                        v26 = 0.0;
                      }
                      *(_DWORD *)&v15[4 * v16] = (__int64)(255.0 * v26) | ((vSGa | ((v24 | 0xFFFFFF00) << 8)) << 8);
                      v17 = nXb;
                    }
                  }
                  ++v16;
                  ++v17;
                  v18 += 4;
                  nXb = v17;
                }
                while ( v16 < nWidth );
              }
            }
            v15 += 4 * OffscreenBuffer_tActiveOffscreenBuffer.nWidth;
            nYa += 4 * ((unsigned int)ptPrim->tTexInfo.nPitch >> 2);
            v27 = isRealColoura == 1;
            anData = (unsigned __int16 *)((char *)anData + 1);
            --isRealColoura;
          }
          while ( !v27 );
        }
      }
    }
  }
}

// source: b/4/pc/pc_offscreenbufferqvertex.c:510  [anchor-mhash]
void __cdecl OffscreenBufferQVertex_DrawStrip(struct OffscreenBufferStrip_s *ptStrip)
{
  if ( ptStrip )
  {
    if ( ptStrip->isTextured )
      OffscreenBufferQVertex_RenderTextured(ptStrip);
    else
      OffscreenBufferQVertex_RenderNoTexture(ptStrip);
  }
}

// source: b/4/pc/pc_offscreenbufferqvertex.c:536  [anchor-hash]
void __cdecl OffscreenBufferQVertex_Open()
{
  __int32 v0; // eax

  v0 = QVertex_eStripPrimType + 130 * dword_73D31C;
  RenderMode_atRenderMode[dword_73D31C].apfRenderModeMethod[QVertex_eRegisterQVertexStripMethod] = (void (__cdecl *)(void *))OffscreenBufferQVertex_RegisterStrip;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v0] = (void (__cdecl *)(void *))OffscreenBufferQVertex_DrawStrip;
}

// source: b/4/pc/pc_offscreenbufferqvertex.c:558  [size]
void __cdecl OffscreenBufferQVertex_Close()
{
  ;
}
