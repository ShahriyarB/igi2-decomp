/* h/2/editormagicobj.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/editormagicobj.c:75  [size]
void __cdecl EditorMagicObj_MagicObjEnterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { int nTick; };
    struct { float nTicka; };
    struct { char igi2_o2[4]; float Real32x9_Multiply_tTemp; };
    struct { char igi2_o3[8]; float Real32x9_Multiply_tTemp_4; };
    struct { char igi2_o4[12]; float Real32x9_Multiply_tTemp_8; };
    struct { char igi2_o5[16]; float Real32x9_Multiply_tTemp_12; };
    struct { char igi2_o6[20]; float Real32x9_Multiply_tTemp_16; };
    struct { char igi2_o7[24]; float Real32x9_Multiply_tTemp_20; };
    struct { char igi2_o8[36]; float Real32x9_Multiply_tTemp_32; };
    struct { char igi2_o9[44]; struct real32x9_t tRotation; };
    char igi2_extent[88];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptHead; // ecx
  struct QTask_s *ptPrev; // edi
  int v5; // esi
  long double v6; // st7
  long double v7; // rt0
  double v8; // st6
  double v9; // st6
  long double v10; // st7
  double v11; // st6
  char *v12; // ecx
  int v13; // edx
  double v14; // st7
  double v15; // st6
  float ptQTaska = *(float *)&ptQTask; // [esp+68h] [ebp+4h] ARGSLOT

  ptHead = ptQTask[8].tQTaskChildren.ptHead;
  ptPrev = ptHead->ptPrev;
  v5 = (char *)ptHead->tQTaskChildren.ptHead - (char *)ptPrev;
  igi2_frame.nTick = 0;
  if ( v5 )
    igi2_frame.nTick = (int)ptPrev + 0 % v5;
  v6 = (double)igi2_frame.nTick * *(float *)&ptHead->ptNext;
  v7 = sin(v6);
  ptQTaska = cos(v6);
  igi2_frame.tRotation.tX.vY = -v7;
  v8 = *(float *)&ptQTask[4].tQTaskChildren.ptMiddle * 0.0;
  igi2_frame.Real32x9_Multiply_tTemp = v7 * *(float *)&ptQTask[4].tQTaskChildren.ptHead
                          + ptQTaska * *(float *)&ptQTask[4].ptPrev
                          + v8;
  igi2_frame.Real32x9_Multiply_tTemp_4 = ptQTaska * *(float *)&ptQTask[4].tQTaskChildren.ptHead
                            + igi2_frame.tRotation.tX.vY * *(float *)&ptQTask[4].ptPrev
                            + v8;
  igi2_frame.Real32x9_Multiply_tTemp_8 = (*(float *)&ptQTask[4].ptPrev + *(float *)&ptQTask[4].tQTaskChildren.ptHead) * 0.0
                            + *(float *)&ptQTask[4].tQTaskChildren.ptMiddle;
  v9 = *(float *)&ptQTask[4].tQTaskRefList.ptMiddle * 0.0;
  igi2_frame.Real32x9_Multiply_tTemp_12 = ptQTaska * *(float *)&ptQTask[4].tQTaskChildren.ptTail
                             + v7 * *(float *)&ptQTask[4].tQTaskRefList.ptHead
                             + v9;
  igi2_frame.Real32x9_Multiply_tTemp_16 = igi2_frame.tRotation.tX.vY * *(float *)&ptQTask[4].tQTaskChildren.ptTail
                             + ptQTaska * *(float *)&ptQTask[4].tQTaskRefList.ptHead
                             + v9;
  igi2_frame.Real32x9_Multiply_tTemp_20 = (*(float *)&ptQTask[4].tQTaskChildren.ptTail + *(float *)&ptQTask[4].tQTaskRefList.ptHead)
                             * 0.0
                             + *(float *)&ptQTask[4].tQTaskRefList.ptMiddle;
  igi2_frame.nTicka = *(float *)&ptQTask[4].eQTaskType * 0.0;
  v10 = v7 * *(float *)&ptQTask[4].ptParent + ptQTaska * *(float *)&ptQTask[4].tQTaskRefList.ptTail + igi2_frame.nTicka;
  v11 = ptQTaska * *(float *)&ptQTask[4].ptParent
      + igi2_frame.tRotation.tX.vY * *(float *)&ptQTask[4].tQTaskRefList.ptTail
      + igi2_frame.nTicka;
  v12 = (char *)&ptQTask[5].ptNext->ptNext + 1;
  igi2_frame.Real32x9_Multiply_tTemp_32 = (*(float *)&ptQTask[4].ptParent + *(float *)&ptQTask[4].tQTaskRefList.ptTail) * 0.0
                             + *(float *)&ptQTask[4].eQTaskType;
  igi2_frame.tRotation.tX.vX = igi2_frame.Real32x9_Multiply_tTemp_12 * *((float *)pxContext + 7)
                  + v10 * *((float *)pxContext + 8)
                  + igi2_frame.Real32x9_Multiply_tTemp * *((float *)pxContext + 6);
  igi2_frame.tRotation.tX.vY = igi2_frame.Real32x9_Multiply_tTemp_16 * *((float *)pxContext + 7)
                  + v11 * *((float *)pxContext + 8)
                  + igi2_frame.Real32x9_Multiply_tTemp_4 * *((float *)pxContext + 6);
  igi2_frame.tRotation.tX.vZ = igi2_frame.Real32x9_Multiply_tTemp_20 * *((float *)pxContext + 7)
                  + igi2_frame.Real32x9_Multiply_tTemp_32 * *((float *)pxContext + 8)
                  + igi2_frame.Real32x9_Multiply_tTemp_8 * *((float *)pxContext + 6);
  igi2_frame.tRotation.tY.vX = v10 * *((float *)pxContext + 11)
                  + igi2_frame.Real32x9_Multiply_tTemp * *((float *)pxContext + 9)
                  + igi2_frame.Real32x9_Multiply_tTemp_12 * *((float *)pxContext + 10);
  igi2_frame.tRotation.tY.vY = v11 * *((float *)pxContext + 11)
                  + igi2_frame.Real32x9_Multiply_tTemp_4 * *((float *)pxContext + 9)
                  + igi2_frame.Real32x9_Multiply_tTemp_16 * *((float *)pxContext + 10);
  igi2_frame.tRotation.tY.vZ = igi2_frame.Real32x9_Multiply_tTemp_32 * *((float *)pxContext + 11)
                  + igi2_frame.Real32x9_Multiply_tTemp_8 * *((float *)pxContext + 9)
                  + igi2_frame.Real32x9_Multiply_tTemp_20 * *((float *)pxContext + 10);
  igi2_frame.tRotation.tZ.vX = igi2_frame.Real32x9_Multiply_tTemp_12 * *((float *)pxContext + 13)
                  + v10 * *((float *)pxContext + 14)
                  + igi2_frame.Real32x9_Multiply_tTemp * *((float *)pxContext + 12);
  v13 = RigidDynCubeObj_eQTaskType;
  igi2_frame.tRotation.tZ.vY = igi2_frame.Real32x9_Multiply_tTemp_16 * *((float *)pxContext + 13)
                  + v11 * *((float *)pxContext + 14)
                  + igi2_frame.Real32x9_Multiply_tTemp_4 * *((float *)pxContext + 12);
  v14 = igi2_frame.Real32x9_Multiply_tTemp_20 * *((float *)pxContext + 13)
      + igi2_frame.Real32x9_Multiply_tTemp_32 * *((float *)pxContext + 14);
  v15 = igi2_frame.Real32x9_Multiply_tTemp_8 * *((float *)pxContext + 12);
  igi2_frame.tRotation.nOps = (int)&v12[*((_DWORD *)pxContext + 15) + 1];
  igi2_frame.tRotation.tZ.vZ = v14 + v15;
  qmemcpy(&ptQTask[3].ptPrev, &igi2_frame.tRotation, sizeof(struct QTask_s));
  ((void (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[5][v13].pfHandler)(ptQTask, 0);
}

// source: h/2/editormagicobj.c:130  [anchor-mhash]
void __cdecl EditorMagicObj_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  double v3; // st7
  double v4; // st7
  int *v5; // eax
  int v6; // eax
  double v7; // st6
  float ptDynCubeObj; // [esp+0h] [ebp-18h]
  struct LODVirModel_s *pxContexta = *(struct LODVirModel_s * *)&pxContext; // [esp+20h] [ebp+8h] ARGSLOT

  pxContexta = MTP_GetLODVirModelExistsFn(*(char **)pxContext);
  if ( !pxContexta )
    pxContexta = nullptr;
  ModelObj_Init((struct ModelObj_s *)ptQTask, *((struct World_s **)pxContext + 1), pxContexta);
  ptQTask[7].tQTaskChildren.ptHead = nullptr;
  ptQTask[7].tQTaskChildren.ptMiddle = (struct QTask_s *)2;
  ptQTask[7].tQTaskRefList.ptHead = nullptr;
  ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[7].tQTaskRefList.ptTail = nullptr;
  ptQTask[7].ptParent = nullptr;
  *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
    v3 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  else
    v3 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  if ( v3 >= *(float *)&ptQTask[6].ptPrev )
  {
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
      v4 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v4 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  }
  else
  {
    v4 = *(float *)&ptQTask[6].ptPrev;
  }
  v5 = *(int **)&ptQTask[2].eQTaskType;
  if ( v5 && (v6 = *v5) != 0 )
    v7 = *(float *)(*(_DWORD *)(*(_DWORD *)(v6 + 12) + 12) + 120);
  else
    v7 = 1.0;
  ptDynCubeObj = v4 * v7;
  World_RegisterDynCubeObjFirstTimeRadius(
    *((struct World_s **)pxContext + 1),
    (struct DynCubeObj_s *)ptQTask,
    (struct real64x3_t *)((char *)pxContext + 8),
    ptDynCubeObj,
    (enum DynCubeTreeCategory_enum)ptQTask[7].tQTaskChildren.ptMiddle);
  qmemcpy(&ptQTask[3].ptPrev, (char *)pxContext + 44, sizeof(struct QTask_s));
  ptQTask[8].ptNext = *((struct QTask_s **)pxContext + 31);
  ModelObj_AttachToParent((struct ModelObj_s *)ptQTask, (struct MagicObjCreateContext_s *)pxContext);
  if ( pxContexta )
  {
    if ( pxContexta != *(struct LODVirModel_s **)&ptQTask[2].eQTaskType )
    {
      ModelObj_SetLODVirModel((struct ModelObj_s *)ptQTask, pxContexta, false);
      ptQTask[7].tQTaskRefList.ptHead = nullptr;
      ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
      ptQTask[7].tQTaskRefList.ptTail = nullptr;
      ptQTask[7].ptParent = nullptr;
      *(_DWORD *)&ptQTask[7].eQTaskType = 0;
    }
    ptQTask[8].tQTaskChildren.ptHead = *((struct QTask_s **)pxContext + 38);
  }
  else
  {
    ptQTask[8].tQTaskChildren.ptHead = *((struct QTask_s **)pxContext + 38);
  }
}

// source: h/2/editormagicobj.c:193  [size]
void __cdecl EditorMagicObj_DeleteHandler(struct QTask_s *ptQTask)
{
  World_RemoveDynCubeObj((struct World_s *)ptQTask[2].ptParent, (struct DynCubeObj_s *)ptQTask);
}

// source: h/2/editormagicobj.c:213  [anchor-mhash]
void __cdecl EditorMagicObj_ParseMagicObjParametersHandler(struct QTask_s *ptQTask, void *pxContext)
{
  void *v2; // ebx
  int v3; // ebp
  int v4; // esi
  struct ArgList_s *v5; // edi
  double v6; // st7
  struct ArgList_s *v7; // edi
  int v8; // esi
  void *v9; // eax
  struct ArgList_s *v10; // edi
  int v11; // eax

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
    v9 = pxContext;
  }
  else
  {
    v9 = (void *)Expression_EvalInt(v7->aptExpression[v8]);
  }
  *(_DWORD *)(v3 + 4) = v9;
  v10 = *((struct ArgList_s **)v2 + 1);
  v11 = v8 + 1;
  if ( v10->isQVM )
  {
    *(float *)&pxContext = 0.0;
    QVM_EvalArg(&pxContext, 4, v10, v11, 1);
    *(float *)(v3 + 8) = *(float *)&pxContext;
  }
  else
  {
    *(_DWORD *)(v3 + 8) = Expression_EvalInt(v10->aptExpression[v11]);
  }
}

// source: h/2/editormagicobj.c:238  [size]
void __cdecl EditorMagicObj_GetMagicObjParameterSizeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = 12;
}

// source: h/2/editormagicobj.c:256  [anchor-strings]
void __cdecl EditorMagicObj_UpdateTagItemsHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v3; // eax
  int v4; // esi
  struct QTask_s *v5; // edi
  struct QTask_s *v6; // eax
  char *v7; // ecx
  char v8; // dl
  struct QTask_s *v9; // edi
  struct QTask_s *v10; // ebx
  struct QTask_s *v11; // eax
  char *v12; // ecx
  char v13; // dl
  struct QTask_s *v14; // edi
  struct QTask_s *v15; // eax
  char *v16; // ecx
  char v17; // dl
  struct QReference_s *ptHead; // esi
  struct QReference_s *v19; // edi
  struct QReference_s **v20; // eax
  struct QReference_s *tEditorMagicObjParameters; // [esp+10h] [ebp-Ch]
  struct QTask_s *pxContexta = *(struct QTask_s * *)&pxContext; // [esp+24h] [ebp+8h] ARGSLOT

  v3 = *(_DWORD *)(*((_DWORD *)pxContext + 1) + 80);
  if ( v3 )
  {
    v4 = *(_DWORD *)((v3 - 4) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v4);
    memset(*(void **)(v4 + 8), 0xCDu, *(_DWORD *)(v4 + 16));
    free((void *)v4);
    *(_DWORD *)(*((_DWORD *)pxContext + 1) + 80) = 0;
  }
  v5 = *(struct QTask_s **)pxContext;
  pxContexta = TagItem_Find(*(struct QTask_s **)pxContext, "EDITORMAGICOBJ - First Frame");
  if ( !pxContexta )
  {
    v6 = QTask_NewFn(v5, TagItem_eInt32QTaskType, nullptr);
    v7 = "EDITORMAGICOBJ - First Frame";
    do
    {
      v8 = *v7;
      v7[(char *)v6 - "EDITORMAGICOBJ - First Frame" + 40] = *v7;
      ++v7;
    }
    while ( v8 );
    v6[7].tQTaskRefList.ptHead = nullptr;
    pxContexta = v6;
  }
  v9 = *(struct QTask_s **)pxContext;
  v10 = TagItem_Find(*(struct QTask_s **)pxContext, "EDITORMAGICOBJ - Last Frame");
  if ( !v10 )
  {
    v11 = QTask_NewFn(v9, TagItem_eInt32QTaskType, nullptr);
    v12 = "EDITORMAGICOBJ - Last Frame";
    do
    {
      v13 = *v12;
      v12[(char *)v11 - "EDITORMAGICOBJ - Last Frame" + 40] = *v12;
      ++v12;
    }
    while ( v13 );
    v11[7].tQTaskRefList.ptHead = nullptr;
    v10 = v11;
  }
  v14 = *(struct QTask_s **)pxContext;
  v15 = TagItem_Find(*(struct QTask_s **)pxContext, "EDITORMAGICOBJ - Rotation Speed");
  if ( !v15 )
  {
    v15 = QTask_NewFn(v14, TagItem_eReal32QTaskType, nullptr);
    v16 = "EDITORMAGICOBJ - Rotation Speed";
    do
    {
      v17 = *v16;
      v16[(char *)v15 - "EDITORMAGICOBJ - Rotation Speed" + 40] = *v16;
      ++v16;
    }
    while ( v17 );
    v15[7].tQTaskRefList.ptHead = nullptr;
  }
  ptHead = pxContexta[7].tQTaskRefList.ptHead;
  v19 = v10[7].tQTaskRefList.ptHead;
  tEditorMagicObjParameters = v15[7].tQTaskRefList.ptHead;
  *(_DWORD *)(*((_DWORD *)pxContext + 1) + 80) = Mem_AllocFn(12, 4);
  v20 = *(struct QReference_s ***)(*((_DWORD *)pxContext + 1) + 80);
  *v20 = tEditorMagicObjParameters;
  v20[1] = ptHead;
  v20[2] = v19;
}

// source: h/2/editormagicobj.c:323  [anchor-strings]
void __cdecl EditorMagicObj_Open()
{
  unsigned __int16 v0; // si
  _DWORD *v1; // esi

  v0 = QTask_NewQTaskType("EditorMagicObj", 336, RigidMagicObj_eQTaskType, 0, 0);
  EditorMagicObj_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 0, EditorMagicObj_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, EditorMagicObj_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    MagicObj_eGetParseMagicObjParametersEvent,
    EditorMagicObj_ParseMagicObjParametersHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    MagicObj_eGetMagicObjParameterSizeEvent,
    (void (__cdecl *)(struct QTask_s *, void *))EditorMagicObj_GetMagicObjParameterSizeHandler);
  QTask_LinkQTaskEventHandlerFn(v0, MagicObj_eMagicObjEnterEvent, EditorMagicObj_MagicObjEnterHandler);
  QTask_LinkQTaskEventHandlerFn(v0, MagicObjConfig_eUpdateTagItemsQTaskEvent, EditorMagicObj_UpdateTagItemsHandler);
  QTask_LinkQTaskEventHandlerFn(v0, QCube_eGetClosestVertexQTaskEvent, nullptr);
  QTask_LinkQTaskEventHandlerFn(v0, 10, nullptr);
  QTask_LinkQTaskEventHandlerFn(v0, 11, nullptr);
  QTask_LinkQTaskEventHandlerFn(v0, 12, nullptr);
  Symbol_Register(
    "TASKTYPE_EDITORMAGICOBJ",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)v0,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  v1 = Mem_AllocFn(18444, 4);
  v1[1] = 0;
  *v1 = 0;
  v1[4610] = "TASKTYPE_EDITORMAGICOBJ";
  Wildcard_CreateNFA("TASKTYPE_EDITORMAGICOBJ", v1 + 2, (char *)v1 + 10248);
  List_AddTail(v1, (int)&MagicObjConfig_tTaskTypeEnumList);
}

// source: h/2/editormagicobj.c:373  [size]
void __cdecl EditorMagicObj_Close()
{
  QTask_DeleteQTaskType(EditorMagicObj_eQTaskType);
}

// source: h/2/editormagicobj.c:387  [size]
unsigned __int16 __cdecl EditorMagicObj_GetQTaskType()
{
  return EditorMagicObj_eQTaskType;
}
