/* j/0/weapons/psg1sniperoverlay.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/weapons/psg1sniperoverlay.c:59  [size]
void __cdecl Psg1SniperOverlay_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  QTask_TriggerBaseHandler(ptQTask, ptQTask->eQTaskType, 0, pxContext);
}

// source: j/0/weapons/psg1sniperoverlay.c:75  [size]
void __cdecl Psg1SniperOverlay_DeleteHandler(struct QTask_s *ptQTask)
{
  QTask_TriggerBaseHandlerNoContext(ptQTask, ptQTask->eQTaskType, 2);
}

// source: j/0/weapons/psg1sniperoverlay.c:93  [anchor-mhash]
void __cdecl Psg1SniperOverlay_Draw(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vX1; };
    struct { float vX1a; };
    struct { char igi2_o2[4]; float v24; };
    struct { char igi2_o3[4]; float v25; };
    struct { char igi2_o4[12]; float v26; };
    struct { char igi2_o5[16]; float vY2; };
    struct { char igi2_o6[80]; float vX; };
    struct { char igi2_o7[80]; float vXa; };
    struct { char igi2_o8[80]; float vXb; };
    struct { char igi2_o9[80]; float vXc; };
    struct { char igi2_o10[84]; int vY; };
    struct { char igi2_o11[84]; float vYa; };
    struct { char igi2_o12[84]; float vYb; };
    struct { char igi2_o13[84]; float vYc; };
    struct { char igi2_o14[88]; float v36; };
    struct { char igi2_o15[92]; float avAngle[2]; };
    struct { char igi2_o16[100]; int nHeight; };
    struct { char igi2_o17[104]; int nWidth; };
    struct { char igi2_o18[108]; int iI; };
    struct { char igi2_o19[112]; float vOffset; };
    struct { char igi2_o20[116]; float vX2; };
    struct { char igi2_o21[120]; struct QSprite_s *v43; };
    struct { char igi2_o22[124]; float vY1; };
    struct { char igi2_o23[128]; __int64 nLineWidth; };
    char igi2_extent[136];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int nQAnimframes; // edx
  struct QAnimframe_s *atQAnimframe; // eax
  int v3; // edx
  double v4; // st7
  float v5; // esi
  float v6; // edi
  int v7; // ebx
  int v8; // esi
  float v9; // edi
  int v10; // eax
  long double v11; // st7
  double v12; // st7
  float v13; // esi
  double v14; // st7
  float v15; // esi
  float v16; // edi
  struct QSprite_s *v17; // ebx
  float v18; // ebp
  double v19; // st7
  double v20; // st7
  double v21; // st7

  igi2_frame.nHeight = Display_tActiveMode.nHeight;
  igi2_frame.nWidth = Display_tActiveMode.nWidth;
  nQAnimframes = Psg1SniperOverlay_ptCornerSprite->tQSprite.nQAnimframes;
  atQAnimframe = Psg1SniperOverlay_ptCornerSprite->tQSprite.atQAnimframe;
  *(float *)&igi2_frame.v43 = (float)Display_tActiveMode.nWidth;
  v3 = atQAnimframe[nQAnimframes].nWidth;
  igi2_frame.avAngle[1] = 0.0;
  igi2_frame.vOffset = *(float *)&igi2_frame.v43 / (double)v3;
  v4 = (double)Display_tActiveMode.nHeight;
  igi2_frame.v36 = v4;
  *(float *)&igi2_frame.nLineWidth = v4 * 0.5;
  v5 = *(float *)&igi2_frame.nLineWidth;
  igi2_frame.vY1 = *(float *)&igi2_frame.v43 * 0.5;
  v6 = igi2_frame.vY1;
  *(float *)&igi2_frame.iI = -igi2_frame.vOffset;
  v7 = igi2_frame.iI;
  QSprite_Register4(
    &Psg1SniperOverlay_ptCornerSprite->tQSprite,
    *(float *)&igi2_frame.iI,
    *(float *)&igi2_frame.iI,
    igi2_frame.vY1,
    *(float *)&igi2_frame.iI,
    *(float *)&igi2_frame.iI,
    *(float *)&igi2_frame.nLineWidth,
    igi2_frame.vY1,
    *(float *)&igi2_frame.nLineWidth,
    128.0,
    128.0,
    128.0,
    0,
    (unsigned int)&MTP_atLODVirModel[45].atBoneVertexRefs[20].atVertexRefs[781],
    1);
  *(float *)&igi2_frame.nLineWidth = *(float *)&igi2_frame.v43 + igi2_frame.vOffset;
  QSprite_Register4(
    &Psg1SniperOverlay_ptCornerSprite->tQSprite,
    *(float *)&igi2_frame.nLineWidth,
    *(float *)&v7,
    v6,
    *(float *)&v7,
    *(float *)&igi2_frame.nLineWidth,
    v5,
    v6,
    v5,
    128.0,
    128.0,
    128.0,
    0,
    (unsigned int)&MTP_atLODVirModel[45].atBoneVertexRefs[20].atVertexRefs[781],
    1);
  igi2_frame.vOffset = igi2_frame.v36 + igi2_frame.vOffset;
  QSprite_Register4(
    &Psg1SniperOverlay_ptCornerSprite->tQSprite,
    *(float *)&v7,
    igi2_frame.vOffset,
    v6,
    igi2_frame.vOffset,
    *(float *)&v7,
    v5,
    v6,
    v5,
    128.0,
    128.0,
    128.0,
    0,
    (unsigned int)&MTP_atLODVirModel[45].atBoneVertexRefs[20].atVertexRefs[781],
    1);
  QSprite_Register4(
    &Psg1SniperOverlay_ptCornerSprite->tQSprite,
    *(float *)&igi2_frame.nLineWidth,
    igi2_frame.vOffset,
    v6,
    igi2_frame.vOffset,
    *(float *)&igi2_frame.nLineWidth,
    v5,
    v6,
    v5,
    128.0,
    128.0,
    128.0,
    0,
    (unsigned int)&MTP_atLODVirModel[45].atBoneVertexRefs[20].atVertexRefs[781],
    1);
  *(float *)&igi2_frame.nWidth = (float)(igi2_frame.nWidth / 2);
  v8 = 1;
  igi2_frame.iI = 1;
  *(float *)&igi2_frame.nHeight = (float)(igi2_frame.nHeight / 2);
  *(float *)&igi2_frame.nLineWidth = igi2_frame.v36 * 0.003000000026077032;
  v9 = *(float *)&igi2_frame.nLineWidth;
  do
  {
    igi2_frame.avAngle[0] = igi2_frame.avAngle[1];
    v10 = 0;
    igi2_frame.avAngle[1] = (double)igi2_frame.iI * 0.13089969389957476;
    do
    {
      v11 = igi2_frame.avAngle[v10++];
      *(float *)((char *)&igi2_frame.iI + v10 * 4) = cos(v11) * igi2_frame.v36 * 0.4000000059604645 + *(float *)&igi2_frame.nWidth;
      *(float *)((char *)&igi2_frame.vY1 + v10 * 4) = sin(igi2_frame.avAngle[v10 - 1]) * igi2_frame.v36 * 0.4000000059604645 + *(float *)&igi2_frame.nHeight;
    }
    while ( v10 < 2 );
    QSprite_RegisterLine(
      igi2_frame.vOffset,
      *(float *)&igi2_frame.nLineWidth,
      1.0,
      igi2_frame.vX2,
      *((float *)&igi2_frame.nLineWidth + 1),
      1.0,
      0.0,
      0.0,
      0.0,
      0.0,
      0.0,
      0.0,
      1.0,
      v9,
      (unsigned int)&MTP_atLODVirModel[87].atBoneVertexRefs[15].atVertexRefs[82],
      1);
    igi2_frame.iI = ++v8;
  }
  while ( v8 <= 48 );
  LODWORD(igi2_frame.avAngle[0]) = (__int64)(igi2_frame.v36 * 0.18000000715255737);
  igi2_frame.nLineWidth = (__int64)(igi2_frame.v36 * 0.02500000037252903);
  *(float *)&igi2_frame.iI = igi2_frame.v36 * 0.4000000059604645;
  v12 = (double)(int)igi2_frame.nLineWidth;
  *(float *)&igi2_frame.nLineWidth = v12;
  v13 = *(float *)&igi2_frame.nLineWidth;
  igi2_frame.vOffset = v12 * 0.5;
  igi2_frame.vXa = *(float *)&igi2_frame.iI + *(float *)&igi2_frame.nWidth - igi2_frame.vOffset;
  igi2_frame.avAngle[0] = (float)SLODWORD(igi2_frame.avAngle[0]);
  igi2_frame.vX1 = igi2_frame.vXa - igi2_frame.avAngle[0];
  QSprite_RegisterLine(
    igi2_frame.vX1,
    *(float *)&igi2_frame.nHeight,
    1.0,
    igi2_frame.vXa,
    *(float *)&igi2_frame.nHeight,
    1.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    1.0,
    *(float *)&igi2_frame.nLineWidth,
    (unsigned int)&MTP_atLODVirModel[87].atBoneVertexRefs[15].atVertexRefs[82],
    1);
  igi2_frame.vXb = *(float *)&igi2_frame.nWidth - *(float *)&igi2_frame.iI + igi2_frame.vOffset;
  igi2_frame.vX1a = igi2_frame.avAngle[0] + igi2_frame.vXb;
  QSprite_RegisterLine(
    igi2_frame.vX1a,
    *(float *)&igi2_frame.nHeight,
    1.0,
    igi2_frame.vXb,
    *(float *)&igi2_frame.nHeight,
    1.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    1.0,
    v13,
    (unsigned int)&MTP_atLODVirModel[3].atBoneVertexRefs[26].atVertexRefs[479],
    1);
  igi2_frame.vYa = *(float *)&igi2_frame.iI + *(float *)&igi2_frame.nHeight - igi2_frame.vOffset;
  igi2_frame.v24 = igi2_frame.vYa - igi2_frame.avAngle[0];
  QSprite_RegisterLine(
    *(float *)&igi2_frame.nWidth,
    igi2_frame.v24,
    1.0,
    *(float *)&igi2_frame.nWidth,
    igi2_frame.vYa,
    1.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    1.0,
    v13,
    (unsigned int)&MTP_atLODVirModel[3].atBoneVertexRefs[26].atVertexRefs[479],
    1);
  igi2_frame.vYb = *(float *)&igi2_frame.nHeight - *(float *)&igi2_frame.iI + igi2_frame.vOffset;
  igi2_frame.v25 = igi2_frame.avAngle[0] + igi2_frame.vYb;
  QSprite_RegisterLine(
    *(float *)&igi2_frame.nWidth,
    igi2_frame.v25,
    1.0,
    *(float *)&igi2_frame.nWidth,
    igi2_frame.vYb,
    1.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    1.0,
    v13,
    (unsigned int)&MTP_atLODVirModel[3].atBoneVertexRefs[26].atVertexRefs[479],
    1);
  igi2_frame.nLineWidth = (__int64)(igi2_frame.v36 * 0.800000011920929);
  igi2_frame.vXc = igi2_frame.vY1 - *(float *)&igi2_frame.iI;
  igi2_frame.avAngle[0] = (float)(int)igi2_frame.nLineWidth;
  igi2_frame.v26 = igi2_frame.avAngle[0] + igi2_frame.vXc;
  QSprite_RegisterLine(
    igi2_frame.vXc,
    *(float *)&igi2_frame.nHeight,
    1.0,
    igi2_frame.v26,
    *(float *)&igi2_frame.nHeight,
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
  igi2_frame.vYc = igi2_frame.v36 * 0.10000000149011612;
  igi2_frame.vY2 = igi2_frame.avAngle[0] + igi2_frame.vYc;
  QSprite_RegisterLine(
    *(float *)&igi2_frame.nWidth,
    igi2_frame.vYc,
    1.0,
    *(float *)&igi2_frame.nWidth,
    igi2_frame.vY2,
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
  igi2_frame.vY = igi2_frame.nHeight;
  igi2_frame.nLineWidth = (__int64)(igi2_frame.v36 * 0.20000000298023224);
  igi2_frame.vX = igi2_frame.vY1;
  LODWORD(igi2_frame.avAngle[0]) = igi2_frame.nLineWidth;
  igi2_frame.iI = 1;
  v14 = *(float *)&igi2_frame.v43 * 0.009999999776482582 * 0.5;
  igi2_frame.v36 = v14;
  *(float *)&igi2_frame.nLineWidth = v14 + *(float *)&igi2_frame.nHeight;
  v15 = *(float *)&igi2_frame.nLineWidth;
  igi2_frame.vY1 = *(float *)&igi2_frame.nHeight - igi2_frame.v36;
  v16 = igi2_frame.vY1;
  *(float *)&igi2_frame.v43 = igi2_frame.v36 + igi2_frame.vX;
  v17 = igi2_frame.v43;
  igi2_frame.avAngle[0] = (float)SLODWORD(igi2_frame.avAngle[0]);
  igi2_frame.vOffset = igi2_frame.vX - igi2_frame.v36;
  v18 = igi2_frame.vOffset;
  do
  {
    *(float *)&igi2_frame.nWidth = (double)igi2_frame.iI * igi2_frame.avAngle[0] * 0.20000000298023224;
    v19 = igi2_frame.vX - *(float *)&igi2_frame.nWidth;
    *(float *)&igi2_frame.nLineWidth = igi2_frame.v36 + v19;
    igi2_frame.vY1 = v19 - igi2_frame.v36;
    QSprite_Register4(
      &Psg1SniperOverlay_ptMilDotSprite->tQSprite,
      igi2_frame.vY1,
      v16,
      *(float *)&igi2_frame.nLineWidth,
      v16,
      igi2_frame.vY1,
      v15,
      *(float *)&igi2_frame.nLineWidth,
      v15,
      128.0,
      128.0,
      128.0,
      0,
      (unsigned int)&MTP_atLODVirModel[45].atBoneVertexRefs[20].atVertexRefs[781],
      1);
    v20 = *(float *)&igi2_frame.nWidth + igi2_frame.v36;
    *(float *)&igi2_frame.nLineWidth = v20;
    igi2_frame.vY1 = v20 + igi2_frame.vX;
    *(float *)&igi2_frame.v43 = *(float *)&igi2_frame.nWidth + igi2_frame.vX - igi2_frame.v36;
    QSprite_Register4(
      &Psg1SniperOverlay_ptMilDotSprite->tQSprite,
      *(float *)&igi2_frame.v43,
      v16,
      igi2_frame.vY1,
      v16,
      *(float *)&igi2_frame.v43,
      v15,
      igi2_frame.vY1,
      v15,
      128.0,
      128.0,
      128.0,
      0,
      (unsigned int)&MTP_atLODVirModel[45].atBoneVertexRefs[20].atVertexRefs[781],
      1);
    v21 = *(float *)&igi2_frame.vY - *(float *)&igi2_frame.nWidth;
    igi2_frame.vY1 = igi2_frame.v36 + v21;
    *(float *)&igi2_frame.v43 = v21 - igi2_frame.v36;
    QSprite_Register4(
      &Psg1SniperOverlay_ptMilDotSprite->tQSprite,
      v18,
      *(float *)&igi2_frame.v43,
      v18,
      igi2_frame.vY1,
      *(float *)&v17,
      *(float *)&igi2_frame.v43,
      *(float *)&v17,
      igi2_frame.vY1,
      128.0,
      128.0,
      128.0,
      0,
      (unsigned int)&MTP_atLODVirModel[45].atBoneVertexRefs[20].atVertexRefs[781],
      1);
    *(float *)&igi2_frame.nLineWidth = *(float *)&igi2_frame.nLineWidth + *(float *)&igi2_frame.vY;
    igi2_frame.vY1 = *(float *)&igi2_frame.nWidth + *(float *)&igi2_frame.vY - igi2_frame.v36;
    QSprite_Register4(
      &Psg1SniperOverlay_ptMilDotSprite->tQSprite,
      v18,
      igi2_frame.vY1,
      v18,
      *(float *)&igi2_frame.nLineWidth,
      *(float *)&v17,
      igi2_frame.vY1,
      *(float *)&v17,
      *(float *)&igi2_frame.nLineWidth,
      128.0,
      128.0,
      128.0,
      0,
      (unsigned int)&MTP_atLODVirModel[45].atBoneVertexRefs[20].atVertexRefs[781],
      1);
    ++igi2_frame.iI;
  }
  while ( igi2_frame.iI < 5 );
}

// source: j/0/weapons/psg1sniperoverlay.c:349  [size]
void __cdecl Psg1SniperOverlay_StatusDisplayHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct TransContext_s *v2; // eax

  v2 = TransContext_Create(
         (struct TransContext_s *)&ptQTask[3].tQTaskRefList.ptMiddle,
         (struct real32x9_t *)&ptQTask[2].tQTaskRefList,
         (struct real64x3_t *)&ptQTask[1].tQTaskRefList.ptMiddle,
         1.0);
  TransContext_SetActiveTransContext(v2);
  Psg1SniperOverlay_Draw(ptQTask);
  TransContext_isValid = 0;
}

// source: j/0/weapons/psg1sniperoverlay.c:374  [size]
void __cdecl Psg1SniperOverlay_DrawHandler(struct QTask_s *ptQTask)
{
  struct TransContext_s *v1; // eax

  v1 = TransContext_Create(
         (struct TransContext_s *)&ptQTask[3].tQTaskRefList.ptMiddle,
         (struct real32x9_t *)&ptQTask[2].tQTaskRefList,
         (struct real64x3_t *)&ptQTask[1].tQTaskRefList.ptMiddle,
         1.0);
  TransContext_SetActiveTransContext(v1);
  Psg1SniperOverlay_Draw(ptQTask);
  TransContext_isValid = 0;
}

// source: j/0/weapons/psg1sniperoverlay.c:391  [size]
unsigned __int16 __cdecl Psg1SniperOverlay_GetQTaskType()
{
  return Psg1SniperOverlay_eQTaskType;
}

// source: j/0/weapons/psg1sniperoverlay.c:404  [anchor-strings]
void __cdecl Psg1SniperOverlay_Open()
{
  unsigned __int16 v0; // si

  v0 = QTask_NewQTaskType("Psg1SniperOverlay", 312, SniperOverlay_eQTaskType, 0, 0);
  Psg1SniperOverlay_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveNoChildrenHandler);
  QTask_LinkQTaskEventHandlerFn(v0, StatusScreen_eStatusDisplayQTaskEvent, Psg1SniperOverlay_StatusDisplayHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, Psg1SniperOverlay_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, Psg1SniperOverlay_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Screen_eDrawQTaskEvent, Psg1SniperOverlay_DrawHandler);
  Psg1SniperOverlay_ptCornerSprite = GameFunctions_RegisterGameSprite((char *)&g_zMessage.tReceiveTimeBuffer.aReceiveTime[4]);
  Psg1SniperOverlay_ptMilDotSprite = GameFunctions_RegisterGameSprite("psg1dot.spr");
  Symbol_Register(
    "TASKTYPE_PSG1SNIPEROVERLAY",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)Psg1SniperOverlay_eQTaskType,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}

// source: j/0/weapons/psg1sniperoverlay.c:433  [size]
void __cdecl Psg1SniperOverlay_Close()
{
  QTask_DeleteQTaskType(Psg1SniperOverlay_eQTaskType);
}
