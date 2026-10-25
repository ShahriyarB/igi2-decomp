/* j/0/menusystem/menuscreen.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/menusystem/menuscreen.c:105  [anchor-mhash]
void __cdecl MenuScreen_DrawBorder(
        float vX0,
        float vY0,
        float vX1,
        float vY1,
        float vY2,
        float vFade,
        float vAlphaTop,
        float vAlphaBottom,
        enum bool isHighlight,
        enum bool isWhite)
{
  double v10; // st7
  double v11; // st7
  float v12; // esi
  float v13; // edi
  float v14; // ebx
  float vX2; // [esp+0h] [ebp-50h]
  float tRGB; // [esp+44h] [ebp-Ch]
  float tRGB_4; // [esp+48h] [ebp-8h]
  float tRGB_8; // [esp+4Ch] [ebp-4h]
  float vX0a = *(float *)&vX0; // [esp+54h] [ebp+4h] ARGSLOT
  float vX1a = *(float *)&vX1; // [esp+5Ch] [ebp+Ch] ARGSLOT
  float vFadea = *(float *)&vFade; // [esp+68h] [ebp+18h] ARGSLOT

  v10 = 1.0 - vFade;
  tRGB = 65.27999877929688;
  tRGB_4 = 80.63999938964844;
  tRGB_8 = 125.44000244140625;
  if ( v10 >= 0.0 )
  {
    if ( v10 > 1.0 )
      v10 = 1.0;
  }
  else
  {
    v10 = 0.0;
  }
  if ( isHighlight )
  {
    tRGB_8 = 115.19999694824219;
    tRGB_4 = 115.19999694824219;
    tRGB = 115.19999694824219;
  }
  if ( isWhite )
  {
    tRGB_8 = 128.0;
    tRGB_4 = 128.0;
    tRGB = 128.0;
  }
  v11 = v10 * ((vX1 - vX0) * 0.5);
  v12 = tRGB_8;
  v13 = tRGB_4;
  v14 = tRGB;
  vX0a = vX0 + v11;
  vX1a = vX1 - v11;
  vFadea = vFade * vAlphaTop;
  QSprite_RegisterLine(
    vX0a,
    vY0,
    1.0,
    vX1a,
    vY0,
    1.0,
    tRGB,
    tRGB_4,
    tRGB_8,
    tRGB,
    tRGB_4,
    tRGB_8,
    vFadea,
    1.0,
    0x80000u,
    0);
  QSprite_RegisterLine(vX0a, vY0, 1.0, vX0a, vY1, 1.0, v14, v13, v12, v14, v13, v12, vFadea, 1.0, 0x80000u, 0);
  QSprite_RegisterLine(vX1a, vY0, 1.0, vX1a, vY1, 1.0, v14, v13, v12, v14, v13, v12, vFadea, 1.0, 0x80000u, 0);
  vX2 = vX1a + 1.0;
  QSprite_RegisterLine(vX0a, vY1, 1.0, vX2, vY1, 1.0, v14, v13, v12, v14, v13, v12, vFadea, 1.0, 0x80000u, 0);
  if ( vY2 > (double)vY0 )
    QSprite_RegisterLine(
      vX0a,
      vY2,
      1.0,
      vX1a,
      vY2,
      1.0,
      tRGB,
      tRGB_4,
      tRGB_8,
      tRGB,
      tRGB_4,
      tRGB_8,
      vFadea,
      1.0,
      0x80000u,
      0);
}

// source: j/0/menusystem/menuscreen.c:200  [anchor-mhash]
void __cdecl MenuScreen_DrawBackground(
        float vX0,
        float vY0,
        float vX1,
        float vY1,
        float vY2,
        float vFade,
        float vAlphaTop,
        float vAlphaBottom,
        float vGradientTop,
        float vGradientBottom,
        enum bool isWhite)
{
  #pragma pack(push, 1)
  union
  {
    struct { float tRGB; };
    struct { char igi2_o1[4]; float tRGB_4; };
    struct { char igi2_o2[12]; struct QVertexStripContext_s tContext; };
    struct { char igi2_o3[32]; struct QVertex_s atQVertex[5]; };
    char igi2_extent[212];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v11; // st7
  double v12; // st7
  float vX0a = *(float *)&vX0; // [esp+DCh] [ebp+4h] ARGSLOT
  float vX1a = *(float *)&vX1; // [esp+E4h] [ebp+Ch] ARGSLOT

  v11 = 1.0 - vFade;
  if ( v11 >= 0.0 )
  {
    if ( v11 > 1.0 )
      v11 = 1.0;
  }
  else
  {
    v11 = 0.0;
  }
  igi2_frame.tRGB = 0.20000000298023224;
  igi2_frame.tRGB_4 = 0.5;
  if ( isWhite )
  {
    igi2_frame.tRGB_4 = 1.0;
    igi2_frame.tRGB = 1.0;
  }
  v12 = v11 * ((vX1 - vX0) * 0.5);
  QVertex_ptActiveTexture = nullptr;
  QVertex_ptActivePalette = nullptr;
  vX0a = vX0 + v12;
  vX1a = vX1 - v12;
  if ( vY2 > (double)vY0 )
  {
    igi2_frame.atQVertex[0].vX = vX0a;
    igi2_frame.atQVertex[0].vR = igi2_frame.tRGB * vGradientTop;
    igi2_frame.atQVertex[1].vX = vX1a;
    igi2_frame.atQVertex[2].vX = vX0a;
    igi2_frame.atQVertex[0].vG = igi2_frame.tRGB_4 * vGradientTop;
    igi2_frame.atQVertex[0].vA = vAlphaTop;
    igi2_frame.atQVertex[1].vA = vAlphaTop;
    igi2_frame.atQVertex[2].vA = vAlphaTop;
    igi2_frame.atQVertex[0].vB = vGradientTop;
    igi2_frame.atQVertex[0].vY = vY0;
    igi2_frame.atQVertex[1].vR = igi2_frame.atQVertex[0].vR;
    igi2_frame.atQVertex[1].vY = vY0;
    igi2_frame.atQVertex[1].vG = igi2_frame.atQVertex[0].vG;
    igi2_frame.atQVertex[3].vX = vX1a;
    igi2_frame.atQVertex[1].vB = vGradientTop;
    igi2_frame.atQVertex[3].vB = vGradientTop;
    igi2_frame.atQVertex[2].vY = vY2;
    igi2_frame.atQVertex[2].vR = igi2_frame.atQVertex[0].vR;
    igi2_frame.atQVertex[3].vY = vY2;
    igi2_frame.atQVertex[2].vG = igi2_frame.atQVertex[0].vG;
    igi2_frame.atQVertex[3].vA = vAlphaTop;
    igi2_frame.atQVertex[2].vB = vGradientTop;
    igi2_frame.atQVertex[3].vR = igi2_frame.atQVertex[0].vR;
    igi2_frame.atQVertex[0].vU = 0.0;
    igi2_frame.atQVertex[0].vV = 0.0;
    igi2_frame.atQVertex[3].vG = igi2_frame.atQVertex[0].vG;
    igi2_frame.atQVertex[0].vZ = 1.0;
    igi2_frame.atQVertex[1].vU = 0.0;
    igi2_frame.atQVertex[1].vV = 0.0;
    igi2_frame.atQVertex[1].vZ = 1.0;
    igi2_frame.atQVertex[2].vU = 0.0;
    igi2_frame.atQVertex[2].vV = 0.0;
    igi2_frame.atQVertex[2].vZ = 1.0;
    igi2_frame.atQVertex[3].vU = 0.0;
    igi2_frame.atQVertex[3].vV = 0.0;
    igi2_frame.atQVertex[3].vZ = 1.0;
    igi2_frame.tContext.bFlags = 0x80000;
    igi2_frame.tContext.isLine = 0;
    igi2_frame.tContext.nDepth = 0;
    igi2_frame.tContext.nStripLength = 4;
    igi2_frame.tContext.atQVertex = igi2_frame.atQVertex;
    RenderMode_tActiveRenderMode.apfRenderModeMethod[QVertex_eRegisterQVertexStripMethod](&igi2_frame.tContext);
  }
  igi2_frame.atQVertex[0].vX = vX0a;
  igi2_frame.atQVertex[0].vR = igi2_frame.tRGB * vGradientTop;
  igi2_frame.atQVertex[1].vX = vX1a;
  igi2_frame.atQVertex[0].vY = vY2;
  igi2_frame.atQVertex[1].vY = vY2;
  igi2_frame.atQVertex[0].vG = igi2_frame.tRGB_4 * vGradientTop;
  igi2_frame.atQVertex[0].vA = vAlphaTop;
  igi2_frame.atQVertex[1].vA = vAlphaTop;
  igi2_frame.atQVertex[0].vB = vGradientTop;
  igi2_frame.atQVertex[1].vR = igi2_frame.atQVertex[0].vR;
  igi2_frame.atQVertex[2].vX = vX0a;
  igi2_frame.atQVertex[1].vG = igi2_frame.atQVertex[0].vG;
  igi2_frame.atQVertex[2].vA = vAlphaBottom;
  igi2_frame.atQVertex[1].vB = vGradientTop;
  igi2_frame.atQVertex[3].vX = vX1a;
  igi2_frame.atQVertex[2].vR = igi2_frame.tRGB * vGradientBottom;
  igi2_frame.atQVertex[2].vY = vY1;
  igi2_frame.atQVertex[3].vY = vY1;
  igi2_frame.atQVertex[3].vA = vAlphaBottom;
  igi2_frame.atQVertex[2].vG = igi2_frame.tRGB_4 * vGradientBottom;
  igi2_frame.atQVertex[0].vU = 0.0;
  igi2_frame.atQVertex[0].vV = 0.0;
  igi2_frame.atQVertex[0].vZ = 1.0;
  igi2_frame.atQVertex[2].vB = vGradientBottom;
  igi2_frame.atQVertex[3].vB = vGradientBottom;
  igi2_frame.atQVertex[3].vR = igi2_frame.atQVertex[2].vR;
  igi2_frame.atQVertex[3].vG = igi2_frame.atQVertex[2].vG;
  igi2_frame.atQVertex[1].vU = 0.0;
  igi2_frame.atQVertex[1].vV = 0.0;
  igi2_frame.atQVertex[1].vZ = 1.0;
  igi2_frame.atQVertex[2].vU = 0.0;
  igi2_frame.atQVertex[2].vV = 0.0;
  igi2_frame.atQVertex[2].vZ = 1.0;
  igi2_frame.atQVertex[3].vU = 0.0;
  igi2_frame.atQVertex[3].vV = 0.0;
  igi2_frame.atQVertex[3].vZ = 1.0;
  igi2_frame.tContext.bFlags = 0x80000;
  igi2_frame.tContext.isLine = 0;
  igi2_frame.tContext.nDepth = 0;
  igi2_frame.tContext.nStripLength = 4;
  igi2_frame.tContext.atQVertex = igi2_frame.atQVertex;
  RenderMode_tActiveRenderMode.apfRenderModeMethod[QVertex_eRegisterQVertexStripMethod](&igi2_frame.tContext);
}

// source: j/0/menusystem/menuscreen.c:344  [anchor-mhash]
void __cdecl MenuScreen_DrawFrame(struct MenuScreen_t *ptMenuScreen)
{
  double v1; // st7
  double v2; // st6
  double v3; // st7
  float vY0; // [esp+0h] [ebp-18h]
  float vFade; // [esp+4h] [ebp-14h]
  float vX0; // [esp+8h] [ebp-10h]
  float vY2; // [esp+Ch] [ebp-Ch]
  float vY1; // [esp+10h] [ebp-8h]
  float vX1; // [esp+14h] [ebp-4h]
  float ptMenuScreena = *(float *)&ptMenuScreen; // [esp+1Ch] [ebp+4h] ARGSLOT

  v1 = (double)((Display_tActiveMode.nWidth >> 1) - 320);
  vX0 = (double)ptMenuScreen->nFrameX0 + v1 + 1.0;
  v2 = (double)((Display_tActiveMode.nHeight >> 1) - 240);
  vY0 = (double)ptMenuScreen->nFrameY0 + v2 + 1.0;
  vX1 = (double)ptMenuScreen->nFrameX1 + v1 + 1.0;
  vY1 = (double)ptMenuScreen->nFrameY1 + v2 + 1.0;
  vY2 = vY0 + 20.0;
  v3 = (double)*(int *)&ptMenuScreen->tMenuWindow.ptMenuManager[8].eQTaskType * 0.125;
  if ( v3 >= 1.0 )
    vFade = 1.0;
  else
    vFade = v3;
  MenuScreen_DrawBorder(vX0, vY0, vX1, vY1, vY2, vFade, 0.20000000298023224, 0.05000000074505806, false, false);
  MenuScreen_DrawBackground(vX0, vY0, vX1, vY1, vY2, vFade, 0.20000000298023224, 0.05000000074505806, 1.0, 0.0, false);
  if ( !ptMenuScreen->ptQPicture )
  {
    ptMenuScreena = vFade * 0.6600000262260437;
    MenuScreen_DrawBackground(vX0, vY0, vX1, vY1, vY2, vFade, ptMenuScreena, ptMenuScreena, 0.0, 0.0, true);
  }
}

// source: j/0/menusystem/menuscreen.c:377  [anchor-mhash]
void __cdecl MenuScreen_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][MenuWindow_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  ptQTask[5].tQTaskRefList.ptHead = nullptr;
  ptQTask[5].tQTaskRefList.ptMiddle = nullptr;
  LOBYTE(ptQTask[2].tQTaskChildren.ptMiddle) = 0;
  ptQTask[12].tQTaskRefList.ptMiddle = nullptr;
  LOBYTE(ptQTask[3].eQTaskType) = 0;
  ptQTask[5].tQTaskRefList.ptTail = nullptr;
  ptQTask[5].ptParent = nullptr;
  *(_DWORD *)&ptQTask[5].eQTaskType = 0;
  ptQTask[6].ptPrev = nullptr;
  ptQTask[6].ptNext = (struct QTask_s *)640;
  ptQTask[6].tQTaskChildren.ptHead = (struct QTask_s *)480;
  LOBYTE(ptQTask[12].tQTaskRefList.ptTail) = 1;
  BYTE1(ptQTask[12].tQTaskRefList.ptTail) = 0;
  ptQTask[12].tQTaskChildren.ptMiddle = (struct QTask_s *)-1;
  ptQTask[12].tQTaskChildren.ptTail = (struct QTask_s *)-1;
  ptQTask[6].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[6].tQTaskChildren.ptTail = nullptr;
  ptQTask[6].tQTaskRefList.ptHead = nullptr;
  ptQTask[8].tQTaskChildren.ptHead = nullptr;
  ptQTask[8].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[8].tQTaskChildren.ptTail = nullptr;
  ptQTask[8].tQTaskRefList.ptHead = nullptr;
  ptQTask[10].tQTaskChildren.ptHead = nullptr;
  ptQTask[10].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[10].tQTaskChildren.ptTail = nullptr;
  ptQTask[10].tQTaskRefList.ptHead = nullptr;
  ptQTask[12].tQTaskChildren.ptHead = nullptr;
}

// source: j/0/menusystem/menuscreen.c:415  [anchor-mhash]
void __cdecl MenuScreen_DeleteHandler(struct QTask_s *ptQTask)
{
  int v1; // eax
  struct QReference_s *v2; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *); // eax

  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[6].tQTaskChildren.ptMiddle);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[8].tQTaskChildren.ptMiddle);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[10].tQTaskChildren.ptMiddle);
  v1 = 0;
  while ( 1 )
  {
    v2 = Level_atLevelQTaskID[v1];
    if ( v2 )
    {
      if ( v2->pxObject == ptQTask )
        break;
    }
    if ( ++v1 >= 4096 )
      return;
  }
  if ( v1 >= 0 )
  {
    pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Level_eRemoveLevelScriptSymbolsEvent][ptQTask->eQTaskType].pfHandler;
    if ( pfHandler )
      pfHandler(ptQTask);
  }
}

// source: j/0/menusystem/menuscreen.c:439  [anchor-mhash]
void __cdecl MenuScreen_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v23; };
    struct { char igi2_o1[4]; char String1_[260]; };
    char igi2_extent[264];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v2; // eax
  struct QTask_s *ptPrev; // ecx
  struct QTask_s *v4; // ebx
  struct QTask_s *v5; // edx
  struct QTask_s *v6; // eax
  unsigned int v7; // eax
  char *v8; // edi
  struct QTask_s *v10; // ebx
  struct StaticTilemap_s *Picture; // eax
  struct QTask_s *ptNext_low; // edx
  struct QTilemap_s *ptQTilemap; // esi
  int nHeight; // ecx
  int v15; // edi
  __int16 *anGraphicWidth; // edx
  int v17; // ebx
  int v18; // ecx
  struct QReference_s *ptHead; // eax
  struct QReference_s *v20; // edi
  int ptPrev_high; // ecx
  struct QReference_s *ptNext; // eax

  if ( BYTE1(ptQTask[12].tQTaskRefList.ptTail) )
  {
    *(_DWORD *)&ptQTask[5].eQTaskType += (int)(Display_tActiveMode.nWidth
                                       - (Display_tActiveMode.nWidth >> 1)
                                       - (unsigned int)ptQTask[6].ptNext
                                       + 320);
    ptQTask[6].ptNext = (struct QTask_s *)(Display_tActiveMode.nWidth - (Display_tActiveMode.nWidth >> 1) + 320);
  }
  v2 = *(struct QTask_s **)&ptQTask[5].eQTaskType;
  ptPrev = ptQTask[6].ptPrev;
  v4 = *(struct QTask_s **)&ptQTask[1].eQTaskType;
  v5 = (struct QTask_s *)((char *)ptQTask[6].ptNext - (char *)v2);
  ptQTask[1].ptNext = v2;
  v6 = (struct QTask_s *)((char *)ptQTask[6].tQTaskChildren.ptHead - (char *)ptPrev);
  ptQTask[1].ptPrev = ptPrev;
  ptQTask[1].tQTaskChildren.ptHead = v5;
  ptQTask[1].tQTaskChildren.ptMiddle = v6;
  if ( v4 )
  {
    ptQTask[5].tQTaskRefList.ptHead = (struct QReference_s *)MenuManager_GetPicture(
                                                               v4,
                                                               (char *)&ptQTask[2].tQTaskChildren.ptMiddle);
    igi2_frame.String1_[0] = 0;
    v7 = strlen((char *)&ptQTask[3].eQTaskType) + 1;
    v8 = (char *)&igi2_frame.v23 + 3;
    while ( *++v8 )
      ;
    v10 = *(struct QTask_s **)&ptQTask[1].eQTaskType;
    qmemcpy(v8, &ptQTask[3].eQTaskType, v7);
    Picture = MenuManager_GetPicture(v10, igi2_frame.String1_);
    ptNext_low = nullptr;
    ptQTask[5].tQTaskRefList.ptMiddle = (struct QReference_s *)Picture;
    if ( Picture )
    {
      ptQTilemap = Picture->ptQTilemap;
      nHeight = Picture->ptQTilemap->nHeight;
      v15 = 0;
      igi2_frame.v23 = 0;
      if ( nHeight > 0 )
      {
        anGraphicWidth = ptQTilemap->anGraphicWidth;
        v17 = nHeight;
        do
        {
          if ( *anGraphicWidth > v15 )
            v15 = *anGraphicWidth;
          ++anGraphicWidth;
          --v17;
        }
        while ( v17 );
        igi2_frame.v23 = v15;
      }
      v18 = (__int64)((double)(int)ptQTask[5].ptParent
                    - (double)(ptQTilemap->nHeight
                             * ptQTilemap->ptQSprite->atQAnimframe[ptQTilemap->ptQSprite->nQAnimframes].nHeight)
                    * 0.5);
      Picture->vX = (float)(int)((__int64)((double)(int)ptQTask[5].tQTaskRefList.ptTail - (double)igi2_frame.v23 * 0.5)
                               + (Display_tActiveMode.nWidth >> 1)
                               - 320);
      *(float *)&ptQTask[5].tQTaskRefList.ptMiddle->pxObject = (float)((Display_tActiveMode.nHeight >> 1) + v18 - 240);
      ptNext_low = nullptr;
      ptQTask[5].tQTaskRefList.ptMiddle[2].pxObject = nullptr;
      ptQTask[5].tQTaskRefList.ptMiddle[3].ptNext = (struct QReference_s *)8;
    }
    ptHead = ptQTask[5].tQTaskRefList.ptHead;
    if ( ptHead )
    {
      ptHead[2].pxObject = nullptr;
      *(float *)&ptQTask[5].tQTaskRefList.ptHead->ptPrev = (float)((Display_tActiveMode.nWidth >> 1) - 320);
      *(float *)&ptQTask[5].tQTaskRefList.ptHead->pxObject = (float)((Display_tActiveMode.nHeight >> 1) - 240);
      v20 = ptQTask[5].tQTaskRefList.ptHead;
      ptPrev_high = SHIWORD(v20->ptNext->ptPrev);
      if ( ptPrev_high > 0 )
      {
        ptNext = v20->ptNext[1].ptNext;
        do
        {
          if ( SLOWORD(ptNext->ptNext) > (int)ptNext_low )
            ptNext_low = (struct QTask_s *)SLOWORD(ptNext->ptNext);
          ptNext = (struct QReference_s *)((char *)ptNext + 2);
          --ptPrev_high;
        }
        while ( ptPrev_high );
      }
      ptQTask[1].tQTaskChildren.ptHead = ptNext_low;
      ptQTask[1].tQTaskChildren.ptMiddle = (struct QTask_s *)(SHIWORD(v20->ptNext->ptPrev)
                                                            * *(__int16 *)(*((_DWORD *)v20->ptNext->pxObject + 2)
                                                                         + 36
                                                                         * *((unsigned __int16 *)v20->ptNext->pxObject
                                                                           + 10)
                                                                         + 14));
    }
  }
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[6].tQTaskChildren.ptMiddle, ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[8].tQTaskChildren.ptMiddle, ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[10].tQTaskChildren.ptMiddle, ptQTask);
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][MenuWindow_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
}

// source: j/0/menusystem/menuscreen.c:534  [anchor-mhash]
void __cdecl MenuScreen_DrawHandler(struct QTask_s *ptQTask)
{
  struct QReference_s *ptMiddle; // eax
  int v2; // eax
  struct QReference_s *ptHead; // eax

  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Screen_eDrawQTaskEvent][MenuWindow_eQTaskType].pfHandler)(ptQTask);
  if ( LOBYTE(ptQTask[12].tQTaskRefList.ptTail) )
    MenuScreen_DrawFrame((struct MenuScreen_t *)ptQTask);
  ptMiddle = ptQTask[5].tQTaskRefList.ptMiddle;
  if ( ptMiddle )
    QTilemap_Register(
      (struct QTilemap_s *)ptMiddle->ptNext,
      *(float *)&ptMiddle->ptPrev,
      *(float *)&ptMiddle->pxObject,
      *(float *)&ptMiddle[1].pxObject,
      *(float *)&ptMiddle[2].ptNext,
      *(float *)&ptMiddle[2].ptPrev,
      *(float *)&ptMiddle[1].ptPrev,
      *(float *)&ptMiddle[1].ptNext,
      (unsigned int)ptMiddle[3].ptNext,
      (int)ptMiddle[2].pxObject);
  v2 = *(_DWORD *)(*(_DWORD *)&ptQTask[1].eQTaskType + 10040);
  if ( v2 )
    ((void (__cdecl *)(_DWORD))QTask_aatQTaskFinalEvent[Screen_eDrawQTaskEvent][*(unsigned __int16 *)(v2 + 36)].pfHandler)(*(_DWORD *)(*(_DWORD *)&ptQTask[1].eQTaskType + 10040));
  ptHead = ptQTask[5].tQTaskRefList.ptHead;
  if ( ptHead )
    QTilemap_Register(
      (struct QTilemap_s *)ptHead->ptNext,
      *(float *)&ptHead->ptPrev,
      *(float *)&ptHead->pxObject,
      *(float *)&ptHead[1].pxObject,
      *(float *)&ptHead[2].ptNext,
      *(float *)&ptHead[2].ptPrev,
      *(float *)&ptHead[1].ptPrev,
      *(float *)&ptHead[1].ptNext,
      (unsigned int)ptHead[3].ptNext,
      (int)ptHead[2].pxObject);
}

// source: j/0/menusystem/menuscreen.c:576  [anchor-caller]
void __cdecl MenuScreen_RunHandler(struct QTask_s *ptQTask)
{
  int v1; // eax
  int v2; // edi
  struct QTask_s *ptMiddle; // eax
  unsigned int ptTail; // eax
  struct QReference_s *v5; // ecx

  v1 = *(_DWORD *)&ptQTask[1].eQTaskType;
  if ( v1 )
  {
    v2 = v1 + 10020;
    if ( v1 != -10020 )
    {
      if ( *(_BYTE *)(v1 + 10024)
        && ptQTask[6].tQTaskChildren.ptMiddle
        && ptQTask[6].tQTaskChildren.ptTail->ptNext
        && ptQTask[6].tQTaskRefList.ptHead )
      {
        LOBYTE(MenuManager_ptQTask[243].eQTaskType) = 1;
        Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[6].tQTaskChildren.ptMiddle, ptQTask);
      }
      *(_BYTE *)(v2 + 4) = 0;
    }
  }
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][MenuWindow_eQTaskType].pfHandler)(ptQTask);
  ptMiddle = ptQTask[12].tQTaskChildren.ptMiddle;
  if ( (int)ptMiddle >= 0 )
    ptQTask[12].tQTaskChildren.ptMiddle = (struct QTask_s *)((char *)ptMiddle - 1);
  if ( !ptQTask[12].tQTaskChildren.ptMiddle )
  {
    ptTail = (unsigned int)ptQTask[12].tQTaskChildren.ptTail;
    if ( ptTail < 0x1000 )
    {
      v5 = Level_atLevelQTaskID[ptTail];
      if ( v5 )
      {
        if ( v5->pxObject )
          MenuManager_ActivateScreen(*(struct QTask_s **)&ptQTask[1].eQTaskType, ptTail, false);
      }
    }
  }
}

// source: j/0/menusystem/menuscreen.c:622  [size]
void __cdecl MenuScreen_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = MenuScreen_ptParameterList;
}

// source: j/0/menusystem/menuscreen.c:638  [size]
void __cdecl MenuScreen_RegisterScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[128]; };
    struct { char igi2_o1[128]; char zTemp[128]; };
    char igi2_extent[256];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( !ptQTask[12].tQTaskRefList.ptMiddle )
  {
    ptQTask[12].tQTaskRefList.ptMiddle = (struct QReference_s *)1;
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.nUserData", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int,
      &ptQTask[12].tQTaskRefList,
      4,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
  }
}

// source: j/0/menusystem/menuscreen.c:664  [size]
void __cdecl MenuScreen_RemoveScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[128]; };
    struct { char igi2_o1[128]; char zTemp[128]; };
    char igi2_extent[256];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( ptQTask[12].tQTaskRefList.ptMiddle )
  {
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.nUserData", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    ptQTask[12].tQTaskRefList.ptMiddle = nullptr;
  }
}

// source: j/0/menusystem/menuscreen.c:693  [size]
void __cdecl MenuScreen_InitDataHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // ecx
  int v2; // edx
  struct QTask_s *v3; // eax
  int v4; // esi
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v6; // edx

  if ( ptQTask[8].tQTaskChildren.ptMiddle && ptQTask[8].tQTaskChildren.ptTail->ptNext && ptQTask[8].tQTaskRefList.ptHead )
    Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[8].tQTaskChildren.ptMiddle, ptQTask);
  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v2 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v3 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v3 = nullptr;
      v4 = MenuWindow_eInitDataEvent;
      QTask_atProtectedQTaskStack[v2].ptQTask = v3;
      pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[v4][ptHead->eQTaskType].pfHandler;
      v6 = v2 + 1;
      QTask_nProtectedQTaskStackOffset = v6;
      if ( pfHandler )
      {
        pfHandler(ptHead);
        v6 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v6];
      v2 = v6 - 1;
      QTask_nProtectedQTaskStackOffset = v2;
    }
    while ( ptHead );
  }
}

// source: j/0/menusystem/menuscreen.c:715  [size]
void __cdecl MenuScreen_ChangeDataHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // ecx
  int v2; // edx
  struct QTask_s *v3; // eax
  int v4; // esi
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v6; // edx

  if ( ptQTask[10].tQTaskChildren.ptMiddle
    && ptQTask[10].tQTaskChildren.ptTail->ptNext
    && ptQTask[10].tQTaskRefList.ptHead )
  {
    Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[10].tQTaskChildren.ptMiddle, ptQTask);
  }
  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v2 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v3 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v3 = nullptr;
      v4 = MenuWindow_eChangeDataEvent;
      QTask_atProtectedQTaskStack[v2].ptQTask = v3;
      pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[v4][ptHead->eQTaskType].pfHandler;
      v6 = v2 + 1;
      QTask_nProtectedQTaskStackOffset = v6;
      if ( pfHandler )
      {
        pfHandler(ptHead);
        v6 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v6];
      v2 = v6 - 1;
      QTask_nProtectedQTaskStackOffset = v2;
    }
    while ( ptHead );
  }
}

// source: j/0/menusystem/menuscreen.c:740  [anchor-hash]
void __cdecl MenuScreen_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // edx

  v0 = QTask_NewQTaskType("MenuScreen", 512, MenuWindow_eQTaskType, 0, 0);
  MenuScreen_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, MenuScreen_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Screen_eDrawQTaskEvent, MenuScreen_DrawHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, MenuScreen_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, MenuScreen_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))MenuScreen_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, MenuScreen_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eRegisterLevelScriptSymbolsEvent,
    MenuScreen_RegisterScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eRemoveLevelScriptSymbolsEvent,
    MenuScreen_RemoveScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, MenuWindow_eInitDataEvent, MenuScreen_InitDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, MenuWindow_eChangeDataEvent, MenuScreen_ChangeDataHandler);
  v1 = (struct ParameterList_s *)Mem_AllocFn(312, 4);
  v2 = Level_eParameterTypeString32;
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  v1->nParameters = 0;
  v1->nMaxParameters = 15;
  MenuScreen_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0x5Cu, v2, "Background", 7u, nullptr);
  ParameterList_AddParameter(MenuScreen_ptParameterList, 0x9Cu, Level_eParameterTypeString32, "Logo", 7u, nullptr);
  ParameterList_AddParameterMinMax(
    MenuScreen_ptParameterList,
    0xE4u,
    Level_eParameterTypeInt32,
    "Center Logo X",
    7u,
    0.0,
    640.0);
  ParameterList_AddParameterMinMax(
    MenuScreen_ptParameterList,
    0xE8u,
    Level_eParameterTypeInt32,
    "Center Logo Y",
    7u,
    0.0,
    480.0);
  ParameterList_AddParameter(MenuScreen_ptParameterList, 0x1FCu, Level_eParameterTypebool8, "Use Frame?", 7u, nullptr);
  ParameterList_AddParameter(MenuScreen_ptParameterList, 0xECu, Level_eParameterTypeInt32, "Frame x0", 7u, nullptr);
  ParameterList_AddParameter(MenuScreen_ptParameterList, 0xF4u, Level_eParameterTypeInt32, "Frame y0", 7u, nullptr);
  ParameterList_AddParameter(MenuScreen_ptParameterList, 0xF0u, Level_eParameterTypeInt32, "Frame x1", 7u, nullptr);
  ParameterList_AddParameter(MenuScreen_ptParameterList, 0xF8u, Level_eParameterTypeInt32, "Frame y1", 7u, nullptr);
  ParameterList_AddParameter(
    MenuScreen_ptParameterList,
    0xFCu,
    Level_eParameterTypeVarString,
    "On Press Escape",
    7u,
    nullptr);
  ParameterList_AddParameter(
    MenuScreen_ptParameterList,
    0x14Cu,
    Level_eParameterTypeVarString,
    "On Init Data",
    7u,
    nullptr);
  ParameterList_AddParameter(
    MenuScreen_ptParameterList,
    0x19Cu,
    Level_eParameterTypeVarString,
    "On Change Data",
    7u,
    nullptr);
  ParameterList_AddParameterMinMax(
    MenuScreen_ptParameterList,
    0x1ECu,
    Level_eParameterTypeInt32,
    "Ticks to Timeout",
    7u,
    -1.0,
    108000.0);
  ParameterList_AddParameterMinMax(
    MenuScreen_ptParameterList,
    0x1F0u,
    Level_eParameterTypeInt32,
    "Timeout Screen",
    7u,
    -1.0,
    10000.0);
  ParameterList_AddParameter(
    MenuScreen_ptParameterList,
    0x1FDu,
    Level_eParameterTypebool8,
    "Right Justify?",
    7u,
    nullptr);
}

// source: j/0/menusystem/menuscreen.c:790  [size]
void __cdecl MenuScreen_Close()
{
  int v0; // esi

  if ( MenuScreen_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&MenuScreen_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(MenuScreen_eQTaskType);
  MenuScreen_eQTaskType = 512;
}
