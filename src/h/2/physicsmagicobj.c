/* h/2/physicsmagicobj.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/physicsmagicobj.c:32  [anchor-mhash]
void __cdecl PhysicsMagicObj_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct PhysicsObjType_s *Type; // eax

  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][RigidDynCubeObj_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  PhysicsObj_Create(ptQTask);
  Type = PhysicsObjType_FindType(*(char **)pxContext);
  PhysicsObj_Init(ptQTask, Type);
}

// source: h/2/physicsmagicobj.c:78  [size]
void __cdecl PhysicsMagicObj_RunHandler(struct QTask_s *ptQTask)
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

// source: h/2/physicsmagicobj.c:91  [size]
void __cdecl PhysicsMagicObj_UpdateMagicObjHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[16]; struct real32x3_t Real32x3_Rotate_tTemp; };
    struct { char igi2_o2[28]; _BYTE tNewPos[40]; };
    char igi2_extent[68];
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
  int v13; // eax
  struct QTask_s *ptNext; // ecx
  double v15; // st7
  double v16; // st6
  struct QTask_s *ptHead; // ecx
  struct QTask_s *v18; // edx
  int v19; // edx
  struct QTask_s *v20; // eax
  int v21; // esi
  void (__cdecl *pfHandler)(struct QTask_s *, struct real32x3_t *); // eax
  int v23; // edx

  v2 = *((float **)pxContext + 1);
  v3 = v2[1] * *(float *)&ptQTask[5].tQTaskChildren.ptHead
     + v2[2] * *(float *)&ptQTask[5].tQTaskChildren.ptMiddle
     + *(float *)&ptQTask[5].ptPrev * *v2;
  v4 = v2[4] * *(float *)&ptQTask[5].tQTaskChildren.ptHead
     + v2[3] * *(float *)&ptQTask[5].ptPrev
     + v2[5] * *(float *)&ptQTask[5].tQTaskChildren.ptMiddle;
  v5 = v2[7] * *(float *)&ptQTask[5].tQTaskChildren.ptHead + v2[6] * *(float *)&ptQTask[5].ptPrev;
  v6 = v2[8];
  v7 = *(double **)pxContext;
  igi2_frame.Real32x3_Rotate_tTemp.vZ = v5 + v6 * *(float *)&ptQTask[5].tQTaskChildren.ptMiddle;
  *(double *)igi2_frame.tNewPos = v3 + *v7;
  *(double *)&igi2_frame.tNewPos[8] = v4 + v7[1];
  *(double *)&igi2_frame.tNewPos[16] = igi2_frame.Real32x3_Rotate_tTemp.vZ + v7[2];
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
  igi2_frame.ptDynCubeObj = v12 * v9;
  World_MoveDynCubeObjRadius(
    (struct World_s *)ptQTask[2].ptParent,
    (struct DynCubeObj_s *)ptQTask,
    (struct real64x3_t *)igi2_frame.tNewPos,
    igi2_frame.ptDynCubeObj);
  v13 = *((_DWORD *)pxContext + 1);
  *(float *)igi2_frame.tNewPos = *(float *)(v13 + 4) * *(float *)&ptQTask[4].tQTaskChildren.ptTail
                    + *(float *)&ptQTask[4].tQTaskRefList.ptTail * *(float *)(v13 + 8)
                    + *(float *)&ptQTask[4].ptPrev * *(float *)v13;
  *(float *)&igi2_frame.tNewPos[4] = *(float *)(v13 + 4) * *(float *)&ptQTask[4].tQTaskRefList.ptHead
                        + *(float *)&ptQTask[4].ptParent * *(float *)(v13 + 8)
                        + *(float *)&ptQTask[4].tQTaskChildren.ptHead * *(float *)v13;
  *(float *)&igi2_frame.tNewPos[8] = *(float *)(v13 + 4) * *(float *)&ptQTask[4].tQTaskRefList.ptMiddle
                        + *(float *)&ptQTask[4].eQTaskType * *(float *)(v13 + 8)
                        + *(float *)&ptQTask[4].tQTaskChildren.ptMiddle * *(float *)v13;
  *(float *)&igi2_frame.tNewPos[12] = *(float *)&ptQTask[4].tQTaskRefList.ptTail * *(float *)(v13 + 20)
                         + *(float *)&ptQTask[4].ptPrev * *(float *)(v13 + 12)
                         + *(float *)(v13 + 16) * *(float *)&ptQTask[4].tQTaskChildren.ptTail;
  *(float *)&igi2_frame.tNewPos[16] = *(float *)&ptQTask[4].ptParent * *(float *)(v13 + 20)
                         + *(float *)&ptQTask[4].tQTaskChildren.ptHead * *(float *)(v13 + 12)
                         + *(float *)(v13 + 16) * *(float *)&ptQTask[4].tQTaskRefList.ptHead;
  *(float *)&igi2_frame.tNewPos[20] = *(float *)&ptQTask[4].eQTaskType * *(float *)(v13 + 20)
                         + *(float *)&ptQTask[4].tQTaskChildren.ptMiddle * *(float *)(v13 + 12)
                         + *(float *)(v13 + 16) * *(float *)&ptQTask[4].tQTaskRefList.ptMiddle;
  *(float *)&igi2_frame.tNewPos[24] = *(float *)(v13 + 28) * *(float *)&ptQTask[4].tQTaskChildren.ptTail
                         + *(float *)(v13 + 32) * *(float *)&ptQTask[4].tQTaskRefList.ptTail
                         + *(float *)(v13 + 24) * *(float *)&ptQTask[4].ptPrev;
  ptNext = ptQTask[5].ptNext;
  *(float *)&igi2_frame.tNewPos[28] = *(float *)(v13 + 28) * *(float *)&ptQTask[4].tQTaskRefList.ptHead
                         + *(float *)(v13 + 32) * *(float *)&ptQTask[4].ptParent
                         + *(float *)(v13 + 24) * *(float *)&ptQTask[4].tQTaskChildren.ptHead;
  v15 = *(float *)(v13 + 28) * *(float *)&ptQTask[4].tQTaskRefList.ptMiddle
      + *(float *)(v13 + 32) * *(float *)&ptQTask[4].eQTaskType;
  v16 = *(float *)(v13 + 24) * *(float *)&ptQTask[4].tQTaskChildren.ptMiddle;
  *(_DWORD *)&igi2_frame.tNewPos[36] = (char *)&ptNext->ptNext + *(_DWORD *)(v13 + 36) + 1;
  *(float *)&igi2_frame.tNewPos[32] = v15 + v16;
  qmemcpy(&ptQTask[3].ptPrev, igi2_frame.tNewPos, sizeof(struct QTask_s));
  ptHead = ptQTask->tQTaskChildren.ptHead;
  v18 = ptHead->ptNext;
  if ( ptHead->ptNext )
  {
    if ( ptHead )
    {
      LODWORD(igi2_frame.Real32x3_Rotate_tTemp.vY) = &ptQTask[3].ptPrev;
      LODWORD(igi2_frame.Real32x3_Rotate_tTemp.vX) = &ptQTask[1];
      if ( v18 )
      {
        v19 = QTask_nProtectedQTaskStackOffset;
        do
        {
          if ( ptHead->ptNext )
            v20 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
          else
            v20 = nullptr;
          v21 = MagicObj_eUpdateMagicObjEvent;
          QTask_atProtectedQTaskStack[v19].ptQTask = v20;
          pfHandler = (void (__cdecl *)(struct QTask_s *, struct real32x3_t *))QTask_aatQTaskFinalEvent[v21][ptHead->eQTaskType].pfHandler;
          v23 = v19 + 1;
          QTask_nProtectedQTaskStackOffset = v23;
          if ( pfHandler )
          {
            pfHandler(ptHead, &igi2_frame.Real32x3_Rotate_tTemp);
            v23 = QTask_nProtectedQTaskStackOffset;
          }
          ptHead = (struct QTask_s *)dword_849C7DC[v23];
          v19 = v23 - 1;
          QTask_nProtectedQTaskStackOffset = v19;
        }
        while ( ptHead );
      }
    }
  }
}

// source: h/2/physicsmagicobj.c:156  [size]
void __cdecl PhysicsMagicObj_CollisionEvaluateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v2; // eax

  v2 = *((struct QTask_s **)pxContext + 1);
  *(_BYTE *)pxContext = ptQTask != v2 && ptQTask[8].ptNext != v2;
}

// source: h/2/physicsmagicobj.c:178  [anchor-strings]
void __cdecl PhysicsMagicObj_Open()
{
  unsigned __int16 v0; // si
  _DWORD *v1; // esi

  v0 = QTask_NewQTaskType("PhysicsMagicObj", 1912, PhysicsObj_eQTaskType, 0, 0);
  PhysicsMagicObj_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, PhysicsMagicObj_RunHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, PhysicsMagicObj_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(v0, MagicObj_eUpdateMagicObjEvent, PhysicsMagicObj_UpdateMagicObjHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 13, PhysicsMagicObj_CollisionEvaluateHandler);
  Symbol_Register(
    "TASKTYPE_PHYSICSMAGICOBJ",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)v0,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  v1 = Mem_AllocFn(18444, 4);
  v1[1] = 0;
  *v1 = 0;
  v1[4610] = "TASKTYPE_PHYSICSMAGICOBJ";
  Wildcard_CreateNFA("TASKTYPE_PHYSICSMAGICOBJ", v1 + 2, (char *)v1 + 10248);
  List_AddTail(v1, (int)&MagicObjConfig_tTaskTypeEnumList);
}

// source: h/2/physicsmagicobj.c:202  [size]
void __cdecl PhysicsMagicObj_Close()
{
  QTask_DeleteQTaskType(PhysicsMagicObj_eQTaskType);
  PhysicsMagicObj_eQTaskType = 512;
}

// source: h/2/physicsmagicobj.c:220  [size]
unsigned __int16 __cdecl PhysicsMagicObj_GetQTaskType()
{
  return PhysicsMagicObj_eQTaskType;
}
