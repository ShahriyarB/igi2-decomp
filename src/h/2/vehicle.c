/* h/2/vehicle.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/vehicle.c:111  [anchor-strings]
__declspec(noreturn) void __cdecl Vehicle_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  LDebug_Error("Vehicle create handler must be overloaded");
  abort();
}

// source: h/2/vehicle.c:124  [anchor-strings]
__declspec(noreturn) void __cdecl Vehicle_DeleteHandler(struct QTask_s *ptQTask)
{
  LDebug_Error("Vehicle delete handler must be overloaded");
  abort();
}

// source: h/2/vehicle.c:137  [anchor-strings]
__declspec(noreturn) void __cdecl Vehicle_RunHandler(struct QTask_s *ptQTask)
{
  LDebug_Error("Vehicle run handler must be overloaded");
  abort();
}

// source: h/2/vehicle.c:151  [anchor-mhash]
void __cdecl Vehicle_GetCameraTargetInfoHandler(struct QTask_s *ptQTask, void *pxContext)
{
  double v2; // st7
  double v3; // st7
  int *v4; // edx
  int v5; // edx
  double v6; // st6

  qmemcpy(pxContext, &ptQTask[1], 0x18u);
  *((_DWORD *)pxContext + 6) = ptQTask[8].tQTaskRefList.ptMiddle;
  *((_DWORD *)pxContext + 7) = ptQTask[8].tQTaskRefList.ptTail;
  *((_DWORD *)pxContext + 8) = ptQTask[8].ptParent;
  qmemcpy((char *)pxContext + 36, &ptQTask[3].ptPrev, 0x28u);
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
  {
    v6 = v3 * *(float *)(*(_DWORD *)(*(_DWORD *)(v5 + 12) + 12) + 120);
    *((_DWORD *)pxContext + 20) = 0;
    *((float *)pxContext + 19) = v6;
  }
  else
  {
    *((_DWORD *)pxContext + 20) = 0;
    *((float *)pxContext + 19) = v3 * 1.0;
  }
}

// source: h/2/vehicle.c:186  [size]
void __cdecl Vehicle_CollisionEvaluateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_BYTE *)pxContext = *((_DWORD *)pxContext + 1) != (_DWORD)ptQTask;
}

// source: h/2/vehicle.c:208  [anchor-mhash]
void __cdecl Vehicle_ParsePhysicsObjTypeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  VehicleType_DefineVehicleType(
    *(struct VehicleType_s **)pxContext,
    (int *)pxContext + 2,
    *((struct ArgList_s **)pxContext + 1));
}

// source: h/2/vehicle.c:227  [size]
void __cdecl Vehicle_GetGetPhysicsObjTypeSizeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = 280;
}

// source: h/2/vehicle.c:243  [anchor-mhash]
void __cdecl Vehicle_RegisterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptNext; // eax
  int ptHead; // eax
  int v4; // edx
  struct QTask_s *v5; // ecx
  void (__cdecl *pfHandler)(int, void *); // ecx
  int v7; // edx

  if ( !ptQTask[2].tQTaskChildren.ptHead )
  {
    ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRegisterQTaskEvent][RigidDynCubeObj_eQTaskType].pfHandler)(
      ptQTask,
      pxContext);
    ptNext = ptQTask[3].ptNext;
    if ( ptNext )
    {
      ptHead = (int)ptNext->tQTaskChildren.ptHead;
      if ( *(_DWORD *)ptHead )
      {
        if ( ptHead )
        {
          v4 = QTask_nProtectedQTaskStackOffset;
          do
          {
            if ( *(_DWORD *)ptHead )
              v5 = **(_DWORD **)ptHead != 0 ? *(struct QTask_s **)ptHead : nullptr;
            else
              v5 = nullptr;
            QTask_atProtectedQTaskStack[v4].ptQTask = v5;
            pfHandler = (void (__cdecl *)(int, void *))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRegisterQTaskEvent][*(unsigned __int16 *)(ptHead + 36)].pfHandler;
            v7 = v4 + 1;
            QTask_nProtectedQTaskStackOffset = v7;
            if ( pfHandler )
            {
              pfHandler(ptHead, pxContext);
              v7 = QTask_nProtectedQTaskStackOffset;
            }
            ptHead = dword_849C7DC[v7];
            v4 = v7 - 1;
            QTask_nProtectedQTaskStackOffset = v4;
          }
          while ( ptHead );
        }
      }
    }
  }
}

// source: h/2/vehicle.c:279  [anchor-mhash]
void __cdecl Vehicle_RemoveHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptNext; // eax
  int ptHead; // eax
  int v4; // edx
  struct QTask_s *v5; // ecx
  void (__cdecl *pfHandler)(int, void *); // ecx
  int v7; // edx

  if ( ptQTask[2].tQTaskChildren.ptHead )
  {
    ptNext = ptQTask[3].ptNext;
    if ( ptNext )
    {
      ptHead = (int)ptNext->tQTaskChildren.ptHead;
      if ( *(_DWORD *)ptHead )
      {
        if ( ptHead )
        {
          v4 = QTask_nProtectedQTaskStackOffset;
          do
          {
            if ( *(_DWORD *)ptHead )
              v5 = **(_DWORD **)ptHead != 0 ? *(struct QTask_s **)ptHead : nullptr;
            else
              v5 = nullptr;
            QTask_atProtectedQTaskStack[v4].ptQTask = v5;
            pfHandler = (void (__cdecl *)(int, void *))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRemoveQTaskEvent][*(unsigned __int16 *)(ptHead + 36)].pfHandler;
            v7 = v4 + 1;
            QTask_nProtectedQTaskStackOffset = v7;
            if ( pfHandler )
            {
              pfHandler(ptHead, pxContext);
              v7 = QTask_nProtectedQTaskStackOffset;
            }
            ptHead = dword_849C7DC[v7];
            v4 = v7 - 1;
            QTask_nProtectedQTaskStackOffset = v4;
          }
          while ( ptHead );
        }
      }
    }
    ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRemoveQTaskEvent][RigidDynCubeObj_eQTaskType].pfHandler)(
      ptQTask,
      pxContext);
  }
}

// source: h/2/vehicle.c:318  [anchor-mhash]
void __cdecl Vehicle_AeraActivateCB(struct AreaActivateContext_s *ptContext)
{
  struct QTask_s *ptAreaActivateQTask; // ecx
  struct QTask_s **ptQTask; // edx
  int nTask; // esi

  if ( Vehicle_ptQTaskList && Vehicle_ptQTaskList->nTask > 0 )
  {
    ptAreaActivateQTask = ptContext->ptAreaActivateQTask;
    ptQTask = Vehicle_ptQTaskList->ptQTask;
    nTask = Vehicle_ptQTaskList->nTask;
    do
    {
      if ( AreaActivateQTask_IsInsideArea(ptAreaActivateQTask, (struct real64x3_t *)&(*ptQTask)[1]) )
        ++ptContext->nHitCount;
      ++ptQTask;
      --nTask;
    }
    while ( nTask );
  }
}

// source: h/2/vehicle.c:398  [anchor-strings]
void __cdecl Vehicle_Open()
{
  unsigned __int16 v0; // si

  v0 = QTask_NewQTaskType("Vehicle", 1944, PhysicsObj_eQTaskType, 0, 0);
  Vehicle_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 0, (void (__cdecl *)(struct QTask_s *, void *))Vehicle_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, (void (__cdecl *)(struct QTask_s *))Vehicle_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, (void (__cdecl *)(struct QTask_s *))Vehicle_RunHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 8, Vehicle_GetCameraTargetInfoHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 13, Vehicle_CollisionEvaluateHandler);
  QTask_LinkQTaskEventHandlerFn(v0, AnimQTask_eSaveKeyframeEvent, Vehicle_SaveKeyframeHandler);
  QTask_LinkQTaskEventHandlerFn(v0, PhysicsObjType_eParsePhysicsObjTypeEvent, Vehicle_ParsePhysicsObjTypeHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    PhysicsObjType_eGetPhysicsObjTypeSizeEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Vehicle_GetGetPhysicsObjTypeSizeHandler);
  QTask_LinkQTaskEventHandlerFn(v0, DynCubeObj_eDynCubeObjRegisterQTaskEvent, Vehicle_RegisterHandler);
  QTask_LinkQTaskEventHandlerFn(v0, DynCubeObj_eDynCubeObjRemoveQTaskEvent, Vehicle_RemoveHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Attach_eUpdateAttachmentEvent, nullptr);
  Vehicle_bAreaActivateCriteria = AreaActivateQTask_RegisterCriteria("CRITERIA_VEHICLE", Vehicle_AeraActivateCB);
  Vehicle_eHitZoneDestroyedQTaskEvent = QTask_NewQTaskEventFn(0, "HitZoneDestroyed");
  Vehicle_eTraceHitZoneQTaskEvent = QTask_NewQTaskEventFn(0, "TraceHitZone");
}

// source: h/2/vehicle.c:438  [anchor-hash]
void __cdecl Vehicle_Close()
{
  int v0; // ecx
  int i; // eax
  int v2; // eax

  QTask_DeleteQTaskType(Vehicle_eQTaskType);
  v0 = Vehicle_bAreaActivateCriteria;
  for ( i = 0; (v0 & 1) == 0; ++i )
    v0 >>= 1;
  v2 = i;
  AreaActivate_atCriteria[v2].isUsed = 0;
  Symbol_Remove(AreaActivate_atCriteria[v2].zName);
  QTask_DeleteQTaskEvent(Vehicle_eHitZoneDestroyedQTaskEvent);
  QTask_DeleteQTaskEvent(Vehicle_eTraceHitZoneQTaskEvent);
}

// source: h/2/vehicle.c:459  [size]
unsigned __int16 __cdecl Vehicle_GetQTaskType()
{
  return Vehicle_eQTaskType;
}

// source: h/2/vehicle.c:474  [anchor-callee]
struct Vehicle_s *__cdecl Vehicle_Init(struct Vehicle_s *ptVehicle)
{
  ptVehicle->tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.iRenderGroup = RenderGroup_Vehicle;
  ptVehicle->vRealDeltaAlpha = 0.0;
  ptVehicle->vRealDeltaBeta = 0.0;
  ptVehicle->vRealDeltaGamma = 0.0;
  ptVehicle->vRealThrust = 0.0;
  ptVehicle->vIdealDeltaAlpha = 0.0;
  ptVehicle->vIdealDeltaBeta = 0.0;
  ptVehicle->vIdealDeltaGamma = 0.0;
  ptVehicle->vIdealThrust = 0.0;
  ptVehicle->isBreak = 0;
  return ptVehicle;
}

// source: h/2/vehicle.c:498  [anchor-mhash]
void __cdecl Vehicle_Delete(struct Vehicle_s *ptVehicle)
{
  if ( ptVehicle->tPhysicsObj.tRigidDynCubeObj.tModelObj.ptMagicObjContainer )
  {
    QTask_Delete(ptVehicle->tPhysicsObj.tRigidDynCubeObj.tModelObj.ptMagicObjContainer);
    ptVehicle->tPhysicsObj.tRigidDynCubeObj.tModelObj.ptMagicObjContainer = nullptr;
  }
  ptVehicle->tPhysicsObj.ptType = nullptr;
  Physics_DeAlloc(&ptVehicle->tPhysicsObj.tPhysics);
}

// source: h/2/vehicle.c:515  [anchor-hash]
struct Vehicle_s *__cdecl Vehicle_Run(struct Vehicle_s *ptVehicle)
{
  struct Vehicle_s *result; // eax

  result = (struct Vehicle_s *)ptVehicle->tPhysicsObj.tRigidDynCubeObj.tModelObj.ptMagicObjContainer;
  if ( result )
    return (struct Vehicle_s *)((int (__cdecl *)(struct Vehicle_s *))QTask_aatQTaskFinalEvent[1][result->tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.eQTaskType].pfHandler)(result);
  return result;
}

// source: h/2/vehicle.c:531  [anchor-caller]
void __cdecl Vehicle_Create(struct Vehicle_s *ptVehicle)
{
  struct QTask_s *v1; // eax

  PhysicsObj_Create(&ptVehicle->tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask);
  v1 = QTask_NewFn(nullptr, MagicObjContainer_eQTaskType, nullptr);
  v1[1].ptNext = &ptVehicle->tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask;
  ptVehicle->tPhysicsObj.tRigidDynCubeObj.tModelObj.ptMagicObjContainer = v1;
  ModelObj_CreateAttachObjects(
    &ptVehicle->tPhysicsObj.tRigidDynCubeObj.tModelObj,
    v1,
    &ptVehicle->tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask,
    false,
    true);
  ptVehicle->vRealDeltaAlpha = 0.0;
  ptVehicle->vRealDeltaBeta = 0.0;
  ptVehicle->vRealDeltaGamma = 0.0;
  ptVehicle->vRealThrust = 0.0;
  ptVehicle->vIdealDeltaAlpha = 0.0;
  ptVehicle->vIdealDeltaBeta = 0.0;
  ptVehicle->vIdealDeltaGamma = 0.0;
  ptVehicle->vIdealThrust = 0.0;
  ptVehicle->isBreak = 0;
}

// source: h/2/vehicle.c:560  [anchor-mhash]
void __cdecl Vehicle_SaveKeyframeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QReference_s **v2; // eax
  struct QReference_s **v3; // esi

  v2 = *(struct QReference_s ***)pxContext;
  v3 = *(struct QReference_s ***)pxContext;
  *v3 = ptQTask[8].tQTaskRefList.ptMiddle;
  v3[1] = ptQTask[8].tQTaskRefList.ptTail;
  v3[2] = (struct QReference_s *)ptQTask[8].ptParent;
  qmemcpy(v2 + 4, &ptQTask[1], 0x18u);
  qmemcpy(*((void **)pxContext + 2), &ptQTask[1], 0x18u);
  qmemcpy(v2 + 10, &ptQTask[3].ptPrev, 0x28u);
  v2[20] = ptQTask[47].tQTaskRefList.ptMiddle;
  v2[21] = ptQTask[47].tQTaskRefList.ptTail;
  v2[22] = (struct QReference_s *)ptQTask[47].ptParent;
  v2[23] = *(struct QReference_s **)&ptQTask[47].eQTaskType;
  v2[24] = (struct QReference_s *)ptQTask[48].ptNext;
  v2[25] = (struct QReference_s *)ptQTask[48].ptPrev;
  v2[26] = (struct QReference_s *)ptQTask[48].tQTaskChildren.ptHead;
  v2[27] = (struct QReference_s *)ptQTask[48].tQTaskChildren.ptMiddle;
}

// source: h/2/vehicle.c:606  [anchor-mhash]
void *__cdecl Vehicle_RestoreKeyframeHandler(
        struct QTask_s *ptQTask,
        void *pxContext)
{
  int v2; // eax
  void *result; // eax

  v2 = *(_DWORD *)pxContext;
  ptQTask[8].tQTaskRefList.ptMiddle = *(struct QReference_s **)v2;
  ptQTask[8].tQTaskRefList.ptTail = *(struct QReference_s **)(v2 + 4);
  ptQTask[8].ptParent = *(struct QTask_s **)(v2 + 8);
  qmemcpy(&ptQTask[3].ptPrev, (void *)(v2 + 40), sizeof(struct QTask_s));
  ptQTask[47].tQTaskRefList.ptMiddle = *(struct QReference_s **)(v2 + 80);
  ptQTask[47].tQTaskRefList.ptTail = *(struct QReference_s **)(v2 + 84);
  ptQTask[47].ptParent = *(struct QTask_s **)(v2 + 88);
  *(_DWORD *)&ptQTask[47].eQTaskType = *(_DWORD *)(v2 + 92);
  ptQTask[48].ptNext = *(struct QTask_s **)(v2 + 96);
  ptQTask[48].ptPrev = *(struct QTask_s **)(v2 + 100);
  ptQTask[48].tQTaskChildren.ptHead = *(struct QTask_s **)(v2 + 104);
  result = *(void **)(v2 + 108);
  ptQTask[48].tQTaskChildren.ptMiddle = (struct QTask_s *)result;
  return result;
}

// source: h/2/vehicle.c:648  [anchor-hash]
void __cdecl Vehicle_CreateAttachObjects(struct Vehicle_s *ptVehicle)
{
  struct QTask_s *v1; // eax

  v1 = QTask_NewFn(nullptr, MagicObjContainer_eQTaskType, nullptr);
  v1[1].ptNext = &ptVehicle->tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask;
  ptVehicle->tPhysicsObj.tRigidDynCubeObj.tModelObj.ptMagicObjContainer = v1;
  ModelObj_CreateAttachObjects(
    &ptVehicle->tPhysicsObj.tRigidDynCubeObj.tModelObj,
    v1,
    &ptVehicle->tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask,
    false,
    true);
}

// source: h/2/vehicle.c:666  [anchor-hash]
void __cdecl Vehicle_DeleteAttachObjects(struct Vehicle_s *ptVehicle)
{
  if ( ptVehicle->tPhysicsObj.tRigidDynCubeObj.tModelObj.ptMagicObjContainer )
  {
    QTask_Delete(ptVehicle->tPhysicsObj.tRigidDynCubeObj.tModelObj.ptMagicObjContainer);
    ptVehicle->tPhysicsObj.tRigidDynCubeObj.tModelObj.ptMagicObjContainer = nullptr;
  }
}

// source: h/2/vehicle.c:684  [anchor-mhash]
void __cdecl Vehicle_AddCollPointFriction(
        struct Vehicle_s *ptVehicle,
        int iCollPoint,
        float vGamma,
        float vGravity,
        float vScale)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vNormalForce; };
    struct { float vNormalForcea; };
    struct { char igi2_o2[4]; float vSpeedFrictionPlane; };
    struct { char igi2_o3[4]; float vSpeedFrictionPlanea; };
    struct { char igi2_o4[8]; float tFrictionForce; };
    struct { char igi2_o5[8]; float tFrictionForcea; };
    struct { char igi2_o6[8]; float tFrictionForceb; };
    struct { char igi2_o7[8]; float tFrictionForcec; };
    struct { char igi2_o8[12]; float tFrictionForce_4; };
    struct { char igi2_o9[12]; float tFrictionForce_4a; };
    struct { char igi2_o10[12]; float tFrictionForce_4b; };
    struct { char igi2_o11[12]; float tFrictionForce_4c; };
    struct { char igi2_o12[20]; struct real32x9_t tGamma; };
    struct { char igi2_o13[60]; struct real32x3_t tPointVelocity; };
    char igi2_extent[72];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v5; // eax
  double v6; // st7
  double v7; // st7
  float vY; // esi
  double v9; // st6
  long double v10; // st3
  long double vZ; // st6
  double v12; // st6
  double v13; // st5
  long double v14; // st3
  long double v15; // st6
  double v16; // st6
  double v17; // st7
  long double v18; // st6
  double v19; // st7
  float v20; // ecx
  int nForces; // eax
  struct PointForce_s *v22; // edi
  double v23; // st7

  v5 = iCollPoint;
  if ( ptVehicle->tPhysicsObj.atCollPoint[v5].isContact )
  {
    v6 = vGravity * ptVehicle->tPhysicsObj.atCollPoint[v5].tNormal.vZ;
    if ( v6 < 0.0 )
      v6 = -v6;
    igi2_frame.vNormalForce = v6;
    if ( igi2_frame.vNormalForce != 0.0 )
    {
      v7 = igi2_frame.vNormalForce;
      igi2_frame.tPointVelocity.vX = ptVehicle->tPhysicsObj.tPhysics.tCMVel.vX;
      vY = ptVehicle->tPhysicsObj.tPhysics.tCMVel.vY;
      igi2_frame.tPointVelocity.vZ = ptVehicle->tPhysicsObj.tPhysics.tCMVel.vZ;
      v9 = igi2_frame.tPointVelocity.vZ * ptVehicle->tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vX;
      igi2_frame.tPointVelocity.vY = vY;
      igi2_frame.tGamma.tX.vX = v9
                   + vY * ptVehicle->tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vX
                   + igi2_frame.tPointVelocity.vX * ptVehicle->tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vX;
      igi2_frame.tFrictionForce = igi2_frame.tGamma.tX.vX;
      igi2_frame.tGamma.tX.vY = igi2_frame.tPointVelocity.vZ * ptVehicle->tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vY
                   + vY * ptVehicle->tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vY
                   + igi2_frame.tPointVelocity.vX * ptVehicle->tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vY;
      igi2_frame.tFrictionForce_4 = igi2_frame.tGamma.tX.vY;
      igi2_frame.tGamma.tX.vZ = igi2_frame.tPointVelocity.vZ * ptVehicle->tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vZ
                   + vY * ptVehicle->tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vZ
                   + igi2_frame.tPointVelocity.vX * ptVehicle->tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vZ;
      if ( igi2_frame.tGamma.tX.vX == 0.0 && igi2_frame.tGamma.tX.vY == 0.0 && igi2_frame.tGamma.tX.vZ == 0.0 )
      {
        vZ = igi2_frame.tGamma.tX.vZ;
      }
      else
      {
        v10 = sqrt(igi2_frame.tGamma.tX.vX * igi2_frame.tGamma.tX.vX + igi2_frame.tGamma.tX.vY * igi2_frame.tGamma.tX.vY + igi2_frame.tGamma.tX.vZ * igi2_frame.tGamma.tX.vZ);
        igi2_frame.tFrictionForce = igi2_frame.tGamma.tX.vX * (1.0 / v10);
        igi2_frame.tFrictionForce_4 = igi2_frame.tGamma.tX.vY * (1.0 / v10);
        vZ = 1.0 / v10 * igi2_frame.tGamma.tX.vZ;
      }
      igi2_frame.tPointVelocity.vX = igi2_frame.tFrictionForce_4 * ptVehicle->tPhysicsObj.atCollPoint[v5].tNormal.vZ
                        - vZ * ptVehicle->tPhysicsObj.atCollPoint[v5].tNormal.vY;
      igi2_frame.tPointVelocity.vY = -(igi2_frame.tFrictionForce * ptVehicle->tPhysicsObj.atCollPoint[v5].tNormal.vZ
                          - vZ * ptVehicle->tPhysicsObj.atCollPoint[v5].tNormal.vX);
      v12 = igi2_frame.tFrictionForce;
      igi2_frame.tFrictionForcea = igi2_frame.tPointVelocity.vX;
      v13 = igi2_frame.tFrictionForce_4;
      igi2_frame.tFrictionForce_4a = igi2_frame.tPointVelocity.vY;
      igi2_frame.tPointVelocity.vZ = v12 * ptVehicle->tPhysicsObj.atCollPoint[v5].tNormal.vY
                        - v13 * ptVehicle->tPhysicsObj.atCollPoint[v5].tNormal.vX;
      if ( igi2_frame.tPointVelocity.vX == 0.0 && igi2_frame.tPointVelocity.vY == 0.0 && igi2_frame.tPointVelocity.vZ == 0.0 )
      {
        v15 = igi2_frame.tPointVelocity.vZ;
      }
      else
      {
        v14 = sqrt(
                igi2_frame.tPointVelocity.vY * igi2_frame.tPointVelocity.vY
              + igi2_frame.tPointVelocity.vZ * igi2_frame.tPointVelocity.vZ
              + igi2_frame.tPointVelocity.vX * igi2_frame.tPointVelocity.vX);
        igi2_frame.tFrictionForcea = igi2_frame.tPointVelocity.vX * (1.0 / v14);
        igi2_frame.tFrictionForce_4a = igi2_frame.tPointVelocity.vY * (1.0 / v14);
        v15 = 1.0 / v14 * igi2_frame.tPointVelocity.vZ;
      }
      igi2_frame.tPointVelocity.vX = igi2_frame.tFrictionForce_4a * ptVehicle->tPhysicsObj.atCollPoint[v5].tNormal.vZ
                        - v15 * ptVehicle->tPhysicsObj.atCollPoint[v5].tNormal.vY;
      igi2_frame.tPointVelocity.vY = -(igi2_frame.tFrictionForcea * ptVehicle->tPhysicsObj.atCollPoint[v5].tNormal.vZ
                          - v15 * ptVehicle->tPhysicsObj.atCollPoint[v5].tNormal.vX);
      igi2_frame.tPointVelocity.vZ = igi2_frame.tFrictionForcea * ptVehicle->tPhysicsObj.atCollPoint[v5].tNormal.vY
                        - igi2_frame.tFrictionForce_4a * ptVehicle->tPhysicsObj.atCollPoint[v5].tNormal.vX;
      v16 = igi2_frame.tPointVelocity.vZ * igi2_frame.tGamma.tX.vZ + igi2_frame.tPointVelocity.vY * igi2_frame.tGamma.tX.vY + igi2_frame.tPointVelocity.vX * igi2_frame.tGamma.tX.vX;
      igi2_frame.vSpeedFrictionPlane = v16;
      if ( v16 < 0.0 )
        v16 = -v16;
      if ( igi2_frame.vNormalForce > v16 )
      {
        v7 = igi2_frame.vSpeedFrictionPlane;
        if ( igi2_frame.vSpeedFrictionPlane < 0.0 )
          v7 = -v7;
      }
      igi2_frame.tFrictionForceb = igi2_frame.tPointVelocity.vX * v7;
      igi2_frame.tFrictionForce_4b = igi2_frame.tPointVelocity.vY * v7;
      v17 = v7 * igi2_frame.tPointVelocity.vZ;
      v18 = sin(vGamma);
      igi2_frame.vNormalForcea = cos(vGamma);
      igi2_frame.tGamma.tX.vY = -v18;
      igi2_frame.tPointVelocity.vX = igi2_frame.vNormalForcea * igi2_frame.tFrictionForceb + igi2_frame.tGamma.tX.vY * igi2_frame.tFrictionForce_4b + v17 * 0.0;
      igi2_frame.tPointVelocity.vY = v18 * igi2_frame.tFrictionForceb + igi2_frame.vNormalForcea * igi2_frame.tFrictionForce_4b + v17 * 0.0;
      igi2_frame.tPointVelocity.vZ = (igi2_frame.tFrictionForceb + igi2_frame.tFrictionForce_4b) * 0.0 + v17;
      igi2_frame.tFrictionForcec = igi2_frame.tPointVelocity.vX * ptVehicle->tPhysicsObj.atCollPoint[v5].vFrictionX;
      igi2_frame.tFrictionForce_4c = igi2_frame.tPointVelocity.vY * ptVehicle->tPhysicsObj.atCollPoint[v5].vFrictionY;
      igi2_frame.vSpeedFrictionPlanea = igi2_frame.tPointVelocity.vZ * 0.0;
      igi2_frame.tPointVelocity.vX = igi2_frame.vNormalForcea * igi2_frame.tFrictionForcec + v18 * igi2_frame.tFrictionForce_4c + igi2_frame.vSpeedFrictionPlanea;
      igi2_frame.tPointVelocity.vY = igi2_frame.vNormalForcea * igi2_frame.tFrictionForce_4c + igi2_frame.tGamma.tX.vY * igi2_frame.tFrictionForcec + igi2_frame.vSpeedFrictionPlanea;
      igi2_frame.tPointVelocity.vZ = (igi2_frame.tFrictionForcec + igi2_frame.tFrictionForce_4c) * 0.0 + igi2_frame.tPointVelocity.vZ;
      igi2_frame.tGamma.tX = igi2_frame.tPointVelocity;
      igi2_frame.tGamma.tY.vX = ptVehicle->tPhysicsObj.atCollPoint[v5].tPos.vX;
      v19 = igi2_frame.tPointVelocity.vX * vScale * ptVehicle->tPhysicsObj.tPhysics.vM;
      v20 = ptVehicle->tPhysicsObj.atCollPoint[v5].tPos.vZ;
      igi2_frame.tGamma.tY.vY = ptVehicle->tPhysicsObj.atCollPoint[v5].tPos.vY;
      nForces = ptVehicle->tPhysicsObj.tPhysics.nForces;
      igi2_frame.tGamma.tX.vX = v19;
      igi2_frame.tGamma.tY.vZ = v20;
      v22 = &ptVehicle->tPhysicsObj.tPhysics.ptForces[nForces];
      v23 = igi2_frame.tPointVelocity.vY * vScale * ptVehicle->tPhysicsObj.tPhysics.vM;
      igi2_frame.tGamma.tX.vZ = 0.0;
      igi2_frame.tGamma.tX.vY = v23;
      igi2_frame.tGamma.tY.vZ = 0.0;
      qmemcpy(v22, &igi2_frame.tGamma, sizeof(struct PointForce_s));
      ++ptVehicle->tPhysicsObj.tPhysics.nForces;
    }
  }
}

// source: h/2/vehicle.c:781  [size]
__int16 __cdecl Vehicle_GetHitZoneDestroyedQTaskEvent()
{
  return Vehicle_eHitZoneDestroyedQTaskEvent;
}

// source: h/2/vehicle.c:796  [size]
__int16 __cdecl Vehicle_GetTraceHitZoneQTaskEvent()
{
  return Vehicle_eTraceHitZoneQTaskEvent;
}

// source: h/2/vehicle.c:811  [size]
struct QTaskList_s *__cdecl Vehicle_SetQTaskList(struct QTaskList_s *ptQTaskList)
{
  Vehicle_ptQTaskList = ptQTaskList;
  return ptQTaskList;
}
