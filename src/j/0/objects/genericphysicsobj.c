/* j/0/objects/genericphysicsobj.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/objects/genericphysicsobj.c:52  [anchor-mhash]
void __cdecl GenericPhysicsObj_Init(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct World_s *ptDynCubeObj; };
    struct { float ptDynCubeObja; };
    struct { char igi2_o2[16]; struct real64x3_t tVNull; };
    char igi2_extent[44];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v1; // st7
  double v2; // st7
  int *v3; // eax
  int v4; // eax
  double v5; // st6

  igi2_frame.ptDynCubeObj = Game_ptGame->ptWorld;
  memset(&igi2_frame.tVNull, 0, sizeof(igi2_frame.tVNull));
  ModelObj_Init((struct ModelObj_s *)ptQTask, igi2_frame.ptDynCubeObj, nullptr);
  ptQTask[7].tQTaskChildren.ptHead = nullptr;
  ptQTask[7].tQTaskChildren.ptMiddle = (struct QTask_s *)2;
  ptQTask[7].tQTaskRefList.ptHead = nullptr;
  ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[7].tQTaskRefList.ptTail = nullptr;
  ptQTask[7].ptParent = nullptr;
  *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
    v1 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  else
    v1 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  if ( v1 >= *(float *)&ptQTask[6].ptPrev )
  {
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
      v2 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v2 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  }
  else
  {
    v2 = *(float *)&ptQTask[6].ptPrev;
  }
  v3 = *(int **)&ptQTask[2].eQTaskType;
  if ( v3 && (v4 = *v3) != 0 )
    v5 = *(float *)(*(_DWORD *)(*(_DWORD *)(v4 + 12) + 12) + 120);
  else
    v5 = 1.0;
  igi2_frame.ptDynCubeObja = v2 * v5;
  World_RegisterDynCubeObjFirstTimeRadius(
    Game_ptGame->ptWorld,
    (struct DynCubeObj_s *)ptQTask,
    &igi2_frame.tVNull,
    igi2_frame.ptDynCubeObja,
    WORLD_DYNCUBETREE_CATEGORY_MOBILE);
  LOBYTE(ptQTask[10].tQTaskRefList.ptHead) = 0;
  PhysicsObj_Create(ptQTask);
}

// source: j/0/objects/genericphysicsobj.c:90  [anchor-caller]
void __cdecl GenericPhysicsObj_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  GenericPhysicsObj_Init(ptQTask);
}

// source: j/0/objects/genericphysicsobj.c:104  [size]
void __cdecl GenericPhysicsObj_RunHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { __int16 eCollisionEvalEvent; };
    struct { char igi2_o1[4]; struct QTask_s *v7; };
    char igi2_extent[8];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptHead; // ecx
  int v2; // edx
  struct QTask_s *v3; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v5; // edx

  if ( !PhysicsObj_IsIdle((struct PhysicsObj_s *)ptQTask) )
  {
    igi2_frame.v7 = ptQTask;
    PhysicsObj_Update(
      (struct PhysicsObj_s *)ptQTask,
      44.600887298583984,
      0.949999988079071,
      0.949999988079071,
      Game_ptGame->ptWorld,
      13,
      &igi2_frame.eCollisionEvalEvent);
  }
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

// source: j/0/objects/genericphysicsobj.c:125  [size]
void __cdecl GenericPhysicsObj_DeleteHandler(struct QTask_s *ptQTask)
{
  *(_DWORD *)&ptQTask[12].eQTaskType = 0;
  Physics_DeAlloc((struct Physics_s *)&ptQTask[8]);
  World_RemoveDynCubeObj(Game_ptGame->ptWorld, (struct DynCubeObj_s *)ptQTask);
}

// source: j/0/objects/genericphysicsobj.c:148  [size]
void __cdecl GenericPhysicsObj_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = GenericPhysicsObj_ptParameterList;
}

// source: j/0/objects/genericphysicsobj.c:164  [size]
void __cdecl GenericPhysicsObj_Move(struct GenericPhysicsObj_s *ptGenericPhysicsObj)
{
  struct CollisionEvaluateContext_s tContext; // [esp+8h] [ebp-Ch] BYREF

  if ( !PhysicsObj_IsIdle(&ptGenericPhysicsObj->tPhysicsObj) )
  {
    tContext.ptQTask = &ptGenericPhysicsObj->tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask;
    PhysicsObj_Update(
      &ptGenericPhysicsObj->tPhysicsObj,
      44.600887298583984,
      0.949999988079071,
      0.949999988079071,
      Game_ptGame->ptWorld,
      13,
      &tContext);
  }
}

// source: j/0/objects/genericphysicsobj.c:206  [anchor-mhash]
void __cdecl GenericPhysicsObj_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[20]; char zTempModel[128]; };
    struct { char igi2_o2[148]; char zString[132]; };
    char igi2_extent[280];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QReferenceList_s *p_tQTaskRefList; // edi
  struct LODVirModel_s *LODVirModelExistsFn; // eax
  struct PhysicsObjType_s *Type; // eax
  char *v5; // eax
  char v6; // cl
  double v7; // st7
  double v8; // st7
  int *v9; // eax
  int v10; // eax
  double v11; // st6

  qmemcpy(&ptQTask[3].ptPrev, &ptQTask[11].eQTaskType, sizeof(struct QTask_s));
  p_tQTaskRefList = &ptQTask[10].tQTaskRefList;
  LODVirModelExistsFn = MTP_GetLODVirModelExistsFn((char *)&ptQTask[10].tQTaskRefList);
  if ( LODVirModelExistsFn )
  {
    if ( LODVirModelExistsFn != *(struct LODVirModel_s **)&ptQTask[2].eQTaskType )
    {
      ModelObj_SetLODVirModel((struct ModelObj_s *)ptQTask, LODVirModelExistsFn, false);
      ptQTask[7].tQTaskRefList.ptHead = nullptr;
      ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
      ptQTask[7].tQTaskRefList.ptTail = nullptr;
      ptQTask[7].ptParent = nullptr;
      *(_DWORD *)&ptQTask[7].eQTaskType = 0;
    }
    Type = PhysicsObjType_FindType((char *)&ptQTask[10].tQTaskRefList);
    PhysicsObj_Init(ptQTask, Type);
  }
  else
  {
    if ( LOBYTE(p_tQTaskRefList->ptHead) && BYTE1(ptQTask[10].tQTaskRefList.ptHead) != 42 )
    {
      sprintf(igi2_frame.zString, "Model \"%s\" not available", (char *)&ptQTask[10].tQTaskRefList);
      v5 = (char *)&ptQTask[10].tQTaskRefList;
      do
      {
        v6 = *v5;
        v5[igi2_frame.zTempModel - (char *)p_tQTaskRefList] = *v5;
        ++v5;
      }
      while ( v6 );
      sprintf((char *const)&ptQTask[10].tQTaskRefList, "** %s **", igi2_frame.zTempModel);
    }
    if ( *(_DWORD *)&ptQTask[2].eQTaskType )
    {
      ModelObj_SetLODVirModel((struct ModelObj_s *)ptQTask, nullptr, false);
      ptQTask[7].tQTaskRefList.ptHead = nullptr;
      ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
      ptQTask[7].tQTaskRefList.ptTail = nullptr;
      ptQTask[7].ptParent = nullptr;
      *(_DWORD *)&ptQTask[7].eQTaskType = 0;
    }
  }
  ptQTask[8].tQTaskRefList.ptMiddle = ptQTask[11].tQTaskRefList.ptMiddle;
  ptQTask[8].tQTaskRefList.ptTail = ptQTask[11].tQTaskRefList.ptTail;
  ptQTask[8].ptParent = ptQTask[11].ptParent;
  Physics_UpdateSpeedApproximation((struct Physics_s *)&ptQTask[8]);
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
    Game_ptGame->ptWorld,
    (struct DynCubeObj_s *)ptQTask,
    (struct real64x3_t *)&ptQTask[11],
    igi2_frame.ptDynCubeObj);
}

// source: j/0/objects/genericphysicsobj.c:283  [anchor-mhash]
void __cdecl GenericPhysicsObj_WeaponHitHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float Real32x3_RotateInverse_tTemp; };
    struct { char igi2_o1[4]; float Real32x3_RotateInverse_tTemp_4; };
    struct { char igi2_o2[8]; float Real32x3_RotateInverse_tTemp_8; };
    struct { char igi2_o3[12]; struct PointForce_s tForce; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  float *v2; // edx
  float v3; // edx
  double v4; // st7
  double v5; // st6
  double v6; // st7
  int v7; // ecx
  double v8; // st7
  double vX; // st6
  char *v10; // edi

  v2 = (float *)(*(_DWORD *)pxContext + 32);
  igi2_frame.tForce.tPoint.vX = *v2;
  igi2_frame.tForce.tPoint.vZ = v2[2];
  igi2_frame.tForce.tForce.vX = *((float *)pxContext + 2);
  v3 = *((float *)pxContext + 3);
  igi2_frame.tForce.tForce.vZ = *((float *)pxContext + 4);
  v4 = igi2_frame.tForce.tForce.vZ * *(float *)&ptQTask[3].tQTaskRefList.ptTail;
  igi2_frame.tForce.tForce.vY = v3;
  v5 = v3 * *(float *)&ptQTask[3].tQTaskChildren.ptTail;
  memset(&igi2_frame.tForce.tPoint, 0, sizeof(igi2_frame.tForce.tPoint));
  igi2_frame.Real32x3_RotateInverse_tTemp = v4 + v5 + igi2_frame.tForce.tForce.vX * *(float *)&ptQTask[3].ptPrev;
  igi2_frame.Real32x3_RotateInverse_tTemp_4 = igi2_frame.tForce.tForce.vZ * *(float *)&ptQTask[3].ptParent
                                 + v3 * *(float *)&ptQTask[3].tQTaskRefList.ptHead
                                 + igi2_frame.tForce.tForce.vX * *(float *)&ptQTask[3].tQTaskChildren.ptHead;
  v6 = igi2_frame.tForce.tForce.vZ * *(float *)&ptQTask[3].eQTaskType;
  igi2_frame.tForce.tForce.vY = igi2_frame.Real32x3_RotateInverse_tTemp_4;
  v7 = 3 * (int)ptQTask[10].tQTaskChildren.ptMiddle;
  v8 = v6 + v3 * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle;
  vX = igi2_frame.tForce.tForce.vX;
  igi2_frame.tForce.tForce.vX = igi2_frame.Real32x3_RotateInverse_tTemp;
  igi2_frame.Real32x3_RotateInverse_tTemp_8 = v8 + vX * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle;
  igi2_frame.tForce.tForce.vZ = igi2_frame.Real32x3_RotateInverse_tTemp_8;
  v10 = (char *)ptQTask[10].ptPrev + 8 * v7;
  igi2_frame.tForce.tForce.vX = igi2_frame.Real32x3_RotateInverse_tTemp * 0.20000000298023224;
  igi2_frame.tForce.tForce.vY = igi2_frame.Real32x3_RotateInverse_tTemp_4 * 0.20000000298023224;
  igi2_frame.tForce.tForce.vZ = igi2_frame.Real32x3_RotateInverse_tTemp_8 * 0.20000000298023224;
  qmemcpy(v10, &igi2_frame.tForce, 0x18u);
  ++*(int *)&ptQTask[10].tQTaskChildren.ptMiddle;
}

// source: j/0/objects/genericphysicsobj.c:328  [size]
void __cdecl GenericPhysicsObj_ExplosionHitHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { __int64 tBlastDir; };
    struct { char igi2_o1[8]; float tBlastDir_8; };
    struct { char igi2_o2[16]; double tBlastDir_16; };
    struct { char igi2_o3[24]; struct PointForce_s tForce; };
    char igi2_extent[52];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double *v2; // ecx
  double v3; // st6
  int v4; // ecx
  double v5; // st7
  double vX; // st6
  double v7; // st7
  long double v8; // st7
  struct QTask_s *ptMiddle; // ecx
  char *v10; // edi

  v2 = *((double **)pxContext + 3);
  v3 = *(double *)&ptQTask[1].tQTaskChildren.ptHead - v2[1];
  igi2_frame.tBlastDir_16 = *(double *)&ptQTask[1].tQTaskChildren.ptTail - v2[2];
  igi2_frame.tForce.tForce.vX = *(double *)&ptQTask[1].ptNext - *v2;
  *(float *)&igi2_frame.tBlastDir = igi2_frame.tBlastDir_16 * *(float *)&ptQTask[3].tQTaskRefList.ptTail
                       + v3 * *(float *)&ptQTask[3].tQTaskChildren.ptTail
                       + igi2_frame.tForce.tForce.vX * *(float *)&ptQTask[3].ptPrev;
  *((float *)&igi2_frame.tBlastDir + 1) = igi2_frame.tBlastDir_16 * *(float *)&ptQTask[3].ptParent
                             + v3 * *(float *)&ptQTask[3].tQTaskRefList.ptHead
                             + igi2_frame.tForce.tForce.vX * *(float *)&ptQTask[3].tQTaskChildren.ptHead;
  v4 = *(_DWORD *)&ptQTask[12].eQTaskType;
  v5 = igi2_frame.tBlastDir_16 * *(float *)&ptQTask[3].eQTaskType + v3 * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle;
  vX = igi2_frame.tForce.tForce.vX;
  *(_QWORD *)&igi2_frame.tForce.tForce.vX = igi2_frame.tBlastDir;
  v7 = v5 + vX * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle;
  igi2_frame.tBlastDir_8 = v7;
  igi2_frame.tForce.tForce.vZ = igi2_frame.tBlastDir_8;
  v8 = *(float *)(v4 + 8)
     * 200.0
     / sqrt(*(float *)&igi2_frame.tBlastDir * *(float *)&igi2_frame.tBlastDir + *((float *)&igi2_frame.tBlastDir + 1) * *((float *)&igi2_frame.tBlastDir + 1) + v7 * v7);
  igi2_frame.tForce.tForce.vX = *(float *)&igi2_frame.tBlastDir * v8;
  igi2_frame.tForce.tForce.vY = *((float *)&igi2_frame.tBlastDir + 1) * v8;
  ptMiddle = ptQTask[10].tQTaskChildren.ptMiddle;
  igi2_frame.tForce.tForce.vZ = igi2_frame.tBlastDir_8 * v8;
  v10 = (char *)ptQTask[10].ptPrev + 24 * (_DWORD)ptMiddle;
  memset(&igi2_frame.tForce.tPoint, 0, sizeof(igi2_frame.tForce.tPoint));
  qmemcpy(v10, &igi2_frame.tForce, 0x18u);
  ++*(int *)&ptQTask[10].tQTaskChildren.ptMiddle;
}

// source: j/0/objects/genericphysicsobj.c:384  [anchor-strings]
void __cdecl GenericPhysicsObj_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // edx

  v0 = QTask_NewQTaskType("GenericPhysicsObj", 1904, PhysicsObj_eQTaskType, 0, 0);
  GenericPhysicsObj_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 0, GenericPhysicsObj_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, GenericPhysicsObj_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, GenericPhysicsObj_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))GenericPhysicsObj_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eUpdateInternalDataQTaskEvent,
    GenericPhysicsObj_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(v0, GameFunctions_eWeaponHitQTaskEvent, GenericPhysicsObj_WeaponHitHandler);
  QTask_LinkQTaskEventHandlerFn(v0, GameFunctions_eExplosionHitQTaskEvent, GenericPhysicsObj_ExplosionHitHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  v1 = (struct ParameterList_s *)Mem_AllocFn(412, 4);
  v2 = Level_eParameterTypeObjectPos;
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  v1->nParameters = 0;
  v1->nMaxParameters = 20;
  GenericPhysicsObj_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0x1B8u, v2, "Position", 7u, nullptr);
  ParameterList_AddParameter(
    GenericPhysicsObj_ptParameterList,
    0x7Cu,
    Level_eParameterTypeReal32x9,
    "Orientation",
    7u,
    nullptr);
  ParameterList_AddParameter(
    GenericPhysicsObj_ptParameterList,
    0x1D0u,
    Level_eParameterTypeReal32x3,
    "Speed",
    7u,
    nullptr);
  ParameterList_AddParameter(
    GenericPhysicsObj_ptParameterList,
    0x1A4u,
    Level_eParameterTypeString16,
    "Model",
    7u,
    nullptr);
  ParameterList_AddParameter(
    GenericPhysicsObj_ptParameterList,
    0x728u,
    Level_eParameterTypebool8,
    "Collision detection",
    7u,
    nullptr);
  ParameterList_AddParameter(
    GenericPhysicsObj_ptParameterList,
    0x729u,
    Level_eParameterTypebool8,
    "Force Z",
    7u,
    nullptr);
  Symbol_Register(
    "TASKTYPE_GENERICPHYSICSOBJ",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)GenericPhysicsObj_eQTaskType,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}

// source: j/0/objects/genericphysicsobj.c:431  [size]
void __cdecl GenericPhysicsObj_Close()
{
  int v0; // esi

  if ( GenericPhysicsObj_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&GenericPhysicsObj_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(GenericPhysicsObj_eQTaskType);
}

// source: j/0/objects/genericphysicsobj.c:453  [anchor-mhash]
struct QTask_s *__cdecl GenericPhysicsObj_New(
        struct QTask_s *ptParent,
        struct real64x3_t *ptPos,
        struct real32x9_t *ptOrientation,
        char *pzModel,
        struct real32x3_t *ptSpeed)
{
  struct QTask_s *v5; // ebx
  void (__cdecl *pfHandler)(struct QTask_s *, _DWORD); // eax

  v5 = QTask_NewFn(ptParent, GenericPhysicsObj_eQTaskType, nullptr);
  qmemcpy(&v5[11], ptPos, 0x18u);
  qmemcpy(&v5[11].eQTaskType, ptOrientation, sizeof(struct QTask_s));
  *(struct real32x3_t *)&v5[11].tQTaskRefList.ptMiddle = *ptSpeed;
  strcpy((char *)&v5[10].tQTaskRefList, pzModel);
  pfHandler = (void (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][v5->eQTaskType].pfHandler;
  if ( pfHandler )
    pfHandler(v5, 0);
  return v5;
}
