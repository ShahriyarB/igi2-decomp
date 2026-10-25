/* j/0/vehicles/rocketpod.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/vehicles/rocketpod.c:78  [anchor-mhash]
void __cdecl RocketPod_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v2; // eax
  struct QTask_s *ptNext; // ecx
  struct Game_s *v4; // eax
  unsigned int v5; // edi
  int v6; // edi
  unsigned int v7; // edi

  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][RigidMagicObj_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  v2 = *((struct QTask_s **)pxContext + 38);
  ptQTask[8].tQTaskChildren.ptHead = v2;
  ptNext = v2->ptNext;
  v4 = Game_ptGame;
  v5 = (Game_ptGame->tRunRandomState.anRandom[0] >> 7) ^ Game_ptGame->tRunRandomState.anRandom[2];
  Game_ptGame->tRunRandomState.anRandom[2] = v5;
  v6 = v5 ^ v4->tRunRandomState.anRandom[1];
  v4->tRunRandomState.anRandom[1] = v6;
  v7 = v6 + v4->tRunRandomState.anRandom[0];
  v4->tRunRandomState.anRandom[0] = v7;
  ptQTask[8].tQTaskChildren.ptMiddle = (struct QTask_s *)(v7 % (unsigned int)ptNext);
}

// source: j/0/vehicles/rocketpod.c:117  [size]
void __cdecl RocketPod_DeleteHandler(struct QTask_s *ptQTask)
{
  World_RemoveDynCubeObj((struct World_s *)ptQTask[2].ptParent, (struct DynCubeObj_s *)ptQTask);
}

// source: j/0/vehicles/rocketpod.c:137  [anchor-caller]
void __cdecl RocketPod_RunHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real64x3_t v18; };
    struct { char igi2_o1[40]; struct AIDetectionListItem_s *ptThis; };
    struct { char igi2_o2[44]; struct AIDetectionListItem_s *ptTemp; };
    struct { char igi2_o3[48]; struct Vehicle_s *ptVehicle; };
    struct { char igi2_o4[52]; struct LineOfSightOutputContext_s tOutputContext; };
    struct { char igi2_o5[60]; struct real32x3_t Real32x3_Rotate_tTemp; };
    struct { char igi2_o6[72]; struct AIDetectionLineOfSightContext_s tAIDetectionLineOfSightContext; };
    struct { char igi2_o7[88]; struct real64x3_t tMissilePos; };
    struct { char igi2_o8[112]; struct real64x3_t Real64x3_RotateInverse_tTemp; };
    struct { char igi2_o9[136]; struct real64x3_t tTargetPos; };
    char igi2_extent[160];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptMiddle; // ecx
  struct Vehicle_s *ptNext; // eax
  struct AIDetectionListItem_s *ptForces; // ecx
  struct AIDetectionListItem_s *v4; // eax
  bool v5; // zf
  int v6; // eax
  struct QReference_s *ptQTaskRef; // edx
  double *pxObject; // eax
  double v9; // st7
  double v10; // st6
  double v11; // st5
  double v12; // st7
  double v13; // st7
  double v14; // st6
  double v15; // st7
  double v16; // st6
  double v17; // st5

  ptMiddle = ptQTask[8].tQTaskChildren.ptMiddle;
  ptNext = (struct Vehicle_s *)ptQTask[8].ptNext;
  igi2_frame.ptVehicle = ptNext;
  if ( (int)ptMiddle < 0 )
  {
    ptForces = (struct AIDetectionListItem_s *)ptNext[1].tPhysicsObj.tPhysics.ptForces;
    v4 = ptForces->ptNext;
    v5 = ptForces->ptNext == nullptr;
    igi2_frame.ptThis = ptForces;
    igi2_frame.ptTemp = v4;
    if ( !v5 )
    {
      while ( 1 )
      {
        v6 = 0;
        while ( !ptForces->aisFullVisible[v6] )
        {
          if ( ++v6 >= 3 )
            goto LABEL_16;
        }
        ptQTaskRef = ptForces->ptQTaskRef;
        pxObject = (double *)ptQTaskRef->pxObject;
        if ( pxObject )
        {
          v9 = pxObject[5] - *(double *)&ptQTask[1].ptNext;
          v10 = pxObject[6] - *(double *)&ptQTask[1].tQTaskChildren.ptHead;
          v11 = pxObject[7] - *(double *)&ptQTask[1].tQTaskChildren.ptTail;
          igi2_frame.Real64x3_RotateInverse_tTemp.vX = *(float *)&ptQTask[3].tQTaskChildren.ptTail * v10
                                          + *(float *)&ptQTask[3].tQTaskRefList.ptTail * v11
                                          + *(float *)&ptQTask[3].ptPrev * v9;
          igi2_frame.Real64x3_RotateInverse_tTemp.vY = *(float *)&ptQTask[3].tQTaskRefList.ptHead * v10
                                          + *(float *)&ptQTask[3].ptParent * v11
                                          + *(float *)&ptQTask[3].tQTaskChildren.ptHead * v9;
          igi2_frame.Real64x3_RotateInverse_tTemp.vZ = *(float *)&ptQTask[3].tQTaskRefList.ptMiddle * v10
                                          + *(float *)&ptQTask[3].eQTaskType * v11
                                          + *(float *)&ptQTask[3].tQTaskChildren.ptMiddle * v9;
          if ( igi2_frame.Real64x3_RotateInverse_tTemp.vY >= 0.0 )
          {
            qmemcpy(&igi2_frame.v18, &igi2_frame.Real64x3_RotateInverse_tTemp, sizeof(igi2_frame.v18));
            v12 = GameFunctions_CalcGamma(igi2_frame.v18);
            if ( v12 < 0.0 )
              v12 = -v12;
            if ( v12 < 1.3 )
            {
              igi2_frame.tAIDetectionLineOfSightContext.tCollisionEvaluateContext.ptQTask = ptQTask;
              igi2_frame.tAIDetectionLineOfSightContext.ptDetectorTask = ptQTask;
              igi2_frame.tAIDetectionLineOfSightContext.ptDetecteeTask = (struct QTask_s *)ptQTaskRef->pxObject;
              if ( World_LineOfSight(
                     Game_ptGame->ptWorld,
                     (struct real64x3_t *)&ptQTask[1],
                     (struct real64x3_t *)((char *)ptQTaskRef->pxObject + 40),
                     AIDetection_eLineOfSightQTaskEvent,
                     &igi2_frame.tAIDetectionLineOfSightContext.tCollisionEvaluateContext,
                     0xFFFFFFFF,
                     WORLD_DYNCUBETREE_CATEGORY_ALL,
                     &igi2_frame.tOutputContext) )
              {
                v13 = (*(float *)&ptQTask[3].tQTaskChildren.ptMiddle + *(float *)&ptQTask[3].ptPrev) * 0.0;
                v14 = *(float *)&ptQTask[3].tQTaskChildren.ptHead;
                qmemcpy(&igi2_frame.tMissilePos, &ptQTask[1], sizeof(igi2_frame.tMissilePos));
                v15 = v13 + v14 * 2048.0;
                v16 = (*(float *)&ptQTask[3].tQTaskRefList.ptMiddle + *(float *)&ptQTask[3].tQTaskChildren.ptTail) * 0.0
                    + *(float *)&ptQTask[3].tQTaskRefList.ptHead * 2048.0;
                v17 = *(float *)&ptQTask[3].eQTaskType + *(float *)&ptQTask[3].tQTaskRefList.ptTail;
                qmemcpy(&igi2_frame.tTargetPos, (char *)igi2_frame.ptThis->ptQTaskRef->pxObject + 40, sizeof(igi2_frame.tTargetPos));
                igi2_frame.Real32x3_Rotate_tTemp.vZ = v17 * 0.0 + *(float *)&ptQTask[3].ptParent * 2048.0;
                igi2_frame.v18.vZ = 0.0;
                igi2_frame.tMissilePos.vX = v15 + igi2_frame.tMissilePos.vX;
                *(_QWORD *)&igi2_frame.v18.vY = __PAIR64__(&igi2_frame.tTargetPos, (unsigned int)igi2_frame.ptVehicle);
                igi2_frame.tMissilePos.vY = v16 + igi2_frame.tMissilePos.vY;
                igi2_frame.tMissilePos.vZ = igi2_frame.Real32x3_Rotate_tTemp.vZ + igi2_frame.tMissilePos.vZ;
                *(float *)&igi2_frame.v18.vY = igi2_frame.ptVehicle->tPhysicsObj.tPhysics.vCMSpeed * 0.00732421875 + 5.0;
                Missile_New(
                  Level_ptDynamicQTask,
                  ptQTask,
                  ptQTask,
                  &igi2_frame.tMissilePos,
                  (struct real32x9_t *)&ptQTask[3].ptPrev,
                  *(float *)&igi2_frame.v18.vY,
                  &igi2_frame.tTargetPos,
                  nullptr,
                  (char *)&stru_690D20.eQTaskType,
                  nullptr);
                ptQTask[8].tQTaskChildren.ptMiddle = (struct QTask_s *)((char *)ptQTask[8].tQTaskChildren.ptHead->ptNext
                                                                      + Random_GetRandomNumberBelowLimit(
                                                                          &Game_ptGame->tRunRandomState,
                                                                          (int)ptQTask[8].tQTaskChildren.ptHead->ptNext));
              }
            }
          }
        }
LABEL_16:
        igi2_frame.ptThis = igi2_frame.ptTemp;
        igi2_frame.ptTemp = igi2_frame.ptTemp->ptNext;
        if ( !igi2_frame.ptTemp )
          break;
        ptForces = igi2_frame.ptThis;
      }
    }
  }
  --*(int *)&ptQTask[8].tQTaskChildren.ptMiddle;
}

// source: j/0/vehicles/rocketpod.c:252  [size]
void __cdecl RocketPod_UpdateMagicObjHandler(struct QTask_s *ptQTask, void *pxContext)
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
  double v3; // st6
  float *v4; // eax
  double v5; // st5
  double v6; // st4
  double v7; // st3
  double *v8; // eax
  double v9; // st7
  double v10; // st7
  int *v11; // eax
  int v12; // eax
  double v13; // st6
  int v14; // eax
  int v15; // ecx
  struct QTask_s *ptNext; // edx
  double v17; // st7
  double v18; // st6

  v2 = *(float *)&ptQTask[5].ptPrev;
  v3 = *(float *)&ptQTask[5].tQTaskChildren.ptHead;
  v4 = *((float **)pxContext + 1);
  v5 = *(float *)&ptQTask[5].tQTaskChildren.ptMiddle;
  *(double *)igi2_frame.Real64x3_Rotate_tTemp = v4[2] * v5 + v4[1] * v3 + *v4 * v2;
  *(double *)&igi2_frame.Real64x3_Rotate_tTemp[8] = v4[5] * v5 + v4[4] * v3 + v4[3] * v2;
  v6 = v4[8] * v5 + v4[7] * v3;
  v7 = v4[6];
  v8 = *(double **)pxContext;
  *(double *)&igi2_frame.Real64x3_Rotate_tTemp[16] = v6 + v7 * v2;
  qmemcpy(&igi2_frame.tNewPos, igi2_frame.Real64x3_Rotate_tTemp, sizeof(igi2_frame.tNewPos));
  igi2_frame.tNewPos.vX = *(double *)igi2_frame.Real64x3_Rotate_tTemp + *v8;
  igi2_frame.tNewPos.vY = igi2_frame.tNewPos.vY + v8[1];
  igi2_frame.tNewPos.vZ = igi2_frame.tNewPos.vZ + v8[2];
  if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
    v9 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  else
    v9 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  if ( v9 >= *(float *)&ptQTask[6].ptPrev )
  {
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
      v10 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v10 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  }
  else
  {
    v10 = *(float *)&ptQTask[6].ptPrev;
  }
  v11 = *(int **)&ptQTask[2].eQTaskType;
  if ( v11 && (v12 = *v11) != 0 )
    v13 = *(float *)(*(_DWORD *)(*(_DWORD *)(v12 + 12) + 12) + 120);
  else
    v13 = 1.0;
  igi2_frame.ptDynCubeObj = v13 * v10;
  World_MoveDynCubeObjRadius(Game_ptGame->ptWorld, (struct DynCubeObj_s *)ptQTask, &igi2_frame.tNewPos, igi2_frame.ptDynCubeObj);
  v14 = *((_DWORD *)pxContext + 1);
  *(float *)igi2_frame.Real64x3_Rotate_tTemp = *(float *)&ptQTask[4].tQTaskRefList.ptTail * *(float *)(v14 + 8)
                                  + *(float *)&ptQTask[4].ptPrev * *(float *)v14
                                  + *(float *)(v14 + 4) * *(float *)&ptQTask[4].tQTaskChildren.ptTail;
  *(float *)&igi2_frame.Real64x3_Rotate_tTemp[4] = *(float *)&ptQTask[4].ptParent * *(float *)(v14 + 8)
                                      + *(float *)&ptQTask[4].tQTaskChildren.ptHead * *(float *)v14
                                      + *(float *)(v14 + 4) * *(float *)&ptQTask[4].tQTaskRefList.ptHead;
  *(float *)&igi2_frame.Real64x3_Rotate_tTemp[8] = *(float *)&ptQTask[4].eQTaskType * *(float *)(v14 + 8)
                                      + *(float *)&ptQTask[4].tQTaskChildren.ptMiddle * *(float *)v14
                                      + *(float *)(v14 + 4) * *(float *)&ptQTask[4].tQTaskRefList.ptMiddle;
  *(float *)&igi2_frame.Real64x3_Rotate_tTemp[12] = *(float *)(v14 + 20) * *(float *)&ptQTask[4].tQTaskRefList.ptTail
                                       + *(float *)(v14 + 12) * *(float *)&ptQTask[4].ptPrev
                                       + *(float *)&ptQTask[4].tQTaskChildren.ptTail * *(float *)(v14 + 16);
  *(float *)&igi2_frame.Real64x3_Rotate_tTemp[16] = *(float *)(v14 + 20) * *(float *)&ptQTask[4].ptParent
                                       + *(float *)(v14 + 12) * *(float *)&ptQTask[4].tQTaskChildren.ptHead
                                       + *(float *)&ptQTask[4].tQTaskRefList.ptHead * *(float *)(v14 + 16);
  *(float *)&igi2_frame.Real64x3_Rotate_tTemp[20] = *(float *)(v14 + 20) * *(float *)&ptQTask[4].eQTaskType
                                       + *(float *)(v14 + 12) * *(float *)&ptQTask[4].tQTaskChildren.ptMiddle
                                       + *(float *)&ptQTask[4].tQTaskRefList.ptMiddle * *(float *)(v14 + 16);
  *(float *)&igi2_frame.Real64x3_Rotate_tTemp[24] = *(float *)(v14 + 32) * *(float *)&ptQTask[4].tQTaskRefList.ptTail
                                       + *(float *)(v14 + 24) * *(float *)&ptQTask[4].ptPrev
                                       + *(float *)&ptQTask[4].tQTaskChildren.ptTail * *(float *)(v14 + 28);
  v15 = *(_DWORD *)(v14 + 36);
  ptNext = ptQTask[5].ptNext;
  *(float *)&igi2_frame.Real64x3_Rotate_tTemp[28] = *(float *)(v14 + 32) * *(float *)&ptQTask[4].ptParent
                                       + *(float *)(v14 + 24) * *(float *)&ptQTask[4].tQTaskChildren.ptHead
                                       + *(float *)&ptQTask[4].tQTaskRefList.ptHead * *(float *)(v14 + 28);
  v17 = *(float *)(v14 + 32) * *(float *)&ptQTask[4].eQTaskType
      + *(float *)(v14 + 24) * *(float *)&ptQTask[4].tQTaskChildren.ptMiddle;
  v18 = *(float *)&ptQTask[4].tQTaskRefList.ptMiddle * *(float *)(v14 + 28);
  *(_DWORD *)&igi2_frame.Real64x3_Rotate_tTemp[36] = (char *)&ptNext->ptNext + v15 + 1;
  *(float *)&igi2_frame.Real64x3_Rotate_tTemp[32] = v17 + v18;
  qmemcpy(&ptQTask[3].ptPrev, igi2_frame.Real64x3_Rotate_tTemp, sizeof(struct QTask_s));
}

// source: j/0/vehicles/rocketpod.c:306  [anchor-mhash]
void __cdecl RocketPod_ParseMagicObjParametersHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // eax
  _DWORD *v3; // esi
  struct ArgList_s *v4; // edi

  v2 = *((_DWORD *)pxContext + 2);
  v3 = *(_DWORD **)pxContext;
  v4 = *((struct ArgList_s **)pxContext + 1);
  if ( v4->isQVM )
  {
    pxContext = nullptr;
    QVM_EvalArg(&pxContext, 4, v4, v2, 1);
    *v3 = 30 * (_DWORD)pxContext;
  }
  else
  {
    *v3 = 30 * Expression_EvalInt(v4->aptExpression[v2]);
  }
}

// source: j/0/vehicles/rocketpod.c:328  [size]
void __cdecl RocketPod_GetMagicObjParameterSizeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = 4;
}

// source: j/0/vehicles/rocketpod.c:344  [size]
void __cdecl RocketPod_WeaponHitHandler(struct QTask_s *ptQTask, void *pxContext)
{
  void (__cdecl *pfHandler)(struct QTask_s *, ...); // ecx

  pfHandler = (void (__cdecl *)(struct QTask_s *, ...))QTask_aatQTaskFinalEvent[GameFunctions_eWeaponHitQTaskEvent][ptQTask[8].ptNext->eQTaskType].pfHandler;
  if ( pfHandler )
    pfHandler(ptQTask[8].ptNext, pxContext);
}

// source: j/0/vehicles/rocketpod.c:373  [size]
void __cdecl RocketPod_AILineOfSightHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v2; // eax

  v2 = *((struct QTask_s **)pxContext + 2);
  *(_BYTE *)pxContext = v2 != ptQTask && *((struct QTask_s **)pxContext + 3) != ptQTask && ptQTask[8].ptNext != v2;
}

// source: j/0/vehicles/rocketpod.c:402  [anchor-strings]
void __cdecl RocketPod_UpdateTagItemsHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // eax
  int v3; // ebx
  struct QTask_s *v4; // esi
  struct QReference_s **v5; // ebp
  struct QTask_s *v6; // eax

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
  *(_DWORD *)(*((_DWORD *)pxContext + 1) + 80) = Mem_AllocFn(4, 4);
  v4 = *(struct QTask_s **)pxContext;
  v5 = *(struct QReference_s ***)(*((_DWORD *)pxContext + 1) + 80);
  v6 = TagItem_Find(*(struct QTask_s **)pxContext, (char *)&stru_690D20);
  if ( v6 || (v6 = TagItem_NewInt32MinMax(v4, (char *)&stru_690D20, 15, 0, 3600)) != nullptr )
    *v5 = v6[7].tQTaskRefList.ptHead;
  else
    *v5 = nullptr;
}

// source: j/0/vehicles/rocketpod.c:434  [anchor-strings]
void __cdecl RocketPod_Open()
{
  unsigned __int16 v0; // si
  _DWORD *v1; // esi

  v0 = QTask_NewQTaskType("RocketPod", 336, RigidMagicObj_eQTaskType, 0, 0);
  RocketPod_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 0, RocketPod_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, RocketPod_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, RocketPod_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v0, MagicObj_eUpdateMagicObjEvent, RocketPod_UpdateMagicObjHandler);
  QTask_LinkQTaskEventHandlerFn(v0, GameFunctions_eWeaponHitQTaskEvent, RocketPod_WeaponHitHandler);
  QTask_LinkQTaskEventHandlerFn(v0, GameFunctions_eExplosionHitQTaskEvent, nullptr);
  QTask_LinkQTaskEventHandlerFn(v0, MagicObj_eGetParseMagicObjParametersEvent, RocketPod_ParseMagicObjParametersHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    MagicObj_eGetMagicObjParameterSizeEvent,
    (void (__cdecl *)(struct QTask_s *, void *))RocketPod_GetMagicObjParameterSizeHandler);
  QTask_LinkQTaskEventHandlerFn(v0, AIDetection_eLineOfSightQTaskEvent, RocketPod_AILineOfSightHandler);
  QTask_LinkQTaskEventHandlerFn(v0, MagicObjConfig_eUpdateTagItemsQTaskEvent, RocketPod_UpdateTagItemsHandler);
  Symbol_Register(
    "TASKTYPE_ROCKETPOD",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)v0,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  v1 = Mem_AllocFn(18444, 4);
  v1[1] = 0;
  *v1 = 0;
  v1[4610] = "TASKTYPE_ROCKETPOD";
  Wildcard_CreateNFA("TASKTYPE_ROCKETPOD", v1 + 2, (char *)v1 + 10248);
  List_AddTail(v1, (int)&MagicObjConfig_tTaskTypeEnumList);
}

// source: j/0/vehicles/rocketpod.c:472  [size]
void __cdecl RocketPod_Close()
{
  QTask_DeleteQTaskType(RocketPod_eQTaskType);
}

// source: j/0/vehicles/rocketpod.c:486  [size]
unsigned __int16 __cdecl RocketPod_GetQTaskType()
{
  return RocketPod_eQTaskType;
}
