/* j/0/weapons/sniperoverlay.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/weapons/sniperoverlay.c:62  [anchor-mhash]
void __cdecl SniperOverlay_Draw(struct QTask_s *ptQTask)
{
  struct QTask_s *ptNext; // eax
  int nQAnimframes; // eax
  double v3; // st7
  float v4; // edi
  float v5; // esi
  int v6; // ebx
  int v7; // edi
  int v8; // ebx
  int v9; // eax
  long double v10; // st7
  int v11; // edi
  double v12; // st7
  struct QSprite_s *v13; // edi
  int v14; // eax
  double v15; // st6
  float v16; // ecx
  struct QSprite_s *p_tQSprite; // ebx
  int v18; // edi
  float vX1; // [esp+0h] [ebp-88h]
  float vX1a; // [esp+0h] [ebp-88h]
  float vX1b; // [esp+0h] [ebp-88h]
  float v22; // [esp+4h] [ebp-84h]
  float v23; // [esp+Ch] [ebp-7Ch]
  float v24; // [esp+10h] [ebp-78h]
  float vThickness; // [esp+34h] [ebp-54h]
  int vY; // [esp+4Ch] [ebp-3Ch]
  float vYa; // [esp+4Ch] [ebp-3Ch]
  float v28; // [esp+50h] [ebp-38h]
  float vX; // [esp+54h] [ebp-34h]
  float vOffset; // [esp+58h] [ebp-30h]
  float vX2; // [esp+5Ch] [ebp-2Ch]
  float v32; // [esp+60h] [ebp-28h]
  float v33; // [esp+64h] [ebp-24h]
  struct QSprite_s *v34; // [esp+68h] [ebp-20h]
  int nWidth; // [esp+6Ch] [ebp-1Ch]
  float vY2; // [esp+70h] [ebp-18h]
  int iI; // [esp+74h] [ebp-14h]
  float vX3; // [esp+78h] [ebp-10h]
  int vY1; // [esp+7Ch] [ebp-Ch]
  __int64 avAngle; // [esp+80h] [ebp-8h]

  nWidth = Display_tActiveMode.nWidth;
  ptNext = ptQTask[1].ptNext;
  vY = Display_tActiveMode.nHeight;
  HIDWORD(avAngle) = 0;
  if ( !ptNext )
  {
    ptQTask[1].ptNext = (struct QTask_s *)Text_New(
                                            ComputerMenu_tComputerMenuResource.ptQSpriteFont3,
                                            0.0,
                                            0.0,
                                            (char *)&g_zInitialValue);
    ptQTask[1].ptPrev = (struct QTask_s *)Text_New(
                                            ComputerMenu_tComputerMenuResource.ptQSpriteFont3,
                                            0.0,
                                            0.0,
                                            (char *)&stru_6972D4.tQTaskRefList.ptTail);
    ptQTask[1].tQTaskChildren.ptHead = (struct QTask_s *)Text_New(
                                                           ComputerMenu_tComputerMenuResource.ptQSpriteFont3,
                                                           0.0,
                                                           0.0,
                                                           (char *)&stru_6972D4.tQTaskRefList.ptMiddle);
    ptQTask[1].tQTaskChildren.ptMiddle = (struct QTask_s *)Text_New(
                                                             ComputerMenu_tComputerMenuResource.ptQSpriteFont3,
                                                             0.0,
                                                             0.0,
                                                             (char *)&stru_6972D4.tQTaskRefList);
    ptQTask[1].tQTaskChildren.ptTail = (struct QTask_s *)Text_New(
                                                           ComputerMenu_tComputerMenuResource.ptQSpriteFont3,
                                                           0.0,
                                                           0.0,
                                                           (char *)&stru_6972D4.tQTaskChildren.ptTail);
  }
  nQAnimframes = SniperOverlay_ptCornerSprite->tQSprite.nQAnimframes;
  v32 = (float)nWidth;
  vOffset = v32 / (double)SniperOverlay_ptCornerSprite->tQSprite.atQAnimframe[nQAnimframes].nWidth;
  v3 = (double)vY;
  v28 = v3;
  vX3 = v3 * 0.5;
  v4 = vX3;
  *(float *)&vY1 = v32 * 0.5;
  v5 = *(float *)&vY1;
  *(float *)&iI = -vOffset;
  v6 = iI;
  QSprite_Register4(
    &SniperOverlay_ptCornerSprite->tQSprite,
    *(float *)&iI,
    *(float *)&iI,
    *(float *)&vY1,
    *(float *)&iI,
    *(float *)&iI,
    vX3,
    *(float *)&vY1,
    vX3,
    128.0,
    128.0,
    128.0,
    0,
    (unsigned int)&MTP_atLODVirModel[45].atBoneVertexRefs[20].atVertexRefs[781],
    1);
  *(float *)&v34 = v32 + vOffset;
  QSprite_Register4(
    &SniperOverlay_ptCornerSprite->tQSprite,
    *(float *)&v34,
    *(float *)&v6,
    v5,
    *(float *)&v6,
    *(float *)&v34,
    v4,
    v5,
    v4,
    128.0,
    128.0,
    128.0,
    0,
    (unsigned int)&MTP_atLODVirModel[45].atBoneVertexRefs[20].atVertexRefs[781],
    1);
  vX = v28 + vOffset;
  QSprite_Register4(
    &SniperOverlay_ptCornerSprite->tQSprite,
    *(float *)&v6,
    vX,
    v5,
    vX,
    *(float *)&v6,
    v4,
    v5,
    v4,
    128.0,
    128.0,
    128.0,
    0,
    (unsigned int)&MTP_atLODVirModel[45].atBoneVertexRefs[20].atVertexRefs[781],
    1);
  QSprite_Register4(
    &SniperOverlay_ptCornerSprite->tQSprite,
    *(float *)&v34,
    vX,
    v5,
    vX,
    *(float *)&v34,
    v4,
    v5,
    v4,
    128.0,
    128.0,
    128.0,
    0,
    (unsigned int)&MTP_atLODVirModel[45].atBoneVertexRefs[20].atVertexRefs[781],
    1);
  *(float *)&v34 = (float)(nWidth / 2);
  v7 = 1;
  iI = 1;
  v33 = (float)(vY / 2);
  *(float *)&nWidth = v28 * 0.003000000026077032;
  v8 = nWidth;
  do
  {
    LODWORD(avAngle) = HIDWORD(avAngle);
    v9 = 0;
    *((float *)&avAngle + 1) = (double)iI * 0.13089969389957476;
    do
    {
      v10 = *(float *)((char *)&avAngle + v9);
      v9 += 4;
      *(float *)((char *)&vX + v9) = cos(v10) * v28 * 0.4000000059604645 + *(float *)&v34;
      *(float *)((char *)&v34 + v9) = sin(*(float *)((char *)&vY1 + v9)) * v28 * 0.4000000059604645 + v33;
    }
    while ( v9 < 8 );
    QSprite_RegisterLine(
      vOffset,
      *(float *)&nWidth,
      1.0,
      vX2,
      vY2,
      1.0,
      0.0,
      0.0,
      0.0,
      0.0,
      0.0,
      0.0,
      1.0,
      *(float *)&v8,
      (unsigned int)&MTP_atLODVirModel[87].atBoneVertexRefs[15].atVertexRefs[82],
      1);
    iI = ++v7;
  }
  while ( v7 <= 48 );
  v11 = (__int64)((double)vY * 0.015);
  *(float *)&nWidth = v28 * 0.4000000059604645;
  vOffset = (float)v11;
  vX = *(float *)&nWidth + *(float *)&v34 - vOffset * 0.5;
  avAngle = (__int64)(v28 * 0.20000000298023224);
  *(float *)&iI = (float)(int)avAngle;
  vX1 = vX - *(float *)&iI;
  QSprite_RegisterLine(
    vX1,
    v33,
    1.0,
    vX,
    v33,
    1.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    1.0,
    vOffset,
    (unsigned int)&MTP_atLODVirModel[87].atBoneVertexRefs[15].atVertexRefs[82],
    1);
  vOffset = (float)v11;
  vX = *(float *)&v34 - *(float *)&nWidth + vOffset * 0.5;
  vX1a = *(float *)&iI + vX;
  QSprite_RegisterLine(
    vX1a,
    v33,
    1.0,
    vX,
    v33,
    1.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    1.0,
    vOffset,
    (unsigned int)&MTP_atLODVirModel[3].atBoneVertexRefs[26].atVertexRefs[479],
    1);
  v12 = (double)v11;
  v13 = v34;
  vOffset = v12;
  vYa = *(float *)&nWidth + v33 - vOffset * 0.5;
  vX = *(float *)&v34;
  *(float *)&iI = vYa - (double)(int)(__int64)(v28 * 0.20000000298023224);
  QSprite_RegisterLine(
    *(float *)&v34,
    *(float *)&iI,
    1.0,
    *(float *)&v34,
    vYa,
    1.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    1.0,
    vOffset,
    (unsigned int)&MTP_atLODVirModel[3].atBoneVertexRefs[26].atVertexRefs[479],
    1);
  v14 = iI;
  iI = (__int64)(v28 * 0.007000000216066837);
  vThickness = (float)iI;
  avAngle = (__int64)(v28 * 0.07500000298023224);
  iI = avAngle;
  v22 = *(float *)&v14 - (double)(int)avAngle;
  QSprite_RegisterLine(
    *(float *)&v13,
    v22,
    1.0,
    *(float *)&v13,
    *(float *)&v14,
    1.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    1.0,
    vThickness,
    (unsigned int)&MTP_atLODVirModel[3].atBoneVertexRefs[26].atVertexRefs[479],
    1);
  avAngle = (__int64)(v32 * 0.20000000298023224);
  iI = avAngle;
  v15 = (double)(int)avAngle;
  v23 = v15 + *(float *)&vY1;
  vX1b = *(float *)&vY1 - v15;
  QSprite_RegisterLine(
    vX1b,
    vX3,
    1.0,
    v23,
    vX3,
    1.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    1.0,
    1.0,
    (unsigned int)&MTP_atLODVirModel[3].atBoneVertexRefs[26].atVertexRefs[479],
    1);
  v16 = *(float *)&vY1;
  avAngle = (__int64)(v28 * 0.05000000074505806);
  vY1 = avAngle;
  vX = v16;
  v24 = (double)(int)avAngle + vX3;
  QSprite_RegisterLine(
    v16,
    vX3,
    1.0,
    v16,
    v24,
    1.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    1.0,
    1.0,
    (unsigned int)&MTP_atLODVirModel[3].atBoneVertexRefs[26].atVertexRefs[479],
    1);
  SniperOverlay_DrawRangeMeter((struct SniperOverlay_s *)ptQTask, 0.36500000953674316, 0.5199999809265137);
  SniperOverlay_DrawCompass((struct SniperOverlay_s *)ptQTask, 0.3499999940395355, 0.32499998807907104, 0.5600000023841858);
  if ( ptQTask[1].tQTaskRefList.ptHead )
  {
    p_tQSprite = &BinocularOverlay_ptInfraGameSprite->tQSprite;
    vY1 = BinocularOverlay_ptInfraGameSprite->tQSprite.atQAnimframe[BinocularOverlay_ptInfraGameSprite->tQSprite.nQAnimframes].nWidth;
    vOffset = v32 / (double)vY1;
    vX = v28 + vOffset;
    *(float *)&iI = -vOffset;
    v18 = iI;
    QSprite_Register4(
      &BinocularOverlay_ptInfraGameSprite->tQSprite,
      *(float *)&iI,
      *(float *)&iI,
      v5,
      *(float *)&iI,
      *(float *)&iI,
      vX,
      v5,
      vX,
      128.0,
      128.0,
      128.0,
      0,
      (unsigned int)&MTP_atLODVirModel[45].atBoneVertexRefs[20].atVertexRefs[781],
      1);
    *(float *)&v34 = v32 + vOffset;
    QSprite_Register4(
      p_tQSprite,
      *(float *)&v34,
      *(float *)&v18,
      v5,
      *(float *)&v18,
      *(float *)&v34,
      vX,
      v5,
      vX,
      128.0,
      128.0,
      128.0,
      0,
      (unsigned int)&MTP_atLODVirModel[45].atBoneVertexRefs[20].atVertexRefs[781],
      1);
  }
}

// source: j/0/weapons/sniperoverlay.c:315  [size]
void __cdecl SniperOverlay_StatusDisplayHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct TransContext_s *v2; // eax

  v2 = TransContext_Create(
         (struct TransContext_s *)&ptQTask[3].tQTaskRefList.ptMiddle,
         (struct real32x9_t *)&ptQTask[2].tQTaskRefList,
         (struct real64x3_t *)&ptQTask[1].tQTaskRefList.ptMiddle,
         1.0);
  TransContext_SetActiveTransContext(v2);
  SniperOverlay_Draw(ptQTask);
  TransContext_isValid = 0;
}

// source: j/0/weapons/sniperoverlay.c:341  [size]
void __cdecl SniperOverlay_DrawHandler(struct QTask_s *ptQTask)
{
  struct TransContext_s *v1; // eax

  v1 = TransContext_Create(
         (struct TransContext_s *)&ptQTask[3].tQTaskRefList.ptMiddle,
         (struct real32x9_t *)&ptQTask[2].tQTaskRefList,
         (struct real64x3_t *)&ptQTask[1].tQTaskRefList.ptMiddle,
         1.0);
  TransContext_SetActiveTransContext(v1);
  SniperOverlay_Draw(ptQTask);
  TransContext_isValid = 0;
}

// source: j/0/weapons/sniperoverlay.c:354  [size]
void __cdecl SniperOverlay_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[1].tQTaskRefList.ptHead = nullptr;
  ptQTask[1].ptNext = nullptr;
  ptQTask[1].ptPrev = nullptr;
  ptQTask[1].tQTaskChildren.ptHead = nullptr;
  ptQTask[1].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[1].tQTaskChildren.ptTail = nullptr;
  if ( pxContext )
    ptQTask[1].tQTaskRefList.ptHead = *((struct QReference_s **)pxContext + 15);
  isDrawInfra = (enum bool)ptQTask[1].tQTaskRefList.ptHead;
  isInfraEnabled = isDrawInfra;
}

// source: j/0/weapons/sniperoverlay.c:388  [size]
void __cdecl SniperOverlay_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptNext; // eax
  struct QTilemap_s ***p_ptPrev; // ebx
  int v3; // ebp
  struct QTilemap_s **v4; // esi
  int v5; // esi

  ptNext = ptQTask[1].ptNext;
  if ( ptNext )
    Text_Delete((struct StaticTilemap_s *)ptNext);
  p_ptPrev = (struct QTilemap_s ***)&ptQTask[1].ptPrev;
  v3 = 4;
  do
  {
    v4 = *p_ptPrev;
    if ( *p_ptPrev )
    {
      QTilemap_Delete(*v4);
      v5 = *(_DWORD *)((unsigned int)(v4 - 1) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v5);
      memset(*(void **)(v5 + 8), 0xCDu, *(_DWORD *)(v5 + 16));
      free((void *)v5);
    }
    ++p_ptPrev;
    --v3;
  }
  while ( v3 );
  isDrawInfra = false;
  isInfraEnabled = 0;
}

// source: j/0/weapons/sniperoverlay.c:421  [anchor-strings]
void __cdecl SniperOverlay_CreateParameterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v2; // esi
  struct QTask_s *v3; // edi
  struct QTask_s *v4; // eax

  v2 = QTask_NewFn(nullptr, SniperOverlay_eQTaskType, nullptr);
  v3 = *((struct QTask_s **)pxContext + 1);
  *((_DWORD *)pxContext + 2) = v2;
  v4 = TagItem_Find(v3, (char *)&stru_6972D4);
  if ( v4 || (v4 = TagItem_NewBool8(v3, (char *)&stru_6972D4, false)) != nullptr )
    v2[1].tQTaskRefList.ptHead = (struct QReference_s *)SLOBYTE(v4[7].tQTaskRefList.ptHead);
  else
    v2[1].tQTaskRefList.ptHead = nullptr;
}

// source: j/0/weapons/sniperoverlay.c:444  [size]
void __cdecl SniperOverlay_DeleteParameterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  QTask_Delete(*(struct QTask_s **)pxContext);
}

// source: j/0/weapons/sniperoverlay.c:463  [anchor-mhash]
void __cdecl SniperOverlay_PositionOverlayHandler(struct QTask_s *ptQTask, void *pxContext)
{
  float *v2; // eax
  struct QTaskNodeList_s struct_qtasknodelist_s; // 0:^C.12

  qmemcpy(&ptQTask[1].tQTaskRefList.ptMiddle, *(void **)pxContext, 0x18u);
  ptQTask[2].tQTaskChildren.ptHead = nullptr;
  ptQTask[2].tQTaskChildren.ptMiddle = (struct QTask_s *)1065353216;
  ptQTask[2].tQTaskChildren.ptTail = nullptr;
  v2 = *((float **)pxContext + 1);
  *(float *)&struct_qtasknodelist_s.ptHead = (v2[2] + *v2) * 0.0 + v2[1];
  *(float *)&struct_qtasknodelist_s.ptMiddle = (v2[5] + v2[3]) * 0.0 + v2[4];
  *(float *)&struct_qtasknodelist_s.ptTail = (v2[8] + v2[6]) * 0.0 + v2[7];
  ptQTask[2].tQTaskChildren = struct_qtasknodelist_s;
  qmemcpy(&ptQTask[2].tQTaskRefList, *((void **)pxContext + 1), sizeof(struct QTask_s));
}

// source: j/0/weapons/sniperoverlay.c:493  [anchor-callee]
void __cdecl SniperOverlay_DrawRangeMeter(struct SniperOverlay_s *ptSniperOverlay, float vXPos, float vYPos)
{
  #pragma pack(push, 1)
  union
  {
    struct { int nWidth; };
    struct { char igi2_o1[8]; int nHeight; };
    struct { char igi2_o2[16]; struct real64x3_t ptEnd; };
    struct { char igi2_o3[40]; struct CollisionEvaluateContext_s nNumPoints; };
    struct { char igi2_o4[48]; struct QIntersection_s ptIntersection; };
    struct { char igi2_o5[168]; double v12; };
    struct { char igi2_o6[192]; char Buffer[128]; };
    char igi2_extent[320];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double vX; // st7
  struct QTask_s *ptParent; // edx
  char *LocalizedStringForLanguage; // eax
  struct StaticTilemap_s *ptRangeText; // ebp

  vX = ptSniperOverlay->tDirection.vX;
  igi2_frame.ptEnd.vY = ptSniperOverlay->tDirection.vY;
  ptParent = ptSniperOverlay->tQTask.ptParent;
  igi2_frame.ptEnd.vZ = ptSniperOverlay->tDirection.vZ;
  igi2_frame.nHeight = Display_tActiveMode.nHeight;
  qmemcpy(&igi2_frame.ptIntersection, &ptSniperOverlay->tPos, 0x18u);
  igi2_frame.ptEnd.vZ = igi2_frame.ptEnd.vZ * 4096000.0;
  igi2_frame.ptEnd.vX = *(double *)&igi2_frame.ptIntersection.ptHitObj + vX * 4096000.0;
  igi2_frame.nWidth = Display_tActiveMode.nWidth;
  igi2_frame.nNumPoints.isEvaluate = 0;
  igi2_frame.ptEnd.vY = igi2_frame.ptIntersection.tPos.vX + igi2_frame.ptEnd.vY * 4096000.0;
  igi2_frame.ptEnd.vZ = igi2_frame.ptIntersection.tPos.vY + igi2_frame.ptEnd.vZ;
  igi2_frame.nNumPoints.ptQTask = ptParent->ptParent;
  World_TraceLines(
    Game_ptGame->ptWorld,
    (struct QIntersection_s *)&igi2_frame.ptIntersection.tPos.vZ,
    (struct real64x3_t *)&igi2_frame.ptIntersection,
    &igi2_frame.ptEnd,
    1,
    13,
    &igi2_frame.nNumPoints,
    Forest_bQTaskGroup | 0x98000000);
  LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                 "weapons/strings/Binoculars/range",
                                 Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                 true);
  if ( *((_DWORD *)&igi2_frame.ptIntersection.vLight + 1) )
    sprintf(igi2_frame.Buffer, "%s: %0.f%s", LocalizedStringForLanguage, igi2_frame.v12 * 0.000244140625, "m");
  else
    sprintf(igi2_frame.Buffer, "%s: %0.f+%s", LocalizedStringForLanguage, 1000.0, "m");
  Text_SetString(ptSniperOverlay->ptRangeText, igi2_frame.Buffer);
  ptSniperOverlay->ptRangeText->vX = (float)(int)(__int64)((double)igi2_frame.nWidth * vXPos);
  ptSniperOverlay->ptRangeText->vY = (float)(int)(__int64)((double)igi2_frame.nHeight * vYPos);
  ptSniperOverlay->ptRangeText->vR = 0.0;
  ptSniperOverlay->ptRangeText->vG = 0.0;
  ptSniperOverlay->ptRangeText->vB = 0.0;
  ptRangeText = ptSniperOverlay->ptRangeText;
  QTilemap_Register(
    ptRangeText->ptQTilemap,
    ptRangeText->vX,
    ptRangeText->vY,
    ptRangeText->vR,
    ptRangeText->vG,
    ptRangeText->vB,
    ptRangeText->vA,
    ptRangeText->vZ,
    ptRangeText->bQGraphicFlags | 0x40000000,
    ptRangeText->nPri);
}

// source: j/0/weapons/sniperoverlay.c:577  [anchor-mhash]
void __cdecl SniperOverlay_DrawCompass(
        struct SniperOverlay_s *ptSniperOverlay,
        float vCompassWidth,
        float vXPos,
        float vYPos)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vZ; };
    struct { char igi2_o1[4]; unsigned int v33; };
    struct { char igi2_o2[4]; unsigned int v34; };
    struct { char igi2_o3[8]; int nPri; };
    struct { char igi2_o4[8]; int v36; };
    struct { char igi2_o5[32]; float vX; };
    struct { char igi2_o6[32]; float vXa; };
    struct { char igi2_o7[36]; int nWidth; };
    struct { char igi2_o8[36]; int nWidtha; };
    struct { char igi2_o9[40]; int vTextHeight; };
    struct { char igi2_o10[40]; float vTextHeighta; };
    struct { char igi2_o11[44]; __int64 vOrientation; };
    struct { char igi2_o12[52]; __int64 vX1; };
    struct { char igi2_o13[64]; float vPitch; };
    struct { char igi2_o14[68]; __int64 vY1; };
    struct { char igi2_o15[76]; float v47; };
    struct { char igi2_o16[80]; struct ClippingRect_s tRect; };
    struct { char igi2_o17[104]; struct QVertexStripContext_s tStrip; };
    struct { char igi2_o18[124]; struct QVertex_s atQVertex[3]; };
    char igi2_extent[240];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct SniperOverlay_s *v4; // edi
  double v5; // st7
  struct QTilemap_s *ptQTilemap; // eax
  struct QSprite_s *ptQSprite; // ecx
  int nHeight; // eax
  int v9; // edx
  double v10; // st7
  int v11; // ebx
  struct StaticTilemap_s *v12; // esi
  double v13; // st7
  double v14; // st7
  struct QTilemap_s *v15; // ebx
  int v16; // edx
  __int16 *anGraphicWidth; // ecx
  int v18; // edi
  double v19; // st7
  double v20; // st6
  float vA; // edx
  float v22; // edi
  float v23; // eax
  double v24; // st7
  unsigned int bQGraphicFlags; // ecx
  struct QTilemap_s *v26; // ebx
  float v27; // eax
  float v28; // edx
  float v29; // ecx
  double v30; // st7
  double v31; // st7

  v4 = ptSniperOverlay;
  igi2_frame.nWidtha = Display_tActiveMode.nWidth;
  Real32x3_GetAngles(&ptSniperOverlay->tDirection, &igi2_frame.vPitch, (float *)&igi2_frame.vOrientation);
  v5 = (double)igi2_frame.nWidtha;
  ptQTilemap = ptSniperOverlay->aptDirectionText[0]->ptQTilemap;
  ptQSprite = ptQTilemap->ptQSprite;
  nHeight = ptQTilemap->nHeight;
  v9 = ptQSprite->atQAnimframe[ptQSprite->nQAnimframes].nHeight;
  igi2_frame.tRect.vX = vXPos * v5;
  igi2_frame.tRect.vY = (double)Display_tActiveMode.nHeight * vYPos;
  igi2_frame.tRect.vWidth = v5 * vCompassWidth;
  igi2_frame.tRect.vHeight = (double)(nHeight * v9) + (double)(nHeight * v9) + 26.0;
  igi2_frame.tRect.vHalfWidth = igi2_frame.tRect.vWidth * 0.5;
  igi2_frame.tRect.vHalfHeight = igi2_frame.tRect.vHeight * 0.5;
  igi2_frame.vPitch = igi2_frame.tRect.vWidth * 0.015625;
  v10 = *(float *)&igi2_frame.vOrientation;
  if ( *(float *)&igi2_frame.vOrientation < 0.0 )
    v10 = v10 + 6.2831854820251465;
  v11 = 0;
  igi2_frame.nWidth = 0;
  igi2_frame.vX = igi2_frame.tRect.vWidth * v10 * 0.15915493667125702;
  igi2_frame.v47 = igi2_frame.tRect.vHalfHeight + igi2_frame.tRect.vY;
  do
  {
    v12 = nullptr;
    if ( (v11 & 0xF) != 0 )
    {
      if ( (v11 & 7) != 0 )
        v13 = 4.0;
      else
        v13 = 8.0;
    }
    else
    {
      v13 = 12.0;
      v12 = v4->aptDirectionText[v11 >> 4];
    }
    v14 = v13 * 0.5;
    *(float *)&igi2_frame.vOrientation = igi2_frame.tRect.vHalfHeight + v14 + igi2_frame.tRect.vY;
    *(float *)&igi2_frame.vX1 = igi2_frame.vX + igi2_frame.tRect.vX;
    *(float *)&igi2_frame.vY1 = igi2_frame.v47 - v14;
    QSprite_RegisterLine(
      *(float *)&igi2_frame.vX1,
      *(float *)&igi2_frame.vY1,
      1.0,
      *(float *)&igi2_frame.vX1,
      *(float *)&igi2_frame.vOrientation,
      1.0,
      0.0,
      0.0,
      0.0,
      0.0,
      0.0,
      0.0,
      1.0,
      1.0,
      0,
      1);
    if ( v12 )
    {
      v15 = v12->ptQTilemap;
      v16 = 0;
      igi2_frame.vTextHeight = 0;
      if ( v12->ptQTilemap->nHeight > 0 )
      {
        anGraphicWidth = v15->anGraphicWidth;
        v18 = v12->ptQTilemap->nHeight;
        do
        {
          if ( *anGraphicWidth > v16 )
            v16 = *anGraphicWidth;
          ++anGraphicWidth;
          --v18;
        }
        while ( v18 );
        igi2_frame.vTextHeight = v16;
      }
      v19 = (double)igi2_frame.vTextHeight;
      igi2_frame.nPri = v12->nPri;
      v20 = (double)(v15->nHeight * v15->ptQSprite->atQAnimframe[v15->ptQSprite->nQAnimframes].nHeight);
      vA = v12->vA;
      v12->vR = 0.0;
      v12->vG = 0.0;
      igi2_frame.vTextHeighta = v20;
      v12->vB = 0.0;
      igi2_frame.vX1 = (__int64)(*(float *)&igi2_frame.vX1 - 0.5 * v19);
      igi2_frame.v33 = v12->bQGraphicFlags | 0x40000000;
      *(float *)&igi2_frame.vX1 = (float)(int)igi2_frame.vX1;
      v12->vX = *(float *)&igi2_frame.vX1;
      v22 = *(float *)&igi2_frame.vX1;
      igi2_frame.vY1 = (__int64)(*(float *)&igi2_frame.vY1 - igi2_frame.vTextHeighta - 2.0);
      igi2_frame.vZ = v12->vZ;
      *(float *)&igi2_frame.vY1 = (float)(int)igi2_frame.vY1;
      v23 = *(float *)&igi2_frame.vY1;
      v12->vY = *(float *)&igi2_frame.vY1;
      QTilemap_Register(v15, v22, v23, 0.0, 0.0, 0.0, vA, igi2_frame.vZ, igi2_frame.v33, igi2_frame.nPri);
      v24 = *(float *)&igi2_frame.vOrientation + 2.0;
      v12->vX = v22;
      igi2_frame.vOrientation = (__int64)v24;
      bQGraphicFlags = v12->bQGraphicFlags;
      v26 = v12->ptQTilemap;
      igi2_frame.v36 = v12->nPri;
      v27 = v12->vA;
      LODWORD(igi2_frame.vOrientation) = (__int64)v24;
      v28 = v12->vZ;
      igi2_frame.v34 = bQGraphicFlags | 0x40000000;
      *(float *)&igi2_frame.vOrientation = (float)(int)igi2_frame.vOrientation;
      v29 = *(float *)&igi2_frame.vOrientation;
      v12->vY = *(float *)&igi2_frame.vOrientation;
      v12->vR = 0.0;
      v12->vG = 0.0;
      v12->vB = 0.0;
      QTilemap_Register(v26, v22, v29, 0.0, 0.0, 0.0, v27, v28, igi2_frame.v34, igi2_frame.v36);
      v11 = igi2_frame.nWidth;
      v4 = ptSniperOverlay;
    }
    v30 = igi2_frame.vX + igi2_frame.vPitch;
    igi2_frame.vX = v30;
    if ( v30 >= igi2_frame.tRect.vWidth )
      igi2_frame.vX = igi2_frame.vX - igi2_frame.tRect.vWidth;
    igi2_frame.nWidth = ++v11;
  }
  while ( v11 < 64 );
  igi2_frame.atQVertex[0].vA = 1.0;
  igi2_frame.atQVertex[0].vR = 0.0;
  igi2_frame.atQVertex[0].vG = 0.0;
  igi2_frame.atQVertex[0].vB = 0.0;
  igi2_frame.vXa = igi2_frame.tRect.vHalfWidth + igi2_frame.tRect.vX;
  igi2_frame.atQVertex[0].vU = 0.0;
  igi2_frame.atQVertex[0].vV = 0.0;
  igi2_frame.atQVertex[0].vZ = 1.0;
  qmemcpy(&igi2_frame.atQVertex[1], igi2_frame.atQVertex, sizeof(struct QVertex_s));
  qmemcpy(&igi2_frame.atQVertex[2], igi2_frame.atQVertex, sizeof(struct QVertex_s));
  igi2_frame.atQVertex[0].vY = igi2_frame.tRect.vY + 4.0;
  igi2_frame.vPitch = igi2_frame.vXa - 4.0;
  igi2_frame.atQVertex[1].vX = igi2_frame.vPitch;
  igi2_frame.v47 = igi2_frame.vXa + 4.0;
  igi2_frame.atQVertex[2].vX = igi2_frame.v47;
  igi2_frame.atQVertex[0].vX = igi2_frame.vXa;
  igi2_frame.tStrip.atQVertex = igi2_frame.atQVertex;
  igi2_frame.atQVertex[1].vY = igi2_frame.tRect.vY;
  igi2_frame.tStrip.bFlags = (unsigned int)&MTP_atLODVirModel[3].atBoneVertexRefs[26].atVertexRefs[479];
  igi2_frame.tStrip.isLine = 0;
  igi2_frame.tStrip.nDepth = 0;
  igi2_frame.tStrip.nStripLength = 3;
  QVertex_ptActiveTexture = nullptr;
  igi2_frame.atQVertex[2].vY = igi2_frame.tRect.vY;
  RenderMode_tActiveRenderMode.apfRenderModeMethod[QVertex_eRegisterQVertexStripMethod](&igi2_frame.tStrip);
  v31 = igi2_frame.tRect.vHeight + igi2_frame.tRect.vY;
  igi2_frame.atQVertex[0].vX = igi2_frame.vXa;
  igi2_frame.atQVertex[1].vX = igi2_frame.vPitch;
  igi2_frame.atQVertex[0].vY = v31 - 4.0;
  igi2_frame.atQVertex[2].vX = igi2_frame.v47;
  igi2_frame.atQVertex[1].vY = v31;
  igi2_frame.atQVertex[2].vY = v31;
  RenderMode_tActiveRenderMode.apfRenderModeMethod[QVertex_eRegisterQVertexStripMethod](&igi2_frame.tStrip);
}

// source: j/0/weapons/sniperoverlay.c:731  [anchor-hash]
void __cdecl SniperOverlay_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("SniperOverlay", 312, BaseQTaskType, 0, 0);
  SniperOverlay_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(
    v1,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveNoChildrenHandler);
  QTask_LinkQTaskEventHandlerFn(v1, StatusScreen_eStatusDisplayQTaskEvent, SniperOverlay_StatusDisplayHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 0, SniperOverlay_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(v1, WeaponType_eCreateParametersQTaskEvent, SniperOverlay_CreateParameterHandler);
  QTask_LinkQTaskEventHandlerFn(v1, WeaponType_eDeleteParametersQTaskEvent, SniperOverlay_DeleteParameterHandler);
  QTask_LinkQTaskEventHandlerFn(v1, Weapon_ePositionOverlayQTaskEvent, SniperOverlay_PositionOverlayHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, SniperOverlay_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, Screen_eDrawQTaskEvent, SniperOverlay_DrawHandler);
  SniperOverlay_ptCornerSprite = GameFunctions_RegisterGameSprite((char *)&g_zMessage.tReceiveTimeBuffer.aReceiveTime[4]);
  Symbol_Register(
    "TASKTYPE_SNIPEROVERLAY",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)SniperOverlay_eQTaskType,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}

// source: j/0/weapons/sniperoverlay.c:766  [size]
void __cdecl SniperOverlay_Close()
{
  QTask_DeleteQTaskType(SniperOverlay_eQTaskType);
}

// source: j/0/weapons/sniperoverlay.c:780  [size]
unsigned __int16 __cdecl SniperOverlay_GetQTaskType()
{
  return SniperOverlay_eQTaskType;
}
