/* j/0/vehicles/wheel.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/vehicles/wheel.c:80  [anchor-mhash]
float __cdecl Wheel_GetCrawlerSpeedScale(
        struct QTask_s *ptQTask,
        int iCollPoint)
{
  float vRealDeltaGamma; // [esp+0h] [ebp-4h]

  vRealDeltaGamma = *(float *)&ptQTask[47].eQTaskType;
  if ( vRealDeltaGamma <= 0.009999999776482582 )
  {
    if ( vRealDeltaGamma < -0.009999999776482582 && !*((_DWORD *)&ptQTask[13].tQTaskChildren.ptHead + 14 * iCollPoint) )
      return vRealDeltaGamma + 0.5 + vRealDeltaGamma + 0.5;
    return 1.0;
  }
  if ( *((_DWORD *)&ptQTask[13].tQTaskChildren.ptHead + 14 * iCollPoint) != 1 )
    return 1.0;
  return 0.5 - vRealDeltaGamma + 0.5 - vRealDeltaGamma;
}

// source: j/0/vehicles/wheel.c:141  [anchor-mhash]
void __cdecl Wheel_MoveCollPoint(struct Car_s *ptCar, int iCollPoint, float vDelta, float vMaxDelta)
{
  struct real32x3_t *p_tPos; // esi
  struct PhysicsObjType_s *ptType; // ecx
  float *pxData; // edi
  double v7; // st7
  double v8; // st7
  double v9; // st7
  double v10; // st7
  double v11; // st7
  struct real32x3_t tOriginalPos; // [esp+8h] [ebp-Ch] BYREF
  int iCollPointa = *(int *)&vMaxDelta; // [esp+1Ch] [ebp+8h] ARGSLOT
  float iCollPointb = *(float *)&vMaxDelta; // [esp+1Ch] [ebp+8h] ARGSLOT
  float iCollPointc = *(float *)&vMaxDelta; // [esp+1Ch] [ebp+8h] ARGSLOT

  p_tPos = &ptCar->tVehicle.tPhysicsObj.atCollPoint[iCollPoint].tPos;
  ptType = ptCar->tVehicle.tPhysicsObj.ptType;
  pxData = (float *)ptType->pxData;
  GameFunctions_GetMagicVertexLocal(
    &tOriginalPos,
    &ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask,
    ptType->atCollPoint[iCollPoint].iMagicVertex);
  v7 = tOriginalPos.vZ - p_tPos->vZ;
  if ( v7 < 0.0 )
    v7 = -v7;
  if ( vMaxDelta + pxData[151] > v7 + 0.0010000000474974513 )
  {
    v8 = tOriginalPos.vZ + vMaxDelta;
    *(float *)&iCollPointa = v8;
    v9 = v8 - pxData[151];
    if ( v9 <= p_tPos->vZ )
    {
      if ( v9 < p_tPos->vZ )
      {
        v11 = p_tPos->vZ - vDelta;
        p_tPos->vZ = v11;
        iCollPointc = *(float *)&iCollPointa - pxData[151];
        if ( v11 < iCollPointc )
          p_tPos->vZ = iCollPointc;
      }
    }
    else
    {
      v10 = vDelta + p_tPos->vZ;
      p_tPos->vZ = v10;
      iCollPointb = *(float *)&iCollPointa - pxData[151];
      if ( v10 > iCollPointb )
      {
        p_tPos->vZ = iCollPointb;
        ptCar->tVehicle.tPhysicsObj.isMovingCollPoint = 1;
        return;
      }
    }
    ptCar->tVehicle.tPhysicsObj.isMovingCollPoint = 1;
  }
}

// source: j/0/vehicles/wheel.c:186  [anchor-mhash]
void __cdecl Wheel_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QReference_s *Type; // eax
  unsigned __int16 v3; // cx
  struct QTask_s *v4; // edx

  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][RigidMagicObj_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  Type = (struct QReference_s *)PhysicsObjType_FindType(*(char **)pxContext);
  v3 = Car_eQTaskType;
  ptQTask[8].tQTaskRefList.ptTail = Type;
  ptQTask[8].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[8].tQTaskChildren.ptTail = nullptr;
  ptQTask[8].tQTaskRefList.ptHead = nullptr;
  ptQTask[8].tQTaskChildren.ptHead = nullptr;
  v4 = *((struct QTask_s **)pxContext + 31);
  ptQTask[8].ptNext = v4;
  if ( QTask_IsQTaskTypeDerived(v4->eQTaskType, v3) )
  {
    ptQTask[8].tQTaskRefList.ptMiddle = (struct QReference_s *)(*(int *)&v4[48].ptParent)++;
    *((_BYTE *)&v4[49].ptPrev + 28 * (int)ptQTask[8].tQTaskRefList.ptMiddle) = 1;
    LOBYTE(ptQTask[8].ptParent) = 0;
  }
  else
  {
    LOBYTE(ptQTask[8].ptParent) = 0;
    ptQTask[8].tQTaskRefList.ptMiddle = (struct QReference_s *)-1;
  }
}

// source: j/0/vehicles/wheel.c:251  [anchor-mhash]
void __cdecl Wheel_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptNext; // eax

  ptNext = ptQTask[8].ptNext;
  if ( ptNext->eQTaskType == Car_eQTaskType )
  {
    --*(int *)&ptNext[48].ptParent;
    *((_BYTE *)&ptNext[49].ptPrev + 28 * (int)ptQTask[8].tQTaskRefList.ptMiddle) = 0;
  }
  World_RemoveDynCubeObj((struct World_s *)ptQTask[2].ptParent, (struct DynCubeObj_s *)ptQTask);
}

// source: j/0/vehicles/wheel.c:285  [anchor-mhash]
void __cdecl Wheel_RunHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptCar; };
    struct { char igi2_o1[24]; struct CarType_s *ptCarType; };
    struct { char igi2_o2[28]; struct real32x3_t tPointVelocity; };
    char igi2_extent[40];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptNext; // edi
  unsigned __int16 eQTaskType; // dx
  struct CarType_s *v4; // ebp
  int iCollPoint; // ebx
  int v6; // ebp
  long double v7; // st4
  struct QReference_s *ptTail; // ecx
  int v9; // ebp
  struct QReference_s *ptPrev; // ecx
  struct QTask_s *ptHead; // esi
  int v12; // ecx
  int v13; // edx
  struct QTask_s *v14; // eax
  void (__cdecl *pfHandler)(int); // eax
  int v16; // edx
  float ptQTaska = *(float *)&ptQTask; // [esp+2Ch] [ebp+4h] ARGSLOT

  ptNext = ptQTask[8].ptNext;
  eQTaskType = ptNext->eQTaskType;
  if ( QTask_IsQTaskTypeDerived(eQTaskType, Vehicle_eQTaskType) )
  {
    if ( LOBYTE(ptQTask[8].ptParent) )
    {
      QTask_Delete(ptQTask);
    }
    else
    {
      if ( eQTaskType == Car_eQTaskType )
      {
        v4 = *(struct CarType_s **)(*(_DWORD *)&ptNext[12].eQTaskType + 724);
        iCollPoint = v4->atCarWheelType[(int)ptQTask[8].tQTaskRefList.ptMiddle].iCollPoint;
        igi2_frame.ptCarType = v4;
        v6 = (int)v4 + 20 * (int)ptQTask[8].tQTaskRefList.ptMiddle;
        ptQTaska = 0.0;
        if ( iCollPoint < 0 )
          iCollPoint = -10 - iCollPoint;
        if ( *((_BYTE *)&ptNext[13].ptParent + 56 * iCollPoint + 2) )
        {
          Physics_GetPointVelocity(
            &igi2_frame.tPointVelocity,
            (struct Physics_s *)&ptNext[8],
            (struct real32x3_t *)((char *)&ptNext[13].tQTaskRefList + 56 * iCollPoint));
          v7 = sqrt(
                 igi2_frame.tPointVelocity.vX * igi2_frame.tPointVelocity.vX
               + igi2_frame.tPointVelocity.vY * igi2_frame.tPointVelocity.vY
               + igi2_frame.tPointVelocity.vZ * igi2_frame.tPointVelocity.vZ);
          ptQTaska = v7;
          if ( v7 < 40.959999084472656 )
            ptQTaska = 0.0;
        }
        else if ( *(_BYTE *)(v6 + 285) )
        {
          ptQTaska = *(float *)&ptNext[47].tQTaskRefList.ptMiddle
                   * 44.600887298583984
                   * *(float *)(*(_DWORD *)(*(_DWORD *)&ptNext[12].eQTaskType + 724) + 28)
                   / (double)(int)ptNext[49].ptNext
                   * 0.6000000238418579;
        }
        if ( igi2_frame.ptCarType->isCrawler )
          ptQTaska = Wheel_GetCrawlerSpeedScale(ptNext, iCollPoint) * ptQTaska;
        ptTail = ptQTask[8].tQTaskRefList.ptTail;
        *(float *)&ptQTask[8].tQTaskChildren.ptHead = ptQTaska
                                                    / (*(float *)&ptTail[60].ptPrev[62].ptNext
                                                     * 6.283185307179589)
                                                    * 6.283185307179589
                                                    * 0.30000001192092896
                                                    + *(float *)&ptQTask[8].tQTaskChildren.ptHead * 0.699999988079071;
        if ( *(_BYTE *)(v6 + 284) )
          *(float *)&ptQTask[8].tQTaskRefList.ptHead = -(*(float *)(v6 + 288)
                                                       * *(float *)&ptNext[47].eQTaskType
                                                       * 0.01745329238474369);
        if ( *(float *)&ptQTask[8].tQTaskChildren.ptMiddle != 0.0 )
        {
          v9 = *(_DWORD *)(v6 + 292);
          if ( v9 >= 0 )
          {
            ptPrev = ptTail[60].ptPrev;
            igi2_frame.ptCar = *(float *)&ptPrev[62].ptPrev * *(float *)&ptQTask[8].tQTaskChildren.ptMiddle;
            Wheel_MoveCollPoint((struct Car_s *)ptNext, v9, igi2_frame.ptCar, *(float *)&ptPrev[62].ptPrev);
          }
        }
      }
      else
      {
        ptQTask[8].tQTaskChildren.ptHead = (struct QTask_s *)ptNext[47].tQTaskRefList.ptMiddle;
      }
      if ( LOBYTE(ptNext[48].tQTaskRefList.ptHead) )
        ptQTask[8].tQTaskChildren.ptHead = nullptr;
      if ( *(float *)&ptQTask[8].tQTaskChildren.ptMiddle != 0.0 )
      {
        ptQTask[8].tQTaskChildren.ptHead = nullptr;
        ptQTask[8].tQTaskChildren.ptTail = nullptr;
      }
      *(float *)&ptQTask[8].tQTaskChildren.ptTail = *(float *)&ptQTask[8].tQTaskChildren.ptTail
                                                  - *(float *)&ptQTask[8].tQTaskChildren.ptHead;
      ptHead = ptQTask->tQTaskChildren.ptHead;
      if ( ptHead->ptNext )
      {
        v12 = (int)ptHead;
        if ( ptHead )
        {
          v13 = QTask_nProtectedQTaskStackOffset;
          do
          {
            if ( *(_DWORD *)v12 )
              v14 = **(_DWORD **)v12 != 0 ? *(struct QTask_s **)v12 : nullptr;
            else
              v14 = nullptr;
            QTask_atProtectedQTaskStack[v13].ptQTask = v14;
            pfHandler = (void (__cdecl *)(int))QTask_aatQTaskFinalEvent[1][*(unsigned __int16 *)(v12 + 36)].pfHandler;
            v16 = v13 + 1;
            QTask_nProtectedQTaskStackOffset = v16;
            if ( pfHandler )
            {
              pfHandler(v12);
              v16 = QTask_nProtectedQTaskStackOffset;
            }
            v12 = dword_849C7DC[v16];
            v13 = v16 - 1;
            QTask_nProtectedQTaskStackOffset = v13;
          }
          while ( v12 );
        }
      }
    }
  }
}

// source: j/0/vehicles/wheel.c:522  [anchor-mhash]
void __cdecl Wheel_UpdateAttachmentHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[20]; _BYTE tNewPos[40]; };
    struct { char igi2_o2[60]; struct real32x9_t tNewOrientation; };
    char igi2_extent[100];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptNext; // ecx
  double v2; // st7
  double v3; // st6
  double v4; // st5
  int v5; // edx
  int v6; // eax
  int v7; // eax
  float *ptTail; // eax
  double v9; // st4
  double v10; // st3
  double *ptMiddle; // eax
  double v12; // st7
  double v13; // st7
  int *v14; // eax
  int v15; // eax
  double v16; // st6
  struct QReference_s *v17; // eax
  struct QReference_s *v18; // edx
  double v19; // st7
  double v20; // st6

  ptNext = ptQTask[8].ptNext;
  v2 = *(float *)&ptQTask[5].ptPrev;
  v3 = *(float *)&ptQTask[5].tQTaskChildren.ptHead;
  v4 = *(float *)&ptQTask[5].tQTaskChildren.ptMiddle;
  if ( ptNext->eQTaskType == Car_eQTaskType )
  {
    v5 = *(_DWORD *)(*(_DWORD *)&ptNext[12].eQTaskType + 724);
    v6 = *(_DWORD *)(v5 + 20 * (int)ptQTask[8].tQTaskRefList.ptMiddle + 292);
    if ( v6 < 0 )
      v6 = -10 - v6;
    v7 = 56 * v6;
    v2 = *(float *)((char *)&ptNext[13].tQTaskRefList.ptHead + v7);
    v3 = *(float *)((char *)&ptNext[13].tQTaskRefList.ptMiddle + v7);
    v4 = *(float *)((char *)&ptNext[13].tQTaskRefList.ptTail + v7)
       + *(float *)((char *)&ptNext[14].tQTaskRefList.ptHead + v7)
       + *(float *)&ptQTask[8].tQTaskRefList.ptTail[60].ptPrev[62].ptNext
       - *(float *)(v5 + 604);
  }
  ptTail = (float *)ptQTask[5].tQTaskRefList.ptTail;
  *(double *)&igi2_frame.tNewOrientation.tX.vX = ptTail[2] * v4 + ptTail[1] * v3 + *ptTail * v2;
  *(double *)&igi2_frame.tNewOrientation.tX.vZ = ptTail[5] * v4 + ptTail[4] * v3 + ptTail[3] * v2;
  v9 = ptTail[8] * v4 + ptTail[7] * v3;
  v10 = ptTail[6];
  ptMiddle = (double *)ptQTask[5].tQTaskRefList.ptMiddle;
  *(double *)&igi2_frame.tNewOrientation.tY.vY = v9 + v10 * v2;
  qmemcpy(igi2_frame.tNewPos, &igi2_frame.tNewOrientation, 0x18u);
  *(double *)igi2_frame.tNewPos = *(double *)&igi2_frame.tNewOrientation.tX.vX + *ptMiddle;
  *(double *)&igi2_frame.tNewPos[8] = *(double *)&igi2_frame.tNewPos[8] + ptMiddle[1];
  *(double *)&igi2_frame.tNewPos[16] = *(double *)&igi2_frame.tNewPos[16] + ptMiddle[2];
  if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
    v12 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  else
    v12 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  if ( v12 >= *(float *)&ptQTask[6].ptPrev )
  {
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
      v13 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v13 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  }
  else
  {
    v13 = *(float *)&ptQTask[6].ptPrev;
  }
  v14 = *(int **)&ptQTask[2].eQTaskType;
  if ( v14 && (v15 = *v14) != 0 )
    v16 = *(float *)(*(_DWORD *)(*(_DWORD *)(v15 + 12) + 12) + 120);
  else
    v16 = 1.0;
  igi2_frame.ptDynCubeObj = v16 * v13;
  World_MoveDynCubeObjRadius(
    Game_ptGame->ptWorld,
    (struct DynCubeObj_s *)ptQTask,
    (struct real64x3_t *)igi2_frame.tNewPos,
    igi2_frame.ptDynCubeObj);
  Real32x9_Rotate(
    &igi2_frame.tNewOrientation,
    (struct real32x9_t *)&ptQTask[4].ptPrev,
    *(float *)&ptQTask[8].tQTaskChildren.ptTail,
    0.0,
    *(float *)&ptQTask[8].tQTaskRefList.ptHead);
  v17 = ptQTask[5].tQTaskRefList.ptTail;
  *(float *)igi2_frame.tNewPos = igi2_frame.tNewOrientation.tY.vX * *(float *)&v17->ptPrev
                    + igi2_frame.tNewOrientation.tZ.vX * *(float *)&v17->pxObject
                    + igi2_frame.tNewOrientation.tX.vX * *(float *)&v17->ptNext;
  *(float *)&igi2_frame.tNewPos[4] = igi2_frame.tNewOrientation.tY.vY * *(float *)&v17->ptPrev
                        + igi2_frame.tNewOrientation.tZ.vY * *(float *)&v17->pxObject
                        + igi2_frame.tNewOrientation.tX.vY * *(float *)&v17->ptNext;
  *(float *)&igi2_frame.tNewPos[8] = igi2_frame.tNewOrientation.tY.vZ * *(float *)&v17->ptPrev
                        + igi2_frame.tNewOrientation.tZ.vZ * *(float *)&v17->pxObject
                        + igi2_frame.tNewOrientation.tX.vZ * *(float *)&v17->ptNext;
  *(float *)&igi2_frame.tNewPos[12] = igi2_frame.tNewOrientation.tY.vX * *(float *)&v17[1].ptPrev
                         + igi2_frame.tNewOrientation.tZ.vX * *(float *)&v17[1].pxObject
                         + igi2_frame.tNewOrientation.tX.vX * *(float *)&v17[1].ptNext;
  *(float *)&igi2_frame.tNewPos[16] = igi2_frame.tNewOrientation.tY.vY * *(float *)&v17[1].ptPrev
                         + igi2_frame.tNewOrientation.tZ.vY * *(float *)&v17[1].pxObject
                         + igi2_frame.tNewOrientation.tX.vY * *(float *)&v17[1].ptNext;
  *(float *)&igi2_frame.tNewPos[20] = igi2_frame.tNewOrientation.tY.vZ * *(float *)&v17[1].ptPrev
                         + igi2_frame.tNewOrientation.tZ.vZ * *(float *)&v17[1].pxObject
                         + igi2_frame.tNewOrientation.tX.vZ * *(float *)&v17[1].ptNext;
  v18 = v17[3].ptNext;
  *(float *)&igi2_frame.tNewPos[24] = igi2_frame.tNewOrientation.tZ.vX * *(float *)&v17[2].pxObject
                         + igi2_frame.tNewOrientation.tX.vX * *(float *)&v17[2].ptNext
                         + igi2_frame.tNewOrientation.tY.vX * *(float *)&v17[2].ptPrev;
  *(float *)&igi2_frame.tNewPos[28] = igi2_frame.tNewOrientation.tZ.vY * *(float *)&v17[2].pxObject
                         + igi2_frame.tNewOrientation.tX.vY * *(float *)&v17[2].ptNext
                         + igi2_frame.tNewOrientation.tY.vY * *(float *)&v17[2].ptPrev;
  v19 = igi2_frame.tNewOrientation.tZ.vZ * *(float *)&v17[2].pxObject + igi2_frame.tNewOrientation.tX.vZ * *(float *)&v17[2].ptNext;
  v20 = igi2_frame.tNewOrientation.tY.vZ * *(float *)&v17[2].ptPrev;
  *(_DWORD *)&igi2_frame.tNewPos[36] = (char *)&v18->ptNext + igi2_frame.tNewOrientation.nOps + 1;
  *(float *)&igi2_frame.tNewPos[32] = v19 + v20;
  qmemcpy(&ptQTask[3].ptPrev, igi2_frame.tNewPos, sizeof(struct QTask_s));
  ModelObj_UpdateAttachments((struct ModelObj_s *)ptQTask);
}

// source: j/0/vehicles/wheel.c:618  [size]
void __cdecl Wheel_WeaponHitHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: j/0/vehicles/wheel.c:636  [size]
void __cdecl Wheel_ExplosionHitHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: j/0/vehicles/wheel.c:659  [size]
void __cdecl Wheel_PhysicsObjTypeDeleteHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // eax
  int v3; // esi

  v2 = *(_DWORD *)(*(_DWORD *)pxContext + 724);
  if ( v2 )
  {
    v3 = *(_DWORD *)((v2 - 4) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v3);
    memset(*(void **)(v3 + 8), 0xCDu, *(_DWORD *)(v3 + 16));
    free((void *)v3);
    *(_DWORD *)(*(_DWORD *)pxContext + 724) = 0;
  }
}

// source: j/0/vehicles/wheel.c:680  [size]
void __cdecl Wheel_AILineOfSightHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v2; // eax

  v2 = *((struct QTask_s **)pxContext + 2);
  *(_BYTE *)pxContext = v2 != ptQTask && *((struct QTask_s **)pxContext + 3) != ptQTask && ptQTask[8].ptNext != v2;
}

// source: j/0/vehicles/wheel.c:711  [anchor-strings]
void __cdecl Wheel_Open()
{
  unsigned __int16 v0; // si
  _DWORD *v1; // esi

  v0 = QTask_NewQTaskType("Wheel", 360, RigidMagicObj_eQTaskType, 0, 0);
  Wheel_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 0, Wheel_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, Wheel_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, Wheel_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Attach_eUpdateAttachmentEvent, Wheel_UpdateAttachmentHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    GameFunctions_eWeaponHitQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Wheel_WeaponHitHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    GameFunctions_eExplosionHitQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Wheel_ExplosionHitHandler);
  QTask_LinkQTaskEventHandlerFn(v0, PhysicsObjType_ePhysicsObjTypeDeleteEvent, Wheel_PhysicsObjTypeDeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v0, AIDetection_eLineOfSightQTaskEvent, Wheel_AILineOfSightHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 11, nullptr);
  QTask_LinkQTaskEventHandlerFn(v0, 10, nullptr);
  Symbol_Register(
    "TASKTYPE_WHEEL",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)v0,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  v1 = Mem_AllocFn(18444, 4);
  v1[1] = 0;
  *v1 = 0;
  v1[4610] = "TASKTYPE_WHEEL";
  Wildcard_CreateNFA("TASKTYPE_WHEEL", v1 + 2, (char *)v1 + 10248);
  List_AddTail(v1, (int)&MagicObjConfig_tTaskTypeEnumList);
}

// source: j/0/vehicles/wheel.c:752  [size]
void __cdecl Wheel_Close()
{
  QTask_DeleteQTaskType(Wheel_eQTaskType);
}

// source: j/0/vehicles/wheel.c:766  [size]
unsigned __int16 __cdecl Wheel_GetQTaskType()
{
  return Wheel_eQTaskType;
}

// source: j/0/vehicles/wheel.c:787  [anchor-mhash]
struct real32x3_t *__cdecl Wheel_AddFriction(
        struct Physics_s *ptPhysics,
        struct real32x9_t *ptOrientation,
        struct real32x3_t *ptPoint,
        struct real32x3_t *ptNormal,
        float vGamma,
        float vXFriction,
        float vYFriction,
        float vVelocityThreshold)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v33; };
    struct { char igi2_o1[4]; struct real32x3_t tFrictionForce; };
    struct { char igi2_o2[16]; struct real32x3_t tPointVelocity; };
    struct { char igi2_o3[28]; struct real32x3_t Real32x3_Rotate_tTemp[2]; };
    struct { char igi2_o4[52]; struct real32x9_t tGamma; };
    char igi2_extent[92];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double vZ; // st7
  double v12; // st7
  double v13; // st7
  float vY; // ecx
  float v15; // edx
  double v16; // st7
  double v17; // st7
  double v18; // st6
  double v19; // st5
  double v20; // st4
  double v21; // st7
  double v22; // rt2
  double v23; // st4
  double v24; // st7
  long double v25; // st6
  double vX; // st7
  double v27; // st7
  float v28; // eax
  float v29; // ecx
  float v30; // edx
  int nForces; // eax
  struct real32x3_t *result; // eax
  float ptPhysicsa = *(float *)&ptPhysics; // [esp+6Ch] [ebp+4h] ARGSLOT
  float ptOrientationa = *(float *)&vGamma; // [esp+70h] [ebp+8h] ARGSLOT
  float ptPointa = *(float *)&vXFriction; // [esp+74h] [ebp+Ch] ARGSLOT

  ptPhysicsa = (ptNormal->vY + ptNormal->vX) * 0.0 + ptPhysics->vM * 44.600887298583984 * ptNormal->vZ;
  igi2_frame.Real32x3_Rotate_tTemp[0].vX = ptOrientation->tX.vX * ptPoint->vX
                              + ptPoint->vY * ptOrientation->tX.vY
                              + ptPoint->vZ * ptOrientation->tX.vZ;
  vZ = ptOrientation->tY.vZ;
  igi2_frame.tFrictionForce.vX = igi2_frame.Real32x3_Rotate_tTemp[0].vX;
  igi2_frame.Real32x3_Rotate_tTemp[0].vY = vZ * ptPoint->vZ
                              + ptOrientation->tY.vX * ptPoint->vX
                              + ptOrientation->tY.vY * ptPoint->vY;
  v12 = ptPoint->vZ;
  igi2_frame.tFrictionForce.vY = igi2_frame.Real32x3_Rotate_tTemp[0].vY;
  igi2_frame.Real32x3_Rotate_tTemp[0].vZ = v12 * ptOrientation->tZ.vZ
                              + ptPoint->vX * ptOrientation->tZ.vX
                              + ptPoint->vY * ptOrientation->tZ.vY;
  igi2_frame.tFrictionForce.vZ = igi2_frame.Real32x3_Rotate_tTemp[0].vZ;
  Physics_GetPointVelocity(&igi2_frame.tPointVelocity, ptPhysics, &igi2_frame.tFrictionForce);
  v13 = igi2_frame.tPointVelocity.vZ * ptNormal->vZ;
  vY = ptNormal->vY;
  v15 = ptNormal->vZ;
  igi2_frame.tFrictionForce.vX = ptNormal->vX;
  igi2_frame.tFrictionForce.vY = vY;
  igi2_frame.tFrictionForce.vZ = v15;
  v16 = v13 + igi2_frame.tPointVelocity.vY * vY + igi2_frame.tPointVelocity.vX * ptNormal->vX;
  igi2_frame.tFrictionForce.vX = igi2_frame.tFrictionForce.vX * v16;
  igi2_frame.tFrictionForce.vY = vY * v16;
  igi2_frame.tFrictionForce.vZ = v15 * v16;
  v17 = igi2_frame.tFrictionForce.vX - igi2_frame.tPointVelocity.vX;
  v18 = igi2_frame.tFrictionForce.vY - igi2_frame.tPointVelocity.vY;
  v19 = igi2_frame.tFrictionForce.vZ - igi2_frame.tPointVelocity.vZ;
  igi2_frame.v33 = sqrt(v17 * v17 + v18 * v18 + v19 * v19);
  if ( v17 != 0.0 || v18 != 0.0 || v19 != 0.0 )
  {
    v20 = v17;
    v21 = 1.0 / igi2_frame.v33;
    v22 = v20 * v21;
    v23 = v21;
    v17 = v22;
    v18 = v18 * v23;
    v19 = v19 * v23;
  }
  igi2_frame.tPointVelocity.vX = v18 * ptOrientation->tY.vX + v17 * ptOrientation->tX.vX + v19 * ptOrientation->tZ.vX;
  igi2_frame.tPointVelocity.vY = v18 * ptOrientation->tY.vY + v19 * ptOrientation->tZ.vY + v17 * ptOrientation->tX.vY;
  v24 = v18 * ptOrientation->tY.vZ + v17 * ptOrientation->tX.vZ + v19 * ptOrientation->tZ.vZ;
  v25 = sin(vGamma);
  ptOrientationa = cos(vGamma);
  igi2_frame.tGamma.tX.vY = -v25;
  igi2_frame.Real32x3_Rotate_tTemp[0].vX = ptOrientationa * igi2_frame.tPointVelocity.vX + igi2_frame.tGamma.tX.vY * igi2_frame.tPointVelocity.vY + v24 * 0.0;
  igi2_frame.Real32x3_Rotate_tTemp[0].vY = ptOrientationa * igi2_frame.tPointVelocity.vY + v25 * igi2_frame.tPointVelocity.vX + v24 * 0.0;
  igi2_frame.Real32x3_Rotate_tTemp[0].vZ = (igi2_frame.tPointVelocity.vY + igi2_frame.tPointVelocity.vX) * 0.0 + v24;
  igi2_frame.tFrictionForce.vX = igi2_frame.Real32x3_Rotate_tTemp[0].vX * vXFriction;
  igi2_frame.tFrictionForce.vY = igi2_frame.Real32x3_Rotate_tTemp[0].vY * vYFriction;
  ptPointa = igi2_frame.Real32x3_Rotate_tTemp[0].vZ * 0.0;
  igi2_frame.tPointVelocity.vX = v25 * igi2_frame.tFrictionForce.vY + ptOrientationa * igi2_frame.tFrictionForce.vX + ptPointa;
  igi2_frame.tPointVelocity.vY = ptOrientationa * igi2_frame.tFrictionForce.vY + igi2_frame.tGamma.tX.vY * igi2_frame.tFrictionForce.vX + ptPointa;
  igi2_frame.tPointVelocity.vZ = (igi2_frame.tFrictionForce.vY + igi2_frame.tFrictionForce.vX) * 0.0 + igi2_frame.Real32x3_Rotate_tTemp[0].vZ;
  igi2_frame.tFrictionForce = igi2_frame.tPointVelocity;
  vX = igi2_frame.tPointVelocity.vX;
  if ( ptPhysicsa / ptPhysics->vM * 4.0 >= igi2_frame.v33 )
  {
    igi2_frame.tFrictionForce.vX = vX * igi2_frame.v33 * ptPhysics->vM * 0.10000000149011612;
    igi2_frame.tFrictionForce.vY = igi2_frame.v33 * igi2_frame.tFrictionForce.vY * ptPhysics->vM * 0.10000000149011612;
    v27 = igi2_frame.v33 * igi2_frame.tFrictionForce.vZ * ptPhysics->vM * 0.10000000149011612;
  }
  else
  {
    igi2_frame.tFrictionForce.vX = vX * ptPhysicsa * 0.23999999463558197;
    igi2_frame.tFrictionForce.vY = igi2_frame.tFrictionForce.vY * ptPhysicsa * 0.23999999463558197;
    v27 = igi2_frame.tFrictionForce.vZ * ptPhysicsa * 0.23999999463558197;
  }
  igi2_frame.tFrictionForce.vZ = v27;
  igi2_frame.Real32x3_Rotate_tTemp[0].vZ = igi2_frame.tFrictionForce.vZ;
  v28 = ptPoint->vZ;
  igi2_frame.Real32x3_Rotate_tTemp[0].vX = igi2_frame.tFrictionForce.vX;
  v29 = ptPoint->vX;
  igi2_frame.Real32x3_Rotate_tTemp[0].vY = igi2_frame.tFrictionForce.vY;
  v30 = ptPoint->vY;
  igi2_frame.Real32x3_Rotate_tTemp[1].vZ = v28;
  nForces = ptPhysics->nForces;
  igi2_frame.Real32x3_Rotate_tTemp[1].vX = v29;
  igi2_frame.Real32x3_Rotate_tTemp[1].vY = v30;
  qmemcpy(&ptPhysics->ptForces[nForces], igi2_frame.Real32x3_Rotate_tTemp, sizeof(ptPhysics->ptForces[nForces]));
  result = (struct real32x3_t *)(ptPhysics->nForces + 1);
  ptPhysics->nForces = (int)result;
  return result;
}

// source: j/0/vehicles/wheel.c:874  [anchor-caller]
void __cdecl Wheel_AddForces(struct Car_s *ptCar, int iWheel, int iCollPoint)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vIdealVelocity; };
    struct { float vIdealVelocitya; };
    struct { float vIdealVelocityb; };
    struct { char igi2_o3[4]; float ptPhysics; };
    struct { char igi2_o4[8]; float vGamma; };
    struct { char igi2_o5[8]; float vGammaa; };
    struct { char igi2_o6[12]; float vRealVelocity; };
    struct { char igi2_o7[16]; float tYAxis; };
    struct { char igi2_o8[16]; float tYAxisa; };
    struct { char igi2_o9[16]; float tYAxisb; };
    struct { char igi2_o10[20]; float tYAxis_4; };
    struct { char igi2_o11[20]; float tYAxis_4a; };
    struct { char igi2_o12[20]; float tYAxis_4b; };
    struct { char igi2_o13[24]; float tYAxis_8; };
    struct { char igi2_o14[24]; float tYAxis_8a; };
    struct { char igi2_o15[40]; struct PointForce_s tForce; };
    char igi2_extent[64];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  float *pxData; // esi
  float *v5; // ebp
  struct Physics_s *p_tPhysics; // edi
  float *v7; // ecx
  double v8; // st7
  float v9; // edi
  double v10; // st7
  double v11; // st6
  double v12; // st5
  double v13; // st4
  double v14; // rt2
  double v15; // st5
  double v16; // st7
  double v17; // st6
  double v18; // st5
  double v19; // st7
  double v20; // st5
  double v21; // st7
  long double v22; // st6
  long double v23; // rtt
  long double v24; // st5
  struct real32x3_t *v25; // esi
  struct real32x3_t struct_real32x3_t; // 0:^40.12

  pxData = (float *)ptCar->tVehicle.tPhysicsObj.ptType->pxData;
  v5 = &pxData[5 * iWheel];
  p_tPhysics = &ptCar->tVehicle.tPhysicsObj.tPhysics;
  igi2_frame.vGamma = v5[72] * 0.01745329238474369 * ptCar->tVehicle.vRealDeltaGamma;
  if ( *((_BYTE *)v5 + 285) )
  {
    if ( (v7 = (float *)((char *)ptCar + 28 * iWheel), *((_BYTE *)v7 + 1965)) && ptCar->tVehicle.vRealThrust != 0.0
      || ptCar->tVehicle.tPhysicsObj.isForceZ )
    {
      v8 = pxData[7] * ptCar->tVehicle.vRealThrust;
      igi2_frame.vRealVelocity = ptCar->tVehicle.tPhysicsObj.tPhysics.vCMSpeed;
      igi2_frame.tForce.tPoint.vX = v7[495];
      v9 = v7[496];
      v10 = v8 * 44.600887298583984 / (double)ptCar->nEngineWheel;
      igi2_frame.tForce.tPoint.vZ = v7[497];
      igi2_frame.tYAxis = ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vY;
      igi2_frame.tYAxis_4 = ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vY;
      igi2_frame.tYAxis_8 = ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vY;
      igi2_frame.tForce.tPoint.vY = v9;
      if ( v7[492] != igi2_frame.tYAxis || v7[493] != igi2_frame.tYAxis_4 || v7[494] != igi2_frame.tYAxis_8 )
      {
        v11 = igi2_frame.tYAxis_8 * v7[493] - igi2_frame.tYAxis_4 * v7[494];
        v12 = -(igi2_frame.tYAxis_8 * v7[492] - igi2_frame.tYAxis * v7[494]);
        v13 = igi2_frame.tYAxis_4 * v7[492] - igi2_frame.tYAxis * v7[493];
        igi2_frame.tYAxisa = v12 * v7[494] - v13 * v7[493];
        igi2_frame.tYAxis_4a = -(v11 * v7[494] - v13 * v7[492]);
        igi2_frame.tForce.tForce.vY = igi2_frame.tYAxis_4a;
        v14 = v11 * v7[493];
        v15 = v12 * v7[492];
        igi2_frame.tForce.tForce.vX = igi2_frame.tYAxisa;
        igi2_frame.tYAxis_8a = v14 - v15;
        igi2_frame.tForce.tForce.vZ = igi2_frame.tYAxis_8a;
      }
      if ( *((_BYTE *)pxData + 609) )
      {
        igi2_frame.vIdealVelocitya = v10;
        v10 = Wheel_GetCrawlerSpeedScale(
                &ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask,
                iCollPoint)
            * igi2_frame.vIdealVelocitya;
      }
      v16 = v10 - igi2_frame.vRealVelocity;
      v17 = igi2_frame.tForce.tForce.vX * v16;
      v18 = v16;
      v19 = v16 * igi2_frame.tForce.tForce.vY;
      v20 = v18 * igi2_frame.tForce.tForce.vZ;
      igi2_frame.tYAxisb = v17 * ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vX
              + v20 * ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vX
              + v19 * ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vX;
      igi2_frame.tYAxis_4b = v17 * ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vY
                + v19 * ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vY
                + v20 * ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vY;
      v21 = v17 * ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vZ
          + v20 * ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vZ
          + v19 * ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vZ;
      v22 = -igi2_frame.vGamma;
      v23 = sin(v22);
      v24 = cos(v22);
      igi2_frame.vIdealVelocityb = v21 * 0.0;
      struct_real32x3_t.vX = v24 * igi2_frame.tYAxisb + -v23 * igi2_frame.tYAxis_4b + igi2_frame.vIdealVelocityb;
      struct_real32x3_t.vY = v24 * igi2_frame.tYAxis_4b + v23 * igi2_frame.tYAxisb + igi2_frame.vIdealVelocityb;
      struct_real32x3_t.vZ = (igi2_frame.tYAxis_4b + igi2_frame.tYAxisb) * 0.0 + v21;
      igi2_frame.tForce.tForce = struct_real32x3_t;
      qmemcpy(
        &ptCar->tVehicle.tPhysicsObj.tPhysics.ptForces[ptCar->tVehicle.tPhysicsObj.tPhysics.nForces++],
        &igi2_frame.tForce,
        sizeof(ptCar->tVehicle.tPhysicsObj.tPhysics.ptForces[ptCar->tVehicle.tPhysicsObj.tPhysics.nForces++]));
      p_tPhysics = &ptCar->tVehicle.tPhysicsObj.tPhysics;
    }
  }
  v25 = (struct real32x3_t *)((char *)ptCar + 28 * iWheel);
  if ( BYTE1(v25[163].vZ) && iCollPoint >= 0 )
  {
    if ( *((_BYTE *)v5 + 284) )
      igi2_frame.vIdealVelocity = igi2_frame.vGamma;
    else
      igi2_frame.vIdealVelocity = 0.0;
    igi2_frame.vGammaa = ptCar->tVehicle.tPhysicsObj.atCollPoint[iCollPoint].vFrictionY;
    igi2_frame.ptPhysics = ptCar->tVehicle.tPhysicsObj.atCollPoint[iCollPoint].vFrictionX;
    if ( ptCar->tVehicle.isBreak )
    {
      igi2_frame.vGammaa = ptCar->tVehicle.tPhysicsObj.atCollPoint[iCollPoint].vFrictionX;
      ptCar->tVehicle.vRealThrust = ptCar->tVehicle.vRealThrust * 0.949999988079071;
    }
    Wheel_AddFriction(
      p_tPhysics,
      &ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation,
      v25 + 165,
      v25 + 164,
      igi2_frame.vIdealVelocity,
      igi2_frame.ptPhysics,
      igi2_frame.vGammaa,
      81.91999816894531);
  }
}
