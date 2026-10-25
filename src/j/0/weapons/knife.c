/* j/0/weapons/knife.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/weapons/knife.c:78  [anchor-strings]
int __cdecl Knife_Stab(
        struct WeaponFireContext_s *ptWeaponFireContext,
        struct Knife_s *ptKnife,
        float vGamma)
{
  #pragma pack(push, 1)
  union
  {
    struct { _BYTE tTrace[32]; };
    struct { char igi2_o1[32]; struct real32x3_t tDirection; };
    struct { char igi2_o2[44]; struct WeaponCollisionEvaluateContext_t tWeaponCollisionEvaluateContext; };
    struct { char igi2_o3[64]; char azSound[2][32]; };
    struct { char igi2_o4[128]; struct real32x9_t tPos1; };
    struct { char igi2_o5[168]; struct real64x3_t tPos0; };
    struct { char igi2_o6[192]; struct QIntersection_s tIntersection; };
    char igi2_extent[316];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  float vY; // edx
  struct QTask_s *ptWeaponQTask; // eax
  bool v6; // zf
  struct WeaponType_s *ptWeaponType; // ebx
  struct QObj_s *ptHitObj; // edx
  struct QTask_s *v9; // eax
  char *v10; // eax
  void (__cdecl *pfHandler)(struct QObj_s *, _BYTE *); // eax

  memset(&igi2_frame.tWeaponCollisionEvaluateContext, 0, sizeof(igi2_frame.tWeaponCollisionEvaluateContext));
  Real32x9_RotateGamma(&igi2_frame.tPos1, &ptWeaponFireContext->tIn.tOrientation, vGamma);
  *(double *)&igi2_frame.tTrace[8] = igi2_frame.tPos1.tY.vY;
  vY = igi2_frame.tPos1.tX.vY;
  igi2_frame.tDirection.vZ = igi2_frame.tPos1.tZ.vY;
  qmemcpy(&igi2_frame.tPos0, &ptWeaponFireContext->tIn.tPosition, sizeof(igi2_frame.tPos0));
  *(double *)&igi2_frame.tTrace[16] = igi2_frame.tPos1.tZ.vY * 12288.0;
  *(double *)&igi2_frame.tPos1.tX.vX = igi2_frame.tPos0.vX + igi2_frame.tPos1.tX.vY * 12288.0;
  igi2_frame.tDirection.vY = igi2_frame.tPos1.tY.vY;
  *(double *)&igi2_frame.tPos1.tX.vZ = igi2_frame.tPos0.vY + igi2_frame.tPos1.tY.vY * 12288.0;
  igi2_frame.tDirection.vX = vY;
  igi2_frame.tWeaponCollisionEvaluateContext.ptIgnore1QTask = ptWeaponFireContext->tIn.ptIgnoreQTask;
  *(double *)&igi2_frame.tPos1.tY.vY = igi2_frame.tPos0.vZ + *(double *)&igi2_frame.tTrace[16];
  igi2_frame.tWeaponCollisionEvaluateContext.tCollisionEvaluateContext.ptQTask = nullptr;
  igi2_frame.tWeaponCollisionEvaluateContext.vHitProbability = 1.0;
  World_TraceLines(
    Game_ptGame->ptWorld,
    &igi2_frame.tIntersection,
    &igi2_frame.tPos0,
    (struct real64x3_t *)&igi2_frame.tPos1,
    1,
    GameFunctions_eWeaponCollisionEvaluateQTaskEvent,
    &igi2_frame.tWeaponCollisionEvaluateContext.tCollisionEvaluateContext,
    0xFFFFFFFF);
  if ( !igi2_frame.tIntersection.isHit )
    return 0;
  memset(igi2_frame.tTrace, 0, sizeof(igi2_frame.tTrace));
  ptWeaponQTask = ptWeaponFireContext->tIn.ptWeaponQTask;
  v6 = ptWeaponFireContext->tIn.ptWeaponQTask == nullptr;
  *(_DWORD *)igi2_frame.tTrace = &igi2_frame.tIntersection;
  *(_DWORD *)&igi2_frame.tTrace[20] = v6 ? nullptr : ptWeaponQTask->ptParent;
  ptWeaponType = ptWeaponFireContext->tIn.ptWeaponType;
  *(_QWORD *)&igi2_frame.tTrace[8] = *(_QWORD *)&igi2_frame.tDirection.vX;
  *(float *)&igi2_frame.tTrace[4] = ptKnife->vDamageFactor;
  ptHitObj = igi2_frame.tIntersection.ptHitObj;
  *(float *)&igi2_frame.tTrace[16] = igi2_frame.tDirection.vZ;
  *(_DWORD *)&igi2_frame.tTrace[24] = ptWeaponType;
  *(_DWORD *)&igi2_frame.tTrace[28] = 0;
  if ( !igi2_frame.tIntersection.ptHitObj )
    return 0;
  if ( QTask_IsQTaskTypeDerived(igi2_frame.tIntersection.ptHitObj->tQTask.eQTaskType, Human_eQTaskType) )
  {
    if ( ptWeaponType->eWeaponType == WEAPONTYPE_KNIFE )
    {
      v9 = SoundSys_NewSoundFn(Level_ptDynamicQTask, "stab_01");
    }
    else
    {
      strcpy(igi2_frame.azSound[0], "punched_01");
      *(_QWORD *)&igi2_frame.azSound[0][11] = 0;
      *(_QWORD *)&igi2_frame.azSound[1][11] = 0;
      *(_QWORD *)&igi2_frame.azSound[0][19] = 0;
      strcpy(igi2_frame.azSound[1], "punched_02");
      *(_QWORD *)&igi2_frame.azSound[1][19] = 0;
      *(_DWORD *)&igi2_frame.azSound[0][27] = 0;
      igi2_frame.azSound[0][31] = 0;
      *(_DWORD *)&igi2_frame.azSound[1][27] = 0;
      igi2_frame.azSound[1][31] = 0;
      v10 = igi2_frame.azSound[Random_GetRandomNumberBelowLimit(&Game_ptGame->tRunRandomState, 2)];
      v9 = SoundSys_NewSoundFn(Level_ptDynamicQTask, v10);
    }
    goto LABEL_12;
  }
  if ( igi2_frame.tIntersection.ptEnterMaterial )
  {
    v9 = SoundSys_NewSoundFn(Level_ptDynamicQTask, (char *)&igi2_frame.tIntersection.ptEnterMaterial[32].vHardness + 1);
LABEL_12:
    if ( v9 )
      ((void (__cdecl *)(struct QTask_s *, struct real64x3_t *))QTask_aatQTaskFinalEvent[SoundSys_eSetPositionQTaskEvent][v9->eQTaskType].pfHandler)(
        v9,
        &igi2_frame.tIntersection.tPos);
    ptHitObj = igi2_frame.tIntersection.ptHitObj;
  }
  pfHandler = (void (__cdecl *)(struct QObj_s *, _BYTE *))QTask_aatQTaskFinalEvent[GameFunctions_eWeaponHitQTaskEvent][ptHitObj->tQTask.eQTaskType].pfHandler;
  if ( pfHandler )
    pfHandler(ptHitObj, igi2_frame.tTrace);
  return 1;
}

// source: j/0/weapons/knife.c:198  [anchor-strings]
void __cdecl Knife_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int i; // esi
  char *v3; // eax

  ptQTask[1].ptNext = (struct QTask_s *)3;
  ptQTask[1].ptPrev = (struct QTask_s *)1106247680;
  ptQTask[1].tQTaskChildren.ptHead = (struct QTask_s *)1050253722;
  ptQTask[1].tQTaskChildren.ptMiddle = (struct QTask_s *)1056964608;
  for ( i = 0; i < 3; ++i )
  {
    v3 = "fire_knife_1st";
    if ( i )
      v3 = "fire_knife%d_1st";
    sprintf((char *const)&ptQTask[1].tQTaskRefList + 32 * i, v3, i);
  }
  ptQTask[1].tQTaskChildren.ptTail = (struct QTask_s *)i;
  LOBYTE(ptQTask[3].eQTaskType) = 0;
  LOBYTE(ptQTask[4].tQTaskRefList.ptTail) = 0;
}

// source: j/0/weapons/knife.c:227  [anchor-mhash]
void __cdecl Knife_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // eax
  struct QReferenceList_s *p_tQTaskRefList; // ecx

  v2 = 0;
  p_tQTaskRefList = &ptQTask[1].tQTaskRefList;
  do
  {
    if ( !LOBYTE(p_tQTaskRefList->ptHead) )
      break;
    ++v2;
    p_tQTaskRefList = (struct QReferenceList_s *)((char *)p_tQTaskRefList + 32);
  }
  while ( v2 < 3 );
  ptQTask[1].tQTaskChildren.ptTail = (struct QTask_s *)v2;
}

// source: j/0/weapons/knife.c:253  [size]
void __cdecl Knife_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = Knife_ptParameterList;
}

// source: j/0/weapons/knife.c:271  [size]
void __cdecl Knife_CreateWeaponTypeParametersHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *((_DWORD *)pxContext + 2) = QTask_NewFn(*((struct QTask_s **)pxContext + 1), Knife_eQTaskType, nullptr);
}

// source: j/0/weapons/knife.c:290  [anchor-mhash]
void __cdecl Knife_GetAnimHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // eax
  int v3; // ecx
  int v4; // eax
  int v5; // edi
  struct QHashTable_s *v6; // esi
  unsigned int v7; // eax
  int v8; // eax
  int v9; // esi
  int v10; // eax

  v2 = *((_DWORD *)pxContext + 3);
  v3 = *((_DWORD *)pxContext + 5);
  if ( v2 == 4 )
  {
    v4 = dword_752A68;
    if ( dword_752A68 < 0 || dword_752A68 >= (int)(*(_DWORD *)(v3 + 56)) )
    {
      v4 = 0;
      dword_752A68 = 0;
    }
    v5 = 32 * v4 + v3 + 60;
    v6 = Hierarchy_ptHashTable;
    v7 = Hierarchy_ptHashTable->tPrivate.pfHashFunction(
           Hierarchy_ptHashTable->tPrivate.nHashTableSize,
           *(void **)pxContext);
    v8 = ((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Hierarchy_ptHashTable->tPrivate.pfFindElement)(v6, v7, (const void *)(*(void **)pxContext));
    v9 = *(_DWORD *)v8;
    v10 = (*(int (__cdecl **)(_DWORD, int))(*(_DWORD *)v8 + 12))(*(_DWORD *)(*(_DWORD *)v8 + 4), v5);
    *((_DWORD *)pxContext + 6) = (*(int (__cdecl **)(int, int, const void *))(v9 + 28))(v9, v10, (const void *)(v5));
    ++dword_752A68;
  }
  else if ( v2 == 17 )
  {
    *((_DWORD *)pxContext + 6) = Hierarchy_GetAnim(*(unsigned __int8 **)pxContext, (char *)(v3 + 156));
  }
}

// source: j/0/weapons/knife.c:334  [size]
void __cdecl Knife_GetAmmoInfoHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *((_DWORD *)pxContext + 2) = 0;
  *((_DWORD *)pxContext + 3) = 0;
  *((_DWORD *)pxContext + 4) = 1;
  *((_DWORD *)pxContext + 1) = 0;
}

// source: j/0/weapons/knife.c:355  [anchor-caller]
void __cdecl Knife_WeaponFireHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct Knife_s *v3; // esi
  int nTraceLines; // eax
  int v5; // ebx
  double v6; // st7
  char *zFireSound; // eax
  struct QTask_s *v8; // esi
  float vDelta; // [esp+10h] [ebp-Ch]
  float pxContexta = *(float *)&pxContext; // [esp+24h] [ebp+8h] ARGSLOT

  v3 = *((struct Knife_s **)pxContext + 25);
  nTraceLines = v3->nTraceLines;
  v5 = 0;
  vDelta = v3->vTraceFOV / (double)nTraceLines * 0.01745329238474369;
  pxContexta = v3->vTraceFOV * -0.5 * 0.01745329238474369;
  if ( nTraceLines > 0 )
  {
    do
    {
      if ( Knife_Stab((struct WeaponFireContext_s *)pxContext, v3, pxContexta) )
        break;
      ++v5;
      pxContexta = pxContexta + vDelta;
    }
    while ( v5 < v3->nTraceLines );
  }
  *((_DWORD *)pxContext + 28) = 0;
  v6 = v3->vDelay * 30.0;
  *((_DWORD *)pxContext + 32) = 1008981770;
  *((_DWORD *)pxContext + 33) = 1008981770;
  zFireSound = v3->zFireSound;
  v8 = *(struct QTask_s **)pxContext;
  *((_DWORD *)pxContext + 29) = (__int64)v6;
  *((_DWORD *)pxContext + 30) = 1036831949;
  Weapon_PlaySound(v8, 0, zFireSound, false);
}

// source: j/0/weapons/knife.c:406  [size]
unsigned __int16 __cdecl Knife_GetQTaskType()
{
  return Knife_eQTaskType;
}

// source: j/0/weapons/knife.c:419  [anchor-hash]
void __cdecl Knife_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // [esp-1Ch] [ebp-28h]

  v0 = QTask_NewQTaskType("Knife", 220, FireType_eQTaskType, 0, 0);
  Knife_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, Knife_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Knife_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, Knife_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(v0, WeaponType_eCreateParametersQTaskEvent, Knife_CreateWeaponTypeParametersHandler);
  QTask_LinkQTaskEventHandlerFn(v0, WeaponType_eGetAnimQTaskEvent, Knife_GetAnimHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    WeaponType_eGetAmmoInfoQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Knife_GetAmmoInfoHandler);
  QTask_LinkQTaskEventHandlerFn(v0, Weapon_eFireQTaskEvent, Knife_WeaponFireHandler);
  v1 = (struct ParameterList_s *)Mem_AllocFn(192, 4);
  v2 = Level_eParameterTypeInt32;
  v1->nParameters = 0;
  v1->nMaxParameters = 9;
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  Knife_ptParameterList = v1;
  ParameterList_AddParameterMinMax(v1, 0x28u, v2, "Traces", 7u, 1.0, 10.0);
  ParameterList_AddParameterMinMax(
    Knife_ptParameterList,
    0x2Cu,
    Level_eParameterTypeDegrees,
    "Trace FOV",
    7u,
    0.0,
    180.0);
  ParameterList_AddParameter(Knife_ptParameterList, 0x34u, Level_eParameterTypeReal32, "Delay (seconds)", 7u, nullptr);
  ParameterList_AddParameterMinMax(
    Knife_ptParameterList,
    0x30u,
    Level_eParameterTypeDegrees,
    (char *)&stru_691BB8.tQTaskRefList,
    7u,
    0.0,
    10.0);
  ParameterList_AddParameterArray(
    Knife_ptParameterList,
    0x3Cu,
    Level_eParameterTypeString32,
    "1st Fire Anim",
    7u,
    nullptr,
    0x20u,
    3u);
  ParameterList_AddParameter(Knife_ptParameterList, 0x9Cu, Level_eParameterTypeString32, "3rd Fire Anim", 7u, nullptr);
  ParameterList_AddParameter(Knife_ptParameterList, 0xBCu, Level_eParameterTypeString32, "Fire Sound", 7u, nullptr);
  Symbol_Register(
    "TASKTYPE_KNIFE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)Knife_eQTaskType,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}

// source: j/0/weapons/knife.c:508  [size]
void __cdecl Knife_Close()
{
  int v0; // esi

  if ( Knife_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&Knife_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(Knife_eQTaskType);
}
