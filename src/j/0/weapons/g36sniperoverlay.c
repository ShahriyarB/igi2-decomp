/* j/0/weapons/g36sniperoverlay.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/weapons/g36sniperoverlay.c:59  [size]
void __cdecl G36SniperOverlay_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  QTask_TriggerBaseHandler(ptQTask, ptQTask->eQTaskType, 0, pxContext);
}

// source: j/0/weapons/g36sniperoverlay.c:75  [size]
void __cdecl G36SniperOverlay_DeleteHandler(struct QTask_s *ptQTask)
{
  QTask_TriggerBaseHandlerNoContext(ptQTask, ptQTask->eQTaskType, 2);
}

// source: j/0/weapons/g36sniperoverlay.c:93  [anchor-mhash]
void __cdecl G36SniperOverlay_Draw(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vX1; };
    struct { float vX1a; };
    struct { char igi2_o2[80]; float v19; };
    struct { char igi2_o3[84]; int vX; };
    struct { char igi2_o4[88]; float vX2; };
    struct { char igi2_o5[92]; int nWidth; };
    struct { char igi2_o6[96]; int vY; };
    struct { char igi2_o7[100]; float v24; };
    struct { char igi2_o8[104]; float vOffset; };
    struct { char igi2_o9[108]; float vY1; };
    struct { char igi2_o10[112]; float avX[2]; };
    struct { char igi2_o11[120]; __int64 avY; };
    struct { char igi2_o12[128]; float avAngle[2]; };
    char igi2_extent[136];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int nQAnimframes; // edx
  struct QAnimframe_s *atQAnimframe; // eax
  int v3; // edx
  double nHeight; // st7
  float v5; // esi
  float v6; // edi
  float v7; // ebx
  int v8; // esi
  float v9; // edi
  int v10; // eax
  long double v11; // st7
  double v12; // st7
  int v13; // esi
  int v14; // eax
  long double v15; // st7
  double v16; // st7

  igi2_frame.vX = Display_tActiveMode.nHeight;
  igi2_frame.nWidth = Display_tActiveMode.nWidth;
  nQAnimframes = G36SniperOverlay_ptCornerSprite->tQSprite.nQAnimframes;
  atQAnimframe = G36SniperOverlay_ptCornerSprite->tQSprite.atQAnimframe;
  igi2_frame.v24 = (float)Display_tActiveMode.nWidth;
  v3 = atQAnimframe[nQAnimframes].nWidth;
  igi2_frame.avAngle[1] = 0.0;
  igi2_frame.vOffset = igi2_frame.v24 / (double)v3;
  nHeight = (double)Display_tActiveMode.nHeight;
  igi2_frame.v19 = nHeight;
  igi2_frame.avX[0] = nHeight * 0.5;
  v5 = igi2_frame.avX[0];
  igi2_frame.vY1 = igi2_frame.v24 * 0.5;
  v6 = igi2_frame.vY1;
  *(float *)&igi2_frame.vY = -igi2_frame.vOffset;
  v7 = *(float *)&igi2_frame.vY;
  QSprite_Register4(
    &G36SniperOverlay_ptCornerSprite->tQSprite,
    *(float *)&igi2_frame.vY,
    *(float *)&igi2_frame.vY,
    igi2_frame.vY1,
    *(float *)&igi2_frame.vY,
    *(float *)&igi2_frame.vY,
    igi2_frame.avX[0],
    igi2_frame.vY1,
    igi2_frame.avX[0],
    128.0,
    128.0,
    128.0,
    0,
    (unsigned int)&MTP_atLODVirModel[45].atBoneVertexRefs[20].atVertexRefs[781],
    1);
  igi2_frame.avX[0] = igi2_frame.v24 + igi2_frame.vOffset;
  QSprite_Register4(
    &G36SniperOverlay_ptCornerSprite->tQSprite,
    igi2_frame.avX[0],
    v7,
    v6,
    v7,
    igi2_frame.avX[0],
    v5,
    v6,
    v5,
    128.0,
    128.0,
    128.0,
    0,
    (unsigned int)&MTP_atLODVirModel[45].atBoneVertexRefs[20].atVertexRefs[781],
    1);
  igi2_frame.vOffset = igi2_frame.v19 + igi2_frame.vOffset;
  QSprite_Register4(
    &G36SniperOverlay_ptCornerSprite->tQSprite,
    v7,
    igi2_frame.vOffset,
    v6,
    igi2_frame.vOffset,
    v7,
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
    &G36SniperOverlay_ptCornerSprite->tQSprite,
    igi2_frame.avX[0],
    igi2_frame.vOffset,
    v6,
    igi2_frame.vOffset,
    igi2_frame.avX[0],
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
  igi2_frame.vY = 1;
  igi2_frame.vOffset = (float)(igi2_frame.vX / 2);
  igi2_frame.avX[0] = igi2_frame.v19 * 0.003000000026077032;
  v9 = igi2_frame.avX[0];
  do
  {
    igi2_frame.avAngle[0] = igi2_frame.avAngle[1];
    v10 = 0;
    igi2_frame.avAngle[1] = (double)igi2_frame.vY * 0.13089969389957476;
    do
    {
      v11 = igi2_frame.avAngle[v10++];
      igi2_frame.avX[v10 - 1] = cos(v11) * igi2_frame.v19 * 0.4000000059604645 + *(float *)&igi2_frame.nWidth;
      igi2_frame.avX[v10 + 1] = sin(igi2_frame.avAngle[v10 - 1]) * igi2_frame.v19 * 0.4000000059604645 + igi2_frame.vOffset;
    }
    while ( v10 < 2 );
    QSprite_RegisterLine(
      igi2_frame.avX[0],
      *(float *)&igi2_frame.avY,
      1.0,
      igi2_frame.avX[1],
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
    igi2_frame.vY = ++v8;
  }
  while ( v8 <= 48 );
  v12 = igi2_frame.v19 * 0.4000000059604645;
  igi2_frame.vY1 = v12;
  *(float *)&igi2_frame.vX = v12 + *(float *)&igi2_frame.nWidth;
  igi2_frame.avX[0] = igi2_frame.v19 * 0.03999999910593033;
  igi2_frame.avY = (__int64)(*(float *)&igi2_frame.vX - *(float *)&igi2_frame.nWidth - igi2_frame.avX[0]);
  igi2_frame.vX1 = *(float *)&igi2_frame.vX - (double)(int)igi2_frame.avY;
  QSprite_RegisterLine(
    igi2_frame.vX1,
    igi2_frame.vOffset,
    1.0,
    *(float *)&igi2_frame.vX,
    igi2_frame.vOffset,
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
  *(float *)&igi2_frame.vX = *(float *)&igi2_frame.nWidth - igi2_frame.vY1;
  igi2_frame.avY = (__int64)(*(float *)&igi2_frame.nWidth - igi2_frame.avX[0] - *(float *)&igi2_frame.vX);
  igi2_frame.vX1a = (double)(int)igi2_frame.avY + *(float *)&igi2_frame.vX;
  QSprite_RegisterLine(
    igi2_frame.vX1a,
    igi2_frame.vOffset,
    1.0,
    *(float *)&igi2_frame.vX,
    igi2_frame.vOffset,
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
  v13 = 1;
  igi2_frame.vY = 1;
  igi2_frame.avX[0] = igi2_frame.v19 * 0.004000000189989805;
  do
  {
    igi2_frame.avAngle[0] = igi2_frame.avAngle[1];
    v14 = 0;
    igi2_frame.avAngle[1] = (double)igi2_frame.vY * 0.19634954084936215;
    do
    {
      v15 = igi2_frame.avAngle[v14++];
      *(float *)((char *)&igi2_frame.v19 + v14 * 4) = cos(v15) * igi2_frame.v19 * 0.03999999910593033 + *(float *)&igi2_frame.nWidth;
      igi2_frame.avX[v14 + 1] = sin(igi2_frame.avAngle[v14 - 1]) * igi2_frame.v19 * 0.03999999910593033 + igi2_frame.vOffset;
    }
    while ( v14 < 2 );
    if ( igi2_frame.avX[0] <= 1.0 )
      igi2_frame.vY1 = 1.0;
    else
      igi2_frame.vY1 = igi2_frame.avX[0];
    QSprite_RegisterLine(
      *(float *)&igi2_frame.vX,
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
      igi2_frame.vY1,
      (unsigned int)&MTP_atLODVirModel[87].atBoneVertexRefs[15].atVertexRefs[82],
      1);
    igi2_frame.vY = ++v13;
  }
  while ( v13 <= 32 );
  *(float *)&igi2_frame.vX = igi2_frame.v24 * 0.3499999940395355;
  *(float *)&igi2_frame.vY = igi2_frame.v19 * 0.5199999809265137;
  v16 = igi2_frame.v24 * 0.03500000014901161;
  *(float *)&igi2_frame.avY = *(float *)&igi2_frame.vY + v16;
  igi2_frame.avX[0] = *(float *)&igi2_frame.vX + v16;
  QSprite_Register4(
    &G36SniperOverlay_ptRangeSprite->tQSprite,
    *(float *)&igi2_frame.vX,
    *(float *)&igi2_frame.vY,
    igi2_frame.avX[0],
    *(float *)&igi2_frame.vY,
    *(float *)&igi2_frame.vX,
    *(float *)&igi2_frame.avY,
    igi2_frame.avX[0],
    *(float *)&igi2_frame.avY,
    128.0,
    128.0,
    128.0,
    0,
    0,
    1);
}

// source: j/0/weapons/g36sniperoverlay.c:295  [size]
void __cdecl G36SniperOverlay_StatusDisplayHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct TransContext_s *v2; // eax

  v2 = TransContext_Create(
         (struct TransContext_s *)&ptQTask[3].tQTaskRefList.ptMiddle,
         (struct real32x9_t *)&ptQTask[2].tQTaskRefList,
         (struct real64x3_t *)&ptQTask[1].tQTaskRefList.ptMiddle,
         1.0);
  TransContext_SetActiveTransContext(v2);
  G36SniperOverlay_Draw(ptQTask);
  TransContext_isValid = 0;
}

// source: j/0/weapons/g36sniperoverlay.c:320  [size]
void __cdecl G36SniperOverlay_DrawHandler(struct QTask_s *ptQTask)
{
  struct TransContext_s *v1; // eax

  v1 = TransContext_Create(
         (struct TransContext_s *)&ptQTask[3].tQTaskRefList.ptMiddle,
         (struct real32x9_t *)&ptQTask[2].tQTaskRefList,
         (struct real64x3_t *)&ptQTask[1].tQTaskRefList.ptMiddle,
         1.0);
  TransContext_SetActiveTransContext(v1);
  G36SniperOverlay_Draw(ptQTask);
  TransContext_isValid = 0;
}

// source: j/0/weapons/g36sniperoverlay.c:337  [size]
unsigned __int16 __cdecl G36SniperOverlay_GetQTaskType()
{
  return G36SniperOverlay_eQTaskType;
}

// source: j/0/weapons/g36sniperoverlay.c:350  [anchor-strings]
void __cdecl G36SniperOverlay_Open()
{
  unsigned __int16 v0; // si

  v0 = QTask_NewQTaskType((char *)&g_zMessage.anDR[2], 312, SniperOverlay_eQTaskType, 0, 0);
  G36SniperOverlay_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveNoChildrenHandler);
  QTask_LinkQTaskEventHandlerFn(v0, StatusScreen_eStatusDisplayQTaskEvent, G36SniperOverlay_StatusDisplayHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, G36SniperOverlay_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, G36SniperOverlay_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Screen_eDrawQTaskEvent, G36SniperOverlay_DrawHandler);
  G36SniperOverlay_ptCornerSprite = GameFunctions_RegisterGameSprite((char *)&g_zMessage.tReceiveTimeBuffer.aReceiveTime[4]);
  G36SniperOverlay_ptRangeSprite = GameFunctions_RegisterGameSprite((char *)g_zMessage.tReceiveTimeBuffer.aReceiveTime);
  Symbol_Register(
    (char *)&g_zMessage.ePrevActiveMenu,
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)G36SniperOverlay_eQTaskType,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}

// source: j/0/weapons/g36sniperoverlay.c:379  [size]
void __cdecl G36SniperOverlay_Close()
{
  QTask_DeleteQTaskType(G36SniperOverlay_eQTaskType);
}
