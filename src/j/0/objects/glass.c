/* j/0/objects/glass.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/objects/glass.c:95  [anchor-mhash]
void __cdecl Glass_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct Game_s *v2; // eax
  int v3; // ecx
  unsigned int v4; // edx
  bool v5; // zf
  struct QReference_s *ptHead; // edi
  struct QReference_s *NextGameItemNode; // ebx

  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][RigidMagicObj_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  QTaskList_Register(GameFunctions_ptExplosionQTaskList, (struct QTaskList_s *)ptQTask);
  v2 = Game_ptGame;
  ptQTask[8].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[8].tQTaskChildren.ptTail = (struct QTask_s *)1061158912;
  v3 = (v2->tRunRandomState.anRandom[0] >> 7) ^ v2->tRunRandomState.anRandom[2] ^ v2->tRunRandomState.anRandom[1];
  v4 = v3 + v2->tRunRandomState.anRandom[0];
  v2->tRunRandomState.anRandom[2] ^= v2->tRunRandomState.anRandom[0] >> 7;
  v2->tRunRandomState.anRandom[1] = v3;
  v2->tRunRandomState.anRandom[0] = v4;
  v5 = Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER;
  BYTE1(ptQTask[8].tQTaskRefList.ptHead) = 0;
  LOBYTE(ptQTask[8].tQTaskRefList.ptHead) = 0;
  *(float *)&ptQTask[8].tQTaskChildren.ptTail = (double)(unsigned __int16)v4 * 0.0000152587890625 * 0.75
                                              + *(float *)&ptQTask[8].tQTaskChildren.ptTail;
  ptQTask[8].tQTaskChildren.ptHead = *((struct QTask_s **)pxContext + 38);
  LOBYTE(ptQTask[8].tQTaskRefList.ptTail) = 0;
  if ( v5 )
  {
    ptHead = Flow_ptFlow->ptNetManagerQTask[6].tQTaskRefList.ptHead;
    NextGameItemNode = NetworkGameItem_GetNextGameItemNode();
    LOWORD(NextGameItemNode->ptNext) = LOWORD(ptHead[3].ptPrev)++;
    NextGameItemNode->ptPrev = QTask_NewQTaskRef(ptQTask);
    LOWORD(NextGameItemNode->pxObject) = 1;
    NextGameItemNode[1].ptNext = nullptr;
    ++HIWORD(ptHead[3].ptPrev);
    LOWORD(ptHead[3].pxObject) += 7;
    ptQTask[8].tQTaskRefList.ptMiddle = (struct QReference_s *)LOWORD(NextGameItemNode->ptNext);
  }
  strcpy((char *)&ptQTask[8].tQTaskRefList.ptTail, GlassContainer_RegisterGlass(ptQTask));
}

// source: j/0/objects/glass.c:155  [anchor-mhash]
void __cdecl Glass_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QHashTable_s *ptQHashTable; // ebp
  int v2; // eax

  if ( GlassContainer_ptGlassContainer )
  {
    ptQHashTable = GlassContainer_ptGlassContainer->ptQHashTable;
    v2 = ptQHashTable->tPrivate.pfHashFunction(ptQHashTable->tPrivate.nHashTableSize, &ptQTask[8].tQTaskRefList.ptTail);
    ((void  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))ptQHashTable->tPrivate.pfDeleteElement)(ptQHashTable, v2, (const void *)(&ptQTask[8].tQTaskRefList.ptTail));
    QVector_RemoveElementByPointer(GlassContainer_ptGlassContainer->ptQVector, ptQTask);
  }
  QTaskList_Remove(GameFunctions_ptExplosionQTaskList, ptQTask);
  World_RemoveDynCubeObj((struct World_s *)ptQTask[2].ptParent, (struct DynCubeObj_s *)ptQTask);
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
    NetworkGameItem_RemoveGameItem((int)ptQTask[8].tQTaskRefList.ptMiddle);
}

// source: j/0/objects/glass.c:185  [anchor-mhash]
void __cdecl Glass_GlassRunHandler(struct QTask_s *ptQTask)
{
  if ( BYTE1(ptQTask[8].tQTaskRefList.ptHead) )
  {
    if ( !LOBYTE(ptQTask[8].tQTaskRefList.ptHead) )
    {
      QTaskList_Remove(GameFunctions_ptExplosionQTaskList, ptQTask);
      World_RemoveDynCubeObj((struct World_s *)ptQTask[2].ptParent, (struct DynCubeObj_s *)ptQTask);
      LOBYTE(ptQTask[8].tQTaskRefList.ptHead) = 1;
    }
  }
}

// source: j/0/objects/glass.c:209  [anchor-mhash]
void __cdecl Glass_MagicObjEnterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  if ( !LOBYTE(ptQTask[8].tQTaskRefList.ptHead) )
    ((void (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[MagicObj_eMagicObjEnterEvent][RigidMagicObj_eQTaskType].pfHandler)(
      ptQTask,
      0);
}

// source: j/0/objects/glass.c:232  [size]
void __cdecl Glass_ParseMagicObjParametersHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: j/0/objects/glass.c:252  [size]
void __cdecl Glass_GetMagicObjParameterSizeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = 4;
}

// source: j/0/objects/glass.c:268  [anchor-mhash]
void __cdecl Glass_WeaponHitHandler(struct QTask_s *ptQTask, void *pxContext)
{
  double v2; // st7
  struct QIntersection_s *v3; // edx
  float v4; // eax
  struct LODVirModel_s *v5; // eax
  struct real32x3_t tImpactSpeed; // [esp+8h] [ebp-Ch] BYREF

  v2 = *((float *)pxContext + 1) + *(float *)&ptQTask[8].tQTaskChildren.ptMiddle;
  *(float *)&ptQTask[8].tQTaskChildren.ptMiddle = v2;
  if ( v2 >= *(float *)&ptQTask[8].tQTaskChildren.ptTail && !BYTE1(ptQTask[8].tQTaskRefList.ptHead) )
  {
    BYTE1(ptQTask[8].tQTaskRefList.ptHead) = 1;
    v3 = *(struct QIntersection_s **)pxContext;
    tImpactSpeed.vX = *((float *)pxContext + 2);
    v4 = *((float *)pxContext + 4);
    tImpactSpeed.vY = *((float *)pxContext + 3);
    tImpactSpeed.vX = tImpactSpeed.vX * 0.007000000216066837;
    tImpactSpeed.vZ = v4;
    v5 = *(struct LODVirModel_s **)&ptQTask[2].eQTaskType;
    tImpactSpeed.vY = tImpactSpeed.vY * 0.007000000216066837;
    tImpactSpeed.vZ = tImpactSpeed.vZ * 0.007000000216066837;
    GlassShatter_NewLocalImpact(
      v5,
      &tImpactSpeed,
      (struct real64x3_t *)&ptQTask[1],
      (struct real32x9_t *)&ptQTask[3].ptPrev,
      v3);
  }
}

// source: j/0/objects/glass.c:317  [anchor-mhash]
void __cdecl Glass_ExplosionHitHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v7; };
    struct { char igi2_o1[36]; float v8; };
    struct { char igi2_o2[40]; struct real64x3_t ptPos; };
    char igi2_extent[68];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // eax
  float *v3; // eax
  double v4; // st6
  double v5; // st7
  struct LODVirModel_s *v6; // edx

  v2 = *(_DWORD *)&ptQTask[2].eQTaskType;
  if ( v2 )
  {
    v3 = *(float **)(*(_DWORD *)(*(_DWORD *)v2 + 12) + 12);
    igi2_frame.v7 = v3[15];
    v4 = *(float *)&ptQTask[3].tQTaskRefList.ptHead * v3[13]
       + *(float *)&ptQTask[3].tQTaskChildren.ptTail * v3[12]
       + *(float *)&ptQTask[3].tQTaskRefList.ptMiddle * v3[14];
    igi2_frame.v8 = *(float *)&ptQTask[3].ptParent * v3[13]
       + *(float *)&ptQTask[3].tQTaskRefList.ptTail * v3[12]
       + *(float *)&ptQTask[3].eQTaskType * v3[14];
    igi2_frame.ptPos.vX = *(float *)&ptQTask[3].tQTaskChildren.ptHead * v3[13]
             + *(float *)&ptQTask[3].tQTaskChildren.ptMiddle * v3[14]
             + v3[12] * *(float *)&ptQTask[3].ptPrev
             + *(double *)&ptQTask[1].ptNext;
    igi2_frame.ptPos.vY = v4 + *(double *)&ptQTask[1].tQTaskChildren.ptHead;
    igi2_frame.ptPos.vZ = igi2_frame.v8 + *(double *)&ptQTask[1].tQTaskChildren.ptTail;
    v5 = GameFunctions_ResolveExplosionHit((struct ExplosionHitContext_t *)pxContext, ptQTask, &igi2_frame.ptPos, igi2_frame.v7, false);
    *(float *)&ptQTask[8].tQTaskChildren.ptMiddle = v5 + *(float *)&ptQTask[8].tQTaskChildren.ptMiddle;
    if ( v5 != 0.0 && !BYTE1(ptQTask[8].tQTaskRefList.ptHead) )
    {
      v6 = *(struct LODVirModel_s **)&ptQTask[2].eQTaskType;
      BYTE1(ptQTask[8].tQTaskRefList.ptHead) = 1;
      GlassShatter_NewExplosion(
        v6,
        (struct real32x9_t *)&ptQTask[3].ptPrev,
        (struct real64x3_t *)&ptQTask[1],
        *((struct real64x3_t **)pxContext + 3),
        *((float *)pxContext + 6),
        409.6000061035156);
    }
  }
}

// source: j/0/objects/glass.c:397  [anchor-mhash]
void __cdecl Glass_PhysicsObjHitHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptTail; // esi

  *((_DWORD *)pxContext + 2) = 1;
  if ( !BYTE1(ptQTask[8].tQTaskRefList.ptHead) )
  {
    ptTail = ptQTask[8].tQTaskChildren.ptTail;
    BYTE1(ptQTask[8].tQTaskRefList.ptHead) = 1;
    ptQTask[8].tQTaskChildren.ptMiddle = ptTail;
    GlassShatter_NewExplosion(
      *(struct LODVirModel_s **)&ptQTask[2].eQTaskType,
      (struct real32x9_t *)&ptQTask[3].ptPrev,
      (struct real64x3_t *)&ptQTask[1],
      (struct real64x3_t *)(*(_DWORD *)pxContext + 40),
      12288.0,
      204.8000030517578);
  }
}

// source: j/0/objects/glass.c:439  [size]
void __cdecl Glass_AIDetectionLineOfSightHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_BYTE *)pxContext = 0;
}

// source: j/0/objects/glass.c:459  [size]
void __cdecl Glass_GetGameItemDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *((_WORD *)pxContext + 1) = 1;
  *(_WORD *)pxContext = ptQTask[8].tQTaskRefList.ptMiddle;
  *((_WORD *)pxContext + 2) = Glass_eQTaskType;
  *((_BYTE *)pxContext + 6) = BYTE1(ptQTask[8].tQTaskRefList.ptHead);
}

// source: j/0/objects/glass.c:491  [size]
void __cdecl Glass_GameItemUpdateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  if ( *((_BYTE *)pxContext + 6) )
    BYTE1(ptQTask[8].tQTaskRefList.ptHead) = 1;
}

// source: j/0/objects/glass.c:521  [size]
enum bool __cdecl Glass_IsBroken(struct QTask_s *ptQTask)
{
  return SLOBYTE(ptQTask[8].tQTaskRefList.ptHead);
}

// source: j/0/objects/glass.c:539  [anchor-mhash]
enum bool __cdecl Glass_SetBroken(struct QTask_s *ptQTask, enum bool isBroken)
{
  int *v2; // eax
  int v3; // eax
  float ptDynCubeObj; // [esp+0h] [ebp-4h]

  if ( isBroken )
  {
    BYTE1(ptQTask[8].tQTaskRefList.ptHead) = 1;
  }
  else
  {
    isBroken = LOBYTE(ptQTask[8].tQTaskRefList.ptHead);
    if ( (_BYTE)isBroken )
    {
      QTaskList_Register(GameFunctions_ptExplosionQTaskList, (struct QTaskList_s *)ptQTask);
      v2 = *(int **)&ptQTask[2].eQTaskType;
      if ( v2 && (v3 = *v2) != 0 )
        ptDynCubeObj = *(float *)(*(_DWORD *)(*(_DWORD *)(v3 + 12) + 12) + 120);
      else
        ptDynCubeObj = 1.0;
      World_RegisterDynCubeObjFirstTimeRadius(
        Game_ptGame->ptWorld,
        (struct DynCubeObj_s *)ptQTask,
        (struct real64x3_t *)&ptQTask[1],
        ptDynCubeObj,
        (enum DynCubeTreeCategory_enum)ptQTask[7].tQTaskChildren.ptMiddle);
      LOBYTE(ptQTask[8].tQTaskRefList.ptHead) = 0;
    }
    BYTE1(ptQTask[8].tQTaskRefList.ptHead) = 0;
  }
  return isBroken;
}

// source: j/0/objects/glass.c:581  [size]
char *__cdecl Glass_GetGlassContainerID(struct QTask_s *ptQTask)
{
  return (char *)&ptQTask[8].tQTaskRefList.ptTail;
}

// source: j/0/objects/glass.c:599  [anchor-strings]
void __cdecl Glass_Open()
{
  unsigned __int16 v0; // si
  _DWORD *v1; // esi

  v0 = QTask_NewQTaskType("Glass", 608, RigidMagicObj_eQTaskType, 0, 0);
  Glass_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 0, Glass_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, nullptr);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, GlassContainer_eGlassRunEvent, Glass_GlassRunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, Glass_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v0, MagicObj_eMagicObjEnterEvent, Glass_MagicObjEnterHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    MagicObj_eGetParseMagicObjParametersEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Glass_ParseMagicObjParametersHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    MagicObj_eGetMagicObjParameterSizeEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Glass_GetMagicObjParameterSizeHandler);
  QTask_LinkQTaskEventHandlerFn(v0, GameFunctions_eWeaponHitQTaskEvent, Glass_WeaponHitHandler);
  QTask_LinkQTaskEventHandlerFn(v0, GameFunctions_eExplosionHitQTaskEvent, Glass_ExplosionHitHandler);
  QTask_LinkQTaskEventHandlerFn(v0, PhysicsObj_eHit, Glass_PhysicsObjHitHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    AIDetection_eLineOfSightQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Glass_AIDetectionLineOfSightHandler);
  QTask_LinkQTaskEventHandlerFn(v0, NetworkGameItem_eGetGameItemDataQTaskEvent, Glass_GetGameItemDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    NetworkGameItem_eGameItemUpdateQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Glass_GameItemUpdateHandler);
  Symbol_Register(
    "TASKTYPE_GLASS",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)v0,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  v1 = Mem_AllocFn(18444, 4);
  v1[1] = 0;
  *v1 = 0;
  v1[4610] = "TASKTYPE_GLASS";
  Wildcard_CreateNFA("TASKTYPE_GLASS", v1 + 2, (char *)v1 + 10248);
  List_AddTail(v1, (int)&MagicObjConfig_tTaskTypeEnumList);
}

// source: j/0/objects/glass.c:640  [size]
void __cdecl Glass_Close()
{
  QTask_DeleteQTaskType(Glass_eQTaskType);
}

// source: j/0/objects/glass.c:654  [size]
unsigned __int16 __cdecl Glass_GetQTaskType()
{
  return Glass_eQTaskType;
}
