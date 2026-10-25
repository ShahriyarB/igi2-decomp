/* f/2/fadeout.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: f/2/fadeout.c:56  [anchor-hash]
struct QTask_s *__cdecl FadeOutQTask_Alloc(struct QTask_s *ptQTask)
{
  ptQTask[1].ptNext = nullptr;
  ptQTask[1].ptPrev = nullptr;
  ptQTask[1].tQTaskChildren.ptHead = nullptr;
  ptQTask[1].tQTaskChildren.ptMiddle = (struct QTask_s *)255;
  return (struct QTask_s *)RenderContext_Alloc((struct RenderContext_s *)&ptQTask[1].tQTaskChildren.ptTail, 1);
}

// source: f/2/fadeout.c:78  [anchor-mhash]
void __cdecl FadeOutQTask_StartDraw(struct QTask_s *ptQTask)
{
  struct ClippingRect_s tClip; // [esp+0h] [ebp-18h] BYREF

  tClip.vX = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX;
  tClip.vHeight = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHeight;
  tClip.vY = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vY;
  tClip.vWidth = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vWidth;
  RenderContext_SetClippingRect((struct RenderContext_s *)&ptQTask[1].tQTaskChildren.ptTail, &tClip);
}

// source: f/2/fadeout.c:108  [anchor-callee]
void __cdecl FadeOutQTask_EndDraw(struct FadeOutQTaskData_s *ptData, int nR, int nG, int nB, int nA)
{
  int v5; // ebx
  float vX; // [esp+0h] [ebp-38h]
  float vXa; // [esp+0h] [ebp-38h]
  float vY; // [esp+4h] [ebp-34h]
  float vYa; // [esp+4h] [ebp-34h]
  float vWidth; // [esp+8h] [ebp-30h]
  float vWidtha; // [esp+8h] [ebp-30h]
  float vHeight; // [esp+Ch] [ebp-2Ch]
  float vHeighta; // [esp+Ch] [ebp-2Ch]
  float v14; // [esp+10h] [ebp-28h]
  float vG; // [esp+14h] [ebp-24h]
  float vB; // [esp+18h] [ebp-20h]
  float vR; // [esp+30h] [ebp-8h]

  v5 = (255 - nA) / 2;
  if ( v5 || nR || nG || nB )
  {
    qmemcpy(&RenderContext_tActiveRenderContext, &ptData->tRenderContext, sizeof(RenderContext_tActiveRenderContext));
    ++RenderContext_nActiveRenderContextTimeStamp;
    ptData->tRenderContext.ptPrev = nullptr;
    ptData->tRenderContext.ptNext = nullptr;
    List_AddTail(&ptData->tRenderContext.ptNext, (int)&RenderContext_tDrawList);
    if ( v5 )
    {
      vR = (float)(unsigned __int8)v5;
      vHeight = (float)(__int16)(__int64)ptData->tRenderContext.tClippingWindow.tClippingRect.vHeight;
      vWidth = (float)(__int16)(__int64)ptData->tRenderContext.tClippingWindow.tClippingRect.vWidth;
      vY = (float)(__int16)(__int64)ptData->tRenderContext.tClippingWindow.tClippingRect.vY;
      vX = (float)(__int16)(__int64)ptData->tRenderContext.tClippingWindow.tClippingRect.vX;
      QSprite_RegisterBlank(vX, vY, vWidth, vHeight, vR, vR, vR, 0x10u, 0);
    }
    if ( nR || nG || nB )
    {
      vB = (float)(unsigned __int8)nB;
      vG = (float)(unsigned __int8)nG;
      v14 = (float)(unsigned __int8)nR;
      vHeighta = (float)(__int16)(__int64)ptData->tRenderContext.tClippingWindow.tClippingRect.vHeight;
      vWidtha = (float)(__int16)(__int64)ptData->tRenderContext.tClippingWindow.tClippingRect.vWidth;
      vYa = (float)(__int16)(__int64)ptData->tRenderContext.tClippingWindow.tClippingRect.vY;
      vXa = (float)(__int16)(__int64)ptData->tRenderContext.tClippingWindow.tClippingRect.vX;
      QSprite_RegisterBlank(vXa, vYa, vWidtha, vHeighta, v14, vG, vB, 8u, 0);
    }
  }
}

// source: f/2/fadeout.c:155  [anchor-hash]
void __cdecl FadeOutQTask_DeAlloc(struct QTask_s *ptQTask)
{
  RenderContext_DeAlloc((struct RenderContext_s *)&ptQTask[1].tQTaskChildren.ptTail);
}

// source: f/2/fadeout.c:176  [anchor-mhash]
void __cdecl FadeOut_Register(int nR, int nG, int nB, int nA)
{
  struct FadeOutQTaskData_s *v4; // eax

  v4 = FadeOut_ptActiveQTask;
  FadeOut_ptActiveQTask->nA = (nA * FadeOut_ptActiveQTask->nA) >> 8;
  v4->nR += nR;
  v4->nG += nG;
  v4->nB += nB;
}

// source: f/2/fadeout.c:198  [anchor-mhash]
void __cdecl FadeOutStart_DrawHandler(struct QTask_s *ptQTask)
{
  struct ClippingRect_s ptRenderContext; // [esp+0h] [ebp-18h] BYREF

  ptQTask[1].tQTaskChildren.ptMiddle = (struct QTask_s *)255;
  ptQTask[1].ptNext = nullptr;
  ptQTask[1].ptPrev = nullptr;
  ptQTask[1].tQTaskChildren.ptHead = nullptr;
  ptRenderContext.vX = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX;
  ptRenderContext.vY = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vY;
  ptRenderContext.vWidth = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vWidth;
  FadeOut_ptActiveQTask = (struct FadeOutQTaskData_s *)ptQTask;
  ptRenderContext.vHeight = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHeight;
  RenderContext_SetClippingRect((struct RenderContext_s *)&ptQTask[1].tQTaskChildren.ptTail, &ptRenderContext);
}

// source: f/2/fadeout.c:218  [size]
void __cdecl FadeOutStart_DeleteHandler(struct QTask_s *ptQTask)
{
  RenderContext_DeAlloc((struct RenderContext_s *)&ptQTask[1].tQTaskChildren.ptTail);
}

// source: f/2/fadeout.c:232  [anchor-hash]
void __cdecl FadeOutEnd_DrawHandler(struct QTask_s *ptQTask)
{
  int nB; // esi
  int nG; // edx
  int nR; // ecx

  nB = FadeOut_ptActiveQTask->nB;
  if ( nB >= 255 )
    nB = 255;
  nG = FadeOut_ptActiveQTask->nG;
  if ( nG >= 255 )
    nG = 255;
  nR = FadeOut_ptActiveQTask->nR;
  if ( nR >= 255 )
    nR = 255;
  FadeOutQTask_EndDraw(FadeOut_ptActiveQTask, nR, nG, nB, FadeOut_ptActiveQTask->nA);
  FadeOut_ptActiveQTask = nullptr;
}

// source: f/2/fadeout.c:249  [anchor-hash]
void __cdecl FadeOut_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // ax
  unsigned __int16 v2; // ax
  unsigned __int16 v3; // di
  unsigned __int16 v4; // si
  int v5; // ebx

  BaseQTaskType = QTask_GetBaseQTaskType();
  FadeOut_eFadeOutStartQTaskType = QTask_NewQTaskType("FadeOutStart", 132, BaseQTaskType, 0, 0);
  v1 = QTask_GetBaseQTaskType();
  v2 = QTask_NewQTaskType("FadeOutEnd", 132, v1, 0, 0);
  v3 = FadeOut_eFadeOutStartQTaskType;
  v4 = v2;
  FadeOut_eFadeOutEndQTaskType = v2;
  QTask_LinkQTaskEventHandlerNoContextFn(FadeOut_eFadeOutStartQTaskType, 2, FadeOutStart_DeleteHandler);
  v5 = Screen_eDrawQTaskEvent;
  QTask_LinkQTaskEventHandlerNoContextFn(v3, Screen_eDrawQTaskEvent, FadeOutStart_DrawHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v4, v5, FadeOutEnd_DrawHandler);
  FadeOut_ptActiveQTask = nullptr;
}

// source: f/2/fadeout.c:269  [size]
void __cdecl FadeOut_Close()
{
  QTask_DeleteQTaskType(FadeOut_eFadeOutStartQTaskType);
  QTask_DeleteQTaskType(FadeOut_eFadeOutEndQTaskType);
}

// source: f/2/fadeout.c:283  [anchor-mhash]
struct QTask_s *__cdecl FadeOutStart_New(struct QTask_s *ptParent)
{
  struct QTask_s *v1; // esi

  v1 = QTask_NewFn(ptParent, FadeOut_eFadeOutStartQTaskType, nullptr);
  v1[1].ptNext = nullptr;
  v1[1].ptPrev = nullptr;
  v1[1].tQTaskChildren.ptHead = nullptr;
  v1[1].tQTaskChildren.ptMiddle = (struct QTask_s *)255;
  RenderContext_Alloc((struct RenderContext_s *)&v1[1].tQTaskChildren.ptTail, 1);
  return v1;
}

// source: f/2/fadeout.c:301  [size]
struct QTask_s *__cdecl FadeOutEnd_New(struct QTask_s *ptParent)
{
  return QTask_NewFn(ptParent, FadeOut_eFadeOutEndQTaskType, nullptr);
}
