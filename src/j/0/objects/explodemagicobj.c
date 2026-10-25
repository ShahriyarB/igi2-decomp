/* j/0/objects/explodemagicobj.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/objects/explodemagicobj.c:115  [anchor-mhash]
void __cdecl ExplodeMagicObj_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptHead; // eax

  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][RigidMagicObj_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  QTaskList_Register(GameFunctions_ptExplosionQTaskList, (struct QTaskList_s *)ptQTask);
  ptQTask[8].tQTaskChildren.ptHead = *((struct QTask_s **)pxContext + 38);
  ptHead = ptQTask[8].tQTaskChildren.ptHead;
  ptQTask[8].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[8].tQTaskChildren.ptTail = ptHead->tQTaskChildren.ptTail;
  LOBYTE(ptQTask[8].tQTaskRefList.ptMiddle) = 0;
  ptQTask[8].tQTaskRefList.ptHead = ptHead->tQTaskRefList.ptTail;
}

// source: j/0/objects/explodemagicobj.c:157  [anchor-mhash]
void __cdecl ExplodeMagicObj_DeleteHandler(struct QTask_s *ptQTask)
{
  QTaskList_Remove(GameFunctions_ptExplosionQTaskList, ptQTask);
  World_RemoveDynCubeObj((struct World_s *)ptQTask[2].ptParent, (struct DynCubeObj_s *)ptQTask);
}

// source: j/0/objects/explodemagicobj.c:177  [anchor-strings]
void __cdecl ExplodeMagicObj_RunHandler(struct QTask_s *ptQTask)
{
  struct LODVirModel_s *LODVirModelExistsFn; // eax
  struct QTask_s *ptHead; // ecx
  int v3; // edx
  struct QTask_s *v4; // eax
  int v5; // esi
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v7; // edx
  struct QTask_s *v8; // eax
  float vFullRange; // [esp+0h] [ebp-40h]
  float vFallOffRange; // [esp+4h] [ebp-3Ch]

  if ( !LOBYTE(ptQTask[8].tQTaskRefList.ptMiddle)
    && *(float *)&ptQTask[8].tQTaskChildren.ptMiddle >= (double)*(float *)&ptQTask[8].tQTaskChildren.ptTail )
  {
    LODVirModelExistsFn = MTP_GetLODVirModelExistsFn((char *)ptQTask[8].tQTaskChildren.ptHead);
    if ( !LODVirModelExistsFn )
    {
      LDebug_Error("VirModel \"%s\" not available", (char *)ptQTask[8].tQTaskChildren.ptHead);
      abort();
    }
    RigidDynCubeObj_SetLODVirModel((struct RigidDynCubeObj_t *)ptQTask, LODVirModelExistsFn);
    ptHead = ptQTask->tQTaskChildren.ptHead;
    if ( ptHead->ptNext && ptHead )
    {
      v3 = QTask_nProtectedQTaskStackOffset;
      do
      {
        if ( ptHead->ptNext )
          v4 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
        else
          v4 = nullptr;
        v5 = Mesh3D_eChangeModelQTaskEventNoContext;
        QTask_atProtectedQTaskStack[v3].ptQTask = v4;
        pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[v5][ptHead->eQTaskType].pfHandler;
        v7 = v3 + 1;
        QTask_nProtectedQTaskStackOffset = v7;
        if ( pfHandler )
        {
          pfHandler(ptHead);
          v7 = QTask_nProtectedQTaskStackOffset;
        }
        ptHead = (struct QTask_s *)dword_849C7DC[v7];
        v3 = v7 - 1;
        QTask_nProtectedQTaskStackOffset = v3;
      }
      while ( ptHead );
    }
    v8 = ptQTask[8].tQTaskChildren.ptHead;
    vFallOffRange = *(float *)&v8->tQTaskRefList.ptMiddle * 4096.0;
    vFullRange = *(float *)&v8->tQTaskRefList.ptHead * 4096.0;
    Explosion0_New(
      (struct real64x3_t *)&ptQTask[1],
      1,
      0,
      *(float *)&ptQTask[8].tQTaskRefList.ptHead,
      vFullRange,
      vFallOffRange,
      6144.0,
      *(_DWORD *)&v8->eQTaskType,
      (int)v8[1].ptNext,
      nullptr,
      "1009_01_1",
      (char *)&v8[1].ptPrev,
      20,
      0x402u,
      307200.0,
      nullptr,
      nullptr,
      EXPLOSIONDAMAGE_LINEAR_FALLOFF);
    LOBYTE(ptQTask[8].tQTaskRefList.ptMiddle) = 1;
  }
}

// source: j/0/objects/explodemagicobj.c:243  [anchor-mhash]
void __cdecl ExplodeMagicObj_ParseMagicObjParametersHandler(struct QTask_s *ptQTask, void *pxContext)
{
  void *v2; // ebx
  _BYTE *v3; // ebp
  int v4; // esi
  struct ArgList_s *v5; // edi
  struct ArgList_s *v6; // edi
  int v7; // esi
  struct ArgList_s *v8; // edi
  int v9; // esi
  double v10; // st7
  struct ArgList_s *v11; // edi
  int v12; // esi
  void *v13; // eax
  struct ArgList_s *v14; // edi
  int v15; // esi
  void *v16; // eax
  struct ArgList_s *v17; // edi
  int v18; // esi
  double v19; // st7
  struct ArgList_s *v20; // edi
  int v21; // esi
  double v22; // st7
  struct ArgList_s *v23; // edi
  int v24; // esi
  double v25; // st7
  struct ArgList_s *v26; // ebx
  int v27; // esi

  v2 = pxContext;
  v3 = *(_BYTE **)pxContext;
  v4 = *((_DWORD *)pxContext + 2);
  v5 = *((struct ArgList_s **)pxContext + 1);
  if ( v5->isQVM )
  {
    *v3 = 0;
    QVM_EvalArg(v3, 16, v5, v4, 3);
  }
  else
  {
    Expression_EvalString(v5->aptExpression[v4], v3, 16);
  }
  v6 = *((struct ArgList_s **)v2 + 1);
  v7 = v4 + 1;
  if ( v6->isQVM )
  {
    v3[44] = 0;
    QVM_EvalArg(v3 + 44, 16, v6, v7, 3);
  }
  else
  {
    Expression_EvalString(v6->aptExpression[v7], v3 + 44, 16);
  }
  v8 = *((struct ArgList_s **)v2 + 1);
  v9 = v7 + 1;
  if ( v8->isQVM )
  {
    *(float *)&pxContext = 0.0;
    QVM_EvalArg(&pxContext, 4, v8, v9, 2);
    v10 = *(float *)&pxContext;
  }
  else
  {
    v10 = Expression_EvalFloat(v8->aptExpression[v9]);
  }
  *((float *)v3 + 4) = v10;
  v11 = *((struct ArgList_s **)v2 + 1);
  v12 = v9 + 1;
  if ( v11->isQVM )
  {
    *(float *)&pxContext = 0.0;
    QVM_EvalArg(&pxContext, 4, v11, v12, 1);
    v13 = pxContext;
  }
  else
  {
    v13 = (void *)Expression_EvalInt(v11->aptExpression[v12]);
  }
  *((_DWORD *)v3 + 10) = v13;
  v14 = *((struct ArgList_s **)v2 + 1);
  v15 = v12 + 1;
  if ( v14->isQVM )
  {
    *(float *)&pxContext = 0.0;
    QVM_EvalArg(&pxContext, 4, v14, v15, 1);
    v16 = pxContext;
  }
  else
  {
    v16 = (void *)Expression_EvalInt(v14->aptExpression[v15]);
  }
  *((_DWORD *)v3 + 9) = v16;
  v17 = *((struct ArgList_s **)v2 + 1);
  v18 = v15 + 1;
  if ( v17->isQVM )
  {
    *(float *)&pxContext = 0.0;
    QVM_EvalArg(&pxContext, 4, v17, v18, 2);
    v19 = *(float *)&pxContext;
  }
  else
  {
    v19 = Expression_EvalFloat(v17->aptExpression[v18]);
  }
  *((float *)v3 + 8) = v19;
  v20 = *((struct ArgList_s **)v2 + 1);
  v21 = v18 + 1;
  if ( v20->isQVM )
  {
    *(float *)&pxContext = 0.0;
    QVM_EvalArg(&pxContext, 4, v20, v21, 2);
    v22 = *(float *)&pxContext;
  }
  else
  {
    v22 = Expression_EvalFloat(v20->aptExpression[v21]);
  }
  *((float *)v3 + 6) = v22;
  v23 = *((struct ArgList_s **)v2 + 1);
  v24 = v21 + 1;
  if ( v23->isQVM )
  {
    *(float *)&pxContext = 0.0;
    QVM_EvalArg(&pxContext, 4, v23, v24, 2);
    v25 = *(float *)&pxContext;
  }
  else
  {
    v25 = Expression_EvalFloat(v23->aptExpression[v24]);
  }
  *((float *)v3 + 7) = v25;
  v26 = *((struct ArgList_s **)v2 + 1);
  v27 = v24 + 1;
  if ( v26->isQVM )
  {
    *(float *)&pxContext = 0.0;
    QVM_EvalArg(&pxContext, 4, v26, v27, 2);
    *((float *)v3 + 5) = *(float *)&pxContext;
  }
  else
  {
    *((float *)v3 + 5) = Expression_EvalFloat(v26->aptExpression[v27]);
  }
}

// source: j/0/objects/explodemagicobj.c:273  [size]
void __cdecl ExplodeMagicObj_GetMagicObjParameterSizeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = 60;
}

// source: j/0/objects/explodemagicobj.c:289  [size]
void __cdecl ExplodeMagicObj_WeaponHitHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(float *)&ptQTask[8].tQTaskChildren.ptMiddle = *((float *)pxContext + 1)
                                                + *(float *)&ptQTask[8].tQTaskChildren.ptMiddle;
}

// source: j/0/objects/explodemagicobj.c:309  [anchor-mhash]
void __cdecl ExplodeMagicObj_ExplosionHitHandler(struct QTask_s *ptQTask, void *pxContext)
{
  double v2; // st7
  double v3; // st7
  int *v4; // eax
  int v5; // eax
  double v6; // st6
  float ptExplosionHitContext; // [esp+0h] [ebp-Ch]

  if ( !LOBYTE(ptQTask[8].tQTaskRefList.ptMiddle) )
  {
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
    ptExplosionHitContext = v3 * v6;
    *(float *)&ptQTask[8].tQTaskChildren.ptMiddle = GameFunctions_ResolveExplosionHit(
                                                      (struct ExplosionHitContext_t *)pxContext,
                                                      ptQTask,
                                                      (struct real64x3_t *)&ptQTask[1],
                                                      ptExplosionHitContext,
                                                      true)
                                                  + *(float *)&ptQTask[8].tQTaskChildren.ptMiddle;
  }
}

// source: j/0/objects/explodemagicobj.c:388  [anchor-strings]
void __cdecl ExplodeMagicObj_UpdateTagItemsHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // eax
  int v3; // ebx
  struct QTask_s *v4; // edi
  int v5; // ebp
  struct QTask_s *v6; // eax
  char *p_tQTaskRefList; // ecx
  struct QTask_s *v8; // edi
  struct QTask_s *v9; // eax
  char *v10; // ecx
  struct QTask_s *v11; // edi
  struct QTask_s *v12; // eax
  double v13; // st7
  struct QTask_s *v14; // edi
  struct QTask_s *v15; // eax
  double v16; // st7
  struct QTask_s *v17; // edi
  struct QTask_s *v18; // eax
  double v19; // st7
  struct QTask_s *v20; // edi
  struct QTask_s *v21; // eax
  double v22; // st7
  struct QTask_s *v23; // edi
  struct QTask_s *v24; // eax
  double v25; // st7
  struct QTask_s *v26; // edi
  struct QTask_s *v27; // eax
  struct QReference_s *ptHead; // eax
  struct QTask_s *v29; // esi
  struct QTask_s *v30; // eax

  v2 = *(_DWORD *)(*((_DWORD *)pxContext + 1) + 80);
  if ( v2 )
  {
    v3 = *(_DWORD *)((v2 - 4) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v3);
    memset(*(void **)(v3 + 8), 0xCDu, *(_DWORD *)(v3 + 16));
    free((void *)v3);
    *(_DWORD *)(*((_DWORD *)pxContext + 1) + 80) = 0;
  }
  *(_DWORD *)(*((_DWORD *)pxContext + 1) + 80) = Mem_AllocFn(60, 4);
  v4 = *(struct QTask_s **)pxContext;
  v5 = *(_DWORD *)(*((_DWORD *)pxContext + 1) + 80);
  v6 = TagItem_Find(*(struct QTask_s **)pxContext, (char *)&stru_68D5A0.eQTaskType);
  if ( v6 || (v6 = TagItem_NewString16(v4, (char *)&stru_68D5A0.eQTaskType, "603_03_1")) != nullptr )
    p_tQTaskRefList = (char *)&v6[7].tQTaskRefList;
  else
    p_tQTaskRefList = (char *)&g_zInitialValue;
  strcpy((char *)v5, p_tQTaskRefList);
  v8 = *(struct QTask_s **)pxContext;
  v9 = TagItem_Find(*(struct QTask_s **)pxContext, (char *)&stru_68D5A0);
  if ( v9
    || (v9 = TagItem_NewString16(v8, (char *)&stru_68D5A0, (char *)&stru_68D5A0.tQTaskRefList.ptMiddle)) != nullptr )
  {
    v10 = (char *)&v9[7].tQTaskRefList;
  }
  else
  {
    v10 = (char *)&g_zInitialValue;
  }
  strcpy((char *)(v5 + 44), v10);
  v11 = *(struct QTask_s **)pxContext;
  v12 = TagItem_Find(*(struct QTask_s **)pxContext, (char *)&stru_68D54C.eQTaskType);
  if ( v12 || (v12 = TagItem_NewReal32MinMax(v11, (char *)&stru_68D54C.eQTaskType, 3.0, 0.0, 1000.0)) != nullptr )
    v13 = *(float *)&v12[7].tQTaskRefList.ptHead;
  else
    v13 = 0.0;
  *(float *)(v5 + 16) = v13;
  v14 = *(struct QTask_s **)pxContext;
  v15 = TagItem_Find(*(struct QTask_s **)pxContext, (char *)&stru_68D54C);
  if ( v15 || (v15 = TagItem_NewReal32MinMax(v14, (char *)&stru_68D54C, 5.0, 0.0, 1000.0)) != nullptr )
    v16 = *(float *)&v15[7].tQTaskRefList.ptHead;
  else
    v16 = 0.0;
  *(float *)(v5 + 20) = v16;
  v17 = *(struct QTask_s **)pxContext;
  v18 = TagItem_Find(*(struct QTask_s **)pxContext, "EXPLODEMAGICOBJ - Explosion falloff radius");
  if ( v18
    || (v18 = TagItem_NewReal32MinMax(v17, "EXPLODEMAGICOBJ - Explosion falloff radius", 5.0, 0.0, 1000.0)) != nullptr )
  {
    v19 = *(float *)&v18[7].tQTaskRefList.ptHead;
  }
  else
  {
    v19 = 0.0;
  }
  *(float *)(v5 + 24) = v19;
  v20 = *(struct QTask_s **)pxContext;
  v21 = TagItem_Find(*(struct QTask_s **)pxContext, "EXPLODEMAGICOBJ - Explosion damage");
  if ( v21 || (v21 = TagItem_NewReal32MinMax(v20, "EXPLODEMAGICOBJ - Explosion damage", 3.0, 0.0, 1000.0)) != nullptr )
    v22 = *(float *)&v21[7].tQTaskRefList.ptHead;
  else
    v22 = 0.0;
  *(float *)(v5 + 28) = v22;
  v23 = *(struct QTask_s **)pxContext;
  v24 = TagItem_Find(*(struct QTask_s **)pxContext, "EXPLODEMAGICOBJ - Delay");
  if ( v24 || (v24 = TagItem_NewReal32MinMax(v23, "EXPLODEMAGICOBJ - Delay", 0.0, 0.0, 1000.0)) != nullptr )
    v25 = *(float *)&v24[7].tQTaskRefList.ptHead;
  else
    v25 = 0.0;
  *(float *)(v5 + 32) = v25;
  v26 = *(struct QTask_s **)pxContext;
  v27 = TagItem_Find(*(struct QTask_s **)pxContext, (char *)&stru_68D4AC.tQTaskRefList.ptTail);
  if ( v27 || (v27 = TagItem_NewInt32MinMax(v26, (char *)&stru_68D4AC.tQTaskRefList.ptTail, 5, 0, 10)) != nullptr )
    ptHead = v27[7].tQTaskRefList.ptHead;
  else
    ptHead = nullptr;
  *(_DWORD *)(v5 + 36) = ptHead;
  v29 = *(struct QTask_s **)pxContext;
  v30 = TagItem_Find(*(struct QTask_s **)pxContext, (char *)&stru_68D4AC);
  if ( v30 || (v30 = TagItem_NewInt32MinMax(v29, (char *)&stru_68D4AC, 6, 0, 10)) != nullptr )
    *(_DWORD *)(v5 + 40) = v30[7].tQTaskRefList.ptHead;
  else
    *(_DWORD *)(v5 + 40) = 0;
}

// source: j/0/objects/explodemagicobj.c:428  [anchor-strings]
void __cdecl ExplodeMagicObj_Open()
{
  unsigned __int16 v0; // si
  _DWORD *v1; // esi

  v0 = QTask_NewQTaskType("ExplodeMagicObj", 352, RigidMagicObj_eQTaskType, 0, 0);
  ExplodeMagicObj_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 0, ExplodeMagicObj_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, ExplodeMagicObj_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, ExplodeMagicObj_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    MagicObj_eGetParseMagicObjParametersEvent,
    ExplodeMagicObj_ParseMagicObjParametersHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    MagicObj_eGetMagicObjParameterSizeEvent,
    (void (__cdecl *)(struct QTask_s *, void *))ExplodeMagicObj_GetMagicObjParameterSizeHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    GameFunctions_eWeaponHitQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))ExplodeMagicObj_WeaponHitHandler);
  QTask_LinkQTaskEventHandlerFn(v0, GameFunctions_eExplosionHitQTaskEvent, ExplodeMagicObj_ExplosionHitHandler);
  QTask_LinkQTaskEventHandlerFn(v0, MagicObjConfig_eUpdateTagItemsQTaskEvent, ExplodeMagicObj_UpdateTagItemsHandler);
  Symbol_Register(
    "TASKTYPE_EXPLODEMAGICOBJ",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)v0,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  v1 = Mem_AllocFn(18444, 4);
  v1[1] = 0;
  *v1 = 0;
  v1[4610] = "TASKTYPE_EXPLODEMAGICOBJ";
  Wildcard_CreateNFA("TASKTYPE_EXPLODEMAGICOBJ", v1 + 2, (char *)v1 + 10248);
  List_AddTail(v1, (int)&MagicObjConfig_tTaskTypeEnumList);
}

// source: j/0/objects/explodemagicobj.c:465  [size]
void __cdecl ExplodeMagicObj_Close()
{
  QTask_DeleteQTaskType(ExplodeMagicObj_eQTaskType);
}
