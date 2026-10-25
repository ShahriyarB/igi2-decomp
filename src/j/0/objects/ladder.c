/* j/0/objects/ladder.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/objects/ladder.c:46  [anchor-caller]
struct Ladder_s *__cdecl Ladder_UpdateSteps(struct Ladder_s *ptLadder)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real32x3_t tMagicPos0; };
    struct { char igi2_o1[12]; struct real32x3_t tMagicPos1; };
    char igi2_extent[24];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v2; // st7
  struct Ladder_s *result; // eax

  RigidDynCubeObj_GetMagicVertexLocalPos(&ptLadder->tMagicObj.tRigidDynCubeObj, 2u, &igi2_frame.tMagicPos0);
  RigidDynCubeObj_GetMagicVertexLocalPos(&ptLadder->tMagicObj.tRigidDynCubeObj, 3u, &igi2_frame.tMagicPos1);
  v2 = igi2_frame.tMagicPos0.vZ - igi2_frame.tMagicPos1.vZ;
  if ( v2 < 0.0 )
    v2 = -v2;
  result = (struct Ladder_s *)(__int64)(0.0008138020833333334 * v2);
  ptLadder->nSteps = (int)result;
  return result;
}

void __cdecl Ladder_EnterHandler(struct QTask_s *a1, void *a2)
{
  *(_BYTE *)a2 = *((struct QTask_s **)a2 + 2) != a1 && *((struct QTask_s **)a2 + 3) != a1;
}

void __cdecl sub_545E30(struct QTask_s *a1, void *a2)
{
  if ( !a1[8].tQTaskChildren.ptTail )
    ((void (__cdecl *)())QTask_aatQTaskFinalEvent[5][RigidDynCubeObj_eQTaskType].pfHandler)(a1, a2);
}

// source: j/0/objects/ladder.c:111  [anchor-mhash]
void __cdecl Ladder_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  double v2; // st7
  double v3; // st7
  int *v4; // eax
  int v5; // eax
  double v6; // st6
  struct World_s *ptDynCubeObj; // [esp+0h] [ebp-14h]
  float ptDynCubeObja; // [esp+0h] [ebp-14h]

  if ( pxContext )
  {
    ptQTask[8].tQTaskChildren.ptTail = (struct QTask_s *)1;
    qmemcpy(&ptQTask[8].tQTaskRefList.ptMiddle, (char *)pxContext + 8, 0x18u);
    qmemcpy(&ptQTask[9].tQTaskChildren, (char *)pxContext + 44, sizeof(struct QTask_s));
    strncpy((char *)&ptQTask[10].tQTaskChildren, *(char **)pxContext, 0x10u);
    ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][RigidMagicObj_eQTaskType].pfHandler)(
      ptQTask,
      pxContext);
  }
  else
  {
    ptQTask[9].tQTaskChildren.ptHead = (struct QTask_s *)1065353216;
    ptQTask[9].tQTaskRefList.ptMiddle = (struct QReference_s *)1065353216;
    ptQTask[10].ptNext = (struct QTask_s *)1065353216;
    ptDynCubeObj = World_ptActiveWorld;
    ptQTask[8].tQTaskChildren.ptTail = nullptr;
    ptQTask[8].tQTaskRefList.ptMiddle = nullptr;
    ptQTask[8].tQTaskRefList.ptTail = nullptr;
    ptQTask[8].ptParent = nullptr;
    *(_DWORD *)&ptQTask[8].eQTaskType = 0;
    ptQTask[9].ptNext = nullptr;
    ptQTask[9].ptPrev = nullptr;
    ptQTask[9].tQTaskChildren.ptMiddle = nullptr;
    ptQTask[9].tQTaskChildren.ptTail = nullptr;
    ptQTask[9].tQTaskRefList.ptHead = nullptr;
    ptQTask[9].tQTaskRefList.ptTail = nullptr;
    ptQTask[9].ptParent = nullptr;
    *(_DWORD *)&ptQTask[9].eQTaskType = 0;
    ptQTask[10].ptPrev = nullptr;
    LOBYTE(ptQTask[10].tQTaskChildren.ptHead) = 0;
    ModelObj_Init((struct ModelObj_s *)ptQTask, ptDynCubeObj, nullptr);
    ptQTask[7].tQTaskChildren.ptHead = nullptr;
    ptQTask[7].tQTaskChildren.ptMiddle = (struct QTask_s *)2;
    ptQTask[7].tQTaskRefList.ptHead = nullptr;
    ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
    ptQTask[7].tQTaskRefList.ptTail = nullptr;
    ptQTask[7].ptParent = nullptr;
    *(_DWORD *)&ptQTask[7].eQTaskType = 0;
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
    ptDynCubeObja = v3 * v6;
    World_RegisterDynCubeObjFirstTimeRadius(
      World_ptActiveWorld,
      (struct DynCubeObj_s *)ptQTask,
      (struct real64x3_t *)&ptQTask[8].tQTaskRefList.ptMiddle,
      ptDynCubeObja,
      WORLD_DYNCUBETREE_CATEGORY_MOBILE);
  }
  QTaskList_Register(GameFunctions_ptActivateQTaskList, (struct QTaskList_s *)ptQTask);
  ptQTask[8].tQTaskChildren.ptMiddle = (struct QTask_s *)QVector_AddElement(Ladder_ptLadderVector, ptQTask);
  Ladder_UpdateSteps((struct Ladder_s *)ptQTask);
}

// source: j/0/objects/ladder.c:173  [anchor-mhash]
void __cdecl Ladder_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QVector_s *v1; // ecx
  unsigned int v2; // eax
  unsigned int *p_ptMiddle; // ebp
  void **papxElement; // ebx
  unsigned int v5; // edx
  unsigned int v6; // ebx
  bool v7; // cf
  enum bool isStrictOrder; // edi
  void **v9; // ecx

  QTaskList_Remove(GameFunctions_ptActivateQTaskList, ptQTask);
  v1 = Ladder_ptLadderVector;
  v2 = 0;
  p_ptMiddle = (unsigned int *)&ptQTask[8].tQTaskChildren.ptMiddle;
  if ( Ladder_ptLadderVector->tPrivate.nElements )
  {
    papxElement = Ladder_ptLadderVector->tPrivate.papxElement;
    while ( *papxElement != ptQTask )
    {
      ++v2;
      ++papxElement;
      if ( v2 >= Ladder_ptLadderVector->tPrivate.nElements )
        goto LABEL_8;
    }
    if ( ptQTask != (struct QTask_s *)-332 )
      *p_ptMiddle = v2;
  }
LABEL_8:
  v5 = *p_ptMiddle;
  v6 = v1->tPrivate.nElements - 1;
  v7 = *p_ptMiddle < v6;
  v1->tPrivate.nElements = v6;
  if ( v7 )
  {
    isStrictOrder = v1->tPrivate.isStrictOrder;
    v9 = v1->tPrivate.papxElement;
    if ( isStrictOrder )
    {
      memmove(&v9[v5], &v9[v5 + 1], 4 * (v6 - v5));
      World_RemoveDynCubeObj((struct World_s *)ptQTask[2].ptParent, (struct DynCubeObj_s *)ptQTask);
      return;
    }
    v9[v5] = v9[v6];
  }
  World_RemoveDynCubeObj((struct World_s *)ptQTask[2].ptParent, (struct DynCubeObj_s *)ptQTask);
}

// source: j/0/objects/ladder.c:201  [anchor-mhash]
void __cdecl Ladder_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct LODVirModel_s *LODVirModelExistsFn; // eax
  double v3; // st7
  double v4; // st7
  int *v5; // eax
  int v6; // eax
  double v7; // st6
  __int16 v8; // cx
  float ptDynCubeObj; // [esp+0h] [ebp-10h]

  LODVirModelExistsFn = MTP_GetLODVirModelExistsFn((char *)&ptQTask[10].tQTaskChildren);
  if ( LODVirModelExistsFn != *(struct LODVirModel_s **)&ptQTask[2].eQTaskType )
  {
    ModelObj_SetLODVirModel((struct ModelObj_s *)ptQTask, LODVirModelExistsFn, false);
    ptQTask[7].tQTaskRefList.ptHead = nullptr;
    ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
    ptQTask[7].tQTaskRefList.ptTail = nullptr;
    ptQTask[7].ptParent = nullptr;
    *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  }
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
  World_MoveDynCubeObjRadius(
    (struct World_s *)ptQTask[2].ptParent,
    (struct DynCubeObj_s *)ptQTask,
    (struct real64x3_t *)&ptQTask[8].tQTaskRefList.ptMiddle,
    ptDynCubeObj);
  qmemcpy(&ptQTask[3].ptPrev, &ptQTask[9].tQTaskChildren, sizeof(struct QTask_s));
  RigidDynCubeObj_UpdateAttachments((struct RigidDynCubeObj_t *)ptQTask);
  v8 = Attach_eAttachEvent;
  ptQTask[5].tQTaskChildren.ptTail = (struct QTask_s *)-1;
  ptQTask[5].tQTaskRefList.ptHead = nullptr;
  QTask_TriggerQTaskEventParent(ptQTask, v8, &ptQTask[5].tQTaskChildren.ptTail);
  ModelObj_CalcRelativePosAndOrientation((struct ModelObj_s *)ptQTask);
  Ladder_UpdateSteps((struct Ladder_s *)ptQTask);
}

// source: j/0/objects/ladder.c:233  [anchor-mhash]
void __cdecl Ladder_EvaluateActivateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v18; };
    struct { char igi2_o1[4]; struct real32x3_t ptEvalContext; };
    struct { char igi2_o2[16]; struct real32x3_t ptSource1; };
    struct { char igi2_o3[28]; struct QTask_s *v21; };
    struct { char igi2_o4[32]; struct real64x3_t ptPos; };
    struct { char igi2_o5[56]; struct real64x3_t ptEnd; };
    char igi2_extent[84];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct EvaluateActivateContext_t *v2; // esi
  double v3; // st7
  struct real64x3_t *v4; // edi
  double v5; // st6
  double v6; // st5
  double v7; // st4
  bool v8; // c0
  float v9; // ecx
  float v10; // edx
  double v11; // st7
  double v12; // st6
  struct QTask_s *ptNext; // edx
  struct QTask_s *ptPrev; // eax
  int v15; // ecx
  struct QTask_s *ptMiddle; // edx
  _DWORD *v17; // eax

  v2 = (struct EvaluateActivateContext_t *)pxContext;
  v3 = *((double *)pxContext + 1) - *(double *)&ptQTask[1].ptNext;
  v4 = (struct real64x3_t *)((char *)pxContext + 8);
  v5 = *((double *)pxContext + 2) - *(double *)&ptQTask[1].tQTaskChildren.ptHead;
  igi2_frame.v18 = *(float *)pxContext;
  v6 = *((double *)pxContext + 3) - *(double *)&ptQTask[1].tQTaskChildren.ptTail;
  igi2_frame.ptEnd.vX = *(float *)&ptQTask[3].tQTaskRefList.ptTail * v6
           + *(float *)&ptQTask[3].tQTaskChildren.ptTail * v5
           + *(float *)&ptQTask[3].ptPrev * v3;
  v7 = *(float *)&ptQTask[3].tQTaskRefList.ptHead * v5
     + *(float *)&ptQTask[3].ptParent * v6
     + *(float *)&ptQTask[3].tQTaskChildren.ptHead * v3;
  if ( v7 >= 0.0 )
  {
    if ( v7 >= 6144.0 )
      goto LABEL_19;
    v8 = v7 < *((double *)pxContext + 15);
  }
  else
  {
    if ( v7 <= -3072.0 )
      goto LABEL_19;
    v8 = -v7 < *((double *)pxContext + 15);
  }
  if ( v8 && igi2_frame.ptEnd.vX > -2867.2 && igi2_frame.ptEnd.vX < 2867.2 )
  {
    v9 = *((float *)pxContext + 9);
    v10 = *((float *)pxContext + 12);
    igi2_frame.ptEvalContext.vZ = *((float *)pxContext + 15);
    igi2_frame.ptEvalContext.vX = v9;
    igi2_frame.ptEvalContext.vY = v10;
    if ( v7 < 0.0 )
    {
      igi2_frame.ptEvalContext.vX = -igi2_frame.ptEvalContext.vX;
      igi2_frame.ptEvalContext.vY = -igi2_frame.ptEvalContext.vY;
      igi2_frame.ptEvalContext.vZ = -igi2_frame.ptEvalContext.vZ;
    }
    v11 = *(float *)&ptQTask[3].tQTaskChildren.ptHead;
    v12 = *(float *)&ptQTask[3].tQTaskRefList.ptHead;
    LODWORD(igi2_frame.ptSource1.vZ) = ptQTask[3].ptParent;
    igi2_frame.ptSource1.vX = -v11;
    igi2_frame.ptSource1.vY = -v12;
    igi2_frame.ptSource1.vZ = -igi2_frame.ptSource1.vZ;
    GameFunctions_GetMagicVertex(&igi2_frame.ptPos, ptQTask, 1);
    if ( Real32x3_Angle(&igi2_frame.ptEvalContext, &igi2_frame.ptSource1) < 0.7853981852531433
      && *((double *)pxContext + 3) < igi2_frame.ptPos.vZ
      && *((double *)pxContext + 3) > *(double *)&ptQTask[1].tQTaskChildren.ptTail )
    {
      ptNext = ptQTask[1].ptNext;
      ptPrev = ptQTask[1].ptPrev;
      LODWORD(igi2_frame.ptPos.vY) = ptQTask[1].tQTaskChildren.ptHead;
      v15 = *((_DWORD *)pxContext + 7);
      *(_QWORD *)&igi2_frame.ptPos.vX = __PAIR64__((unsigned int)ptPrev, (unsigned int)ptNext);
      ptMiddle = ptQTask[1].tQTaskChildren.ptMiddle;
      HIDWORD(igi2_frame.ptPos.vZ) = v15;
      HIDWORD(igi2_frame.ptPos.vY) = ptMiddle;
      igi2_frame.ptSource1.vZ = *(float *)pxContext;
      LODWORD(igi2_frame.ptPos.vZ) = *((_DWORD *)pxContext + 6);
      igi2_frame.ptSource1.vY = 0.0;
      igi2_frame.v21 = ptQTask;
      if ( !World_LineOfSight(
              Game_ptGame->ptWorld,
              v4,
              &igi2_frame.ptPos,
              AIDetection_eLineOfSightQTaskEvent,
              (struct CollisionEvaluateContext_s *)&igi2_frame.ptSource1,
              Forest_bQTaskGroup | 0x8000000,
              WORLD_DYNCUBETREE_CATEGORY_ALL,
              (struct LineOfSightOutputContext_s *)&igi2_frame.ptEvalContext) )
      {
LABEL_15:
        *((_DWORD *)pxContext + 32) = 0;
        return;
      }
      v17 = pxContext;
      if ( igi2_frame.ptEvalContext.vX != 1.0 )
        goto LABEL_17;
      v2 = (struct EvaluateActivateContext_t *)pxContext;
      *((_DWORD *)pxContext + 28) = 0;
      *((_DWORD *)pxContext + 29) = 0;
      *((_DWORD *)pxContext + 32) = ptQTask;
      *(_BYTE *)(LODWORD(igi2_frame.v18) + 3139) = 0;
    }
  }
LABEL_19:
  GameFunctions_GetMagicVertex(&igi2_frame.ptEnd, ptQTask, 1);
  if ( *(float *)&ptQTask[3].tQTaskRefList.ptHead * (v2->tViewPos.vY - igi2_frame.ptEnd.vY)
     + *(float *)&ptQTask[3].ptParent * (v2->tViewPos.vZ - igi2_frame.ptEnd.vZ)
     + *(float *)&ptQTask[3].tQTaskChildren.ptHead * (v4->vX - igi2_frame.ptEnd.vX) < 0.0
    && GameFunctions_ResolveEvaluateActivate(v2, ptQTask, &igi2_frame.ptEnd) )
  {
    LODWORD(igi2_frame.ptSource1.vZ) = v2->ptQTask;
    igi2_frame.ptSource1.vY = 0.0;
    igi2_frame.v21 = ptQTask;
    if ( !World_LineOfSight(
            Game_ptGame->ptWorld,
            v4,
            &igi2_frame.ptEnd,
            AIDetection_eLineOfSightQTaskEvent,
            (struct CollisionEvaluateContext_s *)&igi2_frame.ptSource1,
            Forest_bQTaskGroup | 0x8000000,
            WORLD_DYNCUBETREE_CATEGORY_ALL,
            (struct LineOfSightOutputContext_s *)&igi2_frame.ptEvalContext) )
      goto LABEL_15;
    v17 = pxContext;
    if ( igi2_frame.ptEvalContext.vX != 1.0 )
    {
LABEL_17:
      v17[32] = 0;
      return;
    }
    *((_DWORD *)pxContext + 28) = 0;
    *((_DWORD *)pxContext + 29) = 0;
    *((_DWORD *)pxContext + 32) = ptQTask;
    *(_BYTE *)(LODWORD(igi2_frame.v18) + 3139) = 1;
  }
}

// source: j/0/objects/ladder.c:396  [size]
void __cdecl Ladder_GetActivateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = 8;
}

// source: j/0/objects/ladder.c:413  [size]
void __cdecl Ladder_ActivateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: j/0/objects/ladder.c:436  [size]
void __cdecl Ladder_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = Ladder_ptParameterList;
}

// source: j/0/objects/ladder.c:454  [anchor-hash]
struct Ladder_s *__cdecl Ladder_GetLadder(int i)
{
  if ( i < 0 || i >= (signed int)Ladder_ptLadderVector->tPrivate.nElements )
    return nullptr;
  else
    return (struct Ladder_s *)Ladder_ptLadderVector->tPrivate.papxElement[i];
}

// source: j/0/objects/ladder.c:474  [size]
unsigned __int16 __cdecl Ladder_GetQTaskType()
{
  return Ladder_eQTaskType;
}

// source: j/0/objects/ladder.c:487  [anchor-strings]
void __cdecl Ladder_Open()
{
  void **v0; // esi
  struct QVector_s *v1; // eax
  unsigned __int16 v2; // cx
  struct ParameterList_s *v3; // eax
  int v4; // edx
  _DWORD *v5; // esi

  Ladder_eQTaskType = QTask_NewQTaskType("Ladder", 424, RigidMagicObj_eQTaskType, 0, 0);
  v0 = (void **)Mem_AllocFn(128, 4);
  v1 = (struct QVector_s *)Mem_AllocFn(24, 4);
  v1->tPrivate.nArraySize = 32;
  v1->tPrivate.nReallocSize = 32;
  v1->tPrivate.papxElement = v0;
  LOWORD(v0) = Ladder_eQTaskType;
  v2 = Ladder_eQTaskType;
  v1->tPrivate.nElements = 0;
  v1->tPrivate.isPrivateMem = false;
  v1->tPrivate.isStrictOrder = true;
  Ladder_ptLadderVector = v1;
  QTask_LinkQTaskEventHandlerFn(v2, 0, Ladder_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn((unsigned __int16)v0, 2, Ladder_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    (unsigned __int16)v0,
    ParameterList_eUpdateInternalDataQTaskEvent,
    Ladder_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    (unsigned __int16)v0,
    GameFunctions_eEvaluateActivateQTaskEvent,
    Ladder_EvaluateActivateHandler);
  QTask_LinkQTaskEventHandlerFn(
    (unsigned __int16)v0,
    GameFunctions_eGetActivateQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Ladder_GetActivateHandler);
  QTask_LinkQTaskEventHandlerFn(
    (unsigned __int16)v0,
    GameFunctions_eActivateQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Ladder_ActivateHandler);
  QTask_LinkQTaskEventHandlerFn(
    (unsigned __int16)v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Ladder_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    (unsigned __int16)v0,
    AIDetection_eLineOfSightQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Ladder_EnterHandler);
  v3 = (struct ParameterList_s *)Mem_AllocFn(72, 4);
  v3->ptParameterListItem = (struct ParameterListItem_s *)&v3[1];
  v4 = Level_eParameterTypeString16;
  v3->nParameters = 0;
  v3->nMaxParameters = 3;
  Ladder_ptParameterList = v3;
  ParameterList_AddParameter(v3, 0x198u, v4, "Model", 7u, nullptr);
  ParameterList_AddParameter(Ladder_ptParameterList, 0x158u, Level_eParameterTypeObjectPos, "Position", 7u, nullptr);
  ParameterList_AddParameter(Ladder_ptParameterList, 0x170u, Level_eParameterTypeReal32x9, "Orientation", 7u, nullptr);
  LOWORD(v0) = Ladder_eQTaskType;
  QTask_LinkQTaskEventHandlerFn(
    Ladder_eQTaskType,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn((unsigned __int16)v0, 5, (void (__cdecl *)(struct QTask_s *, void *))sub_545E30);
  Symbol_Register(
    "TASKTYPE_LADDER",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)(unsigned __int16)v0,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  v5 = Mem_AllocFn(18444, 4);
  v5[1] = 0;
  *v5 = 0;
  v5[4610] = "TASKTYPE_LADDER";
  Wildcard_CreateNFA("TASKTYPE_LADDER", v5 + 2, (char *)v5 + 10248);
  List_AddTail(v5, (int)&MagicObjConfig_tTaskTypeEnumList);
}

// source: j/0/objects/ladder.c:535  [size]
void __cdecl Ladder_Close()
{
  int v0; // esi

  QVector_Delete(Ladder_ptLadderVector);
  if ( Ladder_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&Ladder_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(Ladder_eQTaskType);
}
