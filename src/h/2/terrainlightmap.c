/* h/2/terrainlightmap.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/terrainlightmap.c:148  [size]
void __cdecl TerrainLightMap_SaveBitmap(struct World_s *ptWorld)
{
  ;
}

// source: h/2/terrainlightmap.c:161  [anchor-mhash]
void __cdecl TerrainLightMap_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[2].ptParent = (struct QTask_s *)World_ptActiveWorld;
  ptQTask[3].ptNext = nullptr;
  ptQTask[3].ptPrev = nullptr;
  ptQTask[3].tQTaskChildren.ptHead = nullptr;
  ptQTask[3].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[3].tQTaskChildren.ptTail = nullptr;
  ptQTask[3].tQTaskRefList.ptHead = nullptr;
  ptQTask[3].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[3].tQTaskRefList.ptTail = nullptr;
  ptQTask[3].ptParent = nullptr;
  *(_DWORD *)&ptQTask[3].eQTaskType = 0;
  ptQTask[4].ptNext = nullptr;
  ptQTask[4].ptPrev = nullptr;
  ptQTask[4].tQTaskChildren.ptHead = nullptr;
  ptQTask[4].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[4].tQTaskChildren.ptTail = nullptr;
  ptQTask[4].tQTaskRefList.ptHead = nullptr;
  ptQTask[4].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[4].tQTaskRefList.ptTail = nullptr;
  memset(&ptQTask[5].eQTaskType, 0, 0x2Cu);
  BYTE1(ptQTask[5].ptNext) = 0;
  LOBYTE(ptQTask[5].ptNext) = 0;
  BYTE2(ptQTask[5].ptNext) = 0;
  LOBYTE(ptQTask[5].tQTaskChildren.ptHead) = 0;
  HIBYTE(ptQTask[5].ptPrev) = 0;
  ptQTask[5].tQTaskRefList.ptMiddle = nullptr;
  BYTE1(ptQTask[5].ptPrev) = 0;
  LOBYTE(ptQTask[5].ptPrev) = 0;
  BYTE2(ptQTask[5].ptPrev) = 0;
  HIBYTE(ptQTask[5].ptNext) = 0;
  BYTE1(ptQTask[5].tQTaskChildren.ptHead) = 0;
  ptQTask[7].ptPrev = nullptr;
  BYTE2(ptQTask[5].tQTaskChildren.ptHead) = 0;
  HIBYTE(ptQTask[5].tQTaskChildren.ptHead) = 0;
  LOBYTE(ptQTask[5].tQTaskChildren.ptMiddle) = 0;
  BYTE1(ptQTask[5].tQTaskChildren.ptMiddle) = 0;
  ptQTask[7].ptNext = nullptr;
  ptQTask[5].tQTaskRefList.ptTail = (struct QReference_s *)-1;
  ptQTask[4].ptParent = (struct QTask_s *)10;
  ptQTask[5].tQTaskChildren.ptTail = (struct QTask_s *)64;
  ptQTask[5].tQTaskRefList.ptHead = (struct QReference_s *)64;
  TerrainLightMap_tRandomState.anRandom[0] = -773192938;
  TerrainLightMap_tRandomState.anRandom[1] = -965544106;
  TerrainLightMap_tRandomState.anRandom[2] = 1572805325;
}

// source: h/2/terrainlightmap.c:218  [anchor-mhash]
void __cdecl TerrainLightMap_CreateRenderItem(struct TerrainLightMap_t *ptTerrainLightMap)
{
  unsigned int v1; // eax
  int v2; // ecx

  v1 = 48 * ptTerrainLightMap->iIndex;
  TerrainLightMap_atRenderItem[v1 / 0x30].ptTexInfo = ptTerrainLightMap->ptTexInfo;
  TerrainLightMap_atRenderItem[v1 / 0x30].vScale = 1.0;
  v2 = 23 - ptTerrainLightMap->nLevel;
  TerrainLightMap_atRenderItem[v1 / 0x30].nShift = v2;
  *(float *)(v1 + 139188784) = 1.0 / (double)(1 << v2);
  *(float *)(v1 + 139188788) = 256.0 / (double)ptTerrainLightMap->nEditSize * 0.5;
  *(double *)(v1 + 139188792) = ptTerrainLightMap->tDynCubeObj.tQObj.tPos.vX
                              - (double)(0x40000000 >> ptTerrainLightMap->nLevel);
  *(double *)(v1 + 139188800) = ptTerrainLightMap->tDynCubeObj.tQObj.tPos.vY
                              - (double)(0x40000000 >> ptTerrainLightMap->nLevel);
}

// source: h/2/terrainlightmap.c:248  [anchor-mhash]
void __cdecl TerrainLightMap_EnterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v2; // eax
  struct QReference_s *v3; // ecx
  int v4; // eax
  struct QReference_s *ptMiddle; // edx
  int v6; // eax

  if ( Level_isDynamicQTaskActive || !Level_isDynamicQTaskPaused )
  {
    v2 = ptQTask;
    if ( ptQTask[7].ptNext )
    {
      ptMiddle = ptQTask[5].tQTaskRefList.ptMiddle;
      ptQTask[5].ptParent = (struct QTask_s *)1;
      v6 = TerrainLightMap_nStackItem;
      TerrainLightMap_aiStackItem[TerrainLightMap_nStackItem] = (unsigned int)ptMiddle;
      TerrainLightMap_nStackItem = v6 + 1;
      return;
    }
  }
  else
  {
    v2 = ptQTask;
    if ( ptQTask[7].ptNext )
    {
      v3 = ptQTask[5].tQTaskRefList.ptMiddle;
      ptQTask[5].ptParent = (struct QTask_s *)1;
      v4 = TerrainLightMap_nStackItem;
      TerrainLightMap_aiStackItem[TerrainLightMap_nStackItem] = (unsigned int)v3;
      TerrainLightMap_nStackItem = v4 + 1;
      return;
    }
  }
  v2[5].ptParent = nullptr;
}

// source: h/2/terrainlightmap.c:302  [size]
void __cdecl TerrainLightMap_LeaveHandler(struct QTask_s *ptQTask, void *pxContext)
{
  if ( ptQTask[5].ptParent )
    --TerrainLightMap_nStackItem;
}

// source: h/2/terrainlightmap.c:360  [anchor-caller]
void __cdecl TerrainLightMap_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptParent; // ecx
  int ptMiddle; // eax
  struct QTask_s *v3; // edx
  struct TerrainLightMap_t *v4; // ecx
  struct TexInfo_s *ptNext; // eax

  if ( BYTE1(ptQTask[5].tQTaskChildren.ptMiddle) )
  {
    if ( !BYTE2(ptQTask[5].tQTaskChildren.ptHead) )
    {
      ptParent = ptQTask[2].ptParent[9].ptParent;
      ptMiddle = (int)ptQTask[5].tQTaskRefList.ptMiddle;
      v3 = (struct QTask_s *)((char *)ptParent - 1);
      if ( (char *)ptMiddle != &ptParent[-1].isInMemPool + 1 )
      {
        v4 = (struct TerrainLightMap_t *)dword_84BBA1C[(_DWORD)ptParent];
        TerrainLightMap_aptTerrainLightMap[ptMiddle] = v4;
        v4->iIndex = ptMiddle;
      }
      ptQTask[2].ptParent[9].ptParent = v3;
      ptNext = (struct TexInfo_s *)ptQTask[7].ptNext;
      if ( ptNext )
      {
        if ( !TerrainLightMap_atTexInfo[(int)ptQTask[5].tQTaskRefList.ptTail].pxData )
          Texture_Free(ptNext);
      }
    }
    World_RemoveDynCubeObj((struct World_s *)ptQTask[2].ptParent, (struct DynCubeObj_s *)ptQTask);
  }
}

// source: h/2/terrainlightmap.c:426  [size]
void __cdecl TerrainLightMap_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = TerrainLightMap_ptParameterList;
}

// source: h/2/terrainlightmap.c:2159  [anchor-caller]
void __cdecl TerrainLightMap_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct World_s *v33; };
    struct { char igi2_o1[44]; int nCubeSize; };
    struct { char igi2_o2[44]; int nCubeSizea; };
    struct { char igi2_o3[44]; int nCubeSizeb; };
    struct { char igi2_o4[48]; double vHighestZ; };
    struct { char igi2_o5[48]; double vHighestZa; };
    struct { char igi2_o6[48]; double vHighestZb; };
    struct { char igi2_o7[56]; double vRadius; };
    struct { char igi2_o8[64]; struct real64x3_t tNewPos; };
    struct { char igi2_o9[92]; int isNotFirstTime; };
    struct { char igi2_o10[96]; double vLowestZ; };
    struct { char igi2_o11[104]; double vNegDist; };
    struct { char igi2_o12[112]; struct real64x3_t tGetNextZPos; };
    struct { char igi2_o13[136]; struct real64x3_t tCenterPos; };
    struct { char igi2_o14[160]; struct QIntersection_s tIntersection; };
    struct { char igi2_o15[280]; char zFileName[128]; };
    struct { char igi2_o16[408]; char zName[128]; };
    struct { char igi2_o17[536]; char zDrive[128]; };
    struct { char igi2_o18[664]; char zPath[128]; };
    struct { char igi2_o19[792]; char zExtension[128]; };
    char igi2_extent[920];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct TerrainLightMap_t *v2; // ebx
  struct QTask_s *ptParent; // ecx
  char v4; // al
  struct QTask_s *v5; // ecx
  struct QReference_s *v6; // eax
  struct QReference_s *ptTail; // eax
  int v8; // eax
  void *v9; // eax
  struct QReference_s *ptHead; // esi
  void *v11; // ebx
  int isHit; // eax
  int v13; // esi
  double vZ; // st7
  struct World_s *ptWorld; // eax
  double v16; // st7
  double v17; // st6
  double v18; // st7
  bool v19; // zf
  double nZ; // st7
  int nEditSize; // eax
  int v22; // ecx
  int nLevel; // eax
  unsigned int v24; // ecx
  unsigned int v25; // edx
  unsigned int v26; // eax
  int v27; // ecx
  int v28; // edx
  unsigned __int16 BaseQTaskType; // ax
  struct QTask_s *ptContainer; // ecx
  unsigned __int16 v31; // ax
  struct QTask_s *v32; // ecx

  v2 = (struct TerrainLightMap_t *)ptQTask;
  ptParent = ptQTask[4].ptParent;
  igi2_frame.vNegDist = -536870912.0;
  igi2_frame.nCubeSize = 2 * (0x40000000 >> (char)ptParent);
  if ( AppContext_tAppContext.isLightmapsDisabled && AppContext_tAppContext.isTerrainLightmapsUsed == false )
  {
    igi2_frame.isNotFirstTime = SHIBYTE(ptQTask[5].ptPrev);
    v4 = BYTE2(ptQTask[5].tQTaskChildren.ptHead);
    BYTE1(ptQTask[5].tQTaskChildren.ptMiddle) = 1;
    if ( !v4 )
    {
      if ( ptQTask[7].ptPrev )
      {
        QTask_Delete(ptQTask[7].ptPrev);
        ptQTask[7].ptPrev = nullptr;
      }
      if ( !HIBYTE(ptQTask[5].ptPrev) )
      {
        v5 = ptQTask[2].ptParent[9].ptParent;
        v6 = nullptr;
        for ( HIBYTE(ptQTask[5].ptPrev) = 1; (int)v6 < (int)v5; v6 = (struct QReference_s *)((char *)v6 + 1) )
        {
          if ( !TerrainLightMap_aptTerrainLightMap[(_DWORD)v6] )
            break;
        }
        ptQTask[5].tQTaskRefList.ptMiddle = v6;
        TerrainLightMap_aptTerrainLightMap[(_DWORD)v6] = (struct TerrainLightMap_t *)ptQTask;
        if ( v6 == (struct QReference_s *)v5 )
          v5 = (struct QTask_s *)((char *)v5 + 1);
        if ( (int)v5 >= 2048 )
        {
          LDebug_Error("Too many lightmaps whene generated");
          goto LABEL_14;
        }
        ptQTask[2].ptParent[9].ptParent = v5;
        if ( ptQTask[2].ptParent[10].ptNext )
        {
          ptTail = ptQTask[5].tQTaskRefList.ptTail;
          if ( ptTail != (struct QReference_s *)-1 )
          {
            v8 = (int)ptTail;
            if ( TerrainLightMap_atTexInfo[v8].pxData )
              ptQTask[7].ptNext = (struct QTask_s *)&TerrainLightMap_atTexInfo[v8].tTexInfo;
          }
        }
        else if ( ptQTask[5].tQTaskRefList.ptTail != (struct QReference_s *)-1 && strlen(World_zTerrainFileName) )
        {
          splitpath(World_zTerrainFileName, igi2_frame.zDrive, igi2_frame.zPath, igi2_frame.zName, igi2_frame.zExtension);
          sprintf(igi2_frame.zFileName, "%s%slightmap/%s%d.lmp", igi2_frame.zDrive, igi2_frame.zPath, igi2_frame.zName, ptQTask[5].tQTaskRefList.ptTail);
          if ( Resource_IsLoadedInternal(igi2_frame.zFileName, nullptr) || File_Exists(igi2_frame.zFileName) )
          {
            v9 = Resource_Load(igi2_frame.zFileName, nullptr);
            ptHead = ptQTask[5].tQTaskRefList.ptHead;
            v11 = v9;
            if ( Texture_GetTMUs() > 1 )
              Texture_SetActiveTMU(1);
            Texture_AllocAndDownload(
              (struct TexInfo_s *)ptQTask[7].ptNext,
              *(struct PalInfo **)&ptQTask[2].ptParent[9].eQTaskType,
              (int)ptHead,
              (int)ptHead,
              (int)ptHead,
              1,
              0,
              0,
              v11);
            if ( Texture_GetTMUs() > 1 )
              Texture_SetActiveTMU(-1);
            Resource_Unload(igi2_frame.zFileName);
          }
          v2 = (struct TerrainLightMap_t *)ptQTask;
        }
      }
    }
    qmemcpy(&igi2_frame.tNewPos, &v2->tEditPos, sizeof(igi2_frame.tNewPos));
    if ( v2->isCopy )
      goto LABEL_36;
    qmemcpy(&igi2_frame.tGetNextZPos, &v2->tEditPos, sizeof(igi2_frame.tGetNextZPos));
    igi2_frame.tGetNextZPos.vZ = igi2_frame.tGetNextZPos.vZ + 268435456.0;
    isHit = 0;
    igi2_frame.tIntersection.isHit = 0;
    v13 = 0;
    while ( v13 < 5 )
    {
      World_GetNextZ(v2->ptWorld, &igi2_frame.tIntersection, &igi2_frame.tGetNextZPos, 1, &igi2_frame.vNegDist, 512, nullptr, 0x80000000);
      isHit = igi2_frame.tIntersection.isHit;
      ++v13;
      if ( igi2_frame.tIntersection.isHit )
      {
        vZ = igi2_frame.tIntersection.tPos.vZ;
        goto LABEL_37;
      }
    }
    if ( !isHit )
LABEL_36:
      vZ = igi2_frame.tNewPos.vZ;
    else
      vZ = igi2_frame.tIntersection.tPos.vZ;
LABEL_37:
    ptWorld = v2->ptWorld;
    igi2_frame.tNewPos.vX = (double)ptWorld->tOrigo.nX + igi2_frame.tNewPos.vX;
    igi2_frame.tNewPos.vY = (double)ptWorld->tOrigo.nY + igi2_frame.tNewPos.vY;
    igi2_frame.tNewPos.vZ = (double)ptWorld->tOrigo.nZ + vZ;
    v16 = (double)(int)(-igi2_frame.nCubeSize & (__int64)igi2_frame.tNewPos.vX);
    v2->tMin.vX = v16;
    v17 = (double)(int)(-igi2_frame.nCubeSize & (__int64)igi2_frame.tNewPos.vY);
    v2->tMin.vY = v17;
    igi2_frame.vLowestZ = (double)(int)(-igi2_frame.nCubeSize & (__int64)igi2_frame.tNewPos.vZ);
    v2->tMin.vZ = igi2_frame.vLowestZ;
    qmemcpy(&igi2_frame.tNewPos, &v2->tMin, sizeof(igi2_frame.tNewPos));
    igi2_frame.vHighestZa = (double)igi2_frame.nCubeSize;
    v2->tMax.vX = igi2_frame.vHighestZa + v16;
    v2->tMax.vY = igi2_frame.vHighestZa + v17;
    v2->tMax.vZ = igi2_frame.vHighestZa + igi2_frame.vLowestZ;
    igi2_frame.tNewPos.vY = igi2_frame.vHighestZa * 0.5 + igi2_frame.tNewPos.vY;
    v18 = igi2_frame.tNewPos.vX + igi2_frame.vHighestZa * 0.5;
    igi2_frame.tNewPos.vZ = igi2_frame.vHighestZa * 0.5 + igi2_frame.tNewPos.vZ;
    igi2_frame.vHighestZb = (double)ptWorld->tOrigo.nX;
    igi2_frame.tNewPos.vX = v18 - igi2_frame.vHighestZb;
    igi2_frame.tNewPos.vY = igi2_frame.tNewPos.vY - (double)ptWorld->tOrigo.nY;
    igi2_frame.tNewPos.vZ = igi2_frame.tNewPos.vZ - (double)ptWorld->tOrigo.nZ;
    v2->tMin.vX = v2->tMin.vX - igi2_frame.vHighestZb;
    v2->tMin.vY = v2->tMin.vY - (double)ptWorld->tOrigo.nY;
    v2->tMin.vZ = v2->tMin.vZ - (double)ptWorld->tOrigo.nZ;
    v19 = igi2_frame.isNotFirstTime == 0;
    v2->tMax.vX = v2->tMax.vX - (double)ptWorld->tOrigo.nX;
    v2->tMax.vY = v2->tMax.vY - (double)ptWorld->tOrigo.nY;
    nZ = (double)ptWorld->tOrigo.nZ;
    v2->isFirstTimeUpdated = 1;
    v2->tMax.vZ = v2->tMax.vZ - nZ;
    if ( v19 )
      World_RegisterDynCubeObjFirstTimeMinMaxXYZ(
        ptWorld,
        &v2->tDynCubeObj,
        &igi2_frame.tNewPos,
        &v2->tMin,
        &v2->tMax,
        WORLD_DYNCUBETREE_CATEGORY_TERRAINMODIFIERS);
    World_MoveDynCubeObjMinMaxXYZ(v2->ptWorld, &v2->tDynCubeObj, &igi2_frame.tNewPos, &v2->tMin, &v2->tMax);
    if ( !v2->isCopy )
    {
      nEditSize = v2->nEditSize;
      switch ( nEditSize )
      {
        case 256:
          v22 = 7;
          break;
        case 128:
          v22 = 6;
          break;
        case 64:
          v22 = 5;
          break;
        case 32:
          v22 = 4;
          break;
        case 16:
          v22 = 3;
          break;
        case 8:
          v22 = 2;
          break;
        default:
          LDebug_Error("Illegal shift size");
LABEL_14:
          abort();
      }
      nLevel = v2->nLevel;
      v2->nShift = 30 - nLevel - v22;
      qmemcpy(&igi2_frame.tCenterPos, &v2->tDynCubeObj.tQObj.tPos, sizeof(igi2_frame.tCenterPos));
      igi2_frame.vLowestZ = igi2_frame.tCenterPos.vZ;
      igi2_frame.vHighestZ = igi2_frame.tCenterPos.vZ;
      igi2_frame.nCubeSizea = 32;
      igi2_frame.isNotFirstTime = 0x40000000 >> nLevel;
      igi2_frame.vRadius = (double)(0x40000000 >> nLevel);
      do
      {
        qmemcpy(&igi2_frame.tGetNextZPos, &igi2_frame.tCenterPos, sizeof(igi2_frame.tGetNextZPos));
        v24 = (TerrainLightMap_tRandomState.anRandom[0] >> 7) ^ TerrainLightMap_tRandomState.anRandom[2];
        v25 = v24 ^ TerrainLightMap_tRandomState.anRandom[1];
        v26 = (v24 ^ TerrainLightMap_tRandomState.anRandom[1]) + TerrainLightMap_tRandomState.anRandom[0];
        v27 = (v26 >> 7) ^ v24;
        v28 = v27 ^ v25;
        TerrainLightMap_tRandomState.anRandom[0] = v28 + v26;
        igi2_frame.isNotFirstTime = (unsigned __int16)(v28 + v26);
        TerrainLightMap_tRandomState.anRandom[2] = v27;
        TerrainLightMap_tRandomState.anRandom[1] = v28;
        igi2_frame.tGetNextZPos.vX = ((double)(unsigned __int16)v26 * 0.0000152587890625
                         + (double)(unsigned __int16)v26 * 0.0000152587890625
                         - 1.0)
                        * igi2_frame.vRadius
                        + igi2_frame.tCenterPos.vX;
        igi2_frame.v33 = v2->ptWorld;
        igi2_frame.tGetNextZPos.vY = ((double)igi2_frame.isNotFirstTime * 0.0000152587890625
                         + (double)igi2_frame.isNotFirstTime * 0.0000152587890625
                         - 1.0)
                        * igi2_frame.vRadius
                        + igi2_frame.tGetNextZPos.vY;
        igi2_frame.tGetNextZPos.vZ = igi2_frame.tGetNextZPos.vZ + 268435456.0;
        World_GetNextZ(igi2_frame.v33, &igi2_frame.tIntersection, &igi2_frame.tGetNextZPos, 1, &igi2_frame.vNegDist, 512, nullptr, 0x80000000);
        if ( igi2_frame.tIntersection.isHit )
        {
          if ( igi2_frame.tIntersection.tPos.vZ < igi2_frame.vLowestZ )
            igi2_frame.vLowestZ = igi2_frame.tIntersection.tPos.vZ;
          if ( igi2_frame.tIntersection.tPos.vZ > igi2_frame.vHighestZ )
            igi2_frame.vHighestZ = igi2_frame.tIntersection.tPos.vZ;
        }
        --igi2_frame.nCubeSizea;
      }
      while ( igi2_frame.nCubeSizea );
      qmemcpy(&igi2_frame.tNewPos, &igi2_frame.tCenterPos, sizeof(igi2_frame.tNewPos));
      igi2_frame.tNewPos.vZ = igi2_frame.tCenterPos.vZ - igi2_frame.vRadius;
      for ( igi2_frame.nCubeSizeb = 0; igi2_frame.vLowestZ < igi2_frame.tNewPos.vZ; igi2_frame.tNewPos.vZ = igi2_frame.tNewPos.vZ - igi2_frame.vRadius )
      {
        if ( !igi2_frame.nCubeSizeb )
        {
          BaseQTaskType = QTask_GetBaseQTaskType();
          v2->ptContainer = QTask_NewFn(&v2->tDynCubeObj.tQObj.tQTask, BaseQTaskType, nullptr);
          igi2_frame.nCubeSizeb = 1;
        }
        ptContainer = v2->ptContainer;
        igi2_frame.tNewPos.vZ = igi2_frame.tNewPos.vZ - igi2_frame.vRadius;
        TerrainLightMap_NewCopy(ptContainer, v2, &igi2_frame.tNewPos);
      }
      qmemcpy(&igi2_frame.tNewPos, &igi2_frame.tCenterPos, sizeof(igi2_frame.tNewPos));
      for ( igi2_frame.tNewPos.vZ = igi2_frame.vRadius + igi2_frame.tCenterPos.vZ; igi2_frame.vHighestZ > igi2_frame.tNewPos.vZ; igi2_frame.tNewPos.vZ = igi2_frame.tNewPos.vZ + igi2_frame.vRadius )
      {
        if ( !igi2_frame.nCubeSizeb )
        {
          v31 = QTask_GetBaseQTaskType();
          v2->ptContainer = QTask_NewFn(&v2->tDynCubeObj.tQObj.tQTask, v31, nullptr);
          igi2_frame.nCubeSizeb = 1;
        }
        v32 = v2->ptContainer;
        igi2_frame.tNewPos.vZ = igi2_frame.tNewPos.vZ + igi2_frame.vRadius;
        TerrainLightMap_NewCopy(v32, v2, &igi2_frame.tNewPos);
      }
    }
    TerrainLightMap_CreateRenderItem(v2);
  }
}

// source: h/2/terrainlightmap.c:2714  [anchor-hash]
void __cdecl TerrainLightMap_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // edx

  TerrainLightMap_tRandomState.anRandom[0] = -773192938;
  TerrainLightMap_tRandomState.anRandom[1] = -965544106;
  TerrainLightMap_tRandomState.anRandom[2] = 1572805325;
  v0 = QTask_NewQTaskType("TerrainLightMap", 288, DynCubeObj_eQTaskType, 0, 0);
  TerrainLightMap_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 0, TerrainLightMap_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 16, (void (__cdecl *)(struct QTask_s *, void *))TerrainLightMap_LeaveHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, TerrainLightMap_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))TerrainLightMap_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eUpdateInternalDataQTaskEvent,
    TerrainLightMap_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 11, nullptr);
  QTask_LinkQTaskEventHandlerFn(v0, 12, nullptr);
  QTask_LinkQTaskEventHandlerFn(v0, QCube_eGetClosestVertexQTaskEvent, nullptr);
  QTask_LinkQTaskEventHandlerFn(v0, 10, nullptr);
  QTask_LinkQTaskEventHandlerFn(v0, 13, nullptr);
  QTask_LinkQTaskEventHandlerFn(v0, 9, nullptr);
  QTask_LinkQTaskEventHandlerFn(v0, 5, nullptr);
  QTask_LinkQTaskEventHandlerFn(v0, 6, nullptr);
  QTask_LinkQTaskEventHandlerFn(v0, 15, TerrainLightMap_EnterHandler);
  v1 = (struct ParameterList_s *)Mem_AllocFn(312, 4);
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  v2 = Level_eParameterTypeObjectPos;
  v1->nParameters = 0;
  v1->nMaxParameters = 15;
  TerrainLightMap_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0x78u, v2, "Position", 7u, nullptr);
  ParameterList_AddParameter(TerrainLightMap_ptParameterList, 0xC0u, Level_eParameterTypeInt32, "Level", 7u, nullptr);
  ParameterList_AddParameter(TerrainLightMap_ptParameterList, 0xDCu, Level_eParameterTypeInt32, "Size", 7u, nullptr);
  ParameterList_AddParameter(
    TerrainLightMap_ptParameterList,
    0xCDu,
    Level_eParameterTypePushButton,
    "Recalculate",
    6u,
    nullptr);
  ParameterList_AddParameter(TerrainLightMap_ptParameterList, 0xCCu, Level_eParameterTypebool8, "Shadow", 6u, nullptr);
  ParameterList_AddParameter(TerrainLightMap_ptParameterList, 0xCEu, Level_eParameterTypebool8, "Shading", 6u, nullptr);
  ParameterList_AddParameter(TerrainLightMap_ptParameterList, 0xCBu, Level_eParameterTypebool8, "ShowBox", 6u, nullptr);
  ParameterList_AddParameter(
    TerrainLightMap_ptParameterList,
    0xC8u,
    Level_eParameterTypePushButton,
    "GenerateAll",
    6u,
    nullptr);
  ParameterList_AddParameter(
    TerrainLightMap_ptParameterList,
    0xCAu,
    Level_eParameterTypePushButton,
    "SaveAll",
    6u,
    nullptr);
  ParameterList_AddParameter(
    TerrainLightMap_ptParameterList,
    0xC9u,
    Level_eParameterTypePushButton,
    "RenderAll",
    6u,
    nullptr);
  ParameterList_AddParameter(
    TerrainLightMap_ptParameterList,
    0xE4u,
    Level_eParameterTypeInt32,
    "TextureIndex",
    1u,
    nullptr);
  ParameterList_AddParameter(
    TerrainLightMap_ptParameterList,
    0xD0u,
    Level_eParameterTypebool8,
    "GeneratedWhenCreated",
    1u,
    nullptr);
  ParameterList_AddParameter(
    TerrainLightMap_ptParameterList,
    0xD1u,
    Level_eParameterTypePushButton,
    "FixupEdges",
    6u,
    nullptr);
  ParameterList_AddParameter(
    TerrainLightMap_ptParameterList,
    0xD3u,
    Level_eParameterTypebool8,
    "isTopTrace",
    6u,
    nullptr);
  ParameterList_AddParameter(
    TerrainLightMap_ptParameterList,
    0xD4u,
    Level_eParameterTypebool8,
    "isTraceAdvanced",
    6u,
    nullptr);
  TerrainLightMap_nStackItem = 0;
}

// source: h/2/terrainlightmap.c:2780  [size]
void __cdecl TerrainLightMap_Close()
{
  int v0; // esi

  if ( TerrainLightMap_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&TerrainLightMap_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(TerrainLightMap_eQTaskType);
}

// source: h/2/terrainlightmap.c:2797  [size]
unsigned __int16 __cdecl TerrainLightMap_GetQTaskType()
{
  return TerrainLightMap_eQTaskType;
}

// source: h/2/terrainlightmap.c:2816  [anchor-mhash]
struct QTask_s *__cdecl TerrainLightMap_New(
        struct QTask_s *ptParent,
        struct real64x3_t *ptPos,
        int nLevel,
        int nPixelSize)
{
  struct QTask_s *v4; // eax
  int v5; // edx
  struct QTask_s *v6; // ebx
  int eQTaskType; // eax
  void (__cdecl *pfHandler)(struct QTask_s *, _DWORD); // eax

  v4 = QTask_NewFn(ptParent, TerrainLightMap_eQTaskType, nullptr);
  v5 = 511 * ParameterList_eUpdateInternalDataQTaskEvent;
  v6 = v4;
  v4[4].ptParent = (struct QTask_s *)nLevel;
  eQTaskType = v4->eQTaskType;
  v6[5].tQTaskRefList.ptHead = (struct QReference_s *)nPixelSize;
  LOBYTE(v6[5].tQTaskChildren.ptHead) = 1;
  qmemcpy(&v6[3], ptPos, 0x18u);
  pfHandler = (void (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[0][eQTaskType + v5].pfHandler;
  if ( pfHandler )
    pfHandler(v6, 0);
  return v6;
}

// source: h/2/terrainlightmap.c:2865  [anchor-mhash]
struct QTask_s *__cdecl TerrainLightMap_NewCopy(
        struct QTask_s *ptParent,
        struct TerrainLightMap_t *ptCopyOf,
        struct real64x3_t *ptPos)
{
  struct QTask_s *v4; // ebx
  int v5; // edx
  int eQTaskType; // eax
  void (__cdecl *pfHandler)(struct QTask_s *, _DWORD); // eax

  v4 = QTask_NewFn(ptParent, TerrainLightMap_eQTaskType, nullptr);
  BYTE2(v4[5].tQTaskChildren.ptHead) = 1;
  v4[4].ptParent = (struct QTask_s *)ptCopyOf->nLevel;
  v4[5].tQTaskRefList.ptMiddle = (struct QReference_s *)ptCopyOf->iIndex;
  v4[5].tQTaskRefList.ptHead = (struct QReference_s *)ptCopyOf->nEditSize;
  v5 = 511 * ParameterList_eUpdateInternalDataQTaskEvent;
  *(_DWORD *)&v4[4].eQTaskType = ptCopyOf->nShift;
  eQTaskType = v4->eQTaskType;
  v4[7].ptNext = (struct QTask_s *)ptCopyOf->ptTexInfo;
  qmemcpy(&v4[3], ptPos, 0x18u);
  pfHandler = (void (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[0][eQTaskType + v5].pfHandler;
  if ( pfHandler )
    pfHandler(v4, 0);
  return v4;
}
