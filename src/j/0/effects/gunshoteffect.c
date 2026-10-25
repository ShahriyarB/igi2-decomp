/* j/0/effects/gunshoteffect.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/effects/gunshoteffect.c:66  [anchor-caller]
void __cdecl GunShotEffect_CreateEffectHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct World_s *v24; };
    struct { char igi2_o1[4]; struct QSprite_s *p_tQSprite; };
    struct { char igi2_o2[64]; struct real32x3_t *ptVel; };
    struct { char igi2_o3[64]; float ptVela; };
    struct { char igi2_o4[64]; float ptVelb; };
    struct { char igi2_o5[68]; struct real32x3_t ptvRGB; };
    struct { char igi2_o6[80]; int v30; };
    struct { char igi2_o7[84]; float v31; };
    struct { char igi2_o8[88]; struct QSprite_s ptQSprite; };
    struct { char igi2_o9[112]; struct real64x3_t ptPos; };
    char igi2_extent[136];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QIntersection_s *v2; // esi
  int v3; // edx
  int v4; // edi
  struct Game_s *v5; // eax
  unsigned int v6; // edx
  int v7; // edx
  unsigned int v8; // edx
  struct QObj_s *ptHitObj; // ecx
  float v10; // eax
  int v11; // eax
  struct Game_s *v12; // eax
  unsigned int v13; // ecx
  unsigned int v14; // edi
  unsigned int v15; // edx
  struct World_s *ptWorld; // eax
  struct QTask_s *v17; // eax
  struct QTask_s *v18; // eax
  struct QTask_s *v19; // ebx
  struct RandomState_s *p_tRunRandomState; // esi
  double RandomNumberReal32; // st7
  float vX; // edi
  double v23; // st7

  v2 = *(struct QIntersection_s **)pxContext;
  v3 = **(_DWORD **)pxContext;
  v4 = *((_DWORD *)pxContext + 1);
  if ( v3 )
    igi2_frame.ptVel = (struct real32x3_t *)QTask_IsQTaskTypeDerived(*(_WORD *)(v3 + 36), BoneDynCubeObj_eQTaskType);
  else
    igi2_frame.ptVel = nullptr;
  LODWORD(igi2_frame.ptvRGB.vX) = QTask_IsQTaskTypeDerived(*(_WORD *)(v3 + 36), Water_eQTaskType);
  if ( *(_BYTE *)(v4 + 1) && !igi2_frame.ptVel )
  {
    v5 = Game_ptGame;
    v6 = (Game_ptGame->tRunRandomState.anRandom[0] >> 7) ^ Game_ptGame->tRunRandomState.anRandom[2];
    Game_ptGame->tRunRandomState.anRandom[2] = v6;
    v7 = v6 ^ v5->tRunRandomState.anRandom[1];
    v5->tRunRandomState.anRandom[1] = v7;
    v8 = v7 + v5->tRunRandomState.anRandom[0];
    v5->tRunRandomState.anRandom[0] = v8;
    Explosion0_NewEx(
      (struct real64x3_t *)(*(_DWORD *)pxContext + 8),
      1,
      0,
      0.0,
      2048.0,
      0.0,
      0.0,
      (v8 & 1) + 1,
      0,
      nullptr,
      (char *)(v4 + 50),
      (char *)&g_zInitialValue,
      -1,
      0x402u,
      49152.0,
      (struct real32x3_t *)((char *)pxContext + 8),
      0.5235987901687622,
      340.0,
      680.0,
      nullptr,
      nullptr,
      EXPLOSIONDAMAGE_LINEAR_FALLOFF);
  }
  if ( LODWORD(igi2_frame.ptvRGB.vX) )
  {
    Water_GunShotEffect(
      &v2->tPos,
      v2,
      *((float *)pxContext + 6),
      (struct TexInfo_s *)(*(_DWORD *)(v4 + 88) + 24),
      0,
      false);
  }
  else
  {
    ptHitObj = v2->ptHitObj;
    if ( v2->ptHitObj )
    {
      if ( *((_DWORD *)pxContext + 7) && (v10 = *(float *)(v4 + 88), v10 != 0.0)
        || (v10 = *(float *)(v4 + 92), v10 != 0.0) )
      {
        igi2_frame.ptvRGB.vX = v10;
        v11 = BulletHole_eCreateBulletHoleTaskEvent;
        if ( QTask_aatQTaskFinalEvent[v11][ptHitObj->tQTask.eQTaskType].pfHandler )
        {
          igi2_frame.ptQSprite.atQAnimframe = (struct QAnimframe_s *)(LODWORD(igi2_frame.ptvRGB.vX) + 24);
          igi2_frame.ptQSprite.ptQTilemap = *(struct QTilemap_s **)(v4 + 84);
          igi2_frame.ptQSprite.ptPalInfo = (struct PalInfo *)v2;
          igi2_frame.ptQSprite.atTexInfo = nullptr;
          ((void (__cdecl *)(struct QObj_s *, struct QSprite_s *))QTask_aatQTaskFinalEvent[v11][ptHitObj->tQTask.eQTaskType].pfHandler)(
            ptHitObj,
            &igi2_frame.ptQSprite);
        }
      }
    }
    if ( *(_BYTE *)v4 )
    {
      if ( !igi2_frame.ptVel )
      {
        v12 = Game_ptGame;
        v13 = (Game_ptGame->tRunRandomState.anRandom[0] >> 7) ^ Game_ptGame->tRunRandomState.anRandom[2];
        v14 = v13 ^ Game_ptGame->tRunRandomState.anRandom[1];
        Game_ptGame->tRunRandomState.anRandom[2] = v13;
        v15 = v14 + v12->tRunRandomState.anRandom[0];
        LOBYTE(v13) = v14 + LOBYTE(v12->tRunRandomState.anRandom[0]);
        v12->tRunRandomState.anRandom[1] = v14;
        v12->tRunRandomState.anRandom[0] = v15;
        if ( (v13 & 1) != 0 )
        {
          ptWorld = v12->ptWorld;
          igi2_frame.ptvRGB.vX = *((float *)pxContext + 5);
          igi2_frame.ptvRGB.vY = igi2_frame.ptvRGB.vX;
          igi2_frame.p_tQSprite = &GunShotEffect_ptConcreteDust1->tQSprite;
          igi2_frame.v24 = ptWorld;
          memset(&igi2_frame.ptQSprite, 0, 12);
          igi2_frame.ptvRGB.vZ = 127.0;
          igi2_frame.v30 = 1123942400;
          igi2_frame.v31 = 127.0;
          v17 = (struct QTask_s *)sub_52B6B0();
          v18 = Particle2DDynCubeObj_New(
                  v17,
                  igi2_frame.v24,
                  igi2_frame.p_tQSprite,
                  (struct real32x3_t *)&igi2_frame.ptQSprite,
                  (struct real32x3_t *)&igi2_frame.ptvRGB.vZ,
                  (struct real32x2_t *)&igi2_frame.ptvRGB,
                  4096000.0,
                  (int)&MTP_atLODVirModel[48].atBoneVertexRefs[1].atVertexRefs[668],
                  0,
                  0.08888889104127884,
                  0.0,
                  2,
                  nullptr);
          *(double *)&igi2_frame.ptQSprite.ptPalInfo = v2->tNormal.vX;
          *(double *)&igi2_frame.ptQSprite.atQAnimframe = v2->tNormal.vY;
          v19 = v18;
          *(double *)&igi2_frame.ptQSprite.nTextures = v2->tNormal.vZ;
          if ( !Real64x3_NullVector((struct real64x3_t *)&igi2_frame.ptQSprite) )
            Real64x3_Normalize((struct real64x3_t *)&igi2_frame.ptQSprite);
          igi2_frame.ptvRGB.vZ = 0.0;
          igi2_frame.v30 = 0;
          *(double *)&igi2_frame.ptQSprite.nTextures = *(double *)&igi2_frame.ptQSprite.nTextures * 491.5199890136719;
          *(double *)&igi2_frame.ptQSprite.ptPalInfo = *(double *)&igi2_frame.ptQSprite.ptPalInfo * 491.5199890136719 + v2->tPos.vX;
          *(double *)&igi2_frame.ptQSprite.atQAnimframe = *(double *)&igi2_frame.ptQSprite.atQAnimframe * 491.5199890136719 + v2->tPos.vY;
          *(double *)&igi2_frame.ptQSprite.nTextures = *(double *)&igi2_frame.ptQSprite.nTextures + v2->tPos.vZ;
          qmemcpy(&igi2_frame.ptPos, &igi2_frame.ptQSprite, sizeof(igi2_frame.ptPos));
          p_tRunRandomState = &Game_ptGame->tRunRandomState;
          igi2_frame.ptPos.vZ = igi2_frame.ptvRGB.vX * 0.25 + *(double *)&igi2_frame.ptQSprite.nTextures;
          igi2_frame.v31 = (Random_GetRandomNumberReal32(&Game_ptGame->tRunRandomState) * 0.75 + 0.15)
              * 4096000.0
              * 9.259259059035685e-06;
          igi2_frame.ptvRGB.vX = Random_GetRandomNumberReal32(p_tRunRandomState) * 0.25 + 0.75;
          RandomNumberReal32 = Random_GetRandomNumberReal32(p_tRunRandomState);
          vX = igi2_frame.ptvRGB.vX;
          igi2_frame.ptVela = (RandomNumberReal32 - 0.5 + RandomNumberReal32 - 0.5) * 0.05235987901687622 + 0.012799081392586231;
          Particle2DDynCubeObj_AddParticle(
            v19,
            (struct real64x3_t *)&igi2_frame.ptQSprite,
            (struct real32x3_t *)&igi2_frame.ptvRGB.vZ,
            igi2_frame.ptvRGB.vX,
            igi2_frame.ptVela,
            0.0,
            1.0,
            15,
            30);
          igi2_frame.v31 = igi2_frame.v31 * 1.25;
          v23 = Random_GetRandomNumberReal32(p_tRunRandomState);
          igi2_frame.ptVelb = (v23 - 0.5 + v23 - 0.5) * 0.05235987901687622 + 0.012799081392586231;
          Particle2DDynCubeObj_AddParticle(v19, &igi2_frame.ptPos, (struct real32x3_t *)&igi2_frame.ptvRGB.vZ, vX, igi2_frame.ptVelb, 0.0, 1.0, 15, 30);
        }
      }
    }
  }
}

// source: j/0/effects/gunshoteffect.c:292  [anchor-mhash]
void __cdecl GunShotEffect_ParseEffectParametersHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct GunShotEffectParameters_t *ptGunShotEffectParameters; };
    struct { char igi2_o1[4]; float pxData; };
    struct { char igi2_o2[8]; char *zName; };
    char igi2_extent[12];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct GunShotEffectParameters_t *v2; // ebx
  int v3; // esi
  struct ArgList_s *v4; // edi
  char v5; // al
  int v6; // esi
  char v7; // al
  int isQVM; // ecx
  int v9; // esi
  int v10; // esi
  int v11; // esi
  double v12; // st7
  int v13; // esi
  char *v14; // edx
  int v15; // esi

  v2 = *(struct GunShotEffectParameters_t **)pxContext;
  v3 = *((_DWORD *)pxContext + 2);
  v4 = *((struct ArgList_s **)pxContext + 1);
  igi2_frame.ptGunShotEffectParameters = *(struct GunShotEffectParameters_t **)pxContext;
  if ( v4->isQVM )
  {
    igi2_frame.pxData = 0.0;
    QVM_EvalArg(&igi2_frame.pxData, 4, v4, v3, 1);
    v5 = LOBYTE(igi2_frame.pxData);
  }
  else
  {
    v5 = Expression_EvalInt(v4->aptExpression[v3]);
  }
  v2->isSmoke = v5;
  v6 = v3 + 1;
  if ( v4->isQVM )
  {
    igi2_frame.pxData = 0.0;
    QVM_EvalArg(&igi2_frame.pxData, 4, v4, v6, 1);
    v7 = LOBYTE(igi2_frame.pxData);
  }
  else
  {
    v7 = Expression_EvalInt(v4->aptExpression[v6]);
  }
  v2->isParticle = v7;
  isQVM = v4->isQVM;
  v9 = v6 + 1;
  igi2_frame.zName = v2->zPenetratingBulletHole;
  if ( isQVM )
  {
    v2->zPenetratingBulletHole[0] = 0;
    QVM_EvalArg(v2->zPenetratingBulletHole, 24, v4, v9, 3);
  }
  else
  {
    Expression_EvalString(v4->aptExpression[v9], v2->zPenetratingBulletHole, 24);
  }
  v10 = v9 + 1;
  if ( v4->isQVM )
  {
    v2->zNonPenetratingBulletHole[0] = 0;
    QVM_EvalArg(v2->zNonPenetratingBulletHole, 24, v4, v10, 3);
  }
  else
  {
    Expression_EvalString(v4->aptExpression[v10], v2->zNonPenetratingBulletHole, 24);
  }
  v11 = v10 + 1;
  if ( v4->isQVM )
  {
    igi2_frame.pxData = 0.0;
    QVM_EvalArg(&igi2_frame.pxData, 4, v4, v11, 2);
    v12 = igi2_frame.pxData;
  }
  else
  {
    v12 = Expression_EvalFloat(v4->aptExpression[v11]);
  }
  v13 = v11 + 1;
  v2->vBulletHoleSize = v12 * 4096.0;
  if ( v4->isQVM )
  {
    v2->zModelName[0] = 0;
    QVM_EvalArg(v2->zModelName, 32, v4, v13, 3);
  }
  else
  {
    Expression_EvalString(v4->aptExpression[v13], v2->zModelName, 32);
  }
  v14 = igi2_frame.zName;
  v15 = v13 + 1;
  igi2_frame.zName = (char *)strlen(igi2_frame.zName);
  if ( igi2_frame.zName )
  {
    igi2_frame.ptGunShotEffectParameters->ptPenetratingBulletHole = GameFunctions_RegisterGameTexture(v14);
    v2 = igi2_frame.ptGunShotEffectParameters;
  }
  else
  {
    v2->ptPenetratingBulletHole = nullptr;
  }
  igi2_frame.zName = (char *)strlen(v2->zNonPenetratingBulletHole);
  if ( igi2_frame.zName )
    igi2_frame.ptGunShotEffectParameters->ptNonPenetratingBulletHole = GameFunctions_RegisterGameTexture(v2->zNonPenetratingBulletHole);
  else
    v2->ptNonPenetratingBulletHole = nullptr;
  *((_DWORD *)pxContext + 3) = v15 - *((_DWORD *)pxContext + 2);
}

// source: j/0/effects/gunshoteffect.c:347  [size]
void __cdecl GunShotEffect_GetEffectParametersSizeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = 96;
}

// source: j/0/effects/gunshoteffect.c:365  [anchor-hash]
void __cdecl GunShotEffect_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("GunShotEffect", 40, BaseQTaskType, 0, 0);
  GunShotEffect_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(
    v1,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskDontSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v1, GameMaterial_eCreateEffectQTaskEvent, GunShotEffect_CreateEffectHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    GameMaterial_eParseEffectParametersQTaskEvent,
    GunShotEffect_ParseEffectParametersHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    GameMaterial_eGetEffectParametersSizeQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))GunShotEffect_GetEffectParametersSizeHandler);
  Symbol_Register(
    "TASKTYPE_GUNSHOTEFFECT",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)v1,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  GunShotEffect_ptConcreteDust1 = GameFunctions_RegisterGameSprite("concrete1.spr");
  GunShotEffect_ptConcreteDust2 = GameFunctions_RegisterGameSprite("concrete2.spr");
}
