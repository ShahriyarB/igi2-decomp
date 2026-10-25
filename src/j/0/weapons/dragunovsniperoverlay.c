/* j/0/weapons/dragunovsniperoverlay.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/weapons/dragunovsniperoverlay.c:60  [size]
void __cdecl DragunovSniperOverlay_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  QTask_TriggerBaseHandler(ptQTask, ptQTask->eQTaskType, 0, pxContext);
}

// source: j/0/weapons/dragunovsniperoverlay.c:76  [size]
void __cdecl DragunovSniperOverlay_DeleteHandler(struct QTask_s *ptQTask)
{
  QTask_TriggerBaseHandlerNoContext(ptQTask, ptQTask->eQTaskType, 2);
}

// source: j/0/weapons/dragunovsniperoverlay.c:94  [anchor-mhash]
void __cdecl DragunovSniperOverlay_Draw(struct QTask_s *ptQTask)
{
  double v1; // st7
  float v2; // esi
  float v3; // edi
  float v4; // ebx
  double v5; // st7
  double v6; // st6
  float v7; // [esp+0h] [ebp-20h]
  float vOffset; // [esp+4h] [ebp-1Ch]
  float vX1; // [esp+8h] [ebp-18h]
  float vX1a; // [esp+8h] [ebp-18h]
  int nHeight; // [esp+Ch] [ebp-14h]
  int nWidth; // [esp+10h] [ebp-10h]
  float vX3; // [esp+14h] [ebp-Ch]
  float vX3a; // [esp+14h] [ebp-Ch]
  float vY1; // [esp+18h] [ebp-8h]
  float vY1a; // [esp+18h] [ebp-8h]
  float ptQSprite; // [esp+1Ch] [ebp-4h]
  float ptQSpritea; // [esp+1Ch] [ebp-4h]
  float ptQSpriteb; // [esp+1Ch] [ebp-4h]

  nHeight = Display_tActiveMode.nHeight;
  nWidth = Display_tActiveMode.nWidth;
  v7 = (float)Display_tActiveMode.nWidth;
  vOffset = v7
          / (double)DragunovSniperOverlay_ptCornerSprite->tQSprite.atQAnimframe[DragunovSniperOverlay_ptCornerSprite->tQSprite.nQAnimframes].nWidth;
  v1 = (double)Display_tActiveMode.nHeight;
  vX1 = v1;
  vX3 = v1 * 0.5;
  v2 = vX3;
  vY1 = v7 * 0.5;
  v3 = vY1;
  ptQSprite = -vOffset;
  v4 = ptQSprite;
  QSprite_Register4(
    &DragunovSniperOverlay_ptCornerSprite->tQSprite,
    ptQSprite,
    ptQSprite,
    vY1,
    ptQSprite,
    ptQSprite,
    vX3,
    vY1,
    vX3,
    128.0,
    128.0,
    128.0,
    0,
    (unsigned int)&MTP_atLODVirModel[45].atBoneVertexRefs[20].atVertexRefs[781],
    1);
  ptQSpritea = v7 + vOffset;
  QSprite_Register4(
    &DragunovSniperOverlay_ptCornerSprite->tQSprite,
    ptQSpritea,
    v4,
    v3,
    v4,
    ptQSpritea,
    v2,
    v3,
    v2,
    128.0,
    128.0,
    128.0,
    0,
    (unsigned int)&MTP_atLODVirModel[45].atBoneVertexRefs[20].atVertexRefs[781],
    1);
  vX1a = vX1 + vOffset;
  QSprite_Register4(
    &DragunovSniperOverlay_ptCornerSprite->tQSprite,
    v4,
    vX1a,
    v3,
    vX1a,
    v4,
    v2,
    v3,
    v2,
    128.0,
    128.0,
    128.0,
    0,
    (unsigned int)&MTP_atLODVirModel[45].atBoneVertexRefs[20].atVertexRefs[781],
    1);
  QSprite_Register4(
    &DragunovSniperOverlay_ptCornerSprite->tQSprite,
    ptQSpritea,
    vX1a,
    v3,
    vX1a,
    ptQSpritea,
    v2,
    v3,
    v2,
    128.0,
    128.0,
    128.0,
    0,
    (unsigned int)&MTP_atLODVirModel[45].atBoneVertexRefs[20].atVertexRefs[781],
    1);
  v5 = v7 * 0.20000000298023224;
  vY1a = (double)(nHeight / 2) + v5;
  v6 = (double)(nWidth / 2);
  ptQSpriteb = v6 + v5;
  vX3a = v6 - v5;
  QSprite_Register4(
    &DragunovSniperOverlay_ptOpticsSprite->tQSprite,
    vX3a,
    v2,
    ptQSpriteb,
    v2,
    vX3a,
    vY1a,
    ptQSpriteb,
    vY1a,
    128.0,
    128.0,
    128.0,
    0,
    (unsigned int)&MTP_atLODVirModel[45].atBoneVertexRefs[20].atVertexRefs[781],
    1);
}

// source: j/0/weapons/dragunovsniperoverlay.c:201  [size]
void __cdecl DragunovSniperOverlay_StatusDisplayHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct TransContext_s *v2; // eax

  v2 = TransContext_Create(
         (struct TransContext_s *)&ptQTask[3].tQTaskRefList.ptMiddle,
         (struct real32x9_t *)&ptQTask[2].tQTaskRefList,
         (struct real64x3_t *)&ptQTask[1].tQTaskRefList.ptMiddle,
         1.0);
  TransContext_SetActiveTransContext(v2);
  DragunovSniperOverlay_Draw(ptQTask);
  TransContext_isValid = 0;
}

// source: j/0/weapons/dragunovsniperoverlay.c:226  [size]
void __cdecl DragunovSniperOverlay_DrawHandler(struct QTask_s *ptQTask)
{
  struct TransContext_s *v1; // eax

  v1 = TransContext_Create(
         (struct TransContext_s *)&ptQTask[3].tQTaskRefList.ptMiddle,
         (struct real32x9_t *)&ptQTask[2].tQTaskRefList,
         (struct real64x3_t *)&ptQTask[1].tQTaskRefList.ptMiddle,
         1.0);
  TransContext_SetActiveTransContext(v1);
  DragunovSniperOverlay_Draw(ptQTask);
  TransContext_isValid = 0;
}

// source: j/0/weapons/dragunovsniperoverlay.c:243  [size]
unsigned __int16 __cdecl DragunovSniperOverlay_GetQTaskType()
{
  return DragunovSniperOverlay_eQTaskType;
}

// source: j/0/weapons/dragunovsniperoverlay.c:256  [anchor-strings]
void __cdecl DragunovSniperOverlay_Open()
{
  unsigned __int16 v0; // si

  v0 = QTask_NewQTaskType("DragunovSniperOverlay", 312, SniperOverlay_eQTaskType, 0, 0);
  DragunovSniperOverlay_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveNoChildrenHandler);
  QTask_LinkQTaskEventHandlerFn(v0, StatusScreen_eStatusDisplayQTaskEvent, DragunovSniperOverlay_StatusDisplayHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, DragunovSniperOverlay_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, DragunovSniperOverlay_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Screen_eDrawQTaskEvent, DragunovSniperOverlay_DrawHandler);
  DragunovSniperOverlay_ptCornerSprite = GameFunctions_RegisterGameSprite((char *)&g_zMessage.tReceiveTimeBuffer.aReceiveTime[4]);
  DragunovSniperOverlay_ptOpticsSprite = GameFunctions_RegisterGameSprite("dragunovAIM.spr");
  Symbol_Register(
    "TASKTYPE_DRAGUNOVSNIPEROVERLAY",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)DragunovSniperOverlay_eQTaskType,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}

// source: j/0/weapons/dragunovsniperoverlay.c:285  [size]
void __cdecl DragunovSniperOverlay_Close()
{
  QTask_DeleteQTaskType(DragunovSniperOverlay_eQTaskType);
}
