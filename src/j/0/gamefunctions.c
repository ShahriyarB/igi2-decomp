/* j/0/gamefunctions.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/gamefunctions.c:91  [size]
__int16 __cdecl GameFunctions_GetNotifyQTaskEvent()
{
  return GameFunctions_eNotifyQTaskEvent;
}

// source: j/0/gamefunctions.c:105  [size]
__int16 __cdecl GameFunctions_GetPickupQTaskEvent()
{
  return GameFunctions_ePickupQTaskEvent;
}

// source: j/0/gamefunctions.c:119  [size]
__int16 __cdecl GameFunctions_GetEvaluateActivateQTaskEvent()
{
  return GameFunctions_eEvaluateActivateQTaskEvent;
}

// source: j/0/gamefunctions.c:133  [size]
__int16 __cdecl GameFunctions_GetActivateQTaskEvent()
{
  return GameFunctions_eActivateQTaskEvent;
}

// source: j/0/gamefunctions.c:147  [size]
__int16 __cdecl GameFunctions_GetGetActivateQTaskEvent()
{
  return GameFunctions_eGetActivateQTaskEvent;
}

// source: j/0/gamefunctions.c:161  [size]
__int16 __cdecl GameFunctions_GetDeactivateQTaskEvent()
{
  return GameFunctions_eDeactivateQTaskEvent;
}

// source: j/0/gamefunctions.c:175  [size]
__int16 __cdecl GameFunctions_GetActivateDisplayQTaskEvent()
{
  return GameFunctions_eActivateDisplayQTaskEvent;
}

// source: j/0/gamefunctions.c:189  [size]
__int16 __cdecl GameFunctions_GetWeaponCollisionEvaluateQTaskEvent()
{
  return GameFunctions_eWeaponCollisionEvaluateQTaskEvent;
}

// source: j/0/gamefunctions.c:203  [size]
__int16 __cdecl GameFunctions_GetWeaponHitQTaskEvent()
{
  return GameFunctions_eWeaponHitQTaskEvent;
}

// source: j/0/gamefunctions.c:217  [size]
__int16 __cdecl GameFunctions_GetObjectCollisionEvaluateQTaskEvent()
{
  return GameFunctions_eObjectCollisionEvaluateQTaskEvent;
}

// source: j/0/gamefunctions.c:231  [size]
__int16 __cdecl GameFunctions_GetObjectHitQTaskEvent()
{
  return GameFunctions_eObjectHitQTaskEvent;
}

// source: j/0/gamefunctions.c:245  [size]
__int16 __cdecl GameFunctions_GetExplosionHitQTaskEvent()
{
  return GameFunctions_eExplosionHitQTaskEvent;
}

// source: j/0/gamefunctions.c:259  [size]
__int16 __cdecl GameFunctions_GetElectricDamageQTaskEvent()
{
  return GameFunctions_eElectricDamageQTaskEvent;
}

// source: j/0/gamefunctions.c:273  [size]
__int16 __cdecl GameFunctions_GetGetNextZEvaluateQTaskEvent()
{
  return GameFunctions_eGetNextZEvaluateQTaskEvent;
}

// source: j/0/gamefunctions.c:287  [size]
struct QTaskList_s *__cdecl GameFunctions_GetActivateQTaskList()
{
  return GameFunctions_ptActivateQTaskList;
}

// source: j/0/gamefunctions.c:303  [size]
struct QTaskList_s *__cdecl GameFunctions_GetNotifyQTaskList()
{
  return GameFunctions_ptNotifyQTaskList;
}

// source: j/0/gamefunctions.c:319  [size]
struct QTaskList_s *__cdecl GameFunctions_GetPickupQTaskList()
{
  return GameFunctions_ptPickupQTaskList;
}

// source: j/0/gamefunctions.c:335  [size]
struct QTaskList_s *__cdecl GameFunctions_GetExplosionQTaskList()
{
  return GameFunctions_ptExplosionQTaskList;
}

// source: j/0/gamefunctions.c:351  [size]
struct QTaskList_s *__cdecl GameFunctions_GetVehicleQTaskList()
{
  return GameFunctions_ptVehicleQTaskList;
}

// source: j/0/gamefunctions.c:367  [size]
struct QTaskList_s *__cdecl GameFunctions_GetCutsceneDeleteQTaskList()
{
  return GameFunctions_ptCutsceneDeleteQTaskList;
}

// source: j/0/gamefunctions.c:383  [anchor-callee]
float __cdecl GameFunctions_CalcAlpha(struct real64x3_t tDirection)
{
  double v1; // st7
  long double v2; // st5
  float x; // [esp+0h] [ebp-8h]

  if ( tDirection.vY == 0.0 && tDirection.vZ == 0.0 )
  {
    return 0.0;
  }
  else
  {
    v2 = 1.0 / sqrt(tDirection.vY * tDirection.vY + tDirection.vZ * tDirection.vZ);
    x = tDirection.vY * v2;
    v1 = Real32_Acos(x);
    if ( v2 * tDirection.vZ < 0.0 )
      return -v1;
  }
  return v1;
}

// source: j/0/gamefunctions.c:420  [anchor-callee]
float __cdecl GameFunctions_CalcGamma(struct real64x3_t tDirection)
{
  double v1; // st7
  long double v2; // st7
  float x; // [esp+0h] [ebp-8h]

  if ( tDirection.vX == 0.0 && tDirection.vY == 0.0 )
  {
    return 0.0;
  }
  else
  {
    v2 = 1.0 / sqrt(tDirection.vY * tDirection.vY + tDirection.vX * tDirection.vX);
    tDirection.vX = tDirection.vX * v2;
    x = v2 * tDirection.vY;
    v1 = Real32_Acos(x);
    if ( tDirection.vX > 0.0 )
      return -v1;
  }
  return v1;
}

// source: j/0/gamefunctions.c:457  [anchor-mhash]
struct QTask_s *__cdecl GameFunctions_SnapToGround(
        struct QTask_s *ptQTask,
        struct real64x3_t *ptPos)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct World_s *ptWorld; };
    struct { char igi2_o1[32]; double vDistance; };
    struct { char igi2_o2[40]; struct GetNextZEvaluateContext_t tGetNextZEvaluateContext; };
    struct { char igi2_o3[48]; struct QIntersection_s tIntersection; };
    char igi2_extent[172];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *result; // eax

  igi2_frame.tGetNextZEvaluateContext.tCollisionEvaluateContext.ptQTask = ptQTask;
  igi2_frame.ptWorld = Game_ptGame->ptWorld;
  igi2_frame.vDistance = -1638400.0;
  World_GetNextZNoMaterial(
    igi2_frame.ptWorld,
    &igi2_frame.tIntersection,
    ptPos,
    1,
    &igi2_frame.vDistance,
    GameFunctions_eGetNextZEvaluateQTaskEvent,
    &igi2_frame.tGetNextZEvaluateContext.tCollisionEvaluateContext,
    0xFFFFFFFF);
  result = (struct QTask_s *)igi2_frame.tIntersection.isHit;
  if ( igi2_frame.tIntersection.isHit
    || (igi2_frame.vDistance = 1638400.0,
        World_GetNextZNoMaterial(
          Game_ptGame->ptWorld,
          &igi2_frame.tIntersection,
          ptPos,
          1,
          &igi2_frame.vDistance,
          GameFunctions_eGetNextZEvaluateQTaskEvent,
          &igi2_frame.tGetNextZEvaluateContext.tCollisionEvaluateContext,
          0xFFFFFFFF),
        (result = (struct QTask_s *)igi2_frame.tIntersection.isHit) != nullptr) )
  {
    ptPos->vZ = igi2_frame.tIntersection.tPos.vZ;
  }
  return result;
}

// source: j/0/gamefunctions.c:512  [anchor-callee]
void __cdecl GameFunctions_CreateOrientationFromDirection(
        struct real32x9_t *ptOrientation,
        struct real32x3_t *ptDirection)
{
  double vZ; // st7
  bool v3; // zf
  double v4; // st7
  double vY; // st6
  double v6; // st7
  long double v7; // st7
  long double v8; // st4
  long double v9; // st7
  long double v10; // st4
  long double v11; // st6
  float tZ; // [esp+Ch] [ebp-24h]
  float tZ_4; // [esp+10h] [ebp-20h]
  float tZ_8; // [esp+14h] [ebp-1Ch]
  float tX; // [esp+18h] [ebp-18h]
  float tXa; // [esp+18h] [ebp-18h]
  float tX_4; // [esp+1Ch] [ebp-14h]
  float tX_4a; // [esp+1Ch] [ebp-14h]
  float tX_8; // [esp+20h] [ebp-10h]
  float tTemp_; // [esp+24h] [ebp-Ch]
  float tTemp_a; // [esp+24h] [ebp-Ch]
  float tTemp_b; // [esp+24h] [ebp-Ch]
  float tTemp__4; // [esp+28h] [ebp-8h]
  float tTemp__4a; // [esp+28h] [ebp-8h]
  float tTemp__4b; // [esp+28h] [ebp-8h]
  float tTemp__8; // [esp+2Ch] [ebp-4h]
  float tTemp__8a; // [esp+2Ch] [ebp-4h]
  float tTemp__8b; // [esp+2Ch] [ebp-4h]
  struct real32x3_t tY; // 0:^0.12

  vZ = ptDirection->vZ;
  if ( vZ < 0.0 )
    vZ = -vZ;
  v3 = vZ > 0.949999988079071;
  tY = *ptDirection;
  v4 = ptDirection->vZ * 0.0;
  vY = ptDirection->vY;
  if ( v3 )
  {
    tX = v4 - vY * 0.0;
    v6 = tY.vX * 0.0;
    tZ = tX;
    tX_4 = -(tY.vZ - v6);
    tZ_4 = tX_4;
    tX_8 = tY.vY - v6;
    tZ_8 = tX_8;
    if ( tX != 0.0 || tX_4 != 0.0 || tX_8 != 0.0 )
    {
      v7 = 1.0 / sqrt(tX_4 * tX_4 + tX_8 * tX_8 + tX * tX);
      tZ = tX * v7;
      tZ_4 = tX_4 * v7;
      tZ_8 = tX_8 * v7;
    }
    tTemp_ = tY.vY * tZ_8 - tY.vZ * tZ_4;
    tXa = tTemp_;
    tTemp__4 = -(tY.vX * tZ_8 - tY.vZ * tZ);
    tX_4a = tTemp__4;
    tTemp__8 = tY.vX * tZ_4 - tY.vY * tZ;
    if ( tTemp_ == 0.0 && tTemp__4 == 0.0 && tTemp__8 == 0.0 )
    {
      v9 = tTemp__8;
    }
    else
    {
      v8 = sqrt(tTemp_ * tTemp_ + tTemp__4 * tTemp__4 + tTemp__8 * tTemp__8);
      tXa = tTemp_ * (1.0 / v8);
      tX_4a = tTemp__4 * (1.0 / v8);
      v9 = 1.0 / v8 * tTemp__8;
    }
  }
  else
  {
    tTemp_a = vY - v4;
    tXa = tTemp_a;
    tTemp__4a = -(tY.vX - v4);
    tX_4a = tTemp__4a;
    tTemp__8a = tY.vX * 0.0 - tY.vY * 0.0;
    if ( tTemp_a == 0.0 && tTemp__4a == 0.0 && tTemp__8a == 0.0 )
    {
      v9 = tTemp__8a;
    }
    else
    {
      v10 = sqrt(tTemp_a * tTemp_a + tTemp__4a * tTemp__4a + tTemp__8a * tTemp__8a);
      tXa = tTemp_a * (1.0 / v10);
      tX_4a = tTemp__4a * (1.0 / v10);
      v9 = 1.0 / v10 * tTemp__8a;
    }
    tTemp_b = tY.vZ * tX_4a - tY.vY * v9;
    tZ = tTemp_b;
    tTemp__4b = -(tY.vZ * tXa - tY.vX * v9);
    tZ_4 = tTemp__4b;
    tTemp__8b = tY.vY * tXa - tY.vX * tX_4a;
    tZ_8 = tTemp__8b;
    if ( tTemp_b != 0.0 || tTemp__4b != 0.0 || tTemp__8b != 0.0 )
    {
      v11 = 1.0 / sqrt(tTemp_b * tTemp_b + tTemp__4b * tTemp__4b + tTemp__8b * tTemp__8b);
      tZ = tTemp_b * v11;
      tZ_4 = tTemp__4b * v11;
      tZ_8 = tTemp__8b * v11;
    }
  }
  ptOrientation->tZ.vX = v9;
  ptOrientation->tX.vX = tXa;
  ptOrientation->tY.vX = tX_4a;
  ptOrientation->tX.vY = tY.vX;
  ptOrientation->tY.vY = tY.vY;
  ptOrientation->tZ.vY = tY.vZ;
  ptOrientation->tX.vZ = tZ;
  ptOrientation->tY.vZ = tZ_4;
  ptOrientation->tZ.vZ = tZ_8;
}

// source: j/0/gamefunctions.c:563  [anchor-callee]
struct real64x3_t *__cdecl GameFunctions_GetMagicVertex(
        struct real64x3_t *ptPos,
        struct QTask_s *ptQTask,
        int nMagicVertex)
{
  int eQTaskType; // edi

  eQTaskType = ptQTask->eQTaskType;
  if ( QTask_IsQTaskTypeDerived(ptQTask->eQTaskType, RigidDynCubeObj_eQTaskType) )
    return (struct real64x3_t *)RigidDynCubeObj_GetMagicVertexPos(
                                  (struct RigidDynCubeObj_t *)ptQTask,
                                  nMagicVertex,
                                  ptPos);
  if ( QTask_IsQTaskTypeDerived(eQTaskType, BoneDynCubeObj_eQTaskType) )
    return (struct real64x3_t *)BoneDynCubeObj_GetMagicVertexPos(
                                  (struct BoneDynCubeObj_s *)ptQTask,
                                  nMagicVertex,
                                  ptPos);
  LODWORD(ptPos->vX) = 0;
  HIDWORD(ptPos->vX) = 0;
  LODWORD(ptPos->vY) = 0;
  HIDWORD(ptPos->vY) = 0;
  LODWORD(ptPos->vZ) = 0;
  HIDWORD(ptPos->vZ) = 0;
  return nullptr;
}

// source: j/0/gamefunctions.c:597  [anchor-callee]
int __cdecl GameFunctions_GetMagicVertexLocal(
        struct real32x3_t *ptPos,
        struct QTask_s *ptQTask,
        int nMagicVertex)
{
  unsigned __int16 eQTaskType; // dx

  eQTaskType = ptQTask->eQTaskType;
  if ( QTask_IsQTaskTypeDerived(eQTaskType, RigidDynCubeObj_eQTaskType) )
    return RigidDynCubeObj_GetMagicVertexLocalPos((struct RigidDynCubeObj_t *)ptQTask, nMagicVertex, ptPos);
  if ( QTask_IsQTaskTypeDerived(eQTaskType, BoneDynCubeObj_eQTaskType) )
    return BoneDynCubeObj_GetMagicVertexLocalPos((struct BoneDynCubeObj_s *)ptQTask, nMagicVertex, ptPos);
  ptPos->vX = 0.0;
  ptPos->vY = 0.0;
  ptPos->vZ = 0.0;
  return 0;
}

// source: j/0/gamefunctions.c:680  [anchor-strings]
void __cdecl GameFunctions_LoadGameTextures()
{
  #pragma pack(push, 1)
  union
  {
    struct { char v6; };
    struct { char igi2_o1[1]; char zFileName[264]; };
    char igi2_extent[265];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QObjectVector_s *v0; // edx
  unsigned int i; // ebx
  char *v2; // ebp
  unsigned int v3; // eax
  char *v4; // edi

  v0 = GameFunctions_ptGameTextureVector;
  for ( i = 0; i < GameFunctions_ptGameTextureVector->nAllocated; ++i )
  {
    strcpy(igi2_frame.zFileName, "LOCAL:common/textures/");
    memset(&igi2_frame.zFileName[23], 0, 237);
    v2 = (char *)v0->papxElement[i];
    v3 = strlen(v2) + 1;
    v4 = &igi2_frame.v6;
    while ( *++v4 )
      ;
    qmemcpy(v4, v2, v3);
    Texture_Load((struct TexInfo_s *)(v2 + 24), nullptr, igi2_frame.zFileName);
    v0 = GameFunctions_ptGameTextureVector;
  }
}

// source: j/0/gamefunctions.c:707  [anchor-hash]
void __cdecl GameFunctions_FreeGameTextures()
{
  struct QObjectVector_s *v0; // edx
  unsigned int i; // esi
  _DWORD *v2; // edi

  v0 = GameFunctions_ptGameTextureVector;
  for ( i = 0; i < v0->nAllocated; ++i )
  {
    v2 = (char *)v0->papxElement[i] + 24;
    if ( AppContext_tAppContext.isMainMenu == false )
    {
      RenderMode_atRenderMode[*v2].apfRenderModeMethod[Texture_eDeAllocTextureMethod](v2);
      v0 = GameFunctions_ptGameTextureVector;
    }
    memset(v2, 0, 0x2Cu);
  }
}

// source: j/0/gamefunctions.c:730  [anchor-strings]
void __cdecl GameFunctions_LoadGameSprites()
{
  #pragma pack(push, 1)
  union
  {
    struct { char v6; };
    struct { char igi2_o1[1]; char zFileName[264]; };
    char igi2_extent[265];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QObjectVector_s *v0; // edx
  unsigned int i; // ebx
  struct QSprite_s *v2; // ebp
  unsigned int v3; // eax
  char *v4; // edi

  v0 = GameFunctions_ptGameSpriteVector;
  for ( i = 0; i < GameFunctions_ptGameSpriteVector->nAllocated; ++i )
  {
    strcpy(igi2_frame.zFileName, "LOCAL:common/sprites/");
    memset(&igi2_frame.zFileName[22], 0, 238);
    v2 = (struct QSprite_s *)v0->papxElement[i];
    v3 = strlen((char *)v2) + 1;
    v4 = &igi2_frame.v6;
    while ( *++v4 )
      ;
    qmemcpy(v4, v2, v3);
    QSprite_Load(v2 + 1, igi2_frame.zFileName);
    v0 = GameFunctions_ptGameSpriteVector;
  }
}

// source: j/0/gamefunctions.c:757  [anchor-mhash]
void __cdecl GameFunctions_FreeGameSprites()
{
  struct QObjectVector_s *v0; // eax
  unsigned int i; // esi

  v0 = GameFunctions_ptGameSpriteVector;
  for ( i = 0; i < GameFunctions_ptGameSpriteVector->nAllocated; ++i )
  {
    QSprite_DeAlloc((struct QSprite_s *)v0->papxElement[i] + 1);
    v0 = GameFunctions_ptGameSpriteVector;
  }
}

// source: j/0/gamefunctions.c:780  [anchor-callee]
struct GameTexture_s *__cdecl GameFunctions_RegisterGameTexture(char *zName)
{
  struct QObjectVector_s *v1; // esi
  void **papxElement; // ebp
  unsigned int v3; // ecx
  struct GameTexture_s *result; // eax
  unsigned int iGameTexture; // [esp+Ch] [ebp-8h]
  unsigned int nAllocated; // [esp+10h] [ebp-4h]

  v1 = GameFunctions_ptGameTextureVector;
  iGameTexture = 0;
  nAllocated = GameFunctions_ptGameTextureVector->nAllocated;
  if ( nAllocated )
  {
    papxElement = GameFunctions_ptGameTextureVector->papxElement;
    while ( strcmp((char *)*papxElement, zName) )
    {
      ++papxElement;
      if ( ++iGameTexture >= nAllocated )
      {
        v1 = GameFunctions_ptGameTextureVector;
        goto LABEL_6;
      }
    }
    return (struct GameTexture_s *)*papxElement;
  }
  else
  {
LABEL_6:
    if ( v1->nAllocated == v1->nSize )
      QObjectVector_Realloc(v1, v1->nReallocSize);
    v3 = v1->nAllocated;
    result = (struct GameTexture_s *)v1->papxElement[v3];
    v1->nAllocated = v3 + 1;
    strcpy(result->zName, zName);
  }
  return result;
}

// source: j/0/gamefunctions.c:809  [anchor-callee]
struct GameSprite_t *__cdecl GameFunctions_RegisterGameSprite(char *zName)
{
  struct QObjectVector_s *v1; // esi
  void **papxElement; // ebp
  unsigned int v3; // ecx
  struct GameSprite_t *result; // eax
  unsigned int iGameSprite; // [esp+Ch] [ebp-8h]
  unsigned int nAllocated; // [esp+10h] [ebp-4h]

  v1 = GameFunctions_ptGameSpriteVector;
  iGameSprite = 0;
  nAllocated = GameFunctions_ptGameSpriteVector->nAllocated;
  if ( nAllocated )
  {
    papxElement = GameFunctions_ptGameSpriteVector->papxElement;
    while ( strcmp((char *)*papxElement, zName) )
    {
      ++papxElement;
      if ( ++iGameSprite >= nAllocated )
      {
        v1 = GameFunctions_ptGameSpriteVector;
        goto LABEL_6;
      }
    }
    return (struct GameSprite_t *)*papxElement;
  }
  else
  {
LABEL_6:
    if ( v1->nAllocated == v1->nSize )
      QObjectVector_Realloc(v1, v1->nReallocSize);
    v3 = v1->nAllocated;
    result = (struct GameSprite_t *)v1->papxElement[v3];
    v1->nAllocated = v3 + 1;
    strcpy(result->zName, zName);
  }
  return result;
}

// source: j/0/gamefunctions.c:838  [anchor-callee]
enum bool __cdecl GameFunctions_ResolveEvaluateActivate(
        struct EvaluateActivateContext_t *ptEvaluateActivateContext,
        struct QTask_s *ptQTask,
        struct real64x3_t *ptPos)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real64x3_t v8; };
    struct { char igi2_o1[32]; struct real64x3_t Real64x3_RotateInverse_tTemp; };
    char igi2_extent[56];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v3; // st7
  double v4; // st6
  double v5; // st5
  double v6; // st7

  v3 = ptPos->vX - ptEvaluateActivateContext->tViewPos.vX;
  v4 = ptPos->vY - ptEvaluateActivateContext->tViewPos.vY;
  v5 = ptPos->vZ - ptEvaluateActivateContext->tViewPos.vZ;
  if ( sqrt(v4 * v4 + v5 * v5 + v3 * v3) >= ptEvaluateActivateContext->vBestLength )
    return false;
  igi2_frame.Real64x3_RotateInverse_tTemp.vX = ptEvaluateActivateContext->tViewOrientation.tZ.vX * v5
                                  + ptEvaluateActivateContext->tViewOrientation.tY.vX * v4
                                  + ptEvaluateActivateContext->tViewOrientation.tX.vX * v3;
  igi2_frame.Real64x3_RotateInverse_tTemp.vY = ptEvaluateActivateContext->tViewOrientation.tZ.vY * v5
                                  + ptEvaluateActivateContext->tViewOrientation.tY.vY * v4
                                  + ptEvaluateActivateContext->tViewOrientation.tX.vY * v3;
  igi2_frame.Real64x3_RotateInverse_tTemp.vZ = ptEvaluateActivateContext->tViewOrientation.tZ.vZ * v5
                                  + ptEvaluateActivateContext->tViewOrientation.tY.vZ * v4
                                  + ptEvaluateActivateContext->tViewOrientation.tX.vZ * v3;
  if ( igi2_frame.Real64x3_RotateInverse_tTemp.vY <= 0.0 )
    return false;
  qmemcpy(&igi2_frame.v8, &igi2_frame.Real64x3_RotateInverse_tTemp, sizeof(igi2_frame.v8));
  v6 = GameFunctions_CalcGamma(igi2_frame.v8);
  if ( v6 < 0.0 )
    v6 = -v6;
  if ( v6 > ptEvaluateActivateContext->vBestGamma )
    return false;
  ptEvaluateActivateContext->vBestGamma = v6;
  ptEvaluateActivateContext->ptBestQTask = ptQTask;
  ptEvaluateActivateContext->vBestAlpha = 0.0;
  return true;
}

// source: j/0/gamefunctions.c:899  [anchor-mhash]
float __cdecl GameFunctions_ResolveExplosionHit(
        struct ExplosionHitContext_t *ptExplosionHitContext,
        struct QTask_s *ptQTask,
        struct real64x3_t *ptPos,
        float vRadius,
        enum bool isLineOfSight)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v16; };
    struct { float v17; };
    struct { char igi2_o2[4]; float v18; };
    struct { char igi2_o3[4]; float v19; };
    struct { char igi2_o4[8]; float v20; };
    struct { char igi2_o5[8]; float v21; };
    struct { char igi2_o6[12]; float i; };
    struct { char igi2_o7[12]; float v22; };
    struct { char igi2_o8[16]; float v24; };
    struct { char igi2_o9[20]; double v25; };
    struct { char igi2_o10[20]; float v26; };
    struct { char igi2_o11[32]; float v27; };
    struct { char igi2_o12[36]; struct QIntersection_s ptIntersection; };
    struct { char igi2_o13[188]; int v29; };
    struct { char igi2_o14[192]; int v30; };
    struct { char igi2_o15[200]; int v31; };
    char igi2_extent[232];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double vDamage; // st7
  struct real64x3_t *v6; // esi
  double v7; // st5
  long double v8; // st6
  double v9; // st7
  double v10; // st6
  long double v11; // st6
  double v12; // st7
  int v13; // eax
  double v14; // st7

  vDamage = 0.0;
  v6 = ptExplosionHitContext->ptPos;
  v7 = v6->vY - ptPos->vY;
  igi2_frame.v25 = v6->vZ - ptPos->vZ;
  v8 = sqrt((v6->vX - ptPos->vX) * (v6->vX - ptPos->vX) + v7 * v7 + igi2_frame.v25 * igi2_frame.v25)
     - vRadius
     - ptExplosionHitContext->vFullRange;
  igi2_frame.v16 = v8;
  if ( v8 >= 0.0 )
  {
    if ( igi2_frame.v16 >= (double)ptExplosionHitContext->vFallOffRange )
      return vDamage;
    v9 = 1.0 - igi2_frame.v16 / ptExplosionHitContext->vFallOffRange;
    if ( ptExplosionHitContext->eDamageFalloffType == EXPLOSIONDAMAGE_EXPONENTIAL_FALLOFF )
      v9 = v9 * v9;
    vDamage = v9 * ptExplosionHitContext->vDamage;
  }
  else
  {
    vDamage = ptExplosionHitContext->vDamage;
  }
  igi2_frame.v24 = vDamage;
  if ( vDamage != 0.0 )
  {
    v10 = ptExplosionHitContext->vFullRange * 0.000244140625;
    LODWORD(igi2_frame.ptIntersection.tNormal.vZ) = ptExplosionHitContext->ptOwnerQTask;
    igi2_frame.v26 = v10;
    igi2_frame.v17 = v10;
    LODWORD(igi2_frame.ptIntersection.tNormal.vY) = ptQTask;
    igi2_frame.ptIntersection.iSector = 1065353216;
    igi2_frame.ptIntersection.tNormal.vX = 0.0;
    qmemcpy(&igi2_frame.ptIntersection, v6, 0x18u);
    igi2_frame.ptIntersection.tPos.vY = igi2_frame.ptIntersection.tPos.vY + 409.6000061035156;
    qmemcpy(&igi2_frame.ptIntersection.tPos.vZ, ptPos, 0x18u);
    *(double *)&igi2_frame.ptIntersection.tLocalPos.vZ = *(double *)&igi2_frame.ptIntersection.tLocalPos.vZ + 409.6000061035156;
    igi2_frame.v18 = igi2_frame.ptIntersection.tPos.vZ - *(double *)&igi2_frame.ptIntersection.ptHitObj;
    igi2_frame.v20 = *(double *)&igi2_frame.ptIntersection.tLocalPos.vX - igi2_frame.ptIntersection.tPos.vX;
    igi2_frame.v22 = *(double *)&igi2_frame.ptIntersection.tLocalPos.vZ - igi2_frame.ptIntersection.tPos.vY;
    v11 = sqrt(
            igi2_frame.v18 * igi2_frame.v18
          + igi2_frame.v20 * igi2_frame.v20
          + (*(double *)&igi2_frame.ptIntersection.tLocalPos.vZ - igi2_frame.ptIntersection.tPos.vY)
          * (*(double *)&igi2_frame.ptIntersection.tLocalPos.vZ - igi2_frame.ptIntersection.tPos.vY));
    if ( v11 != 0.0 && igi2_frame.v17 != 0.0 && QTask_IsQTaskTypeDerived(ptQTask->eQTaskType, GenericTBA_eQTaskType) == false )
    {
      igi2_frame.v27 = v11;
      v12 = 40.959999084472656 / igi2_frame.v27;
      igi2_frame.v19 = igi2_frame.v18 * v12;
      igi2_frame.v21 = igi2_frame.v20 * v12;
      for ( igi2_frame.i = v12 * igi2_frame.v22; ; igi2_frame.ptIntersection.tPos.vY = igi2_frame.i + igi2_frame.ptIntersection.vDistance )
      {
        igi2_frame.v29 = 0;
        igi2_frame.v30 = 0;
        World_TraceLines(
          Game_ptGame->ptWorld,
          (struct QIntersection_s *)&igi2_frame.ptIntersection.iFace,
          (struct real64x3_t *)&igi2_frame.ptIntersection,
          (struct real64x3_t *)&igi2_frame.ptIntersection.tPos.vZ,
          1,
          GameFunctions_eWeaponCollisionEvaluateQTaskEvent,
          (struct CollisionEvaluateContext_s *)&igi2_frame.ptIntersection.tLocalNormal.vZ,
          Forest_bQTaskGroup | 0x98000000);
        if ( !igi2_frame.v31 )
          break;
        v13 = igi2_frame.v29;
        if ( !igi2_frame.v29 )
        {
          v13 = igi2_frame.v30;
          if ( !igi2_frame.v30 )
            break;
        }
        v14 = igi2_frame.v17 - *(float *)(v13 + 64);
        igi2_frame.v17 = v14;
        if ( v14 <= 0.0 )
        {
          igi2_frame.v17 = 0.0;
          break;
        }
        *(double *)&igi2_frame.ptIntersection.ptHitObj = igi2_frame.v19 + *(double *)&igi2_frame.ptIntersection.ptEnterMaterial;
        igi2_frame.ptIntersection.tPos.vX = igi2_frame.v21 + *(double *)&igi2_frame.ptIntersection.isDoubleFace;
      }
      if ( igi2_frame.v26 == 0.0 )
        return igi2_frame.v24;
      else
        return igi2_frame.v17 / igi2_frame.v26 * igi2_frame.v24;
    }
  }
  return vDamage;
}

void __cdecl GameFunctions_WeaponCollisionEvaluateHandler(struct QTask_s *a1, void *a2)
{
  *(_BYTE *)a2 = a1 != *((struct QTask_s **)a2 + 1)
              && a1 != *((struct QTask_s **)a2 + 2)
              && a1 != *((struct QTask_s **)a2 + 3);
}

void __cdecl GameFunctions_WeaponCollisionEvaluateDiscardHandler(struct QTask_s *a1, void *a2)
{
  *(_BYTE *)a2 = 0;
}

// source: j/0/gamefunctions.c:1132  [size]
void __cdecl GameFunctions_ObjectCollisionEvaluateDiscardHandler(
        struct QTask_s *ptQTask,
        void *pxContext)
{
  *(_BYTE *)pxContext = 0;
}

// source: j/0/gamefunctions.c:1148  [size]
void __cdecl GameFunctions_GetNextZEvaluateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_BYTE *)pxContext = ptQTask != *((struct QTask_s **)pxContext + 1);
}

// source: j/0/gamefunctions.c:1175  [anchor-callee]
struct real32x3_t *__cdecl GameFunctions_GetRandomUnitVectorInCone(
        struct real32x3_t *retstr,
        float vConeRadians,
        struct real32x3_t *ptConeDirection,
        int ltcg_edx)
{
  struct Game_s *v4; // eax
  unsigned int v5; // ecx
  int v6; // ecx
  double v7; // st7
  long double v8; // st7
  int v9; // esi
  int v10; // esi
  unsigned int v11; // esi
  long double v12; // st6
  long double v13; // rt2
  long double v14; // st6
  long double v15; // st4
  long double v16; // st5
  long double v17; // st7
  long double v18; // st6
  double v19; // st5
  double v20; // st6
  long double v21; // st3
  long double v22; // st6
  long double v23; // st3
  long double v24; // st5
  float v26; // [esp+4h] [ebp-44h]
  float v27; // [esp+8h] [ebp-40h]
  float tX; // [esp+18h] [ebp-30h]
  float tX_4; // [esp+1Ch] [ebp-2Ch]
  float tX_8; // [esp+20h] [ebp-28h]
  float tZ; // [esp+24h] [ebp-24h]
  float tZa; // [esp+24h] [ebp-24h]
  float tZ_4; // [esp+28h] [ebp-20h]
  float tZ_4a; // [esp+28h] [ebp-20h]
  float tZ_8; // [esp+2Ch] [ebp-1Ch]
  float tTemp_; // [esp+30h] [ebp-18h]
  float tTemp_a; // [esp+30h] [ebp-18h]
  float tTemp_b; // [esp+30h] [ebp-18h]
  float tTemp_c; // [esp+30h] [ebp-18h]
  float tTemp__4; // [esp+34h] [ebp-14h]
  float tTemp__4a; // [esp+34h] [ebp-14h]
  float tTemp__4b; // [esp+34h] [ebp-14h]
  float tTemp__4c; // [esp+34h] [ebp-14h]
  float tTemp__8; // [esp+38h] [ebp-10h]
  float tTemp__8a; // [esp+38h] [ebp-10h]
  float tTemp__8b; // [esp+38h] [ebp-10h]
  float tTemp__8c; // [esp+38h] [ebp-10h]
  float tReal32x3a; // [esp+3Ch] [ebp-Ch]
  float tReal32x3; // [esp+3Ch] [ebp-Ch]
  float tReal32x3_4; // [esp+40h] [ebp-8h]
  float retstra = *(float *)&retstr; // [esp+4Ch] [ebp+4h] ARGSLOT
  struct real32x3_t tConeDirection; // 0:^C.12

  tConeDirection = *ptConeDirection;
  v4 = Game_ptGame;
  v5 = (Game_ptGame->tRunRandomState.anRandom[0] >> 7) ^ Game_ptGame->tRunRandomState.anRandom[2];
  Game_ptGame->tRunRandomState.anRandom[2] = v5;
  v6 = v5 ^ v4->tRunRandomState.anRandom[1];
  v4->tRunRandomState.anRandom[1] = v6;
  v7 = (double)(unsigned __int16)(v6 + LOWORD(v4->tRunRandomState.anRandom[0]));
  v4->tRunRandomState.anRandom[0] += v6;
  v8 = v7 * 0.0000152587890625 * 6.283185307179589;
  v9 = (v4->tRunRandomState.anRandom[0] >> 7) ^ v4->tRunRandomState.anRandom[2];
  v4->tRunRandomState.anRandom[2] = v9;
  v10 = v9 ^ v4->tRunRandomState.anRandom[1];
  v4->tRunRandomState.anRandom[1] = v10;
  v11 = v10 + v4->tRunRandomState.anRandom[0];
  v4->tRunRandomState.anRandom[0] = v11;
  v12 = tan(*(float *)&retstr) * ((double)(unsigned __int16)v11 * 0.0000152587890625);
  tReal32x3a = sin(v8) * v12;
  v13 = v12;
  v14 = cos(v8);
  v15 = sqrt(tReal32x3a * tReal32x3a + v13 * v14 * (v13 * v14) + 1.0);
  tReal32x3 = tReal32x3a * (1.0 / v15);
  v16 = 1.0 / v15;
  tReal32x3_4 = v16;
  v17 = v13 * v14 * v16;
  if ( tConeDirection.vX != 0.0 || tConeDirection.vY != 0.0 || tConeDirection.vZ != 0.0 )
  {
    v18 = 1.0
        / sqrt(
            tConeDirection.vX * tConeDirection.vX
          + tConeDirection.vY * tConeDirection.vY
          + tConeDirection.vZ * tConeDirection.vZ);
    tConeDirection.vX = tConeDirection.vX * v18;
    tConeDirection.vY = tConeDirection.vY * v18;
    tConeDirection.vZ = tConeDirection.vZ * v18;
  }
  v19 = tConeDirection.vZ * 0.0;
  tZ = tConeDirection.vY - v19;
  tX = tZ;
  tZ_4 = -(tConeDirection.vX - v19);
  tX_4 = tZ_4;
  retstra = tConeDirection.vX * 0.0;
  v27 = tConeDirection.vY * 0.0;
  tZ_8 = retstra - v27;
  tX_8 = tZ_8;
  v26 = sqrt(tZ * tZ + tZ_4 * tZ_4 + tZ_8 * tZ_8);
  if ( v26 <= 0.10000000149011612 )
  {
    tTemp_a = v19 - v27;
    tZa = tTemp_a;
    tTemp__4a = -(tConeDirection.vZ - retstra);
    tZ_4a = tTemp__4a;
    tTemp__8a = tConeDirection.vY - retstra;
    if ( tTemp_a == 0.0 && tTemp__4a == 0.0 && tTemp__8a == 0.0 )
    {
      v22 = tTemp__8a;
    }
    else
    {
      v23 = sqrt(tTemp_a * tTemp_a + tTemp__4a * tTemp__4a + tTemp__8a * tTemp__8a);
      tZa = tTemp_a * (1.0 / v23);
      tZ_4a = tTemp__4a * (1.0 / v23);
      v22 = 1.0 / v23 * tTemp__8a;
    }
    tTemp_b = tConeDirection.vY * v22 - tZ_4a * tConeDirection.vZ;
    tX = tTemp_b;
    tTemp__4b = -(tConeDirection.vX * v22 - tZa * tConeDirection.vZ);
    tX_4 = tTemp__4b;
    tTemp__8b = tZ_4a * tConeDirection.vX - tZa * tConeDirection.vY;
    tX_8 = tTemp__8b;
    if ( tTemp_b != 0.0 || tTemp__4b != 0.0 || tTemp__8b != 0.0 )
    {
      v24 = 1.0 / sqrt(tTemp_b * tTemp_b + tTemp__4b * tTemp__4b + tTemp__8b * tTemp__8b);
      tX = tTemp_b * v24;
      tX_4 = tTemp__4b * v24;
      tX_8 = tTemp__8b * v24;
    }
  }
  else
  {
    if ( tZ != 0.0 || tZ_4 != 0.0 || tZ_8 != 0.0 )
    {
      v20 = 1.0 / v26;
      tX = tZ * v20;
      tX_4 = tZ_4 * v20;
      tX_8 = tZ_8 * v20;
    }
    tTemp_ = tX_4 * tConeDirection.vZ - tX_8 * tConeDirection.vY;
    tZa = tTemp_;
    tTemp__4 = -(tX * tConeDirection.vZ - tX_8 * tConeDirection.vX);
    tZ_4a = tTemp__4;
    tTemp__8 = tX * tConeDirection.vY - tX_4 * tConeDirection.vX;
    if ( tTemp_ == 0.0 && tTemp__4 == 0.0 && tTemp__8 == 0.0 )
    {
      v22 = tTemp__8;
    }
    else
    {
      v21 = sqrt(tTemp_ * tTemp_ + tTemp__4 * tTemp__4 + tTemp__8 * tTemp__8);
      tZa = tTemp_ * (1.0 / v21);
      tZ_4a = tTemp__4 * (1.0 / v21);
      v22 = 1.0 / v21 * tTemp__8;
    }
  }
  tTemp_c = tX * tReal32x3 + tZa * v17 + tConeDirection.vX * tReal32x3_4;
  *(float *)ltcg_edx = tTemp_c;
  tTemp__4c = tX_4 * tReal32x3 + tZ_4a * v17 + tConeDirection.vY * tReal32x3_4;
  *(float *)(ltcg_edx + 4) = tTemp__4c;
  tTemp__8c = tX_8 * tReal32x3 + v22 * v17 + tConeDirection.vZ * tReal32x3_4;
  *(float *)(ltcg_edx + 8) = tTemp__8c;
  return (struct real32x3_t *)ltcg_edx;
}

// source: j/0/gamefunctions.c:1237  [anchor-strings]
void __cdecl GameFunctions_Open()
{
  struct QObjectVector_s *v0; // esi
  struct QObjectVector_s *v1; // esi

  v0 = (struct QObjectVector_s *)Mem_AllocFn(52, 4);
  v0->isStrictOrder = false;
  v0->nSize = 0;
  v0->nAllocated = 0;
  v0->nReallocSize = 8;
  v0->papxElement = nullptr;
  v0->nElementSize = 72;
  v0->tMemPool.nBlocks = 0;
  v0->tMemPool.nAllocatedBlocks = 0;
  v0->tMemPool.nAlignment = 4;
  v0->tMemPool.nBlockSize = 72;
  v0->tMemPool.nReAllocBlocks = 8;
  v0->tMemPool.tMemPoolFreeList.ptHead = nullptr;
  v0->tMemPool.tMemPoolSegmentList.ptHead = nullptr;
  MemPool_ReAlloc(&v0->tMemPool, 0x10u);
  QObjectVector_Realloc(v0, 0x10u);
  GameFunctions_ptGameTextureVector = v0;
  v1 = (struct QObjectVector_s *)Mem_AllocFn(52, 4);
  v1->nElementSize = 52;
  v1->tMemPool.nBlockSize = 52;
  v1->isStrictOrder = false;
  v1->nSize = 0;
  v1->nAllocated = 0;
  v1->nReallocSize = 8;
  v1->papxElement = nullptr;
  v1->tMemPool.nBlocks = 0;
  v1->tMemPool.nAllocatedBlocks = 0;
  v1->tMemPool.nAlignment = 4;
  v1->tMemPool.nReAllocBlocks = 8;
  v1->tMemPool.tMemPoolFreeList.ptHead = nullptr;
  v1->tMemPool.tMemPoolSegmentList.ptHead = nullptr;
  MemPool_ReAlloc(&v1->tMemPool, 0x10u);
  QObjectVector_Realloc(v1, 0x10u);
  GameFunctions_ptGameSpriteVector = v1;
  GameFunctions_eNotifyQTaskEvent = QTask_NewQTaskEventFn(0, "Notify");
  GameFunctions_ePickupQTaskEvent = QTask_NewQTaskEventFn(0, "Pickup");
  GameFunctions_eEvaluateActivateQTaskEvent = QTask_NewQTaskEventFn(0, "EvaluateActivate");
  GameFunctions_eGetActivateQTaskEvent = QTask_NewQTaskEventFn(0, "GetActivate");
  GameFunctions_eActivateQTaskEvent = QTask_NewQTaskEventFn(0, "Activate");
  GameFunctions_eDeactivateQTaskEvent = QTask_NewQTaskEventFn(0, "Deactivate");
  GameFunctions_eActivateDisplayQTaskEvent = QTask_NewQTaskEventFn(0, "ActivateDisplay");
  GameFunctions_eWeaponCollisionEvaluateQTaskEvent = QTask_NewQTaskEventFn(0, "WeaponCollisionEvaluate");
  GameFunctions_eObjectCollisionEvaluateQTaskEvent = QTask_NewQTaskEventFn(0, "ObjectCollisionEvaluate");
  GameFunctions_eWeaponHitQTaskEvent = QTask_NewQTaskEventFn(0, "WeaponHit");
  GameFunctions_eObjectHitQTaskEvent = QTask_NewQTaskEventFn(0, "ObjectHit");
  GameFunctions_eExplosionHitQTaskEvent = QTask_NewQTaskEventFn(0, "ExplosionHit");
  GameFunctions_eElectricDamageQTaskEvent = QTask_NewQTaskEventFn(0, "ElectricDamage");
  GameFunctions_eGetNextZEvaluateQTaskEvent = QTask_NewQTaskEventFn(0, "GetNextZEvaluate");
  GameFunctions_ptActivateQTaskList = QTaskList_New(512);
  GameFunctions_ptNotifyQTaskList = QTaskList_New(64);
  GameFunctions_ptPickupQTaskList = QTaskList_New(256);
  GameFunctions_ptExplosionQTaskList = QTaskList_New(512);
  GameFunctions_ptVehicleQTaskList = QTaskList_New(16);
  GameFunctions_ptCutsceneDeleteQTaskList = QTaskList_New(128);
  Vehicle_ptQTaskList = GameFunctions_ptVehicleQTaskList;
}

// source: j/0/gamefunctions.c:1280  [anchor-hash]
void __cdecl GameFunctions_Close()
{
  QTask_DeleteQTaskEvent(GameFunctions_eGetNextZEvaluateQTaskEvent);
  QTask_DeleteQTaskEvent(GameFunctions_eWeaponCollisionEvaluateQTaskEvent);
  QTask_DeleteQTaskEvent(GameFunctions_eObjectCollisionEvaluateQTaskEvent);
  QTask_DeleteQTaskEvent(GameFunctions_eWeaponHitQTaskEvent);
  QTask_DeleteQTaskEvent(GameFunctions_eObjectHitQTaskEvent);
  QTask_DeleteQTaskEvent(GameFunctions_eExplosionHitQTaskEvent);
  QTask_DeleteQTaskEvent(GameFunctions_eElectricDamageQTaskEvent);
  QTask_DeleteQTaskEvent(GameFunctions_eActivateDisplayQTaskEvent);
  QTask_DeleteQTaskEvent(GameFunctions_eDeactivateQTaskEvent);
  QTask_DeleteQTaskEvent(GameFunctions_eActivateQTaskEvent);
  QTask_DeleteQTaskEvent(GameFunctions_eGetActivateQTaskEvent);
  QTask_DeleteQTaskEvent(GameFunctions_eEvaluateActivateQTaskEvent);
  QTask_DeleteQTaskEvent(GameFunctions_ePickupQTaskEvent);
  QTask_DeleteQTaskEvent(GameFunctions_eNotifyQTaskEvent);
  QTaskList_Delete(GameFunctions_ptActivateQTaskList);
  QTaskList_Delete(GameFunctions_ptNotifyQTaskList);
  QTaskList_Delete(GameFunctions_ptPickupQTaskList);
  QTaskList_Delete(GameFunctions_ptExplosionQTaskList);
  QTaskList_Delete(GameFunctions_ptVehicleQTaskList);
  QTaskList_Delete(GameFunctions_ptCutsceneDeleteQTaskList);
  QObjectVector_Delete(GameFunctions_ptGameSpriteVector);
  QObjectVector_Delete(GameFunctions_ptGameTextureVector);
}
