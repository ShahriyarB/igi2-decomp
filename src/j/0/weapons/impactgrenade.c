/* j/0/weapons/impactgrenade.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/weapons/impactgrenade.c:119  [anchor-mhash]
void __cdecl ImpactGrenade_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct World_s *ptWorld; };
    struct { char igi2_o1[52]; float ptDynCubeObj; };
    struct { char igi2_o2[72]; struct real32x3_t ptvRGB; };
    struct { char igi2_o3[84]; int v12; };
    struct { char igi2_o4[88]; int v13; };
    struct { char igi2_o5[92]; struct QSprite_s ptQSprite; };
    char igi2_extent[116];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v2; // st7
  double v3; // st7
  int *v4; // eax
  int v5; // eax
  double v6; // st6
  struct Game_s *v7; // edx
  struct QTask_s *v8; // eax

  memset(&igi2_frame.ptQSprite, 0, sizeof(igi2_frame.ptQSprite));
  QTaskList_Register(GameFunctions_ptCutsceneDeleteQTaskList, (struct QTaskList_s *)ptQTask);
  ModelObj_Init((struct ModelObj_s *)ptQTask, Game_ptGame->ptWorld, nullptr);
  ptQTask[7].tQTaskChildren.ptHead = nullptr;
  ptQTask[7].tQTaskChildren.ptMiddle = (struct QTask_s *)2;
  ptQTask[7].tQTaskRefList.ptHead = nullptr;
  ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[7].tQTaskRefList.ptTail = nullptr;
  ptQTask[7].ptParent = nullptr;
  *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
    v2 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  else
    v2 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  if ( v2 >= *(float *)&ptQTask[6].ptPrev )
  {
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
      v3 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v3 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  }
  else
  {
    v3 = *(float *)&ptQTask[6].ptPrev;
  }
  v4 = *(int **)&ptQTask[2].eQTaskType;
  if ( v4 && (v5 = *v4) != 0 )
    v6 = *(float *)(*(_DWORD *)(*(_DWORD *)(v5 + 12) + 12) + 120);
  else
    v6 = 1.0;
  igi2_frame.ptDynCubeObj = v3 * v6;
  World_RegisterDynCubeObjFirstTimeRadius(
    Game_ptGame->ptWorld,
    (struct DynCubeObj_s *)ptQTask,
    (struct real64x3_t *)&igi2_frame.ptQSprite,
    igi2_frame.ptDynCubeObj,
    WORLD_DYNCUBETREE_CATEGORY_MOBILE);
  v7 = Game_ptGame;
  ptQTask[9].ptNext = nullptr;
  *(_DWORD *)&ptQTask[8].eQTaskType = 0;
  ptQTask[9].ptPrev = nullptr;
  ptQTask[9].tQTaskChildren.ptHead = nullptr;
  igi2_frame.ptWorld = v7->ptWorld;
  memset(&igi2_frame.ptQSprite, 0, 12);
  igi2_frame.ptvRGB.vZ = 127.0;
  igi2_frame.v12 = 1123942400;
  igi2_frame.v13 = 1123942400;
  igi2_frame.ptvRGB.vX = 614.4000244140625;
  igi2_frame.ptvRGB.vY = 614.4000244140625;
  v8 = Particle2DDynCubeObj_New(
         Level_ptDynamicQTask,
         igi2_frame.ptWorld,
         &ImpactGrenade_ptSmoke->tQSprite,
         (struct real32x3_t *)&igi2_frame.ptQSprite,
         (struct real32x3_t *)&igi2_frame.ptvRGB.vZ,
         (struct real32x2_t *)&igi2_frame.ptvRGB,
         819200.0,
         (int)&MTP_atLODVirModel[45].atBoneVertexRefs[20].atVertexRefs[783],
         0,
         0.10000000149011612,
         0.0,
         20,
         nullptr);
  ptQTask[9].tQTaskChildren.ptHead = (struct QTask_s *)QTask_NewQTaskRef(v8);
}

// source: j/0/weapons/impactgrenade.c:196  [anchor-strings]
void __cdecl ImpactGrenade_RunHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[16]; float vFullRange; };
    struct { char igi2_o2[16]; float vFullRangea; };
    struct { char igi2_o3[16]; float vFullRangeb; };
    struct { char igi2_o4[20]; struct real32x3_t nNumPoints; };
    struct { char igi2_o5[32]; struct QTask_s *ptHead; };
    struct { char igi2_o6[36]; int v23; };
    struct { char igi2_o7[40]; struct real64x3_t *ptPos; };
    struct { char igi2_o8[44]; struct QIntersection_s ptIntersection; };
    struct { char igi2_o9[208]; int v26; };
    char igi2_extent[236];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v1; // st7
  double v2; // st6
  double v3; // rt0
  double v4; // st6
  int v5; // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptNext; // eax
  struct QTask_s *v8; // eax
  double v9; // st7
  double v10; // st7
  int *v11; // eax
  int v12; // eax
  double v13; // st6
  struct QTask_s *v14; // eax
  struct RandomState_s *p_tRunRandomState; // esi
  double RandomNumberReal32; // st7

  v1 = *(float *)&ptQTask[8].tQTaskRefList.ptMiddle * 0.9950000047683716;
  *(float *)&ptQTask[8].tQTaskRefList.ptMiddle = v1;
  v2 = *(float *)&ptQTask[8].tQTaskRefList.ptTail * 0.9950000047683716;
  qmemcpy(&igi2_frame.ptIntersection, &ptQTask[8], 0x18u);
  *(float *)&ptQTask[8].tQTaskRefList.ptTail = v2;
  igi2_frame.vFullRange = (*(float *)&ptQTask[8].ptParent - 35.68070983886719) * 0.9950000047683716;
  *(float *)&ptQTask[8].ptParent = igi2_frame.vFullRange;
  v3 = v2;
  v4 = v1 + *(double *)&ptQTask[8].ptNext;
  LODWORD(igi2_frame.nNumPoints.vY) = ptQTask;
  *(double *)&ptQTask[8].ptNext = v4;
  v5 = *(_DWORD *)&ptQTask[8].eQTaskType;
  *(double *)&ptQTask[8].tQTaskChildren.ptHead = v3 + *(double *)&ptQTask[8].tQTaskChildren.ptHead;
  *(double *)&ptQTask[8].tQTaskChildren.ptTail = igi2_frame.vFullRange + *(double *)&ptQTask[8].tQTaskChildren.ptTail;
  qmemcpy(&igi2_frame.ptIntersection.tLocalNormal.vY, &ptQTask[8], 0x18u);
  if ( v5 )
    igi2_frame.nNumPoints.vZ = *(float *)(v5 + 8);
  else
    igi2_frame.nNumPoints.vZ = 0.0;
  ptPrev = ptQTask[9].ptPrev;
  if ( ptPrev )
    igi2_frame.ptHead = ptPrev->tQTaskChildren.ptHead;
  else
    igi2_frame.ptHead = nullptr;
  igi2_frame.v23 = 1065353216;
  World_TraceLines(
    Game_ptGame->ptWorld,
    (struct QIntersection_s *)&igi2_frame.ptIntersection.iFace,
    (struct real64x3_t *)&igi2_frame.ptIntersection,
    (struct real64x3_t *)&igi2_frame.ptIntersection.tLocalNormal.vY,
    1,
    GameFunctions_eWeaponCollisionEvaluateQTaskEvent,
    (struct CollisionEvaluateContext_s *)&igi2_frame.nNumPoints,
    0xFFFFFFFF);
  if ( igi2_frame.v26 )
  {
    ptNext = ptQTask[9].ptNext;
    if ( ptNext )
      v8 = ptNext->tQTaskChildren.ptHead;
    else
      v8 = nullptr;
    igi2_frame.vFullRangea = *(float *)&ptQTask[9].tQTaskChildren.ptMiddle * 2048.0;
    Explosion0_New(
      (struct real64x3_t *)&igi2_frame.ptIntersection.ptEnterMaterial,
      1,
      1,
      *(float *)&ptQTask[9].tQTaskChildren.ptTail,
      igi2_frame.vFullRangea,
      igi2_frame.vFullRangea,
      4096.0,
      3,
      1,
      (struct QIntersection_s *)&igi2_frame.ptIntersection.iFace,
      "1009_01_1",
      "explo_proxy",
      20,
      0x402u,
      307200.0,
      nullptr,
      v8,
      EXPLOSIONDAMAGE_LINEAR_FALLOFF);
    QTask_Delete(ptQTask);
  }
  else
  {
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
      v9 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v9 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
    if ( v9 >= *(float *)&ptQTask[6].ptPrev )
    {
      if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
        v10 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
      else
        v10 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
    }
    else
    {
      v10 = *(float *)&ptQTask[6].ptPrev;
    }
    v11 = *(int **)&ptQTask[2].eQTaskType;
    if ( v11 && (v12 = *v11) != 0 )
      v13 = *(float *)(*(_DWORD *)(*(_DWORD *)(v12 + 12) + 12) + 120);
    else
      v13 = 1.0;
    igi2_frame.ptDynCubeObj = v10 * v13;
    World_MoveDynCubeObjRadius(
      Game_ptGame->ptWorld,
      (struct DynCubeObj_s *)ptQTask,
      (struct real64x3_t *)&ptQTask[8],
      igi2_frame.ptDynCubeObj);
    v14 = ptQTask[9].tQTaskChildren.ptHead;
    if ( v14 && v14->tQTaskChildren.ptHead )
    {
      qmemcpy(&igi2_frame.ptIntersection.tPos.vZ, &ptQTask[8], 0x18u);
      p_tRunRandomState = &Game_ptGame->tRunRandomState;
      igi2_frame.nNumPoints.vX = 0.0;
      igi2_frame.nNumPoints.vY = 0.0;
      igi2_frame.nNumPoints.vZ = (Random_GetRandomNumberReal32(&Game_ptGame->tRunRandomState) * 0.75 + 0.15)
                    * 4096000.0
                    * 9.259259059035685e-06;
      *(float *)&igi2_frame.ptPos = (Random_GetRandomNumberReal32(p_tRunRandomState) + 1.0) * 0.35;
      RandomNumberReal32 = Random_GetRandomNumberReal32(p_tRunRandomState);
      igi2_frame.vFullRangeb = (RandomNumberReal32 - 0.5 + RandomNumberReal32 - 0.5) * 0.05235987901687622 + 0.012799081392586231;
      Particle2DDynCubeObj_AddParticle(
        ptQTask[9].tQTaskChildren.ptHead->tQTaskChildren.ptHead,
        (struct real64x3_t *)&igi2_frame.ptIntersection.tPos.vZ,
        &igi2_frame.nNumPoints,
        *(float *)&igi2_frame.ptPos,
        igi2_frame.vFullRangeb,
        0.0,
        1.0,
        7,
        7);
    }
  }
}

// source: j/0/weapons/impactgrenade.c:362  [anchor-mhash]
void __cdecl ImpactGrenade_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QReference_s *v1; // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptHead; // eax

  if ( *(_DWORD *)&ptQTask[2].eQTaskType )
  {
    ModelObj_SetLODVirModel((struct ModelObj_s *)ptQTask, nullptr, false);
    ptQTask[7].tQTaskRefList.ptHead = nullptr;
    ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
    ptQTask[7].tQTaskRefList.ptTail = nullptr;
    ptQTask[7].ptParent = nullptr;
    *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  }
  QTaskList_Remove(GameFunctions_ptCutsceneDeleteQTaskList, ptQTask);
  World_RemoveDynCubeObj(Game_ptGame->ptWorld, (struct DynCubeObj_s *)ptQTask);
  v1 = *(struct QReference_s **)&ptQTask[8].eQTaskType;
  if ( v1 )
  {
    QReference_Delete(v1, &QTask_tQTaskRefPool);
    *(_DWORD *)&ptQTask[8].eQTaskType = 0;
  }
  ptPrev = ptQTask[9].ptPrev;
  if ( ptPrev )
  {
    QReference_Delete((struct QReference_s *)ptPrev, &QTask_tQTaskRefPool);
    ptQTask[9].ptPrev = nullptr;
  }
  ptNext = ptQTask[9].ptNext;
  if ( ptNext )
  {
    QReference_Delete((struct QReference_s *)ptNext, &QTask_tQTaskRefPool);
    ptQTask[9].ptNext = nullptr;
  }
  ptHead = ptQTask[9].tQTaskChildren.ptHead;
  if ( ptHead )
  {
    QReference_Delete((struct QReference_s *)ptHead, &QTask_tQTaskRefPool);
    ptQTask[9].tQTaskChildren.ptHead = nullptr;
  }
}

// source: j/0/weapons/impactgrenade.c:414  [anchor-strings]
void __cdecl ImpactGrenade_CreateWeaponTypeParametersHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v2; // eax
  struct QTask_s *v3; // edi
  struct QTask_s *v4; // ebp
  struct QTask_s *v5; // eax
  struct StaticTilemap_s *p_tQTaskRefList; // eax
  int v7; // edx
  char ptQTilemap; // cl
  struct QTask_s *v9; // edi
  struct QTask_s *v10; // eax
  double v11; // st7
  struct QTask_s *v12; // edi
  struct QTask_s *v13; // eax

  v2 = QTask_NewFn(nullptr, ImpactGrenade_eImpactGrenadeQTaskType, nullptr);
  v3 = *((struct QTask_s **)pxContext + 1);
  v4 = v2;
  *((_DWORD *)pxContext + 2) = v2;
  v5 = TagItem_Find(v3, "Model Name");
  if ( v5 || (v5 = TagItem_NewString16(v3, "Model Name", (char *)&g_zInitialValue)) != nullptr )
    p_tQTaskRefList = (struct StaticTilemap_s *)&v5[7].tQTaskRefList;
  else
    p_tQTaskRefList = &g_zInitialValue;
  v7 = (char *)v4 - (char *)p_tQTaskRefList + 40;
  do
  {
    ptQTilemap = (char)p_tQTaskRefList->ptQTilemap;
    *((_BYTE *)&p_tQTaskRefList->ptQTilemap + v7) = p_tQTaskRefList->ptQTilemap;
    p_tQTaskRefList = (struct StaticTilemap_s *)((char *)p_tQTaskRefList + 1);
  }
  while ( ptQTilemap );
  v9 = *((struct QTask_s **)pxContext + 1);
  v10 = TagItem_Find(v9, (char *)&stru_692970.tQTaskRefList);
  if ( v10 || (v10 = TagItem_NewReal32MinMax(v9, (char *)&stru_692970.tQTaskRefList, 1.0, 0.0, 1.0)) != nullptr )
    v11 = *(float *)&v10[7].tQTaskRefList.ptHead;
  else
    v11 = 0.0;
  *(float *)&v4[1].ptParent = v11;
  v12 = *((struct QTask_s **)pxContext + 1);
  v13 = TagItem_Find(v12, (char *)&stru_692970);
  if ( v13 || (v13 = TagItem_NewReal32(v12, (char *)&stru_692970, 1.0)) != nullptr )
    *(_DWORD *)&v4[1].eQTaskType = v13[7].tQTaskRefList.ptHead;
  else
    *(_DWORD *)&v4[1].eQTaskType = 0;
}

// source: j/0/weapons/impactgrenade.c:458  [anchor-mhash]
void __cdecl ImpactGrenade_CreateProjectileHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s *v11; };
    struct { char igi2_o1[4]; struct real64x3_t *v12; };
    struct { char igi2_o2[8]; struct real32x9_t *v13; };
    struct { char igi2_o3[16]; char *v14; };
    struct { char igi2_o4[20]; float v15; };
    struct { char igi2_o5[24]; float v16; };
    struct { char igi2_o6[28]; struct real32x3_t tSpeed; };
    struct { char igi2_o7[40]; struct real32x3_t Real32x3_Rotate_tTemp; };
    char igi2_extent[52];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  float *v2; // eax
  int v3; // edx
  double v4; // st7
  double v5; // st7
  struct real32x9_t *v6; // eax
  struct real64x3_t *v7; // edx
  struct QTask_s *v8; // eax
  struct QTask_s *v9; // edx
  struct QTask_s *v10; // eax

  v2 = *((float **)pxContext + 8);
  v3 = *((_DWORD *)pxContext + 17) + 40;
  igi2_frame.Real32x3_Rotate_tTemp.vX = (v2[2] + *v2) * 0.0 + v2[1];
  igi2_frame.Real32x3_Rotate_tTemp.vY = (v2[5] + v2[3]) * 0.0 + v2[4];
  v4 = (v2[8] + v2[6]) * 0.0 + v2[7];
  igi2_frame.tSpeed.vX = igi2_frame.Real32x3_Rotate_tTemp.vX;
  igi2_frame.Real32x3_Rotate_tTemp.vZ = v4;
  igi2_frame.tSpeed.vY = igi2_frame.Real32x3_Rotate_tTemp.vY;
  v5 = *((float *)pxContext + 10) * 136.53334045410156;
  igi2_frame.tSpeed.vZ = igi2_frame.Real32x3_Rotate_tTemp.vZ;
  igi2_frame.v16 = *(float *)(v3 + 32);
  igi2_frame.v15 = *(float *)(v3 + 36);
  v6 = *((struct real32x9_t **)pxContext + 9);
  igi2_frame.v14 = (char *)v3;
  igi2_frame.tSpeed.vX = igi2_frame.Real32x3_Rotate_tTemp.vX * v5;
  v7 = *((struct real64x3_t **)pxContext + 4);
  igi2_frame.v13 = v6;
  v8 = *((struct QTask_s **)pxContext + 1);
  igi2_frame.tSpeed.vY = igi2_frame.Real32x3_Rotate_tTemp.vY * v5;
  igi2_frame.v12 = v7;
  v9 = *((struct QTask_s **)pxContext + 3);
  igi2_frame.v11 = v8;
  v10 = *((struct QTask_s **)pxContext + 2);
  igi2_frame.tSpeed.vZ = v5 * igi2_frame.Real32x3_Rotate_tTemp.vZ;
  ImpactGrenade_New(Level_ptDynamicQTask, v10, v9, igi2_frame.v11, igi2_frame.v12, igi2_frame.v13, &igi2_frame.tSpeed, igi2_frame.v14, igi2_frame.v15, igi2_frame.v16);
}

// source: j/0/weapons/impactgrenade.c:554  [anchor-mhash]
struct QTask_s *__cdecl ImpactGrenade_New(
        struct QTask_s *ptParent,
        struct QTask_s *ptCreatorQTask,
        struct QTask_s *ptIgnoreQTask,
        struct QTask_s *ptOwnerQTask,
        struct real64x3_t *ptPos,
        struct real32x9_t *ptOrientation,
        struct real32x3_t *ptSpeed,
        char *zModel,
        float vExplosionRadius,
        float vExplosionDamage)
{
  struct QTask_s *v11; // ebx
  struct LODVirModel_s *LODVirModelExistsFn; // eax

  v11 = QTask_NewFn(ptParent, ImpactGrenade_eQTaskType, nullptr);
  if ( ptCreatorQTask )
    *(_DWORD *)&v11[8].eQTaskType = QTask_NewQTaskRef(ptCreatorQTask);
  if ( ptIgnoreQTask )
    v11[9].ptPrev = (struct QTask_s *)QTask_NewQTaskRef(ptIgnoreQTask);
  if ( ptOwnerQTask )
    v11[9].ptNext = (struct QTask_s *)QTask_NewQTaskRef(ptOwnerQTask);
  qmemcpy(&v11[8], ptPos, 0x18u);
  qmemcpy(&v11[3].ptPrev, ptOrientation, sizeof(struct QTask_s));
  *(struct real32x3_t *)&v11[8].tQTaskRefList.ptMiddle = *ptSpeed;
  LODVirModelExistsFn = MTP_GetLODVirModelExistsFn(zModel);
  if ( LODVirModelExistsFn != *(struct LODVirModel_s **)&v11[2].eQTaskType )
  {
    ModelObj_SetLODVirModel((struct ModelObj_s *)v11, LODVirModelExistsFn, false);
    v11[7].tQTaskRefList.ptHead = nullptr;
    v11[7].tQTaskRefList.ptMiddle = nullptr;
    v11[7].tQTaskRefList.ptTail = nullptr;
    v11[7].ptParent = nullptr;
    *(_DWORD *)&v11[7].eQTaskType = 0;
  }
  *(float *)&v11[9].tQTaskChildren.ptTail = vExplosionDamage;
  *(float *)&v11[9].tQTaskChildren.ptMiddle = vExplosionRadius;
  return v11;
}

struct GameSprite_t *sub_4CC9D0()
{
  unsigned __int16 v0; // ax
  unsigned __int16 v1; // si
  struct GameSprite_t *result; // eax

  ImpactGrenade_eQTaskType = QTask_NewQTaskType("ImpactGrenade", 384, RigidDynCubeObj_eQTaskType, 0, 0);
  v0 = QTask_NewQTaskType("ImpactGrenadeParameters", 80, WeaponTypeParameters_eQTaskType, 0, 0);
  v1 = ImpactGrenade_eQTaskType;
  ImpactGrenade_eImpactGrenadeQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(ImpactGrenade_eQTaskType, 0, ImpactGrenade_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, ImpactGrenade_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, ImpactGrenade_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    GameFunctions_eWeaponCollisionEvaluateQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))GameFunctions_WeaponCollisionEvaluateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    WeaponType_eCreateParametersQTaskEvent,
    ImpactGrenade_CreateWeaponTypeParametersHandler);
  QTask_LinkQTaskEventHandlerFn(v1, Weapon_eCreateProjectileQTaskEvent, ImpactGrenade_CreateProjectileHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    Serialize_eDeSerializeDoneQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))NetworkCommand_Close);
  Symbol_Register(
    "TASKTYPE_IMPACTGRENADE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)v1,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  result = GameFunctions_RegisterGameSprite("smoke1.spr");
  ImpactGrenade_ptSmoke = result;
  return result;
}
