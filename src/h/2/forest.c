/* h/2/forest.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/forest.c:290  [size]
int __cdecl Forest_TreeObjectCompareX(void **ppx1, void **ppx2)
{
  if ( *(float *)*ppx1 == *(float *)*ppx2 )
    return 0;
  if ( *(float *)*ppx1 <= (double)*(float *)*ppx2 )
    return -1;
  return 1;
}

// source: h/2/forest.c:311  [size]
int __cdecl Forest_TreeObjectCompareY(void **ppx1, void **ppx2)
{
  if ( *((float *)*ppx1 + 1) == *((float *)*ppx2 + 1) )
    return 0;
  if ( *((float *)*ppx1 + 1) <= (double)*((float *)*ppx2 + 1) )
    return -1;
  return 1;
}

// source: h/2/forest.c:394  [anchor-callee]
void __cdecl Forest_BuildBSPTree(
        struct Forest_s *ptForest,
        struct ForestNode_s **pptCurrNode,
        struct QVector_s *ptVector,
        float vMaxRadius,
        int nLevel,
        int iStart,
        int nNum)
{
  int v7; // eax
  int v8; // ebx
  int v9; // esi
  int v10; // ecx
  int v11; // ebp
  struct QVector_s *v12; // edx
  void **papxElement; // edx
  struct ForestNode_s *v14; // eax
  int nLevela = *(int *)&nLevel; // [esp+24h] [ebp+14h] ARGSLOT

  v7 = nNum;
  v8 = nLevel;
  v9 = nNum >> 1;
  v10 = nLevel & 1;
  v11 = (nNum >> 1) + iStart;
  for ( nLevela = iStart + nNum - 1; v7 > 0; nLevela = iStart + v7 - 1 )
  {
    if ( v8 > ptForest->nBSPTreeDepth )
      ptForest->nBSPTreeDepth = v8;
    v12 = ptVector;
    if ( ptVector->tPrivate.nElements )
    {
      qsort(&ptVector->tPrivate.papxElement[iStart], v7, 4, g_pfQSortCallback[v10]);
      v12 = ptVector;
    }
    papxElement = v12->tPrivate.papxElement;
    v14 = Forest_ptBSPTreePool++;
    v14->ptTree = (struct Tree_s *)papxElement[v11];
    ++v8;
    *pptCurrNode = v14;
    Forest_BuildBSPTree(ptForest, &v14->aptChildren[1], ptVector, vMaxRadius, v8, v11 + 1, nLevela - v9 - iStart);
    v7 = v9;
    pptCurrNode = (*pptCurrNode)->aptChildren;
    v9 >>= 1;
    v10 = v8 & 1;
    v11 = v9 + iStart;
  }
}

// source: h/2/forest.c:440  [anchor-callee]
void __cdecl Forest_RemoveOutsiders(struct Forest_s *ptForest, struct QVector_s *ptVector)
{
  int i; // esi
  void **papxElement; // ebx
  double v4; // st7
  float *v5; // edx
  void **v6; // ecx
  unsigned int v7; // eax

  if ( ptVector )
  {
    for ( i = 0; i < ptForest->nTrees; ++i )
    {
      papxElement = ptVector->tPrivate.papxElement;
      v4 = ptForest->vSize * 2048.0;
      v5 = (float *)papxElement[i];
      v6 = &papxElement[i];
      if ( v4 < fabs(*v5) || v4 < fabs(v5[1]) )
      {
        v7 = ptVector->tPrivate.nElements - 1;
        ptVector->tPrivate.nElements = v7;
        if ( i < v7 )
        {
          if ( ptVector->tPrivate.isStrictOrder )
            memmove(&papxElement[i], v6 + 1, 4 * (v7 - i));
          else
            *v6 = papxElement[v7];
        }
        --i;
        --ptForest->nTrees;
      }
    }
  }
}

// source: h/2/forest.c:553  [anchor-callee]
void __cdecl Forest_CreateBSPTree(struct Forest_s *ptForest)
{
  signed int nTrees; // edi
  struct QVector_s *v2; // ebp
  unsigned int nElements; // edi
  struct Tree_s *v4; // esi
  bool v5; // cc
  struct ForestNode_s *v6; // edi
  unsigned int v7; // edx
  int v8; // esi
  int v9; // eax
  struct Tree_s *v10; // edx
  int v11; // eax
  struct Tree_s *ptRawData; // eax
  int v13; // esi
  int v14; // ebp
  struct QVector_s *v15; // esi
  unsigned int v16; // edi
  struct Tree_s *v17; // eax
  struct Forest_StackElement_s *aptNodeStack; // eax
  int v19; // esi
  int v20; // [esp-8h] [ebp-1Ch]
  int i; // [esp+8h] [ebp-Ch]
  int ia; // [esp+8h] [ebp-Ch]
  int v23; // [esp+Ch] [ebp-8h]
  void **v24; // [esp+Ch] [ebp-8h]
  int v25; // [esp+Ch] [ebp-8h]
  struct Tree_s *ptNewBuffer; // [esp+10h] [ebp-4h]
  struct Tree_s *ptNewBuffera; // [esp+10h] [ebp-4h]

  nTrees = ptForest->nTrees;
  if ( nTrees )
  {
    v2 = QVector_New(nTrees, (nTrees >> 1) + 1, false);
    i = 0;
    if ( ptForest->nTrees > 0 )
    {
      v23 = 0;
      do
      {
        nElements = v2->tPrivate.nElements;
        v4 = &ptForest->ptRawData[v23];
        if ( v2->tPrivate.nElements == v2->tPrivate.nArraySize )
          QVector_Realloc(v2, 1u);
        if ( nElements < v2->tPrivate.nElements - 1 )
          memmove(
            &v2->tPrivate.papxElement[nElements + 1],
            &v2->tPrivate.papxElement[nElements],
            4 * (v2->tPrivate.nElements - nElements));
        ++v2->tPrivate.nElements;
        v2->tPrivate.papxElement[nElements] = v4;
        v5 = ++i < ptForest->nTrees;
        ++v23;
      }
      while ( v5 );
    }
    v20 = 24 * ptForest->nTrees;
    ptForest->nBSPTreeDepth = -1;
    v6 = (struct ForestNode_s *)Mem_AllocFn(v20, 4);
    v7 = 24 * ptForest->nTrees;
    Forest_ptBSPTreePool = v6;
    memset(v6, 0, v7);
    v8 = ptForest->nTrees;
    Forest_RemoveOutsiders(ptForest, v2);
    v9 = ptForest->nTrees;
    if ( v9 != v8 )
    {
      v10 = (struct Tree_s *)Mem_AllocFn(68 * v9, 4);
      v11 = 0;
      for ( ptNewBuffer = v10; v11 < ptForest->nTrees; ++v10 )
        qmemcpy(v10, v2->tPrivate.papxElement[v11++], sizeof(struct Tree_s));
      ptRawData = ptForest->ptRawData;
      if ( ptRawData )
      {
        v13 = *(_DWORD *)((unsigned int)&ptRawData[-1].bLight & 0xFFFFFFFC);
        --Mem_nCurrentAllocations;
        Node_Remove((_DWORD **)v13);
        memset(*(void **)(v13 + 8), 0xCDu, *(_DWORD *)(v13 + 16));
        free((void *)v13);
      }
      ptForest->ptRawData = ptNewBuffer;
      QVector_Delete(v2);
      v14 = ptForest->nTrees;
      v24 = nullptr;
      if ( v14 )
        v24 = (void **)Mem_AllocFn(4 * v14, 4);
      v15 = (struct QVector_s *)Mem_AllocFn(24, 4);
      v15->tPrivate.nArraySize = v14;
      v15->tPrivate.nReallocSize = (v14 >> 1) + 1;
      v15->tPrivate.nElements = 0;
      v15->tPrivate.isPrivateMem = false;
      v15->tPrivate.papxElement = v24;
      v15->tPrivate.isStrictOrder = false;
      v2 = v15;
      ia = 0;
      if ( ptForest->nTrees > 0 )
      {
        v25 = 0;
        do
        {
          v16 = v15->tPrivate.nElements;
          v17 = &ptForest->ptRawData[v25];
          ptNewBuffera = v17;
          if ( v15->tPrivate.nElements == v15->tPrivate.nArraySize )
          {
            QVector_Realloc(v15, 1u);
            v17 = ptNewBuffera;
          }
          if ( v16 < v15->tPrivate.nElements - 1 )
          {
            memmove(
              &v15->tPrivate.papxElement[v16 + 1],
              &v15->tPrivate.papxElement[v16],
              4 * (v15->tPrivate.nElements - v16));
            v17 = ptNewBuffera;
          }
          ++v15->tPrivate.nElements;
          v15->tPrivate.papxElement[v16] = v17;
          v5 = ++ia < ptForest->nTrees;
          ++v25;
        }
        while ( v5 );
      }
    }
    Forest_BuildBSPTree(ptForest, &ptForest->ptBSPTree, v2, ptForest->vTreeRadius, 0, 0, ptForest->nTrees);
    aptNodeStack = ptForest->aptNodeStack;
    ++ptForest->nBSPTreeDepth;
    if ( aptNodeStack )
    {
      v19 = *(_DWORD *)((unsigned int)&aptNodeStack[-1].nLevel & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v19);
      memset(*(void **)(v19 + 8), 0xCDu, *(_DWORD *)(v19 + 16));
      free((void *)v19);
      ptForest->aptNodeStack = nullptr;
    }
    ptForest->aptNodeStack = (struct Forest_StackElement_s *)Mem_AllocFn(24 * ptForest->nBSPTreeDepth, 4);
    QVector_Delete(v2);
  }
}

// source: h/2/forest.c:623  [size]
struct Tree_s *__cdecl Forest_LightUpTree(
        struct Forest_s *ptForest,
        struct Tree_s *ptTree,
        unsigned int *pnLightData)
{
  double vX; // st7
  struct real32x9_t *p_tOrientation; // eax
  struct real64x3_t tTreePos; // [esp+0h] [ebp-1Ch] BYREF

  vX = ptTree->tPosition.vX;
  p_tOrientation = &ptTree->tOrientation;
  tTreePos.vX = vX + ptForest->tPos.vX;
  tTreePos.vY = p_tOrientation[-1].tZ.vZ + ptForest->tPos.vY;
  tTreePos.vZ = ptForest->vTreeHeight * 0.5 + *(float *)&p_tOrientation[-1].nOps + ptForest->tPos.vZ;
  return (struct Tree_s *)Lightmap_RenderHemicube(pnLightData, &tTreePos, p_tOrientation);
}

// source: h/2/forest.c:653  [size]
void __cdecl Forest_UpdateTree(struct Forest_s *ptForest, struct Tree_s *ptTree)
{
  ;
}

// source: h/2/forest.c:754  [anchor-callee]
void __cdecl Forest_GenerateHeightDataRecursively(struct Forest_s *ptForest, struct ForestNode_s *ptNode)
{
  struct ForestNode_s *v3; // eax
  struct ForestNode_s *v4; // eax
  double vZ; // st7
  double vX; // st6
  double vY; // st7
  float tMinMaxZ_Right; // [esp+Ch] [ebp-8h]
  float tMinMaxZ_Right_4; // [esp+10h] [ebp-4h]
  float ptNodea = *(float *)&ptNode; // [esp+1Ch] [ebp+8h] ARGSLOT
  struct real32x2_t tMinMaxZ_Left; // 0:^10.8

  tMinMaxZ_Left.vX = 3.4028234663852886e+38;
  tMinMaxZ_Left.vY = -3.4028234663852886e+38;
  tMinMaxZ_Right = 3.4028234663852886e+38;
  tMinMaxZ_Right_4 = -3.4028234663852886e+38;
  if ( ptNode )
  {
    v3 = ptNode->aptChildren[1];
    if ( v3 )
    {
      Forest_GenerateHeightDataRecursively(ptForest, v3);
      tMinMaxZ_Left = ptNode->aptChildren[1]->tMinMaxZ;
    }
    if ( ptNode->aptChildren[0] )
    {
      Forest_GenerateHeightDataRecursively(ptForest, ptNode->aptChildren[0]);
      v4 = ptNode->aptChildren[0];
      tMinMaxZ_Right = v4->tMinMaxZ.vX;
      tMinMaxZ_Right_4 = v4->tMinMaxZ.vY;
    }
    vZ = ptNode->ptTree->tPosition.vZ;
    ptNodea = ptNode->ptTree->tScale.vZ * ptForest->vTreeHeight + vZ;
    if ( tMinMaxZ_Left.vX >= (double)tMinMaxZ_Right )
      vX = tMinMaxZ_Right;
    else
      vX = tMinMaxZ_Left.vX;
    if ( vX < vZ )
    {
      if ( tMinMaxZ_Left.vX >= (double)tMinMaxZ_Right )
        vZ = tMinMaxZ_Right;
      else
        vZ = tMinMaxZ_Left.vX;
    }
    ptNode->tMinMaxZ.vX = vZ;
    if ( tMinMaxZ_Left.vY <= (double)tMinMaxZ_Right_4 )
      vY = tMinMaxZ_Right_4;
    else
      vY = tMinMaxZ_Left.vY;
    if ( vY <= ptNodea )
    {
      ptNode->tMinMaxZ.vY = ptNodea;
    }
    else if ( tMinMaxZ_Left.vY <= (double)tMinMaxZ_Right_4 )
    {
      ptNode->tMinMaxZ.vY = tMinMaxZ_Right_4;
    }
    else
    {
      ptNode->tMinMaxZ.vY = tMinMaxZ_Left.vY;
    }
  }
}

// source: h/2/forest.c:804  [size]
void __cdecl Forest_LightForest(struct Forest_s *ptForest, int isStart)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v15; };
    struct { char igi2_o1[36]; unsigned int *pnLightData; };
    struct { char igi2_o2[40]; struct Hemicube_t *ptHemicube; };
    struct { char igi2_o3[44]; struct real64x3_t ptPos; };
    char igi2_extent[68];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  DWORD PerformanceCounter; // eax
  unsigned int *v4; // ebp
  struct Hemicube_t *v5; // ebx
  int v6; // edi
  int v7; // ebx
  struct Tree_s *ptRawData; // eax
  double vX; // st7
  struct real32x9_t *p_tOrientation; // eax
  int v11; // eax
  int v12; // ecx
  int v13; // esi
  DWORD TickCount; // eax

  if ( ptForest->nTrees && ptForest->ptRawData )
  {
    if ( !Flow_nSuspendRefCount )
    {
      if ( Timer_isPerformanceCounter )
        PerformanceCounter = Timer_GetPerformanceCounter();
      else
        PerformanceCounter = GetTickCount();
      Flow_nSuspendTime = PerformanceCounter - Timer_nStartTime;
    }
    igi2_frame.v15 = 4 * ptForest->nTrees;
    ++Flow_nSuspendRefCount;
    v4 = (unsigned int *)Mem_AllocFn(igi2_frame.v15, 4);
    igi2_frame.pnLightData = v4;
    v5 = LightmapInfo_NewHemicube(64);
    igi2_frame.ptHemicube = v5;
    if ( GlobalLightQTask_ptGlobalLight )
      Lightmap_Initialize(
        &Level_ptQLevelQTask->tQTask,
        64,
        GlobalLightQTask_ptGlobalLight->vRadiosityIntensity,
        GlobalLightQTask_ptGlobalLight->vRadiosityGamma,
        GlobalLightQTask_ptGlobalLight->vRadiosityFadeout,
        GlobalLightQTask_ptGlobalLight->vRadiosityDirlightRadius,
        v5->pvMainDeltaFormFactor,
        v5->pvHalfDeltaFormFactor,
        Mesh3D_atAmbientColor,
        true,
        nullptr);
    else
      Lightmap_Initialize(
        &Level_ptQLevelQTask->tQTask,
        64,
        0.0,
        1.0,
        1.0,
        0.18000000715255737,
        v5->pvMainDeltaFormFactor,
        v5->pvHalfDeltaFormFactor,
        Mesh3D_atAmbientColor,
        true,
        nullptr);
    v6 = 0;
    if ( ptForest->nTrees > 0 )
    {
      v7 = 0;
      do
      {
        ptRawData = ptForest->ptRawData;
        vX = ptRawData[v7].tPosition.vX;
        p_tOrientation = &ptRawData[v7].tOrientation;
        igi2_frame.ptPos.vX = vX + ptForest->tPos.vX;
        igi2_frame.ptPos.vY = p_tOrientation[-1].tZ.vZ + ptForest->tPos.vY;
        igi2_frame.ptPos.vZ = ptForest->vTreeHeight * 0.5 + *(float *)&p_tOrientation[-1].nOps + ptForest->tPos.vZ;
        Lightmap_RenderHemicube(v4, &igi2_frame.ptPos, p_tOrientation);
        ++v6;
        ++v7;
        ++v4;
      }
      while ( v6 < ptForest->nTrees );
      v4 = igi2_frame.pnLightData;
      v5 = igi2_frame.ptHemicube;
    }
    Lightmap_Deinitialize(false);
    v11 = 0;
    if ( ptForest->nTrees > 0 )
    {
      v12 = 0;
      do
        ptForest->ptRawData[v12++].bLight = v4[v11++] & 0xFFFFFF;
      while ( v11 < ptForest->nTrees );
    }
    LightmapInfo_DeleteHemicube(v5);
    if ( v4 )
    {
      v13 = *(_DWORD *)((unsigned int)(v4 - 1) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v13);
      memset(*(void **)(v13 + 8), 0xCDu, *(_DWORD *)(v13 + 16));
      free((void *)v13);
    }
    if ( !--Flow_nSuspendRefCount )
    {
      if ( Timer_isPerformanceCounter )
        TickCount = Timer_GetPerformanceCounter();
      else
        TickCount = GetTickCount();
      Flow_ptFlow->nSkipTime += TickCount - Timer_nStartTime - Flow_nSuspendTime;
      Flow_nSuspendTime = 0;
    }
  }
}

// source: h/2/forest.c:870  [anchor-caller]
void __cdecl Forest_UpdateForest(struct Forest_s *ptForest)
{
  if ( ptForest->nTrees )
  {
    if ( ptForest->ptRawData )
      Forest_GenerateHeightDataRecursively(ptForest, ptForest->ptBSPTree);
  }
}

// source: h/2/forest.c:918  [anchor-refs]
void __cdecl Forest_SaveData(struct Forest_s *ptForest)
{
  #pragma pack(push, 1)
  union
  {
    struct { int i; };
    struct { char igi2_o1[4]; int nHeaderSize; };
    struct { char igi2_o2[8]; float vAlpha; };
    struct { char igi2_o3[12]; float vBeta; };
    struct { char igi2_o4[16]; float vGamma; };
    struct { char igi2_o5[20]; char *pzHeader; };
    struct { char igi2_o6[24]; struct Forest_SavedTree1_s *ptBuffer; };
    char igi2_extent[28];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char *v1; // ebp
  struct Tree_s *ptRawData; // eax
  int v4; // ecx
  struct QReference_s *v5; // eax
  struct File_s *v6; // ebx
  struct Forest_SavedTree1_s *v7; // eax
  struct Tree_s *v8; // ecx
  int v9; // ebp
  float *p_vY; // esi
  struct Tree_s *v11; // edx
  float *v12; // eax
  float v13; // ecx
  float v14; // eax
  struct real32x3_t *p_tScale; // ecx
  struct Forest_SavedTree1_s *v16; // esi
  int v17; // esi

  v1 = Forest_azFileHeader[1];
  ptRawData = ptForest->ptRawData;
  igi2_frame.pzHeader = Forest_azFileHeader[1];
  if ( ptRawData && ptForest->nTrees > 0 )
  {
    v4 = 0;
    while ( 1 )
    {
      v5 = Level_atLevelQTaskID[v4];
      if ( v5 )
      {
        if ( v5->pxObject == ptForest )
          break;
      }
      if ( ++v4 >= 4096 )
      {
        v4 = -1;
        break;
      }
    }
    ptForest->nID = v4;
    sprintf(ptForest->zFilename, "MISSION:forest_%d.dat", v4);
    v6 = File_New(ptForest->zFilename, "w+");
    if ( v6 )
    {
      v7 = (struct Forest_SavedTree1_s *)Mem_AllocFn(40 * ptForest->nTrees, 4);
      v8 = ptForest->ptRawData;
      igi2_frame.ptBuffer = v7;
      if ( v8 && ptForest->nTrees > 0 )
      {
        igi2_frame.i = 0;
        v9 = 0;
        p_vY = &v7->tAngles.vY;
        do
        {
          Real32x9_GetAngles(&ptForest->ptRawData[v9].tOrientation, &igi2_frame.vAlpha, &igi2_frame.vBeta, &igi2_frame.vGamma);
          v11 = &ptForest->ptRawData[v9];
          v12 = p_vY - 4;
          *v12 = v11->tPosition.vX;
          v12[1] = v11->tPosition.vY;
          v13 = igi2_frame.vBeta;
          v12[2] = v11->tPosition.vZ;
          v14 = igi2_frame.vAlpha;
          p_vY[1] = igi2_frame.vGamma;
          *(p_vY - 1) = v14;
          *p_vY = v13;
          p_tScale = &ptForest->ptRawData[v9].tScale;
          p_vY[2] = p_tScale->vX;
          p_vY[3] = p_tScale->vY;
          p_vY[4] = p_tScale->vZ;
          p_vY[5] = *(float *)&ptForest->ptRawData[v9++].bLight;
          p_vY += 10;
          ++igi2_frame.i;
        }
        while ( igi2_frame.i < ptForest->nTrees );
        v1 = igi2_frame.pzHeader;
      }
      igi2_frame.nHeaderSize = strlen(v1);
      File_atDevice[v6->eDeviceID].pfWrite(v6->eDeviceID, v6, &igi2_frame.nHeaderSize, 4u);
      File_atDevice[v6->eDeviceID].pfWrite(v6->eDeviceID, v6, v1, igi2_frame.nHeaderSize);
      v16 = igi2_frame.ptBuffer;
      File_atDevice[v6->eDeviceID].pfWrite(v6->eDeviceID, v6, igi2_frame.ptBuffer, 40 * ptForest->nTrees);
      if ( v6 == &File_tDummyAsyncFile )
        File_tDummyAsyncFile.isAsync = false;
      else
        File_atDevice[v6->eDeviceID].pfDelete(v6->eDeviceID, v6);
      if ( v16 )
      {
        v17 = *(_DWORD *)((unsigned int)&v16[-1].bLight & 0xFFFFFFFC);
        --Mem_nCurrentAllocations;
        Node_Remove((_DWORD **)v17);
        memset(*(void **)(v17 + 8), 0xCDu, *(_DWORD *)(v17 + 16));
        free((void *)v17);
      }
    }
  }
}

// source: h/2/forest.c:981  [size]
void __cdecl Forest_SaveQTaskHandler(struct QTask_s *ptQTask, void *pxContext)
{
  Forest_SaveData((struct Forest_s *)ptQTask);
}

// source: h/2/forest.c:997  [anchor-strings]
void __cdecl Forest_LoadData(struct Forest_s *ptForest, char *zFileName)
{
  #pragma pack(push, 1)
  union
  {
    struct { char *pxFileBuffer; };
    struct { char igi2_o1[4]; int nFileSize; };
    char igi2_extent[8];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int nTrees; // eax
  size_t *v4; // eax
  int v5; // ebx
  size_t v6; // edi
  int i; // ebp
  int v8; // ecx
  int v9; // ebp
  int v10; // ebx
  int v11; // edi
  struct Tree_s *v12; // edx
  struct real32x3_t *v13; // edx
  int v14; // ecx
  int v15; // ebp
  int v16; // ebx
  int v17; // edi
  struct Tree_s *v18; // edx
  struct real32x3_t *p_tScale; // edx
  int v20; // esi

  nTrees = ptForest->nTrees;
  igi2_frame.nFileSize = 0;
  if ( nTrees && File_Exists(zFileName) )
  {
    v4 = (size_t *)File_Load(zFileName, (unsigned int *)&igi2_frame.nFileSize);
    v5 = igi2_frame.nFileSize;
    igi2_frame.pxFileBuffer = (char *)v4;
    if ( igi2_frame.nFileSize <= 4 || (v6 = *v4, igi2_frame.nFileSize <= (int)(*v4 + 4)) )
    {
      if ( !v4 )
        return;
      --Mem_nCurrentAllocations;
    }
    else
    {
      for ( i = 1; i >= 0; --i )
      {
        if ( !strncmp(igi2_frame.pxFileBuffer + 4, Forest_azFileHeader[i], v6) )
          break;
      }
      if ( !i )
      {
        v14 = ptForest->nTrees;
        if ( v5 - v6 - 4 != 36 * v14 )
        {
          if ( (int)((v5 - v6 - 4) / 0x24) < v14 )
            v14 = (v5 - v6 - 4) / 0x24;
          ptForest->nTrees = v14;
        }
        v15 = 0;
        if ( ptForest->nTrees > 0 )
        {
          v16 = 0;
          v17 = (int)&igi2_frame.pxFileBuffer[v6 + 20];
          do
          {
            v18 = &ptForest->ptRawData[v16];
            v18->tPosition.vX = *(float *)(v17 - 16);
            v18->tPosition.vY = *(float *)(v17 - 16 + 4);
            v18->tPosition.vZ = *(float *)(v17 - 16 + 8);
            Real32x9_Create(
              &ptForest->ptRawData[v16].tOrientation,
              *(float *)(v17 - 4),
              *(float *)v17,
              *(float *)(v17 + 4));
            p_tScale = &ptForest->ptRawData[v16].tScale;
            p_tScale->vX = *(float *)(v17 + 8);
            p_tScale->vY = *(float *)(v17 + 12);
            p_tScale->vZ = *(float *)(v17 + 16);
            ++v15;
            v17 += 36;
            ++v16;
          }
          while ( v15 < ptForest->nTrees );
        }
        v20 = *(_DWORD *)((unsigned int)(igi2_frame.pxFileBuffer - 4) & 0xFFFFFFFC);
        --Mem_nCurrentAllocations;
        goto LABEL_30;
      }
      if ( i != 1 )
      {
        LDebug_Error("Forest data file %s version unknown", zFileName);
        abort();
      }
      v8 = ptForest->nTrees;
      if ( v5 - v6 - 4 != 40 * v8 )
      {
        if ( (int)((v5 - v6 - 4) / 0x28) < v8 )
          v8 = (v5 - v6 - 4) / 0x28;
        ptForest->nTrees = v8;
      }
      v9 = 0;
      if ( ptForest->nTrees > 0 )
      {
        v10 = 0;
        v11 = (int)&igi2_frame.pxFileBuffer[v6 + 20];
        do
        {
          v12 = &ptForest->ptRawData[v10];
          v12->tPosition.vX = *(float *)(v11 - 16);
          v12->tPosition.vY = *(float *)(v11 - 16 + 4);
          v12->tPosition.vZ = *(float *)(v11 - 16 + 8);
          Real32x9_Create(
            &ptForest->ptRawData[v10].tOrientation,
            *(float *)(v11 - 4),
            *(float *)v11,
            *(float *)(v11 + 4));
          v13 = &ptForest->ptRawData[v10].tScale;
          v13->vX = *(float *)(v11 + 8);
          v13->vY = *(float *)(v11 + 12);
          v13->vZ = *(float *)(v11 + 16);
          ptForest->ptRawData[v10].bLight = *(_DWORD *)(v11 + 20);
          ++v9;
          v11 += 40;
          ++v10;
        }
        while ( v9 < ptForest->nTrees );
      }
      --Mem_nCurrentAllocations;
      v4 = (size_t *)igi2_frame.pxFileBuffer;
    }
    v20 = *(_DWORD *)((unsigned int)(v4 - 1) & 0xFFFFFFFC);
LABEL_30:
    Node_Remove((_DWORD **)v20);
    memset(*(void **)(v20 + 8), 0xCDu, *(_DWORD *)(v20 + 16));
    free((void *)v20);
  }
}

// source: h/2/forest.c:1096  [anchor-strings]
void __cdecl Forest_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct World_s *ptDynCubeObj; };
    struct { float ptDynCubeObja; };
    struct { char igi2_o2[4]; int v17; };
    struct { char igi2_o3[24]; struct real64x3_t tNull; };
    char igi2_extent[52];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  long double v3; // st7
  unsigned __int16 v4; // cx
  long double v5; // st6
  double v6; // st7
  double v7; // st7
  int *v8; // eax
  int v9; // eax
  double v10; // st6
  int v11; // eax
  struct QReference_s *v12; // ecx
  int v13; // eax
  struct File_s *v14; // eax

  igi2_frame.ptDynCubeObj = World_ptActiveWorld;
  memset(&igi2_frame.tNull, 0, sizeof(igi2_frame.tNull));
  ptQTask[16].tQTaskChildren.ptMiddle = (struct QTask_s *)World_ptActiveWorld;
  ModelObj_Init((struct ModelObj_s *)ptQTask, igi2_frame.ptDynCubeObj, nullptr);
  ptQTask[7].tQTaskChildren.ptHead = nullptr;
  ptQTask[7].tQTaskChildren.ptMiddle = (struct QTask_s *)2;
  ptQTask[7].tQTaskRefList.ptHead = nullptr;
  ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[7].tQTaskRefList.ptTail = nullptr;
  ptQTask[7].ptParent = nullptr;
  *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  ModelObj_Init((struct ModelObj_s *)&ptQTask[8], (struct World_s *)ptQTask[16].tQTaskChildren.ptMiddle, nullptr);
  v3 = sin(0.0);
  v4 = RigidDynCubeObj_eQTaskType;
  ptQTask[15].tQTaskChildren.ptHead = nullptr;
  ptQTask[15].tQTaskChildren.ptMiddle = (struct QTask_s *)2;
  ptQTask[15].tQTaskRefList.ptHead = nullptr;
  ptQTask[15].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[15].tQTaskRefList.ptTail = nullptr;
  ptQTask[15].ptParent = nullptr;
  *(_DWORD *)&ptQTask[15].eQTaskType = 0;
  ptQTask[8].eQTaskType = v4;
  ptQTask[3].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[3].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[3].tQTaskRefList.ptTail = nullptr;
  ptQTask[3].ptParent = nullptr;
  *(_DWORD *)&ptQTask[3].eQTaskType = 1065353216;
  ptQTask[4].ptNext = nullptr;
  v5 = cos(0.0);
  *(float *)&ptQTask[3].ptPrev = v5;
  *(float *)&ptQTask[3].tQTaskChildren.ptHead = -v3;
  *(float *)&ptQTask[3].tQTaskChildren.ptTail = v3;
  *(float *)&ptQTask[3].tQTaskRefList.ptHead = v5;
  if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
    v6 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  else
    v6 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  if ( v6 >= *(float *)&ptQTask[6].ptPrev )
  {
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
      v7 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v7 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  }
  else
  {
    v7 = *(float *)&ptQTask[6].ptPrev;
  }
  v8 = *(int **)&ptQTask[2].eQTaskType;
  if ( v8 && (v9 = *v8) != 0 )
    v10 = *(float *)(*(_DWORD *)(*(_DWORD *)(v9 + 12) + 12) + 120);
  else
    v10 = 1.0;
  igi2_frame.ptDynCubeObja = v7 * v10;
  World_RegisterDynCubeObjFirstTimeRadius(
    (struct World_s *)ptQTask[16].tQTaskChildren.ptMiddle,
    (struct DynCubeObj_s *)ptQTask,
    &igi2_frame.tNull,
    igi2_frame.ptDynCubeObja,
    WORLD_DYNCUBETREE_CATEGORY_STATIONARY);
  ptQTask[16].tQTaskChildren.ptTail = nullptr;
  ptQTask[16].tQTaskRefList.ptHead = nullptr;
  ptQTask[16].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[16].tQTaskRefList.ptTail = nullptr;
  ptQTask[16].ptParent = nullptr;
  *(_DWORD *)&ptQTask[16].eQTaskType = 0;
  ptQTask[37].ptPrev = nullptr;
  ptQTask[36].ptParent = (struct QTask_s *)1133903872;
  ptQTask[37].ptNext = (struct QTask_s *)1092616192;
  ptQTask[37].tQTaskChildren.ptHead = (struct QTask_s *)1241120768;
  ptQTask[37].tQTaskChildren.ptMiddle = (struct QTask_s *)1140457472;
  LOBYTE(ptQTask[17].tQTaskRefList.ptMiddle) = 0;
  *(_DWORD *)&ptQTask[38].eQTaskType = 0;
  ptQTask[39].ptNext = (struct QTask_s *)1;
  ptQTask[38].ptParent = nullptr;
  ptQTask[39].tQTaskChildren.ptTail = (struct QTask_s *)1;
  ptQTask[39].tQTaskChildren.ptMiddle = nullptr;
  v11 = 0;
  while ( 1 )
  {
    v12 = Level_atLevelQTaskID[v11];
    if ( v12 )
    {
      if ( v12->pxObject == ptQTask )
        break;
    }
    if ( ++v11 >= 4096 )
    {
      v11 = -1;
      break;
    }
  }
  ptQTask[38].ptNext = (struct QTask_s *)v11;
  igi2_frame.v17 = Forest_nCount;
  v13 = Forest_nCount + 1;
  ptQTask[16].ptNext = nullptr;
  ptQTask[16].tQTaskChildren.ptHead = nullptr;
  ptQTask[16].ptPrev = nullptr;
  ptQTask[38].tQTaskRefList.ptMiddle = nullptr;
  Forest_nCount = v13;
  sprintf((char *const)&ptQTask[23].isInMemPool + 1, "MISSION:forest%d.dat", igi2_frame.v17);
  v14 = File_New((char *)&ptQTask[23].isInMemPool + 1, "r");
  if ( v14 )
  {
    if ( v14 == &File_tDummyAsyncFile )
      File_tDummyAsyncFile.isAsync = false;
    else
      File_atDevice[v14->eDeviceID].pfDelete(v14->eDeviceID, v14);
    ptQTask[39].tQTaskRefList.ptHead = (struct QReference_s *)1;
  }
}

// source: h/2/forest.c:1164  [anchor-callee]
void __cdecl Forest_DeleteBSPTree(struct ForestNode_s *ptNode)
{
  int v1; // esi

  if ( ptNode )
  {
    v1 = *(_DWORD *)((unsigned int)&ptNode[-1].aptChildren[1] & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
}

// source: h/2/forest.c:1179  [anchor-mhash]
void __cdecl Forest_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // eax
  int v2; // ebx
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptPrev; // eax
  int v5; // ebx

  if ( ptQTask[39].tQTaskChildren.ptMiddle )
  {
    ptQTask[39].tQTaskChildren.ptMiddle = nullptr;
  }
  else if ( File_Exists((char *)&ptQTask[30].tQTaskChildren.ptMiddle + 2) == false
         && (int)ptQTask[38].tQTaskChildren.ptHead > 0 )
  {
    Forest_SaveData((struct Forest_s *)ptQTask);
  }
  ptHead = ptQTask[16].tQTaskChildren.ptHead;
  --Forest_nCount;
  if ( ptHead )
  {
    --Mem_nCurrentAllocations;
    v2 = *(_DWORD *)((unsigned int)&ptHead[-1].eQTaskType & 0xFFFFFFFC);
    Node_Remove((_DWORD **)v2);
    memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
    free((void *)v2);
    ptNext = ptQTask[16].ptNext;
    ptQTask[16].tQTaskChildren.ptHead = nullptr;
    Forest_DeleteBSPTree((struct ForestNode_s *)ptNext);
  }
  ptPrev = ptQTask[16].ptPrev;
  if ( ptPrev )
  {
    v5 = *(_DWORD *)((unsigned int)&ptPrev[-1].eQTaskType & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v5);
    memset(*(void **)(v5 + 8), 0xCDu, *(_DWORD *)(v5 + 16));
    free((void *)v5);
    ptQTask[16].ptPrev = nullptr;
  }
  World_RemoveDynCubeObj((struct World_s *)ptQTask[16].tQTaskChildren.ptMiddle, (struct DynCubeObj_s *)ptQTask);
}

// source: h/2/forest.c:1230  [size]
void __cdecl Forest_RunHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: h/2/forest.c:1249  [anchor-mhash]
unsigned int __cdecl Forest_PointOutCode(float vdX1, float vdY1, float vdX2, float vdY2)
{
  return (LODWORD(vdY2) & 0x8FFFFFFF
        | ((LODWORD(vdX2) & 0x9FFFFFFF | (((LODWORD(vdX1) >> 1) | LODWORD(vdY1) & 0xBFFFFFFF) >> 1)) >> 1)) >> 28;
}

// source: h/2/forest.c:1272  [anchor-mhash]
int __cdecl Forest_IsLineOutOfNode(
        struct Forest_s *ptForest,
        float *avCoords,
        struct LineOfSightContext_s *ptContext)
{
  struct real64x3_t *ptEnd; // edx
  double v4; // st7
  double v5; // st7
  unsigned int v6; // ecx
  unsigned int v7; // ecx
  unsigned int v8; // eax
  double v9; // st7
  double v10; // st7
  double v11; // st7
  double v12; // st7
  int result; // eax
  float vy1; // [esp+0h] [ebp-30h]
  float vx1; // [esp+4h] [ebp-2Ch]
  float vx2; // [esp+8h] [ebp-28h]
  float vy2; // [esp+Ch] [ebp-24h]
  float vY1; // [esp+10h] [ebp-20h]
  float vY2; // [esp+14h] [ebp-1Ch]
  float vX1; // [esp+18h] [ebp-18h]
  float vX2; // [esp+1Ch] [ebp-14h]
  float v22; // [esp+20h] [ebp-10h]
  float v23; // [esp+20h] [ebp-10h]
  float v24; // [esp+24h] [ebp-Ch]
  float v25; // [esp+24h] [ebp-Ch]
  float v26; // [esp+28h] [ebp-8h]
  float v27; // [esp+28h] [ebp-8h]
  float v28; // [esp+2Ch] [ebp-4h]
  float v29; // [esp+2Ch] [ebp-4h]

  vx1 = ptContext->ptStart->vX - ptForest->tPos.vX;
  ptEnd = ptContext->ptEnd;
  vy1 = ptContext->ptStart->vY - ptForest->tPos.vY;
  vx2 = ptEnd->vX - ptForest->tPos.vX;
  vy2 = ptEnd->vY - ptForest->tPos.vY;
  v4 = ptForest->vTreeRadius * 1.5;
  vX1 = avCoords[1] - v4;
  vY1 = avCoords[3] - v4;
  vX2 = v4 + *avCoords;
  v5 = v4 + avCoords[2];
  vY2 = v5;
  v28 = v5 - vy1;
  v26 = vX2 - vx1;
  v22 = vy1 - vY1;
  v24 = vx1 - vX1;
  v6 = (LODWORD(v24) >> 1) | LODWORD(v22) & 0xBFFFFFFF;
  v23 = vY2 - vy2;
  v25 = vX2 - vx2;
  v7 = (LODWORD(v28) & 0x8FFFFFFF | ((LODWORD(v26) & 0x9FFFFFFF | (v6 >> 1)) >> 1)) >> 28;
  v29 = vy2 - vY1;
  v27 = vx2 - vX1;
  v8 = (LODWORD(v23) & 0x8FFFFFFF
      | ((LODWORD(v25) & 0x9FFFFFFF | (((LODWORD(v27) >> 1) | LODWORD(v29) & 0xBFFFFFFF) >> 1)) >> 1)) >> 28;
  result = false;
  if ( v7 * v8 )
  {
    if ( (v8 & v7) != 0 )
      return true;
    if ( v7 != 5 && v8 != 10 )
    {
      if ( (v7 & 1) == 0
        || (v9 = (vy2 - vy1) * (vX1 - vx1) / (vx2 - vx1) + vy1, vy1 = v9, v9 <= vY1)
        || vy1 >= (double)vY2 )
      {
        if ( (v7 & 2) == 0
          || (v10 = (vY1 - vy1) * (vx2 - vx1) / (vy2 - vy1) + vx1, vx1 = v10, v10 <= vX1)
          || vx1 >= (double)vX2 )
        {
          if ( (v7 & 4) == 0
            || (v11 = (vX2 - vx1) * (vy2 - vy1) / (vx2 - vx1) + vy1, vy1 = v11, v11 <= vY1)
            || vy1 >= (double)vY2 )
          {
            if ( (v7 & 8) == 0 )
              return true;
            v12 = (vY2 - vy1) * (vx2 - vx1) / (vy2 - vy1) + vx1;
            if ( v12 <= vX1 || v12 >= vX2 )
              return true;
          }
        }
      }
    }
  }
  return result;
}

// source: h/2/forest.c:1351  [anchor-mhash]
int __cdecl Forest_IsRectIntersection(
        struct Forest_s *ptForest,
        float *avForestRect,
        struct real32x4_t *ptRectToIntersectWith)
{
  double v3; // st7

  v3 = ptForest->vTreeRadius * 1.5;
  return ptRectToIntersectWith->tY.vX > avForestRect[1] - v3
      && ptRectToIntersectWith->tX.vX < *avForestRect + v3
      && ptRectToIntersectWith->tY.vY > avForestRect[3] - v3
      && ptRectToIntersectWith->tX.vY < avForestRect[2] + v3;
}

// source: h/2/forest.c:1380  [anchor-mhash]
int __cdecl Forest_IsPointOutOfNode(
        struct Forest_s *ptForest,
        float *avForestRect,
        float vX,
        float vY,
        struct real32x2_t *ptMargin)
{
  return avForestRect[1] - ptMargin->vX > vX
      || *avForestRect + ptMargin->vX < vX
      || avForestRect[3] - ptMargin->vY > vY
      || avForestRect[2] + ptMargin->vY < vY;
}

// source: h/2/forest.c:1412  [anchor-mhash]
void __cdecl Forest_TraceLineTrees_Optimized(
        struct Forest_s *ptForest,
        struct ForestNode_s *ptNode,
        int nLevel,
        float vRectX1,
        float vRectY1,
        float vRectX2,
        float vRectY2,
        struct Forest_TraceLinesContext_s *ptContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { int iCoordIndex; };
    struct { int iCoordIndexa; };
    struct { char igi2_o2[4]; int iStackTop; };
    struct { char igi2_o3[8]; float avCoords[4]; };
    struct { char igi2_o4[24]; double bDotProductSign; };
    struct { char igi2_o5[36]; float *v44; };
    struct { char igi2_o6[40]; struct Forest_StackElement_s *aptStack; };
    struct { char igi2_o7[44]; int nIntersections; };
    struct { char igi2_o8[48]; union Position32x3_u uViewVector; };
    struct { char igi2_o9[60]; struct real32x3_t tViewPoint; };
    struct { char igi2_o10[72]; struct TraceLinesContext_s tTempContext; };
    struct { char igi2_o11[112]; float avTreeBoundingBox[4]; };
    struct { char igi2_o12[128]; struct QIntersection_s atIntersections[256]; };
    char igi2_extent[30848];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Forest_s *v8; // edx
  struct ForestNode_s *v9; // ebx
  struct TraceLinesContext_s *ptTraceLinesContext; // eax
  struct real64x3_t *ptStart; // eax
  double vY; // st6
  float *p_vX; // esi
  int v14; // eax
  int v15; // ecx
  int v16; // edi
  float v17; // eax
  double v18; // st7
  struct ForestNode_s *v19; // esi
  int v20; // edi
  float *p_vY1; // ecx
  double v22; // st6
  float *v23; // eax
  double vX; // st7
  double v25; // st7
  int v26; // eax
  float *v27; // ecx
  double v28; // st7
  double vTreeRadius; // st5
  int v30; // eax
  struct QIntersection_s *ptIntersection; // ecx
  struct Tree_s *ptTree; // esi
  int v33; // ecx
  BOOL v34; // eax
  bool v35; // zf
  float v36; // esi
  int v37; // eax
  struct Tree_s *v38; // eax

  v8 = ptForest;
  igi2_frame.aptStack = ptForest->aptNodeStack;
  v9 = ptNode;
  igi2_frame.avCoords[0] = vRectX2;
  igi2_frame.avCoords[2] = vRectY2;
  igi2_frame.avCoords[1] = vRectX1;
  igi2_frame.avCoords[3] = vRectY1;
  igi2_frame.nIntersections = 0;
  igi2_frame.iStackTop = 0;
  ptTraceLinesContext = ptContext->ptTraceLinesContext;
  qmemcpy(&igi2_frame.tTempContext, ptContext->ptTraceLinesContext, sizeof(igi2_frame.tTempContext));
  igi2_frame.tTempContext.iIgnoreMaterial = 32;
  igi2_frame.tTempContext.ptIntersection = igi2_frame.atIntersections;
  qmemcpy(igi2_frame.atIntersections, ptTraceLinesContext->ptIntersection, 120 * ptTraceLinesContext->nNumLines);
  ptStart = ptContext->ptTraceLinesContext->ptStart;
  vY = ptStart->vY;
  igi2_frame.tViewPoint.vX = ptStart->vX - ptForest->tPos.vX;
  igi2_frame.tViewPoint.vY = vY - ptForest->tPos.vY;
  if ( ptNode )
  {
    while ( 1 )
    {
      p_vX = &v9->ptTree->tPosition.vX;
      v14 = nLevel & 1;
      igi2_frame.uViewVector.tXYZ.vX = v9->ptTree->tPosition.vX - igi2_frame.tViewPoint.vX;
      igi2_frame.uViewVector.tXYZ.vY = p_vX[1] - igi2_frame.tViewPoint.vY;
      v15 = *((_DWORD *)&igi2_frame.uViewVector.tXYZ.vX + v14) >> 31;
      v16 = v15 + 2 * v14;
      v17 = p_vX[v14];
      v18 = igi2_frame.avCoords[v16];
      v19 = v9->aptChildren[v15];
      igi2_frame.iCoordIndex = v16;
      igi2_frame.avCoords[v16] = v17;
      if ( v19 )
      {
        v20 = 6 * igi2_frame.iStackTop;
        p_vY1 = &igi2_frame.aptStack[igi2_frame.iStackTop].vY1;
        while ( 1 )
        {
          v22 = v8->vTreeRadius * 1.5;
          if ( ptContext->tBoundingRectangle.tY.vX <= igi2_frame.avCoords[1] - v22 )
            break;
          if ( ptContext->tBoundingRectangle.tX.vX >= igi2_frame.avCoords[0] + v22 )
            break;
          if ( ptContext->tBoundingRectangle.tY.vY <= igi2_frame.avCoords[3] - v22 )
            break;
          if ( ptContext->tBoundingRectangle.tX.vY >= igi2_frame.avCoords[2] + v22 )
            break;
          *(p_vY1 - 1) = igi2_frame.avCoords[0];
          *p_vY1 = igi2_frame.avCoords[1];
          p_vY1[1] = igi2_frame.avCoords[2];
          p_vY1[2] = igi2_frame.avCoords[3];
          *((_DWORD *)p_vY1 - 2) = v9;
          *(&igi2_frame.aptStack->vX1 + v20 + igi2_frame.iCoordIndex) = v18;
          *((_DWORD *)p_vY1 + 3) = nLevel;
          p_vY1 += 6;
          ++nLevel;
          v23 = &v19->ptTree->tPosition.vX;
          vX = v19->ptTree->tPosition.vX;
          igi2_frame.v44 = (float *)(v20 + 6);
          ++igi2_frame.iStackTop;
          v9 = v19;
          igi2_frame.uViewVector.tXYZ.vX = vX - igi2_frame.tViewPoint.vX;
          v25 = v23[1];
          v26 = nLevel & 1;
          igi2_frame.uViewVector.tXYZ.vY = v25 - igi2_frame.tViewPoint.vY;
          LODWORD(igi2_frame.bDotProductSign) = *((_DWORD *)&igi2_frame.uViewVector.tXYZ.vX + v26) >> 31;
          v18 = igi2_frame.avCoords[2 * v26 + LODWORD(igi2_frame.bDotProductSign)];
          igi2_frame.iCoordIndex = LODWORD(igi2_frame.bDotProductSign) + 2 * v26;
          igi2_frame.avCoords[igi2_frame.iCoordIndex] = *(&v19->ptTree->tPosition.vX + v26);
          v19 = v19->aptChildren[LODWORD(igi2_frame.bDotProductSign)];
          if ( !v19 )
            break;
          v20 = (int)igi2_frame.v44;
        }
      }
      igi2_frame.avCoords[igi2_frame.iCoordIndex] = v18;
      igi2_frame.v44 = &igi2_frame.aptStack[igi2_frame.iStackTop].vY1;
      while ( 1 )
      {
        v27 = &v9->ptTree->tPosition.vX;
        v28 = v9->ptTree->tPosition.vX;
        vTreeRadius = v8->vTreeRadius;
        igi2_frame.avTreeBoundingBox[2] = v9->ptTree->tPosition.vY;
        igi2_frame.avTreeBoundingBox[3] = igi2_frame.avTreeBoundingBox[2];
        igi2_frame.bDotProductSign = vTreeRadius * 1.5;
        if ( ptContext->tBoundingRectangle.tY.vX > v28 - igi2_frame.bDotProductSign
          && ptContext->tBoundingRectangle.tX.vX < igi2_frame.bDotProductSign + v28
          && ptContext->tBoundingRectangle.tY.vY > igi2_frame.avTreeBoundingBox[3] - igi2_frame.bDotProductSign
          && ptContext->tBoundingRectangle.tX.vY < igi2_frame.avTreeBoundingBox[2] + igi2_frame.bDotProductSign )
        {
          v8->tRigidTree.tModelObj.tDynCubeObj.tQObj.tPos.vX = *v27 + v8->tPos.vX;
          v8->tRigidTree.tModelObj.tDynCubeObj.tQObj.tPos.vY = v9->ptTree->tPosition.vY + v8->tPos.vY;
          v8->tRigidTree.tModelObj.tDynCubeObj.tQObj.tPos.vZ = v9->ptTree->tPosition.vZ + v8->tPos.vZ;
          qmemcpy(
            &v8->tRigidTree.tModelObj.tOrientation,
            &v9->ptTree->tOrientation,
            sizeof(v8->tRigidTree.tModelObj.tOrientation));
          v8->tRigidTree.tModelObj.tScale.vX = v9->ptTree->tScale.vX;
          v8->tRigidTree.tModelObj.tScale.vY = v9->ptTree->tScale.vY;
          v8->tRigidTree.tModelObj.tScale.vZ = v9->ptTree->tScale.vZ;
          ((void (__cdecl *)(struct RigidDynCubeObj_t *, struct TraceLinesContext_s *))QTask_aatQTaskFinalEvent[10][v8->tRigidTree.tModelObj.tDynCubeObj.tQObj.tQTask.eQTaskType].pfHandler)(
            &v8->tRigidTree,
            &igi2_frame.tTempContext);
          v30 = 0;
          igi2_frame.iCoordIndexa = 0;
          if ( ptContext->ptTraceLinesContext->nNumLines > 0 )
          {
            ptIntersection = igi2_frame.tTempContext.ptIntersection;
            do
            {
              if ( ptIntersection[v30].isHit
                && (struct RigidDynCubeObj_t *)ptIntersection[v30].ptHitObj == &ptForest->tRigidTree )
              {
                ptIntersection[v30].tLocalPos.vX = v9->ptTree->tPosition.vX + ptIntersection[v30].tLocalPos.vX;
                igi2_frame.tTempContext.ptIntersection[v30].tLocalPos.vY = v9->ptTree->tPosition.vY
                                                              + igi2_frame.tTempContext.ptIntersection[v30].tLocalPos.vY;
                igi2_frame.tTempContext.ptIntersection[v30].tLocalPos.vZ = v9->ptTree->tPosition.vZ
                                                              + igi2_frame.tTempContext.ptIntersection[v30].tLocalPos.vZ;
                igi2_frame.tTempContext.ptIntersection[v30].ptHitObj = &ptForest->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj;
                qmemcpy(
                  &ptContext->ptTraceLinesContext->ptIntersection[v30],
                  &igi2_frame.tTempContext.ptIntersection[v30],
                  sizeof(ptContext->ptTraceLinesContext->ptIntersection[v30]));
                ++igi2_frame.nIntersections;
                ptIntersection = igi2_frame.tTempContext.ptIntersection;
              }
              ++v30;
              ++igi2_frame.iCoordIndexa;
            }
            while ( igi2_frame.iCoordIndexa < ptContext->ptTraceLinesContext->nNumLines );
          }
          if ( igi2_frame.nIntersections == ptContext->ptTraceLinesContext->nNumLines )
            return;
          v8 = ptForest;
        }
        ptTree = v9->ptTree;
        v33 = nLevel & 1;
        v34 = *((int *)&igi2_frame.uViewVector.tXYZ.vX + v33) >= 0;
        v9 = v9->aptChildren[v34];
        igi2_frame.avCoords[2 * v33 + v34] = *(&ptTree->tPosition.vX + v33);
        if ( v9 )
        {
          igi2_frame.bDotProductSign = v8->vTreeRadius * 1.5;
          if ( ptContext->tBoundingRectangle.tY.vX > igi2_frame.avCoords[1] - igi2_frame.bDotProductSign
            && ptContext->tBoundingRectangle.tX.vX < igi2_frame.avCoords[0] + igi2_frame.bDotProductSign
            && ptContext->tBoundingRectangle.tY.vY > igi2_frame.avCoords[3] - igi2_frame.bDotProductSign
            && ptContext->tBoundingRectangle.tX.vY < igi2_frame.avCoords[2] + igi2_frame.bDotProductSign )
          {
            break;
          }
        }
        v9 = *((struct ForestNode_s **)igi2_frame.v44 - 8);
        igi2_frame.avCoords[0] = *(igi2_frame.v44 - 7);
        igi2_frame.avCoords[1] = *(igi2_frame.v44 - 6);
        v35 = igi2_frame.iStackTop == 0;
        igi2_frame.avCoords[2] = *(igi2_frame.v44 - 5);
        v36 = *(igi2_frame.v44 - 4);
        igi2_frame.v44 -= 6;
        v37 = *((_DWORD *)igi2_frame.v44 + 3);
        --igi2_frame.iStackTop;
        igi2_frame.avCoords[3] = v36;
        nLevel = v37;
        if ( v35 )
          return;
        v38 = v9->ptTree;
        igi2_frame.uViewVector.tXYZ.vX = v9->ptTree->tPosition.vX - igi2_frame.tViewPoint.vX;
        igi2_frame.uViewVector.tXYZ.vY = v38->tPosition.vY - igi2_frame.tViewPoint.vY;
      }
      ++nLevel;
    }
  }
}

// source: h/2/forest.c:1587  [anchor-mhash]
void __cdecl Forest_LineOfSightTrees_Optimized(
        struct Forest_s *ptForest,
        struct ForestNode_s *ptNode,
        int nLevel,
        float vRectX1,
        float vRectY1,
        float vRectX2,
        float vRectY2,
        struct LineOfSightContext_s *ptContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { int iStackTop; };
    struct { char igi2_o1[4]; int iCoordIndex; };
    struct { char igi2_o2[8]; struct ForestNode_s *ptNearNode; };
    struct { char igi2_o3[12]; float vOldCoord; };
    struct { char igi2_o4[16]; struct Forest_StackElement_s *aptStack; };
    struct { char igi2_o5[20]; int v41; };
    struct { char igi2_o6[20]; int v42; };
    struct { char igi2_o7[28]; float vOldT; };
    struct { char igi2_o8[32]; union Position32x3_u uViewVector; };
    struct { char igi2_o9[44]; struct real32x3_t tViewPoint; };
    struct { char igi2_o10[56]; float avCoords[4]; };
    struct { char igi2_o11[72]; float avTreeBoundingBox[4]; };
    char igi2_extent[88];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct ForestNode_s *v8; // ebx
  double vY; // st6
  int v10; // esi
  float *p_vX; // edx
  int v12; // eax
  int v13; // ecx
  int v14; // edi
  struct ForestNode_s *v15; // ecx
  float *p_vY1; // edi
  float v17; // eax
  float v18; // ecx
  float v19; // edx
  float *v20; // edx
  double v21; // st7
  float v22; // edx
  int v23; // ecx
  float v24; // esi
  float *v25; // edi
  float v26; // eax
  int eQTaskType; // ecx
  struct LineOfSightContext_s *v28; // esi
  float *v29; // edx
  int v30; // ecx
  BOOL v31; // eax
  bool v32; // zf
  float v33; // edx
  int v34; // eax
  float *v35; // eax

  v8 = ptNode;
  igi2_frame.aptStack = ptForest->aptNodeStack;
  igi2_frame.avCoords[0] = vRectX2;
  igi2_frame.avCoords[1] = vRectX1;
  igi2_frame.avCoords[2] = vRectY2;
  igi2_frame.avCoords[3] = vRectY1;
  vY = ptContext->ptStart->vY;
  v10 = 0;
  igi2_frame.iStackTop = 0;
  igi2_frame.tViewPoint.vX = ptContext->ptStart->vX - ptForest->tPos.vX;
  igi2_frame.tViewPoint.vY = vY - ptForest->tPos.vY;
  if ( ptNode )
  {
LABEL_2:
    p_vX = &v8->ptTree->tPosition.vX;
    v12 = nLevel & 1;
    igi2_frame.uViewVector.tXYZ.vX = v8->ptTree->tPosition.vX - igi2_frame.tViewPoint.vX;
    igi2_frame.uViewVector.tXYZ.vY = p_vX[1] - igi2_frame.tViewPoint.vY;
    v13 = *((_DWORD *)&igi2_frame.uViewVector.tXYZ.vX + v12) >> 31;
    v14 = v13 + 2 * v12;
    v15 = v8->aptChildren[v13];
    igi2_frame.iCoordIndex = v14;
    igi2_frame.vOldCoord = igi2_frame.avCoords[v14];
    igi2_frame.avCoords[v14] = p_vX[v12];
    igi2_frame.ptNearNode = v15;
    if ( v15 )
    {
      igi2_frame.v41 = v10;
      p_vY1 = &igi2_frame.aptStack[v10].vY1;
      do
      {
        if ( Forest_IsLineOutOfNode(ptForest, igi2_frame.avCoords, ptContext) )
          break;
        v17 = igi2_frame.avCoords[1];
        v18 = igi2_frame.avCoords[2];
        *(p_vY1 - 1) = igi2_frame.avCoords[0];
        v19 = igi2_frame.avCoords[3];
        *p_vY1 = v17;
        p_vY1[1] = v18;
        p_vY1[2] = v19;
        *((_DWORD *)p_vY1 - 2) = v8;
        *(&igi2_frame.aptStack[igi2_frame.v41].vX1 + igi2_frame.iCoordIndex) = igi2_frame.vOldCoord;
        v8 = igi2_frame.ptNearNode;
        *((_DWORD *)p_vY1 + 3) = nLevel;
        ++igi2_frame.iStackTop;
        v20 = &igi2_frame.ptNearNode->ptTree->tPosition.vX;
        p_vY1 += 6;
        ++nLevel;
        igi2_frame.uViewVector.tXYZ.vX = igi2_frame.ptNearNode->ptTree->tPosition.vX - igi2_frame.tViewPoint.vX;
        v21 = v20[1];
        v22 = v20[nLevel & 1];
        ++igi2_frame.v41;
        igi2_frame.uViewVector.tXYZ.vY = v21 - igi2_frame.tViewPoint.vY;
        v23 = *((_DWORD *)&igi2_frame.uViewVector.tXYZ.vX + (nLevel & 1)) >> 31;
        igi2_frame.iCoordIndex = v23 + 2 * (nLevel & 1);
        v24 = igi2_frame.avCoords[igi2_frame.iCoordIndex];
        igi2_frame.avCoords[igi2_frame.iCoordIndex] = v22;
        igi2_frame.vOldCoord = v24;
        igi2_frame.ptNearNode = igi2_frame.ptNearNode->aptChildren[v23];
      }
      while ( igi2_frame.ptNearNode );
      v10 = igi2_frame.iStackTop;
    }
    igi2_frame.avCoords[igi2_frame.iCoordIndex] = igi2_frame.vOldCoord;
    igi2_frame.v42 = (int)&igi2_frame.aptStack[v10].vY1;
    while ( 1 )
    {
      v25 = &v8->ptTree->tPosition.vX;
      v26 = v8->ptTree->tPosition.vY;
      igi2_frame.avTreeBoundingBox[0] = v8->ptTree->tPosition.vX;
      igi2_frame.avTreeBoundingBox[2] = v26;
      igi2_frame.avTreeBoundingBox[3] = v26;
      igi2_frame.avTreeBoundingBox[1] = igi2_frame.avTreeBoundingBox[0];
      if ( Forest_IsLineOutOfNode(ptForest, igi2_frame.avTreeBoundingBox, ptContext) )
      {
        v28 = ptContext;
      }
      else
      {
        igi2_frame.vOldT = ptContext->vT;
        ptForest->tRigidTree.tModelObj.tDynCubeObj.tQObj.tPos.vX = *v25 + ptForest->tPos.vX;
        ptForest->tRigidTree.tModelObj.tDynCubeObj.tQObj.tPos.vY = v8->ptTree->tPosition.vY + ptForest->tPos.vY;
        ptForest->tRigidTree.tModelObj.tDynCubeObj.tQObj.tPos.vZ = v8->ptTree->tPosition.vZ + ptForest->tPos.vZ;
        qmemcpy(
          &ptForest->tRigidTree.tModelObj.tOrientation,
          &v8->ptTree->tOrientation,
          sizeof(ptForest->tRigidTree.tModelObj.tOrientation));
        ptForest->tRigidTree.tModelObj.tScale.vX = v8->ptTree->tScale.vX;
        ptForest->tRigidTree.tModelObj.tScale.vY = v8->ptTree->tScale.vY;
        eQTaskType = ptForest->tRigidTree.tModelObj.tDynCubeObj.tQObj.tQTask.eQTaskType;
        ptForest->tRigidTree.tModelObj.tScale.vZ = v8->ptTree->tScale.vZ;
        ((void (__cdecl *)(struct RigidDynCubeObj_t *, struct LineOfSightContext_s *))QTask_aatQTaskFinalEvent[9][eQTaskType].pfHandler)(
          &ptForest->tRigidTree,
          ptContext);
        v28 = ptContext;
        if ( ptContext->isHit && ptContext->vT < (double)igi2_frame.vOldT )
        {
          ptContext->vTransparency = 0.0;
          return;
        }
      }
      v29 = &v8->ptTree->tPosition.vX;
      v30 = nLevel & 1;
      v31 = *((int *)&igi2_frame.uViewVector.tXYZ.vX + v30) >= 0;
      v8 = v8->aptChildren[v31];
      igi2_frame.avCoords[2 * v30 + v31] = v29[v30];
      if ( v8 && !Forest_IsLineOutOfNode(ptForest, igi2_frame.avCoords, v28) )
      {
        v10 = igi2_frame.iStackTop;
        ++nLevel;
        goto LABEL_2;
      }
      v8 = *(struct ForestNode_s **)(igi2_frame.v42 - 32);
      igi2_frame.avCoords[0] = *(float *)(igi2_frame.v42 - 28);
      igi2_frame.avCoords[1] = *(float *)(igi2_frame.v42 - 24);
      v32 = igi2_frame.iStackTop == 0;
      igi2_frame.avCoords[2] = *(float *)(igi2_frame.v42 - 24 + 4);
      v33 = *(float *)(igi2_frame.v42 - 24 + 8);
      igi2_frame.v42 -= 24;
      v34 = *(_DWORD *)(igi2_frame.v42 + 12);
      --igi2_frame.iStackTop;
      igi2_frame.avCoords[3] = v33;
      nLevel = v34;
      if ( v32 )
        return;
      v35 = &v8->ptTree->tPosition.vX;
      igi2_frame.uViewVector.tXYZ.vX = v8->ptTree->tPosition.vX - igi2_frame.tViewPoint.vX;
      igi2_frame.uViewVector.tXYZ.vY = v35[1] - igi2_frame.tViewPoint.vY;
    }
  }
}

// source: h/2/forest.c:1737  [anchor-mhash]
struct ForestNode_s *__cdecl Forest_GetNextZTrees_Optimized(
        struct Forest_s *ptForest,
        struct ForestNode_s *ptNode,
        int nLevel,
        float vRectX1,
        float vRectY1,
        float vRectX2,
        float vRectY2,
        struct TraceLinesContext_s *ptContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { int iStackTop; };
    struct { char igi2_o1[4]; int iCoordIndex; };
    struct { char igi2_o2[4]; int iCoordIndexa; };
    struct { char igi2_o3[8]; struct Forest_StackElement_s *aptStack; };
    struct { char igi2_o4[16]; int bDotProductSign; };
    struct { char igi2_o5[20]; float tMargin; };
    struct { char igi2_o6[24]; float tMargin_4; };
    struct { char igi2_o7[28]; float tTreeMargin; };
    struct { char igi2_o8[32]; float tTreeMargin_4; };
    struct { char igi2_o9[36]; float tViewPoint; };
    struct { char igi2_o10[40]; float tViewPoint_4; };
    struct { char igi2_o11[48]; union Position32x3_u uViewVector; };
    struct { char igi2_o12[60]; float avCoords[4]; };
    struct { char igi2_o13[76]; float avTreeBoundingBox[4]; };
    char igi2_extent[92];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Forest_s *v8; // edx
  struct ForestNode_s *v9; // ebx
  bool v10; // zf
  double v11; // st7
  double v12; // st7
  struct ForestNode_s *result; // eax
  float *p_vX; // edi
  int v15; // eax
  int v16; // esi
  int v17; // ecx
  struct ForestNode_s *v18; // esi
  double v19; // st7
  int v20; // edi
  int p_vY1; // ecx
  float *v22; // eax
  double v23; // st7
  int v24; // eax
  float *v25; // ecx
  double vX; // st7
  double v27; // st5
  struct Tree_s *p_tRigidTree; // esi
  struct Tree_s *ptTree; // esi
  int v30; // ecx
  BOOL v31; // eax
  float v32; // esi
  struct Tree_s *v33; // eax

  v8 = ptForest;
  v9 = ptNode;
  v10 = ptNode == nullptr;
  igi2_frame.aptStack = ptForest->aptNodeStack;
  v11 = (ptForest->vRandomScaleRangeX * 0.5 + 1.0) * ptForest->vTreeRadius;
  igi2_frame.avCoords[0] = vRectX2;
  igi2_frame.tMargin = v11;
  igi2_frame.avCoords[1] = vRectX1;
  v12 = ptForest->vRandomScaleRangeY * 0.5;
  igi2_frame.avCoords[2] = vRectY2;
  igi2_frame.avCoords[3] = vRectY1;
  result = (struct ForestNode_s *)ptContext->ptStart;
  igi2_frame.iStackTop = 0;
  igi2_frame.tMargin_4 = (v12 + 1.0) * ptForest->vTreeRadius;
  igi2_frame.tViewPoint = ptContext->ptStart->vX - ptForest->tPos.vX;
  igi2_frame.tViewPoint_4 = ptContext->ptStart->vY - ptForest->tPos.vY;
  if ( !v10 )
  {
LABEL_2:
    p_vX = &v9->ptTree->tPosition.vX;
    v15 = nLevel & 1;
    igi2_frame.uViewVector.tXYZ.vX = v9->ptTree->tPosition.vX - igi2_frame.tViewPoint;
    igi2_frame.uViewVector.tXYZ.vY = p_vX[1] - igi2_frame.tViewPoint_4;
    v16 = *((_DWORD *)&igi2_frame.uViewVector.tXYZ.vX + v15) >> 31;
    v17 = v16 + 2 * v15;
    v18 = v9->aptChildren[v16];
    v19 = igi2_frame.avCoords[v17];
    igi2_frame.iCoordIndex = v17;
    igi2_frame.avCoords[v17] = p_vX[v15];
    if ( v18 )
    {
      v20 = igi2_frame.iStackTop;
      p_vY1 = (int)&igi2_frame.aptStack[igi2_frame.iStackTop].vY1;
      while ( igi2_frame.avCoords[1] - igi2_frame.tMargin <= igi2_frame.tViewPoint )
      {
        if ( igi2_frame.avCoords[0] + igi2_frame.tMargin < igi2_frame.tViewPoint )
          break;
        if ( igi2_frame.avCoords[3] - igi2_frame.tMargin_4 > igi2_frame.tViewPoint_4 )
          break;
        if ( igi2_frame.avCoords[2] + igi2_frame.tMargin_4 < igi2_frame.tViewPoint_4 )
          break;
        *(float *)(p_vY1 - 4) = igi2_frame.avCoords[0];
        *(float *)p_vY1 = igi2_frame.avCoords[1];
        *(float *)(p_vY1 + 4) = igi2_frame.avCoords[2];
        *(float *)(p_vY1 + 8) = igi2_frame.avCoords[3];
        *(_DWORD *)(p_vY1 - 8) = v9;
        *(&igi2_frame.aptStack[v20].vX1 + igi2_frame.iCoordIndex) = v19;
        *(_DWORD *)(p_vY1 + 12) = nLevel;
        p_vY1 += 24;
        ++nLevel;
        v22 = &v18->ptTree->tPosition.vX;
        ++igi2_frame.iStackTop;
        v9 = v18;
        igi2_frame.uViewVector.tXYZ.vX = v18->ptTree->tPosition.vX - igi2_frame.tViewPoint;
        v23 = v22[1];
        v24 = nLevel & 1;
        igi2_frame.uViewVector.tXYZ.vY = v23 - igi2_frame.tViewPoint_4;
        igi2_frame.bDotProductSign = *((_DWORD *)&igi2_frame.uViewVector.tXYZ.vX + v24) >> 31;
        v19 = igi2_frame.avCoords[2 * v24 + igi2_frame.bDotProductSign];
        igi2_frame.iCoordIndex = igi2_frame.bDotProductSign + 2 * v24;
        igi2_frame.avCoords[igi2_frame.iCoordIndex] = *(&v18->ptTree->tPosition.vX + v24);
        v18 = v18->aptChildren[igi2_frame.bDotProductSign];
        if ( !v18 )
          break;
        ++v20;
      }
    }
    igi2_frame.avCoords[igi2_frame.iCoordIndex] = v19;
    igi2_frame.iCoordIndexa = (int)&igi2_frame.aptStack[igi2_frame.iStackTop].vY1;
    while ( 1 )
    {
      v25 = &v9->ptTree->tPosition.vX;
      vX = v9->ptTree->tPosition.vX;
      igi2_frame.avTreeBoundingBox[2] = v9->ptTree->tPosition.vY;
      v27 = v25[13];
      igi2_frame.avTreeBoundingBox[3] = igi2_frame.avTreeBoundingBox[2];
      igi2_frame.tTreeMargin = v27 * v8->vTreeRadius;
      igi2_frame.tTreeMargin_4 = v25[14] * v8->vTreeRadius;
      if ( igi2_frame.tViewPoint >= vX - igi2_frame.tTreeMargin
        && igi2_frame.tViewPoint <= igi2_frame.tTreeMargin + vX
        && igi2_frame.avTreeBoundingBox[3] - igi2_frame.tTreeMargin_4 <= igi2_frame.tViewPoint_4
        && igi2_frame.tTreeMargin_4 + igi2_frame.avTreeBoundingBox[2] >= igi2_frame.tViewPoint_4 )
      {
        v8->tRigidTree.tModelObj.tDynCubeObj.tQObj.tPos.vX = *v25 + v8->tPos.vX;
        v8->tRigidTree.tModelObj.tDynCubeObj.tQObj.tPos.vY = v9->ptTree->tPosition.vY + v8->tPos.vY;
        v8->tRigidTree.tModelObj.tDynCubeObj.tQObj.tPos.vZ = v9->ptTree->tPosition.vZ + v8->tPos.vZ;
        qmemcpy(
          &v8->tRigidTree.tModelObj.tOrientation,
          &v9->ptTree->tOrientation,
          sizeof(v8->tRigidTree.tModelObj.tOrientation));
        p_tRigidTree = (struct Tree_s *)&v8->tRigidTree;
        v8->tRigidTree.tModelObj.tScale.vX = v9->ptTree->tScale.vX;
        v8->tRigidTree.tModelObj.tScale.vY = v9->ptTree->tScale.vY;
        v8->tRigidTree.tModelObj.tScale.vZ = v9->ptTree->tScale.vZ;
        ((void (__cdecl *)(struct RigidDynCubeObj_t *, struct TraceLinesContext_s *))QTask_aatQTaskFinalEvent[11][v8->tRigidTree.tModelObj.tDynCubeObj.tQObj.tQTask.eQTaskType].pfHandler)(
          &v8->tRigidTree,
          ptContext);
        result = (struct ForestNode_s *)ptContext->ptIntersection;
        if ( result[3].aptChildren[1] && result->ptTree == p_tRigidTree )
        {
          ptContext->ptIntersection->ptHitObj = &ptForest->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj;
          return result;
        }
        v8 = ptForest;
      }
      ptTree = v9->ptTree;
      v30 = nLevel & 1;
      v31 = *((int *)&igi2_frame.uViewVector.tXYZ.vX + v30) >= 0;
      v9 = v9->aptChildren[v31];
      igi2_frame.avCoords[2 * v30 + v31] = *(&ptTree->tPosition.vX + v30);
      if ( v9
        && igi2_frame.avCoords[1] - igi2_frame.tMargin <= igi2_frame.tViewPoint
        && igi2_frame.avCoords[0] + igi2_frame.tMargin >= igi2_frame.tViewPoint
        && igi2_frame.avCoords[3] - igi2_frame.tMargin_4 <= igi2_frame.tViewPoint_4
        && igi2_frame.avCoords[2] + igi2_frame.tMargin_4 >= igi2_frame.tViewPoint_4 )
      {
        ++nLevel;
        goto LABEL_2;
      }
      v9 = *(struct ForestNode_s **)(igi2_frame.iCoordIndexa - 32);
      igi2_frame.avCoords[0] = *(float *)(igi2_frame.iCoordIndexa - 28);
      igi2_frame.avCoords[1] = *(float *)(igi2_frame.iCoordIndexa - 24);
      v10 = igi2_frame.iStackTop == 0;
      igi2_frame.avCoords[2] = *(float *)(igi2_frame.iCoordIndexa - 24 + 4);
      v32 = *(float *)(igi2_frame.iCoordIndexa - 24 + 8);
      igi2_frame.iCoordIndexa -= 24;
      result = *(struct ForestNode_s **)(igi2_frame.iCoordIndexa + 12);
      --igi2_frame.iStackTop;
      igi2_frame.avCoords[3] = v32;
      nLevel = (int)result;
      if ( v10 )
        return result;
      v33 = v9->ptTree;
      igi2_frame.uViewVector.tXYZ.vX = v9->ptTree->tPosition.vX - igi2_frame.tViewPoint;
      igi2_frame.uViewVector.tXYZ.vY = v33->tPosition.vY - igi2_frame.tViewPoint_4;
    }
  }
  return result;
}

// source: h/2/forest.c:1938  [anchor-mhash]
void __cdecl Forest_GetLineOfSightHandler(struct QTask_s *ptQTask, void *pxContext)
{
  double v3; // st7
  float nLevel; // [esp+0h] [ebp-4h]
  float ptQTaska = *(float *)&ptQTask; // [esp+8h] [ebp+4h] ARGSLOT

  if ( (int)ptQTask[38].tQTaskChildren.ptHead > 0 )
  {
    v3 = *(float *)&ptQTask[36].ptParent * 2048.0;
    ptQTask[8].eQTaskType = RigidDynCubeObj_eQTaskType;
    ptQTaska = v3;
    nLevel = *(float *)&ptQTask[36].ptParent * -2048.0;
    Forest_LineOfSightTrees_Optimized(
      (struct Forest_s *)ptQTask,
      (struct ForestNode_s *)ptQTask[16].ptNext,
      0,
      nLevel,
      nLevel,
      ptQTaska,
      ptQTaska,
      (struct LineOfSightContext_s *)pxContext);
  }
}

// source: h/2/forest.c:1970  [anchor-mhash]
void __cdecl Forest_TraceLinesHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vRectY1; };
    struct { char igi2_o1[4]; float nLevel; };
    struct { char igi2_o2[8]; float tEnd; };
    struct { char igi2_o3[12]; float tEnd_4; };
    struct { char igi2_o4[20]; float tStart; };
    struct { char igi2_o5[32]; struct Forest_TraceLinesContext_s tForestTraceLinesContext; };
    char igi2_extent[52];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double *v2; // edx
  double v3; // st7
  double v4; // st7
  double v5; // st6
  int v6; // ebx
  double v7; // st7
  double v8; // st6
  double *v9; // edi
  double *v10; // edx
  int v11; // esi
  double v12; // st5

  if ( (int)ptQTask[38].tQTaskChildren.ptHead > 0 )
  {
    v2 = *(double **)pxContext;
    v3 = *(double *)*(_DWORD *)pxContext;
    igi2_frame.tForestTraceLinesContext.ptTraceLinesContext = (struct TraceLinesContext_s *)pxContext;
    v4 = v3 - *(double *)&ptQTask[16].tQTaskChildren.ptTail;
    igi2_frame.tForestTraceLinesContext.tBoundingRectangle.tX.vX = v4;
    v5 = v2[1] - *(double *)&ptQTask[16].tQTaskRefList.ptMiddle;
    ptQTask[8].eQTaskType = RigidDynCubeObj_eQTaskType;
    v6 = *((_DWORD *)pxContext + 2);
    igi2_frame.tForestTraceLinesContext.tBoundingRectangle.tX.vY = v5;
    igi2_frame.tForestTraceLinesContext.tBoundingRectangle.tY.vX = v4;
    igi2_frame.tForestTraceLinesContext.tBoundingRectangle.tY.vY = v5;
    if ( v6 > 0 )
    {
      v7 = *(double *)&ptQTask[16].tQTaskChildren.ptTail;
      v8 = *(double *)&ptQTask[16].tQTaskRefList.ptMiddle;
      v9 = (double *)(*(_DWORD *)pxContext + 8);
      v10 = *((double **)pxContext + 1);
      v11 = *(_DWORD *)pxContext - (_DWORD)v10;
      do
      {
        igi2_frame.tStart = *(double *)((char *)v10 + v11) - v7;
        v12 = *v9 - v8;
        igi2_frame.tEnd = *v10 - v7;
        igi2_frame.tEnd_4 = v10[1] - v8;
        if ( igi2_frame.tStart > (double)igi2_frame.tForestTraceLinesContext.tBoundingRectangle.tY.vX )
          igi2_frame.tForestTraceLinesContext.tBoundingRectangle.tY.vX = *(double *)((char *)v10 + v11) - v7;
        if ( igi2_frame.tStart < (double)igi2_frame.tForestTraceLinesContext.tBoundingRectangle.tX.vX )
          igi2_frame.tForestTraceLinesContext.tBoundingRectangle.tX.vX = igi2_frame.tStart;
        if ( v12 > igi2_frame.tForestTraceLinesContext.tBoundingRectangle.tY.vY )
          igi2_frame.tForestTraceLinesContext.tBoundingRectangle.tY.vY = v12;
        if ( v12 < igi2_frame.tForestTraceLinesContext.tBoundingRectangle.tX.vY )
          igi2_frame.tForestTraceLinesContext.tBoundingRectangle.tX.vY = v12;
        if ( igi2_frame.tEnd > (double)igi2_frame.tForestTraceLinesContext.tBoundingRectangle.tY.vX )
          igi2_frame.tForestTraceLinesContext.tBoundingRectangle.tY.vX = igi2_frame.tEnd;
        if ( igi2_frame.tEnd < (double)igi2_frame.tForestTraceLinesContext.tBoundingRectangle.tX.vX )
          igi2_frame.tForestTraceLinesContext.tBoundingRectangle.tX.vX = igi2_frame.tEnd;
        if ( igi2_frame.tEnd_4 > (double)igi2_frame.tForestTraceLinesContext.tBoundingRectangle.tY.vY )
          igi2_frame.tForestTraceLinesContext.tBoundingRectangle.tY.vY = igi2_frame.tEnd_4;
        if ( igi2_frame.tEnd_4 < (double)igi2_frame.tForestTraceLinesContext.tBoundingRectangle.tX.vY )
          igi2_frame.tForestTraceLinesContext.tBoundingRectangle.tX.vY = igi2_frame.tEnd_4;
        v9 += 3;
        v10 += 3;
        --v6;
      }
      while ( v6 );
    }
    igi2_frame.vRectY1 = *(float *)&ptQTask[36].ptParent * 2048.0;
    igi2_frame.nLevel = *(float *)&ptQTask[36].ptParent * -2048.0;
    Forest_TraceLineTrees_Optimized(
      (struct Forest_s *)ptQTask,
      (struct ForestNode_s *)ptQTask[16].ptNext,
      0,
      igi2_frame.nLevel,
      igi2_frame.nLevel,
      igi2_frame.vRectY1,
      igi2_frame.vRectY1,
      &igi2_frame.tForestTraceLinesContext);
  }
}

// source: h/2/forest.c:2057  [anchor-mhash]
void __cdecl Forest_GetNextZHandler(struct QTask_s *ptQTask, void *pxContext)
{
  __int16 v4; // ax
  void (__cdecl *pfHandler)(struct QTask_s *, _DWORD); // eax
  float ptQTaska = *(float *)&ptQTask; // [esp+8h] [ebp+4h] ARGSLOT
  float pxContexta = *(float *)&pxContext; // [esp+Ch] [ebp+8h] ARGSLOT

  if ( (int)ptQTask[38].tQTaskChildren.ptHead > 0 )
  {
    v4 = *((_WORD *)pxContext + 6);
    if ( v4 == 512
      || (pfHandler = (void (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[v4][ptQTask->eQTaskType].pfHandler) == nullptr
      || (pfHandler(ptQTask, *((_DWORD *)pxContext + 4)), **((_BYTE **)pxContext + 4)) )
    {
      ptQTaska = *(float *)&ptQTask[36].ptParent * 2048.0;
      pxContexta = *(float *)&ptQTask[36].ptParent * -2048.0;
      Forest_GetNextZTrees_Optimized(
        (struct Forest_s *)ptQTask,
        (struct ForestNode_s *)ptQTask[16].ptNext,
        0,
        pxContexta,
        pxContexta,
        ptQTaska,
        ptQTaska,
        (struct TraceLinesContext_s *)pxContext);
    }
  }
}

// source: h/2/forest.c:2102  [size]
void __cdecl Forest_GetNextZEvaluateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_BYTE *)pxContext = *(_WORD *)(*((_DWORD *)pxContext + 1) + 36) != Rain_eQTaskType;
}

// source: h/2/forest.c:2205  [anchor-mhash]
int __cdecl Forest_IsAABBOutOfSight(
        struct Forest_s *ptForest,
        struct ForestNode_s *ptNode,
        float *avForestRect,
        struct real32x2_t *ptMinMaxZ,
        float vMargin,
        int ltcg_arg3)
{
  int iMostRecentPlaneIndex; // ebp
  int v7; // edx
  double v8; // st7
  double v9; // st6
  int v10; // edi
  double v11; // st7
  struct Clipping_ClipPlane_s *v12; // ecx
  double v13; // st6
  double v14; // st5
  int v15; // edx
  double v16; // st7
  double v17; // st5
  int v18; // edx
  double v19; // st6
  int v20; // edx
  int v21; // edx
  int v22; // edx
  int v23; // edx
  int v24; // edx
  float *p_vZ; // edx
  double v26; // st7
  double v27; // st5
  double v28; // st7
  int v29; // ecx
  double v30; // st6
  int v31; // ecx
  int v32; // ecx
  double v33; // st6
  int v34; // ecx
  int v35; // ecx
  int v36; // ecx
  int v37; // ecx
  char v38; // si
  float *v39; // edx
  double v40; // st7
  double v41; // st5
  double v42; // st7
  int v43; // ecx
  double v44; // st6
  int v45; // ecx
  int v46; // ecx
  double v47; // st6
  int v48; // ecx
  int v49; // ecx
  int v50; // ecx
  int v51; // ecx
  struct ForestNode_s *v52; // eax
  struct ForestNode_s *v53; // eax
  float v55; // [esp+10h] [ebp-44h]
  float v56; // [esp+14h] [ebp-40h]
  float v57; // [esp+18h] [ebp-3Ch]
  float v58; // [esp+18h] [ebp-3Ch]
  float v59; // [esp+18h] [ebp-3Ch]
  float v60; // [esp+1Ch] [ebp-38h]
  float v61; // [esp+1Ch] [ebp-38h]
  float v62; // [esp+1Ch] [ebp-38h]
  int v63; // [esp+20h] [ebp-34h]
  float vZ; // [esp+24h] [ebp-30h]
  float v65; // [esp+28h] [ebp-2Ch]
  float v66; // [esp+2Ch] [ebp-28h]
  float v67; // [esp+30h] [ebp-24h]
  float v68; // [esp+30h] [ebp-24h]
  float v69; // [esp+30h] [ebp-24h]
  float v70; // [esp+34h] [ebp-20h]
  float v71; // [esp+34h] [ebp-20h]
  float v72; // [esp+34h] [ebp-20h]
  float v73; // [esp+38h] [ebp-1Ch]
  float v74; // [esp+3Ch] [ebp-18h]
  float v75; // [esp+3Ch] [ebp-18h]
  float v76; // [esp+40h] [ebp-14h]
  float v77; // [esp+40h] [ebp-14h]
  float v78; // [esp+44h] [ebp-10h]
  float v79; // [esp+44h] [ebp-10h]
  float v80; // [esp+44h] [ebp-10h]
  float v81; // [esp+44h] [ebp-10h]
  float v82; // [esp+44h] [ebp-10h]
  float v83; // [esp+44h] [ebp-10h]
  float v84; // [esp+44h] [ebp-10h]
  float v85; // [esp+44h] [ebp-10h]
  float v86; // [esp+44h] [ebp-10h]
  float v87; // [esp+48h] [ebp-Ch]
  float v88; // [esp+48h] [ebp-Ch]
  float v89; // [esp+48h] [ebp-Ch]
  float v90; // [esp+48h] [ebp-Ch]
  float v91; // [esp+48h] [ebp-Ch]
  float v92; // [esp+48h] [ebp-Ch]
  float v93; // [esp+48h] [ebp-Ch]
  float v94; // [esp+48h] [ebp-Ch]
  float v95; // [esp+48h] [ebp-Ch]
  float v96; // [esp+48h] [ebp-Ch]
  float v97; // [esp+48h] [ebp-Ch]
  float v98; // [esp+48h] [ebp-Ch]
  float v99; // [esp+48h] [ebp-Ch]
  float v100; // [esp+48h] [ebp-Ch]
  float v101; // [esp+48h] [ebp-Ch]
  float v102; // [esp+48h] [ebp-Ch]
  float v103; // [esp+48h] [ebp-Ch]
  float v104; // [esp+48h] [ebp-Ch]
  float v105; // [esp+48h] [ebp-Ch]
  float v106; // [esp+48h] [ebp-Ch]
  float v107; // [esp+4Ch] [ebp-8h]
  float v108; // [esp+4Ch] [ebp-8h]

  iMostRecentPlaneIndex = ptNode->iMostRecentPlaneIndex;
  v7 = 127;
  v63 = 127;
  if ( (iMostRecentPlaneIndex & 0xFFFFFF00) == 0x7F00 )
  {
LABEL_63:
    if ( ltcg_arg3 )
    {
      v52 = ptNode->aptChildren[0];
      if ( v52 )
        v52->iMostRecentPlaneIndex = (v7 << 8) | (unsigned __int8)v52->iMostRecentPlaneIndex;
      v53 = ptNode->aptChildren[1];
      if ( v53 )
        v53->iMostRecentPlaneIndex = (v7 << 8) | (unsigned __int8)v53->iMostRecentPlaneIndex;
    }
    return 0;
  }
  v8 = avForestRect[1] - vMargin;
  v9 = avForestRect[3] - vMargin;
  v10 = (unsigned __int8)iMostRecentPlaneIndex;
  v65 = vMargin + *avForestRect - v8;
  v66 = vMargin + avForestRect[2] - v9;
  v56 = v8 + ptForest->tPos.vX;
  v55 = v9 + ptForest->tPos.vY;
  vZ = ptForest->tPos.vZ;
  if ( ((1 << (iMostRecentPlaneIndex + 8)) & iMostRecentPlaneIndex) != 0 )
  {
LABEL_20:
    v10 = 0;
    if ( (_BYTE)iMostRecentPlaneIndex )
    {
      p_vZ = &Forest_tClipPlanes.ptClipPlane->tPos.vZ;
      do
      {
        if ( ((1 << (v10 + 8)) & iMostRecentPlaneIndex) == 0 )
        {
          v26 = v65 * 0.0 + v56;
          v68 = v26;
          v27 = v66 * 0.0 + v55;
          v58 = v27;
          v61 = vZ + ptMinMaxZ->vX;
          v93 = v26 - *(p_vZ - 2);
          v74 = v26;
          v28 = vZ + ptMinMaxZ->vY;
          v29 = 2 * ((v61 - *p_vZ) * p_vZ[3] + (v27 - *(p_vZ - 1)) * p_vZ[2] + v93 * p_vZ[1] > 0.0);
          if ( (v28 - *p_vZ) * p_vZ[3] + (v58 - *(p_vZ - 1)) * p_vZ[2] + (v74 - *(p_vZ - 2)) * p_vZ[1] > 0.0 )
            v29 |= 1u;
          v30 = v56 + v65;
          v31 = 2 * v29;
          v71 = v30;
          v94 = v30 - *(p_vZ - 2);
          if ( (v61 - *p_vZ) * p_vZ[3] + (v58 - *(p_vZ - 1)) * p_vZ[2] + v94 * p_vZ[1] > 0.0 )
            v31 |= 1u;
          v32 = 2 * v31;
          v81 = v28;
          v95 = v30 - *(p_vZ - 2);
          if ( (v81 - *p_vZ) * p_vZ[3] + (v58 - *(p_vZ - 1)) * p_vZ[2] + v95 * p_vZ[1] > 0.0 )
            v32 |= 1u;
          v33 = v55 + v66;
          v34 = 2 * v32;
          v96 = v68 - *(p_vZ - 2);
          v107 = v33 - *(p_vZ - 1);
          if ( (v61 - *p_vZ) * p_vZ[3] + v107 * p_vZ[2] + v96 * p_vZ[1] > 0.0 )
            v34 |= 1u;
          v35 = 2 * v34;
          v82 = v28;
          v97 = v68 - *(p_vZ - 2);
          if ( (v82 - *p_vZ) * p_vZ[3] + (v33 - *(p_vZ - 1)) * p_vZ[2] + v97 * p_vZ[1] > 0.0 )
            v35 |= 1u;
          v36 = 2 * v35;
          v98 = v71 - *(p_vZ - 2);
          if ( (v61 - *p_vZ) * p_vZ[3] + (v33 - *(p_vZ - 1)) * p_vZ[2] + v98 * p_vZ[1] > 0.0 )
            v36 |= 1u;
          v83 = v28;
          v37 = 2 * v36;
          v99 = v71 - *(p_vZ - 2);
          if ( (v83 - *p_vZ) * p_vZ[3] + (v33 - *(p_vZ - 1)) * p_vZ[2] + v99 * p_vZ[1] > 0.0 )
            v37 |= 1u;
          if ( v37 == 255 )
            goto LABEL_69;
          if ( v37 )
            v63 ^= 1 << v10;
        }
        ++v10;
        p_vZ += 6;
      }
      while ( v10 < (unsigned __int8)iMostRecentPlaneIndex );
    }
    v10 = (unsigned __int8)iMostRecentPlaneIndex + 1;
    if ( v10 < Forest_tClipPlanes.nClipPlanes )
    {
      v38 = iMostRecentPlaneIndex + 9;
      v39 = &Forest_tClipPlanes.ptClipPlane[v10].tPos.vZ;
      do
      {
        if ( ((1 << v38) & iMostRecentPlaneIndex) == 0 )
        {
          v40 = v65 * 0.0 + v56;
          v69 = v40;
          v41 = v66 * 0.0 + v55;
          v59 = v41;
          v62 = vZ + ptMinMaxZ->vX;
          v100 = v40 - *(v39 - 2);
          v75 = v40;
          v42 = vZ + ptMinMaxZ->vY;
          v43 = 2 * ((v62 - *v39) * v39[3] + (v41 - *(v39 - 1)) * v39[2] + v100 * v39[1] > 0.0);
          if ( (v42 - *v39) * v39[3] + (v59 - *(v39 - 1)) * v39[2] + (v75 - *(v39 - 2)) * v39[1] > 0.0 )
            v43 |= 1u;
          v44 = v56 + v65;
          v45 = 2 * v43;
          v72 = v44;
          v101 = v44 - *(v39 - 2);
          if ( (v62 - *v39) * v39[3] + (v59 - *(v39 - 1)) * v39[2] + v101 * v39[1] > 0.0 )
            v45 |= 1u;
          v46 = 2 * v45;
          v84 = v42;
          v102 = v44 - *(v39 - 2);
          if ( (v84 - *v39) * v39[3] + (v59 - *(v39 - 1)) * v39[2] + v102 * v39[1] > 0.0 )
            v46 |= 1u;
          v47 = v55 + v66;
          v48 = 2 * v46;
          v103 = v69 - *(v39 - 2);
          v108 = v47 - *(v39 - 1);
          if ( (v62 - *v39) * v39[3] + v108 * v39[2] + v103 * v39[1] > 0.0 )
            v48 |= 1u;
          v49 = 2 * v48;
          v85 = v42;
          v104 = v69 - *(v39 - 2);
          if ( (v85 - *v39) * v39[3] + (v47 - *(v39 - 1)) * v39[2] + v104 * v39[1] > 0.0 )
            v49 |= 1u;
          v50 = 2 * v49;
          v105 = v72 - *(v39 - 2);
          if ( (v62 - *v39) * v39[3] + (v47 - *(v39 - 1)) * v39[2] + v105 * v39[1] > 0.0 )
            v50 |= 1u;
          v86 = v42;
          v51 = 2 * v50;
          v106 = v72 - *(v39 - 2);
          if ( (v86 - *v39) * v39[3] + (v47 - *(v39 - 1)) * v39[2] + v106 * v39[1] > 0.0 )
            v51 |= 1u;
          if ( v51 == 255 )
            goto LABEL_69;
          if ( v51 )
            v63 ^= 1 << v10;
        }
        ++v10;
        ++v38;
        v39 += 6;
      }
      while ( v10 < Forest_tClipPlanes.nClipPlanes );
    }
    v7 = v63;
    goto LABEL_63;
  }
  v11 = v65 * 0.0;
  v12 = &Forest_tClipPlanes.ptClipPlane[(unsigned __int8)iMostRecentPlaneIndex];
  v13 = v56 + v11;
  v60 = v13;
  v14 = v66 * 0.0;
  v70 = v14;
  v67 = vZ + ptMinMaxZ->vX;
  v87 = v13 - v12->tPos.vX;
  v15 = 2
      * ((v14 + v55 - v12->tPos.vY) * v12->tNormal.vY + (v67 - v12->tPos.vZ) * v12->tNormal.vZ + v87 * v12->tNormal.vX > 0.0);
  v57 = v11 + v56;
  v76 = v70 + v55;
  v16 = vZ + ptMinMaxZ->vY;
  if ( (v76 - v12->tPos.vY) * v12->tNormal.vY
     + (v16 - v12->tPos.vZ) * v12->tNormal.vZ
     + (v57 - v12->tPos.vX) * v12->tNormal.vX > 0.0 )
    v15 |= 1u;
  v17 = v56 + v65;
  v18 = 2 * v15;
  v88 = v17 - v12->tPos.vX;
  if ( (v70 + v55 - v12->tPos.vY) * v12->tNormal.vY + (v67 - v12->tPos.vZ) * v12->tNormal.vZ + v88 * v12->tNormal.vX > 0.0 )
    v18 |= 1u;
  v19 = v65 + v56;
  v20 = 2 * v18;
  v78 = v16;
  v89 = v19 - v12->tPos.vX;
  if ( (v70 + v55 - v12->tPos.vY) * v12->tNormal.vY + (v78 - v12->tPos.vZ) * v12->tNormal.vZ + v89 * v12->tNormal.vX > 0.0 )
    v20 |= 1u;
  v21 = 2 * v20;
  v90 = v60 - v12->tPos.vX;
  if ( (v66 + v55 - v12->tPos.vY) * v12->tNormal.vY + (v67 - v12->tPos.vZ) * v12->tNormal.vZ + v90 * v12->tNormal.vX > 0.0 )
    v21 |= 1u;
  v22 = 2 * v21;
  v79 = v16;
  v91 = v57 - v12->tPos.vX;
  if ( (v66 + v55 - v12->tPos.vY) * v12->tNormal.vY + (v79 - v12->tPos.vZ) * v12->tNormal.vZ + v91 * v12->tNormal.vX > 0.0 )
    v22 |= 1u;
  v23 = 2 * v22;
  v73 = v17;
  v92 = v73 - v12->tPos.vX;
  if ( (v66 + v55 - v12->tPos.vY) * v12->tNormal.vY + (v67 - v12->tPos.vZ) * v12->tNormal.vZ + v92 * v12->tNormal.vX > 0.0 )
    v23 |= 1u;
  v24 = 2 * v23;
  v77 = v66 + v55;
  v80 = v16;
  if ( (v77 - v12->tPos.vY) * v12->tNormal.vY
     + (v80 - v12->tPos.vZ) * v12->tNormal.vZ
     + (v19 - v12->tPos.vX) * v12->tNormal.vX > 0.0 )
    v24 |= 1u;
  if ( v24 != 255 )
  {
    if ( v24 )
      v63 = (1 << iMostRecentPlaneIndex) ^ 0x7F;
    goto LABEL_20;
  }
LABEL_69:
  if ( ltcg_arg3 )
    ptNode->iMostRecentPlaneIndex = v10 | iMostRecentPlaneIndex & 0x7F00;
  return 1;
}

// source: h/2/forest.c:2317  [anchor-mhash]
struct ForestNode_s *__cdecl Forest_DrawTrees1_Optimized(
        struct Forest_s *ptForest,
        enum Mesh3D_DrawMode_e eDrawMode,
        struct ForestNode_s *ptNode,
        int nLevel,
        float vRectX1,
        float vRectY1,
        float vRectX2,
        float vRectY2)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v38; };
    struct { char igi2_o1[4]; int v39; };
    struct { char igi2_o2[8]; float v40; };
    struct { char igi2_o3[12]; struct Forest_StackElement_s *aptNodeStack; };
    struct { char igi2_o4[16]; int p_vY1; };
    struct { char igi2_o5[16]; int v42; };
    struct { char igi2_o6[20]; float avForestRect; };
    struct { char igi2_o7[28]; struct ForestNode_s v45; };
    struct { char igi2_o8[52]; float v46; };
    struct { char igi2_o9[60]; int v47; };
    struct { char igi2_o10[64]; float v48; };
    struct { char igi2_o11[68]; float v49; };
    struct { char igi2_o12[72]; float v50; };
    struct { char igi2_o13[76]; float v51[4]; };
    struct { char igi2_o14[92]; _DWORD v52[8]; };
    char igi2_extent[124];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Forest_s *v8; // edx
  double vRandomScaleRangeY; // st7
  struct ForestNode_s *result; // eax
  double v12; // st7
  struct Tree_s *ptTree; // edi
  int v14; // eax
  int v15; // ecx
  int v16; // esi
  int v17; // eax
  struct ForestNode_s *v18; // edi
  struct Forest_StackElement_s *v19; // esi
  float v20; // edx
  float v21; // eax
  float v22; // ecx
  float *p_vX; // ecx
  int v24; // ecx
  int v25; // eax
  struct Tree_s *v26; // eax
  double v27; // st7
  struct real32x9_t *p_tOrientation; // edx
  double v29; // st7
  int nWindLODs; // edx
  float vTreeRadius; // ecx
  struct Tree_s *v32; // edx
  int v33; // ecx
  BOOL v34; // eax
  bool v35; // zf
  float v36; // edx
  struct Tree_s *v37; // eax

  v8 = ptForest;
  igi2_frame.aptNodeStack = ptForest->aptNodeStack;
  if ( ptForest->vRandomScaleRangeX <= (double)ptForest->vRandomScaleRangeY )
    vRandomScaleRangeY = ptForest->vRandomScaleRangeY;
  else
    vRandomScaleRangeY = ptForest->vRandomScaleRangeX;
  igi2_frame.v47 = LODWORD(vRectX2);
  igi2_frame.v48 = vRectX1;
  result = (struct ForestNode_s *)LODWORD(vRectY1);
  v12 = (vRandomScaleRangeY * 0.5 + 1.0) * ptForest->vTreeRadius;
  igi2_frame.v49 = vRectY2;
  igi2_frame.v50 = vRectY1;
  igi2_frame.avForestRect = v12;
  igi2_frame.v38 = 0;
  *(float *)&igi2_frame.v45.aptChildren[1] = TransContext_tActiveTransContext.tPos.vX - ptForest->tPos.vX;
  igi2_frame.v46 = TransContext_tActiveTransContext.tPos.vY - ptForest->tPos.vY;
  if ( ptNode )
  {
    ptNode->iMostRecentPlaneIndex = (unsigned __int8)ptNode->iMostRecentPlaneIndex;
    while ( 1 )
    {
      ptTree = ptNode->ptTree;
      v14 = nLevel & 1;
      igi2_frame.v45.tMinMaxZ.vY = ptNode->ptTree->tPosition.vX - *(float *)&igi2_frame.v45.aptChildren[1];
      *(float *)&igi2_frame.v45.iMostRecentPlaneIndex = ptTree->tPosition.vY - igi2_frame.v46;
      v15 = *((_DWORD *)&igi2_frame.v45.tMinMaxZ.vY + v14) >> 31;
      v16 = v15 + 2 * v14;
      v17 = *((_DWORD *)&ptTree->tPosition.vX + v14);
      v18 = ptNode->aptChildren[v15];
      igi2_frame.v39 = v16;
      igi2_frame.v40 = *((float *)&igi2_frame.v47 + v16);
      *(&igi2_frame.v47 + v16) = v17;
      if ( v18 )
      {
        igi2_frame.v42 = igi2_frame.v38;
        v19 = (struct Forest_StackElement_s *)&igi2_frame.aptNodeStack[igi2_frame.v38].avCoords[1];
        while ( !Forest_IsAABBOutOfSight(v8, v18, (float *)&igi2_frame.v47, &v18->tMinMaxZ, igi2_frame.avForestRect, 1) )
        {
          v20 = igi2_frame.v48;
          v21 = igi2_frame.v49;
          v19[-1].nLevel = igi2_frame.v47;
          v22 = igi2_frame.v50;
          *(float *)&v19->ptNode = v20;
          v19->vY1 = v22;
          v19->vX1 = v21;
          LODWORD(v19[-1].vY2) = ptNode;
          *(&igi2_frame.aptNodeStack[igi2_frame.v42].vX1 + igi2_frame.v39) = igi2_frame.v40;
          LODWORD(v19->vX2) = nLevel;
          ++igi2_frame.v42;
          p_vX = &v18->ptTree->tPosition.vX;
          ++v19;
          ++nLevel;
          igi2_frame.v45.tMinMaxZ.vY = v18->ptTree->tPosition.vX - *(float *)&igi2_frame.v45.aptChildren[1];
          ++igi2_frame.v38;
          ptNode = v18;
          *(float *)&igi2_frame.v45.iMostRecentPlaneIndex = p_vX[1] - igi2_frame.v46;
          v24 = *((_DWORD *)&igi2_frame.v45.tMinMaxZ.vY + (nLevel & 1)) >> 31;
          igi2_frame.v39 = v24 + 2 * (nLevel & 1);
          igi2_frame.v40 = *((float *)&igi2_frame.v47 + igi2_frame.v39);
          v25 = *((_DWORD *)&v18->ptTree->tPosition.vX + (nLevel & 1));
          v18 = v18->aptChildren[v24];
          *(&igi2_frame.v47 + igi2_frame.v39) = v25;
          if ( !v18 )
            break;
          v8 = ptForest;
        }
        v8 = ptForest;
      }
      *((float *)&igi2_frame.v47 + igi2_frame.v39) = igi2_frame.v40;
      igi2_frame.p_vY1 = (int)&igi2_frame.aptNodeStack[igi2_frame.v38].vY1;
      while ( 1 )
      {
        v26 = ptNode->ptTree;
        v27 = ptNode->ptTree->tScale.vX * v8->vTreeRadius;
        igi2_frame.v45.ptTree = (struct Tree_s *)LODWORD(ptNode->ptTree->tPosition.vZ);
        p_tOrientation = &v8->tRigidTree.tModelObj.tOrientation;
        igi2_frame.v51[0] = v27 + v26->tPosition.vX;
        igi2_frame.v51[1] = v26->tPosition.vX - v27;
        v29 = v26->tScale.vY * p_tOrientation[26].tZ.vY;
        igi2_frame.v51[2] = v29 + v26->tPosition.vY;
        igi2_frame.v51[3] = v26->tPosition.vY - v29;
        igi2_frame.v45.tMinMaxZ.vX = v26->tScale.vZ * p_tOrientation[26].tZ.vZ + v26->tPosition.vZ;
        *(double *)&p_tOrientation[-3].nOps = v26->tPosition.vX + *(double *)&p_tOrientation[5].tY.vX;
        *(double *)&p_tOrientation[-2].tX.vY = ptNode->ptTree->tPosition.vY + *(double *)&p_tOrientation[5].tY.vZ;
        *(double *)&p_tOrientation[-2].tY.vX = ptNode->ptTree->tPosition.vZ + *(double *)&p_tOrientation[5].tZ.vY;
        qmemcpy(p_tOrientation, &ptNode->ptTree->tOrientation, sizeof(struct real32x9_t));
        ptForest->tRigidTree.tModelObj.tScale = ptNode->ptTree->tScale;
        if ( !Forest_IsAABBOutOfSight(ptForest, ptNode, igi2_frame.v51, (struct real32x2_t *)&igi2_frame.v45, 0.0, 0) )
        {
          nWindLODs = ptForest->nWindLODs;
          igi2_frame.v52[3] = ptForest->nID;
          vTreeRadius = ptForest->vTreeRadius;
          igi2_frame.v52[4] = nWindLODs;
          igi2_frame.v52[0] = &ptForest->tRigidTree;
          igi2_frame.v52[5] = 1;
          ptForest->tRigidTree.tModelObj.tDynCubeObj.tQObj.vRealRadius = vTreeRadius;
          igi2_frame.v52[7] = ptNode->ptTree->bLight;
          igi2_frame.v52[1] = &TransContext_tActiveTransContext;
          igi2_frame.v52[6] = eDrawMode;
          RenderMode_tActiveRenderMode.apfRenderModeMethod[Mesh3D_eDrawForestRenderModeMethod](igi2_frame.v52);
        }
        v32 = ptNode->ptTree;
        v33 = nLevel & 1;
        v34 = *((int *)&igi2_frame.v45.tMinMaxZ.vY + v33) >= 0;
        ptNode = ptNode->aptChildren[v34];
        *(&igi2_frame.v47 + 2 * v33 + v34) = *((_DWORD *)&v32->tPosition.vX + v33);
        if ( ptNode )
        {
          if ( !Forest_IsAABBOutOfSight(ptForest, ptNode, (float *)&igi2_frame.v47, &ptNode->tMinMaxZ, igi2_frame.avForestRect, 1) )
            break;
        }
        ptNode = *(struct ForestNode_s **)(igi2_frame.p_vY1 - 32);
        igi2_frame.v47 = *(_DWORD *)(igi2_frame.p_vY1 - 28);
        igi2_frame.v48 = *(float *)(igi2_frame.p_vY1 - 24);
        v35 = igi2_frame.v38 == 0;
        igi2_frame.v49 = *(float *)(igi2_frame.p_vY1 - 24 + 4);
        v36 = *(float *)(igi2_frame.p_vY1 - 24 + 8);
        igi2_frame.p_vY1 -= 24;
        result = *(struct ForestNode_s **)(igi2_frame.p_vY1 + 12);
        --igi2_frame.v38;
        igi2_frame.v50 = v36;
        nLevel = (int)result;
        if ( v35 )
          return result;
        v37 = ptNode->ptTree;
        v8 = ptForest;
        igi2_frame.v45.tMinMaxZ.vY = ptNode->ptTree->tPosition.vX - *(float *)&igi2_frame.v45.aptChildren[1];
        *(float *)&igi2_frame.v45.iMostRecentPlaneIndex = v37->tPosition.vY - igi2_frame.v46;
      }
      v8 = ptForest;
      ++nLevel;
    }
  }
  return result;
}

// source: h/2/forest.c:2479  [anchor-mhash]
void __cdecl Forest_SetUpClippingPlanes(struct Forest_s *ptForest, enum Mesh3D_DrawMode_e eDrawMode)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vFOVX; };
    struct { char igi2_o1[4]; float vFOVY; };
    struct { char igi2_o2[8]; float Real32x3_Rotate_tTemp; };
    struct { char igi2_o3[8]; float Real32x3_Rotate_tTempa; };
    struct { char igi2_o4[8]; float Real32x3_Rotate_tTempb; };
    struct { char igi2_o5[12]; float Real32x3_Rotate_tTemp_4; };
    struct { char igi2_o6[12]; float Real32x3_Rotate_tTemp_4a; };
    struct { char igi2_o7[12]; float Real32x3_Rotate_tTemp_4b; };
    struct { char igi2_o8[16]; float Real32x3_Rotate_tTemp_8; };
    struct { char igi2_o9[16]; float Real32x3_Rotate_tTemp_8a; };
    struct { char igi2_o10[16]; float Real32x3_Rotate_tTemp_8b; };
    struct { char igi2_o11[20]; float v57; };
    struct { char igi2_o12[20]; float v58; };
    struct { char igi2_o13[20]; float v59; };
    struct { char igi2_o14[20]; float v60; };
    struct { char igi2_o15[20]; float v61; };
    struct { char igi2_o16[24]; float v62; };
    struct { char igi2_o17[24]; float v63; };
    struct { char igi2_o18[24]; float v64; };
    struct { char igi2_o19[24]; float v65; };
    struct { char igi2_o20[24]; float v66; };
    struct { char igi2_o21[28]; float v67; };
    struct { char igi2_o22[28]; float v68; };
    struct { char igi2_o23[28]; float v69; };
    struct { char igi2_o24[28]; float v70; };
    struct { char igi2_o25[28]; float v71; };
    struct { char igi2_o26[32]; struct real32x9_t Real32x9_Invert_tTemp; };
    char igi2_extent[72];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // eax
  struct Clipping_ClipPlane_s *v3; // edx
  double v4; // st7
  double v5; // st6
  struct real32x3_t *v6; // ecx
  double v7; // st7
  double v8; // st6
  double v9; // st7
  struct Clipping_ClipPlane_s *v10; // ecx
  double v11; // st7
  double v12; // st6
  struct real32x3_t *v13; // ecx
  double v14; // st7
  double v15; // st6
  double v16; // st7
  long double v17; // st7
  long double v18; // st5
  long double v19; // st7
  long double v20; // st7
  int v21; // edi
  int v22; // ecx
  struct Clipping_ClipPlane_s *v23; // eax
  double v24; // st7
  double v25; // st6
  float *p_vZ; // edx
  float *p_vY; // esi
  struct real32x3_t *p_tNormal; // eax
  double v29; // st7
  double v30; // st6
  double v31; // st7
  double v32; // st7
  long double v33; // st6
  long double v34; // st5
  int v35; // edi
  int v36; // ecx
  struct Clipping_ClipPlane_s *v37; // eax
  double v38; // st7
  double v39; // st6
  float *v40; // edx
  float *v41; // esi
  struct real32x3_t *v42; // eax
  double v43; // st7
  double v44; // st6
  double v45; // st7
  float eDrawModea = *(float *)&eDrawMode; // [esp+60h] [ebp+8h] ARGSLOT

  igi2_frame.vFOVX = TransContext_tActiveTransContext.vFOVX;
  igi2_frame.vFOVY = TransContext_tActiveTransContext.vFOVY;
  Forest_tClipPlanes.nClipPlanes = 7;
  if ( dword_7BCD21C != TransContext_nActiveTransContextTimeStamp || eDrawMode )
  {
    dword_7BCD21C = TransContext_nActiveTransContextTimeStamp;
    Real32x9_InvertSafe(&g_ptDest, &TransContext_tActiveTransContext.tMatrix);
    flt_7BCD1D0 = TransContext_tActiveTransContext.tPos.vX;
    flt_7BCD1D4 = TransContext_tActiveTransContext.tPos.vY;
    igi2_frame.Real32x9_Invert_tTemp.tX.vX = g_ptDest.tX.vX;
    flt_7BCD1D8 = TransContext_tActiveTransContext.tPos.vZ;
    igi2_frame.Real32x9_Invert_tTemp.tX.vY = g_ptDest.tY.vX;
    igi2_frame.Real32x9_Invert_tTemp.tX.vZ = g_ptDest.tZ.vX;
    igi2_frame.Real32x9_Invert_tTemp.tY.vX = g_ptDest.tX.vY;
    igi2_frame.Real32x9_Invert_tTemp.tY.vY = g_ptDest.tY.vY;
    igi2_frame.Real32x9_Invert_tTemp.tY.vZ = g_ptDest.tZ.vY;
    igi2_frame.Real32x9_Invert_tTemp.tZ.vX = g_ptDest.tX.vZ;
    igi2_frame.Real32x9_Invert_tTemp.tZ.vY = g_ptDest.tY.vZ;
    igi2_frame.Real32x9_Invert_tTemp.tZ.vZ = g_ptDest.tZ.vZ;
    igi2_frame.Real32x9_Invert_tTemp.nOps = g_ptDest.nOps;
    qmemcpy(&g_ptDest, &igi2_frame.Real32x9_Invert_tTemp, sizeof(g_ptDest));
    if ( Clipping_tClipData.tClipFrustumList.nNumClipWindows <= 0 )
    {
      v16 = Direct3D_vWorldOverlayMinZ;
      Forest_tClipPlanes.ptClipPlane[4].tPos.vX = 0.0;
      Forest_tClipPlanes.ptClipPlane[4].tPos.vY = 0.0;
      Forest_tClipPlanes.ptClipPlane[4].tPos.vZ = v16;
      Forest_tClipPlanes.ptClipPlane[4].tNormal.vX = 0.0;
      Forest_tClipPlanes.ptClipPlane[4].tNormal.vY = 0.0;
      Forest_tClipPlanes.ptClipPlane[4].tNormal.vZ = -1.0;
      Forest_tClipPlanes.ptClipPlane->tPos.vX = 0.0;
      Forest_tClipPlanes.ptClipPlane->tPos.vY = 0.0;
      Forest_tClipPlanes.ptClipPlane->tPos.vZ = 0.0;
      v17 = 1.0 / sqrt(igi2_frame.vFOVX * igi2_frame.vFOVX + 1.0);
      Forest_tClipPlanes.ptClipPlane->tNormal.vX = -1.0 * v17;
      Forest_tClipPlanes.ptClipPlane->tNormal.vY = 0.0;
      v18 = -(igi2_frame.vFOVX * v17);
      Forest_tClipPlanes.ptClipPlane->tNormal.vZ = v18;
      Forest_tClipPlanes.ptClipPlane[2].tPos.vX = 0.0;
      Forest_tClipPlanes.ptClipPlane[2].tPos.vY = 0.0;
      Forest_tClipPlanes.ptClipPlane[2].tPos.vZ = 0.0;
      Forest_tClipPlanes.ptClipPlane[2].tNormal.vX = v17;
      Forest_tClipPlanes.ptClipPlane[2].tNormal.vY = 0.0;
      Forest_tClipPlanes.ptClipPlane[2].tNormal.vZ = v18;
      Forest_tClipPlanes.ptClipPlane[3].tPos.vX = 0.0;
      Forest_tClipPlanes.ptClipPlane[3].tPos.vY = 0.0;
      Forest_tClipPlanes.ptClipPlane[3].tPos.vZ = 0.0;
      Forest_tClipPlanes.ptClipPlane[3].tNormal.vX = 0.0;
      v19 = 1.0 / sqrt(igi2_frame.vFOVY * igi2_frame.vFOVY + 1.0);
      Forest_tClipPlanes.ptClipPlane[3].tNormal.vY = -1.0 * v19;
      v20 = -(v19 * igi2_frame.vFOVY);
      Forest_tClipPlanes.ptClipPlane[3].tNormal.vZ = v20;
      Forest_tClipPlanes.ptClipPlane[1].tPos.vX = 0.0;
      Forest_tClipPlanes.ptClipPlane[1].tPos.vY = 0.0;
      Forest_tClipPlanes.ptClipPlane[1].tPos.vZ = 0.0;
      Forest_tClipPlanes.ptClipPlane[1].tNormal.vX = 0.0;
      v21 = 0;
      dword_7BCD1F0 = 0;
      Forest_tClipPlanes.ptClipPlane[1].tNormal.vY = 1.0 / sqrt(igi2_frame.vFOVY * igi2_frame.vFOVX + 1.0);
      Forest_tClipPlanes.ptClipPlane[1].tNormal.vZ = v20;
      if ( Forest_tClipPlanes.nClipPlanes - 2 > 0 )
      {
        v22 = 0;
        do
        {
          v23 = &Forest_tClipPlanes.ptClipPlane[v22];
          igi2_frame.v60 = g_ptDest.tX.vX * Forest_tClipPlanes.ptClipPlane[v22].tPos.vX
              + g_ptDest.tX.vZ * Forest_tClipPlanes.ptClipPlane[v22].tPos.vZ
              + g_ptDest.tX.vY * Forest_tClipPlanes.ptClipPlane[v22].tPos.vY;
          igi2_frame.v65 = g_ptDest.tY.vX * Forest_tClipPlanes.ptClipPlane[v22].tPos.vX
              + g_ptDest.tY.vZ * Forest_tClipPlanes.ptClipPlane[v22].tPos.vZ
              + g_ptDest.tY.vY * Forest_tClipPlanes.ptClipPlane[v22].tPos.vY;
          v24 = g_ptDest.tZ.vX * Forest_tClipPlanes.ptClipPlane[v22].tPos.vX
              + g_ptDest.tZ.vZ * Forest_tClipPlanes.ptClipPlane[v22].tPos.vZ;
          v25 = g_ptDest.tZ.vY * Forest_tClipPlanes.ptClipPlane[v22].tPos.vY;
          v23->tPos.vX = igi2_frame.v60;
          v23->tPos.vY = igi2_frame.v65;
          igi2_frame.v70 = v24 + v25;
          v23->tPos.vZ = igi2_frame.v70;
          p_vZ = &Forest_tClipPlanes.ptClipPlane[v22].tNormal.vZ;
          p_vY = &Forest_tClipPlanes.ptClipPlane[v22].tNormal.vY;
          p_tNormal = &Forest_tClipPlanes.ptClipPlane[v22].tNormal;
          igi2_frame.Real32x3_Rotate_tTempa = g_ptDest.tX.vZ * *p_vZ + g_ptDest.tX.vX * p_tNormal->vX + g_ptDest.tX.vY * *p_vY;
          igi2_frame.Real32x3_Rotate_tTemp_4a = g_ptDest.tY.vZ * *p_vZ + g_ptDest.tY.vX * p_tNormal->vX + g_ptDest.tY.vY * *p_vY;
          v29 = g_ptDest.tZ.vZ * *p_vZ + g_ptDest.tZ.vX * p_tNormal->vX;
          v30 = g_ptDest.tZ.vY * *p_vY;
          p_tNormal->vX = igi2_frame.Real32x3_Rotate_tTempa;
          p_tNormal->vY = igi2_frame.Real32x3_Rotate_tTemp_4a;
          igi2_frame.Real32x3_Rotate_tTemp_8a = v29 + v30;
          p_tNormal->vZ = igi2_frame.Real32x3_Rotate_tTemp_8a;
          Forest_tClipPlanes.ptClipPlane[v22].tPos.vX = flt_7BCD1D0 + Forest_tClipPlanes.ptClipPlane[v22].tPos.vX;
          Forest_tClipPlanes.ptClipPlane[v22].tPos.vY = flt_7BCD1D4 + Forest_tClipPlanes.ptClipPlane[v22].tPos.vY;
          ++v21;
          v31 = flt_7BCD1D8 + Forest_tClipPlanes.ptClipPlane[v22++].tPos.vZ;
          Forest_tClipPlanes.ptClipPlane[v22 - 1].tPos.vZ = v31;
        }
        while ( v21 < Forest_tClipPlanes.nClipPlanes - 2 );
        dword_7BCD1F0 = v21;
      }
    }
    else
    {
      v2 = 0;
      dword_7BCD1F0 = 4;
      do
      {
        v3 = &Forest_tClipPlanes.ptClipPlane[v2 / 0x18u];
        igi2_frame.Real32x3_Rotate_tTemp = g_ptDest.tX.vY * *(float *)(v2 + 129876368)
                              + g_ptDest.tX.vZ * *(float *)(v2 + 129876372)
                              + g_ptDest.tX.vX * *(float *)(v2 + 129876364);
        igi2_frame.Real32x3_Rotate_tTemp_4 = g_ptDest.tY.vY * *(float *)(v2 + 129876368)
                                + g_ptDest.tY.vZ * *(float *)(v2 + 129876372)
                                + g_ptDest.tY.vX * *(float *)(v2 + 129876364);
        v4 = g_ptDest.tZ.vY * *(float *)(v2 + 129876368) + g_ptDest.tZ.vZ * *(float *)(v2 + 129876372);
        v5 = g_ptDest.tZ.vX * *(float *)(v2 + 129876364);
        v3->tPos.vX = igi2_frame.Real32x3_Rotate_tTemp;
        v3->tPos.vY = igi2_frame.Real32x3_Rotate_tTemp_4;
        igi2_frame.Real32x3_Rotate_tTemp_8 = v4 + v5;
        v3->tPos.vZ = igi2_frame.Real32x3_Rotate_tTemp_8;
        v6 = &Forest_tClipPlanes.ptClipPlane[v2 / 0x18u].tNormal;
        igi2_frame.v57 = g_ptDest.tX.vX * *(float *)(v2 + 129876376)
            + g_ptDest.tX.vZ * *(float *)(v2 + 129876384)
            + g_ptDest.tX.vY * *(float *)(v2 + 129876380);
        igi2_frame.v62 = g_ptDest.tY.vX * *(float *)(v2 + 129876376)
            + g_ptDest.tY.vZ * *(float *)(v2 + 129876384)
            + g_ptDest.tY.vY * *(float *)(v2 + 129876380);
        v7 = g_ptDest.tZ.vX * *(float *)(v2 + 129876376) + g_ptDest.tZ.vZ * *(float *)(v2 + 129876384);
        v8 = g_ptDest.tZ.vY * *(float *)(v2 + 129876380);
        v6->vX = igi2_frame.v57;
        v6->vY = igi2_frame.v62;
        igi2_frame.v67 = v7 + v8;
        v6->vZ = igi2_frame.v67;
        Forest_tClipPlanes.ptClipPlane[v2 / 0x18u].tPos.vX = flt_7BCD1D0 + *(float *)(v2 + 129876364);
        Forest_tClipPlanes.ptClipPlane[v2 / 0x18u].tPos.vY = flt_7BCD1D4 + *(float *)(v2 + 129876368);
        Forest_tClipPlanes.ptClipPlane[v2 / 0x18u].tPos.vZ = flt_7BCD1D8 + *(float *)(v2 + 129876372);
        v2 += 24;
      }
      while ( v2 < 96 );
      v9 = Direct3D_vWorldOverlayMinZ;
      Forest_tClipPlanes.ptClipPlane[4].tPos.vX = 0.0;
      Forest_tClipPlanes.ptClipPlane[4].tPos.vY = 0.0;
      Forest_tClipPlanes.ptClipPlane[4].tPos.vZ = v9;
      Forest_tClipPlanes.ptClipPlane[4].tNormal.vX = 0.0;
      Forest_tClipPlanes.ptClipPlane[4].tNormal.vY = 0.0;
      Forest_tClipPlanes.ptClipPlane[4].tNormal.vZ = -1.0;
      v10 = Forest_tClipPlanes.ptClipPlane + 4;
      igi2_frame.v58 = g_ptDest.tX.vZ * Forest_tClipPlanes.ptClipPlane[4].tPos.vZ
          + g_ptDest.tX.vX * Forest_tClipPlanes.ptClipPlane[4].tPos.vX
          + g_ptDest.tX.vY * Forest_tClipPlanes.ptClipPlane[4].tPos.vY;
      igi2_frame.v63 = g_ptDest.tY.vZ * Forest_tClipPlanes.ptClipPlane[4].tPos.vZ
          + g_ptDest.tY.vX * Forest_tClipPlanes.ptClipPlane[4].tPos.vX
          + g_ptDest.tY.vY * Forest_tClipPlanes.ptClipPlane[4].tPos.vY;
      v11 = g_ptDest.tZ.vZ * Forest_tClipPlanes.ptClipPlane[4].tPos.vZ
          + g_ptDest.tZ.vX * Forest_tClipPlanes.ptClipPlane[4].tPos.vX;
      v12 = g_ptDest.tZ.vY * Forest_tClipPlanes.ptClipPlane[4].tPos.vY;
      Forest_tClipPlanes.ptClipPlane[4].tPos.vX = igi2_frame.v58;
      v10->tPos.vY = igi2_frame.v63;
      igi2_frame.v68 = v11 + v12;
      v10->tPos.vZ = igi2_frame.v68;
      v13 = &Forest_tClipPlanes.ptClipPlane[4].tNormal;
      igi2_frame.v59 = g_ptDest.tX.vY * Forest_tClipPlanes.ptClipPlane[4].tNormal.vY
          + g_ptDest.tX.vZ * Forest_tClipPlanes.ptClipPlane[4].tNormal.vZ
          + g_ptDest.tX.vX * Forest_tClipPlanes.ptClipPlane[4].tNormal.vX;
      igi2_frame.v64 = g_ptDest.tY.vY * Forest_tClipPlanes.ptClipPlane[4].tNormal.vY
          + g_ptDest.tY.vZ * Forest_tClipPlanes.ptClipPlane[4].tNormal.vZ
          + g_ptDest.tY.vX * Forest_tClipPlanes.ptClipPlane[4].tNormal.vX;
      v14 = g_ptDest.tZ.vY * Forest_tClipPlanes.ptClipPlane[4].tNormal.vY
          + g_ptDest.tZ.vZ * Forest_tClipPlanes.ptClipPlane[4].tNormal.vZ;
      v15 = g_ptDest.tZ.vX * Forest_tClipPlanes.ptClipPlane[4].tNormal.vX;
      Forest_tClipPlanes.ptClipPlane[4].tNormal.vX = igi2_frame.v59;
      v13->vY = igi2_frame.v64;
      igi2_frame.v69 = v14 + v15;
      v13->vZ = igi2_frame.v69;
      Forest_tClipPlanes.ptClipPlane[4].tPos.vX = flt_7BCD1D0 + Forest_tClipPlanes.ptClipPlane[4].tPos.vX;
      Forest_tClipPlanes.ptClipPlane[4].tPos.vY = flt_7BCD1D4 + Forest_tClipPlanes.ptClipPlane[4].tPos.vY;
      Forest_tClipPlanes.ptClipPlane[4].tPos.vZ = flt_7BCD1D8 + Forest_tClipPlanes.ptClipPlane[4].tPos.vZ;
    }
  }
  if ( eDrawMode == MESH3D_DRAWMODE_LIGHTMAP )
  {
    Forest_tClipPlanes.nClipPlanes = 5;
  }
  else
  {
    v32 = 1.0 / igi2_frame.vFOVX;
    Forest_tClipPlanes.ptClipPlane[5].tPos.vX = 0.0;
    Forest_tClipPlanes.ptClipPlane[5].tPos.vY = 0.0;
    Forest_tClipPlanes.ptClipPlane[5].tPos.vZ = v32 * ptForest->vViewDistance;
    v33 = 1.0 / sqrt(igi2_frame.vFOVX * igi2_frame.vFOVX + 1.0);
    eDrawModea = sqrt((1.0 - v33) * 0.5);
    Forest_tClipPlanes.ptClipPlane[5].tNormal.vX = eDrawModea;
    Forest_tClipPlanes.ptClipPlane[5].tNormal.vY = 0.0;
    v34 = sqrt((v33 + 1.0) * 0.5);
    Forest_tClipPlanes.ptClipPlane[5].tNormal.vZ = v34;
    Forest_tClipPlanes.ptClipPlane[6].tPos.vX = 0.0;
    Forest_tClipPlanes.ptClipPlane[6].tPos.vY = 0.0;
    Forest_tClipPlanes.ptClipPlane[6].tPos.vZ = v32 * ptForest->vViewDistance;
    Forest_tClipPlanes.ptClipPlane[6].tNormal.vX = -eDrawModea;
    Forest_tClipPlanes.ptClipPlane[6].tNormal.vY = 0.0;
    Forest_tClipPlanes.ptClipPlane[6].tNormal.vZ = v34;
    v35 = Forest_tClipPlanes.nClipPlanes - 2;
    dword_7BCD1F0 = Forest_tClipPlanes.nClipPlanes - 2;
    if ( Forest_tClipPlanes.nClipPlanes - 2 - Forest_tClipPlanes.nClipPlanes < 0 != Forest_tClipPlanes.nClipPlanes - 2 >= Forest_tClipPlanes.nClipPlanes )
    {
      v36 = v35;
      do
      {
        v37 = &Forest_tClipPlanes.ptClipPlane[v36];
        igi2_frame.v61 = g_ptDest.tX.vX * Forest_tClipPlanes.ptClipPlane[v36].tPos.vX
            + g_ptDest.tX.vZ * Forest_tClipPlanes.ptClipPlane[v36].tPos.vZ
            + g_ptDest.tX.vY * Forest_tClipPlanes.ptClipPlane[v36].tPos.vY;
        igi2_frame.v66 = g_ptDest.tY.vX * Forest_tClipPlanes.ptClipPlane[v36].tPos.vX
            + g_ptDest.tY.vZ * Forest_tClipPlanes.ptClipPlane[v36].tPos.vZ
            + g_ptDest.tY.vY * Forest_tClipPlanes.ptClipPlane[v36].tPos.vY;
        v38 = g_ptDest.tZ.vX * Forest_tClipPlanes.ptClipPlane[v36].tPos.vX
            + g_ptDest.tZ.vZ * Forest_tClipPlanes.ptClipPlane[v36].tPos.vZ;
        v39 = g_ptDest.tZ.vY * Forest_tClipPlanes.ptClipPlane[v36].tPos.vY;
        v37->tPos.vX = igi2_frame.v61;
        v37->tPos.vY = igi2_frame.v66;
        igi2_frame.v71 = v38 + v39;
        v37->tPos.vZ = igi2_frame.v71;
        v40 = &Forest_tClipPlanes.ptClipPlane[v36].tNormal.vZ;
        v41 = &Forest_tClipPlanes.ptClipPlane[v36].tNormal.vY;
        v42 = &Forest_tClipPlanes.ptClipPlane[v36].tNormal;
        igi2_frame.Real32x3_Rotate_tTempb = g_ptDest.tX.vZ * *v40 + g_ptDest.tX.vX * v42->vX + g_ptDest.tX.vY * *v41;
        igi2_frame.Real32x3_Rotate_tTemp_4b = g_ptDest.tY.vZ * *v40 + g_ptDest.tY.vX * v42->vX + g_ptDest.tY.vY * *v41;
        v43 = g_ptDest.tZ.vZ * *v40 + g_ptDest.tZ.vX * v42->vX;
        v44 = g_ptDest.tZ.vY * *v41;
        v42->vX = igi2_frame.Real32x3_Rotate_tTempb;
        v42->vY = igi2_frame.Real32x3_Rotate_tTemp_4b;
        igi2_frame.Real32x3_Rotate_tTemp_8b = v43 + v44;
        v42->vZ = igi2_frame.Real32x3_Rotate_tTemp_8b;
        Forest_tClipPlanes.ptClipPlane[v36].tPos.vX = flt_7BCD1D0 + Forest_tClipPlanes.ptClipPlane[v36].tPos.vX;
        Forest_tClipPlanes.ptClipPlane[v36].tPos.vY = flt_7BCD1D4 + Forest_tClipPlanes.ptClipPlane[v36].tPos.vY;
        ++v35;
        v45 = flt_7BCD1D8 + Forest_tClipPlanes.ptClipPlane[v36++].tPos.vZ;
        Forest_tClipPlanes.ptClipPlane[v36 - 1].tPos.vZ = v45;
      }
      while ( v35 < Forest_tClipPlanes.nClipPlanes );
      dword_7BCD1F0 = v35;
    }
  }
}

// source: h/2/forest.c:2604  [anchor-mhash]
void __cdecl Forest_DrawTrees(struct QTask_s *ptQTask, enum Mesh3D_DrawMode_e eDrawMode)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vRectY1; };
    struct { char igi2_o1[4]; float nLevel; };
    struct { char igi2_o2[8]; float tViewVector; };
    struct { char igi2_o3[12]; float tViewVector_4; };
    struct { char igi2_o4[20]; float tViewPoint; };
    struct { char igi2_o5[24]; float tViewPoint_4; };
    struct { char igi2_o6[32]; struct DrawForestContext_t tContext; };
    char igi2_extent[64];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  BOOL v2; // edi
  long double v3; // st7
  double v4; // st6
  struct QTask_s *ptNext; // ecx
  struct QReference_s *ptHead; // edx
  struct QTask_s *v7; // eax

  igi2_frame.tViewPoint = TransContext_tActiveTransContext.tPos.vX;
  igi2_frame.tViewPoint_4 = TransContext_tActiveTransContext.tPos.vY;
  v2 = 1;
  igi2_frame.tViewVector = TransContext_tActiveTransContext.tMatrix.tZ.vX;
  igi2_frame.tViewVector_4 = TransContext_tActiveTransContext.tMatrix.tZ.vY;
  Forest_SetUpClippingPlanes((struct Forest_s *)ptQTask, eDrawMode);
  v3 = TransContext_tActiveTransContext.vFOVX
     / sqrt(TransContext_tActiveTransContext.vFOVX * TransContext_tActiveTransContext.vFOVX + 1.0);
  v4 = *(float *)&ptQTask[36].ptParent * 4096.0 * 0.5;
  if ( v4 + *(double *)&ptQTask[16].tQTaskChildren.ptTail < igi2_frame.tViewPoint )
    v2 = igi2_frame.tViewVector <= v3;
  if ( *(double *)&ptQTask[16].tQTaskChildren.ptTail - v4 > igi2_frame.tViewPoint && -igi2_frame.tViewVector > v3 )
    v2 = 0;
  if ( v4 + *(double *)&ptQTask[16].tQTaskRefList.ptMiddle < igi2_frame.tViewPoint_4 && igi2_frame.tViewVector_4 > v3 )
    v2 = 0;
  if ( *(double *)&ptQTask[16].tQTaskRefList.ptMiddle - v4 <= igi2_frame.tViewPoint_4 || -igi2_frame.tViewVector_4 <= v3 )
  {
    if ( v2 )
    {
      ptNext = ptQTask[38].ptNext;
      ptHead = ptQTask[38].tQTaskRefList.ptHead;
      igi2_frame.tContext.nTreesNum = (int)ptQTask[38].tQTaskChildren.ptHead;
      igi2_frame.tContext.nForestID = (int)ptNext;
      igi2_frame.tContext.ptRigidDynCubeObj = (struct RigidDynCubeObj_t *)&ptQTask[8];
      igi2_frame.tContext.nWindLODs = (int)ptHead;
      igi2_frame.tContext.ptTransContext = &TransContext_tActiveTransContext;
      igi2_frame.tContext.eAction = FOREST_INIT;
      igi2_frame.tContext.eDrawMode = eDrawMode;
      RenderMode_tActiveRenderMode.apfRenderModeMethod[Mesh3D_eDrawForestRenderModeMethod](&igi2_frame.tContext);
      igi2_frame.vRectY1 = *(float *)&ptQTask[36].ptParent * 2048.0;
      igi2_frame.nLevel = *(float *)&ptQTask[36].ptParent * -2048.0;
      Forest_DrawTrees1_Optimized(
        (struct Forest_s *)ptQTask,
        eDrawMode,
        (struct ForestNode_s *)ptQTask[16].ptNext,
        0,
        igi2_frame.nLevel,
        igi2_frame.nLevel,
        igi2_frame.vRectY1,
        igi2_frame.vRectY1);
      v7 = ptQTask[38].tQTaskChildren.ptHead;
      igi2_frame.tContext.nForestID = (int)ptQTask[38].ptNext;
      igi2_frame.tContext.eAction = FOREST_DRAW_FOREST;
      igi2_frame.tContext.nTreesNum = (int)v7;
      igi2_frame.tContext.ptRigidDynCubeObj = (struct RigidDynCubeObj_t *)&ptQTask[8];
      igi2_frame.tContext.ptTransContext = &TransContext_tActiveTransContext;
      igi2_frame.tContext.eDrawMode = eDrawMode;
      RenderMode_tActiveRenderMode.apfRenderModeMethod[Mesh3D_eDrawForestRenderModeMethod](&igi2_frame.tContext);
    }
  }
}

// source: h/2/forest.c:2697  [anchor-mhash]
void __cdecl Forest_DrawLightmapHandler(struct QTask_s *ptQTask, void *pxContext)
{
  if ( !ptQTask[38].tQTaskRefList.ptMiddle
    && (GlobalLightQTask_ptGlobalLight->isRadiosityTerrainShadows || *((_DWORD *)pxContext + 4)) )
  {
    if ( *((_DWORD *)pxContext + 2) )
    {
      qmemcpy(&unk_7BCD150, (char *)pxContext + 24, 0x18u);
      qmemcpy(&unk_7BCD128, (char *)pxContext + 48, 0x28u);
      flt_7BCD16C = *((float *)pxContext + 23);
      flt_7BCD168 = flt_7BCD16C;
      Forest_ptTransContext = (struct TransContext_s *)&unk_7BCD128;
      Forest_DrawTrees(ptQTask, MESH3D_DRAWMODE_LIGHTMAP);
    }
  }
}

// source: h/2/forest.c:2732  [anchor-mhash]
void __cdecl Forest_EnumerateLightmapHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QObjectVector_s *v2; // esi
  unsigned int nAllocated; // eax
  struct QTask_s **v4; // ecx

  if ( !ptQTask[38].tQTaskRefList.ptMiddle && (ptQTask[2].tQTaskChildren.ptHead || *((_DWORD *)pxContext + 1)) )
  {
    v2 = *(struct QObjectVector_s **)pxContext;
    if ( *(_DWORD *)(*(_DWORD *)pxContext + 36) == *(_DWORD *)(*(_DWORD *)pxContext + 40) )
      QObjectVector_Realloc(v2, v2->nReallocSize);
    nAllocated = v2->nAllocated;
    v4 = (struct QTask_s **)v2->papxElement[nAllocated];
    v2->nAllocated = nAllocated + 1;
    *v4 = ptQTask;
  }
}

// source: h/2/forest.c:2958  [anchor-mhash]
void __cdecl Forest_EnterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptHead; // eax

  if ( QCube_isDrawOutside )
  {
    ptHead = ptQTask[38].tQTaskChildren.ptHead;
    Forest_ptTransContext = &TransContext_tActiveTransContext;
    if ( (int)ptHead > 0 )
      Forest_DrawTrees(ptQTask, MESH3D_DRAWMODE_NORMAL);
  }
}

// source: h/2/forest.c:3045  [anchor-mhash]
void __cdecl Forest_DrawEnvmapHandler(struct QTask_s *ptQTask, void *pxContext)
{
  Forest_DrawTrees(ptQTask, MESH3D_DRAWMODE_ENVMAP);
}

// source: h/2/forest.c:3058  [size]
void __cdecl Forest_EnumerateEnvmapHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QObjectVector_s *v2; // esi
  unsigned int nAllocated; // eax
  struct QTask_s **v4; // ecx

  if ( (*((_BYTE *)pxContext + 8) & 8) != 0 )
  {
    v2 = *(struct QObjectVector_s **)pxContext;
    if ( *(_DWORD *)(*(_DWORD *)pxContext + 36) == *(_DWORD *)(*(_DWORD *)pxContext + 40) )
      QObjectVector_Realloc(v2, v2->nReallocSize);
    nAllocated = v2->nAllocated;
    v4 = (struct QTask_s **)v2->papxElement[nAllocated];
    v2->nAllocated = nAllocated + 1;
    *v4 = ptQTask;
    v4[1] = (struct QTask_s *)3;
  }
}

// source: h/2/forest.c:3086  [anchor-caller]
void __cdecl Forest_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  double v3; // st7
  struct ModelObj_s *v4; // esi
  struct LODVirModel_s *LODVirModelExistsFn; // eax
  struct LODVirModel_s *v6; // ebp
  struct Mesh3D_Mesh_t *ptMesh; // edi
  _DWORD *pxRenderMesh; // eax
  int v9; // ecx
  int v10; // eax
  float *v11; // ecx
  int v12; // edx
  double v13; // st3
  double v14; // st4
  int v15; // ecx
  struct QReference_s *v16; // eax
  struct QTask_s *ptHead; // eax
  int v18; // esi
  struct QTask_s *v19; // eax
  int v20; // esi
  struct QTask_s *v21; // eax
  int v22; // esi
  double v23; // st7
  struct QTask_s *v24; // eax
  int v25; // edx
  int v26; // ecx
  unsigned int v27; // esi
  unsigned int v28; // esi
  struct QTask_s *ptParent; // edx
  int v30; // eax
  _DWORD *v31; // edx
  int v32; // ecx
  float ptDynCubeObj; // [esp+0h] [ebp-38h]
  float vMaxZ; // [esp+18h] [ebp-20h]
  float vMinZ; // [esp+1Ch] [ebp-1Ch]
  struct LODVirModel_s *v36; // [esp+24h] [ebp-14h]
  float tOffset; // [esp+28h] [ebp-10h]
  float tOffset_4; // [esp+2Ch] [ebp-Ch]
  float ptQTaska = *(float *)&ptQTask; // [esp+3Ch] [ebp+4h] ARGSLOT

  if ( !Forest_isGetNextZEvaluateEventHandlerLinked )
  {
    QTask_LinkQTaskEventHandlerFn(
      Forest_eQTaskType,
      GameFunctions_eGetNextZEvaluateQTaskEvent,
      Forest_GetNextZEvaluateHandler);
    Forest_isGetNextZEvaluateEventHandlerLinked = 1;
  }
  ptDynCubeObj = *(float *)&ptQTask[36].ptParent * 4096.0;
  World_MoveDynCubeObjRadius(
    (struct World_s *)ptQTask[16].tQTaskChildren.ptMiddle,
    (struct DynCubeObj_s *)ptQTask,
    (struct real64x3_t *)&ptQTask[16].tQTaskChildren.ptTail,
    ptDynCubeObj);
  if ( ptQTask[39].ptPrev )
  {
    v3 = *(float *)&ptQTask[37].tQTaskRefList.ptTail;
    ptQTask[37].tQTaskRefList.ptMiddle = ptQTask[37].tQTaskRefList.ptTail;
    *(float *)&ptQTask[37].tQTaskRefList.ptHead = v3;
  }
  v4 = (struct ModelObj_s *)&ptQTask[8];
  vMinZ = 3.4028234663852886e+38;
  vMaxZ = -3.4028234663852886e+38;
  ptQTaska = 0.0;
  LODVirModelExistsFn = MTP_GetLODVirModelExistsFn((char *)&ptQTask[17].tQTaskRefList.ptMiddle);
  v6 = LODVirModelExistsFn;
  v36 = LODVirModelExistsFn;
  if ( LODVirModelExistsFn )
  {
    ptMesh = LODVirModelExistsFn->aptVirModel[0]->ptModel->ptMesh;
    if ( ptMesh->eRenderMeshType == MESH3D_RENDERMESHTYPE_DIRECT3D_RIGID )
    {
      if ( LODVirModelExistsFn != *(struct LODVirModel_s **)&ptQTask[10].eQTaskType )
      {
        ModelObj_SetLODVirModel(v4, LODVirModelExistsFn, false);
        ptQTask[15].tQTaskRefList.ptHead = nullptr;
        ptQTask[15].tQTaskRefList.ptMiddle = nullptr;
        ptQTask[15].tQTaskRefList.ptTail = nullptr;
        ptQTask[15].ptParent = nullptr;
        *(_DWORD *)&ptQTask[15].eQTaskType = 0;
      }
      pxRenderMesh = ptMesh->pxRenderMesh;
      v9 = pxRenderMesh[4];
      v10 = pxRenderMesh[3];
      if ( v10 > 0 )
      {
        v11 = (float *)(v9 + 8);
        v12 = v10;
        do
        {
          tOffset = *(v11 - 2) - ptMesh->tRenderMeshSphere.tPos.vX;
          tOffset_4 = *(v11 - 1) - ptMesh->tRenderMeshSphere.tPos.vY;
          v13 = *v11 - ptMesh->tRenderMeshSphere.tPos.vZ;
          v14 = tOffset * tOffset + tOffset_4 * tOffset_4 + v13 * v13;
          if ( v14 > ptQTaska )
            ptQTaska = v14;
          if ( *v11 > (double)vMaxZ )
            vMaxZ = *v11;
          if ( *v11 < (double)vMinZ )
            vMinZ = *v11;
          v11 += 8;
          --v12;
        }
        while ( v12 );
      }
      *(float *)&ptQTask[37].ptParent = sqrt(ptQTaska);
      *(float *)&ptQTask[37].eQTaskType = vMaxZ - vMinZ;
    }
    if ( !ptQTask[39].tQTaskChildren.ptTail )
      goto LABEL_35;
    v15 = 0;
    while ( 1 )
    {
      v16 = Level_atLevelQTaskID[v15];
      if ( v16 )
      {
        if ( v16->pxObject == ptQTask )
          break;
      }
      if ( ++v15 >= 4096 )
      {
        v15 = -1;
        break;
      }
    }
    ptQTask[38].ptNext = (struct QTask_s *)v15;
    sprintf((char *const)&ptQTask[30].tQTaskChildren.ptMiddle + 2, "MISSION:forest_%d.dat", v15);
    if ( File_Exists((char *)&ptQTask[30].tQTaskChildren.ptMiddle + 2) )
    {
      ptHead = ptQTask[16].tQTaskChildren.ptHead;
      if ( ptHead )
      {
        v18 = *(_DWORD *)((unsigned int)&ptHead[-1].eQTaskType & 0xFFFFFFFC);
        --Mem_nCurrentAllocations;
        Node_Remove((_DWORD **)v18);
        memset(*(void **)(v18 + 8), 0xCDu, *(_DWORD *)(v18 + 16));
        free((void *)v18);
        ptQTask[16].tQTaskChildren.ptHead = nullptr;
      }
      ptQTask[16].tQTaskChildren.ptHead = (struct QTask_s *)Mem_AllocFn(68 * (int)ptQTask[38].tQTaskChildren.ptHead, 4);
      Forest_LoadData((struct Forest_s *)ptQTask, (char *)&ptQTask[30].tQTaskChildren.ptMiddle + 2);
      Forest_CreateBSPTree((struct Forest_s *)ptQTask);
      Forest_GenerateHeightDataRecursively((struct Forest_s *)ptQTask, (struct ForestNode_s *)ptQTask[16].ptNext);
      ptQTask[39].tQTaskChildren.ptHead = nullptr;
      ptQTask[38].tQTaskRefList.ptTail = nullptr;
    }
    else
    {
      if ( !ptQTask[39].tQTaskRefList.ptHead )
      {
LABEL_34:
        v6 = v36;
        ptQTask[39].tQTaskChildren.ptTail = nullptr;
LABEL_35:
        if ( ptQTask[39].tQTaskChildren.ptHead )
        {
          v21 = ptQTask[16].tQTaskChildren.ptHead;
          if ( v21 )
          {
            v22 = *(_DWORD *)((unsigned int)&v21[-1].eQTaskType & 0xFFFFFFFC);
            --Mem_nCurrentAllocations;
            Node_Remove((_DWORD **)v22);
            memset(*(void **)(v22 + 8), 0xCDu, *(_DWORD *)(v22 + 16));
            free((void *)v22);
            ptQTask[16].tQTaskChildren.ptHead = nullptr;
          }
          Forest_DeleteBSPTree((struct ForestNode_s *)ptQTask[16].ptNext);
          v23 = *(float *)&ptQTask[37].ptPrev * *(float *)&ptQTask[36].ptParent;
          ptQTask[16].ptNext = nullptr;
          v24 = (struct QTask_s *)(__int64)(v23 * *(float *)&ptQTask[36].ptParent);
          ptQTask[38].tQTaskChildren.ptHead = v24;
          ptQTask[16].tQTaskChildren.ptHead = (struct QTask_s *)Mem_AllocFn(68 * (_DWORD)v24, 4);
          v25 = 0;
          if ( (int)ptQTask[38].tQTaskChildren.ptHead > 0 )
          {
            v26 = 0;
            do
            {
              v27 = (Forest_tRandomState.anRandom[0] >> 7) ^ Forest_tRandomState.anRandom[2];
              Forest_tRandomState.anRandom[0] += v27 ^ Forest_tRandomState.anRandom[1];
              Forest_tRandomState.anRandom[2] = v27;
              Forest_tRandomState.anRandom[1] ^= v27;
              *(float *)((char *)&ptQTask[16].tQTaskChildren.ptHead->ptNext + v26) = ((double)LOWORD(Forest_tRandomState.anRandom[0])
                                                                                    * 0.0000152587890625
                                                                                    - 0.5)
                                                                                   * *(float *)&ptQTask[36].ptParent
                                                                                   * 4096.0;
              v28 = (Forest_tRandomState.anRandom[0] >> 7) ^ Forest_tRandomState.anRandom[2];
              Forest_tRandomState.anRandom[0] += v28 ^ Forest_tRandomState.anRandom[1];
              Forest_tRandomState.anRandom[2] = v28;
              Forest_tRandomState.anRandom[1] ^= v28;
              ++v25;
              v26 += 68;
              *(float *)((char *)&ptQTask[16].tQTaskChildren.ptHead[-1] + v26 - 24) = ((double)LOWORD(Forest_tRandomState.anRandom[0])
                                                                                     * 0.0000152587890625
                                                                                     - 0.5)
                                                                                    * *(float *)&ptQTask[36].ptParent
                                                                                    * 4096.0;
              *(_DWORD *)((char *)&ptQTask[16].tQTaskChildren.ptHead[-1] + v26 - 20) = 1241120768;
            }
            while ( v25 < (int)ptQTask[38].tQTaskChildren.ptHead );
            v6 = v36;
          }
          Forest_CreateBSPTree((struct Forest_s *)ptQTask);
          if ( ptQTask[38].tQTaskChildren.ptHead && ptQTask[16].tQTaskChildren.ptHead )
            Forest_GenerateHeightDataRecursively((struct Forest_s *)ptQTask, (struct ForestNode_s *)ptQTask[16].ptNext);
          ptParent = ptQTask[36].ptParent;
          ptQTask[39].tQTaskChildren.ptHead = nullptr;
          ptQTask[38].tQTaskRefList.ptTail = nullptr;
          *(_DWORD *)&ptQTask[36].eQTaskType = ptParent;
        }
        if ( ptQTask[38].tQTaskRefList.ptTail )
        {
          if ( ptQTask[38].tQTaskChildren.ptHead && ptQTask[16].tQTaskChildren.ptHead )
            Forest_GenerateHeightDataRecursively((struct Forest_s *)ptQTask, (struct ForestNode_s *)ptQTask[16].ptNext);
          ptQTask[38].tQTaskRefList.ptTail = nullptr;
        }
        if ( ptQTask[38].tQTaskRefList.ptMiddle )
          Forest_LightForest((struct Forest_s *)ptQTask, 1);
        if ( ptQTask[16].tQTaskChildren.ptHead && *(float *)&ptQTask[36].ptParent != *(float *)&ptQTask[36].eQTaskType )
        {
          Forest_CreateBSPTree((struct Forest_s *)ptQTask);
          *(_DWORD *)&ptQTask[36].eQTaskType = ptQTask[36].ptParent;
        }
        *(float *)&ptQTask[37].tQTaskChildren.ptHead = *(float *)&ptQTask[37].tQTaskChildren.ptMiddle * 4096.0;
        v30 = v6->nLOD - 1;
        if ( v30 < 4 )
        {
          v31 = (struct VirModel_s **)&v6->avLODDistance[v30];
          v32 = 4 - v30;
          do
          {
            *v31++ = LODWORD(v6->avLODDistance[4]);
            --v32;
          }
          while ( v32 );
        }
        return;
      }
      v19 = ptQTask[16].tQTaskChildren.ptHead;
      if ( v19 )
      {
        v20 = *(_DWORD *)((unsigned int)&v19[-1].eQTaskType & 0xFFFFFFFC);
        --Mem_nCurrentAllocations;
        Node_Remove((_DWORD **)v20);
        memset(*(void **)(v20 + 8), 0xCDu, *(_DWORD *)(v20 + 16));
        free((void *)v20);
        ptQTask[16].tQTaskChildren.ptHead = nullptr;
      }
      ptQTask[16].tQTaskChildren.ptHead = (struct QTask_s *)Mem_AllocFn(68 * (int)ptQTask[38].tQTaskChildren.ptHead, 4);
      Forest_LoadData((struct Forest_s *)ptQTask, &ptQTask[23].isInMemPool + 1);
      Forest_SaveData((struct Forest_s *)ptQTask);
      File_Remove((char *)&ptQTask[23].isInMemPool + 1);
      Forest_CreateBSPTree((struct Forest_s *)ptQTask);
      Forest_GenerateHeightDataRecursively((struct Forest_s *)ptQTask, (struct ForestNode_s *)ptQTask[16].ptNext);
      ptQTask[39].tQTaskRefList.ptHead = nullptr;
      ptQTask[39].tQTaskChildren.ptHead = nullptr;
      ptQTask[38].tQTaskRefList.ptTail = nullptr;
    }
    *(_DWORD *)&ptQTask[36].eQTaskType = ptQTask[36].ptParent;
    goto LABEL_34;
  }
}

// source: h/2/forest.c:3317  [size]
void __cdecl Forest_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = Forest_ptParameterList;
}

// source: h/2/forest.c:3335  [size]
unsigned __int16 __cdecl Forest_GetQTaskType()
{
  return Forest_eQTaskType;
}

// source: h/2/forest.c:3348  [size]
unsigned int __cdecl Forest_GetQTaskGroup()
{
  return Forest_bQTaskGroup;
}

// source: h/2/forest.c:3362  [anchor-strings]
void __cdecl Forest_Open()
{
  unsigned __int16 v0; // si
  unsigned int SystemGroup; // eax
  struct ParameterList_s *v2; // eax
  int v3; // edx

  v0 = QTask_NewQTaskType("Forest", 1584, DynCubeObj_eQTaskType, 0, 0);
  Forest_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 0, Forest_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, Forest_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, (void (__cdecl *)(struct QTask_s *))Forest_RunHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 5, Forest_EnterHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 11, Forest_GetNextZHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 10, Forest_TraceLinesHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 9, Forest_GetLineOfSightHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, Forest_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Forest_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, Level_eSaveQTaskQTaskEvent, Forest_SaveQTaskHandler);
  QTask_LinkQTaskEventHandlerFn(v0, Lightmap_eDrawQTaskEvent, Forest_DrawLightmapHandler);
  QTask_LinkQTaskEventHandlerFn(v0, Lightmap_eEnumerateQTaskEvent, Forest_EnumerateLightmapHandler);
  QTask_LinkQTaskEventHandlerFn(v0, Envmap_eDrawQTaskEvent, Forest_DrawEnvmapHandler);
  QTask_LinkQTaskEventHandlerFn(v0, Envmap_eEnumerateQTaskEvent, Forest_EnumerateEnvmapHandler);
  Forest_isGetNextZEvaluateEventHandlerLinked = 0;
  Forest_bQTaskGroup = 2;
  SystemGroup = QTask_AllocateSystemGroup(2u);
  QTask_SetQTaskTypeGroup(Forest_eQTaskType, SystemGroup);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  v2 = (struct ParameterList_s *)Mem_AllocFn(372, 4);
  v2->ptParameterListItem = (struct ParameterListItem_s *)&v2[1];
  v3 = Level_eParameterTypeObjectPos;
  v2->nParameters = 0;
  v2->nMaxParameters = 18;
  Forest_ptParameterList = v2;
  ParameterList_AddParameter(v2, 0x290u, v3, "Position", 7u, nullptr);
  ParameterList_AddParameter(Forest_ptParameterList, 0x2C0u, Level_eParameterTypeString16, "Model", 7u, nullptr);
  ParameterList_AddParameter(Forest_ptParameterList, 0x5C0u, Level_eParameterTypeReal32, "Area size", 7u, nullptr);
  ParameterList_AddParameter(
    Forest_ptParameterList,
    0x620u,
    Level_eParameterTypePushButton,
    "Randomize area",
    7u,
    nullptr);
  ParameterList_AddParameter(Forest_ptParameterList, 0x60Cu, Level_eParameterTypePushButton, "Update", 7u, nullptr);
  ParameterList_AddParameter(
    Forest_ptParameterList,
    0x608u,
    Level_eParameterTypePushButton,
    "Calculate light",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Forest_ptParameterList,
    0x5CCu,
    Level_eParameterTypeReal32,
    "Density of trees [1/m^2]",
    7u,
    nullptr);
  ParameterList_AddParameterMinMax(
    Forest_ptParameterList,
    0x5D8u,
    Level_eParameterTypeReal32,
    "Random rotation range",
    7u,
    0.0,
    1.0);
  ParameterList_AddParameterMinMax(
    Forest_ptParameterList,
    0x5DCu,
    Level_eParameterTypeReal32,
    "Random X-scale range",
    7u,
    0.0,
    1.0);
  ParameterList_AddParameterMinMax(
    Forest_ptParameterList,
    0x5E0u,
    Level_eParameterTypeReal32,
    "Random Y-scale range ",
    7u,
    0.0,
    1.0);
  ParameterList_AddParameterMinMax(
    Forest_ptParameterList,
    0x5E4u,
    Level_eParameterTypeReal32,
    "Random Z-scale range",
    7u,
    0.0,
    1.0);
  ParameterList_AddParameter(
    Forest_ptParameterList,
    0x61Cu,
    Level_eParameterTypebool8,
    "Isotropic scaling",
    7u,
    nullptr);
  ParameterList_AddParameter(Forest_ptParameterList, 0x5F8u, Level_eParameterTypeInt32, "Number of trees", 3u, nullptr);
  ParameterList_AddParameter(Forest_ptParameterList, 0x5C8u, Level_eParameterTypeReal32, "Brush size (m)", 7u, nullptr);
  ParameterList_AddParameter(
    Forest_ptParameterList,
    0x618u,
    Level_eParameterTypebool8,
    "Brush draw/delete",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Forest_ptParameterList,
    0x5D4u,
    Level_eParameterTypeReal32,
    "View cutoff (m) (limited by object lod settings)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Forest_ptParameterList,
    0x610u,
    Level_eParameterTypebool8,
    "Normalize objects to ground",
    7u,
    nullptr);
  ParameterList_AddParameterMinMax(
    Forest_ptParameterList,
    0x604u,
    Level_eParameterTypeInt32,
    "Number of LODs affected by the wind",
    7u,
    0.0,
    5.0);
  Forest_tRandomState.anRandom[0] = -923849456;
  Forest_tRandomState.anRandom[1] = 1433794390;
  Forest_tRandomState.anRandom[2] = 1468206797;
  Forest_tClipPlanes.nClipPlanes = 7;
  if ( !Forest_tClipPlanes.ptClipPlane )
    Forest_tClipPlanes.ptClipPlane = (struct Clipping_ClipPlane_s *)Mem_AllocFn(168, 4);
}

// source: h/2/forest.c:3443  [anchor-hash]
void __cdecl Forest_Close()
{
  int v0; // esi
  int v1; // esi

  if ( Forest_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&Forest_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  if ( Forest_tClipPlanes.ptClipPlane )
  {
    v1 = *(_DWORD *)((int)&Forest_tClipPlanes.ptClipPlane[-1].tNormal.vZ & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
    Forest_tClipPlanes.ptClipPlane = nullptr;
  }
  QTask_DeleteQTaskType(Forest_eQTaskType);
  QTask_FreeGroup(2u);
}
