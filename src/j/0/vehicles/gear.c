/* j/0/vehicles/gear.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/vehicles/gear.c:53  [anchor-mhash]
struct real32x9_t *__cdecl Gear_UpdateOrientation(
        struct Gear_s *ptGear,
        struct real32x9_t *ptParentOrientation)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vGamma; };
    struct { char igi2_o1[4]; struct real32x9_t tNewOrientation; };
    struct { char igi2_o2[44]; struct real32x9_t Real32x9_Multiply_tTemp; };
    char igi2_extent[88];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptCreator; // eax
  double v5; // st7
  double v6; // st6
  double v7; // st5
  double v8; // st4
  int v9; // eax
  double v10; // rt1
  double v11; // st4
  double v12; // st5
  struct real32x9_t *result; // eax

  igi2_frame.vGamma = 0.0;
  if ( ptGear->ptGearParameters->isSteeringGear )
  {
    ptCreator = ptGear->tMagicObj.ptCreator;
    if ( BYTE1(ptCreator[54].tQTaskChildren.ptMiddle) )
      igi2_frame.vGamma = *(float *)&ptCreator[47].eQTaskType * 0.7853981852531433;
  }
  Real32x9_Create(&igi2_frame.tNewOrientation, ptGear->vAngle, 0.0, igi2_frame.vGamma);
  v5 = igi2_frame.tNewOrientation.tX.vX * ptGear->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tX.vX
     + igi2_frame.tNewOrientation.tZ.vX * ptGear->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tX.vZ
     + igi2_frame.tNewOrientation.tY.vX * ptGear->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tX.vY;
  v6 = igi2_frame.tNewOrientation.tX.vY * ptGear->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tX.vX
     + igi2_frame.tNewOrientation.tZ.vY * ptGear->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tX.vZ
     + igi2_frame.tNewOrientation.tY.vY * ptGear->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tX.vY;
  igi2_frame.Real32x9_Multiply_tTemp.tX.vZ = igi2_frame.tNewOrientation.tX.vZ
                                * ptGear->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tX.vX
                                + igi2_frame.tNewOrientation.tZ.vZ
                                * ptGear->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tX.vZ
                                + igi2_frame.tNewOrientation.tY.vZ
                                * ptGear->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tX.vY;
  v7 = igi2_frame.tNewOrientation.tX.vX * ptGear->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tY.vX
     + igi2_frame.tNewOrientation.tZ.vX * ptGear->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tY.vZ
     + igi2_frame.tNewOrientation.tY.vX * ptGear->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tY.vY;
  igi2_frame.Real32x9_Multiply_tTemp.tY.vY = igi2_frame.tNewOrientation.tX.vY
                                * ptGear->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tY.vX
                                + igi2_frame.tNewOrientation.tZ.vY
                                * ptGear->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tY.vZ
                                + igi2_frame.tNewOrientation.tY.vY
                                * ptGear->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tY.vY;
  igi2_frame.Real32x9_Multiply_tTemp.tY.vZ = igi2_frame.tNewOrientation.tX.vZ
                                * ptGear->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tY.vX
                                + igi2_frame.tNewOrientation.tZ.vZ
                                * ptGear->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tY.vZ
                                + igi2_frame.tNewOrientation.tY.vZ
                                * ptGear->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tY.vY;
  v8 = igi2_frame.tNewOrientation.tZ.vX * ptGear->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tZ.vZ
     + igi2_frame.tNewOrientation.tY.vX * ptGear->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tZ.vY
     + igi2_frame.tNewOrientation.tX.vX * ptGear->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tZ.vX;
  v9 = ptGear->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.nOps + igi2_frame.tNewOrientation.nOps + 1;
  igi2_frame.Real32x9_Multiply_tTemp.tZ.vY = igi2_frame.tNewOrientation.tZ.vY
                                * ptGear->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tZ.vZ
                                + igi2_frame.tNewOrientation.tY.vY
                                * ptGear->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tZ.vY
                                + igi2_frame.tNewOrientation.tX.vY
                                * ptGear->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tZ.vX;
  igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ = igi2_frame.tNewOrientation.tZ.vZ
                                * ptGear->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tZ.vZ
                                + igi2_frame.tNewOrientation.tY.vZ
                                * ptGear->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tZ.vY
                                + igi2_frame.tNewOrientation.tX.vZ
                                * ptGear->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tZ.vX;
  igi2_frame.tNewOrientation.tX.vX = v8 * ptParentOrientation->tX.vZ
                        + v7 * ptParentOrientation->tX.vY
                        + v5 * ptParentOrientation->tX.vX;
  igi2_frame.tNewOrientation.tX.vY = igi2_frame.Real32x9_Multiply_tTemp.tZ.vY * ptParentOrientation->tX.vZ
                        + igi2_frame.Real32x9_Multiply_tTemp.tY.vY * ptParentOrientation->tX.vY
                        + v6 * ptParentOrientation->tX.vX;
  igi2_frame.tNewOrientation.tX.vZ = igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ * ptParentOrientation->tX.vZ
                        + igi2_frame.Real32x9_Multiply_tTemp.tY.vZ * ptParentOrientation->tX.vY
                        + igi2_frame.Real32x9_Multiply_tTemp.tX.vZ * ptParentOrientation->tX.vX;
  igi2_frame.tNewOrientation.tY.vX = v5 * ptParentOrientation->tY.vX
                        + v8 * ptParentOrientation->tY.vZ
                        + v7 * ptParentOrientation->tY.vY;
  igi2_frame.tNewOrientation.tY.vY = v6 * ptParentOrientation->tY.vX
                        + igi2_frame.Real32x9_Multiply_tTemp.tZ.vY * ptParentOrientation->tY.vZ
                        + igi2_frame.Real32x9_Multiply_tTemp.tY.vY * ptParentOrientation->tY.vY;
  igi2_frame.tNewOrientation.tY.vZ = igi2_frame.Real32x9_Multiply_tTemp.tX.vZ * ptParentOrientation->tY.vX
                        + igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ * ptParentOrientation->tY.vZ
                        + igi2_frame.Real32x9_Multiply_tTemp.tY.vZ * ptParentOrientation->tY.vY;
  v10 = v5 * ptParentOrientation->tZ.vX;
  v11 = v8 * ptParentOrientation->tZ.vZ;
  v12 = v7 * ptParentOrientation->tZ.vY;
  result = (struct real32x9_t *)(ptParentOrientation->nOps + v9 + 1);
  igi2_frame.tNewOrientation.nOps = (int)result;
  igi2_frame.tNewOrientation.tZ.vX = v10 + v11 + v12;
  igi2_frame.tNewOrientation.tZ.vY = v6 * ptParentOrientation->tZ.vX
                        + igi2_frame.Real32x9_Multiply_tTemp.tZ.vY * ptParentOrientation->tZ.vZ
                        + igi2_frame.Real32x9_Multiply_tTemp.tY.vY * ptParentOrientation->tZ.vY;
  igi2_frame.tNewOrientation.tZ.vZ = igi2_frame.Real32x9_Multiply_tTemp.tX.vZ * ptParentOrientation->tZ.vX
                        + igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ * ptParentOrientation->tZ.vZ
                        + igi2_frame.Real32x9_Multiply_tTemp.tY.vZ * ptParentOrientation->tZ.vY;
  qmemcpy(
    &ptGear->tMagicObj.tRigidDynCubeObj.tModelObj.tOrientation,
    &igi2_frame.tNewOrientation,
    sizeof(ptGear->tMagicObj.tRigidDynCubeObj.tModelObj.tOrientation));
  return result;
}

// source: j/0/vehicles/gear.c:87  [size]
void __cdecl Gear_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptNext; // edi
  struct QTask_s *v3; // eax

  ptNext = ptQTask[8].ptNext;
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][RigidMagicObj_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  v3 = *((struct QTask_s **)pxContext + 38);
  ptQTask[8].tQTaskChildren.ptHead = v3;
  if ( BYTE1(ptNext[54].tQTaskChildren.ptMiddle) )
    *(float *)&ptQTask[8].tQTaskChildren.ptMiddle = 0.0;
  else
    *(float *)&ptQTask[8].tQTaskChildren.ptMiddle = *(float *)&v3->ptNext * 0.01745329238474369;
  Gear_UpdateOrientation((struct Gear_s *)ptQTask, (struct real32x9_t *)&ptNext[3].ptPrev);
}

// source: j/0/vehicles/gear.c:132  [size]
void __cdecl Gear_DeleteHandler(struct QTask_s *ptQTask)
{
  World_RemoveDynCubeObj((struct World_s *)ptQTask[2].ptParent, (struct DynCubeObj_s *)ptQTask);
}

// source: j/0/vehicles/gear.c:152  [anchor-mhash]
void __cdecl Gear_RunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptNext; // edx
  double v2; // st7
  double v3; // st6
  double v4; // st5
  double v5; // st6
  double v6; // st6
  char v7; // fps^1
  bool v8; // c0
  char v9; // c2
  bool v10; // c3
  char v11; // ah
  double v13; // st6
  unsigned __int8 v14; // c0
  unsigned __int8 v15; // c2
  double v16; // st7

  ptNext = ptQTask[8].ptNext;
  v2 = *(float *)&ptQTask[8].tQTaskChildren.ptHead->ptNext * 0.01745329238474369;
  if ( BYTE1(ptNext[54].tQTaskChildren.ptMiddle) && HIBYTE(ptNext[54].tQTaskChildren.ptTail) == 1 )
    v3 = 0.0;
  else
    v3 = v2;
  if ( v3 != *(float *)&ptQTask[8].tQTaskChildren.ptMiddle )
    *(float *)&ptQTask[8].tQTaskChildren.ptMiddle = 0.019999980926513672 * v3
                                                  + *(float *)&ptQTask[8].tQTaskChildren.ptMiddle * 0.9800000190734863;
  v4 = *(float *)&ptQTask[8].tQTaskChildren.ptMiddle - v3;
  if ( v4 < 0.0 )
    v4 = -v4;
  if ( v4 < 0.009999999776482582 )
    *(float *)&ptQTask[8].tQTaskChildren.ptMiddle = v3;
  v5 = *(float *)&ptQTask[8].tQTaskChildren.ptMiddle;
  if ( v5 < 0.0 )
    v5 = -v5;
  if ( v5 >= 0.1 )
  {
    v6 = *(float *)&ptQTask[8].tQTaskChildren.ptMiddle;
    if ( v6 < 0.0 )
      v6 = -v6;
    v8 = v2 - v6 < 0.0;
    v9 = 0;
    v10 = v2 - v6 == 0.0;
      v7 = (char)(v8 | (v9 << 2) | (v10 << 6));
    v11 = v7;
    v13 = *(float *)&ptQTask[8].tQTaskChildren.ptMiddle;
    if ( __SETP__(v11 & 5, 0) )
    {
      if ( v14 | v15 )
        v13 = -v13;
      v16 = v2 - v13;
    }
    else
    {
      if ( v14 | v15 )
        v13 = -v13;
      v16 = -(v2 - v13);
    }
    if ( v16 >= 0.1 )
      BYTE2(ptNext[54].tQTaskChildren.ptTail) = -1;
    else
      BYTE2(ptNext[54].tQTaskChildren.ptTail) = 0;
  }
  else
  {
    BYTE2(ptNext[54].tQTaskChildren.ptTail) = 1;
  }
}

// source: j/0/vehicles/gear.c:216  [size]
void __cdecl Gear_UpdateMagicObjHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[20]; struct real64x3_t tNewPos; };
    struct { char igi2_o2[44]; struct real64x3_t Real64x3_Rotate_tTemp; };
    char igi2_extent[72];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v2; // st7
  float *v3; // eax
  double v4; // st4
  double v5; // st3
  double *v6; // eax
  double v7; // st7
  double v8; // st7
  int *v9; // eax
  int v10; // eax
  double v11; // st6

  v2 = *(float *)&ptQTask[5].ptPrev;
  igi2_frame.tNewPos.vY = *(float *)&ptQTask[5].tQTaskChildren.ptHead;
  v3 = *((float **)pxContext + 1);
  igi2_frame.tNewPos.vZ = *(float *)&ptQTask[5].tQTaskChildren.ptMiddle;
  igi2_frame.Real64x3_Rotate_tTemp.vX = v3[2] * igi2_frame.tNewPos.vZ + v3[1] * igi2_frame.tNewPos.vY + *v3 * v2;
  igi2_frame.Real64x3_Rotate_tTemp.vY = v3[5] * igi2_frame.tNewPos.vZ + v3[4] * igi2_frame.tNewPos.vY + v3[3] * v2;
  v4 = v3[8] * igi2_frame.tNewPos.vZ + v3[7] * igi2_frame.tNewPos.vY;
  v5 = v3[6];
  v6 = *(double **)pxContext;
  igi2_frame.Real64x3_Rotate_tTemp.vZ = v4 + v5 * v2;
  qmemcpy(&igi2_frame.tNewPos, &igi2_frame.Real64x3_Rotate_tTemp, sizeof(igi2_frame.tNewPos));
  igi2_frame.tNewPos.vX = igi2_frame.Real64x3_Rotate_tTemp.vX + *v6;
  igi2_frame.tNewPos.vY = igi2_frame.tNewPos.vY + v6[1];
  igi2_frame.tNewPos.vZ = igi2_frame.tNewPos.vZ + v6[2];
  if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
    v7 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  else
    v7 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  if ( v7 >= *(float *)&ptQTask[6].ptPrev )
  {
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
      v8 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v8 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  }
  else
  {
    v8 = *(float *)&ptQTask[6].ptPrev;
  }
  v9 = *(int **)&ptQTask[2].eQTaskType;
  if ( v9 && (v10 = *v9) != 0 )
    v11 = *(float *)(*(_DWORD *)(*(_DWORD *)(v10 + 12) + 12) + 120);
  else
    v11 = 1.0;
  igi2_frame.ptDynCubeObj = v8 * v11;
  World_MoveDynCubeObjRadius(Game_ptGame->ptWorld, (struct DynCubeObj_s *)ptQTask, &igi2_frame.tNewPos, igi2_frame.ptDynCubeObj);
  Gear_UpdateOrientation((struct Gear_s *)ptQTask, *((struct real32x9_t **)pxContext + 1));
}

// source: j/0/vehicles/gear.c:268  [anchor-mhash]
void __cdecl Gear_ParseMagicObjParametersHandler(struct QTask_s *ptQTask, void *pxContext)
{
  void *v2; // ebx
  int v3; // ebp
  int v4; // esi
  struct ArgList_s *v5; // edi
  double v6; // st7
  struct ArgList_s *v7; // edi
  int v8; // esi
  char v9; // al
  struct ArgList_s *v10; // edi
  int v11; // esi
  double v12; // st7
  struct ArgList_s *v13; // edi
  int v14; // esi
  double v15; // st7
  struct ArgList_s *v16; // ebx
  int v17; // esi

  v2 = pxContext;
  v3 = *(_DWORD *)pxContext;
  v4 = *((_DWORD *)pxContext + 2);
  v5 = *((struct ArgList_s **)pxContext + 1);
  if ( v5->isQVM )
  {
    *(float *)&pxContext = 0.0;
    QVM_EvalArg(&pxContext, 4, v5, v4, 2);
    v6 = *(float *)&pxContext;
  }
  else
  {
    v6 = Expression_EvalFloat(v5->aptExpression[v4]);
  }
  *(float *)v3 = v6;
  v7 = *((struct ArgList_s **)v2 + 1);
  v8 = v4 + 1;
  if ( v7->isQVM )
  {
    *(float *)&pxContext = 0.0;
    QVM_EvalArg(&pxContext, 4, v7, v8, 1);
    v9 = (char)pxContext;
  }
  else
  {
    v9 = Expression_EvalInt(v7->aptExpression[v8]);
  }
  *(_BYTE *)(v3 + 4) = v9;
  v10 = *((struct ArgList_s **)v2 + 1);
  v11 = v8 + 1;
  if ( v10->isQVM )
  {
    *(float *)&pxContext = 0.0;
    QVM_EvalArg(&pxContext, 4, v10, v11, 2);
    v12 = *(float *)&pxContext;
  }
  else
  {
    v12 = Expression_EvalFloat(v10->aptExpression[v11]);
  }
  *(float *)(v3 + 8) = v12;
  v13 = *((struct ArgList_s **)v2 + 1);
  v14 = v11 + 1;
  if ( v13->isQVM )
  {
    *(float *)&pxContext = 0.0;
    QVM_EvalArg(&pxContext, 4, v13, v14, 2);
    v15 = *(float *)&pxContext;
  }
  else
  {
    v15 = Expression_EvalFloat(v13->aptExpression[v14]);
  }
  *(float *)(v3 + 12) = v15;
  v16 = *((struct ArgList_s **)v2 + 1);
  v17 = v14 + 1;
  if ( v16->isQVM )
  {
    *(float *)&pxContext = 0.0;
    QVM_EvalArg(&pxContext, 4, v16, v17, 2);
    *(float *)(v3 + 16) = *(float *)&pxContext;
  }
  else
  {
    *(float *)(v3 + 16) = Expression_EvalFloat(v16->aptExpression[v17]);
  }
}

// source: j/0/vehicles/gear.c:294  [size]
void __cdecl Gear_GetMagicObjParameterSizeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = 20;
}

// source: j/0/vehicles/gear.c:310  [anchor-strings]
void __cdecl Gear_UpdateTagItemsHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // eax
  int v3; // ebx
  struct QTask_s *v4; // edi
  int v5; // ebp
  struct QTask_s *v6; // eax
  double v7; // st7
  struct QTask_s *v8; // edi
  struct QTask_s *v9; // eax
  char ptHead; // al
  struct QTask_s *v11; // edi
  struct QTask_s *v12; // eax
  double v13; // st7
  struct QTask_s *v14; // edi
  struct QTask_s *v15; // eax
  double v16; // st7
  struct QTask_s *v17; // esi
  struct QTask_s *v18; // eax

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
  *(_DWORD *)(*((_DWORD *)pxContext + 1) + 80) = Mem_AllocFn(20, 4);
  v4 = *(struct QTask_s **)pxContext;
  v5 = *(_DWORD *)(*((_DWORD *)pxContext + 1) + 80);
  v6 = TagItem_Find(*(struct QTask_s **)pxContext, "GEAR - Max angle");
  if ( v6 || (v6 = TagItem_NewReal32MinMax(v4, "GEAR - Max angle", 90.0, -360.0, 360.0)) != nullptr )
    v7 = *(float *)&v6[7].tQTaskRefList.ptHead;
  else
    v7 = 0.0;
  *(float *)v5 = v7;
  v8 = *(struct QTask_s **)pxContext;
  v9 = TagItem_Find(*(struct QTask_s **)pxContext, "GEAR - Steering gear");
  if ( v9 || (v9 = TagItem_NewBool8(v8, "GEAR - Steering gear", false)) != nullptr )
    ptHead = (char)v9[7].tQTaskRefList.ptHead;
  else
    ptHead = 0;
  *(_BYTE *)(v5 + 4) = ptHead;
  v11 = *(struct QTask_s **)pxContext;
  v12 = TagItem_Find(*(struct QTask_s **)pxContext, "GEAR - X friction");
  if ( v12 || (v12 = TagItem_NewReal32MinMax(v11, "GEAR - X friction", 0.9800000190734863, 0.0, 1.0)) != nullptr )
    v13 = *(float *)&v12[7].tQTaskRefList.ptHead;
  else
    v13 = 0.0;
  *(float *)(v5 + 8) = v13;
  v14 = *(struct QTask_s **)pxContext;
  v15 = TagItem_Find(*(struct QTask_s **)pxContext, (char *)&stru_69A15C.tQTaskRefList.ptMiddle);
  if ( v15
    || (v15 = TagItem_NewReal32MinMax(v14, (char *)&stru_69A15C.tQTaskRefList.ptMiddle, 0.10000000149011612, 0.0, 1.0)) != nullptr )
  {
    v16 = *(float *)&v15[7].tQTaskRefList.ptHead;
  }
  else
  {
    v16 = 0.0;
  }
  *(float *)(v5 + 12) = v16;
  v17 = *(struct QTask_s **)pxContext;
  v18 = TagItem_Find(*(struct QTask_s **)pxContext, (char *)&stru_69A15C);
  if ( v18 || (v18 = TagItem_NewReal32MinMax(v17, (char *)&stru_69A15C, 0.5, 0.0, 1.0)) != nullptr )
    *(_DWORD *)(v5 + 16) = v18[7].tQTaskRefList.ptHead;
  else
    *(_DWORD *)(v5 + 16) = 0;
}

// source: j/0/vehicles/gear.c:346  [anchor-strings]
void __cdecl Gear_Open()
{
  unsigned __int16 v0; // si
  _DWORD *v1; // esi

  v0 = QTask_NewQTaskType("Gear", 336, RigidMagicObj_eQTaskType, 0, 0);
  Gear_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 0, Gear_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, Gear_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, Gear_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v0, MagicObj_eUpdateMagicObjEvent, Gear_UpdateMagicObjHandler);
  QTask_LinkQTaskEventHandlerFn(v0, MagicObj_eGetParseMagicObjParametersEvent, Gear_ParseMagicObjParametersHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    MagicObj_eGetMagicObjParameterSizeEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Gear_GetMagicObjParameterSizeHandler);
  QTask_LinkQTaskEventHandlerFn(v0, MagicObjConfig_eUpdateTagItemsQTaskEvent, Gear_UpdateTagItemsHandler);
  Symbol_Register(
    "TASKTYPE_GEAR",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)v0,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  v1 = Mem_AllocFn(18444, 4);
  v1[1] = 0;
  *v1 = 0;
  v1[4610] = "TASKTYPE_GEAR";
  Wildcard_CreateNFA("TASKTYPE_GEAR", v1 + 2, (char *)v1 + 10248);
  List_AddTail(v1, (int)&MagicObjConfig_tTaskTypeEnumList);
}

// source: j/0/vehicles/gear.c:381  [size]
void __cdecl Gear_Close()
{
  QTask_DeleteQTaskType(Gear_eQTaskType);
}

// source: j/0/vehicles/gear.c:395  [size]
unsigned __int16 __cdecl Gear_GetQTaskType()
{
  return Gear_eQTaskType;
}
