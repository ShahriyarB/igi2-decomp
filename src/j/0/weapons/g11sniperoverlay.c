/* j/0/weapons/g11sniperoverlay.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/weapons/g11sniperoverlay.c:59  [size]
void __cdecl G11SniperOverlay_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  QTask_TriggerBaseHandler(ptQTask, ptQTask->eQTaskType, 0, pxContext);
}

// source: j/0/weapons/g11sniperoverlay.c:75  [size]
void __cdecl G11SniperOverlay_DeleteHandler(struct QTask_s *ptQTask)
{
  QTask_TriggerBaseHandlerNoContext(ptQTask, ptQTask->eQTaskType, 2);
}

// source: j/0/weapons/g11sniperoverlay.c:93  [anchor-mhash]
void __cdecl G11SniperOverlay_Draw(struct QTask_s *ptQTask)
{
  int nQAnimframes; // eax
  int v2; // edx
  double v3; // st7
  float v4; // esi
  float v5; // edi
  int v6; // ebx
  int v7; // ebp
  int v8; // esi
  int v9; // edi
  int v10; // eax
  long double v11; // st7
  double v12; // st6
  double v13; // st5
  double v14; // st6
  double v15; // st6
  double v16; // st6
  double v17; // st7
  float v18; // ebx
  float v19; // esi
  struct QSprite_s *v20; // ebp
  float v21; // edi
  int v22; // ebx
  float v23; // [esp+0h] [ebp-7Ch]
  float v24; // [esp+0h] [ebp-7Ch]
  float v25; // [esp+4h] [ebp-78h]
  float v26; // [esp+4h] [ebp-78h]
  float v27; // [esp+40h] [ebp-3Ch]
  float vX; // [esp+44h] [ebp-38h]
  float vX2; // [esp+48h] [ebp-34h]
  float vY; // [esp+4Ch] [ebp-30h]
  float v31; // [esp+50h] [ebp-2Ch]
  float vX3; // [esp+54h] [ebp-28h]
  float v33; // [esp+58h] [ebp-24h]
  float vY1; // [esp+5Ch] [ebp-20h]
  float vOffset; // [esp+60h] [ebp-1Ch]
  float vY3; // [esp+64h] [ebp-18h]
  int nHeight; // [esp+68h] [ebp-14h]
  struct QSprite_s *v38; // [esp+6Ch] [ebp-10h]
  int nWidth; // [esp+70h] [ebp-Ch]
  float vY2; // [esp+74h] [ebp-8h]
  int iI; // [esp+78h] [ebp-4h]

  nHeight = Display_tActiveMode.nHeight;
  nWidth = Display_tActiveMode.nWidth;
  nQAnimframes = G11SniperOverlay_ptCornerSprite->tQSprite.nQAnimframes;
  vY3 = (float)Display_tActiveMode.nWidth;
  v2 = G11SniperOverlay_ptCornerSprite->tQSprite.atQAnimframe[nQAnimframes].nWidth;
  v31 = 0.0;
  vOffset = vY3 / (double)v2;
  v3 = (double)Display_tActiveMode.nHeight;
  v33 = v3;
  vX3 = v3 * 0.5;
  v4 = vX3;
  vY1 = vY3 * 0.5;
  v5 = vY1;
  *(float *)&iI = -vOffset;
  v6 = iI;
  QSprite_Register4(
    &G11SniperOverlay_ptCornerSprite->tQSprite,
    *(float *)&iI,
    *(float *)&iI,
    vY1,
    *(float *)&iI,
    *(float *)&iI,
    vX3,
    vY1,
    vX3,
    128.0,
    128.0,
    128.0,
    0,
    (unsigned int)&MTP_atLODVirModel[45].atBoneVertexRefs[20].atVertexRefs[781],
    1);
  *(float *)&iI = vY3 + vOffset;
  v7 = iI;
  QSprite_Register4(
    &G11SniperOverlay_ptCornerSprite->tQSprite,
    *(float *)&iI,
    *(float *)&v6,
    v5,
    *(float *)&v6,
    *(float *)&iI,
    v4,
    v5,
    v4,
    128.0,
    128.0,
    128.0,
    0,
    (unsigned int)&MTP_atLODVirModel[45].atBoneVertexRefs[20].atVertexRefs[781],
    1);
  *(float *)&iI = v33 + vOffset;
  QSprite_Register4(
    &G11SniperOverlay_ptCornerSprite->tQSprite,
    *(float *)&v6,
    *(float *)&iI,
    v5,
    *(float *)&iI,
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
    &G11SniperOverlay_ptCornerSprite->tQSprite,
    *(float *)&v7,
    *(float *)&iI,
    v5,
    *(float *)&iI,
    *(float *)&v7,
    v4,
    v5,
    v4,
    128.0,
    128.0,
    128.0,
    0,
    (unsigned int)&MTP_atLODVirModel[45].atBoneVertexRefs[20].atVertexRefs[781],
    1);
  *(float *)&v38 = (float)(nWidth / 2);
  v8 = 1;
  iI = 1;
  *(float *)&nHeight = (float)(nHeight / 2);
  *(float *)&nWidth = v33 * 0.003000000026077032;
  v9 = nWidth;
  do
  {
    vY = v31;
    v10 = 0;
    v31 = (double)iI * 0.13089969389957476;
    do
    {
      v11 = *(float *)((char *)&vY + v10);
      v10 += 4;
      *(float *)((char *)&v27 + v10) = cos(v11) * v33 * 0.4000000059604645 + *(float *)&v38;
      *(float *)((char *)&v38 + v10) = sin(*(float *)((char *)&vX2 + v10)) * v33 * 0.4000000059604645 + *(float *)&nHeight;
    }
    while ( v10 < 8 );
    QSprite_RegisterLine(
      vX,
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
      *(float *)&v9,
      (unsigned int)&MTP_atLODVirModel[87].atBoneVertexRefs[15].atVertexRefs[82],
      1);
    iI = ++v8;
  }
  while ( v8 <= 48 );
  *(float *)&nHeight = v33 * 0.4000000059604645;
  vX = *(float *)&v38 - *(float *)&nHeight;
  v12 = vY3 * 0.20000000298023224;
  *(float *)&iI = v12;
  vY = 0.029999999329447746 * v12;
  *(float *)&nWidth = 0.029999999329447746 * v12 + vX3;
  vY3 = vX + v12;
  vY = vX3 - vY;
  QSprite_Register4(
    &G11SniperOverlay_ptAimSprite->tQSprite,
    vX,
    vY,
    vY3,
    vY,
    vX,
    *(float *)&nWidth,
    vY3,
    *(float *)&nWidth,
    128.0,
    128.0,
    128.0,
    0,
    (unsigned int)&MTP_atLODVirModel[45].atBoneVertexRefs[20].atVertexRefs[781],
    1);
  vX = *(float *)&nHeight + *(float *)&v38;
  v13 = 0.029999999329447746 * *(float *)&iI;
  vY = v13;
  *(float *)&nWidth = v13 + vX3;
  *(float *)&v38 = vX - *(float *)&iI;
  vY = vX3 - vY;
  QSprite_Register4(
    &G11SniperOverlay_ptAimSprite->tQSprite,
    vX,
    vY,
    *(float *)&v38,
    vY,
    vX,
    *(float *)&nWidth,
    *(float *)&v38,
    *(float *)&nWidth,
    128.0,
    128.0,
    128.0,
    0,
    (unsigned int)&MTP_atLODVirModel[45].atBoneVertexRefs[20].atVertexRefs[781],
    1);
  vY = vX3 - *(float *)&nHeight;
  vY3 = vY + *(float *)&iI;
  v14 = *(float *)&iI * 0.029999999329447746;
  *(float *)&nWidth = v14 + vY1;
  *(float *)&v38 = vY1 - v14;
  QSprite_Register4(
    &G11SniperOverlay_ptAimSprite->tQSprite,
    *(float *)&v38,
    vY,
    *(float *)&v38,
    vY3,
    *(float *)&nWidth,
    vY,
    *(float *)&nWidth,
    vY3,
    128.0,
    128.0,
    128.0,
    0,
    (unsigned int)&MTP_atLODVirModel[45].atBoneVertexRefs[20].atVertexRefs[781],
    1);
  vY = *(float *)&nHeight + vX3;
  v15 = *(float *)&iI;
  *(float *)&iI = vY - *(float *)&iI;
  v16 = v15 * 0.029999999329447746;
  *(float *)&nWidth = v16 + vY1;
  *(float *)&v38 = vY1 - v16;
  QSprite_Register4(
    &G11SniperOverlay_ptAimSprite->tQSprite,
    *(float *)&v38,
    vY,
    *(float *)&v38,
    *(float *)&iI,
    *(float *)&nWidth,
    vY,
    *(float *)&nWidth,
    *(float *)&iI,
    128.0,
    128.0,
    128.0,
    0,
    (unsigned int)&MTP_atLODVirModel[45].atBoneVertexRefs[20].atVertexRefs[781],
    1);
  v17 = v33 * 0.05000000074505806;
  vX = vY1;
  vY3 = v17;
  vY = v17 + vX3;
  *(float *)&nHeight = v33 * 0.15000000596046448;
  v25 = *(float *)&nHeight + vY;
  QSprite_RegisterLine(
    vY1,
    vY,
    1.0,
    vY1,
    v25,
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
  vY = vX3 - vY3;
  v26 = vY - *(float *)&nHeight;
  vX = vY1;
  QSprite_RegisterLine(
    vY1,
    vY,
    1.0,
    vY1,
    v26,
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
  vX = vY1 - vY3;
  v23 = vX - *(float *)&nHeight;
  vY = vX3;
  QSprite_RegisterLine(
    vX,
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
    (unsigned int)&MTP_atLODVirModel[87].atBoneVertexRefs[15].atVertexRefs[82],
    1);
  vX = vY3 + vY1;
  v24 = *(float *)&nHeight + vX;
  vY = vX3;
  QSprite_RegisterLine(
    vX,
    vX3,
    1.0,
    v24,
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
    (unsigned int)&MTP_atLODVirModel[87].atBoneVertexRefs[15].atVertexRefs[82],
    1);
  vY = vX3;
  vOffset = vY3;
  vY3 = vX3 + vY3;
  vX = vY1;
  v18 = vY3;
  v19 = vY1;
  *(float *)&v38 = vY1 - vOffset;
  v20 = v38;
  v21 = vX3;
  QSprite_RegisterLine(
    *(float *)&v38,
    vX3,
    1.0,
    vY1,
    vY3,
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
  vY3 = vX + vOffset;
  QSprite_RegisterLine(
    v19,
    v18,
    1.0,
    vY3,
    v21,
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
  *(float *)&iI = vY - vOffset;
  v22 = iI;
  QSprite_RegisterLine(
    vY3,
    v21,
    1.0,
    v19,
    *(float *)&iI,
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
  QSprite_RegisterLine(
    v19,
    *(float *)&v22,
    1.0,
    *(float *)&v20,
    v21,
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
}

// source: j/0/weapons/g11sniperoverlay.c:358  [size]
void __cdecl G11SniperOverlay_StatusDisplayHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct TransContext_s *v2; // eax

  v2 = TransContext_Create(
         (struct TransContext_s *)&ptQTask[3].tQTaskRefList.ptMiddle,
         (struct real32x9_t *)&ptQTask[2].tQTaskRefList,
         (struct real64x3_t *)&ptQTask[1].tQTaskRefList.ptMiddle,
         1.0);
  TransContext_SetActiveTransContext(v2);
  G11SniperOverlay_Draw(ptQTask);
  TransContext_isValid = 0;
}

// source: j/0/weapons/g11sniperoverlay.c:383  [size]
void __cdecl G11SniperOverlay_DrawHandler(struct QTask_s *ptQTask)
{
  struct TransContext_s *v1; // eax

  v1 = TransContext_Create(
         (struct TransContext_s *)&ptQTask[3].tQTaskRefList.ptMiddle,
         (struct real32x9_t *)&ptQTask[2].tQTaskRefList,
         (struct real64x3_t *)&ptQTask[1].tQTaskRefList.ptMiddle,
         1.0);
  TransContext_SetActiveTransContext(v1);
  G11SniperOverlay_Draw(ptQTask);
  TransContext_isValid = 0;
}

// source: j/0/weapons/g11sniperoverlay.c:400  [size]
unsigned __int16 __cdecl G11SniperOverlay_GetQTaskType()
{
  return G11SniperOverlay_eQTaskType;
}

// source: j/0/weapons/g11sniperoverlay.c:413  [anchor-strings]
void __cdecl G11SniperOverlay_Open()
{
  unsigned __int16 v0; // si

  v0 = QTask_NewQTaskType("G11SniperOverlay", 312, SniperOverlay_eQTaskType, 0, 0);
  G11SniperOverlay_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveNoChildrenHandler);
  QTask_LinkQTaskEventHandlerFn(v0, StatusScreen_eStatusDisplayQTaskEvent, G11SniperOverlay_StatusDisplayHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, G11SniperOverlay_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, G11SniperOverlay_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Screen_eDrawQTaskEvent, G11SniperOverlay_DrawHandler);
  G11SniperOverlay_ptCornerSprite = GameFunctions_RegisterGameSprite((char *)&g_zMessage.tReceiveTimeBuffer.aReceiveTime[4]);
  G11SniperOverlay_ptAimSprite = GameFunctions_RegisterGameSprite("g11sight.spr");
  Symbol_Register(
    "TASKTYPE_G11SNIPEROVERLAY",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)G11SniperOverlay_eQTaskType,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}

// source: j/0/weapons/g11sniperoverlay.c:442  [size]
void __cdecl G11SniperOverlay_Close()
{
  QTask_DeleteQTaskType(G11SniperOverlay_eQTaskType);
}
