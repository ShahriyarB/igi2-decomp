/* j/0/weapons/laserdesignator.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/weapons/laserdesignator.c:83  [anchor-mhash]
struct Result_s *__cdecl LaserDesignator_GetTicksHeldOnTask(
        struct Result_s *retstr,
        void *pxUnused,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // eax
  struct QReference_s *v5; // eax
  struct QTask_s *pxObject; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments
    && (!ptArgList->isQVM
      ? (v4 = (struct ArgList_s *)Expression_EvalInt(*ptArgList->aptExpression))
      : (ptArgList = nullptr, QVM_EvalArg(&ptArgList, 4, v3, 0, 1), v4 = ptArgList),
        (unsigned int)v4 >= 0x1000 || (v5 = Level_atLevelQTaskID[(_DWORD)v4]) == nullptr
      ? (pxObject = nullptr)
      : (pxObject = (struct QTask_s *)v5->pxObject),
        pxObject == LaserDesignator_ptHitQTask) )
  {
    ptArgList = (struct ArgList_s *)(LevelFlow_ptLevelFlow->nTick - LaserDesignator_nTickFirstHit);
    Rs.nResult = (int)ptArgList;
    Rs.vResult = (double)(int)ptArgList;
  }
  else
  {
    Rs.nResult = 0;
    Rs.vResult = 0.0;
  }
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/weapons/laserdesignator.c:107  [size]
void __cdecl LaserDesignator_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  LOBYTE(ptQTask[1].ptPrev) = 0;
  LOBYTE(ptQTask[1].eQTaskType) = 0;
  LOBYTE(ptQTask[2].tQTaskRefList.ptTail) = 0;
  ptQTask[1].ptNext = (struct QTask_s *)1120403456;
  LaserDesignator_ptHitQTask = nullptr;
  LaserDesignator_nTickFirstHit = 0;
}

// source: j/0/weapons/laserdesignator.c:128  [size]
void __cdecl LaserDesignator_DeleteHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: j/0/weapons/laserdesignator.c:143  [size]
void __cdecl LaserDesignator_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = LaserDesignator_ptParameterList;
}

// source: j/0/weapons/laserdesignator.c:161  [size]
void __cdecl LaserDesignator_CreateWeaponTypeParametersHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *((_DWORD *)pxContext + 2) = QTask_NewFn(*((struct QTask_s **)pxContext + 1), LaserDesignator_eQTaskType, nullptr);
}

// source: j/0/weapons/laserdesignator.c:180  [anchor-mhash]
void __cdecl LaserDesignator_GetAnimHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // eax
  char *v3; // ecx
  int v4; // eax

  v2 = *((_DWORD *)pxContext + 3) - 4;
  v3 = *((char **)pxContext + 5);
  *((_DWORD *)pxContext + 6) = 0;
  *((_DWORD *)pxContext + 7) = 1065353216;
  if ( v2 )
  {
    v4 = v2 - 1;
    if ( v4 )
    {
      if ( v4 == 1 )
        *((_DWORD *)pxContext + 6) = Hierarchy_GetAnim(*(unsigned __int8 **)pxContext, v3 + 108);
    }
    else
    {
      *((_DWORD *)pxContext + 6) = Hierarchy_GetAnim(*(unsigned __int8 **)pxContext, v3 + 76);
    }
  }
  else
  {
    *((_DWORD *)pxContext + 6) = Hierarchy_GetAnim(*(unsigned __int8 **)pxContext, v3 + 44);
  }
}

// source: j/0/weapons/laserdesignator.c:223  [anchor-mhash]
struct QTask_s *__cdecl LaserDesignator_ResolveHitQTask(struct QTask_s *ptQTask)
{
  struct QTask_s *v1; // esi
  unsigned __int16 v2; // bx
  unsigned __int16 v3; // di

  v1 = ptQTask;
  if ( ptQTask )
  {
    v2 = MagicObjContainer_eQTaskType;
    v3 = ModelObj_eQTaskType;
    do
    {
      if ( QTask_IsQTaskTypeDerived(ptQTask->eQTaskType, v3) == false )
        break;
      v1 = ptQTask;
      ptQTask = ptQTask->ptParent;
      if ( !ptQTask )
        break;
      if ( QTask_IsQTaskTypeDerived(ptQTask->eQTaskType, v2) )
        ptQTask = ptQTask[1].ptNext;
    }
    while ( ptQTask );
  }
  return v1;
}

// source: j/0/weapons/laserdesignator.c:253  [anchor-mhash]
struct QTask_s *__cdecl LaserDesignator_Fire(
        struct LaserDesignator_s *ptLaserDesignator,
        struct QTask_s *ptWeaponQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct WeaponCollisionEvaluateContext_t tWeaponCollisionEvaluateContext; };
    struct { char igi2_o1[20]; struct real64x3_t Real64x3_Rotate_tTemp; };
    struct { char igi2_o2[44]; struct real64x3_t tTrace; };
    struct { char igi2_o3[68]; struct WeaponGetParentParameterContext_s tGetParentInfoContext; };
    struct { char igi2_o4[140]; struct real64x3_t tPos1; };
    struct { char igi2_o5[164]; struct real64x3_t tPos0; };
    struct { char igi2_o6[188]; struct QIntersection_s tIntersection; };
    char igi2_extent[308];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptParent; // ebx
  double v3; // st7
  struct QTask_s *result; // eax

  ptParent = ptWeaponQTask->ptParent;
  ((void (__cdecl *)(struct QTask_s *, struct WeaponGetParentParameterContext_s *))QTask_aatQTaskFinalEvent[Weapon_eGetParentParametersQTaskEvent][ptParent->eQTaskType].pfHandler)(
    ptParent,
    &igi2_frame.tGetParentInfoContext);
  *(_DWORD *)&igi2_frame.tWeaponCollisionEvaluateContext.tCollisionEvaluateContext.isEvaluate = 0;
  igi2_frame.tWeaponCollisionEvaluateContext.tCollisionEvaluateContext.ptQTask = nullptr;
  igi2_frame.tWeaponCollisionEvaluateContext.ptIgnore2QTask = nullptr;
  igi2_frame.Real64x3_Rotate_tTemp.vX = (igi2_frame.tGetParentInfoContext.tOrientation.tX.vZ + igi2_frame.tGetParentInfoContext.tOrientation.tX.vX) * 0.0
                           + igi2_frame.tGetParentInfoContext.tOrientation.tX.vY;
  igi2_frame.tWeaponCollisionEvaluateContext.ptIgnore1QTask = ptParent;
  igi2_frame.tWeaponCollisionEvaluateContext.vHitProbability = 1.0;
  igi2_frame.Real64x3_Rotate_tTemp.vY = (igi2_frame.tGetParentInfoContext.tOrientation.tY.vZ + igi2_frame.tGetParentInfoContext.tOrientation.tY.vX) * 0.0
                           + igi2_frame.tGetParentInfoContext.tOrientation.tY.vY;
  igi2_frame.Real64x3_Rotate_tTemp.vZ = (igi2_frame.tGetParentInfoContext.tOrientation.tZ.vZ + igi2_frame.tGetParentInfoContext.tOrientation.tZ.vX) * 0.0
                           + igi2_frame.tGetParentInfoContext.tOrientation.tZ.vY;
  qmemcpy(&igi2_frame.tTrace, &igi2_frame.Real64x3_Rotate_tTemp, sizeof(igi2_frame.tTrace));
  v3 = ptLaserDesignator->vRange * 4096.0;
  qmemcpy(&igi2_frame.tPos0, &igi2_frame.tGetParentInfoContext, sizeof(igi2_frame.tPos0));
  igi2_frame.tTrace.vZ = v3 * igi2_frame.tTrace.vZ;
  igi2_frame.tPos1.vX = igi2_frame.tGetParentInfoContext.tPosition.vX + igi2_frame.Real64x3_Rotate_tTemp.vX * v3;
  igi2_frame.tWeaponCollisionEvaluateContext.tCollisionEvaluateContext.ptQTask = nullptr;
  igi2_frame.tPos1.vY = igi2_frame.tGetParentInfoContext.tPosition.vY + v3 * igi2_frame.tTrace.vY;
  igi2_frame.tPos1.vZ = igi2_frame.tGetParentInfoContext.tPosition.vZ + igi2_frame.tTrace.vZ;
  World_TraceLines(
    Game_ptGame->ptWorld,
    &igi2_frame.tIntersection,
    &igi2_frame.tPos0,
    &igi2_frame.tPos1,
    1,
    GameFunctions_eWeaponCollisionEvaluateQTaskEvent,
    &igi2_frame.tWeaponCollisionEvaluateContext.tCollisionEvaluateContext,
    0xFFFFFFFF);
  result = (struct QTask_s *)igi2_frame.tIntersection.isHit;
  if ( igi2_frame.tIntersection.isHit )
  {
    result = LaserDesignator_ResolveHitQTask(&igi2_frame.tIntersection.ptHitObj->tQTask);
    if ( LaserDesignator_ptHitQTask != result )
    {
      LaserDesignator_ptHitQTask = result;
      result = (struct QTask_s *)LevelFlow_ptLevelFlow->nTick;
      LaserDesignator_nTickFirstHit = (int)result;
    }
  }
  else
  {
    LaserDesignator_nTickFirstHit = 0;
    LaserDesignator_ptHitQTask = nullptr;
  }
  return result;
}

// source: j/0/weapons/laserdesignator.c:332  [anchor-mhash]
void __cdecl LaserDesignator_WeaponFireHandler(struct QTask_s *ptQTask, void *pxContext)
{
  LaserDesignator_Fire(*((struct LaserDesignator_s **)pxContext + 25), *(struct QTask_s **)pxContext);
  *(_BYTE *)(*(_DWORD *)(*(_DWORD *)pxContext + 44) + 29) = 1;
}

// source: j/0/weapons/laserdesignator.c:360  [size]
void __cdecl LaserDesignator_StatusDisplayHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: j/0/weapons/laserdesignator.c:377  [anchor-mhash]
void __cdecl LaserDesignator_WeaponReleaseHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // ecx

  v2 = *(_DWORD *)(*(_DWORD *)pxContext + 44);
  LaserDesignator_ptHitQTask = nullptr;
  LaserDesignator_nTickFirstHit = 0;
  *(_BYTE *)(v2 + 29) = 0;
}

// source: j/0/weapons/laserdesignator.c:410  [size]
unsigned __int16 __cdecl LaserDesignator_GetQTaskType()
{
  return LaserDesignator_eQTaskType;
}

// source: j/0/weapons/laserdesignator.c:424  [anchor-hash]
void __cdecl LaserDesignator_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // [esp-1Ch] [ebp-28h]

  v0 = QTask_NewQTaskType("LaserDesignator", 140, FireType_eQTaskType, 0, 0);
  LaserDesignator_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, (void (__cdecl *)(struct QTask_s *, void *))LaserDesignator_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, (void (__cdecl *)(struct QTask_s *))LaserDesignator_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))LaserDesignator_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    WeaponType_eCreateParametersQTaskEvent,
    LaserDesignator_CreateWeaponTypeParametersHandler);
  QTask_LinkQTaskEventHandlerFn(v0, WeaponType_eGetAnimQTaskEvent, LaserDesignator_GetAnimHandler);
  QTask_LinkQTaskEventHandlerFn(v0, Weapon_eFireQTaskEvent, LaserDesignator_WeaponFireHandler);
  QTask_LinkQTaskEventHandlerFn(v0, Weapon_eReleaseQTaskEvent, LaserDesignator_WeaponReleaseHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    StatusScreen_eStatusDisplayQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))LaserDesignator_StatusDisplayHandler);
  v1 = (struct ParameterList_s *)Mem_AllocFn(172, 4);
  v2 = Level_eParameterTypeReal32;
  v1->nParameters = 0;
  v1->nMaxParameters = 8;
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  LaserDesignator_ptParameterList = v1;
  ParameterList_AddParameterMinMax(v1, 0x28u, v2, "Range", 7u, 0.0, 1000.0);
  ParameterList_AddParameter(
    LaserDesignator_ptParameterList,
    0x2Cu,
    Level_eParameterTypeString32,
    "1st person fire anim",
    7u,
    nullptr);
  ParameterList_AddParameter(
    LaserDesignator_ptParameterList,
    0x4Cu,
    Level_eParameterTypeString32,
    "1st person fire hold anim",
    7u,
    nullptr);
  ParameterList_AddParameter(
    LaserDesignator_ptParameterList,
    0x6Cu,
    Level_eParameterTypeString32,
    "1st person fire release anim",
    7u,
    nullptr);
  Symbol_Register(
    "TASKTYPE_LASERDESIGNATOR",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)LaserDesignator_eQTaskType,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "LaserDesignator_GetTicksHeldOnTask",
    LaserDesignator_GetTicksHeldOnTask,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}

// source: j/0/weapons/laserdesignator.c:461  [size]
void __cdecl LaserDesignator_Close()
{
  int v0; // esi

  if ( LaserDesignator_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&LaserDesignator_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(LaserDesignator_eQTaskType);
}

// source: j/0/weapons/laserdesignator.c:479  [size]
int __cdecl LaserDesignator_GetTickFirstHit()
{
  return LaserDesignator_nTickFirstHit;
}

// source: j/0/weapons/laserdesignator.c:492  [size]
float __cdecl LaserDesignator_GetRange(struct QTask_s *ptQTask)
{
  return *(float *)&ptQTask[1].ptNext;
}

// source: j/0/weapons/laserdesignator.c:508  [size]
void __cdecl LaserDesignator_LooseLock()
{
  LaserDesignator_nTickFirstHit = 0;
  LaserDesignator_ptHitQTask = nullptr;
}
