/* j/0/vehicles/heliwheel.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/vehicles/heliwheel.c:38  [size]
void __cdecl HeliWheel_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][RigidMagicObj_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  ptQTask[8].tQTaskChildren.ptHead = *((struct QTask_s **)pxContext + 38);
}

// source: j/0/vehicles/heliwheel.c:74  [size]
void __cdecl HeliWheel_DeleteHandler(struct QTask_s *ptQTask)
{
  World_RemoveDynCubeObj((struct World_s *)ptQTask[2].ptParent, (struct DynCubeObj_s *)ptQTask);
}

// source: j/0/vehicles/heliwheel.c:94  [size]
void __cdecl HeliWheel_RunHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: j/0/vehicles/heliwheel.c:106  [size]
void __cdecl HeliWheel_UpdateMagicObjHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[20]; struct real64x3_t tNewPos; };
    struct { char igi2_o2[44]; _BYTE Real64x3_Rotate_tTemp[40]; };
    char igi2_extent[88];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v2; // st7
  double v3; // st6
  float *v4; // eax
  double v5; // st5
  double v6; // st4
  double v7; // st3
  double *v8; // eax
  double v9; // st7
  double v10; // st7
  int *v11; // eax
  int v12; // eax
  double v13; // st6
  int v14; // eax
  int v15; // ecx
  struct QTask_s *ptNext; // edx
  double v17; // st7
  double v18; // st6

  v2 = *(float *)&ptQTask[5].ptPrev;
  v3 = *(float *)&ptQTask[5].tQTaskChildren.ptHead;
  v4 = *((float **)pxContext + 1);
  v5 = *(float *)&ptQTask[5].tQTaskChildren.ptMiddle;
  *(double *)igi2_frame.Real64x3_Rotate_tTemp = v4[2] * v5 + v4[1] * v3 + *v4 * v2;
  *(double *)&igi2_frame.Real64x3_Rotate_tTemp[8] = v4[5] * v5 + v4[4] * v3 + v4[3] * v2;
  v6 = v4[8] * v5 + v4[7] * v3;
  v7 = v4[6];
  v8 = *(double **)pxContext;
  *(double *)&igi2_frame.Real64x3_Rotate_tTemp[16] = v6 + v7 * v2;
  qmemcpy(&igi2_frame.tNewPos, igi2_frame.Real64x3_Rotate_tTemp, sizeof(igi2_frame.tNewPos));
  igi2_frame.tNewPos.vX = *(double *)igi2_frame.Real64x3_Rotate_tTemp + *v8;
  igi2_frame.tNewPos.vY = igi2_frame.tNewPos.vY + v8[1];
  igi2_frame.tNewPos.vZ = igi2_frame.tNewPos.vZ + v8[2];
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
  igi2_frame.ptDynCubeObj = v13 * v10;
  World_MoveDynCubeObjRadius(Game_ptGame->ptWorld, (struct DynCubeObj_s *)ptQTask, &igi2_frame.tNewPos, igi2_frame.ptDynCubeObj);
  v14 = *((_DWORD *)pxContext + 1);
  *(float *)igi2_frame.Real64x3_Rotate_tTemp = *(float *)&ptQTask[4].tQTaskRefList.ptTail * *(float *)(v14 + 8)
                                  + *(float *)&ptQTask[4].ptPrev * *(float *)v14
                                  + *(float *)(v14 + 4) * *(float *)&ptQTask[4].tQTaskChildren.ptTail;
  *(float *)&igi2_frame.Real64x3_Rotate_tTemp[4] = *(float *)&ptQTask[4].ptParent * *(float *)(v14 + 8)
                                      + *(float *)&ptQTask[4].tQTaskChildren.ptHead * *(float *)v14
                                      + *(float *)(v14 + 4) * *(float *)&ptQTask[4].tQTaskRefList.ptHead;
  *(float *)&igi2_frame.Real64x3_Rotate_tTemp[8] = *(float *)&ptQTask[4].eQTaskType * *(float *)(v14 + 8)
                                      + *(float *)&ptQTask[4].tQTaskChildren.ptMiddle * *(float *)v14
                                      + *(float *)(v14 + 4) * *(float *)&ptQTask[4].tQTaskRefList.ptMiddle;
  *(float *)&igi2_frame.Real64x3_Rotate_tTemp[12] = *(float *)(v14 + 20) * *(float *)&ptQTask[4].tQTaskRefList.ptTail
                                       + *(float *)(v14 + 12) * *(float *)&ptQTask[4].ptPrev
                                       + *(float *)&ptQTask[4].tQTaskChildren.ptTail * *(float *)(v14 + 16);
  *(float *)&igi2_frame.Real64x3_Rotate_tTemp[16] = *(float *)(v14 + 20) * *(float *)&ptQTask[4].ptParent
                                       + *(float *)(v14 + 12) * *(float *)&ptQTask[4].tQTaskChildren.ptHead
                                       + *(float *)&ptQTask[4].tQTaskRefList.ptHead * *(float *)(v14 + 16);
  *(float *)&igi2_frame.Real64x3_Rotate_tTemp[20] = *(float *)(v14 + 20) * *(float *)&ptQTask[4].eQTaskType
                                       + *(float *)(v14 + 12) * *(float *)&ptQTask[4].tQTaskChildren.ptMiddle
                                       + *(float *)&ptQTask[4].tQTaskRefList.ptMiddle * *(float *)(v14 + 16);
  *(float *)&igi2_frame.Real64x3_Rotate_tTemp[24] = *(float *)(v14 + 32) * *(float *)&ptQTask[4].tQTaskRefList.ptTail
                                       + *(float *)(v14 + 24) * *(float *)&ptQTask[4].ptPrev
                                       + *(float *)&ptQTask[4].tQTaskChildren.ptTail * *(float *)(v14 + 28);
  v15 = *(_DWORD *)(v14 + 36);
  ptNext = ptQTask[5].ptNext;
  *(float *)&igi2_frame.Real64x3_Rotate_tTemp[28] = *(float *)(v14 + 32) * *(float *)&ptQTask[4].ptParent
                                       + *(float *)(v14 + 24) * *(float *)&ptQTask[4].tQTaskChildren.ptHead
                                       + *(float *)&ptQTask[4].tQTaskRefList.ptHead * *(float *)(v14 + 28);
  v17 = *(float *)(v14 + 32) * *(float *)&ptQTask[4].eQTaskType
      + *(float *)(v14 + 24) * *(float *)&ptQTask[4].tQTaskChildren.ptMiddle;
  v18 = *(float *)&ptQTask[4].tQTaskRefList.ptMiddle * *(float *)(v14 + 28);
  *(_DWORD *)&igi2_frame.Real64x3_Rotate_tTemp[36] = (char *)&ptNext->ptNext + v15 + 1;
  *(float *)&igi2_frame.Real64x3_Rotate_tTemp[32] = v17 + v18;
  qmemcpy(&ptQTask[3].ptPrev, igi2_frame.Real64x3_Rotate_tTemp, sizeof(struct QTask_s));
}

// source: j/0/vehicles/heliwheel.c:160  [size]
void __cdecl HeliWheel_WeaponHitHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: j/0/vehicles/heliwheel.c:177  [size]
void __cdecl HeliWheel_ExplosionHitHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: j/0/vehicles/heliwheel.c:195  [anchor-mhash]
void __cdecl HeliWheel_ParseMagicObjParametersHandler(struct QTask_s *ptQTask, void *pxContext)
{
  void *v2; // esi
  int v3; // ebx
  float *v4; // ebp
  struct ArgList_s *v5; // edi
  double v6; // st7
  int v7; // eax
  struct ArgList_s *v8; // esi

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
  v7 = v3 + 1;
  v4[1] = v6 * 4096.0;
  v8 = *((struct ArgList_s **)v2 + 1);
  if ( v8->isQVM )
  {
    *(float *)&pxContext = 0.0;
    QVM_EvalArg(&pxContext, 4, v8, v7, 2);
    *v4 = *(float *)&pxContext * 4096.0;
  }
  else
  {
    *v4 = Expression_EvalFloat(v8->aptExpression[v7]) * 4096.0;
  }
}

// source: j/0/vehicles/heliwheel.c:218  [size]
void __cdecl HeliWheel_GetMagicObjParameterSizeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = 8;
}

// source: j/0/vehicles/heliwheel.c:234  [anchor-strings]
void __cdecl HeliWheel_UpdateTagItemsHandler(struct QTask_s *ptQTask, void *pxContext)
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
  v6 = TagItem_Find(*(struct QTask_s **)pxContext, (char *)&stru_691734.ptParent);
  if ( v6 || (v6 = TagItem_NewReal32MinMax(v4, (char *)&stru_691734.ptParent, 0.15000000596046448, 0.0, 20.0)) != nullptr )
    v7 = *(float *)&v6[7].tQTaskRefList.ptHead;
  else
    v7 = 0.0;
  *(float *)(v5 + 4) = v7;
  v8 = *(struct QTask_s **)pxContext;
  v9 = TagItem_Find(*(struct QTask_s **)pxContext, (char *)&stru_691734);
  if ( v9 || (v9 = TagItem_NewReal32MinMax(v8, (char *)&stru_691734, 0.30000001192092896, 0.0, 20.0)) != nullptr )
    *(_DWORD *)v5 = v9[7].tQTaskRefList.ptHead;
  else
    *(_DWORD *)v5 = 0;
}

// source: j/0/vehicles/heliwheel.c:267  [anchor-strings]
void __cdecl HeliWheel_Open()
{
  unsigned __int16 v0; // si
  _DWORD *v1; // esi

  v0 = QTask_NewQTaskType("HeliWheel", 336, RigidMagicObj_eQTaskType, 0, 0);
  HeliWheel_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 0, HeliWheel_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, (void (__cdecl *)(struct QTask_s *))HeliWheel_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, HeliWheel_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v0, MagicObj_eUpdateMagicObjEvent, HeliWheel_UpdateMagicObjHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    GameFunctions_eWeaponHitQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))HeliWheel_WeaponHitHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    GameFunctions_eExplosionHitQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))HeliWheel_ExplosionHitHandler);
  QTask_LinkQTaskEventHandlerFn(v0, MagicObj_eGetParseMagicObjParametersEvent, HeliWheel_ParseMagicObjParametersHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    MagicObj_eGetMagicObjParameterSizeEvent,
    (void (__cdecl *)(struct QTask_s *, void *))HeliWheel_GetMagicObjParameterSizeHandler);
  QTask_LinkQTaskEventHandlerFn(v0, MagicObjConfig_eUpdateTagItemsQTaskEvent, HeliWheel_UpdateTagItemsHandler);
  Symbol_Register(
    "TASKTYPE_HELIWHEEL",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)v0,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  v1 = Mem_AllocFn(18444, 4);
  v1[1] = 0;
  *v1 = 0;
  v1[4610] = "TASKTYPE_HELIWHEEL";
  Wildcard_CreateNFA("TASKTYPE_HELIWHEEL", v1 + 2, (char *)v1 + 10248);
  List_AddTail(v1, (int)&MagicObjConfig_tTaskTypeEnumList);
}

// source: j/0/vehicles/heliwheel.c:304  [size]
void __cdecl HeliWheel_Close()
{
  QTask_DeleteQTaskType(HeliWheel_eQTaskType);
}

// source: j/0/vehicles/heliwheel.c:318  [size]
unsigned __int16 __cdecl HeliWheel_GetQTaskType()
{
  return HeliWheel_eQTaskType;
}
