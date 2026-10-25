/* j/0/vehicles/cockpitshield.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/vehicles/cockpitshield.c:73  [size]
struct real32x9_t *__cdecl UpdateOrientation(
        struct CockpitShield_s *ptCockpitShield,
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

  v2 = sin(ptCockpitShield->vAngle);
  igi2_frame.v11 = cos(ptCockpitShield->vAngle);
  igi2_frame.tNewOrientation.tY.vZ = -v2;
  igi2_frame.Real32x9_Multiply_tTemp = (ptCockpitShield->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tX.vZ
                           + ptCockpitShield->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tX.vY)
                          * 0.0
                          + ptCockpitShield->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tX.vX;
  v3 = ptCockpitShield->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tX.vX * 0.0;
  igi2_frame.Real32x9_Multiply_tTemp_4 = igi2_frame.v11 * ptCockpitShield->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tX.vY
                            + v2 * ptCockpitShield->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tX.vZ
                            + v3;
  igi2_frame.Real32x9_Multiply_tTemp_8 = igi2_frame.tNewOrientation.tY.vZ
                            * ptCockpitShield->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tX.vY
                            + igi2_frame.v11 * ptCockpitShield->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tX.vZ
                            + v3;
  igi2_frame.Real32x9_Multiply_tTemp_12 = (ptCockpitShield->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tY.vZ
                              + ptCockpitShield->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tY.vY)
                             * 0.0
                             + ptCockpitShield->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tY.vX;
  v4 = ptCockpitShield->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tY.vX * 0.0;
  igi2_frame.Real32x9_Multiply_tTemp_16 = igi2_frame.v11 * ptCockpitShield->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tY.vY
                             + v2 * ptCockpitShield->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tY.vZ
                             + v4;
  igi2_frame.Real32x9_Multiply_tTemp_20 = igi2_frame.tNewOrientation.tY.vZ
                             * ptCockpitShield->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tY.vY
                             + igi2_frame.v11 * ptCockpitShield->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tY.vZ
                             + v4;
  igi2_frame.Real32x9_Multiply_tTemp_24 = (ptCockpitShield->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tZ.vZ
                              + ptCockpitShield->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tZ.vY)
                             * 0.0
                             + ptCockpitShield->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tZ.vX;
  igi2_frame.v12 = ptCockpitShield->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tZ.vX * 0.0;
  v5 = igi2_frame.v11 * ptCockpitShield->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tZ.vY
     + v2 * ptCockpitShield->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tZ.vZ
     + igi2_frame.v12;
  v6 = ptCockpitShield->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.nOps + 1;
  v7 = igi2_frame.v11 * ptCockpitShield->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tZ.vZ
     + igi2_frame.tNewOrientation.tY.vZ * ptCockpitShield->tMagicObj.tRigidDynCubeObj.tModelObj.tRelativeOrientation.tZ.vY
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
    &ptCockpitShield->tMagicObj.tRigidDynCubeObj.tModelObj.tOrientation,
    &igi2_frame.tNewOrientation,
    sizeof(ptCockpitShield->tMagicObj.tRigidDynCubeObj.tModelObj.tOrientation));
  return result;
}

// source: j/0/vehicles/cockpitshield.c:102  [anchor-mhash]
void __cdecl CockpitShield_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptNext; // edi
  struct QTask_s *v3; // eax

  ptNext = ptQTask[8].ptNext;
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][RigidMagicObj_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  v3 = *((struct QTask_s **)pxContext + 38);
  ptQTask[8].tQTaskChildren.ptHead = v3;
  if ( LOBYTE(ptNext[54].tQTaskChildren.ptMiddle) )
    *(float *)&ptQTask[8].tQTaskChildren.ptMiddle = *(float *)&v3->ptNext * 0.01745329238474369;
  else
    *(float *)&ptQTask[8].tQTaskChildren.ptMiddle = 0.0;
  UpdateOrientation((struct CockpitShield_s *)ptQTask, (struct real32x9_t *)&ptNext[3].ptPrev);
}

// source: j/0/vehicles/cockpitshield.c:146  [size]
void __cdecl CockpitShield_DeleteHandler(struct QTask_s *ptQTask)
{
  World_RemoveDynCubeObj((struct World_s *)ptQTask[2].ptParent, (struct DynCubeObj_s *)ptQTask);
}

// source: j/0/vehicles/cockpitshield.c:163  [anchor-mhash]
void __cdecl CockpitShield_RunHandler(struct QTask_s *ptQTask)
{
  double v1; // st7

  if ( LOBYTE(ptQTask[8].ptNext[54].tQTaskChildren.ptMiddle) )
    v1 = *(float *)&ptQTask[8].tQTaskChildren.ptHead->ptNext * 0.01745329238474369;
  else
    v1 = 0.0;
  if ( v1 != *(float *)&ptQTask[8].tQTaskChildren.ptMiddle )
    *(float *)&ptQTask[8].tQTaskChildren.ptMiddle = *(float *)&ptQTask[8].tQTaskChildren.ptMiddle * 0.9800000190734863
                                                  + v1 * 0.019999980926513672;
}

// source: j/0/vehicles/cockpitshield.c:205  [size]
void __cdecl CockpitShield_UpdateMagicObjHandler(struct QTask_s *ptQTask, void *pxContext)
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
  UpdateOrientation((struct CockpitShield_s *)ptQTask, *((struct real32x9_t **)pxContext + 1));
}

// source: j/0/vehicles/cockpitshield.c:254  [size]
void __cdecl CockpitShield_ParseMagicObjParametersHandler(struct QTask_s *ptQTask, void *pxContext)
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

// source: j/0/vehicles/cockpitshield.c:276  [size]
void __cdecl CockpitShield_GetMagicObjParameterSizeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = 4;
}

// source: j/0/vehicles/cockpitshield.c:292  [anchor-strings]
void __cdecl CockpitShield_UpdateTagItemsHandler(struct QTask_s *ptQTask, void *pxContext)
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
  v6 = TagItem_Find(*(struct QTask_s **)pxContext, (char *)&stru_690824);
  if ( v6 || (v6 = TagItem_NewReal32MinMax(v4, (char *)&stru_690824, 60.0, 0.0, 180.0)) != nullptr )
    *v5 = v6[7].tQTaskRefList.ptHead;
  else
    *v5 = nullptr;
}

// source: j/0/vehicles/cockpitshield.c:324  [anchor-strings]
void __cdecl CockpitShield_Open()
{
  unsigned __int16 v0; // si
  _DWORD *v1; // esi

  v0 = QTask_NewQTaskType("CockpitShield", 336, RigidMagicObj_eQTaskType, 0, 0);
  CockpitShield_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 0, CockpitShield_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, CockpitShield_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, CockpitShield_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v0, MagicObj_eUpdateMagicObjEvent, CockpitShield_UpdateMagicObjHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    MagicObj_eGetParseMagicObjParametersEvent,
    CockpitShield_ParseMagicObjParametersHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    MagicObj_eGetMagicObjParameterSizeEvent,
    (void (__cdecl *)(struct QTask_s *, void *))CockpitShield_GetMagicObjParameterSizeHandler);
  QTask_LinkQTaskEventHandlerFn(v0, MagicObjConfig_eUpdateTagItemsQTaskEvent, CockpitShield_UpdateTagItemsHandler);
  Symbol_Register(
    "TASKTYPE_COCKPITSHIELD",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)v0,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  v1 = Mem_AllocFn(18444, 4);
  v1[1] = 0;
  *v1 = 0;
  v1[4610] = "TASKTYPE_COCKPITSHIELD";
  Wildcard_CreateNFA("TASKTYPE_COCKPITSHIELD", v1 + 2, (char *)v1 + 10248);
  List_AddTail(v1, (int)&MagicObjConfig_tTaskTypeEnumList);
}

// source: j/0/vehicles/cockpitshield.c:359  [size]
void __cdecl CockpitShield_Close()
{
  QTask_DeleteQTaskType(CockpitShield_eQTaskType);
}

// source: j/0/vehicles/cockpitshield.c:373  [size]
unsigned __int16 __cdecl CockpitShield_GetQTaskType()
{
  return CockpitShield_eQTaskType;
}
