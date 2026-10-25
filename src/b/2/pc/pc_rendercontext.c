/* b/2/pc/pc_rendercontext.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/2/pc/pc_rendercontext.c:52  [anchor-mhash]
struct RenderContext_s *__cdecl RenderContext_SetDisplayArea(
        struct RenderContext_s *ptRenderContext,
        struct real32x2_t *ptMin,
        struct real32x2_t *ptMax)
{
  ptRenderContext->tDisplayAreaMin = *ptMin;
  ptRenderContext->tDisplayAreaMax = *ptMax;
  ++RenderContext_nActiveRenderContextTimeStamp;
  return ptRenderContext;
}

// source: b/2/pc/pc_rendercontext.c:93  [size]
int __cdecl RenderContext_IsValid()
{
  return RenderContext_isValid;
}

// source: b/2/pc/pc_rendercontext.c:108  [anchor-hash]
void __cdecl RenderContext_Open()
{
  RenderContext_tDrawList.ptHead = (struct RenderContext_s *)&RenderContext_tDrawList.ptMiddle;
  RenderContext_tDrawList.ptTail = (struct RenderContext_s *)&RenderContext_tDrawList;
  RenderContext_tDrawList.ptMiddle = nullptr;
}

// source: b/2/pc/pc_rendercontext.c:127  [size]
void __cdecl RenderContext_Close()
{
  ;
}

// source: b/2/pc/pc_rendercontext.c:145  [anchor-callee]
struct RenderContext_s *__cdecl RenderContext_Alloc(
        struct RenderContext_s *ptRenderContext,
        int nDepth)
{
  struct RenderContext_s *result; // eax
  int v4; // ecx
  struct RenderPrimitive_s *ptSortRenderPrimitive; // esi
  struct ClippingRect_s tClippingRect; // [esp+8h] [ebp-18h] BYREF

  ptRenderContext->eRenderMode = -1;
  memset(&tClippingRect, 0, 16);
  RenderContext_SetClippingRect(ptRenderContext, &tClippingRect);
  ptRenderContext->nDepth = nDepth;
  ptRenderContext->ptRenderPrimitive_ = (struct RenderPrimitive_s *)Mem_AllocFn(12 * nDepth, 4);
  ptRenderContext->ptSortRenderPrimitive = (struct RenderPrimitive_s *)Mem_AllocFn(12, 4);
  result = (struct RenderContext_s *)ptRenderContext->ptRenderPrimitive_;
  if ( nDepth )
  {
    v4 = nDepth - 1;
    result->ptNext = nullptr;
    result->ptPrev = (struct RenderContext_s *)-1;
    if ( nDepth != 1 )
    {
      do
      {
        result->tClippingWindow.tRenderPrimitive.ptNext = (struct RenderPrimitive_s *)result;
        result->tClippingWindow.tRenderPrimitive.ePrimType = -1;
        result = (struct RenderContext_s *)((char *)result + 12);
        --v4;
      }
      while ( v4 );
    }
  }
  ptSortRenderPrimitive = ptRenderContext->ptSortRenderPrimitive;
  ptSortRenderPrimitive->ePrimType = -1;
  ptSortRenderPrimitive->ptNext = nullptr;
  return result;
}

// source: b/2/pc/pc_rendercontext.c:181  [anchor-callee]
void __cdecl RenderContext_DeAlloc(struct RenderContext_s *ptRenderContext)
{
  struct RenderPrimitive_s *ptSortRenderPrimitive; // eax
  int v2; // esi
  struct RenderPrimitive_s *ptRenderPrimitive; // eax
  int v4; // esi

  ptSortRenderPrimitive = ptRenderContext->ptSortRenderPrimitive;
  if ( ptSortRenderPrimitive )
  {
    v2 = *(_DWORD *)((unsigned int)&ptSortRenderPrimitive[-1].vZ & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v2);
    memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
    free((void *)v2);
  }
  ptRenderPrimitive = ptRenderContext->ptRenderPrimitive_;
  ptRenderContext->ptSortRenderPrimitive = nullptr;
  if ( ptRenderPrimitive )
  {
    v4 = *(_DWORD *)((unsigned int)&ptRenderPrimitive[-1].vZ & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v4);
    memset(*(void **)(v4 + 8), 0xCDu, *(_DWORD *)(v4 + 16));
    free((void *)v4);
  }
  ptRenderContext->ptRenderPrimitive_ = nullptr;
}

// source: b/2/pc/pc_rendercontext.c:199  [anchor-mhash]
struct RenderContext_s *__cdecl RenderContext_SetActiveRenderContext(
        struct RenderContext_s *ptRenderContext,
        int isAddToList)
{
  qmemcpy(&RenderContext_tActiveRenderContext, ptRenderContext, sizeof(RenderContext_tActiveRenderContext));
  ++RenderContext_nActiveRenderContextTimeStamp;
  if ( isAddToList )
  {
    ptRenderContext->ptPrev = nullptr;
    ptRenderContext->ptNext = nullptr;
    return (struct RenderContext_s *)List_AddTail(ptRenderContext, (int)&RenderContext_tDrawList);
  }
  return ptRenderContext;
}

// source: b/2/pc/pc_rendercontext.c:231  [size]
int __cdecl RenderContext_GetActiveRenderContextTimeStamp()
{
  return RenderContext_nActiveRenderContextTimeStamp;
}

// source: b/2/pc/pc_rendercontext.c:246  [size]
void __cdecl RenderContext_InvalidateActiveRenderContext()
{
  ;
}

// source: b/2/pc/pc_rendercontext.c:267  [anchor-callee]
struct RenderContext_s *__cdecl RenderContext_SetClippingRect(
        struct RenderContext_s *ptRenderContext,
        struct ClippingRect_s *ptClippingRect)
{
  double v2; // st7
  float vX; // edx
  double vHeight; // st7
  float vY; // ecx
  double v6; // st7
  float tMax; // [esp+8h] [ebp-8h]
  float tMax_4; // [esp+Ch] [ebp-4h]

  ptRenderContext->tClippingWindow.tClippingRect.vX = ptClippingRect->vX;
  ptRenderContext->tClippingWindow.tClippingRect.vY = ptClippingRect->vY;
  ptRenderContext->tClippingWindow.tClippingRect.vWidth = ptClippingRect->vWidth;
  ptRenderContext->tClippingWindow.tClippingRect.vHeight = ptClippingRect->vHeight;
  v2 = ptClippingRect->vWidth * 0.5;
  vX = ptRenderContext->tClippingWindow.tClippingRect.vX;
  RenderContext_ptTestRenderContext = nullptr;
  ptRenderContext->tClippingWindow.tClippingRect.vHalfWidth = v2;
  vHeight = ptClippingRect->vHeight;
  ptRenderContext->tClippingWindow.tRenderPrimitive.ePrimType = Display_eClipWindowPrim;
  vY = ptRenderContext->tClippingWindow.tClippingRect.vY;
  ptRenderContext->tDisplayAreaMin.vX = vX;
  ptRenderContext->tClippingWindow.tClippingRect.vHalfHeight = vHeight * 0.5;
  ptRenderContext->tDisplayAreaMin.vY = vY;
  tMax = ptRenderContext->tClippingWindow.tClippingRect.vWidth + ptRenderContext->tClippingWindow.tClippingRect.vX;
  v6 = ptRenderContext->tClippingWindow.tClippingRect.vHeight;
  ptRenderContext->tDisplayAreaMax.vX = tMax;
  tMax_4 = v6 + ptRenderContext->tClippingWindow.tClippingRect.vY;
  ptRenderContext->tDisplayAreaMax.vY = tMax_4;
  ++RenderContext_nActiveRenderContextTimeStamp;
  return ptRenderContext;
}

// source: b/2/pc/pc_rendercontext.c:300  [anchor-hash]
void __cdecl RenderContext_RenderAll()
{
  struct RenderContext_s *ptHead; // ebx
  struct RenderContext_s *ptNext; // ebp
  bool v2; // zf
  enum RenderMode_enum eRenderMode; // eax
  int nDepth; // ecx
  struct RenderPrimitive_s *ptRenderPrimitive; // eax
  int v6; // ecx

  ptHead = RenderContext_tDrawList.ptHead;
  ptNext = RenderContext_tDrawList.ptHead->ptNext;
  v2 = RenderContext_tDrawList.ptHead->ptNext == nullptr;
  TransContext_isValid = 0;
  if ( !v2 )
  {
    do
    {
      qmemcpy(&RenderContext_tActiveRenderContext, ptHead, sizeof(RenderContext_tActiveRenderContext));
      eRenderMode = ptHead->eRenderMode;
      if ( eRenderMode != -1 )
      {
        v2 = eRenderMode == RenderMode_eActiveRenderMode;
        RenderMode_aeRenderModeStack[--RenderMode_nSP] = RenderMode_eActiveRenderMode;
        if ( !v2 )
        {
          qmemcpy(
            &RenderMode_tActiveRenderMode,
            (void *)(520 * eRenderMode + 139167712),
            sizeof(RenderMode_tActiveRenderMode));
          RenderMode_eActiveRenderMode = eRenderMode;
        }
      }
      if ( ptHead == (struct RenderContext_s *)-12 )
      {
        if ( dword_834E068 )
          RenderMode_tActiveRenderMode.apfRenderModeMethod[*(_DWORD *)(dword_834E068 + 4)](nullptr);
      }
      else
      {
        RenderMode_tActiveRenderMode.apfRenderModeMethod[ptHead->tClippingWindow.tRenderPrimitive.ePrimType](&ptHead->tClippingWindow);
        dword_834E068 = (int)&ptHead->tClippingWindow;
      }
      Primitive_DrawList(&ptHead->ptRenderPrimitive_[ptHead->nDepth - 1]);
      nDepth = ptHead->nDepth;
      ptRenderPrimitive = ptHead->ptRenderPrimitive_;
      if ( nDepth )
      {
        v6 = nDepth - 1;
        ptRenderPrimitive->ptNext = nullptr;
        for ( ptRenderPrimitive->ePrimType = -1; v6; --v6 )
        {
          ptRenderPrimitive[1].ptNext = ptRenderPrimitive;
          ptRenderPrimitive[1].ePrimType = -1;
          ++ptRenderPrimitive;
        }
      }
      if ( ptHead->eRenderMode != -1 )
        RenderMode_PopRenderMode();
      ptHead = ptNext;
      ptNext = ptNext->ptNext;
    }
    while ( ptNext );
  }
  RenderContext_tDrawList.ptHead = (struct RenderContext_s *)&RenderContext_tDrawList.ptMiddle;
  RenderContext_tDrawList.ptTail = (struct RenderContext_s *)&RenderContext_tDrawList;
  RenderContext_tDrawList.ptMiddle = nullptr;
  TransContext_isValid = 0;
}

// source: b/2/pc/pc_rendercontext.c:353  [anchor-hash]
struct RenderPrimitive_s *__cdecl RenderContext_GetRenderPrimitive(int nDepth)
{
  return &RenderContext_tActiveRenderContext.ptRenderPrimitive_[nDepth];
}

// source: b/2/pc/pc_rendercontext.c:379  [anchor-callee]
void __cdecl RenderContext_RegisterClippingWindow(
        struct DisplaySetClippingWindowContext_s *ptClippingWindowContext,
        int nDepth)
{
  struct RenderPrimitive_s *v2; // eax
  struct RenderPrimitive_s *v3; // ecx

  v2 = (struct RenderPrimitive_s *)Primitive_ptNextFreePrimitive;
  Primitive_ptNextFreePrimitive = (char *)Primitive_ptNextFreePrimitive + 36;
  if ( (char *)Primitive_ptNextFreePrimitive - Primitive_asPrimitive[0] > (char *)Primitive_nMaxPrimitiveUsage )
  {
    Primitive_nMaxPrimitiveUsage = (unsigned int)Primitive_ptNextFreePrimitive - Primitive_asPrimitive[0];
    if ( (char *)Primitive_ptNextFreePrimitive - Primitive_asPrimitive[0] > (char *)dword_6B9E3C )
      v2 = nullptr;
  }
  qmemcpy(v2, ptClippingWindowContext, 0x24u);
  v2->ePrimType = Display_eClipWindowPrim;
  v3 = &RenderContext_tActiveRenderContext.ptRenderPrimitive_[nDepth];
  v2->ptNext = v3->ptNext;
  v3->ptNext = v2;
}

// source: b/2/pc/pc_rendercontext.c:400  [anchor-mhash]
void __cdecl RenderContext_RegisterBlit(struct DisplayBlitContext_s *ptDisplayBlitContext, int nDepth)
{
  struct RenderPrimitive_s *v2; // eax
  struct RenderPrimitive_s *v3; // ecx

  v2 = (struct RenderPrimitive_s *)Primitive_ptNextFreePrimitive;
  Primitive_ptNextFreePrimitive = (char *)Primitive_ptNextFreePrimitive + 40;
  if ( (char *)Primitive_ptNextFreePrimitive - Primitive_asPrimitive[0] > (char *)Primitive_nMaxPrimitiveUsage )
  {
    Primitive_nMaxPrimitiveUsage = (unsigned int)Primitive_ptNextFreePrimitive - Primitive_asPrimitive[0];
    if ( (char *)Primitive_ptNextFreePrimitive - Primitive_asPrimitive[0] > (char *)dword_6B9E3C )
      v2 = nullptr;
  }
  qmemcpy(v2, ptDisplayBlitContext, 0x28u);
  v2->ePrimType = Display_eBlitPrim;
  v3 = &RenderContext_tActiveRenderContext.ptRenderPrimitive_[nDepth];
  v2->ptNext = v3->ptNext;
  v3->ptNext = v2;
}
