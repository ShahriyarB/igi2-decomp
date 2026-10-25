/* e/3/bsptree.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: e/3/bsptree.c:216  [size]
void __cdecl BspTreeDynCubeObj_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[2].ptParent = nullptr;
  ptQTask[3].ptPrev = nullptr;
  *(_DWORD *)&ptQTask[2].eQTaskType = 0;
  ptQTask[3].ptNext = nullptr;
  ptQTask[3].ptParent = nullptr;
  *(_DWORD *)&ptQTask[3].eQTaskType = 0;
  BspTreeDynCubeObj_ptTree = (struct BspTreeDynCubeObj_s *)ptQTask;
}

// source: e/3/bsptree.c:244  [anchor-callee]
void __cdecl BspTreeDynCubeObj_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptParent; // eax
  int v2; // esi
  int v3; // eax
  int v4; // esi

  ptParent = ptQTask[3].ptParent;
  if ( ptParent )
  {
    v2 = *(_DWORD *)((unsigned int)&ptParent[-1].eQTaskType & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v2);
    memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
    free((void *)v2);
    ptQTask[3].ptParent = nullptr;
  }
  v3 = *(_DWORD *)&ptQTask[3].eQTaskType;
  if ( v3 )
  {
    v4 = *(_DWORD *)((v3 - 4) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v4);
    memset(*(void **)(v4 + 8), 0xCDu, *(_DWORD *)(v4 + 16));
    free((void *)v4);
    *(_DWORD *)&ptQTask[3].eQTaskType = 0;
  }
  BspTreeDynCubeObj_ptTree = nullptr;
}

// source: e/3/bsptree.c:280  [anchor-hash]
void __cdecl BspTreeDynCubeObj_Open()
{
  __int16 v0; // ax
  unsigned __int16 v1; // si

  BspTreeDynCubeObj_eQTaskType = QTask_NewQTaskType("BspTree", 160, DynCubeObj_eQTaskType, 0, 0);
  BspTreeDynCubeObj_eGenerationSizeEvent = QTask_NewQTaskEventFn(0, "BspGenerationSize");
  v0 = QTask_NewQTaskEventFn(0, "BspGenerationList");
  v1 = BspTreeDynCubeObj_eQTaskType;
  BspTreeDynCubeObj_eGenerationListEvent = v0;
  QTask_LinkQTaskEventHandlerFn(
    BspTreeDynCubeObj_eQTaskType,
    0,
    (void (__cdecl *)(struct QTask_s *, void *))BspTreeDynCubeObj_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, BspTreeDynCubeObj_DeleteHandler);
  BspTreeDynCubeObj_ptFindIntersection1 = nullptr;
  BspTreeDynCubeObj_ptFindIntersection2 = nullptr;
}

// source: e/3/bsptree.c:310  [anchor-hash]
void __cdecl BspTreeDynCubeObj_Close()
{
  int v0; // esi

  QTask_DeleteQTaskEvent(BspTreeDynCubeObj_eGenerationSizeEvent);
  BspTreeDynCubeObj_eGenerationSizeEvent = 512;
  QTask_DeleteQTaskEvent(BspTreeDynCubeObj_eGenerationListEvent);
  BspTreeDynCubeObj_eGenerationListEvent = 512;
  QTask_DeleteQTaskType(BspTreeDynCubeObj_eQTaskType);
  BspTreeDynCubeObj_eQTaskType = 512;
  if ( BspTreeDynCubeObj_ptTriangleStorage )
  {
    v0 = *(_DWORD *)((unsigned int)&BspTreeDynCubeObj_ptTriangleStorage[-1].tTriangleData.tNormal.vZ & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
    BspTreeDynCubeObj_ptTriangleStorage = nullptr;
    BspTreeDynCubeObj_unNumStorageTriangles = 0;
    BspTreeDynCubeObj_unNumAllocatedStorageTriangles = 0;
  }
}

// source: e/3/bsptree.c:348  [size]
struct BspTreeDynCubeObj_s *__cdecl BspTreeDynCubeObj_New(struct QTask_s *ptParent)
{
  return (struct BspTreeDynCubeObj_s *)QTask_NewFn(ptParent, BspTreeDynCubeObj_eQTaskType, nullptr);
}

// source: e/3/bsptree.c:369  [size]
unsigned __int16 __cdecl BspTreeDynCubeObj_GetQTaskType()
{
  return BspTreeDynCubeObj_eQTaskType;
}

// source: e/3/bsptree.c:390  [anchor-caller]
struct real64x3_t *__cdecl BspTreeDynCubeObj_InsertTriangles(
        struct BspTreeDynCubeObj_s *ptTree,
        unsigned int unNumVertices,
        struct real64x3_t *ptVertexList,
        unsigned int unNumTriangleVertexIndexes,
        unsigned int *punTriangleVertexIndexes,
        unsigned __int8 *punTriangleMaterial,
        struct real32x3_t *ptTriangleNormals)
{
  unsigned int v8; // esi
  struct real64x3_t *result; // eax

  v8 = ptTree->unNumVertices;
  BspTreeDynCubeObj_AddVertices(ptTree, unNumVertices, ptVertexList, 1);
  BspTreeDynCubeObj_AddUnsplitTrianglesToStorageList(
    ptTree,
    v8,
    unNumTriangleVertexIndexes,
    punTriangleVertexIndexes,
    punTriangleMaterial,
    ptTriangleNormals);
  for ( result = (struct real64x3_t *)BspTreeDynCubeObj_unNumStorageTriangles;
        BspTreeDynCubeObj_unNumStorageTriangles;
        result = (struct real64x3_t *)BspTreeDynCubeObj_unNumStorageTriangles )
  {
    BspTreeDynCubeObj_InsertLastStorageTriangleInBspTree(ptTree);
  }
  return result;
}

// source: e/3/bsptree.c:424  [anchor-callee]
void __cdecl BspTreeDynCubeObj_AddVertices(
        struct BspTreeDynCubeObj_s *ptTree,
        unsigned int unNumVertices,
        struct real64x3_t *ptVertexList,
        char isSubtractOrigo)
{
  unsigned int unNumAllocatedVertices; // ecx
  struct real32x3_t *v6; // eax
  unsigned int v7; // edx
  unsigned int v8; // ecx
  int v9; // eax
  struct real32x3_t *v10; // edx
  _DWORD *v11; // esi
  struct real32x3_t *ptRelativeVertex; // eax
  int v13; // esi
  unsigned int v14; // eax
  double *v15; // ecx
  int v16; // edx
  double *v17; // edx
  double v18; // st7
  int v19; // ecx
  unsigned int v20; // eax
  double *p_vZ; // ecx
  int v22; // edx
  double *v23; // edx
  double v24; // st7
  int v25; // ecx
  struct BspTreeDynCubeObj_s *ptTreea = *(struct BspTreeDynCubeObj_s * *)&unNumVertices; // [esp+10h] [ebp+4h] ARGSLOT

  unNumAllocatedVertices = ptTree->unNumAllocatedVertices;
  if ( unNumAllocatedVertices )
  {
    v7 = ptTree->unNumVertices;
    if ( unNumAllocatedVertices >= v7 + unNumVertices )
      goto LABEL_11;
    ptTreea = (struct BspTreeDynCubeObj_s *)Mem_AllocFn(4 * (3 * (v7 + unNumVertices) + 3000), 4);
    v8 = 0;
    if ( ptTree->unNumVertices )
    {
      v9 = 0;
      do
      {
        v10 = &ptTree->ptRelativeVertex[v9];
        v11 = (struct QTask_s **)((char *)&ptTreea->tDynCubeObj.tQObj.tQTask.ptNext + v9 * 12);
        *v11 = LODWORD(v10->vX);
        v11[1] = LODWORD(v10->vY);
        v11[2] = LODWORD(v10->vZ);
        ++v8;
        ++v9;
      }
      while ( v8 < ptTree->unNumVertices );
    }
    ptRelativeVertex = ptTree->ptRelativeVertex;
    if ( ptRelativeVertex )
    {
      v13 = *(_DWORD *)((unsigned int)&ptRelativeVertex[-1].vZ & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v13);
      memset(*(void **)(v13 + 8), 0xCDu, *(_DWORD *)(v13 + 16));
      free((void *)v13);
    }
    v6 = (struct real32x3_t *)ptTreea;
    ptTree->unNumAllocatedVertices = ptTree->unNumVertices + unNumVertices + 1000;
  }
  else
  {
    qmemcpy(&ptTree->tOrigin, ptVertexList, sizeof(ptTree->tOrigin));
    v6 = (struct real32x3_t *)Mem_AllocFn(12 * (unNumVertices + 1000), 4);
    ptTree->unNumAllocatedVertices = unNumVertices + 1000;
  }
  ptTree->ptRelativeVertex = v6;
LABEL_11:
  if ( !isSubtractOrigo )
  {
    v20 = 0;
    if ( (int)unNumVertices >= 4 )
    {
      p_vZ = &ptVertexList->vZ;
      do
      {
        ptTree->ptRelativeVertex[v20 + ptTree->unNumVertices].vX = *(p_vZ - 2);
        ptTree->ptRelativeVertex[v20 + ptTree->unNumVertices].vY = *(p_vZ - 1);
        ptTree->ptRelativeVertex[v20 + ptTree->unNumVertices].vZ = *p_vZ;
        ptTree->ptRelativeVertex[ptTree->unNumVertices + 1 + v20].vX = p_vZ[1];
        ptTree->ptRelativeVertex[v20 + 1 + ptTree->unNumVertices].vY = p_vZ[2];
        ptTree->ptRelativeVertex[v20 + 1 + ptTree->unNumVertices].vZ = p_vZ[3];
        ptTree->ptRelativeVertex[ptTree->unNumVertices + 2 + v20].vX = p_vZ[4];
        ptTree->ptRelativeVertex[v20 + 2 + ptTree->unNumVertices].vY = p_vZ[5];
        ptTree->ptRelativeVertex[v20 + 2 + ptTree->unNumVertices].vZ = p_vZ[6];
        ptTree->ptRelativeVertex[ptTree->unNumVertices + 3 + v20].vX = p_vZ[7];
        ptTree->ptRelativeVertex[v20 + 3 + ptTree->unNumVertices].vY = p_vZ[8];
        v22 = v20 + ptTree->unNumVertices;
        v20 += 4;
        ptTree->ptRelativeVertex[v22 + 3].vZ = p_vZ[9];
        p_vZ += 12;
      }
      while ( v20 + 3 < unNumVertices );
    }
    if ( v20 < unNumVertices )
    {
      v23 = &ptVertexList[v20].vZ;
      do
      {
        ptTree->ptRelativeVertex[v20 + ptTree->unNumVertices].vX = *(v23 - 2);
        ptTree->ptRelativeVertex[v20 + ptTree->unNumVertices].vY = *(v23 - 1);
        v24 = *v23;
        v25 = v20 + ptTree->unNumVertices;
        ++v20;
        v23 += 3;
        ptTree->ptRelativeVertex[v25].vZ = v24;
      }
      while ( v20 < unNumVertices );
    }
    goto LABEL_25;
  }
  v14 = 0;
  if ( (int)unNumVertices >= 4 )
  {
    v15 = &ptVertexList->vZ;
    do
    {
      ptTree->ptRelativeVertex[v14 + ptTree->unNumVertices].vX = *(v15 - 2) - ptTree->tOrigin.vX;
      ptTree->ptRelativeVertex[v14 + ptTree->unNumVertices].vY = *(v15 - 1) - ptTree->tOrigin.vY;
      ptTree->ptRelativeVertex[v14 + ptTree->unNumVertices].vZ = *v15 - ptTree->tOrigin.vZ;
      ptTree->ptRelativeVertex[ptTree->unNumVertices + 1 + v14].vX = v15[1] - ptTree->tOrigin.vX;
      ptTree->ptRelativeVertex[v14 + 1 + ptTree->unNumVertices].vY = v15[2] - ptTree->tOrigin.vY;
      ptTree->ptRelativeVertex[v14 + 1 + ptTree->unNumVertices].vZ = v15[3] - ptTree->tOrigin.vZ;
      ptTree->ptRelativeVertex[ptTree->unNumVertices + 2 + v14].vX = v15[4] - ptTree->tOrigin.vX;
      ptTree->ptRelativeVertex[v14 + 2 + ptTree->unNumVertices].vY = v15[5] - ptTree->tOrigin.vY;
      ptTree->ptRelativeVertex[v14 + 2 + ptTree->unNumVertices].vZ = v15[6] - ptTree->tOrigin.vZ;
      ptTree->ptRelativeVertex[ptTree->unNumVertices + 3 + v14].vX = v15[7] - ptTree->tOrigin.vX;
      ptTree->ptRelativeVertex[v14 + 3 + ptTree->unNumVertices].vY = v15[8] - ptTree->tOrigin.vY;
      v16 = v14 + ptTree->unNumVertices;
      v14 += 4;
      ptTree->ptRelativeVertex[v16 + 3].vZ = v15[9] - ptTree->tOrigin.vZ;
      v15 += 12;
    }
    while ( v14 + 3 < unNumVertices );
  }
  if ( v14 >= unNumVertices )
  {
LABEL_25:
    ptTree->unNumVertices += unNumVertices;
    return;
  }
  v17 = &ptVertexList[v14].vZ;
  do
  {
    ptTree->ptRelativeVertex[v14 + ptTree->unNumVertices].vX = *(v17 - 2) - ptTree->tOrigin.vX;
    ptTree->ptRelativeVertex[v14 + ptTree->unNumVertices].vY = *(v17 - 1) - ptTree->tOrigin.vY;
    v18 = *v17 - ptTree->tOrigin.vZ;
    v19 = v14 + ptTree->unNumVertices;
    ++v14;
    v17 += 3;
    ptTree->ptRelativeVertex[v19].vZ = v18;
  }
  while ( v14 < unNumVertices );
  ptTree->unNumVertices += unNumVertices;
}

// source: e/3/bsptree.c:499  [anchor-callee]
void __cdecl BspTreeDynCubeObj_AddUnsplitTrianglesToStorageList(
        struct BspTreeDynCubeObj_s *ptTree,
        unsigned int unStartingIndex,
        unsigned int unNumIndexes,
        unsigned int *punTriangleVertexIndexes,
        unsigned __int8 *punTriangleMaterial,
        struct real32x3_t *ptTriangleNormals)
{
  unsigned int *v6; // esi
  unsigned __int8 *v7; // edi
  struct real32x3_t *v8; // ebp
  int v9; // ecx
  int v10; // edx
  int v11; // edx
  int v12; // edx
  unsigned int v13; // edx
  float vY; // ecx
  float vZ; // edx
  long double v16; // st7
  struct TriangleStorageData_s tData; // [esp+14h] [ebp-24h] BYREF
  unsigned int unNumIndexesa = *(unsigned int *)&punTriangleVertexIndexes; // [esp+44h] [ebp+Ch] ARGSLOT

  v6 = &punTriangleVertexIndexes[unNumIndexes - 1];
  v7 = &punTriangleMaterial[unNumIndexes / 3 - 1];
  v8 = &ptTriangleNormals[unNumIndexes / 3 - 1];
  if ( unNumIndexes / 3 )
  {
    unNumIndexesa = unNumIndexes / 3;
    do
    {
      v9 = *(v6 - 2);
      tData.tTriangleData.unMaterialIndex = *v7;
      tData.unSplittingNode = 0;
      tData.tTriangleData.atChildIndex[0].atData[0] = 0;
      tData.tTriangleData.atChildIndex[0].atData[1] = 0;
      tData.tTriangleData.atChildIndex[0].atData[2] = 0;
      tData.tTriangleData.atChildIndex[1].atData[0] = 0;
      tData.tTriangleData.atChildIndex[1].atData[1] = 0;
      tData.tTriangleData.atChildIndex[1].atData[2] = 0;
      v10 = unStartingIndex + v9;
      tData.tTriangleData.atVertexIndex[0].atData[1] = (unsigned __int16)(unStartingIndex + v9) >> 8;
      LOBYTE(v9) = unStartingIndex + *((_BYTE *)v6 - 8);
      tData.tTriangleData.atVertexIndex[0].atData[0] = BYTE2(v10);
      v11 = *(v6 - 1);
      tData.tTriangleData.atVertexIndex[0].atData[2] = v9;
      v12 = v11 + unStartingIndex;
      tData.tTriangleData.atVertexIndex[1].atData[1] = BYTE1(v12);
      LOBYTE(v9) = unStartingIndex + *((_BYTE *)v6 - 4);
      tData.tTriangleData.atVertexIndex[1].atData[0] = BYTE2(v12);
      v13 = *v6;
      tData.tTriangleData.atVertexIndex[1].atData[2] = v9;
      tData.tTriangleData.atVertexIndex[2].atData[0] = (unStartingIndex + v13) >> 16;
      tData.tTriangleData.atVertexIndex[2].atData[1] = (unsigned __int16)(unStartingIndex + v13) >> 8;
      LOBYTE(v9) = unStartingIndex + *(_BYTE *)v6;
      tData.tTriangleData.tNormal.vX = v8->vX;
      tData.tTriangleData.atVertexIndex[2].atData[2] = v9;
      vY = v8->vY;
      vZ = v8->vZ;
      --v7;
      v6 -= 3;
      tData.nPlaneSide = -1;
      tData.tTriangleData.tNormal.vY = vY;
      tData.tTriangleData.tNormal.vZ = vZ;
      if ( tData.tTriangleData.tNormal.vX != 0.0
        || tData.tTriangleData.tNormal.vY != 0.0
        || tData.tTriangleData.tNormal.vZ != 0.0 )
      {
        v16 = 1.0
            / sqrt(
                tData.tTriangleData.tNormal.vX * tData.tTriangleData.tNormal.vX
              + tData.tTriangleData.tNormal.vY * tData.tTriangleData.tNormal.vY
              + tData.tTriangleData.tNormal.vZ * tData.tTriangleData.tNormal.vZ);
        tData.tTriangleData.tNormal.vX = tData.tTriangleData.tNormal.vX * v16;
        tData.tTriangleData.tNormal.vY = tData.tTriangleData.tNormal.vY * v16;
        tData.tTriangleData.tNormal.vZ = tData.tTriangleData.tNormal.vZ * v16;
      }
      --v8;
      BspTreeDynCubeObj_AddTriangleToStorageList(ptTree, &tData);
      --unNumIndexesa;
    }
    while ( unNumIndexesa );
  }
}

// source: e/3/bsptree.c:567  [anchor-callee]
void __cdecl BspTreeDynCubeObj_AddTriangleToStorageList(
        struct BspTreeDynCubeObj_s *ptTree,
        struct TriangleStorageData_s *ptData)
{
  unsigned int v2; // ebp
  struct TriangleStorageData_s *v3; // eax
  struct TriangleStorageData_s *v4; // eax
  struct TriangleStorageData_s *v5; // edx
  int v6; // esi
  struct real32x3_t *ptRelativeVertex; // esi
  float *p_vX; // edx
  float *v9; // eax
  float *v10; // ecx
  double v11; // st7
  double v12; // st6
  double v13; // st5
  double v14; // st4
  long double v15; // st7
  struct TriangleStorageData_s *v16; // eax
  struct TriangleStorageData_s *ptNewStorage; // [esp+Ch] [ebp-28h]
  float atEdge; // [esp+10h] [ebp-24h]
  float atEdge_4; // [esp+14h] [ebp-20h]
  float atEdge_8; // [esp+18h] [ebp-1Ch]
  float atEdge_12; // [esp+1Ch] [ebp-18h]
  float atEdge_16; // [esp+20h] [ebp-14h]
  float tTemp_; // [esp+28h] [ebp-Ch]
  float tTemp__4; // [esp+2Ch] [ebp-8h]
  float tTemp__8; // [esp+30h] [ebp-4h]

  v2 = BspTreeDynCubeObj_unNumStorageTriangles;
  if ( BspTreeDynCubeObj_unNumStorageTriangles == BspTreeDynCubeObj_unNumAllocatedStorageTriangles )
  {
    if ( BspTreeDynCubeObj_unNumStorageTriangles )
    {
      v4 = (struct TriangleStorageData_s *)Mem_AllocFn(
                                             4 * (9 * BspTreeDynCubeObj_unNumAllocatedStorageTriangles + 9009),
                                             4);
      v2 = BspTreeDynCubeObj_unNumStorageTriangles;
      v5 = BspTreeDynCubeObj_ptTriangleStorage;
      ptNewStorage = v4;
      qmemcpy(v4, BspTreeDynCubeObj_ptTriangleStorage, 36 * BspTreeDynCubeObj_unNumStorageTriangles);
      if ( v5 )
      {
        v6 = *(_DWORD *)((unsigned int)&v5[-1].tTriangleData.tNormal.vZ & 0xFFFFFFFC);
        --Mem_nCurrentAllocations;
        Node_Remove((_DWORD **)v6);
        memset(*(void **)(v6 + 8), 0xCDu, *(_DWORD *)(v6 + 16));
        free((void *)v6);
        v2 = BspTreeDynCubeObj_unNumStorageTriangles;
      }
      BspTreeDynCubeObj_ptTriangleStorage = ptNewStorage;
      BspTreeDynCubeObj_unNumAllocatedStorageTriangles += 1001;
    }
    else
    {
      v3 = (struct TriangleStorageData_s *)Mem_AllocFn(36036, 4);
      v2 = BspTreeDynCubeObj_unNumStorageTriangles;
      BspTreeDynCubeObj_ptTriangleStorage = v3;
      BspTreeDynCubeObj_unNumAllocatedStorageTriangles = 1001;
    }
  }
  ptRelativeVertex = ptTree->ptRelativeVertex;
  p_vX = &ptRelativeVertex[256
                         * (ptData->tTriangleData.atVertexIndex[2].atData[1]
                          + (ptData->tTriangleData.atVertexIndex[2].atData[0] << 8))
                         + ptData->tTriangleData.atVertexIndex[2].atData[2]].vX;
  v9 = &ptRelativeVertex[256
                       * (ptData->tTriangleData.atVertexIndex[0].atData[1]
                        + (ptData->tTriangleData.atVertexIndex[0].atData[0] << 8))
                       + ptData->tTriangleData.atVertexIndex[0].atData[2]].vX;
  v10 = &ptRelativeVertex[256
                        * (ptData->tTriangleData.atVertexIndex[1].atData[1]
                         + (ptData->tTriangleData.atVertexIndex[1].atData[0] << 8))
                        + ptData->tTriangleData.atVertexIndex[1].atData[2]].vX;
  v11 = *p_vX - *v9;
  v12 = p_vX[1] - v9[1];
  v13 = p_vX[2] - v9[2];
  atEdge_12 = *v10 - *v9;
  atEdge_16 = v10[1] - v9[1];
  v14 = v10[2] - v9[2];
  tTemp_ = v14 * v12 - atEdge_16 * v13;
  atEdge = tTemp_;
  tTemp__4 = -(v14 * v11 - atEdge_12 * v13);
  atEdge_4 = tTemp__4;
  tTemp__8 = atEdge_16 * v11 - atEdge_12 * v12;
  atEdge_8 = tTemp__8;
  if ( tTemp_ != 0.0 || tTemp__4 != 0.0 || tTemp__8 != 0.0 )
  {
    v15 = 1.0 / sqrt(tTemp_ * tTemp_ + tTemp__4 * tTemp__4 + tTemp__8 * tTemp__8);
    atEdge = tTemp_ * v15;
    atEdge_4 = tTemp__4 * v15;
    atEdge_8 = tTemp__8 * v15;
  }
  if ( atEdge_8 * ptData->tTriangleData.tNormal.vZ
     + atEdge_4 * ptData->tTriangleData.tNormal.vY
     + atEdge * ptData->tTriangleData.tNormal.vX < 0.0 )
  {
    atEdge = -atEdge;
    atEdge_4 = -atEdge_4;
    atEdge_8 = -atEdge_8;
  }
  ptData->tTriangleData.tNormal.vX = atEdge;
  ptData->tTriangleData.tNormal.vY = atEdge_4;
  v16 = BspTreeDynCubeObj_ptTriangleStorage;
  ptData->tTriangleData.tNormal.vZ = atEdge_8;
  qmemcpy(&v16[v2], ptData, sizeof(struct TriangleStorageData_s));
  BspTreeDynCubeObj_unNumStorageTriangles = v2 + 1;
}

// source: e/3/bsptree.c:649  [anchor-caller]
void __cdecl BspTreeDynCubeObj_InsertLastStorageTriangleInBspTree(struct BspTreeDynCubeObj_s *ptTree)
{
  #pragma pack(push, 1)
  union
  {
    struct { float atVertex; };
    struct { char igi2_o1[4]; float atVertex_4; };
    struct { char igi2_o2[8]; float atVertex_8; };
    struct { char igi2_o3[16]; float atVertex_16; };
    struct { char igi2_o4[20]; float atVertex_20; };
    struct { char igi2_o5[24]; float atVertex_24; };
    struct { char igi2_o6[28]; float atVertex_28; };
    struct { char igi2_o7[32]; float atVertex_32; };
    struct { char igi2_o8[36]; struct TriangleStorageData_s tData; };
    char igi2_extent[72];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  unsigned int i; // ebp
  unsigned int unSplittingNode; // esi
  enum BspPlaneSide_e nPlaneSide; // edi
  enum BspPlaneSide_e v4; // edx
  struct real32x3_t *ptRelativeVertex; // ecx
  float *p_vX; // eax
  float *v7; // eax
  double v8; // st7
  float *v9; // ecx
  double v10; // st7
  double v11; // st7
  double v12; // st7
  double v13; // st7
  double v14; // st7
  double v15; // st7
  double v16; // st7
  double v17; // st7

  i = 1;
  qmemcpy(&igi2_frame.tData, &BspTreeDynCubeObj_ptTriangleStorage[BspTreeDynCubeObj_unNumStorageTriangles - 1], sizeof(igi2_frame.tData));
  BspTreeDynCubeObj_RemoveLastStoredTriangle(ptTree);
  if ( ptTree->unNumNodes )
  {
    unSplittingNode = igi2_frame.tData.unSplittingNode;
    if ( !igi2_frame.tData.unSplittingNode )
      goto LABEL_7;
    nPlaneSide = igi2_frame.tData.nPlaneSide;
    if ( BspTreeDynCubeObj_IsPlaneSideChildDefined(ptTree, igi2_frame.tData.unSplittingNode, (enum BspPlaneSide_e)igi2_frame.tData.nPlaneSide) )
    {
      for ( i = ptTree->ptNode[unSplittingNode].atChildIndex[nPlaneSide].atData[2]
              + (((ptTree->ptNode[unSplittingNode].atChildIndex[nPlaneSide].atData[0] << 8)
                + ptTree->ptNode[unSplittingNode].atChildIndex[nPlaneSide].atData[1]) << 8);
            ;
            i = (((ptTree->ptNode[i].atChildIndex[v4].atData[0] << 8) + ptTree->ptNode[i].atChildIndex[v4].atData[1]) << 8)
              + ptTree->ptNode[i].atChildIndex[v4].atData[2] )
      {
LABEL_7:
        v4 = BspTreeDynCubeObj_CheckSplitAndAddNewTriangles(ptTree, i, &igi2_frame.tData);
        ptRelativeVertex = ptTree->ptRelativeVertex;
        p_vX = &ptRelativeVertex[256
                               * (igi2_frame.tData.tTriangleData.atVertexIndex[0].atData[1]
                                + (igi2_frame.tData.tTriangleData.atVertexIndex[0].atData[0] << 8))
                               + igi2_frame.tData.tTriangleData.atVertexIndex[0].atData[2]].vX;
        igi2_frame.atVertex = *p_vX;
        igi2_frame.atVertex_8 = p_vX[2];
        igi2_frame.atVertex_4 = p_vX[1];
        v7 = &ptRelativeVertex[256
                             * (igi2_frame.tData.tTriangleData.atVertexIndex[1].atData[1]
                              + (igi2_frame.tData.tTriangleData.atVertexIndex[1].atData[0] << 8))
                             + igi2_frame.tData.tTriangleData.atVertexIndex[1].atData[2]].vX;
        v8 = igi2_frame.atVertex - *v7;
        igi2_frame.atVertex_20 = v7[2];
        igi2_frame.atVertex_16 = v7[1];
        v9 = &ptRelativeVertex[256
                             * (igi2_frame.tData.tTriangleData.atVertexIndex[2].atData[1]
                              + (igi2_frame.tData.tTriangleData.atVertexIndex[2].atData[0] << 8))
                             + igi2_frame.tData.tTriangleData.atVertexIndex[2].atData[2]].vX;
        igi2_frame.atVertex_24 = *v9;
        igi2_frame.atVertex_28 = v9[1];
        igi2_frame.atVertex_32 = v9[2];
        if ( v8 < 0.0 )
          v8 = -v8;
        if ( v8 < 40.96 )
        {
          v10 = igi2_frame.atVertex_4 - igi2_frame.atVertex_16;
          if ( v10 < 0.0 )
            v10 = -v10;
          if ( v10 < 40.96 )
          {
            v11 = igi2_frame.atVertex_8 - igi2_frame.atVertex_20;
            if ( v11 < 0.0 )
              v11 = -v11;
            if ( v11 < 40.96 )
              break;
          }
        }
        v12 = *v7 - igi2_frame.atVertex_24;
        if ( v12 < 0.0 )
          v12 = -v12;
        if ( v12 < 40.96 )
        {
          v13 = igi2_frame.atVertex_16 - igi2_frame.atVertex_28;
          if ( v13 < 0.0 )
            v13 = -v13;
          if ( v13 < 40.96 )
          {
            v14 = igi2_frame.atVertex_20 - igi2_frame.atVertex_32;
            if ( v14 < 0.0 )
              v14 = -v14;
            if ( v14 < 40.96 )
              break;
          }
        }
        v15 = igi2_frame.atVertex_24 - igi2_frame.atVertex;
        if ( v15 < 0.0 )
          v15 = -v15;
        if ( v15 < 40.96 )
        {
          v16 = igi2_frame.atVertex_28 - igi2_frame.atVertex_4;
          if ( v16 < 0.0 )
            v16 = -v16;
          if ( v16 < 40.96 )
          {
            v17 = igi2_frame.atVertex_32 - igi2_frame.atVertex_8;
            if ( v17 < 0.0 )
              v17 = -v17;
            if ( v17 < 40.96 )
              break;
          }
        }
        if ( !ptTree->unNumNodes
          || !((((ptTree->ptNode[i].atChildIndex[v4].atData[0] << 8) + ptTree->ptNode[i].atChildIndex[v4].atData[1]) << 8)
             + ptTree->ptNode[i].atChildIndex[v4].atData[2]) )
        {
          BspTreeDynCubeObj_CreateNewLeaf(ptTree, i, v4, &igi2_frame.tData.tTriangleData);
          return;
        }
      }
    }
    else
    {
      BspTreeDynCubeObj_CreateNewLeaf(ptTree, unSplittingNode, nPlaneSide, &igi2_frame.tData.tTriangleData);
    }
  }
  else
  {
    BspTreeDynCubeObj_CreateNewLeaf(ptTree, 0, BSPTREE_PLANESIDE_UNDEFINED, &igi2_frame.tData.tTriangleData);
  }
}

// source: e/3/bsptree.c:756  [anchor-hash]
void __cdecl BspTreeDynCubeObj_RemoveLastStoredTriangle(struct BspTreeDynCubeObj_s *ptTree)
{
  int v1; // esi

  if ( !--BspTreeDynCubeObj_unNumStorageTriangles )
  {
    if ( BspTreeDynCubeObj_ptTriangleStorage )
    {
      v1 = *(_DWORD *)((unsigned int)&BspTreeDynCubeObj_ptTriangleStorage[-1].tTriangleData.tNormal.vZ & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v1);
      memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
      free((void *)v1);
    }
    BspTreeDynCubeObj_ptTriangleStorage = nullptr;
    BspTreeDynCubeObj_unNumAllocatedStorageTriangles = 0;
  }
}

// source: e/3/bsptree.c:784  [anchor-callee]
int __cdecl BspTreeDynCubeObj_IsPlaneSideChildDefined(
        struct BspTreeDynCubeObj_s *ptTree,
        unsigned int unNode,
        enum BspPlaneSide_e ePlaneSide)
{
  return ptTree->unNumNodes
      && ptTree->ptNode[unNode].atChildIndex[ePlaneSide].atData[2]
       + ((ptTree->ptNode[unNode].atChildIndex[ePlaneSide].atData[1]
         + (ptTree->ptNode[unNode].atChildIndex[ePlaneSide].atData[0] << 8)) << 8) != 0;
}

// source: e/3/bsptree.c:808  [anchor-callee]
void __cdecl BspTreeDynCubeObj_CreateNewLeaf(
        struct BspTreeDynCubeObj_s *ptTree,
        unsigned int unNode,
        enum BspPlaneSide_e ePlaneSide,
        struct BspTreeNode_s *ptNodeData)
{
  unsigned int unNumNodes; // eax
  unsigned int unNumAllocatedNodes; // ecx
  struct BspTreeNode_s *v6; // ebx
  struct BspTreeNode_s *ptNode; // eax
  int v8; // esi
  unsigned int v9; // eax
  struct BspTreeNode_s *v10; // eax

  unNumNodes = ptTree->unNumNodes;
  if ( unNumNodes )
  {
    unNumAllocatedNodes = ptTree->unNumAllocatedNodes;
    if ( unNumNodes == unNumAllocatedNodes )
    {
      v6 = (struct BspTreeNode_s *)Mem_AllocFn(28 * (unNumAllocatedNodes + 1001), 4);
      qmemcpy(v6, ptTree->ptNode, 28 * ptTree->unNumAllocatedNodes);
      ptNode = ptTree->ptNode;
      ptTree->unNumAllocatedNodes += 1001;
      if ( ptNode )
      {
        v8 = *(_DWORD *)((unsigned int)&ptNode[-1].tNormal.vZ & 0xFFFFFFFC);
        --Mem_nCurrentAllocations;
        Node_Remove((_DWORD **)v8);
        memset(*(void **)(v8 + 8), 0xCDu, *(_DWORD *)(v8 + 16));
        free((void *)v8);
      }
      ptTree->ptNode = v6;
    }
    v9 = 28 * unNode;
    ptTree->ptNode->atChildIndex[ePlaneSide].atData[v9] = BYTE2(ptTree->unNumNodes);
    ptTree->ptNode->atChildIndex[ePlaneSide].atData[v9 + 1] = BYTE1(ptTree->unNumNodes);
    ptTree->ptNode->atChildIndex[ePlaneSide].atData[v9 + 2] = ptTree->unNumNodes;
    qmemcpy(&ptTree->ptNode[ptTree->unNumNodes++], ptNodeData, sizeof(ptTree->ptNode[ptTree->unNumNodes++]));
  }
  else
  {
    v10 = (struct BspTreeNode_s *)Mem_AllocFn(28056, 4);
    ptTree->ptNode = v10;
    ptTree->unNumAllocatedNodes = 1002;
    v10->atChildIndex[0].atData[0] = 0;
    ptTree->ptNode->atChildIndex[0].atData[1] = 0;
    ptTree->ptNode->atChildIndex[0].atData[2] = 0;
    ptTree->ptNode->atChildIndex[1].atData[0] = 0;
    ptTree->ptNode->atChildIndex[1].atData[1] = 0;
    ptTree->ptNode->atChildIndex[1].atData[2] = 0;
    qmemcpy(&ptTree->ptNode[1], ptNodeData, sizeof(ptTree->ptNode[1]));
    ptTree->unNumNodes = 2;
  }
}

// source: e/3/bsptree.c:877  [anchor-callee]
enum BspPlaneSide_e __cdecl BspTreeDynCubeObj_CheckSplitAndAddNewTriangles(
        struct BspTreeDynCubeObj_s *ptTree,
        unsigned int unNode,
        struct TriangleStorageData_s *ptData)
{
  #pragma pack(push, 1)
  union
  {
    struct { float avVertPlaneValue; };
    struct { char igi2_o1[4]; float avVertPlaneValue_4; };
    struct { char igi2_o2[12]; float v59; };
    struct { char igi2_o3[12]; float v60; };
    struct { char igi2_o4[12]; float v61; };
    struct { char igi2_o5[16]; struct real32x3_t tPointInPlane; };
    struct { char igi2_o6[28]; struct real32x3_t atVertex[3]; };
    struct { char igi2_o7[64]; struct real32x3_t tPlaneNormal; };
    struct { char igi2_o8[76]; enum BspPlaneSide_e aeVertexSide[3]; };
    struct { char igi2_o9[88]; unsigned int aunVertIndex[3]; };
    struct { char igi2_o10[100]; struct TriangleStorageData_s atNew[3]; };
    char igi2_extent[212];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v4; // eax
  int v5; // edx
  struct BspTreeNode_s *ptNode; // esi
  int v7; // ebp
  struct real32x3_t *ptRelativeVertex; // ebx
  struct BspTreeNode_s *v9; // esi
  float *p_vX; // ecx
  float v11; // ebp
  enum BspPlaneSide_e v12; // esi
  float *v13; // eax
  double v14; // st4
  enum BspPlaneSide_e v15; // ecx
  double v16; // st4
  enum BspPlaneSide_e v17; // edx
  __int32 v18; // eax
  double v19; // st7
  double v20; // st7
  double v22; // st7
  double v23; // st7
  double v24; // st7
  double v25; // st7
  double v26; // st7
  double v27; // st7
  double v28; // st7
  unsigned __int8 *v29; // esi
  int v30; // edi
  struct real32x3_t *v31; // ecx
  struct real32x3_t *v32; // edx
  float vY; // eax
  float vZ; // edx
  int v35; // eax
  struct real32x3_t *v36; // edx
  float v37; // eax
  float v38; // edx
  double v39; // st7
  int v40; // eax
  struct real32x3_t *v41; // ecx
  float vX; // edx
  float v43; // eax
  float v44; // ecx
  double v45; // st7
  double v46; // st7
  double v47; // st7
  double v48; // st7
  double v49; // st7
  double v50; // st7
  double v51; // st7
  double v52; // st7
  int v53; // ecx
  double v54; // st7
  double v55; // st6
  double v56; // st6

  v4 = ptData->tTriangleData.atVertexIndex[0].atData[2]
     + ((ptData->tTriangleData.atVertexIndex[0].atData[1] + (ptData->tTriangleData.atVertexIndex[0].atData[0] << 8)) << 8);
  v5 = ptData->tTriangleData.atVertexIndex[1].atData[2]
     + ((ptData->tTriangleData.atVertexIndex[1].atData[1] + (ptData->tTriangleData.atVertexIndex[1].atData[0] << 8)) << 8);
  ptNode = ptTree->ptNode;
  igi2_frame.aunVertIndex[2] = ptData->tTriangleData.atVertexIndex[2].atData[2]
                  + ((ptData->tTriangleData.atVertexIndex[2].atData[1]
                    + (ptData->tTriangleData.atVertexIndex[2].atData[0] << 8)) << 8);
  v7 = ptNode[unNode].atVertexIndex[0].atData[1];
  ptRelativeVertex = ptTree->ptRelativeVertex;
  v9 = &ptNode[unNode];
  p_vX = &ptRelativeVertex[256 * (v7 + (v9->atVertexIndex[0].atData[0] << 8)) + v9->atVertexIndex[0].atData[2]].vX;
  igi2_frame.tPointInPlane.vX = *p_vX;
  v11 = p_vX[1];
  igi2_frame.tPointInPlane.vZ = p_vX[2];
  igi2_frame.tPlaneNormal = v9->tNormal;
  igi2_frame.tPointInPlane.vY = v11;
  igi2_frame.v59 = igi2_frame.tPlaneNormal.vZ * (ptRelativeVertex[v4].vZ - igi2_frame.tPointInPlane.vZ)
      + igi2_frame.tPlaneNormal.vY * (ptRelativeVertex[v4].vY - v11)
      + igi2_frame.tPlaneNormal.vX * (ptRelativeVertex[v4].vX - igi2_frame.tPointInPlane.vX);
  igi2_frame.avVertPlaneValue = igi2_frame.v59;
  v12 = igi2_frame.v59 < 0.0;
  v13 = &ptRelativeVertex[v5].vX;
  v14 = *v13 - igi2_frame.tPointInPlane.vX;
  igi2_frame.aeVertexSide[0] = v12;
  igi2_frame.v60 = igi2_frame.tPlaneNormal.vZ * (v13[2] - igi2_frame.tPointInPlane.vZ) + igi2_frame.tPlaneNormal.vY * (v13[1] - v11) + igi2_frame.tPlaneNormal.vX * v14;
  igi2_frame.avVertPlaneValue_4 = igi2_frame.v60;
  v15 = igi2_frame.v60 < 0.0;
  v16 = ptRelativeVertex[igi2_frame.aunVertIndex[2]].vX - igi2_frame.tPointInPlane.vX;
  igi2_frame.aeVertexSide[1] = v15;
  igi2_frame.v61 = igi2_frame.tPlaneNormal.vZ * (ptRelativeVertex[igi2_frame.aunVertIndex[2]].vZ - igi2_frame.tPointInPlane.vZ)
      + igi2_frame.tPlaneNormal.vY * (ptRelativeVertex[igi2_frame.aunVertIndex[2]].vY - v11)
      + igi2_frame.tPlaneNormal.vX * v16;
  v17 = igi2_frame.v61 < 0.0;
  igi2_frame.aeVertexSide[2] = v17;
  v18 = v12 + v17 + v15;
  if ( !v18 || v18 == 3 )
    return v18 != 0;
  v19 = igi2_frame.avVertPlaneValue;
  if ( igi2_frame.avVertPlaneValue < 0.0 )
    v19 = -v19;
  if ( v19 < 40.959999084472656 && v15 == v17 )
    return v15;
  v20 = igi2_frame.avVertPlaneValue_4;
  if ( igi2_frame.avVertPlaneValue_4 < 0.0 )
    v20 = -v20;
  if ( v20 < 40.959999084472656 && v12 == v17 )
    return v12;
  v22 = igi2_frame.v61;
  if ( igi2_frame.v61 < 0.0 )
    v22 = -v22;
  if ( v22 < 40.959999084472656 && v12 == v15 )
    return v12;
  v23 = igi2_frame.avVertPlaneValue;
  if ( igi2_frame.avVertPlaneValue < 0.0 )
    v23 = -v23;
  if ( v23 < 40.959999084472656 )
  {
    v24 = igi2_frame.avVertPlaneValue_4;
    if ( igi2_frame.avVertPlaneValue_4 < 0.0 )
      v24 = -v24;
    if ( v24 < 40.959999084472656 )
      goto LABEL_65;
  }
  v25 = igi2_frame.avVertPlaneValue_4;
  if ( igi2_frame.avVertPlaneValue_4 < 0.0 )
    v25 = -v25;
  if ( v25 < 40.959999084472656 )
  {
    v26 = igi2_frame.v61;
    if ( igi2_frame.v61 < 0.0 )
      v26 = -v26;
    if ( v26 < 40.959999084472656 )
      goto LABEL_65;
  }
  v27 = igi2_frame.v61;
  if ( igi2_frame.v61 < 0.0 )
    v27 = -v27;
  if ( v27 >= 40.959999084472656 )
    goto LABEL_34;
  v28 = igi2_frame.avVertPlaneValue;
  if ( igi2_frame.avVertPlaneValue < 0.0 )
    v28 = -v28;
  if ( v28 < 40.959999084472656 )
  {
LABEL_65:
    v53 = 0;
    v54 = igi2_frame.avVertPlaneValue;
    if ( igi2_frame.avVertPlaneValue < 0.0 )
      v54 = -v54;
    v55 = igi2_frame.avVertPlaneValue_4;
    if ( igi2_frame.avVertPlaneValue_4 < 0.0 )
      v55 = -v55;
    if ( v55 > v54 )
    {
      v53 = 1;
      v54 = igi2_frame.avVertPlaneValue_4;
      if ( igi2_frame.avVertPlaneValue_4 < 0.0 )
        v54 = -v54;
    }
    v56 = igi2_frame.v61;
    if ( igi2_frame.v61 < 0.0 )
      v56 = -v56;
    if ( v56 > v54 )
      v53 = 2;
    return igi2_frame.aeVertexSide[v53];
  }
  else
  {
LABEL_34:
    BspTreeDynCubeObj_SplitTriangle(ptTree, unNode, ptData, &igi2_frame.tPointInPlane, &igi2_frame.tPlaneNormal, igi2_frame.aeVertexSide, igi2_frame.atNew);
    qmemcpy(ptData, igi2_frame.atNew, sizeof(struct TriangleStorageData_s));
    igi2_frame.atNew[0].unSplittingNode = 0;
    igi2_frame.atNew[1].unSplittingNode = unNode;
    igi2_frame.atNew[2].unSplittingNode = unNode;
    v29 = &igi2_frame.atNew[1].tTriangleData.atVertexIndex[0].atData[1];
    v30 = 2;
    do
    {
      v31 = ptTree->ptRelativeVertex;
      v32 = &v31[256 * (*v29 + (*(v29 - 1) << 8)) + v29[1]];
      igi2_frame.atVertex[0].vX = v32->vX;
      vY = v32->vY;
      vZ = v32->vZ;
      igi2_frame.atVertex[0].vY = vY;
      v35 = v29[2] << 8;
      igi2_frame.atVertex[0].vZ = vZ;
      v36 = &v31[256 * (v29[3] + v35) + v29[4]];
      igi2_frame.atVertex[1].vX = v36->vX;
      v37 = v36->vY;
      v38 = v36->vZ;
      v39 = igi2_frame.atVertex[0].vX - igi2_frame.atVertex[1].vX;
      igi2_frame.atVertex[1].vY = v37;
      v40 = v29[5] << 8;
      igi2_frame.atVertex[1].vZ = v38;
      v41 = &v31[256 * (v29[6] + v40) + v29[7]];
      vX = v41->vX;
      v43 = v41->vY;
      v44 = v41->vZ;
      igi2_frame.atVertex[2].vY = v43;
      igi2_frame.atVertex[2].vX = vX;
      igi2_frame.atVertex[2].vZ = v44;
      if ( v39 < 0.0 )
        v39 = -v39;
      if ( v39 > 40.96 )
        goto LABEL_44;
      v45 = igi2_frame.atVertex[0].vY - igi2_frame.atVertex[1].vY;
      if ( v45 < 0.0 )
        v45 = -v45;
      if ( v45 > 40.96 )
        goto LABEL_44;
      v46 = igi2_frame.atVertex[0].vZ - igi2_frame.atVertex[1].vZ;
      if ( v46 < 0.0 )
        v46 = -v46;
      if ( v46 > 40.96 )
      {
LABEL_44:
        v47 = igi2_frame.atVertex[1].vX - igi2_frame.atVertex[2].vX;
        if ( v47 < 0.0 )
          v47 = -v47;
        if ( v47 > 40.96 )
          goto LABEL_53;
        v48 = igi2_frame.atVertex[1].vY - igi2_frame.atVertex[2].vY;
        if ( v48 < 0.0 )
          v48 = -v48;
        if ( v48 > 40.96 )
          goto LABEL_53;
        v49 = igi2_frame.atVertex[1].vZ - igi2_frame.atVertex[2].vZ;
        if ( v49 < 0.0 )
          v49 = -v49;
        if ( v49 > 40.96 )
        {
LABEL_53:
          v50 = igi2_frame.atVertex[2].vX - igi2_frame.atVertex[0].vX;
          if ( v50 < 0.0 )
            v50 = -v50;
          if ( v50 > 40.96 )
            goto LABEL_62;
          v51 = igi2_frame.atVertex[2].vY - igi2_frame.atVertex[0].vY;
          if ( v51 < 0.0 )
            v51 = -v51;
          if ( v51 > 40.96 )
            goto LABEL_62;
          v52 = igi2_frame.atVertex[2].vZ - igi2_frame.atVertex[0].vZ;
          if ( v52 < 0.0 )
            v52 = -v52;
          if ( v52 > 40.96 )
LABEL_62:
            BspTreeDynCubeObj_AddTriangleToStorageList(ptTree, (struct TriangleStorageData_s *)(v29 - 15));
        }
      }
      v29 += 36;
      --v30;
    }
    while ( v30 );
    return igi2_frame.atNew[0].nPlaneSide;
  }
}

// source: e/3/bsptree.c:1058  [anchor-callee]
struct real32x3_t *__cdecl BspTreeDynCubeObj_SplitTriangle(
        struct BspTreeDynCubeObj_s *ptTree,
        unsigned int unNode,
        struct TriangleStorageData_s *ptData,
        struct real32x3_t *ptPointInPlane,
        struct real32x3_t *ptPlaneNormal,
        enum BspPlaneSide_e *peVertexPlaneSide,
        struct TriangleStorageData_s *ptNewTriangles)
{
  #pragma pack(push, 1)
  union
  {
    struct { int i; };
    struct { struct real32x3_t *v94; };
    struct { char igi2_o2[4]; unsigned int unI; };
    struct { char igi2_o3[4]; unsigned int unIa; };
    struct { char igi2_o4[4]; float *unIb; };
    struct { char igi2_o5[8]; unsigned int unSplitEdges; };
    struct { char igi2_o6[12]; int aunVertIndex; };
    struct { char igi2_o7[16]; int aunVertIndex_4; };
    struct { char igi2_o8[20]; int aunVertIndex_8; };
    struct { char igi2_o9[24]; double vT; };
    struct { char igi2_o10[24]; double vTa; };
    struct { char igi2_o11[24]; double vTb; };
    struct { char igi2_o12[24]; double vTc; };
    struct { char igi2_o13[24]; double vTd; };
    struct { char igi2_o14[32]; unsigned int aunEdgeToSplit[3]; };
    struct { char igi2_o15[44]; unsigned int aunVertIndexOfSplitEdge[3]; };
    struct { char igi2_o16[56]; struct real64x3_t tVertex; };
    struct { char igi2_o17[84]; unsigned int aunNodeVertIndex[3]; };
    struct { char igi2_o18[96]; struct real64x3_t atEdge[3]; };
    struct { char igi2_o19[168]; struct real64x3_t atNewVertex[3]; };
    char igi2_extent[244];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  unsigned int v8; // edi
  int v9; // edx
  struct BspTreeDynCubeObj_s *v10; // esi
  struct BspTreeNode_s *ptNode; // ecx
  int v12; // ebp
  unsigned __int8 *v13; // ecx
  int v14; // edi
  int v15; // ebp
  int v16; // edi
  int v17; // ebp
  struct real32x3_t *ptRelativeVertex; // edi
  float *p_vX; // ecx
  float *v20; // ebp
  double v21; // st7
  int v22; // ecx
  enum BspPlaneSide_e v23; // ebp
  bool v24; // zf
  int v25; // edx
  int v26; // ecx
  unsigned int v27; // ebp
  struct real64x3_t *v28; // edx
  double vX; // st7
  struct real32x3_t *v30; // ecx
  double vY; // st6
  double vZ; // st5
  unsigned int v33; // ecx
  double v34; // st5
  double v35; // st4
  double v36; // st3
  unsigned int v37; // esi
  float *v38; // ecx
  double v39; // st7
  double v40; // st6
  unsigned int v41; // ecx
  struct real64x3_t *v42; // esi
  double v43; // st5
  double v44; // st4
  double v45; // st3
  float *v46; // ecx
  unsigned int v47; // esi
  double v48; // st7
  double v49; // st6
  unsigned int v50; // ecx
  struct real64x3_t *v51; // esi
  double v52; // st5
  double v53; // st4
  double v54; // st3
  int v55; // ecx
  float *v56; // ecx
  unsigned int v57; // esi
  double v58; // st5
  struct real64x3_t *v59; // edi
  double v60; // st7
  double v61; // st6
  unsigned int v62; // ecx
  struct real64x3_t *v63; // esi
  double v64; // st5
  double v65; // st4
  double v66; // st3
  bool v67; // cf
  struct real64x3_t *v68; // edx
  double v69; // st7
  struct real32x3_t *v70; // ecx
  double v71; // st6
  double v72; // st5
  unsigned int v73; // ecx
  struct real64x3_t *v74; // edi
  double v75; // st5
  double v76; // st4
  double v77; // st3
  unsigned int unNumVertices; // eax
  unsigned int v79; // ecx
  int v80; // eax
  struct real32x3_t *v81; // ebp
  int v82; // edi
  float *v83; // ecx
  double v84; // st7
  struct real32x3_t *v85; // edx
  double v86; // st7
  double v87; // st7
  float *v88; // eax
  struct real32x3_t *result; // eax
  struct real32x3_t *p_tNormal; // ecx
  int v91; // edi
  char v92; // cl
  char v93; // cl

  v8 = unNode;
  v9 = ptData->tTriangleData.atVertexIndex[0].atData[2]
     + ((ptData->tTriangleData.atVertexIndex[0].atData[1] + (ptData->tTriangleData.atVertexIndex[0].atData[0] << 8)) << 8);
  igi2_frame.aunVertIndex_4 = ptData->tTriangleData.atVertexIndex[1].atData[2]
                 + ((ptData->tTriangleData.atVertexIndex[1].atData[1]
                   + (ptData->tTriangleData.atVertexIndex[1].atData[0] << 8)) << 8);
  igi2_frame.aunVertIndex_8 = ptData->tTriangleData.atVertexIndex[2].atData[2]
                 + ((ptData->tTriangleData.atVertexIndex[2].atData[1]
                   + (ptData->tTriangleData.atVertexIndex[2].atData[0] << 8)) << 8);
  v10 = ptTree;
  ptNode = ptTree->ptNode;
  v12 = ptNode[v8].atVertexIndex[0].atData[1];
  v13 = (unsigned __int8 *)&ptNode[v8];
  v14 = v13[8] + ((v12 + (v13[6] << 8)) << 8);
  v15 = v13[10];
  igi2_frame.aunNodeVertIndex[0] = v14;
  v16 = v13[11] + ((v15 + (v13[9] << 8)) << 8);
  v17 = v13[13];
  igi2_frame.aunNodeVertIndex[1] = v16;
  igi2_frame.aunNodeVertIndex[2] = v13[14] + ((v17 + (v13[12] << 8)) << 8);
  ptRelativeVertex = ptTree->ptRelativeVertex;
  p_vX = &ptRelativeVertex[igi2_frame.aunVertIndex_4].vX;
  igi2_frame.unIb = &ptRelativeVertex[v9].vX;
  igi2_frame.aunVertIndex = v9;
  igi2_frame.v94 = ptRelativeVertex;
  igi2_frame.atEdge[0].vX = *p_vX - *igi2_frame.unIb;
  igi2_frame.atEdge[0].vY = p_vX[1] - igi2_frame.unIb[1];
  igi2_frame.atEdge[0].vZ = p_vX[2] - igi2_frame.unIb[2];
  v20 = &ptRelativeVertex[igi2_frame.aunVertIndex_8].vX;
  igi2_frame.unSplitEdges = 0;
  igi2_frame.atEdge[1].vX = *v20 - *p_vX;
  igi2_frame.atEdge[1].vY = v20[1] - p_vX[1];
  igi2_frame.atEdge[1].vZ = v20[2] - p_vX[2];
  igi2_frame.atEdge[2].vX = *igi2_frame.unIb - *v20;
  igi2_frame.atEdge[2].vY = igi2_frame.unIb[1] - v20[1];
  v21 = igi2_frame.unIb[2] - v20[2];
  v22 = *((_DWORD *)peVertexPlaneSide + 1);
  v23 = *peVertexPlaneSide;
  v24 = *peVertexPlaneSide == v22;
  igi2_frame.atEdge[2].vZ = v21;
  if ( !v24 )
  {
    igi2_frame.aunVertIndexOfSplitEdge[0] = v9;
    igi2_frame.aunEdgeToSplit[0] = 0;
    igi2_frame.unSplitEdges = 1;
  }
  v25 = *((_DWORD *)peVertexPlaneSide + 2);
  v24 = v22 == v25;
  v26 = igi2_frame.unSplitEdges;
  if ( !v24 )
  {
    igi2_frame.aunVertIndexOfSplitEdge[igi2_frame.unSplitEdges] = igi2_frame.aunVertIndex_4;
    igi2_frame.aunEdgeToSplit[igi2_frame.unSplitEdges] = 1;
    v26 = ++igi2_frame.unSplitEdges;
  }
  if ( v25 != v23 )
  {
    igi2_frame.aunVertIndexOfSplitEdge[v26] = igi2_frame.aunVertIndex_8;
    igi2_frame.aunEdgeToSplit[v26++] = 2;
    igi2_frame.unSplitEdges = v26;
  }
  v27 = 0;
  if ( v26 >= 4 )
  {
    igi2_frame.unI = 3;
    v28 = igi2_frame.atNewVertex;
    do
    {
      vX = ptRelativeVertex[igi2_frame.aunVertIndexOfSplitEdge[v27]].vX;
      v30 = &ptRelativeVertex[igi2_frame.aunVertIndexOfSplitEdge[v27]];
      vY = v30->vY;
      vZ = v30->vZ;
      v33 = 3 * igi2_frame.aunEdgeToSplit[v27];
      igi2_frame.tVertex.vZ = vZ;
      v33 *= 8;
      v34 = -((vX - ptPointInPlane->vX) * ptPlaneNormal->vX
            + (vZ - ptPointInPlane->vZ) * ptPlaneNormal->vZ
            + (vY - ptPointInPlane->vY) * ptPlaneNormal->vY);
      v35 = ptPlaneNormal->vY * *(double *)((char *)&igi2_frame.atEdge[0].vY + v33)
          + ptPlaneNormal->vZ * *(double *)((char *)&igi2_frame.atEdge[0].vZ + v33);
      v36 = ptPlaneNormal->vX * *(double *)((char *)&igi2_frame.atEdge[0].vX + v33);
      qmemcpy(v28, (char *)igi2_frame.atEdge + v33, sizeof(struct real64x3_t));
      v37 = igi2_frame.aunEdgeToSplit[v27 + 1];
      v38 = &igi2_frame.v94[igi2_frame.aunVertIndexOfSplitEdge[v27 + 1]].vX;
      igi2_frame.vT = v34 / (v35 + v36);
      v28->vX = igi2_frame.vT * v28->vX + vX;
      v28->vY = igi2_frame.vT * v28->vY + vY;
      v28->vZ = igi2_frame.vT * v28->vZ + igi2_frame.tVertex.vZ;
      v39 = *v38;
      v40 = v38[1];
      igi2_frame.tVertex.vZ = v38[2];
      v41 = v37;
      v42 = &igi2_frame.atEdge[v37];
      v43 = -((v39 - ptPointInPlane->vX) * ptPlaneNormal->vX
            + (igi2_frame.tVertex.vZ - ptPointInPlane->vZ) * ptPlaneNormal->vZ
            + (v40 - ptPointInPlane->vY) * ptPlaneNormal->vY);
      v44 = ptPlaneNormal->vY * igi2_frame.atEdge[v41].vY + ptPlaneNormal->vZ * igi2_frame.atEdge[v41].vZ;
      v45 = ptPlaneNormal->vX * v42->vX;
      qmemcpy(&v28[1], v42, sizeof(struct real64x3_t));
      v46 = &igi2_frame.v94[igi2_frame.aunVertIndexOfSplitEdge[v27 + 2]].vX;
      v47 = igi2_frame.aunEdgeToSplit[v27 + 2];
      igi2_frame.vTa = v43 / (v44 + v45);
      v28[1].vX = igi2_frame.vTa * v28[1].vX + v39;
      v28[1].vY = igi2_frame.vTa * v28[1].vY + v40;
      v28[1].vZ = igi2_frame.vTa * v28[1].vZ + igi2_frame.tVertex.vZ;
      v48 = *v46;
      v49 = v46[1];
      igi2_frame.tVertex.vZ = v46[2];
      v50 = v47;
      v51 = &igi2_frame.atEdge[v47];
      v52 = -((v48 - ptPointInPlane->vX) * ptPlaneNormal->vX
            + (igi2_frame.tVertex.vZ - ptPointInPlane->vZ) * ptPlaneNormal->vZ
            + (v49 - ptPointInPlane->vY) * ptPlaneNormal->vY);
      v53 = ptPlaneNormal->vY * igi2_frame.atEdge[v50].vY + ptPlaneNormal->vZ * igi2_frame.atEdge[v50].vZ;
      v54 = ptPlaneNormal->vX * v51->vX;
      qmemcpy(&v28[2], v51, sizeof(struct real64x3_t));
      igi2_frame.vTb = v52 / (v53 + v54);
      v55 = *((_DWORD *)&igi2_frame.tVertex.vX + v27);
      v28[2].vX = igi2_frame.vTb * v28[2].vX + v48;
      v56 = &igi2_frame.v94[v55].vX;
      v57 = igi2_frame.aunVertIndexOfSplitEdge[v27];
      v58 = igi2_frame.vTb * v28[2].vY;
      v59 = v28 + 3;
      v27 += 4;
      v28 += 4;
      v28[-2].vY = v58 + v49;
      v28[-2].vZ = igi2_frame.vTb * v28[-2].vZ + igi2_frame.tVertex.vZ;
      v60 = *v56;
      v61 = v56[1];
      igi2_frame.tVertex.vZ = v56[2];
      v62 = v57;
      v63 = &igi2_frame.atEdge[v57];
      v64 = -((v60 - ptPointInPlane->vX) * ptPlaneNormal->vX
            + (igi2_frame.tVertex.vZ - ptPointInPlane->vZ) * ptPlaneNormal->vZ
            + (v61 - ptPointInPlane->vY) * ptPlaneNormal->vY);
      v65 = ptPlaneNormal->vY * igi2_frame.atEdge[v62].vY + ptPlaneNormal->vZ * igi2_frame.atEdge[v62].vZ;
      v66 = ptPlaneNormal->vX * v63->vX;
      qmemcpy(v59, v63, sizeof(struct real64x3_t));
      ptRelativeVertex = igi2_frame.v94;
      v67 = igi2_frame.unI + 4 < igi2_frame.unSplitEdges;
      igi2_frame.unI += 4;
      igi2_frame.vTc = v64 / (v65 + v66);
      v28[-1].vX = igi2_frame.vTc * v28[-1].vX + v60;
      v28[-1].vY = igi2_frame.vTc * v28[-1].vY + v61;
      v28[-1].vZ = igi2_frame.vTc * v28[-1].vZ + igi2_frame.tVertex.vZ;
    }
    while ( v67 );
    v26 = igi2_frame.unSplitEdges;
    v10 = ptTree;
  }
  if ( v27 < v26 )
  {
    v68 = &igi2_frame.atNewVertex[v27];
    while ( 1 )
    {
      v69 = ptRelativeVertex[igi2_frame.aunVertIndexOfSplitEdge[v27]].vX;
      v70 = &ptRelativeVertex[igi2_frame.aunVertIndexOfSplitEdge[v27]];
      v71 = v70->vY;
      v72 = v70->vZ;
      v73 = 3 * igi2_frame.aunEdgeToSplit[v27];
      igi2_frame.tVertex.vZ = v72;
      v73 *= 8;
      v74 = v68;
      ++v27;
      ++v68;
      v75 = -((v69 - ptPointInPlane->vX) * ptPlaneNormal->vX
            + (v72 - ptPointInPlane->vZ) * ptPlaneNormal->vZ
            + (v71 - ptPointInPlane->vY) * ptPlaneNormal->vY);
      v76 = ptPlaneNormal->vY * *(double *)((char *)&igi2_frame.atEdge[0].vY + v73)
          + ptPlaneNormal->vZ * *(double *)((char *)&igi2_frame.atEdge[0].vZ + v73);
      v77 = ptPlaneNormal->vX * *(double *)((char *)&igi2_frame.atEdge[0].vX + v73);
      qmemcpy(v74, (char *)igi2_frame.atEdge + v73, sizeof(struct real64x3_t));
      igi2_frame.vTd = v75 / (v76 + v77);
      v68[-1].vX = igi2_frame.vTd * v68[-1].vX + v69;
      v68[-1].vY = igi2_frame.vTd * v68[-1].vY + v71;
      v68[-1].vZ = igi2_frame.vTd * v68[-1].vZ + igi2_frame.tVertex.vZ;
      if ( v27 >= igi2_frame.unSplitEdges )
        break;
      ptRelativeVertex = igi2_frame.v94;
    }
    v10 = ptTree;
  }
  BspTreeDynCubeObj_AddVertices(v10, 2u, igi2_frame.atNewVertex, 0);
  unNumVertices = v10->unNumVertices;
  v79 = unNumVertices - 2;
  igi2_frame.unIa = unNumVertices - 2;
  if ( unNumVertices >= 2 )
  {
    v80 = 12 * v79;
    for ( igi2_frame.i = 12 * v79; ; v80 = igi2_frame.i )
    {
      v81 = v10->ptRelativeVertex;
      v82 = 0;
      v83 = (float *)((char *)&v81->vX + v80);
      while ( 1 )
      {
        v84 = *v83 - v81[igi2_frame.aunNodeVertIndex[v82]].vX;
        v85 = &v81[igi2_frame.aunNodeVertIndex[v82]];
        if ( v84 < 0.0 )
          v84 = -v84;
        if ( v84 < 40.96 )
        {
          v86 = v83[1] - v85->vY;
          if ( v86 < 0.0 )
            v86 = -v86;
          if ( v86 < 40.96 )
          {
            v87 = v83[2] - v85->vZ;
            if ( v87 < 0.0 )
              v87 = -v87;
            if ( v87 < 40.96 )
              break;
          }
        }
        if ( (unsigned int)++v82 >= 3 )
          goto LABEL_32;
      }
      v88 = &v81[igi2_frame.aunNodeVertIndex[v82]].vX;
      *v83 = *v88;
      v83[1] = v88[1];
      v83[2] = v88[2];
LABEL_32:
      v67 = ++igi2_frame.unIa < v10->unNumVertices;
      igi2_frame.i += 12;
      if ( !v67 )
        break;
    }
  }
  result = (struct real32x3_t *)ptNewTriangles;
  p_tNormal = &ptNewTriangles->tTriangleData.tNormal;
  v91 = 3;
  do
  {
    p_tNormal[-2].vX = 0.0;
    HIBYTE(p_tNormal[-1].vZ) = ptData->tTriangleData.unMaterialIndex;
    *p_tNormal = ptData->tTriangleData.tNormal;
    LOBYTE(p_tNormal[-2].vZ) = 0;
    BYTE1(p_tNormal[-2].vZ) = 0;
    BYTE2(p_tNormal[-2].vZ) = 0;
    HIBYTE(p_tNormal[-2].vZ) = 0;
    LOBYTE(p_tNormal[-1].vX) = 0;
    BYTE1(p_tNormal[-1].vX) = 0;
    p_tNormal += 3;
    --v91;
  }
  while ( v91 );
  if ( *peVertexPlaneSide == *((_DWORD *)peVertexPlaneSide + 1) )
  {
    ptNewTriangles->nPlaneSide = *((_BYTE *)peVertexPlaneSide + 8);
    ptNewTriangles->tTriangleData.atVertexIndex[0].atData[2] = igi2_frame.aunVertIndex_8;
    ptNewTriangles->tTriangleData.atVertexIndex[0].atData[0] = BYTE2(igi2_frame.aunVertIndex_8);
    ptNewTriangles->tTriangleData.atVertexIndex[0].atData[1] = BYTE1(igi2_frame.aunVertIndex_8);
    ptNewTriangles->tTriangleData.atVertexIndex[1].atData[0] = (v10->unNumVertices - 2) >> 16;
    ptNewTriangles->tTriangleData.atVertexIndex[1].atData[1] = (unsigned __int16)(LOWORD(v10->unNumVertices) - 2) >> 8;
    ptNewTriangles->tTriangleData.atVertexIndex[1].atData[2] = LOBYTE(v10->unNumVertices) - 2;
    ptNewTriangles->tTriangleData.atVertexIndex[2].atData[0] = (v10->unNumVertices - 1) >> 16;
    ptNewTriangles->tTriangleData.atVertexIndex[2].atData[1] = (unsigned __int16)(LOWORD(v10->unNumVertices) - 1) >> 8;
    ptNewTriangles->tTriangleData.atVertexIndex[2].atData[2] = LOBYTE(v10->unNumVertices) - 1;
    ptNewTriangles[1].nPlaneSide = *(_BYTE *)peVertexPlaneSide;
    ptNewTriangles[1].tTriangleData.atVertexIndex[0].atData[1] = BYTE1(igi2_frame.aunVertIndex);
    ptNewTriangles[1].tTriangleData.atVertexIndex[0].atData[2] = igi2_frame.aunVertIndex;
    ptNewTriangles[1].tTriangleData.atVertexIndex[1].atData[0] = BYTE2(igi2_frame.aunVertIndex_4);
    ptNewTriangles[1].tTriangleData.atVertexIndex[1].atData[1] = BYTE1(igi2_frame.aunVertIndex_4);
    ptNewTriangles[1].tTriangleData.atVertexIndex[1].atData[2] = igi2_frame.aunVertIndex_4;
    ptNewTriangles[1].tTriangleData.atVertexIndex[0].atData[0] = BYTE2(igi2_frame.aunVertIndex);
    ptNewTriangles[1].tTriangleData.atVertexIndex[2].atData[0] = (v10->unNumVertices - 2) >> 16;
    ptNewTriangles[1].tTriangleData.atVertexIndex[2].atData[1] = (unsigned __int16)(LOWORD(v10->unNumVertices) - 2) >> 8;
    ptNewTriangles[1].tTriangleData.atVertexIndex[2].atData[2] = LOBYTE(v10->unNumVertices) - 2;
    v92 = *(_BYTE *)peVertexPlaneSide;
    ptNewTriangles[2].tTriangleData.atVertexIndex[0].atData[0] = BYTE2(igi2_frame.aunVertIndex);
    ptNewTriangles[2].nPlaneSide = v92;
    ptNewTriangles[2].tTriangleData.atVertexIndex[0].atData[1] = BYTE1(igi2_frame.aunVertIndex);
    ptNewTriangles[2].tTriangleData.atVertexIndex[0].atData[2] = igi2_frame.aunVertIndex;
    ptNewTriangles[2].tTriangleData.atVertexIndex[1].atData[0] = (v10->unNumVertices - 2) >> 16;
    ptNewTriangles[2].tTriangleData.atVertexIndex[1].atData[1] = (unsigned __int16)(LOWORD(v10->unNumVertices) - 2) >> 8;
    ptNewTriangles[2].tTriangleData.atVertexIndex[1].atData[2] = LOBYTE(v10->unNumVertices) - 2;
    ptNewTriangles[2].tTriangleData.atVertexIndex[2].atData[0] = (v10->unNumVertices - 1) >> 16;
    ptNewTriangles[2].tTriangleData.atVertexIndex[2].atData[1] = (unsigned __int16)(LOWORD(v10->unNumVertices) - 1) >> 8;
    ptNewTriangles[2].tTriangleData.atVertexIndex[2].atData[2] = LOBYTE(v10->unNumVertices) - 1;
  }
  else if ( *peVertexPlaneSide == *((_DWORD *)peVertexPlaneSide + 2) )
  {
    ptNewTriangles->nPlaneSide = *((_BYTE *)peVertexPlaneSide + 4);
    ptNewTriangles->tTriangleData.atVertexIndex[0].atData[0] = BYTE2(igi2_frame.aunVertIndex_4);
    ptNewTriangles->tTriangleData.atVertexIndex[0].atData[2] = igi2_frame.aunVertIndex_4;
    ptNewTriangles->tTriangleData.atVertexIndex[0].atData[1] = BYTE1(igi2_frame.aunVertIndex_4);
    ptNewTriangles->tTriangleData.atVertexIndex[1].atData[0] = (v10->unNumVertices - 2) >> 16;
    ptNewTriangles->tTriangleData.atVertexIndex[1].atData[1] = (unsigned __int16)(LOWORD(v10->unNumVertices) - 2) >> 8;
    ptNewTriangles->tTriangleData.atVertexIndex[1].atData[2] = LOBYTE(v10->unNumVertices) - 2;
    ptNewTriangles->tTriangleData.atVertexIndex[2].atData[0] = (v10->unNumVertices - 1) >> 16;
    ptNewTriangles->tTriangleData.atVertexIndex[2].atData[1] = (unsigned __int16)(LOWORD(v10->unNumVertices) - 1) >> 8;
    ptNewTriangles->tTriangleData.atVertexIndex[2].atData[2] = LOBYTE(v10->unNumVertices) - 1;
    ptNewTriangles[1].nPlaneSide = *(_BYTE *)peVertexPlaneSide;
    ptNewTriangles[1].tTriangleData.atVertexIndex[0].atData[1] = BYTE1(igi2_frame.aunVertIndex);
    ptNewTriangles[1].tTriangleData.atVertexIndex[0].atData[2] = igi2_frame.aunVertIndex;
    ptNewTriangles[1].tTriangleData.atVertexIndex[0].atData[0] = BYTE2(igi2_frame.aunVertIndex);
    ptNewTriangles[1].tTriangleData.atVertexIndex[1].atData[0] = (v10->unNumVertices - 2) >> 16;
    ptNewTriangles[1].tTriangleData.atVertexIndex[1].atData[1] = (unsigned __int16)(LOWORD(v10->unNumVertices) - 2) >> 8;
    ptNewTriangles[1].tTriangleData.atVertexIndex[1].atData[2] = LOBYTE(v10->unNumVertices) - 2;
    ptNewTriangles[1].tTriangleData.atVertexIndex[2].atData[0] = (v10->unNumVertices - 1) >> 16;
    ptNewTriangles[1].tTriangleData.atVertexIndex[2].atData[1] = (unsigned __int16)(LOWORD(v10->unNumVertices) - 1) >> 8;
    ptNewTriangles[1].tTriangleData.atVertexIndex[2].atData[2] = LOBYTE(v10->unNumVertices) - 1;
    ptNewTriangles[2].nPlaneSide = *((_BYTE *)peVertexPlaneSide + 8);
    ptNewTriangles[2].tTriangleData.atVertexIndex[0].atData[0] = BYTE2(igi2_frame.aunVertIndex_8);
    ptNewTriangles[2].tTriangleData.atVertexIndex[0].atData[2] = igi2_frame.aunVertIndex_8;
    ptNewTriangles[2].tTriangleData.atVertexIndex[1].atData[0] = BYTE2(igi2_frame.aunVertIndex);
    ptNewTriangles[2].tTriangleData.atVertexIndex[0].atData[1] = BYTE1(igi2_frame.aunVertIndex_8);
    ptNewTriangles[2].tTriangleData.atVertexIndex[1].atData[1] = BYTE1(igi2_frame.aunVertIndex);
    ptNewTriangles[2].tTriangleData.atVertexIndex[1].atData[2] = igi2_frame.aunVertIndex;
    ptNewTriangles[2].tTriangleData.atVertexIndex[2].atData[0] = (v10->unNumVertices - 1) >> 16;
    ptNewTriangles[2].tTriangleData.atVertexIndex[2].atData[1] = (unsigned __int16)(LOWORD(v10->unNumVertices) - 1) >> 8;
    ptNewTriangles[2].tTriangleData.atVertexIndex[2].atData[2] = LOBYTE(v10->unNumVertices) - 1;
  }
  else
  {
    ptNewTriangles->nPlaneSide = *(_BYTE *)peVertexPlaneSide;
    ptNewTriangles->tTriangleData.atVertexIndex[0].atData[0] = BYTE2(igi2_frame.aunVertIndex);
    ptNewTriangles->tTriangleData.atVertexIndex[0].atData[2] = igi2_frame.aunVertIndex;
    ptNewTriangles->tTriangleData.atVertexIndex[0].atData[1] = BYTE1(igi2_frame.aunVertIndex);
    ptNewTriangles->tTriangleData.atVertexIndex[1].atData[0] = (v10->unNumVertices - 2) >> 16;
    ptNewTriangles->tTriangleData.atVertexIndex[1].atData[1] = (unsigned __int16)(LOWORD(v10->unNumVertices) - 2) >> 8;
    ptNewTriangles->tTriangleData.atVertexIndex[1].atData[2] = LOBYTE(v10->unNumVertices) - 2;
    ptNewTriangles->tTriangleData.atVertexIndex[2].atData[0] = (v10->unNumVertices - 1) >> 16;
    ptNewTriangles->tTriangleData.atVertexIndex[2].atData[1] = (unsigned __int16)(LOWORD(v10->unNumVertices) - 1) >> 8;
    ptNewTriangles->tTriangleData.atVertexIndex[2].atData[2] = LOBYTE(v10->unNumVertices) - 1;
    ptNewTriangles[1].nPlaneSide = *((_BYTE *)peVertexPlaneSide + 4);
    ptNewTriangles[1].tTriangleData.atVertexIndex[0].atData[1] = BYTE1(igi2_frame.aunVertIndex_4);
    ptNewTriangles[1].tTriangleData.atVertexIndex[0].atData[2] = igi2_frame.aunVertIndex_4;
    ptNewTriangles[1].tTriangleData.atVertexIndex[1].atData[0] = BYTE2(igi2_frame.aunVertIndex_8);
    ptNewTriangles[1].tTriangleData.atVertexIndex[1].atData[1] = BYTE1(igi2_frame.aunVertIndex_8);
    ptNewTriangles[1].tTriangleData.atVertexIndex[1].atData[2] = igi2_frame.aunVertIndex_8;
    ptNewTriangles[1].tTriangleData.atVertexIndex[0].atData[0] = BYTE2(igi2_frame.aunVertIndex_4);
    ptNewTriangles[1].tTriangleData.atVertexIndex[2].atData[0] = (v10->unNumVertices - 1) >> 16;
    ptNewTriangles[1].tTriangleData.atVertexIndex[2].atData[1] = (unsigned __int16)(LOWORD(v10->unNumVertices) - 1) >> 8;
    ptNewTriangles[1].tTriangleData.atVertexIndex[2].atData[2] = LOBYTE(v10->unNumVertices) - 1;
    v93 = *((_BYTE *)peVertexPlaneSide + 4);
    ptNewTriangles[2].tTriangleData.atVertexIndex[0].atData[0] = BYTE2(igi2_frame.aunVertIndex_4);
    ptNewTriangles[2].nPlaneSide = v93;
    ptNewTriangles[2].tTriangleData.atVertexIndex[0].atData[1] = BYTE1(igi2_frame.aunVertIndex_4);
    ptNewTriangles[2].tTriangleData.atVertexIndex[0].atData[2] = igi2_frame.aunVertIndex_4;
    ptNewTriangles[2].tTriangleData.atVertexIndex[1].atData[0] = (v10->unNumVertices - 1) >> 16;
    ptNewTriangles[2].tTriangleData.atVertexIndex[1].atData[1] = (unsigned __int16)(LOWORD(v10->unNumVertices) - 1) >> 8;
    ptNewTriangles[2].tTriangleData.atVertexIndex[1].atData[2] = LOBYTE(v10->unNumVertices) - 1;
    ptNewTriangles[2].tTriangleData.atVertexIndex[2].atData[0] = (v10->unNumVertices - 2) >> 16;
    ptNewTriangles[2].tTriangleData.atVertexIndex[2].atData[1] = (unsigned __int16)(LOWORD(v10->unNumVertices) - 2) >> 8;
    ptNewTriangles[2].tTriangleData.atVertexIndex[2].atData[2] = LOBYTE(v10->unNumVertices) - 2;
  }
  return result;
}

// source: e/3/bsptree.c:1287  [anchor-mhash]
void __cdecl BspTreeDynCubeObj_FindLineIntersection1(
        struct BspTreeDynCubeObj_s *ptTree,
        struct World_s *ptWorld,
        struct real64x3_t *ptStartPoint,
        struct real64x3_t *ptEndPoint,
        struct QIntersection_s *ptIntersection)
{
  #pragma pack(push, 1)
  union
  {
    struct { unsigned int unLayer; };
    struct { char igi2_o1[4]; unsigned int unNode; };
    struct { char igi2_o2[8]; unsigned int unLastNode; };
    struct { char igi2_o3[8]; float unLastNodea; };
    struct { char igi2_o4[12]; float tHitPos; };
    struct { char igi2_o5[16]; float tHitPos_4; };
    struct { char igi2_o6[20]; float tHitPos_8; };
    struct { char igi2_o7[20]; float tHitPos_8a; };
    struct { char igi2_o8[24]; float tRelativeStartPoint; };
    struct { char igi2_o9[28]; float tRelativeStartPoint_4; };
    struct { char igi2_o10[32]; float tRelativeStartPoint_8; };
    struct { char igi2_o11[36]; enum BspPlaneSide_e eEndPointSide; };
    struct { char igi2_o12[40]; float tLineDelta; };
    struct { char igi2_o13[44]; float tLineDelta_4; };
    struct { char igi2_o14[48]; float tLineDelta_8; };
    struct { char igi2_o15[64]; float *v50; };
    struct { char igi2_o16[80]; struct real32x3_t ptNormal; };
    struct { char igi2_o17[92]; struct real32x3_t tRelativeEndPoint; };
    struct { char igi2_o18[104]; int v53; };
    struct { char igi2_o19[108]; float vU; };
    struct { char igi2_o20[112]; float v55; };
    struct { char igi2_o21[116]; float v56; };
    struct { char igi2_o22[120]; float v57; };
    struct { char igi2_o23[124]; int p_tNormal; };
    struct { char igi2_o24[128]; int v59; };
    struct { char igi2_o25[132]; float vV; };
    struct { char igi2_o26[136]; struct real32x3_t tRelativeHitPos; };
    struct { char igi2_o27[148]; struct real32x3_t atEdge[2]; };
    struct { char igi2_o28[172]; unsigned int aunNodeStack[500]; };
    struct { char igi2_o29[2172]; enum BspPlaneSide_e aeStartPointSide[500]; };
    char igi2_extent[4172];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct BspTreeDynCubeObj_s *v5; // ebx
  int v6; // ecx
  double vY; // st7
  double v8; // st7
  struct BspTreeNode_s *ptNode; // edi
  int v10; // ecx
  float *p_vX; // eax
  enum BspPlaneSide_e v12; // eax
  int v13; // edi
  unsigned int v14; // edi
  struct BspTreeNode_s *v15; // ecx
  unsigned int v16; // edi
  struct real32x3_t *ptRelativeVertex; // edx
  float *v18; // edx
  float v19; // eax
  double v20; // st7
  float v21; // edx
  enum BspPlaneSide_e v22; // edx
  int v23; // eax
  int v24; // edx
  struct real32x3_t *v25; // ecx
  float *v26; // ecx
  struct real32x3_t *v27; // eax
  double v28; // st7
  float v29; // edx
  float v30; // eax
  float v31; // eax
  double v32; // st7
  float v33; // edx
  double v34; // st7

  v5 = ptTree;
  ptIntersection->isHit = 0;
  if ( ptTree->unNumNodes )
  {
    v6 = 1;
    igi2_frame.unNode = 1;
    igi2_frame.tRelativeStartPoint = ptStartPoint->vX - ptTree->tOrigin.vX;
    igi2_frame.unLayer = 1;
    vY = ptStartPoint->vY;
    igi2_frame.aunNodeStack[0] = 0;
    v8 = vY - ptTree->tOrigin.vY;
    igi2_frame.aunNodeStack[1] = 1;
    igi2_frame.tRelativeStartPoint_4 = v8;
    igi2_frame.tRelativeStartPoint_8 = ptStartPoint->vZ - ptTree->tOrigin.vZ;
    igi2_frame.tRelativeEndPoint.vX = ptEndPoint->vX - ptTree->tOrigin.vX;
    igi2_frame.tRelativeEndPoint.vY = ptEndPoint->vY - ptTree->tOrigin.vY;
    igi2_frame.tRelativeEndPoint.vZ = ptEndPoint->vZ - ptTree->tOrigin.vZ;
    igi2_frame.tLineDelta = igi2_frame.tRelativeEndPoint.vX - igi2_frame.tRelativeStartPoint;
    igi2_frame.tLineDelta_4 = igi2_frame.tRelativeEndPoint.vY - igi2_frame.tRelativeStartPoint_4;
    igi2_frame.tLineDelta_8 = igi2_frame.tRelativeEndPoint.vZ - igi2_frame.tRelativeStartPoint_8;
    while ( 1 )
    {
      ptNode = v5->ptNode;
      while ( 1 )
      {
        v10 = v6;
        p_vX = &v5->ptRelativeVertex[256
                                   * (ptNode[v10].atVertexIndex[0].atData[1]
                                    + (ptNode[v10].atVertexIndex[0].atData[0] << 8))
                                   + ptNode[v10].atVertexIndex[0].atData[2]].vX;
        v12 = ptNode[v10].tNormal.vZ * (igi2_frame.tRelativeStartPoint_8 - p_vX[2])
            + ptNode[v10].tNormal.vY * (igi2_frame.tRelativeStartPoint_4 - p_vX[1])
            + ptNode[v10].tNormal.vX * (igi2_frame.tRelativeStartPoint - *p_vX) < 0.0;
        igi2_frame.aeStartPointSide[igi2_frame.unLayer] = v12;
        if ( !v5->unNumNodes )
          break;
        v13 = ptNode->atChildIndex[0].atData[2 * v12 + 2 + v12 + v10 * 28]
            + ((ptNode->atChildIndex[0].atData[2 * v12 + 1 + v12 + v10 * 28]
              + (ptNode->atChildIndex[0].atData[2 * v12 + v12 + v10 * 28] << 8)) << 8);
        igi2_frame.v53 = v13 != 0;
        if ( !v13 )
          break;
        igi2_frame.aunNodeStack[igi2_frame.unLayer] = igi2_frame.unNode;
        ptNode = v5->ptNode;
        v6 = ptNode->atChildIndex[0].atData[2 * v12 + 2 + v12 + v10 * 28]
           + ((ptNode->atChildIndex[0].atData[2 * v12 + 1 + v12 + v10 * 28]
             + (ptNode->atChildIndex[0].atData[2 * v12 + v12 + v10 * 28] << 8)) << 8);
        igi2_frame.unNode = v6;
        ++igi2_frame.unLayer;
      }
      v14 = igi2_frame.unNode;
      igi2_frame.unLastNode = igi2_frame.unNode;
      while ( 1 )
      {
        v15 = v5->ptNode;
        v16 = v14;
        ptRelativeVertex = v5->ptRelativeVertex;
        igi2_frame.v59 = ((v15[v16].atVertexIndex[0].atData[1] + (v15[v16].atVertexIndex[0].atData[0] << 8)) << 8)
            + v15[v16].atVertexIndex[0].atData[2];
        v18 = &ptRelativeVertex[igi2_frame.v59].vX;
        v19 = v18[1];
        v20 = igi2_frame.tRelativeEndPoint.vX - *v18;
        v21 = v18[2];
        igi2_frame.p_tNormal = (int)&v15[v16].tNormal;
        v22 = v15[v16].tNormal.vZ * (igi2_frame.tRelativeEndPoint.vZ - v21)
            + v15[v16].tNormal.vY * (igi2_frame.tRelativeEndPoint.vY - v19)
            + *(float *)igi2_frame.p_tNormal * v20 < 0.0;
        igi2_frame.eEndPointSide = v22;
        if ( ptIntersection->isHit
          || v22 == igi2_frame.aeStartPointSide[igi2_frame.unLayer]
          || (igi2_frame.v53 = ((v15->atChildIndex[0].atData[2 * v22 + 1 + v22 + v16 * 28]
                    + (v15->atChildIndex[0].atData[2 * v22 + v22 + v16 * 28] << 8)) << 8)
                  + v15->atChildIndex[0].atData[2 * v22 + 2 + v22 + v16 * 28],
              igi2_frame.unLastNode == igi2_frame.v53) )
        {
          igi2_frame.unLastNode = igi2_frame.unNode;
          goto LABEL_19;
        }
        v23 = v15[v16].atVertexIndex[1].atData[2]
            + ((v15[v16].atVertexIndex[1].atData[1] + (v15[v16].atVertexIndex[1].atData[0] << 8)) << 8);
        v5 = ptTree;
        v24 = v15[v16].atVertexIndex[2].atData[2]
            + ((v15[v16].atVertexIndex[2].atData[1] + (v15[v16].atVertexIndex[2].atData[0] << 8)) << 8);
        v25 = ptTree->ptRelativeVertex;
        igi2_frame.v50 = &v25[v23].vX;
        v26 = &v25[igi2_frame.v59].vX;
        igi2_frame.atEdge[0].vX = *igi2_frame.v50 - *v26;
        igi2_frame.atEdge[0].vY = igi2_frame.v50[1] - v26[1];
        v27 = &ptTree->ptRelativeVertex[v24];
        igi2_frame.atEdge[0].vZ = igi2_frame.v50[2] - v26[2];
        igi2_frame.atEdge[1].vX = v27->vX - *v26;
        igi2_frame.atEdge[1].vY = v27->vY - v26[1];
        v28 = v27->vZ - v26[2];
        igi2_frame.ptNormal.vX = *(float *)igi2_frame.p_tNormal;
        v29 = *(float *)(igi2_frame.p_tNormal + 4);
        v30 = *(float *)(igi2_frame.p_tNormal + 8);
        igi2_frame.atEdge[1].vZ = v28;
        igi2_frame.ptNormal.vY = v29;
        igi2_frame.ptNormal.vZ = v30;
        igi2_frame.v55 = *v26;
        v31 = v26[1];
        igi2_frame.v57 = v26[2];
        igi2_frame.v56 = v31;
        v32 = ((igi2_frame.v57 - igi2_frame.tRelativeStartPoint_8) * igi2_frame.ptNormal.vZ
             + (v31 - igi2_frame.tRelativeStartPoint_4) * igi2_frame.ptNormal.vY
             + (igi2_frame.v55 - igi2_frame.tRelativeStartPoint) * igi2_frame.ptNormal.vX)
            / (igi2_frame.ptNormal.vZ * igi2_frame.tLineDelta_8 + igi2_frame.ptNormal.vY * igi2_frame.tLineDelta_4 + igi2_frame.ptNormal.vX * igi2_frame.tLineDelta);
        igi2_frame.unLastNodea = v32;
        if ( v32 < 0.0 )
          break;
        if ( igi2_frame.unLastNodea > 1.0 )
          break;
        igi2_frame.tHitPos_8a = igi2_frame.tLineDelta_8 * igi2_frame.unLastNodea;
        igi2_frame.tHitPos = igi2_frame.unLastNodea * igi2_frame.tLineDelta + igi2_frame.tRelativeStartPoint;
        igi2_frame.tHitPos_4 = igi2_frame.tLineDelta_4 * igi2_frame.unLastNodea + igi2_frame.tRelativeStartPoint_4;
        igi2_frame.tHitPos_8 = igi2_frame.tHitPos_8a + igi2_frame.tRelativeStartPoint_8;
        igi2_frame.tRelativeHitPos.vX = igi2_frame.tHitPos - *v26;
        igi2_frame.tRelativeHitPos.vY = igi2_frame.tHitPos_4 - v26[1];
        igi2_frame.tRelativeHitPos.vZ = igi2_frame.tHitPos_8 - v26[2];
        if ( !Real32x3_PointOnTriangle(&igi2_frame.vU, &igi2_frame.vV, &igi2_frame.tRelativeHitPos, igi2_frame.atEdge, &igi2_frame.atEdge[1], &igi2_frame.ptNormal) )
          break;
        v33 = igi2_frame.vV;
        ptIntersection->tHitUV.vX = igi2_frame.vU;
        ptIntersection->tHitUV.vY = v33;
        ptIntersection->iFace = 0;
        ptIntersection->isDoubleFace = 0;
        ptIntersection->iSector = 0;
        ptIntersection->isHit = 1;
        ptIntersection->ptEnterMaterial = nullptr;
        ptIntersection->ptHitObj = nullptr;
        ptIntersection->ptLeaveMaterial = nullptr;
        ptIntersection->tLocalNormal.vX = 0.0;
        ptIntersection->tLocalNormal.vY = 0.0;
        ptIntersection->tLocalNormal.vZ = 0.0;
        ptIntersection->tLocalPos.vX = 0.0;
        ptIntersection->tLocalPos.vY = 0.0;
        ptIntersection->tLocalPos.vZ = 0.0;
        ptIntersection->tNormal = ptTree->ptNode[v16].tNormal;
        ptIntersection->tPos.vX = igi2_frame.tHitPos + ptTree->tOrigin.vX;
        ptIntersection->tPos.vY = igi2_frame.tHitPos_4 + ptTree->tOrigin.vY;
        ptIntersection->tPos.vZ = igi2_frame.tHitPos_8 + ptTree->tOrigin.vZ;
        v34 = igi2_frame.unLastNodea;
        igi2_frame.unLastNode = igi2_frame.unNode;
        ptIntersection->vDistance = v34;
LABEL_19:
        v14 = *((_DWORD *)&igi2_frame.atEdge[1].vZ + igi2_frame.unLayer--);
        igi2_frame.unNode = v14;
        if ( !v14 )
          goto LABEL_22;
      }
      if ( !ptTree->unNumNodes || !igi2_frame.v53 )
        break;
      igi2_frame.aunNodeStack[igi2_frame.unLayer] = igi2_frame.unNode;
      igi2_frame.unNode = ((ptTree->ptNode[igi2_frame.unNode].atChildIndex[igi2_frame.eEndPointSide].atData[1]
               + (ptTree->ptNode[igi2_frame.unNode].atChildIndex[igi2_frame.eEndPointSide].atData[0] << 8)) << 8)
             + ptTree->ptNode[igi2_frame.unNode].atChildIndex[igi2_frame.eEndPointSide].atData[2];
      v6 = igi2_frame.unNode;
      ++igi2_frame.unLayer;
      if ( !igi2_frame.unNode )
      {
LABEL_22:
        if ( ptIntersection->isHit )
          ptIntersection->vDistance = sqrt(
                                        igi2_frame.tLineDelta * igi2_frame.tLineDelta
                                      + igi2_frame.tLineDelta_4 * igi2_frame.tLineDelta_4
                                      + igi2_frame.tLineDelta_8 * igi2_frame.tLineDelta_8)
                                    * ptIntersection->vDistance;
        return;
      }
    }
    igi2_frame.unLastNode = igi2_frame.unNode;
    goto LABEL_19;
  }
}

// source: e/3/bsptree.c:1525  [anchor-mhash]
void __cdecl BspTreeDynCubeObj_FindLineIntersection2(
        struct BspTreeDynCubeObj_s *ptTree,
        struct World_s *ptWorld,
        struct real64x3_t *ptStartPoint,
        struct real64x3_t *ptEndPoint,
        struct QIntersection_s *ptIntersection)
{
  #pragma pack(push, 1)
  union
  {
    struct { int vT; };
    struct { float vTa; };
    struct { char igi2_o2[4]; unsigned int v35; };
    struct { char igi2_o3[8]; unsigned int unNode; };
    struct { char igi2_o4[12]; struct real32x3_t *ptRelativeVertex; };
    struct { char igi2_o5[16]; unsigned int *v38; };
    struct { char igi2_o6[20]; enum BspPlaneSide_e eStartPointSide; };
    struct { char igi2_o7[24]; float tHitPos; };
    struct { char igi2_o8[28]; float tHitPos_4; };
    struct { char igi2_o9[32]; float tHitPos_8; };
    struct { char igi2_o10[32]; float tHitPos_8a; };
    struct { char igi2_o11[36]; float tRelativeStartPoint; };
    struct { char igi2_o12[40]; float tRelativeStartPoint_4; };
    struct { char igi2_o13[44]; float tRelativeStartPoint_8; };
    struct { char igi2_o14[48]; unsigned int unStackSize; };
    struct { char igi2_o15[52]; float tLineDelta; };
    struct { char igi2_o16[56]; float tLineDelta_4; };
    struct { char igi2_o17[60]; float tLineDelta_8; };
    struct { char igi2_o18[64]; struct real32x3_t tPlaneNormal; };
    struct { char igi2_o19[76]; struct real32x3_t tPointInPlane; };
    struct { char igi2_o20[88]; struct real32x3_t tRelativeEndPoint; };
    struct { char igi2_o21[100]; enum BspPlaneSide_e eEndPointSide; };
    struct { char igi2_o22[104]; float v55; };
    struct { char igi2_o23[108]; float v56; };
    struct { char igi2_o24[112]; float vZ; };
    struct { char igi2_o25[116]; float v58; };
    struct { char igi2_o26[120]; float v59; };
    struct { char igi2_o27[124]; float v60; };
    struct { char igi2_o28[128]; float vU; };
    struct { char igi2_o29[132]; float vV; };
    struct { char igi2_o30[136]; struct real32x3_t tRelativeHitPos; };
    struct { char igi2_o31[148]; struct real32x3_t atEdge[2]; };
    struct { char igi2_o32[172]; unsigned int uiVertIndex[3]; };
    struct { char igi2_o33[184]; unsigned int aunLayerStack[500]; };
    struct { char igi2_o34[2184]; unsigned int aunNodeStack[500]; };
    struct { char igi2_o35[4184]; unsigned int aunParentStack[500]; };
    char igi2_extent[6184];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QIntersection_s *v5; // edx
  struct BspTreeDynCubeObj_s *v6; // ebx
  double vX; // st7
  int v8; // eax
  int v9; // esi
  unsigned int v10; // eax
  unsigned int *i; // ecx
  struct BspTreeNode_s *ptNode; // edi
  unsigned int v13; // esi
  struct real32x3_t *v14; // eax
  float vY; // ebx
  double v16; // st6
  float v17; // ebx
  int v18; // edx
  float v19; // ecx
  float *p_vX; // ecx
  float v21; // ebx
  double v22; // st7
  int v23; // eax
  struct real32x3_t *v24; // edx
  float *v25; // eax
  double v26; // st7
  float *v27; // eax
  char v28; // al
  bool v29; // zf
  int isHit; // eax
  float v31; // eax
  int v32; // eax

  v5 = ptIntersection;
  v6 = ptTree;
  ptIntersection->isHit = 0;
  if ( !ptTree->unNumNodes )
    return;
  vX = ptStartPoint->vX;
  igi2_frame.aunLayerStack[0] = 0;
  igi2_frame.tRelativeStartPoint = vX - ptTree->tOrigin.vX;
  igi2_frame.tRelativeStartPoint_4 = ptStartPoint->vY - ptTree->tOrigin.vY;
  igi2_frame.tRelativeStartPoint_8 = ptStartPoint->vZ - ptTree->tOrigin.vZ;
  igi2_frame.tRelativeEndPoint.vX = ptEndPoint->vX - ptTree->tOrigin.vX;
  igi2_frame.tRelativeEndPoint.vY = ptEndPoint->vY - ptTree->tOrigin.vY;
  v8 = 1;
  igi2_frame.tRelativeEndPoint.vZ = ptEndPoint->vZ - ptTree->tOrigin.vZ;
  igi2_frame.aunNodeStack[0] = 1;
  igi2_frame.tLineDelta = igi2_frame.tRelativeEndPoint.vX - igi2_frame.tRelativeStartPoint;
  igi2_frame.tLineDelta_4 = igi2_frame.tRelativeEndPoint.vY - igi2_frame.tRelativeStartPoint_4;
  igi2_frame.tLineDelta_8 = igi2_frame.tRelativeEndPoint.vZ - igi2_frame.tRelativeStartPoint_8;
  while ( 2 )
  {
    v9 = igi2_frame.aunLayerStack[v8 + 499];
    igi2_frame.unStackSize = v8 - 1;
    v10 = igi2_frame.aunLayerStack[v8 - 1];
    igi2_frame.v35 = v10 + 1;
    for ( i = &igi2_frame.aunParentStack[v10]; ; i = igi2_frame.v38 + 1 )
    {
      while ( 1 )
      {
        ptNode = v6->ptNode;
        igi2_frame.unNode = v9;
        v13 = v9;
        igi2_frame.vT = ptNode[v13].atVertexIndex[0].atData[2]
           + ((ptNode[v13].atVertexIndex[0].atData[1] + (ptNode[v13].atVertexIndex[0].atData[0] << 8)) << 8);
        v14 = &ptTree->ptRelativeVertex[igi2_frame.vT];
        igi2_frame.ptRelativeVertex = ptTree->ptRelativeVertex;
        igi2_frame.tPointInPlane.vX = v14->vX;
        vY = v14->vY;
        igi2_frame.tPointInPlane.vZ = v14->vZ;
        igi2_frame.tPointInPlane.vY = vY;
        v16 = igi2_frame.tRelativeStartPoint_4 - vY;
        igi2_frame.v55 = ptNode[v13].tNormal.vX;
        v17 = ptNode[v13].tNormal.vY;
        igi2_frame.vZ = ptNode[v13].tNormal.vZ;
        igi2_frame.v56 = v17;
        igi2_frame.v38 = i;
        igi2_frame.eStartPointSide = igi2_frame.vZ * (igi2_frame.tRelativeStartPoint_8 - igi2_frame.tPointInPlane.vZ)
                        + v17 * v16
                        + igi2_frame.v55 * (igi2_frame.tRelativeStartPoint - igi2_frame.tPointInPlane.vX) < 0.0;
        igi2_frame.eEndPointSide = igi2_frame.vZ * (igi2_frame.tRelativeEndPoint.vZ - igi2_frame.tPointInPlane.vZ)
                      + v17 * (igi2_frame.tRelativeEndPoint.vY - igi2_frame.tPointInPlane.vY)
                      + igi2_frame.v55 * (igi2_frame.tRelativeEndPoint.vX - igi2_frame.tPointInPlane.vX) < 0.0;
        if ( igi2_frame.eStartPointSide == igi2_frame.eEndPointSide )
        {
          v6 = ptTree;
          if ( !ptTree->unNumNodes )
            goto LABEL_31;
          v9 = ((ptNode->atChildIndex[0].atData[2 * igi2_frame.eStartPointSide + 1 + igi2_frame.eStartPointSide + v13 * 28]
               + (ptNode->atChildIndex[0].atData[2 * igi2_frame.eStartPointSide + igi2_frame.eStartPointSide + v13 * 28] << 8)) << 8)
             + ptNode->atChildIndex[0].atData[2 * igi2_frame.eStartPointSide + 2 + igi2_frame.eStartPointSide + v13 * 28];
          if ( !v9 )
            goto LABEL_31;
          goto LABEL_26;
        }
        v18 = ptNode[v13].atVertexIndex[1].atData[2]
            + ((ptNode[v13].atVertexIndex[1].atData[1] + (ptNode[v13].atVertexIndex[1].atData[0] << 8)) << 8);
        v19 = ptNode[v13].tNormal.vY;
        igi2_frame.uiVertIndex[2] = ptNode[v13].atVertexIndex[2].atData[2]
                       + ((ptNode[v13].atVertexIndex[2].atData[1] + (ptNode[v13].atVertexIndex[2].atData[0] << 8)) << 8);
        igi2_frame.tPlaneNormal.vX = ptNode[v13].tNormal.vX;
        igi2_frame.tPlaneNormal.vZ = ptNode[v13].tNormal.vZ;
        igi2_frame.tPlaneNormal.vY = v19;
        p_vX = &igi2_frame.ptRelativeVertex[igi2_frame.vT].vX;
        igi2_frame.v58 = *p_vX;
        v21 = p_vX[1];
        igi2_frame.v60 = p_vX[2];
        igi2_frame.v59 = v21;
        v22 = ((igi2_frame.v60 - igi2_frame.tRelativeStartPoint_8) * igi2_frame.tPlaneNormal.vZ
             + (v21 - igi2_frame.tRelativeStartPoint_4) * igi2_frame.tPlaneNormal.vY
             + (igi2_frame.v58 - igi2_frame.tRelativeStartPoint) * igi2_frame.tPlaneNormal.vX)
            / (igi2_frame.tPlaneNormal.vZ * igi2_frame.tLineDelta_8 + igi2_frame.tPlaneNormal.vY * igi2_frame.tLineDelta_4 + igi2_frame.tPlaneNormal.vX * igi2_frame.tLineDelta);
        igi2_frame.vTa = v22;
        if ( v22 < 0.0 || igi2_frame.vTa > 1.0 )
          break;
        v6 = ptTree;
        v23 = v18;
        v24 = ptTree->ptRelativeVertex;
        igi2_frame.tHitPos_8a = igi2_frame.tLineDelta_8 * igi2_frame.vTa;
        v25 = &v24[v23].vX;
        igi2_frame.tHitPos = igi2_frame.vTa * igi2_frame.tLineDelta + igi2_frame.tRelativeStartPoint;
        igi2_frame.tHitPos_4 = igi2_frame.tLineDelta_4 * igi2_frame.vTa + igi2_frame.tRelativeStartPoint_4;
        igi2_frame.tHitPos_8 = igi2_frame.tHitPos_8a + igi2_frame.tRelativeStartPoint_8;
        igi2_frame.tRelativeHitPos.vX = igi2_frame.tHitPos - *p_vX;
        igi2_frame.tRelativeHitPos.vY = igi2_frame.tHitPos_4 - p_vX[1];
        igi2_frame.tRelativeHitPos.vZ = igi2_frame.tHitPos_8 - p_vX[2];
        igi2_frame.atEdge[0].vX = *v25 - *p_vX;
        igi2_frame.atEdge[0].vY = v25[1] - p_vX[1];
        v26 = v25[2];
        v27 = &v24[igi2_frame.uiVertIndex[2]].vX;
        igi2_frame.atEdge[0].vZ = v26 - p_vX[2];
        igi2_frame.atEdge[1].vX = *v27 - *p_vX;
        igi2_frame.atEdge[1].vY = v27[1] - p_vX[1];
        igi2_frame.atEdge[1].vZ = v27[2] - p_vX[2];
        v28 = Real32x3_PointOnTriangle(&igi2_frame.vU, &igi2_frame.vV, &igi2_frame.tRelativeHitPos, igi2_frame.atEdge, &igi2_frame.atEdge[1], &igi2_frame.tPlaneNormal);
        v5 = ptIntersection;
        v29 = v28 == 0;
        isHit = ptIntersection->isHit;
        if ( v29 )
        {
          if ( !isHit || igi2_frame.vTa <= ptIntersection->vDistance )
          {
            if ( !ptTree->unNumNodes )
              goto LABEL_31;
            v32 = (((ptNode->atChildIndex[0].atData[2 * igi2_frame.eEndPointSide + igi2_frame.eEndPointSide + v13 * 28] << 8)
                  + ptNode->atChildIndex[0].atData[2 * igi2_frame.eEndPointSide + 1 + igi2_frame.eEndPointSide + v13 * 28]) << 8)
                + ptNode->atChildIndex[0].atData[2 * igi2_frame.eEndPointSide + 2 + igi2_frame.eEndPointSide + v13 * 28];
            if ( v32 )
            {
              igi2_frame.aunNodeStack[igi2_frame.unStackSize] = v32;
              igi2_frame.aunLayerStack[igi2_frame.unStackSize++] = igi2_frame.v35;
            }
          }
          if ( !ptTree->unNumNodes )
            goto LABEL_31;
          v9 = ((ptNode->atChildIndex[0].atData[2 * igi2_frame.eStartPointSide + 1 + igi2_frame.eStartPointSide + v13 * 28]
               + (ptNode->atChildIndex[0].atData[2 * igi2_frame.eStartPointSide + igi2_frame.eStartPointSide + v13 * 28] << 8)) << 8)
             + ptNode->atChildIndex[0].atData[2 * igi2_frame.eStartPointSide + 2 + igi2_frame.eStartPointSide + v13 * 28];
          if ( !v9 )
            goto LABEL_31;
        }
        else
        {
          if ( !isHit || igi2_frame.vTa < ptIntersection->vDistance )
          {
            ptIntersection->tHitUV.vX = igi2_frame.vU;
            v31 = igi2_frame.vV;
            ptIntersection->iFace = 0;
            ptIntersection->isDoubleFace = 0;
            ptIntersection->iSector = 0;
            ptIntersection->ptEnterMaterial = nullptr;
            ptIntersection->ptHitObj = nullptr;
            ptIntersection->ptLeaveMaterial = nullptr;
            ptIntersection->tLocalNormal.vX = 0.0;
            ptIntersection->tLocalNormal.vY = 0.0;
            ptIntersection->tLocalNormal.vZ = 0.0;
            ptIntersection->tLocalPos.vX = 0.0;
            ptIntersection->tLocalPos.vY = 0.0;
            ptIntersection->tLocalPos.vZ = 0.0;
            ptIntersection->tHitUV.vY = v31;
            ptIntersection->isHit = 1;
            ptIntersection->tNormal = ptTree->ptNode[v13].tNormal;
            ptIntersection->tPos.vX = igi2_frame.tHitPos + ptTree->tOrigin.vX;
            ptIntersection->tPos.vY = igi2_frame.tHitPos_4 + ptTree->tOrigin.vY;
            ptIntersection->tPos.vZ = igi2_frame.tHitPos_8 + ptTree->tOrigin.vZ;
            ptIntersection->vDistance = igi2_frame.vTa;
          }
          if ( !ptTree->unNumNodes )
            goto LABEL_31;
          v9 = ((ptTree->ptNode->atChildIndex[igi2_frame.eStartPointSide].atData[v13 * 28 + 1]
               + (ptTree->ptNode->atChildIndex[igi2_frame.eStartPointSide].atData[v13 * 28] << 8)) << 8)
             + ptTree->ptNode->atChildIndex[igi2_frame.eStartPointSide].atData[v13 * 28 + 2];
          if ( !v9 )
            goto LABEL_31;
        }
        i = igi2_frame.v38;
LABEL_26:
        *i = igi2_frame.unNode;
        ++igi2_frame.v35;
        ++i;
      }
      v6 = ptTree;
      if ( !ptTree->unNumNodes )
        break;
      v9 = ((ptNode->atChildIndex[0].atData[2 * igi2_frame.eStartPointSide + 1 + igi2_frame.eStartPointSide + v13 * 28]
           + (ptNode->atChildIndex[0].atData[2 * igi2_frame.eStartPointSide + igi2_frame.eStartPointSide + v13 * 28] << 8)) << 8)
         + ptNode->atChildIndex[0].atData[2 * igi2_frame.eStartPointSide + 2 + igi2_frame.eStartPointSide + v13 * 28];
      if ( !v9 )
        break;
      *igi2_frame.v38 = igi2_frame.unNode;
      ++igi2_frame.v35;
      v5 = ptIntersection;
    }
    v5 = ptIntersection;
LABEL_31:
    if ( igi2_frame.unStackSize )
    {
      v8 = igi2_frame.unStackSize;
      continue;
    }
    break;
  }
  if ( v5->isHit )
    v5->vDistance = sqrt(igi2_frame.tLineDelta * igi2_frame.tLineDelta + igi2_frame.tLineDelta_4 * igi2_frame.tLineDelta_4 + igi2_frame.tLineDelta_8 * igi2_frame.tLineDelta_8)
                  * v5->vDistance;
}

// source: e/3/bsptree.c:1788  [anchor-mhash]
void __cdecl BspTreeDynCubeObj_Validate(struct BspTreeDynCubeObj_s *ptTree)
{
  #pragma pack(push, 1)
  union
  {
    struct { float avPlaneSideValue[3]; };
    struct { char igi2_o1[12]; unsigned int v35; };
    struct { char igi2_o2[16]; unsigned int unDeepestLayer; };
    struct { char igi2_o3[20]; enum BspPlaneSide_e aePlaneSide[3]; };
    struct { char igi2_o4[32]; struct real32x3_t tNormal; };
    struct { char igi2_o5[44]; struct real32x3_t tPointInPlane; };
    struct { char igi2_o6[56]; unsigned int aunVertIndex[3]; };
    struct { char igi2_o7[68]; unsigned int aunSidesChecked[500]; };
    struct { char igi2_o8[2068]; unsigned int aunNodeStack[500]; };
    char igi2_extent[4068];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct BspTreeDynCubeObj_s *v1; // ebx
  unsigned int unNumNodes; // edx
  unsigned int v3; // esi
  unsigned int v4; // eax
  unsigned int v5; // edi
  int v6; // ecx
  int v7; // ecx
  struct BspTreeNode_s *ptNode; // edx
  unsigned int v9; // eax
  struct real32x3_t *ptRelativeVertex; // ebx
  float *p_vX; // ecx
  float *v12; // eax
  float v13; // ebp
  float v14; // eax
  float v15; // ecx
  double v16; // st7
  double v17; // st6
  double vX; // st5
  unsigned __int8 *v19; // eax
  int v20; // edx
  int v21; // ecx
  int v22; // edx
  int v23; // ecx
  int v24; // eax
  unsigned int i; // ecx
  double v26; // st4
  int v27; // ecx
  double v28; // st7
  double v29; // st6
  double v30; // st6
  double v31; // st7
  double v32; // st7
  double v33; // st7

  v1 = ptTree;
  unNumNodes = ptTree->unNumNodes;
  igi2_frame.unDeepestLayer = 0;
  igi2_frame.v35 = unNumNodes;
  if ( unNumNodes >= 2 )
  {
    igi2_frame.aunNodeStack[0] = 1;
    v3 = 0;
    igi2_frame.aunSidesChecked[0] = 0;
    do
    {
      v4 = igi2_frame.aunSidesChecked[v3];
      v5 = igi2_frame.aunNodeStack[v3];
      if ( v4 )
      {
        if ( v4 == 1 )
        {
          igi2_frame.aunSidesChecked[v3] = 2;
          if ( unNumNodes )
          {
            v7 = v1->ptNode[v5].atChildIndex[1].atData[2]
               + ((v1->ptNode[v5].atChildIndex[1].atData[1] + (v1->ptNode[v5].atChildIndex[1].atData[0] << 8)) << 8);
            if ( v7 )
            {
              ++v3;
              v5 = v1->ptNode[v5].atChildIndex[1].atData[2]
                 + ((v1->ptNode[v5].atChildIndex[1].atData[1] + (v1->ptNode[v5].atChildIndex[1].atData[0] << 8)) << 8);
              igi2_frame.aunNodeStack[v3] = v7;
              igi2_frame.aunSidesChecked[v3] = 0;
            }
          }
        }
        else if ( v5 > 1 )
        {
          if ( v3 > igi2_frame.unDeepestLayer )
            igi2_frame.unDeepestLayer = v3;
          ptNode = v1->ptNode;
          v9 = igi2_frame.aunSidesChecked[v3 + 499];
          ptRelativeVertex = v1->ptRelativeVertex;
          p_vX = &ptNode[v9].tNormal.vX;
          v12 = &ptRelativeVertex[256
                                * (ptNode[v9].atVertexIndex[0].atData[1] + (ptNode[v9].atVertexIndex[0].atData[0] << 8))
                                + ptNode[v9].atVertexIndex[0].atData[2]].vX;
          igi2_frame.tPointInPlane.vX = *v12;
          v13 = v12[1];
          igi2_frame.tPointInPlane.vZ = v12[2];
          igi2_frame.tNormal.vX = *p_vX;
          v14 = p_vX[1];
          v15 = p_vX[2];
          igi2_frame.tNormal.vY = v14;
          igi2_frame.tNormal.vZ = v15;
          v16 = v15;
          v17 = v14;
          vX = igi2_frame.tNormal.vX;
          v19 = (unsigned __int8 *)&ptNode[v5];
          v20 = v19[10];
          igi2_frame.aunVertIndex[0] = v19[8] + ((v19[7] + (v19[6] << 8)) << 8);
          v21 = v19[11] + ((v20 + (v19[9] << 8)) << 8);
          v22 = v19[13];
          igi2_frame.aunVertIndex[1] = v21;
          v23 = v19[12];
          v24 = v19[14];
          igi2_frame.tPointInPlane.vY = v13;
          --v3;
          igi2_frame.aunVertIndex[2] = v24 + ((v22 + (v23 << 8)) << 8);
          for ( i = 0; i < 3; ++i )
          {
            v26 = (ptRelativeVertex[igi2_frame.aunVertIndex[i]].vX - igi2_frame.tPointInPlane.vX) * vX
                + (ptRelativeVertex[igi2_frame.aunVertIndex[i]].vY - igi2_frame.tPointInPlane.vY) * v17
                + (ptRelativeVertex[igi2_frame.aunVertIndex[i]].vZ - igi2_frame.tPointInPlane.vZ) * v16;
            igi2_frame.avPlaneSideValue[i] = v26;
            if ( v26 < 0.0 )
              v26 = -v26;
            if ( v26 < 40.959999084472656 )
              igi2_frame.avPlaneSideValue[i] = 0.0;
            igi2_frame.aePlaneSide[i] = igi2_frame.avPlaneSideValue[i] < 0.0;
          }
          v27 = 0;
          v28 = igi2_frame.avPlaneSideValue[0];
          if ( igi2_frame.avPlaneSideValue[0] < 0.0 )
            v28 = -v28;
          v29 = igi2_frame.avPlaneSideValue[1];
          if ( igi2_frame.avPlaneSideValue[1] < 0.0 )
            v29 = -v29;
          if ( v29 > v28 )
          {
            v28 = igi2_frame.avPlaneSideValue[1];
            if ( igi2_frame.avPlaneSideValue[1] < 0.0 )
              v28 = -v28;
            v27 = 1;
          }
          v30 = igi2_frame.avPlaneSideValue[2];
          if ( igi2_frame.avPlaneSideValue[2] < 0.0 )
            v30 = -v30;
          if ( v30 > v28 )
            v27 = 2;
          v31 = igi2_frame.avPlaneSideValue[0];
          if ( igi2_frame.avPlaneSideValue[0] < 0.0 )
            v31 = -v31;
          if ( v31 < 40.959999084472656 )
            igi2_frame.aePlaneSide[0] = igi2_frame.aePlaneSide[v27];
          v32 = igi2_frame.avPlaneSideValue[1];
          if ( igi2_frame.avPlaneSideValue[1] < 0.0 )
            v32 = -v32;
          if ( v32 < 40.959999084472656 )
            igi2_frame.aePlaneSide[1] = igi2_frame.aePlaneSide[v27];
          v33 = igi2_frame.avPlaneSideValue[2];
          if ( igi2_frame.avPlaneSideValue[2] < 0.0 )
            v33 = -v33;
          unNumNodes = igi2_frame.v35;
          v1 = ptTree;
          if ( v33 < 40.959999084472656 )
            igi2_frame.aePlaneSide[2] = igi2_frame.aePlaneSide[v27];
        }
      }
      else
      {
        igi2_frame.aunSidesChecked[v3] = 1;
        if ( unNumNodes )
        {
          v6 = v1->ptNode[v5].atChildIndex[0].atData[2]
             + (((v1->ptNode[v5].atChildIndex[0].atData[0] << 8) + v1->ptNode[v5].atChildIndex[0].atData[1]) << 8);
          if ( v6 )
          {
            ++v3;
            v5 = v1->ptNode[v5].atChildIndex[0].atData[2]
               + (((v1->ptNode[v5].atChildIndex[0].atData[0] << 8) + v1->ptNode[v5].atChildIndex[0].atData[1]) << 8);
            igi2_frame.aunNodeStack[v3] = v6;
            igi2_frame.aunSidesChecked[v3] = 0;
          }
        }
      }
    }
    while ( igi2_frame.aunSidesChecked[0] != 2 || v5 != 1 );
  }
}

// source: e/3/bsptree.c:1937  [anchor-callee]
void __cdecl BspTreeDynCubeObj_GenerateScoreList2(
        unsigned int unNumVertices,
        struct real64x3_t *ptVertexList,
        unsigned int unNumTriangleVertexIndexes,
        unsigned int *punTriangleVertexIndexes,
        unsigned __int8 *punTriangleMaterial,
        struct real32x3_t *ptTriangleNormals,
        float *pvScoreList)
{
  #pragma pack(push, 1)
  union
  {
    struct { unsigned int *punIndexList; };
    struct { char igi2_o1[4]; unsigned int unEndOfQueue; };
    struct { char igi2_o2[8]; unsigned int unSortedTriangles; };
    struct { char igi2_o3[12]; unsigned int *punSortedIndex; };
    struct { char igi2_o4[16]; unsigned int unBestIndex; };
    char igi2_extent[20];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  unsigned int v7; // edi
  int v8; // esi
  _DWORD *v9; // ebx
  _DWORD *v10; // ebp
  unsigned int *v11; // eax
  unsigned int v12; // esi
  unsigned int v13; // ecx
  unsigned int v14; // ecx
  unsigned int v15; // edx
  unsigned int v16; // eax
  unsigned int v17; // edx
  unsigned int i; // ecx
  double v19; // st7
  unsigned int v20; // edx
  int v21; // esi
  int v22; // esi
  int v23; // esi
  int v24; // esi

  v7 = unNumTriangleVertexIndexes / 3;
  v8 = 4 * (unNumTriangleVertexIndexes / 3);
  igi2_frame.punIndexList = (unsigned int *)Mem_AllocFn(v8, 4);
  v9 = Mem_AllocFn(v8, 4);
  v10 = Mem_AllocFn(v8, 4);
  v11 = (unsigned int *)Mem_AllocFn(v8, 4);
  v12 = 0;
  v13 = 0;
  for ( igi2_frame.punSortedIndex = v11; v13 < v7; ++v13 )
    igi2_frame.punIndexList[v13] = v13;
  *v9 = 0;
  *v10 = v7 - 1;
  igi2_frame.unEndOfQueue = 0;
  igi2_frame.unSortedTriangles = 0;
  if ( v7 )
  {
    do
    {
      BSPScore_SelectBestTriangleFromInterval(
        &igi2_frame.unBestIndex,
        igi2_frame.punIndexList,
        v9[v12],
        v10[v12],
        ptVertexList,
        punTriangleVertexIndexes,
        ptTriangleNormals);
      BSPScore_ReorderTriangleIndexes(
        &unNumTriangleVertexIndexes,
        igi2_frame.punIndexList,
        igi2_frame.unBestIndex,
        v9[v12],
        v10[v12],
        ptVertexList,
        punTriangleVertexIndexes,
        ptTriangleNormals);
      igi2_frame.punSortedIndex[igi2_frame.unSortedTriangles] = igi2_frame.punIndexList[unNumTriangleVertexIndexes];
      v14 = v9[v12];
      ++igi2_frame.unSortedTriangles;
      if ( v14 >= unNumTriangleVertexIndexes )
      {
        v15 = igi2_frame.unEndOfQueue;
      }
      else
      {
        v15 = (igi2_frame.unEndOfQueue + 1) % v7;
        v16 = unNumTriangleVertexIndexes - 1;
        v9[v15] = v14;
        igi2_frame.unEndOfQueue = v15;
        v10[v15] = v16;
      }
      if ( v10[v12] > unNumTriangleVertexIndexes )
      {
        v17 = (v15 + 1) % v7;
        v9[v17] = unNumTriangleVertexIndexes + 1;
        igi2_frame.unEndOfQueue = v17;
        v10[v17] = v10[v12];
      }
      v12 = (v12 + 1) % v7;
    }
    while ( igi2_frame.unSortedTriangles < v7 );
    v11 = igi2_frame.punSortedIndex;
  }
  for ( i = 0; i < v7; pvScoreList[v20] = v19 )
  {
    unNumTriangleVertexIndexes = v7 - i;
    v19 = (double)(v7 - i);
    v20 = v11[i++];
  }
  if ( v11 )
  {
    v21 = *(_DWORD *)((unsigned int)(v11 - 1) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v21);
    memset(*(void **)(v21 + 8), 0xCDu, *(_DWORD *)(v21 + 16));
    free((void *)v21);
  }
  if ( igi2_frame.punIndexList )
  {
    v22 = *(_DWORD *)((unsigned int)(igi2_frame.punIndexList - 1) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v22);
    memset(*(void **)(v22 + 8), 0xCDu, *(_DWORD *)(v22 + 16));
    free((void *)v22);
  }
  v23 = *(_DWORD *)((unsigned int)(v9 - 1) & 0xFFFFFFFC);
  --Mem_nCurrentAllocations;
  Node_Remove((_DWORD **)v23);
  memset(*(void **)(v23 + 8), 0xCDu, *(_DWORD *)(v23 + 16));
  free((void *)v23);
  v24 = *(_DWORD *)((unsigned int)(v10 - 1) & 0xFFFFFFFC);
  --Mem_nCurrentAllocations;
  Node_Remove((_DWORD **)v24);
  memset(*(void **)(v24 + 8), 0xCDu, *(_DWORD *)(v24 + 16));
  free((void *)v24);
}

// source: e/3/bsptree.c:2057  [anchor-callee]
void __cdecl BSPScore_SelectBestTriangleFromInterval(
        unsigned int *punBestIndex,
        unsigned int *punIndexList,
        unsigned int unLeft,
        unsigned int unRight,
        struct real64x3_t *ptVertexList,
        unsigned int *punTriangleVertexIndexes,
        struct real32x3_t *ptTriangleNormals)
{
  #pragma pack(push, 1)
  union
  {
    struct { int *pnScore; };
    struct { char igi2_o1[4]; int *v31; };
    struct { char igi2_o2[8]; unsigned int unI; };
    struct { char igi2_o3[12]; int *v33; };
    struct { char igi2_o4[16]; float tNormal; };
    struct { char igi2_o5[20]; float tNormal_4; };
    struct { char igi2_o6[24]; float tNormal_8; };
    struct { char igi2_o7[40]; struct real64x3_t tPointInPlane; };
    char igi2_extent[68];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  unsigned int v7; // esi
  unsigned int v8; // edi
  int *v10; // eax
  unsigned int v11; // edx
  unsigned int v12; // eax
  double vZ; // st7
  double vY; // st6
  double vX; // st5
  unsigned int v16; // edi
  struct real64x3_t *v17; // eax
  BOOL v18; // edx
  struct real64x3_t *v19; // eax
  BOOL v20; // esi
  struct real64x3_t *v21; // eax
  int v22; // eax
  int v23; // eax
  unsigned int v24; // edx
  int v25; // ebx
  int *v26; // esi
  int v27; // eax
  int v28; // ecx
  int v29; // esi

  v7 = unLeft;
  v8 = unRight;
  v10 = (int *)Mem_AllocFn(4 * (unRight - unLeft) + 4, 4);
  v11 = unLeft;
  igi2_frame.pnScore = v10;
  igi2_frame.unI = unLeft;
  if ( unLeft <= unRight )
  {
    igi2_frame.v33 = v10;
    do
    {
      v12 = 3 * punIndexList[v11];
      igi2_frame.tNormal = ptTriangleNormals[v12 / 3].vX;
      igi2_frame.tNormal_8 = ptTriangleNormals[v12 / 3].vZ;
      igi2_frame.tNormal_4 = ptTriangleNormals[v12 / 3].vY;
      qmemcpy(&igi2_frame.tPointInPlane, &ptVertexList[punTriangleVertexIndexes[v12]], sizeof(igi2_frame.tPointInPlane));
      vZ = igi2_frame.tPointInPlane.vZ;
      vY = igi2_frame.tPointInPlane.vY;
      vX = igi2_frame.tPointInPlane.vX;
      v16 = unLeft;
      *igi2_frame.v33 = 0;
      igi2_frame.v31 = igi2_frame.pnScore;
      do
      {
        if ( v11 != v16 )
        {
          v17 = &ptVertexList[punTriangleVertexIndexes[3 * punIndexList[v16]]];
          v18 = igi2_frame.tNormal_8 * (vZ - v17->vZ) + igi2_frame.tNormal_4 * (vY - v17->vY) + igi2_frame.tNormal * (vX - v17->vX) >= 0.0;
          v19 = &ptVertexList[punTriangleVertexIndexes[3 * punIndexList[v16] + 1]];
          v20 = igi2_frame.tNormal_8 * (vZ - v19->vZ) + igi2_frame.tNormal_4 * (vY - v19->vY) + igi2_frame.tNormal * (vX - v19->vX) >= 0.0;
          v21 = &ptVertexList[punTriangleVertexIndexes[3 * punIndexList[v16] + 2]];
          v22 = v18 + v20 + (igi2_frame.tNormal_8 * (vZ - v21->vZ) + igi2_frame.tNormal_4 * (vY - v21->vY) + igi2_frame.tNormal * (vX - v21->vX) >= 0.0);
          if ( v22 )
          {
            if ( v22 != 3 )
              ++*igi2_frame.v31;
          }
        }
        v11 = igi2_frame.unI;
        ++v16;
        ++igi2_frame.v31;
      }
      while ( v16 <= unRight );
      v11 = igi2_frame.unI + 1;
      igi2_frame.unI = v11;
      ++igi2_frame.v33;
    }
    while ( v11 <= unRight );
    v7 = unLeft;
    v8 = unRight;
    v10 = igi2_frame.pnScore;
  }
  *punBestIndex = v7;
  v23 = *v10;
  if ( v23 < 0 )
    v23 = -v23;
  v24 = v7 + 1;
  v25 = v23;
  if ( v7 + 1 <= v8 )
  {
    v26 = igi2_frame.pnScore + 1;
    do
    {
      v27 = *v26;
      v28 = *v26;
      if ( *v26 < 0 )
        v28 = -v28;
      if ( v28 > v25 )
      {
        if ( v27 < 0 )
          v27 = -v27;
        v25 = v27;
        *punBestIndex = v24;
      }
      ++v24;
      ++v26;
    }
    while ( v24 <= v8 );
  }
  v29 = *(_DWORD *)((unsigned int)(igi2_frame.pnScore - 1) & 0xFFFFFFFC);
  --Mem_nCurrentAllocations;
  Node_Remove((_DWORD **)v29);
  memset(*(void **)(v29 + 8), 0xCDu, *(_DWORD *)(v29 + 16));
  free((void *)v29);
}

// source: e/3/bsptree.c:2164  [anchor-callee]
void __cdecl BSPScore_ReorderTriangleIndexes(
        unsigned int *punIndexAfterReorder,
        unsigned int *punIndexList,
        unsigned int unBestIndex,
        unsigned int unLeft,
        unsigned int unRight,
        struct real64x3_t *ptVertexList,
        unsigned int *punTriangleVertexIndexes,
        struct real32x3_t *ptTriangleNormals)
{
  #pragma pack(push, 1)
  union
  {
    struct { unsigned int unLeftInsert; };
    struct { char igi2_o1[4]; unsigned int unRightInsert; };
    struct { char igi2_o2[12]; float tPlaneNormal; };
    struct { char igi2_o3[16]; float tPlaneNormal_4; };
    struct { char igi2_o4[20]; float tPlaneNormal_8; };
    struct { char igi2_o5[24]; struct real64x3_t tPointInPlane; };
    char igi2_extent[48];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct real64x3_t *v10; // eax
  unsigned int *v11; // edx
  unsigned int v12; // eax
  struct real64x3_t *v13; // esi
  unsigned int v14; // eax
  unsigned int v15; // esi
  double vZ; // st7
  double vY; // st6
  double vX; // st5
  unsigned int v19; // edx
  struct real64x3_t *v20; // eax
  BOOL v21; // edi
  struct real64x3_t *v22; // eax
  BOOL v23; // esi
  struct real64x3_t *v24; // eax
  int v25; // eax
  struct real64x3_t *v26; // ecx
  int v27; // esi
  struct real64x3_t *ptVertexLista = *(struct real64x3_t * *)&ptVertexList; // [esp+58h] [ebp+18h] ARGSLOT
  unsigned int *punTriangleVertexIndexesa = *(unsigned int * *)&ptTriangleNormals; // [esp+5Ch] [ebp+1Ch] ARGSLOT

  v10 = (struct real64x3_t *)Mem_AllocFn(4 * (unRight - unLeft) + 4, 4);
  v11 = punIndexList;
  ptVertexLista = v10;
  v12 = 3 * punIndexList[unBestIndex];
  igi2_frame.unRightInsert = unRight - unLeft;
  igi2_frame.tPlaneNormal = ptTriangleNormals[v12 / 3].vX;
  igi2_frame.tPlaneNormal_4 = ptTriangleNormals[v12 / 3].vY;
  igi2_frame.tPlaneNormal_8 = ptTriangleNormals[v12 / 3].vZ;
  v13 = &ptVertexList[punTriangleVertexIndexes[v12]];
  v14 = unLeft;
  qmemcpy(&igi2_frame.tPointInPlane, v13, sizeof(igi2_frame.tPointInPlane));
  v15 = unRight;
  igi2_frame.unLeftInsert = 0;
  punTriangleVertexIndexesa = (unsigned int *)unLeft;
  if ( unLeft <= unRight )
  {
    vZ = igi2_frame.tPointInPlane.vZ;
    vY = igi2_frame.tPointInPlane.vY;
    vX = igi2_frame.tPointInPlane.vX;
    do
    {
      if ( v14 != unBestIndex )
      {
        v19 = v11[v14];
        v20 = &ptVertexList[punTriangleVertexIndexes[3 * v19]];
        v21 = igi2_frame.tPlaneNormal_8 * (vZ - v20->vZ) + igi2_frame.tPlaneNormal_4 * (vY - v20->vY) + igi2_frame.tPlaneNormal * (vX - v20->vX) >= 0.0;
        v22 = &ptVertexList[punTriangleVertexIndexes[3 * v19 + 1]];
        v23 = igi2_frame.tPlaneNormal_8 * (vZ - v22->vZ) + igi2_frame.tPlaneNormal_4 * (vY - v22->vY) + igi2_frame.tPlaneNormal * (vX - v22->vX) >= 0.0;
        v24 = &ptVertexList[punTriangleVertexIndexes[3 * v19 + 2]];
        LODWORD(igi2_frame.tPointInPlane.vY) = igi2_frame.tPlaneNormal_8 * (vZ - v24->vZ)
                                  + igi2_frame.tPlaneNormal_4 * (vY - v24->vY)
                                  + igi2_frame.tPlaneNormal * (vX - v24->vX) >= 0.0;
        v25 = v21 + v23 + LODWORD(igi2_frame.tPointInPlane.vY);
        if ( v25 == 3 )
        {
          *((_DWORD *)&ptVertexLista->vX + igi2_frame.unLeftInsert++) = v19;
        }
        else if ( v25 && igi2_frame.unLeftInsert < unRight - unLeft - igi2_frame.unRightInsert )
        {
          *((_DWORD *)&ptVertexLista->vX + igi2_frame.unLeftInsert++) = v19;
        }
        else
        {
          *((_DWORD *)&ptVertexLista->vX + igi2_frame.unRightInsert--) = v19;
        }
      }
      v15 = unRight;
      v11 = punIndexList;
      v14 = (unsigned int)punTriangleVertexIndexesa + 1;
      punTriangleVertexIndexesa = (unsigned int *)((char *)punTriangleVertexIndexesa + 1);
    }
    while ( (unsigned int)punTriangleVertexIndexesa <= unRight );
    v14 = unLeft;
  }
  *((_DWORD *)&ptVertexLista->vX + igi2_frame.unLeftInsert) = v11[unBestIndex];
  *punIndexAfterReorder = v14 + igi2_frame.unLeftInsert;
  if ( v14 <= v15 )
  {
    v26 = ptVertexLista;
    do
    {
      v11[v14++] = LODWORD(v26->vX);
      v26 = (struct real64x3_t *)((char *)v26 + 4);
    }
    while ( v14 <= v15 );
  }
  if ( ptVertexLista )
  {
    v27 = *(_DWORD *)(((unsigned int)&ptVertexLista[-1].vZ + 4) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v27);
    memset(*(void **)(v27 + 8), 0xCDu, *(_DWORD *)(v27 + 16));
    free((void *)v27);
  }
}

// source: e/3/bsptree.c:2276  [anchor-mhash]
void __cdecl BspTreeDynCubeObj_GenerateScoreList(
        unsigned int unNumVertices,
        struct real64x3_t *ptVertexList,
        unsigned int unNumTriangleVertexIndexes,
        unsigned int *punTriangleVertexIndexes,
        unsigned __int8 *punTriangleMaterial,
        struct real32x3_t *ptTriangleNormals,
        float *pvScoreList)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vLongestDistance; };
    struct { char igi2_o1[8]; double v33; };
    struct { char igi2_o2[20]; int aunVertexIndex[3]; };
    struct { char igi2_o3[32]; struct real64x3_t tCenter; };
    char igi2_extent[56];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v7; // st7
  unsigned int v9; // ecx
  unsigned int v10; // edi
  double *p_vZ; // eax
  double v12; // st7
  double v13; // st6
  double v14; // st7
  double v15; // st6
  double *v16; // eax
  unsigned int v17; // edi
  double *v18; // ecx
  unsigned int v19; // esi
  long double v20; // st7
  unsigned int v21; // edi
  unsigned int *v22; // edx
  int v23; // eax
  float *v24; // esi
  long double v25; // st6
  int v26; // ecx
  int v27; // eax
  int i; // ecx
  struct real64x3_t *v29; // eax
  long double v30; // st6
  double v31; // st5

  v7 = 0.0;
  v9 = 0;
  memset(&igi2_frame.tCenter.vY, 0, 16);
  if ( (int)unNumVertices >= 4 )
  {
    v10 = 3;
    p_vZ = &ptVertexList->vZ;
    do
    {
      v12 = v7 + *(p_vZ - 2);
      v10 += 4;
      v9 += 4;
      v13 = igi2_frame.tCenter.vY + *(p_vZ - 1);
      p_vZ += 12;
      igi2_frame.tCenter.vZ = igi2_frame.tCenter.vZ + *(p_vZ - 12);
      igi2_frame.tCenter.vX = v12 + *(p_vZ - 11);
      v14 = v13 + *(p_vZ - 10);
      v15 = igi2_frame.tCenter.vZ + *(p_vZ - 9);
      igi2_frame.tCenter.vX = igi2_frame.tCenter.vX + *(p_vZ - 8);
      igi2_frame.tCenter.vY = v14 + *(p_vZ - 7);
      igi2_frame.tCenter.vZ = v15 + *(p_vZ - 6);
      v7 = igi2_frame.tCenter.vX + *(p_vZ - 5);
      igi2_frame.tCenter.vY = igi2_frame.tCenter.vY + *(p_vZ - 4);
      igi2_frame.tCenter.vZ = igi2_frame.tCenter.vZ + *(p_vZ - 3);
    }
    while ( v10 < unNumVertices );
  }
  if ( v9 < unNumVertices )
  {
    v16 = &ptVertexList[v9].vZ;
    v17 = unNumVertices - v9;
    do
    {
      v7 = v7 + *(v16 - 2);
      v16 += 3;
      --v17;
      igi2_frame.tCenter.vY = igi2_frame.tCenter.vY + *(v16 - 4);
      igi2_frame.tCenter.vZ = igi2_frame.tCenter.vZ + *(v16 - 3);
    }
    while ( v17 );
  }
  igi2_frame.v33 = 1.0 / (double)unNumVertices;
  igi2_frame.tCenter.vX = igi2_frame.v33 * v7;
  igi2_frame.tCenter.vY = igi2_frame.v33 * igi2_frame.tCenter.vY;
  igi2_frame.tCenter.vZ = igi2_frame.v33 * igi2_frame.tCenter.vZ;
  igi2_frame.vLongestDistance = sqrt(
                       (ptVertexList->vX - igi2_frame.tCenter.vX) * (ptVertexList->vX - igi2_frame.tCenter.vX)
                     + (ptVertexList->vY - igi2_frame.tCenter.vY) * (ptVertexList->vY - igi2_frame.tCenter.vY)
                     + (ptVertexList->vZ - igi2_frame.tCenter.vZ) * (ptVertexList->vZ - igi2_frame.tCenter.vZ));
  if ( unNumVertices > 1 )
  {
    v18 = &ptVertexList[1].vZ;
    v19 = unNumVertices - 1;
    do
    {
      v20 = sqrt(
              (*(v18 - 2) - igi2_frame.tCenter.vX) * (*(v18 - 2) - igi2_frame.tCenter.vX)
            + (*(v18 - 1) - igi2_frame.tCenter.vY) * (*(v18 - 1) - igi2_frame.tCenter.vY)
            + (*v18 - igi2_frame.tCenter.vZ) * (*v18 - igi2_frame.tCenter.vZ));
      if ( v20 > igi2_frame.vLongestDistance )
        igi2_frame.vLongestDistance = v20;
      v18 += 3;
      --v19;
    }
    while ( v19 );
  }
  v21 = 0;
  if ( unNumTriangleVertexIndexes / 3 )
  {
    v22 = punTriangleVertexIndexes;
    v23 = (char *)punTriangleVertexIndexes - (char *)ptTriangleNormals;
    v24 = &ptTriangleNormals->vZ;
    while ( 1 )
    {
      v25 = 0.0;
      igi2_frame.aunVertexIndex[0] = *v22;
      v26 = *(_DWORD *)((char *)v24 + v23 - 4);
      v27 = *(_DWORD *)((char *)v24 + v23);
      igi2_frame.aunVertexIndex[1] = v26;
      igi2_frame.aunVertexIndex[2] = v27;
      for ( i = 0; i < 3; ++i )
      {
        v29 = &ptVertexList[igi2_frame.aunVertexIndex[i]];
        v25 = v25
            + sqrt(
                (v29->vY - igi2_frame.tCenter.vY) * (v29->vY - igi2_frame.tCenter.vY)
              + (v29->vZ - igi2_frame.tCenter.vZ) * (v29->vZ - igi2_frame.tCenter.vZ)
              + (v29->vX - igi2_frame.tCenter.vX) * (v29->vX - igi2_frame.tCenter.vX));
      }
      v30 = 1.0 - v25 * 0.3333333432674408 * (1.0 / igi2_frame.vLongestDistance);
      v31 = *v24;
      if ( v31 < 0.0 )
        v31 = -v31;
      ++v21;
      v22 += 3;
      v24 += 3;
      pvScoreList[v21 - 1] = 1.0 - v31 + 1.0 - v31 - 1.0 + v30;
      if ( v21 >= unNumTriangleVertexIndexes / 3 )
        break;
      v23 = (char *)punTriangleVertexIndexes - (char *)ptTriangleNormals;
    }
  }
}

// source: e/3/bsptree.c:2375  [anchor-caller]
float *__cdecl BspTreeDynCubeObj_OrderTrianglesByScoreList(
        unsigned int unNumTriangleVertexIndexes,
        unsigned int *punTriangleVertexIndexes,
        unsigned __int8 *punTriangleMaterial,
        struct real32x3_t *ptTriangleNormals,
        float *pvScoreList)
{
  float *result; // eax

  BspTreeDynCubeObj_QuickSortTrianglesByScoreList(
    0,
    unNumTriangleVertexIndexes / 3 - 1,
    punTriangleVertexIndexes,
    punTriangleMaterial,
    ptTriangleNormals,
    pvScoreList);
  return result;
}

// source: e/3/bsptree.c:2441  [anchor-callee]
void __cdecl BspTreeDynCubeObj_QuickSortTrianglesByScoreList(
        unsigned int unFirstIndex,
        unsigned int unLastIndex,
        unsigned int *punTriangleVertexIndexes,
        unsigned __int8 *punTriangleMaterial,
        struct real32x3_t *ptTriangleNormals,
        float *pvScoreList)
{
  float *v6; // ebx
  unsigned int v7; // ebp
  unsigned int i; // edi
  unsigned int v9; // eax
  double v10; // st7
  unsigned int *v11; // ebx
  unsigned int v12; // edx
  unsigned int v13; // ebp
  struct real32x3_t *v14; // eax
  unsigned int v15; // ecx
  unsigned int v16; // eax
  float *v17; // eax
  bool v18; // c0
  bool v19; // c3
  struct real32x3_t *v20; // ecx
  struct real32x3_t *v21; // ebx
  int v22; // ecx
  struct real32x3_t *v23; // ecx
  unsigned __int8 unPivotMaterial; // [esp+13h] [ebp-31h]
  int v25; // [esp+14h] [ebp-30h]
  unsigned __int8 *v26; // [esp+14h] [ebp-30h]
  unsigned int v27; // [esp+18h] [ebp-2Ch]
  unsigned int *v28; // [esp+1Ch] [ebp-28h]
  struct real32x3_t *v29; // [esp+1Ch] [ebp-28h]
  unsigned int *v30; // [esp+1Ch] [ebp-28h]
  unsigned int *v31; // [esp+20h] [ebp-24h]
  struct real32x3_t *v32; // [esp+24h] [ebp-20h]
  float *v33; // [esp+28h] [ebp-1Ch]
  unsigned int aunPivotIndexes; // [esp+2Ch] [ebp-18h]
  unsigned int aunPivotIndexes_4; // [esp+30h] [ebp-14h]
  unsigned int aunPivotIndexes_8; // [esp+34h] [ebp-10h]
  float tPivotNormal; // [esp+38h] [ebp-Ch]
  float tPivotNormal_4; // [esp+3Ch] [ebp-8h]
  float tPivotNormal_8; // [esp+40h] [ebp-4h]

  v6 = pvScoreList;
  v7 = unLastIndex;
  for ( i = unFirstIndex; ; unFirstIndex = i )
  {
    v9 = (i + v7) >> 1;
    v10 = v6[v9];
    v27 = i;
    v6[v9] = v6[i];
    v6[i] = v10;
    aunPivotIndexes = punTriangleVertexIndexes[3 * v9];
    v25 = 3 * v9;
    punTriangleVertexIndexes[v25] = punTriangleVertexIndexes[3 * i];
    punTriangleVertexIndexes[3 * i] = aunPivotIndexes;
    v11 = &punTriangleVertexIndexes[3 * v9 + 1];
    v28 = &punTriangleVertexIndexes[3 * i + 1];
    v12 = v7;
    v13 = *v11;
    *v11 = *v28;
    *v28 = v13;
    aunPivotIndexes_8 = punTriangleVertexIndexes[3 * v9 + 2];
    aunPivotIndexes_4 = v13;
    punTriangleVertexIndexes[v25 + 2] = punTriangleVertexIndexes[3 * i + 2];
    punTriangleVertexIndexes[3 * i + 2] = aunPivotIndexes_8;
    unPivotMaterial = punTriangleMaterial[v9];
    v26 = &punTriangleMaterial[i];
    punTriangleMaterial[v9] = punTriangleMaterial[i];
    punTriangleMaterial[i] = unPivotMaterial;
    v14 = &ptTriangleNormals[v9];
    tPivotNormal = v14->vX;
    tPivotNormal_8 = v14->vZ;
    v15 = 12 * i;
    v29 = &ptTriangleNormals[i];
    tPivotNormal_4 = v14->vY;
    v14->vX = v29->vX;
    v14->vY = v29->vY;
    v7 = unLastIndex;
    v14->vZ = v29->vZ;
    v29->vX = tPivotNormal;
    v29->vY = tPivotNormal_4;
    v29->vZ = tPivotNormal_8;
    v16 = unFirstIndex;
    v6 = pvScoreList;
    if ( unFirstIndex < unLastIndex )
    {
      v17 = &pvScoreList[unLastIndex];
      do
      {
        if ( v10 > *v17 )
        {
          do
          {
            v18 = v10 < v6[v12 - 1];
            v19 = v10 == v6[--v12];
          }
          while ( !v18 && !v19 );
        }
        punTriangleVertexIndexes[v15 / 4] = punTriangleVertexIndexes[3 * v12];
        v30 = &punTriangleVertexIndexes[3 * v12 + 1];
        punTriangleVertexIndexes[v15 / 4 + 1] = *v30;
        v31 = &punTriangleVertexIndexes[3 * v12 + 2];
        punTriangleVertexIndexes[v15 / 4 + 2] = *v31;
        *v26 = punTriangleMaterial[v12];
        v20 = &ptTriangleNormals[v15 / 0xC];
        v32 = &ptTriangleNormals[v12];
        v20->vX = v32->vX;
        v20->vY = v32->vY;
        v20->vZ = v32->vZ;
        v33 = &pvScoreList[v12];
        for ( pvScoreList[v27] = *v33; i < v12; ++i )
        {
          if ( v10 > pvScoreList[i] )
            break;
        }
        v15 = 12 * i;
        punTriangleVertexIndexes[3 * v12] = punTriangleVertexIndexes[3 * i];
        *v30 = punTriangleVertexIndexes[3 * i + 1];
        *v31 = punTriangleVertexIndexes[3 * i + 2];
        punTriangleMaterial[v12] = punTriangleMaterial[i];
        v21 = &ptTriangleNormals[i];
        v26 = &punTriangleMaterial[i];
        v32->vX = v21->vX;
        v32->vY = v21->vY;
        v32->vZ = v21->vZ;
        v6 = pvScoreList;
        v27 = i;
        v17 = &pvScoreList[v12];
        *v33 = pvScoreList[i];
      }
      while ( i < v12 );
      v16 = unFirstIndex;
      v7 = unLastIndex;
    }
    v6[i] = v10;
    v22 = 3 * i;
    punTriangleVertexIndexes[v22] = aunPivotIndexes;
    punTriangleVertexIndexes[v22 + 1] = aunPivotIndexes_4;
    punTriangleVertexIndexes[v22 + 2] = aunPivotIndexes_8;
    punTriangleMaterial[i] = unPivotMaterial;
    v23 = &ptTriangleNormals[i];
    v23->vX = tPivotNormal;
    v23->vY = tPivotNormal_4;
    v23->vZ = tPivotNormal_8;
    if ( i > v16 )
      BspTreeDynCubeObj_QuickSortTrianglesByScoreList(
        v16,
        i - 1,
        punTriangleVertexIndexes,
        punTriangleMaterial,
        ptTriangleNormals,
        v6);
    if ( i >= v7 )
      break;
    ++i;
  }
}

// source: e/3/bsptree.c:2562  [size]
__int16 __cdecl BspTreeDynCubeObj_GetGenerationSizeEvent()
{
  return BspTreeDynCubeObj_eGenerationSizeEvent;
}

// source: e/3/bsptree.c:2577  [size]
__int16 __cdecl BspTreeDynCubeObj_GetGenerationListEvent()
{
  return BspTreeDynCubeObj_eGenerationListEvent;
}

// source: e/3/bsptree.c:2595  [anchor-caller]
void __cdecl BspTreeDynCubeObj_GenerateTree(
        struct BspTreeDynCubeObj_s *ptTree,
        struct World_s *ptWorld,
        struct real64x3_t tMin,
        struct real64x3_t tMax)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct BspTree_GenerationSizeContext_s tSizeContext; };
    struct { char igi2_o1[8]; struct BspTree_GenerationListContext_s tListContext; };
    char igi2_extent[40];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  unsigned int v5; // edi
  float *v6; // edi
  struct real32x3_t *ptNormalList; // ecx
  int v8; // ebp
  int v9; // esi
  int v10; // esi
  int v11; // esi
  int v12; // esi

  igi2_frame.tSizeContext.unNumTriangleIndexes = 0;
  igi2_frame.tSizeContext.unNumVertices = 0;
  World_TriggerQTaskEventMinMaxXyzSpecificTree(
    ptWorld,
    BspTreeDynCubeObj_eGenerationSizeEvent,
    &igi2_frame.tSizeContext,
    &tMin,
    &tMax,
    0xFFFFFFFF,
    WORLD_DYNCUBETREE_STATIONARY);
  World_TriggerQTaskEventMinMaxXyzSpecificTree(
    ptWorld,
    BspTreeDynCubeObj_eGenerationSizeEvent,
    &igi2_frame.tSizeContext,
    &tMin,
    &tMax,
    0xFFFFFFFF,
    WORLD_DYNCUBETREE_STATIONARY);
  if ( igi2_frame.tSizeContext.unNumTriangleIndexes >= 3 && igi2_frame.tSizeContext.unNumVertices >= 3 )
  {
    v5 = igi2_frame.tSizeContext.unNumTriangleIndexes / 3;
    igi2_frame.tListContext.ptNormalList = (struct real32x3_t *)Mem_AllocFn(12 * (igi2_frame.tSizeContext.unNumTriangleIndexes / 3), 4);
    igi2_frame.tListContext.ptVertexList = (struct real64x3_t *)Mem_AllocFn(24 * igi2_frame.tSizeContext.unNumVertices, 4);
    igi2_frame.tListContext.punMaterialIndexList = (unsigned __int8 *)Mem_AllocFn(v5, 4);
    igi2_frame.tListContext.punVertexIndexList = (unsigned int *)Mem_AllocFn(4 * igi2_frame.tSizeContext.unNumTriangleIndexes, 4);
    igi2_frame.tListContext.unNumVertexIndexes = 0;
    igi2_frame.tListContext.unNumVertices = 0;
    *(struct BspTree_GenerationSizeContext_s *)&igi2_frame.tListContext.unMaxVertices = igi2_frame.tSizeContext;
    v6 = (float *)Mem_AllocFn(4 * v5, 4);
    World_TriggerQTaskEventMinMaxXyzSpecificTree(
      ptWorld,
      BspTreeDynCubeObj_eGenerationListEvent,
      &igi2_frame.tListContext,
      &tMin,
      &tMax,
      0xFFFFFFFF,
      WORLD_DYNCUBETREE_STATIONARY);
    World_TriggerQTaskEventMinMaxXyzSpecificTree(
      ptWorld,
      BspTreeDynCubeObj_eGenerationListEvent,
      &igi2_frame.tListContext,
      &tMin,
      &tMax,
      0xFFFFFFFF,
      WORLD_DYNCUBETREE_STATIONARY);
    BspTreeDynCubeObj_DeleteHandler(&ptTree->tDynCubeObj.tQObj.tQTask);
    ptNormalList = igi2_frame.tListContext.ptNormalList;
    ptTree->unNumNodes = 0;
    ptTree->unNumVertices = 0;
    ptTree->unNumAllocatedNodes = 0;
    ptTree->unNumAllocatedVertices = 0;
    ptTree->ptNode = nullptr;
    ptTree->ptRelativeVertex = nullptr;
    BspTreeDynCubeObj_ptTree = ptTree;
    BspTreeDynCubeObj_GenerateScoreList2(
      igi2_frame.tListContext.unNumVertices,
      igi2_frame.tListContext.ptVertexList,
      igi2_frame.tListContext.unNumVertexIndexes,
      igi2_frame.tListContext.punVertexIndexList,
      igi2_frame.tListContext.punMaterialIndexList,
      ptNormalList,
      v6);
    BspTreeDynCubeObj_QuickSortTrianglesByScoreList(
      0,
      igi2_frame.tListContext.unNumVertexIndexes / 3 - 1,
      igi2_frame.tListContext.punVertexIndexList,
      igi2_frame.tListContext.punMaterialIndexList,
      igi2_frame.tListContext.ptNormalList,
      v6);
    if ( v6 )
    {
      v8 = *(_DWORD *)((unsigned int)(v6 - 1) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v8);
      memset(*(void **)(v8 + 8), 0xCDu, *(_DWORD *)(v8 + 16));
      free((void *)v8);
    }
    BspTreeDynCubeObj_InsertTriangles(
      ptTree,
      igi2_frame.tListContext.unNumVertices,
      igi2_frame.tListContext.ptVertexList,
      igi2_frame.tListContext.unNumVertexIndexes,
      igi2_frame.tListContext.punVertexIndexList,
      igi2_frame.tListContext.punMaterialIndexList,
      igi2_frame.tListContext.ptNormalList);
    if ( igi2_frame.tListContext.ptNormalList )
    {
      v9 = *(_DWORD *)((int)&igi2_frame.tListContext.ptNormalList[-1].vZ & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v9);
      memset(*(void **)(v9 + 8), 0xCDu, *(_DWORD *)(v9 + 16));
      free((void *)v9);
    }
    igi2_frame.tListContext.ptNormalList = nullptr;
    if ( igi2_frame.tListContext.ptVertexList )
    {
      v10 = *(_DWORD *)(((int)&igi2_frame.tListContext.ptVertexList[-1].vZ + 4) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v10);
      memset(*(void **)(v10 + 8), 0xCDu, *(_DWORD *)(v10 + 16));
      free((void *)v10);
    }
    igi2_frame.tListContext.ptVertexList = nullptr;
    if ( igi2_frame.tListContext.punMaterialIndexList )
    {
      v11 = *(_DWORD *)((int)(igi2_frame.tListContext.punMaterialIndexList - 4) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v11);
      memset(*(void **)(v11 + 8), 0xCDu, *(_DWORD *)(v11 + 16));
      free((void *)v11);
    }
    igi2_frame.tListContext.punMaterialIndexList = nullptr;
    if ( igi2_frame.tListContext.punVertexIndexList )
    {
      v12 = *(_DWORD *)((int)(igi2_frame.tListContext.punVertexIndexList - 1) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v12);
      memset(*(void **)(v12 + 8), 0xCDu, *(_DWORD *)(v12 + 16));
      free((void *)v12);
    }
  }
}

// source: e/3/bsptree.c:2756  [anchor-caller]
void __cdecl BspTreeDynCubeObj_Load(struct BspTreeDynCubeObj_s *ptTree, char *zFileName)
{
  _DWORD *v2; // eax
  void *v3; // esi
  _DWORD *FirstChunk; // ebx
  unsigned int *ChunkData; // eax
  unsigned int v6; // eax
  int v7; // eax
  _DWORD *v8; // ebx
  void *v9; // esi
  struct BspTreeNode_s *v10; // eax
  unsigned int v11; // edx
  int v12; // eax
  char *v13; // ebx
  void *v14; // esi
  struct real32x3_t *v15; // eax
  int v16; // eax
  unsigned int unSize; // [esp+10h] [ebp-4h] BYREF

  v2 = Resource_Load(zFileName, &unSize);
  v3 = v2;
  unSize = (unsigned int)v2;
  if ( v2 && *v2 == 1179012169 && v2[4] == 1129337666 )
  {
    BspTreeDynCubeObj_DeleteHandler(&ptTree->tDynCubeObj.tQObj.tQTask);
    ptTree->unNumNodes = 0;
    ptTree->unNumVertices = 0;
    ptTree->unNumAllocatedNodes = 0;
    ptTree->unNumAllocatedVertices = 0;
    ptTree->ptNode = nullptr;
    ptTree->ptRelativeVertex = nullptr;
    BspTreeDynCubeObj_ptTree = ptTree;
    FirstChunk = ILF_GetFirstChunk(v3);
    ChunkData = (unsigned int *)ILF_GetChunkData(FirstChunk, v3);
    qmemcpy(&ptTree->tOrigin, ChunkData + 2, sizeof(ptTree->tOrigin));
    ptTree->unNumAllocatedNodes = *ChunkData;
    ptTree->unNumNodes = *ChunkData;
    v6 = ChunkData[1];
    ptTree->unNumVertices = v6;
    ptTree->unNumAllocatedVertices = v6;
    if ( FirstChunk && (v7 = FirstChunk[3]) != 0 )
      v8 = (_DWORD *)((char *)FirstChunk + v7);
    else
      v8 = nullptr;
    v9 = ILF_GetChunkData(v8, (void *)unSize);
    v10 = (struct BspTreeNode_s *)Mem_AllocFn(28 * ptTree->unNumNodes, 4);
    v11 = 28 * ptTree->unNumNodes;
    ptTree->ptNode = v10;
    qmemcpy(v10, v9, v11);
    if ( v8 && (v12 = v8[3]) != 0 )
      v13 = (char *)v8 + v12;
    else
      v13 = nullptr;
    v14 = ILF_GetChunkData(v13, (void *)unSize);
    v15 = (struct real32x3_t *)Mem_AllocFn(12 * ptTree->unNumVertices, 4);
    ptTree->ptRelativeVertex = v15;
    qmemcpy(v15, v14, 12 * ptTree->unNumVertices);
  }
  if ( Resource_IsLoadedInternal(zFileName, (struct Resource_s **)&unSize) )
  {
    v16 = *(_DWORD *)(unSize + 36);
    if ( v16 != 3 && v16 != 1 )
      Resource_Remove((struct Resource_s *)unSize);
  }
}

// source: e/3/bsptree.c:2824  [anchor-caller]
void __cdecl BspTreeDynCubeObj_Save(struct BspTreeDynCubeObj_s *ptTree, char *zFileName)
{
  struct ILFContainerNode_s *v2; // ebp
  unsigned int unNumNodes; // eax
  unsigned int unNumVertices; // ecx
  _DWORD *v5; // edx
  _DWORD *v6; // edx
  unsigned int v7; // eax
  _DWORD *v8; // edx
  unsigned int v9; // eax
  struct Bsp_ILF_Header_s tHeader; // [esp+10h] [ebp-20h] BYREF

  v2 = ILF_NewContainterNode(0x46464C49u, 0x43505342u);
  unNumNodes = ptTree->unNumNodes;
  qmemcpy(&tHeader.tOrigin, &ptTree->tOrigin, sizeof(tHeader.tOrigin));
  unNumVertices = ptTree->unNumVertices;
  tHeader.unNumNodes = unNumNodes;
  tHeader.unNumVertices = unNumVertices;
  v5 = Mem_AllocFn(40, 4);
  memset(v5, 0, 0x28u);
  v5[9] = &tHeader;
  v5[2] = 1213223746;
  v5[8] = 0;
  v5[1] = 0;
  *v5 = 0;
  v5[7] = 32;
  v5[5] = 0;
  List_AddTail(v5, (int)&v2->tChunkNodeList);
  v6 = Mem_AllocFn(40, 4);
  memset(v6, 0, 0x28u);
  v6[2] = 1313887042;
  v6[8] = 0;
  v6[1] = 0;
  *v6 = 0;
  v7 = 28 * ptTree->unNumNodes;
  v6[9] = ptTree->ptNode;
  v6[7] = v7;
  v6[5] = 0;
  List_AddTail(v6, (int)&v2->tChunkNodeList);
  v8 = Mem_AllocFn(40, 4);
  memset(v8, 0, 0x28u);
  v8[2] = 1448104770;
  v8[8] = 0;
  v8[1] = 0;
  *v8 = 0;
  v9 = 12 * ptTree->unNumVertices;
  v8[9] = ptTree->ptRelativeVertex;
  v8[7] = v9;
  v8[5] = 0;
  List_AddTail(v8, (int)&v2->tChunkNodeList);
  ILF_Write(v2, zFileName);
  ILF_DeleteContainerNode(v2);
}

// source: e/3/bsptree.c:2873  [size]
struct BspTreeDynCubeObj_s *__cdecl BspTreeDynCubeObj_GetTree()
{
  return BspTreeDynCubeObj_ptTree;
}
