/* j/0/weapons/laserdesignatoroverlay.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/weapons/laserdesignatoroverlay.c:86  [anchor-mhash]
struct Result_s *__cdecl LaserDesignatorOverlay_SetLockedOnStatus(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      ptArgList = nullptr;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
      v4 = ptArgList;
    }
    else
    {
      v4 = (struct ArgList_s *)Expression_EvalInt(*ptArgList->aptExpression);
    }
    LaserDesignatorOverlay_IsLockedOn = (enum bool)v4;
  }
  Rs.nResult = 1;
  Rs.zResult = (char *)&g_zInitialValue;
  Rs.vResult = 1.0;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/weapons/laserdesignatoroverlay.c:111  [anchor-strings]
void __cdecl LaserDesignatorOverlay_Draw(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { double ptQSprite; };
    struct { float ptQSpritea; };
    struct { float ptQSpriteb; };
    struct { float ptQSpritec; };
    struct { char igi2_o4[12]; float v20; };
    struct { char igi2_o5[12]; float v21; };
    struct { char igi2_o6[12]; float v22; };
    struct { char igi2_o7[12]; float v23; };
    struct { char igi2_o8[16]; int nWidth; };
    struct { char igi2_o9[16]; float v25; };
    struct { char igi2_o10[16]; float v26; };
    struct { char igi2_o11[16]; float v27; };
    struct { char igi2_o12[20]; float v28; };
    struct { char igi2_o13[20]; float v29; };
    struct { char igi2_o14[24]; char *LocalizedStringForLanguage; };
    struct { char igi2_o15[24]; float v31; };
    struct { char igi2_o16[28]; float vY1; };
    struct { char igi2_o17[28]; int vY1a; };
    struct { char igi2_o18[32]; float vX3; };
    struct { char igi2_o19[32]; float vX3a; };
    struct { char igi2_o20[32]; float vX3b; };
    struct { char igi2_o21[36]; struct real32x3_t ptStart; };
    struct { char igi2_o22[48]; struct real32x3_t v38; };
    struct { char igi2_o23[60]; struct real32x3_t ptColor; };
    struct { char igi2_o24[72]; struct CollisionEvaluateContext_s nNumPoints; };
    struct { char igi2_o25[80]; struct real64x3_t ptEnd; };
    struct { char igi2_o26[104]; struct QIntersection_s ptIntersection; };
    struct { char igi2_o27[256]; struct QIntersection_s v43; };
    char igi2_extent[376];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v1; // eax
  double v2; // st7
  float v3; // esi
  double v4; // st7
  double v5; // st6
  struct QTask_s *ptParent; // ecx
  struct QReference_s *v7; // eax
  struct Weapon_s **pxObject; // esi
  struct QReference_s *ptParametersQTaskRef; // eax
  float *v10; // eax
  float *ptMiddle; // eax
  struct QReference_s *v12; // eax
  char *p_vZ; // eax
  double v14; // st7
  struct QReference_s *ptTail; // eax

  igi2_frame.nWidth = Display_tActiveMode.nWidth;
  igi2_frame.vY1a = Display_tActiveMode.nHeight;
  igi2_frame.LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                 "weapons/strings/Binoculars/range",
                                 Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                 true);
  igi2_frame.v28 = (float)igi2_frame.nWidth;
  v1 = LaserDesignatorOverlay_ptBorderSprite->tQSprite.atQAnimframe[LaserDesignatorOverlay_ptBorderSprite->tQSprite.nQAnimframes].nWidth;
  igi2_frame.ptColor.vX = 0.30000001192092896;
  igi2_frame.ptColor.vY = 0.800000011920929;
  igi2_frame.ptColor.vZ = 0.30000001192092896;
  igi2_frame.v20 = igi2_frame.v28 / (double)v1;
  v2 = (double)igi2_frame.vY1a;
  igi2_frame.v25 = v2;
  igi2_frame.vX3a = v2 + igi2_frame.v20;
  igi2_frame.vY1 = igi2_frame.v28 * 0.5;
  igi2_frame.ptQSpritea = -igi2_frame.v20;
  v3 = igi2_frame.ptQSpritea;
  QSprite_Register4(
    &LaserDesignatorOverlay_ptBorderSprite->tQSprite,
    igi2_frame.ptQSpritea,
    igi2_frame.ptQSpritea,
    igi2_frame.vY1,
    igi2_frame.ptQSpritea,
    igi2_frame.ptQSpritea,
    igi2_frame.vX3a,
    igi2_frame.vY1,
    igi2_frame.vX3a,
    128.0,
    128.0,
    128.0,
    0,
    (unsigned int)&MTP_atLODVirModel[45].atBoneVertexRefs[20].atVertexRefs[781],
    1);
  igi2_frame.ptQSpriteb = igi2_frame.v28 + igi2_frame.v20;
  QSprite_Register4(
    &LaserDesignatorOverlay_ptBorderSprite->tQSprite,
    igi2_frame.ptQSpriteb,
    v3,
    igi2_frame.vY1,
    v3,
    igi2_frame.ptQSpriteb,
    igi2_frame.vX3a,
    igi2_frame.vY1,
    igi2_frame.vX3a,
    128.0,
    128.0,
    128.0,
    0,
    (unsigned int)&MTP_atLODVirModel[45].atBoneVertexRefs[20].atVertexRefs[781],
    1);
  v4 = *(float *)&ptQTask[2].ptNext;
  v5 = *(float *)&ptQTask[2].ptPrev;
  igi2_frame.ptEnd.vZ = *(float *)&ptQTask[2].tQTaskChildren.ptHead;
  qmemcpy(&igi2_frame.ptIntersection, &ptQTask[1].tQTaskChildren.ptTail, 0x18u);
  igi2_frame.ptEnd.vX = v4 * 4096000.0;
  ptParent = ptQTask->ptParent;
  igi2_frame.ptEnd.vX = *(double *)&igi2_frame.ptIntersection.ptHitObj + igi2_frame.ptEnd.vX;
  igi2_frame.nNumPoints.isEvaluate = 0;
  igi2_frame.ptEnd.vY = igi2_frame.ptIntersection.tPos.vX + v5 * 4096000.0;
  igi2_frame.ptEnd.vZ = igi2_frame.ptIntersection.tPos.vY + igi2_frame.ptEnd.vZ * 4096000.0;
  igi2_frame.nNumPoints.ptQTask = ptParent->ptParent;
  World_TraceLines(
    Game_ptGame->ptWorld,
    &igi2_frame.v43,
    (struct real64x3_t *)&igi2_frame.ptIntersection,
    &igi2_frame.ptEnd,
    1,
    13,
    &igi2_frame.nNumPoints,
    Forest_bQTaskGroup | 0x98000000);
  if ( igi2_frame.v43.isHit )
  {
    v7 = Game_ptGame->aptPlayerQTaskRef[2];
    pxObject = nullptr;
    if ( v7 )
      pxObject = (struct Weapon_s **)v7->pxObject;
    igi2_frame.ptQSprite = floor(igi2_frame.v43.vDistance * 0.000244140625);
    if ( pxObject )
    {
      ptParametersQTaskRef = Weapon_GetWeaponTypeItemFromCategory(pxObject[330], WEAPONCATEGORY_LASERDESIGNATOR)->ptWeaponType->atFireTypes[0].ptParametersQTaskRef;
      if ( ptParametersQTaskRef )
      {
        v10 = (float *)ptParametersQTaskRef->pxObject;
        if ( v10 )
        {
          if ( v10[10] < igi2_frame.ptQSprite )
          {
            LaserDesignator_nTickFirstHit = 0;
            LaserDesignator_ptHitQTask = nullptr;
          }
        }
      }
    }
    sprintf((char *const)&igi2_frame.ptIntersection.tPos.vZ, "%s: %0.f%s", igi2_frame.LocalizedStringForLanguage, igi2_frame.ptQSprite, "m");
  }
  else
  {
    sprintf((char *const)&igi2_frame.ptIntersection.tPos.vZ, "%s: %0.f+%s", igi2_frame.LocalizedStringForLanguage, 1000.0, "m");
  }
  Text_SetString((struct StaticTilemap_s *)ptQTask[7].tQTaskRefList.ptMiddle, (char *)&igi2_frame.ptIntersection.tPos.vZ);
  ptMiddle = (float *)ptQTask[7].tQTaskRefList.ptMiddle;
  igi2_frame.v31 = igi2_frame.v25 * 0.5;
  igi2_frame.v21 = (double)(*(__int16 *)(*(_DWORD *)ptMiddle + 6)
               * *(__int16 *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)ptMiddle + 8) + 8)
                            + 36 * *(unsigned __int16 *)(*(_DWORD *)(*(_DWORD *)ptMiddle + 8) + 20)
                            + 14))
      + igi2_frame.v31;
  igi2_frame.vX3 = (float)(int)(__int64)(igi2_frame.vY1 - igi2_frame.v28 * 0.1599999964237213);
  ptMiddle[1] = igi2_frame.vX3;
  *(float *)&ptQTask[7].tQTaskRefList.ptMiddle->pxObject = (float)(__int64)igi2_frame.v21;
  v12 = ptQTask[7].tQTaskRefList.ptMiddle;
  QTilemap_Register(
    (struct QTilemap_s *)v12->ptNext,
    *(float *)&v12->ptPrev,
    *(float *)&v12->pxObject,
    *(float *)&v12[1].pxObject,
    *(float *)&v12[2].ptNext,
    *(float *)&v12[2].ptPrev,
    *(float *)&v12[1].ptPrev,
    *(float *)&v12[1].ptNext,
    (int)v12[3].ptNext | 0x40000000,
    (int)v12[2].pxObject);
  igi2_frame.v22 = (double)(SHIWORD(ptQTask[7].tQTaskRefList.ptMiddle->ptNext->ptPrev)
               * *(__int16 *)(*((_DWORD *)ptQTask[7].tQTaskRefList.ptMiddle->ptNext->pxObject + 2)
                            + 36 * *((unsigned __int16 *)ptQTask[7].tQTaskRefList.ptMiddle->ptNext->pxObject + 10)
                            + 14))
      + igi2_frame.v21;
  if ( LaserDesignatorOverlay_IsLockedOn )
  {
    p_vZ = Config_GetLocalizedStringForLanguage(
             "BOMB_LOCKED_ON",
             Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
             true);
  }
  else if ( LaserDesignator_nTickFirstHit )
  {
    v14 = 20.0 - (double)(LevelFlow_ptLevelFlow->nTick - LaserDesignator_nTickFirstHit) * 0.03333333507180214;
    if ( v14 <= 0.0 )
      v14 = 0.0;
    sprintf((char *const)&igi2_frame.ptIntersection.tPos.vZ, "L: %.3f", v14);
    p_vZ = (char *)&igi2_frame.ptIntersection.tPos.vZ;
  }
  else
  {
    p_vZ = Config_GetLocalizedStringForLanguage(
             "NO_LOCK",
             Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
             true);
  }
  Text_SetString((struct StaticTilemap_s *)ptQTask[7].tQTaskRefList.ptTail, p_vZ);
  *(float *)&ptQTask[7].tQTaskRefList.ptTail->ptPrev = igi2_frame.vX3;
  *(float *)&ptQTask[7].tQTaskRefList.ptTail->pxObject = (float)(__int64)igi2_frame.v22;
  ptTail = ptQTask[7].tQTaskRefList.ptTail;
  QTilemap_Register(
    (struct QTilemap_s *)ptTail->ptNext,
    *(float *)&ptTail->ptPrev,
    *(float *)&ptTail->pxObject,
    *(float *)&ptTail[1].pxObject,
    *(float *)&ptTail[2].ptNext,
    *(float *)&ptTail[2].ptPrev,
    *(float *)&ptTail[1].ptPrev,
    *(float *)&ptTail[1].ptNext,
    (int)ptTail[3].ptNext | 0x40000000,
    (int)ptTail[2].pxObject);
  igi2_frame.v23 = igi2_frame.v28 * 0.009999999776482582;
  igi2_frame.ptStart.vZ = 1.0;
  igi2_frame.v38.vZ = 1.0;
  igi2_frame.v26 = igi2_frame.vY1 - igi2_frame.v23;
  igi2_frame.ptStart.vX = igi2_frame.v26;
  igi2_frame.ptStart.vY = igi2_frame.v31;
  igi2_frame.v29 = igi2_frame.v28 * 0.15000000596046448;
  igi2_frame.v38.vX = igi2_frame.v26 - igi2_frame.v29;
  igi2_frame.v38.vY = igi2_frame.v31;
  Line_RegisterLine2D(&igi2_frame.ptStart, &igi2_frame.v38, &igi2_frame.ptColor, 1.0);
  igi2_frame.ptStart.vX = igi2_frame.v26;
  igi2_frame.ptQSpritec = igi2_frame.v23 + igi2_frame.v31;
  igi2_frame.v38.vX = igi2_frame.v26;
  igi2_frame.ptStart.vY = igi2_frame.ptQSpritec;
  igi2_frame.ptStart.vZ = 1.0;
  igi2_frame.vX3b = igi2_frame.v31 - igi2_frame.v23;
  igi2_frame.v38.vZ = 1.0;
  igi2_frame.v38.vY = igi2_frame.vX3b;
  Line_RegisterLine2D(&igi2_frame.ptStart, &igi2_frame.v38, &igi2_frame.ptColor, 1.0);
  igi2_frame.v27 = igi2_frame.v23 + igi2_frame.vY1;
  igi2_frame.ptStart.vZ = 1.0;
  igi2_frame.ptStart.vX = igi2_frame.v27;
  igi2_frame.v38.vZ = 1.0;
  igi2_frame.ptStart.vY = igi2_frame.v31;
  igi2_frame.v38.vX = igi2_frame.v29 + igi2_frame.v27;
  igi2_frame.v38.vY = igi2_frame.v31;
  Line_RegisterLine2D(&igi2_frame.ptStart, &igi2_frame.v38, &igi2_frame.ptColor, 1.0);
  igi2_frame.ptStart.vX = igi2_frame.v27;
  igi2_frame.ptStart.vY = igi2_frame.ptQSpritec;
  igi2_frame.v38.vX = igi2_frame.v27;
  igi2_frame.v38.vY = igi2_frame.vX3b;
  igi2_frame.ptStart.vZ = 1.0;
  igi2_frame.v38.vZ = 1.0;
  Line_RegisterLine2D(&igi2_frame.ptStart, &igi2_frame.v38, &igi2_frame.ptColor, 1.0);
}

// source: j/0/weapons/laserdesignatoroverlay.c:311  [anchor-strings]
void __cdecl LaserDesignatorOverlay_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  char *LocalizedStringForLanguage; // eax

  ptQTask[1].tQTaskChildren.ptTail = nullptr;
  ptQTask[1].tQTaskRefList.ptHead = nullptr;
  ptQTask[1].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[1].tQTaskRefList.ptTail = nullptr;
  ptQTask[1].ptParent = nullptr;
  *(_DWORD *)&ptQTask[1].eQTaskType = 0;
  ptQTask[2].ptNext = nullptr;
  ptQTask[2].ptPrev = nullptr;
  ptQTask[2].tQTaskChildren.ptHead = nullptr;
  ptQTask[2].tQTaskChildren.ptMiddle = (struct QTask_s *)1065353216;
  ptQTask[2].tQTaskChildren.ptTail = nullptr;
  ptQTask[2].tQTaskRefList.ptHead = nullptr;
  ptQTask[2].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[2].tQTaskRefList.ptTail = (struct QReference_s *)1065353216;
  ptQTask[2].ptParent = nullptr;
  *(_DWORD *)&ptQTask[2].eQTaskType = 0;
  ptQTask[3].ptNext = nullptr;
  ptQTask[3].ptPrev = (struct QTask_s *)1065353216;
  ptQTask[3].tQTaskChildren.ptHead = nullptr;
  LOBYTE(ptQTask[1].ptNext) = 0;
  ptQTask[7].tQTaskRefList.ptMiddle = (struct QReference_s *)Text_New(
                                                               ComputerMenu_tComputerMenuResource.ptQSpriteFont3,
                                                               0.0,
                                                               0.0,
                                                               (char *)&g_zInitialValue);
  ptQTask[7].tQTaskRefList.ptTail = (struct QReference_s *)Text_New(
                                                             ComputerMenu_tComputerMenuResource.ptQSpriteFont3,
                                                             0.0,
                                                             0.0,
                                                             (char *)&g_zInitialValue);
  LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                 "BOMB_LOCKED_ON",
                                 Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                 true);
  Text_SetString((struct StaticTilemap_s *)ptQTask[7].tQTaskRefList.ptTail, LocalizedStringForLanguage);
}

// source: j/0/weapons/laserdesignatoroverlay.c:333  [size]
void __cdecl LaserDesignatorOverlay_DeleteHandler(struct QTask_s *ptQTask)
{
  Text_Delete((struct StaticTilemap_s *)ptQTask[7].tQTaskRefList.ptMiddle);
  Text_Delete((struct StaticTilemap_s *)ptQTask[7].tQTaskRefList.ptTail);
}

// source: j/0/weapons/laserdesignatoroverlay.c:350  [anchor-mhash]
void __cdecl LaserDesignatorOverlay_DrawHandler(struct QTask_s *ptQTask)
{
  qmemcpy(&ptQTask[1].tQTaskChildren.ptTail, &TransContext_tActiveTransContext.tPos, 0x18u);
  ptQTask[2].ptNext = (struct QTask_s *)LODWORD(TransContext_tActiveTransContext.tMatrix.tZ.vX);
  ptQTask[2].ptPrev = (struct QTask_s *)LODWORD(TransContext_tActiveTransContext.tMatrix.tZ.vY);
  ptQTask[2].tQTaskChildren.ptHead = (struct QTask_s *)LODWORD(TransContext_tActiveTransContext.tMatrix.tZ.vZ);
}

// source: j/0/weapons/laserdesignatoroverlay.c:387  [anchor-caller]
void __cdecl LaserDesignatorOverlay_StatusDisplayHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct TransContext_s *v2; // eax

  v2 = TransContext_Create(
         (struct TransContext_s *)&ptQTask[3].tQTaskChildren.ptTail,
         (struct real32x9_t *)&ptQTask[2].tQTaskChildren.ptMiddle,
         (struct real64x3_t *)&ptQTask[1].tQTaskChildren.ptTail,
         1.5707963705062866);
  TransContext_SetActiveTransContext(v2);
  LaserDesignatorOverlay_Draw(ptQTask);
  TransContext_isValid = 0;
}

// source: j/0/weapons/laserdesignatoroverlay.c:412  [size]
void __cdecl LaserDesignatorOverlay_PositionOverlayHandler(struct QTask_s *ptQTask, void *pxContext)
{
  double v3; // st7
  double v4; // st7
  float Real32x3_Rotate_tTemp; // [esp+Ch] [ebp-Ch]
  float Real32x3_Rotate_tTemp_4; // [esp+10h] [ebp-8h]
  float Real32x3_Rotate_tTemp_8; // [esp+14h] [ebp-4h]

  qmemcpy(&ptQTask[1].tQTaskChildren.ptTail, *(void **)pxContext, 0x18u);
  qmemcpy(&ptQTask[2].tQTaskChildren.ptMiddle, *((void **)pxContext + 1), sizeof(struct QTask_s));
  Real32x3_Rotate_tTemp = (*(float *)&ptQTask[2].tQTaskRefList.ptHead + *(float *)&ptQTask[2].tQTaskChildren.ptMiddle)
                        * 0.0
                        + *(float *)&ptQTask[2].tQTaskChildren.ptTail;
  v3 = *(float *)&ptQTask[2].ptParent + *(float *)&ptQTask[2].tQTaskRefList.ptMiddle;
  ptQTask[2].ptPrev = (struct QTask_s *)1065353216;
  ptQTask[2].tQTaskChildren.ptHead = nullptr;
  ptQTask[2].ptNext = nullptr;
  Real32x3_Rotate_tTemp_4 = v3 * 0.0 + *(float *)&ptQTask[2].tQTaskRefList.ptTail;
  v4 = (*(float *)&ptQTask[3].ptPrev + *(float *)&ptQTask[2].eQTaskType) * 0.0 + *(float *)&ptQTask[3].ptNext;
  *(float *)&ptQTask[2].ptNext = Real32x3_Rotate_tTemp;
  *(float *)&ptQTask[2].ptPrev = Real32x3_Rotate_tTemp_4;
  Real32x3_Rotate_tTemp_8 = v4;
  *(float *)&ptQTask[2].tQTaskChildren.ptHead = Real32x3_Rotate_tTemp_8;
}

// source: j/0/weapons/laserdesignatoroverlay.c:459  [size]
unsigned __int16 __cdecl LaserDesignatorOverlay_GetQTaskType()
{
  return LaserDesignatorOverlay_eQTaskType;
}

// source: j/0/weapons/laserdesignatoroverlay.c:475  [anchor-hash]
void __cdecl LaserDesignatorOverlay_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("LaserDesignatorOverlay", 312, BaseQTaskType, 0, 0);
  LaserDesignatorOverlay_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 0, LaserDesignatorOverlay_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(v1, StatusScreen_eStatusDisplayQTaskEvent, LaserDesignatorOverlay_StatusDisplayHandler);
  QTask_LinkQTaskEventHandlerFn(v1, Weapon_ePositionOverlayQTaskEvent, LaserDesignatorOverlay_PositionOverlayHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, LaserDesignatorOverlay_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, Screen_eDrawQTaskEvent, LaserDesignatorOverlay_DrawHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  Symbol_Register(
    "TASKTYPE_LASERDESIGNATOROVERLAY",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)v1,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "LaserDesignatorOverlay_SetLockedOnStatus",
    LaserDesignatorOverlay_SetLockedOnStatus,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  LaserDesignatorOverlay_ptBorderSprite = GameFunctions_RegisterGameSprite("binoculars.spr");
}

// source: j/0/weapons/laserdesignatoroverlay.c:506  [anchor-strings]
void __cdecl LaserDesignatorOverlay_Close()
{
  Symbol_Remove("LaserDesignatorOverlay_SetLockedOnStatus");
  QTask_DeleteQTaskType(LaserDesignatorOverlay_eQTaskType);
}

// source: j/0/weapons/laserdesignatoroverlay.c:524  [size]
struct QTask_s *__cdecl LaserDesignatorOverlay_New(struct QTask_s *ptParent)
{
  return QTask_NewFn(ptParent, LaserDesignatorOverlay_eQTaskType, nullptr);
}
