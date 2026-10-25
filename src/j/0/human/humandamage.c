/* j/0/human/humandamage.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/human/humandamage.c:49  [anchor-mhash]
struct HumanDamage_t *__cdecl HumanDamage_Init(
        struct HumanDamage_t *ptHumanDamage,
        struct DamagePartData_t *ptDamagePartData,
        float vMaxDamage)
{
  ptHumanDamage->vMaxDamage = vMaxDamage;
  ptHumanDamage->ptDamagePartData = ptDamagePartData;
  HumanDamage_ClearDamage(ptHumanDamage);
  ptHumanDamage->eDamagePart = HUMANDAMAGE_PART_NONE;
  ptHumanDamage->ptBlood1QTaskRef = nullptr;
  ptHumanDamage->ptBlood2QTaskRef = nullptr;
  return nullptr;
}

// source: j/0/human/humandamage.c:76  [anchor-hash]
void __cdecl HumanDamage_DeInit(struct HumanDamage_t *ptHumanDamage)
{
  struct QReference_s *ptBlood1QTaskRef; // eax
  struct QReference_s *ptBlood2QTaskRef; // eax

  ptBlood1QTaskRef = ptHumanDamage->ptBlood1QTaskRef;
  if ( ptBlood1QTaskRef )
    QReference_Delete(ptBlood1QTaskRef, &QTask_tQTaskRefPool);
  ptBlood2QTaskRef = ptHumanDamage->ptBlood2QTaskRef;
  if ( ptBlood2QTaskRef )
    QReference_Delete(ptBlood2QTaskRef, &QTask_tQTaskRefPool);
}

// source: j/0/human/humandamage.c:97  [anchor-callee]
enum DamagePart_e __cdecl HumanDamage_GetDamagePartFromWeaponHit(
        struct HumanDamage_t *ptHumanDamage,
        struct BoneDynCubeObj_s *ptBoneDynCubeObj,
        struct WeaponHitContext_t *ptWeaponHitContext)
{
  float vY; // edx
  float vZ; // eax
  double v5; // st7
  double v6; // st6
  int iSector; // ebx
  double v8; // st5
  unsigned __int8 *pcHierarchy; // esi
  enum DamagePart_e v10; // ebx
  double v11; // st7
  double v12; // st6
  double v13; // st6
  struct QIntersection_s *ptIntersection; // ebp
  enum DamagePart_e result; // eax
  struct real64x3_t tPos; // [esp+Ch] [ebp-1Ch] BYREF

  vY = ptWeaponHitContext->tDirection.vY;
  vZ = ptWeaponHitContext->tDirection.vZ;
  *(float *)&tPos.vX = ptWeaponHitContext->tDirection.vX;
  v5 = -*(float *)&tPos.vX;
  *((float *)&tPos.vX + 1) = vY;
  *(float *)&tPos.vY = vZ;
  v6 = -vY;
  iSector = ptWeaponHitContext->ptIntersection->iSector;
  v8 = -vZ;
  pcHierarchy = ptBoneDynCubeObj->pcHierarchy;
  *(float *)&tPos.vX = v8 * ptBoneDynCubeObj->tModelObj.tOrientation.tZ.vX
                     + v6 * ptBoneDynCubeObj->tModelObj.tOrientation.tY.vX
                     + v5 * ptBoneDynCubeObj->tModelObj.tOrientation.tX.vX;
  *((float *)&tPos.vX + 1) = v8 * ptBoneDynCubeObj->tModelObj.tOrientation.tZ.vY
                           + v6 * ptBoneDynCubeObj->tModelObj.tOrientation.tY.vY
                           + v5 * ptBoneDynCubeObj->tModelObj.tOrientation.tX.vY;
  v10 = *(_DWORD *)(HumanAnim_FindAnimatedInfo(pcHierarchy) + 4 * iSector + 1028);
  if ( v10 == HUMANDAMAGE_PART_UPPERBODY )
  {
    if ( *((float *)&tPos.vX + 1) <= 0.0 )
    {
      v11 = *((float *)&tPos.vX + 1);
      if ( *((float *)&tPos.vX + 1) < 0.0 )
        v11 = -v11;
      v12 = *(float *)&tPos.vX;
      if ( *(float *)&tPos.vX < 0.0 )
        v12 = -v12;
      if ( v11 > v12 )
        v10 = HUMANDAMAGE_PART_BACK;
    }
    if ( *((float *)&tPos.vX + 1) < 0.0 )
      return v10;
    v13 = *(float *)&tPos.vX;
    if ( *(float *)&tPos.vX < 0.0 )
      v13 = -v13;
    if ( *((float *)&tPos.vX + 1) > v13 )
      v10 = HUMANDAMAGE_PART_CHEST;
  }
  if ( *((float *)&tPos.vX + 1) < 0.0 )
    return v10;
  BoneDynCubeObj_GetMagicVertexPos(ptBoneDynCubeObj, 1u, &tPos);
  ptIntersection = ptWeaponHitContext->ptIntersection;
  result = HUMANDAMAGE_PART_GROIN;
  if ( sqrt(
         (ptIntersection->tPos.vY - tPos.vY) * (ptIntersection->tPos.vY - tPos.vY)
       + (ptIntersection->tPos.vZ - tPos.vZ) * (ptIntersection->tPos.vZ - tPos.vZ)
       + (ptIntersection->tPos.vX - tPos.vX) * (ptIntersection->tPos.vX - tPos.vX)) >= 614.4 )
    return v10;
  return result;
}

// source: j/0/human/humandamage.c:178  [size]
struct DamagePartData_t *__cdecl HumanDamage_GetDamagePartData(
        struct HumanDamage_t *ptHumanDamage,
        enum DamagePart_e eDamagePart)
{
  return &ptHumanDamage->ptDamagePartData[eDamagePart];
}

// source: j/0/human/humandamage.c:191  [anchor-hash]
void __cdecl HumanDamage_ClearDamage(struct HumanDamage_t *ptHumanDamage)
{
  int v1; // edx
  struct DamagePart_t *atDamagePart; // ecx
  struct DamagePartData_t *v3; // eax

  ptHumanDamage->vDamage = 0.0;
  v1 = 0;
  atDamagePart = ptHumanDamage->atDamagePart;
  do
  {
    v3 = &ptHumanDamage->ptDamagePartData[v1];
    atDamagePart->vDamage = 0.0;
    atDamagePart->vDamageMultiplier = v3->vDamageMultiplier;
    ++v1;
    ++atDamagePart;
  }
  while ( v1 < 17 );
}

// source: j/0/human/humandamage.c:224  [anchor-mhash]
void __cdecl HumanDamage_BloodParticle2DCollisionCallback(
        struct Particle2DCollisionContext_t *ptParticle2DCollisionContext)
{
  int v1; // ebx
  struct QIntersection_s *ptIntersection; // edi
  double v3; // st7
  double v4; // st6
  double v5; // st5
  long double v6; // st4
  struct RandomState_s *p_tRunRandomState; // esi
  double RandomNumberReal32; // st7
  unsigned int v9; // ecx
  double v10; // st7
  int v11; // eax
  int v12; // eax
  unsigned int v13; // edx
  struct TexInfo_s *p_tTexInfo; // eax
  struct QObj_s *ptHitObj; // edi
  struct CreateBulletHoleContext_t tCreateBulletHoleContext; // [esp+10h] [ebp-10h] BYREF

  v1 = BulletHole_eCreateBulletHoleTaskEvent;
  ptIntersection = ptParticle2DCollisionContext->ptIntersection;
  if ( QTask_aatQTaskFinalEvent[v1][ptParticle2DCollisionContext->ptIntersection->ptHitObj->tQTask.eQTaskType].pfHandler )
  {
    v3 = ptParticle2DCollisionContext->tPos0.vX - ptParticle2DCollisionContext->tPos1.vX;
    v4 = ptParticle2DCollisionContext->tPos0.vY - ptParticle2DCollisionContext->tPos1.vY;
    v5 = ptParticle2DCollisionContext->tPos0.vZ - ptParticle2DCollisionContext->tPos1.vZ;
    if ( ptIntersection->tNormal.vX != 0.0 || ptIntersection->tNormal.vY != 0.0 || ptIntersection->tNormal.vZ != 0.0 )
    {
      v6 = 1.0
         / sqrt(
             ptIntersection->tNormal.vX * ptIntersection->tNormal.vX
           + ptIntersection->tNormal.vY * ptIntersection->tNormal.vY
           + ptIntersection->tNormal.vZ * ptIntersection->tNormal.vZ);
      ptIntersection->tNormal.vX = ptIntersection->tNormal.vX * v6;
      ptIntersection->tNormal.vY = ptIntersection->tNormal.vY * v6;
      ptIntersection->tNormal.vZ = ptIntersection->tNormal.vZ * v6;
    }
    if ( v5 * ptIntersection->tNormal.vZ + v4 * ptIntersection->tNormal.vY + v3 * ptIntersection->tNormal.vX < 0.0 )
    {
      p_tRunRandomState = &Game_ptGame->tRunRandomState;
      RandomNumberReal32 = Random_GetRandomNumberReal32(&Game_ptGame->tRunRandomState);
      v9 = p_tRunRandomState->anRandom[1];
      v10 = RandomNumberReal32 * 204.8000030517578 + 102.4000015258789;
      v11 = (p_tRunRandomState->anRandom[0] >> 7) ^ p_tRunRandomState->anRandom[2];
      p_tRunRandomState->anRandom[2] = v11;
      v12 = v11 ^ v9;
      v13 = v12 + p_tRunRandomState->anRandom[0];
      p_tRunRandomState->anRandom[1] = v12;
      p_tRunRandomState->anRandom[0] = v13;
      if ( (v13 & 1) != 0 )
      {
        if ( (v13 & 1) == 1 )
          p_tTexInfo = &HumanDamage_ptBloodStain4->tTexInfo;
        else
          p_tTexInfo = (struct TexInfo_s *)ptParticle2DCollisionContext;
      }
      else
      {
        p_tTexInfo = &HumanDamage_ptBloodStain3->tTexInfo;
      }
      tCreateBulletHoleContext.ptIntersection = ptIntersection;
      tCreateBulletHoleContext.vRadius = v10;
      ptHitObj = ptIntersection->ptHitObj;
      tCreateBulletHoleContext.ptTexInfo = p_tTexInfo;
      tCreateBulletHoleContext.nBulletHoleType = 0;
      ((void (__cdecl *)(struct QObj_s *, struct CreateBulletHoleContext_t *))QTask_aatQTaskFinalEvent[v1][ptHitObj->tQTask.eQTaskType].pfHandler)(
        ptHitObj,
        &tCreateBulletHoleContext);
    }
  }
}

// source: j/0/human/humandamage.c:294  [anchor-callee]
void __cdecl HumanDamage_CreateFleshEnterEffect(
        struct HumanDamage_t *ptHumanDamage,
        struct real32x3_t *ptDirection,
        struct real64x3_t *ptPos,
        struct QTask_s *ptIgnoreQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vIntensity; };
    struct { float vIntensitya; };
    struct { char igi2_o2[32]; struct real32x3_t ptDir; };
    struct { char igi2_o3[44]; struct real32x3_t ptvRGB; };
    struct { char igi2_o4[56]; float v57; };
    struct { char igi2_o5[60]; float v58; };
    struct { char igi2_o6[64]; struct QSprite_s ptQSprite; };
    struct { char igi2_o7[88]; float v60; };
    struct { char igi2_o8[92]; struct real64x3_t ptEnd; };
    struct { char igi2_o9[116]; struct QIntersection_s ptIntersection; };
    struct { char igi2_o10[240]; int v63; };
    char igi2_extent[268];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  float vY; // eax
  float vZ; // ecx
  long double v6; // st4
  struct QTask_s *v7; // esi
  int v8; // eax
  struct RandomState_s *p_tRunRandomState; // esi
  double v10; // st7
  unsigned int RandomNumberBelowLimit; // eax
  float vX; // eax
  void (__cdecl *pfHandler)(_DWORD, struct QTilemap_s **); // eax
  struct QReference_s *ptBlood1QTaskRef; // eax
  struct QTask_s *pxObject; // ebx
  double v16; // st7
  struct QReference_s *v17; // eax
  struct QReference_s *ptBlood2QTaskRef; // eax
  struct QTask_s *v19; // edi
  struct QReference_s *v20; // eax
  struct Game_s *v21; // esi
  unsigned int v22; // ecx
  unsigned int v23; // ebx
  unsigned int v24; // edx
  signed int v25; // edx
  signed int v26; // ebx
  int v27; // eax
  unsigned int v28; // edx
  int v29; // ecx
  unsigned int v30; // edx
  float v31; // edx
  float v32; // eax
  long double v33; // st7
  long double v35; // st6
  unsigned __int8 v36; // c2
  unsigned __int8 v37; // c3
  long double v38; // st5
  unsigned int v39; // ecx
  unsigned int v40; // eax
  unsigned int v41; // ebx
  unsigned int v42; // edx
  int v43; // eax
  int v44; // ebx
  double v45; // st7
  unsigned int v46; // edx
  signed int v47; // edx
  signed int v48; // ebx
  int v49; // eax
  unsigned int v50; // edx
  int v51; // ecx
  unsigned int v52; // edx

  if ( Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.isBlood )
  {
    vY = ptDirection->vY;
    vZ = ptDirection->vZ;
    igi2_frame.ptDir.vX = ptDirection->vX;
    igi2_frame.ptDir.vY = vY;
    igi2_frame.ptDir.vZ = vZ;
    if ( igi2_frame.ptDir.vX != 0.0 || igi2_frame.ptDir.vY != 0.0 || igi2_frame.ptDir.vZ != 0.0 )
    {
      v6 = sqrt(igi2_frame.ptDir.vX * igi2_frame.ptDir.vX + igi2_frame.ptDir.vY * igi2_frame.ptDir.vY + igi2_frame.ptDir.vZ * igi2_frame.ptDir.vZ);
      igi2_frame.ptDir.vX = igi2_frame.ptDir.vX * (1.0 / v6);
      igi2_frame.ptDir.vY = igi2_frame.ptDir.vY * (1.0 / v6);
      igi2_frame.ptDir.vZ = igi2_frame.ptDir.vZ * (1.0 / v6);
    }
    qmemcpy(&igi2_frame.ptIntersection, ptPos, 0x18u);
    igi2_frame.ptEnd.vX = igi2_frame.ptDir.vX * 12288.0;
    v7 = ptIgnoreQTask;
    igi2_frame.ptEnd.vX = *(double *)&igi2_frame.ptIntersection.ptHitObj + igi2_frame.ptEnd.vX;
    igi2_frame.ptEnd.vY = igi2_frame.ptIntersection.tPos.vX + igi2_frame.ptDir.vY * 12288.0;
    HIDWORD(igi2_frame.ptIntersection.tPos.vZ) = ptIgnoreQTask;
    igi2_frame.ptEnd.vZ = igi2_frame.ptIntersection.tPos.vY + igi2_frame.ptDir.vZ * 12288.0;
    World_TraceLines(
      Game_ptGame->ptWorld,
      (struct QIntersection_s *)&igi2_frame.ptIntersection.tLocalPos,
      (struct real64x3_t *)&igi2_frame.ptIntersection,
      &igi2_frame.ptEnd,
      1,
      GameFunctions_eObjectCollisionEvaluateQTaskEvent,
      (struct CollisionEvaluateContext_s *)&igi2_frame.ptIntersection.tPos.vZ,
      0x20000000u);
    if ( igi2_frame.v63 )
    {
      if ( LODWORD(igi2_frame.ptIntersection.vLight) )
      {
        if ( !*((_DWORD *)&igi2_frame.ptIntersection.vLight + 1) )
        {
          v8 = *(_DWORD *)(LODWORD(igi2_frame.ptIntersection.vLight) + 1016);
          if ( v8 )
          {
            if ( *(_DWORD *)(v8 + 88) )
            {
              p_tRunRandomState = &Game_ptGame->tRunRandomState;
              v10 = (Random_GetRandomNumberReal32(&Game_ptGame->tRunRandomState) + 1.0) * 614.4000244140625;
              RandomNumberBelowLimit = Random_GetRandomNumberBelowLimit(p_tRunRandomState, 2);
              if ( RandomNumberBelowLimit )
              {
                if ( RandomNumberBelowLimit == 1 )
                  LODWORD(vX) = &HumanDamage_ptBloodStain2->tTexInfo;
                else
                  vX = igi2_frame.ptvRGB.vX;
              }
              else
              {
                LODWORD(vX) = &HumanDamage_ptBloodStain1->tTexInfo;
              }
              *(float *)&igi2_frame.ptQSprite.nQAnimframes = vX;
              igi2_frame.v60 = v10;
              igi2_frame.ptQSprite.ptQTilemap = (struct QTilemap_s *)&igi2_frame.ptIntersection.tLocalPos;
              igi2_frame.ptQSprite.nTextures = 0;
              pfHandler = (void (__cdecl *)(_DWORD, struct QTilemap_s **))QTask_aatQTaskFinalEvent[BulletHole_eCreateBulletHoleTaskEvent][*(unsigned __int16 *)(LODWORD(igi2_frame.ptIntersection.tLocalPos.vX) + 36)].pfHandler;
              if ( pfHandler )
                pfHandler(LODWORD(igi2_frame.ptIntersection.tLocalPos.vX), &igi2_frame.ptQSprite.ptQTilemap);
              v7 = ptIgnoreQTask;
            }
          }
        }
      }
    }
    ptBlood1QTaskRef = ptHumanDamage->ptBlood1QTaskRef;
    pxObject = nullptr;
    memset(&igi2_frame.ptQSprite, 0, 12);
    igi2_frame.ptvRGB.vZ = 127.0;
    igi2_frame.v57 = 127.0;
    igi2_frame.v58 = 127.0;
    igi2_frame.ptvRGB.vX = 1228.800048828125;
    igi2_frame.ptvRGB.vY = 1228.800048828125;
    if ( ptBlood1QTaskRef )
      pxObject = (struct QTask_s *)ptBlood1QTaskRef->pxObject;
    if ( QTask_IsQTaskTypeDerived(v7->eQTaskType, Human_eQTaskType) )
    {
      v16 = *(float *)&v7[49].ptParent * 128.0;
      if ( v16 >= 128.0 )
        igi2_frame.ptvRGB.vZ = 128.0;
      else
        igi2_frame.ptvRGB.vZ = v16;
      if ( v16 >= 128.0 )
        igi2_frame.v57 = 128.0;
      else
        igi2_frame.v57 = v16;
      if ( v16 >= 128.0 )
        igi2_frame.v58 = 128.0;
      else
        igi2_frame.v58 = v16;
    }
    if ( !pxObject )
    {
      pxObject = Particle2DDynCubeObj_New(
                   Level_ptDynamicQTask,
                   Game_ptGame->ptWorld,
                   &HumanDamage_ptBloodSquirt1->tQSprite,
                   (struct real32x3_t *)&igi2_frame.ptQSprite,
                   (struct real32x3_t *)&igi2_frame.ptvRGB.vZ,
                   (struct real32x2_t *)&igi2_frame.ptvRGB,
                   409600.0,
                   (int)&MTP_atLODVirModel[48].atBoneVertexRefs[1].atVertexRefs[668],
                   15 / HumanDamage_ptBloodSquirt1->tQSprite.ptQTilemap->nWidth,
                   0.0,
                   0.0,
                   2,
                   nullptr);
      v17 = ptHumanDamage->ptBlood1QTaskRef;
      if ( v17 )
        QReference_Delete(v17, &QTask_tQTaskRefPool);
      ptHumanDamage->ptBlood1QTaskRef = QTask_NewQTaskRef(pxObject);
    }
    qmemcpy(&igi2_frame.ptIntersection, ptPos, 0x18u);
    memset(&igi2_frame.ptQSprite.ptQTilemap, 0, 12);
    Particle2DDynCubeObj_AddParticle(
      pxObject,
      (struct real64x3_t *)&igi2_frame.ptIntersection,
      (struct real32x3_t *)&igi2_frame.ptQSprite.ptQTilemap,
      1.0,
      0.0,
      0.0,
      1.0,
      15,
      0);
    ptBlood2QTaskRef = ptHumanDamage->ptBlood2QTaskRef;
    igi2_frame.ptQSprite.ptPalInfo = nullptr;
    igi2_frame.ptQSprite.atTexInfo = nullptr;
    igi2_frame.ptQSprite.atQAnimframe = (struct QAnimframe_s *)-1049764075;
    igi2_frame.ptvRGB.vX = 143.36000061035156;
    igi2_frame.ptvRGB.vY = 143.36000061035156;
    if ( !ptBlood2QTaskRef || (v19 = (struct QTask_s *)ptBlood2QTaskRef->pxObject) == nullptr )
    {
      v19 = Particle2DDynCubeObj_New(
              Level_ptDynamicQTask,
              Game_ptGame->ptWorld,
              &HumanDamage_ptBloodSquirt2->tQSprite,
              (struct real32x3_t *)&igi2_frame.ptQSprite,
              (struct real32x3_t *)&igi2_frame.ptvRGB.vZ,
              (struct real32x2_t *)&igi2_frame.ptvRGB,
              409600.0,
              0x80000,
              0,
              0.0,
              0.0,
              20,
              HumanDamage_BloodParticle2DCollisionCallback);
      v20 = ptHumanDamage->ptBlood2QTaskRef;
      if ( v20 )
        QReference_Delete(v20, &QTask_tQTaskRefPool);
      ptHumanDamage->ptBlood2QTaskRef = QTask_NewQTaskRef(v19);
    }
    v21 = Game_ptGame;
    v22 = (Game_ptGame->tRunRandomState.anRandom[0] >> 7) ^ Game_ptGame->tRunRandomState.anRandom[2];
    v23 = v22 ^ Game_ptGame->tRunRandomState.anRandom[1];
    v24 = v23 + Game_ptGame->tRunRandomState.anRandom[0];
    Game_ptGame->tRunRandomState.anRandom[0] = v24;
    v21->tRunRandomState.anRandom[2] = v22;
    v21->tRunRandomState.anRandom[1] = v23;
    v25 = v24 % 3 + 12;
    if ( v25 > 0 )
    {
      v26 = v25;
      do
      {
        v27 = (v21->tRunRandomState.anRandom[0] >> 7) ^ v21->tRunRandomState.anRandom[2];
        v28 = v21->tRunRandomState.anRandom[0];
        v29 = v27 ^ v21->tRunRandomState.anRandom[1];
        v21->tRunRandomState.anRandom[2] = v27;
        v30 = v29 + v28;
        LODWORD(igi2_frame.ptvRGB.vX) = (unsigned __int16)v30;
        v21->tRunRandomState.anRandom[1] = v29;
        v21->tRunRandomState.anRandom[0] = v30;
        igi2_frame.vIntensity = ((double)(unsigned __int16)v30 * 0.0000152587890625
                    - 0.5
                    + (double)(unsigned __int16)v30 * 0.0000152587890625
                    - 0.5)
                   * 0.05235987901687622
                   + 0.012799081392586231;
        Particle2DDynCubeObj_AddConeParticle(
          v19,
          ptPos,
          &igi2_frame.ptDir,
          0.7853981852531433,
          379.0,
          606.0,
          1.0,
          igi2_frame.vIntensity,
          0.0,
          1.0,
          30,
          22);
        --v26;
      }
      while ( v26 );
    }
    v31 = ptDirection->vY;
    v32 = ptDirection->vZ;
    igi2_frame.ptDir.vX = ptDirection->vX;
    v33 = igi2_frame.ptDir.vX;
    igi2_frame.ptDir.vZ = v32;
    igi2_frame.ptDir.vY = v31;
    v35 = v31;
    if ( !(v37 | v36) || v35 != 0.0 || igi2_frame.ptDir.vZ != 0.0 )
    {
      v38 = 1.0 / sqrt(v33 * v33 + v35 * v35 + igi2_frame.ptDir.vZ * igi2_frame.ptDir.vZ);
      v33 = igi2_frame.ptDir.vX * v38;
      v35 = v35 * v38;
      igi2_frame.ptDir.vZ = igi2_frame.ptDir.vZ * v38;
    }
    v39 = v21->tRunRandomState.anRandom[0];
    v40 = v21->tRunRandomState.anRandom[2];
    v41 = v21->tRunRandomState.anRandom[1];
    igi2_frame.ptDir.vX = -v33;
    v42 = v21->tRunRandomState.anRandom[0];
    v43 = (v39 >> 7) ^ v40;
    igi2_frame.ptDir.vY = -v35;
    v44 = v43 ^ v41;
    v45 = igi2_frame.ptDir.vZ;
    v21->tRunRandomState.anRandom[2] = v43;
    igi2_frame.ptDir.vZ = -v45;
    v46 = v44 + v42;
    v21->tRunRandomState.anRandom[0] = v46;
    v21->tRunRandomState.anRandom[1] = v44;
    v47 = v46 % 3 + 16;
    if ( v47 > 0 )
    {
      v48 = v47;
      do
      {
        v49 = (v21->tRunRandomState.anRandom[0] >> 7) ^ v21->tRunRandomState.anRandom[2];
        v50 = v21->tRunRandomState.anRandom[0];
        v51 = v49 ^ v21->tRunRandomState.anRandom[1];
        v21->tRunRandomState.anRandom[2] = v49;
        v52 = v51 + v50;
        LODWORD(igi2_frame.ptvRGB.vX) = (unsigned __int16)v52;
        v21->tRunRandomState.anRandom[1] = v51;
        v21->tRunRandomState.anRandom[0] = v52;
        igi2_frame.vIntensitya = ((double)(unsigned __int16)v52 * 0.0000152587890625
                     - 0.5
                     + (double)(unsigned __int16)v52 * 0.0000152587890625
                     - 0.5)
                    * 0.05235987901687622
                    + 0.012799081392586231;
        Particle2DDynCubeObj_AddConeParticle(
          v19,
          ptPos,
          &igi2_frame.ptDir,
          3.1415927410125732,
          37.0,
          113.0,
          1.0,
          igi2_frame.vIntensitya,
          0.0,
          1.0,
          30,
          22);
        --v48;
      }
      while ( v48 );
    }
  }
}

// source: j/0/human/humandamage.c:608  [anchor-hash]
void __cdecl HumanDamage_Open()
{
  HumanDamage_ptBloodStain1 = GameFunctions_RegisterGameTexture("hole_blood1.tex");
  HumanDamage_ptBloodStain2 = GameFunctions_RegisterGameTexture("hole_blood2.tex");
  HumanDamage_ptBloodStain3 = GameFunctions_RegisterGameTexture("hole_blood3.tex");
  HumanDamage_ptBloodStain4 = GameFunctions_RegisterGameTexture("hole_blood4.tex");
  HumanDamage_ptBloodSquirt1 = GameFunctions_RegisterGameSprite("blood1.spr");
  HumanDamage_ptBloodSquirt2 = GameFunctions_RegisterGameSprite("blood2.spr");
}

// source: j/0/human/humandamage.c:622  [size]
void __cdecl HumanDamage_Close()
{
  ;
}
