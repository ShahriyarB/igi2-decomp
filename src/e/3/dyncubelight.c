/* e/3/dyncubelight.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: e/3/dyncubelight.c:38  [anchor-mhash]
void __cdecl DynCubeLight_PointlightEnterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  Lightsource_NewPointlight(
    (struct real64x3_t *)&ptQTask[1],
    (struct real32x3_t *)&ptQTask[2].ptParent,
    *(float *)&ptQTask[3].ptPrev);
}

// source: e/3/dyncubelight.c:60  [size]
void __cdecl DynCubeLight_PointlightLeaveHandler(struct QTask_s *ptQTask, void *pxContext)
{
  if ( Lightsource_nIdealLightDataStackPos == Lightsource_nLightDataStackPos )
    --Lightsource_nLightDataStackPos;
  --Lightsource_nIdealLightDataStackPos;
}

// source: e/3/dyncubelight.c:76  [anchor-mhash]
void __cdecl DynCubeLight_PointlightGetCameraTargetInfoHandler(struct QTask_s *ptQTask, void *pxContext)
{
  char *v2; // eax

  qmemcpy(pxContext, &ptQTask[1], 0x18u);
  *((_DWORD *)pxContext + 9) = 1065353216;
  *((_DWORD *)pxContext + 13) = 1065353216;
  *((_DWORD *)pxContext + 17) = 1065353216;
  *((_DWORD *)pxContext + 6) = 0;
  *((_DWORD *)pxContext + 7) = 0;
  *((_DWORD *)pxContext + 8) = 0;
  *((_DWORD *)pxContext + 10) = 0;
  *((_DWORD *)pxContext + 11) = 0;
  *((_DWORD *)pxContext + 12) = 0;
  *((_DWORD *)pxContext + 14) = 0;
  *((_DWORD *)pxContext + 15) = 0;
  *((_DWORD *)pxContext + 16) = 0;
  *((_DWORD *)pxContext + 18) = 0;
  *((_DWORD *)pxContext + 19) = ptQTask[3].ptPrev;
  v2 = *((char **)pxContext + 20);
  if ( v2 )
    strcpy(v2, "Pointlight");
}

// source: e/3/dyncubelight.c:114  [anchor-mhash]
void __cdecl DynCubeLight_SpotlightEnterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  Lightsource_NewSpotlight(
    (struct real64x3_t *)&ptQTask[1],
    (struct real32x3_t *)&ptQTask[2].ptParent,
    *(float *)&ptQTask[3].ptPrev,
    (struct real32x3_t *)&ptQTask[3].tQTaskChildren,
    *(float *)&ptQTask[3].tQTaskRefList.ptHead);
}

// source: e/3/dyncubelight.c:139  [size]
void __cdecl DynCubeLight_SpotlightLeaveHandler(struct QTask_s *ptQTask, void *pxContext)
{
  if ( Lightsource_nIdealLightDataStackPos == Lightsource_nLightDataStackPos )
    --Lightsource_nLightDataStackPos;
  --Lightsource_nIdealLightDataStackPos;
}

// source: e/3/dyncubelight.c:153  [anchor-mhash]
void __cdecl DynCubeLight_SpotlightGetCameraTargetInfoHandler(struct QTask_s *ptQTask, void *pxContext)
{
  char *v2; // eax

  qmemcpy(pxContext, &ptQTask[1], 0x18u);
  *((_DWORD *)pxContext + 9) = 1065353216;
  *((_DWORD *)pxContext + 13) = 1065353216;
  *((_DWORD *)pxContext + 17) = 1065353216;
  *((_DWORD *)pxContext + 6) = 0;
  *((_DWORD *)pxContext + 7) = 0;
  *((_DWORD *)pxContext + 8) = 0;
  *((_DWORD *)pxContext + 10) = 0;
  *((_DWORD *)pxContext + 11) = 0;
  *((_DWORD *)pxContext + 12) = 0;
  *((_DWORD *)pxContext + 14) = 0;
  *((_DWORD *)pxContext + 15) = 0;
  *((_DWORD *)pxContext + 16) = 0;
  *((_DWORD *)pxContext + 18) = 0;
  *((_DWORD *)pxContext + 19) = ptQTask[3].ptPrev;
  v2 = *((char **)pxContext + 20);
  if ( v2 )
    strcpy(v2, "Spotlight");
}

// source: e/3/dyncubelight.c:198  [anchor-mhash]
struct PointlightDynCubeObj_s *__cdecl DynCubeLight_NewPointlight(
        struct World_s *ptWorld,
        struct real64x3_t *ptPos,
        struct real32x3_t *ptColor,
        float vRadius)
{
  struct QTask_s *v4; // ebx
  struct QObjectVector_s *v5; // eax
  unsigned int *p_nAllocated; // esi
  struct QObjectVector_s *v7; // edi
  struct QTask_s *v8; // ecx

  v4 = QTask_NewFn(nullptr, DynCubeLight_eQTaskTypePointlight, nullptr);
  memset(&v4[1], 0, 0x48u);
  v5 = DynCubeLight_ptPointlightCollection;
  v4[2].tQTaskRefList.ptTail = (struct QReference_s *)5;
  p_nAllocated = &v5->nAllocated;
  v7 = v5;
  if ( v5->nAllocated == v5->nSize )
    QObjectVector_Realloc(v5, v5->nReallocSize);
  v8 = (struct QTask_s *)v7->papxElement[(*p_nAllocated)++];
  v4[3].tQTaskChildren.ptHead = v8;
  v8->ptNext = v4;
  *(struct real32x3_t *)&v4[2].ptParent = *ptColor;
  *(float *)&v4[3].ptPrev = vRadius;
  World_RegisterDynCubeObjFirstTimeRadius(
    ptWorld,
    (struct DynCubeObj_s *)v4,
    ptPos,
    vRadius,
    WORLD_DYNCUBETREE_CATEGORY_MOBILE);
  return (struct PointlightDynCubeObj_s *)v4;
}

// source: e/3/dyncubelight.c:241  [size]
void __cdecl DynCubeLight_DeletePointlight(
        struct World_s *ptWorld,
        struct PointlightDynCubeObj_s *ptPointlightDynCubeObj)
{
  World_RemoveDynCubeObj(ptWorld, &ptPointlightDynCubeObj->tDynCubeObj);
  QObjectVector_RemoveElement(
    DynCubeLight_ptPointlightCollection,
    *(unsigned int *)((char *)ptPointlightDynCubeObj->pptObject + DynCubeLight_ptPointlightCollection->nElementSize - 4));
  QTask_Delete(&ptPointlightDynCubeObj->tDynCubeObj.tQObj.tQTask);
}

// source: e/3/dyncubelight.c:267  [size]
void __cdecl DynCubeLight_SetPointlightPosAndRadius(
        struct World_s *ptWorld,
        struct PointlightDynCubeObj_s *ptPointlightDynCubeObj,
        struct real64x3_t *ptPos,
        float vRadius)
{
  ptPointlightDynCubeObj->vRadius = vRadius;
  World_MoveDynCubeObjRadius(ptWorld, &ptPointlightDynCubeObj->tDynCubeObj, ptPos, vRadius);
}

// source: e/3/dyncubelight.c:294  [anchor-mhash]
struct SpotlightDynCubeObj_s *__cdecl DynCubeLight_NewSpotlight(
        struct World_s *ptWorld,
        struct real64x3_t *ptPos,
        struct real32x3_t *ptColor,
        float vRadius,
        struct real32x3_t *ptDir,
        float vAngle)
{
  struct QTask_s *v6; // ebx
  struct QObjectVector_s *v7; // eax
  unsigned int *p_nAllocated; // esi
  struct QObjectVector_s *v9; // edi
  struct QTask_s **v10; // ecx

  v6 = QTask_NewFn(nullptr, DynCubeLight_eQTaskTypeSpotlight, nullptr);
  memset(&v6[1], 0, 0x48u);
  v7 = DynCubeLight_ptSpotlightCollection;
  v6[2].tQTaskRefList.ptTail = (struct QReference_s *)5;
  p_nAllocated = &v7->nAllocated;
  v9 = v7;
  if ( v7->nAllocated == v7->nSize )
    QObjectVector_Realloc(v7, v7->nReallocSize);
  v10 = (struct QTask_s **)v9->papxElement[(*p_nAllocated)++];
  v6[3].tQTaskRefList.ptMiddle = (struct QReference_s *)v10;
  *v10 = v6;
  *(struct real32x3_t *)&v6[2].ptParent = *ptColor;
  *(float *)&v6[3].ptPrev = vRadius;
  v6[3].tQTaskChildren = (*(struct QTaskNodeList_s *)&*ptDir);
  *(float *)&v6[3].tQTaskRefList.ptHead = vAngle;
  World_RegisterDynCubeObjFirstTimeRadius(
    ptWorld,
    (struct DynCubeObj_s *)v6,
    ptPos,
    vRadius,
    WORLD_DYNCUBETREE_CATEGORY_MOBILE);
  return (struct SpotlightDynCubeObj_s *)v6;
}

// source: e/3/dyncubelight.c:342  [size]
void __cdecl DynCubeLight_DeleteSpotlight(
        struct World_s *ptWorld,
        struct SpotlightDynCubeObj_s *ptSpotlightDynCubeObj)
{
  World_RemoveDynCubeObj(ptWorld, &ptSpotlightDynCubeObj->tDynCubeObj);
  QObjectVector_RemoveElement(
    DynCubeLight_ptSpotlightCollection,
    *(unsigned int *)((char *)ptSpotlightDynCubeObj->pptObject + DynCubeLight_ptSpotlightCollection->nElementSize - 4));
  QTask_Delete(&ptSpotlightDynCubeObj->tDynCubeObj.tQObj.tQTask);
}

// source: e/3/dyncubelight.c:369  [size]
void __cdecl DynCubeLight_SetSpotlightPosAndRadius(
        struct World_s *ptWorld,
        struct SpotlightDynCubeObj_s *ptSpotlightDynCubeObj,
        struct real64x3_t *ptPos,
        float vRadius)
{
  ptSpotlightDynCubeObj->vRadius = vRadius;
  World_MoveDynCubeObjRadius(ptWorld, &ptSpotlightDynCubeObj->tDynCubeObj, ptPos, vRadius);
}

// source: e/3/dyncubelight.c:389  [anchor-hash]
void __cdecl DynCubeLight_Open()
{
  unsigned __int16 v0; // ax
  unsigned __int16 v1; // bx
  unsigned __int16 v2; // si
  struct QObjectVector_s *v3; // esi
  struct QObjectVector_s *v4; // esi

  DynCubeLight_eQTaskTypePointlight = QTask_NewQTaskType("PointlightDynCubeObj", 136, DynCubeObj_eQTaskType, 0, 0);
  v0 = QTask_NewQTaskType("SpotlightDynCubeObj", 152, DynCubeObj_eQTaskType, 0, 0);
  v1 = DynCubeLight_eQTaskTypePointlight;
  v2 = v0;
  DynCubeLight_eQTaskTypeSpotlight = v0;
  QTask_LinkQTaskEventHandlerFn(DynCubeLight_eQTaskTypePointlight, 5, DynCubeLight_PointlightEnterHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 6, (void (__cdecl *)(struct QTask_s *, void *))DynCubeLight_PointlightLeaveHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 8, DynCubeLight_PointlightGetCameraTargetInfoHandler);
  QTask_LinkQTaskEventHandlerFn(v2, 5, DynCubeLight_SpotlightEnterHandler);
  QTask_LinkQTaskEventHandlerFn(v2, 6, (void (__cdecl *)(struct QTask_s *, void *))DynCubeLight_SpotlightLeaveHandler);
  QTask_LinkQTaskEventHandlerFn(v2, 8, DynCubeLight_SpotlightGetCameraTargetInfoHandler);
  v3 = (struct QObjectVector_s *)Mem_AllocFn(52, 4);
  v3->isStrictOrder = false;
  v3->nSize = 0;
  v3->nAllocated = 0;
  v3->nReallocSize = 0;
  v3->papxElement = nullptr;
  v3->nElementSize = 8;
  v3->tMemPool.nBlocks = 0;
  v3->tMemPool.nAllocatedBlocks = 0;
  v3->tMemPool.nAlignment = 4;
  v3->tMemPool.nBlockSize = 8;
  v3->tMemPool.nReAllocBlocks = 0;
  v3->tMemPool.tMemPoolFreeList.ptHead = nullptr;
  v3->tMemPool.tMemPoolSegmentList.ptHead = nullptr;
  MemPool_ReAlloc(&v3->tMemPool, 0xAu);
  QObjectVector_Realloc(v3, 0xAu);
  DynCubeLight_ptPointlightCollection = v3;
  v4 = (struct QObjectVector_s *)Mem_AllocFn(52, 4);
  v4->isStrictOrder = false;
  v4->nSize = 0;
  v4->nAllocated = 0;
  v4->nReallocSize = 0;
  v4->papxElement = nullptr;
  v4->nElementSize = 8;
  v4->tMemPool.nBlocks = 0;
  v4->tMemPool.nAllocatedBlocks = 0;
  v4->tMemPool.nAlignment = 4;
  v4->tMemPool.nBlockSize = 8;
  v4->tMemPool.nReAllocBlocks = 0;
  v4->tMemPool.tMemPoolFreeList.ptHead = nullptr;
  v4->tMemPool.tMemPoolSegmentList.ptHead = nullptr;
  MemPool_ReAlloc(&v4->tMemPool, 0xAu);
  QObjectVector_Realloc(v4, 0xAu);
  DynCubeLight_ptSpotlightCollection = v4;
}

// source: e/3/dyncubelight.c:417  [anchor-hash]
void __cdecl DynCubeLight_Close()
{
  QObjectVector_Delete(DynCubeLight_ptPointlightCollection);
  QObjectVector_Delete(DynCubeLight_ptSpotlightCollection);
  QTask_DeleteQTaskType(DynCubeLight_eQTaskTypePointlight);
  DynCubeLight_eQTaskTypePointlight = 512;
  QTask_DeleteQTaskType(DynCubeLight_eQTaskTypeSpotlight);
  DynCubeLight_eQTaskTypeSpotlight = 512;
}

// source: e/3/dyncubelight.c:439  [size]
int __cdecl DynCubeLight_GetNumPointlights()
{
  return DynCubeLight_ptPointlightCollection->nAllocated;
}

// source: e/3/dyncubelight.c:452  [size]
int __cdecl DynCubeLight_GetNumSpotlights()
{
  return DynCubeLight_ptSpotlightCollection->nAllocated;
}

// source: e/3/dyncubelight.c:465  [size]
struct SpotlightDynCubeObj_s *__cdecl DynCubeLight_GetSpotlight(int iSpotlight)
{
  return *(struct SpotlightDynCubeObj_s **)DynCubeLight_ptSpotlightCollection->papxElement[iSpotlight];
}

// source: e/3/dyncubelight.c:478  [size]
struct PointlightDynCubeObj_s *__cdecl DynCubeLight_GetPointlight(int iPointlight)
{
  return *(struct PointlightDynCubeObj_s **)DynCubeLight_ptPointlightCollection->papxElement[iPointlight];
}

// source: e/3/dyncubelight.c:491  [size]
unsigned __int16 __cdecl DynCubeLight_GetQTaskTypePointlight()
{
  return DynCubeLight_eQTaskTypePointlight;
}

// source: e/3/dyncubelight.c:504  [size]
unsigned __int16 __cdecl DynCubeLight_GetQTaskTypeSpotlight()
{
  return DynCubeLight_eQTaskTypeSpotlight;
}
