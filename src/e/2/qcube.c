/* e/2/qcube.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: e/2/qcube.c:366  [anchor-strings]
void __cdecl QCube_Open()
{
  int v0; // eax
  int v1; // ecx
  int v2; // ebp
  int v3; // ebx
  int i; // edi
  int v5; // eax
  int v6; // esi
  int v7; // edx
  bool v8; // cc
  bool v9; // cc
  int v10; // eax
  unsigned __int8 v11; // cl
  unsigned __int8 *v12; // esi
  unsigned __int8 j; // al
  char v14; // bl
  char v15; // dl
  unsigned __int8 *v16; // edi
  int *v17; // esi
  int k; // edx
  int v19; // eax
  int v20; // ecx
  int v21; // eax
  int m; // edx
  int v23; // ecx
  unsigned __int8 v24; // bl
  char v25; // al
  int iZ; // [esp+10h] [ebp-18h]
  int iZa; // [esp+10h] [ebp-18h]
  int iY; // [esp+14h] [ebp-14h]
  int iYa; // [esp+14h] [ebp-14h]
  int nTemp; // [esp+18h] [ebp-10h]
  int nTempa; // [esp+18h] [ebp-10h]
  int v32; // [esp+1Ch] [ebp-Ch]
  int v33; // [esp+20h] [ebp-8h]
  int v34; // [esp+24h] [ebp-4h]

  v0 = 0;
  for ( nTemp = 0; ; v0 = nTemp )
  {
    v32 = v0 & 4;
    v1 = 0;
    iZ = -1;
    v33 = v0 & 3;
    v34 = v0 << 6;
    do
    {
      v2 = -1;
      for ( iY = 1; iY > -2; --iY )
      {
        v3 = -1;
        for ( i = 1; i > -2; --i )
        {
          v5 = v3;
          v6 = v2;
          if ( v32 )
            v5 = i;
          switch ( v33 )
          {
            case 1:
              v6 = v5;
              v5 = iY;
              break;
            case 2:
              v6 = iY;
              v5 = -v5;
              break;
            case 3:
              v6 = -v5;
              v5 = v2;
              break;
          }
          v7 = v5 < 0;
          if ( v5 > 0 )
            v7 |= 2u;
          v8 = v6 <= 0;
          if ( v6 < 0 )
          {
            v7 |= 4u;
            v8 = v6 <= 0;
          }
          if ( !v8 )
            v7 |= 8u;
          v9 = iZ <= 0;
          if ( iZ < 0 )
          {
            v7 |= 0x10u;
            v9 = iZ <= 0;
          }
          if ( !v9 )
            v7 |= 0x20u;
          v10 = 1 << v1++;
          ++v3;
          QCube_aanHideLUT[0][v7 + v34] = v10;
        }
        ++v2;
      }
      ++iZ;
    }
    while ( iZ < 2 );
    if ( ++nTemp >= 8 )
      break;
  }
  v11 = 0;
  v12 = QCube_aabNewOrientation[0];
  do
  {
    for ( j = 0; j < 8u; ++j )
    {
      v14 = j;
      if ( v11 >= 4u )
      {
        v15 = v11 - j;
        v14 = ~j;
      }
      else
      {
        v15 = v11 + j;
      }
      *v12++ = (v14 & 4) + (v15 & 3);
    }
    ++v11;
  }
  while ( v11 < 8u );
  v16 = QCube_aabCubeVertexMaskOrientation[0];
  v17 = &World_abOrientationData[0][1];
  do
  {
    for ( k = 0; k < 256; ++k )
    {
      v19 = 0;
      if ( (k & 1) != 0 )
        v19 = 1 << *(v17 - 1);
      if ( (k & 2) != 0 )
        v19 |= 1 << *v17;
      if ( (k & 4) != 0 )
        v19 |= 1 << v17[1];
      if ( (k & 8) != 0 )
        v19 |= 1 << v17[2];
      if ( (k & 0x10) != 0 )
        v19 |= 1 << v17[3];
      if ( (k & 0x20) != 0 )
        v19 |= 1 << v17[4];
      if ( (k & 0x40) != 0 )
        v19 |= 1 << v17[5];
      if ( (k & 0x80u) != 0 )
        v19 |= 1 << v17[6];
      v16[v19] = k;
    }
    v17 += 8;
    v16 += 256;
  }
  while ( (int)v17 < 7061780 );
  v20 = 0;
  nTempa = 0;
  for ( iZa = 0; iZa < 3; ++iZa )
  {
    v21 = 0;
    iYa = 0;
    do
    {
      for ( m = 0; m < 3; ++m )
      {
        QCube_abSubVertexBelongsToCubes[v20] = 0;
        v23 = 0;
        v24 = 0;
        do
        {
          v25 = (m == 1 || m >> 1 == (v23 & 1)) && (v21 == 1 || v21 == (v23 & 2)) && (iZa == 1 || 2 * iZa == (v23 & 4));
          v24 |= v25 << v23;
          v21 = iYa;
          ++v23;
        }
        while ( v23 < 8 );
        QCube_abSubVertexBelongsToCubes[nTempa] = v24;
        if ( (m & 1) == 0 && (iYa & 1) == 0 && (iZa & 1) == 0 )
          QCube_abSubVertexBelongsToCubes[nTempa] = 0;
        v20 = ++nTempa;
      }
      v21 = iYa + 1;
      iYa = v21;
    }
    while ( v21 < 3 );
  }
  QTask_NewSystemQTaskEventFn(0, 15, "EnterImmediately");
  QTask_NewSystemQTaskEventFn(0, 16, "LeaveImmediately");
  QTask_NewSystemQTaskEventFn(0, 17, "EnterCameraCube");
  QTask_NewSystemQTaskEventFn(0, 18, "LeaveCameraCube");
  QTask_AllocateSystemPropertyBit(15, 7);
  QTask_AllocateSystemPropertyBit(16, 8);
  QCube_eGetSectorQTaskEvent = QTask_NewQTaskEventFn(0x200u, "GetSector");
  QCube_eGetClosestVertexQTaskEvent = QTask_NewQTaskEventFn(0x200u, "GetClosestVertex");
}

// source: e/2/qcube.c:561  [size]
void __cdecl QCube_AllocHashCubeData()
{
  void **p_ptHashCubeData; // eax

  p_ptHashCubeData = &QCube_atCubeHash[0].ptHashCubeData;
  do
  {
    *(p_ptHashCubeData - 2) = (void *)-1;
    *p_ptHashCubeData = nullptr;
    p_ptHashCubeData += 7;
  }
  while ( (int)p_ptHashCubeData < 139693560 );
}

// source: e/2/qcube.c:574  [size]
void __cdecl QCube_FreeHashCubeData()
{
  void **p_ptHashCubeData; // eax

  p_ptHashCubeData = &QCube_atCubeHash[0].ptHashCubeData;
  do
  {
    *(p_ptHashCubeData - 2) = (void *)-1;
    *p_ptHashCubeData = nullptr;
    p_ptHashCubeData += 7;
  }
  while ( (int)p_ptHashCubeData < 139693560 );
}

// source: e/2/qcube.c:594  [anchor-hash]
void __cdecl QCube_Close()
{
  QTask_FreePropertyBit(15);
  QTask_FreePropertyBit(16);
  QTask_DeleteQTaskEvent(15);
  QTask_DeleteQTaskEvent(16);
  QTask_DeleteQTaskEvent(17);
  QTask_DeleteQTaskEvent(18);
  QTask_DeleteQTaskEvent(QCube_eGetSectorQTaskEvent);
  QTask_DeleteQTaskEvent(QCube_eGetClosestVertexQTaskEvent);
}

// source: e/2/qcube.c:838  [size~]
void __cdecl QCube_CallHandlers(struct World_s *ptWorld)
{
  int v1; // esi
  struct QTaskList_s *ptTerrainQTaskList; // eax
  int v3; // esi
  int v4; // edi
  struct CallQueueItem_s *ptFirst; // eax
  struct CallQueueItem_s *v6; // edx
  struct CallQueueItem_s *ptNext; // ecx
  bool v8; // zf
  int v9; // [esp+8h] [ebp-4h]

  World_TriggerQTaskEventXyzSpecificTree(
    ptWorld,
    17,
    nullptr,
    &TransContext_tActiveTransContext.tPos,
    0x20000000u,
    WORLD_DYNCUBETREE_STATIONARY);
  v1 = 0;
  v9 = 0;
  do
  {
    NetManager_RunNetworkInterrupt();
    if ( v1 == 2 )
    {
      ptTerrainQTaskList = ptWorld->ptTerrainQTaskList;
      if ( ptTerrainQTaskList )
      {
        v3 = 0;
        if ( ptTerrainQTaskList->nTask > 0 )
        {
          v4 = 8;
          do
          {
            ((void (__cdecl *)(_DWORD, _DWORD))QTask_aatQTaskFinalEvent[5][*(unsigned __int16 *)(*(int *)((char *)&ptTerrainQTaskList->nTask + v4)
                                                                                               + 36)].pfHandler)(
              *(int *)((char *)&ptTerrainQTaskList->nTask + v4),
              0);
            ptTerrainQTaskList = ptWorld->ptTerrainQTaskList;
            ++v3;
            v4 += 4;
          }
          while ( v3 < ptTerrainQTaskList->nTask );
        }
        v1 = v9;
      }
    }
    CallQueue_CallHandlers((struct CallQueue_t *)(8 * v1 + 128714432));
    if ( v1 == 5 && isDrawInfra )
    {
      CallQueue_CallHandlers(&QCube_atCallQueues[12]);
      ptFirst = QCube_atCallQueues[13].ptFirst;
      if ( QCube_atCallQueues[13].ptFirst )
      {
        v6 = CallQueue_ptFirstFreeItem;
        do
        {
          ptNext = ptFirst->ptNext;
          v8 = ptFirst->ptNext == nullptr;
          ptFirst->ptNext = v6;
          v6 = ptFirst;
          ptFirst = ptNext;
        }
        while ( !v8 );
        CallQueue_ptFirstFreeItem = v6;
      }
      QCube_atCallQueues[13].pptLast = &QCube_atCallQueues[13].ptFirst;
      QCube_atCallQueues[13].ptFirst = nullptr;
    }
    sub_5C3D30();
    v9 = ++v1;
  }
  while ( v1 < 16 );
  World_TriggerQTaskEventXyzSpecificTree(
    ptWorld,
    18,
    nullptr,
    &TransContext_tActiveTransContext.tPos,
    0x20000000u,
    WORLD_DYNCUBETREE_STATIONARY);
}

// source: e/2/qcube.c:881  [size]
__int16 __cdecl QCube_GetGetSectorQTaskEvent()
{
  return QCube_eGetSectorQTaskEvent;
}

// source: e/2/qcube.c:894  [size]
__int16 __cdecl QCube_GetGetClosestVertexQTaskEvent()
{
  return QCube_eGetClosestVertexQTaskEvent;
}

// source: e/2/qcube.c:909  [anchor-strings]
void __cdecl QCube_ProcessCube(struct World_s *ptWorld)
{
  #pragma pack(push, 1)
  union
  {
    struct { unsigned __int8 bChildren; };
    struct { char igi2_o1[1]; int iCubeIterationFromTop; };
    struct { char igi2_o2[5]; int isSplit; };
    struct { char igi2_o3[5]; int isSplita; };
    struct { char igi2_o4[5]; int isSplitb; };
    struct { char igi2_o5[9]; int nChildUnrotatedPosY; };
    struct { char igi2_o6[9]; int nChildUnrotatedPosYa; };
    struct { char igi2_o7[17]; int iCube; };
    struct { char igi2_o8[17]; int iCubea; };
    struct { char igi2_o9[17]; int iCubeb; };
    struct { char igi2_o10[21]; int nCubeUnrotatedPosY; };
    struct { char igi2_o11[25]; float vZ; };
    struct { char igi2_o12[25]; int vZa; };
    struct { char igi2_o13[29]; int nCubeUnrotatedPosZ; };
    struct { char igi2_o14[29]; int nCubeUnrotatedPosZa; };
    struct { char igi2_o15[33]; int nCubeUnrotatedPosX; };
    struct { char igi2_o16[37]; int nCubePosX; };
    struct { char igi2_o17[37]; int nCubePosXa; };
    struct { char igi2_o18[41]; int nCubePosY; };
    struct { char igi2_o19[41]; int nCubePosYa; };
    struct { char igi2_o20[45]; int nCubePosZ; };
    struct { char igi2_o21[45]; int nCubePosZa; };
    struct { char igi2_o22[49]; struct int32x3_t *pnCorner; };
    struct { char igi2_o23[53]; int bCubeOrientation; };
    struct { char igi2_o24[53]; int bCubeOrientationa; };
    struct { char igi2_o25[57]; struct DynCubeTreeItem_s *aptCurrentDynCubeTree; };
    struct { char igi2_o26[61]; struct QCube_CubeStack_t *ptCurrentCubeStack; };
    struct { char igi2_o27[65]; int v87; };
    struct { char igi2_o28[69]; int nWorldPosZ; };
    struct { char igi2_o29[73]; int bisDynCubeTree; };
    struct { char igi2_o30[77]; int nFastTerrainCube; };
    struct { char igi2_o31[81]; int iCubeChildMask; };
    struct { char igi2_o32[85]; int nFrame; };
    struct { char igi2_o33[89]; int bOrientatedChildMask; };
    struct { char igi2_o34[93]; int bCubeContainsChildren; };
    struct { char igi2_o35[97]; int nDrawHashTerrainCube; };
    struct { char igi2_o36[101]; int nDetail; };
    struct { char igi2_o37[105]; float tCameraPos; };
    struct { char igi2_o38[105]; float tCameraPosa; };
    struct { char igi2_o39[109]; float tCameraPos_4; };
    struct { char igi2_o40[109]; float tCameraPos_4a; };
    struct { char igi2_o41[109]; float tCameraPos_4b; };
    struct { char igi2_o42[113]; float tCameraPos_8; };
    struct { char igi2_o43[117]; int iOrientatedCubeChild; };
    struct { char igi2_o44[117]; int iOrientatedCubeChilda; };
    struct { char igi2_o45[121]; int nPrevFrame; };
    struct { char igi2_o46[125]; int nWaterLevel; };
    struct { char igi2_o47[129]; int bDynCubeChildrenMask; };
    struct { char igi2_o48[133]; struct TerrainMesh_HashCubeData_t **pptDrawHashTerrainCube; };
    struct { char igi2_o49[137]; int v109; };
    struct { char igi2_o50[141]; float vFovX; };
    struct { char igi2_o51[145]; struct CubeTree_s *ptCubeTree; };
    struct { char igi2_o52[149]; float vFovY; };
    struct { char igi2_o53[153]; int tIntCameraPos; };
    struct { char igi2_o54[157]; int tIntCameraPos_4; };
    struct { char igi2_o55[161]; int tIntCameraPos_8; };
    struct { char igi2_o56[165]; struct CubeTree_s *ptCurrentTreeCube; };
    struct { char igi2_o57[169]; char *pbNewOrientation; };
    struct { char igi2_o58[173]; char *pbOrientationData; };
    struct { char igi2_o59[177]; struct real32x9_t tCameraMatrix; };
    struct { char igi2_o60[217]; struct int32x3_t atUnrotatedCorner[8]; };
    struct { char igi2_o61[313]; struct int32x3_t atCorner[8]; };
    struct { char igi2_o62[409]; char aabOrientationData[8][8]; };
    struct { char igi2_o63[473]; char aabNewOrientation[8][8]; };
    struct { char igi2_o64[537]; struct QCube_CubeStack_t atCubeStack[128]; };
    char igi2_extent[1561];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct World_Water_t *ptWater; // eax
  char v2; // bl
  double *v3; // edx
  int *v4; // esi
  int v5; // ecx
  double v6; // st7
  double v7; // st6
  char v8; // al
  int v9; // esi
  int v10; // edi
  double v11; // st5
  double v12; // st4
  double v13; // st3
  int v14; // ecx
  double nX; // st5
  double v16; // st4
  double v17; // st3
  double v18; // st5
  unsigned __int8 v19; // cl
  struct DynCubeTreeItem_s *v20; // ebx
  int v21; // eax
  struct QCube_CubeStack_t *v22; // ebx
  int bCubeData; // eax
  struct int32x3_t *v24; // esi
  struct int32x3_t *v25; // edi
  int v26; // eax
  int v27; // eax
  struct DynCubeTreeItem_s *v28; // eax
  struct QTask_s *p_tQTask; // ecx
  struct CallQueueItem_s *v30; // eax
  int v31; // eax
  char *v32; // esi
  char v33; // cl
  double v34; // st5
  double v35; // st5
  double v36; // st4
  double v37; // st5
  double v38; // st4
  int v39; // esi
  int v40; // edi
  int v41; // ebx
  int v42; // eax
  int v43; // ecx
  int v44; // ecx
  struct CubeTree_s *v45; // eax
  int v46; // edi
  int v47; // ebx
  int v48; // esi
  int v49; // eax
  int v50; // ecx
  int v51; // esi
  int *v52; // eax
  int v53; // esi
  struct TerrainMesh_HashCubeData_t *v54; // ecx
  double *v55; // edx
  bool v56; // cc
  struct DynCubeTreeItem_s *v57; // edi
  int *p_nFrame; // edx
  int v59; // edi

  ptWater = World_ptActiveWorld->ptWater;
  v2 = 0;
  if ( ptWater )
    igi2_frame.nWaterLevel = (__int64)ptWater->vWaterLevel;
  else
    igi2_frame.nWaterLevel = -536870912;
  igi2_frame.nFrame = (unsigned __int16)Display_nFrame;
  igi2_frame.vFovX = TransContext_tActiveTransContext.vFOVX;
  igi2_frame.ptCubeTree = ptWorld->ptCubeTree;
  igi2_frame.vFovY = TransContext_tActiveTransContext.vFOVY;
  qmemcpy(igi2_frame.aabNewOrientation, QCube_aabNewOrientation, sizeof(igi2_frame.aabNewOrientation));
  igi2_frame.nPrevFrame = (unsigned __int16)(Display_nFrame - 1);
  Debug_iFastTerrainCube = 0;
  igi2_frame.nFastTerrainCube = 0;
  igi2_frame.nDrawHashTerrainCube = 0;
  v3 = (double *)&unk_84FAC30;
  igi2_frame.pptDrawHashTerrainCube = QCube_aptDrawHashTerrainCube;
  HeightMap_nStackItem = 0;
  TerrainLightMap_nStackItem = 0;
  TextureModifier_nStackItem = 0;
  HeightMap_biHeightMap = 0;
  TextureModifier_biTextureModifier = 0;
  v4 = World_abOrientationData[0];
  v5 = 0;
  v6 = 1.732100009918213 / cos(atan2(TransContext_tActiveTransContext.vFOVX, 1.0)) * 1073741824.0;
  v7 = 1.732100009918213 / cos(atan2(TransContext_tActiveTransContext.vFOVY, 1.0)) * 1073741824.0;
  do
  {
    v8 = *(_BYTE *)v4++;
    igi2_frame.aabOrientationData[0][v5++] = v8;
  }
  while ( v5 < 64 );
  igi2_frame.tCameraPos_4 = TransContext_tActiveTransContext.tPos.vY;
  qmemcpy(&igi2_frame.tCameraMatrix, &TransContext_tActiveTransContext, sizeof(igi2_frame.tCameraMatrix));
  igi2_frame.tCameraPos_8 = TransContext_tActiveTransContext.tPos.vZ;
  igi2_frame.tIntCameraPos = (__int64)TransContext_tActiveTransContext.tPos.vX;
  igi2_frame.tIntCameraPos_4 = (__int64)igi2_frame.tCameraPos_4;
  igi2_frame.tIntCameraPos_8 = (__int64)igi2_frame.tCameraPos_8;
  v9 = -(QCube_tOrigoInt32x3.nX + igi2_frame.tIntCameraPos);
  v10 = -(QCube_tOrigoInt32x3.nY + igi2_frame.tIntCameraPos_4);
  igi2_frame.nCubeUnrotatedPosZ = -(QCube_tOrigoInt32x3.nZ + igi2_frame.tIntCameraPos_8);
  v11 = (double)v9;
  v12 = (double)v10;
  v13 = (double)igi2_frame.nCubeUnrotatedPosZ;
  igi2_frame.tCameraPos = igi2_frame.tCameraMatrix.tX.vZ * v13 + igi2_frame.tCameraMatrix.tX.vY * v12 + igi2_frame.tCameraMatrix.tX.vX * v11;
  igi2_frame.tCameraPos_4a = igi2_frame.tCameraMatrix.tY.vZ * v13 + igi2_frame.tCameraMatrix.tY.vY * v12 + igi2_frame.tCameraMatrix.tY.vX * v11;
  igi2_frame.nCubePosX = (__int64)igi2_frame.tCameraPos;
  igi2_frame.nCubePosY = (__int64)igi2_frame.tCameraPos_4a;
  v14 = 0;
  igi2_frame.nCubePosZ = (__int64)(igi2_frame.tCameraMatrix.tZ.vZ * v13 + igi2_frame.tCameraMatrix.tZ.vY * v12 + igi2_frame.tCameraMatrix.tZ.vX * v11);
  do
  {
    igi2_frame.atUnrotatedCorner[v14].nX = -1073741824;
    if ( (v2 & 1) != 0 )
      igi2_frame.atUnrotatedCorner[v14].nX = 0x40000000;
    igi2_frame.atUnrotatedCorner[v14].nY = -1073741824;
    if ( (v2 & 2) != 0 )
      igi2_frame.atUnrotatedCorner[v14].nY = 0x40000000;
    igi2_frame.atUnrotatedCorner[v14].nZ = -1073741824;
    if ( (v2 & 4) != 0 )
      igi2_frame.atUnrotatedCorner[v14].nZ = 0x40000000;
    nX = (double)igi2_frame.atUnrotatedCorner[v14++].nX;
    v16 = (double)*(int *)((char *)&igi2_frame.tCameraMatrix.tZ.vZ + v14 * 12);
    ++v2;
    v17 = (double)*(int *)((char *)&igi2_frame.tCameraMatrix.nOps + v14 * 12);
    igi2_frame.tCameraPosa = igi2_frame.tCameraMatrix.tX.vZ * v17 + v16 * igi2_frame.tCameraMatrix.tX.vY + nX * igi2_frame.tCameraMatrix.tX.vX;
    igi2_frame.tCameraPos_4b = igi2_frame.tCameraMatrix.tY.vZ * v17 + v16 * igi2_frame.tCameraMatrix.tY.vY + nX * igi2_frame.tCameraMatrix.tY.vX;
    v18 = v17 * igi2_frame.tCameraMatrix.tZ.vZ + v16 * igi2_frame.tCameraMatrix.tZ.vY + nX * igi2_frame.tCameraMatrix.tZ.vX;
    igi2_frame.atUnrotatedCorner[v14 + 7].nX = (__int64)igi2_frame.tCameraPosa;
    igi2_frame.atUnrotatedCorner[v14 + 7].nY = (__int64)igi2_frame.tCameraPos_4b;
    igi2_frame.atUnrotatedCorner[v14 + 7].nZ = (__int64)v18;
  }
  while ( v14 < 8 );
  igi2_frame.atCubeStack[0].bCubeData = 0;
  if ( igi2_frame.ptCubeTree )
  {
    v19 = igi2_frame.ptCubeTree[1].bEnableData & 0xF0;
    igi2_frame.atCubeStack[0].ptCubeTree = igi2_frame.ptCubeTree + 1;
    igi2_frame.ptCubeTree[1].bEnableData = v19;
    igi2_frame.atCubeStack[0].bCubeData = 2;
  }
  v20 = ptWorld->aptDynCubeTree[QCube_aiDynCubeTree[0]];
  if ( v20 )
  {
    qmemcpy(QCube_atStaticCopyFirstIterationDynCube, v20, sizeof(QCube_atStaticCopyFirstIterationDynCube));
    v20->aptChild[0] = QCube_atStaticCopyFirstIterationDynCube[0].aptChild[7];
    v20->aptChild[1] = QCube_atStaticCopyFirstIterationDynCube[0].aptChild[6];
    v20->aptChild[2] = QCube_atStaticCopyFirstIterationDynCube[0].aptChild[5];
    v20->aptChild[3] = QCube_atStaticCopyFirstIterationDynCube[0].aptChild[4];
    v20->aptChild[4] = QCube_atStaticCopyFirstIterationDynCube[0].aptChild[3];
    v20->aptChild[5] = QCube_atStaticCopyFirstIterationDynCube[0].aptChild[2];
    v20->aptChild[6] = QCube_atStaticCopyFirstIterationDynCube[0].aptChild[1];
    v20->aptChild[7] = QCube_atStaticCopyFirstIterationDynCube[0].aptChild[0];
    igi2_frame.bChildren = v20->bChildren;
    v21 = igi2_frame.atCubeStack[0].bCubeData | 0x400;
    v20->bChildren = (igi2_frame.bChildren >> 7)
                   + 2
                   * (((igi2_frame.bChildren & 0x40) != 0)
                    + 2
                    * (((igi2_frame.bChildren & 0x20) != 0)
                     + 2
                     * (((igi2_frame.bChildren & 0x10) != 0)
                      + 2
                      * (((igi2_frame.bChildren & 8) != 0)
                       + 2 * (((igi2_frame.bChildren & 4) != 0) + 2 * (2 * igi2_frame.bChildren + ((igi2_frame.bChildren & 2) != 0)))))));
    QCube_atStaticFakeParentDynCube[0].aptChild[0] = v20;
    igi2_frame.atCubeStack[0].bCubeData = v21;
    igi2_frame.aptCurrentDynCubeTree = QCube_atStaticFakeParentDynCube;
  }
  igi2_frame.nCubePosXa = igi2_frame.nCubePosX - igi2_frame.atCorner[0].nX;
  igi2_frame.nCubePosYa = igi2_frame.nCubePosY - igi2_frame.atCorner[0].nY;
  igi2_frame.nCubeUnrotatedPosX = v9 - igi2_frame.atUnrotatedCorner[0].nX;
  igi2_frame.nCubePosZa = igi2_frame.nCubePosZ - igi2_frame.atCorner[0].nZ;
  v22 = igi2_frame.atCubeStack;
  igi2_frame.nCubeUnrotatedPosY = v10 - igi2_frame.atUnrotatedCorner[0].nY;
  igi2_frame.nCubeUnrotatedPosZa = igi2_frame.nCubeUnrotatedPosZ - igi2_frame.atUnrotatedCorner[0].nZ;
  igi2_frame.iCubeIterationFromTop = -1;
  igi2_frame.ptCurrentCubeStack = igi2_frame.atCubeStack;
  igi2_frame.v87 = 0;
  do
  {
    bCubeData = v22->bCubeData;
    igi2_frame.iCube = (bCubeData >> 7) & 7;
    igi2_frame.bisDynCubeTree = bCubeData >> 10;
    v24 = &igi2_frame.atCorner[igi2_frame.iCube];
    v25 = &igi2_frame.atUnrotatedCorner[igi2_frame.iCube];
    if ( (bCubeData & 1) == 0 )
    {
      v27 = bCubeData | 1;
      v22->bCubeData = v27;
      igi2_frame.bCubeOrientation = 0;
      igi2_frame.bCubeContainsChildren = 0;
      if ( (v27 & 2) != 0 )
      {
        igi2_frame.ptCurrentTreeCube = v22->ptCubeTree;
        igi2_frame.bCubeOrientation = (v27 >> 4) & 7;
        igi2_frame.bCubeContainsChildren = v22->ptCubeTree->bEnableData;
      }
      igi2_frame.bDynCubeChildrenMask = 0;
      QCube_isDiscard = 0;
      if ( igi2_frame.bisDynCubeTree )
      {
        if ( (igi2_frame.bisDynCubeTree & 1) != 0 )
        {
          v28 = igi2_frame.aptCurrentDynCubeTree->aptChild[igi2_frame.iCube];
          igi2_frame.bDynCubeChildrenMask = v28->bChildren;
          p_tQTask = &v28->ptDynCubeObj->tQObj.tQTask;
          for ( igi2_frame.aptCurrentDynCubeTree = v28; p_tQTask; p_tQTask = p_tQTask[2].tQTaskChildren.ptTail )
          {
            if ( !p_tQTask[2].tQTaskRefList.ptHead )
            {
              igi2_frame.isSplitb = (int)p_tQTask[2].ptNext;
              igi2_frame.iCubeb = 8 * (int)p_tQTask[2].tQTaskRefList.ptTail + 128714432;
              v30 = CallQueue_ptFirstFreeItem;
              CallQueue_ptFirstFreeItem = CallQueue_ptFirstFreeItem->ptNext;
              v30->pxContext = (void *)igi2_frame.isSplitb;
              v30->ptQTask = p_tQTask;
              v30->uEvent.eQTaskEvent = 5;
              v30->isNoContext = false;
              v30->ptNext = nullptr;
              **(_DWORD **)(igi2_frame.iCubeb + 4) = v30;
              *(_DWORD *)(igi2_frame.iCubeb + 4) = v30;
              v22 = igi2_frame.ptCurrentCubeStack;
              ++QCube_nNumObjects;
            }
          }
        }
      }
      v6 = v6 * 0.5;
      v7 = v7 * 0.5;
      --igi2_frame.v87;
      v31 = v24->nX >> ++igi2_frame.iCubeIterationFromTop;
      igi2_frame.iCubea = 0;
      igi2_frame.nCubePosXa += v31;
      igi2_frame.iCubeChildMask = 1;
      igi2_frame.nCubePosYa += v24->nY >> igi2_frame.iCubeIterationFromTop;
      igi2_frame.nCubePosZa += v24->nZ >> igi2_frame.iCubeIterationFromTop;
      igi2_frame.nCubeUnrotatedPosX += v25->nX >> igi2_frame.iCubeIterationFromTop;
      igi2_frame.nCubeUnrotatedPosY += v25->nY >> igi2_frame.iCubeIterationFromTop;
      v32 = igi2_frame.aabOrientationData[igi2_frame.bCubeOrientation];
      igi2_frame.nCubeUnrotatedPosZa += v25->nZ >> igi2_frame.iCubeIterationFromTop;
      igi2_frame.pbNewOrientation = igi2_frame.aabNewOrientation[igi2_frame.bCubeOrientation];
      igi2_frame.pnCorner = igi2_frame.atCorner;
      igi2_frame.v109 = (char *)igi2_frame.atUnrotatedCorner - (char *)igi2_frame.atCorner;
      while ( 1 )
      {
        igi2_frame.iOrientatedCubeChild = *v32;
        igi2_frame.pbOrientationData = v32 + 1;
        igi2_frame.bOrientatedChildMask = 1 << *v32;
        if ( (igi2_frame.bDynCubeChildrenMask & igi2_frame.iCubeChildMask) != 0 || ((1 << *v32) & igi2_frame.bCubeContainsChildren) != 0 )
        {
          v33 = igi2_frame.iCubeIterationFromTop + 1;
          v34 = (double)(igi2_frame.nCubePosZa + (igi2_frame.pnCorner->nZ >> (igi2_frame.iCubeIterationFromTop + 1)));
          igi2_frame.vZ = v34;
          if ( 64.0 - v7 < v34 )
          {
            v35 = (double)(igi2_frame.nCubePosXa + (igi2_frame.pnCorner->nX >> v33));
            v36 = igi2_frame.vZ * igi2_frame.vFovX + v6;
            if ( v35 < v36 && v35 > -v36 )
            {
              v37 = (double)(igi2_frame.nCubePosYa + (igi2_frame.pnCorner->nY >> v33));
              v38 = igi2_frame.vZ * igi2_frame.vFovY + v7;
              if ( v37 < v38 && v37 > -v38 )
              {
                igi2_frame.bCubeOrientationa = 0;
                v39 = igi2_frame.nCubeUnrotatedPosZa + (*(int *)((char *)&igi2_frame.pnCorner->nZ + igi2_frame.v109) >> v33);
                igi2_frame.isSplit = 0x40000000 >> v33;
                if ( igi2_frame.tIntCameraPos_8 + v39 + (0x40000000 >> v33) >= igi2_frame.nWaterLevel )
                {
                  v40 = igi2_frame.nCubeUnrotatedPosX + (*(int *)((char *)&igi2_frame.pnCorner->nX + igi2_frame.v109) >> v33);
                  v41 = igi2_frame.nCubeUnrotatedPosY + (*(int *)((char *)&igi2_frame.pnCorner->nY + igi2_frame.v109) >> v33);
                  igi2_frame.nChildUnrotatedPosY = v41;
                  v42 = v40;
                  if ( v40 < 0 )
                    v42 = -v40;
                  if ( v41 < 0 )
                    v41 = -v41;
                  if ( v41 > v42 )
                    v42 = v41;
                  v43 = igi2_frame.nCubeUnrotatedPosZa + (*(int *)((char *)&igi2_frame.pnCorner->nZ + igi2_frame.v109) >> v33);
                  if ( v39 < 0 )
                    v43 = -v39;
                  if ( v43 > v42 )
                    v42 = v43;
                  igi2_frame.nDetail = (v42 - igi2_frame.isSplit) >> (igi2_frame.v87 + 25);
                  igi2_frame.vZa = 0;
                  igi2_frame.isSplita = 0;
                  if ( (igi2_frame.bDynCubeChildrenMask & igi2_frame.iCubeChildMask) != 0
                    && (double)igi2_frame.nDetail * TransContext_tActiveTransContext.vFOVX < 9600.0
                    && (igi2_frame.bisDynCubeTree & 1) != 0
                    && ((unsigned __int8)igi2_frame.iCubeChildMask & igi2_frame.aptCurrentDynCubeTree->bChildren) != 0 )
                  {
                    igi2_frame.vZa = 1024;
                    igi2_frame.isSplita = 1;
                  }
                  if ( (igi2_frame.bCubeContainsChildren & igi2_frame.bOrientatedChildMask) != 0 )
                  {
                    v44 = igi2_frame.pbNewOrientation[igi2_frame.ptCurrentTreeCube->abOrientation[igi2_frame.iOrientatedCubeChild]];
                    v45 = &igi2_frame.ptCubeTree[igi2_frame.ptCurrentTreeCube->aiChildIndex[igi2_frame.iOrientatedCubeChild]];
                    igi2_frame.bCubeOrientationa = (int)v45;
                    igi2_frame.iOrientatedCubeChilda = v44;
                    if ( igi2_frame.nDetail < QCube_nMainDetailLevel && igi2_frame.iCubeIterationFromTop + 1 < 16 )
                    {
                      igi2_frame.vZa |= (16 * v44) | 2;
LABEL_79:
                      v22 = igi2_frame.ptCurrentCubeStack + 1;
                      igi2_frame.ptCurrentCubeStack = v22;
                      v22->bCubeData = igi2_frame.vZa | (igi2_frame.iCubea << 7);
                      v22->ptCubeTree = v45;
                      goto LABEL_82;
                    }
                    if ( igi2_frame.iCubeIterationFromTop + 1 > 6 )
                    {
                      v46 = igi2_frame.tIntCameraPos + v40;
                      v47 = igi2_frame.nChildUnrotatedPosY + igi2_frame.tIntCameraPos_4;
                      v48 = igi2_frame.tIntCameraPos_8 + v39;
                      v49 = ((v46
                            ^ (igi2_frame.nChildUnrotatedPosY + igi2_frame.tIntCameraPos_4)
                            ^ v48
                            ^ (((igi2_frame.nChildUnrotatedPosY + igi2_frame.tIntCameraPos_4) ^ ((v46 ^ (v48 >> 2)) >> 3)) >> 5)) >> 6)
                          & 0x7FF;
                      v50 = v49;
                      igi2_frame.nWorldPosZ = v48;
                      v51 = QCube_atCubeHash[v49].nFrame;
                      for ( igi2_frame.nChildUnrotatedPosYa = igi2_frame.nChildUnrotatedPosY + igi2_frame.tIntCameraPos_4;
                            v51 != -1;
                            v51 = QCube_atCubeHash[v49].nFrame )
                      {
                        if ( igi2_frame.nPrevFrame == v51
                          && QCube_atCubeHash[v50].nX == v46
                          && QCube_atCubeHash[v50].nY == v47
                          && QCube_atCubeHash[v50].nZ == igi2_frame.nWorldPosZ )
                        {
                          break;
                        }
                        v49 = ((_WORD)v49 + 1) & 0x7FF;
                        v50 = v49;
                      }
                      v52 = (int *)(28 * v49 + 139636192);
                      v53 = 1;
                      if ( igi2_frame.nPrevFrame == v52[4] )
                      {
                        v52[4] = igi2_frame.nFrame;
                        v54 = (struct TerrainMesh_HashCubeData_t *)v52[6];
                        v53 = 0;
                        if ( !v54 )
                        {
                          LDebug_Error("Should have allocated data for cube existing previous frame");
                          goto LABEL_94;
                        }
                        *igi2_frame.pptDrawHashTerrainCube++ = v54;
                        ++igi2_frame.nDrawHashTerrainCube;
                      }
                      else
                      {
                        if ( v52[6] )
                        {
                          LDebug_Error("Should't have allocate hash data! ERROR!");
LABEL_94:
                          abort();
                        }
                        v52[2] = igi2_frame.nWorldPosZ;
                        v52[3] = igi2_frame.nDetail;
                        v52[5] = 3;
                        *v52 = v46;
                        v52[1] = v47;
                        v52[4] = igi2_frame.nFrame;
                      }
                      if ( igi2_frame.nFastTerrainCube <= 4095 )
                      {
                        if ( v53 )
                        {
                          *((_DWORD *)v3 - 1) = v52;
                          v55 = (double *)((char *)v3 - 4);
                          *((_DWORD *)v55 - 1) = 0;
                          v55 = (double *)((char *)v55 - 4);
                          *((_DWORD *)v55-- - 1) = 0xFFFF;
                          *(_DWORD *)v55 = *(_DWORD *)(igi2_frame.bCubeOrientationa + 28);
                          *((_DWORD *)v55-- - 1) = igi2_frame.iOrientatedCubeChilda;
                          *(_DWORD *)v55 = igi2_frame.iCubeIterationFromTop + 1;
                          *(v55 - 1) = (double)igi2_frame.nWorldPosZ;
                          v55 -= 2;
                          *v55 = (double)igi2_frame.nChildUnrotatedPosYa;
                          v3 = v55 + 11;
                          ++igi2_frame.nFastTerrainCube;
                          *(v3 - 12) = (double)v46;
                        }
                      }
                      else
                      {
                        ++Debug_iFastTerrainCube;
                      }
                    }
                  }
                  if ( igi2_frame.isSplita )
                  {
                    v45 = (struct CubeTree_s *)igi2_frame.bCubeOrientationa;
                    goto LABEL_79;
                  }
                  v22 = igi2_frame.ptCurrentCubeStack;
                }
              }
            }
          }
        }
LABEL_82:
        ++igi2_frame.pnCorner;
        v56 = igi2_frame.iCubea + 1 < 8;
        igi2_frame.iCubeChildMask *= 2;
        ++igi2_frame.iCubea;
        if ( !v56 )
          goto LABEL_83;
        v32 = igi2_frame.pbOrientationData;
      }
    }
    if ( igi2_frame.bisDynCubeTree && (igi2_frame.bisDynCubeTree & 1) != 0 )
      igi2_frame.aptCurrentDynCubeTree = igi2_frame.aptCurrentDynCubeTree->ptParent;
    v6 = v6 + v6;
    v7 = v7 + v7;
    igi2_frame.nCubePosXa -= v24->nX >> igi2_frame.iCubeIterationFromTop;
    igi2_frame.nCubePosYa -= v24->nY >> igi2_frame.iCubeIterationFromTop;
    igi2_frame.nCubePosZa -= v24->nZ >> igi2_frame.iCubeIterationFromTop;
    igi2_frame.nCubeUnrotatedPosX -= v25->nX >> igi2_frame.iCubeIterationFromTop;
    v26 = v25->nZ >> igi2_frame.iCubeIterationFromTop;
    igi2_frame.nCubeUnrotatedPosY -= v25->nY >> igi2_frame.iCubeIterationFromTop--;
    --v22;
    igi2_frame.nCubeUnrotatedPosZa -= v26;
    ++igi2_frame.v87;
    igi2_frame.ptCurrentCubeStack = v22;
LABEL_83:
    ;
  }
  while ( v22 >= igi2_frame.atCubeStack );
  v57 = ptWorld->aptDynCubeTree[QCube_aiDynCubeTree[0]];
  if ( v57 )
    qmemcpy(v57, QCube_atStaticCopyFirstIterationDynCube, sizeof(struct DynCubeTreeItem_s));
  QCube_nDrawHashTerrainCube = igi2_frame.nDrawHashTerrainCube;
  QCube_nFastTerrainCube = igi2_frame.nFastTerrainCube;
  p_nFrame = &QCube_atCubeHash[0].nFrame;
  v59 = 2048;
  do
  {
    if ( (igi2_frame.nFrame & 0xFFFF0000) == (*p_nFrame & 0xFFFF0000) && (unsigned __int16)*p_nFrame != (unsigned __int16)igi2_frame.nFrame
      || (unsigned __int16)*p_nFrame + 1 < (unsigned __int16)igi2_frame.nFrame )
    {
      *p_nFrame = -1;
    }
    p_nFrame += 7;
    --v59;
  }
  while ( v59 );
}

// source: e/2/qcube.c:1714  [anchor-hash]
void __cdecl QCube_TraverseWorldTree(struct World_s *ptWorld)
{
  double nX; // st7
  double nY; // st7
  double nZ; // st7
  int v4; // eax

  QCube_tOrigoInt32x3 = ptWorld->tOrigo;
  nX = (double)ptWorld->tOrigo.nX;
  QCube_iLeaveBuffer = 0;
  QCube_tOrigoReal32x3.vX = nX;
  QCube_iLeaveImmediatelyBuffer = 0;
  nY = (double)ptWorld->tOrigo.nY;
  QCube_nNumObjects = 0;
  QCube_nNumTerrainObj = 0;
  QCube_nLevel = 0;
  QCube_tOrigoReal32x3.vY = nY;
  nZ = (double)ptWorld->tOrigo.nZ;
  World_ptExternalCube = (struct CubeTree_s *)-1;
  QCube_ptWorld = ptWorld;
  QCube_tOrigoReal32x3.vZ = nZ;
  QCube_tOrigoReal64x3.vX = (double)ptWorld->tOrigo.nX;
  QCube_tOrigoReal64x3.vY = (double)ptWorld->tOrigo.nY;
  QCube_tOrigoReal64x3.vZ = (double)ptWorld->tOrigo.nZ;
  if ( TransContext_tActiveTransContext.vFOVX <= 1.0 )
    v4 = (__int64)((double)QCube_DynCubeDetailLevel / pow(TransContext_tActiveTransContext.vFOVX, 0.5));
  else
    v4 = QCube_DynCubeDetailLevel;
  QCube_nMainDetailLevel = v4;
  if ( v4 < 70 )
    QCube_nMainDetailLevel = 70;
  QCube_ProcessCube(ptWorld);
}

// source: e/2/qcube.c:1820  [anchor-mhash]
void __cdecl World_DrawManualDynCubeObj(struct DynCubeObj_s *ptDynCubeObj)
{
  enum DynCubeRenderGroup_e iRenderGroup; // edx
  struct CallQueueItem_s *v2; // eax
  struct CallQueueItem_s *ptNext; // edi
  int v4; // edx
  struct CallQueueItem_s **v5; // ecx

  iRenderGroup = ptDynCubeObj->iRenderGroup;
  v2 = CallQueue_ptFirstFreeItem;
  ptNext = CallQueue_ptFirstFreeItem->ptNext;
  CallQueue_ptFirstFreeItem->pxContext = ptDynCubeObj->tQObj.pxQData;
  v4 = 8 * iRenderGroup + 128714432;
  v2->ptQTask = &ptDynCubeObj->tQObj.tQTask;
  v2->uEvent.eQTaskEvent = 5;
  v2->isNoContext = false;
  v2->ptNext = nullptr;
  v5 = *(struct CallQueueItem_s ***)(v4 + 4);
  CallQueue_ptFirstFreeItem = ptNext;
  *v5 = v2;
  *(_DWORD *)(v4 + 4) = v2;
}

// source: e/2/qcube.c:1839  [anchor-caller]
void __cdecl World_Draw(
        struct World_s *ptWorld,
        enum bool isEnableCubeTree,
        struct GetSectorContext_t *ptSectorContext)
{
  struct CallQueue_t *v3; // eax
  struct DynCubeObj_s *ptInsideSectorObject; // eax
  struct DynCubeObj_s *ptInsideSector; // ebx
  struct DynCubeObj_s *ptManualRedrawList; // ecx
  struct CallQueueItem_s *v7; // edx
  enum DynCubeRenderGroup_e iRenderGroup; // esi
  void *pxQData; // edi
  struct CallQueueItem_s *v10; // eax
  struct CallQueue_t *v11; // esi
  struct CallQueueItem_s *ptFirst; // eax
  struct CallQueueItem_s *ptNext; // ecx
  bool v14; // zf

  v3 = QCube_atCallQueues;
  do
  {
    v3->pptLast = &v3->ptFirst;
    v3->ptFirst = nullptr;
    ++v3;
  }
  while ( (int)v3 < 128714560 );
  QCube_nCubesLastRegistered = QCube_nCubesRegistered;
  QCube_nCubesRegistered = 0;
  CubeOcclusion_ResetList();
  Lightsource_nLightDataBufferPos = 0;
  Lightsource_nNumPointlights = 0;
  Lightsource_nNumSpotlights = 0;
  Hazinglayers_iHazingBuffer = 0;
  if ( TransContext_tActiveTransContext.isDraw )
  {
    if ( isEnableCubeTree )
    {
      if ( ptSectorContext )
      {
        ptInsideSectorObject = ptSectorContext->ptInsideSectorObject;
        ptInsideSector = ptSectorContext->ptInsideSector;
        QCube_ptInsideSector = ptInsideSector;
        QCube_ptInsideSectorObject = ptInsideSectorObject;
        if ( ptInsideSectorObject )
          ptInsideSectorObject->iRenderGroup = RenderGroup_InsideSectorObject;
        qmemcpy(&QCube_tInsideSectorObjectPos, &ptSectorContext->tOptimalPos, sizeof(QCube_tInsideSectorObjectPos));
        QCube_vInsideSectorObjectRadius = ptSectorContext->vOptimalRadius;
        if ( ptInsideSector )
        {
          DebugConsole_PushActiveConsole(RenderInfo_tFrameInfoConsoleID);
          DebugConsole_printf(
            "Camera sector: %s\n\n",
            (char *)&ptInsideSector[1].tQObj.tQTask.ptPrev->tQTaskRefList);
          DebugConsole_PopActiveConsole();
          ptInsideSectorObject = QCube_ptInsideSectorObject;
        }
        if ( ptInsideSectorObject )
          QCube_isDrawOutside = 0;
      }
      QCube_TraverseWorldTree(ptWorld);
    }
    ptManualRedrawList = ptWorld->ptManualRedrawList;
    v7 = CallQueue_ptFirstFreeItem;
    if ( ptManualRedrawList )
    {
      do
      {
        iRenderGroup = ptManualRedrawList->iRenderGroup;
        pxQData = ptManualRedrawList->tQObj.pxQData;
        v10 = v7;
        v7 = v7->ptNext;
        v10->ptQTask = &ptManualRedrawList->tQObj.tQTask;
        v10->uEvent.eQTaskEvent = 5;
        v10->isNoContext = false;
        v10->pxContext = pxQData;
        v10->ptNext = nullptr;
        *QCube_atCallQueues[iRenderGroup].pptLast = v10;
        QCube_atCallQueues[iRenderGroup].pptLast = &v10->ptNext;
        ptManualRedrawList = ptManualRedrawList->ptNext;
      }
      while ( ptManualRedrawList );
      CallQueue_ptFirstFreeItem = v7;
    }
    if ( isEnableCubeTree )
    {
      QCube_CallHandlers(ptWorld);
    }
    else
    {
      v11 = QCube_atCallQueues;
      do
      {
        ptFirst = v11->ptFirst;
        if ( v11->ptFirst )
        {
          do
          {
            ptNext = ptFirst->ptNext;
            v14 = ptFirst->ptNext == nullptr;
            ptFirst->ptNext = v7;
            v7 = ptFirst;
            ptFirst = ptNext;
          }
          while ( !v14 );
        }
        v11->pptLast = &v11->ptFirst;
        v11->ptFirst = nullptr;
        ++v11;
      }
      while ( (int)v11 < 128714560 );
      CallQueue_ptFirstFreeItem = v7;
    }
  }
  QCube_ptInsideSector = nullptr;
  QCube_ptInsideSectorObject = nullptr;
  QCube_isInsideSectorObjectDrawn = 0;
  QCube_isDrawOutside = 1;
}

// source: e/2/qcube.c:2153  [size]
int __cdecl QCube_SetDynCubeDetailLevel(int nDetailLevel)
{
  QCube_DynCubeDetailLevel = nDetailLevel;
  return nDetailLevel;
}
