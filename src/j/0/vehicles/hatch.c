/* j/0/vehicles/hatch.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/vehicles/hatch.c:73  [size]
struct real32x9_t *__cdecl Hatch_UpdateOrientation(
        struct Hatch_s *ptHatch,
        struct real32x9_t *ptParentOrientation)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v11; };
    struct { char igi2_o1[4]; float v12; };
    struct { char igi2_o2[8]; float Real32x9_Multiply_tTemp; };
    struct { char igi2_o3[12]; float Real32x9_Multiply_tTemp_4; };
    struct { char igi2_o4[16]; float Real32x9_Multiply_tTemp_8; };
    struct { char igi2_o5[20]; float Real32x9_Multiply_tTemp_12; };
    struct { char igi2_o6[24]; float Real32x9_Multiply_tTemp_16; };
    struct { char igi2_o7[28]; float Real32x9_Multiply_tTemp_20; };
    struct { char igi2_o8[32]; float Real32x9_Multiply_tTemp_24; };
    struct { char igi2_o9[48]; struct real32x9_t tNewOrientation; };
    char igi2_extent[92];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  long double v2; // rt0
  double v3; // st6
  double v4; // st6
  long double v5; // st7
  int v6; // edx
  double v7; // st6
  double v8; // st7
  double v9; // st6
  struct real32x9_t *result; // eax

  v2 = sin(ptHatch->vAngle);
  igi2_frame.v11 = cos(ptHatch->vAngle);
  igi2_frame.tNewOrientation.tY.vZ = -v2;
  igi2_frame.Real32x9_Multiply_tTemp = (ptHatch->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tX.vZ
                           + ptHatch->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tX.vY)
                          * 0.0
                          + ptHatch->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tX.vX;
  v3 = ptHatch->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tX.vX * 0.0;
  igi2_frame.Real32x9_Multiply_tTemp_4 = igi2_frame.v11 * ptHatch->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tX.vY
                            + v2 * ptHatch->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tX.vZ
                            + v3;
  igi2_frame.Real32x9_Multiply_tTemp_8 = igi2_frame.tNewOrientation.tY.vZ
                            * ptHatch->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tX.vY
                            + igi2_frame.v11 * ptHatch->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tX.vZ
                            + v3;
  igi2_frame.Real32x9_Multiply_tTemp_12 = (ptHatch->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tY.vZ
                              + ptHatch->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tY.vY)
                             * 0.0
                             + ptHatch->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tY.vX;
  v4 = ptHatch->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tY.vX * 0.0;
  igi2_frame.Real32x9_Multiply_tTemp_16 = igi2_frame.v11 * ptHatch->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tY.vY
                             + v2 * ptHatch->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tY.vZ
                             + v4;
  igi2_frame.Real32x9_Multiply_tTemp_20 = igi2_frame.tNewOrientation.tY.vZ
                             * ptHatch->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tY.vY
                             + igi2_frame.v11 * ptHatch->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tY.vZ
                             + v4;
  igi2_frame.Real32x9_Multiply_tTemp_24 = (ptHatch->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tZ.vZ
                              + ptHatch->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tZ.vY)
                             * 0.0
                             + ptHatch->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tZ.vX;
  igi2_frame.v12 = ptHatch->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tZ.vX * 0.0;
  v5 = igi2_frame.v11 * ptHatch->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tZ.vY
     + v2 * ptHatch->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tZ.vZ
     + igi2_frame.v12;
  v6 = ptHatch->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.nOps + 1;
  v7 = igi2_frame.v11 * ptHatch->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tZ.vZ
     + igi2_frame.tNewOrientation.tY.vZ * ptHatch->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tZ.vY
     + igi2_frame.v12;
  igi2_frame.tNewOrientation.tX.vX = igi2_frame.Real32x9_Multiply_tTemp_24 * ptParentOrientation->tX.vZ
                        + igi2_frame.Real32x9_Multiply_tTemp_12 * ptParentOrientation->tX.vY
                        + igi2_frame.Real32x9_Multiply_tTemp * ptParentOrientation->tX.vX;
  igi2_frame.tNewOrientation.tX.vY = v5 * ptParentOrientation->tX.vZ
                        + igi2_frame.Real32x9_Multiply_tTemp_16 * ptParentOrientation->tX.vY
                        + igi2_frame.Real32x9_Multiply_tTemp_4 * ptParentOrientation->tX.vX;
  igi2_frame.tNewOrientation.tX.vZ = v7 * ptParentOrientation->tX.vZ
                        + igi2_frame.Real32x9_Multiply_tTemp_20 * ptParentOrientation->tX.vY
                        + igi2_frame.Real32x9_Multiply_tTemp_8 * ptParentOrientation->tX.vX;
  igi2_frame.tNewOrientation.tY.vX = igi2_frame.Real32x9_Multiply_tTemp_24 * ptParentOrientation->tY.vZ
                        + igi2_frame.Real32x9_Multiply_tTemp_12 * ptParentOrientation->tY.vY
                        + igi2_frame.Real32x9_Multiply_tTemp * ptParentOrientation->tY.vX;
  igi2_frame.tNewOrientation.tY.vY = v5 * ptParentOrientation->tY.vZ
                        + igi2_frame.Real32x9_Multiply_tTemp_16 * ptParentOrientation->tY.vY
                        + igi2_frame.Real32x9_Multiply_tTemp_4 * ptParentOrientation->tY.vX;
  igi2_frame.tNewOrientation.tY.vZ = v7 * ptParentOrientation->tY.vZ
                        + igi2_frame.Real32x9_Multiply_tTemp_20 * ptParentOrientation->tY.vY
                        + igi2_frame.Real32x9_Multiply_tTemp_8 * ptParentOrientation->tY.vX;
  igi2_frame.tNewOrientation.tZ.vX = igi2_frame.Real32x9_Multiply_tTemp * ptParentOrientation->tZ.vX
                        + igi2_frame.Real32x9_Multiply_tTemp_24 * ptParentOrientation->tZ.vZ
                        + igi2_frame.Real32x9_Multiply_tTemp_12 * ptParentOrientation->tZ.vY;
  igi2_frame.tNewOrientation.tZ.vY = igi2_frame.Real32x9_Multiply_tTemp_4 * ptParentOrientation->tZ.vX
                        + v5 * ptParentOrientation->tZ.vZ
                        + igi2_frame.Real32x9_Multiply_tTemp_16 * ptParentOrientation->tZ.vY;
  v8 = igi2_frame.Real32x9_Multiply_tTemp_8 * ptParentOrientation->tZ.vX + v7 * ptParentOrientation->tZ.vZ;
  v9 = igi2_frame.Real32x9_Multiply_tTemp_20 * ptParentOrientation->tZ.vY;
  result = (struct real32x9_t *)ptParentOrientation->nOps;
  igi2_frame.tNewOrientation.nOps = (int)&result->tX.vX + v6 + 1;
  igi2_frame.tNewOrientation.tZ.vZ = v8 + v9;
  qmemcpy(
    &ptHatch->tMagicObj.tRigidDynCubeObj.tModelObj.tOrientation,
    &igi2_frame.tNewOrientation,
    sizeof(ptHatch->tMagicObj.tRigidDynCubeObj.tModelObj.tOrientation));
  return result;
}

// source: j/0/vehicles/hatch.c:101  [size]
void __cdecl Hatch_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
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
  Hatch_UpdateOrientation((struct Hatch_s *)ptQTask, (struct real32x9_t *)&ptNext[3].ptPrev);
}

// source: j/0/vehicles/hatch.c:145  [size]
void __cdecl Hatch_DeleteHandler(struct QTask_s *ptQTask)
{
  World_RemoveDynCubeObj((struct World_s *)ptQTask[2].ptParent, (struct DynCubeObj_s *)ptQTask);
}

// source: j/0/vehicles/hatch.c:162  [anchor-mhash]
void __cdecl Hatch_RunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptNext; // edx
  double v2; // st7
  double v3; // st6
  double v4; // st6
  double v5; // st6
  char v6; // fps^1
  bool v7; // c0
  char v8; // c2
  bool v9; // c3
  char v10; // ah
  double v12; // st6
  unsigned __int8 v13; // c0
  unsigned __int8 v14; // c2
  double v15; // st7

  ptNext = ptQTask[8].ptNext;
  v2 = *(float *)&ptQTask[8].tQTaskChildren.ptHead->ptNext * 0.01745329238474369;
  if ( BYTE1(ptNext[54].tQTaskChildren.ptMiddle) || BYTE2(ptNext[54].tQTaskChildren.ptTail) )
    v3 = *(float *)&ptQTask[8].tQTaskChildren.ptMiddle * 0.9700000286102295;
  else
    v3 = 0.029999971389770508 * v2 + *(float *)&ptQTask[8].tQTaskChildren.ptMiddle * 0.9700000286102295;
  *(float *)&ptQTask[8].tQTaskChildren.ptMiddle = v3;
  v4 = *(float *)&ptQTask[8].tQTaskChildren.ptMiddle;
  if ( v4 < 0.0 )
    v4 = -v4;
  if ( v4 >= 0.1 )
  {
    v5 = *(float *)&ptQTask[8].tQTaskChildren.ptMiddle;
    if ( v5 < 0.0 )
      v5 = -v5;
    v7 = v2 - v5 < 0.0;
    v8 = 0;
    v9 = v2 - v5 == 0.0;
      v6 = (char)(v7 | (v8 << 2) | (v9 << 6));
    v10 = v6;
    v12 = *(float *)&ptQTask[8].tQTaskChildren.ptMiddle;
    if ( __SETP__(v10 & 5, 0) )
    {
      if ( v13 | v14 )
        v12 = -v12;
      v15 = v2 - v12;
    }
    else
    {
      if ( v13 | v14 )
        v12 = -v12;
      v15 = -(v2 - v12);
    }
    if ( v15 >= 0.1 )
      HIBYTE(ptNext[54].tQTaskChildren.ptTail) = -1;
    else
      HIBYTE(ptNext[54].tQTaskChildren.ptTail) = 0;
  }
  else
  {
    HIBYTE(ptNext[54].tQTaskChildren.ptTail) = 1;
  }
}

// source: j/0/vehicles/hatch.c:211  [size]
void __cdecl Hatch_UpdateMagicObjHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[24]; float Real32x3_Rotate_tTemp_8; };
    struct { char igi2_o2[28]; struct real64x3_t tNewPos; };
    char igi2_extent[56];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  float *v2; // eax
  double v3; // st7
  double v4; // st6
  double v5; // st5
  double v6; // st4
  double *v7; // eax
  double v8; // st7
  double v9; // st7
  int *v10; // eax
  int v11; // eax
  double v12; // st6

  v2 = *((float **)pxContext + 1);
  v3 = v2[2] * *(float *)&ptQTask[5].tQTaskChildren.ptMiddle
     + v2[1] * *(float *)&ptQTask[5].tQTaskChildren.ptHead
     + *v2 * *(float *)&ptQTask[5].ptPrev;
  v4 = v2[5] * *(float *)&ptQTask[5].tQTaskChildren.ptMiddle
     + v2[4] * *(float *)&ptQTask[5].tQTaskChildren.ptHead
     + v2[3] * *(float *)&ptQTask[5].ptPrev;
  v5 = v2[8] * *(float *)&ptQTask[5].tQTaskChildren.ptMiddle + v2[7] * *(float *)&ptQTask[5].tQTaskChildren.ptHead;
  v6 = v2[6];
  v7 = *(double **)pxContext;
  igi2_frame.Real32x3_Rotate_tTemp_8 = v5 + v6 * *(float *)&ptQTask[5].ptPrev;
  igi2_frame.tNewPos.vX = v3 + *(double *)*(_DWORD *)pxContext;
  igi2_frame.tNewPos.vY = v4 + v7[1];
  igi2_frame.tNewPos.vZ = igi2_frame.Real32x3_Rotate_tTemp_8 + v7[2];
  if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
    v8 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  else
    v8 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  if ( v8 >= *(float *)&ptQTask[6].ptPrev )
  {
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
      v9 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v9 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  }
  else
  {
    v9 = *(float *)&ptQTask[6].ptPrev;
  }
  v10 = *(int **)&ptQTask[2].eQTaskType;
  if ( v10 && (v11 = *v10) != 0 )
    v12 = *(float *)(*(_DWORD *)(*(_DWORD *)(v11 + 12) + 12) + 120);
  else
    v12 = 1.0;
  igi2_frame.ptDynCubeObj = v9 * v12;
  World_MoveDynCubeObjRadius(Game_ptGame->ptWorld, (struct DynCubeObj_s *)ptQTask, &igi2_frame.tNewPos, igi2_frame.ptDynCubeObj);
  Hatch_UpdateOrientation((struct Hatch_s *)ptQTask, *((struct real32x9_t **)pxContext + 1));
}

// source: j/0/vehicles/hatch.c:264  [size]
void __cdecl Hatch_ParseMagicObjParametersHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // eax
  void **v3; // esi
  struct ArgList_s *v4; // edi

  v2 = *((_DWORD *)pxContext + 2);
  v3 = *(void ***)pxContext;
  v4 = *((struct ArgList_s **)pxContext + 1);
  if ( v4->isQVM )
  {
    pxContext = nullptr;
    QVM_EvalArg(&pxContext, 4, v4, v2, 2);
    *v3 = pxContext;
  }
  else
  {
    *(float *)v3 = Expression_EvalFloat(v4->aptExpression[v2]);
  }
}

// source: j/0/vehicles/hatch.c:286  [size]
void __cdecl Hatch_GetMagicObjParameterSizeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = 4;
}

// source: j/0/vehicles/hatch.c:302  [anchor-strings]
void __cdecl Hatch_UpdateTagItemsHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // eax
  int v3; // ebx
  struct QTask_s *v4; // esi
  struct QReference_s **v5; // ebp
  struct QTask_s *v6; // eax

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
  *(_DWORD *)(*((_DWORD *)pxContext + 1) + 80) = Mem_AllocFn(4, 4);
  v4 = *(struct QTask_s **)pxContext;
  v5 = *(struct QReference_s ***)(*((_DWORD *)pxContext + 1) + 80);
  v6 = TagItem_Find(*(struct QTask_s **)pxContext, &g_zMessage_0.zTalkString[132]);
  if ( v6 || (v6 = TagItem_NewReal32MinMax(v4, &g_zMessage_0.zTalkString[132], 90.0, 0.0, 180.0)) != nullptr )
    *v5 = v6[7].tQTaskRefList.ptHead;
  else
    *v5 = nullptr;
}

// source: j/0/vehicles/hatch.c:334  [anchor-strings]
void __cdecl Hatch_Open()
{
  unsigned __int16 v0; // si
  _DWORD *v1; // esi

  v0 = QTask_NewQTaskType(&g_zMessage_0.zTalkString[124], 336, RigidMagicObj_eQTaskType, 0, 0);
  Hatch_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 0, Hatch_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, Hatch_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, Hatch_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v0, MagicObj_eUpdateMagicObjEvent, Hatch_UpdateMagicObjHandler);
  QTask_LinkQTaskEventHandlerFn(v0, MagicObj_eGetParseMagicObjParametersEvent, Hatch_ParseMagicObjParametersHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    MagicObj_eGetMagicObjParameterSizeEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Hatch_GetMagicObjParameterSizeHandler);
  QTask_LinkQTaskEventHandlerFn(v0, MagicObjConfig_eUpdateTagItemsQTaskEvent, Hatch_UpdateTagItemsHandler);
  Symbol_Register(
    &g_zMessage_0.zTalkString[108],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)v0,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  v1 = Mem_AllocFn(18444, 4);
  v1[1] = 0;
  *v1 = 0;
  v1[4610] = &g_zMessage_0.zTalkString[108];
  Wildcard_CreateNFA(&g_zMessage_0.zTalkString[108], v1 + 2, (char *)v1 + 10248);
  List_AddTail(v1, (int)&MagicObjConfig_tTaskTypeEnumList);
}

// source: j/0/vehicles/hatch.c:369  [size]
void __cdecl Hatch_Close()
{
  QTask_DeleteQTaskType(Hatch_eQTaskType);
}

// source: j/0/vehicles/hatch.c:383  [size]
unsigned __int16 __cdecl Hatch_GetQTaskType()
{
  return Hatch_eQTaskType;
}
