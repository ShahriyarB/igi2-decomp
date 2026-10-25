/* j/0/weapons/augsniperoverlay.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/weapons/augsniperoverlay.c:58  [size]
void __cdecl AugSniperOverlay_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: j/0/weapons/augsniperoverlay.c:73  [size]
void __cdecl AugSniperOverlay_DeleteHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: j/0/weapons/augsniperoverlay.c:89  [anchor-mhash]
void __cdecl AugSniperOverlay_Draw(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vX1; };
    struct { float vX1a; };
    struct { char igi2_o2[4]; float v21; };
    struct { char igi2_o3[80]; float vX; };
    struct { char igi2_o4[80]; float vXa; };
    struct { char igi2_o5[80]; float vXb; };
    struct { char igi2_o6[84]; float v25; };
    struct { char igi2_o7[88]; int vY; };
    struct { char igi2_o8[92]; float v27; };
    struct { char igi2_o9[96]; int nHeight; };
    struct { char igi2_o10[100]; float vY2; };
    struct { char igi2_o11[104]; float vY1; };
    struct { char igi2_o12[108]; float vOffset; };
    struct { char igi2_o13[112]; int iI[2]; };
    struct { char igi2_o14[120]; int nWidth; };
    struct { char igi2_o15[124]; float vX2; };
    struct { char igi2_o16[128]; __int64 avY; };
    struct { char igi2_o17[136]; float avAngle[2]; };
    char igi2_extent[144];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int nQAnimframes; // eax
  int v2; // edx
  double v3; // st7
  float v4; // esi
  float v5; // edi
  float v6; // ebx
  float v7; // ebp
  int v8; // esi
  float v9; // edi
  int v10; // eax
  long double v11; // st7
  float v12; // ebx
  int v13; // esi
  int v14; // edi
  float v15; // eax
  int v16; // esi
  int v17; // eax
  long double v18; // st7

  igi2_frame.nHeight = Display_tActiveMode.nHeight;
  igi2_frame.nWidth = Display_tActiveMode.nWidth;
  nQAnimframes = AugSniperOverlay_ptCornerSprite->tQSprite.nQAnimframes;
  *(float *)igi2_frame.iI = (float)Display_tActiveMode.nWidth;
  v2 = AugSniperOverlay_ptCornerSprite->tQSprite.atQAnimframe[nQAnimframes].nWidth;
  igi2_frame.avAngle[1] = 0.0;
  igi2_frame.vOffset = *(float *)igi2_frame.iI / (double)v2;
  v3 = (double)Display_tActiveMode.nHeight;
  igi2_frame.v25 = v3;
  *(float *)&igi2_frame.avY = v3 * 0.5;
  v4 = *(float *)&igi2_frame.avY;
  igi2_frame.vY1 = *(float *)igi2_frame.iI * 0.5;
  v5 = igi2_frame.vY1;
  *(float *)&igi2_frame.vY = -igi2_frame.vOffset;
  v6 = *(float *)&igi2_frame.vY;
  QSprite_Register4(
    &AugSniperOverlay_ptCornerSprite->tQSprite,
    *(float *)&igi2_frame.vY,
    *(float *)&igi2_frame.vY,
    igi2_frame.vY1,
    *(float *)&igi2_frame.vY,
    *(float *)&igi2_frame.vY,
    *(float *)&igi2_frame.avY,
    igi2_frame.vY1,
    *(float *)&igi2_frame.avY,
    128.0,
    128.0,
    128.0,
    0,
    (unsigned int)&MTP_atLODVirModel[45].atBoneVertexRefs[20].atVertexRefs[781],
    1);
  *(float *)&igi2_frame.avY = *(float *)igi2_frame.iI + igi2_frame.vOffset;
  v7 = *(float *)&igi2_frame.avY;
  QSprite_Register4(
    &AugSniperOverlay_ptCornerSprite->tQSprite,
    *(float *)&igi2_frame.avY,
    v6,
    v5,
    v6,
    *(float *)&igi2_frame.avY,
    v4,
    v5,
    v4,
    128.0,
    128.0,
    128.0,
    0,
    (unsigned int)&MTP_atLODVirModel[45].atBoneVertexRefs[20].atVertexRefs[781],
    1);
  *(float *)&igi2_frame.avY = igi2_frame.v25 + igi2_frame.vOffset;
  QSprite_Register4(
    &AugSniperOverlay_ptCornerSprite->tQSprite,
    v6,
    *(float *)&igi2_frame.avY,
    v5,
    *(float *)&igi2_frame.avY,
    v6,
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
    &AugSniperOverlay_ptCornerSprite->tQSprite,
    v7,
    *(float *)&igi2_frame.avY,
    v5,
    *(float *)&igi2_frame.avY,
    v7,
    v4,
    v5,
    v4,
    128.0,
    128.0,
    128.0,
    0,
    (unsigned int)&MTP_atLODVirModel[45].atBoneVertexRefs[20].atVertexRefs[781],
    1);
  igi2_frame.vY1 = (float)(igi2_frame.nWidth / 2);
  v8 = 1;
  igi2_frame.iI[0] = 1;
  igi2_frame.vOffset = (float)(igi2_frame.nHeight / 2);
  *(float *)&igi2_frame.avY = igi2_frame.v25 * 0.003000000026077032;
  v9 = *(float *)&igi2_frame.avY;
  do
  {
    igi2_frame.avAngle[0] = igi2_frame.avAngle[1];
    v10 = 0;
    igi2_frame.avAngle[1] = (double)igi2_frame.iI[0] * 0.13089969389957476;
    do
    {
      v11 = igi2_frame.avAngle[v10++];
      *(float *)&igi2_frame.iI[v10 + 1] = cos(v11) * igi2_frame.v25 * 0.4000000059604645 + igi2_frame.vY1;
      *(float *)((char *)&igi2_frame.vX2 + v10 * 4) = sin(igi2_frame.avAngle[v10 - 1]) * igi2_frame.v25 * 0.4000000059604645 + igi2_frame.vOffset;
    }
    while ( v10 < 2 );
    QSprite_RegisterLine(
      *(float *)&igi2_frame.nWidth,
      *(float *)&igi2_frame.avY,
      1.0,
      igi2_frame.vX2,
      *((float *)&igi2_frame.avY + 1),
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
    igi2_frame.iI[0] = ++v8;
  }
  while ( v8 <= 48 );
  v12 = igi2_frame.vOffset;
  v13 = (__int64)(igi2_frame.v25 * 0.20000000298023224);
  igi2_frame.avY = (__int64)((double)igi2_frame.nHeight * 0.015);
  v14 = igi2_frame.avY;
  *(float *)&igi2_frame.nWidth = igi2_frame.v25 * 0.4000000059604645;
  *(float *)&igi2_frame.nHeight = (float)(int)igi2_frame.avY;
  igi2_frame.vX = *(float *)&igi2_frame.nWidth + igi2_frame.vY1 - *(float *)&igi2_frame.nHeight * 0.5;
  *(float *)&igi2_frame.avY = igi2_frame.vX - (double)v13;
  QSprite_RegisterLine(
    *(float *)&igi2_frame.avY,
    igi2_frame.vOffset,
    1.0,
    igi2_frame.vX,
    igi2_frame.vOffset,
    1.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    1.0,
    *(float *)&igi2_frame.nHeight,
    (unsigned int)&MTP_atLODVirModel[87].atBoneVertexRefs[15].atVertexRefs[82],
    1);
  v15 = *(float *)&igi2_frame.avY;
  *(float *)&igi2_frame.avY = igi2_frame.v25 * 0.03999999910593033;
  *(_QWORD *)igi2_frame.iI = (__int64)(v15 - igi2_frame.vY1 - *(float *)&igi2_frame.avY);
  igi2_frame.vX1 = v15 - (double)igi2_frame.iI[0];
  QSprite_RegisterLine(
    igi2_frame.vX1,
    v12,
    1.0,
    v15,
    v12,
    1.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    1.0,
    1.0,
    (unsigned int)&MTP_atLODVirModel[87].atBoneVertexRefs[15].atVertexRefs[82],
    1);
  *(float *)&igi2_frame.nHeight = (float)v14;
  igi2_frame.vXa = igi2_frame.vY1 - *(float *)&igi2_frame.nWidth + *(float *)&igi2_frame.nHeight * 0.5;
  *(float *)igi2_frame.iI = (double)v13 + igi2_frame.vXa;
  QSprite_RegisterLine(
    *(float *)igi2_frame.iI,
    v12,
    1.0,
    igi2_frame.vXa,
    v12,
    1.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    1.0,
    *(float *)&igi2_frame.nHeight,
    (unsigned int)&MTP_atLODVirModel[3].atBoneVertexRefs[26].atVertexRefs[479],
    1);
  igi2_frame.vXb = *(float *)igi2_frame.iI;
  *(_QWORD *)igi2_frame.iI = (__int64)(igi2_frame.vY1 - *(float *)&igi2_frame.avY - *(float *)igi2_frame.iI);
  igi2_frame.vX1a = (double)igi2_frame.iI[0] + igi2_frame.vXb;
  QSprite_RegisterLine(
    igi2_frame.vX1a,
    v12,
    1.0,
    igi2_frame.vXb,
    v12,
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
  *(float *)&igi2_frame.vY = *(float *)&igi2_frame.nWidth + igi2_frame.vOffset - *(float *)&igi2_frame.nHeight * 0.5;
  *(float *)&igi2_frame.nWidth = *(float *)&igi2_frame.vY - (double)v13;
  QSprite_RegisterLine(
    igi2_frame.vY1,
    *(float *)&igi2_frame.nWidth,
    1.0,
    igi2_frame.vY1,
    *(float *)&igi2_frame.vY,
    1.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    1.0,
    *(float *)&igi2_frame.nHeight,
    (unsigned int)&MTP_atLODVirModel[3].atBoneVertexRefs[26].atVertexRefs[479],
    1);
  igi2_frame.vY = igi2_frame.nWidth;
  igi2_frame.avY = (__int64)(*(float *)&igi2_frame.nWidth - igi2_frame.vOffset - *(float *)&igi2_frame.avY);
  igi2_frame.v21 = *(float *)&igi2_frame.nWidth - (double)(int)igi2_frame.avY;
  QSprite_RegisterLine(
    igi2_frame.vY1,
    igi2_frame.v21,
    1.0,
    igi2_frame.vY1,
    *(float *)&igi2_frame.nWidth,
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
  v16 = 1;
  igi2_frame.iI[0] = 1;
  *(float *)&igi2_frame.avY = igi2_frame.v25 * 0.004000000189989805;
  do
  {
    igi2_frame.avAngle[0] = igi2_frame.avAngle[1];
    v17 = 0;
    igi2_frame.avAngle[1] = (double)igi2_frame.iI[0] * 0.19634954084936215;
    do
    {
      v18 = igi2_frame.avAngle[v17++];
      *(float *)((char *)&igi2_frame.v25 + v17 * 4) = cos(v18) * igi2_frame.v25 * 0.03999999910593033 + igi2_frame.vY1;
      *(float *)((char *)&igi2_frame.v27 + v17 * 4) = sin(igi2_frame.avAngle[v17 - 1]) * igi2_frame.v25 * 0.03999999910593033 + igi2_frame.vOffset;
    }
    while ( v17 < 2 );
    if ( *(float *)&igi2_frame.avY <= 1.0 )
      *(float *)&igi2_frame.nWidth = 1.0;
    else
      igi2_frame.nWidth = igi2_frame.avY;
    QSprite_RegisterLine(
      *(float *)&igi2_frame.vY,
      *(float *)&igi2_frame.nHeight,
      1.0,
      igi2_frame.v27,
      igi2_frame.vY2,
      1.0,
      0.0,
      0.0,
      0.0,
      0.0,
      0.0,
      0.0,
      1.0,
      *(float *)&igi2_frame.nWidth,
      (unsigned int)&MTP_atLODVirModel[87].atBoneVertexRefs[15].atVertexRefs[82],
      1);
    igi2_frame.iI[0] = ++v16;
  }
  while ( v16 <= 32 );
}

// source: j/0/weapons/augsniperoverlay.c:322  [size]
void __cdecl AugSniperOverlay_StatusDisplayHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct TransContext_s *v2; // eax

  v2 = TransContext_Create(
         (struct TransContext_s *)&ptQTask[3].tQTaskRefList.ptMiddle,
         (struct real32x9_t *)&ptQTask[2].tQTaskRefList,
         (struct real64x3_t *)&ptQTask[1].tQTaskRefList.ptMiddle,
         1.0);
  TransContext_SetActiveTransContext(v2);
  AugSniperOverlay_Draw(ptQTask);
  TransContext_isValid = 0;
}

// source: j/0/weapons/augsniperoverlay.c:347  [size]
void __cdecl AugSniperOverlay_DrawHandler(struct QTask_s *ptQTask)
{
  struct TransContext_s *v1; // eax

  v1 = TransContext_Create(
         (struct TransContext_s *)&ptQTask[3].tQTaskRefList.ptMiddle,
         (struct real32x9_t *)&ptQTask[2].tQTaskRefList,
         (struct real64x3_t *)&ptQTask[1].tQTaskRefList.ptMiddle,
         1.0);
  TransContext_SetActiveTransContext(v1);
  AugSniperOverlay_Draw(ptQTask);
  TransContext_isValid = 0;
}

// source: j/0/weapons/augsniperoverlay.c:364  [size]
unsigned __int16 __cdecl AugSniperOverlay_GetQTaskType()
{
  return AugSniperOverlay_eQTaskType;
}

// source: j/0/weapons/augsniperoverlay.c:377  [anchor-hash]
void __cdecl AugSniperOverlay_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("AugSniperOverlay", 312, BaseQTaskType, 0, 0);
  AugSniperOverlay_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(
    v1,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveNoChildrenHandler);
  QTask_LinkQTaskEventHandlerFn(v1, StatusScreen_eStatusDisplayQTaskEvent, AugSniperOverlay_StatusDisplayHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 0, (void (__cdecl *)(struct QTask_s *, void *))AugSniperOverlay_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, (void (__cdecl *)(struct QTask_s *))AugSniperOverlay_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, Screen_eDrawQTaskEvent, AugSniperOverlay_DrawHandler);
  AugSniperOverlay_ptCornerSprite = GameFunctions_RegisterGameSprite((char *)&g_zMessage.tReceiveTimeBuffer.aReceiveTime[4]);
  Symbol_Register(
    "TASKTYPE_AUGSNIPEROVERLAY",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)AugSniperOverlay_eQTaskType,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}

// source: j/0/weapons/augsniperoverlay.c:405  [size]
void __cdecl AugSniperOverlay_Close()
{
  QTask_DeleteQTaskType(AugSniperOverlay_eQTaskType);
}
