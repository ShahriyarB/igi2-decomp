/* j/0/vehicles/cardoor.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/vehicles/cardoor.c:92  [size]
void __cdecl CarDoor_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][RigidMagicObj_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  ptQTask[8].tQTaskChildren.ptHead = *((struct QTask_s **)pxContext + 38);
  LOBYTE(ptQTask[8].tQTaskChildren.ptTail) = 0;
  ptQTask[8].tQTaskChildren.ptMiddle = nullptr;
}

// source: j/0/vehicles/cardoor.c:129  [size]
void __cdecl CarDoor_DeleteHandler(struct QTask_s *ptQTask)
{
  World_RemoveDynCubeObj((struct World_s *)ptQTask[2].ptParent, (struct DynCubeObj_s *)ptQTask);
}

// source: j/0/vehicles/cardoor.c:149  [size]
void __cdecl CarDoor_RunHandler(struct QTask_s *ptQTask)
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

// source: j/0/vehicles/cardoor.c:181  [size]
void __cdecl CarDoor_UpdateMagicObjHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[20]; struct real64x3_t tNewPos; };
    struct { char igi2_o2[48]; float v28; };
    struct { char igi2_o3[52]; float v29; };
    struct { char igi2_o4[60]; struct real32x9_t tNewOrientation; };
    char igi2_extent[104];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v3; // st7
  double v4; // st6
  float *v5; // eax
  double v6; // st5
  double v7; // st4
  double v8; // st3
  double *v9; // eax
  double v10; // st7
  double v11; // st7
  int *v12; // eax
  int v13; // eax
  double v14; // st6
  struct QTask_s *ptNext; // eax
  long double v16; // st7
  long double v17; // st7
  double v18; // st7
  double v19; // st6
  double v20; // st5
  double v21; // st4
  char *v22; // ecx
  int v23; // eax
  double v24; // st7
  double v25; // st6
  struct QTask_s *ptQTaska = *(struct QTask_s * *)&ptQTask; // [esp+6Ch] [ebp+4h] ARGSLOT
  float ptQTaskb = *(float *)&ptQTask; // [esp+6Ch] [ebp+4h] ARGSLOT

  v3 = *(float *)&ptQTask[5].ptPrev;
  v4 = *(float *)&ptQTask[5].tQTaskChildren.ptHead;
  v5 = *((float **)pxContext + 1);
  v6 = *(float *)&ptQTask[5].tQTaskChildren.ptMiddle;
  *(double *)&igi2_frame.tNewOrientation.tX.vX = v5[2] * v6 + v5[1] * v4 + *v5 * v3;
  *(double *)&igi2_frame.tNewOrientation.tX.vZ = v5[5] * v6 + v5[4] * v4 + v5[3] * v3;
  v7 = v5[8] * v6 + v5[7] * v4;
  v8 = v5[6];
  v9 = *(double **)pxContext;
  *(double *)&igi2_frame.tNewOrientation.tY.vY = v7 + v8 * v3;
  qmemcpy(&igi2_frame.tNewPos, &igi2_frame.tNewOrientation, sizeof(igi2_frame.tNewPos));
  igi2_frame.tNewPos.vX = *(double *)&igi2_frame.tNewOrientation.tX.vX + *v9;
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
  ptNext = ptQTask[8].tQTaskChildren.ptHead->ptNext;
  if ( ptNext )
  {
    if ( ptNext == (struct QTask_s *)1 )
    {
      v17 = *(float *)&ptQTask[8].tQTaskChildren.ptMiddle;
      igi2_frame.tNewOrientation.tX.vY = 0.0;
      igi2_frame.tNewOrientation.tY.vX = 0.0;
      igi2_frame.tNewOrientation.tY.vY = 1.0;
      igi2_frame.tNewOrientation.tY.vZ = 0.0;
      igi2_frame.tNewOrientation.tZ.vY = 0.0;
      ptQTaskb = sin(v17);
      igi2_frame.tNewOrientation.tX.vZ = ptQTaskb;
      ptNext = nullptr;
      igi2_frame.tNewOrientation.tX.vX = cos(v17);
      igi2_frame.tNewOrientation.tZ.vX = -ptQTaskb;
      igi2_frame.tNewOrientation.tZ.vZ = igi2_frame.tNewOrientation.tX.vX;
    }
    else
    {
      if ( ptNext == (struct QTask_s *)2 )
        Real32x9_CreateGamma(&igi2_frame.tNewOrientation, *(float *)&ptQTask[8].tQTaskChildren.ptMiddle);
      ptNext = (struct QTask_s *)igi2_frame.tNewOrientation.nOps;
    }
  }
  else
  {
    ptQTaska = ptQTask[8].tQTaskChildren.ptMiddle;
    igi2_frame.tNewOrientation.tX.vX = 1.0;
    v16 = sin(*(float *)&ptQTaska);
    memset(&igi2_frame.tNewOrientation.tX.vY, 0, 12);
    igi2_frame.tNewOrientation.tZ.vX = 0.0;
    igi2_frame.tNewOrientation.tY.vY = cos(*(float *)&ptQTaska);
    igi2_frame.tNewOrientation.tY.vZ = -v16;
    igi2_frame.tNewOrientation.tZ.vY = v16;
    igi2_frame.tNewOrientation.tZ.vZ = igi2_frame.tNewOrientation.tY.vY;
  }
  v18 = igi2_frame.tNewOrientation.tZ.vX * *(float *)&ptQTask[4].tQTaskChildren.ptMiddle
      + igi2_frame.tNewOrientation.tX.vX * *(float *)&ptQTask[4].ptPrev
      + igi2_frame.tNewOrientation.tY.vX * *(float *)&ptQTask[4].tQTaskChildren.ptHead;
  v19 = igi2_frame.tNewOrientation.tZ.vY * *(float *)&ptQTask[4].tQTaskChildren.ptMiddle
      + igi2_frame.tNewOrientation.tX.vY * *(float *)&ptQTask[4].ptPrev
      + igi2_frame.tNewOrientation.tY.vY * *(float *)&ptQTask[4].tQTaskChildren.ptHead;
  *(float *)&igi2_frame.tNewPos.vY = igi2_frame.tNewOrientation.tZ.vZ * *(float *)&ptQTask[4].tQTaskChildren.ptMiddle
                        + igi2_frame.tNewOrientation.tX.vZ * *(float *)&ptQTask[4].ptPrev
                        + igi2_frame.tNewOrientation.tY.vZ * *(float *)&ptQTask[4].tQTaskChildren.ptHead;
  v20 = igi2_frame.tNewOrientation.tZ.vX * *(float *)&ptQTask[4].tQTaskRefList.ptMiddle
      + igi2_frame.tNewOrientation.tX.vX * *(float *)&ptQTask[4].tQTaskChildren.ptTail
      + igi2_frame.tNewOrientation.tY.vX * *(float *)&ptQTask[4].tQTaskRefList.ptHead;
  *(float *)&igi2_frame.tNewPos.vZ = igi2_frame.tNewOrientation.tZ.vY * *(float *)&ptQTask[4].tQTaskRefList.ptMiddle
                        + igi2_frame.tNewOrientation.tX.vY * *(float *)&ptQTask[4].tQTaskChildren.ptTail
                        + igi2_frame.tNewOrientation.tY.vY * *(float *)&ptQTask[4].tQTaskRefList.ptHead;
  *((float *)&igi2_frame.tNewPos.vZ + 1) = igi2_frame.tNewOrientation.tZ.vZ * *(float *)&ptQTask[4].tQTaskRefList.ptMiddle
                              + igi2_frame.tNewOrientation.tX.vZ * *(float *)&ptQTask[4].tQTaskChildren.ptTail
                              + igi2_frame.tNewOrientation.tY.vZ * *(float *)&ptQTask[4].tQTaskRefList.ptHead;
  v21 = igi2_frame.tNewOrientation.tZ.vX * *(float *)&ptQTask[4].eQTaskType
      + igi2_frame.tNewOrientation.tX.vX * *(float *)&ptQTask[4].tQTaskRefList.ptTail
      + igi2_frame.tNewOrientation.tY.vX * *(float *)&ptQTask[4].ptParent;
  igi2_frame.v28 = igi2_frame.tNewOrientation.tZ.vY * *(float *)&ptQTask[4].eQTaskType
      + igi2_frame.tNewOrientation.tX.vY * *(float *)&ptQTask[4].tQTaskRefList.ptTail
      + igi2_frame.tNewOrientation.tY.vY * *(float *)&ptQTask[4].ptParent;
  v22 = (char *)&ptQTask[5].ptNext->ptNext + (unsigned int)ptNext + 1;
  v23 = *((_DWORD *)pxContext + 1);
  igi2_frame.v29 = igi2_frame.tNewOrientation.tZ.vZ * *(float *)&ptQTask[4].eQTaskType
      + igi2_frame.tNewOrientation.tX.vZ * *(float *)&ptQTask[4].tQTaskRefList.ptTail
      + igi2_frame.tNewOrientation.tY.vZ * *(float *)&ptQTask[4].ptParent;
  igi2_frame.tNewOrientation.tX.vX = v20 * *(float *)(v23 + 4) + v21 * *(float *)(v23 + 8) + v18 * *(float *)v23;
  igi2_frame.tNewOrientation.tX.vY = *(float *)&igi2_frame.tNewPos.vZ * *(float *)(v23 + 4) + igi2_frame.v28 * *(float *)(v23 + 8) + v19 * *(float *)v23;
  igi2_frame.tNewOrientation.tX.vZ = *((float *)&igi2_frame.tNewPos.vZ + 1) * *(float *)(v23 + 4)
                        + igi2_frame.v29 * *(float *)(v23 + 8)
                        + *(float *)&igi2_frame.tNewPos.vY * *(float *)v23;
  igi2_frame.tNewOrientation.tY.vX = v20 * *(float *)(v23 + 16) + v21 * *(float *)(v23 + 20) + v18 * *(float *)(v23 + 12);
  igi2_frame.tNewOrientation.tY.vY = *(float *)&igi2_frame.tNewPos.vZ * *(float *)(v23 + 16)
                        + igi2_frame.v28 * *(float *)(v23 + 20)
                        + v19 * *(float *)(v23 + 12);
  igi2_frame.tNewOrientation.tY.vZ = *((float *)&igi2_frame.tNewPos.vZ + 1) * *(float *)(v23 + 16)
                        + igi2_frame.v29 * *(float *)(v23 + 20)
                        + *(float *)&igi2_frame.tNewPos.vY * *(float *)(v23 + 12);
  igi2_frame.tNewOrientation.tZ.vX = v20 * *(float *)(v23 + 28) + v21 * *(float *)(v23 + 32) + v18 * *(float *)(v23 + 24);
  igi2_frame.tNewOrientation.tZ.vY = *(float *)&igi2_frame.tNewPos.vZ * *(float *)(v23 + 28)
                        + igi2_frame.v28 * *(float *)(v23 + 32)
                        + v19 * *(float *)(v23 + 24);
  v24 = *((float *)&igi2_frame.tNewPos.vZ + 1) * *(float *)(v23 + 28) + igi2_frame.v29 * *(float *)(v23 + 32);
  v25 = *(float *)&igi2_frame.tNewPos.vY * *(float *)(v23 + 24);
  igi2_frame.tNewOrientation.nOps = (int)&v22[*(_DWORD *)(v23 + 36) + 1];
  igi2_frame.tNewOrientation.tZ.vZ = v24 + v25;
  qmemcpy(&ptQTask[3].ptPrev, &igi2_frame.tNewOrientation, sizeof(struct QTask_s));
}

// source: j/0/vehicles/cardoor.c:257  [anchor-mhash]
void __cdecl CarDoor_ParseMagicObjParametersHandler(struct QTask_s *ptQTask, void *pxContext)
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
  *(float *)(v3 + 4) = v9 * 0.01745329238474369 * 0.03333333507180214;
  v11 = *((struct ArgList_s **)v2 + 1);
  if ( v11->isQVM )
  {
    *(float *)&pxContext = 0.0;
    QVM_EvalArg(&pxContext, 4, v11, v10, 2);
    *(float *)(v3 + 8) = *(float *)&pxContext * 0.01745329238474369;
  }
  else
  {
    *(float *)(v3 + 8) = Expression_EvalFloat(v11->aptExpression[v10]) * 0.01745329238474369;
  }
}

// source: j/0/vehicles/cardoor.c:281  [size]
void __cdecl CarDoor_GetMagicObjParameterSizeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = 12;
}

// source: j/0/vehicles/cardoor.c:297  [size]
void __cdecl CarDoor_WeaponHitHandler(struct QTask_s *ptQTask, void *pxContext)
{
  void (__cdecl *pfHandler)(struct QTask_s *, ...); // ecx

  pfHandler = (void (__cdecl *)(struct QTask_s *, ...))QTask_aatQTaskFinalEvent[GameFunctions_eWeaponHitQTaskEvent][ptQTask[8].ptNext->eQTaskType].pfHandler;
  if ( pfHandler )
    pfHandler(ptQTask[8].ptNext, pxContext);
}

// source: j/0/vehicles/cardoor.c:323  [size]
void __cdecl CarDoor_AILineOfSightHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v2; // eax

  v2 = *((struct QTask_s **)pxContext + 2);
  *(_BYTE *)pxContext = v2 != ptQTask && *((struct QTask_s **)pxContext + 3) != ptQTask && ptQTask[8].ptNext != v2;
}

// source: j/0/vehicles/cardoor.c:352  [anchor-strings]
void __cdecl CarDoor_UpdateTagItemsHandler(struct QTask_s *ptQTask, void *pxContext)
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
  v6 = TagItem_Find(*(struct QTask_s **)pxContext, "CARDOOR - Rotation axis");
  if ( !v6 )
  {
    v6 = QTask_NewFn(v4, TagItem_eInt32QTaskType, nullptr);
    v7 = "CARDOOR - Rotation axis";
    do
    {
      v8 = *v7;
      v7[(char *)v6 - "CARDOOR - Rotation axis" + 40] = *v7;
      ++v7;
    }
    while ( v8 );
    v6[7].tQTaskRefList.ptHead = nullptr;
  }
  *(_DWORD *)v5 = v6[7].tQTaskRefList.ptHead;
  v9 = *(struct QTask_s **)pxContext;
  v10 = TagItem_Find(*(struct QTask_s **)pxContext, (char *)&stru_6968D8.tQTaskRefList);
  if ( v10
    || (v10 = TagItem_NewReal32MinMax(v9, (char *)&stru_6968D8.tQTaskRefList, 30.0, 0.0, 1000.0)) != nullptr )
  {
    v11 = *(float *)&v10[7].tQTaskRefList.ptHead;
  }
  else
  {
    v11 = 0.0;
  }
  *(float *)(v5 + 4) = v11;
  v12 = *(struct QTask_s **)pxContext;
  v13 = TagItem_Find(*(struct QTask_s **)pxContext, (char *)&stru_6968D8);
  if ( v13 || (v13 = TagItem_NewReal32MinMax(v12, (char *)&stru_6968D8, -118.0, -360.0, 360.0)) != nullptr )
    *(_DWORD *)(v5 + 8) = v13[7].tQTaskRefList.ptHead;
  else
    *(_DWORD *)(v5 + 8) = 0;
}

// source: j/0/vehicles/cardoor.c:386  [anchor-strings]
void __cdecl CarDoor_Open()
{
  unsigned __int16 v0; // si
  _DWORD *v1; // esi
  _DWORD *v2; // esi
  _DWORD *v3; // esi
  _DWORD *v4; // esi

  v0 = QTask_NewQTaskType("CarDoor", 344, RigidMagicObj_eQTaskType, 0, 0);
  CarDoor_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 0, CarDoor_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, CarDoor_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, CarDoor_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v0, MagicObj_eUpdateMagicObjEvent, CarDoor_UpdateMagicObjHandler);
  QTask_LinkQTaskEventHandlerFn(v0, GameFunctions_eWeaponHitQTaskEvent, CarDoor_WeaponHitHandler);
  QTask_LinkQTaskEventHandlerFn(v0, GameFunctions_eExplosionHitQTaskEvent, nullptr);
  QTask_LinkQTaskEventHandlerFn(v0, MagicObj_eGetParseMagicObjParametersEvent, CarDoor_ParseMagicObjParametersHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    MagicObj_eGetMagicObjParameterSizeEvent,
    (void (__cdecl *)(struct QTask_s *, void *))CarDoor_GetMagicObjParameterSizeHandler);
  QTask_LinkQTaskEventHandlerFn(v0, AIDetection_eLineOfSightQTaskEvent, CarDoor_AILineOfSightHandler);
  QTask_LinkQTaskEventHandlerFn(v0, MagicObjConfig_eUpdateTagItemsQTaskEvent, CarDoor_UpdateTagItemsHandler);
  Symbol_Register(
    "TASKTYPE_CARDOOR",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)v0,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  v1 = Mem_AllocFn(18444, 4);
  v1[1] = 0;
  *v1 = 0;
  v1[4610] = "TASKTYPE_CARDOOR";
  Wildcard_CreateNFA("TASKTYPE_CARDOOR", v1 + 2, (char *)v1 + 10248);
  List_AddTail(v1, (int)&MagicObjConfig_tTaskTypeEnumList);
  Symbol_Register(
    "CARDOOR_AXIS_X",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    nullptr,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "CARDOOR_AXIS_Y",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)1,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "CARDOOR_AXIS_Z",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)2,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  CarDoor_tAxisEnumList.pfEnumItemsCallback = ParameterEnumList_EnumerateItemsCallback;
  CarDoor_tAxisEnumList.ptHead = (struct ParameterEnumItem_s *)&CarDoor_tAxisEnumList.ptMiddle;
  CarDoor_tAxisEnumList.ptTail = (struct ParameterEnumItem_s *)&CarDoor_tAxisEnumList;
  CarDoor_tAxisEnumList.ptMiddle = nullptr;
  v2 = Mem_AllocFn(18444, 4);
  v2[1] = 0;
  *v2 = 0;
  v2[4610] = "CARDOOR_AXIS_X";
  Wildcard_CreateNFA("CARDOOR_AXIS_X", v2 + 2, (char *)v2 + 10248);
  List_AddTail(v2, (int)&CarDoor_tAxisEnumList);
  v3 = Mem_AllocFn(18444, 4);
  v3[1] = 0;
  *v3 = 0;
  v3[4610] = "CARDOOR_AXIS_Y";
  Wildcard_CreateNFA("CARDOOR_AXIS_Y", v3 + 2, (char *)v3 + 10248);
  List_AddTail(v3, (int)&CarDoor_tAxisEnumList);
  v4 = Mem_AllocFn(18444, 4);
  v4[1] = 0;
  *v4 = 0;
  v4[4610] = "CARDOOR_AXIS_Z";
  Wildcard_CreateNFA("CARDOOR_AXIS_Z", v4 + 2, (char *)v4 + 10248);
  List_AddTail(v4, (int)&CarDoor_tAxisEnumList);
}

// source: j/0/vehicles/cardoor.c:433  [size]
void __cdecl CarDoor_Close()
{
  ParameterEnumList_DeAlloc(&CarDoor_tAxisEnumList);
  QTask_DeleteQTaskType(CarDoor_eQTaskType);
}

// source: j/0/vehicles/cardoor.c:449  [size]
unsigned __int16 __cdecl CarDoor_GetQTaskType()
{
  return CarDoor_eQTaskType;
}

// source: j/0/vehicles/cardoor.c:462  [size]
void __cdecl CarDoor_SetOpen(struct QTask_s *ptQTask, int isOpen)
{
  LOBYTE(ptQTask[8].tQTaskChildren.ptTail) = isOpen;
}
