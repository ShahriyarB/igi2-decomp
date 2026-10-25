/* h/1/modelobjparameters.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/1/modelobjparameters.c:37  [anchor-mhash]
void __cdecl ModelObjParameters_DeSerializeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct ModelObj_s *v2; // edi
  int eQTaskType; // edx
  void (__cdecl *pfHandler)(struct ModelObj_s *, struct QTask_s **); // eax
  struct World_s *v5; // eax
  int v6; // ecx
  void (__cdecl *v7)(struct ModelObj_s *, struct DynCubeObjRegisterObjContext_s *); // eax
  struct DynCubeObjRegisterObjContext_s tRegisterContext; // [esp+4h] [ebp-Ch] BYREF

  v2 = (struct ModelObj_s *)ptQTask;
  if ( ptQTask[2].tQTaskChildren.ptHead )
  {
    eQTaskType = ptQTask->eQTaskType;
    ptQTask = (struct QTask_s *)World_ptActiveWorld;
    pfHandler = (void (__cdecl *)(struct ModelObj_s *, struct QTask_s **))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRemoveQTaskEvent][eQTaskType].pfHandler;
    if ( pfHandler )
      pfHandler(v2, &ptQTask);
  }
  Serialize_DeSerializeHandler(&v2->tDynCubeObj.tQObj.tQTask, pxContext);
  if ( v2->tDynCubeObj.ptDynCubeObjTreeItem )
  {
    v5 = World_ptActiveWorld;
    v6 = v2->tDynCubeObj.tQObj.tQTask.eQTaskType + 511 * DynCubeObj_eDynCubeObjRegisterQTaskEvent;
    v2->tDynCubeObj.ptDynCubeObjTreeItem = nullptr;
    tRegisterContext.ptWorld = v5;
    v7 = (void (__cdecl *)(struct ModelObj_s *, struct DynCubeObjRegisterObjContext_s *))QTask_aatQTaskFinalEvent[0][v6].pfHandler;
    tRegisterContext.eDynCubeObjRegisterMethod = DYNCUBEOBJREGISTERMETHOD_RADIUS;
    tRegisterContext.eDynCubeTreeCategory = 2;
    if ( v7 )
      v7(v2, &tRegisterContext);
    ModelObj_UpdateAttachments(v2);
  }
}

// source: h/1/modelobjparameters.c:73  [anchor-mhash]
void __cdecl SectorInteriorObject_DeSerializeDoneHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct ModelObj_s *v2; // edi
  int eQTaskType; // edx
  void (__cdecl *pfHandler)(struct ModelObj_s *, struct QTask_s **); // eax
  void (__cdecl *v5)(struct ModelObj_s *, struct DynCubeObjRegisterObjContext_s *); // eax
  struct DynCubeObjRegisterObjContext_s tRegisterContext; // [esp+4h] [ebp-Ch] BYREF

  v2 = (struct ModelObj_s *)ptQTask;
  if ( ptQTask[2].tQTaskChildren.ptHead )
  {
    eQTaskType = ptQTask->eQTaskType;
    ptQTask = (struct QTask_s *)World_ptActiveWorld;
    pfHandler = (void (__cdecl *)(struct ModelObj_s *, struct QTask_s **))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRemoveQTaskEvent][eQTaskType].pfHandler;
    if ( pfHandler )
      pfHandler(v2, &ptQTask);
  }
  v5 = (void (__cdecl *)(struct ModelObj_s *, struct DynCubeObjRegisterObjContext_s *))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRegisterQTaskEvent][v2->tDynCubeObj.tQObj.tQTask.eQTaskType].pfHandler;
  tRegisterContext.eDynCubeObjRegisterMethod = DYNCUBEOBJREGISTERMETHOD_RADIUS;
  tRegisterContext.eDynCubeTreeCategory = 2;
  tRegisterContext.ptWorld = World_ptActiveWorld;
  if ( v5 )
    v5(v2, &tRegisterContext);
  ModelObj_UpdateAttachments(v2);
}

// source: h/1/modelobjparameters.c:108  [size]
struct ParameterList_s *__cdecl ModelObj_GetSerializeParameterList()
{
  return ModelObjParameters_ptSerializeParameterList;
}

// source: h/1/modelobjparameters.c:123  [size]
struct ParameterList_s *__cdecl RigidDynCubeObj_GetSerializeParameterList()
{
  return ModelObjParameters_ptSerializeParameterList;
}

// source: h/1/modelobjparameters.c:136  [size]
struct ParameterList_s *__cdecl BoneDynCubeObj_GetSerializeParameterList()
{
  return ModelObjParameters_ptSerializeParameterList;
}

// source: h/1/modelobjparameters.c:149  [size]
struct ParameterList_s *__cdecl SectorInteriorObject_GetSerializeParameterList()
{
  return ModelObjParameters_ptSerializeParameterList;
}

// source: h/1/modelobjparameters.c:162  [size]
struct ParameterList_s *__cdecl PhysicsObj_GetSerializeParameterList()
{
  return ModelObjParameters_ptSerializeParameterList;
}

// source: h/1/modelobjparameters.c:175  [size]
struct ParameterList_s *__cdecl Vehicle_GetSerializeParameterList()
{
  return ModelObjParameters_ptSerializeParameterList;
}

// source: h/1/modelobjparameters.c:188  [anchor-hash]
void __cdecl ModelObjParameters_Open()
{
  struct ParameterList_s *v0; // eax
  int v1; // edx

  QTask_LinkQTaskEventHandlerFn(
    ModelObj_eQTaskType,
    Serialize_eDeSerializeQTaskEvent,
    ModelObjParameters_DeSerializeHandler);
  QTask_LinkQTaskEventHandlerFn(
    SectorInteriorObject_eQTaskType,
    Serialize_eDeSerializeDoneQTaskEvent,
    SectorInteriorObject_DeSerializeDoneHandler);
  v0 = (struct ParameterList_s *)Mem_AllocFn(112, 4);
  v1 = Level_eParameterTypeReal64x3;
  v0->ptParameterListItem = (struct ParameterListItem_s *)&v0[1];
  v0->nParameters = 0;
  v0->nMaxParameters = 5;
  ModelObjParameters_ptSerializeParameterList = v0;
  ParameterList_AddParameter(v0, 0x28u, v1, "tPos", 7u, nullptr);
  ParameterList_AddParameter(
    ModelObjParameters_ptSerializeParameterList,
    0x7Cu,
    Level_eParameterTypeReal32x9,
    "tOrientation",
    7u,
    nullptr);
  ParameterList_AddParameter(
    ModelObjParameters_ptSerializeParameterList,
    0xA4u,
    Level_eParameterTypeReal32x9,
    "tRelativeOrientation",
    7u,
    nullptr);
  ParameterList_AddParameter(
    ModelObjParameters_ptSerializeParameterList,
    0xCCu,
    Level_eParameterTypeReal32x3,
    "tRelativePos",
    7u,
    nullptr);
  ParameterList_AddParameter(
    ModelObjParameters_ptSerializeParameterList,
    0x58u,
    Level_eParameterTypeInt32,
    "isRegisteredInWorldHack",
    7u,
    nullptr);
}

// source: h/1/modelobjparameters.c:209  [anchor-hash]
void __cdecl ModelObjParameters_Close()
{
  int v0; // esi

  if ( ModelObjParameters_ptSerializeParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&ModelObjParameters_ptSerializeParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
}
