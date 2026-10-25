/* j/0/vehicles/hitzone.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/vehicles/hitzone.c:88  [anchor-mhash]
struct HitZone_s *__cdecl HitZone_AddSmoke(
        struct HitZone_s *ptHitZone,
        struct real64x3_t *ptPos)
{
  *(float *)&ptHitZone->ptSmoke[8].tQTaskRefList.ptTail = ptHitZone->vDamage
                                                        / ptHitZone->ptHitZoneParameters->vMaxDamage;
  qmemcpy(&ptHitZone->ptSmoke[2].ptParent, ptPos, 0x18u);
  return ptHitZone;
}

// source: j/0/vehicles/hitzone.c:108  [anchor-caller]
void __cdecl HitZone_CreateSmoke(struct HitZone_s *ptHitZone, struct real64x3_t *ptPos)
{
  struct real32x3_t tRGB; // [esp+0h] [ebp-Ch] BYREF

  memset(&tRGB, 0, sizeof(tRGB));
  ptHitZone->ptSmoke = Smoke_New(
                         &ptHitZone->tMagicObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask,
                         ptPos,
                         0.0,
                         0.0,
                         150,
                         0.0,
                         1.0,
                         4.5,
                         6.0,
                         &tRGB,
                         0.5,
                         2.0,
                         SMOKE_MODE_ALPHA,
                         3,
                         0.4000000059604645,
                         2.5,
                         0.10000000149011612,
                         0.30000001192092896,
                         0.0,
                         10.0);
}

// source: j/0/vehicles/hitzone.c:150  [anchor-mhash]
void __cdecl HitZone_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ModelObj_Init((struct ModelObj_s *)ptQTask, *((struct World_s **)pxContext + 1), nullptr);
  ptQTask[7].tQTaskChildren.ptHead = nullptr;
  ptQTask[7].tQTaskChildren.ptMiddle = (struct QTask_s *)2;
  ptQTask[7].tQTaskRefList.ptHead = nullptr;
  ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[7].tQTaskRefList.ptTail = nullptr;
  ptQTask[7].ptParent = nullptr;
  *(_DWORD *)&ptQTask[7].eQTaskType = 0;
}

// source: j/0/vehicles/hitzone.c:217  [size]
void __cdecl HitZone_DeleteHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: j/0/vehicles/hitzone.c:239  [size]
void __cdecl HitZone_RunHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: j/0/vehicles/hitzone.c:295  [size]
void __cdecl HitZone_UpdateMagicObjHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: j/0/vehicles/hitzone.c:354  [anchor-mhash]
void __cdecl HitZone_ParseMagicObjParametersHandler(struct QTask_s *ptQTask, void *pxContext)
{
  void *v2; // esi
  int v3; // ebx
  float *v4; // ebp
  struct ArgList_s *v5; // edi
  double v6; // st7
  struct ArgList_s *v7; // esi
  int v8; // eax

  v2 = pxContext;
  v3 = *((_DWORD *)pxContext + 2);
  v4 = *(float **)pxContext;
  v5 = *((struct ArgList_s **)pxContext + 1);
  if ( v5->isQVM )
  {
    *(float *)&pxContext = 0.0;
    QVM_EvalArg(&pxContext, 4, v5, v3, 2);
    v6 = *(float *)&pxContext;
  }
  else
  {
    v6 = Expression_EvalFloat(v5->aptExpression[v3]);
  }
  *v4 = v6;
  v7 = *((struct ArgList_s **)v2 + 1);
  v8 = v3 + 1;
  if ( v7->isQVM )
  {
    *(float *)&pxContext = 0.0;
    QVM_EvalArg(&pxContext, 4, v7, v8, 2);
    v4[1] = *(float *)&pxContext;
  }
  else
  {
    v4[1] = Expression_EvalFloat(v7->aptExpression[v8]);
  }
}

// source: j/0/vehicles/hitzone.c:377  [size]
void __cdecl HitZone_GetMagicObjParameterSizeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = 8;
}

// source: j/0/vehicles/hitzone.c:393  [anchor-mhash]
void __cdecl HitZone_TraceHitZoneHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)(*(_DWORD *)(*(_DWORD *)pxContext + 36) + 92) = 0;
  *(_DWORD *)(*(_DWORD *)(*(_DWORD *)pxContext + 36) + 84) = 0;
  *(_DWORD *)(*(_DWORD *)(*(_DWORD *)pxContext + 36) + 80) = 0;
}

// source: j/0/vehicles/hitzone.c:434  [size]
void __cdecl HitZone_CollisionEvaluateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_BYTE *)pxContext = 0;
}

// source: j/0/vehicles/hitzone.c:453  [anchor-strings]
void __cdecl HitZone_UpdateTagItemsHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // eax
  int v3; // ebx
  struct QTask_s *v4; // edi
  int v5; // ebp
  struct QTask_s *v6; // eax
  double v7; // st7
  struct QTask_s *v8; // esi
  struct QTask_s *v9; // eax

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
  *(_DWORD *)(*((_DWORD *)pxContext + 1) + 80) = Mem_AllocFn(8, 4);
  v4 = *(struct QTask_s **)pxContext;
  v5 = *(_DWORD *)(*((_DWORD *)pxContext + 1) + 80);
  v6 = TagItem_Find(*(struct QTask_s **)pxContext, (char *)&stru_697310.ptParent);
  if ( v6 || (v6 = TagItem_NewReal32MinMax(v4, (char *)&stru_697310.ptParent, 5.0, 0.0, 100.0)) != nullptr )
    v7 = *(float *)&v6[7].tQTaskRefList.ptHead;
  else
    v7 = 0.0;
  *(float *)v5 = v7;
  v8 = *(struct QTask_s **)pxContext;
  v9 = TagItem_Find(*(struct QTask_s **)pxContext, (char *)&stru_697310);
  if ( v9 || (v9 = TagItem_NewReal32MinMax(v8, (char *)&stru_697310, 0.0, 0.0, 100.0)) != nullptr )
    *(_DWORD *)(v5 + 4) = v9[7].tQTaskRefList.ptHead;
  else
    *(_DWORD *)(v5 + 4) = 0;
}

// source: j/0/vehicles/hitzone.c:486  [anchor-strings]
void __cdecl HitZone_Open()
{
  unsigned __int16 v0; // si
  _DWORD *v1; // esi

  v0 = QTask_NewQTaskType("HitZone", 344, RigidMagicObj_eQTaskType, 0, 0);
  HitZone_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 0, HitZone_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, (void (__cdecl *)(struct QTask_s *))HitZone_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, (void (__cdecl *)(struct QTask_s *))HitZone_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    MagicObj_eUpdateMagicObjEvent,
    (void (__cdecl *)(struct QTask_s *, void *))HitZone_UpdateMagicObjHandler);
  QTask_LinkQTaskEventHandlerFn(v0, GameFunctions_eWeaponHitQTaskEvent, nullptr);
  QTask_LinkQTaskEventHandlerFn(v0, GameFunctions_eExplosionHitQTaskEvent, nullptr);
  QTask_LinkQTaskEventHandlerFn(v0, MagicObj_eGetParseMagicObjParametersEvent, HitZone_ParseMagicObjParametersHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    MagicObj_eGetMagicObjParameterSizeEvent,
    (void (__cdecl *)(struct QTask_s *, void *))HitZone_GetMagicObjParameterSizeHandler);
  QTask_LinkQTaskEventHandlerFn(v0, Vehicle_eTraceHitZoneQTaskEvent, HitZone_TraceHitZoneHandler);
  QTask_LinkQTaskEventHandlerFn(v0, QCube_eGetClosestVertexQTaskEvent, nullptr);
  QTask_LinkQTaskEventHandlerFn(v0, 10, nullptr);
  QTask_LinkQTaskEventHandlerFn(v0, 13, (void (__cdecl *)(struct QTask_s *, void *))HitZone_CollisionEvaluateHandler);
  QTask_LinkQTaskEventHandlerFn(v0, DynCubeObj_eDynCubeObjRemoveQTaskEvent, nullptr);
  QTask_LinkQTaskEventHandlerFn(v0, DynCubeObj_eDynCubeObjRegisterQTaskEvent, nullptr);
  QTask_LinkQTaskEventHandlerFn(v0, MagicObj_eMagicObjEnterEvent, nullptr);
  QTask_LinkQTaskEventHandlerFn(v0, 5, nullptr);
  QTask_LinkQTaskEventHandlerFn(v0, MagicObjConfig_eUpdateTagItemsQTaskEvent, HitZone_UpdateTagItemsHandler);
  Symbol_Register(
    (char *)&stru_6972D4.ptParent,
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)v0,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  v1 = Mem_AllocFn(18444, 4);
  v1[1] = 0;
  *v1 = 0;
  v1[4610] = &stru_6972D4.ptParent;
  Wildcard_CreateNFA(&stru_6972D4.ptParent, v1 + 2, (char *)v1 + 10248);
  List_AddTail(v1, (int)&MagicObjConfig_tTaskTypeEnumList);
}

// source: j/0/vehicles/hitzone.c:534  [size]
void __cdecl HitZone_Close()
{
  QTask_DeleteQTaskType(HitZone_eQTaskType);
}

// source: j/0/vehicles/hitzone.c:548  [size]
unsigned __int16 __cdecl HitZone_GetQTaskType()
{
  return HitZone_eQTaskType;
}
