/* j/0/objects/genericphysicsmagicobj.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/objects/genericphysicsmagicobj.c:50  [size]
void __cdecl GenericPhysicsMagicObj_Move(struct GenericPhysicsMagicObj_s *ptGenericPhysicsMagicObj)
{
  struct CollisionEvaluateContext_s tContext; // [esp+8h] [ebp-Ch] BYREF

  if ( !PhysicsObj_IsIdle(&ptGenericPhysicsMagicObj->tPhysicsMagicObj.tPhysicsObj) )
  {
    tContext.ptQTask = &ptGenericPhysicsMagicObj->tPhysicsMagicObj.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask;
    PhysicsObj_Update(
      &ptGenericPhysicsMagicObj->tPhysicsMagicObj.tPhysicsObj,
      44.600887298583984,
      0.9599999785423279,
      0.9200000166893005,
      Game_ptGame->ptWorld,
      13,
      &tContext);
  }
}

// source: j/0/objects/genericphysicsmagicobj.c:93  [size]
void __cdecl GenericPhysicsMagicObj_RunHandler(struct QTask_s *ptQTask)
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
      0.9599999785423279,
      0.9200000166893005,
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

// source: j/0/objects/genericphysicsmagicobj.c:114  [size]
void __cdecl GenericPhysicsMagicObj_DeleteHandler(struct QTask_s *ptQTask)
{
  *(_DWORD *)&ptQTask[12].eQTaskType = 0;
  Physics_DeAlloc((struct Physics_s *)&ptQTask[8]);
  World_RemoveDynCubeObj(Game_ptGame->ptWorld, (struct DynCubeObj_s *)ptQTask);
}

// source: j/0/objects/genericphysicsmagicobj.c:137  [anchor-mhash]
void __cdecl GenericPhysicsMagicObj_WeaponHitHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float Real32x3_RotateInverse_tTemp; };
    struct { char igi2_o1[4]; float Real32x3_RotateInverse_tTemp_4; };
    struct { char igi2_o2[8]; float Real32x3_RotateInverse_tTemp_8; };
    struct { char igi2_o3[12]; struct PointForce_s tForce; };
    char igi2_extent[40];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // edx
  float v3; // esi
  float v4; // edx
  double v5; // st7
  double v6; // st6
  double v7; // st7
  int v8; // ecx
  double v9; // st7
  double vX; // st6
  double v11; // st7
  long double v12; // st7
  int v13; // edx
  char *v14; // edi

  v2 = *(_DWORD *)pxContext + 32;
  igi2_frame.tForce.tPoint.vX = *(float *)v2;
  v3 = *(float *)(v2 + 4);
  igi2_frame.tForce.tPoint.vZ = *(float *)(v2 + 8);
  igi2_frame.tForce.tForce.vX = *((float *)pxContext + 2);
  v4 = *((float *)pxContext + 3);
  igi2_frame.tForce.tForce.vZ = *((float *)pxContext + 4);
  v5 = igi2_frame.tForce.tForce.vZ * *(float *)&ptQTask[3].tQTaskRefList.ptTail;
  igi2_frame.tForce.tForce.vY = v4;
  v6 = v4 * *(float *)&ptQTask[3].tQTaskChildren.ptTail;
  igi2_frame.tForce.tPoint.vY = v3;
  igi2_frame.Real32x3_RotateInverse_tTemp = v5 + v6 + igi2_frame.tForce.tForce.vX * *(float *)&ptQTask[3].ptPrev;
  igi2_frame.Real32x3_RotateInverse_tTemp_4 = igi2_frame.tForce.tForce.vZ * *(float *)&ptQTask[3].ptParent
                                 + v4 * *(float *)&ptQTask[3].tQTaskRefList.ptHead
                                 + igi2_frame.tForce.tForce.vX * *(float *)&ptQTask[3].tQTaskChildren.ptHead;
  v7 = igi2_frame.tForce.tForce.vZ * *(float *)&ptQTask[3].eQTaskType;
  igi2_frame.tForce.tForce.vY = igi2_frame.Real32x3_RotateInverse_tTemp_4;
  v8 = *(_DWORD *)&ptQTask[12].eQTaskType;
  v9 = v7 + v4 * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle;
  vX = igi2_frame.tForce.tForce.vX;
  igi2_frame.tForce.tForce.vX = igi2_frame.Real32x3_RotateInverse_tTemp;
  v11 = v9 + vX * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle;
  igi2_frame.Real32x3_RotateInverse_tTemp_8 = v11;
  igi2_frame.tForce.tForce.vZ = igi2_frame.Real32x3_RotateInverse_tTemp_8;
  v12 = *(float *)(v8 + 8)
      * 100.0
      / sqrt(
          igi2_frame.Real32x3_RotateInverse_tTemp * igi2_frame.Real32x3_RotateInverse_tTemp
        + igi2_frame.Real32x3_RotateInverse_tTemp_4 * igi2_frame.Real32x3_RotateInverse_tTemp_4
        + v11 * v11);
  igi2_frame.tForce.tForce.vX = igi2_frame.Real32x3_RotateInverse_tTemp * v12;
  v13 = 3 * (int)ptQTask[10].tQTaskChildren.ptMiddle;
  igi2_frame.tForce.tForce.vY = igi2_frame.Real32x3_RotateInverse_tTemp_4 * v12;
  v14 = (char *)ptQTask[10].ptPrev + 8 * v13;
  igi2_frame.tForce.tForce.vZ = igi2_frame.Real32x3_RotateInverse_tTemp_8 * v12;
  qmemcpy(v14, &igi2_frame.tForce, 0x18u);
  ++*(int *)&ptQTask[10].tQTaskChildren.ptMiddle;
}

// source: j/0/objects/genericphysicsmagicobj.c:181  [size]
void __cdecl GenericPhysicsMagicObj_ExplosionHitHandler(struct QTask_s *ptQTask, void *pxContext)
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

// source: j/0/objects/genericphysicsmagicobj.c:237  [anchor-strings]
void __cdecl GenericPhysicsMagicObj_Open()
{
  unsigned __int16 v0; // si
  _DWORD *v1; // esi

  v0 = QTask_NewQTaskType("GenericPhysicsMagicObj", 1912, PhysicsMagicObj_eQTaskType, 0, 0);
  GenericPhysicsMagicObj_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, GenericPhysicsMagicObj_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, GenericPhysicsMagicObj_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v0, GameFunctions_eWeaponHitQTaskEvent, GenericPhysicsMagicObj_WeaponHitHandler);
  QTask_LinkQTaskEventHandlerFn(v0, GameFunctions_eExplosionHitQTaskEvent, GenericPhysicsMagicObj_ExplosionHitHandler);
  Symbol_Register(
    "TASKTYPE_GENERICPHYSICSMAGICOBJ",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)v0,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  v1 = Mem_AllocFn(18444, 4);
  v1[1] = 0;
  *v1 = 0;
  v1[4610] = "TASKTYPE_GENERICPHYSICSMAGICOBJ";
  Wildcard_CreateNFA("TASKTYPE_GENERICPHYSICSMAGICOBJ", v1 + 2, (char *)v1 + 10248);
  List_AddTail(v1, (int)&MagicObjConfig_tTaskTypeEnumList);
}

// source: j/0/objects/genericphysicsmagicobj.c:269  [size]
void __cdecl GenericPhysicsMagicObj_Close()
{
  QTask_DeleteQTaskType(GenericPhysicsMagicObj_eQTaskType);
}
