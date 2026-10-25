/* j/0/vehicles/helidoor.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/vehicles/helidoor.c:100  [size]
void __cdecl HeliDoor_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][RigidMagicObj_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  ptQTask[8].tQTaskChildren.ptHead = *((struct QTask_s **)pxContext + 38);
  LOBYTE(ptQTask[8].tQTaskChildren.ptTail) = 0;
  ptQTask[8].tQTaskChildren.ptMiddle = nullptr;
}

// source: j/0/vehicles/helidoor.c:140  [size]
void __cdecl HeliDoor_DeleteHandler(struct QTask_s *ptQTask)
{
  World_RemoveDynCubeObj((struct World_s *)ptQTask[2].ptParent, (struct DynCubeObj_s *)ptQTask);
}

// source: j/0/vehicles/helidoor.c:160  [size]
void __cdecl HeliDoor_RunHandler(struct QTask_s *ptQTask)
{
  double v1; // st7
  struct QTask_s *ptHead; // edx
  double v3; // st7
  double v4; // st7
  double v5; // st7
  double v6; // st7

  v1 = *(float *)&ptQTask[8].tQTaskChildren.ptMiddle;
  if ( LOBYTE(ptQTask[8].tQTaskChildren.ptTail) )
  {
    ptHead = ptQTask[8].tQTaskChildren.ptHead;
    if ( v1 != *(float *)&ptHead->tQTaskChildren.ptHead )
    {
      if ( *(float *)&ptQTask[8].tQTaskChildren.ptMiddle >= (double)*(float *)&ptHead->tQTaskChildren.ptHead )
      {
        if ( *(float *)&ptQTask[8].tQTaskChildren.ptMiddle > (double)*(float *)&ptHead->tQTaskChildren.ptHead )
        {
          v4 = *(float *)&ptQTask[8].tQTaskChildren.ptMiddle - *(float *)&ptHead->ptPrev;
          *(float *)&ptQTask[8].tQTaskChildren.ptMiddle = v4;
          if ( v4 < *(float *)&ptHead->tQTaskChildren.ptHead )
            ptQTask[8].tQTaskChildren.ptMiddle = ptHead->tQTaskChildren.ptHead;
        }
      }
      else
      {
        v3 = *(float *)&ptHead->ptPrev + *(float *)&ptQTask[8].tQTaskChildren.ptMiddle;
        *(float *)&ptQTask[8].tQTaskChildren.ptMiddle = v3;
        if ( v3 > *(float *)&ptHead->tQTaskChildren.ptHead )
          ptQTask[8].tQTaskChildren.ptMiddle = ptHead->tQTaskChildren.ptHead;
      }
    }
  }
  else if ( v1 != 0.0 )
  {
    if ( *(float *)&ptQTask[8].tQTaskChildren.ptMiddle >= 0.0 )
    {
      if ( *(float *)&ptQTask[8].tQTaskChildren.ptMiddle > 0.0 )
      {
        v6 = *(float *)&ptQTask[8].tQTaskChildren.ptMiddle - *(float *)&ptQTask[8].tQTaskChildren.ptHead->ptPrev;
        *(float *)&ptQTask[8].tQTaskChildren.ptMiddle = v6;
        if ( v6 < 0.0 )
          ptQTask[8].tQTaskChildren.ptMiddle = nullptr;
      }
    }
    else
    {
      v5 = *(float *)&ptQTask[8].tQTaskChildren.ptHead->ptPrev + *(float *)&ptQTask[8].tQTaskChildren.ptMiddle;
      *(float *)&ptQTask[8].tQTaskChildren.ptMiddle = v5;
      if ( v5 > 0.0 )
        ptQTask[8].tQTaskChildren.ptMiddle = nullptr;
    }
  }
}

// source: j/0/vehicles/helidoor.c:195  [size]
void __cdecl HeliDoor_UpdateMagicObjHandler(struct QTask_s *ptQTask, void *pxContext)
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
  struct QTask_s *ptNext; // eax
  double v4; // st6
  double v5; // st5
  float *v6; // eax
  double v7; // st4
  double v8; // st3
  double *v9; // eax
  double v10; // st7
  double v11; // st7
  int *v12; // eax
  int v13; // eax
  double v14; // st6
  int v15; // eax
  int v16; // edx
  double v17; // st7
  double v18; // st6

  v2 = *(float *)&ptQTask[5].ptPrev;
  ptNext = ptQTask[8].tQTaskChildren.ptHead->ptNext;
  v4 = *(float *)&ptQTask[5].tQTaskChildren.ptHead;
  v5 = *(float *)&ptQTask[5].tQTaskChildren.ptMiddle;
  if ( ptNext )
  {
    if ( ptNext == (struct QTask_s *)1 )
    {
      v4 = v4 + *(float *)&ptQTask[8].tQTaskChildren.ptMiddle;
    }
    else if ( ptNext == (struct QTask_s *)2 )
    {
      v5 = v5 + *(float *)&ptQTask[8].tQTaskChildren.ptMiddle;
    }
  }
  else
  {
    v2 = v2 + *(float *)&ptQTask[8].tQTaskChildren.ptMiddle;
  }
  v6 = *((float **)pxContext + 1);
  *(double *)igi2_frame.Real64x3_Rotate_tTemp = v6[2] * v5 + v6[1] * v4 + *v6 * v2;
  *(double *)&igi2_frame.Real64x3_Rotate_tTemp[8] = v6[5] * v5 + v6[4] * v4 + v6[3] * v2;
  v7 = v6[8] * v5 + v6[7] * v4;
  v8 = v6[6];
  v9 = *(double **)pxContext;
  *(double *)&igi2_frame.Real64x3_Rotate_tTemp[16] = v7 + v8 * v2;
  qmemcpy(&igi2_frame.tNewPos, igi2_frame.Real64x3_Rotate_tTemp, sizeof(igi2_frame.tNewPos));
  igi2_frame.tNewPos.vX = *(double *)igi2_frame.Real64x3_Rotate_tTemp + *v9;
  igi2_frame.tNewPos.vY = igi2_frame.tNewPos.vY + v9[1];
  igi2_frame.tNewPos.vZ = igi2_frame.tNewPos.vZ + v9[2];
  if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
    v10 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  else
    v10 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  if ( v10 >= *(float *)&ptQTask[6].ptPrev )
  {
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
      v11 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v11 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  }
  else
  {
    v11 = *(float *)&ptQTask[6].ptPrev;
  }
  v12 = *(int **)&ptQTask[2].eQTaskType;
  if ( v12 && (v13 = *v12) != 0 )
    v14 = *(float *)(*(_DWORD *)(*(_DWORD *)(v13 + 12) + 12) + 120);
  else
    v14 = 1.0;
  igi2_frame.ptDynCubeObj = v14 * v11;
  World_MoveDynCubeObjRadius(Game_ptGame->ptWorld, (struct DynCubeObj_s *)ptQTask, &igi2_frame.tNewPos, igi2_frame.ptDynCubeObj);
  v15 = *((_DWORD *)pxContext + 1);
  *(float *)igi2_frame.Real64x3_Rotate_tTemp = *(float *)(v15 + 8) * *(float *)&ptQTask[4].tQTaskRefList.ptTail
                                  + *(float *)v15 * *(float *)&ptQTask[4].ptPrev
                                  + *(float *)(v15 + 4) * *(float *)&ptQTask[4].tQTaskChildren.ptTail;
  *(float *)&igi2_frame.Real64x3_Rotate_tTemp[4] = *(float *)(v15 + 8) * *(float *)&ptQTask[4].ptParent
                                      + *(float *)v15 * *(float *)&ptQTask[4].tQTaskChildren.ptHead
                                      + *(float *)(v15 + 4) * *(float *)&ptQTask[4].tQTaskRefList.ptHead;
  *(float *)&igi2_frame.Real64x3_Rotate_tTemp[8] = *(float *)(v15 + 8) * *(float *)&ptQTask[4].eQTaskType
                                      + *(float *)v15 * *(float *)&ptQTask[4].tQTaskChildren.ptMiddle
                                      + *(float *)(v15 + 4) * *(float *)&ptQTask[4].tQTaskRefList.ptMiddle;
  *(float *)&igi2_frame.Real64x3_Rotate_tTemp[12] = *(float *)(v15 + 20) * *(float *)&ptQTask[4].tQTaskRefList.ptTail
                                       + *(float *)(v15 + 12) * *(float *)&ptQTask[4].ptPrev
                                       + *(float *)(v15 + 16) * *(float *)&ptQTask[4].tQTaskChildren.ptTail;
  *(float *)&igi2_frame.Real64x3_Rotate_tTemp[16] = *(float *)(v15 + 20) * *(float *)&ptQTask[4].ptParent
                                       + *(float *)(v15 + 12) * *(float *)&ptQTask[4].tQTaskChildren.ptHead
                                       + *(float *)(v15 + 16) * *(float *)&ptQTask[4].tQTaskRefList.ptHead;
  *(float *)&igi2_frame.Real64x3_Rotate_tTemp[20] = *(float *)(v15 + 20) * *(float *)&ptQTask[4].eQTaskType
                                       + *(float *)(v15 + 12) * *(float *)&ptQTask[4].tQTaskChildren.ptMiddle
                                       + *(float *)(v15 + 16) * *(float *)&ptQTask[4].tQTaskRefList.ptMiddle;
  *(float *)&igi2_frame.Real64x3_Rotate_tTemp[24] = *(float *)(v15 + 32) * *(float *)&ptQTask[4].tQTaskRefList.ptTail
                                       + *(float *)(v15 + 24) * *(float *)&ptQTask[4].ptPrev
                                       + *(float *)(v15 + 28) * *(float *)&ptQTask[4].tQTaskChildren.ptTail;
  v16 = *(_DWORD *)(v15 + 36);
  *(float *)&igi2_frame.Real64x3_Rotate_tTemp[28] = *(float *)(v15 + 32) * *(float *)&ptQTask[4].ptParent
                                       + *(float *)(v15 + 24) * *(float *)&ptQTask[4].tQTaskChildren.ptHead
                                       + *(float *)(v15 + 28) * *(float *)&ptQTask[4].tQTaskRefList.ptHead;
  v17 = *(float *)(v15 + 32) * *(float *)&ptQTask[4].eQTaskType
      + *(float *)(v15 + 24) * *(float *)&ptQTask[4].tQTaskChildren.ptMiddle;
  v18 = *(float *)(v15 + 28) * *(float *)&ptQTask[4].tQTaskRefList.ptMiddle;
  *(_DWORD *)&igi2_frame.Real64x3_Rotate_tTemp[36] = (char *)&ptQTask[5].ptNext->ptNext + v16 + 1;
  *(float *)&igi2_frame.Real64x3_Rotate_tTemp[32] = v17 + v18;
  qmemcpy(&ptQTask[3].ptPrev, igi2_frame.Real64x3_Rotate_tTemp, sizeof(struct QTask_s));
}

// source: j/0/vehicles/helidoor.c:266  [anchor-mhash]
void __cdecl HeliDoor_ParseMagicObjParametersHandler(struct QTask_s *ptQTask, void *pxContext)
{
  void *v2; // ebx
  int v3; // ebp
  int v4; // esi
  struct ArgList_s *v5; // edi
  void *v6; // eax
  struct ArgList_s *v7; // edi
  int v8; // esi
  double v9; // st7
  int v10; // eax
  struct ArgList_s *v11; // edi

  v2 = pxContext;
  v3 = *(_DWORD *)pxContext;
  v4 = *((_DWORD *)pxContext + 2);
  v5 = *((struct ArgList_s **)pxContext + 1);
  if ( v5->isQVM )
  {
    *(float *)&pxContext = 0.0;
    QVM_EvalArg(&pxContext, 4, v5, v4, 1);
    v6 = pxContext;
  }
  else
  {
    v6 = (void *)Expression_EvalInt(v5->aptExpression[v4]);
  }
  *(_DWORD *)v3 = v6;
  v7 = *((struct ArgList_s **)v2 + 1);
  v8 = v4 + 1;
  if ( v7->isQVM )
  {
    *(float *)&pxContext = 0.0;
    QVM_EvalArg(&pxContext, 4, v7, v8, 2);
    v9 = *(float *)&pxContext;
  }
  else
  {
    v9 = Expression_EvalFloat(v7->aptExpression[v8]);
  }
  v10 = v8 + 1;
  *(float *)(v3 + 4) = v9 * 136.53334045410156;
  v11 = *((struct ArgList_s **)v2 + 1);
  if ( v11->isQVM )
  {
    *(float *)&pxContext = 0.0;
    QVM_EvalArg(&pxContext, 4, v11, v10, 2);
    *(float *)(v3 + 8) = *(float *)&pxContext * 4096.0;
  }
  else
  {
    *(float *)(v3 + 8) = Expression_EvalFloat(v11->aptExpression[v10]) * 4096.0;
  }
}

// source: j/0/vehicles/helidoor.c:290  [size]
void __cdecl HeliDoor_GetMagicObjParameterSizeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = 12;
}

// source: j/0/vehicles/helidoor.c:306  [size]
void __cdecl HeliDoor_WeaponHitHandler(struct QTask_s *ptQTask, void *pxContext)
{
  void (__cdecl *pfHandler)(struct QTask_s *, ...); // ecx

  pfHandler = (void (__cdecl *)(struct QTask_s *, ...))QTask_aatQTaskFinalEvent[GameFunctions_eWeaponHitQTaskEvent][ptQTask[8].ptNext->eQTaskType].pfHandler;
  if ( pfHandler )
    pfHandler(ptQTask[8].ptNext, pxContext);
}

// source: j/0/vehicles/helidoor.c:335  [size]
void __cdecl HeliDoor_AILineOfSightHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v2; // eax

  v2 = *((struct QTask_s **)pxContext + 2);
  *(_BYTE *)pxContext = v2 != ptQTask && *((struct QTask_s **)pxContext + 3) != ptQTask && ptQTask[8].ptNext != v2;
}

// source: j/0/vehicles/helidoor.c:364  [anchor-strings]
void __cdecl HeliDoor_UpdateTagItemsHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // eax
  int v3; // ebx
  struct QTask_s *v4; // edi
  int v5; // ebp
  struct QTask_s *v6; // eax
  char *v7; // ecx
  char v8; // dl
  struct QTask_s *v9; // edi
  struct QTask_s *v10; // eax
  double v11; // st7
  struct QTask_s *v12; // esi
  struct QTask_s *v13; // eax

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
  *(_DWORD *)(*((_DWORD *)pxContext + 1) + 80) = Mem_AllocFn(12, 4);
  v4 = *(struct QTask_s **)pxContext;
  v5 = *(_DWORD *)(*((_DWORD *)pxContext + 1) + 80);
  v6 = TagItem_Find(*(struct QTask_s **)pxContext, "HELIDOOR - Movement axis");
  if ( !v6 )
  {
    v6 = QTask_NewFn(v4, TagItem_eInt32QTaskType, nullptr);
    v7 = "HELIDOOR - Movement axis";
    do
    {
      v8 = *v7;
      v7[(char *)v6 - "HELIDOOR - Movement axis" + 40] = *v7;
      ++v7;
    }
    while ( v8 );
    v6[7].tQTaskRefList.ptHead = nullptr;
  }
  *(_DWORD *)v5 = v6[7].tQTaskRefList.ptHead;
  v9 = *(struct QTask_s **)pxContext;
  v10 = TagItem_Find(*(struct QTask_s **)pxContext, (char *)&stru_69432C.eQTaskType);
  if ( v10
    || (v10 = TagItem_NewReal32MinMax(v9, (char *)&stru_69432C.eQTaskType, 0.6000000238418579, 0.0, 100.0)) != nullptr )
  {
    v11 = *(float *)&v10[7].tQTaskRefList.ptHead;
  }
  else
  {
    v11 = 0.0;
  }
  *(float *)(v5 + 4) = v11;
  v12 = *(struct QTask_s **)pxContext;
  v13 = TagItem_Find(*(struct QTask_s **)pxContext, (char *)&stru_69432C);
  if ( v13 || (v13 = TagItem_NewReal32MinMax(v12, (char *)&stru_69432C, 2.6500000953674316, 0.0, 100.0)) != nullptr )
    *(_DWORD *)(v5 + 8) = v13[7].tQTaskRefList.ptHead;
  else
    *(_DWORD *)(v5 + 8) = 0;
}

// source: j/0/vehicles/helidoor.c:398  [size]
unsigned __int16 __cdecl HeliDoor_GetQTaskType()
{
  return HeliDoor_eQTaskType;
}

// source: j/0/vehicles/helidoor.c:411  [size]
void __cdecl HeliDoor_SetOpen(struct QTask_s *ptQTask, int isOpen)
{
  LOBYTE(ptQTask[8].tQTaskChildren.ptTail) = isOpen;
}

// source: j/0/vehicles/helidoor.c:429  [anchor-strings]
void __cdecl HeliDoor_Open()
{
  unsigned __int16 v0; // si
  _DWORD *v1; // esi
  _DWORD *v2; // esi
  _DWORD *v3; // esi
  _DWORD *v4; // esi

  v0 = QTask_NewQTaskType("HeliDoor", 344, RigidMagicObj_eQTaskType, 0, 0);
  HeliDoor_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 0, HeliDoor_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, HeliDoor_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, HeliDoor_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v0, MagicObj_eUpdateMagicObjEvent, HeliDoor_UpdateMagicObjHandler);
  QTask_LinkQTaskEventHandlerFn(v0, GameFunctions_eWeaponHitQTaskEvent, HeliDoor_WeaponHitHandler);
  QTask_LinkQTaskEventHandlerFn(v0, GameFunctions_eExplosionHitQTaskEvent, nullptr);
  QTask_LinkQTaskEventHandlerFn(v0, MagicObj_eGetParseMagicObjParametersEvent, HeliDoor_ParseMagicObjParametersHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    MagicObj_eGetMagicObjParameterSizeEvent,
    (void (__cdecl *)(struct QTask_s *, void *))HeliDoor_GetMagicObjParameterSizeHandler);
  QTask_LinkQTaskEventHandlerFn(v0, AIDetection_eLineOfSightQTaskEvent, HeliDoor_AILineOfSightHandler);
  QTask_LinkQTaskEventHandlerFn(v0, MagicObjConfig_eUpdateTagItemsQTaskEvent, HeliDoor_UpdateTagItemsHandler);
  Symbol_Register(
    "TASKTYPE_HELIDOOR",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)v0,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  v1 = Mem_AllocFn(18444, 4);
  v1[1] = 0;
  *v1 = 0;
  v1[4610] = "TASKTYPE_HELIDOOR";
  Wildcard_CreateNFA("TASKTYPE_HELIDOOR", v1 + 2, (char *)v1 + 10248);
  List_AddTail(v1, (int)&MagicObjConfig_tTaskTypeEnumList);
  Symbol_Register(
    "HELIDOOR_AXIS_X",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    nullptr,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "HELIDOOR_AXIS_Y",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)1,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "HELIDOOR_AXIS_Z",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)2,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  HeliDoor_tAxisEnumList.pfEnumItemsCallback = ParameterEnumList_EnumerateItemsCallback;
  HeliDoor_tAxisEnumList.ptHead = (struct ParameterEnumItem_s *)&HeliDoor_tAxisEnumList.ptMiddle;
  HeliDoor_tAxisEnumList.ptTail = (struct ParameterEnumItem_s *)&HeliDoor_tAxisEnumList;
  HeliDoor_tAxisEnumList.ptMiddle = nullptr;
  v2 = Mem_AllocFn(18444, 4);
  v2[1] = 0;
  *v2 = 0;
  v2[4610] = "HELIDOOR_AXIS_X";
  Wildcard_CreateNFA("HELIDOOR_AXIS_X", v2 + 2, (char *)v2 + 10248);
  List_AddTail(v2, (int)&HeliDoor_tAxisEnumList);
  v3 = Mem_AllocFn(18444, 4);
  v3[1] = 0;
  *v3 = 0;
  v3[4610] = "HELIDOOR_AXIS_Y";
  Wildcard_CreateNFA("HELIDOOR_AXIS_Y", v3 + 2, (char *)v3 + 10248);
  List_AddTail(v3, (int)&HeliDoor_tAxisEnumList);
  v4 = Mem_AllocFn(18444, 4);
  v4[1] = 0;
  *v4 = 0;
  v4[4610] = "HELIDOOR_AXIS_Z";
  Wildcard_CreateNFA("HELIDOOR_AXIS_Z", v4 + 2, (char *)v4 + 10248);
  List_AddTail(v4, (int)&HeliDoor_tAxisEnumList);
}

// source: j/0/vehicles/helidoor.c:475  [size]
void __cdecl HeliDoor_Close()
{
  ParameterEnumList_DeAlloc(&HeliDoor_tAxisEnumList);
  QTask_DeleteQTaskType(HeliDoor_eQTaskType);
}
