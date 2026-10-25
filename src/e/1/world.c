/* e/1/world.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: e/1/world.c:347  [size]
int __cdecl World_IsTerrainLoaded(struct World_s *ptWorld)
{
  return ptWorld->ptCubeTree != nullptr;
}

// source: e/1/world.c:355  [anchor-hash]
void __cdecl World_ClearImmediateStackItems()
{
  HeightMap_nStackItem = 0;
  TerrainLightMap_nStackItem = 0;
  TextureModifier_nStackItem = 0;
  HeightMap_biHeightMap = 0;
  TextureModifier_biTextureModifier = 0;
}

// source: e/1/world.c:368  [size]
void __cdecl World_SaveImmediateStackItems()
{
  World_anImmediateStackItem[0] = HeightMap_nStackItem;
  World_anImmediateStackItem[1] = TerrainLightMap_nStackItem;
  World_anImmediateStackItem[2] = TextureModifier_nStackItem;
  World_anImmediateStackItem[3] = HeightMap_biHeightMap;
  World_anImmediateStackItem[4] = TextureModifier_biTextureModifier;
}

// source: e/1/world.c:378  [size]
void __cdecl World_LoadImmediateStackItems()
{
  HeightMap_nStackItem = World_anImmediateStackItem[0];
  TerrainLightMap_nStackItem = World_anImmediateStackItem[1];
  TextureModifier_nStackItem = World_anImmediateStackItem[2];
  HeightMap_biHeightMap = World_anImmediateStackItem[3];
  TextureModifier_biTextureModifier = World_anImmediateStackItem[4];
}

// source: e/1/world.c:395  [size]
int __cdecl World_GetDynCubeTreeIndex(
        enum DynCubeTreeCategory_enum eDynCubeTreeCategory,
        unsigned __int16 eQTaskType)
{
  return 0;
}

// source: e/1/world.c:476  [size]
enum DynCubeTreeCategory_enum __cdecl World_GetDynCubeTreeCategory(enum DynCubeTree_e eDynCubeTree)
{
  return WORLD_DYNCUBETREE_CATEGORY_MOBILE;
}

// source: e/1/world.c:792  [anchor-mhash]
int __cdecl World_TraverseWorldCubeTowardsPoint(
        struct World_s *ptWorld,
        struct WorldCube_t *ptWorldCube,
        struct WorldCube_t *ptDest,
        struct real64x3_t *ptPos,
        int nLevels)
{
  unsigned int nRadius; // ebx
  int nRadiusBit; // ecx
  unsigned int v8; // esi
  int v9; // edx
  int v10; // eax
  int v11; // esi
  int v12; // edx
  int v13; // eax
  int v14; // edx
  int v15; // esi
  int v16; // edi
  int v17; // ecx
  unsigned __int8 v18; // al
  int nY; // [esp+8h] [ebp-34h]
  int nYa; // [esp+8h] [ebp-34h]
  int nZ; // [esp+Ch] [ebp-30h]
  int nZa; // [esp+Ch] [ebp-30h]
  int nCurrentRadiusBit; // [esp+10h] [ebp-2Ch]
  int nCurrentOrientation; // [esp+14h] [ebp-28h]
  struct CubeTree_s *ptCubeTree; // [esp+18h] [ebp-24h]
  int nCurrentRadius; // [esp+1Ch] [ebp-20h]
  int nCubeCenterX; // [esp+20h] [ebp-1Ch]
  int nCubeCenterY; // [esp+24h] [ebp-18h]
  int nCubeCenterZ; // [esp+28h] [ebp-14h]
  int nLevel; // [esp+2Ch] [ebp-10h]
  struct CubeTree_s *ptTopOfTree; // [esp+30h] [ebp-Ch]
  struct DynCubeTreeItem_s *ptDynCubeTerrainModifier; // [esp+34h] [ebp-8h]
  struct World_s *ptWorlda = *(struct World_s * *)&ptWorldCube; // [esp+40h] [ebp+4h] ARGSLOT
  struct World_s *ptWorldb = *(struct World_s * *)&ptWorldCube; // [esp+40h] [ebp+4h] ARGSLOT

  ptCubeTree = ptWorldCube->ptCubeTreeItem;
  ptTopOfTree = ptWorldCube->ptWorld->ptCubeTree;
  nRadius = ptWorldCube->nRadius;
  nRadiusBit = ptWorldCube->nRadiusBit;
  nCurrentOrientation = ptWorldCube->nOrientation;
  nCubeCenterX = ptWorldCube->nX;
  nCubeCenterY = ptWorldCube->nY;
  nCubeCenterZ = ptWorldCube->nZ;
  ptWorlda = (struct World_s *)(__int64)ptPos->vX;
  nY = (__int64)ptPos->vY;
  nCurrentRadius = nRadius;
  nCurrentRadiusBit = nRadiusBit;
  nZ = (__int64)ptPos->vZ;
  ptDynCubeTerrainModifier = ptWorld->aptDynCubeTree[0];
  if ( ptPos->vX < 0.0 && (double)(int)ptWorlda != ptPos->vX )
    ptWorlda = (struct World_s *)((char *)ptWorlda - 1);
  if ( ptPos->vY < 0.0 && (double)nY != ptPos->vY )
    --nY;
  if ( ptPos->vZ < 0.0 && (double)nZ != ptPos->vZ )
    --nZ;
  v8 = (unsigned int)ptWorlda + ptWorld->tOrigo.nX;
  v9 = nY + ptWorld->tOrigo.nY;
  v10 = nZ + ptWorld->tOrigo.nZ;
  HeightMap_nStackItem = 0;
  TerrainLightMap_nStackItem = 0;
  TextureModifier_nStackItem = 0;
  HeightMap_biHeightMap = 0;
  TextureModifier_biTextureModifier = 0;
  nLevel = 0;
  v11 = v8 ^ 0x40000000;
  v12 = v9 ^ 0x40000000;
  v13 = v10 ^ 0x40000000;
  ptWorldb = (struct World_s *)v11;
  nYa = v12;
  nZa = v13;
  if ( nLevels > 0 )
  {
    while ( 1 )
    {
      v14 = (v12 >> nRadiusBit) & 1;
      v15 = (v11 >> nRadiusBit) & 1;
      v16 = (v13 >> nRadiusBit) & 1;
      v17 = (4 * v16) | World_abOrientationData[nCurrentOrientation][v15 | (2 * v14)];
      nRadius = nCurrentRadius;
      if ( ((unsigned __int8)(1 << v17) & ptCubeTree->bEnableData) == 0 )
        break;
      nRadius = nCurrentRadius >> 1;
      --nCurrentRadiusBit;
      nCubeCenterY -= v14 + ((nCurrentRadius >> 1) ^ -v14);
      nCubeCenterX -= v15 + ((nCurrentRadius >> 1) ^ -v15);
      nCubeCenterZ -= v16 + ((nCurrentRadius >> 1) ^ -v16);
      v18 = ptCubeTree->abOrientation[v17];
      nCurrentRadius >>= 1;
      nCurrentOrientation = nCurrentOrientation >= 4
                          ? (((unsigned __int8)nCurrentOrientation ^ v18) & 4)
                          + (((_BYTE)nCurrentOrientation - v18) & 3)
                          : (v18 & 4) + ((v18 + (_BYTE)nCurrentOrientation) & 3);
      ptCubeTree = &ptTopOfTree[ptCubeTree->aiChildIndex[v17]];
      if ( ++nLevel >= nLevels )
        break;
      LOBYTE(nRadiusBit) = nCurrentRadiusBit;
      v11 = (int)ptWorldb;
      v12 = nYa;
      v13 = nZa;
    }
    nRadiusBit = nCurrentRadiusBit;
  }
  ptWorldCube->nRadiusBit = nRadiusBit;
  ptWorldCube->nX = nCubeCenterX;
  ptWorldCube->nOrientation = nCurrentOrientation;
  ptWorldCube->nY = nCubeCenterY;
  ptWorldCube->nRadius = nRadius;
  ptWorldCube->ptCubeTreeItem = ptCubeTree;
  ptWorldCube->nZ = nCubeCenterZ;
  ptWorldCube->ptDynCubeTerrainModifier = ptDynCubeTerrainModifier;
  return nLevel;
}

// source: e/1/world.c:937  [anchor-mhash]
struct DynCubeTreeItem_s *__cdecl DynCube_InitEmptyCube(
        struct World_s *ptWorld,
        struct DynCubeTreeItem_s *ptCube,
        int nCube,
        int nRadius,
        enum DynCubeTree_e eDynCubeTree)
{
  ptCube->bChildren = 0;
  ptCube->nCube = nCube;
  ptCube->ptParent = nullptr;
  ptCube->aptChild[0] = nullptr;
  ptCube->aptChild[1] = nullptr;
  ptCube->aptChild[2] = nullptr;
  ptCube->aptChild[3] = nullptr;
  ptCube->aptChild[4] = nullptr;
  ptCube->aptChild[5] = nullptr;
  ptCube->aptChild[6] = nullptr;
  ptCube->aptChild[7] = nullptr;
  ptCube->ptDynCubeObj = nullptr;
  ptCube->nSize = nRadius;
  ptCube->eDynCubeTree = eDynCubeTree;
  return ptCube;
}

// source: e/1/world.c:1021  [anchor-mhash]
struct DynCubeObj_s *__cdecl DynCube_RegisterObjLinkedList(
        struct DynCubeTreeItem_s *ptDynCubeObjTreeItem,
        struct DynCubeObj_s *ptDynCubeObj)
{
  struct DynCubeObj_s *v2; // ecx

  v2 = ptDynCubeObjTreeItem->ptDynCubeObj;
  if ( v2 )
  {
    v2->ptPrev = ptDynCubeObj;
    ptDynCubeObj->ptNext = v2;
  }
  else
  {
    ptDynCubeObj->ptNext = nullptr;
  }
  ptDynCubeObj->ptPrev = nullptr;
  ptDynCubeObj->ptDynCubeObjTreeItem = ptDynCubeObjTreeItem;
  ptDynCubeObjTreeItem->ptDynCubeObj = ptDynCubeObj;
  return ptDynCubeObj;
}

// source: e/1/world.c:1067  [anchor-callee]
struct DynCubeTreeItem_s *__cdecl DynCube_DelEmptyTreeNodesUpwards(
        struct World_s *ptWorld,
        struct DynCubeTreeItem_s *ptDynCubeObjTreeItem)
{
  struct DynCubeTreeItem_s *v2; // esi
  unsigned int nCube; // ecx
  struct DynCubeTreeItem_s *result; // eax
  struct DynCubeObj_s *ptDynCubeObj; // ebp
  int i; // edx
  struct MemPoolFreeItem_s *v7; // esi

  v2 = ptDynCubeObjTreeItem;
  nCube = ptDynCubeObjTreeItem->nCube;
  result = ptDynCubeObjTreeItem->ptParent;
  ptDynCubeObj = v2->ptDynCubeObj;
  for ( i = ~(1 << nCube); result; i = ~(1 << nCube) )
  {
    if ( !v2->bChildren && !ptDynCubeObj )
    {
      v7 = (struct MemPoolFreeItem_s *)result->aptChild[nCube];
      --ptWorld->tDynCubeObjTreeItemPool.nAllocatedBlocks;
      v7->ptNext = ptWorld->tDynCubeObjTreeItemPool.tMemPoolFreeList.ptHead;
      ptWorld->tDynCubeObjTreeItemPool.tMemPoolFreeList.ptHead = v7;
      result->aptChild[nCube] = nullptr;
      result->bChildren &= i;
    }
    nCube = result->nCube;
    ptDynCubeObj = result->ptDynCubeObj;
    v2 = result;
    result = result->ptParent;
  }
  return result;
}

// source: e/1/world.c:1194  [anchor-callee]
void __cdecl DynCube_DelUpTo(
        struct World_s *ptWorld,
        unsigned int nTopSize,
        unsigned int nCurrentSize,
        struct DynCubeTreeItem_s **pptDynCubeObjTreeItem)
{
  struct DynCubeTreeItem_s **v4; // eax
  struct DynCubeTreeItem_s *v5; // edx
  unsigned int v6; // ebp
  unsigned int nCube; // esi
  struct DynCubeTreeItem_s *ptParent; // eax
  struct MemPoolFreeItem_s *v9; // ecx

  v4 = pptDynCubeObjTreeItem;
  v5 = *pptDynCubeObjTreeItem;
  v6 = nCurrentSize;
  if ( nTopSize > nCurrentSize )
  {
    do
    {
      nCube = v5->nCube;
      ptParent = v5->ptParent;
      if ( !v5->bChildren && !v5->ptDynCubeObj )
      {
        v9 = (struct MemPoolFreeItem_s *)ptParent->aptChild[nCube];
        --ptWorld->tDynCubeObjTreeItemPool.nAllocatedBlocks;
        v9->ptNext = ptWorld->tDynCubeObjTreeItemPool.tMemPoolFreeList.ptHead;
        ptWorld->tDynCubeObjTreeItemPool.tMemPoolFreeList.ptHead = v9;
        ptParent->aptChild[nCube] = nullptr;
        ptParent->bChildren &= ~(1 << nCube);
      }
      v5 = ptParent;
      v6 *= 2;
    }
    while ( nTopSize > v6 );
    v4 = pptDynCubeObjTreeItem;
  }
  *v4 = v5;
}

// source: e/1/world.c:1316  [anchor-mhash]
void __cdecl DynCube_RemoveObjLinkedList(
        struct DynCubeTreeItem_s *ptDynCubeObjTreeItem,
        struct DynCubeObj_s *ptDynCubeObj)
{
  struct DynCubeObj_s *ptNext; // eax
  struct DynCubeObj_s *ptPrev; // ecx

  ptNext = ptDynCubeObj->ptNext;
  if ( ptDynCubeObj == ptDynCubeObjTreeItem->ptDynCubeObj )
  {
    ptDynCubeObjTreeItem->ptDynCubeObj = ptNext;
    if ( ptNext )
      ptNext->ptPrev = nullptr;
  }
  else
  {
    ptPrev = ptDynCubeObj->ptPrev;
    if ( ptNext )
      ptNext->ptPrev = ptPrev;
    if ( ptPrev )
      ptPrev->ptNext = ptNext;
  }
}

// source: e/1/world.c:1360  [anchor-callee]
struct DynCubeTreeItem_s *__cdecl World_RegisterObj(
        struct World_s *ptWorld,
        struct DynCubeTreeItem_s *ptDynCubeObjTreeItem,
        struct DynCubeObj_s *ptDynCubeObj,
        unsigned int nObjSize,
        int nX,
        int nY,
        int nZ)
{
  struct DynCubeTreeItem_s *v7; // edi
  unsigned int nSize; // ebx
  unsigned int v9; // ebp
  struct MemPoolFreeItem_s *ptHead; // eax
  struct MemPoolFreeItem_s *eDynCubeTree; // ecx
  struct DynCubeObj_s *v12; // eax
  struct DynCubeTreeItem_s *result; // eax

  v7 = ptDynCubeObjTreeItem;
  nSize = ptDynCubeObjTreeItem->nSize;
  for ( ptWorld->aisStartDynCubeValid[ptDynCubeObjTreeItem->eDynCubeTree] = 0; nSize != nObjSize; v7 = v7->aptChild[v9] )
  {
    v9 = (nSize & nX) != 0;
    if ( (nSize & nY) != 0 )
      v9 |= 2u;
    if ( (nSize & nZ) != 0 )
      v9 |= 4u;
    nSize >>= 1;
    v7->bChildren |= 1 << v9;
    if ( !v7->aptChild[v9] )
    {
      if ( ptWorld->tDynCubeObjTreeItemPool.nAllocatedBlocks == ptWorld->tDynCubeObjTreeItemPool.nBlocks )
        MemPool_ReAlloc(&ptWorld->tDynCubeObjTreeItemPool, ptWorld->tDynCubeObjTreeItemPool.nReAllocBlocks);
      ++ptWorld->tDynCubeObjTreeItemPool.nAllocatedBlocks;
      ptHead = ptWorld->tDynCubeObjTreeItemPool.tMemPoolFreeList.ptHead;
      ptWorld->tDynCubeObjTreeItemPool.tMemPoolFreeList.ptHead = ptHead->ptNext;
      v7->aptChild[v9] = (struct DynCubeTreeItem_s *)ptHead;
      eDynCubeTree = (struct MemPoolFreeItem_s *)v7->eDynCubeTree;
      LOBYTE(ptHead[12].ptNext) = 0;
      ptHead[1].ptNext = (struct MemPoolFreeItem_s *)v9;
      ptHead->ptNext = (struct MemPoolFreeItem_s *)nSize;
      ptHead[2].ptNext = nullptr;
      ptHead[3].ptNext = nullptr;
      ptHead[4].ptNext = nullptr;
      ptHead[5].ptNext = nullptr;
      ptHead[6].ptNext = nullptr;
      ptHead[7].ptNext = nullptr;
      ptHead[8].ptNext = nullptr;
      ptHead[9].ptNext = nullptr;
      ptHead[10].ptNext = nullptr;
      ptHead[11].ptNext = nullptr;
      ptHead[13].ptNext = eDynCubeTree;
      v7->aptChild[v9]->ptParent = v7;
    }
  }
  v12 = v7->ptDynCubeObj;
  if ( v12 )
  {
    v12->ptPrev = ptDynCubeObj;
    ptDynCubeObj->ptNext = v12;
    result = (struct DynCubeTreeItem_s *)ptDynCubeObj;
  }
  else
  {
    result = (struct DynCubeTreeItem_s *)ptDynCubeObj;
    ptDynCubeObj->ptNext = nullptr;
  }
  ptDynCubeObj->ptDynCubeObjTreeItem = v7;
  ptDynCubeObj->ptPrev = nullptr;
  v7->ptDynCubeObj = ptDynCubeObj;
  return result;
}

// source: e/1/world.c:1475  [anchor-hash]
void __cdecl World_Open()
{
  QTask_NewSystemQTaskEventFn(0, 9, "LineOfSight");
  QTask_NewSystemQTaskEventFn(0, 10, "TraceLines");
  QTask_NewSystemQTaskEventFn(0, 11, "GetNextZ");
  QTask_NewSystemQTaskEventFn(0, 12, "GetMaterial");
  QTask_NewSystemQTaskEventFn(0, 13, "CollisionEval");
  QTask_NewSystemQTaskEventFn(0, 14, "ModifyGroundMaterial");
  World_ptTriggerMinMaxXYZProfileRegion = nullptr;
  World_ptTriggerMinMaxXYZProfileRegionWOHandlers = nullptr;
  World_ptTriggerXYZProfileRegion = nullptr;
  World_ptTriggerXYZProfileRegionWOHandlers = nullptr;
  World_ptTriggerAlongLineProfileRegion = nullptr;
  World_ptTriggerAlongLineProfileRegionWOHandlers = nullptr;
  World_ptTraceLinesProfileRegion = nullptr;
  World_ptTraceLinesProfileRegionWOHandlers = nullptr;
  World_ptTraceLineStepProfileRegion = nullptr;
  World_ptTraceLineStepPosProfileRegion = nullptr;
  World_ptGetMaterialProfileRegion = nullptr;
  World_ptGetMaterialTerrainMeshProfileRegion = nullptr;
  World_ptGetMaterialCubeIndexProfileRegion = nullptr;
  World_ptGetNextZProfileRegion = nullptr;
  World_ptGetNextZNoMaterialProfileRegion = nullptr;
  World_ptLineOfSightProfileRegion = nullptr;
  World_ptMoveDynCubeObjRadiusProfileRegion = nullptr;
  QTask_AllocateSystemGroup((unsigned int)&MTP_atLODVirModel[296].atBoneVertexRefs[36].atVertexRefs[609]);
}

// source: e/1/world.c:1532  [anchor-hash]
void __cdecl World_Close()
{
  QTask_FreeGroup((unsigned int)&MTP_atLODVirModel[296].atBoneVertexRefs[36].atVertexRefs[609]);
  QTask_DeleteQTaskEvent(9);
  QTask_DeleteQTaskEvent(10);
  QTask_DeleteQTaskEvent(11);
  QTask_DeleteQTaskEvent(12);
  QTask_DeleteQTaskEvent(13);
  QTask_DeleteQTaskEvent(14);
}

// source: e/1/world.c:1567  [anchor-hash]
struct World_s *__cdecl World_New(int nMaxDynCubeItems)
{
  struct World_s *v2; // ebp
  unsigned __int8 **p_pxData; // eax
  struct MemPoolFreeItem_s *ptHead; // eax

  v2 = (struct World_s *)Mem_AllocFn(672, 4);
  memset(v2, 0, sizeof(struct World_s));
  v2->ptTerrainQTaskList = nullptr;
  v2->ptWater = nullptr;
  v2->ptCubeTree = nullptr;
  v2->zLightmapFile[0] = 0;
  v2->ptManualRedrawList = nullptr;
  v2->nTerrainLightMap = 0;
  v2->pxLightMapFile = nullptr;
  p_pxData = &TerrainLightMap_atTexInfo[0].pxData;
  do
  {
    *(p_pxData - 1) = nullptr;
    *p_pxData = nullptr;
    p_pxData += 13;
  }
  while ( (int)p_pxData < 139161156 );
  v2->pnWaveIndex = nullptr;
  v2->ptWaveTable = nullptr;
  v2->tOrigo.nX = 0;
  v2->tOrigo.nY = 0;
  v2->tOrigo.nZ = 0;
  v2->ptTerrainTex = nullptr;
  v2->ptTerrainPalInfo = nullptr;
  v2->pxCubeMeshData = nullptr;
  v2->pxCubeData = nullptr;
  v2->ptMaterialBitmap = nullptr;
  v2->ptHeightBitmap = nullptr;
  v2->tDynCubeObjTreeItemPool.nBlocks = 0;
  v2->tDynCubeObjTreeItemPool.nAllocatedBlocks = 0;
  v2->tDynCubeObjTreeItemPool.nAlignment = 4;
  v2->tDynCubeObjTreeItemPool.nBlockSize = 56;
  v2->tDynCubeObjTreeItemPool.nReAllocBlocks = 0;
  v2->tDynCubeObjTreeItemPool.tMemPoolFreeList.ptHead = nullptr;
  v2->tDynCubeObjTreeItemPool.tMemPoolSegmentList.ptHead = nullptr;
  if ( nMaxDynCubeItems )
    MemPool_ReAlloc(&v2->tDynCubeObjTreeItemPool, nMaxDynCubeItems);
  if ( v2->tDynCubeObjTreeItemPool.nAllocatedBlocks == v2->tDynCubeObjTreeItemPool.nBlocks )
    MemPool_ReAlloc(&v2->tDynCubeObjTreeItemPool, v2->tDynCubeObjTreeItemPool.nReAllocBlocks);
  ptHead = v2->tDynCubeObjTreeItemPool.tMemPoolFreeList.ptHead;
  ++v2->tDynCubeObjTreeItemPool.nAllocatedBlocks;
  v2->tDynCubeObjTreeItemPool.tMemPoolFreeList.ptHead = ptHead->ptNext;
  v2->aptDynCubeTree[0] = (struct DynCubeTreeItem_s *)ptHead;
  LOBYTE(ptHead[12].ptNext) = 0;
  ptHead[1].ptNext = nullptr;
  ptHead->ptNext = (struct MemPoolFreeItem_s *)0x40000000;
  ptHead[2].ptNext = nullptr;
  ptHead[3].ptNext = nullptr;
  ptHead[4].ptNext = nullptr;
  ptHead[5].ptNext = nullptr;
  ptHead[6].ptNext = nullptr;
  ptHead[7].ptNext = nullptr;
  ptHead[8].ptNext = nullptr;
  ptHead[9].ptNext = nullptr;
  ptHead[10].ptNext = nullptr;
  ptHead[11].ptNext = nullptr;
  ptHead[13].ptNext = nullptr;
  v2->aisStartDynCubeValid[0] = 0;
  World_UpdateStartDynCube(v2, WORLD_DYNCUBETREE_STATIONARY);
  v2->isLightingTablesValid = 0;
  World_isImmediateRunOnCollision = 0;
  HeightMap_nStackItem = 0;
  TerrainLightMap_nStackItem = 0;
  TextureModifier_nStackItem = 0;
  HeightMap_biHeightMap = 0;
  TextureModifier_biTextureModifier = 0;
  return v2;
}

// source: e/1/world.c:1653  [anchor-callee]
void __cdecl World_UnloadTerrain(struct World_s *ptWorld)
{
  struct MultiTex_s *ptTerrainTex; // eax
  struct PalInfo *ptTerrainPalInfo; // eax
  struct PalInfo *v4; // eax
  int v5; // ebp
  int i; // ebp
  unsigned __int8 *ptBitmap; // eax
  int v8; // esi
  int j; // ebp
  unsigned __int8 *v10; // eax
  int v11; // esi
  void *pxCubeMeshData; // edx
  struct Resource_s *ptHead; // ecx
  struct Resource_s *ptNext; // eax
  unsigned int nType; // eax
  struct CubeTree_s *ptCubeTree; // edx
  struct Resource_s *v17; // ecx
  struct Resource_s *v18; // eax
  unsigned int v19; // eax
  void **p_ptHashCubeData; // eax
  void *pxCubeData; // edx
  struct Resource_s *v22; // ecx
  struct Resource_s *v23; // eax
  unsigned int v24; // eax
  struct Terrain_MaterialBitmap_t *ptMaterialBitmap; // edx
  struct Resource_s *v26; // ecx
  struct Resource_s *v27; // eax
  unsigned int v28; // eax
  struct Terrain_HeightBitmap_t *ptHeightBitmap; // edx
  struct Resource_s *v30; // ecx
  struct Resource_s *v31; // eax
  unsigned int v32; // eax
  struct TexInfo_s *p_tTexInfo; // ebx
  int iMaterialBitmap; // [esp+Ch] [ebp-4h]
  int iMaterialBitmapa; // [esp+Ch] [ebp-4h]

  ptTerrainTex = ptWorld->ptTerrainTex;
  if ( ptTerrainTex )
  {
    MultiTex_Delete(ptTerrainTex);
    ptWorld->ptTerrainTex = nullptr;
  }
  ptTerrainPalInfo = ptWorld->ptTerrainPalInfo;
  if ( ptTerrainPalInfo )
  {
    if ( ptTerrainPalInfo->eRenderMode != -1 )
      RenderMode_atRenderMode[ptTerrainPalInfo->eRenderMode].apfRenderModeMethod[Palette_eDeAllocPaletteMethod](ptTerrainPalInfo);
    v4 = ptWorld->ptTerrainPalInfo;
    if ( v4 )
    {
      --Mem_nCurrentAllocations;
      v5 = *(_DWORD *)((unsigned int)&v4[-1].pxPalette & 0xFFFFFFFC);
      Node_Remove((_DWORD **)v5);
      memset(*(void **)(v5 + 8), 0xCDu, *(_DWORD *)(v5 + 16));
      free((void *)v5);
    }
    ptWorld->ptTerrainPalInfo = nullptr;
  }
  if ( ptWorld->ptMaterialBitmap )
  {
    iMaterialBitmap = 0;
    for ( i = 0; i < 256; ++i )
    {
      ptBitmap = ptWorld->ptMaterialBitmap[i].ptBitmap;
      if ( ptBitmap && !World_aisMaterialBitmapResource[iMaterialBitmap] )
      {
        v8 = *(_DWORD *)((unsigned int)(ptBitmap - 4) & 0xFFFFFFFC);
        --Mem_nCurrentAllocations;
        Node_Remove((_DWORD **)v8);
        memset(*(void **)(v8 + 8), 0xCDu, *(_DWORD *)(v8 + 16));
        free((void *)v8);
        ptWorld->ptMaterialBitmap[i].ptBitmap = nullptr;
        ptWorld->ptMaterialBitmap[i].ptBitmap = nullptr;
      }
      ++iMaterialBitmap;
    }
  }
  if ( ptWorld->ptHeightBitmap )
  {
    iMaterialBitmapa = 0;
    for ( j = 0; j < 256; ++j )
    {
      v10 = ptWorld->ptHeightBitmap[j].ptBitmap;
      if ( v10 && !World_aisHeightBitmapResource[iMaterialBitmapa] )
      {
        v11 = *(_DWORD *)((unsigned int)(v10 - 4) & 0xFFFFFFFC);
        --Mem_nCurrentAllocations;
        Node_Remove((_DWORD **)v11);
        memset(*(void **)(v11 + 8), 0xCDu, *(_DWORD *)(v11 + 16));
        free((void *)v11);
        ptWorld->ptHeightBitmap[j].ptBitmap = nullptr;
        ptWorld->ptHeightBitmap[j].ptBitmap = nullptr;
      }
      ++iMaterialBitmapa;
    }
  }
  pxCubeMeshData = ptWorld->pxCubeMeshData;
  if ( pxCubeMeshData )
  {
    ptHead = Resource_tResourceList.ptHead;
    ptNext = Resource_tResourceList.ptHead->ptNext;
    if ( Resource_tResourceList.ptHead->ptNext )
    {
      while ( ptHead->pxData != pxCubeMeshData )
      {
        ptHead = ptNext;
        ptNext = ptNext->ptNext;
        if ( !ptNext )
          goto LABEL_29;
      }
      nType = ptHead->nType;
      if ( nType != 3 && nType != 1 )
        Resource_Remove(ptHead);
    }
LABEL_29:
    ptWorld->pxCubeMeshData = nullptr;
  }
  ptCubeTree = ptWorld->ptCubeTree;
  if ( ptCubeTree )
  {
    v17 = Resource_tResourceList.ptHead;
    v18 = Resource_tResourceList.ptHead->ptNext;
    if ( Resource_tResourceList.ptHead->ptNext )
    {
      while ( v17->pxData != ptCubeTree )
      {
        v17 = v18;
        v18 = v18->ptNext;
        if ( !v18 )
          goto LABEL_38;
      }
      v19 = v17->nType;
      if ( v19 != 3 && v19 != 1 )
        Resource_Remove(v17);
    }
LABEL_38:
    p_ptHashCubeData = &QCube_atCubeHash[0].ptHashCubeData;
    do
    {
      *(p_ptHashCubeData - 2) = (void *)-1;
      *p_ptHashCubeData = nullptr;
      p_ptHashCubeData += 7;
    }
    while ( (int)p_ptHashCubeData < 139693560 );
    ptWorld->ptCubeTree = nullptr;
  }
  pxCubeData = ptWorld->pxCubeData;
  if ( pxCubeData )
  {
    v22 = Resource_tResourceList.ptHead;
    v23 = Resource_tResourceList.ptHead->ptNext;
    if ( Resource_tResourceList.ptHead->ptNext )
    {
      while ( v22->pxData != pxCubeData )
      {
        v22 = v23;
        v23 = v23->ptNext;
        if ( !v23 )
          goto LABEL_49;
      }
      v24 = v22->nType;
      if ( v24 != 3 && v24 != 1 )
        Resource_Remove(v22);
    }
LABEL_49:
    ptWorld->pxCubeData = nullptr;
  }
  ptMaterialBitmap = ptWorld->ptMaterialBitmap;
  if ( ptMaterialBitmap )
  {
    v26 = Resource_tResourceList.ptHead;
    v27 = Resource_tResourceList.ptHead->ptNext;
    if ( Resource_tResourceList.ptHead->ptNext )
    {
      while ( v26->pxData != ptMaterialBitmap )
      {
        v26 = v27;
        v27 = v27->ptNext;
        if ( !v27 )
          goto LABEL_58;
      }
      v28 = v26->nType;
      if ( v28 != 3 && v28 != 1 )
        Resource_Remove(v26);
    }
LABEL_58:
    ptWorld->ptMaterialBitmap = nullptr;
  }
  ptHeightBitmap = ptWorld->ptHeightBitmap;
  if ( ptHeightBitmap )
  {
    v30 = Resource_tResourceList.ptHead;
    v31 = Resource_tResourceList.ptHead->ptNext;
    if ( Resource_tResourceList.ptHead->ptNext )
    {
      while ( v30->pxData != ptHeightBitmap )
      {
        v30 = v31;
        v31 = v31->ptNext;
        if ( !v31 )
          goto LABEL_67;
      }
      v32 = v30->nType;
      if ( v32 != 3 && v32 != 1 )
        Resource_Remove(v30);
    }
LABEL_67:
    ptWorld->ptHeightBitmap = nullptr;
  }
  p_tTexInfo = &TerrainLightMap_atTexInfo[0].tTexInfo;
  do
  {
    if ( p_tTexInfo[-1].eDirect3DFormat )
    {
      if ( AppContext_tAppContext.isMainMenu == false )
        RenderMode_atRenderMode[p_tTexInfo->eRenderMode].apfRenderModeMethod[Texture_eDeAllocTextureMethod](p_tTexInfo);
      memset(p_tTexInfo, 0, sizeof(struct TexInfo_s));
      p_tTexInfo[-1].eDirect3DFormat = D3DFMT_UNKNOWN;
    }
    p_tTexInfo = (struct TexInfo_s *)((char *)p_tTexInfo + 52);
  }
  while ( (int)p_tTexInfo < 139161160 );
}

// source: e/1/world.c:1755  [anchor-callee]
void __cdecl World_FreeTree(struct World_s *ptWorld, struct DynCubeTreeItem_s *ptTree)
{
  struct DynCubeObj_s *i; // eax
  struct DynCubeTreeItem_s **aptChild; // esi
  int v4; // ebx

  for ( i = ptTree->ptDynCubeObj; i; i = i->ptNext )
    ;
  aptChild = ptTree->aptChild;
  v4 = 8;
  do
  {
    if ( *aptChild )
      World_FreeTree(ptWorld, *aptChild);
    ++aptChild;
    --v4;
  }
  while ( v4 );
  --ptWorld->tDynCubeObjTreeItemPool.nAllocatedBlocks;
  ptTree->nSize = (unsigned int)ptWorld->tDynCubeObjTreeItemPool.tMemPoolFreeList.ptHead;
  ptWorld->tDynCubeObjTreeItemPool.tMemPoolFreeList.ptHead = (struct MemPoolFreeItem_s *)ptTree;
}

// source: e/1/world.c:1791  [anchor-hash]
void __cdecl World_Delete(struct World_s *ptWorld)
{
  struct WaterWave_t *ptWaveTable; // eax
  int v3; // ebx
  unsigned __int8 *pnWaveIndex; // eax
  int v5; // ebx
  int v6; // esi

  ptWaveTable = ptWorld->ptWaveTable;
  if ( ptWaveTable )
  {
    --Mem_nCurrentAllocations;
    v3 = *(_DWORD *)((unsigned int)&ptWaveTable[-1].tNormal.vZ & 0xFFFFFFFC);
    Node_Remove((_DWORD **)v3);
    memset(*(void **)(v3 + 8), 0xCDu, *(_DWORD *)(v3 + 16));
    free((void *)v3);
    ptWorld->ptWaveTable = nullptr;
  }
  pnWaveIndex = ptWorld->pnWaveIndex;
  if ( pnWaveIndex )
  {
    v5 = *(_DWORD *)((unsigned int)(pnWaveIndex - 4) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v5);
    memset(*(void **)(v5 + 8), 0xCDu, *(_DWORD *)(v5 + 16));
    free((void *)v5);
    ptWorld->pnWaveIndex = nullptr;
  }
  World_UnloadTerrain(ptWorld);
  World_FreeTree(ptWorld, ptWorld->aptDynCubeTree[0]);
  MemPool_DeInit(&ptWorld->tDynCubeObjTreeItemPool);
  v6 = *(_DWORD *)((unsigned int)(&ptWorld[-1].ptTerrainQTaskList + 1) & 0xFFFFFFFC);
  --Mem_nCurrentAllocations;
  Node_Remove((_DWORD **)v6);
  memset(*(void **)(v6 + 8), 0xCDu, *(_DWORD *)(v6 + 16));
  free((void *)v6);
}

// source: e/1/world.c:1833  [anchor-mhash]
struct Result_s *__cdecl World_CreateTerrainMaterial(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *aArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int pxData; };
    struct { char igi2_o1[4]; int v17; };
    struct { char igi2_o2[8]; float v18; };
    struct { char igi2_o3[12]; float v19; };
    struct { char igi2_o4[16]; float v20; };
    struct { char igi2_o5[20]; int v21; };
    struct { char igi2_o6[24]; float v22; };
    struct { char igi2_o7[28]; int v23; };
    struct { char igi2_o8[32]; struct Result_s Rs; };
    char igi2_extent[56];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v3; // esi
  int v4; // eax
  int v5; // ecx
  int v6; // esi
  float *p_vFadeScale; // ebx
  int v8; // eax
  double v9; // st7
  double v10; // st7
  double v11; // st7
  int v12; // eax
  double v13; // st7
  int v14; // eax

  if ( aArgList->isQVM )
  {
    igi2_frame.pxData = 0;
    QVM_EvalArg(&igi2_frame.pxData, 4, aArgList, 0, 1);
    v3 = igi2_frame.pxData;
  }
  else
  {
    v3 = Expression_EvalInt(*aArgList->aptExpression);
  }
  if ( aArgList->isQVM )
  {
    igi2_frame.pxData = 0;
    QVM_EvalArg(&igi2_frame.pxData, 4, aArgList, 1, 1);
    v4 = igi2_frame.pxData;
  }
  else
  {
    v4 = Expression_EvalInt(aArgList->aptExpression[1]);
  }
  v5 = v3;
  TerrainMesh_atMaterial[v5].iQMaterial = v4;
  v6 = 3;
  p_vFadeScale = &TerrainMesh_atMaterial[v5].atTexLOD[0].vFadeScale;
  for ( igi2_frame.pxData = 12; igi2_frame.pxData < 908; igi2_frame.pxData += 28 )
  {
    if ( aArgList->isQVM )
    {
      igi2_frame.v17 = 0;
      QVM_EvalArg(&igi2_frame.v17, 4, aArgList, v6 - 1, 1);
      v8 = igi2_frame.v17;
    }
    else
    {
      v8 = Expression_EvalInt(*(struct QExpression_s **)((char *)aArgList->aptExpression + igi2_frame.pxData - 4));
    }
    *((_DWORD *)p_vFadeScale - 1) = v8;
    if ( aArgList->isQVM )
    {
      igi2_frame.v18 = 0.0;
      QVM_EvalArg(&igi2_frame.v18, 4, aArgList, v6, 2);
      v9 = igi2_frame.v18;
    }
    else
    {
      v9 = Expression_EvalFloat(*(struct QExpression_s **)((char *)aArgList->aptExpression + igi2_frame.pxData));
    }
    *p_vFadeScale = v9;
    if ( aArgList->isQVM )
    {
      igi2_frame.v19 = 0.0;
      QVM_EvalArg(&igi2_frame.v19, 4, aArgList, v6 + 1, 2);
      v10 = igi2_frame.v19;
    }
    else
    {
      v10 = Expression_EvalFloat(*(struct QExpression_s **)((char *)aArgList->aptExpression + igi2_frame.pxData + 4));
    }
    p_vFadeScale[1] = v10;
    if ( aArgList->isQVM )
    {
      igi2_frame.v20 = 0.0;
      QVM_EvalArg(&igi2_frame.v20, 4, aArgList, v6 + 2, 2);
      v11 = igi2_frame.v20;
    }
    else
    {
      v11 = Expression_EvalFloat(*(struct QExpression_s **)((char *)aArgList->aptExpression + igi2_frame.pxData + 8));
    }
    p_vFadeScale[2] = v11 * 0.5;
    if ( aArgList->isQVM )
    {
      igi2_frame.v21 = 0;
      QVM_EvalArg(&igi2_frame.v21, 4, aArgList, v6 + 3, 1);
      v12 = igi2_frame.v21;
    }
    else
    {
      v12 = Expression_EvalInt(*(struct QExpression_s **)((char *)aArgList->aptExpression + igi2_frame.pxData + 12));
    }
    *((_DWORD *)p_vFadeScale + 3) = v12;
    if ( aArgList->isQVM )
    {
      igi2_frame.v22 = 0.0;
      QVM_EvalArg(&igi2_frame.v22, 4, aArgList, v6 + 4, 2);
      v13 = igi2_frame.v22;
    }
    else
    {
      v13 = Expression_EvalFloat(*(struct QExpression_s **)((char *)aArgList->aptExpression + igi2_frame.pxData + 16));
    }
    p_vFadeScale[4] = v13 * 0.5;
    if ( aArgList->isQVM )
    {
      igi2_frame.v23 = 0;
      QVM_EvalArg(&igi2_frame.v23, 4, aArgList, v6 + 5, 1);
      v14 = igi2_frame.v23;
    }
    else
    {
      v14 = Expression_EvalInt(*(struct QExpression_s **)((char *)aArgList->aptExpression + igi2_frame.pxData + 20));
    }
    *((_DWORD *)p_vFadeScale + 5) = v14;
    v6 += 7;
    p_vFadeScale += 7;
  }
  igi2_frame.Rs.nResult = 0;
  igi2_frame.Rs.vResult = 0.0;
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: e/1/world.c:1866  [anchor-mhash]
struct Result_s *__cdecl World_CreateTerrainTileMap(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *aArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // eax
  int v5; // esi
  struct TerrainMesh_TileMap_t *v6; // ebp
  unsigned __int8 v7; // al
  struct Result_s Rs; // [esp+10h] [ebp-18h] BYREF

  v3 = aArgList;
  if ( aArgList->isQVM )
  {
    aArgList = nullptr;
    QVM_EvalArg(&aArgList, 4, v3, 0, 1);
    v4 = aArgList;
  }
  else
  {
    v4 = (struct ArgList_s *)Expression_EvalInt(*aArgList->aptExpression);
  }
  v5 = 0;
  v6 = &TerrainMesh_atTileMap[(_DWORD)v4];
  do
  {
    if ( v3->isQVM )
    {
      aArgList = nullptr;
      QVM_EvalArg(&aArgList, 4, v3, v5 + 1, 1);
      v7 = (unsigned __int8)aArgList;
    }
    else
    {
      v7 = Expression_EvalInt(v3->aptExpression[v5 + 1]);
    }
    v6->aiTerrainTex[0][v5++] = v7;
  }
  while ( v5 < 64 );
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: e/1/world.c:1894  [anchor-caller]
char *__cdecl World_LoadTerrainTextureData(struct World_s *ptWorld, char *zFile)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v35; };
    struct { char igi2_o1[4]; int nSize; };
    struct { char igi2_o2[8]; _DWORD v37[2]; };
    struct { char igi2_o3[16]; unsigned int *v38; };
    struct { char igi2_o4[20]; char zTempFileName[128]; };
    struct { char igi2_o5[148]; unsigned int anPalette[256]; };
    char igi2_extent[1172];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char *v2; // ebx
  int v3; // edx
  char v4; // cl
  char *v5; // eax
  char *v6; // esi
  char v7; // cl
  char *v8; // edi
  int v10; // edx
  void (__cdecl *v11)(void *); // eax
  void (__cdecl *v12)(void *); // eax
  void (__cdecl *v13)(void *); // eax
  void (__cdecl *v14)(void *); // eax
  int i; // eax
  struct PalInfo *v16; // eax
  enum RenderMode_enum v17; // ecx
  char *result; // eax
  char *v19; // eax
  char v20; // cl
  char *v21; // edi
  char *v23; // eax
  char v24; // cl
  unsigned __int8 *v25; // edi
  int v26; // ebp
  struct TerrainLightMap_TexInfo_t *v27; // ebx
  int v28; // esi
  char *v29; // edi
  int v30; // ebp
  void (__cdecl *v31)(void *); // eax
  void (__cdecl *v32)(void *); // eax
  void (__cdecl *v33)(void *); // eax
  void (__cdecl *v34)(void *); // eax

  v2 = (char *)zFile;
  v3 = World_zTerrainFileName - zFile;
  do
  {
    v4 = *zFile;
    zFile[v3] = *zFile;
    ++zFile;
  }
  while ( v4 );
  v5 = v2;
  v6 = (char *)(igi2_frame.zTempFileName - v2);
  do
  {
    v7 = *v5;
    v5[(_DWORD)v6] = *v5;
    ++v5;
  }
  while ( v7 );
  v8 = (char *)&igi2_frame.v38 + 3;
  while ( *++v8 )
    ;
  v10 = Texture_eGetTMUsMethod;
  strcpy(v8, ".tex");
  v11 = RenderMode_tActiveRenderMode.apfRenderModeMethod[v10];
  igi2_frame.v35 = 1;
  if ( v11 )
  {
    v11(&igi2_frame.v35);
    if ( igi2_frame.v35 > 1 )
    {
      v12 = RenderMode_tActiveRenderMode.apfRenderModeMethod[Texture_eSetActiveTMUMethod];
      igi2_frame.nSize = 0;
      if ( v12 )
        v12(&igi2_frame.nSize);
    }
  }
  ptWorld->ptTerrainTex = MultiTex_Load(igi2_frame.zTempFileName);
  v13 = RenderMode_tActiveRenderMode.apfRenderModeMethod[Texture_eGetTMUsMethod];
  igi2_frame.v35 = 1;
  if ( v13 )
  {
    v13(&igi2_frame.v35);
    if ( igi2_frame.v35 > 1 )
    {
      v14 = RenderMode_tActiveRenderMode.apfRenderModeMethod[Texture_eSetActiveTMUMethod];
      igi2_frame.nSize = -1;
      if ( v14 )
        v14(&igi2_frame.nSize);
    }
  }
  for ( i = 0; i < 256; ++i )
    igi2_frame.anPalette[i] = i << 16;
  v16 = (struct PalInfo *)Mem_AllocFn(12, 4);
  v17 = RenderMode_eActiveRenderMode;
  ptWorld->ptTerrainPalInfo = v16;
  v16->eRenderMode = v17;
  igi2_frame.v37[0] = v16;
  igi2_frame.v37[1] = 1;
  igi2_frame.v38 = igi2_frame.anPalette;
  RenderMode_tActiveRenderMode.apfRenderModeMethod[Palette_eAllocPaletteMethod](igi2_frame.v37);
  result = (char *)AppContext_tAppContext.isLightmapsDisabled;
  if ( AppContext_tAppContext.isLightmapsDisabled )
  {
    result = (char *)AppContext_tAppContext.isTerrainLightmapsUsed;
    if ( AppContext_tAppContext.isTerrainLightmapsUsed == false )
    {
      v19 = v2;
      do
      {
        v20 = *v19;
        v19[(_DWORD)v6] = *v19;
        ++v19;
      }
      while ( v20 );
      v21 = (char *)&igi2_frame.v38 + 3;
      while ( *++v21 )
        ;
      strcpy(v21, ".lmp");
      v23 = igi2_frame.zTempFileName;
      do
      {
        v24 = *v23;
        v23[(char *)ptWorld - igi2_frame.zTempFileName + 408] = *v23;
        ++v23;
      }
      while ( v24 );
      if ( Resource_IsLoadedInternal(igi2_frame.zTempFileName, nullptr) == false )
      {
        result = (char *)File_New(igi2_frame.zTempFileName, "r");
        if ( !result )
          return result;
        if ( result == (char *)&File_tDummyAsyncFile )
          File_tDummyAsyncFile.isAsync = false;
        else
          File_atDevice[*(_DWORD *)result].pfDelete(*(_DWORD *)result, (struct File_s *)result);
      }
      v25 = (unsigned __int8 *)Resource_Load(igi2_frame.zTempFileName, (unsigned int *)&igi2_frame.nSize);
      ptWorld->pxLightMapFile = v25;
      if ( v25 )
      {
        v26 = 0;
        if ( igi2_frame.nSize > 0 )
        {
          v27 = TerrainLightMap_atTexInfo;
          do
          {
            v28 = *(_DWORD *)v25;
            v29 = (char *)(v25 + 4);
            v30 = v26 + 4;
            if ( v28 )
            {
              v31 = RenderMode_tActiveRenderMode.apfRenderModeMethod[Texture_eGetTMUsMethod];
              igi2_frame.v35 = 1;
              if ( v31 )
              {
                v31(&igi2_frame.v35);
                if ( igi2_frame.v35 > 1 )
                {
                  v32 = RenderMode_tActiveRenderMode.apfRenderModeMethod[Texture_eSetActiveTMUMethod];
                  igi2_frame.v35 = 1;
                  if ( v32 )
                    v32(&igi2_frame.v35);
                }
              }
              Texture_AllocAndDownload(&v27->tTexInfo, ptWorld->ptTerrainPalInfo, v28, v28, v28, 1, 0, 0x20000000u, v29);
              v33 = RenderMode_tActiveRenderMode.apfRenderModeMethod[Texture_eGetTMUsMethod];
              igi2_frame.v35 = 1;
              if ( v33 )
              {
                v33(&igi2_frame.v35);
                if ( igi2_frame.v35 > 1 )
                {
                  v34 = RenderMode_tActiveRenderMode.apfRenderModeMethod[Texture_eSetActiveTMUMethod];
                  igi2_frame.v35 = -1;
                  if ( v34 )
                    v34(&igi2_frame.v35);
                }
              }
              v27->nSize = v28;
              v27->pxData = (unsigned __int8 *)v29;
            }
            v25 = (unsigned __int8 *)&v29[v28 * v28];
            v26 = v28 * v28 + v30;
            ++v27;
          }
          while ( v26 < igi2_frame.nSize );
        }
      }
      result = (char *)Resource_IsLoadedInternal(igi2_frame.zTempFileName, (struct Resource_s **)&igi2_frame.nSize);
      if ( result )
      {
        result = *(char **)(igi2_frame.nSize + 36);
        if ( result != (char *)3 && result != (char *)1 )
          Resource_Remove((struct Resource_s *)igi2_frame.nSize);
      }
    }
  }
  return result;
}

// source: e/1/world.c:2025  [size]
void __cdecl World_ReloadTerrainLightmaps(struct World_s *ptWorld)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v14; };
    struct { char igi2_o1[4]; int nSize; };
    struct { char igi2_o2[8]; char *zFilename; };
    char igi2_extent[12];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct World_s *v1; // ebp
  char *zLightmapFile; // ebx
  int *v3; // edi
  int v4; // ebp
  struct TerrainLightMap_TexInfo_t *v5; // ebx
  int v6; // esi
  char *v7; // edi
  int v8; // ebp
  void (__cdecl *v9)(void *); // eax
  void (__cdecl *v10)(void *); // eax
  void (__cdecl *v11)(void *); // eax
  void (__cdecl *v12)(void *); // eax
  int vY_high; // eax

  v1 = ptWorld;
  zLightmapFile = ptWorld->zLightmapFile;
  igi2_frame.zFilename = ptWorld->zLightmapFile;
  igi2_frame.nSize = strlen(ptWorld->zLightmapFile);
  if ( igi2_frame.nSize && (Resource_IsLoadedInternal(zLightmapFile, nullptr) || File_Exists(zLightmapFile)) )
  {
    v3 = (int *)Resource_Load(zLightmapFile, (unsigned int *)&igi2_frame.nSize);
    v1->pxLightMapFile = (unsigned __int8 *)v3;
    if ( v3 )
    {
      v4 = 0;
      if ( igi2_frame.nSize > 0 )
      {
        v5 = TerrainLightMap_atTexInfo;
        do
        {
          v6 = *v3;
          v7 = (char *)(v3 + 1);
          v8 = v4 + 4;
          if ( v6 )
          {
            v9 = RenderMode_tActiveRenderMode.apfRenderModeMethod[Texture_eGetTMUsMethod];
            igi2_frame.v14 = 1;
            if ( v9 )
            {
              v9(&igi2_frame.v14);
              if ( igi2_frame.v14 > 1 )
              {
                v10 = RenderMode_tActiveRenderMode.apfRenderModeMethod[Texture_eSetActiveTMUMethod];
                igi2_frame.v14 = 1;
                if ( v10 )
                  v10(&igi2_frame.v14);
              }
            }
            Texture_Download(&v5->tTexInfo, ptWorld->ptTerrainPalInfo, v6, v6, v6, 1, v7);
            v11 = RenderMode_tActiveRenderMode.apfRenderModeMethod[Texture_eGetTMUsMethod];
            igi2_frame.v14 = 1;
            if ( v11 )
            {
              v11(&igi2_frame.v14);
              if ( igi2_frame.v14 > 1 )
              {
                v12 = RenderMode_tActiveRenderMode.apfRenderModeMethod[Texture_eSetActiveTMUMethod];
                igi2_frame.v14 = -1;
                if ( v12 )
                  v12(&igi2_frame.v14);
              }
            }
            v5->nSize = v6;
            v5->pxData = (unsigned __int8 *)v7;
          }
          v3 = (int *)&v7[v6 * v6];
          v4 = v6 * v6 + v8;
          ++v5;
        }
        while ( v4 < igi2_frame.nSize );
      }
      zLightmapFile = igi2_frame.zFilename;
    }
    if ( Resource_IsLoadedInternal(zLightmapFile, (struct Resource_s **)&ptWorld) )
    {
      vY_high = HIDWORD(ptWorld->atStartDynCubePos[0].vY);
      if ( vY_high != 3 && vY_high != 1 )
        Resource_Remove((struct Resource_s *)ptWorld);
    }
  }
}

// source: e/1/world.c:2127  [anchor-strings]
void __cdecl World_LoadTerrain(struct World_s *ptWorld, char *zFile)
{
  #pragma pack(push, 1)
  union
  {
    struct { int nCubeTreeSize; };
    struct { char igi2_o1[4]; int v55; };
    struct { char igi2_o2[8]; char zTempFileName[128]; };
    char igi2_extent[136];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  void **p_ptHashCubeData; // eax
  char *v3; // eax
  int v4; // ebx
  char v5; // cl
  char *v6; // edi
  struct Terrain_MaterialBitmap_t *v8; // eax
  struct Terrain_MaterialBitmap_t *v9; // edi
  struct Terrain_MaterialBitmap_t *v10; // edi
  int v11; // esi
  int i; // ecx
  struct Terrain_MaterialBitmap_t *ptMaterialBitmap; // edx
  int nSize; // eax
  struct Terrain_MaterialBitmap_t *v15; // edx
  char *v16; // eax
  char v17; // cl
  char *v18; // edi
  struct File_s *v20; // eax
  struct Terrain_HeightBitmap_t *v21; // eax
  struct Terrain_HeightBitmap_t *v22; // edi
  struct Terrain_HeightBitmap_t *v23; // edi
  int v24; // esi
  int j; // eax
  struct Terrain_HeightBitmap_t *ptHeightBitmap; // ecx
  int v27; // edx
  struct Terrain_HeightBitmap_t *v28; // ecx
  char *v29; // eax
  char v30; // cl
  char *v31; // edi
  char *v33; // ecx
  int v34; // eax
  void *v35; // eax
  void *v36; // eax
  char *v37; // eax
  char v38; // cl
  char *v39; // edi
  char *v41; // eax
  char v42; // cl
  char *v43; // edi
  struct Script_s *v45; // esi
  unsigned int v46; // eax
  int v47; // edx
  struct CubeTree_s *ptCubeTree; // ecx
  struct CubeItem0_MeshHeader_s *ptMesh; // edi
  struct CubeItem0_MeshHeader_s **p_ptMesh; // ecx
  int k; // ecx
  int m; // eax
  int n; // eax

  p_ptHashCubeData = &QCube_atCubeHash[0].ptHashCubeData;
  do
  {
    *(p_ptHashCubeData - 2) = (void *)-1;
    *p_ptHashCubeData = nullptr;
    p_ptHashCubeData += 7;
  }
  while ( (int)p_ptHashCubeData < 139693560 );
  v3 = zFile;
  v4 = igi2_frame.zTempFileName - zFile;
  igi2_frame.v55 = igi2_frame.zTempFileName - zFile;
  do
  {
    v5 = *v3;
    v3[v4] = *v3;
    ++v3;
  }
  while ( v5 );
  v6 = (char *)&igi2_frame.v55 + 3;
  while ( *++v6 )
    ;
  strcpy(v6, ".bit");
  v8 = (struct Terrain_MaterialBitmap_t *)Resource_Load(igi2_frame.zTempFileName, (unsigned int *)&igi2_frame.nCubeTreeSize);
  ptWorld->ptMaterialBitmap = v8;
  v9 = v8 + 256;
  if ( (unsigned int)igi2_frame.nCubeTreeSize >= 0xC00 )
  {
    v11 = 0;
    for ( i = 0; i < 256; ++i )
    {
      World_aisMaterialBitmapResource[v11] = 1;
      ptMaterialBitmap = ptWorld->ptMaterialBitmap;
      nSize = ptMaterialBitmap[i].nSize;
      v15 = &ptMaterialBitmap[i];
      igi2_frame.nCubeTreeSize = nSize;
      if ( nSize )
      {
        v15->ptBitmap = (unsigned __int8 *)v9;
        v9 = (struct Terrain_MaterialBitmap_t *)((char *)v9 + nSize * nSize / 8);
      }
      ptWorld->ptMaterialBitmap[i].isEdit = 0;
      ++v11;
    }
  }
  else
  {
    v10 = (struct Terrain_MaterialBitmap_t *)Mem_AllocFn(3072, 4);
    ptWorld->ptMaterialBitmap = v10;
    memset(v10, 0, 0xC00u);
    memset(World_aisMaterialBitmapResource, 0, sizeof(World_aisMaterialBitmapResource));
  }
  v16 = zFile;
  do
  {
    v17 = *v16;
    v16[v4] = *v16;
    ++v16;
  }
  while ( v17 );
  v18 = (char *)&igi2_frame.v55 + 3;
  while ( *++v18 )
    ;
  strcpy(v18, ".hmp");
  if ( Resource_IsLoadedInternal(igi2_frame.zTempFileName, nullptr) == false )
  {
    v20 = File_New(igi2_frame.zTempFileName, "r");
    if ( !v20 )
    {
      ptWorld->ptHeightBitmap = nullptr;
      goto LABEL_30;
    }
    if ( v20 == &File_tDummyAsyncFile )
      File_tDummyAsyncFile.isAsync = false;
    else
      File_atDevice[v20->eDeviceID].pfDelete(v20->eDeviceID, v20);
  }
  v21 = (struct Terrain_HeightBitmap_t *)Resource_Load(igi2_frame.zTempFileName, (unsigned int *)&igi2_frame.nCubeTreeSize);
  ptWorld->ptHeightBitmap = v21;
  v22 = v21 + 256;
  if ( (unsigned int)igi2_frame.nCubeTreeSize >= 0xC00 )
  {
    v24 = 0;
    for ( j = 0; j < 256; ++j )
    {
      World_aisHeightBitmapResource[v24] = 1;
      ptHeightBitmap = ptWorld->ptHeightBitmap;
      v27 = ptHeightBitmap[j].nSize;
      v28 = &ptHeightBitmap[j];
      if ( v27 )
      {
        v28->ptBitmap = (unsigned __int8 *)v22;
        v22 = (struct Terrain_HeightBitmap_t *)((char *)v22 + (v27 + 1) * (v27 + 1));
      }
      ptWorld->ptHeightBitmap[j].isEdit = 0;
      ++v24;
    }
  }
  else
  {
    v23 = (struct Terrain_HeightBitmap_t *)Mem_AllocFn(3072, 4);
    ptWorld->ptHeightBitmap = v23;
    memset(v23, 0, 0xC00u);
    memset(World_aisHeightBitmapResource, 0, sizeof(World_aisHeightBitmapResource));
  }
LABEL_30:
  v29 = zFile;
  do
  {
    v30 = *v29;
    v29[igi2_frame.v55] = *v29;
    ++v29;
  }
  while ( v30 );
  v31 = (char *)&igi2_frame.v55 + 3;
  while ( *++v31 )
    ;
  strcpy(v31, ".cmd");
  if ( Resource_IsLoadedInternal(igi2_frame.zTempFileName, (struct Resource_s **)&igi2_frame.nCubeTreeSize) )
  {
    v34 = igi2_frame.nCubeTreeSize;
    *(_DWORD *)(igi2_frame.nCubeTreeSize + 44) = 1;
    v35 = *(void **)(v34 + 52);
  }
  else
  {
    Game_MPRunNetwork(v33);
    v36 = File_Load(igi2_frame.zTempFileName, (unsigned int *)&igi2_frame.nCubeTreeSize);
    if ( !v36 )
    {
      LDebug_Error("Failed to load resource: '%s'", igi2_frame.zTempFileName);
      abort();
    }
    v35 = Resource_ParseFile(File_zLastSubstitutedPath, v36, igi2_frame.nCubeTreeSize);
  }
  ptWorld->pxCubeMeshData = v35;
  v37 = zFile;
  do
  {
    v38 = *v37;
    v37[igi2_frame.v55] = *v37;
    ++v37;
  }
  while ( v38 );
  v39 = (char *)&igi2_frame.v55 + 3;
  while ( *++v39 )
    ;
  strcpy(v39, ".ctr");
  ptWorld->ptCubeTree = (struct CubeTree_s *)Resource_Load(igi2_frame.zTempFileName, (unsigned int *)&igi2_frame.nCubeTreeSize);
  v41 = zFile;
  do
  {
    v42 = *v41;
    v41[igi2_frame.v55] = *v41;
    ++v41;
  }
  while ( v42 );
  v43 = (char *)&igi2_frame.v55 + 3;
  while ( *++v43 )
    ;
  strcpy(v43, ".qsc");
  Symbol_Register(
    stru_6A4CDC.zName,
    World_CreateTerrainMaterial,
    nullptr,
    226,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&stru_6A4CDC.pxPrintCallbackContext,
    World_CreateTerrainTileMap,
    nullptr,
    65,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  v45 = Script_New(igi2_frame.zTempFileName);
  Script_Execute(v45);
  Script_Delete(v45);
  Symbol_Remove(stru_6A4CDC.zName);
  Symbol_Remove((char *)&stru_6A4CDC.pxPrintCallbackContext);
  v46 = (unsigned int)igi2_frame.nCubeTreeSize >> 5;
  if ( (unsigned int)igi2_frame.nCubeTreeSize >> 5 )
  {
    v47 = 0;
    do
    {
      ptCubeTree = ptWorld->ptCubeTree;
      ptMesh = ptCubeTree[v47].ptMesh;
      p_ptMesh = &ptCubeTree[v47++].ptMesh;
      --v46;
      *p_ptMesh = (struct CubeItem0_MeshHeader_s *)((char *)ptWorld->pxCubeMeshData + (unsigned int)ptMesh);
    }
    while ( v46 );
  }
  ptWorld->ptWaveTable = (struct WaterWave_t *)Mem_AllocFn(4096, 4);
  ptWorld->pnWaveIndex = (unsigned __int8 *)Mem_AllocFn(0x10000, 4);
  for ( k = 0; k < 0x10000; k += 256 )
  {
    for ( m = 0; m < 256; ++m )
      ptWorld->pnWaveIndex[k + m] = 0;
  }
  for ( n = 0; n < 256; ++n )
    ptWorld->ptWaveTable[n].vZOffset = 0.0;
  ptWorld->isLightingTablesValid = 0;
}

// source: e/1/world.c:2285  [anchor-mhash]
unsigned int __cdecl World_FindSize(int nX0, int nY0, int nZ0, int nX1, int nY1, int nZ1)
{
  unsigned int v6; // eax
  unsigned int result; // eax

  v6 = nZ1 ^ nZ0 | nY1 ^ nY0 | nX1 ^ nX0;
  if ( !v6 )
    return 0x2000;
  _BitScanReverse(&v6, v6);
  result = 1 << v6;
  if ( result < 0x2000 )
    return 0x2000;
  if ( result > 0x40000000 )
    return 0x40000000;
  return result;
}

// source: e/1/world.c:2332  [anchor-mhash]
struct DynCubeObj_s *__cdecl World_RemoveManualObj(
        struct World_s *ptWorld,
        struct DynCubeObj_s *ptDynCubeObj,
        int iList)
{
  struct DynCubeObj_s *ptPrev; // ecx
  struct DynCubeObj_s *ptNext; // ecx

  ptPrev = ptDynCubeObj->ptPrev;
  if ( ptPrev )
    ptPrev->ptNext = ptDynCubeObj->ptNext;
  else
    ptWorld->ptManualRedrawList = ptDynCubeObj->ptNext;
  ptNext = ptDynCubeObj->ptNext;
  if ( ptNext )
  {
    ptDynCubeObj = ptDynCubeObj->ptPrev;
    ptNext->ptPrev = ptDynCubeObj;
  }
  return ptDynCubeObj;
}

// source: e/1/world.c:2369  [anchor-mhash]
struct World_s *__cdecl World_RegisterManualObj(
        struct World_s *ptWorld,
        struct DynCubeObj_s *ptDynCubeObj,
        int iList)
{
  struct DynCubeObj_s *ptManualRedrawList; // ecx
  struct DynCubeObj_s *ptPrev; // ecx

  ptManualRedrawList = ptWorld->ptManualRedrawList;
  if ( ptManualRedrawList )
  {
    ptManualRedrawList->ptPrev = ptDynCubeObj;
    ptWorld->ptManualRedrawList->ptPrev->ptNext = ptWorld->ptManualRedrawList;
    ptPrev = ptWorld->ptManualRedrawList->ptPrev;
    ptWorld->ptManualRedrawList = ptPrev;
    ptPrev->ptPrev = nullptr;
  }
  else
  {
    ptWorld->ptManualRedrawList = ptDynCubeObj;
    ptDynCubeObj->ptNext = nullptr;
    ptWorld->ptManualRedrawList->ptPrev = nullptr;
  }
  return ptWorld;
}

// source: e/1/world.c:2406  [anchor-callee]
void __cdecl World_MoveDynCubeObjRadius(
        struct World_s *ptWorld,
        struct DynCubeObj_s *ptDynCubeObj,
        struct real64x3_t *ptNewPos,
        float vRadius)
{
  #pragma pack(push, 1)
  union
  {
    struct { unsigned int v26; };
    struct { unsigned int v27; };
    struct { char igi2_o2[4]; unsigned int v29; };
    struct { char igi2_o3[4]; __int64 vX; };
    struct { char igi2_o4[16]; unsigned int nCurrentSize; };
    struct { char igi2_o5[20]; unsigned int nTopSize[3]; };
    struct { char igi2_o6[32]; unsigned int nObjSize; };
    struct { char igi2_o7[36]; int nX; };
    struct { char igi2_o8[40]; int nY; };
    char igi2_extent[44];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  bool v4; // c3
  unsigned int v5; // ebx
  unsigned int v6; // edi
  int v7; // eax
  int v8; // ebx
  int nZ; // edx
  double vY; // st7
  int v11; // edi
  int v12; // edi
  int v13; // edx
  int v14; // eax
  struct DynCubeTreeItem_s *v15; // ebx
  bool v16; // zf
  unsigned int v17; // eax
  unsigned int v18; // eax
  unsigned int v19; // edi
  unsigned int v20; // eax
  unsigned int v21; // eax
  unsigned int v22; // edx
  unsigned int v23; // edi
  struct DynCubeObj_s *ptNext; // eax
  struct DynCubeObj_s *ptPrev; // ecx

  v4 = ptNewPos->vX == ptDynCubeObj->tQObj.tPos.vX;
  igi2_frame.nCurrentSize = (unsigned int)ptDynCubeObj->ptDynCubeObjTreeItem;
  if ( !v4
    || ptNewPos->vY != ptDynCubeObj->tQObj.tPos.vY
    || ptNewPos->vZ != ptDynCubeObj->tQObj.tPos.vZ
    || vRadius != ptDynCubeObj->tQObj.vRealRadius )
  {
    if ( vRadius <= 2147483648.0 )
    {
      *(_QWORD *)igi2_frame.nTopSize = (__int64)vRadius;
      igi2_frame.v26 = igi2_frame.nTopSize[0];
    }
    else
    {
      igi2_frame.v26 = 0x7FFFFFFF;
    }
    *(_QWORD *)igi2_frame.nTopSize = (__int64)ptNewPos->vX;
    v5 = igi2_frame.nTopSize[0];
    *(_QWORD *)igi2_frame.nTopSize = (__int64)ptNewPos->vY;
    v6 = igi2_frame.nTopSize[0];
    *(_QWORD *)igi2_frame.nTopSize = (__int64)ptNewPos->vZ;
    igi2_frame.nY = igi2_frame.nTopSize[0];
    v7 = ptWorld->tOrigo.nX;
    igi2_frame.vX = (__int64)ptDynCubeObj->tQObj.tPos.vX;
    igi2_frame.nObjSize = v7 + v5;
    v8 = ptWorld->tOrigo.nY;
    nZ = ptWorld->tOrigo.nZ;
    igi2_frame.nX = v8 + v6;
    vY = ptDynCubeObj->tQObj.tPos.vY;
    v11 = nZ + igi2_frame.nTopSize[0];
    igi2_frame.nTopSize[0] = nZ;
    igi2_frame.nY = v11;
    v12 = v8 + (__int64)vY;
    v13 = v7 + igi2_frame.vX;
    v14 = igi2_frame.nTopSize[0] + (__int64)ptDynCubeObj->tQObj.tPos.vZ;
    ptDynCubeObj->tQObj.tPos.vX = ptNewPos->vX;
    ptDynCubeObj->tQObj.tPos.vY = ptNewPos->vY;
    LODWORD(ptDynCubeObj->tQObj.tPos.vZ) = LODWORD(ptNewPos->vZ);
    v15 = (struct DynCubeTreeItem_s *)igi2_frame.nCurrentSize;
    v16 = igi2_frame.nCurrentSize == 0;
    HIDWORD(ptDynCubeObj->tQObj.tPos.vZ) = HIDWORD(ptNewPos->vZ);
    ptDynCubeObj->tQObj.vRealRadius = vRadius;
    if ( !v16 )
    {
      igi2_frame.nTopSize[0] = v15->nSize;
      v17 = igi2_frame.nObjSize ^ v13 | igi2_frame.nX ^ v12 | igi2_frame.nY ^ v14;
      if ( v17 )
      {
        _BitScanReverse(&v17, v17);
        v18 = 1 << v17;
        if ( v18 >= 0x2000 )
        {
          igi2_frame.v29 = 0x40000000;
          if ( v18 <= 0x40000000 )
            igi2_frame.v29 = v18;
        }
        else
        {
          igi2_frame.v29 = 0x2000;
        }
      }
      else
      {
        igi2_frame.v29 = 0x2000;
      }
      v19 = (igi2_frame.v26 + igi2_frame.nObjSize) ^ (igi2_frame.nObjSize - igi2_frame.v26);
      if ( v19 | (igi2_frame.v26 + igi2_frame.nX) ^ (igi2_frame.nX - igi2_frame.v26) | (igi2_frame.v26 + igi2_frame.nY) ^ (igi2_frame.nY - igi2_frame.v26) )
      {
        _BitScanReverse(&v20, v19 | (igi2_frame.v26 + igi2_frame.nX) ^ (igi2_frame.nX - igi2_frame.v26) | (igi2_frame.v26 + igi2_frame.nY) ^ (igi2_frame.nY - igi2_frame.v26));
        v21 = 1 << v20;
        if ( v21 >= 0x2000 )
        {
          igi2_frame.v27 = 0x40000000;
          if ( v21 <= 0x40000000 )
            igi2_frame.v27 = v21;
        }
        else
        {
          igi2_frame.v27 = 0x2000;
        }
      }
      else
      {
        igi2_frame.v27 = 0x2000;
      }
      v22 = igi2_frame.v29;
      v23 = igi2_frame.nTopSize[0];
      if ( igi2_frame.v27 <= igi2_frame.v29 )
      {
        if ( igi2_frame.nTopSize[0] == igi2_frame.v29 && igi2_frame.v29 == igi2_frame.v27 )
          return;
      }
      else
      {
        v22 = igi2_frame.v27;
      }
      ptNext = ptDynCubeObj->ptNext;
      if ( ptDynCubeObj == v15->ptDynCubeObj )
      {
        v15->ptDynCubeObj = ptNext;
        if ( ptNext )
          ptNext->ptPrev = nullptr;
      }
      else
      {
        ptPrev = ptDynCubeObj->ptPrev;
        if ( ptNext )
          ptNext->ptPrev = ptPrev;
        if ( ptPrev )
          ptPrev->ptNext = ptNext;
      }
      if ( v23 < v22 )
      {
        DynCube_DelUpTo(ptWorld, v22, v23, (struct DynCubeTreeItem_s **)&igi2_frame.nCurrentSize);
        v15 = (struct DynCubeTreeItem_s *)igi2_frame.nCurrentSize;
      }
      World_RegisterObj(ptWorld, v15, ptDynCubeObj, igi2_frame.v27, igi2_frame.nObjSize, igi2_frame.nX, igi2_frame.nY);
    }
  }
}

// source: e/1/world.c:2536  [anchor-caller]
void __cdecl World_MoveDynCubeObjMinMaxXYZ(
        struct World_s *ptWorld,
        struct DynCubeObj_s *ptDynCubeObj,
        struct real64x3_t *ptNewPos,
        struct real64x3_t *ptXYZMin,
        struct real64x3_t *ptXYZMax)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct DynCubeTreeItem_s *ptTree; };
    struct { char igi2_o1[4]; __int64 nCurrentSize; };
    struct { char igi2_o2[12]; struct int32x3_t tXYZMax; };
    struct { char igi2_o3[24]; struct int32x3_t tXYZMin; };
    struct { char igi2_o4[36]; struct int32x3_t tNewPos; };
    struct { char igi2_o5[48]; struct int32x3_t tOrigo; };
    char igi2_extent[60];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  bool v5; // c3
  int v6; // ebp
  int nX; // edi
  int nY; // eax
  double vX; // st7
  int v10; // edx
  int v11; // ebp
  int nZ; // edi
  int v13; // ebx
  int v14; // ebp
  int v15; // edi
  int v16; // ebp
  int v17; // edi
  int v18; // ebp
  int v19; // edi
  int v20; // ebx
  int v21; // eax
  int v22; // ebp
  int v23; // edi
  int v24; // ebp
  int v25; // edi
  int v26; // ebp
  int v27; // edi
  int v28; // ebp
  int v29; // edi
  double v30; // st7
  int v31; // ebp
  double v32; // st6
  double v33; // st5
  struct DynCubeTreeItem_s *v34; // edi
  int v35; // eax
  int v36; // ebx
  unsigned int v37; // eax
  unsigned int v38; // edx
  unsigned int v39; // eax
  unsigned int v40; // ebp
  unsigned int v41; // ebp
  unsigned int v42; // eax
  unsigned int v43; // eax
  struct DynCubeObj_s *ptNext; // eax
  struct DynCubeObj_s *ptPrev; // ecx

  v5 = ptNewPos->vX == ptDynCubeObj->tQObj.tPos.vX;
  igi2_frame.ptTree = ptDynCubeObj->ptDynCubeObjTreeItem;
  if ( !v5 || ptNewPos->vY != ptDynCubeObj->tQObj.tPos.vY || ptNewPos->vZ != ptDynCubeObj->tQObj.tPos.vZ )
  {
    igi2_frame.nCurrentSize = (__int64)ptNewPos->vX;
    v6 = igi2_frame.nCurrentSize;
    igi2_frame.nCurrentSize = (__int64)ptNewPos->vY;
    igi2_frame.tNewPos.nY = igi2_frame.nCurrentSize;
    igi2_frame.nCurrentSize = (__int64)ptNewPos->vZ;
    igi2_frame.tNewPos.nZ = igi2_frame.nCurrentSize;
    igi2_frame.nCurrentSize = (__int64)ptXYZMin->vX;
    igi2_frame.tXYZMin.nX = igi2_frame.nCurrentSize;
    igi2_frame.nCurrentSize = (__int64)ptXYZMin->vY;
    igi2_frame.tXYZMin.nY = igi2_frame.nCurrentSize;
    igi2_frame.nCurrentSize = (__int64)ptXYZMin->vZ;
    nX = ptWorld->tOrigo.nX;
    igi2_frame.tXYZMin.nZ = igi2_frame.nCurrentSize;
    igi2_frame.tNewPos.nX = nX + v6;
    igi2_frame.nCurrentSize = (__int64)ptXYZMax->vX;
    igi2_frame.tXYZMax.nX = igi2_frame.nCurrentSize;
    igi2_frame.nCurrentSize = (__int64)ptXYZMax->vY;
    igi2_frame.tXYZMax.nY = igi2_frame.nCurrentSize;
    nY = ptWorld->tOrigo.nY;
    igi2_frame.nCurrentSize = (__int64)ptXYZMax->vZ;
    igi2_frame.tXYZMax.nZ = igi2_frame.nCurrentSize;
    vX = ptDynCubeObj->tQObj.tPos.vX;
    igi2_frame.tOrigo.nZ = ptWorld->tOrigo.nZ;
    igi2_frame.nCurrentSize = (__int64)vX;
    v10 = nX + (__int64)vX;
    v11 = ptWorld->tOrigo.nY + igi2_frame.tNewPos.nY;
    igi2_frame.nCurrentSize = (__int64)ptDynCubeObj->tQObj.tPos.vY;
    nZ = ptWorld->tOrigo.nZ;
    v13 = igi2_frame.nCurrentSize;
    igi2_frame.tNewPos.nY = v11;
    v14 = nZ + igi2_frame.tNewPos.nZ;
    igi2_frame.nCurrentSize = (__int64)ptDynCubeObj->tQObj.tPos.vZ;
    v15 = ptWorld->tOrigo.nX;
    igi2_frame.tNewPos.nZ = v14;
    v16 = v15 + igi2_frame.tXYZMin.nX;
    v17 = ptWorld->tOrigo.nY;
    igi2_frame.tXYZMin.nX = v16;
    v18 = v17 + igi2_frame.tXYZMin.nY;
    v19 = ptWorld->tOrigo.nZ;
    v20 = nY + v13;
    v21 = igi2_frame.tOrigo.nZ + igi2_frame.nCurrentSize;
    igi2_frame.tXYZMin.nY = v18;
    v22 = v19 + igi2_frame.tXYZMin.nZ;
    v23 = ptWorld->tOrigo.nX;
    igi2_frame.tXYZMin.nZ = v22;
    v24 = v23 + igi2_frame.tXYZMax.nX;
    v25 = ptWorld->tOrigo.nY;
    igi2_frame.tXYZMax.nX = v24;
    v26 = v25 + igi2_frame.tXYZMax.nY;
    v27 = ptWorld->tOrigo.nZ;
    igi2_frame.tXYZMax.nY = v26;
    v28 = v27 + igi2_frame.tXYZMax.nZ;
    ptDynCubeObj->tQObj.tPos.vX = ptNewPos->vX;
    ptDynCubeObj->tQObj.tPos.vY = ptNewPos->vY;
    LODWORD(ptDynCubeObj->tQObj.tPos.vZ) = LODWORD(ptNewPos->vZ);
    v29 = igi2_frame.tXYZMax.nX;
    HIDWORD(ptDynCubeObj->tQObj.tPos.vZ) = HIDWORD(ptNewPos->vZ);
    --igi2_frame.tXYZMax.nY;
    v30 = ptXYZMax->vX;
    igi2_frame.tXYZMax.nX = v29 - 1;
    v31 = v28 - 1;
    v32 = ptXYZMax->vY - ptXYZMin->vY;
    v33 = ptXYZMax->vZ - ptXYZMin->vZ;
    v34 = igi2_frame.ptTree;
    ptDynCubeObj->tQObj.vRealRadius = sqrt(v33 * v33 + v32 * v32 + (v30 - ptXYZMin->vX) * (v30 - ptXYZMin->vX)) * 0.5;
    LODWORD(igi2_frame.nCurrentSize) = v34->nSize;
    v35 = igi2_frame.tNewPos.nY ^ v20 | igi2_frame.tNewPos.nZ ^ v21;
    v36 = igi2_frame.tNewPos.nX;
    v37 = igi2_frame.tNewPos.nX ^ v10 | v35;
    if ( v37 )
    {
      _BitScanReverse(&v37, v37);
      v39 = 1 << v37;
      if ( v39 >= 0x2000 )
      {
        v38 = 0x40000000;
        if ( v39 <= 0x40000000 )
          v38 = v39;
      }
      else
      {
        v38 = 0x2000;
      }
    }
    else
    {
      v38 = 0x2000;
    }
    v40 = igi2_frame.tXYZMin.nX ^ igi2_frame.tXYZMax.nX | igi2_frame.tXYZMin.nY ^ igi2_frame.tXYZMax.nY | igi2_frame.tXYZMin.nZ ^ v31;
    if ( v40 )
    {
      _BitScanReverse(&v42, v40);
      v43 = 1 << v42;
      if ( v43 >= 0x2000 )
      {
        v41 = 0x40000000;
        if ( v43 <= 0x40000000 )
          v41 = v43;
      }
      else
      {
        v41 = 0x2000;
      }
    }
    else
    {
      v41 = 0x2000;
    }
    if ( v41 <= v38 )
    {
      if ( (_DWORD)igi2_frame.nCurrentSize == v38 && v38 == v41 )
        return;
    }
    else
    {
      v38 = v41;
    }
    ptNext = ptDynCubeObj->ptNext;
    if ( ptDynCubeObj == v34->ptDynCubeObj )
    {
      v34->ptDynCubeObj = ptNext;
      if ( ptNext )
        ptNext->ptPrev = nullptr;
    }
    else
    {
      ptPrev = ptDynCubeObj->ptPrev;
      if ( ptNext )
        ptNext->ptPrev = ptPrev;
      if ( ptPrev )
        ptPrev->ptNext = ptNext;
    }
    if ( (unsigned int)igi2_frame.nCurrentSize < v38 )
    {
      DynCube_DelUpTo(ptWorld, v38, igi2_frame.nCurrentSize, &igi2_frame.ptTree);
      v34 = igi2_frame.ptTree;
    }
    World_RegisterObj(ptWorld, v34, ptDynCubeObj, v41, v36, igi2_frame.tNewPos.nY, igi2_frame.tNewPos.nZ);
  }
}

// source: e/1/world.c:2674  [anchor-callee]
void __cdecl World_RegisterDynCubeObjFirstTimeRadius(
        struct World_s *ptWorld,
        struct DynCubeObj_s *ptDynCubeObj,
        struct real64x3_t *ptPos,
        float vRadius,
        enum DynCubeTreeCategory_enum eDynCubeTreeCategory)
{
  int v5; // edi
  int v6; // ebx
  int v7; // ecx
  unsigned int v8; // eax
  unsigned int v9; // eax
  struct DynCubeTreeItem_s *ptDynCubeObjTreeItem; // [esp+10h] [ebp-10h]
  unsigned int nObjSize; // [esp+14h] [ebp-Ch]
  int nX; // [esp+18h] [ebp-8h]
  int nY; // [esp+1Ch] [ebp-4h]

  ptDynCubeObjTreeItem = ptWorld->aptDynCubeTree[0];
  if ( !ptDynCubeObj->ptDynCubeObjTreeItem )
  {
    nObjSize = ptWorld->tOrigo.nX + (__int64)ptPos->vX;
    nX = ptWorld->tOrigo.nY + (__int64)ptPos->vY;
    nY = ptWorld->tOrigo.nZ + (__int64)ptPos->vZ;
    if ( vRadius <= 2147483648.0 )
      v7 = (__int64)vRadius;
    else
      v7 = 0x7FFFFFFF;
    v6 = ptWorld->tOrigo.nZ + (__int64)ptPos->vZ;
    v5 = ptWorld->tOrigo.nY + (__int64)ptPos->vY;
    v8 = (nObjSize + v7) ^ (nObjSize - v7) | (v7 + v5) ^ (v5 - v7) | (v7 + v6) ^ (v6 - v7);
    if ( v8 && (_BitScanReverse(&v8, v8), v9 = 1 << v8, v9 >= 0x2000) )
    {
      if ( v9 > 0x40000000 )
        v9 = 0x40000000;
    }
    else
    {
      v9 = 0x2000;
    }
    ptDynCubeObj->tQObj.tPos = *ptPos;
    ptDynCubeObj->tQObj.vRealRadius = vRadius;
    ptDynCubeObj->iSector = 0;
    World_RegisterObj(ptWorld, ptDynCubeObjTreeItem, ptDynCubeObj, v9, nObjSize, nX, nY);
  }
}

// source: e/1/world.c:2745  [anchor-caller]
struct real64x3_t *__cdecl World_RegisterDynCubeObjFirstTimeMinMaxXYZ(
        struct World_s *ptWorld,
        struct DynCubeObj_s *ptDynCubeObj,
        struct real64x3_t *ptPos,
        struct real64x3_t *ptMin,
        struct real64x3_t *ptMax,
        enum DynCubeTreeCategory_enum eDynCubeTreeCategory)
{
  int nZ; // ebx
  int v7; // esi
  int v8; // edi
  int v9; // ecx
  unsigned int v10; // ecx
  unsigned int v11; // eax
  unsigned int v12; // eax
  struct DynCubeTreeItem_s *ptDynCubeObjTreeItem; // [esp+14h] [ebp-24h]
  int tXYZMin; // [esp+20h] [ebp-18h]
  int tXYZMin_4; // [esp+24h] [ebp-14h]
  int tXYZMin_8; // [esp+28h] [ebp-10h]
  int tPos; // [esp+2Ch] [ebp-Ch]
  int tPos_4; // [esp+30h] [ebp-8h]
  int tPos_8; // [esp+34h] [ebp-4h]

  ptDynCubeObjTreeItem = ptWorld->aptDynCubeTree[0];
  if ( !ptDynCubeObj->ptDynCubeObjTreeItem )
  {
    tPos = ptWorld->tOrigo.nX + (__int64)ptPos->vX;
    tPos_4 = ptWorld->tOrigo.nY + (__int64)ptPos->vY;
    tPos_8 = ptWorld->tOrigo.nZ + (__int64)ptPos->vZ;
    tXYZMin = ptWorld->tOrigo.nX + (__int64)ptMin->vX;
    nZ = ptWorld->tOrigo.nZ;
    tXYZMin_4 = ptWorld->tOrigo.nY + (__int64)ptMin->vY;
    tXYZMin_8 = nZ + (__int64)ptMin->vZ;
    v7 = ptWorld->tOrigo.nX + (__int64)ptMax->vX;
    v8 = ptWorld->tOrigo.nY + (__int64)ptMax->vY;
    v9 = nZ + (__int64)ptMax->vZ;
    ptDynCubeObj->tQObj.tPos = *ptPos;
    v10 = tXYZMin ^ (v7 - 1) | tXYZMin_4 ^ (v8 - 1) | tXYZMin_8 ^ (v9 - 1);
    ptDynCubeObj->tQObj.vRealRadius = sqrt(0.0) * 0.5;
    ptDynCubeObj->iSector = 0;
    if ( v10 && (_BitScanReverse(&v11, v10), v12 = 1 << v11, v12 >= 0x2000) )
    {
      if ( v12 > 0x40000000 )
        v12 = 0x40000000;
    }
    else
    {
      v12 = 0x2000;
    }
    return (struct real64x3_t *)World_RegisterObj(
                                  ptWorld,
                                  ptDynCubeObjTreeItem,
                                  ptDynCubeObj,
                                  v12,
                                  tPos,
                                  tPos_4,
                                  tPos_8);
  }
  return ptPos;
}

// source: e/1/world.c:2843  [anchor-hash]
struct World_s *__cdecl World_RemoveDynCubeObj(
        struct World_s *ptWorld,
        struct DynCubeObj_s *ptDynCubeObj)
{
  struct World_s *result; // eax
  struct DynCubeObj_s *ptNext; // ecx
  struct DynCubeObj_s *ptPrev; // edx

  result = (struct World_s *)ptDynCubeObj->ptDynCubeObjTreeItem;
  if ( result )
  {
    ptWorld->aisStartDynCubeValid[result->aisStartDynCubeValid[0]] = 0;
    ptNext = ptDynCubeObj->ptNext;
    if ( ptDynCubeObj == (struct DynCubeObj_s *)HIDWORD(result->atStartDynCubePos[0].vZ) )
    {
      HIDWORD(result->atStartDynCubePos[0].vZ) = ptNext;
      if ( ptNext )
      {
        ptNext->ptPrev = nullptr;
        result = (struct World_s *)DynCube_DelEmptyTreeNodesUpwards(ptWorld, (struct DynCubeTreeItem_s *)result);
        ptDynCubeObj->ptDynCubeObjTreeItem = nullptr;
        return result;
      }
    }
    else
    {
      ptPrev = ptDynCubeObj->ptPrev;
      if ( ptNext )
        ptNext->ptPrev = ptPrev;
      if ( ptPrev )
        ptPrev->ptNext = ptNext;
    }
    result = (struct World_s *)DynCube_DelEmptyTreeNodesUpwards(ptWorld, (struct DynCubeTreeItem_s *)result);
    ptDynCubeObj->ptDynCubeObjTreeItem = nullptr;
  }
  return result;
}

// source: e/1/world.c:2879  [size]
struct DynCubeTreeItem_s *__cdecl World_GetTopOfTree(
        struct World_s *ptWorld,
        enum DynCubeTree_e eDynCubeTree)
{
  return ptWorld->aptDynCubeTree[eDynCubeTree];
}

// source: e/1/world.c:2896  [anchor-mhash]
void __cdecl World_InitDynCubeObj(struct DynCubeObj_s *ptDynCubeObj)
{
  memset(&ptDynCubeObj->tQObj.tPos, 0, 0x48u);
  ptDynCubeObj->iRenderGroup = RenderGroup_Normal;
}

// source: e/1/world.c:2923  [anchor-callee]
struct World_s *__cdecl World_TriggerQTaskEventMinMaxXyzSpecificTree(
        struct World_s *ptWorld,
        __int16 eQTaskEvent,
        void *pxContext,
        struct real64x3_t *ptMin,
        struct real64x3_t *ptMax,
        unsigned int bQTaskGroup,
        enum DynCubeTree_e eDynCubeTree)
{
  #pragma pack(push, 1)
  union
  {
    struct { unsigned int nStackSize; };
    struct { char igi2_o1[8]; unsigned int nLevel; };
    struct { char igi2_o2[12]; unsigned int nRadius; };
    struct { char igi2_o3[16]; int tIntMax; };
    struct { char igi2_o4[20]; int tIntMax_4; };
    struct { char igi2_o5[24]; int tIntMax_8; };
    struct { char igi2_o6[28]; struct CallQueue_t tCallQueue; };
    struct { char igi2_o7[36]; struct int32x3_t tIntMin; };
    struct { char igi2_o8[48]; __int64 v59; };
    struct { char igi2_o9[56]; struct DynCubeTreeItem_s tCopy; };
    struct { char igi2_o10[112]; struct real64x3_t tRealMin; };
    struct { char igi2_o11[136]; struct real64x3_t tRealMax; };
    struct { char igi2_o12[160]; struct WorldTriggerStack_s atTriggerStack[50]; };
    char igi2_extent[1160];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct WorldTriggerStack_s *v8; // ebp
  int nX; // eax
  int nY; // ecx
  int nZ; // edx
  struct DynCubeTreeItem_s *v12; // ecx
  struct DynCubeTreeItem_s *v13; // edi
  struct DynCubeTreeItem_s *v14; // edx
  struct DynCubeTreeItem_s *v15; // eax
  unsigned __int8 bChildren; // cl
  double *v17; // esi
  double v18; // st7
  unsigned __int8 v19; // al
  int v20; // edx
  int v21; // edi
  unsigned __int8 v22; // cl
  char v23; // al
  double vX; // st7
  struct CallQueueItem_s *v25; // edi
  double vY; // st6
  double vZ; // st5
  double v28; // st4
  double v29; // st3
  unsigned __int8 bChildBits; // bl
  struct DynCubeTreeItem_s *ptCube; // eax
  struct DynCubeObj_s *ptDynCubeObj; // ecx
  struct CallQueueItem_s *v33; // eax
  double vRealRadius; // st2
  struct CallQueueItem_s *v35; // eax
  unsigned __int8 nChildToCheck; // dl
  struct DynCubeTreeItem_s *v37; // esi
  unsigned __int8 v38; // al
  unsigned __int8 v39; // al
  struct WorldTriggerStack_s *v40; // ebx
  unsigned __int8 v41; // al
  unsigned __int8 v42; // al
  unsigned __int8 v43; // al
  int v44; // esi
  int v45; // ecx
  int v46; // edx
  int v47; // esi
  unsigned __int8 v48; // al
  int v49; // eax
  struct World_s *result; // eax

  qmemcpy(&igi2_frame.tRealMin, ptMin, sizeof(igi2_frame.tRealMin));
  qmemcpy(&igi2_frame.tRealMax, ptMax, sizeof(igi2_frame.tRealMax));
  igi2_frame.tCallQueue.pptLast = (struct CallQueueItem_s **)&igi2_frame.tCallQueue;
  v8 = igi2_frame.atTriggerStack;
  igi2_frame.tCallQueue.ptFirst = nullptr;
  nX = ptWorld->tOrigo.nX;
  igi2_frame.tIntMin.nX = nX + (__int64)igi2_frame.tRealMin.vX;
  nY = ptWorld->tOrigo.nY;
  igi2_frame.tIntMin.nY = nY + (__int64)igi2_frame.tRealMin.vY;
  nZ = ptWorld->tOrigo.nZ;
  igi2_frame.tIntMin.nZ = nZ + (__int64)igi2_frame.tRealMin.vZ;
  igi2_frame.tIntMax_4 = nY + (__int64)igi2_frame.tRealMax.vY;
  igi2_frame.tIntMax = nX + (__int64)igi2_frame.tRealMax.vX;
  igi2_frame.tIntMax_8 = nZ + (__int64)igi2_frame.tRealMax.vZ;
  World_UpdateStartDynCube(ptWorld, eDynCubeTree);
  qmemcpy(&igi2_frame.tCopy, ptWorld->aptStartDynCube[eDynCubeTree], sizeof(igi2_frame.tCopy));
  igi2_frame.nLevel = ptWorld->anStartDynCubeLevel[eDynCubeTree];
  igi2_frame.nRadius = igi2_frame.tCopy.nSize;
  if ( igi2_frame.nLevel == 30 )
  {
    v12 = igi2_frame.tCopy.aptChild[0];
    v13 = igi2_frame.tCopy.aptChild[6];
    igi2_frame.tCopy.aptChild[0] = igi2_frame.tCopy.aptChild[7];
    igi2_frame.tCopy.aptChild[7] = v12;
    igi2_frame.tCopy.aptChild[6] = igi2_frame.tCopy.aptChild[1];
    v14 = igi2_frame.tCopy.aptChild[5];
    igi2_frame.tCopy.aptChild[5] = igi2_frame.tCopy.aptChild[2];
    igi2_frame.tCopy.aptChild[2] = v14;
    igi2_frame.tCopy.aptChild[1] = v13;
    v15 = igi2_frame.tCopy.aptChild[3];
    igi2_frame.tCopy.aptChild[3] = igi2_frame.tCopy.aptChild[4];
    igi2_frame.tCopy.aptChild[4] = v15;
    bChildren = (8 * (((int)igi2_frame.tCopy.bChildren >> 4) & 1 | (2 * (((int)igi2_frame.tCopy.bChildren >> 3) & 1))))
              | (4 * (((int)igi2_frame.tCopy.bChildren >> 5) & 1 | (8 * (((int)igi2_frame.tCopy.bChildren >> 2) & 1))))
              | (2 * (((int)igi2_frame.tCopy.bChildren >> 6) & 1 | (32 * (((int)igi2_frame.tCopy.bChildren >> 1) & 1))))
              | (igi2_frame.tCopy.bChildren << 7)
              | ((int)igi2_frame.tCopy.bChildren >> 7) & 1;
    igi2_frame.tCopy.bChildren = bChildren;
  }
  else
  {
    bChildren = igi2_frame.tCopy.bChildren;
  }
  v17 = (double *)((char *)ptWorld + 24 * eDynCubeTree);
  v18 = (double)ptWorld->tOrigo.nX + v17[3];
  igi2_frame.atTriggerStack[0].ptCube = &igi2_frame.tCopy;
  v19 = bChildren;
  igi2_frame.nStackSize = 1;
  igi2_frame.v59 = (__int64)v18;
  igi2_frame.atTriggerStack[0].bChildBits = bChildren;
  v20 = (__int64)v18;
  igi2_frame.atTriggerStack[0].isInside = 0;
  igi2_frame.atTriggerStack[0].tCenter.nX = v20;
  igi2_frame.v59 = (__int64)((double)ptWorld->tOrigo.nY + v17[4]);
  v21 = igi2_frame.v59;
  igi2_frame.atTriggerStack[0].tCenter.nY = igi2_frame.v59;
  igi2_frame.v59 = (__int64)((double)ptWorld->tOrigo.nZ + v17[5]);
  igi2_frame.atTriggerStack[0].tCenter.nZ = igi2_frame.v59;
  if ( igi2_frame.tIntMax > v20 )
  {
    if ( igi2_frame.tIntMin.nX < v20 )
      goto LABEL_9;
    v22 = bChildren & 0xAA;
  }
  else
  {
    v22 = bChildren & 0x55;
  }
  v19 = v22;
  igi2_frame.atTriggerStack[0].bChildBits = v22;
LABEL_9:
  if ( igi2_frame.tIntMax_4 > v21 )
  {
    if ( igi2_frame.tIntMin.nY < v21 )
      goto LABEL_14;
    v19 &= 0xCCu;
  }
  else
  {
    v19 &= 0x33u;
  }
  igi2_frame.atTriggerStack[0].bChildBits = v19;
LABEL_14:
  if ( igi2_frame.tIntMax_8 <= (int)igi2_frame.v59 )
  {
    v19 &= 0xFu;
LABEL_18:
    igi2_frame.atTriggerStack[0].bChildBits = v19;
    goto LABEL_19;
  }
  if ( igi2_frame.tIntMin.nZ >= (int)igi2_frame.v59 )
  {
    v19 &= 0xF0u;
    goto LABEL_18;
  }
LABEL_19:
  if ( (v19 & 0xF) != 0 )
  {
    if ( (v19 & 3) != 0 )
      v23 = v19 & 1;
    else
      v23 = ((v19 & 4) != 0) + 2;
  }
  else if ( (v19 & 0x30) != 0 )
  {
    v23 = ((v19 & 0x10) != 0) + 4;
  }
  else
  {
    v23 = ((v19 & 0x40) != 0) + 6;
  }
  vX = igi2_frame.tRealMin.vX;
  v25 = CallQueue_ptFirstFreeItem;
  vY = igi2_frame.tRealMin.vY;
  vZ = igi2_frame.tRealMin.vZ;
  igi2_frame.atTriggerStack[0].nChildToCheck = v23 ^ 1;
  v28 = igi2_frame.tRealMax.vX;
  v29 = igi2_frame.tRealMax.vY;
  do
  {
    bChildBits = v8->bChildBits;
    ptCube = v8->ptCube;
    if ( !bChildBits )
    {
      ptDynCubeObj = ptCube->ptDynCubeObj;
      if ( v8->isInside )
      {
        if ( ptDynCubeObj )
        {
          do
          {
            if ( (bQTaskGroup & QTask_atQTaskType[ptDynCubeObj->tQObj.tQTask.eQTaskType].bQTaskGroup) != 0 )
            {
              v33 = v25;
              v25 = v25->ptNext;
              v33->uEvent.eQTaskEvent = eQTaskEvent;
              v33->ptQTask = &ptDynCubeObj->tQObj.tQTask;
              v33->isNoContext = false;
              v33->pxContext = pxContext;
              v33->ptNext = nullptr;
              *igi2_frame.tCallQueue.pptLast = v33;
              igi2_frame.tCallQueue.pptLast = &v33->ptNext;
            }
            ptDynCubeObj = ptDynCubeObj->ptNext;
          }
          while ( ptDynCubeObj );
LABEL_44:
          CallQueue_ptFirstFreeItem = v25;
        }
      }
      else if ( ptDynCubeObj )
      {
        do
        {
          vRealRadius = ptDynCubeObj->tQObj.vRealRadius;
          if ( v28 >= ptDynCubeObj->tQObj.tPos.vX - vRealRadius
            && vX <= vRealRadius + ptDynCubeObj->tQObj.tPos.vX
            && v29 >= ptDynCubeObj->tQObj.tPos.vY - vRealRadius
            && vY <= vRealRadius + ptDynCubeObj->tQObj.tPos.vY
            && ptDynCubeObj->tQObj.tPos.vZ - vRealRadius <= igi2_frame.tRealMax.vZ
            && vZ <= vRealRadius + ptDynCubeObj->tQObj.tPos.vZ
            && (bQTaskGroup & QTask_atQTaskType[ptDynCubeObj->tQObj.tQTask.eQTaskType].bQTaskGroup) != 0 )
          {
            v35 = v25;
            v25 = v25->ptNext;
            v35->uEvent.eQTaskEvent = eQTaskEvent;
            v35->ptQTask = &ptDynCubeObj->tQObj.tQTask;
            v35->isNoContext = false;
            v35->pxContext = pxContext;
            v35->ptNext = nullptr;
            *igi2_frame.tCallQueue.pptLast = v35;
            igi2_frame.tCallQueue.pptLast = &v35->ptNext;
          }
          ptDynCubeObj = ptDynCubeObj->ptNext;
        }
        while ( ptDynCubeObj );
        goto LABEL_44;
      }
      --v8;
      ++igi2_frame.nLevel;
      igi2_frame.nRadius *= 2;
      --igi2_frame.nStackSize;
      continue;
    }
    nChildToCheck = v8->nChildToCheck;
    v37 = ptCube->aptChild[nChildToCheck];
    v38 = bChildBits ^ (1 << nChildToCheck);
    v8->bChildBits = v38;
    if ( v38 )
    {
      if ( (v38 & 0xF) != 0 )
      {
        if ( (v38 & 3) != 0 )
          v39 = v38 & 1;
        else
          v39 = ((v38 & 4) != 0) + 2;
      }
      else if ( (v38 & 0x30) != 0 )
      {
        v39 = ((v38 & 0x10) != 0) + 4;
      }
      else
      {
        v39 = ((v38 & 0x40) != 0) + 6;
      }
      v8->nChildToCheck = v39;
      v8->nChildToCheck = v39 ^ 1;
    }
    --igi2_frame.nLevel;
    v40 = v8++;
    igi2_frame.nRadius >>= 1;
    v41 = v37->bChildren;
    ++igi2_frame.nStackSize;
    v8->ptCube = v37;
    v8->bChildBits = v41;
    if ( v40->isInside )
    {
      v8->isInside = 1;
      if ( v41 )
      {
        if ( (v41 & 0xF) != 0 )
        {
          if ( (v41 & 3) != 0 )
            v42 = v41 & 1;
          else
            v42 = ((v41 & 4) != 0) + 2;
          v8->nChildToCheck = v42;
          v8->nChildToCheck = v42 ^ 1;
        }
        else
        {
          if ( (v41 & 0x30) != 0 )
            v43 = ((v41 & 0x10) != 0) + 4;
          else
            v43 = ((v41 & 0x40) != 0) + 6;
          v8->nChildToCheck = v43;
          v8->nChildToCheck = v43 ^ 1;
        }
      }
    }
    else
    {
      v8->isInside = 0;
      if ( v41 )
      {
        v44 = nChildToCheck;
        v8->tCenter.nX = v40->tCenter.nX + (World_atSubCubePos[v44].nX << igi2_frame.nLevel);
        v8->tCenter.nY = v40->tCenter.nY + (World_atSubCubePos[v44].nY << igi2_frame.nLevel);
        v45 = (World_atSubCubePos[v44].nZ << igi2_frame.nLevel) + v40->tCenter.nZ;
        v46 = v8->tCenter.nX;
        v8->tCenter.nZ = v45;
        if ( igi2_frame.tIntMax > v46 )
        {
          if ( igi2_frame.tIntMin.nX >= v46 )
            v41 &= 0xAAu;
        }
        else
        {
          v41 &= 0x55u;
        }
        v47 = v8->tCenter.nY;
        if ( igi2_frame.tIntMax_4 > v47 )
        {
          if ( igi2_frame.tIntMin.nY >= v47 )
            v41 &= 0xCCu;
        }
        else
        {
          v41 &= 0x33u;
        }
        if ( igi2_frame.tIntMax_8 > v45 )
        {
          if ( igi2_frame.tIntMin.nZ >= v45 )
            v41 &= 0xF0u;
        }
        else
        {
          v41 &= 0xFu;
        }
        v8->bChildBits = v41;
        if ( v41 )
        {
          if ( (v41 & 0xF) != 0 )
          {
            if ( (v41 & 3) != 0 )
              v48 = v41 & 1;
            else
              v48 = ((v41 & 4) != 0) + 2;
          }
          else if ( (v41 & 0x30) != 0 )
          {
            v48 = ((v41 & 0x10) != 0) + 4;
          }
          else
          {
            v48 = ((v41 & 0x40) != 0) + 6;
          }
          v8->nChildToCheck = v48;
          v8->nChildToCheck = v48 ^ 1;
        }
        if ( igi2_frame.tIntMax >= (int)(v46 + igi2_frame.nRadius)
          && igi2_frame.tIntMin.nX <= (int)(v46 - igi2_frame.nRadius)
          && igi2_frame.tIntMax_4 >= (int)(v47 + igi2_frame.nRadius)
          && igi2_frame.tIntMin.nY <= (int)(v47 - igi2_frame.nRadius) )
        {
          v49 = v8->tCenter.nZ;
          if ( igi2_frame.tIntMax_8 >= (int)(v49 + igi2_frame.nRadius) && igi2_frame.tIntMin.nZ <= (int)(v49 - igi2_frame.nRadius) )
            v8->isInside = 1;
        }
        v25 = CallQueue_ptFirstFreeItem;
      }
    }
  }
  while ( igi2_frame.nStackSize );
  CallQueue_CallHandlers(&igi2_frame.tCallQueue);
  return result;
}

// source: e/1/world.c:3300  [anchor-mhash]
unsigned int __cdecl World_TriggerQTaskEventMinMaxXyz(
        struct World_s *ptWorld,
        __int16 eQTaskEvent,
        void *pxContext,
        struct real64x3_t *ptMin,
        struct real64x3_t *ptMax,
        unsigned int bQTaskGroup)
{
  return (unsigned int)World_TriggerQTaskEventMinMaxXyzSpecificTree(
                         ptWorld,
                         eQTaskEvent,
                         pxContext,
                         ptMin,
                         ptMax,
                         bQTaskGroup,
                         WORLD_DYNCUBETREE_STATIONARY);
}

// source: e/1/world.c:3342  [anchor-callee]
void __cdecl World_TriggerQTaskEventAlongLineSpecificTree(
        struct World_s *ptWorld,
        __int16 eQTaskEvent,
        void *pxContext,
        struct real64x3_t *ptStart,
        struct real64x3_t *ptEnd,
        int nNumLines,
        unsigned int bQTaskGroup,
        enum DynCubeTree_e eDynCubeTree)
{
  #pragma pack(push, 1)
  union
  {
    struct { unsigned __int8 nChildToCheck; };
    struct { char igi2_o1[1]; unsigned __int8 bChildBits; };
    struct { char igi2_o2[2]; float v104; };
    struct { char igi2_o3[2]; float v105; };
    struct { char igi2_o4[2]; float v106; };
    struct { char igi2_o5[2]; float v107; };
    struct { char igi2_o6[2]; int v108; };
    struct { char igi2_o7[2]; float v109; };
    struct { char igi2_o8[2]; float v110; };
    struct { char igi2_o9[2]; float v111; };
    struct { char igi2_o10[2]; float v112; };
    struct { char igi2_o11[2]; float v113; };
    struct { char igi2_o12[6]; int tIntMax; };
    struct { char igi2_o13[6]; float tIntMaxa; };
    struct { char igi2_o14[6]; float tIntMaxb; };
    struct { char igi2_o15[6]; float tIntMaxc; };
    struct { char igi2_o16[6]; float tIntMaxd; };
    struct { char igi2_o17[6]; float tIntMaxe; };
    struct { char igi2_o18[10]; int tIntMax_4; };
    struct { char igi2_o19[10]; float tIntMax_4a; };
    struct { char igi2_o20[10]; float tIntMax_4b; };
    struct { char igi2_o21[10]; float tIntMax_4c; };
    struct { char igi2_o22[10]; float tIntMax_4d; };
    struct { char igi2_o23[10]; float tIntMax_4e; };
    struct { char igi2_o24[14]; int tIntMax_8; };
    struct { char igi2_o25[14]; float tIntMax_8a; };
    struct { char igi2_o26[14]; float tIntMax_8b; };
    struct { char igi2_o27[14]; float tIntMax_8c; };
    struct { char igi2_o28[14]; float tIntMax_8d; };
    struct { char igi2_o29[14]; float tIntMax_8e; };
    struct { char igi2_o30[18]; double v132; };
    struct { char igi2_o31[18]; __int64 v133; };
    struct { char igi2_o32[18]; float v134; };
    struct { char igi2_o33[30]; float v135; };
    struct { char igi2_o34[30]; float v136; };
    struct { char igi2_o35[30]; float v137; };
    struct { char igi2_o36[30]; float v138; };
    struct { char igi2_o37[30]; float v139; };
    struct { char igi2_o38[34]; float vSphereRadius; };
    struct { char igi2_o39[38]; struct WorldTriggerStack_s *ptTop; };
    struct { char igi2_o40[42]; int v142; };
    struct { char igi2_o41[42]; float v143; };
    struct { char igi2_o42[46]; float v144; };
    struct { char igi2_o43[46]; float v145; };
    struct { char igi2_o44[46]; float v146; };
    struct { char igi2_o45[46]; float v147; };
    struct { char igi2_o46[50]; float v148; };
    struct { char igi2_o47[50]; int v149; };
    struct { char igi2_o48[54]; unsigned int nStackSize; };
    struct { char igi2_o49[58]; int isTouchingLine; };
    struct { char igi2_o50[62]; int iChild; };
    struct { char igi2_o51[66]; unsigned int nRadius; };
    struct { char igi2_o52[74]; float vCubeRadius; };
    struct { char igi2_o53[78]; unsigned int nLevel; };
    struct { char igi2_o54[82]; double tIntMin; };
    struct { char igi2_o55[86]; int tIntMin_4; };
    struct { char igi2_o56[90]; int tIntMin_8; };
    struct { char igi2_o57[98]; struct CallQueue_t tCallQueue; };
    struct { char igi2_o58[106]; double v160; };
    struct { char igi2_o59[114]; double v161; };
    struct { char igi2_o60[122]; struct real64x3_t tRealMin; };
    struct { char igi2_o61[146]; double v163; };
    struct { char igi2_o62[154]; struct real64x3_t tRealMax; };
    struct { char igi2_o63[178]; int v165; };
    struct { char igi2_o64[182]; int v166; };
    struct { char igi2_o65[186]; int v167; };
    struct { char igi2_o66[190]; int v168; };
    struct { char igi2_o67[194]; int v169; };
    struct { char igi2_o68[198]; int v170; };
    struct { char igi2_o69[202]; struct DynCubeTreeItem_s tCopy; };
    struct { char igi2_o70[258]; struct real64x3_t tCenter; };
    struct { char igi2_o71[282]; float av1DivSquaredDistance[256]; };
    struct { char igi2_o72[1306]; struct WorldTriggerStack_s atTriggerStack[50]; };
    struct { char igi2_o73[2306]; struct real64x3_t atMin[256]; };
    struct { char igi2_o74[8450]; struct real64x3_t atMax[256]; };
    struct { char igi2_o75[14594]; struct real32x3_t atDelta[256]; };
    char igi2_extent[17670];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct real64x3_t *v8; // ebx
  int v9; // esi
  struct real64x3_t *v10; // edx
  int v11; // edi
  float *p_vY; // ecx
  double *v13; // eax
  double v14; // st7
  double v15; // st7
  double v16; // st7
  double v17; // st7
  int v18; // edi
  int v19; // edi
  double *p_vX; // edx
  float *v21; // ecx
  double *v22; // eax
  double v23; // st7
  double v24; // st7
  double v25; // st7
  int v26; // esi
  double *v27; // ecx
  int v28; // edx
  double vX; // st7
  double v30; // st7
  double vZ; // st7
  double v32; // st7
  double v33; // st7
  double v34; // st7
  int nX; // eax
  int v36; // ebx
  int nY; // ecx
  int nZ; // edx
  int v39; // eax
  struct DynCubeTreeItem_s *v40; // ecx
  struct DynCubeTreeItem_s *v41; // esi
  struct DynCubeTreeItem_s *v42; // esi
  struct DynCubeTreeItem_s *v43; // esi
  unsigned __int8 bChildren; // cl
  double v45; // st7
  double v46; // st7
  double *v47; // eax
  unsigned __int8 v48; // al
  char v49; // al
  struct CallQueueItem_s *v50; // edi
  unsigned __int8 v51; // dl
  struct DynCubeObj_s *ptDynCubeObj; // ecx
  struct CallQueueItem_s *v53; // eax
  struct DynCubeObj_s *v54; // ecx
  double vRealRadius; // st7
  struct CallQueueItem_s *v56; // eax
  struct DynCubeTreeItem_s *v57; // ebx
  unsigned __int8 v58; // al
  unsigned __int8 v59; // al
  unsigned __int8 v60; // al
  char v61; // cl
  struct WorldTriggerStack_s *v62; // edx
  struct WorldTriggerStack_s *v63; // esi
  unsigned __int8 v64; // al
  unsigned __int8 v65; // al
  int v66; // eax
  int v67; // edi
  int v68; // eax
  int v69; // eax
  int v70; // edx
  double v71; // st7
  int v72; // esi
  double v73; // st7
  unsigned __int8 v74; // dl
  double v75; // st7
  int v76; // ecx
  int v77; // edi
  double v78; // st6
  double v79; // st5
  int v80; // ebx
  float *v81; // esi
  double *p_vZ; // edx
  double v83; // st4
  double v84; // st4
  double v85; // st4
  double v86; // st4
  double v87; // st4
  double v88; // st4
  double v89; // st4
  double v90; // st4
  float *v91; // esi
  double *v92; // edx
  int v93; // ecx
  double v94; // st4
  double v95; // st4
  char v96; // fps^1
  double v97; // st2
  bool v98; // c0
  char v99; // c2
  bool v100; // c3
  unsigned __int8 v101; // cl

  v8 = ptEnd;
  igi2_frame.ptTop = igi2_frame.atTriggerStack;
  v9 = 0;
  igi2_frame.tCallQueue.pptLast = (struct CallQueueItem_s **)&igi2_frame.tCallQueue;
  igi2_frame.tCallQueue.ptFirst = nullptr;
  if ( nNumLines >= 4 )
  {
    v10 = ptEnd + 1;
    v11 = 3;
    p_vY = &igi2_frame.atDelta[0].vY;
    v13 = &ptStart->vY;
    do
    {
      igi2_frame.v135 = v10[-1].vX - *(v13 - 1);
      *(p_vY - 1) = igi2_frame.v135;
      igi2_frame.v104 = *(double *)((char *)v13 + ((char *)ptEnd - (char *)ptStart)) - *v13;
      *p_vY = igi2_frame.v104;
      v14 = v10[-1].vZ - v13[1];
      p_vY[1] = v14;
      igi2_frame.av1DivSquaredDistance[v9] = 1.0 / (igi2_frame.v135 * igi2_frame.v135 + igi2_frame.v104 * igi2_frame.v104 + v14 * v14);
      igi2_frame.v136 = v10->vX - v13[2];
      p_vY[2] = igi2_frame.v136;
      igi2_frame.v105 = v10->vY - v13[3];
      p_vY[3] = igi2_frame.v105;
      v15 = v10->vZ - v13[4];
      p_vY[4] = v15;
      igi2_frame.av1DivSquaredDistance[v9 + 1] = 1.0 / (igi2_frame.v105 * igi2_frame.v105 + v15 * v15 + igi2_frame.v136 * igi2_frame.v136);
      igi2_frame.v137 = v10[1].vX - v13[5];
      p_vY[5] = igi2_frame.v137;
      igi2_frame.v106 = v10[1].vY - v13[6];
      p_vY[6] = igi2_frame.v106;
      v16 = v10[1].vZ - v13[7];
      p_vY[7] = v16;
      v11 += 4;
      v9 += 4;
      v10 += 4;
      v13 += 12;
      p_vY += 12;
      *((float *)&igi2_frame.tCenter.vZ + v9) = 1.0 / (igi2_frame.v137 * igi2_frame.v137 + igi2_frame.v106 * igi2_frame.v106 + v16 * v16);
      igi2_frame.v138 = v10[-2].vX - *(v13 - 4);
      *(p_vY - 4) = igi2_frame.v138;
      igi2_frame.v107 = v10[-2].vY - *(v13 - 3);
      *(p_vY - 3) = igi2_frame.v107;
      v17 = v10[-2].vZ - *(v13 - 2);
      *(p_vY - 2) = v17;
      *((float *)&igi2_frame.tCenter.vZ + v9 + 1) = 1.0 / (igi2_frame.v138 * igi2_frame.v138 + igi2_frame.v107 * igi2_frame.v107 + v17 * v17);
    }
    while ( v11 < nNumLines );
    v8 = ptEnd;
  }
  v18 = nNumLines;
  if ( v9 < nNumLines )
  {
    v19 = (char *)v8 - (char *)ptStart;
    p_vX = &v8[v9].vX;
    v21 = &igi2_frame.atDelta[v9].vY;
    v22 = &ptStart[v9].vY;
    while ( 1 )
    {
      ++v9;
      v23 = *p_vX - *(v22 - 1);
      p_vX += 3;
      v22 += 3;
      v21 += 3;
      igi2_frame.v148 = v23;
      *(v21 - 4) = v23;
      v24 = *(double *)((char *)v22 + v19 - 24);
      v18 = nNumLines;
      igi2_frame.v139 = v24 - *(v22 - 3);
      *(v21 - 3) = igi2_frame.v139;
      v25 = *(p_vX - 1) - *(v22 - 2);
      *(v21 - 2) = v25;
      *((float *)&igi2_frame.tCenter.vZ + v9 + 1) = 1.0 / (igi2_frame.v148 * igi2_frame.v148 + igi2_frame.v139 * igi2_frame.v139 + v25 * v25);
      if ( v9 >= nNumLines )
        break;
      v19 = (char *)v8 - (char *)ptStart;
    }
  }
  igi2_frame.tRealMin.vX = 1.7976931348623157e+308;
  igi2_frame.tRealMin.vY = 1.7976931348623157e+308;
  igi2_frame.tRealMin.vZ = 1.7976931348623157e+308;
  igi2_frame.tRealMax.vX = -1.7976931348623157e+308;
  igi2_frame.tRealMax.vY = -1.7976931348623157e+308;
  igi2_frame.tRealMax.vZ = -1.7976931348623157e+308;
  if ( v18 > 0 )
  {
    igi2_frame.v149 = (char *)&igi2_frame.atMin[0].vY - (char *)ptStart;
    v26 = (char *)v8 - (char *)ptStart;
    v27 = &ptStart->vY;
    v28 = 0;
    igi2_frame.v142 = v18;
    do
    {
      if ( *(v27 - 1) >= v8[v28].vX )
        vX = v8[v28].vX;
      else
        vX = *(v27 - 1);
      igi2_frame.v132 = vX;
      igi2_frame.atMin[v28].vX = vX;
      if ( *v27 >= *(double *)((char *)v27 + v26) )
        v30 = *(double *)((char *)v27 + v26);
      else
        v30 = *v27;
      igi2_frame.tIntMin = v30;
      *(double *)((char *)v27 + igi2_frame.v149 - 8) = v30;
      if ( v27[1] >= v8[v28].vZ )
        vZ = v8[v28].vZ;
      else
        vZ = v27[1];
      igi2_frame.v161 = vZ;
      *(double *)((char *)v27 + igi2_frame.v149) = vZ;
      if ( *(v27 - 1) <= v8[v28].vX )
        v32 = v8[v28].vX;
      else
        v32 = *(v27 - 1);
      igi2_frame.v163 = v32;
      igi2_frame.atMax[v28].vX = v32;
      if ( *v27 <= *(double *)((char *)v27 + v26) )
        v33 = *(double *)((char *)v27 + v26);
      else
        v33 = *v27;
      igi2_frame.v160 = v33;
      *(double *)((char *)v27 + ((char *)igi2_frame.atMax - (char *)ptStart)) = v33;
      if ( v27[1] <= v8[v28].vZ )
        v34 = v8[v28].vZ;
      else
        v34 = v27[1];
      *(double *)((char *)v27 + ((char *)&igi2_frame.atMax[0].vY - (char *)ptStart)) = v34;
      if ( igi2_frame.v132 < igi2_frame.tRealMin.vX )
        igi2_frame.tRealMin.vX = igi2_frame.v132;
      if ( igi2_frame.tIntMin < igi2_frame.tRealMin.vY )
        igi2_frame.tRealMin.vY = igi2_frame.tIntMin;
      if ( igi2_frame.v161 < igi2_frame.tRealMin.vZ )
        igi2_frame.tRealMin.vZ = igi2_frame.v161;
      if ( igi2_frame.v163 > igi2_frame.tRealMax.vX )
        igi2_frame.tRealMax.vX = igi2_frame.v163;
      if ( igi2_frame.v160 > igi2_frame.tRealMax.vY )
        igi2_frame.tRealMax.vY = igi2_frame.v160;
      if ( v34 > igi2_frame.tRealMax.vZ )
        igi2_frame.tRealMax.vZ = v34;
      ++v28;
      v27 += 3;
      --igi2_frame.v142;
    }
    while ( igi2_frame.v142 );
  }
  nX = ptWorld->tOrigo.nX;
  v36 = nX + (__int64)igi2_frame.tRealMin.vX;
  nY = ptWorld->tOrigo.nY;
  igi2_frame.tIntMin_4 = nY + (__int64)igi2_frame.tRealMin.vY;
  nZ = ptWorld->tOrigo.nZ;
  igi2_frame.tIntMin_8 = nZ + (__int64)igi2_frame.tRealMin.vZ;
  igi2_frame.tIntMax = nX + (__int64)igi2_frame.tRealMax.vX;
  igi2_frame.tIntMax_8 = nZ + (__int64)igi2_frame.tRealMax.vZ;
  igi2_frame.tIntMax_4 = nY + (__int64)igi2_frame.tRealMax.vY;
  World_UpdateStartDynCube(ptWorld, eDynCubeTree);
  v39 = ptWorld->anStartDynCubeLevel[eDynCubeTree];
  qmemcpy(&igi2_frame.tCopy, ptWorld->aptStartDynCube[eDynCubeTree], sizeof(igi2_frame.tCopy));
  igi2_frame.nLevel = v39;
  igi2_frame.nRadius = igi2_frame.tCopy.nSize;
  if ( v39 == 30 )
  {
    v40 = igi2_frame.tCopy.aptChild[0];
    v41 = igi2_frame.tCopy.aptChild[6];
    igi2_frame.tCopy.aptChild[0] = igi2_frame.tCopy.aptChild[7];
    igi2_frame.tCopy.aptChild[7] = v40;
    igi2_frame.tCopy.aptChild[6] = igi2_frame.tCopy.aptChild[1];
    igi2_frame.tCopy.aptChild[1] = v41;
    v42 = igi2_frame.tCopy.aptChild[5];
    igi2_frame.tCopy.aptChild[5] = igi2_frame.tCopy.aptChild[2];
    igi2_frame.tCopy.aptChild[2] = v42;
    v43 = igi2_frame.tCopy.aptChild[4];
    igi2_frame.tCopy.aptChild[4] = igi2_frame.tCopy.aptChild[3];
    bChildren = (8 * (((int)igi2_frame.tCopy.bChildren >> 4) & 1 | (2 * (((int)igi2_frame.tCopy.bChildren >> 3) & 1))))
              | (4 * (((int)igi2_frame.tCopy.bChildren >> 5) & 1 | (8 * (((int)igi2_frame.tCopy.bChildren >> 2) & 1))))
              | (2 * (((int)igi2_frame.tCopy.bChildren >> 6) & 1 | (32 * (((int)igi2_frame.tCopy.bChildren >> 1) & 1))))
              | (igi2_frame.tCopy.bChildren << 7)
              | ((int)igi2_frame.tCopy.bChildren >> 7) & 1;
    igi2_frame.tCopy.aptChild[3] = v43;
    igi2_frame.tCopy.bChildren = bChildren;
  }
  else
  {
    bChildren = igi2_frame.tCopy.bChildren;
  }
  v45 = (double)ptWorld->tOrigo.nX;
  igi2_frame.atTriggerStack[0].ptCube = &igi2_frame.tCopy;
  v46 = v45 + ptWorld->atStartDynCubePos[eDynCubeTree].vX;
  v47 = (double *)((char *)ptWorld + 24 * eDynCubeTree);
  igi2_frame.nStackSize = 1;
  igi2_frame.atTriggerStack[0].isInside = 0;
  igi2_frame.atTriggerStack[0].tCenter.nX = (__int64)v46;
  igi2_frame.atTriggerStack[0].tCenter.nY = (__int64)((double)ptWorld->tOrigo.nY + v47[4]);
  igi2_frame.v133 = (__int64)((double)ptWorld->tOrigo.nZ + v47[5]);
  v48 = nZMinMask[igi2_frame.tIntMin_8 > (int)igi2_frame.v133]
      & nZMaxMask[igi2_frame.tIntMax_8 < (int)igi2_frame.v133]
      & nYMinMask[igi2_frame.tIntMin_4 > igi2_frame.atTriggerStack[0].tCenter.nY]
      & nYMaxMask[igi2_frame.tIntMax_4 < igi2_frame.atTriggerStack[0].tCenter.nY]
      & nXMinMask[v36 > igi2_frame.atTriggerStack[0].tCenter.nX]
      & bChildren
      & nXMaxMask[igi2_frame.tIntMax < igi2_frame.atTriggerStack[0].tCenter.nX];
  igi2_frame.atTriggerStack[0].tCenter.nZ = igi2_frame.v133;
  igi2_frame.atTriggerStack[0].bChildBits = v48;
  if ( (v48 & 0xF) != 0 )
  {
    if ( (v48 & 3) != 0 )
      v49 = v48 & 1;
    else
      v49 = ((v48 & 4) != 0) + 2;
  }
  else if ( (v48 & 0x30) != 0 )
  {
    v49 = ((v48 & 0x10) != 0) + 4;
  }
  else
  {
    v49 = ((v48 & 0x40) != 0) + 6;
  }
  v50 = CallQueue_ptFirstFreeItem;
  igi2_frame.atTriggerStack[0].nChildToCheck = v49 ^ 1;
  do
  {
    v51 = igi2_frame.ptTop->bChildBits;
    if ( !v51 )
    {
      if ( igi2_frame.ptTop->isInside )
      {
        ptDynCubeObj = igi2_frame.ptTop->ptCube->ptDynCubeObj;
        if ( ptDynCubeObj )
        {
          do
          {
            if ( (bQTaskGroup & QTask_atQTaskType[ptDynCubeObj->tQObj.tQTask.eQTaskType].bQTaskGroup) != 0 )
            {
              v53 = v50;
              v50 = v50->ptNext;
              v53->ptQTask = &ptDynCubeObj->tQObj.tQTask;
              v53->uEvent.eQTaskEvent = eQTaskEvent;
              v53->isNoContext = false;
              v53->pxContext = pxContext;
              v53->ptNext = nullptr;
              *igi2_frame.tCallQueue.pptLast = v53;
              igi2_frame.tCallQueue.pptLast = &v53->ptNext;
            }
            ptDynCubeObj = ptDynCubeObj->ptNext;
          }
          while ( ptDynCubeObj );
LABEL_70:
          CallQueue_ptFirstFreeItem = v50;
        }
      }
      else
      {
        v54 = igi2_frame.ptTop->ptCube->ptDynCubeObj;
        if ( v54 )
        {
          do
          {
            vRealRadius = v54->tQObj.vRealRadius;
            if ( v54->tQObj.tPos.vX - vRealRadius <= igi2_frame.tRealMax.vX
              && vRealRadius + v54->tQObj.tPos.vX >= igi2_frame.tRealMin.vX
              && v54->tQObj.tPos.vY - vRealRadius <= igi2_frame.tRealMax.vY
              && vRealRadius + v54->tQObj.tPos.vY >= igi2_frame.tRealMin.vY
              && v54->tQObj.tPos.vZ - vRealRadius <= igi2_frame.tRealMax.vZ
              && vRealRadius + v54->tQObj.tPos.vZ >= igi2_frame.tRealMin.vZ
              && (bQTaskGroup & QTask_atQTaskType[v54->tQObj.tQTask.eQTaskType].bQTaskGroup) != 0 )
            {
              v56 = v50;
              v50 = v50->ptNext;
              v56->ptQTask = &v54->tQObj.tQTask;
              v56->uEvent.eQTaskEvent = eQTaskEvent;
              v56->isNoContext = false;
              v56->pxContext = pxContext;
              v56->ptNext = nullptr;
              *igi2_frame.tCallQueue.pptLast = v56;
              igi2_frame.tCallQueue.pptLast = &v56->ptNext;
            }
            v54 = v54->ptNext;
          }
          while ( v54 );
          goto LABEL_70;
        }
      }
      --igi2_frame.ptTop;
      ++igi2_frame.nLevel;
      igi2_frame.nRadius *= 2;
      --igi2_frame.nStackSize;
      continue;
    }
    igi2_frame.nChildToCheck = igi2_frame.ptTop->nChildToCheck;
    v57 = igi2_frame.ptTop->ptCube->aptChild[igi2_frame.nChildToCheck];
    v58 = v51 ^ (1 << igi2_frame.nChildToCheck);
    igi2_frame.ptTop->bChildBits = v58;
    if ( v58 )
    {
      if ( (v58 & 0xF) != 0 )
      {
        if ( (v58 & 3) != 0 )
          v59 = v58 & 1;
        else
          v59 = ((v58 & 4) != 0) + 2;
      }
      else if ( (v58 & 0x30) != 0 )
      {
        v59 = ((v58 & 0x10) != 0) + 4;
      }
      else
      {
        v59 = ((v58 & 0x40) != 0) + 6;
      }
      igi2_frame.ptTop->nChildToCheck = v59;
      igi2_frame.ptTop->nChildToCheck = v59 ^ 1;
    }
    v60 = v57->bChildren;
    igi2_frame.nRadius >>= 1;
    v61 = igi2_frame.nLevel - 1;
    ++igi2_frame.nStackSize;
    v62 = igi2_frame.ptTop;
    v63 = igi2_frame.ptTop + 1;
    igi2_frame.ptTop[1].ptCube = v57;
    igi2_frame.ptTop[1].bChildBits = v60;
    --igi2_frame.nLevel;
    ++igi2_frame.ptTop;
    if ( v62->isInside )
    {
      v63->isInside = 1;
      if ( v60 )
      {
        if ( (v60 & 0xF) != 0 )
        {
          if ( (v60 & 3) != 0 )
            v64 = v60 & 1;
          else
            v64 = ((v60 & 4) != 0) + 2;
          v63->nChildToCheck = v64;
          v63->nChildToCheck = v64 ^ 1;
        }
        else
        {
          if ( (v60 & 0x30) != 0 )
            v65 = ((v60 & 0x10) != 0) + 4;
          else
            v65 = ((v60 & 0x40) != 0) + 6;
          v63->nChildToCheck = v65;
          v63->nChildToCheck = v65 ^ 1;
        }
      }
      continue;
    }
    igi2_frame.bChildBits = v60;
    v63->isInside = 0;
    if ( !v60 )
      continue;
    v66 = igi2_frame.nChildToCheck;
    v63->tCenter.nX = v62->tCenter.nX + (World_atSubCubePos[v66].nX << v61);
    v67 = World_atSubCubePos[v66].nY;
    v68 = World_atSubCubePos[v66].nZ << v61;
    v63->tCenter.nY = v62->tCenter.nY + (v67 << v61);
    v69 = v62->tCenter.nZ + v68;
    v70 = v63->tCenter.nY;
    v71 = (double)(v63->tCenter.nX - ptWorld->tOrigo.nX);
    v63->tCenter.nZ = v69;
    v72 = ptWorld->tOrigo.nY;
    igi2_frame.tCenter.vX = v71;
    igi2_frame.v108 = v69 - ptWorld->tOrigo.nZ;
    igi2_frame.tCenter.vY = (double)(v70 - v72);
    igi2_frame.tCenter.vZ = (double)igi2_frame.v108;
    v73 = (double)(igi2_frame.nRadius >> 1);
    igi2_frame.vCubeRadius = v73;
    igi2_frame.iChild = 0;
    igi2_frame.vSphereRadius = v73 * 1.7320507764816284;
    do
    {
      v74 = igi2_frame.bChildBits;
      if ( ((unsigned __int8)(1 << igi2_frame.iChild) & igi2_frame.bChildBits) == 0 )
        goto LABEL_106;
      v75 = (double)(2 * (igi2_frame.iChild & 1) - 1) * igi2_frame.vCubeRadius + igi2_frame.tCenter.vX;
      v76 = 0;
      v77 = 0;
      igi2_frame.isTouchingLine = 0;
      v78 = (double)((igi2_frame.iChild & 2) - 1) * igi2_frame.vCubeRadius + igi2_frame.tCenter.vY;
      v79 = (double)(((igi2_frame.iChild >> 1) & 2) - 1) * igi2_frame.vCubeRadius + igi2_frame.tCenter.vZ;
      if ( nNumLines >= 4 )
      {
        igi2_frame.v166 = (char *)igi2_frame.atMin - (char *)ptStart;
        igi2_frame.v168 = (char *)&igi2_frame.atMin[0].vZ - (char *)ptStart;
        igi2_frame.v165 = (char *)&igi2_frame.atMin[1] - (char *)ptStart;
        igi2_frame.v167 = (char *)&igi2_frame.atMax[0].vZ - (char *)ptStart;
        igi2_frame.v169 = (char *)&igi2_frame.atMax[1] - (char *)ptStart;
        igi2_frame.v170 = (char *)&igi2_frame.atMin[1].vY - (char *)ptStart;
        LODWORD(igi2_frame.v160) = (char *)&igi2_frame.atMin[1].vZ - (char *)ptStart;
        LODWORD(igi2_frame.v163) = (char *)&igi2_frame.atMin[2] - (char *)ptStart;
        LODWORD(igi2_frame.v161) = (char *)&igi2_frame.atMax[1].vY - (char *)ptStart;
        v80 = 3;
        v81 = &igi2_frame.atDelta[0].vY;
        p_vZ = &ptStart[1].vZ;
        while ( !igi2_frame.isTouchingLine )
        {
          igi2_frame.tIntMaxa = v75 - *(p_vZ - 5);
          igi2_frame.tIntMax_4a = v78 - *(p_vZ - 4);
          v83 = v79 - *(p_vZ - 3);
          igi2_frame.tIntMax_8a = v83;
          igi2_frame.v109 = igi2_frame.tIntMax_8a * v81[1] + igi2_frame.tIntMax_4a * *v81 + igi2_frame.tIntMaxa * *(v81 - 1);
          igi2_frame.v143 = igi2_frame.vSphereRadius * igi2_frame.vSphereRadius;
          igi2_frame.v144 = igi2_frame.tIntMaxa * igi2_frame.tIntMaxa + igi2_frame.tIntMax_4a * igi2_frame.tIntMax_4a + v83 * v83;
          if ( igi2_frame.v144 - igi2_frame.v109 * igi2_frame.v109 * igi2_frame.av1DivSquaredDistance[v77] <= igi2_frame.v143 )
          {
            v84 = igi2_frame.vSphereRadius;
            if ( igi2_frame.vSphereRadius + v75 >= igi2_frame.atMin[v76].vX
              && v84 + v78 >= igi2_frame.atMin[v76].vY
              && v84 + v79 >= igi2_frame.atMin[v76].vZ
              && v75 - v84 <= igi2_frame.atMax[v76].vX
              && v78 - v84 <= igi2_frame.atMax[v76].vY
              && igi2_frame.atMax[v76].vZ >= v79 - v84 )
            {
              break;
            }
          }
          igi2_frame.tIntMaxb = v75 - *(p_vZ - 2);
          igi2_frame.tIntMax_4b = v78 - *(p_vZ - 1);
          v85 = v79 - *p_vZ;
          igi2_frame.tIntMax_8b = v85;
          igi2_frame.v110 = igi2_frame.tIntMax_8b * v81[4] + igi2_frame.tIntMax_4b * v81[3] + igi2_frame.tIntMaxb * v81[2];
          igi2_frame.v145 = igi2_frame.tIntMaxb * igi2_frame.tIntMaxb + igi2_frame.tIntMax_4b * igi2_frame.tIntMax_4b + v85 * v85;
          if ( igi2_frame.v145 - igi2_frame.v110 * igi2_frame.v110 * igi2_frame.av1DivSquaredDistance[v77 + 1] <= igi2_frame.v143 )
          {
            v86 = igi2_frame.vSphereRadius;
            if ( igi2_frame.vSphereRadius + v75 >= igi2_frame.atMin[v76 + 1].vX
              && v86 + v78 >= igi2_frame.atMin[v76 + 1].vY
              && v86 + v79 >= *(double *)((char *)p_vZ + igi2_frame.v166)
              && v75 - v86 <= igi2_frame.atMax[v76 + 1].vX
              && v78 - v86 <= igi2_frame.atMax[v76 + 1].vY
              && *(double *)((char *)p_vZ + ((char *)igi2_frame.atMax - (char *)ptStart)) >= v79 - v86 )
            {
              break;
            }
          }
          igi2_frame.tIntMaxc = v75 - p_vZ[1];
          igi2_frame.tIntMax_4c = v78 - p_vZ[2];
          v87 = v79 - p_vZ[3];
          igi2_frame.tIntMax_8c = v87;
          igi2_frame.v111 = igi2_frame.tIntMax_8c * v81[7] + igi2_frame.tIntMax_4c * v81[6] + igi2_frame.tIntMaxc * v81[5];
          igi2_frame.v146 = igi2_frame.tIntMaxc * igi2_frame.tIntMaxc + igi2_frame.tIntMax_4c * igi2_frame.tIntMax_4c + v87 * v87;
          if ( igi2_frame.v146 - igi2_frame.v111 * igi2_frame.v111 * igi2_frame.av1DivSquaredDistance[v77 + 2] <= igi2_frame.v143 )
          {
            v88 = igi2_frame.vSphereRadius;
            if ( igi2_frame.vSphereRadius + v75 >= *(double *)((char *)p_vZ + ((char *)&igi2_frame.atMin[0].vY - (char *)ptStart))
              && v88 + v78 >= *(double *)((char *)p_vZ + igi2_frame.v168)
              && v88 + v79 >= *(double *)((char *)p_vZ + igi2_frame.v165)
              && v75 - v88 <= *(double *)((char *)p_vZ + ((char *)&igi2_frame.atMax[0].vY - (char *)ptStart))
              && v78 - v88 <= *(double *)((char *)p_vZ + igi2_frame.v167)
              && *(double *)((char *)p_vZ + igi2_frame.v169) >= v79 - v88 )
            {
              break;
            }
          }
          igi2_frame.tIntMaxd = v75 - p_vZ[4];
          igi2_frame.tIntMax_4d = v78 - p_vZ[5];
          v89 = v79 - p_vZ[6];
          igi2_frame.tIntMax_8d = v89;
          igi2_frame.v112 = igi2_frame.tIntMax_8d * v81[10] + igi2_frame.tIntMax_4d * v81[9] + igi2_frame.tIntMaxd * v81[8];
          igi2_frame.v147 = igi2_frame.tIntMaxd * igi2_frame.tIntMaxd + igi2_frame.tIntMax_4d * igi2_frame.tIntMax_4d + v89 * v89;
          if ( igi2_frame.v147 - igi2_frame.v112 * igi2_frame.v112 * igi2_frame.av1DivSquaredDistance[v77 + 3] <= igi2_frame.v143 )
          {
            v90 = igi2_frame.vSphereRadius;
            if ( igi2_frame.vSphereRadius + v75 >= *(double *)((char *)p_vZ + igi2_frame.v170)
              && v90 + v78 >= *(double *)((char *)p_vZ + LODWORD(igi2_frame.v160))
              && v90 + v79 >= *(double *)((char *)p_vZ + LODWORD(igi2_frame.v163))
              && v75 - v90 <= *(double *)((char *)p_vZ + LODWORD(igi2_frame.v161))
              && v78 - v90 <= *(double *)((char *)p_vZ + ((char *)&igi2_frame.atMax[1].vZ - (char *)ptStart))
              && *(double *)((char *)p_vZ + ((char *)&igi2_frame.atMax[2] - (char *)ptStart)) >= v79 - v90 )
            {
              igi2_frame.isTouchingLine = 1;
            }
          }
          v80 += 4;
          v77 += 4;
          v81 += 12;
          v76 += 4;
          p_vZ += 12;
          if ( v80 >= nNumLines )
          {
            v74 = igi2_frame.bChildBits;
            goto LABEL_135;
          }
        }
        goto LABEL_105;
      }
LABEL_135:
      if ( v77 < nNumLines )
      {
        v91 = &igi2_frame.atDelta[v77].vY;
        v92 = &ptStart[v77].vZ;
        v93 = v77;
        while ( !igi2_frame.isTouchingLine )
        {
          igi2_frame.tIntMaxe = v75 - *(v92 - 2);
          igi2_frame.tIntMax_4e = v78 - *(v92 - 1);
          v94 = v79 - *v92;
          igi2_frame.tIntMax_8e = v94;
          igi2_frame.v113 = igi2_frame.tIntMax_8e * v91[1] + igi2_frame.tIntMax_4e * *v91 + igi2_frame.tIntMaxe * *(v91 - 1);
          igi2_frame.v134 = igi2_frame.tIntMaxe * igi2_frame.tIntMaxe + igi2_frame.tIntMax_4e * igi2_frame.tIntMax_4e + v94 * v94;
          if ( igi2_frame.vSphereRadius * igi2_frame.vSphereRadius >= igi2_frame.v134 - igi2_frame.v113 * igi2_frame.v113 * igi2_frame.av1DivSquaredDistance[v77] )
          {
            v95 = igi2_frame.vSphereRadius;
            if ( igi2_frame.vSphereRadius + v75 >= igi2_frame.atMin[v93].vX
              && v95 + v78 >= igi2_frame.atMin[v93].vY
              && v95 + v79 >= *(double *)((char *)v92 + ((char *)igi2_frame.atMin - (char *)ptStart))
              && v75 - v95 <= igi2_frame.atMax[v93].vX
              && v78 - v95 <= igi2_frame.atMax[v93].vY )
            {
              v97 = *(double *)((char *)v92 + ((char *)igi2_frame.atMax - (char *)ptStart));
              v98 = v97 < v79 - v95;
              v99 = 0;
              v100 = v97 == v79 - v95;
              v96 = (char)(v98 | (v99 << 2) | (v100 << 6));
              igi2_frame.isTouchingLine = __SETP__(v96 & 5, 0);
            }
          }
          ++v77;
          v91 += 3;
          v92 += 3;
          ++v93;
          if ( v77 >= nNumLines )
          {
            v74 = igi2_frame.bChildBits;
            goto LABEL_147;
          }
        }
LABEL_105:
        v74 = igi2_frame.bChildBits;
        goto LABEL_106;
      }
LABEL_147:
      if ( !igi2_frame.isTouchingLine )
      {
        v74 &= ~(1 << igi2_frame.iChild);
        igi2_frame.bChildBits = v74;
      }
LABEL_106:
      ++igi2_frame.iChild;
    }
    while ( igi2_frame.iChild < 8 );
    igi2_frame.ptTop->bChildBits = v74;
    if ( v74 )
    {
      if ( (v74 & 0xF) != 0 )
      {
        if ( (v74 & 3) != 0 )
        {
          igi2_frame.ptTop->nChildToCheck = v74 & 1;
          goto LABEL_154;
        }
        v101 = ((v74 & 4) != 0) + 2;
LABEL_153:
        igi2_frame.ptTop->nChildToCheck = v101;
      }
      else
      {
        if ( (v74 & 0x30) == 0 )
        {
          v101 = ((v74 & 0x40) != 0) + 6;
          goto LABEL_153;
        }
        igi2_frame.ptTop->nChildToCheck = ((v74 & 0x10) != 0) + 4;
      }
LABEL_154:
      igi2_frame.ptTop->nChildToCheck ^= 1u;
    }
    v50 = CallQueue_ptFirstFreeItem;
  }
  while ( igi2_frame.nStackSize );
  CallQueue_CallHandlers(&igi2_frame.tCallQueue);
}

// source: e/1/world.c:3809  [anchor-mhash]
unsigned int __cdecl World_TriggerQTaskEventAlongLine(
        struct World_s *ptWorld,
        __int16 eQTaskEvent,
        void *pxContext,
        struct real64x3_t *ptStart,
        struct real64x3_t *ptEnd,
        int nNumLines,
        unsigned int bQTaskGroup)
{
  unsigned int result; // eax

  World_TriggerQTaskEventAlongLineSpecificTree(
    ptWorld,
    eQTaskEvent,
    pxContext,
    ptStart,
    ptEnd,
    nNumLines,
    bQTaskGroup,
    WORLD_DYNCUBETREE_STATIONARY);
  return result;
}

// source: e/1/world.c:3849  [anchor-callee]
struct real64x3_t *__cdecl World_TriggerQTaskEventSphereSpecificTree(
        struct World_s *ptWorld,
        __int16 eQTaskEvent,
        void *pxContext,
        struct real64x3_t *ptPos,
        float vRadius,
        unsigned int bQTaskGroup,
        enum DynCubeTree_e eDynCubeTree)
{
  #pragma pack(push, 1)
  union
  {
    struct { unsigned __int8 nChildToCheck; };
    struct { char igi2_o1[1]; unsigned int nRadiusBits; };
    struct { char igi2_o2[5]; unsigned int nRadius; };
    struct { char igi2_o3[9]; int tIntMax; };
    struct { char igi2_o4[13]; int tIntMax_4; };
    struct { char igi2_o5[17]; int tIntMax_8; };
    struct { char igi2_o6[21]; int tIntMin; };
    struct { char igi2_o7[25]; int tIntMin_4; };
    struct { char igi2_o8[29]; int tIntMin_8; };
    struct { char igi2_o9[33]; struct CallQueue_t tCallQueue; };
    struct { char igi2_o10[41]; unsigned int nStackSize; };
    struct { char igi2_o11[45]; struct int32x3_t tAbsolutePos; };
    struct { char igi2_o12[57]; struct DynCubeTreeItem_s tCopy; };
    struct { char igi2_o13[113]; struct real32x3_t tDelta; };
    struct { char igi2_o14[125]; struct real64x3_t tRealMin; };
    struct { char igi2_o15[149]; struct real64x3_t tRealMax; };
    struct { char igi2_o16[173]; struct WorldTriggerStack_s atTriggerStack[50]; };
    char igi2_extent[1173];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v7; // st6
  double vY; // st6
  struct WorldTriggerStack_s *v9; // ebp
  double v10; // st7
  double vX; // st6
  int nX; // edx
  int v13; // ebx
  int nY; // esi
  int nZ; // edi
  struct DynCubeTreeItem_s *v16; // eax
  bool v17; // cl
  struct DynCubeTreeItem_s *v18; // eax
  unsigned int v19; // edi
  char v20; // cl
  char v21; // cl
  struct DynCubeTreeItem_s *v22; // eax
  char v23; // cl
  struct DynCubeTreeItem_s *v24; // eax
  unsigned __int8 v25; // cl
  unsigned __int8 v26; // al
  char v27; // al
  unsigned __int8 bChildBits; // bl
  struct DynCubeObj_s *i; // ecx
  struct CallQueueItem_s *v30; // eax
  struct DynCubeObj_s *j; // esi
  double vRealRadius; // st5
  struct DynCubeTreeItem_s *v33; // edx
  unsigned __int8 v34; // al
  unsigned __int8 v35; // al
  unsigned __int8 bChildren; // al
  struct WorldTriggerStack_s *v37; // esi
  unsigned __int8 isInside; // cl
  unsigned __int8 v39; // al
  unsigned __int8 v40; // al
  int v41; // edx
  int v42; // edi
  int v43; // edx
  int v44; // edx
  int v45; // ecx
  int v46; // esi
  unsigned __int8 v47; // al
  int v48; // eax
  struct real64x3_t *result; // eax

  v7 = ptPos->vX - vRadius;
  igi2_frame.tCallQueue.pptLast = (struct CallQueueItem_s **)&igi2_frame.tCallQueue;
  igi2_frame.tRealMin.vX = v7;
  vY = ptPos->vY;
  igi2_frame.nRadiusBits = 30;
  igi2_frame.nRadius = 0x40000000;
  v9 = igi2_frame.atTriggerStack;
  igi2_frame.tCallQueue.ptFirst = nullptr;
  igi2_frame.tRealMin.vY = vY - vRadius;
  igi2_frame.tRealMin.vZ = ptPos->vZ - vRadius;
  igi2_frame.tRealMax.vX = vRadius + ptPos->vX;
  igi2_frame.tRealMax.vY = vRadius + ptPos->vY;
  v10 = vRadius + ptPos->vZ;
  vX = igi2_frame.tRealMin.vX;
  nX = ptWorld->tOrigo.nX;
  v13 = nX + (__int64)igi2_frame.tRealMin.vX;
  igi2_frame.tIntMin = v13;
  igi2_frame.tAbsolutePos.nX = nX + (__int64)ptPos->vX;
  nY = ptWorld->tOrigo.nY;
  igi2_frame.tAbsolutePos.nY = nY + (__int64)ptPos->vY;
  nZ = ptWorld->tOrigo.nZ;
  igi2_frame.tAbsolutePos.nZ = nZ + (__int64)ptPos->vZ;
  igi2_frame.tIntMin_4 = nY + (__int64)igi2_frame.tRealMin.vY;
  igi2_frame.tIntMin_8 = nZ + (__int64)igi2_frame.tRealMin.vZ;
  igi2_frame.tIntMax = nX + (__int64)igi2_frame.tRealMax.vX;
  igi2_frame.tIntMax_8 = nZ + (__int64)v10;
  igi2_frame.tIntMax_4 = nY + (__int64)igi2_frame.tRealMax.vY;
  qmemcpy(&igi2_frame.tCopy, ptWorld->aptDynCubeTree[eDynCubeTree], sizeof(igi2_frame.tCopy));
  v16 = igi2_frame.tCopy.aptChild[0];
  igi2_frame.tCopy.aptChild[0] = igi2_frame.tCopy.aptChild[7];
  v17 = igi2_frame.tCopy.aptChild[7] != nullptr;
  LOBYTE(nX) = (v16 == nullptr) - 1;
  igi2_frame.tCopy.aptChild[7] = v16;
  v18 = igi2_frame.tCopy.aptChild[1];
  v19 = 1;
  igi2_frame.atTriggerStack[0].isInside = 0;
  v20 = nX & 0x80 | v17;
  igi2_frame.tCopy.aptChild[1] = igi2_frame.tCopy.aptChild[6];
  LOBYTE(nX) = (igi2_frame.tCopy.aptChild[6] == nullptr) - 1;
  igi2_frame.tCopy.aptChild[6] = v18;
  v21 = (v18 == nullptr ? 0 : 0x40) | nX & 2 | v20;
  v22 = igi2_frame.tCopy.aptChild[2];
  igi2_frame.tCopy.aptChild[2] = igi2_frame.tCopy.aptChild[5];
  LOBYTE(nX) = (igi2_frame.tCopy.aptChild[5] == nullptr) - 1;
  igi2_frame.tCopy.aptChild[5] = v22;
  v23 = (v22 == nullptr ? 0 : 0x20) | nX & 4 | v21;
  v24 = igi2_frame.tCopy.aptChild[3];
  igi2_frame.tCopy.aptChild[3] = igi2_frame.tCopy.aptChild[4];
  LOBYTE(nX) = (igi2_frame.tCopy.aptChild[4] == nullptr) - 1;
  igi2_frame.tCopy.aptChild[4] = v24;
  igi2_frame.atTriggerStack[0].tCenter.nX = 0;
  igi2_frame.atTriggerStack[0].tCenter.nY = 0;
  igi2_frame.atTriggerStack[0].tCenter.nZ = 0;
  igi2_frame.atTriggerStack[0].ptCube = &igi2_frame.tCopy;
  v25 = (v24 == nullptr ? 0 : 0x10) | nX & 8 | v23;
  LOBYTE(v24) = v25 & nXMaxMask[igi2_frame.tIntMax < 0];
  igi2_frame.tCopy.bChildren = v25;
  v26 = nZMinMask[igi2_frame.tIntMin_8 > 0]
      & nZMaxMask[igi2_frame.tIntMax_8 < 0]
      & nYMinMask[igi2_frame.tIntMin_4 > 0]
      & nYMaxMask[igi2_frame.tIntMax_4 < 0]
      & nXMinMask[v13 > 0]
      & (unsigned __int8)v24;
  igi2_frame.atTriggerStack[0].bChildBits = v26;
  if ( (v26 & 0xF) != 0 )
  {
    if ( (v26 & 3) != 0 )
      v27 = v26 & 1;
    else
      v27 = ((v26 & 4) != 0) + 2;
  }
  else if ( (v26 & 0x30) != 0 )
  {
    v27 = ((v26 & 0x10) != 0) + 4;
  }
  else
  {
    v27 = ((v26 & 0x40) != 0) + 6;
  }
  igi2_frame.atTriggerStack[0].nChildToCheck = v27 ^ 1;
  do
  {
    bChildBits = v9->bChildBits;
    if ( bChildBits )
    {
      igi2_frame.nChildToCheck = v9->nChildToCheck;
      v33 = v9->ptCube->aptChild[igi2_frame.nChildToCheck];
      v34 = bChildBits ^ (1 << igi2_frame.nChildToCheck);
      v9->bChildBits = v34;
      if ( v34 )
      {
        if ( (v34 & 0xF) != 0 )
        {
          if ( (v34 & 3) != 0 )
            v35 = v34 & 1;
          else
            v35 = ((v34 & 4) != 0) + 2;
        }
        else if ( (v34 & 0x30) != 0 )
        {
          v35 = ((v34 & 0x10) != 0) + 4;
        }
        else
        {
          v35 = ((v34 & 0x40) != 0) + 6;
        }
        v9->nChildToCheck = v35;
        v9->nChildToCheck = v35 ^ 1;
      }
      bChildren = v33->bChildren;
      igi2_frame.nRadius >>= 1;
      v37 = v9++;
      --igi2_frame.nRadiusBits;
      v9->ptCube = v33;
      v9->bChildBits = bChildren;
      isInside = v37->isInside;
      igi2_frame.nStackSize = ++v19;
      if ( isInside )
      {
        v9->isInside = 1;
        if ( bChildren )
        {
          if ( (bChildren & 0xF) != 0 )
          {
            if ( (bChildren & 3) != 0 )
              v39 = bChildren & 1;
            else
              v39 = ((bChildren & 4) != 0) + 2;
            v9->nChildToCheck = v39;
            v9->nChildToCheck = v39 ^ 1;
          }
          else
          {
            if ( (bChildren & 0x30) != 0 )
              v40 = ((bChildren & 0x10) != 0) + 4;
            else
              v40 = ((bChildren & 0x40) != 0) + 6;
            v9->nChildToCheck = v40;
            v9->nChildToCheck = v40 ^ 1;
          }
        }
      }
      else
      {
        v9->isInside = 0;
        if ( bChildren )
        {
          v41 = igi2_frame.nChildToCheck;
          v9->tCenter.nX = v37->tCenter.nX + (World_atSubCubePos[v41].nX << igi2_frame.nRadiusBits);
          v42 = World_atSubCubePos[v41].nY;
          v43 = World_atSubCubePos[v41].nZ << igi2_frame.nRadiusBits;
          v9->tCenter.nY = v37->tCenter.nY + (v42 << igi2_frame.nRadiusBits);
          v44 = v37->tCenter.nZ + v43;
          v45 = v9->tCenter.nX;
          v9->tCenter.nZ = v44;
          if ( igi2_frame.tIntMax > v45 )
          {
            if ( igi2_frame.tIntMin >= v45 )
              bChildren &= 0xAAu;
          }
          else
          {
            bChildren &= 0x55u;
          }
          v46 = v9->tCenter.nY;
          if ( igi2_frame.tIntMax_4 > v46 )
          {
            if ( igi2_frame.tIntMin_4 >= v46 )
              bChildren &= 0xCCu;
          }
          else
          {
            bChildren &= 0x33u;
          }
          if ( igi2_frame.tIntMax_8 > v44 )
          {
            if ( igi2_frame.tIntMin_8 >= v44 )
              bChildren &= 0xF0u;
          }
          else
          {
            bChildren &= 0xFu;
          }
          v9->bChildBits = bChildren;
          if ( bChildren )
          {
            if ( (bChildren & 0xF) != 0 )
            {
              if ( (bChildren & 3) != 0 )
                v47 = bChildren & 1;
              else
                v47 = ((bChildren & 4) != 0) + 2;
            }
            else if ( (bChildren & 0x30) != 0 )
            {
              v47 = ((bChildren & 0x10) != 0) + 4;
            }
            else
            {
              v47 = ((bChildren & 0x40) != 0) + 6;
            }
            v9->nChildToCheck = v47;
            v9->nChildToCheck = v47 ^ 1;
          }
          v48 = v9->tCenter.nZ;
          igi2_frame.tDelta.vX = (float)(v45 - igi2_frame.tAbsolutePos.nX);
          v19 = igi2_frame.nStackSize;
          igi2_frame.tDelta.vY = (float)(v46 - igi2_frame.tAbsolutePos.nY);
          if ( (vRadius - (double)igi2_frame.nRadius * 1.7320507764816284) * (vRadius - (double)igi2_frame.nRadius * 1.7320507764816284) > igi2_frame.tDelta.vX * igi2_frame.tDelta.vX
                                                                                                 + igi2_frame.tDelta.vY * igi2_frame.tDelta.vY
                                                                                                 + (double)(v48 - igi2_frame.tAbsolutePos.nZ)
                                                                                                 * (double)(v48 - igi2_frame.tAbsolutePos.nZ) )
            v9->isInside = 1;
        }
      }
    }
    else
    {
      if ( v9->isInside )
      {
        for ( i = v9->ptCube->ptDynCubeObj; i; i = i->ptNext )
        {
          if ( (bQTaskGroup & QTask_atQTaskType[i->tQObj.tQTask.eQTaskType].bQTaskGroup) != 0 )
          {
            v30 = CallQueue_ptFirstFreeItem;
            CallQueue_ptFirstFreeItem = CallQueue_ptFirstFreeItem->ptNext;
            v30->uEvent.eQTaskEvent = eQTaskEvent;
            v30->ptQTask = &i->tQObj.tQTask;
            v30->isNoContext = false;
            v30->pxContext = pxContext;
            v30->ptNext = nullptr;
            *igi2_frame.tCallQueue.pptLast = v30;
            igi2_frame.tCallQueue.pptLast = &v30->ptNext;
          }
        }
      }
      else
      {
        for ( j = v9->ptCube->ptDynCubeObj; j; j = j->ptNext )
        {
          vRealRadius = j->tQObj.vRealRadius;
          if ( j->tQObj.tPos.vX - vRealRadius <= igi2_frame.tRealMax.vX
            && vX <= vRealRadius + j->tQObj.tPos.vX
            && j->tQObj.tPos.vY - vRealRadius <= igi2_frame.tRealMax.vY
            && vRealRadius + j->tQObj.tPos.vY >= igi2_frame.tRealMin.vY
            && v10 >= j->tQObj.tPos.vZ - vRealRadius
            && vRealRadius + j->tQObj.tPos.vZ >= igi2_frame.tRealMin.vZ
            && (bQTaskGroup & QTask_atQTaskType[j->tQObj.tQTask.eQTaskType].bQTaskGroup) != 0 )
          {
            CallQueue_QueueEvent(&igi2_frame.tCallQueue, &j->tQObj.tQTask, eQTaskEvent, pxContext);
          }
        }
      }
      --v9;
      igi2_frame.nRadius *= 2;
      ++igi2_frame.nRadiusBits;
      --v19;
    }
  }
  while ( v19 );
  CallQueue_CallHandlers(&igi2_frame.tCallQueue);
  return result;
}

// source: e/1/world.c:4311  [anchor-mhash]
unsigned int __cdecl World_TriggerQTaskEventSphere(
        struct World_s *ptWorld,
        __int16 eQTaskEvent,
        void *pxContext,
        struct real64x3_t *ptPos,
        float vRadius,
        unsigned int bQTaskGroup)
{
  return (unsigned int)World_TriggerQTaskEventSphereSpecificTree(
                         ptWorld,
                         eQTaskEvent,
                         pxContext,
                         ptPos,
                         vRadius,
                         bQTaskGroup,
                         WORLD_DYNCUBETREE_STATIONARY);
}

// source: e/1/world.c:4345  [anchor-mhash]
int __cdecl World_GetMaterialTerrainMesh(
        struct CubeItem0_MeshHeader_s *ptFastMesh,
        struct real64x3_t *ptCubeCenter,
        struct real64x3_t *ptA,
        int nIteration,
        int *piEnterMaterial,
        unsigned int bOrientation)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real32x3_t vTemp; };
    struct { char igi2_o1[20]; int nU; };
    struct { char igi2_o2[24]; struct real64x3_t tPos; };
    struct { char igi2_o3[52]; float vPixScaleX; };
    struct { char igi2_o4[56]; __int64 v107; };
    struct { char igi2_o5[64]; int v108; };
    struct { char igi2_o6[68]; int iFace; };
    struct { char igi2_o7[72]; float vHeightMapScale; };
    struct { char igi2_o8[76]; int nHeightMapPitchShift; };
    struct { char igi2_o9[80]; int nFace; };
    struct { char igi2_o10[84]; int isHit; };
    struct { char igi2_o11[88]; double vMinDistSquared; };
    struct { char igi2_o12[96]; int nFaceData; };
    struct { char igi2_o13[100]; struct CubeItem0Face_t *ptFace; };
    struct { char igi2_o14[104]; float vFlipBackFace; };
    struct { char igi2_o15[108]; struct real32x3_t tTempHitPos; };
    struct { char igi2_o16[120]; struct real64x3_t tVec1; };
    struct { char igi2_o17[144]; struct real32x3_t tDirection; };
    struct { char igi2_o18[156]; struct real32x3_t tHitNormal; };
    struct { char igi2_o19[168]; struct real64x3_t tReal64Normal; };
    struct { char igi2_o20[192]; struct real64x3_t tVec0; };
    struct { char igi2_o21[216]; struct real32x3_t tReal32Vec1; };
    struct { char igi2_o22[228]; struct real32x3_t tReal32Vec0; };
    struct { char igi2_o23[240]; struct real64x3_t tB; };
    struct { char igi2_o24[264]; double v127[3]; };
    struct { char igi2_o25[288]; struct real64x3_t tHitDirection; };
    struct { char igi2_o26[312]; struct real64x3_t tReal64HitDirection; };
    struct { char igi2_o27[336]; struct real64x3_t atVertex[64]; };
    char igi2_extent[1876];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  float v6; // ecx
  int v7; // edx
  double v8; // st7
  struct CubeItem0Face_t *v9; // ebp
  int v10; // esi
  char v11; // al
  unsigned __int16 *v12; // ebx
  int v13; // ecx
  double v14; // st7
  int v15; // ecx
  unsigned int v16; // esi
  struct real64x3_t *v17; // ebp
  unsigned int v18; // eax
  double v19; // st6
  double v20; // st5
  double v21; // st6
  double v22; // st5
  float v23; // eax
  int v24; // ecx
  int v25; // edi
  float v26; // ecx
  double v27; // st3
  int v28; // eax
  unsigned int v29; // eax
  double v30; // st6
  double v31; // st5
  double v32; // st6
  double v33; // st5
  float v34; // eax
  int v35; // ecx
  int v36; // edi
  float v37; // ecx
  double v38; // st3
  int v39; // eax
  unsigned int v40; // eax
  double v41; // st6
  double v42; // st5
  double v43; // st6
  double v44; // st5
  float v45; // eax
  int v46; // ecx
  int v47; // edi
  float v48; // ecx
  double v49; // st3
  int v50; // eax
  unsigned int v51; // eax
  double v52; // st6
  double v53; // st5
  double v54; // st6
  double v55; // st5
  float v56; // eax
  int v57; // ecx
  int v58; // edi
  float v59; // ecx
  double v60; // st3
  int v61; // eax
  int v62; // edi
  struct real64x3_t *v63; // ebp
  unsigned int v64; // eax
  double v65; // st6
  double v66; // st6
  double v67; // st5
  double v68; // st6
  double v69; // st5
  int v70; // ecx
  int v71; // edi
  double v72; // st4
  int v73; // eax
  double v74; // st3
  struct real64x3_t *v75; // edi
  bool v76; // zf
  int v77; // eax
  int v78; // esi
  unsigned __int8 v79; // dl
  int nFace_low_high; // ecx
  int v81; // edx
  double v82; // st7
  double v83; // st7
  double v84; // st6
  double v85; // st5
  int v87; // ecx
  struct real64x3_t *v88; // ebx
  double *p_vY; // ebp
  double v90; // st7
  double v91; // st6
  double v92; // st6
  double v93; // st5
  long double v94; // st3
  double v95; // st5
  long double v96; // st6
  double v97; // st7
  double v98; // st6
  double v99; // st5
  double v100; // st4
  double v101; // st4
  double v102; // st4

  if ( HeightMap_biHeightMap )
  {
    v6 = *((float *)&HeightMap_nCurrentHeightSmooth + 12 * HeightMap_biHeightMap);
    v7 = dword_8538DF8[12 * HeightMap_biHeightMap];
    *(float *)&igi2_frame.vMinDistSquared = *((double *)&unk_8538DE8 + 6 * HeightMap_biHeightMap);
    v8 = *((double *)&unk_8538DF0 + 6 * HeightMap_biHeightMap);
    igi2_frame.vHeightMapScale = v6;
    *((float *)&igi2_frame.vMinDistSquared + 1) = v8;
    igi2_frame.nHeightMapPitchShift = *((_DWORD *)&QCube_atCubeHash[2047].ptHashCubeData + 12 * HeightMap_biHeightMap) + 3;
  }
  else
  {
    v7 = LODWORD(igi2_frame.vFlipBackFace);
  }
  v9 = (struct CubeItem0Face_t *)&ptFastMesh[1];
  v10 = ptFastMesh->nSimple + ptFastMesh->nComplexEdge;
  v11 = bOrientation;
  v12 = (unsigned __int16 *)((char *)&ptFastMesh[1] + ptFastMesh->nSizeToVertexList);
  igi2_frame.ptFace = (struct CubeItem0Face_t *)&ptFastMesh[1];
  igi2_frame.isHit = v10;
  igi2_frame.vFlipBackFace = 1.0;
  if ( (bOrientation & 0xFFFFFFFC) != 0 )
    igi2_frame.vFlipBackFace = -1.0;
  v13 = 0;
  igi2_frame.nFaceData = 0;
  LODWORD(igi2_frame.v107) = 0x40000000 >> nIteration;
  v14 = (double)(0x40000000 >> nIteration) * 0.041666666666666664;
  if ( v10 >= 4 )
  {
    igi2_frame.iFace = bOrientation & 1;
    v15 = bOrientation & 4;
    v16 = bOrientation & 2;
    igi2_frame.nFace = v15;
    igi2_frame.v108 = v16;
    LODWORD(igi2_frame.v107) = 3;
    v17 = &igi2_frame.atVertex[1];
    while ( 1 )
    {
      v18 = *v12 + (v12[1] << 16);
      LODWORD(igi2_frame.vTemp.vX) = ((v18 >> 14) & 0x3F) - 24;
      igi2_frame.tPos.vY = (double)(int)(((v18 >> 20) & 0x3F) - 24);
      igi2_frame.tPos.vZ = (double)SLODWORD(igi2_frame.vTemp.vX);
      v19 = (double)(int)((v18 >> 26) - 24) * v14;
      v20 = igi2_frame.tPos.vY * v14;
      igi2_frame.tPos.vY = igi2_frame.tPos.vY * v14;
      igi2_frame.tPos.vZ = igi2_frame.tPos.vZ * v14;
      if ( v15 )
        v19 = -v19;
      if ( igi2_frame.iFace )
      {
        *(double *)&igi2_frame.vTemp.vX = v20;
        if ( v16 )
        {
          igi2_frame.tPos.vY = -v19;
          v19 = *(double *)&igi2_frame.vTemp.vX;
        }
        else
        {
          igi2_frame.tPos.vY = v19;
          v19 = -*(double *)&igi2_frame.vTemp.vX;
        }
      }
      else if ( v16 )
      {
        v19 = -v19;
        igi2_frame.tPos.vY = -v20;
      }
      igi2_frame.tPos.vX = v19 + ptCubeCenter->vX;
      igi2_frame.tPos.vY = igi2_frame.tPos.vY + ptCubeCenter->vY;
      igi2_frame.tPos.vZ = igi2_frame.tPos.vZ + ptCubeCenter->vZ;
      if ( HeightMap_biHeightMap )
      {
        v21 = (igi2_frame.tPos.vX - *(float *)&igi2_frame.vMinDistSquared) * igi2_frame.vHeightMapScale;
        v22 = (igi2_frame.tPos.vY - *((float *)&igi2_frame.vMinDistSquared + 1)) * igi2_frame.vHeightMapScale;
        igi2_frame.nU = (__int64)v21;
        *(_QWORD *)&igi2_frame.vTemp.vX = (__int64)v22;
        LODWORD(v23) = (__int64)v22;
        igi2_frame.vTemp.vX = v23;
        v24 = (LODWORD(v23) << igi2_frame.nHeightMapPitchShift) + LODWORD(v23);
        v25 = *(char *)(v24 + igi2_frame.nU + v7);
        LODWORD(v26) = *(char *)(igi2_frame.nU + 1 + v24 + v7);
        igi2_frame.vPixScaleX = v21 - (double)igi2_frame.nU;
        igi2_frame.vTemp.vX = v26;
        v27 = (double)*(char *)(igi2_frame.nU + LODWORD(v23) + 1 + ((LODWORD(v23) + 1) << igi2_frame.nHeightMapPitchShift) + v7);
        LODWORD(igi2_frame.vTemp.vX) = *(char *)(igi2_frame.nU + 1 + LODWORD(v23) + 1 + ((LODWORD(v23) + 1) << igi2_frame.nHeightMapPitchShift) + v7);
        *(float *)&igi2_frame.nU = v27;
        igi2_frame.tPos.vZ = ((v22 - (double)SLODWORD(v23))
                 * (((double)SLODWORD(igi2_frame.vTemp.vX) - *(float *)&igi2_frame.nU) * igi2_frame.vPixScaleX
                  + *(float *)&igi2_frame.nU
                  - ((double)v25
                   + ((double)SLODWORD(v26) - (double)v25) * igi2_frame.vPixScaleX))
                 + (double)v25
                 + ((double)SLODWORD(v26) - (double)v25) * igi2_frame.vPixScaleX
                 - 64.0)
                * 256.0
                + igi2_frame.tPos.vZ;
      }
      v28 = v12[3];
      qmemcpy(&v17[-1], &igi2_frame.tPos, sizeof(struct real64x3_t));
      v29 = v12[2] + (v28 << 16);
      LODWORD(igi2_frame.vTemp.vX) = ((v29 >> 14) & 0x3F) - 24;
      igi2_frame.tPos.vY = (double)(int)(((v29 >> 20) & 0x3F) - 24);
      igi2_frame.tPos.vZ = (double)SLODWORD(igi2_frame.vTemp.vX);
      v30 = (double)(int)((v29 >> 26) - 24) * v14;
      v31 = igi2_frame.tPos.vY * v14;
      igi2_frame.tPos.vY = igi2_frame.tPos.vY * v14;
      igi2_frame.tPos.vZ = igi2_frame.tPos.vZ * v14;
      if ( igi2_frame.nFace )
        v30 = -v30;
      if ( igi2_frame.iFace )
      {
        *(double *)&igi2_frame.vTemp.vX = v31;
        if ( igi2_frame.v108 )
        {
          igi2_frame.tPos.vY = -v30;
          v30 = *(double *)&igi2_frame.vTemp.vX;
        }
        else
        {
          igi2_frame.tPos.vY = v30;
          v30 = -*(double *)&igi2_frame.vTemp.vX;
        }
      }
      else if ( igi2_frame.v108 )
      {
        v30 = -v30;
        igi2_frame.tPos.vY = -v31;
      }
      igi2_frame.tPos.vX = v30 + ptCubeCenter->vX;
      igi2_frame.tPos.vY = igi2_frame.tPos.vY + ptCubeCenter->vY;
      igi2_frame.tPos.vZ = igi2_frame.tPos.vZ + ptCubeCenter->vZ;
      if ( HeightMap_biHeightMap )
      {
        v32 = (igi2_frame.tPos.vX - *(float *)&igi2_frame.vMinDistSquared) * igi2_frame.vHeightMapScale;
        v33 = (igi2_frame.tPos.vY - *((float *)&igi2_frame.vMinDistSquared + 1)) * igi2_frame.vHeightMapScale;
        igi2_frame.nU = (__int64)v32;
        *(_QWORD *)&igi2_frame.vTemp.vX = (__int64)v33;
        LODWORD(v34) = (__int64)v33;
        igi2_frame.vTemp.vX = v34;
        v35 = (LODWORD(v34) << igi2_frame.nHeightMapPitchShift) + LODWORD(v34);
        v36 = *(char *)(v35 + igi2_frame.nU + v7);
        LODWORD(v37) = *(char *)(igi2_frame.nU + 1 + v35 + v7);
        igi2_frame.vPixScaleX = v32 - (double)igi2_frame.nU;
        igi2_frame.vTemp.vX = v37;
        v38 = (double)*(char *)(igi2_frame.nU + LODWORD(v34) + 1 + ((LODWORD(v34) + 1) << igi2_frame.nHeightMapPitchShift) + v7);
        LODWORD(igi2_frame.vTemp.vX) = *(char *)(igi2_frame.nU + 1 + LODWORD(v34) + 1 + ((LODWORD(v34) + 1) << igi2_frame.nHeightMapPitchShift) + v7);
        *(float *)&igi2_frame.nU = v38;
        igi2_frame.tPos.vZ = ((v33 - (double)SLODWORD(v34))
                 * (((double)SLODWORD(igi2_frame.vTemp.vX) - *(float *)&igi2_frame.nU) * igi2_frame.vPixScaleX
                  + *(float *)&igi2_frame.nU
                  - ((double)v36
                   + ((double)SLODWORD(v37) - (double)v36) * igi2_frame.vPixScaleX))
                 + (double)v36
                 + ((double)SLODWORD(v37) - (double)v36) * igi2_frame.vPixScaleX
                 - 64.0)
                * 256.0
                + igi2_frame.tPos.vZ;
      }
      v39 = v12[5];
      qmemcpy(v17, &igi2_frame.tPos, sizeof(struct real64x3_t));
      v40 = v12[4] + (v39 << 16);
      LODWORD(igi2_frame.vTemp.vX) = ((v40 >> 14) & 0x3F) - 24;
      igi2_frame.tPos.vY = (double)(int)(((v40 >> 20) & 0x3F) - 24);
      igi2_frame.tPos.vZ = (double)SLODWORD(igi2_frame.vTemp.vX);
      v41 = (double)(int)((v40 >> 26) - 24) * v14;
      v42 = igi2_frame.tPos.vY * v14;
      igi2_frame.tPos.vY = igi2_frame.tPos.vY * v14;
      igi2_frame.tPos.vZ = igi2_frame.tPos.vZ * v14;
      if ( igi2_frame.nFace )
        v41 = -v41;
      if ( igi2_frame.iFace )
      {
        *(double *)&igi2_frame.vTemp.vX = v42;
        if ( igi2_frame.v108 )
        {
          igi2_frame.tPos.vY = -v41;
          v41 = *(double *)&igi2_frame.vTemp.vX;
        }
        else
        {
          igi2_frame.tPos.vY = v41;
          v41 = -*(double *)&igi2_frame.vTemp.vX;
        }
      }
      else if ( igi2_frame.v108 )
      {
        v41 = -v41;
        igi2_frame.tPos.vY = -v42;
      }
      igi2_frame.tPos.vX = v41 + ptCubeCenter->vX;
      igi2_frame.tPos.vY = igi2_frame.tPos.vY + ptCubeCenter->vY;
      igi2_frame.tPos.vZ = igi2_frame.tPos.vZ + ptCubeCenter->vZ;
      if ( HeightMap_biHeightMap )
      {
        v43 = (igi2_frame.tPos.vX - *(float *)&igi2_frame.vMinDistSquared) * igi2_frame.vHeightMapScale;
        v44 = (igi2_frame.tPos.vY - *((float *)&igi2_frame.vMinDistSquared + 1)) * igi2_frame.vHeightMapScale;
        igi2_frame.nU = (__int64)v43;
        *(_QWORD *)&igi2_frame.vTemp.vX = (__int64)v44;
        LODWORD(v45) = (__int64)v44;
        igi2_frame.vTemp.vX = v45;
        v46 = (LODWORD(v45) << igi2_frame.nHeightMapPitchShift) + LODWORD(v45);
        v47 = *(char *)(v46 + igi2_frame.nU + v7);
        LODWORD(v48) = *(char *)(igi2_frame.nU + 1 + v46 + v7);
        igi2_frame.vPixScaleX = v43 - (double)igi2_frame.nU;
        igi2_frame.vTemp.vX = v48;
        v49 = (double)*(char *)(igi2_frame.nU + LODWORD(v45) + 1 + ((LODWORD(v45) + 1) << igi2_frame.nHeightMapPitchShift) + v7);
        LODWORD(igi2_frame.vTemp.vX) = *(char *)(igi2_frame.nU + 1 + LODWORD(v45) + 1 + ((LODWORD(v45) + 1) << igi2_frame.nHeightMapPitchShift) + v7);
        *(float *)&igi2_frame.nU = v49;
        igi2_frame.tPos.vZ = ((v44 - (double)SLODWORD(v45))
                 * (((double)SLODWORD(igi2_frame.vTemp.vX) - *(float *)&igi2_frame.nU) * igi2_frame.vPixScaleX
                  + *(float *)&igi2_frame.nU
                  - ((double)v47
                   + ((double)SLODWORD(v48) - (double)v47) * igi2_frame.vPixScaleX))
                 + (double)v47
                 + ((double)SLODWORD(v48) - (double)v47) * igi2_frame.vPixScaleX
                 - 64.0)
                * 256.0
                + igi2_frame.tPos.vZ;
      }
      v50 = v12[7];
      qmemcpy(&v17[1], &igi2_frame.tPos, sizeof(struct real64x3_t));
      v51 = v12[6] + (v50 << 16);
      LODWORD(igi2_frame.vTemp.vX) = ((v51 >> 14) & 0x3F) - 24;
      igi2_frame.tPos.vY = (double)(int)(((v51 >> 20) & 0x3F) - 24);
      igi2_frame.tPos.vZ = (double)SLODWORD(igi2_frame.vTemp.vX);
      v52 = (double)(int)((v51 >> 26) - 24) * v14;
      v53 = igi2_frame.tPos.vY * v14;
      igi2_frame.tPos.vY = igi2_frame.tPos.vY * v14;
      igi2_frame.tPos.vZ = igi2_frame.tPos.vZ * v14;
      if ( igi2_frame.nFace )
        v52 = -v52;
      if ( igi2_frame.iFace )
      {
        *(double *)&igi2_frame.vTemp.vX = v53;
        if ( igi2_frame.v108 )
        {
          igi2_frame.tPos.vY = -v52;
          v52 = *(double *)&igi2_frame.vTemp.vX;
        }
        else
        {
          igi2_frame.tPos.vY = v52;
          v52 = -*(double *)&igi2_frame.vTemp.vX;
        }
      }
      else if ( igi2_frame.v108 )
      {
        v52 = -v52;
        igi2_frame.tPos.vY = -v53;
      }
      igi2_frame.tPos.vX = v52 + ptCubeCenter->vX;
      igi2_frame.tPos.vY = igi2_frame.tPos.vY + ptCubeCenter->vY;
      igi2_frame.tPos.vZ = igi2_frame.tPos.vZ + ptCubeCenter->vZ;
      if ( HeightMap_biHeightMap )
      {
        v54 = (igi2_frame.tPos.vX - *(float *)&igi2_frame.vMinDistSquared) * igi2_frame.vHeightMapScale;
        v55 = (igi2_frame.tPos.vY - *((float *)&igi2_frame.vMinDistSquared + 1)) * igi2_frame.vHeightMapScale;
        igi2_frame.nU = (__int64)v54;
        *(_QWORD *)&igi2_frame.vTemp.vX = (__int64)v55;
        LODWORD(v56) = (__int64)v55;
        igi2_frame.vTemp.vX = v56;
        v57 = (LODWORD(v56) << igi2_frame.nHeightMapPitchShift) + LODWORD(v56);
        v58 = *(char *)(v57 + igi2_frame.nU + v7);
        LODWORD(v59) = *(char *)(igi2_frame.nU + 1 + v57 + v7);
        igi2_frame.vPixScaleX = v54 - (double)igi2_frame.nU;
        igi2_frame.vTemp.vX = v59;
        v60 = (double)*(char *)(igi2_frame.nU + LODWORD(v56) + 1 + ((LODWORD(v56) + 1) << igi2_frame.nHeightMapPitchShift) + v7);
        LODWORD(igi2_frame.vTemp.vX) = *(char *)(igi2_frame.nU + 1 + LODWORD(v56) + 1 + ((LODWORD(v56) + 1) << igi2_frame.nHeightMapPitchShift) + v7);
        *(float *)&igi2_frame.nU = v60;
        igi2_frame.tPos.vZ = ((v55 - (double)SLODWORD(v56))
                 * (((double)SLODWORD(igi2_frame.vTemp.vX) - *(float *)&igi2_frame.nU) * igi2_frame.vPixScaleX
                  + *(float *)&igi2_frame.nU
                  - ((double)v58
                   + ((double)SLODWORD(v59) - (double)v58) * igi2_frame.vPixScaleX))
                 + (double)v58
                 + ((double)SLODWORD(v59) - (double)v58) * igi2_frame.vPixScaleX
                 - 64.0)
                * 256.0
                + igi2_frame.tPos.vZ;
      }
      v61 = igi2_frame.v107;
      qmemcpy(&v17[2], &igi2_frame.tPos, sizeof(struct real64x3_t));
      igi2_frame.nFaceData += 4;
      v17 += 4;
      v12 += 8;
      LODWORD(igi2_frame.v107) = v61 + 4;
      if ( v61 + 4 >= igi2_frame.isHit )
        break;
      v16 = igi2_frame.v108;
      v15 = igi2_frame.nFace;
    }
    v13 = igi2_frame.nFaceData;
    v11 = bOrientation;
    v10 = igi2_frame.isHit;
    v9 = igi2_frame.ptFace;
  }
  if ( v13 < v10 )
  {
    v62 = v11 & 4;
    igi2_frame.iFace = v11 & 1;
    igi2_frame.nFace = v62;
    igi2_frame.v108 = v11 & 2;
    v63 = &igi2_frame.atVertex[v13];
    igi2_frame.isHit = v10 - v13;
    while ( 1 )
    {
      v64 = *v12 + (v12[1] << 16);
      LODWORD(igi2_frame.v107) = (v64 >> 26) - 24;
      v65 = (double)(int)igi2_frame.v107;
      LODWORD(igi2_frame.v107) = ((v64 >> 14) & 0x3F) - 24;
      igi2_frame.tPos.vY = (double)(int)(((v64 >> 20) & 0x3F) - 24);
      igi2_frame.tPos.vZ = (double)(int)igi2_frame.v107;
      v66 = v65 * v14;
      v67 = igi2_frame.tPos.vY * v14;
      igi2_frame.tPos.vY = igi2_frame.tPos.vY * v14;
      igi2_frame.tPos.vZ = igi2_frame.tPos.vZ * v14;
      if ( v62 )
        v66 = -v66;
      if ( igi2_frame.iFace )
      {
        *(double *)&igi2_frame.vTemp.vX = v67;
        if ( igi2_frame.v108 )
        {
          igi2_frame.tPos.vY = -v66;
          v66 = *(double *)&igi2_frame.vTemp.vX;
        }
        else
        {
          igi2_frame.tPos.vY = v66;
          v66 = -*(double *)&igi2_frame.vTemp.vX;
        }
      }
      else if ( igi2_frame.v108 )
      {
        v66 = -v66;
        igi2_frame.tPos.vY = -v67;
      }
      igi2_frame.tPos.vX = v66 + ptCubeCenter->vX;
      igi2_frame.tPos.vY = igi2_frame.tPos.vY + ptCubeCenter->vY;
      igi2_frame.tPos.vZ = igi2_frame.tPos.vZ + ptCubeCenter->vZ;
      if ( HeightMap_biHeightMap )
      {
        v68 = (igi2_frame.tPos.vX - *(float *)&igi2_frame.vMinDistSquared) * igi2_frame.vHeightMapScale;
        v69 = (igi2_frame.tPos.vY - *((float *)&igi2_frame.vMinDistSquared + 1)) * igi2_frame.vHeightMapScale;
        igi2_frame.nU = (__int64)v68;
        igi2_frame.v107 = (__int64)v69;
        LODWORD(igi2_frame.vTemp.vX) = (__int64)v69;
        v70 = (LODWORD(igi2_frame.vTemp.vX) << igi2_frame.nHeightMapPitchShift) + LODWORD(igi2_frame.vTemp.vX);
        v71 = *(char *)(v70 + igi2_frame.nU + v7);
        igi2_frame.vPixScaleX = v68 - (double)igi2_frame.nU;
        LODWORD(igi2_frame.v107) = *(char *)(igi2_frame.nU + 1 + v70 + v7);
        v72 = (double)(int)igi2_frame.v107;
        v73 = *(char *)(igi2_frame.nU + 1 + LODWORD(igi2_frame.vTemp.vX) + 1 + ((LODWORD(igi2_frame.vTemp.vX) + 1) << igi2_frame.nHeightMapPitchShift) + v7);
        LODWORD(igi2_frame.v107) = *(char *)(igi2_frame.nU + LODWORD(igi2_frame.vTemp.vX) + 1 + ((LODWORD(igi2_frame.vTemp.vX) + 1) << igi2_frame.nHeightMapPitchShift) + v7);
        v74 = (double)(int)igi2_frame.v107;
        LODWORD(igi2_frame.v107) = v73;
        *(float *)&igi2_frame.nU = v74;
        igi2_frame.tPos.vZ = ((v69 - (double)SLODWORD(igi2_frame.vTemp.vX))
                 * (((double)v73 - *(float *)&igi2_frame.nU) * igi2_frame.vPixScaleX
                  + *(float *)&igi2_frame.nU
                  - ((double)v71
                   + (v72 - (double)v71) * igi2_frame.vPixScaleX))
                 + (double)v71
                 + (v72 - (double)v71) * igi2_frame.vPixScaleX
                 - 64.0)
                * 256.0
                + igi2_frame.tPos.vZ;
      }
      v75 = v63;
      v12 += 2;
      ++v63;
      v77 = igi2_frame.isHit - 1;
      v76 = igi2_frame.isHit == 1;
      qmemcpy(v75, &igi2_frame.tPos, sizeof(struct real64x3_t));
      igi2_frame.isHit = v77;
      if ( v76 )
        break;
      v62 = igi2_frame.nFace;
    }
    v9 = igi2_frame.ptFace;
  }
  v78 = ptFastMesh->nFace;
  v79 = v9->nFace;
  nFace_low_high = (unsigned __int8)HIBYTE(LOWORD(v9->nFace));
  igi2_frame.nFaceData = LOWORD(v9->nFace) + (HIWORD(v9->nFace) << 16);
  v81 = v79;
  nFace_low_high *= 24;
  v82 = igi2_frame.atVertex[v81].vX + *(double *)((char *)&igi2_frame.atVertex[0].vX + nFace_low_high);
  igi2_frame.nFace = v78;
  v83 = v82 + igi2_frame.atVertex[BYTE2(igi2_frame.nFaceData)].vX;
  v84 = igi2_frame.atVertex[v81].vY + *(double *)((char *)&igi2_frame.atVertex[0].vY + nFace_low_high) + igi2_frame.atVertex[BYTE2(igi2_frame.nFaceData)].vY;
  v85 = igi2_frame.atVertex[v81].vZ + *(double *)((char *)&igi2_frame.atVertex[0].vZ + nFace_low_high) + igi2_frame.atVertex[BYTE2(igi2_frame.nFaceData)].vZ;
  igi2_frame.isHit = 0;
  igi2_frame.vMinDistSquared = 4.611686018427388e18;
  igi2_frame.iFace = 0;
  igi2_frame.tB.vX = v83 * 0.3333333333333333;
  igi2_frame.tB.vY = v84 * 0.3333333333333333;
  igi2_frame.tB.vZ = v85 * 0.3333333333333333;
  if ( v78 <= 0 )
    goto LABEL_67;
  while ( 1 )
  {
    igi2_frame.nFaceData = LOWORD(v9[igi2_frame.iFace].nFace) + (HIWORD(v9[igi2_frame.iFace].nFace) << 16);
    v87 = (unsigned __int8)igi2_frame.nFaceData;
    v88 = &igi2_frame.atVertex[v87];
    p_vY = &igi2_frame.atVertex[v87].vY;
    v90 = igi2_frame.atVertex[BYTE1(igi2_frame.nFaceData)].vX - igi2_frame.atVertex[v87].vX;
    v91 = igi2_frame.atVertex[BYTE1(igi2_frame.nFaceData)].vY - igi2_frame.atVertex[v87].vY;
    LODWORD(igi2_frame.v107) = &igi2_frame.atVertex[v87].vZ;
    igi2_frame.tVec0.vY = v91;
    igi2_frame.tVec0.vZ = igi2_frame.atVertex[BYTE1(igi2_frame.nFaceData)].vZ - igi2_frame.atVertex[v87].vZ;
    igi2_frame.tVec1.vX = igi2_frame.atVertex[BYTE2(igi2_frame.nFaceData)].vX - igi2_frame.atVertex[v87].vX;
    igi2_frame.tVec1.vY = igi2_frame.atVertex[BYTE2(igi2_frame.nFaceData)].vY - igi2_frame.atVertex[v87].vY;
    igi2_frame.tVec1.vZ = igi2_frame.atVertex[BYTE2(igi2_frame.nFaceData)].vZ - igi2_frame.atVertex[v87].vZ;
    v92 = igi2_frame.tVec1.vZ * v91 - igi2_frame.tVec1.vY * igi2_frame.tVec0.vZ;
    igi2_frame.v127[0] = v92;
    igi2_frame.v127[1] = -(igi2_frame.tVec1.vZ * v90 - igi2_frame.tVec1.vX * igi2_frame.tVec0.vZ);
    v93 = igi2_frame.tVec1.vY * v90 - igi2_frame.tVec1.vX * igi2_frame.tVec0.vY;
    igi2_frame.v127[2] = v93;
    qmemcpy(&igi2_frame.tReal64Normal, igi2_frame.v127, sizeof(igi2_frame.tReal64Normal));
    if ( v92 != 0.0 || igi2_frame.v127[1] != 0.0 || v93 != 0.0 )
    {
      v94 = sqrt(v92 * v92 + igi2_frame.v127[1] * igi2_frame.v127[1] + v93 * v93);
      v95 = v92;
      v96 = 1.0 / v94;
      igi2_frame.tReal64Normal.vX = v95 * v96;
      igi2_frame.tReal64Normal.vY = igi2_frame.tReal64Normal.vY * v96;
      igi2_frame.tReal64Normal.vZ = v96 * igi2_frame.tReal64Normal.vZ;
      igi2_frame.tReal32Vec0.vX = v90;
      igi2_frame.tReal32Vec0.vY = igi2_frame.tVec0.vY;
      igi2_frame.tReal32Vec0.vZ = igi2_frame.tVec0.vZ;
      igi2_frame.tReal32Vec1.vX = igi2_frame.tVec1.vX;
      igi2_frame.tReal32Vec1.vY = igi2_frame.tVec1.vY;
      igi2_frame.tReal32Vec1.vZ = igi2_frame.tVec1.vZ;
      igi2_frame.vTemp.vX = igi2_frame.tReal64Normal.vX;
      igi2_frame.vTemp.vY = igi2_frame.tReal64Normal.vY;
      igi2_frame.vTemp.vZ = igi2_frame.tReal64Normal.vZ;
      v97 = ptA->vX - v88->vX;
      *((float *)&igi2_frame.tPos.vX + 1) = ptA->vY - *p_vY;
      v98 = ptA->vZ - igi2_frame.atVertex[(unsigned __int8)igi2_frame.nFaceData].vZ;
      igi2_frame.tDirection.vX = igi2_frame.tB.vX - ptA->vX;
      igi2_frame.tDirection.vY = igi2_frame.tB.vY - ptA->vY;
      v99 = igi2_frame.tB.vZ - ptA->vZ;
      v100 = igi2_frame.vTemp.vZ * v99 + igi2_frame.tDirection.vY * igi2_frame.vTemp.vY + igi2_frame.tDirection.vX * igi2_frame.vTemp.vX;
      if ( v100 > 9.999999747378752e-06 || v100 < -9.999999747378752e-06 )
      {
        v101 = (v98 * igi2_frame.vTemp.vZ + *((float *)&igi2_frame.tPos.vX + 1) * igi2_frame.vTemp.vY + v97 * igi2_frame.vTemp.vX) / v100;
        igi2_frame.tTempHitPos.vX = v97 - igi2_frame.tDirection.vX * v101;
        igi2_frame.tTempHitPos.vY = *((float *)&igi2_frame.tPos.vX + 1) - igi2_frame.tDirection.vY * v101;
        igi2_frame.tTempHitPos.vZ = v98 - v101 * v99;
        if ( Real32x3_PointOnTriangle(nullptr, nullptr, &igi2_frame.tTempHitPos, &igi2_frame.tReal32Vec0, &igi2_frame.tReal32Vec1, &igi2_frame.vTemp) )
        {
          igi2_frame.tReal64HitDirection.vX = v88->vX - ptA->vX + igi2_frame.tTempHitPos.vX;
          igi2_frame.tReal64HitDirection.vY = *p_vY - ptA->vY + igi2_frame.tTempHitPos.vY;
          igi2_frame.tReal64HitDirection.vZ = *(double *)igi2_frame.v107 - ptA->vZ + igi2_frame.tTempHitPos.vZ;
          v102 = igi2_frame.tReal64HitDirection.vZ * igi2_frame.tReal64HitDirection.vZ
               + igi2_frame.tReal64HitDirection.vY * igi2_frame.tReal64HitDirection.vY
               + igi2_frame.tReal64HitDirection.vX * igi2_frame.tReal64HitDirection.vX;
          if ( igi2_frame.vMinDistSquared > v102 )
          {
            igi2_frame.vMinDistSquared = v102;
            igi2_frame.tHitNormal = igi2_frame.vTemp;
            igi2_frame.isHit = 1;
            qmemcpy(&igi2_frame.tHitDirection, &igi2_frame.tReal64HitDirection, sizeof(igi2_frame.tHitDirection));
          }
        }
      }
      else
      {
        memset(&igi2_frame.tTempHitPos, 0, sizeof(igi2_frame.tTempHitPos));
      }
    }
    if ( ++igi2_frame.iFace >= igi2_frame.nFace )
      break;
    v9 = igi2_frame.ptFace;
  }
  if ( igi2_frame.isHit )
  {
    *piEnterMaterial = (igi2_frame.tHitNormal.vZ * igi2_frame.tHitDirection.vZ
                      + igi2_frame.tHitNormal.vY * igi2_frame.tHitDirection.vY
                      + igi2_frame.tHitNormal.vX * igi2_frame.tHitDirection.vX)
                     * igi2_frame.vFlipBackFace > 0.0;
    return 1;
  }
  else
  {
LABEL_67:
    *piEnterMaterial = 0;
    return 1;
  }
}

// source: e/1/world.c:4680  [anchor-mhash]
struct QMaterial_t *__cdecl World_GetMaterialCubeIndex(
        struct WorldCube_t *ptCubeIndex,
        struct real64x3_t *ptPos,
        int nIteration)
{
  #pragma pack(push, 1)
  union
  {
    struct { int nZ; };
    struct { int nZa; };
    struct { char igi2_o2[4]; int nY; };
    struct { char igi2_o3[8]; int nCurrentRadius; };
    struct { char igi2_o4[12]; int nCubeCenterX; };
    struct { char igi2_o5[16]; struct CubeTree_s *ptTopOfTree; };
    struct { char igi2_o6[20]; int nX; };
    struct { char igi2_o7[24]; int nCubeCenterY; };
    struct { char igi2_o8[28]; int v30; };
    struct { char igi2_o9[32]; int nCubeCenterZ; };
    struct { char igi2_o10[36]; int v32; };
    struct { char igi2_o11[44]; struct real64x3_t tCubeCenter; };
    char igi2_extent[68];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct World_s *ptWorld; // ecx
  unsigned int nOrientation; // esi
  struct CubeTree_s *ptCubeTreeItem; // edi
  int nRadiusBit; // edx
  int vX; // ebp
  int vY; // ebx
  int v9; // ebp
  int v10; // eax
  int v11; // ecx
  int v12; // ebp
  int v13; // ecx
  unsigned __int8 v14; // al
  int v15; // ebx
  int v16; // eax
  unsigned __int8 bEnableData; // bl
  int v18; // edx
  int v19; // eax
  struct CubeItem0_MeshHeader_s *ptMesh; // ecx

  ptWorld = ptCubeIndex->ptWorld;
  igi2_frame.ptTopOfTree = ptWorld->ptCubeTree;
  nOrientation = ptCubeIndex->nOrientation;
  ptCubeTreeItem = ptCubeIndex->ptCubeTreeItem;
  igi2_frame.nCurrentRadius = ptCubeIndex->nRadius;
  nRadiusBit = ptCubeIndex->nRadiusBit;
  vX = (__int64)ptPos->vX;
  vY = (__int64)ptPos->vY;
  igi2_frame.nZ = (__int64)ptPos->vZ;
  if ( ptPos->vX < 0.0 && (double)(int)(__int64)ptPos->vX != ptPos->vX )
    --vX;
  if ( ptPos->vY < 0.0 && (double)(int)(__int64)ptPos->vY != ptPos->vY )
    --vY;
  if ( ptPos->vZ < 0.0 && (double)igi2_frame.nZ != ptPos->vZ )
    --igi2_frame.nZ;
  v9 = ptWorld->tOrigo.nX + vX;
  igi2_frame.nX = ptWorld->tOrigo.nX;
  v10 = ptWorld->tOrigo.nY;
  v11 = ptWorld->tOrigo.nZ;
  igi2_frame.v30 = v10;
  igi2_frame.nCubeCenterY = v10 + vY;
  igi2_frame.nCubeCenterZ = v11 + igi2_frame.nZ;
  igi2_frame.nY = (v10 + vY) ^ 0x40000000;
  igi2_frame.nZa = (v11 + igi2_frame.nZ) ^ 0x40000000;
  igi2_frame.v32 = v11;
  igi2_frame.nCubeCenterX = v9;
  v12 = v9 ^ 0x40000000;
  v13 = (4 * ((igi2_frame.nZa >> nRadiusBit) & 1))
      | World_abOrientationData[nOrientation][(v12 >> nRadiusBit) & 1 | (2 * ((igi2_frame.nY >> nRadiusBit) & 1))];
  if ( (ptCubeTreeItem->bEnableData & (unsigned __int8)(1 << v13)) != 0 )
  {
    do
    {
      if ( nIteration >= 16 )
        break;
      v14 = ptCubeTreeItem->abOrientation[v13];
      if ( nOrientation >= 4 )
      {
        v15 = ((_BYTE)nOrientation - v14) & 3;
        v16 = ((unsigned __int8)nOrientation ^ v14) & 4;
      }
      else
      {
        v15 = ((unsigned __int8)nOrientation ^ v14) & 4;
        v16 = ((_BYTE)nOrientation + v14) & 3;
      }
      nOrientation = v16 + v15;
      ptCubeTreeItem = &igi2_frame.ptTopOfTree[ptCubeTreeItem->aiChildIndex[v13]];
      --nRadiusBit;
      igi2_frame.nCurrentRadius >>= 1;
      v13 = (4 * ((igi2_frame.nZa >> nRadiusBit) & 1))
          | World_abOrientationData[v16][8 * v15 + ((v12 >> nRadiusBit) & 1 | (2 * ((igi2_frame.nY >> nRadiusBit) & 1)))];
      bEnableData = ptCubeTreeItem->bEnableData;
      ++nIteration;
    }
    while ( (bEnableData & (unsigned __int8)(1 << v13)) != 0 );
  }
  v18 = nIteration;
  v19 = ~((0x40000000 >> (nIteration - 1)) - 1);
  nIteration = igi2_frame.nCurrentRadius + (igi2_frame.nCubeCenterX & v19) - igi2_frame.nX;
  igi2_frame.tCubeCenter.vX = (double)nIteration;
  nIteration = igi2_frame.nCurrentRadius + (igi2_frame.nCubeCenterY & v19) - igi2_frame.v30;
  igi2_frame.tCubeCenter.vY = (double)nIteration;
  ptMesh = ptCubeTreeItem->ptMesh;
  nIteration = igi2_frame.nCurrentRadius + (igi2_frame.nCubeCenterZ & v19) - igi2_frame.v32;
  igi2_frame.tCubeCenter.vZ = (double)nIteration;
  World_GetMaterialTerrainMesh(ptMesh, &igi2_frame.tCubeCenter, ptPos, v18, (int *)&ptPos, nOrientation);
  return ptCubeIndex->ptWorld->aptQMaterial[(_DWORD)ptPos];
}

// source: e/1/world.c:4824  [anchor-mhash]
void __cdecl World_GetMaterial(
        struct World_s *ptWorld,
        struct QMaterial_t **pptMaterial,
        struct real64x3_t *ptPos,
        int nNumPoints,
        __int16 eQEvalEvent,
        struct CollisionEvaluateContext_s *ptEvalContext,
        unsigned int bQTaskGroup)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real64x3_t tMax; };
    struct { char igi2_o1[24]; struct real64x3_t tMin; };
    struct { char igi2_o2[52]; struct WorldCube_t tCubeIndex; };
    struct { char igi2_o3[88]; struct GetMaterialContext_s tGetMaterialContext; };
    char igi2_extent[240];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct CubeTree_s *ptCubeTree; // ecx
  int v8; // esi
  double vZ; // st7
  double *p_vZ; // edx
  int v11; // ebx
  int v12; // ebx
  int v13; // ebx
  int v14; // ebx
  int v15; // ebx
  int nX; // eax
  struct real64x3_t *v17; // ebx
  int v18; // esi
  unsigned int v19; // ecx
  struct QTaskList_s *ptTerrainQTaskList; // eax
  int v21; // edi
  int v22; // ebx
  int v23; // edi
  int v24; // esi
  struct QMaterial_t *v25; // eax
  struct QMaterial_t *MaterialCubeIndex; // eax

  ptCubeTree = ptWorld->ptCubeTree;
  HeightMap_nStackItem = 0;
  TerrainLightMap_nStackItem = 0;
  TextureModifier_nStackItem = 0;
  HeightMap_biHeightMap = 0;
  TextureModifier_biTextureModifier = 0;
  igi2_frame.tCubeIndex.ptWorld = ptWorld;
  if ( ptCubeTree )
    igi2_frame.tCubeIndex.ptCubeTreeItem = ptCubeTree + 1;
  else
    igi2_frame.tCubeIndex.ptCubeTreeItem = nullptr;
  qmemcpy(&igi2_frame.tMin, ptPos, sizeof(igi2_frame.tMin));
  qmemcpy(&igi2_frame.tMax, ptPos, sizeof(igi2_frame.tMax));
  v8 = 0;
  igi2_frame.tCubeIndex.nRadius = 0x40000000;
  igi2_frame.tCubeIndex.nRadiusBit = 30;
  memset(&igi2_frame.tCubeIndex.nOrientation, 0, 16);
  if ( nNumPoints > 0 )
  {
    vZ = igi2_frame.tMin.vZ;
    memset(igi2_frame.tGetMaterialContext.aisEvaluateTerrain, 1u, nNumPoints);
    p_vZ = &ptPos->vZ;
    do
    {
      if ( igi2_frame.tMax.vX >= *(p_vZ - 2) )
      {
        if ( igi2_frame.tMin.vX > *(p_vZ - 2) )
        {
          v12 = *((_DWORD *)p_vZ - 3);
          LODWORD(igi2_frame.tMin.vX) = *((_DWORD *)p_vZ - 4);
          HIDWORD(igi2_frame.tMin.vX) = v12;
        }
      }
      else
      {
        v11 = *((_DWORD *)p_vZ - 3);
        LODWORD(igi2_frame.tMax.vX) = *((_DWORD *)p_vZ - 4);
        HIDWORD(igi2_frame.tMax.vX) = v11;
      }
      if ( igi2_frame.tMax.vY >= *(p_vZ - 1) )
      {
        if ( igi2_frame.tMin.vY > *(p_vZ - 1) )
        {
          v14 = *((_DWORD *)p_vZ - 1);
          LODWORD(igi2_frame.tMin.vY) = *((_DWORD *)p_vZ - 2);
          HIDWORD(igi2_frame.tMin.vY) = v14;
        }
      }
      else
      {
        v13 = *((_DWORD *)p_vZ - 1);
        LODWORD(igi2_frame.tMax.vY) = *((_DWORD *)p_vZ - 2);
        HIDWORD(igi2_frame.tMax.vY) = v13;
      }
      if ( igi2_frame.tMax.vZ >= *p_vZ )
      {
        if ( vZ > *p_vZ )
          vZ = *p_vZ;
      }
      else
      {
        v15 = *((_DWORD *)p_vZ + 1);
        LODWORD(igi2_frame.tMax.vZ) = *(_DWORD *)p_vZ;
        HIDWORD(igi2_frame.tMax.vZ) = v15;
      }
      pptMaterial[v8++] = nullptr;
      p_vZ += 3;
    }
    while ( v8 < nNumPoints );
    igi2_frame.tMin.vZ = vZ;
  }
  nX = ptWorld->tOrigo.nX;
  igi2_frame.tMax.vY = igi2_frame.tMax.vY + 2.0;
  igi2_frame.tMax.vZ = igi2_frame.tMax.vZ + 2.0;
  igi2_frame.tMin.vY = igi2_frame.tMin.vY - 2.0;
  igi2_frame.tMin.vZ = igi2_frame.tMin.vZ - 2.0;
  _BitScanReverse(
    (unsigned int *)&nX,
    (nX + (__int64)(igi2_frame.tMin.vX - 2.0)) ^ (nX + (__int64)(igi2_frame.tMax.vX + 2.0))
  | (ptWorld->tOrigo.nY + (__int64)igi2_frame.tMin.vY) ^ (ptWorld->tOrigo.nY + (__int64)igi2_frame.tMax.vY)
  | (ptWorld->tOrigo.nZ + (__int64)igi2_frame.tMin.vZ) ^ (ptWorld->tOrigo.nZ + (__int64)igi2_frame.tMax.vZ));
  v17 = ptPos;
  v18 = 30 - nX;
  igi2_frame.tGetMaterialContext.nNumPoints = nNumPoints;
  igi2_frame.tGetMaterialContext.ptPos = ptPos;
  igi2_frame.tGetMaterialContext.pptQMaterial = pptMaterial;
  igi2_frame.tGetMaterialContext.eEvalQTaskEvent = eQEvalEvent;
  igi2_frame.tGetMaterialContext.ptEvalContext = ptEvalContext;
  igi2_frame.tGetMaterialContext.isAllowFlippedGroups = 0;
  if ( (bQTaskGroup & 0x7FFFFFFF) != 0 )
    World_TriggerQTaskEventXyzSpecificTree(
      ptWorld,
      12,
      &igi2_frame.tGetMaterialContext,
      ptPos,
      bQTaskGroup,
      WORLD_DYNCUBETREE_STATIONARY);
  v19 = bQTaskGroup & 0x80000000;
  if ( (bQTaskGroup & 0x80000000) != 0 )
  {
    ptTerrainQTaskList = ptWorld->ptTerrainQTaskList;
    if ( ptTerrainQTaskList )
    {
      v21 = 0;
      if ( ptTerrainQTaskList->nTask > 0 )
      {
        v22 = 8;
        do
        {
          ((void (__cdecl *)(_DWORD, struct GetMaterialContext_s *))QTask_aatQTaskFinalEvent[12][*(unsigned __int16 *)(*(int *)((char *)&ptTerrainQTaskList->nTask + v22) + 36)].pfHandler)(
            *(int *)((char *)&ptTerrainQTaskList->nTask + v22),
            &igi2_frame.tGetMaterialContext);
          ptTerrainQTaskList = ptWorld->ptTerrainQTaskList;
          ++v21;
          v22 += 4;
        }
        while ( v21 < ptTerrainQTaskList->nTask );
        v19 = bQTaskGroup & 0x80000000;
        v17 = ptPos;
      }
    }
  }
  if ( v19 && ptWorld->ptCubeTree )
  {
    if ( v18 > 16 )
      v18 = 16;
    v23 = World_TraverseWorldCubeTowardsPoint(ptWorld, &igi2_frame.tCubeIndex, &igi2_frame.tCubeIndex, v17, v18);
    v24 = 0;
    if ( nNumPoints > 0 )
    {
      while ( !igi2_frame.tGetMaterialContext.aisEvaluateTerrain[v24] )
      {
        if ( !pptMaterial[v24] )
        {
          MaterialCubeIndex = ptWorld->aptQMaterial[0];
LABEL_39:
          pptMaterial[v24] = MaterialCubeIndex;
        }
LABEL_40:
        ++v24;
        ++v17;
        if ( v24 >= nNumPoints )
          return;
      }
      v25 = pptMaterial[v24];
      if ( v25 && v25->vDensity != 0.0 )
        goto LABEL_40;
      MaterialCubeIndex = World_GetMaterialCubeIndex(&igi2_frame.tCubeIndex, v17, v23);
      goto LABEL_39;
    }
  }
}

// source: e/1/world.c:5023  [anchor-mhash]
struct QMaterial_t *__cdecl World_TraceLineStepPos(
        struct World_s *ptWorld,
        struct real64x3_t *ptIntersection,
        struct real64x3_t *ptStart,
        struct real64x3_t *ptStop,
        float vMaxStepLength,
        int nMaxSteps,
        unsigned int bQTaskGroup)
{
  #pragma pack(push, 1)
  union
  {
    struct { int nSteps; };
    struct { char igi2_o1[4]; __int64 ptStartMaterial; };
    struct { char igi2_o2[16]; struct real32x3_t tDelta; };
    struct { char igi2_o3[28]; struct real64x3_t tPos; };
    char igi2_extent[52];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v8; // st7
  int v9; // ebx
  double v10; // st7
  int v11; // esi
  struct QMaterial_t *result; // eax

  igi2_frame.tDelta.vX = ptStop->vX - ptStart->vX;
  igi2_frame.tDelta.vY = ptStop->vY - ptStart->vY;
  v8 = ptStop->vZ - ptStart->vZ;
  igi2_frame.tDelta.vZ = v8;
  igi2_frame.ptStartMaterial = (__int64)(sqrt(igi2_frame.tDelta.vX * igi2_frame.tDelta.vX + igi2_frame.tDelta.vY * igi2_frame.tDelta.vY + v8 * v8) / vMaxStepLength);
  v9 = igi2_frame.ptStartMaterial;
  igi2_frame.nSteps = igi2_frame.ptStartMaterial;
  if ( (int)igi2_frame.ptStartMaterial > nMaxSteps )
  {
    v9 = nMaxSteps;
    igi2_frame.nSteps = nMaxSteps;
  }
  if ( v9 < 2 )
  {
    v9 = 2;
    igi2_frame.nSteps = 2;
  }
  World_GetMaterial(ptWorld, (struct QMaterial_t **)&igi2_frame.ptStartMaterial, ptStart, 1, 512, nullptr, bQTaskGroup);
  v10 = 1.0 / (double)igi2_frame.nSteps;
  qmemcpy(&igi2_frame.tPos, ptStart, sizeof(igi2_frame.tPos));
  v11 = 1;
  igi2_frame.tDelta.vX = igi2_frame.tDelta.vX * v10;
  igi2_frame.tDelta.vY = igi2_frame.tDelta.vY * v10;
  igi2_frame.tDelta.vZ = v10 * igi2_frame.tDelta.vZ;
  while ( 1 )
  {
    igi2_frame.tPos.vX = igi2_frame.tDelta.vX + igi2_frame.tPos.vX;
    igi2_frame.tPos.vY = igi2_frame.tDelta.vY + igi2_frame.tPos.vY;
    igi2_frame.tPos.vZ = igi2_frame.tDelta.vZ + igi2_frame.tPos.vZ;
    World_GetMaterial(ptWorld, (struct QMaterial_t **)&igi2_frame.nSteps, &igi2_frame.tPos, 1, 512, nullptr, bQTaskGroup);
    result = (struct QMaterial_t *)igi2_frame.nSteps;
    if ( igi2_frame.nSteps != (_DWORD)igi2_frame.ptStartMaterial )
      break;
    if ( ++v11 > v9 )
      return nullptr;
  }
  qmemcpy(ptIntersection, &igi2_frame.tPos, sizeof(struct real64x3_t));
  return result;
}

// source: e/1/world.c:5115  [anchor-mhash]
char __cdecl World_TraceLineStep(
        struct World_s *ptWorld,
        struct real64x3_t *ptStart,
        struct real64x3_t *ptStop,
        float vMaxStepLength,
        int nMaxSteps,
        unsigned int bQTaskGroup)
{
  #pragma pack(push, 1)
  union
  {
    struct { int nSteps; };
    struct { char igi2_o1[4]; __int64 ptStartMaterial; };
    struct { char igi2_o2[16]; struct real32x3_t tDelta; };
    struct { char igi2_o3[28]; struct real64x3_t tPos; };
    char igi2_extent[52];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v7; // st7
  int v8; // ebx
  double v9; // st7
  int v10; // esi

  igi2_frame.tDelta.vX = ptStop->vX - ptStart->vX;
  igi2_frame.tDelta.vY = ptStop->vY - ptStart->vY;
  v7 = ptStop->vZ - ptStart->vZ;
  igi2_frame.tDelta.vZ = v7;
  igi2_frame.ptStartMaterial = (__int64)(sqrt(igi2_frame.tDelta.vX * igi2_frame.tDelta.vX + igi2_frame.tDelta.vY * igi2_frame.tDelta.vY + v7 * v7) / vMaxStepLength);
  v8 = igi2_frame.ptStartMaterial;
  igi2_frame.nSteps = igi2_frame.ptStartMaterial;
  if ( (int)igi2_frame.ptStartMaterial > nMaxSteps )
  {
    v8 = nMaxSteps;
    igi2_frame.nSteps = nMaxSteps;
  }
  if ( v8 < 2 )
  {
    v8 = 2;
    igi2_frame.nSteps = 2;
  }
  World_GetMaterial(ptWorld, (struct QMaterial_t **)&igi2_frame.ptStartMaterial, ptStart, 1, 512, nullptr, bQTaskGroup);
  v9 = 1.0 / (double)igi2_frame.nSteps;
  qmemcpy(&igi2_frame.tPos, ptStart, sizeof(igi2_frame.tPos));
  v10 = 1;
  igi2_frame.tDelta.vX = igi2_frame.tDelta.vX * v9;
  igi2_frame.tDelta.vY = igi2_frame.tDelta.vY * v9;
  igi2_frame.tDelta.vZ = v9 * igi2_frame.tDelta.vZ;
  while ( 1 )
  {
    igi2_frame.tPos.vX = igi2_frame.tDelta.vX + igi2_frame.tPos.vX;
    igi2_frame.tPos.vY = igi2_frame.tDelta.vY + igi2_frame.tPos.vY;
    igi2_frame.tPos.vZ = igi2_frame.tDelta.vZ + igi2_frame.tPos.vZ;
    World_GetMaterial(ptWorld, (struct QMaterial_t **)&igi2_frame.nSteps, &igi2_frame.tPos, 1, 512, nullptr, bQTaskGroup);
    if ( igi2_frame.nSteps != (_DWORD)igi2_frame.ptStartMaterial )
      break;
    if ( ++v10 > v8 )
      return 0;
  }
  return 1;
}

// source: e/1/world.c:5208  [anchor-callee]
void __cdecl World_GetNextZNoMaterial(
        struct World_s *ptWorld,
        struct QIntersection_s *ptIntersection,
        struct real64x3_t *ptStart,
        int nNumPoints,
        double *pvDistance,
        __int16 eEvalQTaskEvent,
        struct CollisionEvaluateContext_s *ptEvalContext,
        unsigned int bQTaskGroup)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real64x3_t tMax; };
    struct { char igi2_o1[24]; struct real64x3_t tMin; };
    struct { char igi2_o2[48]; int v27; };
    struct { char igi2_o3[52]; int v28; };
    struct { char igi2_o4[56]; int v29; };
    struct { char igi2_o5[60]; struct QIntersection_s *v30; };
    struct { char igi2_o6[64]; struct real64x3_t atEnd[20]; };
    char igi2_extent[548];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v8; // edx
  int v9; // ebp
  int *p_isHit; // ebx
  int v11; // ecx
  double *p_vZ; // eax
  double v13; // st7
  double vZ; // st7
  double *v15; // ecx
  int v16; // edx
  int v17; // esi
  int v18; // esi
  int v19; // esi
  int v20; // esi
  int v21; // esi
  int v22; // esi
  struct QTaskList_s *ptTerrainQTaskList; // eax
  int v24; // edi

  v8 = 0;
  v9 = nNumPoints;
  HeightMap_nStackItem = 0;
  TerrainLightMap_nStackItem = 0;
  TextureModifier_nStackItem = 0;
  HeightMap_biHeightMap = 0;
  TextureModifier_biTextureModifier = 0;
  if ( nNumPoints > 0 )
  {
    p_isHit = &ptIntersection->isHit;
    v11 = (char *)ptStart - (char *)igi2_frame.atEnd;
    p_vZ = &igi2_frame.atEnd[0].vZ;
    while ( 1 )
    {
      qmemcpy(p_vZ - 2, (char *)p_vZ + v11 - 16, 0x18u);
      ++v8;
      p_vZ += 3;
      v13 = pvDistance[v8 - 1];
      *p_isHit = 0;
      p_isHit += 30;
      *(p_vZ - 3) = v13 + *(p_vZ - 3);
      if ( v8 >= nNumPoints )
        break;
      v11 = (char *)ptStart - (char *)igi2_frame.atEnd;
    }
  }
  qmemcpy(&igi2_frame.tMin, ptStart, sizeof(igi2_frame.tMin));
  vZ = igi2_frame.tMin.vZ;
  qmemcpy(&igi2_frame.tMax, ptStart, sizeof(igi2_frame.tMax));
  if ( nNumPoints > 0 )
  {
    v15 = &ptStart->vZ;
    v16 = (char *)igi2_frame.atEnd - (char *)ptStart;
    do
    {
      if ( igi2_frame.tMax.vX >= *(v15 - 2) )
      {
        if ( igi2_frame.tMin.vX > *(v15 - 2) )
        {
          v18 = *((_DWORD *)v15 - 3);
          LODWORD(igi2_frame.tMin.vX) = *((_DWORD *)v15 - 4);
          HIDWORD(igi2_frame.tMin.vX) = v18;
        }
      }
      else
      {
        v17 = *((_DWORD *)v15 - 3);
        LODWORD(igi2_frame.tMax.vX) = *((_DWORD *)v15 - 4);
        HIDWORD(igi2_frame.tMax.vX) = v17;
      }
      if ( igi2_frame.tMax.vY >= *(v15 - 1) )
      {
        if ( igi2_frame.tMin.vY > *(v15 - 1) )
        {
          v20 = *((_DWORD *)v15 - 1);
          LODWORD(igi2_frame.tMin.vY) = *((_DWORD *)v15 - 2);
          HIDWORD(igi2_frame.tMin.vY) = v20;
        }
      }
      else
      {
        v19 = *((_DWORD *)v15 - 1);
        LODWORD(igi2_frame.tMax.vY) = *((_DWORD *)v15 - 2);
        HIDWORD(igi2_frame.tMax.vY) = v19;
      }
      if ( igi2_frame.tMax.vZ >= *v15 )
      {
        if ( vZ > *v15 )
          vZ = *v15;
      }
      else
      {
        v21 = *((_DWORD *)v15 + 1);
        LODWORD(igi2_frame.tMax.vZ) = *(_DWORD *)v15;
        HIDWORD(igi2_frame.tMax.vZ) = v21;
      }
      if ( igi2_frame.tMax.vZ >= *(double *)((char *)v15 + v16) )
      {
        if ( vZ > *(double *)((char *)v15 + v16) )
          vZ = *(double *)((char *)v15 + v16);
      }
      else
      {
        igi2_frame.tMax.vZ = *(double *)((char *)v15 + v16);
      }
      v15 += 3;
      --v9;
    }
    while ( v9 );
  }
  igi2_frame.tMax.vX = igi2_frame.tMax.vX + 2.0;
  igi2_frame.tMax.vY = igi2_frame.tMax.vY + 2.0;
  igi2_frame.tMax.vZ = igi2_frame.tMax.vZ + 16387.0;
  igi2_frame.tMin.vX = igi2_frame.tMin.vX - 2.0;
  igi2_frame.tMin.vY = igi2_frame.tMin.vY - 2.0;
  v22 = 0;
  nTRT = 0;
  if ( (bQTaskGroup & 0x7FFFFFFF) != 0 )
    World_TraceLines(
      ptWorld,
      ptIntersection,
      ptStart,
      igi2_frame.atEnd,
      nNumPoints,
      eEvalQTaskEvent,
      ptEvalContext,
      bQTaskGroup & 0x7FFFFFFF);
  if ( (bQTaskGroup & 0x80000000) != 0 )
  {
    ptTerrainQTaskList = ptWorld->ptTerrainQTaskList;
    if ( ptTerrainQTaskList )
    {
      *(_QWORD *)&igi2_frame.tMin.vX = __PAIR64__(igi2_frame.atEnd, (unsigned int)ptStart);
      WORD2(igi2_frame.tMin.vY) = eEvalQTaskEvent;
      *(_QWORD *)&igi2_frame.tMin.vZ = (unsigned int)ptEvalContext;
      igi2_frame.v30 = ptIntersection;
      LODWORD(igi2_frame.tMin.vY) = nNumPoints;
      igi2_frame.v28 = 0;
      igi2_frame.v27 = 0;
      igi2_frame.v29 = 1094861636;
      if ( ptTerrainQTaskList->nTask > 0 )
      {
        v24 = 8;
        do
        {
          ((void (__cdecl *)(_DWORD, struct real64x3_t *))QTask_aatQTaskFinalEvent[11][*(unsigned __int16 *)(*(int *)((char *)&ptTerrainQTaskList->nTask + v24) + 36)].pfHandler)(
            *(int *)((char *)&ptTerrainQTaskList->nTask + v24),
            &igi2_frame.tMin);
          ptTerrainQTaskList = ptWorld->ptTerrainQTaskList;
          ++v22;
          v24 += 4;
        }
        while ( v22 < ptTerrainQTaskList->nTask );
      }
    }
  }
}

// source: e/1/world.c:5396  [anchor-callee]
void __cdecl World_GetNextZ(
        struct World_s *ptWorld,
        struct QIntersection_s *ptIntersection,
        struct real64x3_t *ptStart,
        int nNumPoints,
        double *pvDistance,
        __int16 eEvalQTaskEvent,
        struct CollisionEvaluateContext_s *ptEvalContext,
        unsigned int bQTaskGroup)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real64x3_t tMax; };
    struct { char igi2_o1[24]; struct real64x3_t tMin; };
    struct { char igi2_o2[48]; int v27; };
    struct { char igi2_o3[52]; int v28; };
    struct { char igi2_o4[56]; int v29; };
    struct { char igi2_o5[60]; struct QIntersection_s *v30; };
    struct { char igi2_o6[64]; struct real64x3_t atEnd[20]; };
    char igi2_extent[548];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v8; // edx
  int v9; // ebp
  int *p_isHit; // ebx
  int v11; // ecx
  double *p_vZ; // eax
  double v13; // st7
  double vZ; // st7
  double *v15; // ecx
  int v16; // edx
  int v17; // esi
  int v18; // esi
  int v19; // esi
  int v20; // esi
  int v21; // esi
  struct QTaskList_s *ptTerrainQTaskList; // eax
  int v23; // esi
  int v24; // edi

  v8 = 0;
  v9 = nNumPoints;
  HeightMap_nStackItem = 0;
  TerrainLightMap_nStackItem = 0;
  TextureModifier_nStackItem = 0;
  HeightMap_biHeightMap = 0;
  TextureModifier_biTextureModifier = 0;
  if ( nNumPoints > 0 )
  {
    p_isHit = &ptIntersection->isHit;
    v11 = (char *)ptStart - (char *)igi2_frame.atEnd;
    p_vZ = &igi2_frame.atEnd[0].vZ;
    while ( 1 )
    {
      qmemcpy(p_vZ - 2, (char *)p_vZ + v11 - 16, 0x18u);
      ++v8;
      p_vZ += 3;
      v13 = pvDistance[v8 - 1];
      *p_isHit = 0;
      p_isHit += 30;
      *(p_vZ - 3) = v13 + *(p_vZ - 3);
      if ( v8 >= nNumPoints )
        break;
      v11 = (char *)ptStart - (char *)igi2_frame.atEnd;
    }
  }
  qmemcpy(&igi2_frame.tMin, ptStart, sizeof(igi2_frame.tMin));
  vZ = igi2_frame.tMin.vZ;
  qmemcpy(&igi2_frame.tMax, ptStart, sizeof(igi2_frame.tMax));
  if ( nNumPoints > 0 )
  {
    v15 = &ptStart->vZ;
    v16 = (char *)igi2_frame.atEnd - (char *)ptStart;
    do
    {
      if ( igi2_frame.tMax.vX >= *(v15 - 2) )
      {
        if ( igi2_frame.tMin.vX > *(v15 - 2) )
        {
          v18 = *((_DWORD *)v15 - 3);
          LODWORD(igi2_frame.tMin.vX) = *((_DWORD *)v15 - 4);
          HIDWORD(igi2_frame.tMin.vX) = v18;
        }
      }
      else
      {
        v17 = *((_DWORD *)v15 - 3);
        LODWORD(igi2_frame.tMax.vX) = *((_DWORD *)v15 - 4);
        HIDWORD(igi2_frame.tMax.vX) = v17;
      }
      if ( igi2_frame.tMax.vY >= *(v15 - 1) )
      {
        if ( igi2_frame.tMin.vY > *(v15 - 1) )
        {
          v20 = *((_DWORD *)v15 - 1);
          LODWORD(igi2_frame.tMin.vY) = *((_DWORD *)v15 - 2);
          HIDWORD(igi2_frame.tMin.vY) = v20;
        }
      }
      else
      {
        v19 = *((_DWORD *)v15 - 1);
        LODWORD(igi2_frame.tMax.vY) = *((_DWORD *)v15 - 2);
        HIDWORD(igi2_frame.tMax.vY) = v19;
      }
      if ( igi2_frame.tMax.vZ >= *v15 )
      {
        if ( vZ > *v15 )
          vZ = *v15;
      }
      else
      {
        v21 = *((_DWORD *)v15 + 1);
        LODWORD(igi2_frame.tMax.vZ) = *(_DWORD *)v15;
        HIDWORD(igi2_frame.tMax.vZ) = v21;
      }
      if ( igi2_frame.tMax.vZ >= *(double *)((char *)v15 + v16) )
      {
        if ( vZ > *(double *)((char *)v15 + v16) )
          vZ = *(double *)((char *)v15 + v16);
      }
      else
      {
        igi2_frame.tMax.vZ = *(double *)((char *)v15 + v16);
      }
      v15 += 3;
      --v9;
    }
    while ( v9 );
  }
  igi2_frame.tMax.vX = igi2_frame.tMax.vX + 2.0;
  igi2_frame.tMax.vY = igi2_frame.tMax.vY + 2.0;
  igi2_frame.tMax.vZ = igi2_frame.tMax.vZ + 16387.0;
  igi2_frame.tMin.vX = igi2_frame.tMin.vX - 2.0;
  igi2_frame.tMin.vY = igi2_frame.tMin.vY - 2.0;
  if ( (bQTaskGroup & 0x7FFFFFFF) != 0 )
    World_TraceLines(
      ptWorld,
      ptIntersection,
      ptStart,
      igi2_frame.atEnd,
      nNumPoints,
      eEvalQTaskEvent,
      ptEvalContext,
      bQTaskGroup & 0x7FFFFFFF);
  if ( (bQTaskGroup & 0x80000000) != 0 )
  {
    ptTerrainQTaskList = ptWorld->ptTerrainQTaskList;
    v23 = 0;
    if ( ptTerrainQTaskList )
    {
      *(_QWORD *)&igi2_frame.tMin.vX = __PAIR64__(igi2_frame.atEnd, (unsigned int)ptStart);
      WORD2(igi2_frame.tMin.vY) = eEvalQTaskEvent;
      *(_QWORD *)&igi2_frame.tMin.vZ = (unsigned int)ptEvalContext;
      igi2_frame.v30 = ptIntersection;
      LODWORD(igi2_frame.tMin.vY) = nNumPoints;
      igi2_frame.v28 = 0;
      igi2_frame.v27 = 0;
      igi2_frame.v29 = 1094861636;
      if ( ptTerrainQTaskList->nTask > 0 )
      {
        v24 = 8;
        do
        {
          ((void (__cdecl *)(_DWORD, struct real64x3_t *))QTask_aatQTaskFinalEvent[11][*(unsigned __int16 *)(*(int *)((char *)&ptTerrainQTaskList->nTask + v24) + 36)].pfHandler)(
            *(int *)((char *)&ptTerrainQTaskList->nTask + v24),
            &igi2_frame.tMin);
          ptTerrainQTaskList = ptWorld->ptTerrainQTaskList;
          ++v23;
          v24 += 4;
        }
        while ( v23 < ptTerrainQTaskList->nTask );
      }
    }
  }
}

// source: e/1/world.c:5580  [anchor-callee]
void __cdecl World_GetNextZSpecificMesh(
        struct World_s *ptWorld,
        struct QIntersection_s *ptIntersection,
        struct real64x3_t *ptStart,
        int nNumPoints,
        double *pvDistance,
        __int16 eEvalQTaskEvent,
        struct CollisionEvaluateContext_s *ptEvalContext,
        unsigned int bQTaskGroup,
        int iMesh)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real64x3_t tMax; };
    struct { char igi2_o1[24]; struct real64x3_t tMin; };
    struct { char igi2_o2[48]; int v28; };
    struct { char igi2_o3[52]; int v29; };
    struct { char igi2_o4[56]; int v30; };
    struct { char igi2_o5[60]; struct QIntersection_s *v31; };
    struct { char igi2_o6[64]; struct real64x3_t atEnd[20]; };
    char igi2_extent[544];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v9; // edx
  int v10; // ebp
  int *p_isHit; // ebx
  int v12; // ecx
  double *p_vZ; // eax
  double v14; // st7
  double vZ; // st7
  double *v16; // ecx
  int v17; // edx
  int v18; // esi
  int v19; // esi
  int v20; // esi
  int v21; // esi
  int v22; // esi
  struct QTaskList_s *ptTerrainQTaskList; // eax
  int v24; // esi
  int v25; // edi

  v9 = 0;
  v10 = nNumPoints;
  HeightMap_nStackItem = 0;
  TerrainLightMap_nStackItem = 0;
  TextureModifier_nStackItem = 0;
  HeightMap_biHeightMap = 0;
  TextureModifier_biTextureModifier = 0;
  if ( nNumPoints > 0 )
  {
    p_isHit = &ptIntersection->isHit;
    v12 = (char *)ptStart - (char *)igi2_frame.atEnd;
    p_vZ = &igi2_frame.atEnd[0].vZ;
    while ( 1 )
    {
      qmemcpy(p_vZ - 2, (char *)p_vZ + v12 - 16, 0x18u);
      ++v9;
      p_vZ += 3;
      v14 = pvDistance[v9 - 1];
      *p_isHit = 0;
      p_isHit += 30;
      *(p_vZ - 3) = v14 + *(p_vZ - 3);
      if ( v9 >= nNumPoints )
        break;
      v12 = (char *)ptStart - (char *)igi2_frame.atEnd;
    }
  }
  qmemcpy(&igi2_frame.tMin, ptStart, sizeof(igi2_frame.tMin));
  vZ = igi2_frame.tMin.vZ;
  qmemcpy(&igi2_frame.tMax, ptStart, sizeof(igi2_frame.tMax));
  if ( nNumPoints > 0 )
  {
    v16 = &ptStart->vZ;
    v17 = (char *)igi2_frame.atEnd - (char *)ptStart;
    do
    {
      if ( igi2_frame.tMax.vX >= *(v16 - 2) )
      {
        if ( igi2_frame.tMin.vX > *(v16 - 2) )
        {
          v19 = *((_DWORD *)v16 - 3);
          LODWORD(igi2_frame.tMin.vX) = *((_DWORD *)v16 - 4);
          HIDWORD(igi2_frame.tMin.vX) = v19;
        }
      }
      else
      {
        v18 = *((_DWORD *)v16 - 3);
        LODWORD(igi2_frame.tMax.vX) = *((_DWORD *)v16 - 4);
        HIDWORD(igi2_frame.tMax.vX) = v18;
      }
      if ( igi2_frame.tMax.vY >= *(v16 - 1) )
      {
        if ( igi2_frame.tMin.vY > *(v16 - 1) )
        {
          v21 = *((_DWORD *)v16 - 1);
          LODWORD(igi2_frame.tMin.vY) = *((_DWORD *)v16 - 2);
          HIDWORD(igi2_frame.tMin.vY) = v21;
        }
      }
      else
      {
        v20 = *((_DWORD *)v16 - 1);
        LODWORD(igi2_frame.tMax.vY) = *((_DWORD *)v16 - 2);
        HIDWORD(igi2_frame.tMax.vY) = v20;
      }
      if ( igi2_frame.tMax.vZ >= *v16 )
      {
        if ( vZ > *v16 )
          vZ = *v16;
      }
      else
      {
        v22 = *((_DWORD *)v16 + 1);
        LODWORD(igi2_frame.tMax.vZ) = *(_DWORD *)v16;
        HIDWORD(igi2_frame.tMax.vZ) = v22;
      }
      if ( igi2_frame.tMax.vZ >= *(double *)((char *)v16 + v17) )
      {
        if ( vZ > *(double *)((char *)v16 + v17) )
          vZ = *(double *)((char *)v16 + v17);
      }
      else
      {
        igi2_frame.tMax.vZ = *(double *)((char *)v16 + v17);
      }
      v16 += 3;
      --v10;
    }
    while ( v10 );
  }
  igi2_frame.tMax.vX = igi2_frame.tMax.vX + 2.0;
  igi2_frame.tMax.vY = igi2_frame.tMax.vY + 2.0;
  igi2_frame.tMax.vZ = igi2_frame.tMax.vZ + 16387.0;
  igi2_frame.tMin.vX = igi2_frame.tMin.vX - 2.0;
  igi2_frame.tMin.vY = igi2_frame.tMin.vY - 2.0;
  if ( (bQTaskGroup & 0x7FFFFFFF) != 0 )
    World_TraceLinesSpecificMesh(
      ptWorld,
      ptIntersection,
      ptStart,
      igi2_frame.atEnd,
      nNumPoints,
      eEvalQTaskEvent,
      ptEvalContext,
      bQTaskGroup & 0x7FFFFFFF,
      iMesh);
  if ( (bQTaskGroup & 0x80000000) != 0 )
  {
    ptTerrainQTaskList = ptWorld->ptTerrainQTaskList;
    v24 = 0;
    if ( ptTerrainQTaskList )
    {
      *(_QWORD *)&igi2_frame.tMin.vX = __PAIR64__(igi2_frame.atEnd, (unsigned int)ptStart);
      WORD2(igi2_frame.tMin.vY) = eEvalQTaskEvent;
      LODWORD(igi2_frame.tMin.vZ) = ptEvalContext;
      igi2_frame.v31 = ptIntersection;
      LODWORD(igi2_frame.tMin.vY) = nNumPoints;
      HIDWORD(igi2_frame.tMin.vZ) = iMesh;
      igi2_frame.v29 = 0;
      igi2_frame.v28 = 0;
      igi2_frame.v30 = 1094861636;
      if ( ptTerrainQTaskList->nTask > 0 )
      {
        v25 = 8;
        do
        {
          ((void (__cdecl *)(_DWORD, struct real64x3_t *))QTask_aatQTaskFinalEvent[11][*(unsigned __int16 *)(*(int *)((char *)&ptTerrainQTaskList->nTask + v25) + 36)].pfHandler)(
            *(int *)((char *)&ptTerrainQTaskList->nTask + v25),
            &igi2_frame.tMin);
          ptTerrainQTaskList = ptWorld->ptTerrainQTaskList;
          ++v24;
          v25 += 4;
        }
        while ( v24 < ptTerrainQTaskList->nTask );
      }
    }
  }
}

// source: e/1/world.c:5765  [anchor-callee]
struct real64x3_t *__cdecl World_TraceLines(
        struct World_s *ptWorld,
        struct QIntersection_s *ptIntersection,
        struct real64x3_t *ptStart,
        struct real64x3_t *ptEnd,
        int nNumPoints,
        __int16 eQEvalEvent,
        struct CollisionEvaluateContext_s *ptEvalContext,
        unsigned int bQTaskGroup)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real64x3_t *v30; };
    struct { char igi2_o1[4]; int v31; };
    struct { char igi2_o2[8]; int isTraceAlongZ; };
    struct { char igi2_o3[12]; struct real64x3_t tMin; };
    struct { char igi2_o4[36]; struct real64x3_t tMax; };
    struct { char igi2_o5[60]; struct TraceLinesContext_s tTraceContext; };
    char igi2_extent[104];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct real64x3_t *v8; // ebp
  struct real64x3_t *result; // eax
  double vZ; // st7
  struct real64x3_t *p_tPos; // edi
  int v13; // ecx
  int vX_high; // ecx
  int v15; // ecx
  int vY_high; // ecx
  int vZ_high; // ecx
  int v18; // ecx
  int v19; // ecx
  int v20; // ecx
  int v21; // ecx
  int v22; // ecx
  int v23; // eax
  unsigned int v24; // eax
  struct real64x3_t *v25; // ebp
  struct real64x3_t *v26; // ebx
  int v27; // edi
  int v28; // esi
  int v29; // edi

  v8 = ptStart;
  result = (struct real64x3_t *)nNumPoints;
  igi2_frame.isTraceAlongZ = 1;
  if ( nNumPoints )
  {
    ++World_nTraceLines;
    World_nTraceLinesActual += nNumPoints;
    qmemcpy(&igi2_frame.tMax, ptStart, sizeof(igi2_frame.tMax));
    vZ = igi2_frame.tMax.vZ;
    qmemcpy(&igi2_frame.tMin, ptStart, sizeof(igi2_frame.tMin));
    if ( nNumPoints > 0 )
    {
      p_tPos = &ptIntersection->tPos;
      igi2_frame.v30 = &ptIntersection->tPos;
      igi2_frame.v31 = nNumPoints;
      while ( 1 )
      {
        if ( v8->vX != ptEnd->vX || v8->vY != ptEnd->vY )
          igi2_frame.isTraceAlongZ = 0;
        if ( v8->vX <= igi2_frame.tMax.vX )
        {
          if ( v8->vX < igi2_frame.tMin.vX )
          {
            vX_high = HIDWORD(v8->vX);
            LODWORD(igi2_frame.tMin.vX) = LODWORD(v8->vX);
            HIDWORD(igi2_frame.tMin.vX) = vX_high;
          }
        }
        else
        {
          v13 = HIDWORD(v8->vX);
          LODWORD(igi2_frame.tMax.vX) = LODWORD(v8->vX);
          HIDWORD(igi2_frame.tMax.vX) = v13;
        }
        if ( v8->vY <= igi2_frame.tMax.vY )
        {
          if ( v8->vY < igi2_frame.tMin.vY )
          {
            vY_high = HIDWORD(v8->vY);
            LODWORD(igi2_frame.tMin.vY) = LODWORD(v8->vY);
            HIDWORD(igi2_frame.tMin.vY) = vY_high;
          }
        }
        else
        {
          v15 = HIDWORD(v8->vY);
          LODWORD(igi2_frame.tMax.vY) = LODWORD(v8->vY);
          HIDWORD(igi2_frame.tMax.vY) = v15;
        }
        if ( vZ >= v8->vZ )
        {
          if ( v8->vZ < igi2_frame.tMin.vZ )
          {
            vZ_high = HIDWORD(v8->vZ);
            LODWORD(igi2_frame.tMin.vZ) = LODWORD(v8->vZ);
            HIDWORD(igi2_frame.tMin.vZ) = vZ_high;
          }
        }
        else
        {
          vZ = v8->vZ;
        }
        if ( ptEnd->vX <= igi2_frame.tMax.vX )
        {
          if ( ptEnd->vX < igi2_frame.tMin.vX )
          {
            v19 = HIDWORD(ptEnd->vX);
            LODWORD(igi2_frame.tMin.vX) = LODWORD(ptEnd->vX);
            HIDWORD(igi2_frame.tMin.vX) = v19;
          }
        }
        else
        {
          v18 = HIDWORD(ptEnd->vX);
          LODWORD(igi2_frame.tMax.vX) = LODWORD(ptEnd->vX);
          HIDWORD(igi2_frame.tMax.vX) = v18;
        }
        if ( ptEnd->vY <= igi2_frame.tMax.vY )
        {
          if ( ptEnd->vY < igi2_frame.tMin.vY )
          {
            v21 = HIDWORD(ptEnd->vY);
            LODWORD(igi2_frame.tMin.vY) = LODWORD(ptEnd->vY);
            HIDWORD(igi2_frame.tMin.vY) = v21;
          }
        }
        else
        {
          v20 = HIDWORD(ptEnd->vY);
          LODWORD(igi2_frame.tMax.vY) = LODWORD(ptEnd->vY);
          HIDWORD(igi2_frame.tMax.vY) = v20;
        }
        if ( vZ >= ptEnd->vZ )
        {
          if ( ptEnd->vZ < igi2_frame.tMin.vZ )
          {
            v22 = HIDWORD(ptEnd->vZ);
            LODWORD(igi2_frame.tMin.vZ) = LODWORD(ptEnd->vZ);
            HIDWORD(igi2_frame.tMin.vZ) = v22;
          }
        }
        else
        {
          vZ = ptEnd->vZ;
        }
        v23 = igi2_frame.v31;
        ptIntersection->ptHitObj = nullptr;
        HIDWORD(p_tPos[3].vY) = 0;
        qmemcpy(p_tPos, ptEnd, sizeof(struct real64x3_t));
        ++v8;
        ++ptEnd;
        ++ptIntersection;
        igi2_frame.v30 += 5;
        --igi2_frame.v31;
        if ( v23 == 1 )
          break;
        p_tPos = igi2_frame.v30;
      }
      result = (struct real64x3_t *)nNumPoints;
    }
    v24 = 24 * (_DWORD)result;
    igi2_frame.tMax.vX = igi2_frame.tMax.vX + 2.0;
    v25 = &v8[(int)v24 / (int)0xFFFFFFE8];
    v26 = &ptEnd[(int)v24 / (int)0xFFFFFFE8];
    igi2_frame.tTraceContext.eEvalQTaskEvent = eQEvalEvent;
    result = (struct real64x3_t *)nNumPoints;
    igi2_frame.tMax.vY = igi2_frame.tMax.vY + 2.0;
    igi2_frame.tTraceContext.ptEvalContext = ptEvalContext;
    igi2_frame.tMax.vZ = vZ + 16387.0;
    igi2_frame.tMin.vX = igi2_frame.tMin.vX - 2.0;
    v27 = 0;
    igi2_frame.tTraceContext.ptStart = v25;
    igi2_frame.tTraceContext.ptEnd = v26;
    igi2_frame.tMin.vY = igi2_frame.tMin.vY - 2.0;
    igi2_frame.tTraceContext.ptIntersection = &ptIntersection[-nNumPoints];
    igi2_frame.tTraceContext.nNumLines = nNumPoints;
    memset(&igi2_frame.tTraceContext.iMesh, 0, 12);
    igi2_frame.tMin.vZ = igi2_frame.tMin.vZ - 16387.0;
    igi2_frame.tTraceContext.nValidationNumber = 1094861636;
    if ( (bQTaskGroup & 0x7FFFFFFF) != 0 )
    {
      if ( igi2_frame.isTraceAlongZ )
      {
        do
        {
          if ( !v27 )
            result = (struct real64x3_t *)World_TriggerQTaskEventMinMaxXyzSpecificTree(
                                            ptWorld,
                                            11,
                                            &igi2_frame.tTraceContext,
                                            &igi2_frame.tMin,
                                            &igi2_frame.tMax,
                                            bQTaskGroup,
                                            WORLD_DYNCUBETREE_STATIONARY);
          ++v27;
        }
        while ( v27 < 1 );
      }
      else
      {
        do
        {
          if ( !v27 )
          {
            World_TriggerQTaskEventAlongLineSpecificTree(
              ptWorld,
              10,
              &igi2_frame.tTraceContext,
              v25,
              v26,
              (int)result,
              bQTaskGroup,
              WORLD_DYNCUBETREE_STATIONARY);
            result = (struct real64x3_t *)nNumPoints;
          }
          ++v27;
        }
        while ( v27 < 1 );
      }
    }
    if ( (bQTaskGroup & 0x80000000) != 0 )
    {
      result = (struct real64x3_t *)ptWorld->ptTerrainQTaskList;
      if ( result )
      {
        v28 = 0;
        if ( SLODWORD(result->vX) > 0 )
        {
          v29 = 8;
          do
          {
            ((void (__cdecl *)(_DWORD, struct TraceLinesContext_s *))QTask_aatQTaskFinalEvent[10][*(unsigned __int16 *)(*(_DWORD *)((char *)&result->vX + v29) + 36)].pfHandler)(
              *(_DWORD *)((char *)&result->vX + v29),
              &igi2_frame.tTraceContext);
            result = (struct real64x3_t *)ptWorld->ptTerrainQTaskList;
            ++v28;
            v29 += 4;
          }
          while ( v28 < SLODWORD(result->vX) );
        }
      }
    }
  }
  return result;
}

// source: e/1/world.c:5978  [anchor-callee]
struct real64x3_t *__cdecl World_TraceLinesSpecificMesh(
        struct World_s *ptWorld,
        struct QIntersection_s *ptIntersection,
        struct real64x3_t *ptStart,
        struct real64x3_t *ptEnd,
        int nNumPoints,
        __int16 eQEvalEvent,
        struct CollisionEvaluateContext_s *ptEvalContext,
        unsigned int bQTaskGroup,
        int iMesh)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real64x3_t *v31; };
    struct { char igi2_o1[4]; int v32; };
    struct { char igi2_o2[8]; int isTraceAlongZ; };
    struct { char igi2_o3[12]; struct real64x3_t tMin; };
    struct { char igi2_o4[36]; struct real64x3_t tMax; };
    struct { char igi2_o5[60]; struct TraceLinesContext_s tTraceContext; };
    char igi2_extent[100];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct real64x3_t *v9; // ebp
  struct real64x3_t *result; // eax
  double vZ; // st7
  struct real64x3_t *p_tPos; // edi
  int v14; // ecx
  int vX_high; // ecx
  int v16; // ecx
  int vY_high; // ecx
  int vZ_high; // ecx
  int v19; // ecx
  int v20; // ecx
  int v21; // ecx
  int v22; // ecx
  int v23; // ecx
  int v24; // eax
  unsigned int v25; // eax
  struct real64x3_t *v26; // ebp
  struct real64x3_t *v27; // ebx
  int v28; // edi
  int v29; // esi
  int v30; // edi

  v9 = ptStart;
  result = (struct real64x3_t *)nNumPoints;
  igi2_frame.isTraceAlongZ = 1;
  if ( nNumPoints )
  {
    ++World_nTraceLines;
    World_nTraceLinesActual += nNumPoints;
    qmemcpy(&igi2_frame.tMax, ptStart, sizeof(igi2_frame.tMax));
    vZ = igi2_frame.tMax.vZ;
    qmemcpy(&igi2_frame.tMin, ptStart, sizeof(igi2_frame.tMin));
    if ( nNumPoints > 0 )
    {
      p_tPos = &ptIntersection->tPos;
      igi2_frame.v31 = &ptIntersection->tPos;
      igi2_frame.v32 = nNumPoints;
      while ( 1 )
      {
        if ( v9->vX != ptEnd->vX || v9->vY != ptEnd->vY )
          igi2_frame.isTraceAlongZ = 0;
        if ( v9->vX <= igi2_frame.tMax.vX )
        {
          if ( v9->vX < igi2_frame.tMin.vX )
          {
            vX_high = HIDWORD(v9->vX);
            LODWORD(igi2_frame.tMin.vX) = LODWORD(v9->vX);
            HIDWORD(igi2_frame.tMin.vX) = vX_high;
          }
        }
        else
        {
          v14 = HIDWORD(v9->vX);
          LODWORD(igi2_frame.tMax.vX) = LODWORD(v9->vX);
          HIDWORD(igi2_frame.tMax.vX) = v14;
        }
        if ( v9->vY <= igi2_frame.tMax.vY )
        {
          if ( v9->vY < igi2_frame.tMin.vY )
          {
            vY_high = HIDWORD(v9->vY);
            LODWORD(igi2_frame.tMin.vY) = LODWORD(v9->vY);
            HIDWORD(igi2_frame.tMin.vY) = vY_high;
          }
        }
        else
        {
          v16 = HIDWORD(v9->vY);
          LODWORD(igi2_frame.tMax.vY) = LODWORD(v9->vY);
          HIDWORD(igi2_frame.tMax.vY) = v16;
        }
        if ( vZ >= v9->vZ )
        {
          if ( v9->vZ < igi2_frame.tMin.vZ )
          {
            vZ_high = HIDWORD(v9->vZ);
            LODWORD(igi2_frame.tMin.vZ) = LODWORD(v9->vZ);
            HIDWORD(igi2_frame.tMin.vZ) = vZ_high;
          }
        }
        else
        {
          vZ = v9->vZ;
        }
        if ( ptEnd->vX <= igi2_frame.tMax.vX )
        {
          if ( ptEnd->vX < igi2_frame.tMin.vX )
          {
            v20 = HIDWORD(ptEnd->vX);
            LODWORD(igi2_frame.tMin.vX) = LODWORD(ptEnd->vX);
            HIDWORD(igi2_frame.tMin.vX) = v20;
          }
        }
        else
        {
          v19 = HIDWORD(ptEnd->vX);
          LODWORD(igi2_frame.tMax.vX) = LODWORD(ptEnd->vX);
          HIDWORD(igi2_frame.tMax.vX) = v19;
        }
        if ( ptEnd->vY <= igi2_frame.tMax.vY )
        {
          if ( ptEnd->vY < igi2_frame.tMin.vY )
          {
            v22 = HIDWORD(ptEnd->vY);
            LODWORD(igi2_frame.tMin.vY) = LODWORD(ptEnd->vY);
            HIDWORD(igi2_frame.tMin.vY) = v22;
          }
        }
        else
        {
          v21 = HIDWORD(ptEnd->vY);
          LODWORD(igi2_frame.tMax.vY) = LODWORD(ptEnd->vY);
          HIDWORD(igi2_frame.tMax.vY) = v21;
        }
        if ( vZ >= ptEnd->vZ )
        {
          if ( ptEnd->vZ < igi2_frame.tMin.vZ )
          {
            v23 = HIDWORD(ptEnd->vZ);
            LODWORD(igi2_frame.tMin.vZ) = LODWORD(ptEnd->vZ);
            HIDWORD(igi2_frame.tMin.vZ) = v23;
          }
        }
        else
        {
          vZ = ptEnd->vZ;
        }
        v24 = igi2_frame.v32;
        ptIntersection->ptHitObj = nullptr;
        HIDWORD(p_tPos[3].vY) = 0;
        qmemcpy(p_tPos, ptEnd, sizeof(struct real64x3_t));
        ++v9;
        ++ptEnd;
        ++ptIntersection;
        igi2_frame.v31 += 5;
        --igi2_frame.v32;
        if ( v24 == 1 )
          break;
        p_tPos = igi2_frame.v31;
      }
      result = (struct real64x3_t *)nNumPoints;
    }
    v25 = 24 * (_DWORD)result;
    igi2_frame.tMax.vX = igi2_frame.tMax.vX + 2.0;
    v26 = &v9[(int)v25 / (int)0xFFFFFFE8];
    v27 = &ptEnd[(int)v25 / (int)0xFFFFFFE8];
    igi2_frame.tTraceContext.eEvalQTaskEvent = eQEvalEvent;
    result = (struct real64x3_t *)nNumPoints;
    igi2_frame.tMax.vY = igi2_frame.tMax.vY + 2.0;
    igi2_frame.tTraceContext.ptEvalContext = ptEvalContext;
    igi2_frame.tMax.vZ = vZ + 16387.0;
    igi2_frame.tMin.vX = igi2_frame.tMin.vX - 2.0;
    v28 = 0;
    igi2_frame.tTraceContext.ptIntersection = &ptIntersection[-nNumPoints];
    igi2_frame.tMin.vY = igi2_frame.tMin.vY - 2.0;
    igi2_frame.tTraceContext.ptStart = v26;
    igi2_frame.tTraceContext.ptEnd = v27;
    igi2_frame.tTraceContext.nNumLines = nNumPoints;
    igi2_frame.tTraceContext.iMesh = iMesh;
    igi2_frame.tTraceContext.iIgnoreMaterial = 0;
    igi2_frame.tMin.vZ = igi2_frame.tMin.vZ - 16387.0;
    igi2_frame.tTraceContext.isTracePortals = 0;
    igi2_frame.tTraceContext.nValidationNumber = 1094861636;
    if ( (bQTaskGroup & 0x7FFFFFFF) != 0 )
    {
      if ( igi2_frame.isTraceAlongZ )
      {
        do
        {
          if ( !v28 )
            result = (struct real64x3_t *)World_TriggerQTaskEventMinMaxXyzSpecificTree(
                                            ptWorld,
                                            11,
                                            &igi2_frame.tTraceContext,
                                            &igi2_frame.tMin,
                                            &igi2_frame.tMax,
                                            bQTaskGroup,
                                            WORLD_DYNCUBETREE_STATIONARY);
          ++v28;
        }
        while ( v28 < 1 );
      }
      else
      {
        do
        {
          if ( !v28 )
          {
            World_TriggerQTaskEventAlongLineSpecificTree(
              ptWorld,
              10,
              &igi2_frame.tTraceContext,
              v26,
              v27,
              (int)result,
              bQTaskGroup,
              WORLD_DYNCUBETREE_STATIONARY);
            result = (struct real64x3_t *)nNumPoints;
          }
          ++v28;
        }
        while ( v28 < 1 );
      }
    }
    if ( (bQTaskGroup & 0x80000000) != 0 )
    {
      result = (struct real64x3_t *)ptWorld->ptTerrainQTaskList;
      if ( result )
      {
        v29 = 0;
        if ( SLODWORD(result->vX) > 0 )
        {
          v30 = 8;
          do
          {
            ((void (__cdecl *)(_DWORD, struct TraceLinesContext_s *))QTask_aatQTaskFinalEvent[10][*(unsigned __int16 *)(*(_DWORD *)((char *)&result->vX + v30) + 36)].pfHandler)(
              *(_DWORD *)((char *)&result->vX + v30),
              &igi2_frame.tTraceContext);
            result = (struct real64x3_t *)ptWorld->ptTerrainQTaskList;
            ++v29;
            v30 += 4;
          }
          while ( v29 < SLODWORD(result->vX) );
        }
      }
    }
  }
  return result;
}

// source: e/1/world.c:6185  [anchor-callee]
struct World_s *__cdecl World_TriggerQTaskEventXyzSpecificTree(
        struct World_s *ptWorld,
        __int16 eQTaskEvent,
        void *pxContext,
        struct real64x3_t *ptPos,
        unsigned int bQTaskGroup,
        enum DynCubeTree_e eDynCubeTree)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct CallQueue_t tCallQueue; };
    struct { char igi2_o1[8]; struct int32x3_t tIntPos; };
    struct { char igi2_o2[24]; struct real64x3_t tRealPos; };
    char igi2_extent[48];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int nY; // edx
  double vY; // st7
  int nX; // esi
  int v10; // edi
  int v11; // eax
  unsigned int v12; // esi
  double vZ; // st7
  struct CallQueueItem_s *v14; // ebp
  int v15; // ecx
  struct DynCubeTreeItem_s *v16; // edi
  double v17; // st7
  int v18; // ecx
  double v19; // st6
  struct DynCubeObj_s *ptDynCubeObj; // edx
  int i; // eax
  int eQTaskType; // esi
  struct CallQueueItem_s *v23; // eax
  struct World_s *result; // eax

  igi2_frame.tCallQueue.pptLast = (struct CallQueueItem_s **)&igi2_frame.tCallQueue;
  igi2_frame.tCallQueue.ptFirst = nullptr;
  World_UpdateStartDynCube(ptWorld, eDynCubeTree);
  nY = ptWorld->tOrigo.nY;
  *(_QWORD *)&igi2_frame.tIntPos.nX = (__int64)ptPos->vX;
  vY = ptPos->vY;
  qmemcpy(&igi2_frame.tRealPos, ptPos, sizeof(igi2_frame.tRealPos));
  nX = igi2_frame.tIntPos.nX;
  v10 = ptWorld->tOrigo.nX;
  *(_QWORD *)&igi2_frame.tIntPos.nX = (__int64)vY;
  v11 = nY + (__int64)vY;
  v12 = v10 + nX;
  vZ = ptPos->vZ;
  v14 = CallQueue_ptFirstFreeItem;
  *(_QWORD *)&igi2_frame.tIntPos.nX = (__int64)vZ;
  igi2_frame.tIntPos.nY = v11;
  v15 = (__int64)vZ;
  v16 = ptWorld->aptStartDynCube[eDynCubeTree];
  v17 = igi2_frame.tRealPos.vZ;
  igi2_frame.tIntPos.nZ = ptWorld->tOrigo.nZ + v15;
  v18 = ptWorld->anStartDynCubeLevel[eDynCubeTree];
  v19 = igi2_frame.tRealPos.vY;
  igi2_frame.tIntPos.nX = v12;
  while ( 1 )
  {
    ptDynCubeObj = v16->ptDynCubeObj;
    if ( ptDynCubeObj )
    {
      for ( i = 511 * eQTaskEvent; ; i = 511 * eQTaskEvent )
      {
        eQTaskType = ptDynCubeObj->tQObj.tQTask.eQTaskType;
        if ( QTask_aatQTaskFinalEvent[0][eQTaskType + i].pfHandler
          && ptDynCubeObj->tQObj.vRealRadius * ptDynCubeObj->tQObj.vRealRadius > (ptDynCubeObj->tQObj.tPos.vZ - v17)
                                                                               * (ptDynCubeObj->tQObj.tPos.vZ - v17)
                                                                               + (ptDynCubeObj->tQObj.tPos.vY - v19)
                                                                               * (ptDynCubeObj->tQObj.tPos.vY - v19)
                                                                               + (ptDynCubeObj->tQObj.tPos.vX
                                                                                - igi2_frame.tRealPos.vX)
                                                                               * (ptDynCubeObj->tQObj.tPos.vX
                                                                                - igi2_frame.tRealPos.vX)
          && (bQTaskGroup & QTask_atQTaskType[eQTaskType].bQTaskGroup) != 0 )
        {
          v23 = v14;
          v14 = v14->ptNext;
          v23->ptQTask = &ptDynCubeObj->tQObj.tQTask;
          v23->uEvent.eQTaskEvent = eQTaskEvent;
          v23->isNoContext = false;
          v23->pxContext = pxContext;
          v23->ptNext = nullptr;
          *igi2_frame.tCallQueue.pptLast = v23;
          igi2_frame.tCallQueue.pptLast = &v23->ptNext;
        }
        ptDynCubeObj = ptDynCubeObj->ptNext;
        if ( !ptDynCubeObj )
          break;
      }
      v12 = igi2_frame.tIntPos.nX;
    }
    v16 = v16->aptChild[(v12 >> v18) & 1
                      | (2 * (((unsigned int)igi2_frame.tIntPos.nY >> v18) & 1 | (2 * (((unsigned int)igi2_frame.tIntPos.nZ >> v18) & 1))))];
    if ( !v16 )
      break;
    LOBYTE(v18) = v18 - 1;
  }
  CallQueue_ptFirstFreeItem = v14;
  CallQueue_CallHandlers(&igi2_frame.tCallQueue);
  return result;
}

// source: e/1/world.c:6344  [anchor-mhash]
unsigned int __cdecl World_TriggerQTaskEventXyz(
        struct World_s *ptWorld,
        __int16 eQTaskEvent,
        void *pxContext,
        struct real64x3_t *ptPos,
        unsigned int bQTaskGroup)
{
  return (unsigned int)World_TriggerQTaskEventXyzSpecificTree(
                         ptWorld,
                         eQTaskEvent,
                         pxContext,
                         ptPos,
                         bQTaskGroup,
                         WORLD_DYNCUBETREE_STATIONARY);
}

// source: e/1/world.c:6411  [size]
struct World_s *__cdecl World_InvalidateLightingTables(struct World_s *ptWorld)
{
  ptWorld->isLightingTablesValid = 0;
  return ptWorld;
}

// source: e/1/world.c:6424  [size]
struct QMaterial_t *__cdecl World_DefineMaterial(
        struct World_s *ptWorld,
        int iMaterial,
        struct QMaterial_t *ptQMaterial)
{
  ptWorld->aptQMaterial[iMaterial] = ptQMaterial;
  return ptQMaterial;
}

// source: e/1/world.c:6440  [anchor-strings]
int __cdecl World_GetMaterialID(int a1, int a2)
{
  int result; // eax
  _DWORD *i; // ecx

  result = 0;
  for ( i = (_DWORD *)(a1 + 88); *i != a2; ++i )
  {
    if ( ++result >= 64 )
    {
      LDebug_Error((char *)&stru_6A4CDC.tWorkQString.tPrivate.patQStringChar);
      abort();
    }
  }
  return result;
}

// source: e/1/world.c:6467  [size]
struct QMaterial_t *__cdecl World_GetMaterialFromID(
        struct World_s *ptWorld,
        int eMaterial)
{
  return ptWorld->aptQMaterial[eMaterial];
}

// source: e/1/world.c:6491  [anchor-callee]
char __cdecl World_LineOfSight(
        struct World_s *ptWorld,
        struct real64x3_t *ptStart,
        struct real64x3_t *ptEnd,
        __int16 eQEvalEvent,
        struct CollisionEvaluateContext_s *ptEvalContext,
        unsigned int bQTaskGroup,
        enum DynCubeTreeCategory_enum eDynCubeTreeCategory,
        struct LineOfSightOutputContext_s *ptOutputContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct LineOfSightContext_s tContext; };
    struct { char igi2_o1[36]; struct QIntersection_s tQObjIntersection; };
    char igi2_extent[156];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v8; // ebx
  struct QMaterial_t *ptQMaterial; // edx

  ++World_nLineOfSights;
  v8 = 0;
  igi2_frame.tContext.ptStart = ptStart;
  igi2_frame.tContext.ptEnd = ptEnd;
  igi2_frame.tContext.eEvalQTaskEvent = eQEvalEvent;
  igi2_frame.tContext.ptEvalContext = ptEvalContext;
  igi2_frame.tContext.ptWorld = ptWorld;
  igi2_frame.tContext.isHit = 0;
  igi2_frame.tContext.vTransparency = 1.0;
  igi2_frame.tContext.ptQMaterial = nullptr;
  igi2_frame.tContext.vT = 1.0;
  do
  {
    if ( !v8
      && (eDynCubeTreeCategory & 2) != 0
      && (ptStart->vX != ptEnd->vX || ptStart->vY != ptEnd->vY || ptStart->vZ != ptEnd->vZ) )
    {
      World_TriggerQTaskEventAlongLineSpecificTree(
        ptWorld,
        9,
        &igi2_frame.tContext,
        ptStart,
        ptEnd,
        1,
        bQTaskGroup,
        WORLD_DYNCUBETREE_STATIONARY);
    }
    ++v8;
  }
  while ( v8 < 1 );
  if ( igi2_frame.tContext.vTransparency != 0.0 && (bQTaskGroup & 0x80000000) != 0 )
  {
    World_TraceLines(ptWorld, &igi2_frame.tQObjIntersection, ptStart, ptEnd, 1, 512, nullptr, 0x80000000);
    if ( igi2_frame.tQObjIntersection.isHit )
    {
      igi2_frame.tContext.vTransparency = 0.0;
      igi2_frame.tContext.isHit = 1;
    }
  }
  if ( ptOutputContext )
  {
    ptQMaterial = igi2_frame.tContext.ptQMaterial;
    ptOutputContext->vTransparency = igi2_frame.tContext.vTransparency;
    ptOutputContext->ptQMaterial = ptQMaterial;
  }
  return igi2_frame.tContext.isHit == 0;
}

// source: e/1/world.c:6570  [anchor-callee]
void __cdecl World_UpdateStartDynCube(struct World_s *ptWorld, enum DynCubeTree_e eDynCubeTree)
{
  #pragma pack(push, 1)
  union
  {
    struct { int _nTemp; };
    struct { char igi2_o1[4]; int nLevel; };
    struct { char igi2_o2[8]; struct real64x3_t tPos; };
    struct { char igi2_o3[32]; struct DynCubeTreeItem_s tDynCube; };
    char igi2_extent[92];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct DynCubeTreeItem_s *v2; // ebp
  int nY; // ecx
  int nZ; // eax
  int bChildren; // eax
  struct DynCubeTreeItem_s *v6; // ecx
  struct DynCubeTreeItem_s *v7; // esi
  unsigned __int8 v8; // cl
  struct DynCubeTreeItem_s *p_tDynCube; // edx
  int v10; // ebp
  unsigned __int8 *p_bChildren; // eax
  unsigned int nSize; // ecx
  int v13; // esi
  int v14; // eax
  unsigned __int8 v15; // cl

  if ( !ptWorld->aisStartDynCubeValid[eDynCubeTree] )
  {
    v2 = ptWorld->aptDynCubeTree[eDynCubeTree];
    nY = ptWorld->tOrigo.nY;
    nZ = ptWorld->tOrigo.nZ;
    igi2_frame.tPos.vX = (double)-ptWorld->tOrigo.nX;
    igi2_frame.tPos.vY = (double)-nY;
    qmemcpy(&igi2_frame.tDynCube, v2, sizeof(igi2_frame.tDynCube));
    igi2_frame.tDynCube.aptChild[0] = v2->aptChild[7];
    igi2_frame.tDynCube.aptChild[7] = v2->aptChild[0];
    igi2_frame._nTemp = -nZ;
    bChildren = v2->bChildren;
    igi2_frame.tPos.vZ = (double)igi2_frame._nTemp;
    igi2_frame.tDynCube.bChildren = ((_BYTE)bChildren << 7) | (bChildren >> 7) & 1;
    igi2_frame.tDynCube.aptChild[1] = v2->aptChild[6];
    igi2_frame.tDynCube.aptChild[6] = v2->aptChild[1];
    v6 = v2->aptChild[5];
    igi2_frame.tDynCube.bChildren |= 2 * ((bChildren >> 6) & 1 | (32 * ((bChildren >> 1) & 1)));
    v7 = v2->aptChild[4];
    igi2_frame.tDynCube.aptChild[2] = v6;
    igi2_frame.tDynCube.aptChild[5] = v2->aptChild[2];
    igi2_frame.tDynCube.aptChild[3] = v7;
    v8 = (8 * ((bChildren >> 4) & 1 | (2 * ((bChildren >> 3) & 1))))
       | (4 * ((bChildren >> 5) & 1 | (8 * ((bChildren >> 2) & 1))))
       | igi2_frame.tDynCube.bChildren;
    p_tDynCube = &igi2_frame.tDynCube;
    igi2_frame.tDynCube.aptChild[4] = v2->aptChild[3];
    igi2_frame.tDynCube.bChildren = v8;
    if ( v8 && (v8 & ~(v8 - 1)) == v8 && !igi2_frame.tDynCube.ptDynCubeObj )
    {
      v10 = 30;
      p_bChildren = &igi2_frame.tDynCube.bChildren;
      do
      {
        _BitScanForward((unsigned int *)&p_bChildren, *p_bChildren);
        p_tDynCube = p_tDynCube->aptChild[(_DWORD)p_bChildren];
        nSize = p_tDynCube->nSize;
        v13 = p_tDynCube->nSize * (((unsigned __int8)p_bChildren & 2) - 1);
        igi2_frame.tPos.vX = (double)(p_tDynCube->nSize * (2 * ((unsigned __int8)p_bChildren & 1) - 1)) + igi2_frame.tPos.vX;
        v14 = nSize * ((((int)p_bChildren >> 1) & 2) - 1);
        v15 = p_tDynCube->bChildren;
        --v10;
        igi2_frame.nLevel = v14;
        p_bChildren = &p_tDynCube->bChildren;
        igi2_frame.tPos.vY = (double)v13 + igi2_frame.tPos.vY;
        igi2_frame.tPos.vZ = (double)igi2_frame.nLevel + igi2_frame.tPos.vZ;
      }
      while ( v15 && (v15 & ~(v15 - 1)) == v15 && !p_tDynCube->ptDynCubeObj );
      ptWorld->aptStartDynCube[eDynCubeTree] = p_tDynCube;
      ptWorld->anStartDynCubeLevel[eDynCubeTree] = v10;
      ptWorld->aisStartDynCubeValid[eDynCubeTree] = 1;
      qmemcpy(&ptWorld->atStartDynCubePos[eDynCubeTree], &igi2_frame.tPos, sizeof(ptWorld->atStartDynCubePos[eDynCubeTree]));
    }
    else
    {
      ptWorld->aptStartDynCube[eDynCubeTree] = v2;
      ptWorld->anStartDynCubeLevel[eDynCubeTree] = 30;
      ptWorld->aisStartDynCubeValid[eDynCubeTree] = 1;
      qmemcpy(&ptWorld->atStartDynCubePos[eDynCubeTree], &igi2_frame.tPos, sizeof(ptWorld->atStartDynCubePos[eDynCubeTree]));
    }
  }
}

// source: e/1/world.c:6644  [size]
struct World_Water_t *__cdecl World_GetWater(struct World_s *ptWorld)
{
  return ptWorld->ptWater;
}

// source: e/1/world.c:6657  [anchor-hash]
struct World_s *__cdecl World_CalculateLightning(struct World_s *ptWorld)
{
  if ( !ptWorld->isLightingTablesValid )
  {
    if ( ptWorld->ptCubeTree )
      ptWorld->isLightingTablesValid = 1;
  }
  return ptWorld;
}

// source: e/1/world.c:6682  [anchor-strings]
void __cdecl World_WriteDynCubeTreeItemToDiskRecursively(
        struct DynCubeTreeItem_s *ptDynCubeTreeItem,
        int iLevel,
        struct _iobuf *fpFile,
        unsigned int *pnTaskCount)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v14; };
    struct { char igi2_o1[16]; unsigned int nCount; };
    struct { char igi2_o2[20]; unsigned int nSubCount; };
    char igi2_extent[24];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v4; // ebx
  struct DynCubeObj_s *ptDynCubeObj; // edi
  int v6; // ebp
  char *QTaskTypeName; // eax
  unsigned __int16 eQTaskType; // dx
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptNext; // eax
  int v11; // edi
  struct DynCubeTreeItem_s **aptChild; // ebp
  int v13; // edi

  v4 = iLevel;
  ptDynCubeObj = ptDynCubeTreeItem->ptDynCubeObj;
  igi2_frame.nCount = 0;
  igi2_frame.nSubCount = 0;
  if ( iLevel > 0 )
  {
    v6 = iLevel;
    do
    {
      fprintf(fpFile, (int)&Delimiter, igi2_frame.v14);
      --v6;
    }
    while ( v6 );
  }
  fprintf(fpFile, (int)&stru_6A4CDC.tDebugConsoleLineList.ptTail, iLevel);
  for ( ; ptDynCubeObj; ++igi2_frame.nCount )
  {
    if ( v4 > 0 )
    {
      do
      {
        fprintf(fpFile, (int)&Delimiter, igi2_frame.v14);
        --v4;
      }
      while ( v4 );
      v4 = iLevel;
    }
    QTaskTypeName = QTask_GetQTaskTypeName(ptDynCubeObj->tQObj.tQTask.eQTaskType);
    fprintf(fpFile, (int)&stru_6A4CDC.tDebugConsoleLineList.ptMiddle, (int)QTaskTypeName);
    eQTaskType = ptDynCubeObj->tQObj.tQTask.eQTaskType;
    if ( QTask_IsQTaskTypeDerived(eQTaskType, SoundDefSound_eQTaskType) )
    {
      fprintf(fpFile, (int)&stru_6A4CDC.ptPrev, (int)&ptDynCubeObj[2].tQObj.pxQData + 6);
    }
    else if ( QTask_IsQTaskTypeDerived(eQTaskType, RigidDynCubeObj_eQTaskType) )
    {
      ptPrev = ptDynCubeObj[1].tQObj.tQTask.ptPrev;
      if ( ptPrev )
      {
        ptNext = ptPrev->ptNext;
        if ( ptNext )
          fprintf(fpFile, (int)&stru_6A4CDC.ptPrev, (int)ptNext->tQTaskChildren.ptHead);
      }
    }
    fprintf(fpFile, (int)&stru_6A4CDC, igi2_frame.v14);
    ptDynCubeObj = ptDynCubeObj->ptNext;
  }
  v11 = 0;
  aptChild = ptDynCubeTreeItem->aptChild;
  do
  {
    if ( *aptChild )
    {
      if ( v4 > 0 )
      {
        do
        {
          fprintf(fpFile, (int)&Delimiter, igi2_frame.v14);
          --v4;
        }
        while ( v4 );
        v4 = iLevel;
      }
      fprintf(fpFile, (int)"Child: %i\n", v11);
      World_WriteDynCubeTreeItemToDiskRecursively(*aptChild, v4 + 1, fpFile, &igi2_frame.nSubCount);
    }
    ++v11;
    ++aptChild;
  }
  while ( v11 < 8 );
  if ( v4 > 0 )
  {
    v13 = v4;
    do
    {
      fprintf(fpFile, (int)&Delimiter, igi2_frame.v14);
      --v13;
    }
    while ( v13 );
  }
  fprintf(fpFile, (int)"Level: %i Tasks: %u ChildTasks: %u\n", v4);
  *pnTaskCount += igi2_frame.nCount + igi2_frame.nSubCount;
}

// source: e/1/world.c:6757  [anchor-strings]
char *__cdecl World_WriteCubeTreeTaskInfoToFile(struct World_s *ptWorld, char *zFileName)
{
  char *result; // eax
  FILE *v3; // esi
  struct DynCubeTreeItem_s *v4; // edi
  unsigned int v5; // edi
  unsigned int nTreeCount; // [esp+4h] [ebp-4h] BYREF

  result = (char *)fopen(zFileName, "wt");
  v3 = (FILE *)result;
  if ( result )
  {
    v4 = ptWorld->aptDynCubeTree[0];
    fprintf((FILE *)result, (int)"\nTree: %i\n", 0);
    nTreeCount = 0;
    World_WriteDynCubeTreeItemToDiskRecursively(v4, 0, v3, &nTreeCount);
    v5 = nTreeCount;
    fprintf(v3, (int)"Tasks In Tree: %u\n", nTreeCount);
    fprintf(v3, (int)"\nTotal Tasks: %u\n", v5);
    return (char *)fclose(v3);
  }
  return result;
}

// source: e/1/world.c:6805  [anchor-callee]
struct int32x3_t *__cdecl World_SetInt32CentimeterFromReal64Meter(
        struct real64x3_t *ptReal,
        struct int32x3_t *ptInt)
{
  struct real64x3_t tTemp; // [esp+10h] [ebp-1Ch] BYREF

  qmemcpy(&tTemp, ptReal, sizeof(tTemp));
  tTemp.vY = tTemp.vY * 100.0;
  tTemp.vZ = tTemp.vZ * 100.0;
  ptInt->nX = (__int64)(tTemp.vX * 100.0);
  ptInt->nY = (__int64)tTemp.vY;
  ptInt->nZ = (__int64)tTemp.vZ;
  return ptInt;
}

// source: e/1/world.c:6833  [anchor-callee]
struct real64x3_t *__cdecl World_SetReal64MeterFromInt32Centimeter(
        struct real64x3_t *ptReal,
        struct int32x3_t *ptInt)
{
  ptReal->vX = (double)ptInt->nX;
  ptReal->vY = (double)ptInt->nY;
  ptReal->vZ = (double)ptInt->nZ;
  ptReal->vX = ptReal->vX * 0.01;
  ptReal->vY = ptReal->vY * 0.01;
  ptReal->vZ = ptReal->vZ * 0.01;
  return ptReal;
}

// source: e/1/world.c:6864  [anchor-callee]
unsigned __int8 __cdecl World_GetScaledUint8FromReal32(float value, float max)
{
  double v2; // st7
  double v3; // st7
  double v4; // st6
  int v5; // eax

  v2 = -max;
  if ( value < v2 )
    value = v2;
  if ( value > (double)max )
    value = max;
  v3 = value / max * 127.0;
  if ( v3 >= 0.0 )
    v4 = v3 + 0.5;
  else
    v4 = v3 - 0.5;
  v5 = (__int64)v4 + 127;
  if ( v5 >= 0 )
  {
    if ( v5 > 255 )
      LOBYTE(v5) = -1;
  }
  else
  {
    LOBYTE(v5) = 0;
  }
  return v5;
}

// source: e/1/world.c:6909  [size]
float __cdecl World_GetReal32FromScaledUint8(unsigned __int8 c, float max)
{
  return (double)(c - 127) * max * 0.007874015718698502;
}

// source: e/1/world.c:6929  [anchor-callee]
unsigned __int16 __cdecl World_GetScaledUint16FromReal32(float value, float max)
{
  double v2; // st7
  double v3; // st7
  double v4; // st6
  int v5; // eax

  v2 = -max;
  if ( value < v2 )
    value = v2;
  if ( value > (double)max )
    value = max;
  v3 = value / max * 32767.0;
  if ( v3 >= 0.0 )
    v4 = v3 + 0.5;
  else
    v4 = v3 - 0.5;
  v5 = (__int64)v4 + 0x7FFF;
  if ( v5 >= 0 )
  {
    if ( v5 > 0xFFFF )
      LOWORD(v5) = -1;
  }
  else
  {
    LOWORD(v5) = 0;
  }
  return v5;
}

// source: e/1/world.c:6975  [size]
float __cdecl World_GetReal32FromScaledUint16(unsigned __int16 c, float max)
{
  return (double)(c - 0x7FFF) * max * 3.0518509447574615e-05;
}

// source: e/1/world.c:6994  [anchor-caller]
float __cdecl World_GetErrorBetweenReal32AndScaledUint8(float value, float max)
{
  double v2; // st7

  v2 = (double)(World_GetScaledUint8FromReal32(value, max) - 127) * max * 0.007874015718698502 - value;
  if ( v2 < 0.0 )
    return -v2;
  return v2;
}

// source: e/1/world.c:7019  [anchor-mhash]
float __cdecl World_GetErrorBetweenReal32AndScaledUint16(float value, float max)
{
  double v2; // st7

  v2 = (double)(World_GetScaledUint16FromReal32(value, max) - 0x7FFF) * max * 3.0518509447574615e-05 - value;
  if ( v2 < 0.0 )
    return -v2;
  return v2;
}

struct Result_s *__cdecl sub_4161D0(struct Result_s *retstr, void *a2, struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { char ArgList[4]; };
    struct { char igi2_o1[4]; char Destination[2]; };
    struct { char igi2_o2[6]; char pxData[2]; };
    struct { char igi2_o3[8]; char zBuffer[2]; };
    struct { char igi2_o4[10]; char v13[2]; };
    struct { char igi2_o5[12]; _DWORD v14[6]; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  _DWORD *v3; // esi
  int v4; // eax
  struct Node_s *ptHead; // edx
  struct Node_s *i; // ecx
  unsigned __int16 v7; // cx

  v3 = Mem_AllocFn(1200, 4);
  v3[1] = 0;
  *v3 = 0;
  if ( ptArgList->isQVM )
  {
    *(_DWORD *)igi2_frame.ArgList = 0;
    QVM_EvalArg(igi2_frame.ArgList, 4, ptArgList, 0, 1);
    v4 = *(_DWORD *)igi2_frame.ArgList;
  }
  else
  {
    v4 = Expression_EvalInt(*ptArgList->aptExpression);
  }
  v3[2] = v4;
  ptHead = Mission_tMissions.ptHead;
  for ( i = Mission_tMissions.ptHead->ptNext; i; i = i->ptNext )
  {
    if ( ptHead[1].ptNext == (struct Node_s *)v4 )
    {
      LDebug_Error("Mission ID %d not unique", v4);
      abort();
    }
    ptHead = i;
  }
  List_AddTail(v3, (int)&Mission_tMissions);
  if ( ptArgList->isQVM )
  {
    igi2_frame.Destination[0] = 0;
    QVM_EvalArg(igi2_frame.Destination, 2, ptArgList, 1, 3);
  }
  else
  {
    Expression_EvalString(ptArgList->aptExpression[1], igi2_frame.Destination, 2);
  }
  if ( ptArgList->isQVM )
  {
    igi2_frame.pxData[0] = 0;
    QVM_EvalArg(igi2_frame.pxData, 2, ptArgList, 2, 3);
  }
  else
  {
    Expression_EvalString(ptArgList->aptExpression[2], igi2_frame.pxData, 2);
  }
  if ( ptArgList->isQVM )
  {
    igi2_frame.zBuffer[0] = 0;
    QVM_EvalArg(igi2_frame.zBuffer, 2, ptArgList, 3, 3);
  }
  else
  {
    Expression_EvalString(ptArgList->aptExpression[3], igi2_frame.zBuffer, 2);
  }
  if ( ptArgList->isQVM )
  {
    igi2_frame.v13[0] = 0;
    QVM_EvalArg(igi2_frame.v13, 2, ptArgList, 4, 3);
  }
  else
  {
    Expression_EvalString(ptArgList->aptExpression[4], igi2_frame.v13, 2);
  }
  LOBYTE(v7) = 0;
  HIBYTE(v7) = igi2_frame.Destination[0];
  v3[3] = (unsigned __int8)igi2_frame.v13[0] | (((unsigned __int8)igi2_frame.zBuffer[0] | (((unsigned __int8)igi2_frame.pxData[0] | v7) << 8)) << 8);
  if ( ptArgList->isQVM )
  {
    *((_BYTE *)v3 + 16) = 0;
    QVM_EvalArg(v3 + 4, 32, ptArgList, 5, 3);
  }
  else
  {
    Expression_EvalString(ptArgList->aptExpression[5], (char *)v3 + 16, 32);
  }
  if ( ptArgList->isQVM )
  {
    *((_BYTE *)v3 + 48) = 0;
    QVM_EvalArg(v3 + 12, 256, ptArgList, 6, 3);
  }
  else
  {
    Expression_EvalString(ptArgList->aptExpression[6], (char *)v3 + 48, 256);
  }
  if ( ptArgList->isQVM )
  {
    *((_BYTE *)v3 + 304) = 0;
    QVM_EvalArg(v3 + 76, 32, ptArgList, 7, 3);
  }
  else
  {
    Expression_EvalString(ptArgList->aptExpression[7], (char *)v3 + 304, 32);
  }
  if ( ptArgList->isQVM )
  {
    *((_BYTE *)v3 + 336) = 0;
    QVM_EvalArg(v3 + 84, 256, ptArgList, 8, 3);
  }
  else
  {
    Expression_EvalString(ptArgList->aptExpression[8], (char *)v3 + 336, 256);
  }
  if ( ptArgList->isQVM )
  {
    *((_BYTE *)v3 + 592) = 0;
    QVM_EvalArg(v3 + 148, 256, ptArgList, 9, 3);
  }
  else
  {
    Expression_EvalString(ptArgList->aptExpression[9], (char *)v3 + 592, 256);
  }
  if ( ptArgList->isQVM )
  {
    *((_BYTE *)v3 + 848) = 0;
    QVM_EvalArg(v3 + 212, 256, ptArgList, 10, 3);
  }
  else
  {
    Expression_EvalString(ptArgList->aptExpression[10], (char *)v3 + 848, 256);
  }
  if ( ptArgList->isQVM )
  {
    *((_BYTE *)v3 + 1104) = 0;
    QVM_EvalArg(v3 + 276, 32, ptArgList, 11, 3);
  }
  else
  {
    Expression_EvalString(ptArgList->aptExpression[11], (char *)v3 + 1104, 32);
  }
  if ( ptArgList->isQVM )
  {
    *((_BYTE *)v3 + 1136) = 0;
    QVM_EvalArg(v3 + 284, 32, ptArgList, 12, 3);
  }
  else
  {
    Expression_EvalString(ptArgList->aptExpression[12], (char *)v3 + 1136, 32);
  }
  if ( ptArgList->isQVM )
  {
    *((_BYTE *)v3 + 1168) = 0;
    QVM_EvalArg(v3 + 292, 32, ptArgList, 13, 3);
  }
  else
  {
    Expression_EvalString(ptArgList->aptExpression[13], (char *)v3 + 1168, 32);
  }
  ++Mission_nMission;
  igi2_frame.v14[0] = 1;
  igi2_frame.v14[2] = 0;
  igi2_frame.v14[3] = 1072693248;
  igi2_frame.v14[4] = &g_zInitialValue;
  qmemcpy(retstr, igi2_frame.v14, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_416580(struct Result_s *retstr, void *a2, struct ArgList_s *pxData)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // edi
  struct Node_s *ptHead; // esi
  struct Node_s *ptNext; // eax
  _DWORD *v7; // eax
  _DWORD *v8; // eax
  _DWORD v10[6]; // [esp+8h] [ebp-18h] BYREF

  v3 = pxData;
  if ( pxData->isQVM )
  {
    pxData = nullptr;
    QVM_EvalArg(&pxData, 4, v3, 0, 1);
    v4 = pxData;
  }
  else
  {
    v4 = (struct ArgList_s *)Expression_EvalInt(*pxData->aptExpression);
  }
  ptHead = Mission_tMissions.ptHead;
  ptNext = Mission_tMissions.ptHead->ptNext;
  if ( Mission_tMissions.ptHead->ptNext )
  {
    while ( (struct ArgList_s *)ptHead[1].ptNext != v4 )
    {
      ptHead = ptNext;
      ptNext = ptNext->ptNext;
      if ( !ptNext )
        goto LABEL_9;
    }
    v7 = Mem_AllocFn(16, 4);
    v7[1] = 0;
    *v7 = 0;
    v8 = List_AddTail(v7, (int)&Mission_tMissionList);
    v8[2] = v4;
    v8[3] = ptHead;
  }
LABEL_9:
  v10[0] = 1;
  v10[2] = 0;
  v10[3] = 1072693248;
  v10[4] = &g_zInitialValue;
  qmemcpy(retstr, v10, sizeof(struct Result_s));
  return retstr;
}

void __cdecl sub_416650(int a1)
{
  #pragma pack(push, 1)
  union
  {
    struct { char *v3; };
    struct { char igi2_o1[16]; int pxContext[2]; };
    char igi2_extent[24];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Script_s *v1; // eax
  struct Script_s *v2; // edi

  if ( *(_DWORD *)(a1 + 8) )
  {
    igi2_frame.v3 = *(char **)a1;
    igi2_frame.pxContext[0] = (int)sub_416650;
    igi2_frame.pxContext[1] = 0;
    File_DirList(igi2_frame.v3, (void (__cdecl *)(struct FileDirListCallbackContext_s *, void *))Script_DirListCallback, igi2_frame.pxContext);
  }
  else if ( Wildcard_SearchSimple("mission.*", *(void **)a1, nullptr, nullptr, nullptr, 1) )
  {
    v1 = Script_New(*(char **)a1);
    v2 = v1;
    if ( !v1 )
    {
      LDebug_Error("Mission_Open(): Couldn't load script: %s", *(char **)a1);
      abort();
    }
    Script_Execute(v1);
    Script_Delete(v2);
  }
}

void __cdecl sub_4166E0(int a1)
{
  struct Script_s *v1; // eax
  struct Script_s *v2; // esi

  if ( !*(_DWORD *)(a1 + 8) )
  {
    v1 = Script_New(*(char **)a1);
    v2 = v1;
    if ( !v1 )
    {
      LDebug_Error("Mission_Open(): Couldn't load script: %s", *(char **)a1);
      abort();
    }
    Script_Execute(v1);
    Script_Delete(v2);
  }
}

int sub_416750()
{
  return Mission_nMission;
}

struct Node_s *__cdecl sub_416790(int a1)
{
  struct Node_s *result; // eax
  struct Node_s *ptNext; // ecx
  int v3; // edx

  result = Mission_tMissionList.ptHead;
  ptNext = Mission_tMissionList.ptHead->ptNext;
  v3 = 0;
  if ( !Mission_tMissionList.ptHead->ptNext )
    return nullptr;
  while ( a1 != v3 )
  {
    result = ptNext;
    ptNext = ptNext->ptNext;
    ++v3;
    if ( !ptNext )
      return nullptr;
  }
  return result;
}

int sub_416810()
{
  #pragma pack(push, 1)
  union
  {
    struct { int pxContext; };
    struct { char igi2_o1[4]; int v2; };
    char igi2_extent[8];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  Symbol_Register(
    "DefineMission",
    sub_4161D0,
    nullptr,
    -1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "DefineMissionListItem",
    sub_416580,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Mission_tMissions.ptHead = (struct Node_s *)&Mission_tMissions.ptMiddle;
  Mission_tMissions.ptTail = (struct Node_s *)&Mission_tMissions;
  Mission_tMissions.ptMiddle = nullptr;
  Mission_tMissionList.ptHead = (struct Node_s *)&Mission_tMissionList.ptMiddle;
  Mission_tMissionList.ptTail = (struct Node_s *)&Mission_tMissionList;
  Mission_tMissionList.ptMiddle = nullptr;
  igi2_frame.pxContext = (int)sub_416650;
  igi2_frame.v2 = 0;
  File_DirList(
    "LOCAL:missions",
    (void (__cdecl *)(struct FileDirListCallbackContext_s *, void *))Script_DirListCallback,
    &igi2_frame.pxContext);
  igi2_frame.pxContext = (int)sub_4166E0;
  igi2_frame.v2 = 0;
  return File_DirList(
           "LOCAL:missions",
           (void (__cdecl *)(struct FileDirListCallbackContext_s *, void *))Script_DirListCallback,
           &igi2_frame.pxContext);
}

struct Node_s *sub_4168C0()
{
  struct Node_s *ptHead; // eax
  struct Node_s *i; // ebx
  _DWORD **v2; // eax
  int v3; // esi
  struct Node_s *result; // eax
  struct Node_s *j; // ebx
  _DWORD **v6; // eax
  int v7; // esi

  ptHead = Mission_tMissions.ptHead;
  for ( i = Mission_tMissions.ptHead->ptNext; i; i = i->ptNext )
  {
    v2 = Node_Remove(ptHead);
    if ( v2 )
    {
      v3 = *(_DWORD *)((unsigned int)(v2 - 1) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v3);
      memset(*(void **)(v3 + 8), 0xCDu, *(_DWORD *)(v3 + 16));
      free((void *)v3);
    }
    ptHead = i;
  }
  result = Mission_tMissionList.ptHead;
  for ( j = Mission_tMissionList.ptHead->ptNext; j; j = j->ptNext )
  {
    v6 = Node_Remove(result);
    if ( v6 )
    {
      v7 = *(_DWORD *)((unsigned int)(v6 - 1) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v7);
      memset(*(void **)(v7 + 8), 0xCDu, *(_DWORD *)(v7 + 16));
      free((void *)v7);
    }
    result = j;
  }
  return result;
}
