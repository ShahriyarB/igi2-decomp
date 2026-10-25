/* j/0/vehicles/rotor.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/vehicles/rotor.c:112  [anchor-mhash]
void __cdecl Rotor_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][RigidMagicObj_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  ptQTask[8].tQTaskChildren.ptMiddle = (struct QTask_s *)PhysicsObjType_FindType(*(char **)pxContext);
  ptQTask[8].tQTaskChildren.ptHead = nullptr;
}

// source: j/0/vehicles/rotor.c:150  [size]
void __cdecl Rotor_DeleteHandler(struct QTask_s *ptQTask)
{
  World_RemoveDynCubeObj((struct World_s *)ptQTask[2].ptParent, (struct DynCubeObj_s *)ptQTask);
}

// source: j/0/vehicles/rotor.c:167  [anchor-mhash]
void __cdecl Rotor_RunHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vThrustZ; };
    struct { char igi2_o1[4]; struct real32x3_t tForward; };
    struct { char igi2_o2[16]; struct PointForce_s tForce; };
    char igi2_extent[40];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v1; // ecx
  struct QTask_s *ptNext; // ebx
  struct QTask_s *ptPrev; // ebp
  double v4; // st7
  long double v5; // st7
  float v6; // eax
  double v7; // st6
  float v8; // ecx
  float v9; // edx
  float v10; // ecx
  struct PointForce_s *v11; // edi
  char v12; // al
  double v13; // st7
  int ptHead; // ecx
  int v15; // edx
  struct QTask_s *v16; // eax
  void (__cdecl *pfHandler)(int); // eax
  int v18; // edx

  v1 = ptQTask;
  ptNext = ptQTask[8].ptNext;
  ptPrev = ptQTask[8].tQTaskChildren.ptMiddle[18].ptPrev;
  if ( LOBYTE(ptPrev->ptNext) )
  {
    v4 = *(float *)(*(_DWORD *)&ptNext[12].eQTaskType + 8) * *(float *)&ptNext[47].tQTaskRefList.ptMiddle * 44.600887298583984;
    igi2_frame.vThrustZ = v4;
    if ( v4 != 0.0 )
    {
      v5 = 0.0;
      v6 = *(float *)&ptNext[3].tQTaskRefList.ptHead;
      v7 = *(float *)&ptNext[3].tQTaskChildren.ptHead;
      v8 = *(float *)&ptNext[3].ptParent;
      v9 = *(float *)&ptNext[3].tQTaskChildren.ptMiddle;
      igi2_frame.tForward.vX = *(float *)&ptNext[3].tQTaskChildren.ptHead;
      igi2_frame.tForward.vY = v6;
      LODWORD(igi2_frame.tForce.tForce.vY) = ptNext[3].tQTaskRefList.ptMiddle;
      igi2_frame.tForward.vZ = v8;
      v10 = *(float *)&ptNext[3].eQTaskType;
      igi2_frame.tForce.tForce.vX = v9;
      igi2_frame.tForce.tForce.vZ = v10;
      if ( v7 != 0.0 || igi2_frame.tForward.vY != 0.0 )
      {
        igi2_frame.tForward.vZ = 0.0;
        v5 = Real32x3_Angle(&igi2_frame.tForward, &igi2_frame.tForce.tForce);
      }
      v11 = (struct PointForce_s *)((char *)ptNext[10].ptPrev + 24 * (int)ptNext[10].tQTaskChildren.ptMiddle);
      memset(&igi2_frame.tForce.tPoint, 0, sizeof(igi2_frame.tForce.tPoint));
      igi2_frame.tForce.tForce.vX = 0.0;
      igi2_frame.tForce.tForce.vZ = igi2_frame.vThrustZ;
      igi2_frame.tForce.tForce.vY = cos(v5) * igi2_frame.vThrustZ;
      qmemcpy(v11, &igi2_frame.tForce, sizeof(struct PointForce_s));
      v1 = ptQTask;
      ++*(int *)&ptNext[10].tQTaskChildren.ptMiddle;
    }
  }
  if ( *(float *)&ptNext[47].tQTaskRefList.ptMiddle != 0.0 )
  {
    v12 = BYTE1(ptPrev->ptNext);
    if ( (v12 || LOBYTE(ptPrev->ptNext)) && !ptNext[13].ptNext )
    {
      igi2_frame.tForce.tPoint.vY = 8192.0;
      igi2_frame.tForce.tPoint.vZ = 0.0;
      memset(&igi2_frame.tForce, 0, 16);
      if ( v12 )
      {
        v13 = -(*(float *)(*(_DWORD *)&ptNext[12].eQTaskType + 8) * *(float *)&ptNext[47].tQTaskRefList.ptMiddle * 2.5);
      }
      else
      {
        if ( !LOBYTE(ptPrev->ptNext) )
        {
LABEL_16:
          qmemcpy((char *)ptNext[10].ptPrev + 24 * (int)ptNext[10].tQTaskChildren.ptMiddle, &igi2_frame.tForce, 0x18u);
          v1 = ptQTask;
          ++*(int *)&ptNext[10].tQTaskChildren.ptMiddle;
          goto LABEL_17;
        }
        v13 = *(float *)(*(_DWORD *)&ptNext[12].eQTaskType + 8) * *(float *)&ptNext[47].tQTaskRefList.ptMiddle * 2.5;
      }
      igi2_frame.tForce.tForce.vX = v13;
      goto LABEL_16;
    }
  }
LABEL_17:
  *(float *)&v1[8].tQTaskChildren.ptHead = (double)(int)ptPrev->tQTaskChildren.ptMiddle
                                         * *(float *)&ptPrev->tQTaskChildren.ptHead
                                         * *(float *)&ptNext[47].tQTaskRefList.ptMiddle
                                         + *(float *)&v1[8].tQTaskChildren.ptHead;
  ptHead = (int)v1->tQTaskChildren.ptHead;
  if ( *(_DWORD *)ptHead && ptHead )
  {
    v15 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( *(_DWORD *)ptHead )
        v16 = **(_DWORD **)ptHead != 0 ? *(struct QTask_s **)ptHead : nullptr;
      else
        v16 = nullptr;
      QTask_atProtectedQTaskStack[v15].ptQTask = v16;
      pfHandler = (void (__cdecl *)(int))QTask_aatQTaskFinalEvent[1][*(unsigned __int16 *)(ptHead + 36)].pfHandler;
      v18 = v15 + 1;
      QTask_nProtectedQTaskStackOffset = v18;
      if ( pfHandler )
      {
        pfHandler(ptHead);
        v18 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = dword_849C7DC[v18];
      v15 = v18 - 1;
      QTask_nProtectedQTaskStackOffset = v15;
    }
    while ( ptHead );
  }
}

// source: j/0/vehicles/rotor.c:286  [size]
void __cdecl Rotor_UpdateMagicObjHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[20]; struct real64x3_t tNewPos; };
    struct { char igi2_o2[44]; _BYTE Real64x3_Rotate_tTemp[40]; };
    char igi2_extent[88];
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
  int v12; // eax
  int v13; // ecx
  struct QTask_s *ptNext; // edx
  double v15; // st7
  double v16; // st6
  struct QTask_s *ptHead; // ecx
  struct QTask_s *v18; // edx
  int v19; // edx
  struct QTask_s *v20; // eax
  int v21; // esi
  void (__cdecl *pfHandler)(struct QTask_s *, struct real64x3_t *); // eax
  int v23; // edx

  v2 = *(float *)&ptQTask[5].ptPrev;
  igi2_frame.tNewPos.vY = *(float *)&ptQTask[5].tQTaskChildren.ptHead;
  v3 = *((float **)pxContext + 1);
  igi2_frame.tNewPos.vZ = *(float *)&ptQTask[5].tQTaskChildren.ptMiddle;
  *(double *)igi2_frame.Real64x3_Rotate_tTemp = v3[2] * igi2_frame.tNewPos.vZ + v3[1] * igi2_frame.tNewPos.vY + *v3 * v2;
  *(double *)&igi2_frame.Real64x3_Rotate_tTemp[8] = v3[5] * igi2_frame.tNewPos.vZ + v3[4] * igi2_frame.tNewPos.vY + v3[3] * v2;
  v4 = v3[8] * igi2_frame.tNewPos.vZ + v3[7] * igi2_frame.tNewPos.vY;
  v5 = v3[6];
  v6 = *(double **)pxContext;
  *(double *)&igi2_frame.Real64x3_Rotate_tTemp[16] = v4 + v5 * v2;
  qmemcpy(&igi2_frame.tNewPos, igi2_frame.Real64x3_Rotate_tTemp, sizeof(igi2_frame.tNewPos));
  igi2_frame.tNewPos.vX = *(double *)igi2_frame.Real64x3_Rotate_tTemp + *v6;
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
  igi2_frame.ptDynCubeObj = v11 * v8;
  World_MoveDynCubeObjRadius(Game_ptGame->ptWorld, (struct DynCubeObj_s *)ptQTask, &igi2_frame.tNewPos, igi2_frame.ptDynCubeObj);
  v12 = *((_DWORD *)pxContext + 1);
  *(float *)igi2_frame.Real64x3_Rotate_tTemp = *(float *)&ptQTask[4].tQTaskRefList.ptTail * *(float *)(v12 + 8)
                                  + *(float *)&ptQTask[4].ptPrev * *(float *)v12
                                  + *(float *)(v12 + 4) * *(float *)&ptQTask[4].tQTaskChildren.ptTail;
  *(float *)&igi2_frame.Real64x3_Rotate_tTemp[4] = *(float *)&ptQTask[4].ptParent * *(float *)(v12 + 8)
                                      + *(float *)&ptQTask[4].tQTaskChildren.ptHead * *(float *)v12
                                      + *(float *)(v12 + 4) * *(float *)&ptQTask[4].tQTaskRefList.ptHead;
  *(float *)&igi2_frame.Real64x3_Rotate_tTemp[8] = *(float *)&ptQTask[4].eQTaskType * *(float *)(v12 + 8)
                                      + *(float *)&ptQTask[4].tQTaskChildren.ptMiddle * *(float *)v12
                                      + *(float *)(v12 + 4) * *(float *)&ptQTask[4].tQTaskRefList.ptMiddle;
  *(float *)&igi2_frame.Real64x3_Rotate_tTemp[12] = *(float *)(v12 + 20) * *(float *)&ptQTask[4].tQTaskRefList.ptTail
                                       + *(float *)(v12 + 12) * *(float *)&ptQTask[4].ptPrev
                                       + *(float *)&ptQTask[4].tQTaskChildren.ptTail * *(float *)(v12 + 16);
  *(float *)&igi2_frame.Real64x3_Rotate_tTemp[16] = *(float *)(v12 + 20) * *(float *)&ptQTask[4].ptParent
                                       + *(float *)(v12 + 12) * *(float *)&ptQTask[4].tQTaskChildren.ptHead
                                       + *(float *)&ptQTask[4].tQTaskRefList.ptHead * *(float *)(v12 + 16);
  *(float *)&igi2_frame.Real64x3_Rotate_tTemp[20] = *(float *)(v12 + 20) * *(float *)&ptQTask[4].eQTaskType
                                       + *(float *)(v12 + 12) * *(float *)&ptQTask[4].tQTaskChildren.ptMiddle
                                       + *(float *)&ptQTask[4].tQTaskRefList.ptMiddle * *(float *)(v12 + 16);
  *(float *)&igi2_frame.Real64x3_Rotate_tTemp[24] = *(float *)(v12 + 32) * *(float *)&ptQTask[4].tQTaskRefList.ptTail
                                       + *(float *)(v12 + 24) * *(float *)&ptQTask[4].ptPrev
                                       + *(float *)&ptQTask[4].tQTaskChildren.ptTail * *(float *)(v12 + 28);
  v13 = *(_DWORD *)(v12 + 36);
  ptNext = ptQTask[5].ptNext;
  *(float *)&igi2_frame.Real64x3_Rotate_tTemp[28] = *(float *)(v12 + 32) * *(float *)&ptQTask[4].ptParent
                                       + *(float *)(v12 + 24) * *(float *)&ptQTask[4].tQTaskChildren.ptHead
                                       + *(float *)&ptQTask[4].tQTaskRefList.ptHead * *(float *)(v12 + 28);
  v15 = *(float *)(v12 + 32) * *(float *)&ptQTask[4].eQTaskType
      + *(float *)(v12 + 24) * *(float *)&ptQTask[4].tQTaskChildren.ptMiddle;
  v16 = *(float *)&ptQTask[4].tQTaskRefList.ptMiddle * *(float *)(v12 + 28);
  *(_DWORD *)&igi2_frame.Real64x3_Rotate_tTemp[36] = (char *)&ptNext->ptNext + v13 + 1;
  *(float *)&igi2_frame.Real64x3_Rotate_tTemp[32] = v15 + v16;
  qmemcpy(&ptQTask[3].ptPrev, igi2_frame.Real64x3_Rotate_tTemp, sizeof(struct QTask_s));
  ptHead = ptQTask->tQTaskChildren.ptHead;
  v18 = ptHead->ptNext;
  if ( ptHead->ptNext )
  {
    if ( ptHead )
    {
      HIDWORD(igi2_frame.tNewPos.vX) = (char *)ptQTask + 124;
      LODWORD(igi2_frame.tNewPos.vX) = ptQTask + 1;
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
          pfHandler = (void (__cdecl *)(struct QTask_s *, struct real64x3_t *))QTask_aatQTaskFinalEvent[v21][ptHead->eQTaskType].pfHandler;
          v23 = v19 + 1;
          QTask_nProtectedQTaskStackOffset = v23;
          if ( pfHandler )
          {
            pfHandler(ptHead, &igi2_frame.tNewPos);
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

// source: j/0/vehicles/rotor.c:350  [size]
void __cdecl Rotor_WeaponHitHandler(struct QTask_s *ptQTask, void *pxContext)
{
  void (__cdecl *pfHandler)(struct QTask_s *, ...); // ecx

  pfHandler = (void (__cdecl *)(struct QTask_s *, ...))QTask_aatQTaskFinalEvent[GameFunctions_eWeaponHitQTaskEvent][ptQTask[8].ptNext->eQTaskType].pfHandler;
  if ( pfHandler )
    pfHandler(ptQTask[8].ptNext, pxContext);
}

// source: j/0/vehicles/rotor.c:379  [anchor-mhash]
void __cdecl Rotor_ParsePhysicsObjTypeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // ebp
  int v3; // esi
  struct ArgList_s *v4; // edi
  char v5; // al
  int v6; // esi
  char v7; // al
  int v8; // esi
  void *v9; // eax
  int v10; // esi
  double v11; // st7
  int v12; // esi
  double v13; // st7
  int v14; // eax

  v2 = *(_DWORD *)pxContext;
  v3 = *((_DWORD *)pxContext + 2);
  v4 = *((struct ArgList_s **)pxContext + 1);
  if ( v4->isQVM )
  {
    *(float *)&pxContext = 0.0;
    QVM_EvalArg(&pxContext, 4, v4, v3, 1);
    v5 = (char)pxContext;
  }
  else
  {
    v5 = Expression_EvalInt(v4->aptExpression[v3]);
  }
  *(_BYTE *)v2 = v5;
  v6 = v3 + 1;
  if ( v4->isQVM )
  {
    *(float *)&pxContext = 0.0;
    QVM_EvalArg(&pxContext, 4, v4, v6, 1);
    v7 = (char)pxContext;
  }
  else
  {
    v7 = Expression_EvalInt(v4->aptExpression[v6]);
  }
  *(_BYTE *)(v2 + 1) = v7;
  v8 = v6 + 1;
  if ( v4->isQVM )
  {
    *(float *)&pxContext = 0.0;
    QVM_EvalArg(&pxContext, 4, v4, v8, 1);
    v9 = pxContext;
  }
  else
  {
    v9 = (void *)Expression_EvalInt(v4->aptExpression[v8]);
  }
  *(_DWORD *)(v2 + 12) = v9;
  v10 = v8 + 1;
  if ( v4->isQVM )
  {
    *(float *)&pxContext = 0.0;
    QVM_EvalArg(&pxContext, 4, v4, v10, 2);
    v11 = *(float *)&pxContext;
  }
  else
  {
    v11 = Expression_EvalFloat(v4->aptExpression[v10]);
  }
  v12 = v10 + 1;
  *(float *)(v2 + 4) = v11 * 0.017453293005625408;
  if ( v4->isQVM )
  {
    *(float *)&pxContext = 0.0;
    QVM_EvalArg(&pxContext, 4, v4, v12, 2);
    v13 = *(float *)&pxContext;
  }
  else
  {
    v13 = Expression_EvalFloat(v4->aptExpression[v12]);
  }
  *(float *)(v2 + 8) = v13;
  v14 = v12 + 1;
  if ( v4->isQVM )
  {
    *(_BYTE *)(v2 + 16) = 0;
    QVM_EvalArg((void *)(v2 + 16), 16, v4, v14, 3);
  }
  else
  {
    Expression_EvalString(v4->aptExpression[v14], (char *)(v2 + 16), 16);
  }
}

// source: j/0/vehicles/rotor.c:410  [size]
void __cdecl Rotor_GetGetPhysicsObjTypeSizeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = 32;
}

// source: j/0/vehicles/rotor.c:426  [anchor-caller]
void __cdecl Rotor_DrawHandler(void *pxPrimitive)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vTiltRad; };
    struct { float vTiltRada; };
    struct { char igi2_o2[4]; struct VehicleType_s *ptVehicleType; };
    struct { char igi2_o3[4]; float ptVehicleTypea; };
    struct { char igi2_o4[20]; float v27; };
    struct { char igi2_o5[24]; float v28; };
    struct { char igi2_o6[28]; float v29; };
    struct { char igi2_o7[32]; float v30; };
    struct { char igi2_o8[36]; float v31; };
    struct { char igi2_o9[40]; float v32; };
    struct { char igi2_o10[56]; struct real32x9_t Real32x9_Multiply_tTemp; };
    struct { char igi2_o11[96]; float v36[10]; };
    struct { char igi2_o12[136]; struct real32x9_t Real32x9_Normalize_tTemp; };
    struct { char igi2_o13[176]; float v38[10]; };
    struct { char igi2_o14[216]; int v39; };
    struct { char igi2_o15[220]; struct real32x9_t tTilt; };
    struct { char igi2_o16[260]; struct real32x9_t tOriginalOrientation; };
    struct { char igi2_o17[300]; float vDeltaAngle; };
    struct { char igi2_o18[304]; int v43; };
    struct { char igi2_o19[308]; struct DrawRigidMeshContext_t tContext; };
    struct { char igi2_o20[340]; struct RigidDynCubeObj_t tRigidDynCubeObj; };
    char igi2_extent[660];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v1; // edx
  int v2; // ecx
  int v3; // eax
  int v4; // ecx
  double v5; // st6
  double v6; // st7
  int v7; // ebp
  bool v8; // cc
  long double v9; // st4
  long double v10; // st4
  long double v11; // st4
  int v12; // eax
  bool v13; // sf
  long double v14; // st4
  long double v15; // st4
  long double v16; // st7
  int v17; // ecx
  int *v18; // eax
  struct HazingDynCubeObj_t **v19; // edx
  int v20; // eax
  struct real32x3_t tTemp_; // 0:^24.12
  struct real32x3_t v47; // 0:^48.12

  if ( pxPrimitive )
  {
    v1 = *((_DWORD *)pxPrimitive + 3);
    qmemcpy(&igi2_frame.tRigidDynCubeObj, (void *)v1, sizeof(igi2_frame.tRigidDynCubeObj));
    v2 = *(_DWORD *)(v1 + 332);
    v3 = *(_DWORD *)(v1 + 320);
    if ( v2 )
    {
      igi2_frame.v39 = *(_DWORD *)(v2 + 724);
      if ( igi2_frame.v39 )
      {
        if ( v3 )
        {
          v4 = *(_DWORD *)(v3 + 516);
          if ( v4 )
          {
            igi2_frame.ptVehicleType = *(struct VehicleType_s **)(v4 + 724);
            qmemcpy(&igi2_frame.tOriginalOrientation, &igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation, sizeof(igi2_frame.tOriginalOrientation));
            if ( igi2_frame.tRigidDynCubeObj.tModelObj.ptLODVirModel )
            {
              igi2_frame.vTiltRad = *(float *)(igi2_frame.v39 + 4);
              igi2_frame.vDeltaAngle = *(float *)(igi2_frame.v39 + 8) * *(float *)(v3 + 1904);
              v5 = 1.0 - *(float *)(v3 + 1904);
              if ( v5 >= -0.10000000149011612 )
              {
                if ( v5 > 1.0 )
                  v5 = 1.0;
              }
              else
              {
                v5 = -0.10000000149011612;
              }
              igi2_frame.ptVehicleTypea = -(v5 * igi2_frame.vTiltRad)
                             - (*(float *)(v3 + 156) * *(float *)(v3 + 352)
                              + *(float *)(v3 + 144) * *(float *)(v3 + 348)
                              + *(float *)(v3 + 132) * *(float *)(v3 + 344))
                             * 0.0263671875
                             * igi2_frame.vTiltRad
                             / (igi2_frame.ptVehicleType->vMaxSpeed
                              * 0.4000000059604645);
              v6 = -igi2_frame.vTiltRad;
              if ( v6 <= igi2_frame.ptVehicleTypea )
              {
                if ( igi2_frame.vTiltRad < (double)igi2_frame.ptVehicleTypea )
                  igi2_frame.ptVehicleTypea = igi2_frame.vTiltRad;
              }
              else
              {
                igi2_frame.ptVehicleTypea = v6;
              }
              v7 = 0;
              igi2_frame.vTiltRada = *(float *)(v1 + 328) * 21.362831115722656;
              if ( *(int *)(igi2_frame.v39 + 12) > 0 )
              {
                igi2_frame.v43 = igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.nOps + 1;
                do
                {
                  Real32x9_CreateGamma(&igi2_frame.tTilt, igi2_frame.ptVehicleTypea);
                  Real32x9_CreateAlpha(&igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation, igi2_frame.vTiltRada);
                  igi2_frame.Real32x9_Multiply_tTemp.tX.vX = igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vX
                                                * igi2_frame.tOriginalOrientation.tX.vZ
                                                + igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.tY.vX
                                                * igi2_frame.tOriginalOrientation.tX.vY
                                                + igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.tX.vX
                                                * igi2_frame.tOriginalOrientation.tX.vX;
                  igi2_frame.Real32x9_Multiply_tTemp.tX.vY = igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vY
                                                * igi2_frame.tOriginalOrientation.tX.vZ
                                                + igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.tY.vY
                                                * igi2_frame.tOriginalOrientation.tX.vY
                                                + igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.tX.vY
                                                * igi2_frame.tOriginalOrientation.tX.vX;
                  igi2_frame.Real32x9_Multiply_tTemp.tX.vZ = igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vZ
                                                * igi2_frame.tOriginalOrientation.tX.vZ
                                                + igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.tY.vZ
                                                * igi2_frame.tOriginalOrientation.tX.vY
                                                + igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.tX.vZ
                                                * igi2_frame.tOriginalOrientation.tX.vX;
                  igi2_frame.Real32x9_Multiply_tTemp.tY.vX = igi2_frame.tOriginalOrientation.tY.vZ
                                                * igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vX
                                                + igi2_frame.tOriginalOrientation.tY.vY
                                                * igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.tY.vX
                                                + igi2_frame.tOriginalOrientation.tY.vX
                                                * igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.tX.vX;
                  igi2_frame.Real32x9_Multiply_tTemp.tY.vY = igi2_frame.tOriginalOrientation.tY.vZ
                                                * igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vY
                                                + igi2_frame.tOriginalOrientation.tY.vY
                                                * igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.tY.vY
                                                + igi2_frame.tOriginalOrientation.tY.vX
                                                * igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.tX.vY;
                  igi2_frame.Real32x9_Multiply_tTemp.tY.vZ = igi2_frame.tOriginalOrientation.tY.vZ
                                                * igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vZ
                                                + igi2_frame.tOriginalOrientation.tY.vY
                                                * igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.tY.vZ
                                                + igi2_frame.tOriginalOrientation.tY.vX
                                                * igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.tX.vZ;
                  igi2_frame.Real32x9_Multiply_tTemp.tZ.vX = igi2_frame.tOriginalOrientation.tZ.vZ
                                                * igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vX
                                                + igi2_frame.tOriginalOrientation.tZ.vY
                                                * igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.tY.vX
                                                + igi2_frame.tOriginalOrientation.tZ.vX
                                                * igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.tX.vX;
                  v8 = igi2_frame.v43 + igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.nOps <= 1000;
                  igi2_frame.Real32x9_Multiply_tTemp.nOps = igi2_frame.v43 + igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.nOps;
                  igi2_frame.Real32x9_Multiply_tTemp.tZ.vY = igi2_frame.tOriginalOrientation.tZ.vZ
                                                * igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vY
                                                + igi2_frame.tOriginalOrientation.tZ.vY
                                                * igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.tY.vY
                                                + igi2_frame.tOriginalOrientation.tZ.vX
                                                * igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.tX.vY;
                  igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ = igi2_frame.tOriginalOrientation.tZ.vZ
                                                * igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vZ
                                                + igi2_frame.tOriginalOrientation.tZ.vY
                                                * igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.tY.vZ
                                                + igi2_frame.tOriginalOrientation.tZ.vX
                                                * igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.tX.vZ;
                  qmemcpy(
                    &igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation,
                    &igi2_frame.Real32x9_Multiply_tTemp,
                    sizeof(igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation));
                  if ( !v8 )
                  {
                    igi2_frame.Real32x9_Normalize_tTemp.tX = igi2_frame.Real32x9_Multiply_tTemp.tX;
                    if ( igi2_frame.Real32x9_Multiply_tTemp.tX.vX != 0.0
                      || igi2_frame.Real32x9_Multiply_tTemp.tX.vY != 0.0
                      || igi2_frame.Real32x9_Multiply_tTemp.tX.vZ != 0.0 )
                    {
                      v9 = sqrt(
                             igi2_frame.Real32x9_Multiply_tTemp.tX.vX * igi2_frame.Real32x9_Multiply_tTemp.tX.vX
                           + igi2_frame.Real32x9_Multiply_tTemp.tX.vY * igi2_frame.Real32x9_Multiply_tTemp.tX.vY
                           + igi2_frame.Real32x9_Multiply_tTemp.tX.vZ * igi2_frame.Real32x9_Multiply_tTemp.tX.vZ);
                      igi2_frame.Real32x9_Normalize_tTemp.tX.vX = igi2_frame.Real32x9_Multiply_tTemp.tX.vX * (1.0 / v9);
                      igi2_frame.Real32x9_Normalize_tTemp.tX.vY = igi2_frame.Real32x9_Normalize_tTemp.tX.vY * (1.0 / v9);
                      igi2_frame.Real32x9_Normalize_tTemp.tX.vZ = igi2_frame.Real32x9_Normalize_tTemp.tX.vZ * (1.0 / v9);
                    }
                    tTemp_.vX = igi2_frame.Real32x9_Multiply_tTemp.tZ.vY * igi2_frame.Real32x9_Multiply_tTemp.tX.vZ
                              - igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ * igi2_frame.Real32x9_Multiply_tTemp.tX.vY;
                    tTemp_.vY = -(igi2_frame.Real32x9_Multiply_tTemp.tZ.vX * igi2_frame.Real32x9_Multiply_tTemp.tX.vZ
                                - igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ * igi2_frame.Real32x9_Multiply_tTemp.tX.vX);
                    tTemp_.vZ = igi2_frame.Real32x9_Multiply_tTemp.tZ.vX * igi2_frame.Real32x9_Multiply_tTemp.tX.vY
                              - igi2_frame.Real32x9_Multiply_tTemp.tZ.vY * igi2_frame.Real32x9_Multiply_tTemp.tX.vX;
                    igi2_frame.Real32x9_Normalize_tTemp.tY = tTemp_;
                    v47.vX = tTemp_.vZ * igi2_frame.Real32x9_Normalize_tTemp.tX.vY - tTemp_.vY * igi2_frame.Real32x9_Normalize_tTemp.tX.vZ;
                    v47.vY = -(tTemp_.vZ * igi2_frame.Real32x9_Normalize_tTemp.tX.vX - tTemp_.vX * igi2_frame.Real32x9_Normalize_tTemp.tX.vZ);
                    v47.vZ = tTemp_.vY * igi2_frame.Real32x9_Normalize_tTemp.tX.vX - tTemp_.vX * igi2_frame.Real32x9_Normalize_tTemp.tX.vY;
                    igi2_frame.Real32x9_Normalize_tTemp.tZ = v47;
                    if ( tTemp_.vX != 0.0 || tTemp_.vY != 0.0 || tTemp_.vZ != 0.0 )
                    {
                      v10 = sqrt(tTemp_.vZ * tTemp_.vZ + tTemp_.vY * tTemp_.vY + tTemp_.vX * tTemp_.vX);
                      igi2_frame.Real32x9_Normalize_tTemp.tY.vX = tTemp_.vX * (1.0 / v10);
                      igi2_frame.Real32x9_Normalize_tTemp.tY.vY = igi2_frame.Real32x9_Normalize_tTemp.tY.vY * (1.0 / v10);
                      igi2_frame.Real32x9_Normalize_tTemp.tY.vZ = igi2_frame.Real32x9_Normalize_tTemp.tY.vZ * (1.0 / v10);
                    }
                    if ( v47.vX != 0.0 || v47.vY != 0.0 || v47.vZ != 0.0 )
                    {
                      v11 = sqrt(v47.vX * v47.vX + v47.vY * v47.vY + v47.vZ * v47.vZ);
                      igi2_frame.Real32x9_Normalize_tTemp.tZ.vX = v47.vX * (1.0 / v11);
                      igi2_frame.Real32x9_Normalize_tTemp.tZ.vY = igi2_frame.Real32x9_Normalize_tTemp.tZ.vY * (1.0 / v11);
                      igi2_frame.Real32x9_Normalize_tTemp.tZ.vZ = igi2_frame.Real32x9_Normalize_tTemp.tZ.vZ * (1.0 / v11);
                    }
                    qmemcpy(&igi2_frame.Real32x9_Multiply_tTemp, &igi2_frame.Real32x9_Normalize_tTemp, sizeof(igi2_frame.Real32x9_Multiply_tTemp));
                    igi2_frame.Real32x9_Multiply_tTemp.nOps = 0;
                  }
                  igi2_frame.v36[0] = igi2_frame.tTilt.tZ.vX * igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.tX.vZ
                         + igi2_frame.tTilt.tY.vX * igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.tX.vY
                         + igi2_frame.tTilt.tX.vX * igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.tX.vX;
                  igi2_frame.v36[1] = igi2_frame.tTilt.tZ.vY * igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.tX.vZ
                         + igi2_frame.tTilt.tY.vY * igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.tX.vY
                         + igi2_frame.tTilt.tX.vY * igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.tX.vX;
                  igi2_frame.v36[2] = igi2_frame.tTilt.tZ.vZ * igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.tX.vZ
                         + igi2_frame.tTilt.tY.vZ * igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.tX.vY
                         + igi2_frame.tTilt.tX.vZ * igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.tX.vX;
                  igi2_frame.v36[3] = igi2_frame.tTilt.tZ.vX * igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.tY.vZ
                         + igi2_frame.tTilt.tY.vX * igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.tY.vY
                         + igi2_frame.tTilt.tX.vX * igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.tY.vX;
                  igi2_frame.v36[4] = igi2_frame.tTilt.tZ.vY * igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.tY.vZ
                         + igi2_frame.tTilt.tY.vY * igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.tY.vY
                         + igi2_frame.tTilt.tX.vY * igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.tY.vX;
                  igi2_frame.v36[5] = igi2_frame.tTilt.tZ.vZ * igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.tY.vZ
                         + igi2_frame.tTilt.tY.vZ * igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.tY.vY
                         + igi2_frame.tTilt.tX.vZ * igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.tY.vX;
                  igi2_frame.v36[6] = igi2_frame.tTilt.tZ.vX * igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vZ
                         + igi2_frame.tTilt.tY.vX * igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vY
                         + igi2_frame.tTilt.tX.vX * igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vX;
                  igi2_frame.v36[7] = igi2_frame.tTilt.tZ.vY * igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vZ
                         + igi2_frame.tTilt.tY.vY * igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vY
                         + igi2_frame.tTilt.tX.vY * igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vX;
                  v12 = igi2_frame.tTilt.nOps + igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.nOps + 1;
                  v13 = igi2_frame.tTilt.nOps + igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.nOps - 999 < 0;
                  LODWORD(igi2_frame.v36[9]) = v12;
                  igi2_frame.v36[8] = igi2_frame.tTilt.tZ.vZ * igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vZ
                         + igi2_frame.tTilt.tY.vZ * igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vY
                         + igi2_frame.tTilt.tX.vZ * igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vX;
                  qmemcpy(
                    &igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation,
                    igi2_frame.v36,
                    sizeof(igi2_frame.tRigidDynCubeObj.tModelObj.tOrientation));
                  if ( !(v13 ^ __OFSUB__(v12, 1000) | (v12 == 1000)) )
                  {
                    igi2_frame.v38[1] = igi2_frame.v36[1];
                    igi2_frame.v38[0] = igi2_frame.v36[0];
                    igi2_frame.v38[2] = igi2_frame.v36[2];
                    if ( igi2_frame.v36[0] != 0.0 || igi2_frame.v36[1] != 0.0 || igi2_frame.v36[2] != 0.0 )
                    {
                      v14 = sqrt(igi2_frame.v36[0] * igi2_frame.v36[0] + igi2_frame.v36[1] * igi2_frame.v36[1] + igi2_frame.v36[2] * igi2_frame.v36[2]);
                      igi2_frame.v38[0] = igi2_frame.v36[0] * (1.0 / v14);
                      igi2_frame.v38[1] = igi2_frame.v38[1] * (1.0 / v14);
                      igi2_frame.v38[2] = igi2_frame.v38[2] * (1.0 / v14);
                    }
                    igi2_frame.v27 = igi2_frame.v36[7] * igi2_frame.v36[2] - igi2_frame.v36[8] * igi2_frame.v36[1];
                    igi2_frame.v38[3] = igi2_frame.v27;
                    igi2_frame.v28 = -(igi2_frame.v36[6] * igi2_frame.v36[2] - igi2_frame.v36[8] * igi2_frame.v36[0]);
                    igi2_frame.v38[4] = igi2_frame.v28;
                    igi2_frame.v29 = igi2_frame.v36[6] * igi2_frame.v36[1] - igi2_frame.v36[7] * igi2_frame.v36[0];
                    igi2_frame.v38[5] = igi2_frame.v29;
                    igi2_frame.v30 = igi2_frame.v29 * igi2_frame.v38[1] - igi2_frame.v28 * igi2_frame.v38[2];
                    igi2_frame.v38[6] = igi2_frame.v30;
                    igi2_frame.v31 = -(igi2_frame.v29 * igi2_frame.v38[0] - igi2_frame.v27 * igi2_frame.v38[2]);
                    igi2_frame.v38[7] = igi2_frame.v31;
                    igi2_frame.v32 = igi2_frame.v28 * igi2_frame.v38[0] - igi2_frame.v27 * igi2_frame.v38[1];
                    igi2_frame.v38[8] = igi2_frame.v32;
                    if ( igi2_frame.v27 != 0.0 || igi2_frame.v28 != 0.0 || igi2_frame.v29 != 0.0 )
                    {
                      v15 = sqrt(igi2_frame.v29 * igi2_frame.v29 + igi2_frame.v28 * igi2_frame.v28 + igi2_frame.v27 * igi2_frame.v27);
                      igi2_frame.v38[3] = igi2_frame.v27 * (1.0 / v15);
                      igi2_frame.v38[4] = igi2_frame.v38[4] * (1.0 / v15);
                      igi2_frame.v38[5] = igi2_frame.v38[5] * (1.0 / v15);
                    }
                    if ( igi2_frame.v30 != 0.0 || igi2_frame.v31 != 0.0 || igi2_frame.v32 != 0.0 )
                    {
                      v16 = 1.0 / sqrt(igi2_frame.v30 * igi2_frame.v30 + igi2_frame.v31 * igi2_frame.v31 + igi2_frame.v32 * igi2_frame.v32);
                      igi2_frame.v38[6] = igi2_frame.v30 * v16;
                      igi2_frame.v38[7] = igi2_frame.v38[7] * v16;
                      igi2_frame.v38[8] = igi2_frame.v38[8] * v16;
                    }
                    qmemcpy(igi2_frame.v36, igi2_frame.v38, sizeof(igi2_frame.v36));
                    igi2_frame.v36[9] = 0.0;
                  }
                  v17 = *((_DWORD *)pxPrimitive + 6);
                  v18 = *((int **)pxPrimitive + 5);
                  igi2_frame.tContext.isExcludeTestPassed = false;
                  igi2_frame.tContext.ptRigidDynCubeObj = &igi2_frame.tRigidDynCubeObj;
                  v19 = *((struct HazingDynCubeObj_t ***)pxPrimitive + 8);
                  igi2_frame.tContext.tLightContext.nLightNum = v17;
                  igi2_frame.tContext.tLightContext.pnLightList = v18;
                  v20 = *((_DWORD *)pxPrimitive + 7);
                  igi2_frame.tContext.tLightContext.pptHazingList = v19;
                  igi2_frame.tContext.isSort = true;
                  igi2_frame.tContext.tLightContext.nNumHazingBox = v20;
                  RenderMode_tActiveRenderMode.apfRenderModeMethod[Mesh3D_eDrawRigidMeshRenderModeMethod](&igi2_frame.tContext);
                  ++v7;
                  igi2_frame.vTiltRada = igi2_frame.vTiltRada + igi2_frame.vDeltaAngle;
                }
                while ( v7 < (int)(*(_DWORD *)(igi2_frame.v39 + 12)) );
              }
            }
          }
        }
      }
    }
  }
}

// source: j/0/vehicles/rotor.c:558  [size~]
void __cdecl Rotor_EnterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { _BYTE v17[24]; };
    struct { char igi2_o1[24]; _BYTE v18[40]; };
    char igi2_extent[76];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  _DWORD *v2; // ebx
  int v3; // edx
  int *v4; // eax
  int v5; // edi
  int v6; // edx
  int v7; // eax
  struct HazingDynCubeObj_t **v8; // edi
  int v9; // ecx
  struct QTask_s *ptHead; // ebp
  bool v11; // zf
  int v12; // ecx
  int v13; // edx
  struct QTask_s *v14; // eax
  void (__cdecl *pfHandler)(int, _BYTE *); // eax
  int v16; // edx

  v2 = Primitive_ptNextFreePrimitive;
  Primitive_ptNextFreePrimitive = (char *)Primitive_ptNextFreePrimitive + 36;
  if ( (char *)Primitive_ptNextFreePrimitive - Primitive_asPrimitive[0] > (char *)Primitive_nMaxPrimitiveUsage )
  {
    Primitive_nMaxPrimitiveUsage = (unsigned int)Primitive_ptNextFreePrimitive - Primitive_asPrimitive[0];
    if ( (char *)Primitive_ptNextFreePrimitive - Primitive_asPrimitive[0] > (char *)dword_6B9E3C )
      v2 = nullptr;
  }
  v3 = Lightsource_nLightDataStackPos;
  v2[1] = Rotor_nPrimType;
  v4 = (int *)(4 * Lightsource_nLightDataBufferPos + 140666816);
  v2[3] = ptQTask;
  qmemcpy(v4, Lightsource_anLightDataStack, 4 * v3);
  v5 = v3 + Lightsource_nLightDataBufferPos;
  v2[6] = v3;
  v6 = Hazinglayers_iHazingBuffer;
  v2[5] = v4;
  v7 = Hazinglayers_iHazingStack;
  Lightsource_nLightDataBufferPos = v5;
  v8 = (struct HazingDynCubeObj_t **)(4 * v6 + 129834072);
  v2[8] = v8;
  qmemcpy(v8, Hazinglayers_aptHazingStack, 4 * v7);
  v9 = v2[1];
  v2[7] = v7;
  Hazinglayers_iHazingBuffer = v7 + v6;
  RenderMode_tActiveRenderMode.apfRenderModeMethod[v9](v2);
  qmemcpy(igi2_frame.v17, &ptQTask[1], sizeof(igi2_frame.v17));
  ptHead = ptQTask->tQTaskChildren.ptHead;
  qmemcpy(igi2_frame.v18, &ptQTask[3].ptPrev, sizeof(igi2_frame.v18));
  v11 = ptHead->ptNext == nullptr;
  dword_834E068 = (int)v2;
  if ( !v11 )
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
        pfHandler = (void (__cdecl *)(int, _BYTE *))QTask_aatQTaskFinalEvent[MagicObj_eMagicObjEnterEvent][*(unsigned __int16 *)(v12 + 36)].pfHandler;
        v16 = v13 + 1;
        QTask_nProtectedQTaskStackOffset = v16;
        if ( pfHandler )
        {
          pfHandler(v12, igi2_frame.v17);
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

// source: j/0/vehicles/rotor.c:606  [size]
void __cdecl Rotor_PhysicsObjTypeDeleteHandler(struct QTask_s *ptQTask, void *pxContext)
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

// source: j/0/vehicles/rotor.c:629  [anchor-strings]
void __cdecl Rotor_Open()
{
  int v0; // eax
  unsigned __int16 v1; // si
  _DWORD *v2; // esi
  _DWORD pxContext[3]; // [esp+8h] [ebp-Ch] BYREF

  Rotor_eQTaskType = QTask_NewQTaskType("Rotor", 336, RigidMagicObj_eQTaskType, 0, 0);
  v0 = 0;
  while ( RenderMode_atRenderModeMethod[v0].isAllocated )
  {
    if ( ++v0 >= 128 )
    {
      LDebug_Error("RenderMode: Failed to create new method '%s'", "RotorPrimitive");
      abort();
    }
  }
  RenderMode_atRenderModeMethod[v0].zName = "RotorPrimitive";
  RenderMode_atRenderModeMethod[v0].isAllocated = 1;
  Rotor_nPrimType = v0;
  pxContext[0] = v0;
  pxContext[1] = Rotor_DrawHandler;
  RenderMode_EnumerateRenderModes(
    (void (__cdecl *)(struct RenderModeEnumerateContext_s *, void *))Primitive_SetPrimitiveDrawCallback,
    pxContext);
  v1 = Rotor_eQTaskType;
  QTask_LinkQTaskEventHandlerFn(Rotor_eQTaskType, 0, Rotor_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, Rotor_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, Rotor_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v1, MagicObj_eUpdateMagicObjEvent, Rotor_UpdateMagicObjHandler);
  QTask_LinkQTaskEventHandlerFn(v1, GameFunctions_eWeaponHitQTaskEvent, Rotor_WeaponHitHandler);
  QTask_LinkQTaskEventHandlerFn(v1, GameFunctions_eExplosionHitQTaskEvent, nullptr);
  QTask_LinkQTaskEventHandlerFn(v1, PhysicsObjType_eParsePhysicsObjTypeEvent, Rotor_ParsePhysicsObjTypeHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    PhysicsObjType_eGetPhysicsObjTypeSizeEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Rotor_GetGetPhysicsObjTypeSizeHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 5, Rotor_EnterHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, Screen_eDrawQTaskEvent, nullptr);
  QTask_LinkQTaskEventHandlerFn(v1, MagicObj_eMagicObjEnterEvent, nullptr);
  QTask_LinkQTaskEventHandlerFn(v1, PhysicsObjType_ePhysicsObjTypeDeleteEvent, Rotor_PhysicsObjTypeDeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v1, BulletHole_eCreateBulletHoleTaskEvent, nullptr);
  Symbol_Register(
    "TASKTYPE_ROTOR",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)v1,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  v2 = Mem_AllocFn(18444, 4);
  v2[1] = 0;
  *v2 = 0;
  v2[4610] = "TASKTYPE_ROTOR";
  Wildcard_CreateNFA("TASKTYPE_ROTOR", v2 + 2, (char *)v2 + 10248);
  List_AddTail(v2, (int)&MagicObjConfig_tTaskTypeEnumList);
}

// source: j/0/vehicles/rotor.c:676  [size]
void __cdecl Rotor_Close()
{
  QTask_DeleteQTaskType(Rotor_eQTaskType);
  RenderMode_atRenderModeMethod[Rotor_nPrimType].isAllocated = 0;
}

// source: j/0/vehicles/rotor.c:693  [size]
unsigned __int16 __cdecl Rotor_GetQTaskType()
{
  return Rotor_eQTaskType;
}
