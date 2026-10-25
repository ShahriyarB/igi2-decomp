/* j/0/vehicles/rudder.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/vehicles/rudder.c:89  [size]
void __cdecl Rudder_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][RigidMagicObj_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  ptQTask[8].tQTaskChildren.ptHead = *((struct QTask_s **)pxContext + 38);
}

// source: j/0/vehicles/rudder.c:124  [size]
void __cdecl Rudder_DeleteHandler(struct QTask_s *ptQTask)
{
  World_RemoveDynCubeObj((struct World_s *)ptQTask[2].ptParent, (struct DynCubeObj_s *)ptQTask);
}

// source: j/0/vehicles/rudder.c:141  [size]
void __cdecl Rudder_RunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // ecx
  int v2; // edx
  struct QTask_s *v3; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v5; // edx

  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v2 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v3 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v3 = nullptr;
      QTask_atProtectedQTaskStack[v2].ptQTask = v3;
      pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][ptHead->eQTaskType].pfHandler;
      v5 = v2 + 1;
      QTask_nProtectedQTaskStackOffset = v5;
      if ( pfHandler )
      {
        pfHandler(ptHead);
        v5 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v5];
      v2 = v5 - 1;
      QTask_nProtectedQTaskStackOffset = v2;
    }
    while ( ptHead );
  }
}

// source: j/0/vehicles/rudder.c:160  [size]
void __cdecl Rudder_UpdateMagicObjHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[32]; float Real32x3_Rotate_tTemp_8; };
    struct { char igi2_o2[36]; struct real64x3_t tNewPos; };
    struct { char igi2_o3[60]; float v35; };
    struct { char igi2_o4[64]; float v36; };
    struct { char igi2_o5[76]; struct real32x9_t Real32x9_Multiply_tTemp; };
    char igi2_extent[120];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v3; // edi
  int v4; // ebp
  float *v5; // eax
  double v6; // st7
  double v7; // st6
  double v8; // st5
  double v9; // st4
  double *v10; // eax
  double v11; // st7
  double v12; // st7
  int *v13; // eax
  int v14; // eax
  double v15; // st6
  struct QTask_s *ptHead; // eax
  double v17; // st7
  struct QTask_s *ptNext; // eax
  double v19; // st7
  long double v20; // st7
  long double v21; // st7
  double v22; // st6
  double v23; // st5
  double v24; // st5
  double v25; // st5
  long double v26; // st7
  int v27; // eax
  char *v28; // ecx
  int v29; // edx
  long double v30; // st7
  double v31; // st6
  float pxContexta = *(float *)&pxContext; // [esp+80h] [ebp+8h] ARGSLOT

  v3 = *((_DWORD *)pxContext + 2);
  v4 = *(_DWORD *)(*(_DWORD *)(v3 + 516) + 724);
  v5 = *((float **)pxContext + 1);
  v6 = v5[2] * *(float *)&ptQTask[5].tQTaskChildren.ptMiddle
     + v5[1] * *(float *)&ptQTask[5].tQTaskChildren.ptHead
     + *(float *)&ptQTask[5].ptPrev * *v5;
  v7 = v5[5] * *(float *)&ptQTask[5].tQTaskChildren.ptMiddle
     + v5[4] * *(float *)&ptQTask[5].tQTaskChildren.ptHead
     + v5[3] * *(float *)&ptQTask[5].ptPrev;
  v8 = v5[8] * *(float *)&ptQTask[5].tQTaskChildren.ptMiddle + v5[7] * *(float *)&ptQTask[5].tQTaskChildren.ptHead;
  v9 = v5[6];
  v10 = *(double **)pxContext;
  igi2_frame.Real32x3_Rotate_tTemp_8 = v8 + v9 * *(float *)&ptQTask[5].ptPrev;
  igi2_frame.tNewPos.vX = v6 + *(double *)*(_DWORD *)pxContext;
  igi2_frame.tNewPos.vY = v7 + v10[1];
  igi2_frame.tNewPos.vZ = igi2_frame.Real32x3_Rotate_tTemp_8 + v10[2];
  if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
    v11 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  else
    v11 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  if ( v11 >= *(float *)&ptQTask[6].ptPrev )
  {
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
      v12 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v12 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  }
  else
  {
    v12 = *(float *)&ptQTask[6].ptPrev;
  }
  v13 = *(int **)&ptQTask[2].eQTaskType;
  if ( v13 && (v14 = *v13) != 0 )
    v15 = *(float *)(*(_DWORD *)(*(_DWORD *)(v14 + 12) + 12) + 120);
  else
    v15 = 1.0;
  igi2_frame.ptDynCubeObj = v15 * v12;
  World_MoveDynCubeObjRadius(Game_ptGame->ptWorld, (struct DynCubeObj_s *)ptQTask, &igi2_frame.tNewPos, igi2_frame.ptDynCubeObj);
  ptHead = ptQTask[8].tQTaskChildren.ptHead;
  v17 = *(float *)&ptHead->ptPrev;
  ptNext = ptHead->ptNext;
  v19 = v17 * 0.01745329238474369;
  if ( ptNext == (struct QTask_s *)1 )
  {
    v20 = v19 * *(float *)(v3 + 1912) - v19 * *(float *)(v3 + 1908);
  }
  else
  {
    if ( ptNext != (struct QTask_s *)2 )
    {
      if ( ptNext )
      {
        if ( ptNext == (struct QTask_s *)3 )
          v20 = -(v19 * *(float *)(v3 + 1916));
        else
          v20 = *(float *)&pxContext;
      }
      else
      {
        v20 = -(v19 * *(float *)(v3 + 1908));
      }
      goto LABEL_24;
    }
    v20 = v19 * *(float *)(v3 + 1912) + v19 * *(float *)(v3 + 1908);
  }
  if ( v20 >= *(float *)(v4 + 4) )
    v20 = *(float *)(v4 + 4);
LABEL_24:
  pxContexta = sin(v20);
  v21 = cos(v20);
  v22 = -pxContexta;
  *(float *)&igi2_frame.tNewPos.vX = (*(float *)&ptQTask[4].tQTaskChildren.ptHead + *(float *)&ptQTask[4].tQTaskChildren.ptMiddle)
                        * 0.0
                        + *(float *)&ptQTask[4].ptPrev;
  v23 = *(float *)&ptQTask[4].ptPrev * 0.0;
  *((float *)&igi2_frame.tNewPos.vX + 1) = v21 * *(float *)&ptQTask[4].tQTaskChildren.ptHead
                              + pxContexta * *(float *)&ptQTask[4].tQTaskChildren.ptMiddle
                              + v23;
  *(float *)&igi2_frame.tNewPos.vY = v21 * *(float *)&ptQTask[4].tQTaskChildren.ptMiddle
                        + v22 * *(float *)&ptQTask[4].tQTaskChildren.ptHead
                        + v23;
  *((float *)&igi2_frame.tNewPos.vY + 1) = (*(float *)&ptQTask[4].tQTaskRefList.ptMiddle
                               + *(float *)&ptQTask[4].tQTaskRefList.ptHead)
                              * 0.0
                              + *(float *)&ptQTask[4].tQTaskChildren.ptTail;
  v24 = *(float *)&ptQTask[4].tQTaskChildren.ptTail * 0.0;
  *(float *)&igi2_frame.tNewPos.vZ = pxContexta * *(float *)&ptQTask[4].tQTaskRefList.ptMiddle
                        + v21 * *(float *)&ptQTask[4].tQTaskRefList.ptHead
                        + v24;
  *((float *)&igi2_frame.tNewPos.vZ + 1) = v21 * *(float *)&ptQTask[4].tQTaskRefList.ptMiddle
                              + v22 * *(float *)&ptQTask[4].tQTaskRefList.ptHead
                              + v24;
  igi2_frame.v35 = (*(float *)&ptQTask[4].eQTaskType + *(float *)&ptQTask[4].ptParent) * 0.0
      + *(float *)&ptQTask[4].tQTaskRefList.ptTail;
  v25 = *(float *)&ptQTask[4].tQTaskRefList.ptTail * 0.0;
  igi2_frame.v36 = v21 * *(float *)&ptQTask[4].ptParent + pxContexta * *(float *)&ptQTask[4].eQTaskType + v25;
  v26 = v22 * *(float *)&ptQTask[4].ptParent + v21 * *(float *)&ptQTask[4].eQTaskType + v25;
  v27 = *((_DWORD *)pxContext + 1);
  v28 = (char *)&ptQTask[5].ptNext->ptNext + 1;
  igi2_frame.Real32x9_Multiply_tTemp.tX.vX = *((float *)&igi2_frame.tNewPos.vY + 1) * *(float *)(v27 + 4)
                                + *(float *)&igi2_frame.tNewPos.vX * *(float *)v27
                                + igi2_frame.v35 * *(float *)(v27 + 8);
  igi2_frame.Real32x9_Multiply_tTemp.tX.vY = *(float *)&igi2_frame.tNewPos.vZ * *(float *)(v27 + 4)
                                + *((float *)&igi2_frame.tNewPos.vX + 1) * *(float *)v27
                                + igi2_frame.v36 * *(float *)(v27 + 8);
  igi2_frame.Real32x9_Multiply_tTemp.tX.vZ = *((float *)&igi2_frame.tNewPos.vZ + 1) * *(float *)(v27 + 4)
                                + *(float *)&igi2_frame.tNewPos.vY * *(float *)v27
                                + v26 * *(float *)(v27 + 8);
  igi2_frame.Real32x9_Multiply_tTemp.tY.vX = igi2_frame.v35 * *(float *)(v27 + 20)
                                + *(float *)&igi2_frame.tNewPos.vX * *(float *)(v27 + 12)
                                + *((float *)&igi2_frame.tNewPos.vY + 1) * *(float *)(v27 + 16);
  igi2_frame.Real32x9_Multiply_tTemp.tY.vY = igi2_frame.v36 * *(float *)(v27 + 20)
                                + *((float *)&igi2_frame.tNewPos.vX + 1) * *(float *)(v27 + 12)
                                + *(float *)&igi2_frame.tNewPos.vZ * *(float *)(v27 + 16);
  igi2_frame.Real32x9_Multiply_tTemp.tY.vZ = v26 * *(float *)(v27 + 20)
                                + *(float *)&igi2_frame.tNewPos.vY * *(float *)(v27 + 12)
                                + *((float *)&igi2_frame.tNewPos.vZ + 1) * *(float *)(v27 + 16);
  igi2_frame.Real32x9_Multiply_tTemp.tZ.vX = igi2_frame.v35 * *(float *)(v27 + 32)
                                + *(float *)&igi2_frame.tNewPos.vX * *(float *)(v27 + 24)
                                + *((float *)&igi2_frame.tNewPos.vY + 1) * *(float *)(v27 + 28);
  v29 = *(_DWORD *)(v27 + 36);
  igi2_frame.Real32x9_Multiply_tTemp.tZ.vY = igi2_frame.v36 * *(float *)(v27 + 32)
                                + *((float *)&igi2_frame.tNewPos.vX + 1) * *(float *)(v27 + 24)
                                + *(float *)&igi2_frame.tNewPos.vZ * *(float *)(v27 + 28);
  v30 = v26 * *(float *)(v27 + 32) + *(float *)&igi2_frame.tNewPos.vY * *(float *)(v27 + 24);
  v31 = *((float *)&igi2_frame.tNewPos.vZ + 1) * *(float *)(v27 + 28);
  igi2_frame.Real32x9_Multiply_tTemp.nOps = (int)&v28[v29 + 1];
  igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ = v30 + v31;
  qmemcpy(&ptQTask[3].ptPrev, &igi2_frame.Real32x9_Multiply_tTemp, sizeof(struct QTask_s));
}

// source: j/0/vehicles/rudder.c:255  [anchor-mhash]
void __cdecl Rudder_ParseMagicObjParametersHandler(struct QTask_s *ptQTask, void *pxContext)
{
  void *v2; // esi
  int v3; // ebx
  float *v4; // ebp
  struct ArgList_s *v5; // edi
  void *v6; // eax
  struct ArgList_s *v7; // edi
  int v8; // eax

  v2 = pxContext;
  v3 = *((_DWORD *)pxContext + 2);
  v4 = *(float **)pxContext;
  v5 = *((struct ArgList_s **)pxContext + 1);
  if ( v5->isQVM )
  {
    pxContext = nullptr;
    QVM_EvalArg(&pxContext, 4, v5, v3, 1);
    v6 = pxContext;
  }
  else
  {
    v6 = (void *)Expression_EvalInt(v5->aptExpression[v3]);
  }
  *(_DWORD *)v4 = v6;
  v7 = *((struct ArgList_s **)v2 + 1);
  v8 = v3 + 1;
  if ( v7->isQVM )
  {
    pxContext = nullptr;
    QVM_EvalArg(&pxContext, 4, v7, v8, 2);
    *((_DWORD *)v4 + 1) = pxContext;
  }
  else
  {
    v4[1] = Expression_EvalFloat(v7->aptExpression[v8]);
  }
}

// source: j/0/vehicles/rudder.c:278  [size]
void __cdecl Rudder_GetMagicObjParameterSizeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = 8;
}

// source: j/0/vehicles/rudder.c:294  [anchor-strings]
void __cdecl Rudder_UpdateTagItemsHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // eax
  int v3; // ebx
  struct QTask_s *v4; // edi
  int v5; // ebp
  struct QTask_s *v6; // eax
  double v7; // st7
  struct QTask_s *v8; // esi
  struct QTask_s *v9; // eax
  struct QTask_s *v10; // eax
  struct QTask_s *v11; // ecx
  char ptNext; // dl

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
  v6 = TagItem_Find(*(struct QTask_s **)pxContext, (char *)&stru_694424.tQTaskRefList.ptMiddle);
  if ( v6
    || (v6 = TagItem_NewReal32MinMax(v4, (char *)&stru_694424.tQTaskRefList.ptMiddle, 10.0, 0.0, 360.0)) != nullptr )
  {
    v7 = *(float *)&v6[7].tQTaskRefList.ptHead;
  }
  else
  {
    v7 = 0.0;
  }
  *(float *)(v5 + 4) = v7;
  v8 = *(struct QTask_s **)pxContext;
  v9 = TagItem_Find(*(struct QTask_s **)pxContext, (char *)&stru_694424);
  if ( v9 )
  {
    *(_DWORD *)v5 = v9[7].tQTaskRefList.ptHead;
  }
  else
  {
    v10 = QTask_NewFn(v8, TagItem_eInt32QTaskType, nullptr);
    v11 = &stru_694424;
    do
    {
      ptNext = (char)v11->ptNext;
      *((_BYTE *)&v11[1].ptNext + ((char *)v10 - (char *)&stru_694424)) = v11->ptNext;
      v11 = (struct QTask_s *)((char *)v11 + 1);
    }
    while ( ptNext );
    v10[7].tQTaskRefList.ptHead = nullptr;
    *(_DWORD *)v5 = v10[7].tQTaskRefList.ptHead;
  }
}

// source: j/0/vehicles/rudder.c:327  [anchor-strings]
void __cdecl Rudder_Open()
{
  unsigned __int16 v0; // si
  _DWORD *v1; // esi
  _DWORD *v2; // esi
  _DWORD *v3; // esi
  _DWORD *v4; // esi
  _DWORD *v5; // esi

  v0 = QTask_NewQTaskType("Rudder", 336, RigidMagicObj_eQTaskType, 0, 0);
  Rudder_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 0, Rudder_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, Rudder_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, Rudder_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v0, MagicObj_eUpdateMagicObjEvent, Rudder_UpdateMagicObjHandler);
  QTask_LinkQTaskEventHandlerFn(v0, MagicObj_eGetParseMagicObjParametersEvent, Rudder_ParseMagicObjParametersHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    MagicObj_eGetMagicObjParameterSizeEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Rudder_GetMagicObjParameterSizeHandler);
  QTask_LinkQTaskEventHandlerFn(v0, MagicObjConfig_eUpdateTagItemsQTaskEvent, Rudder_UpdateTagItemsHandler);
  Symbol_Register(
    "TASKTYPE_RUDDER",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)v0,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  v1 = Mem_AllocFn(18444, 4);
  v1[1] = 0;
  *v1 = 0;
  v1[4610] = "TASKTYPE_RUDDER";
  Wildcard_CreateNFA("TASKTYPE_RUDDER", v1 + 2, (char *)v1 + 10248);
  List_AddTail(v1, (int)&MagicObjConfig_tTaskTypeEnumList);
  Symbol_Register(
    "RUDDER_TAILERON_LEFT",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)1,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "RUDDER_TAILERON_RIGHT",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)2,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "RUDDER_AILERON",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    nullptr,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "RUDDER_GAMMA",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)3,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Rudder_tRudderTypeEnumList.pfEnumItemsCallback = ParameterEnumList_EnumerateItemsCallback;
  Rudder_tRudderTypeEnumList.ptHead = (struct ParameterEnumItem_s *)&Rudder_tRudderTypeEnumList.ptMiddle;
  Rudder_tRudderTypeEnumList.ptTail = (struct ParameterEnumItem_s *)&Rudder_tRudderTypeEnumList;
  Rudder_tRudderTypeEnumList.ptMiddle = nullptr;
  v2 = Mem_AllocFn(18444, 4);
  v2[1] = 0;
  *v2 = 0;
  v2[4610] = "RUDDER_TAILERON_LEFT";
  Wildcard_CreateNFA("RUDDER_TAILERON_LEFT", v2 + 2, (char *)v2 + 10248);
  List_AddTail(v2, (int)&Rudder_tRudderTypeEnumList);
  v3 = Mem_AllocFn(18444, 4);
  v3[1] = 0;
  *v3 = 0;
  v3[4610] = "RUDDER_TAILERON_RIGHT";
  Wildcard_CreateNFA("RUDDER_TAILERON_RIGHT", v3 + 2, (char *)v3 + 10248);
  List_AddTail(v3, (int)&Rudder_tRudderTypeEnumList);
  v4 = Mem_AllocFn(18444, 4);
  v4[1] = 0;
  *v4 = 0;
  v4[4610] = "RUDDER_AILERON";
  Wildcard_CreateNFA("RUDDER_AILERON", v4 + 2, (char *)v4 + 10248);
  List_AddTail(v4, (int)&Rudder_tRudderTypeEnumList);
  v5 = Mem_AllocFn(18444, 4);
  v5[1] = 0;
  *v5 = 0;
  v5[4610] = "RUDDER_GAMMA";
  Wildcard_CreateNFA("RUDDER_GAMMA", v5 + 2, (char *)v5 + 10248);
  List_AddTail(v5, (int)&Rudder_tRudderTypeEnumList);
}

// source: j/0/vehicles/rudder.c:373  [size]
void __cdecl Rudder_Close()
{
  ParameterEnumList_DeAlloc(&Rudder_tRudderTypeEnumList);
  QTask_DeleteQTaskType(Rudder_eQTaskType);
}

// source: j/0/vehicles/rudder.c:390  [size]
unsigned __int16 __cdecl Rudder_GetQTaskType()
{
  return Rudder_eQTaskType;
}
