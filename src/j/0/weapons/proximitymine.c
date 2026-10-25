/* j/0/weapons/proximitymine.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/weapons/proximitymine.c:64  [size]
void __cdecl ProximityMine_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[1].ptNext = (struct QTask_s *)-1;
  ptQTask[1].ptPrev = (struct QTask_s *)1;
  ptQTask[1].tQTaskChildren.ptHead = (struct QTask_s *)1065353216;
  ptQTask[1].tQTaskChildren.ptMiddle = (struct QTask_s *)0x40000000;
  ptQTask[1].tQTaskChildren.ptTail = (struct QTask_s *)1056964608;
  ptQTask[1].tQTaskRefList.ptHead = (struct QReference_s *)1069547520;
  ptQTask[1].tQTaskRefList.ptMiddle = (struct QReference_s *)1077936128;
  LOBYTE(ptQTask[1].tQTaskRefList.ptTail) = 0;
  LOBYTE(ptQTask[2].tQTaskRefList.ptHead) = 0;
  LOBYTE(ptQTask[3].tQTaskChildren.ptMiddle) = 0;
}

// source: j/0/weapons/proximitymine.c:89  [size]
void __cdecl ProximityMine_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = ProximityMine_ptParameterList;
}

// source: j/0/weapons/proximitymine.c:107  [size]
void __cdecl ProximityMine_CreateWeaponTypeParametersHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *((_DWORD *)pxContext + 2) = QTask_NewFn(*((struct QTask_s **)pxContext + 1), ProximityMine_eQTaskType, nullptr);
}

// source: j/0/weapons/proximitymine.c:126  [size]
void __cdecl ProximityMine_GetAnimHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // ecx
  int v3; // eax
  int v4; // edi
  struct QHashTable_s *v5; // esi
  unsigned int v6; // eax
  int v7; // eax
  int v8; // esi
  int v9; // eax

  v2 = *((_DWORD *)pxContext + 3);
  v3 = *((_DWORD *)pxContext + 5);
  if ( v2 == 4 )
  {
    v4 = v3 + 68;
    v5 = Hierarchy_ptHashTable;
    v6 = Hierarchy_ptHashTable->tPrivate.pfHashFunction(
           Hierarchy_ptHashTable->tPrivate.nHashTableSize,
           *(void **)pxContext);
    v7 = ((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Hierarchy_ptHashTable->tPrivate.pfFindElement)(v5, v6, (const void *)(*(void **)pxContext));
    v8 = *(_DWORD *)v7;
    v9 = (*(int (__cdecl **)(_DWORD, int))(*(_DWORD *)v7 + 12))(*(_DWORD *)(*(_DWORD *)v7 + 4), v4);
    *((_DWORD *)pxContext + 6) = (*(int (__cdecl **)(int, int, const void *))(v8 + 28))(v8, v9, (const void *)(v4));
  }
  else if ( v2 == 17 )
  {
    *((_DWORD *)pxContext + 6) = Hierarchy_GetAnim(*(unsigned __int8 **)pxContext, (char *)(v3 + 100));
  }
}

// source: j/0/weapons/proximitymine.c:163  [anchor-mhash]
void __cdecl RemoteMine_GetAnimHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // eax
  int v3; // ecx

  if ( Game_eGameMode )
  {
    *((_DWORD *)pxContext + 6) = 0;
  }
  else
  {
    v2 = *((_DWORD *)pxContext + 3);
    v3 = *((_DWORD *)pxContext + 5);
    if ( v2 == 4 )
    {
      *((_DWORD *)pxContext + 6) = Hierarchy_GetAnim(*(unsigned __int8 **)pxContext, (char *)(v3 + 68));
    }
    else if ( v2 == 17 )
    {
      *((_DWORD *)pxContext + 6) = Hierarchy_GetAnim(*(unsigned __int8 **)pxContext, (char *)(v3 + 100));
    }
  }
}

// source: j/0/weapons/proximitymine.c:208  [size]
void __cdecl ProximityMine_GetAmmoInfoHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // eax

  v2 = *(_DWORD *)pxContext;
  *((_DWORD *)pxContext + 2) = 1;
  *((_DWORD *)pxContext + 3) = 1;
  *((_DWORD *)pxContext + 4) = 1;
  *((_DWORD *)pxContext + 1) = AmmoType_GetAmmoTypeFromID(*(_DWORD *)(v2 + 40));
}

// source: j/0/weapons/proximitymine.c:233  [size]
void __cdecl ProximityMine_StatusDisplayHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zText[16]; };
    struct { char igi2_o1[16]; struct WeaponTypeGetFireTypeScreenPositionContext_s tPositionContext; };
    char igi2_extent[44];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // ebp
  struct AmmoType_s *AmmoTypeFromID; // eax
  struct AmmoTypeItem_s *AmmoTypeItemFromAmmoType; // eax
  float *v5; // edi
  float v6; // eax
  int v7; // ecx
  int v8; // esi
  __int16 *v9; // eax
  int v10; // eax
  void *pxContexta = *(void * *)&pxContext; // [esp+4Ch] [ebp+8h] ARGSLOT

  v2 = **((_DWORD **)pxContext + 1);
  AmmoTypeFromID = AmmoType_GetAmmoTypeFromID(*(_DWORD *)(*((_DWORD *)pxContext + 6) + 40));
  AmmoTypeItemFromAmmoType = Weapon_GetAmmoTypeItemFromAmmoType(
                               *(struct QTask_s **)pxContext,
                               AmmoTypeFromID->zAmmoTypeScriptID);
  sprintf(igi2_frame.zText, "%4d", AmmoTypeItemFromAmmoType->nAmmoCount);
  Text_SetString(*(struct StaticTilemap_s **)(v2 + 1136), igi2_frame.zText);
  v5 = *(float **)(v2 + 1136);
  v6 = *v5;
  igi2_frame.tPositionContext.tIn.nFireType = *((_DWORD *)pxContext + 2);
  v7 = *(__int16 *)(LODWORD(v6) + 6);
  v8 = 0;
  pxContexta = nullptr;
  if ( v7 > 0 )
  {
    v9 = *(__int16 **)(LODWORD(v6) + 12);
    do
    {
      if ( *v9 > v8 )
        v8 = *v9;
      ++v9;
      --v7;
    }
    while ( v7 );
    pxContexta = (void *)v8;
  }
  igi2_frame.tPositionContext.tIn.vTextWidth = (float)(int)pxContexta;
  WeaponType_GetFireTypeScreenPosition(&igi2_frame.tPositionContext);
  v5[1] = (float)(__int64)igi2_frame.tPositionContext.tOut.vTextXPos;
  *(float *)(*(_DWORD *)(v2 + 1136) + 8) = (float)(__int64)igi2_frame.tPositionContext.tOut.vTextYPos;
  v10 = *(_DWORD *)(v2 + 1136);
  QTilemap_Register(
    *(struct QTilemap_s **)v10,
    *(float *)(v10 + 4),
    *(float *)(v10 + 8),
    *(float *)(v10 + 20),
    *(float *)(v10 + 24),
    *(float *)(v10 + 28),
    *(float *)(v10 + 16),
    *(float *)(v10 + 12),
    *(_DWORD *)(v10 + 36) | 0x40000000,
    *(_DWORD *)(v10 + 32));
}

// source: j/0/weapons/proximitymine.c:289  [anchor-mhash]
void __cdecl ProximityMine_WeaponFireHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v21; };
    struct { char igi2_o1[4]; float vExplodeRadius; };
    struct { char igi2_o2[24]; float v23; };
    struct { char igi2_o3[28]; struct ProximityMine_t *ptProximityMineParameters; };
    struct { char igi2_o4[28]; __int64 ptProximityMineParametersa; };
    struct { char igi2_o5[40]; struct WeaponCollisionEvaluateContext_t tWeaponCollisionEvaluateContext; };
    struct { char igi2_o6[60]; struct real64x3_t tPos0; };
    struct { char igi2_o7[84]; struct real64x3_t tPos1; };
    struct { char igi2_o8[108]; struct QIntersection_s tIntersection; };
    struct { char igi2_o9[228]; struct real32x9_t tOrientation; };
    char igi2_extent[268];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  _DWORD *v2; // ebx
  struct ProximityMine_t *v3; // eax
  double v4; // st7
  double v5; // st6
  double v6; // st5
  struct QTask_s *v7; // eax
  double v8; // st7
  double v9; // st6
  int v10; // esi
  struct QObj_s *ptHitObj; // edx
  unsigned __int16 v12; // cx
  BOOL v13; // edi
  struct QTask_s *ptParent; // eax
  unsigned __int16 eQTaskType; // ax
  BOOL v16; // eax
  long double v17; // st7
  struct ProximityMine_t *v18; // esi
  float vDetectionRadius; // eax
  int v20; // eax

  v2 = pxContext;
  v3 = *((struct ProximityMine_t **)pxContext + 25);
  v4 = *((float *)pxContext + 11);
  v5 = *((float *)pxContext + 14);
  igi2_frame.tWeaponCollisionEvaluateContext.ptIgnore1QTask = *((struct QTask_s **)pxContext + 17);
  v6 = v3->vEffectiveRange * 4096.0;
  igi2_frame.ptProximityMineParameters = v3;
  igi2_frame.v23 = v6;
  v7 = *((struct QTask_s **)pxContext + 1);
  *(float *)&igi2_frame.tWeaponCollisionEvaluateContext.tCollisionEvaluateContext.isEvaluate = v6 * v4;
  qmemcpy(&igi2_frame.tPos0, (char *)pxContext + 16, sizeof(igi2_frame.tPos0));
  v8 = igi2_frame.v23 * v5;
  v9 = igi2_frame.v23 * *(float *)&igi2_frame.tWeaponCollisionEvaluateContext.ptIgnore1QTask;
  igi2_frame.tWeaponCollisionEvaluateContext.tCollisionEvaluateContext.ptQTask = v7;
  igi2_frame.tWeaponCollisionEvaluateContext.ptIgnore1QTask = v7;
  igi2_frame.tPos1.vX = *(float *)&igi2_frame.tWeaponCollisionEvaluateContext.tCollisionEvaluateContext.isEvaluate + igi2_frame.tPos0.vX;
  igi2_frame.tPos1.vY = v8 + igi2_frame.tPos0.vY;
  v10 = 0;
  igi2_frame.tPos1.vZ = v9 + igi2_frame.tPos0.vZ;
  igi2_frame.tWeaponCollisionEvaluateContext.ptIgnore2QTask = nullptr;
  igi2_frame.tWeaponCollisionEvaluateContext.vHitProbability = 1.0;
  World_TraceLines(
    Game_ptGame->ptWorld,
    &igi2_frame.tIntersection,
    &igi2_frame.tPos0,
    &igi2_frame.tPos1,
    1,
    GameFunctions_eWeaponCollisionEvaluateQTaskEvent,
    &igi2_frame.tWeaponCollisionEvaluateContext.tCollisionEvaluateContext,
    0xFFFFFFFF);
  if ( igi2_frame.tIntersection.isHit )
  {
    ptHitObj = igi2_frame.tIntersection.ptHitObj;
    v12 = Human_eQTaskType;
    v13 = igi2_frame.tIntersection.ptHitObj
       && QTask_IsQTaskTypeDerived(igi2_frame.tIntersection.ptHitObj->tQTask.eQTaskType, Human_eQTaskType);
    if ( ptHitObj )
    {
      ptParent = ptHitObj->tQTask.ptParent;
      if ( ptParent )
      {
        if ( QTask_IsQTaskTypeDerived(ptParent->eQTaskType, v12) )
          v10 = 1;
      }
    }
    v16 = false;
    if ( ptHitObj )
    {
      eQTaskType = ptHitObj->tQTask.eQTaskType;
      if ( eQTaskType == Glass_eQTaskType
        || eQTaskType == Door_eQTaskType
        || QTask_IsQTaskTypeDerived(eQTaskType, Vehicle_eQTaskType) )
      {
        v16 = true;
      }
    }
    if ( !v13 && !v10 && !v16 )
    {
      if ( igi2_frame.tIntersection.tNormal.vX != 0.0 || igi2_frame.tIntersection.tNormal.vY != 0.0 || igi2_frame.tIntersection.tNormal.vZ != 0.0 )
      {
        v17 = 1.0
            / sqrt(
                igi2_frame.tIntersection.tNormal.vX * igi2_frame.tIntersection.tNormal.vX
              + igi2_frame.tIntersection.tNormal.vY * igi2_frame.tIntersection.tNormal.vY
              + igi2_frame.tIntersection.tNormal.vZ * igi2_frame.tIntersection.tNormal.vZ);
        igi2_frame.tIntersection.tNormal.vX = igi2_frame.tIntersection.tNormal.vX * v17;
        igi2_frame.tIntersection.tNormal.vY = igi2_frame.tIntersection.tNormal.vY * v17;
        igi2_frame.tIntersection.tNormal.vZ = igi2_frame.tIntersection.tNormal.vZ * v17;
      }
      GameFunctions_CreateOrientationFromDirection(&igi2_frame.tOrientation, &igi2_frame.tIntersection.tNormal);
      v18 = igi2_frame.ptProximityMineParameters;
      vDetectionRadius = igi2_frame.ptProximityMineParameters->vDetectionRadius;
      igi2_frame.vExplodeRadius = igi2_frame.ptProximityMineParameters->vExplodeRadius;
      igi2_frame.ptProximityMineParametersa = (__int64)(igi2_frame.ptProximityMineParameters->vTimeBeforeArm * 30.0);
      igi2_frame.v21 = vDetectionRadius;
      v20 = *((_DWORD *)pxContext + 26);
      Mine_iGameItemID = *((unsigned __int8 *)pxContext + 96);
      Mine_New(
        Level_ptDynamicQTask,
        &igi2_frame.tIntersection.tPos,
        &igi2_frame.tOrientation,
        (char *)(v20 + 676),
        igi2_frame.ptProximityMineParametersa,
        v18->vTimeBeforeExplode,
        igi2_frame.v21,
        igi2_frame.vExplodeRadius,
        false);
      *((_DWORD *)pxContext + 28) = 1;
      *((_DWORD *)pxContext + 29) = (__int64)(60.0 / (double)v18->nRoundsPerMinute * 30.0);
      Weapon_PlaySound(*(struct QTask_s **)pxContext, 0, v18->zFireSound, false);
      v2 = pxContext;
    }
  }
  v2[32] = 1008981770;
  v2[33] = 1008981770;
  v2[30] = 1036831949;
}

// source: j/0/weapons/proximitymine.c:403  [size]
void __cdecl RemoteMine_CreateWeaponTypeParametersHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *((_DWORD *)pxContext + 2) = QTask_NewFn(*((struct QTask_s **)pxContext + 1), RemoteMine_eQTaskType, nullptr);
}

// source: j/0/weapons/proximitymine.c:422  [anchor-mhash]
void __cdecl RemoteMine_WeaponFireHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v17; };
    struct { char igi2_o1[4]; struct ProximityMine_t *ptProximityMineParameters; };
    struct { char igi2_o2[16]; struct WeaponCollisionEvaluateContext_t tWeaponCollisionEvaluateContext; };
    struct { char igi2_o3[36]; struct real64x3_t tPos0; };
    struct { char igi2_o4[60]; struct real64x3_t tPos1; };
    struct { char igi2_o5[84]; struct QIntersection_s tIntersection; };
    struct { char igi2_o6[204]; struct real32x9_t tOrientation; };
    char igi2_extent[244];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct ProximityMine_t *v2; // eax
  double v3; // st7
  double v4; // st6
  double v5; // st5
  struct QTask_s *v6; // eax
  double v7; // st7
  double v8; // st6
  struct QObj_s *ptHitObj; // edx
  unsigned __int16 v10; // cx
  BOOL v11; // edi
  struct QTask_s *ptParent; // eax
  BOOL v13; // esi
  unsigned __int16 eQTaskType; // ax
  BOOL v15; // eax
  long double v16; // st7

  if ( Game_eGameMode == GAME_GAMEMODE_SINGLEPLAYER )
  {
    v2 = *((struct ProximityMine_t **)pxContext + 25);
    v3 = *((float *)pxContext + 11);
    v4 = *((float *)pxContext + 14);
    igi2_frame.tWeaponCollisionEvaluateContext.ptIgnore1QTask = *((struct QTask_s **)pxContext + 17);
    v5 = v2->vEffectiveRange * 4096.0;
    igi2_frame.ptProximityMineParameters = v2;
    v6 = *((struct QTask_s **)pxContext + 1);
    igi2_frame.v17 = v5;
    qmemcpy(&igi2_frame.tPos0, (char *)pxContext + 16, sizeof(igi2_frame.tPos0));
    *(float *)&igi2_frame.tWeaponCollisionEvaluateContext.tCollisionEvaluateContext.isEvaluate = v5 * v3;
    v7 = igi2_frame.v17 * v4;
    v8 = igi2_frame.v17 * *(float *)&igi2_frame.tWeaponCollisionEvaluateContext.ptIgnore1QTask;
    igi2_frame.tWeaponCollisionEvaluateContext.tCollisionEvaluateContext.ptQTask = v6;
    igi2_frame.tWeaponCollisionEvaluateContext.ptIgnore1QTask = v6;
    igi2_frame.tPos1.vX = *(float *)&igi2_frame.tWeaponCollisionEvaluateContext.tCollisionEvaluateContext.isEvaluate + igi2_frame.tPos0.vX;
    igi2_frame.tPos1.vY = v7 + igi2_frame.tPos0.vY;
    igi2_frame.tWeaponCollisionEvaluateContext.ptIgnore2QTask = nullptr;
    igi2_frame.tWeaponCollisionEvaluateContext.vHitProbability = 1.0;
    igi2_frame.tPos1.vZ = v8 + igi2_frame.tPos0.vZ;
    World_TraceLines(
      Game_ptGame->ptWorld,
      &igi2_frame.tIntersection,
      &igi2_frame.tPos0,
      &igi2_frame.tPos1,
      1,
      GameFunctions_eWeaponCollisionEvaluateQTaskEvent,
      &igi2_frame.tWeaponCollisionEvaluateContext.tCollisionEvaluateContext,
      0xFFFFFFFF);
    if ( igi2_frame.tIntersection.isHit )
    {
      ptHitObj = igi2_frame.tIntersection.ptHitObj;
      v10 = Human_eQTaskType;
      v11 = igi2_frame.tIntersection.ptHitObj
         && QTask_IsQTaskTypeDerived(igi2_frame.tIntersection.ptHitObj->tQTask.eQTaskType, Human_eQTaskType);
      v13 = false;
      if ( ptHitObj )
      {
        ptParent = ptHitObj->tQTask.ptParent;
        if ( ptParent )
        {
          if ( QTask_IsQTaskTypeDerived(ptParent->eQTaskType, v10) )
            v13 = true;
        }
      }
      v15 = false;
      if ( ptHitObj )
      {
        eQTaskType = ptHitObj->tQTask.eQTaskType;
        if ( eQTaskType == Glass_eQTaskType
          || eQTaskType == Door_eQTaskType
          || QTask_IsQTaskTypeDerived(eQTaskType, Vehicle_eQTaskType) )
        {
          v15 = true;
        }
      }
      if ( !v11 && !v13 && !v15 )
      {
        if ( igi2_frame.tIntersection.tNormal.vX != 0.0 || igi2_frame.tIntersection.tNormal.vY != 0.0 || igi2_frame.tIntersection.tNormal.vZ != 0.0 )
        {
          v16 = 1.0
              / sqrt(
                  igi2_frame.tIntersection.tNormal.vX * igi2_frame.tIntersection.tNormal.vX
                + igi2_frame.tIntersection.tNormal.vY * igi2_frame.tIntersection.tNormal.vY
                + igi2_frame.tIntersection.tNormal.vZ * igi2_frame.tIntersection.tNormal.vZ);
          igi2_frame.tIntersection.tNormal.vX = igi2_frame.tIntersection.tNormal.vX * v16;
          igi2_frame.tIntersection.tNormal.vY = igi2_frame.tIntersection.tNormal.vY * v16;
          igi2_frame.tIntersection.tNormal.vZ = igi2_frame.tIntersection.tNormal.vZ * v16;
        }
        GameFunctions_CreateOrientationFromDirection(&igi2_frame.tOrientation, &igi2_frame.tIntersection.tNormal);
        Mine_New(
          Level_ptDynamicQTask,
          &igi2_frame.tIntersection.tPos,
          &igi2_frame.tOrientation,
          (char *)(*((_DWORD *)pxContext + 26) + 676),
          (__int64)(igi2_frame.ptProximityMineParameters->vTimeBeforeArm * 30.0),
          igi2_frame.ptProximityMineParameters->vTimeBeforeExplode,
          igi2_frame.ptProximityMineParameters->vDetectionRadius,
          igi2_frame.ptProximityMineParameters->vExplodeRadius,
          true);
        *((_DWORD *)pxContext + 28) = 1;
        *((_DWORD *)pxContext + 29) = (__int64)(60.0 / (double)igi2_frame.ptProximityMineParameters->nRoundsPerMinute * 30.0);
      }
    }
  }
  *((_DWORD *)pxContext + 32) = 1008981770;
  *((_DWORD *)pxContext + 33) = 1008981770;
  *((_DWORD *)pxContext + 30) = 1036831949;
}

// source: j/0/weapons/proximitymine.c:539  [anchor-hash]
void __cdecl ProximityMine_Open()
{
  unsigned __int16 v0; // ax
  __int16 v1; // bx
  unsigned __int16 v2; // si
  unsigned __int16 v3; // di
  __int16 v4; // bx
  __int16 v5; // bp
  struct ParameterList_s *v6; // eax
  int v7; // edx

  ProximityMine_eQTaskType = QTask_NewQTaskType("ProximityMine", 164, FireType_eQTaskType, 0, 0);
  v0 = QTask_NewQTaskType("RemoteMine", 164, ProximityMine_eQTaskType, 0, 0);
  v1 = Level_eAllowSaveQTaskEvent;
  v2 = ProximityMine_eQTaskType;
  v3 = v0;
  RemoteMine_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    ProximityMine_eQTaskType,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v3, v1, (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v2, 0, (void (__cdecl *)(struct QTask_s *, void *))ProximityMine_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v2,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))ProximityMine_GetParameterListHandler);
  v4 = WeaponType_eCreateParametersQTaskEvent;
  QTask_LinkQTaskEventHandlerFn(
    v2,
    WeaponType_eCreateParametersQTaskEvent,
    ProximityMine_CreateWeaponTypeParametersHandler);
  QTask_LinkQTaskEventHandlerFn(v2, WeaponType_eGetAmmoInfoQTaskEvent, ProximityMine_GetAmmoInfoHandler);
  v5 = WeaponType_eGetAnimQTaskEvent;
  QTask_LinkQTaskEventHandlerFn(v2, WeaponType_eGetAnimQTaskEvent, ProximityMine_GetAnimHandler);
  QTask_LinkQTaskEventHandlerFn(v2, StatusScreen_eStatusDisplayQTaskEvent, ProximityMine_StatusDisplayHandler);
  QTask_LinkQTaskEventHandlerFn(v2, Weapon_eFireQTaskEvent, ProximityMine_WeaponFireHandler);
  QTask_LinkQTaskEventHandlerFn(v3, v4, RemoteMine_CreateWeaponTypeParametersHandler);
  QTask_LinkQTaskEventHandlerFn(v3, Weapon_eFireQTaskEvent, RemoteMine_WeaponFireHandler);
  QTask_LinkQTaskEventHandlerFn(v3, v5, RemoteMine_GetAnimHandler);
  v6 = (struct ParameterList_s *)Mem_AllocFn(212, 4);
  v7 = ParameterEnumList_eParameterTypeInt32;
  v6->ptParameterListItem = (struct ParameterListItem_s *)&v6[1];
  v6->nParameters = 0;
  v6->nMaxParameters = 10;
  ProximityMine_ptParameterList = v6;
  ParameterList_AddParameter(v6, 0x28u, v7, "AmmoType", 7u, &AmmoType_tEnumList);
  ParameterList_AddParameter(
    ProximityMine_ptParameterList,
    0x2Cu,
    Level_eParameterTypeInt32,
    "Rounds Per Minute",
    7u,
    nullptr);
  ParameterList_AddParameter(
    ProximityMine_ptParameterList,
    0x30u,
    Level_eParameterTypeReal32,
    "Effective Range (meters)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    ProximityMine_ptParameterList,
    0x34u,
    Level_eParameterTypeReal32,
    "Time before arming (seconds)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    ProximityMine_ptParameterList,
    0x38u,
    Level_eParameterTypeReal32,
    "Countdown time (seconds)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    ProximityMine_ptParameterList,
    0x3Cu,
    Level_eParameterTypeReal32,
    "Activate radius (meters)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    ProximityMine_ptParameterList,
    0x40u,
    Level_eParameterTypeReal32,
    "Explosion radius (meters)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    ProximityMine_ptParameterList,
    0x44u,
    Level_eParameterTypeString32,
    "1st Fire Anim",
    7u,
    nullptr);
  ParameterList_AddParameter(
    ProximityMine_ptParameterList,
    0x64u,
    Level_eParameterTypeString32,
    "3rd Fire Anim",
    7u,
    nullptr);
  ParameterList_AddParameter(
    ProximityMine_ptParameterList,
    0x84u,
    Level_eParameterTypeString32,
    "Fire Sound",
    7u,
    nullptr);
  Symbol_Register(
    "TASKTYPE_PROXIMITYMINE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)ProximityMine_eQTaskType,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "TASKTYPE_REMOTEMINE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)RemoteMine_eQTaskType,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}

// source: j/0/weapons/proximitymine.c:650  [size]
void __cdecl ProximityMine_Close()
{
  int v0; // esi

  if ( ProximityMine_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&ProximityMine_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(RemoteMine_eQTaskType);
  QTask_DeleteQTaskType(ProximityMine_eQTaskType);
}

// source: j/0/weapons/proximitymine.c:668  [anchor-strings]
struct ProximityMine_t *__cdecl ProximityMine_GetParameters()
{
  int v0; // eax

  v0 = Script_ParseLineInt32("WEAPON_ID_PROXIMITYMINE");
  return (struct ProximityMine_t *)WeaponType_GetWeaponTypeFromID(v0)->atFireTypes[0].ptParametersQTaskRef->pxObject;
}
