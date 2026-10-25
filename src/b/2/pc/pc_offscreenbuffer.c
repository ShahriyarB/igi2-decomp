/* b/2/pc/pc_offscreenbuffer.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/2/pc/pc_offscreenbuffer.c:48  [anchor-mhash]
void __cdecl OffscreenBuffer_SetClippingWindow(struct DisplaySetClippingWindowContext_s *ptClippingWindow)
{
  double nWidth; // st7
  double nHeight; // st7
  double v3; // st7
  double v4; // st7

  if ( ptClippingWindow->tClippingRect.vX >= 0.0 )
  {
    nWidth = (double)OffscreenBuffer_tActiveOffscreenBuffer.nWidth;
    if ( nWidth >= ptClippingWindow->tClippingRect.vX )
      OffscreenBuffer_tActiveClippingRect.vX = ptClippingWindow->tClippingRect.vX;
    else
      OffscreenBuffer_tActiveClippingRect.vX = nWidth;
  }
  else
  {
    OffscreenBuffer_tActiveClippingRect.vX = 0.0;
  }
  if ( ptClippingWindow->tClippingRect.vY >= 0.0 )
  {
    nHeight = (double)OffscreenBuffer_tActiveOffscreenBuffer.nHeight;
    if ( nHeight >= ptClippingWindow->tClippingRect.vY )
      OffscreenBuffer_tActiveClippingRect.vY = ptClippingWindow->tClippingRect.vY;
    else
      OffscreenBuffer_tActiveClippingRect.vY = nHeight;
  }
  else
  {
    OffscreenBuffer_tActiveClippingRect.vY = 0.0;
  }
  if ( ptClippingWindow->tClippingRect.vX <= (double)ptClippingWindow->tClippingRect.vWidth )
  {
    v3 = (double)OffscreenBuffer_tActiveOffscreenBuffer.nWidth - ptClippingWindow->tClippingRect.vX;
    if ( v3 >= ptClippingWindow->tClippingRect.vWidth )
      OffscreenBuffer_tActiveClippingRect.vWidth = ptClippingWindow->tClippingRect.vWidth;
    else
      OffscreenBuffer_tActiveClippingRect.vWidth = v3;
  }
  else
  {
    OffscreenBuffer_tActiveClippingRect.vWidth = ptClippingWindow->tClippingRect.vX;
  }
  if ( ptClippingWindow->tClippingRect.vY <= (double)ptClippingWindow->tClippingRect.vHeight )
  {
    v4 = (double)OffscreenBuffer_tActiveOffscreenBuffer.nHeight - ptClippingWindow->tClippingRect.vY;
    if ( v4 >= ptClippingWindow->tClippingRect.vHeight )
      OffscreenBuffer_tActiveClippingRect.vHeight = ptClippingWindow->tClippingRect.vHeight;
    else
      OffscreenBuffer_tActiveClippingRect.vHeight = v4;
  }
  else
  {
    OffscreenBuffer_tActiveClippingRect.vHeight = ptClippingWindow->tClippingRect.vY;
  }
}

// source: b/2/pc/pc_offscreenbuffer.c:66  [size]
void __cdecl OffscreenBuffer_SwapBuffers(void *pxUnused)
{
  ;
}

// source: b/2/pc/pc_offscreenbuffer.c:78  [anchor-hash]
int __cdecl OffscreenBuffer_Open(void *pxUnused)
{
  OffscreenBuffer_tActiveOffscreenBuffer.nWidth = 0;
  OffscreenBuffer_tActiveOffscreenBuffer.nHeight = 0;
  memset(&OffscreenBuffer_tActiveClippingRect, 0, sizeof(OffscreenBuffer_tActiveClippingRect));
  OffscreenBuffer_tActiveOffscreenBuffer.pxBuffer = nullptr;
  return 1;
}

// source: b/2/pc/pc_offscreenbuffer.c:96  [size]
void __cdecl OffscreenBuffer_Close(void *pxUnused)
{
  ;
}

// source: b/2/pc/pc_offscreenbuffer.c:110  [anchor-hash]
void __cdecl OffscreenBuffer_Clear(void *pxUnused)
{
  int v1; // edx
  int nWidth; // ecx
  int v3; // eax

  v1 = 0;
  if ( OffscreenBuffer_tActiveOffscreenBuffer.nHeight > 0 )
  {
    nWidth = OffscreenBuffer_tActiveOffscreenBuffer.nWidth;
    do
    {
      v3 = 0;
      if ( nWidth > 0 )
      {
        do
        {
          *((_DWORD *)OffscreenBuffer_tActiveOffscreenBuffer.pxBuffer + v3 + v1 * nWidth) = -16777216;
          nWidth = OffscreenBuffer_tActiveOffscreenBuffer.nWidth;
          ++v3;
        }
        while ( v3 < OffscreenBuffer_tActiveOffscreenBuffer.nWidth );
      }
      ++v1;
    }
    while ( v1 < OffscreenBuffer_tActiveOffscreenBuffer.nHeight );
  }
}

// source: b/2/pc/pc_offscreenbuffer.c:136  [anchor-mhash]
void __cdecl OffscreenBuffer_Blit(struct DisplayBlitContext_s *ptDisplayBlitContext)
{
  struct DisplayBlitContext_s *v1; // eax
  int nDestinationWidth; // edx
  int v3; // ecx
  int nDestinationHeight; // esi
  int v5; // edx
  char *pxSourceBuffer; // ebp
  char *v7; // ebx
  bool v8; // zf
  int v9; // [esp+10h] [ebp-8h]

  v1 = ptDisplayBlitContext;
  nDestinationWidth = ptDisplayBlitContext->nDestinationWidth;
  if ( nDestinationWidth >= 0 )
  {
    v3 = OffscreenBuffer_tActiveOffscreenBuffer.nWidth - ptDisplayBlitContext->nDestinationX;
    if ( v3 >= nDestinationWidth )
      v3 = ptDisplayBlitContext->nDestinationWidth;
  }
  else
  {
    v3 = 0;
  }
  nDestinationHeight = ptDisplayBlitContext->nDestinationHeight;
  if ( nDestinationHeight >= 0 )
  {
    v5 = OffscreenBuffer_tActiveOffscreenBuffer.nHeight - ptDisplayBlitContext->nDestinationY;
    if ( v5 >= nDestinationHeight )
      v5 = ptDisplayBlitContext->nDestinationHeight;
  }
  else
  {
    v5 = 0;
  }
  pxSourceBuffer = (char *)ptDisplayBlitContext->pxSourceBuffer;
  v7 = (char *)OffscreenBuffer_tActiveOffscreenBuffer.pxBuffer
     + 4 * ptDisplayBlitContext->nDestinationX
     + 4 * OffscreenBuffer_tActiveOffscreenBuffer.nWidth * ptDisplayBlitContext->nDestinationY;
  if ( v5 > 0 )
  {
    v9 = v5;
    while ( 1 )
    {
      qmemcpy(v7, pxSourceBuffer, 4 * v3);
      pxSourceBuffer += 4 * (v1->nSourceModulo / 4);
      v8 = v9 == 1;
      v7 += 4 * OffscreenBuffer_tActiveOffscreenBuffer.nWidth;
      --v9;
      if ( v8 )
        break;
      v1 = ptDisplayBlitContext;
    }
  }
}

// source: b/2/pc/pc_offscreenbuffer.c:173  [anchor-hash]
void __cdecl OffscreenBuffer_New()
{
  unsigned __int32 v0; // eax
  int v1; // ecx
  unsigned __int32 v2; // edx
  int v3; // ecx
  unsigned __int32 v4; // edx
  int v5; // ecx
  unsigned __int32 v6; // edx
  int v7; // ecx
  unsigned __int32 v8; // edx
  unsigned __int32 v9; // eax

  dword_73D31C = RenderMode_New("OffscreenBuffer");
  v0 = 130 * dword_73D31C;
  v1 = Display_eCloseMethod;
  RenderMode_atRenderMode[v0 / 0x82].apfRenderModeMethod[Display_eOpenMethod] = (void (__cdecl *)(void *))OffscreenBuffer_Open;
  v2 = v0 + v1;
  v3 = Display_eClearMethod;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v2] = (void (__cdecl *)(void *))OffscreenBuffer_Close;
  v4 = v0 + v3;
  v5 = Display_eSwapBuffersMethod;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v4] = OffscreenBuffer_Clear;
  v6 = v0 + v5;
  v7 = Display_eBlitPrim;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v6] = (void (__cdecl *)(void *))OffscreenBuffer_SwapBuffers;
  v8 = v0 + v7;
  v9 = Display_eClipWindowPrim + v0;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v8] = (void (__cdecl *)(void *))OffscreenBuffer_Blit;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v9] = (void (__cdecl *)(void *))OffscreenBuffer_SetClippingWindow;
  OffscreenBuffer_isInitialised[0] = 1;
}

// source: b/2/pc/pc_offscreenbuffer.c:199  [anchor-hash]
void __cdecl OffscreenBuffer_Delete()
{
  RenderMode_atRenderMode[dword_73D31C].isAllocated = 0;
  OffscreenBuffer_isInitialised[0] = 0;
}

// source: b/2/pc/pc_offscreenbuffer.c:216  [size]
enum RenderMode_enum __cdecl OffscreenBuffer_GetRenderMode()
{
  return dword_73D31C;
}

// source: b/2/pc/pc_offscreenbuffer.c:232  [anchor-mhash]
void __cdecl OffscreenBuffer_Alloc(struct OffscreenBuffer_s *ptOffscreenBuffer, int nWidth, int nHeight)
{
  void *v3; // edi

  v3 = Mem_AllocFn(4 * nHeight * nWidth, 4);
  ptOffscreenBuffer->nWidth = nWidth;
  ptOffscreenBuffer->pxBuffer = v3;
  ptOffscreenBuffer->nHeight = nHeight;
  memset(v3, 0, 4 * ((unsigned int)(4 * nHeight * nWidth) >> 2));
}

// source: b/2/pc/pc_offscreenbuffer.c:253  [anchor-mhash]
void __cdecl OffscreenBuffer_DeAlloc(struct OffscreenBuffer_s *ptOffscreenBuffer)
{
  void *pxBuffer; // eax
  int v2; // esi

  if ( ptOffscreenBuffer->pxBuffer == OffscreenBuffer_tActiveOffscreenBuffer.pxBuffer )
  {
    OffscreenBuffer_tActiveOffscreenBuffer.pxBuffer = nullptr;
    OffscreenBuffer_tActiveOffscreenBuffer.nHeight = 0;
    OffscreenBuffer_tActiveOffscreenBuffer.nWidth = 0;
  }
  pxBuffer = ptOffscreenBuffer->pxBuffer;
  if ( pxBuffer )
  {
    v2 = *(_DWORD *)(((int)pxBuffer - 4) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v2);
    memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
    free((void *)v2);
  }
  ptOffscreenBuffer->pxBuffer = nullptr;
}

// source: b/2/pc/pc_offscreenbuffer.c:277  [anchor-hash]
struct OffscreenBuffer_s *__cdecl OffscreenBuffer_SetActiveOffscreenBuffer(
        struct OffscreenBuffer_s *ptOffscreenBuffer)
{
  OffscreenBuffer_tActiveOffscreenBuffer = *ptOffscreenBuffer;
  OffscreenBuffer_tActiveClippingRect.vX = 0.0;
  OffscreenBuffer_tActiveClippingRect.vY = 0.0;
  OffscreenBuffer_tActiveClippingRect.vWidth = (float)ptOffscreenBuffer->nWidth;
  OffscreenBuffer_tActiveClippingRect.vHeight = (float)ptOffscreenBuffer->nHeight;
  return ptOffscreenBuffer;
}

// source: b/2/pc/pc_offscreenbuffer.c:300  [anchor-mhash]
void __cdecl OffscreenBuffer_PutPixel(int nX, int nY, int nR, int nG, int nB)
{
  double v5; // st7
  double v6; // st7

  v5 = (double)nX;
  if ( v5 > OffscreenBuffer_tActiveClippingRect.vX
    && v5 < OffscreenBuffer_tActiveClippingRect.vWidth + OffscreenBuffer_tActiveClippingRect.vX )
  {
    v6 = (double)nY;
    if ( v6 > OffscreenBuffer_tActiveClippingRect.vY
      && v6 < OffscreenBuffer_tActiveClippingRect.vHeight + OffscreenBuffer_tActiveClippingRect.vY )
    {
      *((_DWORD *)OffscreenBuffer_tActiveOffscreenBuffer.pxBuffer
      + nX
      + nY * OffscreenBuffer_tActiveOffscreenBuffer.nWidth) = (nB | ((nG | (nR << 8)) << 8)) & 0xFFFFFF;
    }
  }
}
