/* j/0/objects/wire.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/objects/wire.c:44  [size]
void __cdecl Wire_GetSerializeParameterlistHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = Wire_ptSerializeParameterList;
}

// source: j/0/objects/wire.c:60  [anchor-mhash]
void __cdecl Wire_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[24]; struct real64x3_t tNull; };
    char igi2_extent[52];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v2; // st7
  double v3; // st7
  int *v4; // eax
  int v5; // eax
  double v6; // st6

  memset(&igi2_frame.tNull, 0, sizeof(igi2_frame.tNull));
  QTaskList_Register(GameFunctions_ptActivateQTaskList, (struct QTaskList_s *)ptQTask);
  ModelObj_Init((struct ModelObj_s *)ptQTask, World_ptActiveWorld, nullptr);
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
  igi2_frame.ptDynCubeObj = v3 * v6;
  World_RegisterDynCubeObjFirstTimeRadius(
    World_ptActiveWorld,
    (struct DynCubeObj_s *)ptQTask,
    &igi2_frame.tNull,
    igi2_frame.ptDynCubeObj,
    WORLD_DYNCUBETREE_CATEGORY_STATIONARY);
  ptQTask[8].ptNext = nullptr;
  ptQTask[8].ptPrev = nullptr;
  ptQTask[8].tQTaskChildren.ptHead = nullptr;
  ptQTask[8].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[8].tQTaskChildren.ptTail = nullptr;
  ptQTask[8].tQTaskRefList.ptHead = nullptr;
  ptQTask[8].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[8].tQTaskRefList.ptTail = nullptr;
  ptQTask[8].ptParent = nullptr;
  *(_DWORD *)&ptQTask[8].eQTaskType = 0;
  ptQTask[9].ptNext = nullptr;
  ptQTask[9].ptPrev = nullptr;
  LOBYTE(ptQTask[9].tQTaskChildren.ptHead) = 0;
  LOBYTE(ptQTask[9].tQTaskRefList.ptMiddle) = 0;
  BYTE1(ptQTask[9].tQTaskRefList.ptMiddle) = 0;
  BYTE2(ptQTask[9].tQTaskRefList.ptMiddle) = 0;
  ptQTask[9].tQTaskRefList.ptTail = nullptr;
  ptQTask[9].ptParent = nullptr;
  *(_DWORD *)&ptQTask[9].eQTaskType = 0;
  ptQTask[11].tQTaskRefList.ptMiddle = nullptr;
}

// source: j/0/objects/wire.c:108  [size]
void __cdecl Wire_RunHandler(struct QTask_s *ptQTask)
{
  BYTE1(ptQTask[9].tQTaskRefList.ptMiddle) = ptQTask[9].tQTaskRefList.ptMiddle;
}

// source: j/0/objects/wire.c:128  [anchor-mhash]
void __cdecl Wire_DeleteHandler(struct QTask_s *ptQTask)
{
  int v1; // eax
  struct QReference_s *v2; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *); // eax

  QTaskList_Remove(GameFunctions_ptActivateQTaskList, ptQTask);
  v1 = 0;
  while ( 1 )
  {
    v2 = Level_atLevelQTaskID[v1];
    if ( v2 )
    {
      if ( v2->pxObject == ptQTask )
        break;
    }
    if ( ++v1 >= 4096 )
      goto LABEL_9;
  }
  if ( v1 >= 0 )
  {
    pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Level_eRemoveLevelScriptSymbolsEvent][ptQTask->eQTaskType].pfHandler;
    if ( pfHandler )
      pfHandler(ptQTask);
  }
LABEL_9:
  World_RemoveDynCubeObj((struct World_s *)ptQTask[2].ptParent, (struct DynCubeObj_s *)ptQTask);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[9].tQTaskRefList.ptTail);
}

// source: j/0/objects/wire.c:158  [size]
void __cdecl Wire_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = Wire_ptParameterList;
}

// source: j/0/objects/wire.c:174  [anchor-mhash]
void __cdecl Wire_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[20]; long double vLen; };
    struct { char igi2_o2[32]; struct real32x3_t tDirection; };
    struct { char igi2_o3[44]; struct real32x9_t tDelta; };
    char igi2_extent[88];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v2; // st7
  double v3; // st6
  struct LODVirModel_s *LODVirModelExistsFn; // eax
  double v5; // st5
  double v6; // rt0
  double v7; // st7
  double v8; // st7
  int *v9; // eax
  int v10; // eax
  double v11; // st6

  v2 = *(double *)&ptQTask[8].tQTaskRefList.ptMiddle - *(double *)&ptQTask[8].ptNext;
  *(double *)&igi2_frame.tDelta.tX.vZ = *(double *)&ptQTask[8].ptParent - *(double *)&ptQTask[8].tQTaskChildren.ptHead;
  v3 = *(double *)&ptQTask[9].ptNext - *(double *)&ptQTask[8].tQTaskChildren.ptTail;
  igi2_frame.vLen = sqrt(v2 * v2 + *(double *)&igi2_frame.tDelta.tX.vZ * *(double *)&igi2_frame.tDelta.tX.vZ + v3 * v3);
  *(double *)&igi2_frame.tDelta.tX.vX = 1.0 / igi2_frame.vLen * v2;
  *(double *)&igi2_frame.tDelta.tX.vZ = *(double *)&igi2_frame.tDelta.tX.vZ * (1.0 / igi2_frame.vLen);
  igi2_frame.tDirection.vX = *(double *)&igi2_frame.tDelta.tX.vX;
  igi2_frame.tDirection.vY = *(double *)&igi2_frame.tDelta.tX.vZ;
  igi2_frame.tDirection.vZ = 1.0 / igi2_frame.vLen * v3;
  GameFunctions_CreateOrientationFromDirection(&igi2_frame.tDelta, &igi2_frame.tDirection);
  *(float *)&ptQTask[6].tQTaskChildren.ptHead = igi2_frame.vLen * 0.000244140625;
  qmemcpy(&ptQTask[3].ptPrev, &igi2_frame.tDelta, sizeof(struct QTask_s));
  LODVirModelExistsFn = MTP_GetLODVirModelExistsFn((char *)&ptQTask[9].tQTaskChildren);
  if ( LODVirModelExistsFn != *(struct LODVirModel_s **)&ptQTask[2].eQTaskType )
  {
    ModelObj_SetLODVirModel((struct ModelObj_s *)ptQTask, LODVirModelExistsFn, false);
    ptQTask[7].tQTaskRefList.ptHead = nullptr;
    ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
    ptQTask[7].tQTaskRefList.ptTail = nullptr;
    ptQTask[7].ptParent = nullptr;
    *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  }
  v5 = *(double *)&ptQTask[9].ptNext + *(double *)&ptQTask[8].tQTaskChildren.ptTail;
  v6 = *(double *)&ptQTask[8].ptParent + *(double *)&ptQTask[8].tQTaskChildren.ptHead;
  *(double *)&igi2_frame.tDelta.tX.vX = (*(double *)&ptQTask[8].tQTaskRefList.ptMiddle + *(double *)&ptQTask[8].ptNext) * 0.5;
  *(double *)&igi2_frame.tDelta.tX.vZ = v6 * 0.5;
  *(double *)&igi2_frame.tDelta.tY.vY = v5 * 0.5;
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
  World_MoveDynCubeObjRadius(
    (struct World_s *)ptQTask[2].ptParent,
    (struct DynCubeObj_s *)ptQTask,
    (struct real64x3_t *)&igi2_frame.tDelta,
    igi2_frame.ptDynCubeObj);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[9].tQTaskRefList.ptTail, ptQTask);
}

// source: j/0/objects/wire.c:253  [anchor-mhash]
void __cdecl Wire_EvaluateActivateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real32x3_t tMagicPos0; };
    struct { char igi2_o1[12]; struct real64x3_t tPos; };
    struct { char igi2_o2[36]; struct real64x3_t Real64x3_RotateInverse_tTemp; };
    struct { char igi2_o3[60]; struct real64x3_t tDelta; };
    struct { char igi2_o4[84]; struct real32x9_t tOrientation; };
    char igi2_extent[128];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v2; // st7
  double v3; // st5
  double vY; // st7
  struct LevelExpression_s *p_ptTail; // eax
  bool v6; // zf

  Wire_GetOrientation(&igi2_frame.tOrientation, ptQTask);
  v2 = *((double *)pxContext + 1) - *(double *)&ptQTask[1].ptNext;
  igi2_frame.tDelta.vY = *((double *)pxContext + 2) - *(double *)&ptQTask[1].tQTaskChildren.ptHead;
  v3 = *((double *)pxContext + 3) - *(double *)&ptQTask[1].tQTaskChildren.ptTail;
  igi2_frame.Real64x3_RotateInverse_tTemp.vX = igi2_frame.tOrientation.tZ.vX * v3 + igi2_frame.tOrientation.tY.vX * igi2_frame.tDelta.vY + igi2_frame.tOrientation.tX.vX * v2;
  igi2_frame.Real64x3_RotateInverse_tTemp.vY = igi2_frame.tOrientation.tZ.vY * v3 + igi2_frame.tOrientation.tY.vY * igi2_frame.tDelta.vY + igi2_frame.tOrientation.tX.vY * v2;
  igi2_frame.Real64x3_RotateInverse_tTemp.vZ = igi2_frame.tOrientation.tZ.vZ * v3 + igi2_frame.tOrientation.tY.vZ * igi2_frame.tDelta.vY + igi2_frame.tOrientation.tX.vZ * v2;
  qmemcpy(&igi2_frame.tDelta, &igi2_frame.Real64x3_RotateInverse_tTemp, sizeof(igi2_frame.tDelta));
  GameFunctions_GetMagicVertexLocal(&igi2_frame.tMagicPos0, ptQTask, 0);
  GameFunctions_GetMagicVertexLocal((struct real32x3_t *)&igi2_frame.tPos, ptQTask, 1);
  if ( igi2_frame.tMagicPos0.vY <= igi2_frame.Real64x3_RotateInverse_tTemp.vY )
  {
    if ( *((float *)&igi2_frame.tPos.vX + 1) >= igi2_frame.Real64x3_RotateInverse_tTemp.vY )
      vY = igi2_frame.tDelta.vY;
    else
      vY = *((float *)&igi2_frame.tPos.vX + 1);
  }
  else
  {
    vY = igi2_frame.tMagicPos0.vY;
  }
  p_ptTail = (struct LevelExpression_s *)&ptQTask[9].tQTaskRefList.ptTail;
  igi2_frame.Real64x3_RotateInverse_tTemp.vX = (igi2_frame.tOrientation.tX.vZ + igi2_frame.tOrientation.tX.vX) * 0.0 + igi2_frame.tOrientation.tX.vY * vY;
  igi2_frame.Real64x3_RotateInverse_tTemp.vY = (igi2_frame.tOrientation.tY.vZ + igi2_frame.tOrientation.tY.vX) * 0.0 + igi2_frame.tOrientation.tY.vY * vY;
  igi2_frame.Real64x3_RotateInverse_tTemp.vZ = (igi2_frame.tOrientation.tZ.vZ + igi2_frame.tOrientation.tZ.vX) * 0.0 + igi2_frame.tOrientation.tZ.vY * vY;
  qmemcpy(&igi2_frame.tPos, &igi2_frame.Real64x3_RotateInverse_tTemp, sizeof(igi2_frame.tPos));
  igi2_frame.tPos.vX = igi2_frame.Real64x3_RotateInverse_tTemp.vX + *(double *)&ptQTask[1].ptNext;
  v6 = ptQTask[9].tQTaskRefList.ptTail == nullptr;
  igi2_frame.tPos.vY = igi2_frame.tPos.vY + *(double *)&ptQTask[1].tQTaskChildren.ptHead;
  igi2_frame.tPos.vZ = igi2_frame.tPos.vZ + *(double *)&ptQTask[1].tQTaskChildren.ptTail;
  if ( v6
    || !ptQTask[9].ptParent->ptNext
    || !*(_DWORD *)&ptQTask[9].eQTaskType
    || p_ptTail->zExpression
    && ptQTask[9].ptParent->ptNext
    && *(_DWORD *)&ptQTask[9].eQTaskType
    && Level_RunLevelExpression(p_ptTail, ptQTask) != 0.0 )
  {
    GameFunctions_ResolveEvaluateActivate((struct EvaluateActivateContext_t *)pxContext, ptQTask, &igi2_frame.tPos);
  }
}

// source: j/0/objects/wire.c:320  [size]
void __cdecl Wire_GetActivateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = 7;
}

// source: j/0/objects/wire.c:337  [size]
void __cdecl Wire_ActivateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  LOBYTE(ptQTask[9].tQTaskRefList.ptMiddle) = 1;
}

// source: j/0/objects/wire.c:363  [anchor-refs]
void __cdecl Wire_RegisterScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( !BYTE2(ptQTask[9].tQTaskRefList.ptMiddle) )
  {
    BYTE2(ptQTask[9].tQTaskRefList.ptMiddle) = 1;
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.isInUse", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      &ptQTask[9].tQTaskRefList.ptMiddle,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.isLastInUse", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      (char *)&ptQTask[9].tQTaskRefList.ptMiddle + 1,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
  }
}

// source: j/0/objects/wire.c:396  [anchor-mhash]
void __cdecl Wire_RemoveScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( BYTE2(ptQTask[9].tQTaskRefList.ptMiddle) )
  {
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    BYTE2(ptQTask[9].tQTaskRefList.ptMiddle) = 0;
    sprintf(igi2_frame.zTemp, "%s.isInUse", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.isLastInUse", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    BYTE2(ptQTask[9].tQTaskRefList.ptMiddle) = 0;
  }
}

// source: j/0/objects/wire.c:463  [anchor-callee]
void __cdecl Wire_GetOrientation(struct real32x9_t *ptOrientation, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real64x3_t tMagicPos1; };
    struct { char igi2_o1[24]; struct real64x3_t tDelta; };
    struct { char igi2_o2[48]; struct real64x3_t tMagicPos0; };
    char igi2_extent[72];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  long double v2; // st3

  GameFunctions_GetMagicVertex(&igi2_frame.tMagicPos0, ptQTask, 0);
  GameFunctions_GetMagicVertex(&igi2_frame.tMagicPos1, ptQTask, 1);
  igi2_frame.tDelta.vY = igi2_frame.tMagicPos1.vY - igi2_frame.tMagicPos0.vY;
  v2 = 1.0
     / sqrt(
         igi2_frame.tDelta.vY * igi2_frame.tDelta.vY
       + (igi2_frame.tMagicPos1.vZ - igi2_frame.tMagicPos0.vZ) * (igi2_frame.tMagicPos1.vZ - igi2_frame.tMagicPos0.vZ)
       + (igi2_frame.tMagicPos1.vX - igi2_frame.tMagicPos0.vX) * (igi2_frame.tMagicPos1.vX - igi2_frame.tMagicPos0.vX));
  igi2_frame.tDelta.vX = v2 * (igi2_frame.tMagicPos1.vX - igi2_frame.tMagicPos0.vX);
  igi2_frame.tDelta.vY = igi2_frame.tDelta.vY * v2;
  *(float *)&igi2_frame.tMagicPos1.vX = igi2_frame.tDelta.vX;
  *((float *)&igi2_frame.tMagicPos1.vX + 1) = igi2_frame.tDelta.vY;
  *(float *)&igi2_frame.tMagicPos1.vY = v2 * (igi2_frame.tMagicPos1.vZ - igi2_frame.tMagicPos0.vZ);
  GameFunctions_CreateOrientationFromDirection(ptOrientation, (struct real32x3_t *)&igi2_frame.tMagicPos1);
}

// source: j/0/objects/wire.c:501  [anchor-callee]
enum bool __cdecl Wire_IsSliding(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vAlpha; };
    struct { char igi2_o1[4]; float vGamma; };
    struct { char igi2_o2[8]; float vBeta; };
    struct { char igi2_o3[12]; struct real32x9_t tOrientation; };
    char igi2_extent[56];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v1; // st7

  Wire_GetOrientation(&igi2_frame.tOrientation, ptQTask);
  Real32x9_GetAngles(&igi2_frame.tOrientation, &igi2_frame.vAlpha, &igi2_frame.vBeta, &igi2_frame.vGamma);
  v1 = igi2_frame.vAlpha;
  if ( igi2_frame.vAlpha < 0.0 )
    v1 = -v1;
  return v1 > 0.03490658476948738;
}

// source: j/0/objects/wire.c:539  [size]
unsigned __int16 __cdecl Wire_GetQTaskType()
{
  return Wire_eQTaskType;
}

// source: j/0/objects/wire.c:552  [anchor-strings]
void __cdecl Wire_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // edx

  v0 = QTask_NewQTaskType("Wire", 472, RigidDynCubeObj_eQTaskType, 0, 0);
  Wire_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, Wire_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, (void (__cdecl *)(struct QTask_s *))Wire_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, Wire_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Wire_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, Wire_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(v0, GameFunctions_eEvaluateActivateQTaskEvent, Wire_EvaluateActivateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    GameFunctions_eGetActivateQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Wire_GetActivateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    GameFunctions_eActivateQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Wire_ActivateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    GameFunctions_eObjectCollisionEvaluateQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))GameFunctions_ObjectCollisionEvaluateDiscardHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Level_eRegisterLevelScriptSymbolsEvent, Wire_RegisterScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Level_eRemoveLevelScriptSymbolsEvent, Wire_RemoveScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 9, nullptr);
  QTask_LinkQTaskEventHandlerFn(v0, BulletHole_eCreateBulletHoleTaskEvent, nullptr);
  v1 = (struct ParameterList_s *)Mem_AllocFn(92, 4);
  v2 = Level_eParameterTypeObjectPos;
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  v1->nParameters = 0;
  v1->nMaxParameters = 4;
  Wire_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0x140u, v2, "Start position", 7u, nullptr);
  ParameterList_AddParameter(Wire_ptParameterList, 0x158u, Level_eParameterTypeObjectPos, "Stop position", 7u, nullptr);
  ParameterList_AddParameter(Wire_ptParameterList, 0x170u, Level_eParameterTypeString16, "Model", 7u, nullptr);
  ParameterList_AddParameter(
    Wire_ptParameterList,
    0x184u,
    Level_eParameterTypeVarString,
    "Useable expression",
    7u,
    nullptr);
  QTask_LinkQTaskEventHandlerFn(
    Wire_eQTaskType,
    Serialize_eGetSerializeParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Wire_GetSerializeParameterlistHandler);
  Wire_ptSerializeParameterList = ParameterList_Derive(ModelObjParameters_ptSerializeParameterList, 2);
  ParameterList_AddParameter(Wire_ptSerializeParameterList, 0x180u, Level_eParameterTypebool8, "isInUse", 7u, nullptr);
  ParameterList_AddParameter(
    Wire_ptSerializeParameterList,
    0x181u,
    Level_eParameterTypebool8,
    "isLastInUse",
    7u,
    nullptr);
}

// source: j/0/objects/wire.c:609  [size]
void __cdecl Wire_Close()
{
  int v0; // esi
  int v1; // esi

  if ( Wire_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&Wire_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  if ( Wire_ptSerializeParameterList )
  {
    v1 = *(_DWORD *)((unsigned int)&Wire_ptSerializeParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
  QTask_DeleteQTaskType(Wire_eQTaskType);
}
