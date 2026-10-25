/* e/3/magicobjcontainer.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: e/3/magicobjcontainer.c:52  [size~]
void __cdecl MagicObjContainer_RunHandler(struct QTask_s *ptQTask, int ltcg_eax, int ltcg_arg1)
{
  unsigned int *p_nAllocated; // esi
  struct QObjectVector_s *v5; // ebx
  _DWORD *v6; // eax

  if ( ShadowVolume_isEnabled && ptQTask->ptNext )
  {
    p_nAllocated = &ShadowVolume_ptProtectRequestVector->nAllocated;
    v5 = ShadowVolume_ptProtectRequestVector;
    if ( ShadowVolume_ptProtectRequestVector->nAllocated == ShadowVolume_ptProtectRequestVector->nSize )
      QObjectVector_Realloc(ShadowVolume_ptProtectRequestVector, ShadowVolume_ptProtectRequestVector->nReallocSize);
    v6 = v5->papxElement[(*p_nAllocated)++];
    *v6 = *(_DWORD *)(ltcg_eax + 116);
    v6[1] = ptQTask;
    v6[2] = ltcg_eax + 40;
    v6[3] = ltcg_eax + 124;
    v6[4] = ltcg_arg1;
  }
}

long double __cdecl sub_5C5840(struct real64x3_t *a1, struct World_s *ptWorld, float a3)
{
  #pragma pack(push, 1)
  union
  {
    struct { float bQTaskGroup_4; };
    struct { char igi2_o1[4]; float v5; };
    struct { char igi2_o2[12]; struct real64x3_t ptEnd; };
    struct { char igi2_o3[36]; struct QIntersection_s ptIntersection; };
    char igi2_extent[156];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  long double result; // st7

  if ( a3 >= 12288.0 )
  {
    if ( a3 > 81920.0 )
      a3 = 81920.0;
  }
  else
  {
    a3 = 12288.0;
  }
  igi2_frame.bQTaskGroup_4 = SkyDome_ptDirlight->tDir.vY;
  igi2_frame.v5 = -(SkyDome_ptDirlight->tDir.vZ * a3);
  igi2_frame.ptEnd.vX = a1->vX - SkyDome_ptDirlight->tDir.vX * a3;
  igi2_frame.ptEnd.vY = a1->vY - igi2_frame.bQTaskGroup_4 * a3;
  igi2_frame.ptEnd.vZ = igi2_frame.v5 + a1->vZ;
  World_TraceLines(ptWorld, &igi2_frame.ptIntersection, a1, &igi2_frame.ptEnd, 1, 512, nullptr, 0x98000000);
  if ( !igi2_frame.ptIntersection.isHit )
    return a3;
  result = sqrt(
             (a1->vX - igi2_frame.ptIntersection.tPos.vX) * (a1->vX - igi2_frame.ptIntersection.tPos.vX)
           + (a1->vY - igi2_frame.ptIntersection.tPos.vY) * (a1->vY - igi2_frame.ptIntersection.tPos.vY)
           + (a1->vZ - igi2_frame.ptIntersection.tPos.vZ) * (a1->vZ - igi2_frame.ptIntersection.tPos.vZ));
  if ( result < 12288.0 )
    return 12288.0;
  return result;
}

void sub_5C5990()
{
  unsigned __int16 v0; // ax
  unsigned __int16 v1; // si
  unsigned __int16 v2; // di
  __int16 v3; // bx
  struct QObjectVector_s *v4; // esi

  ShadowVolume_eQTaskType = QTask_NewQTaskType("ShadowVolume", 264, DynCubeObj_eQTaskType, 0, 0);
  v0 = QTask_NewQTaskType("ShadowLayer", 112, DynCubeObj_eQTaskType, 0, 0);
  v1 = ShadowVolume_eQTaskType;
  v2 = v0;
  ShadowVolume_eShadowLayerQTaskType = v0;
  ShadowVolume_tShadowLayerDynCubeObj.tQObj.tQTask.eQTaskType = v0;
  ShadowVolume_tShadowLayerDynCubeObj.iRenderGroup = RenderGroup_ShadowPoly;
  QTask_LinkQTaskEventHandlerFn(ShadowVolume_eQTaskType, 0, (void (__cdecl *)(struct QTask_s *, void *))sub_5C5100);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v1,
    Attach_eUpdateAttachmentEvent,
    (void (__cdecl *)(struct QTask_s *))sub_5C5200);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, (void (__cdecl *)(struct QTask_s *))sub_5C5460);
  QTask_LinkQTaskEventHandlerFn(v1, 5, (void (__cdecl *)(struct QTask_s *, void *))sub_5C4E70);
  v3 = DynCubeObj_eDynCubeObjRegisterQTaskEvent;
  QTask_LinkQTaskEventHandlerFn(
    v1,
    DynCubeObj_eDynCubeObjRegisterQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))sub_5C5470);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    DynCubeObj_eDynCubeObjRemoveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))sub_5C5490);
  QTask_LinkQTaskEventHandlerFn(v2, 5, (void (__cdecl *)(struct QTask_s *, void *))sub_5C4E10);
  QTask_LinkQTaskEventHandlerFn(v2, v3, nullptr);
  QTask_LinkQTaskEventHandlerFn(v2, DynCubeObj_eDynCubeObjRemoveQTaskEvent, nullptr);
  ShadowVolume_eGetShadowInfoEvent = QTask_NewQTaskEventFn(0, "GetShadowInfoEvent");
  Display_RegisterCallback((void (__cdecl *)())sub_5C54A0, &Display_ptStartFrameCallback);
  Display_RegisterCallback((void (__cdecl *)())sub_5C54C0, &Display_ptEndFrameCallback);
  Direct3D_RegisterCallback(sub_5C54D0, &Direct3D_ptSetModeCallback);
  Direct3D_RegisterCallback(sub_5C5560, &Direct3D_ptUnsetModeCallback);
  Direct3D_RegisterCallback(sub_5C55A0, &Direct3D_ptDestroyCallback);
  Direct3D_RegisterCallback(sub_5C55E0, &Direct3D_ptRestoreCallback);
  Symbol_Register(
    "TASKTYPE_SHADOWVOLUME",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)ShadowVolume_eQTaskType,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  v4 = (struct QObjectVector_s *)Mem_AllocFn(52, 4);
  v4->isStrictOrder = false;
  v4->nSize = 0;
  v4->nAllocated = 0;
  v4->nReallocSize = 100;
  v4->papxElement = nullptr;
  v4->nElementSize = 24;
  v4->tMemPool.nBlocks = 0;
  v4->tMemPool.nAllocatedBlocks = 0;
  v4->tMemPool.nAlignment = 4;
  v4->tMemPool.nBlockSize = 24;
  v4->tMemPool.nReAllocBlocks = 100;
  v4->tMemPool.tMemPoolFreeList.ptHead = nullptr;
  v4->tMemPool.tMemPoolSegmentList.ptHead = nullptr;
  MemPool_ReAlloc(&v4->tMemPool, 0x64u);
  QObjectVector_Realloc(v4, 0x64u);
  ShadowVolume_ptProtectRequestVector = v4;
}

// source: e/3/magicobjcontainer.c:66  [size~]
void __cdecl MagicObjContainer_MagicObjEnterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptHead; // ecx
  int v3; // edx
  struct QTask_s *v4; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v6; // edx

  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v3 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v4 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v4 = nullptr;
      QTask_atProtectedQTaskStack[v3].ptQTask = v4;
      pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][ptHead->eQTaskType].pfHandler;
      v6 = v3 + 1;
      QTask_nProtectedQTaskStackOffset = v6;
      if ( pfHandler )
      {
        pfHandler(ptHead);
        v6 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v6];
      v3 = v6 - 1;
      QTask_nProtectedQTaskStackOffset = v3;
    }
    while ( ptHead );
  }
}

void __cdecl sub_5C5C30(struct QTask_s *a1, void *a2)
{
  struct QTask_s *ptHead; // eax
  int v3; // edx
  struct QTask_s *v4; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // ecx
  int v6; // edx

  ptHead = a1->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v3 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v4 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v4 = nullptr;
      QTask_atProtectedQTaskStack[v3].ptQTask = v4;
      pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[MagicObj_eMagicObjEnterEvent][ptHead->eQTaskType].pfHandler;
      v6 = v3 + 1;
      QTask_nProtectedQTaskStackOffset = v6;
      if ( pfHandler )
      {
        pfHandler(ptHead, a2);
        v6 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v6];
      v3 = v6 - 1;
      QTask_nProtectedQTaskStackOffset = v3;
    }
    while ( ptHead );
  }
}

void __cdecl sub_5C5CB0(struct QTask_s *a1)
{
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Attach_eAttachEvent][a1[1].ptNext->eQTaskType].pfHandler)(a1[1].ptNext);
}

// source: e/3/magicobjcontainer.c:110  [size]
void __cdecl MagicObjContainer_GetShadowInfoHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ((void (__cdecl *)(struct QTask_s *, ...))QTask_aatQTaskFinalEvent[ShadowVolume_eGetShadowInfoEvent][ptQTask[1].ptNext->eQTaskType].pfHandler)(ptQTask[1].ptNext, pxContext);
}

// source: e/3/magicobjcontainer.c:128  [anchor-hash]
void __cdecl MagicObjContainer_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("MagicObjContainer", 44, BaseQTaskType, 0, 0);
  MagicObjContainer_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerNoContextFn(
    v1,
    1,
    (void (__cdecl *)(struct QTask_s *))MagicObjContainer_MagicObjEnterHandler);
  QTask_LinkQTaskEventHandlerFn(v1, MagicObj_eMagicObjEnterEvent, sub_5C5C30);
  QTask_LinkQTaskEventHandlerFn(v1, Attach_eAttachEvent, (void (__cdecl *)(struct QTask_s *, void *))sub_5C5CB0);
  QTask_LinkQTaskEventHandlerFn(v1, ShadowVolume_eGetShadowInfoEvent, MagicObjContainer_GetShadowInfoHandler);
}

// source: e/3/magicobjcontainer.c:156  [size]
void __cdecl MagicObjContainer_Close()
{
  QTask_DeleteQTaskType(MagicObjContainer_eQTaskType);
}

// source: e/3/magicobjcontainer.c:170  [size]
unsigned __int16 __cdecl MagicObjContainer_GetQTaskType()
{
  return MagicObjContainer_eQTaskType;
}

// source: e/3/magicobjcontainer.c:184  [anchor-callee]
struct QTask_s *__cdecl MagicObjContainer_New(
        struct QTask_s *ptParentQTask,
        struct QTask_s *ptCreatorQTask)
{
  struct QTask_s *result; // eax

  result = QTask_NewFn(ptParentQTask, MagicObjContainer_eQTaskType, nullptr);
  result[1].ptNext = ptCreatorQTask;
  return result;
}
